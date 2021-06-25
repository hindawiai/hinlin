<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * CRC32C chksum
 *
 *@Articleअणुcastagnoli-crc,
 * author =       अणु Guy Castagnoli and Stefan Braeuer and Martin Herrmanपूर्ण,
 * title =        अणुअणुOptimization of Cyclic Redundancy-Check Codes with 24
 *                 and 32 Parity Bitsपूर्णपूर्ण,
 * journal =      IEEE Transactions on Communication,
 * year =         अणु1993पूर्ण,
 * volume =       अणु41पूर्ण,
 * number =       अणु6पूर्ण,
 * pages =        अणुपूर्ण,
 * month =        अणुJuneपूर्ण,
 *पूर्ण
 * Used by the iSCSI driver, possibly others, and derived from
 * the iscsi-crc.c module of the linux-iscsi driver at
 * http://linux-iscsi.sourceक्रमge.net.
 *
 * Following the example of lib/crc32, this function is पूर्णांकended to be
 * flexible and useful क्रम all users.  Modules that currently have their
 * own crc32c, but hopefully may be able to use this one are:
 *  net/sctp (please add all your करोco to here अगर you change to
 *            use this one!)
 *  <enकरोflist>
 *
 * Copyright (c) 2004 Cisco Systems, Inc.
 * Copyright (c) 2008 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/crc32.h>

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

काष्ठा chksum_ctx अणु
	u32 key;
पूर्ण;

काष्ठा chksum_desc_ctx अणु
	u32 crc;
पूर्ण;

/*
 * Steps through buffer one byte at a समय, calculates reflected
 * crc using table.
 */

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

	ctx->crc = __crc32c_le(ctx->crc, data, length);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	put_unaligned_le32(~ctx->crc, out);
	वापस 0;
पूर्ण

अटल पूर्णांक __chksum_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len, u8 *out)
अणु
	put_unaligned_le32(~__crc32c_le(*crcp, data, len), out);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	वापस __chksum_finup(&ctx->crc, data, len, out);
पूर्ण

अटल पूर्णांक chksum_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length, u8 *out)
अणु
	काष्ठा chksum_ctx *mctx = crypto_shash_ctx(desc->tfm);

	वापस __chksum_finup(&mctx->key, data, length, out);
पूर्ण

अटल पूर्णांक crc32c_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा chksum_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = ~0;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.setkey			=	chksum_setkey,
	.init		=	chksum_init,
	.update		=	chksum_update,
	.final		=	chksum_final,
	.finup		=	chksum_finup,
	.digest		=	chksum_digest,
	.descsize		=	माप(काष्ठा chksum_desc_ctx),
	.base			=	अणु
		.cra_name		=	"crc32c",
		.cra_driver_name	=	"crc32c-generic",
		.cra_priority		=	100,
		.cra_flags		=	CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		=	CHKSUM_BLOCK_SIZE,
		.cra_ctxsize		=	माप(काष्ठा chksum_ctx),
		.cra_module		=	THIS_MODULE,
		.cra_init		=	crc32c_cra_init,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crc32c_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crc32c_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(crc32c_mod_init);
module_निकास(crc32c_mod_fini);

MODULE_AUTHOR("Clay Haapala <chaapala@cisco.com>");
MODULE_DESCRIPTION("CRC32c (Castagnoli) calculations wrapper for lib/crc32c");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("crc32c");
MODULE_ALIAS_CRYPTO("crc32c-generic");
