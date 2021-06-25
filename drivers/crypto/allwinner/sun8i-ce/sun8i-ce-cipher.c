<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ce-cipher.c - hardware cryptographic offloader क्रम
 * Allwinner H3/A64/H5/H2+/H6/R40 SoC
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
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "sun8i-ce.h"

अटल पूर्णांक sun8i_ce_cipher_need_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा scatterlist *sg;

	अगर (sg_nents(areq->src) > MAX_SG || sg_nents(areq->dst) > MAX_SG)
		वापस true;

	अगर (areq->cryptlen < crypto_skcipher_ivsize(tfm))
		वापस true;

	अगर (areq->cryptlen == 0 || areq->cryptlen % 16)
		वापस true;

	sg = areq->src;
	जबतक (sg) अणु
		अगर (sg->length % 4 || !IS_ALIGNED(sg->offset, माप(u32)))
			वापस true;
		sg = sg_next(sg);
	पूर्ण
	sg = areq->dst;
	जबतक (sg) अणु
		अगर (sg->length % 4 || !IS_ALIGNED(sg->offset, माप(u32)))
			वापस true;
		sg = sg_next(sg);
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक sun8i_ce_cipher_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	पूर्णांक err;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.skcipher);
	algt->stat_fb++;
#पूर्ण_अगर

	skcipher_request_set_tfm(&rctx->fallback_req, op->fallback_tfm);
	skcipher_request_set_callback(&rctx->fallback_req, areq->base.flags,
				      areq->base.complete, areq->base.data);
	skcipher_request_set_crypt(&rctx->fallback_req, areq->src, areq->dst,
				   areq->cryptlen, areq->iv);
	अगर (rctx->op_dir & CE_DECRYPTION)
		err = crypto_skcipher_decrypt(&rctx->fallback_req);
	अन्यथा
		err = crypto_skcipher_encrypt(&rctx->fallback_req);
	वापस err;
पूर्ण

अटल पूर्णांक sun8i_ce_cipher_prepare(काष्ठा crypto_engine *engine, व्योम *async_req)
अणु
	काष्ठा skcipher_request *areq = container_of(async_req, काष्ठा skcipher_request, base);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ce_dev *ce = op->ce;
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
	काष्ठा sun8i_ce_flow *chan;
	काष्ठा ce_task *cet;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक toकरो, len, offset, ivsize;
	u32 common, sym;
	पूर्णांक flow, i;
	पूर्णांक nr_sgs = 0;
	पूर्णांक nr_sgd = 0;
	पूर्णांक err = 0;

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.skcipher);

	dev_dbg(ce->dev, "%s %s %u %x IV(%p %u) key=%u\n", __func__,
		crypto_tfm_alg_name(areq->base.tfm),
		areq->cryptlen,
		rctx->op_dir, areq->iv, crypto_skcipher_ivsize(tfm),
		op->keylen);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	algt->stat_req++;
#पूर्ण_अगर

	flow = rctx->flow;

	chan = &ce->chanlist[flow];

	cet = chan->tl;
	स_रखो(cet, 0, माप(काष्ठा ce_task));

	cet->t_id = cpu_to_le32(flow);
	common = ce->variant->alg_cipher[algt->ce_algo_id];
	common |= rctx->op_dir | CE_COMM_INT;
	cet->t_common_ctl = cpu_to_le32(common);
	/* CTS and recent CE (H6) need length in bytes, in word otherwise */
	अगर (ce->variant->cipher_t_dlen_in_bytes)
		cet->t_dlen = cpu_to_le32(areq->cryptlen);
	अन्यथा
		cet->t_dlen = cpu_to_le32(areq->cryptlen / 4);

	sym = ce->variant->op_mode[algt->ce_blockmode];
	len = op->keylen;
	चयन (len) अणु
	हाल 128 / 8:
		sym |= CE_AES_128BITS;
		अवरोध;
	हाल 192 / 8:
		sym |= CE_AES_192BITS;
		अवरोध;
	हाल 256 / 8:
		sym |= CE_AES_256BITS;
		अवरोध;
	पूर्ण

	cet->t_sym_ctl = cpu_to_le32(sym);
	cet->t_asym_ctl = 0;

	rctx->addr_key = dma_map_single(ce->dev, op->key, op->keylen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ce->dev, rctx->addr_key)) अणु
		dev_err(ce->dev, "Cannot DMA MAP KEY\n");
		err = -EFAULT;
		जाओ theend;
	पूर्ण
	cet->t_key = cpu_to_le32(rctx->addr_key);

	ivsize = crypto_skcipher_ivsize(tfm);
	अगर (areq->iv && crypto_skcipher_ivsize(tfm) > 0) अणु
		rctx->ivlen = ivsize;
		rctx->bounce_iv = kzalloc(ivsize, GFP_KERNEL | GFP_DMA);
		अगर (!rctx->bounce_iv) अणु
			err = -ENOMEM;
			जाओ theend_key;
		पूर्ण
		अगर (rctx->op_dir & CE_DECRYPTION) अणु
			rctx->backup_iv = kzalloc(ivsize, GFP_KERNEL);
			अगर (!rctx->backup_iv) अणु
				err = -ENOMEM;
				जाओ theend_key;
			पूर्ण
			offset = areq->cryptlen - ivsize;
			scatterwalk_map_and_copy(rctx->backup_iv, areq->src,
						 offset, ivsize, 0);
		पूर्ण
		स_नकल(rctx->bounce_iv, areq->iv, ivsize);
		rctx->addr_iv = dma_map_single(ce->dev, rctx->bounce_iv, rctx->ivlen,
					       DMA_TO_DEVICE);
		अगर (dma_mapping_error(ce->dev, rctx->addr_iv)) अणु
			dev_err(ce->dev, "Cannot DMA MAP IV\n");
			err = -ENOMEM;
			जाओ theend_iv;
		पूर्ण
		cet->t_iv = cpu_to_le32(rctx->addr_iv);
	पूर्ण

	अगर (areq->src == areq->dst) अणु
		nr_sgs = dma_map_sg(ce->dev, areq->src, sg_nents(areq->src),
				    DMA_BIसूचीECTIONAL);
		अगर (nr_sgs <= 0 || nr_sgs > MAX_SG) अणु
			dev_err(ce->dev, "Invalid sg number %d\n", nr_sgs);
			err = -EINVAL;
			जाओ theend_iv;
		पूर्ण
		nr_sgd = nr_sgs;
	पूर्ण अन्यथा अणु
		nr_sgs = dma_map_sg(ce->dev, areq->src, sg_nents(areq->src),
				    DMA_TO_DEVICE);
		अगर (nr_sgs <= 0 || nr_sgs > MAX_SG) अणु
			dev_err(ce->dev, "Invalid sg number %d\n", nr_sgs);
			err = -EINVAL;
			जाओ theend_iv;
		पूर्ण
		nr_sgd = dma_map_sg(ce->dev, areq->dst, sg_nents(areq->dst),
				    DMA_FROM_DEVICE);
		अगर (nr_sgd <= 0 || nr_sgd > MAX_SG) अणु
			dev_err(ce->dev, "Invalid sg number %d\n", nr_sgd);
			err = -EINVAL;
			जाओ theend_sgs;
		पूर्ण
	पूर्ण

	len = areq->cryptlen;
	क्रम_each_sg(areq->src, sg, nr_sgs, i) अणु
		cet->t_src[i].addr = cpu_to_le32(sg_dma_address(sg));
		toकरो = min(len, sg_dma_len(sg));
		cet->t_src[i].len = cpu_to_le32(toकरो / 4);
		dev_dbg(ce->dev, "%s total=%u SG(%d %u off=%d) todo=%u\n", __func__,
			areq->cryptlen, i, cet->t_src[i].len, sg->offset, toकरो);
		len -= toकरो;
	पूर्ण
	अगर (len > 0) अणु
		dev_err(ce->dev, "remaining len %d\n", len);
		err = -EINVAL;
		जाओ theend_sgs;
	पूर्ण

	len = areq->cryptlen;
	क्रम_each_sg(areq->dst, sg, nr_sgd, i) अणु
		cet->t_dst[i].addr = cpu_to_le32(sg_dma_address(sg));
		toकरो = min(len, sg_dma_len(sg));
		cet->t_dst[i].len = cpu_to_le32(toकरो / 4);
		dev_dbg(ce->dev, "%s total=%u SG(%d %u off=%d) todo=%u\n", __func__,
			areq->cryptlen, i, cet->t_dst[i].len, sg->offset, toकरो);
		len -= toकरो;
	पूर्ण
	अगर (len > 0) अणु
		dev_err(ce->dev, "remaining len %d\n", len);
		err = -EINVAL;
		जाओ theend_sgs;
	पूर्ण

	chan->समयout = areq->cryptlen;
	rctx->nr_sgs = nr_sgs;
	rctx->nr_sgd = nr_sgd;
	वापस 0;

theend_sgs:
	अगर (areq->src == areq->dst) अणु
		dma_unmap_sg(ce->dev, areq->src, sg_nents(areq->src),
			     DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		अगर (nr_sgs > 0)
			dma_unmap_sg(ce->dev, areq->src, sg_nents(areq->src),
				     DMA_TO_DEVICE);
		dma_unmap_sg(ce->dev, areq->dst, sg_nents(areq->dst),
			     DMA_FROM_DEVICE);
	पूर्ण

theend_iv:
	अगर (areq->iv && ivsize > 0) अणु
		अगर (rctx->addr_iv)
			dma_unmap_single(ce->dev, rctx->addr_iv, rctx->ivlen, DMA_TO_DEVICE);
		offset = areq->cryptlen - ivsize;
		अगर (rctx->op_dir & CE_DECRYPTION) अणु
			स_नकल(areq->iv, rctx->backup_iv, ivsize);
			kमुक्त_sensitive(rctx->backup_iv);
		पूर्ण अन्यथा अणु
			scatterwalk_map_and_copy(areq->iv, areq->dst, offset,
						 ivsize, 0);
		पूर्ण
		kमुक्त(rctx->bounce_iv);
	पूर्ण

theend_key:
	dma_unmap_single(ce->dev, rctx->addr_key, op->keylen, DMA_TO_DEVICE);

theend:
	वापस err;
पूर्ण

अटल पूर्णांक sun8i_ce_cipher_run(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा skcipher_request *breq = container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(breq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ce_dev *ce = op->ce;
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(breq);
	पूर्णांक flow, err;

	flow = rctx->flow;
	err = sun8i_ce_run_task(ce, flow, crypto_tfm_alg_name(breq->base.tfm));
	crypto_finalize_skcipher_request(engine, breq, err);
	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ce_cipher_unprepare(काष्ठा crypto_engine *engine, व्योम *async_req)
अणु
	काष्ठा skcipher_request *areq = container_of(async_req, काष्ठा skcipher_request, base);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ce_dev *ce = op->ce;
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा sun8i_ce_flow *chan;
	काष्ठा ce_task *cet;
	अचिन्हित पूर्णांक ivsize, offset;
	पूर्णांक nr_sgs = rctx->nr_sgs;
	पूर्णांक nr_sgd = rctx->nr_sgd;
	पूर्णांक flow;

	flow = rctx->flow;
	chan = &ce->chanlist[flow];
	cet = chan->tl;
	ivsize = crypto_skcipher_ivsize(tfm);

	अगर (areq->src == areq->dst) अणु
		dma_unmap_sg(ce->dev, areq->src, nr_sgs, DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		अगर (nr_sgs > 0)
			dma_unmap_sg(ce->dev, areq->src, nr_sgs, DMA_TO_DEVICE);
		dma_unmap_sg(ce->dev, areq->dst, nr_sgd, DMA_FROM_DEVICE);
	पूर्ण

	अगर (areq->iv && ivsize > 0) अणु
		अगर (cet->t_iv)
			dma_unmap_single(ce->dev, rctx->addr_iv, rctx->ivlen, DMA_TO_DEVICE);
		offset = areq->cryptlen - ivsize;
		अगर (rctx->op_dir & CE_DECRYPTION) अणु
			स_नकल(areq->iv, rctx->backup_iv, ivsize);
			kमुक्त_sensitive(rctx->backup_iv);
		पूर्ण अन्यथा अणु
			scatterwalk_map_and_copy(areq->iv, areq->dst, offset,
						 ivsize, 0);
		पूर्ण
		kमुक्त(rctx->bounce_iv);
	पूर्ण

	dma_unmap_single(ce->dev, rctx->addr_key, op->keylen, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

पूर्णांक sun8i_ce_skdecrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा crypto_engine *engine;
	पूर्णांक e;

	rctx->op_dir = CE_DECRYPTION;
	अगर (sun8i_ce_cipher_need_fallback(areq))
		वापस sun8i_ce_cipher_fallback(areq);

	e = sun8i_ce_get_engine_number(op->ce);
	rctx->flow = e;
	engine = op->ce->chanlist[e].engine;

	वापस crypto_transfer_skcipher_request_to_engine(engine, areq);
पूर्ण

पूर्णांक sun8i_ce_skencrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा crypto_engine *engine;
	पूर्णांक e;

	rctx->op_dir = CE_ENCRYPTION;
	अगर (sun8i_ce_cipher_need_fallback(areq))
		वापस sun8i_ce_cipher_fallback(areq);

	e = sun8i_ce_get_engine_number(op->ce);
	rctx->flow = e;
	engine = op->ce->chanlist[e].engine;

	वापस crypto_transfer_skcipher_request_to_engine(engine, areq);
पूर्ण

पूर्णांक sun8i_ce_cipher_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
	स्थिर अक्षर *name = crypto_tfm_alg_name(tfm);
	काष्ठा crypto_skcipher *sktfm = __crypto_skcipher_cast(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(sktfm);
	पूर्णांक err;

	स_रखो(op, 0, माप(काष्ठा sun8i_cipher_tfm_ctx));

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.skcipher);
	op->ce = algt->ce;

	op->fallback_tfm = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(op->fallback_tfm)) अणु
		dev_err(op->ce->dev, "ERROR: Cannot allocate fallback for %s %ld\n",
			name, PTR_ERR(op->fallback_tfm));
		वापस PTR_ERR(op->fallback_tfm);
	पूर्ण

	sktfm->reqsize = माप(काष्ठा sun8i_cipher_req_ctx) +
			 crypto_skcipher_reqsize(op->fallback_tfm);


	dev_info(op->ce->dev, "Fallback for %s is %s\n",
		 crypto_tfm_alg_driver_name(&sktfm->base),
		 crypto_tfm_alg_driver_name(crypto_skcipher_tfm(op->fallback_tfm)));

	op->enginectx.op.करो_one_request = sun8i_ce_cipher_run;
	op->enginectx.op.prepare_request = sun8i_ce_cipher_prepare;
	op->enginectx.op.unprepare_request = sun8i_ce_cipher_unprepare;

	err = pm_runसमय_get_sync(op->ce->dev);
	अगर (err < 0)
		जाओ error_pm;

	वापस 0;
error_pm:
	pm_runसमय_put_noidle(op->ce->dev);
	crypto_मुक्त_skcipher(op->fallback_tfm);
	वापस err;
पूर्ण

व्योम sun8i_ce_cipher_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_tfm_ctx(tfm);

	kमुक्त_sensitive(op->key);
	crypto_मुक्त_skcipher(op->fallback_tfm);
	pm_runसमय_put_sync_suspend(op->ce->dev);
पूर्ण

पूर्णांक sun8i_ce_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun8i_ce_dev *ce = op->ce;

	चयन (keylen) अणु
	हाल 128 / 8:
		अवरोध;
	हाल 192 / 8:
		अवरोध;
	हाल 256 / 8:
		अवरोध;
	शेष:
		dev_dbg(ce->dev, "ERROR: Invalid keylen %u\n", keylen);
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

पूर्णांक sun8i_ce_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun8i_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(tfm, key);
	अगर (err)
		वापस err;

	kमुक्त_sensitive(op->key);
	op->keylen = keylen;
	op->key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
	अगर (!op->key)
		वापस -ENOMEM;

	crypto_skcipher_clear_flags(op->fallback_tfm, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(op->fallback_tfm, tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण
