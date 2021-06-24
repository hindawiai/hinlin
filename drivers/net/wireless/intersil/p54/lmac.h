<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LMAC Interface specअगरic definitions क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007 - 2009, Christian Lamparter <chunkeey@web.de>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 *
 * - LMAC API पूर्णांकerface header file क्रम STLC4560 (lmac_दीर्घbow.h)
 *   Copyright (C) 2007 Conexant Systems, Inc.
 */

#अगर_अघोषित LMAC_H
#घोषणा LMAC_H

क्रमागत p54_control_frame_types अणु
	P54_CONTROL_TYPE_SETUP = 0,
	P54_CONTROL_TYPE_SCAN,
	P54_CONTROL_TYPE_TRAP,
	P54_CONTROL_TYPE_DCFINIT,
	P54_CONTROL_TYPE_RX_KEYCACHE,
	P54_CONTROL_TYPE_TIM,
	P54_CONTROL_TYPE_PSM,
	P54_CONTROL_TYPE_TXCANCEL,
	P54_CONTROL_TYPE_TXDONE,
	P54_CONTROL_TYPE_BURST,
	P54_CONTROL_TYPE_STAT_READBACK,
	P54_CONTROL_TYPE_BBP,
	P54_CONTROL_TYPE_EEPROM_READBACK,
	P54_CONTROL_TYPE_LED,
	P54_CONTROL_TYPE_GPIO,
	P54_CONTROL_TYPE_TIMER,
	P54_CONTROL_TYPE_MODULATION,
	P54_CONTROL_TYPE_SYNTH_CONFIG,
	P54_CONTROL_TYPE_DETECTOR_VALUE,
	P54_CONTROL_TYPE_XBOW_SYNTH_CFG,
	P54_CONTROL_TYPE_CCE_QUIET,
	P54_CONTROL_TYPE_PSM_STA_UNLOCK,
	P54_CONTROL_TYPE_PCS,
	P54_CONTROL_TYPE_BT_BALANCER = 28,
	P54_CONTROL_TYPE_GROUP_ADDRESS_TABLE = 30,
	P54_CONTROL_TYPE_ARPTABLE = 31,
	P54_CONTROL_TYPE_BT_OPTIONS = 35,
पूर्ण;

#घोषणा P54_HDR_FLAG_CONTROL		BIT(15)
#घोषणा P54_HDR_FLAG_CONTROL_OPSET	(BIT(15) + BIT(0))
#घोषणा P54_HDR_FLAG_DATA_ALIGN		BIT(14)

#घोषणा P54_HDR_FLAG_DATA_OUT_PROMISC		BIT(0)
#घोषणा P54_HDR_FLAG_DATA_OUT_TIMESTAMP		BIT(1)
#घोषणा P54_HDR_FLAG_DATA_OUT_SEQNR		BIT(2)
#घोषणा P54_HDR_FLAG_DATA_OUT_BIT3		BIT(3)
#घोषणा P54_HDR_FLAG_DATA_OUT_BURST		BIT(4)
#घोषणा P54_HDR_FLAG_DATA_OUT_NOCANCEL		BIT(5)
#घोषणा P54_HDR_FLAG_DATA_OUT_CLEARTIM		BIT(6)
#घोषणा P54_HDR_FLAG_DATA_OUT_HITCHHIKE		BIT(7)
#घोषणा P54_HDR_FLAG_DATA_OUT_COMPRESS		BIT(8)
#घोषणा P54_HDR_FLAG_DATA_OUT_CONCAT		BIT(9)
#घोषणा P54_HDR_FLAG_DATA_OUT_PCS_ACCEPT	BIT(10)
#घोषणा P54_HDR_FLAG_DATA_OUT_WAITEOSP		BIT(11)

#घोषणा P54_HDR_FLAG_DATA_IN_FCS_GOOD		BIT(0)
#घोषणा P54_HDR_FLAG_DATA_IN_MATCH_MAC		BIT(1)
#घोषणा P54_HDR_FLAG_DATA_IN_MCBC		BIT(2)
#घोषणा P54_HDR_FLAG_DATA_IN_BEACON		BIT(3)
#घोषणा P54_HDR_FLAG_DATA_IN_MATCH_BSS		BIT(4)
#घोषणा P54_HDR_FLAG_DATA_IN_BCAST_BSS		BIT(5)
#घोषणा P54_HDR_FLAG_DATA_IN_DATA		BIT(6)
#घोषणा P54_HDR_FLAG_DATA_IN_TRUNCATED		BIT(7)
#घोषणा P54_HDR_FLAG_DATA_IN_BIT8		BIT(8)
#घोषणा P54_HDR_FLAG_DATA_IN_TRANSPARENT	BIT(9)

काष्ठा p54_hdr अणु
	__le16 flags;
	__le16 len;
	__le32 req_id;
	__le16 type;	/* क्रमागत p54_control_frame_types */
	u8 rts_tries;
	u8 tries;
	u8 data[];
पूर्ण __packed;

#घोषणा GET_REQ_ID(skb)							\
	(((काष्ठा p54_hdr *) ((काष्ठा sk_buff *) skb)->data)->req_id)	\

#घोषणा FREE_AFTER_TX(skb)						\
	((((काष्ठा p54_hdr *) ((काष्ठा sk_buff *) skb)->data)->		\
	flags) == cpu_to_le16(P54_HDR_FLAG_CONTROL_OPSET))

#घोषणा IS_DATA_FRAME(skb)						\
	(!((((काष्ठा p54_hdr *) ((काष्ठा sk_buff *) skb)->data)->	\
	flags) & cpu_to_le16(P54_HDR_FLAG_CONTROL)))

#घोषणा GET_HW_QUEUE(skb)						\
	(((काष्ठा p54_tx_data *)((काष्ठा p54_hdr *)			\
	skb->data)->data)->hw_queue)

/*
 * shared पूर्णांकerface ID definitions
 * The पूर्णांकerface ID is a unique identअगरication of a specअगरic पूर्णांकerface.
 * The following values are reserved: 0x0000, 0x0002, 0x0012, 0x0014, 0x0015
 */
#घोषणा IF_ID_ISL36356A			0x0001	/* ISL36356A <-> Firmware */
#घोषणा IF_ID_MVC			0x0003	/* MAC Virtual Coprocessor */
#घोषणा IF_ID_DEBUG			0x0008	/* PolDebug Interface */
#घोषणा IF_ID_PRODUCT			0x0009
#घोषणा IF_ID_OEM			0x000a
#घोषणा IF_ID_PCI3877			0x000b	/* 3877 <-> Host PCI */
#घोषणा IF_ID_ISL37704C			0x000c	/* ISL37704C <-> Fw */
#घोषणा IF_ID_ISL39000			0x000f	/* ISL39000 <-> Fw */
#घोषणा IF_ID_ISL39300A			0x0010	/* ISL39300A <-> Fw */
#घोषणा IF_ID_ISL37700_UAP		0x0016	/* ISL37700 uAP Fw <-> Fw */
#घोषणा IF_ID_ISL39000_UAP		0x0017	/* ISL39000 uAP Fw <-> Fw */
#घोषणा IF_ID_LMAC			0x001a	/* Interface exposed by LMAC */

काष्ठा exp_अगर अणु
	__le16 role;
	__le16 अगर_id;
	__le16 variant;
	__le16 bपंचांग_compat;
	__le16 top_compat;
पूर्ण __packed;

काष्ठा dep_अगर अणु
	__le16 role;
	__le16 अगर_id;
	__le16 variant;
पूर्ण __packed;

/* driver <-> lmac definitions */
काष्ठा p54_eeprom_lm86 अणु
	जोड़ अणु
		काष्ठा अणु
			__le16 offset;
			__le16 len;
			u8 data[0];
		पूर्ण __packed v1;
		काष्ठा अणु
			__le32 offset;
			__le16 len;
			u8 magic2;
			u8 pad;
			u8 magic[4];
			u8 data[0];
		पूर्ण __packed v2;
	पूर्ण  __packed;
पूर्ण __packed;

क्रमागत p54_rx_decrypt_status अणु
	P54_DECRYPT_NONE = 0,
	P54_DECRYPT_OK,
	P54_DECRYPT_NOKEY,
	P54_DECRYPT_NOMICHAEL,
	P54_DECRYPT_NOCKIPMIC,
	P54_DECRYPT_FAIL_WEP,
	P54_DECRYPT_FAIL_TKIP,
	P54_DECRYPT_FAIL_MICHAEL,
	P54_DECRYPT_FAIL_CKIPKP,
	P54_DECRYPT_FAIL_CKIPMIC,
	P54_DECRYPT_FAIL_AESCCMP
पूर्ण;

काष्ठा p54_rx_data अणु
	__le16 flags;
	__le16 len;
	__le16 freq;
	u8 antenna;
	u8 rate;
	u8 rssi;
	u8 quality;
	u8 decrypt_status;
	u8 rssi_raw;
	__le32 tsf32;
	__le32 unalloc0;
	u8 align[];
पूर्ण __packed;

क्रमागत p54_trap_type अणु
	P54_TRAP_SCAN = 0,
	P54_TRAP_TIMER,
	P54_TRAP_BEACON_TX,
	P54_TRAP_FAA_RADIO_ON,
	P54_TRAP_FAA_RADIO_OFF,
	P54_TRAP_RADAR,
	P54_TRAP_NO_BEACON,
	P54_TRAP_TBTT,
	P54_TRAP_SCO_ENTER,
	P54_TRAP_SCO_EXIT
पूर्ण;

काष्ठा p54_trap अणु
	__le16 event;
	__le16 frequency;
पूर्ण __packed;

क्रमागत p54_frame_sent_status अणु
	P54_TX_OK = 0,
	P54_TX_FAILED,
	P54_TX_PSM,
	P54_TX_PSM_CANCELLED = 4
पूर्ण;

काष्ठा p54_frame_sent अणु
	u8 status;
	u8 tries;
	u8 ack_rssi;
	u8 quality;
	__le16 seq;
	u8 antenna;
	u8 padding;
पूर्ण __packed;

क्रमागत p54_tx_data_crypt अणु
	P54_CRYPTO_NONE = 0,
	P54_CRYPTO_WEP,
	P54_CRYPTO_TKIP,
	P54_CRYPTO_TKIPMICHAEL,
	P54_CRYPTO_CCX_WEPMIC,
	P54_CRYPTO_CCX_KPMIC,
	P54_CRYPTO_CCX_KP,
	P54_CRYPTO_AESCCMP
पूर्ण;

क्रमागत p54_tx_data_queue अणु
	P54_QUEUE_BEACON	= 0,
	P54_QUEUE_FWSCAN	= 1,
	P54_QUEUE_MGMT		= 2,
	P54_QUEUE_CAB		= 3,
	P54_QUEUE_DATA		= 4,

	P54_QUEUE_AC_NUM	= 4,
	P54_QUEUE_AC_VO		= 4,
	P54_QUEUE_AC_VI		= 5,
	P54_QUEUE_AC_BE		= 6,
	P54_QUEUE_AC_BK		= 7,

	/* keep last */
	P54_QUEUE_NUM		= 8,
पूर्ण;

#घोषणा IS_QOS_QUEUE(n)	(n >= P54_QUEUE_DATA)

काष्ठा p54_tx_data अणु
	u8 rateset[8];
	u8 rts_rate_idx;
	u8 crypt_offset;
	u8 key_type;
	u8 key_len;
	u8 key[16];
	u8 hw_queue;
	u8 backlog;
	__le16 durations[4];
	u8 tx_antenna;
	जोड़ अणु
		काष्ठा अणु
			u8 cts_rate;
			__le16 output_घातer;
		पूर्ण __packed दीर्घbow;
		काष्ठा अणु
			u8 output_घातer;
			u8 cts_rate;
			u8 unalloc;
		पूर्ण __packed normal;
	पूर्ण __packed;
	u8 unalloc2[2];
	u8 align[];
पूर्ण __packed;

/* unit is ms */
#घोषणा P54_TX_FRAME_LIFETIME 2000
#घोषणा P54_TX_TIMEOUT 4000
#घोषणा P54_STATISTICS_UPDATE 5000

#घोषणा P54_FILTER_TYPE_NONE		0
#घोषणा P54_FILTER_TYPE_STATION		BIT(0)
#घोषणा P54_FILTER_TYPE_IBSS		BIT(1)
#घोषणा P54_FILTER_TYPE_AP		BIT(2)
#घोषणा P54_FILTER_TYPE_TRANSPARENT	BIT(3)
#घोषणा P54_FILTER_TYPE_PROMISCUOUS	BIT(4)
#घोषणा P54_FILTER_TYPE_HIBERNATE	BIT(5)
#घोषणा P54_FILTER_TYPE_NOACK		BIT(6)
#घोषणा P54_FILTER_TYPE_RX_DISABLED	BIT(7)

काष्ठा p54_setup_mac अणु
	__le16 mac_mode;
	u8 mac_addr[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	u8 rx_antenna;
	u8 rx_align;
	जोड़ अणु
		काष्ठा अणु
			__le32 basic_rate_mask;
			u8 rts_rates[8];
			__le32 rx_addr;
			__le16 max_rx;
			__le16 rxhw;
			__le16 wakeup_समयr;
			__le16 unalloc0;
		पूर्ण __packed v1;
		काष्ठा अणु
			__le32 rx_addr;
			__le16 max_rx;
			__le16 rxhw;
			__le16 समयr;
			__le16 truncate;
			__le32 basic_rate_mask;
			u8 sbss_offset;
			u8 mcast_winकरोw;
			u8 rx_rssi_threshold;
			u8 rx_ed_threshold;
			__le32 ref_घड़ी;
			__le16 lpf_bandwidth;
			__le16 osc_start_delay;
		पूर्ण __packed v2;
	पूर्ण __packed;
पूर्ण __packed;

#घोषणा P54_SETUP_V1_LEN 40
#घोषणा P54_SETUP_V2_LEN (माप(काष्ठा p54_setup_mac))

#घोषणा P54_SCAN_EXIT	BIT(0)
#घोषणा P54_SCAN_TRAP	BIT(1)
#घोषणा P54_SCAN_ACTIVE BIT(2)
#घोषणा P54_SCAN_FILTER BIT(3)

काष्ठा p54_scan_head अणु
	__le16 mode;
	__le16 dwell;
	u8 scan_params[20];
	__le16 freq;
पूर्ण __packed;

काष्ठा p54_pa_curve_data_sample अणु
	u8 rf_घातer;
	u8 pa_detector;
	u8 data_barker;
	u8 data_bpsk;
	u8 data_qpsk;
	u8 data_16qam;
	u8 data_64qam;
	u8 padding;
पूर्ण __packed;

काष्ठा p54_scan_body अणु
	u8 pa_poपूर्णांकs_per_curve;
	u8 val_barker;
	u8 val_bpsk;
	u8 val_qpsk;
	u8 val_16qam;
	u8 val_64qam;
	काष्ठा p54_pa_curve_data_sample curve_data[8];
	u8 dup_bpsk;
	u8 dup_qpsk;
	u8 dup_16qam;
	u8 dup_64qam;
पूर्ण __packed;

/*
 * Warning: Longbow's काष्ठाures are bogus.
 */
काष्ठा p54_channel_output_limit_दीर्घbow अणु
	__le16 rf_घातer_poपूर्णांकs[12];
पूर्ण __packed;

काष्ठा p54_pa_curve_data_sample_दीर्घbow अणु
	__le16 rf_घातer;
	__le16 pa_detector;
	काष्ठा अणु
		__le16 data[4];
	पूर्ण poपूर्णांकs[3] __packed;
पूर्ण __packed;

काष्ठा p54_scan_body_दीर्घbow अणु
	काष्ठा p54_channel_output_limit_दीर्घbow घातer_limits;
	काष्ठा p54_pa_curve_data_sample_दीर्घbow curve_data[8];
	__le16 unkn[6];		/* maybe more घातer_limits or rate_mask */
पूर्ण __packed;

जोड़ p54_scan_body_जोड़ अणु
	काष्ठा p54_scan_body normal;
	काष्ठा p54_scan_body_दीर्घbow दीर्घbow;
पूर्ण __packed;

काष्ठा p54_scan_tail_rate अणु
	__le32 basic_rate_mask;
	u8 rts_rates[8];
पूर्ण __packed;

काष्ठा p54_led अणु
	__le16 flags;
	__le16 mask[2];
	__le16 delay[2];
पूर्ण __packed;

काष्ठा p54_edcf अणु
	u8 flags;
	u8 slotसमय;
	u8 sअगरs;
	u8 eofpad;
	काष्ठा p54_edcf_queue_param queue[8];
	u8 mapping[4];
	__le16 frameburst;
	__le16 round_trip_delay;
पूर्ण __packed;

काष्ठा p54_statistics अणु
	__le32 rx_success;
	__le32 rx_bad_fcs;
	__le32 rx_पात;
	__le32 rx_पात_phy;
	__le32 rts_success;
	__le32 rts_fail;
	__le32 tsf32;
	__le32 airसमय;
	__le32 noise;
	__le32 sample_noise[8];
	__le32 sample_cca;
	__le32 sample_tx;
पूर्ण __packed;

काष्ठा p54_xbow_synth अणु
	__le16 magic1;
	__le16 magic2;
	__le16 freq;
	u32 padding[5];
पूर्ण __packed;

काष्ठा p54_समयr अणु
	__le32 पूर्णांकerval;
पूर्ण __packed;

काष्ठा p54_keycache अणु
	u8 entry;
	u8 key_id;
	u8 mac[ETH_ALEN];
	u8 padding[2];
	u8 key_type;
	u8 key_len;
	u8 key[24];
पूर्ण __packed;

काष्ठा p54_burst अणु
	u8 flags;
	u8 queue;
	u8 backlog;
	u8 pad;
	__le16 durations[32];
पूर्ण __packed;

काष्ठा p54_psm_पूर्णांकerval अणु
	__le16 पूर्णांकerval;
	__le16 periods;
पूर्ण __packed;

#घोषणा P54_PSM_CAM			0
#घोषणा P54_PSM				BIT(0)
#घोषणा P54_PSM_DTIM			BIT(1)
#घोषणा P54_PSM_MCBC			BIT(2)
#घोषणा P54_PSM_CHECKSUM		BIT(3)
#घोषणा P54_PSM_SKIP_MORE_DATA		BIT(4)
#घोषणा P54_PSM_BEACON_TIMEOUT		BIT(5)
#घोषणा P54_PSM_HFOSLEEP		BIT(6)
#घोषणा P54_PSM_AUTOSWITCH_SLEEP	BIT(7)
#घोषणा P54_PSM_LPIT			BIT(8)
#घोषणा P54_PSM_BF_UCAST_SKIP		BIT(9)
#घोषणा P54_PSM_BF_MCAST_SKIP		BIT(10)

काष्ठा p54_psm अणु
	__le16 mode;
	__le16 aid;
	काष्ठा p54_psm_पूर्णांकerval पूर्णांकervals[4];
	u8 beacon_rssi_skip_max;
	u8 rssi_delta_threshold;
	u8 nr;
	u8 exclude[1];
पूर्ण __packed;

#घोषणा MC_FILTER_ADDRESS_NUM 4

काष्ठा p54_group_address_table अणु
	__le16 filter_enable;
	__le16 num_address;
	u8 mac_list[MC_FILTER_ADDRESS_NUM][ETH_ALEN];
पूर्ण __packed;

काष्ठा p54_txcancel अणु
	__le32 req_id;
पूर्ण __packed;

काष्ठा p54_sta_unlock अणु
	u8 addr[ETH_ALEN];
	u16 padding;
पूर्ण __packed;

#घोषणा P54_TIM_CLEAR BIT(15)
काष्ठा p54_tim अणु
	u8 count;
	u8 padding[3];
	__le16 entry[8];
पूर्ण __packed;

काष्ठा p54_cce_quiet अणु
	__le32 period;
पूर्ण __packed;

काष्ठा p54_bt_balancer अणु
	__le16 prio_thresh;
	__le16 acl_thresh;
पूर्ण __packed;

काष्ठा p54_arp_table अणु
	__le16 filter_enable;
	u8 ipv4_addr[4];
पूर्ण __packed;

/* LED control */
पूर्णांक p54_set_leds(काष्ठा p54_common *priv);
पूर्णांक p54_init_leds(काष्ठा p54_common *priv);
व्योम p54_unरेजिस्टर_leds(काष्ठा p54_common *priv);

/* xmit functions */
व्योम p54_tx_80211(काष्ठा ieee80211_hw *dev,
		  काष्ठा ieee80211_tx_control *control,
		  काष्ठा sk_buff *skb);
पूर्णांक p54_tx_cancel(काष्ठा p54_common *priv, __le32 req_id);
व्योम p54_tx(काष्ठा p54_common *priv, काष्ठा sk_buff *skb);

/* synth/phy configuration */
पूर्णांक p54_init_xbow_synth(काष्ठा p54_common *priv);
पूर्णांक p54_scan(काष्ठा p54_common *priv, u16 mode, u16 dwell);

/* MAC */
पूर्णांक p54_sta_unlock(काष्ठा p54_common *priv, u8 *addr);
पूर्णांक p54_update_beacon_tim(काष्ठा p54_common *priv, u16 aid, bool set);
पूर्णांक p54_setup_mac(काष्ठा p54_common *priv);
पूर्णांक p54_set_ps(काष्ठा p54_common *priv);
पूर्णांक p54_fetch_statistics(काष्ठा p54_common *priv);
पूर्णांक p54_set_groupfilter(काष्ठा p54_common *priv);

/* e/v DCF setup */
पूर्णांक p54_set_edcf(काष्ठा p54_common *priv);

/* cryptographic engine */
पूर्णांक p54_upload_key(काष्ठा p54_common *priv, u8 algo, पूर्णांक slot,
		   u8 idx, u8 len, u8 *addr, u8* key);

/* eeprom */
पूर्णांक p54_करोwnload_eeprom(काष्ठा p54_common *priv, व्योम *buf,
			u16 offset, u16 len);
काष्ठा p54_rssi_db_entry *p54_rssi_find(काष्ठा p54_common *p, स्थिर u16 freq);

/* utility */
u8 *p54_find_ie(काष्ठा sk_buff *skb, u8 ie);

#पूर्ण_अगर /* LMAC_H */
