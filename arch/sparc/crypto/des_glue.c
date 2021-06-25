<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम DES encryption optimized क्रम sparc64 crypto opcodes.
 *
 * Copyright (C) 2012 David S. Miller <davem@davemloft.net>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

काष्ठा des_sparc64_ctx अणु
	u64 encrypt_expkey[DES_EXPKEY_WORDS / 2];
	u64 decrypt_expkey[DES_EXPKEY_WORDS / 2];
पूर्ण;

काष्ठा des3_ede_sparc64_ctx अणु
	u64 encrypt_expkey[DES3_EDE_EXPKEY_WORDS / 2];
	u64 decrypt_expkey[DES3_EDE_EXPKEY_WORDS / 2];
पूर्ण;

अटल व्योम encrypt_to_decrypt(u64 *d, स्थिर u64 *e)
अणु
	स्थिर u64 *s = e + (DES_EXPKEY_WORDS / 2) - 1;
	पूर्णांक i;

	क्रम (i = 0; i < DES_EXPKEY_WORDS / 2; i++)
		*d++ = *s--;
पूर्ण

बाह्य व्योम des_sparc64_key_expand(स्थिर u32 *input_key, u64 *key);

अटल पूर्णांक des_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा des_sparc64_ctx *dctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	/* Even though we have special inकाष्ठाions क्रम key expansion,
	 * we call des_verअगरy_key() so that we करोn't have to ग_लिखो our own
	 * weak key detection code.
	 */
	err = crypto_des_verअगरy_key(tfm, key);
	अगर (err)
		वापस err;

	des_sparc64_key_expand((स्थिर u32 *) key, &dctx->encrypt_expkey[0]);
	encrypt_to_decrypt(&dctx->decrypt_expkey[0], &dctx->encrypt_expkey[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक des_set_key_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	वापस des_set_key(crypto_skcipher_tfm(tfm), key, keylen);
पूर्ण

बाह्य व्योम des_sparc64_crypt(स्थिर u64 *key, स्थिर u64 *input,
			      u64 *output);

अटल व्योम sparc_des_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा des_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u64 *K = ctx->encrypt_expkey;

	des_sparc64_crypt(K, (स्थिर u64 *) src, (u64 *) dst);
पूर्ण

अटल व्योम sparc_des_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा des_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u64 *K = ctx->decrypt_expkey;

	des_sparc64_crypt(K, (स्थिर u64 *) src, (u64 *) dst);
पूर्ण

बाह्य व्योम des_sparc64_load_keys(स्थिर u64 *key);

बाह्य व्योम des_sparc64_ecb_crypt(स्थिर u64 *input, u64 *output,
				  अचिन्हित पूर्णांक len);

अटल पूर्णांक __ecb_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा des_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	अगर (encrypt)
		des_sparc64_load_keys(&ctx->encrypt_expkey[0]);
	अन्यथा
		des_sparc64_load_keys(&ctx->decrypt_expkey[0]);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		des_sparc64_ecb_crypt(walk.src.virt.addr, walk.dst.virt.addr,
				      round_करोwn(nbytes, DES_BLOCK_SIZE));
		err = skcipher_walk_करोne(&walk, nbytes % DES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस __ecb_crypt(req, true);
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस __ecb_crypt(req, false);
पूर्ण

बाह्य व्योम des_sparc64_cbc_encrypt(स्थिर u64 *input, u64 *output,
				    अचिन्हित पूर्णांक len, u64 *iv);

बाह्य व्योम des_sparc64_cbc_decrypt(स्थिर u64 *input, u64 *output,
				    अचिन्हित पूर्णांक len, u64 *iv);

अटल पूर्णांक __cbc_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा des_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	अगर (encrypt)
		des_sparc64_load_keys(&ctx->encrypt_expkey[0]);
	अन्यथा
		des_sparc64_load_keys(&ctx->decrypt_expkey[0]);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		अगर (encrypt)
			des_sparc64_cbc_encrypt(walk.src.virt.addr,
						walk.dst.virt.addr,
						round_करोwn(nbytes,
							   DES_BLOCK_SIZE),
						walk.iv);
		अन्यथा
			des_sparc64_cbc_decrypt(walk.src.virt.addr,
						walk.dst.virt.addr,
						round_करोwn(nbytes,
							   DES_BLOCK_SIZE),
						walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % DES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस __cbc_crypt(req, true);
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस __cbc_crypt(req, false);
पूर्ण

अटल पूर्णांक des3_ede_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा des3_ede_sparc64_ctx *dctx = crypto_tfm_ctx(tfm);
	u64 k1[DES_EXPKEY_WORDS / 2];
	u64 k2[DES_EXPKEY_WORDS / 2];
	u64 k3[DES_EXPKEY_WORDS / 2];
	पूर्णांक err;

	err = crypto_des3_ede_verअगरy_key(tfm, key);
	अगर (err)
		वापस err;

	des_sparc64_key_expand((स्थिर u32 *)key, k1);
	key += DES_KEY_SIZE;
	des_sparc64_key_expand((स्थिर u32 *)key, k2);
	key += DES_KEY_SIZE;
	des_sparc64_key_expand((स्थिर u32 *)key, k3);

	स_नकल(&dctx->encrypt_expkey[0], &k1[0], माप(k1));
	encrypt_to_decrypt(&dctx->encrypt_expkey[DES_EXPKEY_WORDS / 2], &k2[0]);
	स_नकल(&dctx->encrypt_expkey[(DES_EXPKEY_WORDS / 2) * 2],
	       &k3[0], माप(k3));

	encrypt_to_decrypt(&dctx->decrypt_expkey[0], &k3[0]);
	स_नकल(&dctx->decrypt_expkey[DES_EXPKEY_WORDS / 2],
	       &k2[0], माप(k2));
	encrypt_to_decrypt(&dctx->decrypt_expkey[(DES_EXPKEY_WORDS / 2) * 2],
			   &k1[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक des3_ede_set_key_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				     अचिन्हित पूर्णांक keylen)
अणु
	वापस des3_ede_set_key(crypto_skcipher_tfm(tfm), key, keylen);
पूर्ण

बाह्य व्योम des3_ede_sparc64_crypt(स्थिर u64 *key, स्थिर u64 *input,
				   u64 *output);

अटल व्योम sparc_des3_ede_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा des3_ede_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u64 *K = ctx->encrypt_expkey;

	des3_ede_sparc64_crypt(K, (स्थिर u64 *) src, (u64 *) dst);
पूर्ण

अटल व्योम sparc_des3_ede_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा des3_ede_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u64 *K = ctx->decrypt_expkey;

	des3_ede_sparc64_crypt(K, (स्थिर u64 *) src, (u64 *) dst);
पूर्ण

बाह्य व्योम des3_ede_sparc64_load_keys(स्थिर u64 *key);

बाह्य व्योम des3_ede_sparc64_ecb_crypt(स्थिर u64 *expkey, स्थिर u64 *input,
				       u64 *output, अचिन्हित पूर्णांक len);

अटल पूर्णांक __ecb3_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा des3_ede_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	स्थिर u64 *K;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	अगर (encrypt)
		K = &ctx->encrypt_expkey[0];
	अन्यथा
		K = &ctx->decrypt_expkey[0];
	des3_ede_sparc64_load_keys(K);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		des3_ede_sparc64_ecb_crypt(K, walk.src.virt.addr,
					   walk.dst.virt.addr,
					   round_करोwn(nbytes, DES_BLOCK_SIZE));
		err = skcipher_walk_करोne(&walk, nbytes % DES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक ecb3_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस __ecb3_crypt(req, true);
पूर्ण

अटल पूर्णांक ecb3_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस __ecb3_crypt(req, false);
पूर्ण

बाह्य व्योम des3_ede_sparc64_cbc_encrypt(स्थिर u64 *expkey, स्थिर u64 *input,
					 u64 *output, अचिन्हित पूर्णांक len,
					 u64 *iv);

बाह्य व्योम des3_ede_sparc64_cbc_decrypt(स्थिर u64 *expkey, स्थिर u64 *input,
					 u64 *output, अचिन्हित पूर्णांक len,
					 u64 *iv);

अटल पूर्णांक __cbc3_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा des3_ede_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	स्थिर u64 *K;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	अगर (encrypt)
		K = &ctx->encrypt_expkey[0];
	अन्यथा
		K = &ctx->decrypt_expkey[0];
	des3_ede_sparc64_load_keys(K);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		अगर (encrypt)
			des3_ede_sparc64_cbc_encrypt(K, walk.src.virt.addr,
						     walk.dst.virt.addr,
						     round_करोwn(nbytes,
								DES_BLOCK_SIZE),
						     walk.iv);
		अन्यथा
			des3_ede_sparc64_cbc_decrypt(K, walk.src.virt.addr,
						     walk.dst.virt.addr,
						     round_करोwn(nbytes,
								DES_BLOCK_SIZE),
						     walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % DES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक cbc3_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस __cbc3_crypt(req, true);
पूर्ण

अटल पूर्णांक cbc3_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस __cbc3_crypt(req, false);
पूर्ण

अटल काष्ठा crypto_alg cipher_algs[] = अणु
	अणु
		.cra_name		= "des",
		.cra_driver_name	= "des-sparc64",
		.cra_priority		= SPARC_CR_OPCODE_PRIORITY,
		.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
		.cra_blocksize		= DES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा des_sparc64_ctx),
		.cra_alignmask		= 7,
		.cra_module		= THIS_MODULE,
		.cra_u	= अणु
			.cipher	= अणु
				.cia_min_keysize	= DES_KEY_SIZE,
				.cia_max_keysize	= DES_KEY_SIZE,
				.cia_setkey		= des_set_key,
				.cia_encrypt		= sparc_des_encrypt,
				.cia_decrypt		= sparc_des_decrypt
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.cra_name		= "des3_ede",
		.cra_driver_name	= "des3_ede-sparc64",
		.cra_priority		= SPARC_CR_OPCODE_PRIORITY,
		.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
		.cra_blocksize		= DES3_EDE_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा des3_ede_sparc64_ctx),
		.cra_alignmask		= 7,
		.cra_module		= THIS_MODULE,
		.cra_u	= अणु
			.cipher	= अणु
				.cia_min_keysize	= DES3_EDE_KEY_SIZE,
				.cia_max_keysize	= DES3_EDE_KEY_SIZE,
				.cia_setkey		= des3_ede_set_key,
				.cia_encrypt		= sparc_des3_ede_encrypt,
				.cia_decrypt		= sparc_des3_ede_decrypt
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg skcipher_algs[] = अणु
	अणु
		.base.cra_name		= "ecb(des)",
		.base.cra_driver_name	= "ecb-des-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा des_sparc64_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
		.setkey			= des_set_key_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(des)",
		.base.cra_driver_name	= "cbc-des-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा des_sparc64_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
		.ivsize			= DES_BLOCK_SIZE,
		.setkey			= des_set_key_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "ecb(des3_ede)",
		.base.cra_driver_name	= "ecb-des3_ede-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा des3_ede_sparc64_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.setkey			= des3_ede_set_key_skcipher,
		.encrypt		= ecb3_encrypt,
		.decrypt		= ecb3_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(des3_ede)",
		.base.cra_driver_name	= "cbc-des3_ede-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा des3_ede_sparc64_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES3_EDE_BLOCK_SIZE,
		.setkey			= des3_ede_set_key_skcipher,
		.encrypt		= cbc3_encrypt,
		.decrypt		= cbc3_decrypt,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_des_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_DES))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init des_sparc64_mod_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!sparc64_has_des_opcode()) अणु
		pr_info("sparc64 des opcodes not available.\n");
		वापस -ENODEV;
	पूर्ण
	pr_info("Using sparc64 des opcodes optimized DES implementation\n");
	err = crypto_रेजिस्टर_algs(cipher_algs, ARRAY_SIZE(cipher_algs));
	अगर (err)
		वापस err;
	err = crypto_रेजिस्टर_skciphers(skcipher_algs,
					ARRAY_SIZE(skcipher_algs));
	अगर (err)
		crypto_unरेजिस्टर_algs(cipher_algs, ARRAY_SIZE(cipher_algs));
	वापस err;
पूर्ण

अटल व्योम __निकास des_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_algs(cipher_algs, ARRAY_SIZE(cipher_algs));
	crypto_unरेजिस्टर_skciphers(skcipher_algs, ARRAY_SIZE(skcipher_algs));
पूर्ण

module_init(des_sparc64_mod_init);
module_निकास(des_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DES & Triple DES EDE Cipher Algorithms, sparc64 des opcode accelerated");

MODULE_ALIAS_CRYPTO("des");
MODULE_ALIAS_CRYPTO("des3_ede");

#समावेश "crop_devid.c"
