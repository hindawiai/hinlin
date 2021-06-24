<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Merged with मुख्यline rtllib.h in Aug 2004.  Original ieee802_11
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
#अगर_अघोषित RTLLIB_H
#घोषणा RTLLIB_H
#समावेश <linux/अगर_ether.h> /* ETH_ALEN */
#समावेश <linux/kernel.h>   /* ARRAY_SIZE */
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>

#समावेश <linux/delay.h>
#समावेश <linux/wireless.h>

#समावेश "rtllib_debug.h"
#समावेश "rtl819x_HT.h"
#समावेश "rtl819x_BA.h"
#समावेश "rtl819x_TS.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h> /* ARPHRD_ETHER */
#समावेश <net/lib80211.h>

#घोषणा MAX_PRECMD_CNT 16
#घोषणा MAX_RFDEPENDCMD_CNT 16
#घोषणा MAX_POSTCMD_CNT 16

#अगर_अघोषित WIRELESS_SPY
#घोषणा WIRELESS_SPY
#पूर्ण_अगर
#समावेश <net/iw_handler.h>

#अगर_अघोषित IW_MODE_MONITOR
#घोषणा IW_MODE_MONITOR 6
#पूर्ण_अगर

#अगर_अघोषित IWEVCUSTOM
#घोषणा IWEVCUSTOM 0x8c02
#पूर्ण_अगर

#अगर_अघोषित IW_CUSTOM_MAX
/* Max number of अक्षर in custom event - use multiple of them अगर needed */
#घोषणा IW_CUSTOM_MAX	256	/* In bytes */
#पूर्ण_अगर

#घोषणा skb_tail_poपूर्णांकer_rsl(skb) skb_tail_poपूर्णांकer(skb)

#घोषणा queue_delayed_work_rsl(x, y, z) queue_delayed_work(x, y, z)
#घोषणा INIT_DELAYED_WORK_RSL(x, y, z) INIT_DELAYED_WORK(x, y)

#घोषणा queue_work_rsl(x, y) queue_work(x, y)
#घोषणा INIT_WORK_RSL(x, y, z) INIT_WORK(x, y)

#घोषणा container_of_work_rsl(x, y, z) container_of(x, y, z)
#घोषणा container_of_dwork_rsl(x, y, z)				\
	container_of(to_delayed_work(x), y, z)

#घोषणा iwe_stream_add_event_rsl(info, start, stop, iwe, len)	\
	iwe_stream_add_event(info, start, stop, iwe, len)

#घोषणा iwe_stream_add_poपूर्णांक_rsl(info, start, stop, iwe, p)	\
	iwe_stream_add_poपूर्णांक(info, start, stop, iwe, p)

अटल अंतरभूत व्योम *netdev_priv_rsl(काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

#घोषणा KEY_TYPE_NA		0x0
#घोषणा KEY_TYPE_WEP40		0x1
#घोषणा KEY_TYPE_TKIP		0x2
#घोषणा KEY_TYPE_CCMP		0x4
#घोषणा KEY_TYPE_WEP104		0x5
/* added क्रम rtl819x tx procedure */
#घोषणा MAX_QUEUE_SIZE		0x10

#घोषणा BK_QUEUE			       0
#घोषणा BE_QUEUE			       1
#घोषणा VI_QUEUE			       2
#घोषणा VO_QUEUE			       3
#घोषणा HCCA_QUEUE			     4
#घोषणा TXCMD_QUEUE			    5
#घोषणा MGNT_QUEUE			     6
#घोषणा HIGH_QUEUE			     7
#घोषणा BEACON_QUEUE			   8

#अगर_अघोषित IW_MODE_MESH
#घोषणा IW_MODE_MESH			7
#पूर्ण_अगर

#घोषणा IE_CISCO_FLAG_POSITION		0x08
#घोषणा SUPPORT_CKIP_MIC			0x08
#घोषणा SUPPORT_CKIP_PK			0x10
#घोषणा	RT_RF_OFF_LEVL_HALT_NIC		BIT3
#घोषणा	RT_IN_PS_LEVEL(pPSC, _PS_FLAG)		\
	((pPSC->CurPsLevel & _PS_FLAG) ? true : false)
#घोषणा	RT_CLEAR_PS_LEVEL(pPSC, _PS_FLAG)	\
	(pPSC->CurPsLevel &= (~(_PS_FLAG)))
#घोषणा	RT_SET_PS_LEVEL(pPSC, _PS_FLAG)	(pPSC->CurPsLevel |= _PS_FLAG)

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
	u8 bHwSec:1;

	u8 nStuckCount;

	/* Tx Firmware Related flags (10-11)*/
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
	u8 drv_agg_enable:1;
	u8 reserved2:1;

	/* Tx Desc related element(12-19) */
	u8 rata_index;
	u8 queue_index;
	u16 txbuf_size;
	u8 RATRIndex;
	u8 bAMSDU:1;
	u8 bFromAggrQ:1;
	u8 reserved6:6;
	u8 macId;
	u8 priority;

	/* Tx firmware related element(20-27) */
	u8 data_rate;
	u8 rts_rate;
	u8 ampdu_factor;
	u8 ampdu_density;
	u8 DrvAggrNum;
	u8 bdhcp;
	u16 pkt_size;
	u8 bIsSpecialDataFrame;

	u8 bBTTxPacket;
	u8 bIsBTProbRsp;
पूर्ण;

क्रमागत sw_chnl_cmd_id अणु
	CmdID_End,
	CmdID_SetTxPowerLevel,
	CmdID_BBRegWrite10,
	CmdID_WritePortUदीर्घ,
	CmdID_WritePortUलघु,
	CmdID_WritePortUअक्षर,
	CmdID_RF_WriteReg,
पूर्ण;

काष्ठा sw_chnl_cmd अणु
	क्रमागत sw_chnl_cmd_id CmdID;
	u32			Para1;
	u32			Para2;
	u32			msDelay;
पूर्ण __packed;

/*--------------------------Define -------------------------------------------*/
#घोषणा MGN_1M		  0x02
#घोषणा MGN_2M		  0x04
#घोषणा MGN_5_5M		0x0b
#घोषणा MGN_11M		 0x16

#घोषणा MGN_6M		  0x0c
#घोषणा MGN_9M		  0x12
#घोषणा MGN_12M		 0x18
#घोषणा MGN_18M		 0x24
#घोषणा MGN_24M		 0x30
#घोषणा MGN_36M		 0x48
#घोषणा MGN_48M		 0x60
#घोषणा MGN_54M		 0x6c

#घोषणा MGN_MCS0		0x80
#घोषणा MGN_MCS1		0x81
#घोषणा MGN_MCS2		0x82
#घोषणा MGN_MCS3		0x83
#घोषणा MGN_MCS4		0x84
#घोषणा MGN_MCS5		0x85
#घोषणा MGN_MCS6		0x86
#घोषणा MGN_MCS7		0x87
#घोषणा MGN_MCS8		0x88
#घोषणा MGN_MCS9		0x89
#घोषणा MGN_MCS10	       0x8a
#घोषणा MGN_MCS11	       0x8b
#घोषणा MGN_MCS12	       0x8c
#घोषणा MGN_MCS13	       0x8d
#घोषणा MGN_MCS14	       0x8e
#घोषणा MGN_MCS15	       0x8f

क्रमागत hw_variables अणु
	HW_VAR_ETHER_ADDR,
	HW_VAR_MULTICAST_REG,
	HW_VAR_BASIC_RATE,
	HW_VAR_BSSID,
	HW_VAR_MEDIA_STATUS,
	HW_VAR_SECURITY_CONF,
	HW_VAR_BEACON_INTERVAL,
	HW_VAR_ATIM_WINDOW,
	HW_VAR_LISTEN_INTERVAL,
	HW_VAR_CS_COUNTER,
	HW_VAR_DEFAULTKEY0,
	HW_VAR_DEFAULTKEY1,
	HW_VAR_DEFAULTKEY2,
	HW_VAR_DEFAULTKEY3,
	HW_VAR_SIFS,
	HW_VAR_DIFS,
	HW_VAR_EIFS,
	HW_VAR_SLOT_TIME,
	HW_VAR_ACK_PREAMBLE,
	HW_VAR_CW_CONFIG,
	HW_VAR_CW_VALUES,
	HW_VAR_RATE_FALLBACK_CONTROL,
	HW_VAR_CONTENTION_WINDOW,
	HW_VAR_RETRY_COUNT,
	HW_VAR_TR_SWITCH,
	HW_VAR_COMMAND,
	HW_VAR_WPA_CONFIG,
	HW_VAR_AMPDU_MIN_SPACE,
	HW_VAR_SHORTGI_DENSITY,
	HW_VAR_AMPDU_FACTOR,
	HW_VAR_MCS_RATE_AVAILABLE,
	HW_VAR_AC_PARAM,
	HW_VAR_ACM_CTRL,
	HW_VAR_DIS_Req_Qsize,
	HW_VAR_CCX_CHNL_LOAD,
	HW_VAR_CCX_NOISE_HISTOGRAM,
	HW_VAR_CCX_CLM_NHM,
	HW_VAR_TxOPLimit,
	HW_VAR_TURBO_MODE,
	HW_VAR_RF_STATE,
	HW_VAR_RF_OFF_BY_HW,
	HW_VAR_BUS_SPEED,
	HW_VAR_SET_DEV_POWER,

	HW_VAR_RCR,
	HW_VAR_RATR_0,
	HW_VAR_RRSR,
	HW_VAR_CPU_RST,
	HW_VAR_CECHK_BSSID,
	HW_VAR_LBK_MODE,
	HW_VAR_AES_11N_FIX,
	HW_VAR_USB_RX_AGGR,
	HW_VAR_USER_CONTROL_TURBO_MODE,
	HW_VAR_RETRY_LIMIT,
	HW_VAR_INIT_TX_RATE,
	HW_VAR_TX_RATE_REG,
	HW_VAR_EFUSE_USAGE,
	HW_VAR_EFUSE_BYTES,
	HW_VAR_AUTOLOAD_STATUS,
	HW_VAR_RF_2R_DISABLE,
	HW_VAR_SET_RPWM,
	HW_VAR_H2C_FW_PWRMODE,
	HW_VAR_H2C_FW_JOINBSSRPT,
	HW_VAR_1X1_RECV_COMBINE,
	HW_VAR_STOP_SEND_BEACON,
	HW_VAR_TSF_TIMER,
	HW_VAR_IO_CMD,

	HW_VAR_RF_RECOVERY,
	HW_VAR_H2C_FW_UPDATE_GTK,
	HW_VAR_WF_MASK,
	HW_VAR_WF_CRC,
	HW_VAR_WF_IS_MAC_ADDR,
	HW_VAR_H2C_FW_OFFLOAD,
	HW_VAR_RESET_WFCRC,

	HW_VAR_HANDLE_FW_C2H,
	HW_VAR_DL_FW_RSVD_PAGE,
	HW_VAR_AID,
	HW_VAR_HW_SEQ_ENABLE,
	HW_VAR_CORRECT_TSF,
	HW_VAR_BCN_VALID,
	HW_VAR_FWLPS_RF_ON,
	HW_VAR_DUAL_TSF_RST,
	HW_VAR_SWITCH_EPHY_WoWLAN,
	HW_VAR_INT_MIGRATION,
	HW_VAR_INT_AC,
	HW_VAR_RF_TIMING,
पूर्ण;

क्रमागत rt_op_mode अणु
	RT_OP_MODE_AP,
	RT_OP_MODE_INFRASTRUCTURE,
	RT_OP_MODE_IBSS,
	RT_OP_MODE_NO_LINK,
पूर्ण;


#घोषणा aSअगरsTime						\
	 (((priv->rtllib->current_network.mode == IEEE_A)	\
	|| (priv->rtllib->current_network.mode == IEEE_N_24G)	\
	|| (priv->rtllib->current_network.mode == IEEE_N_5G)) ? 16 : 10)

#घोषणा MGMT_QUEUE_NUM 5

#घोषणा MAX_IE_LEN  0xff

#घोषणा msleep_पूर्णांकerruptible_rsl  msleep_पूर्णांकerruptible

/* Maximum size क्रम the MA-UNITDATA primitive, 802.11 standard section
 * 6.2.1.1.2.
 *
 * The figure in section 7.1.2 suggests a body size of up to 2312
 * bytes is allowed, which is a bit confusing, I suspect this
 * represents the 2304 bytes of real data, plus a possible 8 bytes of
 * WEP IV and ICV. (this पूर्णांकerpretation suggested by Ramiro Barreiro)
 */
#घोषणा RTLLIB_1ADDR_LEN 10
#घोषणा RTLLIB_2ADDR_LEN 16
#घोषणा RTLLIB_3ADDR_LEN 24
#घोषणा RTLLIB_4ADDR_LEN 30
#घोषणा RTLLIB_FCS_LEN    4

#घोषणा RTLLIB_SKBBUFFER_SIZE 2500

#घोषणा MIN_FRAG_THRESHOLD     256U
#घोषणा MAX_FRAG_THRESHOLD     2346U

/* Frame control field स्थिरants */
#घोषणा RTLLIB_FCTL_FTYPE		0x000c
#घोषणा RTLLIB_FCTL_STYPE		0x00f0
#घोषणा RTLLIB_FCTL_FRAMETYPE	0x00fc
#घोषणा RTLLIB_FCTL_TODS		0x0100
#घोषणा RTLLIB_FCTL_FROMDS		0x0200
#घोषणा RTLLIB_FCTL_DSTODS		0x0300
#घोषणा RTLLIB_FCTL_MOREFRAGS	0x0400
#घोषणा RTLLIB_FCTL_RETRY		0x0800
#घोषणा RTLLIB_FCTL_PM		0x1000
#घोषणा RTLLIB_FCTL_MOREDATA		0x2000
#घोषणा RTLLIB_FCTL_WEP		0x4000
#घोषणा RTLLIB_FCTL_ORDER		0x8000

#घोषणा RTLLIB_FTYPE_MGMT		0x0000
#घोषणा RTLLIB_FTYPE_CTL		0x0004
#घोषणा RTLLIB_FTYPE_DATA		0x0008

/* management */
#घोषणा RTLLIB_STYPE_ASSOC_REQ	0x0000
#घोषणा RTLLIB_STYPE_ASSOC_RESP		0x0010
#घोषणा RTLLIB_STYPE_REASSOC_REQ	0x0020
#घोषणा RTLLIB_STYPE_REASSOC_RESP	0x0030
#घोषणा RTLLIB_STYPE_PROBE_REQ	0x0040
#घोषणा RTLLIB_STYPE_PROBE_RESP	0x0050
#घोषणा RTLLIB_STYPE_BEACON		0x0080
#घोषणा RTLLIB_STYPE_ATIM		0x0090
#घोषणा RTLLIB_STYPE_DISASSOC	0x00A0
#घोषणा RTLLIB_STYPE_AUTH		0x00B0
#घोषणा RTLLIB_STYPE_DEAUTH		0x00C0
#घोषणा RTLLIB_STYPE_MANAGE_ACT	0x00D0

/* control */
#घोषणा RTLLIB_STYPE_PSPOLL		0x00A0
#घोषणा RTLLIB_STYPE_RTS		0x00B0
#घोषणा RTLLIB_STYPE_CTS		0x00C0
#घोषणा RTLLIB_STYPE_ACK		0x00D0

/* data */
#घोषणा RTLLIB_STYPE_DATA		0x0000
#घोषणा RTLLIB_STYPE_DATA_CFACK	0x0010
#घोषणा RTLLIB_STYPE_DATA_CFPOLL	0x0020
#घोषणा RTLLIB_STYPE_DATA_CFACKPOLL	0x0030
#घोषणा RTLLIB_STYPE_शून्यFUNC	0x0040
#घोषणा RTLLIB_STYPE_QOS_DATA	0x0080
#घोषणा RTLLIB_STYPE_QOS_शून्य	0x00C0

#घोषणा RTLLIB_SCTL_FRAG		0x000F
#घोषणा RTLLIB_SCTL_SEQ		0xFFF0

/* QOS control */
#घोषणा RTLLIB_QCTL_TID	      0x000F

#घोषणा	FC_QOS_BIT					BIT7
#घोषणा IsDataFrame(pdu)	(((pdu[0] & 0x0C) == 0x08) ? true : false)
#घोषणा	IsLegacyDataFrame(pdu)	(IsDataFrame(pdu) && (!(pdu[0]&FC_QOS_BIT)))
#घोषणा IsQoSDataFrame(pframe)			\
	((*(u16 *)pframe&(RTLLIB_STYPE_QOS_DATA|RTLLIB_FTYPE_DATA)) ==	\
	(RTLLIB_STYPE_QOS_DATA|RTLLIB_FTYPE_DATA))
#घोषणा Frame_Order(pframe)     (*(u16 *)pframe&RTLLIB_FCTL_ORDER)
#घोषणा SN_LESS(a, b)		(((a-b)&0x800) != 0)
#घोषणा SN_EQUAL(a, b)	(a == b)
#घोषणा MAX_DEV_ADDR_SIZE 8

क्रमागत act_category अणु
	ACT_CAT_QOS = 1,
	ACT_CAT_DLS = 2,
	ACT_CAT_BA  = 3,
	ACT_CAT_HT  = 7,
	ACT_CAT_WMM = 17,
पूर्ण;

क्रमागत ba_action अणु
	ACT_ADDBAREQ = 0,
	ACT_ADDBARSP = 1,
	ACT_DELBA    = 2,
पूर्ण;

क्रमागत init_gain_op_type अणु
	IG_Backup = 0,
	IG_Restore,
	IG_Max
पूर्ण;

क्रमागत led_ctl_mode अणु
	LED_CTL_POWER_ON = 1,
	LED_CTL_LINK = 2,
	LED_CTL_NO_LINK = 3,
	LED_CTL_TX = 4,
	LED_CTL_RX = 5,
	LED_CTL_SITE_SURVEY = 6,
	LED_CTL_POWER_OFF = 7,
	LED_CTL_START_TO_LINK = 8,
पूर्ण;

क्रमागत rt_rf_type_def अणु
	RF_1T2R = 0,
	RF_2T4R,
पूर्ण;

क्रमागत wireless_mode अणु
	WIRELESS_MODE_UNKNOWN = 0x00,
	WIRELESS_MODE_A = 0x01,
	WIRELESS_MODE_B = 0x02,
	WIRELESS_MODE_G = 0x04,
	WIRELESS_MODE_AUTO = 0x08,
	WIRELESS_MODE_N_24G = 0x10,
	WIRELESS_MODE_N_5G = 0x20
पूर्ण;

#अगर_अघोषित ETH_P_PAE
#घोषणा ETH_P_PAE	0x888E		/* Port Access Entity (IEEE 802.1X) */
#घोषणा ETH_P_IP	0x0800		/* Internet Protocol packet	*/
#घोषणा ETH_P_ARP	0x0806		/* Address Resolution packet	*/
#पूर्ण_अगर /* ETH_P_PAE */

#अगर_अघोषित ETH_P_80211_RAW
#घोषणा ETH_P_80211_RAW (ETH_P_ECONET + 1)
#पूर्ण_अगर

/* IEEE 802.11 defines */

#घोषणा P80211_OUI_LEN 3

काष्ठा rtllib_snap_hdr अणु
	u8    dsap;   /* always 0xAA */
	u8    ssap;   /* always 0xAA */
	u8    ctrl;   /* always 0x03 */
	u8    oui[P80211_OUI_LEN];    /* organizational universal id */

पूर्ण __packed;

क्रमागत _REG_PREAMBLE_MODE अणु
	PREAMBLE_LONG = 1,
	PREAMBLE_AUTO = 2,
	PREAMBLE_SHORT = 3,
पूर्ण;

#घोषणा SNAP_SIZE माप(काष्ठा rtllib_snap_hdr)

#घोषणा WLAN_FC_GET_TYPE(fc) ((fc) & RTLLIB_FCTL_FTYPE)
#घोषणा WLAN_FC_GET_STYPE(fc) ((fc) & RTLLIB_FCTL_STYPE)
#घोषणा WLAN_FC_MORE_DATA(fc) ((fc) & RTLLIB_FCTL_MOREDATA)

#घोषणा WLAN_FC_GET_FRAMETYPE(fc) ((fc) & RTLLIB_FCTL_FRAMETYPE)
#घोषणा WLAN_GET_SEQ_FRAG(seq) ((seq) & RTLLIB_SCTL_FRAG)
#घोषणा WLAN_GET_SEQ_SEQ(seq)  (((seq) & RTLLIB_SCTL_SEQ) >> 4)

/* Authentication algorithms */
#घोषणा WLAN_AUTH_OPEN 0
#घोषणा WLAN_AUTH_SHARED_KEY 1
#घोषणा WLAN_AUTH_LEAP 128

#घोषणा WLAN_CAPABILITY_ESS (1<<0)
#घोषणा WLAN_CAPABILITY_IBSS (1<<1)
#घोषणा WLAN_CAPABILITY_PRIVACY (1<<4)
#घोषणा WLAN_CAPABILITY_SHORT_PREAMBLE (1<<5)
#घोषणा WLAN_CAPABILITY_SHORT_SLOT_TIME (1<<10)

#घोषणा RTLLIB_STATMASK_SIGNAL (1<<0)
#घोषणा RTLLIB_STATMASK_RSSI (1<<1)
#घोषणा RTLLIB_STATMASK_NOISE (1<<2)
#घोषणा RTLLIB_STATMASK_WEMASK 0x7

#घोषणा RTLLIB_CCK_MODULATION    (1<<0)
#घोषणा RTLLIB_OFDM_MODULATION   (1<<1)

#घोषणा RTLLIB_24GHZ_BAND     (1<<0)
#घोषणा RTLLIB_52GHZ_BAND     (1<<1)

#घोषणा RTLLIB_CCK_RATE_LEN		4
#घोषणा RTLLIB_CCK_RATE_1MB			0x02
#घोषणा RTLLIB_CCK_RATE_2MB			0x04
#घोषणा RTLLIB_CCK_RATE_5MB			0x0B
#घोषणा RTLLIB_CCK_RATE_11MB			0x16
#घोषणा RTLLIB_OFDM_RATE_LEN		8
#घोषणा RTLLIB_OFDM_RATE_6MB			0x0C
#घोषणा RTLLIB_OFDM_RATE_9MB			0x12
#घोषणा RTLLIB_OFDM_RATE_12MB		0x18
#घोषणा RTLLIB_OFDM_RATE_18MB		0x24
#घोषणा RTLLIB_OFDM_RATE_24MB		0x30
#घोषणा RTLLIB_OFDM_RATE_36MB		0x48
#घोषणा RTLLIB_OFDM_RATE_48MB		0x60
#घोषणा RTLLIB_OFDM_RATE_54MB		0x6C
#घोषणा RTLLIB_BASIC_RATE_MASK		0x80

/* this is stolen and modअगरied from the madwअगरi driver*/
#घोषणा RTLLIB_FC0_TYPE_MASK		0x0c
#घोषणा RTLLIB_FC0_TYPE_DATA		0x08
#घोषणा RTLLIB_FC0_SUBTYPE_MASK	0xB0
#घोषणा RTLLIB_FC0_SUBTYPE_QOS	0x80

#घोषणा RTLLIB_QOS_HAS_SEQ(fc) \
	(((fc) & (RTLLIB_FC0_TYPE_MASK | RTLLIB_FC0_SUBTYPE_MASK)) == \
	 (RTLLIB_FC0_TYPE_DATA | RTLLIB_FC0_SUBTYPE_QOS))

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
काष्ठा rtllib_rx_stats अणु
	u64 mac_समय;
	s8  rssi;
	u8  संकेत;
	u8  noise;
	u16 rate; /* in 100 kbps */
	u8  received_channel;
	u8  control;
	u8  mask;
	u8  freq;
	u16 len;
	u64 tsf;
	u32 beacon_समय;
	u8  nic_type;
	u16 Length;
	u8  SignalQuality;
	s32 RecvSignalPower;
	s8  RxPower;
	u8  SignalStrength;
	u16 bHwError:1;
	u16 bCRC:1;
	u16 bICV:1;
	u16 bShortPreamble:1;
	u16 Antenna:1;
	u16 Decrypted:1;
	u16 Wakeup:1;
	u16 Reserved0:1;
	u8  AGC;
	u32 TimeStampLow;
	u32 TimeStampHigh;
	bool bShअगरt;
	bool bIsQosData;

	u8    RxDrvInfoSize;
	u8    RxBufShअगरt;
	bool  bIsAMPDU;
	bool  bFirstMPDU;
	bool  bContainHTC;
	bool  RxIs40MHzPacket;
	u32   RxPWDBAll;
	u8    RxMIMOSignalStrength[4];
	s8    RxMIMOSignalQuality[2];
	bool  bPacketMatchBSSID;
	bool  bIsCCK;
	bool  bPacketToSelf;
	u16    packetlength;
	u16    fraglength;
	u16    fragoffset;
	u16    ntotalfrag;
	bool   bPacketBeacon;
	bool   bToSelfBA;
	u16    Seq_Num;
पूर्ण;

/* IEEE 802.11 requires that STA supports concurrent reception of at least
 * three fragmented frames. This define can be increased to support more
 * concurrent frames, but it should be noted that each entry can consume about
 * 2 kB of RAM and increasing cache size will slow करोwn frame reassembly.
 */
#घोषणा RTLLIB_FRAG_CACHE_LEN 4

काष्ठा rtllib_frag_entry अणु
	अचिन्हित दीर्घ first_frag_समय;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक last_frag;
	काष्ठा sk_buff *skb;
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
पूर्ण;

काष्ठा rtllib_device;

#घोषणा SEC_ACTIVE_KEY    (1<<4)
#घोषणा SEC_AUTH_MODE     (1<<5)
#घोषणा SEC_UNICAST_GROUP (1<<6)
#घोषणा SEC_LEVEL	 (1<<7)
#घोषणा SEC_ENABLED       (1<<8)

#घोषणा SEC_LEVEL_0      0 /* None */
#घोषणा SEC_LEVEL_1      1 /* WEP 40 and 104 bit */
#घोषणा SEC_LEVEL_2      2 /* Level 1 + TKIP */
#घोषणा SEC_LEVEL_2_CKIP 3 /* Level 1 + CKIP */
#घोषणा SEC_LEVEL_3      4 /* Level 2 + CCMP */

#घोषणा SEC_ALG_NONE		0
#घोषणा SEC_ALG_WEP		1
#घोषणा SEC_ALG_TKIP		2
#घोषणा SEC_ALG_CCMP		4

#घोषणा WEP_KEY_LEN		13
#घोषणा SCM_KEY_LEN		32

काष्ठा rtllib_security अणु
	u16 active_key:2,
	    enabled:1,
	    auth_mode:2,
	    auth_algo:4,
	    unicast_uses_group:1,
	    encrypt:1;
	u8 key_sizes[NUM_WEP_KEYS];
	u8 keys[NUM_WEP_KEYS][SCM_KEY_LEN];
	u8 level;
	u16 flags;
पूर्ण __packed;


/* 802.11 data frame from AP
 *       ,-------------------------------------------------------------------.
 * Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
 *       |------|------|---------|---------|---------|------|---------|------|
 * Desc. | ctrl | dura |  DA/RA  |   TA    |    SA   | Sequ |  frame  |  fcs |
 *       |      | tion | (BSSID) |         |         | ence |  data   |      |
 *       `-------------------------------------------------------------------'
 * Total: 28-2340 bytes
 */

/* Management Frame Inक्रमmation Element Types */
क्रमागत rtllib_mfie अणु
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
	MFIE_TYPE_HT_CAP = 45,
	MFIE_TYPE_RSN = 48,
	MFIE_TYPE_RATES_EX = 50,
	MFIE_TYPE_HT_INFO = 61,
	MFIE_TYPE_AIRONET = 133,
	MFIE_TYPE_GENERIC = 221,
	MFIE_TYPE_QOS_PARAMETER = 222,
पूर्ण;

/* Minimal header; can be used क्रम passing 802.11 frames with sufficient
 * inक्रमmation to determine what type of underlying data type is actually
 * stored in the data.
 */
काष्ठा rtllib_pspoll_hdr अणु
	__le16 frame_ctl;
	__le16 aid;
	u8 bssid[ETH_ALEN];
	u8 ta[ETH_ALEN];
पूर्ण __packed;

काष्ठा rtllib_hdr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_hdr_1addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_hdr_2addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_hdr_3addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_hdr_4addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 addr4[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_hdr_3addrqos अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	__le16 qos_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_hdr_4addrqos अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 addr4[ETH_ALEN];
	__le16 qos_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtllib_info_element अणु
	u8 id;
	u8 len;
	u8 data[];
पूर्ण __packed;

काष्ठा rtllib_authentication अणु
	काष्ठा rtllib_hdr_3addr header;
	__le16 algorithm;
	__le16 transaction;
	__le16 status;
	/*challenge*/
	काष्ठा rtllib_info_element info_element[];
पूर्ण __packed;

काष्ठा rtllib_disauth अणु
	काष्ठा rtllib_hdr_3addr header;
	__le16 reason;
पूर्ण __packed;

काष्ठा rtllib_disassoc अणु
	काष्ठा rtllib_hdr_3addr header;
	__le16 reason;
पूर्ण __packed;

काष्ठा rtllib_probe_request अणु
	काष्ठा rtllib_hdr_3addr header;
	/* SSID, supported rates */
	काष्ठा rtllib_info_element info_element[];
पूर्ण __packed;

काष्ठा rtllib_probe_response अणु
	काष्ठा rtllib_hdr_3addr header;
	u32 समय_stamp[2];
	__le16 beacon_पूर्णांकerval;
	__le16 capability;
	/* SSID, supported rates, FH params, DS params,
	 * CF params, IBSS params, TIM (अगर beacon), RSN
	 */
	काष्ठा rtllib_info_element info_element[];
पूर्ण __packed;

/* Alias beacon क्रम probe_response */
#घोषणा rtllib_beacon rtllib_probe_response

काष्ठा rtllib_assoc_request_frame अणु
	काष्ठा rtllib_hdr_3addr header;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	/* SSID, supported rates, RSN */
	काष्ठा rtllib_info_element info_element[];
पूर्ण __packed;

काष्ठा rtllib_assoc_response_frame अणु
	काष्ठा rtllib_hdr_3addr header;
	__le16 capability;
	__le16 status;
	__le16 aid;
	काष्ठा rtllib_info_element info_element[]; /* supported rates */
पूर्ण __packed;

काष्ठा rtllib_txb अणु
	u8 nr_frags;
	u8 encrypted;
	u8 queue_index;
	u8 rts_included;
	u16 reserved;
	__le16 frag_size;
	__le16 payload_size;
	काष्ठा sk_buff *fragments[];
पूर्ण;

#घोषणा MAX_SUBFRAME_COUNT		  64
काष्ठा rtllib_rxb अणु
	u8 nr_subframes;
	काष्ठा sk_buff *subframes[MAX_SUBFRAME_COUNT];
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
पूर्ण __packed;

जोड़ frameqos अणु
	u16 लघुdata;
	u8  अक्षरdata[2];
	काष्ठा अणु
		u16 tid:4;
		u16 eosp:1;
		u16 ack_policy:2;
		u16 reserved:1;
		u16 txop:8;
	पूर्ण field;
पूर्ण;

/* MAX_RATES_LENGTH needs to be 12.  The spec says 8, and many APs
 * only use 8, and then use extended rates क्रम the reमुख्यing supported
 * rates.  Other APs, however, stick all of their supported rates on the
 * मुख्य rates inक्रमmation element...
 */
#घोषणा MAX_RATES_LENGTH		  ((u8)12)
#घोषणा MAX_RATES_EX_LENGTH	       ((u8)16)
#घोषणा MAX_NETWORK_COUNT		  96

#घोषणा MAX_CHANNEL_NUMBER		 161
#घोषणा RTLLIB_SOFTMAC_SCAN_TIME	   100
#घोषणा RTLLIB_SOFTMAC_ASSOC_RETRY_TIME (HZ * 2)

#घोषणा MAX_WPA_IE_LEN 64
#घोषणा MAX_WZC_IE_LEN 256

#घोषणा NETWORK_EMPTY_ESSID (1<<0)
#घोषणा NETWORK_HAS_OFDM    (1<<1)
#घोषणा NETWORK_HAS_CCK     (1<<2)

/* QoS काष्ठाure */
#घोषणा NETWORK_HAS_QOS_PARAMETERS      (1<<3)
#घोषणा NETWORK_HAS_QOS_INFORMATION     (1<<4)
#घोषणा NETWORK_HAS_QOS_MASK	    (NETWORK_HAS_QOS_PARAMETERS | \
					 NETWORK_HAS_QOS_INFORMATION)
/* 802.11h */
#घोषणा NETWORK_HAS_ERP_VALUE	   (1<<10)

#घोषणा QOS_QUEUE_NUM		   4
#घोषणा QOS_OUI_LEN		     3
#घोषणा QOS_OUI_TYPE		    2
#घोषणा QOS_ELEMENT_ID		  221
#घोषणा QOS_OUI_INFO_SUB_TYPE	   0
#घोषणा QOS_OUI_PARAM_SUB_TYPE	  1
#घोषणा QOS_VERSION_1		   1

काष्ठा rtllib_qos_inक्रमmation_element अणु
	u8 elementID;
	u8 length;
	u8 qui[QOS_OUI_LEN];
	u8 qui_type;
	u8 qui_subtype;
	u8 version;
	u8 ac_info;
पूर्ण __packed;

काष्ठा rtllib_qos_ac_parameter अणु
	u8 aci_aअगरsn;
	u8 ecw_min_max;
	__le16 tx_op_limit;
पूर्ण __packed;

काष्ठा rtllib_qos_parameter_info अणु
	काष्ठा rtllib_qos_inक्रमmation_element info_element;
	u8 reserved;
	काष्ठा rtllib_qos_ac_parameter ac_params_record[QOS_QUEUE_NUM];
पूर्ण __packed;

काष्ठा rtllib_qos_parameters अणु
	__le16 cw_min[QOS_QUEUE_NUM];
	__le16 cw_max[QOS_QUEUE_NUM];
	u8 aअगरs[QOS_QUEUE_NUM];
	u8 flag[QOS_QUEUE_NUM];
	__le16 tx_op_limit[QOS_QUEUE_NUM];
पूर्ण __packed;

काष्ठा rtllib_qos_data अणु
	काष्ठा rtllib_qos_parameters parameters;
	अचिन्हित पूर्णांक wmm_acm;
	पूर्णांक active;
	पूर्णांक supported;
	u8 param_count;
	u8 old_param_count;
पूर्ण;

काष्ठा rtllib_tim_parameters अणु
	u8 tim_count;
	u8 tim_period;
पूर्ण __packed;

काष्ठा rtllib_wmm_ac_param अणु
	u8 ac_aci_acm_aअगरsn;
	u8 ac_ecwmin_ecwmax;
	u16 ac_txop_limit;
पूर्ण;

क्रमागत eap_type अणु
	EAP_PACKET = 0,
	EAPOL_START,
	EAPOL_LOGOFF,
	EAPOL_KEY,
	EAPOL_ENCAP_ASF_ALERT
पूर्ण;

अटल स्थिर अक्षर * स्थिर eap_types[] = अणु
	[EAP_PACKET]		= "EAP-Packet",
	[EAPOL_START]		= "EAPOL-Start",
	[EAPOL_LOGOFF]		= "EAPOL-Logoff",
	[EAPOL_KEY]		= "EAPOL-Key",
	[EAPOL_ENCAP_ASF_ALERT]	= "EAPOL-Encap-ASF-Alert"
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *eap_get_type(पूर्णांक type)
अणु
	वापस ((u32)type >= ARRAY_SIZE(eap_types)) ? "Unknown" :
		 eap_types[type];
पूर्ण
अटल अंतरभूत u8 Frame_QoSTID(u8 *buf)
अणु
	काष्ठा rtllib_hdr_3addr *hdr;
	u16 fc;

	hdr = (काष्ठा rtllib_hdr_3addr *)buf;
	fc = le16_to_cpu(hdr->frame_ctl);
	वापस (u8)((जोड़ frameqos *)(buf + (((fc & RTLLIB_FCTL_TODS) &&
		    (fc & RTLLIB_FCTL_FROMDS)) ? 30 : 24)))->field.tid;
पूर्ण


काष्ठा eapol अणु
	u8 snap[6];
	u16 ethertype;
	u8 version;
	u8 type;
	u16 length;
पूर्ण __packed;

काष्ठा rtllib_sofपंचांगac_stats अणु
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

/* These are the data types that can make up management packets
 *
 * u16 auth_algorithm;
 * u16 auth_sequence;
 * u16 beacon_पूर्णांकerval;
 * u16 capability;
 * u8 current_ap[ETH_ALEN];
 * u16 listen_पूर्णांकerval;
 * काष्ठा अणु
 *   u16 association_id:14, reserved:2;
 * पूर्ण __packed;
 * u32 समय_stamp[2];
 * u16 reason;
 * u16 status;
 */

#घोषणा RTLLIB_DEFAULT_TX_ESSID "Penguin"
#घोषणा RTLLIB_DEFAULT_BASIC_RATE 2

क्रमागत अणुWMM_all_frame, WMM_two_frame, WMM_four_frame, WMM_six_frameपूर्ण;
#घोषणा MAX_SP_Len  (WMM_all_frame << 4)
#घोषणा RTLLIB_QOS_TID 0x0f
#घोषणा QOS_CTL_NOTCONTAIN_ACK (0x01 << 5)

#घोषणा RTLLIB_DTIM_MBCAST 4
#घोषणा RTLLIB_DTIM_UCAST 2
#घोषणा RTLLIB_DTIM_VALID 1
#घोषणा RTLLIB_DTIM_INVALID 0

#घोषणा RTLLIB_PS_DISABLED 0
#घोषणा RTLLIB_PS_UNICAST RTLLIB_DTIM_UCAST
#घोषणा RTLLIB_PS_MBCAST RTLLIB_DTIM_MBCAST

#घोषणा WME_AC_BK   0x00
#घोषणा WME_AC_BE   0x01
#घोषणा WME_AC_VI   0x02
#घोषणा WME_AC_VO   0x03
#घोषणा WME_AC_PRAM_LEN 16

#घोषणा MAX_RECEIVE_BUFFER_SIZE 9100

#घोषणा UP2AC(up) (		   \
	((up) < 1) ? WME_AC_BE : \
	((up) < 3) ? WME_AC_BK : \
	((up) < 4) ? WME_AC_BE : \
	((up) < 6) ? WME_AC_VI : \
	WME_AC_VO)

#घोषणा	ETHER_ADDR_LEN		6	/* length of an Ethernet address */
#घोषणा ETHERNET_HEADER_SIZE    14      /* length of two Ethernet address
					 * plus ether type
					 */

क्रमागत erp_t अणु
	ERP_NonERPpresent	= 0x01,
	ERP_UseProtection	= 0x02,
	ERP_BarkerPreambleMode = 0x04,
पूर्ण;

काष्ठा rtllib_network अणु
	/* These entries are used to identअगरy a unique network */
	u8 bssid[ETH_ALEN];
	u8 channel;
	/* Ensure null-terminated क्रम any debug msgs */
	u8 ssid[IW_ESSID_MAX_SIZE + 1];
	u8 ssid_len;
	u8 hidden_ssid[IW_ESSID_MAX_SIZE + 1];
	u8 hidden_ssid_len;
	काष्ठा rtllib_qos_data qos_data;

	bool	bWithAironetIE;
	bool	bCkipSupported;
	bool	bCcxRmEnable;
	u8	CcxRmState[2];
	bool	bMBssidValid;
	u8	MBssidMask;
	u8	MBssid[ETH_ALEN];
	bool	bWithCcxVerNum;
	u8	BssCcxVerNumber;
	/* These are network statistics */
	काष्ठा rtllib_rx_stats stats;
	u16 capability;
	u8  rates[MAX_RATES_LENGTH];
	u8  rates_len;
	u8  rates_ex[MAX_RATES_EX_LENGTH];
	u8  rates_ex_len;
	अचिन्हित दीर्घ last_scanned;
	u8  mode;
	u32 flags;
	u32 समय_stamp[2];
	u16 beacon_पूर्णांकerval;
	u16 listen_पूर्णांकerval;
	u16 atim_winकरोw;
	u8  erp_value;
	u8  wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;
	u8  rsn_ie[MAX_WPA_IE_LEN];
	माप_प्रकार rsn_ie_len;
	u8  wzc_ie[MAX_WZC_IE_LEN];
	माप_प्रकार wzc_ie_len;

	काष्ठा rtllib_tim_parameters tim;
	u8  dtim_period;
	u8  dtim_data;
	u64 last_dtim_sta_समय;

	u8 wmm_info;
	काष्ठा rtllib_wmm_ac_param wmm_param[4];
	u8 Turbo_Enable;
	u16 CountryIeLen;
	u8 CountryIeBuf[MAX_IE_LEN];
	काष्ठा bss_ht bssht;
	bool broadcom_cap_exist;
	bool realtek_cap_निकास;
	bool marvell_cap_exist;
	bool ralink_cap_exist;
	bool atheros_cap_exist;
	bool cisco_cap_exist;
	bool airgo_cap_exist;
	bool unknown_cap_exist;
	bool	berp_info_valid;
	bool buseprotection;
	u8 SignalStrength;
	u8 RSSI;
	काष्ठा list_head list;
पूर्ण;

क्रमागत rtllib_state अणु

	/* the card is not linked at all */
	RTLLIB_NOLINK = 0,

	/* RTLLIB_ASSOCIATING* are क्रम BSS client mode
	 * the driver shall not perक्रमm RX filtering unless
	 * the state is LINKED.
	 * The driver shall just check क्रम the state LINKED and
	 * शेषs to NOLINK क्रम ALL the other states (including
	 * LINKED_SCANNING)
	 */

	/* the association procedure will start (wq scheduling)*/
	RTLLIB_ASSOCIATING,
	RTLLIB_ASSOCIATING_RETRY,

	/* the association procedure is sending AUTH request*/
	RTLLIB_ASSOCIATING_AUTHENTICATING,

	/* the association procedure has successfully authenticated
	 * and is sending association request
	 */
	RTLLIB_ASSOCIATING_AUTHENTICATED,

	/* the link is ok. the card associated to a BSS or linked
	 * to a ibss cell or acting as an AP and creating the bss
	 */
	RTLLIB_LINKED,

	/* same as LINKED, but the driver shall apply RX filter
	 * rules as we are in NO_LINK mode. As the card is still
	 * logically linked, but it is करोing a syncro site survey
	 * then it will be back to LINKED state.
	 */
	RTLLIB_LINKED_SCANNING,
पूर्ण;

#घोषणा DEFAULT_MAX_SCAN_AGE (15 * HZ)
#घोषणा DEFAULT_FTS 2346

#घोषणा CFG_RTLLIB_RESERVE_FCS (1<<0)
#घोषणा CFG_RTLLIB_COMPUTE_FCS (1<<1)

काष्ठा tx_pending अणु
	पूर्णांक frag;
	काष्ठा rtllib_txb *txb;
पूर्ण;

काष्ठा bandwidth_स्वतःचयन अणु
	दीर्घ threshold_20Mhzto40Mhz;
	दीर्घ	threshold_40Mhzto20Mhz;
	bool bक्रमced_tx20Mhz;
	bool bस्वतःचयन_enable;
पूर्ण;



#घोषणा REORDER_WIN_SIZE	128
#घोषणा REORDER_ENTRY_NUM	128
काष्ठा rx_reorder_entry अणु
	काष्ठा list_head	List;
	u16			SeqNum;
	काष्ठा rtllib_rxb *prxb;
पूर्ण;
क्रमागत fsync_state अणु
	Default_Fsync,
	HW_Fsync,
	SW_Fsync
पूर्ण;

क्रमागत rt_ps_mode अणु
	eActive,
	eMaxPs,
	eFastPs,
	eAutoPs,
पूर्ण;

क्रमागत ips_callback_function अणु
	IPS_CALLBACK_NONE = 0,
	IPS_CALLBACK_MGNT_LINK_REQUEST = 1,
	IPS_CALLBACK_JOIN_REQUEST = 2,
पूर्ण;

क्रमागत rt_rf_घातer_state अणु
	eRfOn,
	eRfSleep,
	eRfOff
पूर्ण;

काष्ठा rt_pwr_save_ctrl अणु

	bool				bInactivePs;
	bool				bIPSModeBackup;
	bool				bSwRfProcessing;
	क्रमागत rt_rf_घातer_state eInactivePowerState;
	क्रमागत ips_callback_function ReturnPoपूर्णांक;

	bool				bLeisurePs;
	u8				LpsIdleCount;
	u8				RegMaxLPSAwakeIntvl;
	u8				LPSAwakeIntvl;

	u32				CurPsLevel;
	u32				RegRfPsLevel;

	bool				bFwCtrlLPS;

पूर्ण;

#घोषणा RT_RF_CHANGE_SOURCE u32

#घोषणा RF_CHANGE_BY_SW BIT31
#घोषणा RF_CHANGE_BY_HW BIT30
#घोषणा RF_CHANGE_BY_PS BIT29
#घोषणा RF_CHANGE_BY_IPS BIT28
#घोषणा RF_CHANGE_BY_INIT	0

क्रमागत country_code_type अणु
	COUNTRY_CODE_FCC = 0,
	COUNTRY_CODE_IC = 1,
	COUNTRY_CODE_ETSI = 2,
	COUNTRY_CODE_SPAIN = 3,
	COUNTRY_CODE_FRANCE = 4,
	COUNTRY_CODE_MKK = 5,
	COUNTRY_CODE_MKK1 = 6,
	COUNTRY_CODE_ISRAEL = 7,
	COUNTRY_CODE_TELEC = 8,
	COUNTRY_CODE_MIC = 9,
	COUNTRY_CODE_GLOBAL_DOMAIN = 10,
	COUNTRY_CODE_WORLD_WIDE_13 = 11,
	COUNTRY_CODE_TELEC_NETGEAR = 12,
	COUNTRY_CODE_MAX
पूर्ण;

क्रमागत scan_op_backup_opt अणु
	SCAN_OPT_BACKUP = 0,
	SCAN_OPT_RESTORE,
	SCAN_OPT_MAX
पूर्ण;

क्रमागत fw_cmd_io_type अणु
	FW_CMD_DIG_ENABLE = 0,
	FW_CMD_DIG_DISABLE = 1,
	FW_CMD_DIG_HALT = 2,
	FW_CMD_DIG_RESUME = 3,
	FW_CMD_HIGH_PWR_ENABLE = 4,
	FW_CMD_HIGH_PWR_DISABLE = 5,
	FW_CMD_RA_RESET = 6,
	FW_CMD_RA_ACTIVE = 7,
	FW_CMD_RA_REFRESH_N = 8,
	FW_CMD_RA_REFRESH_BG = 9,
	FW_CMD_RA_INIT = 10,
	FW_CMD_IQK_ENABLE = 11,
	FW_CMD_TXPWR_TRACK_ENABLE = 12,
	FW_CMD_TXPWR_TRACK_DISABLE = 13,
	FW_CMD_TXPWR_TRACK_THERMAL = 14,
	FW_CMD_PAUSE_DM_BY_SCAN = 15,
	FW_CMD_RESUME_DM_BY_SCAN = 16,
	FW_CMD_RA_REFRESH_N_COMB = 17,
	FW_CMD_RA_REFRESH_BG_COMB = 18,
	FW_CMD_ANTENNA_SW_ENABLE = 19,
	FW_CMD_ANTENNA_SW_DISABLE = 20,
	FW_CMD_TX_FEEDBACK_CCX_ENABLE = 21,
	FW_CMD_LPS_ENTER = 22,
	FW_CMD_LPS_LEAVE = 23,
पूर्ण;

#घोषणा RT_MAX_LD_SLOT_NUM	10
काष्ठा rt_link_detect अणु

	u32				NumRecvBcnInPeriod;
	u32				NumRecvDataInPeriod;

	u32				RxBcnNum[RT_MAX_LD_SLOT_NUM];
	u32				RxDataNum[RT_MAX_LD_SLOT_NUM];
	u16				SlotNum;
	u16				SlotIndex;

	u32				NumTxOkInPeriod;
	u32				NumRxOkInPeriod;
	u32				NumRxUnicastOkInPeriod;
	bool				bBusyTraffic;
	bool				bHigherBusyTraffic;
	bool				bHigherBusyRxTraffic;
पूर्ण;

काष्ठा sw_cam_table अणु

	u8				macaddr[ETH_ALEN];
	bool				bused;
	u8				key_buf[16];
	u16				key_type;
	u8				useDK;
	u8				key_index;

पूर्ण;
#घोषणा   TOTAL_CAM_ENTRY				32
काष्ठा rate_adaptive अणु
	u8				rate_adaptive_disabled;
	u8				ratr_state;
	u16				reserve;

	u32				high_rssi_thresh_क्रम_ra;
	u32				high2low_rssi_thresh_क्रम_ra;
	u8				low2high_rssi_thresh_क्रम_ra40M;
	u32				low_rssi_thresh_क्रम_ra40M;
	u8				low2high_rssi_thresh_क्रम_ra20M;
	u32				low_rssi_thresh_क्रम_ra20M;
	u32				upper_rssi_threshold_ratr;
	u32				middle_rssi_threshold_ratr;
	u32				low_rssi_threshold_ratr;
	u32				low_rssi_threshold_ratr_40M;
	u32				low_rssi_threshold_ratr_20M;
	u8				ping_rssi_enable;
	u32				ping_rssi_ratr;
	u32				ping_rssi_thresh_क्रम_ra;
	u32				last_ratr;
	u8				PreRATRState;

पूर्ण;

#घोषणा	NUM_PMKID_CACHE		16
काष्ठा rt_pmkid_list अणु
	u8 Bssid[ETH_ALEN];
	u8 PMKID[16];
	u8 SsidBuf[33];
	u8 bUsed;
पूर्ण;

काष्ठा rt_पूर्णांकel_promisc_mode अणु
	bool bPromiscuousOn;
	bool bFilterSourceStationFrame;
पूर्ण;


/*************** DRIVER STATUS   *****/
#घोषणा STATUS_SCANNING			0
/*************** DRIVER STATUS   *****/

क्रमागत अणु
	LPS_IS_WAKE = 0,
	LPS_IS_SLEEP = 1,
	LPS_WAIT_शून्य_DATA_SEND = 2,
पूर्ण;

काष्ठा rtllib_device अणु
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *dev;
	काष्ठा rtllib_security sec;

	bool disable_mgnt_queue;

	अचिन्हित दीर्घ status;
	u8	CntAfterLink;

	क्रमागत rt_op_mode OpMode;

	/* The last AssocReq/Resp IEs */
	u8 *assocreq_ies, *assocresp_ies;
	माप_प्रकार assocreq_ies_len, assocresp_ies_len;

	bool	bForcedBgMode;
	u8 RF_Type;

	u8 hwsec_active;
	bool is_silent_reset;
	bool is_roaming;
	bool ieee_up;
	bool cannot_notअगरy;
	bool bSupportRemoteWakeUp;
	bool actscanning;
	bool FirstIe_InScan;
	bool be_scan_inprogress;
	bool beinretry;
	क्रमागत rt_rf_घातer_state eRFPowerState;
	RT_RF_CHANGE_SOURCE	RfOffReason;
	bool is_set_key;
	bool wx_set_enc;
	काष्ठा rt_hi_throughput *pHTInfo;

	spinlock_t reorder_spinlock;
	u8	Regकरोt11HTOperationalRateSet[16];
	u8	Regकरोt11TxHTOperationalRateSet[16];
	u8	करोt11HTOperationalRateSet[16];
	u8	RegHTSuppRateSet[16];
	u8	HTCurrentOperaRate;
	u8	HTHighestOperaRate;
	u8	bTxDisableRateFallBack;
	u8	bTxUseDriverAssingedRate;
	u8	bTxEnableFwCalcDur;
	atomic_t	aपंचांग_swbw;

	काष्ठा list_head		Tx_TS_Admit_List;
	काष्ठा list_head		Tx_TS_Pending_List;
	काष्ठा list_head		Tx_TS_Unused_List;
	काष्ठा tx_ts_record TxTsRecord[TOTAL_TS_NUM];
	काष्ठा list_head		Rx_TS_Admit_List;
	काष्ठा list_head		Rx_TS_Pending_List;
	काष्ठा list_head		Rx_TS_Unused_List;
	काष्ठा rx_ts_record RxTsRecord[TOTAL_TS_NUM];
	काष्ठा rx_reorder_entry RxReorderEntry[128];
	काष्ठा list_head		RxReorder_Unused_List;


	/* Bookkeeping काष्ठाures */
	काष्ठा net_device_stats stats;
	काष्ठा rtllib_sofपंचांगac_stats sofपंचांगac_stats;

	/* Probe / Beacon management */
	काष्ठा list_head network_मुक्त_list;
	काष्ठा list_head network_list;
	काष्ठा rtllib_network *networks;
	पूर्णांक scans;
	पूर्णांक scan_age;

	पूर्णांक iw_mode; /* operating mode (IW_MODE_*) */
	bool bNetPromiscuousMode;
	काष्ठा rt_पूर्णांकel_promisc_mode IntelPromiscuousModeInfo;

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
	पूर्णांक host_decrypt;

	पूर्णांक ieee802_1x; /* is IEEE 802.1X used */

	/* WPA data */
	bool bHalfWirelessN24GMode;
	पूर्णांक wpa_enabled;
	पूर्णांक drop_unencrypted;
	पूर्णांक tkip_countermeasures;
	पूर्णांक privacy_invoked;
	माप_प्रकार wpa_ie_len;
	u8 *wpa_ie;
	माप_प्रकार wps_ie_len;
	u8 *wps_ie;
	u8 ap_mac_addr[ETH_ALEN];
	u16 pairwise_key_type;
	u16 group_key_type;

	काष्ठा lib80211_crypt_info crypt_info;

	काष्ठा sw_cam_table swcamtable[TOTAL_CAM_ENTRY];

	काष्ठा rt_pmkid_list PMKIDList[NUM_PMKID_CACHE];

	/* Fragmentation काष्ठाures */
	काष्ठा rtllib_frag_entry frag_cache[17][RTLLIB_FRAG_CACHE_LEN];
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
	काष्ठा rtllib_network current_network;

	क्रमागत rtllib_state state;

	पूर्णांक लघु_slot;
	पूर्णांक mode;       /* A, B, G */
	पूर्णांक modulation; /* CCK, OFDM */

	/* used क्रम क्रमcing the ibss workqueue to terminate
	 * without रुको क्रम the syncro scan to terminate
	 */
	लघु sync_scan_hurryup;
	u16 scan_watch_करोg;

	/* map of allowed channels. 0 is dummy */
	व्योम *करोt11d_info;
	bool global_करोमुख्य;
	u8 active_channel_map[MAX_CHANNEL_NUMBER+1];

	u8   bss_start_channel;
	u8   ibss_maxjoin_chal;

	पूर्णांक rate;       /* current rate */
	पूर्णांक basic_rate;

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
	u8 ack_tx_to_ieee;
	लघु ps;
	लघु sta_sleep;
	पूर्णांक ps_समयout;
	पूर्णांक ps_period;
	काष्ठा tasklet_काष्ठा ps_task;
	u64 ps_समय;
	bool polling;

	लघु raw_tx;
	/* used अगर IEEE_SOFTMAC_TX_QUEUE is set */
	लघु queue_stop;
	लघु scanning_जारी;
	लघु proto_started;
	लघु proto_stoppping;

	काष्ठा mutex wx_mutex;
	काष्ठा mutex scan_mutex;
	काष्ठा mutex ips_mutex;

	spinlock_t mgmt_tx_lock;
	spinlock_t beacon_lock;

	लघु beacon_txing;

	लघु wap_set;
	लघु ssid_set;

	/* set on initialization */
	अचिन्हित पूर्णांक wmm_acm;

	/* क्रम discarding duplicated packets in IBSS */
	काष्ठा list_head ibss_mac_hash[IEEE_IBSS_MAC_HASH_SIZE];

	/* क्रम discarding duplicated packets in BSS */
	u16 last_rxseq_num[17]; /* rx seq previous per-tid */
	u16 last_rxfrag_num[17];/* tx frag previous per-tid */
	अचिन्हित दीर्घ last_packet_समय[17];

	/* क्रम PS mode */
	अचिन्हित दीर्घ last_rx_ps_समय;
	bool			bAwakePktSent;
	u8			LPSDelayCnt;

	/* used अगर IEEE_SOFTMAC_SINGLE_QUEUE is set */
	काष्ठा sk_buff *mgmt_queue_ring[MGMT_QUEUE_NUM];
	पूर्णांक mgmt_queue_head;
	पूर्णांक mgmt_queue_tail;
	u8 AsocRetryCount;
	काष्ठा sk_buff_head skb_रुकोQ[MAX_QUEUE_SIZE];
	काष्ठा sk_buff_head  skb_aggQ[MAX_QUEUE_SIZE];

	bool	bdynamic_txघातer_enable;

	bool bCTSToSelfEnable;

	u32	fsync_समय_पूर्णांकerval;
	u32	fsync_rate_biपंचांगap;
	u8	fsync_rssi_threshold;
	bool	bfsync_enable;

	u8	fsync_multiple_समयपूर्णांकerval;
	u32	fsync_firstdअगरf_ratethreshold;
	u32	fsync_seconddअगरf_ratethreshold;
	क्रमागत fsync_state fsync_state;
	bool		bis_any_nonbepkts;
	काष्ठा bandwidth_स्वतःचयन bandwidth_स्वतः_चयन;
	bool FwRWRF;

	काष्ठा rt_link_detect LinkDetectInfo;
	bool bIsAggregateFrame;
	काष्ठा rt_pwr_save_ctrl PowerSaveControl;

	/* used अगर IEEE_SOFTMAC_TX_QUEUE is set */
	काष्ठा tx_pending tx_pending;

	/* used अगर IEEE_SOFTMAC_ASSOCIATE is set */
	काष्ठा समयr_list associate_समयr;

	/* used अगर IEEE_SOFTMAC_BEACONS is set */
	काष्ठा समयr_list beacon_समयr;
	u8 need_sw_enc;
	काष्ठा work_काष्ठा associate_complete_wq;
	काष्ठा work_काष्ठा ips_leave_wq;
	काष्ठा delayed_work associate_procedure_wq;
	काष्ठा delayed_work sofपंचांगac_scan_wq;
	काष्ठा delayed_work associate_retry_wq;
	काष्ठा delayed_work start_ibss_wq;
	काष्ठा delayed_work hw_wakeup_wq;
	काष्ठा delayed_work hw_sleep_wq;
	काष्ठा delayed_work link_change_wq;
	काष्ठा work_काष्ठा wx_sync_scan_wq;

	जोड़ अणु
		काष्ठा rtllib_rxb *RfdArray[REORDER_WIN_SIZE];
		काष्ठा rtllib_rxb *stats_IndicateArray[REORDER_WIN_SIZE];
		काष्ठा rtllib_rxb *prxbIndicateArray[REORDER_WIN_SIZE];
		काष्ठा अणु
			काष्ठा sw_chnl_cmd PreCommonCmd[MAX_PRECMD_CNT];
			काष्ठा sw_chnl_cmd PostCommonCmd[MAX_POSTCMD_CNT];
			काष्ठा sw_chnl_cmd RfDependCmd[MAX_RFDEPENDCMD_CNT];
		पूर्ण;
	पूर्ण;

	/* Callback functions */
	व्योम (*set_security)(काष्ठा net_device *dev,
			     काष्ठा rtllib_security *sec);

	/* Used to TX data frame by using txb काष्ठाs.
	 * this is not used अगर in the sofपंचांगac_features
	 * is set the flag IEEE_SOFTMAC_TX_QUEUE
	 */
	पूर्णांक (*hard_start_xmit)(काष्ठा rtllib_txb *txb,
			       काष्ठा net_device *dev);

	पूर्णांक (*reset_port)(काष्ठा net_device *dev);

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
	 * frames. If the option IEEE_SOFTMAC_SINGLE_QUEUE is also set
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

	/* OK this is complementing to data_poll_hard_stop */
	व्योम (*data_hard_resume)(काष्ठा net_device *dev);

	/* ask to the driver to retune the radio.
	 * This function can sleep. the driver should ensure
	 * the radio has been चयनed beक्रमe वापस.
	 */
	व्योम (*set_chan)(काष्ठा net_device *dev, लघु ch);

	व्योम (*rtllib_start_hw_scan)(काष्ठा net_device *dev);
	व्योम (*rtllib_stop_hw_scan)(काष्ठा net_device *dev);

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
	व्योम (*start_send_beacons)(काष्ठा net_device *dev);
	व्योम (*stop_send_beacons)(काष्ठा net_device *dev);

	/* घातer save mode related */
	व्योम (*sta_wake_up)(काष्ठा net_device *dev);
	व्योम (*enter_sleep_state)(काष्ठा net_device *dev, u64 समय);
	लघु (*ps_is_queue_empty)(काष्ठा net_device *dev);
	पूर्णांक (*handle_beacon)(काष्ठा net_device *dev,
			     काष्ठा rtllib_beacon *beacon,
			     काष्ठा rtllib_network *network);
	पूर्णांक (*handle_assoc_response)(काष्ठा net_device *dev,
				     काष्ठा rtllib_assoc_response_frame *resp,
				     काष्ठा rtllib_network *network);


	/* check whether Tx hw resource available */
	लघु (*check_nic_enough_desc)(काष्ठा net_device *dev, पूर्णांक queue_index);
	व्योम (*SetBWModeHandler)(काष्ठा net_device *dev,
				 क्रमागत ht_channel_width Bandwidth,
				 क्रमागत ht_extchnl_offset Offset);
	bool (*GetNmodeSupportBySecCfg)(काष्ठा net_device *dev);
	व्योम (*SetWirelessMode)(काष्ठा net_device *dev, u8 wireless_mode);
	bool (*GetHalfNmodeSupportByAPsHandler)(काष्ठा net_device *dev);
	u8   (*rtllib_ap_sec_type)(काष्ठा rtllib_device *ieee);
	व्योम (*InitialGainHandler)(काष्ठा net_device *dev, u8 Operation);
	bool (*SetFwCmdHandler)(काष्ठा net_device *dev,
				क्रमागत fw_cmd_io_type FwCmdIO);
	व्योम (*UpdateBeaconInterruptHandler)(काष्ठा net_device *dev,
					     bool start);
	व्योम (*ScanOperationBackupHandler)(काष्ठा net_device *dev,
					   u8 Operation);
	व्योम (*LedControlHandler)(काष्ठा net_device *dev,
				  क्रमागत led_ctl_mode LedAction);
	व्योम (*SetHwRegHandler)(काष्ठा net_device *dev, u8 variable, u8 *val);

	व्योम (*AllowAllDestAddrHandler)(काष्ठा net_device *dev,
					bool bAllowAllDA, bool WriteIntoReg);

	व्योम (*rtllib_ips_leave_wq)(काष्ठा net_device *dev);
	व्योम (*rtllib_ips_leave)(काष्ठा net_device *dev);
	व्योम (*LeisurePSLeave)(काष्ठा net_device *dev);

	/* This must be the last item so that it poपूर्णांकs to the data
	 * allocated beyond this काष्ठाure by alloc_rtllib
	 */
	u8 priv[];
पूर्ण;

#घोषणा IEEE_A	    (1<<0)
#घोषणा IEEE_B	    (1<<1)
#घोषणा IEEE_G	    (1<<2)
#घोषणा IEEE_N_24G		  (1<<4)
#घोषणा	IEEE_N_5G		  (1<<5)
#घोषणा IEEE_MODE_MASK    (IEEE_A|IEEE_B|IEEE_G)

/* Generate a 802.11 header */

/* Uses the channel change callback directly
 * instead of [start/stop] scan callbacks
 */
#घोषणा IEEE_SOFTMAC_SCAN (1<<2)

/* Perक्रमm authentication and association handshake */
#घोषणा IEEE_SOFTMAC_ASSOCIATE (1<<3)

/* Generate probe requests */
#घोषणा IEEE_SOFTMAC_PROBERQ (1<<4)

/* Generate response to probe requests */
#घोषणा IEEE_SOFTMAC_PROBERS (1<<5)

/* The ieee802.11 stack will manage the netअगर queue
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


अटल अंतरभूत व्योम *rtllib_priv(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा rtllib_device *)netdev_priv(dev))->priv;
पूर्ण

अटल अंतरभूत पूर्णांक rtllib_is_empty_essid(स्थिर अक्षर *essid, पूर्णांक essid_len)
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

अटल अंतरभूत पूर्णांक rtllib_get_hdrlen(u16 fc)
अणु
	पूर्णांक hdrlen = RTLLIB_3ADDR_LEN;

	चयन (WLAN_FC_GET_TYPE(fc)) अणु
	हाल RTLLIB_FTYPE_DATA:
		अगर ((fc & RTLLIB_FCTL_FROMDS) && (fc & RTLLIB_FCTL_TODS))
			hdrlen = RTLLIB_4ADDR_LEN; /* Addr4 */
		अगर (RTLLIB_QOS_HAS_SEQ(fc))
			hdrlen += 2; /* QOS ctrl*/
		अवरोध;
	हाल RTLLIB_FTYPE_CTL:
		चयन (WLAN_FC_GET_STYPE(fc)) अणु
		हाल RTLLIB_STYPE_CTS:
		हाल RTLLIB_STYPE_ACK:
			hdrlen = RTLLIB_1ADDR_LEN;
			अवरोध;
		शेष:
			hdrlen = RTLLIB_2ADDR_LEN;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस hdrlen;
पूर्ण

अटल अंतरभूत u8 *rtllib_get_payload(काष्ठा rtllib_hdr *hdr)
अणु
	चयन (rtllib_get_hdrlen(le16_to_cpu(hdr->frame_ctl))) अणु
	हाल RTLLIB_1ADDR_LEN:
		वापस ((काष्ठा rtllib_hdr_1addr *)hdr)->payload;
	हाल RTLLIB_2ADDR_LEN:
		वापस ((काष्ठा rtllib_hdr_2addr *)hdr)->payload;
	हाल RTLLIB_3ADDR_LEN:
		वापस ((काष्ठा rtllib_hdr_3addr *)hdr)->payload;
	हाल RTLLIB_4ADDR_LEN:
		वापस ((काष्ठा rtllib_hdr_4addr *)hdr)->payload;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक rtllib_is_ofdm_rate(u8 rate)
अणु
	चयन (rate & ~RTLLIB_BASIC_RATE_MASK) अणु
	हाल RTLLIB_OFDM_RATE_6MB:
	हाल RTLLIB_OFDM_RATE_9MB:
	हाल RTLLIB_OFDM_RATE_12MB:
	हाल RTLLIB_OFDM_RATE_18MB:
	हाल RTLLIB_OFDM_RATE_24MB:
	हाल RTLLIB_OFDM_RATE_36MB:
	हाल RTLLIB_OFDM_RATE_48MB:
	हाल RTLLIB_OFDM_RATE_54MB:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rtllib_is_cck_rate(u8 rate)
अणु
	चयन (rate & ~RTLLIB_BASIC_RATE_MASK) अणु
	हाल RTLLIB_CCK_RATE_1MB:
	हाल RTLLIB_CCK_RATE_2MB:
	हाल RTLLIB_CCK_RATE_5MB:
	हाल RTLLIB_CCK_RATE_11MB:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


/* rtllib.c */
व्योम मुक्त_rtllib(काष्ठा net_device *dev);
काष्ठा net_device *alloc_rtllib(पूर्णांक माप_priv);

/* rtllib_tx.c */

पूर्णांक rtllib_encrypt_fragment(
	काष्ठा rtllib_device *ieee,
	काष्ठा sk_buff *frag,
	पूर्णांक hdr_len);

पूर्णांक rtllib_xmit(काष्ठा sk_buff *skb,  काष्ठा net_device *dev);
व्योम rtllib_txb_मुक्त(काष्ठा rtllib_txb *txb);

/* rtllib_rx.c */
पूर्णांक rtllib_rx(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
	      काष्ठा rtllib_rx_stats *rx_stats);
व्योम rtllib_rx_probe_rq(काष्ठा rtllib_device *ieee,
			काष्ठा sk_buff *skb);
पूर्णांक rtllib_legal_channel(काष्ठा rtllib_device *rtllib, u8 channel);

/* rtllib_wx.c */
पूर्णांक rtllib_wx_get_scan(काष्ठा rtllib_device *ieee,
		       काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक rtllib_wx_set_encode(काष्ठा rtllib_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक rtllib_wx_get_encode(काष्ठा rtllib_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक rtllib_wx_set_encode_ext(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक rtllib_wx_set_auth(काष्ठा rtllib_device *ieee,
		       काष्ठा iw_request_info *info,
		       काष्ठा iw_param *data, अक्षर *extra);
पूर्णांक rtllib_wx_set_mlme(काष्ठा rtllib_device *ieee,
		       काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक rtllib_wx_set_gen_ie(काष्ठा rtllib_device *ieee, u8 *ie, माप_प्रकार len);

/* rtllib_sofपंचांगac.c */
पूर्णांक rtllib_rx_frame_sofपंचांगac(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			    काष्ठा rtllib_rx_stats *rx_stats, u16 type,
			    u16 stype);
व्योम rtllib_sofपंचांगac_new_net(काष्ठा rtllib_device *ieee,
			    काष्ठा rtllib_network *net);

व्योम SendDisassociation(काष्ठा rtllib_device *ieee, bool deauth, u16 asRsn);
व्योम rtllib_sofपंचांगac_xmit(काष्ठा rtllib_txb *txb, काष्ठा rtllib_device *ieee);

व्योम rtllib_stop_send_beacons(काष्ठा rtllib_device *ieee);
व्योम notअगरy_wx_assoc_event(काष्ठा rtllib_device *ieee);
व्योम rtllib_start_ibss(काष्ठा rtllib_device *ieee);
व्योम rtllib_sofपंचांगac_init(काष्ठा rtllib_device *ieee);
व्योम rtllib_sofपंचांगac_मुक्त(काष्ठा rtllib_device *ieee);
व्योम rtllib_disassociate(काष्ठा rtllib_device *ieee);
व्योम rtllib_stop_scan(काष्ठा rtllib_device *ieee);
bool rtllib_act_scanning(काष्ठा rtllib_device *ieee, bool sync_scan);
व्योम rtllib_stop_scan_syncro(काष्ठा rtllib_device *ieee);
व्योम rtllib_start_scan_syncro(काष्ठा rtllib_device *ieee, u8 is_mesh);
व्योम rtllib_sta_ps_send_null_frame(काष्ठा rtllib_device *ieee, लघु pwr);
व्योम rtllib_sta_ps_send_pspoll_frame(काष्ठा rtllib_device *ieee);
व्योम rtllib_start_protocol(काष्ठा rtllib_device *ieee);
व्योम rtllib_stop_protocol(काष्ठा rtllib_device *ieee, u8 shutकरोwn);

व्योम rtllib_EnableNetMonitorMode(काष्ठा net_device *dev, bool bInitState);
व्योम rtllib_DisableNetMonitorMode(काष्ठा net_device *dev, bool bInitState);
व्योम rtllib_EnableIntelPromiscuousMode(काष्ठा net_device *dev, bool bInitState);
व्योम rtllib_DisableIntelPromiscuousMode(काष्ठा net_device *dev,
					bool bInitState);
व्योम rtllib_sofपंचांगac_stop_protocol(काष्ठा rtllib_device *ieee,
				  u8 mesh_flag, u8 shutकरोwn);
व्योम rtllib_sofपंचांगac_start_protocol(काष्ठा rtllib_device *ieee, u8 mesh_flag);

व्योम rtllib_reset_queue(काष्ठा rtllib_device *ieee);
व्योम rtllib_wake_all_queues(काष्ठा rtllib_device *ieee);
व्योम rtllib_stop_all_queues(काष्ठा rtllib_device *ieee);
काष्ठा sk_buff *rtllib_get_beacon(काष्ठा rtllib_device *ieee);
व्योम rtllib_start_send_beacons(काष्ठा rtllib_device *ieee);
व्योम rtllib_stop_send_beacons(काष्ठा rtllib_device *ieee);

व्योम notअगरy_wx_assoc_event(काष्ठा rtllib_device *ieee);
व्योम rtllib_ps_tx_ack(काष्ठा rtllib_device *ieee, लघु success);

व्योम sofपंचांगac_mgmt_xmit(काष्ठा sk_buff *skb, काष्ठा rtllib_device *ieee);
u8 rtllib_ap_sec_type(काष्ठा rtllib_device *ieee);

/* rtllib_sofपंचांगac_wx.c */

पूर्णांक rtllib_wx_get_wap(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		      जोड़ iwreq_data *wrqu, अक्षर *ext);

पूर्णांक rtllib_wx_set_wap(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		      जोड़ iwreq_data *awrq, अक्षर *extra);

पूर्णांक rtllib_wx_get_essid(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
			जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक rtllib_wx_set_rate(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_get_rate(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_set_mode(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
		       जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक rtllib_wx_set_scan(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
		       जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक rtllib_wx_set_essid(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
			जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_get_mode(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
		       जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक rtllib_wx_set_freq(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
		       जोड़ iwreq_data *wrqu, अक्षर *b);

पूर्णांक rtllib_wx_get_freq(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
		       जोड़ iwreq_data *wrqu, अक्षर *b);
व्योम rtllib_wx_sync_scan_wq(व्योम *data);

पूर्णांक rtllib_wx_set_rawtx(काष्ठा rtllib_device *ieee,
			काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_get_name(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_set_घातer(काष्ठा rtllib_device *ieee,
			काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_get_घातer(काष्ठा rtllib_device *ieee,
			काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_set_rts(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		      जोड़ iwreq_data *wrqu, अक्षर *extra);

पूर्णांक rtllib_wx_get_rts(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *info,
		      जोड़ iwreq_data *wrqu, अक्षर *extra);
#घोषणा MAX_RECEIVE_BUFFER_SIZE 9100

व्योम HTSetConnectBwMode(काष्ठा rtllib_device *ieee,
			क्रमागत ht_channel_width Bandwidth,
			क्रमागत ht_extchnl_offset Offset);
व्योम HTUpdateDefaultSetting(काष्ठा rtllib_device *ieee);
व्योम HTConकाष्ठाCapabilityElement(काष्ठा rtllib_device *ieee,
				  u8 *posHTCap, u8 *len,
				  u8 isEncrypt, bool bAssoc);
व्योम HTConकाष्ठाInfoElement(काष्ठा rtllib_device *ieee,
			    u8 *posHTInfo, u8 *len, u8 isEncrypt);
व्योम HTConकाष्ठाRT2RTAggElement(काष्ठा rtllib_device *ieee,
				u8 *posRT2RTAgg, u8 *len);
व्योम HTOnAssocRsp(काष्ठा rtllib_device *ieee);
व्योम HTInitializeHTInfo(काष्ठा rtllib_device *ieee);
व्योम HTInitializeBssDesc(काष्ठा bss_ht *pBssHT);
व्योम HTResetSelfAndSavePeerSetting(काष्ठा rtllib_device *ieee,
				   काष्ठा rtllib_network *pNetwork);
व्योम HT_update_self_and_peer_setting(काष्ठा rtllib_device *ieee,
				     काष्ठा rtllib_network *pNetwork);
u8 HTGetHighestMCSRate(काष्ठा rtllib_device *ieee, u8 *pMCSRateSet,
		       u8 *pMCSFilter);
बाह्य u8 MCS_FILTER_ALL[];
बाह्य u16 MCS_DATA_RATE[2][2][77];
u8 HTCCheck(काष्ठा rtllib_device *ieee, u8 *pFrame);
व्योम HTResetIOTSetting(काष्ठा rt_hi_throughput *pHTInfo);
bool IsHTHalfNmodeAPs(काष्ठा rtllib_device *ieee);
u16  TxCountToDataRate(काष्ठा rtllib_device *ieee, u8 nDataRate);
पूर्णांक rtllib_rx_ADDBAReq(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb);
पूर्णांक rtllib_rx_ADDBARsp(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb);
पूर्णांक rtllib_rx_DELBA(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb);
व्योम TsInitAddBA(काष्ठा rtllib_device *ieee, काष्ठा tx_ts_record *pTS,
		 u8 Policy, u8 bOverग_लिखोPending);
व्योम TsInitDelBA(काष्ठा rtllib_device *ieee,
		 काष्ठा ts_common_info *pTsCommonInfo,
		 क्रमागत tr_select TxRxSelect);
व्योम BaSetupTimeOut(काष्ठा समयr_list *t);
व्योम TxBaInactTimeout(काष्ठा समयr_list *t);
व्योम RxBaInactTimeout(काष्ठा समयr_list *t);
व्योम ResetBaEntry(काष्ठा ba_record *pBA);
bool GetTs(काष्ठा rtllib_device *ieee, काष्ठा ts_common_info **ppTS, u8 *Addr,
	   u8 TID, क्रमागत tr_select TxRxSelect, bool bAddNewTs);
व्योम TSInitialize(काष्ठा rtllib_device *ieee);
व्योम TsStartAddBaProcess(काष्ठा rtllib_device *ieee,
			 काष्ठा tx_ts_record *pTxTS);
व्योम RemovePeerTS(काष्ठा rtllib_device *ieee, u8 *Addr);
व्योम RemoveAllTS(काष्ठा rtllib_device *ieee);

बाह्य स्थिर दीर्घ rtllib_wlan_frequencies[];

अटल अंतरभूत स्थिर अक्षर *escape_essid(स्थिर अक्षर *essid, u8 essid_len)
अणु
	अटल अक्षर escaped[IW_ESSID_MAX_SIZE * 2 + 1];

	अगर (rtllib_is_empty_essid(essid, essid_len)) अणु
		स_नकल(escaped, "<hidden>", माप("<hidden>"));
		वापस escaped;
	पूर्ण

	snम_लिखो(escaped, माप(escaped), "%*pE", essid_len, essid);
	वापस escaped;
पूर्ण

/* fun with the built-in rtllib stack... */
bool rtllib_MgntDisconnect(काष्ठा rtllib_device *rtllib, u8 asRsn);


/* For the function is more related to hardware setting, it's better to use the
 * ieee handler to refer to it.
 */
व्योम rtllib_FlushRxTsPendingPkts(काष्ठा rtllib_device *ieee,
				 काष्ठा rx_ts_record *pTS);
पूर्णांक rtllib_parse_info_param(काष्ठा rtllib_device *ieee,
			    काष्ठा rtllib_info_element *info_element,
			    u16 length,
			    काष्ठा rtllib_network *network,
			    काष्ठा rtllib_rx_stats *stats);

व्योम rtllib_indicate_packets(काष्ठा rtllib_device *ieee,
			     काष्ठा rtllib_rxb **prxbIndicateArray, u8  index);
व्योम HTUseDefaultSetting(काष्ठा rtllib_device *ieee);
#घोषणा RT_ASOC_RETRY_LIMIT	5
u8 MgntQuery_TxRateExcludeCCKRates(काष्ठा rtllib_device *ieee);

#पूर्ण_अगर /* RTLLIB_H */
