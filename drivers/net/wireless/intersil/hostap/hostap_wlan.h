<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित HOSTAP_WLAN_H
#घोषणा HOSTAP_WLAN_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <net/iw_handler.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/lib80211.h>

#समावेश "hostap_config.h"
#समावेश "hostap_common.h"

#घोषणा MAX_PARM_DEVICES 8
#घोषणा PARM_MIN_MAX "1-" __MODULE_STRING(MAX_PARM_DEVICES)
#घोषणा DEF_INTS -1, -1, -1, -1, -1, -1, -1
#घोषणा GET_INT_PARM(var,idx) var[var[idx] < 0 ? 0 : idx]


/* Specअगरic skb->protocol value that indicates that the packet alपढ़ोy contains
 * txdesc header.
 * FIX: This might need own value that would be allocated especially क्रम Prism2
 * txdesc; ETH_P_CONTROL is commented as "Card specific control frames".
 * However, these skb's should have only minimal path in the kernel side since
 * prism2_send_mgmt() sends these with dev_queue_xmit() to prism2_tx(). */
#घोषणा ETH_P_HOSTAP ETH_P_CONTROL

/* ARPHRD_IEEE80211_PRISM uses a bloated version of Prism2 RX frame header
 * (from linux-wlan-ng) */
काष्ठा linux_wlan_ng_val अणु
	u32 did;
	u16 status, len;
	u32 data;
पूर्ण __packed;

काष्ठा linux_wlan_ng_prism_hdr अणु
	u32 msgcode, msglen;
	अक्षर devname[16];
	काष्ठा linux_wlan_ng_val hostसमय, maस_समय, channel, rssi, sq, संकेत,
		noise, rate, istx, frmlen;
पूर्ण __packed;

काष्ठा linux_wlan_ng_cap_hdr अणु
	__be32 version;
	__be32 length;
	__be64 maस_समय;
	__be64 hostसमय;
	__be32 phytype;
	__be32 channel;
	__be32 datarate;
	__be32 antenna;
	__be32 priority;
	__be32 ssi_type;
	__be32 ssi_संकेत;
	__be32 ssi_noise;
	__be32 preamble;
	__be32 encoding;
पूर्ण __packed;

काष्ठा hostap_radiotap_rx अणु
	काष्ठा ieee80211_radiotap_header hdr;
	__le64 tsft;
	u8 rate;
	u8 padding;
	__le16 chan_freq;
	__le16 chan_flags;
	s8 dbm_antसंकेत;
	s8 dbm_antnoise;
पूर्ण __packed;

#घोषणा LWNG_CAP_DID_BASE   (4 | (1 << 6)) /* section 4, group 1 */
#घोषणा LWNG_CAPHDR_VERSION 0x80211001

काष्ठा hfa384x_rx_frame अणु
	/* HFA384X RX frame descriptor */
	__le16 status; /* HFA384X_RX_STATUS_ flags */
	__le32 समय; /* बारtamp, 1 microsecond resolution */
	u8 silence; /* 27 .. 154; seems to be 0 */
	u8 संकेत; /* 27 .. 154 */
	u8 rate; /* 10, 20, 55, or 110 */
	u8 rxflow;
	__le32 reserved;

	/* 802.11 */
	__le16 frame_control;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctrl;
	u8 addr4[ETH_ALEN];
	__le16 data_len;

	/* 802.3 */
	u8 dst_addr[ETH_ALEN];
	u8 src_addr[ETH_ALEN];
	__be16 len;

	/* followed by frame data; max 2304 bytes */
पूर्ण __packed;


काष्ठा hfa384x_tx_frame अणु
	/* HFA384X TX frame descriptor */
	__le16 status; /* HFA384X_TX_STATUS_ flags */
	__le16 reserved1;
	__le16 reserved2;
	__le32 sw_support;
	u8 retry_count; /* not yet implemented */
	u8 tx_rate; /* Host AP only; 0 = firmware, or 10, 20, 55, 110 */
	__le16 tx_control; /* HFA384X_TX_CTRL_ flags */

	/* 802.11 */
	__le16 frame_control; /* parts not used */
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN]; /* filled by firmware */
	u8 addr3[ETH_ALEN];
	__le16 seq_ctrl; /* filled by firmware */
	u8 addr4[ETH_ALEN];
	__le16 data_len;

	/* 802.3 */
	u8 dst_addr[ETH_ALEN];
	u8 src_addr[ETH_ALEN];
	__be16 len;

	/* followed by frame data; max 2304 bytes */
पूर्ण __packed;


काष्ठा hfa384x_rid_hdr
अणु
	__le16 len;
	__le16 rid;
पूर्ण __packed;


/* Macro क्रम converting संकेत levels (range 27 .. 154) to wireless ext
 * dBm value with some accuracy */
#घोषणा HFA384X_LEVEL_TO_dBm(v) 0x100 + (v) * 100 / 255 - 100

#घोषणा HFA384X_LEVEL_TO_dBm_sign(v) (v) * 100 / 255 - 100

काष्ठा hfa384x_scan_request अणु
	__le16 channel_list;
	__le16 txrate; /* HFA384X_RATES_* */
पूर्ण __packed;

काष्ठा hfa384x_hostscan_request अणु
	__le16 channel_list;
	__le16 txrate;
	__le16 target_ssid_len;
	u8 target_ssid[32];
पूर्ण __packed;

काष्ठा hfa384x_join_request अणु
	u8 bssid[ETH_ALEN];
	__le16 channel;
पूर्ण __packed;

काष्ठा hfa384x_info_frame अणु
	__le16 len;
	__le16 type;
पूर्ण __packed;

काष्ठा hfa384x_comm_tallies अणु
	__le16 tx_unicast_frames;
	__le16 tx_multicast_frames;
	__le16 tx_fragments;
	__le16 tx_unicast_octets;
	__le16 tx_multicast_octets;
	__le16 tx_deferred_transmissions;
	__le16 tx_single_retry_frames;
	__le16 tx_multiple_retry_frames;
	__le16 tx_retry_limit_exceeded;
	__le16 tx_discards;
	__le16 rx_unicast_frames;
	__le16 rx_multicast_frames;
	__le16 rx_fragments;
	__le16 rx_unicast_octets;
	__le16 rx_multicast_octets;
	__le16 rx_fcs_errors;
	__le16 rx_discards_no_buffer;
	__le16 tx_discards_wrong_sa;
	__le16 rx_discards_wep_undecryptable;
	__le16 rx_message_in_msg_fragments;
	__le16 rx_message_in_bad_msg_fragments;
पूर्ण __packed;

काष्ठा hfa384x_comm_tallies32 अणु
	__le32 tx_unicast_frames;
	__le32 tx_multicast_frames;
	__le32 tx_fragments;
	__le32 tx_unicast_octets;
	__le32 tx_multicast_octets;
	__le32 tx_deferred_transmissions;
	__le32 tx_single_retry_frames;
	__le32 tx_multiple_retry_frames;
	__le32 tx_retry_limit_exceeded;
	__le32 tx_discards;
	__le32 rx_unicast_frames;
	__le32 rx_multicast_frames;
	__le32 rx_fragments;
	__le32 rx_unicast_octets;
	__le32 rx_multicast_octets;
	__le32 rx_fcs_errors;
	__le32 rx_discards_no_buffer;
	__le32 tx_discards_wrong_sa;
	__le32 rx_discards_wep_undecryptable;
	__le32 rx_message_in_msg_fragments;
	__le32 rx_message_in_bad_msg_fragments;
पूर्ण __packed;

काष्ठा hfa384x_scan_result_hdr अणु
	__le16 reserved;
	__le16 scan_reason;
#घोषणा HFA384X_SCAN_IN_PROGRESS 0 /* no results available yet */
#घोषणा HFA384X_SCAN_HOST_INITIATED 1
#घोषणा HFA384X_SCAN_FIRMWARE_INITIATED 2
#घोषणा HFA384X_SCAN_INQUIRY_FROM_HOST 3
पूर्ण __packed;

#घोषणा HFA384X_SCAN_MAX_RESULTS 32

काष्ठा hfa384x_scan_result अणु
	__le16 chid;
	__le16 anl;
	__le16 sl;
	u8 bssid[ETH_ALEN];
	__le16 beacon_पूर्णांकerval;
	__le16 capability;
	__le16 ssid_len;
	u8 ssid[32];
	u8 sup_rates[10];
	__le16 rate;
पूर्ण __packed;

काष्ठा hfa384x_hostscan_result अणु
	__le16 chid;
	__le16 anl;
	__le16 sl;
	u8 bssid[ETH_ALEN];
	__le16 beacon_पूर्णांकerval;
	__le16 capability;
	__le16 ssid_len;
	u8 ssid[32];
	u8 sup_rates[10];
	__le16 rate;
	__le16 atim;
पूर्ण __packed;

काष्ठा comm_tallies_sums अणु
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
	अचिन्हित पूर्णांक rx_discards_wep_undecryptable;
	अचिन्हित पूर्णांक rx_message_in_msg_fragments;
	अचिन्हित पूर्णांक rx_message_in_bad_msg_fragments;
पूर्ण;


काष्ठा hfa384x_regs अणु
	u16 cmd;
	u16 evstat;
	u16 offset0;
	u16 offset1;
	u16 swsupport0;
पूर्ण;


#अगर defined(PRISM2_PCCARD) || defined(PRISM2_PLX)
/* I/O ports क्रम HFA384X Controller access */
#घोषणा HFA384X_CMD_OFF 0x00
#घोषणा HFA384X_PARAM0_OFF 0x02
#घोषणा HFA384X_PARAM1_OFF 0x04
#घोषणा HFA384X_PARAM2_OFF 0x06
#घोषणा HFA384X_STATUS_OFF 0x08
#घोषणा HFA384X_RESP0_OFF 0x0A
#घोषणा HFA384X_RESP1_OFF 0x0C
#घोषणा HFA384X_RESP2_OFF 0x0E
#घोषणा HFA384X_INFOFID_OFF 0x10
#घोषणा HFA384X_CONTROL_OFF 0x14
#घोषणा HFA384X_SELECT0_OFF 0x18
#घोषणा HFA384X_SELECT1_OFF 0x1A
#घोषणा HFA384X_OFFSET0_OFF 0x1C
#घोषणा HFA384X_OFFSET1_OFF 0x1E
#घोषणा HFA384X_RXFID_OFF 0x20
#घोषणा HFA384X_ALLOCFID_OFF 0x22
#घोषणा HFA384X_TXCOMPLFID_OFF 0x24
#घोषणा HFA384X_SWSUPPORT0_OFF 0x28
#घोषणा HFA384X_SWSUPPORT1_OFF 0x2A
#घोषणा HFA384X_SWSUPPORT2_OFF 0x2C
#घोषणा HFA384X_EVSTAT_OFF 0x30
#घोषणा HFA384X_INTEN_OFF 0x32
#घोषणा HFA384X_EVACK_OFF 0x34
#घोषणा HFA384X_DATA0_OFF 0x36
#घोषणा HFA384X_DATA1_OFF 0x38
#घोषणा HFA384X_AUXPAGE_OFF 0x3A
#घोषणा HFA384X_AUXOFFSET_OFF 0x3C
#घोषणा HFA384X_AUXDATA_OFF 0x3E
#पूर्ण_अगर /* PRISM2_PCCARD || PRISM2_PLX */

#अगर_घोषित PRISM2_PCI
/* Memory addresses क्रम ISL3874 controller access */
#घोषणा HFA384X_CMD_OFF 0x00
#घोषणा HFA384X_PARAM0_OFF 0x04
#घोषणा HFA384X_PARAM1_OFF 0x08
#घोषणा HFA384X_PARAM2_OFF 0x0C
#घोषणा HFA384X_STATUS_OFF 0x10
#घोषणा HFA384X_RESP0_OFF 0x14
#घोषणा HFA384X_RESP1_OFF 0x18
#घोषणा HFA384X_RESP2_OFF 0x1C
#घोषणा HFA384X_INFOFID_OFF 0x20
#घोषणा HFA384X_CONTROL_OFF 0x28
#घोषणा HFA384X_SELECT0_OFF 0x30
#घोषणा HFA384X_SELECT1_OFF 0x34
#घोषणा HFA384X_OFFSET0_OFF 0x38
#घोषणा HFA384X_OFFSET1_OFF 0x3C
#घोषणा HFA384X_RXFID_OFF 0x40
#घोषणा HFA384X_ALLOCFID_OFF 0x44
#घोषणा HFA384X_TXCOMPLFID_OFF 0x48
#घोषणा HFA384X_PCICOR_OFF 0x4C
#घोषणा HFA384X_SWSUPPORT0_OFF 0x50
#घोषणा HFA384X_SWSUPPORT1_OFF 0x54
#घोषणा HFA384X_SWSUPPORT2_OFF 0x58
#घोषणा HFA384X_PCIHCR_OFF 0x5C
#घोषणा HFA384X_EVSTAT_OFF 0x60
#घोषणा HFA384X_INTEN_OFF 0x64
#घोषणा HFA384X_EVACK_OFF 0x68
#घोषणा HFA384X_DATA0_OFF 0x6C
#घोषणा HFA384X_DATA1_OFF 0x70
#घोषणा HFA384X_AUXPAGE_OFF 0x74
#घोषणा HFA384X_AUXOFFSET_OFF 0x78
#घोषणा HFA384X_AUXDATA_OFF 0x7C
#घोषणा HFA384X_PCI_M0_ADDRH_OFF 0x80
#घोषणा HFA384X_PCI_M0_ADDRL_OFF 0x84
#घोषणा HFA384X_PCI_M0_LEN_OFF 0x88
#घोषणा HFA384X_PCI_M0_CTL_OFF 0x8C
#घोषणा HFA384X_PCI_STATUS_OFF 0x98
#घोषणा HFA384X_PCI_M1_ADDRH_OFF 0xA0
#घोषणा HFA384X_PCI_M1_ADDRL_OFF 0xA4
#घोषणा HFA384X_PCI_M1_LEN_OFF 0xA8
#घोषणा HFA384X_PCI_M1_CTL_OFF 0xAC

/* PCI bus master control bits (these are unकरोcumented; based on guessing and
 * experimenting..) */
#घोषणा HFA384X_PCI_CTL_FROM_BAP (BIT(5) | BIT(1) | BIT(0))
#घोषणा HFA384X_PCI_CTL_TO_BAP (BIT(5) | BIT(0))

#पूर्ण_अगर /* PRISM2_PCI */


/* Command codes क्रम CMD reg. */
#घोषणा HFA384X_CMDCODE_INIT 0x00
#घोषणा HFA384X_CMDCODE_ENABLE 0x01
#घोषणा HFA384X_CMDCODE_DISABLE 0x02
#घोषणा HFA384X_CMDCODE_ALLOC 0x0A
#घोषणा HFA384X_CMDCODE_TRANSMIT 0x0B
#घोषणा HFA384X_CMDCODE_INQUIRE 0x11
#घोषणा HFA384X_CMDCODE_ACCESS 0x21
#घोषणा HFA384X_CMDCODE_ACCESS_WRITE (0x21 | BIT(8))
#घोषणा HFA384X_CMDCODE_DOWNLOAD 0x22
#घोषणा HFA384X_CMDCODE_READMIF 0x30
#घोषणा HFA384X_CMDCODE_WRITEMIF 0x31
#घोषणा HFA384X_CMDCODE_TEST 0x38

#घोषणा HFA384X_CMDCODE_MASK 0x3F

/* Test mode operations */
#घोषणा HFA384X_TEST_CHANGE_CHANNEL 0x08
#घोषणा HFA384X_TEST_MONITOR 0x0B
#घोषणा HFA384X_TEST_STOP 0x0F
#घोषणा HFA384X_TEST_CFG_BITS 0x15
#घोषणा HFA384X_TEST_CFG_BIT_ALC BIT(3)

#घोषणा HFA384X_CMD_BUSY BIT(15)

#घोषणा HFA384X_CMD_TX_RECLAIM BIT(8)

#घोषणा HFA384X_OFFSET_ERR BIT(14)
#घोषणा HFA384X_OFFSET_BUSY BIT(15)


/* ProgMode क्रम करोwnload command */
#घोषणा HFA384X_PROGMODE_DISABLE 0
#घोषणा HFA384X_PROGMODE_ENABLE_VOLATILE 1
#घोषणा HFA384X_PROGMODE_ENABLE_NON_VOLATILE 2
#घोषणा HFA384X_PROGMODE_PROGRAM_NON_VOLATILE 3

#घोषणा HFA384X_AUX_MAGIC0 0xfe01
#घोषणा HFA384X_AUX_MAGIC1 0xdc23
#घोषणा HFA384X_AUX_MAGIC2 0xba45

#घोषणा HFA384X_AUX_PORT_DISABLED 0
#घोषणा HFA384X_AUX_PORT_DISABLE BIT(14)
#घोषणा HFA384X_AUX_PORT_ENABLE BIT(15)
#घोषणा HFA384X_AUX_PORT_ENABLED (BIT(14) | BIT(15))
#घोषणा HFA384X_AUX_PORT_MASK (BIT(14) | BIT(15))

#घोषणा PRISM2_PDA_SIZE 1024


/* Events; EvStat, Interrupt mask (IntEn), and acknowledge bits (EvAck) */
#घोषणा HFA384X_EV_TICK BIT(15)
#घोषणा HFA384X_EV_WTERR BIT(14)
#घोषणा HFA384X_EV_INFDROP BIT(13)
#अगर_घोषित PRISM2_PCI
#घोषणा HFA384X_EV_PCI_M1 BIT(9)
#घोषणा HFA384X_EV_PCI_M0 BIT(8)
#पूर्ण_अगर /* PRISM2_PCI */
#घोषणा HFA384X_EV_INFO BIT(7)
#घोषणा HFA384X_EV_DTIM BIT(5)
#घोषणा HFA384X_EV_CMD BIT(4)
#घोषणा HFA384X_EV_ALLOC BIT(3)
#घोषणा HFA384X_EV_TXEXC BIT(2)
#घोषणा HFA384X_EV_TX BIT(1)
#घोषणा HFA384X_EV_RX BIT(0)


/* HFA384X Inक्रमmation frames */
#घोषणा HFA384X_INFO_HANDOVERADDR 0xF000 /* AP f/w ? */
#घोषणा HFA384X_INFO_HANDOVERDEAUTHADDR 0xF001 /* AP f/w 1.3.7 */
#घोषणा HFA384X_INFO_COMMTALLIES 0xF100
#घोषणा HFA384X_INFO_SCANRESULTS 0xF101
#घोषणा HFA384X_INFO_CHANNELINFORESULTS 0xF102 /* AP f/w only */
#घोषणा HFA384X_INFO_HOSTSCANRESULTS 0xF103
#घोषणा HFA384X_INFO_LINKSTATUS 0xF200
#घोषणा HFA384X_INFO_ASSOCSTATUS 0xF201 /* ? */
#घोषणा HFA384X_INFO_AUTHREQ 0xF202 /* ? */
#घोषणा HFA384X_INFO_PSUSERCNT 0xF203 /* ? */
#घोषणा HFA384X_INFO_KEYIDCHANGED 0xF204 /* ? */

क्रमागत अणु HFA384X_LINKSTATUS_CONNECTED = 1,
       HFA384X_LINKSTATUS_DISCONNECTED = 2,
       HFA384X_LINKSTATUS_AP_CHANGE = 3,
       HFA384X_LINKSTATUS_AP_OUT_OF_RANGE = 4,
       HFA384X_LINKSTATUS_AP_IN_RANGE = 5,
       HFA384X_LINKSTATUS_ASSOC_FAILED = 6 पूर्ण;

क्रमागत अणु HFA384X_PORTTYPE_BSS = 1, HFA384X_PORTTYPE_WDS = 2,
       HFA384X_PORTTYPE_PSEUDO_IBSS = 3, HFA384X_PORTTYPE_IBSS = 0,
       HFA384X_PORTTYPE_HOSTAP = 6 पूर्ण;

#घोषणा HFA384X_RATES_1MBPS BIT(0)
#घोषणा HFA384X_RATES_2MBPS BIT(1)
#घोषणा HFA384X_RATES_5MBPS BIT(2)
#घोषणा HFA384X_RATES_11MBPS BIT(3)

#घोषणा HFA384X_ROAMING_FIRMWARE 1
#घोषणा HFA384X_ROAMING_HOST 2
#घोषणा HFA384X_ROAMING_DISABLED 3

#घोषणा HFA384X_WEPFLAGS_PRIVACYINVOKED BIT(0)
#घोषणा HFA384X_WEPFLAGS_EXCLUDEUNENCRYPTED BIT(1)
#घोषणा HFA384X_WEPFLAGS_HOSTENCRYPT BIT(4)
#घोषणा HFA384X_WEPFLAGS_HOSTDECRYPT BIT(7)

#घोषणा HFA384X_RX_STATUS_MSGTYPE (BIT(15) | BIT(14) | BIT(13))
#घोषणा HFA384X_RX_STATUS_PCF BIT(12)
#घोषणा HFA384X_RX_STATUS_MACPORT (BIT(10) | BIT(9) | BIT(8))
#घोषणा HFA384X_RX_STATUS_UNDECR BIT(1)
#घोषणा HFA384X_RX_STATUS_FCSERR BIT(0)

#घोषणा HFA384X_RX_STATUS_GET_MSGTYPE(s) \
(((s) & HFA384X_RX_STATUS_MSGTYPE) >> 13)
#घोषणा HFA384X_RX_STATUS_GET_MACPORT(s) \
(((s) & HFA384X_RX_STATUS_MACPORT) >> 8)

क्रमागत अणु HFA384X_RX_MSGTYPE_NORMAL = 0, HFA384X_RX_MSGTYPE_RFC1042 = 1,
       HFA384X_RX_MSGTYPE_BRIDGETUNNEL = 2, HFA384X_RX_MSGTYPE_MGMT = 4 पूर्ण;


#घोषणा HFA384X_TX_CTRL_ALT_RTRY BIT(5)
#घोषणा HFA384X_TX_CTRL_802_11 BIT(3)
#घोषणा HFA384X_TX_CTRL_802_3 0
#घोषणा HFA384X_TX_CTRL_TX_EX BIT(2)
#घोषणा HFA384X_TX_CTRL_TX_OK BIT(1)

#घोषणा HFA384X_TX_STATUS_RETRYERR BIT(0)
#घोषणा HFA384X_TX_STATUS_AGEDERR BIT(1)
#घोषणा HFA384X_TX_STATUS_DISCON BIT(2)
#घोषणा HFA384X_TX_STATUS_FORMERR BIT(3)

/* HFA3861/3863 (BBP) Control Registers */
#घोषणा HFA386X_CR_TX_CONFIGURE 0x12 /* CR9 */
#घोषणा HFA386X_CR_RX_CONFIGURE 0x14 /* CR10 */
#घोषणा HFA386X_CR_A_D_TEST_MODES2 0x1A /* CR13 */
#घोषणा HFA386X_CR_MANUAL_TX_POWER 0x3E /* CR31 */
#घोषणा HFA386X_CR_MEASURED_TX_POWER 0x74 /* CR58 */


#अगर_घोषित __KERNEL__

#घोषणा PRISM2_TXFID_COUNT 8
#घोषणा PRISM2_DATA_MAXLEN 2304
#घोषणा PRISM2_TXFID_LEN (PRISM2_DATA_MAXLEN + माप(काष्ठा hfa384x_tx_frame))
#घोषणा PRISM2_TXFID_EMPTY 0xffff
#घोषणा PRISM2_TXFID_RESERVED 0xfffe
#घोषणा PRISM2_DUMMY_FID 0xffff
#घोषणा MAX_SSID_LEN 32
#घोषणा MAX_NAME_LEN 32 /* this is assumed to be equal to MAX_SSID_LEN */

#घोषणा PRISM2_DUMP_RX_HDR BIT(0)
#घोषणा PRISM2_DUMP_TX_HDR BIT(1)
#घोषणा PRISM2_DUMP_TXEXC_HDR BIT(2)

काष्ठा hostap_tx_callback_info अणु
	u16 idx;
	व्योम (*func)(काष्ठा sk_buff *, पूर्णांक ok, व्योम *);
	व्योम *data;
	काष्ठा hostap_tx_callback_info *next;
पूर्ण;


/* IEEE 802.11 requires that STA supports concurrent reception of at least
 * three fragmented frames. This define can be increased to support more
 * concurrent frames, but it should be noted that each entry can consume about
 * 2 kB of RAM and increasing cache size will slow करोwn frame reassembly. */
#घोषणा PRISM2_FRAG_CACHE_LEN 4

काष्ठा prism2_frag_entry अणु
	अचिन्हित दीर्घ first_frag_समय;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक last_frag;
	काष्ठा sk_buff *skb;
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
पूर्ण;


काष्ठा hostap_cmd_queue अणु
	काष्ठा list_head list;
	रुको_queue_head_t compl;
	अस्थिर क्रमागत अणु CMD_SLEEP, CMD_CALLBACK, CMD_COMPLETED पूर्ण type;
	व्योम (*callback)(काष्ठा net_device *dev, दीर्घ context, u16 resp0,
			 u16 res);
	दीर्घ context;
	u16 cmd, param0, param1;
	u16 resp0, res;
	अस्थिर पूर्णांक issued, issuing;

	refcount_t usecnt;
	पूर्णांक del_req;
पूर्ण;

/* options क्रम hw_shutकरोwn */
#घोषणा HOSTAP_HW_NO_DISABLE BIT(0)
#घोषणा HOSTAP_HW_ENABLE_CMDCOMPL BIT(1)

प्रकार काष्ठा local_info local_info_t;

काष्ठा prism2_helper_functions अणु
	/* these functions are defined in hardware model specअगरic files
	 * (hostap_अणुcs,plx,pciपूर्ण.c */
	पूर्णांक (*card_present)(local_info_t *local);
	व्योम (*cor_sreset)(local_info_t *local);
	व्योम (*genesis_reset)(local_info_t *local, पूर्णांक hcr);

	/* the following functions are from hostap_hw.c, but they may have some
	 * hardware model specअगरic code */

	/* FIX: low-level commands like cmd might disappear at some poपूर्णांक to
	 * make it easier to change them अगर needed (e.g., cmd would be replaced
	 * with ग_लिखो_mअगर/पढ़ो_mअगर/testcmd/inquire); at least get_rid and
	 * set_rid might move to hostap_अणुcs,plx,pciपूर्ण.c */
	पूर्णांक (*cmd)(काष्ठा net_device *dev, u16 cmd, u16 param0, u16 *param1,
		   u16 *resp0);
	व्योम (*पढ़ो_regs)(काष्ठा net_device *dev, काष्ठा hfa384x_regs *regs);
	पूर्णांक (*get_rid)(काष्ठा net_device *dev, u16 rid, व्योम *buf, पूर्णांक len,
		       पूर्णांक exact_len);
	पूर्णांक (*set_rid)(काष्ठा net_device *dev, u16 rid, व्योम *buf, पूर्णांक len);
	पूर्णांक (*hw_enable)(काष्ठा net_device *dev, पूर्णांक initial);
	पूर्णांक (*hw_config)(काष्ठा net_device *dev, पूर्णांक initial);
	व्योम (*hw_reset)(काष्ठा net_device *dev);
	व्योम (*hw_shutकरोwn)(काष्ठा net_device *dev, पूर्णांक no_disable);
	पूर्णांक (*reset_port)(काष्ठा net_device *dev);
	व्योम (*schedule_reset)(local_info_t *local);
	पूर्णांक (*करोwnload)(local_info_t *local,
			काष्ठा prism2_करोwnload_param *param);
	पूर्णांक (*tx)(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
	पूर्णांक (*set_tim)(काष्ठा net_device *dev, पूर्णांक aid, पूर्णांक set);
	स्थिर काष्ठा proc_ops *पढ़ो_aux_proc_ops;

	पूर्णांक need_tx_headroom; /* number of bytes of headroom needed beक्रमe
			       * IEEE 802.11 header */
	क्रमागत अणु HOSTAP_HW_PCCARD, HOSTAP_HW_PLX, HOSTAP_HW_PCI पूर्ण hw_type;
पूर्ण;


काष्ठा prism2_करोwnload_data अणु
	u32 dl_cmd;
	u32 start_addr;
	u32 num_areas;
	काष्ठा prism2_करोwnload_data_area अणु
		u32 addr; /* wlan card address */
		u32 len;
		u8 *data; /* allocated data */
	पूर्ण data[];
पूर्ण;


#घोषणा HOSTAP_MAX_BSS_COUNT 64
#घोषणा MAX_WPA_IE_LEN 64

काष्ठा hostap_bss_info अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ last_update;
	अचिन्हित पूर्णांक count;
	u8 bssid[ETH_ALEN];
	u16 capab_info;
	u8 ssid[32];
	माप_प्रकार ssid_len;
	u8 wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;
	u8 rsn_ie[MAX_WPA_IE_LEN];
	माप_प्रकार rsn_ie_len;
	पूर्णांक chan;
	पूर्णांक included;
पूर्ण;


/* Per radio निजी Host AP data - shared by all net devices पूर्णांकerfaces used
 * by each radio (wlan#, wlan#ap, wlan#sta, WDS).
 * ((काष्ठा hostap_पूर्णांकerface *) netdev_priv(dev))->local poपूर्णांकs to this
 * काष्ठाure. */
काष्ठा local_info अणु
	काष्ठा module *hw_module;
	पूर्णांक card_idx;
	पूर्णांक dev_enabled;
	पूर्णांक master_dev_स्वतः_खोलो; /* was master device खोलोed स्वतःmatically */
	पूर्णांक num_dev_खोलो; /* number of खोलो devices */
	काष्ठा net_device *dev; /* master radio device */
	काष्ठा net_device *ddev; /* मुख्य data device */
	काष्ठा list_head hostap_पूर्णांकerfaces; /* Host AP पूर्णांकerface list (contains
					     * काष्ठा hostap_पूर्णांकerface entries)
					     */
	rwlock_t अगरace_lock; /* hostap_पूर्णांकerfaces पढ़ो lock; use ग_लिखो lock
			      * when removing entries from the list.
			      * TX and RX paths can use पढ़ो lock. */
	spinlock_t cmdlock, baplock, lock, irq_init_lock;
	काष्ठा mutex rid_bap_mtx;
	u16 infofid; /* MAC buffer id क्रम info frame */
	/* txfid, पूर्णांकransmitfid, next_txtid, and next_alloc are रक्षित by
	 * txfidlock */
	spinlock_t txfidlock;
	पूर्णांक txfid_len; /* length of allocated TX buffers */
	u16 txfid[PRISM2_TXFID_COUNT]; /* buffer IDs क्रम TX frames */
	/* buffer IDs क्रम पूर्णांकransmit frames or PRISM2_TXFID_EMPTY अगर
	 * corresponding txfid is मुक्त क्रम next TX frame */
	u16 पूर्णांकransmitfid[PRISM2_TXFID_COUNT];
	पूर्णांक next_txfid; /* index to the next txfid to be checked क्रम
			 * availability */
	पूर्णांक next_alloc; /* index to the next पूर्णांकransmitfid to be checked क्रम
			 * allocation events */

	/* bitfield क्रम atomic bitops */
#घोषणा HOSTAP_BITS_TRANSMIT 0
#घोषणा HOSTAP_BITS_BAP_TASKLET 1
#घोषणा HOSTAP_BITS_BAP_TASKLET2 2
	अचिन्हित दीर्घ bits;

	काष्ठा ap_data *ap;

	अक्षर essid[MAX_SSID_LEN + 1];
	अक्षर name[MAX_NAME_LEN + 1];
	पूर्णांक name_set;
	u16 channel_mask; /* mask of allowed channels */
	u16 scan_channel_mask; /* mask of channels to be scanned */
	काष्ठा comm_tallies_sums comm_tallies;
	काष्ठा proc_dir_entry *proc;
	पूर्णांक iw_mode; /* operating mode (IW_MODE_*) */
	पूर्णांक pseuकरो_adhoc; /* 0: IW_MODE_ADHOC is real 802.11 compliant IBSS
			   * 1: IW_MODE_ADHOC is "pseudo IBSS" */
	अक्षर bssid[ETH_ALEN];
	पूर्णांक channel;
	पूर्णांक beacon_पूर्णांक;
	पूर्णांक dtim_period;
	पूर्णांक mtu;
	पूर्णांक frame_dump; /* dump RX/TX frame headers, PRISM2_DUMP_ flags */
	पूर्णांक fw_tx_rate_control;
	u16 tx_rate_control;
	u16 basic_rates;
	पूर्णांक hw_resetting;
	पूर्णांक hw_पढ़ोy;
	पूर्णांक hw_reset_tries; /* how many बार reset has been tried */
	पूर्णांक hw_करोwnloading;
	पूर्णांक shutकरोwn;
	पूर्णांक pri_only;
	पूर्णांक no_pri; /* no PRI f/w present */
	पूर्णांक sram_type; /* 8 = x8 SRAM, 16 = x16 SRAM, -1 = unknown */

	क्रमागत अणु
		PRISM2_TXPOWER_AUTO = 0, PRISM2_TXPOWER_OFF,
		PRISM2_TXPOWER_FIXED, PRISM2_TXPOWER_UNKNOWN
	पूर्ण txघातer_type;
	पूर्णांक txघातer; /* अगर txघातer_type == PRISM2_TXPOWER_FIXED */

	/* command queue क्रम hfa384x_cmd(); रक्षित with cmdlock */
	काष्ठा list_head cmd_queue;
	/* max_len क्रम cmd_queue; in addition, cmd_callback can use two
	 * additional entries to prevent sleeping commands from stopping
	 * transmits */
#घोषणा HOSTAP_CMD_QUEUE_MAX_LEN 16
	पूर्णांक cmd_queue_len; /* number of entries in cmd_queue */

	/* अगर card समयout is detected in पूर्णांकerrupt context, reset_queue is
	 * used to schedule card reseting to be करोne in user context */
	काष्ठा work_काष्ठा reset_queue;

	/* For scheduling a change of the promiscuous mode RID */
	पूर्णांक is_promisc;
	काष्ठा work_काष्ठा set_multicast_list_queue;

	काष्ठा work_काष्ठा set_tim_queue;
	काष्ठा list_head set_tim_list;
	spinlock_t set_tim_lock;

	पूर्णांक wds_max_connections;
	पूर्णांक wds_connections;
#घोषणा HOSTAP_WDS_BROADCAST_RA BIT(0)
#घोषणा HOSTAP_WDS_AP_CLIENT BIT(1)
#घोषणा HOSTAP_WDS_STANDARD_FRAME BIT(2)
	u32 wds_type;
	u16 tx_control; /* flags to be used in TX description */
	पूर्णांक manual_retry_count; /* -1 = use f/w शेष; otherwise retry count
				 * to be used with all frames */

	काष्ठा iw_statistics wstats;
	अचिन्हित दीर्घ scan_बारtamp; /* Time started to scan */
	क्रमागत अणु
		PRISM2_MONITOR_80211 = 0, PRISM2_MONITOR_PRISM = 1,
		PRISM2_MONITOR_CAPHDR = 2, PRISM2_MONITOR_RADIOTAP = 3
	पूर्ण monitor_type;
	पूर्णांक monitor_allow_fcserr;

	पूर्णांक hostapd; /* whether user space daemon, hostapd, is used क्रम AP
		      * management */
	पूर्णांक hostapd_sta; /* whether hostapd is used with an extra STA पूर्णांकerface
			  */
	काष्ठा net_device *apdev;
	काष्ठा net_device_stats apdevstats;

	अक्षर assoc_ap_addr[ETH_ALEN];
	काष्ठा net_device *stadev;
	काष्ठा net_device_stats stadevstats;

#घोषणा WEP_KEYS 4
#घोषणा WEP_KEY_LEN 13
	काष्ठा lib80211_crypt_info crypt_info;

	पूर्णांक खोलो_wep; /* allow unencrypted frames */
	पूर्णांक host_encrypt;
	पूर्णांक host_decrypt;
	पूर्णांक privacy_invoked; /* क्रमce privacy invoked flag even अगर no keys are
			      * configured */
	पूर्णांक fw_encrypt_ok; /* whether firmware-based WEP encrypt is working
			    * in Host AP mode (STA f/w 1.4.9 or newer) */
	पूर्णांक bcrx_sta_key; /* use inभागidual keys to override शेष keys even
			   * with RX of broad/multicast frames */

	काष्ठा prism2_frag_entry frag_cache[PRISM2_FRAG_CACHE_LEN];
	अचिन्हित पूर्णांक frag_next_idx;

	पूर्णांक ieee_802_1x; /* is IEEE 802.1X used */

	पूर्णांक antsel_tx, antsel_rx;
	पूर्णांक rts_threshold; /* करोt11RTSThreshold */
	पूर्णांक fragm_threshold; /* करोt11FragmentationThreshold */
	पूर्णांक auth_algs; /* PRISM2_AUTH_ flags */

	पूर्णांक enh_sec; /* cnfEnhSecurity options (broadcast SSID hide/ignore) */
	पूर्णांक tallies32; /* 32-bit tallies in use */

	काष्ठा prism2_helper_functions *func;

	u8 *pda;
	पूर्णांक fw_ap;
#घोषणा PRISM2_FW_VER(major, minor, variant) \
(((major) << 16) | ((minor) << 8) | variant)
	u32 sta_fw_ver;

	/* Tasklets क्रम handling hardware IRQ related operations outside hw IRQ
	 * handler */
	काष्ठा tasklet_काष्ठा bap_tasklet;

	काष्ठा tasklet_काष्ठा info_tasklet;
	काष्ठा sk_buff_head info_list; /* info frames as skb's क्रम
					* info_tasklet */

	काष्ठा hostap_tx_callback_info *tx_callback; /* रेजिस्टरed TX callbacks
						      */

	काष्ठा tasklet_काष्ठा rx_tasklet;
	काष्ठा sk_buff_head rx_list;

	काष्ठा tasklet_काष्ठा sta_tx_exc_tasklet;
	काष्ठा sk_buff_head sta_tx_exc_list;

	पूर्णांक host_roaming;
	अचिन्हित दीर्घ last_join_समय; /* समय of last JoinRequest */
	काष्ठा hfa384x_hostscan_result *last_scan_results;
	पूर्णांक last_scan_results_count;
	क्रमागत अणु PRISM2_SCAN, PRISM2_HOSTSCAN पूर्ण last_scan_type;
	काष्ठा work_काष्ठा info_queue;
	अचिन्हित दीर्घ pending_info; /* bit field of pending info_queue items */
#घोषणा PRISM2_INFO_PENDING_LINKSTATUS 0
#घोषणा PRISM2_INFO_PENDING_SCANRESULTS 1
	पूर्णांक prev_link_status; /* previous received LinkStatus info */
	पूर्णांक prev_linkstatus_connected;
	u8 preferred_ap[ETH_ALEN]; /* use this AP अगर possible */

#अगर_घोषित PRISM2_CALLBACK
	व्योम *callback_data; /* Can be used in callbacks; e.g., allocate
			      * on enable event and मुक्त on disable event.
			      * Host AP driver code करोes not touch this. */
#पूर्ण_अगर /* PRISM2_CALLBACK */

	रुको_queue_head_t hostscan_wq;

	/* Passive scan in Host AP mode */
	काष्ठा समयr_list passive_scan_समयr;
	पूर्णांक passive_scan_पूर्णांकerval; /* in seconds, 0 = disabled */
	पूर्णांक passive_scan_channel;
	क्रमागत अणु PASSIVE_SCAN_WAIT, PASSIVE_SCAN_LISTEN पूर्ण passive_scan_state;

	काष्ठा समयr_list tick_समयr;
	अचिन्हित दीर्घ last_tick_समयr;
	अचिन्हित पूर्णांक sw_tick_stuck;

	/* commsQuality / dBmCommsQuality data from periodic polling; only
	 * valid क्रम Managed and Ad-hoc modes */
	अचिन्हित दीर्घ last_comms_qual_update;
	पूर्णांक comms_qual; /* in some odd unit.. */
	पूर्णांक avg_संकेत; /* in dB (note: negative) */
	पूर्णांक avg_noise; /* in dB (note: negative) */
	काष्ठा work_काष्ठा comms_qual_update;

	/* RSSI to dBm adjusपंचांगent (क्रम RX descriptor fields) */
	पूर्णांक rssi_to_dBm; /* subtract from RSSI to get approximate dBm value */

	/* BSS list / रक्षित by local->lock */
	काष्ठा list_head bss_list;
	पूर्णांक num_bss_info;
	पूर्णांक wpa; /* WPA support enabled */
	पूर्णांक tkip_countermeasures;
	पूर्णांक drop_unencrypted;
	/* Generic IEEE 802.11 info element to be added to
	 * ProbeResp/Beacon/(Re)AssocReq */
	u8 *generic_elem;
	माप_प्रकार generic_elem_len;

#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
	/* Persistent अस्थिर करोwnload data */
	काष्ठा prism2_करोwnload_data *dl_pri;
	काष्ठा prism2_करोwnload_data *dl_sec;
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */

#अगर_घोषित PRISM2_IO_DEBUG
#घोषणा PRISM2_IO_DEBUG_SIZE 10000
	u32 io_debug[PRISM2_IO_DEBUG_SIZE];
	पूर्णांक io_debug_head;
	पूर्णांक io_debug_enabled;
#पूर्ण_अगर /* PRISM2_IO_DEBUG */

	/* Poपूर्णांकer to hardware model specअगरic (cs,pci,plx) निजी data. */
	व्योम *hw_priv;
पूर्ण;


/* Per पूर्णांकerface निजी Host AP data
 * Allocated क्रम each net device that Host AP uses (wlan#, wlan#ap, wlan#sta,
 * WDS) and netdev_priv(dev) poपूर्णांकs to this काष्ठाure. */
काष्ठा hostap_पूर्णांकerface अणु
	काष्ठा list_head list; /* list entry in Host AP पूर्णांकerface list */
	काष्ठा net_device *dev; /* poपूर्णांकer to this device */
	काष्ठा local_info *local; /* poपूर्णांकer to shared निजी data */
	काष्ठा net_device_stats stats;
	काष्ठा iw_spy_data spy_data; /* iwspy support */
	काष्ठा iw_खुला_data wireless_data;

	क्रमागत अणु
		HOSTAP_INTERFACE_MASTER,
		HOSTAP_INTERFACE_MAIN,
		HOSTAP_INTERFACE_AP,
		HOSTAP_INTERFACE_STA,
		HOSTAP_INTERFACE_WDS,
	पूर्ण type;

	जोड़ अणु
		काष्ठा hostap_पूर्णांकerface_wds अणु
			u8 remote_addr[ETH_ALEN];
		पूर्ण wds;
	पूर्ण u;
पूर्ण;


#घोषणा HOSTAP_SKB_TX_DATA_MAGIC 0xf08a36a2

/*
 * TX meta data - stored in skb->cb buffer, so this must not be increased over
 * the 48-byte limit.
 * THE PADDING THIS STARTS WITH IS A HORRIBLE HACK THAT SHOULD NOT LIVE
 * TO SEE THE DAY.
 */
काष्ठा hostap_skb_tx_data अणु
	अचिन्हित पूर्णांक __padding_क्रम_शेष_qdiscs;
	u32 magic; /* HOSTAP_SKB_TX_DATA_MAGIC */
	u8 rate; /* transmit rate */
#घोषणा HOSTAP_TX_FLAGS_WDS BIT(0)
#घोषणा HOSTAP_TX_FLAGS_BUFFERED_FRAME BIT(1)
#घोषणा HOSTAP_TX_FLAGS_ADD_MOREDATA BIT(2)
	u8 flags; /* HOSTAP_TX_FLAGS_* */
	u16 tx_cb_idx;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	अचिन्हित दीर्घ jअगरfies; /* queueing बारtamp */
	अचिन्हित लघु ethertype;
पूर्ण;


#अगर_अघोषित PRISM2_NO_DEBUG

#घोषणा DEBUG_FID BIT(0)
#घोषणा DEBUG_PS BIT(1)
#घोषणा DEBUG_FLOW BIT(2)
#घोषणा DEBUG_AP BIT(3)
#घोषणा DEBUG_HW BIT(4)
#घोषणा DEBUG_EXTRA BIT(5)
#घोषणा DEBUG_EXTRA2 BIT(6)
#घोषणा DEBUG_PS2 BIT(7)
#घोषणा DEBUG_MASK (DEBUG_PS | DEBUG_AP | DEBUG_HW | DEBUG_EXTRA)
#घोषणा PDEBUG(n, args...) \
करो अणु अगर ((n) & DEBUG_MASK) prपूर्णांकk(KERN_DEBUG args); पूर्ण जबतक (0)
#घोषणा PDEBUG2(n, args...) \
करो अणु अगर ((n) & DEBUG_MASK) prपूर्णांकk(args); पूर्ण जबतक (0)

#अन्यथा /* PRISM2_NO_DEBUG */

#घोषणा PDEBUG(n, args...)
#घोषणा PDEBUG2(n, args...)

#पूर्ण_अगर /* PRISM2_NO_DEBUG */

क्रमागत अणु BAP0 = 0, BAP1 = 1 पूर्ण;

#घोषणा PRISM2_IO_DEBUG_CMD_INB 0
#घोषणा PRISM2_IO_DEBUG_CMD_INW 1
#घोषणा PRISM2_IO_DEBUG_CMD_INSW 2
#घोषणा PRISM2_IO_DEBUG_CMD_OUTB 3
#घोषणा PRISM2_IO_DEBUG_CMD_OUTW 4
#घोषणा PRISM2_IO_DEBUG_CMD_OUTSW 5
#घोषणा PRISM2_IO_DEBUG_CMD_ERROR 6
#घोषणा PRISM2_IO_DEBUG_CMD_INTERRUPT 7

#अगर_घोषित PRISM2_IO_DEBUG

#घोषणा PRISM2_IO_DEBUG_ENTRY(cmd, reg, value) \
(((cmd) << 24) | ((reg) << 16) | value)

अटल अंतरभूत व्योम prism2_io_debug_add(काष्ठा net_device *dev, पूर्णांक cmd,
				       पूर्णांक reg, पूर्णांक value)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;

	अगर (!local->io_debug_enabled)
		वापस;

	local->io_debug[local->io_debug_head] =	jअगरfies & 0xffffffff;
	अगर (++local->io_debug_head >= PRISM2_IO_DEBUG_SIZE)
		local->io_debug_head = 0;
	local->io_debug[local->io_debug_head] =
		PRISM2_IO_DEBUG_ENTRY(cmd, reg, value);
	अगर (++local->io_debug_head >= PRISM2_IO_DEBUG_SIZE)
		local->io_debug_head = 0;
पूर्ण


अटल अंतरभूत व्योम prism2_io_debug_error(काष्ठा net_device *dev, पूर्णांक err)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;
	अचिन्हित दीर्घ flags;

	अगर (!local->io_debug_enabled)
		वापस;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_ERROR, 0, err);
	अगर (local->io_debug_enabled == 1) अणु
		local->io_debug_enabled = 0;
		prपूर्णांकk(KERN_DEBUG "%s: I/O debug stopped\n", dev->name);
	पूर्ण
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

#अन्यथा /* PRISM2_IO_DEBUG */

अटल अंतरभूत व्योम prism2_io_debug_add(काष्ठा net_device *dev, पूर्णांक cmd,
				       पूर्णांक reg, पूर्णांक value)
अणु
पूर्ण

अटल अंतरभूत व्योम prism2_io_debug_error(काष्ठा net_device *dev, पूर्णांक err)
अणु
पूर्ण

#पूर्ण_अगर /* PRISM2_IO_DEBUG */


#अगर_घोषित PRISM2_CALLBACK
क्रमागत अणु
	/* Called when card is enabled */
	PRISM2_CALLBACK_ENABLE,

	/* Called when card is disabled */
	PRISM2_CALLBACK_DISABLE,

	/* Called when RX/TX starts/ends */
	PRISM2_CALLBACK_RX_START, PRISM2_CALLBACK_RX_END,
	PRISM2_CALLBACK_TX_START, PRISM2_CALLBACK_TX_END
पूर्ण;
व्योम prism2_callback(local_info_t *local, पूर्णांक event);
#अन्यथा /* PRISM2_CALLBACK */
#घोषणा prism2_callback(d, e) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* PRISM2_CALLBACK */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* HOSTAP_WLAN_H */
