<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _COMMON_H_
#घोषणा _COMMON_H_

#समावेश <linux/crypto.h>
#समावेश <linux/types.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

/* xts du size */
#घोषणा QCE_SECTOR_SIZE			512

/* key size in bytes */
#घोषणा QCE_SHA_HMAC_KEY_SIZE		64
#घोषणा QCE_MAX_CIPHER_KEY_SIZE		AES_KEYSIZE_256

/* IV length in bytes */
#घोषणा QCE_AES_IV_LENGTH		AES_BLOCK_SIZE
/* max of AES_BLOCK_SIZE, DES3_EDE_BLOCK_SIZE */
#घोषणा QCE_MAX_IV_SIZE			AES_BLOCK_SIZE

/* maximum nonce bytes  */
#घोषणा QCE_MAX_NONCE			16
#घोषणा QCE_MAX_NONCE_WORDS		(QCE_MAX_NONCE / माप(u32))

/* burst size alignment requirement */
#घोषणा QCE_MAX_ALIGN_SIZE		64

/* cipher algorithms */
#घोषणा QCE_ALG_DES			BIT(0)
#घोषणा QCE_ALG_3DES			BIT(1)
#घोषणा QCE_ALG_AES			BIT(2)

/* hash and hmac algorithms */
#घोषणा QCE_HASH_SHA1			BIT(3)
#घोषणा QCE_HASH_SHA256			BIT(4)
#घोषणा QCE_HASH_SHA1_HMAC		BIT(5)
#घोषणा QCE_HASH_SHA256_HMAC		BIT(6)
#घोषणा QCE_HASH_AES_CMAC		BIT(7)

/* cipher modes */
#घोषणा QCE_MODE_CBC			BIT(8)
#घोषणा QCE_MODE_ECB			BIT(9)
#घोषणा QCE_MODE_CTR			BIT(10)
#घोषणा QCE_MODE_XTS			BIT(11)
#घोषणा QCE_MODE_CCM			BIT(12)
#घोषणा QCE_MODE_MASK			GENMASK(12, 8)

/* cipher encryption/decryption operations */
#घोषणा QCE_ENCRYPT			BIT(13)
#घोषणा QCE_DECRYPT			BIT(14)

#घोषणा IS_DES(flags)			(flags & QCE_ALG_DES)
#घोषणा IS_3DES(flags)			(flags & QCE_ALG_3DES)
#घोषणा IS_AES(flags)			(flags & QCE_ALG_AES)

#घोषणा IS_SHA1(flags)			(flags & QCE_HASH_SHA1)
#घोषणा IS_SHA256(flags)		(flags & QCE_HASH_SHA256)
#घोषणा IS_SHA1_HMAC(flags)		(flags & QCE_HASH_SHA1_HMAC)
#घोषणा IS_SHA256_HMAC(flags)		(flags & QCE_HASH_SHA256_HMAC)
#घोषणा IS_CMAC(flags)			(flags & QCE_HASH_AES_CMAC)
#घोषणा IS_SHA(flags)			(IS_SHA1(flags) || IS_SHA256(flags))
#घोषणा IS_SHA_HMAC(flags)		\
		(IS_SHA1_HMAC(flags) || IS_SHA256_HMAC(flags))

#घोषणा IS_CBC(mode)			(mode & QCE_MODE_CBC)
#घोषणा IS_ECB(mode)			(mode & QCE_MODE_ECB)
#घोषणा IS_CTR(mode)			(mode & QCE_MODE_CTR)
#घोषणा IS_XTS(mode)			(mode & QCE_MODE_XTS)
#घोषणा IS_CCM(mode)			(mode & QCE_MODE_CCM)

#घोषणा IS_ENCRYPT(dir)			(dir & QCE_ENCRYPT)
#घोषणा IS_DECRYPT(dir)			(dir & QCE_DECRYPT)

काष्ठा qce_alg_ढाँचा अणु
	काष्ठा list_head entry;
	u32 crypto_alg_type;
	अचिन्हित दीर्घ alg_flags;
	स्थिर u32 *std_iv;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा ahash_alg ahash;
	पूर्ण alg;
	काष्ठा qce_device *qce;
	स्थिर u8 *hash_zero;
	स्थिर u32 digest_size;
पूर्ण;

व्योम qce_cpu_to_be32p_array(__be32 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक len);
पूर्णांक qce_check_status(काष्ठा qce_device *qce, u32 *status);
व्योम qce_get_version(काष्ठा qce_device *qce, u32 *major, u32 *minor, u32 *step);
पूर्णांक qce_start(काष्ठा crypto_async_request *async_req, u32 type);

#पूर्ण_अगर /* _COMMON_H_ */
