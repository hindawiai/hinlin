<शैली गुरु>
/* Orinoco MIC helpers
 *
 * See copyright notice in मुख्य.c
 */
#अगर_अघोषित _ORINOCO_MIC_H_
#घोषणा _ORINOCO_MIC_H_

#समावेश <linux/types.h>
#समावेश <crypto/hash.h>

#घोषणा MICHAEL_MIC_LEN 8

/* Forward declarations */
काष्ठा orinoco_निजी;
काष्ठा crypto_ahash;

पूर्णांक orinoco_mic_init(काष्ठा orinoco_निजी *priv);
व्योम orinoco_mic_मुक्त(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_mic(काष्ठा crypto_shash *tfm_michael, u8 *key,
		u8 *da, u8 *sa, u8 priority,
		u8 *data, माप_प्रकार data_len, u8 *mic);

#पूर्ण_अगर /* ORINOCO_MIC_H */
