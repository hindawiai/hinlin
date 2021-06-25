<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 *
 * Copyright (c) 2017-present, Facebook, Inc.
 */
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/zstd.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>


#घोषणा ZSTD_DEF_LEVEL	3

काष्ठा zstd_ctx अणु
	ZSTD_CCtx *cctx;
	ZSTD_DCtx *dctx;
	व्योम *cwksp;
	व्योम *dwksp;
पूर्ण;

अटल ZSTD_parameters zstd_params(व्योम)
अणु
	वापस ZSTD_getParams(ZSTD_DEF_LEVEL, 0, 0);
पूर्ण

अटल पूर्णांक zstd_comp_init(काष्ठा zstd_ctx *ctx)
अणु
	पूर्णांक ret = 0;
	स्थिर ZSTD_parameters params = zstd_params();
	स्थिर माप_प्रकार wksp_size = ZSTD_CCtxWorkspaceBound(params.cParams);

	ctx->cwksp = vzalloc(wksp_size);
	अगर (!ctx->cwksp) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ctx->cctx = ZSTD_initCCtx(ctx->cwksp, wksp_size);
	अगर (!ctx->cctx) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
out:
	वापस ret;
out_मुक्त:
	vमुक्त(ctx->cwksp);
	जाओ out;
पूर्ण

अटल पूर्णांक zstd_decomp_init(काष्ठा zstd_ctx *ctx)
अणु
	पूर्णांक ret = 0;
	स्थिर माप_प्रकार wksp_size = ZSTD_DCtxWorkspaceBound();

	ctx->dwksp = vzalloc(wksp_size);
	अगर (!ctx->dwksp) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ctx->dctx = ZSTD_initDCtx(ctx->dwksp, wksp_size);
	अगर (!ctx->dctx) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
out:
	वापस ret;
out_मुक्त:
	vमुक्त(ctx->dwksp);
	जाओ out;
पूर्ण

अटल व्योम zstd_comp_निकास(काष्ठा zstd_ctx *ctx)
अणु
	vमुक्त(ctx->cwksp);
	ctx->cwksp = शून्य;
	ctx->cctx = शून्य;
पूर्ण

अटल व्योम zstd_decomp_निकास(काष्ठा zstd_ctx *ctx)
अणु
	vमुक्त(ctx->dwksp);
	ctx->dwksp = शून्य;
	ctx->dctx = शून्य;
पूर्ण

अटल पूर्णांक __zstd_init(व्योम *ctx)
अणु
	पूर्णांक ret;

	ret = zstd_comp_init(ctx);
	अगर (ret)
		वापस ret;
	ret = zstd_decomp_init(ctx);
	अगर (ret)
		zstd_comp_निकास(ctx);
	वापस ret;
पूर्ण

अटल व्योम *zstd_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	पूर्णांक ret;
	काष्ठा zstd_ctx *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ret = __zstd_init(ctx);
	अगर (ret) अणु
		kमुक्त(ctx);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस ctx;
पूर्ण

अटल पूर्णांक zstd_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा zstd_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस __zstd_init(ctx);
पूर्ण

अटल व्योम __zstd_निकास(व्योम *ctx)
अणु
	zstd_comp_निकास(ctx);
	zstd_decomp_निकास(ctx);
पूर्ण

अटल व्योम zstd_मुक्त_ctx(काष्ठा crypto_scomp *tfm, व्योम *ctx)
अणु
	__zstd_निकास(ctx);
	kमुक्त_sensitive(ctx);
पूर्ण

अटल व्योम zstd_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा zstd_ctx *ctx = crypto_tfm_ctx(tfm);

	__zstd_निकास(ctx);
पूर्ण

अटल पूर्णांक __zstd_compress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			   u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	माप_प्रकार out_len;
	काष्ठा zstd_ctx *zctx = ctx;
	स्थिर ZSTD_parameters params = zstd_params();

	out_len = ZSTD_compressCCtx(zctx->cctx, dst, *dlen, src, slen, params);
	अगर (ZSTD_isError(out_len))
		वापस -EINVAL;
	*dlen = out_len;
	वापस 0;
पूर्ण

अटल पूर्णांक zstd_compress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			 अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा zstd_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस __zstd_compress(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक zstd_scompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			  अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			  व्योम *ctx)
अणु
	वापस __zstd_compress(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक __zstd_decompress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			     u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	माप_प्रकार out_len;
	काष्ठा zstd_ctx *zctx = ctx;

	out_len = ZSTD_decompressDCtx(zctx->dctx, dst, *dlen, src, slen);
	अगर (ZSTD_isError(out_len))
		वापस -EINVAL;
	*dlen = out_len;
	वापस 0;
पूर्ण

अटल पूर्णांक zstd_decompress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा zstd_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस __zstd_decompress(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक zstd_sdecompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			    अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			    व्योम *ctx)
अणु
	वापस __zstd_decompress(src, slen, dst, dlen, ctx);
पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name		= "zstd",
	.cra_driver_name	= "zstd-generic",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा zstd_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= zstd_init,
	.cra_निकास		= zstd_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress		= zstd_compress,
	.coa_decompress		= zstd_decompress पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg scomp = अणु
	.alloc_ctx		= zstd_alloc_ctx,
	.मुक्त_ctx		= zstd_मुक्त_ctx,
	.compress		= zstd_scompress,
	.decompress		= zstd_sdecompress,
	.base			= अणु
		.cra_name	= "zstd",
		.cra_driver_name = "zstd-scomp",
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init zstd_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_alg(&alg);
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_scomp(&scomp);
	अगर (ret)
		crypto_unरेजिस्टर_alg(&alg);

	वापस ret;
पूर्ण

अटल व्योम __निकास zstd_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
	crypto_unरेजिस्टर_scomp(&scomp);
पूर्ण

subsys_initcall(zstd_mod_init);
module_निकास(zstd_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Zstd Compression Algorithm");
MODULE_ALIAS_CRYPTO("zstd");
