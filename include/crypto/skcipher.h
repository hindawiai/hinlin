<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Symmetric key ciphers.
 * 
 * Copyright (c) 2007-2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_SKCIPHER_H
#घोषणा _CRYPTO_SKCIPHER_H

#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

/**
 *	काष्ठा skcipher_request - Symmetric key cipher request
 *	@cryptlen: Number of bytes to encrypt or decrypt
 *	@iv: Initialisation Vector
 *	@src: Source SG list
 *	@dst: Destination SG list
 *	@base: Underlying async request
 *	@__ctx: Start of निजी context data
 */
काष्ठा skcipher_request अणु
	अचिन्हित पूर्णांक cryptlen;

	u8 *iv;

	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;

	काष्ठा crypto_async_request base;

	व्योम *__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

काष्ठा crypto_skcipher अणु
	अचिन्हित पूर्णांक reqsize;

	काष्ठा crypto_tfm base;
पूर्ण;

काष्ठा crypto_sync_skcipher अणु
	काष्ठा crypto_skcipher base;
पूर्ण;

/**
 * काष्ठा skcipher_alg - symmetric key cipher definition
 * @min_keysize: Minimum key size supported by the transक्रमmation. This is the
 *		 smallest key length supported by this transक्रमmation algorithm.
 *		 This must be set to one of the pre-defined values as this is
 *		 not hardware specअगरic. Possible values क्रम this field can be
 *		 found via git grep "_MIN_KEY_SIZE" include/crypto/
 * @max_keysize: Maximum key size supported by the transक्रमmation. This is the
 *		 largest key length supported by this transक्रमmation algorithm.
 *		 This must be set to one of the pre-defined values as this is
 *		 not hardware specअगरic. Possible values क्रम this field can be
 *		 found via git grep "_MAX_KEY_SIZE" include/crypto/
 * @setkey: Set key क्रम the transक्रमmation. This function is used to either
 *	    program a supplied key पूर्णांकo the hardware or store the key in the
 *	    transक्रमmation context क्रम programming it later. Note that this
 *	    function करोes modअगरy the transक्रमmation context. This function can
 *	    be called multiple बार during the existence of the transक्रमmation
 *	    object, so one must make sure the key is properly reprogrammed पूर्णांकo
 *	    the hardware. This function is also responsible क्रम checking the key
 *	    length क्रम validity. In हाल a software fallback was put in place in
 *	    the @cra_init call, this function might need to use the fallback अगर
 *	    the algorithm करोesn't support all of the key sizes.
 * @encrypt: Encrypt a scatterlist of blocks. This function is used to encrypt
 *	     the supplied scatterlist containing the blocks of data. The crypto
 *	     API consumer is responsible क्रम aligning the entries of the
 *	     scatterlist properly and making sure the chunks are correctly
 *	     sized. In हाल a software fallback was put in place in the
 *	     @cra_init call, this function might need to use the fallback अगर
 *	     the algorithm करोesn't support all of the key sizes. In हाल the
 *	     key was stored in transक्रमmation context, the key might need to be
 *	     re-programmed पूर्णांकo the hardware in this function. This function
 *	     shall not modअगरy the transक्रमmation context, as this function may
 *	     be called in parallel with the same transक्रमmation object.
 * @decrypt: Decrypt a single block. This is a reverse counterpart to @encrypt
 *	     and the conditions are exactly the same.
 * @init: Initialize the cryptographic transक्रमmation object. This function
 *	  is used to initialize the cryptographic transक्रमmation object.
 *	  This function is called only once at the instantiation समय, right
 *	  after the transक्रमmation context was allocated. In हाल the
 *	  cryptographic hardware has some special requirements which need to
 *	  be handled by software, this function shall check क्रम the precise
 *	  requirement of the transक्रमmation and put any software fallbacks
 *	  in place.
 * @निकास: Deinitialize the cryptographic transक्रमmation object. This is a
 *	  counterpart to @init, used to हटाओ various changes set in
 *	  @init.
 * @ivsize: IV size applicable क्रम transक्रमmation. The consumer must provide an
 *	    IV of exactly that size to perक्रमm the encrypt or decrypt operation.
 * @chunksize: Equal to the block size except क्रम stream ciphers such as
 *	       CTR where it is set to the underlying block size.
 * @walksize: Equal to the chunk size except in हालs where the algorithm is
 * 	      considerably more efficient अगर it can operate on multiple chunks
 * 	      in parallel. Should be a multiple of chunksize.
 * @base: Definition of a generic crypto algorithm.
 *
 * All fields except @ivsize are mandatory and must be filled.
 */
काष्ठा skcipher_alg अणु
	पूर्णांक (*setkey)(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
	              अचिन्हित पूर्णांक keylen);
	पूर्णांक (*encrypt)(काष्ठा skcipher_request *req);
	पूर्णांक (*decrypt)(काष्ठा skcipher_request *req);
	पूर्णांक (*init)(काष्ठा crypto_skcipher *tfm);
	व्योम (*निकास)(काष्ठा crypto_skcipher *tfm);

	अचिन्हित पूर्णांक min_keysize;
	अचिन्हित पूर्णांक max_keysize;
	अचिन्हित पूर्णांक ivsize;
	अचिन्हित पूर्णांक chunksize;
	अचिन्हित पूर्णांक walksize;

	काष्ठा crypto_alg base;
पूर्ण;

#घोषणा MAX_SYNC_SKCIPHER_REQSIZE      384
/*
 * This perक्रमms a type-check against the "tfm" argument to make sure
 * all users have the correct skcipher tfm क्रम करोing on-stack requests.
 */
#घोषणा SYNC_SKCIPHER_REQUEST_ON_STACK(name, tfm) \
	अक्षर __##name##_desc[माप(काष्ठा skcipher_request) + \
			     MAX_SYNC_SKCIPHER_REQSIZE + \
			     (!(माप((काष्ठा crypto_sync_skcipher *)1 == \
				       (typeof(tfm))1))) \
			    ] CRYPTO_MINALIGN_ATTR; \
	काष्ठा skcipher_request *name = (व्योम *)__##name##_desc

/**
 * DOC: Symmetric Key Cipher API
 *
 * Symmetric key cipher API is used with the ciphers of type
 * CRYPTO_ALG_TYPE_SKCIPHER (listed as type "skcipher" in /proc/crypto).
 *
 * Asynchronous cipher operations imply that the function invocation क्रम a
 * cipher request वापसs immediately beक्रमe the completion of the operation.
 * The cipher request is scheduled as a separate kernel thपढ़ो and thereक्रमe
 * load-balanced on the dअगरferent CPUs via the process scheduler. To allow
 * the kernel crypto API to inक्रमm the caller about the completion of a cipher
 * request, the caller must provide a callback function. That function is
 * invoked with the cipher handle when the request completes.
 *
 * To support the asynchronous operation, additional inक्रमmation than just the
 * cipher handle must be supplied to the kernel crypto API. That additional
 * inक्रमmation is given by filling in the skcipher_request data काष्ठाure.
 *
 * For the symmetric key cipher API, the state is मुख्यtained with the tfm
 * cipher handle. A single tfm can be used across multiple calls and in
 * parallel. For asynchronous block cipher calls, context data supplied and
 * only used by the caller can be referenced the request data काष्ठाure in
 * addition to the IV used क्रम the cipher request. The मुख्यtenance of such
 * state inक्रमmation would be important क्रम a crypto driver implementer to
 * have, because when calling the callback function upon completion of the
 * cipher operation, that callback function may need some inक्रमmation about
 * which operation just finished अगर it invoked multiple in parallel. This
 * state inक्रमmation is unused by the kernel crypto API.
 */

अटल अंतरभूत काष्ठा crypto_skcipher *__crypto_skcipher_cast(
	काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_skcipher, base);
पूर्ण

/**
 * crypto_alloc_skcipher() - allocate symmetric key cipher handle
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      skcipher cipher
 * @type: specअगरies the type of the cipher
 * @mask: specअगरies the mask क्रम the cipher
 *
 * Allocate a cipher handle क्रम an skcipher. The वापसed काष्ठा
 * crypto_skcipher is the cipher handle that is required क्रम any subsequent
 * API invocation क्रम that skcipher.
 *
 * Return: allocated cipher handle in हाल of success; IS_ERR() is true in हाल
 *	   of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_skcipher *crypto_alloc_skcipher(स्थिर अक्षर *alg_name,
					      u32 type, u32 mask);

काष्ठा crypto_sync_skcipher *crypto_alloc_sync_skcipher(स्थिर अक्षर *alg_name,
					      u32 type, u32 mask);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_skcipher_tfm(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस &tfm->base;
पूर्ण

/**
 * crypto_मुक्त_skcipher() - zeroize and मुक्त cipher handle
 * @tfm: cipher handle to be मुक्तd
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_skcipher(काष्ठा crypto_skcipher *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_skcipher_tfm(tfm));
पूर्ण

अटल अंतरभूत व्योम crypto_मुक्त_sync_skcipher(काष्ठा crypto_sync_skcipher *tfm)
अणु
	crypto_मुक्त_skcipher(&tfm->base);
पूर्ण

/**
 * crypto_has_skcipher() - Search क्रम the availability of an skcipher.
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      skcipher
 * @type: specअगरies the type of the skcipher
 * @mask: specअगरies the mask क्रम the skcipher
 *
 * Return: true when the skcipher is known to the kernel crypto API; false
 *	   otherwise
 */
पूर्णांक crypto_has_skcipher(स्थिर अक्षर *alg_name, u32 type, u32 mask);

अटल अंतरभूत स्थिर अक्षर *crypto_skcipher_driver_name(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_tfm_alg_driver_name(crypto_skcipher_tfm(tfm));
पूर्ण

अटल अंतरभूत काष्ठा skcipher_alg *crypto_skcipher_alg(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस container_of(crypto_skcipher_tfm(tfm)->__crt_alg,
			    काष्ठा skcipher_alg, base);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_alg_ivsize(काष्ठा skcipher_alg *alg)
अणु
	वापस alg->ivsize;
पूर्ण

/**
 * crypto_skcipher_ivsize() - obtain IV size
 * @tfm: cipher handle
 *
 * The size of the IV क्रम the skcipher referenced by the cipher handle is
 * वापसed. This IV size may be zero अगर the cipher करोes not need an IV.
 *
 * Return: IV size in bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_ivsize(काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_skcipher_alg(tfm)->ivsize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_sync_skcipher_ivsize(
	काष्ठा crypto_sync_skcipher *tfm)
अणु
	वापस crypto_skcipher_ivsize(&tfm->base);
पूर्ण

/**
 * crypto_skcipher_blocksize() - obtain block size of cipher
 * @tfm: cipher handle
 *
 * The block size क्रम the skcipher referenced with the cipher handle is
 * वापसed. The caller may use that inक्रमmation to allocate appropriate
 * memory क्रम the data वापसed by the encryption or decryption operation
 *
 * Return: block size of cipher
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_blocksize(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_tfm_alg_blocksize(crypto_skcipher_tfm(tfm));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_alg_chunksize(
	काष्ठा skcipher_alg *alg)
अणु
	वापस alg->chunksize;
पूर्ण

/**
 * crypto_skcipher_chunksize() - obtain chunk size
 * @tfm: cipher handle
 *
 * The block size is set to one क्रम ciphers such as CTR.  However,
 * you still need to provide incremental updates in multiples of
 * the underlying block size as the IV करोes not have sub-block
 * granularity.  This is known in this API as the chunk size.
 *
 * Return: chunk size in bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_chunksize(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_skcipher_alg_chunksize(crypto_skcipher_alg(tfm));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_sync_skcipher_blocksize(
	काष्ठा crypto_sync_skcipher *tfm)
अणु
	वापस crypto_skcipher_blocksize(&tfm->base);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_alignmask(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_tfm_alg_alignmask(crypto_skcipher_tfm(tfm));
पूर्ण

अटल अंतरभूत u32 crypto_skcipher_get_flags(काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_tfm_get_flags(crypto_skcipher_tfm(tfm));
पूर्ण

अटल अंतरभूत व्योम crypto_skcipher_set_flags(काष्ठा crypto_skcipher *tfm,
					       u32 flags)
अणु
	crypto_tfm_set_flags(crypto_skcipher_tfm(tfm), flags);
पूर्ण

अटल अंतरभूत व्योम crypto_skcipher_clear_flags(काष्ठा crypto_skcipher *tfm,
						 u32 flags)
अणु
	crypto_tfm_clear_flags(crypto_skcipher_tfm(tfm), flags);
पूर्ण

अटल अंतरभूत u32 crypto_sync_skcipher_get_flags(
	काष्ठा crypto_sync_skcipher *tfm)
अणु
	वापस crypto_skcipher_get_flags(&tfm->base);
पूर्ण

अटल अंतरभूत व्योम crypto_sync_skcipher_set_flags(
	काष्ठा crypto_sync_skcipher *tfm, u32 flags)
अणु
	crypto_skcipher_set_flags(&tfm->base, flags);
पूर्ण

अटल अंतरभूत व्योम crypto_sync_skcipher_clear_flags(
	काष्ठा crypto_sync_skcipher *tfm, u32 flags)
अणु
	crypto_skcipher_clear_flags(&tfm->base, flags);
पूर्ण

/**
 * crypto_skcipher_setkey() - set key क्रम cipher
 * @tfm: cipher handle
 * @key: buffer holding the key
 * @keylen: length of the key in bytes
 *
 * The caller provided key is set क्रम the skcipher referenced by the cipher
 * handle.
 *
 * Note, the key length determines the cipher type. Many block ciphers implement
 * dअगरferent cipher modes depending on the key size, such as AES-128 vs AES-192
 * vs. AES-256. When providing a 16 byte key क्रम an AES cipher handle, AES-128
 * is perक्रमmed.
 *
 * Return: 0 अगर the setting of the key was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_skcipher_setkey(काष्ठा crypto_skcipher *tfm,
			   स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

अटल अंतरभूत पूर्णांक crypto_sync_skcipher_setkey(काष्ठा crypto_sync_skcipher *tfm,
					 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto_skcipher_setkey(&tfm->base, key, keylen);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_min_keysize(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_skcipher_alg(tfm)->min_keysize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_max_keysize(
	काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_skcipher_alg(tfm)->max_keysize;
पूर्ण

/**
 * crypto_skcipher_reqtfm() - obtain cipher handle from request
 * @req: skcipher_request out of which the cipher handle is to be obtained
 *
 * Return the crypto_skcipher handle when furnishing an skcipher_request
 * data काष्ठाure.
 *
 * Return: crypto_skcipher handle
 */
अटल अंतरभूत काष्ठा crypto_skcipher *crypto_skcipher_reqtfm(
	काष्ठा skcipher_request *req)
अणु
	वापस __crypto_skcipher_cast(req->base.tfm);
पूर्ण

अटल अंतरभूत काष्ठा crypto_sync_skcipher *crypto_sync_skcipher_reqtfm(
	काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);

	वापस container_of(tfm, काष्ठा crypto_sync_skcipher, base);
पूर्ण

/**
 * crypto_skcipher_encrypt() - encrypt plaपूर्णांकext
 * @req: reference to the skcipher_request handle that holds all inक्रमmation
 *	 needed to perक्रमm the cipher operation
 *
 * Encrypt plaपूर्णांकext data using the skcipher_request handle. That data
 * काष्ठाure and how it is filled with data is discussed with the
 * skcipher_request_* functions.
 *
 * Return: 0 अगर the cipher operation was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_skcipher_encrypt(काष्ठा skcipher_request *req);

/**
 * crypto_skcipher_decrypt() - decrypt ciphertext
 * @req: reference to the skcipher_request handle that holds all inक्रमmation
 *	 needed to perक्रमm the cipher operation
 *
 * Decrypt ciphertext data using the skcipher_request handle. That data
 * काष्ठाure and how it is filled with data is discussed with the
 * skcipher_request_* functions.
 *
 * Return: 0 अगर the cipher operation was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_skcipher_decrypt(काष्ठा skcipher_request *req);

/**
 * DOC: Symmetric Key Cipher Request Handle
 *
 * The skcipher_request data काष्ठाure contains all poपूर्णांकers to data
 * required क्रम the symmetric key cipher operation. This includes the cipher
 * handle (which can be used by multiple skcipher_request instances), poपूर्णांकer
 * to plaपूर्णांकext and ciphertext, asynchronous callback function, etc. It acts
 * as a handle to the skcipher_request_* API calls in a similar way as
 * skcipher handle to the crypto_skcipher_* API calls.
 */

/**
 * crypto_skcipher_reqsize() - obtain size of the request data काष्ठाure
 * @tfm: cipher handle
 *
 * Return: number of bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_skcipher_reqsize(काष्ठा crypto_skcipher *tfm)
अणु
	वापस tfm->reqsize;
पूर्ण

/**
 * skcipher_request_set_tfm() - update cipher handle reference in request
 * @req: request handle to be modअगरied
 * @tfm: cipher handle that shall be added to the request handle
 *
 * Allow the caller to replace the existing skcipher handle in the request
 * data काष्ठाure with a dअगरferent one.
 */
अटल अंतरभूत व्योम skcipher_request_set_tfm(काष्ठा skcipher_request *req,
					    काष्ठा crypto_skcipher *tfm)
अणु
	req->base.tfm = crypto_skcipher_tfm(tfm);
पूर्ण

अटल अंतरभूत व्योम skcipher_request_set_sync_tfm(काष्ठा skcipher_request *req,
					    काष्ठा crypto_sync_skcipher *tfm)
अणु
	skcipher_request_set_tfm(req, &tfm->base);
पूर्ण

अटल अंतरभूत काष्ठा skcipher_request *skcipher_request_cast(
	काष्ठा crypto_async_request *req)
अणु
	वापस container_of(req, काष्ठा skcipher_request, base);
पूर्ण

/**
 * skcipher_request_alloc() - allocate request data काष्ठाure
 * @tfm: cipher handle to be रेजिस्टरed with the request
 * @gfp: memory allocation flag that is handed to kदो_स्मृति by the API call.
 *
 * Allocate the request data काष्ठाure that must be used with the skcipher
 * encrypt and decrypt API calls. During the allocation, the provided skcipher
 * handle is रेजिस्टरed in the request data काष्ठाure.
 *
 * Return: allocated request handle in हाल of success, or शून्य अगर out of memory
 */
अटल अंतरभूत काष्ठा skcipher_request *skcipher_request_alloc(
	काष्ठा crypto_skcipher *tfm, gfp_t gfp)
अणु
	काष्ठा skcipher_request *req;

	req = kदो_स्मृति(माप(काष्ठा skcipher_request) +
		      crypto_skcipher_reqsize(tfm), gfp);

	अगर (likely(req))
		skcipher_request_set_tfm(req, tfm);

	वापस req;
पूर्ण

/**
 * skcipher_request_मुक्त() - zeroize and मुक्त request data काष्ठाure
 * @req: request data काष्ठाure cipher handle to be मुक्तd
 */
अटल अंतरभूत व्योम skcipher_request_मुक्त(काष्ठा skcipher_request *req)
अणु
	kमुक्त_sensitive(req);
पूर्ण

अटल अंतरभूत व्योम skcipher_request_zero(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);

	memzero_explicit(req, माप(*req) + crypto_skcipher_reqsize(tfm));
पूर्ण

/**
 * skcipher_request_set_callback() - set asynchronous callback function
 * @req: request handle
 * @flags: specअगरy zero or an ORing of the flags
 *	   CRYPTO_TFM_REQ_MAY_BACKLOG the request queue may back log and
 *	   increase the रुको queue beyond the initial maximum size;
 *	   CRYPTO_TFM_REQ_MAY_SLEEP the request processing may sleep
 * @compl: callback function poपूर्णांकer to be रेजिस्टरed with the request handle
 * @data: The data poपूर्णांकer refers to memory that is not used by the kernel
 *	  crypto API, but provided to the callback function क्रम it to use. Here,
 *	  the caller can provide a reference to memory the callback function can
 *	  operate on. As the callback function is invoked asynchronously to the
 *	  related functionality, it may need to access data काष्ठाures of the
 *	  related functionality which can be referenced using this poपूर्णांकer. The
 *	  callback function can access the memory via the "data" field in the
 *	  crypto_async_request data काष्ठाure provided to the callback function.
 *
 * This function allows setting the callback function that is triggered once the
 * cipher operation completes.
 *
 * The callback function is रेजिस्टरed with the skcipher_request handle and
 * must comply with the following ढाँचा::
 *
 *	व्योम callback_function(काष्ठा crypto_async_request *req, पूर्णांक error)
 */
अटल अंतरभूत व्योम skcipher_request_set_callback(काष्ठा skcipher_request *req,
						 u32 flags,
						 crypto_completion_t compl,
						 व्योम *data)
अणु
	req->base.complete = compl;
	req->base.data = data;
	req->base.flags = flags;
पूर्ण

/**
 * skcipher_request_set_crypt() - set data buffers
 * @req: request handle
 * @src: source scatter / gather list
 * @dst: destination scatter / gather list
 * @cryptlen: number of bytes to process from @src
 * @iv: IV क्रम the cipher operation which must comply with the IV size defined
 *      by crypto_skcipher_ivsize
 *
 * This function allows setting of the source data and destination data
 * scatter / gather lists.
 *
 * For encryption, the source is treated as the plaपूर्णांकext and the
 * destination is the ciphertext. For a decryption operation, the use is
 * reversed - the source is the ciphertext and the destination is the plaपूर्णांकext.
 */
अटल अंतरभूत व्योम skcipher_request_set_crypt(
	काष्ठा skcipher_request *req,
	काष्ठा scatterlist *src, काष्ठा scatterlist *dst,
	अचिन्हित पूर्णांक cryptlen, व्योम *iv)
अणु
	req->src = src;
	req->dst = dst;
	req->cryptlen = cryptlen;
	req->iv = iv;
पूर्ण

#पूर्ण_अगर	/* _CRYPTO_SKCIPHER_H */

