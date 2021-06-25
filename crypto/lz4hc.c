<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 *
 * Copyright (c) 2013 Chanho Min <chanho.min@lge.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/lz4.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>

काष्ठा lz4hc_ctx अणु
	व्योम *lz4hc_comp_mem;
पूर्ण;

अटल व्योम *lz4hc_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	व्योम *ctx;

	ctx = vदो_स्मृति(LZ4HC_MEM_COMPRESS);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	वापस ctx;
पूर्ण

अटल पूर्णांक lz4hc_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा lz4hc_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->lz4hc_comp_mem = lz4hc_alloc_ctx(शून्य);
	अगर (IS_ERR(ctx->lz4hc_comp_mem))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम lz4hc_मुक्त_ctx(काष्ठा crypto_scomp *tfm, व्योम *ctx)
अणु
	vमुक्त(ctx);
पूर्ण

अटल व्योम lz4hc_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा lz4hc_ctx *ctx = crypto_tfm_ctx(tfm);

	lz4hc_मुक्त_ctx(शून्य, ctx->lz4hc_comp_mem);
पूर्ण

अटल पूर्णांक __lz4hc_compress_crypto(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				   u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	पूर्णांक out_len = LZ4_compress_HC(src, dst, slen,
		*dlen, LZ4HC_DEFAULT_CLEVEL, ctx);

	अगर (!out_len)
		वापस -EINVAL;

	*dlen = out_len;
	वापस 0;
पूर्ण

अटल पूर्णांक lz4hc_scompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			   व्योम *ctx)
अणु
	वापस __lz4hc_compress_crypto(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक lz4hc_compress_crypto(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
				 अचिन्हित पूर्णांक slen, u8 *dst,
				 अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा lz4hc_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस __lz4hc_compress_crypto(src, slen, dst, dlen,
					ctx->lz4hc_comp_mem);
पूर्ण

अटल पूर्णांक __lz4hc_decompress_crypto(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				     u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	पूर्णांक out_len = LZ4_decompress_safe(src, dst, slen, *dlen);

	अगर (out_len < 0)
		वापस -EINVAL;

	*dlen = out_len;
	वापस 0;
पूर्ण

अटल पूर्णांक lz4hc_sdecompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			     अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			     व्योम *ctx)
अणु
	वापस __lz4hc_decompress_crypto(src, slen, dst, dlen, शून्य);
पूर्ण

अटल पूर्णांक lz4hc_decompress_crypto(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
				   अचिन्हित पूर्णांक slen, u8 *dst,
				   अचिन्हित पूर्णांक *dlen)
अणु
	वापस __lz4hc_decompress_crypto(src, slen, dst, dlen, शून्य);
पूर्ण

अटल काष्ठा crypto_alg alg_lz4hc = अणु
	.cra_name		= "lz4hc",
	.cra_driver_name	= "lz4hc-generic",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा lz4hc_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= lz4hc_init,
	.cra_निकास		= lz4hc_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress		= lz4hc_compress_crypto,
	.coa_decompress		= lz4hc_decompress_crypto पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg scomp = अणु
	.alloc_ctx		= lz4hc_alloc_ctx,
	.मुक्त_ctx		= lz4hc_मुक्त_ctx,
	.compress		= lz4hc_scompress,
	.decompress		= lz4hc_sdecompress,
	.base			= अणु
		.cra_name	= "lz4hc",
		.cra_driver_name = "lz4hc-scomp",
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init lz4hc_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_alg(&alg_lz4hc);
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_scomp(&scomp);
	अगर (ret) अणु
		crypto_unरेजिस्टर_alg(&alg_lz4hc);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास lz4hc_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg_lz4hc);
	crypto_unरेजिस्टर_scomp(&scomp);
पूर्ण

subsys_initcall(lz4hc_mod_init);
module_निकास(lz4hc_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LZ4HC Compression Algorithm");
MODULE_ALIAS_CRYPTO("lz4hc");
