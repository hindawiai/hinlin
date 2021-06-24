<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * amlogic-cipher.c - hardware cryptographic offloader क्रम Amlogic GXL SoC
 *
 * Copyright (C) 2018-2019 Corentin LABBE <clabbe@baylibre.com>
 *
 * This file add support क्रम AES cipher with 128,192,256 bits keysize in
 * CBC and ECB mode.
 */

#समावेश <linux/crypto.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "amlogic-gxl.h"

अटल पूर्णांक get_engine_number(काष्ठा meson_dev *mc)
अणु
	वापस atomic_inc_वापस(&mc->flow) % MAXFLOW;
पूर्ण

अटल bool meson_cipher_need_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा scatterlist *src_sg = areq->src;
	काष्ठा scatterlist *dst_sg = areq->dst;

	अगर (areq->cryptlen == 0)
		वापस true;

	अगर (sg_nents(src_sg) != sg_nents(dst_sg))
		वापस true;

	/* KEY/IV descriptors use 3 desc */
	अगर (sg_nents(src_sg) > MAXDESC - 3 || sg_nents(dst_sg) > MAXDESC - 3)
		वापस true;

	जबतक (src_sg && dst_sg) अणु
		अगर ((src_sg->length % 16) != 0)
			वापस true;
		अगर ((dst_sg->length % 16) != 0)
			वापस true;
		अगर (src_sg->length != dst_sg->length)
			वापस true;
		अगर (!IS_ALIGNED(src_sg->offset, माप(u32)))
			वापस true;
		अगर (!IS_ALIGNED(dst_sg->offset, माप(u32)))
			वापस true;
		src_sg = sg_next(src_sg);
		dst_sg = sg_next(dst_sg);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक meson_cipher_करो_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा meson_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा meson_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	पूर्णांक err;
#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा meson_alg_ढाँचा *algt;

	algt = container_of(alg, काष्ठा meson_alg_ढाँचा, alg.skcipher);
	algt->stat_fb++;
#पूर्ण_अगर
	skcipher_request_set_tfm(&rctx->fallback_req, op->fallback_tfm);
	skcipher_request_set_callback(&rctx->fallback_req, areq->base.flags,
				      areq->base.complete, areq->base.data);
	skcipher_request_set_crypt(&rctx->fallback_req, areq->src, areq->dst,
				   areq->cryptlen, areq->iv);

	अगर (rctx->op_dir == MESON_DECRYPT)
		err = crypto_skcipher_decrypt(&rctx->fallback_req);
	अन्यथा
		err = crypto_skcipher_encrypt(&rctx->fallback_req);
	वापस err;
पूर्ण

अटल पूर्णांक meson_cipher(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा meson_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा meson_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा meson_dev *mc = op->mc;
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा meson_alg_ढाँचा *algt;
	पूर्णांक flow = rctx->flow;
	अचिन्हित पूर्णांक toकरो, eat, len;
	काष्ठा scatterlist *src_sg = areq->src;
	काष्ठा scatterlist *dst_sg = areq->dst;
	काष्ठा meson_desc *desc;
	पूर्णांक nr_sgs, nr_sgd;
	पूर्णांक i, err = 0;
	अचिन्हित पूर्णांक keyivlen, ivsize, offset, tloffset;
	dma_addr_t phykeyiv;
	व्योम *backup_iv = शून्य, *bkeyiv;
	u32 v;

	algt = container_of(alg, काष्ठा meson_alg_ढाँचा, alg.skcipher);

	dev_dbg(mc->dev, "%s %s %u %x IV(%u) key=%u flow=%d\n", __func__,
		crypto_tfm_alg_name(areq->base.tfm),
		areq->cryptlen,
		rctx->op_dir, crypto_skcipher_ivsize(tfm),
		op->keylen, flow);

#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	algt->stat_req++;
	mc->chanlist[flow].stat_req++;
#पूर्ण_अगर

	/*
	 * The hardware expect a list of meson_desc काष्ठाures.
	 * The 2 first काष्ठाures store key
	 * The third stores IV
	 */
	bkeyiv = kzalloc(48, GFP_KERNEL | GFP_DMA);
	अगर (!bkeyiv)
		वापस -ENOMEM;

	स_नकल(bkeyiv, op->key, op->keylen);
	keyivlen = op->keylen;

	ivsize = crypto_skcipher_ivsize(tfm);
	अगर (areq->iv && ivsize > 0) अणु
		अगर (ivsize > areq->cryptlen) अणु
			dev_err(mc->dev, "invalid ivsize=%d vs len=%d\n", ivsize, areq->cryptlen);
			err = -EINVAL;
			जाओ theend;
		पूर्ण
		स_नकल(bkeyiv + 32, areq->iv, ivsize);
		keyivlen = 48;
		अगर (rctx->op_dir == MESON_DECRYPT) अणु
			backup_iv = kzalloc(ivsize, GFP_KERNEL);
			अगर (!backup_iv) अणु
				err = -ENOMEM;
				जाओ theend;
			पूर्ण
			offset = areq->cryptlen - ivsize;
			scatterwalk_map_and_copy(backup_iv, areq->src, offset,
						 ivsize, 0);
		पूर्ण
	पूर्ण
	अगर (keyivlen == 24)
		keyivlen = 32;

	phykeyiv = dma_map_single(mc->dev, bkeyiv, keyivlen,
				  DMA_TO_DEVICE);
	err = dma_mapping_error(mc->dev, phykeyiv);
	अगर (err) अणु
		dev_err(mc->dev, "Cannot DMA MAP KEY IV\n");
		जाओ theend;
	पूर्ण

	tloffset = 0;
	eat = 0;
	i = 0;
	जबतक (keyivlen > eat) अणु
		desc = &mc->chanlist[flow].tl[tloffset];
		स_रखो(desc, 0, माप(काष्ठा meson_desc));
		toकरो = min(keyivlen - eat, 16u);
		desc->t_src = cpu_to_le32(phykeyiv + i * 16);
		desc->t_dst = cpu_to_le32(i * 16);
		v = (MODE_KEY << 20) | DESC_OWN | 16;
		desc->t_status = cpu_to_le32(v);

		eat += toकरो;
		i++;
		tloffset++;
	पूर्ण

	अगर (areq->src == areq->dst) अणु
		nr_sgs = dma_map_sg(mc->dev, areq->src, sg_nents(areq->src),
				    DMA_BIसूचीECTIONAL);
		अगर (nr_sgs < 0) अणु
			dev_err(mc->dev, "Invalid SG count %d\n", nr_sgs);
			err = -EINVAL;
			जाओ theend;
		पूर्ण
		nr_sgd = nr_sgs;
	पूर्ण अन्यथा अणु
		nr_sgs = dma_map_sg(mc->dev, areq->src, sg_nents(areq->src),
				    DMA_TO_DEVICE);
		अगर (nr_sgs < 0 || nr_sgs > MAXDESC - 3) अणु
			dev_err(mc->dev, "Invalid SG count %d\n", nr_sgs);
			err = -EINVAL;
			जाओ theend;
		पूर्ण
		nr_sgd = dma_map_sg(mc->dev, areq->dst, sg_nents(areq->dst),
				    DMA_FROM_DEVICE);
		अगर (nr_sgd < 0 || nr_sgd > MAXDESC - 3) अणु
			dev_err(mc->dev, "Invalid SG count %d\n", nr_sgd);
			err = -EINVAL;
			जाओ theend;
		पूर्ण
	पूर्ण

	src_sg = areq->src;
	dst_sg = areq->dst;
	len = areq->cryptlen;
	जबतक (src_sg) अणु
		desc = &mc->chanlist[flow].tl[tloffset];
		स_रखो(desc, 0, माप(काष्ठा meson_desc));

		desc->t_src = cpu_to_le32(sg_dma_address(src_sg));
		desc->t_dst = cpu_to_le32(sg_dma_address(dst_sg));
		toकरो = min(len, sg_dma_len(src_sg));
		v = (op->keymode << 20) | DESC_OWN | toकरो | (algt->blockmode << 26);
		अगर (rctx->op_dir)
			v |= DESC_ENCRYPTION;
		len -= toकरो;

		अगर (!sg_next(src_sg))
			v |= DESC_LAST;
		desc->t_status = cpu_to_le32(v);
		tloffset++;
		src_sg = sg_next(src_sg);
		dst_sg = sg_next(dst_sg);
	पूर्ण

	reinit_completion(&mc->chanlist[flow].complete);
	mc->chanlist[flow].status = 0;
	ग_लिखोl(mc->chanlist[flow].t_phy | 2, mc->base + (flow << 2));
	रुको_क्रम_completion_पूर्णांकerruptible_समयout(&mc->chanlist[flow].complete,
						  msecs_to_jअगरfies(500));
	अगर (mc->chanlist[flow].status == 0) अणु
		dev_err(mc->dev, "DMA timeout for flow %d\n", flow);
		err = -EINVAL;
	पूर्ण

	dma_unmap_single(mc->dev, phykeyiv, keyivlen, DMA_TO_DEVICE);

	अगर (areq->src == areq->dst) अणु
		dma_unmap_sg(mc->dev, areq->src, sg_nents(areq->src), DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(mc->dev, areq->src, sg_nents(areq->src), DMA_TO_DEVICE);
		dma_unmap_sg(mc->dev, areq->dst, sg_nents(areq->dst), DMA_FROM_DEVICE);
	पूर्ण

	अगर (areq->iv && ivsize > 0) अणु
		अगर (rctx->op_dir == MESON_DECRYPT) अणु
			स_नकल(areq->iv, backup_iv, ivsize);
		पूर्ण अन्यथा अणु
			scatterwalk_map_and_copy(areq->iv, areq->dst,
						 areq->cryptlen - ivsize,
						 ivsize, 0);
		पूर्ण
	पूर्ण
theend:
	kमुक्त_sensitive(bkeyiv);
	kमुक्त_sensitive(backup_iv);

	वापस err;
पूर्ण

अटल पूर्णांक meson_handle_cipher_request(काष्ठा crypto_engine *engine,
				       व्योम *areq)
अणु
	पूर्णांक err;
	काष्ठा skcipher_request *breq = container_of(areq, काष्ठा skcipher_request, base);

	err = meson_cipher(breq);
	crypto_finalize_skcipher_request(engine, breq, err);

	वापस 0;
पूर्ण

पूर्णांक meson_skdecrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा meson_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा meson_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा crypto_engine *engine;
	पूर्णांक e;

	rctx->op_dir = MESON_DECRYPT;
	अगर (meson_cipher_need_fallback(areq))
		वापस meson_cipher_करो_fallback(areq);
	e = get_engine_number(op->mc);
	engine = op->mc->chanlist[e].engine;
	rctx->flow = e;

	वापस crypto_transfer_skcipher_request_to_engine(engine, areq);
पूर्ण

पूर्णांक meson_skencrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा meson_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा meson_cipher_req_ctx *rctx = skcipher_request_ctx(areq);
	काष्ठा crypto_engine *engine;
	पूर्णांक e;

	rctx->op_dir = MESON_ENCRYPT;
	अगर (meson_cipher_need_fallback(areq))
		वापस meson_cipher_करो_fallback(areq);
	e = get_engine_number(op->mc);
	engine = op->mc->chanlist[e].engine;
	rctx->flow = e;

	वापस crypto_transfer_skcipher_request_to_engine(engine, areq);
पूर्ण

पूर्णांक meson_cipher_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा meson_cipher_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा meson_alg_ढाँचा *algt;
	स्थिर अक्षर *name = crypto_tfm_alg_name(tfm);
	काष्ठा crypto_skcipher *sktfm = __crypto_skcipher_cast(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(sktfm);

	स_रखो(op, 0, माप(काष्ठा meson_cipher_tfm_ctx));

	algt = container_of(alg, काष्ठा meson_alg_ढाँचा, alg.skcipher);
	op->mc = algt->mc;

	op->fallback_tfm = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(op->fallback_tfm)) अणु
		dev_err(op->mc->dev, "ERROR: Cannot allocate fallback for %s %ld\n",
			name, PTR_ERR(op->fallback_tfm));
		वापस PTR_ERR(op->fallback_tfm);
	पूर्ण

	sktfm->reqsize = माप(काष्ठा meson_cipher_req_ctx) +
			 crypto_skcipher_reqsize(op->fallback_tfm);

	op->enginectx.op.करो_one_request = meson_handle_cipher_request;
	op->enginectx.op.prepare_request = शून्य;
	op->enginectx.op.unprepare_request = शून्य;

	वापस 0;
पूर्ण

व्योम meson_cipher_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा meson_cipher_tfm_ctx *op = crypto_tfm_ctx(tfm);

	kमुक्त_sensitive(op->key);
	crypto_मुक्त_skcipher(op->fallback_tfm);
पूर्ण

पूर्णांक meson_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
		     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा meson_cipher_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा meson_dev *mc = op->mc;

	चयन (keylen) अणु
	हाल 128 / 8:
		op->keymode = MODE_AES_128;
		अवरोध;
	हाल 192 / 8:
		op->keymode = MODE_AES_192;
		अवरोध;
	हाल 256 / 8:
		op->keymode = MODE_AES_256;
		अवरोध;
	शेष:
		dev_dbg(mc->dev, "ERROR: Invalid keylen %u\n", keylen);
		वापस -EINVAL;
	पूर्ण
	kमुक्त_sensitive(op->key);
	op->keylen = keylen;
	op->key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
	अगर (!op->key)
		वापस -ENOMEM;

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण
