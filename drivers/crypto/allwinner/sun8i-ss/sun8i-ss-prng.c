<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ss-prng.c - hardware cryptographic offloader क्रम
 * Allwinner A80/A83T SoC
 *
 * Copyright (C) 2015-2020 Corentin Labbe <clabbe@baylibre.com>
 *
 * This file handle the PRNG found in the SS
 *
 * You could find a link क्रम the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश "sun8i-ss.h"
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <crypto/पूर्णांकernal/rng.h>

पूर्णांक sun8i_ss_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
		       अचिन्हित पूर्णांक slen)
अणु
	काष्ठा sun8i_ss_rng_tfm_ctx *ctx = crypto_rng_ctx(tfm);

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

पूर्णांक sun8i_ss_prng_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ss_rng_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	स_रखो(ctx, 0, माप(काष्ठा sun8i_ss_rng_tfm_ctx));
	वापस 0;
पूर्ण

व्योम sun8i_ss_prng_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun8i_ss_rng_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	memzero_explicit(ctx->seed, ctx->slen);
	kमुक्त(ctx->seed);
	ctx->seed = शून्य;
	ctx->slen = 0;
पूर्ण

पूर्णांक sun8i_ss_prng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा sun8i_ss_rng_tfm_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा rng_alg *alg = crypto_rng_alg(tfm);
	काष्ठा sun8i_ss_alg_ढाँचा *algt;
	काष्ठा sun8i_ss_dev *ss;
	dma_addr_t dma_iv, dma_dst;
	अचिन्हित पूर्णांक toकरो;
	पूर्णांक err = 0;
	पूर्णांक flow;
	व्योम *d;
	u32 v;

	algt = container_of(alg, काष्ठा sun8i_ss_alg_ढाँचा, alg.rng);
	ss = algt->ss;

	अगर (ctx->slen == 0) अणु
		dev_err(ss->dev, "The PRNG is not seeded\n");
		वापस -EINVAL;
	पूर्ण

	/* The SS करोes not give an updated seed, so we need to get a new one.
	 * So we will ask क्रम an extra PRNG_SEED_SIZE data.
	 * We want dlen + seedsize rounded up to a multiple of PRNG_DATA_SIZE
	 */
	toकरो = dlen + PRNG_SEED_SIZE + PRNG_DATA_SIZE;
	toकरो -= toकरो % PRNG_DATA_SIZE;

	d = kzalloc(toकरो, GFP_KERNEL | GFP_DMA);
	अगर (!d)
		वापस -ENOMEM;

	flow = sun8i_ss_get_engine_number(ss);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	algt->stat_req++;
	algt->stat_bytes += toकरो;
#पूर्ण_अगर

	v = SS_ALG_PRNG | SS_PRNG_CONTINUE | SS_START;
	अगर (flow)
		v |= SS_FLOW1;
	अन्यथा
		v |= SS_FLOW0;

	dma_iv = dma_map_single(ss->dev, ctx->seed, ctx->slen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ss->dev, dma_iv)) अणु
		dev_err(ss->dev, "Cannot DMA MAP IV\n");
		err = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	dma_dst = dma_map_single(ss->dev, d, toकरो, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ss->dev, dma_dst)) अणु
		dev_err(ss->dev, "Cannot DMA MAP DST\n");
		err = -EFAULT;
		जाओ err_iv;
	पूर्ण

	err = pm_runसमय_get_sync(ss->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(ss->dev);
		जाओ err_pm;
	पूर्ण
	err = 0;

	mutex_lock(&ss->mlock);
	ग_लिखोl(dma_iv, ss->base + SS_IV_ADR_REG);
	/* the PRNG act badly (failing rngtest) without SS_KEY_ADR_REG set */
	ग_लिखोl(dma_iv, ss->base + SS_KEY_ADR_REG);
	ग_लिखोl(dma_dst, ss->base + SS_DST_ADR_REG);
	ग_लिखोl(toकरो / 4, ss->base + SS_LEN_ADR_REG);

	reinit_completion(&ss->flows[flow].complete);
	ss->flows[flow].status = 0;
	/* Be sure all data is written beक्रमe enabling the task */
	wmb();

	ग_लिखोl(v, ss->base + SS_CTL_REG);

	रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ss->flows[flow].complete,
						  msecs_to_jअगरfies(toकरो));
	अगर (ss->flows[flow].status == 0) अणु
		dev_err(ss->dev, "DMA timeout for PRNG (size=%u)\n", toकरो);
		err = -EFAULT;
	पूर्ण
	/* Since cipher and hash use the linux/cryptoengine and that we have
	 * a cryptoengine per flow, we are sure that they will issue only one
	 * request per flow.
	 * Since the cryptoengine रुको क्रम completion beक्रमe submitting a new
	 * one, the mlock could be left just after the final ग_लिखोl.
	 * But cryptoengine cannot handle crypto_rng, so we need to be sure
	 * nothing will use our flow.
	 * The easiest way is to grab mlock until the hardware end our requests.
	 * We could have used a per flow lock, but this would increase
	 * complनिकासy.
	 * The drawback is that no request could be handled क्रम the other flow.
	 */
	mutex_unlock(&ss->mlock);

	pm_runसमय_put(ss->dev);

err_pm:
	dma_unmap_single(ss->dev, dma_dst, toकरो, DMA_FROM_DEVICE);
err_iv:
	dma_unmap_single(ss->dev, dma_iv, ctx->slen, DMA_TO_DEVICE);

	अगर (!err) अणु
		स_नकल(dst, d, dlen);
		/* Update seed */
		स_नकल(ctx->seed, d + dlen, ctx->slen);
	पूर्ण
	memzero_explicit(d, toकरो);
err_मुक्त:
	kमुक्त(d);

	वापस err;
पूर्ण
