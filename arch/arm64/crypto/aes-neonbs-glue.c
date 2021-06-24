<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Bit sliced AES using NEON inकाष्ठाions
 *
 * Copyright (C) 2016 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/xts.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

MODULE_ALIAS_CRYPTO("ecb(aes)");
MODULE_ALIAS_CRYPTO("cbc(aes)");
MODULE_ALIAS_CRYPTO("ctr(aes)");
MODULE_ALIAS_CRYPTO("xts(aes)");

यंत्रlinkage व्योम aesbs_convert_key(u8 out[], u32 स्थिर rk[], पूर्णांक rounds);

यंत्रlinkage व्योम aesbs_ecb_encrypt(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks);
यंत्रlinkage व्योम aesbs_ecb_decrypt(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks);

यंत्रlinkage व्योम aesbs_cbc_decrypt(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);

यंत्रlinkage व्योम aesbs_ctr_encrypt(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks, u8 iv[], u8 final[]);

यंत्रlinkage व्योम aesbs_xts_encrypt(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);
यंत्रlinkage व्योम aesbs_xts_decrypt(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);

/* borrowed from aes-neon-blk.ko */
यंत्रlinkage व्योम neon_aes_ecb_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				     पूर्णांक rounds, पूर्णांक blocks);
यंत्रlinkage व्योम neon_aes_cbc_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				     पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);
यंत्रlinkage व्योम neon_aes_xts_encrypt(u8 out[], u8 स्थिर in[],
				     u32 स्थिर rk1[], पूर्णांक rounds, पूर्णांक bytes,
				     u32 स्थिर rk2[], u8 iv[], पूर्णांक first);
यंत्रlinkage व्योम neon_aes_xts_decrypt(u8 out[], u8 स्थिर in[],
				     u32 स्थिर rk1[], पूर्णांक rounds, पूर्णांक bytes,
				     u32 स्थिर rk2[], u8 iv[], पूर्णांक first);

काष्ठा aesbs_ctx अणु
	u8	rk[13 * (8 * AES_BLOCK_SIZE) + 32];
	पूर्णांक	rounds;
पूर्ण __aligned(AES_BLOCK_SIZE);

काष्ठा aesbs_cbc_ctx अणु
	काष्ठा aesbs_ctx	key;
	u32			enc[AES_MAX_KEYLENGTH_U32];
पूर्ण;

काष्ठा aesbs_ctr_ctx अणु
	काष्ठा aesbs_ctx	key;		/* must be first member */
	काष्ठा crypto_aes_ctx	fallback;
पूर्ण;

काष्ठा aesbs_xts_ctx अणु
	काष्ठा aesbs_ctx	key;
	u32			twkey[AES_MAX_KEYLENGTH_U32];
	काष्ठा crypto_aes_ctx	cts;
पूर्ण;

अटल पूर्णांक aesbs_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा aesbs_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_aes_ctx rk;
	पूर्णांक err;

	err = aes_expandkey(&rk, in_key, key_len);
	अगर (err)
		वापस err;

	ctx->rounds = 6 + key_len / 4;

	kernel_neon_begin();
	aesbs_convert_key(ctx->rk, rk.key_enc, ctx->rounds);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक __ecb_crypt(काष्ठा skcipher_request *req,
		       व्योम (*fn)(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks))
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aesbs_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes >= AES_BLOCK_SIZE) अणु
		अचिन्हित पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;

		अगर (walk.nbytes < walk.total)
			blocks = round_करोwn(blocks,
					    walk.stride / AES_BLOCK_SIZE);

		kernel_neon_begin();
		fn(walk.dst.virt.addr, walk.src.virt.addr, ctx->rk,
		   ctx->rounds, blocks);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk,
					 walk.nbytes - blocks * AES_BLOCK_SIZE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस __ecb_crypt(req, aesbs_ecb_encrypt);
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस __ecb_crypt(req, aesbs_ecb_decrypt);
पूर्ण

अटल पूर्णांक aesbs_cbc_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा aesbs_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_aes_ctx rk;
	पूर्णांक err;

	err = aes_expandkey(&rk, in_key, key_len);
	अगर (err)
		वापस err;

	ctx->key.rounds = 6 + key_len / 4;

	स_नकल(ctx->enc, rk.key_enc, माप(ctx->enc));

	kernel_neon_begin();
	aesbs_convert_key(ctx->key.rk, rk.key_enc, ctx->key.rounds);
	kernel_neon_end();
	memzero_explicit(&rk, माप(rk));

	वापस 0;
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aesbs_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes >= AES_BLOCK_SIZE) अणु
		अचिन्हित पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;

		/* fall back to the non-bitsliced NEON implementation */
		kernel_neon_begin();
		neon_aes_cbc_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				     ctx->enc, ctx->key.rounds, blocks,
				     walk.iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aesbs_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes >= AES_BLOCK_SIZE) अणु
		अचिन्हित पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;

		अगर (walk.nbytes < walk.total)
			blocks = round_करोwn(blocks,
					    walk.stride / AES_BLOCK_SIZE);

		kernel_neon_begin();
		aesbs_cbc_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
				  ctx->key.rk, ctx->key.rounds, blocks,
				  walk.iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk,
					 walk.nbytes - blocks * AES_BLOCK_SIZE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aesbs_ctr_setkey_sync(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
				 अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा aesbs_ctr_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = aes_expandkey(&ctx->fallback, in_key, key_len);
	अगर (err)
		वापस err;

	ctx->key.rounds = 6 + key_len / 4;

	kernel_neon_begin();
	aesbs_convert_key(ctx->key.rk, ctx->fallback.key_enc, ctx->key.rounds);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aesbs_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	u8 buf[AES_BLOCK_SIZE];
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes > 0) अणु
		अचिन्हित पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;
		u8 *final = (walk.total % AES_BLOCK_SIZE) ? buf : शून्य;

		अगर (walk.nbytes < walk.total) अणु
			blocks = round_करोwn(blocks,
					    walk.stride / AES_BLOCK_SIZE);
			final = शून्य;
		पूर्ण

		kernel_neon_begin();
		aesbs_ctr_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				  ctx->rk, ctx->rounds, blocks, walk.iv, final);
		kernel_neon_end();

		अगर (final) अणु
			u8 *dst = walk.dst.virt.addr + blocks * AES_BLOCK_SIZE;
			u8 *src = walk.src.virt.addr + blocks * AES_BLOCK_SIZE;

			crypto_xor_cpy(dst, src, final,
				       walk.total % AES_BLOCK_SIZE);

			err = skcipher_walk_करोne(&walk, 0);
			अवरोध;
		पूर्ण
		err = skcipher_walk_करोne(&walk,
					 walk.nbytes - blocks * AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक aesbs_xts_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा aesbs_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_aes_ctx rk;
	पूर्णांक err;

	err = xts_verअगरy_key(tfm, in_key, key_len);
	अगर (err)
		वापस err;

	key_len /= 2;
	err = aes_expandkey(&ctx->cts, in_key, key_len);
	अगर (err)
		वापस err;

	err = aes_expandkey(&rk, in_key + key_len, key_len);
	अगर (err)
		वापस err;

	स_नकल(ctx->twkey, rk.key_enc, माप(ctx->twkey));

	वापस aesbs_setkey(tfm, in_key, key_len);
पूर्ण

अटल व्योम ctr_encrypt_one(काष्ठा crypto_skcipher *tfm, स्थिर u8 *src, u8 *dst)
अणु
	काष्ठा aesbs_ctr_ctx *ctx = crypto_skcipher_ctx(tfm);
	अचिन्हित दीर्घ flags;

	/*
	 * Temporarily disable पूर्णांकerrupts to aव्योम races where
	 * cachelines are evicted when the CPU is पूर्णांकerrupted
	 * to करो something अन्यथा.
	 */
	local_irq_save(flags);
	aes_encrypt(&ctx->fallback, dst, src);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक ctr_encrypt_sync(काष्ठा skcipher_request *req)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_ctr_encrypt_walk(req, ctr_encrypt_one);

	वापस ctr_encrypt(req);
पूर्ण

अटल पूर्णांक __xts_crypt(काष्ठा skcipher_request *req, bool encrypt,
		       व्योम (*fn)(u8 out[], u8 स्थिर in[], u8 स्थिर rk[],
				  पूर्णांक rounds, पूर्णांक blocks, u8 iv[]))
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aesbs_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक tail = req->cryptlen % (8 * AES_BLOCK_SIZE);
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा scatterlist *src, *dst;
	काष्ठा skcipher_walk walk;
	पूर्णांक nbytes, err;
	पूर्णांक first = 1;
	u8 *out, *in;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	/* ensure that the cts tail is covered by a single step */
	अगर (unlikely(tail > 0 && tail < AES_BLOCK_SIZE)) अणु
		पूर्णांक xts_blocks = DIV_ROUND_UP(req->cryptlen,
					      AES_BLOCK_SIZE) - 2;

		skcipher_request_set_tfm(&subreq, tfm);
		skcipher_request_set_callback(&subreq,
					      skcipher_request_flags(req),
					      शून्य, शून्य);
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   xts_blocks * AES_BLOCK_SIZE,
					   req->iv);
		req = &subreq;
	पूर्ण अन्यथा अणु
		tail = 0;
	पूर्ण

	err = skcipher_walk_virt(&walk, req, false);
	अगर (err)
		वापस err;

	जबतक (walk.nbytes >= AES_BLOCK_SIZE) अणु
		अचिन्हित पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;

		अगर (walk.nbytes < walk.total || walk.nbytes % AES_BLOCK_SIZE)
			blocks = round_करोwn(blocks,
					    walk.stride / AES_BLOCK_SIZE);

		out = walk.dst.virt.addr;
		in = walk.src.virt.addr;
		nbytes = walk.nbytes;

		kernel_neon_begin();
		अगर (likely(blocks > 6)) अणु /* plain NEON is faster otherwise */
			अगर (first)
				neon_aes_ecb_encrypt(walk.iv, walk.iv,
						     ctx->twkey,
						     ctx->key.rounds, 1);
			first = 0;

			fn(out, in, ctx->key.rk, ctx->key.rounds, blocks,
			   walk.iv);

			out += blocks * AES_BLOCK_SIZE;
			in += blocks * AES_BLOCK_SIZE;
			nbytes -= blocks * AES_BLOCK_SIZE;
		पूर्ण

		अगर (walk.nbytes == walk.total && nbytes > 0)
			जाओ xts_tail;

		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	अगर (err || likely(!tail))
		वापस err;

	/* handle ciphertext stealing */
	dst = src = scatterwalk_ffwd(sg_src, req->src, req->cryptlen);
	अगर (req->dst != req->src)
		dst = scatterwalk_ffwd(sg_dst, req->dst, req->cryptlen);

	skcipher_request_set_crypt(req, src, dst, AES_BLOCK_SIZE + tail,
				   req->iv);

	err = skcipher_walk_virt(&walk, req, false);
	अगर (err)
		वापस err;

	out = walk.dst.virt.addr;
	in = walk.src.virt.addr;
	nbytes = walk.nbytes;

	kernel_neon_begin();
xts_tail:
	अगर (encrypt)
		neon_aes_xts_encrypt(out, in, ctx->cts.key_enc, ctx->key.rounds,
				     nbytes, ctx->twkey, walk.iv, first ?: 2);
	अन्यथा
		neon_aes_xts_decrypt(out, in, ctx->cts.key_dec, ctx->key.rounds,
				     nbytes, ctx->twkey, walk.iv, first ?: 2);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक xts_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस __xts_crypt(req, true, aesbs_xts_encrypt);
पूर्ण

अटल पूर्णांक xts_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस __xts_crypt(req, false, aesbs_xts_decrypt);
पूर्ण

अटल काष्ठा skcipher_alg aes_algs[] = अणु अणु
	.base.cra_name		= "__ecb(aes)",
	.base.cra_driver_name	= "__ecb-aes-neonbs",
	.base.cra_priority	= 250,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aesbs_ctx),
	.base.cra_module	= THIS_MODULE,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.walksize		= 8 * AES_BLOCK_SIZE,
	.setkey			= aesbs_setkey,
	.encrypt		= ecb_encrypt,
	.decrypt		= ecb_decrypt,
पूर्ण, अणु
	.base.cra_name		= "__cbc(aes)",
	.base.cra_driver_name	= "__cbc-aes-neonbs",
	.base.cra_priority	= 250,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aesbs_cbc_ctx),
	.base.cra_module	= THIS_MODULE,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.walksize		= 8 * AES_BLOCK_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= aesbs_cbc_setkey,
	.encrypt		= cbc_encrypt,
	.decrypt		= cbc_decrypt,
पूर्ण, अणु
	.base.cra_name		= "__ctr(aes)",
	.base.cra_driver_name	= "__ctr-aes-neonbs",
	.base.cra_priority	= 250,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा aesbs_ctx),
	.base.cra_module	= THIS_MODULE,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.chunksize		= AES_BLOCK_SIZE,
	.walksize		= 8 * AES_BLOCK_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= aesbs_setkey,
	.encrypt		= ctr_encrypt,
	.decrypt		= ctr_encrypt,
पूर्ण, अणु
	.base.cra_name		= "ctr(aes)",
	.base.cra_driver_name	= "ctr-aes-neonbs",
	.base.cra_priority	= 250 - 1,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा aesbs_ctr_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.chunksize		= AES_BLOCK_SIZE,
	.walksize		= 8 * AES_BLOCK_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= aesbs_ctr_setkey_sync,
	.encrypt		= ctr_encrypt_sync,
	.decrypt		= ctr_encrypt_sync,
पूर्ण, अणु
	.base.cra_name		= "__xts(aes)",
	.base.cra_driver_name	= "__xts-aes-neonbs",
	.base.cra_priority	= 250,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aesbs_xts_ctx),
	.base.cra_module	= THIS_MODULE,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.walksize		= 8 * AES_BLOCK_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= aesbs_xts_setkey,
	.encrypt		= xts_encrypt,
	.decrypt		= xts_decrypt,
पूर्ण पूर्ण;

अटल काष्ठा simd_skcipher_alg *aes_simd_algs[ARRAY_SIZE(aes_algs)];

अटल व्योम aes_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aes_simd_algs); i++)
		अगर (aes_simd_algs[i])
			simd_skcipher_मुक्त(aes_simd_algs[i]);

	crypto_unरेजिस्टर_skciphers(aes_algs, ARRAY_SIZE(aes_algs));
पूर्ण

अटल पूर्णांक __init aes_init(व्योम)
अणु
	काष्ठा simd_skcipher_alg *simd;
	स्थिर अक्षर *basename;
	स्थिर अक्षर *algname;
	स्थिर अक्षर *drvname;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!cpu_have_named_feature(ASIMD))
		वापस -ENODEV;

	err = crypto_रेजिस्टर_skciphers(aes_algs, ARRAY_SIZE(aes_algs));
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(aes_algs); i++) अणु
		अगर (!(aes_algs[i].base.cra_flags & CRYPTO_ALG_INTERNAL))
			जारी;

		algname = aes_algs[i].base.cra_name + 2;
		drvname = aes_algs[i].base.cra_driver_name + 2;
		basename = aes_algs[i].base.cra_driver_name;
		simd = simd_skcipher_create_compat(algname, drvname, basename);
		err = PTR_ERR(simd);
		अगर (IS_ERR(simd))
			जाओ unरेजिस्टर_simds;

		aes_simd_algs[i] = simd;
	पूर्ण
	वापस 0;

unरेजिस्टर_simds:
	aes_निकास();
	वापस err;
पूर्ण

module_init(aes_init);
module_निकास(aes_निकास);
