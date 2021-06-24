<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google LLC
 */

/*
 * Refer to Documentation/block/अंतरभूत-encryption.rst क्रम detailed explanation.
 */

#घोषणा pr_fmt(fmt) "blk-crypto: " fmt

#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/keyslot-manager.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "blk-crypto-internal.h"

स्थिर काष्ठा blk_crypto_mode blk_crypto_modes[] = अणु
	[BLK_ENCRYPTION_MODE_AES_256_XTS] = अणु
		.cipher_str = "xts(aes)",
		.keysize = 64,
		.ivsize = 16,
	पूर्ण,
	[BLK_ENCRYPTION_MODE_AES_128_CBC_ESSIV] = अणु
		.cipher_str = "essiv(cbc(aes),sha256)",
		.keysize = 16,
		.ivsize = 16,
	पूर्ण,
	[BLK_ENCRYPTION_MODE_ADIANTUM] = अणु
		.cipher_str = "adiantum(xchacha12,aes)",
		.keysize = 32,
		.ivsize = 32,
	पूर्ण,
पूर्ण;

/*
 * This number needs to be at least (the number of thपढ़ोs करोing IO
 * concurrently) * (maximum recursive depth of a bio), so that we करोn't
 * deadlock on crypt_ctx allocations. The शेष is chosen to be the same
 * as the शेष number of post पढ़ो contexts in both EXT4 and F2FS.
 */
अटल पूर्णांक num_pपुनः_स्मृति_crypt_ctxs = 128;

module_param(num_pपुनः_स्मृति_crypt_ctxs, पूर्णांक, 0444);
MODULE_PARM_DESC(num_pपुनः_स्मृति_crypt_ctxs,
		"Number of bio crypto contexts to preallocate");

अटल काष्ठा kmem_cache *bio_crypt_ctx_cache;
अटल mempool_t *bio_crypt_ctx_pool;

अटल पूर्णांक __init bio_crypt_ctx_init(व्योम)
अणु
	माप_प्रकार i;

	bio_crypt_ctx_cache = KMEM_CACHE(bio_crypt_ctx, 0);
	अगर (!bio_crypt_ctx_cache)
		जाओ out_no_mem;

	bio_crypt_ctx_pool = mempool_create_slab_pool(num_pपुनः_स्मृति_crypt_ctxs,
						      bio_crypt_ctx_cache);
	अगर (!bio_crypt_ctx_pool)
		जाओ out_no_mem;

	/* This is assumed in various places. */
	BUILD_BUG_ON(BLK_ENCRYPTION_MODE_INVALID != 0);

	/* Sanity check that no algorithm exceeds the defined limits. */
	क्रम (i = 0; i < BLK_ENCRYPTION_MODE_MAX; i++) अणु
		BUG_ON(blk_crypto_modes[i].keysize > BLK_CRYPTO_MAX_KEY_SIZE);
		BUG_ON(blk_crypto_modes[i].ivsize > BLK_CRYPTO_MAX_IV_SIZE);
	पूर्ण

	वापस 0;
out_no_mem:
	panic("Failed to allocate mem for bio crypt ctxs\n");
पूर्ण
subsys_initcall(bio_crypt_ctx_init);

व्योम bio_crypt_set_ctx(काष्ठा bio *bio, स्थिर काष्ठा blk_crypto_key *key,
		       स्थिर u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE], gfp_t gfp_mask)
अणु
	काष्ठा bio_crypt_ctx *bc;

	/*
	 * The caller must use a gfp_mask that contains __GFP_सूचीECT_RECLAIM so
	 * that the mempool_alloc() can't fail.
	 */
	WARN_ON_ONCE(!(gfp_mask & __GFP_सूचीECT_RECLAIM));

	bc = mempool_alloc(bio_crypt_ctx_pool, gfp_mask);

	bc->bc_key = key;
	स_नकल(bc->bc_dun, dun, माप(bc->bc_dun));

	bio->bi_crypt_context = bc;
पूर्ण

व्योम __bio_crypt_मुक्त_ctx(काष्ठा bio *bio)
अणु
	mempool_मुक्त(bio->bi_crypt_context, bio_crypt_ctx_pool);
	bio->bi_crypt_context = शून्य;
पूर्ण

पूर्णांक __bio_crypt_clone(काष्ठा bio *dst, काष्ठा bio *src, gfp_t gfp_mask)
अणु
	dst->bi_crypt_context = mempool_alloc(bio_crypt_ctx_pool, gfp_mask);
	अगर (!dst->bi_crypt_context)
		वापस -ENOMEM;
	*dst->bi_crypt_context = *src->bi_crypt_context;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__bio_crypt_clone);

/* Increments @dun by @inc, treating @dun as a multi-limb पूर्णांकeger. */
व्योम bio_crypt_dun_increment(u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE],
			     अचिन्हित पूर्णांक inc)
अणु
	पूर्णांक i;

	क्रम (i = 0; inc && i < BLK_CRYPTO_DUN_ARRAY_SIZE; i++) अणु
		dun[i] += inc;
		/*
		 * If the addition in this limb overflowed, then we need to
		 * carry 1 पूर्णांकo the next limb. Else the carry is 0.
		 */
		अगर (dun[i] < inc)
			inc = 1;
		अन्यथा
			inc = 0;
	पूर्ण
पूर्ण

व्योम __bio_crypt_advance(काष्ठा bio *bio, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा bio_crypt_ctx *bc = bio->bi_crypt_context;

	bio_crypt_dun_increment(bc->bc_dun,
				bytes >> bc->bc_key->data_unit_size_bits);
पूर्ण

/*
 * Returns true अगर @bc->bc_dun plus @bytes converted to data units is equal to
 * @next_dun, treating the DUNs as multi-limb पूर्णांकegers.
 */
bool bio_crypt_dun_is_contiguous(स्थिर काष्ठा bio_crypt_ctx *bc,
				 अचिन्हित पूर्णांक bytes,
				 स्थिर u64 next_dun[BLK_CRYPTO_DUN_ARRAY_SIZE])
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक carry = bytes >> bc->bc_key->data_unit_size_bits;

	क्रम (i = 0; i < BLK_CRYPTO_DUN_ARRAY_SIZE; i++) अणु
		अगर (bc->bc_dun[i] + carry != next_dun[i])
			वापस false;
		/*
		 * If the addition in this limb overflowed, then we need to
		 * carry 1 पूर्णांकo the next limb. Else the carry is 0.
		 */
		अगर ((bc->bc_dun[i] + carry) < carry)
			carry = 1;
		अन्यथा
			carry = 0;
	पूर्ण

	/* If the DUN wrapped through 0, करोn't treat it as contiguous. */
	वापस carry == 0;
पूर्ण

/*
 * Checks that two bio crypt contexts are compatible - i.e. that
 * they are mergeable except क्रम data_unit_num continuity.
 */
अटल bool bio_crypt_ctx_compatible(काष्ठा bio_crypt_ctx *bc1,
				     काष्ठा bio_crypt_ctx *bc2)
अणु
	अगर (!bc1)
		वापस !bc2;

	वापस bc2 && bc1->bc_key == bc2->bc_key;
पूर्ण

bool bio_crypt_rq_ctx_compatible(काष्ठा request *rq, काष्ठा bio *bio)
अणु
	वापस bio_crypt_ctx_compatible(rq->crypt_ctx, bio->bi_crypt_context);
पूर्ण

/*
 * Checks that two bio crypt contexts are compatible, and also
 * that their data_unit_nums are continuous (and can hence be merged)
 * in the order @bc1 followed by @bc2.
 */
bool bio_crypt_ctx_mergeable(काष्ठा bio_crypt_ctx *bc1, अचिन्हित पूर्णांक bc1_bytes,
			     काष्ठा bio_crypt_ctx *bc2)
अणु
	अगर (!bio_crypt_ctx_compatible(bc1, bc2))
		वापस false;

	वापस !bc1 || bio_crypt_dun_is_contiguous(bc1, bc1_bytes, bc2->bc_dun);
पूर्ण

/* Check that all I/O segments are data unit aligned. */
अटल bool bio_crypt_check_alignment(काष्ठा bio *bio)
अणु
	स्थिर अचिन्हित पूर्णांक data_unit_size =
		bio->bi_crypt_context->bc_key->crypto_cfg.data_unit_size;
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bv;

	bio_क्रम_each_segment(bv, bio, iter) अणु
		अगर (!IS_ALIGNED(bv.bv_len | bv.bv_offset, data_unit_size))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

blk_status_t __blk_crypto_init_request(काष्ठा request *rq)
अणु
	वापस blk_ksm_get_slot_क्रम_key(rq->q->ksm, rq->crypt_ctx->bc_key,
					&rq->crypt_keyslot);
पूर्ण

/**
 * __blk_crypto_मुक्त_request - Uninitialize the crypto fields of a request.
 *
 * @rq: The request whose crypto fields to uninitialize.
 *
 * Completely uninitializes the crypto fields of a request. If a keyslot has
 * been programmed पूर्णांकo some अंतरभूत encryption hardware, that keyslot is
 * released. The rq->crypt_ctx is also मुक्तd.
 */
व्योम __blk_crypto_मुक्त_request(काष्ठा request *rq)
अणु
	blk_ksm_put_slot(rq->crypt_keyslot);
	mempool_मुक्त(rq->crypt_ctx, bio_crypt_ctx_pool);
	blk_crypto_rq_set_शेषs(rq);
पूर्ण

/**
 * __blk_crypto_bio_prep - Prepare bio क्रम अंतरभूत encryption
 *
 * @bio_ptr: poपूर्णांकer to original bio poपूर्णांकer
 *
 * If the bio crypt context provided क्रम the bio is supported by the underlying
 * device's अंतरभूत encryption hardware, करो nothing.
 *
 * Otherwise, try to perक्रमm en/decryption क्रम this bio by falling back to the
 * kernel crypto API. When the crypto API fallback is used क्रम encryption,
 * blk-crypto may choose to split the bio पूर्णांकo 2 - the first one that will
 * जारी to be processed and the second one that will be resubmitted via
 * submit_bio_noacct. A bounce bio will be allocated to encrypt the contents
 * of the aक्रमementioned "first one", and *bio_ptr will be updated to this
 * bounce bio.
 *
 * Caller must ensure bio has bio_crypt_ctx.
 *
 * Return: true on success; false on error (and bio->bi_status will be set
 *	   appropriately, and bio_endio() will have been called so bio
 *	   submission should पात).
 */
bool __blk_crypto_bio_prep(काष्ठा bio **bio_ptr)
अणु
	काष्ठा bio *bio = *bio_ptr;
	स्थिर काष्ठा blk_crypto_key *bc_key = bio->bi_crypt_context->bc_key;

	/* Error अगर bio has no data. */
	अगर (WARN_ON_ONCE(!bio_has_data(bio))) अणु
		bio->bi_status = BLK_STS_IOERR;
		जाओ fail;
	पूर्ण

	अगर (!bio_crypt_check_alignment(bio)) अणु
		bio->bi_status = BLK_STS_IOERR;
		जाओ fail;
	पूर्ण

	/*
	 * Success अगर device supports the encryption context, or अगर we succeeded
	 * in falling back to the crypto API.
	 */
	अगर (blk_ksm_crypto_cfg_supported(bio->bi_bdev->bd_disk->queue->ksm,
					 &bc_key->crypto_cfg))
		वापस true;

	अगर (blk_crypto_fallback_bio_prep(bio_ptr))
		वापस true;
fail:
	bio_endio(*bio_ptr);
	वापस false;
पूर्ण

पूर्णांक __blk_crypto_rq_bio_prep(काष्ठा request *rq, काष्ठा bio *bio,
			     gfp_t gfp_mask)
अणु
	अगर (!rq->crypt_ctx) अणु
		rq->crypt_ctx = mempool_alloc(bio_crypt_ctx_pool, gfp_mask);
		अगर (!rq->crypt_ctx)
			वापस -ENOMEM;
	पूर्ण
	*rq->crypt_ctx = *bio->bi_crypt_context;
	वापस 0;
पूर्ण

/**
 * blk_crypto_init_key() - Prepare a key क्रम use with blk-crypto
 * @blk_key: Poपूर्णांकer to the blk_crypto_key to initialize.
 * @raw_key: Poपूर्णांकer to the raw key. Must be the correct length क्रम the chosen
 *	     @crypto_mode; see blk_crypto_modes[].
 * @crypto_mode: identअगरier क्रम the encryption algorithm to use
 * @dun_bytes: number of bytes that will be used to specअगरy the DUN when this
 *	       key is used
 * @data_unit_size: the data unit size to use क्रम en/decryption
 *
 * Return: 0 on success, -त्रुटि_सं on failure.  The caller is responsible क्रम
 *	   zeroizing both blk_key and raw_key when करोne with them.
 */
पूर्णांक blk_crypto_init_key(काष्ठा blk_crypto_key *blk_key, स्थिर u8 *raw_key,
			क्रमागत blk_crypto_mode_num crypto_mode,
			अचिन्हित पूर्णांक dun_bytes,
			अचिन्हित पूर्णांक data_unit_size)
अणु
	स्थिर काष्ठा blk_crypto_mode *mode;

	स_रखो(blk_key, 0, माप(*blk_key));

	अगर (crypto_mode >= ARRAY_SIZE(blk_crypto_modes))
		वापस -EINVAL;

	mode = &blk_crypto_modes[crypto_mode];
	अगर (mode->keysize == 0)
		वापस -EINVAL;

	अगर (dun_bytes == 0 || dun_bytes > BLK_CRYPTO_MAX_IV_SIZE)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(data_unit_size))
		वापस -EINVAL;

	blk_key->crypto_cfg.crypto_mode = crypto_mode;
	blk_key->crypto_cfg.dun_bytes = dun_bytes;
	blk_key->crypto_cfg.data_unit_size = data_unit_size;
	blk_key->data_unit_size_bits = ilog2(data_unit_size);
	blk_key->size = mode->keysize;
	स_नकल(blk_key->raw, raw_key, mode->keysize);

	वापस 0;
पूर्ण

/*
 * Check अगर bios with @cfg can be en/decrypted by blk-crypto (i.e. either the
 * request queue it's submitted to supports अंतरभूत crypto, or the
 * blk-crypto-fallback is enabled and supports the cfg).
 */
bool blk_crypto_config_supported(काष्ठा request_queue *q,
				 स्थिर काष्ठा blk_crypto_config *cfg)
अणु
	वापस IS_ENABLED(CONFIG_BLK_INLINE_ENCRYPTION_FALLBACK) ||
	       blk_ksm_crypto_cfg_supported(q->ksm, cfg);
पूर्ण

/**
 * blk_crypto_start_using_key() - Start using a blk_crypto_key on a device
 * @key: A key to use on the device
 * @q: the request queue क्रम the device
 *
 * Upper layers must call this function to ensure that either the hardware
 * supports the key's crypto settings, or the crypto API fallback has transक्रमms
 * क्रम the needed mode allocated and पढ़ोy to go. This function may allocate
 * an skcipher, and *should not* be called from the data path, since that might
 * cause a deadlock
 *
 * Return: 0 on success; -ENOPKG अगर the hardware करोesn't support the key and
 *	   blk-crypto-fallback is either disabled or the needed algorithm
 *	   is disabled in the crypto API; or another -त्रुटि_सं code.
 */
पूर्णांक blk_crypto_start_using_key(स्थिर काष्ठा blk_crypto_key *key,
			       काष्ठा request_queue *q)
अणु
	अगर (blk_ksm_crypto_cfg_supported(q->ksm, &key->crypto_cfg))
		वापस 0;
	वापस blk_crypto_fallback_start_using_mode(key->crypto_cfg.crypto_mode);
पूर्ण

/**
 * blk_crypto_evict_key() - Evict a key from any अंतरभूत encryption hardware
 *			    it may have been programmed पूर्णांकo
 * @q: The request queue who's associated अंतरभूत encryption hardware this key
 *     might have been programmed पूर्णांकo
 * @key: The key to evict
 *
 * Upper layers (fileप्रणालीs) must call this function to ensure that a key is
 * evicted from any hardware that it might have been programmed पूर्णांकo.  The key
 * must not be in use by any in-flight IO when this function is called.
 *
 * Return: 0 on success or अगर key is not present in the q's ksm, -err on error.
 */
पूर्णांक blk_crypto_evict_key(काष्ठा request_queue *q,
			 स्थिर काष्ठा blk_crypto_key *key)
अणु
	अगर (blk_ksm_crypto_cfg_supported(q->ksm, &key->crypto_cfg))
		वापस blk_ksm_evict_key(q->ksm, key);

	/*
	 * If the request queue's associated inline encryption hardware didn't
	 * have support क्रम the key, then the key might have been programmed
	 * पूर्णांकo the fallback keyslot manager, so try to evict from there.
	 */
	वापस blk_crypto_fallback_evict_key(key);
पूर्ण
EXPORT_SYMBOL_GPL(blk_crypto_evict_key);
