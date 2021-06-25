<शैली गुरु>
/* Orinoco MIC helpers
 *
 * See copyright notice in मुख्य.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/hash.h>

#समावेश "orinoco.h"
#समावेश "mic.h"

/********************************************************************/
/* Michael MIC crypto setup                                         */
/********************************************************************/
पूर्णांक orinoco_mic_init(काष्ठा orinoco_निजी *priv)
अणु
	priv->tx_tfm_mic = crypto_alloc_shash("michael_mic", 0, 0);
	अगर (IS_ERR(priv->tx_tfm_mic)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: could not allocate "
		       "crypto API michael_mic\n", __func__);
		priv->tx_tfm_mic = शून्य;
		वापस -ENOMEM;
	पूर्ण

	priv->rx_tfm_mic = crypto_alloc_shash("michael_mic", 0, 0);
	अगर (IS_ERR(priv->rx_tfm_mic)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: could not allocate "
		       "crypto API michael_mic\n", __func__);
		priv->rx_tfm_mic = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम orinoco_mic_मुक्त(काष्ठा orinoco_निजी *priv)
अणु
	अगर (priv->tx_tfm_mic)
		crypto_मुक्त_shash(priv->tx_tfm_mic);
	अगर (priv->rx_tfm_mic)
		crypto_मुक्त_shash(priv->rx_tfm_mic);
पूर्ण

पूर्णांक orinoco_mic(काष्ठा crypto_shash *tfm_michael, u8 *key,
		u8 *da, u8 *sa, u8 priority,
		u8 *data, माप_प्रकार data_len, u8 *mic)
अणु
	SHASH_DESC_ON_STACK(desc, tfm_michael);
	u8 hdr[ETH_HLEN + 2]; /* size of header + padding */
	पूर्णांक err;

	अगर (tfm_michael == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "%s: tfm_michael == NULL\n", __func__);
		वापस -1;
	पूर्ण

	/* Copy header पूर्णांकo buffer. We need the padding on the end zeroed */
	स_नकल(&hdr[0], da, ETH_ALEN);
	स_नकल(&hdr[ETH_ALEN], sa, ETH_ALEN);
	hdr[ETH_ALEN * 2] = priority;
	hdr[ETH_ALEN * 2 + 1] = 0;
	hdr[ETH_ALEN * 2 + 2] = 0;
	hdr[ETH_ALEN * 2 + 3] = 0;

	desc->tfm = tfm_michael;

	err = crypto_shash_setkey(tfm_michael, key, MIC_KEYLEN);
	अगर (err)
		वापस err;

	err = crypto_shash_init(desc);
	अगर (err)
		वापस err;

	err = crypto_shash_update(desc, hdr, माप(hdr));
	अगर (err)
		वापस err;

	err = crypto_shash_update(desc, data, data_len);
	अगर (err)
		वापस err;

	err = crypto_shash_final(desc, mic);
	shash_desc_zero(desc);

	वापस err;
पूर्ण
