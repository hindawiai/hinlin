<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Driver क्रम KeyStream wireless LAN cards.
 *
 *   Copyright (C) 2005-2008 KeyStream Corp.
 *   Copyright (C) 2009 Renesas Technology Corp.
 */

#समावेश <crypto/hash.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/iw_handler.h>
#समावेश <uapi/linux/llc.h>
#समावेश "eap_packet.h"
#समावेश "ks_wlan.h"
#समावेश "ks_hostif.h"

#घोषणा MICHAEL_MIC_KEY_LEN 8
#घोषणा MICHAEL_MIC_LEN     8

अटल अंतरभूत व्योम inc_smeqhead(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->sme_i.qhead = (priv->sme_i.qhead + 1) % SME_EVENT_BUFF_SIZE;
पूर्ण

अटल अंतरभूत व्योम inc_smeqtail(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->sme_i.qtail = (priv->sme_i.qtail + 1) % SME_EVENT_BUFF_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cnt_smeqbody(काष्ठा ks_wlan_निजी *priv)
अणु
	वापस CIRC_CNT_TO_END(priv->sme_i.qhead, priv->sme_i.qtail,
			       SME_EVENT_BUFF_SIZE);
पूर्ण

अटल अंतरभूत u8 get_byte(काष्ठा ks_wlan_निजी *priv)
अणु
	u8 data;

	data = *priv->rxp++;
	/* length check in advance ! */
	--(priv->rx_size);
	वापस data;
पूर्ण

अटल अंतरभूत u16 get_word(काष्ठा ks_wlan_निजी *priv)
अणु
	u16 data;

	data = (get_byte(priv) & 0xff);
	data |= ((get_byte(priv) << 8) & 0xff00);
	वापस data;
पूर्ण

अटल अंतरभूत u32 get_dword(काष्ठा ks_wlan_निजी *priv)
अणु
	u32 data;

	data = (get_byte(priv) & 0xff);
	data |= ((get_byte(priv) << 8) & 0x0000ff00);
	data |= ((get_byte(priv) << 16) & 0x00ff0000);
	data |= ((get_byte(priv) << 24) & 0xff000000);
	वापस data;
पूर्ण

अटल व्योम ks_wlan_hw_wakeup_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ks_wlan_निजी *priv;
	पूर्णांक ps_status;
	दीर्घ समय_left;

	priv = container_of(work, काष्ठा ks_wlan_निजी, wakeup_work);
	ps_status = atomic_पढ़ो(&priv->psstatus.status);

	अगर (ps_status == PS_SNOOZE) अणु
		ks_wlan_hw_wakeup_request(priv);
		समय_left = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&priv->psstatus.wakeup_रुको,
				msecs_to_jअगरfies(20));
		अगर (समय_left <= 0) अणु
			netdev_dbg(priv->net_dev, "wake up timeout or interrupted !!!\n");
			schedule_work(&priv->wakeup_work);
			वापस;
		पूर्ण
	पूर्ण

	/* घातer save */
	अगर (atomic_पढ़ो(&priv->sme_task.count) > 0)
		tasklet_enable(&priv->sme_task);
पूर्ण

अटल व्योम ks_wlan_करो_घातer_save(काष्ठा ks_wlan_निजी *priv)
अणु
	अगर (is_connect_status(priv->connect_status))
		hostअगर_sme_enqueue(priv, SME_POW_MNGMT_REQUEST);
	अन्यथा
		priv->dev_state = DEVICE_STATE_READY;
पूर्ण

अटल
पूर्णांक get_current_ap(काष्ठा ks_wlan_निजी *priv, काष्ठा link_ap_info *ap_info)
अणु
	काष्ठा local_ap *ap;
	जोड़ iwreq_data wrqu;
	काष्ठा net_device *netdev = priv->net_dev;
	u8 size;

	ap = &priv->current_ap;

	अगर (is_disconnect_status(priv->connect_status)) अणु
		स_रखो(ap, 0, माप(काष्ठा local_ap));
		वापस -EPERM;
	पूर्ण

	ether_addr_copy(ap->bssid, ap_info->bssid);
	स_नकल(ap->ssid.body, priv->reg.ssid.body,
	       priv->reg.ssid.size);
	ap->ssid.size = priv->reg.ssid.size;
	स_नकल(ap->rate_set.body, ap_info->rate_set.body,
	       ap_info->rate_set.size);
	ap->rate_set.size = ap_info->rate_set.size;
	अगर (ap_info->ext_rate_set.size != 0) अणु
		स_नकल(&ap->rate_set.body[ap->rate_set.size],
		       ap_info->ext_rate_set.body,
		       ap_info->ext_rate_set.size);
		ap->rate_set.size += ap_info->ext_rate_set.size;
	पूर्ण
	ap->channel = ap_info->ds_parameter.channel;
	ap->rssi = ap_info->rssi;
	ap->sq = ap_info->sq;
	ap->noise = ap_info->noise;
	ap->capability = le16_to_cpu(ap_info->capability);
	size = (ap_info->rsn.size <= RSN_IE_BODY_MAX) ?
		ap_info->rsn.size : RSN_IE_BODY_MAX;
	अगर ((ap_info->rsn_mode & RSN_MODE_WPA2) &&
	    (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2)) अणु
		ap->rsn_ie.id = RSN_INFO_ELEM_ID;
		ap->rsn_ie.size = size;
		स_नकल(ap->rsn_ie.body, ap_info->rsn.body, size);
	पूर्ण अन्यथा अगर ((ap_info->rsn_mode & RSN_MODE_WPA) &&
		   (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA)) अणु
		ap->wpa_ie.id = WPA_INFO_ELEM_ID;
		ap->wpa_ie.size = size;
		स_नकल(ap->wpa_ie.body, ap_info->rsn.body, size);
	पूर्ण अन्यथा अणु
		ap->rsn_ie.id = 0;
		ap->rsn_ie.size = 0;
		ap->wpa_ie.id = 0;
		ap->wpa_ie.size = 0;
	पूर्ण

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	अगर (is_connect_status(priv->connect_status)) अणु
		ether_addr_copy(wrqu.ap_addr.sa_data, priv->current_ap.bssid);
		netdev_dbg(priv->net_dev,
			   "IWEVENT: connect bssid=%pM\n",
			   wrqu.ap_addr.sa_data);
		wireless_send_event(netdev, SIOCGIWAP, &wrqu, शून्य);
	पूर्ण
	netdev_dbg(priv->net_dev, "Link AP\n"
		   "- bssid=%pM\n"
		   "- essid=%s\n"
		   "- rate_set=%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X\n"
		   "- channel=%d\n"
		   "- rssi=%d\n"
		   "- sq=%d\n"
		   "- capability=%04X\n"
		   "- rsn.mode=%d\n"
		   "- rsn.size=%d\n"
		   "- ext_rate_set_size=%d\n"
		   "- rate_set_size=%d\n",
		   ap->bssid,
		   &ap->ssid.body[0],
		   ap->rate_set.body[0], ap->rate_set.body[1],
		   ap->rate_set.body[2], ap->rate_set.body[3],
		   ap->rate_set.body[4], ap->rate_set.body[5],
		   ap->rate_set.body[6], ap->rate_set.body[7],
		   ap->channel, ap->rssi, ap->sq, ap->capability,
		   ap_info->rsn_mode, ap_info->rsn.size,
		   ap_info->ext_rate_set.size, ap_info->rate_set.size);

	वापस 0;
पूर्ण

अटल u8 पढ़ो_ie(अचिन्हित अक्षर *bp, u8 max, u8 *body)
अणु
	u8 size = (*(bp + 1) <= max) ? *(bp + 1) : max;

	स_नकल(body, bp + 2, size);
	वापस size;
पूर्ण

अटल पूर्णांक
michael_mic(u8 *key, u8 *data, अचिन्हित पूर्णांक len, u8 priority, u8 *result)
अणु
	u8 pad_data[4] = अणु priority, 0, 0, 0 पूर्ण;
	काष्ठा crypto_shash *tfm = शून्य;
	काष्ठा shash_desc *desc = शून्य;
	पूर्णांक ret;

	tfm = crypto_alloc_shash("michael_mic", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		ret = PTR_ERR(tfm);
		जाओ err;
	पूर्ण

	ret = crypto_shash_setkey(tfm, key, MICHAEL_MIC_KEY_LEN);
	अगर (ret < 0)
		जाओ err_मुक्त_tfm;

	desc = kदो_स्मृति(माप(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
	अगर (!desc) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_tfm;
	पूर्ण

	desc->tfm = tfm;

	ret = crypto_shash_init(desc);
	अगर (ret < 0)
		जाओ err_मुक्त_desc;

	// Compute the MIC value
	/*
	 * IEEE802.11i  page 47
	 * Figure 43g TKIP MIC processing क्रमmat
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 * |6 |6 |1       |3 |M   |1 |1 |1 |1 |1 |1 |1 |1 | Octet
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 * |DA|SA|Priority|0 |Data|M0|M1|M2|M3|M4|M5|M6|M7|
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 */

	ret = crypto_shash_update(desc, data, 12);
	अगर (ret < 0)
		जाओ err_मुक्त_desc;

	ret = crypto_shash_update(desc, pad_data, 4);
	अगर (ret < 0)
		जाओ err_मुक्त_desc;

	ret = crypto_shash_finup(desc, data + 12, len - 12, result);

err_मुक्त_desc:
	kमुक्त_sensitive(desc);

err_मुक्त_tfm:
	crypto_मुक्त_shash(tfm);

err:
	वापस ret;
पूर्ण

अटल
पूर्णांक get_ap_inक्रमmation(काष्ठा ks_wlan_निजी *priv, काष्ठा ap_info *ap_info,
		       काष्ठा local_ap *ap)
अणु
	अचिन्हित अक्षर *bp;
	पूर्णांक bsize, offset;

	स_रखो(ap, 0, माप(काष्ठा local_ap));

	ether_addr_copy(ap->bssid, ap_info->bssid);
	ap->rssi = ap_info->rssi;
	ap->sq = ap_info->sq;
	ap->noise = ap_info->noise;
	ap->capability = le16_to_cpu(ap_info->capability);
	ap->channel = ap_info->ch_info;

	bp = ap_info->body;
	bsize = le16_to_cpu(ap_info->body_size);
	offset = 0;

	जबतक (bsize > offset) अणु
		चयन (*bp) अणु /* Inक्रमmation Element ID */
		हाल WLAN_EID_SSID:
			ap->ssid.size = पढ़ो_ie(bp, IEEE80211_MAX_SSID_LEN,
						ap->ssid.body);
			अवरोध;
		हाल WLAN_EID_SUPP_RATES:
		हाल WLAN_EID_EXT_SUPP_RATES:
			अगर ((*(bp + 1) + ap->rate_set.size) <=
			    RATE_SET_MAX_SIZE) अणु
				स_नकल(&ap->rate_set.body[ap->rate_set.size],
				       bp + 2, *(bp + 1));
				ap->rate_set.size += *(bp + 1);
			पूर्ण अन्यथा अणु
				स_नकल(&ap->rate_set.body[ap->rate_set.size],
				       bp + 2,
				       RATE_SET_MAX_SIZE - ap->rate_set.size);
				ap->rate_set.size +=
				    (RATE_SET_MAX_SIZE - ap->rate_set.size);
			पूर्ण
			अवरोध;
		हाल WLAN_EID_RSN:
			ap->rsn_ie.id = *bp;
			ap->rsn_ie.size = पढ़ो_ie(bp, RSN_IE_BODY_MAX,
						  ap->rsn_ie.body);
			अवरोध;
		हाल WLAN_EID_VENDOR_SPECIFIC: /* WPA */
			/* WPA OUI check */
			अगर (स_भेद(bp + 2, CIPHER_ID_WPA_WEP40, 4) == 0) अणु
				ap->wpa_ie.id = *bp;
				ap->wpa_ie.size = पढ़ो_ie(bp, RSN_IE_BODY_MAX,
							  ap->wpa_ie.body);
			पूर्ण
			अवरोध;
		हाल WLAN_EID_DS_PARAMS:
		हाल WLAN_EID_FH_PARAMS:
		हाल WLAN_EID_CF_PARAMS:
		हाल WLAN_EID_TIM:
		हाल WLAN_EID_IBSS_PARAMS:
		हाल WLAN_EID_COUNTRY:
		हाल WLAN_EID_ERP_INFO:
			अवरोध;
		शेष:
			netdev_err(priv->net_dev,
				   "unknown Element ID=%d\n", *bp);
			अवरोध;
		पूर्ण

		offset += 2;	/* id & size field */
		offset += *(bp + 1);	/* +size offset */
		bp += (*(bp + 1) + 2);	/* poपूर्णांकer update */
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक hostअगर_data_indication_wpa(काष्ठा ks_wlan_निजी *priv,
			       अचिन्हित लघु auth_type)
अणु
	काष्ठा ether_hdr *eth_hdr;
	अचिन्हित लघु eth_proto;
	अचिन्हित अक्षर recv_mic[MICHAEL_MIC_LEN];
	अक्षर buf[128];
	अचिन्हित दीर्घ now;
	काष्ठा mic_failure *mic_failure;
	u8 mic[MICHAEL_MIC_LEN];
	जोड़ iwreq_data wrqu;
	अचिन्हित पूर्णांक key_index = auth_type - 1;
	काष्ठा wpa_key *key = &priv->wpa.key[key_index];

	eth_hdr = (काष्ठा ether_hdr *)(priv->rxp);
	eth_proto = ntohs(eth_hdr->h_proto);

	अगर (eth_hdr->h_dest_snap != eth_hdr->h_source_snap) अणु
		netdev_err(priv->net_dev, "invalid data format\n");
		priv->nstats.rx_errors++;
		वापस -EINVAL;
	पूर्ण
	अगर (((auth_type == TYPE_PMK1 &&
	      priv->wpa.pairwise_suite == IW_AUTH_CIPHER_TKIP) ||
	     (auth_type == TYPE_GMK1 &&
	      priv->wpa.group_suite == IW_AUTH_CIPHER_TKIP) ||
	     (auth_type == TYPE_GMK2 &&
	      priv->wpa.group_suite == IW_AUTH_CIPHER_TKIP)) &&
	    key->key_len) अणु
		पूर्णांक ret;

		netdev_dbg(priv->net_dev, "TKIP: protocol=%04X: size=%u\n",
			   eth_proto, priv->rx_size);
		/* MIC save */
		स_नकल(&recv_mic[0],
		       (priv->rxp) + ((priv->rx_size) - माप(recv_mic)),
		       माप(recv_mic));
		priv->rx_size = priv->rx_size - माप(recv_mic);

		ret = michael_mic(key->rx_mic_key, priv->rxp, priv->rx_size,
				  0, mic);
		अगर (ret < 0)
			वापस ret;
		अगर (स_भेद(mic, recv_mic, माप(mic)) != 0) अणु
			now = jअगरfies;
			mic_failure = &priv->wpa.mic_failure;
			/* MIC FAILURE */
			अगर (mic_failure->last_failure_समय &&
			    (now - mic_failure->last_failure_समय) / HZ >= 60) अणु
				mic_failure->failure = 0;
			पूर्ण
			netdev_err(priv->net_dev, "MIC FAILURE\n");
			अगर (mic_failure->failure == 0) अणु
				mic_failure->failure = 1;
				mic_failure->counter = 0;
			पूर्ण अन्यथा अगर (mic_failure->failure == 1) अणु
				mic_failure->failure = 2;
				mic_failure->counter =
					(u16)((now - mic_failure->last_failure_समय) / HZ);
				/*  range 1-60 */
				अगर (!mic_failure->counter)
					mic_failure->counter = 1;
			पूर्ण
			priv->wpa.mic_failure.last_failure_समय = now;

			/*  needed parameters: count, keyid, key type, TSC */
			प्र_लिखो(buf,
				"MLME-MICHAELMICFAILURE.indication(keyid=%d %scast addr=%pM)",
				key_index,
				eth_hdr->h_dest[0] & 0x01 ? "broad" : "uni",
				eth_hdr->h_source);
			स_रखो(&wrqu, 0, माप(wrqu));
			wrqu.data.length = म_माप(buf);
			wireless_send_event(priv->net_dev, IWEVCUSTOM, &wrqu,
					    buf);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल
व्योम hostअगर_data_indication(काष्ठा ks_wlan_निजी *priv)
अणु
	अचिन्हित पूर्णांक rx_ind_size;	/* indicate data size */
	काष्ठा sk_buff *skb;
	u16 auth_type;
	अचिन्हित अक्षर temp[256];
	काष्ठा ether_hdr *eth_hdr;
	काष्ठा ieee802_1x_hdr *aa1x_hdr;
	माप_प्रकार size;
	पूर्णांक ret;

	/* min length check */
	अगर (priv->rx_size <= ETH_HLEN) अणु
		priv->nstats.rx_errors++;
		वापस;
	पूर्ण

	auth_type = get_word(priv);	/* AuthType */
	get_word(priv);	/* Reserve Area */

	eth_hdr = (काष्ठा ether_hdr *)(priv->rxp);

	/* source address check */
	अगर (ether_addr_equal(&priv->eth_addr[0], eth_hdr->h_source)) अणु
		netdev_err(priv->net_dev, "invalid : source is own mac address !!\n");
		netdev_err(priv->net_dev, "eth_hdrernet->h_dest=%pM\n", eth_hdr->h_source);
		priv->nstats.rx_errors++;
		वापस;
	पूर्ण

	/*  क्रम WPA */
	अगर (auth_type != TYPE_DATA && priv->wpa.rsn_enabled) अणु
		ret = hostअगर_data_indication_wpa(priv, auth_type);
		अगर (ret)
			वापस;
	पूर्ण

	अगर ((priv->connect_status & FORCE_DISCONNECT) ||
	    priv->wpa.mic_failure.failure == 2) अणु
		वापस;
	पूर्ण

	/* check 13th byte at rx data */
	चयन (*(priv->rxp + 12)) अणु
	हाल LLC_SAP_SNAP:
		rx_ind_size = priv->rx_size - 6;
		skb = dev_alloc_skb(rx_ind_size);
		अगर (!skb) अणु
			priv->nstats.rx_dropped++;
			वापस;
		पूर्ण
		netdev_dbg(priv->net_dev, "SNAP, rx_ind_size = %d\n",
			   rx_ind_size);

		size = ETH_ALEN * 2;
		skb_put_data(skb, priv->rxp, size);

		/* (SNAP+UI..) skip */

		size = rx_ind_size - (ETH_ALEN * 2);
		skb_put_data(skb, &eth_hdr->h_proto, size);

		aa1x_hdr = (काष्ठा ieee802_1x_hdr *)(priv->rxp + ETHER_HDR_SIZE);
		अवरोध;
	हाल LLC_SAP_NETBEUI:
		rx_ind_size = (priv->rx_size + 2);
		skb = dev_alloc_skb(rx_ind_size);
		अगर (!skb) अणु
			priv->nstats.rx_dropped++;
			वापस;
		पूर्ण
		netdev_dbg(priv->net_dev, "NETBEUI/NetBIOS rx_ind_size=%d\n",
			   rx_ind_size);

		/* 8802/FDDI MAC copy */
		skb_put_data(skb, priv->rxp, 12);

		/* NETBEUI size add */
		temp[0] = (((rx_ind_size - 12) >> 8) & 0xff);
		temp[1] = ((rx_ind_size - 12) & 0xff);
		skb_put_data(skb, temp, 2);

		/* copy after Type */
		skb_put_data(skb, priv->rxp + 12, rx_ind_size - 14);

		aa1x_hdr = (काष्ठा ieee802_1x_hdr *)(priv->rxp + 14);
		अवरोध;
	शेष:	/* other rx data */
		netdev_err(priv->net_dev, "invalid data format\n");
		priv->nstats.rx_errors++;
		वापस;
	पूर्ण

	अगर (aa1x_hdr->type == IEEE802_1X_TYPE_EAPOL_KEY &&
	    priv->wpa.rsn_enabled)
		atomic_set(&priv->psstatus.snooze_guard, 1);

	/* rx indication */
	skb->dev = priv->net_dev;
	skb->protocol = eth_type_trans(skb, skb->dev);
	priv->nstats.rx_packets++;
	priv->nstats.rx_bytes += rx_ind_size;
	netअगर_rx(skb);
पूर्ण

अटल
व्योम hostअगर_mib_get_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	u32 mib_status;
	u32 mib_attribute;
	u16 mib_val_size;
	u16 mib_val_type;

	mib_status = get_dword(priv);
	mib_attribute = get_dword(priv);
	mib_val_size = get_word(priv);
	mib_val_type = get_word(priv);

	अगर (mib_status) अणु
		netdev_err(priv->net_dev, "attribute=%08X, status=%08X\n",
			   mib_attribute, mib_status);
		वापस;
	पूर्ण

	चयन (mib_attribute) अणु
	हाल DOT11_MAC_ADDRESS:
		hostअगर_sme_enqueue(priv, SME_GET_MAC_ADDRESS);
		ether_addr_copy(priv->eth_addr, priv->rxp);
		priv->mac_address_valid = true;
		ether_addr_copy(dev->dev_addr, priv->eth_addr);
		netdev_info(dev, "MAC ADDRESS = %pM\n", priv->eth_addr);
		अवरोध;
	हाल DOT11_PRODUCT_VERSION:
		priv->version_size = priv->rx_size;
		स_नकल(priv->firmware_version, priv->rxp, priv->rx_size);
		priv->firmware_version[priv->rx_size] = '\0';
		netdev_info(dev, "firmware ver. = %s\n",
			    priv->firmware_version);
		hostअगर_sme_enqueue(priv, SME_GET_PRODUCT_VERSION);
		/* wake_up_पूर्णांकerruptible_all(&priv->confirm_रुको); */
		complete(&priv->confirm_रुको);
		अवरोध;
	हाल LOCAL_GAIN:
		स_नकल(&priv->gain, priv->rxp, माप(priv->gain));
		netdev_dbg(priv->net_dev, "tx_mode=%d, rx_mode=%d, tx_gain=%d, rx_gain=%d\n",
			   priv->gain.tx_mode, priv->gain.rx_mode,
			   priv->gain.tx_gain, priv->gain.rx_gain);
		अवरोध;
	हाल LOCAL_EEPROM_SUM:
		स_नकल(&priv->eeprom_sum, priv->rxp, माप(priv->eeprom_sum));
		अगर (priv->eeprom_sum.type != 0 &&
		    priv->eeprom_sum.type != 1) अणु
			netdev_err(dev, "LOCAL_EEPROM_SUM error!\n");
			वापस;
		पूर्ण
		priv->eeprom_checksum = (priv->eeprom_sum.type == 0) ?
					 EEPROM_CHECKSUM_NONE :
					 (priv->eeprom_sum.result == 0) ?
					 EEPROM_NG : EEPROM_OK;
		अवरोध;
	शेष:
		netdev_err(priv->net_dev, "mib_attribute=%08x\n",
			   (अचिन्हित पूर्णांक)mib_attribute);
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_mib_set_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	u32 mib_status;
	u32 mib_attribute;

	mib_status = get_dword(priv);
	mib_attribute = get_dword(priv);

	अगर (mib_status) अणु
		/* in हाल of error */
		netdev_err(priv->net_dev, "error :: attribute=%08X, status=%08X\n",
			   mib_attribute, mib_status);
	पूर्ण

	चयन (mib_attribute) अणु
	हाल DOT11_RTS_THRESHOLD:
		hostअगर_sme_enqueue(priv, SME_RTS_THRESHOLD_CONFIRM);
		अवरोध;
	हाल DOT11_FRAGMENTATION_THRESHOLD:
		hostअगर_sme_enqueue(priv, SME_FRAGMENTATION_THRESHOLD_CONFIRM);
		अवरोध;
	हाल DOT11_WEP_DEFAULT_KEY_ID:
		अगर (!priv->wpa.wpa_enabled)
			hostअगर_sme_enqueue(priv, SME_WEP_INDEX_CONFIRM);
		अवरोध;
	हाल DOT11_WEP_DEFAULT_KEY_VALUE1:
		अगर (priv->wpa.rsn_enabled)
			hostअगर_sme_enqueue(priv, SME_SET_PMK_TSC);
		अन्यथा
			hostअगर_sme_enqueue(priv, SME_WEP_KEY1_CONFIRM);
		अवरोध;
	हाल DOT11_WEP_DEFAULT_KEY_VALUE2:
		अगर (priv->wpa.rsn_enabled)
			hostअगर_sme_enqueue(priv, SME_SET_GMK1_TSC);
		अन्यथा
			hostअगर_sme_enqueue(priv, SME_WEP_KEY2_CONFIRM);
		अवरोध;
	हाल DOT11_WEP_DEFAULT_KEY_VALUE3:
		अगर (priv->wpa.rsn_enabled)
			hostअगर_sme_enqueue(priv, SME_SET_GMK2_TSC);
		अन्यथा
			hostअगर_sme_enqueue(priv, SME_WEP_KEY3_CONFIRM);
		अवरोध;
	हाल DOT11_WEP_DEFAULT_KEY_VALUE4:
		अगर (!priv->wpa.rsn_enabled)
			hostअगर_sme_enqueue(priv, SME_WEP_KEY4_CONFIRM);
		अवरोध;
	हाल DOT11_PRIVACY_INVOKED:
		अगर (!priv->wpa.rsn_enabled)
			hostअगर_sme_enqueue(priv, SME_WEP_FLAG_CONFIRM);
		अवरोध;
	हाल DOT11_RSN_ENABLED:
		hostअगर_sme_enqueue(priv, SME_RSN_ENABLED_CONFIRM);
		अवरोध;
	हाल LOCAL_RSN_MODE:
		hostअगर_sme_enqueue(priv, SME_RSN_MODE_CONFIRM);
		अवरोध;
	हाल LOCAL_MULTICAST_ADDRESS:
		hostअगर_sme_enqueue(priv, SME_MULTICAST_REQUEST);
		अवरोध;
	हाल LOCAL_MULTICAST_FILTER:
		hostअगर_sme_enqueue(priv, SME_MULTICAST_CONFIRM);
		अवरोध;
	हाल LOCAL_CURRENTADDRESS:
		priv->mac_address_valid = true;
		अवरोध;
	हाल DOT11_RSN_CONFIG_MULTICAST_CIPHER:
		hostअगर_sme_enqueue(priv, SME_RSN_MCAST_CONFIRM);
		अवरोध;
	हाल DOT11_RSN_CONFIG_UNICAST_CIPHER:
		hostअगर_sme_enqueue(priv, SME_RSN_UCAST_CONFIRM);
		अवरोध;
	हाल DOT11_RSN_CONFIG_AUTH_SUITE:
		hostअगर_sme_enqueue(priv, SME_RSN_AUTH_CONFIRM);
		अवरोध;
	हाल DOT11_GMK1_TSC:
		अगर (atomic_पढ़ो(&priv->psstatus.snooze_guard))
			atomic_set(&priv->psstatus.snooze_guard, 0);
		अवरोध;
	हाल DOT11_GMK2_TSC:
		अगर (atomic_पढ़ो(&priv->psstatus.snooze_guard))
			atomic_set(&priv->psstatus.snooze_guard, 0);
		अवरोध;
	हाल DOT11_PMK_TSC:
	हाल LOCAL_PMK:
	हाल LOCAL_GAIN:
	हाल LOCAL_WPS_ENABLE:
	हाल LOCAL_WPS_PROBE_REQ:
	हाल LOCAL_REGION:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_घातer_mgmt_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	अगर (priv->reg.घातer_mgmt > POWER_MGMT_ACTIVE &&
	    priv->reg.operation_mode == MODE_INFRASTRUCTURE) अणु
		atomic_set(&priv->psstatus.confirm_रुको, 0);
		priv->dev_state = DEVICE_STATE_SLEEP;
		ks_wlan_hw_घातer_save(priv);
	पूर्ण अन्यथा अणु
		priv->dev_state = DEVICE_STATE_READY;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_sleep_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	atomic_set(&priv->sleepstatus.करोze_request, 1);
	queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
पूर्ण

अटल
व्योम hostअगर_start_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	जोड़ iwreq_data wrqu;

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	अगर (is_connect_status(priv->connect_status)) अणु
		eth_zero_addr(wrqu.ap_addr.sa_data);
		wireless_send_event(priv->net_dev, SIOCGIWAP, &wrqu, शून्य);
	पूर्ण
	netdev_dbg(priv->net_dev, " scan_ind_count=%d\n", priv->scan_ind_count);
	hostअगर_sme_enqueue(priv, SME_START_CONFIRM);
पूर्ण

अटल
व्योम hostअगर_connect_indication(काष्ठा ks_wlan_निजी *priv)
अणु
	u16 connect_code;
	अचिन्हित पूर्णांक पंचांगp = 0;
	अचिन्हित पूर्णांक old_status = priv->connect_status;
	काष्ठा net_device *netdev = priv->net_dev;
	जोड़ iwreq_data wrqu0;

	connect_code = get_word(priv);

	चयन (connect_code) अणु
	हाल RESULT_CONNECT:
		अगर (!(priv->connect_status & FORCE_DISCONNECT))
			netअगर_carrier_on(netdev);
		पंचांगp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = पंचांगp + CONNECT_STATUS;
		अवरोध;
	हाल RESULT_DISCONNECT:
		netअगर_carrier_off(netdev);
		पंचांगp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = पंचांगp + DISCONNECT_STATUS;
		अवरोध;
	शेष:
		netdev_dbg(priv->net_dev, "unknown connect_code=%d :: scan_ind_count=%d\n",
			   connect_code, priv->scan_ind_count);
		netअगर_carrier_off(netdev);
		पंचांगp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = पंचांगp + DISCONNECT_STATUS;
		अवरोध;
	पूर्ण

	get_current_ap(priv, (काष्ठा link_ap_info *)priv->rxp);
	अगर (is_connect_status(priv->connect_status) &&
	    is_disconnect_status(old_status)) अणु
		/* क्रम घातer save */
		atomic_set(&priv->psstatus.snooze_guard, 0);
		atomic_set(&priv->psstatus.confirm_रुको, 0);
	पूर्ण
	ks_wlan_करो_घातer_save(priv);

	wrqu0.data.length = 0;
	wrqu0.data.flags = 0;
	wrqu0.ap_addr.sa_family = ARPHRD_ETHER;
	अगर (is_disconnect_status(priv->connect_status) &&
	    is_connect_status(old_status)) अणु
		eth_zero_addr(wrqu0.ap_addr.sa_data);
		netdev_dbg(priv->net_dev, "disconnect :: scan_ind_count=%d\n",
			   priv->scan_ind_count);
		wireless_send_event(netdev, SIOCGIWAP, &wrqu0, शून्य);
	पूर्ण
	priv->scan_ind_count = 0;
पूर्ण

अटल
व्योम hostअगर_scan_indication(काष्ठा ks_wlan_निजी *priv)
अणु
	पूर्णांक i;
	काष्ठा ap_info *ap_info;

	netdev_dbg(priv->net_dev,
		   "scan_ind_count = %d\n", priv->scan_ind_count);
	ap_info = (काष्ठा ap_info *)(priv->rxp);

	अगर (priv->scan_ind_count) अणु
		/* bssid check */
		क्रम (i = 0; i < priv->aplist.size; i++) अणु
			u8 *bssid = priv->aplist.ap[i].bssid;

			अगर (ether_addr_equal(ap_info->bssid, bssid))
				जारी;

			अगर (ap_info->frame_type == IEEE80211_STYPE_PROBE_RESP)
				get_ap_inक्रमmation(priv, ap_info,
						   &priv->aplist.ap[i]);
			वापस;
		पूर्ण
	पूर्ण
	priv->scan_ind_count++;
	अगर (priv->scan_ind_count < LOCAL_APLIST_MAX + 1) अणु
		netdev_dbg(priv->net_dev, " scan_ind_count=%d :: aplist.size=%d\n",
			   priv->scan_ind_count, priv->aplist.size);
		get_ap_inक्रमmation(priv, (काष्ठा ap_info *)(priv->rxp),
				   &priv->aplist.ap[priv->scan_ind_count - 1]);
		priv->aplist.size = priv->scan_ind_count;
	पूर्ण अन्यथा अणु
		netdev_dbg(priv->net_dev, " count over :: scan_ind_count=%d\n",
			   priv->scan_ind_count);
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_stop_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	अचिन्हित पूर्णांक पंचांगp = 0;
	अचिन्हित पूर्णांक old_status = priv->connect_status;
	काष्ठा net_device *netdev = priv->net_dev;
	जोड़ iwreq_data wrqu0;

	अगर (priv->dev_state == DEVICE_STATE_SLEEP)
		priv->dev_state = DEVICE_STATE_READY;

	/* disconnect indication */
	अगर (is_connect_status(priv->connect_status)) अणु
		netअगर_carrier_off(netdev);
		पंचांगp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = पंचांगp | DISCONNECT_STATUS;
		netdev_info(netdev, "IWEVENT: disconnect\n");

		wrqu0.data.length = 0;
		wrqu0.data.flags = 0;
		wrqu0.ap_addr.sa_family = ARPHRD_ETHER;
		अगर (is_disconnect_status(priv->connect_status) &&
		    is_connect_status(old_status)) अणु
			eth_zero_addr(wrqu0.ap_addr.sa_data);
			netdev_info(netdev, "IWEVENT: disconnect\n");
			wireless_send_event(netdev, SIOCGIWAP, &wrqu0, शून्य);
		पूर्ण
		priv->scan_ind_count = 0;
	पूर्ण

	hostअगर_sme_enqueue(priv, SME_STOP_CONFIRM);
पूर्ण

अटल
व्योम hostअगर_ps_adhoc_set_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->infra_status = 0;	/* infraकाष्ठाure mode cancel */
	hostअगर_sme_enqueue(priv, SME_MODE_SET_CONFIRM);
पूर्ण

अटल
व्योम hostअगर_infraकाष्ठाure_set_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	u16 result_code;

	result_code = get_word(priv);
	priv->infra_status = 1;	/* infraकाष्ठाure mode set */
	hostअगर_sme_enqueue(priv, SME_MODE_SET_CONFIRM);
पूर्ण

अटल
व्योम hostअगर_adhoc_set_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->infra_status = 1;	/* infraकाष्ठाure mode set */
	hostअगर_sme_enqueue(priv, SME_MODE_SET_CONFIRM);
पूर्ण

अटल
व्योम hostअगर_associate_indication(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा association_request *assoc_req;
	काष्ठा association_response *assoc_resp;
	अचिन्हित अक्षर *pb;
	जोड़ iwreq_data wrqu;
	अक्षर buf[IW_CUSTOM_MAX];
	अक्षर *pbuf = &buf[0];
	पूर्णांक i;

	अटल स्थिर अक्षर associnfo_leader0[] = "ASSOCINFO(ReqIEs=";
	अटल स्थिर अक्षर associnfo_leader1[] = " RespIEs=";

	assoc_req = (काष्ठा association_request *)(priv->rxp);
	assoc_resp = (काष्ठा association_response *)(assoc_req + 1);
	pb = (अचिन्हित अक्षर *)(assoc_resp + 1);

	स_रखो(&wrqu, 0, माप(wrqu));
	स_नकल(pbuf, associnfo_leader0, माप(associnfo_leader0) - 1);
	wrqu.data.length += माप(associnfo_leader0) - 1;
	pbuf += माप(associnfo_leader0) - 1;

	क्रम (i = 0; i < le16_to_cpu(assoc_req->req_ies_size); i++)
		pbuf += प्र_लिखो(pbuf, "%02x", *(pb + i));
	wrqu.data.length += (le16_to_cpu(assoc_req->req_ies_size)) * 2;

	स_नकल(pbuf, associnfo_leader1, माप(associnfo_leader1) - 1);
	wrqu.data.length += माप(associnfo_leader1) - 1;
	pbuf += माप(associnfo_leader1) - 1;

	pb += le16_to_cpu(assoc_req->req_ies_size);
	क्रम (i = 0; i < le16_to_cpu(assoc_resp->resp_ies_size); i++)
		pbuf += प्र_लिखो(pbuf, "%02x", *(pb + i));
	wrqu.data.length += (le16_to_cpu(assoc_resp->resp_ies_size)) * 2;

	pbuf += प्र_लिखो(pbuf, ")");
	wrqu.data.length += 1;

	wireless_send_event(priv->net_dev, IWEVCUSTOM, &wrqu, buf);
पूर्ण

अटल
व्योम hostअगर_bss_scan_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	u32 result_code;
	काष्ठा net_device *dev = priv->net_dev;
	जोड़ iwreq_data wrqu;

	result_code = get_dword(priv);
	netdev_dbg(priv->net_dev, "result=%d :: scan_ind_count=%d\n",
		   result_code, priv->scan_ind_count);

	priv->sme_i.sme_flag &= ~SME_AP_SCAN;
	hostअगर_sme_enqueue(priv, SME_BSS_SCAN_CONFIRM);

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(dev, SIOCGIWSCAN, &wrqu, शून्य);
	priv->scan_ind_count = 0;
पूर्ण

अटल
व्योम hostअगर_phy_inक्रमmation_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा iw_statistics *wstats = &priv->wstats;
	u8 rssi, संकेत, noise;
	u8 link_speed;
	u32 transmitted_frame_count, received_fragment_count;
	u32 failed_count, fcs_error_count;

	rssi = get_byte(priv);
	संकेत = get_byte(priv);
	noise = get_byte(priv);
	link_speed = get_byte(priv);
	transmitted_frame_count = get_dword(priv);
	received_fragment_count = get_dword(priv);
	failed_count = get_dword(priv);
	fcs_error_count = get_dword(priv);

	netdev_dbg(priv->net_dev, "phyinfo confirm rssi=%d signal=%d\n",
		   rssi, संकेत);
	priv->current_rate = (link_speed & RATE_MASK);
	wstats->qual.qual = संकेत;
	wstats->qual.level = 256 - rssi;
	wstats->qual.noise = 0;	/* invalid noise value */
	wstats->qual.updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;

	netdev_dbg(priv->net_dev, "\n    rssi=%u\n"
		   "    signal=%u\n"
		   "    link_speed=%ux500Kbps\n"
		   "    transmitted_frame_count=%u\n"
		   "    received_fragment_count=%u\n"
		   "    failed_count=%u\n"
		   "    fcs_error_count=%u\n",
		   rssi, संकेत, link_speed, transmitted_frame_count,
		   received_fragment_count, failed_count, fcs_error_count);
	/* wake_up_पूर्णांकerruptible_all(&priv->confirm_रुको); */
	complete(&priv->confirm_रुको);
पूर्ण

अटल
व्योम hostअगर_mic_failure_confirm(काष्ठा ks_wlan_निजी *priv)
अणु
	netdev_dbg(priv->net_dev, "mic_failure=%u\n",
		   priv->wpa.mic_failure.failure);
	hostअगर_sme_enqueue(priv, SME_MIC_FAILURE_CONFIRM);
पूर्ण

अटल
व्योम hostअगर_event_check(काष्ठा ks_wlan_निजी *priv)
अणु
	u16 event;

	event = get_word(priv);
	चयन (event) अणु
	हाल HIF_DATA_IND:
		hostअगर_data_indication(priv);
		अवरोध;
	हाल HIF_MIB_GET_CONF:
		hostअगर_mib_get_confirm(priv);
		अवरोध;
	हाल HIF_MIB_SET_CONF:
		hostअगर_mib_set_confirm(priv);
		अवरोध;
	हाल HIF_POWER_MGMT_CONF:
		hostअगर_घातer_mgmt_confirm(priv);
		अवरोध;
	हाल HIF_SLEEP_CONF:
		hostअगर_sleep_confirm(priv);
		अवरोध;
	हाल HIF_START_CONF:
		hostअगर_start_confirm(priv);
		अवरोध;
	हाल HIF_CONNECT_IND:
		hostअगर_connect_indication(priv);
		अवरोध;
	हाल HIF_STOP_CONF:
		hostअगर_stop_confirm(priv);
		अवरोध;
	हाल HIF_PS_ADH_SET_CONF:
		hostअगर_ps_adhoc_set_confirm(priv);
		अवरोध;
	हाल HIF_INFRA_SET_CONF:
	हाल HIF_INFRA_SET2_CONF:
		hostअगर_infraकाष्ठाure_set_confirm(priv);
		अवरोध;
	हाल HIF_ADH_SET_CONF:
	हाल HIF_ADH_SET2_CONF:
		hostअगर_adhoc_set_confirm(priv);
		अवरोध;
	हाल HIF_ASSOC_INFO_IND:
		hostअगर_associate_indication(priv);
		अवरोध;
	हाल HIF_MIC_FAILURE_CONF:
		hostअगर_mic_failure_confirm(priv);
		अवरोध;
	हाल HIF_SCAN_CONF:
		hostअगर_bss_scan_confirm(priv);
		अवरोध;
	हाल HIF_PHY_INFO_CONF:
	हाल HIF_PHY_INFO_IND:
		hostअगर_phy_inक्रमmation_confirm(priv);
		अवरोध;
	हाल HIF_SCAN_IND:
		hostअगर_scan_indication(priv);
		अवरोध;
	हाल HIF_AP_SET_CONF:
	शेष:
		netdev_err(priv->net_dev, "undefined event[%04X]\n", event);
		/* wake_up_all(&priv->confirm_रुको); */
		complete(&priv->confirm_रुको);
		अवरोध;
	पूर्ण

	/* add event to hostt buffer */
	priv->hostt.buff[priv->hostt.qtail] = event;
	priv->hostt.qtail = (priv->hostt.qtail + 1) % SME_EVENT_BUFF_SIZE;
पूर्ण

/* allocate size bytes, set header size and event */
अटल व्योम *hostअगर_generic_request(माप_प्रकार size, पूर्णांक event)
अणु
	काष्ठा hostअगर_hdr *p;

	p = kzalloc(hअगर_align_size(size), GFP_ATOMIC);
	अगर (!p)
		वापस शून्य;

	p->size = cpu_to_le16(size - माप(p->size));
	p->event = cpu_to_le16(event);

	वापस p;
पूर्ण

पूर्णांक hostअगर_data_request(काष्ठा ks_wlan_निजी *priv, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक skb_len = 0;
	अचिन्हित अक्षर *buffer = शून्य;
	अचिन्हित पूर्णांक length = 0;
	काष्ठा hostअगर_data_request *pp;
	अचिन्हित अक्षर *p;
	अचिन्हित लघु eth_proto;
	काष्ठा ether_hdr *eth_hdr;
	अचिन्हित लघु keyinfo = 0;
	काष्ठा ieee802_1x_hdr *aa1x_hdr;
	काष्ठा wpa_eapol_key *eap_key;
	काष्ठा ethhdr *eth;
	माप_प्रकार size;
	पूर्णांक ret;

	skb_len = skb->len;
	अगर (skb_len > ETH_FRAME_LEN) अणु
		netdev_err(priv->net_dev, "bad length skb_len=%d\n", skb_len);
		ret = -EOVERFLOW;
		जाओ err_kमुक्त_skb;
	पूर्ण

	अगर (is_disconnect_status(priv->connect_status) ||
	    (priv->connect_status & FORCE_DISCONNECT) ||
	    priv->wpa.mic_failure.stop) अणु
		अगर (netअगर_queue_stopped(priv->net_dev))
			netअगर_wake_queue(priv->net_dev);

		dev_kमुक्त_skb(skb);

		वापस 0;
	पूर्ण

	/* घातer save wakeup */
	अगर (atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE) अणु
		अगर (!netअगर_queue_stopped(priv->net_dev))
			netअगर_stop_queue(priv->net_dev);
	पूर्ण

	size = माप(*pp) + 6 + skb_len + 8;
	pp = kदो_स्मृति(hअगर_align_size(size), GFP_ATOMIC);
	अगर (!pp) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त_skb;
	पूर्ण

	p = (अचिन्हित अक्षर *)pp->data;

	buffer = skb->data;
	length = skb->len;

	/* skb check */
	eth = (काष्ठा ethhdr *)skb->data;
	अगर (!ether_addr_equal(&priv->eth_addr[0], eth->h_source)) अणु
		netdev_err(priv->net_dev,
			   "Invalid mac address: ethernet->h_source=%pM\n",
			   eth->h_source);
		ret = -ENXIO;
		जाओ err_kमुक्त;
	पूर्ण

	/* dest and src MAC address copy */
	size = ETH_ALEN * 2;
	स_नकल(p, buffer, size);
	p += size;
	buffer += size;
	length -= size;

	/* EtherType/Length check */
	अगर (*(buffer + 1) + (*buffer << 8) > 1500) अणु
		/* ProtocolEAP = *(buffer+1) + (*buffer << 8); */
		/* SAP/CTL/OUI(6 byte) add */
		*p++ = 0xAA;	/* DSAP */
		*p++ = 0xAA;	/* SSAP */
		*p++ = 0x03;	/* CTL */
		*p++ = 0x00;	/* OUI ("000000") */
		*p++ = 0x00;	/* OUI ("000000") */
		*p++ = 0x00;	/* OUI ("000000") */
		skb_len += 6;
	पूर्ण अन्यथा अणु
		/* Length(2 byte) delete */
		buffer += 2;
		length -= 2;
		skb_len -= 2;
	पूर्ण

	/* pp->data copy */
	स_नकल(p, buffer, length);

	p += length;

	/* क्रम WPA */
	eth_hdr = (काष्ठा ether_hdr *)&pp->data[0];
	eth_proto = ntohs(eth_hdr->h_proto);

	/* क्रम MIC FAILURE REPORT check */
	अगर (eth_proto == ETH_P_PAE &&
	    priv->wpa.mic_failure.failure > 0) अणु
		aa1x_hdr = (काष्ठा ieee802_1x_hdr *)(eth_hdr + 1);
		अगर (aa1x_hdr->type == IEEE802_1X_TYPE_EAPOL_KEY) अणु
			eap_key = (काष्ठा wpa_eapol_key *)(aa1x_hdr + 1);
			keyinfo = ntohs(eap_key->key_info);
		पूर्ण
	पूर्ण

	अगर (priv->wpa.rsn_enabled && priv->wpa.key[0].key_len) अणु
		/* no encryption */
		अगर (eth_proto == ETH_P_PAE &&
		    priv->wpa.key[1].key_len == 0 &&
		    priv->wpa.key[2].key_len == 0 &&
		    priv->wpa.key[3].key_len == 0) अणु
			pp->auth_type = cpu_to_le16(TYPE_AUTH);
		पूर्ण अन्यथा अणु
			अगर (priv->wpa.pairwise_suite == IW_AUTH_CIPHER_TKIP) अणु
				u8 mic[MICHAEL_MIC_LEN];

				ret = michael_mic(priv->wpa.key[0].tx_mic_key,
						  &pp->data[0], skb_len,
						  0, mic);
				अगर (ret < 0)
					जाओ err_kमुक्त;

				स_नकल(p, mic, माप(mic));
				length += माप(mic);
				skb_len += माप(mic);
				p += माप(mic);
				pp->auth_type =
				    cpu_to_le16(TYPE_DATA);
			पूर्ण अन्यथा अगर (priv->wpa.pairwise_suite ==
				   IW_AUTH_CIPHER_CCMP) अणु
				pp->auth_type =
				    cpu_to_le16(TYPE_DATA);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (eth_proto == ETH_P_PAE)
			pp->auth_type = cpu_to_le16(TYPE_AUTH);
		अन्यथा
			pp->auth_type = cpu_to_le16(TYPE_DATA);
	पूर्ण

	/* header value set */
	pp->header.size =
	    cpu_to_le16((माप(*pp) - माप(pp->header.size) + skb_len));
	pp->header.event = cpu_to_le16(HIF_DATA_REQ);

	/* tx request */
	ret = ks_wlan_hw_tx(priv, pp, hअगर_align_size(माप(*pp) + skb_len),
			    send_packet_complete, skb);

	/* MIC FAILURE REPORT check */
	अगर (eth_proto == ETH_P_PAE &&
	    priv->wpa.mic_failure.failure > 0) अणु
		अगर (keyinfo & WPA_KEY_INFO_ERROR &&
		    keyinfo & WPA_KEY_INFO_REQUEST) अणु
			netdev_err(priv->net_dev,
				   "MIC ERROR Report SET : %04X\n", keyinfo);
			hostअगर_sme_enqueue(priv, SME_MIC_FAILURE_REQUEST);
		पूर्ण
		अगर (priv->wpa.mic_failure.failure == 2)
			priv->wpa.mic_failure.stop = 1;
	पूर्ण

	वापस ret;

err_kमुक्त:
	kमुक्त(pp);
err_kमुक्त_skb:
	dev_kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ps_confirm_रुको_inc(काष्ठा ks_wlan_निजी *priv)
अणु
	अगर (atomic_पढ़ो(&priv->psstatus.status) > PS_ACTIVE_SET)
		atomic_inc(&priv->psstatus.confirm_रुको);
पूर्ण

अटल अंतरभूत व्योम send_request_to_device(काष्ठा ks_wlan_निजी *priv,
					  व्योम *data, माप_प्रकार size)
अणु
	ps_confirm_रुको_inc(priv);
	ks_wlan_hw_tx(priv, data, size, शून्य, शून्य);
पूर्ण

अटल व्योम hostअगर_mib_get_request(काष्ठा ks_wlan_निजी *priv,
				   u32 mib_attribute)
अणु
	काष्ठा hostअगर_mib_get_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_MIB_GET_REQ);
	अगर (!pp)
		वापस;

	pp->mib_attribute = cpu_to_le32(mib_attribute);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल व्योम hostअगर_mib_set_request(काष्ठा ks_wlan_निजी *priv,
				   क्रमागत mib_attribute attr,
				   क्रमागत mib_data_type type,
				   व्योम *data, माप_प्रकार size)
अणु
	काष्ठा hostअगर_mib_set_request_t *pp;

	अगर (priv->dev_state < DEVICE_STATE_BOOT)
		वापस;

	pp = hostअगर_generic_request(माप(*pp), HIF_MIB_SET_REQ);
	अगर (!pp)
		वापस;

	pp->mib_attribute = cpu_to_le32(attr);
	pp->mib_value.size = cpu_to_le16(size);
	pp->mib_value.type = cpu_to_le16(type);
	स_नकल(&pp->mib_value.body, data, size);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp) + size));
पूर्ण

अटल अंतरभूत व्योम hostअगर_mib_set_request_पूर्णांक(काष्ठा ks_wlan_निजी *priv,
					      क्रमागत mib_attribute attr, पूर्णांक val)
अणु
	__le32 v = cpu_to_le32(val);
	माप_प्रकार size = माप(v);

	hostअगर_mib_set_request(priv, attr, MIB_VALUE_TYPE_INT, &v, size);
पूर्ण

अटल अंतरभूत व्योम hostअगर_mib_set_request_bool(काष्ठा ks_wlan_निजी *priv,
					       क्रमागत mib_attribute attr,
					       bool val)
अणु
	__le32 v = cpu_to_le32(val);
	माप_प्रकार size = माप(v);

	hostअगर_mib_set_request(priv, attr, MIB_VALUE_TYPE_BOOL, &v, size);
पूर्ण

अटल अंतरभूत व्योम hostअगर_mib_set_request_ostring(काष्ठा ks_wlan_निजी *priv,
						  क्रमागत mib_attribute attr,
						  व्योम *data, माप_प्रकार size)
अणु
	hostअगर_mib_set_request(priv, attr, MIB_VALUE_TYPE_OSTRING, data, size);
पूर्ण

अटल
व्योम hostअगर_start_request(काष्ठा ks_wlan_निजी *priv, अचिन्हित अक्षर mode)
अणु
	काष्ठा hostअगर_start_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_START_REQ);
	अगर (!pp)
		वापस;

	pp->mode = cpu_to_le16(mode);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));

	priv->aplist.size = 0;
	priv->scan_ind_count = 0;
पूर्ण

अटल __le16 ks_wlan_cap(काष्ठा ks_wlan_निजी *priv)
अणु
	u16 capability = 0x0000;

	अगर (priv->reg.preamble == SHORT_PREAMBLE)
		capability |= WLAN_CAPABILITY_SHORT_PREAMBLE;

	capability &= ~(WLAN_CAPABILITY_PBCC);	/* pbcc not support */

	अगर (priv->reg.phy_type != D_11B_ONLY_MODE) अणु
		capability |= WLAN_CAPABILITY_SHORT_SLOT_TIME;
		capability &= ~(WLAN_CAPABILITY_DSSS_OFDM);
	पूर्ण

	वापस cpu_to_le16(capability);
पूर्ण

अटल व्योम init_request(काष्ठा ks_wlan_निजी *priv,
			 काष्ठा hostअगर_request *req)
अणु
	req->phy_type = cpu_to_le16(priv->reg.phy_type);
	req->cts_mode = cpu_to_le16(priv->reg.cts_mode);
	req->scan_type = cpu_to_le16(priv->reg.scan_type);
	req->rate_set.size = priv->reg.rate_set.size;
	req->capability = ks_wlan_cap(priv);
	स_नकल(&req->rate_set.body[0], &priv->reg.rate_set.body[0],
	       priv->reg.rate_set.size);
पूर्ण

अटल
व्योम hostअगर_ps_adhoc_set_request(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा hostअगर_ps_adhoc_set_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_PS_ADH_SET_REQ);
	अगर (!pp)
		वापस;

	init_request(priv, &pp->request);
	pp->channel = cpu_to_le16(priv->reg.channel);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_infraकाष्ठाure_set_request(काष्ठा ks_wlan_निजी *priv, पूर्णांक event)
अणु
	काष्ठा hostअगर_infraकाष्ठाure_set_request *pp;

	pp = hostअगर_generic_request(माप(*pp), event);
	अगर (!pp)
		वापस;

	init_request(priv, &pp->request);
	pp->ssid.size = priv->reg.ssid.size;
	स_नकल(&pp->ssid.body[0], &priv->reg.ssid.body[0], priv->reg.ssid.size);
	pp->beacon_lost_count =
	    cpu_to_le16(priv->reg.beacon_lost_count);
	pp->auth_type = cpu_to_le16(priv->reg.authenticate_type);

	pp->channel_list.body[0] = 1;
	pp->channel_list.body[1] = 8;
	pp->channel_list.body[2] = 2;
	pp->channel_list.body[3] = 9;
	pp->channel_list.body[4] = 3;
	pp->channel_list.body[5] = 10;
	pp->channel_list.body[6] = 4;
	pp->channel_list.body[7] = 11;
	pp->channel_list.body[8] = 5;
	pp->channel_list.body[9] = 12;
	pp->channel_list.body[10] = 6;
	pp->channel_list.body[11] = 13;
	pp->channel_list.body[12] = 7;
	अगर (priv->reg.phy_type == D_11G_ONLY_MODE) अणु
		pp->channel_list.size = 13;
	पूर्ण अन्यथा अणु
		pp->channel_list.body[13] = 14;
		pp->channel_list.size = 14;
	पूर्ण

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_adhoc_set_request(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा hostअगर_adhoc_set_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_ADH_SET_REQ);
	अगर (!pp)
		वापस;

	init_request(priv, &pp->request);
	pp->channel = cpu_to_le16(priv->reg.channel);
	pp->ssid.size = priv->reg.ssid.size;
	स_नकल(&pp->ssid.body[0], &priv->reg.ssid.body[0], priv->reg.ssid.size);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_adhoc_set2_request(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा hostअगर_adhoc_set2_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_ADH_SET_REQ);
	अगर (!pp)
		वापस;

	init_request(priv, &pp->request);
	pp->ssid.size = priv->reg.ssid.size;
	स_नकल(&pp->ssid.body[0], &priv->reg.ssid.body[0], priv->reg.ssid.size);

	pp->channel_list.body[0] = priv->reg.channel;
	pp->channel_list.size = 1;
	स_नकल(pp->bssid, priv->reg.bssid, ETH_ALEN);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_stop_request(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा hostअगर_stop_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_STOP_REQ);
	अगर (!pp)
		वापस;

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_phy_inक्रमmation_request(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा hostअगर_phy_inक्रमmation_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_PHY_INFO_REQ);
	अगर (!pp)
		वापस;

	अगर (priv->reg.phy_info_समयr) अणु
		pp->type = cpu_to_le16(TIME_TYPE);
		pp->समय = cpu_to_le16(priv->reg.phy_info_समयr);
	पूर्ण अन्यथा अणु
		pp->type = cpu_to_le16(NORMAL_TYPE);
		pp->समय = cpu_to_le16(0);
	पूर्ण

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_घातer_mgmt_request(काष्ठा ks_wlan_निजी *priv,
			       u32 mode, u32 wake_up, u32 receive_dtims)
अणु
	काष्ठा hostअगर_घातer_mgmt_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_POWER_MGMT_REQ);
	अगर (!pp)
		वापस;

	pp->mode = cpu_to_le32(mode);
	pp->wake_up = cpu_to_le32(wake_up);
	pp->receive_dtims = cpu_to_le32(receive_dtims);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

अटल
व्योम hostअगर_sleep_request(काष्ठा ks_wlan_निजी *priv,
			  क्रमागत sleep_mode_type mode)
अणु
	काष्ठा hostअगर_sleep_request *pp;

	अगर (mode == SLP_SLEEP) अणु
		pp = hostअगर_generic_request(माप(*pp), HIF_SLEEP_REQ);
		अगर (!pp)
			वापस;

		send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
	पूर्ण अन्यथा अगर (mode == SLP_ACTIVE) अणु
		atomic_set(&priv->sleepstatus.wakeup_request, 1);
		queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
	पूर्ण अन्यथा अणु
		netdev_err(priv->net_dev, "invalid mode %ld\n", (दीर्घ)mode);
		वापस;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_bss_scan_request(काष्ठा ks_wlan_निजी *priv,
			     अचिन्हित दीर्घ scan_type, u8 *scan_ssid,
			     u8 scan_ssid_len)
अणु
	काष्ठा hostअगर_bss_scan_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_SCAN_REQ);
	अगर (!pp)
		वापस;

	pp->scan_type = scan_type;

	pp->ch_समय_min = cpu_to_le32(110);	/* शेष value */
	pp->ch_समय_max = cpu_to_le32(130);	/* शेष value */
	pp->channel_list.body[0] = 1;
	pp->channel_list.body[1] = 8;
	pp->channel_list.body[2] = 2;
	pp->channel_list.body[3] = 9;
	pp->channel_list.body[4] = 3;
	pp->channel_list.body[5] = 10;
	pp->channel_list.body[6] = 4;
	pp->channel_list.body[7] = 11;
	pp->channel_list.body[8] = 5;
	pp->channel_list.body[9] = 12;
	pp->channel_list.body[10] = 6;
	pp->channel_list.body[11] = 13;
	pp->channel_list.body[12] = 7;
	अगर (priv->reg.phy_type == D_11G_ONLY_MODE) अणु
		pp->channel_list.size = 13;
	पूर्ण अन्यथा अणु
		pp->channel_list.body[13] = 14;
		pp->channel_list.size = 14;
	पूर्ण
	pp->ssid.size = 0;

	/* specअगरied SSID SCAN */
	अगर (scan_ssid_len > 0 && scan_ssid_len <= 32) अणु
		pp->ssid.size = scan_ssid_len;
		स_नकल(&pp->ssid.body[0], scan_ssid, scan_ssid_len);
	पूर्ण

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));

	priv->aplist.size = 0;
	priv->scan_ind_count = 0;
पूर्ण

अटल
व्योम hostअगर_mic_failure_request(काष्ठा ks_wlan_निजी *priv,
				u16 failure_count, u16 समयr)
अणु
	काष्ठा hostअगर_mic_failure_request *pp;

	pp = hostअगर_generic_request(माप(*pp), HIF_MIC_FAILURE_REQ);
	अगर (!pp)
		वापस;

	pp->failure_count = cpu_to_le16(failure_count);
	pp->समयr = cpu_to_le16(समयr);

	send_request_to_device(priv, pp, hअगर_align_size(माप(*pp)));
पूर्ण

/* Device I/O Receive indicate */
अटल व्योम devio_rec_ind(काष्ठा ks_wlan_निजी *priv, अचिन्हित अक्षर *p,
			  अचिन्हित पूर्णांक size)
अणु
	अगर (!priv->is_device_खोलो)
		वापस;

	spin_lock(&priv->dev_पढ़ो_lock);
	priv->dev_data[atomic_पढ़ो(&priv->rec_count)] = p;
	priv->dev_size[atomic_पढ़ो(&priv->rec_count)] = size;

	अगर (atomic_पढ़ो(&priv->event_count) != DEVICE_STOCK_COUNT) अणु
		/* rx event count inc */
		atomic_inc(&priv->event_count);
	पूर्ण
	atomic_inc(&priv->rec_count);
	अगर (atomic_पढ़ो(&priv->rec_count) == DEVICE_STOCK_COUNT)
		atomic_set(&priv->rec_count, 0);

	wake_up_पूर्णांकerruptible_all(&priv->devपढ़ो_रुको);

	spin_unlock(&priv->dev_पढ़ो_lock);
पूर्ण

व्योम hostअगर_receive(काष्ठा ks_wlan_निजी *priv, अचिन्हित अक्षर *p,
		    अचिन्हित पूर्णांक size)
अणु
	devio_rec_ind(priv, p, size);

	priv->rxp = p;
	priv->rx_size = size;

	अगर (get_word(priv) == priv->rx_size)
		hostअगर_event_check(priv);
पूर्ण

अटल व्योम hostअगर_sme_set_wep(काष्ठा ks_wlan_निजी *priv, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SME_WEP_INDEX_REQUEST:
		hostअगर_mib_set_request_पूर्णांक(priv, DOT11_WEP_DEFAULT_KEY_ID,
					   priv->reg.wep_index);
		अवरोध;
	हाल SME_WEP_KEY1_REQUEST:
		अगर (priv->wpa.wpa_enabled)
			वापस;
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE1,
					       &priv->reg.wep_key[0].val[0],
					       priv->reg.wep_key[0].size);
		अवरोध;
	हाल SME_WEP_KEY2_REQUEST:
		अगर (priv->wpa.wpa_enabled)
			वापस;
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE2,
					       &priv->reg.wep_key[1].val[0],
					       priv->reg.wep_key[1].size);
		अवरोध;
	हाल SME_WEP_KEY3_REQUEST:
		अगर (priv->wpa.wpa_enabled)
			वापस;
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE3,
					       &priv->reg.wep_key[2].val[0],
					       priv->reg.wep_key[2].size);
		अवरोध;
	हाल SME_WEP_KEY4_REQUEST:
		अगर (priv->wpa.wpa_enabled)
			वापस;
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE4,
					       &priv->reg.wep_key[3].val[0],
					       priv->reg.wep_key[3].size);
		अवरोध;
	हाल SME_WEP_FLAG_REQUEST:
		hostअगर_mib_set_request_bool(priv, DOT11_PRIVACY_INVOKED,
					    priv->reg.privacy_invoked);
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा wpa_suite अणु
	__le16 size;
	अचिन्हित अक्षर suite[4][CIPHER_ID_LEN];
पूर्ण __packed;

काष्ठा rsn_mode अणु
	__le32 rsn_mode;
	__le16 rsn_capability;
पूर्ण __packed;

अटल व्योम hostअगर_sme_set_rsn(काष्ठा ks_wlan_निजी *priv, पूर्णांक type)
अणु
	काष्ठा wpa_suite wpa_suite;
	काष्ठा rsn_mode rsn_mode;
	माप_प्रकार size;
	u32 mode;
	स्थिर u8 *buf = शून्य;

	स_रखो(&wpa_suite, 0, माप(wpa_suite));

	चयन (type) अणु
	हाल SME_RSN_UCAST_REQUEST:
		wpa_suite.size = cpu_to_le16(1);
		चयन (priv->wpa.pairwise_suite) अणु
		हाल IW_AUTH_CIPHER_NONE:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_NONE : CIPHER_ID_WPA_NONE;
			अवरोध;
		हाल IW_AUTH_CIPHER_WEP40:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP40 : CIPHER_ID_WPA_WEP40;
			अवरोध;
		हाल IW_AUTH_CIPHER_TKIP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_TKIP : CIPHER_ID_WPA_TKIP;
			अवरोध;
		हाल IW_AUTH_CIPHER_CCMP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_CCMP : CIPHER_ID_WPA_CCMP;
			अवरोध;
		हाल IW_AUTH_CIPHER_WEP104:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP104 : CIPHER_ID_WPA_WEP104;
			अवरोध;
		पूर्ण

		अगर (buf)
			स_नकल(&wpa_suite.suite[0][0], buf, CIPHER_ID_LEN);
		size = माप(wpa_suite.size) +
		       (CIPHER_ID_LEN * le16_to_cpu(wpa_suite.size));
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_RSN_CONFIG_UNICAST_CIPHER,
					       &wpa_suite, size);
		अवरोध;
	हाल SME_RSN_MCAST_REQUEST:
		चयन (priv->wpa.group_suite) अणु
		हाल IW_AUTH_CIPHER_NONE:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_NONE : CIPHER_ID_WPA_NONE;
			अवरोध;
		हाल IW_AUTH_CIPHER_WEP40:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP40 : CIPHER_ID_WPA_WEP40;
			अवरोध;
		हाल IW_AUTH_CIPHER_TKIP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_TKIP : CIPHER_ID_WPA_TKIP;
			अवरोध;
		हाल IW_AUTH_CIPHER_CCMP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_CCMP : CIPHER_ID_WPA_CCMP;
			अवरोध;
		हाल IW_AUTH_CIPHER_WEP104:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP104 : CIPHER_ID_WPA_WEP104;
			अवरोध;
		पूर्ण
		अगर (buf)
			स_नकल(&wpa_suite.suite[0][0], buf, CIPHER_ID_LEN);
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_RSN_CONFIG_MULTICAST_CIPHER,
					       &wpa_suite.suite[0][0],
					       CIPHER_ID_LEN);
		अवरोध;
	हाल SME_RSN_AUTH_REQUEST:
		wpa_suite.size = cpu_to_le16(1);
		चयन (priv->wpa.key_mgmt_suite) अणु
		हाल IW_AUTH_KEY_MGMT_802_1X:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_1X : KEY_MGMT_ID_WPA_1X;
			अवरोध;
		हाल IW_AUTH_KEY_MGMT_PSK:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_PSK : KEY_MGMT_ID_WPA_PSK;
			अवरोध;
		हाल 0:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_NONE : KEY_MGMT_ID_WPA_NONE;
			अवरोध;
		हाल 4:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_WPANONE :
				KEY_MGMT_ID_WPA_WPANONE;
			अवरोध;
		पूर्ण

		अगर (buf)
			स_नकल(&wpa_suite.suite[0][0], buf, KEY_MGMT_ID_LEN);
		size = माप(wpa_suite.size) +
		       (KEY_MGMT_ID_LEN * le16_to_cpu(wpa_suite.size));
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_RSN_CONFIG_AUTH_SUITE,
					       &wpa_suite, size);
		अवरोध;
	हाल SME_RSN_ENABLED_REQUEST:
		hostअगर_mib_set_request_bool(priv, DOT11_RSN_ENABLED,
					    priv->wpa.rsn_enabled);
		अवरोध;
	हाल SME_RSN_MODE_REQUEST:
		mode = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
			RSN_MODE_WPA2 :
			(priv->wpa.version == IW_AUTH_WPA_VERSION_WPA) ?
			 RSN_MODE_WPA : RSN_MODE_NONE;
		rsn_mode.rsn_mode = cpu_to_le32(mode);
		rsn_mode.rsn_capability = cpu_to_le16(0);
		hostअगर_mib_set_request_ostring(priv, LOCAL_RSN_MODE,
					       &rsn_mode, माप(rsn_mode));
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_sme_mode_setup(काष्ठा ks_wlan_निजी *priv)
अणु
	अचिन्हित अक्षर rate_size;
	अचिन्हित अक्षर rate_octet[RATE_SET_MAX_SIZE];
	पूर्णांक i = 0;

	/* rate setting अगर rate segging is स्वतः क्रम changing phy_type (#94) */
	अगर (priv->reg.tx_rate == TX_RATE_FULL_AUTO) अणु
		अगर (priv->reg.phy_type == D_11B_ONLY_MODE) अणु
			priv->reg.rate_set.body[3] = TX_RATE_11M;
			priv->reg.rate_set.body[2] = TX_RATE_5M;
			priv->reg.rate_set.body[1] = TX_RATE_2M | BASIC_RATE;
			priv->reg.rate_set.body[0] = TX_RATE_1M | BASIC_RATE;
			priv->reg.rate_set.size = 4;
		पूर्ण अन्यथा अणु	/* D_11G_ONLY_MODE or D_11BG_COMPATIBLE_MODE */
			priv->reg.rate_set.body[11] = TX_RATE_54M;
			priv->reg.rate_set.body[10] = TX_RATE_48M;
			priv->reg.rate_set.body[9] = TX_RATE_36M;
			priv->reg.rate_set.body[8] = TX_RATE_18M;
			priv->reg.rate_set.body[7] = TX_RATE_9M;
			priv->reg.rate_set.body[6] = TX_RATE_24M | BASIC_RATE;
			priv->reg.rate_set.body[5] = TX_RATE_12M | BASIC_RATE;
			priv->reg.rate_set.body[4] = TX_RATE_6M | BASIC_RATE;
			priv->reg.rate_set.body[3] = TX_RATE_11M | BASIC_RATE;
			priv->reg.rate_set.body[2] = TX_RATE_5M | BASIC_RATE;
			priv->reg.rate_set.body[1] = TX_RATE_2M | BASIC_RATE;
			priv->reg.rate_set.body[0] = TX_RATE_1M | BASIC_RATE;
			priv->reg.rate_set.size = 12;
		पूर्ण
	पूर्ण

	/* rate mask by phy setting */
	अगर (priv->reg.phy_type == D_11B_ONLY_MODE) अणु
		क्रम (i = 0; i < priv->reg.rate_set.size; i++) अणु
			अगर (!is_11b_rate(priv->reg.rate_set.body[i]))
				अवरोध;

			अगर ((priv->reg.rate_set.body[i] & RATE_MASK) >= TX_RATE_5M) अणु
				rate_octet[i] = priv->reg.rate_set.body[i] &
						RATE_MASK;
			पूर्ण अन्यथा अणु
				rate_octet[i] = priv->reg.rate_set.body[i];
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु	/* D_11G_ONLY_MODE or D_11BG_COMPATIBLE_MODE */
		क्रम (i = 0; i < priv->reg.rate_set.size; i++) अणु
			अगर (!is_11bg_rate(priv->reg.rate_set.body[i]))
				अवरोध;

			अगर (is_ofdm_ext_rate(priv->reg.rate_set.body[i])) अणु
				rate_octet[i] = priv->reg.rate_set.body[i] &
						RATE_MASK;
			पूर्ण अन्यथा अणु
				rate_octet[i] = priv->reg.rate_set.body[i];
			पूर्ण
		पूर्ण
	पूर्ण
	rate_size = i;
	अगर (rate_size == 0) अणु
		अगर (priv->reg.phy_type == D_11G_ONLY_MODE)
			rate_octet[0] = TX_RATE_6M | BASIC_RATE;
		अन्यथा
			rate_octet[0] = TX_RATE_2M | BASIC_RATE;
		rate_size = 1;
	पूर्ण

	/* rate set update */
	priv->reg.rate_set.size = rate_size;
	स_नकल(&priv->reg.rate_set.body[0], &rate_octet[0], rate_size);

	चयन (priv->reg.operation_mode) अणु
	हाल MODE_PSEUDO_ADHOC:
		hostअगर_ps_adhoc_set_request(priv);
		अवरोध;
	हाल MODE_INFRASTRUCTURE:
		अगर (!is_valid_ether_addr((u8 *)priv->reg.bssid)) अणु
			hostअगर_infraकाष्ठाure_set_request(priv,
							  HIF_INFRA_SET_REQ);
		पूर्ण अन्यथा अणु
			hostअगर_infraकाष्ठाure_set_request(priv,
							  HIF_INFRA_SET2_REQ);
			netdev_dbg(priv->net_dev,
				   "Infra bssid = %pM\n", priv->reg.bssid);
		पूर्ण
		अवरोध;
	हाल MODE_ADHOC:
		अगर (!is_valid_ether_addr((u8 *)priv->reg.bssid)) अणु
			hostअगर_adhoc_set_request(priv);
		पूर्ण अन्यथा अणु
			hostअगर_adhoc_set2_request(priv);
			netdev_dbg(priv->net_dev,
				   "Adhoc bssid = %pM\n", priv->reg.bssid);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_sme_multicast_set(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	पूर्णांक mc_count;
	काष्ठा netdev_hw_addr *ha;
	अक्षर set_address[NIC_MAX_MCAST_LIST * ETH_ALEN];
	पूर्णांक i = 0;

	spin_lock(&priv->multicast_spin);

	स_रखो(set_address, 0, NIC_MAX_MCAST_LIST * ETH_ALEN);

	अगर (dev->flags & IFF_PROMISC) अणु
		hostअगर_mib_set_request_पूर्णांक(priv, LOCAL_MULTICAST_FILTER,
					   MCAST_FILTER_PROMISC);
		जाओ spin_unlock;
	पूर्ण

	अगर ((netdev_mc_count(dev) > NIC_MAX_MCAST_LIST) ||
	    (dev->flags & IFF_ALLMULTI)) अणु
		hostअगर_mib_set_request_पूर्णांक(priv, LOCAL_MULTICAST_FILTER,
					   MCAST_FILTER_MCASTALL);
		जाओ spin_unlock;
	पूर्ण

	अगर (priv->sme_i.sme_flag & SME_MULTICAST) अणु
		mc_count = netdev_mc_count(dev);
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			ether_addr_copy(&set_address[i * ETH_ALEN], ha->addr);
			i++;
		पूर्ण
		priv->sme_i.sme_flag &= ~SME_MULTICAST;
		hostअगर_mib_set_request_ostring(priv, LOCAL_MULTICAST_ADDRESS,
					       &set_address[0],
					       ETH_ALEN * mc_count);
	पूर्ण अन्यथा अणु
		priv->sme_i.sme_flag |= SME_MULTICAST;
		hostअगर_mib_set_request_पूर्णांक(priv, LOCAL_MULTICAST_FILTER,
					   MCAST_FILTER_MCAST);
	पूर्ण

spin_unlock:
	spin_unlock(&priv->multicast_spin);
पूर्ण

अटल व्योम hostअगर_sme_घातer_mgmt_set(काष्ठा ks_wlan_निजी *priv)
अणु
	u32 mode, wake_up, receive_dtims;

	अगर (priv->reg.घातer_mgmt != POWER_MGMT_SAVE1 &&
	    priv->reg.घातer_mgmt != POWER_MGMT_SAVE2) अणु
		mode = POWER_ACTIVE;
		wake_up = 0;
		receive_dtims = 0;
	पूर्ण अन्यथा अणु
		mode = (priv->reg.operation_mode == MODE_INFRASTRUCTURE) ?
			POWER_SAVE : POWER_ACTIVE;
		wake_up = 0;
		receive_dtims = (priv->reg.operation_mode == MODE_INFRASTRUCTURE &&
				 priv->reg.घातer_mgmt == POWER_MGMT_SAVE2);
	पूर्ण

	hostअगर_घातer_mgmt_request(priv, mode, wake_up, receive_dtims);
पूर्ण

अटल व्योम hostअगर_sme_sleep_set(काष्ठा ks_wlan_निजी *priv)
अणु
	अगर (priv->sleep_mode != SLP_SLEEP &&
	    priv->sleep_mode != SLP_ACTIVE)
		वापस;

	hostअगर_sleep_request(priv, priv->sleep_mode);
पूर्ण

अटल
व्योम hostअगर_sme_set_key(काष्ठा ks_wlan_निजी *priv, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SME_SET_FLAG:
		hostअगर_mib_set_request_bool(priv, DOT11_PRIVACY_INVOKED,
					    priv->reg.privacy_invoked);
		अवरोध;
	हाल SME_SET_TXKEY:
		hostअगर_mib_set_request_पूर्णांक(priv, DOT11_WEP_DEFAULT_KEY_ID,
					   priv->wpa.txkey);
		अवरोध;
	हाल SME_SET_KEY1:
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE1,
					       &priv->wpa.key[0].key_val[0],
					       priv->wpa.key[0].key_len);
		अवरोध;
	हाल SME_SET_KEY2:
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE2,
					       &priv->wpa.key[1].key_val[0],
					       priv->wpa.key[1].key_len);
		अवरोध;
	हाल SME_SET_KEY3:
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE3,
					       &priv->wpa.key[2].key_val[0],
					       priv->wpa.key[2].key_len);
		अवरोध;
	हाल SME_SET_KEY4:
		hostअगर_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE4,
					       &priv->wpa.key[3].key_val[0],
					       priv->wpa.key[3].key_len);
		अवरोध;
	हाल SME_SET_PMK_TSC:
		hostअगर_mib_set_request_ostring(priv, DOT11_PMK_TSC,
					       &priv->wpa.key[0].rx_seq[0],
					       WPA_RX_SEQ_LEN);
		अवरोध;
	हाल SME_SET_GMK1_TSC:
		hostअगर_mib_set_request_ostring(priv, DOT11_GMK1_TSC,
					       &priv->wpa.key[1].rx_seq[0],
					       WPA_RX_SEQ_LEN);
		अवरोध;
	हाल SME_SET_GMK2_TSC:
		hostअगर_mib_set_request_ostring(priv, DOT11_GMK2_TSC,
					       &priv->wpa.key[2].rx_seq[0],
					       WPA_RX_SEQ_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_sme_set_pmksa(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा pmk_cache अणु
		__le16 size;
		काष्ठा अणु
			u8 bssid[ETH_ALEN];
			u8 pmkid[IW_PMKID_LEN];
		पूर्ण __packed list[PMK_LIST_MAX];
	पूर्ण __packed pmkcache;
	काष्ठा pmk *pmk;
	माप_प्रकार size;
	पूर्णांक i = 0;

	list_क्रम_each_entry(pmk, &priv->pmklist.head, list) अणु
		अगर (i >= PMK_LIST_MAX)
			अवरोध;
		ether_addr_copy(pmkcache.list[i].bssid, pmk->bssid);
		स_नकल(pmkcache.list[i].pmkid, pmk->pmkid, IW_PMKID_LEN);
		i++;
	पूर्ण
	pmkcache.size = cpu_to_le16(priv->pmklist.size);
	size = माप(priv->pmklist.size) +
	       ((ETH_ALEN + IW_PMKID_LEN) * priv->pmklist.size);
	hostअगर_mib_set_request_ostring(priv, LOCAL_PMK, &pmkcache, size);
पूर्ण

/* execute sme */
अटल व्योम hostअगर_sme_execute(काष्ठा ks_wlan_निजी *priv, पूर्णांक event)
अणु
	u16 failure;

	चयन (event) अणु
	हाल SME_START:
		अगर (priv->dev_state == DEVICE_STATE_BOOT)
			hostअगर_mib_get_request(priv, DOT11_MAC_ADDRESS);
		अवरोध;
	हाल SME_MULTICAST_REQUEST:
		hostअगर_sme_multicast_set(priv);
		अवरोध;
	हाल SME_MACADDRESS_SET_REQUEST:
		hostअगर_mib_set_request_ostring(priv, LOCAL_CURRENTADDRESS,
					       &priv->eth_addr[0], ETH_ALEN);
		अवरोध;
	हाल SME_BSS_SCAN_REQUEST:
		hostअगर_bss_scan_request(priv, priv->reg.scan_type,
					priv->scan_ssid, priv->scan_ssid_len);
		अवरोध;
	हाल SME_POW_MNGMT_REQUEST:
		hostअगर_sme_घातer_mgmt_set(priv);
		अवरोध;
	हाल SME_PHY_INFO_REQUEST:
		hostअगर_phy_inक्रमmation_request(priv);
		अवरोध;
	हाल SME_MIC_FAILURE_REQUEST:
		failure = priv->wpa.mic_failure.failure;
		अगर (failure != 1 && failure != 2) अणु
			netdev_err(priv->net_dev,
				   "SME_MIC_FAILURE_REQUEST: failure count=%u error?\n",
				   failure);
			वापस;
		पूर्ण
		hostअगर_mic_failure_request(priv, failure - 1, (failure == 1) ?
					    0 : priv->wpa.mic_failure.counter);
		अवरोध;
	हाल SME_MIC_FAILURE_CONFIRM:
		अगर (priv->wpa.mic_failure.failure == 2) अणु
			अगर (priv->wpa.mic_failure.stop)
				priv->wpa.mic_failure.stop = 0;
			priv->wpa.mic_failure.failure = 0;
			hostअगर_start_request(priv, priv->reg.operation_mode);
		पूर्ण
		अवरोध;
	हाल SME_GET_MAC_ADDRESS:
		अगर (priv->dev_state == DEVICE_STATE_BOOT)
			hostअगर_mib_get_request(priv, DOT11_PRODUCT_VERSION);
		अवरोध;
	हाल SME_GET_PRODUCT_VERSION:
		अगर (priv->dev_state == DEVICE_STATE_BOOT)
			priv->dev_state = DEVICE_STATE_PREINIT;
		अवरोध;
	हाल SME_STOP_REQUEST:
		hostअगर_stop_request(priv);
		अवरोध;
	हाल SME_RTS_THRESHOLD_REQUEST:
		hostअगर_mib_set_request_पूर्णांक(priv, DOT11_RTS_THRESHOLD,
					   priv->reg.rts);
		अवरोध;
	हाल SME_FRAGMENTATION_THRESHOLD_REQUEST:
		hostअगर_mib_set_request_पूर्णांक(priv, DOT11_FRAGMENTATION_THRESHOLD,
					   priv->reg.fragment);
		अवरोध;
	हाल SME_WEP_INDEX_REQUEST:
	हाल SME_WEP_KEY1_REQUEST:
	हाल SME_WEP_KEY2_REQUEST:
	हाल SME_WEP_KEY3_REQUEST:
	हाल SME_WEP_KEY4_REQUEST:
	हाल SME_WEP_FLAG_REQUEST:
		hostअगर_sme_set_wep(priv, event);
		अवरोध;
	हाल SME_RSN_UCAST_REQUEST:
	हाल SME_RSN_MCAST_REQUEST:
	हाल SME_RSN_AUTH_REQUEST:
	हाल SME_RSN_ENABLED_REQUEST:
	हाल SME_RSN_MODE_REQUEST:
		hostअगर_sme_set_rsn(priv, event);
		अवरोध;
	हाल SME_SET_FLAG:
	हाल SME_SET_TXKEY:
	हाल SME_SET_KEY1:
	हाल SME_SET_KEY2:
	हाल SME_SET_KEY3:
	हाल SME_SET_KEY4:
	हाल SME_SET_PMK_TSC:
	हाल SME_SET_GMK1_TSC:
	हाल SME_SET_GMK2_TSC:
		hostअगर_sme_set_key(priv, event);
		अवरोध;
	हाल SME_SET_PMKSA:
		hostअगर_sme_set_pmksa(priv);
		अवरोध;
	हाल SME_WPS_ENABLE_REQUEST:
		hostअगर_mib_set_request_पूर्णांक(priv, LOCAL_WPS_ENABLE,
					   priv->wps.wps_enabled);
		अवरोध;
	हाल SME_WPS_PROBE_REQUEST:
		hostअगर_mib_set_request_ostring(priv, LOCAL_WPS_PROBE_REQ,
					       priv->wps.ie, priv->wps.ielen);
		अवरोध;
	हाल SME_MODE_SET_REQUEST:
		hostअगर_sme_mode_setup(priv);
		अवरोध;
	हाल SME_SET_GAIN:
		hostअगर_mib_set_request_ostring(priv, LOCAL_GAIN,
					       &priv->gain, माप(priv->gain));
		अवरोध;
	हाल SME_GET_GAIN:
		hostअगर_mib_get_request(priv, LOCAL_GAIN);
		अवरोध;
	हाल SME_GET_EEPROM_CKSUM:
		priv->eeprom_checksum = EEPROM_FW_NOT_SUPPORT;	/* initialize */
		hostअगर_mib_get_request(priv, LOCAL_EEPROM_SUM);
		अवरोध;
	हाल SME_START_REQUEST:
		hostअगर_start_request(priv, priv->reg.operation_mode);
		अवरोध;
	हाल SME_START_CONFIRM:
		/* क्रम घातer save */
		atomic_set(&priv->psstatus.snooze_guard, 0);
		atomic_set(&priv->psstatus.confirm_रुको, 0);
		अगर (priv->dev_state == DEVICE_STATE_PREINIT)
			priv->dev_state = DEVICE_STATE_INIT;
		/* wake_up_पूर्णांकerruptible_all(&priv->confirm_रुको); */
		complete(&priv->confirm_रुको);
		अवरोध;
	हाल SME_SLEEP_REQUEST:
		hostअगर_sme_sleep_set(priv);
		अवरोध;
	हाल SME_SET_REGION:
		hostअगर_mib_set_request_पूर्णांक(priv, LOCAL_REGION, priv->region);
		अवरोध;
	हाल SME_MULTICAST_CONFIRM:
	हाल SME_BSS_SCAN_CONFIRM:
	हाल SME_POW_MNGMT_CONFIRM:
	हाल SME_PHY_INFO_CONFIRM:
	हाल SME_STOP_CONFIRM:
	हाल SME_RTS_THRESHOLD_CONFIRM:
	हाल SME_FRAGMENTATION_THRESHOLD_CONFIRM:
	हाल SME_WEP_INDEX_CONFIRM:
	हाल SME_WEP_KEY1_CONFIRM:
	हाल SME_WEP_KEY2_CONFIRM:
	हाल SME_WEP_KEY3_CONFIRM:
	हाल SME_WEP_KEY4_CONFIRM:
	हाल SME_WEP_FLAG_CONFIRM:
	हाल SME_RSN_UCAST_CONFIRM:
	हाल SME_RSN_MCAST_CONFIRM:
	हाल SME_RSN_AUTH_CONFIRM:
	हाल SME_RSN_ENABLED_CONFIRM:
	हाल SME_RSN_MODE_CONFIRM:
	हाल SME_MODE_SET_CONFIRM:
	हाल SME_TERMINATE:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम hostअगर_sme_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ks_wlan_निजी *priv = from_tasklet(priv, t, sme_task);

	अगर (priv->dev_state < DEVICE_STATE_BOOT)
		वापस;

	अगर (cnt_smeqbody(priv) <= 0)
		वापस;

	hostअगर_sme_execute(priv, priv->sme_i.event_buff[priv->sme_i.qhead]);
	inc_smeqhead(priv);
	अगर (cnt_smeqbody(priv) > 0)
		tasklet_schedule(&priv->sme_task);
पूर्ण

/* send to Station Management Entity module */
व्योम hostअगर_sme_enqueue(काष्ठा ks_wlan_निजी *priv, u16 event)
अणु
	/* enqueue sme event */
	अगर (cnt_smeqbody(priv) < (SME_EVENT_BUFF_SIZE - 1)) अणु
		priv->sme_i.event_buff[priv->sme_i.qtail] = event;
		inc_smeqtail(priv);
	पूर्ण अन्यथा अणु
		/* in हाल of buffer overflow */
		netdev_err(priv->net_dev, "sme queue buffer overflow\n");
	पूर्ण

	tasklet_schedule(&priv->sme_task);
पूर्ण

अटल अंतरभूत व्योम hostअगर_aplist_init(काष्ठा ks_wlan_निजी *priv)
अणु
	माप_प्रकार size = LOCAL_APLIST_MAX * माप(काष्ठा local_ap);

	priv->aplist.size = 0;
	स_रखो(&priv->aplist.ap[0], 0, size);
पूर्ण

अटल अंतरभूत व्योम hostअगर_status_init(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->infra_status = 0;
	priv->current_rate = 4;
	priv->connect_status = DISCONNECT_STATUS;
पूर्ण

अटल अंतरभूत व्योम hostअगर_sme_init(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->sme_i.sme_status = SME_IDLE;
	priv->sme_i.qhead = 0;
	priv->sme_i.qtail = 0;
	spin_lock_init(&priv->sme_i.sme_spin);
	priv->sme_i.sme_flag = 0;
	tasklet_setup(&priv->sme_task, hostअगर_sme_task);
पूर्ण

अटल अंतरभूत व्योम hostअगर_wpa_init(काष्ठा ks_wlan_निजी *priv)
अणु
	स_रखो(&priv->wpa, 0, माप(priv->wpa));
	priv->wpa.rsn_enabled = false;
	priv->wpa.mic_failure.failure = 0;
	priv->wpa.mic_failure.last_failure_समय = 0;
	priv->wpa.mic_failure.stop = 0;
पूर्ण

अटल अंतरभूत व्योम hostअगर_घातer_save_init(काष्ठा ks_wlan_निजी *priv)
अणु
	atomic_set(&priv->psstatus.status, PS_NONE);
	atomic_set(&priv->psstatus.confirm_रुको, 0);
	atomic_set(&priv->psstatus.snooze_guard, 0);
	init_completion(&priv->psstatus.wakeup_रुको);
	INIT_WORK(&priv->wakeup_work, ks_wlan_hw_wakeup_task);
पूर्ण

अटल अंतरभूत व्योम hostअगर_pmklist_init(काष्ठा ks_wlan_निजी *priv)
अणु
	पूर्णांक i;

	स_रखो(&priv->pmklist, 0, माप(priv->pmklist));
	INIT_LIST_HEAD(&priv->pmklist.head);
	क्रम (i = 0; i < PMK_LIST_MAX; i++)
		INIT_LIST_HEAD(&priv->pmklist.pmk[i].list);
पूर्ण

अटल अंतरभूत व्योम hostअगर_counters_init(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->dev_count = 0;
	atomic_set(&priv->event_count, 0);
	atomic_set(&priv->rec_count, 0);
पूर्ण

पूर्णांक hostअगर_init(काष्ठा ks_wlan_निजी *priv)
अणु
	hostअगर_aplist_init(priv);
	hostअगर_status_init(priv);

	spin_lock_init(&priv->multicast_spin);
	spin_lock_init(&priv->dev_पढ़ो_lock);
	init_रुकोqueue_head(&priv->devपढ़ो_रुको);

	hostअगर_counters_init(priv);
	hostअगर_घातer_save_init(priv);
	hostअगर_wpa_init(priv);
	hostअगर_pmklist_init(priv);
	hostअगर_sme_init(priv);

	वापस 0;
पूर्ण

व्योम hostअगर_निकास(काष्ठा ks_wlan_निजी *priv)
अणु
	tasklet_समाप्त(&priv->sme_task);
पूर्ण
