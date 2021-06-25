<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * aes-ccm-glue.c - AES-CCM transक्रमm क्रम ARMv8 with Crypto Extensions
 *
 * Copyright (C) 2013 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/module.h>

#समावेश "aes-ce-setkey.h"

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

यंत्रlinkage व्योम ce_aes_ccm_auth_data(u8 mac[], u8 स्थिर in[], u32 abytes,
				     u32 *macp, u32 स्थिर rk[], u32 rounds);

यंत्रlinkage व्योम ce_aes_ccm_encrypt(u8 out[], u8 स्थिर in[], u32 cbytes,
				   u32 स्थिर rk[], u32 rounds, u8 mac[],
				   u8 ctr[]);

यंत्रlinkage व्योम ce_aes_ccm_decrypt(u8 out[], u8 स्थिर in[], u32 cbytes,
				   u32 स्थिर rk[], u32 rounds, u8 mac[],
				   u8 ctr[]);

यंत्रlinkage व्योम ce_aes_ccm_final(u8 mac[], u8 स्थिर ctr[], u32 स्थिर rk[],
				 u32 rounds);

अटल पूर्णांक ccm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *in_key,
		      अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_aead_ctx(tfm);

	वापस ce_aes_expandkey(ctx, in_key, key_len);
पूर्ण

अटल पूर्णांक ccm_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	अगर ((authsize & 1) || authsize < 4)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक ccm_init_mac(काष्ठा aead_request *req, u8 maciv[], u32 msglen)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	__be32 *n = (__be32 *)&maciv[AES_BLOCK_SIZE - 8];
	u32 l = req->iv[0] + 1;

	/* verअगरy that CCM dimension 'L' is set correctly in the IV */
	अगर (l < 2 || l > 8)
		वापस -EINVAL;

	/* verअगरy that msglen can in fact be represented in L bytes */
	अगर (l < 4 && msglen >> (8 * l))
		वापस -EOVERFLOW;

	/*
	 * Even अगर the CCM spec allows L values of up to 8, the Linux cryptoapi
	 * uses a u32 type to represent msglen so the top 4 bytes are always 0.
	 */
	n[0] = 0;
	n[1] = cpu_to_be32(msglen);

	स_नकल(maciv, req->iv, AES_BLOCK_SIZE - l);

	/*
	 * Meaning of byte 0 according to CCM spec (RFC 3610/NIST 800-38C)
	 * - bits 0..2	: max # of bytes required to represent msglen, minus 1
	 *                (alपढ़ोy set by caller)
	 * - bits 3..5	: size of auth tag (1 => 4 bytes, 2 => 6 bytes, etc)
	 * - bit 6	: indicates presence of authenticate-only data
	 */
	maciv[0] |= (crypto_aead_authsize(aead) - 2) << 2;
	अगर (req->assoclen)
		maciv[0] |= 0x40;

	स_रखो(&req->iv[AES_BLOCK_SIZE - l], 0, l);
	वापस 0;
पूर्ण

अटल व्योम ccm_update_mac(काष्ठा crypto_aes_ctx *key, u8 mac[], u8 स्थिर in[],
			   u32 abytes, u32 *macp)
अणु
	अगर (crypto_simd_usable()) अणु
		kernel_neon_begin();
		ce_aes_ccm_auth_data(mac, in, abytes, macp, key->key_enc,
				     num_rounds(key));
		kernel_neon_end();
	पूर्ण अन्यथा अणु
		अगर (*macp > 0 && *macp < AES_BLOCK_SIZE) अणु
			पूर्णांक added = min(abytes, AES_BLOCK_SIZE - *macp);

			crypto_xor(&mac[*macp], in, added);

			*macp += added;
			in += added;
			abytes -= added;
		पूर्ण

		जबतक (abytes >= AES_BLOCK_SIZE) अणु
			aes_encrypt(key, mac, mac);
			crypto_xor(mac, in, AES_BLOCK_SIZE);

			in += AES_BLOCK_SIZE;
			abytes -= AES_BLOCK_SIZE;
		पूर्ण

		अगर (abytes > 0) अणु
			aes_encrypt(key, mac, mac);
			crypto_xor(mac, in, abytes);
			*macp = abytes;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ccm_calculate_auth_mac(काष्ठा aead_request *req, u8 mac[])
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा __packed अणु __be16 l; __be32 h; u16 len; पूर्ण ltag;
	काष्ठा scatter_walk walk;
	u32 len = req->assoclen;
	u32 macp = 0;

	/* prepend the AAD with a length tag */
	अगर (len < 0xff00) अणु
		ltag.l = cpu_to_be16(len);
		ltag.len = 2;
	पूर्ण अन्यथा  अणु
		ltag.l = cpu_to_be16(0xfffe);
		put_unaligned_be32(len, &ltag.h);
		ltag.len = 6;
	पूर्ण

	ccm_update_mac(ctx, mac, (u8 *)&ltag, ltag.len, &macp);
	scatterwalk_start(&walk, req->src);

	करो अणु
		u32 n = scatterwalk_clamp(&walk, len);
		u8 *p;

		अगर (!n) अणु
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		पूर्ण
		p = scatterwalk_map(&walk);
		ccm_update_mac(ctx, mac, p, n, &macp);
		len -= n;

		scatterwalk_unmap(p);
		scatterwalk_advance(&walk, n);
		scatterwalk_करोne(&walk, 0, len);
	पूर्ण जबतक (len);
पूर्ण

अटल पूर्णांक ccm_crypt_fallback(काष्ठा skcipher_walk *walk, u8 mac[], u8 iv0[],
			      काष्ठा crypto_aes_ctx *ctx, bool enc)
अणु
	u8 buf[AES_BLOCK_SIZE];
	पूर्णांक err = 0;

	जबतक (walk->nbytes) अणु
		पूर्णांक blocks = walk->nbytes / AES_BLOCK_SIZE;
		u32 tail = walk->nbytes % AES_BLOCK_SIZE;
		u8 *dst = walk->dst.virt.addr;
		u8 *src = walk->src.virt.addr;
		u32 nbytes = walk->nbytes;

		अगर (nbytes == walk->total && tail > 0) अणु
			blocks++;
			tail = 0;
		पूर्ण

		करो अणु
			u32 bsize = AES_BLOCK_SIZE;

			अगर (nbytes < AES_BLOCK_SIZE)
				bsize = nbytes;

			crypto_inc(walk->iv, AES_BLOCK_SIZE);
			aes_encrypt(ctx, buf, walk->iv);
			aes_encrypt(ctx, mac, mac);
			अगर (enc)
				crypto_xor(mac, src, bsize);
			crypto_xor_cpy(dst, src, buf, bsize);
			अगर (!enc)
				crypto_xor(mac, dst, bsize);
			dst += bsize;
			src += bsize;
			nbytes -= bsize;
		पूर्ण जबतक (--blocks);

		err = skcipher_walk_करोne(walk, tail);
	पूर्ण

	अगर (!err) अणु
		aes_encrypt(ctx, buf, iv0);
		aes_encrypt(ctx, mac, mac);
		crypto_xor(mac, buf, AES_BLOCK_SIZE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ccm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा skcipher_walk walk;
	u8 __aligned(8) mac[AES_BLOCK_SIZE];
	u8 buf[AES_BLOCK_SIZE];
	u32 len = req->cryptlen;
	पूर्णांक err;

	err = ccm_init_mac(req, mac, len);
	अगर (err)
		वापस err;

	अगर (req->assoclen)
		ccm_calculate_auth_mac(req, mac);

	/* preserve the original iv क्रम the final round */
	स_नकल(buf, req->iv, AES_BLOCK_SIZE);

	err = skcipher_walk_aead_encrypt(&walk, req, false);

	अगर (crypto_simd_usable()) अणु
		जबतक (walk.nbytes) अणु
			u32 tail = walk.nbytes % AES_BLOCK_SIZE;

			अगर (walk.nbytes == walk.total)
				tail = 0;

			kernel_neon_begin();
			ce_aes_ccm_encrypt(walk.dst.virt.addr,
					   walk.src.virt.addr,
					   walk.nbytes - tail, ctx->key_enc,
					   num_rounds(ctx), mac, walk.iv);
			kernel_neon_end();

			err = skcipher_walk_करोne(&walk, tail);
		पूर्ण
		अगर (!err) अणु
			kernel_neon_begin();
			ce_aes_ccm_final(mac, buf, ctx->key_enc,
					 num_rounds(ctx));
			kernel_neon_end();
		पूर्ण
	पूर्ण अन्यथा अणु
		err = ccm_crypt_fallback(&walk, mac, buf, ctx, true);
	पूर्ण
	अगर (err)
		वापस err;

	/* copy authtag to end of dst */
	scatterwalk_map_and_copy(mac, req->dst, req->assoclen + req->cryptlen,
				 crypto_aead_authsize(aead), 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ccm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_aes_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	काष्ठा skcipher_walk walk;
	u8 __aligned(8) mac[AES_BLOCK_SIZE];
	u8 buf[AES_BLOCK_SIZE];
	u32 len = req->cryptlen - authsize;
	पूर्णांक err;

	err = ccm_init_mac(req, mac, len);
	अगर (err)
		वापस err;

	अगर (req->assoclen)
		ccm_calculate_auth_mac(req, mac);

	/* preserve the original iv क्रम the final round */
	स_नकल(buf, req->iv, AES_BLOCK_SIZE);

	err = skcipher_walk_aead_decrypt(&walk, req, false);

	अगर (crypto_simd_usable()) अणु
		जबतक (walk.nbytes) अणु
			u32 tail = walk.nbytes % AES_BLOCK_SIZE;

			अगर (walk.nbytes == walk.total)
				tail = 0;

			kernel_neon_begin();
			ce_aes_ccm_decrypt(walk.dst.virt.addr,
					   walk.src.virt.addr,
					   walk.nbytes - tail, ctx->key_enc,
					   num_rounds(ctx), mac, walk.iv);
			kernel_neon_end();

			err = skcipher_walk_करोne(&walk, tail);
		पूर्ण
		अगर (!err) अणु
			kernel_neon_begin();
			ce_aes_ccm_final(mac, buf, ctx->key_enc,
					 num_rounds(ctx));
			kernel_neon_end();
		पूर्ण
	पूर्ण अन्यथा अणु
		err = ccm_crypt_fallback(&walk, mac, buf, ctx, false);
	पूर्ण

	अगर (err)
		वापस err;

	/* compare calculated auth tag with the stored one */
	scatterwalk_map_and_copy(buf, req->src,
				 req->assoclen + req->cryptlen - authsize,
				 authsize, 0);

	अगर (crypto_memneq(mac, buf, authsize))
		वापस -EBADMSG;
	वापस 0;
पूर्ण

अटल काष्ठा aead_alg ccm_aes_alg = अणु
	.base = अणु
		.cra_name		= "ccm(aes)",
		.cra_driver_name	= "ccm-aes-ce",
		.cra_priority		= 300,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.ivsize		= AES_BLOCK_SIZE,
	.chunksize	= AES_BLOCK_SIZE,
	.maxauthsize	= AES_BLOCK_SIZE,
	.setkey		= ccm_setkey,
	.setauthsize	= ccm_setauthsize,
	.encrypt	= ccm_encrypt,
	.decrypt	= ccm_decrypt,
पूर्ण;

अटल पूर्णांक __init aes_mod_init(व्योम)
अणु
	अगर (!cpu_have_named_feature(AES))
		वापस -ENODEV;
	वापस crypto_रेजिस्टर_aead(&ccm_aes_alg);
पूर्ण

अटल व्योम __निकास aes_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_aead(&ccm_aes_alg);
पूर्ण

module_init(aes_mod_init);
module_निकास(aes_mod_निकास);

MODULE_DESCRIPTION("Synchronous AES in CCM mode using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("ccm(aes)");
