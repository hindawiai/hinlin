<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * DES & Triple DES EDE key verअगरication helpers
 */

#अगर_अघोषित __CRYPTO_INTERNAL_DES_H
#घोषणा __CRYPTO_INTERNAL_DES_H

#समावेश <linux/crypto.h>
#समावेश <linux/fips.h>
#समावेश <crypto/des.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/skcipher.h>

/**
 * crypto_des_verअगरy_key - Check whether a DES key is weak
 * @tfm: the crypto algo
 * @key: the key buffer
 *
 * Returns -EINVAL अगर the key is weak and the crypto TFM करोes not permit weak
 * keys. Otherwise, 0 is वापसed.
 *
 * It is the job of the caller to ensure that the size of the key equals
 * DES_KEY_SIZE.
 */
अटल अंतरभूत पूर्णांक crypto_des_verअगरy_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *key)
अणु
	काष्ठा des_ctx पंचांगp;
	पूर्णांक err;

	err = des_expand_key(&पंचांगp, key, DES_KEY_SIZE);
	अगर (err == -ENOKEY) अणु
		अगर (crypto_tfm_get_flags(tfm) & CRYPTO_TFM_REQ_FORBID_WEAK_KEYS)
			err = -EINVAL;
		अन्यथा
			err = 0;
	पूर्ण
	memzero_explicit(&पंचांगp, माप(पंचांगp));
	वापस err;
पूर्ण

/*
 * RFC2451:
 *
 *   For DES-EDE3, there is no known need to reject weak or
 *   complementation keys.  Any weakness is obviated by the use of
 *   multiple keys.
 *
 *   However, अगर the first two or last two independent 64-bit keys are
 *   equal (k1 == k2 or k2 == k3), then the DES3 operation is simply the
 *   same as DES.  Implementers MUST reject keys that exhibit this
 *   property.
 *
 */
अटल अंतरभूत पूर्णांक des3_ede_verअगरy_key(स्थिर u8 *key, अचिन्हित पूर्णांक key_len,
				      bool check_weak)
अणु
	पूर्णांक ret = fips_enabled ? -EINVAL : -ENOKEY;
	u32 K[6];

	स_नकल(K, key, DES3_EDE_KEY_SIZE);

	अगर ((!((K[0] ^ K[2]) | (K[1] ^ K[3])) ||
	     !((K[2] ^ K[4]) | (K[3] ^ K[5]))) &&
	    (fips_enabled || check_weak))
		जाओ bad;

	अगर ((!((K[0] ^ K[4]) | (K[1] ^ K[5]))) && fips_enabled)
		जाओ bad;

	ret = 0;
bad:
	memzero_explicit(K, DES3_EDE_KEY_SIZE);

	वापस ret;
पूर्ण

/**
 * crypto_des3_ede_verअगरy_key - Check whether a DES3-EDE key is weak
 * @tfm: the crypto algo
 * @key: the key buffer
 *
 * Returns -EINVAL अगर the key is weak and the crypto TFM करोes not permit weak
 * keys or when running in FIPS mode. Otherwise, 0 is वापसed. Note that some
 * keys are rejected in FIPS mode even अगर weak keys are permitted by the TFM
 * flags.
 *
 * It is the job of the caller to ensure that the size of the key equals
 * DES3_EDE_KEY_SIZE.
 */
अटल अंतरभूत पूर्णांक crypto_des3_ede_verअगरy_key(काष्ठा crypto_tfm *tfm,
					     स्थिर u8 *key)
अणु
	वापस des3_ede_verअगरy_key(key, DES3_EDE_KEY_SIZE,
				   crypto_tfm_get_flags(tfm) &
				   CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_skcipher_des_key(काष्ठा crypto_skcipher *tfm,
					  स्थिर u8 *key)
अणु
	वापस crypto_des_verअगरy_key(crypto_skcipher_tfm(tfm), key);
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_skcipher_des3_key(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key)
अणु
	वापस crypto_des3_ede_verअगरy_key(crypto_skcipher_tfm(tfm), key);
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_aead_des_key(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				      पूर्णांक keylen)
अणु
	अगर (keylen != DES_KEY_SIZE)
		वापस -EINVAL;
	वापस crypto_des_verअगरy_key(crypto_aead_tfm(tfm), key);
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_aead_des3_key(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				       पूर्णांक keylen)
अणु
	अगर (keylen != DES3_EDE_KEY_SIZE)
		वापस -EINVAL;
	वापस crypto_des3_ede_verअगरy_key(crypto_aead_tfm(tfm), key);
पूर्ण

#पूर्ण_अगर /* __CRYPTO_INTERNAL_DES_H */
