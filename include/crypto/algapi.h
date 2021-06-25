<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Cryptographic API क्रम algorithms (i.e., low-level API).
 *
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */
#अगर_अघोषित _CRYPTO_ALGAPI_H
#घोषणा _CRYPTO_ALGAPI_H

#समावेश <linux/crypto.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>

/*
 * Maximum values क्रम blocksize and alignmask, used to allocate
 * अटल buffers that are big enough क्रम any combination of
 * algs and architectures. Ciphers have a lower maximum size.
 */
#घोषणा MAX_ALGAPI_BLOCKSIZE		160
#घोषणा MAX_ALGAPI_ALIGNMASK		63
#घोषणा MAX_CIPHER_BLOCKSIZE		16
#घोषणा MAX_CIPHER_ALIGNMASK		15

काष्ठा crypto_aead;
काष्ठा crypto_instance;
काष्ठा module;
काष्ठा rtattr;
काष्ठा seq_file;
काष्ठा sk_buff;

काष्ठा crypto_type अणु
	अचिन्हित पूर्णांक (*ctxsize)(काष्ठा crypto_alg *alg, u32 type, u32 mask);
	अचिन्हित पूर्णांक (*extsize)(काष्ठा crypto_alg *alg);
	पूर्णांक (*init)(काष्ठा crypto_tfm *tfm, u32 type, u32 mask);
	पूर्णांक (*init_tfm)(काष्ठा crypto_tfm *tfm);
	व्योम (*show)(काष्ठा seq_file *m, काष्ठा crypto_alg *alg);
	पूर्णांक (*report)(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg);
	व्योम (*मुक्त)(काष्ठा crypto_instance *inst);

	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक maskclear;
	अचिन्हित पूर्णांक maskset;
	अचिन्हित पूर्णांक tfmsize;
पूर्ण;

काष्ठा crypto_instance अणु
	काष्ठा crypto_alg alg;

	काष्ठा crypto_ढाँचा *पंचांगpl;

	जोड़ अणु
		/* Node in list of instances after registration. */
		काष्ठा hlist_node list;
		/* List of attached spawns beक्रमe registration. */
		काष्ठा crypto_spawn *spawns;
	पूर्ण;

	व्योम *__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

काष्ठा crypto_ढाँचा अणु
	काष्ठा list_head list;
	काष्ठा hlist_head instances;
	काष्ठा module *module;

	पूर्णांक (*create)(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb);

	अक्षर name[CRYPTO_MAX_ALG_NAME];
पूर्ण;

काष्ठा crypto_spawn अणु
	काष्ठा list_head list;
	काष्ठा crypto_alg *alg;
	जोड़ अणु
		/* Back poपूर्णांकer to instance after registration.*/
		काष्ठा crypto_instance *inst;
		/* Spawn list poपूर्णांकer prior to registration. */
		काष्ठा crypto_spawn *next;
	पूर्ण;
	स्थिर काष्ठा crypto_type *frontend;
	u32 mask;
	bool dead;
	bool रेजिस्टरed;
पूर्ण;

काष्ठा crypto_queue अणु
	काष्ठा list_head list;
	काष्ठा list_head *backlog;

	अचिन्हित पूर्णांक qlen;
	अचिन्हित पूर्णांक max_qlen;
पूर्ण;

काष्ठा scatter_walk अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;
पूर्ण;

व्योम crypto_mod_put(काष्ठा crypto_alg *alg);

पूर्णांक crypto_रेजिस्टर_ढाँचा(काष्ठा crypto_ढाँचा *पंचांगpl);
पूर्णांक crypto_रेजिस्टर_ढाँचाs(काष्ठा crypto_ढाँचा *पंचांगpls, पूर्णांक count);
व्योम crypto_unरेजिस्टर_ढाँचा(काष्ठा crypto_ढाँचा *पंचांगpl);
व्योम crypto_unरेजिस्टर_ढाँचाs(काष्ठा crypto_ढाँचा *पंचांगpls, पूर्णांक count);
काष्ठा crypto_ढाँचा *crypto_lookup_ढाँचा(स्थिर अक्षर *name);

पूर्णांक crypto_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			     काष्ठा crypto_instance *inst);
व्योम crypto_unरेजिस्टर_instance(काष्ठा crypto_instance *inst);

पूर्णांक crypto_grab_spawn(काष्ठा crypto_spawn *spawn, काष्ठा crypto_instance *inst,
		      स्थिर अक्षर *name, u32 type, u32 mask);
व्योम crypto_drop_spawn(काष्ठा crypto_spawn *spawn);
काष्ठा crypto_tfm *crypto_spawn_tfm(काष्ठा crypto_spawn *spawn, u32 type,
				    u32 mask);
व्योम *crypto_spawn_tfm2(काष्ठा crypto_spawn *spawn);

काष्ठा crypto_attr_type *crypto_get_attr_type(काष्ठा rtattr **tb);
पूर्णांक crypto_check_attr_type(काष्ठा rtattr **tb, u32 type, u32 *mask_ret);
स्थिर अक्षर *crypto_attr_alg_name(काष्ठा rtattr *rta);
पूर्णांक crypto_attr_u32(काष्ठा rtattr *rta, u32 *num);
पूर्णांक crypto_inst_setname(काष्ठा crypto_instance *inst, स्थिर अक्षर *name,
			काष्ठा crypto_alg *alg);

व्योम crypto_init_queue(काष्ठा crypto_queue *queue, अचिन्हित पूर्णांक max_qlen);
पूर्णांक crypto_enqueue_request(काष्ठा crypto_queue *queue,
			   काष्ठा crypto_async_request *request);
व्योम crypto_enqueue_request_head(काष्ठा crypto_queue *queue,
				 काष्ठा crypto_async_request *request);
काष्ठा crypto_async_request *crypto_dequeue_request(काष्ठा crypto_queue *queue);
अटल अंतरभूत अचिन्हित पूर्णांक crypto_queue_len(काष्ठा crypto_queue *queue)
अणु
	वापस queue->qlen;
पूर्ण

व्योम crypto_inc(u8 *a, अचिन्हित पूर्णांक size);
व्योम __crypto_xor(u8 *dst, स्थिर u8 *src1, स्थिर u8 *src2, अचिन्हित पूर्णांक size);

अटल अंतरभूत व्योम crypto_xor(u8 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक size)
अणु
	अगर (IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) &&
	    __builtin_स्थिरant_p(size) &&
	    (size % माप(अचिन्हित दीर्घ)) == 0) अणु
		अचिन्हित दीर्घ *d = (अचिन्हित दीर्घ *)dst;
		अचिन्हित दीर्घ *s = (अचिन्हित दीर्घ *)src;

		जबतक (size > 0) अणु
			*d++ ^= *s++;
			size -= माप(अचिन्हित दीर्घ);
		पूर्ण
	पूर्ण अन्यथा अणु
		__crypto_xor(dst, dst, src, size);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम crypto_xor_cpy(u8 *dst, स्थिर u8 *src1, स्थिर u8 *src2,
				  अचिन्हित पूर्णांक size)
अणु
	अगर (IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) &&
	    __builtin_स्थिरant_p(size) &&
	    (size % माप(अचिन्हित दीर्घ)) == 0) अणु
		अचिन्हित दीर्घ *d = (अचिन्हित दीर्घ *)dst;
		अचिन्हित दीर्घ *s1 = (अचिन्हित दीर्घ *)src1;
		अचिन्हित दीर्घ *s2 = (अचिन्हित दीर्घ *)src2;

		जबतक (size > 0) अणु
			*d++ = *s1++ ^ *s2++;
			size -= माप(अचिन्हित दीर्घ);
		पूर्ण
	पूर्ण अन्यथा अणु
		__crypto_xor(dst, src1, src2, size);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *crypto_tfm_ctx_aligned(काष्ठा crypto_tfm *tfm)
अणु
	वापस PTR_ALIGN(crypto_tfm_ctx(tfm),
			 crypto_tfm_alg_alignmask(tfm) + 1);
पूर्ण

अटल अंतरभूत काष्ठा crypto_instance *crypto_tfm_alg_instance(
	काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm->__crt_alg, काष्ठा crypto_instance, alg);
पूर्ण

अटल अंतरभूत व्योम *crypto_instance_ctx(काष्ठा crypto_instance *inst)
अणु
	वापस inst->__ctx;
पूर्ण

अटल अंतरभूत काष्ठा crypto_async_request *crypto_get_backlog(
	काष्ठा crypto_queue *queue)
अणु
	वापस queue->backlog == &queue->list ? शून्य :
	       container_of(queue->backlog, काष्ठा crypto_async_request, list);
पूर्ण

अटल अंतरभूत u32 crypto_requires_off(काष्ठा crypto_attr_type *algt, u32 off)
अणु
	वापस (algt->type ^ off) & algt->mask & off;
पूर्ण

/*
 * When an algorithm uses another algorithm (e.g., अगर it's an instance of a
 * ढाँचा), these are the flags that should always be set on the "outer"
 * algorithm अगर any "inner" algorithm has them set.
 */
#घोषणा CRYPTO_ALG_INHERITED_FLAGS	\
	(CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK |	\
	 CRYPTO_ALG_ALLOCATES_MEMORY)

/*
 * Given the type and mask that specअगरy the flags restrictions on a ढाँचा
 * instance being created, वापस the mask that should be passed to
 * crypto_grab_*() (aदीर्घ with type=0) to honor any request the user made to
 * have any of the CRYPTO_ALG_INHERITED_FLAGS clear.
 */
अटल अंतरभूत u32 crypto_algt_inherited_mask(काष्ठा crypto_attr_type *algt)
अणु
	वापस crypto_requires_off(algt, CRYPTO_ALG_INHERITED_FLAGS);
पूर्ण

noअंतरभूत अचिन्हित दीर्घ __crypto_memneq(स्थिर व्योम *a, स्थिर व्योम *b, माप_प्रकार size);

/**
 * crypto_memneq - Compare two areas of memory without leaking
 *		   timing inक्रमmation.
 *
 * @a: One area of memory
 * @b: Another area of memory
 * @size: The size of the area.
 *
 * Returns 0 when data is equal, 1 otherwise.
 */
अटल अंतरभूत पूर्णांक crypto_memneq(स्थिर व्योम *a, स्थिर व्योम *b, माप_प्रकार size)
अणु
	वापस __crypto_memneq(a, b, size) != 0UL ? 1 : 0;
पूर्ण

पूर्णांक crypto_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक crypto_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);

/* Crypto notअगरication events. */
क्रमागत अणु
	CRYPTO_MSG_ALG_REQUEST,
	CRYPTO_MSG_ALG_REGISTER,
	CRYPTO_MSG_ALG_LOADED,
पूर्ण;

#पूर्ण_अगर	/* _CRYPTO_ALGAPI_H */
