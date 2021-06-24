<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम MD5 hashing optimized क्रम sparc64 crypto opcodes.
 *
 * This is based largely upon arch/x86/crypto/sha1_ssse3_glue.c
 * and crypto/md5.c which are:
 *
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) Mathias Krause <minipli@googlemail.com>
 * Copyright (c) Cryptoapi developers.
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/md5.h>

#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

यंत्रlinkage व्योम md5_sparc64_transक्रमm(u32 *digest, स्थिर अक्षर *data,
				      अचिन्हित पूर्णांक rounds);

अटल पूर्णांक md5_sparc64_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = MD5_H0;
	mctx->hash[1] = MD5_H1;
	mctx->hash[2] = MD5_H2;
	mctx->hash[3] = MD5_H3;
	le32_to_cpu_array(mctx->hash, 4);
	mctx->byte_count = 0;

	वापस 0;
पूर्ण

अटल व्योम __md5_sparc64_update(काष्ठा md5_state *sctx, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक partial)
अणु
	अचिन्हित पूर्णांक करोne = 0;

	sctx->byte_count += len;
	अगर (partial) अणु
		करोne = MD5_HMAC_BLOCK_SIZE - partial;
		स_नकल((u8 *)sctx->block + partial, data, करोne);
		md5_sparc64_transक्रमm(sctx->hash, (u8 *)sctx->block, 1);
	पूर्ण
	अगर (len - करोne >= MD5_HMAC_BLOCK_SIZE) अणु
		स्थिर अचिन्हित पूर्णांक rounds = (len - करोne) / MD5_HMAC_BLOCK_SIZE;

		md5_sparc64_transक्रमm(sctx->hash, data + करोne, rounds);
		करोne += rounds * MD5_HMAC_BLOCK_SIZE;
	पूर्ण

	स_नकल(sctx->block, data + करोne, len - करोne);
पूर्ण

अटल पूर्णांक md5_sparc64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->byte_count % MD5_HMAC_BLOCK_SIZE;

	/* Handle the fast हाल right here */
	अगर (partial + len < MD5_HMAC_BLOCK_SIZE) अणु
		sctx->byte_count += len;
		स_नकल((u8 *)sctx->block + partial, data, len);
	पूर्ण अन्यथा
		__md5_sparc64_update(sctx, data, len, partial);

	वापस 0;
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक md5_sparc64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक i, index, padlen;
	u32 *dst = (u32 *)out;
	__le64 bits;
	अटल स्थिर u8 padding[MD5_HMAC_BLOCK_SIZE] = अणु 0x80, पूर्ण;

	bits = cpu_to_le64(sctx->byte_count << 3);

	/* Pad out to 56 mod 64 and append length */
	index = sctx->byte_count % MD5_HMAC_BLOCK_SIZE;
	padlen = (index < 56) ? (56 - index) : ((MD5_HMAC_BLOCK_SIZE+56) - index);

	/* We need to fill a whole block क्रम __md5_sparc64_update() */
	अगर (padlen <= 56) अणु
		sctx->byte_count += padlen;
		स_नकल((u8 *)sctx->block + index, padding, padlen);
	पूर्ण अन्यथा अणु
		__md5_sparc64_update(sctx, padding, padlen, index);
	पूर्ण
	__md5_sparc64_update(sctx, (स्थिर u8 *)&bits, माप(bits), 56);

	/* Store state in digest */
	क्रम (i = 0; i < MD5_HASH_WORDS; i++)
		dst[i] = sctx->hash[i];

	/* Wipe context */
	स_रखो(sctx, 0, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक md5_sparc64_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक md5_sparc64_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	md5_sparc64_init,
	.update		=	md5_sparc64_update,
	.final		=	md5_sparc64_final,
	.export		=	md5_sparc64_export,
	.import		=	md5_sparc64_import,
	.descsize	=	माप(काष्ठा md5_state),
	.statesize	=	माप(काष्ठा md5_state),
	.base		=	अणु
		.cra_name	=	"md5",
		.cra_driver_name=	"md5-sparc64",
		.cra_priority	=	SPARC_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	MD5_HMAC_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_md5_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_MD5))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init md5_sparc64_mod_init(व्योम)
अणु
	अगर (sparc64_has_md5_opcode()) अणु
		pr_info("Using sparc64 md5 opcode optimized MD5 implementation\n");
		वापस crypto_रेजिस्टर_shash(&alg);
	पूर्ण
	pr_info("sparc64 md5 opcode not available.\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास md5_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(md5_sparc64_mod_init);
module_निकास(md5_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MD5 Message Digest Algorithm, sparc64 md5 opcode accelerated");

MODULE_ALIAS_CRYPTO("md5");

#समावेश "crop_devid.c"
