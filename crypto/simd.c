<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Shared crypto simd helpers
 *
 * Copyright (c) 2012 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 * Copyright (c) 2016 Herbert Xu <herbert@gonकरोr.apana.org.au>
 * Copyright (c) 2019 Google LLC
 *
 * Based on aesni-पूर्णांकel_glue.c by:
 *  Copyright (C) 2008, Intel Corp.
 *    Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

/*
 * Shared crypto SIMD helpers.  These functions dynamically create and रेजिस्टर
 * an skcipher or AEAD algorithm that wraps another, पूर्णांकernal algorithm.  The
 * wrapper ensures that the पूर्णांकernal algorithm is only executed in a context
 * where SIMD inकाष्ठाions are usable, i.e. where may_use_simd() वापसs true.
 * If SIMD is alपढ़ोy usable, the wrapper directly calls the पूर्णांकernal algorithm.
 * Otherwise it defers execution to a workqueue via cryptd.
 *
 * This is an alternative to the पूर्णांकernal algorithm implementing a fallback क्रम
 * the !may_use_simd() हाल itself.
 *
 * Note that the wrapper algorithm is asynchronous, i.e. it has the
 * CRYPTO_ALG_ASYNC flag set.  Thereक्रमe it won't be found by users who
 * explicitly allocate a synchronous algorithm.
 */

#समावेश <crypto/cryptd.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <यंत्र/simd.h>

/* skcipher support */

काष्ठा simd_skcipher_alg अणु
	स्थिर अक्षर *ialg_name;
	काष्ठा skcipher_alg alg;
पूर्ण;

काष्ठा simd_skcipher_ctx अणु
	काष्ठा cryptd_skcipher *cryptd_tfm;
पूर्ण;

अटल पूर्णांक simd_skcipher_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा simd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *child = &ctx->cryptd_tfm->base;

	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(tfm) &
					 CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(child, key, key_len);
पूर्ण

अटल पूर्णांक simd_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा simd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_request *subreq;
	काष्ठा crypto_skcipher *child;

	subreq = skcipher_request_ctx(req);
	*subreq = *req;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_skcipher_queued(ctx->cryptd_tfm)))
		child = &ctx->cryptd_tfm->base;
	अन्यथा
		child = cryptd_skcipher_child(ctx->cryptd_tfm);

	skcipher_request_set_tfm(subreq, child);

	वापस crypto_skcipher_encrypt(subreq);
पूर्ण

अटल पूर्णांक simd_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा simd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_request *subreq;
	काष्ठा crypto_skcipher *child;

	subreq = skcipher_request_ctx(req);
	*subreq = *req;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_skcipher_queued(ctx->cryptd_tfm)))
		child = &ctx->cryptd_tfm->base;
	अन्यथा
		child = cryptd_skcipher_child(ctx->cryptd_tfm);

	skcipher_request_set_tfm(subreq, child);

	वापस crypto_skcipher_decrypt(subreq);
पूर्ण

अटल व्योम simd_skcipher_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा simd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	cryptd_मुक्त_skcipher(ctx->cryptd_tfm);
पूर्ण

अटल पूर्णांक simd_skcipher_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा simd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा cryptd_skcipher *cryptd_tfm;
	काष्ठा simd_skcipher_alg *salg;
	काष्ठा skcipher_alg *alg;
	अचिन्हित reqsize;

	alg = crypto_skcipher_alg(tfm);
	salg = container_of(alg, काष्ठा simd_skcipher_alg, alg);

	cryptd_tfm = cryptd_alloc_skcipher(salg->ialg_name,
					   CRYPTO_ALG_INTERNAL,
					   CRYPTO_ALG_INTERNAL);
	अगर (IS_ERR(cryptd_tfm))
		वापस PTR_ERR(cryptd_tfm);

	ctx->cryptd_tfm = cryptd_tfm;

	reqsize = crypto_skcipher_reqsize(cryptd_skcipher_child(cryptd_tfm));
	reqsize = max(reqsize, crypto_skcipher_reqsize(&cryptd_tfm->base));
	reqsize += माप(काष्ठा skcipher_request);

	crypto_skcipher_set_reqsize(tfm, reqsize);

	वापस 0;
पूर्ण

काष्ठा simd_skcipher_alg *simd_skcipher_create_compat(स्थिर अक्षर *algname,
						      स्थिर अक्षर *drvname,
						      स्थिर अक्षर *basename)
अणु
	काष्ठा simd_skcipher_alg *salg;
	काष्ठा crypto_skcipher *tfm;
	काष्ठा skcipher_alg *ialg;
	काष्ठा skcipher_alg *alg;
	पूर्णांक err;

	tfm = crypto_alloc_skcipher(basename, CRYPTO_ALG_INTERNAL,
				    CRYPTO_ALG_INTERNAL | CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		वापस ERR_CAST(tfm);

	ialg = crypto_skcipher_alg(tfm);

	salg = kzalloc(माप(*salg), GFP_KERNEL);
	अगर (!salg) अणु
		salg = ERR_PTR(-ENOMEM);
		जाओ out_put_tfm;
	पूर्ण

	salg->ialg_name = basename;
	alg = &salg->alg;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", algname) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ out_मुक्त_salg;

	अगर (snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		     drvname) >= CRYPTO_MAX_ALG_NAME)
		जाओ out_मुक्त_salg;

	alg->base.cra_flags = CRYPTO_ALG_ASYNC |
		(ialg->base.cra_flags & CRYPTO_ALG_INHERITED_FLAGS);
	alg->base.cra_priority = ialg->base.cra_priority;
	alg->base.cra_blocksize = ialg->base.cra_blocksize;
	alg->base.cra_alignmask = ialg->base.cra_alignmask;
	alg->base.cra_module = ialg->base.cra_module;
	alg->base.cra_ctxsize = माप(काष्ठा simd_skcipher_ctx);

	alg->ivsize = ialg->ivsize;
	alg->chunksize = ialg->chunksize;
	alg->min_keysize = ialg->min_keysize;
	alg->max_keysize = ialg->max_keysize;

	alg->init = simd_skcipher_init;
	alg->निकास = simd_skcipher_निकास;

	alg->setkey = simd_skcipher_setkey;
	alg->encrypt = simd_skcipher_encrypt;
	alg->decrypt = simd_skcipher_decrypt;

	err = crypto_रेजिस्टर_skcipher(alg);
	अगर (err)
		जाओ out_मुक्त_salg;

out_put_tfm:
	crypto_मुक्त_skcipher(tfm);
	वापस salg;

out_मुक्त_salg:
	kमुक्त(salg);
	salg = ERR_PTR(err);
	जाओ out_put_tfm;
पूर्ण
EXPORT_SYMBOL_GPL(simd_skcipher_create_compat);

काष्ठा simd_skcipher_alg *simd_skcipher_create(स्थिर अक्षर *algname,
					       स्थिर अक्षर *basename)
अणु
	अक्षर drvname[CRYPTO_MAX_ALG_NAME];

	अगर (snम_लिखो(drvname, CRYPTO_MAX_ALG_NAME, "simd-%s", basename) >=
	    CRYPTO_MAX_ALG_NAME)
		वापस ERR_PTR(-ENAMETOOLONG);

	वापस simd_skcipher_create_compat(algname, drvname, basename);
पूर्ण
EXPORT_SYMBOL_GPL(simd_skcipher_create);

व्योम simd_skcipher_मुक्त(काष्ठा simd_skcipher_alg *salg)
अणु
	crypto_unरेजिस्टर_skcipher(&salg->alg);
	kमुक्त(salg);
पूर्ण
EXPORT_SYMBOL_GPL(simd_skcipher_मुक्त);

पूर्णांक simd_रेजिस्टर_skciphers_compat(काष्ठा skcipher_alg *algs, पूर्णांक count,
				   काष्ठा simd_skcipher_alg **simd_algs)
अणु
	पूर्णांक err;
	पूर्णांक i;
	स्थिर अक्षर *algname;
	स्थिर अक्षर *drvname;
	स्थिर अक्षर *basename;
	काष्ठा simd_skcipher_alg *simd;

	err = crypto_रेजिस्टर_skciphers(algs, count);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < count; i++) अणु
		WARN_ON(म_भेदन(algs[i].base.cra_name, "__", 2));
		WARN_ON(म_भेदन(algs[i].base.cra_driver_name, "__", 2));
		algname = algs[i].base.cra_name + 2;
		drvname = algs[i].base.cra_driver_name + 2;
		basename = algs[i].base.cra_driver_name;
		simd = simd_skcipher_create_compat(algname, drvname, basename);
		err = PTR_ERR(simd);
		अगर (IS_ERR(simd))
			जाओ err_unरेजिस्टर;
		simd_algs[i] = simd;
	पूर्ण
	वापस 0;

err_unरेजिस्टर:
	simd_unरेजिस्टर_skciphers(algs, count, simd_algs);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(simd_रेजिस्टर_skciphers_compat);

व्योम simd_unरेजिस्टर_skciphers(काष्ठा skcipher_alg *algs, पूर्णांक count,
			       काष्ठा simd_skcipher_alg **simd_algs)
अणु
	पूर्णांक i;

	crypto_unरेजिस्टर_skciphers(algs, count);

	क्रम (i = 0; i < count; i++) अणु
		अगर (simd_algs[i]) अणु
			simd_skcipher_मुक्त(simd_algs[i]);
			simd_algs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(simd_unरेजिस्टर_skciphers);

/* AEAD support */

काष्ठा simd_aead_alg अणु
	स्थिर अक्षर *ialg_name;
	काष्ठा aead_alg alg;
पूर्ण;

काष्ठा simd_aead_ctx अणु
	काष्ठा cryptd_aead *cryptd_tfm;
पूर्ण;

अटल पूर्णांक simd_aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा simd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *child = &ctx->cryptd_tfm->base;

	crypto_aead_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(child, crypto_aead_get_flags(tfm) &
				     CRYPTO_TFM_REQ_MASK);
	वापस crypto_aead_setkey(child, key, key_len);
पूर्ण

अटल पूर्णांक simd_aead_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा simd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *child = &ctx->cryptd_tfm->base;

	वापस crypto_aead_setauthsize(child, authsize);
पूर्ण

अटल पूर्णांक simd_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा simd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_request *subreq;
	काष्ठा crypto_aead *child;

	subreq = aead_request_ctx(req);
	*subreq = *req;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_aead_queued(ctx->cryptd_tfm)))
		child = &ctx->cryptd_tfm->base;
	अन्यथा
		child = cryptd_aead_child(ctx->cryptd_tfm);

	aead_request_set_tfm(subreq, child);

	वापस crypto_aead_encrypt(subreq);
पूर्ण

अटल पूर्णांक simd_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा simd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_request *subreq;
	काष्ठा crypto_aead *child;

	subreq = aead_request_ctx(req);
	*subreq = *req;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_aead_queued(ctx->cryptd_tfm)))
		child = &ctx->cryptd_tfm->base;
	अन्यथा
		child = cryptd_aead_child(ctx->cryptd_tfm);

	aead_request_set_tfm(subreq, child);

	वापस crypto_aead_decrypt(subreq);
पूर्ण

अटल व्योम simd_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा simd_aead_ctx *ctx = crypto_aead_ctx(tfm);

	cryptd_मुक्त_aead(ctx->cryptd_tfm);
पूर्ण

अटल पूर्णांक simd_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा simd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा cryptd_aead *cryptd_tfm;
	काष्ठा simd_aead_alg *salg;
	काष्ठा aead_alg *alg;
	अचिन्हित reqsize;

	alg = crypto_aead_alg(tfm);
	salg = container_of(alg, काष्ठा simd_aead_alg, alg);

	cryptd_tfm = cryptd_alloc_aead(salg->ialg_name, CRYPTO_ALG_INTERNAL,
				       CRYPTO_ALG_INTERNAL);
	अगर (IS_ERR(cryptd_tfm))
		वापस PTR_ERR(cryptd_tfm);

	ctx->cryptd_tfm = cryptd_tfm;

	reqsize = crypto_aead_reqsize(cryptd_aead_child(cryptd_tfm));
	reqsize = max(reqsize, crypto_aead_reqsize(&cryptd_tfm->base));
	reqsize += माप(काष्ठा aead_request);

	crypto_aead_set_reqsize(tfm, reqsize);

	वापस 0;
पूर्ण

काष्ठा simd_aead_alg *simd_aead_create_compat(स्थिर अक्षर *algname,
					      स्थिर अक्षर *drvname,
					      स्थिर अक्षर *basename)
अणु
	काष्ठा simd_aead_alg *salg;
	काष्ठा crypto_aead *tfm;
	काष्ठा aead_alg *ialg;
	काष्ठा aead_alg *alg;
	पूर्णांक err;

	tfm = crypto_alloc_aead(basename, CRYPTO_ALG_INTERNAL,
				CRYPTO_ALG_INTERNAL | CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		वापस ERR_CAST(tfm);

	ialg = crypto_aead_alg(tfm);

	salg = kzalloc(माप(*salg), GFP_KERNEL);
	अगर (!salg) अणु
		salg = ERR_PTR(-ENOMEM);
		जाओ out_put_tfm;
	पूर्ण

	salg->ialg_name = basename;
	alg = &salg->alg;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", algname) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ out_मुक्त_salg;

	अगर (snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		     drvname) >= CRYPTO_MAX_ALG_NAME)
		जाओ out_मुक्त_salg;

	alg->base.cra_flags = CRYPTO_ALG_ASYNC |
		(ialg->base.cra_flags & CRYPTO_ALG_INHERITED_FLAGS);
	alg->base.cra_priority = ialg->base.cra_priority;
	alg->base.cra_blocksize = ialg->base.cra_blocksize;
	alg->base.cra_alignmask = ialg->base.cra_alignmask;
	alg->base.cra_module = ialg->base.cra_module;
	alg->base.cra_ctxsize = माप(काष्ठा simd_aead_ctx);

	alg->ivsize = ialg->ivsize;
	alg->maxauthsize = ialg->maxauthsize;
	alg->chunksize = ialg->chunksize;

	alg->init = simd_aead_init;
	alg->निकास = simd_aead_निकास;

	alg->setkey = simd_aead_setkey;
	alg->setauthsize = simd_aead_setauthsize;
	alg->encrypt = simd_aead_encrypt;
	alg->decrypt = simd_aead_decrypt;

	err = crypto_रेजिस्टर_aead(alg);
	अगर (err)
		जाओ out_मुक्त_salg;

out_put_tfm:
	crypto_मुक्त_aead(tfm);
	वापस salg;

out_मुक्त_salg:
	kमुक्त(salg);
	salg = ERR_PTR(err);
	जाओ out_put_tfm;
पूर्ण
EXPORT_SYMBOL_GPL(simd_aead_create_compat);

काष्ठा simd_aead_alg *simd_aead_create(स्थिर अक्षर *algname,
				       स्थिर अक्षर *basename)
अणु
	अक्षर drvname[CRYPTO_MAX_ALG_NAME];

	अगर (snम_लिखो(drvname, CRYPTO_MAX_ALG_NAME, "simd-%s", basename) >=
	    CRYPTO_MAX_ALG_NAME)
		वापस ERR_PTR(-ENAMETOOLONG);

	वापस simd_aead_create_compat(algname, drvname, basename);
पूर्ण
EXPORT_SYMBOL_GPL(simd_aead_create);

व्योम simd_aead_मुक्त(काष्ठा simd_aead_alg *salg)
अणु
	crypto_unरेजिस्टर_aead(&salg->alg);
	kमुक्त(salg);
पूर्ण
EXPORT_SYMBOL_GPL(simd_aead_मुक्त);

पूर्णांक simd_रेजिस्टर_aeads_compat(काष्ठा aead_alg *algs, पूर्णांक count,
			       काष्ठा simd_aead_alg **simd_algs)
अणु
	पूर्णांक err;
	पूर्णांक i;
	स्थिर अक्षर *algname;
	स्थिर अक्षर *drvname;
	स्थिर अक्षर *basename;
	काष्ठा simd_aead_alg *simd;

	err = crypto_रेजिस्टर_aeads(algs, count);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < count; i++) अणु
		WARN_ON(म_भेदन(algs[i].base.cra_name, "__", 2));
		WARN_ON(म_भेदन(algs[i].base.cra_driver_name, "__", 2));
		algname = algs[i].base.cra_name + 2;
		drvname = algs[i].base.cra_driver_name + 2;
		basename = algs[i].base.cra_driver_name;
		simd = simd_aead_create_compat(algname, drvname, basename);
		err = PTR_ERR(simd);
		अगर (IS_ERR(simd))
			जाओ err_unरेजिस्टर;
		simd_algs[i] = simd;
	पूर्ण
	वापस 0;

err_unरेजिस्टर:
	simd_unरेजिस्टर_aeads(algs, count, simd_algs);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(simd_रेजिस्टर_aeads_compat);

व्योम simd_unरेजिस्टर_aeads(काष्ठा aead_alg *algs, पूर्णांक count,
			   काष्ठा simd_aead_alg **simd_algs)
अणु
	पूर्णांक i;

	crypto_unरेजिस्टर_aeads(algs, count);

	क्रम (i = 0; i < count; i++) अणु
		अगर (simd_algs[i]) अणु
			simd_aead_मुक्त(simd_algs[i]);
			simd_algs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(simd_unरेजिस्टर_aeads);

MODULE_LICENSE("GPL");
