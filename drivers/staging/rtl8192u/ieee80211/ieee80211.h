<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Merged with मुख्यline ieee80211.h in Aug 2004.  Original ieee802_11
 * reमुख्यs copyright by the original authors
 *
 * Portions of the merged code are based on Host AP (software wireless
 * LAN access poपूर्णांक) driver क्रम Intersil Prism2/2.5/3.
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <jkmaline@cc.hut.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * Adaption to a generic IEEE 802.11 stack by James Ketrenos
 * <jketreno@linux.पूर्णांकel.com>
 * Copyright (c) 2004, Intel Corporation
 *
 * Modअगरied क्रम Realtek's wi-fi cards by Andrea Merello
 * <andrea.merello@gmail.com>
 */
#अगर_अघोषित IEEE80211_H
#घोषणा IEEE80211_H
#समावेश <linux/अगर_ether.h> /* ETH_ALEN */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/delay.h>
#समावेश <linux/wireless.h>
#समावेश <linux/ieee80211.h>

#समावेश "rtl819x_HT.h"
#समावेश "rtl819x_BA.h"
#समावेश "rtl819x_TS.h"


#अगर_अघोषित IW_MODE_MONITOR
#घोषणा IW_MODE_MONITOR 6
#पूर्ण_अगर

#अगर_अघोषित IWEVCUSTOM
#घोषणा IWEVCUSTOM 0x8c02
#पूर्ण_अगर

#घोषणा KEY_TYPE_NA		0x0
#घोषणा KEY_TYPE_WEP40		0x1
#घोषणा KEY_TYPE_TKIP		0x2
#घोषणा KEY_TYPE_CCMP		0x4
#घोषणा KEY_TYPE_WEP104		0x5

/* added क्रम rtl819x tx procedure */
#घोषणा MAX_QUEUE_SIZE		0x10

//
// 8190 queue mapping
//
#घोषणा BK_QUEUE                               0
#घोषणा BE_QUEUE                               1
#घोषणा VI_QUEUE                               2
#घोषणा VO_QUEUE                               3
#घोषणा HCCA_QUEUE                             4
#घोषणा TXCMD_QUEUE                            5
#घोषणा MGNT_QUEUE                             6
#घोषणा HIGH_QUEUE                             7
#घोषणा BEACON_QUEUE                           8

#घोषणा LOW_QUEUE                              BE_QUEUE
#घोषणा NORMAL_QUEUE                           MGNT_QUEUE

//added by amy क्रम ps
#घोषणा SWRF_TIMEOUT				50

//added by amy क्रम LEAP related
#घोषणा IE_CISCO_FLAG_POSITION		0x08	// Flag byte: byte 8, numbered from 0.
#घोषणा SUPPORT_CKIP_MIC			0x08	// bit3
#घोषणा SUPPORT_CKIP_PK			0x10	// bit4
/* defined क्रम skb cb field */
/* At most 28 byte */
काष्ठा cb_desc अणु
	/* Tx Desc Related flags (8-9) */
	u8 bLastIniPkt:1;
	u8 bCmdOrInit:1;
	u8 bFirstSeg:1;
	u8 bLastSeg:1;
	u8 bEncrypt:1;
	u8 bTxDisableRateFallBack:1;
	u8 bTxUseDriverAssingedRate:1;
	u8 bHwSec:1; //indicate whether use Hw security. WB

	u8 reserved1;

	/* Tx Firmware Relaged flags (10-11)*/
	u8 bCTSEnable:1;
	u8 bRTSEnable:1;
	u8 bUseShortGI:1;
	u8 bUseShortPreamble:1;
	u8 bTxEnableFwCalcDur:1;
	u8 bAMPDUEnable:1;
	u8 bRTSSTBC:1;
	u8 RTSSC:1;

	u8 bRTSBW:1;
	u8 bPacketBW:1;
	u8 bRTSUseShortPreamble:1;
	u8 bRTSUseShortGI:1;
	u8 bMulticast:1;
	u8 bBroadcast:1;
	//u8 reserved2:2;
	u8 drv_agg_enable:1;
	u8 reserved2:1;

	/* Tx Desc related element(12-19) */
	u8 rata_index;
	u8 queue_index;
	//u8 reserved3;
	//u8 reserved4;
	u16 txbuf_size;
	//u8 reserved5;
	u8 RATRIndex;
	u8 reserved6;
	u8 reserved7;
	u8 reserved8;

	/* Tx firmware related element(20-27) */
	u8 data_rate;
	u8 rts_rate;
	u8 ampdu_factor;
	u8 ampdu_density;
	//u8 reserved9;
	//u8 reserved10;
	//u8 reserved11;
	u8 DrvAggrNum;
	u16 pkt_size;
	u8 reserved12;
पूर्ण;

/*--------------------------Define -------------------------------------------*/
#घोषणा MGN_1M                  0x02
#घोषणा MGN_2M                  0x04
#घोषणा MGN_5_5M                0x0b
#घोषणा MGN_11M                 0x16

#घोषणा MGN_6M                  0x0c
#घोषणा MGN_9M                  0x12
#घोषणा MGN_12M                 0x18
#घोषणा MGN_18M                 0x24
#घोषणा MGN_24M                 0x30
#घोषणा MGN_36M                 0x48
#घोषणा MGN_48M                 0x60
#घोषणा MGN_54M                 0x6c

#घोषणा MGN_MCS0                0x80
#घोषणा MGN_MCS1                0x81
#घोषणा MGN_MCS2                0x82
#घोषणा MGN_MCS3                0x83
#घोषणा MGN_MCS4                0x84
#घोषणा MGN_MCS5                0x85
#घोषणा MGN_MCS6                0x86
#घोषणा MGN_MCS7                0x87
#घोषणा MGN_MCS8                0x88
#घोषणा MGN_MCS9                0x89
#घोषणा MGN_MCS10               0x8a
#घोषणा MGN_MCS11               0x8b
#घोषणा MGN_MCS12               0x8c
#घोषणा MGN_MCS13               0x8d
#घोषणा MGN_MCS14               0x8e
#घोषणा MGN_MCS15               0x8f

#घोषणा aSअगरsTime ((priv->ieee80211->current_network.mode == IEEE_A ||     \
		    priv->ieee80211->current_network.mode == IEEE_N_24G || \
		    priv->ieee80211->current_network.mode == IEEE_N_5G) ?  \
		   16 : 10)

#घोषणा MGMT_QUEUE_NUM 5

#घोषणा IEEE_CMD_SET_WPA_PARAM			1
#घोषणा	IEEE_CMD_SET_WPA_IE			2
#घोषणा IEEE_CMD_SET_ENCRYPTION			3
#घोषणा IEEE_CMD_MLME				4

#घोषणा IEEE_PARAM_WPA_ENABLED			1
#घोषणा IEEE_PARAM_TKIP_COUNTERMEASURES		2
#घोषणा IEEE_PARAM_DROP_UNENCRYPTED		3
#घोषणा IEEE_PARAM_PRIVACY_INVOKED		4
#घोषणा IEEE_PARAM_AUTH_ALGS			5
#घोषणा IEEE_PARAM_IEEE_802_1X			6
//It should consistent with the driver_XXX.c
//   David, 2006.9.26
#घोषणा IEEE_PARAM_WPAX_SELECT			7
//Added क्रम notअगरy the encryption type selection
//   David, 2006.9.26
#घोषणा IEEE_PROTO_WPA				1
#घोषणा IEEE_PROTO_RSN				2
//Added क्रम notअगरy the encryption type selection
//   David, 2006.9.26
#घोषणा IEEE_WPAX_USEGROUP			0
#घोषणा IEEE_WPAX_WEP40				1
#घोषणा IEEE_WPAX_TKIP				2
#घोषणा IEEE_WPAX_WRAP				3
#घोषणा IEEE_WPAX_CCMP				4
#घोषणा IEEE_WPAX_WEP104			5

#घोषणा IEEE_KEY_MGMT_IEEE8021X			1
#घोषणा IEEE_KEY_MGMT_PSK			2

#घोषणा IEEE_MLME_STA_DEAUTH			1
#घोषणा IEEE_MLME_STA_DISASSOC			2


#घोषणा IEEE_CRYPT_ERR_UNKNOWN_ALG		2
#घोषणा IEEE_CRYPT_ERR_UNKNOWN_ADDR		3
#घोषणा IEEE_CRYPT_ERR_CRYPT_INIT_FAILED	4
#घोषणा IEEE_CRYPT_ERR_KEY_SET_FAILED		5
#घोषणा IEEE_CRYPT_ERR_TX_KEY_SET_FAILED	6
#घोषणा IEEE_CRYPT_ERR_CARD_CONF_FAILED		7


#घोषणा	IEEE_CRYPT_ALG_NAME_LEN			16

#घोषणा MAX_IE_LEN  0xff

// added क्रम kernel conflict
#घोषणा ieee80211_crypt_deinit_entries	ieee80211_crypt_deinit_entries_rsl
#घोषणा ieee80211_crypt_deinit_handler	ieee80211_crypt_deinit_handler_rsl
#घोषणा ieee80211_crypt_delayed_deinit	ieee80211_crypt_delayed_deinit_rsl
#घोषणा ieee80211_रेजिस्टर_crypto_ops	ieee80211_रेजिस्टर_crypto_ops_rsl
#घोषणा ieee80211_unरेजिस्टर_crypto_ops ieee80211_unरेजिस्टर_crypto_ops_rsl
#घोषणा ieee80211_get_crypto_ops	ieee80211_get_crypto_ops_rsl

#घोषणा ieee80211_ccmp_null		ieee80211_ccmp_null_rsl

#घोषणा ieee80211_tkip_null		ieee80211_tkip_null_rsl

#घोषणा मुक्त_ieee80211			मुक्त_ieee80211_rsl
#घोषणा alloc_ieee80211			alloc_ieee80211_rsl

#घोषणा ieee80211_rx			ieee80211_rx_rsl
#घोषणा ieee80211_rx_mgt		ieee80211_rx_mgt_rsl

#घोषणा ieee80211_get_beacon		ieee80211_get_beacon_rsl
#घोषणा ieee80211_wake_queue		ieee80211_wake_queue_rsl
#घोषणा ieee80211_stop_queue		ieee80211_stop_queue_rsl
#घोषणा ieee80211_reset_queue		ieee80211_reset_queue_rsl
#घोषणा ieee80211_sofपंचांगac_stop_protocol	ieee80211_sofपंचांगac_stop_protocol_rsl
#घोषणा ieee80211_sofपंचांगac_start_protocol ieee80211_sofपंचांगac_start_protocol_rsl
#घोषणा ieee80211_is_लघुslot		ieee80211_is_लघुslot_rsl
#घोषणा ieee80211_is_54g		ieee80211_is_54g_rsl
#घोषणा ieee80211_wpa_supplicant_ioctl	ieee80211_wpa_supplicant_ioctl_rsl
#घोषणा ieee80211_ps_tx_ack		ieee80211_ps_tx_ack_rsl
#घोषणा ieee80211_sofपंचांगac_xmit		ieee80211_sofपंचांगac_xmit_rsl
#घोषणा ieee80211_stop_send_beacons	ieee80211_stop_send_beacons_rsl
#घोषणा notअगरy_wx_assoc_event		notअगरy_wx_assoc_event_rsl
#घोषणा SendDisassociation		SendDisassociation_rsl
#घोषणा ieee80211_disassociate		ieee80211_disassociate_rsl
#घोषणा ieee80211_start_send_beacons	ieee80211_start_send_beacons_rsl
#घोषणा ieee80211_stop_scan		ieee80211_stop_scan_rsl
#घोषणा ieee80211_send_probe_requests	ieee80211_send_probe_requests_rsl
#घोषणा ieee80211_sofपंचांगac_scan_syncro	ieee80211_sofपंचांगac_scan_syncro_rsl
#घोषणा ieee80211_start_scan_syncro	ieee80211_start_scan_syncro_rsl

#घोषणा ieee80211_wx_get_essid		ieee80211_wx_get_essid_rsl
#घोषणा ieee80211_wx_set_essid		ieee80211_wx_set_essid_rsl
#घोषणा ieee80211_wx_set_rate		ieee80211_wx_set_rate_rsl
#घोषणा ieee80211_wx_get_rate		ieee80211_wx_get_rate_rsl
#घोषणा ieee80211_wx_set_wap		ieee80211_wx_set_wap_rsl
#घोषणा ieee80211_wx_get_wap		ieee80211_wx_get_wap_rsl
#घोषणा ieee80211_wx_set_mode		ieee80211_wx_set_mode_rsl
#घोषणा ieee80211_wx_get_mode		ieee80211_wx_get_mode_rsl
#घोषणा ieee80211_wx_set_scan		ieee80211_wx_set_scan_rsl
#घोषणा ieee80211_wx_get_freq		ieee80211_wx_get_freq_rsl
#घोषणा ieee80211_wx_set_freq		ieee80211_wx_set_freq_rsl
#घोषणा ieee80211_wx_set_rawtx		ieee80211_wx_set_rawtx_rsl
#घोषणा ieee80211_wx_get_name		ieee80211_wx_get_name_rsl
#घोषणा ieee80211_wx_set_घातer		ieee80211_wx_set_घातer_rsl
#घोषणा ieee80211_wx_get_घातer		ieee80211_wx_get_घातer_rsl
#घोषणा ieee80211_wlan_frequencies	ieee80211_wlan_frequencies_rsl
#घोषणा ieee80211_wx_set_rts		ieee80211_wx_set_rts_rsl
#घोषणा ieee80211_wx_get_rts		ieee80211_wx_get_rts_rsl

#घोषणा ieee80211_txb_मुक्त		ieee80211_txb_मुक्त_rsl

#घोषणा ieee80211_wx_set_gen_ie		ieee80211_wx_set_gen_ie_rsl
#घोषणा ieee80211_wx_get_scan		ieee80211_wx_get_scan_rsl
#घोषणा ieee80211_wx_set_encode		ieee80211_wx_set_encode_rsl
#घोषणा ieee80211_wx_get_encode		ieee80211_wx_get_encode_rsl
#घोषणा ieee80211_wx_set_mlme		ieee80211_wx_set_mlme_rsl
#घोषणा ieee80211_wx_set_auth		ieee80211_wx_set_auth_rsl
#घोषणा ieee80211_wx_set_encode_ext	ieee80211_wx_set_encode_ext_rsl
#घोषणा ieee80211_wx_get_encode_ext	ieee80211_wx_get_encode_ext_rsl


काष्ठा ieee_param अणु
	u32 cmd;
	u8 sta_addr[ETH_ALEN];
	जोड़ अणु
		काष्ठा अणु
			u8 name;
			u32 value;
		पूर्ण wpa_param;
		काष्ठा अणु
			u32 len;
			u8 reserved[32];
			u8 data[0];
		पूर्ण wpa_ie;
		काष्ठाअणु
			पूर्णांक command;
			पूर्णांक reason_code;
		पूर्ण mlme;
		काष्ठा अणु
			u8 alg[IEEE_CRYPT_ALG_NAME_LEN];
			u8 set_tx;
			u32 err;
			u8 idx;
			u8 seq[8]; /* sequence counter (set: RX, get: TX) */
			u16 key_len;
			u8 key[0];
		पूर्ण crypt;
	पूर्ण u;
पूर्ण;


// linux under 2.6.9 release may not support it, so modअगरy it क्रम common use
#घोषणा IEEE80211_DATA_LEN		2304
/* Maximum size क्रम the MA-UNITDATA primitive, 802.11 standard section
 *   6.2.1.1.2.
 *
 *   The figure in section 7.1.2 suggests a body size of up to 2312
 *   bytes is allowed, which is a bit confusing, I suspect this
 *   represents the 2304 bytes of real data, plus a possible 8 bytes of
 *   WEP IV and ICV. (this पूर्णांकerpretation suggested by Ramiro Barreiro)
 */
#घोषणा IEEE80211_1ADDR_LEN 10
#घोषणा IEEE80211_2ADDR_LEN 16
#घोषणा IEEE80211_3ADDR_LEN 24
#घोषणा IEEE80211_4ADDR_LEN 30
#घोषणा IEEE80211_FCS_LEN    4
#घोषणा IEEE80211_HLEN                  (IEEE80211_4ADDR_LEN)
#घोषणा IEEE80211_FRAME_LEN             (IEEE80211_DATA_LEN + IEEE80211_HLEN)
#घोषणा IEEE80211_MGMT_HDR_LEN 24
#घोषणा IEEE80211_DATA_HDR3_LEN 24
#घोषणा IEEE80211_DATA_HDR4_LEN 30

#घोषणा MIN_FRAG_THRESHOLD     256U
#घोषणा MAX_FRAG_THRESHOLD     2346U


/* Frame control field स्थिरants */
#घोषणा IEEE80211_FCTL_VERS		0x0003
#घोषणा IEEE80211_FCTL_FTYPE		0x000c
#घोषणा IEEE80211_FCTL_STYPE		0x00f0
#घोषणा IEEE80211_FCTL_FRAMETYPE	0x00fc
#घोषणा IEEE80211_FCTL_TODS		0x0100
#घोषणा IEEE80211_FCTL_FROMDS		0x0200
#घोषणा IEEE80211_FCTL_DSTODS		0x0300 //added by david
#घोषणा IEEE80211_FCTL_MOREFRAGS	0x0400
#घोषणा IEEE80211_FCTL_RETRY		0x0800
#घोषणा IEEE80211_FCTL_PM		0x1000
#घोषणा IEEE80211_FCTL_MOREDATA		0x2000
#घोषणा IEEE80211_FCTL_WEP		0x4000
#घोषणा IEEE80211_FCTL_ORDER		0x8000

#घोषणा IEEE80211_FTYPE_MGMT		0x0000
#घोषणा IEEE80211_FTYPE_CTL		0x0004
#घोषणा IEEE80211_FTYPE_DATA		0x0008

/* management */
#घोषणा IEEE80211_STYPE_ASSOC_REQ	0x0000
#घोषणा IEEE80211_STYPE_ASSOC_RESP	0x0010
#घोषणा IEEE80211_STYPE_REASSOC_REQ	0x0020
#घोषणा IEEE80211_STYPE_REASSOC_RESP	0x0030
#घोषणा IEEE80211_STYPE_PROBE_REQ	0x0040
#घोषणा IEEE80211_STYPE_PROBE_RESP	0x0050
#घोषणा IEEE80211_STYPE_BEACON		0x0080
#घोषणा IEEE80211_STYPE_ATIM		0x0090
#घोषणा IEEE80211_STYPE_DISASSOC	0x00A0
#घोषणा IEEE80211_STYPE_AUTH		0x00B0
#घोषणा IEEE80211_STYPE_DEAUTH		0x00C0
#घोषणा IEEE80211_STYPE_MANAGE_ACT	0x00D0

/* control */
#घोषणा IEEE80211_STYPE_PSPOLL		0x00A0
#घोषणा IEEE80211_STYPE_RTS		0x00B0
#घोषणा IEEE80211_STYPE_CTS		0x00C0
#घोषणा IEEE80211_STYPE_ACK		0x00D0
#घोषणा IEEE80211_STYPE_CFEND		0x00E0
#घोषणा IEEE80211_STYPE_CFENDACK	0x00F0
#घोषणा IEEE80211_STYPE_BLOCKACK	0x0094

/* data */
#घोषणा IEEE80211_STYPE_DATA		0x0000
#घोषणा IEEE80211_STYPE_DATA_CFACK	0x0010
#घोषणा IEEE80211_STYPE_DATA_CFPOLL	0x0020
#घोषणा IEEE80211_STYPE_DATA_CFACKPOLL	0x0030
#घोषणा IEEE80211_STYPE_शून्यFUNC	0x0040
#घोषणा IEEE80211_STYPE_CFACK		0x0050
#घोषणा IEEE80211_STYPE_CFPOLL		0x0060
#घोषणा IEEE80211_STYPE_CFACKPOLL	0x0070
#घोषणा IEEE80211_STYPE_QOS_DATA	0x0080 //added क्रम WMM 2006/8/2
#घोषणा IEEE80211_STYPE_QOS_शून्य	0x00C0

#घोषणा IEEE80211_SCTL_FRAG		0x000F
#घोषणा IEEE80211_SCTL_SEQ		0xFFF0

/* QOS control */
#घोषणा IEEE80211_QCTL_TID              0x000F

#घोषणा	FC_QOS_BIT					BIT(7)
#घोषणा IsDataFrame(pdu)			(((pdu[0] & 0x0C) == 0x08) ? true : false)
#घोषणा	IsLegacyDataFrame(pdu)	(IsDataFrame(pdu) && (!(pdu[0] & FC_QOS_BIT)))
//added by wb. Is this right?
#घोषणा IsQoSDataFrame(pframe)  ((*(u16 *)pframe & (IEEE80211_STYPE_QOS_DATA | IEEE80211_FTYPE_DATA)) == (IEEE80211_STYPE_QOS_DATA | IEEE80211_FTYPE_DATA))
#घोषणा Frame_Order(pframe)     (*(u16 *)pframe & IEEE80211_FCTL_ORDER)
#घोषणा SN_LESS(a, b)		(((a - b) & 0x800) != 0)
#घोषणा SN_EQUAL(a, b)	(a == b)
#घोषणा MAX_DEV_ADDR_SIZE 8
प्रकार क्रमागत _ACT_CATEGORY अणु
	ACT_CAT_QOS = 1,
	ACT_CAT_DLS = 2,
	ACT_CAT_BA  = 3,
	ACT_CAT_HT  = 7,
	ACT_CAT_WMM = 17,
पूर्ण ACT_CATEGORY, *PACT_CATEGORY;

प्रकार क्रमागत _TS_ACTION अणु
	ACT_ADDTSREQ = 0,
	ACT_ADDTSRSP = 1,
	ACT_DELTS    = 2,
	ACT_SCHEDULE = 3,
पूर्ण TS_ACTION, *PTS_ACTION;

प्रकार क्रमागत _BA_ACTION अणु
	ACT_ADDBAREQ = 0,
	ACT_ADDBARSP = 1,
	ACT_DELBA    = 2,
पूर्ण BA_ACTION, *PBA_ACTION;

प्रकार क्रमागत _InitialGainOpType अणु
	IG_Backup = 0,
	IG_Restore,
	IG_Max
पूर्ण InitialGainOpType;

/* debug macros */
#घोषणा CONFIG_IEEE80211_DEBUG
#अगर_घोषित CONFIG_IEEE80211_DEBUG
बाह्य u32 ieee80211_debug_level;
#घोषणा IEEE80211_DEBUG(level, fmt, args...) \
करो अणु अगर (ieee80211_debug_level & (level)) \
  prपूर्णांकk(KERN_DEBUG "ieee80211: " fmt, ## args); पूर्ण जबतक (0)
//wb added to debug out data buf
//अगर you want prपूर्णांक DATA buffer related BA, please set ieee80211_debug_level to DATA|BA
#घोषणा IEEE80211_DEBUG_DATA(level, data, datalen)                             \
	करो अणु अगर ((ieee80211_debug_level & (level)) == (level))                 \
		अणु                                                              \
			पूर्णांक i;                                                 \
			u8 *pdata = (u8 *)data;                                \
			prपूर्णांकk(KERN_DEBUG "ieee80211: %s()\n", __func__);      \
			क्रम (i = 0; i < (पूर्णांक)(datalen); i++) अणु                 \
				prपूर्णांकk("%2x ", pdata[i]);                      \
				अगर ((i + 1) % 16 == 0)                         \
					prपूर्णांकk("\n");                          \
			पूर्ण                                                      \
			prपूर्णांकk("\n");                                          \
		पूर्ण                                                              \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा IEEE80211_DEBUG (level, fmt, args...) करो अणुपूर्ण जबतक (0)
#घोषणा IEEE80211_DEBUG_DATA (level, data, datalen) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर	/* CONFIG_IEEE80211_DEBUG */

/* debug macros not dependent on CONFIG_IEEE80211_DEBUG */

/*
 * To use the debug प्रणाली;
 *
 * If you are defining a new debug classअगरication, simply add it to the #घोषणा
 * list here in the क्रमm of:
 *
 * #घोषणा IEEE80211_DL_xxxx VALUE
 *
 * shअगरting value to the left one bit from the previous entry.  xxxx should be
 * the name of the classअगरication (क्रम example, WEP)
 *
 * You then need to either add a IEEE80211_xxxx_DEBUG() macro definition क्रम your
 * classअगरication, or use IEEE80211_DEBUG(IEEE80211_DL_xxxx, ...) whenever you want
 * to send output to that classअगरication.
 *
 * To add your debug level to the list of levels seen when you perक्रमm
 *
 * % cat /proc/net/ipw/debug_level
 *
 * you simply need to add your entry to the ipw_debug_levels array.
 *
 * If you करो not see debug_level in /proc/net/ipw then you करो not have
 * CONFIG_IEEE80211_DEBUG defined in your kernel configuration
 *
 */

#घोषणा IEEE80211_DL_INFO          (1<<0)
#घोषणा IEEE80211_DL_WX            (1<<1)
#घोषणा IEEE80211_DL_SCAN          (1<<2)
#घोषणा IEEE80211_DL_STATE         (1<<3)
#घोषणा IEEE80211_DL_MGMT          (1<<4)
#घोषणा IEEE80211_DL_FRAG          (1<<5)
#घोषणा IEEE80211_DL_EAP           (1<<6)
#घोषणा IEEE80211_DL_DROP          (1<<7)

#घोषणा IEEE80211_DL_TX            (1<<8)
#घोषणा IEEE80211_DL_RX            (1<<9)

#घोषणा IEEE80211_DL_HT		   (1<<10)  //HT
#घोषणा IEEE80211_DL_BA		   (1<<11)  //ba
#घोषणा IEEE80211_DL_TS		   (1<<12)  //TS
#घोषणा IEEE80211_DL_QOS           (1<<13)
#घोषणा IEEE80211_DL_REORDER	   (1<<14)
#घोषणा IEEE80211_DL_IOT	   (1<<15)
#घोषणा IEEE80211_DL_IPS	   (1<<16)
#घोषणा IEEE80211_DL_TRACE	   (1<<29)  //trace function, need to user net_ratelimit() together in order not to prपूर्णांक too much to the screen
#घोषणा IEEE80211_DL_DATA	   (1<<30)   //use this flag to control whether prपूर्णांक data buf out.
#घोषणा IEEE80211_DL_ERR	   (1<<31)   //always खोलो
#घोषणा IEEE80211_ERROR(f, a...) prपूर्णांकk(KERN_ERR "ieee80211: " f, ## a)
#घोषणा IEEE80211_WARNING(f, a...) prपूर्णांकk(KERN_WARNING "ieee80211: " f, ## a)
#घोषणा IEEE80211_DEBUG_INFO(f, a...)   IEEE80211_DEBUG(IEEE80211_DL_INFO, f, ## a)

#घोषणा IEEE80211_DEBUG_WX(f, a...)     IEEE80211_DEBUG(IEEE80211_DL_WX, f, ## a)
#घोषणा IEEE80211_DEBUG_SCAN(f, a...)   IEEE80211_DEBUG(IEEE80211_DL_SCAN, f, ## a)
#घोषणा IEEE80211_DEBUG_STATE(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_STATE, f, ## a)
#घोषणा IEEE80211_DEBUG_MGMT(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_MGMT, f, ## a)
#घोषणा IEEE80211_DEBUG_FRAG(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_FRAG, f, ## a)
#घोषणा IEEE80211_DEBUG_EAP(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_EAP, f, ## a)
#घोषणा IEEE80211_DEBUG_DROP(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_DROP, f, ## a)
#घोषणा IEEE80211_DEBUG_TX(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_TX, f, ## a)
#घोषणा IEEE80211_DEBUG_RX(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_RX, f, ## a)
#घोषणा IEEE80211_DEBUG_QOS(f, a...)  IEEE80211_DEBUG(IEEE80211_DL_QOS, f, ## a)

#समावेश <linux/अगर_arp.h> /* ARPHRD_ETHER */

#अगर_अघोषित WIRELESS_SPY
#घोषणा WIRELESS_SPY		// enable iwspy support
#पूर्ण_अगर
#समावेश <net/iw_handler.h>	// new driver API

#अगर_अघोषित ETH_P_PAE
#घोषणा ETH_P_PAE 0x888E /* Port Access Entity (IEEE 802.1X) */
#पूर्ण_अगर /* ETH_P_PAE */

#घोषणा ETH_P_PREAUTH 0x88C7 /* IEEE 802.11i pre-authentication */

#अगर_अघोषित ETH_P_80211_RAW
#घोषणा ETH_P_80211_RAW (ETH_P_ECONET + 1)
#पूर्ण_अगर

/* IEEE 802.11 defines */

#घोषणा P80211_OUI_LEN 3

काष्ठा ieee80211_snap_hdr अणु

	u8    dsap;   /* always 0xAA */
	u8    ssap;   /* always 0xAA */
	u8    ctrl;   /* always 0x03 */
	u8    oui[P80211_OUI_LEN];    /* organizational universal id */

पूर्ण __packed;

#घोषणा SNAP_SIZE माप(काष्ठा ieee80211_snap_hdr)

#घोषणा WLAN_FC_GET_VERS(fc) ((fc) & IEEE80211_FCTL_VERS)
#घोषणा WLAN_FC_GET_TYPE(fc) ((fc) & IEEE80211_FCTL_FTYPE)
#घोषणा WLAN_FC_GET_STYPE(fc) ((fc) & IEEE80211_FCTL_STYPE)

#घोषणा WLAN_FC_GET_FRAMETYPE(fc) ((fc) & IEEE80211_FCTL_FRAMETYPE)
#घोषणा WLAN_GET_SEQ_FRAG(seq) ((seq) & IEEE80211_SCTL_FRAG)
#घोषणा WLAN_GET_SEQ_SEQ(seq)  (((seq) & IEEE80211_SCTL_SEQ) >> 4)

#घोषणा WLAN_CAPABILITY_BSS (1<<0)
#घोषणा WLAN_CAPABILITY_IBSS (1<<1)
#घोषणा WLAN_CAPABILITY_CF_POLLABLE (1<<2)
#घोषणा WLAN_CAPABILITY_CF_POLL_REQUEST (1<<3)
#घोषणा WLAN_CAPABILITY_PRIVACY (1<<4)
#घोषणा WLAN_CAPABILITY_SHORT_PREAMBLE (1<<5)
#घोषणा WLAN_CAPABILITY_PBCC (1<<6)
#घोषणा WLAN_CAPABILITY_CHANNEL_AGILITY (1<<7)
#घोषणा WLAN_CAPABILITY_SPECTRUM_MGMT (1<<8)
#घोषणा WLAN_CAPABILITY_QOS (1<<9)
#घोषणा WLAN_CAPABILITY_SHORT_SLOT (1<<10)
#घोषणा WLAN_CAPABILITY_DSSS_OFDM (1<<13)

/* 802.11g ERP inक्रमmation element */
#घोषणा WLAN_ERP_NON_ERP_PRESENT (1<<0)
#घोषणा WLAN_ERP_USE_PROTECTION (1<<1)
#घोषणा WLAN_ERP_BARKER_PREAMBLE (1<<2)

#घोषणा IEEE80211_STATMASK_SIGNAL (1<<0)
#घोषणा IEEE80211_STATMASK_RSSI (1<<1)
#घोषणा IEEE80211_STATMASK_NOISE (1<<2)
#घोषणा IEEE80211_STATMASK_RATE (1<<3)
#घोषणा IEEE80211_STATMASK_WEMASK 0x7

#घोषणा IEEE80211_CCK_MODULATION    (1<<0)
#घोषणा IEEE80211_OFDM_MODULATION   (1<<1)

#घोषणा IEEE80211_24GHZ_BAND     (1<<0)
#घोषणा IEEE80211_52GHZ_BAND     (1<<1)

#घोषणा IEEE80211_CCK_RATE_LEN			4
#घोषणा IEEE80211_CCK_RATE_1MB			0x02
#घोषणा IEEE80211_CCK_RATE_2MB			0x04
#घोषणा IEEE80211_CCK_RATE_5MB			0x0B
#घोषणा IEEE80211_CCK_RATE_11MB			0x16
#घोषणा IEEE80211_OFDM_RATE_LEN			8
#घोषणा IEEE80211_OFDM_RATE_6MB			0x0C
#घोषणा IEEE80211_OFDM_RATE_9MB			0x12
#घोषणा IEEE80211_OFDM_RATE_12MB		0x18
#घोषणा IEEE80211_OFDM_RATE_18MB		0x24
#घोषणा IEEE80211_OFDM_RATE_24MB		0x30
#घोषणा IEEE80211_OFDM_RATE_36MB		0x48
#घोषणा IEEE80211_OFDM_RATE_48MB		0x60
#घोषणा IEEE80211_OFDM_RATE_54MB		0x6C
#घोषणा IEEE80211_BASIC_RATE_MASK		0x80

#घोषणा IEEE80211_CCK_RATE_1MB_MASK		(1<<0)
#घोषणा IEEE80211_CCK_RATE_2MB_MASK		(1<<1)
#घोषणा IEEE80211_CCK_RATE_5MB_MASK		(1<<2)
#घोषणा IEEE80211_CCK_RATE_11MB_MASK		(1<<3)
#घोषणा IEEE80211_OFDM_RATE_6MB_MASK		(1<<4)
#घोषणा IEEE80211_OFDM_RATE_9MB_MASK		(1<<5)
#घोषणा IEEE80211_OFDM_RATE_12MB_MASK		(1<<6)
#घोषणा IEEE80211_OFDM_RATE_18MB_MASK		(1<<7)
#घोषणा IEEE80211_OFDM_RATE_24MB_MASK		(1<<8)
#घोषणा IEEE80211_OFDM_RATE_36MB_MASK		(1<<9)
#घोषणा IEEE80211_OFDM_RATE_48MB_MASK		(1<<10)
#घोषणा IEEE80211_OFDM_RATE_54MB_MASK		(1<<11)

#घोषणा IEEE80211_CCK_RATES_MASK		0x0000000F
#घोषणा IEEE80211_CCK_BASIC_RATES_MASK	(IEEE80211_CCK_RATE_1MB_MASK | \
	IEEE80211_CCK_RATE_2MB_MASK)
#घोषणा IEEE80211_CCK_DEFAULT_RATES_MASK	(IEEE80211_CCK_BASIC_RATES_MASK | \
	IEEE80211_CCK_RATE_5MB_MASK | \
	IEEE80211_CCK_RATE_11MB_MASK)

#घोषणा IEEE80211_OFDM_RATES_MASK		0x00000FF0
#घोषणा IEEE80211_OFDM_BASIC_RATES_MASK	(IEEE80211_OFDM_RATE_6MB_MASK | \
	IEEE80211_OFDM_RATE_12MB_MASK | \
	IEEE80211_OFDM_RATE_24MB_MASK)
#घोषणा IEEE80211_OFDM_DEFAULT_RATES_MASK	(IEEE80211_OFDM_BASIC_RATES_MASK | \
	IEEE80211_OFDM_RATE_9MB_MASK  | \
	IEEE80211_OFDM_RATE_18MB_MASK | \
	IEEE80211_OFDM_RATE_36MB_MASK | \
	IEEE80211_OFDM_RATE_48MB_MASK | \
	IEEE80211_OFDM_RATE_54MB_MASK)
#घोषणा IEEE80211_DEFAULT_RATES_MASK (IEEE80211_OFDM_DEFAULT_RATES_MASK | \
				IEEE80211_CCK_DEFAULT_RATES_MASK)

#घोषणा IEEE80211_NUM_OFDM_RATES	    8
#घोषणा IEEE80211_NUM_CCK_RATES		    4
#घोषणा IEEE80211_OFDM_SHIFT_MASK_A         4


/* this is stolen and modअगरied from the madwअगरi driver*/
#घोषणा IEEE80211_FC0_TYPE_MASK		0x0c
#घोषणा IEEE80211_FC0_TYPE_DATA		0x08
#घोषणा IEEE80211_FC0_SUBTYPE_MASK	0xB0
#घोषणा IEEE80211_FC0_SUBTYPE_QOS	0x80

#घोषणा IEEE80211_QOS_HAS_SEQ(fc) \
	(((fc) & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) == \
	 (IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_QOS))

/* this is stolen from ipw2200 driver */
#घोषणा IEEE_IBSS_MAC_HASH_SIZE 31
काष्ठा ieee_ibss_seq अणु
	u8 mac[ETH_ALEN];
	u16 seq_num[17];
	u16 frag_num[17];
	अचिन्हित दीर्घ packet_समय[17];
	काष्ठा list_head list;
पूर्ण;

/* NOTE: This data is क्रम statistical purposes; not all hardware provides this
 *       inक्रमmation क्रम frames received.  Not setting these will not cause
 *       any adverse affects.
 */
काष्ठा ieee80211_rx_stats अणु
	u32 mac_समय[2];
	s8 rssi;
	u8 संकेत;
	u8 noise;
	u16 rate; /* in 100 kbps */
	u8 received_channel;
	u8 control;
	u8 mask;
	u8 freq;
	u16 len;
	u64 tsf;
	u32 beacon_समय;
	u8 nic_type;
	u16       Length;
	//      u8        DataRate;      // In 0.5 Mbps
	u8        SignalQuality; // in 0-100 index.
	s32       RecvSignalPower; // Real घातer in dBm क्रम this packet, no beautअगरication and aggregation.
	s8        RxPower; // in dBm Translate from PWdB
	u8        SignalStrength; // in 0-100 index.
	u16       bHwError:1;
	u16       bCRC:1;
	u16       bICV:1;
	u16       bShortPreamble:1;
	u16       Antenna:1;      //क्रम rtl8185
	u16       Decrypted:1;    //क्रम rtl8185, rtl8187
	u16       Wakeup:1;       //क्रम rtl8185
	u16       Reserved0:1;    //क्रम rtl8185
	u8        AGC;
	u32       TimeStampLow;
	u32       TimeStampHigh;
	bool      bShअगरt;
	bool      bIsQosData;             // Added by Annie, 2005-12-22.
	u8        UserPriority;

	//1!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//1Attention Please!!!<11n or 8190 specअगरic code should be put below this line>
	//1!!!!!!!!!!!!!!!!!!!!!!!!!!!

	u8        RxDrvInfoSize;
	u8        RxBufShअगरt;
	bool      bIsAMPDU;
	bool      bFirstMPDU;
	bool      bContainHTC;
	bool      RxIs40MHzPacket;
	u32       RxPWDBAll;
	u8        RxMIMOSignalStrength[4];        // in 0~100 index
	s8        RxMIMOSignalQuality[2];
	bool      bPacketMatchBSSID;
	bool      bIsCCK;
	bool      bPacketToSelf;
	//added by amy
	u8        *भव_address;
	u16          packetlength;              // Total packet length: Must equal to sum of all FragLength
	u16          fraglength;                        // FragLength should equal to PacketLength in non-fragment हाल
	u16          fragoffset;                        // Data offset क्रम this fragment
	u16          ntotalfrag;
	bool		  bisrxaggrsubframe;
	bool		  bPacketBeacon;	//cosa add क्रम rssi
	bool		  bToSelfBA;		//cosa add क्रम rssi
	s8		  cck_adc_pwdb[4];	//cosa add क्रम rx path selection
	u16		  Seq_Num;

पूर्ण;

/* IEEE 802.11 requires that STA supports concurrent reception of at least
 * three fragmented frames. This define can be increased to support more
 * concurrent frames, but it should be noted that each entry can consume about
 * 2 kB of RAM and increasing cache size will slow करोwn frame reassembly.
 */
#घोषणा IEEE80211_FRAG_CACHE_LEN 4

काष्ठा ieee80211_frag_entry अणु
	अचिन्हित दीर्घ first_frag_समय;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक last_frag;
	काष्ठा sk_buff *skb;
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
पूर्ण;

काष्ठा ieee80211_stats अणु
	अचिन्हित पूर्णांक tx_unicast_frames;
	अचिन्हित पूर्णांक tx_multicast_frames;
	अचिन्हित पूर्णांक tx_fragments;
	अचिन्हित पूर्णांक tx_unicast_octets;
	अचिन्हित पूर्णांक tx_multicast_octets;
	अचिन्हित पूर्णांक tx_deferred_transmissions;
	अचिन्हित पूर्णांक tx_single_retry_frames;
	अचिन्हित पूर्णांक tx_multiple_retry_frames;
	अचिन्हित पूर्णांक tx_retry_limit_exceeded;
	अचिन्हित पूर्णांक tx_discards;
	अचिन्हित पूर्णांक rx_unicast_frames;
	अचिन्हित पूर्णांक rx_multicast_frames;
	अचिन्हित पूर्णांक rx_fragments;
	अचिन्हित पूर्णांक rx_unicast_octets;
	अचिन्हित पूर्णांक rx_multicast_octets;
	अचिन्हित पूर्णांक rx_fcs_errors;
	अचिन्हित पूर्णांक rx_discards_no_buffer;
	अचिन्हित पूर्णांक tx_discards_wrong_sa;
	अचिन्हित पूर्णांक rx_discards_undecryptable;
	अचिन्हित पूर्णांक rx_message_in_msg_fragments;
	अचिन्हित पूर्णांक rx_message_in_bad_msg_fragments;
पूर्ण;

काष्ठा ieee80211_device;

#समावेश "ieee80211_crypt.h"

#घोषणा SEC_KEY_1         (1<<0)
#घोषणा SEC_KEY_2         (1<<1)
#घोषणा SEC_KEY_3         (1<<2)
#घोषणा SEC_KEY_4         (1<<3)
#घोषणा SEC_ACTIVE_KEY    (1<<4)
#घोषणा SEC_AUTH_MODE     (1<<5)
#घोषणा SEC_UNICAST_GROUP (1<<6)
#घोषणा SEC_LEVEL         (1<<7)
#घोषणा SEC_ENABLED       (1<<8)
#घोषणा SEC_ENCRYPT       (1<<9)

#घोषणा SEC_LEVEL_0      0 /* None */
#घोषणा SEC_LEVEL_1      1 /* WEP 40 and 104 bit */
#घोषणा SEC_LEVEL_2      2 /* Level 1 + TKIP */
#घोषणा SEC_LEVEL_2_CKIP 3 /* Level 1 + CKIP */
#घोषणा SEC_LEVEL_3      4 /* Level 2 + CCMP */

#घोषणा SEC_ALG_NONE            0
#घोषणा SEC_ALG_WEP             1
#घोषणा SEC_ALG_TKIP            2
#घोषणा SEC_ALG_CCMP            3

#घोषणा WEP_KEYS		4
#घोषणा WEP_KEY_LEN		13
#घोषणा SCM_KEY_LEN             32
#घोषणा SCM_TEMPORAL_KEY_LENGTH 16

काष्ठा ieee80211_security अणु
	u16 active_key:2,
	    enabled:1,
	    auth_algo:4,
	    unicast_uses_group:1,
	    encrypt:1;
	u8 auth_mode;
	u8 key_sizes[WEP_KEYS];
	u8 keys[WEP_KEYS][SCM_KEY_LEN];
	u8 level;
	u16 flags;
पूर्ण __packed;


/*
 *  802.11 data frame from AP
 *       ,-------------------------------------------------------------------.
 * Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
 *       |------|------|---------|---------|---------|------|---------|------|
 * Desc. | ctrl | dura |  DA/RA  |   TA    |    SA   | Sequ |  frame  |  fcs |
 *       |      | tion | (BSSID) |         |         | ence |  data   |      |
 *       `-------------------------------------------------------------------'
 *  Total: 28-2340 bytes
 */

/* Management Frame Inक्रमmation Element Types */
क्रमागत ieee80211_mfie अणु
	MFIE_TYPE_SSID = 0,
	MFIE_TYPE_RATES = 1,
	MFIE_TYPE_FH_SET = 2,
	MFIE_TYPE_DS_SET = 3,
	MFIE_TYPE_CF_SET = 4,
	MFIE_TYPE_TIM = 5,
	MFIE_TYPE_IBSS_SET = 6,
	MFIE_TYPE_COUNTRY = 7,
	MFIE_TYPE_HOP_PARAMS = 8,
	MFIE_TYPE_HOP_TABLE = 9,
	MFIE_TYPE_REQUEST = 10,
	MFIE_TYPE_CHALLENGE = 16,
	MFIE_TYPE_POWER_CONSTRAINT = 32,
	MFIE_TYPE_POWER_CAPABILITY = 33,
	MFIE_TYPE_TPC_REQUEST = 34,
	MFIE_TYPE_TPC_REPORT = 35,
	MFIE_TYPE_SUPP_CHANNELS = 36,
	MFIE_TYPE_CSA = 37,
	MFIE_TYPE_MEASURE_REQUEST = 38,
	MFIE_TYPE_MEASURE_REPORT = 39,
	MFIE_TYPE_QUIET = 40,
	MFIE_TYPE_IBSS_DFS = 41,
	MFIE_TYPE_ERP = 42,
	MFIE_TYPE_RSN = 48,
	MFIE_TYPE_RATES_EX = 50,
	MFIE_TYPE_HT_CAP = 45,
	 MFIE_TYPE_HT_INFO = 61,
	 MFIE_TYPE_AIRONET = 133,
	MFIE_TYPE_GENERIC = 221,
	MFIE_TYPE_QOS_PARAMETER = 222,
पूर्ण;

/* Minimal header; can be used क्रम passing 802.11 frames with sufficient
 * inक्रमmation to determine what type of underlying data type is actually
 * stored in the data.
 */
काष्ठा rtl_80211_hdr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtl_80211_hdr_1addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा rtl_80211_hdr_2addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा rtl_80211_hdr_3addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtl_80211_hdr_4addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 addr4[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा rtl_80211_hdr_3addrqos अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[0];
	__le16 qos_ctl;
पूर्ण __packed;

काष्ठा rtl_80211_hdr_4addrqos अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 addr4[ETH_ALEN];
	u8 payload[0];
	__le16 qos_ctl;
पूर्ण __packed;

काष्ठा ieee80211_info_element अणु
	u8 id;
	u8 len;
	u8 data[];
पूर्ण __packed;

काष्ठा ieee80211_authentication अणु
	काष्ठा rtl_80211_hdr_3addr header;
	__le16 algorithm;
	__le16 transaction;
	__le16 status;
	/*challenge*/
	काष्ठा ieee80211_info_element info_element[];
पूर्ण __packed;

काष्ठा ieee80211_disassoc अणु
	काष्ठा rtl_80211_hdr_3addr header;
	__le16 reason;
पूर्ण __packed;

काष्ठा ieee80211_probe_request अणु
	काष्ठा rtl_80211_hdr_3addr header;
	/* SSID, supported rates */
	काष्ठा ieee80211_info_element info_element[];
पूर्ण __packed;

काष्ठा ieee80211_probe_response अणु
	काष्ठा rtl_80211_hdr_3addr header;
	__le32 समय_stamp[2];
	__le16 beacon_पूर्णांकerval;
	__le16 capability;
	/* SSID, supported rates, FH params, DS params,
	 * CF params, IBSS params, TIM (अगर beacon), RSN
	 */
	काष्ठा ieee80211_info_element info_element[];
पूर्ण __packed;

/* Alias beacon क्रम probe_response */
#घोषणा ieee80211_beacon ieee80211_probe_response

काष्ठा ieee80211_assoc_request_frame अणु
	काष्ठा rtl_80211_hdr_3addr header;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	/* SSID, supported rates, RSN */
	काष्ठा ieee80211_info_element info_element[];
पूर्ण __packed;

काष्ठा ieee80211_reassoc_request_frame अणु
	काष्ठा rtl_80211_hdr_3addr header;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	u8 current_ap[ETH_ALEN];
	/* SSID, supported rates, RSN */
	काष्ठा ieee80211_info_element info_element[];
पूर्ण __packed;

काष्ठा ieee80211_assoc_response_frame अणु
	काष्ठा rtl_80211_hdr_3addr header;
	__le16 capability;
	__le16 status;
	__le16 aid;
	काष्ठा ieee80211_info_element info_element[]; /* supported rates */
पूर्ण __packed;

काष्ठा ieee80211_txb अणु
	u8 nr_frags;
	u8 encrypted;
	u8 queue_index;
	u8 rts_included;
	u16 reserved;
	__le16 frag_size;
	__le16 payload_size;
	काष्ठा sk_buff *fragments[];
पूर्ण;

#घोषणा MAX_TX_AGG_COUNT		  16
काष्ठा ieee80211_drv_agg_txb अणु
	u8 nr_drv_agg_frames;
	काष्ठा sk_buff *tx_agg_frames[MAX_TX_AGG_COUNT];
पूर्ण __packed;

#घोषणा MAX_SUBFRAME_COUNT		  64
काष्ठा ieee80211_rxb अणु
	u8 nr_subframes;
	काष्ठा sk_buff *subframes[MAX_SUBFRAME_COUNT];
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
पूर्ण __packed;

प्रकार जोड़ _frameqos अणु
	u16 लघुdata;
	u8  अक्षरdata[2];
	काष्ठा अणु
		u16 tid:4;
		u16 eosp:1;
		u16 ack_policy:2;
		u16 reserved:1;
		u16 txop:8;
	पूर्ण field;
पूर्ण frameqos, *pframeqos;

/* SWEEP TABLE ENTRIES NUMBER*/
#घोषणा MAX_SWEEP_TAB_ENTRIES		  42
#घोषणा MAX_SWEEP_TAB_ENTRIES_PER_PACKET  7
/* MAX_RATES_LENGTH needs to be 12.  The spec says 8, and many APs
 * only use 8, and then use extended rates क्रम the reमुख्यing supported
 * rates.  Other APs, however, stick all of their supported rates on the
 * मुख्य rates inक्रमmation element...
 */
#घोषणा MAX_RATES_LENGTH                  ((u8)12)
#घोषणा MAX_RATES_EX_LENGTH               ((u8)16)
#घोषणा MAX_NETWORK_COUNT                  128

#घोषणा MAX_CHANNEL_NUMBER                 161
#घोषणा IEEE80211_SOFTMAC_SCAN_TIME	   100
//(HZ / 2)
#घोषणा IEEE80211_SOFTMAC_ASSOC_RETRY_TIME (HZ * 2)

#घोषणा CRC_LENGTH                 4U

#घोषणा MAX_WPA_IE_LEN 64

#घोषणा NETWORK_EMPTY_ESSID (1<<0)
#घोषणा NETWORK_HAS_OFDM    (1<<1)
#घोषणा NETWORK_HAS_CCK     (1<<2)

/* QoS काष्ठाure */
#घोषणा NETWORK_HAS_QOS_PARAMETERS      (1<<3)
#घोषणा NETWORK_HAS_QOS_INFORMATION     (1<<4)
#घोषणा NETWORK_HAS_QOS_MASK            (NETWORK_HAS_QOS_PARAMETERS | \
					 NETWORK_HAS_QOS_INFORMATION)
/* 802.11h */
#घोषणा NETWORK_HAS_POWER_CONSTRAINT    (1<<5)
#घोषणा NETWORK_HAS_CSA                 (1<<6)
#घोषणा NETWORK_HAS_QUIET               (1<<7)
#घोषणा NETWORK_HAS_IBSS_DFS            (1<<8)
#घोषणा NETWORK_HAS_TPC_REPORT          (1<<9)

#घोषणा NETWORK_HAS_ERP_VALUE           (1<<10)

#घोषणा QOS_QUEUE_NUM                   4
#घोषणा QOS_OUI_LEN                     3
#घोषणा QOS_OUI_TYPE                    2
#घोषणा QOS_ELEMENT_ID                  221
#घोषणा QOS_OUI_INFO_SUB_TYPE           0
#घोषणा QOS_OUI_PARAM_SUB_TYPE          1
#घोषणा QOS_VERSION_1                   1
#घोषणा QOS_AIFSN_MIN_VALUE             2
काष्ठा ieee80211_qos_inक्रमmation_element अणु
	u8 elementID;
	u8 length;
	u8 qui[QOS_OUI_LEN];
	u8 qui_type;
	u8 qui_subtype;
	u8 version;
	u8 ac_info;
पूर्ण __packed;

काष्ठा ieee80211_qos_ac_parameter अणु
	u8 aci_aअगरsn;
	u8 ecw_min_max;
	__le16 tx_op_limit;
पूर्ण __packed;

काष्ठा ieee80211_qos_parameter_info अणु
	काष्ठा ieee80211_qos_inक्रमmation_element info_element;
	u8 reserved;
	काष्ठा ieee80211_qos_ac_parameter ac_params_record[QOS_QUEUE_NUM];
पूर्ण __packed;

काष्ठा ieee80211_qos_parameters अणु
	__le16 cw_min[QOS_QUEUE_NUM];
	__le16 cw_max[QOS_QUEUE_NUM];
	u8 aअगरs[QOS_QUEUE_NUM];
	u8 flag[QOS_QUEUE_NUM];
	__le16 tx_op_limit[QOS_QUEUE_NUM];
पूर्ण __packed;

काष्ठा ieee80211_qos_data अणु
	काष्ठा ieee80211_qos_parameters parameters;
	पूर्णांक active;
	पूर्णांक supported;
	u8 param_count;
	u8 old_param_count;
पूर्ण;

काष्ठा ieee80211_tim_parameters अणु
	u8 tim_count;
	u8 tim_period;
पूर्ण __packed;

//#अन्यथा
काष्ठा ieee80211_wmm_ts_info अणु
	u8 ac_dir_tid;
	u8 ac_up_psb;
	u8 reserved;
पूर्ण __packed;

काष्ठा ieee80211_wmm_tspec_elem अणु
	काष्ठा ieee80211_wmm_ts_info ts_info;
	u16 norm_msdu_size;
	u16 max_msdu_size;
	u32 min_serv_पूर्णांकer;
	u32 max_serv_पूर्णांकer;
	u32 inact_पूर्णांकer;
	u32 suspen_पूर्णांकer;
	u32 serv_start_समय;
	u32 min_data_rate;
	u32 mean_data_rate;
	u32 peak_data_rate;
	u32 max_burst_size;
	u32 delay_bound;
	u32 min_phy_rate;
	u16 surp_band_allow;
	u16 medium_समय;
पूर्ण __packed;
क्रमागत eap_type अणु
	EAP_PACKET = 0,
	EAPOL_START,
	EAPOL_LOGOFF,
	EAPOL_KEY,
	EAPOL_ENCAP_ASF_ALERT
पूर्ण;

अटल स्थिर अक्षर *eap_types[] = अणु
	[EAP_PACKET]		= "EAP-Packet",
	[EAPOL_START]		= "EAPOL-Start",
	[EAPOL_LOGOFF]		= "EAPOL-Logoff",
	[EAPOL_KEY]		= "EAPOL-Key",
	[EAPOL_ENCAP_ASF_ALERT]	= "EAPOL-Encap-ASF-Alert"
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *eap_get_type(पूर्णांक type)
अणु
	वापस ((u32)type >= ARRAY_SIZE(eap_types)) ? "Unknown" : eap_types[type];
पूर्ण
//added by amy क्रम reorder
अटल अंतरभूत u8 Frame_QoSTID(u8 *buf)
अणु
	काष्ठा rtl_80211_hdr_3addr *hdr;
	u16 fc;
	hdr = (काष्ठा rtl_80211_hdr_3addr *)buf;
	fc = le16_to_cpu(hdr->frame_ctl);
	वापस (u8)((frameqos *)(buf + (((fc & IEEE80211_FCTL_TODS) && (fc & IEEE80211_FCTL_FROMDS)) ? 30 : 24)))->field.tid;
पूर्ण

//added by amy क्रम reorder

काष्ठा eapol अणु
	u8 snap[6];
	u16 ethertype;
	u8 version;
	u8 type;
	u16 length;
पूर्ण __packed;

काष्ठा ieee80211_sofपंचांगac_stats अणु
	अचिन्हित पूर्णांक rx_ass_ok;
	अचिन्हित पूर्णांक rx_ass_err;
	अचिन्हित पूर्णांक rx_probe_rq;
	अचिन्हित पूर्णांक tx_probe_rs;
	अचिन्हित पूर्णांक tx_beacons;
	अचिन्हित पूर्णांक rx_auth_rq;
	अचिन्हित पूर्णांक rx_auth_rs_ok;
	अचिन्हित पूर्णांक rx_auth_rs_err;
	अचिन्हित पूर्णांक tx_auth_rq;
	अचिन्हित पूर्णांक no_auth_rs;
	अचिन्हित पूर्णांक no_ass_rs;
	अचिन्हित पूर्णांक tx_ass_rq;
	अचिन्हित पूर्णांक rx_ass_rq;
	अचिन्हित पूर्णांक tx_probe_rq;
	अचिन्हित पूर्णांक reassoc;
	अचिन्हित पूर्णांक swtxstop;
	अचिन्हित पूर्णांक swtxawake;
	अचिन्हित अक्षर CurrentShowTxate;
	अचिन्हित अक्षर last_packet_rate;
	अचिन्हित पूर्णांक txretrycount;
पूर्ण;

#घोषणा BEACON_PROBE_SSID_ID_POSITION 12

काष्ठा ieee80211_info_element_hdr अणु
	u8 id;
	u8 len;
पूर्ण __packed;

/*
 * These are the data types that can make up management packets
 *
	u16 auth_algorithm;
	u16 auth_sequence;
	u16 beacon_पूर्णांकerval;
	u16 capability;
	u8 current_ap[ETH_ALEN];
	u16 listen_पूर्णांकerval;
	काष्ठा अणु
		u16 association_id:14, reserved:2;
	पूर्ण __packed;
	u32 समय_stamp[2];
	u16 reason;
	u16 status;
*/

#घोषणा IEEE80211_DEFAULT_TX_ESSID "Penguin"
#घोषणा IEEE80211_DEFAULT_BASIC_RATE 2 //1Mbps

क्रमागत अणुWMM_all_frame, WMM_two_frame, WMM_four_frame, WMM_six_frameपूर्ण;
#घोषणा MAX_SP_Len  (WMM_all_frame << 4)
#घोषणा IEEE80211_QOS_TID 0x0f
#घोषणा QOS_CTL_NOTCONTAIN_ACK (0x01 << 5)

#घोषणा IEEE80211_DTIM_MBCAST 4
#घोषणा IEEE80211_DTIM_UCAST 2
#घोषणा IEEE80211_DTIM_VALID 1
#घोषणा IEEE80211_DTIM_INVALID 0

#घोषणा IEEE80211_PS_DISABLED 0
#घोषणा IEEE80211_PS_UNICAST IEEE80211_DTIM_UCAST
#घोषणा IEEE80211_PS_MBCAST IEEE80211_DTIM_MBCAST

//added by David क्रम QoS 2006/6/30
//#घोषणा WMM_Hang_8187
#अगर_घोषित WMM_Hang_8187
#अघोषित WMM_Hang_8187
#पूर्ण_अगर

#घोषणा WME_AC_BK   0x00
#घोषणा WME_AC_BE   0x01
#घोषणा WME_AC_VI   0x02
#घोषणा WME_AC_VO   0x03
#घोषणा WME_ACI_MASK 0x03
#घोषणा WME_AIFSN_MASK 0x03
#घोषणा WME_AC_PRAM_LEN 16

#घोषणा MAX_RECEIVE_BUFFER_SIZE 9100

//UP Mapping to AC, using in MgntQuery_SequenceNumber() and maybe क्रम DSCP
//#घोषणा UP2AC(up)	((up<3) ? ((up==0)?1:0) : (up>>1))
#घोषणा UP2AC(up) (		   \
	((up) < 1) ? WME_AC_BE : \
	((up) < 3) ? WME_AC_BK : \
	((up) < 4) ? WME_AC_BE : \
	((up) < 6) ? WME_AC_VI : \
	WME_AC_VO)
//AC Mapping to UP, using in Tx part क्रम selecting the corresponding TX queue
#घोषणा AC2UP(_ac)	(       \
	((_ac) == WME_AC_VO) ? 6 : \
	((_ac) == WME_AC_VI) ? 5 : \
	((_ac) == WME_AC_BK) ? 1 : \
	0)

#घोषणा	ETHER_ADDR_LEN		6	/* length of an Ethernet address */
#घोषणा ETHERNET_HEADER_SIZE    14      /* length of two Ethernet address plus ether type*/

काष्ठा	ether_header अणु
	u8 ether_dhost[ETHER_ADDR_LEN];
	u8 ether_shost[ETHER_ADDR_LEN];
	u16 ether_type;
पूर्ण __packed;

#अगर_अघोषित ETHERTYPE_PAE
#घोषणा	ETHERTYPE_PAE	0x888e		/* EAPOL PAE/802.1x */
#पूर्ण_अगर
#अगर_अघोषित ETHERTYPE_IP
#घोषणा	ETHERTYPE_IP	0x0800		/* IP protocol */
#पूर्ण_अगर

प्रकार क्रमागत _erp_t अणु
	ERP_NonERPpresent	= 0x01,
	ERP_UseProtection	= 0x02,
	ERP_BarkerPreambleMode = 0x04,
पूर्ण erp_t;


काष्ठा ieee80211_network अणु
	/* These entries are used to identअगरy a unique network */
	u8 bssid[ETH_ALEN];   /* u16 aligned! */
	u8 channel;

	// CCXv4 S59, MBSSID.
	bool	bMBssidValid;
	u8	MBssid[ETH_ALEN];    /* u16 aligned! */
	u8	MBssidMask;
	/* Ensure null-terminated क्रम any debug msgs */
	u8 ssid[IW_ESSID_MAX_SIZE + 1];
	u8 ssid_len;
	काष्ठा ieee80211_qos_data qos_data;

	//added by amy क्रम LEAP
	bool	bWithAironetIE;
	bool	bCkipSupported;
	bool	bCcxRmEnable;
	u16	CcxRmState[2];
	// CCX 2 S38, WLAN Device Version Number element. Annie, 2006-08-20.
	bool	bWithCcxVerNum;
	u8	BssCcxVerNumber;
	/* These are network statistics */
	काष्ठा ieee80211_rx_stats stats;
	u16 capability;
	u8  rates[MAX_RATES_LENGTH];
	u8  rates_len;
	u8  rates_ex[MAX_RATES_EX_LENGTH];
	u8  rates_ex_len;
	अचिन्हित दीर्घ last_scanned;
	u8  mode;
	u32 flags;
	u32 last_associate;
	u32 समय_stamp[2];
	u16 beacon_पूर्णांकerval;
	u16 listen_पूर्णांकerval;
	u16 atim_winकरोw;
	u8  erp_value;
	u8  wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;
	u8  rsn_ie[MAX_WPA_IE_LEN];
	माप_प्रकार rsn_ie_len;

	काष्ठा ieee80211_tim_parameters tim;
	u8  dtim_period;
	u8  dtim_data;
	u32 last_dtim_sta_समय[2];

	//appeded क्रम QoS
	u8 wmm_info;
	काष्ठा ieee80211_wmm_ac_param wmm_param[4];
	u8 QoS_Enable;
#अगर_घोषित THOMAS_TURBO
	u8 Turbo_Enable;//enable turbo mode, added by thomas
#पूर्ण_अगर
	u16 CountryIeLen;
	u8 CountryIeBuf[MAX_IE_LEN];
	// HT Related, by amy, 2008.04.29
	BSS_HT	bssht;
	// Add to handle broadcom AP management frame CCK rate.
	bool broadcom_cap_exist;
	bool ralink_cap_exist;
	bool atheros_cap_exist;
	bool cisco_cap_exist;
	bool unknown_cap_exist;
//	u8	berp_info;
	bool	berp_info_valid;
	bool buseprotection;
	//put at the end of the काष्ठाure.
	काष्ठा list_head list;
पूर्ण;

क्रमागत ieee80211_state अणु

	/* the card is not linked at all */
	IEEE80211_NOLINK = 0,

	/* IEEE80211_ASSOCIATING* are क्रम BSS client mode
	 * the driver shall not perक्रमm RX filtering unless
	 * the state is LINKED.
	 * The driver shall just check क्रम the state LINKED and
	 * शेषs to NOLINK क्रम ALL the other states (including
	 * LINKED_SCANNING)
	 */

	/* the association procedure will start (wq scheduling)*/
	IEEE80211_ASSOCIATING,
	IEEE80211_ASSOCIATING_RETRY,

	/* the association procedure is sending AUTH request*/
	IEEE80211_ASSOCIATING_AUTHENTICATING,

	/* the association procedure has successfully authentcated
	 * and is sending association request
	 */
	IEEE80211_ASSOCIATING_AUTHENTICATED,

	/* the link is ok. the card associated to a BSS or linked
	 * to a ibss cell or acting as an AP and creating the bss
	 */
	IEEE80211_LINKED,

	/* same as LINKED, but the driver shall apply RX filter
	 * rules as we are in NO_LINK mode. As the card is still
	 * logically linked, but it is करोing a syncro site survey
	 * then it will be back to LINKED state.
	 */
	IEEE80211_LINKED_SCANNING,

पूर्ण;

#घोषणा DEFAULT_MAX_SCAN_AGE (15 * HZ)
#घोषणा DEFAULT_FTS 2346

#घोषणा CFG_IEEE80211_RESERVE_FCS (1<<0)
#घोषणा CFG_IEEE80211_COMPUTE_FCS (1<<1)
#घोषणा CFG_IEEE80211_RTS (1<<2)

#घोषणा IEEE80211_24GHZ_MIN_CHANNEL 1
#घोषणा IEEE80211_24GHZ_MAX_CHANNEL 14
#घोषणा IEEE80211_24GHZ_CHANNELS (IEEE80211_24GHZ_MAX_CHANNEL - \
				  IEEE80211_24GHZ_MIN_CHANNEL + 1)

#घोषणा IEEE80211_52GHZ_MIN_CHANNEL 34
#घोषणा IEEE80211_52GHZ_MAX_CHANNEL 165
#घोषणा IEEE80211_52GHZ_CHANNELS (IEEE80211_52GHZ_MAX_CHANNEL - \
				  IEEE80211_52GHZ_MIN_CHANNEL + 1)



काष्ठा tx_pending अणु
	पूर्णांक frag;
	काष्ठा ieee80211_txb *txb;
पूर्ण;

काष्ठा bandwidth_स्वतःचयन अणु
	दीर्घ threshold_20Mhzto40Mhz;
	दीर्घ	threshold_40Mhzto20Mhz;
	bool bक्रमced_tx20Mhz;
	bool bस्वतःचयन_enable;
पूर्ण;


//added by amy क्रम order

#घोषणा REORDER_WIN_SIZE	128
#घोषणा REORDER_ENTRY_NUM	128
काष्ठा rx_reorder_entry अणु
	काष्ठा list_head	List;
	u16			SeqNum;
	काष्ठा ieee80211_rxb *prxb;
पूर्ण;
//added by amy क्रम order
प्रकार क्रमागत _Fsync_State अणु
	Default_Fsync,
	HW_Fsync,
	SW_Fsync
पूर्ण Fsync_State;

// Power save mode configured.
प्रकार	क्रमागत _RT_PS_MODE अणु
	eActive,	// Active/Continuous access.
	eMaxPs,		// Max घातer save mode.
	eFastPs		// Fast घातer save mode.
पूर्ण RT_PS_MODE;

प्रकार क्रमागत _IPS_CALLBACK_FUNCION अणु
	IPS_CALLBACK_NONE = 0,
	IPS_CALLBACK_MGNT_LINK_REQUEST = 1,
	IPS_CALLBACK_JOIN_REQUEST = 2,
पूर्ण IPS_CALLBACK_FUNCION;

प्रकार क्रमागत _RT_JOIN_ACTION अणु
	RT_JOIN_INFRA   = 1,
	RT_JOIN_IBSS  = 2,
	RT_START_IBSS = 3,
	RT_NO_ACTION  = 4,
पूर्ण RT_JOIN_ACTION;

काष्ठा ibss_parms अणु
	u16   atimWin;
पूर्ण;
#घोषणा MAX_NUM_RATES	264 // Max num of support rates element: 8,  Max num of ext. support rate: 255. 061122, by rcnjko.

// RF state.
प्रकार	क्रमागत _RT_RF_POWER_STATE अणु
	eRfOn,
	eRfSleep,
	eRfOff
पूर्ण RT_RF_POWER_STATE;

काष्ठा rt_घातer_save_control अणु

	//
	// Inactive Power Save(IPS) : Disable RF when disconnected
	//
	bool				bInactivePs;
	bool				bIPSModeBackup;
	bool				bSwRfProcessing;
	RT_RF_POWER_STATE	eInactivePowerState;
	काष्ठा work_काष्ठा	InactivePsWorkItem;
	काष्ठा समयr_list	InactivePsTimer;

	// Return poपूर्णांक क्रम join action
	IPS_CALLBACK_FUNCION	ReturnPoपूर्णांक;

	// Recored Parameters क्रम rescheduled JoinRequest
	bool				bTmpBssDesc;
	RT_JOIN_ACTION		पंचांगpJoinAction;
	काष्ठा ieee80211_network पंचांगpBssDesc;

	// Recored Parameters क्रम rescheduled MgntLinkRequest
	bool				bTmpScanOnly;
	bool				bTmpActiveScan;
	bool				bTmpFilterHiddenAP;
	bool				bTmpUpdateParms;
	u8					पंचांगpSsidBuf[33];
	काष्ठा octet_string			पंचांगpSsid2Scan;
	bool				bTmpSsid2Scan;
	u8					पंचांगpNetworkType;
	u8					पंचांगpChannelNumber;
	u16					पंचांगpBcnPeriod;
	u8					पंचांगpDtimPeriod;
	u16					पंचांगpmCap;
	काष्ठा octet_string			पंचांगpSuppRateSet;
	u8					पंचांगpSuppRateBuf[MAX_NUM_RATES];
	bool				bTmpSuppRate;
	काष्ठा ibss_parms			पंचांगpIbpm;
	bool				bTmpIbpm;

	//
	// Leisre Poswer Save : Disable RF अगर connected but traffic is not busy
	//
	bool				bLeisurePs;

पूर्ण;

प्रकार u32 RT_RF_CHANGE_SOURCE;
#घोषणा RF_CHANGE_BY_SW		BIT(31)
#घोषणा RF_CHANGE_BY_HW		BIT(30)
#घोषणा RF_CHANGE_BY_PS		BIT(29)
#घोषणा RF_CHANGE_BY_IPS	BIT(28)
#घोषणा RF_CHANGE_BY_INIT	0	// Do not change the RFOff reason. Defined by Bruce, 2008-01-17.

प्रकार क्रमागत अणु
	COUNTRY_CODE_FCC = 0,
	COUNTRY_CODE_IC = 1,
	COUNTRY_CODE_ETSI = 2,
	COUNTRY_CODE_SPAIN = 3,
	COUNTRY_CODE_FRANCE = 4,
	COUNTRY_CODE_MKK = 5,
	COUNTRY_CODE_MKK1 = 6,
	COUNTRY_CODE_ISRAEL = 7,
	COUNTRY_CODE_TELEC,
	COUNTRY_CODE_MIC,
	COUNTRY_CODE_GLOBAL_DOMAIN
पूर्ण country_code_type_t;

#घोषणा RT_MAX_LD_SLOT_NUM	10
काष्ठा rt_link_detect अणु

	u32				NumRecvBcnInPeriod;
	u32				NumRecvDataInPeriod;

	u32				RxBcnNum[RT_MAX_LD_SLOT_NUM];	// number of Rx beacon / CheckForHang_period  to determine link status
	u32				RxDataNum[RT_MAX_LD_SLOT_NUM];	// number of Rx data / CheckForHang_period  to determine link status
	u16				SlotNum;	// number of CheckForHang period to determine link status
	u16				SlotIndex;

	u32				NumTxOkInPeriod;
	u32				NumRxOkInPeriod;
	bool				bBusyTraffic;
पूर्ण;


काष्ठा ieee80211_device अणु
	काष्ठा net_device *dev;
	काष्ठा ieee80211_security sec;

	//hw security related
//	u8 hwsec_support; //support?
	u8 hwsec_active;  //hw security active.
	bool is_silent_reset;
	bool ieee_up;
	//added by amy
	bool bSupportRemoteWakeUp;
	RT_PS_MODE	करोt11PowerSaveMode; // Power save mode configured.
	bool actscanning;
	bool beinretry;
	RT_RF_POWER_STATE		eRFPowerState;
	RT_RF_CHANGE_SOURCE	RfOffReason;
	bool is_set_key;
	//11n spec related I wonder अगर These info काष्ठाure need to be moved out of ieee80211_device

	//11n HT below
	PRT_HIGH_THROUGHPUT	pHTInfo;
	//काष्ठा समयr_list		SwBwTimer;
//	spinlock_t chnlop_spinlock;
	spinlock_t bw_spinlock;

	spinlock_t reorder_spinlock;
	// क्रम HT operation rate set.  we use this one क्रम HT data rate to separate dअगरferent descriptors
	//the way fill this is the same as in the IE
	u8	Regकरोt11HTOperationalRateSet[16];		//use RATR क्रमmat
	u8	करोt11HTOperationalRateSet[16];		//use RATR क्रमmat
	u8	RegHTSuppRateSet[16];
	u8				HTCurrentOperaRate;
	u8				HTHighestOperaRate;
	//wb added क्रम rate operation mode to firmware
	u8	bTxDisableRateFallBack;
	u8	bTxUseDriverAssingedRate;
	atomic_t	aपंचांग_chnlop;
	atomic_t	aपंचांग_swbw;
//	u8	HTHighestOperaRate;
//	u8	HTCurrentOperaRate;

	// 802.11e and WMM Traffic Stream Info (TX)
	काष्ठा list_head		Tx_TS_Admit_List;
	काष्ठा list_head		Tx_TS_Pending_List;
	काष्ठा list_head		Tx_TS_Unused_List;
	काष्ठा tx_ts_record		TxTsRecord[TOTAL_TS_NUM];
	// 802.11e and WMM Traffic Stream Info (RX)
	काष्ठा list_head		Rx_TS_Admit_List;
	काष्ठा list_head		Rx_TS_Pending_List;
	काष्ठा list_head		Rx_TS_Unused_List;
	काष्ठा rx_ts_record		RxTsRecord[TOTAL_TS_NUM];
	काष्ठा rx_reorder_entry	RxReorderEntry[128];
	काष्ठा list_head		RxReorder_Unused_List;
	// Qos related. Added by Annie, 2005-11-01.
//	PSTA_QOS			pStaQos;
	u8				ForcedPriority;		// Force per-packet priority 1~7. (शेष: 0, not to क्रमce it.)


	/* Bookkeeping काष्ठाures */
	काष्ठा net_device_stats stats;
	काष्ठा ieee80211_stats ieee_stats;
	काष्ठा ieee80211_sofपंचांगac_stats sofपंचांगac_stats;

	/* Probe / Beacon management */
	काष्ठा list_head network_मुक्त_list;
	काष्ठा list_head network_list;
	काष्ठा ieee80211_network *networks;
	पूर्णांक scans;
	पूर्णांक scan_age;

	पूर्णांक iw_mode; /* operating mode (IW_MODE_*) */
	काष्ठा iw_spy_data spy_data;

	spinlock_t lock;
	spinlock_t wpax_suitlist_lock;

	पूर्णांक tx_headroom; /* Set to size of any additional room needed at front
			  * of allocated Tx SKBs
			  */
	u32 config;

	/* WEP and other encryption related settings at the device level */
	पूर्णांक खोलो_wep; /* Set to 1 to allow unencrypted frames */
	पूर्णांक auth_mode;
	पूर्णांक reset_on_keychange; /* Set to 1 अगर the HW needs to be reset on
				 * WEP key changes
				 */

	/* If the host perक्रमms अणुen,deपूर्णcryption, then set to 1 */
	पूर्णांक host_encrypt;
	पूर्णांक host_encrypt_msdu;
	पूर्णांक host_decrypt;
	/* host perक्रमms multicast decryption */
	पूर्णांक host_mc_decrypt;

	/* host should strip IV and ICV from रक्षित frames */
	/* meaningful only when hardware decryption is being used */
	पूर्णांक host_strip_iv_icv;

	पूर्णांक host_खोलो_frag;
	पूर्णांक host_build_iv;
	पूर्णांक ieee802_1x; /* is IEEE 802.1X used */

	/* WPA data */
	bool bHalfWirelessN24GMode;
	पूर्णांक wpa_enabled;
	पूर्णांक drop_unencrypted;
	पूर्णांक tkip_countermeasures;
	पूर्णांक privacy_invoked;
	माप_प्रकार wpa_ie_len;
	u8 *wpa_ie;
	u8 ap_mac_addr[6];
	u16 pairwise_key_type;
	u16 group_key_type;
	काष्ठा list_head crypt_deinit_list;
	काष्ठा ieee80211_crypt_data *crypt[WEP_KEYS];
	पूर्णांक tx_keyidx; /* शेष TX key index (crypt[tx_keyidx]) */
	काष्ठा समयr_list crypt_deinit_समयr;
	पूर्णांक crypt_quiesced;

	पूर्णांक bcrx_sta_key; /* use inभागidual keys to override शेष keys even
			   * with RX of broad/multicast frames
			   */

	/* Fragmentation काष्ठाures */
	// each streaming contain a entry
	काष्ठा ieee80211_frag_entry frag_cache[17][IEEE80211_FRAG_CACHE_LEN];
	अचिन्हित पूर्णांक frag_next_idx[17];
	u16 fts; /* Fragmentation Threshold */
#घोषणा DEFAULT_RTS_THRESHOLD 2346U
#घोषणा MIN_RTS_THRESHOLD 1
#घोषणा MAX_RTS_THRESHOLD 2346U
	u16 rts; /* RTS threshold */

	/* Association info */
	u8 bssid[ETH_ALEN];

	/* This stores infos क्रम the current network.
	 * Either the network we are associated in INFRASTRUCTURE
	 * or the network that we are creating in MASTER mode.
	 * ad-hoc is a mixture ;-).
	 * Note that in infraकाष्ठाure mode, even when not associated,
	 * fields bssid and essid may be valid (अगर wpa_set and essid_set
	 * are true) as thy carry the value set by the user via iwconfig
	 */
	काष्ठा ieee80211_network current_network;

	क्रमागत ieee80211_state state;

	पूर्णांक लघु_slot;
	पूर्णांक reg_mode;
	पूर्णांक mode;       /* A, B, G */
	पूर्णांक modulation; /* CCK, OFDM */
	पूर्णांक freq_band;  /* 2.4Ghz, 5.2Ghz, Mixed */
	पूर्णांक abg_true;   /* ABG flag              */

	/* used क्रम क्रमcing the ibss workqueue to terminate
	 * without रुको क्रम the syncro scan to terminate
	 */
	लघु sync_scan_hurryup;

	पूर्णांक perfect_rssi;
	पूर्णांक worst_rssi;

	u16 prev_seq_ctl;       /* used to drop duplicate frames */

	/* map of allowed channels. 0 is dummy */
	// FIXME: remember to शेष to a basic channel plan depending of the PHY type
	व्योम *करोt11d_info;
	bool bGlobalDoमुख्य;
	पूर्णांक rate;       /* current rate */
	पूर्णांक basic_rate;
	//FIXME: pleace callback, see अगर redundant with sofपंचांगac_features
	लघु active_scan;

	/* this contains flags क्रम selectively enable sofपंचांगac support */
	u16 sofपंचांगac_features;

	/* अगर the sequence control field is not filled by HW */
	u16 seq_ctrl[5];

	/* association procedure transaction sequence number */
	u16 associate_seq;

	/* AID क्रम RTXed association responses */
	u16 assoc_id;

	/* घातer save mode related*/
	लघु ps;
	लघु sta_sleep;
	पूर्णांक ps_समयout;
	पूर्णांक ps_period;
	काष्ठा tasklet_काष्ठा ps_task;
	u32 ps_th;
	u32 ps_tl;

	लघु raw_tx;
	/* used अगर IEEE_SOFTMAC_TX_QUEUE is set */
	लघु queue_stop;
	लघु scanning;
	लघु proto_started;

	काष्ठा mutex wx_mutex;
	काष्ठा mutex scan_mutex;

	spinlock_t mgmt_tx_lock;
	spinlock_t beacon_lock;

	लघु beacon_txing;

	लघु wap_set;
	लघु ssid_set;

	u8  wpax_type_set;    //अणुadded by David, 2006.9.28पूर्ण
	u32 wpax_type_notअगरy; //अणुadded by David, 2006.9.26पूर्ण

	/* QoS related flag */
	s8  init_wmmparam_flag;
	/* set on initialization */
	u8  qos_support;

	/* क्रम discarding duplicated packets in IBSS */
	काष्ठा list_head ibss_mac_hash[IEEE_IBSS_MAC_HASH_SIZE];

	/* क्रम discarding duplicated packets in BSS */
	u16 last_rxseq_num[17]; /* rx seq previous per-tid */
	u16 last_rxfrag_num[17];/* tx frag previous per-tid */
	अचिन्हित दीर्घ last_packet_समय[17];

	/* क्रम PS mode */
	अचिन्हित दीर्घ last_rx_ps_समय;

	/* used अगर IEEE_SOFTMAC_SINGLE_QUEUE is set */
	काष्ठा sk_buff *mgmt_queue_ring[MGMT_QUEUE_NUM];
	पूर्णांक mgmt_queue_head;
	पूर्णांक mgmt_queue_tail;
//अणु added क्रम rtl819x
#घोषणा IEEE80211_QUEUE_LIMIT 128
	u8 AsocRetryCount;
	अचिन्हित पूर्णांक hw_header;
	काष्ठा sk_buff_head skb_रुकोQ[MAX_QUEUE_SIZE];
	काष्ठा sk_buff_head  skb_aggQ[MAX_QUEUE_SIZE];
	काष्ठा sk_buff_head  skb_drv_aggQ[MAX_QUEUE_SIZE];
	u32	sta_edca_param[4];
	bool aggregation;
	// Enable/Disable Rx immediate BA capability.
	bool enable_rx_imm_BA;
	bool bibsscoordinator;

	//+by amy क्रम DM ,080515
	//Dynamic Tx घातer क्रम near/far range enable/Disable  , by amy , 2008-05-15
	bool	bdynamic_txघातer_enable;

	bool bCTSToSelfEnable;
	u8	CTSToSelfTH;

	u32	fsync_समय_पूर्णांकerval;
	u32	fsync_rate_biपंचांगap;
	u8	fsync_rssi_threshold;
	bool	bfsync_enable;

	u8	fsync_multiple_समयपूर्णांकerval;		// FsyncMultipleTimeInterval * FsyncTimeInterval
	u32	fsync_firstdअगरf_ratethreshold;		// low threshold
	u32	fsync_seconddअगरf_ratethreshold;	 // decrease threshold
	Fsync_State			fsync_state;
	bool		bis_any_nonbepkts;
	//20Mhz 40Mhz AutoSwitch Threshold
	काष्ठा bandwidth_स्वतःचयन bandwidth_स्वतः_चयन;
	//क्रम txघातer tracking
	bool FwRWRF;

	//added by amy क्रम AP roaming
	काष्ठा rt_link_detect LinkDetectInfo;
	//added by amy क्रम ps
	काष्ठा rt_घातer_save_control PowerSaveControl;
//पूर्ण
	/* used अगर IEEE_SOFTMAC_TX_QUEUE is set */
	काष्ठा  tx_pending tx_pending;

	/* used अगर IEEE_SOFTMAC_ASSOCIATE is set */
	काष्ठा समयr_list associate_समयr;

	/* used अगर IEEE_SOFTMAC_BEACONS is set */
	काष्ठा समयr_list beacon_समयr;
	काष्ठा work_काष्ठा associate_complete_wq;
	काष्ठा work_काष्ठा associate_procedure_wq;
	काष्ठा delayed_work sofपंचांगac_scan_wq;
	काष्ठा delayed_work associate_retry_wq;
	 काष्ठा delayed_work start_ibss_wq;
	काष्ठा work_काष्ठा wx_sync_scan_wq;
	काष्ठा workqueue_काष्ठा *wq;
	// Qos related. Added by Annie, 2005-11-01.
	//STA_QOS  StaQos;

	//u32 STA_EDCA_PARAM[4];
	//CHANNEL_ACCESS_SETTING ChannelAccessSetting;

	काष्ठा ieee80211_rxb *stats_IndicateArray[REORDER_WIN_SIZE];

	/* Callback functions */
	व्योम (*set_security)(काष्ठा net_device *dev,
			     काष्ठा ieee80211_security *sec);

	/* Used to TX data frame by using txb काष्ठाs.
	 * this is not used अगर in the sofपंचांगac_features
	 * is set the flag IEEE_SOFTMAC_TX_QUEUE
	 */
	पूर्णांक (*hard_start_xmit)(काष्ठा ieee80211_txb *txb,
			       काष्ठा net_device *dev);

	पूर्णांक (*reset_port)(काष्ठा net_device *dev);
	पूर्णांक (*is_queue_full)(काष्ठा net_device *dev, पूर्णांक pri);

	पूर्णांक (*handle_management)(काष्ठा net_device *dev,
				  काष्ठा ieee80211_network *network, u16 type);
	पूर्णांक (*is_qos_active)(काष्ठा net_device *dev, काष्ठा sk_buff *skb);

	/* Sofपंचांगac-generated frames (management) are TXed via this
	 * callback अगर the flag IEEE_SOFTMAC_SINGLE_QUEUE is
	 * not set. As some cards may have dअगरferent HW queues that
	 * one might want to use क्रम data and management frames
	 * the option to have two callbacks might be useful.
	 * This function can't sleep.
	 */
	पूर्णांक (*sofपंचांगac_hard_start_xmit)(काष्ठा sk_buff *skb,
			       काष्ठा net_device *dev);

	/* used instead of hard_start_xmit (not sofपंचांगac_hard_start_xmit)
	 * अगर the IEEE_SOFTMAC_TX_QUEUE feature is used to TX data
	 * frames. I the option IEEE_SOFTMAC_SINGLE_QUEUE is also set
	 * then also management frames are sent via this callback.
	 * This function can't sleep.
	 */
	व्योम (*sofपंचांगac_data_hard_start_xmit)(काष्ठा sk_buff *skb,
			       काष्ठा net_device *dev, पूर्णांक rate);

	/* stops the HW queue क्रम DATA frames. Useful to aव्योम
	 * waste समय to TX data frame when we are reassociating
	 * This function can sleep.
	 */
	व्योम (*data_hard_stop)(काष्ठा net_device *dev);

	/* OK this is complementar to data_poll_hard_stop */
	व्योम (*data_hard_resume)(काष्ठा net_device *dev);

	/* ask to the driver to retune the radio .
	 * This function can sleep. the driver should ensure
	 * the radio has been चयनed beक्रमe वापस.
	 */
	व्योम (*set_chan)(काष्ठा net_device *dev, लघु ch);

	/* These are not used अगर the ieee stack takes care of
	 * scanning (IEEE_SOFTMAC_SCAN feature set).
	 * In this हाल only the set_chan is used.
	 *
	 * The syncro version is similar to the start_scan but
	 * करोes not वापस until all channels has been scanned.
	 * this is called in user context and should sleep,
	 * it is called in a work_queue when चयनing to ad-hoc mode
	 * or in behalf of iwlist scan when the card is associated
	 * and root user ask क्रम a scan.
	 * the function stop_scan should stop both the syncro and
	 * background scanning and can sleep.
	 * The function start_scan should initiate the background
	 * scanning and can't sleep.
	 */
	व्योम (*scan_syncro)(काष्ठा net_device *dev);
	व्योम (*start_scan)(काष्ठा net_device *dev);
	व्योम (*stop_scan)(काष्ठा net_device *dev);

	/* indicate the driver that the link state is changed
	 * क्रम example it may indicate the card is associated now.
	 * Driver might be पूर्णांकerested in this to apply RX filter
	 * rules or simply light the LINK led
	 */
	व्योम (*link_change)(काष्ठा net_device *dev);

	/* these two function indicates to the HW when to start
	 * and stop to send beacons. This is used when the
	 * IEEE_SOFTMAC_BEACONS is not set. For now the
	 * stop_send_bacons is NOT guaranteed to be called only
	 * after start_send_beacons.
	 */
	व्योम (*start_send_beacons)(काष्ठा net_device *dev, u16 tx_rate);
	व्योम (*stop_send_beacons)(काष्ठा net_device *dev);

	/* घातer save mode related */
	व्योम (*sta_wake_up)(काष्ठा net_device *dev);
	व्योम (*ps_request_tx_ack)(काष्ठा net_device *dev);
	व्योम (*enter_sleep_state)(काष्ठा net_device *dev, u32 th, u32 tl);
	लघु (*ps_is_queue_empty)(काष्ठा net_device *dev);
	पूर्णांक (*handle_beacon)(काष्ठा net_device *dev, काष्ठा ieee80211_beacon *beacon, काष्ठा ieee80211_network *network);
	पूर्णांक (*handle_assoc_response)(काष्ठा net_device *dev, काष्ठा ieee80211_assoc_response_frame *resp, काष्ठा ieee80211_network *network);


	/* check whether Tx hw resource available */
	लघु (*check_nic_enough_desc)(काष्ठा net_device *dev, पूर्णांक queue_index);
	//added by wb क्रम HT related
//	व्योम (*SwChnlByTimerHandler)(काष्ठा net_device *dev, पूर्णांक channel);
	व्योम (*SetBWModeHandler)(काष्ठा net_device *dev, क्रमागत ht_channel_width Bandwidth, क्रमागत ht_extension_chan_offset Offset);
//	व्योम (*UpdateHalRATRTableHandler)(काष्ठा net_device* dev, u8* pMcsRate);
	bool (*GetNmodeSupportBySecCfg)(काष्ठा net_device *dev);
	व्योम (*SetWirelessMode)(काष्ठा net_device *dev, u8 wireless_mode);
	bool (*GetHalfNmodeSupportByAPsHandler)(काष्ठा net_device *dev);
	व्योम (*InitialGainHandler)(काष्ठा net_device *dev, u8 Operation);

	/* This must be the last item so that it poपूर्णांकs to the data
	 * allocated beyond this काष्ठाure by alloc_ieee80211
	 */
	u8 priv[];
पूर्ण;

#घोषणा IEEE_A            (1<<0)
#घोषणा IEEE_B            (1<<1)
#घोषणा IEEE_G            (1<<2)
#घोषणा IEEE_N_24G        (1<<4)
#घोषणा IEEE_N_5G         (1<<5)
#घोषणा IEEE_MODE_MASK    (IEEE_A | IEEE_B | IEEE_G)

/* Generate a 802.11 header */

/* Uses the channel change callback directly
 * instead of [start/stop] scan callbacks
 */
#घोषणा IEEE_SOFTMAC_SCAN (1<<2)

/* Perक्रमm authentication and association handshake */
#घोषणा IEEE_SOFTMAC_ASSOCIATE (1<<3)

/* Generate probe requests */
#घोषणा IEEE_SOFTMAC_PROBERQ (1<<4)

/* Generate respones to probe requests */
#घोषणा IEEE_SOFTMAC_PROBERS (1<<5)

/* The ieee802.11 stack will manages the netअगर queue
 * wake/stop क्रम the driver, taking care of 802.11
 * fragmentation. See sofपंचांगac.c क्रम details.
 */
#घोषणा IEEE_SOFTMAC_TX_QUEUE (1<<7)

/* Uses only the sofपंचांगac_data_hard_start_xmit
 * even क्रम TX management frames.
 */
#घोषणा IEEE_SOFTMAC_SINGLE_QUEUE (1<<8)

/* Generate beacons.  The stack will enqueue beacons
 * to the card
 */
#घोषणा IEEE_SOFTMAC_BEACONS (1<<6)

अटल अंतरभूत व्योम *ieee80211_priv(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा ieee80211_device *)netdev_priv(dev))->priv;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_is_empty_essid(स्थिर अक्षर *essid, पूर्णांक essid_len)
अणु
	/* Single white space is क्रम Linksys APs */
	अगर (essid_len == 1 && essid[0] == ' ')
		वापस 1;

	/* Otherwise, अगर the entire essid is 0, we assume it is hidden */
	जबतक (essid_len) अणु
		essid_len--;
		अगर (essid[essid_len] != '\0')
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_is_valid_mode(काष्ठा ieee80211_device *ieee, पूर्णांक mode)
अणु
	/*
	 * It is possible क्रम both access poपूर्णांकs and our device to support
	 * combinations of modes, so as दीर्घ as there is one valid combination
	 * of ap/device supported modes, then वापस success
	 *
	 */
	अगर ((mode & IEEE_A) &&
	    (ieee->modulation & IEEE80211_OFDM_MODULATION) &&
	    (ieee->freq_band & IEEE80211_52GHZ_BAND))
		वापस 1;

	अगर ((mode & IEEE_G) &&
	    (ieee->modulation & IEEE80211_OFDM_MODULATION) &&
	    (ieee->freq_band & IEEE80211_24GHZ_BAND))
		वापस 1;

	अगर ((mode & IEEE_B) &&
	    (ieee->modulation & IEEE80211_CCK_MODULATION) &&
	    (ieee->freq_band & IEEE80211_24GHZ_BAND))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_get_hdrlen(u16 fc)
अणु
	पूर्णांक hdrlen = IEEE80211_3ADDR_LEN;

	चयन (WLAN_FC_GET_TYPE(fc)) अणु
	हाल IEEE80211_FTYPE_DATA:
		अगर ((fc & IEEE80211_FCTL_FROMDS) && (fc & IEEE80211_FCTL_TODS))
			hdrlen = IEEE80211_4ADDR_LEN; /* Addr4 */
		अगर (IEEE80211_QOS_HAS_SEQ(fc))
			hdrlen += 2; /* QOS ctrl*/
		अवरोध;
	हाल IEEE80211_FTYPE_CTL:
		चयन (WLAN_FC_GET_STYPE(fc)) अणु
		हाल IEEE80211_STYPE_CTS:
		हाल IEEE80211_STYPE_ACK:
			hdrlen = IEEE80211_1ADDR_LEN;
			अवरोध;
		शेष:
			hdrlen = IEEE80211_2ADDR_LEN;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस hdrlen;
पूर्ण

अटल अंतरभूत u8 *ieee80211_get_payload(काष्ठा rtl_80211_hdr *hdr)
अणु
	चयन (ieee80211_get_hdrlen(le16_to_cpu(hdr->frame_ctl))) अणु
	हाल IEEE80211_1ADDR_LEN:
		वापस ((काष्ठा rtl_80211_hdr_1addr *)hdr)->payload;
	हाल IEEE80211_2ADDR_LEN:
		वापस ((काष्ठा rtl_80211_hdr_2addr *)hdr)->payload;
	हाल IEEE80211_3ADDR_LEN:
		वापस ((काष्ठा rtl_80211_hdr_3addr *)hdr)->payload;
	हाल IEEE80211_4ADDR_LEN:
		वापस ((काष्ठा rtl_80211_hdr_4addr *)hdr)->payload;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_is_ofdm_rate(u8 rate)
अणु
	चयन (rate & ~IEEE80211_BASIC_RATE_MASK) अणु
	हाल IEEE80211_OFDM_RATE_6MB:
	हाल IEEE80211_OFDM_RATE_9MB:
	हाल IEEE80211_OFDM_RATE_12MB:
	हाल IEEE80211_OFDM_RATE_18MB:
	हाल IEEE80211_OFDM_RATE_24MB:
	हाल IEEE80211_OFDM_RATE_36MB:
	हाल IEEE80211_OFDM_RATE_48MB:
	हाल IEEE80211_OFDM_RATE_54MB:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_is_cck_rate(u8 rate)
अणु
	चयन (rate & ~IEEE80211_BASIC_RATE_MASK) अणु
	हाल IEEE80211_CCK_RATE_1MB:
	हाल IEEE80211_CCK_RATE_2MB:
	हाल IEEE80211_CCK_RATE_5MB:
	हाल IEEE80211_CCK_RATE_11MB:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


/* ieee80211.c */
व्योम मुक्त_ieee80211(काष्ठा net_device *dev);
काष्ठा net_device *alloc_ieee80211(पूर्णांक माप_priv);

पूर्णांक ieee80211_set_encryption(काष्ठा ieee80211_device *ieee);

/* ieee80211_tx.c */

पूर्णांक ieee80211_encrypt_fragment(काष्ठा ieee80211_device *ieee,
			       काष्ठा sk_buff *frag, पूर्णांक hdr_len);

पूर्णांक ieee80211_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम ieee80211_txb_मुक्त(काष्ठा ieee80211_txb *txb);


/* ieee80211_rx.c */
पूर्णांक ieee80211_rx(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा ieee80211_rx_stats *rx_stats);
व्योम ieee80211_rx_mgt(काष्ठा ieee80211_device *ieee,
		      काष्ठा rtl_80211_hdr_4addr *header,
		      काष्ठा ieee80211_rx_stats *stats);

/* ieee80211_wx.c */
पूर्णांक ieee80211_wx_get_scan(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक ieee80211_wx_set_encode(काष्ठा ieee80211_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक ieee80211_wx_get_encode(काष्ठा ieee80211_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक ieee80211_wx_get_encode_ext(काष्ठा ieee80211_device *ieee,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक ieee80211_wx_set_encode_ext(काष्ठा ieee80211_device *ieee,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक ieee80211_wx_set_auth(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *data, अक्षर *extra);
पूर्णांक ieee80211_wx_set_mlme(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक ieee80211_wx_set_gen_ie(काष्ठा ieee80211_device *ieee, u8 *ie, माप_प्रकार len);

/* ieee80211_sofपंचांगac.c */
लघु ieee80211_is_54g(स्थिर काष्ठा ieee80211_network *net);
लघु ieee80211_is_लघुslot(स्थिर काष्ठा ieee80211_network *net);
पूर्णांक ieee80211_rx_frame_sofपंचांगac(काष्ठा ieee80211_device *ieee,
			       काष्ठा sk_buff *skb,
			       काष्ठा ieee80211_rx_stats *rx_stats,
			       u16 type, u16 stype);
व्योम ieee80211_sofपंचांगac_new_net(काष्ठा ieee80211_device *ieee,
			       काष्ठा ieee80211_network *net);

व्योम SendDisassociation(काष्ठा ieee80211_device *ieee, u8 *asSta, u8 asRsn);
व्योम ieee80211_sofपंचांगac_xmit(काष्ठा ieee80211_txb *txb,
			    काष्ठा ieee80211_device *ieee);

व्योम ieee80211_stop_send_beacons(काष्ठा ieee80211_device *ieee);
व्योम notअगरy_wx_assoc_event(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_sofपंचांगac_check_all_nets(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_start_bss(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_start_master_bss(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_start_ibss(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_sofपंचांगac_init(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_sofपंचांगac_मुक्त(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_associate_पात(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_disassociate(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_stop_scan(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_start_scan_syncro(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_check_all_nets(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_start_protocol(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_stop_protocol(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_sofपंचांगac_start_protocol(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_sofपंचांगac_stop_protocol(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_reset_queue(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_wake_queue(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_stop_queue(काष्ठा ieee80211_device *ieee);
काष्ठा sk_buff *ieee80211_get_beacon(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_start_send_beacons(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_stop_send_beacons(काष्ठा ieee80211_device *ieee);
पूर्णांक ieee80211_wpa_supplicant_ioctl(काष्ठा ieee80211_device *ieee,
				   काष्ठा iw_poपूर्णांक *p);
व्योम notअगरy_wx_assoc_event(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_ps_tx_ack(काष्ठा ieee80211_device *ieee, लघु success);

व्योम sofपंचांगac_mgmt_xmit(काष्ठा sk_buff *skb, काष्ठा ieee80211_device *ieee);

/* ieee80211_crypt_ccmp&tkip&wep.c */
व्योम ieee80211_tkip_null(व्योम);

पूर्णांक ieee80211_crypto_init(व्योम);
व्योम ieee80211_crypto_deinit(व्योम);
पूर्णांक ieee80211_crypto_tkip_init(व्योम);
व्योम ieee80211_crypto_tkip_निकास(व्योम);
पूर्णांक ieee80211_crypto_ccmp_init(व्योम);
व्योम ieee80211_crypto_ccmp_निकास(व्योम);
पूर्णांक ieee80211_crypto_wep_init(व्योम);
व्योम ieee80211_crypto_wep_निकास(व्योम);

/* ieee80211_sofपंचांगac_wx.c */

पूर्णांक ieee80211_wx_get_wap(काष्ठा ieee80211_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *ext);

पूर्णांक ieee80211_wx_set_wap(काष्ठा ieee80211_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *awrq,
			 अक्षर *extra);

पूर्णांक ieee80211_wx_get_essid(काष्ठा ieee80211_device *ieee,
			   काष्ठा iw_request_info *a,
			   जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक ieee80211_wx_set_rate(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_get_rate(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_set_mode(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *a,
			  जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक ieee80211_wx_set_scan(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *a,
			  जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक ieee80211_wx_set_essid(काष्ठा ieee80211_device *ieee,
			   काष्ठा iw_request_info *a,
			   जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_get_mode(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *a,
			  जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक ieee80211_wx_set_freq(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *a,
			  जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक ieee80211_wx_get_freq(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *a,
			  जोड़ iwreq_data *wrqu, अक्षर *b);

/* ieee80211_module.c */
पूर्णांक ieee80211_debug_init(व्योम);
व्योम ieee80211_debug_निकास(व्योम);

//बाह्य व्योम ieee80211_wx_sync_scan_wq(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_wx_sync_scan_wq(काष्ठा work_काष्ठा *work);


पूर्णांक ieee80211_wx_set_rawtx(काष्ठा ieee80211_device *ieee,
			   काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_get_name(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_set_घातer(काष्ठा ieee80211_device *ieee,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_get_घातer(काष्ठा ieee80211_device *ieee,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_set_rts(काष्ठा ieee80211_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक ieee80211_wx_get_rts(काष्ठा ieee80211_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra);
//HT
#घोषणा MAX_RECEIVE_BUFFER_SIZE 9100  //
व्योम HTDebugHTCapability(u8 *CapIE, u8 *TitleString);
व्योम HTDebugHTInfo(u8 *InfoIE, u8 *TitleString);

व्योम HTSetConnectBwMode(काष्ठा ieee80211_device *ieee,
			क्रमागत ht_channel_width Bandwidth, क्रमागत ht_extension_chan_offset Offset);
व्योम HTUpdateDefaultSetting(काष्ठा ieee80211_device *ieee);
व्योम HTConकाष्ठाCapabilityElement(काष्ठा ieee80211_device *ieee, u8 *posHTCap,
				  u8 *len, u8 isEncrypt);
व्योम HTConकाष्ठाInfoElement(काष्ठा ieee80211_device *ieee, u8 *posHTInfo,
			    u8 *len, u8 isEncrypt);
व्योम HTConकाष्ठाRT2RTAggElement(काष्ठा ieee80211_device *ieee, u8 *posRT2RTAgg,
				u8 *len);
व्योम HTOnAssocRsp(काष्ठा ieee80211_device *ieee);
व्योम HTInitializeHTInfo(काष्ठा ieee80211_device *ieee);
व्योम HTInitializeBssDesc(PBSS_HT pBssHT);
व्योम HTResetSelfAndSavePeerSetting(काष्ठा ieee80211_device *ieee,
				   काष्ठा ieee80211_network *pNetwork);
व्योम HTUpdateSelfAndPeerSetting(काष्ठा ieee80211_device *ieee,
				काष्ठा ieee80211_network *pNetwork);
u8 HTGetHighestMCSRate(काष्ठा ieee80211_device *ieee,
		       u8 *pMCSRateSet, u8 *pMCSFilter);
बाह्य u8 MCS_FILTER_ALL[];
बाह्य u16 MCS_DATA_RATE[2][2][77];
u8 HTCCheck(काष्ठा ieee80211_device *ieee, u8 *pFrame);
व्योम HTResetIOTSetting(PRT_HIGH_THROUGHPUT pHTInfo);
bool IsHTHalfNmodeAPs(काष्ठा ieee80211_device *ieee);
u16 TxCountToDataRate(काष्ठा ieee80211_device *ieee, u8 nDataRate);
//function in BAPROC.c
पूर्णांक ieee80211_rx_ADDBAReq(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb);
पूर्णांक ieee80211_rx_ADDBARsp(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb);
पूर्णांक ieee80211_rx_DELBA(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb);
व्योम TsInitAddBA(काष्ठा ieee80211_device *ieee, काष्ठा tx_ts_record *pTS,
		 u8 Policy, u8 bOverग_लिखोPending);
व्योम TsInitDelBA(काष्ठा ieee80211_device *ieee,
		 काष्ठा ts_common_info *pTsCommonInfo, क्रमागत tr_select TxRxSelect);
व्योम BaSetupTimeOut(काष्ठा समयr_list *t);
व्योम TxBaInactTimeout(काष्ठा समयr_list *t);
व्योम RxBaInactTimeout(काष्ठा समयr_list *t);
व्योम ResetBaEntry(काष्ठा ba_record *pBA);
//function in TS.c
bool GetTs(
	काष्ठा ieee80211_device		*ieee,
	काष्ठा ts_common_info           **ppTS,
	u8                              *Addr,
	u8                              TID,
	क्रमागत tr_select                  TxRxSelect,  //Rx:1, Tx:0
	bool                            bAddNewTs
	);
व्योम TSInitialize(काष्ठा ieee80211_device *ieee);
व्योम TsStartAddBaProcess(काष्ठा ieee80211_device *ieee, काष्ठा tx_ts_record   *pTxTS);
व्योम RemovePeerTS(काष्ठा ieee80211_device *ieee, u8 *Addr);
व्योम RemoveAllTS(काष्ठा ieee80211_device *ieee);
व्योम ieee80211_sofपंचांगac_scan_syncro(काष्ठा ieee80211_device *ieee);

बाह्य स्थिर दीर्घ ieee80211_wlan_frequencies[];

अटल अंतरभूत व्योम ieee80211_increment_scans(काष्ठा ieee80211_device *ieee)
अणु
	ieee->scans++;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_get_scans(काष्ठा ieee80211_device *ieee)
अणु
	वापस ieee->scans;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *escape_essid(स्थिर अक्षर *essid, u8 essid_len)
अणु
	अटल अक्षर escaped[IW_ESSID_MAX_SIZE * 2 + 1];

	अगर (ieee80211_is_empty_essid(essid, essid_len)) अणु
		स_नकल(escaped, "<hidden>", माप("<hidden>"));
		वापस escaped;
	पूर्ण

	snम_लिखो(escaped, माप(escaped), "%*pE", essid_len, essid);
	वापस escaped;
पूर्ण

/* For the function is more related to hardware setting, it's better to use the
 * ieee handler to refer to it.
 */
लघु check_nic_enough_desc(काष्ठा net_device *dev, पूर्णांक queue_index);
पूर्णांक ieee80211_data_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक ieee80211_parse_info_param(काष्ठा ieee80211_device *ieee,
			       काष्ठा ieee80211_info_element *info_element,
			       u16 length,
			       काष्ठा ieee80211_network *network,
			       काष्ठा ieee80211_rx_stats *stats);

व्योम ieee80211_indicate_packets(काष्ठा ieee80211_device *ieee,
				काष्ठा ieee80211_rxb **prxbIndicateArray,
				u8 index);
#घोषणा RT_ASOC_RETRY_LIMIT	5
#पूर्ण_अगर /* IEEE80211_H */
