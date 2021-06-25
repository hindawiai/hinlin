<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _MAC_H_
#घोषणा _MAC_H_

#समावेश <net/mac80211.h>
#समावेश "core.h"

#घोषणा WEP_KEYID_SHIFT 6

क्रमागत wmi_tlv_tx_छोड़ो_id;
क्रमागत wmi_tlv_tx_छोड़ो_action;

काष्ठा ath10k_generic_iter अणु
	काष्ठा ath10k *ar;
	पूर्णांक ret;
पूर्ण;

काष्ठा rfc1042_hdr अणु
	u8 llc_dsap;
	u8 llc_ssap;
	u8 llc_ctrl;
	u8 snap_oui[3];
	__be16 snap_type;
पूर्ण __packed;

काष्ठा ath10k *ath10k_mac_create(माप_प्रकार priv_size);
व्योम ath10k_mac_destroy(काष्ठा ath10k *ar);
पूर्णांक ath10k_mac_रेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_mac_unरेजिस्टर(काष्ठा ath10k *ar);
काष्ठा ath10k_vअगर *ath10k_get_arvअगर(काष्ठा ath10k *ar, u32 vdev_id);
व्योम __ath10k_scan_finish(काष्ठा ath10k *ar);
व्योम ath10k_scan_finish(काष्ठा ath10k *ar);
व्योम ath10k_scan_समयout_work(काष्ठा work_काष्ठा *work);
व्योम ath10k_offchan_tx_purge(काष्ठा ath10k *ar);
व्योम ath10k_offchan_tx_work(काष्ठा work_काष्ठा *work);
व्योम ath10k_mgmt_over_wmi_tx_purge(काष्ठा ath10k *ar);
व्योम ath10k_mgmt_over_wmi_tx_work(काष्ठा work_काष्ठा *work);
व्योम ath10k_halt(काष्ठा ath10k *ar);
व्योम ath10k_mac_vअगर_beacon_मुक्त(काष्ठा ath10k_vअगर *arvअगर);
व्योम ath10k_drain_tx(काष्ठा ath10k *ar);
bool ath10k_mac_is_peer_wep_key_set(काष्ठा ath10k *ar, स्थिर u8 *addr,
				    u8 keyidx);
पूर्णांक ath10k_mac_vअगर_chan(काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा cfg80211_chan_def *def);

व्योम ath10k_mac_handle_beacon(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
व्योम ath10k_mac_handle_beacon_miss(काष्ठा ath10k *ar, u32 vdev_id);
व्योम ath10k_mac_handle_tx_छोड़ो_vdev(काष्ठा ath10k *ar, u32 vdev_id,
				     क्रमागत wmi_tlv_tx_छोड़ो_id छोड़ो_id,
				     क्रमागत wmi_tlv_tx_छोड़ो_action action);

u8 ath10k_mac_hw_rate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u8 hw_rate, bool cck);
u8 ath10k_mac_bitrate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u32 bitrate);

व्योम ath10k_mac_tx_lock(काष्ठा ath10k *ar, पूर्णांक reason);
व्योम ath10k_mac_tx_unlock(काष्ठा ath10k *ar, पूर्णांक reason);
व्योम ath10k_mac_vअगर_tx_lock(काष्ठा ath10k_vअगर *arvअगर, पूर्णांक reason);
व्योम ath10k_mac_vअगर_tx_unlock(काष्ठा ath10k_vअगर *arvअगर, पूर्णांक reason);
bool ath10k_mac_tx_frm_has_freq(काष्ठा ath10k *ar);
व्योम ath10k_mac_tx_push_pending(काष्ठा ath10k *ar);
पूर्णांक ath10k_mac_tx_push_txq(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_txq *txq);
काष्ठा ieee80211_txq *ath10k_mac_txq_lookup(काष्ठा ath10k *ar,
					    u16 peer_id,
					    u8 tid);
पूर्णांक ath10k_mac_ext_resource_config(काष्ठा ath10k *ar, u32 val);
व्योम ath10k_mac_रुको_tx_complete(काष्ठा ath10k *ar);
पूर्णांक ath10k_mac_rfसमाप्त_enable_radio(काष्ठा ath10k *ar, bool enable);

अटल अंतरभूत व्योम ath10k_tx_h_seq_no(काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	अगर (info->flags  & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		अगर (arvअगर->tx_seq_no == 0)
			arvअगर->tx_seq_no = 0x1000;

		अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
			arvअगर->tx_seq_no += 0x10;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(arvअगर->tx_seq_no);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _MAC_H_ */
