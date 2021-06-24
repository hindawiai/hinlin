<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित __ETH_COMMON__
#घोषणा __ETH_COMMON__

/********************/
/* ETH FW CONSTANTS */
/********************/

#घोषणा ETH_HSI_VER_MAJOR		3
#घोषणा ETH_HSI_VER_MINOR		11

#घोषणा ETH_HSI_VER_NO_PKT_LEN_TUNN         5
/* Maximum number of pinned L2 connections (CIDs) */
#घोषणा ETH_PINNED_CONN_MAX_NUM             32

#घोषणा ETH_CACHE_LINE_SIZE		64
#घोषणा ETH_RX_CQE_GAP			32
#घोषणा ETH_MAX_RAMROD_PER_CON		8
#घोषणा ETH_TX_BD_PAGE_SIZE_BYTES	4096
#घोषणा ETH_RX_BD_PAGE_SIZE_BYTES	4096
#घोषणा ETH_RX_CQE_PAGE_SIZE_BYTES	4096
#घोषणा ETH_RX_NUM_NEXT_PAGE_BDS	2

#घोषणा ETH_MAX_TUNN_LSO_INNER_IPV4_OFFSET	253
#घोषणा ETH_MAX_TUNN_LSO_INNER_IPV6_OFFSET	251

#घोषणा ETH_TX_MIN_BDS_PER_NON_LSO_PKT			1
#घोषणा ETH_TX_MAX_BDS_PER_NON_LSO_PACKET		18
#घोषणा ETH_TX_MAX_BDS_PER_LSO_PACKET			255
#घोषणा ETH_TX_MAX_LSO_HDR_NBD				4
#घोषणा ETH_TX_MIN_BDS_PER_LSO_PKT			3
#घोषणा ETH_TX_MIN_BDS_PER_TUNN_IPV6_WITH_EXT_PKT	3
#घोषणा ETH_TX_MIN_BDS_PER_IPV6_WITH_EXT_PKT		2
#घोषणा ETH_TX_MIN_BDS_PER_PKT_W_LOOPBACK_MODE		2
#घोषणा ETH_TX_MIN_BDS_PER_PKT_W_VPORT_FORWARDING	4
#घोषणा ETH_TX_MAX_NON_LSO_PKT_LEN		(9700 - (4 + 4 + 12 + 8))
#घोषणा ETH_TX_MAX_LSO_HDR_BYTES			510
#घोषणा ETH_TX_LSO_WINDOW_BDS_NUM			(18 - 1)
#घोषणा ETH_TX_LSO_WINDOW_MIN_LEN			9700
#घोषणा ETH_TX_MAX_LSO_PAYLOAD_LEN			0xFE000
#घोषणा ETH_TX_NUM_SAME_AS_LAST_ENTRIES			320
#घोषणा ETH_TX_INACTIVE_SAME_AS_LAST			0xFFFF

#घोषणा ETH_NUM_STATISTIC_COUNTERS			MAX_NUM_VPORTS
#घोषणा ETH_NUM_STATISTIC_COUNTERS_DOUBLE_VF_ZONE \
	(ETH_NUM_STATISTIC_COUNTERS - MAX_NUM_VFS / 2)
#घोषणा ETH_NUM_STATISTIC_COUNTERS_QUAD_VF_ZONE \
	(ETH_NUM_STATISTIC_COUNTERS - 3 * MAX_NUM_VFS / 4)

#घोषणा ETH_RX_MAX_BUFF_PER_PKT		5
#घोषणा ETH_RX_BD_THRESHOLD             16

/* Num of MAC/VLAN filters */
#घोषणा ETH_NUM_MAC_FILTERS		512
#घोषणा ETH_NUM_VLAN_FILTERS		512

/* Approx. multicast स्थिरants */
#घोषणा ETH_MULTICAST_BIN_FROM_MAC_SEED	0
#घोषणा ETH_MULTICAST_MAC_BINS		256
#घोषणा ETH_MULTICAST_MAC_BINS_IN_REGS	(ETH_MULTICAST_MAC_BINS / 32)

/* Ethernet vport update स्थिरants */
#घोषणा ETH_FILTER_RULES_COUNT		10
#घोषणा ETH_RSS_IND_TABLE_ENTRIES_NUM	128
#घोषणा ETH_RSS_KEY_SIZE_REGS		10
#घोषणा ETH_RSS_ENGINE_NUM_K2		207
#घोषणा ETH_RSS_ENGINE_NUM_BB		127

/* TPA स्थिरants */
#घोषणा ETH_TPA_MAX_AGGS_NUM                64
#घोषणा ETH_TPA_CQE_START_BW_LEN_LIST_SIZE  2
#घोषणा ETH_TPA_CQE_CONT_LEN_LIST_SIZE      6
#घोषणा ETH_TPA_CQE_END_LEN_LIST_SIZE       4

/* Control frame check स्थिरants */
#घोषणा ETH_CTL_FRAME_ETH_TYPE_NUM        4

/* GFS स्थिरants */
#घोषणा ETH_GFT_TRASHCAN_VPORT         0x1FF	/* GFT drop flow vport number */

/* Destination port mode */
क्रमागत dst_port_mode अणु
	DST_PORT_PHY,
	DST_PORT_LOOPBACK,
	DST_PORT_PHY_LOOPBACK,
	DST_PORT_DROP,
	MAX_DST_PORT_MODE
पूर्ण;

/* Ethernet address type */
क्रमागत eth_addr_type अणु
	BROADCAST_ADDRESS,
	MULTICAST_ADDRESS,
	UNICAST_ADDRESS,
	UNKNOWN_ADDRESS,
	MAX_ETH_ADDR_TYPE
पूर्ण;

काष्ठा eth_tx_1st_bd_flags अणु
	u8 bitfields;
#घोषणा ETH_TX_1ST_BD_FLAGS_START_BD_MASK		0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_START_BD_SHIFT		0
#घोषणा ETH_TX_1ST_BD_FLAGS_FORCE_VLAN_MODE_MASK	0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_FORCE_VLAN_MODE_SHIFT	1
#घोषणा ETH_TX_1ST_BD_FLAGS_IP_CSUM_MASK		0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_IP_CSUM_SHIFT		2
#घोषणा ETH_TX_1ST_BD_FLAGS_L4_CSUM_MASK		0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_L4_CSUM_SHIFT		3
#घोषणा ETH_TX_1ST_BD_FLAGS_VLAN_INSERTION_MASK		0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_VLAN_INSERTION_SHIFT	4
#घोषणा ETH_TX_1ST_BD_FLAGS_LSO_MASK			0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_LSO_SHIFT			5
#घोषणा ETH_TX_1ST_BD_FLAGS_TUNN_IP_CSUM_MASK		0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_TUNN_IP_CSUM_SHIFT		6
#घोषणा ETH_TX_1ST_BD_FLAGS_TUNN_L4_CSUM_MASK		0x1
#घोषणा ETH_TX_1ST_BD_FLAGS_TUNN_L4_CSUM_SHIFT		7
पूर्ण;

/* The parsing inक्रमmation data fo rthe first tx bd of a given packet */
काष्ठा eth_tx_data_1st_bd अणु
	__le16 vlan;
	u8 nbds;
	काष्ठा eth_tx_1st_bd_flags bd_flags;
	__le16 bitfields;
#घोषणा ETH_TX_DATA_1ST_BD_TUNN_FLAG_MASK	0x1
#घोषणा ETH_TX_DATA_1ST_BD_TUNN_FLAG_SHIFT	0
#घोषणा ETH_TX_DATA_1ST_BD_RESERVED0_MASK	0x1
#घोषणा ETH_TX_DATA_1ST_BD_RESERVED0_SHIFT	1
#घोषणा ETH_TX_DATA_1ST_BD_PKT_LEN_MASK		0x3FFF
#घोषणा ETH_TX_DATA_1ST_BD_PKT_LEN_SHIFT	2
पूर्ण;

/* The parsing inक्रमmation data क्रम the second tx bd of a given packet */
काष्ठा eth_tx_data_2nd_bd अणु
	__le16 tunn_ip_size;
	__le16	bitfields1;
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_INNER_L2_HDR_SIZE_W_MASK	0xF
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_INNER_L2_HDR_SIZE_W_SHIFT	0
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_INNER_ETH_TYPE_MASK		0x3
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_INNER_ETH_TYPE_SHIFT		4
#घोषणा ETH_TX_DATA_2ND_BD_DST_PORT_MODE_MASK			0x3
#घोषणा ETH_TX_DATA_2ND_BD_DST_PORT_MODE_SHIFT			6
#घोषणा ETH_TX_DATA_2ND_BD_START_BD_MASK			0x1
#घोषणा ETH_TX_DATA_2ND_BD_START_BD_SHIFT			8
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_TYPE_MASK			0x3
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_TYPE_SHIFT			9
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_INNER_IPV6_MASK			0x1
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_INNER_IPV6_SHIFT		11
#घोषणा ETH_TX_DATA_2ND_BD_IPV6_EXT_MASK			0x1
#घोषणा ETH_TX_DATA_2ND_BD_IPV6_EXT_SHIFT			12
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_IPV6_EXT_MASK			0x1
#घोषणा ETH_TX_DATA_2ND_BD_TUNN_IPV6_EXT_SHIFT			13
#घोषणा ETH_TX_DATA_2ND_BD_L4_UDP_MASK				0x1
#घोषणा ETH_TX_DATA_2ND_BD_L4_UDP_SHIFT				14
#घोषणा ETH_TX_DATA_2ND_BD_L4_PSEUDO_CSUM_MODE_MASK		0x1
#घोषणा ETH_TX_DATA_2ND_BD_L4_PSEUDO_CSUM_MODE_SHIFT		15
	__le16 bitfields2;
#घोषणा ETH_TX_DATA_2ND_BD_L4_HDR_START_OFFSET_W_MASK		0x1FFF
#घोषणा ETH_TX_DATA_2ND_BD_L4_HDR_START_OFFSET_W_SHIFT		0
#घोषणा ETH_TX_DATA_2ND_BD_RESERVED0_MASK			0x7
#घोषणा ETH_TX_DATA_2ND_BD_RESERVED0_SHIFT			13
पूर्ण;

/* Firmware data क्रम L2-EDPM packet */
काष्ठा eth_edpm_fw_data अणु
	काष्ठा eth_tx_data_1st_bd data_1st_bd;
	काष्ठा eth_tx_data_2nd_bd data_2nd_bd;
	__le32 reserved;
पूर्ण;

/* Tunneling parsing flags */
काष्ठा eth_tunnel_parsing_flags अणु
	u8 flags;
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_TYPE_MASK		0x3
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_TYPE_SHIFT		0
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_TENन_अंकT_ID_EXIST_MASK	0x1
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_TENन_अंकT_ID_EXIST_SHIFT	2
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_NEXT_PROTOCOL_MASK	0x3
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_NEXT_PROTOCOL_SHIFT	3
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_FIRSTHDRIPMATCH_MASK	0x1
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_FIRSTHDRIPMATCH_SHIFT	5
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_MASK	0x1
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_SHIFT	6
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_IPV4_OPTIONS_MASK	0x1
#घोषणा	ETH_TUNNEL_PARSING_FLAGS_IPV4_OPTIONS_SHIFT	7
पूर्ण;

/* PMD flow control bits */
काष्ठा eth_pmd_flow_flags अणु
	u8 flags;
#घोषणा ETH_PMD_FLOW_FLAGS_VALID_MASK		0x1
#घोषणा ETH_PMD_FLOW_FLAGS_VALID_SHIFT		0
#घोषणा ETH_PMD_FLOW_FLAGS_TOGGLE_MASK		0x1
#घोषणा ETH_PMD_FLOW_FLAGS_TOGGLE_SHIFT		1
#घोषणा ETH_PMD_FLOW_FLAGS_RESERVED_MASK	0x3F
#घोषणा ETH_PMD_FLOW_FLAGS_RESERVED_SHIFT	2
पूर्ण;

/* Regular ETH Rx FP CQE */
काष्ठा eth_fast_path_rx_reg_cqe अणु
	u8 type;
	u8 bitfields;
#घोषणा ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE_MASK	0x7
#घोषणा ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE_SHIFT	0
#घोषणा ETH_FAST_PATH_RX_REG_CQE_TC_MASK		0xF
#घोषणा ETH_FAST_PATH_RX_REG_CQE_TC_SHIFT		3
#घोषणा ETH_FAST_PATH_RX_REG_CQE_RESERVED0_MASK		0x1
#घोषणा ETH_FAST_PATH_RX_REG_CQE_RESERVED0_SHIFT	7
	__le16 pkt_len;
	काष्ठा parsing_and_err_flags pars_flags;
	__le16 vlan_tag;
	__le32 rss_hash;
	__le16 len_on_first_bd;
	u8 placement_offset;
	काष्ठा eth_tunnel_parsing_flags tunnel_pars_flags;
	u8 bd_num;
	u8 reserved;
	__le16 reserved2;
	__le32 flow_id_or_resource_id;
	u8 reserved1[7];
	काष्ठा eth_pmd_flow_flags pmd_flags;
पूर्ण;

/* TPA-जारी ETH Rx FP CQE */
काष्ठा eth_fast_path_rx_tpa_cont_cqe अणु
	u8 type;
	u8 tpa_agg_index;
	__le16 len_list[ETH_TPA_CQE_CONT_LEN_LIST_SIZE];
	u8 reserved;
	u8 reserved1;
	__le16 reserved2[ETH_TPA_CQE_CONT_LEN_LIST_SIZE];
	u8 reserved3[3];
	काष्ठा eth_pmd_flow_flags pmd_flags;
पूर्ण;

/* TPA-end ETH Rx FP CQE */
काष्ठा eth_fast_path_rx_tpa_end_cqe अणु
	u8 type;
	u8 tpa_agg_index;
	__le16 total_packet_len;
	u8 num_of_bds;
	u8 end_reason;
	__le16 num_of_coalesced_segs;
	__le32 ts_delta;
	__le16 len_list[ETH_TPA_CQE_END_LEN_LIST_SIZE];
	__le16 reserved3[ETH_TPA_CQE_END_LEN_LIST_SIZE];
	__le16 reserved1;
	u8 reserved2;
	काष्ठा eth_pmd_flow_flags pmd_flags;
पूर्ण;

/* TPA-start ETH Rx FP CQE */
काष्ठा eth_fast_path_rx_tpa_start_cqe अणु
	u8 type;
	u8 bitfields;
#घोषणा ETH_FAST_PATH_RX_TPA_START_CQE_RSS_HASH_TYPE_MASK	0x7
#घोषणा ETH_FAST_PATH_RX_TPA_START_CQE_RSS_HASH_TYPE_SHIFT	0
#घोषणा ETH_FAST_PATH_RX_TPA_START_CQE_TC_MASK			0xF
#घोषणा ETH_FAST_PATH_RX_TPA_START_CQE_TC_SHIFT			3
#घोषणा ETH_FAST_PATH_RX_TPA_START_CQE_RESERVED0_MASK		0x1
#घोषणा ETH_FAST_PATH_RX_TPA_START_CQE_RESERVED0_SHIFT		7
	__le16 seg_len;
	काष्ठा parsing_and_err_flags pars_flags;
	__le16 vlan_tag;
	__le32 rss_hash;
	__le16 len_on_first_bd;
	u8 placement_offset;
	काष्ठा eth_tunnel_parsing_flags tunnel_pars_flags;
	u8 tpa_agg_index;
	u8 header_len;
	__le16 bw_ext_bd_len_list[ETH_TPA_CQE_START_BW_LEN_LIST_SIZE];
	__le16 reserved2;
	__le32 flow_id_or_resource_id;
	u8 reserved[3];
	काष्ठा eth_pmd_flow_flags pmd_flags;
पूर्ण;

/* The L4 pseuकरो checksum mode क्रम Ethernet */
क्रमागत eth_l4_pseuकरो_checksum_mode अणु
	ETH_L4_PSEUDO_CSUM_CORRECT_LENGTH,
	ETH_L4_PSEUDO_CSUM_ZERO_LENGTH,
	MAX_ETH_L4_PSEUDO_CHECKSUM_MODE
पूर्ण;

काष्ठा eth_rx_bd अणु
	काष्ठा regpair addr;
पूर्ण;

/* Regular ETH Rx SP CQE */
काष्ठा eth_slow_path_rx_cqe अणु
	u8 type;
	u8 ramrod_cmd_id;
	u8 error_flag;
	u8 reserved[25];
	__le16 echo;
	u8 reserved1;
	काष्ठा eth_pmd_flow_flags pmd_flags;
पूर्ण;

/* Union क्रम all ETH Rx CQE types */
जोड़ eth_rx_cqe अणु
	काष्ठा eth_fast_path_rx_reg_cqe fast_path_regular;
	काष्ठा eth_fast_path_rx_tpa_start_cqe fast_path_tpa_start;
	काष्ठा eth_fast_path_rx_tpa_cont_cqe fast_path_tpa_cont;
	काष्ठा eth_fast_path_rx_tpa_end_cqe fast_path_tpa_end;
	काष्ठा eth_slow_path_rx_cqe slow_path;
पूर्ण;

/* ETH Rx CQE type */
क्रमागत eth_rx_cqe_type अणु
	ETH_RX_CQE_TYPE_UNUSED,
	ETH_RX_CQE_TYPE_REGULAR,
	ETH_RX_CQE_TYPE_SLOW_PATH,
	ETH_RX_CQE_TYPE_TPA_START,
	ETH_RX_CQE_TYPE_TPA_CONT,
	ETH_RX_CQE_TYPE_TPA_END,
	MAX_ETH_RX_CQE_TYPE
पूर्ण;

काष्ठा eth_rx_pmd_cqe अणु
	जोड़ eth_rx_cqe cqe;
	u8 reserved[ETH_RX_CQE_GAP];
पूर्ण;

क्रमागत eth_rx_tunn_type अणु
	ETH_RX_NO_TUNN,
	ETH_RX_TUNN_GENEVE,
	ETH_RX_TUNN_GRE,
	ETH_RX_TUNN_VXLAN,
	MAX_ETH_RX_TUNN_TYPE
पूर्ण;

/* Aggregation end reason. */
क्रमागत eth_tpa_end_reason अणु
	ETH_AGG_END_UNUSED,
	ETH_AGG_END_SP_UPDATE,
	ETH_AGG_END_MAX_LEN,
	ETH_AGG_END_LAST_SEG,
	ETH_AGG_END_TIMEOUT,
	ETH_AGG_END_NOT_CONSISTENT,
	ETH_AGG_END_OUT_OF_ORDER,
	ETH_AGG_END_NON_TPA_SEG,
	MAX_ETH_TPA_END_REASON
पूर्ण;

/* The first tx bd of a given packet */
काष्ठा eth_tx_1st_bd अणु
	काष्ठा regpair addr;
	__le16 nbytes;
	काष्ठा eth_tx_data_1st_bd data;
पूर्ण;

/* The second tx bd of a given packet */
काष्ठा eth_tx_2nd_bd अणु
	काष्ठा regpair addr;
	__le16 nbytes;
	काष्ठा eth_tx_data_2nd_bd data;
पूर्ण;

/* The parsing inक्रमmation data क्रम the third tx bd of a given packet */
काष्ठा eth_tx_data_3rd_bd अणु
	__le16 lso_mss;
	__le16 bitfields;
#घोषणा ETH_TX_DATA_3RD_BD_TCP_HDR_LEN_DW_MASK	0xF
#घोषणा ETH_TX_DATA_3RD_BD_TCP_HDR_LEN_DW_SHIFT	0
#घोषणा ETH_TX_DATA_3RD_BD_HDR_NBD_MASK		0xF
#घोषणा ETH_TX_DATA_3RD_BD_HDR_NBD_SHIFT	4
#घोषणा ETH_TX_DATA_3RD_BD_START_BD_MASK	0x1
#घोषणा ETH_TX_DATA_3RD_BD_START_BD_SHIFT	8
#घोषणा ETH_TX_DATA_3RD_BD_RESERVED0_MASK	0x7F
#घोषणा ETH_TX_DATA_3RD_BD_RESERVED0_SHIFT	9
	u8 tunn_l4_hdr_start_offset_w;
	u8 tunn_hdr_size_w;
पूर्ण;

/* The third tx bd of a given packet */
काष्ठा eth_tx_3rd_bd अणु
	काष्ठा regpair addr;
	__le16 nbytes;
	काष्ठा eth_tx_data_3rd_bd data;
पूर्ण;

/* The parsing inक्रमmation data क्रम the क्रमth tx bd of a given packet. */
काष्ठा eth_tx_data_4th_bd अणु
	u8 dst_vport_id;
	u8 reserved4;
	__le16 bitfields;
#घोषणा ETH_TX_DATA_4TH_BD_DST_VPORT_ID_VALID_MASK  0x1
#घोषणा ETH_TX_DATA_4TH_BD_DST_VPORT_ID_VALID_SHIFT 0
#घोषणा ETH_TX_DATA_4TH_BD_RESERVED1_MASK           0x7F
#घोषणा ETH_TX_DATA_4TH_BD_RESERVED1_SHIFT          1
#घोषणा ETH_TX_DATA_4TH_BD_START_BD_MASK            0x1
#घोषणा ETH_TX_DATA_4TH_BD_START_BD_SHIFT           8
#घोषणा ETH_TX_DATA_4TH_BD_RESERVED2_MASK           0x7F
#घोषणा ETH_TX_DATA_4TH_BD_RESERVED2_SHIFT          9
	__le16 reserved3;
पूर्ण;

/* The क्रमth tx bd of a given packet */
काष्ठा eth_tx_4th_bd अणु
	काष्ठा regpair addr; /* Single continuous buffer */
	__le16 nbytes; /* Number of bytes in this BD */
	काष्ठा eth_tx_data_4th_bd data; /* Parsing inक्रमmation data */
पूर्ण;

/* Complementary inक्रमmation क्रम the regular tx bd of a given packet */
काष्ठा eth_tx_data_bd अणु
	__le16 reserved0;
	__le16 bitfields;
#घोषणा ETH_TX_DATA_BD_RESERVED1_MASK	0xFF
#घोषणा ETH_TX_DATA_BD_RESERVED1_SHIFT	0
#घोषणा ETH_TX_DATA_BD_START_BD_MASK	0x1
#घोषणा ETH_TX_DATA_BD_START_BD_SHIFT	8
#घोषणा ETH_TX_DATA_BD_RESERVED2_MASK	0x7F
#घोषणा ETH_TX_DATA_BD_RESERVED2_SHIFT	9
	__le16 reserved3;
पूर्ण;

/* The common non-special TX BD ring element */
काष्ठा eth_tx_bd अणु
	काष्ठा regpair addr;
	__le16 nbytes;
	काष्ठा eth_tx_data_bd data;
पूर्ण;

जोड़ eth_tx_bd_types अणु
	काष्ठा eth_tx_1st_bd first_bd;
	काष्ठा eth_tx_2nd_bd second_bd;
	काष्ठा eth_tx_3rd_bd third_bd;
	काष्ठा eth_tx_4th_bd fourth_bd;
	काष्ठा eth_tx_bd reg_bd;
पूर्ण;

/* Mstorm Queue Zone */
क्रमागत eth_tx_tunn_type अणु
	ETH_TX_TUNN_GENEVE,
	ETH_TX_TUNN_TTAG,
	ETH_TX_TUNN_GRE,
	ETH_TX_TUNN_VXLAN,
	MAX_ETH_TX_TUNN_TYPE
पूर्ण;

/* Mstorm Queue Zone */
काष्ठा mstorm_eth_queue_zone अणु
	काष्ठा eth_rx_prod_data rx_producers;
	__le32 reserved[3];
पूर्ण;

/* Ystorm Queue Zone */
काष्ठा xstorm_eth_queue_zone अणु
	काष्ठा coalescing_बारet पूर्णांक_coalescing_बारet;
	u8 reserved[7];
पूर्ण;

/* ETH करोorbell data */
काष्ठा eth_db_data अणु
	u8 params;
#घोषणा ETH_DB_DATA_DEST_MASK		0x3
#घोषणा ETH_DB_DATA_DEST_SHIFT		0
#घोषणा ETH_DB_DATA_AGG_CMD_MASK	0x3
#घोषणा ETH_DB_DATA_AGG_CMD_SHIFT	2
#घोषणा ETH_DB_DATA_BYPASS_EN_MASK	0x1
#घोषणा ETH_DB_DATA_BYPASS_EN_SHIFT	4
#घोषणा ETH_DB_DATA_RESERVED_MASK	0x1
#घोषणा ETH_DB_DATA_RESERVED_SHIFT	5
#घोषणा ETH_DB_DATA_AGG_VAL_SEL_MASK	0x3
#घोषणा ETH_DB_DATA_AGG_VAL_SEL_SHIFT	6
	u8 agg_flags;
	__le16 bd_prod;
पूर्ण;

/* RSS hash type */
क्रमागत rss_hash_type अणु
	RSS_HASH_TYPE_DEFAULT = 0,
	RSS_HASH_TYPE_IPV4 = 1,
	RSS_HASH_TYPE_TCP_IPV4 = 2,
	RSS_HASH_TYPE_IPV6 = 3,
	RSS_HASH_TYPE_TCP_IPV6 = 4,
	RSS_HASH_TYPE_UDP_IPV4 = 5,
	RSS_HASH_TYPE_UDP_IPV6 = 6,
	MAX_RSS_HASH_TYPE
पूर्ण;

#पूर्ण_अगर /* __ETH_COMMON__ */
