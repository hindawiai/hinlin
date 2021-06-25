<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित HOSTAP_80211_H
#घोषणा HOSTAP_80211_H

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>

काष्ठा hostap_ieee80211_mgmt अणु
	__le16 frame_control;
	__le16 duration;
	u8 da[6];
	u8 sa[6];
	u8 bssid[6];
	__le16 seq_ctrl;
	जोड़ अणु
		काष्ठा अणु
			__le16 auth_alg;
			__le16 auth_transaction;
			__le16 status_code;
			/* possibly followed by Challenge text */
			u8 variable[0];
		पूर्ण __packed auth;
		काष्ठा अणु
			__le16 reason_code;
		पूर्ण __packed deauth;
		काष्ठा अणु
			__le16 capab_info;
			__le16 listen_पूर्णांकerval;
			/* followed by SSID and Supported rates */
			u8 variable[0];
		पूर्ण __packed assoc_req;
		काष्ठा अणु
			__le16 capab_info;
			__le16 status_code;
			__le16 aid;
			/* followed by Supported rates */
			u8 variable[0];
		पूर्ण __packed assoc_resp, reassoc_resp;
		काष्ठा अणु
			__le16 capab_info;
			__le16 listen_पूर्णांकerval;
			u8 current_ap[6];
			/* followed by SSID and Supported rates */
			u8 variable[0];
		पूर्ण __packed reassoc_req;
		काष्ठा अणु
			__le16 reason_code;
		पूर्ण __packed disassoc;
		काष्ठा अणु
		पूर्ण __packed probe_req;
		काष्ठा अणु
			u8 बारtamp[8];
			__le16 beacon_पूर्णांक;
			__le16 capab_info;
			/* followed by some of SSID, Supported rates,
			 * FH Params, DS Params, CF Params, IBSS Params, TIM */
			u8 variable[0];
		पूर्ण __packed beacon, probe_resp;
	पूर्ण u;
पूर्ण __packed;


#घोषणा IEEE80211_MGMT_HDR_LEN 24
#घोषणा IEEE80211_DATA_HDR3_LEN 24
#घोषणा IEEE80211_DATA_HDR4_LEN 30


काष्ठा hostap_80211_rx_status अणु
	u32 mac_समय;
	u8 संकेत;
	u8 noise;
	u16 rate; /* in 100 kbps */
पूर्ण;

/* prism2_rx_80211 'type' argument */
क्रमागत अणु
	PRISM2_RX_MONITOR, PRISM2_RX_MGMT, PRISM2_RX_NON_ASSOC,
	PRISM2_RX_शून्यFUNC_ACK
पूर्ण;

पूर्णांक prism2_rx_80211(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		    काष्ठा hostap_80211_rx_status *rx_stats, पूर्णांक type);
व्योम hostap_80211_rx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		     काष्ठा hostap_80211_rx_status *rx_stats);
व्योम hostap_dump_rx_80211(स्थिर अक्षर *name, काष्ठा sk_buff *skb,
			  काष्ठा hostap_80211_rx_status *rx_stats);

व्योम hostap_dump_tx_80211(स्थिर अक्षर *name, काष्ठा sk_buff *skb);
netdev_tx_t hostap_data_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev);
netdev_tx_t hostap_mgmt_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev);
netdev_tx_t hostap_master_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev);

#पूर्ण_अगर /* HOSTAP_80211_H */
