<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम SHA256 hashing optimized क्रम sparc64 crypto opcodes.
 *
 * This is based largely upon crypto/sha256_generic.c
 *
 * Copyright (c) Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * SHA224 Support Copyright 2007 Intel Corporation <jonathan.lynch@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha2.h>

#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

यंत्रlinkage व्योम sha256_sparc64_transक्रमm(u32 *digest, स्थिर अक्षर *data,
					 अचिन्हित पूर्णांक rounds);

अटल पूर्णांक sha224_sparc64_init(काष्ठा shash_desc *desc)
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

अटल पूर्णांक sha256_sparc64_init(काष्ठा shash_desc *desc)
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

अटल व्योम __sha256_sparc64_update(काष्ठा sha256_state *sctx, स्थिर u8 *data,
				    अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक partial)
अणु
	अचिन्हित पूर्णांक करोne = 0;

	sctx->count += len;
	अगर (partial) अणु
		करोne = SHA256_BLOCK_SIZE - partial;
		स_नकल(sctx->buf + partial, data, करोne);
		sha256_sparc64_transक्रमm(sctx->state, sctx->buf, 1);
	पूर्ण
	अगर (len - करोne >= SHA256_BLOCK_SIZE) अणु
		स्थिर अचिन्हित पूर्णांक rounds = (len - करोne) / SHA256_BLOCK_SIZE;

		sha256_sparc64_transक्रमm(sctx->state, data + करोne, rounds);
		करोne += rounds * SHA256_BLOCK_SIZE;
	पूर्ण

	स_नकल(sctx->buf, data + करोne, len - करोne);
पूर्ण

अटल पूर्णांक sha256_sparc64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->count % SHA256_BLOCK_SIZE;

	/* Handle the fast हाल right here */
	अगर (partial + len < SHA256_BLOCK_SIZE) अणु
		sctx->count += len;
		स_नकल(sctx->buf + partial, data, len);
	पूर्ण अन्यथा
		__sha256_sparc64_update(sctx, data, len, partial);

	वापस 0;
पूर्ण

अटल पूर्णांक sha256_sparc64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक i, index, padlen;
	__be32 *dst = (__be32 *)out;
	__be64 bits;
	अटल स्थिर u8 padding[SHA256_BLOCK_SIZE] = अणु 0x80, पूर्ण;

	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64 and append length */
	index = sctx->count % SHA256_BLOCK_SIZE;
	padlen = (index < 56) ? (56 - index) : ((SHA256_BLOCK_SIZE+56) - index);

	/* We need to fill a whole block क्रम __sha256_sparc64_update() */
	अगर (padlen <= 56) अणु
		sctx->count += padlen;
		स_नकल(sctx->buf + index, padding, padlen);
	पूर्ण अन्यथा अणु
		__sha256_sparc64_update(sctx, padding, padlen, index);
	पूर्ण
	__sha256_sparc64_update(sctx, (स्थिर u8 *)&bits, माप(bits), 56);

	/* Store state in digest */
	क्रम (i = 0; i < 8; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Wipe context */
	स_रखो(sctx, 0, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sha224_sparc64_final(काष्ठा shash_desc *desc, u8 *hash)
अणु
	u8 D[SHA256_DIGEST_SIZE];

	sha256_sparc64_final(desc, D);

	स_नकल(hash, D, SHA224_DIGEST_SIZE);
	memzero_explicit(D, SHA256_DIGEST_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक sha256_sparc64_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक sha256_sparc64_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha256_alg = अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_sparc64_init,
	.update		=	sha256_sparc64_update,
	.final		=	sha256_sparc64_final,
	.export		=	sha256_sparc64_export,
	.import		=	sha256_sparc64_import,
	.descsize	=	माप(काष्ठा sha256_state),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name=	"sha256-sparc64",
		.cra_priority	=	SPARC_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा shash_alg sha224_alg = अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_sparc64_init,
	.update		=	sha256_sparc64_update,
	.final		=	sha224_sparc64_final,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name=	"sha224-sparc64",
		.cra_priority	=	SPARC_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_sha256_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_SHA256))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init sha256_sparc64_mod_init(व्योम)
अणु
	अगर (sparc64_has_sha256_opcode()) अणु
		पूर्णांक ret = crypto_रेजिस्टर_shash(&sha224_alg);
		अगर (ret < 0)
			वापस ret;

		ret = crypto_रेजिस्टर_shash(&sha256_alg);
		अगर (ret < 0) अणु
			crypto_unरेजिस्टर_shash(&sha224_alg);
			वापस ret;
		पूर्ण

		pr_info("Using sparc64 sha256 opcode optimized SHA-256/SHA-224 implementation\n");
		वापस 0;
	पूर्ण
	pr_info("sparc64 sha256 opcode not available.\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sha256_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sha224_alg);
	crypto_unरेजिस्टर_shash(&sha256_alg);
पूर्ण

module_init(sha256_sparc64_mod_init);
module_निकास(sha256_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA-224 and SHA-256 Secure Hash Algorithm, sparc64 sha256 opcode accelerated");

MODULE_ALIAS_CRYPTO("sha224");
MODULE_ALIAS_CRYPTO("sha256");

#समावेश "crop_devid.c"
