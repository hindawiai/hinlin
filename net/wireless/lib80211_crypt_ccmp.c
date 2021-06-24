<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib80211 crypt: host-based CCMP encryption implementation क्रम lib80211
 *
 * Copyright (c) 2003-2004, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2008, John W. Linville <linville@tuxdriver.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <यंत्र/माला.स>
#समावेश <linux/wireless.h>

#समावेश <linux/ieee80211.h>

#समावेश <linux/crypto.h>
#समावेश <crypto/aead.h>

#समावेश <net/lib80211.h>

MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("Host AP crypt: CCMP");
MODULE_LICENSE("GPL");

#घोषणा AES_BLOCK_LEN 16
#घोषणा CCMP_HDR_LEN 8
#घोषणा CCMP_MIC_LEN 8
#घोषणा CCMP_TK_LEN 16
#घोषणा CCMP_PN_LEN 6

काष्ठा lib80211_ccmp_data अणु
	u8 key[CCMP_TK_LEN];
	पूर्णांक key_set;

	u8 tx_pn[CCMP_PN_LEN];
	u8 rx_pn[CCMP_PN_LEN];

	u32 करोt11RSNAStatsCCMPFormatErrors;
	u32 करोt11RSNAStatsCCMPReplays;
	u32 करोt11RSNAStatsCCMPDecryptErrors;

	पूर्णांक key_idx;

	काष्ठा crypto_aead *tfm;

	/* scratch buffers क्रम virt_to_page() (crypto API) */
	u8 tx_aad[2 * AES_BLOCK_LEN];
	u8 rx_aad[2 * AES_BLOCK_LEN];
पूर्ण;

अटल व्योम *lib80211_ccmp_init(पूर्णांक key_idx)
अणु
	काष्ठा lib80211_ccmp_data *priv;

	priv = kzalloc(माप(*priv), GFP_ATOMIC);
	अगर (priv == शून्य)
		जाओ fail;
	priv->key_idx = key_idx;

	priv->tfm = crypto_alloc_aead("ccm(aes)", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(priv->tfm)) अणु
		priv->tfm = शून्य;
		जाओ fail;
	पूर्ण

	वापस priv;

      fail:
	अगर (priv) अणु
		अगर (priv->tfm)
			crypto_मुक्त_aead(priv->tfm);
		kमुक्त(priv);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम lib80211_ccmp_deinit(व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *_priv = priv;
	अगर (_priv && _priv->tfm)
		crypto_मुक्त_aead(_priv->tfm);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक ccmp_init_iv_and_aad(स्थिर काष्ठा ieee80211_hdr *hdr,
				स्थिर u8 *pn, u8 *iv, u8 *aad)
अणु
	u8 *pos, qc = 0;
	माप_प्रकार aad_len;
	पूर्णांक a4_included, qc_included;

	a4_included = ieee80211_has_a4(hdr->frame_control);
	qc_included = ieee80211_is_data_qos(hdr->frame_control);

	aad_len = 22;
	अगर (a4_included)
		aad_len += 6;
	अगर (qc_included) अणु
		pos = (u8 *) & hdr->addr4;
		अगर (a4_included)
			pos += 6;
		qc = *pos & 0x0f;
		aad_len += 2;
	पूर्ण

	/* In CCM, the initial vectors (IV) used क्रम CTR mode encryption and CBC
	 * mode authentication are not allowed to collide, yet both are derived
	 * from the same vector. We only set L := 1 here to indicate that the
	 * data size can be represented in (L+1) bytes. The CCM layer will take
	 * care of storing the data length in the top (L+1) bytes and setting
	 * and clearing the other bits as is required to derive the two IVs.
	 */
	iv[0] = 0x1;

	/* Nonce: QC | A2 | PN */
	iv[1] = qc;
	स_नकल(iv + 2, hdr->addr2, ETH_ALEN);
	स_नकल(iv + 8, pn, CCMP_PN_LEN);

	/* AAD:
	 * FC with bits 4..6 and 11..13 masked to zero; 14 is always one
	 * A1 | A2 | A3
	 * SC with bits 4..15 (seq#) masked to zero
	 * A4 (अगर present)
	 * QC (अगर present)
	 */
	pos = (u8 *) hdr;
	aad[0] = pos[0] & 0x8f;
	aad[1] = pos[1] & 0xc7;
	स_नकल(aad + 2, hdr->addr1, 3 * ETH_ALEN);
	pos = (u8 *) & hdr->seq_ctrl;
	aad[20] = pos[0] & 0x0f;
	aad[21] = 0;		/* all bits masked */
	स_रखो(aad + 22, 0, 8);
	अगर (a4_included)
		स_नकल(aad + 22, hdr->addr4, ETH_ALEN);
	अगर (qc_included) अणु
		aad[a4_included ? 28 : 22] = qc;
		/* rest of QC masked */
	पूर्ण
	वापस aad_len;
पूर्ण

अटल पूर्णांक lib80211_ccmp_hdr(काष्ठा sk_buff *skb, पूर्णांक hdr_len,
			      u8 *aeskey, पूर्णांक keylen, व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *key = priv;
	पूर्णांक i;
	u8 *pos;

	अगर (skb_headroom(skb) < CCMP_HDR_LEN || skb->len < hdr_len)
		वापस -1;

	अगर (aeskey != शून्य && keylen >= CCMP_TK_LEN)
		स_नकल(aeskey, key->key, CCMP_TK_LEN);

	pos = skb_push(skb, CCMP_HDR_LEN);
	स_हटाओ(pos, pos + CCMP_HDR_LEN, hdr_len);
	pos += hdr_len;

	i = CCMP_PN_LEN - 1;
	जबतक (i >= 0) अणु
		key->tx_pn[i]++;
		अगर (key->tx_pn[i] != 0)
			अवरोध;
		i--;
	पूर्ण

	*pos++ = key->tx_pn[5];
	*pos++ = key->tx_pn[4];
	*pos++ = 0;
	*pos++ = (key->key_idx << 6) | (1 << 5) /* Ext IV included */ ;
	*pos++ = key->tx_pn[3];
	*pos++ = key->tx_pn[2];
	*pos++ = key->tx_pn[1];
	*pos++ = key->tx_pn[0];

	वापस CCMP_HDR_LEN;
पूर्ण

अटल पूर्णांक lib80211_ccmp_encrypt(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *key = priv;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा aead_request *req;
	काष्ठा scatterlist sg[2];
	u8 *aad = key->tx_aad;
	u8 iv[AES_BLOCK_LEN];
	पूर्णांक len, data_len, aad_len;
	पूर्णांक ret;

	अगर (skb_tailroom(skb) < CCMP_MIC_LEN || skb->len < hdr_len)
		वापस -1;

	data_len = skb->len - hdr_len;
	len = lib80211_ccmp_hdr(skb, hdr_len, शून्य, 0, priv);
	अगर (len < 0)
		वापस -1;

	req = aead_request_alloc(key->tfm, GFP_ATOMIC);
	अगर (!req)
		वापस -ENOMEM;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	aad_len = ccmp_init_iv_and_aad(hdr, key->tx_pn, iv, aad);

	skb_put(skb, CCMP_MIC_LEN);

	sg_init_table(sg, 2);
	sg_set_buf(&sg[0], aad, aad_len);
	sg_set_buf(&sg[1], skb->data + hdr_len + CCMP_HDR_LEN,
		   data_len + CCMP_MIC_LEN);

	aead_request_set_callback(req, 0, शून्य, शून्य);
	aead_request_set_ad(req, aad_len);
	aead_request_set_crypt(req, sg, sg, data_len, iv);

	ret = crypto_aead_encrypt(req);
	aead_request_मुक्त(req);

	वापस ret;
पूर्ण

/*
 * deal with seq counter wrapping correctly.
 * refer to समयr_after() क्रम jअगरfies wrapping handling
 */
अटल अंतरभूत पूर्णांक ccmp_replay_check(u8 *pn_n, u8 *pn_o)
अणु
	u32 iv32_n, iv16_n;
	u32 iv32_o, iv16_o;

	iv32_n = (pn_n[0] << 24) | (pn_n[1] << 16) | (pn_n[2] << 8) | pn_n[3];
	iv16_n = (pn_n[4] << 8) | pn_n[5];

	iv32_o = (pn_o[0] << 24) | (pn_o[1] << 16) | (pn_o[2] << 8) | pn_o[3];
	iv16_o = (pn_o[4] << 8) | pn_o[5];

	अगर ((s32)iv32_n - (s32)iv32_o < 0 ||
	    (iv32_n == iv32_o && iv16_n <= iv16_o))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक lib80211_ccmp_decrypt(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *key = priv;
	u8 keyidx, *pos;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा aead_request *req;
	काष्ठा scatterlist sg[2];
	u8 *aad = key->rx_aad;
	u8 iv[AES_BLOCK_LEN];
	u8 pn[6];
	पूर्णांक aad_len, ret;
	माप_प्रकार data_len = skb->len - hdr_len - CCMP_HDR_LEN;

	अगर (skb->len < hdr_len + CCMP_HDR_LEN + CCMP_MIC_LEN) अणु
		key->करोt11RSNAStatsCCMPFormatErrors++;
		वापस -1;
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	pos = skb->data + hdr_len;
	keyidx = pos[3];
	अगर (!(keyidx & (1 << 5))) अणु
		net_dbg_ratelimited("CCMP: received packet without ExtIV flag from %pM\n",
				    hdr->addr2);
		key->करोt11RSNAStatsCCMPFormatErrors++;
		वापस -2;
	पूर्ण
	keyidx >>= 6;
	अगर (key->key_idx != keyidx) अणु
		net_dbg_ratelimited("CCMP: RX tkey->key_idx=%d frame keyidx=%d\n",
				    key->key_idx, keyidx);
		वापस -6;
	पूर्ण
	अगर (!key->key_set) अणु
		net_dbg_ratelimited("CCMP: received packet from %pM with keyid=%d that does not have a configured key\n",
				    hdr->addr2, keyidx);
		वापस -3;
	पूर्ण

	pn[0] = pos[7];
	pn[1] = pos[6];
	pn[2] = pos[5];
	pn[3] = pos[4];
	pn[4] = pos[1];
	pn[5] = pos[0];
	pos += 8;

	अगर (ccmp_replay_check(pn, key->rx_pn)) अणु
#अगर_घोषित CONFIG_LIB80211_DEBUG
		net_dbg_ratelimited("CCMP: replay detected: STA=%pM previous PN %02x%02x%02x%02x%02x%02x received PN %02x%02x%02x%02x%02x%02x\n",
				    hdr->addr2,
				    key->rx_pn[0], key->rx_pn[1], key->rx_pn[2],
				    key->rx_pn[3], key->rx_pn[4], key->rx_pn[5],
				    pn[0], pn[1], pn[2], pn[3], pn[4], pn[5]);
#पूर्ण_अगर
		key->करोt11RSNAStatsCCMPReplays++;
		वापस -4;
	पूर्ण

	req = aead_request_alloc(key->tfm, GFP_ATOMIC);
	अगर (!req)
		वापस -ENOMEM;

	aad_len = ccmp_init_iv_and_aad(hdr, pn, iv, aad);

	sg_init_table(sg, 2);
	sg_set_buf(&sg[0], aad, aad_len);
	sg_set_buf(&sg[1], pos, data_len);

	aead_request_set_callback(req, 0, शून्य, शून्य);
	aead_request_set_ad(req, aad_len);
	aead_request_set_crypt(req, sg, sg, data_len, iv);

	ret = crypto_aead_decrypt(req);
	aead_request_मुक्त(req);

	अगर (ret) अणु
		net_dbg_ratelimited("CCMP: decrypt failed: STA=%pM (%d)\n",
				    hdr->addr2, ret);
		key->करोt11RSNAStatsCCMPDecryptErrors++;
		वापस -5;
	पूर्ण

	स_नकल(key->rx_pn, pn, CCMP_PN_LEN);

	/* Remove hdr and MIC */
	स_हटाओ(skb->data + CCMP_HDR_LEN, skb->data, hdr_len);
	skb_pull(skb, CCMP_HDR_LEN);
	skb_trim(skb, skb->len - CCMP_MIC_LEN);

	वापस keyidx;
पूर्ण

अटल पूर्णांक lib80211_ccmp_set_key(व्योम *key, पूर्णांक len, u8 * seq, व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *data = priv;
	पूर्णांक keyidx;
	काष्ठा crypto_aead *tfm = data->tfm;

	keyidx = data->key_idx;
	स_रखो(data, 0, माप(*data));
	data->key_idx = keyidx;
	data->tfm = tfm;
	अगर (len == CCMP_TK_LEN) अणु
		स_नकल(data->key, key, CCMP_TK_LEN);
		data->key_set = 1;
		अगर (seq) अणु
			data->rx_pn[0] = seq[5];
			data->rx_pn[1] = seq[4];
			data->rx_pn[2] = seq[3];
			data->rx_pn[3] = seq[2];
			data->rx_pn[4] = seq[1];
			data->rx_pn[5] = seq[0];
		पूर्ण
		अगर (crypto_aead_setauthsize(data->tfm, CCMP_MIC_LEN) ||
		    crypto_aead_setkey(data->tfm, data->key, CCMP_TK_LEN))
			वापस -1;
	पूर्ण अन्यथा अगर (len == 0)
		data->key_set = 0;
	अन्यथा
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक lib80211_ccmp_get_key(व्योम *key, पूर्णांक len, u8 * seq, व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *data = priv;

	अगर (len < CCMP_TK_LEN)
		वापस -1;

	अगर (!data->key_set)
		वापस 0;
	स_नकल(key, data->key, CCMP_TK_LEN);

	अगर (seq) अणु
		seq[0] = data->tx_pn[5];
		seq[1] = data->tx_pn[4];
		seq[2] = data->tx_pn[3];
		seq[3] = data->tx_pn[2];
		seq[4] = data->tx_pn[1];
		seq[5] = data->tx_pn[0];
	पूर्ण

	वापस CCMP_TK_LEN;
पूर्ण

अटल व्योम lib80211_ccmp_prपूर्णांक_stats(काष्ठा seq_file *m, व्योम *priv)
अणु
	काष्ठा lib80211_ccmp_data *ccmp = priv;

	seq_म_लिखो(m,
		   "key[%d] alg=CCMP key_set=%d "
		   "tx_pn=%02x%02x%02x%02x%02x%02x "
		   "rx_pn=%02x%02x%02x%02x%02x%02x "
		   "format_errors=%d replays=%d decrypt_errors=%d\n",
		   ccmp->key_idx, ccmp->key_set,
		   ccmp->tx_pn[0], ccmp->tx_pn[1], ccmp->tx_pn[2],
		   ccmp->tx_pn[3], ccmp->tx_pn[4], ccmp->tx_pn[5],
		   ccmp->rx_pn[0], ccmp->rx_pn[1], ccmp->rx_pn[2],
		   ccmp->rx_pn[3], ccmp->rx_pn[4], ccmp->rx_pn[5],
		   ccmp->करोt11RSNAStatsCCMPFormatErrors,
		   ccmp->करोt11RSNAStatsCCMPReplays,
		   ccmp->करोt11RSNAStatsCCMPDecryptErrors);
पूर्ण

अटल काष्ठा lib80211_crypto_ops lib80211_crypt_ccmp = अणु
	.name = "CCMP",
	.init = lib80211_ccmp_init,
	.deinit = lib80211_ccmp_deinit,
	.encrypt_mpdu = lib80211_ccmp_encrypt,
	.decrypt_mpdu = lib80211_ccmp_decrypt,
	.encrypt_msdu = शून्य,
	.decrypt_msdu = शून्य,
	.set_key = lib80211_ccmp_set_key,
	.get_key = lib80211_ccmp_get_key,
	.prपूर्णांक_stats = lib80211_ccmp_prपूर्णांक_stats,
	.extra_mpdu_prefix_len = CCMP_HDR_LEN,
	.extra_mpdu_postfix_len = CCMP_MIC_LEN,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init lib80211_crypto_ccmp_init(व्योम)
अणु
	वापस lib80211_रेजिस्टर_crypto_ops(&lib80211_crypt_ccmp);
पूर्ण

अटल व्योम __निकास lib80211_crypto_ccmp_निकास(व्योम)
अणु
	lib80211_unरेजिस्टर_crypto_ops(&lib80211_crypt_ccmp);
पूर्ण

module_init(lib80211_crypto_ccmp_init);
module_निकास(lib80211_crypto_ccmp_निकास);
