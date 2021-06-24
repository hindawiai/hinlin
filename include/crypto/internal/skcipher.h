<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Symmetric key ciphers.
 * 
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_INTERNAL_SKCIPHER_H
#घोषणा _CRYPTO_INTERNAL_SKCIPHER_H

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>

काष्ठा aead_request;
काष्ठा rtattr;

काष्ठा skcipher_instance अणु
	व्योम (*मुक्त)(काष्ठा skcipher_instance *inst);
	जोड़ अणु
		काष्ठा अणु
			अक्षर head[दुरत्व(काष्ठा skcipher_alg, base)];
			काष्ठा crypto_instance base;
		पूर्ण s;
		काष्ठा skcipher_alg alg;
	पूर्ण;
पूर्ण;

काष्ठा crypto_skcipher_spawn अणु
	काष्ठा crypto_spawn base;
पूर्ण;

काष्ठा skcipher_walk अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा page *page;
			अचिन्हित दीर्घ offset;
		पूर्ण phys;

		काष्ठा अणु
			u8 *page;
			व्योम *addr;
		पूर्ण virt;
	पूर्ण src, dst;

	काष्ठा scatter_walk in;
	अचिन्हित पूर्णांक nbytes;

	काष्ठा scatter_walk out;
	अचिन्हित पूर्णांक total;

	काष्ठा list_head buffers;

	u8 *page;
	u8 *buffer;
	u8 *oiv;
	व्योम *iv;

	अचिन्हित पूर्णांक ivsize;

	पूर्णांक flags;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक alignmask;
पूर्ण;

अटल अंतरभूत काष्ठा crypto_instance *skcipher_crypto_instance(
	काष्ठा skcipher_instance *inst)
अणु
	वापस &inst->s.base;
पूर्ण

अटल अंतरभूत काष्ठा skcipher_instance *skcipher_alg_instance(
	काष्ठा crypto_skcipher *skcipher)
अणु
	वापस container_of(crypto_skcipher_alg(skcipher),
			    काष्ठा skcipher_instance, alg);
पूर्ण

अटल अंतरभूत व्योम *skcipher_instance_ctx(काष्ठा skcipher_instance *inst)
अणु
	वापस crypto_instance_ctx(skcipher_crypto_instance(inst));
पूर्ण

अटल अंतरभूत व्योम skcipher_request_complete(काष्ठा skcipher_request *req, पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

पूर्णांक crypto_grab_skcipher(काष्ठा crypto_skcipher_spawn *spawn,
			 काष्ठा crypto_instance *inst,
			 स्थिर अक्षर *name, u32 type, u32 mask);

अटल अंतरभूत व्योम crypto_drop_skcipher(काष्ठा crypto_skcipher_spawn *spawn)
अणु
	crypto_drop_spawn(&spawn->base);
पूर्ण

अटल अंतरभूत काष्ठा skcipher_alg *crypto_skcipher_spawn_alg(
	काष्ठा crypto_skcipher_spawn *spawn)
अणु
	वापस container_of(spawn->base.alg, काष्ठा skcipher_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा skcipher_alg *crypto_spawn_skcipher_alg(
	काष्ठा crypto_skcipher_spawn *spawn)
अणु
	वापस crypto_skcipher_spawn_alg(spawn);
पूर्ण

अटल अंतरभूत काष्ठा crypto_skcipher *crypto_spawn_skcipher(
	काष्ठा crypto_skcipher_spawn *spawn)
अणु
	वापस crypto_spawn_tfm2(&spawn->base);
पूर्ण

अटल अंतरभूत व्योम crypto_skcipher_set_reqsize(
	काष्ठा crypto_skcipher *skcipher, अचिन्हित पूर्णांक reqsize)
अणु
	skcipher->reqsize = reqsize;
पूर्ण

पूर्णांक crypto_रेजिस्टर_skcipher(काष्ठा skcipher_alg *alg);
व्योम crypto_unरेजिस्टर_skcipher(काष्ठा skcipher_alg *alg);
पूर्णांक crypto_रेजिस्टर_skciphers(काष्ठा skcipher_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_skciphers(काष्ठा skcipher_alg *algs, पूर्णांक count);
पूर्णांक skcipher_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			       काष्ठा skcipher_instance *inst);

पूर्णांक skcipher_walk_करोne(काष्ठा skcipher_walk *walk, पूर्णांक err);
पूर्णांक skcipher_walk_virt(काष्ठा skcipher_walk *walk,
		       काष्ठा skcipher_request *req,
		       bool atomic);
पूर्णांक skcipher_walk_async(काष्ठा skcipher_walk *walk,
			काष्ठा skcipher_request *req);
पूर्णांक skcipher_walk_aead_encrypt(काष्ठा skcipher_walk *walk,
			       काष्ठा aead_request *req, bool atomic);
पूर्णांक skcipher_walk_aead_decrypt(काष्ठा skcipher_walk *walk,
			       काष्ठा aead_request *req, bool atomic);
व्योम skcipher_walk_complete(काष्ठा skcipher_walk *walk, पूर्णांक err);

अटल अंतरभूत व्योम skcipher_walk_पात(काष्ठा skcipher_walk *walk)
अणु
	skcipher_walk_करोne(walk, -ECANCELED);
पूर्ण

अटल अंतरभूत व्योम *crypto_skcipher_ctx(काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_tfm_ctx(&tfm->base);
पूर्ण

अटल अंतरभूत व्योम *skcipher_request_ctx(काष्ठा skcipher_request *req)
अणु
	वापस req->__ctx;
पूर्ण

अटल अंतरभूत u32 skcipher_request_flags(काष्ठा skcipher_request *req)
अणु
	वापस req->base.flags;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_alg_min_keysize(
	काष्ठा skcipher_alg *alg)
अणु
	वापस alg->min_keysize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_alg_max_keysize(
	काष्ठा skcipher_alg *alg)
अणु
	वापस alg->max_keysize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_alg_walksize(
	काष्ठा skcipher_alg *alg)
अणु
	वापस alg->walksize;
पूर्ण

/**
 * crypto_skcipher_walksize() - obtain walk size
 * @tfm: cipher handle
 *
 * In some हालs, algorithms can only perक्रमm optimally when operating on
 * multiple blocks in parallel. This is reflected by the walksize, which
 * must be a multiple of the chunksize (or equal अगर the concern करोes not
 * apply)
 *
 * Return: walk size in bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_walksize(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_skcipher_alg_walksize(crypto_skcipher_alg(tfm));
पूर्ण

/* Helpers क्रम simple block cipher modes of operation */
काष्ठा skcipher_ctx_simple अणु
	काष्ठा crypto_cipher *cipher;	/* underlying block cipher */
पूर्ण;
अटल अंतरभूत काष्ठा crypto_cipher *
skcipher_cipher_simple(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_ctx_simple *ctx = crypto_skcipher_ctx(tfm);

	वापस ctx->cipher;
पूर्ण

काष्ठा skcipher_instance *skcipher_alloc_instance_simple(
	काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb);

अटल अंतरभूत काष्ठा crypto_alg *skcipher_ialg_simple(
	काष्ठा skcipher_instance *inst)
अणु
	काष्ठा crypto_cipher_spawn *spawn = skcipher_instance_ctx(inst);

	वापस crypto_spawn_cipher_alg(spawn);
पूर्ण

#पूर्ण_अगर	/* _CRYPTO_INTERNAL_SKCIPHER_H */

