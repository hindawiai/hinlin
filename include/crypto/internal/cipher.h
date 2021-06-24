<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 David S. Miller (davem@redhat.com)
 * Copyright (c) 2005 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * Portions derived from Cryptoapi, by Alexander Kjeldaas <astor@fast.no>
 * and Nettle, by Niels Mथघller.
 */

#अगर_अघोषित _CRYPTO_INTERNAL_CIPHER_H
#घोषणा _CRYPTO_INTERNAL_CIPHER_H

#समावेश <crypto/algapi.h>

काष्ठा crypto_cipher अणु
	काष्ठा crypto_tfm base;
पूर्ण;

/**
 * DOC: Single Block Cipher API
 *
 * The single block cipher API is used with the ciphers of type
 * CRYPTO_ALG_TYPE_CIPHER (listed as type "cipher" in /proc/crypto).
 *
 * Using the single block cipher API calls, operations with the basic cipher
 * primitive can be implemented. These cipher primitives exclude any block
 * chaining operations including IV handling.
 *
 * The purpose of this single block cipher API is to support the implementation
 * of ढाँचाs or other concepts that only need to perक्रमm the cipher operation
 * on one block at a समय. Templates invoke the underlying cipher primitive
 * block-wise and process either the input or the output data of these cipher
 * operations.
 */

अटल अंतरभूत काष्ठा crypto_cipher *__crypto_cipher_cast(काष्ठा crypto_tfm *tfm)
अणु
	वापस (काष्ठा crypto_cipher *)tfm;
पूर्ण

/**
 * crypto_alloc_cipher() - allocate single block cipher handle
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	     single block cipher
 * @type: specअगरies the type of the cipher
 * @mask: specअगरies the mask क्रम the cipher
 *
 * Allocate a cipher handle क्रम a single block cipher. The वापसed काष्ठा
 * crypto_cipher is the cipher handle that is required क्रम any subsequent API
 * invocation क्रम that single block cipher.
 *
 * Return: allocated cipher handle in हाल of success; IS_ERR() is true in हाल
 *	   of an error, PTR_ERR() वापसs the error code.
 */
अटल अंतरभूत काष्ठा crypto_cipher *crypto_alloc_cipher(स्थिर अक्षर *alg_name,
							u32 type, u32 mask)
अणु
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_CIPHER;
	mask |= CRYPTO_ALG_TYPE_MASK;

	वापस __crypto_cipher_cast(crypto_alloc_base(alg_name, type, mask));
पूर्ण

अटल अंतरभूत काष्ठा crypto_tfm *crypto_cipher_tfm(काष्ठा crypto_cipher *tfm)
अणु
	वापस &tfm->base;
पूर्ण

/**
 * crypto_मुक्त_cipher() - zeroize and मुक्त the single block cipher handle
 * @tfm: cipher handle to be मुक्तd
 */
अटल अंतरभूत व्योम crypto_मुक्त_cipher(काष्ठा crypto_cipher *tfm)
अणु
	crypto_मुक्त_tfm(crypto_cipher_tfm(tfm));
पूर्ण

/**
 * crypto_has_cipher() - Search क्रम the availability of a single block cipher
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	     single block cipher
 * @type: specअगरies the type of the cipher
 * @mask: specअगरies the mask क्रम the cipher
 *
 * Return: true when the single block cipher is known to the kernel crypto API;
 *	   false otherwise
 */
अटल अंतरभूत पूर्णांक crypto_has_cipher(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_CIPHER;
	mask |= CRYPTO_ALG_TYPE_MASK;

	वापस crypto_has_alg(alg_name, type, mask);
पूर्ण

/**
 * crypto_cipher_blocksize() - obtain block size क्रम cipher
 * @tfm: cipher handle
 *
 * The block size क्रम the single block cipher referenced with the cipher handle
 * tfm is वापसed. The caller may use that inक्रमmation to allocate appropriate
 * memory क्रम the data वापसed by the encryption or decryption operation
 *
 * Return: block size of cipher
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_cipher_blocksize(काष्ठा crypto_cipher *tfm)
अणु
	वापस crypto_tfm_alg_blocksize(crypto_cipher_tfm(tfm));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_cipher_alignmask(काष्ठा crypto_cipher *tfm)
अणु
	वापस crypto_tfm_alg_alignmask(crypto_cipher_tfm(tfm));
पूर्ण

अटल अंतरभूत u32 crypto_cipher_get_flags(काष्ठा crypto_cipher *tfm)
अणु
	वापस crypto_tfm_get_flags(crypto_cipher_tfm(tfm));
पूर्ण

अटल अंतरभूत व्योम crypto_cipher_set_flags(काष्ठा crypto_cipher *tfm,
					   u32 flags)
अणु
	crypto_tfm_set_flags(crypto_cipher_tfm(tfm), flags);
पूर्ण

अटल अंतरभूत व्योम crypto_cipher_clear_flags(काष्ठा crypto_cipher *tfm,
					     u32 flags)
अणु
	crypto_tfm_clear_flags(crypto_cipher_tfm(tfm), flags);
पूर्ण

/**
 * crypto_cipher_setkey() - set key क्रम cipher
 * @tfm: cipher handle
 * @key: buffer holding the key
 * @keylen: length of the key in bytes
 *
 * The caller provided key is set क्रम the single block cipher referenced by the
 * cipher handle.
 *
 * Note, the key length determines the cipher type. Many block ciphers implement
 * dअगरferent cipher modes depending on the key size, such as AES-128 vs AES-192
 * vs. AES-256. When providing a 16 byte key क्रम an AES cipher handle, AES-128
 * is perक्रमmed.
 *
 * Return: 0 अगर the setting of the key was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_cipher_setkey(काष्ठा crypto_cipher *tfm,
			 स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

/**
 * crypto_cipher_encrypt_one() - encrypt one block of plaपूर्णांकext
 * @tfm: cipher handle
 * @dst: poपूर्णांकs to the buffer that will be filled with the ciphertext
 * @src: buffer holding the plaपूर्णांकext to be encrypted
 *
 * Invoke the encryption operation of one block. The caller must ensure that
 * the plaपूर्णांकext and ciphertext buffers are at least one block in size.
 */
व्योम crypto_cipher_encrypt_one(काष्ठा crypto_cipher *tfm,
			       u8 *dst, स्थिर u8 *src);

/**
 * crypto_cipher_decrypt_one() - decrypt one block of ciphertext
 * @tfm: cipher handle
 * @dst: poपूर्णांकs to the buffer that will be filled with the plaपूर्णांकext
 * @src: buffer holding the ciphertext to be decrypted
 *
 * Invoke the decryption operation of one block. The caller must ensure that
 * the plaपूर्णांकext and ciphertext buffers are at least one block in size.
 */
व्योम crypto_cipher_decrypt_one(काष्ठा crypto_cipher *tfm,
			       u8 *dst, स्थिर u8 *src);

काष्ठा crypto_cipher_spawn अणु
	काष्ठा crypto_spawn base;
पूर्ण;

अटल अंतरभूत पूर्णांक crypto_grab_cipher(काष्ठा crypto_cipher_spawn *spawn,
				     काष्ठा crypto_instance *inst,
				     स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_CIPHER;
	mask |= CRYPTO_ALG_TYPE_MASK;
	वापस crypto_grab_spawn(&spawn->base, inst, name, type, mask);
पूर्ण

अटल अंतरभूत व्योम crypto_drop_cipher(काष्ठा crypto_cipher_spawn *spawn)
अणु
	crypto_drop_spawn(&spawn->base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_alg *crypto_spawn_cipher_alg(
       काष्ठा crypto_cipher_spawn *spawn)
अणु
	वापस spawn->base.alg;
पूर्ण

अटल अंतरभूत काष्ठा crypto_cipher *crypto_spawn_cipher(
	काष्ठा crypto_cipher_spawn *spawn)
अणु
	u32 type = CRYPTO_ALG_TYPE_CIPHER;
	u32 mask = CRYPTO_ALG_TYPE_MASK;

	वापस __crypto_cipher_cast(crypto_spawn_tfm(&spawn->base, type, mask));
पूर्ण

अटल अंतरभूत काष्ठा cipher_alg *crypto_cipher_alg(काष्ठा crypto_cipher *tfm)
अणु
	वापस &crypto_cipher_tfm(tfm)->__crt_alg->cra_cipher;
पूर्ण

#पूर्ण_अगर
