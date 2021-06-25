<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/xts.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_common.h"
#समावेश "nitrox_req.h"

काष्ठा nitrox_cipher अणु
	स्थिर अक्षर *name;
	क्रमागत flexi_cipher value;
पूर्ण;

/**
 * supported cipher list
 */
अटल स्थिर काष्ठा nitrox_cipher flexi_cipher_table[] = अणु
	अणु "null",		CIPHER_शून्य पूर्ण,
	अणु "cbc(des3_ede)",	CIPHER_3DES_CBC पूर्ण,
	अणु "ecb(des3_ede)",	CIPHER_3DES_ECB पूर्ण,
	अणु "cbc(aes)",		CIPHER_AES_CBC पूर्ण,
	अणु "ecb(aes)",		CIPHER_AES_ECB पूर्ण,
	अणु "cfb(aes)",		CIPHER_AES_CFB पूर्ण,
	अणु "rfc3686(ctr(aes))",	CIPHER_AES_CTR पूर्ण,
	अणु "xts(aes)",		CIPHER_AES_XTS पूर्ण,
	अणु "cts(cbc(aes))",	CIPHER_AES_CBC_CTS पूर्ण,
	अणु शून्य,			CIPHER_INVALID पूर्ण
पूर्ण;

अटल क्रमागत flexi_cipher flexi_cipher_type(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा nitrox_cipher *cipher = flexi_cipher_table;

	जबतक (cipher->name) अणु
		अगर (!म_भेद(cipher->name, name))
			अवरोध;
		cipher++;
	पूर्ण
	वापस cipher->value;
पूर्ण

अटल व्योम मुक्त_src_sglist(काष्ठा skcipher_request *skreq)
अणु
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);

	kमुक्त(nkreq->src);
पूर्ण

अटल व्योम मुक्त_dst_sglist(काष्ठा skcipher_request *skreq)
अणु
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);

	kमुक्त(nkreq->dst);
पूर्ण

अटल व्योम nitrox_skcipher_callback(व्योम *arg, पूर्णांक err)
अणु
	काष्ठा skcipher_request *skreq = arg;

	मुक्त_src_sglist(skreq);
	मुक्त_dst_sglist(skreq);
	अगर (err) अणु
		pr_err_ratelimited("request failed status 0x%0x\n", err);
		err = -EINVAL;
	पूर्ण

	skcipher_request_complete(skreq, err);
पूर्ण

अटल व्योम nitrox_cbc_cipher_callback(व्योम *arg, पूर्णांक err)
अणु
	काष्ठा skcipher_request *skreq = arg;
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(skreq);
	पूर्णांक ivsize = crypto_skcipher_ivsize(cipher);
	अचिन्हित पूर्णांक start = skreq->cryptlen - ivsize;

	अगर (err) अणु
		nitrox_skcipher_callback(arg, err);
		वापस;
	पूर्ण

	अगर (nkreq->creq.ctrl.s.arg == ENCRYPT) अणु
		scatterwalk_map_and_copy(skreq->iv, skreq->dst, start, ivsize,
					 0);
	पूर्ण अन्यथा अणु
		अगर (skreq->src != skreq->dst) अणु
			scatterwalk_map_and_copy(skreq->iv, skreq->src, start,
						 ivsize, 0);
		पूर्ण अन्यथा अणु
			स_नकल(skreq->iv, nkreq->iv_out, ivsize);
			kमुक्त(nkreq->iv_out);
		पूर्ण
	पूर्ण

	nitrox_skcipher_callback(arg, err);
पूर्ण

अटल पूर्णांक nitrox_skcipher_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा nitrox_crypto_ctx *nctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_ctx_hdr *chdr;

	/* get the first device */
	nctx->ndev = nitrox_get_first_device();
	अगर (!nctx->ndev)
		वापस -ENODEV;

	/* allocate nitrox crypto context */
	chdr = crypto_alloc_context(nctx->ndev);
	अगर (!chdr) अणु
		nitrox_put_device(nctx->ndev);
		वापस -ENOMEM;
	पूर्ण

	nctx->callback = nitrox_skcipher_callback;
	nctx->chdr = chdr;
	nctx->u.ctx_handle = (uपूर्णांकptr_t)((u8 *)chdr->vaddr +
					 माप(काष्ठा ctx_hdr));
	crypto_skcipher_set_reqsize(tfm, crypto_skcipher_reqsize(tfm) +
				    माप(काष्ठा nitrox_kcrypt_request));
	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_cbc_init(काष्ठा crypto_skcipher *tfm)
अणु
	पूर्णांक err;
	काष्ठा nitrox_crypto_ctx *nctx = crypto_skcipher_ctx(tfm);

	err = nitrox_skcipher_init(tfm);
	अगर (err)
		वापस err;

	nctx->callback = nitrox_cbc_cipher_callback;
	वापस 0;
पूर्ण

अटल व्योम nitrox_skcipher_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा nitrox_crypto_ctx *nctx = crypto_skcipher_ctx(tfm);

	/* मुक्त the nitrox crypto context */
	अगर (nctx->u.ctx_handle) अणु
		काष्ठा flexi_crypto_context *fctx = nctx->u.fctx;

		memzero_explicit(&fctx->crypto, माप(काष्ठा crypto_keys));
		memzero_explicit(&fctx->auth, माप(काष्ठा auth_keys));
		crypto_मुक्त_context((व्योम *)nctx->chdr);
	पूर्ण
	nitrox_put_device(nctx->ndev);

	nctx->u.ctx_handle = 0;
	nctx->ndev = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक nitrox_skcipher_setkey(काष्ठा crypto_skcipher *cipher,
					 पूर्णांक aes_keylen, स्थिर u8 *key,
					 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_tfm_ctx(tfm);
	काष्ठा flexi_crypto_context *fctx;
	जोड़ fc_ctx_flags *flags;
	क्रमागत flexi_cipher cipher_type;
	स्थिर अक्षर *name;

	name = crypto_tfm_alg_name(tfm);
	cipher_type = flexi_cipher_type(name);
	अगर (unlikely(cipher_type == CIPHER_INVALID)) अणु
		pr_err("unsupported cipher: %s\n", name);
		वापस -EINVAL;
	पूर्ण

	/* fill crypto context */
	fctx = nctx->u.fctx;
	flags = &fctx->flags;
	flags->f = 0;
	flags->w0.cipher_type = cipher_type;
	flags->w0.aes_keylen = aes_keylen;
	flags->w0.iv_source = IV_FROM_DPTR;
	flags->f = cpu_to_be64(*(u64 *)&flags->w0);
	/* copy the key to context */
	स_नकल(fctx->crypto.u.key, key, keylen);

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_aes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	पूर्णांक aes_keylen;

	aes_keylen = flexi_aes_keylen(keylen);
	अगर (aes_keylen < 0)
		वापस -EINVAL;
	वापस nitrox_skcipher_setkey(cipher, aes_keylen, key, keylen);
पूर्ण

अटल पूर्णांक alloc_src_sglist(काष्ठा skcipher_request *skreq, पूर्णांक ivsize)
अणु
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	पूर्णांक nents = sg_nents(skreq->src) + 1;
	पूर्णांक ret;

	/* Allocate buffer to hold IV and input scatterlist array */
	ret = alloc_src_req_buf(nkreq, nents, ivsize);
	अगर (ret)
		वापस ret;

	nitrox_creq_copy_iv(nkreq->src, skreq->iv, ivsize);
	nitrox_creq_set_src_sg(nkreq, nents, ivsize, skreq->src,
			       skreq->cryptlen);

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_dst_sglist(काष्ठा skcipher_request *skreq, पूर्णांक ivsize)
अणु
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	पूर्णांक nents = sg_nents(skreq->dst) + 3;
	पूर्णांक ret;

	/* Allocate buffer to hold ORH, COMPLETION and output scatterlist
	 * array
	 */
	ret = alloc_dst_req_buf(nkreq, nents);
	अगर (ret)
		वापस ret;

	nitrox_creq_set_orh(nkreq);
	nitrox_creq_set_comp(nkreq);
	nitrox_creq_set_dst_sg(nkreq, nents, ivsize, skreq->dst,
			       skreq->cryptlen);

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_skcipher_crypt(काष्ठा skcipher_request *skreq, bool enc)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(skreq);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_skcipher_ctx(cipher);
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	पूर्णांक ivsize = crypto_skcipher_ivsize(cipher);
	काष्ठा se_crypto_request *creq;
	पूर्णांक ret;

	creq = &nkreq->creq;
	creq->flags = skreq->base.flags;
	creq->gfp = (skreq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		     GFP_KERNEL : GFP_ATOMIC;

	/* fill the request */
	creq->ctrl.value = 0;
	creq->opcode = FLEXI_CRYPTO_ENCRYPT_HMAC;
	creq->ctrl.s.arg = (enc ? ENCRYPT : DECRYPT);
	/* param0: length of the data to be encrypted */
	creq->gph.param0 = cpu_to_be16(skreq->cryptlen);
	creq->gph.param1 = 0;
	/* param2: encryption data offset */
	creq->gph.param2 = cpu_to_be16(ivsize);
	creq->gph.param3 = 0;

	creq->ctx_handle = nctx->u.ctx_handle;
	creq->ctrl.s.ctxl = माप(काष्ठा flexi_crypto_context);

	ret = alloc_src_sglist(skreq, ivsize);
	अगर (ret)
		वापस ret;

	ret = alloc_dst_sglist(skreq, ivsize);
	अगर (ret) अणु
		मुक्त_src_sglist(skreq);
		वापस ret;
	पूर्ण

	/* send the crypto request */
	वापस nitrox_process_se_request(nctx->ndev, creq, nctx->callback,
					 skreq);
पूर्ण

अटल पूर्णांक nitrox_cbc_decrypt(काष्ठा skcipher_request *skreq)
अणु
	काष्ठा nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(skreq);
	पूर्णांक ivsize = crypto_skcipher_ivsize(cipher);
	gfp_t flags = (skreq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
			GFP_KERNEL : GFP_ATOMIC;
	अचिन्हित पूर्णांक start = skreq->cryptlen - ivsize;

	अगर (skreq->src != skreq->dst)
		वापस nitrox_skcipher_crypt(skreq, false);

	nkreq->iv_out = kदो_स्मृति(ivsize, flags);
	अगर (!nkreq->iv_out)
		वापस -ENOMEM;

	scatterwalk_map_and_copy(nkreq->iv_out, skreq->src, start, ivsize, 0);
	वापस nitrox_skcipher_crypt(skreq, false);
पूर्ण

अटल पूर्णांक nitrox_aes_encrypt(काष्ठा skcipher_request *skreq)
अणु
	वापस nitrox_skcipher_crypt(skreq, true);
पूर्ण

अटल पूर्णांक nitrox_aes_decrypt(काष्ठा skcipher_request *skreq)
अणु
	वापस nitrox_skcipher_crypt(skreq, false);
पूर्ण

अटल पूर्णांक nitrox_3des_setkey(काष्ठा crypto_skcipher *cipher,
			      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(cipher, key) ?:
	       nitrox_skcipher_setkey(cipher, 0, key, keylen);
पूर्ण

अटल पूर्णांक nitrox_3des_encrypt(काष्ठा skcipher_request *skreq)
अणु
	वापस nitrox_skcipher_crypt(skreq, true);
पूर्ण

अटल पूर्णांक nitrox_3des_decrypt(काष्ठा skcipher_request *skreq)
अणु
	वापस nitrox_skcipher_crypt(skreq, false);
पूर्ण

अटल पूर्णांक nitrox_aes_xts_setkey(काष्ठा crypto_skcipher *cipher,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_tfm_ctx(tfm);
	काष्ठा flexi_crypto_context *fctx;
	पूर्णांक aes_keylen, ret;

	ret = xts_check_key(tfm, key, keylen);
	अगर (ret)
		वापस ret;

	keylen /= 2;

	aes_keylen = flexi_aes_keylen(keylen);
	अगर (aes_keylen < 0)
		वापस -EINVAL;

	fctx = nctx->u.fctx;
	/* copy KEY2 */
	स_नकल(fctx->auth.u.key2, (key + keylen), keylen);

	वापस nitrox_skcipher_setkey(cipher, aes_keylen, key, keylen);
पूर्ण

अटल पूर्णांक nitrox_aes_ctr_rfc3686_setkey(काष्ठा crypto_skcipher *cipher,
					 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_tfm_ctx(tfm);
	काष्ठा flexi_crypto_context *fctx;
	पूर्णांक aes_keylen;

	अगर (keylen < CTR_RFC3686_NONCE_SIZE)
		वापस -EINVAL;

	fctx = nctx->u.fctx;

	स_नकल(fctx->crypto.iv, key + (keylen - CTR_RFC3686_NONCE_SIZE),
	       CTR_RFC3686_NONCE_SIZE);

	keylen -= CTR_RFC3686_NONCE_SIZE;

	aes_keylen = flexi_aes_keylen(keylen);
	अगर (aes_keylen < 0)
		वापस -EINVAL;
	वापस nitrox_skcipher_setkey(cipher, aes_keylen, key, keylen);
पूर्ण

अटल काष्ठा skcipher_alg nitrox_skciphers[] = अणु अणु
	.base = अणु
		.cra_name = "cbc(aes)",
		.cra_driver_name = "n5_cbc(aes)",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
	.setkey = nitrox_aes_setkey,
	.encrypt = nitrox_aes_encrypt,
	.decrypt = nitrox_cbc_decrypt,
	.init = nitrox_cbc_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण, अणु
	.base = अणु
		.cra_name = "ecb(aes)",
		.cra_driver_name = "n5_ecb(aes)",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
	.setkey = nitrox_aes_setkey,
	.encrypt = nitrox_aes_encrypt,
	.decrypt = nitrox_aes_decrypt,
	.init = nitrox_skcipher_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण, अणु
	.base = अणु
		.cra_name = "cfb(aes)",
		.cra_driver_name = "n5_cfb(aes)",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
	.setkey = nitrox_aes_setkey,
	.encrypt = nitrox_aes_encrypt,
	.decrypt = nitrox_aes_decrypt,
	.init = nitrox_skcipher_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण, अणु
	.base = अणु
		.cra_name = "xts(aes)",
		.cra_driver_name = "n5_xts(aes)",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
	.setkey = nitrox_aes_xts_setkey,
	.encrypt = nitrox_aes_encrypt,
	.decrypt = nitrox_aes_decrypt,
	.init = nitrox_skcipher_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण, अणु
	.base = अणु
		.cra_name = "rfc3686(ctr(aes))",
		.cra_driver_name = "n5_rfc3686(ctr(aes))",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = 1,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
	.ivsize = CTR_RFC3686_IV_SIZE,
	.init = nitrox_skcipher_init,
	.निकास = nitrox_skcipher_निकास,
	.setkey = nitrox_aes_ctr_rfc3686_setkey,
	.encrypt = nitrox_aes_encrypt,
	.decrypt = nitrox_aes_decrypt,
पूर्ण, अणु
	.base = अणु
		.cra_name = "cts(cbc(aes))",
		.cra_driver_name = "n5_cts(cbc(aes))",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
	.setkey = nitrox_aes_setkey,
	.encrypt = nitrox_aes_encrypt,
	.decrypt = nitrox_aes_decrypt,
	.init = nitrox_skcipher_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण, अणु
	.base = अणु
		.cra_name = "cbc(des3_ede)",
		.cra_driver_name = "n5_cbc(des3_ede)",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = DES3_EDE_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BLOCK_SIZE,
	.setkey = nitrox_3des_setkey,
	.encrypt = nitrox_3des_encrypt,
	.decrypt = nitrox_cbc_decrypt,
	.init = nitrox_cbc_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण, अणु
	.base = अणु
		.cra_name = "ecb(des3_ede)",
		.cra_driver_name = "n5_ecb(des3_ede)",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = DES3_EDE_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BLOCK_SIZE,
	.setkey = nitrox_3des_setkey,
	.encrypt = nitrox_3des_encrypt,
	.decrypt = nitrox_3des_decrypt,
	.init = nitrox_skcipher_init,
	.निकास = nitrox_skcipher_निकास,
पूर्ण

पूर्ण;

पूर्णांक nitrox_रेजिस्टर_skciphers(व्योम)
अणु
	वापस crypto_रेजिस्टर_skciphers(nitrox_skciphers,
					 ARRAY_SIZE(nitrox_skciphers));
पूर्ण

व्योम nitrox_unरेजिस्टर_skciphers(व्योम)
अणु
	crypto_unरेजिस्टर_skciphers(nitrox_skciphers,
				    ARRAY_SIZE(nitrox_skciphers));
पूर्ण
