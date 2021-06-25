<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम SHA512 hashing optimized क्रम sparc64 crypto opcodes.
 *
 * This is based largely upon crypto/sha512_generic.c
 *
 * Copyright (c) Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) 2003 Kyle McMartin <kyle@debian.org>
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

यंत्रlinkage व्योम sha512_sparc64_transक्रमm(u64 *digest, स्थिर अक्षर *data,
					 अचिन्हित पूर्णांक rounds);

अटल पूर्णांक sha512_sparc64_init(काष्ठा shash_desc *desc)
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

अटल पूर्णांक sha384_sparc64_init(काष्ठा shash_desc *desc)
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

अटल व्योम __sha512_sparc64_update(काष्ठा sha512_state *sctx, स्थिर u8 *data,
				    अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक partial)
अणु
	अचिन्हित पूर्णांक करोne = 0;

	अगर ((sctx->count[0] += len) < len)
		sctx->count[1]++;
	अगर (partial) अणु
		करोne = SHA512_BLOCK_SIZE - partial;
		स_नकल(sctx->buf + partial, data, करोne);
		sha512_sparc64_transक्रमm(sctx->state, sctx->buf, 1);
	पूर्ण
	अगर (len - करोne >= SHA512_BLOCK_SIZE) अणु
		स्थिर अचिन्हित पूर्णांक rounds = (len - करोne) / SHA512_BLOCK_SIZE;

		sha512_sparc64_transक्रमm(sctx->state, data + करोne, rounds);
		करोne += rounds * SHA512_BLOCK_SIZE;
	पूर्ण

	स_नकल(sctx->buf, data + करोne, len - करोne);
पूर्ण

अटल पूर्णांक sha512_sparc64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->count[0] % SHA512_BLOCK_SIZE;

	/* Handle the fast हाल right here */
	अगर (partial + len < SHA512_BLOCK_SIZE) अणु
		अगर ((sctx->count[0] += len) < len)
			sctx->count[1]++;
		स_नकल(sctx->buf + partial, data, len);
	पूर्ण अन्यथा
		__sha512_sparc64_update(sctx, data, len, partial);

	वापस 0;
पूर्ण

अटल पूर्णांक sha512_sparc64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक i, index, padlen;
	__be64 *dst = (__be64 *)out;
	__be64 bits[2];
	अटल स्थिर u8 padding[SHA512_BLOCK_SIZE] = अणु 0x80, पूर्ण;

	/* Save number of bits */
	bits[1] = cpu_to_be64(sctx->count[0] << 3);
	bits[0] = cpu_to_be64(sctx->count[1] << 3 | sctx->count[0] >> 61);

	/* Pad out to 112 mod 128 and append length */
	index = sctx->count[0] % SHA512_BLOCK_SIZE;
	padlen = (index < 112) ? (112 - index) : ((SHA512_BLOCK_SIZE+112) - index);

	/* We need to fill a whole block क्रम __sha512_sparc64_update() */
	अगर (padlen <= 112) अणु
		अगर ((sctx->count[0] += padlen) < padlen)
			sctx->count[1]++;
		स_नकल(sctx->buf + index, padding, padlen);
	पूर्ण अन्यथा अणु
		__sha512_sparc64_update(sctx, padding, padlen, index);
	पूर्ण
	__sha512_sparc64_update(sctx, (स्थिर u8 *)&bits, माप(bits), 112);

	/* Store state in digest */
	क्रम (i = 0; i < 8; i++)
		dst[i] = cpu_to_be64(sctx->state[i]);

	/* Wipe context */
	स_रखो(sctx, 0, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sha384_sparc64_final(काष्ठा shash_desc *desc, u8 *hash)
अणु
	u8 D[64];

	sha512_sparc64_final(desc, D);

	स_नकल(hash, D, 48);
	memzero_explicit(D, 64);

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha512 = अणु
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_sparc64_init,
	.update		=	sha512_sparc64_update,
	.final		=	sha512_sparc64_final,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha512",
		.cra_driver_name=	"sha512-sparc64",
		.cra_priority	=	SPARC_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA512_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा shash_alg sha384 = अणु
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_sparc64_init,
	.update		=	sha512_sparc64_update,
	.final		=	sha384_sparc64_final,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha384",
		.cra_driver_name=	"sha384-sparc64",
		.cra_priority	=	SPARC_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA384_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_sha512_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_SHA512))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init sha512_sparc64_mod_init(व्योम)
अणु
	अगर (sparc64_has_sha512_opcode()) अणु
		पूर्णांक ret = crypto_रेजिस्टर_shash(&sha384);
		अगर (ret < 0)
			वापस ret;

		ret = crypto_रेजिस्टर_shash(&sha512);
		अगर (ret < 0) अणु
			crypto_unरेजिस्टर_shash(&sha384);
			वापस ret;
		पूर्ण

		pr_info("Using sparc64 sha512 opcode optimized SHA-512/SHA-384 implementation\n");
		वापस 0;
	पूर्ण
	pr_info("sparc64 sha512 opcode not available.\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sha512_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sha384);
	crypto_unरेजिस्टर_shash(&sha512);
पूर्ण

module_init(sha512_sparc64_mod_init);
module_निकास(sha512_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA-384 and SHA-512 Secure Hash Algorithm, sparc64 sha512 opcode accelerated");

MODULE_ALIAS_CRYPTO("sha384");
MODULE_ALIAS_CRYPTO("sha512");

#समावेश "crop_devid.c"
