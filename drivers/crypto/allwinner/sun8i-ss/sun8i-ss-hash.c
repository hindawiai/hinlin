<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ss-hash.c - hardware cryptographic offloader क्रम
 * Allwinner A80/A83T SoC
 *
 * Copyright (C) 2015-2020 Corentin Labbe <clabbe@baylibre.com>
 *
 * This file add support क्रम MD5 and SHA1/SHA224/SHA256.
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
#समावेश "sun8i-ss.h"

पूर्णांक sun8i_ss_hash_crainit(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ss_hash_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->__crt_alg);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
	पूर्णांक err;

	स_रखो(op, 0, माप(काष्ठा sun8i_ss_hash_tfm_ctx));

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.hash);
	op->ss = algt->ss;

	op->enginectx.op.करो_one_request = sun8i_ss_hash_run;
	op->enginectx.op.prepare_request = शून्य;
	op->enginectx.op.unprepare_request = शून्य;

	/* FALLBACK */
	op->fallback_tfm = crypto_alloc_ahash(crypto_tfm_alg_name(tfm), 0,
					      CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(op->fallback_tfm)) अणु
		dev_err(algt->ss->dev, "Fallback driver could no be loaded\n");
		वापस PTR_ERR(op->fallback_tfm);
	पूर्ण

	अगर (algt->alg.hash.halg.statesize < crypto_ahash_statesize(op->fallback_tfm))
		algt->alg.hash.halg.statesize = crypto_ahash_statesize(op->fallback_tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा sun8i_ss_hash_reqctx) +
				 crypto_ahash_reqsize(op->fallback_tfm));

	dev_info(op->ss->dev, "Fallback for %s is %s\n",
		 crypto_tfm_alg_driver_name(tfm),
		 crypto_tfm_alg_driver_name(&op->fallback_tfm->base));
	err = pm_runसमय_get_sync(op->ss->dev);
	अगर (err < 0)
		जाओ error_pm;
	वापस 0;
error_pm:
	pm_runसमय_put_noidle(op->ss->dev);
	crypto_मुक्त_ahash(op->fallback_tfm);
	वापस err;
पूर्ण

व्योम sun8i_ss_hash_craनिकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_ahash(tfmctx->fallback_tfm);
	pm_runसमय_put_sync_suspend(tfmctx->ss->dev);
पूर्ण

पूर्णांक sun8i_ss_hash_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	स_रखो(rctx, 0, माप(काष्ठा sun8i_ss_hash_reqctx));

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_init(&rctx->fallback_req);
पूर्ण

पूर्णांक sun8i_ss_hash_export(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_export(&rctx->fallback_req, out);
पूर्ण

पूर्णांक sun8i_ss_hash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_import(&rctx->fallback_req, in);
पूर्ण

पूर्णांक sun8i_ss_hash_final(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
#पूर्ण_अगर

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.result = areq->result;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.hash);
	algt->stat_fb++;
#पूर्ण_अगर

	वापस crypto_ahash_final(&rctx->fallback_req);
पूर्ण

पूर्णांक sun8i_ss_hash_update(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = areq->nbytes;
	rctx->fallback_req.src = areq->src;

	वापस crypto_ahash_update(&rctx->fallback_req);
पूर्ण

पूर्णांक sun8i_ss_hash_finup(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
#पूर्ण_अगर

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	rctx->fallback_req.nbytes = areq->nbytes;
	rctx->fallback_req.src = areq->src;
	rctx->fallback_req.result = areq->result;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.hash);
	algt->stat_fb++;
#पूर्ण_अगर

	वापस crypto_ahash_finup(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sun8i_ss_hash_digest_fb(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा sun8i_ss_hash_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
#पूर्ण_अगर

	ahash_request_set_tfm(&rctx->fallback_req, tfmctx->fallback_tfm);
	rctx->fallback_req.base.flags = areq->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	rctx->fallback_req.nbytes = areq->nbytes;
	rctx->fallback_req.src = areq->src;
	rctx->fallback_req.result = areq->result;
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.hash);
	algt->stat_fb++;
#पूर्ण_अगर

	वापस crypto_ahash_digest(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sun8i_ss_run_hash_task(काष्ठा sun8i_ss_dev *ss,
				  काष्ठा sun8i_ss_hash_reqctx *rctx,
				  स्थिर अक्षर *name)
अणु
	पूर्णांक flow = rctx->flow;
	u32 v = SS_START;
	पूर्णांक i;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	ss->flows[flow].stat_req++;
#पूर्ण_अगर

	/* choose between stream0/stream1 */
	अगर (flow)
		v |= SS_FLOW1;
	अन्यथा
		v |= SS_FLOW0;

	v |= rctx->method;

	क्रम (i = 0; i < MAX_SG; i++) अणु
		अगर (!rctx->t_dst[i].addr)
			अवरोध;

		mutex_lock(&ss->mlock);
		अगर (i > 0) अणु
			v |= BIT(17);
			ग_लिखोl(rctx->t_dst[i - 1].addr, ss->base + SS_KEY_ADR_REG);
			ग_लिखोl(rctx->t_dst[i - 1].addr, ss->base + SS_IV_ADR_REG);
		पूर्ण

		dev_dbg(ss->dev,
			"Processing SG %d on flow %d %s ctl=%x %d to %d method=%x src=%x dst=%x\n",
			i, flow, name, v,
			rctx->t_src[i].len, rctx->t_dst[i].len,
			rctx->method, rctx->t_src[i].addr, rctx->t_dst[i].addr);

		ग_लिखोl(rctx->t_src[i].addr, ss->base + SS_SRC_ADR_REG);
		ग_लिखोl(rctx->t_dst[i].addr, ss->base + SS_DST_ADR_REG);
		ग_लिखोl(rctx->t_src[i].len, ss->base + SS_LEN_ADR_REG);
		ग_लिखोl(BIT(0) | BIT(1), ss->base + SS_INT_CTL_REG);

		reinit_completion(&ss->flows[flow].complete);
		ss->flows[flow].status = 0;
		wmb();

		ग_लिखोl(v, ss->base + SS_CTL_REG);
		mutex_unlock(&ss->mlock);
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ss->flows[flow].complete,
							  msecs_to_jअगरfies(2000));
		अगर (ss->flows[flow].status == 0) अणु
			dev_err(ss->dev, "DMA timeout for %s\n", name);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool sun8i_ss_hash_need_fallback(काष्ठा ahash_request *areq)
अणु
	काष्ठा scatterlist *sg;

	अगर (areq->nbytes == 0)
		वापस true;
	/* we need to reserve one SG क्रम the padding one */
	अगर (sg_nents(areq->src) > MAX_SG - 1)
		वापस true;
	sg = areq->src;
	जबतक (sg) अणु
		/* SS can operate hash only on full block size
		 * since SS support only MD5,sha1,sha224 and sha256, blocksize
		 * is always 64
		 * TODO: handle request अगर last SG is not len%64
		 * but this will need to copy data on a new SG of size=64
		 */
		अगर (sg->length % 64 || !IS_ALIGNED(sg->offset, माप(u32)))
			वापस true;
		sg = sg_next(sg);
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक sun8i_ss_hash_digest(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
	काष्ठा sun8i_ss_dev *ss;
	काष्ठा crypto_engine *engine;
	काष्ठा scatterlist *sg;
	पूर्णांक nr_sgs, e, i;

	अगर (sun8i_ss_hash_need_fallback(areq))
		वापस sun8i_ss_hash_digest_fb(areq);

	nr_sgs = sg_nents(areq->src);
	अगर (nr_sgs > MAX_SG - 1)
		वापस sun8i_ss_hash_digest_fb(areq);

	क्रम_each_sg(areq->src, sg, nr_sgs, i) अणु
		अगर (sg->length % 4 || !IS_ALIGNED(sg->offset, माप(u32)))
			वापस sun8i_ss_hash_digest_fb(areq);
	पूर्ण

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.hash);
	ss = algt->ss;

	e = sun8i_ss_get_engine_number(ss);
	rctx->flow = e;
	engine = ss->flows[e].engine;

	वापस crypto_transfer_hash_request_to_engine(engine, areq);
पूर्ण

/* sun8i_ss_hash_run - run an ahash request
 * Send the data of the request to the SS aदीर्घ with an extra SG with padding
 */
पूर्णांक sun8i_ss_hash_run(काष्ठा crypto_engine *engine, व्योम *breq)
अणु
	काष्ठा ahash_request *areq = container_of(breq, काष्ठा ahash_request, base);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun8i_ss_hash_reqctx *rctx = ahash_request_ctx(areq);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
	काष्ठा sun8i_ss_dev *ss;
	काष्ठा scatterlist *sg;
	पूर्णांक nr_sgs, err, digestsize;
	अचिन्हित पूर्णांक len;
	u64 fill, min_fill, byte_count;
	व्योम *pad, *result;
	पूर्णांक j, i, toकरो;
	__be64 *bebits;
	__le64 *lebits;
	dma_addr_t addr_res, addr_pad;
	__le32 *bf;

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.hash);
	ss = algt->ss;

	digestsize = algt->alg.hash.halg.digestsize;
	अगर (digestsize == SHA224_DIGEST_SIZE)
		digestsize = SHA256_DIGEST_SIZE;

	/* the padding could be up to two block. */
	pad = kzalloc(algt->alg.hash.halg.base.cra_blocksize * 2, GFP_KERNEL | GFP_DMA);
	अगर (!pad)
		वापस -ENOMEM;
	bf = (__le32 *)pad;

	result = kzalloc(digestsize, GFP_KERNEL | GFP_DMA);
	अगर (!result) अणु
		kमुक्त(pad);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < MAX_SG; i++) अणु
		rctx->t_dst[i].addr = 0;
		rctx->t_dst[i].len = 0;
	पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	algt->stat_req++;
#पूर्ण_अगर

	rctx->method = ss->variant->alg_hash[algt->ss_algo_id];

	nr_sgs = dma_map_sg(ss->dev, areq->src, sg_nents(areq->src), DMA_TO_DEVICE);
	अगर (nr_sgs <= 0 || nr_sgs > MAX_SG) अणु
		dev_err(ss->dev, "Invalid sg number %d\n", nr_sgs);
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	addr_res = dma_map_single(ss->dev, result, digestsize, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ss->dev, addr_res)) अणु
		dev_err(ss->dev, "DMA map dest\n");
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	len = areq->nbytes;
	क्रम_each_sg(areq->src, sg, nr_sgs, i) अणु
		rctx->t_src[i].addr = sg_dma_address(sg);
		toकरो = min(len, sg_dma_len(sg));
		rctx->t_src[i].len = toकरो / 4;
		len -= toकरो;
		rctx->t_dst[i].addr = addr_res;
		rctx->t_dst[i].len = digestsize / 4;
	पूर्ण
	अगर (len > 0) अणु
		dev_err(ss->dev, "remaining len %d\n", len);
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	byte_count = areq->nbytes;
	j = 0;
	bf[j++] = cpu_to_le32(0x80);

	fill = 64 - (byte_count % 64);
	min_fill = 3 * माप(u32);

	अगर (fill < min_fill)
		fill += 64;

	j += (fill - min_fill) / माप(u32);

	चयन (algt->ss_algo_id) अणु
	हाल SS_ID_HASH_MD5:
		lebits = (__le64 *)&bf[j];
		*lebits = cpu_to_le64(byte_count << 3);
		j += 2;
		अवरोध;
	हाल SS_ID_HASH_SHA1:
	हाल SS_ID_HASH_SHA224:
	हाल SS_ID_HASH_SHA256:
		bebits = (__be64 *)&bf[j];
		*bebits = cpu_to_be64(byte_count << 3);
		j += 2;
		अवरोध;
	पूर्ण

	addr_pad = dma_map_single(ss->dev, pad, j * 4, DMA_TO_DEVICE);
	rctx->t_src[i].addr = addr_pad;
	rctx->t_src[i].len = j;
	rctx->t_dst[i].addr = addr_res;
	rctx->t_dst[i].len = digestsize / 4;
	अगर (dma_mapping_error(ss->dev, addr_pad)) अणु
		dev_err(ss->dev, "DMA error on padding SG\n");
		err = -EINVAL;
		जाओ theend;
	पूर्ण

	err = sun8i_ss_run_hash_task(ss, rctx, crypto_tfm_alg_name(areq->base.tfm));

	dma_unmap_single(ss->dev, addr_pad, j * 4, DMA_TO_DEVICE);
	dma_unmap_sg(ss->dev, areq->src, sg_nents(areq->src),
		     DMA_TO_DEVICE);
	dma_unmap_single(ss->dev, addr_res, digestsize, DMA_FROM_DEVICE);

	स_नकल(areq->result, result, algt->alg.hash.halg.digestsize);
theend:
	kमुक्त(pad);
	kमुक्त(result);
	crypto_finalize_hash_request(engine, breq, err);
	वापस 0;
पूर्ण
