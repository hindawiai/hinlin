<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/lzo.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>

काष्ठा lzo_ctx अणु
	व्योम *lzo_comp_mem;
पूर्ण;

अटल व्योम *lzo_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	व्योम *ctx;

	ctx = kvदो_स्मृति(LZO1X_MEM_COMPRESS, GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	वापस ctx;
पूर्ण

अटल पूर्णांक lzo_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा lzo_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->lzo_comp_mem = lzo_alloc_ctx(शून्य);
	अगर (IS_ERR(ctx->lzo_comp_mem))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम lzo_मुक्त_ctx(काष्ठा crypto_scomp *tfm, व्योम *ctx)
अणु
	kvमुक्त(ctx);
पूर्ण

अटल व्योम lzo_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा lzo_ctx *ctx = crypto_tfm_ctx(tfm);

	lzo_मुक्त_ctx(शून्य, ctx->lzo_comp_mem);
पूर्ण

अटल पूर्णांक __lzo_compress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			  u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	माप_प्रकार पंचांगp_len = *dlen; /* माप_प्रकार(uदीर्घ) <-> uपूर्णांक on 64 bit */
	पूर्णांक err;

	err = lzo1x_1_compress(src, slen, dst, &पंचांगp_len, ctx);

	अगर (err != LZO_E_OK)
		वापस -EINVAL;

	*dlen = पंचांगp_len;
	वापस 0;
पूर्ण

अटल पूर्णांक lzo_compress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा lzo_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस __lzo_compress(src, slen, dst, dlen, ctx->lzo_comp_mem);
पूर्ण

अटल पूर्णांक lzo_scompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			 अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			 व्योम *ctx)
अणु
	वापस __lzo_compress(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक __lzo_decompress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			    u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	पूर्णांक err;
	माप_प्रकार पंचांगp_len = *dlen; /* माप_प्रकार(uदीर्घ) <-> uपूर्णांक on 64 bit */

	err = lzo1x_decompress_safe(src, slen, dst, &पंचांगp_len);

	अगर (err != LZO_E_OK)
		वापस -EINVAL;

	*dlen = पंचांगp_len;
	वापस 0;
पूर्ण

अटल पूर्णांक lzo_decompress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			  अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	वापस __lzo_decompress(src, slen, dst, dlen);
पूर्ण

अटल पूर्णांक lzo_sdecompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			   व्योम *ctx)
अणु
	वापस __lzo_decompress(src, slen, dst, dlen);
पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name		= "lzo",
	.cra_driver_name	= "lzo-generic",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा lzo_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= lzo_init,
	.cra_निकास		= lzo_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress		= lzo_compress,
	.coa_decompress		= lzo_decompress पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg scomp = अणु
	.alloc_ctx		= lzo_alloc_ctx,
	.मुक्त_ctx		= lzo_मुक्त_ctx,
	.compress		= lzo_scompress,
	.decompress		= lzo_sdecompress,
	.base			= अणु
		.cra_name	= "lzo",
		.cra_driver_name = "lzo-scomp",
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init lzo_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_alg(&alg);
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_scomp(&scomp);
	अगर (ret) अणु
		crypto_unरेजिस्टर_alg(&alg);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास lzo_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
	crypto_unरेजिस्टर_scomp(&scomp);
पूर्ण

subsys_initcall(lzo_mod_init);
module_निकास(lzo_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LZO Compression Algorithm");
MODULE_ALIAS_CRYPTO("lzo");
