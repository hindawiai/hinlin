<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CRYPTO_TWOFISH_H
#घोषणा _CRYPTO_TWOFISH_H

#समावेश <linux/types.h>

#घोषणा TF_MIN_KEY_SIZE 16
#घोषणा TF_MAX_KEY_SIZE 32
#घोषणा TF_BLOCK_SIZE 16

काष्ठा crypto_tfm;

/* Structure क्रम an expanded Twofish key.  s contains the key-dependent
 * S-boxes composed with the MDS matrix; w contains the eight "whitening"
 * subkeys, K[0] through K[7].	k holds the reमुख्यing, "round" subkeys.  Note
 * that k[i] corresponds to what the Twofish paper calls K[i+8]. */
काष्ठा twofish_ctx अणु
	u32 s[4][256], w[8], k[32];
पूर्ण;

पूर्णांक __twofish_setkey(काष्ठा twofish_ctx *ctx, स्थिर u8 *key,
		     अचिन्हित पूर्णांक key_len);
पूर्णांक twofish_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key, अचिन्हित पूर्णांक key_len);

#पूर्ण_अगर
