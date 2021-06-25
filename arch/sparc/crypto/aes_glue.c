<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम AES encryption optimized क्रम sparc64 crypto opcodes.
 *
 * This is based largely upon arch/x86/crypto/aesni-पूर्णांकel_glue.c
 *
 * Copyright (C) 2008, Intel Corp.
 *    Author: Huang Ying <ying.huang@पूर्णांकel.com>
 *
 * Added RFC4106 AES-GCM support क्रम 128-bit keys under the AEAD
 * पूर्णांकerface क्रम 64-bit kernels.
 *    Authors: Adrian Hoban <adrian.hoban@पूर्णांकel.com>
 *             Gabriele Paoloni <gabriele.paoloni@पूर्णांकel.com>
 *             Tadeusz Struk (tadeusz.struk@पूर्णांकel.com)
 *             Aidan O'Mahony (aidan.o.mahony@पूर्णांकel.com)
 *    Copyright (c) 2010, Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

काष्ठा aes_ops अणु
	व्योम (*encrypt)(स्थिर u64 *key, स्थिर u32 *input, u32 *output);
	व्योम (*decrypt)(स्थिर u64 *key, स्थिर u32 *input, u32 *output);
	व्योम (*load_encrypt_keys)(स्थिर u64 *key);
	व्योम (*load_decrypt_keys)(स्थिर u64 *key);
	व्योम (*ecb_encrypt)(स्थिर u64 *key, स्थिर u64 *input, u64 *output,
			    अचिन्हित पूर्णांक len);
	व्योम (*ecb_decrypt)(स्थिर u64 *key, स्थिर u64 *input, u64 *output,
			    अचिन्हित पूर्णांक len);
	व्योम (*cbc_encrypt)(स्थिर u64 *key, स्थिर u64 *input, u64 *output,
			    अचिन्हित पूर्णांक len, u64 *iv);
	व्योम (*cbc_decrypt)(स्थिर u64 *key, स्थिर u64 *input, u64 *output,
			    अचिन्हित पूर्णांक len, u64 *iv);
	व्योम (*ctr_crypt)(स्थिर u64 *key, स्थिर u64 *input, u64 *output,
			  अचिन्हित पूर्णांक len, u64 *iv);
पूर्ण;

काष्ठा crypto_sparc64_aes_ctx अणु
	काष्ठा aes_ops *ops;
	u64 key[AES_MAX_KEYLENGTH / माप(u64)];
	u32 key_length;
	u32 expanded_key_length;
पूर्ण;

बाह्य व्योम aes_sparc64_encrypt_128(स्थिर u64 *key, स्थिर u32 *input,
				    u32 *output);
बाह्य व्योम aes_sparc64_encrypt_192(स्थिर u64 *key, स्थिर u32 *input,
				    u32 *output);
बाह्य व्योम aes_sparc64_encrypt_256(स्थिर u64 *key, स्थिर u32 *input,
				    u32 *output);

बाह्य व्योम aes_sparc64_decrypt_128(स्थिर u64 *key, स्थिर u32 *input,
				    u32 *output);
बाह्य व्योम aes_sparc64_decrypt_192(स्थिर u64 *key, स्थिर u32 *input,
				    u32 *output);
बाह्य व्योम aes_sparc64_decrypt_256(स्थिर u64 *key, स्थिर u32 *input,
				    u32 *output);

बाह्य व्योम aes_sparc64_load_encrypt_keys_128(स्थिर u64 *key);
बाह्य व्योम aes_sparc64_load_encrypt_keys_192(स्थिर u64 *key);
बाह्य व्योम aes_sparc64_load_encrypt_keys_256(स्थिर u64 *key);

बाह्य व्योम aes_sparc64_load_decrypt_keys_128(स्थिर u64 *key);
बाह्य व्योम aes_sparc64_load_decrypt_keys_192(स्थिर u64 *key);
बाह्य व्योम aes_sparc64_load_decrypt_keys_256(स्थिर u64 *key);

बाह्य व्योम aes_sparc64_ecb_encrypt_128(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len);
बाह्य व्योम aes_sparc64_ecb_encrypt_192(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len);
बाह्य व्योम aes_sparc64_ecb_encrypt_256(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len);

बाह्य व्योम aes_sparc64_ecb_decrypt_128(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len);
बाह्य व्योम aes_sparc64_ecb_decrypt_192(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len);
बाह्य व्योम aes_sparc64_ecb_decrypt_256(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len);

बाह्य व्योम aes_sparc64_cbc_encrypt_128(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len,
					u64 *iv);

बाह्य व्योम aes_sparc64_cbc_encrypt_192(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len,
					u64 *iv);

बाह्य व्योम aes_sparc64_cbc_encrypt_256(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len,
					u64 *iv);

बाह्य व्योम aes_sparc64_cbc_decrypt_128(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len,
					u64 *iv);

बाह्य व्योम aes_sparc64_cbc_decrypt_192(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len,
					u64 *iv);

बाह्य व्योम aes_sparc64_cbc_decrypt_256(स्थिर u64 *key, स्थिर u64 *input,
					u64 *output, अचिन्हित पूर्णांक len,
					u64 *iv);

बाह्य व्योम aes_sparc64_ctr_crypt_128(स्थिर u64 *key, स्थिर u64 *input,
				      u64 *output, अचिन्हित पूर्णांक len,
				      u64 *iv);
बाह्य व्योम aes_sparc64_ctr_crypt_192(स्थिर u64 *key, स्थिर u64 *input,
				      u64 *output, अचिन्हित पूर्णांक len,
				      u64 *iv);
बाह्य व्योम aes_sparc64_ctr_crypt_256(स्थिर u64 *key, स्थिर u64 *input,
				      u64 *output, अचिन्हित पूर्णांक len,
				      u64 *iv);

अटल काष्ठा aes_ops aes128_ops = अणु
	.encrypt		= aes_sparc64_encrypt_128,
	.decrypt		= aes_sparc64_decrypt_128,
	.load_encrypt_keys	= aes_sparc64_load_encrypt_keys_128,
	.load_decrypt_keys	= aes_sparc64_load_decrypt_keys_128,
	.ecb_encrypt		= aes_sparc64_ecb_encrypt_128,
	.ecb_decrypt		= aes_sparc64_ecb_decrypt_128,
	.cbc_encrypt		= aes_sparc64_cbc_encrypt_128,
	.cbc_decrypt		= aes_sparc64_cbc_decrypt_128,
	.ctr_crypt		= aes_sparc64_ctr_crypt_128,
पूर्ण;

अटल काष्ठा aes_ops aes192_ops = अणु
	.encrypt		= aes_sparc64_encrypt_192,
	.decrypt		= aes_sparc64_decrypt_192,
	.load_encrypt_keys	= aes_sparc64_load_encrypt_keys_192,
	.load_decrypt_keys	= aes_sparc64_load_decrypt_keys_192,
	.ecb_encrypt		= aes_sparc64_ecb_encrypt_192,
	.ecb_decrypt		= aes_sparc64_ecb_decrypt_192,
	.cbc_encrypt		= aes_sparc64_cbc_encrypt_192,
	.cbc_decrypt		= aes_sparc64_cbc_decrypt_192,
	.ctr_crypt		= aes_sparc64_ctr_crypt_192,
पूर्ण;

अटल काष्ठा aes_ops aes256_ops = अणु
	.encrypt		= aes_sparc64_encrypt_256,
	.decrypt		= aes_sparc64_decrypt_256,
	.load_encrypt_keys	= aes_sparc64_load_encrypt_keys_256,
	.load_decrypt_keys	= aes_sparc64_load_decrypt_keys_256,
	.ecb_encrypt		= aes_sparc64_ecb_encrypt_256,
	.ecb_decrypt		= aes_sparc64_ecb_decrypt_256,
	.cbc_encrypt		= aes_sparc64_cbc_encrypt_256,
	.cbc_decrypt		= aes_sparc64_cbc_decrypt_256,
	.ctr_crypt		= aes_sparc64_ctr_crypt_256,
पूर्ण;

बाह्य व्योम aes_sparc64_key_expand(स्थिर u32 *in_key, u64 *output_key,
				   अचिन्हित पूर्णांक key_len);

अटल पूर्णांक aes_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		ctx->expanded_key_length = 0xb0;
		ctx->ops = &aes128_ops;
		अवरोध;

	हाल AES_KEYSIZE_192:
		ctx->expanded_key_length = 0xd0;
		ctx->ops = &aes192_ops;
		अवरोध;

	हाल AES_KEYSIZE_256:
		ctx->expanded_key_length = 0xf0;
		ctx->ops = &aes256_ops;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	aes_sparc64_key_expand((स्थिर u32 *)in_key, &ctx->key[0], key_len);
	ctx->key_length = key_len;

	वापस 0;
पूर्ण

अटल पूर्णांक aes_set_key_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
				अचिन्हित पूर्णांक key_len)
अणु
	वापस aes_set_key(crypto_skcipher_tfm(tfm), in_key, key_len);
पूर्ण

अटल व्योम crypto_aes_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->ops->encrypt(&ctx->key[0], (स्थिर u32 *) src, (u32 *) dst);
पूर्ण

अटल व्योम crypto_aes_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->ops->decrypt(&ctx->key[0], (स्थिर u32 *) src, (u32 *) dst);
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	ctx->ops->load_encrypt_keys(&ctx->key[0]);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		ctx->ops->ecb_encrypt(&ctx->key[0], walk.src.virt.addr,
				      walk.dst.virt.addr,
				      round_करोwn(nbytes, AES_BLOCK_SIZE));
		err = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	स्थिर u64 *key_end;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	ctx->ops->load_decrypt_keys(&ctx->key[0]);
	key_end = &ctx->key[ctx->expanded_key_length / माप(u64)];
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		ctx->ops->ecb_decrypt(key_end, walk.src.virt.addr,
				      walk.dst.virt.addr,
				      round_करोwn(nbytes, AES_BLOCK_SIZE));
		err = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);

	वापस err;
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	ctx->ops->load_encrypt_keys(&ctx->key[0]);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		ctx->ops->cbc_encrypt(&ctx->key[0], walk.src.virt.addr,
				      walk.dst.virt.addr,
				      round_करोwn(nbytes, AES_BLOCK_SIZE),
				      walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	स्थिर u64 *key_end;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	ctx->ops->load_decrypt_keys(&ctx->key[0]);
	key_end = &ctx->key[ctx->expanded_key_length / माप(u64)];
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		ctx->ops->cbc_decrypt(key_end, walk.src.virt.addr,
				      walk.dst.virt.addr,
				      round_करोwn(nbytes, AES_BLOCK_SIZE),
				      walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण
	fprs_ग_लिखो(0);

	वापस err;
पूर्ण

अटल व्योम ctr_crypt_final(स्थिर काष्ठा crypto_sparc64_aes_ctx *ctx,
			    काष्ठा skcipher_walk *walk)
अणु
	u8 *ctrblk = walk->iv;
	u64 keystream[AES_BLOCK_SIZE / माप(u64)];
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;

	ctx->ops->ecb_encrypt(&ctx->key[0], (स्थिर u64 *)ctrblk,
			      keystream, AES_BLOCK_SIZE);
	crypto_xor_cpy(dst, (u8 *) keystream, src, nbytes);
	crypto_inc(ctrblk, AES_BLOCK_SIZE);
पूर्ण

अटल पूर्णांक ctr_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा crypto_sparc64_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, true);
	अगर (err)
		वापस err;

	ctx->ops->load_encrypt_keys(&ctx->key[0]);
	जबतक ((nbytes = walk.nbytes) >= AES_BLOCK_SIZE) अणु
		ctx->ops->ctr_crypt(&ctx->key[0], walk.src.virt.addr,
				    walk.dst.virt.addr,
				    round_करोwn(nbytes, AES_BLOCK_SIZE),
				    walk.iv);
		err = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण
	अगर (walk.nbytes) अणु
		ctr_crypt_final(ctx, &walk);
		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण
	fprs_ग_लिखो(0);
	वापस err;
पूर्ण

अटल काष्ठा crypto_alg cipher_alg = अणु
	.cra_name		= "aes",
	.cra_driver_name	= "aes-sparc64",
	.cra_priority		= SPARC_CR_OPCODE_PRIORITY,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= AES_BLOCK_SIZE,
	.cra_ctxsize		= माप(काष्ठा crypto_sparc64_aes_ctx),
	.cra_alignmask		= 3,
	.cra_module		= THIS_MODULE,
	.cra_u	= अणु
		.cipher	= अणु
			.cia_min_keysize	= AES_MIN_KEY_SIZE,
			.cia_max_keysize	= AES_MAX_KEY_SIZE,
			.cia_setkey		= aes_set_key,
			.cia_encrypt		= crypto_aes_encrypt,
			.cia_decrypt		= crypto_aes_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg skcipher_algs[] = अणु
	अणु
		.base.cra_name		= "ecb(aes)",
		.base.cra_driver_name	= "ecb-aes-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा crypto_sparc64_aes_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= aes_set_key_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_driver_name	= "cbc-aes-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा crypto_sparc64_aes_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
		.setkey			= aes_set_key_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "ctr(aes)",
		.base.cra_driver_name	= "ctr-aes-sparc64",
		.base.cra_priority	= SPARC_CR_OPCODE_PRIORITY,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा crypto_sparc64_aes_ctx),
		.base.cra_alignmask	= 7,
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
		.setkey			= aes_set_key_skcipher,
		.encrypt		= ctr_crypt,
		.decrypt		= ctr_crypt,
		.chunksize		= AES_BLOCK_SIZE,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_aes_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_AES))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init aes_sparc64_mod_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!sparc64_has_aes_opcode()) अणु
		pr_info("sparc64 aes opcodes not available.\n");
		वापस -ENODEV;
	पूर्ण
	pr_info("Using sparc64 aes opcodes optimized AES implementation\n");
	err = crypto_रेजिस्टर_alg(&cipher_alg);
	अगर (err)
		वापस err;
	err = crypto_रेजिस्टर_skciphers(skcipher_algs,
					ARRAY_SIZE(skcipher_algs));
	अगर (err)
		crypto_unरेजिस्टर_alg(&cipher_alg);
	वापस err;
पूर्ण

अटल व्योम __निकास aes_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&cipher_alg);
	crypto_unरेजिस्टर_skciphers(skcipher_algs, ARRAY_SIZE(skcipher_algs));
पूर्ण

module_init(aes_sparc64_mod_init);
module_निकास(aes_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Rijndael (AES) Cipher Algorithm, sparc64 aes opcode accelerated");

MODULE_ALIAS_CRYPTO("aes");

#समावेश "crop_devid.c"
