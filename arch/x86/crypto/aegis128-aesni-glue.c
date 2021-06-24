<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The AEGIS-128 Authenticated-Encryption Algorithm
 *   Glue क्रम AES-NI + SSE2 implementation
 *
 * Copyright (c) 2017-2018 Ondrej Mosnacek <omosnacek@gmail.com>
 * Copyright (C) 2017-2018 Red Hat, Inc. All rights reserved.
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/cpu_device_id.h>

#घोषणा AEGIS128_BLOCK_ALIGN 16
#घोषणा AEGIS128_BLOCK_SIZE 16
#घोषणा AEGIS128_NONCE_SIZE 16
#घोषणा AEGIS128_STATE_BLOCKS 5
#घोषणा AEGIS128_KEY_SIZE 16
#घोषणा AEGIS128_MIN_AUTH_SIZE 8
#घोषणा AEGIS128_MAX_AUTH_SIZE 16

यंत्रlinkage व्योम crypto_aegis128_aesni_init(व्योम *state, व्योम *key, व्योम *iv);

यंत्रlinkage व्योम crypto_aegis128_aesni_ad(
		व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *data);

यंत्रlinkage व्योम crypto_aegis128_aesni_enc(
		व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *src, व्योम *dst);

यंत्रlinkage व्योम crypto_aegis128_aesni_dec(
		व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *src, व्योम *dst);

यंत्रlinkage व्योम crypto_aegis128_aesni_enc_tail(
		व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *src, व्योम *dst);

यंत्रlinkage व्योम crypto_aegis128_aesni_dec_tail(
		व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *src, व्योम *dst);

यंत्रlinkage व्योम crypto_aegis128_aesni_final(
		व्योम *state, व्योम *tag_xor, अचिन्हित पूर्णांक cryptlen,
		अचिन्हित पूर्णांक assoclen);

काष्ठा aegis_block अणु
	u8 bytes[AEGIS128_BLOCK_SIZE] __aligned(AEGIS128_BLOCK_ALIGN);
पूर्ण;

काष्ठा aegis_state अणु
	काष्ठा aegis_block blocks[AEGIS128_STATE_BLOCKS];
पूर्ण;

काष्ठा aegis_ctx अणु
	काष्ठा aegis_block key;
पूर्ण;

काष्ठा aegis_crypt_ops अणु
	पूर्णांक (*skcipher_walk_init)(काष्ठा skcipher_walk *walk,
				  काष्ठा aead_request *req, bool atomic);

	व्योम (*crypt_blocks)(व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *src,
			     व्योम *dst);
	व्योम (*crypt_tail)(व्योम *state, अचिन्हित पूर्णांक length, स्थिर व्योम *src,
			   व्योम *dst);
पूर्ण;

अटल व्योम crypto_aegis128_aesni_process_ad(
		काष्ठा aegis_state *state, काष्ठा scatterlist *sg_src,
		अचिन्हित पूर्णांक assoclen)
अणु
	काष्ठा scatter_walk walk;
	काष्ठा aegis_block buf;
	अचिन्हित पूर्णांक pos = 0;

	scatterwalk_start(&walk, sg_src);
	जबतक (assoclen != 0) अणु
		अचिन्हित पूर्णांक size = scatterwalk_clamp(&walk, assoclen);
		अचिन्हित पूर्णांक left = size;
		व्योम *mapped = scatterwalk_map(&walk);
		स्थिर u8 *src = (स्थिर u8 *)mapped;

		अगर (pos + size >= AEGIS128_BLOCK_SIZE) अणु
			अगर (pos > 0) अणु
				अचिन्हित पूर्णांक fill = AEGIS128_BLOCK_SIZE - pos;
				स_नकल(buf.bytes + pos, src, fill);
				crypto_aegis128_aesni_ad(state,
							 AEGIS128_BLOCK_SIZE,
							 buf.bytes);
				pos = 0;
				left -= fill;
				src += fill;
			पूर्ण

			crypto_aegis128_aesni_ad(state, left, src);

			src += left & ~(AEGIS128_BLOCK_SIZE - 1);
			left &= AEGIS128_BLOCK_SIZE - 1;
		पूर्ण

		स_नकल(buf.bytes + pos, src, left);
		pos += left;
		assoclen -= size;

		scatterwalk_unmap(mapped);
		scatterwalk_advance(&walk, size);
		scatterwalk_करोne(&walk, 0, assoclen);
	पूर्ण

	अगर (pos > 0) अणु
		स_रखो(buf.bytes + pos, 0, AEGIS128_BLOCK_SIZE - pos);
		crypto_aegis128_aesni_ad(state, AEGIS128_BLOCK_SIZE, buf.bytes);
	पूर्ण
पूर्ण

अटल व्योम crypto_aegis128_aesni_process_crypt(
		काष्ठा aegis_state *state, काष्ठा skcipher_walk *walk,
		स्थिर काष्ठा aegis_crypt_ops *ops)
अणु
	जबतक (walk->nbytes >= AEGIS128_BLOCK_SIZE) अणु
		ops->crypt_blocks(state,
				  round_करोwn(walk->nbytes, AEGIS128_BLOCK_SIZE),
				  walk->src.virt.addr, walk->dst.virt.addr);
		skcipher_walk_करोne(walk, walk->nbytes % AEGIS128_BLOCK_SIZE);
	पूर्ण

	अगर (walk->nbytes) अणु
		ops->crypt_tail(state, walk->nbytes, walk->src.virt.addr,
				walk->dst.virt.addr);
		skcipher_walk_करोne(walk, 0);
	पूर्ण
पूर्ण

अटल काष्ठा aegis_ctx *crypto_aegis128_aesni_ctx(काष्ठा crypto_aead *aead)
अणु
	u8 *ctx = crypto_aead_ctx(aead);
	ctx = PTR_ALIGN(ctx, __alignof__(काष्ठा aegis_ctx));
	वापस (व्योम *)ctx;
पूर्ण

अटल पूर्णांक crypto_aegis128_aesni_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
					अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aegis_ctx *ctx = crypto_aegis128_aesni_ctx(aead);

	अगर (keylen != AEGIS128_KEY_SIZE)
		वापस -EINVAL;

	स_नकल(ctx->key.bytes, key, AEGIS128_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_aesni_setauthsize(काष्ठा crypto_aead *tfm,
						अचिन्हित पूर्णांक authsize)
अणु
	अगर (authsize > AEGIS128_MAX_AUTH_SIZE)
		वापस -EINVAL;
	अगर (authsize < AEGIS128_MIN_AUTH_SIZE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम crypto_aegis128_aesni_crypt(काष्ठा aead_request *req,
					काष्ठा aegis_block *tag_xor,
					अचिन्हित पूर्णांक cryptlen,
					स्थिर काष्ठा aegis_crypt_ops *ops)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aegis_ctx *ctx = crypto_aegis128_aesni_ctx(tfm);
	काष्ठा skcipher_walk walk;
	काष्ठा aegis_state state;

	ops->skcipher_walk_init(&walk, req, true);

	kernel_fpu_begin();

	crypto_aegis128_aesni_init(&state, ctx->key.bytes, req->iv);
	crypto_aegis128_aesni_process_ad(&state, req->src, req->assoclen);
	crypto_aegis128_aesni_process_crypt(&state, &walk, ops);
	crypto_aegis128_aesni_final(&state, tag_xor, req->assoclen, cryptlen);

	kernel_fpu_end();
पूर्ण

अटल पूर्णांक crypto_aegis128_aesni_encrypt(काष्ठा aead_request *req)
अणु
	अटल स्थिर काष्ठा aegis_crypt_ops OPS = अणु
		.skcipher_walk_init = skcipher_walk_aead_encrypt,
		.crypt_blocks = crypto_aegis128_aesni_enc,
		.crypt_tail = crypto_aegis128_aesni_enc_tail,
	पूर्ण;

	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aegis_block tag = अणुपूर्ण;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;

	crypto_aegis128_aesni_crypt(req, &tag, cryptlen, &OPS);

	scatterwalk_map_and_copy(tag.bytes, req->dst,
				 req->assoclen + cryptlen, authsize, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_aesni_decrypt(काष्ठा aead_request *req)
अणु
	अटल स्थिर काष्ठा aegis_block zeros = अणुपूर्ण;

	अटल स्थिर काष्ठा aegis_crypt_ops OPS = अणु
		.skcipher_walk_init = skcipher_walk_aead_decrypt,
		.crypt_blocks = crypto_aegis128_aesni_dec,
		.crypt_tail = crypto_aegis128_aesni_dec_tail,
	पूर्ण;

	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aegis_block tag;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen - authsize;

	scatterwalk_map_and_copy(tag.bytes, req->src,
				 req->assoclen + cryptlen, authsize, 0);

	crypto_aegis128_aesni_crypt(req, &tag, cryptlen, &OPS);

	वापस crypto_memneq(tag.bytes, zeros.bytes, authsize) ? -EBADMSG : 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_aesni_init_tfm(काष्ठा crypto_aead *aead)
अणु
	वापस 0;
पूर्ण

अटल व्योम crypto_aegis128_aesni_निकास_tfm(काष्ठा crypto_aead *aead)
अणु
पूर्ण

अटल काष्ठा aead_alg crypto_aegis128_aesni_alg = अणु
	.setkey = crypto_aegis128_aesni_setkey,
	.setauthsize = crypto_aegis128_aesni_setauthsize,
	.encrypt = crypto_aegis128_aesni_encrypt,
	.decrypt = crypto_aegis128_aesni_decrypt,
	.init = crypto_aegis128_aesni_init_tfm,
	.निकास = crypto_aegis128_aesni_निकास_tfm,

	.ivsize = AEGIS128_NONCE_SIZE,
	.maxauthsize = AEGIS128_MAX_AUTH_SIZE,
	.chunksize = AEGIS128_BLOCK_SIZE,

	.base = अणु
		.cra_flags = CRYPTO_ALG_INTERNAL,
		.cra_blocksize = 1,
		.cra_ctxsize = माप(काष्ठा aegis_ctx) +
			       __alignof__(काष्ठा aegis_ctx),
		.cra_alignmask = 0,
		.cra_priority = 400,

		.cra_name = "__aegis128",
		.cra_driver_name = "__aegis128-aesni",

		.cra_module = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा simd_aead_alg *simd_alg;

अटल पूर्णांक __init crypto_aegis128_aesni_module_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_XMM2) ||
	    !boot_cpu_has(X86_FEATURE_AES) ||
	    !cpu_has_xfeatures(XFEATURE_MASK_SSE, शून्य))
		वापस -ENODEV;

	वापस simd_रेजिस्टर_aeads_compat(&crypto_aegis128_aesni_alg, 1,
					  &simd_alg);
पूर्ण

अटल व्योम __निकास crypto_aegis128_aesni_module_निकास(व्योम)
अणु
	simd_unरेजिस्टर_aeads(&crypto_aegis128_aesni_alg, 1, &simd_alg);
पूर्ण

module_init(crypto_aegis128_aesni_module_init);
module_निकास(crypto_aegis128_aesni_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ondrej Mosnacek <omosnacek@gmail.com>");
MODULE_DESCRIPTION("AEGIS-128 AEAD algorithm -- AESNI+SSE2 implementation");
MODULE_ALIAS_CRYPTO("aegis128");
MODULE_ALIAS_CRYPTO("aegis128-aesni");
