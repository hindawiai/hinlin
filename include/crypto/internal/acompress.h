<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Asynchronous Compression operations
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Weigang Li <weigang.li@पूर्णांकel.com>
 *          Giovanni Cabiddu <giovanni.cabiddu@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_ACOMP_INT_H
#घोषणा _CRYPTO_ACOMP_INT_H
#समावेश <crypto/acompress.h>

/*
 * Transक्रमm पूर्णांकernal helpers.
 */
अटल अंतरभूत व्योम *acomp_request_ctx(काष्ठा acomp_req *req)
अणु
	वापस req->__ctx;
पूर्ण

अटल अंतरभूत व्योम *acomp_tfm_ctx(काष्ठा crypto_acomp *tfm)
अणु
	वापस tfm->base.__crt_ctx;
पूर्ण

अटल अंतरभूत व्योम acomp_request_complete(काष्ठा acomp_req *req,
					  पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *acomp_alg_name(काष्ठा crypto_acomp *tfm)
अणु
	वापस crypto_acomp_tfm(tfm)->__crt_alg->cra_name;
पूर्ण

अटल अंतरभूत काष्ठा acomp_req *__acomp_request_alloc(काष्ठा crypto_acomp *tfm)
अणु
	काष्ठा acomp_req *req;

	req = kzalloc(माप(*req) + crypto_acomp_reqsize(tfm), GFP_KERNEL);
	अगर (likely(req))
		acomp_request_set_tfm(req, tfm);
	वापस req;
पूर्ण

अटल अंतरभूत व्योम __acomp_request_मुक्त(काष्ठा acomp_req *req)
अणु
	kमुक्त_sensitive(req);
पूर्ण

/**
 * crypto_रेजिस्टर_acomp() -- Register asynchronous compression algorithm
 *
 * Function रेजिस्टरs an implementation of an asynchronous
 * compression algorithm
 *
 * @alg:	algorithm definition
 *
 * Return:	zero on success; error code in हाल of error
 */
पूर्णांक crypto_रेजिस्टर_acomp(काष्ठा acomp_alg *alg);

/**
 * crypto_unरेजिस्टर_acomp() -- Unरेजिस्टर asynchronous compression algorithm
 *
 * Function unरेजिस्टरs an implementation of an asynchronous
 * compression algorithm
 *
 * @alg:	algorithm definition
 */
व्योम crypto_unरेजिस्टर_acomp(काष्ठा acomp_alg *alg);

पूर्णांक crypto_रेजिस्टर_acomps(काष्ठा acomp_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_acomps(काष्ठा acomp_alg *algs, पूर्णांक count);

#पूर्ण_अगर
