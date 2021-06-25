<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2002,2003 Oliver Kurth
 *	     (c) 2003,2004 Joerg Albert <joerg.albert@gmx.de>
 *	     (c) 2007 Guiकरो Guenther <agx@sigxcpu.org>
 *
 * This driver was based on inक्रमmation from the Sourceक्रमge driver
 * released and मुख्यtained by Aपंचांगel:
 *
 *  http://sourceक्रमge.net/projects/aपंचांगelwlandriver/
 *
 * Although the code was completely re-written,
 * it would have been impossible without Aपंचांगel's decision to
 * release an Open Source driver (unक्रमtunately the firmware was
 * kept binary only). Thanks क्रम that decision to Aपंचांगel!
 */

#अगर_अघोषित _AT76_USB_H
#घोषणा _AT76_USB_H

/* Board types */
क्रमागत board_type अणु
	BOARD_503_ISL3861 = 1,
	BOARD_503_ISL3863 = 2,
	BOARD_503 = 3,
	BOARD_503_ACC = 4,
	BOARD_505 = 5,
	BOARD_505_2958 = 6,
	BOARD_505A = 7,
	BOARD_505AMX = 8
पूर्ण;

#घोषणा CMD_STATUS_IDLE				0x00
#घोषणा CMD_STATUS_COMPLETE			0x01
#घोषणा CMD_STATUS_UNKNOWN			0x02
#घोषणा CMD_STATUS_INVALID_PARAMETER		0x03
#घोषणा CMD_STATUS_FUNCTION_NOT_SUPPORTED	0x04
#घोषणा CMD_STATUS_TIME_OUT			0x07
#घोषणा CMD_STATUS_IN_PROGRESS			0x08
#घोषणा CMD_STATUS_HOST_FAILURE			0xff
#घोषणा CMD_STATUS_SCAN_FAILED			0xf0

/* answers to get op mode */
#घोषणा OPMODE_NONE				0x00
#घोषणा OPMODE_NORMAL_NIC_WITH_FLASH		0x01
#घोषणा OPMODE_HW_CONFIG_MODE			0x02
#घोषणा OPMODE_DFU_MODE_WITH_FLASH		0x03
#घोषणा OPMODE_NORMAL_NIC_WITHOUT_FLASH		0x04

#घोषणा CMD_SET_MIB		0x01
#घोषणा CMD_GET_MIB		0x02
#घोषणा CMD_SCAN		0x03
#घोषणा CMD_JOIN		0x04
#घोषणा CMD_START_IBSS		0x05
#घोषणा CMD_RADIO_ON		0x06
#घोषणा CMD_RADIO_OFF		0x07
#घोषणा CMD_STARTUP		0x0B

#घोषणा MIB_LOCAL		0x01
#घोषणा MIB_MAC_ADDR		0x02
#घोषणा MIB_MAC			0x03
#घोषणा MIB_MAC_MGMT		0x05
#घोषणा MIB_MAC_WEP		0x06
#घोषणा MIB_PHY			0x07
#घोषणा MIB_FW_VERSION		0x08
#घोषणा MIB_MDOMAIN		0x09

#घोषणा ADHOC_MODE		1
#घोषणा INFRASTRUCTURE_MODE	2

/* values क्रम काष्ठा mib_local, field preamble_type */
#घोषणा PREAMBLE_TYPE_LONG	0
#घोषणा PREAMBLE_TYPE_SHORT	1
#घोषणा PREAMBLE_TYPE_AUTO	2

/* values क्रम tx_rate */
#घोषणा TX_RATE_1MBIT		0
#घोषणा TX_RATE_2MBIT		1
#घोषणा TX_RATE_5_5MBIT 	2
#घोषणा TX_RATE_11MBIT		3
#घोषणा TX_RATE_AUTO		4

/* घातer management modes */
#घोषणा AT76_PM_OFF		1
#घोषणा AT76_PM_ON		2
#घोषणा AT76_PM_SMART		3

काष्ठा hwcfg_r505 अणु
	u8 cr39_values[14];
	u8 reserved1[14];
	u8 bb_cr[14];
	u8 pidvid[4];
	u8 mac_addr[ETH_ALEN];
	u8 regulatory_करोमुख्य;
	u8 reserved2[14];
	u8 cr15_values[14];
	u8 reserved3[3];
पूर्ण __packed;

काष्ठा hwcfg_rfmd अणु
	u8 cr20_values[14];
	u8 cr21_values[14];
	u8 bb_cr[14];
	u8 pidvid[4];
	u8 mac_addr[ETH_ALEN];
	u8 regulatory_करोमुख्य;
	u8 low_घातer_values[14];
	u8 normal_घातer_values[14];
	u8 reserved1[3];
पूर्ण __packed;

काष्ठा hwcfg_पूर्णांकersil अणु
	u8 mac_addr[ETH_ALEN];
	u8 cr31_values[14];
	u8 cr58_values[14];
	u8 pidvid[4];
	u8 regulatory_करोमुख्य;
	u8 reserved[1];
पूर्ण __packed;

जोड़ at76_hwcfg अणु
	काष्ठा hwcfg_पूर्णांकersil i;
	काष्ठा hwcfg_rfmd r3;
	काष्ठा hwcfg_r505 r5;
पूर्ण;

#घोषणा WEP_SMALL_KEY_LEN	(40 / 8)
#घोषणा WEP_LARGE_KEY_LEN	(104 / 8)
#घोषणा WEP_KEYS		(4)

काष्ठा at76_card_config अणु
	u8 exclude_unencrypted;
	u8 promiscuous_mode;
	u8 लघु_retry_limit;
	u8 encryption_type;
	__le16 rts_threshold;
	__le16 fragmentation_threshold;	/* 256..2346 */
	u8 basic_rate_set[4];
	u8 स्वतः_rate_fallback;	/* 0,1 */
	u8 channel;
	u8 privacy_invoked;
	u8 wep_शेष_key_id;	/* 0..3 */
	u8 current_ssid[32];
	u8 wep_शेष_key_value[4][WEP_LARGE_KEY_LEN];
	u8 ssid_len;
	u8 लघु_preamble;
	__le16 beacon_period;
पूर्ण __packed;

काष्ठा at76_command अणु
	u8 cmd;
	u8 reserved;
	__le16 size;
	u8 data[];
पूर्ण __packed;

/* Length of Aपंचांगel-specअगरic Rx header beक्रमe 802.11 frame */
#घोषणा AT76_RX_HDRLEN दुरत्व(काष्ठा at76_rx_buffer, packet)

काष्ठा at76_rx_buffer अणु
	__le16 wlength;
	u8 rx_rate;
	u8 newbss;
	u8 fragmentation;
	u8 rssi;
	u8 link_quality;
	u8 noise_level;
	__le32 rx_समय;
	u8 packet[IEEE80211_MAX_FRAG_THRESHOLD];
पूर्ण __packed;

/* Length of Aपंचांगel-specअगरic Tx header beक्रमe 802.11 frame */
#घोषणा AT76_TX_HDRLEN दुरत्व(काष्ठा at76_tx_buffer, packet)

काष्ठा at76_tx_buffer अणु
	__le16 wlength;
	u8 tx_rate;
	u8 padding;
	u8 reserved[4];
	u8 packet[IEEE80211_MAX_FRAG_THRESHOLD];
पूर्ण __packed;

/* defines क्रम scan_type below */
#घोषणा SCAN_TYPE_ACTIVE	0
#घोषणा SCAN_TYPE_PASSIVE	1

काष्ठा at76_req_scan अणु
	u8 bssid[ETH_ALEN];
	u8 essid[32];
	u8 scan_type;
	u8 channel;
	__le16 probe_delay;
	__le16 min_channel_समय;
	__le16 max_channel_समय;
	u8 essid_size;
	u8 पूर्णांकernational_scan;
पूर्ण __packed;

काष्ठा at76_req_ibss अणु
	u8 bssid[ETH_ALEN];
	u8 essid[32];
	u8 bss_type;
	u8 channel;
	u8 essid_size;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा at76_req_join अणु
	u8 bssid[ETH_ALEN];
	u8 essid[32];
	u8 bss_type;
	u8 channel;
	__le16 समयout;
	u8 essid_size;
	u8 reserved;
पूर्ण __packed;

काष्ठा mib_local अणु
	u16 reserved0;
	u8 beacon_enable;
	u8 txस्वतःrate_fallback;
	u8 reserved1;
	u8 ssid_size;
	u8 promiscuous_mode;
	u16 reserved2;
	u8 preamble_type;
	u16 reserved3;
पूर्ण __packed;

काष्ठा mib_mac_addr अणु
	u8 mac_addr[ETH_ALEN];
	u8 res[2];		/* ??? */
	u8 group_addr[4][ETH_ALEN];
	u8 group_addr_status[4];
पूर्ण __packed;

काष्ठा mib_mac अणु
	__le32 max_tx_msdu_lअगरeसमय;
	__le32 max_rx_lअगरeसमय;
	__le16 frag_threshold;
	__le16 rts_threshold;
	__le16 cwmin;
	__le16 cwmax;
	u8 लघु_retry_समय;
	u8 दीर्घ_retry_समय;
	u8 scan_type;		/* active or passive */
	u8 scan_channel;
	__le16 probe_delay;	/* delay beक्रमe ProbeReq in active scan, RO */
	__le16 min_channel_समय;
	__le16 max_channel_समय;
	__le16 listen_पूर्णांकerval;
	u8 desired_ssid[32];
	u8 desired_bssid[ETH_ALEN];
	u8 desired_bsstype;	/* ad-hoc or infraकाष्ठाure */
	u8 reserved2;
पूर्ण __packed;

काष्ठा mib_mac_mgmt अणु
	__le16 beacon_period;
	__le16 CFP_max_duration;
	__le16 medium_occupancy_limit;
	__le16 station_id;	/* assoc id */
	__le16 ATIM_winकरोw;
	u8 CFP_mode;
	u8 privacy_option_implemented;
	u8 DTIM_period;
	u8 CFP_period;
	u8 current_bssid[ETH_ALEN];
	u8 current_essid[32];
	u8 current_bss_type;
	u8 घातer_mgmt_mode;
	/* rfmd and 505 */
	u8 ibss_change;
	u8 res;
	u8 multi_करोमुख्य_capability_implemented;
	u8 multi_करोमुख्य_capability_enabled;
	u8 country_string[IEEE80211_COUNTRY_STRING_LEN];
	u8 reserved[3];
पूर्ण __packed;

काष्ठा mib_mac_wep अणु
	u8 privacy_invoked;	/* 0 disable encr., 1 enable encr */
	u8 wep_शेष_key_id;
	u8 wep_key_mapping_len;
	u8 exclude_unencrypted;
	__le32 wep_icv_error_count;
	__le32 wep_excluded_count;
	u8 wep_शेष_keyvalue[WEP_KEYS][WEP_LARGE_KEY_LEN];
	u8 encryption_level;	/* 1 क्रम 40bit, 2 क्रम 104bit encryption */
पूर्ण __packed;

काष्ठा mib_phy अणु
	__le32 ed_threshold;

	__le16 slot_समय;
	__le16 sअगरs_समय;
	__le16 preamble_length;
	__le16 plcp_header_length;
	__le16 mpdu_max_length;
	__le16 cca_mode_supported;

	u8 operation_rate_set[4];
	u8 channel_id;
	u8 current_cca_mode;
	u8 phy_type;
	u8 current_reg_करोमुख्य;
पूर्ण __packed;

काष्ठा mib_fw_version अणु
	u8 major;
	u8 minor;
	u8 patch;
	u8 build;
पूर्ण __packed;

काष्ठा mib_mकरोमुख्य अणु
	u8 tx_घातerlevel[14];
	u8 channel_list[14];	/* 0 क्रम invalid channels */
पूर्ण __packed;

काष्ठा set_mib_buffer अणु
	u8 type;
	u8 size;
	u8 index;
	u8 reserved;
	जोड़ अणु
		u8 byte;
		__le16 word;
		u8 addr[ETH_ALEN];
		काष्ठा mib_mac_wep wep_mib;
	पूर्ण data;
पूर्ण __packed;

काष्ठा at76_fw_header अणु
	__le32 crc;		/* CRC32 of the whole image */
	__le32 board_type;	/* firmware compatibility code */
	u8 build;		/* firmware build number */
	u8 patch;		/* firmware patch level */
	u8 minor;		/* firmware minor version */
	u8 major;		/* firmware major version */
	__le32 str_offset;	/* offset of the copyright string */
	__le32 पूर्णांक_fw_offset;	/* पूर्णांकernal firmware image offset */
	__le32 पूर्णांक_fw_len;	/* पूर्णांकernal firmware image length */
	__le32 ext_fw_offset;	/* बाह्यal firmware image offset */
	__le32 ext_fw_len;	/* बाह्यal firmware image length */
पूर्ण __packed;

/* a description of a regulatory करोमुख्य and the allowed channels */
काष्ठा reg_करोमुख्य अणु
	u16 code;
	अक्षर स्थिर *name;
	u32 channel_map;	/* अगर bit N is set, channel (N+1) is allowed */
पूर्ण;

/* Data क्रम one loaded firmware file */
काष्ठा fwentry अणु
	स्थिर अक्षर *स्थिर fwname;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक extfw_size;
	पूर्णांक पूर्णांकfw_size;
	/* poपूर्णांकer to loaded firmware, no need to मुक्त */
	u8 *extfw;		/* बाह्यal firmware, extfw_size bytes दीर्घ */
	u8 *पूर्णांकfw;		/* पूर्णांकernal firmware, पूर्णांकfw_size bytes दीर्घ */
	क्रमागत board_type board_type;	/* board type */
	काष्ठा mib_fw_version fw_version;
	पूर्णांक loaded;		/* Loaded and parsed successfully */
पूर्ण;

काष्ठा at76_priv अणु
	काष्ठा usb_device *udev;	/* USB device poपूर्णांकer */

	काष्ठा sk_buff *rx_skb;	/* skbuff क्रम receiving data */
	काष्ठा sk_buff *tx_skb;	/* skbuff क्रम transmitting data */
	व्योम *bulk_out_buffer;	/* buffer क्रम sending data */

	काष्ठा urb *tx_urb;	/* URB क्रम sending data */
	काष्ठा urb *rx_urb;	/* URB क्रम receiving data */

	अचिन्हित पूर्णांक tx_pipe;	/* bulk out pipe */
	अचिन्हित पूर्णांक rx_pipe;	/* bulk in pipe */

	काष्ठा mutex mtx;	/* locks this काष्ठाure */

	/* work queues */
	काष्ठा work_काष्ठा work_set_promisc;
	काष्ठा work_काष्ठा work_submit_rx;
	काष्ठा work_काष्ठा work_join_bssid;
	काष्ठा delayed_work dwork_hw_scan;

	काष्ठा tasklet_काष्ठा rx_tasklet;

	/* the WEP stuff */
	पूर्णांक wep_enabled;	/* 1 अगर WEP is enabled */
	पूर्णांक wep_key_id;		/* key id to be used */
	u8 wep_keys[WEP_KEYS][WEP_LARGE_KEY_LEN];	/* WEP keys */
	u8 wep_keys_len[WEP_KEYS];	/* length of WEP keys */

	पूर्णांक channel;
	पूर्णांक iw_mode;
	u8 bssid[ETH_ALEN];
	u8 essid[IW_ESSID_MAX_SIZE];
	पूर्णांक essid_size;
	पूर्णांक radio_on;
	पूर्णांक promisc;

	पूर्णांक preamble_type;	/* 0 - दीर्घ, 1 - लघु, 2 - स्वतः */
	पूर्णांक auth_mode;		/* authentication type: 0 खोलो, 1 shared key */
	पूर्णांक txrate;		/* 0,1,2,3 = 1,2,5.5,11 Mbps, 4 is स्वतः */
	पूर्णांक frag_threshold;	/* threshold क्रम fragmentation of tx packets */
	पूर्णांक rts_threshold;	/* threshold क्रम RTS mechanism */
	पूर्णांक लघु_retry_limit;

	पूर्णांक scan_min_समय;	/* scan min channel समय */
	पूर्णांक scan_max_समय;	/* scan max channel समय */
	पूर्णांक scan_mode;		/* SCAN_TYPE_ACTIVE, SCAN_TYPE_PASSIVE */
	पूर्णांक scan_need_any;	/* अगर set, need to scan क्रम any ESSID */
	bool scanning;		/* अगर set, the scan is running */

	u16 assoc_id;		/* current association ID, अगर associated */

	u8 pm_mode;		/* घातer management mode */
	u32 pm_period;		/* घातer management period in microseconds */

	काष्ठा reg_करोमुख्य स्थिर *करोमुख्य;	/* reg करोमुख्य description */

	/* These fields contain HW config provided by the device (not all of
	 * these fields are used by all board types) */
	u8 mac_addr[ETH_ALEN];
	u8 regulatory_करोमुख्य;

	काष्ठा at76_card_config card_config;

	क्रमागत board_type board_type;
	काष्ठा mib_fw_version fw_version;

	अचिन्हित पूर्णांक device_unplugged:1;
	अचिन्हित पूर्णांक netdev_रेजिस्टरed:1;
	काष्ठा set_mib_buffer mib_buf;	/* global buffer क्रम set_mib calls */

	पूर्णांक beacon_period;	/* period of mgmt beacons, Kus */

	काष्ठा ieee80211_hw *hw;
	पूर्णांक mac80211_रेजिस्टरed;
पूर्ण;

#घोषणा AT76_SUPPORTED_FILTERS 0

#घोषणा SCAN_POLL_INTERVAL	(HZ / 4)

#घोषणा CMD_COMPLETION_TIMEOUT	(5 * HZ)

#घोषणा DEF_RTS_THRESHOLD	1536
#घोषणा DEF_FRAG_THRESHOLD	1536
#घोषणा DEF_SHORT_RETRY_LIMIT	8
#घोषणा DEF_CHANNEL		10
#घोषणा DEF_SCAN_MIN_TIME	10
#घोषणा DEF_SCAN_MAX_TIME	120

/* the max padding size क्रम tx in bytes (see calc_padding) */
#घोषणा MAX_PADDING_SIZE	53

#पूर्ण_अगर				/* _AT76_USB_H */
