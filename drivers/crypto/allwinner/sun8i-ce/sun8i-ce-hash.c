<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ce-hash.c - hardware cryptographic offloader क्रम
 * Allwinner H3/A64/H5/H2+/H6/R40 SoC
 *
 * Copyright (C) 2015-2020 Corentin Labbe <clabbe@baylibre.com>
 *
 * This file add support क्रम MD5 and SHA1/SHA224/SHA256/SHA384/SHA512.
 *
 * You could find the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/md5.h>
#समावेश "sun8i-ce.h"

पूर्णांक sun8i_ce_hash_crainit(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ce_hash_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->__crt_alg);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
	पूर्णांक err;

	स_रखो(op, 0, माप(काष्ठा sun8i_ce_hash_tfm_ctx));

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.hash);
	op->ce = algt->ce;

	op->enginectx.op.करो_one_request = sun8i_ce_hash_run;
	op->enginectx.op.prepare_request = शून्य;
	op->enginectx.op.unprepare_request = शून्य;

	/* FALLBACK */
	op->fallback_tfm = crypto_alloc_ahash(crypto_tfm_alg_name(tfm), 0,
					      CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(op->fallback_tfm)) अणु
		dev_err(algt->ce->dev, "Fallback driver could no be loaded\n");
		वापस PTR_ERR(op->fallback_tfm);
	पूर्ण

	अगर (algt->alg.hash.halg.statesize < crypto_ahash_statesize(op->fallback_tfm))
		algt->alg.hash.halg.statesize = crypto_ahash_statesize(op->fallback_tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा sun8i_ce_hash_reqctx) +
				 crypto_ahash_reqsize(op->fallback_tfm));

	dev_info(op->ce->dev, "Fallback for %s is %s\n",
		 crypto_tfm_alg_driver_name(tfm),
		 crypto_tfm_alg_driver_name(&op->fallback_tfm->base));
	err = pm_runसमय_get_sync(op->ce->dev);
	अगर (err < 0)
		जाओ error_pm;
	वापस 0;
error_pm:
	pm_runसमय_put_noidle(op->ce->dev);
	crypto_मुक्त_ahash(op->fallback_tfm);
	वापस err;
पूर्ण

व्योम sun8i_ce_hash_craनिकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_ahash(tfmctx->fallback_tfm);
	pm_runसमय_put_sync_suspend(tfmctx->ce->dev);
पूर्ण

पूर्णांक sun8i_ce_hash_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	स_रखो(rctx, 0, माप(काष्ठा sun8i_ce_hash_reqctx));

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_init(&rctx->fallback_req);
पूर्ण

पूर्णांक sun8i_ce_hash_export(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_export(&rctx->fallback_req, out);
पूर्ण

पूर्णांक sun8i_ce_hash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_import(&rctx->fallback_req, in);
पूर्ण

पूर्णांक sun8i_ce_hash_final(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
#पूर्ण_अगर

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.result = areq->result;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.hash);
	algt->stat_fb++;
#पूर्ण_अगर

	वापस crypto_ahash_final(&rctx->fallback_req);
पूर्ण

पूर्णांक sun8i_ce_hash_update(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = areq->nbytes;
	rctx->fallback_req.src = areq->src;

	वापस crypto_ahash_update(&rctx->fallback_req);
पूर्ण

पूर्णांक sun8i_ce_hash_finup(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
#पूर्ण_अगर

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	rctx->fallback_req.nbytes = areq->nbytes;
	rctx->fallback_req.src = areq->src;
	rctx->fallback_req.result = areq->result;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.hash);
	algt->stat_fb++;
#पूर्ण_अगर

	वापस crypto_ahash_finup(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sun8i_ce_hash_digest_fb(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ce_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
#पूर्ण_अगर

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	rctx->fallback_req.nbytes = areq->nbytes;
	rctx->fallback_req.src = areq->src;
	rctx->fallback_req.result = areq->result;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.hash);
	algt->stat_fb++;
#पूर्ण_अगर

	वापस crypto_ahash_digest(&rctx->fallback_req);
पूर्ण

अटल bool sun8i_ce_hash_need_fallback(काष्ठा ahash_request *areq)
अणु
	काष्ठा scatterlist *sg;

	अगर (areq->nbytes == 0)
		वापस true;
	/* we need to reserve one SG क्रम padding one */
	अगर (sg_nents(areq->src) > MAX_SG - 1)
		वापस true;
	sg = areq->src;
	जबतक (sg) अणु
		अगर (sg->length % 4 || !IS_ALIGNED(sg->offset, माप(u32)))
			वापस true;
		sg = sg_next(sg);
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक sun8i_ce_hash_digest(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
	काष्ठा sun8i_ce_dev *ce;
	काष्ठा crypto_engine *engine;
	काष्ठा scatterlist *sg;
	पूर्णांक nr_sgs, e, i;

	अगर (sun8i_ce_hash_need_fallback(areq))
		वापस sun8i_ce_hash_digest_fb(areq);

	nr_sgs = sg_nents(areq->src);
	अगर (nr_sgs > MAX_SG - 1)
		वापस sun8i_ce_hash_digest_fb(areq);

	क्रम_each_sg(areq->src, sg, nr_sgs, i) अणु
		अगर (sg->length % 4 || !IS_ALIGNED(sg->offset, माप(u32)))
			वापस sun8i_ce_hash_digest_fb(areq);
	पूर्ण

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.hash);
	ce = algt->ce;

	e = sun8i_ce_get_engine_number(ce);
	rctx->flow = e;
	engine = ce->chanlist[e].engine;

	वापस crypto_transfer_hash_request_to_engine(engine, areq);
पूर्ण

पूर्णांक sun8i_ce_hash_run(काष्ठा crypto_engine *engine, व्योम *breq)
अणु
	काष्ठा ahash_request *areq = container_of(breq, काष्ठा ahash_request, base);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ce_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
	काष्ठा sun8i_ce_dev *ce;
	काष्ठा sun8i_ce_flow *chan;
	काष्ठा ce_task *cet;
	काष्ठा scatterlist *sg;
	पूर्णांक nr_sgs, flow, err;
	अचिन्हित पूर्णांक len;
	u32 common;
	u64 byte_count;
	__le32 *bf;
	व्योम *buf = शून्य;
	पूर्णांक j, i, toकरो;
	पूर्णांक nbw = 0;
	u64 fill, min_fill;
	__be64 *bebits;
	__le64 *lebits;
	व्योम *result = शून्य;
	u64 bs;
	पूर्णांक digestsize;
	dma_addr_t addr_res, addr_pad;

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.hash);
	ce = algt->ce;

	bs = algt->alg.hash.halg.base.cra_blocksize;
	digestsize = algt->alg.hash.halg.digestsize;
	अगर (digestsize == SHA224_DIGEST_SIZE)
		digestsize = SHA256_DIGEST_SIZE;
	अगर (digestsize == SHA384_DIGEST_SIZE)
		digestsize = SHA512_DIGEST_SIZE;

	/* the padding could be up to two block. */
	buf = kzalloc(bs * 2, GFP_KERNEL | GFP_DMA);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ theend;
	पूर्ण
	bf = (__le32 *)buf;

	result = kzalloc(digestsize, GFP_KERNEL | GFP_DMA);
	अगर (!result) अणु
		err = -ENOMEM;
		जाओ theend;
	पूर्ण

	flow = rctx->flow;
	chan = &ce->chanlist[flow];

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	algt->stat_req++;
#पूर्ण_अगर
	dev_dbg(ce->dev, "%s %s len=%d\n", __func__, crypto_tfm_alg_name(areq->base.tfm), areq->nbytes);

	cet = chan->tl;
	स_रखो(cet, 0, माप(काष्ठा ce_task));

	cet->t_id = cpu_to_le32(flow);
	common = ce->variant->alg_hash[algt->ce_algo_id];
	common |= CE_COMM_INT;
	cet->t_common_ctl = cpu_to_le32(common);

	cet->t_sym_ctl = 0;
	cet->t_asym_ctl = 0;

	nr_sgs = dma_map_sg(ce->dev, areq->src, sg_nents(areq->src), DMA_TO_DEVICE);
	अगर (nr_sgs <= 0 || nr_sgs > MAX_SG) अणु
		dev_err(ce->dev, "Invalid sg number %d\n", nr_sgs);
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	len = areq->nbytes;
	क्रम_each_sg(areq->src, sg, nr_sgs, i) अणु
		cet->t_src[i].addr = cpu_to_le32(sg_dma_address(sg));
		toकरो = min(len, sg_dma_len(sg));
		cet->t_src[i].len = cpu_to_le32(toकरो / 4);
		len -= toकरो;
	पूर्ण
	अगर (len > 0) अणु
		dev_err(ce->dev, "remaining len %d\n", len);
		err = -EINVAL;
		जाओ theend;
	पूर्ण
	addr_res = dma_map_single(ce->dev, result, digestsize, DMA_FROM_DEVICE);
	cet->t_dst[0].addr = cpu_to_le32(addr_res);
	cet->t_dst[0].len = cpu_to_le32(digestsize / 4);
	अगर (dma_mapping_error(ce->dev, addr_res)) अणु
		dev_err(ce->dev, "DMA map dest\n");
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	byte_count = areq->nbytes;
	j = 0;
	bf[j++] = cpu_to_le32(0x80);

	अगर (bs == 64) अणु
		fill = 64 - (byte_count % 64);
		min_fill = 2 * माप(u32) + (nbw ? 0 : माप(u32));
	पूर्ण अन्यथा अणु
		fill = 128 - (byte_count % 128);
		min_fill = 4 * माप(u32) + (nbw ? 0 : माप(u32));
	पूर्ण

	अगर (fill < min_fill)
		fill += bs;

	j += (fill - min_fill) / माप(u32);

	चयन (algt->ce_algo_id) अणु
	हाल CE_ID_HASH_MD5:
		lebits = (__le64 *)&bf[j];
		*lebits = cpu_to_le64(byte_count << 3);
		j += 2;
		अवरोध;
	हाल CE_ID_HASH_SHA1:
	हाल CE_ID_HASH_SHA224:
	हाल CE_ID_HASH_SHA256:
		bebits = (__be64 *)&bf[j];
		*bebits = cpu_to_be64(byte_count << 3);
		j += 2;
		अवरोध;
	हाल CE_ID_HASH_SHA384:
	हाल CE_ID_HASH_SHA512:
		bebits = (__be64 *)&bf[j];
		*bebits = cpu_to_be64(byte_count >> 61);
		j += 2;
		bebits = (__be64 *)&bf[j];
		*bebits = cpu_to_be64(byte_count << 3);
		j += 2;
		अवरोध;
	पूर्ण

	addr_pad = dma_map_single(ce->dev, buf, j * 4, DMA_TO_DEVICE);
	cet->t_src[i].addr = cpu_to_le32(addr_pad);
	cet->t_src[i].len = cpu_to_le32(j);
	अगर (dma_mapping_error(ce->dev, addr_pad)) अणु
		dev_err(ce->dev, "DMA error on padding SG\n");
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	अगर (ce->variant->hash_t_dlen_in_bits)
		cet->t_dlen = cpu_to_le32((areq->nbytes + j * 4) * 8);
	अन्यथा
		cet->t_dlen = cpu_to_le32(areq->nbytes / 4 + j);

	chan->समयout = areq->nbytes;

	err = sun8i_ce_run_task(ce, flow, crypto_tfm_alg_name(areq->base.tfm));

	dma_unmap_single(ce->dev, addr_pad, j * 4, DMA_TO_DEVICE);
	dma_unmap_sg(ce->dev, areq->src, sg_nents(areq->src),
		     DMA_TO_DEVICE);
	dma_unmap_single(ce->dev, addr_res, digestsize, DMA_FROM_DEVICE);


	स_नकल(areq->result, result, algt->alg.hash.halg.digestsize);
theend:
	kमुक्त(buf);
	kमुक्त(result);
	crypto_finalize_hash_request(engine, breq, err);
	वापस 0;
पूर्ण
