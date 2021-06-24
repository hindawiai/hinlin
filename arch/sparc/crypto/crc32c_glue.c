<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Glue code क्रम CRC32C optimized क्रम sparc64 crypto opcodes.
 *
 * This is based largely upon arch/x86/crypto/crc32c-पूर्णांकel.c
 *
 * Copyright (C) 2008 Intel Corporation
 * Authors: Austin Zhang <austin_zhang@linux.पूर्णांकel.com>
 *          Kent Liu <kent.liu@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/crc32.h>

#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>

#समावेश "opcodes.h"

/*
 * Setting the seed allows arbitrary accumulators and flexible XOR policy
 * If your algorithm starts with ~0, then XOR with ~0 beक्रमe you set
 * the seed.
 */
अटल पूर्णांक crc32c_sparc64_setkey(काष्ठा crypto_shash *hash, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	u32 *mctx = crypto_shash_ctx(hash);

	अगर (keylen != माप(u32))
		वापस -EINVAL;
	*mctx = le32_to_cpup((__le32 *)key);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_sparc64_init(काष्ठा shash_desc *desc)
अणु
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = *mctx;

	वापस 0;
पूर्ण

बाह्य व्योम crc32c_sparc64(u32 *crcp, स्थिर u64 *data, अचिन्हित पूर्णांक len);

अटल व्योम crc32c_compute(u32 *crcp, स्थिर u64 *data, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक यंत्र_len;

	यंत्र_len = len & ~7U;
	अगर (यंत्र_len) अणु
		crc32c_sparc64(crcp, data, यंत्र_len);
		data += यंत्र_len / 8;
		len -= यंत्र_len;
	पूर्ण
	अगर (len)
		*crcp = __crc32c_le(*crcp, (स्थिर अचिन्हित अक्षर *) data, len);
पूर्ण

अटल पूर्णांक crc32c_sparc64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	crc32c_compute(crcp, (स्थिर u64 *) data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक __crc32c_sparc64_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len,
				  u8 *out)
अणु
	u32 पंचांगp = *crcp;

	crc32c_compute(&पंचांगp, (स्थिर u64 *) data, len);

	*(__le32 *) out = ~cpu_to_le32(पंचांगp);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_sparc64_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
				अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_sparc64_finup(shash_desc_ctx(desc), data, len, out);
पूर्ण

अटल पूर्णांक crc32c_sparc64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*(__le32 *) out = ~cpu_to_le32p(crcp);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_sparc64_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_sparc64_finup(crypto_shash_ctx(desc->tfm), data, len,
				      out);
पूर्ण

अटल पूर्णांक crc32c_sparc64_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = ~0;

	वापस 0;
पूर्ण

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

अटल काष्ठा shash_alg alg = अणु
	.setkey			=	crc32c_sparc64_setkey,
	.init			=	crc32c_sparc64_init,
	.update			=	crc32c_sparc64_update,
	.final			=	crc32c_sparc64_final,
	.finup			=	crc32c_sparc64_finup,
	.digest			=	crc32c_sparc64_digest,
	.descsize		=	माप(u32),
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.base			=	अणु
		.cra_name		=	"crc32c",
		.cra_driver_name	=	"crc32c-sparc64",
		.cra_priority		=	SPARC_CR_OPCODE_PRIORITY,
		.cra_flags		=	CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		=	CHKSUM_BLOCK_SIZE,
		.cra_ctxsize		=	माप(u32),
		.cra_alignmask		=	7,
		.cra_module		=	THIS_MODULE,
		.cra_init		=	crc32c_sparc64_cra_init,
	पूर्ण
पूर्ण;

अटल bool __init sparc64_has_crc32c_opcode(व्योम)
अणु
	अचिन्हित दीर्घ cfr;

	अगर (!(sparc64_elf_hwcap & HWCAP_SPARC_CRYPTO))
		वापस false;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
	अगर (!(cfr & CFR_CRC32C))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init crc32c_sparc64_mod_init(व्योम)
अणु
	अगर (sparc64_has_crc32c_opcode()) अणु
		pr_info("Using sparc64 crc32c opcode optimized CRC32C implementation\n");
		वापस crypto_रेजिस्टर_shash(&alg);
	पूर्ण
	pr_info("sparc64 crc32c opcode not available.\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास crc32c_sparc64_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(crc32c_sparc64_mod_init);
module_निकास(crc32c_sparc64_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CRC32c (Castagnoli), sparc64 crc32c opcode accelerated");

MODULE_ALIAS_CRYPTO("crc32c");

#समावेश "crop_devid.c"
