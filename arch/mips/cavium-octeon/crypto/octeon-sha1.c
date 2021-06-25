<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * SHA1 Secure Hash Algorithm.
 *
 * Adapted क्रम OCTEON by Aaro Koskinen <aaro.koskinen@iki.fi>.
 *
 * Based on crypto/sha1_generic.c, which is:
 *
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 */

#समावेश <linux/mm.h>
#समावेश <crypto/sha1.h>
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

अटल व्योम octeon_sha1_store_hash(काष्ठा sha1_state *sctx)
अणु
	u64 *hash = (u64 *)sctx->state;
	जोड़ अणु
		u32 word[2];
		u64 dword;
	पूर्ण hash_tail = अणु अणु sctx->state[4], पूर्ण पूर्ण;

	ग_लिखो_octeon_64bit_hash_dword(hash[0], 0);
	ग_लिखो_octeon_64bit_hash_dword(hash[1], 1);
	ग_लिखो_octeon_64bit_hash_dword(hash_tail.dword, 2);
	memzero_explicit(&hash_tail.word[0], माप(hash_tail.word[0]));
पूर्ण

अटल व्योम octeon_sha1_पढ़ो_hash(काष्ठा sha1_state *sctx)
अणु
	u64 *hash = (u64 *)sctx->state;
	जोड़ अणु
		u32 word[2];
		u64 dword;
	पूर्ण hash_tail;

	hash[0]		= पढ़ो_octeon_64bit_hash_dword(0);
	hash[1]		= पढ़ो_octeon_64bit_hash_dword(1);
	hash_tail.dword	= पढ़ो_octeon_64bit_hash_dword(2);
	sctx->state[4]	= hash_tail.word[0];
	memzero_explicit(&hash_tail.dword, माप(hash_tail.dword));
पूर्ण

अटल व्योम octeon_sha1_transक्रमm(स्थिर व्योम *_block)
अणु
	स्थिर u64 *block = _block;

	ग_लिखो_octeon_64bit_block_dword(block[0], 0);
	ग_लिखो_octeon_64bit_block_dword(block[1], 1);
	ग_लिखो_octeon_64bit_block_dword(block[2], 2);
	ग_लिखो_octeon_64bit_block_dword(block[3], 3);
	ग_लिखो_octeon_64bit_block_dword(block[4], 4);
	ग_लिखो_octeon_64bit_block_dword(block[5], 5);
	ग_लिखो_octeon_64bit_block_dword(block[6], 6);
	octeon_sha1_start(block[7]);
पूर्ण

अटल पूर्णांक octeon_sha1_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA1_H0;
	sctx->state[1] = SHA1_H1;
	sctx->state[2] = SHA1_H2;
	sctx->state[3] = SHA1_H3;
	sctx->state[4] = SHA1_H4;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल व्योम __octeon_sha1_update(काष्ठा sha1_state *sctx, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक partial;
	अचिन्हित पूर्णांक करोne;
	स्थिर u8 *src;

	partial = sctx->count % SHA1_BLOCK_SIZE;
	sctx->count += len;
	करोne = 0;
	src = data;

	अगर ((partial + len) >= SHA1_BLOCK_SIZE) अणु
		अगर (partial) अणु
			करोne = -partial;
			स_नकल(sctx->buffer + partial, data,
			       करोne + SHA1_BLOCK_SIZE);
			src = sctx->buffer;
		पूर्ण

		करो अणु
			octeon_sha1_transक्रमm(src);
			करोne += SHA1_BLOCK_SIZE;
			src = data + करोne;
		पूर्ण जबतक (करोne + SHA1_BLOCK_SIZE <= len);

		partial = 0;
	पूर्ण
	स_नकल(sctx->buffer + partial, src, len - करोne);
पूर्ण

अटल पूर्णांक octeon_sha1_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	काष्ठा octeon_cop2_state state;
	अचिन्हित दीर्घ flags;

	/*
	 * Small updates never reach the crypto engine, so the generic sha1 is
	 * faster because of the heavyweight octeon_crypto_enable() /
	 * octeon_crypto_disable().
	 */
	अगर ((sctx->count % SHA1_BLOCK_SIZE) + len < SHA1_BLOCK_SIZE)
		वापस crypto_sha1_update(desc, data, len);

	flags = octeon_crypto_enable(&state);
	octeon_sha1_store_hash(sctx);

	__octeon_sha1_update(sctx, data, len);

	octeon_sha1_पढ़ो_hash(sctx);
	octeon_crypto_disable(&state, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha1_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
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
	octeon_sha1_store_hash(sctx);

	__octeon_sha1_update(sctx, padding, pad_len);

	/* Append length (beक्रमe padding). */
	__octeon_sha1_update(sctx, (स्थिर u8 *)&bits, माप(bits));

	octeon_sha1_पढ़ो_hash(sctx);
	octeon_crypto_disable(&state, flags);

	/* Store state in digest */
	क्रम (i = 0; i < 5; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Zeroize sensitive inक्रमmation. */
	स_रखो(sctx, 0, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha1_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_sha1_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg octeon_sha1_alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	octeon_sha1_init,
	.update		=	octeon_sha1_update,
	.final		=	octeon_sha1_final,
	.export		=	octeon_sha1_export,
	.import		=	octeon_sha1_import,
	.descsize	=	माप(काष्ठा sha1_state),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"octeon-sha1",
		.cra_priority	=	OCTEON_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init octeon_sha1_mod_init(व्योम)
अणु
	अगर (!octeon_has_crypto())
		वापस -ENOTSUPP;
	वापस crypto_रेजिस्टर_shash(&octeon_sha1_alg);
पूर्ण

अटल व्योम __निकास octeon_sha1_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&octeon_sha1_alg);
पूर्ण

module_init(octeon_sha1_mod_init);
module_निकास(octeon_sha1_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm (OCTEON)");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
