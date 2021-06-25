<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ss-cipher.c - hardware cryptographic offloader क्रम
 * Allwinner A80/A83T SoC
 *
 * Copyright (C) 2016-2019 Corentin LABBE <clabbe.montjoie@gmail.com>
 *
 * This file add support क्रम AES cipher with 128,192,256 bits keysize in
 * CBC and ECB mode.
 *
 * You could find a link क्रम the datasheet in Documentation/arm/sunxi.rst
 */

#समावेश <linux/crypto.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "sun8i-ss.h"

अटल bool sun8i_ss_need_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा scatterlist *in_sg = areq->src;
	काष्ठा scatterlist *out_sg = areq->dst;
	काष्ठा scatterlist *sg;

	अगर (areq->cryptlen == 0 || areq->cryptlen % 16)
		वापस true;

	अगर (sg_nents(areq->src) > 8 || sg_nents(areq->dst) > 8)
		वापस true;

	sg = areq->src;
	जबतक (sg) अणु
		अगर ((sg->length % 16) != 0)
			वापस true;
		अगर ((sg_dma_len(sg) % 16) != 0)
			वापस true;
		अगर (!IS_ALIGNED(sg->offset, 16))
			वापस true;
		sg = sg_next(sg);
	पूर्ण
	sg = areq->dst;
	जबतक (sg) अणु
		अगर ((sg->length % 16) != 0)
			वापस true;
		अगर ((sg_dma_len(sg) % 16) != 0)
			वापस true;
		अगर (!IS_ALIGNED(sg->offset, 16))
			वापस true;
		sg = sg_next(sg);
	पूर्ण

	/* SS need same numbers of SG (with same length) क्रम source and destination */
	in_sg = areq->src;
	out_sg = areq->dst;
	जबतक (in_sg && out_sg) अणु
		अगर (in_sg->length != out_sg->length)
			वापस true;
		in_sg = sg_next(in_sg);
		out_sg = sg_next(out_sg);
	पूर्ण
	अगर (in_sg || out_sg)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक sun8i_ss_cipher_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	पूर्णांक err;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.skcipher);
	algt->stat_fb++;
#पूर्ण_अगर
	skcipher_request_set_tfm(&rctx->fallback_req, op->fallback_tfm);
	skcipher_request_set_callback(&rctx->fallback_req, areq->base.flags,
				      areq->base.complete, areq->base.data);
	skcipher_request_set_crypt(&rctx->fallback_req, areq->src, areq->dst,
				   areq->cryptlen, areq->iv);
	अगर (rctx->op_dir & SS_DECRYPTION)
		err = crypto_skcipher_decrypt(&rctx->fallback_req);
	अन्यथा
		err = crypto_skcipher_encrypt(&rctx->fallback_req);
	वापस err;
पूर्ण

अटल पूर्णांक sun8i_ss_cipher(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ss_dev *ss = op->ss;
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक toकरो, len, offset, ivsize;
	व्योम *backup_iv = शून्य;
	पूर्णांक nr_sgs = 0;
	पूर्णांक nr_sgd = 0;
	पूर्णांक err = 0;
	पूर्णांक i;

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.skcipher);

	dev_dbg(ss->dev, "%s %s %u %x IV(%p %u) key=%u\n", __func__,
		crypto_tfm_alg_name(areq->base.tfm),
		areq->cryptlen,
		rctx->op_dir, areq->iv, crypto_skcipher_ivsize(tfm),
		op->keylen);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	algt->stat_req++;
#पूर्ण_अगर

	rctx->op_mode = ss->variant->op_mode[algt->ss_blockmode];
	rctx->method = ss->variant->alg_cipher[algt->ss_algo_id];
	rctx->keylen = op->keylen;

	rctx->p_key = dma_map_single(ss->dev, op->key, op->keylen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ss->dev, rctx->p_key)) अणु
		dev_err(ss->dev, "Cannot DMA MAP KEY\n");
		err = -EFAULT;
		जाओ theend;
	पूर्ण

	ivsize = crypto_skcipher_ivsize(tfm);
	अगर (areq->iv && crypto_skcipher_ivsize(tfm) > 0) अणु
		rctx->ivlen = ivsize;
		rctx->biv = kzalloc(ivsize, GFP_KERNEL | GFP_DMA);
		अगर (!rctx->biv) अणु
			err = -ENOMEM;
			जाओ theend_key;
		पूर्ण
		अगर (rctx->op_dir & SS_DECRYPTION) अणु
			backup_iv = kzalloc(ivsize, GFP_KERNEL);
			अगर (!backup_iv) अणु
				err = -ENOMEM;
				जाओ theend_key;
			पूर्ण
			offset = areq->cryptlen - ivsize;
			scatterwalk_map_and_copy(backup_iv, areq->src, offset,
						 ivsize, 0);
		पूर्ण
		स_नकल(rctx->biv, areq->iv, ivsize);
		rctx->p_iv = dma_map_single(ss->dev, rctx->biv, rctx->ivlen,
					    DMA_TO_DEVICE);
		अगर (dma_mapping_error(ss->dev, rctx->p_iv)) अणु
			dev_err(ss->dev, "Cannot DMA MAP IV\n");
			err = -ENOMEM;
			जाओ theend_iv;
		पूर्ण
	पूर्ण
	अगर (areq->src == areq->dst) अणु
		nr_sgs = dma_map_sg(ss->dev, areq->src, sg_nents(areq->src),
				    DMA_BIसूचीECTIONAL);
		अगर (nr_sgs <= 0 || nr_sgs > 8) अणु
			dev_err(ss->dev, "Invalid sg number %d\n", nr_sgs);
			err = -EINVAL;
			जाओ theend_iv;
		पूर्ण
		nr_sgd = nr_sgs;
	पूर्ण अन्यथा अणु
		nr_sgs = dma_map_sg(ss->dev, areq->src, sg_nents(areq->src),
				    DMA_TO_DEVICE);
		अगर (nr_sgs <= 0 || nr_sgs > 8) अणु
			dev_err(ss->dev, "Invalid sg number %d\n", nr_sgs);
			err = -EINVAL;
			जाओ theend_iv;
		पूर्ण
		nr_sgd = dma_map_sg(ss->dev, areq->dst, sg_nents(areq->dst),
				    DMA_FROM_DEVICE);
		अगर (nr_sgd <= 0 || nr_sgd > 8) अणु
			dev_err(ss->dev, "Invalid sg number %d\n", nr_sgd);
			err = -EINVAL;
			जाओ theend_sgs;
		पूर्ण
	पूर्ण

	len = areq->cryptlen;
	i = 0;
	sg = areq->src;
	जबतक (i < nr_sgs && sg && len) अणु
		अगर (sg_dma_len(sg) == 0)
			जाओ sgs_next;
		rctx->t_src[i].addr = sg_dma_address(sg);
		toकरो = min(len, sg_dma_len(sg));
		rctx->t_src[i].len = toकरो / 4;
		dev_dbg(ss->dev, "%s total=%u SGS(%d %u off=%d) todo=%u\n", __func__,
			areq->cryptlen, i, rctx->t_src[i].len, sg->offset, toकरो);
		len -= toकरो;
		i++;
sgs_next:
		sg = sg_next(sg);
	पूर्ण
	अगर (len > 0) अणु
		dev_err(ss->dev, "remaining len %d\n", len);
		err = -EINVAL;
		जाओ theend_sgs;
	पूर्ण

	len = areq->cryptlen;
	i = 0;
	sg = areq->dst;
	जबतक (i < nr_sgd && sg && len) अणु
		अगर (sg_dma_len(sg) == 0)
			जाओ sgd_next;
		rctx->t_dst[i].addr = sg_dma_address(sg);
		toकरो = min(len, sg_dma_len(sg));
		rctx->t_dst[i].len = toकरो / 4;
		dev_dbg(ss->dev, "%s total=%u SGD(%d %u off=%d) todo=%u\n", __func__,
			areq->cryptlen, i, rctx->t_dst[i].len, sg->offset, toकरो);
		len -= toकरो;
		i++;
sgd_next:
		sg = sg_next(sg);
	पूर्ण
	अगर (len > 0) अणु
		dev_err(ss->dev, "remaining len %d\n", len);
		err = -EINVAL;
		जाओ theend_sgs;
	पूर्ण

	err = sun8i_ss_run_task(ss, rctx, crypto_tfm_alg_name(areq->base.tfm));

theend_sgs:
	अगर (areq->src == areq->dst) अणु
		dma_unmap_sg(ss->dev, areq->src, sg_nents(areq->src),
			     DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(ss->dev, areq->src, sg_nents(areq->src),
			     DMA_TO_DEVICE);
		dma_unmap_sg(ss->dev, areq->dst, sg_nents(areq->dst),
			     DMA_FROM_DEVICE);
	पूर्ण

theend_iv:
	अगर (rctx->p_iv)
		dma_unmap_single(ss->dev, rctx->p_iv, rctx->ivlen,
				 DMA_TO_DEVICE);

	अगर (areq->iv && ivsize > 0) अणु
		अगर (rctx->biv) अणु
			offset = areq->cryptlen - ivsize;
			अगर (rctx->op_dir & SS_DECRYPTION) अणु
				स_नकल(areq->iv, backup_iv, ivsize);
				kमुक्त_sensitive(backup_iv);
			पूर्ण अन्यथा अणु
				scatterwalk_map_and_copy(areq->iv, areq->dst, offset,
							 ivsize, 0);
			पूर्ण
			kमुक्त(rctx->biv);
		पूर्ण
	पूर्ण

theend_key:
	dma_unmap_single(ss->dev, rctx->p_key, op->keylen, DMA_TO_DEVICE);

theend:

	वापस err;
पूर्ण

अटल पूर्णांक sun8i_ss_handle_cipher_request(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	पूर्णांक err;
	काष्ठा skcipher_request *breq = container_of(areq, काष्ठा skcipher_request, base);

	err = sun8i_ss_cipher(breq);
	crypto_finalize_skcipher_request(engine, breq, err);

	वापस 0;
पूर्ण

पूर्णांक sun8i_ss_skdecrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा crypto_engine *engine;
	पूर्णांक e;

	स_रखो(rctx, 0, माप(काष्ठा sun8i_cipher_req_ctx));
	rctx->op_dir = SS_DECRYPTION;

	अगर (sun8i_ss_need_fallback(areq))
		वापस sun8i_ss_cipher_fallback(areq);

	e = sun8i_ss_get_engine_number(op->ss);
	engine = op->ss->flows[e].engine;
	rctx->flow = e;

	वापस crypto_transfer_skcipher_request_to_engine(engine, areq);
पूर्ण

पूर्णांक sun8i_ss_skencrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा crypto_engine *engine;
	पूर्णांक e;

	स_रखो(rctx, 0, माप(काष्ठा sun8i_cipher_req_ctx));
	rctx->op_dir = SS_ENCRYPTION;

	अगर (sun8i_ss_need_fallback(areq))
		वापस sun8i_ss_cipher_fallback(areq);

	e = sun8i_ss_get_engine_number(op->ss);
	engine = op->ss->flows[e].engine;
	rctx->flow = e;

	वापस crypto_transfer_skcipher_request_to_engine(engine, areq);
पूर्ण

पूर्णांक sun8i_ss_cipher_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
	स्थिर अक्षर *name = crypto_tfm_alg_name(tfm);
	काष्ठा crypto_skcipher *sktfm = __crypto_skcipher_cast(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(sktfm);
	पूर्णांक err;

	स_रखो(op, 0, माप(काष्ठा sun8i_cipher_tfm_ctx));

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.skcipher);
	op->ss = algt->ss;

	op->fallback_tfm = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(op->fallback_tfm)) अणु
		dev_err(op->ss->dev, "ERROR: Cannot allocate fallback for %s %ld\n",
			name, PTR_ERR(op->fallback_tfm));
		वापस PTR_ERR(op->fallback_tfm);
	पूर्ण

	sktfm->reqsize = माप(काष्ठा sun8i_cipher_req_ctx) +
			 crypto_skcipher_reqsize(op->fallback_tfm);


	dev_info(op->ss->dev, "Fallback for %s is %s\n",
		 crypto_tfm_alg_driver_name(&sktfm->base),
		 crypto_tfm_alg_driver_name(crypto_skcipher_tfm(op->fallback_tfm)));

	op->enginectx.op.करो_one_request = sun8i_ss_handle_cipher_request;
	op->enginectx.op.prepare_request = शून्य;
	op->enginectx.op.unprepare_request = शून्य;

	err = pm_runसमय_resume_and_get(op->ss->dev);
	अगर (err < 0) अणु
		dev_err(op->ss->dev, "pm error %d\n", err);
		जाओ error_pm;
	पूर्ण

	वापस 0;
error_pm:
	crypto_मुक्त_skcipher(op->fallback_tfm);
	वापस err;
पूर्ण

व्योम sun8i_ss_cipher_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_tfm_ctx(tfm);

	kमुक्त_sensitive(op->key);
	crypto_मुक्त_skcipher(op->fallback_tfm);
	pm_runसमय_put_sync(op->ss->dev);
पूर्ण

पूर्णांक sun8i_ss_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ss_dev *ss = op->ss;

	चयन (keylen) अणु
	हाल 128 / 8:
		अवरोध;
	हाल 192 / 8:
		अवरोध;
	हाल 256 / 8:
		अवरोध;
	शेष:
		dev_dbg(ss->dev, "ERROR: Invalid keylen %u\n", keylen);
		वापस -EINVAL;
	पूर्ण
	kमुक्त_sensitive(op->key);
	op->keylen = keylen;
	op->key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
	अगर (!op->key)
		वापस -ENOMEM;

	crypto_skcipher_clear_flags(op->fallback_tfm, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(op->fallback_tfm, tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण

पूर्णांक sun8i_ss_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ss_dev *ss = op->ss;

	अगर (unlikely(keylen != 3 * DES_KEY_SIZE)) अणु
		dev_dbg(ss->dev, "Invalid keylen %u\n", keylen);
		वापस -EINVAL;
	पूर्ण

	kमुक्त_sensitive(op->key);
	op->keylen = keylen;
	op->key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
	अगर (!op->key)
		वापस -ENOMEM;

	crypto_skcipher_clear_flags(op->fallback_tfm, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(op->fallback_tfm, tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण
