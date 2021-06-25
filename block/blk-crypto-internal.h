<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित __LINUX_BLK_CRYPTO_INTERNAL_H
#घोषणा __LINUX_BLK_CRYPTO_INTERNAL_H

#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>

/* Represents a crypto mode supported by blk-crypto  */
काष्ठा blk_crypto_mode अणु
	स्थिर अक्षर *cipher_str; /* crypto API name (क्रम fallback हाल) */
	अचिन्हित पूर्णांक keysize; /* key size in bytes */
	अचिन्हित पूर्णांक ivsize; /* iv size in bytes */
पूर्ण;

बाह्य स्थिर काष्ठा blk_crypto_mode blk_crypto_modes[];

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION

व्योम bio_crypt_dun_increment(u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE],
			     अचिन्हित पूर्णांक inc);

bool bio_crypt_rq_ctx_compatible(काष्ठा request *rq, काष्ठा bio *bio);

bool bio_crypt_ctx_mergeable(काष्ठा bio_crypt_ctx *bc1, अचिन्हित पूर्णांक bc1_bytes,
			     काष्ठा bio_crypt_ctx *bc2);

अटल अंतरभूत bool bio_crypt_ctx_back_mergeable(काष्ठा request *req,
						काष्ठा bio *bio)
अणु
	वापस bio_crypt_ctx_mergeable(req->crypt_ctx, blk_rq_bytes(req),
				       bio->bi_crypt_context);
पूर्ण

अटल अंतरभूत bool bio_crypt_ctx_front_mergeable(काष्ठा request *req,
						 काष्ठा bio *bio)
अणु
	वापस bio_crypt_ctx_mergeable(bio->bi_crypt_context,
				       bio->bi_iter.bi_size, req->crypt_ctx);
पूर्ण

अटल अंतरभूत bool bio_crypt_ctx_merge_rq(काष्ठा request *req,
					  काष्ठा request *next)
अणु
	वापस bio_crypt_ctx_mergeable(req->crypt_ctx, blk_rq_bytes(req),
				       next->crypt_ctx);
पूर्ण

अटल अंतरभूत व्योम blk_crypto_rq_set_शेषs(काष्ठा request *rq)
अणु
	rq->crypt_ctx = शून्य;
	rq->crypt_keyslot = शून्य;
पूर्ण

अटल अंतरभूत bool blk_crypto_rq_is_encrypted(काष्ठा request *rq)
अणु
	वापस rq->crypt_ctx;
पूर्ण

#अन्यथा /* CONFIG_BLK_INLINE_ENCRYPTION */

अटल अंतरभूत bool bio_crypt_rq_ctx_compatible(काष्ठा request *rq,
					       काष्ठा bio *bio)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool bio_crypt_ctx_front_mergeable(काष्ठा request *req,
						 काष्ठा bio *bio)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool bio_crypt_ctx_back_mergeable(काष्ठा request *req,
						काष्ठा bio *bio)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool bio_crypt_ctx_merge_rq(काष्ठा request *req,
					  काष्ठा request *next)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम blk_crypto_rq_set_शेषs(काष्ठा request *rq) अणु पूर्ण

अटल अंतरभूत bool blk_crypto_rq_is_encrypted(काष्ठा request *rq)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_INLINE_ENCRYPTION */

व्योम __bio_crypt_advance(काष्ठा bio *bio, अचिन्हित पूर्णांक bytes);
अटल अंतरभूत व्योम bio_crypt_advance(काष्ठा bio *bio, अचिन्हित पूर्णांक bytes)
अणु
	अगर (bio_has_crypt_ctx(bio))
		__bio_crypt_advance(bio, bytes);
पूर्ण

व्योम __bio_crypt_मुक्त_ctx(काष्ठा bio *bio);
अटल अंतरभूत व्योम bio_crypt_मुक्त_ctx(काष्ठा bio *bio)
अणु
	अगर (bio_has_crypt_ctx(bio))
		__bio_crypt_मुक्त_ctx(bio);
पूर्ण

अटल अंतरभूत व्योम bio_crypt_करो_front_merge(काष्ठा request *rq,
					    काष्ठा bio *bio)
अणु
#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
	अगर (bio_has_crypt_ctx(bio))
		स_नकल(rq->crypt_ctx->bc_dun, bio->bi_crypt_context->bc_dun,
		       माप(rq->crypt_ctx->bc_dun));
#पूर्ण_अगर
पूर्ण

bool __blk_crypto_bio_prep(काष्ठा bio **bio_ptr);
अटल अंतरभूत bool blk_crypto_bio_prep(काष्ठा bio **bio_ptr)
अणु
	अगर (bio_has_crypt_ctx(*bio_ptr))
		वापस __blk_crypto_bio_prep(bio_ptr);
	वापस true;
पूर्ण

blk_status_t __blk_crypto_init_request(काष्ठा request *rq);
अटल अंतरभूत blk_status_t blk_crypto_init_request(काष्ठा request *rq)
अणु
	अगर (blk_crypto_rq_is_encrypted(rq))
		वापस __blk_crypto_init_request(rq);
	वापस BLK_STS_OK;
पूर्ण

व्योम __blk_crypto_मुक्त_request(काष्ठा request *rq);
अटल अंतरभूत व्योम blk_crypto_मुक्त_request(काष्ठा request *rq)
अणु
	अगर (blk_crypto_rq_is_encrypted(rq))
		__blk_crypto_मुक्त_request(rq);
पूर्ण

पूर्णांक __blk_crypto_rq_bio_prep(काष्ठा request *rq, काष्ठा bio *bio,
			     gfp_t gfp_mask);
/**
 * blk_crypto_rq_bio_prep - Prepare a request's crypt_ctx when its first bio
 *			    is inserted
 * @rq: The request to prepare
 * @bio: The first bio being inserted पूर्णांकo the request
 * @gfp_mask: Memory allocation flags
 *
 * Return: 0 on success, -ENOMEM अगर out of memory.  -ENOMEM is only possible अगर
 *	   @gfp_mask करोesn't include %__GFP_सूचीECT_RECLAIM.
 */
अटल अंतरभूत पूर्णांक blk_crypto_rq_bio_prep(काष्ठा request *rq, काष्ठा bio *bio,
					 gfp_t gfp_mask)
अणु
	अगर (bio_has_crypt_ctx(bio))
		वापस __blk_crypto_rq_bio_prep(rq, bio, gfp_mask);
	वापस 0;
पूर्ण

/**
 * blk_crypto_insert_cloned_request - Prepare a cloned request to be inserted
 *				      पूर्णांकo a request queue.
 * @rq: the request being queued
 *
 * Return: BLK_STS_OK on success, nonzero on error.
 */
अटल अंतरभूत blk_status_t blk_crypto_insert_cloned_request(काष्ठा request *rq)
अणु

	अगर (blk_crypto_rq_is_encrypted(rq))
		वापस blk_crypto_init_request(rq);
	वापस BLK_STS_OK;
पूर्ण

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION_FALLBACK

पूर्णांक blk_crypto_fallback_start_using_mode(क्रमागत blk_crypto_mode_num mode_num);

bool blk_crypto_fallback_bio_prep(काष्ठा bio **bio_ptr);

पूर्णांक blk_crypto_fallback_evict_key(स्थिर काष्ठा blk_crypto_key *key);

#अन्यथा /* CONFIG_BLK_INLINE_ENCRYPTION_FALLBACK */

अटल अंतरभूत पूर्णांक
blk_crypto_fallback_start_using_mode(क्रमागत blk_crypto_mode_num mode_num)
अणु
	pr_warn_once("crypto API fallback is disabled\n");
	वापस -ENOPKG;
पूर्ण

अटल अंतरभूत bool blk_crypto_fallback_bio_prep(काष्ठा bio **bio_ptr)
अणु
	pr_warn_once("crypto API fallback disabled; failing request.\n");
	(*bio_ptr)->bi_status = BLK_STS_NOTSUPP;
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
blk_crypto_fallback_evict_key(स्थिर काष्ठा blk_crypto_key *key)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_INLINE_ENCRYPTION_FALLBACK */

#पूर्ण_अगर /* __LINUX_BLK_CRYPTO_INTERNAL_H */
