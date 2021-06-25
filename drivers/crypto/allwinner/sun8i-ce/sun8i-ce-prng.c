<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ce-prng.c - hardware cryptographic offloader क्रम
 * Allwinner H3/A64/H5/H2+/H6/R40 SoC
 *
 * Copyright (C) 2015-2020 Corentin Labbe <clabbe@baylibre.com>
 *
 * This file handle the PRNG
 *
 * You could find a link क्रम the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश "sun8i-ce.h"
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <crypto/पूर्णांकernal/rng.h>

पूर्णांक sun8i_ce_prng_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ce_rng_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	स_रखो(ctx, 0, माप(काष्ठा sun8i_ce_rng_tfm_ctx));
	वापस 0;
पूर्ण

व्योम sun8i_ce_prng_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ce_rng_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	memzero_explicit(ctx->seed, ctx->slen);
	kमुक्त(ctx->seed);
	ctx->seed = शून्य;
	ctx->slen = 0;
पूर्ण

पूर्णांक sun8i_ce_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
		       अचिन्हित पूर्णांक slen)
अणु
	काष्ठा sun8i_ce_rng_tfm_ctx *ctx = crypto_rng_ctx(tfm);

	अगर (ctx->seed && ctx->slen != slen) अणु
		memzero_explicit(ctx->seed, ctx->slen);
		kमुक्त(ctx->seed);
		ctx->slen = 0;
		ctx->seed = शून्य;
	पूर्ण
	अगर (!ctx->seed)
		ctx->seed = kदो_स्मृति(slen, GFP_KERNEL | GFP_DMA);
	अगर (!ctx->seed)
		वापस -ENOMEM;

	स_नकल(ctx->seed, seed, slen);
	ctx->slen = slen;

	वापस 0;
पूर्ण

पूर्णांक sun8i_ce_prng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा sun8i_ce_rng_tfm_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा rng_alg *alg = crypto_rng_alg(tfm);
	काष्ठा sun8i_ce_alg_ढाँचा *algt;
	काष्ठा sun8i_ce_dev *ce;
	dma_addr_t dma_iv, dma_dst;
	पूर्णांक err = 0;
	पूर्णांक flow = 3;
	अचिन्हित पूर्णांक toकरो;
	काष्ठा sun8i_ce_flow *chan;
	काष्ठा ce_task *cet;
	u32 common, sym;
	व्योम *d;

	algt = container_of(alg, काष्ठा sun8i_ce_alg_ढाँचा, alg.rng);
	ce = algt->ce;

	अगर (ctx->slen == 0) अणु
		dev_err(ce->dev, "not seeded\n");
		वापस -EINVAL;
	पूर्ण

	/* we want dlen + seedsize rounded up to a multiple of PRNG_DATA_SIZE */
	toकरो = dlen + ctx->slen + PRNG_DATA_SIZE * 2;
	toकरो -= toकरो % PRNG_DATA_SIZE;

	d = kzalloc(toकरो, GFP_KERNEL | GFP_DMA);
	अगर (!d) अणु
		err = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	dev_dbg(ce->dev, "%s PRNG slen=%u dlen=%u todo=%u multi=%u\n", __func__,
		slen, dlen, toकरो, toकरो / PRNG_DATA_SIZE);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	algt->stat_req++;
	algt->stat_bytes += toकरो;
#पूर्ण_अगर

	dma_iv = dma_map_single(ce->dev, ctx->seed, ctx->slen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ce->dev, dma_iv)) अणु
		dev_err(ce->dev, "Cannot DMA MAP IV\n");
		err = -EFAULT;
		जाओ err_iv;
	पूर्ण

	dma_dst = dma_map_single(ce->dev, d, toकरो, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ce->dev, dma_dst)) अणु
		dev_err(ce->dev, "Cannot DMA MAP DST\n");
		err = -EFAULT;
		जाओ err_dst;
	पूर्ण

	err = pm_runसमय_get_sync(ce->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(ce->dev);
		जाओ err_pm;
	पूर्ण

	mutex_lock(&ce->rnglock);
	chan = &ce->chanlist[flow];

	cet = &chan->tl[0];
	स_रखो(cet, 0, माप(काष्ठा ce_task));

	cet->t_id = cpu_to_le32(flow);
	common = ce->variant->prng | CE_COMM_INT;
	cet->t_common_ctl = cpu_to_le32(common);

	/* recent CE (H6) need length in bytes, in word otherwise */
	अगर (ce->variant->prng_t_dlen_in_bytes)
		cet->t_dlen = cpu_to_le32(toकरो);
	अन्यथा
		cet->t_dlen = cpu_to_le32(toकरो / 4);

	sym = PRNG_LD;
	cet->t_sym_ctl = cpu_to_le32(sym);
	cet->t_asym_ctl = 0;

	cet->t_key = cpu_to_le32(dma_iv);
	cet->t_iv = cpu_to_le32(dma_iv);

	cet->t_dst[0].addr = cpu_to_le32(dma_dst);
	cet->t_dst[0].len = cpu_to_le32(toकरो / 4);
	ce->chanlist[flow].समयout = 2000;

	err = sun8i_ce_run_task(ce, 3, "PRNG");
	mutex_unlock(&ce->rnglock);

	pm_runसमय_put(ce->dev);

err_pm:
	dma_unmap_single(ce->dev, dma_dst, toकरो, DMA_FROM_DEVICE);
err_dst:
	dma_unmap_single(ce->dev, dma_iv, ctx->slen, DMA_TO_DEVICE);

	अगर (!err) अणु
		स_नकल(dst, d, dlen);
		स_नकल(ctx->seed, d + dlen, ctx->slen);
	पूर्ण
	memzero_explicit(d, toकरो);
err_iv:
	kमुक्त(d);
err_mem:
	वापस err;
पूर्ण
