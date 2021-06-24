<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * SHA-512 and SHA-384 Secure Hash Algorithm.
 *
 * Adapted क्रम OCTEON by Aaro Koskinen <aaro.koskinen@iki.fi>.
 *
 * Based on crypto/sha512_generic.c, which is:
 *
 * Copyright (c) Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) 2003 Kyle McMartin <kyle@debian.org>
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

अटल व्योम octeon_sha512_store_hash(काष्ठा sha512_state *sctx)
अणु
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[0], 0);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[1], 1);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[2], 2);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[3], 3);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[4], 4);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[5], 5);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[6], 6);
	ग_लिखो_octeon_64bit_hash_sha512(sctx->state[7], 7);
पूर्ण

अटल व्योम octeon_sha512_पढ़ो_hash(काष्ठा sha512_state *sctx)
अणु
	sctx->state[0] = पढ़ो_octeon_64bit_hash_sha512(0);
	sctx->state[1] = पढ़ो_octeon_64bit_hash_sha512(1);
	sctx->state[2] = पढ़ो_octeon_64bit_hash_sha512(2);
	sctx->state[3] = पढ़ो_octeon_64bit_hash_sha512(3);
	sctx->state[4] = पढ़ो_octeon_64bit_hash_sha512(4);
	sctx->state[5] = पढ़ो_octeon_64bit_hash_sha512(5);
	sctx->state[6] = पढ़ो_octeon_64bit_hash_sha512(6);
	sctx->state[7] = पढ़ो_octeon_64bit_hash_sha512(7);
पूर्ण

अटल व्योम octeon_sha512_transक्रमm(स्थिर व्योम *_block)
अणु
	स्थिर u64 *block = _block;

	ग_लिखो_octeon_64bit_block_sha512(block[0], 0);
	ग_लिखो_octeon_64bit_block_sha512(block[1], 1);
	ग_लिखो_octeon_64bit_block_sha512(block[2], 2);
	ग_लिखो_octeon_64bit_block_sha512(block[3], 3);
	ग_लिखो_octeon_64bit_block_sha512(block[4], 4);
	ग_लिखो_octeon_64bit_block_sha512(block[5], 5);
	ग_लिखो_octeon_64bit_block_sha512(block[6], 6);
	ग_लिखो_octeon_64bit_block_sha512(block[7], 7);
	ग_लिखो_octeon_64bit_block_sha512(block[8], 8);
	ग_लिखो_octeon_64bit_block_sha512(block[9], 9);
	ग_लिखो_octeon_64bit_block_sha512(block[10], 10);
	ग_लिखो_octeon_64bit_block_sha512(block[11], 11);
	ग_लिखो_octeon_64bit_block_sha512(block[12], 12);
	ग_लिखो_octeon_64bit_block_sha512(block[13], 13);
	ग_लिखो_octeon_64bit_block_sha512(block[14], 14);
	octeon_sha512_start(block[15]);
पूर्ण

अटल पूर्णांक octeon_sha512_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA512_H0;
	sctx->state[1] = SHA512_H1;
	sctx->state[2] = SHA512_H2;
	sctx->state[3] = SHA512_H3;
	sctx->state[4] = SHA512_H4;
	sctx->state[5] = SHA512_H5;
	sctx->state[6] = SHA512_H6;
	sctx->state[7] = SHA512_H7;
	sctx->count[0] = sctx->count[1] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha384_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA384_H0;
	sctx->state[1] = SHA384_H1;
	sctx->state[2] = SHA384_H2;
	sctx->state[3] = SHA384_H3;
	sctx->state[4] = SHA384_H4;
	sctx->state[5] = SHA384_H5;
	sctx->state[6] = SHA384_H6;
	sctx->state[7] = SHA384_H7;
	sctx->count[0] = sctx->count[1] = 0;

	वापस 0;
पूर्ण

अटल व्योम __octeon_sha512_update(काष्ठा sha512_state *sctx, स्थिर u8 *data,
				   अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक part_len;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक i;

	/* Compute number of bytes mod 128. */
	index = sctx->count[0] % SHA512_BLOCK_SIZE;

	/* Update number of bytes. */
	अगर ((sctx->count[0] += len) < len)
		sctx->count[1]++;

	part_len = SHA512_BLOCK_SIZE - index;

	/* Transक्रमm as many बार as possible. */
	अगर (len >= part_len) अणु
		स_नकल(&sctx->buf[index], data, part_len);
		octeon_sha512_transक्रमm(sctx->buf);

		क्रम (i = part_len; i + SHA512_BLOCK_SIZE <= len;
			i += SHA512_BLOCK_SIZE)
			octeon_sha512_transक्रमm(&data[i]);

		index = 0;
	पूर्ण अन्यथा अणु
		i = 0;
	पूर्ण

	/* Buffer reमुख्यing input. */
	स_नकल(&sctx->buf[index], &data[i], len - i);
पूर्ण

अटल पूर्णांक octeon_sha512_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	काष्ठा octeon_cop2_state state;
	अचिन्हित दीर्घ flags;

	/*
	 * Small updates never reach the crypto engine, so the generic sha512 is
	 * faster because of the heavyweight octeon_crypto_enable() /
	 * octeon_crypto_disable().
	 */
	अगर ((sctx->count[0] % SHA512_BLOCK_SIZE) + len < SHA512_BLOCK_SIZE)
		वापस crypto_sha512_update(desc, data, len);

	flags = octeon_crypto_enable(&state);
	octeon_sha512_store_hash(sctx);

	__octeon_sha512_update(sctx, data, len);

	octeon_sha512_पढ़ो_hash(sctx);
	octeon_crypto_disable(&state, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha512_final(काष्ठा shash_desc *desc, u8 *hash)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	अटल u8 padding[128] = अणु 0x80, पूर्ण;
	काष्ठा octeon_cop2_state state;
	__be64 *dst = (__be64 *)hash;
	अचिन्हित पूर्णांक pad_len;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक index;
	__be64 bits[2];
	पूर्णांक i;

	/* Save number of bits. */
	bits[1] = cpu_to_be64(sctx->count[0] << 3);
	bits[0] = cpu_to_be64(sctx->count[1] << 3 | sctx->count[0] >> 61);

	/* Pad out to 112 mod 128. */
	index = sctx->count[0] & 0x7f;
	pad_len = (index < 112) ? (112 - index) : ((128+112) - index);

	flags = octeon_crypto_enable(&state);
	octeon_sha512_store_hash(sctx);

	__octeon_sha512_update(sctx, padding, pad_len);

	/* Append length (beक्रमe padding). */
	__octeon_sha512_update(sctx, (स्थिर u8 *)bits, माप(bits));

	octeon_sha512_पढ़ो_hash(sctx);
	octeon_crypto_disable(&state, flags);

	/* Store state in digest. */
	क्रम (i = 0; i < 8; i++)
		dst[i] = cpu_to_be64(sctx->state[i]);

	/* Zeroize sensitive inक्रमmation. */
	स_रखो(sctx, 0, माप(काष्ठा sha512_state));

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha384_final(काष्ठा shash_desc *desc, u8 *hash)
अणु
	u8 D[64];

	octeon_sha512_final(desc, D);

	स_नकल(hash, D, 48);
	memzero_explicit(D, 64);

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg octeon_sha512_algs[2] = अणु अणु
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	octeon_sha512_init,
	.update		=	octeon_sha512_update,
	.final		=	octeon_sha512_final,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha512",
		.cra_driver_name=	"octeon-sha512",
		.cra_priority	=	OCTEON_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA512_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	octeon_sha384_init,
	.update		=	octeon_sha512_update,
	.final		=	octeon_sha384_final,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha384",
		.cra_driver_name=	"octeon-sha384",
		.cra_priority	=	OCTEON_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA384_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init octeon_sha512_mod_init(व्योम)
अणु
	अगर (!octeon_has_crypto())
		वापस -ENOTSUPP;
	वापस crypto_रेजिस्टर_shashes(octeon_sha512_algs,
				       ARRAY_SIZE(octeon_sha512_algs));
पूर्ण

अटल व्योम __निकास octeon_sha512_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(octeon_sha512_algs,
				  ARRAY_SIZE(octeon_sha512_algs));
पूर्ण

module_init(octeon_sha512_mod_init);
module_निकास(octeon_sha512_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA-512 and SHA-384 Secure Hash Algorithms (OCTEON)");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
