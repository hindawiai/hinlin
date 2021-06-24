<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API क्रम the 842 software compression algorithm.
 *
 * Copyright (C) IBM Corporation, 2011-2015
 *
 * Original Authors: Robert Jennings <rcj@linux.vnet.ibm.com>
 *                   Seth Jennings <sjenning@linux.vnet.ibm.com>
 *
 * Reग_लिखो: Dan Streeपंचांगan <ddstreet@ieee.org>
 *
 * This is the software implementation of compression and decompression using
 * the 842 क्रमmat.  This uses the software 842 library at lib/842/ which is
 * only a reference implementation, and is very, very slow as compared to other
 * software compressors.  You probably करो not want to use this software
 * compression.  If you have access to the PowerPC 842 compression hardware, you
 * want to use the 842 hardware compression पूर्णांकerface, which is at:
 * drivers/crypto/nx/nx-842-crypto.c
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/sw842.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>

काष्ठा crypto842_ctx अणु
	व्योम *wmem;	/* working memory क्रम compress */
पूर्ण;

अटल व्योम *crypto842_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	व्योम *ctx;

	ctx = kदो_स्मृति(SW842_MEM_COMPRESS, GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	वापस ctx;
पूर्ण

अटल पूर्णांक crypto842_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto842_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->wmem = crypto842_alloc_ctx(शून्य);
	अगर (IS_ERR(ctx->wmem))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम crypto842_मुक्त_ctx(काष्ठा crypto_scomp *tfm, व्योम *ctx)
अणु
	kमुक्त(ctx);
पूर्ण

अटल व्योम crypto842_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto842_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto842_मुक्त_ctx(शून्य, ctx->wmem);
पूर्ण

अटल पूर्णांक crypto842_compress(काष्ठा crypto_tfm *tfm,
			      स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			      u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा crypto842_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस sw842_compress(src, slen, dst, dlen, ctx->wmem);
पूर्ण

अटल पूर्णांक crypto842_scompress(काष्ठा crypto_scomp *tfm,
			       स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			       u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	वापस sw842_compress(src, slen, dst, dlen, ctx);
पूर्ण

अटल पूर्णांक crypto842_decompress(काष्ठा crypto_tfm *tfm,
				स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	वापस sw842_decompress(src, slen, dst, dlen);
पूर्ण

अटल पूर्णांक crypto842_sdecompress(काष्ठा crypto_scomp *tfm,
				 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				 u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	वापस sw842_decompress(src, slen, dst, dlen);
पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name		= "842",
	.cra_driver_name	= "842-generic",
	.cra_priority		= 100,
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा crypto842_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= crypto842_init,
	.cra_निकास		= crypto842_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress		= crypto842_compress,
	.coa_decompress		= crypto842_decompress पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg scomp = अणु
	.alloc_ctx		= crypto842_alloc_ctx,
	.मुक्त_ctx		= crypto842_मुक्त_ctx,
	.compress		= crypto842_scompress,
	.decompress		= crypto842_sdecompress,
	.base			= अणु
		.cra_name	= "842",
		.cra_driver_name = "842-scomp",
		.cra_priority	 = 100,
		.cra_module	 = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crypto842_mod_init(व्योम)
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
subsys_initcall(crypto842_mod_init);

अटल व्योम __निकास crypto842_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
	crypto_unरेजिस्टर_scomp(&scomp);
पूर्ण
module_निकास(crypto842_mod_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("842 Software Compression Algorithm");
MODULE_ALIAS_CRYPTO("842");
MODULE_ALIAS_CRYPTO("842-generic");
MODULE_AUTHOR("Dan Streetman <ddstreet@ieee.org>");
