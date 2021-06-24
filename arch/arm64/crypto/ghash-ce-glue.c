<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Accelerated GHASH implementation with ARMv8 PMULL inकाष्ठाions.
 *
 * Copyright (C) 2014 - 2018 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/b128ops.h>
#समावेश <crypto/gf128mul.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("GHASH and AES-GCM using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("ghash");

#घोषणा GHASH_BLOCK_SIZE	16
#घोषणा GHASH_DIGEST_SIZE	16
#घोषणा GCM_IV_SIZE		12

काष्ठा ghash_key अणु
	be128			k;
	u64			h[][2];
पूर्ण;

काष्ठा ghash_desc_ctx अणु
	u64 digest[GHASH_DIGEST_SIZE/माप(u64)];
	u8 buf[GHASH_BLOCK_SIZE];
	u32 count;
पूर्ण;

काष्ठा gcm_aes_ctx अणु
	काष्ठा crypto_aes_ctx	aes_key;
	काष्ठा ghash_key	ghash_key;
पूर्ण;

यंत्रlinkage व्योम pmull_ghash_update_p64(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
				       u64 स्थिर h[][2], स्थिर अक्षर *head);

यंत्रlinkage व्योम pmull_ghash_update_p8(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
				      u64 स्थिर h[][2], स्थिर अक्षर *head);

यंत्रlinkage व्योम pmull_gcm_encrypt(पूर्णांक bytes, u8 dst[], स्थिर u8 src[],
				  u64 स्थिर h[][2], u64 dg[], u8 ctr[],
				  u32 स्थिर rk[], पूर्णांक rounds, u8 tag[]);
यंत्रlinkage पूर्णांक pmull_gcm_decrypt(पूर्णांक bytes, u8 dst[], स्थिर u8 src[],
				 u64 स्थिर h[][2], u64 dg[], u8 ctr[],
				 u32 स्थिर rk[], पूर्णांक rounds, स्थिर u8 l[],
				 स्थिर u8 tag[], u64 authsize);

अटल पूर्णांक ghash_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा ghash_desc_ctx *ctx = shash_desc_ctx(desc);

	*ctx = (काष्ठा ghash_desc_ctx)अणुपूर्ण;
	वापस 0;
पूर्ण

अटल व्योम ghash_करो_update(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
			    काष्ठा ghash_key *key, स्थिर अक्षर *head)
अणु
	be128 dst = अणु cpu_to_be64(dg[1]), cpu_to_be64(dg[0]) पूर्ण;

	करो अणु
		स्थिर u8 *in = src;

		अगर (head) अणु
			in = head;
			blocks++;
			head = शून्य;
		पूर्ण अन्यथा अणु
			src += GHASH_BLOCK_SIZE;
		पूर्ण

		crypto_xor((u8 *)&dst, in, GHASH_BLOCK_SIZE);
		gf128mul_lle(&dst, &key->k);
	पूर्ण जबतक (--blocks);

	dg[0] = be64_to_cpu(dst.b);
	dg[1] = be64_to_cpu(dst.a);
पूर्ण

अटल __always_अंतरभूत
व्योम ghash_करो_simd_update(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
			  काष्ठा ghash_key *key, स्थिर अक्षर *head,
			  व्योम (*simd_update)(पूर्णांक blocks, u64 dg[],
					      स्थिर अक्षर *src,
					      u64 स्थिर h[][2],
					      स्थिर अक्षर *head))
अणु
	अगर (likely(crypto_simd_usable())) अणु
		kernel_neon_begin();
		simd_update(blocks, dg, src, key->h, head);
		kernel_neon_end();
	पूर्ण अन्यथा अणु
		ghash_करो_update(blocks, dg, src, key, head);
	पूर्ण
पूर्ण

/* aव्योम hogging the CPU क्रम too दीर्घ */
#घोषणा MAX_BLOCKS	(SZ_64K / GHASH_BLOCK_SIZE)

अटल पूर्णांक ghash_update(काष्ठा shash_desc *desc, स्थिर u8 *src,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा ghash_desc_ctx *ctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = ctx->count % GHASH_BLOCK_SIZE;

	ctx->count += len;

	अगर ((partial + len) >= GHASH_BLOCK_SIZE) अणु
		काष्ठा ghash_key *key = crypto_shash_ctx(desc->tfm);
		पूर्णांक blocks;

		अगर (partial) अणु
			पूर्णांक p = GHASH_BLOCK_SIZE - partial;

			स_नकल(ctx->buf + partial, src, p);
			src += p;
			len -= p;
		पूर्ण

		blocks = len / GHASH_BLOCK_SIZE;
		len %= GHASH_BLOCK_SIZE;

		करो अणु
			पूर्णांक chunk = min(blocks, MAX_BLOCKS);

			ghash_करो_simd_update(chunk, ctx->digest, src, key,
					     partial ? ctx->buf : शून्य,
					     pmull_ghash_update_p8);

			blocks -= chunk;
			src += chunk * GHASH_BLOCK_SIZE;
			partial = 0;
		पूर्ण जबतक (unlikely(blocks > 0));
	पूर्ण
	अगर (len)
		स_नकल(ctx->buf + partial, src, len);
	वापस 0;
पूर्ण

अटल पूर्णांक ghash_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा ghash_desc_ctx *ctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = ctx->count % GHASH_BLOCK_SIZE;

	अगर (partial) अणु
		काष्ठा ghash_key *key = crypto_shash_ctx(desc->tfm);

		स_रखो(ctx->buf + partial, 0, GHASH_BLOCK_SIZE - partial);

		ghash_करो_simd_update(1, ctx->digest, ctx->buf, key, शून्य,
				     pmull_ghash_update_p8);
	पूर्ण
	put_unaligned_be64(ctx->digest[1], dst);
	put_unaligned_be64(ctx->digest[0], dst + 8);

	memzero_explicit(ctx, माप(*ctx));
	वापस 0;
पूर्ण

अटल व्योम ghash_reflect(u64 h[], स्थिर be128 *k)
अणु
	u64 carry = be64_to_cpu(k->a) & BIT(63) ? 1 : 0;

	h[0] = (be64_to_cpu(k->b) << 1) | carry;
	h[1] = (be64_to_cpu(k->a) << 1) | (be64_to_cpu(k->b) >> 63);

	अगर (carry)
		h[1] ^= 0xc200000000000000UL;
पूर्ण

अटल पूर्णांक ghash_setkey(काष्ठा crypto_shash *tfm,
			स्थिर u8 *inkey, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ghash_key *key = crypto_shash_ctx(tfm);

	अगर (keylen != GHASH_BLOCK_SIZE)
		वापस -EINVAL;

	/* needed क्रम the fallback */
	स_नकल(&key->k, inkey, GHASH_BLOCK_SIZE);

	ghash_reflect(key->h[0], &key->k);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg ghash_alg = अणु
	.base.cra_name		= "ghash",
	.base.cra_driver_name	= "ghash-neon",
	.base.cra_priority	= 150,
	.base.cra_blocksize	= GHASH_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा ghash_key) + माप(u64[2]),
	.base.cra_module	= THIS_MODULE,

	.digestsize		= GHASH_DIGEST_SIZE,
	.init			= ghash_init,
	.update			= ghash_update,
	.final			= ghash_final,
	.setkey			= ghash_setkey,
	.descsize		= माप(काष्ठा ghash_desc_ctx),
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

अटल पूर्णांक gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *inkey,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा gcm_aes_ctx *ctx = crypto_aead_ctx(tfm);
	u8 key[GHASH_BLOCK_SIZE];
	be128 h;
	पूर्णांक ret;

	ret = aes_expandkey(&ctx->aes_key, inkey, keylen);
	अगर (ret)
		वापस -EINVAL;

	aes_encrypt(&ctx->aes_key, key, (u8[AES_BLOCK_SIZE])अणुपूर्ण);

	/* needed क्रम the fallback */
	स_नकल(&ctx->ghash_key.k, key, GHASH_BLOCK_SIZE);

	ghash_reflect(ctx->ghash_key.h[0], &ctx->ghash_key.k);

	h = ctx->ghash_key.k;
	gf128mul_lle(&h, &ctx->ghash_key.k);
	ghash_reflect(ctx->ghash_key.h[1], &h);

	gf128mul_lle(&h, &ctx->ghash_key.k);
	ghash_reflect(ctx->ghash_key.h[2], &h);

	gf128mul_lle(&h, &ctx->ghash_key.k);
	ghash_reflect(ctx->ghash_key.h[3], &h);

	वापस 0;
पूर्ण

अटल पूर्णांक gcm_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 8:
	हाल 12 ... 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gcm_update_mac(u64 dg[], स्थिर u8 *src, पूर्णांक count, u8 buf[],
			   पूर्णांक *buf_count, काष्ठा gcm_aes_ctx *ctx)
अणु
	अगर (*buf_count > 0) अणु
		पूर्णांक buf_added = min(count, GHASH_BLOCK_SIZE - *buf_count);

		स_नकल(&buf[*buf_count], src, buf_added);

		*buf_count += buf_added;
		src += buf_added;
		count -= buf_added;
	पूर्ण

	अगर (count >= GHASH_BLOCK_SIZE || *buf_count == GHASH_BLOCK_SIZE) अणु
		पूर्णांक blocks = count / GHASH_BLOCK_SIZE;

		ghash_करो_simd_update(blocks, dg, src, &ctx->ghash_key,
				     *buf_count ? buf : शून्य,
				     pmull_ghash_update_p64);

		src += blocks * GHASH_BLOCK_SIZE;
		count %= GHASH_BLOCK_SIZE;
		*buf_count = 0;
	पूर्ण

	अगर (count > 0) अणु
		स_नकल(buf, src, count);
		*buf_count = count;
	पूर्ण
पूर्ण

अटल व्योम gcm_calculate_auth_mac(काष्ठा aead_request *req, u64 dg[])
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा gcm_aes_ctx *ctx = crypto_aead_ctx(aead);
	u8 buf[GHASH_BLOCK_SIZE];
	काष्ठा scatter_walk walk;
	u32 len = req->assoclen;
	पूर्णांक buf_count = 0;

	scatterwalk_start(&walk, req->src);

	करो अणु
		u32 n = scatterwalk_clamp(&walk, len);
		u8 *p;

		अगर (!n) अणु
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		पूर्ण
		p = scatterwalk_map(&walk);

		gcm_update_mac(dg, p, n, buf, &buf_count, ctx);
		len -= n;

		scatterwalk_unmap(p);
		scatterwalk_advance(&walk, n);
		scatterwalk_करोne(&walk, 0, len);
	पूर्ण जबतक (len);

	अगर (buf_count) अणु
		स_रखो(&buf[buf_count], 0, GHASH_BLOCK_SIZE - buf_count);
		ghash_करो_simd_update(1, dg, buf, &ctx->ghash_key, शून्य,
				     pmull_ghash_update_p64);
	पूर्ण
पूर्ण

अटल पूर्णांक gcm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा gcm_aes_ctx *ctx = crypto_aead_ctx(aead);
	पूर्णांक nrounds = num_rounds(&ctx->aes_key);
	काष्ठा skcipher_walk walk;
	u8 buf[AES_BLOCK_SIZE];
	u8 iv[AES_BLOCK_SIZE];
	u64 dg[2] = अणुपूर्ण;
	be128 lengths;
	u8 *tag;
	पूर्णांक err;

	lengths.a = cpu_to_be64(req->assoclen * 8);
	lengths.b = cpu_to_be64(req->cryptlen * 8);

	अगर (req->assoclen)
		gcm_calculate_auth_mac(req, dg);

	स_नकल(iv, req->iv, GCM_IV_SIZE);
	put_unaligned_be32(2, iv + GCM_IV_SIZE);

	err = skcipher_walk_aead_encrypt(&walk, req, false);

	अगर (likely(crypto_simd_usable())) अणु
		करो अणु
			स्थिर u8 *src = walk.src.virt.addr;
			u8 *dst = walk.dst.virt.addr;
			पूर्णांक nbytes = walk.nbytes;

			tag = (u8 *)&lengths;

			अगर (unlikely(nbytes > 0 && nbytes < AES_BLOCK_SIZE)) अणु
				src = dst = स_नकल(buf + माप(buf) - nbytes,
						   src, nbytes);
			पूर्ण अन्यथा अगर (nbytes < walk.total) अणु
				nbytes &= ~(AES_BLOCK_SIZE - 1);
				tag = शून्य;
			पूर्ण

			kernel_neon_begin();
			pmull_gcm_encrypt(nbytes, dst, src, ctx->ghash_key.h,
					  dg, iv, ctx->aes_key.key_enc, nrounds,
					  tag);
			kernel_neon_end();

			अगर (unlikely(!nbytes))
				अवरोध;

			अगर (unlikely(nbytes > 0 && nbytes < AES_BLOCK_SIZE))
				स_नकल(walk.dst.virt.addr,
				       buf + माप(buf) - nbytes, nbytes);

			err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
		पूर्ण जबतक (walk.nbytes);
	पूर्ण अन्यथा अणु
		जबतक (walk.nbytes >= AES_BLOCK_SIZE) अणु
			पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;
			स्थिर u8 *src = walk.src.virt.addr;
			u8 *dst = walk.dst.virt.addr;
			पूर्णांक reमुख्यing = blocks;

			करो अणु
				aes_encrypt(&ctx->aes_key, buf, iv);
				crypto_xor_cpy(dst, src, buf, AES_BLOCK_SIZE);
				crypto_inc(iv, AES_BLOCK_SIZE);

				dst += AES_BLOCK_SIZE;
				src += AES_BLOCK_SIZE;
			पूर्ण जबतक (--reमुख्यing > 0);

			ghash_करो_update(blocks, dg, walk.dst.virt.addr,
					&ctx->ghash_key, शून्य);

			err = skcipher_walk_करोne(&walk,
						 walk.nbytes % AES_BLOCK_SIZE);
		पूर्ण

		/* handle the tail */
		अगर (walk.nbytes) अणु
			aes_encrypt(&ctx->aes_key, buf, iv);

			crypto_xor_cpy(walk.dst.virt.addr, walk.src.virt.addr,
				       buf, walk.nbytes);

			स_नकल(buf, walk.dst.virt.addr, walk.nbytes);
			स_रखो(buf + walk.nbytes, 0, माप(buf) - walk.nbytes);
		पूर्ण

		tag = (u8 *)&lengths;
		ghash_करो_update(1, dg, tag, &ctx->ghash_key,
				walk.nbytes ? buf : शून्य);

		अगर (walk.nbytes)
			err = skcipher_walk_करोne(&walk, 0);

		put_unaligned_be64(dg[1], tag);
		put_unaligned_be64(dg[0], tag + 8);
		put_unaligned_be32(1, iv + GCM_IV_SIZE);
		aes_encrypt(&ctx->aes_key, iv, iv);
		crypto_xor(tag, iv, AES_BLOCK_SIZE);
	पूर्ण

	अगर (err)
		वापस err;

	/* copy authtag to end of dst */
	scatterwalk_map_and_copy(tag, req->dst, req->assoclen + req->cryptlen,
				 crypto_aead_authsize(aead), 1);

	वापस 0;
पूर्ण

अटल पूर्णांक gcm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा gcm_aes_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	पूर्णांक nrounds = num_rounds(&ctx->aes_key);
	काष्ठा skcipher_walk walk;
	u8 otag[AES_BLOCK_SIZE];
	u8 buf[AES_BLOCK_SIZE];
	u8 iv[AES_BLOCK_SIZE];
	u64 dg[2] = अणुपूर्ण;
	be128 lengths;
	u8 *tag;
	पूर्णांक err;

	lengths.a = cpu_to_be64(req->assoclen * 8);
	lengths.b = cpu_to_be64((req->cryptlen - authsize) * 8);

	अगर (req->assoclen)
		gcm_calculate_auth_mac(req, dg);

	स_नकल(iv, req->iv, GCM_IV_SIZE);
	put_unaligned_be32(2, iv + GCM_IV_SIZE);

	scatterwalk_map_and_copy(otag, req->src,
				 req->assoclen + req->cryptlen - authsize,
				 authsize, 0);

	err = skcipher_walk_aead_decrypt(&walk, req, false);

	अगर (likely(crypto_simd_usable())) अणु
		पूर्णांक ret;

		करो अणु
			स्थिर u8 *src = walk.src.virt.addr;
			u8 *dst = walk.dst.virt.addr;
			पूर्णांक nbytes = walk.nbytes;

			tag = (u8 *)&lengths;

			अगर (unlikely(nbytes > 0 && nbytes < AES_BLOCK_SIZE)) अणु
				src = dst = स_नकल(buf + माप(buf) - nbytes,
						   src, nbytes);
			पूर्ण अन्यथा अगर (nbytes < walk.total) अणु
				nbytes &= ~(AES_BLOCK_SIZE - 1);
				tag = शून्य;
			पूर्ण

			kernel_neon_begin();
			ret = pmull_gcm_decrypt(nbytes, dst, src,
						ctx->ghash_key.h,
						dg, iv, ctx->aes_key.key_enc,
						nrounds, tag, otag, authsize);
			kernel_neon_end();

			अगर (unlikely(!nbytes))
				अवरोध;

			अगर (unlikely(nbytes > 0 && nbytes < AES_BLOCK_SIZE))
				स_नकल(walk.dst.virt.addr,
				       buf + माप(buf) - nbytes, nbytes);

			err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
		पूर्ण जबतक (walk.nbytes);

		अगर (err)
			वापस err;
		अगर (ret)
			वापस -EBADMSG;
	पूर्ण अन्यथा अणु
		जबतक (walk.nbytes >= AES_BLOCK_SIZE) अणु
			पूर्णांक blocks = walk.nbytes / AES_BLOCK_SIZE;
			स्थिर u8 *src = walk.src.virt.addr;
			u8 *dst = walk.dst.virt.addr;

			ghash_करो_update(blocks, dg, walk.src.virt.addr,
					&ctx->ghash_key, शून्य);

			करो अणु
				aes_encrypt(&ctx->aes_key, buf, iv);
				crypto_xor_cpy(dst, src, buf, AES_BLOCK_SIZE);
				crypto_inc(iv, AES_BLOCK_SIZE);

				dst += AES_BLOCK_SIZE;
				src += AES_BLOCK_SIZE;
			पूर्ण जबतक (--blocks > 0);

			err = skcipher_walk_करोne(&walk,
						 walk.nbytes % AES_BLOCK_SIZE);
		पूर्ण

		/* handle the tail */
		अगर (walk.nbytes) अणु
			स_नकल(buf, walk.src.virt.addr, walk.nbytes);
			स_रखो(buf + walk.nbytes, 0, माप(buf) - walk.nbytes);
		पूर्ण

		tag = (u8 *)&lengths;
		ghash_करो_update(1, dg, tag, &ctx->ghash_key,
				walk.nbytes ? buf : शून्य);

		अगर (walk.nbytes) अणु
			aes_encrypt(&ctx->aes_key, buf, iv);

			crypto_xor_cpy(walk.dst.virt.addr, walk.src.virt.addr,
				       buf, walk.nbytes);

			err = skcipher_walk_करोne(&walk, 0);
		पूर्ण

		अगर (err)
			वापस err;

		put_unaligned_be64(dg[1], tag);
		put_unaligned_be64(dg[0], tag + 8);
		put_unaligned_be32(1, iv + GCM_IV_SIZE);
		aes_encrypt(&ctx->aes_key, iv, iv);
		crypto_xor(tag, iv, AES_BLOCK_SIZE);

		अगर (crypto_memneq(tag, otag, authsize)) अणु
			memzero_explicit(tag, AES_BLOCK_SIZE);
			वापस -EBADMSG;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा aead_alg gcm_aes_alg = अणु
	.ivsize			= GCM_IV_SIZE,
	.chunksize		= AES_BLOCK_SIZE,
	.maxauthsize		= AES_BLOCK_SIZE,
	.setkey			= gcm_setkey,
	.setauthsize		= gcm_setauthsize,
	.encrypt		= gcm_encrypt,
	.decrypt		= gcm_decrypt,

	.base.cra_name		= "gcm(aes)",
	.base.cra_driver_name	= "gcm-aes-ce",
	.base.cra_priority	= 300,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा gcm_aes_ctx) +
				  4 * माप(u64[2]),
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ghash_ce_mod_init(व्योम)
अणु
	अगर (!cpu_have_named_feature(ASIMD))
		वापस -ENODEV;

	अगर (cpu_have_named_feature(PMULL))
		वापस crypto_रेजिस्टर_aead(&gcm_aes_alg);

	वापस crypto_रेजिस्टर_shash(&ghash_alg);
पूर्ण

अटल व्योम __निकास ghash_ce_mod_निकास(व्योम)
अणु
	अगर (cpu_have_named_feature(PMULL))
		crypto_unरेजिस्टर_aead(&gcm_aes_alg);
	अन्यथा
		crypto_unरेजिस्टर_shash(&ghash_alg);
पूर्ण

अटल स्थिर काष्ठा cpu_feature ghash_cpu_feature[] = अणु
	अणु cpu_feature(PMULL) पूर्ण, अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(cpu, ghash_cpu_feature);

module_init(ghash_ce_mod_init);
module_निकास(ghash_ce_mod_निकास);
