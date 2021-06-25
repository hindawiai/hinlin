<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The AEGIS-128 Authenticated-Encryption Algorithm
 *
 * Copyright (c) 2017-2018 Ondrej Mosnacek <omosnacek@gmail.com>
 * Copyright (C) 2017-2018 Red Hat, Inc. All rights reserved.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/simd.h>

#समावेश "aegis.h"

#घोषणा AEGIS128_NONCE_SIZE 16
#घोषणा AEGIS128_STATE_BLOCKS 5
#घोषणा AEGIS128_KEY_SIZE 16
#घोषणा AEGIS128_MIN_AUTH_SIZE 8
#घोषणा AEGIS128_MAX_AUTH_SIZE 16

काष्ठा aegis_state अणु
	जोड़ aegis_block blocks[AEGIS128_STATE_BLOCKS];
पूर्ण;

काष्ठा aegis_ctx अणु
	जोड़ aegis_block key;
पूर्ण;

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(have_simd);

अटल स्थिर जोड़ aegis_block crypto_aegis_स्थिर[2] = अणु
	अणु .words64 = अणु
		cpu_to_le64(U64_C(0x0d08050302010100)),
		cpu_to_le64(U64_C(0x6279e99059372215)),
	पूर्ण पूर्ण,
	अणु .words64 = अणु
		cpu_to_le64(U64_C(0xf12fc26d55183ddb)),
		cpu_to_le64(U64_C(0xdd28b57342311120)),
	पूर्ण पूर्ण,
पूर्ण;

अटल bool aegis128_करो_simd(व्योम)
अणु
#अगर_घोषित CONFIG_CRYPTO_AEGIS128_SIMD
	अगर (अटल_branch_likely(&have_simd))
		वापस crypto_simd_usable();
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल व्योम crypto_aegis128_update(काष्ठा aegis_state *state)
अणु
	जोड़ aegis_block पंचांगp;
	अचिन्हित पूर्णांक i;

	पंचांगp = state->blocks[AEGIS128_STATE_BLOCKS - 1];
	क्रम (i = AEGIS128_STATE_BLOCKS - 1; i > 0; i--)
		crypto_aegis_aesenc(&state->blocks[i], &state->blocks[i - 1],
				    &state->blocks[i]);
	crypto_aegis_aesenc(&state->blocks[0], &पंचांगp, &state->blocks[0]);
पूर्ण

अटल व्योम crypto_aegis128_update_a(काष्ठा aegis_state *state,
				     स्थिर जोड़ aegis_block *msg,
				     bool करो_simd)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_AEGIS128_SIMD) && करो_simd) अणु
		crypto_aegis128_update_simd(state, msg);
		वापस;
	पूर्ण

	crypto_aegis128_update(state);
	crypto_aegis_block_xor(&state->blocks[0], msg);
पूर्ण

अटल व्योम crypto_aegis128_update_u(काष्ठा aegis_state *state, स्थिर व्योम *msg,
				     bool करो_simd)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_AEGIS128_SIMD) && करो_simd) अणु
		crypto_aegis128_update_simd(state, msg);
		वापस;
	पूर्ण

	crypto_aegis128_update(state);
	crypto_xor(state->blocks[0].bytes, msg, AEGIS_BLOCK_SIZE);
पूर्ण

अटल व्योम crypto_aegis128_init(काष्ठा aegis_state *state,
				 स्थिर जोड़ aegis_block *key,
				 स्थिर u8 *iv)
अणु
	जोड़ aegis_block key_iv;
	अचिन्हित पूर्णांक i;

	key_iv = *key;
	crypto_xor(key_iv.bytes, iv, AEGIS_BLOCK_SIZE);

	state->blocks[0] = key_iv;
	state->blocks[1] = crypto_aegis_स्थिर[1];
	state->blocks[2] = crypto_aegis_स्थिर[0];
	state->blocks[3] = *key;
	state->blocks[4] = *key;

	crypto_aegis_block_xor(&state->blocks[3], &crypto_aegis_स्थिर[0]);
	crypto_aegis_block_xor(&state->blocks[4], &crypto_aegis_स्थिर[1]);

	क्रम (i = 0; i < 5; i++) अणु
		crypto_aegis128_update_a(state, key, false);
		crypto_aegis128_update_a(state, &key_iv, false);
	पूर्ण
पूर्ण

अटल व्योम crypto_aegis128_ad(काष्ठा aegis_state *state,
			       स्थिर u8 *src, अचिन्हित पूर्णांक size,
			       bool करो_simd)
अणु
	अगर (AEGIS_ALIGNED(src)) अणु
		स्थिर जोड़ aegis_block *src_blk =
				(स्थिर जोड़ aegis_block *)src;

		जबतक (size >= AEGIS_BLOCK_SIZE) अणु
			crypto_aegis128_update_a(state, src_blk, करो_simd);

			size -= AEGIS_BLOCK_SIZE;
			src_blk++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (size >= AEGIS_BLOCK_SIZE) अणु
			crypto_aegis128_update_u(state, src, करो_simd);

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम crypto_aegis128_wipe_chunk(काष्ठा aegis_state *state, u8 *dst,
				       स्थिर u8 *src, अचिन्हित पूर्णांक size)
अणु
	memzero_explicit(dst, size);
पूर्ण

अटल व्योम crypto_aegis128_encrypt_chunk(काष्ठा aegis_state *state, u8 *dst,
					  स्थिर u8 *src, अचिन्हित पूर्णांक size)
अणु
	जोड़ aegis_block पंचांगp;

	अगर (AEGIS_ALIGNED(src) && AEGIS_ALIGNED(dst)) अणु
		जबतक (size >= AEGIS_BLOCK_SIZE) अणु
			जोड़ aegis_block *dst_blk =
					(जोड़ aegis_block *)dst;
			स्थिर जोड़ aegis_block *src_blk =
					(स्थिर जोड़ aegis_block *)src;

			पंचांगp = state->blocks[2];
			crypto_aegis_block_and(&पंचांगp, &state->blocks[3]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[4]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[1]);
			crypto_aegis_block_xor(&पंचांगp, src_blk);

			crypto_aegis128_update_a(state, src_blk, false);

			*dst_blk = पंचांगp;

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
			dst += AEGIS_BLOCK_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (size >= AEGIS_BLOCK_SIZE) अणु
			पंचांगp = state->blocks[2];
			crypto_aegis_block_and(&पंचांगp, &state->blocks[3]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[4]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[1]);
			crypto_xor(पंचांगp.bytes, src, AEGIS_BLOCK_SIZE);

			crypto_aegis128_update_u(state, src, false);

			स_नकल(dst, पंचांगp.bytes, AEGIS_BLOCK_SIZE);

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
			dst += AEGIS_BLOCK_SIZE;
		पूर्ण
	पूर्ण

	अगर (size > 0) अणु
		जोड़ aegis_block msg = अणुपूर्ण;
		स_नकल(msg.bytes, src, size);

		पंचांगp = state->blocks[2];
		crypto_aegis_block_and(&पंचांगp, &state->blocks[3]);
		crypto_aegis_block_xor(&पंचांगp, &state->blocks[4]);
		crypto_aegis_block_xor(&पंचांगp, &state->blocks[1]);

		crypto_aegis128_update_a(state, &msg, false);

		crypto_aegis_block_xor(&msg, &पंचांगp);

		स_नकल(dst, msg.bytes, size);
	पूर्ण
पूर्ण

अटल व्योम crypto_aegis128_decrypt_chunk(काष्ठा aegis_state *state, u8 *dst,
					  स्थिर u8 *src, अचिन्हित पूर्णांक size)
अणु
	जोड़ aegis_block पंचांगp;

	अगर (AEGIS_ALIGNED(src) && AEGIS_ALIGNED(dst)) अणु
		जबतक (size >= AEGIS_BLOCK_SIZE) अणु
			जोड़ aegis_block *dst_blk =
					(जोड़ aegis_block *)dst;
			स्थिर जोड़ aegis_block *src_blk =
					(स्थिर जोड़ aegis_block *)src;

			पंचांगp = state->blocks[2];
			crypto_aegis_block_and(&पंचांगp, &state->blocks[3]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[4]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[1]);
			crypto_aegis_block_xor(&पंचांगp, src_blk);

			crypto_aegis128_update_a(state, &पंचांगp, false);

			*dst_blk = पंचांगp;

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
			dst += AEGIS_BLOCK_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (size >= AEGIS_BLOCK_SIZE) अणु
			पंचांगp = state->blocks[2];
			crypto_aegis_block_and(&पंचांगp, &state->blocks[3]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[4]);
			crypto_aegis_block_xor(&पंचांगp, &state->blocks[1]);
			crypto_xor(पंचांगp.bytes, src, AEGIS_BLOCK_SIZE);

			crypto_aegis128_update_a(state, &पंचांगp, false);

			स_नकल(dst, पंचांगp.bytes, AEGIS_BLOCK_SIZE);

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
			dst += AEGIS_BLOCK_SIZE;
		पूर्ण
	पूर्ण

	अगर (size > 0) अणु
		जोड़ aegis_block msg = अणुपूर्ण;
		स_नकल(msg.bytes, src, size);

		पंचांगp = state->blocks[2];
		crypto_aegis_block_and(&पंचांगp, &state->blocks[3]);
		crypto_aegis_block_xor(&पंचांगp, &state->blocks[4]);
		crypto_aegis_block_xor(&पंचांगp, &state->blocks[1]);
		crypto_aegis_block_xor(&msg, &पंचांगp);

		स_रखो(msg.bytes + size, 0, AEGIS_BLOCK_SIZE - size);

		crypto_aegis128_update_a(state, &msg, false);

		स_नकल(dst, msg.bytes, size);
	पूर्ण
पूर्ण

अटल व्योम crypto_aegis128_process_ad(काष्ठा aegis_state *state,
				       काष्ठा scatterlist *sg_src,
				       अचिन्हित पूर्णांक assoclen,
				       bool करो_simd)
अणु
	काष्ठा scatter_walk walk;
	जोड़ aegis_block buf;
	अचिन्हित पूर्णांक pos = 0;

	scatterwalk_start(&walk, sg_src);
	जबतक (assoclen != 0) अणु
		अचिन्हित पूर्णांक size = scatterwalk_clamp(&walk, assoclen);
		अचिन्हित पूर्णांक left = size;
		व्योम *mapped = scatterwalk_map(&walk);
		स्थिर u8 *src = (स्थिर u8 *)mapped;

		अगर (pos + size >= AEGIS_BLOCK_SIZE) अणु
			अगर (pos > 0) अणु
				अचिन्हित पूर्णांक fill = AEGIS_BLOCK_SIZE - pos;
				स_नकल(buf.bytes + pos, src, fill);
				crypto_aegis128_update_a(state, &buf, करो_simd);
				pos = 0;
				left -= fill;
				src += fill;
			पूर्ण

			crypto_aegis128_ad(state, src, left, करो_simd);
			src += left & ~(AEGIS_BLOCK_SIZE - 1);
			left &= AEGIS_BLOCK_SIZE - 1;
		पूर्ण

		स_नकल(buf.bytes + pos, src, left);

		pos += left;
		assoclen -= size;
		scatterwalk_unmap(mapped);
		scatterwalk_advance(&walk, size);
		scatterwalk_करोne(&walk, 0, assoclen);
	पूर्ण

	अगर (pos > 0) अणु
		स_रखो(buf.bytes + pos, 0, AEGIS_BLOCK_SIZE - pos);
		crypto_aegis128_update_a(state, &buf, करो_simd);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत
पूर्णांक crypto_aegis128_process_crypt(काष्ठा aegis_state *state,
				  काष्ठा skcipher_walk *walk,
				  व्योम (*crypt)(काष्ठा aegis_state *state,
					        u8 *dst, स्थिर u8 *src,
					        अचिन्हित पूर्णांक size))
अणु
	पूर्णांक err = 0;

	जबतक (walk->nbytes) अणु
		अचिन्हित पूर्णांक nbytes = walk->nbytes;

		अगर (nbytes < walk->total)
			nbytes = round_करोwn(nbytes, walk->stride);

		crypt(state, walk->dst.virt.addr, walk->src.virt.addr, nbytes);

		err = skcipher_walk_करोne(walk, walk->nbytes - nbytes);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम crypto_aegis128_final(काष्ठा aegis_state *state,
				  जोड़ aegis_block *tag_xor,
				  u64 assoclen, u64 cryptlen)
अणु
	u64 assocbits = assoclen * 8;
	u64 cryptbits = cryptlen * 8;

	जोड़ aegis_block पंचांगp;
	अचिन्हित पूर्णांक i;

	पंचांगp.words64[0] = cpu_to_le64(assocbits);
	पंचांगp.words64[1] = cpu_to_le64(cryptbits);

	crypto_aegis_block_xor(&पंचांगp, &state->blocks[3]);

	क्रम (i = 0; i < 7; i++)
		crypto_aegis128_update_a(state, &पंचांगp, false);

	क्रम (i = 0; i < AEGIS128_STATE_BLOCKS; i++)
		crypto_aegis_block_xor(tag_xor, &state->blocks[i]);
पूर्ण

अटल पूर्णांक crypto_aegis128_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aegis_ctx *ctx = crypto_aead_ctx(aead);

	अगर (keylen != AEGIS128_KEY_SIZE)
		वापस -EINVAL;

	स_नकल(ctx->key.bytes, key, AEGIS128_KEY_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_setauthsize(काष्ठा crypto_aead *tfm,
				       अचिन्हित पूर्णांक authsize)
अणु
	अगर (authsize > AEGIS128_MAX_AUTH_SIZE)
		वापस -EINVAL;
	अगर (authsize < AEGIS128_MIN_AUTH_SIZE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_encrypt_generic(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	जोड़ aegis_block tag = अणुपूर्ण;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	काष्ठा aegis_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	काष्ठा skcipher_walk walk;
	काष्ठा aegis_state state;

	skcipher_walk_aead_encrypt(&walk, req, false);
	crypto_aegis128_init(&state, &ctx->key, req->iv);
	crypto_aegis128_process_ad(&state, req->src, req->assoclen, false);
	crypto_aegis128_process_crypt(&state, &walk,
				      crypto_aegis128_encrypt_chunk);
	crypto_aegis128_final(&state, &tag, req->assoclen, cryptlen);

	scatterwalk_map_and_copy(tag.bytes, req->dst, req->assoclen + cryptlen,
				 authsize, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_decrypt_generic(काष्ठा aead_request *req)
अणु
	अटल स्थिर u8 zeros[AEGIS128_MAX_AUTH_SIZE] = अणुपूर्ण;
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	जोड़ aegis_block tag;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen - authsize;
	काष्ठा aegis_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा skcipher_walk walk;
	काष्ठा aegis_state state;

	scatterwalk_map_and_copy(tag.bytes, req->src, req->assoclen + cryptlen,
				 authsize, 0);

	skcipher_walk_aead_decrypt(&walk, req, false);
	crypto_aegis128_init(&state, &ctx->key, req->iv);
	crypto_aegis128_process_ad(&state, req->src, req->assoclen, false);
	crypto_aegis128_process_crypt(&state, &walk,
				      crypto_aegis128_decrypt_chunk);
	crypto_aegis128_final(&state, &tag, req->assoclen, cryptlen);

	अगर (unlikely(crypto_memneq(tag.bytes, zeros, authsize))) अणु
		/*
		 * From Chapter 4. 'Security Analysis' of the AEGIS spec [0]
		 *
		 * "3. If verअगरication fails, the decrypted plaपूर्णांकext and the
		 *     wrong authentication tag should not be given as output."
		 *
		 * [0] https://competitions.cr.yp.to/round3/aegisv11.pdf
		 */
		skcipher_walk_aead_decrypt(&walk, req, false);
		crypto_aegis128_process_crypt(शून्य, &walk,
					      crypto_aegis128_wipe_chunk);
		memzero_explicit(&tag, माप(tag));
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_encrypt_simd(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	जोड़ aegis_block tag = अणुपूर्ण;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	काष्ठा aegis_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	काष्ठा skcipher_walk walk;
	काष्ठा aegis_state state;

	अगर (!aegis128_करो_simd())
		वापस crypto_aegis128_encrypt_generic(req);

	skcipher_walk_aead_encrypt(&walk, req, false);
	crypto_aegis128_init_simd(&state, &ctx->key, req->iv);
	crypto_aegis128_process_ad(&state, req->src, req->assoclen, true);
	crypto_aegis128_process_crypt(&state, &walk,
				      crypto_aegis128_encrypt_chunk_simd);
	crypto_aegis128_final_simd(&state, &tag, req->assoclen, cryptlen, 0);

	scatterwalk_map_and_copy(tag.bytes, req->dst, req->assoclen + cryptlen,
				 authsize, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_aegis128_decrypt_simd(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	जोड़ aegis_block tag;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen - authsize;
	काष्ठा aegis_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा skcipher_walk walk;
	काष्ठा aegis_state state;

	अगर (!aegis128_करो_simd())
		वापस crypto_aegis128_decrypt_generic(req);

	scatterwalk_map_and_copy(tag.bytes, req->src, req->assoclen + cryptlen,
				 authsize, 0);

	skcipher_walk_aead_decrypt(&walk, req, false);
	crypto_aegis128_init_simd(&state, &ctx->key, req->iv);
	crypto_aegis128_process_ad(&state, req->src, req->assoclen, true);
	crypto_aegis128_process_crypt(&state, &walk,
				      crypto_aegis128_decrypt_chunk_simd);

	अगर (unlikely(crypto_aegis128_final_simd(&state, &tag, req->assoclen,
						cryptlen, authsize))) अणु
		skcipher_walk_aead_decrypt(&walk, req, false);
		crypto_aegis128_process_crypt(शून्य, &walk,
					      crypto_aegis128_wipe_chunk);
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा aead_alg crypto_aegis128_alg_generic = अणु
	.setkey			= crypto_aegis128_setkey,
	.setauthsize		= crypto_aegis128_setauthsize,
	.encrypt		= crypto_aegis128_encrypt_generic,
	.decrypt		= crypto_aegis128_decrypt_generic,

	.ivsize			= AEGIS128_NONCE_SIZE,
	.maxauthsize		= AEGIS128_MAX_AUTH_SIZE,
	.chunksize		= AEGIS_BLOCK_SIZE,

	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा aegis_ctx),
	.base.cra_alignmask	= 0,
	.base.cra_priority	= 100,
	.base.cra_name		= "aegis128",
	.base.cra_driver_name	= "aegis128-generic",
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल काष्ठा aead_alg crypto_aegis128_alg_simd = अणु
	.setkey			= crypto_aegis128_setkey,
	.setauthsize		= crypto_aegis128_setauthsize,
	.encrypt		= crypto_aegis128_encrypt_simd,
	.decrypt		= crypto_aegis128_decrypt_simd,

	.ivsize			= AEGIS128_NONCE_SIZE,
	.maxauthsize		= AEGIS128_MAX_AUTH_SIZE,
	.chunksize		= AEGIS_BLOCK_SIZE,

	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा aegis_ctx),
	.base.cra_alignmask	= 0,
	.base.cra_priority	= 200,
	.base.cra_name		= "aegis128",
	.base.cra_driver_name	= "aegis128-simd",
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_aegis128_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_aead(&crypto_aegis128_alg_generic);
	अगर (ret)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_CRYPTO_AEGIS128_SIMD) &&
	    crypto_aegis128_have_simd()) अणु
		ret = crypto_रेजिस्टर_aead(&crypto_aegis128_alg_simd);
		अगर (ret) अणु
			crypto_unरेजिस्टर_aead(&crypto_aegis128_alg_generic);
			वापस ret;
		पूर्ण
		अटल_branch_enable(&have_simd);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास crypto_aegis128_module_निकास(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_AEGIS128_SIMD) &&
	    crypto_aegis128_have_simd())
		crypto_unरेजिस्टर_aead(&crypto_aegis128_alg_simd);

	crypto_unरेजिस्टर_aead(&crypto_aegis128_alg_generic);
पूर्ण

subsys_initcall(crypto_aegis128_module_init);
module_निकास(crypto_aegis128_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ondrej Mosnacek <omosnacek@gmail.com>");
MODULE_DESCRIPTION("AEGIS-128 AEAD algorithm");
MODULE_ALIAS_CRYPTO("aegis128");
MODULE_ALIAS_CRYPTO("aegis128-generic");
MODULE_ALIAS_CRYPTO("aegis128-simd");
