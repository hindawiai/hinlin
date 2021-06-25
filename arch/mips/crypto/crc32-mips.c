<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * crc32-mips.c - CRC32 and CRC32C using optional MIPSr6 inकाष्ठाions
 *
 * Module based on arm64/crypto/crc32-arm.c
 *
 * Copyright (C) 2014 Linaro Ltd <yazen.ghannam@linaro.org>
 * Copyright (C) 2018 MIPS Tech, LLC
 */

#समावेश <linux/unaligned/access_ok.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/mipsregs.h>

#समावेश <crypto/पूर्णांकernal/hash.h>

क्रमागत crc_op_size अणु
	b, h, w, d,
पूर्ण;

क्रमागत crc_type अणु
	crc32,
	crc32c,
पूर्ण;

#अगर_अघोषित TOOLCHAIN_SUPPORTS_CRC
#घोषणा _ASM_MACRO_CRC32(OP, SZ, TYPE)					  \
_ASM_MACRO_3R(OP, rt, rs, rt2,						  \
	".ifnc	\\rt, \\rt2\n\t"					  \
	".error	\"invalid operands \\\"" #OP " \\rt,\\rs,\\rt2\\\"\"\n\t" \
	".endif\n\t"							  \
	_ASM_INSN_IF_MIPS(0x7c00000f | (__rt << 16) | (__rs << 21) |	  \
			  ((SZ) <<  6) | ((TYPE) << 8))			  \
	_ASM_INSN32_IF_MM(0x00000030 | (__rs << 16) | (__rt << 21) |	  \
			  ((SZ) << 14) | ((TYPE) << 3)))
_ASM_MACRO_CRC32(crc32b,  0, 0);
_ASM_MACRO_CRC32(crc32h,  1, 0);
_ASM_MACRO_CRC32(crc32w,  2, 0);
_ASM_MACRO_CRC32(crc32d,  3, 0);
_ASM_MACRO_CRC32(crc32cb, 0, 1);
_ASM_MACRO_CRC32(crc32ch, 1, 1);
_ASM_MACRO_CRC32(crc32cw, 2, 1);
_ASM_MACRO_CRC32(crc32cd, 3, 1);
#घोषणा _ASM_SET_CRC ""
#अन्यथा /* !TOOLCHAIN_SUPPORTS_CRC */
#घोषणा _ASM_SET_CRC ".set\tcrc\n\t"
#पूर्ण_अगर

#घोषणा _CRC32(crc, value, size, type)		\
करो अणु						\
	__यंत्र__ __अस्थिर__(			\
		".set	push\n\t"		\
		_ASM_SET_CRC			\
		#type #size "	%0, %1, %0\n\t"	\
		".set	pop"			\
		: "+r" (crc)			\
		: "r" (value));			\
पूर्ण जबतक (0)

#घोषणा CRC32(crc, value, size) \
	_CRC32(crc, value, size, crc32)

#घोषणा CRC32C(crc, value, size) \
	_CRC32(crc, value, size, crc32c)

अटल u32 crc32_mips_le_hw(u32 crc_, स्थिर u8 *p, अचिन्हित पूर्णांक len)
अणु
	u32 crc = crc_;

#अगर_घोषित CONFIG_64BIT
	जबतक (len >= माप(u64)) अणु
		u64 value = get_unaligned_le64(p);

		CRC32(crc, value, d);
		p += माप(u64);
		len -= माप(u64);
	पूर्ण

	अगर (len & माप(u32)) अणु
#अन्यथा /* !CONFIG_64BIT */
	जबतक (len >= माप(u32)) अणु
#पूर्ण_अगर
		u32 value = get_unaligned_le32(p);

		CRC32(crc, value, w);
		p += माप(u32);
		len -= माप(u32);
	पूर्ण

	अगर (len & माप(u16)) अणु
		u16 value = get_unaligned_le16(p);

		CRC32(crc, value, h);
		p += माप(u16);
	पूर्ण

	अगर (len & माप(u8)) अणु
		u8 value = *p++;

		CRC32(crc, value, b);
	पूर्ण

	वापस crc;
पूर्ण

अटल u32 crc32c_mips_le_hw(u32 crc_, स्थिर u8 *p, अचिन्हित पूर्णांक len)
अणु
	u32 crc = crc_;

#अगर_घोषित CONFIG_64BIT
	जबतक (len >= माप(u64)) अणु
		u64 value = get_unaligned_le64(p);

		CRC32C(crc, value, d);
		p += माप(u64);
		len -= माप(u64);
	पूर्ण

	अगर (len & माप(u32)) अणु
#अन्यथा /* !CONFIG_64BIT */
	जबतक (len >= माप(u32)) अणु
#पूर्ण_अगर
		u32 value = get_unaligned_le32(p);

		CRC32C(crc, value, w);
		p += माप(u32);
		len -= माप(u32);
	पूर्ण

	अगर (len & माप(u16)) अणु
		u16 value = get_unaligned_le16(p);

		CRC32C(crc, value, h);
		p += माप(u16);
	पूर्ण

	अगर (len & माप(u8)) अणु
		u8 value = *p++;

		CRC32C(crc, value, b);
	पूर्ण
	वापस crc;
पूर्ण

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

काष्ठा chksum_ctx अणु
	u32 key;
पूर्ण;

काष्ठा chksum_desc_ctx अणु
	u32 crc;
पूर्ण;

अटल पूर्णांक chksum_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा chksum_ctx *mctx = crypto_shash_ctx(desc->tfm);
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = mctx->key;

	वापस 0;
पूर्ण

/*
 * Setting the seed allows arbitrary accumulators and flexible XOR policy
 * If your algorithm starts with ~0, then XOR with ~0 beक्रमe you set
 * the seed.
 */
अटल पूर्णांक chksum_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chksum_ctx *mctx = crypto_shash_ctx(tfm);

	अगर (keylen != माप(mctx->key))
		वापस -EINVAL;
	mctx->key = get_unaligned_le32(key);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = crc32_mips_le_hw(ctx->crc, data, length);
	वापस 0;
पूर्ण

अटल पूर्णांक chksumc_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = crc32c_mips_le_hw(ctx->crc, data, length);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	put_unaligned_le32(ctx->crc, out);
	वापस 0;
पूर्ण

अटल पूर्णांक chksumc_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	put_unaligned_le32(~ctx->crc, out);
	वापस 0;
पूर्ण

अटल पूर्णांक __chksum_finup(u32 crc, स्थिर u8 *data, अचिन्हित पूर्णांक len, u8 *out)
अणु
	put_unaligned_le32(crc32_mips_le_hw(crc, data, len), out);
	वापस 0;
पूर्ण

अटल पूर्णांक __chksumc_finup(u32 crc, स्थिर u8 *data, अचिन्हित पूर्णांक len, u8 *out)
अणु
	put_unaligned_le32(~crc32c_mips_le_hw(crc, data, len), out);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	वापस __chksum_finup(ctx->crc, data, len, out);
पूर्ण

अटल पूर्णांक chksumc_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	वापस __chksumc_finup(ctx->crc, data, len, out);
पूर्ण

अटल पूर्णांक chksum_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length, u8 *out)
अणु
	काष्ठा chksum_ctx *mctx = crypto_shash_ctx(desc->tfm);

	वापस __chksum_finup(mctx->key, data, length, out);
पूर्ण

अटल पूर्णांक chksumc_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length, u8 *out)
अणु
	काष्ठा chksum_ctx *mctx = crypto_shash_ctx(desc->tfm);

	वापस __chksumc_finup(mctx->key, data, length, out);
पूर्ण

अटल पूर्णांक chksum_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा chksum_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = ~0;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg crc32_alg = अणु
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.setkey			=	chksum_setkey,
	.init			=	chksum_init,
	.update			=	chksum_update,
	.final			=	chksum_final,
	.finup			=	chksum_finup,
	.digest			=	chksum_digest,
	.descsize		=	माप(काष्ठा chksum_desc_ctx),
	.base			=	अणु
		.cra_name		=	"crc32",
		.cra_driver_name	=	"crc32-mips-hw",
		.cra_priority		=	300,
		.cra_flags		=	CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		=	CHKSUM_BLOCK_SIZE,
		.cra_alignmask		=	0,
		.cra_ctxsize		=	माप(काष्ठा chksum_ctx),
		.cra_module		=	THIS_MODULE,
		.cra_init		=	chksum_cra_init,
	पूर्ण
पूर्ण;

अटल काष्ठा shash_alg crc32c_alg = अणु
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.setkey			=	chksum_setkey,
	.init			=	chksum_init,
	.update			=	chksumc_update,
	.final			=	chksumc_final,
	.finup			=	chksumc_finup,
	.digest			=	chksumc_digest,
	.descsize		=	माप(काष्ठा chksum_desc_ctx),
	.base			=	अणु
		.cra_name		=	"crc32c",
		.cra_driver_name	=	"crc32c-mips-hw",
		.cra_priority		=	300,
		.cra_flags		=	CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		=	CHKSUM_BLOCK_SIZE,
		.cra_alignmask		=	0,
		.cra_ctxsize		=	माप(काष्ठा chksum_ctx),
		.cra_module		=	THIS_MODULE,
		.cra_init		=	chksum_cra_init,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crc32_mod_init(व्योम)
अणु
	पूर्णांक err;

	err = crypto_रेजिस्टर_shash(&crc32_alg);

	अगर (err)
		वापस err;

	err = crypto_रेजिस्टर_shash(&crc32c_alg);

	अगर (err) अणु
		crypto_unरेजिस्टर_shash(&crc32_alg);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास crc32_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&crc32_alg);
	crypto_unरेजिस्टर_shash(&crc32c_alg);
पूर्ण

MODULE_AUTHOR("Marcin Nowakowski <marcin.nowakowski@mips.com");
MODULE_DESCRIPTION("CRC32 and CRC32C using optional MIPS instructions");
MODULE_LICENSE("GPL v2");

module_cpu_feature_match(MIPS_CRC32, crc32_mod_init);
module_निकास(crc32_mod_निकास);
