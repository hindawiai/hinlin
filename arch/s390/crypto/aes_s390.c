<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the AES Cipher Algorithm.
 *
 * s390 Version:
 *   Copyright IBM Corp. 2005, 2017
 *   Author(s): Jan Glauber (jang@de.ibm.com)
 *		Sebastian Siewior (sebastian@अवरोधpoपूर्णांक.cc> SW-Fallback
 *		Patrick Steuer <patrick.steuer@de.ibm.com>
 *		Harald Freudenberger <freude@de.ibm.com>
 *
 * Derived from "crypto/aes_generic.c"
 */

#घोषणा KMSG_COMPONENT "aes_s390"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/ghash.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fips.h>
#समावेश <linux/माला.स>
#समावेश <crypto/xts.h>
#समावेश <यंत्र/cpacf.h>

अटल u8 *ctrblk;
अटल DEFINE_MUTEX(ctrblk_lock);

अटल cpacf_mask_t km_functions, kmc_functions, kmctr_functions,
		    kma_functions;

काष्ठा s390_aes_ctx अणु
	u8 key[AES_MAX_KEY_SIZE];
	पूर्णांक key_len;
	अचिन्हित दीर्घ fc;
	जोड़ अणु
		काष्ठा crypto_skcipher *skcipher;
		काष्ठा crypto_cipher *cip;
	पूर्ण fallback;
पूर्ण;

काष्ठा s390_xts_ctx अणु
	u8 key[32];
	u8 pcc_key[32];
	पूर्णांक key_len;
	अचिन्हित दीर्घ fc;
	काष्ठा crypto_skcipher *fallback;
पूर्ण;

काष्ठा gcm_sg_walk अणु
	काष्ठा scatter_walk walk;
	अचिन्हित पूर्णांक walk_bytes;
	u8 *walk_ptr;
	अचिन्हित पूर्णांक walk_bytes_reमुख्य;
	u8 buf[AES_BLOCK_SIZE];
	अचिन्हित पूर्णांक buf_bytes;
	u8 *ptr;
	अचिन्हित पूर्णांक nbytes;
पूर्ण;

अटल पूर्णांक setkey_fallback_cip(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	sctx->fallback.cip->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
	sctx->fallback.cip->base.crt_flags |= (tfm->crt_flags &
			CRYPTO_TFM_REQ_MASK);

	वापस crypto_cipher_setkey(sctx->fallback.cip, in_key, key_len);
पूर्ण

अटल पूर्णांक aes_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);
	अचिन्हित दीर्घ fc;

	/* Pick the correct function code based on the key length */
	fc = (key_len == 16) ? CPACF_KM_AES_128 :
	     (key_len == 24) ? CPACF_KM_AES_192 :
	     (key_len == 32) ? CPACF_KM_AES_256 : 0;

	/* Check अगर the function code is available */
	sctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	अगर (!sctx->fc)
		वापस setkey_fallback_cip(tfm, in_key, key_len);

	sctx->key_len = key_len;
	स_नकल(sctx->key, in_key, key_len);
	वापस 0;
पूर्ण

अटल व्योम crypto_aes_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	अगर (unlikely(!sctx->fc)) अणु
		crypto_cipher_encrypt_one(sctx->fallback.cip, out, in);
		वापस;
	पूर्ण
	cpacf_km(sctx->fc, &sctx->key, out, in, AES_BLOCK_SIZE);
पूर्ण

अटल व्योम crypto_aes_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	अगर (unlikely(!sctx->fc)) अणु
		crypto_cipher_decrypt_one(sctx->fallback.cip, out, in);
		वापस;
	पूर्ण
	cpacf_km(sctx->fc | CPACF_DECRYPT,
		 &sctx->key, out, in, AES_BLOCK_SIZE);
पूर्ण

अटल पूर्णांक fallback_init_cip(काष्ठा crypto_tfm *tfm)
अणु
	स्थिर अक्षर *name = tfm->__crt_alg->cra_name;
	काष्ठा s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	sctx->fallback.cip = crypto_alloc_cipher(name, 0,
						 CRYPTO_ALG_NEED_FALLBACK);

	अगर (IS_ERR(sctx->fallback.cip)) अणु
		pr_err("Allocating AES fallback algorithm %s failed\n",
		       name);
		वापस PTR_ERR(sctx->fallback.cip);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fallback_निकास_cip(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_cipher(sctx->fallback.cip);
	sctx->fallback.cip = शून्य;
पूर्ण

अटल काष्ठा crypto_alg aes_alg = अणु
	.cra_name		=	"aes",
	.cra_driver_name	=	"aes-s390",
	.cra_priority		=	300,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER |
					CRYPTO_ALG_NEED_FALLBACK,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा s390_aes_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_init               =       fallback_init_cip,
	.cra_निकास               =       fallback_निकास_cip,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey		=	aes_set_key,
			.cia_encrypt		=	crypto_aes_encrypt,
			.cia_decrypt		=	crypto_aes_decrypt,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक setkey_fallback_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक len)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_clear_flags(sctx->fallback.skcipher,
				    CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(sctx->fallback.skcipher,
				  crypto_skcipher_get_flags(tfm) &
				  CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(sctx->fallback.skcipher, key, len);
पूर्ण

अटल पूर्णांक fallback_skcipher_crypt(काष्ठा s390_aes_ctx *sctx,
				   काष्ठा skcipher_request *req,
				   अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

	*subreq = *req;
	skcipher_request_set_tfm(subreq, sctx->fallback.skcipher);
	वापस (modअगरier & CPACF_DECRYPT) ?
		crypto_skcipher_decrypt(subreq) :
		crypto_skcipher_encrypt(subreq);
पूर्ण

अटल पूर्णांक ecb_aes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			   अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);
	अचिन्हित दीर्घ fc;

	/* Pick the correct function code based on the key length */
	fc = (key_len == 16) ? CPACF_KM_AES_128 :
	     (key_len == 24) ? CPACF_KM_AES_192 :
	     (key_len == 32) ? CPACF_KM_AES_256 : 0;

	/* Check अगर the function code is available */
	sctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	अगर (!sctx->fc)
		वापस setkey_fallback_skcipher(tfm, in_key, key_len);

	sctx->key_len = key_len;
	स_नकल(sctx->key, in_key, key_len);
	वापस 0;
पूर्ण

अटल पूर्णांक ecb_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n;
	पूर्णांक ret;

	अगर (unlikely(!sctx->fc))
		वापस fallback_skcipher_crypt(sctx, req, modअगरier);

	ret = skcipher_walk_virt(&walk, req, false);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		cpacf_km(sctx->fc | modअगरier, sctx->key,
			 walk.dst.virt.addr, walk.src.virt.addr, n);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ecb_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_aes_crypt(req, 0);
पूर्ण

अटल पूर्णांक ecb_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_aes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल पूर्णांक fallback_init_skcipher(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);

	sctx->fallback.skcipher = crypto_alloc_skcipher(name, 0,
				CRYPTO_ALG_NEED_FALLBACK | CRYPTO_ALG_ASYNC);

	अगर (IS_ERR(sctx->fallback.skcipher)) अणु
		pr_err("Allocating AES fallback algorithm %s failed\n",
		       name);
		वापस PTR_ERR(sctx->fallback.skcipher);
	पूर्ण

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा skcipher_request) +
				    crypto_skcipher_reqsize(sctx->fallback.skcipher));
	वापस 0;
पूर्ण

अटल व्योम fallback_निकास_skcipher(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(sctx->fallback.skcipher);
पूर्ण

अटल काष्ठा skcipher_alg ecb_aes_alg = अणु
	.base.cra_name		=	"ecb(aes)",
	.base.cra_driver_name	=	"ecb-aes-s390",
	.base.cra_priority	=	401,	/* combo: aes + ecb + 1 */
	.base.cra_flags		=	CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_aes_ctx),
	.base.cra_module	=	THIS_MODULE,
	.init			=	fallback_init_skcipher,
	.निकास			=	fallback_निकास_skcipher,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.setkey			=	ecb_aes_set_key,
	.encrypt		=	ecb_aes_encrypt,
	.decrypt		=	ecb_aes_decrypt,
पूर्ण;

अटल पूर्णांक cbc_aes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			   अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);
	अचिन्हित दीर्घ fc;

	/* Pick the correct function code based on the key length */
	fc = (key_len == 16) ? CPACF_KMC_AES_128 :
	     (key_len == 24) ? CPACF_KMC_AES_192 :
	     (key_len == 32) ? CPACF_KMC_AES_256 : 0;

	/* Check अगर the function code is available */
	sctx->fc = (fc && cpacf_test_func(&kmc_functions, fc)) ? fc : 0;
	अगर (!sctx->fc)
		वापस setkey_fallback_skcipher(tfm, in_key, key_len);

	sctx->key_len = key_len;
	स_नकल(sctx->key, in_key, key_len);
	वापस 0;
पूर्ण

अटल पूर्णांक cbc_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n;
	पूर्णांक ret;
	काष्ठा अणु
		u8 iv[AES_BLOCK_SIZE];
		u8 key[AES_MAX_KEY_SIZE];
	पूर्ण param;

	अगर (unlikely(!sctx->fc))
		वापस fallback_skcipher_crypt(sctx, req, modअगरier);

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;
	स_नकल(param.iv, walk.iv, AES_BLOCK_SIZE);
	स_नकल(param.key, sctx->key, sctx->key_len);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		cpacf_kmc(sctx->fc | modअगरier, &param,
			  walk.dst.virt.addr, walk.src.virt.addr, n);
		स_नकल(walk.iv, param.iv, AES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	memzero_explicit(&param, माप(param));
	वापस ret;
पूर्ण

अटल पूर्णांक cbc_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_aes_crypt(req, 0);
पूर्ण

अटल पूर्णांक cbc_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_aes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg cbc_aes_alg = अणु
	.base.cra_name		=	"cbc(aes)",
	.base.cra_driver_name	=	"cbc-aes-s390",
	.base.cra_priority	=	402,	/* ecb-aes-s390 + 1 */
	.base.cra_flags		=	CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_aes_ctx),
	.base.cra_module	=	THIS_MODULE,
	.init			=	fallback_init_skcipher,
	.निकास			=	fallback_निकास_skcipher,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	cbc_aes_set_key,
	.encrypt		=	cbc_aes_encrypt,
	.decrypt		=	cbc_aes_decrypt,
पूर्ण;

अटल पूर्णांक xts_fallback_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा s390_xts_ctx *xts_ctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_clear_flags(xts_ctx->fallback, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(xts_ctx->fallback,
				  crypto_skcipher_get_flags(tfm) &
				  CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(xts_ctx->fallback, key, len);
पूर्ण

अटल पूर्णांक xts_aes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			   अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_xts_ctx *xts_ctx = crypto_skcipher_ctx(tfm);
	अचिन्हित दीर्घ fc;
	पूर्णांक err;

	err = xts_fallback_setkey(tfm, in_key, key_len);
	अगर (err)
		वापस err;

	/* In fips mode only 128 bit or 256 bit keys are valid */
	अगर (fips_enabled && key_len != 32 && key_len != 64)
		वापस -EINVAL;

	/* Pick the correct function code based on the key length */
	fc = (key_len == 32) ? CPACF_KM_XTS_128 :
	     (key_len == 64) ? CPACF_KM_XTS_256 : 0;

	/* Check अगर the function code is available */
	xts_ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	अगर (!xts_ctx->fc)
		वापस 0;

	/* Split the XTS key पूर्णांकo the two subkeys */
	key_len = key_len / 2;
	xts_ctx->key_len = key_len;
	स_नकल(xts_ctx->key, in_key, key_len);
	स_नकल(xts_ctx->pcc_key, in_key + key_len, key_len);
	वापस 0;
पूर्ण

अटल पूर्णांक xts_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_xts_ctx *xts_ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक offset, nbytes, n;
	पूर्णांक ret;
	काष्ठा अणु
		u8 key[32];
		u8 tweak[16];
		u8 block[16];
		u8 bit[16];
		u8 xts[16];
	पूर्ण pcc_param;
	काष्ठा अणु
		u8 key[32];
		u8 init[16];
	पूर्ण xts_param;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (unlikely(!xts_ctx->fc || (req->cryptlen % AES_BLOCK_SIZE) != 0)) अणु
		काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

		*subreq = *req;
		skcipher_request_set_tfm(subreq, xts_ctx->fallback);
		वापस (modअगरier & CPACF_DECRYPT) ?
			crypto_skcipher_decrypt(subreq) :
			crypto_skcipher_encrypt(subreq);
	पूर्ण

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;
	offset = xts_ctx->key_len & 0x10;
	स_रखो(pcc_param.block, 0, माप(pcc_param.block));
	स_रखो(pcc_param.bit, 0, माप(pcc_param.bit));
	स_रखो(pcc_param.xts, 0, माप(pcc_param.xts));
	स_नकल(pcc_param.tweak, walk.iv, माप(pcc_param.tweak));
	स_नकल(pcc_param.key + offset, xts_ctx->pcc_key, xts_ctx->key_len);
	cpacf_pcc(xts_ctx->fc, pcc_param.key + offset);

	स_नकल(xts_param.key + offset, xts_ctx->key, xts_ctx->key_len);
	स_नकल(xts_param.init, pcc_param.xts, 16);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		cpacf_km(xts_ctx->fc | modअगरier, xts_param.key + offset,
			 walk.dst.virt.addr, walk.src.virt.addr, n);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	memzero_explicit(&pcc_param, माप(pcc_param));
	memzero_explicit(&xts_param, माप(xts_param));
	वापस ret;
पूर्ण

अटल पूर्णांक xts_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस xts_aes_crypt(req, 0);
पूर्ण

अटल पूर्णांक xts_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस xts_aes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल पूर्णांक xts_fallback_init(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा s390_xts_ctx *xts_ctx = crypto_skcipher_ctx(tfm);

	xts_ctx->fallback = crypto_alloc_skcipher(name, 0,
				CRYPTO_ALG_NEED_FALLBACK | CRYPTO_ALG_ASYNC);

	अगर (IS_ERR(xts_ctx->fallback)) अणु
		pr_err("Allocating XTS fallback algorithm %s failed\n",
		       name);
		वापस PTR_ERR(xts_ctx->fallback);
	पूर्ण
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा skcipher_request) +
				    crypto_skcipher_reqsize(xts_ctx->fallback));
	वापस 0;
पूर्ण

अटल व्योम xts_fallback_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_xts_ctx *xts_ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(xts_ctx->fallback);
पूर्ण

अटल काष्ठा skcipher_alg xts_aes_alg = अणु
	.base.cra_name		=	"xts(aes)",
	.base.cra_driver_name	=	"xts-aes-s390",
	.base.cra_priority	=	402,	/* ecb-aes-s390 + 1 */
	.base.cra_flags		=	CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_xts_ctx),
	.base.cra_module	=	THIS_MODULE,
	.init			=	xts_fallback_init,
	.निकास			=	xts_fallback_निकास,
	.min_keysize		=	2 * AES_MIN_KEY_SIZE,
	.max_keysize		=	2 * AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	xts_aes_set_key,
	.encrypt		=	xts_aes_encrypt,
	.decrypt		=	xts_aes_decrypt,
पूर्ण;

अटल पूर्णांक ctr_aes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			   अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);
	अचिन्हित दीर्घ fc;

	/* Pick the correct function code based on the key length */
	fc = (key_len == 16) ? CPACF_KMCTR_AES_128 :
	     (key_len == 24) ? CPACF_KMCTR_AES_192 :
	     (key_len == 32) ? CPACF_KMCTR_AES_256 : 0;

	/* Check अगर the function code is available */
	sctx->fc = (fc && cpacf_test_func(&kmctr_functions, fc)) ? fc : 0;
	अगर (!sctx->fc)
		वापस setkey_fallback_skcipher(tfm, in_key, key_len);

	sctx->key_len = key_len;
	स_नकल(sctx->key, in_key, key_len);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक __ctrblk_init(u8 *ctrptr, u8 *iv, अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित पूर्णांक i, n;

	/* only use complete blocks, max. PAGE_SIZE */
	स_नकल(ctrptr, iv, AES_BLOCK_SIZE);
	n = (nbytes > PAGE_SIZE) ? PAGE_SIZE : nbytes & ~(AES_BLOCK_SIZE - 1);
	क्रम (i = (n / AES_BLOCK_SIZE) - 1; i > 0; i--) अणु
		स_नकल(ctrptr + AES_BLOCK_SIZE, ctrptr, AES_BLOCK_SIZE);
		crypto_inc(ctrptr + AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		ctrptr += AES_BLOCK_SIZE;
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक ctr_aes_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_aes_ctx *sctx = crypto_skcipher_ctx(tfm);
	u8 buf[AES_BLOCK_SIZE], *ctrptr;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक n, nbytes;
	पूर्णांक ret, locked;

	अगर (unlikely(!sctx->fc))
		वापस fallback_skcipher_crypt(sctx, req, 0);

	locked = mutex_trylock(&ctrblk_lock);

	ret = skcipher_walk_virt(&walk, req, false);
	जबतक ((nbytes = walk.nbytes) >= AES_BLOCK_SIZE) अणु
		n = AES_BLOCK_SIZE;

		अगर (nbytes >= 2*AES_BLOCK_SIZE && locked)
			n = __ctrblk_init(ctrblk, walk.iv, nbytes);
		ctrptr = (n > AES_BLOCK_SIZE) ? ctrblk : walk.iv;
		cpacf_kmctr(sctx->fc, sctx->key, walk.dst.virt.addr,
			    walk.src.virt.addr, n, ctrptr);
		अगर (ctrptr == ctrblk)
			स_नकल(walk.iv, ctrptr + n - AES_BLOCK_SIZE,
			       AES_BLOCK_SIZE);
		crypto_inc(walk.iv, AES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	अगर (locked)
		mutex_unlock(&ctrblk_lock);
	/*
	 * final block may be < AES_BLOCK_SIZE, copy only nbytes
	 */
	अगर (nbytes) अणु
		cpacf_kmctr(sctx->fc, sctx->key, buf, walk.src.virt.addr,
			    AES_BLOCK_SIZE, walk.iv);
		स_नकल(walk.dst.virt.addr, buf, nbytes);
		crypto_inc(walk.iv, AES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा skcipher_alg ctr_aes_alg = अणु
	.base.cra_name		=	"ctr(aes)",
	.base.cra_driver_name	=	"ctr-aes-s390",
	.base.cra_priority	=	402,	/* ecb-aes-s390 + 1 */
	.base.cra_flags		=	CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	=	1,
	.base.cra_ctxsize	=	माप(काष्ठा s390_aes_ctx),
	.base.cra_module	=	THIS_MODULE,
	.init			=	fallback_init_skcipher,
	.निकास			=	fallback_निकास_skcipher,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	ctr_aes_set_key,
	.encrypt		=	ctr_aes_crypt,
	.decrypt		=	ctr_aes_crypt,
	.chunksize		=	AES_BLOCK_SIZE,
पूर्ण;

अटल पूर्णांक gcm_aes_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा s390_aes_ctx *ctx = crypto_aead_ctx(tfm);

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->fc = CPACF_KMA_GCM_AES_128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->fc = CPACF_KMA_GCM_AES_192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->fc = CPACF_KMA_GCM_AES_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(ctx->key, key, keylen);
	ctx->key_len = keylen;
	वापस 0;
पूर्ण

अटल पूर्णांक gcm_aes_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 8:
	हाल 12:
	हाल 13:
	हाल 14:
	हाल 15:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gcm_walk_start(काष्ठा gcm_sg_walk *gw, काष्ठा scatterlist *sg,
			   अचिन्हित पूर्णांक len)
अणु
	स_रखो(gw, 0, माप(*gw));
	gw->walk_bytes_reमुख्य = len;
	scatterwalk_start(&gw->walk, sg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक _gcm_sg_clamp_and_map(काष्ठा gcm_sg_walk *gw)
अणु
	काष्ठा scatterlist *nextsg;

	gw->walk_bytes = scatterwalk_clamp(&gw->walk, gw->walk_bytes_reमुख्य);
	जबतक (!gw->walk_bytes) अणु
		nextsg = sg_next(gw->walk.sg);
		अगर (!nextsg)
			वापस 0;
		scatterwalk_start(&gw->walk, nextsg);
		gw->walk_bytes = scatterwalk_clamp(&gw->walk,
						   gw->walk_bytes_reमुख्य);
	पूर्ण
	gw->walk_ptr = scatterwalk_map(&gw->walk);
	वापस gw->walk_bytes;
पूर्ण

अटल अंतरभूत व्योम _gcm_sg_unmap_and_advance(काष्ठा gcm_sg_walk *gw,
					     अचिन्हित पूर्णांक nbytes)
अणु
	gw->walk_bytes_reमुख्य -= nbytes;
	scatterwalk_unmap(&gw->walk);
	scatterwalk_advance(&gw->walk, nbytes);
	scatterwalk_करोne(&gw->walk, 0, gw->walk_bytes_reमुख्य);
	gw->walk_ptr = शून्य;
पूर्ण

अटल पूर्णांक gcm_in_walk_go(काष्ठा gcm_sg_walk *gw, अचिन्हित पूर्णांक minbytesneeded)
अणु
	पूर्णांक n;

	अगर (gw->buf_bytes && gw->buf_bytes >= minbytesneeded) अणु
		gw->ptr = gw->buf;
		gw->nbytes = gw->buf_bytes;
		जाओ out;
	पूर्ण

	अगर (gw->walk_bytes_reमुख्य == 0) अणु
		gw->ptr = शून्य;
		gw->nbytes = 0;
		जाओ out;
	पूर्ण

	अगर (!_gcm_sg_clamp_and_map(gw)) अणु
		gw->ptr = शून्य;
		gw->nbytes = 0;
		जाओ out;
	पूर्ण

	अगर (!gw->buf_bytes && gw->walk_bytes >= minbytesneeded) अणु
		gw->ptr = gw->walk_ptr;
		gw->nbytes = gw->walk_bytes;
		जाओ out;
	पूर्ण

	जबतक (1) अणु
		n = min(gw->walk_bytes, AES_BLOCK_SIZE - gw->buf_bytes);
		स_नकल(gw->buf + gw->buf_bytes, gw->walk_ptr, n);
		gw->buf_bytes += n;
		_gcm_sg_unmap_and_advance(gw, n);
		अगर (gw->buf_bytes >= minbytesneeded) अणु
			gw->ptr = gw->buf;
			gw->nbytes = gw->buf_bytes;
			जाओ out;
		पूर्ण
		अगर (!_gcm_sg_clamp_and_map(gw)) अणु
			gw->ptr = शून्य;
			gw->nbytes = 0;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस gw->nbytes;
पूर्ण

अटल पूर्णांक gcm_out_walk_go(काष्ठा gcm_sg_walk *gw, अचिन्हित पूर्णांक minbytesneeded)
अणु
	अगर (gw->walk_bytes_reमुख्य == 0) अणु
		gw->ptr = शून्य;
		gw->nbytes = 0;
		जाओ out;
	पूर्ण

	अगर (!_gcm_sg_clamp_and_map(gw)) अणु
		gw->ptr = शून्य;
		gw->nbytes = 0;
		जाओ out;
	पूर्ण

	अगर (gw->walk_bytes >= minbytesneeded) अणु
		gw->ptr = gw->walk_ptr;
		gw->nbytes = gw->walk_bytes;
		जाओ out;
	पूर्ण

	scatterwalk_unmap(&gw->walk);
	gw->walk_ptr = शून्य;

	gw->ptr = gw->buf;
	gw->nbytes = माप(gw->buf);

out:
	वापस gw->nbytes;
पूर्ण

अटल पूर्णांक gcm_in_walk_करोne(काष्ठा gcm_sg_walk *gw, अचिन्हित पूर्णांक bytesकरोne)
अणु
	अगर (gw->ptr == शून्य)
		वापस 0;

	अगर (gw->ptr == gw->buf) अणु
		पूर्णांक n = gw->buf_bytes - bytesकरोne;
		अगर (n > 0) अणु
			स_हटाओ(gw->buf, gw->buf + bytesकरोne, n);
			gw->buf_bytes = n;
		पूर्ण अन्यथा
			gw->buf_bytes = 0;
	पूर्ण अन्यथा
		_gcm_sg_unmap_and_advance(gw, bytesकरोne);

	वापस bytesकरोne;
पूर्ण

अटल पूर्णांक gcm_out_walk_करोne(काष्ठा gcm_sg_walk *gw, अचिन्हित पूर्णांक bytesकरोne)
अणु
	पूर्णांक i, n;

	अगर (gw->ptr == शून्य)
		वापस 0;

	अगर (gw->ptr == gw->buf) अणु
		क्रम (i = 0; i < bytesकरोne; i += n) अणु
			अगर (!_gcm_sg_clamp_and_map(gw))
				वापस i;
			n = min(gw->walk_bytes, bytesकरोne - i);
			स_नकल(gw->walk_ptr, gw->buf + i, n);
			_gcm_sg_unmap_and_advance(gw, n);
		पूर्ण
	पूर्ण अन्यथा
		_gcm_sg_unmap_and_advance(gw, bytesकरोne);

	वापस bytesकरोne;
पूर्ण

अटल पूर्णांक gcm_aes_crypt(काष्ठा aead_request *req, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा s390_aes_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(tfm);
	अचिन्हित पूर्णांक taglen = crypto_aead_authsize(tfm);
	अचिन्हित पूर्णांक aadlen = req->assoclen;
	अचिन्हित पूर्णांक pclen = req->cryptlen;
	पूर्णांक ret = 0;

	अचिन्हित पूर्णांक n, len, in_bytes, out_bytes,
		     min_bytes, bytes, aad_bytes, pc_bytes;
	काष्ठा gcm_sg_walk gw_in, gw_out;
	u8 tag[GHASH_DIGEST_SIZE];

	काष्ठा अणु
		u32 _[3];		/* reserved */
		u32 cv;			/* Counter Value */
		u8 t[GHASH_DIGEST_SIZE];/* Tag */
		u8 h[AES_BLOCK_SIZE];	/* Hash-subkey */
		u64 taadl;		/* Total AAD Length */
		u64 tpcl;		/* Total Plain-/Cipher-text Length */
		u8 j0[GHASH_BLOCK_SIZE];/* initial counter value */
		u8 k[AES_MAX_KEY_SIZE];	/* Key */
	पूर्ण param;

	/*
	 * encrypt
	 *   req->src: aad||plaपूर्णांकext
	 *   req->dst: aad||ciphertext||tag
	 * decrypt
	 *   req->src: aad||ciphertext||tag
	 *   req->dst: aad||plaपूर्णांकext, वापस 0 or -EBADMSG
	 * aad, plaपूर्णांकext and ciphertext may be empty.
	 */
	अगर (flags & CPACF_DECRYPT)
		pclen -= taglen;
	len = aadlen + pclen;

	स_रखो(&param, 0, माप(param));
	param.cv = 1;
	param.taadl = aadlen * 8;
	param.tpcl = pclen * 8;
	स_नकल(param.j0, req->iv, ivsize);
	*(u32 *)(param.j0 + ivsize) = 1;
	स_नकल(param.k, ctx->key, ctx->key_len);

	gcm_walk_start(&gw_in, req->src, len);
	gcm_walk_start(&gw_out, req->dst, len);

	करो अणु
		min_bytes = min_t(अचिन्हित पूर्णांक,
				  aadlen > 0 ? aadlen : pclen, AES_BLOCK_SIZE);
		in_bytes = gcm_in_walk_go(&gw_in, min_bytes);
		out_bytes = gcm_out_walk_go(&gw_out, min_bytes);
		bytes = min(in_bytes, out_bytes);

		अगर (aadlen + pclen <= bytes) अणु
			aad_bytes = aadlen;
			pc_bytes = pclen;
			flags |= CPACF_KMA_LAAD | CPACF_KMA_LPC;
		पूर्ण अन्यथा अणु
			अगर (aadlen <= bytes) अणु
				aad_bytes = aadlen;
				pc_bytes = (bytes - aadlen) &
					   ~(AES_BLOCK_SIZE - 1);
				flags |= CPACF_KMA_LAAD;
			पूर्ण अन्यथा अणु
				aad_bytes = bytes & ~(AES_BLOCK_SIZE - 1);
				pc_bytes = 0;
			पूर्ण
		पूर्ण

		अगर (aad_bytes > 0)
			स_नकल(gw_out.ptr, gw_in.ptr, aad_bytes);

		cpacf_kma(ctx->fc | flags, &param,
			  gw_out.ptr + aad_bytes,
			  gw_in.ptr + aad_bytes, pc_bytes,
			  gw_in.ptr, aad_bytes);

		n = aad_bytes + pc_bytes;
		अगर (gcm_in_walk_करोne(&gw_in, n) != n)
			वापस -ENOMEM;
		अगर (gcm_out_walk_करोne(&gw_out, n) != n)
			वापस -ENOMEM;
		aadlen -= aad_bytes;
		pclen -= pc_bytes;
	पूर्ण जबतक (aadlen + pclen > 0);

	अगर (flags & CPACF_DECRYPT) अणु
		scatterwalk_map_and_copy(tag, req->src, len, taglen, 0);
		अगर (crypto_memneq(tag, param.t, taglen))
			ret = -EBADMSG;
	पूर्ण अन्यथा
		scatterwalk_map_and_copy(param.t, req->dst, len, taglen, 1);

	memzero_explicit(&param, माप(param));
	वापस ret;
पूर्ण

अटल पूर्णांक gcm_aes_encrypt(काष्ठा aead_request *req)
अणु
	वापस gcm_aes_crypt(req, CPACF_ENCRYPT);
पूर्ण

अटल पूर्णांक gcm_aes_decrypt(काष्ठा aead_request *req)
अणु
	वापस gcm_aes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल काष्ठा aead_alg gcm_aes_aead = अणु
	.setkey			= gcm_aes_setkey,
	.setauthsize		= gcm_aes_setauthsize,
	.encrypt		= gcm_aes_encrypt,
	.decrypt		= gcm_aes_decrypt,

	.ivsize			= GHASH_BLOCK_SIZE - माप(u32),
	.maxauthsize		= GHASH_DIGEST_SIZE,
	.chunksize		= AES_BLOCK_SIZE,

	.base			= अणु
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा s390_aes_ctx),
		.cra_priority		= 900,
		.cra_name		= "gcm(aes)",
		.cra_driver_name	= "gcm-aes-s390",
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल काष्ठा crypto_alg *aes_s390_alg;
अटल काष्ठा skcipher_alg *aes_s390_skcipher_algs[4];
अटल पूर्णांक aes_s390_skciphers_num;
अटल काष्ठा aead_alg *aes_s390_aead_alg;

अटल पूर्णांक aes_s390_रेजिस्टर_skcipher(काष्ठा skcipher_alg *alg)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_skcipher(alg);
	अगर (!ret)
		aes_s390_skcipher_algs[aes_s390_skciphers_num++] = alg;
	वापस ret;
पूर्ण

अटल व्योम aes_s390_fini(व्योम)
अणु
	अगर (aes_s390_alg)
		crypto_unरेजिस्टर_alg(aes_s390_alg);
	जबतक (aes_s390_skciphers_num--)
		crypto_unरेजिस्टर_skcipher(aes_s390_skcipher_algs[aes_s390_skciphers_num]);
	अगर (ctrblk)
		मुक्त_page((अचिन्हित दीर्घ) ctrblk);

	अगर (aes_s390_aead_alg)
		crypto_unरेजिस्टर_aead(aes_s390_aead_alg);
पूर्ण

अटल पूर्णांक __init aes_s390_init(व्योम)
अणु
	पूर्णांक ret;

	/* Query available functions क्रम KM, KMC, KMCTR and KMA */
	cpacf_query(CPACF_KM, &km_functions);
	cpacf_query(CPACF_KMC, &kmc_functions);
	cpacf_query(CPACF_KMCTR, &kmctr_functions);
	cpacf_query(CPACF_KMA, &kma_functions);

	अगर (cpacf_test_func(&km_functions, CPACF_KM_AES_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_AES_192) ||
	    cpacf_test_func(&km_functions, CPACF_KM_AES_256)) अणु
		ret = crypto_रेजिस्टर_alg(&aes_alg);
		अगर (ret)
			जाओ out_err;
		aes_s390_alg = &aes_alg;
		ret = aes_s390_रेजिस्टर_skcipher(&ecb_aes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&kmc_functions, CPACF_KMC_AES_128) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_AES_192) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_AES_256)) अणु
		ret = aes_s390_रेजिस्टर_skcipher(&cbc_aes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&km_functions, CPACF_KM_XTS_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_XTS_256)) अणु
		ret = aes_s390_रेजिस्टर_skcipher(&xts_aes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&kmctr_functions, CPACF_KMCTR_AES_128) ||
	    cpacf_test_func(&kmctr_functions, CPACF_KMCTR_AES_192) ||
	    cpacf_test_func(&kmctr_functions, CPACF_KMCTR_AES_256)) अणु
		ctrblk = (u8 *) __get_मुक्त_page(GFP_KERNEL);
		अगर (!ctrblk) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
		ret = aes_s390_रेजिस्टर_skcipher(&ctr_aes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&kma_functions, CPACF_KMA_GCM_AES_128) ||
	    cpacf_test_func(&kma_functions, CPACF_KMA_GCM_AES_192) ||
	    cpacf_test_func(&kma_functions, CPACF_KMA_GCM_AES_256)) अणु
		ret = crypto_रेजिस्टर_aead(&gcm_aes_aead);
		अगर (ret)
			जाओ out_err;
		aes_s390_aead_alg = &gcm_aes_aead;
	पूर्ण

	वापस 0;
out_err:
	aes_s390_fini();
	वापस ret;
पूर्ण

module_cpu_feature_match(MSA, aes_s390_init);
module_निकास(aes_s390_fini);

MODULE_ALIAS_CRYPTO("aes-all");

MODULE_DESCRIPTION("Rijndael (AES) Cipher Algorithm");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
