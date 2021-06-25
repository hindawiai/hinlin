<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hash: Hash algorithms under the crypto API
 * 
 * Copyright (c) 2008 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_HASH_H
#घोषणा _CRYPTO_HASH_H

#समावेश <linux/crypto.h>
#समावेश <linux/माला.स>

काष्ठा crypto_ahash;

/**
 * DOC: Message Digest Algorithm Definitions
 *
 * These data काष्ठाures define modular message digest algorithm
 * implementations, managed via crypto_रेजिस्टर_ahash(),
 * crypto_रेजिस्टर_shash(), crypto_unरेजिस्टर_ahash() and
 * crypto_unरेजिस्टर_shash().
 */

/**
 * काष्ठा hash_alg_common - define properties of message digest
 * @digestsize: Size of the result of the transक्रमmation. A buffer of this size
 *	        must be available to the @final and @finup calls, so they can
 *	        store the resulting hash पूर्णांकo it. For various predefined sizes,
 *	        search include/crypto/ using
 *	        git grep _DIGEST_SIZE include/crypto.
 * @statesize: Size of the block क्रम partial state of the transक्रमmation. A
 *	       buffer of this size must be passed to the @export function as it
 *	       will save the partial state of the transक्रमmation पूर्णांकo it. On the
 *	       other side, the @import function will load the state from a
 *	       buffer of this size as well.
 * @base: Start of data काष्ठाure of cipher algorithm. The common data
 *	  काष्ठाure of crypto_alg contains inक्रमmation common to all ciphers.
 *	  The hash_alg_common data काष्ठाure now adds the hash-specअगरic
 *	  inक्रमmation.
 */
काष्ठा hash_alg_common अणु
	अचिन्हित पूर्णांक digestsize;
	अचिन्हित पूर्णांक statesize;

	काष्ठा crypto_alg base;
पूर्ण;

काष्ठा ahash_request अणु
	काष्ठा crypto_async_request base;

	अचिन्हित पूर्णांक nbytes;
	काष्ठा scatterlist *src;
	u8 *result;

	/* This field may only be used by the ahash API code. */
	व्योम *priv;

	व्योम *__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

/**
 * काष्ठा ahash_alg - asynchronous message digest definition
 * @init: **[mandatory]** Initialize the transक्रमmation context. Intended only to initialize the
 *	  state of the HASH transक्रमmation at the beginning. This shall fill in
 *	  the पूर्णांकernal काष्ठाures used during the entire duration of the whole
 *	  transक्रमmation. No data processing happens at this poपूर्णांक. Driver code
 *	  implementation must not use req->result.
 * @update: **[mandatory]** Push a chunk of data पूर्णांकo the driver क्रम transक्रमmation. This
 *	   function actually pushes blocks of data from upper layers पूर्णांकo the
 *	   driver, which then passes those to the hardware as seen fit. This
 *	   function must not finalize the HASH transक्रमmation by calculating the
 *	   final message digest as this only adds more data पूर्णांकo the
 *	   transक्रमmation. This function shall not modअगरy the transक्रमmation
 *	   context, as this function may be called in parallel with the same
 *	   transक्रमmation object. Data processing can happen synchronously
 *	   [SHASH] or asynchronously [AHASH] at this poपूर्णांक. Driver must not use
 *	   req->result.
 * @final: **[mandatory]** Retrieve result from the driver. This function finalizes the
 *	   transक्रमmation and retrieves the resulting hash from the driver and
 *	   pushes it back to upper layers. No data processing happens at this
 *	   poपूर्णांक unless hardware requires it to finish the transक्रमmation
 *	   (then the data buffered by the device driver is processed).
 * @finup: **[optional]** Combination of @update and @final. This function is effectively a
 *	   combination of @update and @final calls issued in sequence. As some
 *	   hardware cannot करो @update and @final separately, this callback was
 *	   added to allow such hardware to be used at least by IPsec. Data
 *	   processing can happen synchronously [SHASH] or asynchronously [AHASH]
 *	   at this poपूर्णांक.
 * @digest: Combination of @init and @update and @final. This function
 *	    effectively behaves as the entire chain of operations, @init,
 *	    @update and @final issued in sequence. Just like @finup, this was
 *	    added क्रम hardware which cannot करो even the @finup, but can only करो
 *	    the whole transक्रमmation in one run. Data processing can happen
 *	    synchronously [SHASH] or asynchronously [AHASH] at this poपूर्णांक.
 * @setkey: Set optional key used by the hashing algorithm. Intended to push
 *	    optional key used by the hashing algorithm from upper layers पूर्णांकo
 *	    the driver. This function can store the key in the transक्रमmation
 *	    context or can outright program it पूर्णांकo the hardware. In the क्रमmer
 *	    हाल, one must be careful to program the key पूर्णांकo the hardware at
 *	    appropriate समय and one must be careful that .setkey() can be
 *	    called multiple बार during the existence of the transक्रमmation
 *	    object. Not  all hashing algorithms करो implement this function as it
 *	    is only needed क्रम keyed message digests. SHAx/MDx/CRCx करो NOT
 *	    implement this function. HMAC(MDx)/HMAC(SHAx)/CMAC(AES) करो implement
 *	    this function. This function must be called beक्रमe any other of the
 *	    @init, @update, @final, @finup, @digest is called. No data
 *	    processing happens at this poपूर्णांक.
 * @export: Export partial state of the transक्रमmation. This function dumps the
 *	    entire state of the ongoing transक्रमmation पूर्णांकo a provided block of
 *	    data so it can be @import 'ed back later on. This is useful in हाल
 *	    you want to save partial result of the transक्रमmation after
 *	    processing certain amount of data and reload this partial result
 *	    multiple बार later on क्रम multiple re-use. No data processing
 *	    happens at this poपूर्णांक. Driver must not use req->result.
 * @import: Import partial state of the transक्रमmation. This function loads the
 *	    entire state of the ongoing transक्रमmation from a provided block of
 *	    data so the transक्रमmation can जारी from this poपूर्णांक onward. No
 *	    data processing happens at this poपूर्णांक. Driver must not use
 *	    req->result.
 * @init_tfm: Initialize the cryptographic transक्रमmation object.
 *	      This function is called only once at the instantiation
 *	      समय, right after the transक्रमmation context was
 *	      allocated. In हाल the cryptographic hardware has
 *	      some special requirements which need to be handled
 *	      by software, this function shall check क्रम the precise
 *	      requirement of the transक्रमmation and put any software
 *	      fallbacks in place.
 * @निकास_tfm: Deinitialize the cryptographic transक्रमmation object.
 *	      This is a counterpart to @init_tfm, used to हटाओ
 *	      various changes set in @init_tfm.
 * @halg: see काष्ठा hash_alg_common
 */
काष्ठा ahash_alg अणु
	पूर्णांक (*init)(काष्ठा ahash_request *req);
	पूर्णांक (*update)(काष्ठा ahash_request *req);
	पूर्णांक (*final)(काष्ठा ahash_request *req);
	पूर्णांक (*finup)(काष्ठा ahash_request *req);
	पूर्णांक (*digest)(काष्ठा ahash_request *req);
	पूर्णांक (*export)(काष्ठा ahash_request *req, व्योम *out);
	पूर्णांक (*import)(काष्ठा ahash_request *req, स्थिर व्योम *in);
	पूर्णांक (*setkey)(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen);
	पूर्णांक (*init_tfm)(काष्ठा crypto_ahash *tfm);
	व्योम (*निकास_tfm)(काष्ठा crypto_ahash *tfm);

	काष्ठा hash_alg_common halg;
पूर्ण;

काष्ठा shash_desc अणु
	काष्ठा crypto_shash *tfm;
	व्योम *__ctx[] __aligned(ARCH_SLAB_MINALIGN);
पूर्ण;

#घोषणा HASH_MAX_DIGESTSIZE	 64

/*
 * Worst हाल is hmac(sha3-224-generic).  Its context is a nested 'shash_desc'
 * containing a 'struct sha3_state'.
 */
#घोषणा HASH_MAX_DESCSIZE	(माप(काष्ठा shash_desc) + 360)

#घोषणा HASH_MAX_STATESIZE	512

#घोषणा SHASH_DESC_ON_STACK(shash, ctx)					     \
	अक्षर __##shash##_desc[माप(काष्ठा shash_desc) + HASH_MAX_DESCSIZE] \
		__aligned(__alignof__(काष्ठा shash_desc));		     \
	काष्ठा shash_desc *shash = (काष्ठा shash_desc *)__##shash##_desc

/**
 * काष्ठा shash_alg - synchronous message digest definition
 * @init: see काष्ठा ahash_alg
 * @update: see काष्ठा ahash_alg
 * @final: see काष्ठा ahash_alg
 * @finup: see काष्ठा ahash_alg
 * @digest: see काष्ठा ahash_alg
 * @export: see काष्ठा ahash_alg
 * @import: see काष्ठा ahash_alg
 * @setkey: see काष्ठा ahash_alg
 * @init_tfm: Initialize the cryptographic transक्रमmation object.
 *	      This function is called only once at the instantiation
 *	      समय, right after the transक्रमmation context was
 *	      allocated. In हाल the cryptographic hardware has
 *	      some special requirements which need to be handled
 *	      by software, this function shall check क्रम the precise
 *	      requirement of the transक्रमmation and put any software
 *	      fallbacks in place.
 * @निकास_tfm: Deinitialize the cryptographic transक्रमmation object.
 *	      This is a counterpart to @init_tfm, used to हटाओ
 *	      various changes set in @init_tfm.
 * @digestsize: see काष्ठा ahash_alg
 * @statesize: see काष्ठा ahash_alg
 * @descsize: Size of the operational state क्रम the message digest. This state
 * 	      size is the memory size that needs to be allocated क्रम
 *	      shash_desc.__ctx
 * @base: पूर्णांकernally used
 */
काष्ठा shash_alg अणु
	पूर्णांक (*init)(काष्ठा shash_desc *desc);
	पूर्णांक (*update)(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len);
	पूर्णांक (*final)(काष्ठा shash_desc *desc, u8 *out);
	पूर्णांक (*finup)(काष्ठा shash_desc *desc, स्थिर u8 *data,
		     अचिन्हित पूर्णांक len, u8 *out);
	पूर्णांक (*digest)(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len, u8 *out);
	पूर्णांक (*export)(काष्ठा shash_desc *desc, व्योम *out);
	पूर्णांक (*import)(काष्ठा shash_desc *desc, स्थिर व्योम *in);
	पूर्णांक (*setkey)(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen);
	पूर्णांक (*init_tfm)(काष्ठा crypto_shash *tfm);
	व्योम (*निकास_tfm)(काष्ठा crypto_shash *tfm);

	अचिन्हित पूर्णांक descsize;

	/* These fields must match hash_alg_common. */
	अचिन्हित पूर्णांक digestsize
		__attribute__ ((aligned(__alignof__(काष्ठा hash_alg_common))));
	अचिन्हित पूर्णांक statesize;

	काष्ठा crypto_alg base;
पूर्ण;

काष्ठा crypto_ahash अणु
	पूर्णांक (*init)(काष्ठा ahash_request *req);
	पूर्णांक (*update)(काष्ठा ahash_request *req);
	पूर्णांक (*final)(काष्ठा ahash_request *req);
	पूर्णांक (*finup)(काष्ठा ahash_request *req);
	पूर्णांक (*digest)(काष्ठा ahash_request *req);
	पूर्णांक (*export)(काष्ठा ahash_request *req, व्योम *out);
	पूर्णांक (*import)(काष्ठा ahash_request *req, स्थिर व्योम *in);
	पूर्णांक (*setkey)(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen);

	अचिन्हित पूर्णांक reqsize;
	काष्ठा crypto_tfm base;
पूर्ण;

काष्ठा crypto_shash अणु
	अचिन्हित पूर्णांक descsize;
	काष्ठा crypto_tfm base;
पूर्ण;

/**
 * DOC: Asynchronous Message Digest API
 *
 * The asynchronous message digest API is used with the ciphers of type
 * CRYPTO_ALG_TYPE_AHASH (listed as type "ahash" in /proc/crypto)
 *
 * The asynchronous cipher operation discussion provided क्रम the
 * CRYPTO_ALG_TYPE_SKCIPHER API applies here as well.
 */

अटल अंतरभूत काष्ठा crypto_ahash *__crypto_ahash_cast(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_ahash, base);
पूर्ण

/**
 * crypto_alloc_ahash() - allocate ahash cipher handle
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      ahash cipher
 * @type: specअगरies the type of the cipher
 * @mask: specअगरies the mask क्रम the cipher
 *
 * Allocate a cipher handle क्रम an ahash. The वापसed काष्ठा
 * crypto_ahash is the cipher handle that is required क्रम any subsequent
 * API invocation क्रम that ahash.
 *
 * Return: allocated cipher handle in हाल of success; IS_ERR() is true in हाल
 *	   of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_ahash *crypto_alloc_ahash(स्थिर अक्षर *alg_name, u32 type,
					u32 mask);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_ahash_tfm(काष्ठा crypto_ahash *tfm)
अणु
	वापस &tfm->base;
पूर्ण

/**
 * crypto_मुक्त_ahash() - zeroize and मुक्त the ahash handle
 * @tfm: cipher handle to be मुक्तd
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_ahash(काष्ठा crypto_ahash *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_ahash_tfm(tfm));
पूर्ण

/**
 * crypto_has_ahash() - Search क्रम the availability of an ahash.
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      ahash
 * @type: specअगरies the type of the ahash
 * @mask: specअगरies the mask क्रम the ahash
 *
 * Return: true when the ahash is known to the kernel crypto API; false
 *	   otherwise
 */
पूर्णांक crypto_has_ahash(स्थिर अक्षर *alg_name, u32 type, u32 mask);

अटल अंतरभूत स्थिर अक्षर *crypto_ahash_alg_name(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_alg_name(crypto_ahash_tfm(tfm));
पूर्ण

अटल अंतरभूत स्थिर अक्षर *crypto_ahash_driver_name(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_alg_driver_name(crypto_ahash_tfm(tfm));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_ahash_alignmask(
	काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_alg_alignmask(crypto_ahash_tfm(tfm));
पूर्ण

/**
 * crypto_ahash_blocksize() - obtain block size क्रम cipher
 * @tfm: cipher handle
 *
 * The block size क्रम the message digest cipher referenced with the cipher
 * handle is वापसed.
 *
 * Return: block size of cipher
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_ahash_blocksize(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
पूर्ण

अटल अंतरभूत काष्ठा hash_alg_common *__crypto_hash_alg_common(
	काष्ठा crypto_alg *alg)
अणु
	वापस container_of(alg, काष्ठा hash_alg_common, base);
पूर्ण

अटल अंतरभूत काष्ठा hash_alg_common *crypto_hash_alg_common(
	काष्ठा crypto_ahash *tfm)
अणु
	वापस __crypto_hash_alg_common(crypto_ahash_tfm(tfm)->__crt_alg);
पूर्ण

/**
 * crypto_ahash_digestsize() - obtain message digest size
 * @tfm: cipher handle
 *
 * The size क्रम the message digest created by the message digest cipher
 * referenced with the cipher handle is वापसed.
 *
 *
 * Return: message digest size of cipher
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_ahash_digestsize(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_hash_alg_common(tfm)->digestsize;
पूर्ण

/**
 * crypto_ahash_statesize() - obtain size of the ahash state
 * @tfm: cipher handle
 *
 * Return the size of the ahash state. With the crypto_ahash_export()
 * function, the caller can export the state पूर्णांकo a buffer whose size is
 * defined with this function.
 *
 * Return: size of the ahash state
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_ahash_statesize(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_hash_alg_common(tfm)->statesize;
पूर्ण

अटल अंतरभूत u32 crypto_ahash_get_flags(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_get_flags(crypto_ahash_tfm(tfm));
पूर्ण

अटल अंतरभूत व्योम crypto_ahash_set_flags(काष्ठा crypto_ahash *tfm, u32 flags)
अणु
	crypto_tfm_set_flags(crypto_ahash_tfm(tfm), flags);
पूर्ण

अटल अंतरभूत व्योम crypto_ahash_clear_flags(काष्ठा crypto_ahash *tfm, u32 flags)
अणु
	crypto_tfm_clear_flags(crypto_ahash_tfm(tfm), flags);
पूर्ण

/**
 * crypto_ahash_reqtfm() - obtain cipher handle from request
 * @req: asynchronous request handle that contains the reference to the ahash
 *	 cipher handle
 *
 * Return the ahash cipher handle that is रेजिस्टरed with the asynchronous
 * request handle ahash_request.
 *
 * Return: ahash cipher handle
 */
अटल अंतरभूत काष्ठा crypto_ahash *crypto_ahash_reqtfm(
	काष्ठा ahash_request *req)
अणु
	वापस __crypto_ahash_cast(req->base.tfm);
पूर्ण

/**
 * crypto_ahash_reqsize() - obtain size of the request data काष्ठाure
 * @tfm: cipher handle
 *
 * Return: size of the request data
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_ahash_reqsize(काष्ठा crypto_ahash *tfm)
अणु
	वापस tfm->reqsize;
पूर्ण

अटल अंतरभूत व्योम *ahash_request_ctx(काष्ठा ahash_request *req)
अणु
	वापस req->__ctx;
पूर्ण

/**
 * crypto_ahash_setkey - set key क्रम cipher handle
 * @tfm: cipher handle
 * @key: buffer holding the key
 * @keylen: length of the key in bytes
 *
 * The caller provided key is set क्रम the ahash cipher. The cipher
 * handle must poपूर्णांक to a keyed hash in order क्रम this function to succeed.
 *
 * Return: 0 अगर the setting of the key was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_ahash_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);

/**
 * crypto_ahash_finup() - update and finalize message digest
 * @req: reference to the ahash_request handle that holds all inक्रमmation
 *	 needed to perक्रमm the cipher operation
 *
 * This function is a "short-hand" क्रम the function calls of
 * crypto_ahash_update and crypto_ahash_final. The parameters have the same
 * meaning as discussed क्रम those separate functions.
 *
 * Return: see crypto_ahash_final()
 */
पूर्णांक crypto_ahash_finup(काष्ठा ahash_request *req);

/**
 * crypto_ahash_final() - calculate message digest
 * @req: reference to the ahash_request handle that holds all inक्रमmation
 *	 needed to perक्रमm the cipher operation
 *
 * Finalize the message digest operation and create the message digest
 * based on all data added to the cipher handle. The message digest is placed
 * पूर्णांकo the output buffer रेजिस्टरed with the ahash_request handle.
 *
 * Return:
 * 0		अगर the message digest was successfully calculated;
 * -EINPROGRESS	अगर data is feeded पूर्णांकo hardware (DMA) or queued क्रम later;
 * -EBUSY	अगर queue is full and request should be resubmitted later;
 * other < 0	अगर an error occurred
 */
पूर्णांक crypto_ahash_final(काष्ठा ahash_request *req);

/**
 * crypto_ahash_digest() - calculate message digest क्रम a buffer
 * @req: reference to the ahash_request handle that holds all inक्रमmation
 *	 needed to perक्रमm the cipher operation
 *
 * This function is a "short-hand" क्रम the function calls of crypto_ahash_init,
 * crypto_ahash_update and crypto_ahash_final. The parameters have the same
 * meaning as discussed क्रम those separate three functions.
 *
 * Return: see crypto_ahash_final()
 */
पूर्णांक crypto_ahash_digest(काष्ठा ahash_request *req);

/**
 * crypto_ahash_export() - extract current message digest state
 * @req: reference to the ahash_request handle whose state is exported
 * @out: output buffer of sufficient size that can hold the hash state
 *
 * This function exports the hash state of the ahash_request handle पूर्णांकo the
 * caller-allocated output buffer out which must have sufficient size (e.g. by
 * calling crypto_ahash_statesize()).
 *
 * Return: 0 अगर the export was successful; < 0 अगर an error occurred
 */
अटल अंतरभूत पूर्णांक crypto_ahash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	वापस crypto_ahash_reqtfm(req)->export(req, out);
पूर्ण

/**
 * crypto_ahash_import() - import message digest state
 * @req: reference to ahash_request handle the state is imported पूर्णांकo
 * @in: buffer holding the state
 *
 * This function imports the hash state पूर्णांकo the ahash_request handle from the
 * input buffer. That buffer should have been generated with the
 * crypto_ahash_export function.
 *
 * Return: 0 अगर the import was successful; < 0 अगर an error occurred
 */
अटल अंतरभूत पूर्णांक crypto_ahash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);

	अगर (crypto_ahash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस tfm->import(req, in);
पूर्ण

/**
 * crypto_ahash_init() - (re)initialize message digest handle
 * @req: ahash_request handle that alपढ़ोy is initialized with all necessary
 *	 data using the ahash_request_* API functions
 *
 * The call (re-)initializes the message digest referenced by the ahash_request
 * handle. Any potentially existing state created by previous operations is
 * discarded.
 *
 * Return: see crypto_ahash_final()
 */
अटल अंतरभूत पूर्णांक crypto_ahash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);

	अगर (crypto_ahash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस tfm->init(req);
पूर्ण

/**
 * crypto_ahash_update() - add data to message digest क्रम processing
 * @req: ahash_request handle that was previously initialized with the
 *	 crypto_ahash_init call.
 *
 * Updates the message digest state of the &ahash_request handle. The input data
 * is poपूर्णांकed to by the scatter/gather list रेजिस्टरed in the &ahash_request
 * handle
 *
 * Return: see crypto_ahash_final()
 */
अटल अंतरभूत पूर्णांक crypto_ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	पूर्णांक ret;

	crypto_stats_get(alg);
	ret = crypto_ahash_reqtfm(req)->update(req);
	crypto_stats_ahash_update(nbytes, ret, alg);
	वापस ret;
पूर्ण

/**
 * DOC: Asynchronous Hash Request Handle
 *
 * The &ahash_request data काष्ठाure contains all poपूर्णांकers to data
 * required क्रम the asynchronous cipher operation. This includes the cipher
 * handle (which can be used by multiple &ahash_request instances), poपूर्णांकer
 * to plaपूर्णांकext and the message digest output buffer, asynchronous callback
 * function, etc. It acts as a handle to the ahash_request_* API calls in a
 * similar way as ahash handle to the crypto_ahash_* API calls.
 */

/**
 * ahash_request_set_tfm() - update cipher handle reference in request
 * @req: request handle to be modअगरied
 * @tfm: cipher handle that shall be added to the request handle
 *
 * Allow the caller to replace the existing ahash handle in the request
 * data काष्ठाure with a dअगरferent one.
 */
अटल अंतरभूत व्योम ahash_request_set_tfm(काष्ठा ahash_request *req,
					 काष्ठा crypto_ahash *tfm)
अणु
	req->base.tfm = crypto_ahash_tfm(tfm);
पूर्ण

/**
 * ahash_request_alloc() - allocate request data काष्ठाure
 * @tfm: cipher handle to be रेजिस्टरed with the request
 * @gfp: memory allocation flag that is handed to kदो_स्मृति by the API call.
 *
 * Allocate the request data काष्ठाure that must be used with the ahash
 * message digest API calls. During
 * the allocation, the provided ahash handle
 * is रेजिस्टरed in the request data काष्ठाure.
 *
 * Return: allocated request handle in हाल of success, or शून्य अगर out of memory
 */
अटल अंतरभूत काष्ठा ahash_request *ahash_request_alloc(
	काष्ठा crypto_ahash *tfm, gfp_t gfp)
अणु
	काष्ठा ahash_request *req;

	req = kदो_स्मृति(माप(काष्ठा ahash_request) +
		      crypto_ahash_reqsize(tfm), gfp);

	अगर (likely(req))
		ahash_request_set_tfm(req, tfm);

	वापस req;
पूर्ण

/**
 * ahash_request_मुक्त() - zeroize and मुक्त the request data काष्ठाure
 * @req: request data काष्ठाure cipher handle to be मुक्तd
 */
अटल अंतरभूत व्योम ahash_request_मुक्त(काष्ठा ahash_request *req)
अणु
	kमुक्त_sensitive(req);
पूर्ण

अटल अंतरभूत व्योम ahash_request_zero(काष्ठा ahash_request *req)
अणु
	memzero_explicit(req, माप(*req) +
			      crypto_ahash_reqsize(crypto_ahash_reqtfm(req)));
पूर्ण

अटल अंतरभूत काष्ठा ahash_request *ahash_request_cast(
	काष्ठा crypto_async_request *req)
अणु
	वापस container_of(req, काष्ठा ahash_request, base);
पूर्ण

/**
 * ahash_request_set_callback() - set asynchronous callback function
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
 *	  &crypto_async_request data काष्ठाure provided to the callback function.
 *
 * This function allows setting the callback function that is triggered once
 * the cipher operation completes.
 *
 * The callback function is रेजिस्टरed with the &ahash_request handle and
 * must comply with the following ढाँचा::
 *
 *	व्योम callback_function(काष्ठा crypto_async_request *req, पूर्णांक error)
 */
अटल अंतरभूत व्योम ahash_request_set_callback(काष्ठा ahash_request *req,
					      u32 flags,
					      crypto_completion_t compl,
					      व्योम *data)
अणु
	req->base.complete = compl;
	req->base.data = data;
	req->base.flags = flags;
पूर्ण

/**
 * ahash_request_set_crypt() - set data buffers
 * @req: ahash_request handle to be updated
 * @src: source scatter/gather list
 * @result: buffer that is filled with the message digest -- the caller must
 *	    ensure that the buffer has sufficient space by, क्रम example, calling
 *	    crypto_ahash_digestsize()
 * @nbytes: number of bytes to process from the source scatter/gather list
 *
 * By using this call, the caller references the source scatter/gather list.
 * The source scatter/gather list poपूर्णांकs to the data the message digest is to
 * be calculated क्रम.
 */
अटल अंतरभूत व्योम ahash_request_set_crypt(काष्ठा ahash_request *req,
					   काष्ठा scatterlist *src, u8 *result,
					   अचिन्हित पूर्णांक nbytes)
अणु
	req->src = src;
	req->nbytes = nbytes;
	req->result = result;
पूर्ण

/**
 * DOC: Synchronous Message Digest API
 *
 * The synchronous message digest API is used with the ciphers of type
 * CRYPTO_ALG_TYPE_SHASH (listed as type "shash" in /proc/crypto)
 *
 * The message digest API is able to मुख्यtain state inक्रमmation क्रम the
 * caller.
 *
 * The synchronous message digest API can store user-related context in its
 * shash_desc request data काष्ठाure.
 */

/**
 * crypto_alloc_shash() - allocate message digest handle
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      message digest cipher
 * @type: specअगरies the type of the cipher
 * @mask: specअगरies the mask क्रम the cipher
 *
 * Allocate a cipher handle क्रम a message digest. The वापसed &काष्ठा
 * crypto_shash is the cipher handle that is required क्रम any subsequent
 * API invocation क्रम that message digest.
 *
 * Return: allocated cipher handle in हाल of success; IS_ERR() is true in हाल
 *	   of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_shash *crypto_alloc_shash(स्थिर अक्षर *alg_name, u32 type,
					u32 mask);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_shash_tfm(काष्ठा crypto_shash *tfm)
अणु
	वापस &tfm->base;
पूर्ण

/**
 * crypto_मुक्त_shash() - zeroize and मुक्त the message digest handle
 * @tfm: cipher handle to be मुक्तd
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_shash(काष्ठा crypto_shash *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_shash_tfm(tfm));
पूर्ण

अटल अंतरभूत स्थिर अक्षर *crypto_shash_alg_name(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_alg_name(crypto_shash_tfm(tfm));
पूर्ण

अटल अंतरभूत स्थिर अक्षर *crypto_shash_driver_name(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_alg_driver_name(crypto_shash_tfm(tfm));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_shash_alignmask(
	काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_alg_alignmask(crypto_shash_tfm(tfm));
पूर्ण

/**
 * crypto_shash_blocksize() - obtain block size क्रम cipher
 * @tfm: cipher handle
 *
 * The block size क्रम the message digest cipher referenced with the cipher
 * handle is वापसed.
 *
 * Return: block size of cipher
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_shash_blocksize(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_alg_blocksize(crypto_shash_tfm(tfm));
पूर्ण

अटल अंतरभूत काष्ठा shash_alg *__crypto_shash_alg(काष्ठा crypto_alg *alg)
अणु
	वापस container_of(alg, काष्ठा shash_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा shash_alg *crypto_shash_alg(काष्ठा crypto_shash *tfm)
अणु
	वापस __crypto_shash_alg(crypto_shash_tfm(tfm)->__crt_alg);
पूर्ण

/**
 * crypto_shash_digestsize() - obtain message digest size
 * @tfm: cipher handle
 *
 * The size क्रम the message digest created by the message digest cipher
 * referenced with the cipher handle is वापसed.
 *
 * Return: digest size of cipher
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_shash_digestsize(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_shash_alg(tfm)->digestsize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_shash_statesize(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_shash_alg(tfm)->statesize;
पूर्ण

अटल अंतरभूत u32 crypto_shash_get_flags(काष्ठा crypto_shash *tfm)
अणु
	वापस crypto_tfm_get_flags(crypto_shash_tfm(tfm));
पूर्ण

अटल अंतरभूत व्योम crypto_shash_set_flags(काष्ठा crypto_shash *tfm, u32 flags)
अणु
	crypto_tfm_set_flags(crypto_shash_tfm(tfm), flags);
पूर्ण

अटल अंतरभूत व्योम crypto_shash_clear_flags(काष्ठा crypto_shash *tfm, u32 flags)
अणु
	crypto_tfm_clear_flags(crypto_shash_tfm(tfm), flags);
पूर्ण

/**
 * crypto_shash_descsize() - obtain the operational state size
 * @tfm: cipher handle
 *
 * The size of the operational state the cipher needs during operation is
 * वापसed क्रम the hash referenced with the cipher handle. This size is
 * required to calculate the memory requirements to allow the caller allocating
 * sufficient memory क्रम operational state.
 *
 * The operational state is defined with काष्ठा shash_desc where the size of
 * that data काष्ठाure is to be calculated as
 * माप(काष्ठा shash_desc) + crypto_shash_descsize(alg)
 *
 * Return: size of the operational state
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_shash_descsize(काष्ठा crypto_shash *tfm)
अणु
	वापस tfm->descsize;
पूर्ण

अटल अंतरभूत व्योम *shash_desc_ctx(काष्ठा shash_desc *desc)
अणु
	वापस desc->__ctx;
पूर्ण

/**
 * crypto_shash_setkey() - set key क्रम message digest
 * @tfm: cipher handle
 * @key: buffer holding the key
 * @keylen: length of the key in bytes
 *
 * The caller provided key is set क्रम the keyed message digest cipher. The
 * cipher handle must poपूर्णांक to a keyed message digest cipher in order क्रम this
 * function to succeed.
 *
 * Context: Any context.
 * Return: 0 अगर the setting of the key was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_shash_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);

/**
 * crypto_shash_digest() - calculate message digest क्रम buffer
 * @desc: see crypto_shash_final()
 * @data: see crypto_shash_update()
 * @len: see crypto_shash_update()
 * @out: see crypto_shash_final()
 *
 * This function is a "short-hand" क्रम the function calls of crypto_shash_init,
 * crypto_shash_update and crypto_shash_final. The parameters have the same
 * meaning as discussed क्रम those separate three functions.
 *
 * Context: Any context.
 * Return: 0 अगर the message digest creation was successful; < 0 अगर an error
 *	   occurred
 */
पूर्णांक crypto_shash_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out);

/**
 * crypto_shash_tfm_digest() - calculate message digest क्रम buffer
 * @tfm: hash transक्रमmation object
 * @data: see crypto_shash_update()
 * @len: see crypto_shash_update()
 * @out: see crypto_shash_final()
 *
 * This is a simplअगरied version of crypto_shash_digest() क्रम users who करोn't
 * want to allocate their own hash descriptor (shash_desc).  Instead,
 * crypto_shash_tfm_digest() takes a hash transक्रमmation object (crypto_shash)
 * directly, and it allocates a hash descriptor on the stack पूर्णांकernally.
 * Note that this stack allocation may be fairly large.
 *
 * Context: Any context.
 * Return: 0 on success; < 0 अगर an error occurred.
 */
पूर्णांक crypto_shash_tfm_digest(काष्ठा crypto_shash *tfm, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len, u8 *out);

/**
 * crypto_shash_export() - extract operational state क्रम message digest
 * @desc: reference to the operational state handle whose state is exported
 * @out: output buffer of sufficient size that can hold the hash state
 *
 * This function exports the hash state of the operational state handle पूर्णांकo the
 * caller-allocated output buffer out which must have sufficient size (e.g. by
 * calling crypto_shash_descsize).
 *
 * Context: Any context.
 * Return: 0 अगर the export creation was successful; < 0 अगर an error occurred
 */
अटल अंतरभूत पूर्णांक crypto_shash_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	वापस crypto_shash_alg(desc->tfm)->export(desc, out);
पूर्ण

/**
 * crypto_shash_import() - import operational state
 * @desc: reference to the operational state handle the state imported पूर्णांकo
 * @in: buffer holding the state
 *
 * This function imports the hash state पूर्णांकo the operational state handle from
 * the input buffer. That buffer should have been generated with the
 * crypto_ahash_export function.
 *
 * Context: Any context.
 * Return: 0 अगर the import was successful; < 0 अगर an error occurred
 */
अटल अंतरभूत पूर्णांक crypto_shash_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;

	अगर (crypto_shash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस crypto_shash_alg(tfm)->import(desc, in);
पूर्ण

/**
 * crypto_shash_init() - (re)initialize message digest
 * @desc: operational state handle that is alपढ़ोy filled
 *
 * The call (re-)initializes the message digest referenced by the
 * operational state handle. Any potentially existing state created by
 * previous operations is discarded.
 *
 * Context: Any context.
 * Return: 0 अगर the message digest initialization was successful; < 0 अगर an
 *	   error occurred
 */
अटल अंतरभूत पूर्णांक crypto_shash_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;

	अगर (crypto_shash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस crypto_shash_alg(tfm)->init(desc);
पूर्ण

/**
 * crypto_shash_update() - add data to message digest क्रम processing
 * @desc: operational state handle that is alपढ़ोy initialized
 * @data: input data to be added to the message digest
 * @len: length of the input data
 *
 * Updates the message digest state of the operational state handle.
 *
 * Context: Any context.
 * Return: 0 अगर the message digest update was successful; < 0 अगर an error
 *	   occurred
 */
पूर्णांक crypto_shash_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len);

/**
 * crypto_shash_final() - calculate message digest
 * @desc: operational state handle that is alपढ़ोy filled with data
 * @out: output buffer filled with the message digest
 *
 * Finalize the message digest operation and create the message digest
 * based on all data added to the cipher handle. The message digest is placed
 * पूर्णांकo the output buffer. The caller must ensure that the output buffer is
 * large enough by using crypto_shash_digestsize.
 *
 * Context: Any context.
 * Return: 0 अगर the message digest creation was successful; < 0 अगर an error
 *	   occurred
 */
पूर्णांक crypto_shash_final(काष्ठा shash_desc *desc, u8 *out);

/**
 * crypto_shash_finup() - calculate message digest of buffer
 * @desc: see crypto_shash_final()
 * @data: see crypto_shash_update()
 * @len: see crypto_shash_update()
 * @out: see crypto_shash_final()
 *
 * This function is a "short-hand" क्रम the function calls of
 * crypto_shash_update and crypto_shash_final. The parameters have the same
 * meaning as discussed क्रम those separate functions.
 *
 * Context: Any context.
 * Return: 0 अगर the message digest creation was successful; < 0 अगर an error
 *	   occurred
 */
पूर्णांक crypto_shash_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len, u8 *out);

अटल अंतरभूत व्योम shash_desc_zero(काष्ठा shash_desc *desc)
अणु
	memzero_explicit(desc,
			 माप(*desc) + crypto_shash_descsize(desc->tfm));
पूर्ण

#पूर्ण_अगर	/* _CRYPTO_HASH_H */
