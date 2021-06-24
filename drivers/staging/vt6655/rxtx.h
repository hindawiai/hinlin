<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: rxtx.h
 *
 * Purpose:
 *
 * Author: Jerry Chen
 *
 * Date: Jun. 27, 2002
 *
 */

#अगर_अघोषित __RXTX_H__
#घोषणा __RXTX_H__

#समावेश "device.h"

#घोषणा DEFAULT_MSDU_LIFETIME_RES_64us	8000 /* 64us */
#घोषणा DEFAULT_MGN_LIFETIME_RES_64us	125  /* 64us */


/*---------------------  Export Definitions -------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

/* MIC HDR data header */
काष्ठा vnt_mic_hdr अणु
	u8 id;
	u8 tx_priority;
	u8 mic_addr2[ETH_ALEN];
	u8 ccmp_pn[IEEE80211_CCMP_PN_LEN];
	__be16 payload_len;
	__be16 hlen;
	__le16 frame_control;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctrl;
	u8 addr4[ETH_ALEN];
	u16 packing; /* packing to 48 bytes */
पूर्ण __packed;

/* RsvTime buffer header */
काष्ठा vnt_rrv_समय_rts अणु
	__le16 rts_rrv_समय_ba;
	__le16 rts_rrv_समय_aa;
	__le16 rts_rrv_समय_bb;
	u16 reserved;
	__le16 rrv_समय_b;
	__le16 rrv_समय_a;
पूर्ण __packed;

काष्ठा vnt_rrv_समय_cts अणु
	__le16 cts_rrv_समय_ba;
	u16 reserved;
	__le16 rrv_समय_b;
	__le16 rrv_समय_a;
पूर्ण __packed;

काष्ठा vnt_rrv_समय_ab अणु
	__le16 rts_rrv_समय;
	__le16 rrv_समय;
पूर्ण __packed;

/* TX data header */
काष्ठा vnt_tx_datahead_g अणु
	काष्ठा vnt_phy_field b;
	काष्ठा vnt_phy_field a;
	__le16 duration_b;
	__le16 duration_a;
	__le16 समय_stamp_off_b;
	__le16 समय_stamp_off_a;
पूर्ण __packed;

काष्ठा vnt_tx_datahead_g_fb अणु
	काष्ठा vnt_phy_field b;
	काष्ठा vnt_phy_field a;
	__le16 duration_b;
	__le16 duration_a;
	__le16 duration_a_f0;
	__le16 duration_a_f1;
	__le16 समय_stamp_off_b;
	__le16 समय_stamp_off_a;
पूर्ण __packed;

काष्ठा vnt_tx_datahead_ab अणु
	काष्ठा vnt_phy_field ab;
	__le16 duration;
	__le16 समय_stamp_off;
पूर्ण __packed;

काष्ठा vnt_tx_datahead_a_fb अणु
	काष्ठा vnt_phy_field a;
	__le16 duration;
	__le16 समय_stamp_off;
	__le16 duration_f0;
	__le16 duration_f1;
पूर्ण __packed;

/* RTS buffer header */
काष्ठा vnt_rts_g अणु
	काष्ठा vnt_phy_field b;
	काष्ठा vnt_phy_field a;
	__le16 duration_ba;
	__le16 duration_aa;
	__le16 duration_bb;
	u16 reserved;
	काष्ठा ieee80211_rts data;
पूर्ण __packed __aligned(2);

काष्ठा vnt_rts_g_fb अणु
	काष्ठा vnt_phy_field b;
	काष्ठा vnt_phy_field a;
	__le16 duration_ba;
	__le16 duration_aa;
	__le16 duration_bb;
	u16 wReserved;
	__le16 rts_duration_ba_f0;
	__le16 rts_duration_aa_f0;
	__le16 rts_duration_ba_f1;
	__le16 rts_duration_aa_f1;
	काष्ठा ieee80211_rts data;
पूर्ण __packed __aligned(2);

काष्ठा vnt_rts_ab अणु
	काष्ठा vnt_phy_field ab;
	__le16 duration;
	u16 reserved;
	काष्ठा ieee80211_rts data;
पूर्ण __packed __aligned(2);

काष्ठा vnt_rts_a_fb अणु
	काष्ठा vnt_phy_field a;
	__le16 duration;
	u16 reserved;
	__le16 rts_duration_f0;
	__le16 rts_duration_f1;
	काष्ठा ieee80211_rts data;
पूर्ण __packed __aligned(2);

/* CTS buffer header */
काष्ठा vnt_cts अणु
	काष्ठा vnt_phy_field b;
	__le16 duration_ba;
	u16 reserved;
	काष्ठा ieee80211_cts data;
	u16 reserved2;
पूर्ण __packed __aligned(2);

काष्ठा vnt_cts_fb अणु
	काष्ठा vnt_phy_field b;
	__le16 duration_ba;
	u16 reserved;
	__le16 cts_duration_ba_f0;
	__le16 cts_duration_ba_f1;
	काष्ठा ieee80211_cts data;
	u16 reserved2;
पूर्ण __packed __aligned(2);

काष्ठा vnt_tx_fअगरo_head अणु
	u8 tx_key[WLAN_KEY_LEN_CCMP];
	__le16 fअगरo_ctl;
	__le16 समय_stamp;
	__le16 frag_ctl;
	__le16 current_rate;
पूर्ण __packed;

काष्ठा vnt_tx_लघु_buf_head अणु
	__le16 fअगरo_ctl;
	u16 समय_stamp;
	काष्ठा vnt_phy_field ab;
	__le16 duration;
	__le16 समय_stamp_off;
पूर्ण __packed;

पूर्णांक vnt_generate_fअगरo_header(काष्ठा vnt_निजी *priv, u32 dma_idx,
			     काष्ठा vnt_tx_desc *head_td, काष्ठा sk_buff *skb);
पूर्णांक vnt_beacon_make(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक vnt_beacon_enable(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_bss_conf *conf);

#पूर्ण_अगर /* __RXTX_H__ */
