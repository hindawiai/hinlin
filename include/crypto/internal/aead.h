<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AEAD: Authenticated Encryption with Associated Data
 * 
 * Copyright (c) 2007-2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_INTERNAL_AEAD_H
#घोषणा _CRYPTO_INTERNAL_AEAD_H

#समावेश <crypto/aead.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

काष्ठा rtattr;

काष्ठा aead_instance अणु
	व्योम (*मुक्त)(काष्ठा aead_instance *inst);
	जोड़ अणु
		काष्ठा अणु
			अक्षर head[दुरत्व(काष्ठा aead_alg, base)];
			काष्ठा crypto_instance base;
		पूर्ण s;
		काष्ठा aead_alg alg;
	पूर्ण;
पूर्ण;

काष्ठा crypto_aead_spawn अणु
	काष्ठा crypto_spawn base;
पूर्ण;

काष्ठा aead_queue अणु
	काष्ठा crypto_queue base;
पूर्ण;

अटल अंतरभूत व्योम *crypto_aead_ctx(काष्ठा crypto_aead *tfm)
अणु
	वापस crypto_tfm_ctx(&tfm->base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_instance *aead_crypto_instance(
	काष्ठा aead_instance *inst)
अणु
	वापस container_of(&inst->alg.base, काष्ठा crypto_instance, alg);
पूर्ण

अटल अंतरभूत काष्ठा aead_instance *aead_instance(काष्ठा crypto_instance *inst)
अणु
	वापस container_of(&inst->alg, काष्ठा aead_instance, alg.base);
पूर्ण

अटल अंतरभूत काष्ठा aead_instance *aead_alg_instance(काष्ठा crypto_aead *aead)
अणु
	वापस aead_instance(crypto_tfm_alg_instance(&aead->base));
पूर्ण

अटल अंतरभूत व्योम *aead_instance_ctx(काष्ठा aead_instance *inst)
अणु
	वापस crypto_instance_ctx(aead_crypto_instance(inst));
पूर्ण

अटल अंतरभूत व्योम *aead_request_ctx(काष्ठा aead_request *req)
अणु
	वापस req->__ctx;
पूर्ण

अटल अंतरभूत व्योम aead_request_complete(काष्ठा aead_request *req, पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

अटल अंतरभूत u32 aead_request_flags(काष्ठा aead_request *req)
अणु
	वापस req->base.flags;
पूर्ण

अटल अंतरभूत काष्ठा aead_request *aead_request_cast(
	काष्ठा crypto_async_request *req)
अणु
	वापस container_of(req, काष्ठा aead_request, base);
पूर्ण

पूर्णांक crypto_grab_aead(काष्ठा crypto_aead_spawn *spawn,
		     काष्ठा crypto_instance *inst,
		     स्थिर अक्षर *name, u32 type, u32 mask);

अटल अंतरभूत व्योम crypto_drop_aead(काष्ठा crypto_aead_spawn *spawn)
अणु
	crypto_drop_spawn(&spawn->base);
पूर्ण

अटल अंतरभूत काष्ठा aead_alg *crypto_spawn_aead_alg(
	काष्ठा crypto_aead_spawn *spawn)
अणु
	वापस container_of(spawn->base.alg, काष्ठा aead_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_aead *crypto_spawn_aead(
	काष्ठा crypto_aead_spawn *spawn)
अणु
	वापस crypto_spawn_tfm2(&spawn->base);
पूर्ण

अटल अंतरभूत व्योम crypto_aead_set_reqsize(काष्ठा crypto_aead *aead,
					   अचिन्हित पूर्णांक reqsize)
अणु
	aead->reqsize = reqsize;
पूर्ण

अटल अंतरभूत व्योम aead_init_queue(काष्ठा aead_queue *queue,
				   अचिन्हित पूर्णांक max_qlen)
अणु
	crypto_init_queue(&queue->base, max_qlen);
पूर्ण

अटल अंतरभूत पूर्णांक aead_enqueue_request(काष्ठा aead_queue *queue,
				       काष्ठा aead_request *request)
अणु
	वापस crypto_enqueue_request(&queue->base, &request->base);
पूर्ण

अटल अंतरभूत काष्ठा aead_request *aead_dequeue_request(
	काष्ठा aead_queue *queue)
अणु
	काष्ठा crypto_async_request *req;

	req = crypto_dequeue_request(&queue->base);

	वापस req ? container_of(req, काष्ठा aead_request, base) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा aead_request *aead_get_backlog(काष्ठा aead_queue *queue)
अणु
	काष्ठा crypto_async_request *req;

	req = crypto_get_backlog(&queue->base);

	वापस req ? container_of(req, काष्ठा aead_request, base) : शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_aead_alg_chunksize(काष्ठा aead_alg *alg)
अणु
	वापस alg->chunksize;
पूर्ण

/**
 * crypto_aead_chunksize() - obtain chunk size
 * @tfm: cipher handle
 *
 * The block size is set to one क्रम ciphers such as CCM.  However,
 * you still need to provide incremental updates in multiples of
 * the underlying block size as the IV करोes not have sub-block
 * granularity.  This is known in this API as the chunk size.
 *
 * Return: chunk size in bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_aead_chunksize(काष्ठा crypto_aead *tfm)
अणु
	वापस crypto_aead_alg_chunksize(crypto_aead_alg(tfm));
पूर्ण

पूर्णांक crypto_रेजिस्टर_aead(काष्ठा aead_alg *alg);
व्योम crypto_unरेजिस्टर_aead(काष्ठा aead_alg *alg);
पूर्णांक crypto_रेजिस्टर_aeads(काष्ठा aead_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_aeads(काष्ठा aead_alg *algs, पूर्णांक count);
पूर्णांक aead_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			   काष्ठा aead_instance *inst);

#पूर्ण_अगर	/* _CRYPTO_INTERNAL_AEAD_H */

