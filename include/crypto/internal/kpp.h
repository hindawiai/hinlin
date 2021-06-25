<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Key-agreement Protocol Primitives (KPP)
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_KPP_INT_H
#घोषणा _CRYPTO_KPP_INT_H
#समावेश <crypto/kpp.h>
#समावेश <crypto/algapi.h>

/*
 * Transक्रमm पूर्णांकernal helpers.
 */
अटल अंतरभूत व्योम *kpp_request_ctx(काष्ठा kpp_request *req)
अणु
	वापस req->__ctx;
पूर्ण

अटल अंतरभूत व्योम *kpp_tfm_ctx(काष्ठा crypto_kpp *tfm)
अणु
	वापस tfm->base.__crt_ctx;
पूर्ण

अटल अंतरभूत व्योम kpp_request_complete(काष्ठा kpp_request *req, पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *kpp_alg_name(काष्ठा crypto_kpp *tfm)
अणु
	वापस crypto_kpp_tfm(tfm)->__crt_alg->cra_name;
पूर्ण

/**
 * crypto_रेजिस्टर_kpp() -- Register key-agreement protocol primitives algorithm
 *
 * Function रेजिस्टरs an implementation of a key-agreement protocol primitive
 * algorithm
 *
 * @alg:	algorithm definition
 *
 * Return: zero on success; error code in हाल of error
 */
पूर्णांक crypto_रेजिस्टर_kpp(काष्ठा kpp_alg *alg);

/**
 * crypto_unरेजिस्टर_kpp() -- Unरेजिस्टर key-agreement protocol primitive
 * algorithm
 *
 * Function unरेजिस्टरs an implementation of a key-agreement protocol primitive
 * algorithm
 *
 * @alg:	algorithm definition
 */
व्योम crypto_unरेजिस्टर_kpp(काष्ठा kpp_alg *alg);

#पूर्ण_अगर
