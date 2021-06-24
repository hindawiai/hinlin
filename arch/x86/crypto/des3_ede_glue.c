<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम assembler optimized version of 3DES
 *
 * Copyright तऊ 2014 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 *
 * CBC & ECB parts based on code (crypto/cbc.c,ecb.c) by:
 *   Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

काष्ठा des3_ede_x86_ctx अणु
	काष्ठा des3_ede_ctx enc;
	काष्ठा des3_ede_ctx dec;
पूर्ण;

/* regular block cipher functions */
यंत्रlinkage व्योम des3_ede_x86_64_crypt_blk(स्थिर u32 *expkey, u8 *dst,
					  स्थिर u8 *src);

/* 3-way parallel cipher functions */
यंत्रlinkage व्योम des3_ede_x86_64_crypt_blk_3way(स्थिर u32 *expkey, u8 *dst,
					       स्थिर u8 *src);

अटल अंतरभूत व्योम des3_ede_enc_blk(काष्ठा des3_ede_x86_ctx *ctx, u8 *dst,
				    स्थिर u8 *src)
अणु
	u32 *enc_ctx = ctx->enc.expkey;

	des3_ede_x86_64_crypt_blk(enc_ctx, dst, src);
पूर्ण

अटल अंतरभूत व्योम des3_ede_dec_blk(काष्ठा des3_ede_x86_ctx *ctx, u8 *dst,
				    स्थिर u8 *src)
अणु
	u32 *dec_ctx = ctx->dec.expkey;

	des3_ede_x86_64_crypt_blk(dec_ctx, dst, src);
पूर्ण

अटल अंतरभूत व्योम des3_ede_enc_blk_3way(काष्ठा des3_ede_x86_ctx *ctx, u8 *dst,
					 स्थिर u8 *src)
अणु
	u32 *enc_ctx = ctx->enc.expkey;

	des3_ede_x86_64_crypt_blk_3way(enc_ctx, dst, src);
पूर्ण

अटल अंतरभूत व्योम des3_ede_dec_blk_3way(काष्ठा des3_ede_x86_ctx *ctx, u8 *dst,
					 स्थिर u8 *src)
अणु
	u32 *dec_ctx = ctx->dec.expkey;

	des3_ede_x86_64_crypt_blk_3way(dec_ctx, dst, src);
पूर्ण

अटल व्योम des3_ede_x86_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	des3_ede_enc_blk(crypto_tfm_ctx(tfm), dst, src);
पूर्ण

अटल व्योम des3_ede_x86_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	des3_ede_dec_blk(crypto_tfm_ctx(tfm), dst, src);
पूर्ण

अटल पूर्णांक ecb_crypt(काष्ठा skcipher_request *req, स्थिर u32 *expkey)
अणु
	स्थिर अचिन्हित पूर्णांक bsize = DES3_EDE_BLOCK_SIZE;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		u8 *wsrc = walk.src.virt.addr;
		u8 *wdst = walk.dst.virt.addr;

		/* Process four block batch */
		अगर (nbytes >= bsize * 3) अणु
			करो अणु
				des3_ede_x86_64_crypt_blk_3way(expkey, wdst,
							       wsrc);

				wsrc += bsize * 3;
				wdst += bsize * 3;
				nbytes -= bsize * 3;
			पूर्ण जबतक (nbytes >= bsize * 3);

			अगर (nbytes < bsize)
				जाओ करोne;
		पूर्ण

		/* Handle leftovers */
		करो अणु
			des3_ede_x86_64_crypt_blk(expkey, wdst, wsrc);

			wsrc += bsize;
			wdst += bsize;
			nbytes -= bsize;
		पूर्ण जबतक (nbytes >= bsize);

करोne:
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा des3_ede_x86_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस ecb_crypt(req, ctx->enc.expkey);
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा des3_ede_x86_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस ecb_crypt(req, ctx->dec.expkey);
पूर्ण

अटल अचिन्हित पूर्णांक __cbc_encrypt(काष्ठा des3_ede_x86_ctx *ctx,
				  काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित पूर्णांक bsize = DES3_EDE_BLOCK_SIZE;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u64 *src = (u64 *)walk->src.virt.addr;
	u64 *dst = (u64 *)walk->dst.virt.addr;
	u64 *iv = (u64 *)walk->iv;

	करो अणु
		*dst = *src ^ *iv;
		des3_ede_enc_blk(ctx, (u8 *)dst, (u8 *)dst);
		iv = dst;

		src += 1;
		dst += 1;
		nbytes -= bsize;
	पूर्ण जबतक (nbytes >= bsize);

	*(u64 *)walk->iv = *iv;
	वापस nbytes;
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा des3_ede_x86_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		nbytes = __cbc_encrypt(ctx, &walk);
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक __cbc_decrypt(काष्ठा des3_ede_x86_ctx *ctx,
				  काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित पूर्णांक bsize = DES3_EDE_BLOCK_SIZE;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u64 *src = (u64 *)walk->src.virt.addr;
	u64 *dst = (u64 *)walk->dst.virt.addr;
	u64 ivs[3 - 1];
	u64 last_iv;

	/* Start of the last block. */
	src += nbytes / bsize - 1;
	dst += nbytes / bsize - 1;

	last_iv = *src;

	/* Process four block batch */
	अगर (nbytes >= bsize * 3) अणु
		करो अणु
			nbytes -= bsize * 3 - bsize;
			src -= 3 - 1;
			dst -= 3 - 1;

			ivs[0] = src[0];
			ivs[1] = src[1];

			des3_ede_dec_blk_3way(ctx, (u8 *)dst, (u8 *)src);

			dst[1] ^= ivs[0];
			dst[2] ^= ivs[1];

			nbytes -= bsize;
			अगर (nbytes < bsize)
				जाओ करोne;

			*dst ^= *(src - 1);
			src -= 1;
			dst -= 1;
		पूर्ण जबतक (nbytes >= bsize * 3);
	पूर्ण

	/* Handle leftovers */
	क्रम (;;) अणु
		des3_ede_dec_blk(ctx, (u8 *)dst, (u8 *)src);

		nbytes -= bsize;
		अगर (nbytes < bsize)
			अवरोध;

		*dst ^= *(src - 1);
		src -= 1;
		dst -= 1;
	पूर्ण

करोne:
	*dst ^= *(u64 *)walk->iv;
	*(u64 *)walk->iv = last_iv;

	वापस nbytes;
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा des3_ede_x86_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		nbytes = __cbc_decrypt(ctx, &walk);
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक des3_ede_x86_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा des3_ede_x86_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 i, j, पंचांगp;
	पूर्णांक err;

	err = des3_ede_expand_key(&ctx->enc, key, keylen);
	अगर (err == -ENOKEY) अणु
		अगर (crypto_tfm_get_flags(tfm) & CRYPTO_TFM_REQ_FORBID_WEAK_KEYS)
			err = -EINVAL;
		अन्यथा
			err = 0;
	पूर्ण

	अगर (err) अणु
		स_रखो(ctx, 0, माप(*ctx));
		वापस err;
	पूर्ण

	/* Fix encryption context क्रम this implementation and क्रमm decryption
	 * context. */
	j = DES3_EDE_EXPKEY_WORDS - 2;
	क्रम (i = 0; i < DES3_EDE_EXPKEY_WORDS; i += 2, j -= 2) अणु
		पंचांगp = ror32(ctx->enc.expkey[i + 1], 4);
		ctx->enc.expkey[i + 1] = पंचांगp;

		ctx->dec.expkey[j + 0] = ctx->enc.expkey[i + 0];
		ctx->dec.expkey[j + 1] = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक des3_ede_x86_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
					स्थिर u8 *key,
					अचिन्हित पूर्णांक keylen)
अणु
	वापस des3_ede_x86_setkey(&tfm->base, key, keylen);
पूर्ण

अटल काष्ठा crypto_alg des3_ede_cipher = अणु
	.cra_name		= "des3_ede",
	.cra_driver_name	= "des3_ede-asm",
	.cra_priority		= 200,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= DES3_EDE_BLOCK_SIZE,
	.cra_ctxsize		= माप(काष्ठा des3_ede_x86_ctx),
	.cra_alignmask		= 0,
	.cra_module		= THIS_MODULE,
	.cra_u = अणु
		.cipher = अणु
			.cia_min_keysize	= DES3_EDE_KEY_SIZE,
			.cia_max_keysize	= DES3_EDE_KEY_SIZE,
			.cia_setkey		= des3_ede_x86_setkey,
			.cia_encrypt		= des3_ede_x86_encrypt,
			.cia_decrypt		= des3_ede_x86_decrypt,
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg des3_ede_skciphers[] = अणु
	अणु
		.base.cra_name		= "ecb(des3_ede)",
		.base.cra_driver_name	= "ecb-des3_ede-asm",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा des3_ede_x86_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.setkey			= des3_ede_x86_setkey_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(des3_ede)",
		.base.cra_driver_name	= "cbc-des3_ede-asm",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा des3_ede_x86_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES3_EDE_BLOCK_SIZE,
		.setkey			= des3_ede_x86_setkey_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण
पूर्ण;

अटल bool is_blacklisted_cpu(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस false;

	अगर (boot_cpu_data.x86 == 0x0f) अणु
		/*
		 * On Pentium 4, des3_ede-x86_64 is slower than generic C
		 * implementation because use of 64bit rotates (which are really
		 * slow on P4). Thereक्रमe blacklist P4s.
		 */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक क्रमce;
module_param(क्रमce, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमce, "Force module load, ignore CPU blacklist");

अटल पूर्णांक __init des3_ede_x86_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!क्रमce && is_blacklisted_cpu()) अणु
		pr_info("des3_ede-x86_64: performance on this CPU would be suboptimal: disabling des3_ede-x86_64.\n");
		वापस -ENODEV;
	पूर्ण

	err = crypto_रेजिस्टर_alg(&des3_ede_cipher);
	अगर (err)
		वापस err;

	err = crypto_रेजिस्टर_skciphers(des3_ede_skciphers,
					ARRAY_SIZE(des3_ede_skciphers));
	अगर (err)
		crypto_unरेजिस्टर_alg(&des3_ede_cipher);

	वापस err;
पूर्ण

अटल व्योम __निकास des3_ede_x86_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&des3_ede_cipher);
	crypto_unरेजिस्टर_skciphers(des3_ede_skciphers,
				    ARRAY_SIZE(des3_ede_skciphers));
पूर्ण

module_init(des3_ede_x86_init);
module_निकास(des3_ede_x86_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Triple DES EDE Cipher Algorithm, asm optimized");
MODULE_ALIAS_CRYPTO("des3_ede");
MODULE_ALIAS_CRYPTO("des3_ede-asm");
MODULE_AUTHOR("Jussi Kivilinna <jussi.kivilinna@iki.fi>");
