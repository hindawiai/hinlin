<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CRYPTO_XTS_H
#घोषणा _CRYPTO_XTS_H

#समावेश <crypto/b128ops.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/fips.h>

#घोषणा XTS_BLOCK_SIZE 16

अटल अंतरभूत पूर्णांक xts_check_key(काष्ठा crypto_tfm *tfm,
				स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	/*
	 * key consists of keys of equal size concatenated, thereक्रमe
	 * the length must be even.
	 */
	अगर (keylen % 2)
		वापस -EINVAL;

	/* ensure that the AES and tweak key are not identical */
	अगर (fips_enabled && !crypto_memneq(key, key + (keylen / 2), keylen / 2))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xts_verअगरy_key(काष्ठा crypto_skcipher *tfm,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	/*
	 * key consists of keys of equal size concatenated, thereक्रमe
	 * the length must be even.
	 */
	अगर (keylen % 2)
		वापस -EINVAL;

	/* ensure that the AES and tweak key are not identical */
	अगर ((fips_enabled || (crypto_skcipher_get_flags(tfm) &
			      CRYPTO_TFM_REQ_FORBID_WEAK_KEYS)) &&
	    !crypto_memneq(key, key + (keylen / 2), keylen / 2))
		वापस -EINVAL;

	वापस 0;
पूर्ण

#पूर्ण_अगर  /* _CRYPTO_XTS_H */
