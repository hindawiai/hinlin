<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Cryptographic API.
 *
 * s390 generic implementation of the SHA Secure Hash Algorithms.
 *
 * Copyright IBM Corp. 2007
 * Author(s): Jan Glauber (jang@de.ibm.com)
 */
#अगर_अघोषित _CRYPTO_ARCH_S390_SHA_H
#घोषणा _CRYPTO_ARCH_S390_SHA_H

#समावेश <linux/crypto.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha3.h>

/* must be big enough क्रम the largest SHA variant */
#घोषणा SHA3_STATE_SIZE			200
#घोषणा CPACF_MAX_PARMBLOCK_SIZE	SHA3_STATE_SIZE
#घोषणा SHA_MAX_BLOCK_SIZE		SHA3_224_BLOCK_SIZE

काष्ठा s390_sha_ctx अणु
	u64 count;		/* message length in bytes */
	u32 state[CPACF_MAX_PARMBLOCK_SIZE / माप(u32)];
	u8 buf[SHA_MAX_BLOCK_SIZE];
	पूर्णांक func;		/* KIMD function to use */
पूर्ण;

काष्ठा shash_desc;

पूर्णांक s390_sha_update(काष्ठा shash_desc *desc, स्थिर u8 *data, अचिन्हित पूर्णांक len);
पूर्णांक s390_sha_final(काष्ठा shash_desc *desc, u8 *out);

#पूर्ण_अगर
