<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Deflate algorithm (RFC 1951), implemented here primarily क्रम use
 * by IPCOMP (RFC 3173 & RFC 2394).
 *
 * Copyright (c) 2003 James Morris <jmorris@पूर्णांकercode.com.au>
 *
 * FIXME: deflate transक्रमms will require up to a total of about 436k of kernel
 * memory on i386 (390k क्रम compression, the rest क्रम decompression), as the
 * current zlib kernel code uses a worst हाल pre-allocation प्रणाली by शेष.
 * This needs to be fixed so that the amount of memory required is properly
 * related to the  winbits and memlevel parameters.
 *
 * The शेष winbits of 11 should suit most packets, and it may be something
 * to configure on a per-tfm basis in the future.
 *
 * Currently, compression history is not मुख्यtained between tfm calls, as
 * it is not needed क्रम IPCOMP and keeps the code simpler.  It can be
 * implemented अगर someone wants it.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/zlib.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/net.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>

#घोषणा DEFLATE_DEF_LEVEL		Z_DEFAULT_COMPRESSION
#घोषणा DEFLATE_DEF_WINBITS		11
#घोषणा DEFLATE_DEF_MEMLEVEL		MAX_MEM_LEVEL

काष्ठा deflate_ctx अणु
	काष्ठा z_stream_s comp_stream;
	काष्ठा z_stream_s decomp_stream;
पूर्ण;

अटल पूर्णांक deflate_comp_init(काष्ठा deflate_ctx *ctx, पूर्णांक क्रमmat)
अणु
	पूर्णांक ret = 0;
	काष्ठा z_stream_s *stream = &ctx->comp_stream;

	stream->workspace = vzalloc(zlib_deflate_workspacesize(
				    MAX_WBITS, MAX_MEM_LEVEL));
	अगर (!stream->workspace) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (क्रमmat)
		ret = zlib_deflateInit(stream, 3);
	अन्यथा
		ret = zlib_deflateInit2(stream, DEFLATE_DEF_LEVEL, Z_DEFLATED,
					-DEFLATE_DEF_WINBITS,
					DEFLATE_DEF_MEMLEVEL,
					Z_DEFAULT_STRATEGY);
	अगर (ret != Z_OK) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
out:
	वापस ret;
out_मुक्त:
	vमुक्त(stream->workspace);
	जाओ out;
पूर्ण

अटल पूर्णांक deflate_decomp_init(काष्ठा deflate_ctx *ctx, पूर्णांक क्रमmat)
अणु
	पूर्णांक ret = 0;
	काष्ठा z_stream_s *stream = &ctx->decomp_stream;

	stream->workspace = vzalloc(zlib_inflate_workspacesize());
	अगर (!stream->workspace) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (क्रमmat)
		ret = zlib_inflateInit(stream);
	अन्यथा
		ret = zlib_inflateInit2(stream, -DEFLATE_DEF_WINBITS);
	अगर (ret != Z_OK) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
out:
	वापस ret;
out_मुक्त:
	vमुक्त(stream->workspace);
	जाओ out;
पूर्ण

अटल व्योम deflate_comp_निकास(काष्ठा deflate_ctx *ctx)
अणु
	zlib_deflateEnd(&ctx->comp_stream);
	vमुक्त(ctx->comp_stream.workspace);
पूर्ण

अटल व्योम deflate_decomp_निकास(काष्ठा deflate_ctx *ctx)
अणु
	zlib_inflateEnd(&ctx->decomp_stream);
	vमुक्त(ctx->decomp_stream.workspace);
पूर्ण

अटल पूर्णांक __deflate_init(व्योम *ctx, पूर्णांक क्रमmat)
अणु
	पूर्णांक ret;

	ret = deflate_comp_init(ctx, क्रमmat);
	अगर (ret)
		जाओ out;
	ret = deflate_decomp_init(ctx, क्रमmat);
	अगर (ret)
		deflate_comp_निकास(ctx);
out:
	वापस ret;
पूर्ण

अटल व्योम *gen_deflate_alloc_ctx(काष्ठा crypto_scomp *tfm, पूर्णांक क्रमmat)
अणु
	काष्ठा deflate_ctx *ctx;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ret = __deflate_init(ctx, क्रमmat);
	अगर (ret) अणु
		kमुक्त(ctx);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस ctx;
पूर्ण

अटल व्योम *deflate_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	वापस gen_deflate_alloc_ctx(tfm, 0);
पूर्ण

अटल व्योम *zlib_deflate_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	वापस gen_deflate_alloc_ctx(tfm, 1);
पूर्ण

अटल पूर्णांक deflate_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा deflate_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस __deflate_init(ctx, 0);
पूर्ण

अटल व्योम __deflate_निकास(व्योम *ctx)
अणु
	deflate_comp_निकास(ctx);
	deflate_decomp_निकास(ctx);
पूर्ण

अटल व्योम deflate_मुक्त_ctx(काष्ठा crypto_scomp *tfm, व्योम *ctx)
अणु
	__deflate_निकास(ctx);
	kमुक्त_sensitive(ctx);
पूर्ण

अटल व्योम deflate_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा deflate_ctx *ctx = crypto_tfm_ctx(tfm);

	__deflate_निकास(ctx);
पूर्ण

अटल पूर्णांक __deflate_compress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			      u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	पूर्णांक ret = 0;
	काष्ठा deflate_ctx *dctx = ctx;
	काष्ठा z_stream_s *stream = &dctx->comp_stream;

	ret = zlib_deflateReset(stream);
	अगर (ret != Z_OK) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	stream->next_in = (u8 *)src;
	stream->avail_in = slen;
	stream->next_out = (u8 *)dst;
	stream->avail_out = *dlen;

	ret = zlib_deflate(stream, Z_FINISH);
	अगर (ret != Z_STREAM_END) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = 0;
	*dlen = stream->total_out;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक deflate_compress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			    अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा deflate_ctx *dctx = crypto_tfm_ctx(tfm);

	वापस __deflate_compress(src, slen, dst, dlen, dctx);
पूर्ण

अटल पूर्णांक deflate_scompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			     अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			     व्योम *ctx)
अणु
	वापस __deflate_compress(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक __deflate_decompress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु

	पूर्णांक ret = 0;
	काष्ठा deflate_ctx *dctx = ctx;
	काष्ठा z_stream_s *stream = &dctx->decomp_stream;

	ret = zlib_inflateReset(stream);
	अगर (ret != Z_OK) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	stream->next_in = (u8 *)src;
	stream->avail_in = slen;
	stream->next_out = (u8 *)dst;
	stream->avail_out = *dlen;

	ret = zlib_inflate(stream, Z_SYNC_FLUSH);
	/*
	 * Work around a bug in zlib, which someबार wants to taste an extra
	 * byte when being used in the (unकरोcumented) raw deflate mode.
	 * (From USAGI).
	 */
	अगर (ret == Z_OK && !stream->avail_in && stream->avail_out) अणु
		u8 zerostuff = 0;
		stream->next_in = &zerostuff;
		stream->avail_in = 1;
		ret = zlib_inflate(stream, Z_FINISH);
	पूर्ण
	अगर (ret != Z_STREAM_END) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = 0;
	*dlen = stream->total_out;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक deflate_decompress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			      अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा deflate_ctx *dctx = crypto_tfm_ctx(tfm);

	वापस __deflate_decompress(src, slen, dst, dlen, dctx);
पूर्ण

अटल पूर्णांक deflate_sdecompress(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			       अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			       व्योम *ctx)
अणु
	वापस __deflate_decompress(src, slen, dst, dlen, ctx);
पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name		= "deflate",
	.cra_driver_name	= "deflate-generic",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा deflate_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= deflate_init,
	.cra_निकास		= deflate_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress 		= deflate_compress,
	.coa_decompress  	= deflate_decompress पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg scomp[] = अणु अणु
	.alloc_ctx		= deflate_alloc_ctx,
	.मुक्त_ctx		= deflate_मुक्त_ctx,
	.compress		= deflate_scompress,
	.decompress		= deflate_sdecompress,
	.base			= अणु
		.cra_name	= "deflate",
		.cra_driver_name = "deflate-scomp",
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.alloc_ctx		= zlib_deflate_alloc_ctx,
	.मुक्त_ctx		= deflate_मुक्त_ctx,
	.compress		= deflate_scompress,
	.decompress		= deflate_sdecompress,
	.base			= अणु
		.cra_name	= "zlib-deflate",
		.cra_driver_name = "zlib-deflate-scomp",
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init deflate_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_alg(&alg);
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_scomps(scomp, ARRAY_SIZE(scomp));
	अगर (ret) अणु
		crypto_unरेजिस्टर_alg(&alg);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास deflate_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
	crypto_unरेजिस्टर_scomps(scomp, ARRAY_SIZE(scomp));
पूर्ण

subsys_initcall(deflate_mod_init);
module_निकास(deflate_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Deflate Compression Algorithm for IPCOMP");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");
MODULE_ALIAS_CRYPTO("deflate");
