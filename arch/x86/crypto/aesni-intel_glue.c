<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम Intel AES-NI inकाष्ठाions. This file contains glue
 * code, the real AES implementation is in पूर्णांकel-aes_यंत्र.S.
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

#समावेश <linux/hardirq.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/b128ops.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/xts.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/simd.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अटल_call.h>


#घोषणा AESNI_ALIGN	16
#घोषणा AESNI_ALIGN_ATTR __attribute__ ((__aligned__(AESNI_ALIGN)))
#घोषणा AES_BLOCK_MASK	(~(AES_BLOCK_SIZE - 1))
#घोषणा RFC4106_HASH_SUBKEY_SIZE 16
#घोषणा AESNI_ALIGN_EXTRA ((AESNI_ALIGN - 1) & ~(CRYPTO_MINALIGN - 1))
#घोषणा CRYPTO_AES_CTX_SIZE (माप(काष्ठा crypto_aes_ctx) + AESNI_ALIGN_EXTRA)
#घोषणा XTS_AES_CTX_SIZE (माप(काष्ठा aesni_xts_ctx) + AESNI_ALIGN_EXTRA)

/* This data is stored at the end of the crypto_tfm काष्ठा.
 * It's a type of per "session" data storage location.
 * This needs to be 16 byte aligned.
 */
काष्ठा aesni_rfc4106_gcm_ctx अणु
	u8 hash_subkey[16] AESNI_ALIGN_ATTR;
	काष्ठा crypto_aes_ctx aes_key_expanded AESNI_ALIGN_ATTR;
	u8 nonce[4];
पूर्ण;

काष्ठा generic_gcmaes_ctx अणु
	u8 hash_subkey[16] AESNI_ALIGN_ATTR;
	काष्ठा crypto_aes_ctx aes_key_expanded AESNI_ALIGN_ATTR;
पूर्ण;

काष्ठा aesni_xts_ctx अणु
	u8 raw_tweak_ctx[माप(काष्ठा crypto_aes_ctx)] AESNI_ALIGN_ATTR;
	u8 raw_crypt_ctx[माप(काष्ठा crypto_aes_ctx)] AESNI_ALIGN_ATTR;
पूर्ण;

#घोषणा GCM_BLOCK_LEN 16

काष्ठा gcm_context_data अणु
	/* init, update and finalize context data */
	u8 aad_hash[GCM_BLOCK_LEN];
	u64 aad_length;
	u64 in_length;
	u8 partial_block_enc_key[GCM_BLOCK_LEN];
	u8 orig_IV[GCM_BLOCK_LEN];
	u8 current_counter[GCM_BLOCK_LEN];
	u64 partial_block_len;
	u64 unused;
	u8 hash_keys[GCM_BLOCK_LEN * 16];
पूर्ण;

यंत्रlinkage पूर्णांक aesni_set_key(काष्ठा crypto_aes_ctx *ctx, स्थिर u8 *in_key,
			     अचिन्हित पूर्णांक key_len);
यंत्रlinkage व्योम aesni_enc(स्थिर व्योम *ctx, u8 *out, स्थिर u8 *in);
यंत्रlinkage व्योम aesni_dec(स्थिर व्योम *ctx, u8 *out, स्थिर u8 *in);
यंत्रlinkage व्योम aesni_ecb_enc(काष्ठा crypto_aes_ctx *ctx, u8 *out,
			      स्थिर u8 *in, अचिन्हित पूर्णांक len);
यंत्रlinkage व्योम aesni_ecb_dec(काष्ठा crypto_aes_ctx *ctx, u8 *out,
			      स्थिर u8 *in, अचिन्हित पूर्णांक len);
यंत्रlinkage व्योम aesni_cbc_enc(काष्ठा crypto_aes_ctx *ctx, u8 *out,
			      स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);
यंत्रlinkage व्योम aesni_cbc_dec(काष्ठा crypto_aes_ctx *ctx, u8 *out,
			      स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);
यंत्रlinkage व्योम aesni_cts_cbc_enc(काष्ठा crypto_aes_ctx *ctx, u8 *out,
				  स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);
यंत्रlinkage व्योम aesni_cts_cbc_dec(काष्ठा crypto_aes_ctx *ctx, u8 *out,
				  स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);

#घोषणा AVX_GEN2_OPTSIZE 640
#घोषणा AVX_GEN4_OPTSIZE 4096

यंत्रlinkage व्योम aesni_xts_encrypt(स्थिर काष्ठा crypto_aes_ctx *ctx, u8 *out,
				  स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);

यंत्रlinkage व्योम aesni_xts_decrypt(स्थिर काष्ठा crypto_aes_ctx *ctx, u8 *out,
				  स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);

#अगर_घोषित CONFIG_X86_64

यंत्रlinkage व्योम aesni_ctr_enc(काष्ठा crypto_aes_ctx *ctx, u8 *out,
			      स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv);
DEFINE_STATIC_CALL(aesni_ctr_enc_tfm, aesni_ctr_enc);

/* Scatter / Gather routines, with args similar to above */
यंत्रlinkage व्योम aesni_gcm_init(व्योम *ctx,
			       काष्ठा gcm_context_data *gdata,
			       u8 *iv,
			       u8 *hash_subkey, स्थिर u8 *aad,
			       अचिन्हित दीर्घ aad_len);
यंत्रlinkage व्योम aesni_gcm_enc_update(व्योम *ctx,
				     काष्ठा gcm_context_data *gdata, u8 *out,
				     स्थिर u8 *in, अचिन्हित दीर्घ plaपूर्णांकext_len);
यंत्रlinkage व्योम aesni_gcm_dec_update(व्योम *ctx,
				     काष्ठा gcm_context_data *gdata, u8 *out,
				     स्थिर u8 *in,
				     अचिन्हित दीर्घ ciphertext_len);
यंत्रlinkage व्योम aesni_gcm_finalize(व्योम *ctx,
				   काष्ठा gcm_context_data *gdata,
				   u8 *auth_tag, अचिन्हित दीर्घ auth_tag_len);

यंत्रlinkage व्योम aes_ctr_enc_128_avx_by8(स्थिर u8 *in, u8 *iv,
		व्योम *keys, u8 *out, अचिन्हित पूर्णांक num_bytes);
यंत्रlinkage व्योम aes_ctr_enc_192_avx_by8(स्थिर u8 *in, u8 *iv,
		व्योम *keys, u8 *out, अचिन्हित पूर्णांक num_bytes);
यंत्रlinkage व्योम aes_ctr_enc_256_avx_by8(स्थिर u8 *in, u8 *iv,
		व्योम *keys, u8 *out, अचिन्हित पूर्णांक num_bytes);
/*
 * यंत्रlinkage व्योम aesni_gcm_init_avx_gen2()
 * gcm_data *my_ctx_data, context data
 * u8 *hash_subkey,  the Hash sub key input. Data starts on a 16-byte boundary.
 */
यंत्रlinkage व्योम aesni_gcm_init_avx_gen2(व्योम *my_ctx_data,
					काष्ठा gcm_context_data *gdata,
					u8 *iv,
					u8 *hash_subkey,
					स्थिर u8 *aad,
					अचिन्हित दीर्घ aad_len);

यंत्रlinkage व्योम aesni_gcm_enc_update_avx_gen2(व्योम *ctx,
				     काष्ठा gcm_context_data *gdata, u8 *out,
				     स्थिर u8 *in, अचिन्हित दीर्घ plaपूर्णांकext_len);
यंत्रlinkage व्योम aesni_gcm_dec_update_avx_gen2(व्योम *ctx,
				     काष्ठा gcm_context_data *gdata, u8 *out,
				     स्थिर u8 *in,
				     अचिन्हित दीर्घ ciphertext_len);
यंत्रlinkage व्योम aesni_gcm_finalize_avx_gen2(व्योम *ctx,
				   काष्ठा gcm_context_data *gdata,
				   u8 *auth_tag, अचिन्हित दीर्घ auth_tag_len);

/*
 * यंत्रlinkage व्योम aesni_gcm_init_avx_gen4()
 * gcm_data *my_ctx_data, context data
 * u8 *hash_subkey,  the Hash sub key input. Data starts on a 16-byte boundary.
 */
यंत्रlinkage व्योम aesni_gcm_init_avx_gen4(व्योम *my_ctx_data,
					काष्ठा gcm_context_data *gdata,
					u8 *iv,
					u8 *hash_subkey,
					स्थिर u8 *aad,
					अचिन्हित दीर्घ aad_len);

यंत्रlinkage व्योम aesni_gcm_enc_update_avx_gen4(व्योम *ctx,
				     काष्ठा gcm_context_data *gdata, u8 *out,
				     स्थिर u8 *in, अचिन्हित दीर्घ plaपूर्णांकext_len);
यंत्रlinkage व्योम aesni_gcm_dec_update_avx_gen4(व्योम *ctx,
				     काष्ठा gcm_context_data *gdata, u8 *out,
				     स्थिर u8 *in,
				     अचिन्हित दीर्घ ciphertext_len);
यंत्रlinkage व्योम aesni_gcm_finalize_avx_gen4(व्योम *ctx,
				   काष्ठा gcm_context_data *gdata,
				   u8 *auth_tag, अचिन्हित दीर्घ auth_tag_len);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(gcm_use_avx);
अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(gcm_use_avx2);

अटल अंतरभूत काष्ठा
aesni_rfc4106_gcm_ctx *aesni_rfc4106_gcm_ctx_get(काष्ठा crypto_aead *tfm)
अणु
	अचिन्हित दीर्घ align = AESNI_ALIGN;

	अगर (align <= crypto_tfm_ctx_alignment())
		align = 1;
	वापस PTR_ALIGN(crypto_aead_ctx(tfm), align);
पूर्ण

अटल अंतरभूत काष्ठा
generic_gcmaes_ctx *generic_gcmaes_ctx_get(काष्ठा crypto_aead *tfm)
अणु
	अचिन्हित दीर्घ align = AESNI_ALIGN;

	अगर (align <= crypto_tfm_ctx_alignment())
		align = 1;
	वापस PTR_ALIGN(crypto_aead_ctx(tfm), align);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा crypto_aes_ctx *aes_ctx(व्योम *raw_ctx)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)raw_ctx;
	अचिन्हित दीर्घ align = AESNI_ALIGN;

	अगर (align <= crypto_tfm_ctx_alignment())
		align = 1;
	वापस (काष्ठा crypto_aes_ctx *)ALIGN(addr, align);
पूर्ण

अटल पूर्णांक aes_set_key_common(काष्ठा crypto_tfm *tfm, व्योम *raw_ctx,
			      स्थिर u8 *in_key, अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(raw_ctx);
	पूर्णांक err;

	अगर (key_len != AES_KEYSIZE_128 && key_len != AES_KEYSIZE_192 &&
	    key_len != AES_KEYSIZE_256)
		वापस -EINVAL;

	अगर (!crypto_simd_usable())
		err = aes_expandkey(ctx, in_key, key_len);
	अन्यथा अणु
		kernel_fpu_begin();
		err = aesni_set_key(ctx, in_key, key_len);
		kernel_fpu_end();
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aes_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	वापस aes_set_key_common(tfm, crypto_tfm_ctx(tfm), in_key, key_len);
पूर्ण

अटल व्योम aesni_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_tfm_ctx(tfm));

	अगर (!crypto_simd_usable()) अणु
		aes_encrypt(ctx, dst, src);
	पूर्ण अन्यथा अणु
		kernel_fpu_begin();
		aesni_enc(ctx, dst, src);
		kernel_fpu_end();
	पूर्ण
पूर्ण

अटल व्योम aesni_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_tfm_ctx(tfm));

	अगर (!crypto_simd_usable()) अणु
		aes_decrypt(ctx, dst, src);
	पूर्ण अन्यथा अणु
		kernel_fpu_begin();
		aesni_dec(ctx, dst, src);
		kernel_fpu_end();
	पूर्ण
पूर्ण

अटल पूर्णांक aesni_skcipher_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			         अचिन्हित पूर्णांक len)
अणु
	वापस aes_set_key_common(crypto_skcipher_tfm(tfm),
				  crypto_skcipher_ctx(tfm), key, len);
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		kernel_fpu_begin();
		aesni_ecb_enc(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			      nbytes & AES_BLOCK_MASK);
		kernel_fpu_end();
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		kernel_fpu_begin();
		aesni_ecb_dec(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			      nbytes & AES_BLOCK_MASK);
		kernel_fpu_end();
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		kernel_fpu_begin();
		aesni_cbc_enc(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			      nbytes & AES_BLOCK_MASK, walk.iv);
		kernel_fpu_end();
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		kernel_fpu_begin();
		aesni_cbc_dec(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			      nbytes & AES_BLOCK_MASK, walk.iv);
		kernel_fpu_end();
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cts_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
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

		err = cbc_encrypt(&subreq);
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

	kernel_fpu_begin();
	aesni_cts_cbc_enc(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			  walk.nbytes, walk.iv);
	kernel_fpu_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

अटल पूर्णांक cts_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
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

		err = cbc_decrypt(&subreq);
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

	kernel_fpu_begin();
	aesni_cts_cbc_dec(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			  walk.nbytes, walk.iv);
	kernel_fpu_end();

	वापस skcipher_walk_करोne(&walk, 0);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल व्योम aesni_ctr_enc_avx_tfm(काष्ठा crypto_aes_ctx *ctx, u8 *out,
			      स्थिर u8 *in, अचिन्हित पूर्णांक len, u8 *iv)
अणु
	/*
	 * based on key length, override with the by8 version
	 * of ctr mode encryption/decryption क्रम improved perक्रमmance
	 * aes_set_key_common() ensures that key length is one of
	 * अणु128,192,256पूर्ण
	 */
	अगर (ctx->key_length == AES_KEYSIZE_128)
		aes_ctr_enc_128_avx_by8(in, iv, (व्योम *)ctx, out, len);
	अन्यथा अगर (ctx->key_length == AES_KEYSIZE_192)
		aes_ctr_enc_192_avx_by8(in, iv, (व्योम *)ctx, out, len);
	अन्यथा
		aes_ctr_enc_256_avx_by8(in, iv, (व्योम *)ctx, out, len);
पूर्ण

अटल पूर्णांक ctr_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = aes_ctx(crypto_skcipher_ctx(tfm));
	u8 keystream[AES_BLOCK_SIZE];
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) > 0) अणु
		kernel_fpu_begin();
		अगर (nbytes & AES_BLOCK_MASK)
			अटल_call(aesni_ctr_enc_tfm)(ctx, walk.dst.virt.addr,
						       walk.src.virt.addr,
						       nbytes & AES_BLOCK_MASK,
						       walk.iv);
		nbytes &= ~AES_BLOCK_MASK;

		अगर (walk.nbytes == walk.total && nbytes > 0) अणु
			aesni_enc(ctx, keystream, walk.iv);
			crypto_xor_cpy(walk.dst.virt.addr + walk.nbytes - nbytes,
				       walk.src.virt.addr + walk.nbytes - nbytes,
				       keystream, nbytes);
			crypto_inc(walk.iv, AES_BLOCK_SIZE);
			nbytes = 0;
		पूर्ण
		kernel_fpu_end();
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
rfc4106_set_hash_subkey(u8 *hash_subkey, स्थिर u8 *key, अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx ctx;
	पूर्णांक ret;

	ret = aes_expandkey(&ctx, key, key_len);
	अगर (ret)
		वापस ret;

	/* Clear the data in the hash sub key container to zero.*/
	/* We want to cipher all zeros to create the hash sub key. */
	स_रखो(hash_subkey, 0, RFC4106_HASH_SUBKEY_SIZE);

	aes_encrypt(&ctx, hash_subkey, hash_subkey);

	memzero_explicit(&ctx, माप(ctx));
	वापस 0;
पूर्ण

अटल पूर्णांक common_rfc4106_set_key(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा aesni_rfc4106_gcm_ctx *ctx = aesni_rfc4106_gcm_ctx_get(aead);

	अगर (key_len < 4)
		वापस -EINVAL;

	/*Account क्रम 4 byte nonce at the end.*/
	key_len -= 4;

	स_नकल(ctx->nonce, key + key_len, माप(ctx->nonce));

	वापस aes_set_key_common(crypto_aead_tfm(aead),
				  &ctx->aes_key_expanded, key, key_len) ?:
	       rfc4106_set_hash_subkey(ctx->hash_subkey, key, key_len);
पूर्ण

/* This is the Integrity Check Value (aka the authentication tag) length and can
 * be 8, 12 or 16 bytes दीर्घ. */
अटल पूर्णांक common_rfc4106_set_authsize(काष्ठा crypto_aead *aead,
				       अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक generic_gcmaes_set_authsize(काष्ठा crypto_aead *tfm,
				       अचिन्हित पूर्णांक authsize)
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

अटल पूर्णांक gcmaes_crypt_by_sg(bool enc, काष्ठा aead_request *req,
			      अचिन्हित पूर्णांक assoclen, u8 *hash_subkey,
			      u8 *iv, व्योम *aes_ctx, u8 *auth_tag,
			      अचिन्हित दीर्घ auth_tag_len)
अणु
	u8 databuf[माप(काष्ठा gcm_context_data) + (AESNI_ALIGN - 8)] __aligned(8);
	काष्ठा gcm_context_data *data = PTR_ALIGN((व्योम *)databuf, AESNI_ALIGN);
	अचिन्हित दीर्घ left = req->cryptlen;
	काष्ठा scatter_walk assoc_sg_walk;
	काष्ठा skcipher_walk walk;
	bool करो_avx, करो_avx2;
	u8 *assocmem = शून्य;
	u8 *assoc;
	पूर्णांक err;

	अगर (!enc)
		left -= auth_tag_len;

	करो_avx = (left >= AVX_GEN2_OPTSIZE);
	करो_avx2 = (left >= AVX_GEN4_OPTSIZE);

	/* Linearize assoc, अगर not alपढ़ोy linear */
	अगर (req->src->length >= assoclen && req->src->length) अणु
		scatterwalk_start(&assoc_sg_walk, req->src);
		assoc = scatterwalk_map(&assoc_sg_walk);
	पूर्ण अन्यथा अणु
		gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
			      GFP_KERNEL : GFP_ATOMIC;

		/* assoc can be any length, so must be on heap */
		assocmem = kदो_स्मृति(assoclen, flags);
		अगर (unlikely(!assocmem))
			वापस -ENOMEM;
		assoc = assocmem;

		scatterwalk_map_and_copy(assoc, req->src, 0, assoclen, 0);
	पूर्ण

	kernel_fpu_begin();
	अगर (अटल_branch_likely(&gcm_use_avx2) && करो_avx2)
		aesni_gcm_init_avx_gen4(aes_ctx, data, iv, hash_subkey, assoc,
					assoclen);
	अन्यथा अगर (अटल_branch_likely(&gcm_use_avx) && करो_avx)
		aesni_gcm_init_avx_gen2(aes_ctx, data, iv, hash_subkey, assoc,
					assoclen);
	अन्यथा
		aesni_gcm_init(aes_ctx, data, iv, hash_subkey, assoc, assoclen);
	kernel_fpu_end();

	अगर (!assocmem)
		scatterwalk_unmap(assoc);
	अन्यथा
		kमुक्त(assocmem);

	err = enc ? skcipher_walk_aead_encrypt(&walk, req, false)
		  : skcipher_walk_aead_decrypt(&walk, req, false);

	जबतक (walk.nbytes > 0) अणु
		kernel_fpu_begin();
		अगर (अटल_branch_likely(&gcm_use_avx2) && करो_avx2) अणु
			अगर (enc)
				aesni_gcm_enc_update_avx_gen4(aes_ctx, data,
							      walk.dst.virt.addr,
							      walk.src.virt.addr,
							      walk.nbytes);
			अन्यथा
				aesni_gcm_dec_update_avx_gen4(aes_ctx, data,
							      walk.dst.virt.addr,
							      walk.src.virt.addr,
							      walk.nbytes);
		पूर्ण अन्यथा अगर (अटल_branch_likely(&gcm_use_avx) && करो_avx) अणु
			अगर (enc)
				aesni_gcm_enc_update_avx_gen2(aes_ctx, data,
							      walk.dst.virt.addr,
							      walk.src.virt.addr,
							      walk.nbytes);
			अन्यथा
				aesni_gcm_dec_update_avx_gen2(aes_ctx, data,
							      walk.dst.virt.addr,
							      walk.src.virt.addr,
							      walk.nbytes);
		पूर्ण अन्यथा अगर (enc) अणु
			aesni_gcm_enc_update(aes_ctx, data, walk.dst.virt.addr,
					     walk.src.virt.addr, walk.nbytes);
		पूर्ण अन्यथा अणु
			aesni_gcm_dec_update(aes_ctx, data, walk.dst.virt.addr,
					     walk.src.virt.addr, walk.nbytes);
		पूर्ण
		kernel_fpu_end();

		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण

	अगर (err)
		वापस err;

	kernel_fpu_begin();
	अगर (अटल_branch_likely(&gcm_use_avx2) && करो_avx2)
		aesni_gcm_finalize_avx_gen4(aes_ctx, data, auth_tag,
					    auth_tag_len);
	अन्यथा अगर (अटल_branch_likely(&gcm_use_avx) && करो_avx)
		aesni_gcm_finalize_avx_gen2(aes_ctx, data, auth_tag,
					    auth_tag_len);
	अन्यथा
		aesni_gcm_finalize(aes_ctx, data, auth_tag, auth_tag_len);
	kernel_fpu_end();

	वापस 0;
पूर्ण

अटल पूर्णांक gcmaes_encrypt(काष्ठा aead_request *req, अचिन्हित पूर्णांक assoclen,
			  u8 *hash_subkey, u8 *iv, व्योम *aes_ctx)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	अचिन्हित दीर्घ auth_tag_len = crypto_aead_authsize(tfm);
	u8 auth_tag[16];
	पूर्णांक err;

	err = gcmaes_crypt_by_sg(true, req, assoclen, hash_subkey, iv, aes_ctx,
				 auth_tag, auth_tag_len);
	अगर (err)
		वापस err;

	scatterwalk_map_and_copy(auth_tag, req->dst,
				 req->assoclen + req->cryptlen,
				 auth_tag_len, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक gcmaes_decrypt(काष्ठा aead_request *req, अचिन्हित पूर्णांक assoclen,
			  u8 *hash_subkey, u8 *iv, व्योम *aes_ctx)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	अचिन्हित दीर्घ auth_tag_len = crypto_aead_authsize(tfm);
	u8 auth_tag_msg[16];
	u8 auth_tag[16];
	पूर्णांक err;

	err = gcmaes_crypt_by_sg(false, req, assoclen, hash_subkey, iv, aes_ctx,
				 auth_tag, auth_tag_len);
	अगर (err)
		वापस err;

	/* Copy out original auth_tag */
	scatterwalk_map_and_copy(auth_tag_msg, req->src,
				 req->assoclen + req->cryptlen - auth_tag_len,
				 auth_tag_len, 0);

	/* Compare generated tag with passed in tag. */
	अगर (crypto_memneq(auth_tag_msg, auth_tag, auth_tag_len)) अणु
		memzero_explicit(auth_tag, माप(auth_tag));
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक helper_rfc4106_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aesni_rfc4106_gcm_ctx *ctx = aesni_rfc4106_gcm_ctx_get(tfm);
	व्योम *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_ALIGN - 8)] __aligned(8);
	u8 *iv = PTR_ALIGN(&ivbuf[0], AESNI_ALIGN);
	अचिन्हित पूर्णांक i;
	__be32 counter = cpu_to_be32(1);

	/* Assuming we are supporting rfc4106 64-bit extended */
	/* sequence numbers We need to have the AAD length equal */
	/* to 16 or 20 bytes */
	अगर (unlikely(req->assoclen != 16 && req->assoclen != 20))
		वापस -EINVAL;

	/* IV below built */
	क्रम (i = 0; i < 4; i++)
		*(iv+i) = ctx->nonce[i];
	क्रम (i = 0; i < 8; i++)
		*(iv+4+i) = req->iv[i];
	*((__be32 *)(iv+12)) = counter;

	वापस gcmaes_encrypt(req, req->assoclen - 8, ctx->hash_subkey, iv,
			      aes_ctx);
पूर्ण

अटल पूर्णांक helper_rfc4106_decrypt(काष्ठा aead_request *req)
अणु
	__be32 counter = cpu_to_be32(1);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aesni_rfc4106_gcm_ctx *ctx = aesni_rfc4106_gcm_ctx_get(tfm);
	व्योम *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_ALIGN - 8)] __aligned(8);
	u8 *iv = PTR_ALIGN(&ivbuf[0], AESNI_ALIGN);
	अचिन्हित पूर्णांक i;

	अगर (unlikely(req->assoclen != 16 && req->assoclen != 20))
		वापस -EINVAL;

	/* Assuming we are supporting rfc4106 64-bit extended */
	/* sequence numbers We need to have the AAD length */
	/* equal to 16 or 20 bytes */

	/* IV below built */
	क्रम (i = 0; i < 4; i++)
		*(iv+i) = ctx->nonce[i];
	क्रम (i = 0; i < 8; i++)
		*(iv+4+i) = req->iv[i];
	*((__be32 *)(iv+12)) = counter;

	वापस gcmaes_decrypt(req, req->assoclen - 8, ctx->hash_subkey, iv,
			      aes_ctx);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xts_aesni_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aesni_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = xts_verअगरy_key(tfm, key, keylen);
	अगर (err)
		वापस err;

	keylen /= 2;

	/* first half of xts-key is क्रम crypt */
	err = aes_set_key_common(crypto_skcipher_tfm(tfm), ctx->raw_crypt_ctx,
				 key, keylen);
	अगर (err)
		वापस err;

	/* second half of xts-key is क्रम tweak */
	वापस aes_set_key_common(crypto_skcipher_tfm(tfm), ctx->raw_tweak_ctx,
				  key + keylen, keylen);
पूर्ण

अटल पूर्णांक xts_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aesni_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक tail = req->cryptlen % AES_BLOCK_SIZE;
	काष्ठा skcipher_request subreq;
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	err = skcipher_walk_virt(&walk, req, false);

	अगर (unlikely(tail > 0 && walk.nbytes < walk.total)) अणु
		पूर्णांक blocks = DIV_ROUND_UP(req->cryptlen, AES_BLOCK_SIZE) - 2;

		skcipher_walk_पात(&walk);

		skcipher_request_set_tfm(&subreq, tfm);
		skcipher_request_set_callback(&subreq,
					      skcipher_request_flags(req),
					      शून्य, शून्य);
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   blocks * AES_BLOCK_SIZE, req->iv);
		req = &subreq;
		err = skcipher_walk_virt(&walk, req, false);
	पूर्ण अन्यथा अणु
		tail = 0;
	पूर्ण

	kernel_fpu_begin();

	/* calculate first value of T */
	aesni_enc(aes_ctx(ctx->raw_tweak_ctx), walk.iv, walk.iv);

	जबतक (walk.nbytes > 0) अणु
		पूर्णांक nbytes = walk.nbytes;

		अगर (nbytes < walk.total)
			nbytes &= ~(AES_BLOCK_SIZE - 1);

		अगर (encrypt)
			aesni_xts_encrypt(aes_ctx(ctx->raw_crypt_ctx),
					  walk.dst.virt.addr, walk.src.virt.addr,
					  nbytes, walk.iv);
		अन्यथा
			aesni_xts_decrypt(aes_ctx(ctx->raw_crypt_ctx),
					  walk.dst.virt.addr, walk.src.virt.addr,
					  nbytes, walk.iv);
		kernel_fpu_end();

		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);

		अगर (walk.nbytes > 0)
			kernel_fpu_begin();
	पूर्ण

	अगर (unlikely(tail > 0 && !err)) अणु
		काष्ठा scatterlist sg_src[2], sg_dst[2];
		काष्ठा scatterlist *src, *dst;

		dst = src = scatterwalk_ffwd(sg_src, req->src, req->cryptlen);
		अगर (req->dst != req->src)
			dst = scatterwalk_ffwd(sg_dst, req->dst, req->cryptlen);

		skcipher_request_set_crypt(req, src, dst, AES_BLOCK_SIZE + tail,
					   req->iv);

		err = skcipher_walk_virt(&walk, &subreq, false);
		अगर (err)
			वापस err;

		kernel_fpu_begin();
		अगर (encrypt)
			aesni_xts_encrypt(aes_ctx(ctx->raw_crypt_ctx),
					  walk.dst.virt.addr, walk.src.virt.addr,
					  walk.nbytes, walk.iv);
		अन्यथा
			aesni_xts_decrypt(aes_ctx(ctx->raw_crypt_ctx),
					  walk.dst.virt.addr, walk.src.virt.addr,
					  walk.nbytes, walk.iv);
		kernel_fpu_end();

		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक xts_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस xts_crypt(req, true);
पूर्ण

अटल पूर्णांक xts_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस xts_crypt(req, false);
पूर्ण

अटल काष्ठा crypto_alg aesni_cipher_alg = अणु
	.cra_name		= "aes",
	.cra_driver_name	= "aes-aesni",
	.cra_priority		= 300,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= AES_BLOCK_SIZE,
	.cra_ctxsize		= CRYPTO_AES_CTX_SIZE,
	.cra_module		= THIS_MODULE,
	.cra_u	= अणु
		.cipher	= अणु
			.cia_min_keysize	= AES_MIN_KEY_SIZE,
			.cia_max_keysize	= AES_MAX_KEY_SIZE,
			.cia_setkey		= aes_set_key,
			.cia_encrypt		= aesni_encrypt,
			.cia_decrypt		= aesni_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg aesni_skciphers[] = अणु
	अणु
		.base = अणु
			.cra_name		= "__ecb(aes)",
			.cra_driver_name	= "__ecb-aes-aesni",
			.cra_priority		= 400,
			.cra_flags		= CRYPTO_ALG_INTERNAL,
			.cra_blocksize		= AES_BLOCK_SIZE,
			.cra_ctxsize		= CRYPTO_AES_CTX_SIZE,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= aesni_skcipher_setkey,
		.encrypt	= ecb_encrypt,
		.decrypt	= ecb_decrypt,
	पूर्ण, अणु
		.base = अणु
			.cra_name		= "__cbc(aes)",
			.cra_driver_name	= "__cbc-aes-aesni",
			.cra_priority		= 400,
			.cra_flags		= CRYPTO_ALG_INTERNAL,
			.cra_blocksize		= AES_BLOCK_SIZE,
			.cra_ctxsize		= CRYPTO_AES_CTX_SIZE,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= aesni_skcipher_setkey,
		.encrypt	= cbc_encrypt,
		.decrypt	= cbc_decrypt,
	पूर्ण, अणु
		.base = अणु
			.cra_name		= "__cts(cbc(aes))",
			.cra_driver_name	= "__cts-cbc-aes-aesni",
			.cra_priority		= 400,
			.cra_flags		= CRYPTO_ALG_INTERNAL,
			.cra_blocksize		= AES_BLOCK_SIZE,
			.cra_ctxsize		= CRYPTO_AES_CTX_SIZE,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.walksize	= 2 * AES_BLOCK_SIZE,
		.setkey		= aesni_skcipher_setkey,
		.encrypt	= cts_cbc_encrypt,
		.decrypt	= cts_cbc_decrypt,
#अगर_घोषित CONFIG_X86_64
	पूर्ण, अणु
		.base = अणु
			.cra_name		= "__ctr(aes)",
			.cra_driver_name	= "__ctr-aes-aesni",
			.cra_priority		= 400,
			.cra_flags		= CRYPTO_ALG_INTERNAL,
			.cra_blocksize		= 1,
			.cra_ctxsize		= CRYPTO_AES_CTX_SIZE,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.chunksize	= AES_BLOCK_SIZE,
		.setkey		= aesni_skcipher_setkey,
		.encrypt	= ctr_crypt,
		.decrypt	= ctr_crypt,
#पूर्ण_अगर
	पूर्ण, अणु
		.base = अणु
			.cra_name		= "__xts(aes)",
			.cra_driver_name	= "__xts-aes-aesni",
			.cra_priority		= 401,
			.cra_flags		= CRYPTO_ALG_INTERNAL,
			.cra_blocksize		= AES_BLOCK_SIZE,
			.cra_ctxsize		= XTS_AES_CTX_SIZE,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.min_keysize	= 2 * AES_MIN_KEY_SIZE,
		.max_keysize	= 2 * AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.walksize	= 2 * AES_BLOCK_SIZE,
		.setkey		= xts_aesni_setkey,
		.encrypt	= xts_encrypt,
		.decrypt	= xts_decrypt,
	पूर्ण
पूर्ण;

अटल
काष्ठा simd_skcipher_alg *aesni_simd_skciphers[ARRAY_SIZE(aesni_skciphers)];

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक generic_gcmaes_set_key(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा generic_gcmaes_ctx *ctx = generic_gcmaes_ctx_get(aead);

	वापस aes_set_key_common(crypto_aead_tfm(aead),
				  &ctx->aes_key_expanded, key, key_len) ?:
	       rfc4106_set_hash_subkey(ctx->hash_subkey, key, key_len);
पूर्ण

अटल पूर्णांक generic_gcmaes_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा generic_gcmaes_ctx *ctx = generic_gcmaes_ctx_get(tfm);
	व्योम *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_ALIGN - 8)] __aligned(8);
	u8 *iv = PTR_ALIGN(&ivbuf[0], AESNI_ALIGN);
	__be32 counter = cpu_to_be32(1);

	स_नकल(iv, req->iv, 12);
	*((__be32 *)(iv+12)) = counter;

	वापस gcmaes_encrypt(req, req->assoclen, ctx->hash_subkey, iv,
			      aes_ctx);
पूर्ण

अटल पूर्णांक generic_gcmaes_decrypt(काष्ठा aead_request *req)
अणु
	__be32 counter = cpu_to_be32(1);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा generic_gcmaes_ctx *ctx = generic_gcmaes_ctx_get(tfm);
	व्योम *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_ALIGN - 8)] __aligned(8);
	u8 *iv = PTR_ALIGN(&ivbuf[0], AESNI_ALIGN);

	स_नकल(iv, req->iv, 12);
	*((__be32 *)(iv+12)) = counter;

	वापस gcmaes_decrypt(req, req->assoclen, ctx->hash_subkey, iv,
			      aes_ctx);
पूर्ण

अटल काष्ठा aead_alg aesni_aeads[] = अणु अणु
	.setkey			= common_rfc4106_set_key,
	.setauthsize		= common_rfc4106_set_authsize,
	.encrypt		= helper_rfc4106_encrypt,
	.decrypt		= helper_rfc4106_decrypt,
	.ivsize			= GCM_RFC4106_IV_SIZE,
	.maxauthsize		= 16,
	.base = अणु
		.cra_name		= "__rfc4106(gcm(aes))",
		.cra_driver_name	= "__rfc4106-gcm-aesni",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा aesni_rfc4106_gcm_ctx),
		.cra_alignmask		= AESNI_ALIGN - 1,
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण, अणु
	.setkey			= generic_gcmaes_set_key,
	.setauthsize		= generic_gcmaes_set_authsize,
	.encrypt		= generic_gcmaes_encrypt,
	.decrypt		= generic_gcmaes_decrypt,
	.ivsize			= GCM_AES_IV_SIZE,
	.maxauthsize		= 16,
	.base = अणु
		.cra_name		= "__gcm(aes)",
		.cra_driver_name	= "__generic-gcm-aesni",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा generic_gcmaes_ctx),
		.cra_alignmask		= AESNI_ALIGN - 1,
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण पूर्ण;
#अन्यथा
अटल काष्ठा aead_alg aesni_aeads[0];
#पूर्ण_अगर

अटल काष्ठा simd_aead_alg *aesni_simd_aeads[ARRAY_SIZE(aesni_aeads)];

अटल स्थिर काष्ठा x86_cpu_id aesni_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_AES, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, aesni_cpu_id);

अटल पूर्णांक __init aesni_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!x86_match_cpu(aesni_cpu_id))
		वापस -ENODEV;
#अगर_घोषित CONFIG_X86_64
	अगर (boot_cpu_has(X86_FEATURE_AVX2)) अणु
		pr_info("AVX2 version of gcm_enc/dec engaged.\n");
		अटल_branch_enable(&gcm_use_avx);
		अटल_branch_enable(&gcm_use_avx2);
	पूर्ण अन्यथा
	अगर (boot_cpu_has(X86_FEATURE_AVX)) अणु
		pr_info("AVX version of gcm_enc/dec engaged.\n");
		अटल_branch_enable(&gcm_use_avx);
	पूर्ण अन्यथा अणु
		pr_info("SSE version of gcm_enc/dec engaged.\n");
	पूर्ण
	अगर (boot_cpu_has(X86_FEATURE_AVX)) अणु
		/* optimize perक्रमmance of ctr mode encryption transक्रमm */
		अटल_call_update(aesni_ctr_enc_tfm, aesni_ctr_enc_avx_tfm);
		pr_info("AES CTR mode by8 optimization enabled\n");
	पूर्ण
#पूर्ण_अगर

	err = crypto_रेजिस्टर_alg(&aesni_cipher_alg);
	अगर (err)
		वापस err;

	err = simd_रेजिस्टर_skciphers_compat(aesni_skciphers,
					     ARRAY_SIZE(aesni_skciphers),
					     aesni_simd_skciphers);
	अगर (err)
		जाओ unरेजिस्टर_cipher;

	err = simd_रेजिस्टर_aeads_compat(aesni_aeads, ARRAY_SIZE(aesni_aeads),
					 aesni_simd_aeads);
	अगर (err)
		जाओ unरेजिस्टर_skciphers;

	वापस 0;

unरेजिस्टर_skciphers:
	simd_unरेजिस्टर_skciphers(aesni_skciphers, ARRAY_SIZE(aesni_skciphers),
				  aesni_simd_skciphers);
unरेजिस्टर_cipher:
	crypto_unरेजिस्टर_alg(&aesni_cipher_alg);
	वापस err;
पूर्ण

अटल व्योम __निकास aesni_निकास(व्योम)
अणु
	simd_unरेजिस्टर_aeads(aesni_aeads, ARRAY_SIZE(aesni_aeads),
			      aesni_simd_aeads);
	simd_unरेजिस्टर_skciphers(aesni_skciphers, ARRAY_SIZE(aesni_skciphers),
				  aesni_simd_skciphers);
	crypto_unरेजिस्टर_alg(&aesni_cipher_alg);
पूर्ण

late_initcall(aesni_init);
module_निकास(aesni_निकास);

MODULE_DESCRIPTION("Rijndael (AES) Cipher Algorithm, Intel AES-NI instructions optimized");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("aes");
