<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hash algorithms.
 * 
 * Copyright (c) 2008 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_INTERNAL_HASH_H
#घोषणा _CRYPTO_INTERNAL_HASH_H

#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>

काष्ठा ahash_request;
काष्ठा scatterlist;

काष्ठा crypto_hash_walk अणु
	अक्षर *data;

	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक alignmask;

	काष्ठा page *pg;
	अचिन्हित पूर्णांक entrylen;

	अचिन्हित पूर्णांक total;
	काष्ठा scatterlist *sg;

	अचिन्हित पूर्णांक flags;
पूर्ण;

काष्ठा ahash_instance अणु
	व्योम (*मुक्त)(काष्ठा ahash_instance *inst);
	जोड़ अणु
		काष्ठा अणु
			अक्षर head[दुरत्व(काष्ठा ahash_alg, halg.base)];
			काष्ठा crypto_instance base;
		पूर्ण s;
		काष्ठा ahash_alg alg;
	पूर्ण;
पूर्ण;

काष्ठा shash_instance अणु
	व्योम (*मुक्त)(काष्ठा shash_instance *inst);
	जोड़ अणु
		काष्ठा अणु
			अक्षर head[दुरत्व(काष्ठा shash_alg, base)];
			काष्ठा crypto_instance base;
		पूर्ण s;
		काष्ठा shash_alg alg;
	पूर्ण;
पूर्ण;

काष्ठा crypto_ahash_spawn अणु
	काष्ठा crypto_spawn base;
पूर्ण;

काष्ठा crypto_shash_spawn अणु
	काष्ठा crypto_spawn base;
पूर्ण;

पूर्णांक crypto_hash_walk_करोne(काष्ठा crypto_hash_walk *walk, पूर्णांक err);
पूर्णांक crypto_hash_walk_first(काष्ठा ahash_request *req,
			   काष्ठा crypto_hash_walk *walk);

अटल अंतरभूत पूर्णांक crypto_hash_walk_last(काष्ठा crypto_hash_walk *walk)
अणु
	वापस !(walk->entrylen | walk->total);
पूर्ण

पूर्णांक crypto_रेजिस्टर_ahash(काष्ठा ahash_alg *alg);
व्योम crypto_unरेजिस्टर_ahash(काष्ठा ahash_alg *alg);
पूर्णांक crypto_रेजिस्टर_ahashes(काष्ठा ahash_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_ahashes(काष्ठा ahash_alg *algs, पूर्णांक count);
पूर्णांक ahash_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			    काष्ठा ahash_instance *inst);

पूर्णांक shash_no_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
		    अचिन्हित पूर्णांक keylen);

अटल अंतरभूत bool crypto_shash_alg_has_setkey(काष्ठा shash_alg *alg)
अणु
	वापस alg->setkey != shash_no_setkey;
पूर्ण

अटल अंतरभूत bool crypto_shash_alg_needs_key(काष्ठा shash_alg *alg)
अणु
	वापस crypto_shash_alg_has_setkey(alg) &&
		!(alg->base.cra_flags & CRYPTO_ALG_OPTIONAL_KEY);
पूर्ण

bool crypto_hash_alg_has_setkey(काष्ठा hash_alg_common *halg);

पूर्णांक crypto_grab_ahash(काष्ठा crypto_ahash_spawn *spawn,
		      काष्ठा crypto_instance *inst,
		      स्थिर अक्षर *name, u32 type, u32 mask);

अटल अंतरभूत व्योम crypto_drop_ahash(काष्ठा crypto_ahash_spawn *spawn)
अणु
	crypto_drop_spawn(&spawn->base);
पूर्ण

अटल अंतरभूत काष्ठा hash_alg_common *crypto_spawn_ahash_alg(
	काष्ठा crypto_ahash_spawn *spawn)
अणु
	वापस __crypto_hash_alg_common(spawn->base.alg);
पूर्ण

पूर्णांक crypto_रेजिस्टर_shash(काष्ठा shash_alg *alg);
व्योम crypto_unरेजिस्टर_shash(काष्ठा shash_alg *alg);
पूर्णांक crypto_रेजिस्टर_shashes(काष्ठा shash_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_shashes(काष्ठा shash_alg *algs, पूर्णांक count);
पूर्णांक shash_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			    काष्ठा shash_instance *inst);
व्योम shash_मुक्त_singlespawn_instance(काष्ठा shash_instance *inst);

पूर्णांक crypto_grab_shash(काष्ठा crypto_shash_spawn *spawn,
		      काष्ठा crypto_instance *inst,
		      स्थिर अक्षर *name, u32 type, u32 mask);

अटल अंतरभूत व्योम crypto_drop_shash(काष्ठा crypto_shash_spawn *spawn)
अणु
	crypto_drop_spawn(&spawn->base);
पूर्ण

अटल अंतरभूत काष्ठा shash_alg *crypto_spawn_shash_alg(
	काष्ठा crypto_shash_spawn *spawn)
अणु
	वापस __crypto_shash_alg(spawn->base.alg);
पूर्ण

पूर्णांक shash_ahash_update(काष्ठा ahash_request *req, काष्ठा shash_desc *desc);
पूर्णांक shash_ahash_finup(काष्ठा ahash_request *req, काष्ठा shash_desc *desc);
पूर्णांक shash_ahash_digest(काष्ठा ahash_request *req, काष्ठा shash_desc *desc);

पूर्णांक crypto_init_shash_ops_async(काष्ठा crypto_tfm *tfm);

अटल अंतरभूत व्योम *crypto_ahash_ctx(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_ctx(crypto_ahash_tfm(tfm));
पूर्ण

अटल अंतरभूत काष्ठा ahash_alg *__crypto_ahash_alg(काष्ठा crypto_alg *alg)
अणु
	वापस container_of(__crypto_hash_alg_common(alg), काष्ठा ahash_alg,
			    halg);
पूर्ण

अटल अंतरभूत व्योम crypto_ahash_set_reqsize(काष्ठा crypto_ahash *tfm,
					    अचिन्हित पूर्णांक reqsize)
अणु
	tfm->reqsize = reqsize;
पूर्ण

अटल अंतरभूत काष्ठा crypto_instance *ahash_crypto_instance(
	काष्ठा ahash_instance *inst)
अणु
	वापस &inst->s.base;
पूर्ण

अटल अंतरभूत काष्ठा ahash_instance *ahash_instance(
	काष्ठा crypto_instance *inst)
अणु
	वापस container_of(inst, काष्ठा ahash_instance, s.base);
पूर्ण

अटल अंतरभूत काष्ठा ahash_instance *ahash_alg_instance(
	काष्ठा crypto_ahash *ahash)
अणु
	वापस ahash_instance(crypto_tfm_alg_instance(&ahash->base));
पूर्ण

अटल अंतरभूत व्योम *ahash_instance_ctx(काष्ठा ahash_instance *inst)
अणु
	वापस crypto_instance_ctx(ahash_crypto_instance(inst));
पूर्ण

अटल अंतरभूत व्योम ahash_request_complete(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

अटल अंतरभूत u32 ahash_request_flags(काष्ठा ahash_request *req)
अणु
	वापस req->base.flags;
पूर्ण

अटल अंतरभूत काष्ठा crypto_ahash *crypto_spawn_ahash(
	काष्ठा crypto_ahash_spawn *spawn)
अणु
	वापस crypto_spawn_tfm2(&spawn->base);
पूर्ण

अटल अंतरभूत पूर्णांक ahash_enqueue_request(काष्ठा crypto_queue *queue,
					     काष्ठा ahash_request *request)
अणु
	वापस crypto_enqueue_request(queue, &request->base);
पूर्ण

अटल अंतरभूत काष्ठा ahash_request *ahash_dequeue_request(
	काष्ठा crypto_queue *queue)
अणु
	वापस ahash_request_cast(crypto_dequeue_request(queue));
पूर्ण

अटल अंतरभूत व्योम *crypto_shash_ctx(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_ctx(&tfm->base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_instance *shash_crypto_instance(
	काष्ठा shash_instance *inst)
अणु
	वापस &inst->s.base;
पूर्ण

अटल अंतरभूत काष्ठा shash_instance *shash_instance(
	काष्ठा crypto_instance *inst)
अणु
	वापस container_of(inst, काष्ठा shash_instance, s.base);
पूर्ण

अटल अंतरभूत काष्ठा shash_instance *shash_alg_instance(
	काष्ठा crypto_shash *shash)
अणु
	वापस shash_instance(crypto_tfm_alg_instance(&shash->base));
पूर्ण

अटल अंतरभूत व्योम *shash_instance_ctx(काष्ठा shash_instance *inst)
अणु
	वापस crypto_instance_ctx(shash_crypto_instance(inst));
पूर्ण

अटल अंतरभूत काष्ठा crypto_shash *crypto_spawn_shash(
	काष्ठा crypto_shash_spawn *spawn)
अणु
	वापस crypto_spawn_tfm2(&spawn->base);
पूर्ण

अटल अंतरभूत व्योम *crypto_shash_ctx_aligned(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_ctx_aligned(&tfm->base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_shash *__crypto_shash_cast(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_shash, base);
पूर्ण

#पूर्ण_अगर	/* _CRYPTO_INTERNAL_HASH_H */

