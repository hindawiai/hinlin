<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * घातerpc implementation of the SHA1 Secure Hash Algorithm.
 *
 * Derived from cryptoapi implementation, adapted क्रम in-place
 * scatterlist पूर्णांकerface.
 *
 * Derived from "crypto/sha1.c"
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha1.h>
#समावेश <यंत्र/byteorder.h>

व्योम घातerpc_sha_transक्रमm(u32 *state, स्थिर u8 *src);

अटल पूर्णांक घातerpc_sha1_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	*sctx = (काष्ठा sha1_state)अणु
		.state = अणु SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4 पूर्ण,
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक घातerpc_sha1_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial, करोne;
	स्थिर u8 *src;

	partial = sctx->count & 0x3f;
	sctx->count += len;
	करोne = 0;
	src = data;

	अगर ((partial + len) > 63) अणु

		अगर (partial) अणु
			करोne = -partial;
			स_नकल(sctx->buffer + partial, data, करोne + 64);
			src = sctx->buffer;
		पूर्ण

		करो अणु
			घातerpc_sha_transक्रमm(sctx->state, src);
			करोne += 64;
			src = data + करोne;
		पूर्ण जबतक (करोne + 63 < len);

		partial = 0;
	पूर्ण
	स_नकल(sctx->buffer + partial, src, len - करोne);

	वापस 0;
पूर्ण


/* Add padding and वापस the message digest. */
अटल पूर्णांक घातerpc_sha1_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	__be32 *dst = (__be32 *)out;
	u32 i, index, padlen;
	__be64 bits;
	अटल स्थिर u8 padding[64] = अणु 0x80, पूर्ण;

	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64 */
	index = sctx->count & 0x3f;
	padlen = (index < 56) ? (56 - index) : ((64+56) - index);
	घातerpc_sha1_update(desc, padding, padlen);

	/* Append length */
	घातerpc_sha1_update(desc, (स्थिर u8 *)&bits, माप(bits));

	/* Store state in digest */
	क्रम (i = 0; i < 5; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Wipe context */
	स_रखो(sctx, 0, माप *sctx);

	वापस 0;
पूर्ण

अटल पूर्णांक घातerpc_sha1_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक घातerpc_sha1_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	घातerpc_sha1_init,
	.update		=	घातerpc_sha1_update,
	.final		=	घातerpc_sha1_final,
	.export		=	घातerpc_sha1_export,
	.import		=	घातerpc_sha1_import,
	.descsize	=	माप(काष्ठा sha1_state),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"sha1-powerpc",
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha1_घातerpc_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास sha1_घातerpc_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(sha1_घातerpc_mod_init);
module_निकास(sha1_घातerpc_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm");

MODULE_ALIAS_CRYPTO("sha1");
MODULE_ALIAS_CRYPTO("sha1-powerpc");
