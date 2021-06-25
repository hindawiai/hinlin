<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_PORT_H
#घोषणा HINIC_PORT_H

#समावेश <linux/types.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/bitops.h>

#समावेश "hinic_dev.h"

#घोषणा HINIC_RSS_KEY_SIZE	40
#घोषणा HINIC_RSS_INसूची_SIZE	256
#घोषणा HINIC_PORT_STATS_VERSION	0
#घोषणा HINIC_FW_VERSION_NAME	16
#घोषणा HINIC_COMPILE_TIME_LEN	20
#घोषणा HINIC_MGMT_VERSION_MAX_LEN	32

काष्ठा hinic_version_info अणु
	u8 status;
	u8 version;
	u8 rsvd[6];

	u8 ver[HINIC_FW_VERSION_NAME];
	u8 समय[HINIC_COMPILE_TIME_LEN];
पूर्ण;

क्रमागत hinic_rx_mode अणु
	HINIC_RX_MODE_UC        = BIT(0),
	HINIC_RX_MODE_MC        = BIT(1),
	HINIC_RX_MODE_BC        = BIT(2),
	HINIC_RX_MODE_MC_ALL    = BIT(3),
	HINIC_RX_MODE_PROMISC   = BIT(4),
पूर्ण;

क्रमागत hinic_port_link_state अणु
	HINIC_LINK_STATE_DOWN,
	HINIC_LINK_STATE_UP,
पूर्ण;

क्रमागत hinic_port_state अणु
	HINIC_PORT_DISABLE      = 0,
	HINIC_PORT_ENABLE       = 3,
पूर्ण;

क्रमागत hinic_func_port_state अणु
	HINIC_FUNC_PORT_DISABLE = 0,
	HINIC_FUNC_PORT_ENABLE  = 2,
पूर्ण;

क्रमागत hinic_स्वतःneg_cap अणु
	HINIC_AUTONEG_UNSUPPORTED,
	HINIC_AUTONEG_SUPPORTED,
पूर्ण;

क्रमागत hinic_स्वतःneg_state अणु
	HINIC_AUTONEG_DISABLED,
	HINIC_AUTONEG_ACTIVE,
पूर्ण;

क्रमागत hinic_duplex अणु
	HINIC_DUPLEX_HALF,
	HINIC_DUPLEX_FULL,
पूर्ण;

क्रमागत hinic_speed अणु
	HINIC_SPEED_10MB_LINK = 0,
	HINIC_SPEED_100MB_LINK,
	HINIC_SPEED_1000MB_LINK,
	HINIC_SPEED_10GB_LINK,
	HINIC_SPEED_25GB_LINK,
	HINIC_SPEED_40GB_LINK,
	HINIC_SPEED_100GB_LINK,

	HINIC_SPEED_UNKNOWN = 0xFF,
पूर्ण;

क्रमागत hinic_link_mode अणु
	HINIC_10GE_BASE_KR = 0,
	HINIC_40GE_BASE_KR4 = 1,
	HINIC_40GE_BASE_CR4 = 2,
	HINIC_100GE_BASE_KR4 = 3,
	HINIC_100GE_BASE_CR4 = 4,
	HINIC_25GE_BASE_KR_S = 5,
	HINIC_25GE_BASE_CR_S = 6,
	HINIC_25GE_BASE_KR = 7,
	HINIC_25GE_BASE_CR = 8,
	HINIC_GE_BASE_KX = 9,
	HINIC_LINK_MODE_NUMBERS,

	HINIC_SUPPORTED_UNKNOWN = 0xFFFF,
पूर्ण;

क्रमागत hinic_port_type अणु
	HINIC_PORT_TP,		/* BASET */
	HINIC_PORT_AUI,
	HINIC_PORT_MII,
	HINIC_PORT_FIBRE,	/* OPTICAL */
	HINIC_PORT_BNC,
	HINIC_PORT_ELEC,
	HINIC_PORT_COPPER,	/* PORT_DA */
	HINIC_PORT_AOC,
	HINIC_PORT_BACKPLANE,
	HINIC_PORT_NONE = 0xEF,
	HINIC_PORT_OTHER = 0xFF,
पूर्ण;

क्रमागत hinic_valid_link_settings अणु
	HILINK_LINK_SET_SPEED = 0x1,
	HILINK_LINK_SET_AUTONEG = 0x2,
	HILINK_LINK_SET_FEC = 0x4,
पूर्ण;

क्रमागत hinic_tso_state अणु
	HINIC_TSO_DISABLE = 0,
	HINIC_TSO_ENABLE  = 1,
पूर्ण;

काष्ठा hinic_port_mac_cmd अणु
	u8              status;
	u8              version;
	u8              rsvd0[6];

	u16             func_idx;
	u16             vlan_id;
	u16             rsvd1;
	अचिन्हित अक्षर   mac[ETH_ALEN];
पूर्ण;

काष्ठा hinic_port_mtu_cmd अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     rsvd1;
	u32     mtu;
पूर्ण;

काष्ठा hinic_port_vlan_cmd अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     vlan_id;
पूर्ण;

काष्ठा hinic_port_rx_mode_cmd अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     rsvd;
	u32     rx_mode;
पूर्ण;

काष्ठा hinic_port_link_cmd अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u8      state;
	u8      rsvd1;
पूर्ण;

काष्ठा hinic_port_state_cmd अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u8      state;
	u8      rsvd1[3];
पूर्ण;

काष्ठा hinic_port_link_status अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_id;
	u8      link;
	u8      port_id;
पूर्ण;

काष्ठा hinic_cable_plug_event अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	plugged; /* 0: unplugged, 1: plugged */
	u8	port_id;
पूर्ण;

क्रमागत link_err_type अणु
	LINK_ERR_MODULE_UNRECOGENIZED,
	LINK_ERR_NUM,
पूर्ण;

काष्ठा hinic_link_err_event अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	err_type;
	u8	port_id;
पूर्ण;

काष्ठा hinic_port_func_state_cmd अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     rsvd1;
	u8      state;
	u8      rsvd2[3];
पूर्ण;

काष्ठा hinic_port_cap अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     rsvd1;
	u8      port_type;
	u8      स्वतःneg_cap;
	u8      स्वतःneg_state;
	u8      duplex;
	u8      speed;
	u8      rsvd2[3];
पूर्ण;

काष्ठा hinic_link_mode_cmd अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u16	supported;	/* 0xFFFF represents invalid value */
	u16	advertised;
पूर्ण;

काष्ठा hinic_speed_cmd अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	speed;
पूर्ण;

काष्ठा hinic_set_स्वतःneg_cmd अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	enable;	/* 1: enable , 0: disable */
पूर्ण;

काष्ठा hinic_link_ksettings_info अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;

	u32	valid_biपंचांगap;
	u32	speed;		/* क्रमागत nic_speed_level */
	u8	स्वतःneg;	/* 0 - off; 1 - on */
	u8	fec;		/* 0 - RSFEC; 1 - BASEFEC; 2 - NOFEC */
	u8	rsvd2[18];	/* reserved क्रम duplex, port, etc. */
पूर्ण;

काष्ठा hinic_tso_config अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u8	tso_en;
	u8	resv2[3];
पूर्ण;

काष्ठा hinic_checksum_offload अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u32	rx_csum_offload;
पूर्ण;

काष्ठा hinic_rq_num अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1[33];
	u32	num_rqs;
	u32	rq_depth;
पूर्ण;

काष्ठा hinic_lro_config अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u8	lro_ipv4_en;
	u8	lro_ipv6_en;
	u8	lro_max_wqe_num;
	u8	resv2[13];
पूर्ण;

काष्ठा hinic_lro_समयr अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u8	type;   /* 0: set समयr value, 1: get समयr value */
	u8	enable; /* when set lro समय, enable should be 1 */
	u16	rsvd1;
	u32	समयr;
पूर्ण;

काष्ठा hinic_vlan_cfg अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_id;
	u8      vlan_rx_offload;
	u8      rsvd1[5];
पूर्ण;

काष्ठा hinic_rss_ढाँचा_mgmt अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	cmd;
	u8	ढाँचा_id;
	u8	rsvd1[4];
पूर्ण;

काष्ठा hinic_rss_ढाँचा_key अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	ढाँचा_id;
	u8	rsvd1;
	u8	key[HINIC_RSS_KEY_SIZE];
पूर्ण;

काष्ठा hinic_rss_context_tbl अणु
	u32 group_index;
	u32 offset;
	u32 size;
	u32 rsvd;
	u32 ctx;
पूर्ण;

काष्ठा hinic_rss_context_table अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_id;
	u8      ढाँचा_id;
	u8      rsvd1;
	u32     context;
पूर्ण;

काष्ठा hinic_rss_indirect_tbl अणु
	u32 group_index;
	u32 offset;
	u32 size;
	u32 rsvd;
	u8 entry[HINIC_RSS_INसूची_SIZE];
पूर्ण;

काष्ठा hinic_rss_indir_table अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_id;
	u8      ढाँचा_id;
	u8      rsvd1;
	u8      indir[HINIC_RSS_INसूची_SIZE];
पूर्ण;

काष्ठा hinic_rss_key अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	ढाँचा_id;
	u8	rsvd1;
	u8	key[HINIC_RSS_KEY_SIZE];
पूर्ण;

काष्ठा hinic_rss_engine_type अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	ढाँचा_id;
	u8	hash_engine;
	u8	rsvd1[4];
पूर्ण;

काष्ठा hinic_rss_config अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	rss_en;
	u8	ढाँचा_id;
	u8	rq_priority_number;
	u8	rsvd1[11];
पूर्ण;

काष्ठा hinic_stats अणु
	अक्षर name[ETH_GSTRING_LEN];
	u32 size;
	पूर्णांक offset;
पूर्ण;

काष्ठा hinic_vport_stats अणु
	u64 tx_unicast_pkts_vport;
	u64 tx_unicast_bytes_vport;
	u64 tx_multicast_pkts_vport;
	u64 tx_multicast_bytes_vport;
	u64 tx_broadcast_pkts_vport;
	u64 tx_broadcast_bytes_vport;

	u64 rx_unicast_pkts_vport;
	u64 rx_unicast_bytes_vport;
	u64 rx_multicast_pkts_vport;
	u64 rx_multicast_bytes_vport;
	u64 rx_broadcast_pkts_vport;
	u64 rx_broadcast_bytes_vport;

	u64 tx_discard_vport;
	u64 rx_discard_vport;
	u64 tx_err_vport;
	u64 rx_err_vport;
पूर्ण;

काष्ठा hinic_phy_port_stats अणु
	u64 mac_rx_total_pkt_num;
	u64 mac_rx_total_oct_num;
	u64 mac_rx_bad_pkt_num;
	u64 mac_rx_bad_oct_num;
	u64 mac_rx_good_pkt_num;
	u64 mac_rx_good_oct_num;
	u64 mac_rx_uni_pkt_num;
	u64 mac_rx_multi_pkt_num;
	u64 mac_rx_broad_pkt_num;

	u64 mac_tx_total_pkt_num;
	u64 mac_tx_total_oct_num;
	u64 mac_tx_bad_pkt_num;
	u64 mac_tx_bad_oct_num;
	u64 mac_tx_good_pkt_num;
	u64 mac_tx_good_oct_num;
	u64 mac_tx_uni_pkt_num;
	u64 mac_tx_multi_pkt_num;
	u64 mac_tx_broad_pkt_num;

	u64 mac_rx_fragment_pkt_num;
	u64 mac_rx_undersize_pkt_num;
	u64 mac_rx_undermin_pkt_num;
	u64 mac_rx_64_oct_pkt_num;
	u64 mac_rx_65_127_oct_pkt_num;
	u64 mac_rx_128_255_oct_pkt_num;
	u64 mac_rx_256_511_oct_pkt_num;
	u64 mac_rx_512_1023_oct_pkt_num;
	u64 mac_rx_1024_1518_oct_pkt_num;
	u64 mac_rx_1519_2047_oct_pkt_num;
	u64 mac_rx_2048_4095_oct_pkt_num;
	u64 mac_rx_4096_8191_oct_pkt_num;
	u64 mac_rx_8192_9216_oct_pkt_num;
	u64 mac_rx_9217_12287_oct_pkt_num;
	u64 mac_rx_12288_16383_oct_pkt_num;
	u64 mac_rx_1519_max_bad_pkt_num;
	u64 mac_rx_1519_max_good_pkt_num;
	u64 mac_rx_oversize_pkt_num;
	u64 mac_rx_jabber_pkt_num;

	u64 mac_rx_छोड़ो_num;
	u64 mac_rx_pfc_pkt_num;
	u64 mac_rx_pfc_pri0_pkt_num;
	u64 mac_rx_pfc_pri1_pkt_num;
	u64 mac_rx_pfc_pri2_pkt_num;
	u64 mac_rx_pfc_pri3_pkt_num;
	u64 mac_rx_pfc_pri4_pkt_num;
	u64 mac_rx_pfc_pri5_pkt_num;
	u64 mac_rx_pfc_pri6_pkt_num;
	u64 mac_rx_pfc_pri7_pkt_num;
	u64 mac_rx_control_pkt_num;
	u64 mac_rx_y1731_pkt_num;
	u64 mac_rx_sym_err_pkt_num;
	u64 mac_rx_fcs_err_pkt_num;
	u64 mac_rx_send_app_good_pkt_num;
	u64 mac_rx_send_app_bad_pkt_num;

	u64 mac_tx_fragment_pkt_num;
	u64 mac_tx_undersize_pkt_num;
	u64 mac_tx_undermin_pkt_num;
	u64 mac_tx_64_oct_pkt_num;
	u64 mac_tx_65_127_oct_pkt_num;
	u64 mac_tx_128_255_oct_pkt_num;
	u64 mac_tx_256_511_oct_pkt_num;
	u64 mac_tx_512_1023_oct_pkt_num;
	u64 mac_tx_1024_1518_oct_pkt_num;
	u64 mac_tx_1519_2047_oct_pkt_num;
	u64 mac_tx_2048_4095_oct_pkt_num;
	u64 mac_tx_4096_8191_oct_pkt_num;
	u64 mac_tx_8192_9216_oct_pkt_num;
	u64 mac_tx_9217_12287_oct_pkt_num;
	u64 mac_tx_12288_16383_oct_pkt_num;
	u64 mac_tx_1519_max_bad_pkt_num;
	u64 mac_tx_1519_max_good_pkt_num;
	u64 mac_tx_oversize_pkt_num;
	u64 mac_tx_jabber_pkt_num;

	u64 mac_tx_छोड़ो_num;
	u64 mac_tx_pfc_pkt_num;
	u64 mac_tx_pfc_pri0_pkt_num;
	u64 mac_tx_pfc_pri1_pkt_num;
	u64 mac_tx_pfc_pri2_pkt_num;
	u64 mac_tx_pfc_pri3_pkt_num;
	u64 mac_tx_pfc_pri4_pkt_num;
	u64 mac_tx_pfc_pri5_pkt_num;
	u64 mac_tx_pfc_pri6_pkt_num;
	u64 mac_tx_pfc_pri7_pkt_num;
	u64 mac_tx_control_pkt_num;
	u64 mac_tx_y1731_pkt_num;
	u64 mac_tx_1588_pkt_num;
	u64 mac_tx_err_all_pkt_num;
	u64 mac_tx_from_app_good_pkt_num;
	u64 mac_tx_from_app_bad_pkt_num;

	u64 mac_rx_higig2_ext_pkt_num;
	u64 mac_rx_higig2_message_pkt_num;
	u64 mac_rx_higig2_error_pkt_num;
	u64 mac_rx_higig2_cpu_ctrl_pkt_num;
	u64 mac_rx_higig2_unicast_pkt_num;
	u64 mac_rx_higig2_broadcast_pkt_num;
	u64 mac_rx_higig2_l2_multicast_pkt_num;
	u64 mac_rx_higig2_l3_multicast_pkt_num;

	u64 mac_tx_higig2_message_pkt_num;
	u64 mac_tx_higig2_ext_pkt_num;
	u64 mac_tx_higig2_cpu_ctrl_pkt_num;
	u64 mac_tx_higig2_unicast_pkt_num;
	u64 mac_tx_higig2_broadcast_pkt_num;
	u64 mac_tx_higig2_l2_multicast_pkt_num;
	u64 mac_tx_higig2_l3_multicast_pkt_num;
पूर्ण;

काष्ठा hinic_port_stats_info अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u32	stats_version;
	u32	stats_size;
पूर्ण;

काष्ठा hinic_port_stats अणु
	u8 status;
	u8 version;
	u8 rsvd[6];

	काष्ठा hinic_phy_port_stats stats;
पूर्ण;

काष्ठा hinic_cmd_vport_stats अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	काष्ठा hinic_vport_stats stats;
पूर्ण;

काष्ठा hinic_tx_rate_cfg_max_min अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u32	min_rate;
	u32	max_rate;
	u8	rsvd2[8];
पूर्ण;

काष्ठा hinic_tx_rate_cfg अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u32	tx_rate;
पूर्ण;

क्रमागत nic_speed_level अणु
	LINK_SPEED_10MB = 0,
	LINK_SPEED_100MB,
	LINK_SPEED_1GB,
	LINK_SPEED_10GB,
	LINK_SPEED_25GB,
	LINK_SPEED_40GB,
	LINK_SPEED_100GB,
	LINK_SPEED_LEVELS,
पूर्ण;

काष्ठा hinic_spoofchk_set अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u8	state;
	u8	rsvd1;
	u16	func_id;
पूर्ण;

काष्ठा hinic_छोड़ो_config अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	rsvd1;
	u32	स्वतः_neg;
	u32	rx_छोड़ो;
	u32	tx_छोड़ो;
पूर्ण;

काष्ठा hinic_set_pfc अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u8	pfc_en;
	u8	pfc_biपंचांगap;
	u8	rsvd1[4];
पूर्ण;

/* get or set loopback mode, need to modअगरy by base API */
#घोषणा HINIC_INTERNAL_LP_MODE			5
#घोषणा LOOP_MODE_MIN				1
#घोषणा LOOP_MODE_MAX				6

काष्ठा hinic_port_loopback अणु
	u8	status;
	u8	version;
	u8	rsvd[6];

	u32	mode;
	u32	en;
पूर्ण;

काष्ठा hinic_led_info अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u8	port;
	u8	type;
	u8	mode;
	u8	reset;
पूर्ण;

#घोषणा STD_SFP_INFO_MAX_SIZE	640

काष्ठा hinic_cmd_get_light_module_असल अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	u8 port_id;
	u8 असल_status; /* 0:present, 1:असलent */
	u8 rsv[2];
पूर्ण;

#घोषणा STD_SFP_INFO_MAX_SIZE	640

काष्ठा hinic_cmd_get_std_sfp_info अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	u8 port_id;
	u8 wire_type;
	u16 eeprom_len;
	u32 rsvd;
	u8 sfp_info[STD_SFP_INFO_MAX_SIZE];
पूर्ण;

काष्ठा hinic_cmd_update_fw अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	काष्ठा अणु
		u32 SL:1;
		u32 SF:1;
		u32 flag:1;
		u32 reserved:13;
		u32 fragment_len:16;
	पूर्ण ctl_info;

	काष्ठा अणु
		u32 FW_section_CRC;
		u32 FW_section_type;
	पूर्ण section_info;

	u32 total_len;
	u32 setion_total_len;
	u32 fw_section_version;
	u32 section_offset;
	u32 data[384];
पूर्ण;

पूर्णांक hinic_port_add_mac(काष्ठा hinic_dev *nic_dev, स्थिर u8 *addr,
		       u16 vlan_id);

पूर्णांक hinic_port_del_mac(काष्ठा hinic_dev *nic_dev, स्थिर u8 *addr,
		       u16 vlan_id);

पूर्णांक hinic_port_get_mac(काष्ठा hinic_dev *nic_dev, u8 *addr);

पूर्णांक hinic_port_set_mtu(काष्ठा hinic_dev *nic_dev, पूर्णांक new_mtu);

पूर्णांक hinic_port_add_vlan(काष्ठा hinic_dev *nic_dev, u16 vlan_id);

पूर्णांक hinic_port_del_vlan(काष्ठा hinic_dev *nic_dev, u16 vlan_id);

पूर्णांक hinic_port_set_rx_mode(काष्ठा hinic_dev *nic_dev, u32 rx_mode);

पूर्णांक hinic_port_link_state(काष्ठा hinic_dev *nic_dev,
			  क्रमागत hinic_port_link_state *link_state);

पूर्णांक hinic_port_set_state(काष्ठा hinic_dev *nic_dev,
			 क्रमागत hinic_port_state state);

पूर्णांक hinic_port_set_func_state(काष्ठा hinic_dev *nic_dev,
			      क्रमागत hinic_func_port_state state);

पूर्णांक hinic_port_get_cap(काष्ठा hinic_dev *nic_dev,
		       काष्ठा hinic_port_cap *port_cap);

पूर्णांक hinic_set_max_qnum(काष्ठा hinic_dev *nic_dev, u8 num_rqs);

पूर्णांक hinic_port_set_tso(काष्ठा hinic_dev *nic_dev, क्रमागत hinic_tso_state state);

पूर्णांक hinic_set_rx_csum_offload(काष्ठा hinic_dev *nic_dev, u32 en);

पूर्णांक hinic_set_rx_lro_state(काष्ठा hinic_dev *nic_dev, u8 lro_en,
			   u32 lro_समयr, u32 wqe_num);

पूर्णांक hinic_set_rss_type(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
		       काष्ठा hinic_rss_type rss_type);

पूर्णांक hinic_rss_set_indir_tbl(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
			    स्थिर u32 *indir_table);

पूर्णांक hinic_rss_set_ढाँचा_tbl(काष्ठा hinic_dev *nic_dev, u32 ढाँचा_id,
			       स्थिर u8 *temp);

पूर्णांक hinic_rss_set_hash_engine(काष्ठा hinic_dev *nic_dev, u8 ढाँचा_id,
			      u8 type);

पूर्णांक hinic_rss_cfg(काष्ठा hinic_dev *nic_dev, u8 rss_en, u8 ढाँचा_id);

पूर्णांक hinic_rss_ढाँचा_alloc(काष्ठा hinic_dev *nic_dev, u8 *पंचांगpl_idx);

पूर्णांक hinic_rss_ढाँचा_मुक्त(काष्ठा hinic_dev *nic_dev, u8 पंचांगpl_idx);

व्योम hinic_set_ethtool_ops(काष्ठा net_device *netdev);

पूर्णांक hinic_get_rss_type(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
		       काष्ठा hinic_rss_type *rss_type);

पूर्णांक hinic_rss_get_indir_tbl(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
			    u32 *indir_table);

पूर्णांक hinic_rss_get_ढाँचा_tbl(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
			       u8 *temp);

पूर्णांक hinic_rss_get_hash_engine(काष्ठा hinic_dev *nic_dev, u8 पंचांगpl_idx,
			      u8 *type);

पूर्णांक hinic_get_phy_port_stats(काष्ठा hinic_dev *nic_dev,
			     काष्ठा hinic_phy_port_stats *stats);

पूर्णांक hinic_get_vport_stats(काष्ठा hinic_dev *nic_dev,
			  काष्ठा hinic_vport_stats *stats);

पूर्णांक hinic_set_rx_vlan_offload(काष्ठा hinic_dev *nic_dev, u8 en);

पूर्णांक hinic_get_mgmt_version(काष्ठा hinic_dev *nic_dev, u8 *mgmt_ver);

पूर्णांक hinic_set_link_settings(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_link_ksettings_info *info);

पूर्णांक hinic_get_link_mode(काष्ठा hinic_hwdev *hwdev,
			काष्ठा hinic_link_mode_cmd *link_mode);

पूर्णांक hinic_set_स्वतःneg(काष्ठा hinic_hwdev *hwdev, bool enable);

पूर्णांक hinic_set_speed(काष्ठा hinic_hwdev *hwdev, क्रमागत nic_speed_level speed);

पूर्णांक hinic_get_hw_छोड़ो_info(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_छोड़ो_config *छोड़ो_info);

पूर्णांक hinic_set_hw_छोड़ो_info(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_छोड़ो_config *छोड़ो_info);

पूर्णांक hinic_dcb_set_pfc(काष्ठा hinic_hwdev *hwdev, u8 pfc_en, u8 pfc_biपंचांगap);

पूर्णांक hinic_set_loopback_mode(काष्ठा hinic_hwdev *hwdev, u32 mode, u32 enable);

क्रमागत hinic_led_mode अणु
	HINIC_LED_MODE_ON,
	HINIC_LED_MODE_OFF,
	HINIC_LED_MODE_FORCE_1HZ,
	HINIC_LED_MODE_FORCE_2HZ,
	HINIC_LED_MODE_FORCE_4HZ,
	HINIC_LED_MODE_1HZ,
	HINIC_LED_MODE_2HZ,
	HINIC_LED_MODE_4HZ,
	HINIC_LED_MODE_INVALID,
पूर्ण;

क्रमागत hinic_led_type अणु
	HINIC_LED_TYPE_LINK,
	HINIC_LED_TYPE_LOW_SPEED,
	HINIC_LED_TYPE_HIGH_SPEED,
	HINIC_LED_TYPE_INVALID,
पूर्ण;

पूर्णांक hinic_reset_led_status(काष्ठा hinic_hwdev *hwdev, u8 port);

पूर्णांक hinic_set_led_status(काष्ठा hinic_hwdev *hwdev, u8 port,
			 क्रमागत hinic_led_type type, क्रमागत hinic_led_mode mode);

पूर्णांक hinic_get_sfp_type(काष्ठा hinic_hwdev *hwdev, u8 *data0, u8 *data1);

पूर्णांक hinic_get_sfp_eeprom(काष्ठा hinic_hwdev *hwdev, u8 *data, u16 *len);

पूर्णांक hinic_खोलो(काष्ठा net_device *netdev);

पूर्णांक hinic_बंद(काष्ठा net_device *netdev);

#पूर्ण_अगर
