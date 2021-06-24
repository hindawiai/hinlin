<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/xxhash.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा XXHASH64_BLOCK_SIZE	32
#घोषणा XXHASH64_DIGEST_SIZE	8

काष्ठा xxhash64_tfm_ctx अणु
	u64 seed;
पूर्ण;

काष्ठा xxhash64_desc_ctx अणु
	काष्ठा xxh64_state xxhstate;
पूर्ण;

अटल पूर्णांक xxhash64_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा xxhash64_tfm_ctx *tctx = crypto_shash_ctx(tfm);

	अगर (keylen != माप(tctx->seed))
		वापस -EINVAL;
	tctx->seed = get_unaligned_le64(key);
	वापस 0;
पूर्ण

अटल पूर्णांक xxhash64_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा xxhash64_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	xxh64_reset(&dctx->xxhstate, tctx->seed);

	वापस 0;
पूर्ण

अटल पूर्णांक xxhash64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length)
अणु
	काष्ठा xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	xxh64_update(&dctx->xxhstate, data, length);

	वापस 0;
पूर्ण

अटल पूर्णांक xxhash64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	put_unaligned_le64(xxh64_digest(&dctx->xxhstate), out);

	वापस 0;
पूर्ण

अटल पूर्णांक xxhash64_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length, u8 *out)
अणु
	काष्ठा xxhash64_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);

	put_unaligned_le64(xxh64(data, length, tctx->seed), out);

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	= XXHASH64_DIGEST_SIZE,
	.setkey		= xxhash64_setkey,
	.init		= xxhash64_init,
	.update		= xxhash64_update,
	.final		= xxhash64_final,
	.digest		= xxhash64_digest,
	.descsize	= माप(काष्ठा xxhash64_desc_ctx),
	.base		= अणु
		.cra_name	 = "xxhash64",
		.cra_driver_name = "xxhash64-generic",
		.cra_priority	 = 100,
		.cra_flags	 = CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize	 = XXHASH64_BLOCK_SIZE,
		.cra_ctxsize	 = माप(काष्ठा xxhash64_tfm_ctx),
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init xxhash_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास xxhash_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(xxhash_mod_init);
module_निकास(xxhash_mod_fini);

MODULE_AUTHOR("Nikolay Borisov <nborisov@suse.com>");
MODULE_DESCRIPTION("xxhash calculations wrapper for lib/xxhash.c");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("xxhash64");
MODULE_ALIAS_CRYPTO("xxhash64-generic");
