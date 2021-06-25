<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ce-core.c - hardware cryptographic offloader क्रम
 * Allwinner H3/A64/H5/H2+/H6/R40 SoC
 *
 * Copyright (C) 2015-2019 Corentin Labbe <clabbe.montjoie@gmail.com>
 *
 * Core file which रेजिस्टरs crypto algorithms supported by the CryptoEngine.
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

#समावेश "sun8i-ce.h"

/*
 * mod घड़ी is lower on H3 than other SoC due to some DMA समयout occurring
 * with high value.
 * If you want to tune mod घड़ी, loading driver and passing selftest is
 * insufficient, you need to test with some LUKS test (mount and ग_लिखो to it)
 */
अटल स्थिर काष्ठा ce_variant ce_h3_variant = अणु
	.alg_cipher = अणु CE_ALG_AES, CE_ALG_DES, CE_ALG_3DES,
	पूर्ण,
	.alg_hash = अणु CE_ALG_MD5, CE_ALG_SHA1, CE_ALG_SHA224, CE_ALG_SHA256,
		CE_ALG_SHA384, CE_ALG_SHA512
	पूर्ण,
	.op_mode = अणु CE_OP_ECB, CE_OP_CBC
	पूर्ण,
	.ce_clks = अणु
		अणु "bus", 0, 200000000 पूर्ण,
		अणु "mod", 50000000, 0 पूर्ण,
		पूर्ण,
	.esr = ESR_H3,
	.prng = CE_ALG_PRNG,
	.trng = CE_ID_NOTSUPP,
पूर्ण;

अटल स्थिर काष्ठा ce_variant ce_h5_variant = अणु
	.alg_cipher = अणु CE_ALG_AES, CE_ALG_DES, CE_ALG_3DES,
	पूर्ण,
	.alg_hash = अणु CE_ALG_MD5, CE_ALG_SHA1, CE_ALG_SHA224, CE_ALG_SHA256,
		CE_ID_NOTSUPP, CE_ID_NOTSUPP
	पूर्ण,
	.op_mode = अणु CE_OP_ECB, CE_OP_CBC
	पूर्ण,
	.ce_clks = अणु
		अणु "bus", 0, 200000000 पूर्ण,
		अणु "mod", 300000000, 0 पूर्ण,
		पूर्ण,
	.esr = ESR_H5,
	.prng = CE_ALG_PRNG,
	.trng = CE_ID_NOTSUPP,
पूर्ण;

अटल स्थिर काष्ठा ce_variant ce_h6_variant = अणु
	.alg_cipher = अणु CE_ALG_AES, CE_ALG_DES, CE_ALG_3DES,
	पूर्ण,
	.alg_hash = अणु CE_ALG_MD5, CE_ALG_SHA1, CE_ALG_SHA224, CE_ALG_SHA256,
		CE_ALG_SHA384, CE_ALG_SHA512
	पूर्ण,
	.op_mode = अणु CE_OP_ECB, CE_OP_CBC
	पूर्ण,
	.cipher_t_dlen_in_bytes = true,
	.hash_t_dlen_in_bits = true,
	.prng_t_dlen_in_bytes = true,
	.trng_t_dlen_in_bytes = true,
	.ce_clks = अणु
		अणु "bus", 0, 200000000 पूर्ण,
		अणु "mod", 300000000, 0 पूर्ण,
		अणु "ram", 0, 400000000 पूर्ण,
		पूर्ण,
	.esr = ESR_H6,
	.prng = CE_ALG_PRNG_V2,
	.trng = CE_ALG_TRNG_V2,
पूर्ण;

अटल स्थिर काष्ठा ce_variant ce_a64_variant = अणु
	.alg_cipher = अणु CE_ALG_AES, CE_ALG_DES, CE_ALG_3DES,
	पूर्ण,
	.alg_hash = अणु CE_ALG_MD5, CE_ALG_SHA1, CE_ALG_SHA224, CE_ALG_SHA256,
		CE_ID_NOTSUPP, CE_ID_NOTSUPP
	पूर्ण,
	.op_mode = अणु CE_OP_ECB, CE_OP_CBC
	पूर्ण,
	.ce_clks = अणु
		अणु "bus", 0, 200000000 पूर्ण,
		अणु "mod", 300000000, 0 पूर्ण,
		पूर्ण,
	.esr = ESR_A64,
	.prng = CE_ALG_PRNG,
	.trng = CE_ID_NOTSUPP,
पूर्ण;

अटल स्थिर काष्ठा ce_variant ce_r40_variant = अणु
	.alg_cipher = अणु CE_ALG_AES, CE_ALG_DES, CE_ALG_3DES,
	पूर्ण,
	.alg_hash = अणु CE_ALG_MD5, CE_ALG_SHA1, CE_ALG_SHA224, CE_ALG_SHA256,
		CE_ID_NOTSUPP, CE_ID_NOTSUPP
	पूर्ण,
	.op_mode = अणु CE_OP_ECB, CE_OP_CBC
	पूर्ण,
	.ce_clks = अणु
		अणु "bus", 0, 200000000 पूर्ण,
		अणु "mod", 300000000, 0 पूर्ण,
		पूर्ण,
	.esr = ESR_R40,
	.prng = CE_ALG_PRNG,
	.trng = CE_ID_NOTSUPP,
पूर्ण;

/*
 * sun8i_ce_get_engine_number() get the next channel slot
 * This is a simple round-robin way of getting the next channel
 * The flow 3 is reserve क्रम xRNG operations
 */
पूर्णांक sun8i_ce_get_engine_number(काष्ठा sun8i_ce_dev *ce)
अणु
	वापस atomic_inc_वापस(&ce->flow) % (MAXFLOW - 1);
पूर्ण

पूर्णांक sun8i_ce_run_task(काष्ठा sun8i_ce_dev *ce, पूर्णांक flow, स्थिर अक्षर *name)
अणु
	u32 v;
	पूर्णांक err = 0;
	काष्ठा ce_task *cet = ce->chanlist[flow].tl;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	ce->chanlist[flow].stat_req++;
#पूर्ण_अगर

	mutex_lock(&ce->mlock);

	v = पढ़ोl(ce->base + CE_ICR);
	v |= 1 << flow;
	ग_लिखोl(v, ce->base + CE_ICR);

	reinit_completion(&ce->chanlist[flow].complete);
	ग_लिखोl(ce->chanlist[flow].t_phy, ce->base + CE_TDQ);

	ce->chanlist[flow].status = 0;
	/* Be sure all data is written beक्रमe enabling the task */
	wmb();

	/* Only H6 needs to ग_लिखो a part of t_common_ctl aदीर्घ with "1", but since it is ignored
	 * on older SoCs, we have no reason to complicate things.
	 */
	v = 1 | ((le32_to_cpu(ce->chanlist[flow].tl->t_common_ctl) & 0x7F) << 8);
	ग_लिखोl(v, ce->base + CE_TLR);
	mutex_unlock(&ce->mlock);

	रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ce->chanlist[flow].complete,
			msecs_to_jअगरfies(ce->chanlist[flow].समयout));

	अगर (ce->chanlist[flow].status == 0) अणु
		dev_err(ce->dev, "DMA timeout for %s (tm=%d) on flow %d\n", name,
			ce->chanlist[flow].समयout, flow);
		err = -EFAULT;
	पूर्ण
	/* No need to lock क्रम this पढ़ो, the channel is locked so
	 * nothing could modअगरy the error value क्रम this channel
	 */
	v = पढ़ोl(ce->base + CE_ESR);
	चयन (ce->variant->esr) अणु
	हाल ESR_H3:
		/* Sadly, the error bit is not per flow */
		अगर (v) अणु
			dev_err(ce->dev, "CE ERROR: %x for flow %x\n", v, flow);
			err = -EFAULT;
			prपूर्णांक_hex_dump(KERN_INFO, "TASK: ", DUMP_PREFIX_NONE, 16, 4,
				       cet, माप(काष्ठा ce_task), false);
		पूर्ण
		अगर (v & CE_ERR_ALGO_NOTSUP)
			dev_err(ce->dev, "CE ERROR: algorithm not supported\n");
		अगर (v & CE_ERR_DATALEN)
			dev_err(ce->dev, "CE ERROR: data length error\n");
		अगर (v & CE_ERR_KEYSRAM)
			dev_err(ce->dev, "CE ERROR: keysram access error for AES\n");
		अवरोध;
	हाल ESR_A64:
	हाल ESR_H5:
	हाल ESR_R40:
		v >>= (flow * 4);
		v &= 0xF;
		अगर (v) अणु
			dev_err(ce->dev, "CE ERROR: %x for flow %x\n", v, flow);
			err = -EFAULT;
			prपूर्णांक_hex_dump(KERN_INFO, "TASK: ", DUMP_PREFIX_NONE, 16, 4,
				       cet, माप(काष्ठा ce_task), false);
		पूर्ण
		अगर (v & CE_ERR_ALGO_NOTSUP)
			dev_err(ce->dev, "CE ERROR: algorithm not supported\n");
		अगर (v & CE_ERR_DATALEN)
			dev_err(ce->dev, "CE ERROR: data length error\n");
		अगर (v & CE_ERR_KEYSRAM)
			dev_err(ce->dev, "CE ERROR: keysram access error for AES\n");
		अवरोध;
	हाल ESR_H6:
		v >>= (flow * 8);
		v &= 0xFF;
		अगर (v) अणु
			dev_err(ce->dev, "CE ERROR: %x for flow %x\n", v, flow);
			err = -EFAULT;
			prपूर्णांक_hex_dump(KERN_INFO, "TASK: ", DUMP_PREFIX_NONE, 16, 4,
				       cet, माप(काष्ठा ce_task), false);
		पूर्ण
		अगर (v & CE_ERR_ALGO_NOTSUP)
			dev_err(ce->dev, "CE ERROR: algorithm not supported\n");
		अगर (v & CE_ERR_DATALEN)
			dev_err(ce->dev, "CE ERROR: data length error\n");
		अगर (v & CE_ERR_KEYSRAM)
			dev_err(ce->dev, "CE ERROR: keysram access error for AES\n");
		अगर (v & CE_ERR_ADDR_INVALID)
			dev_err(ce->dev, "CE ERROR: address invalid\n");
		अगर (v & CE_ERR_KEYLADDER)
			dev_err(ce->dev, "CE ERROR: key ladder configuration error\n");
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t ce_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sun8i_ce_dev *ce = (काष्ठा sun8i_ce_dev *)data;
	पूर्णांक flow = 0;
	u32 p;

	p = पढ़ोl(ce->base + CE_ISR);
	क्रम (flow = 0; flow < MAXFLOW; flow++) अणु
		अगर (p & (BIT(flow))) अणु
			ग_लिखोl(BIT(flow), ce->base + CE_ISR);
			ce->chanlist[flow].status = 1;
			complete(&ce->chanlist[flow].complete);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा sun8i_ce_alg_ढाँचा ce_algs[] = अणु
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ce_algo_id = CE_ID_CIPHER_AES,
	.ce_blockmode = CE_ID_OP_CBC,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "cbc-aes-sun8i-ce",
			.cra_priority = 400,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ce_cipher_init,
			.cra_निकास = sun8i_ce_cipher_निकास,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= sun8i_ce_aes_setkey,
		.encrypt	= sun8i_ce_skencrypt,
		.decrypt	= sun8i_ce_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ce_algo_id = CE_ID_CIPHER_AES,
	.ce_blockmode = CE_ID_OP_ECB,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "ecb-aes-sun8i-ce",
			.cra_priority = 400,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ce_cipher_init,
			.cra_निकास = sun8i_ce_cipher_निकास,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= sun8i_ce_aes_setkey,
		.encrypt	= sun8i_ce_skencrypt,
		.decrypt	= sun8i_ce_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ce_algo_id = CE_ID_CIPHER_DES3,
	.ce_blockmode = CE_ID_OP_CBC,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "cbc(des3_ede)",
			.cra_driver_name = "cbc-des3-sun8i-ce",
			.cra_priority = 400,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ce_cipher_init,
			.cra_निकास = sun8i_ce_cipher_निकास,
		पूर्ण,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
		.ivsize		= DES3_EDE_BLOCK_SIZE,
		.setkey		= sun8i_ce_des3_setkey,
		.encrypt	= sun8i_ce_skencrypt,
		.decrypt	= sun8i_ce_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.ce_algo_id = CE_ID_CIPHER_DES3,
	.ce_blockmode = CE_ID_OP_ECB,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "ecb(des3_ede)",
			.cra_driver_name = "ecb-des3-sun8i-ce",
			.cra_priority = 400,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun8i_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = sun8i_ce_cipher_init,
			.cra_निकास = sun8i_ce_cipher_निकास,
		पूर्ण,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
		.setkey		= sun8i_ce_des3_setkey,
		.encrypt	= sun8i_ce_skencrypt,
		.decrypt	= sun8i_ce_skdecrypt,
	पूर्ण
पूर्ण,
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_HASH
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ce_algo_id = CE_ID_HASH_MD5,
	.alg.hash = अणु
		.init = sun8i_ce_hash_init,
		.update = sun8i_ce_hash_update,
		.final = sun8i_ce_hash_final,
		.finup = sun8i_ce_hash_finup,
		.digest = sun8i_ce_hash_digest,
		.export = sun8i_ce_hash_export,
		.import = sun8i_ce_hash_import,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा md5_state),
			.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "md5-sun8i-ce",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ce_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ce_hash_crainit,
				.cra_निकास = sun8i_ce_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ce_algo_id = CE_ID_HASH_SHA1,
	.alg.hash = अणु
		.init = sun8i_ce_hash_init,
		.update = sun8i_ce_hash_update,
		.final = sun8i_ce_hash_final,
		.finup = sun8i_ce_hash_finup,
		.digest = sun8i_ce_hash_digest,
		.export = sun8i_ce_hash_export,
		.import = sun8i_ce_hash_import,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha1_state),
			.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "sha1-sun8i-ce",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ce_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ce_hash_crainit,
				.cra_निकास = sun8i_ce_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ce_algo_id = CE_ID_HASH_SHA224,
	.alg.hash = अणु
		.init = sun8i_ce_hash_init,
		.update = sun8i_ce_hash_update,
		.final = sun8i_ce_hash_final,
		.finup = sun8i_ce_hash_finup,
		.digest = sun8i_ce_hash_digest,
		.export = sun8i_ce_hash_export,
		.import = sun8i_ce_hash_import,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha256_state),
			.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "sha224-sun8i-ce",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ce_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ce_hash_crainit,
				.cra_निकास = sun8i_ce_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ce_algo_id = CE_ID_HASH_SHA256,
	.alg.hash = अणु
		.init = sun8i_ce_hash_init,
		.update = sun8i_ce_hash_update,
		.final = sun8i_ce_hash_final,
		.finup = sun8i_ce_hash_finup,
		.digest = sun8i_ce_hash_digest,
		.export = sun8i_ce_hash_export,
		.import = sun8i_ce_hash_import,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha256_state),
			.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "sha256-sun8i-ce",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ce_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ce_hash_crainit,
				.cra_निकास = sun8i_ce_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ce_algo_id = CE_ID_HASH_SHA384,
	.alg.hash = अणु
		.init = sun8i_ce_hash_init,
		.update = sun8i_ce_hash_update,
		.final = sun8i_ce_hash_final,
		.finup = sun8i_ce_hash_finup,
		.digest = sun8i_ce_hash_digest,
		.export = sun8i_ce_hash_export,
		.import = sun8i_ce_hash_import,
		.halg = अणु
			.digestsize = SHA384_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha512_state),
			.base = अणु
				.cra_name = "sha384",
				.cra_driver_name = "sha384-sun8i-ce",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA384_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ce_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ce_hash_crainit,
				.cra_निकास = sun8i_ce_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	.type = CRYPTO_ALG_TYPE_AHASH,
	.ce_algo_id = CE_ID_HASH_SHA512,
	.alg.hash = अणु
		.init = sun8i_ce_hash_init,
		.update = sun8i_ce_hash_update,
		.final = sun8i_ce_hash_final,
		.finup = sun8i_ce_hash_finup,
		.digest = sun8i_ce_hash_digest,
		.export = sun8i_ce_hash_export,
		.import = sun8i_ce_hash_import,
		.halg = अणु
			.digestsize = SHA512_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha512_state),
			.base = अणु
				.cra_name = "sha512",
				.cra_driver_name = "sha512-sun8i-ce",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA512_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun8i_ce_hash_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun8i_ce_hash_crainit,
				.cra_निकास = sun8i_ce_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_PRNG
अणु
	.type = CRYPTO_ALG_TYPE_RNG,
	.alg.rng = अणु
		.base = अणु
			.cra_name		= "stdrng",
			.cra_driver_name	= "sun8i-ce-prng",
			.cra_priority		= 300,
			.cra_ctxsize		= माप(काष्ठा sun8i_ce_rng_tfm_ctx),
			.cra_module		= THIS_MODULE,
			.cra_init		= sun8i_ce_prng_init,
			.cra_निकास		= sun8i_ce_prng_निकास,
		पूर्ण,
		.generate               = sun8i_ce_prng_generate,
		.seed                   = sun8i_ce_prng_seed,
		.seedsize               = PRNG_SEED_SIZE,
	पूर्ण
पूर्ण,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
अटल पूर्णांक sun8i_ce_debugfs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sun8i_ce_dev *ce = seq->निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAXFLOW; i++)
		seq_म_लिखो(seq, "Channel %d: nreq %lu\n", i, ce->chanlist[i].stat_req);

	क्रम (i = 0; i < ARRAY_SIZE(ce_algs); i++) अणु
		अगर (!ce_algs[i].ce)
			जारी;
		चयन (ce_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			seq_म_लिखो(seq, "%s %s %lu %lu\n",
				   ce_algs[i].alg.skcipher.base.cra_driver_name,
				   ce_algs[i].alg.skcipher.base.cra_name,
				   ce_algs[i].stat_req, ce_algs[i].stat_fb);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			seq_म_लिखो(seq, "%s %s %lu %lu\n",
				   ce_algs[i].alg.hash.halg.base.cra_driver_name,
				   ce_algs[i].alg.hash.halg.base.cra_name,
				   ce_algs[i].stat_req, ce_algs[i].stat_fb);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			seq_म_लिखो(seq, "%s %s %lu %lu\n",
				   ce_algs[i].alg.rng.base.cra_driver_name,
				   ce_algs[i].alg.rng.base.cra_name,
				   ce_algs[i].stat_req, ce_algs[i].stat_bytes);
			अवरोध;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_TRNG
	seq_म_लिखो(seq, "HWRNG %lu %lu\n",
		   ce->hwrng_stat_req, ce->hwrng_stat_bytes);
#पूर्ण_अगर
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(sun8i_ce_debugfs);
#पूर्ण_अगर

अटल व्योम sun8i_ce_मुक्त_chanlist(काष्ठा sun8i_ce_dev *ce, पूर्णांक i)
अणु
	जबतक (i >= 0) अणु
		crypto_engine_निकास(ce->chanlist[i].engine);
		अगर (ce->chanlist[i].tl)
			dma_मुक्त_coherent(ce->dev, माप(काष्ठा ce_task),
					  ce->chanlist[i].tl,
					  ce->chanlist[i].t_phy);
		i--;
	पूर्ण
पूर्ण

/*
 * Allocate the channel list काष्ठाure
 */
अटल पूर्णांक sun8i_ce_allocate_chanlist(काष्ठा sun8i_ce_dev *ce)
अणु
	पूर्णांक i, err;

	ce->chanlist = devm_kसुस्मृति(ce->dev, MAXFLOW,
				    माप(काष्ठा sun8i_ce_flow), GFP_KERNEL);
	अगर (!ce->chanlist)
		वापस -ENOMEM;

	क्रम (i = 0; i < MAXFLOW; i++) अणु
		init_completion(&ce->chanlist[i].complete);

		ce->chanlist[i].engine = crypto_engine_alloc_init(ce->dev, true);
		अगर (!ce->chanlist[i].engine) अणु
			dev_err(ce->dev, "Cannot allocate engine\n");
			i--;
			err = -ENOMEM;
			जाओ error_engine;
		पूर्ण
		err = crypto_engine_start(ce->chanlist[i].engine);
		अगर (err) अणु
			dev_err(ce->dev, "Cannot start engine\n");
			जाओ error_engine;
		पूर्ण
		ce->chanlist[i].tl = dma_alloc_coherent(ce->dev,
							माप(काष्ठा ce_task),
							&ce->chanlist[i].t_phy,
							GFP_KERNEL);
		अगर (!ce->chanlist[i].tl) अणु
			dev_err(ce->dev, "Cannot get DMA memory for task %d\n",
				i);
			err = -ENOMEM;
			जाओ error_engine;
		पूर्ण
	पूर्ण
	वापस 0;
error_engine:
	sun8i_ce_मुक्त_chanlist(ce, i);
	वापस err;
पूर्ण

/*
 * Power management strategy: The device is suspended unless a TFM exists क्रम
 * one of the algorithms proposed by this driver.
 */
अटल पूर्णांक sun8i_ce_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun8i_ce_dev *ce = dev_get_drvdata(dev);
	पूर्णांक i;

	reset_control_निश्चित(ce->reset);
	क्रम (i = 0; i < CE_MAX_CLOCKS; i++)
		clk_disable_unprepare(ce->ceclks[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ce_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा sun8i_ce_dev *ce = dev_get_drvdata(dev);
	पूर्णांक err, i;

	क्रम (i = 0; i < CE_MAX_CLOCKS; i++) अणु
		अगर (!ce->variant->ce_clks[i].name)
			जारी;
		err = clk_prepare_enable(ce->ceclks[i]);
		अगर (err) अणु
			dev_err(ce->dev, "Cannot prepare_enable %s\n",
				ce->variant->ce_clks[i].name);
			जाओ error;
		पूर्ण
	पूर्ण
	err = reset_control_deनिश्चित(ce->reset);
	अगर (err) अणु
		dev_err(ce->dev, "Cannot deassert reset control\n");
		जाओ error;
	पूर्ण
	वापस 0;
error:
	sun8i_ce_pm_suspend(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sun8i_ce_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sun8i_ce_pm_suspend, sun8i_ce_pm_resume, शून्य)
पूर्ण;

अटल पूर्णांक sun8i_ce_pm_init(काष्ठा sun8i_ce_dev *ce)
अणु
	पूर्णांक err;

	pm_runसमय_use_स्वतःsuspend(ce->dev);
	pm_runसमय_set_स्वतःsuspend_delay(ce->dev, 2000);

	err = pm_runसमय_set_suspended(ce->dev);
	अगर (err)
		वापस err;
	pm_runसमय_enable(ce->dev);
	वापस err;
पूर्ण

अटल व्योम sun8i_ce_pm_निकास(काष्ठा sun8i_ce_dev *ce)
अणु
	pm_runसमय_disable(ce->dev);
पूर्ण

अटल पूर्णांक sun8i_ce_get_clks(काष्ठा sun8i_ce_dev *ce)
अणु
	अचिन्हित दीर्घ cr;
	पूर्णांक err, i;

	क्रम (i = 0; i < CE_MAX_CLOCKS; i++) अणु
		अगर (!ce->variant->ce_clks[i].name)
			जारी;
		ce->ceclks[i] = devm_clk_get(ce->dev, ce->variant->ce_clks[i].name);
		अगर (IS_ERR(ce->ceclks[i])) अणु
			err = PTR_ERR(ce->ceclks[i]);
			dev_err(ce->dev, "Cannot get %s CE clock err=%d\n",
				ce->variant->ce_clks[i].name, err);
			वापस err;
		पूर्ण
		cr = clk_get_rate(ce->ceclks[i]);
		अगर (!cr)
			वापस -EINVAL;
		अगर (ce->variant->ce_clks[i].freq > 0 &&
		    cr != ce->variant->ce_clks[i].freq) अणु
			dev_info(ce->dev, "Set %s clock to %lu (%lu Mhz) from %lu (%lu Mhz)\n",
				 ce->variant->ce_clks[i].name,
				 ce->variant->ce_clks[i].freq,
				 ce->variant->ce_clks[i].freq / 1000000,
				 cr, cr / 1000000);
			err = clk_set_rate(ce->ceclks[i], ce->variant->ce_clks[i].freq);
			अगर (err)
				dev_err(ce->dev, "Fail to set %s clk speed to %lu hz\n",
					ce->variant->ce_clks[i].name,
					ce->variant->ce_clks[i].freq);
		पूर्ण
		अगर (ce->variant->ce_clks[i].max_freq > 0 &&
		    cr > ce->variant->ce_clks[i].max_freq)
			dev_warn(ce->dev, "Frequency for %s (%lu hz) is higher than datasheet's recommendation (%lu hz)",
				 ce->variant->ce_clks[i].name, cr,
				 ce->variant->ce_clks[i].max_freq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ce_रेजिस्टर_algs(काष्ठा sun8i_ce_dev *ce)
अणु
	पूर्णांक ce_method, err, id;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ce_algs); i++) अणु
		ce_algs[i].ce = ce;
		चयन (ce_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			id = ce_algs[i].ce_algo_id;
			ce_method = ce->variant->alg_cipher[id];
			अगर (ce_method == CE_ID_NOTSUPP) अणु
				dev_dbg(ce->dev,
					"DEBUG: Algo of %s not supported\n",
					ce_algs[i].alg.skcipher.base.cra_name);
				ce_algs[i].ce = शून्य;
				अवरोध;
			पूर्ण
			id = ce_algs[i].ce_blockmode;
			ce_method = ce->variant->op_mode[id];
			अगर (ce_method == CE_ID_NOTSUPP) अणु
				dev_dbg(ce->dev, "DEBUG: Blockmode of %s not supported\n",
					ce_algs[i].alg.skcipher.base.cra_name);
				ce_algs[i].ce = शून्य;
				अवरोध;
			पूर्ण
			dev_info(ce->dev, "Register %s\n",
				 ce_algs[i].alg.skcipher.base.cra_name);
			err = crypto_रेजिस्टर_skcipher(&ce_algs[i].alg.skcipher);
			अगर (err) अणु
				dev_err(ce->dev, "ERROR: Fail to register %s\n",
					ce_algs[i].alg.skcipher.base.cra_name);
				ce_algs[i].ce = शून्य;
				वापस err;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			id = ce_algs[i].ce_algo_id;
			ce_method = ce->variant->alg_hash[id];
			अगर (ce_method == CE_ID_NOTSUPP) अणु
				dev_info(ce->dev,
					 "DEBUG: Algo of %s not supported\n",
					 ce_algs[i].alg.hash.halg.base.cra_name);
				ce_algs[i].ce = शून्य;
				अवरोध;
			पूर्ण
			dev_info(ce->dev, "Register %s\n",
				 ce_algs[i].alg.hash.halg.base.cra_name);
			err = crypto_रेजिस्टर_ahash(&ce_algs[i].alg.hash);
			अगर (err) अणु
				dev_err(ce->dev, "ERROR: Fail to register %s\n",
					ce_algs[i].alg.hash.halg.base.cra_name);
				ce_algs[i].ce = शून्य;
				वापस err;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			अगर (ce->variant->prng == CE_ID_NOTSUPP) अणु
				dev_info(ce->dev,
					 "DEBUG: Algo of %s not supported\n",
					 ce_algs[i].alg.rng.base.cra_name);
				ce_algs[i].ce = शून्य;
				अवरोध;
			पूर्ण
			dev_info(ce->dev, "Register %s\n",
				 ce_algs[i].alg.rng.base.cra_name);
			err = crypto_रेजिस्टर_rng(&ce_algs[i].alg.rng);
			अगर (err) अणु
				dev_err(ce->dev, "Fail to register %s\n",
					ce_algs[i].alg.rng.base.cra_name);
				ce_algs[i].ce = शून्य;
			पूर्ण
			अवरोध;
		शेष:
			ce_algs[i].ce = शून्य;
			dev_err(ce->dev, "ERROR: tried to register an unknown algo\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sun8i_ce_unरेजिस्टर_algs(काष्ठा sun8i_ce_dev *ce)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ce_algs); i++) अणु
		अगर (!ce_algs[i].ce)
			जारी;
		चयन (ce_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			dev_info(ce->dev, "Unregister %d %s\n", i,
				 ce_algs[i].alg.skcipher.base.cra_name);
			crypto_unरेजिस्टर_skcipher(&ce_algs[i].alg.skcipher);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			dev_info(ce->dev, "Unregister %d %s\n", i,
				 ce_algs[i].alg.hash.halg.base.cra_name);
			crypto_unरेजिस्टर_ahash(&ce_algs[i].alg.hash);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			dev_info(ce->dev, "Unregister %d %s\n", i,
				 ce_algs[i].alg.rng.base.cra_name);
			crypto_unरेजिस्टर_rng(&ce_algs[i].alg.rng);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sun8i_ce_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun8i_ce_dev *ce;
	पूर्णांक err, irq;
	u32 v;

	ce = devm_kzalloc(&pdev->dev, माप(*ce), GFP_KERNEL);
	अगर (!ce)
		वापस -ENOMEM;

	ce->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ce);

	ce->variant = of_device_get_match_data(&pdev->dev);
	अगर (!ce->variant) अणु
		dev_err(&pdev->dev, "Missing Crypto Engine variant\n");
		वापस -EINVAL;
	पूर्ण

	ce->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ce->base))
		वापस PTR_ERR(ce->base);

	err = sun8i_ce_get_clks(ce);
	अगर (err)
		वापस err;

	/* Get Non Secure IRQ */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ce->reset = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ce->reset))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(ce->reset),
				     "No reset control found\n");

	mutex_init(&ce->mlock);
	mutex_init(&ce->rnglock);

	err = sun8i_ce_allocate_chanlist(ce);
	अगर (err)
		वापस err;

	err = sun8i_ce_pm_init(ce);
	अगर (err)
		जाओ error_pm;

	err = devm_request_irq(&pdev->dev, irq, ce_irq_handler, 0,
			       "sun8i-ce-ns", ce);
	अगर (err) अणु
		dev_err(ce->dev, "Cannot request CryptoEngine Non-secure IRQ (err=%d)\n", err);
		जाओ error_irq;
	पूर्ण

	err = sun8i_ce_रेजिस्टर_algs(ce);
	अगर (err)
		जाओ error_alg;

	err = pm_runसमय_resume_and_get(ce->dev);
	अगर (err < 0)
		जाओ error_alg;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_TRNG
	sun8i_ce_hwrng_रेजिस्टर(ce);
#पूर्ण_अगर

	v = पढ़ोl(ce->base + CE_CTR);
	v >>= CE_DIE_ID_SHIFT;
	v &= CE_DIE_ID_MASK;
	dev_info(&pdev->dev, "CryptoEngine Die ID %x\n", v);

	pm_runसमय_put_sync(ce->dev);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	/* Ignore error of debugfs */
	ce->dbgfs_dir = debugfs_create_dir("sun8i-ce", शून्य);
	ce->dbgfs_stats = debugfs_create_file("stats", 0444,
					      ce->dbgfs_dir, ce,
					      &sun8i_ce_debugfs_fops);
#पूर्ण_अगर

	वापस 0;
error_alg:
	sun8i_ce_unरेजिस्टर_algs(ce);
error_irq:
	sun8i_ce_pm_निकास(ce);
error_pm:
	sun8i_ce_मुक्त_chanlist(ce, MAXFLOW - 1);
	वापस err;
पूर्ण

अटल पूर्णांक sun8i_ce_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun8i_ce_dev *ce = platक्रमm_get_drvdata(pdev);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_TRNG
	sun8i_ce_hwrng_unरेजिस्टर(ce);
#पूर्ण_अगर

	sun8i_ce_unरेजिस्टर_algs(ce);

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	debugfs_हटाओ_recursive(ce->dbgfs_dir);
#पूर्ण_अगर

	sun8i_ce_मुक्त_chanlist(ce, MAXFLOW - 1);

	sun8i_ce_pm_निकास(ce);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun8i_ce_crypto_of_match_table[] = अणु
	अणु .compatible = "allwinner,sun8i-h3-crypto",
	  .data = &ce_h3_variant पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-crypto",
	  .data = &ce_r40_variant पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-crypto",
	  .data = &ce_a64_variant पूर्ण,
	अणु .compatible = "allwinner,sun50i-h5-crypto",
	  .data = &ce_h5_variant पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-crypto",
	  .data = &ce_h6_variant पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_ce_crypto_of_match_table);

अटल काष्ठा platक्रमm_driver sun8i_ce_driver = अणु
	.probe		 = sun8i_ce_probe,
	.हटाओ		 = sun8i_ce_हटाओ,
	.driver		 = अणु
		.name		= "sun8i-ce",
		.pm		= &sun8i_ce_pm_ops,
		.of_match_table	= sun8i_ce_crypto_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sun8i_ce_driver);

MODULE_DESCRIPTION("Allwinner Crypto Engine cryptographic offloader");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corentin Labbe <clabbe.montjoie@gmail.com>");
