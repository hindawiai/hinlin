<शैली गुरु>
/*
 * Poly1305 authenticator algorithm, RFC7539
 *
 * Copyright (C) 2015 Martin Willi
 *
 * Based on खुला करोमुख्य code by Andrew Moon and Daniel J. Bernstein.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

अटल पूर्णांक crypto_poly1305_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	poly1305_core_init(&dctx->h);
	dctx->buflen = 0;
	dctx->rset = 0;
	dctx->sset = false;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक crypto_poly1305_setdesckey(काष्ठा poly1305_desc_ctx *dctx,
					       स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	अगर (!dctx->sset) अणु
		अगर (!dctx->rset && srclen >= POLY1305_BLOCK_SIZE) अणु
			poly1305_core_setkey(&dctx->core_r, src);
			src += POLY1305_BLOCK_SIZE;
			srclen -= POLY1305_BLOCK_SIZE;
			dctx->rset = 2;
		पूर्ण
		अगर (srclen >= POLY1305_BLOCK_SIZE) अणु
			dctx->s[0] = get_unaligned_le32(src +  0);
			dctx->s[1] = get_unaligned_le32(src +  4);
			dctx->s[2] = get_unaligned_le32(src +  8);
			dctx->s[3] = get_unaligned_le32(src + 12);
			src += POLY1305_BLOCK_SIZE;
			srclen -= POLY1305_BLOCK_SIZE;
			dctx->sset = true;
		पूर्ण
	पूर्ण
	वापस srclen;
पूर्ण

अटल व्योम poly1305_blocks(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 *src,
			    अचिन्हित पूर्णांक srclen)
अणु
	अचिन्हित पूर्णांक datalen;

	अगर (unlikely(!dctx->sset)) अणु
		datalen = crypto_poly1305_setdesckey(dctx, src, srclen);
		src += srclen - datalen;
		srclen = datalen;
	पूर्ण

	poly1305_core_blocks(&dctx->h, &dctx->core_r, src,
			     srclen / POLY1305_BLOCK_SIZE, 1);
पूर्ण

अटल पूर्णांक crypto_poly1305_update(काष्ठा shash_desc *desc,
				  स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक bytes;

	अगर (unlikely(dctx->buflen)) अणु
		bytes = min(srclen, POLY1305_BLOCK_SIZE - dctx->buflen);
		स_नकल(dctx->buf + dctx->buflen, src, bytes);
		src += bytes;
		srclen -= bytes;
		dctx->buflen += bytes;

		अगर (dctx->buflen == POLY1305_BLOCK_SIZE) अणु
			poly1305_blocks(dctx, dctx->buf,
					POLY1305_BLOCK_SIZE);
			dctx->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(srclen >= POLY1305_BLOCK_SIZE)) अणु
		poly1305_blocks(dctx, src, srclen);
		src += srclen - (srclen % POLY1305_BLOCK_SIZE);
		srclen %= POLY1305_BLOCK_SIZE;
	पूर्ण

	अगर (unlikely(srclen)) अणु
		dctx->buflen = srclen;
		स_नकल(dctx->buf, src, srclen);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_poly1305_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (unlikely(!dctx->sset))
		वापस -ENOKEY;

	poly1305_final_generic(dctx, dst);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg poly1305_alg = अणु
	.digestsize	= POLY1305_DIGEST_SIZE,
	.init		= crypto_poly1305_init,
	.update		= crypto_poly1305_update,
	.final		= crypto_poly1305_final,
	.descsize	= माप(काष्ठा poly1305_desc_ctx),
	.base		= अणु
		.cra_name		= "poly1305",
		.cra_driver_name	= "poly1305-generic",
		.cra_priority		= 100,
		.cra_blocksize		= POLY1305_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init poly1305_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&poly1305_alg);
पूर्ण

अटल व्योम __निकास poly1305_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&poly1305_alg);
पूर्ण

subsys_initcall(poly1305_mod_init);
module_निकास(poly1305_mod_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Willi <martin@strongswan.org>");
MODULE_DESCRIPTION("Poly1305 authenticator");
MODULE_ALIAS_CRYPTO("poly1305");
MODULE_ALIAS_CRYPTO("poly1305-generic");
