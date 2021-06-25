<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ss-core.c - hardware cryptographic offloader क्रम
 * Allwinner A80/A83T SoC
 *
 * Copyright (C) 2015-2019 Corentin Labbe <clabbe.montjoie@gmail.com>
 *
 * Core file which रेजिस्टरs crypto algorithms supported by the SecuritySystem
 *
 * You could find a link क्रम the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "sun8i-ss.h"

अटल स्थिर काष्ठा ss_variant ss_a80_variant = अणु
	.alg_cipher = अणु SS_ALG_AES, SS_ALG_DES, SS_ALG_3DES,
	पूर्ण,
	.op_mode = अणु SS_OP_ECB, SS_OP_CBC,
	पूर्ण,
	.ss_clks = अणु
		अणु "bus", 0, 300 * 1000 * 1000 पूर्ण,
		अणु "mod", 0, 300 * 1000 * 1000 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ss_variant ss_a83t_variant = अणु
	.alg_cipher = अणु SS_ALG_AES, SS_ALG_DES, SS_ALG_3DES,
	पूर्ण,
	.alg_hash = अणु SS_ALG_MD5, SS_ALG_SHA1, SS_ALG_SHA224, SS_ALG_SHA256,
	पूर्ण,
	.op_mode = अणु SS_OP_ECB, SS_OP_CBC,
	पूर्ण,
	.ss_clks = अणु
		अणु "bus", 0, 300 * 1000 * 1000 पूर्ण,
		अणु "mod", 0, 300 * 1000 * 1000 पूर्ण,
	पूर्ण
पूर्ण;

/*
 * sun8i_ss_get_engine_number() get the next channel slot
 * This is a simple round-robin way of getting the next channel
 */
पूर्णांक sun8i_ss_get_engine_number(काष्ठा sun8i_ss_dev *ss)
अणु
	वापस atomic_inc_वापस(&ss->flow) % MAXFLOW;
पूर्ण

पूर्णांक sun8i_ss_run_task(काष्ठा sun8i_ss_dev *ss, काष्ठा sun8i_cipher_req_ctx *rctx,
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

	v |= rctx->op_mode;
	v |= rctx->method;

	अगर (rctx->op_dir)
		v |= SS_DECRYPTION;

	चयन (rctx->keylen) अणु
	हाल 128 / 8:
		v |= SS_AES_128BITS << 7;
		अवरोध;
	हाल 192 / 8:
		v |= SS_AES_192BITS << 7;
		अवरोध;
	हाल 256 / 8:
		v |= SS_AES_256BITS << 7;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < MAX_SG; i++) अणु
		अगर (!rctx->t_dst[i].addr)
			अवरोध;

		mutex_lock(&ss->mlock);
		ग_लिखोl(rctx->p_key, ss->base + SS_KEY_ADR_REG);

		अगर (i == 0) अणु
			अगर (rctx->p_iv)
				ग_लिखोl(rctx->p_iv, ss->base + SS_IV_ADR_REG);
		पूर्ण अन्यथा अणु
			अगर (rctx->biv) अणु
				अगर (rctx->op_dir == SS_ENCRYPTION)
					ग_लिखोl(rctx->t_dst[i - 1].addr + rctx->t_dst[i - 1].len * 4 - rctx->ivlen, ss->base + SS_IV_ADR_REG);
				अन्यथा
					ग_लिखोl(rctx->t_src[i - 1].addr + rctx->t_src[i - 1].len * 4 - rctx->ivlen, ss->base + SS_IV_ADR_REG);
			पूर्ण
		पूर्ण

		dev_dbg(ss->dev,
			"Processing SG %d on flow %d %s ctl=%x %d to %d method=%x opmode=%x opdir=%x srclen=%d\n",
			i, flow, name, v,
			rctx->t_src[i].len, rctx->t_dst[i].len,
			rctx->method, rctx->op_mode,
			rctx->op_dir, rctx->t_src[i].len);

		ग_लिखोl(rctx->t_src[i].addr, ss->base + SS_SRC_ADR_REG);
		ग_लिखोl(rctx->t_dst[i].addr, ss->base + SS_DST_ADR_REG);
		ग_लिखोl(rctx->t_src[i].len, ss->base + SS_LEN_ADR_REG);

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

अटल irqवापस_t ss_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sun8i_ss_dev *ss = (काष्ठा sun8i_ss_dev *)data;
	पूर्णांक flow = 0;
	u32 p;

	p = पढ़ोl(ss->base + SS_INT_STA_REG);
	क्रम (flow = 0; flow < MAXFLOW; flow++) अणु
		अगर (p & (BIT(flow))) अणु
			ग_लिखोl(BIT(flow), ss->base + SS_INT_STA_REG);
			ss->flows[flow].status = 1;
			complete(&ss->flows[flow].complete);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा sun8i_ss_alg_ढाँचा ss_algs[] = अणु
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ss_algo_id = SS_ID_CIPHER_AES,
	.ss_blockmode = SS_ID_OP_CBC,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "cbc-aes-sun8i-ss",
			.cra_priority = 400,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ss_cipher_init,
			.cra_निकास = sun8i_ss_cipher_निकास,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= sun8i_ss_aes_setkey,
		.encrypt	= sun8i_ss_skencrypt,
		.decrypt	= sun8i_ss_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ss_algo_id = SS_ID_CIPHER_AES,
	.ss_blockmode = SS_ID_OP_ECB,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "ecb-aes-sun8i-ss",
			.cra_priority = 400,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ss_cipher_init,
			.cra_निकास = sun8i_ss_cipher_निकास,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= sun8i_ss_aes_setkey,
		.encrypt	= sun8i_ss_skencrypt,
		.decrypt	= sun8i_ss_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ss_algo_id = SS_ID_CIPHER_DES3,
	.ss_blockmode = SS_ID_OP_CBC,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "cbc(des3_ede)",
			.cra_driver_name = "cbc-des3-sun8i-ss",
			.cra_priority = 400,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ss_cipher_init,
			.cra_निकास = sun8i_ss_cipher_निकास,
		पूर्ण,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
		.ivsize		= DES3_EDE_BLOCK_SIZE,
		.setkey		= sun8i_ss_des3_setkey,
		.encrypt	= sun8i_ss_skencrypt,
		.decrypt	= sun8i_ss_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ss_algo_id = SS_ID_CIPHER_DES3,
	.ss_blockmode = SS_ID_OP_ECB,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "ecb(des3_ede)",
			.cra_driver_name = "ecb-des3-sun8i-ss",
			.cra_priority = 400,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ss_cipher_init,
			.cra_निकास = sun8i_ss_cipher_निकास,
		पूर्ण,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
		.setkey		= sun8i_ss_des3_setkey,
		.encrypt	= sun8i_ss_skencrypt,
		.decrypt	= sun8i_ss_skdecrypt,
	पूर्ण
पूर्ण,
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_PRNG
अणु
	.type = CRYPTO_ALG_TYPE_RNG,
	.alg.rng = अणु
		.base = अणु
			.cra_name		= "stdrng",
			.cra_driver_name	= "sun8i-ss-prng",
			.cra_priority		= 300,
			.cra_ctxsize = माप(काष्ठा sun8i_ss_rng_tfm_ctx),
			.cra_module		= THIS_MODULE,
			.cra_init		= sun8i_ss_prng_init,
			.cra_निकास		= sun8i_ss_prng_निकास,
		पूर्ण,
		.generate               = sun8i_ss_prng_generate,
		.seed                   = sun8i_ss_prng_seed,
		.seedsize               = PRNG_SEED_SIZE,
	पूर्ण
पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_HASH
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ss_algo_id = SS_ID_HASH_MD5,
	.alg.hash = अणु
		.init = sun8i_ss_hash_init,
		.update = sun8i_ss_hash_update,
		.final = sun8i_ss_hash_final,
		.finup = sun8i_ss_hash_finup,
		.digest = sun8i_ss_hash_digest,
		.export = sun8i_ss_hash_export,
		.import = sun8i_ss_hash_import,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा md5_state),
			.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "md5-sun8i-ss",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ss_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ss_hash_crainit,
				.cra_निकास = sun8i_ss_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ss_algo_id = SS_ID_HASH_SHA1,
	.alg.hash = अणु
		.init = sun8i_ss_hash_init,
		.update = sun8i_ss_hash_update,
		.final = sun8i_ss_hash_final,
		.finup = sun8i_ss_hash_finup,
		.digest = sun8i_ss_hash_digest,
		.export = sun8i_ss_hash_export,
		.import = sun8i_ss_hash_import,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha1_state),
			.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "sha1-sun8i-ss",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ss_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ss_hash_crainit,
				.cra_निकास = sun8i_ss_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ss_algo_id = SS_ID_HASH_SHA224,
	.alg.hash = अणु
		.init = sun8i_ss_hash_init,
		.update = sun8i_ss_hash_update,
		.final = sun8i_ss_hash_final,
		.finup = sun8i_ss_hash_finup,
		.digest = sun8i_ss_hash_digest,
		.export = sun8i_ss_hash_export,
		.import = sun8i_ss_hash_import,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha256_state),
			.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "sha224-sun8i-ss",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ss_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ss_hash_crainit,
				.cra_निकास = sun8i_ss_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ss_algo_id = SS_ID_HASH_SHA256,
	.alg.hash = अणु
		.init = sun8i_ss_hash_init,
		.update = sun8i_ss_hash_update,
		.final = sun8i_ss_hash_final,
		.finup = sun8i_ss_hash_finup,
		.digest = sun8i_ss_hash_digest,
		.export = sun8i_ss_hash_export,
		.import = sun8i_ss_hash_import,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha256_state),
			.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "sha256-sun8i-ss",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ss_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ss_hash_crainit,
				.cra_निकास = sun8i_ss_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
अटल पूर्णांक sun8i_ss_debugfs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sun8i_ss_dev *ss = seq->निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAXFLOW; i++)
		seq_म_लिखो(seq, "Channel %d: nreq %lu\n", i, ss->flows[i].stat_req);

	क्रम (i = 0; i < ARRAY_SIZE(ss_algs); i++) अणु
		अगर (!ss_algs[i].ss)
			जारी;
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			seq_म_लिखो(seq, "%s %s reqs=%lu fallback=%lu\n",
				   ss_algs[i].alg.skcipher.base.cra_driver_name,
				   ss_algs[i].alg.skcipher.base.cra_name,
				   ss_algs[i].stat_req, ss_algs[i].stat_fb);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			seq_म_लिखो(seq, "%s %s reqs=%lu tsize=%lu\n",
				   ss_algs[i].alg.rng.base.cra_driver_name,
				   ss_algs[i].alg.rng.base.cra_name,
				   ss_algs[i].stat_req, ss_algs[i].stat_bytes);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			seq_म_लिखो(seq, "%s %s reqs=%lu fallback=%lu\n",
				   ss_algs[i].alg.hash.halg.base.cra_driver_name,
				   ss_algs[i].alg.hash.halg.base.cra_name,
				   ss_algs[i].stat_req, ss_algs[i].stat_fb);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(sun8i_ss_debugfs);
#पूर्ण_अगर

अटल व्योम sun8i_ss_मुक्त_flows(काष्ठा sun8i_ss_dev *ss, पूर्णांक i)
अणु
	जबतक (i >= 0) अणु
		crypto_engine_निकास(ss->flows[i].engine);
		i--;
	पूर्ण
पूर्ण

/*
 * Allocate the flow list काष्ठाure
 */
अटल पूर्णांक allocate_flows(काष्ठा sun8i_ss_dev *ss)
अणु
	पूर्णांक i, err;

	ss->flows = devm_kसुस्मृति(ss->dev, MAXFLOW, माप(काष्ठा sun8i_ss_flow),
				 GFP_KERNEL);
	अगर (!ss->flows)
		वापस -ENOMEM;

	क्रम (i = 0; i < MAXFLOW; i++) अणु
		init_completion(&ss->flows[i].complete);

		ss->flows[i].engine = crypto_engine_alloc_init(ss->dev, true);
		अगर (!ss->flows[i].engine) अणु
			dev_err(ss->dev, "Cannot allocate engine\n");
			i--;
			err = -ENOMEM;
			जाओ error_engine;
		पूर्ण
		err = crypto_engine_start(ss->flows[i].engine);
		अगर (err) अणु
			dev_err(ss->dev, "Cannot start engine\n");
			जाओ error_engine;
		पूर्ण
	पूर्ण
	वापस 0;
error_engine:
	sun8i_ss_मुक्त_flows(ss, i);
	वापस err;
पूर्ण

/*
 * Power management strategy: The device is suspended unless a TFM exists क्रम
 * one of the algorithms proposed by this driver.
 */
अटल पूर्णांक sun8i_ss_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun8i_ss_dev *ss = dev_get_drvdata(dev);
	पूर्णांक i;

	reset_control_निश्चित(ss->reset);
	क्रम (i = 0; i < SS_MAX_CLOCKS; i++)
		clk_disable_unprepare(ss->ssclks[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ss_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा sun8i_ss_dev *ss = dev_get_drvdata(dev);
	पूर्णांक err, i;

	क्रम (i = 0; i < SS_MAX_CLOCKS; i++) अणु
		अगर (!ss->variant->ss_clks[i].name)
			जारी;
		err = clk_prepare_enable(ss->ssclks[i]);
		अगर (err) अणु
			dev_err(ss->dev, "Cannot prepare_enable %s\n",
				ss->variant->ss_clks[i].name);
			जाओ error;
		पूर्ण
	पूर्ण
	err = reset_control_deनिश्चित(ss->reset);
	अगर (err) अणु
		dev_err(ss->dev, "Cannot deassert reset control\n");
		जाओ error;
	पूर्ण
	/* enable पूर्णांकerrupts क्रम all flows */
	ग_लिखोl(BIT(0) | BIT(1), ss->base + SS_INT_CTL_REG);

	वापस 0;
error:
	sun8i_ss_pm_suspend(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sun8i_ss_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sun8i_ss_pm_suspend, sun8i_ss_pm_resume, शून्य)
पूर्ण;

अटल पूर्णांक sun8i_ss_pm_init(काष्ठा sun8i_ss_dev *ss)
अणु
	पूर्णांक err;

	pm_runसमय_use_स्वतःsuspend(ss->dev);
	pm_runसमय_set_स्वतःsuspend_delay(ss->dev, 2000);

	err = pm_runसमय_set_suspended(ss->dev);
	अगर (err)
		वापस err;
	pm_runसमय_enable(ss->dev);
	वापस err;
पूर्ण

अटल व्योम sun8i_ss_pm_निकास(काष्ठा sun8i_ss_dev *ss)
अणु
	pm_runसमय_disable(ss->dev);
पूर्ण

अटल पूर्णांक sun8i_ss_रेजिस्टर_algs(काष्ठा sun8i_ss_dev *ss)
अणु
	पूर्णांक ss_method, err, id;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ss_algs); i++) अणु
		ss_algs[i].ss = ss;
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			id = ss_algs[i].ss_algo_id;
			ss_method = ss->variant->alg_cipher[id];
			अगर (ss_method == SS_ID_NOTSUPP) अणु
				dev_info(ss->dev,
					 "DEBUG: Algo of %s not supported\n",
					 ss_algs[i].alg.skcipher.base.cra_name);
				ss_algs[i].ss = शून्य;
				अवरोध;
			पूर्ण
			id = ss_algs[i].ss_blockmode;
			ss_method = ss->variant->op_mode[id];
			अगर (ss_method == SS_ID_NOTSUPP) अणु
				dev_info(ss->dev, "DEBUG: Blockmode of %s not supported\n",
					 ss_algs[i].alg.skcipher.base.cra_name);
				ss_algs[i].ss = शून्य;
				अवरोध;
			पूर्ण
			dev_info(ss->dev, "DEBUG: Register %s\n",
				 ss_algs[i].alg.skcipher.base.cra_name);
			err = crypto_रेजिस्टर_skcipher(&ss_algs[i].alg.skcipher);
			अगर (err) अणु
				dev_err(ss->dev, "Fail to register %s\n",
					ss_algs[i].alg.skcipher.base.cra_name);
				ss_algs[i].ss = शून्य;
				वापस err;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			err = crypto_रेजिस्टर_rng(&ss_algs[i].alg.rng);
			अगर (err) अणु
				dev_err(ss->dev, "Fail to register %s\n",
					ss_algs[i].alg.rng.base.cra_name);
				ss_algs[i].ss = शून्य;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			id = ss_algs[i].ss_algo_id;
			ss_method = ss->variant->alg_hash[id];
			अगर (ss_method == SS_ID_NOTSUPP) अणु
				dev_info(ss->dev,
					"DEBUG: Algo of %s not supported\n",
					ss_algs[i].alg.hash.halg.base.cra_name);
				ss_algs[i].ss = शून्य;
				अवरोध;
			पूर्ण
			dev_info(ss->dev, "Register %s\n",
				 ss_algs[i].alg.hash.halg.base.cra_name);
			err = crypto_रेजिस्टर_ahash(&ss_algs[i].alg.hash);
			अगर (err) अणु
				dev_err(ss->dev, "ERROR: Fail to register %s\n",
					ss_algs[i].alg.hash.halg.base.cra_name);
				ss_algs[i].ss = शून्य;
				वापस err;
			पूर्ण
			अवरोध;
		शेष:
			ss_algs[i].ss = शून्य;
			dev_err(ss->dev, "ERROR: tried to register an unknown algo\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sun8i_ss_unरेजिस्टर_algs(काष्ठा sun8i_ss_dev *ss)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ss_algs); i++) अणु
		अगर (!ss_algs[i].ss)
			जारी;
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			dev_info(ss->dev, "Unregister %d %s\n", i,
				 ss_algs[i].alg.skcipher.base.cra_name);
			crypto_unरेजिस्टर_skcipher(&ss_algs[i].alg.skcipher);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			dev_info(ss->dev, "Unregister %d %s\n", i,
				 ss_algs[i].alg.rng.base.cra_name);
			crypto_unरेजिस्टर_rng(&ss_algs[i].alg.rng);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			dev_info(ss->dev, "Unregister %d %s\n", i,
				 ss_algs[i].alg.hash.halg.base.cra_name);
			crypto_unरेजिस्टर_ahash(&ss_algs[i].alg.hash);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sun8i_ss_get_clks(काष्ठा sun8i_ss_dev *ss)
अणु
	अचिन्हित दीर्घ cr;
	पूर्णांक err, i;

	क्रम (i = 0; i < SS_MAX_CLOCKS; i++) अणु
		अगर (!ss->variant->ss_clks[i].name)
			जारी;
		ss->ssclks[i] = devm_clk_get(ss->dev, ss->variant->ss_clks[i].name);
		अगर (IS_ERR(ss->ssclks[i])) अणु
			err = PTR_ERR(ss->ssclks[i]);
			dev_err(ss->dev, "Cannot get %s SS clock err=%d\n",
				ss->variant->ss_clks[i].name, err);
			वापस err;
		पूर्ण
		cr = clk_get_rate(ss->ssclks[i]);
		अगर (!cr)
			वापस -EINVAL;
		अगर (ss->variant->ss_clks[i].freq > 0 &&
		    cr != ss->variant->ss_clks[i].freq) अणु
			dev_info(ss->dev, "Set %s clock to %lu (%lu Mhz) from %lu (%lu Mhz)\n",
				 ss->variant->ss_clks[i].name,
				 ss->variant->ss_clks[i].freq,
				 ss->variant->ss_clks[i].freq / 1000000,
				 cr, cr / 1000000);
			err = clk_set_rate(ss->ssclks[i], ss->variant->ss_clks[i].freq);
			अगर (err)
				dev_err(ss->dev, "Fail to set %s clk speed to %lu hz\n",
					ss->variant->ss_clks[i].name,
					ss->variant->ss_clks[i].freq);
		पूर्ण
		अगर (ss->variant->ss_clks[i].max_freq > 0 &&
		    cr > ss->variant->ss_clks[i].max_freq)
			dev_warn(ss->dev, "Frequency for %s (%lu hz) is higher than datasheet's recommendation (%lu hz)",
				 ss->variant->ss_clks[i].name, cr,
				 ss->variant->ss_clks[i].max_freq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun8i_ss_dev *ss;
	पूर्णांक err, irq;
	u32 v;

	ss = devm_kzalloc(&pdev->dev, माप(*ss), GFP_KERNEL);
	अगर (!ss)
		वापस -ENOMEM;

	ss->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ss);

	ss->variant = of_device_get_match_data(&pdev->dev);
	अगर (!ss->variant) अणु
		dev_err(&pdev->dev, "Missing Crypto Engine variant\n");
		वापस -EINVAL;
	पूर्ण

	ss->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ss->base))
		वापस PTR_ERR(ss->base);

	err = sun8i_ss_get_clks(ss);
	अगर (err)
		वापस err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ss->reset = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ss->reset))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(ss->reset),
				     "No reset control found\n");

	mutex_init(&ss->mlock);

	err = allocate_flows(ss);
	अगर (err)
		वापस err;

	err = sun8i_ss_pm_init(ss);
	अगर (err)
		जाओ error_pm;

	err = devm_request_irq(&pdev->dev, irq, ss_irq_handler, 0, "sun8i-ss", ss);
	अगर (err) अणु
		dev_err(ss->dev, "Cannot request SecuritySystem IRQ (err=%d)\n", err);
		जाओ error_irq;
	पूर्ण

	err = sun8i_ss_रेजिस्टर_algs(ss);
	अगर (err)
		जाओ error_alg;

	err = pm_runसमय_resume_and_get(ss->dev);
	अगर (err < 0)
		जाओ error_alg;

	v = पढ़ोl(ss->base + SS_CTL_REG);
	v >>= SS_DIE_ID_SHIFT;
	v &= SS_DIE_ID_MASK;
	dev_info(&pdev->dev, "Security System Die ID %x\n", v);

	pm_runसमय_put_sync(ss->dev);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	/* Ignore error of debugfs */
	ss->dbgfs_dir = debugfs_create_dir("sun8i-ss", शून्य);
	ss->dbgfs_stats = debugfs_create_file("stats", 0444,
					      ss->dbgfs_dir, ss,
					      &sun8i_ss_debugfs_fops);
#पूर्ण_अगर

	वापस 0;
error_alg:
	sun8i_ss_unरेजिस्टर_algs(ss);
error_irq:
	sun8i_ss_pm_निकास(ss);
error_pm:
	sun8i_ss_मुक्त_flows(ss, MAXFLOW - 1);
	वापस err;
पूर्ण

अटल पूर्णांक sun8i_ss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun8i_ss_dev *ss = platक्रमm_get_drvdata(pdev);

	sun8i_ss_unरेजिस्टर_algs(ss);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_SS_DEBUG
	debugfs_हटाओ_recursive(ss->dbgfs_dir);
#पूर्ण_अगर

	sun8i_ss_मुक्त_flows(ss, MAXFLOW - 1);

	sun8i_ss_pm_निकास(ss);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun8i_ss_crypto_of_match_table[] = अणु
	अणु .compatible = "allwinner,sun8i-a83t-crypto",
	  .data = &ss_a83t_variant पूर्ण,
	अणु .compatible = "allwinner,sun9i-a80-crypto",
	  .data = &ss_a80_variant पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_ss_crypto_of_match_table);

अटल काष्ठा platक्रमm_driver sun8i_ss_driver = अणु
	.probe		 = sun8i_ss_probe,
	.हटाओ		 = sun8i_ss_हटाओ,
	.driver		 = अणु
		.name		= "sun8i-ss",
		.pm             = &sun8i_ss_pm_ops,
		.of_match_table	= sun8i_ss_crypto_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sun8i_ss_driver);

MODULE_DESCRIPTION("Allwinner SecuritySystem cryptographic offloader");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corentin Labbe <clabbe.montjoie@gmail.com>");
