<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm64/crypto/aes-glue.c - wrapper code क्रम ARMv8 AES
 *
 * Copyright (C) 2013 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/simd.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <crypto/xts.h>

#समावेश "aes-ce-setkey.h"

#अगर_घोषित USE_V8_CRYPTO_EXTENSIONS
#घोषणा MODE			"ce"
#घोषणा PRIO			300
#घोषणा STRIDE			5
#घोषणा aes_expandkey		ce_aes_expandkey
#घोषणा aes_ecb_encrypt		ce_aes_ecb_encrypt
#घोषणा aes_ecb_decrypt		ce_aes_ecb_decrypt
#घोषणा aes_cbc_encrypt		ce_aes_cbc_encrypt
#घोषणा aes_cbc_decrypt		ce_aes_cbc_decrypt
#घोषणा aes_cbc_cts_encrypt	ce_aes_cbc_cts_encrypt
#घोषणा aes_cbc_cts_decrypt	ce_aes_cbc_cts_decrypt
#घोषणा aes_essiv_cbc_encrypt	ce_aes_essiv_cbc_encrypt
#घोषणा aes_essiv_cbc_decrypt	ce_aes_essiv_cbc_decrypt
#घोषणा aes_ctr_encrypt		ce_aes_ctr_encrypt
#घोषणा aes_xts_encrypt		ce_aes_xts_encrypt
#घोषणा aes_xts_decrypt		ce_aes_xts_decrypt
#घोषणा aes_mac_update		ce_aes_mac_update
MODULE_DESCRIPTION("AES-ECB/CBC/CTR/XTS using ARMv8 Crypto Extensions");
#अन्यथा
#घोषणा MODE			"neon"
#घोषणा PRIO			200
#घोषणा STRIDE			4
#घोषणा aes_ecb_encrypt		neon_aes_ecb_encrypt
#घोषणा aes_ecb_decrypt		neon_aes_ecb_decrypt
#घोषणा aes_cbc_encrypt		neon_aes_cbc_encrypt
#घोषणा aes_cbc_decrypt		neon_aes_cbc_decrypt
#घोषणा aes_cbc_cts_encrypt	neon_aes_cbc_cts_encrypt
#घोषणा aes_cbc_cts_decrypt	neon_aes_cbc_cts_decrypt
#घोषणा aes_essiv_cbc_encrypt	neon_aes_essiv_cbc_encrypt
#घोषणा aes_essiv_cbc_decrypt	neon_aes_essiv_cbc_decrypt
#घोषणा aes_ctr_encrypt		neon_aes_ctr_encrypt
#घोषणा aes_xts_encrypt		neon_aes_xts_encrypt
#घोषणा aes_xts_decrypt		neon_aes_xts_decrypt
#घोषणा aes_mac_update		neon_aes_mac_update
MODULE_DESCRIPTION("AES-ECB/CBC/CTR/XTS using ARMv8 NEON");
#पूर्ण_अगर
#अगर defined(USE_V8_CRYPTO_EXTENSIONS) || !IS_ENABLED(CONFIG_CRYPTO_AES_ARM64_BS)
MODULE_ALIAS_CRYPTO("ecb(aes)");
MODULE_ALIAS_CRYPTO("cbc(aes)");
MODULE_ALIAS_CRYPTO("ctr(aes)");
MODULE_ALIAS_CRYPTO("xts(aes)");
#पूर्ण_अगर
MODULE_ALIAS_CRYPTO("cts(cbc(aes))");
MODULE_ALIAS_CRYPTO("essiv(cbc(aes),sha256)");
MODULE_ALIAS_CRYPTO("cmac(aes)");
MODULE_ALIAS_CRYPTO("xcbc(aes)");
MODULE_ALIAS_CRYPTO("cbcmac(aes)");

MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

/* defined in aes-modes.S */
यंत्रlinkage व्योम aes_ecb_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक blocks);
यंत्रlinkage व्योम aes_ecb_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक blocks);

यंत्रlinkage व्योम aes_cbc_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);
यंत्रlinkage व्योम aes_cbc_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);

यंत्रlinkage व्योम aes_cbc_cts_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक bytes, u8 स्थिर iv[]);
यंत्रlinkage व्योम aes_cbc_cts_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक bytes, u8 स्थिर iv[]);

यंत्रlinkage व्योम aes_ctr_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				पूर्णांक rounds, पूर्णांक bytes, u8 ctr[], u8 finalbuf[]);

यंत्रlinkage व्योम aes_xts_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk1[],
				पूर्णांक rounds, पूर्णांक bytes, u32 स्थिर rk2[], u8 iv[],
				पूर्णांक first);
यंत्रlinkage व्योम aes_xts_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk1[],
				पूर्णांक rounds, पूर्णांक bytes, u32 स्थिर rk2[], u8 iv[],
				पूर्णांक first);

यंत्रlinkage व्योम aes_essiv_cbc_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk1[],
				      पूर्णांक rounds, पूर्णांक blocks, u8 iv[],
				      u32 स्थिर rk2[]);
यंत्रlinkage व्योम aes_essiv_cbc_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk1[],
				      पूर्णांक rounds, पूर्णांक blocks, u8 iv[],
				      u32 स्थिर rk2[]);

यंत्रlinkage पूर्णांक aes_mac_update(u8 स्थिर in[], u32 स्थिर rk[], पूर्णांक rounds,
			      पूर्णांक blocks, u8 dg[], पूर्णांक enc_beक्रमe,
			      पूर्णांक enc_after);

काष्ठा crypto_aes_xts_ctx अणु
	काष्ठा crypto_aes_ctx key1;
	काष्ठा crypto_aes_ctx __aligned(8) key2;
पूर्ण;

काष्ठा crypto_aes_essiv_cbc_ctx अणु
	काष्ठा crypto_aes_ctx key1;
	काष्ठा crypto_aes_ctx __aligned(8) key2;
	काष्ठा crypto_shash *hash;
पूर्ण;

काष्ठा mac_tfm_ctx अणु
	काष्ठा crypto_aes_ctx key;
	u8 __aligned(8) स्थिरs[];
पूर्ण;

काष्ठा mac_desc_ctx अणु
	अचिन्हित पूर्णांक len;
	u8 dg[AES_BLOCK_SIZE];
पूर्ण;

अटल पूर्णांक skcipher_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस aes_expandkey(ctx, in_key, key_len);
पूर्ण

अटल पूर्णांक __maybe_unused xts_set_key(काष्ठा crypto_skcipher *tfm,
				      स्थिर u8 *in_key, अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	ret = xts_verअगरy_key(tfm, in_key, key_len);
	अगर (ret)
		वापस ret;

	ret = aes_expandkey(&ctx->key1, in_key, key_len / 2);
	अगर (!ret)
		ret = aes_expandkey(&ctx->key2, &in_key[key_len / 2],
				    key_len / 2);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused essiv_cbc_set_key(काष्ठा crypto_skcipher *tfm,
					    स्थिर u8 *in_key,
					    अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_essiv_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	u8 digest[SHA256_DIGEST_SIZE];
	पूर्णांक ret;

	ret = aes_expandkey(&ctx->key1, in_key, key_len);
	अगर (ret)
		वापस ret;

	crypto_shash_tfm_digest(ctx->hash, in_key, key_len, digest);

	वापस aes_expandkey(&ctx->key2, digest, माप(digest));
पूर्ण

अटल पूर्णांक __maybe_unused ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key_length / 4;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक blocks;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		aes_ecb_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				ctx->key_enc, rounds, blocks);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key_length / 4;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक blocks;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		aes_ecb_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
				ctx->key_dec, rounds, blocks);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cbc_encrypt_walk(काष्ठा skcipher_request *req,
			    काष्ठा skcipher_walk *walk)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err = 0, rounds = 6 + ctx->key_length / 4;
	अचिन्हित पूर्णांक blocks;

	जबतक ((blocks = (walk->nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		aes_cbc_encrypt(walk->dst.virt.addr, walk->src.virt.addr,
				ctx->key_enc, rounds, blocks, walk->iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(walk, walk->nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);
	अगर (err)
		वापस err;
	वापस cbc_encrypt_walk(req, &walk);
पूर्ण

अटल पूर्णांक cbc_decrypt_walk(काष्ठा skcipher_request *req,
			    काष्ठा skcipher_walk *walk)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err = 0, rounds = 6 + ctx->key_length / 4;
	अचिन्हित पूर्णांक blocks;

	जबतक ((blocks = (walk->nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		aes_cbc_decrypt(walk->dst.virt.addr, walk->src.virt.addr,
				ctx->key_dec, rounds, blocks, walk->iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(walk, walk->nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);
	अगर (err)
		वापस err;
	वापस cbc_decrypt_walk(req, &walk);
पूर्ण

अटल पूर्णांक cts_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key_length / 4;
	पूर्णांक cbc_blocks = DIV_ROUND_UP(req->cryptlen, AES_BLOCK_SIZE) - 2;
	काष्ठा scatterlist *src = req->src, *dst = req->dst;
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा skcipher_walk walk;

	skcipher_request_set_tfm(&subreq, tfm);
	skcipher_request_set_callback(&subreq, skcipher_request_flags(req),
				      शून्य, शून्य);

	अगर (req->cryptlen <= AES_BLOCK_SIZE) अणु
		अगर (req->cryptlen < AES_BLOCK_SIZE)
			वापस -EINVAL;
		cbc_blocks = 1;
	पूर्ण

	अगर (cbc_blocks > 0) अणु
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   cbc_blocks * AES_BLOCK_SIZE,
					   req->iv);

		err = skcipher_walk_virt(&walk, &subreq, false) ?:
		      cbc_encrypt_walk(&subreq, &walk);
		अगर (err)
			वापस err;

		अगर (req->cryptlen == AES_BLOCK_SIZE)
			वापस 0;

		dst = src = scatterwalk_ffwd(sg_src, req->src, subreq.cryptlen);
		अगर (req->dst != req->src)
			dst = scatterwalk_ffwd(sg_dst, req->dst,
					       subreq.cryptlen);
	पूर्ण

	/* handle ciphertext stealing */
	skcipher_request_set_crypt(&subreq, src, dst,
				   req->cryptlen - cbc_blocks * AES_BLOCK_SIZE,
				   req->iv);

	err = skcipher_walk_virt(&walk, &subreq, false);
	अगर (err)
		वापस err;

	kernel_neon_begin();
	aes_cbc_cts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
			    ctx->key_enc, rounds, walk.nbytes, walk.iv);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक cts_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key_length / 4;
	पूर्णांक cbc_blocks = DIV_ROUND_UP(req->cryptlen, AES_BLOCK_SIZE) - 2;
	काष्ठा scatterlist *src = req->src, *dst = req->dst;
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा skcipher_walk walk;

	skcipher_request_set_tfm(&subreq, tfm);
	skcipher_request_set_callback(&subreq, skcipher_request_flags(req),
				      शून्य, शून्य);

	अगर (req->cryptlen <= AES_BLOCK_SIZE) अणु
		अगर (req->cryptlen < AES_BLOCK_SIZE)
			वापस -EINVAL;
		cbc_blocks = 1;
	पूर्ण

	अगर (cbc_blocks > 0) अणु
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   cbc_blocks * AES_BLOCK_SIZE,
					   req->iv);

		err = skcipher_walk_virt(&walk, &subreq, false) ?:
		      cbc_decrypt_walk(&subreq, &walk);
		अगर (err)
			वापस err;

		अगर (req->cryptlen == AES_BLOCK_SIZE)
			वापस 0;

		dst = src = scatterwalk_ffwd(sg_src, req->src, subreq.cryptlen);
		अगर (req->dst != req->src)
			dst = scatterwalk_ffwd(sg_dst, req->dst,
					       subreq.cryptlen);
	पूर्ण

	/* handle ciphertext stealing */
	skcipher_request_set_crypt(&subreq, src, dst,
				   req->cryptlen - cbc_blocks * AES_BLOCK_SIZE,
				   req->iv);

	err = skcipher_walk_virt(&walk, &subreq, false);
	अगर (err)
		वापस err;

	kernel_neon_begin();
	aes_cbc_cts_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
			    ctx->key_dec, rounds, walk.nbytes, walk.iv);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक __maybe_unused essiv_cbc_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा crypto_aes_essiv_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->hash = crypto_alloc_shash("sha256", 0, 0);

	वापस PTR_ERR_OR_ZERO(ctx->hash);
पूर्ण

अटल व्योम __maybe_unused essiv_cbc_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा crypto_aes_essiv_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_shash(ctx->hash);
पूर्ण

अटल पूर्णांक __maybe_unused essiv_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_essiv_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key1.key_length / 4;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक blocks;

	err = skcipher_walk_virt(&walk, req, false);

	blocks = walk.nbytes / AES_BLOCK_SIZE;
	अगर (blocks) अणु
		kernel_neon_begin();
		aes_essiv_cbc_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				      ctx->key1.key_enc, rounds, blocks,
				      req->iv, ctx->key2.key_enc);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err ?: cbc_encrypt_walk(req, &walk);
पूर्ण

अटल पूर्णांक __maybe_unused essiv_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_essiv_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key1.key_length / 4;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक blocks;

	err = skcipher_walk_virt(&walk, req, false);

	blocks = walk.nbytes / AES_BLOCK_SIZE;
	अगर (blocks) अणु
		kernel_neon_begin();
		aes_essiv_cbc_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
				      ctx->key1.key_dec, rounds, blocks,
				      req->iv, ctx->key2.key_enc);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err ?: cbc_decrypt_walk(req, &walk);
पूर्ण

अटल पूर्णांक ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, rounds = 6 + ctx->key_length / 4;
	काष्ठा skcipher_walk walk;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes > 0) अणु
		स्थिर u8 *src = walk.src.virt.addr;
		अचिन्हित पूर्णांक nbytes = walk.nbytes;
		u8 *dst = walk.dst.virt.addr;
		u8 buf[AES_BLOCK_SIZE];
		अचिन्हित पूर्णांक tail;

		अगर (unlikely(nbytes < AES_BLOCK_SIZE))
			src = स_नकल(buf, src, nbytes);
		अन्यथा अगर (nbytes < walk.total)
			nbytes &= ~(AES_BLOCK_SIZE - 1);

		kernel_neon_begin();
		aes_ctr_encrypt(dst, src, ctx->key_enc, rounds, nbytes,
				walk.iv, buf);
		kernel_neon_end();

		tail = nbytes % (STRIDE * AES_BLOCK_SIZE);
		अगर (tail > 0 && tail < AES_BLOCK_SIZE)
			/*
			 * The final partial block could not be वापसed using
			 * an overlapping store, so it was passed via buf[]
			 * instead.
			 */
			स_नकल(dst + nbytes - tail, buf, tail);

		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ctr_encrypt_one(काष्ठा crypto_skcipher *tfm, स्थिर u8 *src, u8 *dst)
अणु
	स्थिर काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	अचिन्हित दीर्घ flags;

	/*
	 * Temporarily disable पूर्णांकerrupts to aव्योम races where
	 * cachelines are evicted when the CPU is पूर्णांकerrupted
	 * to करो something अन्यथा.
	 */
	local_irq_save(flags);
	aes_encrypt(ctx, dst, src);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __maybe_unused ctr_encrypt_sync(काष्ठा skcipher_request *req)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_ctr_encrypt_walk(req, ctr_encrypt_one);

	वापस ctr_encrypt(req);
पूर्ण

अटल पूर्णांक __maybe_unused xts_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, first, rounds = 6 + ctx->key1.key_length / 4;
	पूर्णांक tail = req->cryptlen % AES_BLOCK_SIZE;
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा scatterlist *src, *dst;
	काष्ठा skcipher_walk walk;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	err = skcipher_walk_virt(&walk, req, false);

	अगर (unlikely(tail > 0 && walk.nbytes < walk.total)) अणु
		पूर्णांक xts_blocks = DIV_ROUND_UP(req->cryptlen,
					      AES_BLOCK_SIZE) - 2;

		skcipher_walk_पात(&walk);

		skcipher_request_set_tfm(&subreq, tfm);
		skcipher_request_set_callback(&subreq,
					      skcipher_request_flags(req),
					      शून्य, शून्य);
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   xts_blocks * AES_BLOCK_SIZE,
					   req->iv);
		req = &subreq;
		err = skcipher_walk_virt(&walk, req, false);
	पूर्ण अन्यथा अणु
		tail = 0;
	पूर्ण

	क्रम (first = 1; walk.nbytes >= AES_BLOCK_SIZE; first = 0) अणु
		पूर्णांक nbytes = walk.nbytes;

		अगर (walk.nbytes < walk.total)
			nbytes &= ~(AES_BLOCK_SIZE - 1);

		kernel_neon_begin();
		aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				ctx->key1.key_enc, rounds, nbytes,
				ctx->key2.key_enc, walk.iv, first);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	अगर (err || likely(!tail))
		वापस err;

	dst = src = scatterwalk_ffwd(sg_src, req->src, req->cryptlen);
	अगर (req->dst != req->src)
		dst = scatterwalk_ffwd(sg_dst, req->dst, req->cryptlen);

	skcipher_request_set_crypt(req, src, dst, AES_BLOCK_SIZE + tail,
				   req->iv);

	err = skcipher_walk_virt(&walk, &subreq, false);
	अगर (err)
		वापस err;

	kernel_neon_begin();
	aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
			ctx->key1.key_enc, rounds, walk.nbytes,
			ctx->key2.key_enc, walk.iv, first);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक __maybe_unused xts_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, first, rounds = 6 + ctx->key1.key_length / 4;
	पूर्णांक tail = req->cryptlen % AES_BLOCK_SIZE;
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा scatterlist *src, *dst;
	काष्ठा skcipher_walk walk;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	err = skcipher_walk_virt(&walk, req, false);

	अगर (unlikely(tail > 0 && walk.nbytes < walk.total)) अणु
		पूर्णांक xts_blocks = DIV_ROUND_UP(req->cryptlen,
					      AES_BLOCK_SIZE) - 2;

		skcipher_walk_पात(&walk);

		skcipher_request_set_tfm(&subreq, tfm);
		skcipher_request_set_callback(&subreq,
					      skcipher_request_flags(req),
					      शून्य, शून्य);
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   xts_blocks * AES_BLOCK_SIZE,
					   req->iv);
		req = &subreq;
		err = skcipher_walk_virt(&walk, req, false);
	पूर्ण अन्यथा अणु
		tail = 0;
	पूर्ण

	क्रम (first = 1; walk.nbytes >= AES_BLOCK_SIZE; first = 0) अणु
		पूर्णांक nbytes = walk.nbytes;

		अगर (walk.nbytes < walk.total)
			nbytes &= ~(AES_BLOCK_SIZE - 1);

		kernel_neon_begin();
		aes_xts_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
				ctx->key1.key_dec, rounds, nbytes,
				ctx->key2.key_enc, walk.iv, first);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	अगर (err || likely(!tail))
		वापस err;

	dst = src = scatterwalk_ffwd(sg_src, req->src, req->cryptlen);
	अगर (req->dst != req->src)
		dst = scatterwalk_ffwd(sg_dst, req->dst, req->cryptlen);

	skcipher_request_set_crypt(req, src, dst, AES_BLOCK_SIZE + tail,
				   req->iv);

	err = skcipher_walk_virt(&walk, &subreq, false);
	अगर (err)
		वापस err;


	kernel_neon_begin();
	aes_xts_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
			ctx->key1.key_dec, rounds, walk.nbytes,
			ctx->key2.key_enc, walk.iv, first);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल काष्ठा skcipher_alg aes_algs[] = अणु अणु
#अगर defined(USE_V8_CRYPTO_EXTENSIONS) || !IS_ENABLED(CONFIG_CRYPTO_AES_ARM64_BS)
	.base = अणु
		.cra_name		= "__ecb(aes)",
		.cra_driver_name	= "__ecb-aes-" MODE,
		.cra_priority		= PRIO,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.setkey		= skcipher_aes_setkey,
	.encrypt	= ecb_encrypt,
	.decrypt	= ecb_decrypt,
पूर्ण, अणु
	.base = अणु
		.cra_name		= "__cbc(aes)",
		.cra_driver_name	= "__cbc-aes-" MODE,
		.cra_priority		= PRIO,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BLOCK_SIZE,
	.setkey		= skcipher_aes_setkey,
	.encrypt	= cbc_encrypt,
	.decrypt	= cbc_decrypt,
पूर्ण, अणु
	.base = अणु
		.cra_name		= "__ctr(aes)",
		.cra_driver_name	= "__ctr-aes-" MODE,
		.cra_priority		= PRIO,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BLOCK_SIZE,
	.chunksize	= AES_BLOCK_SIZE,
	.setkey		= skcipher_aes_setkey,
	.encrypt	= ctr_encrypt,
	.decrypt	= ctr_encrypt,
पूर्ण, अणु
	.base = अणु
		.cra_name		= "ctr(aes)",
		.cra_driver_name	= "ctr-aes-" MODE,
		.cra_priority		= PRIO - 1,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BLOCK_SIZE,
	.chunksize	= AES_BLOCK_SIZE,
	.setkey		= skcipher_aes_setkey,
	.encrypt	= ctr_encrypt_sync,
	.decrypt	= ctr_encrypt_sync,
पूर्ण, अणु
	.base = अणु
		.cra_name		= "__xts(aes)",
		.cra_driver_name	= "__xts-aes-" MODE,
		.cra_priority		= PRIO,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_xts_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= 2 * AES_MIN_KEY_SIZE,
	.max_keysize	= 2 * AES_MAX_KEY_SIZE,
	.ivsize		= AES_BLOCK_SIZE,
	.walksize	= 2 * AES_BLOCK_SIZE,
	.setkey		= xts_set_key,
	.encrypt	= xts_encrypt,
	.decrypt	= xts_decrypt,
पूर्ण, अणु
#पूर्ण_अगर
	.base = अणु
		.cra_name		= "__cts(cbc(aes))",
		.cra_driver_name	= "__cts-cbc-aes-" MODE,
		.cra_priority		= PRIO,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BLOCK_SIZE,
	.walksize	= 2 * AES_BLOCK_SIZE,
	.setkey		= skcipher_aes_setkey,
	.encrypt	= cts_cbc_encrypt,
	.decrypt	= cts_cbc_decrypt,
पूर्ण, अणु
	.base = अणु
		.cra_name		= "__essiv(cbc(aes),sha256)",
		.cra_driver_name	= "__essiv-cbc-aes-sha256-" MODE,
		.cra_priority		= PRIO + 1,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_essiv_cbc_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BLOCK_SIZE,
	.setkey		= essiv_cbc_set_key,
	.encrypt	= essiv_cbc_encrypt,
	.decrypt	= essiv_cbc_decrypt,
	.init		= essiv_cbc_init_tfm,
	.निकास		= essiv_cbc_निकास_tfm,
पूर्ण पूर्ण;

अटल पूर्णांक cbcmac_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *in_key,
			 अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा mac_tfm_ctx *ctx = crypto_shash_ctx(tfm);

	वापस aes_expandkey(&ctx->key, in_key, key_len);
पूर्ण

अटल व्योम cmac_gf128_mul_by_x(be128 *y, स्थिर be128 *x)
अणु
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	y->a = cpu_to_be64((a << 1) | (b >> 63));
	y->b = cpu_to_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0));
पूर्ण

अटल पूर्णांक cmac_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा mac_tfm_ctx *ctx = crypto_shash_ctx(tfm);
	be128 *स्थिरs = (be128 *)ctx->स्थिरs;
	पूर्णांक rounds = 6 + key_len / 4;
	पूर्णांक err;

	err = cbcmac_setkey(tfm, in_key, key_len);
	अगर (err)
		वापस err;

	/* encrypt the zero vector */
	kernel_neon_begin();
	aes_ecb_encrypt(ctx->स्थिरs, (u8[AES_BLOCK_SIZE])अणुपूर्ण, ctx->key.key_enc,
			rounds, 1);
	kernel_neon_end();

	cmac_gf128_mul_by_x(स्थिरs, स्थिरs);
	cmac_gf128_mul_by_x(स्थिरs + 1, स्थिरs);

	वापस 0;
पूर्ण

अटल पूर्णांक xcbc_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	अटल u8 स्थिर ks[3][AES_BLOCK_SIZE] = अणु
		अणु [0 ... AES_BLOCK_SIZE - 1] = 0x1 पूर्ण,
		अणु [0 ... AES_BLOCK_SIZE - 1] = 0x2 पूर्ण,
		अणु [0 ... AES_BLOCK_SIZE - 1] = 0x3 पूर्ण,
	पूर्ण;

	काष्ठा mac_tfm_ctx *ctx = crypto_shash_ctx(tfm);
	पूर्णांक rounds = 6 + key_len / 4;
	u8 key[AES_BLOCK_SIZE];
	पूर्णांक err;

	err = cbcmac_setkey(tfm, in_key, key_len);
	अगर (err)
		वापस err;

	kernel_neon_begin();
	aes_ecb_encrypt(key, ks[0], ctx->key.key_enc, rounds, 1);
	aes_ecb_encrypt(ctx->स्थिरs, ks[1], ctx->key.key_enc, rounds, 2);
	kernel_neon_end();

	वापस cbcmac_setkey(tfm, key, माप(key));
पूर्ण

अटल पूर्णांक mac_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा mac_desc_ctx *ctx = shash_desc_ctx(desc);

	स_रखो(ctx->dg, 0, AES_BLOCK_SIZE);
	ctx->len = 0;

	वापस 0;
पूर्ण

अटल व्योम mac_करो_update(काष्ठा crypto_aes_ctx *ctx, u8 स्थिर in[], पूर्णांक blocks,
			  u8 dg[], पूर्णांक enc_beक्रमe, पूर्णांक enc_after)
अणु
	पूर्णांक rounds = 6 + ctx->key_length / 4;

	अगर (crypto_simd_usable()) अणु
		पूर्णांक rem;

		करो अणु
			kernel_neon_begin();
			rem = aes_mac_update(in, ctx->key_enc, rounds, blocks,
					     dg, enc_beक्रमe, enc_after);
			kernel_neon_end();
			in += (blocks - rem) * AES_BLOCK_SIZE;
			blocks = rem;
			enc_beक्रमe = 0;
		पूर्ण जबतक (blocks);
	पूर्ण अन्यथा अणु
		अगर (enc_beक्रमe)
			aes_encrypt(ctx, dg, dg);

		जबतक (blocks--) अणु
			crypto_xor(dg, in, AES_BLOCK_SIZE);
			in += AES_BLOCK_SIZE;

			अगर (blocks || enc_after)
				aes_encrypt(ctx, dg, dg);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mac_update(काष्ठा shash_desc *desc, स्थिर u8 *p, अचिन्हित पूर्णांक len)
अणु
	काष्ठा mac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा mac_desc_ctx *ctx = shash_desc_ctx(desc);

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक l;

		अगर ((ctx->len % AES_BLOCK_SIZE) == 0 &&
		    (ctx->len + len) > AES_BLOCK_SIZE) अणु

			पूर्णांक blocks = len / AES_BLOCK_SIZE;

			len %= AES_BLOCK_SIZE;

			mac_करो_update(&tctx->key, p, blocks, ctx->dg,
				      (ctx->len != 0), (len != 0));

			p += blocks * AES_BLOCK_SIZE;

			अगर (!len) अणु
				ctx->len = AES_BLOCK_SIZE;
				अवरोध;
			पूर्ण
			ctx->len = 0;
		पूर्ण

		l = min(len, AES_BLOCK_SIZE - ctx->len);

		अगर (l <= AES_BLOCK_SIZE) अणु
			crypto_xor(ctx->dg + ctx->len, p, l);
			ctx->len += l;
			len -= l;
			p += l;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cbcmac_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा mac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा mac_desc_ctx *ctx = shash_desc_ctx(desc);

	mac_करो_update(&tctx->key, शून्य, 0, ctx->dg, (ctx->len != 0), 0);

	स_नकल(out, ctx->dg, AES_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक cmac_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा mac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा mac_desc_ctx *ctx = shash_desc_ctx(desc);
	u8 *स्थिरs = tctx->स्थिरs;

	अगर (ctx->len != AES_BLOCK_SIZE) अणु
		ctx->dg[ctx->len] ^= 0x80;
		स्थिरs += AES_BLOCK_SIZE;
	पूर्ण

	mac_करो_update(&tctx->key, स्थिरs, 1, ctx->dg, 0, 1);

	स_नकल(out, ctx->dg, AES_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg mac_algs[] = अणु अणु
	.base.cra_name		= "cmac(aes)",
	.base.cra_driver_name	= "cmac-aes-" MODE,
	.base.cra_priority	= PRIO,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा mac_tfm_ctx) +
				  2 * AES_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,

	.digestsize		= AES_BLOCK_SIZE,
	.init			= mac_init,
	.update			= mac_update,
	.final			= cmac_final,
	.setkey			= cmac_setkey,
	.descsize		= माप(काष्ठा mac_desc_ctx),
पूर्ण, अणु
	.base.cra_name		= "xcbc(aes)",
	.base.cra_driver_name	= "xcbc-aes-" MODE,
	.base.cra_priority	= PRIO,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा mac_tfm_ctx) +
				  2 * AES_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,

	.digestsize		= AES_BLOCK_SIZE,
	.init			= mac_init,
	.update			= mac_update,
	.final			= cmac_final,
	.setkey			= xcbc_setkey,
	.descsize		= माप(काष्ठा mac_desc_ctx),
पूर्ण, अणु
	.base.cra_name		= "cbcmac(aes)",
	.base.cra_driver_name	= "cbcmac-aes-" MODE,
	.base.cra_priority	= PRIO,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा mac_tfm_ctx),
	.base.cra_module	= THIS_MODULE,

	.digestsize		= AES_BLOCK_SIZE,
	.init			= mac_init,
	.update			= mac_update,
	.final			= cbcmac_final,
	.setkey			= cbcmac_setkey,
	.descsize		= माप(काष्ठा mac_desc_ctx),
पूर्ण पूर्ण;

अटल काष्ठा simd_skcipher_alg *aes_simd_algs[ARRAY_SIZE(aes_algs)];

अटल व्योम aes_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aes_simd_algs); i++)
		अगर (aes_simd_algs[i])
			simd_skcipher_मुक्त(aes_simd_algs[i]);

	crypto_unरेजिस्टर_shashes(mac_algs, ARRAY_SIZE(mac_algs));
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

	err = crypto_रेजिस्टर_skciphers(aes_algs, ARRAY_SIZE(aes_algs));
	अगर (err)
		वापस err;

	err = crypto_रेजिस्टर_shashes(mac_algs, ARRAY_SIZE(mac_algs));
	अगर (err)
		जाओ unरेजिस्टर_ciphers;

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
unरेजिस्टर_ciphers:
	crypto_unरेजिस्टर_skciphers(aes_algs, ARRAY_SIZE(aes_algs));
	वापस err;
पूर्ण

#अगर_घोषित USE_V8_CRYPTO_EXTENSIONS
module_cpu_feature_match(AES, aes_init);
#अन्यथा
module_init(aes_init);
EXPORT_SYMBOL(neon_aes_ecb_encrypt);
EXPORT_SYMBOL(neon_aes_cbc_encrypt);
EXPORT_SYMBOL(neon_aes_xts_encrypt);
EXPORT_SYMBOL(neon_aes_xts_decrypt);
#पूर्ण_अगर
module_निकास(aes_निकास);
