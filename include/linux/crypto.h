<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Scatterlist Cryptographic API.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 David S. Miller (davem@redhat.com)
 * Copyright (c) 2005 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * Portions derived from Cryptoapi, by Alexander Kjeldaas <astor@fast.no>
 * and Nettle, by Niels Mथघller.
 */
#अगर_अघोषित _LINUX_CRYPTO_H
#घोषणा _LINUX_CRYPTO_H

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>

/*
 * Autoloaded crypto modules should only use a prefixed name to aव्योम allowing
 * arbitrary modules to be loaded. Loading from userspace may still need the
 * unprefixed names, so retains those aliases as well.
 * This uses __MODULE_INFO directly instead of MODULE_ALIAS because pre-4.3
 * gcc (e.g. avr32 toolchain) uses __LINE__ क्रम uniqueness, and this macro
 * expands twice on the same line. Instead, use a separate base name क्रम the
 * alias.
 */
#घोषणा MODULE_ALIAS_CRYPTO(name)	\
		__MODULE_INFO(alias, alias_userspace, name);	\
		__MODULE_INFO(alias, alias_crypto, "crypto-" name)

/*
 * Algorithm masks and types.
 */
#घोषणा CRYPTO_ALG_TYPE_MASK		0x0000000f
#घोषणा CRYPTO_ALG_TYPE_CIPHER		0x00000001
#घोषणा CRYPTO_ALG_TYPE_COMPRESS	0x00000002
#घोषणा CRYPTO_ALG_TYPE_AEAD		0x00000003
#घोषणा CRYPTO_ALG_TYPE_SKCIPHER	0x00000005
#घोषणा CRYPTO_ALG_TYPE_KPP		0x00000008
#घोषणा CRYPTO_ALG_TYPE_ACOMPRESS	0x0000000a
#घोषणा CRYPTO_ALG_TYPE_SCOMPRESS	0x0000000b
#घोषणा CRYPTO_ALG_TYPE_RNG		0x0000000c
#घोषणा CRYPTO_ALG_TYPE_AKCIPHER	0x0000000d
#घोषणा CRYPTO_ALG_TYPE_HASH		0x0000000e
#घोषणा CRYPTO_ALG_TYPE_SHASH		0x0000000e
#घोषणा CRYPTO_ALG_TYPE_AHASH		0x0000000f

#घोषणा CRYPTO_ALG_TYPE_HASH_MASK	0x0000000e
#घोषणा CRYPTO_ALG_TYPE_AHASH_MASK	0x0000000e
#घोषणा CRYPTO_ALG_TYPE_ACOMPRESS_MASK	0x0000000e

#घोषणा CRYPTO_ALG_LARVAL		0x00000010
#घोषणा CRYPTO_ALG_DEAD			0x00000020
#घोषणा CRYPTO_ALG_DYING		0x00000040
#घोषणा CRYPTO_ALG_ASYNC		0x00000080

/*
 * Set अगर the algorithm (or an algorithm which it uses) requires another
 * algorithm of the same type to handle corner हालs.
 */
#घोषणा CRYPTO_ALG_NEED_FALLBACK	0x00000100

/*
 * Set अगर the algorithm has passed स्वतःmated run-समय testing.  Note that
 * अगर there is no run-समय testing क्रम a given algorithm it is considered
 * to have passed.
 */

#घोषणा CRYPTO_ALG_TESTED		0x00000400

/*
 * Set अगर the algorithm is an instance that is built from ढाँचाs.
 */
#घोषणा CRYPTO_ALG_INSTANCE		0x00000800

/* Set this bit अगर the algorithm provided is hardware accelerated but
 * not available to userspace via inकाष्ठाion set or so.
 */
#घोषणा CRYPTO_ALG_KERN_DRIVER_ONLY	0x00001000

/*
 * Mark a cipher as a service implementation only usable by another
 * cipher and never by a normal user of the kernel crypto API
 */
#घोषणा CRYPTO_ALG_INTERNAL		0x00002000

/*
 * Set अगर the algorithm has a ->setkey() method but can be used without
 * calling it first, i.e. there is a शेष key.
 */
#घोषणा CRYPTO_ALG_OPTIONAL_KEY		0x00004000

/*
 * Don't trigger module loading
 */
#घोषणा CRYPTO_NOLOAD			0x00008000

/*
 * The algorithm may allocate memory during request processing, i.e. during
 * encryption, decryption, or hashing.  Users can request an algorithm with this
 * flag unset अगर they can't handle memory allocation failures.
 *
 * This flag is currently only implemented क्रम algorithms of type "skcipher",
 * "aead", "ahash", "shash", and "cipher".  Algorithms of other types might not
 * have this flag set even अगर they allocate memory.
 *
 * In some edge हालs, algorithms can allocate memory regardless of this flag.
 * To aव्योम these हालs, users must obey the following usage स्थिरraपूर्णांकs:
 *    skcipher:
 *	- The IV buffer and all scatterlist elements must be aligned to the
 *	  algorithm's alignmask.
 *	- If the data were to be भागided पूर्णांकo chunks of size
 *	  crypto_skcipher_walksize() (with any reमुख्यder going at the end), no
 *	  chunk can cross a page boundary or a scatterlist element boundary.
 *    aead:
 *	- The IV buffer and all scatterlist elements must be aligned to the
 *	  algorithm's alignmask.
 *	- The first scatterlist element must contain all the associated data,
 *	  and its pages must be !PageHighMem.
 *	- If the plaपूर्णांकext/ciphertext were to be भागided पूर्णांकo chunks of size
 *	  crypto_aead_walksize() (with the reमुख्यder going at the end), no chunk
 *	  can cross a page boundary or a scatterlist element boundary.
 *    ahash:
 *	- The result buffer must be aligned to the algorithm's alignmask.
 *	- crypto_ahash_finup() must not be used unless the algorithm implements
 *	  ->finup() natively.
 */
#घोषणा CRYPTO_ALG_ALLOCATES_MEMORY	0x00010000

/*
 * Transक्रमm masks and values (क्रम crt_flags).
 */
#घोषणा CRYPTO_TFM_NEED_KEY		0x00000001

#घोषणा CRYPTO_TFM_REQ_MASK		0x000fff00
#घोषणा CRYPTO_TFM_REQ_FORBID_WEAK_KEYS	0x00000100
#घोषणा CRYPTO_TFM_REQ_MAY_SLEEP	0x00000200
#घोषणा CRYPTO_TFM_REQ_MAY_BACKLOG	0x00000400

/*
 * Miscellaneous stuff.
 */
#घोषणा CRYPTO_MAX_ALG_NAME		128

/*
 * The macro CRYPTO_MINALIGN_ATTR (aदीर्घ with the व्योम * type in the actual
 * declaration) is used to ensure that the crypto_tfm context काष्ठाure is
 * aligned correctly क्रम the given architecture so that there are no alignment
 * faults क्रम C data types.  On architectures that support non-cache coherent
 * DMA, such as ARM or arm64, it also takes पूर्णांकo account the minimal alignment
 * that is required to ensure that the context काष्ठा member करोes not share any
 * cachelines with the rest of the काष्ठा. This is needed to ensure that cache
 * मुख्यtenance क्रम non-coherent DMA (cache invalidation in particular) करोes not
 * affect data that may be accessed by the CPU concurrently.
 */
#घोषणा CRYPTO_MINALIGN ARCH_KMALLOC_MINALIGN

#घोषणा CRYPTO_MINALIGN_ATTR __attribute__ ((__aligned__(CRYPTO_MINALIGN)))

काष्ठा scatterlist;
काष्ठा crypto_async_request;
काष्ठा crypto_tfm;
काष्ठा crypto_type;

प्रकार व्योम (*crypto_completion_t)(काष्ठा crypto_async_request *req, पूर्णांक err);

/**
 * DOC: Block Cipher Context Data Structures
 *
 * These data काष्ठाures define the operating context क्रम each block cipher
 * type.
 */

काष्ठा crypto_async_request अणु
	काष्ठा list_head list;
	crypto_completion_t complete;
	व्योम *data;
	काष्ठा crypto_tfm *tfm;

	u32 flags;
पूर्ण;

/**
 * DOC: Block Cipher Algorithm Definitions
 *
 * These data काष्ठाures define modular crypto algorithm implementations,
 * managed via crypto_रेजिस्टर_alg() and crypto_unरेजिस्टर_alg().
 */

/**
 * काष्ठा cipher_alg - single-block symmetric ciphers definition
 * @cia_min_keysize: Minimum key size supported by the transक्रमmation. This is
 *		     the smallest key length supported by this transक्रमmation
 *		     algorithm. This must be set to one of the pre-defined
 *		     values as this is not hardware specअगरic. Possible values
 *		     क्रम this field can be found via git grep "_MIN_KEY_SIZE"
 *		     include/crypto/
 * @cia_max_keysize: Maximum key size supported by the transक्रमmation. This is
 *		    the largest key length supported by this transक्रमmation
 *		    algorithm. This must be set to one of the pre-defined values
 *		    as this is not hardware specअगरic. Possible values क्रम this
 *		    field can be found via git grep "_MAX_KEY_SIZE"
 *		    include/crypto/
 * @cia_setkey: Set key क्रम the transक्रमmation. This function is used to either
 *	        program a supplied key पूर्णांकo the hardware or store the key in the
 *	        transक्रमmation context क्रम programming it later. Note that this
 *	        function करोes modअगरy the transक्रमmation context. This function
 *	        can be called multiple बार during the existence of the
 *	        transक्रमmation object, so one must make sure the key is properly
 *	        reprogrammed पूर्णांकo the hardware. This function is also
 *	        responsible क्रम checking the key length क्रम validity.
 * @cia_encrypt: Encrypt a single block. This function is used to encrypt a
 *		 single block of data, which must be @cra_blocksize big. This
 *		 always operates on a full @cra_blocksize and it is not possible
 *		 to encrypt a block of smaller size. The supplied buffers must
 *		 thereक्रमe also be at least of @cra_blocksize size. Both the
 *		 input and output buffers are always aligned to @cra_alignmask.
 *		 In हाल either of the input or output buffer supplied by user
 *		 of the crypto API is not aligned to @cra_alignmask, the crypto
 *		 API will re-align the buffers. The re-alignment means that a
 *		 new buffer will be allocated, the data will be copied पूर्णांकo the
 *		 new buffer, then the processing will happen on the new buffer,
 *		 then the data will be copied back पूर्णांकo the original buffer and
 *		 finally the new buffer will be मुक्तd. In हाल a software
 *		 fallback was put in place in the @cra_init call, this function
 *		 might need to use the fallback अगर the algorithm करोesn't support
 *		 all of the key sizes. In हाल the key was stored in
 *		 transक्रमmation context, the key might need to be re-programmed
 *		 पूर्णांकo the hardware in this function. This function shall not
 *		 modअगरy the transक्रमmation context, as this function may be
 *		 called in parallel with the same transक्रमmation object.
 * @cia_decrypt: Decrypt a single block. This is a reverse counterpart to
 *		 @cia_encrypt, and the conditions are exactly the same.
 *
 * All fields are mandatory and must be filled.
 */
काष्ठा cipher_alg अणु
	अचिन्हित पूर्णांक cia_min_keysize;
	अचिन्हित पूर्णांक cia_max_keysize;
	पूर्णांक (*cia_setkey)(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
	                  अचिन्हित पूर्णांक keylen);
	व्योम (*cia_encrypt)(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src);
	व्योम (*cia_decrypt)(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src);
पूर्ण;

/**
 * काष्ठा compress_alg - compression/decompression algorithm
 * @coa_compress: Compress a buffer of specअगरied length, storing the resulting
 *		  data in the specअगरied buffer. Return the length of the
 *		  compressed data in dlen.
 * @coa_decompress: Decompress the source buffer, storing the uncompressed
 *		    data in the specअगरied buffer. The length of the data is
 *		    वापसed in dlen.
 *
 * All fields are mandatory.
 */
काष्ठा compress_alg अणु
	पूर्णांक (*coa_compress)(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			    अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen);
	पूर्णांक (*coa_decompress)(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			      अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen);
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_STATS
/*
 * काष्ठा crypto_istat_aead - statistics क्रम AEAD algorithm
 * @encrypt_cnt:	number of encrypt requests
 * @encrypt_tlen:	total data size handled by encrypt requests
 * @decrypt_cnt:	number of decrypt requests
 * @decrypt_tlen:	total data size handled by decrypt requests
 * @err_cnt:		number of error क्रम AEAD requests
 */
काष्ठा crypto_istat_aead अणु
	atomic64_t encrypt_cnt;
	atomic64_t encrypt_tlen;
	atomic64_t decrypt_cnt;
	atomic64_t decrypt_tlen;
	atomic64_t err_cnt;
पूर्ण;

/*
 * काष्ठा crypto_istat_akcipher - statistics क्रम akcipher algorithm
 * @encrypt_cnt:	number of encrypt requests
 * @encrypt_tlen:	total data size handled by encrypt requests
 * @decrypt_cnt:	number of decrypt requests
 * @decrypt_tlen:	total data size handled by decrypt requests
 * @verअगरy_cnt:		number of verअगरy operation
 * @sign_cnt:		number of sign requests
 * @err_cnt:		number of error क्रम akcipher requests
 */
काष्ठा crypto_istat_akcipher अणु
	atomic64_t encrypt_cnt;
	atomic64_t encrypt_tlen;
	atomic64_t decrypt_cnt;
	atomic64_t decrypt_tlen;
	atomic64_t verअगरy_cnt;
	atomic64_t sign_cnt;
	atomic64_t err_cnt;
पूर्ण;

/*
 * काष्ठा crypto_istat_cipher - statistics क्रम cipher algorithm
 * @encrypt_cnt:	number of encrypt requests
 * @encrypt_tlen:	total data size handled by encrypt requests
 * @decrypt_cnt:	number of decrypt requests
 * @decrypt_tlen:	total data size handled by decrypt requests
 * @err_cnt:		number of error क्रम cipher requests
 */
काष्ठा crypto_istat_cipher अणु
	atomic64_t encrypt_cnt;
	atomic64_t encrypt_tlen;
	atomic64_t decrypt_cnt;
	atomic64_t decrypt_tlen;
	atomic64_t err_cnt;
पूर्ण;

/*
 * काष्ठा crypto_istat_compress - statistics क्रम compress algorithm
 * @compress_cnt:	number of compress requests
 * @compress_tlen:	total data size handled by compress requests
 * @decompress_cnt:	number of decompress requests
 * @decompress_tlen:	total data size handled by decompress requests
 * @err_cnt:		number of error क्रम compress requests
 */
काष्ठा crypto_istat_compress अणु
	atomic64_t compress_cnt;
	atomic64_t compress_tlen;
	atomic64_t decompress_cnt;
	atomic64_t decompress_tlen;
	atomic64_t err_cnt;
पूर्ण;

/*
 * काष्ठा crypto_istat_hash - statistics क्रम has algorithm
 * @hash_cnt:		number of hash requests
 * @hash_tlen:		total data size hashed
 * @err_cnt:		number of error क्रम hash requests
 */
काष्ठा crypto_istat_hash अणु
	atomic64_t hash_cnt;
	atomic64_t hash_tlen;
	atomic64_t err_cnt;
पूर्ण;

/*
 * काष्ठा crypto_istat_kpp - statistics क्रम KPP algorithm
 * @setsecret_cnt:		number of setsecrey operation
 * @generate_खुला_key_cnt:	number of generate_खुला_key operation
 * @compute_shared_secret_cnt:	number of compute_shared_secret operation
 * @err_cnt:			number of error क्रम KPP requests
 */
काष्ठा crypto_istat_kpp अणु
	atomic64_t setsecret_cnt;
	atomic64_t generate_खुला_key_cnt;
	atomic64_t compute_shared_secret_cnt;
	atomic64_t err_cnt;
पूर्ण;

/*
 * काष्ठा crypto_istat_rng: statistics क्रम RNG algorithm
 * @generate_cnt:	number of RNG generate requests
 * @generate_tlen:	total data size of generated data by the RNG
 * @seed_cnt:		number of बार the RNG was seeded
 * @err_cnt:		number of error क्रम RNG requests
 */
काष्ठा crypto_istat_rng अणु
	atomic64_t generate_cnt;
	atomic64_t generate_tlen;
	atomic64_t seed_cnt;
	atomic64_t err_cnt;
पूर्ण;
#पूर्ण_अगर /* CONFIG_CRYPTO_STATS */

#घोषणा cra_cipher	cra_u.cipher
#घोषणा cra_compress	cra_u.compress

/**
 * काष्ठा crypto_alg - definition of a cryptograpic cipher algorithm
 * @cra_flags: Flags describing this transक्रमmation. See include/linux/crypto.h
 *	       CRYPTO_ALG_* flags क्रम the flags which go in here. Those are
 *	       used क्रम fine-tuning the description of the transक्रमmation
 *	       algorithm.
 * @cra_blocksize: Minimum block size of this transक्रमmation. The size in bytes
 *		   of the smallest possible unit which can be transक्रमmed with
 *		   this algorithm. The users must respect this value.
 *		   In हाल of HASH transक्रमmation, it is possible क्रम a smaller
 *		   block than @cra_blocksize to be passed to the crypto API क्रम
 *		   transक्रमmation, in हाल of any other transक्रमmation type, an
 * 		   error will be वापसed upon any attempt to transक्रमm smaller
 *		   than @cra_blocksize chunks.
 * @cra_ctxsize: Size of the operational context of the transक्रमmation. This
 *		 value inक्रमms the kernel crypto API about the memory size
 *		 needed to be allocated क्रम the transक्रमmation context.
 * @cra_alignmask: Alignment mask क्रम the input and output data buffer. The data
 *		   buffer containing the input data क्रम the algorithm must be
 *		   aligned to this alignment mask. The data buffer क्रम the
 *		   output data must be aligned to this alignment mask. Note that
 *		   the Crypto API will करो the re-alignment in software, but
 *		   only under special conditions and there is a perक्रमmance hit.
 *		   The re-alignment happens at these occasions क्रम dअगरferent
 *		   @cra_u types: cipher -- For both input data and output data
 *		   buffer; ahash -- For output hash destination buf; shash --
 *		   For output hash destination buf.
 *		   This is needed on hardware which is flawed by design and
 *		   cannot pick data from arbitrary addresses.
 * @cra_priority: Priority of this transक्रमmation implementation. In हाल
 *		  multiple transक्रमmations with same @cra_name are available to
 *		  the Crypto API, the kernel will use the one with highest
 *		  @cra_priority.
 * @cra_name: Generic name (usable by multiple implementations) of the
 *	      transक्रमmation algorithm. This is the name of the transक्रमmation
 *	      itself. This field is used by the kernel when looking up the
 *	      providers of particular transक्रमmation.
 * @cra_driver_name: Unique name of the transक्रमmation provider. This is the
 *		     name of the provider of the transक्रमmation. This can be any
 *		     arbitrary value, but in the usual हाल, this contains the
 *		     name of the chip or provider and the name of the
 *		     transक्रमmation algorithm.
 * @cra_type: Type of the cryptographic transक्रमmation. This is a poपूर्णांकer to
 *	      काष्ठा crypto_type, which implements callbacks common क्रम all
 *	      transक्रमmation types. There are multiple options, such as
 *	      &crypto_skcipher_type, &crypto_ahash_type, &crypto_rng_type.
 *	      This field might be empty. In that हाल, there are no common
 *	      callbacks. This is the हाल क्रम: cipher, compress, shash.
 * @cra_u: Callbacks implementing the transक्रमmation. This is a जोड़ of
 *	   multiple काष्ठाures. Depending on the type of transक्रमmation selected
 *	   by @cra_type and @cra_flags above, the associated काष्ठाure must be
 *	   filled with callbacks. This field might be empty. This is the हाल
 *	   क्रम ahash, shash.
 * @cra_init: Initialize the cryptographic transक्रमmation object. This function
 *	      is used to initialize the cryptographic transक्रमmation object.
 *	      This function is called only once at the instantiation समय, right
 *	      after the transक्रमmation context was allocated. In हाल the
 *	      cryptographic hardware has some special requirements which need to
 *	      be handled by software, this function shall check क्रम the precise
 *	      requirement of the transक्रमmation and put any software fallbacks
 *	      in place.
 * @cra_निकास: Deinitialize the cryptographic transक्रमmation object. This is a
 *	      counterpart to @cra_init, used to हटाओ various changes set in
 *	      @cra_init.
 * @cra_u.cipher: Union member which contains a single-block symmetric cipher
 *		  definition. See @काष्ठा @cipher_alg.
 * @cra_u.compress: Union member which contains a (de)compression algorithm.
 *		    See @काष्ठा @compress_alg.
 * @cra_module: Owner of this transक्रमmation implementation. Set to THIS_MODULE
 * @cra_list: पूर्णांकernally used
 * @cra_users: पूर्णांकernally used
 * @cra_refcnt: पूर्णांकernally used
 * @cra_destroy: पूर्णांकernally used
 *
 * @stats: जोड़ of all possible crypto_istat_xxx काष्ठाures
 * @stats.aead:		statistics क्रम AEAD algorithm
 * @stats.akcipher:	statistics क्रम akcipher algorithm
 * @stats.cipher:	statistics क्रम cipher algorithm
 * @stats.compress:	statistics क्रम compress algorithm
 * @stats.hash:		statistics क्रम hash algorithm
 * @stats.rng:		statistics क्रम rng algorithm
 * @stats.kpp:		statistics क्रम KPP algorithm
 *
 * The काष्ठा crypto_alg describes a generic Crypto API algorithm and is common
 * क्रम all of the transक्रमmations. Any variable not करोcumented here shall not
 * be used by a cipher implementation as it is पूर्णांकernal to the Crypto API.
 */
काष्ठा crypto_alg अणु
	काष्ठा list_head cra_list;
	काष्ठा list_head cra_users;

	u32 cra_flags;
	अचिन्हित पूर्णांक cra_blocksize;
	अचिन्हित पूर्णांक cra_ctxsize;
	अचिन्हित पूर्णांक cra_alignmask;

	पूर्णांक cra_priority;
	refcount_t cra_refcnt;

	अक्षर cra_name[CRYPTO_MAX_ALG_NAME];
	अक्षर cra_driver_name[CRYPTO_MAX_ALG_NAME];

	स्थिर काष्ठा crypto_type *cra_type;

	जोड़ अणु
		काष्ठा cipher_alg cipher;
		काष्ठा compress_alg compress;
	पूर्ण cra_u;

	पूर्णांक (*cra_init)(काष्ठा crypto_tfm *tfm);
	व्योम (*cra_निकास)(काष्ठा crypto_tfm *tfm);
	व्योम (*cra_destroy)(काष्ठा crypto_alg *alg);
	
	काष्ठा module *cra_module;

#अगर_घोषित CONFIG_CRYPTO_STATS
	जोड़ अणु
		काष्ठा crypto_istat_aead aead;
		काष्ठा crypto_istat_akcipher akcipher;
		काष्ठा crypto_istat_cipher cipher;
		काष्ठा crypto_istat_compress compress;
		काष्ठा crypto_istat_hash hash;
		काष्ठा crypto_istat_rng rng;
		काष्ठा crypto_istat_kpp kpp;
	पूर्ण stats;
#पूर्ण_अगर /* CONFIG_CRYPTO_STATS */

पूर्ण CRYPTO_MINALIGN_ATTR;

#अगर_घोषित CONFIG_CRYPTO_STATS
व्योम crypto_stats_init(काष्ठा crypto_alg *alg);
व्योम crypto_stats_get(काष्ठा crypto_alg *alg);
व्योम crypto_stats_aead_encrypt(अचिन्हित पूर्णांक cryptlen, काष्ठा crypto_alg *alg, पूर्णांक ret);
व्योम crypto_stats_aead_decrypt(अचिन्हित पूर्णांक cryptlen, काष्ठा crypto_alg *alg, पूर्णांक ret);
व्योम crypto_stats_ahash_update(अचिन्हित पूर्णांक nbytes, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_ahash_final(अचिन्हित पूर्णांक nbytes, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_akcipher_encrypt(अचिन्हित पूर्णांक src_len, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_akcipher_decrypt(अचिन्हित पूर्णांक src_len, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_akcipher_sign(पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_akcipher_verअगरy(पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_compress(अचिन्हित पूर्णांक slen, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_decompress(अचिन्हित पूर्णांक slen, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_kpp_set_secret(काष्ठा crypto_alg *alg, पूर्णांक ret);
व्योम crypto_stats_kpp_generate_खुला_key(काष्ठा crypto_alg *alg, पूर्णांक ret);
व्योम crypto_stats_kpp_compute_shared_secret(काष्ठा crypto_alg *alg, पूर्णांक ret);
व्योम crypto_stats_rng_seed(काष्ठा crypto_alg *alg, पूर्णांक ret);
व्योम crypto_stats_rng_generate(काष्ठा crypto_alg *alg, अचिन्हित पूर्णांक dlen, पूर्णांक ret);
व्योम crypto_stats_skcipher_encrypt(अचिन्हित पूर्णांक cryptlen, पूर्णांक ret, काष्ठा crypto_alg *alg);
व्योम crypto_stats_skcipher_decrypt(अचिन्हित पूर्णांक cryptlen, पूर्णांक ret, काष्ठा crypto_alg *alg);
#अन्यथा
अटल अंतरभूत व्योम crypto_stats_init(काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_get(काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_aead_encrypt(अचिन्हित पूर्णांक cryptlen, काष्ठा crypto_alg *alg, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_aead_decrypt(अचिन्हित पूर्णांक cryptlen, काष्ठा crypto_alg *alg, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_ahash_update(अचिन्हित पूर्णांक nbytes, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_ahash_final(अचिन्हित पूर्णांक nbytes, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_akcipher_encrypt(अचिन्हित पूर्णांक src_len, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_akcipher_decrypt(अचिन्हित पूर्णांक src_len, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_akcipher_sign(पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_akcipher_verअगरy(पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_compress(अचिन्हित पूर्णांक slen, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_decompress(अचिन्हित पूर्णांक slen, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_kpp_set_secret(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_kpp_generate_खुला_key(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_kpp_compute_shared_secret(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_rng_seed(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_rng_generate(काष्ठा crypto_alg *alg, अचिन्हित पूर्णांक dlen, पूर्णांक ret)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_skcipher_encrypt(अचिन्हित पूर्णांक cryptlen, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
अटल अंतरभूत व्योम crypto_stats_skcipher_decrypt(अचिन्हित पूर्णांक cryptlen, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणुपूर्ण
#पूर्ण_अगर
/*
 * A helper काष्ठा क्रम रुकोing क्रम completion of async crypto ops
 */
काष्ठा crypto_रुको अणु
	काष्ठा completion completion;
	पूर्णांक err;
पूर्ण;

/*
 * Macro क्रम declaring a crypto op async रुको object on stack
 */
#घोषणा DECLARE_CRYPTO_WAIT(_रुको) \
	काष्ठा crypto_रुको _रुको = अणु \
		COMPLETION_INITIALIZER_ONSTACK((_रुको).completion), 0 पूर्ण

/*
 * Async ops completion helper functioons
 */
व्योम crypto_req_करोne(काष्ठा crypto_async_request *req, पूर्णांक err);

अटल अंतरभूत पूर्णांक crypto_रुको_req(पूर्णांक err, काष्ठा crypto_रुको *रुको)
अणु
	चयन (err) अणु
	हाल -EINPROGRESS:
	हाल -EBUSY:
		रुको_क्रम_completion(&रुको->completion);
		reinit_completion(&रुको->completion);
		err = रुको->err;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत व्योम crypto_init_रुको(काष्ठा crypto_रुको *रुको)
अणु
	init_completion(&रुको->completion);
पूर्ण

/*
 * Algorithm registration पूर्णांकerface.
 */
पूर्णांक crypto_रेजिस्टर_alg(काष्ठा crypto_alg *alg);
व्योम crypto_unरेजिस्टर_alg(काष्ठा crypto_alg *alg);
पूर्णांक crypto_रेजिस्टर_algs(काष्ठा crypto_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_algs(काष्ठा crypto_alg *algs, पूर्णांक count);

/*
 * Algorithm query पूर्णांकerface.
 */
पूर्णांक crypto_has_alg(स्थिर अक्षर *name, u32 type, u32 mask);

/*
 * Transक्रमms: user-instantiated objects which encapsulate algorithms
 * and core processing logic.  Managed via crypto_alloc_*() and
 * crypto_मुक्त_*(), as well as the various helpers below.
 */

काष्ठा crypto_tfm अणु

	u32 crt_flags;

	पूर्णांक node;
	
	व्योम (*निकास)(काष्ठा crypto_tfm *tfm);
	
	काष्ठा crypto_alg *__crt_alg;

	व्योम *__crt_ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

काष्ठा crypto_comp अणु
	काष्ठा crypto_tfm base;
पूर्ण;

क्रमागत अणु
	CRYPTOA_UNSPEC,
	CRYPTOA_ALG,
	CRYPTOA_TYPE,
	CRYPTOA_U32,
	__CRYPTOA_MAX,
पूर्ण;

#घोषणा CRYPTOA_MAX (__CRYPTOA_MAX - 1)

/* Maximum number of (rtattr) parameters क्रम each ढाँचा. */
#घोषणा CRYPTO_MAX_ATTRS 32

काष्ठा crypto_attr_alg अणु
	अक्षर name[CRYPTO_MAX_ALG_NAME];
पूर्ण;

काष्ठा crypto_attr_type अणु
	u32 type;
	u32 mask;
पूर्ण;

काष्ठा crypto_attr_u32 अणु
	u32 num;
पूर्ण;

/* 
 * Transक्रमm user पूर्णांकerface.
 */
 
काष्ठा crypto_tfm *crypto_alloc_base(स्थिर अक्षर *alg_name, u32 type, u32 mask);
व्योम crypto_destroy_tfm(व्योम *mem, काष्ठा crypto_tfm *tfm);

अटल अंतरभूत व्योम crypto_मुक्त_tfm(काष्ठा crypto_tfm *tfm)
अणु
	वापस crypto_destroy_tfm(tfm, tfm);
पूर्ण

पूर्णांक alg_test(स्थिर अक्षर *driver, स्थिर अक्षर *alg, u32 type, u32 mask);

/*
 * Transक्रमm helpers which query the underlying algorithm.
 */
अटल अंतरभूत स्थिर अक्षर *crypto_tfm_alg_name(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_alg->cra_name;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *crypto_tfm_alg_driver_name(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_alg->cra_driver_name;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_tfm_alg_priority(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_alg->cra_priority;
पूर्ण

अटल अंतरभूत u32 crypto_tfm_alg_type(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_alg->cra_flags & CRYPTO_ALG_TYPE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_tfm_alg_blocksize(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_alg->cra_blocksize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_tfm_alg_alignmask(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_alg->cra_alignmask;
पूर्ण

अटल अंतरभूत u32 crypto_tfm_get_flags(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->crt_flags;
पूर्ण

अटल अंतरभूत व्योम crypto_tfm_set_flags(काष्ठा crypto_tfm *tfm, u32 flags)
अणु
	tfm->crt_flags |= flags;
पूर्ण

अटल अंतरभूत व्योम crypto_tfm_clear_flags(काष्ठा crypto_tfm *tfm, u32 flags)
अणु
	tfm->crt_flags &= ~flags;
पूर्ण

अटल अंतरभूत व्योम *crypto_tfm_ctx(काष्ठा crypto_tfm *tfm)
अणु
	वापस tfm->__crt_ctx;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_tfm_ctx_alignment(व्योम)
अणु
	काष्ठा crypto_tfm *tfm;
	वापस __alignof__(tfm->__crt_ctx);
पूर्ण

अटल अंतरभूत काष्ठा crypto_comp *__crypto_comp_cast(काष्ठा crypto_tfm *tfm)
अणु
	वापस (काष्ठा crypto_comp *)tfm;
पूर्ण

अटल अंतरभूत काष्ठा crypto_comp *crypto_alloc_comp(स्थिर अक्षर *alg_name,
						    u32 type, u32 mask)
अणु
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_COMPRESS;
	mask |= CRYPTO_ALG_TYPE_MASK;

	वापस __crypto_comp_cast(crypto_alloc_base(alg_name, type, mask));
पूर्ण

अटल अंतरभूत काष्ठा crypto_tfm *crypto_comp_tfm(काष्ठा crypto_comp *tfm)
अणु
	वापस &tfm->base;
पूर्ण

अटल अंतरभूत व्योम crypto_मुक्त_comp(काष्ठा crypto_comp *tfm)
अणु
	crypto_मुक्त_tfm(crypto_comp_tfm(tfm));
पूर्ण

अटल अंतरभूत पूर्णांक crypto_has_comp(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_COMPRESS;
	mask |= CRYPTO_ALG_TYPE_MASK;

	वापस crypto_has_alg(alg_name, type, mask);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *crypto_comp_name(काष्ठा crypto_comp *tfm)
अणु
	वापस crypto_tfm_alg_name(crypto_comp_tfm(tfm));
पूर्ण

पूर्णांक crypto_comp_compress(काष्ठा crypto_comp *tfm,
			 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			 u8 *dst, अचिन्हित पूर्णांक *dlen);

पूर्णांक crypto_comp_decompress(काष्ठा crypto_comp *tfm,
			   स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			   u8 *dst, अचिन्हित पूर्णांक *dlen);

#पूर्ण_अगर	/* _LINUX_CRYPTO_H */

