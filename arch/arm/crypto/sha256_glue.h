<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CRYPTO_SHA256_GLUE_H
#घोषणा _CRYPTO_SHA256_GLUE_H

#समावेश <linux/crypto.h>

बाह्य काष्ठा shash_alg sha256_neon_algs[2];

पूर्णांक crypto_sha256_arm_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len);

पूर्णांक crypto_sha256_arm_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len, u8 *hash);

#पूर्ण_अगर /* _CRYPTO_SHA256_GLUE_H */
