<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#समावेश "cipher.h"
#समावेश "common.h"
#समावेश "core.h"
#समावेश "regs-v5.h"
#समावेश "sha.h"

अटल अंतरभूत u32 qce_पढ़ो(काष्ठा qce_device *qce, u32 offset)
अणु
	वापस पढ़ोl(qce->base + offset);
पूर्ण

अटल अंतरभूत व्योम qce_ग_लिखो(काष्ठा qce_device *qce, u32 offset, u32 val)
अणु
	ग_लिखोl(val, qce->base + offset);
पूर्ण

अटल अंतरभूत व्योम qce_ग_लिखो_array(काष्ठा qce_device *qce, u32 offset,
				   स्थिर u32 *val, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		qce_ग_लिखो(qce, offset + i * माप(u32), val[i]);
पूर्ण

अटल अंतरभूत व्योम
qce_clear_array(काष्ठा qce_device *qce, u32 offset, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		qce_ग_लिखो(qce, offset + i * माप(u32), 0);
पूर्ण

अटल u32 qce_config_reg(काष्ठा qce_device *qce, पूर्णांक little)
अणु
	u32 beats = (qce->burst_size >> 3) - 1;
	u32 pipe_pair = qce->pipe_pair_id;
	u32 config;

	config = (beats << REQ_SIZE_SHIFT) & REQ_SIZE_MASK;
	config |= BIT(MASK_DOUT_INTR_SHIFT) | BIT(MASK_DIN_INTR_SHIFT) |
		  BIT(MASK_OP_DONE_INTR_SHIFT) | BIT(MASK_ERR_INTR_SHIFT);
	config |= (pipe_pair << PIPE_SET_SELECT_SHIFT) & PIPE_SET_SELECT_MASK;
	config &= ~HIGH_SPD_EN_N_SHIFT;

	अगर (little)
		config |= BIT(LITTLE_ENDIAN_MODE_SHIFT);

	वापस config;
पूर्ण

व्योम qce_cpu_to_be32p_array(__be32 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक len)
अणु
	__be32 *d = dst;
	स्थिर u8 *s = src;
	अचिन्हित पूर्णांक n;

	n = len / माप(u32);
	क्रम (; n > 0; n--) अणु
		*d = cpu_to_be32p((स्थिर __u32 *) s);
		s += माप(__u32);
		d++;
	पूर्ण
पूर्ण

अटल व्योम qce_setup_config(काष्ठा qce_device *qce)
अणु
	u32 config;

	/* get big endianness */
	config = qce_config_reg(qce, 0);

	/* clear status */
	qce_ग_लिखो(qce, REG_STATUS, 0);
	qce_ग_लिखो(qce, REG_CONFIG, config);
पूर्ण

अटल अंतरभूत व्योम qce_crypto_go(काष्ठा qce_device *qce)
अणु
	qce_ग_लिखो(qce, REG_GOPROC, BIT(GO_SHIFT) | BIT(RESULTS_DUMP_SHIFT));
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_QCE_SHA
अटल u32 qce_auth_cfg(अचिन्हित दीर्घ flags, u32 key_size)
अणु
	u32 cfg = 0;

	अगर (IS_AES(flags) && (IS_CCM(flags) || IS_CMAC(flags)))
		cfg |= AUTH_ALG_AES << AUTH_ALG_SHIFT;
	अन्यथा
		cfg |= AUTH_ALG_SHA << AUTH_ALG_SHIFT;

	अगर (IS_CCM(flags) || IS_CMAC(flags)) अणु
		अगर (key_size == AES_KEYSIZE_128)
			cfg |= AUTH_KEY_SZ_AES128 << AUTH_KEY_SIZE_SHIFT;
		अन्यथा अगर (key_size == AES_KEYSIZE_256)
			cfg |= AUTH_KEY_SZ_AES256 << AUTH_KEY_SIZE_SHIFT;
	पूर्ण

	अगर (IS_SHA1(flags) || IS_SHA1_HMAC(flags))
		cfg |= AUTH_SIZE_SHA1 << AUTH_SIZE_SHIFT;
	अन्यथा अगर (IS_SHA256(flags) || IS_SHA256_HMAC(flags))
		cfg |= AUTH_SIZE_SHA256 << AUTH_SIZE_SHIFT;
	अन्यथा अगर (IS_CMAC(flags))
		cfg |= AUTH_SIZE_ENUM_16_BYTES << AUTH_SIZE_SHIFT;

	अगर (IS_SHA1(flags) || IS_SHA256(flags))
		cfg |= AUTH_MODE_HASH << AUTH_MODE_SHIFT;
	अन्यथा अगर (IS_SHA1_HMAC(flags) || IS_SHA256_HMAC(flags) ||
		 IS_CBC(flags) || IS_CTR(flags))
		cfg |= AUTH_MODE_HMAC << AUTH_MODE_SHIFT;
	अन्यथा अगर (IS_AES(flags) && IS_CCM(flags))
		cfg |= AUTH_MODE_CCM << AUTH_MODE_SHIFT;
	अन्यथा अगर (IS_AES(flags) && IS_CMAC(flags))
		cfg |= AUTH_MODE_CMAC << AUTH_MODE_SHIFT;

	अगर (IS_SHA(flags) || IS_SHA_HMAC(flags))
		cfg |= AUTH_POS_BEFORE << AUTH_POS_SHIFT;

	अगर (IS_CCM(flags))
		cfg |= QCE_MAX_NONCE_WORDS << AUTH_NONCE_NUM_WORDS_SHIFT;

	अगर (IS_CBC(flags) || IS_CTR(flags) || IS_CCM(flags) ||
	    IS_CMAC(flags))
		cfg |= BIT(AUTH_LAST_SHIFT) | BIT(AUTH_FIRST_SHIFT);

	वापस cfg;
पूर्ण

अटल पूर्णांक qce_setup_regs_ahash(काष्ठा crypto_async_request *async_req)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(async_req);
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(async_req->tfm);
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(async_req->tfm);
	काष्ठा qce_device *qce = पंचांगpl->qce;
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	अचिन्हित पूर्णांक blocksize = crypto_tfm_alg_blocksize(async_req->tfm);
	__be32 auth[SHA256_DIGEST_SIZE / माप(__be32)] = अणु0पूर्ण;
	__be32 mackey[QCE_SHA_HMAC_KEY_SIZE / माप(__be32)] = अणु0पूर्ण;
	u32 auth_cfg = 0, config;
	अचिन्हित पूर्णांक iv_words;

	/* अगर not the last, the size has to be on the block boundary */
	अगर (!rctx->last_blk && req->nbytes % blocksize)
		वापस -EINVAL;

	qce_setup_config(qce);

	अगर (IS_CMAC(rctx->flags)) अणु
		qce_ग_लिखो(qce, REG_AUTH_SEG_CFG, 0);
		qce_ग_लिखो(qce, REG_ENCR_SEG_CFG, 0);
		qce_ग_लिखो(qce, REG_ENCR_SEG_SIZE, 0);
		qce_clear_array(qce, REG_AUTH_IV0, 16);
		qce_clear_array(qce, REG_AUTH_KEY0, 16);
		qce_clear_array(qce, REG_AUTH_BYTECNT0, 4);

		auth_cfg = qce_auth_cfg(rctx->flags, rctx->authklen);
	पूर्ण

	अगर (IS_SHA_HMAC(rctx->flags) || IS_CMAC(rctx->flags)) अणु
		u32 authkey_words = rctx->authklen / माप(u32);

		qce_cpu_to_be32p_array(mackey, rctx->authkey, rctx->authklen);
		qce_ग_लिखो_array(qce, REG_AUTH_KEY0, (u32 *)mackey,
				authkey_words);
	पूर्ण

	अगर (IS_CMAC(rctx->flags))
		जाओ go_proc;

	अगर (rctx->first_blk)
		स_नकल(auth, rctx->digest, digestsize);
	अन्यथा
		qce_cpu_to_be32p_array(auth, rctx->digest, digestsize);

	iv_words = (IS_SHA1(rctx->flags) || IS_SHA1_HMAC(rctx->flags)) ? 5 : 8;
	qce_ग_लिखो_array(qce, REG_AUTH_IV0, (u32 *)auth, iv_words);

	अगर (rctx->first_blk)
		qce_clear_array(qce, REG_AUTH_BYTECNT0, 4);
	अन्यथा
		qce_ग_लिखो_array(qce, REG_AUTH_BYTECNT0,
				(u32 *)rctx->byte_count, 2);

	auth_cfg = qce_auth_cfg(rctx->flags, 0);

	अगर (rctx->last_blk)
		auth_cfg |= BIT(AUTH_LAST_SHIFT);
	अन्यथा
		auth_cfg &= ~BIT(AUTH_LAST_SHIFT);

	अगर (rctx->first_blk)
		auth_cfg |= BIT(AUTH_FIRST_SHIFT);
	अन्यथा
		auth_cfg &= ~BIT(AUTH_FIRST_SHIFT);

go_proc:
	qce_ग_लिखो(qce, REG_AUTH_SEG_CFG, auth_cfg);
	qce_ग_लिखो(qce, REG_AUTH_SEG_SIZE, req->nbytes);
	qce_ग_लिखो(qce, REG_AUTH_SEG_START, 0);
	qce_ग_लिखो(qce, REG_ENCR_SEG_CFG, 0);
	qce_ग_लिखो(qce, REG_SEG_SIZE, req->nbytes);

	/* get little endianness */
	config = qce_config_reg(qce, 1);
	qce_ग_लिखो(qce, REG_CONFIG, config);

	qce_crypto_go(qce);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRYPTO_DEV_QCE_SKCIPHER
अटल u32 qce_encr_cfg(अचिन्हित दीर्घ flags, u32 aes_key_size)
अणु
	u32 cfg = 0;

	अगर (IS_AES(flags)) अणु
		अगर (aes_key_size == AES_KEYSIZE_128)
			cfg |= ENCR_KEY_SZ_AES128 << ENCR_KEY_SZ_SHIFT;
		अन्यथा अगर (aes_key_size == AES_KEYSIZE_256)
			cfg |= ENCR_KEY_SZ_AES256 << ENCR_KEY_SZ_SHIFT;
	पूर्ण

	अगर (IS_AES(flags))
		cfg |= ENCR_ALG_AES << ENCR_ALG_SHIFT;
	अन्यथा अगर (IS_DES(flags) || IS_3DES(flags))
		cfg |= ENCR_ALG_DES << ENCR_ALG_SHIFT;

	अगर (IS_DES(flags))
		cfg |= ENCR_KEY_SZ_DES << ENCR_KEY_SZ_SHIFT;

	अगर (IS_3DES(flags))
		cfg |= ENCR_KEY_SZ_3DES << ENCR_KEY_SZ_SHIFT;

	चयन (flags & QCE_MODE_MASK) अणु
	हाल QCE_MODE_ECB:
		cfg |= ENCR_MODE_ECB << ENCR_MODE_SHIFT;
		अवरोध;
	हाल QCE_MODE_CBC:
		cfg |= ENCR_MODE_CBC << ENCR_MODE_SHIFT;
		अवरोध;
	हाल QCE_MODE_CTR:
		cfg |= ENCR_MODE_CTR << ENCR_MODE_SHIFT;
		अवरोध;
	हाल QCE_MODE_XTS:
		cfg |= ENCR_MODE_XTS << ENCR_MODE_SHIFT;
		अवरोध;
	हाल QCE_MODE_CCM:
		cfg |= ENCR_MODE_CCM << ENCR_MODE_SHIFT;
		cfg |= LAST_CCM_XFR << LAST_CCM_SHIFT;
		अवरोध;
	शेष:
		वापस ~0;
	पूर्ण

	वापस cfg;
पूर्ण

अटल व्योम qce_xts_swapiv(__be32 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक ivsize)
अणु
	u8 swap[QCE_AES_IV_LENGTH];
	u32 i, j;

	अगर (ivsize > QCE_AES_IV_LENGTH)
		वापस;

	स_रखो(swap, 0, QCE_AES_IV_LENGTH);

	क्रम (i = (QCE_AES_IV_LENGTH - ivsize), j = ivsize - 1;
	     i < QCE_AES_IV_LENGTH; i++, j--)
		swap[i] = src[j];

	qce_cpu_to_be32p_array(dst, swap, QCE_AES_IV_LENGTH);
पूर्ण

अटल व्योम qce_xtskey(काष्ठा qce_device *qce, स्थिर u8 *enckey,
		       अचिन्हित पूर्णांक enckeylen, अचिन्हित पूर्णांक cryptlen)
अणु
	u32 xtskey[QCE_MAX_CIPHER_KEY_SIZE / माप(u32)] = अणु0पूर्ण;
	अचिन्हित पूर्णांक xtsklen = enckeylen / (2 * माप(u32));

	qce_cpu_to_be32p_array((__be32 *)xtskey, enckey + enckeylen / 2,
			       enckeylen / 2);
	qce_ग_लिखो_array(qce, REG_ENCR_XTS_KEY0, xtskey, xtsklen);

	/* Set data unit size to cryptlen. Anything अन्यथा causes
	 * crypto engine to वापस back incorrect results.
	 */
	qce_ग_लिखो(qce, REG_ENCR_XTS_DU_SIZE, cryptlen);
पूर्ण

अटल पूर्णांक qce_setup_regs_skcipher(काष्ठा crypto_async_request *async_req)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा qce_cipher_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा qce_cipher_ctx *ctx = crypto_tfm_ctx(async_req->tfm);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_cipher_पंचांगpl(crypto_skcipher_reqtfm(req));
	काष्ठा qce_device *qce = पंचांगpl->qce;
	__be32 enckey[QCE_MAX_CIPHER_KEY_SIZE / माप(__be32)] = अणु0पूर्ण;
	__be32 enciv[QCE_MAX_IV_SIZE / माप(__be32)] = अणु0पूर्ण;
	अचिन्हित पूर्णांक enckey_words, enciv_words;
	अचिन्हित पूर्णांक keylen;
	u32 encr_cfg = 0, auth_cfg = 0, config;
	अचिन्हित पूर्णांक ivsize = rctx->ivsize;
	अचिन्हित दीर्घ flags = rctx->flags;

	qce_setup_config(qce);

	अगर (IS_XTS(flags))
		keylen = ctx->enc_keylen / 2;
	अन्यथा
		keylen = ctx->enc_keylen;

	qce_cpu_to_be32p_array(enckey, ctx->enc_key, keylen);
	enckey_words = keylen / माप(u32);

	qce_ग_लिखो(qce, REG_AUTH_SEG_CFG, auth_cfg);

	encr_cfg = qce_encr_cfg(flags, keylen);

	अगर (IS_DES(flags)) अणु
		enciv_words = 2;
		enckey_words = 2;
	पूर्ण अन्यथा अगर (IS_3DES(flags)) अणु
		enciv_words = 2;
		enckey_words = 6;
	पूर्ण अन्यथा अगर (IS_AES(flags)) अणु
		अगर (IS_XTS(flags))
			qce_xtskey(qce, ctx->enc_key, ctx->enc_keylen,
				   rctx->cryptlen);
		enciv_words = 4;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	qce_ग_लिखो_array(qce, REG_ENCR_KEY0, (u32 *)enckey, enckey_words);

	अगर (!IS_ECB(flags)) अणु
		अगर (IS_XTS(flags))
			qce_xts_swapiv(enciv, rctx->iv, ivsize);
		अन्यथा
			qce_cpu_to_be32p_array(enciv, rctx->iv, ivsize);

		qce_ग_लिखो_array(qce, REG_CNTR0_IV0, (u32 *)enciv, enciv_words);
	पूर्ण

	अगर (IS_ENCRYPT(flags))
		encr_cfg |= BIT(ENCODE_SHIFT);

	qce_ग_लिखो(qce, REG_ENCR_SEG_CFG, encr_cfg);
	qce_ग_लिखो(qce, REG_ENCR_SEG_SIZE, rctx->cryptlen);
	qce_ग_लिखो(qce, REG_ENCR_SEG_START, 0);

	अगर (IS_CTR(flags)) अणु
		qce_ग_लिखो(qce, REG_CNTR_MASK, ~0);
		qce_ग_लिखो(qce, REG_CNTR_MASK0, ~0);
		qce_ग_लिखो(qce, REG_CNTR_MASK1, ~0);
		qce_ग_लिखो(qce, REG_CNTR_MASK2, ~0);
	पूर्ण

	qce_ग_लिखो(qce, REG_SEG_SIZE, rctx->cryptlen);

	/* get little endianness */
	config = qce_config_reg(qce, 1);
	qce_ग_लिखो(qce, REG_CONFIG, config);

	qce_crypto_go(qce);

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक qce_start(काष्ठा crypto_async_request *async_req, u32 type)
अणु
	चयन (type) अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_QCE_SKCIPHER
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		वापस qce_setup_regs_skcipher(async_req);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_QCE_SHA
	हाल CRYPTO_ALG_TYPE_AHASH:
		वापस qce_setup_regs_ahash(async_req);
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा STATUS_ERRORS	\
		(BIT(SW_ERR_SHIFT) | BIT(AXI_ERR_SHIFT) | BIT(HSD_ERR_SHIFT))

पूर्णांक qce_check_status(काष्ठा qce_device *qce, u32 *status)
अणु
	पूर्णांक ret = 0;

	*status = qce_पढ़ो(qce, REG_STATUS);

	/*
	 * Don't use result dump status. The operation may not be complete.
	 * Instead, use the status we just पढ़ो from device. In हाल, we need to
	 * use result_status from result dump the result_status needs to be byte
	 * swapped, since we set the device to little endian.
	 */
	अगर (*status & STATUS_ERRORS || !(*status & BIT(OPERATION_DONE_SHIFT)))
		ret = -ENXIO;

	वापस ret;
पूर्ण

व्योम qce_get_version(काष्ठा qce_device *qce, u32 *major, u32 *minor, u32 *step)
अणु
	u32 val;

	val = qce_पढ़ो(qce, REG_VERSION);
	*major = (val & CORE_MAJOR_REV_MASK) >> CORE_MAJOR_REV_SHIFT;
	*minor = (val & CORE_MINOR_REV_MASK) >> CORE_MINOR_REV_SHIFT;
	*step = (val & CORE_STEP_REV_MASK) >> CORE_STEP_REV_SHIFT;
पूर्ण
