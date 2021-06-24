<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs-verity hash algorithms
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <crypto/hash.h>
#समावेश <linux/scatterlist.h>

/* The hash algorithms supported by fs-verity */
काष्ठा fsverity_hash_alg fsverity_hash_algs[] = अणु
	[FS_VERITY_HASH_ALG_SHA256] = अणु
		.name = "sha256",
		.digest_size = SHA256_DIGEST_SIZE,
		.block_size = SHA256_BLOCK_SIZE,
	पूर्ण,
	[FS_VERITY_HASH_ALG_SHA512] = अणु
		.name = "sha512",
		.digest_size = SHA512_DIGEST_SIZE,
		.block_size = SHA512_BLOCK_SIZE,
	पूर्ण,
पूर्ण;

अटल DEFINE_MUTEX(fsverity_hash_alg_init_mutex);

/**
 * fsverity_get_hash_alg() - validate and prepare a hash algorithm
 * @inode: optional inode क्रम logging purposes
 * @num: the hash algorithm number
 *
 * Get the काष्ठा fsverity_hash_alg क्रम the given hash algorithm number, and
 * ensure it has a hash transक्रमm पढ़ोy to go.  The hash transक्रमms are
 * allocated on-demand so that we करोn't waste resources unnecessarily, and
 * because the crypto modules may be initialized later than fs/verity/.
 *
 * Return: poपूर्णांकer to the hash alg on success, अन्यथा an ERR_PTR()
 */
काष्ठा fsverity_hash_alg *fsverity_get_hash_alg(स्थिर काष्ठा inode *inode,
						अचिन्हित पूर्णांक num)
अणु
	काष्ठा fsverity_hash_alg *alg;
	काष्ठा crypto_ahash *tfm;
	पूर्णांक err;

	अगर (num >= ARRAY_SIZE(fsverity_hash_algs) ||
	    !fsverity_hash_algs[num].name) अणु
		fsverity_warn(inode, "Unknown hash algorithm number: %u", num);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	alg = &fsverity_hash_algs[num];

	/* pairs with smp_store_release() below */
	अगर (likely(smp_load_acquire(&alg->tfm) != शून्य))
		वापस alg;

	mutex_lock(&fsverity_hash_alg_init_mutex);

	अगर (alg->tfm != शून्य)
		जाओ out_unlock;

	/*
	 * Using the shash API would make things a bit simpler, but the ahash
	 * API is preferable as it allows the use of crypto accelerators.
	 */
	tfm = crypto_alloc_ahash(alg->name, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		अगर (PTR_ERR(tfm) == -ENOENT) अणु
			fsverity_warn(inode,
				      "Missing crypto API support for hash algorithm \"%s\"",
				      alg->name);
			alg = ERR_PTR(-ENOPKG);
			जाओ out_unlock;
		पूर्ण
		fsverity_err(inode,
			     "Error allocating hash algorithm \"%s\": %ld",
			     alg->name, PTR_ERR(tfm));
		alg = ERR_CAST(tfm);
		जाओ out_unlock;
	पूर्ण

	err = -EINVAL;
	अगर (WARN_ON(alg->digest_size != crypto_ahash_digestsize(tfm)))
		जाओ err_मुक्त_tfm;
	अगर (WARN_ON(alg->block_size != crypto_ahash_blocksize(tfm)))
		जाओ err_मुक्त_tfm;

	err = mempool_init_kदो_स्मृति_pool(&alg->req_pool, 1,
					माप(काष्ठा ahash_request) +
					crypto_ahash_reqsize(tfm));
	अगर (err)
		जाओ err_मुक्त_tfm;

	pr_info("%s using implementation \"%s\"\n",
		alg->name, crypto_ahash_driver_name(tfm));

	/* pairs with smp_load_acquire() above */
	smp_store_release(&alg->tfm, tfm);
	जाओ out_unlock;

err_मुक्त_tfm:
	crypto_मुक्त_ahash(tfm);
	alg = ERR_PTR(err);
out_unlock:
	mutex_unlock(&fsverity_hash_alg_init_mutex);
	वापस alg;
पूर्ण

/**
 * fsverity_alloc_hash_request() - allocate a hash request object
 * @alg: the hash algorithm क्रम which to allocate the request
 * @gfp_flags: memory allocation flags
 *
 * This is mempool-backed, so this never fails अगर __GFP_सूचीECT_RECLAIM is set in
 * @gfp_flags.  However, in that हाल this might need to रुको क्रम all
 * previously-allocated requests to be मुक्तd.  So to aव्योम deadlocks, callers
 * must never need multiple requests at a समय to make क्रमward progress.
 *
 * Return: the request object on success; शून्य on failure (but see above)
 */
काष्ठा ahash_request *fsverity_alloc_hash_request(काष्ठा fsverity_hash_alg *alg,
						  gfp_t gfp_flags)
अणु
	काष्ठा ahash_request *req = mempool_alloc(&alg->req_pool, gfp_flags);

	अगर (req)
		ahash_request_set_tfm(req, alg->tfm);
	वापस req;
पूर्ण

/**
 * fsverity_मुक्त_hash_request() - मुक्त a hash request object
 * @alg: the hash algorithm
 * @req: the hash request object to मुक्त
 */
व्योम fsverity_मुक्त_hash_request(काष्ठा fsverity_hash_alg *alg,
				काष्ठा ahash_request *req)
अणु
	अगर (req) अणु
		ahash_request_zero(req);
		mempool_मुक्त(req, &alg->req_pool);
	पूर्ण
पूर्ण

/**
 * fsverity_prepare_hash_state() - precompute the initial hash state
 * @alg: hash algorithm
 * @salt: a salt which is to be prepended to all data to be hashed
 * @salt_size: salt size in bytes, possibly 0
 *
 * Return: शून्य अगर the salt is empty, otherwise the kदो_स्मृति()'ed precomputed
 *	   initial hash state on success or an ERR_PTR() on failure.
 */
स्थिर u8 *fsverity_prepare_hash_state(काष्ठा fsverity_hash_alg *alg,
				      स्थिर u8 *salt, माप_प्रकार salt_size)
अणु
	u8 *hashstate = शून्य;
	काष्ठा ahash_request *req = शून्य;
	u8 *padded_salt = शून्य;
	माप_प्रकार padded_salt_size;
	काष्ठा scatterlist sg;
	DECLARE_CRYPTO_WAIT(रुको);
	पूर्णांक err;

	अगर (salt_size == 0)
		वापस शून्य;

	hashstate = kदो_स्मृति(crypto_ahash_statesize(alg->tfm), GFP_KERNEL);
	अगर (!hashstate)
		वापस ERR_PTR(-ENOMEM);

	/* This allocation never fails, since it's mempool-backed. */
	req = fsverity_alloc_hash_request(alg, GFP_KERNEL);

	/*
	 * Zero-pad the salt to the next multiple of the input size of the hash
	 * algorithm's compression function, e.g. 64 bytes क्रम SHA-256 or 128
	 * bytes क्रम SHA-512.  This ensures that the hash algorithm won't have
	 * any bytes buffered पूर्णांकernally after processing the salt, thus making
	 * salted hashing just as fast as unsalted hashing.
	 */
	padded_salt_size = round_up(salt_size, alg->block_size);
	padded_salt = kzalloc(padded_salt_size, GFP_KERNEL);
	अगर (!padded_salt) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण
	स_नकल(padded_salt, salt, salt_size);

	sg_init_one(&sg, padded_salt, padded_salt_size);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);
	ahash_request_set_crypt(req, &sg, शून्य, padded_salt_size);

	err = crypto_रुको_req(crypto_ahash_init(req), &रुको);
	अगर (err)
		जाओ err_मुक्त;

	err = crypto_रुको_req(crypto_ahash_update(req), &रुको);
	अगर (err)
		जाओ err_मुक्त;

	err = crypto_ahash_export(req, hashstate);
	अगर (err)
		जाओ err_मुक्त;
out:
	fsverity_मुक्त_hash_request(alg, req);
	kमुक्त(padded_salt);
	वापस hashstate;

err_मुक्त:
	kमुक्त(hashstate);
	hashstate = ERR_PTR(err);
	जाओ out;
पूर्ण

/**
 * fsverity_hash_page() - hash a single data or hash page
 * @params: the Merkle tree's parameters
 * @inode: inode क्रम which the hashing is being करोne
 * @req: pपुनः_स्मृतिated hash request
 * @page: the page to hash
 * @out: output digest, size 'params->digest_size' bytes
 *
 * Hash a single data or hash block, assuming block_size == PAGE_SIZE.
 * The hash is salted अगर a salt is specअगरied in the Merkle tree parameters.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_hash_page(स्थिर काष्ठा merkle_tree_params *params,
		       स्थिर काष्ठा inode *inode,
		       काष्ठा ahash_request *req, काष्ठा page *page, u8 *out)
अणु
	काष्ठा scatterlist sg;
	DECLARE_CRYPTO_WAIT(रुको);
	पूर्णांक err;

	अगर (WARN_ON(params->block_size != PAGE_SIZE))
		वापस -EINVAL;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, page, PAGE_SIZE, 0);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);
	ahash_request_set_crypt(req, &sg, out, PAGE_SIZE);

	अगर (params->hashstate) अणु
		err = crypto_ahash_import(req, params->hashstate);
		अगर (err) अणु
			fsverity_err(inode,
				     "Error %d importing hash state", err);
			वापस err;
		पूर्ण
		err = crypto_ahash_finup(req);
	पूर्ण अन्यथा अणु
		err = crypto_ahash_digest(req);
	पूर्ण

	err = crypto_रुको_req(err, &रुको);
	अगर (err)
		fsverity_err(inode, "Error %d computing page hash", err);
	वापस err;
पूर्ण

/**
 * fsverity_hash_buffer() - hash some data
 * @alg: the hash algorithm to use
 * @data: the data to hash
 * @size: size of data to hash, in bytes
 * @out: output digest, size 'alg->digest_size' bytes
 *
 * Hash some data which is located in physically contiguous memory (i.e. memory
 * allocated by kदो_स्मृति(), not by vदो_स्मृति()).  No salt is used.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fsverity_hash_buffer(काष्ठा fsverity_hash_alg *alg,
			 स्थिर व्योम *data, माप_प्रकार size, u8 *out)
अणु
	काष्ठा ahash_request *req;
	काष्ठा scatterlist sg;
	DECLARE_CRYPTO_WAIT(रुको);
	पूर्णांक err;

	/* This allocation never fails, since it's mempool-backed. */
	req = fsverity_alloc_hash_request(alg, GFP_KERNEL);

	sg_init_one(&sg, data, size);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);
	ahash_request_set_crypt(req, &sg, out, size);

	err = crypto_रुको_req(crypto_ahash_digest(req), &रुको);

	fsverity_मुक्त_hash_request(alg, req);
	वापस err;
पूर्ण

व्योम __init fsverity_check_hash_algs(व्योम)
अणु
	माप_प्रकार i;

	/*
	 * Sanity check the hash algorithms (could be a build-समय check, but
	 * they're in an array)
	 */
	क्रम (i = 0; i < ARRAY_SIZE(fsverity_hash_algs); i++) अणु
		स्थिर काष्ठा fsverity_hash_alg *alg = &fsverity_hash_algs[i];

		अगर (!alg->name)
			जारी;

		BUG_ON(alg->digest_size > FS_VERITY_MAX_DIGEST_SIZE);

		/*
		 * For efficiency, the implementation currently assumes the
		 * digest and block sizes are घातers of 2.  This limitation can
		 * be lअगरted अगर the code is updated to handle other values.
		 */
		BUG_ON(!is_घातer_of_2(alg->digest_size));
		BUG_ON(!is_घातer_of_2(alg->block_size));
	पूर्ण
पूर्ण
