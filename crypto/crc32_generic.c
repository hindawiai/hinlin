<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Xyratex Technology Limited
 */

/*
 * This is crypto api shash wrappers to crc32_le.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/crc32.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

/** No शेष init with ~0 */
अटल पूर्णांक crc32_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = 0;

	वापस 0;
पूर्ण

/*
 * Setting the seed allows arbitrary accumulators and flexible XOR policy
 * If your algorithm starts with ~0, then XOR with ~0 beक्रमe you set
 * the seed.
 */
अटल पूर्णांक crc32_setkey(काष्ठा crypto_shash *hash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	u32 *mctx = crypto_shash_ctx(hash);

	अगर (keylen != माप(u32))
		वापस -EINVAL;
	*mctx = get_unaligned_le32(key);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_init(काष्ठा shash_desc *desc)
अणु
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = *mctx;

	वापस 0;
पूर्ण

अटल पूर्णांक crc32_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = crc32_le(*crcp, data, len);
	वापस 0;
पूर्ण

/* No final XOR 0xFFFFFFFF, like crc32_le */
अटल पूर्णांक __crc32_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len,
			 u8 *out)
अणु
	put_unaligned_le32(crc32_le(*crcp, data, len), out);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32_finup(shash_desc_ctx(desc), data, len, out);
पूर्ण

अटल पूर्णांक crc32_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	put_unaligned_le32(*crcp, out);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32_finup(crypto_shash_ctx(desc->tfm), data, len,
			     out);
पूर्ण
अटल काष्ठा shash_alg alg = अणु
	.setkey		= crc32_setkey,
	.init		= crc32_init,
	.update		= crc32_update,
	.final		= crc32_final,
	.finup		= crc32_finup,
	.digest		= crc32_digest,
	.descsize	= माप(u32),
	.digestsize	= CHKSUM_DIGEST_SIZE,
	.base		= अणु
		.cra_name		= "crc32",
		.cra_driver_name	= "crc32-generic",
		.cra_priority		= 100,
		.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		= CHKSUM_BLOCK_SIZE,
		.cra_ctxsize		= माप(u32),
		.cra_module		= THIS_MODULE,
		.cra_init		= crc32_cra_init,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crc32_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crc32_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(crc32_mod_init);
module_निकास(crc32_mod_fini);

MODULE_AUTHOR("Alexander Boyko <alexander_boyko@xyratex.com>");
MODULE_DESCRIPTION("CRC32 calculations wrapper for lib/crc32");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("crc32");
MODULE_ALIAS_CRYPTO("crc32-generic");
