<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम assembler optimized version of Blowfish
 *
 * Copyright (c) 2011 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 *
 * CBC & ECB parts based on code (crypto/cbc.c,ecb.c) by:
 *   Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/blowfish.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

/* regular block cipher functions */
यंत्रlinkage व्योम __blowfish_enc_blk(काष्ठा bf_ctx *ctx, u8 *dst, स्थिर u8 *src,
				   bool xor);
यंत्रlinkage व्योम blowfish_dec_blk(काष्ठा bf_ctx *ctx, u8 *dst, स्थिर u8 *src);

/* 4-way parallel cipher functions */
यंत्रlinkage व्योम __blowfish_enc_blk_4way(काष्ठा bf_ctx *ctx, u8 *dst,
					स्थिर u8 *src, bool xor);
यंत्रlinkage व्योम blowfish_dec_blk_4way(काष्ठा bf_ctx *ctx, u8 *dst,
				      स्थिर u8 *src);

अटल अंतरभूत व्योम blowfish_enc_blk(काष्ठा bf_ctx *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__blowfish_enc_blk(ctx, dst, src, false);
पूर्ण

अटल अंतरभूत व्योम blowfish_enc_blk_xor(काष्ठा bf_ctx *ctx, u8 *dst,
					स्थिर u8 *src)
अणु
	__blowfish_enc_blk(ctx, dst, src, true);
पूर्ण

अटल अंतरभूत व्योम blowfish_enc_blk_4way(काष्ठा bf_ctx *ctx, u8 *dst,
					 स्थिर u8 *src)
अणु
	__blowfish_enc_blk_4way(ctx, dst, src, false);
पूर्ण

अटल अंतरभूत व्योम blowfish_enc_blk_xor_4way(काष्ठा bf_ctx *ctx, u8 *dst,
				      स्थिर u8 *src)
अणु
	__blowfish_enc_blk_4way(ctx, dst, src, true);
पूर्ण

अटल व्योम blowfish_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	blowfish_enc_blk(crypto_tfm_ctx(tfm), dst, src);
पूर्ण

अटल व्योम blowfish_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	blowfish_dec_blk(crypto_tfm_ctx(tfm), dst, src);
पूर्ण

अटल पूर्णांक blowfish_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
				    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस blowfish_setkey(&tfm->base, key, keylen);
पूर्ण

अटल पूर्णांक ecb_crypt(काष्ठा skcipher_request *req,
		     व्योम (*fn)(काष्ठा bf_ctx *, u8 *, स्थिर u8 *),
		     व्योम (*fn_4way)(काष्ठा bf_ctx *, u8 *, स्थिर u8 *))
अणु
	अचिन्हित पूर्णांक bsize = BF_BLOCK_SIZE;
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा bf_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		u8 *wsrc = walk.src.virt.addr;
		u8 *wdst = walk.dst.virt.addr;

		/* Process four block batch */
		अगर (nbytes >= bsize * 4) अणु
			करो अणु
				fn_4way(ctx, wdst, wsrc);

				wsrc += bsize * 4;
				wdst += bsize * 4;
				nbytes -= bsize * 4;
			पूर्ण जबतक (nbytes >= bsize * 4);

			अगर (nbytes < bsize)
				जाओ करोne;
		पूर्ण

		/* Handle leftovers */
		करो अणु
			fn(ctx, wdst, wsrc);

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
	वापस ecb_crypt(req, blowfish_enc_blk, blowfish_enc_blk_4way);
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_crypt(req, blowfish_dec_blk, blowfish_dec_blk_4way);
पूर्ण

अटल अचिन्हित पूर्णांक __cbc_encrypt(काष्ठा bf_ctx *ctx,
				  काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित पूर्णांक bsize = BF_BLOCK_SIZE;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u64 *src = (u64 *)walk->src.virt.addr;
	u64 *dst = (u64 *)walk->dst.virt.addr;
	u64 *iv = (u64 *)walk->iv;

	करो अणु
		*dst = *src ^ *iv;
		blowfish_enc_blk(ctx, (u8 *)dst, (u8 *)dst);
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
	काष्ठा bf_ctx *ctx = crypto_skcipher_ctx(tfm);
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

अटल अचिन्हित पूर्णांक __cbc_decrypt(काष्ठा bf_ctx *ctx,
				  काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित पूर्णांक bsize = BF_BLOCK_SIZE;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u64 *src = (u64 *)walk->src.virt.addr;
	u64 *dst = (u64 *)walk->dst.virt.addr;
	u64 ivs[4 - 1];
	u64 last_iv;

	/* Start of the last block. */
	src += nbytes / bsize - 1;
	dst += nbytes / bsize - 1;

	last_iv = *src;

	/* Process four block batch */
	अगर (nbytes >= bsize * 4) अणु
		करो अणु
			nbytes -= bsize * 4 - bsize;
			src -= 4 - 1;
			dst -= 4 - 1;

			ivs[0] = src[0];
			ivs[1] = src[1];
			ivs[2] = src[2];

			blowfish_dec_blk_4way(ctx, (u8 *)dst, (u8 *)src);

			dst[1] ^= ivs[0];
			dst[2] ^= ivs[1];
			dst[3] ^= ivs[2];

			nbytes -= bsize;
			अगर (nbytes < bsize)
				जाओ करोne;

			*dst ^= *(src - 1);
			src -= 1;
			dst -= 1;
		पूर्ण जबतक (nbytes >= bsize * 4);
	पूर्ण

	/* Handle leftovers */
	क्रम (;;) अणु
		blowfish_dec_blk(ctx, (u8 *)dst, (u8 *)src);

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
	काष्ठा bf_ctx *ctx = crypto_skcipher_ctx(tfm);
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

अटल काष्ठा crypto_alg bf_cipher_alg = अणु
	.cra_name		= "blowfish",
	.cra_driver_name	= "blowfish-asm",
	.cra_priority		= 200,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= BF_BLOCK_SIZE,
	.cra_ctxsize		= माप(काष्ठा bf_ctx),
	.cra_alignmask		= 0,
	.cra_module		= THIS_MODULE,
	.cra_u = अणु
		.cipher = अणु
			.cia_min_keysize	= BF_MIN_KEY_SIZE,
			.cia_max_keysize	= BF_MAX_KEY_SIZE,
			.cia_setkey		= blowfish_setkey,
			.cia_encrypt		= blowfish_encrypt,
			.cia_decrypt		= blowfish_decrypt,
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg bf_skcipher_algs[] = अणु
	अणु
		.base.cra_name		= "ecb(blowfish)",
		.base.cra_driver_name	= "ecb-blowfish-asm",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= BF_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा bf_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= BF_MIN_KEY_SIZE,
		.max_keysize		= BF_MAX_KEY_SIZE,
		.setkey			= blowfish_setkey_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(blowfish)",
		.base.cra_driver_name	= "cbc-blowfish-asm",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= BF_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा bf_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= BF_MIN_KEY_SIZE,
		.max_keysize		= BF_MAX_KEY_SIZE,
		.ivsize			= BF_BLOCK_SIZE,
		.setkey			= blowfish_setkey_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण,
पूर्ण;

अटल bool is_blacklisted_cpu(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस false;

	अगर (boot_cpu_data.x86 == 0x0f) अणु
		/*
		 * On Pentium 4, blowfish-x86_64 is slower than generic C
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

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक err;

	अगर (!क्रमce && is_blacklisted_cpu()) अणु
		prपूर्णांकk(KERN_INFO
			"blowfish-x86_64: performance on this CPU "
			"would be suboptimal: disabling "
			"blowfish-x86_64.\n");
		वापस -ENODEV;
	पूर्ण

	err = crypto_रेजिस्टर_alg(&bf_cipher_alg);
	अगर (err)
		वापस err;

	err = crypto_रेजिस्टर_skciphers(bf_skcipher_algs,
					ARRAY_SIZE(bf_skcipher_algs));
	अगर (err)
		crypto_unरेजिस्टर_alg(&bf_cipher_alg);

	वापस err;
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&bf_cipher_alg);
	crypto_unरेजिस्टर_skciphers(bf_skcipher_algs,
				    ARRAY_SIZE(bf_skcipher_algs));
पूर्ण

module_init(init);
module_निकास(fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blowfish Cipher Algorithm, asm optimized");
MODULE_ALIAS_CRYPTO("blowfish");
MODULE_ALIAS_CRYPTO("blowfish-asm");
