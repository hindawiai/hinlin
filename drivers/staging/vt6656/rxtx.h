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
#समावेश "wcmd.h"
#समावेश "baseband.h"

#घोषणा DEFAULT_MGN_LIFETIME_RES_64us	125  /* 64us */
#घोषणा DEFAULT_MSDU_LIFETIME_RES_64us  8000

/* Length, Service, and Signal fields of Phy क्रम Tx */
काष्ठा vnt_phy_field अणु
	u8 संकेत;
	u8 service;
	__le16 len;
पूर्ण __packed;

/* MIC HDR data header */
काष्ठा vnt_mic_hdr अणु
	u8 id;
	u8 tx_priority;
	u8 mic_addr2[6];
	u8 ccmp_pn[IEEE80211_CCMP_PN_LEN];
	__be16 payload_len;
	__be16 hlen;
	__le16 frame_control;
	u8 addr1[6];
	u8 addr2[6];
	u8 addr3[6];
	__le16 seq_ctrl;
	u8 addr4[6];
	u16 packing; /* packing to 48 bytes */
पूर्ण __packed;

/* RsvTime buffer header */
काष्ठा vnt_rrv_समय_rts अणु
	__le16 rts_rrv_समय_ba;
	__le16 rts_rrv_समय_aa;
	__le16 rts_rrv_समय_bb;
	u16 wReserved;
	__le16 rrv_समय_b;
	__le16 rrv_समय_a;
पूर्ण __packed;

काष्ठा vnt_rrv_समय_cts अणु
	__le16 cts_rrv_समय_ba;
	u16 wReserved;
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

काष्ठा vnt_tx_datahead_ab अणु
	काष्ठा vnt_phy_field ab;
	__le16 duration;
	__le16 समय_stamp_off;
पूर्ण __packed;

/* RTS buffer header */
काष्ठा vnt_rts_g अणु
	काष्ठा vnt_phy_field b;
	काष्ठा vnt_phy_field a;
	__le16 duration_ba;
	__le16 duration_aa;
	__le16 duration_bb;
	u16 wReserved;
	काष्ठा ieee80211_rts data;
	काष्ठा vnt_tx_datahead_g data_head;
पूर्ण __packed __aligned(2);

काष्ठा vnt_rts_ab अणु
	काष्ठा vnt_phy_field ab;
	__le16 duration;
	u16 wReserved;
	काष्ठा ieee80211_rts data;
	काष्ठा vnt_tx_datahead_ab data_head;
पूर्ण __packed __aligned(2);

/* CTS buffer header */
काष्ठा vnt_cts अणु
	काष्ठा vnt_phy_field b;
	__le16 duration_ba;
	u16 wReserved;
	काष्ठा ieee80211_cts data;
	u16 reserved2;
	काष्ठा vnt_tx_datahead_g data_head;
पूर्ण __packed __aligned(2);

जोड़ vnt_tx_data_head अणु
	/* rts g */
	काष्ठा vnt_rts_g rts_g;
	/* rts a/b */
	काष्ठा vnt_rts_ab rts_ab;
	/* cts g */
	काष्ठा vnt_cts cts_g;
	/* no rts/cts */
	काष्ठा vnt_tx_datahead_ab data_head_ab;
पूर्ण;

काष्ठा vnt_tx_mic_hdr अणु
	काष्ठा vnt_mic_hdr hdr;
	जोड़ vnt_tx_data_head head;
पूर्ण __packed;

जोड़ vnt_tx अणु
	काष्ठा vnt_tx_mic_hdr mic;
	जोड़ vnt_tx_data_head head;
पूर्ण;

जोड़ vnt_tx_head अणु
	काष्ठा अणु
		काष्ठा vnt_rrv_समय_rts rts;
		जोड़ vnt_tx tx;
	पूर्ण __packed tx_rts;
	काष्ठा अणु
		काष्ठा vnt_rrv_समय_cts cts;
		जोड़ vnt_tx tx;
	पूर्ण __packed tx_cts;
	काष्ठा अणु
		काष्ठा vnt_rrv_समय_ab ab;
		जोड़ vnt_tx tx;
	पूर्ण __packed tx_ab;
पूर्ण;

काष्ठा vnt_tx_fअगरo_head अणु
	u8 tx_key[WLAN_KEY_LEN_CCMP];
	__le16 fअगरo_ctl;
	__le16 समय_stamp;
	__le16 frag_ctl;
	__le16 current_rate;
पूर्ण __packed;

काष्ठा vnt_tx_buffer अणु
	काष्ठा vnt_tx_fअगरo_head fअगरo_head;
	जोड़ vnt_tx_head tx_head;
पूर्ण __packed;

काष्ठा vnt_tx_लघु_buf_head अणु
	__le16 fअगरo_ctl;
	u16 समय_stamp;
	काष्ठा vnt_phy_field ab;
	__le16 duration;
	__le16 समय_stamp_off;
पूर्ण __packed;

पूर्णांक vnt_tx_packet(काष्ठा vnt_निजी *priv, काष्ठा sk_buff *skb);
पूर्णांक vnt_beacon_make(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक vnt_beacon_enable(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_bss_conf *conf);

#पूर्ण_अगर /* __RXTX_H__ */
