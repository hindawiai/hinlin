<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम SHA1 hashing optimized क्रम sparc64 crypto opcodes.
 *
 * This is based largely upon arch/x86/crypto/sha1_ssse3_glue.c
 *
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) Mathias Krause <minipli@googlemail.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha1.h>

#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

यंत्रlinkage व्योम sha1_sparc64_transक्रमm(u32 *digest, स्थिर अक्षर *data,
				       अचिन्हित पूर्णांक rounds);

अटल पूर्णांक sha1_sparc64_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	*sctx = (काष्ठा sha1_state)अणु
		.state = अणु SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4 पूर्ण,
	पूर्ण;

	वापस 0;
पूर्ण

अटल व्योम __sha1_sparc64_update(काष्ठा sha1_state *sctx, स्थिर u8 *data,
				  अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक partial)
अणु
	अचिन्हित पूर्णांक करोne = 0;

	sctx->count += len;
	अगर (partial) अणु
		करोne = SHA1_BLOCK_SIZE - partial;
		स_नकल(sctx->buffer + partial, data, करोne);
		sha1_sparc64_transक्रमm(sctx->state, sctx->buffer, 1);
	पूर्ण
	अगर (len - करोne >= SHA1_BLOCK_SIZE) अणु
		स्थिर अचिन्हित पूर्णांक rounds = (len - करोne) / SHA1_BLOCK_SIZE;

		sha1_sparc64_transक्रमm(sctx->state, data + करोne, rounds);
		करोne += rounds * SHA1_BLOCK_SIZE;
	पूर्ण

	स_नकल(sctx->buffer, data + करोne, len - करोne);
पूर्ण

अटल पूर्णांक sha1_sparc64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->count % SHA1_BLOCK_SIZE;

	/* Handle the fast हाल right here */
	अगर (partial + len < SHA1_BLOCK_SIZE) अणु
		sctx->count += len;
		स_नकल(sctx->buffer + partial, data, len);
	पूर्ण अन्यथा
		__sha1_sparc64_update(sctx, data, len, partial);

	वापस 0;
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक sha1_sparc64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक i, index, padlen;
	__be32 *dst = (__be32 *)out;
	__be64 bits;
	अटल स्थिर u8 padding[SHA1_BLOCK_SIZE] = अणु 0x80, पूर्ण;

	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64 and append length */
	index = sctx->count % SHA1_BLOCK_SIZE;
	padlen = (index < 56) ? (56 - index) : ((SHA1_BLOCK_SIZE+56) - index);

	/* We need to fill a whole block क्रम __sha1_sparc64_update() */
	अगर (padlen <= 56) अणु
		sctx->count += padlen;
		स_नकल(sctx->buffer + index, padding, padlen);
	पूर्ण अन्यथा अणु
		__sha1_sparc64_update(sctx, padding, padlen, index);
	पूर्ण
	__sha1_sparc64_update(sctx, (स्थिर u8 *)&bits, माप(bits), 56);

	/* Store state in digest */
	क्रम (i = 0; i < 5; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Wipe context */
	स_रखो(sctx, 0, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sha1_sparc64_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sha1_sparc64_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_sparc64_init,
	.update		=	sha1_sparc64_update,
	.final		=	sha1_sparc64_final,
	.export		=	sha1_sparc64_export,
	.import		=	sha1_sparc64_import,
	.descsize	=	माप(काष्ठा sha1_state),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"sha1-sparc64",
		.cra_priority	=	SPARC_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_sha1_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_SHA1))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init sha1_sparc64_mod_init(व्योम)
अणु
	अगर (sparc64_has_sha1_opcode()) अणु
		pr_info("Using sparc64 sha1 opcode optimized SHA-1 implementation\n");
		वापस crypto_रेजिस्टर_shash(&alg);
	पूर्ण
	pr_info("sparc64 sha1 opcode not available.\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sha1_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(sha1_sparc64_mod_init);
module_निकास(sha1_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm, sparc64 sha1 opcode accelerated");

MODULE_ALIAS_CRYPTO("sha1");

#समावेश "crop_devid.c"
