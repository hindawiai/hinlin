<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google LLC
 */

/*
 * Refer to Documentation/block/अंतरभूत-encryption.rst क्रम detailed explanation.
 */

#घोषणा pr_fmt(fmt) "blk-crypto-fallback: " fmt

#समावेश <crypto/skcipher.h>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/blk-crypto.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/crypto.h>
#समावेश <linux/keyslot-manager.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>

#समावेश "blk-crypto-internal.h"

अटल अचिन्हित पूर्णांक num_pपुनः_स्मृति_bounce_pg = 32;
module_param(num_pपुनः_स्मृति_bounce_pg, uपूर्णांक, 0);
MODULE_PARM_DESC(num_pपुनः_स्मृति_bounce_pg,
		 "Number of preallocated bounce pages for the blk-crypto crypto API fallback");

अटल अचिन्हित पूर्णांक blk_crypto_num_keyslots = 100;
module_param_named(num_keyslots, blk_crypto_num_keyslots, uपूर्णांक, 0);
MODULE_PARM_DESC(num_keyslots,
		 "Number of keyslots for the blk-crypto crypto API fallback");

अटल अचिन्हित पूर्णांक num_pपुनः_स्मृति_fallback_crypt_ctxs = 128;
module_param(num_pपुनः_स्मृति_fallback_crypt_ctxs, uपूर्णांक, 0);
MODULE_PARM_DESC(num_pपुनः_स्मृति_crypt_fallback_ctxs,
		 "Number of preallocated bio fallback crypto contexts for blk-crypto to use during crypto API fallback");

काष्ठा bio_fallback_crypt_ctx अणु
	काष्ठा bio_crypt_ctx crypt_ctx;
	/*
	 * Copy of the bvec_iter when this bio was submitted.
	 * We only want to en/decrypt the part of the bio as described by the
	 * bvec_iter upon submission because bio might be split beक्रमe being
	 * resubmitted
	 */
	काष्ठा bvec_iter crypt_iter;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा work_काष्ठा work;
			काष्ठा bio *bio;
		पूर्ण;
		काष्ठा अणु
			व्योम *bi_निजी_orig;
			bio_end_io_t *bi_end_io_orig;
		पूर्ण;
	पूर्ण;
पूर्ण;

अटल काष्ठा kmem_cache *bio_fallback_crypt_ctx_cache;
अटल mempool_t *bio_fallback_crypt_ctx_pool;

/*
 * Allocating a crypto tfm during I/O can deadlock, so we have to pपुनः_स्मृतिate
 * all of a mode's tfms when that mode starts being used. Since each mode may
 * need all the keyslots at some poपूर्णांक, each mode needs its own tfm क्रम each
 * keyslot; thus, a keyslot may contain tfms क्रम multiple modes.  However, to
 * match the behavior of real अंतरभूत encryption hardware (which only supports a
 * single encryption context per keyslot), we only allow one tfm per keyslot to
 * be used at a समय - the rest of the unused tfms have their keys cleared.
 */
अटल DEFINE_MUTEX(tfms_init_lock);
अटल bool tfms_inited[BLK_ENCRYPTION_MODE_MAX];

अटल काष्ठा blk_crypto_keyslot अणु
	क्रमागत blk_crypto_mode_num crypto_mode;
	काष्ठा crypto_skcipher *tfms[BLK_ENCRYPTION_MODE_MAX];
पूर्ण *blk_crypto_keyslots;

अटल काष्ठा blk_keyslot_manager blk_crypto_ksm;
अटल काष्ठा workqueue_काष्ठा *blk_crypto_wq;
अटल mempool_t *blk_crypto_bounce_page_pool;
अटल काष्ठा bio_set crypto_bio_split;

/*
 * This is the key we set when evicting a keyslot. This *should* be the all 0's
 * key, but AES-XTS rejects that key, so we use some अक्रमom bytes instead.
 */
अटल u8 blank_key[BLK_CRYPTO_MAX_KEY_SIZE];

अटल व्योम blk_crypto_evict_keyslot(अचिन्हित पूर्णांक slot)
अणु
	काष्ठा blk_crypto_keyslot *slotp = &blk_crypto_keyslots[slot];
	क्रमागत blk_crypto_mode_num crypto_mode = slotp->crypto_mode;
	पूर्णांक err;

	WARN_ON(slotp->crypto_mode == BLK_ENCRYPTION_MODE_INVALID);

	/* Clear the key in the skcipher */
	err = crypto_skcipher_setkey(slotp->tfms[crypto_mode], blank_key,
				     blk_crypto_modes[crypto_mode].keysize);
	WARN_ON(err);
	slotp->crypto_mode = BLK_ENCRYPTION_MODE_INVALID;
पूर्ण

अटल पूर्णांक blk_crypto_keyslot_program(काष्ठा blk_keyslot_manager *ksm,
				      स्थिर काष्ठा blk_crypto_key *key,
				      अचिन्हित पूर्णांक slot)
अणु
	काष्ठा blk_crypto_keyslot *slotp = &blk_crypto_keyslots[slot];
	स्थिर क्रमागत blk_crypto_mode_num crypto_mode =
						key->crypto_cfg.crypto_mode;
	पूर्णांक err;

	अगर (crypto_mode != slotp->crypto_mode &&
	    slotp->crypto_mode != BLK_ENCRYPTION_MODE_INVALID)
		blk_crypto_evict_keyslot(slot);

	slotp->crypto_mode = crypto_mode;
	err = crypto_skcipher_setkey(slotp->tfms[crypto_mode], key->raw,
				     key->size);
	अगर (err) अणु
		blk_crypto_evict_keyslot(slot);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक blk_crypto_keyslot_evict(काष्ठा blk_keyslot_manager *ksm,
				    स्थिर काष्ठा blk_crypto_key *key,
				    अचिन्हित पूर्णांक slot)
अणु
	blk_crypto_evict_keyslot(slot);
	वापस 0;
पूर्ण

/*
 * The crypto API fallback KSM ops - only used क्रम a bio when it specअगरies a
 * blk_crypto_key that was not supported by the device's अंतरभूत encryption
 * hardware.
 */
अटल स्थिर काष्ठा blk_ksm_ll_ops blk_crypto_ksm_ll_ops = अणु
	.keyslot_program	= blk_crypto_keyslot_program,
	.keyslot_evict		= blk_crypto_keyslot_evict,
पूर्ण;

अटल व्योम blk_crypto_fallback_encrypt_endio(काष्ठा bio *enc_bio)
अणु
	काष्ठा bio *src_bio = enc_bio->bi_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < enc_bio->bi_vcnt; i++)
		mempool_मुक्त(enc_bio->bi_io_vec[i].bv_page,
			     blk_crypto_bounce_page_pool);

	src_bio->bi_status = enc_bio->bi_status;

	bio_put(enc_bio);
	bio_endio(src_bio);
पूर्ण

अटल काष्ठा bio *blk_crypto_clone_bio(काष्ठा bio *bio_src)
अणु
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bv;
	काष्ठा bio *bio;

	bio = bio_kदो_स्मृति(GFP_NOIO, bio_segments(bio_src));
	अगर (!bio)
		वापस शून्य;
	bio->bi_bdev		= bio_src->bi_bdev;
	अगर (bio_flagged(bio_src, BIO_REMAPPED))
		bio_set_flag(bio, BIO_REMAPPED);
	bio->bi_opf		= bio_src->bi_opf;
	bio->bi_ioprio		= bio_src->bi_ioprio;
	bio->bi_ग_लिखो_hपूर्णांक	= bio_src->bi_ग_लिखो_hपूर्णांक;
	bio->bi_iter.bi_sector	= bio_src->bi_iter.bi_sector;
	bio->bi_iter.bi_size	= bio_src->bi_iter.bi_size;

	bio_क्रम_each_segment(bv, bio_src, iter)
		bio->bi_io_vec[bio->bi_vcnt++] = bv;

	bio_clone_blkg_association(bio, bio_src);
	blkcg_bio_issue_init(bio);

	वापस bio;
पूर्ण

अटल bool blk_crypto_alloc_cipher_req(काष्ठा blk_ksm_keyslot *slot,
					काष्ठा skcipher_request **ciph_req_ret,
					काष्ठा crypto_रुको *रुको)
अणु
	काष्ठा skcipher_request *ciph_req;
	स्थिर काष्ठा blk_crypto_keyslot *slotp;
	पूर्णांक keyslot_idx = blk_ksm_get_slot_idx(slot);

	slotp = &blk_crypto_keyslots[keyslot_idx];
	ciph_req = skcipher_request_alloc(slotp->tfms[slotp->crypto_mode],
					  GFP_NOIO);
	अगर (!ciph_req)
		वापस false;

	skcipher_request_set_callback(ciph_req,
				      CRYPTO_TFM_REQ_MAY_BACKLOG |
				      CRYPTO_TFM_REQ_MAY_SLEEP,
				      crypto_req_करोne, रुको);
	*ciph_req_ret = ciph_req;

	वापस true;
पूर्ण

अटल bool blk_crypto_split_bio_अगर_needed(काष्ठा bio **bio_ptr)
अणु
	काष्ठा bio *bio = *bio_ptr;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक num_sectors = 0;
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;

	bio_क्रम_each_segment(bv, bio, iter) अणु
		num_sectors += bv.bv_len >> SECTOR_SHIFT;
		अगर (++i == BIO_MAX_VECS)
			अवरोध;
	पूर्ण
	अगर (num_sectors < bio_sectors(bio)) अणु
		काष्ठा bio *split_bio;

		split_bio = bio_split(bio, num_sectors, GFP_NOIO,
				      &crypto_bio_split);
		अगर (!split_bio) अणु
			bio->bi_status = BLK_STS_RESOURCE;
			वापस false;
		पूर्ण
		bio_chain(split_bio, bio);
		submit_bio_noacct(bio);
		*bio_ptr = split_bio;
	पूर्ण

	वापस true;
पूर्ण

जोड़ blk_crypto_iv अणु
	__le64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE];
	u8 bytes[BLK_CRYPTO_MAX_IV_SIZE];
पूर्ण;

अटल व्योम blk_crypto_dun_to_iv(स्थिर u64 dun[BLK_CRYPTO_DUN_ARRAY_SIZE],
				 जोड़ blk_crypto_iv *iv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLK_CRYPTO_DUN_ARRAY_SIZE; i++)
		iv->dun[i] = cpu_to_le64(dun[i]);
पूर्ण

/*
 * The crypto API fallback's encryption routine.
 * Allocate a bounce bio क्रम encryption, encrypt the input bio using crypto API,
 * and replace *bio_ptr with the bounce bio. May split input bio अगर it's too
 * large. Returns true on success. Returns false and sets bio->bi_status on
 * error.
 */
अटल bool blk_crypto_fallback_encrypt_bio(काष्ठा bio **bio_ptr)
अणु
	काष्ठा bio *src_bio, *enc_bio;
	काष्ठा bio_crypt_ctx *bc;
	काष्ठा blk_ksm_keyslot *slot;
	पूर्णांक data_unit_size;
	काष्ठा skcipher_request *ciph_req = शून्य;
	DECLARE_CRYPTO_WAIT(रुको);
	u64 curr_dun[BLK_CRYPTO_DUN_ARRAY_SIZE];
	काष्ठा scatterlist src, dst;
	जोड़ blk_crypto_iv iv;
	अचिन्हित पूर्णांक i, j;
	bool ret = false;
	blk_status_t blk_st;

	/* Split the bio अगर it's too big क्रम single page bvec */
	अगर (!blk_crypto_split_bio_अगर_needed(bio_ptr))
		वापस false;

	src_bio = *bio_ptr;
	bc = src_bio->bi_crypt_context;
	data_unit_size = bc->bc_key->crypto_cfg.data_unit_size;

	/* Allocate bounce bio क्रम encryption */
	enc_bio = blk_crypto_clone_bio(src_bio);
	अगर (!enc_bio) अणु
		src_bio->bi_status = BLK_STS_RESOURCE;
		वापस false;
	पूर्ण

	/*
	 * Use the crypto API fallback keyslot manager to get a crypto_skcipher
	 * क्रम the algorithm and key specअगरied क्रम this bio.
	 */
	blk_st = blk_ksm_get_slot_क्रम_key(&blk_crypto_ksm, bc->bc_key, &slot);
	अगर (blk_st != BLK_STS_OK) अणु
		src_bio->bi_status = blk_st;
		जाओ out_put_enc_bio;
	पूर्ण

	/* and then allocate an skcipher_request क्रम it */
	अगर (!blk_crypto_alloc_cipher_req(slot, &ciph_req, &रुको)) अणु
		src_bio->bi_status = BLK_STS_RESOURCE;
		जाओ out_release_keyslot;
	पूर्ण

	स_नकल(curr_dun, bc->bc_dun, माप(curr_dun));
	sg_init_table(&src, 1);
	sg_init_table(&dst, 1);

	skcipher_request_set_crypt(ciph_req, &src, &dst, data_unit_size,
				   iv.bytes);

	/* Encrypt each page in the bounce bio */
	क्रम (i = 0; i < enc_bio->bi_vcnt; i++) अणु
		काष्ठा bio_vec *enc_bvec = &enc_bio->bi_io_vec[i];
		काष्ठा page *plaपूर्णांकext_page = enc_bvec->bv_page;
		काष्ठा page *ciphertext_page =
			mempool_alloc(blk_crypto_bounce_page_pool, GFP_NOIO);

		enc_bvec->bv_page = ciphertext_page;

		अगर (!ciphertext_page) अणु
			src_bio->bi_status = BLK_STS_RESOURCE;
			जाओ out_मुक्त_bounce_pages;
		पूर्ण

		sg_set_page(&src, plaपूर्णांकext_page, data_unit_size,
			    enc_bvec->bv_offset);
		sg_set_page(&dst, ciphertext_page, data_unit_size,
			    enc_bvec->bv_offset);

		/* Encrypt each data unit in this page */
		क्रम (j = 0; j < enc_bvec->bv_len; j += data_unit_size) अणु
			blk_crypto_dun_to_iv(curr_dun, &iv);
			अगर (crypto_रुको_req(crypto_skcipher_encrypt(ciph_req),
					    &रुको)) अणु
				i++;
				src_bio->bi_status = BLK_STS_IOERR;
				जाओ out_मुक्त_bounce_pages;
			पूर्ण
			bio_crypt_dun_increment(curr_dun, 1);
			src.offset += data_unit_size;
			dst.offset += data_unit_size;
		पूर्ण
	पूर्ण

	enc_bio->bi_निजी = src_bio;
	enc_bio->bi_end_io = blk_crypto_fallback_encrypt_endio;
	*bio_ptr = enc_bio;
	ret = true;

	enc_bio = शून्य;
	जाओ out_मुक्त_ciph_req;

out_मुक्त_bounce_pages:
	जबतक (i > 0)
		mempool_मुक्त(enc_bio->bi_io_vec[--i].bv_page,
			     blk_crypto_bounce_page_pool);
out_मुक्त_ciph_req:
	skcipher_request_मुक्त(ciph_req);
out_release_keyslot:
	blk_ksm_put_slot(slot);
out_put_enc_bio:
	अगर (enc_bio)
		bio_put(enc_bio);

	वापस ret;
पूर्ण

/*
 * The crypto API fallback's मुख्य decryption routine.
 * Decrypts input bio in place, and calls bio_endio on the bio.
 */
अटल व्योम blk_crypto_fallback_decrypt_bio(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_fallback_crypt_ctx *f_ctx =
		container_of(work, काष्ठा bio_fallback_crypt_ctx, work);
	काष्ठा bio *bio = f_ctx->bio;
	काष्ठा bio_crypt_ctx *bc = &f_ctx->crypt_ctx;
	काष्ठा blk_ksm_keyslot *slot;
	काष्ठा skcipher_request *ciph_req = शून्य;
	DECLARE_CRYPTO_WAIT(रुको);
	u64 curr_dun[BLK_CRYPTO_DUN_ARRAY_SIZE];
	जोड़ blk_crypto_iv iv;
	काष्ठा scatterlist sg;
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;
	स्थिर पूर्णांक data_unit_size = bc->bc_key->crypto_cfg.data_unit_size;
	अचिन्हित पूर्णांक i;
	blk_status_t blk_st;

	/*
	 * Use the crypto API fallback keyslot manager to get a crypto_skcipher
	 * क्रम the algorithm and key specअगरied क्रम this bio.
	 */
	blk_st = blk_ksm_get_slot_क्रम_key(&blk_crypto_ksm, bc->bc_key, &slot);
	अगर (blk_st != BLK_STS_OK) अणु
		bio->bi_status = blk_st;
		जाओ out_no_keyslot;
	पूर्ण

	/* and then allocate an skcipher_request क्रम it */
	अगर (!blk_crypto_alloc_cipher_req(slot, &ciph_req, &रुको)) अणु
		bio->bi_status = BLK_STS_RESOURCE;
		जाओ out;
	पूर्ण

	स_नकल(curr_dun, bc->bc_dun, माप(curr_dun));
	sg_init_table(&sg, 1);
	skcipher_request_set_crypt(ciph_req, &sg, &sg, data_unit_size,
				   iv.bytes);

	/* Decrypt each segment in the bio */
	__bio_क्रम_each_segment(bv, bio, iter, f_ctx->crypt_iter) अणु
		काष्ठा page *page = bv.bv_page;

		sg_set_page(&sg, page, data_unit_size, bv.bv_offset);

		/* Decrypt each data unit in the segment */
		क्रम (i = 0; i < bv.bv_len; i += data_unit_size) अणु
			blk_crypto_dun_to_iv(curr_dun, &iv);
			अगर (crypto_रुको_req(crypto_skcipher_decrypt(ciph_req),
					    &रुको)) अणु
				bio->bi_status = BLK_STS_IOERR;
				जाओ out;
			पूर्ण
			bio_crypt_dun_increment(curr_dun, 1);
			sg.offset += data_unit_size;
		पूर्ण
	पूर्ण

out:
	skcipher_request_मुक्त(ciph_req);
	blk_ksm_put_slot(slot);
out_no_keyslot:
	mempool_मुक्त(f_ctx, bio_fallback_crypt_ctx_pool);
	bio_endio(bio);
पूर्ण

/**
 * blk_crypto_fallback_decrypt_endio - queue bio क्रम fallback decryption
 *
 * @bio: the bio to queue
 *
 * Restore bi_निजी and bi_end_io, and queue the bio क्रम decryption पूर्णांकo a
 * workqueue, since this function will be called from an atomic context.
 */
अटल व्योम blk_crypto_fallback_decrypt_endio(काष्ठा bio *bio)
अणु
	काष्ठा bio_fallback_crypt_ctx *f_ctx = bio->bi_निजी;

	bio->bi_निजी = f_ctx->bi_निजी_orig;
	bio->bi_end_io = f_ctx->bi_end_io_orig;

	/* If there was an IO error, करोn't queue क्रम decrypt. */
	अगर (bio->bi_status) अणु
		mempool_मुक्त(f_ctx, bio_fallback_crypt_ctx_pool);
		bio_endio(bio);
		वापस;
	पूर्ण

	INIT_WORK(&f_ctx->work, blk_crypto_fallback_decrypt_bio);
	f_ctx->bio = bio;
	queue_work(blk_crypto_wq, &f_ctx->work);
पूर्ण

/**
 * blk_crypto_fallback_bio_prep - Prepare a bio to use fallback en/decryption
 *
 * @bio_ptr: poपूर्णांकer to the bio to prepare
 *
 * If bio is करोing a WRITE operation, this splits the bio पूर्णांकo two parts अगर it's
 * too big (see blk_crypto_split_bio_अगर_needed). It then allocates a bounce bio
 * क्रम the first part, encrypts it, and update bio_ptr to poपूर्णांक to the bounce
 * bio.
 *
 * For a READ operation, we mark the bio क्रम decryption by using bi_निजी and
 * bi_end_io.
 *
 * In either हाल, this function will make the bio look like a regular bio (i.e.
 * as अगर no encryption context was ever specअगरied) क्रम the purposes of the rest
 * of the stack except क्रम blk-पूर्णांकegrity (blk-पूर्णांकegrity and blk-crypto are not
 * currently supported together).
 *
 * Return: true on success. Sets bio->bi_status and वापसs false on error.
 */
bool blk_crypto_fallback_bio_prep(काष्ठा bio **bio_ptr)
अणु
	काष्ठा bio *bio = *bio_ptr;
	काष्ठा bio_crypt_ctx *bc = bio->bi_crypt_context;
	काष्ठा bio_fallback_crypt_ctx *f_ctx;

	अगर (WARN_ON_ONCE(!tfms_inited[bc->bc_key->crypto_cfg.crypto_mode])) अणु
		/* User didn't call blk_crypto_start_using_key() first */
		bio->bi_status = BLK_STS_IOERR;
		वापस false;
	पूर्ण

	अगर (!blk_ksm_crypto_cfg_supported(&blk_crypto_ksm,
					  &bc->bc_key->crypto_cfg)) अणु
		bio->bi_status = BLK_STS_NOTSUPP;
		वापस false;
	पूर्ण

	अगर (bio_data_dir(bio) == WRITE)
		वापस blk_crypto_fallback_encrypt_bio(bio_ptr);

	/*
	 * bio READ हाल: Set up a f_ctx in the bio's bi_निजी and set the
	 * bi_end_io appropriately to trigger decryption when the bio is ended.
	 */
	f_ctx = mempool_alloc(bio_fallback_crypt_ctx_pool, GFP_NOIO);
	f_ctx->crypt_ctx = *bc;
	f_ctx->crypt_iter = bio->bi_iter;
	f_ctx->bi_निजी_orig = bio->bi_निजी;
	f_ctx->bi_end_io_orig = bio->bi_end_io;
	bio->bi_निजी = (व्योम *)f_ctx;
	bio->bi_end_io = blk_crypto_fallback_decrypt_endio;
	bio_crypt_मुक्त_ctx(bio);

	वापस true;
पूर्ण

पूर्णांक blk_crypto_fallback_evict_key(स्थिर काष्ठा blk_crypto_key *key)
अणु
	वापस blk_ksm_evict_key(&blk_crypto_ksm, key);
पूर्ण

अटल bool blk_crypto_fallback_inited;
अटल पूर्णांक blk_crypto_fallback_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक err;

	अगर (blk_crypto_fallback_inited)
		वापस 0;

	pअक्रमom_bytes(blank_key, BLK_CRYPTO_MAX_KEY_SIZE);

	err = bioset_init(&crypto_bio_split, 64, 0, 0);
	अगर (err)
		जाओ out;

	err = blk_ksm_init(&blk_crypto_ksm, blk_crypto_num_keyslots);
	अगर (err)
		जाओ fail_मुक्त_bioset;
	err = -ENOMEM;

	blk_crypto_ksm.ksm_ll_ops = blk_crypto_ksm_ll_ops;
	blk_crypto_ksm.max_dun_bytes_supported = BLK_CRYPTO_MAX_IV_SIZE;

	/* All blk-crypto modes have a crypto API fallback. */
	क्रम (i = 0; i < BLK_ENCRYPTION_MODE_MAX; i++)
		blk_crypto_ksm.crypto_modes_supported[i] = 0xFFFFFFFF;
	blk_crypto_ksm.crypto_modes_supported[BLK_ENCRYPTION_MODE_INVALID] = 0;

	blk_crypto_wq = alloc_workqueue("blk_crypto_wq",
					WQ_UNBOUND | WQ_HIGHPRI |
					WQ_MEM_RECLAIM, num_online_cpus());
	अगर (!blk_crypto_wq)
		जाओ fail_मुक्त_ksm;

	blk_crypto_keyslots = kसुस्मृति(blk_crypto_num_keyslots,
				      माप(blk_crypto_keyslots[0]),
				      GFP_KERNEL);
	अगर (!blk_crypto_keyslots)
		जाओ fail_मुक्त_wq;

	blk_crypto_bounce_page_pool =
		mempool_create_page_pool(num_pपुनः_स्मृति_bounce_pg, 0);
	अगर (!blk_crypto_bounce_page_pool)
		जाओ fail_मुक्त_keyslots;

	bio_fallback_crypt_ctx_cache = KMEM_CACHE(bio_fallback_crypt_ctx, 0);
	अगर (!bio_fallback_crypt_ctx_cache)
		जाओ fail_मुक्त_bounce_page_pool;

	bio_fallback_crypt_ctx_pool =
		mempool_create_slab_pool(num_pपुनः_स्मृति_fallback_crypt_ctxs,
					 bio_fallback_crypt_ctx_cache);
	अगर (!bio_fallback_crypt_ctx_pool)
		जाओ fail_मुक्त_crypt_ctx_cache;

	blk_crypto_fallback_inited = true;

	वापस 0;
fail_मुक्त_crypt_ctx_cache:
	kmem_cache_destroy(bio_fallback_crypt_ctx_cache);
fail_मुक्त_bounce_page_pool:
	mempool_destroy(blk_crypto_bounce_page_pool);
fail_मुक्त_keyslots:
	kमुक्त(blk_crypto_keyslots);
fail_मुक्त_wq:
	destroy_workqueue(blk_crypto_wq);
fail_मुक्त_ksm:
	blk_ksm_destroy(&blk_crypto_ksm);
fail_मुक्त_bioset:
	bioset_निकास(&crypto_bio_split);
out:
	वापस err;
पूर्ण

/*
 * Prepare blk-crypto-fallback क्रम the specअगरied crypto mode.
 * Returns -ENOPKG अगर the needed crypto API support is missing.
 */
पूर्णांक blk_crypto_fallback_start_using_mode(क्रमागत blk_crypto_mode_num mode_num)
अणु
	स्थिर अक्षर *cipher_str = blk_crypto_modes[mode_num].cipher_str;
	काष्ठा blk_crypto_keyslot *slotp;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	/*
	 * Fast path
	 * Ensure that updates to blk_crypto_keyslots[i].tfms[mode_num]
	 * क्रम each i are visible beक्रमe we try to access them.
	 */
	अगर (likely(smp_load_acquire(&tfms_inited[mode_num])))
		वापस 0;

	mutex_lock(&tfms_init_lock);
	अगर (tfms_inited[mode_num])
		जाओ out;

	err = blk_crypto_fallback_init();
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < blk_crypto_num_keyslots; i++) अणु
		slotp = &blk_crypto_keyslots[i];
		slotp->tfms[mode_num] = crypto_alloc_skcipher(cipher_str, 0, 0);
		अगर (IS_ERR(slotp->tfms[mode_num])) अणु
			err = PTR_ERR(slotp->tfms[mode_num]);
			अगर (err == -ENOENT) अणु
				pr_warn_once("Missing crypto API support for \"%s\"\n",
					     cipher_str);
				err = -ENOPKG;
			पूर्ण
			slotp->tfms[mode_num] = शून्य;
			जाओ out_मुक्त_tfms;
		पूर्ण

		crypto_skcipher_set_flags(slotp->tfms[mode_num],
					  CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	पूर्ण

	/*
	 * Ensure that updates to blk_crypto_keyslots[i].tfms[mode_num]
	 * क्रम each i are visible beक्रमe we set tfms_inited[mode_num].
	 */
	smp_store_release(&tfms_inited[mode_num], true);
	जाओ out;

out_मुक्त_tfms:
	क्रम (i = 0; i < blk_crypto_num_keyslots; i++) अणु
		slotp = &blk_crypto_keyslots[i];
		crypto_मुक्त_skcipher(slotp->tfms[mode_num]);
		slotp->tfms[mode_num] = शून्य;
	पूर्ण
out:
	mutex_unlock(&tfms_init_lock);
	वापस err;
पूर्ण
