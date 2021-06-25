<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_d3_h__
#घोषणा __iwl_fw_api_d3_h__

/**
 * क्रमागत iwl_d0i3_flags - d0i3 flags
 * @IWL_D0I3_RESET_REQUIRE: FW require reset upon resume
 */
क्रमागत iwl_d0i3_flags अणु
	IWL_D0I3_RESET_REQUIRE = BIT(0),
पूर्ण;

/**
 * क्रमागत iwl_d3_wakeup_flags - D3 manager wakeup flags
 * @IWL_WAKEUP_D3_CONFIG_FW_ERROR: wake up on firmware sysनिश्चित
 */
क्रमागत iwl_d3_wakeup_flags अणु
	IWL_WAKEUP_D3_CONFIG_FW_ERROR = BIT(0),
पूर्ण; /* D3_MANAGER_WAKEUP_CONFIG_API_E_VER_3 */

/**
 * काष्ठा iwl_d3_manager_config - D3 manager configuration command
 * @min_sleep_समय: minimum sleep समय (in usec)
 * @wakeup_flags: wakeup flags, see &क्रमागत iwl_d3_wakeup_flags
 * @wakeup_host_समयr: क्रमce wakeup after this many seconds
 *
 * The काष्ठाure is used क्रम the D3_CONFIG_CMD command.
 */
काष्ठा iwl_d3_manager_config अणु
	__le32 min_sleep_समय;
	__le32 wakeup_flags;
	__le32 wakeup_host_समयr;
पूर्ण __packed; /* D3_MANAGER_CONFIG_CMD_S_VER_4 */


/* TODO: OFFLOADS_QUERY_API_S_VER_1 */

/**
 * क्रमागत iwl_d3_proto_offloads - enabled protocol offloads
 * @IWL_D3_PROTO_OFFLOAD_ARP: ARP data is enabled
 * @IWL_D3_PROTO_OFFLOAD_NS: NS (Neighbor Solicitation) is enabled
 * @IWL_D3_PROTO_IPV4_VALID: IPv4 data is valid
 * @IWL_D3_PROTO_IPV6_VALID: IPv6 data is valid
 */
क्रमागत iwl_proto_offloads अणु
	IWL_D3_PROTO_OFFLOAD_ARP = BIT(0),
	IWL_D3_PROTO_OFFLOAD_NS = BIT(1),
	IWL_D3_PROTO_IPV4_VALID = BIT(2),
	IWL_D3_PROTO_IPV6_VALID = BIT(3),
पूर्ण;

#घोषणा IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V1	2
#घोषणा IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V2	6
#घोषणा IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V3L	12
#घोषणा IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V3S	4
#घोषणा IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_MAX	12

#घोषणा IWL_PROTO_OFFLOAD_NUM_NS_CONFIG_V3L	4
#घोषणा IWL_PROTO_OFFLOAD_NUM_NS_CONFIG_V3S	2

/**
 * काष्ठा iwl_proto_offload_cmd_common - ARP/NS offload common part
 * @enabled: enable flags
 * @remote_ipv4_addr: remote address to answer to (or zero अगर all)
 * @host_ipv4_addr: our IPv4 address to respond to queries क्रम
 * @arp_mac_addr: our MAC address क्रम ARP responses
 * @reserved: unused
 */
काष्ठा iwl_proto_offload_cmd_common अणु
	__le32 enabled;
	__be32 remote_ipv4_addr;
	__be32 host_ipv4_addr;
	u8 arp_mac_addr[ETH_ALEN];
	__le16 reserved;
पूर्ण __packed;

/**
 * काष्ठा iwl_proto_offload_cmd_v1 - ARP/NS offload configuration
 * @common: common/IPv4 configuration
 * @remote_ipv6_addr: remote address to answer to (or zero अगर all)
 * @solicited_node_ipv6_addr: broken -- solicited node address exists
 *	क्रम each target address
 * @target_ipv6_addr: our target addresses
 * @ndp_mac_addr: neighbor solicitation response MAC address
 * @reserved2: reserved
 */
काष्ठा iwl_proto_offload_cmd_v1 अणु
	काष्ठा iwl_proto_offload_cmd_common common;
	u8 remote_ipv6_addr[16];
	u8 solicited_node_ipv6_addr[16];
	u8 target_ipv6_addr[IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V1][16];
	u8 ndp_mac_addr[ETH_ALEN];
	__le16 reserved2;
पूर्ण __packed; /* PROT_OFFLOAD_CONFIG_CMD_DB_S_VER_1 */

/**
 * काष्ठा iwl_proto_offload_cmd_v2 - ARP/NS offload configuration
 * @common: common/IPv4 configuration
 * @remote_ipv6_addr: remote address to answer to (or zero अगर all)
 * @solicited_node_ipv6_addr: broken -- solicited node address exists
 *	क्रम each target address
 * @target_ipv6_addr: our target addresses
 * @ndp_mac_addr: neighbor solicitation response MAC address
 * @num_valid_ipv6_addrs: number of valid IPv6 addresses
 * @reserved2: reserved
 */
काष्ठा iwl_proto_offload_cmd_v2 अणु
	काष्ठा iwl_proto_offload_cmd_common common;
	u8 remote_ipv6_addr[16];
	u8 solicited_node_ipv6_addr[16];
	u8 target_ipv6_addr[IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V2][16];
	u8 ndp_mac_addr[ETH_ALEN];
	u8 num_valid_ipv6_addrs;
	u8 reserved2[3];
पूर्ण __packed; /* PROT_OFFLOAD_CONFIG_CMD_DB_S_VER_2 */

काष्ठा iwl_ns_config अणु
	काष्ठा in6_addr source_ipv6_addr;
	काष्ठा in6_addr dest_ipv6_addr;
	u8 target_mac_addr[ETH_ALEN];
	__le16 reserved;
पूर्ण __packed; /* NS_OFFLOAD_CONFIG */

काष्ठा iwl_targ_addr अणु
	काष्ठा in6_addr addr;
	__le32 config_num;
पूर्ण __packed; /* TARGET_IPV6_ADDRESS */

/**
 * काष्ठा iwl_proto_offload_cmd_v3_small - ARP/NS offload configuration
 * @common: common/IPv4 configuration
 * @num_valid_ipv6_addrs: number of valid IPv6 addresses
 * @targ_addrs: target IPv6 addresses
 * @ns_config: NS offload configurations
 */
काष्ठा iwl_proto_offload_cmd_v3_small अणु
	काष्ठा iwl_proto_offload_cmd_common common;
	__le32 num_valid_ipv6_addrs;
	काष्ठा iwl_targ_addr targ_addrs[IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V3S];
	काष्ठा iwl_ns_config ns_config[IWL_PROTO_OFFLOAD_NUM_NS_CONFIG_V3S];
पूर्ण __packed; /* PROT_OFFLOAD_CONFIG_CMD_DB_S_VER_3 */

/**
 * काष्ठा iwl_proto_offload_cmd_v3_large - ARP/NS offload configuration
 * @common: common/IPv4 configuration
 * @num_valid_ipv6_addrs: number of valid IPv6 addresses
 * @targ_addrs: target IPv6 addresses
 * @ns_config: NS offload configurations
 */
काष्ठा iwl_proto_offload_cmd_v3_large अणु
	काष्ठा iwl_proto_offload_cmd_common common;
	__le32 num_valid_ipv6_addrs;
	काष्ठा iwl_targ_addr targ_addrs[IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_V3L];
	काष्ठा iwl_ns_config ns_config[IWL_PROTO_OFFLOAD_NUM_NS_CONFIG_V3L];
पूर्ण __packed; /* PROT_OFFLOAD_CONFIG_CMD_DB_S_VER_3 */

/*
 * WOWLAN_PATTERNS
 */
#घोषणा IWL_WOWLAN_MIN_PATTERN_LEN	16
#घोषणा IWL_WOWLAN_MAX_PATTERN_LEN	128

काष्ठा iwl_wowlan_pattern_v1 अणु
	u8 mask[IWL_WOWLAN_MAX_PATTERN_LEN / 8];
	u8 pattern[IWL_WOWLAN_MAX_PATTERN_LEN];
	u8 mask_size;
	u8 pattern_size;
	__le16 reserved;
पूर्ण __packed; /* WOWLAN_PATTERN_API_S_VER_1 */

#घोषणा IWL_WOWLAN_MAX_PATTERNS	20

/**
 * काष्ठा iwl_wowlan_patterns_cmd - WoWLAN wakeup patterns
 */
काष्ठा iwl_wowlan_patterns_cmd_v1 अणु
	/**
	 * @n_patterns: number of patterns
	 */
	__le32 n_patterns;

	/**
	 * @patterns: the patterns, array length in @n_patterns
	 */
	काष्ठा iwl_wowlan_pattern_v1 patterns[];
पूर्ण __packed; /* WOWLAN_PATTERN_ARRAY_API_S_VER_1 */

#घोषणा IPV4_ADDR_SIZE	4
#घोषणा IPV6_ADDR_SIZE	16

क्रमागत iwl_wowlan_pattern_type अणु
	WOWLAN_PATTERN_TYPE_BITMASK,
	WOWLAN_PATTERN_TYPE_IPV4_TCP_SYN,
	WOWLAN_PATTERN_TYPE_IPV6_TCP_SYN,
	WOWLAN_PATTERN_TYPE_IPV4_TCP_SYN_WILDCARD,
	WOWLAN_PATTERN_TYPE_IPV6_TCP_SYN_WILDCARD,
पूर्ण; /* WOWLAN_PATTERN_TYPE_API_E_VER_1 */

/**
 * काष्ठा iwl_wowlan_ipv4_tcp_syn - WoWLAN IPv4 TCP SYN pattern data
 */
काष्ठा iwl_wowlan_ipv4_tcp_syn अणु
	/**
	 * @src_addr: source IP address to match
	 */
	u8 src_addr[IPV4_ADDR_SIZE];

	/**
	 * @dst_addr: destination IP address to match
	 */
	u8 dst_addr[IPV4_ADDR_SIZE];

	/**
	 * @src_port: source TCP port to match
	 */
	__le16 src_port;

	/**
	 * @dst_port: destination TCP port to match
	 */
	__le16 dst_port;
पूर्ण __packed; /* WOWLAN_IPV4_TCP_SYN_API_S_VER_1 */

/**
 * काष्ठा iwl_wowlan_ipv6_tcp_syn - WoWLAN Ipv6 TCP SYN pattern data
 */
काष्ठा iwl_wowlan_ipv6_tcp_syn अणु
	/**
	 * @src_addr: source IP address to match
	 */
	u8 src_addr[IPV6_ADDR_SIZE];

	/**
	 * @dst_addr: destination IP address to match
	 */
	u8 dst_addr[IPV6_ADDR_SIZE];

	/**
	 * @src_port: source TCP port to match
	 */
	__le16 src_port;

	/**
	 * @dst_port: destination TCP port to match
	 */
	__le16 dst_port;
पूर्ण __packed; /* WOWLAN_IPV6_TCP_SYN_API_S_VER_1 */

/**
 * जोड़ iwl_wowlan_pattern_data - Data क्रम the dअगरferent pattern types
 *
 * If wildcard addresses/ports are to be used, the जोड़ can be left
 * undefined.
 */
जोड़ iwl_wowlan_pattern_data अणु
	/**
	 * @biपंचांगask: biपंचांगask pattern data
	 */
	काष्ठा iwl_wowlan_pattern_v1 biपंचांगask;

	/**
	 * @ipv4_tcp_syn: IPv4 TCP SYN pattern data
	 */
	काष्ठा iwl_wowlan_ipv4_tcp_syn ipv4_tcp_syn;

	/**
	 * @ipv6_tcp_syn: IPv6 TCP SYN pattern data
	 */
	काष्ठा iwl_wowlan_ipv6_tcp_syn ipv6_tcp_syn;
पूर्ण; /* WOWLAN_PATTERN_API_U_VER_1 */

/**
 * काष्ठा iwl_wowlan_pattern_v2 - Pattern entry क्रम the WoWLAN wakeup patterns
 */
काष्ठा iwl_wowlan_pattern_v2 अणु
	/**
	 * @pattern_type: defines the काष्ठा type to be used in the जोड़
	 */
	u8 pattern_type;

	/**
	 * @reserved: reserved क्रम alignment
	 */
	u8 reserved[3];

	/**
	 * @u: the जोड़ containing the match data, or undefined क्रम
	 *     wildcard matches
	 */
	जोड़ iwl_wowlan_pattern_data u;
पूर्ण __packed; /* WOWLAN_PATTERN_API_S_VER_2 */

/**
 * काष्ठा iwl_wowlan_patterns_cmd - WoWLAN wakeup patterns command
 */
काष्ठा iwl_wowlan_patterns_cmd अणु
	/**
	 * @n_patterns: number of patterns
	 */
	__le32 n_patterns;

	/**
	 * @patterns: the patterns, array length in @n_patterns
	 */
	काष्ठा iwl_wowlan_pattern_v2 patterns[];
पूर्ण __packed; /* WOWLAN_PATTERN_ARRAY_API_S_VER_2 */

क्रमागत iwl_wowlan_wakeup_filters अणु
	IWL_WOWLAN_WAKEUP_MAGIC_PACKET			= BIT(0),
	IWL_WOWLAN_WAKEUP_PATTERN_MATCH			= BIT(1),
	IWL_WOWLAN_WAKEUP_BEACON_MISS			= BIT(2),
	IWL_WOWLAN_WAKEUP_LINK_CHANGE			= BIT(3),
	IWL_WOWLAN_WAKEUP_GTK_REKEY_FAIL		= BIT(4),
	IWL_WOWLAN_WAKEUP_EAP_IDENT_REQ			= BIT(5),
	IWL_WOWLAN_WAKEUP_4WAY_HANDSHAKE		= BIT(6),
	IWL_WOWLAN_WAKEUP_ENABLE_NET_DETECT		= BIT(7),
	IWL_WOWLAN_WAKEUP_RF_KILL_DEASSERT		= BIT(8),
	IWL_WOWLAN_WAKEUP_REMOTE_LINK_LOSS		= BIT(9),
	IWL_WOWLAN_WAKEUP_REMOTE_SIGNATURE_TABLE	= BIT(10),
	IWL_WOWLAN_WAKEUP_REMOTE_TCP_EXTERNAL		= BIT(11),
	IWL_WOWLAN_WAKEUP_REMOTE_WAKEUP_PACKET		= BIT(12),
	IWL_WOWLAN_WAKEUP_IOAC_MAGIC_PACKET		= BIT(13),
	IWL_WOWLAN_WAKEUP_HOST_TIMER			= BIT(14),
	IWL_WOWLAN_WAKEUP_RX_FRAME			= BIT(15),
	IWL_WOWLAN_WAKEUP_BCN_FILTERING			= BIT(16),
पूर्ण; /* WOWLAN_WAKEUP_FILTER_API_E_VER_4 */

क्रमागत iwl_wowlan_flags अणु
	IS_11W_ASSOC		= BIT(0),
	ENABLE_L3_FILTERING	= BIT(1),
	ENABLE_NBNS_FILTERING	= BIT(2),
	ENABLE_DHCP_FILTERING	= BIT(3),
	ENABLE_STORE_BEACON	= BIT(4),
पूर्ण;

/**
 * काष्ठा iwl_wowlan_config_cmd - WoWLAN configuration
 * @wakeup_filter: filter from &क्रमागत iwl_wowlan_wakeup_filters
 * @non_qos_seq: non-QoS sequence counter to use next
 * @qos_seq: QoS sequence counters to use next
 * @wowlan_ba_tearकरोwn_tids: biपंचांगap of BA sessions to tear करोwn
 * @is_11n_connection: indicates HT connection
 * @offloading_tid: TID reserved क्रम firmware use
 * @flags: extra flags, see &क्रमागत iwl_wowlan_flags
 * @sta_id: station ID क्रम wowlan.
 * @reserved: reserved
 */
काष्ठा iwl_wowlan_config_cmd अणु
	__le32 wakeup_filter;
	__le16 non_qos_seq;
	__le16 qos_seq[8];
	u8 wowlan_ba_tearकरोwn_tids;
	u8 is_11n_connection;
	u8 offloading_tid;
	u8 flags;
	u8 sta_id;
	u8 reserved;
पूर्ण __packed; /* WOWLAN_CONFIG_API_S_VER_5 */

/*
 * WOWLAN_TSC_RSC_PARAMS
 */
#घोषणा IWL_NUM_RSC	16

काष्ठा tkip_sc अणु
	__le16 iv16;
	__le16 pad;
	__le32 iv32;
पूर्ण __packed; /* TKIP_SC_API_U_VER_1 */

काष्ठा iwl_tkip_rsc_tsc अणु
	काष्ठा tkip_sc unicast_rsc[IWL_NUM_RSC];
	काष्ठा tkip_sc multicast_rsc[IWL_NUM_RSC];
	काष्ठा tkip_sc tsc;
पूर्ण __packed; /* TKIP_TSC_RSC_API_S_VER_1 */

काष्ठा aes_sc अणु
	__le64 pn;
पूर्ण __packed; /* TKIP_AES_SC_API_U_VER_1 */

काष्ठा iwl_aes_rsc_tsc अणु
	काष्ठा aes_sc unicast_rsc[IWL_NUM_RSC];
	काष्ठा aes_sc multicast_rsc[IWL_NUM_RSC];
	काष्ठा aes_sc tsc;
पूर्ण __packed; /* AES_TSC_RSC_API_S_VER_1 */

जोड़ iwl_all_tsc_rsc अणु
	काष्ठा iwl_tkip_rsc_tsc tkip;
	काष्ठा iwl_aes_rsc_tsc aes;
पूर्ण; /* ALL_TSC_RSC_API_S_VER_2 */

काष्ठा iwl_wowlan_rsc_tsc_params_cmd_ver_2 अणु
	जोड़ iwl_all_tsc_rsc all_tsc_rsc;
पूर्ण __packed; /* ALL_TSC_RSC_API_S_VER_2 */

काष्ठा iwl_wowlan_rsc_tsc_params_cmd अणु
	काष्ठा iwl_wowlan_rsc_tsc_params_cmd_ver_2 params;
	__le32 sta_id;
पूर्ण __packed; /* ALL_TSC_RSC_API_S_VER_4 */

#घोषणा IWL_MIC_KEY_SIZE	8
काष्ठा iwl_mic_keys अणु
	u8 tx[IWL_MIC_KEY_SIZE];
	u8 rx_unicast[IWL_MIC_KEY_SIZE];
	u8 rx_mcast[IWL_MIC_KEY_SIZE];
पूर्ण __packed; /* MIC_KEYS_API_S_VER_1 */

#घोषणा IWL_P1K_SIZE		5
काष्ठा iwl_p1k_cache अणु
	__le16 p1k[IWL_P1K_SIZE];
पूर्ण __packed;

#घोषणा IWL_NUM_RX_P1K_CACHE	2

काष्ठा iwl_wowlan_tkip_params_cmd_ver_1 अणु
	काष्ठा iwl_mic_keys mic_keys;
	काष्ठा iwl_p1k_cache tx;
	काष्ठा iwl_p1k_cache rx_uni[IWL_NUM_RX_P1K_CACHE];
	काष्ठा iwl_p1k_cache rx_multi[IWL_NUM_RX_P1K_CACHE];
पूर्ण __packed; /* WOWLAN_TKIP_SETTING_API_S_VER_1 */

काष्ठा iwl_wowlan_tkip_params_cmd अणु
	काष्ठा iwl_mic_keys mic_keys;
	काष्ठा iwl_p1k_cache tx;
	काष्ठा iwl_p1k_cache rx_uni[IWL_NUM_RX_P1K_CACHE];
	काष्ठा iwl_p1k_cache rx_multi[IWL_NUM_RX_P1K_CACHE];
	u8     reversed[2];
	__le32 sta_id;
पूर्ण __packed; /* WOWLAN_TKIP_SETTING_API_S_VER_2 */

#घोषणा IWL_KCK_MAX_SIZE	32
#घोषणा IWL_KEK_MAX_SIZE	32

काष्ठा iwl_wowlan_kek_kck_material_cmd_v2 अणु
	u8	kck[IWL_KCK_MAX_SIZE];
	u8	kek[IWL_KEK_MAX_SIZE];
	__le16	kck_len;
	__le16	kek_len;
	__le64	replay_ctr;
पूर्ण __packed; /* KEK_KCK_MATERIAL_API_S_VER_2 */

काष्ठा iwl_wowlan_kek_kck_material_cmd_v3 अणु
	u8	kck[IWL_KCK_MAX_SIZE];
	u8	kek[IWL_KEK_MAX_SIZE];
	__le16	kck_len;
	__le16	kek_len;
	__le64	replay_ctr;
	__le32  akm;
	__le32  gtk_cipher;
	__le32  igtk_cipher;
	__le32  bigtk_cipher;
पूर्ण __packed; /* KEK_KCK_MATERIAL_API_S_VER_3 */

#घोषणा RF_KILL_INDICATOR_FOR_WOWLAN	0x87

क्रमागत iwl_wowlan_rekey_status अणु
	IWL_WOWLAN_REKEY_POST_REKEY = 0,
	IWL_WOWLAN_REKEY_WHILE_REKEY = 1,
पूर्ण; /* WOWLAN_REKEY_STATUS_API_E_VER_1 */

क्रमागत iwl_wowlan_wakeup_reason अणु
	IWL_WOWLAN_WAKEUP_BY_NON_WIRELESS			= 0,
	IWL_WOWLAN_WAKEUP_BY_MAGIC_PACKET			= BIT(0),
	IWL_WOWLAN_WAKEUP_BY_PATTERN				= BIT(1),
	IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON	= BIT(2),
	IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH		= BIT(3),
	IWL_WOWLAN_WAKEUP_BY_GTK_REKEY_FAILURE			= BIT(4),
	IWL_WOWLAN_WAKEUP_BY_RFKILL_DEASSERTED			= BIT(5),
	IWL_WOWLAN_WAKEUP_BY_UCODE_ERROR			= BIT(6),
	IWL_WOWLAN_WAKEUP_BY_EAPOL_REQUEST			= BIT(7),
	IWL_WOWLAN_WAKEUP_BY_FOUR_WAY_HANDSHAKE			= BIT(8),
	IWL_WOWLAN_WAKEUP_BY_REM_WAKE_LINK_LOSS			= BIT(9),
	IWL_WOWLAN_WAKEUP_BY_REM_WAKE_SIGNATURE_TABLE		= BIT(10),
	IWL_WOWLAN_WAKEUP_BY_REM_WAKE_TCP_EXTERNAL		= BIT(11),
	IWL_WOWLAN_WAKEUP_BY_REM_WAKE_WAKEUP_PACKET		= BIT(12),
	IWL_WOWLAN_WAKEUP_BY_IOAC_MAGIC_PACKET			= BIT(13),
	IWL_WOWLAN_WAKEUP_BY_D3_WAKEUP_HOST_TIMER		= BIT(14),
	IWL_WOWLAN_WAKEUP_BY_RXFRAME_FILTERED_IN		= BIT(15),
	IWL_WOWLAN_WAKEUP_BY_BEACON_FILTERED_IN			= BIT(16),
	IWL_WAKEUP_BY_11W_UNPROTECTED_DEAUTH_OR_DISASSOC	= BIT(17),
	IWL_WAKEUP_BY_PATTERN_IPV4_TCP_SYN			= BIT(18),
	IWL_WAKEUP_BY_PATTERN_IPV4_TCP_SYN_WILDCARD		= BIT(19),
	IWL_WAKEUP_BY_PATTERN_IPV6_TCP_SYN			= BIT(20),
	IWL_WAKEUP_BY_PATTERN_IPV6_TCP_SYN_WILDCARD		= BIT(21),
पूर्ण; /* WOWLAN_WAKE_UP_REASON_API_E_VER_2 */

काष्ठा iwl_wowlan_gtk_status_v1 अणु
	u8 key_index;
	u8 reserved[3];
	u8 decrypt_key[16];
	u8 tkip_mic_key[8];
	काष्ठा iwl_wowlan_rsc_tsc_params_cmd_ver_2 rsc;
पूर्ण __packed; /* WOWLAN_GTK_MATERIAL_VER_1 */

#घोषणा WOWLAN_KEY_MAX_SIZE	32
#घोषणा WOWLAN_GTK_KEYS_NUM     2
#घोषणा WOWLAN_IGTK_KEYS_NUM	2

/**
 * काष्ठा iwl_wowlan_gtk_status - GTK status
 * @key: GTK material
 * @key_len: GTK legth, अगर set to 0, the key is not available
 * @key_flags: inक्रमmation about the key:
 *	bits[0:1]:  key index asचिन्हित by the AP
 *	bits[2:6]:  GTK index of the key in the पूर्णांकernal DB
 *	bit[7]:     Set अगरf this is the currently used GTK
 * @reserved: padding
 * @tkip_mic_key: TKIP RX MIC key
 * @rsc: TSC RSC counters
 */
काष्ठा iwl_wowlan_gtk_status अणु
	u8 key[WOWLAN_KEY_MAX_SIZE];
	u8 key_len;
	u8 key_flags;
	u8 reserved[2];
	u8 tkip_mic_key[8];
	काष्ठा iwl_wowlan_rsc_tsc_params_cmd_ver_2 rsc;
पूर्ण __packed; /* WOWLAN_GTK_MATERIAL_VER_2 */

#घोषणा IWL_WOWLAN_GTK_IDX_MASK		(BIT(0) | BIT(1))

/**
 * काष्ठा iwl_wowlan_igtk_status - IGTK status
 * @key: IGTK material
 * @ipn: the IGTK packet number (replay counter)
 * @key_len: IGTK length, अगर set to 0, the key is not available
 * @key_flags: inक्रमmation about the key:
 *	bits[0]:    key index asचिन्हित by the AP (0: index 4, 1: index 5)
 *	bits[1:5]:  IGTK index of the key in the पूर्णांकernal DB
 *	bit[6]:     Set अगरf this is the currently used IGTK
 */
काष्ठा iwl_wowlan_igtk_status अणु
	u8 key[WOWLAN_KEY_MAX_SIZE];
	u8 ipn[6];
	u8 key_len;
	u8 key_flags;
पूर्ण __packed; /* WOWLAN_IGTK_MATERIAL_VER_1 */

/**
 * काष्ठा iwl_wowlan_status_v6 - WoWLAN status
 * @gtk: GTK data
 * @replay_ctr: GTK rekey replay counter
 * @pattern_number: number of the matched pattern
 * @non_qos_seq_ctr: non-QoS sequence counter to use next
 * @qos_seq_ctr: QoS sequence counters to use next
 * @wakeup_reasons: wakeup reasons, see &क्रमागत iwl_wowlan_wakeup_reason
 * @num_of_gtk_rekeys: number of GTK rekeys
 * @transmitted_ndps: number of transmitted neighbor discovery packets
 * @received_beacons: number of received beacons
 * @wake_packet_length: wakeup packet length
 * @wake_packet_bufsize: wakeup packet buffer size
 * @wake_packet: wakeup packet
 */
काष्ठा iwl_wowlan_status_v6 अणु
	काष्ठा iwl_wowlan_gtk_status_v1 gtk;
	__le64 replay_ctr;
	__le16 pattern_number;
	__le16 non_qos_seq_ctr;
	__le16 qos_seq_ctr[8];
	__le32 wakeup_reasons;
	__le32 num_of_gtk_rekeys;
	__le32 transmitted_ndps;
	__le32 received_beacons;
	__le32 wake_packet_length;
	__le32 wake_packet_bufsize;
	u8 wake_packet[]; /* can be truncated from _length to _bufsize */
पूर्ण __packed; /* WOWLAN_STATUSES_API_S_VER_6 */

/**
 * काष्ठा iwl_wowlan_status - WoWLAN status
 * @gtk: GTK data
 * @igtk: IGTK data
 * @replay_ctr: GTK rekey replay counter
 * @pattern_number: number of the matched pattern
 * @non_qos_seq_ctr: non-QoS sequence counter to use next
 * @qos_seq_ctr: QoS sequence counters to use next
 * @wakeup_reasons: wakeup reasons, see &क्रमागत iwl_wowlan_wakeup_reason
 * @num_of_gtk_rekeys: number of GTK rekeys
 * @transmitted_ndps: number of transmitted neighbor discovery packets
 * @received_beacons: number of received beacons
 * @wake_packet_length: wakeup packet length
 * @wake_packet_bufsize: wakeup packet buffer size
 * @wake_packet: wakeup packet
 */
काष्ठा iwl_wowlan_status_v7 अणु
	काष्ठा iwl_wowlan_gtk_status gtk[WOWLAN_GTK_KEYS_NUM];
	काष्ठा iwl_wowlan_igtk_status igtk[WOWLAN_IGTK_KEYS_NUM];
	__le64 replay_ctr;
	__le16 pattern_number;
	__le16 non_qos_seq_ctr;
	__le16 qos_seq_ctr[8];
	__le32 wakeup_reasons;
	__le32 num_of_gtk_rekeys;
	__le32 transmitted_ndps;
	__le32 received_beacons;
	__le32 wake_packet_length;
	__le32 wake_packet_bufsize;
	u8 wake_packet[]; /* can be truncated from _length to _bufsize */
पूर्ण __packed; /* WOWLAN_STATUSES_API_S_VER_7 */

/**
 * काष्ठा iwl_wowlan_status_v9 - WoWLAN status (version 9)
 * @gtk: GTK data
 * @igtk: IGTK data
 * @replay_ctr: GTK rekey replay counter
 * @pattern_number: number of the matched pattern
 * @non_qos_seq_ctr: non-QoS sequence counter to use next
 * @qos_seq_ctr: QoS sequence counters to use next
 * @wakeup_reasons: wakeup reasons, see &क्रमागत iwl_wowlan_wakeup_reason
 * @num_of_gtk_rekeys: number of GTK rekeys
 * @transmitted_ndps: number of transmitted neighbor discovery packets
 * @received_beacons: number of received beacons
 * @wake_packet_length: wakeup packet length
 * @wake_packet_bufsize: wakeup packet buffer size
 * @tid_tear_करोwn: bit mask of tids whose BA sessions were बंदd
 *		   in suspend state
 * @reserved: unused
 * @wake_packet: wakeup packet
 */
काष्ठा iwl_wowlan_status_v9 अणु
	काष्ठा iwl_wowlan_gtk_status gtk[WOWLAN_GTK_KEYS_NUM];
	काष्ठा iwl_wowlan_igtk_status igtk[WOWLAN_IGTK_KEYS_NUM];
	__le64 replay_ctr;
	__le16 pattern_number;
	__le16 non_qos_seq_ctr;
	__le16 qos_seq_ctr[8];
	__le32 wakeup_reasons;
	__le32 num_of_gtk_rekeys;
	__le32 transmitted_ndps;
	__le32 received_beacons;
	__le32 wake_packet_length;
	__le32 wake_packet_bufsize;
	u8 tid_tear_करोwn;
	u8 reserved[3];
	u8 wake_packet[]; /* can be truncated from _length to _bufsize */
पूर्ण __packed; /* WOWLAN_STATUSES_API_S_VER_9 */

/**
 * काष्ठा iwl_wowlan_status - WoWLAN status
 * @gtk: GTK data
 * @igtk: IGTK data
 * @bigtk: BIGTK data
 * @replay_ctr: GTK rekey replay counter
 * @pattern_number: number of the matched pattern
 * @non_qos_seq_ctr: non-QoS sequence counter to use next
 * @qos_seq_ctr: QoS sequence counters to use next
 * @wakeup_reasons: wakeup reasons, see &क्रमागत iwl_wowlan_wakeup_reason
 * @num_of_gtk_rekeys: number of GTK rekeys
 * @tid_tear_करोwn: biपंचांगap of TIDs torn करोwn
 * @reserved: reserved
 * @received_beacons: number of received beacons
 * @wake_packet_length: wakeup packet length
 * @wake_packet_bufsize: wakeup packet buffer size
 * @tid_tear_करोwn: bit mask of tids whose BA sessions were बंदd
 *		   in suspend state
 * @wake_packet: wakeup packet
 */
काष्ठा iwl_wowlan_status अणु
	काष्ठा iwl_wowlan_gtk_status gtk[1];
	काष्ठा iwl_wowlan_igtk_status igtk[1];
	काष्ठा iwl_wowlan_igtk_status bigtk[WOWLAN_IGTK_KEYS_NUM];
	__le64 replay_ctr;
	__le16 pattern_number;
	__le16 non_qos_seq_ctr;
	__le16 qos_seq_ctr[8];
	__le32 wakeup_reasons;
	__le32 num_of_gtk_rekeys;
	u8 tid_tear_करोwn;
	u8 reserved[3];
	__le32 received_beacons;
	__le32 wake_packet_length;
	__le32 wake_packet_bufsize;
	u8 wake_packet[]; /* can be truncated from _length to _bufsize */
पूर्ण __packed; /* WOWLAN_STATUSES_API_S_VER_11 */

अटल अंतरभूत u8 iwlmvm_wowlan_gtk_idx(काष्ठा iwl_wowlan_gtk_status *gtk)
अणु
	वापस gtk->key_flags & IWL_WOWLAN_GTK_IDX_MASK;
पूर्ण

#घोषणा IWL_WOWLAN_TCP_MAX_PACKET_LEN		64
#घोषणा IWL_WOWLAN_REMOTE_WAKE_MAX_PACKET_LEN	128
#घोषणा IWL_WOWLAN_REMOTE_WAKE_MAX_TOKENS	2048

काष्ठा iwl_tcp_packet_info अणु
	__le16 tcp_pseuकरो_header_checksum;
	__le16 tcp_payload_length;
पूर्ण __packed; /* TCP_PACKET_INFO_API_S_VER_2 */

काष्ठा iwl_tcp_packet अणु
	काष्ठा iwl_tcp_packet_info info;
	u8 rx_mask[IWL_WOWLAN_MAX_PATTERN_LEN / 8];
	u8 data[IWL_WOWLAN_TCP_MAX_PACKET_LEN];
पूर्ण __packed; /* TCP_PROTOCOL_PACKET_API_S_VER_1 */

काष्ठा iwl_remote_wake_packet अणु
	काष्ठा iwl_tcp_packet_info info;
	u8 rx_mask[IWL_WOWLAN_MAX_PATTERN_LEN / 8];
	u8 data[IWL_WOWLAN_REMOTE_WAKE_MAX_PACKET_LEN];
पूर्ण __packed; /* TCP_PROTOCOL_PACKET_API_S_VER_1 */

काष्ठा iwl_wowlan_remote_wake_config अणु
	__le32 connection_max_समय; /* unused */
	/* TCP_PROTOCOL_CONFIG_API_S_VER_1 */
	u8 max_syn_retries;
	u8 max_data_retries;
	u8 tcp_syn_ack_समयout;
	u8 tcp_ack_समयout;

	काष्ठा iwl_tcp_packet syn_tx;
	काष्ठा iwl_tcp_packet synack_rx;
	काष्ठा iwl_tcp_packet keepalive_ack_rx;
	काष्ठा iwl_tcp_packet fin_tx;

	काष्ठा iwl_remote_wake_packet keepalive_tx;
	काष्ठा iwl_remote_wake_packet wake_rx;

	/* REMOTE_WAKE_OFFSET_INFO_API_S_VER_1 */
	u8 sequence_number_offset;
	u8 sequence_number_length;
	u8 token_offset;
	u8 token_length;
	/* REMOTE_WAKE_PROTOCOL_PARAMS_API_S_VER_1 */
	__le32 initial_sequence_number;
	__le16 keepalive_पूर्णांकerval;
	__le16 num_tokens;
	u8 tokens[IWL_WOWLAN_REMOTE_WAKE_MAX_TOKENS];
पूर्ण __packed; /* REMOTE_WAKE_CONFIG_API_S_VER_2 */

/* TODO: NetDetect API */

#पूर्ण_अगर /* __iwl_fw_api_d3_h__ */
