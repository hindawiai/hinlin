<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * SHA-224 and SHA-256 Secure Hash Algorithm.
 *
 * Adapted क्रम OCTEON by Aaro Koskinen <aaro.koskinen@iki.fi>.
 *
 * Based on crypto/sha256_generic.c, which is:
 *
 * Copyright (c) Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * SHA224 Support Copyright 2007 Intel Corporation <jonathan.lynch@पूर्णांकel.com>
 */

#समावेश <linux/mm.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/octeon/octeon.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "octeon-crypto.h"

/*
 * We pass everything as 64-bit. OCTEON can handle misaligned data.
 */

अटल व्योम octeon_sha256_store_hash(काष्ठा sha256_state *sctx)
अणु
	u64 *hash = (u64 *)sctx->state;

	ग_लिखो_octeon_64bit_hash_dword(hash[0], 0);
	ग_लिखो_octeon_64bit_hash_dword(hash[1], 1);
	ग_लिखो_octeon_64bit_hash_dword(hash[2], 2);
	ग_लिखो_octeon_64bit_hash_dword(hash[3], 3);
पूर्ण

अटल व्योम octeon_sha256_पढ़ो_hash(काष्ठा sha256_state *sctx)
अणु
	u64 *hash = (u64 *)sctx->state;

	hash[0] = पढ़ो_octeon_64bit_hash_dword(0);
	hash[1] = पढ़ो_octeon_64bit_hash_dword(1);
	hash[2] = पढ़ो_octeon_64bit_hash_dword(2);
	hash[3] = पढ़ो_octeon_64bit_hash_dword(3);
पूर्ण

अटल व्योम octeon_sha256_transक्रमm(स्थिर व्योम *_block)
अणु
	स्थिर u64 *block = _block;

	ग_लिखो_octeon_64bit_block_dword(block[0], 0);
	ग_लिखो_octeon_64bit_block_dword(block[1], 1);
	ग_लिखो_octeon_64bit_block_dword(block[2], 2);
	ग_लिखो_octeon_64bit_block_dword(block[3], 3);
	ग_लिखो_octeon_64bit_block_dword(block[4], 4);
	ग_लिखो_octeon_64bit_block_dword(block[5], 5);
	ग_लिखो_octeon_64bit_block_dword(block[6], 6);
	octeon_sha256_start(block[7]);
पूर्ण

अटल पूर्णांक octeon_sha224_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA224_H0;
	sctx->state[1] = SHA224_H1;
	sctx->state[2] = SHA224_H2;
	sctx->state[3] = SHA224_H3;
	sctx->state[4] = SHA224_H4;
	sctx->state[5] = SHA224_H5;
	sctx->state[6] = SHA224_H6;
	sctx->state[7] = SHA224_H7;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha256_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA256_H0;
	sctx->state[1] = SHA256_H1;
	sctx->state[2] = SHA256_H2;
	sctx->state[3] = SHA256_H3;
	sctx->state[4] = SHA256_H4;
	sctx->state[5] = SHA256_H5;
	sctx->state[6] = SHA256_H6;
	sctx->state[7] = SHA256_H7;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल व्योम __octeon_sha256_update(काष्ठा sha256_state *sctx, स्थिर u8 *data,
				   अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक partial;
	अचिन्हित पूर्णांक करोne;
	स्थिर u8 *src;

	partial = sctx->count % SHA256_BLOCK_SIZE;
	sctx->count += len;
	करोne = 0;
	src = data;

	अगर ((partial + len) >= SHA256_BLOCK_SIZE) अणु
		अगर (partial) अणु
			करोne = -partial;
			स_नकल(sctx->buf + partial, data,
			       करोne + SHA256_BLOCK_SIZE);
			src = sctx->buf;
		पूर्ण

		करो अणु
			octeon_sha256_transक्रमm(src);
			करोne += SHA256_BLOCK_SIZE;
			src = data + करोne;
		पूर्ण जबतक (करोne + SHA256_BLOCK_SIZE <= len);

		partial = 0;
	पूर्ण
	स_नकल(sctx->buf + partial, src, len - करोne);
पूर्ण

अटल पूर्णांक octeon_sha256_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	काष्ठा octeon_cop2_state state;
	अचिन्हित दीर्घ flags;

	/*
	 * Small updates never reach the crypto engine, so the generic sha256 is
	 * faster because of the heavyweight octeon_crypto_enable() /
	 * octeon_crypto_disable().
	 */
	अगर ((sctx->count % SHA256_BLOCK_SIZE) + len < SHA256_BLOCK_SIZE)
		वापस crypto_sha256_update(desc, data, len);

	flags = octeon_crypto_enable(&state);
	octeon_sha256_store_hash(sctx);

	__octeon_sha256_update(sctx, data, len);

	octeon_sha256_पढ़ो_hash(sctx);
	octeon_crypto_disable(&state, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha256_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	अटल स्थिर u8 padding[64] = अणु 0x80, पूर्ण;
	काष्ठा octeon_cop2_state state;
	__be32 *dst = (__be32 *)out;
	अचिन्हित पूर्णांक pad_len;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक index;
	__be64 bits;
	पूर्णांक i;

	/* Save number of bits. */
	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64. */
	index = sctx->count & 0x3f;
	pad_len = (index < 56) ? (56 - index) : ((64+56) - index);

	flags = octeon_crypto_enable(&state);
	octeon_sha256_store_hash(sctx);

	__octeon_sha256_update(sctx, padding, pad_len);

	/* Append length (beक्रमe padding). */
	__octeon_sha256_update(sctx, (स्थिर u8 *)&bits, माप(bits));

	octeon_sha256_पढ़ो_hash(sctx);
	octeon_crypto_disable(&state, flags);

	/* Store state in digest */
	क्रम (i = 0; i < 8; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Zeroize sensitive inक्रमmation. */
	स_रखो(sctx, 0, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha224_final(काष्ठा shash_desc *desc, u8 *hash)
अणु
	u8 D[SHA256_DIGEST_SIZE];

	octeon_sha256_final(desc, D);

	स_नकल(hash, D, SHA224_DIGEST_SIZE);
	memzero_explicit(D, SHA256_DIGEST_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha256_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha256_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg octeon_sha256_algs[2] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	octeon_sha256_init,
	.update		=	octeon_sha256_update,
	.final		=	octeon_sha256_final,
	.export		=	octeon_sha256_export,
	.import		=	octeon_sha256_import,
	.descsize	=	माप(काष्ठा sha256_state),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name=	"octeon-sha256",
		.cra_priority	=	OCTEON_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	octeon_sha224_init,
	.update		=	octeon_sha256_update,
	.final		=	octeon_sha224_final,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name=	"octeon-sha224",
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init octeon_sha256_mod_init(व्योम)
अणु
	अगर (!octeon_has_crypto())
		वापस -ENOTSUPP;
	वापस crypto_रेजिस्टर_shashes(octeon_sha256_algs,
				       ARRAY_SIZE(octeon_sha256_algs));
पूर्ण

अटल व्योम __निकास octeon_sha256_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(octeon_sha256_algs,
				  ARRAY_SIZE(octeon_sha256_algs));
पूर्ण

module_init(octeon_sha256_mod_init);
module_निकास(octeon_sha256_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA-224 and SHA-256 Secure Hash Algorithm (OCTEON)");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
