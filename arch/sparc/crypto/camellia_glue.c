<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम CAMELLIA encryption optimized क्रम sparc64 crypto opcodes.
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
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

#घोषणा CAMELLIA_MIN_KEY_SIZE        16
#घोषणा CAMELLIA_MAX_KEY_SIZE        32
#घोषणा CAMELLIA_BLOCK_SIZE          16
#घोषणा CAMELLIA_TABLE_BYTE_LEN     272

काष्ठा camellia_sparc64_ctx अणु
	u64 encrypt_key[CAMELLIA_TABLE_BYTE_LEN / माप(u64)];
	u64 decrypt_key[CAMELLIA_TABLE_BYTE_LEN / माप(u64)];
	पूर्णांक key_len;
पूर्ण;

बाह्य व्योम camellia_sparc64_key_expand(स्थिर u32 *in_key, u64 *encrypt_key,
					अचिन्हित पूर्णांक key_len, u64 *decrypt_key);

अटल पूर्णांक camellia_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *_in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा camellia_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u32 *in_key = (स्थिर u32 *) _in_key;

	अगर (key_len != 16 && key_len != 24 && key_len != 32)
		वापस -EINVAL;

	ctx->key_len = key_len;

	camellia_sparc64_key_expand(in_key, &ctx->encrypt_key[0],
				    key_len, &ctx->decrypt_key[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक camellia_set_key_skcipher(काष्ठा crypto_skcipher *tfm,
				     स्थिर u8 *in_key, अचिन्हित पूर्णांक key_len)
अणु
	वापस camellia_set_key(crypto_skcipher_tfm(tfm), in_key, key_len);
पूर्ण

बाह्य व्योम camellia_sparc64_crypt(स्थिर u64 *key, स्थिर u32 *input,
				   u32 *output, अचिन्हित पूर्णांक key_len);

अटल व्योम camellia_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा camellia_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);

	camellia_sparc64_crypt(&ctx->encrypt_key[0],
			       (स्थिर u32 *) src,
			       (u32 *) dst, ctx->key_len);
पूर्ण

अटल व्योम camellia_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा camellia_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);

	camellia_sparc64_crypt(&ctx->decrypt_key[0],
			       (स्थिर u32 *) src,
			       (u32 *) dst, ctx->key_len);
पूर्ण

बाह्य व्योम camellia_sparc64_load_keys(स्थिर u64 *key, अचिन्हित पूर्णांक key_len);

प्रकार व्योम ecb_crypt_op(स्थिर u64 *input, u64 *output, अचिन्हित पूर्णांक len,
			  स्थिर u64 *key);

बाह्य ecb_crypt_op camellia_sparc64_ecb_crypt_3_gअक्रम_rounds;
बाह्य ecb_crypt_op camellia_sparc64_ecb_crypt_4_gअक्रम_rounds;

अटल पूर्णांक __ecb_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा camellia_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	ecb_crypt_op *op;
	स्थिर u64 *key;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	op = camellia_sparc64_ecb_crypt_3_gअक्रम_rounds;
	अगर (ctx->key_len != 16)
		op = camellia_sparc64_ecb_crypt_4_gअक्रम_rounds;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	अगर (encrypt)
		key = &ctx->encrypt_key[0];
	अन्यथा
		key = &ctx->decrypt_key[0];
	camellia_sparc64_load_keys(key, ctx->key_len);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		op(walk.src.virt.addr, walk.dst.virt.addr,
		   round_करोwn(nbytes, CAMELLIA_BLOCK_SIZE), key);
		err = skcipher_walk_करोne(&walk, nbytes % CAMELLIA_BLOCK_SIZE);
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

प्रकार व्योम cbc_crypt_op(स्थिर u64 *input, u64 *output, अचिन्हित पूर्णांक len,
			  स्थिर u64 *key, u64 *iv);

बाह्य cbc_crypt_op camellia_sparc64_cbc_encrypt_3_gअक्रम_rounds;
बाह्य cbc_crypt_op camellia_sparc64_cbc_encrypt_4_gअक्रम_rounds;
बाह्य cbc_crypt_op camellia_sparc64_cbc_decrypt_3_gअक्रम_rounds;
बाह्य cbc_crypt_op camellia_sparc64_cbc_decrypt_4_gअक्रम_rounds;

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा camellia_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	cbc_crypt_op *op;
	स्थिर u64 *key;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	op = camellia_sparc64_cbc_encrypt_3_gअक्रम_rounds;
	अगर (ctx->key_len != 16)
		op = camellia_sparc64_cbc_encrypt_4_gअक्रम_rounds;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	key = &ctx->encrypt_key[0];
	camellia_sparc64_load_keys(key, ctx->key_len);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		op(walk.src.virt.addr, walk.dst.virt.addr,
		   round_करोwn(nbytes, CAMELLIA_BLOCK_SIZE), key, walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % CAMELLIA_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा camellia_sparc64_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	cbc_crypt_op *op;
	स्थिर u64 *key;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	op = camellia_sparc64_cbc_decrypt_3_gअक्रम_rounds;
	अगर (ctx->key_len != 16)
		op = camellia_sparc64_cbc_decrypt_4_gअक्रम_rounds;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	key = &ctx->decrypt_key[0];
	camellia_sparc64_load_keys(key, ctx->key_len);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		op(walk.src.virt.addr, walk.dst.virt.addr,
		   round_करोwn(nbytes, CAMELLIA_BLOCK_SIZE), key, walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % CAMELLIA_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल काष्ठा crypto_alg cipher_alg = अणु
	.cra_name		= "camellia",
	.cra_driver_name	= "camellia-sparc64",
	.cra_priority		= SPARC_CR_OPCODE_PRIORITY,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= CAMELLIA_BLOCK_SIZE,
	.cra_ctxsize		= माप(काष्ठा camellia_sparc64_ctx),
	.cra_alignmask		= 3,
	.cra_module		= THIS_MODULE,
	.cra_u	= अणु
		.cipher	= अणु
			.cia_min_keysize	= CAMELLIA_MIN_KEY_SIZE,
			.cia_max_keysize	= CAMELLIA_MAX_KEY_SIZE,
			.cia_setkey		= camellia_set_key,
			.cia_encrypt		= camellia_encrypt,
			.cia_decrypt		= camellia_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg skcipher_algs[] = अणु
	अणु
		.base.cra_name		= "ecb(camellia)",
		.base.cra_driver_name	= "ecb-camellia-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= CAMELLIA_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा camellia_sparc64_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= CAMELLIA_MIN_KEY_SIZE,
		.max_keysize		= CAMELLIA_MAX_KEY_SIZE,
		.setkey			= camellia_set_key_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(camellia)",
		.base.cra_driver_name	= "cbc-camellia-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= CAMELLIA_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा camellia_sparc64_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= CAMELLIA_MIN_KEY_SIZE,
		.max_keysize		= CAMELLIA_MAX_KEY_SIZE,
		.ivsize			= CAMELLIA_BLOCK_SIZE,
		.setkey			= camellia_set_key_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_camellia_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_CAMELLIA))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init camellia_sparc64_mod_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!sparc64_has_camellia_opcode()) अणु
		pr_info("sparc64 camellia opcodes not available.\n");
		वापस -ENODEV;
	पूर्ण
	pr_info("Using sparc64 camellia opcodes optimized CAMELLIA implementation\n");
	err = crypto_रेजिस्टर_alg(&cipher_alg);
	अगर (err)
		वापस err;
	err = crypto_रेजिस्टर_skciphers(skcipher_algs,
					ARRAY_SIZE(skcipher_algs));
	अगर (err)
		crypto_unरेजिस्टर_alg(&cipher_alg);
	वापस err;
पूर्ण

अटल व्योम __निकास camellia_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&cipher_alg);
	crypto_unरेजिस्टर_skciphers(skcipher_algs, ARRAY_SIZE(skcipher_algs));
पूर्ण

module_init(camellia_sparc64_mod_init);
module_निकास(camellia_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Camellia Cipher Algorithm, sparc64 camellia opcode accelerated");

MODULE_ALIAS_CRYPTO("camellia");

#समावेश "crop_devid.c"
