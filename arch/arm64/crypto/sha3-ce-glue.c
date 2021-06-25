<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sha3-ce-glue.c - core SHA-3 transक्रमm using v8.2 Crypto Extensions
 *
 * Copyright (C) 2018 Linaro Ltd <ard.biesheuvel@linaro.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha3.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("SHA3 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sha3-224");
MODULE_ALIAS_CRYPTO("sha3-256");
MODULE_ALIAS_CRYPTO("sha3-384");
MODULE_ALIAS_CRYPTO("sha3-512");

यंत्रlinkage पूर्णांक sha3_ce_transक्रमm(u64 *st, स्थिर u8 *data, पूर्णांक blocks,
				 पूर्णांक md_len);

अटल पूर्णांक sha3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha3_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक digest_size = crypto_shash_digestsize(desc->tfm);

	अगर (!crypto_simd_usable())
		वापस crypto_sha3_update(desc, data, len);

	अगर ((sctx->partial + len) >= sctx->rsiz) अणु
		पूर्णांक blocks;

		अगर (sctx->partial) अणु
			पूर्णांक p = sctx->rsiz - sctx->partial;

			स_नकल(sctx->buf + sctx->partial, data, p);
			kernel_neon_begin();
			sha3_ce_transक्रमm(sctx->st, sctx->buf, 1, digest_size);
			kernel_neon_end();

			data += p;
			len -= p;
			sctx->partial = 0;
		पूर्ण

		blocks = len / sctx->rsiz;
		len %= sctx->rsiz;

		जबतक (blocks) अणु
			पूर्णांक rem;

			kernel_neon_begin();
			rem = sha3_ce_transक्रमm(sctx->st, data, blocks,
						digest_size);
			kernel_neon_end();
			data += (blocks - rem) * sctx->rsiz;
			blocks = rem;
		पूर्ण
	पूर्ण

	अगर (len) अणु
		स_नकल(sctx->buf + sctx->partial, data, len);
		sctx->partial += len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sha3_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha3_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक digest_size = crypto_shash_digestsize(desc->tfm);
	__le64 *digest = (__le64 *)out;
	पूर्णांक i;

	अगर (!crypto_simd_usable())
		वापस crypto_sha3_final(desc, out);

	sctx->buf[sctx->partial++] = 0x06;
	स_रखो(sctx->buf + sctx->partial, 0, sctx->rsiz - sctx->partial);
	sctx->buf[sctx->rsiz - 1] |= 0x80;

	kernel_neon_begin();
	sha3_ce_transक्रमm(sctx->st, sctx->buf, 1, digest_size);
	kernel_neon_end();

	क्रम (i = 0; i < digest_size / 8; i++)
		put_unaligned_le64(sctx->st[i], digest++);

	अगर (digest_size & 4)
		put_unaligned_le32(sctx->st[i], (__le32 *)digest);

	memzero_explicit(sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg algs[] = अणु अणु
	.digestsize		= SHA3_224_DIGEST_SIZE,
	.init			= crypto_sha3_init,
	.update			= sha3_update,
	.final			= sha3_final,
	.descsize		= माप(काष्ठा sha3_state),
	.base.cra_name		= "sha3-224",
	.base.cra_driver_name	= "sha3-224-ce",
	.base.cra_blocksize	= SHA3_224_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
	.base.cra_priority	= 200,
पूर्ण, अणु
	.digestsize		= SHA3_256_DIGEST_SIZE,
	.init			= crypto_sha3_init,
	.update			= sha3_update,
	.final			= sha3_final,
	.descsize		= माप(काष्ठा sha3_state),
	.base.cra_name		= "sha3-256",
	.base.cra_driver_name	= "sha3-256-ce",
	.base.cra_blocksize	= SHA3_256_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
	.base.cra_priority	= 200,
पूर्ण, अणु
	.digestsize		= SHA3_384_DIGEST_SIZE,
	.init			= crypto_sha3_init,
	.update			= sha3_update,
	.final			= sha3_final,
	.descsize		= माप(काष्ठा sha3_state),
	.base.cra_name		= "sha3-384",
	.base.cra_driver_name	= "sha3-384-ce",
	.base.cra_blocksize	= SHA3_384_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
	.base.cra_priority	= 200,
पूर्ण, अणु
	.digestsize		= SHA3_512_DIGEST_SIZE,
	.init			= crypto_sha3_init,
	.update			= sha3_update,
	.final			= sha3_final,
	.descsize		= माप(काष्ठा sha3_state),
	.base.cra_name		= "sha3-512",
	.base.cra_driver_name	= "sha3-512-ce",
	.base.cra_blocksize	= SHA3_512_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
	.base.cra_priority	= 200,
पूर्ण पूर्ण;

अटल पूर्णांक __init sha3_neon_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

अटल व्योम __निकास sha3_neon_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

module_cpu_feature_match(SHA3, sha3_neon_mod_init);
module_निकास(sha3_neon_mod_fini);
