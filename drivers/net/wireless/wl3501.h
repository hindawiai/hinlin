<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __WL3501_H__
#घोषणा __WL3501_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/ieee80211.h>

/* define क्रम WLA 2.0 */
#घोषणा WL3501_BLKSZ 256
/*
 * ID क्रम input Signals of DRIVER block
 * bit[7-5] is block ID: 000
 * bit[4-0] is संकेत ID
*/
क्रमागत wl3501_संकेतs अणु
	WL3501_SIG_ALARM,
	WL3501_SIG_MD_CONFIRM,
	WL3501_SIG_MD_IND,
	WL3501_SIG_ASSOC_CONFIRM,
	WL3501_SIG_ASSOC_IND,
	WL3501_SIG_AUTH_CONFIRM,
	WL3501_SIG_AUTH_IND,
	WL3501_SIG_DEAUTH_CONFIRM,
	WL3501_SIG_DEAUTH_IND,
	WL3501_SIG_DISASSOC_CONFIRM,
	WL3501_SIG_DISASSOC_IND,
	WL3501_SIG_GET_CONFIRM,
	WL3501_SIG_JOIN_CONFIRM,
	WL3501_SIG_PWR_MGMT_CONFIRM,
	WL3501_SIG_REASSOC_CONFIRM,
	WL3501_SIG_REASSOC_IND,
	WL3501_SIG_SCAN_CONFIRM,
	WL3501_SIG_SET_CONFIRM,
	WL3501_SIG_START_CONFIRM,
	WL3501_SIG_RESYNC_CONFIRM,
	WL3501_SIG_SITE_CONFIRM,
	WL3501_SIG_SAVE_CONFIRM,
	WL3501_SIG_RFTEST_CONFIRM,
/*
 * ID क्रम input Signals of MLME block
 * bit[7-5] is block ID: 010
 * bit[4-0] is संकेत ID
 */
	WL3501_SIG_ASSOC_REQ = 0x20,
	WL3501_SIG_AUTH_REQ,
	WL3501_SIG_DEAUTH_REQ,
	WL3501_SIG_DISASSOC_REQ,
	WL3501_SIG_GET_REQ,
	WL3501_SIG_JOIN_REQ,
	WL3501_SIG_PWR_MGMT_REQ,
	WL3501_SIG_REASSOC_REQ,
	WL3501_SIG_SCAN_REQ,
	WL3501_SIG_SET_REQ,
	WL3501_SIG_START_REQ,
	WL3501_SIG_MD_REQ,
	WL3501_SIG_RESYNC_REQ,
	WL3501_SIG_SITE_REQ,
	WL3501_SIG_SAVE_REQ,
	WL3501_SIG_RF_TEST_REQ,
	WL3501_SIG_MM_CONFIRM = 0x60,
	WL3501_SIG_MM_IND,
पूर्ण;

क्रमागत wl3501_mib_attribs अणु
	WL3501_MIB_ATTR_STATION_ID,
	WL3501_MIB_ATTR_AUTH_ALGORITHMS,
	WL3501_MIB_ATTR_AUTH_TYPE,
	WL3501_MIB_ATTR_MEDIUM_OCCUPANCY_LIMIT,
	WL3501_MIB_ATTR_CF_POLLABLE,
	WL3501_MIB_ATTR_CFP_PERIOD,
	WL3501_MIB_ATTR_CFPMAX_DURATION,
	WL3501_MIB_ATTR_AUTH_RESP_TMOUT,
	WL3501_MIB_ATTR_RX_DTIMS,
	WL3501_MIB_ATTR_PRIV_OPT_IMPLEMENTED,
	WL3501_MIB_ATTR_PRIV_INVOKED,
	WL3501_MIB_ATTR_WEP_DEFAULT_KEYS,
	WL3501_MIB_ATTR_WEP_DEFAULT_KEY_ID,
	WL3501_MIB_ATTR_WEP_KEY_MAPPINGS,
	WL3501_MIB_ATTR_WEP_KEY_MAPPINGS_LEN,
	WL3501_MIB_ATTR_EXCLUDE_UNENCRYPTED,
	WL3501_MIB_ATTR_WEP_ICV_ERROR_COUNT,
	WL3501_MIB_ATTR_WEP_UNDECRYPTABLE_COUNT,
	WL3501_MIB_ATTR_WEP_EXCLUDED_COUNT,
	WL3501_MIB_ATTR_MAC_ADDR,
	WL3501_MIB_ATTR_GROUP_ADDRS,
	WL3501_MIB_ATTR_RTS_THRESHOLD,
	WL3501_MIB_ATTR_SHORT_RETRY_LIMIT,
	WL3501_MIB_ATTR_LONG_RETRY_LIMIT,
	WL3501_MIB_ATTR_FRAG_THRESHOLD,
	WL3501_MIB_ATTR_MAX_TX_MSDU_LIFETIME,
	WL3501_MIB_ATTR_MAX_RX_LIFETIME,
	WL3501_MIB_ATTR_MANUFACTURER_ID,
	WL3501_MIB_ATTR_PRODUCT_ID,
	WL3501_MIB_ATTR_TX_FRAG_COUNT,
	WL3501_MIB_ATTR_MULTICAST_TX_FRAME_COUNT,
	WL3501_MIB_ATTR_FAILED_COUNT,
	WL3501_MIB_ATTR_RX_FRAG_COUNT,
	WL3501_MIB_ATTR_MULTICAST_RX_COUNT,
	WL3501_MIB_ATTR_FCS_ERROR_COUNT,
	WL3501_MIB_ATTR_RETRY_COUNT,
	WL3501_MIB_ATTR_MULTIPLE_RETRY_COUNT,
	WL3501_MIB_ATTR_RTS_SUCCESS_COUNT,
	WL3501_MIB_ATTR_RTS_FAILURE_COUNT,
	WL3501_MIB_ATTR_ACK_FAILURE_COUNT,
	WL3501_MIB_ATTR_FRAME_DUPLICATE_COUNT,
	WL3501_MIB_ATTR_PHY_TYPE,
	WL3501_MIB_ATTR_REG_DOMAINS_SUPPORT,
	WL3501_MIB_ATTR_CURRENT_REG_DOMAIN,
	WL3501_MIB_ATTR_SLOT_TIME,
	WL3501_MIB_ATTR_CCA_TIME,
	WL3501_MIB_ATTR_RX_TX_TURNAROUND_TIME,
	WL3501_MIB_ATTR_TX_PLCP_DELAY,
	WL3501_MIB_ATTR_RX_TX_SWITCH_TIME,
	WL3501_MIB_ATTR_TX_RAMP_ON_TIME,
	WL3501_MIB_ATTR_TX_RF_DELAY,
	WL3501_MIB_ATTR_SIFS_TIME,
	WL3501_MIB_ATTR_RX_RF_DELAY,
	WL3501_MIB_ATTR_RX_PLCP_DELAY,
	WL3501_MIB_ATTR_MAC_PROCESSING_DELAY,
	WL3501_MIB_ATTR_TX_RAMP_OFF_TIME,
	WL3501_MIB_ATTR_PREAMBLE_LEN,
	WL3501_MIB_ATTR_PLCP_HEADER_LEN,
	WL3501_MIB_ATTR_MPDU_DURATION_FACTOR,
	WL3501_MIB_ATTR_AIR_PROPAGATION_TIME,
	WL3501_MIB_ATTR_TEMP_TYPE,
	WL3501_MIB_ATTR_CW_MIN,
	WL3501_MIB_ATTR_CW_MAX,
	WL3501_MIB_ATTR_SUPPORT_DATA_RATES_TX,
	WL3501_MIB_ATTR_SUPPORT_DATA_RATES_RX,
	WL3501_MIB_ATTR_MPDU_MAX_LEN,
	WL3501_MIB_ATTR_SUPPORT_TX_ANTENNAS,
	WL3501_MIB_ATTR_CURRENT_TX_ANTENNA,
	WL3501_MIB_ATTR_SUPPORT_RX_ANTENNAS,
	WL3501_MIB_ATTR_DIVERSITY_SUPPORT,
	WL3501_MIB_ATTR_DIVERSITY_SELECTION_RS,
	WL3501_MIB_ATTR_NR_SUPPORTED_PWR_LEVELS,
	WL3501_MIB_ATTR_TX_PWR_LEVEL1,
	WL3501_MIB_ATTR_TX_PWR_LEVEL2,
	WL3501_MIB_ATTR_TX_PWR_LEVEL3,
	WL3501_MIB_ATTR_TX_PWR_LEVEL4,
	WL3501_MIB_ATTR_TX_PWR_LEVEL5,
	WL3501_MIB_ATTR_TX_PWR_LEVEL6,
	WL3501_MIB_ATTR_TX_PWR_LEVEL7,
	WL3501_MIB_ATTR_TX_PWR_LEVEL8,
	WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL,
	WL3501_MIB_ATTR_CURRENT_CHAN,
	WL3501_MIB_ATTR_CCA_MODE_SUPPORTED,
	WL3501_MIB_ATTR_CURRENT_CCA_MODE,
	WL3501_MIB_ATTR_ED_THRESHOLD,
	WL3501_MIB_ATTR_SINTHESIZER_LOCKED,
	WL3501_MIB_ATTR_CURRENT_PWR_STATE,
	WL3501_MIB_ATTR_DOZE_TURNON_TIME,
	WL3501_MIB_ATTR_RCR33,
	WL3501_MIB_ATTR_DEFAULT_CHAN,
	WL3501_MIB_ATTR_SSID,
	WL3501_MIB_ATTR_PWR_MGMT_ENABLE,
	WL3501_MIB_ATTR_NET_CAPABILITY,
	WL3501_MIB_ATTR_ROUTING,
पूर्ण;

क्रमागत wl3501_net_type अणु
	WL3501_NET_TYPE_INFRA,
	WL3501_NET_TYPE_ADHOC,
	WL3501_NET_TYPE_ANY_BSS,
पूर्ण;

क्रमागत wl3501_scan_type अणु
	WL3501_SCAN_TYPE_ACTIVE,
	WL3501_SCAN_TYPE_PASSIVE,
पूर्ण;

क्रमागत wl3501_tx_result अणु
	WL3501_TX_RESULT_SUCCESS,
	WL3501_TX_RESULT_NO_BSS,
	WL3501_TX_RESULT_RETRY_LIMIT,
पूर्ण;

क्रमागत wl3501_sys_type अणु
	WL3501_SYS_TYPE_OPEN,
	WL3501_SYS_TYPE_SHARE_KEY,
पूर्ण;

क्रमागत wl3501_status अणु
	WL3501_STATUS_SUCCESS,
	WL3501_STATUS_INVALID,
	WL3501_STATUS_TIMEOUT,
	WL3501_STATUS_REFUSED,
	WL3501_STATUS_MANY_REQ,
	WL3501_STATUS_ALREADY_BSS,
पूर्ण;

#घोषणा WL3501_MGMT_CAPABILITY_ESS		0x0001  /* see 802.11 p.58 */
#घोषणा WL3501_MGMT_CAPABILITY_IBSS		0x0002  /*      - " -	   */
#घोषणा WL3501_MGMT_CAPABILITY_CF_POLLABLE	0x0004  /*      - " -	   */
#घोषणा WL3501_MGMT_CAPABILITY_CF_POLL_REQUEST	0x0008  /*      - " -	   */
#घोषणा WL3501_MGMT_CAPABILITY_PRIVACY		0x0010  /*      - " -	   */

#घोषणा IW_REG_DOMAIN_FCC	0x10	/* Channel 1 to 11	USA    */
#घोषणा IW_REG_DOMAIN_DOC	0x20	/* Channel 1 to 11	Canada */
#घोषणा IW_REG_DOMAIN_ETSI	0x30	/* Channel 1 to 13	Europe */
#घोषणा IW_REG_DOMAIN_SPAIN	0x31	/* Channel 10 to 11	Spain  */
#घोषणा IW_REG_DOMAIN_FRANCE	0x32	/* Channel 10 to 13	France */
#घोषणा IW_REG_DOMAIN_MKK	0x40	/* Channel 14		Japan  */
#घोषणा IW_REG_DOMAIN_MKK1	0x41	/* Channel 1-14		Japan  */
#घोषणा IW_REG_DOMAIN_ISRAEL	0x50	/* Channel 3 - 9	Israel */

#घोषणा IW_MGMT_RATE_LABEL_MANDATORY 128 /* MSB */

क्रमागत iw_mgmt_rate_labels अणु
	IW_MGMT_RATE_LABEL_1MBIT   = 2,
	IW_MGMT_RATE_LABEL_2MBIT   = 4,
	IW_MGMT_RATE_LABEL_5_5MBIT = 11,
	IW_MGMT_RATE_LABEL_11MBIT  = 22,
पूर्ण;

क्रमागत iw_mgmt_info_element_ids अणु
	IW_MGMT_INFO_ELEMENT_SSID,		  /* Service Set Identity */
	IW_MGMT_INFO_ELEMENT_SUPPORTED_RATES,
	IW_MGMT_INFO_ELEMENT_FH_PARAMETER_SET,
	IW_MGMT_INFO_ELEMENT_DS_PARAMETER_SET,
	IW_MGMT_INFO_ELEMENT_CS_PARAMETER_SET,
	IW_MGMT_INFO_ELEMENT_CS_TIM,		  /* Traffic Inक्रमmation Map */
	IW_MGMT_INFO_ELEMENT_IBSS_PARAMETER_SET,
	/* 7-15: Reserved, unused */
	IW_MGMT_INFO_ELEMENT_CHALLENGE_TEXT = 16,
	/* 17-31 Reserved क्रम challenge text extension */
	/* 32-255 Reserved, unused */
पूर्ण;

काष्ठा iw_mgmt_info_element अणु
	u8 id; /* one of क्रमागत iw_mgmt_info_element_ids,
		  but माप(क्रमागत) > माप(u8) :-( */
	u8 len;
	u8 data[];
पूर्ण __packed;

काष्ठा iw_mgmt_essid_pset अणु
	काष्ठा iw_mgmt_info_element el;
	u8 			    essid[IW_ESSID_MAX_SIZE];
पूर्ण __packed;

/*
 * According to 802.11 Wireless Networks, the definitive guide - O'Reilly
 * Pg 75
 */ 
#घोषणा IW_DATA_RATE_MAX_LABELS 8

काष्ठा iw_mgmt_data_rset अणु
	काष्ठा iw_mgmt_info_element el;
	u8 			    data_rate_labels[IW_DATA_RATE_MAX_LABELS];
पूर्ण __packed;

काष्ठा iw_mgmt_ds_pset अणु
	काष्ठा iw_mgmt_info_element el;
	u8 			    chan;
पूर्ण __packed;

काष्ठा iw_mgmt_cf_pset अणु
	काष्ठा iw_mgmt_info_element el;
	u8 			    cfp_count;
	u8 			    cfp_period;
	u16 			    cfp_max_duration;
	u16 			    cfp_dur_reमुख्यing;
पूर्ण __packed;

काष्ठा iw_mgmt_ibss_pset अणु
	काष्ठा iw_mgmt_info_element el;
	u16 			    atim_winकरोw;
पूर्ण __packed;

काष्ठा wl3501_tx_hdr अणु
	u16	tx_cnt;
	u8	sync[16];
	u16	sfd;
	u8	संकेत;
	u8	service;
	u16	len;
	u16	crc16;
	u16	frame_ctrl;
	u16	duration_id;
	u8	addr1[ETH_ALEN];
	u8	addr2[ETH_ALEN];
	u8	addr3[ETH_ALEN];
	u16	seq_ctrl;
	u8	addr4[ETH_ALEN];
पूर्ण;

काष्ठा wl3501_rx_hdr अणु
	u16	rx_next_blk;
	u16	rc_next_frame_blk;
	u8	rx_blk_ctrl;
	u8	rx_next_frame;
	u8	rx_next_frame1;
	u8	rssi;
	अक्षर	समय[8];
	u8	संकेत;
	u8	service;
	u16	len;
	u16	crc16;
	u16	frame_ctrl;
	u16	duration;
	u8	addr1[ETH_ALEN];
	u8	addr2[ETH_ALEN];
	u8	addr3[ETH_ALEN];
	u16	seq;
	u8	addr4[ETH_ALEN];
पूर्ण;

काष्ठा wl3501_start_req अणु
	u16			    next_blk;
	u8			    sig_id;
	u8			    bss_type;
	u16			    beacon_period;
	u16			    dtim_period;
	u16			    probe_delay;
	u16			    cap_info;
	काष्ठा iw_mgmt_essid_pset   ssid;
	काष्ठा iw_mgmt_data_rset    bss_basic_rset;
	काष्ठा iw_mgmt_data_rset    operational_rset;
	काष्ठा iw_mgmt_cf_pset	    cf_pset;
	काष्ठा iw_mgmt_ds_pset	    ds_pset;
	काष्ठा iw_mgmt_ibss_pset    ibss_pset;
पूर्ण;

काष्ठा wl3501_assoc_req अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	समयout;
	u16	cap_info;
	u16	listen_पूर्णांकerval;
	u8	mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा wl3501_assoc_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	status;
पूर्ण;

काष्ठा wl3501_assoc_ind अणु
	u16	next_blk;
	u8	sig_id;
	u8	mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा wl3501_auth_req अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	type;
	u16	समयout;
	u8	mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा wl3501_auth_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	type;
	u16	status;
	u8	mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा wl3501_get_req अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	mib_attrib;
पूर्ण;

काष्ठा wl3501_get_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	mib_status;
	u16	mib_attrib;
	u8	mib_value[100];
पूर्ण;

काष्ठा wl3501_req अणु
	u16			    beacon_period;
	u16			    dtim_period;
	u16			    cap_info;
	u8			    bss_type;
	u8			    bssid[ETH_ALEN];
	काष्ठा iw_mgmt_essid_pset   ssid;
	काष्ठा iw_mgmt_ds_pset	    ds_pset;
	काष्ठा iw_mgmt_cf_pset	    cf_pset;
	काष्ठा iw_mgmt_ibss_pset    ibss_pset;
	काष्ठा iw_mgmt_data_rset    bss_basic_rset;
पूर्ण;

काष्ठा wl3501_join_req अणु
	u16			    next_blk;
	u8			    sig_id;
	u8			    reserved;
	काष्ठा iw_mgmt_data_rset    operational_rset;
	u16			    reserved2;
	u16			    समयout;
	u16			    probe_delay;
	u8			    बारtamp[8];
	u8			    local_समय[8];
	काष्ठा wl3501_req	    req;
पूर्ण;

काष्ठा wl3501_join_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	status;
पूर्ण;

काष्ठा wl3501_pwr_mgmt_req अणु
	u16	next_blk;
	u8	sig_id;
	u8	pwr_save;
	u8	wake_up;
	u8	receive_dtims;
पूर्ण;

काष्ठा wl3501_pwr_mgmt_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	status;
पूर्ण;

काष्ठा wl3501_scan_req अणु
	u16			    next_blk;
	u8			    sig_id;
	u8			    bss_type;
	u16			    probe_delay;
	u16			    min_chan_समय;
	u16			    max_chan_समय;
	u8			    chan_list[14];
	u8			    bssid[ETH_ALEN];
	काष्ठा iw_mgmt_essid_pset   ssid;
	क्रमागत wl3501_scan_type	    scan_type;
पूर्ण;

काष्ठा wl3501_scan_confirm अणु
	u16			    next_blk;
	u8			    sig_id;
	u8			    reserved;
	u16			    status;
	अक्षर			    बारtamp[8];
	अक्षर			    स_स्थानीय[8];
	काष्ठा wl3501_req	    req;
	u8			    rssi;
पूर्ण;

काष्ठा wl3501_start_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	status;
पूर्ण;

काष्ठा wl3501_md_req अणु
	u16	next_blk;
	u8	sig_id;
	u8	routing;
	u16	data;
	u16	size;
	u8	pri;
	u8	service_class;
	काष्ठा अणु
		u8	daddr[ETH_ALEN];
		u8	saddr[ETH_ALEN];
	पूर्ण addr;
पूर्ण;

काष्ठा wl3501_md_ind अणु
	u16	next_blk;
	u8	sig_id;
	u8	routing;
	u16	data;
	u16	size;
	u8	reception;
	u8	pri;
	u8	service_class;
	काष्ठा अणु
		u8	daddr[ETH_ALEN];
		u8	saddr[ETH_ALEN];
	पूर्ण addr;
पूर्ण;

काष्ठा wl3501_md_confirm अणु
	u16	next_blk;
	u8	sig_id;
	u8	reserved;
	u16	data;
	u8	status;
	u8	pri;
	u8	service_class;
पूर्ण;

काष्ठा wl3501_resync_req अणु
	u16	next_blk;
	u8	sig_id;
पूर्ण;

/* Definitions क्रम supporting clone adapters. */
/* System Interface Registers (SIR space) */
#घोषणा WL3501_NIC_GCR ((u8)0x00)	/* SIR0 - General Conf Register */
#घोषणा WL3501_NIC_BSS ((u8)0x01)	/* SIR1 - Bank Switching Select Reg */
#घोषणा WL3501_NIC_LMAL ((u8)0x02)	/* SIR2 - Local Mem addr Reg [7:0] */
#घोषणा WL3501_NIC_LMAH ((u8)0x03)	/* SIR3 - Local Mem addr Reg [14:8] */
#घोषणा WL3501_NIC_IODPA ((u8)0x04)	/* SIR4 - I/O Data Port A */
#घोषणा WL3501_NIC_IODPB ((u8)0x05)	/* SIR5 - I/O Data Port B */
#घोषणा WL3501_NIC_IODPC ((u8)0x06)	/* SIR6 - I/O Data Port C */
#घोषणा WL3501_NIC_IODPD ((u8)0x07)	/* SIR7 - I/O Data Port D */

/* Bits in GCR */
#घोषणा WL3501_GCR_SWRESET ((u8)0x80)
#घोषणा WL3501_GCR_CORESET ((u8)0x40)
#घोषणा WL3501_GCR_DISPWDN ((u8)0x20)
#घोषणा WL3501_GCR_ECWAIT  ((u8)0x10)
#घोषणा WL3501_GCR_ECINT   ((u8)0x08)
#घोषणा WL3501_GCR_INT2EC  ((u8)0x04)
#घोषणा WL3501_GCR_ENECINT ((u8)0x02)
#घोषणा WL3501_GCR_DAM     ((u8)0x01)

/* Bits in BSS (Bank Switching Select Register) */
#घोषणा WL3501_BSS_FPAGE0 ((u8)0x20)	/* Flash memory page0 */
#घोषणा WL3501_BSS_FPAGE1 ((u8)0x28)
#घोषणा WL3501_BSS_FPAGE2 ((u8)0x30)
#घोषणा WL3501_BSS_FPAGE3 ((u8)0x38)
#घोषणा WL3501_BSS_SPAGE0 ((u8)0x00)	/* SRAM page0 */
#घोषणा WL3501_BSS_SPAGE1 ((u8)0x08)
#घोषणा WL3501_BSS_SPAGE2 ((u8)0x10)
#घोषणा WL3501_BSS_SPAGE3 ((u8)0x18)

/* Define Driver Interface */
/* Refer IEEE 802.11 */
/* Tx packet header, include PLCP and MPDU */
/* Tx PLCP Header */
काष्ठा wl3501_80211_tx_plcp_hdr अणु
	u8	sync[16];
	u16	sfd;
	u8	संकेत;
	u8	service;
	u16	len;
	u16	crc16;
पूर्ण __packed;

काष्ठा wl3501_80211_tx_hdr अणु
	काष्ठा wl3501_80211_tx_plcp_hdr	pclp_hdr;
	काष्ठा ieee80211_hdr		mac_hdr;
पूर्ण __packed __aligned(2);

/*
   Reserve the beginning Tx space क्रम descriptor use.

   TxBlockOffset -->	*----*----*----*----* \
	(TxFreeDesc)	|  0 |  1 |  2 |  3 |  \
			|  4 |  5 |  6 |  7 |   |
			|  8 |  9 | 10 | 11 |   TX_DESC * 20
			| 12 | 13 | 14 | 15 |   |
			| 16 | 17 | 18 | 19 |  /
   TxBufferBegin -->	*----*----*----*----* /
   (TxBufferHead)	| 		    |
   (TxBufferTail)	| 		    |
			|    Send Buffer    |
			| 		    |
			|		    |
			*-------------------*
   TxBufferEnd    -------------------------/

*/

काष्ठा wl3501_card अणु
	पूर्णांक				base_addr;
	u8				mac_addr[ETH_ALEN];
	spinlock_t			lock;
	रुको_queue_head_t		रुको;
	काष्ठा wl3501_get_confirm	sig_get_confirm;
	काष्ठा wl3501_pwr_mgmt_confirm	sig_pwr_mgmt_confirm;
	u16				tx_buffer_size;
	u16				tx_buffer_head;
	u16				tx_buffer_tail;
	u16				tx_buffer_cnt;
	u16				esbq_req_start;
	u16				esbq_req_end;
	u16				esbq_req_head;
	u16				esbq_req_tail;
	u16				esbq_confirm_start;
	u16				esbq_confirm_end;
	u16				esbq_confirm;
	काष्ठा iw_mgmt_essid_pset  	essid;
	काष्ठा iw_mgmt_essid_pset  	keep_essid;
	u8				bssid[ETH_ALEN];
	पूर्णांक				net_type;
	अक्षर				nick[32];
	अक्षर				card_name[32];
	अक्षर				firmware_date[32];
	u8				chan;
	u8				cap_info;
	u16				start_seg;
	u16				bss_cnt;
	u16				join_sta_bss;
	u8				rssi;
	u8				adhoc_बार;
	u8				reg_करोमुख्य;
	u8				version[2];
	काष्ठा wl3501_scan_confirm	bss_set[20];

	काष्ठा iw_statistics		wstats;
	काष्ठा iw_spy_data		spy_data;
	काष्ठा iw_खुला_data		wireless_data;
	काष्ठा pcmcia_device		*p_dev;
पूर्ण;
#पूर्ण_अगर
