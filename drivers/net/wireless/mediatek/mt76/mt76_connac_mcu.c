<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt76_connac_mcu.h"

पूर्णांक mt76_connac_mcu_start_firmware(काष्ठा mt76_dev *dev, u32 addr, u32 option)
अणु
	काष्ठा अणु
		__le32 option;
		__le32 addr;
	पूर्ण req = अणु
		.option = cpu_to_le32(option),
		.addr = cpu_to_le32(addr),
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_CMD_FW_START_REQ, &req, माप(req),
				 true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_start_firmware);

पूर्णांक mt76_connac_mcu_patch_sem_ctrl(काष्ठा mt76_dev *dev, bool get)
अणु
	u32 op = get ? PATCH_SEM_GET : PATCH_SEM_RELEASE;
	काष्ठा अणु
		__le32 op;
	पूर्ण req = अणु
		.op = cpu_to_le32(op),
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_CMD_PATCH_SEM_CONTROL, &req,
				 माप(req), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_patch_sem_ctrl);

पूर्णांक mt76_connac_mcu_start_patch(काष्ठा mt76_dev *dev)
अणु
	काष्ठा अणु
		u8 check_crc;
		u8 reserved[3];
	पूर्ण req = अणु
		.check_crc = 0,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_CMD_PATCH_FINISH_REQ, &req,
				 माप(req), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_start_patch);

#घोषणा MCU_PATCH_ADDRESS	0x200000

पूर्णांक mt76_connac_mcu_init_करोwnload(काष्ठा mt76_dev *dev, u32 addr, u32 len,
				  u32 mode)
अणु
	काष्ठा अणु
		__le32 addr;
		__le32 len;
		__le32 mode;
	पूर्ण req = अणु
		.addr = cpu_to_le32(addr),
		.len = cpu_to_le32(len),
		.mode = cpu_to_le32(mode),
	पूर्ण;
	पूर्णांक cmd;

	अगर (is_mt7921(dev) &&
	    (req.addr == cpu_to_le32(MCU_PATCH_ADDRESS) || addr == 0x900000))
		cmd = MCU_CMD_PATCH_START_REQ;
	अन्यथा
		cmd = MCU_CMD_TARGET_ADDRESS_LEN_REQ;

	वापस mt76_mcu_send_msg(dev, cmd, &req, माप(req), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_init_करोwnload);

पूर्णांक mt76_connac_mcu_set_channel_करोमुख्य(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा mt76_connac_mcu_channel_करोमुख्य अणु
		u8 alpha2[4]; /* regulatory_request.alpha2 */
		u8 bw_2g; /* BW_20_40M		0
			   * BW_20M		1
			   * BW_20_40_80M	2
			   * BW_20_40_80_160M	3
			   * BW_20_40_80_8080M	4
			   */
		u8 bw_5g;
		__le16 pad;
		u8 n_2ch;
		u8 n_5ch;
		__le16 pad2;
	पूर्ण __packed hdr = अणु
		.bw_2g = 0,
		.bw_5g = 3,
	पूर्ण;
	काष्ठा mt76_connac_mcu_chan अणु
		__le16 hw_value;
		__le16 pad;
		__le32 flags;
	पूर्ण __packed channel;
	पूर्णांक len, i, n_max_channels, n_2ch = 0, n_5ch = 0;
	काष्ठा ieee80211_channel *chan;
	काष्ठा sk_buff *skb;

	n_max_channels = phy->sband_2g.sband.n_channels +
			 phy->sband_5g.sband.n_channels;
	len = माप(hdr) + n_max_channels * माप(channel);

	skb = mt76_mcu_msg_alloc(dev, शून्य, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, माप(hdr));

	क्रम (i = 0; i < phy->sband_2g.sband.n_channels; i++) अणु
		chan = &phy->sband_2g.sband.channels[i];
		अगर (chan->flags & IEEE80211_CHAN_DISABLED)
			जारी;

		channel.hw_value = cpu_to_le16(chan->hw_value);
		channel.flags = cpu_to_le32(chan->flags);
		channel.pad = 0;

		skb_put_data(skb, &channel, माप(channel));
		n_2ch++;
	पूर्ण
	क्रम (i = 0; i < phy->sband_5g.sband.n_channels; i++) अणु
		chan = &phy->sband_5g.sband.channels[i];
		अगर (chan->flags & IEEE80211_CHAN_DISABLED)
			जारी;

		channel.hw_value = cpu_to_le16(chan->hw_value);
		channel.flags = cpu_to_le32(chan->flags);
		channel.pad = 0;

		skb_put_data(skb, &channel, माप(channel));
		n_5ch++;
	पूर्ण

	BUILD_BUG_ON(माप(dev->alpha2) > माप(hdr.alpha2));
	स_नकल(hdr.alpha2, dev->alpha2, माप(dev->alpha2));
	hdr.n_2ch = n_2ch;
	hdr.n_5ch = n_5ch;

	स_नकल(__skb_push(skb, माप(hdr)), &hdr, माप(hdr));

	वापस mt76_mcu_skb_send_msg(dev, skb, MCU_CMD_SET_CHAN_DOMAIN, false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_channel_करोमुख्य);

पूर्णांक mt76_connac_mcu_set_mac_enable(काष्ठा mt76_dev *dev, पूर्णांक band, bool enable,
				   bool hdr_trans)
अणु
	काष्ठा अणु
		u8 enable;
		u8 band;
		u8 rsv[2];
	पूर्ण __packed req_mac = अणु
		.enable = enable,
		.band = band,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_EXT_CMD_MAC_INIT_CTRL, &req_mac,
				 माप(req_mac), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_mac_enable);

पूर्णांक mt76_connac_mcu_set_vअगर_ps(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		u8 bss_idx;
		u8 ps_state; /* 0: device awake
			      * 1: अटल घातer save
			      * 2: dynamic घातer saving
			      */
	पूर्ण req = अणु
		.bss_idx = mvअगर->idx,
		.ps_state = vअगर->bss_conf.ps ? 2 : 0,
	पूर्ण;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	वापस mt76_mcu_send_msg(dev, MCU_CMD_SET_PS_PROखाता, &req,
				 माप(req), false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_vअगर_ps);

पूर्णांक mt76_connac_mcu_set_rts_thresh(काष्ठा mt76_dev *dev, u32 val, u8 band)
अणु
	काष्ठा अणु
		u8 prot_idx;
		u8 band;
		u8 rsv[2];
		__le32 len_thresh;
		__le32 pkt_thresh;
	पूर्ण __packed req = अणु
		.prot_idx = 1,
		.band = band,
		.len_thresh = cpu_to_le32(val),
		.pkt_thresh = cpu_to_le32(0x2),
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_EXT_CMD_PROTECT_CTRL, &req,
				 माप(req), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_rts_thresh);

व्योम mt76_connac_mcu_beacon_loss_iter(व्योम *priv, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_connac_beacon_loss_event *event = priv;

	अगर (mvअगर->idx != event->bss_idx)
		वापस;

	अगर (!(vअगर->driver_flags & IEEE80211_VIF_BEACON_FILTER))
		वापस;

	ieee80211_beacon_loss(vअगर);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_beacon_loss_iter);

काष्ठा tlv *
mt76_connac_mcu_add_nested_tlv(काष्ठा sk_buff *skb, पूर्णांक tag, पूर्णांक len,
			       व्योम *sta_ntlv, व्योम *sta_wtbl)
अणु
	काष्ठा sta_ntlv_hdr *ntlv_hdr = sta_ntlv;
	काष्ठा tlv *sta_hdr = sta_wtbl;
	काष्ठा tlv *ptlv, tlv = अणु
		.tag = cpu_to_le16(tag),
		.len = cpu_to_le16(len),
	पूर्ण;
	u16 ntlv;

	ptlv = skb_put(skb, len);
	स_नकल(ptlv, &tlv, माप(tlv));

	ntlv = le16_to_cpu(ntlv_hdr->tlv_num);
	ntlv_hdr->tlv_num = cpu_to_le16(ntlv + 1);

	अगर (sta_hdr) अणु
		u16 size = le16_to_cpu(sta_hdr->len);

		sta_hdr->len = cpu_to_le16(size + len);
	पूर्ण

	वापस ptlv;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_add_nested_tlv);

काष्ठा sk_buff *
mt76_connac_mcu_alloc_sta_req(काष्ठा mt76_dev *dev, काष्ठा mt76_vअगर *mvअगर,
			      काष्ठा mt76_wcid *wcid)
अणु
	काष्ठा sta_req_hdr hdr = अणु
		.bss_idx = mvअगर->idx,
		.muar_idx = wcid ? mvअगर->omac_idx : 0,
		.is_tlv_append = 1,
	पूर्ण;
	काष्ठा sk_buff *skb;

	mt76_connac_mcu_get_wlan_idx(dev, wcid, &hdr.wlan_idx_lo,
				     &hdr.wlan_idx_hi);
	skb = mt76_mcu_msg_alloc(dev, शून्य, MT76_CONNAC_STA_UPDATE_MAX_SIZE);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	skb_put_data(skb, &hdr, माप(hdr));

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_alloc_sta_req);

काष्ठा wtbl_req_hdr *
mt76_connac_mcu_alloc_wtbl_req(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			       पूर्णांक cmd, व्योम *sta_wtbl, काष्ठा sk_buff **skb)
अणु
	काष्ठा tlv *sta_hdr = sta_wtbl;
	काष्ठा wtbl_req_hdr hdr = अणु
		.operation = cmd,
	पूर्ण;
	काष्ठा sk_buff *nskb = *skb;

	mt76_connac_mcu_get_wlan_idx(dev, wcid, &hdr.wlan_idx_lo,
				     &hdr.wlan_idx_hi);
	अगर (!nskb) अणु
		nskb = mt76_mcu_msg_alloc(dev, शून्य,
					  MT76_CONNAC_WTBL_UPDATE_MAX_SIZE);
		अगर (!nskb)
			वापस ERR_PTR(-ENOMEM);

		*skb = nskb;
	पूर्ण

	अगर (sta_hdr)
		sta_hdr->len = cpu_to_le16(माप(hdr));

	वापस skb_put_data(nskb, &hdr, माप(hdr));
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_alloc_wtbl_req);

व्योम mt76_connac_mcu_sta_basic_tlv(काष्ठा sk_buff *skb,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   bool enable)
अणु
	काष्ठा sta_rec_basic *basic;
	काष्ठा tlv *tlv;
	पूर्णांक conn_type;

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_BASIC, माप(*basic));

	basic = (काष्ठा sta_rec_basic *)tlv;
	basic->extra_info = cpu_to_le16(EXTRA_INFO_VER);

	अगर (enable) अणु
		basic->extra_info |= cpu_to_le16(EXTRA_INFO_NEW);
		basic->conn_state = CONN_STATE_PORT_SECURE;
	पूर्ण अन्यथा अणु
		basic->conn_state = CONN_STATE_DISCONNECT;
	पूर्ण

	अगर (!sta) अणु
		basic->conn_type = cpu_to_le32(CONNECTION_INFRA_BC);
		eth_broadcast_addr(basic->peer_addr);
		वापस;
	पूर्ण

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		अगर (vअगर->p2p)
			conn_type = CONNECTION_P2P_GC;
		अन्यथा
			conn_type = CONNECTION_INFRA_STA;
		basic->conn_type = cpu_to_le32(conn_type);
		basic->aid = cpu_to_le16(sta->aid);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (vअगर->p2p)
			conn_type = CONNECTION_P2P_GO;
		अन्यथा
			conn_type = CONNECTION_INFRA_AP;
		basic->conn_type = cpu_to_le32(conn_type);
		basic->aid = cpu_to_le16(vअगर->bss_conf.aid);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		basic->conn_type = cpu_to_le32(CONNECTION_IBSS_ADHOC);
		basic->aid = cpu_to_le16(sta->aid);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	स_नकल(basic->peer_addr, sta->addr, ETH_ALEN);
	basic->qos = sta->wme;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_sta_basic_tlv);

अटल व्योम
mt76_connac_mcu_sta_uapsd(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा sta_rec_uapsd *uapsd;
	काष्ठा tlv *tlv;

	अगर (vअगर->type != NL80211_IFTYPE_AP || !sta->wme)
		वापस;

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_APPS, माप(*uapsd));
	uapsd = (काष्ठा sta_rec_uapsd *)tlv;

	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO) अणु
		uapsd->dac_map |= BIT(3);
		uapsd->tac_map |= BIT(3);
	पूर्ण
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI) अणु
		uapsd->dac_map |= BIT(2);
		uapsd->tac_map |= BIT(2);
	पूर्ण
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE) अणु
		uapsd->dac_map |= BIT(1);
		uapsd->tac_map |= BIT(1);
	पूर्ण
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK) अणु
		uapsd->dac_map |= BIT(0);
		uapsd->tac_map |= BIT(0);
	पूर्ण
	uapsd->max_sp = sta->max_sp;
पूर्ण

व्योम mt76_connac_mcu_wtbl_hdr_trans_tlv(काष्ठा sk_buff *skb,
					काष्ठा mt76_wcid *wcid,
					व्योम *sta_wtbl, व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_hdr_trans *htr;
	काष्ठा tlv *tlv;

	tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_HDR_TRANS,
					     माप(*htr),
					     wtbl_tlv, sta_wtbl);
	htr = (काष्ठा wtbl_hdr_trans *)tlv;
	htr->no_rx_trans = !test_bit(MT_WCID_FLAG_HDR_TRANS, &wcid->flags);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_wtbl_hdr_trans_tlv);

व्योम mt76_connac_mcu_wtbl_generic_tlv(काष्ठा mt76_dev *dev,
				      काष्ठा sk_buff *skb,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      व्योम *sta_wtbl, व्योम *wtbl_tlv)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा wtbl_generic *generic;
	काष्ठा wtbl_rx *rx;
	काष्ठा wtbl_spe *spe;
	काष्ठा tlv *tlv;

	tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_GENERIC,
					     माप(*generic),
					     wtbl_tlv, sta_wtbl);

	generic = (काष्ठा wtbl_generic *)tlv;

	अगर (sta) अणु
		अगर (vअगर->type == NL80211_IFTYPE_STATION)
			generic->partial_aid = cpu_to_le16(vअगर->bss_conf.aid);
		अन्यथा
			generic->partial_aid = cpu_to_le16(sta->aid);
		स_नकल(generic->peer_addr, sta->addr, ETH_ALEN);
		generic->muar_idx = mvअगर->omac_idx;
		generic->qos = sta->wme;
	पूर्ण अन्यथा अणु
		अगर (is_mt7921(dev) &&
		    vअगर->type == NL80211_IFTYPE_STATION)
			स_नकल(generic->peer_addr, vअगर->bss_conf.bssid,
			       ETH_ALEN);
		अन्यथा
			eth_broadcast_addr(generic->peer_addr);

		generic->muar_idx = 0xe;
	पूर्ण

	tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_RX, माप(*rx),
					     wtbl_tlv, sta_wtbl);

	rx = (काष्ठा wtbl_rx *)tlv;
	rx->rca1 = sta ? vअगर->type != NL80211_IFTYPE_AP : 1;
	rx->rca2 = 1;
	rx->rv = 1;

	अगर (is_mt7921(dev))
		वापस;

	tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_SPE, माप(*spe),
					     wtbl_tlv, sta_wtbl);
	spe = (काष्ठा wtbl_spe *)tlv;
	spe->spe_idx = 24;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_wtbl_generic_tlv);

अटल व्योम
mt76_connac_mcu_sta_amsdu_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	काष्ठा sta_rec_amsdu *amsdu;
	काष्ठा tlv *tlv;

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!sta->max_amsdu_len)
		वापस;

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_HW_AMSDU, माप(*amsdu));
	amsdu = (काष्ठा sta_rec_amsdu *)tlv;
	amsdu->max_amsdu_num = 8;
	amsdu->amsdu_en = true;
	amsdu->max_mpdu_size = sta->max_amsdu_len >=
			       IEEE80211_MAX_MPDU_LEN_VHT_7991;

	wcid->amsdu = true;
पूर्ण

#घोषणा HE_PHY(p, c)	u8_get_bits(c, IEEE80211_HE_PHY_##p)
#घोषणा HE_MAC(m, c)	u8_get_bits(c, IEEE80211_HE_MAC_##m)
अटल व्योम
mt76_connac_mcu_sta_he_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	काष्ठा ieee80211_he_cap_elem *elem = &he_cap->he_cap_elem;
	काष्ठा sta_rec_he *he;
	काष्ठा tlv *tlv;
	u32 cap = 0;

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_HE, माप(*he));

	he = (काष्ठा sta_rec_he *)tlv;

	अगर (elem->mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_HTC_HE)
		cap |= STA_REC_HE_CAP_HTC;

	अगर (elem->mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSR)
		cap |= STA_REC_HE_CAP_BSR;

	अगर (elem->mac_cap_info[3] & IEEE80211_HE_MAC_CAP3_OMI_CONTROL)
		cap |= STA_REC_HE_CAP_OM;

	अगर (elem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU)
		cap |= STA_REC_HE_CAP_AMSDU_IN_AMPDU;

	अगर (elem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQR)
		cap |= STA_REC_HE_CAP_BQR;

	अगर (elem->phy_cap_info[0] &
	    (IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_2G |
	     IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_5G))
		cap |= STA_REC_HE_CAP_BW20_RU242_SUPPORT;

	अगर (elem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD)
		cap |= STA_REC_HE_CAP_LDPC;

	अगर (elem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_HE_LTF_AND_GI_FOR_HE_PPDUS_0_8US)
		cap |= STA_REC_HE_CAP_SU_PPDU_1LTF_8US_GI;

	अगर (elem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US)
		cap |= STA_REC_HE_CAP_NDP_4LTF_3DOT2MS_GI;

	अगर (elem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_TX_UNDER_80MHZ)
		cap |= STA_REC_HE_CAP_LE_EQ_80M_TX_STBC;

	अगर (elem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ)
		cap |= STA_REC_HE_CAP_LE_EQ_80M_RX_STBC;

	अगर (elem->phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PARTIAL_BW_EXT_RANGE)
		cap |= STA_REC_HE_CAP_PARTIAL_BW_EXT_RANGE;

	अगर (elem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XLTF_AND_08_US_GI)
		cap |= STA_REC_HE_CAP_SU_MU_PPDU_4LTF_8US_GI;

	अगर (elem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ)
		cap |= STA_REC_HE_CAP_GT_80M_TX_STBC;

	अगर (elem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_RX_ABOVE_80MHZ)
		cap |= STA_REC_HE_CAP_GT_80M_RX_STBC;

	अगर (elem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI)
		cap |= STA_REC_HE_CAP_ER_SU_PPDU_4LTF_8US_GI;

	अगर (elem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_ER_SU_1XLTF_AND_08_US_GI)
		cap |= STA_REC_HE_CAP_ER_SU_PPDU_1LTF_8US_GI;

	अगर (elem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK)
		cap |= STA_REC_HE_CAP_TRIG_CQI_FK;

	अगर (elem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU)
		cap |= STA_REC_HE_CAP_TX_1024QAM_UNDER_RU242;

	अगर (elem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU)
		cap |= STA_REC_HE_CAP_RX_1024QAM_UNDER_RU242;

	he->he_cap = cpu_to_le32(cap);

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
		अगर (elem->phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G)
			he->max_nss_mcs[CMD_HE_MCS_BW8080] =
				he_cap->he_mcs_nss_supp.rx_mcs_80p80;

		he->max_nss_mcs[CMD_HE_MCS_BW160] =
				he_cap->he_mcs_nss_supp.rx_mcs_160;
		fallthrough;
	शेष:
		he->max_nss_mcs[CMD_HE_MCS_BW80] =
				he_cap->he_mcs_nss_supp.rx_mcs_80;
		अवरोध;
	पूर्ण

	he->t_frame_dur =
		HE_MAC(CAP1_TF_MAC_PAD_DUR_MASK, elem->mac_cap_info[1]);
	he->max_ampdu_exp =
		HE_MAC(CAP3_MAX_AMPDU_LEN_EXP_MASK, elem->mac_cap_info[3]);

	he->bw_set =
		HE_PHY(CAP0_CHANNEL_WIDTH_SET_MASK, elem->phy_cap_info[0]);
	he->device_class =
		HE_PHY(CAP1_DEVICE_CLASS_A, elem->phy_cap_info[1]);
	he->punc_pream_rx =
		HE_PHY(CAP1_PREAMBLE_PUNC_RX_MASK, elem->phy_cap_info[1]);

	he->dcm_tx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_TX_MASK, elem->phy_cap_info[3]);
	he->dcm_tx_max_nss =
		HE_PHY(CAP3_DCM_MAX_TX_NSS_2, elem->phy_cap_info[3]);
	he->dcm_rx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_RX_MASK, elem->phy_cap_info[3]);
	he->dcm_rx_max_nss =
		HE_PHY(CAP3_DCM_MAX_RX_NSS_2, elem->phy_cap_info[3]);
	he->dcm_rx_max_nss =
		HE_PHY(CAP8_DCM_MAX_RU_MASK, elem->phy_cap_info[8]);

	he->pkt_ext = 2;
पूर्ण

अटल u8
mt76_connac_get_phy_mode_v2(काष्ठा mt76_phy *mphy, काष्ठा ieee80211_vअगर *vअगर,
			    क्रमागत nl80211_band band, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	u8 mode = 0;

	अगर (sta) अणु
		ht_cap = &sta->ht_cap;
		vht_cap = &sta->vht_cap;
		he_cap = &sta->he_cap;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = mphy->hw->wiphy->bands[band];
		ht_cap = &sband->ht_cap;
		vht_cap = &sband->vht_cap;
		he_cap = ieee80211_get_he_अगरtype_cap(sband, vअगर->type);
	पूर्ण

	अगर (band == NL80211_BAND_2GHZ) अणु
		mode |= PHY_TYPE_BIT_HR_DSSS | PHY_TYPE_BIT_ERP;

		अगर (ht_cap->ht_supported)
			mode |= PHY_TYPE_BIT_HT;

		अगर (he_cap->has_he)
			mode |= PHY_TYPE_BIT_HE;
	पूर्ण अन्यथा अगर (band == NL80211_BAND_5GHZ) अणु
		mode |= PHY_TYPE_BIT_OFDM;

		अगर (ht_cap->ht_supported)
			mode |= PHY_TYPE_BIT_HT;

		अगर (vht_cap->vht_supported)
			mode |= PHY_TYPE_BIT_VHT;

		अगर (he_cap->has_he)
			mode |= PHY_TYPE_BIT_HE;
	पूर्ण

	वापस mode;
पूर्ण

व्योम mt76_connac_mcu_sta_tlv(काष्ठा mt76_phy *mphy, काष्ठा sk_buff *skb,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_vअगर *vअगर,
			     u8 rcpi)
अणु
	काष्ठा cfg80211_chan_def *chandef = &mphy->chandef;
	क्रमागत nl80211_band band = chandef->chan->band;
	काष्ठा mt76_dev *dev = mphy->dev;
	काष्ठा sta_rec_ra_info *ra_info;
	काष्ठा sta_rec_state *state;
	काष्ठा sta_rec_phy *phy;
	काष्ठा tlv *tlv;

	/* starec ht */
	अगर (sta->ht_cap.ht_supported) अणु
		काष्ठा sta_rec_ht *ht;

		tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_HT, माप(*ht));
		ht = (काष्ठा sta_rec_ht *)tlv;
		ht->ht_cap = cpu_to_le16(sta->ht_cap.cap);
	पूर्ण

	/* starec vht */
	अगर (sta->vht_cap.vht_supported) अणु
		काष्ठा sta_rec_vht *vht;
		पूर्णांक len;

		len = is_mt7921(dev) ? माप(*vht) : माप(*vht) - 4;
		tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_VHT, len);
		vht = (काष्ठा sta_rec_vht *)tlv;
		vht->vht_cap = cpu_to_le32(sta->vht_cap.cap);
		vht->vht_rx_mcs_map = sta->vht_cap.vht_mcs.rx_mcs_map;
		vht->vht_tx_mcs_map = sta->vht_cap.vht_mcs.tx_mcs_map;
	पूर्ण

	/* starec uapsd */
	mt76_connac_mcu_sta_uapsd(skb, vअगर, sta);

	अगर (!is_mt7921(dev))
		वापस;

	अगर (sta->ht_cap.ht_supported)
		mt76_connac_mcu_sta_amsdu_tlv(skb, sta, vअगर);

	/* starec he */
	अगर (sta->he_cap.has_he)
		mt76_connac_mcu_sta_he_tlv(skb, sta);

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_PHY, माप(*phy));
	phy = (काष्ठा sta_rec_phy *)tlv;
	phy->phy_type = mt76_connac_get_phy_mode_v2(mphy, vअगर, band, sta);
	phy->basic_rate = cpu_to_le16((u16)vअगर->bss_conf.basic_rates);
	phy->rcpi = rcpi;
	phy->ampdu = FIELD_PREP(IEEE80211_HT_AMPDU_PARM_FACTOR,
				sta->ht_cap.ampdu_factor) |
		     FIELD_PREP(IEEE80211_HT_AMPDU_PARM_DENSITY,
				sta->ht_cap.ampdu_density);

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_RA, माप(*ra_info));
	ra_info = (काष्ठा sta_rec_ra_info *)tlv;
	ra_info->legacy = cpu_to_le16((u16)sta->supp_rates[band]);

	अगर (sta->ht_cap.ht_supported)
		स_नकल(ra_info->rx_mcs_biपंचांगask, sta->ht_cap.mcs.rx_mask,
		       HT_MCS_MASK_NUM);

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_STATE, माप(*state));
	state = (काष्ठा sta_rec_state *)tlv;
	state->state = 2;

	अगर (sta->vht_cap.vht_supported) अणु
		state->vht_opmode = sta->bandwidth;
		state->vht_opmode |= (sta->rx_nss - 1) <<
			IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_sta_tlv);

अटल व्योम
mt76_connac_mcu_wtbl_smps_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta,
			      व्योम *sta_wtbl, व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_smps *smps;
	काष्ठा tlv *tlv;

	tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_SMPS, माप(*smps),
					     wtbl_tlv, sta_wtbl);
	smps = (काष्ठा wtbl_smps *)tlv;

	अगर (sta->smps_mode == IEEE80211_SMPS_DYNAMIC)
		smps->smps = true;
पूर्ण

व्योम mt76_connac_mcu_wtbl_ht_tlv(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_sta *sta, व्योम *sta_wtbl,
				 व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_ht *ht = शून्य;
	काष्ठा tlv *tlv;
	u32 flags = 0;

	अगर (sta->ht_cap.ht_supported) अणु
		tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_HT, माप(*ht),
						     wtbl_tlv, sta_wtbl);
		ht = (काष्ठा wtbl_ht *)tlv;
		ht->ldpc = !!(sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING);
		ht->af = sta->ht_cap.ampdu_factor;
		ht->mm = sta->ht_cap.ampdu_density;
		ht->ht = true;
	पूर्ण

	अगर (sta->vht_cap.vht_supported) अणु
		काष्ठा wtbl_vht *vht;
		u8 af;

		tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_VHT,
						     माप(*vht), wtbl_tlv,
						     sta_wtbl);
		vht = (काष्ठा wtbl_vht *)tlv;
		vht->ldpc = !!(sta->vht_cap.cap & IEEE80211_VHT_CAP_RXLDPC);
		vht->vht = true;

		af = FIELD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK,
			       sta->vht_cap.cap);
		अगर (ht)
			ht->af = max(ht->af, af);
	पूर्ण

	mt76_connac_mcu_wtbl_smps_tlv(skb, sta, sta_wtbl, wtbl_tlv);

	अगर (!is_mt7921(dev) && sta->ht_cap.ht_supported) अणु
		/* sgi */
		u32 msk = MT_WTBL_W5_SHORT_GI_20 | MT_WTBL_W5_SHORT_GI_40 |
			  MT_WTBL_W5_SHORT_GI_80 | MT_WTBL_W5_SHORT_GI_160;
		काष्ठा wtbl_raw *raw;

		tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_RAW_DATA,
						     माप(*raw), wtbl_tlv,
						     sta_wtbl);

		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
			flags |= MT_WTBL_W5_SHORT_GI_20;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
			flags |= MT_WTBL_W5_SHORT_GI_40;

		अगर (sta->vht_cap.vht_supported) अणु
			अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80)
				flags |= MT_WTBL_W5_SHORT_GI_80;
			अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_160)
				flags |= MT_WTBL_W5_SHORT_GI_160;
		पूर्ण
		raw = (काष्ठा wtbl_raw *)tlv;
		raw->val = cpu_to_le32(flags);
		raw->msk = cpu_to_le32(~msk);
		raw->wtbl_idx = 1;
		raw->dw = 5;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_wtbl_ht_tlv);

पूर्णांक mt76_connac_mcu_add_sta_cmd(काष्ठा mt76_phy *phy,
				काष्ठा mt76_sta_cmd_info *info)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)info->vअगर->drv_priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;

	skb = mt76_connac_mcu_alloc_sta_req(dev, mvअगर, info->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt76_connac_mcu_sta_basic_tlv(skb, info->vअगर, info->sta, info->enable);
	अगर (info->enable && info->sta)
		mt76_connac_mcu_sta_tlv(phy, skb, info->sta, info->vअगर,
					info->rcpi);

	sta_wtbl = mt76_connac_mcu_add_tlv(skb, STA_REC_WTBL,
					   माप(काष्ठा tlv));

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(dev, info->wcid,
						  WTBL_RESET_AND_SET,
						  sta_wtbl, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	अगर (info->enable) अणु
		mt76_connac_mcu_wtbl_generic_tlv(dev, skb, info->vअगर,
						 info->sta, sta_wtbl,
						 wtbl_hdr);
		अगर (info->sta)
			mt76_connac_mcu_wtbl_ht_tlv(dev, skb, info->sta,
						    sta_wtbl, wtbl_hdr);
	पूर्ण

	वापस mt76_mcu_skb_send_msg(dev, skb, info->cmd, true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_add_sta_cmd);

व्योम mt76_connac_mcu_wtbl_ba_tlv(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_ampdu_params *params,
				 bool enable, bool tx, व्योम *sta_wtbl,
				 व्योम *wtbl_tlv)
अणु
	काष्ठा wtbl_ba *ba;
	काष्ठा tlv *tlv;

	tlv = mt76_connac_mcu_add_nested_tlv(skb, WTBL_BA, माप(*ba),
					     wtbl_tlv, sta_wtbl);

	ba = (काष्ठा wtbl_ba *)tlv;
	ba->tid = params->tid;

	अगर (tx) अणु
		ba->ba_type = MT_BA_TYPE_ORIGINATOR;
		ba->sn = enable ? cpu_to_le16(params->ssn) : 0;
		ba->ba_winsize = enable ? cpu_to_le16(params->buf_size) : 0;
		ba->ba_en = enable;
	पूर्ण अन्यथा अणु
		स_नकल(ba->peer_addr, params->sta->addr, ETH_ALEN);
		ba->ba_type = MT_BA_TYPE_RECIPIENT;
		ba->rst_ba_tid = params->tid;
		ba->rst_ba_sel = RST_BA_MAC_TID_MATCH;
		ba->rst_ba_sb = 1;
	पूर्ण

	अगर (is_mt7921(dev))
		वापस;

	अगर (enable && tx) अणु
		u8 ba_range[] = अणु 4, 8, 12, 24, 36, 48, 54, 64 पूर्ण;
		पूर्णांक i;

		क्रम (i = 7; i > 0; i--) अणु
			अगर (params->buf_size >= ba_range[i])
				अवरोध;
		पूर्ण
		ba->ba_winsize_idx = i;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_wtbl_ba_tlv);

पूर्णांक mt76_connac_mcu_uni_add_dev(काष्ठा mt76_phy *phy,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा mt76_wcid *wcid,
				bool enable)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा अणु
		काष्ठा अणु
			u8 omac_idx;
			u8 band_idx;
			__le16 pad;
		पूर्ण __packed hdr;
		काष्ठा req_tlv अणु
			__le16 tag;
			__le16 len;
			u8 active;
			u8 pad;
			u8 omac_addr[ETH_ALEN];
		पूर्ण __packed tlv;
	पूर्ण dev_req = अणु
		.hdr = अणु
			.omac_idx = mvअगर->omac_idx,
			.band_idx = mvअगर->band_idx,
		पूर्ण,
		.tlv = अणु
			.tag = cpu_to_le16(DEV_INFO_ACTIVE),
			.len = cpu_to_le16(माप(काष्ठा req_tlv)),
			.active = enable,
		पूर्ण,
	पूर्ण;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_bss_basic_tlv basic;
	पूर्ण basic_req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.basic = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_BASIC),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_bss_basic_tlv)),
			.omac_idx = mvअगर->omac_idx,
			.band_idx = mvअगर->band_idx,
			.wmm_idx = mvअगर->wmm_idx,
			.active = enable,
			.bmc_tx_wlan_idx = cpu_to_le16(wcid->idx),
			.sta_idx = cpu_to_le16(wcid->idx),
			.conn_state = 1,
		पूर्ण,
	पूर्ण;
	पूर्णांक err, idx, cmd, len;
	व्योम *data;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_AP:
		basic_req.basic.conn_type = cpu_to_le32(CONNECTION_INFRA_AP);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		basic_req.basic.conn_type = cpu_to_le32(CONNECTION_INFRA_STA);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		basic_req.basic.conn_type = cpu_to_le32(CONNECTION_IBSS_ADHOC);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	idx = mvअगर->omac_idx > EXT_BSSID_START ? HW_BSSID_0 : mvअगर->omac_idx;
	basic_req.basic.hw_bss_idx = idx;

	स_नकल(dev_req.tlv.omac_addr, vअगर->addr, ETH_ALEN);

	cmd = enable ? MCU_UNI_CMD_DEV_INFO_UPDATE : MCU_UNI_CMD_BSS_INFO_UPDATE;
	data = enable ? (व्योम *)&dev_req : (व्योम *)&basic_req;
	len = enable ? माप(dev_req) : माप(basic_req);

	err = mt76_mcu_send_msg(dev, cmd, data, len, true);
	अगर (err < 0)
		वापस err;

	cmd = enable ? MCU_UNI_CMD_BSS_INFO_UPDATE : MCU_UNI_CMD_DEV_INFO_UPDATE;
	data = enable ? (व्योम *)&basic_req : (व्योम *)&dev_req;
	len = enable ? माप(basic_req) : माप(dev_req);

	वापस mt76_mcu_send_msg(dev, cmd, data, len, true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_uni_add_dev);

व्योम mt76_connac_mcu_sta_ba_tlv(काष्ठा sk_buff *skb,
				काष्ठा ieee80211_ampdu_params *params,
				bool enable, bool tx)
अणु
	काष्ठा sta_rec_ba *ba;
	काष्ठा tlv *tlv;

	tlv = mt76_connac_mcu_add_tlv(skb, STA_REC_BA, माप(*ba));

	ba = (काष्ठा sta_rec_ba *)tlv;
	ba->ba_type = tx ? MT_BA_TYPE_ORIGINATOR : MT_BA_TYPE_RECIPIENT;
	ba->winsize = cpu_to_le16(params->buf_size);
	ba->ssn = cpu_to_le16(params->ssn);
	ba->ba_en = enable << params->tid;
	ba->amsdu = params->amsdu;
	ba->tid = params->tid;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_sta_ba_tlv);

पूर्णांक mt76_connac_mcu_sta_ba(काष्ठा mt76_dev *dev, काष्ठा mt76_vअगर *mvअगर,
			   काष्ठा ieee80211_ampdu_params *params,
			   bool enable, bool tx)
अणु
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)params->sta->drv_priv;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = mt76_connac_mcu_alloc_sta_req(dev, mvअगर, wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	sta_wtbl = mt76_connac_mcu_add_tlv(skb, STA_REC_WTBL,
					   माप(काष्ठा tlv));

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(dev, wcid, WTBL_SET,
						  sta_wtbl, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt76_connac_mcu_wtbl_ba_tlv(dev, skb, params, enable, tx, sta_wtbl,
				    wtbl_hdr);

	ret = mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD_STA_REC_UPDATE, true);
	अगर (ret)
		वापस ret;

	skb = mt76_connac_mcu_alloc_sta_req(dev, mvअगर, wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt76_connac_mcu_sta_ba_tlv(skb, params, enable, tx);

	वापस mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD_STA_REC_UPDATE,
				     true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_sta_ba);

अटल u8
mt76_connac_get_phy_mode(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			 क्रमागत nl80211_band band,
			 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	u8 mode = 0;

	अगर (!is_mt7921(dev))
		वापस 0x38;

	अगर (sta) अणु
		ht_cap = &sta->ht_cap;
		vht_cap = &sta->vht_cap;
		he_cap = &sta->he_cap;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = phy->hw->wiphy->bands[band];
		ht_cap = &sband->ht_cap;
		vht_cap = &sband->vht_cap;
		he_cap = ieee80211_get_he_अगरtype_cap(sband, vअगर->type);
	पूर्ण

	अगर (band == NL80211_BAND_2GHZ) अणु
		mode |= PHY_MODE_B | PHY_MODE_G;

		अगर (ht_cap->ht_supported)
			mode |= PHY_MODE_GN;

		अगर (he_cap->has_he)
			mode |= PHY_MODE_AX_24G;
	पूर्ण अन्यथा अगर (band == NL80211_BAND_5GHZ) अणु
		mode |= PHY_MODE_A;

		अगर (ht_cap->ht_supported)
			mode |= PHY_MODE_AN;

		अगर (vht_cap->vht_supported)
			mode |= PHY_MODE_AC;

		अगर (he_cap->has_he)
			mode |= PHY_MODE_AX_5G;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा ieee80211_sta_he_cap *
mt76_connac_get_he_phy_cap(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर)
अणु
	क्रमागत nl80211_band band = phy->chandef.chan->band;
	काष्ठा ieee80211_supported_band *sband;

	sband = phy->hw->wiphy->bands[band];

	वापस ieee80211_get_he_अगरtype_cap(sband, vअगर->type);
पूर्ण

#घोषणा DEFAULT_HE_PE_DURATION		4
#घोषणा DEFAULT_HE_DURATION_RTS_THRES	1023
अटल व्योम
mt76_connac_mcu_uni_bss_he_tlv(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा tlv *tlv)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *cap;
	काष्ठा bss_info_uni_he *he;

	cap = mt76_connac_get_he_phy_cap(phy, vअगर);

	he = (काष्ठा bss_info_uni_he *)tlv;
	he->he_pe_duration = vअगर->bss_conf.htc_trig_based_pkt_ext;
	अगर (!he->he_pe_duration)
		he->he_pe_duration = DEFAULT_HE_PE_DURATION;

	he->he_rts_thres = cpu_to_le16(vअगर->bss_conf.frame_समय_rts_th);
	अगर (!he->he_rts_thres)
		he->he_rts_thres = cpu_to_le16(DEFAULT_HE_DURATION_RTS_THRES);

	he->max_nss_mcs[CMD_HE_MCS_BW80] = cap->he_mcs_nss_supp.tx_mcs_80;
	he->max_nss_mcs[CMD_HE_MCS_BW160] = cap->he_mcs_nss_supp.tx_mcs_160;
	he->max_nss_mcs[CMD_HE_MCS_BW8080] = cap->he_mcs_nss_supp.tx_mcs_80p80;
पूर्ण

पूर्णांक mt76_connac_mcu_uni_add_bss(काष्ठा mt76_phy *phy,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा mt76_wcid *wcid,
				bool enable)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def *chandef = &phy->chandef;
	पूर्णांक freq1 = chandef->center_freq1, freq2 = chandef->center_freq2;
	क्रमागत nl80211_band band = chandef->chan->band;
	काष्ठा mt76_dev *mdev = phy->dev;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_bss_basic_tlv basic;
		काष्ठा mt76_connac_bss_qos_tlv qos;
	पूर्ण basic_req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.basic = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_BASIC),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_bss_basic_tlv)),
			.bcn_पूर्णांकerval = cpu_to_le16(vअगर->bss_conf.beacon_पूर्णांक),
			.dtim_period = vअगर->bss_conf.dtim_period,
			.omac_idx = mvअगर->omac_idx,
			.band_idx = mvअगर->band_idx,
			.wmm_idx = mvअगर->wmm_idx,
			.active = true, /* keep bss deactivated */
			.phymode = mt76_connac_get_phy_mode(phy, vअगर, band, शून्य),
		पूर्ण,
		.qos = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_QBSS),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_bss_qos_tlv)),
			.qos = vअगर->bss_conf.qos,
		पूर्ण,
	पूर्ण;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा rlm_tlv अणु
			__le16 tag;
			__le16 len;
			u8 control_channel;
			u8 center_chan;
			u8 center_chan2;
			u8 bw;
			u8 tx_streams;
			u8 rx_streams;
			u8 लघु_st;
			u8 ht_op_info;
			u8 sco;
			u8 pad[3];
		पूर्ण __packed rlm;
	पूर्ण __packed rlm_req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.rlm = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_RLM),
			.len = cpu_to_le16(माप(काष्ठा rlm_tlv)),
			.control_channel = chandef->chan->hw_value,
			.center_chan = ieee80211_frequency_to_channel(freq1),
			.center_chan2 = ieee80211_frequency_to_channel(freq2),
			.tx_streams = hweight8(phy->antenna_mask),
			.ht_op_info = 4, /* set HT 40M allowed */
			.rx_streams = phy->chainmask,
			.लघु_st = true,
		पूर्ण,
	पूर्ण;
	पूर्णांक err, conn_type;
	u8 idx;

	idx = mvअगर->omac_idx > EXT_BSSID_START ? HW_BSSID_0 : mvअगर->omac_idx;
	basic_req.basic.hw_bss_idx = idx;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		अगर (vअगर->p2p)
			conn_type = CONNECTION_P2P_GO;
		अन्यथा
			conn_type = CONNECTION_INFRA_AP;
		basic_req.basic.conn_type = cpu_to_le32(conn_type);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (vअगर->p2p)
			conn_type = CONNECTION_P2P_GC;
		अन्यथा
			conn_type = CONNECTION_INFRA_STA;
		basic_req.basic.conn_type = cpu_to_le32(conn_type);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		basic_req.basic.conn_type = cpu_to_le32(CONNECTION_IBSS_ADHOC);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	स_नकल(basic_req.basic.bssid, vअगर->bss_conf.bssid, ETH_ALEN);
	basic_req.basic.bmc_tx_wlan_idx = cpu_to_le16(wcid->idx);
	basic_req.basic.sta_idx = cpu_to_le16(wcid->idx);
	basic_req.basic.conn_state = !enable;

	err = mt76_mcu_send_msg(mdev, MCU_UNI_CMD_BSS_INFO_UPDATE, &basic_req,
				माप(basic_req), true);
	अगर (err < 0)
		वापस err;

	अगर (vअगर->bss_conf.he_support) अणु
		काष्ठा अणु
			काष्ठा अणु
				u8 bss_idx;
				u8 pad[3];
			पूर्ण __packed hdr;
			काष्ठा bss_info_uni_he he;
		पूर्ण he_req = अणु
			.hdr = अणु
				.bss_idx = mvअगर->idx,
			पूर्ण,
			.he = अणु
				.tag = cpu_to_le16(UNI_BSS_INFO_HE_BASIC),
				.len = cpu_to_le16(माप(काष्ठा bss_info_uni_he)),
			पूर्ण,
		पूर्ण;

		mt76_connac_mcu_uni_bss_he_tlv(phy, vअगर,
					       (काष्ठा tlv *)&he_req.he);
		err = mt76_mcu_send_msg(mdev, MCU_UNI_CMD_BSS_INFO_UPDATE,
					&he_req, माप(he_req), true);
		अगर (err < 0)
			वापस err;
	पूर्ण

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		rlm_req.rlm.bw = CMD_CBW_40MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		rlm_req.rlm.bw = CMD_CBW_80MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		rlm_req.rlm.bw = CMD_CBW_8080MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		rlm_req.rlm.bw = CMD_CBW_160MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
		rlm_req.rlm.bw = CMD_CBW_5MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		rlm_req.rlm.bw = CMD_CBW_10MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
	शेष:
		rlm_req.rlm.bw = CMD_CBW_20MHZ;
		rlm_req.rlm.ht_op_info = 0;
		अवरोध;
	पूर्ण

	अगर (rlm_req.rlm.control_channel < rlm_req.rlm.center_chan)
		rlm_req.rlm.sco = 1; /* SCA */
	अन्यथा अगर (rlm_req.rlm.control_channel > rlm_req.rlm.center_chan)
		rlm_req.rlm.sco = 3; /* SCB */

	वापस mt76_mcu_send_msg(mdev, MCU_UNI_CMD_BSS_INFO_UPDATE, &rlm_req,
				 माप(rlm_req), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_uni_add_bss);

#घोषणा MT76_CONNAC_SCAN_CHANNEL_TIME		60
पूर्णांक mt76_connac_mcu_hw_scan(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_scan_request *scan_req)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा cfg80211_scan_request *sreq = &scan_req->req;
	पूर्णांक n_ssids = 0, err, i, duration;
	पूर्णांक ext_channels_num = max_t(पूर्णांक, sreq->n_channels - 32, 0);
	काष्ठा ieee80211_channel **scan_list = sreq->channels;
	काष्ठा mt76_dev *mdev = phy->dev;
	bool ext_phy = phy == mdev->phy2;
	काष्ठा mt76_connac_mcu_scan_channel *chan;
	काष्ठा mt76_connac_hw_scan_req *req;
	काष्ठा sk_buff *skb;

	skb = mt76_mcu_msg_alloc(mdev, शून्य, माप(*req));
	अगर (!skb)
		वापस -ENOMEM;

	set_bit(MT76_HW_SCANNING, &phy->state);
	mvअगर->scan_seq_num = (mvअगर->scan_seq_num + 1) & 0x7f;

	req = (काष्ठा mt76_connac_hw_scan_req *)skb_put(skb, माप(*req));

	req->seq_num = mvअगर->scan_seq_num | ext_phy << 7;
	req->bss_idx = mvअगर->idx;
	req->scan_type = sreq->n_ssids ? 1 : 0;
	req->probe_req_num = sreq->n_ssids ? 2 : 0;
	req->version = 1;

	क्रम (i = 0; i < sreq->n_ssids; i++) अणु
		अगर (!sreq->ssids[i].ssid_len)
			जारी;

		req->ssids[i].ssid_len = cpu_to_le32(sreq->ssids[i].ssid_len);
		स_नकल(req->ssids[i].ssid, sreq->ssids[i].ssid,
		       sreq->ssids[i].ssid_len);
		n_ssids++;
	पूर्ण
	req->ssid_type = n_ssids ? BIT(2) : BIT(0);
	req->ssid_type_ext = n_ssids ? BIT(0) : 0;
	req->ssids_num = n_ssids;

	duration = is_mt7921(phy->dev) ? 0 : MT76_CONNAC_SCAN_CHANNEL_TIME;
	/* increase channel समय क्रम passive scan */
	अगर (!sreq->n_ssids)
		duration *= 2;
	req->समयout_value = cpu_to_le16(sreq->n_channels * duration);
	req->channel_min_dwell_समय = cpu_to_le16(duration);
	req->channel_dwell_समय = cpu_to_le16(duration);

	req->channels_num = min_t(u8, sreq->n_channels, 32);
	req->ext_channels_num = min_t(u8, ext_channels_num, 32);
	क्रम (i = 0; i < req->channels_num + req->ext_channels_num; i++) अणु
		अगर (i >= 32)
			chan = &req->ext_channels[i - 32];
		अन्यथा
			chan = &req->channels[i];

		chan->band = scan_list[i]->band == NL80211_BAND_2GHZ ? 1 : 2;
		chan->channel_num = scan_list[i]->hw_value;
	पूर्ण
	req->channel_type = sreq->n_channels ? 4 : 0;

	अगर (sreq->ie_len > 0) अणु
		स_नकल(req->ies, sreq->ie, sreq->ie_len);
		req->ies_len = cpu_to_le16(sreq->ie_len);
	पूर्ण

	अगर (is_mt7921(phy->dev))
		req->scan_func |= SCAN_FUNC_SPLIT_SCAN;

	स_नकल(req->bssid, sreq->bssid, ETH_ALEN);
	अगर (sreq->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
		get_अक्रमom_mask_addr(req->अक्रमom_mac, sreq->mac_addr,
				     sreq->mac_addr_mask);
		req->scan_func |= SCAN_FUNC_RANDOM_MAC;
	पूर्ण

	err = mt76_mcu_skb_send_msg(mdev, skb, MCU_CMD_START_HW_SCAN, false);
	अगर (err < 0)
		clear_bit(MT76_HW_SCANNING, &phy->state);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_hw_scan);

पूर्णांक mt76_connac_mcu_cancel_hw_scan(काष्ठा mt76_phy *phy,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		u8 seq_num;
		u8 is_ext_channel;
		u8 rsv[2];
	पूर्ण __packed req = अणु
		.seq_num = mvअगर->scan_seq_num,
	पूर्ण;

	अगर (test_and_clear_bit(MT76_HW_SCANNING, &phy->state)) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		ieee80211_scan_completed(phy->hw, &info);
	पूर्ण

	वापस mt76_mcu_send_msg(phy->dev, MCU_CMD_CANCEL_HW_SCAN, &req,
				 माप(req), false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_cancel_hw_scan);

पूर्णांक mt76_connac_mcu_sched_scan_req(काष्ठा mt76_phy *phy,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा cfg80211_sched_scan_request *sreq)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा ieee80211_channel **scan_list = sreq->channels;
	काष्ठा mt76_connac_mcu_scan_channel *chan;
	काष्ठा mt76_connac_sched_scan_req *req;
	काष्ठा mt76_dev *mdev = phy->dev;
	bool ext_phy = phy == mdev->phy2;
	काष्ठा cfg80211_match_set *match;
	काष्ठा cfg80211_ssid *ssid;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	skb = mt76_mcu_msg_alloc(mdev, शून्य, माप(*req) + sreq->ie_len);
	अगर (!skb)
		वापस -ENOMEM;

	mvअगर->scan_seq_num = (mvअगर->scan_seq_num + 1) & 0x7f;

	req = (काष्ठा mt76_connac_sched_scan_req *)skb_put(skb, माप(*req));
	req->version = 1;
	req->seq_num = mvअगर->scan_seq_num | ext_phy << 7;

	अगर (is_mt7663(phy->dev) &&
	    (sreq->flags & NL80211_SCAN_FLAG_RANDOM_ADDR)) अणु
		get_अक्रमom_mask_addr(req->mt7663.अक्रमom_mac, sreq->mac_addr,
				     sreq->mac_addr_mask);
		req->scan_func = 1;
	पूर्ण अन्यथा अगर (is_mt7921(phy->dev)) अणु
		req->mt7921.bss_idx = mvअगर->idx;
	पूर्ण

	req->ssids_num = sreq->n_ssids;
	क्रम (i = 0; i < req->ssids_num; i++) अणु
		ssid = &sreq->ssids[i];
		स_नकल(req->ssids[i].ssid, ssid->ssid, ssid->ssid_len);
		req->ssids[i].ssid_len = cpu_to_le32(ssid->ssid_len);
	पूर्ण

	req->match_num = sreq->n_match_sets;
	क्रम (i = 0; i < req->match_num; i++) अणु
		match = &sreq->match_sets[i];
		स_नकल(req->match[i].ssid, match->ssid.ssid,
		       match->ssid.ssid_len);
		req->match[i].rssi_th = cpu_to_le32(match->rssi_thold);
		req->match[i].ssid_len = match->ssid.ssid_len;
	पूर्ण

	req->channel_type = sreq->n_channels ? 4 : 0;
	req->channels_num = min_t(u8, sreq->n_channels, 64);
	क्रम (i = 0; i < req->channels_num; i++) अणु
		chan = &req->channels[i];
		chan->band = scan_list[i]->band == NL80211_BAND_2GHZ ? 1 : 2;
		chan->channel_num = scan_list[i]->hw_value;
	पूर्ण

	req->पूर्णांकervals_num = sreq->n_scan_plans;
	क्रम (i = 0; i < req->पूर्णांकervals_num; i++)
		req->पूर्णांकervals[i] = cpu_to_le16(sreq->scan_plans[i].पूर्णांकerval);

	अगर (sreq->ie_len > 0) अणु
		req->ie_len = cpu_to_le16(sreq->ie_len);
		स_नकल(skb_put(skb, sreq->ie_len), sreq->ie, sreq->ie_len);
	पूर्ण

	वापस mt76_mcu_skb_send_msg(mdev, skb, MCU_CMD_SCHED_SCAN_REQ, false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_sched_scan_req);

पूर्णांक mt76_connac_mcu_sched_scan_enable(काष्ठा mt76_phy *phy,
				      काष्ठा ieee80211_vअगर *vअगर,
				      bool enable)
अणु
	काष्ठा अणु
		u8 active; /* 0: enabled 1: disabled */
		u8 rsv[3];
	पूर्ण __packed req = अणु
		.active = !enable,
	पूर्ण;

	अगर (enable)
		set_bit(MT76_HW_SCHED_SCANNING, &phy->state);
	अन्यथा
		clear_bit(MT76_HW_SCHED_SCANNING, &phy->state);

	वापस mt76_mcu_send_msg(phy->dev, MCU_CMD_SCHED_SCAN_ENABLE, &req,
				 माप(req), false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_sched_scan_enable);

पूर्णांक mt76_connac_mcu_chip_config(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_connac_config req = अणु
		.resp_type = 0,
	पूर्ण;

	स_नकल(req.data, "assert", 7);

	वापस mt76_mcu_send_msg(dev, MCU_CMD_CHIP_CONFIG, &req, माप(req),
				 false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_chip_config);

पूर्णांक mt76_connac_mcu_set_deep_sleep(काष्ठा mt76_dev *dev, bool enable)
अणु
	काष्ठा mt76_connac_config req = अणु
		.resp_type = 0,
	पूर्ण;

	snम_लिखो(req.data, माप(req.data), "KeepFullPwr %d", !enable);

	वापस mt76_mcu_send_msg(dev, MCU_CMD_CHIP_CONFIG, &req, माप(req),
				 false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_deep_sleep);

व्योम mt76_connac_mcu_coredump_event(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				    काष्ठा mt76_connac_coredump *coredump)
अणु
	spin_lock_bh(&dev->lock);
	__skb_queue_tail(&coredump->msg_list, skb);
	spin_unlock_bh(&dev->lock);

	coredump->last_activity = jअगरfies;

	queue_delayed_work(dev->wq, &coredump->work,
			   MT76_CONNAC_COREDUMP_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_coredump_event);

अटल व्योम
mt76_connac_mcu_build_sku(काष्ठा mt76_dev *dev, s8 *sku,
			  काष्ठा mt76_घातer_limits *limits,
			  क्रमागत nl80211_band band)
अणु
	पूर्णांक max_घातer = is_mt7921(dev) ? 127 : 63;
	पूर्णांक i, offset = माप(limits->cck);

	स_रखो(sku, max_घातer, MT_SKU_POWER_LIMIT);

	अगर (band == NL80211_BAND_2GHZ) अणु
		/* cck */
		स_नकल(sku, limits->cck, माप(limits->cck));
	पूर्ण

	/* ofdm */
	स_नकल(&sku[offset], limits->ofdm, माप(limits->ofdm));
	offset += माप(limits->ofdm);

	/* ht */
	क्रम (i = 0; i < 2; i++) अणु
		स_नकल(&sku[offset], limits->mcs[i], 8);
		offset += 8;
	पूर्ण
	sku[offset++] = limits->mcs[0][0];

	/* vht */
	क्रम (i = 0; i < ARRAY_SIZE(limits->mcs); i++) अणु
		स_नकल(&sku[offset], limits->mcs[i],
		       ARRAY_SIZE(limits->mcs[i]));
		offset += 12;
	पूर्ण

	अगर (!is_mt7921(dev))
		वापस;

	/* he */
	क्रम (i = 0; i < ARRAY_SIZE(limits->ru); i++) अणु
		स_नकल(&sku[offset], limits->ru[i], ARRAY_SIZE(limits->ru[i]));
		offset += ARRAY_SIZE(limits->ru[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक
mt76_connac_mcu_rate_txघातer_band(काष्ठा mt76_phy *phy,
				  क्रमागत nl80211_band band)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	पूर्णांक sku_len, batch_len = is_mt7921(dev) ? 8 : 16;
	अटल स्थिर u8 chan_list_2ghz[] = अणु
		1, 2,  3,  4,  5,  6,  7,
		8, 9, 10, 11, 12, 13, 14
	पूर्ण;
	अटल स्थिर u8 chan_list_5ghz[] = अणु
		 36,  38,  40,  42,  44,  46,  48,
		 50,  52,  54,  56,  58,  60,  62,
		 64, 100, 102, 104, 106, 108, 110,
		112, 114, 116, 118, 120, 122, 124,
		126, 128, 132, 134, 136, 138, 140,
		142, 144, 149, 151, 153, 155, 157,
		159, 161, 165
	पूर्ण;
	काष्ठा mt76_connac_sku_tlv sku_tlbv;
	पूर्णांक i, n_chan, batch_size, idx = 0;
	काष्ठा mt76_घातer_limits limits;
	स्थिर u8 *ch_list;

	sku_len = is_mt7921(dev) ? माप(sku_tlbv) : माप(sku_tlbv) - 92;

	अगर (band == NL80211_BAND_2GHZ) अणु
		n_chan = ARRAY_SIZE(chan_list_2ghz);
		ch_list = chan_list_2ghz;
	पूर्ण अन्यथा अणु
		n_chan = ARRAY_SIZE(chan_list_5ghz);
		ch_list = chan_list_5ghz;
	पूर्ण
	batch_size = DIV_ROUND_UP(n_chan, batch_len);

	क्रम (i = 0; i < batch_size; i++) अणु
		bool last_msg = i == batch_size - 1;
		पूर्णांक num_ch = last_msg ? n_chan % batch_len : batch_len;
		काष्ठा mt76_connac_tx_घातer_limit_tlv tx_घातer_tlv = अणु
			.band = band == NL80211_BAND_2GHZ ? 1 : 2,
			.n_chan = num_ch,
			.last_msg = last_msg,
		पूर्ण;
		काष्ठा sk_buff *skb;
		पूर्णांक j, err, msg_len;

		msg_len = माप(tx_घातer_tlv) + num_ch * माप(sku_tlbv);
		skb = mt76_mcu_msg_alloc(dev, शून्य, msg_len);
		अगर (!skb)
			वापस -ENOMEM;

		BUILD_BUG_ON(माप(dev->alpha2) > माप(tx_घातer_tlv.alpha2));
		स_नकल(tx_घातer_tlv.alpha2, dev->alpha2, माप(dev->alpha2));

		skb_put_data(skb, &tx_घातer_tlv, माप(tx_घातer_tlv));
		क्रम (j = 0; j < num_ch; j++, idx++) अणु
			काष्ठा ieee80211_channel chan = अणु
				.hw_value = ch_list[idx],
				.band = band,
			पूर्ण;

			mt76_get_rate_घातer_limits(phy, &chan, &limits, 127);

			sku_tlbv.channel = ch_list[idx];
			mt76_connac_mcu_build_sku(dev, sku_tlbv.pwr_limit,
						  &limits, band);
			skb_put_data(skb, &sku_tlbv, sku_len);
		पूर्ण

		err = mt76_mcu_skb_send_msg(dev, skb,
					    MCU_CMD_SET_RATE_TX_POWER, false);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt76_connac_mcu_set_rate_txघातer(काष्ठा mt76_phy *phy)
अणु
	पूर्णांक err;

	err = mt76_connac_mcu_rate_txघातer_band(phy, NL80211_BAND_2GHZ);
	अगर (err < 0)
		वापस err;

	वापस mt76_connac_mcu_rate_txघातer_band(phy, NL80211_BAND_5GHZ);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_rate_txघातer);

पूर्णांक mt76_connac_mcu_update_arp_filter(काष्ठा mt76_dev *dev,
				      काष्ठा mt76_vअगर *vअगर,
				      काष्ठा ieee80211_bss_conf *info)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i, len = min_t(पूर्णांक, info->arp_addr_cnt,
			   IEEE80211_BSS_ARP_ADDR_LIST_LEN);
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_arpns_tlv arp;
	पूर्ण req_hdr = अणु
		.hdr = अणु
			.bss_idx = vअगर->idx,
		पूर्ण,
		.arp = अणु
			.tag = cpu_to_le16(UNI_OFFLOAD_OFFLOAD_ARP),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_arpns_tlv)),
			.ips_num = len,
			.mode = 2,  /* update */
			.option = 1,
		पूर्ण,
	पूर्ण;

	skb = mt76_mcu_msg_alloc(dev, शून्य,
				 माप(req_hdr) + len * माप(__be32));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &req_hdr, माप(req_hdr));
	क्रम (i = 0; i < len; i++) अणु
		u8 *addr = (u8 *)skb_put(skb, माप(__be32));

		स_नकल(addr, &info->arp_addr_list[i], माप(__be32));
	पूर्ण

	वापस mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD_OFFLOAD, true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_update_arp_filter);

#अगर_घोषित CONFIG_PM

स्थिर काष्ठा wiphy_wowlan_support mt76_connac_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT |
		 WIPHY_WOWLAN_SUPPORTS_GTK_REKEY | WIPHY_WOWLAN_NET_DETECT,
	.n_patterns = 1,
	.pattern_min_len = 1,
	.pattern_max_len = MT76_CONNAC_WOW_PATTEN_MAX_LEN,
	.max_nd_match_sets = 10,
पूर्ण;
EXPORT_SYMBOL_GPL(mt76_connac_wowlan_support);

अटल व्योम
mt76_connac_mcu_key_iter(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta,
			 काष्ठा ieee80211_key_conf *key,
			 व्योम *data)
अणु
	काष्ठा mt76_connac_gtk_rekey_tlv *gtk_tlv = data;
	u32 cipher;

	अगर (key->cipher != WLAN_CIPHER_SUITE_AES_CMAC &&
	    key->cipher != WLAN_CIPHER_SUITE_CCMP &&
	    key->cipher != WLAN_CIPHER_SUITE_TKIP)
		वापस;

	अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		gtk_tlv->proto = cpu_to_le32(NL80211_WPA_VERSION_1);
		cipher = BIT(3);
	पूर्ण अन्यथा अणु
		gtk_tlv->proto = cpu_to_le32(NL80211_WPA_VERSION_2);
		cipher = BIT(4);
	पूर्ण

	/* we are assuming here to have a single pairwise key */
	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
		gtk_tlv->pairwise_cipher = cpu_to_le32(cipher);
		gtk_tlv->group_cipher = cpu_to_le32(cipher);
		gtk_tlv->keyid = key->keyidx;
	पूर्ण
पूर्ण

पूर्णांक mt76_connac_mcu_update_gtk_rekey(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा cfg80211_gtk_rekey_data *key)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_connac_gtk_rekey_tlv *gtk_tlv;
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा sk_buff *skb;
	काष्ठा अणु
		u8 bss_idx;
		u8 pad[3];
	पूर्ण __packed hdr = अणु
		.bss_idx = mvअगर->idx,
	पूर्ण;

	skb = mt76_mcu_msg_alloc(phy->dev, शून्य,
				 माप(hdr) + माप(*gtk_tlv));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &hdr, माप(hdr));
	gtk_tlv = (काष्ठा mt76_connac_gtk_rekey_tlv *)skb_put(skb,
							 माप(*gtk_tlv));
	gtk_tlv->tag = cpu_to_le16(UNI_OFFLOAD_OFFLOAD_GTK_REKEY);
	gtk_tlv->len = cpu_to_le16(माप(*gtk_tlv));
	gtk_tlv->rekey_mode = 2;
	gtk_tlv->option = 1;

	rcu_पढ़ो_lock();
	ieee80211_iter_keys_rcu(hw, vअगर, mt76_connac_mcu_key_iter, gtk_tlv);
	rcu_पढ़ो_unlock();

	स_नकल(gtk_tlv->kek, key->kek, NL80211_KEK_LEN);
	स_नकल(gtk_tlv->kck, key->kck, NL80211_KCK_LEN);
	स_नकल(gtk_tlv->replay_ctr, key->replay_ctr, NL80211_REPLAY_CTR_LEN);

	वापस mt76_mcu_skb_send_msg(phy->dev, skb, MCU_UNI_CMD_OFFLOAD, true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_update_gtk_rekey);

अटल पूर्णांक
mt76_connac_mcu_set_arp_filter(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			       bool suspend)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_arpns_tlv arpns;
	पूर्ण req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.arpns = अणु
			.tag = cpu_to_le16(UNI_OFFLOAD_OFFLOAD_ARP),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_arpns_tlv)),
			.mode = suspend,
		पूर्ण,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_UNI_CMD_OFFLOAD, &req, माप(req),
				 true);
पूर्ण

अटल पूर्णांक
mt76_connac_mcu_set_gtk_rekey(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			      bool suspend)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_gtk_rekey_tlv gtk_tlv;
	पूर्ण __packed req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.gtk_tlv = अणु
			.tag = cpu_to_le16(UNI_OFFLOAD_OFFLOAD_GTK_REKEY),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_gtk_rekey_tlv)),
			.rekey_mode = !suspend,
		पूर्ण,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_UNI_CMD_OFFLOAD, &req, माप(req),
				 true);
पूर्ण

अटल पूर्णांक
mt76_connac_mcu_set_suspend_mode(काष्ठा mt76_dev *dev,
				 काष्ठा ieee80211_vअगर *vअगर,
				 bool enable, u8 mdtim,
				 bool wow_suspend)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_suspend_tlv suspend_tlv;
	पूर्ण req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.suspend_tlv = अणु
			.tag = cpu_to_le16(UNI_SUSPEND_MODE_SETTING),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_suspend_tlv)),
			.enable = enable,
			.mdtim = mdtim,
			.wow_suspend = wow_suspend,
		पूर्ण,
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_UNI_CMD_SUSPEND, &req, माप(req),
				 true);
पूर्ण

अटल पूर्णांक
mt76_connac_mcu_set_wow_pattern(काष्ठा mt76_dev *dev,
				काष्ठा ieee80211_vअगर *vअगर,
				u8 index, bool enable,
				काष्ठा cfg80211_pkt_pattern *pattern)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_connac_wow_pattern_tlv *ptlv;
	काष्ठा sk_buff *skb;
	काष्ठा req_hdr अणु
		u8 bss_idx;
		u8 pad[3];
	पूर्ण __packed hdr = अणु
		.bss_idx = mvअगर->idx,
	पूर्ण;

	skb = mt76_mcu_msg_alloc(dev, शून्य, माप(hdr) + माप(*ptlv));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &hdr, माप(hdr));
	ptlv = (काष्ठा mt76_connac_wow_pattern_tlv *)skb_put(skb, माप(*ptlv));
	ptlv->tag = cpu_to_le16(UNI_SUSPEND_WOW_PATTERN);
	ptlv->len = cpu_to_le16(माप(*ptlv));
	ptlv->data_len = pattern->pattern_len;
	ptlv->enable = enable;
	ptlv->index = index;

	स_नकल(ptlv->pattern, pattern->pattern, pattern->pattern_len);
	स_नकल(ptlv->mask, pattern->mask, pattern->pattern_len / 8);

	वापस mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD_SUSPEND, true);
पूर्ण

अटल पूर्णांक
mt76_connac_mcu_set_wow_ctrl(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			     bool suspend, काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा अणु
		काष्ठा अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा mt76_connac_wow_ctrl_tlv wow_ctrl_tlv;
		काष्ठा mt76_connac_wow_gpio_param_tlv gpio_tlv;
	पूर्ण req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->idx,
		पूर्ण,
		.wow_ctrl_tlv = अणु
			.tag = cpu_to_le16(UNI_SUSPEND_WOW_CTRL),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_wow_ctrl_tlv)),
			.cmd = suspend ? 1 : 2,
		पूर्ण,
		.gpio_tlv = अणु
			.tag = cpu_to_le16(UNI_SUSPEND_WOW_GPIO_PARAM),
			.len = cpu_to_le16(माप(काष्ठा mt76_connac_wow_gpio_param_tlv)),
			.gpio_pin = 0xff, /* follow fw about GPIO pin */
		पूर्ण,
	पूर्ण;

	अगर (wowlan->magic_pkt)
		req.wow_ctrl_tlv.trigger |= BIT(0);
	अगर (wowlan->disconnect)
		req.wow_ctrl_tlv.trigger |= BIT(2);
	अगर (wowlan->nd_config) अणु
		mt76_connac_mcu_sched_scan_req(phy, vअगर, wowlan->nd_config);
		req.wow_ctrl_tlv.trigger |= BIT(5);
		mt76_connac_mcu_sched_scan_enable(phy, vअगर, suspend);
	पूर्ण

	अगर (mt76_is_mmio(dev))
		req.wow_ctrl_tlv.wakeup_hअगर = WOW_PCIE;
	अन्यथा अगर (mt76_is_usb(dev))
		req.wow_ctrl_tlv.wakeup_hअगर = WOW_USB;
	अन्यथा अगर (mt76_is_sdio(dev))
		req.wow_ctrl_tlv.wakeup_hअगर = WOW_GPIO;

	वापस mt76_mcu_send_msg(dev, MCU_UNI_CMD_SUSPEND, &req, माप(req),
				 true);
पूर्ण

पूर्णांक mt76_connac_mcu_set_hअगर_suspend(काष्ठा mt76_dev *dev, bool suspend)
अणु
	काष्ठा अणु
		काष्ठा अणु
			u8 hअगर_type; /* 0x0: HIF_SDIO
				      * 0x1: HIF_USB
				      * 0x2: HIF_PCIE
				      */
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा hअगर_suspend_tlv अणु
			__le16 tag;
			__le16 len;
			u8 suspend;
		पूर्ण __packed hअगर_suspend;
	पूर्ण req = अणु
		.hअगर_suspend = अणु
			.tag = cpu_to_le16(0), /* 0: UNI_HIF_CTRL_BASIC */
			.len = cpu_to_le16(माप(काष्ठा hअगर_suspend_tlv)),
			.suspend = suspend,
		पूर्ण,
	पूर्ण;

	अगर (mt76_is_mmio(dev))
		req.hdr.hअगर_type = 2;
	अन्यथा अगर (mt76_is_usb(dev))
		req.hdr.hअगर_type = 1;
	अन्यथा अगर (mt76_is_sdio(dev))
		req.hdr.hअगर_type = 0;

	वापस mt76_mcu_send_msg(dev, MCU_UNI_CMD_HIF_CTRL, &req, माप(req),
				 true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_hअगर_suspend);

व्योम mt76_connac_mcu_set_suspend_iter(व्योम *priv, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_phy *phy = priv;
	bool suspend = test_bit(MT76_STATE_SUSPEND, &phy->state);
	काष्ठा ieee80211_hw *hw = phy->hw;
	काष्ठा cfg80211_wowlan *wowlan = hw->wiphy->wowlan_config;
	पूर्णांक i;

	mt76_connac_mcu_set_gtk_rekey(phy->dev, vअगर, suspend);
	mt76_connac_mcu_set_arp_filter(phy->dev, vअगर, suspend);

	mt76_connac_mcu_set_suspend_mode(phy->dev, vअगर, suspend, 1, true);

	क्रम (i = 0; i < wowlan->n_patterns; i++)
		mt76_connac_mcu_set_wow_pattern(phy->dev, vअगर, i, suspend,
						&wowlan->patterns[i]);
	mt76_connac_mcu_set_wow_ctrl(phy, vअगर, suspend, wowlan);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_mcu_set_suspend_iter);

#पूर्ण_अगर /* CONFIG_PM */

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo@kernel.org>");
MODULE_LICENSE("Dual BSD/GPL");
