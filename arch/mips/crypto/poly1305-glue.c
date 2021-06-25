<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OpenSSL/Cryptogams accelerated Poly1305 transक्रमm क्रम MIPS
 *
 * Copyright (C) 2019 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

यंत्रlinkage व्योम poly1305_init_mips(व्योम *state, स्थिर u8 *key);
यंत्रlinkage व्योम poly1305_blocks_mips(व्योम *state, स्थिर u8 *src, u32 len, u32 hibit);
यंत्रlinkage व्योम poly1305_emit_mips(व्योम *state, u8 *digest, स्थिर u32 *nonce);

व्योम poly1305_init_arch(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 key[POLY1305_KEY_SIZE])
अणु
	poly1305_init_mips(&dctx->h, key);
	dctx->s[0] = get_unaligned_le32(key + 16);
	dctx->s[1] = get_unaligned_le32(key + 20);
	dctx->s[2] = get_unaligned_le32(key + 24);
	dctx->s[3] = get_unaligned_le32(key + 28);
	dctx->buflen = 0;
पूर्ण
EXPORT_SYMBOL(poly1305_init_arch);

अटल पूर्णांक mips_poly1305_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->buflen = 0;
	dctx->rset = 0;
	dctx->sset = false;

	वापस 0;
पूर्ण

अटल व्योम mips_poly1305_blocks(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 *src,
				 u32 len, u32 hibit)
अणु
	अगर (unlikely(!dctx->sset)) अणु
		अगर (!dctx->rset) अणु
			poly1305_init_mips(&dctx->h, src);
			src += POLY1305_BLOCK_SIZE;
			len -= POLY1305_BLOCK_SIZE;
			dctx->rset = 1;
		पूर्ण
		अगर (len >= POLY1305_BLOCK_SIZE) अणु
			dctx->s[0] = get_unaligned_le32(src +  0);
			dctx->s[1] = get_unaligned_le32(src +  4);
			dctx->s[2] = get_unaligned_le32(src +  8);
			dctx->s[3] = get_unaligned_le32(src + 12);
			src += POLY1305_BLOCK_SIZE;
			len -= POLY1305_BLOCK_SIZE;
			dctx->sset = true;
		पूर्ण
		अगर (len < POLY1305_BLOCK_SIZE)
			वापस;
	पूर्ण

	len &= ~(POLY1305_BLOCK_SIZE - 1);

	poly1305_blocks_mips(&dctx->h, src, len, hibit);
पूर्ण

अटल पूर्णांक mips_poly1305_update(काष्ठा shash_desc *desc, स्थिर u8 *src,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (unlikely(dctx->buflen)) अणु
		u32 bytes = min(len, POLY1305_BLOCK_SIZE - dctx->buflen);

		स_नकल(dctx->buf + dctx->buflen, src, bytes);
		src += bytes;
		len -= bytes;
		dctx->buflen += bytes;

		अगर (dctx->buflen == POLY1305_BLOCK_SIZE) अणु
			mips_poly1305_blocks(dctx, dctx->buf, POLY1305_BLOCK_SIZE, 1);
			dctx->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(len >= POLY1305_BLOCK_SIZE)) अणु
		mips_poly1305_blocks(dctx, src, len, 1);
		src += round_करोwn(len, POLY1305_BLOCK_SIZE);
		len %= POLY1305_BLOCK_SIZE;
	पूर्ण

	अगर (unlikely(len)) अणु
		dctx->buflen = len;
		स_नकल(dctx->buf, src, len);
	पूर्ण
	वापस 0;
पूर्ण

व्योम poly1305_update_arch(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 *src,
			  अचिन्हित पूर्णांक nbytes)
अणु
	अगर (unlikely(dctx->buflen)) अणु
		u32 bytes = min(nbytes, POLY1305_BLOCK_SIZE - dctx->buflen);

		स_नकल(dctx->buf + dctx->buflen, src, bytes);
		src += bytes;
		nbytes -= bytes;
		dctx->buflen += bytes;

		अगर (dctx->buflen == POLY1305_BLOCK_SIZE) अणु
			poly1305_blocks_mips(&dctx->h, dctx->buf,
					     POLY1305_BLOCK_SIZE, 1);
			dctx->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(nbytes >= POLY1305_BLOCK_SIZE)) अणु
		अचिन्हित पूर्णांक len = round_करोwn(nbytes, POLY1305_BLOCK_SIZE);

		poly1305_blocks_mips(&dctx->h, src, len, 1);
		src += len;
		nbytes %= POLY1305_BLOCK_SIZE;
	पूर्ण

	अगर (unlikely(nbytes)) अणु
		dctx->buflen = nbytes;
		स_नकल(dctx->buf, src, nbytes);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(poly1305_update_arch);

व्योम poly1305_final_arch(काष्ठा poly1305_desc_ctx *dctx, u8 *dst)
अणु
	अगर (unlikely(dctx->buflen)) अणु
		dctx->buf[dctx->buflen++] = 1;
		स_रखो(dctx->buf + dctx->buflen, 0,
		       POLY1305_BLOCK_SIZE - dctx->buflen);
		poly1305_blocks_mips(&dctx->h, dctx->buf, POLY1305_BLOCK_SIZE, 0);
	पूर्ण

	poly1305_emit_mips(&dctx->h, dst, dctx->s);
	*dctx = (काष्ठा poly1305_desc_ctx)अणुपूर्ण;
पूर्ण
EXPORT_SYMBOL(poly1305_final_arch);

अटल पूर्णांक mips_poly1305_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (unlikely(!dctx->sset))
		वापस -ENOKEY;

	poly1305_final_arch(dctx, dst);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg mips_poly1305_alg = अणु
	.init			= mips_poly1305_init,
	.update			= mips_poly1305_update,
	.final			= mips_poly1305_final,
	.digestsize		= POLY1305_DIGEST_SIZE,
	.descsize		= माप(काष्ठा poly1305_desc_ctx),

	.base.cra_name		= "poly1305",
	.base.cra_driver_name	= "poly1305-mips",
	.base.cra_priority	= 200,
	.base.cra_blocksize	= POLY1305_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init mips_poly1305_mod_init(व्योम)
अणु
	वापस IS_REACHABLE(CONFIG_CRYPTO_HASH) ?
		crypto_रेजिस्टर_shash(&mips_poly1305_alg) : 0;
पूर्ण

अटल व्योम __निकास mips_poly1305_mod_निकास(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_HASH))
		crypto_unरेजिस्टर_shash(&mips_poly1305_alg);
पूर्ण

module_init(mips_poly1305_mod_init);
module_निकास(mips_poly1305_mod_निकास);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("poly1305");
MODULE_ALIAS_CRYPTO("poly1305-mips");
