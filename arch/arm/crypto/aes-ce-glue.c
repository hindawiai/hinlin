<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * aes-ce-glue.c - wrapper code क्रम ARMv8 AES
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/module.h>
#समावेश <crypto/xts.h>

MODULE_DESCRIPTION("AES-ECB/CBC/CTR/XTS using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

/* defined in aes-ce-core.S */
यंत्रlinkage u32 ce_aes_sub(u32 input);
यंत्रlinkage व्योम ce_aes_invert(व्योम *dst, व्योम *src);

यंत्रlinkage व्योम ce_aes_ecb_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक blocks);
यंत्रlinkage व्योम ce_aes_ecb_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक blocks);

यंत्रlinkage व्योम ce_aes_cbc_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);
यंत्रlinkage व्योम ce_aes_cbc_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक blocks, u8 iv[]);
यंत्रlinkage व्योम ce_aes_cbc_cts_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक bytes, u8 स्थिर iv[]);
यंत्रlinkage व्योम ce_aes_cbc_cts_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक bytes, u8 स्थिर iv[]);

यंत्रlinkage व्योम ce_aes_ctr_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk[],
				   पूर्णांक rounds, पूर्णांक blocks, u8 ctr[]);

यंत्रlinkage व्योम ce_aes_xts_encrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk1[],
				   पूर्णांक rounds, पूर्णांक bytes, u8 iv[],
				   u32 स्थिर rk2[], पूर्णांक first);
यंत्रlinkage व्योम ce_aes_xts_decrypt(u8 out[], u8 स्थिर in[], u32 स्थिर rk1[],
				   पूर्णांक rounds, पूर्णांक bytes, u8 iv[],
				   u32 स्थिर rk2[], पूर्णांक first);

काष्ठा aes_block अणु
	u8 b[AES_BLOCK_SIZE];
पूर्ण;

अटल पूर्णांक num_rounds(काष्ठा crypto_aes_ctx *ctx)
अणु
	/*
	 * # of rounds specअगरied by AES:
	 * 128 bit key		10 rounds
	 * 192 bit key		12 rounds
	 * 256 bit key		14 rounds
	 * => n byte key	=> 6 + (n/4) rounds
	 */
	वापस 6 + ctx->key_length / 4;
पूर्ण

अटल पूर्णांक ce_aes_expandkey(काष्ठा crypto_aes_ctx *ctx, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	/*
	 * The AES key schedule round स्थिरants
	 */
	अटल u8 स्थिर rcon[] = अणु
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
	पूर्ण;

	u32 kwords = key_len / माप(u32);
	काष्ठा aes_block *key_enc, *key_dec;
	पूर्णांक i, j;

	अगर (key_len != AES_KEYSIZE_128 &&
	    key_len != AES_KEYSIZE_192 &&
	    key_len != AES_KEYSIZE_256)
		वापस -EINVAL;

	ctx->key_length = key_len;
	क्रम (i = 0; i < kwords; i++)
		ctx->key_enc[i] = get_unaligned_le32(in_key + i * माप(u32));

	kernel_neon_begin();
	क्रम (i = 0; i < माप(rcon); i++) अणु
		u32 *rki = ctx->key_enc + (i * kwords);
		u32 *rko = rki + kwords;

		rko[0] = ror32(ce_aes_sub(rki[kwords - 1]), 8);
		rko[0] = rko[0] ^ rki[0] ^ rcon[i];
		rko[1] = rko[0] ^ rki[1];
		rko[2] = rko[1] ^ rki[2];
		rko[3] = rko[2] ^ rki[3];

		अगर (key_len == AES_KEYSIZE_192) अणु
			अगर (i >= 7)
				अवरोध;
			rko[4] = rko[3] ^ rki[4];
			rko[5] = rko[4] ^ rki[5];
		पूर्ण अन्यथा अगर (key_len == AES_KEYSIZE_256) अणु
			अगर (i >= 6)
				अवरोध;
			rko[4] = ce_aes_sub(rko[3]) ^ rki[4];
			rko[5] = rko[4] ^ rki[5];
			rko[6] = rko[5] ^ rki[6];
			rko[7] = rko[6] ^ rki[7];
		पूर्ण
	पूर्ण

	/*
	 * Generate the decryption keys क्रम the Equivalent Inverse Cipher.
	 * This involves reversing the order of the round keys, and applying
	 * the Inverse Mix Columns transक्रमmation on all but the first and
	 * the last one.
	 */
	key_enc = (काष्ठा aes_block *)ctx->key_enc;
	key_dec = (काष्ठा aes_block *)ctx->key_dec;
	j = num_rounds(ctx);

	key_dec[0] = key_enc[j];
	क्रम (i = 1, j--; j > 0; i++, j--)
		ce_aes_invert(key_dec + i, key_enc + j);
	key_dec[i] = key_enc[0];

	kernel_neon_end();
	वापस 0;
पूर्ण

अटल पूर्णांक ce_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			 अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस ce_aes_expandkey(ctx, in_key, key_len);
पूर्ण

काष्ठा crypto_aes_xts_ctx अणु
	काष्ठा crypto_aes_ctx key1;
	काष्ठा crypto_aes_ctx __aligned(8) key2;
पूर्ण;

अटल पूर्णांक xts_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	ret = xts_verअगरy_key(tfm, in_key, key_len);
	अगर (ret)
		वापस ret;

	ret = ce_aes_expandkey(&ctx->key1, in_key, key_len / 2);
	अगर (!ret)
		ret = ce_aes_expandkey(&ctx->key2, &in_key[key_len / 2],
				       key_len / 2);
	वापस ret;
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक blocks;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		ce_aes_ecb_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				   ctx->key_enc, num_rounds(ctx), blocks);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक blocks;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		ce_aes_ecb_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
				   ctx->key_dec, num_rounds(ctx), blocks);
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
	अचिन्हित पूर्णांक blocks;
	पूर्णांक err = 0;

	जबतक ((blocks = (walk->nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		ce_aes_cbc_encrypt(walk->dst.virt.addr, walk->src.virt.addr,
				   ctx->key_enc, num_rounds(ctx), blocks,
				   walk->iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(walk, walk->nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
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
	अचिन्हित पूर्णांक blocks;
	पूर्णांक err = 0;

	जबतक ((blocks = (walk->nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		ce_aes_cbc_decrypt(walk->dst.virt.addr, walk->src.virt.addr,
				   ctx->key_dec, num_rounds(ctx), blocks,
				   walk->iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(walk, walk->nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
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
	पूर्णांक cbc_blocks = DIV_ROUND_UP(req->cryptlen, AES_BLOCK_SIZE) - 2;
	काष्ठा scatterlist *src = req->src, *dst = req->dst;
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

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
	ce_aes_cbc_cts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
			       ctx->key_enc, num_rounds(ctx), walk.nbytes,
			       walk.iv);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक cts_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक cbc_blocks = DIV_ROUND_UP(req->cryptlen, AES_BLOCK_SIZE) - 2;
	काष्ठा scatterlist *src = req->src, *dst = req->dst;
	काष्ठा scatterlist sg_src[2], sg_dst[2];
	काष्ठा skcipher_request subreq;
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

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
	ce_aes_cbc_cts_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
			       ctx->key_dec, num_rounds(ctx), walk.nbytes,
			       walk.iv);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	पूर्णांक err, blocks;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((blocks = (walk.nbytes / AES_BLOCK_SIZE))) अणु
		kernel_neon_begin();
		ce_aes_ctr_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				   ctx->key_enc, num_rounds(ctx), blocks,
				   walk.iv);
		kernel_neon_end();
		err = skcipher_walk_करोne(&walk, walk.nbytes % AES_BLOCK_SIZE);
	पूर्ण
	अगर (walk.nbytes) अणु
		u8 __aligned(8) tail[AES_BLOCK_SIZE];
		अचिन्हित पूर्णांक nbytes = walk.nbytes;
		u8 *tdst = walk.dst.virt.addr;
		u8 *tsrc = walk.src.virt.addr;

		/*
		 * Tell aes_ctr_encrypt() to process a tail block.
		 */
		blocks = -1;

		kernel_neon_begin();
		ce_aes_ctr_encrypt(tail, शून्य, ctx->key_enc, num_rounds(ctx),
				   blocks, walk.iv);
		kernel_neon_end();
		crypto_xor_cpy(tdst, tsrc, tail, nbytes);
		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ctr_encrypt_one(काष्ठा crypto_skcipher *tfm, स्थिर u8 *src, u8 *dst)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
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

अटल पूर्णांक ctr_encrypt_sync(काष्ठा skcipher_request *req)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_ctr_encrypt_walk(req, ctr_encrypt_one);

	वापस ctr_encrypt(req);
पूर्ण

अटल पूर्णांक xts_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, first, rounds = num_rounds(&ctx->key1);
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
		ce_aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				   ctx->key1.key_enc, rounds, nbytes, walk.iv,
				   ctx->key2.key_enc, first);
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

	err = skcipher_walk_virt(&walk, req, false);
	अगर (err)
		वापस err;

	kernel_neon_begin();
	ce_aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
			   ctx->key1.key_enc, rounds, walk.nbytes, walk.iv,
			   ctx->key2.key_enc, first);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक xts_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err, first, rounds = num_rounds(&ctx->key1);
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
		ce_aes_xts_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
				   ctx->key1.key_dec, rounds, nbytes, walk.iv,
				   ctx->key2.key_enc, first);
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

	err = skcipher_walk_virt(&walk, req, false);
	अगर (err)
		वापस err;

	kernel_neon_begin();
	ce_aes_xts_decrypt(walk.dst.virt.addr, walk.src.virt.addr,
			   ctx->key1.key_dec, rounds, walk.nbytes, walk.iv,
			   ctx->key2.key_enc, first);
	kernel_neon_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल काष्ठा skcipher_alg aes_algs[] = अणु अणु
	.base.cra_name		= "__ecb(aes)",
	.base.cra_driver_name	= "__ecb-aes-ce",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा crypto_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= ce_aes_setkey,
	.encrypt		= ecb_encrypt,
	.decrypt		= ecb_decrypt,
पूर्ण, अणु
	.base.cra_name		= "__cbc(aes)",
	.base.cra_driver_name	= "__cbc-aes-ce",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा crypto_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encrypt		= cbc_encrypt,
	.decrypt		= cbc_decrypt,
पूर्ण, अणु
	.base.cra_name		= "__cts(cbc(aes))",
	.base.cra_driver_name	= "__cts-cbc-aes-ce",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा crypto_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.walksize		= 2 * AES_BLOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encrypt		= cts_cbc_encrypt,
	.decrypt		= cts_cbc_decrypt,
पूर्ण, अणु
	.base.cra_name		= "__ctr(aes)",
	.base.cra_driver_name	= "__ctr-aes-ce",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा crypto_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.chunksize		= AES_BLOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encrypt		= ctr_encrypt,
	.decrypt		= ctr_encrypt,
पूर्ण, अणु
	.base.cra_name		= "ctr(aes)",
	.base.cra_driver_name	= "ctr-aes-ce-sync",
	.base.cra_priority	= 300 - 1,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा crypto_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.chunksize		= AES_BLOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encrypt		= ctr_encrypt_sync,
	.decrypt		= ctr_encrypt_sync,
पूर्ण, अणु
	.base.cra_name		= "__xts(aes)",
	.base.cra_driver_name	= "__xts-aes-ce",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_INTERNAL,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा crypto_aes_xts_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.walksize		= 2 * AES_BLOCK_SIZE,
	.setkey			= xts_set_key,
	.encrypt		= xts_encrypt,
	.decrypt		= xts_decrypt,
पूर्ण पूर्ण;

अटल काष्ठा simd_skcipher_alg *aes_simd_algs[ARRAY_SIZE(aes_algs)];

अटल व्योम aes_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aes_simd_algs) && aes_simd_algs[i]; i++)
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

module_cpu_feature_match(AES, aes_init);
module_निकास(aes_निकास);
