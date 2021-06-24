<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Public Key Encryption
 *
 * Copyright (c) 2015, Intel Corporation
 * Authors: Tadeusz Struk <tadeusz.struk@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_AKCIPHER_INT_H
#घोषणा _CRYPTO_AKCIPHER_INT_H
#समावेश <crypto/akcipher.h>
#समावेश <crypto/algapi.h>

काष्ठा akcipher_instance अणु
	व्योम (*मुक्त)(काष्ठा akcipher_instance *inst);
	जोड़ अणु
		काष्ठा अणु
			अक्षर head[दुरत्व(काष्ठा akcipher_alg, base)];
			काष्ठा crypto_instance base;
		पूर्ण s;
		काष्ठा akcipher_alg alg;
	पूर्ण;
पूर्ण;

काष्ठा crypto_akcipher_spawn अणु
	काष्ठा crypto_spawn base;
पूर्ण;

/*
 * Transक्रमm पूर्णांकernal helpers.
 */
अटल अंतरभूत व्योम *akcipher_request_ctx(काष्ठा akcipher_request *req)
अणु
	वापस req->__ctx;
पूर्ण

अटल अंतरभूत व्योम akcipher_set_reqsize(काष्ठा crypto_akcipher *akcipher,
					अचिन्हित पूर्णांक reqsize)
अणु
	crypto_akcipher_alg(akcipher)->reqsize = reqsize;
पूर्ण

अटल अंतरभूत व्योम *akcipher_tfm_ctx(काष्ठा crypto_akcipher *tfm)
अणु
	वापस tfm->base.__crt_ctx;
पूर्ण

अटल अंतरभूत व्योम akcipher_request_complete(काष्ठा akcipher_request *req,
					     पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *akcipher_alg_name(काष्ठा crypto_akcipher *tfm)
अणु
	वापस crypto_akcipher_tfm(tfm)->__crt_alg->cra_name;
पूर्ण

अटल अंतरभूत काष्ठा crypto_instance *akcipher_crypto_instance(
		काष्ठा akcipher_instance *inst)
अणु
	वापस container_of(&inst->alg.base, काष्ठा crypto_instance, alg);
पूर्ण

अटल अंतरभूत काष्ठा akcipher_instance *akcipher_instance(
		काष्ठा crypto_instance *inst)
अणु
	वापस container_of(&inst->alg, काष्ठा akcipher_instance, alg.base);
पूर्ण

अटल अंतरभूत काष्ठा akcipher_instance *akcipher_alg_instance(
		काष्ठा crypto_akcipher *akcipher)
अणु
	वापस akcipher_instance(crypto_tfm_alg_instance(&akcipher->base));
पूर्ण

अटल अंतरभूत व्योम *akcipher_instance_ctx(काष्ठा akcipher_instance *inst)
अणु
	वापस crypto_instance_ctx(akcipher_crypto_instance(inst));
पूर्ण

पूर्णांक crypto_grab_akcipher(काष्ठा crypto_akcipher_spawn *spawn,
			 काष्ठा crypto_instance *inst,
			 स्थिर अक्षर *name, u32 type, u32 mask);

अटल अंतरभूत काष्ठा crypto_akcipher *crypto_spawn_akcipher(
		काष्ठा crypto_akcipher_spawn *spawn)
अणु
	वापस crypto_spawn_tfm2(&spawn->base);
पूर्ण

अटल अंतरभूत व्योम crypto_drop_akcipher(काष्ठा crypto_akcipher_spawn *spawn)
अणु
	crypto_drop_spawn(&spawn->base);
पूर्ण

अटल अंतरभूत काष्ठा akcipher_alg *crypto_spawn_akcipher_alg(
		काष्ठा crypto_akcipher_spawn *spawn)
अणु
	वापस container_of(spawn->base.alg, काष्ठा akcipher_alg, base);
पूर्ण

/**
 * crypto_रेजिस्टर_akcipher() -- Register खुला key algorithm
 *
 * Function रेजिस्टरs an implementation of a खुला key verअगरy algorithm
 *
 * @alg:	algorithm definition
 *
 * Return: zero on success; error code in हाल of error
 */
पूर्णांक crypto_रेजिस्टर_akcipher(काष्ठा akcipher_alg *alg);

/**
 * crypto_unरेजिस्टर_akcipher() -- Unरेजिस्टर खुला key algorithm
 *
 * Function unरेजिस्टरs an implementation of a खुला key verअगरy algorithm
 *
 * @alg:	algorithm definition
 */
व्योम crypto_unरेजिस्टर_akcipher(काष्ठा akcipher_alg *alg);

/**
 * akcipher_रेजिस्टर_instance() -- Unरेजिस्टर खुला key ढाँचा instance
 *
 * Function रेजिस्टरs an implementation of an asymmetric key algorithm
 * created from a ढाँचा
 *
 * @पंचांगpl:	the ढाँचा from which the algorithm was created
 * @inst:	the ढाँचा instance
 */
पूर्णांक akcipher_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
		काष्ठा akcipher_instance *inst);
#पूर्ण_अगर
