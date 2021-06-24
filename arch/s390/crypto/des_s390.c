<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the DES Cipher Algorithm.
 *
 * Copyright IBM Corp. 2003, 2011
 * Author(s): Thomas Spatzier
 *	      Jan Glauber (jan.glauber@de.ibm.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/fips.h>
#समावेश <linux/mutex.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <यंत्र/cpacf.h>

#घोषणा DES3_KEY_SIZE	(3 * DES_KEY_SIZE)

अटल u8 *ctrblk;
अटल DEFINE_MUTEX(ctrblk_lock);

अटल cpacf_mask_t km_functions, kmc_functions, kmctr_functions;

काष्ठा s390_des_ctx अणु
	u8 iv[DES_BLOCK_SIZE];
	u8 key[DES3_KEY_SIZE];
पूर्ण;

अटल पूर्णांक des_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		      अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_des_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	err = crypto_des_verअगरy_key(tfm, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, key_len);
	वापस 0;
पूर्ण

अटल पूर्णांक des_setkey_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक key_len)
अणु
	वापस des_setkey(crypto_skcipher_tfm(tfm), key, key_len);
पूर्ण

अटल व्योम s390_des_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा s390_des_ctx *ctx = crypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_DEA, ctx->key, out, in, DES_BLOCK_SIZE);
पूर्ण

अटल व्योम s390_des_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा s390_des_ctx *ctx = crypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_DEA | CPACF_DECRYPT,
		 ctx->key, out, in, DES_BLOCK_SIZE);
पूर्ण

अटल काष्ठा crypto_alg des_alg = अणु
	.cra_name		=	"des",
	.cra_driver_name	=	"des-s390",
	.cra_priority		=	300,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा s390_des_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	DES_KEY_SIZE,
			.cia_max_keysize	=	DES_KEY_SIZE,
			.cia_setkey		=	des_setkey,
			.cia_encrypt		=	s390_des_encrypt,
			.cia_decrypt		=	s390_des_decrypt,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक ecb_desall_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ fc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_des_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n;
	पूर्णांक ret;

	ret = skcipher_walk_virt(&walk, req, false);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(DES_BLOCK_SIZE - 1);
		cpacf_km(fc, ctx->key, walk.dst.virt.addr,
			 walk.src.virt.addr, n);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cbc_desall_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ fc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_des_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n;
	पूर्णांक ret;
	काष्ठा अणु
		u8 iv[DES_BLOCK_SIZE];
		u8 key[DES3_KEY_SIZE];
	पूर्ण param;

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;
	स_नकल(param.iv, walk.iv, DES_BLOCK_SIZE);
	स_नकल(param.key, ctx->key, DES3_KEY_SIZE);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(DES_BLOCK_SIZE - 1);
		cpacf_kmc(fc, &param, walk.dst.virt.addr,
			  walk.src.virt.addr, n);
		स_नकल(walk.iv, param.iv, DES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ecb_des_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_desall_crypt(req, CPACF_KM_DEA);
पूर्ण

अटल पूर्णांक ecb_des_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_desall_crypt(req, CPACF_KM_DEA | CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg ecb_des_alg = अणु
	.base.cra_name		=	"ecb(des)",
	.base.cra_driver_name	=	"ecb-des-s390",
	.base.cra_priority	=	400,	/* combo: des + ecb */
	.base.cra_blocksize	=	DES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_des_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	DES_KEY_SIZE,
	.max_keysize		=	DES_KEY_SIZE,
	.setkey			=	des_setkey_skcipher,
	.encrypt		=	ecb_des_encrypt,
	.decrypt		=	ecb_des_decrypt,
पूर्ण;

अटल पूर्णांक cbc_des_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_desall_crypt(req, CPACF_KMC_DEA);
पूर्ण

अटल पूर्णांक cbc_des_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_desall_crypt(req, CPACF_KMC_DEA | CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg cbc_des_alg = अणु
	.base.cra_name		=	"cbc(des)",
	.base.cra_driver_name	=	"cbc-des-s390",
	.base.cra_priority	=	400,	/* combo: des + cbc */
	.base.cra_blocksize	=	DES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_des_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	DES_KEY_SIZE,
	.max_keysize		=	DES_KEY_SIZE,
	.ivsize			=	DES_BLOCK_SIZE,
	.setkey			=	des_setkey_skcipher,
	.encrypt		=	cbc_des_encrypt,
	.decrypt		=	cbc_des_decrypt,
पूर्ण;

/*
 * RFC2451:
 *
 *   For DES-EDE3, there is no known need to reject weak or
 *   complementation keys.  Any weakness is obviated by the use of
 *   multiple keys.
 *
 *   However, अगर the first two or last two independent 64-bit keys are
 *   equal (k1 == k2 or k2 == k3), then the DES3 operation is simply the
 *   same as DES.  Implementers MUST reject keys that exhibit this
 *   property.
 *
 *   In fips mode additinally check क्रम all 3 keys are unique.
 *
 */
अटल पूर्णांक des3_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा s390_des_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	err = crypto_des3_ede_verअगरy_key(tfm, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, key_len);
	वापस 0;
पूर्ण

अटल पूर्णांक des3_setkey_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक key_len)
अणु
	वापस des3_setkey(crypto_skcipher_tfm(tfm), key, key_len);
पूर्ण

अटल व्योम des3_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा s390_des_ctx *ctx = crypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_TDEA_192, ctx->key, dst, src, DES_BLOCK_SIZE);
पूर्ण

अटल व्योम des3_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा s390_des_ctx *ctx = crypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_TDEA_192 | CPACF_DECRYPT,
		 ctx->key, dst, src, DES_BLOCK_SIZE);
पूर्ण

अटल काष्ठा crypto_alg des3_alg = अणु
	.cra_name		=	"des3_ede",
	.cra_driver_name	=	"des3_ede-s390",
	.cra_priority		=	300,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा s390_des_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	DES3_KEY_SIZE,
			.cia_max_keysize	=	DES3_KEY_SIZE,
			.cia_setkey		=	des3_setkey,
			.cia_encrypt		=	des3_encrypt,
			.cia_decrypt		=	des3_decrypt,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक ecb_des3_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_desall_crypt(req, CPACF_KM_TDEA_192);
पूर्ण

अटल पूर्णांक ecb_des3_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_desall_crypt(req, CPACF_KM_TDEA_192 | CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg ecb_des3_alg = अणु
	.base.cra_name		=	"ecb(des3_ede)",
	.base.cra_driver_name	=	"ecb-des3_ede-s390",
	.base.cra_priority	=	400,	/* combo: des3 + ecb */
	.base.cra_blocksize	=	DES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_des_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	DES3_KEY_SIZE,
	.max_keysize		=	DES3_KEY_SIZE,
	.setkey			=	des3_setkey_skcipher,
	.encrypt		=	ecb_des3_encrypt,
	.decrypt		=	ecb_des3_decrypt,
पूर्ण;

अटल पूर्णांक cbc_des3_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_desall_crypt(req, CPACF_KMC_TDEA_192);
पूर्ण

अटल पूर्णांक cbc_des3_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_desall_crypt(req, CPACF_KMC_TDEA_192 | CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg cbc_des3_alg = अणु
	.base.cra_name		=	"cbc(des3_ede)",
	.base.cra_driver_name	=	"cbc-des3_ede-s390",
	.base.cra_priority	=	400,	/* combo: des3 + cbc */
	.base.cra_blocksize	=	DES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_des_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	DES3_KEY_SIZE,
	.max_keysize		=	DES3_KEY_SIZE,
	.ivsize			=	DES_BLOCK_SIZE,
	.setkey			=	des3_setkey_skcipher,
	.encrypt		=	cbc_des3_encrypt,
	.decrypt		=	cbc_des3_decrypt,
पूर्ण;

अटल अचिन्हित पूर्णांक __ctrblk_init(u8 *ctrptr, u8 *iv, अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित पूर्णांक i, n;

	/* align to block size, max. PAGE_SIZE */
	n = (nbytes > PAGE_SIZE) ? PAGE_SIZE : nbytes & ~(DES_BLOCK_SIZE - 1);
	स_नकल(ctrptr, iv, DES_BLOCK_SIZE);
	क्रम (i = (n / DES_BLOCK_SIZE) - 1; i > 0; i--) अणु
		स_नकल(ctrptr + DES_BLOCK_SIZE, ctrptr, DES_BLOCK_SIZE);
		crypto_inc(ctrptr + DES_BLOCK_SIZE, DES_BLOCK_SIZE);
		ctrptr += DES_BLOCK_SIZE;
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक ctr_desall_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ fc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_des_ctx *ctx = crypto_skcipher_ctx(tfm);
	u8 buf[DES_BLOCK_SIZE], *ctrptr;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक n, nbytes;
	पूर्णांक ret, locked;

	locked = mutex_trylock(&ctrblk_lock);

	ret = skcipher_walk_virt(&walk, req, false);
	जबतक ((nbytes = walk.nbytes) >= DES_BLOCK_SIZE) अणु
		n = DES_BLOCK_SIZE;
		अगर (nbytes >= 2*DES_BLOCK_SIZE && locked)
			n = __ctrblk_init(ctrblk, walk.iv, nbytes);
		ctrptr = (n > DES_BLOCK_SIZE) ? ctrblk : walk.iv;
		cpacf_kmctr(fc, ctx->key, walk.dst.virt.addr,
			    walk.src.virt.addr, n, ctrptr);
		अगर (ctrptr == ctrblk)
			स_नकल(walk.iv, ctrptr + n - DES_BLOCK_SIZE,
				DES_BLOCK_SIZE);
		crypto_inc(walk.iv, DES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, nbytes - n);
	पूर्ण
	अगर (locked)
		mutex_unlock(&ctrblk_lock);
	/* final block may be < DES_BLOCK_SIZE, copy only nbytes */
	अगर (nbytes) अणु
		cpacf_kmctr(fc, ctx->key, buf, walk.src.virt.addr,
			    DES_BLOCK_SIZE, walk.iv);
		स_नकल(walk.dst.virt.addr, buf, nbytes);
		crypto_inc(walk.iv, DES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ctr_des_crypt(काष्ठा skcipher_request *req)
अणु
	वापस ctr_desall_crypt(req, CPACF_KMCTR_DEA);
पूर्ण

अटल काष्ठा skcipher_alg ctr_des_alg = अणु
	.base.cra_name		=	"ctr(des)",
	.base.cra_driver_name	=	"ctr-des-s390",
	.base.cra_priority	=	400,	/* combo: des + ctr */
	.base.cra_blocksize	=	1,
	.base.cra_ctxsize	=	माप(काष्ठा s390_des_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	DES_KEY_SIZE,
	.max_keysize		=	DES_KEY_SIZE,
	.ivsize			=	DES_BLOCK_SIZE,
	.setkey			=	des_setkey_skcipher,
	.encrypt		=	ctr_des_crypt,
	.decrypt		=	ctr_des_crypt,
	.chunksize		=	DES_BLOCK_SIZE,
पूर्ण;

अटल पूर्णांक ctr_des3_crypt(काष्ठा skcipher_request *req)
अणु
	वापस ctr_desall_crypt(req, CPACF_KMCTR_TDEA_192);
पूर्ण

अटल काष्ठा skcipher_alg ctr_des3_alg = अणु
	.base.cra_name		=	"ctr(des3_ede)",
	.base.cra_driver_name	=	"ctr-des3_ede-s390",
	.base.cra_priority	=	400,	/* combo: des3 + ede */
	.base.cra_blocksize	=	1,
	.base.cra_ctxsize	=	माप(काष्ठा s390_des_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	DES3_KEY_SIZE,
	.max_keysize		=	DES3_KEY_SIZE,
	.ivsize			=	DES_BLOCK_SIZE,
	.setkey			=	des3_setkey_skcipher,
	.encrypt		=	ctr_des3_crypt,
	.decrypt		=	ctr_des3_crypt,
	.chunksize		=	DES_BLOCK_SIZE,
पूर्ण;

अटल काष्ठा crypto_alg *des_s390_algs_ptr[2];
अटल पूर्णांक des_s390_algs_num;
अटल काष्ठा skcipher_alg *des_s390_skciphers_ptr[6];
अटल पूर्णांक des_s390_skciphers_num;

अटल पूर्णांक des_s390_रेजिस्टर_alg(काष्ठा crypto_alg *alg)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_alg(alg);
	अगर (!ret)
		des_s390_algs_ptr[des_s390_algs_num++] = alg;
	वापस ret;
पूर्ण

अटल पूर्णांक des_s390_रेजिस्टर_skcipher(काष्ठा skcipher_alg *alg)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_skcipher(alg);
	अगर (!ret)
		des_s390_skciphers_ptr[des_s390_skciphers_num++] = alg;
	वापस ret;
पूर्ण

अटल व्योम des_s390_निकास(व्योम)
अणु
	जबतक (des_s390_algs_num--)
		crypto_unरेजिस्टर_alg(des_s390_algs_ptr[des_s390_algs_num]);
	जबतक (des_s390_skciphers_num--)
		crypto_unरेजिस्टर_skcipher(des_s390_skciphers_ptr[des_s390_skciphers_num]);
	अगर (ctrblk)
		मुक्त_page((अचिन्हित दीर्घ) ctrblk);
पूर्ण

अटल पूर्णांक __init des_s390_init(व्योम)
अणु
	पूर्णांक ret;

	/* Query available functions क्रम KM, KMC and KMCTR */
	cpacf_query(CPACF_KM, &km_functions);
	cpacf_query(CPACF_KMC, &kmc_functions);
	cpacf_query(CPACF_KMCTR, &kmctr_functions);

	अगर (cpacf_test_func(&km_functions, CPACF_KM_DEA)) अणु
		ret = des_s390_रेजिस्टर_alg(&des_alg);
		अगर (ret)
			जाओ out_err;
		ret = des_s390_रेजिस्टर_skcipher(&ecb_des_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण
	अगर (cpacf_test_func(&kmc_functions, CPACF_KMC_DEA)) अणु
		ret = des_s390_रेजिस्टर_skcipher(&cbc_des_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण
	अगर (cpacf_test_func(&km_functions, CPACF_KM_TDEA_192)) अणु
		ret = des_s390_रेजिस्टर_alg(&des3_alg);
		अगर (ret)
			जाओ out_err;
		ret = des_s390_रेजिस्टर_skcipher(&ecb_des3_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण
	अगर (cpacf_test_func(&kmc_functions, CPACF_KMC_TDEA_192)) अणु
		ret = des_s390_रेजिस्टर_skcipher(&cbc_des3_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&kmctr_functions, CPACF_KMCTR_DEA) ||
	    cpacf_test_func(&kmctr_functions, CPACF_KMCTR_TDEA_192)) अणु
		ctrblk = (u8 *) __get_मुक्त_page(GFP_KERNEL);
		अगर (!ctrblk) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (cpacf_test_func(&kmctr_functions, CPACF_KMCTR_DEA)) अणु
		ret = des_s390_रेजिस्टर_skcipher(&ctr_des_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण
	अगर (cpacf_test_func(&kmctr_functions, CPACF_KMCTR_TDEA_192)) अणु
		ret = des_s390_रेजिस्टर_skcipher(&ctr_des3_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	वापस 0;
out_err:
	des_s390_निकास();
	वापस ret;
पूर्ण

module_cpu_feature_match(MSA, des_s390_init);
module_निकास(des_s390_निकास);

MODULE_ALIAS_CRYPTO("des");
MODULE_ALIAS_CRYPTO("des3_ede");

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DES & Triple DES EDE Cipher Algorithms");
