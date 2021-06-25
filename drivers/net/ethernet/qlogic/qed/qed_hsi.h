<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_HSI_H
#घोषणा _QED_HSI_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/common_hsi.h>
#समावेश <linux/qed/storage_common.h>
#समावेश <linux/qed/tcp_common.h>
#समावेश <linux/qed/fcoe_common.h>
#समावेश <linux/qed/eth_common.h>
#समावेश <linux/qed/iscsi_common.h>
#समावेश <linux/qed/iwarp_common.h>
#समावेश <linux/qed/rdma_common.h>
#समावेश <linux/qed/roce_common.h>
#समावेश <linux/qed/qed_fcoe_अगर.h>

काष्ठा qed_hwfn;
काष्ठा qed_ptt;

/* Opcodes क्रम the event ring */
क्रमागत common_event_opcode अणु
	COMMON_EVENT_PF_START,
	COMMON_EVENT_PF_STOP,
	COMMON_EVENT_VF_START,
	COMMON_EVENT_VF_STOP,
	COMMON_EVENT_VF_PF_CHANNEL,
	COMMON_EVENT_VF_FLR,
	COMMON_EVENT_PF_UPDATE,
	COMMON_EVENT_MALICIOUS_VF,
	COMMON_EVENT_RL_UPDATE,
	COMMON_EVENT_EMPTY,
	MAX_COMMON_EVENT_OPCODE
पूर्ण;

/* Common Ramrod Command IDs */
क्रमागत common_ramrod_cmd_id अणु
	COMMON_RAMROD_UNUSED,
	COMMON_RAMROD_PF_START,
	COMMON_RAMROD_PF_STOP,
	COMMON_RAMROD_VF_START,
	COMMON_RAMROD_VF_STOP,
	COMMON_RAMROD_PF_UPDATE,
	COMMON_RAMROD_RL_UPDATE,
	COMMON_RAMROD_EMPTY,
	MAX_COMMON_RAMROD_CMD_ID
पूर्ण;

/* How ll2 should deal with packet upon errors */
क्रमागत core_error_handle अणु
	LL2_DROP_PACKET,
	LL2_DO_NOTHING,
	LL2_ASSERT,
	MAX_CORE_ERROR_HANDLE
पूर्ण;

/* Opcodes क्रम the event ring */
क्रमागत core_event_opcode अणु
	CORE_EVENT_TX_QUEUE_START,
	CORE_EVENT_TX_QUEUE_STOP,
	CORE_EVENT_RX_QUEUE_START,
	CORE_EVENT_RX_QUEUE_STOP,
	CORE_EVENT_RX_QUEUE_FLUSH,
	CORE_EVENT_TX_QUEUE_UPDATE,
	CORE_EVENT_QUEUE_STATS_QUERY,
	MAX_CORE_EVENT_OPCODE
पूर्ण;

/* The L4 pseuकरो checksum mode क्रम Core */
क्रमागत core_l4_pseuकरो_checksum_mode अणु
	CORE_L4_PSEUDO_CSUM_CORRECT_LENGTH,
	CORE_L4_PSEUDO_CSUM_ZERO_LENGTH,
	MAX_CORE_L4_PSEUDO_CHECKSUM_MODE
पूर्ण;

/* Light-L2 RX Producers in Tstorm RAM */
काष्ठा core_ll2_port_stats अणु
	काष्ठा regpair gsi_invalid_hdr;
	काष्ठा regpair gsi_invalid_pkt_length;
	काष्ठा regpair gsi_unsupported_pkt_typ;
	काष्ठा regpair gsi_crcchksm_error;
पूर्ण;

/* LL2 TX Per Queue Stats */
काष्ठा core_ll2_pstorm_per_queue_stat अणु
	काष्ठा regpair sent_ucast_bytes;
	काष्ठा regpair sent_mcast_bytes;
	काष्ठा regpair sent_bcast_bytes;
	काष्ठा regpair sent_ucast_pkts;
	काष्ठा regpair sent_mcast_pkts;
	काष्ठा regpair sent_bcast_pkts;
	काष्ठा regpair error_drop_pkts;
पूर्ण;

/* Light-L2 RX Producers in Tstorm RAM */
काष्ठा core_ll2_rx_prod अणु
	__le16 bd_prod;
	__le16 cqe_prod;
पूर्ण;

काष्ठा core_ll2_tstorm_per_queue_stat अणु
	काष्ठा regpair packet_too_big_discard;
	काष्ठा regpair no_buff_discard;
पूर्ण;

काष्ठा core_ll2_ustorm_per_queue_stat अणु
	काष्ठा regpair rcv_ucast_bytes;
	काष्ठा regpair rcv_mcast_bytes;
	काष्ठा regpair rcv_bcast_bytes;
	काष्ठा regpair rcv_ucast_pkts;
	काष्ठा regpair rcv_mcast_pkts;
	काष्ठा regpair rcv_bcast_pkts;
पूर्ण;

/* Structure क्रम करोorbell data, in PWM mode, क्रम RX producers update. */
काष्ठा core_pwm_prod_update_data अणु
	__le16 icid; /* पूर्णांकernal CID */
	u8 reserved0;
	u8 params;
#घोषणा CORE_PWM_PROD_UPDATE_DATA_AGG_CMD_MASK	  0x3
#घोषणा CORE_PWM_PROD_UPDATE_DATA_AGG_CMD_SHIFT   0
#घोषणा CORE_PWM_PROD_UPDATE_DATA_RESERVED1_MASK  0x3F	/* Set 0 */
#घोषणा CORE_PWM_PROD_UPDATE_DATA_RESERVED1_SHIFT 2
	काष्ठा core_ll2_rx_prod prod; /* Producers */
पूर्ण;

/* Core Ramrod Command IDs (light L2) */
क्रमागत core_ramrod_cmd_id अणु
	CORE_RAMROD_UNUSED,
	CORE_RAMROD_RX_QUEUE_START,
	CORE_RAMROD_TX_QUEUE_START,
	CORE_RAMROD_RX_QUEUE_STOP,
	CORE_RAMROD_TX_QUEUE_STOP,
	CORE_RAMROD_RX_QUEUE_FLUSH,
	CORE_RAMROD_TX_QUEUE_UPDATE,
	CORE_RAMROD_QUEUE_STATS_QUERY,
	MAX_CORE_RAMROD_CMD_ID
पूर्ण;

/* Core RX CQE Type क्रम Light L2 */
क्रमागत core_roce_flavor_type अणु
	CORE_ROCE,
	CORE_RROCE,
	MAX_CORE_ROCE_FLAVOR_TYPE
पूर्ण;

/* Specअगरies how ll2 should deal with packets errors: packet_too_big and
 * no_buff.
 */
काष्ठा core_rx_action_on_error अणु
	u8 error_type;
#घोषणा CORE_RX_ACTION_ON_ERROR_PACKET_TOO_BIG_MASK	0x3
#घोषणा CORE_RX_ACTION_ON_ERROR_PACKET_TOO_BIG_SHIFT	0
#घोषणा CORE_RX_ACTION_ON_ERROR_NO_BUFF_MASK		0x3
#घोषणा CORE_RX_ACTION_ON_ERROR_NO_BUFF_SHIFT		2
#घोषणा CORE_RX_ACTION_ON_ERROR_RESERVED_MASK		0xF
#घोषणा CORE_RX_ACTION_ON_ERROR_RESERVED_SHIFT		4
पूर्ण;

/* Core RX BD क्रम Light L2 */
काष्ठा core_rx_bd अणु
	काष्ठा regpair addr;
	__le16 reserved[4];
पूर्ण;

/* Core RX CM offload BD क्रम Light L2 */
काष्ठा core_rx_bd_with_buff_len अणु
	काष्ठा regpair addr;
	__le16 buff_length;
	__le16 reserved[3];
पूर्ण;

/* Core RX CM offload BD क्रम Light L2 */
जोड़ core_rx_bd_जोड़ अणु
	काष्ठा core_rx_bd rx_bd;
	काष्ठा core_rx_bd_with_buff_len rx_bd_with_len;
पूर्ण;

/* Opaque Data क्रम Light L2 RX CQE */
काष्ठा core_rx_cqe_opaque_data अणु
	__le32 data[2];
पूर्ण;

/* Core RX CQE Type क्रम Light L2 */
क्रमागत core_rx_cqe_type अणु
	CORE_RX_CQE_ILLEGAL_TYPE,
	CORE_RX_CQE_TYPE_REGULAR,
	CORE_RX_CQE_TYPE_GSI_OFFLOAD,
	CORE_RX_CQE_TYPE_SLOW_PATH,
	MAX_CORE_RX_CQE_TYPE
पूर्ण;

/* Core RX CQE क्रम Light L2 */
काष्ठा core_rx_fast_path_cqe अणु
	u8 type;
	u8 placement_offset;
	काष्ठा parsing_and_err_flags parse_flags;
	__le16 packet_length;
	__le16 vlan;
	काष्ठा core_rx_cqe_opaque_data opaque_data;
	काष्ठा parsing_err_flags err_flags;
	__le16 reserved0;
	__le32 reserved1[3];
पूर्ण;

/* Core Rx CM offload CQE */
काष्ठा core_rx_gsi_offload_cqe अणु
	u8 type;
	u8 data_length_error;
	काष्ठा parsing_and_err_flags parse_flags;
	__le16 data_length;
	__le16 vlan;
	__le32 src_mac_addrhi;
	__le16 src_mac_addrlo;
	__le16 qp_id;
	__le32 src_qp;
	काष्ठा core_rx_cqe_opaque_data opaque_data;
	__le32 reserved;
पूर्ण;

/* Core RX CQE क्रम Light L2 */
काष्ठा core_rx_slow_path_cqe अणु
	u8 type;
	u8 ramrod_cmd_id;
	__le16 echo;
	काष्ठा core_rx_cqe_opaque_data opaque_data;
	__le32 reserved1[5];
पूर्ण;

/* Core RX CM offload BD क्रम Light L2 */
जोड़ core_rx_cqe_जोड़ अणु
	काष्ठा core_rx_fast_path_cqe rx_cqe_fp;
	काष्ठा core_rx_gsi_offload_cqe rx_cqe_gsi;
	काष्ठा core_rx_slow_path_cqe rx_cqe_sp;
पूर्ण;

/* Ramrod data क्रम rx queue start ramrod */
काष्ठा core_rx_start_ramrod_data अणु
	काष्ठा regpair bd_base;
	काष्ठा regpair cqe_pbl_addr;
	__le16 mtu;
	__le16 sb_id;
	u8 sb_index;
	u8 complete_cqe_flg;
	u8 complete_event_flg;
	u8 drop_ttl0_flg;
	__le16 num_of_pbl_pages;
	u8 inner_vlan_stripping_en;
	u8 report_outer_vlan;
	u8 queue_id;
	u8 मुख्य_func_queue;
	u8 mf_si_bcast_accept_all;
	u8 mf_si_mcast_accept_all;
	काष्ठा core_rx_action_on_error action_on_error;
	u8 gsi_offload_flag;
	u8 vport_id_valid;
	u8 vport_id;
	u8 zero_prod_flg;
	u8 wipe_inner_vlan_pri_en;
	u8 reserved[2];
पूर्ण;

/* Ramrod data क्रम rx queue stop ramrod */
काष्ठा core_rx_stop_ramrod_data अणु
	u8 complete_cqe_flg;
	u8 complete_event_flg;
	u8 queue_id;
	u8 reserved1;
	__le16 reserved2[2];
पूर्ण;

/* Flags क्रम Core TX BD */
काष्ठा core_tx_bd_data अणु
	__le16 as_bitfield;
#घोषणा CORE_TX_BD_DATA_FORCE_VLAN_MODE_MASK		0x1
#घोषणा CORE_TX_BD_DATA_FORCE_VLAN_MODE_SHIFT		0
#घोषणा CORE_TX_BD_DATA_VLAN_INSERTION_MASK		0x1
#घोषणा CORE_TX_BD_DATA_VLAN_INSERTION_SHIFT		1
#घोषणा CORE_TX_BD_DATA_START_BD_MASK			0x1
#घोषणा CORE_TX_BD_DATA_START_BD_SHIFT			2
#घोषणा CORE_TX_BD_DATA_IP_CSUM_MASK			0x1
#घोषणा CORE_TX_BD_DATA_IP_CSUM_SHIFT			3
#घोषणा CORE_TX_BD_DATA_L4_CSUM_MASK			0x1
#घोषणा CORE_TX_BD_DATA_L4_CSUM_SHIFT			4
#घोषणा CORE_TX_BD_DATA_IPV6_EXT_MASK			0x1
#घोषणा CORE_TX_BD_DATA_IPV6_EXT_SHIFT			5
#घोषणा CORE_TX_BD_DATA_L4_PROTOCOL_MASK		0x1
#घोषणा CORE_TX_BD_DATA_L4_PROTOCOL_SHIFT		6
#घोषणा CORE_TX_BD_DATA_L4_PSEUDO_CSUM_MODE_MASK	0x1
#घोषणा CORE_TX_BD_DATA_L4_PSEUDO_CSUM_MODE_SHIFT	7
#घोषणा CORE_TX_BD_DATA_NBDS_MASK			0xF
#घोषणा CORE_TX_BD_DATA_NBDS_SHIFT			8
#घोषणा CORE_TX_BD_DATA_ROCE_FLAV_MASK			0x1
#घोषणा CORE_TX_BD_DATA_ROCE_FLAV_SHIFT			12
#घोषणा CORE_TX_BD_DATA_IP_LEN_MASK			0x1
#घोषणा CORE_TX_BD_DATA_IP_LEN_SHIFT			13
#घोषणा CORE_TX_BD_DATA_DISABLE_STAG_INSERTION_MASK	0x1
#घोषणा CORE_TX_BD_DATA_DISABLE_STAG_INSERTION_SHIFT	14
#घोषणा CORE_TX_BD_DATA_RESERVED0_MASK			0x1
#घोषणा CORE_TX_BD_DATA_RESERVED0_SHIFT			15
पूर्ण;

/* Core TX BD क्रम Light L2 */
काष्ठा core_tx_bd अणु
	काष्ठा regpair addr;
	__le16 nbytes;
	__le16 nw_vlan_or_lb_echo;
	काष्ठा core_tx_bd_data bd_data;
	__le16 bitfield1;
#घोषणा CORE_TX_BD_L4_HDR_OFFSET_W_MASK		0x3FFF
#घोषणा CORE_TX_BD_L4_HDR_OFFSET_W_SHIFT	0
#घोषणा CORE_TX_BD_TX_DST_MASK			0x3
#घोषणा CORE_TX_BD_TX_DST_SHIFT			14
पूर्ण;

/* Light L2 TX Destination */
क्रमागत core_tx_dest अणु
	CORE_TX_DEST_NW,
	CORE_TX_DEST_LB,
	CORE_TX_DEST_RESERVED,
	CORE_TX_DEST_DROP,
	MAX_CORE_TX_DEST
पूर्ण;

/* Ramrod data क्रम tx queue start ramrod */
काष्ठा core_tx_start_ramrod_data अणु
	काष्ठा regpair pbl_base_addr;
	__le16 mtu;
	__le16 sb_id;
	u8 sb_index;
	u8 stats_en;
	u8 stats_id;
	u8 conn_type;
	__le16 pbl_size;
	__le16 qm_pq_id;
	u8 gsi_offload_flag;
	u8 ctx_stats_en;
	u8 vport_id_valid;
	u8 vport_id;
	u8 enक्रमce_security_flag;
	u8 reserved[7];
पूर्ण;

/* Ramrod data क्रम tx queue stop ramrod */
काष्ठा core_tx_stop_ramrod_data अणु
	__le32 reserved0[2];
पूर्ण;

/* Ramrod data क्रम tx queue update ramrod */
काष्ठा core_tx_update_ramrod_data अणु
	u8 update_qm_pq_id_flg;
	u8 reserved0;
	__le16 qm_pq_id;
	__le32 reserved1;
पूर्ण;

/* Enum flag क्रम what type of dcb data to update */
क्रमागत dcb_dscp_update_mode अणु
	DONT_UPDATE_DCB_DSCP,
	UPDATE_DCB,
	UPDATE_DSCP,
	UPDATE_DCB_DSCP,
	MAX_DCB_DSCP_UPDATE_MODE
पूर्ण;

/* The core storm context क्रम the Ystorm */
काष्ठा ystorm_core_conn_st_ctx अणु
	__le32 reserved[4];
पूर्ण;

/* The core storm context क्रम the Pstorm */
काष्ठा pstorm_core_conn_st_ctx अणु
	__le32 reserved[20];
पूर्ण;

/* Core Slowpath Connection storm context of Xstorm */
काष्ठा xstorm_core_conn_st_ctx अणु
	__le32 spq_base_lo;
	__le32 spq_base_hi;
	काष्ठा regpair consolid_base_addr;
	__le16 spq_cons;
	__le16 consolid_cons;
	__le32 reserved0[55];
पूर्ण;

काष्ठा e4_xstorm_core_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED1_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED3_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED4_SHIFT	5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED5_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED6_SHIFT	7
	u8 flags1;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED7_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED8_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED9_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT11_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT12_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT12_SHIFT		4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT13_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT13_SHIFT		5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TX_RULE_ACTIVE_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TX_RULE_ACTIVE_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_ACTIVE_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_ACTIVE_SHIFT	7
	u8 flags2;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF0_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF1_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF2_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF4_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF5_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF6_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF7_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF12_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF12_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF13_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF13_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF14_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF14_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF15_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CONSOLID_PROD_CF_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CONSOLID_PROD_CF_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF17_MASK			0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF17_SHIFT			2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_MASK			0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_SHIFT			4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TERMINATE_CF_MASK		0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TERMINATE_CF_SHIFT		6
	u8 flags7;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_FLUSH_Q0_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_FLUSH_Q0_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED10_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED10_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF0EN_SHIFT		6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF1EN_SHIFT		7
	u8 flags8;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF2EN_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF3EN_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF4EN_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF5EN_SHIFT	3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF6EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF6EN_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF7EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF7EN_SHIFT	5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF8EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF8EN_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF9EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF9EN_SHIFT	7
	u8 flags9;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF10EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF10EN_SHIFT			0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF11EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF11EN_SHIFT			1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF12EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF12EN_SHIFT			2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF13EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF13EN_SHIFT			3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF14EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF14EN_SHIFT			4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF15EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF15EN_SHIFT			5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CONSOLID_PROD_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CONSOLID_PROD_CF_EN_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF17EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF17EN_SHIFT			7
	u8 flags10;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_EN_SHIFT		0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TERMINATE_CF_EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TERMINATE_CF_EN_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_FLUSH_Q0_EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_FLUSH_Q0_EN_SHIFT		2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED11_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED11_SHIFT		3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_SLOW_PATH_EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_SLOW_PATH_EN_SHIFT		4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF23EN_MASK			0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF23EN_SHIFT			5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED12_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED12_SHIFT		6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED13_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED13_SHIFT		7
	u8 flags11;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED14_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED14_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED15_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RESERVED15_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TX_DEC_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_TX_DEC_RULE_EN_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE5EN_SHIFT	3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE6EN_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE7EN_SHIFT	5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED1_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE9EN_MASK		0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE9EN_SHIFT	7
	u8 flags12;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE10EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE10EN_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE11EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE11EN_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED3_SHIFT	3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE14EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE14EN_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE15EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE15EN_SHIFT	5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE16EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE16EN_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE17EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE17EN_SHIFT	7
	u8 flags13;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE18EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE18EN_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE19EN_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_RULE19EN_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED4_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED5_SHIFT	3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED6_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED7_SHIFT	5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED8_SHIFT	6
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT16_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT16_SHIFT	0
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT17_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT17_SHIFT	1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT18_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT18_SHIFT	2
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT19_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT19_SHIFT	3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT20_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT20_SHIFT	4
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT21_MASK	0x1
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_BIT21_SHIFT	5
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF23_MASK	0x3
#घोषणा E4_XSTORM_CORE_CONN_AG_CTX_CF23_SHIFT	6
	u8 byte2;
	__le16 physical_q0;
	__le16 consolid_prod;
	__le16 reserved16;
	__le16 tx_bd_cons;
	__le16 tx_bd_or_spq_prod;
	__le16 updated_qm_pq_id;
	__le16 conn_dpi;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le16 word7;
	__le16 word8;
	__le16 word9;
	__le16 word10;
	__le32 reg7;
	__le32 reg8;
	__le32 reg9;
	u8 byte7;
	u8 byte8;
	u8 byte9;
	u8 byte10;
	u8 byte11;
	u8 byte12;
	u8 byte13;
	u8 byte14;
	u8 byte15;
	u8 e5_reserved;
	__le16 word11;
	__le32 reg10;
	__le32 reg11;
	__le32 reg12;
	__le32 reg13;
	__le32 reg14;
	__le32 reg15;
	__le32 reg16;
	__le32 reg17;
	__le32 reg18;
	__le32 reg19;
	__le16 word12;
	__le16 word13;
	__le16 word14;
	__le16 word15;
पूर्ण;

काष्ठा e4_tstorm_core_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT2_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT2_SHIFT	2
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT3_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT3_SHIFT	3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT4_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT4_SHIFT	4
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT5_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_BIT5_SHIFT	5
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF0_SHIFT	6
	u8 flags1;
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF1_SHIFT	0
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF2_SHIFT	2
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF3_SHIFT	4
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF4_SHIFT	6
	u8 flags2;
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF5_SHIFT	0
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF6_SHIFT	2
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF7_SHIFT	4
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF8_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF9_SHIFT	0
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF10_SHIFT	2
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF0EN_SHIFT	4
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF1EN_SHIFT	5
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF2EN_SHIFT	6
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF3EN_SHIFT	7
	u8 flags4;
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF4EN_SHIFT		0
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF5EN_SHIFT		1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF6EN_SHIFT		2
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF7EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF7EN_SHIFT		3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF8EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF8EN_SHIFT		4
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF9EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF9EN_SHIFT		5
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF10EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_CF10EN_SHIFT		6
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags5;
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_TSTORM_CORE_CONN_AG_CTX_RULE8EN_SHIFT	7
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le32 reg7;
	__le32 reg8;
	u8 byte2;
	u8 byte3;
	__le16 word0;
	u8 byte4;
	u8 byte5;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le32 ll2_rx_prod;
	__le32 reg10;
पूर्ण;

काष्ठा e4_ustorm_core_conn_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF3_SHIFT	0
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF4_SHIFT	2
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF5_SHIFT	4
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF6_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF3EN_SHIFT		3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF4EN_SHIFT		4
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF5EN_SHIFT		5
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_CF6EN_SHIFT		6
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags3;
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_USTORM_CORE_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 word1;
	__le32 rx_producers;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le16 word2;
	__le16 word3;
पूर्ण;

/* The core storm context क्रम the Mstorm */
काष्ठा mstorm_core_conn_st_ctx अणु
	__le32 reserved[40];
पूर्ण;

/* The core storm context क्रम the Ustorm */
काष्ठा ustorm_core_conn_st_ctx अणु
	__le32 reserved[20];
पूर्ण;

/* The core storm context क्रम the Tstorm */
काष्ठा tstorm_core_conn_st_ctx अणु
	__le32 reserved[4];
पूर्ण;

/* core connection context */
काष्ठा e4_core_conn_context अणु
	काष्ठा ystorm_core_conn_st_ctx ystorm_st_context;
	काष्ठा regpair ystorm_st_padding[2];
	काष्ठा pstorm_core_conn_st_ctx pstorm_st_context;
	काष्ठा regpair pstorm_st_padding[2];
	काष्ठा xstorm_core_conn_st_ctx xstorm_st_context;
	काष्ठा e4_xstorm_core_conn_ag_ctx xstorm_ag_context;
	काष्ठा e4_tstorm_core_conn_ag_ctx tstorm_ag_context;
	काष्ठा e4_ustorm_core_conn_ag_ctx ustorm_ag_context;
	काष्ठा mstorm_core_conn_st_ctx mstorm_st_context;
	काष्ठा ustorm_core_conn_st_ctx ustorm_st_context;
	काष्ठा regpair ustorm_st_padding[2];
	काष्ठा tstorm_core_conn_st_ctx tstorm_st_context;
	काष्ठा regpair tstorm_st_padding[2];
पूर्ण;

काष्ठा eth_mstorm_per_pf_stat अणु
	काष्ठा regpair gre_discard_pkts;
	काष्ठा regpair vxlan_discard_pkts;
	काष्ठा regpair geneve_discard_pkts;
	काष्ठा regpair lb_discard_pkts;
पूर्ण;

काष्ठा eth_mstorm_per_queue_stat अणु
	काष्ठा regpair ttl0_discard;
	काष्ठा regpair packet_too_big_discard;
	काष्ठा regpair no_buff_discard;
	काष्ठा regpair not_active_discard;
	काष्ठा regpair tpa_coalesced_pkts;
	काष्ठा regpair tpa_coalesced_events;
	काष्ठा regpair tpa_पातs_num;
	काष्ठा regpair tpa_coalesced_bytes;
पूर्ण;

/* Ethernet TX Per PF */
काष्ठा eth_pstorm_per_pf_stat अणु
	काष्ठा regpair sent_lb_ucast_bytes;
	काष्ठा regpair sent_lb_mcast_bytes;
	काष्ठा regpair sent_lb_bcast_bytes;
	काष्ठा regpair sent_lb_ucast_pkts;
	काष्ठा regpair sent_lb_mcast_pkts;
	काष्ठा regpair sent_lb_bcast_pkts;
	काष्ठा regpair sent_gre_bytes;
	काष्ठा regpair sent_vxlan_bytes;
	काष्ठा regpair sent_geneve_bytes;
	काष्ठा regpair sent_mpls_bytes;
	काष्ठा regpair sent_gre_mpls_bytes;
	काष्ठा regpair sent_udp_mpls_bytes;
	काष्ठा regpair sent_gre_pkts;
	काष्ठा regpair sent_vxlan_pkts;
	काष्ठा regpair sent_geneve_pkts;
	काष्ठा regpair sent_mpls_pkts;
	काष्ठा regpair sent_gre_mpls_pkts;
	काष्ठा regpair sent_udp_mpls_pkts;
	काष्ठा regpair gre_drop_pkts;
	काष्ठा regpair vxlan_drop_pkts;
	काष्ठा regpair geneve_drop_pkts;
	काष्ठा regpair mpls_drop_pkts;
	काष्ठा regpair gre_mpls_drop_pkts;
	काष्ठा regpair udp_mpls_drop_pkts;
पूर्ण;

/* Ethernet TX Per Queue Stats */
काष्ठा eth_pstorm_per_queue_stat अणु
	काष्ठा regpair sent_ucast_bytes;
	काष्ठा regpair sent_mcast_bytes;
	काष्ठा regpair sent_bcast_bytes;
	काष्ठा regpair sent_ucast_pkts;
	काष्ठा regpair sent_mcast_pkts;
	काष्ठा regpair sent_bcast_pkts;
	काष्ठा regpair error_drop_pkts;
पूर्ण;

/* ETH Rx producers data */
काष्ठा eth_rx_rate_limit अणु
	__le16 mult;
	__le16 cnst;
	u8 add_sub_cnst;
	u8 reserved0;
	__le16 reserved1;
पूर्ण;

/* Update RSS indirection table entry command */
काष्ठा eth_tstorm_rss_update_data अणु
	u8 valid;
	u8 vport_id;
	u8 ind_table_index;
	u8 reserved;
	__le16 ind_table_value;
	__le16 reserved1;
पूर्ण;

काष्ठा eth_ustorm_per_pf_stat अणु
	काष्ठा regpair rcv_lb_ucast_bytes;
	काष्ठा regpair rcv_lb_mcast_bytes;
	काष्ठा regpair rcv_lb_bcast_bytes;
	काष्ठा regpair rcv_lb_ucast_pkts;
	काष्ठा regpair rcv_lb_mcast_pkts;
	काष्ठा regpair rcv_lb_bcast_pkts;
	काष्ठा regpair rcv_gre_bytes;
	काष्ठा regpair rcv_vxlan_bytes;
	काष्ठा regpair rcv_geneve_bytes;
	काष्ठा regpair rcv_gre_pkts;
	काष्ठा regpair rcv_vxlan_pkts;
	काष्ठा regpair rcv_geneve_pkts;
पूर्ण;

काष्ठा eth_ustorm_per_queue_stat अणु
	काष्ठा regpair rcv_ucast_bytes;
	काष्ठा regpair rcv_mcast_bytes;
	काष्ठा regpair rcv_bcast_bytes;
	काष्ठा regpair rcv_ucast_pkts;
	काष्ठा regpair rcv_mcast_pkts;
	काष्ठा regpair rcv_bcast_pkts;
पूर्ण;

/* Event Ring VF-PF Channel data */
काष्ठा vf_pf_channel_eqe_data अणु
	काष्ठा regpair msg_addr;
पूर्ण;

/* Event Ring malicious VF data */
काष्ठा malicious_vf_eqe_data अणु
	u8 vf_id;
	u8 err_id;
	__le16 reserved[3];
पूर्ण;

/* Event Ring initial cleanup data */
काष्ठा initial_cleanup_eqe_data अणु
	u8 vf_id;
	u8 reserved[7];
पूर्ण;

/* Event Data Union */
जोड़ event_ring_data अणु
	u8 bytes[8];
	काष्ठा vf_pf_channel_eqe_data vf_pf_channel;
	काष्ठा iscsi_eqe_data iscsi_info;
	काष्ठा iscsi_connect_करोne_results iscsi_conn_करोne_info;
	जोड़ rdma_eqe_data rdma_data;
	काष्ठा malicious_vf_eqe_data malicious_vf;
	काष्ठा initial_cleanup_eqe_data vf_init_cleanup;
पूर्ण;

/* Event Ring Entry */
काष्ठा event_ring_entry अणु
	u8 protocol_id;
	u8 opcode;
	u8 reserved0;
	u8 vf_id;
	__le16 echo;
	u8 fw_वापस_code;
	u8 flags;
#घोषणा EVENT_RING_ENTRY_ASYNC_MASK		0x1
#घोषणा EVENT_RING_ENTRY_ASYNC_SHIFT		0
#घोषणा EVENT_RING_ENTRY_RESERVED1_MASK		0x7F
#घोषणा EVENT_RING_ENTRY_RESERVED1_SHIFT	1
	जोड़ event_ring_data data;
पूर्ण;

/* Event Ring Next Page Address */
काष्ठा event_ring_next_addr अणु
	काष्ठा regpair addr;
	__le32 reserved[2];
पूर्ण;

/* Event Ring Element */
जोड़ event_ring_element अणु
	काष्ठा event_ring_entry entry;
	काष्ठा event_ring_next_addr next_addr;
पूर्ण;

/* Ports mode */
क्रमागत fw_flow_ctrl_mode अणु
	flow_ctrl_छोड़ो,
	flow_ctrl_pfc,
	MAX_FW_FLOW_CTRL_MODE
पूर्ण;

/* GFT profile type */
क्रमागत gft_profile_type अणु
	GFT_PROखाता_TYPE_4_TUPLE,
	GFT_PROखाता_TYPE_L4_DST_PORT,
	GFT_PROखाता_TYPE_IP_DST_ADDR,
	GFT_PROखाता_TYPE_IP_SRC_ADDR,
	GFT_PROखाता_TYPE_TUNNEL_TYPE,
	MAX_GFT_PROखाता_TYPE
पूर्ण;

/* Major and Minor hsi Versions */
काष्ठा hsi_fp_ver_काष्ठा अणु
	u8 minor_ver_arr[2];
	u8 major_ver_arr[2];
पूर्ण;

क्रमागत iwarp_ll2_tx_queues अणु
	IWARP_LL2_IN_ORDER_TX_QUEUE = 1,
	IWARP_LL2_ALIGNED_TX_QUEUE,
	IWARP_LL2_ALIGNED_RIGHT_TRIMMED_TX_QUEUE,
	IWARP_LL2_ERROR,
	MAX_IWARP_LL2_TX_QUEUES
पूर्ण;

/* Malicious VF error ID */
क्रमागत malicious_vf_error_id अणु
	MALICIOUS_VF_NO_ERROR,
	VF_PF_CHANNEL_NOT_READY,
	VF_ZONE_MSG_NOT_VALID,
	VF_ZONE_FUNC_NOT_ENABLED,
	ETH_PACKET_TOO_SMALL,
	ETH_ILLEGAL_VLAN_MODE,
	ETH_MTU_VIOLATION,
	ETH_ILLEGAL_INBAND_TAGS,
	ETH_VLAN_INSERT_AND_INBAND_VLAN,
	ETH_ILLEGAL_NBDS,
	ETH_FIRST_BD_WO_SOP,
	ETH_INSUFFICIENT_BDS,
	ETH_ILLEGAL_LSO_HDR_NBDS,
	ETH_ILLEGAL_LSO_MSS,
	ETH_ZERO_SIZE_BD,
	ETH_ILLEGAL_LSO_HDR_LEN,
	ETH_INSUFFICIENT_PAYLOAD,
	ETH_EDPM_OUT_OF_SYNC,
	ETH_TUNN_IPV6_EXT_NBD_ERR,
	ETH_CONTROL_PACKET_VIOLATION,
	ETH_ANTI_SPOOFING_ERR,
	ETH_PACKET_SIZE_TOO_LARGE,
	CORE_ILLEGAL_VLAN_MODE,
	CORE_ILLEGAL_NBDS,
	CORE_FIRST_BD_WO_SOP,
	CORE_INSUFFICIENT_BDS,
	CORE_PACKET_TOO_SMALL,
	CORE_ILLEGAL_INBAND_TAGS,
	CORE_VLAN_INSERT_AND_INBAND_VLAN,
	CORE_MTU_VIOLATION,
	CORE_CONTROL_PACKET_VIOLATION,
	CORE_ANTI_SPOOFING_ERR,
	CORE_PACKET_SIZE_TOO_LARGE,
	CORE_ILLEGAL_BD_FLAGS,
	CORE_GSI_PACKET_VIOLATION,
	MAX_MALICIOUS_VF_ERROR_ID,
पूर्ण;

/* Mstorm non-triggering VF zone */
काष्ठा mstorm_non_trigger_vf_zone अणु
	काष्ठा eth_mstorm_per_queue_stat eth_queue_stat;
	काष्ठा eth_rx_prod_data eth_rx_queue_producers[ETH_MAX_NUM_RX_QUEUES_PER_VF_QUAD];
पूर्ण;

/* Mstorm VF zone */
काष्ठा mstorm_vf_zone अणु
	काष्ठा mstorm_non_trigger_vf_zone non_trigger;
पूर्ण;

/* vlan header including TPID and TCI fields */
काष्ठा vlan_header अणु
	__le16 tpid;
	__le16 tci;
पूर्ण;

/* outer tag configurations */
काष्ठा outer_tag_config_काष्ठा अणु
	u8 enable_stag_pri_change;
	u8 pri_map_valid;
	u8 reserved[2];
	काष्ठा vlan_header outer_tag;
	u8 inner_to_outer_pri_map[8];
पूर्ण;

/* personality per PF */
क्रमागत personality_type अणु
	BAD_PERSONALITY_TYP,
	PERSONALITY_ISCSI,
	PERSONALITY_FCOE,
	PERSONALITY_RDMA_AND_ETH,
	PERSONALITY_RDMA,
	PERSONALITY_CORE,
	PERSONALITY_ETH,
	PERSONALITY_RESERVED,
	MAX_PERSONALITY_TYPE
पूर्ण;

/* tunnel configuration */
काष्ठा pf_start_tunnel_config अणु
	u8 set_vxlan_udp_port_flg;
	u8 set_geneve_udp_port_flg;
	u8 set_no_inner_l2_vxlan_udp_port_flg;
	u8 tunnel_clss_vxlan;
	u8 tunnel_clss_l2geneve;
	u8 tunnel_clss_ipgeneve;
	u8 tunnel_clss_l2gre;
	u8 tunnel_clss_ipgre;
	__le16 vxlan_udp_port;
	__le16 geneve_udp_port;
	__le16 no_inner_l2_vxlan_udp_port;
	__le16 reserved[3];
पूर्ण;

/* Ramrod data क्रम PF start ramrod */
काष्ठा pf_start_ramrod_data अणु
	काष्ठा regpair event_ring_pbl_addr;
	काष्ठा regpair consolid_q_pbl_addr;
	काष्ठा pf_start_tunnel_config tunnel_config;
	__le16 event_ring_sb_id;
	u8 base_vf_id;
	u8 num_vfs;
	u8 event_ring_num_pages;
	u8 event_ring_sb_index;
	u8 path_id;
	u8 warning_as_error;
	u8 करोnt_log_ramrods;
	u8 personality;
	__le16 log_type_mask;
	u8 mf_mode;
	u8 पूर्णांकeg_phase;
	u8 allow_npar_tx_चयनing;
	u8 reserved0;
	काष्ठा hsi_fp_ver_काष्ठा hsi_fp_ver;
	काष्ठा outer_tag_config_काष्ठा outer_tag_config;
पूर्ण;

/* Data क्रम port update ramrod */
काष्ठा protocol_dcb_data अणु
	u8 dcb_enable_flag;
	u8 dscp_enable_flag;
	u8 dcb_priority;
	u8 dcb_tc;
	u8 dscp_val;
	u8 dcb_करोnt_add_vlan0;
पूर्ण;

/* Update tunnel configuration */
काष्ठा pf_update_tunnel_config अणु
	u8 update_rx_pf_clss;
	u8 update_rx_def_ucast_clss;
	u8 update_rx_def_non_ucast_clss;
	u8 set_vxlan_udp_port_flg;
	u8 set_geneve_udp_port_flg;
	u8 set_no_inner_l2_vxlan_udp_port_flg;
	u8 tunnel_clss_vxlan;
	u8 tunnel_clss_l2geneve;
	u8 tunnel_clss_ipgeneve;
	u8 tunnel_clss_l2gre;
	u8 tunnel_clss_ipgre;
	u8 reserved;
	__le16 vxlan_udp_port;
	__le16 geneve_udp_port;
	__le16 no_inner_l2_vxlan_udp_port;
	__le16 reserved1[3];
पूर्ण;

/* Data क्रम port update ramrod */
काष्ठा pf_update_ramrod_data अणु
	u8 update_eth_dcb_data_mode;
	u8 update_fcoe_dcb_data_mode;
	u8 update_iscsi_dcb_data_mode;
	u8 update_roce_dcb_data_mode;
	u8 update_rroce_dcb_data_mode;
	u8 update_iwarp_dcb_data_mode;
	u8 update_mf_vlan_flag;
	u8 update_enable_stag_pri_change;
	काष्ठा protocol_dcb_data eth_dcb_data;
	काष्ठा protocol_dcb_data fcoe_dcb_data;
	काष्ठा protocol_dcb_data iscsi_dcb_data;
	काष्ठा protocol_dcb_data roce_dcb_data;
	काष्ठा protocol_dcb_data rroce_dcb_data;
	काष्ठा protocol_dcb_data iwarp_dcb_data;
	__le16 mf_vlan;
	u8 enable_stag_pri_change;
	u8 reserved;
	काष्ठा pf_update_tunnel_config tunnel_config;
पूर्ण;

/* Ports mode */
क्रमागत ports_mode अणु
	ENGX2_PORTX1,
	ENGX2_PORTX2,
	ENGX1_PORTX1,
	ENGX1_PORTX2,
	ENGX1_PORTX4,
	MAX_PORTS_MODE
पूर्ण;

/* use to index in hsi_fp_[major|minor]_ver_arr per protocol */
क्रमागत protocol_version_array_key अणु
	ETH_VER_KEY = 0,
	ROCE_VER_KEY,
	MAX_PROTOCOL_VERSION_ARRAY_KEY
पूर्ण;

/* RDMA TX Stats */
काष्ठा rdma_sent_stats अणु
	काष्ठा regpair sent_bytes;
	काष्ठा regpair sent_pkts;
पूर्ण;

/* Pstorm non-triggering VF zone */
काष्ठा pstorm_non_trigger_vf_zone अणु
	काष्ठा eth_pstorm_per_queue_stat eth_queue_stat;
	काष्ठा rdma_sent_stats rdma_stats;
पूर्ण;

/* Pstorm VF zone */
काष्ठा pstorm_vf_zone अणु
	काष्ठा pstorm_non_trigger_vf_zone non_trigger;
	काष्ठा regpair reserved[7];
पूर्ण;

/* Ramrod Header of SPQE */
काष्ठा ramrod_header अणु
	__le32 cid;
	u8 cmd_id;
	u8 protocol_id;
	__le16 echo;
पूर्ण;

/* RDMA RX Stats */
काष्ठा rdma_rcv_stats अणु
	काष्ठा regpair rcv_bytes;
	काष्ठा regpair rcv_pkts;
पूर्ण;

/* Data क्रम update QCN/DCQCN RL ramrod */
काष्ठा rl_update_ramrod_data अणु
	u8 qcn_update_param_flg;
	u8 dcqcn_update_param_flg;
	u8 rl_init_flg;
	u8 rl_start_flg;
	u8 rl_stop_flg;
	u8 rl_id_first;
	u8 rl_id_last;
	u8 rl_dc_qcn_flg;
	u8 dcqcn_reset_alpha_on_idle;
	u8 rl_bc_stage_th;
	u8 rl_समयr_stage_th;
	u8 reserved1;
	__le32 rl_bc_rate;
	__le16 rl_max_rate;
	__le16 rl_r_ai;
	__le16 rl_r_hai;
	__le16 dcqcn_g;
	__le32 dcqcn_k_us;
	__le32 dcqcn_समयuot_us;
	__le32 qcn_समयuot_us;
	__le32 reserved2;
पूर्ण;

/* Slowpath Element (SPQE) */
काष्ठा slow_path_element अणु
	काष्ठा ramrod_header hdr;
	काष्ठा regpair data_ptr;
पूर्ण;

/* Tstorm non-triggering VF zone */
काष्ठा tstorm_non_trigger_vf_zone अणु
	काष्ठा rdma_rcv_stats rdma_stats;
पूर्ण;

काष्ठा tstorm_per_port_stat अणु
	काष्ठा regpair trunc_error_discard;
	काष्ठा regpair mac_error_discard;
	काष्ठा regpair mftag_filter_discard;
	काष्ठा regpair eth_mac_filter_discard;
	काष्ठा regpair ll2_mac_filter_discard;
	काष्ठा regpair ll2_conn_disabled_discard;
	काष्ठा regpair iscsi_irregular_pkt;
	काष्ठा regpair fcoe_irregular_pkt;
	काष्ठा regpair roce_irregular_pkt;
	काष्ठा regpair iwarp_irregular_pkt;
	काष्ठा regpair eth_irregular_pkt;
	काष्ठा regpair toe_irregular_pkt;
	काष्ठा regpair preroce_irregular_pkt;
	काष्ठा regpair eth_gre_tunn_filter_discard;
	काष्ठा regpair eth_vxlan_tunn_filter_discard;
	काष्ठा regpair eth_geneve_tunn_filter_discard;
	काष्ठा regpair eth_gft_drop_pkt;
पूर्ण;

/* Tstorm VF zone */
काष्ठा tstorm_vf_zone अणु
	काष्ठा tstorm_non_trigger_vf_zone non_trigger;
पूर्ण;

/* Tunnel classअगरication scheme */
क्रमागत tunnel_clss अणु
	TUNNEL_CLSS_MAC_VLAN = 0,
	TUNNEL_CLSS_MAC_VNI,
	TUNNEL_CLSS_INNER_MAC_VLAN,
	TUNNEL_CLSS_INNER_MAC_VNI,
	TUNNEL_CLSS_MAC_VLAN_DUAL_STAGE,
	MAX_TUNNEL_CLSS
पूर्ण;

/* Ustorm non-triggering VF zone */
काष्ठा ustorm_non_trigger_vf_zone अणु
	काष्ठा eth_ustorm_per_queue_stat eth_queue_stat;
	काष्ठा regpair vf_pf_msg_addr;
पूर्ण;

/* Ustorm triggering VF zone */
काष्ठा ustorm_trigger_vf_zone अणु
	u8 vf_pf_msg_valid;
	u8 reserved[7];
पूर्ण;

/* Ustorm VF zone */
काष्ठा ustorm_vf_zone अणु
	काष्ठा ustorm_non_trigger_vf_zone non_trigger;
	काष्ठा ustorm_trigger_vf_zone trigger;
पूर्ण;

/* VF-PF channel data */
काष्ठा vf_pf_channel_data अणु
	__le32 पढ़ोy;
	u8 valid;
	u8 reserved0;
	__le16 reserved1;
पूर्ण;

/* Ramrod data क्रम VF start ramrod */
काष्ठा vf_start_ramrod_data अणु
	u8 vf_id;
	u8 enable_flr_ack;
	__le16 opaque_fid;
	u8 personality;
	u8 reserved[7];
	काष्ठा hsi_fp_ver_काष्ठा hsi_fp_ver;

पूर्ण;

/* Ramrod data क्रम VF start ramrod */
काष्ठा vf_stop_ramrod_data अणु
	u8 vf_id;
	u8 reserved0;
	__le16 reserved1;
	__le32 reserved2;
पूर्ण;

/* VF zone size mode */
क्रमागत vf_zone_size_mode अणु
	VF_ZONE_SIZE_MODE_DEFAULT,
	VF_ZONE_SIZE_MODE_DOUBLE,
	VF_ZONE_SIZE_MODE_QUAD,
	MAX_VF_ZONE_SIZE_MODE
पूर्ण;

/* Xstorm non-triggering VF zone */
काष्ठा xstorm_non_trigger_vf_zone अणु
	काष्ठा regpair non_edpm_ack_pkts;
पूर्ण;

/* Tstorm VF zone */
काष्ठा xstorm_vf_zone अणु
	काष्ठा xstorm_non_trigger_vf_zone non_trigger;
पूर्ण;

/* Attentions status block */
काष्ठा atten_status_block अणु
	__le32 atten_bits;
	__le32 atten_ack;
	__le16 reserved0;
	__le16 sb_index;
	__le32 reserved1;
पूर्ण;

/* DMAE command */
काष्ठा dmae_cmd अणु
	__le32 opcode;
#घोषणा DMAE_CMD_SRC_MASK		0x1
#घोषणा DMAE_CMD_SRC_SHIFT		0
#घोषणा DMAE_CMD_DST_MASK		0x3
#घोषणा DMAE_CMD_DST_SHIFT		1
#घोषणा DMAE_CMD_C_DST_MASK		0x1
#घोषणा DMAE_CMD_C_DST_SHIFT		3
#घोषणा DMAE_CMD_CRC_RESET_MASK		0x1
#घोषणा DMAE_CMD_CRC_RESET_SHIFT	4
#घोषणा DMAE_CMD_SRC_ADDR_RESET_MASK	0x1
#घोषणा DMAE_CMD_SRC_ADDR_RESET_SHIFT	5
#घोषणा DMAE_CMD_DST_ADDR_RESET_MASK	0x1
#घोषणा DMAE_CMD_DST_ADDR_RESET_SHIFT	6
#घोषणा DMAE_CMD_COMP_FUNC_MASK		0x1
#घोषणा DMAE_CMD_COMP_FUNC_SHIFT	7
#घोषणा DMAE_CMD_COMP_WORD_EN_MASK	0x1
#घोषणा DMAE_CMD_COMP_WORD_EN_SHIFT	8
#घोषणा DMAE_CMD_COMP_CRC_EN_MASK	0x1
#घोषणा DMAE_CMD_COMP_CRC_EN_SHIFT	9
#घोषणा DMAE_CMD_COMP_CRC_OFFSET_MASK	0x7
#घोषणा DMAE_CMD_COMP_CRC_OFFSET_SHIFT 10
#घोषणा DMAE_CMD_RESERVED1_MASK		0x1
#घोषणा DMAE_CMD_RESERVED1_SHIFT	13
#घोषणा DMAE_CMD_ENDIANITY_MODE_MASK	0x3
#घोषणा DMAE_CMD_ENDIANITY_MODE_SHIFT	14
#घोषणा DMAE_CMD_ERR_HANDLING_MASK	0x3
#घोषणा DMAE_CMD_ERR_HANDLING_SHIFT	16
#घोषणा DMAE_CMD_PORT_ID_MASK		0x3
#घोषणा DMAE_CMD_PORT_ID_SHIFT		18
#घोषणा DMAE_CMD_SRC_PF_ID_MASK		0xF
#घोषणा DMAE_CMD_SRC_PF_ID_SHIFT	20
#घोषणा DMAE_CMD_DST_PF_ID_MASK		0xF
#घोषणा DMAE_CMD_DST_PF_ID_SHIFT	24
#घोषणा DMAE_CMD_SRC_VF_ID_VALID_MASK	0x1
#घोषणा DMAE_CMD_SRC_VF_ID_VALID_SHIFT 28
#घोषणा DMAE_CMD_DST_VF_ID_VALID_MASK	0x1
#घोषणा DMAE_CMD_DST_VF_ID_VALID_SHIFT 29
#घोषणा DMAE_CMD_RESERVED2_MASK		0x3
#घोषणा DMAE_CMD_RESERVED2_SHIFT	30
	__le32 src_addr_lo;
	__le32 src_addr_hi;
	__le32 dst_addr_lo;
	__le32 dst_addr_hi;
	__le16 length_dw;
	__le16 opcode_b;
#घोषणा DMAE_CMD_SRC_VF_ID_MASK		0xFF
#घोषणा DMAE_CMD_SRC_VF_ID_SHIFT	0
#घोषणा DMAE_CMD_DST_VF_ID_MASK		0xFF
#घोषणा DMAE_CMD_DST_VF_ID_SHIFT	8
	__le32 comp_addr_lo;
	__le32 comp_addr_hi;
	__le32 comp_val;
	__le32 crc32;
	__le32 crc_32_c;
	__le16 crc16;
	__le16 crc16_c;
	__le16 crc10;
	__le16 error_bit_reserved;
#घोषणा DMAE_CMD_ERROR_BIT_MASK        0x1
#घोषणा DMAE_CMD_ERROR_BIT_SHIFT       0
#घोषणा DMAE_CMD_RESERVED_MASK	       0x7FFF
#घोषणा DMAE_CMD_RESERVED_SHIFT        1
	__le16 xsum16;
	__le16 xsum8;
पूर्ण;

क्रमागत dmae_cmd_comp_crc_en_क्रमागत अणु
	dmae_cmd_comp_crc_disabled,
	dmae_cmd_comp_crc_enabled,
	MAX_DMAE_CMD_COMP_CRC_EN_ENUM
पूर्ण;

क्रमागत dmae_cmd_comp_func_क्रमागत अणु
	dmae_cmd_comp_func_to_src,
	dmae_cmd_comp_func_to_dst,
	MAX_DMAE_CMD_COMP_FUNC_ENUM
पूर्ण;

क्रमागत dmae_cmd_comp_word_en_क्रमागत अणु
	dmae_cmd_comp_word_disabled,
	dmae_cmd_comp_word_enabled,
	MAX_DMAE_CMD_COMP_WORD_EN_ENUM
पूर्ण;

क्रमागत dmae_cmd_c_dst_क्रमागत अणु
	dmae_cmd_c_dst_pcie,
	dmae_cmd_c_dst_grc,
	MAX_DMAE_CMD_C_DST_ENUM
पूर्ण;

क्रमागत dmae_cmd_dst_क्रमागत अणु
	dmae_cmd_dst_none_0,
	dmae_cmd_dst_pcie,
	dmae_cmd_dst_grc,
	dmae_cmd_dst_none_3,
	MAX_DMAE_CMD_DST_ENUM
पूर्ण;

क्रमागत dmae_cmd_error_handling_क्रमागत अणु
	dmae_cmd_error_handling_send_regular_comp,
	dmae_cmd_error_handling_send_comp_with_err,
	dmae_cmd_error_handling_करोnt_send_comp,
	MAX_DMAE_CMD_ERROR_HANDLING_ENUM
पूर्ण;

क्रमागत dmae_cmd_src_क्रमागत अणु
	dmae_cmd_src_pcie,
	dmae_cmd_src_grc,
	MAX_DMAE_CMD_SRC_ENUM
पूर्ण;

काष्ठा e4_mstorm_core_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_MSTORM_CORE_CONN_AG_CTX_RULE4EN_SHIFT	7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_ystorm_core_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_YSTORM_CORE_CONN_AG_CTX_RULE4EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

/* DMAE parameters */
काष्ठा qed_dmae_params अणु
	u32 flags;
/* If QED_DMAE_PARAMS_RW_REPL_SRC flag is set and the
 * source is a block of length DMAE_MAX_RW_SIZE and the
 * destination is larger, the source block will be duplicated as
 * many बार as required to fill the destination block. This is
 * used mostly to ग_लिखो a zeroed buffer to destination address
 * using DMA
 */
#घोषणा QED_DMAE_PARAMS_RW_REPL_SRC_MASK	0x1
#घोषणा QED_DMAE_PARAMS_RW_REPL_SRC_SHIFT	0
#घोषणा QED_DMAE_PARAMS_SRC_VF_VALID_MASK	0x1
#घोषणा QED_DMAE_PARAMS_SRC_VF_VALID_SHIFT	1
#घोषणा QED_DMAE_PARAMS_DST_VF_VALID_MASK	0x1
#घोषणा QED_DMAE_PARAMS_DST_VF_VALID_SHIFT	2
#घोषणा QED_DMAE_PARAMS_COMPLETION_DST_MASK	0x1
#घोषणा QED_DMAE_PARAMS_COMPLETION_DST_SHIFT	3
#घोषणा QED_DMAE_PARAMS_PORT_VALID_MASK		0x1
#घोषणा QED_DMAE_PARAMS_PORT_VALID_SHIFT	4
#घोषणा QED_DMAE_PARAMS_SRC_PF_VALID_MASK	0x1
#घोषणा QED_DMAE_PARAMS_SRC_PF_VALID_SHIFT	5
#घोषणा QED_DMAE_PARAMS_DST_PF_VALID_MASK	0x1
#घोषणा QED_DMAE_PARAMS_DST_PF_VALID_SHIFT	6
#घोषणा QED_DMAE_PARAMS_RESERVED_MASK		0x1FFFFFF
#घोषणा QED_DMAE_PARAMS_RESERVED_SHIFT		7
	u8 src_vfid;
	u8 dst_vfid;
	u8 port_id;
	u8 src_pfid;
	u8 dst_pfid;
	u8 reserved1;
	__le16 reserved2;
पूर्ण;

/* IGU cleanup command */
काष्ठा igu_cleanup अणु
	__le32 sb_id_and_flags;
#घोषणा IGU_CLEANUP_RESERVED0_MASK	0x7FFFFFF
#घोषणा IGU_CLEANUP_RESERVED0_SHIFT	0
#घोषणा IGU_CLEANUP_CLEANUP_SET_MASK	0x1
#घोषणा IGU_CLEANUP_CLEANUP_SET_SHIFT	27
#घोषणा IGU_CLEANUP_CLEANUP_TYPE_MASK	0x7
#घोषणा IGU_CLEANUP_CLEANUP_TYPE_SHIFT	28
#घोषणा IGU_CLEANUP_COMMAND_TYPE_MASK	0x1
#घोषणा IGU_CLEANUP_COMMAND_TYPE_SHIFT	31
	__le32 reserved1;
पूर्ण;

/* IGU firmware driver command */
जोड़ igu_command अणु
	काष्ठा igu_prod_cons_update prod_cons_update;
	काष्ठा igu_cleanup cleanup;
पूर्ण;

/* IGU firmware driver command */
काष्ठा igu_command_reg_ctrl अणु
	__le16 opaque_fid;
	__le16 igu_command_reg_ctrl_fields;
#घोषणा IGU_COMMAND_REG_CTRL_PXP_BAR_ADDR_MASK	0xFFF
#घोषणा IGU_COMMAND_REG_CTRL_PXP_BAR_ADDR_SHIFT	0
#घोषणा IGU_COMMAND_REG_CTRL_RESERVED_MASK	0x7
#घोषणा IGU_COMMAND_REG_CTRL_RESERVED_SHIFT	12
#घोषणा IGU_COMMAND_REG_CTRL_COMMAND_TYPE_MASK	0x1
#घोषणा IGU_COMMAND_REG_CTRL_COMMAND_TYPE_SHIFT	15
पूर्ण;

/* IGU mapping line काष्ठाure */
काष्ठा igu_mapping_line अणु
	__le32 igu_mapping_line_fields;
#घोषणा IGU_MAPPING_LINE_VALID_MASK		0x1
#घोषणा IGU_MAPPING_LINE_VALID_SHIFT		0
#घोषणा IGU_MAPPING_LINE_VECTOR_NUMBER_MASK	0xFF
#घोषणा IGU_MAPPING_LINE_VECTOR_NUMBER_SHIFT	1
#घोषणा IGU_MAPPING_LINE_FUNCTION_NUMBER_MASK	0xFF
#घोषणा IGU_MAPPING_LINE_FUNCTION_NUMBER_SHIFT	9
#घोषणा IGU_MAPPING_LINE_PF_VALID_MASK		0x1
#घोषणा IGU_MAPPING_LINE_PF_VALID_SHIFT		17
#घोषणा IGU_MAPPING_LINE_IPS_GROUP_MASK		0x3F
#घोषणा IGU_MAPPING_LINE_IPS_GROUP_SHIFT	18
#घोषणा IGU_MAPPING_LINE_RESERVED_MASK		0xFF
#घोषणा IGU_MAPPING_LINE_RESERVED_SHIFT		24
पूर्ण;

/* IGU MSIX line काष्ठाure */
काष्ठा igu_msix_vector अणु
	काष्ठा regpair address;
	__le32 data;
	__le32 msix_vector_fields;
#घोषणा IGU_MSIX_VECTOR_MASK_BIT_MASK		0x1
#घोषणा IGU_MSIX_VECTOR_MASK_BIT_SHIFT		0
#घोषणा IGU_MSIX_VECTOR_RESERVED0_MASK		0x7FFF
#घोषणा IGU_MSIX_VECTOR_RESERVED0_SHIFT		1
#घोषणा IGU_MSIX_VECTOR_STEERING_TAG_MASK	0xFF
#घोषणा IGU_MSIX_VECTOR_STEERING_TAG_SHIFT	16
#घोषणा IGU_MSIX_VECTOR_RESERVED1_MASK		0xFF
#घोषणा IGU_MSIX_VECTOR_RESERVED1_SHIFT		24
पूर्ण;
/* per encapsulation type enabling flags */
काष्ठा prs_reg_encapsulation_type_en अणु
	u8 flags;
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GRE_ENABLE_MASK		0x1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GRE_ENABLE_SHIFT		0
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GRE_ENABLE_MASK		0x1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GRE_ENABLE_SHIFT		1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_VXLAN_ENABLE_MASK			0x1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_VXLAN_ENABLE_SHIFT		2
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_T_TAG_ENABLE_MASK			0x1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_T_TAG_ENABLE_SHIFT		3
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_MASK	0x1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_SHIFT	4
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_MASK	0x1
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_SHIFT	5
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_RESERVED_MASK			0x3
#घोषणा PRS_REG_ENCAPSULATION_TYPE_EN_RESERVED_SHIFT			6
पूर्ण;

क्रमागत pxp_tph_st_hपूर्णांक अणु
	TPH_ST_HINT_BIसूची,
	TPH_ST_HINT_REQUESTER,
	TPH_ST_HINT_TARGET,
	TPH_ST_HINT_TARGET_PRIO,
	MAX_PXP_TPH_ST_HINT
पूर्ण;

/* QM hardware काष्ठाure of enable bypass credit mask */
काष्ठा qm_rf_bypass_mask अणु
	u8 flags;
#घोषणा QM_RF_BYPASS_MASK_LINEVOQ_MASK		0x1
#घोषणा QM_RF_BYPASS_MASK_LINEVOQ_SHIFT		0
#घोषणा QM_RF_BYPASS_MASK_RESERVED0_MASK	0x1
#घोषणा QM_RF_BYPASS_MASK_RESERVED0_SHIFT	1
#घोषणा QM_RF_BYPASS_MASK_PFWFQ_MASK		0x1
#घोषणा QM_RF_BYPASS_MASK_PFWFQ_SHIFT		2
#घोषणा QM_RF_BYPASS_MASK_VPWFQ_MASK		0x1
#घोषणा QM_RF_BYPASS_MASK_VPWFQ_SHIFT		3
#घोषणा QM_RF_BYPASS_MASK_PFRL_MASK		0x1
#घोषणा QM_RF_BYPASS_MASK_PFRL_SHIFT		4
#घोषणा QM_RF_BYPASS_MASK_VPQCNRL_MASK		0x1
#घोषणा QM_RF_BYPASS_MASK_VPQCNRL_SHIFT		5
#घोषणा QM_RF_BYPASS_MASK_FWPAUSE_MASK		0x1
#घोषणा QM_RF_BYPASS_MASK_FWPAUSE_SHIFT		6
#घोषणा QM_RF_BYPASS_MASK_RESERVED1_MASK	0x1
#घोषणा QM_RF_BYPASS_MASK_RESERVED1_SHIFT	7
पूर्ण;

/* QM hardware काष्ठाure of opportunistic credit mask */
काष्ठा qm_rf_opportunistic_mask अणु
	__le16 flags;
#घोषणा QM_RF_OPPORTUNISTIC_MASK_LINEVOQ_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_LINEVOQ_SHIFT		0
#घोषणा QM_RF_OPPORTUNISTIC_MASK_BYTEVOQ_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_BYTEVOQ_SHIFT		1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_PFWFQ_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_PFWFQ_SHIFT		2
#घोषणा QM_RF_OPPORTUNISTIC_MASK_VPWFQ_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_VPWFQ_SHIFT		3
#घोषणा QM_RF_OPPORTUNISTIC_MASK_PFRL_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_PFRL_SHIFT		4
#घोषणा QM_RF_OPPORTUNISTIC_MASK_VPQCNRL_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_VPQCNRL_SHIFT		5
#घोषणा QM_RF_OPPORTUNISTIC_MASK_FWPAUSE_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_FWPAUSE_SHIFT		6
#घोषणा QM_RF_OPPORTUNISTIC_MASK_RESERVED0_MASK		0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_RESERVED0_SHIFT	7
#घोषणा QM_RF_OPPORTUNISTIC_MASK_QUEUEEMPTY_MASK	0x1
#घोषणा QM_RF_OPPORTUNISTIC_MASK_QUEUEEMPTY_SHIFT	8
#घोषणा QM_RF_OPPORTUNISTIC_MASK_RESERVED1_MASK		0x7F
#घोषणा QM_RF_OPPORTUNISTIC_MASK_RESERVED1_SHIFT	9
पूर्ण;

/* QM hardware काष्ठाure of QM map memory */
काष्ठा qm_rf_pq_map_e4 अणु
	__le32 reg;
#घोषणा QM_RF_PQ_MAP_E4_PQ_VALID_MASK		0x1
#घोषणा QM_RF_PQ_MAP_E4_PQ_VALID_SHIFT		0
#घोषणा QM_RF_PQ_MAP_E4_RL_ID_MASK		0xFF
#घोषणा QM_RF_PQ_MAP_E4_RL_ID_SHIFT		1
#घोषणा QM_RF_PQ_MAP_E4_VP_PQ_ID_MASK		0x1FF
#घोषणा QM_RF_PQ_MAP_E4_VP_PQ_ID_SHIFT		9
#घोषणा QM_RF_PQ_MAP_E4_VOQ_MASK		0x1F
#घोषणा QM_RF_PQ_MAP_E4_VOQ_SHIFT		18
#घोषणा QM_RF_PQ_MAP_E4_WRR_WEIGHT_GROUP_MASK	0x3
#घोषणा QM_RF_PQ_MAP_E4_WRR_WEIGHT_GROUP_SHIFT	23
#घोषणा QM_RF_PQ_MAP_E4_RL_VALID_MASK		0x1
#घोषणा QM_RF_PQ_MAP_E4_RL_VALID_SHIFT		25
#घोषणा QM_RF_PQ_MAP_E4_RESERVED_MASK		0x3F
#घोषणा QM_RF_PQ_MAP_E4_RESERVED_SHIFT		26
पूर्ण;

/* Completion params क्रम aggregated पूर्णांकerrupt completion */
काष्ठा sdm_agg_पूर्णांक_comp_params अणु
	__le16 params;
#घोषणा SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_MASK	0x3F
#घोषणा SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_SHIFT	0
#घोषणा SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_MASK	0x1
#घोषणा SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_SHIFT	6
#घोषणा SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_MASK	0x1FF
#घोषणा SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_SHIFT	7
पूर्ण;

/* SDM operation gen command (generate aggregative पूर्णांकerrupt) */
काष्ठा sdm_op_gen अणु
	__le32 command;
#घोषणा SDM_OP_GEN_COMP_PARAM_MASK	0xFFFF
#घोषणा SDM_OP_GEN_COMP_PARAM_SHIFT	0
#घोषणा SDM_OP_GEN_COMP_TYPE_MASK	0xF
#घोषणा SDM_OP_GEN_COMP_TYPE_SHIFT	16
#घोषणा SDM_OP_GEN_RESERVED_MASK	0xFFF
#घोषणा SDM_OP_GEN_RESERVED_SHIFT	20
पूर्ण;

/* Physical memory descriptor */
काष्ठा phys_mem_desc अणु
	dma_addr_t phys_addr;
	व्योम *virt_addr;
	u32 size;		/* In bytes */
पूर्ण;

/* Virtual memory descriptor */
काष्ठा virt_mem_desc अणु
	व्योम *ptr;
	u32 size;		/* In bytes */
पूर्ण;

/****************************************/
/* Debug Tools HSI स्थिरants and macros */
/****************************************/

क्रमागत block_id अणु
	BLOCK_GRC,
	BLOCK_MISCS,
	BLOCK_MISC,
	BLOCK_DBU,
	BLOCK_PGLUE_B,
	BLOCK_CNIG,
	BLOCK_CPMU,
	BLOCK_NCSI,
	BLOCK_OPTE,
	BLOCK_BMB,
	BLOCK_PCIE,
	BLOCK_MCP,
	BLOCK_MCP2,
	BLOCK_PSWHST,
	BLOCK_PSWHST2,
	BLOCK_PSWRD,
	BLOCK_PSWRD2,
	BLOCK_PSWWR,
	BLOCK_PSWWR2,
	BLOCK_PSWRQ,
	BLOCK_PSWRQ2,
	BLOCK_PGLCS,
	BLOCK_DMAE,
	BLOCK_PTU,
	BLOCK_TCM,
	BLOCK_MCM,
	BLOCK_UCM,
	BLOCK_XCM,
	BLOCK_YCM,
	BLOCK_PCM,
	BLOCK_QM,
	BLOCK_TM,
	BLOCK_DORQ,
	BLOCK_BRB,
	BLOCK_SRC,
	BLOCK_PRS,
	BLOCK_TSDM,
	BLOCK_MSDM,
	BLOCK_USDM,
	BLOCK_XSDM,
	BLOCK_YSDM,
	BLOCK_PSDM,
	BLOCK_TSEM,
	BLOCK_MSEM,
	BLOCK_USEM,
	BLOCK_XSEM,
	BLOCK_YSEM,
	BLOCK_PSEM,
	BLOCK_RSS,
	BLOCK_TMLD,
	BLOCK_MULD,
	BLOCK_YULD,
	BLOCK_XYLD,
	BLOCK_PRM,
	BLOCK_PBF_PB1,
	BLOCK_PBF_PB2,
	BLOCK_RPB,
	BLOCK_BTB,
	BLOCK_PBF,
	BLOCK_RDIF,
	BLOCK_TDIF,
	BLOCK_CDU,
	BLOCK_CCFC,
	BLOCK_TCFC,
	BLOCK_IGU,
	BLOCK_CAU,
	BLOCK_UMAC,
	BLOCK_XMAC,
	BLOCK_MSTAT,
	BLOCK_DBG,
	BLOCK_NIG,
	BLOCK_WOL,
	BLOCK_BMBN,
	BLOCK_IPC,
	BLOCK_NWM,
	BLOCK_NWS,
	BLOCK_MS,
	BLOCK_PHY_PCIE,
	BLOCK_LED,
	BLOCK_AVS_WRAP,
	BLOCK_PXPREQBUS,
	BLOCK_BAR0_MAP,
	BLOCK_MCP_FIO,
	BLOCK_LAST_INIT,
	BLOCK_PRS_FC,
	BLOCK_PBF_FC,
	BLOCK_NIG_LB_FC,
	BLOCK_NIG_LB_FC_PLLH,
	BLOCK_NIG_TX_FC_PLLH,
	BLOCK_NIG_TX_FC,
	BLOCK_NIG_RX_FC_PLLH,
	BLOCK_NIG_RX_FC,
	MAX_BLOCK_ID
पूर्ण;

/* binary debug buffer types */
क्रमागत bin_dbg_buffer_type अणु
	BIN_BUF_DBG_MODE_TREE,
	BIN_BUF_DBG_DUMP_REG,
	BIN_BUF_DBG_DUMP_MEM,
	BIN_BUF_DBG_IDLE_CHK_REGS,
	BIN_BUF_DBG_IDLE_CHK_IMMS,
	BIN_BUF_DBG_IDLE_CHK_RULES,
	BIN_BUF_DBG_IDLE_CHK_PARSING_DATA,
	BIN_BUF_DBG_ATTN_BLOCKS,
	BIN_BUF_DBG_ATTN_REGS,
	BIN_BUF_DBG_ATTN_INDEXES,
	BIN_BUF_DBG_ATTN_NAME_OFFSETS,
	BIN_BUF_DBG_BLOCKS,
	BIN_BUF_DBG_BLOCKS_CHIP_DATA,
	BIN_BUF_DBG_BUS_LINES,
	BIN_BUF_DBG_BLOCKS_USER_DATA,
	BIN_BUF_DBG_BLOCKS_CHIP_USER_DATA,
	BIN_BUF_DBG_BUS_LINE_NAME_OFFSETS,
	BIN_BUF_DBG_RESET_REGS,
	BIN_BUF_DBG_PARSING_STRINGS,
	MAX_BIN_DBG_BUFFER_TYPE
पूर्ण;


/* Attention bit mapping */
काष्ठा dbg_attn_bit_mapping अणु
	u16 data;
#घोषणा DBG_ATTN_BIT_MAPPING_VAL_MASK			0x7FFF
#घोषणा DBG_ATTN_BIT_MAPPING_VAL_SHIFT			0
#घोषणा DBG_ATTN_BIT_MAPPING_IS_UNUSED_BIT_CNT_MASK	0x1
#घोषणा DBG_ATTN_BIT_MAPPING_IS_UNUSED_BIT_CNT_SHIFT	15
पूर्ण;

/* Attention block per-type data */
काष्ठा dbg_attn_block_type_data अणु
	u16 names_offset;
	u16 reserved1;
	u8 num_regs;
	u8 reserved2;
	u16 regs_offset;

पूर्ण;

/* Block attentions */
काष्ठा dbg_attn_block अणु
	काष्ठा dbg_attn_block_type_data per_type_data[2];
पूर्ण;

/* Attention रेजिस्टर result */
काष्ठा dbg_attn_reg_result अणु
	u32 data;
#घोषणा DBG_ATTN_REG_RESULT_STS_ADDRESS_MASK	0xFFFFFF
#घोषणा DBG_ATTN_REG_RESULT_STS_ADDRESS_SHIFT	0
#घोषणा DBG_ATTN_REG_RESULT_NUM_REG_ATTN_MASK	0xFF
#घोषणा DBG_ATTN_REG_RESULT_NUM_REG_ATTN_SHIFT	24
	u16 block_attn_offset;
	u16 reserved;
	u32 sts_val;
	u32 mask_val;
पूर्ण;

/* Attention block result */
काष्ठा dbg_attn_block_result अणु
	u8 block_id;
	u8 data;
#घोषणा DBG_ATTN_BLOCK_RESULT_ATTN_TYPE_MASK	0x3
#घोषणा DBG_ATTN_BLOCK_RESULT_ATTN_TYPE_SHIFT	0
#घोषणा DBG_ATTN_BLOCK_RESULT_NUM_REGS_MASK	0x3F
#घोषणा DBG_ATTN_BLOCK_RESULT_NUM_REGS_SHIFT	2
	u16 names_offset;
	काष्ठा dbg_attn_reg_result reg_results[15];
पूर्ण;

/* Mode header */
काष्ठा dbg_mode_hdr अणु
	u16 data;
#घोषणा DBG_MODE_HDR_EVAL_MODE_MASK		0x1
#घोषणा DBG_MODE_HDR_EVAL_MODE_SHIFT		0
#घोषणा DBG_MODE_HDR_MODES_BUF_OFFSET_MASK	0x7FFF
#घोषणा DBG_MODE_HDR_MODES_BUF_OFFSET_SHIFT	1
पूर्ण;

/* Attention रेजिस्टर */
काष्ठा dbg_attn_reg अणु
	काष्ठा dbg_mode_hdr mode;
	u16 block_attn_offset;
	u32 data;
#घोषणा DBG_ATTN_REG_STS_ADDRESS_MASK	0xFFFFFF
#घोषणा DBG_ATTN_REG_STS_ADDRESS_SHIFT	0
#घोषणा DBG_ATTN_REG_NUM_REG_ATTN_MASK	0xFF
#घोषणा DBG_ATTN_REG_NUM_REG_ATTN_SHIFT 24
	u32 sts_clr_address;
	u32 mask_address;
पूर्ण;

/* Attention types */
क्रमागत dbg_attn_type अणु
	ATTN_TYPE_INTERRUPT,
	ATTN_TYPE_PARITY,
	MAX_DBG_ATTN_TYPE
पूर्ण;

/* Block debug data */
काष्ठा dbg_block अणु
	u8 name[15];
	u8 associated_storm_letter;
पूर्ण;

/* Chip-specअगरic block debug data */
काष्ठा dbg_block_chip अणु
	u8 flags;
#घोषणा DBG_BLOCK_CHIP_IS_REMOVED_MASK		 0x1
#घोषणा DBG_BLOCK_CHIP_IS_REMOVED_SHIFT		 0
#घोषणा DBG_BLOCK_CHIP_HAS_RESET_REG_MASK	 0x1
#घोषणा DBG_BLOCK_CHIP_HAS_RESET_REG_SHIFT	 1
#घोषणा DBG_BLOCK_CHIP_UNRESET_BEFORE_DUMP_MASK  0x1
#घोषणा DBG_BLOCK_CHIP_UNRESET_BEFORE_DUMP_SHIFT 2
#घोषणा DBG_BLOCK_CHIP_HAS_DBG_BUS_MASK		 0x1
#घोषणा DBG_BLOCK_CHIP_HAS_DBG_BUS_SHIFT	 3
#घोषणा DBG_BLOCK_CHIP_HAS_LATENCY_EVENTS_MASK	 0x1
#घोषणा DBG_BLOCK_CHIP_HAS_LATENCY_EVENTS_SHIFT  4
#घोषणा DBG_BLOCK_CHIP_RESERVED0_MASK		 0x7
#घोषणा DBG_BLOCK_CHIP_RESERVED0_SHIFT		 5
	u8 dbg_client_id;
	u8 reset_reg_id;
	u8 reset_reg_bit_offset;
	काष्ठा dbg_mode_hdr dbg_bus_mode;
	u16 reserved1;
	u8 reserved2;
	u8 num_of_dbg_bus_lines;
	u16 dbg_bus_lines_offset;
	u32 dbg_select_reg_addr;
	u32 dbg_dword_enable_reg_addr;
	u32 dbg_shअगरt_reg_addr;
	u32 dbg_क्रमce_valid_reg_addr;
	u32 dbg_क्रमce_frame_reg_addr;
पूर्ण;

/* Chip-specअगरic block user debug data */
काष्ठा dbg_block_chip_user अणु
	u8 num_of_dbg_bus_lines;
	u8 has_latency_events;
	u16 names_offset;
पूर्ण;

/* Block user debug data */
काष्ठा dbg_block_user अणु
	u8 name[16];
पूर्ण;

/* Block Debug line data */
काष्ठा dbg_bus_line अणु
	u8 data;
#घोषणा DBG_BUS_LINE_NUM_OF_GROUPS_MASK		0xF
#घोषणा DBG_BUS_LINE_NUM_OF_GROUPS_SHIFT	0
#घोषणा DBG_BUS_LINE_IS_256B_MASK		0x1
#घोषणा DBG_BUS_LINE_IS_256B_SHIFT		4
#घोषणा DBG_BUS_LINE_RESERVED_MASK		0x7
#घोषणा DBG_BUS_LINE_RESERVED_SHIFT		5
	u8 group_sizes;
पूर्ण;

/* Condition header क्रम रेजिस्टरs dump */
काष्ठा dbg_dump_cond_hdr अणु
	काष्ठा dbg_mode_hdr mode; /* Mode header */
	u8 block_id; /* block ID */
	u8 data_size; /* size in dwords of the data following this header */
पूर्ण;

/* Memory data क्रम रेजिस्टरs dump */
काष्ठा dbg_dump_mem अणु
	u32 dword0;
#घोषणा DBG_DUMP_MEM_ADDRESS_MASK	0xFFFFFF
#घोषणा DBG_DUMP_MEM_ADDRESS_SHIFT	0
#घोषणा DBG_DUMP_MEM_MEM_GROUP_ID_MASK	0xFF
#घोषणा DBG_DUMP_MEM_MEM_GROUP_ID_SHIFT	24
	u32 dword1;
#घोषणा DBG_DUMP_MEM_LENGTH_MASK	0xFFFFFF
#घोषणा DBG_DUMP_MEM_LENGTH_SHIFT	0
#घोषणा DBG_DUMP_MEM_WIDE_BUS_MASK	0x1
#घोषणा DBG_DUMP_MEM_WIDE_BUS_SHIFT	24
#घोषणा DBG_DUMP_MEM_RESERVED_MASK	0x7F
#घोषणा DBG_DUMP_MEM_RESERVED_SHIFT	25
पूर्ण;

/* Register data क्रम रेजिस्टरs dump */
काष्ठा dbg_dump_reg अणु
	u32 data;
#घोषणा DBG_DUMP_REG_ADDRESS_MASK	0x7FFFFF
#घोषणा DBG_DUMP_REG_ADDRESS_SHIFT	0
#घोषणा DBG_DUMP_REG_WIDE_BUS_MASK	0x1
#घोषणा DBG_DUMP_REG_WIDE_BUS_SHIFT	23
#घोषणा DBG_DUMP_REG_LENGTH_MASK	0xFF
#घोषणा DBG_DUMP_REG_LENGTH_SHIFT	24
पूर्ण;

/* Split header क्रम रेजिस्टरs dump */
काष्ठा dbg_dump_split_hdr अणु
	u32 hdr;
#घोषणा DBG_DUMP_SPLIT_HDR_DATA_SIZE_MASK	0xFFFFFF
#घोषणा DBG_DUMP_SPLIT_HDR_DATA_SIZE_SHIFT	0
#घोषणा DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID_MASK	0xFF
#घोषणा DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID_SHIFT	24
पूर्ण;

/* Condition header क्रम idle check */
काष्ठा dbg_idle_chk_cond_hdr अणु
	काष्ठा dbg_mode_hdr mode; /* Mode header */
	u16 data_size; /* size in dwords of the data following this header */
पूर्ण;

/* Idle Check condition रेजिस्टर */
काष्ठा dbg_idle_chk_cond_reg अणु
	u32 data;
#घोषणा DBG_IDLE_CHK_COND_REG_ADDRESS_MASK	0x7FFFFF
#घोषणा DBG_IDLE_CHK_COND_REG_ADDRESS_SHIFT	0
#घोषणा DBG_IDLE_CHK_COND_REG_WIDE_BUS_MASK	0x1
#घोषणा DBG_IDLE_CHK_COND_REG_WIDE_BUS_SHIFT	23
#घोषणा DBG_IDLE_CHK_COND_REG_BLOCK_ID_MASK	0xFF
#घोषणा DBG_IDLE_CHK_COND_REG_BLOCK_ID_SHIFT	24
	u16 num_entries;
	u8 entry_size;
	u8 start_entry;
पूर्ण;

/* Idle Check info रेजिस्टर */
काष्ठा dbg_idle_chk_info_reg अणु
	u32 data;
#घोषणा DBG_IDLE_CHK_INFO_REG_ADDRESS_MASK	0x7FFFFF
#घोषणा DBG_IDLE_CHK_INFO_REG_ADDRESS_SHIFT	0
#घोषणा DBG_IDLE_CHK_INFO_REG_WIDE_BUS_MASK	0x1
#घोषणा DBG_IDLE_CHK_INFO_REG_WIDE_BUS_SHIFT	23
#घोषणा DBG_IDLE_CHK_INFO_REG_BLOCK_ID_MASK	0xFF
#घोषणा DBG_IDLE_CHK_INFO_REG_BLOCK_ID_SHIFT	24
	u16 size; /* रेजिस्टर size in dwords */
	काष्ठा dbg_mode_hdr mode; /* Mode header */
पूर्ण;

/* Idle Check रेजिस्टर */
जोड़ dbg_idle_chk_reg अणु
	काष्ठा dbg_idle_chk_cond_reg cond_reg; /* condition रेजिस्टर */
	काष्ठा dbg_idle_chk_info_reg info_reg; /* info रेजिस्टर */
पूर्ण;

/* Idle Check result header */
काष्ठा dbg_idle_chk_result_hdr अणु
	u16 rule_id; /* Failing rule index */
	u16 mem_entry_id; /* Failing memory entry index */
	u8 num_dumped_cond_regs; /* number of dumped condition रेजिस्टरs */
	u8 num_dumped_info_regs; /* number of dumped condition रेजिस्टरs */
	u8 severity; /* from dbg_idle_chk_severity_types क्रमागत */
	u8 reserved;
पूर्ण;

/* Idle Check result रेजिस्टर header */
काष्ठा dbg_idle_chk_result_reg_hdr अणु
	u8 data;
#घोषणा DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM_MASK  0x1
#घोषणा DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM_SHIFT 0
#घोषणा DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID_MASK  0x7F
#घोषणा DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID_SHIFT 1
	u8 start_entry; /* index of the first checked entry */
	u16 size; /* रेजिस्टर size in dwords */
पूर्ण;

/* Idle Check rule */
काष्ठा dbg_idle_chk_rule अणु
	u16 rule_id; /* Idle Check rule ID */
	u8 severity; /* value from dbg_idle_chk_severity_types क्रमागत */
	u8 cond_id; /* Condition ID */
	u8 num_cond_regs; /* number of condition रेजिस्टरs */
	u8 num_info_regs; /* number of info रेजिस्टरs */
	u8 num_imms; /* number of immediates in the condition */
	u8 reserved1;
	u16 reg_offset; /* offset of this rules रेजिस्टरs in the idle check
			 * रेजिस्टर array (in dbg_idle_chk_reg units).
			 */
	u16 imm_offset; /* offset of this rules immediate values in the
			 * immediate values array (in dwords).
			 */
पूर्ण;

/* Idle Check rule parsing data */
काष्ठा dbg_idle_chk_rule_parsing_data अणु
	u32 data;
#घोषणा DBG_IDLE_CHK_RULE_PARSING_DATA_HAS_FW_MSG_MASK	0x1
#घोषणा DBG_IDLE_CHK_RULE_PARSING_DATA_HAS_FW_MSG_SHIFT	0
#घोषणा DBG_IDLE_CHK_RULE_PARSING_DATA_STR_OFFSET_MASK	0x7FFFFFFF
#घोषणा DBG_IDLE_CHK_RULE_PARSING_DATA_STR_OFFSET_SHIFT	1
पूर्ण;

/* Idle check severity types */
क्रमागत dbg_idle_chk_severity_types अणु
	/* idle check failure should cause an error */
	IDLE_CHK_SEVERITY_ERROR,
	/* idle check failure should cause an error only अगर theres no traffic */
	IDLE_CHK_SEVERITY_ERROR_NO_TRAFFIC,
	/* idle check failure should cause a warning */
	IDLE_CHK_SEVERITY_WARNING,
	MAX_DBG_IDLE_CHK_SEVERITY_TYPES
पूर्ण;

/* Reset रेजिस्टर */
काष्ठा dbg_reset_reg अणु
	u32 data;
#घोषणा DBG_RESET_REG_ADDR_MASK        0xFFFFFF
#घोषणा DBG_RESET_REG_ADDR_SHIFT       0
#घोषणा DBG_RESET_REG_IS_REMOVED_MASK  0x1
#घोषणा DBG_RESET_REG_IS_REMOVED_SHIFT 24
#घोषणा DBG_RESET_REG_RESERVED_MASK    0x7F
#घोषणा DBG_RESET_REG_RESERVED_SHIFT   25
पूर्ण;

/* Debug Bus block data */
काष्ठा dbg_bus_block_data अणु
	u8 enable_mask;
	u8 right_shअगरt;
	u8 क्रमce_valid_mask;
	u8 क्रमce_frame_mask;
	u8 dword_mask;
	u8 line_num;
	u8 hw_id;
	u8 flags;
#घोषणा DBG_BUS_BLOCK_DATA_IS_256B_LINE_MASK  0x1
#घोषणा DBG_BUS_BLOCK_DATA_IS_256B_LINE_SHIFT 0
#घोषणा DBG_BUS_BLOCK_DATA_RESERVED_MASK      0x7F
#घोषणा DBG_BUS_BLOCK_DATA_RESERVED_SHIFT     1
पूर्ण;

क्रमागत dbg_bus_clients अणु
	DBG_BUS_CLIENT_RBCN,
	DBG_BUS_CLIENT_RBCP,
	DBG_BUS_CLIENT_RBCR,
	DBG_BUS_CLIENT_RBCT,
	DBG_BUS_CLIENT_RBCU,
	DBG_BUS_CLIENT_RBCF,
	DBG_BUS_CLIENT_RBCX,
	DBG_BUS_CLIENT_RBCS,
	DBG_BUS_CLIENT_RBCH,
	DBG_BUS_CLIENT_RBCZ,
	DBG_BUS_CLIENT_OTHER_ENGINE,
	DBG_BUS_CLIENT_TIMESTAMP,
	DBG_BUS_CLIENT_CPU,
	DBG_BUS_CLIENT_RBCY,
	DBG_BUS_CLIENT_RBCQ,
	DBG_BUS_CLIENT_RBCM,
	DBG_BUS_CLIENT_RBCB,
	DBG_BUS_CLIENT_RBCW,
	DBG_BUS_CLIENT_RBCV,
	MAX_DBG_BUS_CLIENTS
पूर्ण;

/* Debug Bus स्थिरraपूर्णांक operation types */
क्रमागत dbg_bus_स्थिरraपूर्णांक_ops अणु
	DBG_BUS_CONSTRAINT_OP_EQ,
	DBG_BUS_CONSTRAINT_OP_NE,
	DBG_BUS_CONSTRAINT_OP_LT,
	DBG_BUS_CONSTRAINT_OP_LTC,
	DBG_BUS_CONSTRAINT_OP_LE,
	DBG_BUS_CONSTRAINT_OP_LEC,
	DBG_BUS_CONSTRAINT_OP_GT,
	DBG_BUS_CONSTRAINT_OP_GTC,
	DBG_BUS_CONSTRAINT_OP_GE,
	DBG_BUS_CONSTRAINT_OP_GEC,
	MAX_DBG_BUS_CONSTRAINT_OPS
पूर्ण;

/* Debug Bus trigger state data */
काष्ठा dbg_bus_trigger_state_data अणु
	u8 msg_len;
	u8 स्थिरraपूर्णांक_dword_mask;
	u8 storm_id;
	u8 reserved;
पूर्ण;

/* Debug Bus memory address */
काष्ठा dbg_bus_mem_addr अणु
	u32 lo;
	u32 hi;
पूर्ण;

/* Debug Bus PCI buffer data */
काष्ठा dbg_bus_pci_buf_data अणु
	काष्ठा dbg_bus_mem_addr phys_addr; /* PCI buffer physical address */
	काष्ठा dbg_bus_mem_addr virt_addr; /* PCI buffer भव address */
	u32 size; /* PCI buffer size in bytes */
पूर्ण;

/* Debug Bus Storm EID range filter params */
काष्ठा dbg_bus_storm_eid_range_params अणु
	u8 min; /* Minimal event ID to filter on */
	u8 max; /* Maximal event ID to filter on */
पूर्ण;

/* Debug Bus Storm EID mask filter params */
काष्ठा dbg_bus_storm_eid_mask_params अणु
	u8 val; /* Event ID value */
	u8 mask; /* Event ID mask. 1s in the mask = करोnt care bits. */
पूर्ण;

/* Debug Bus Storm EID filter params */
जोड़ dbg_bus_storm_eid_params अणु
	काष्ठा dbg_bus_storm_eid_range_params range;
	काष्ठा dbg_bus_storm_eid_mask_params mask;
पूर्ण;

/* Debug Bus Storm data */
काष्ठा dbg_bus_storm_data अणु
	u8 enabled;
	u8 mode;
	u8 hw_id;
	u8 eid_filter_en;
	u8 eid_range_not_mask;
	u8 cid_filter_en;
	जोड़ dbg_bus_storm_eid_params eid_filter_params;
	u32 cid;
पूर्ण;

/* Debug Bus data */
काष्ठा dbg_bus_data अणु
	u32 app_version;
	u8 state;
	u8 mode_256b_en;
	u8 num_enabled_blocks;
	u8 num_enabled_storms;
	u8 target;
	u8 one_shot_en;
	u8 grc_input_en;
	u8 बारtamp_input_en;
	u8 filter_en;
	u8 adding_filter;
	u8 filter_pre_trigger;
	u8 filter_post_trigger;
	u8 trigger_en;
	u8 filter_स्थिरraपूर्णांक_dword_mask;
	u8 next_trigger_state;
	u8 next_स्थिरraपूर्णांक_id;
	काष्ठा dbg_bus_trigger_state_data trigger_states[3];
	u8 filter_msg_len;
	u8 rcv_from_other_engine;
	u8 blocks_dword_mask;
	u8 blocks_dword_overlap;
	u32 hw_id_mask;
	काष्ठा dbg_bus_pci_buf_data pci_buf;
	काष्ठा dbg_bus_block_data blocks[132];
	काष्ठा dbg_bus_storm_data storms[6];
पूर्ण;

/* Debug bus states */
क्रमागत dbg_bus_states अणु
	DBG_BUS_STATE_IDLE,
	DBG_BUS_STATE_READY,
	DBG_BUS_STATE_RECORDING,
	DBG_BUS_STATE_STOPPED,
	MAX_DBG_BUS_STATES
पूर्ण;

/* Debug Bus Storm modes */
क्रमागत dbg_bus_storm_modes अणु
	DBG_BUS_STORM_MODE_PRINTF,
	DBG_BUS_STORM_MODE_PRAM_ADDR,
	DBG_BUS_STORM_MODE_DRA_RW,
	DBG_BUS_STORM_MODE_DRA_W,
	DBG_BUS_STORM_MODE_LD_ST_ADDR,
	DBG_BUS_STORM_MODE_DRA_FSM,
	DBG_BUS_STORM_MODE_FAST_DBGMUX,
	DBG_BUS_STORM_MODE_RH,
	DBG_BUS_STORM_MODE_RH_WITH_STORE,
	DBG_BUS_STORM_MODE_FOC,
	DBG_BUS_STORM_MODE_EXT_STORE,
	MAX_DBG_BUS_STORM_MODES
पूर्ण;

/* Debug bus target IDs */
क्रमागत dbg_bus_tarमाला_लो अणु
	DBG_BUS_TARGET_ID_INT_BUF,
	DBG_BUS_TARGET_ID_NIG,
	DBG_BUS_TARGET_ID_PCI,
	MAX_DBG_BUS_TARGETS
पूर्ण;

/* GRC Dump data */
काष्ठा dbg_grc_data अणु
	u8 params_initialized;
	u8 reserved1;
	u16 reserved2;
	u32 param_val[48];
पूर्ण;

/* Debug GRC params */
क्रमागत dbg_grc_params अणु
	DBG_GRC_PARAM_DUMP_TSTORM,
	DBG_GRC_PARAM_DUMP_MSTORM,
	DBG_GRC_PARAM_DUMP_USTORM,
	DBG_GRC_PARAM_DUMP_XSTORM,
	DBG_GRC_PARAM_DUMP_YSTORM,
	DBG_GRC_PARAM_DUMP_PSTORM,
	DBG_GRC_PARAM_DUMP_REGS,
	DBG_GRC_PARAM_DUMP_RAM,
	DBG_GRC_PARAM_DUMP_PBUF,
	DBG_GRC_PARAM_DUMP_IOR,
	DBG_GRC_PARAM_DUMP_VFC,
	DBG_GRC_PARAM_DUMP_CM_CTX,
	DBG_GRC_PARAM_DUMP_PXP,
	DBG_GRC_PARAM_DUMP_RSS,
	DBG_GRC_PARAM_DUMP_CAU,
	DBG_GRC_PARAM_DUMP_QM,
	DBG_GRC_PARAM_DUMP_MCP,
	DBG_GRC_PARAM_DUMP_DORQ,
	DBG_GRC_PARAM_DUMP_CFC,
	DBG_GRC_PARAM_DUMP_IGU,
	DBG_GRC_PARAM_DUMP_BRB,
	DBG_GRC_PARAM_DUMP_BTB,
	DBG_GRC_PARAM_DUMP_BMB,
	DBG_GRC_PARAM_RESERVD1,
	DBG_GRC_PARAM_DUMP_MULD,
	DBG_GRC_PARAM_DUMP_PRS,
	DBG_GRC_PARAM_DUMP_DMAE,
	DBG_GRC_PARAM_DUMP_TM,
	DBG_GRC_PARAM_DUMP_SDM,
	DBG_GRC_PARAM_DUMP_DIF,
	DBG_GRC_PARAM_DUMP_STATIC,
	DBG_GRC_PARAM_UNSTALL,
	DBG_GRC_PARAM_RESERVED2,
	DBG_GRC_PARAM_MCP_TRACE_META_SIZE,
	DBG_GRC_PARAM_EXCLUDE_ALL,
	DBG_GRC_PARAM_CRASH,
	DBG_GRC_PARAM_PARITY_SAFE,
	DBG_GRC_PARAM_DUMP_CM,
	DBG_GRC_PARAM_DUMP_PHY,
	DBG_GRC_PARAM_NO_MCP,
	DBG_GRC_PARAM_NO_FW_VER,
	DBG_GRC_PARAM_RESERVED3,
	DBG_GRC_PARAM_DUMP_MCP_HW_DUMP,
	DBG_GRC_PARAM_DUMP_ILT_CDUC,
	DBG_GRC_PARAM_DUMP_ILT_CDUT,
	DBG_GRC_PARAM_DUMP_CAU_EXT,
	MAX_DBG_GRC_PARAMS
पूर्ण;

/* Debug status codes */
क्रमागत dbg_status अणु
	DBG_STATUS_OK,
	DBG_STATUS_APP_VERSION_NOT_SET,
	DBG_STATUS_UNSUPPORTED_APP_VERSION,
	DBG_STATUS_DBG_BLOCK_NOT_RESET,
	DBG_STATUS_INVALID_ARGS,
	DBG_STATUS_OUTPUT_ALREADY_SET,
	DBG_STATUS_INVALID_PCI_BUF_SIZE,
	DBG_STATUS_PCI_BUF_ALLOC_FAILED,
	DBG_STATUS_PCI_BUF_NOT_ALLOCATED,
	DBG_STATUS_INVALID_FILTER_TRIGGER_DWORDS,
	DBG_STATUS_NO_MATCHING_FRAMING_MODE,
	DBG_STATUS_VFC_READ_ERROR,
	DBG_STATUS_STORM_ALREADY_ENABLED,
	DBG_STATUS_STORM_NOT_ENABLED,
	DBG_STATUS_BLOCK_ALREADY_ENABLED,
	DBG_STATUS_BLOCK_NOT_ENABLED,
	DBG_STATUS_NO_INPUT_ENABLED,
	DBG_STATUS_NO_FILTER_TRIGGER_256B,
	DBG_STATUS_FILTER_ALREADY_ENABLED,
	DBG_STATUS_TRIGGER_ALREADY_ENABLED,
	DBG_STATUS_TRIGGER_NOT_ENABLED,
	DBG_STATUS_CANT_ADD_CONSTRAINT,
	DBG_STATUS_TOO_MANY_TRIGGER_STATES,
	DBG_STATUS_TOO_MANY_CONSTRAINTS,
	DBG_STATUS_RECORDING_NOT_STARTED,
	DBG_STATUS_DATA_DIDNT_TRIGGER,
	DBG_STATUS_NO_DATA_RECORDED,
	DBG_STATUS_DUMP_BUF_TOO_SMALL,
	DBG_STATUS_DUMP_NOT_CHUNK_ALIGNED,
	DBG_STATUS_UNKNOWN_CHIP,
	DBG_STATUS_VIRT_MEM_ALLOC_FAILED,
	DBG_STATUS_BLOCK_IN_RESET,
	DBG_STATUS_INVALID_TRACE_SIGNATURE,
	DBG_STATUS_INVALID_NVRAM_BUNDLE,
	DBG_STATUS_NVRAM_GET_IMAGE_FAILED,
	DBG_STATUS_NON_ALIGNED_NVRAM_IMAGE,
	DBG_STATUS_NVRAM_READ_FAILED,
	DBG_STATUS_IDLE_CHK_PARSE_FAILED,
	DBG_STATUS_MCP_TRACE_BAD_DATA,
	DBG_STATUS_MCP_TRACE_NO_META,
	DBG_STATUS_MCP_COULD_NOT_HALT,
	DBG_STATUS_MCP_COULD_NOT_RESUME,
	DBG_STATUS_RESERVED0,
	DBG_STATUS_SEMI_FIFO_NOT_EMPTY,
	DBG_STATUS_IGU_FIFO_BAD_DATA,
	DBG_STATUS_MCP_COULD_NOT_MASK_PRTY,
	DBG_STATUS_FW_ASSERTS_PARSE_FAILED,
	DBG_STATUS_REG_FIFO_BAD_DATA,
	DBG_STATUS_PROTECTION_OVERRIDE_BAD_DATA,
	DBG_STATUS_DBG_ARRAY_NOT_SET,
	DBG_STATUS_RESERVED1,
	DBG_STATUS_NON_MATCHING_LINES,
	DBG_STATUS_INSUFFICIENT_HW_IDS,
	DBG_STATUS_DBG_BUS_IN_USE,
	DBG_STATUS_INVALID_STORM_DBG_MODE,
	DBG_STATUS_OTHER_ENGINE_BB_ONLY,
	DBG_STATUS_FILTER_SINGLE_HW_ID,
	DBG_STATUS_TRIGGER_SINGLE_HW_ID,
	DBG_STATUS_MISSING_TRIGGER_STATE_STORM,
	MAX_DBG_STATUS
पूर्ण;

/* Debug Storms IDs */
क्रमागत dbg_storms अणु
	DBG_TSTORM_ID,
	DBG_MSTORM_ID,
	DBG_USTORM_ID,
	DBG_XSTORM_ID,
	DBG_YSTORM_ID,
	DBG_PSTORM_ID,
	MAX_DBG_STORMS
पूर्ण;

/* Idle Check data */
काष्ठा idle_chk_data अणु
	u32 buf_size;
	u8 buf_size_set;
	u8 reserved1;
	u16 reserved2;
पूर्ण;

काष्ठा pretend_params अणु
	u8 split_type;
	u8 reserved;
	u16 split_id;
पूर्ण;

/* Debug Tools data (per HW function)
 */
काष्ठा dbg_tools_data अणु
	काष्ठा dbg_grc_data grc;
	काष्ठा dbg_bus_data bus;
	काष्ठा idle_chk_data idle_chk;
	u8 mode_enable[40];
	u8 block_in_reset[132];
	u8 chip_id;
	u8 hw_type;
	u8 num_ports;
	u8 num_pfs_per_port;
	u8 num_vfs;
	u8 initialized;
	u8 use_dmae;
	u8 reserved;
	काष्ठा pretend_params pretend;
	u32 num_regs_पढ़ो;
पूर्ण;

/* ILT Clients */
क्रमागत ilt_clients अणु
	ILT_CLI_CDUC,
	ILT_CLI_CDUT,
	ILT_CLI_QM,
	ILT_CLI_TM,
	ILT_CLI_SRC,
	ILT_CLI_TSDM,
	ILT_CLI_RGFS,
	ILT_CLI_TGFS,
	MAX_ILT_CLIENTS
पूर्ण;

/********************************/
/* HSI Init Functions स्थिरants */
/********************************/

/* Number of VLAN priorities */
#घोषणा NUM_OF_VLAN_PRIORITIES	8

/* BRB RAM init requirements */
काष्ठा init_brb_ram_req अणु
	u32 guranteed_per_tc;
	u32 headroom_per_tc;
	u32 min_pkt_size;
	u32 max_ports_per_engine;
	u8 num_active_tcs[MAX_NUM_PORTS];
पूर्ण;

/* ETS per-TC init requirements */
काष्ठा init_ets_tc_req अणु
	u8 use_sp;
	u8 use_wfq;
	u16 weight;
पूर्ण;

/* ETS init requirements */
काष्ठा init_ets_req अणु
	u32 mtu;
	काष्ठा init_ets_tc_req tc_req[NUM_OF_TCS];
पूर्ण;

/* NIG LB RL init requirements */
काष्ठा init_nig_lb_rl_req अणु
	u16 lb_mac_rate;
	u16 lb_rate;
	u32 mtu;
	u16 tc_rate[NUM_OF_PHYS_TCS];
पूर्ण;

/* NIG TC mapping क्रम each priority */
काष्ठा init_nig_pri_tc_map_entry अणु
	u8 tc_id;
	u8 valid;
पूर्ण;

/* NIG priority to TC map init requirements */
काष्ठा init_nig_pri_tc_map_req अणु
	काष्ठा init_nig_pri_tc_map_entry pri[NUM_OF_VLAN_PRIORITIES];
पूर्ण;

/* QM per global RL init parameters */
काष्ठा init_qm_global_rl_params अणु
	u32 rate_limit;
पूर्ण;

/* QM per-port init parameters */
काष्ठा init_qm_port_params अणु
	u16 active_phys_tcs;
	u16 num_pbf_cmd_lines;
	u16 num_btb_blocks;
	u8 active;
	u8 reserved;
पूर्ण;

/* QM per-PQ init parameters */
काष्ठा init_qm_pq_params अणु
	u8 vport_id;
	u8 tc_id;
	u8 wrr_group;
	u8 rl_valid;
	u16 rl_id;
	u8 port_id;
	u8 reserved;
पूर्ण;

/* QM per-vport init parameters */
काष्ठा init_qm_vport_params अणु
	u16 wfq;
	u16 first_tx_pq_id[NUM_OF_TCS];
पूर्ण;

/**************************************/
/* Init Tool HSI स्थिरants and macros */
/**************************************/

/* Width of GRC address in bits (addresses are specअगरied in dwords) */
#घोषणा GRC_ADDR_BITS	23
#घोषणा MAX_GRC_ADDR	(BIT(GRC_ADDR_BITS) - 1)

/* indicates an init that should be applied to any phase ID */
#घोषणा ANY_PHASE_ID	0xffff

/* Max size in dwords of a zipped array */
#घोषणा MAX_ZIPPED_SIZE	8192
क्रमागत chip_ids अणु
	CHIP_BB,
	CHIP_K2,
	MAX_CHIP_IDS
पूर्ण;

काष्ठा fw_निश्चितs_ram_section अणु
	__le16 section_ram_line_offset;
	__le16 section_ram_line_size;
	u8 list_dword_offset;
	u8 list_element_dword_size;
	u8 list_num_elements;
	u8 list_next_index_dword_offset;
पूर्ण;

काष्ठा fw_ver_num अणु
	u8 major;
	u8 minor;
	u8 rev;
	u8 eng;
पूर्ण;

काष्ठा fw_ver_info अणु
	__le16 tools_ver;
	u8 image_id;
	u8 reserved1;
	काष्ठा fw_ver_num num;
	__le32 बारtamp;
	__le32 reserved2;
पूर्ण;

काष्ठा fw_info अणु
	काष्ठा fw_ver_info ver;
	काष्ठा fw_निश्चितs_ram_section fw_निश्चितs_section;
पूर्ण;

काष्ठा fw_info_location अणु
	__le32 grc_addr;
	__le32 size;
पूर्ण;

क्रमागत init_modes अणु
	MODE_RESERVED,
	MODE_BB,
	MODE_K2,
	MODE_ASIC,
	MODE_RESERVED2,
	MODE_RESERVED3,
	MODE_RESERVED4,
	MODE_RESERVED5,
	MODE_SF,
	MODE_MF_SD,
	MODE_MF_SI,
	MODE_PORTS_PER_ENG_1,
	MODE_PORTS_PER_ENG_2,
	MODE_PORTS_PER_ENG_4,
	MODE_100G,
	MODE_RESERVED6,
	MODE_RESERVED7,
	MAX_INIT_MODES
पूर्ण;

क्रमागत init_phases अणु
	PHASE_ENGINE,
	PHASE_PORT,
	PHASE_PF,
	PHASE_VF,
	PHASE_QM_PF,
	MAX_INIT_PHASES
पूर्ण;

क्रमागत init_split_types अणु
	SPLIT_TYPE_NONE,
	SPLIT_TYPE_PORT,
	SPLIT_TYPE_PF,
	SPLIT_TYPE_PORT_PF,
	SPLIT_TYPE_VF,
	MAX_INIT_SPLIT_TYPES
पूर्ण;

/* Binary buffer header */
काष्ठा bin_buffer_hdr अणु
	u32 offset;
	u32 length;
पूर्ण;

/* Binary init buffer types */
क्रमागत bin_init_buffer_type अणु
	BIN_BUF_INIT_FW_VER_INFO,
	BIN_BUF_INIT_CMD,
	BIN_BUF_INIT_VAL,
	BIN_BUF_INIT_MODE_TREE,
	BIN_BUF_INIT_IRO,
	BIN_BUF_INIT_OVERLAYS,
	MAX_BIN_INIT_BUFFER_TYPE
पूर्ण;

/* FW overlay buffer header */
काष्ठा fw_overlay_buf_hdr अणु
	u32 data;
#घोषणा FW_OVERLAY_BUF_HDR_STORM_ID_MASK  0xFF
#घोषणा FW_OVERLAY_BUF_HDR_STORM_ID_SHIFT 0
#घोषणा FW_OVERLAY_BUF_HDR_BUF_SIZE_MASK  0xFFFFFF
#घोषणा FW_OVERLAY_BUF_HDR_BUF_SIZE_SHIFT 8
पूर्ण;

/* init array header: raw */
काष्ठा init_array_raw_hdr अणु
	__le32						data;
#घोषणा INIT_ARRAY_RAW_HDR_TYPE_MASK			0xF
#घोषणा INIT_ARRAY_RAW_HDR_TYPE_SHIFT			0
#घोषणा INIT_ARRAY_RAW_HDR_PARAMS_MASK			0xFFFFFFF
#घोषणा INIT_ARRAY_RAW_HDR_PARAMS_SHIFT			4
पूर्ण;

/* init array header: standard */
काष्ठा init_array_standard_hdr अणु
	__le32						data;
#घोषणा INIT_ARRAY_STANDARD_HDR_TYPE_MASK		0xF
#घोषणा INIT_ARRAY_STANDARD_HDR_TYPE_SHIFT		0
#घोषणा INIT_ARRAY_STANDARD_HDR_SIZE_MASK		0xFFFFFFF
#घोषणा INIT_ARRAY_STANDARD_HDR_SIZE_SHIFT		4
पूर्ण;

/* init array header: zipped */
काष्ठा init_array_zipped_hdr अणु
	__le32						data;
#घोषणा INIT_ARRAY_ZIPPED_HDR_TYPE_MASK			0xF
#घोषणा INIT_ARRAY_ZIPPED_HDR_TYPE_SHIFT		0
#घोषणा INIT_ARRAY_ZIPPED_HDR_ZIPPED_SIZE_MASK		0xFFFFFFF
#घोषणा INIT_ARRAY_ZIPPED_HDR_ZIPPED_SIZE_SHIFT		4
पूर्ण;

/* init array header: pattern */
काष्ठा init_array_pattern_hdr अणु
	__le32						data;
#घोषणा INIT_ARRAY_PATTERN_HDR_TYPE_MASK		0xF
#घोषणा INIT_ARRAY_PATTERN_HDR_TYPE_SHIFT		0
#घोषणा INIT_ARRAY_PATTERN_HDR_PATTERN_SIZE_MASK	0xF
#घोषणा INIT_ARRAY_PATTERN_HDR_PATTERN_SIZE_SHIFT	4
#घोषणा INIT_ARRAY_PATTERN_HDR_REPETITIONS_MASK		0xFFFFFF
#घोषणा INIT_ARRAY_PATTERN_HDR_REPETITIONS_SHIFT	8
पूर्ण;

/* init array header जोड़ */
जोड़ init_array_hdr अणु
	काष्ठा init_array_raw_hdr			raw;
	काष्ठा init_array_standard_hdr			standard;
	काष्ठा init_array_zipped_hdr			zipped;
	काष्ठा init_array_pattern_hdr			pattern;
पूर्ण;

/* init array types */
क्रमागत init_array_types अणु
	INIT_ARR_STANDARD,
	INIT_ARR_ZIPPED,
	INIT_ARR_PATTERN,
	MAX_INIT_ARRAY_TYPES
पूर्ण;

/* init operation: callback */
काष्ठा init_callback_op अणु
	__le32						op_data;
#घोषणा INIT_CALLBACK_OP_OP_MASK			0xF
#घोषणा INIT_CALLBACK_OP_OP_SHIFT			0
#घोषणा INIT_CALLBACK_OP_RESERVED_MASK			0xFFFFFFF
#घोषणा INIT_CALLBACK_OP_RESERVED_SHIFT			4
	__le16						callback_id;
	__le16						block_id;
पूर्ण;

/* init operation: delay */
काष्ठा init_delay_op अणु
	__le32						op_data;
#घोषणा INIT_DELAY_OP_OP_MASK				0xF
#घोषणा INIT_DELAY_OP_OP_SHIFT				0
#घोषणा INIT_DELAY_OP_RESERVED_MASK			0xFFFFFFF
#घोषणा INIT_DELAY_OP_RESERVED_SHIFT			4
	__le32						delay;
पूर्ण;

/* init operation: अगर_mode */
काष्ठा init_अगर_mode_op अणु
	__le32						op_data;
#घोषणा INIT_IF_MODE_OP_OP_MASK				0xF
#घोषणा INIT_IF_MODE_OP_OP_SHIFT			0
#घोषणा INIT_IF_MODE_OP_RESERVED1_MASK			0xFFF
#घोषणा INIT_IF_MODE_OP_RESERVED1_SHIFT			4
#घोषणा INIT_IF_MODE_OP_CMD_OFFSET_MASK			0xFFFF
#घोषणा INIT_IF_MODE_OP_CMD_OFFSET_SHIFT		16
	__le16						reserved2;
	__le16						modes_buf_offset;
पूर्ण;

/* init operation: अगर_phase */
काष्ठा init_अगर_phase_op अणु
	__le32						op_data;
#घोषणा INIT_IF_PHASE_OP_OP_MASK			0xF
#घोषणा INIT_IF_PHASE_OP_OP_SHIFT			0
#घोषणा INIT_IF_PHASE_OP_RESERVED1_MASK			0xFFF
#घोषणा INIT_IF_PHASE_OP_RESERVED1_SHIFT		4
#घोषणा INIT_IF_PHASE_OP_CMD_OFFSET_MASK		0xFFFF
#घोषणा INIT_IF_PHASE_OP_CMD_OFFSET_SHIFT		16
	__le32						phase_data;
#घोषणा INIT_IF_PHASE_OP_PHASE_MASK			0xFF
#घोषणा INIT_IF_PHASE_OP_PHASE_SHIFT			0
#घोषणा INIT_IF_PHASE_OP_RESERVED2_MASK			0xFF
#घोषणा INIT_IF_PHASE_OP_RESERVED2_SHIFT		8
#घोषणा INIT_IF_PHASE_OP_PHASE_ID_MASK			0xFFFF
#घोषणा INIT_IF_PHASE_OP_PHASE_ID_SHIFT			16
पूर्ण;

/* init mode चालकs */
क्रमागत init_mode_ops अणु
	INIT_MODE_OP_NOT,
	INIT_MODE_OP_OR,
	INIT_MODE_OP_AND,
	MAX_INIT_MODE_OPS
पूर्ण;

/* init operation: raw */
काष्ठा init_raw_op अणु
	__le32						op_data;
#घोषणा INIT_RAW_OP_OP_MASK				0xF
#घोषणा INIT_RAW_OP_OP_SHIFT				0
#घोषणा INIT_RAW_OP_PARAM1_MASK				0xFFFFFFF
#घोषणा INIT_RAW_OP_PARAM1_SHIFT			4
	__le32						param2;
पूर्ण;

/* init array params */
काष्ठा init_op_array_params अणु
	__le16						size;
	__le16						offset;
पूर्ण;

/* Write init operation arguments */
जोड़ init_ग_लिखो_args अणु
	__le32						अंतरभूत_val;
	__le32						zeros_count;
	__le32						array_offset;
	काष्ठा init_op_array_params			runसमय;
पूर्ण;

/* init operation: ग_लिखो */
काष्ठा init_ग_लिखो_op अणु
	__le32						data;
#घोषणा INIT_WRITE_OP_OP_MASK				0xF
#घोषणा INIT_WRITE_OP_OP_SHIFT				0
#घोषणा INIT_WRITE_OP_SOURCE_MASK			0x7
#घोषणा INIT_WRITE_OP_SOURCE_SHIFT			4
#घोषणा INIT_WRITE_OP_RESERVED_MASK			0x1
#घोषणा INIT_WRITE_OP_RESERVED_SHIFT			7
#घोषणा INIT_WRITE_OP_WIDE_BUS_MASK			0x1
#घोषणा INIT_WRITE_OP_WIDE_BUS_SHIFT			8
#घोषणा INIT_WRITE_OP_ADDRESS_MASK			0x7FFFFF
#घोषणा INIT_WRITE_OP_ADDRESS_SHIFT			9
	जोड़ init_ग_लिखो_args				args;
पूर्ण;

/* init operation: पढ़ो */
काष्ठा init_पढ़ो_op अणु
	__le32						op_data;
#घोषणा INIT_READ_OP_OP_MASK				0xF
#घोषणा INIT_READ_OP_OP_SHIFT				0
#घोषणा INIT_READ_OP_POLL_TYPE_MASK			0xF
#घोषणा INIT_READ_OP_POLL_TYPE_SHIFT			4
#घोषणा INIT_READ_OP_RESERVED_MASK			0x1
#घोषणा INIT_READ_OP_RESERVED_SHIFT			8
#घोषणा INIT_READ_OP_ADDRESS_MASK			0x7FFFFF
#घोषणा INIT_READ_OP_ADDRESS_SHIFT			9
	__le32						expected_val;
पूर्ण;

/* Init operations जोड़ */
जोड़ init_op अणु
	काष्ठा init_raw_op				raw;
	काष्ठा init_ग_लिखो_op				ग_लिखो;
	काष्ठा init_पढ़ो_op				पढ़ो;
	काष्ठा init_अगर_mode_op				अगर_mode;
	काष्ठा init_अगर_phase_op				अगर_phase;
	काष्ठा init_callback_op				callback;
	काष्ठा init_delay_op				delay;
पूर्ण;

/* Init command operation types */
क्रमागत init_op_types अणु
	INIT_OP_READ,
	INIT_OP_WRITE,
	INIT_OP_IF_MODE,
	INIT_OP_IF_PHASE,
	INIT_OP_DELAY,
	INIT_OP_CALLBACK,
	MAX_INIT_OP_TYPES
पूर्ण;

/* init polling types */
क्रमागत init_poll_types अणु
	INIT_POLL_NONE,
	INIT_POLL_EQ,
	INIT_POLL_OR,
	INIT_POLL_AND,
	MAX_INIT_POLL_TYPES
पूर्ण;

/* init source types */
क्रमागत init_source_types अणु
	INIT_SRC_INLINE,
	INIT_SRC_ZEROS,
	INIT_SRC_ARRAY,
	INIT_SRC_RUNTIME,
	MAX_INIT_SOURCE_TYPES
पूर्ण;

/* Internal RAM Offsets macro data */
काष्ठा iro अणु
	u32 base;
	u16 m1;
	u16 m2;
	u16 m3;
	u16 size;
पूर्ण;

/***************************** Public Functions *******************************/

/**
 * @brief qed_dbg_set_bin_ptr - Sets a poपूर्णांकer to the binary data with debug
 *	arrays.
 *
 * @param p_hwfn -	    HW device data
 * @param bin_ptr - a poपूर्णांकer to the binary data with debug arrays.
 */
क्रमागत dbg_status qed_dbg_set_bin_ptr(काष्ठा qed_hwfn *p_hwfn,
				    स्थिर u8 * स्थिर bin_ptr);

/**
 * @brief qed_पढ़ो_regs - Reads रेजिस्टरs पूर्णांकo a buffer (using GRC).
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf - Destination buffer.
 * @param addr - Source GRC address in dwords.
 * @param len - Number of रेजिस्टरs to पढ़ो.
 */
व्योम qed_पढ़ो_regs(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt, u32 *buf, u32 addr, u32 len);

/**
 * @brief qed_पढ़ो_fw_info - Reads FW info from the chip.
 *
 * The FW info contains FW-related inक्रमmation, such as the FW version,
 * FW image (मुख्य/L2B/kuku), FW बारtamp, etc.
 * The FW info is पढ़ो from the पूर्णांकernal RAM of the first Storm that is not in
 * reset.
 *
 * @param p_hwfn -	    HW device data
 * @param p_ptt -	    Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param fw_info -	Out: a poपूर्णांकer to ग_लिखो the FW info पूर्णांकo.
 *
 * @वापस true अगर the FW info was पढ़ो successfully from one of the Storms,
 * or false अगर all Storms are in reset.
 */
bool qed_पढ़ो_fw_info(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, काष्ठा fw_info *fw_info);
/**
 * @brief qed_dbg_grc_config - Sets the value of a GRC parameter.
 *
 * @param p_hwfn -	HW device data
 * @param grc_param -	GRC parameter
 * @param val -		Value to set.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- grc_param is invalid
 *	- val is outside the allowed boundaries
 */
क्रमागत dbg_status qed_dbg_grc_config(काष्ठा qed_hwfn *p_hwfn,
				   क्रमागत dbg_grc_params grc_param, u32 val);

/**
 * @brief qed_dbg_grc_set_params_शेष - Reverts all GRC parameters to their
 *	शेष value.
 *
 * @param p_hwfn		- HW device data
 */
व्योम qed_dbg_grc_set_params_शेष(काष्ठा qed_hwfn *p_hwfn);
/**
 * @brief qed_dbg_grc_get_dump_buf_size - Returns the required buffer size क्रम
 *	GRC Dump.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम the GRC Dump
 *	data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_grc_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ptt *p_ptt,
					      u32 *buf_size);

/**
 * @brief qed_dbg_grc_dump - Dumps GRC data पूर्णांकo the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the collected GRC data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied dump buffer is too small
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_grc_dump(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *dump_buf,
				 u32 buf_size_in_dwords,
				 u32 *num_dumped_dwords);

/**
 * @brief qed_dbg_idle_chk_get_dump_buf_size - Returns the required buffer size
 *	क्रम idle check results.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम the idle check
 *	data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_idle_chk_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *buf_size);

/**
 * @brief qed_dbg_idle_chk_dump - Perक्रमms idle check and ग_लिखोs the results
 *	पूर्णांकo the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the idle check data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied buffer is too small
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_idle_chk_dump(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf,
				      u32 buf_size_in_dwords,
				      u32 *num_dumped_dwords);

/**
 * @brief qed_dbg_mcp_trace_get_dump_buf_size - Returns the required buffer size
 *	क्रम mcp trace results.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम mcp trace data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the trace data in MCP scratchpad contain an invalid signature
 *	- the bundle ID in NVRAM is invalid
 *	- the trace meta data cannot be found (in NVRAM or image file)
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_mcp_trace_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						    काष्ठा qed_ptt *p_ptt,
						    u32 *buf_size);

/**
 * @brief qed_dbg_mcp_trace_dump - Perक्रमms mcp trace and ग_लिखोs the results
 *	पूर्णांकo the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the mcp trace data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied buffer is too small
 *	- the trace data in MCP scratchpad contain an invalid signature
 *	- the bundle ID in NVRAM is invalid
 *	- the trace meta data cannot be found (in NVRAM or image file)
 *	- the trace meta data cannot be पढ़ो (from NVRAM or image file)
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_mcp_trace_dump(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       u32 *dump_buf,
				       u32 buf_size_in_dwords,
				       u32 *num_dumped_dwords);

/**
 * @brief qed_dbg_reg_fअगरo_get_dump_buf_size - Returns the required buffer size
 *	क्रम grc trace fअगरo results.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम reg fअगरo data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_reg_fअगरo_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *buf_size);

/**
 * @brief qed_dbg_reg_fअगरo_dump - Reads the reg fअगरo and ग_लिखोs the results पूर्णांकo
 *	the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the reg fअगरo data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied buffer is too small
 *	- DMAE transaction failed
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_reg_fअगरo_dump(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf,
				      u32 buf_size_in_dwords,
				      u32 *num_dumped_dwords);

/**
 * @brief qed_dbg_igu_fअगरo_get_dump_buf_size - Returns the required buffer size
 *	क्रम the IGU fअगरo results.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम the IGU fअगरo
 *	data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_igu_fअगरo_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *buf_size);

/**
 * @brief qed_dbg_igu_fअगरo_dump - Reads the IGU fअगरo and ग_लिखोs the results पूर्णांकo
 *	the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the IGU fअगरo data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied buffer is too small
 *	- DMAE transaction failed
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_igu_fअगरo_dump(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf,
				      u32 buf_size_in_dwords,
				      u32 *num_dumped_dwords);

/**
 * @brief qed_dbg_protection_override_get_dump_buf_size - Returns the required
 *	buffer size क्रम protection override winकरोw results.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम protection
 *	override data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status
qed_dbg_protection_override_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ptt *p_ptt,
					      u32 *buf_size);
/**
 * @brief qed_dbg_protection_override_dump - Reads protection override winकरोw
 *	entries and ग_लिखोs the results पूर्णांकo the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the protection override data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied buffer is too small
 *	- DMAE transaction failed
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_protection_override_dump(काष्ठा qed_hwfn *p_hwfn,
						 काष्ठा qed_ptt *p_ptt,
						 u32 *dump_buf,
						 u32 buf_size_in_dwords,
						 u32 *num_dumped_dwords);
/**
 * @brief qed_dbg_fw_निश्चितs_get_dump_buf_size - Returns the required buffer
 *	size क्रम FW Asserts results.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param buf_size - OUT: required buffer size (in dwords) क्रम FW Asserts data.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_fw_निश्चितs_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						     काष्ठा qed_ptt *p_ptt,
						     u32 *buf_size);
/**
 * @brief qed_dbg_fw_निश्चितs_dump - Reads the FW Asserts and ग_लिखोs the results
 *	पूर्णांकo the specअगरied buffer.
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dump_buf - Poपूर्णांकer to ग_लिखो the FW Asserts data पूर्णांकo.
 * @param buf_size_in_dwords - Size of the specअगरied buffer in dwords.
 * @param num_dumped_dwords - OUT: number of dumped dwords.
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 *	- the specअगरied buffer is too small
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_fw_निश्चितs_dump(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					u32 *dump_buf,
					u32 buf_size_in_dwords,
					u32 *num_dumped_dwords);

/**
 * @brief qed_dbg_पढ़ो_attn - Reads the attention रेजिस्टरs of the specअगरied
 * block and type, and ग_लिखोs the results पूर्णांकo the specअगरied buffer.
 *
 * @param p_hwfn -	 HW device data
 * @param p_ptt -	 Ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param block -	 Block ID.
 * @param attn_type -	 Attention type.
 * @param clear_status - Indicates अगर the attention status should be cleared.
 * @param results -	 OUT: Poपूर्णांकer to ग_लिखो the पढ़ो results पूर्णांकo
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_पढ़ो_attn(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  क्रमागत block_id block,
				  क्रमागत dbg_attn_type attn_type,
				  bool clear_status,
				  काष्ठा dbg_attn_block_result *results);

/**
 * @brief qed_dbg_prपूर्णांक_attn - Prपूर्णांकs attention रेजिस्टरs values in the
 *	specअगरied results काष्ठा.
 *
 * @param p_hwfn
 * @param results - Poपूर्णांकer to the attention पढ़ो results
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_prपूर्णांक_attn(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा dbg_attn_block_result *results);

/******************************* Data Types **********************************/

काष्ठा mcp_trace_क्रमmat अणु
	u32 data;
#घोषणा MCP_TRACE_FORMAT_MODULE_MASK	0x0000ffff
#घोषणा MCP_TRACE_FORMAT_MODULE_OFFSET	0
#घोषणा MCP_TRACE_FORMAT_LEVEL_MASK	0x00030000
#घोषणा MCP_TRACE_FORMAT_LEVEL_OFFSET	16
#घोषणा MCP_TRACE_FORMAT_P1_SIZE_MASK	0x000c0000
#घोषणा MCP_TRACE_FORMAT_P1_SIZE_OFFSET 18
#घोषणा MCP_TRACE_FORMAT_P2_SIZE_MASK	0x00300000
#घोषणा MCP_TRACE_FORMAT_P2_SIZE_OFFSET 20
#घोषणा MCP_TRACE_FORMAT_P3_SIZE_MASK	0x00c00000
#घोषणा MCP_TRACE_FORMAT_P3_SIZE_OFFSET 22
#घोषणा MCP_TRACE_FORMAT_LEN_MASK	0xff000000
#घोषणा MCP_TRACE_FORMAT_LEN_OFFSET	24

	अक्षर *क्रमmat_str;
पूर्ण;

/* MCP Trace Meta data काष्ठाure */
काष्ठा mcp_trace_meta अणु
	u32 modules_num;
	अक्षर **modules;
	u32 क्रमmats_num;
	काष्ठा mcp_trace_क्रमmat *क्रमmats;
	bool is_allocated;
पूर्ण;

/* Debug Tools user data */
काष्ठा dbg_tools_user_data अणु
	काष्ठा mcp_trace_meta mcp_trace_meta;
	स्थिर u32 *mcp_trace_user_meta_buf;
पूर्ण;

/******************************** Constants **********************************/

#घोषणा MAX_NAME_LEN	16

/***************************** Public Functions *******************************/

/**
 * @brief qed_dbg_user_set_bin_ptr - Sets a poपूर्णांकer to the binary data with
 *	debug arrays.
 *
 * @param p_hwfn - HW device data
 * @param bin_ptr - a poपूर्णांकer to the binary data with debug arrays.
 */
क्रमागत dbg_status qed_dbg_user_set_bin_ptr(काष्ठा qed_hwfn *p_hwfn,
					 स्थिर u8 * स्थिर bin_ptr);

/**
 * @brief qed_dbg_alloc_user_data - Allocates user debug data.
 *
 * @param p_hwfn -		 HW device data
 * @param user_data_ptr - OUT: a poपूर्णांकer to the allocated memory.
 */
क्रमागत dbg_status qed_dbg_alloc_user_data(काष्ठा qed_hwfn *p_hwfn,
					व्योम **user_data_ptr);

/**
 * @brief qed_dbg_get_status_str - Returns a string क्रम the specअगरied status.
 *
 * @param status - a debug status code.
 *
 * @वापस a string क्रम the specअगरied status
 */
स्थिर अक्षर *qed_dbg_get_status_str(क्रमागत dbg_status status);

/**
 * @brief qed_get_idle_chk_results_buf_size - Returns the required buffer size
 *	क्रम idle check results (in bytes).
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - idle check dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf_size - OUT: required buffer size (in bytes) क्रम the parsed
 *	results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_get_idle_chk_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32  num_dumped_dwords,
						  u32 *results_buf_size);
/**
 * @brief qed_prपूर्णांक_idle_chk_results - Prपूर्णांकs idle check results
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - idle check dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf - buffer क्रम prपूर्णांकing the idle check results.
 * @param num_errors - OUT: number of errors found in idle check.
 * @param num_warnings - OUT: number of warnings found in idle check.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_idle_chk_results(काष्ठा qed_hwfn *p_hwfn,
					   u32 *dump_buf,
					   u32 num_dumped_dwords,
					   अक्षर *results_buf,
					   u32 *num_errors,
					   u32 *num_warnings);

/**
 * @brief qed_dbg_mcp_trace_set_meta_data - Sets the MCP Trace meta data.
 *
 * Needed in हाल the MCP Trace dump करोesn't contain the meta data (e.g. due to
 * no NVRAM access).
 *
 * @param data - poपूर्णांकer to MCP Trace meta data
 * @param size - size of MCP Trace meta data in dwords
 */
व्योम qed_dbg_mcp_trace_set_meta_data(काष्ठा qed_hwfn *p_hwfn,
				     स्थिर u32 *meta_buf);

/**
 * @brief qed_get_mcp_trace_results_buf_size - Returns the required buffer size
 *	क्रम MCP Trace results (in bytes).
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - MCP Trace dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf_size - OUT: required buffer size (in bytes) क्रम the parsed
 *	results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_get_mcp_trace_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   u32 *dump_buf,
						   u32 num_dumped_dwords,
						   u32 *results_buf_size);

/**
 * @brief qed_prपूर्णांक_mcp_trace_results - Prपूर्णांकs MCP Trace results
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - mcp trace dump buffer, starting from the header.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf - buffer क्रम prपूर्णांकing the mcp trace results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_mcp_trace_results(काष्ठा qed_hwfn *p_hwfn,
					    u32 *dump_buf,
					    u32 num_dumped_dwords,
					    अक्षर *results_buf);

/**
 * @brief qed_prपूर्णांक_mcp_trace_results_cont - Prपूर्णांकs MCP Trace results, and
 * keeps the MCP trace meta data allocated, to support continuous MCP Trace
 * parsing. After the continuous parsing ends, mcp_trace_मुक्त_meta_data should
 * be called to मुक्त the meta data.
 *
 * @param p_hwfn -	      HW device data
 * @param dump_buf -	      mcp trace dump buffer, starting from the header.
 * @param results_buf -	      buffer क्रम prपूर्णांकing the mcp trace results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_mcp_trace_results_cont(काष्ठा qed_hwfn *p_hwfn,
						 u32 *dump_buf,
						 अक्षर *results_buf);

/**
 * @brief prपूर्णांक_mcp_trace_line - Prपूर्णांकs MCP Trace results क्रम a single line
 *
 * @param p_hwfn -	      HW device data
 * @param dump_buf -	      mcp trace dump buffer, starting from the header.
 * @param num_dumped_bytes -  number of bytes that were dumped.
 * @param results_buf -	      buffer क्रम prपूर्णांकing the mcp trace results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_mcp_trace_line(काष्ठा qed_hwfn *p_hwfn,
					 u8 *dump_buf,
					 u32 num_dumped_bytes,
					 अक्षर *results_buf);

/**
 * @brief mcp_trace_मुक्त_meta_data - Frees the MCP Trace meta data.
 * Should be called after continuous MCP Trace parsing.
 *
 * @param p_hwfn - HW device data
 */
व्योम qed_mcp_trace_मुक्त_meta_data(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_get_reg_fअगरo_results_buf_size - Returns the required buffer size
 *	क्रम reg_fअगरo results (in bytes).
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - reg fअगरo dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf_size - OUT: required buffer size (in bytes) क्रम the parsed
 *	results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_get_reg_fअगरo_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32 num_dumped_dwords,
						  u32 *results_buf_size);

/**
 * @brief qed_prपूर्णांक_reg_fअगरo_results - Prपूर्णांकs reg fअगरo results
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - reg fअगरo dump buffer, starting from the header.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf - buffer क्रम prपूर्णांकing the reg fअगरo results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_reg_fअगरo_results(काष्ठा qed_hwfn *p_hwfn,
					   u32 *dump_buf,
					   u32 num_dumped_dwords,
					   अक्षर *results_buf);

/**
 * @brief qed_get_igu_fअगरo_results_buf_size - Returns the required buffer size
 *	क्रम igu_fअगरo results (in bytes).
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - IGU fअगरo dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf_size - OUT: required buffer size (in bytes) क्रम the parsed
 *	results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_get_igu_fअगरo_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32 num_dumped_dwords,
						  u32 *results_buf_size);

/**
 * @brief qed_prपूर्णांक_igu_fअगरo_results - Prपूर्णांकs IGU fअगरo results
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - IGU fअगरo dump buffer, starting from the header.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf - buffer क्रम prपूर्णांकing the IGU fअगरo results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_igu_fअगरo_results(काष्ठा qed_hwfn *p_hwfn,
					   u32 *dump_buf,
					   u32 num_dumped_dwords,
					   अक्षर *results_buf);

/**
 * @brief qed_get_protection_override_results_buf_size - Returns the required
 *	buffer size क्रम protection override results (in bytes).
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - protection override dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf_size - OUT: required buffer size (in bytes) क्रम the parsed
 *	results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status
qed_get_protection_override_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
					     u32 *dump_buf,
					     u32 num_dumped_dwords,
					     u32 *results_buf_size);

/**
 * @brief qed_prपूर्णांक_protection_override_results - Prपूर्णांकs protection override
 *	results.
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - protection override dump buffer, starting from the header.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf - buffer क्रम prपूर्णांकing the reg fअगरo results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_protection_override_results(काष्ठा qed_hwfn *p_hwfn,
						      u32 *dump_buf,
						      u32 num_dumped_dwords,
						      अक्षर *results_buf);

/**
 * @brief qed_get_fw_निश्चितs_results_buf_size - Returns the required buffer size
 *	क्रम FW Asserts results (in bytes).
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - FW Asserts dump buffer.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf_size - OUT: required buffer size (in bytes) क्रम the parsed
 *	results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_get_fw_निश्चितs_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						    u32 *dump_buf,
						    u32 num_dumped_dwords,
						    u32 *results_buf_size);

/**
 * @brief qed_prपूर्णांक_fw_निश्चितs_results - Prपूर्णांकs FW Asserts results
 *
 * @param p_hwfn - HW device data
 * @param dump_buf - FW Asserts dump buffer, starting from the header.
 * @param num_dumped_dwords - number of dwords that were dumped.
 * @param results_buf - buffer क्रम prपूर्णांकing the FW Asserts results.
 *
 * @वापस error अगर the parsing fails, ok otherwise.
 */
क्रमागत dbg_status qed_prपूर्णांक_fw_निश्चितs_results(काष्ठा qed_hwfn *p_hwfn,
					     u32 *dump_buf,
					     u32 num_dumped_dwords,
					     अक्षर *results_buf);

/**
 * @brief qed_dbg_parse_attn - Parses and prपूर्णांकs attention रेजिस्टरs values in
 * the specअगरied results काष्ठा.
 *
 * @param p_hwfn -  HW device data
 * @param results - Poपूर्णांकer to the attention पढ़ो results
 *
 * @वापस error अगर one of the following holds:
 *	- the version wasn't set
 * Otherwise, वापसs ok.
 */
क्रमागत dbg_status qed_dbg_parse_attn(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा dbg_attn_block_result *results);

/* Win 2 */
#घोषणा GTT_BAR0_MAP_REG_IGU_CMD	0x00f000UL

/* Win 3 */
#घोषणा GTT_BAR0_MAP_REG_TSDM_RAM	0x010000UL

/* Win 4 */
#घोषणा GTT_BAR0_MAP_REG_MSDM_RAM	0x011000UL

/* Win 5 */
#घोषणा GTT_BAR0_MAP_REG_MSDM_RAM_1024	0x012000UL

/* Win 6 */
#घोषणा GTT_BAR0_MAP_REG_MSDM_RAM_2048	0x013000UL

/* Win 7 */
#घोषणा GTT_BAR0_MAP_REG_USDM_RAM	0x014000UL

/* Win 8 */
#घोषणा GTT_BAR0_MAP_REG_USDM_RAM_1024	0x015000UL

/* Win 9 */
#घोषणा GTT_BAR0_MAP_REG_USDM_RAM_2048	0x016000UL

/* Win 10 */
#घोषणा GTT_BAR0_MAP_REG_XSDM_RAM	0x017000UL

/* Win 11 */
#घोषणा GTT_BAR0_MAP_REG_XSDM_RAM_1024	0x018000UL

/* Win 12 */
#घोषणा GTT_BAR0_MAP_REG_YSDM_RAM	0x019000UL

/* Win 13 */
#घोषणा GTT_BAR0_MAP_REG_PSDM_RAM	0x01a000UL

/**
 * @brief qed_qm_pf_mem_size - prepare QM ILT sizes
 *
 * Returns the required host memory size in 4KB units.
 * Must be called beक्रमe all QM init HSI functions.
 *
 * @param num_pf_cids - number of connections used by this PF
 * @param num_vf_cids - number of connections used by VFs of this PF
 * @param num_tids - number of tasks used by this PF
 * @param num_pf_pqs - number of PQs used by this PF
 * @param num_vf_pqs - number of PQs used by VFs of this PF
 *
 * @वापस The required host memory size in 4KB units.
 */
u32 qed_qm_pf_mem_size(u32 num_pf_cids,
		       u32 num_vf_cids,
		       u32 num_tids, u16 num_pf_pqs, u16 num_vf_pqs);

काष्ठा qed_qm_common_rt_init_params अणु
	u8 max_ports_per_engine;
	u8 max_phys_tcs_per_port;
	bool pf_rl_en;
	bool pf_wfq_en;
	bool global_rl_en;
	bool vport_wfq_en;
	काष्ठा init_qm_port_params *port_params;
पूर्ण;

पूर्णांक qed_qm_common_rt_init(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_qm_common_rt_init_params *p_params);

काष्ठा qed_qm_pf_rt_init_params अणु
	u8 port_id;
	u8 pf_id;
	u8 max_phys_tcs_per_port;
	bool is_pf_loading;
	u32 num_pf_cids;
	u32 num_vf_cids;
	u32 num_tids;
	u16 start_pq;
	u16 num_pf_pqs;
	u16 num_vf_pqs;
	u16 start_vport;
	u16 num_vports;
	u16 pf_wfq;
	u32 pf_rl;
	काष्ठा init_qm_pq_params *pq_params;
	काष्ठा init_qm_vport_params *vport_params;
पूर्ण;

पूर्णांक qed_qm_pf_rt_init(काष्ठा qed_hwfn *p_hwfn,
	काष्ठा qed_ptt *p_ptt,
	काष्ठा qed_qm_pf_rt_init_params *p_params);

/**
 * @brief qed_init_pf_wfq - Initializes the WFQ weight of the specअगरied PF
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs
 * @param pf_id - PF ID
 * @param pf_wfq - WFQ weight. Must be non-zero.
 *
 * @वापस 0 on success, -1 on error.
 */
पूर्णांक qed_init_pf_wfq(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, u8 pf_id, u16 pf_wfq);

/**
 * @brief qed_init_pf_rl - Initializes the rate limit of the specअगरied PF
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs
 * @param pf_id - PF ID
 * @param pf_rl - rate limit in Mb/sec units
 *
 * @वापस 0 on success, -1 on error.
 */
पूर्णांक qed_init_pf_rl(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt, u8 pf_id, u32 pf_rl);

/**
 * @brief qed_init_vport_wfq Initializes the WFQ weight of the specअगरied VPORT
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs
 * @param first_tx_pq_id- An array containing the first Tx PQ ID associated
 *	  with the VPORT क्रम each TC. This array is filled by
 *	  qed_qm_pf_rt_init
 * @param vport_wfq - WFQ weight. Must be non-zero.
 *
 * @वापस 0 on success, -1 on error.
 */
पूर्णांक qed_init_vport_wfq(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       u16 first_tx_pq_id[NUM_OF_TCS], u16 wfq);

/**
 * @brief qed_init_global_rl - Initializes the rate limit of the specअगरied
 * rate limiter
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs
 * @param rl_id - RL ID
 * @param rate_limit - rate limit in Mb/sec units
 *
 * @वापस 0 on success, -1 on error.
 */
पूर्णांक qed_init_global_rl(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       u16 rl_id, u32 rate_limit);

/**
 * @brief qed_send_qm_stop_cmd  Sends a stop command to the QM
 *
 * @param p_hwfn
 * @param p_ptt
 * @param is_release_cmd - true क्रम release, false क्रम stop.
 * @param is_tx_pq - true क्रम Tx PQs, false क्रम Other PQs.
 * @param start_pq - first PQ ID to stop
 * @param num_pqs - Number of PQs to stop, starting from start_pq.
 *
 * @वापस bool, true अगर successful, false अगर समयout occurred जबतक रुकोing क्रम
 *	QM command करोne.
 */
bool qed_send_qm_stop_cmd(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  bool is_release_cmd,
			  bool is_tx_pq, u16 start_pq, u16 num_pqs);

/**
 * @brief qed_set_vxlan_dest_port - initializes vxlan tunnel destination udp port
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dest_port - vxlan destination udp port.
 */
व्योम qed_set_vxlan_dest_port(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u16 dest_port);

/**
 * @brief qed_set_vxlan_enable - enable or disable VXLAN tunnel in HW
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param vxlan_enable - vxlan enable flag.
 */
व्योम qed_set_vxlan_enable(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, bool vxlan_enable);

/**
 * @brief qed_set_gre_enable - enable or disable GRE tunnel in HW
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param eth_gre_enable - eth GRE enable enable flag.
 * @param ip_gre_enable - IP GRE enable enable flag.
 */
व्योम qed_set_gre_enable(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt,
			bool eth_gre_enable, bool ip_gre_enable);

/**
 * @brief qed_set_geneve_dest_port - initializes geneve tunnel destination udp port
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param dest_port - geneve destination udp port.
 */
व्योम qed_set_geneve_dest_port(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt, u16 dest_port);

/**
 * @brief qed_set_gre_enable - enable or disable GRE tunnel in HW
 *
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param eth_geneve_enable - eth GENEVE enable enable flag.
 * @param ip_geneve_enable - IP GENEVE enable enable flag.
 */
व्योम qed_set_geneve_enable(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt,
			   bool eth_geneve_enable, bool ip_geneve_enable);

व्योम qed_set_vxlan_no_l2_enable(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt, bool enable);

/**
 * @brief qed_gft_disable - Disable GFT
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param pf_id - pf on which to disable GFT.
 */
व्योम qed_gft_disable(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt, u16 pf_id);

/**
 * @brief qed_gft_config - Enable and configure HW क्रम GFT
 *
 * @param p_hwfn - HW device data
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param pf_id - pf on which to enable GFT.
 * @param tcp - set profile tcp packets.
 * @param udp - set profile udp  packet.
 * @param ipv4 - set profile ipv4 packet.
 * @param ipv6 - set profile ipv6 packet.
 * @param profile_type - define packet same fields. Use क्रमागत gft_profile_type.
 */
व्योम qed_gft_config(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    u16 pf_id,
		    bool tcp,
		    bool udp,
		    bool ipv4, bool ipv6, क्रमागत gft_profile_type profile_type);

/**
 * @brief qed_enable_context_validation - Enable and configure context
 *	validation.
 *
 * @param p_hwfn
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 */
व्योम qed_enable_context_validation(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_calc_session_ctx_validation - Calcualte validation byte क्रम
 *	session context.
 *
 * @param p_ctx_mem - poपूर्णांकer to context memory.
 * @param ctx_size - context size.
 * @param ctx_type - context type.
 * @param cid - context cid.
 */
व्योम qed_calc_session_ctx_validation(व्योम *p_ctx_mem,
				     u16 ctx_size, u8 ctx_type, u32 cid);

/**
 * @brief qed_calc_task_ctx_validation - Calcualte validation byte क्रम task
 *	context.
 *
 * @param p_ctx_mem - poपूर्णांकer to context memory.
 * @param ctx_size - context size.
 * @param ctx_type - context type.
 * @param tid - context tid.
 */
व्योम qed_calc_task_ctx_validation(व्योम *p_ctx_mem,
				  u16 ctx_size, u8 ctx_type, u32 tid);

/**
 * @brief qed_स_रखो_session_ctx - Memset session context to 0 जबतक
 *	preserving validation bytes.
 *
 * @param p_hwfn -
 * @param p_ctx_mem - poपूर्णांकer to context memory.
 * @param ctx_size - size to initialzie.
 * @param ctx_type - context type.
 */
व्योम qed_स_रखो_session_ctx(व्योम *p_ctx_mem, u32 ctx_size, u8 ctx_type);

/**
 * @brief qed_स_रखो_task_ctx - Memset task context to 0 जबतक preserving
 *	validation bytes.
 *
 * @param p_ctx_mem - poपूर्णांकer to context memory.
 * @param ctx_size - size to initialzie.
 * @param ctx_type - context type.
 */
व्योम qed_स_रखो_task_ctx(व्योम *p_ctx_mem, u32 ctx_size, u8 ctx_type);

#घोषणा NUM_STORMS 6

/**
 * @brief qed_set_rdma_error_level - Sets the RDMA निश्चित level.
 *                                   If the severity of the error will be
 *                                   above the level, the FW will निश्चित.
 * @param p_hwfn - HW device data
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs
 * @param निश्चित_level - An array of निश्चित levels क्रम each storm.
 *
 */
व्योम qed_set_rdma_error_level(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      u8 निश्चित_level[NUM_STORMS]);
/**
 * @brief qed_fw_overlay_mem_alloc - Allocates and fills the FW overlay memory.
 *
 * @param p_hwfn - HW device data
 * @param fw_overlay_in_buf - the input FW overlay buffer.
 * @param buf_size - the size of the input FW overlay buffer in bytes.
 *		     must be aligned to dwords.
 * @param fw_overlay_out_mem - OUT: a poपूर्णांकer to the allocated overlays memory.
 *
 * @वापस a poपूर्णांकer to the allocated overlays memory,
 * or शून्य in हाल of failures.
 */
काष्ठा phys_mem_desc *
qed_fw_overlay_mem_alloc(काष्ठा qed_hwfn *p_hwfn,
			 स्थिर u32 * स्थिर fw_overlay_in_buf,
			 u32 buf_size_in_bytes);

/**
 * @brief qed_fw_overlay_init_ram - Initializes the FW overlay RAM.
 *
 * @param p_hwfn - HW device data.
 * @param p_ptt - ptt winकरोw used क्रम writing the रेजिस्टरs.
 * @param fw_overlay_mem - the allocated FW overlay memory.
 */
व्योम qed_fw_overlay_init_ram(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt,
			     काष्ठा phys_mem_desc *fw_overlay_mem);

/**
 * @brief qed_fw_overlay_mem_मुक्त - Frees the FW overlay memory.
 *
 * @param p_hwfn - HW device data.
 * @param fw_overlay_mem - the allocated FW overlay memory to मुक्त.
 */
व्योम qed_fw_overlay_mem_मुक्त(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा phys_mem_desc *fw_overlay_mem);

/* Ystorm flow control mode. Use क्रमागत fw_flow_ctrl_mode */
#घोषणा YSTORM_FLOW_CONTROL_MODE_OFFSET			(IRO[0].base)
#घोषणा YSTORM_FLOW_CONTROL_MODE_SIZE			(IRO[0].size)

/* Tstorm port statistics */
#घोषणा TSTORM_PORT_STAT_OFFSET(port_id) \
	(IRO[1].base + ((port_id) * IRO[1].m1))
#घोषणा TSTORM_PORT_STAT_SIZE				(IRO[1].size)

/* Tstorm ll2 port statistics */
#घोषणा TSTORM_LL2_PORT_STAT_OFFSET(port_id) \
	(IRO[2].base + ((port_id) * IRO[2].m1))
#घोषणा TSTORM_LL2_PORT_STAT_SIZE			(IRO[2].size)

/* Ustorm VF-PF Channel पढ़ोy flag */
#घोषणा USTORM_VF_PF_CHANNEL_READY_OFFSET(vf_id) \
	(IRO[3].base + ((vf_id) * IRO[3].m1))
#घोषणा USTORM_VF_PF_CHANNEL_READY_SIZE			(IRO[3].size)

/* Ustorm Final flr cleanup ack */
#घोषणा USTORM_FLR_FINAL_ACK_OFFSET(pf_id) \
	(IRO[4].base + ((pf_id) * IRO[4].m1))
#घोषणा USTORM_FLR_FINAL_ACK_SIZE			(IRO[4].size)

/* Ustorm Event ring consumer */
#घोषणा USTORM_EQE_CONS_OFFSET(pf_id) \
	(IRO[5].base + ((pf_id) * IRO[5].m1))
#घोषणा USTORM_EQE_CONS_SIZE				(IRO[5].size)

/* Ustorm eth queue zone */
#घोषणा USTORM_ETH_QUEUE_ZONE_OFFSET(queue_zone_id) \
	(IRO[6].base + ((queue_zone_id) * IRO[6].m1))
#घोषणा USTORM_ETH_QUEUE_ZONE_SIZE			(IRO[6].size)

/* Ustorm Common Queue ring consumer */
#घोषणा USTORM_COMMON_QUEUE_CONS_OFFSET(queue_zone_id) \
	(IRO[7].base + ((queue_zone_id) * IRO[7].m1))
#घोषणा USTORM_COMMON_QUEUE_CONS_SIZE			(IRO[7].size)

/* Xstorm common PQ info */
#घोषणा XSTORM_PQ_INFO_OFFSET(pq_id) \
	(IRO[8].base + ((pq_id) * IRO[8].m1))
#घोषणा XSTORM_PQ_INFO_SIZE				(IRO[8].size)

/* Xstorm Integration Test Data */
#घोषणा XSTORM_INTEG_TEST_DATA_OFFSET			(IRO[9].base)
#घोषणा XSTORM_INTEG_TEST_DATA_SIZE			(IRO[9].size)

/* Ystorm Integration Test Data */
#घोषणा YSTORM_INTEG_TEST_DATA_OFFSET			(IRO[10].base)
#घोषणा YSTORM_INTEG_TEST_DATA_SIZE			(IRO[10].size)

/* Pstorm Integration Test Data */
#घोषणा PSTORM_INTEG_TEST_DATA_OFFSET			(IRO[11].base)
#घोषणा PSTORM_INTEG_TEST_DATA_SIZE			(IRO[11].size)

/* Tstorm Integration Test Data */
#घोषणा TSTORM_INTEG_TEST_DATA_OFFSET			(IRO[12].base)
#घोषणा TSTORM_INTEG_TEST_DATA_SIZE			(IRO[12].size)

/* Mstorm Integration Test Data */
#घोषणा MSTORM_INTEG_TEST_DATA_OFFSET			(IRO[13].base)
#घोषणा MSTORM_INTEG_TEST_DATA_SIZE			(IRO[13].size)

/* Ustorm Integration Test Data */
#घोषणा USTORM_INTEG_TEST_DATA_OFFSET			(IRO[14].base)
#घोषणा USTORM_INTEG_TEST_DATA_SIZE			(IRO[14].size)

/* Xstorm overlay buffer host address */
#घोषणा XSTORM_OVERLAY_BUF_ADDR_OFFSET			(IRO[15].base)
#घोषणा XSTORM_OVERLAY_BUF_ADDR_SIZE			(IRO[15].size)

/* Ystorm overlay buffer host address */
#घोषणा YSTORM_OVERLAY_BUF_ADDR_OFFSET			(IRO[16].base)
#घोषणा YSTORM_OVERLAY_BUF_ADDR_SIZE			(IRO[16].size)

/* Pstorm overlay buffer host address */
#घोषणा PSTORM_OVERLAY_BUF_ADDR_OFFSET			(IRO[17].base)
#घोषणा PSTORM_OVERLAY_BUF_ADDR_SIZE			(IRO[17].size)

/* Tstorm overlay buffer host address */
#घोषणा TSTORM_OVERLAY_BUF_ADDR_OFFSET			(IRO[18].base)
#घोषणा TSTORM_OVERLAY_BUF_ADDR_SIZE			(IRO[18].size)

/* Mstorm overlay buffer host address */
#घोषणा MSTORM_OVERLAY_BUF_ADDR_OFFSET			(IRO[19].base)
#घोषणा MSTORM_OVERLAY_BUF_ADDR_SIZE			(IRO[19].size)

/* Ustorm overlay buffer host address */
#घोषणा USTORM_OVERLAY_BUF_ADDR_OFFSET			(IRO[20].base)
#घोषणा USTORM_OVERLAY_BUF_ADDR_SIZE			(IRO[20].size)

/* Tstorm producers */
#घोषणा TSTORM_LL2_RX_PRODS_OFFSET(core_rx_queue_id) \
	(IRO[21].base + ((core_rx_queue_id) * IRO[21].m1))
#घोषणा TSTORM_LL2_RX_PRODS_SIZE			(IRO[21].size)

/* Tstorm LightL2 queue statistics */
#घोषणा CORE_LL2_TSTORM_PER_QUEUE_STAT_OFFSET(core_rx_queue_id) \
	(IRO[22].base + ((core_rx_queue_id) * IRO[22].m1))
#घोषणा CORE_LL2_TSTORM_PER_QUEUE_STAT_SIZE		(IRO[22].size)

/* Ustorm LiteL2 queue statistics */
#घोषणा CORE_LL2_USTORM_PER_QUEUE_STAT_OFFSET(core_rx_queue_id) \
	(IRO[23].base + ((core_rx_queue_id) * IRO[23].m1))
#घोषणा CORE_LL2_USTORM_PER_QUEUE_STAT_SIZE		(IRO[23].size)

/* Pstorm LiteL2 queue statistics */
#घोषणा CORE_LL2_PSTORM_PER_QUEUE_STAT_OFFSET(core_tx_stats_id) \
	(IRO[24].base + ((core_tx_stats_id) * IRO[24].m1))
#घोषणा CORE_LL2_PSTORM_PER_QUEUE_STAT_SIZE		(IRO[24].size)

/* Mstorm queue statistics */
#घोषणा MSTORM_QUEUE_STAT_OFFSET(stat_counter_id) \
	(IRO[25].base + ((stat_counter_id) * IRO[25].m1))
#घोषणा MSTORM_QUEUE_STAT_SIZE				(IRO[25].size)

/* TPA agregation समयout in us resolution (on ASIC) */
#घोषणा MSTORM_TPA_TIMEOUT_US_OFFSET			(IRO[26].base)
#घोषणा MSTORM_TPA_TIMEOUT_US_SIZE			(IRO[26].size)

/* Mstorm ETH VF queues producers offset in RAM. Used in शेष VF zone size
 * mode
 */
#घोषणा MSTORM_ETH_VF_PRODS_OFFSET(vf_id, vf_queue_id) \
	(IRO[27].base + ((vf_id) * IRO[27].m1) + ((vf_queue_id) * IRO[27].m2))
#घोषणा MSTORM_ETH_VF_PRODS_SIZE			(IRO[27].size)

/* Mstorm ETH PF queues producers */
#घोषणा MSTORM_ETH_PF_PRODS_OFFSET(queue_id) \
	(IRO[28].base + ((queue_id) * IRO[28].m1))
#घोषणा MSTORM_ETH_PF_PRODS_SIZE			(IRO[28].size)

/* Mstorm pf statistics */
#घोषणा MSTORM_ETH_PF_STAT_OFFSET(pf_id) \
	(IRO[29].base + ((pf_id) * IRO[29].m1))
#घोषणा MSTORM_ETH_PF_STAT_SIZE				(IRO[29].size)

/* Ustorm queue statistics */
#घोषणा USTORM_QUEUE_STAT_OFFSET(stat_counter_id) \
	(IRO[30].base + ((stat_counter_id) * IRO[30].m1))
#घोषणा USTORM_QUEUE_STAT_SIZE				(IRO[30].size)

/* Ustorm pf statistics */
#घोषणा USTORM_ETH_PF_STAT_OFFSET(pf_id) \
	(IRO[31].base + ((pf_id) * IRO[31].m1))
#घोषणा USTORM_ETH_PF_STAT_SIZE				(IRO[31].size)

/* Pstorm queue statistics */
#घोषणा PSTORM_QUEUE_STAT_OFFSET(stat_counter_id)	\
	(IRO[32].base + ((stat_counter_id) * IRO[32].m1))
#घोषणा PSTORM_QUEUE_STAT_SIZE				(IRO[32].size)

/* Pstorm pf statistics */
#घोषणा PSTORM_ETH_PF_STAT_OFFSET(pf_id) \
	(IRO[33].base + ((pf_id) * IRO[33].m1))
#घोषणा PSTORM_ETH_PF_STAT_SIZE				(IRO[33].size)

/* Control frame's EthType configuration क्रम TX control frame security */
#घोषणा PSTORM_CTL_FRAME_ETHTYPE_OFFSET(eth_type_id)	\
	(IRO[34].base + ((eth_type_id) * IRO[34].m1))
#घोषणा PSTORM_CTL_FRAME_ETHTYPE_SIZE			(IRO[34].size)

/* Tstorm last parser message */
#घोषणा TSTORM_ETH_PRS_INPUT_OFFSET			(IRO[35].base)
#घोषणा TSTORM_ETH_PRS_INPUT_SIZE			(IRO[35].size)

/* Tstorm Eth limit Rx rate */
#घोषणा ETH_RX_RATE_LIMIT_OFFSET(pf_id)	\
	(IRO[36].base + ((pf_id) * IRO[36].m1))
#घोषणा ETH_RX_RATE_LIMIT_SIZE				(IRO[36].size)

/* RSS indirection table entry update command per PF offset in TSTORM PF BAR0.
 * Use eth_tstorm_rss_update_data क्रम update
 */
#घोषणा TSTORM_ETH_RSS_UPDATE_OFFSET(pf_id) \
	(IRO[37].base + ((pf_id) * IRO[37].m1))
#घोषणा TSTORM_ETH_RSS_UPDATE_SIZE			(IRO[37].size)

/* Xstorm queue zone */
#घोषणा XSTORM_ETH_QUEUE_ZONE_OFFSET(queue_id) \
	(IRO[38].base + ((queue_id) * IRO[38].m1))
#घोषणा XSTORM_ETH_QUEUE_ZONE_SIZE			(IRO[38].size)

/* Ystorm cqe producer */
#घोषणा YSTORM_TOE_CQ_PROD_OFFSET(rss_id) \
	(IRO[39].base + ((rss_id) * IRO[39].m1))
#घोषणा YSTORM_TOE_CQ_PROD_SIZE				(IRO[39].size)

/* Ustorm cqe producer */
#घोषणा USTORM_TOE_CQ_PROD_OFFSET(rss_id) \
	(IRO[40].base + ((rss_id) * IRO[40].m1))
#घोषणा USTORM_TOE_CQ_PROD_SIZE				(IRO[40].size)

/* Ustorm grq producer */
#घोषणा USTORM_TOE_GRQ_PROD_OFFSET(pf_id) \
	(IRO[41].base + ((pf_id) * IRO[41].m1))
#घोषणा USTORM_TOE_GRQ_PROD_SIZE			(IRO[41].size)

/* Tstorm cmdq-cons of given command queue-id */
#घोषणा TSTORM_SCSI_CMDQ_CONS_OFFSET(cmdq_queue_id) \
	(IRO[42].base + ((cmdq_queue_id) * IRO[42].m1))
#घोषणा TSTORM_SCSI_CMDQ_CONS_SIZE			(IRO[42].size)

/* Tstorm (reflects M-Storm) bdq-बाह्यal-producer of given function ID,
 * BDqueue-id
 */
#घोषणा TSTORM_SCSI_BDQ_EXT_PROD_OFFSET(storage_func_id, bdq_id) \
	(IRO[43].base + ((storage_func_id) * IRO[43].m1) + \
	 ((bdq_id) * IRO[43].m2))
#घोषणा TSTORM_SCSI_BDQ_EXT_PROD_SIZE			(IRO[43].size)

/* Mstorm bdq-बाह्यal-producer of given BDQ resource ID, BDqueue-id */
#घोषणा MSTORM_SCSI_BDQ_EXT_PROD_OFFSET(storage_func_id, bdq_id) \
	(IRO[44].base + ((storage_func_id) * IRO[44].m1) + \
	 ((bdq_id) * IRO[44].m2))
#घोषणा MSTORM_SCSI_BDQ_EXT_PROD_SIZE			(IRO[44].size)

/* Tstorm iSCSI RX stats */
#घोषणा TSTORM_ISCSI_RX_STATS_OFFSET(storage_func_id) \
	(IRO[45].base + ((storage_func_id) * IRO[45].m1))
#घोषणा TSTORM_ISCSI_RX_STATS_SIZE			(IRO[45].size)

/* Mstorm iSCSI RX stats */
#घोषणा MSTORM_ISCSI_RX_STATS_OFFSET(storage_func_id) \
	(IRO[46].base + ((storage_func_id) * IRO[46].m1))
#घोषणा MSTORM_ISCSI_RX_STATS_SIZE			(IRO[46].size)

/* Ustorm iSCSI RX stats */
#घोषणा USTORM_ISCSI_RX_STATS_OFFSET(storage_func_id) \
	(IRO[47].base + ((storage_func_id) * IRO[47].m1))
#घोषणा USTORM_ISCSI_RX_STATS_SIZE			(IRO[47].size)

/* Xstorm iSCSI TX stats */
#घोषणा XSTORM_ISCSI_TX_STATS_OFFSET(storage_func_id) \
	(IRO[48].base + ((storage_func_id) * IRO[48].m1))
#घोषणा XSTORM_ISCSI_TX_STATS_SIZE			(IRO[48].size)

/* Ystorm iSCSI TX stats */
#घोषणा YSTORM_ISCSI_TX_STATS_OFFSET(storage_func_id) \
	(IRO[49].base + ((storage_func_id) * IRO[49].m1))
#घोषणा YSTORM_ISCSI_TX_STATS_SIZE			(IRO[49].size)

/* Pstorm iSCSI TX stats */
#घोषणा PSTORM_ISCSI_TX_STATS_OFFSET(storage_func_id) \
	(IRO[50].base + ((storage_func_id) * IRO[50].m1))
#घोषणा PSTORM_ISCSI_TX_STATS_SIZE			(IRO[50].size)

/* Tstorm FCoE RX stats */
#घोषणा TSTORM_FCOE_RX_STATS_OFFSET(pf_id) \
	(IRO[51].base + ((pf_id) * IRO[51].m1))
#घोषणा TSTORM_FCOE_RX_STATS_SIZE			(IRO[51].size)

/* Pstorm FCoE TX stats */
#घोषणा PSTORM_FCOE_TX_STATS_OFFSET(pf_id) \
	(IRO[52].base + ((pf_id) * IRO[52].m1))
#घोषणा PSTORM_FCOE_TX_STATS_SIZE			(IRO[52].size)

/* Pstorm RDMA queue statistics */
#घोषणा PSTORM_RDMA_QUEUE_STAT_OFFSET(rdma_stat_counter_id) \
	(IRO[53].base + ((rdma_stat_counter_id) * IRO[53].m1))
#घोषणा PSTORM_RDMA_QUEUE_STAT_SIZE			(IRO[53].size)

/* Tstorm RDMA queue statistics */
#घोषणा TSTORM_RDMA_QUEUE_STAT_OFFSET(rdma_stat_counter_id) \
	(IRO[54].base + ((rdma_stat_counter_id) * IRO[54].m1))
#घोषणा TSTORM_RDMA_QUEUE_STAT_SIZE			(IRO[54].size)

/* Xstorm error level क्रम निश्चित */
#घोषणा XSTORM_RDMA_ASSERT_LEVEL_OFFSET(pf_id) \
	(IRO[55].base + ((pf_id) * IRO[55].m1))
#घोषणा XSTORM_RDMA_ASSERT_LEVEL_SIZE			(IRO[55].size)

/* Ystorm error level क्रम निश्चित */
#घोषणा YSTORM_RDMA_ASSERT_LEVEL_OFFSET(pf_id) \
	(IRO[56].base + ((pf_id) * IRO[56].m1))
#घोषणा YSTORM_RDMA_ASSERT_LEVEL_SIZE			(IRO[56].size)

/* Pstorm error level क्रम निश्चित */
#घोषणा PSTORM_RDMA_ASSERT_LEVEL_OFFSET(pf_id) \
	(IRO[57].base + ((pf_id) * IRO[57].m1))
#घोषणा PSTORM_RDMA_ASSERT_LEVEL_SIZE			(IRO[57].size)

/* Tstorm error level क्रम निश्चित */
#घोषणा TSTORM_RDMA_ASSERT_LEVEL_OFFSET(pf_id) \
	(IRO[58].base + ((pf_id) * IRO[58].m1))
#घोषणा TSTORM_RDMA_ASSERT_LEVEL_SIZE			(IRO[58].size)

/* Mstorm error level क्रम निश्चित */
#घोषणा MSTORM_RDMA_ASSERT_LEVEL_OFFSET(pf_id) \
	(IRO[59].base + ((pf_id) * IRO[59].m1))
#घोषणा MSTORM_RDMA_ASSERT_LEVEL_SIZE			(IRO[59].size)

/* Ustorm error level क्रम निश्चित */
#घोषणा USTORM_RDMA_ASSERT_LEVEL_OFFSET(pf_id) \
	(IRO[60].base + ((pf_id) * IRO[60].m1))
#घोषणा USTORM_RDMA_ASSERT_LEVEL_SIZE			(IRO[60].size)

/* Xstorm iWARP rxmit stats */
#घोषणा XSTORM_IWARP_RXMIT_STATS_OFFSET(pf_id) \
	(IRO[61].base + ((pf_id) * IRO[61].m1))
#घोषणा XSTORM_IWARP_RXMIT_STATS_SIZE			(IRO[61].size)

/* Tstorm RoCE Event Statistics */
#घोषणा TSTORM_ROCE_EVENTS_STAT_OFFSET(roce_pf_id)	\
	(IRO[62].base + ((roce_pf_id) * IRO[62].m1))
#घोषणा TSTORM_ROCE_EVENTS_STAT_SIZE			(IRO[62].size)

/* DCQCN Received Statistics */
#घोषणा YSTORM_ROCE_DCQCN_RECEIVED_STATS_OFFSET(roce_pf_id)\
	(IRO[63].base + ((roce_pf_id) * IRO[63].m1))
#घोषणा YSTORM_ROCE_DCQCN_RECEIVED_STATS_SIZE		(IRO[63].size)

/* RoCE Error Statistics */
#घोषणा YSTORM_ROCE_ERROR_STATS_OFFSET(roce_pf_id)	\
	(IRO[64].base + ((roce_pf_id) * IRO[64].m1))
#घोषणा YSTORM_ROCE_ERROR_STATS_SIZE			(IRO[64].size)

/* DCQCN Sent Statistics */
#घोषणा PSTORM_ROCE_DCQCN_SENT_STATS_OFFSET(roce_pf_id)	\
	(IRO[65].base + ((roce_pf_id) * IRO[65].m1))
#घोषणा PSTORM_ROCE_DCQCN_SENT_STATS_SIZE		(IRO[65].size)

/* RoCE CQEs Statistics */
#घोषणा USTORM_ROCE_CQE_STATS_OFFSET(roce_pf_id)	\
	(IRO[66].base + ((roce_pf_id) * IRO[66].m1))
#घोषणा USTORM_ROCE_CQE_STATS_SIZE			(IRO[66].size)

/* Runसमय array offsets */
#घोषणा DORQ_REG_PF_MAX_ICID_0_RT_OFFSET				0
#घोषणा DORQ_REG_PF_MAX_ICID_1_RT_OFFSET				1
#घोषणा DORQ_REG_PF_MAX_ICID_2_RT_OFFSET				2
#घोषणा DORQ_REG_PF_MAX_ICID_3_RT_OFFSET				3
#घोषणा DORQ_REG_PF_MAX_ICID_4_RT_OFFSET				4
#घोषणा DORQ_REG_PF_MAX_ICID_5_RT_OFFSET				5
#घोषणा DORQ_REG_PF_MAX_ICID_6_RT_OFFSET				6
#घोषणा DORQ_REG_PF_MAX_ICID_7_RT_OFFSET				7
#घोषणा DORQ_REG_VF_MAX_ICID_0_RT_OFFSET				8
#घोषणा DORQ_REG_VF_MAX_ICID_1_RT_OFFSET				9
#घोषणा DORQ_REG_VF_MAX_ICID_2_RT_OFFSET				10
#घोषणा DORQ_REG_VF_MAX_ICID_3_RT_OFFSET				11
#घोषणा DORQ_REG_VF_MAX_ICID_4_RT_OFFSET				12
#घोषणा DORQ_REG_VF_MAX_ICID_5_RT_OFFSET				13
#घोषणा DORQ_REG_VF_MAX_ICID_6_RT_OFFSET				14
#घोषणा DORQ_REG_VF_MAX_ICID_7_RT_OFFSET				15
#घोषणा DORQ_REG_VF_ICID_BIT_SHIFT_NORM_RT_OFFSET			16
#घोषणा DORQ_REG_PF_WAKE_ALL_RT_OFFSET					17
#घोषणा DORQ_REG_TAG1_ETHERTYPE_RT_OFFSET				18
#घोषणा IGU_REG_PF_CONFIGURATION_RT_OFFSET				19
#घोषणा IGU_REG_VF_CONFIGURATION_RT_OFFSET				20
#घोषणा IGU_REG_ATTN_MSG_ADDR_L_RT_OFFSET				21
#घोषणा IGU_REG_ATTN_MSG_ADDR_H_RT_OFFSET				22
#घोषणा IGU_REG_LEADING_EDGE_LATCH_RT_OFFSET				23
#घोषणा IGU_REG_TRAILING_EDGE_LATCH_RT_OFFSET				24
#घोषणा CAU_REG_CQE_AGG_UNIT_SIZE_RT_OFFSET				25
#घोषणा CAU_REG_SB_VAR_MEMORY_RT_OFFSET					26
#घोषणा CAU_REG_SB_VAR_MEMORY_RT_SIZE					736
#घोषणा CAU_REG_SB_ADDR_MEMORY_RT_OFFSET				762
#घोषणा CAU_REG_SB_ADDR_MEMORY_RT_SIZE					736
#घोषणा CAU_REG_PI_MEMORY_RT_OFFSET					1498
#घोषणा CAU_REG_PI_MEMORY_RT_SIZE					4416
#घोषणा PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET			5914
#घोषणा PRS_REG_TASK_ID_MAX_INITIATOR_PF_RT_OFFSET			5915
#घोषणा PRS_REG_TASK_ID_MAX_INITIATOR_VF_RT_OFFSET			5916
#घोषणा PRS_REG_TASK_ID_MAX_TARGET_PF_RT_OFFSET				5917
#घोषणा PRS_REG_TASK_ID_MAX_TARGET_VF_RT_OFFSET				5918
#घोषणा PRS_REG_SEARCH_TCP_RT_OFFSET					5919
#घोषणा PRS_REG_SEARCH_FCOE_RT_OFFSET					5920
#घोषणा PRS_REG_SEARCH_ROCE_RT_OFFSET					5921
#घोषणा PRS_REG_ROCE_DEST_QP_MAX_VF_RT_OFFSET				5922
#घोषणा PRS_REG_ROCE_DEST_QP_MAX_PF_RT_OFFSET				5923
#घोषणा PRS_REG_SEARCH_OPENFLOW_RT_OFFSET				5924
#घोषणा PRS_REG_SEARCH_NON_IP_AS_OPENFLOW_RT_OFFSET			5925
#घोषणा PRS_REG_OPENFLOW_SUPPORT_ONLY_KNOWN_OVER_IP_RT_OFFSET		5926
#घोषणा PRS_REG_OPENFLOW_SEARCH_KEY_MASK_RT_OFFSET			5927
#घोषणा PRS_REG_TAG_ETHERTYPE_0_RT_OFFSET				5928
#घोषणा PRS_REG_LIGHT_L2_ETHERTYPE_EN_RT_OFFSET				5929
#घोषणा SRC_REG_FIRSTFREE_RT_OFFSET					5930
#घोषणा SRC_REG_FIRSTFREE_RT_SIZE					2
#घोषणा SRC_REG_LASTFREE_RT_OFFSET					5932
#घोषणा SRC_REG_LASTFREE_RT_SIZE					2
#घोषणा SRC_REG_COUNTFREE_RT_OFFSET					5934
#घोषणा SRC_REG_NUMBER_HASH_BITS_RT_OFFSET				5935
#घोषणा PSWRQ2_REG_CDUT_P_SIZE_RT_OFFSET				5936
#घोषणा PSWRQ2_REG_CDUC_P_SIZE_RT_OFFSET				5937
#घोषणा PSWRQ2_REG_TM_P_SIZE_RT_OFFSET					5938
#घोषणा PSWRQ2_REG_QM_P_SIZE_RT_OFFSET					5939
#घोषणा PSWRQ2_REG_SRC_P_SIZE_RT_OFFSET					5940
#घोषणा PSWRQ2_REG_TSDM_P_SIZE_RT_OFFSET				5941
#घोषणा PSWRQ2_REG_TM_FIRST_ILT_RT_OFFSET				5942
#घोषणा PSWRQ2_REG_TM_LAST_ILT_RT_OFFSET				5943
#घोषणा PSWRQ2_REG_QM_FIRST_ILT_RT_OFFSET				5944
#घोषणा PSWRQ2_REG_QM_LAST_ILT_RT_OFFSET				5945
#घोषणा PSWRQ2_REG_SRC_FIRST_ILT_RT_OFFSET				5946
#घोषणा PSWRQ2_REG_SRC_LAST_ILT_RT_OFFSET				5947
#घोषणा PSWRQ2_REG_CDUC_FIRST_ILT_RT_OFFSET				5948
#घोषणा PSWRQ2_REG_CDUC_LAST_ILT_RT_OFFSET				5949
#घोषणा PSWRQ2_REG_CDUT_FIRST_ILT_RT_OFFSET				5950
#घोषणा PSWRQ2_REG_CDUT_LAST_ILT_RT_OFFSET				5951
#घोषणा PSWRQ2_REG_TSDM_FIRST_ILT_RT_OFFSET				5952
#घोषणा PSWRQ2_REG_TSDM_LAST_ILT_RT_OFFSET				5953
#घोषणा PSWRQ2_REG_TM_NUMBER_OF_PF_BLOCKS_RT_OFFSET			5954
#घोषणा PSWRQ2_REG_CDUT_NUMBER_OF_PF_BLOCKS_RT_OFFSET			5955
#घोषणा PSWRQ2_REG_CDUC_NUMBER_OF_PF_BLOCKS_RT_OFFSET			5956
#घोषणा PSWRQ2_REG_TM_VF_BLOCKS_RT_OFFSET				5957
#घोषणा PSWRQ2_REG_CDUT_VF_BLOCKS_RT_OFFSET				5958
#घोषणा PSWRQ2_REG_CDUC_VF_BLOCKS_RT_OFFSET				5959
#घोषणा PSWRQ2_REG_TM_BLOCKS_FACTOR_RT_OFFSET				5960
#घोषणा PSWRQ2_REG_CDUT_BLOCKS_FACTOR_RT_OFFSET				5961
#घोषणा PSWRQ2_REG_CDUC_BLOCKS_FACTOR_RT_OFFSET				5962
#घोषणा PSWRQ2_REG_VF_BASE_RT_OFFSET					5963
#घोषणा PSWRQ2_REG_VF_LAST_ILT_RT_OFFSET				5964
#घोषणा PSWRQ2_REG_DRAM_ALIGN_WR_RT_OFFSET				5965
#घोषणा PSWRQ2_REG_DRAM_ALIGN_RD_RT_OFFSET				5966
#घोषणा PSWRQ2_REG_ILT_MEMORY_RT_OFFSET					5967
#घोषणा PSWRQ2_REG_ILT_MEMORY_RT_SIZE					22000
#घोषणा PGLUE_REG_B_VF_BASE_RT_OFFSET					27967
#घोषणा PGLUE_REG_B_MSDM_OFFSET_MASK_B_RT_OFFSET			27968
#घोषणा PGLUE_REG_B_MSDM_VF_SHIFT_B_RT_OFFSET				27969
#घोषणा PGLUE_REG_B_CACHE_LINE_SIZE_RT_OFFSET				27970
#घोषणा PGLUE_REG_B_PF_BAR0_SIZE_RT_OFFSET				27971
#घोषणा PGLUE_REG_B_PF_BAR1_SIZE_RT_OFFSET				27972
#घोषणा PGLUE_REG_B_VF_BAR1_SIZE_RT_OFFSET				27973
#घोषणा TM_REG_VF_ENABLE_CONN_RT_OFFSET					27974
#घोषणा TM_REG_PF_ENABLE_CONN_RT_OFFSET					27975
#घोषणा TM_REG_PF_ENABLE_TASK_RT_OFFSET					27976
#घोषणा TM_REG_GROUP_SIZE_RESOLUTION_CONN_RT_OFFSET			27977
#घोषणा TM_REG_GROUP_SIZE_RESOLUTION_TASK_RT_OFFSET			27978
#घोषणा TM_REG_CONFIG_CONN_MEM_RT_OFFSET				27979
#घोषणा TM_REG_CONFIG_CONN_MEM_RT_SIZE					416
#घोषणा TM_REG_CONFIG_TASK_MEM_RT_OFFSET				28395
#घोषणा TM_REG_CONFIG_TASK_MEM_RT_SIZE					512
#घोषणा QM_REG_MAXPQSIZE_0_RT_OFFSET					28907
#घोषणा QM_REG_MAXPQSIZE_1_RT_OFFSET					28908
#घोषणा QM_REG_MAXPQSIZE_2_RT_OFFSET					28909
#घोषणा QM_REG_MAXPQSIZETXSEL_0_RT_OFFSET				28910
#घोषणा QM_REG_MAXPQSIZETXSEL_1_RT_OFFSET				28911
#घोषणा QM_REG_MAXPQSIZETXSEL_2_RT_OFFSET				28912
#घोषणा QM_REG_MAXPQSIZETXSEL_3_RT_OFFSET				28913
#घोषणा QM_REG_MAXPQSIZETXSEL_4_RT_OFFSET				28914
#घोषणा QM_REG_MAXPQSIZETXSEL_5_RT_OFFSET				28915
#घोषणा QM_REG_MAXPQSIZETXSEL_6_RT_OFFSET				28916
#घोषणा QM_REG_MAXPQSIZETXSEL_7_RT_OFFSET				28917
#घोषणा QM_REG_MAXPQSIZETXSEL_8_RT_OFFSET				28918
#घोषणा QM_REG_MAXPQSIZETXSEL_9_RT_OFFSET				28919
#घोषणा QM_REG_MAXPQSIZETXSEL_10_RT_OFFSET				28920
#घोषणा QM_REG_MAXPQSIZETXSEL_11_RT_OFFSET				28921
#घोषणा QM_REG_MAXPQSIZETXSEL_12_RT_OFFSET				28922
#घोषणा QM_REG_MAXPQSIZETXSEL_13_RT_OFFSET				28923
#घोषणा QM_REG_MAXPQSIZETXSEL_14_RT_OFFSET				28924
#घोषणा QM_REG_MAXPQSIZETXSEL_15_RT_OFFSET				28925
#घोषणा QM_REG_MAXPQSIZETXSEL_16_RT_OFFSET				28926
#घोषणा QM_REG_MAXPQSIZETXSEL_17_RT_OFFSET				28927
#घोषणा QM_REG_MAXPQSIZETXSEL_18_RT_OFFSET				28928
#घोषणा QM_REG_MAXPQSIZETXSEL_19_RT_OFFSET				28929
#घोषणा QM_REG_MAXPQSIZETXSEL_20_RT_OFFSET				28930
#घोषणा QM_REG_MAXPQSIZETXSEL_21_RT_OFFSET				28931
#घोषणा QM_REG_MAXPQSIZETXSEL_22_RT_OFFSET				28932
#घोषणा QM_REG_MAXPQSIZETXSEL_23_RT_OFFSET				28933
#घोषणा QM_REG_MAXPQSIZETXSEL_24_RT_OFFSET				28934
#घोषणा QM_REG_MAXPQSIZETXSEL_25_RT_OFFSET				28935
#घोषणा QM_REG_MAXPQSIZETXSEL_26_RT_OFFSET				28936
#घोषणा QM_REG_MAXPQSIZETXSEL_27_RT_OFFSET				28937
#घोषणा QM_REG_MAXPQSIZETXSEL_28_RT_OFFSET				28938
#घोषणा QM_REG_MAXPQSIZETXSEL_29_RT_OFFSET				28939
#घोषणा QM_REG_MAXPQSIZETXSEL_30_RT_OFFSET				28940
#घोषणा QM_REG_MAXPQSIZETXSEL_31_RT_OFFSET				28941
#घोषणा QM_REG_MAXPQSIZETXSEL_32_RT_OFFSET				28942
#घोषणा QM_REG_MAXPQSIZETXSEL_33_RT_OFFSET				28943
#घोषणा QM_REG_MAXPQSIZETXSEL_34_RT_OFFSET				28944
#घोषणा QM_REG_MAXPQSIZETXSEL_35_RT_OFFSET				28945
#घोषणा QM_REG_MAXPQSIZETXSEL_36_RT_OFFSET				28946
#घोषणा QM_REG_MAXPQSIZETXSEL_37_RT_OFFSET				28947
#घोषणा QM_REG_MAXPQSIZETXSEL_38_RT_OFFSET				28948
#घोषणा QM_REG_MAXPQSIZETXSEL_39_RT_OFFSET				28949
#घोषणा QM_REG_MAXPQSIZETXSEL_40_RT_OFFSET				28950
#घोषणा QM_REG_MAXPQSIZETXSEL_41_RT_OFFSET				28951
#घोषणा QM_REG_MAXPQSIZETXSEL_42_RT_OFFSET				28952
#घोषणा QM_REG_MAXPQSIZETXSEL_43_RT_OFFSET				28953
#घोषणा QM_REG_MAXPQSIZETXSEL_44_RT_OFFSET				28954
#घोषणा QM_REG_MAXPQSIZETXSEL_45_RT_OFFSET				28955
#घोषणा QM_REG_MAXPQSIZETXSEL_46_RT_OFFSET				28956
#घोषणा QM_REG_MAXPQSIZETXSEL_47_RT_OFFSET				28957
#घोषणा QM_REG_MAXPQSIZETXSEL_48_RT_OFFSET				28958
#घोषणा QM_REG_MAXPQSIZETXSEL_49_RT_OFFSET				28959
#घोषणा QM_REG_MAXPQSIZETXSEL_50_RT_OFFSET				28960
#घोषणा QM_REG_MAXPQSIZETXSEL_51_RT_OFFSET				28961
#घोषणा QM_REG_MAXPQSIZETXSEL_52_RT_OFFSET				28962
#घोषणा QM_REG_MAXPQSIZETXSEL_53_RT_OFFSET				28963
#घोषणा QM_REG_MAXPQSIZETXSEL_54_RT_OFFSET				28964
#घोषणा QM_REG_MAXPQSIZETXSEL_55_RT_OFFSET				28965
#घोषणा QM_REG_MAXPQSIZETXSEL_56_RT_OFFSET				28966
#घोषणा QM_REG_MAXPQSIZETXSEL_57_RT_OFFSET				28967
#घोषणा QM_REG_MAXPQSIZETXSEL_58_RT_OFFSET				28968
#घोषणा QM_REG_MAXPQSIZETXSEL_59_RT_OFFSET				28969
#घोषणा QM_REG_MAXPQSIZETXSEL_60_RT_OFFSET				28970
#घोषणा QM_REG_MAXPQSIZETXSEL_61_RT_OFFSET				28971
#घोषणा QM_REG_MAXPQSIZETXSEL_62_RT_OFFSET				28972
#घोषणा QM_REG_MAXPQSIZETXSEL_63_RT_OFFSET				28973
#घोषणा QM_REG_BASEADDROTHERPQ_RT_OFFSET				28974
#घोषणा QM_REG_BASEADDROTHERPQ_RT_SIZE					128
#घोषणा QM_REG_PTRTBLOTHER_RT_OFFSET					29102
#घोषणा QM_REG_PTRTBLOTHER_RT_SIZE					256
#घोषणा QM_REG_VOQCRDLINE_RT_OFFSET					29358
#घोषणा QM_REG_VOQCRDLINE_RT_SIZE					20
#घोषणा QM_REG_VOQINITCRDLINE_RT_OFFSET					29378
#घोषणा QM_REG_VOQINITCRDLINE_RT_SIZE					20
#घोषणा QM_REG_AFULLQMBYPTHRPFWFQ_RT_OFFSET				29398
#घोषणा QM_REG_AFULLQMBYPTHRVPWFQ_RT_OFFSET				29399
#घोषणा QM_REG_AFULLQMBYPTHRPFRL_RT_OFFSET				29400
#घोषणा QM_REG_AFULLQMBYPTHRGLBLRL_RT_OFFSET				29401
#घोषणा QM_REG_AFULLOPRTNSTCCRDMASK_RT_OFFSET				29402
#घोषणा QM_REG_WRROTHERPQGRP_0_RT_OFFSET				29403
#घोषणा QM_REG_WRROTHERPQGRP_1_RT_OFFSET				29404
#घोषणा QM_REG_WRROTHERPQGRP_2_RT_OFFSET				29405
#घोषणा QM_REG_WRROTHERPQGRP_3_RT_OFFSET				29406
#घोषणा QM_REG_WRROTHERPQGRP_4_RT_OFFSET				29407
#घोषणा QM_REG_WRROTHERPQGRP_5_RT_OFFSET				29408
#घोषणा QM_REG_WRROTHERPQGRP_6_RT_OFFSET				29409
#घोषणा QM_REG_WRROTHERPQGRP_7_RT_OFFSET				29410
#घोषणा QM_REG_WRROTHERPQGRP_8_RT_OFFSET				29411
#घोषणा QM_REG_WRROTHERPQGRP_9_RT_OFFSET				29412
#घोषणा QM_REG_WRROTHERPQGRP_10_RT_OFFSET				29413
#घोषणा QM_REG_WRROTHERPQGRP_11_RT_OFFSET				29414
#घोषणा QM_REG_WRROTHERPQGRP_12_RT_OFFSET				29415
#घोषणा QM_REG_WRROTHERPQGRP_13_RT_OFFSET				29416
#घोषणा QM_REG_WRROTHERPQGRP_14_RT_OFFSET				29417
#घोषणा QM_REG_WRROTHERPQGRP_15_RT_OFFSET				29418
#घोषणा QM_REG_WRROTHERGRPWEIGHT_0_RT_OFFSET				29419
#घोषणा QM_REG_WRROTHERGRPWEIGHT_1_RT_OFFSET				29420
#घोषणा QM_REG_WRROTHERGRPWEIGHT_2_RT_OFFSET				29421
#घोषणा QM_REG_WRROTHERGRPWEIGHT_3_RT_OFFSET				29422
#घोषणा QM_REG_WRRTXGRPWEIGHT_0_RT_OFFSET				29423
#घोषणा QM_REG_WRRTXGRPWEIGHT_1_RT_OFFSET				29424
#घोषणा QM_REG_PQTX2PF_0_RT_OFFSET					29425
#घोषणा QM_REG_PQTX2PF_1_RT_OFFSET					29426
#घोषणा QM_REG_PQTX2PF_2_RT_OFFSET					29427
#घोषणा QM_REG_PQTX2PF_3_RT_OFFSET					29428
#घोषणा QM_REG_PQTX2PF_4_RT_OFFSET					29429
#घोषणा QM_REG_PQTX2PF_5_RT_OFFSET					29430
#घोषणा QM_REG_PQTX2PF_6_RT_OFFSET					29431
#घोषणा QM_REG_PQTX2PF_7_RT_OFFSET					29432
#घोषणा QM_REG_PQTX2PF_8_RT_OFFSET					29433
#घोषणा QM_REG_PQTX2PF_9_RT_OFFSET					29434
#घोषणा QM_REG_PQTX2PF_10_RT_OFFSET					29435
#घोषणा QM_REG_PQTX2PF_11_RT_OFFSET					29436
#घोषणा QM_REG_PQTX2PF_12_RT_OFFSET					29437
#घोषणा QM_REG_PQTX2PF_13_RT_OFFSET					29438
#घोषणा QM_REG_PQTX2PF_14_RT_OFFSET					29439
#घोषणा QM_REG_PQTX2PF_15_RT_OFFSET					29440
#घोषणा QM_REG_PQTX2PF_16_RT_OFFSET					29441
#घोषणा QM_REG_PQTX2PF_17_RT_OFFSET					29442
#घोषणा QM_REG_PQTX2PF_18_RT_OFFSET					29443
#घोषणा QM_REG_PQTX2PF_19_RT_OFFSET					29444
#घोषणा QM_REG_PQTX2PF_20_RT_OFFSET					29445
#घोषणा QM_REG_PQTX2PF_21_RT_OFFSET					29446
#घोषणा QM_REG_PQTX2PF_22_RT_OFFSET					29447
#घोषणा QM_REG_PQTX2PF_23_RT_OFFSET					29448
#घोषणा QM_REG_PQTX2PF_24_RT_OFFSET					29449
#घोषणा QM_REG_PQTX2PF_25_RT_OFFSET					29450
#घोषणा QM_REG_PQTX2PF_26_RT_OFFSET					29451
#घोषणा QM_REG_PQTX2PF_27_RT_OFFSET					29452
#घोषणा QM_REG_PQTX2PF_28_RT_OFFSET					29453
#घोषणा QM_REG_PQTX2PF_29_RT_OFFSET					29454
#घोषणा QM_REG_PQTX2PF_30_RT_OFFSET					29455
#घोषणा QM_REG_PQTX2PF_31_RT_OFFSET					29456
#घोषणा QM_REG_PQTX2PF_32_RT_OFFSET					29457
#घोषणा QM_REG_PQTX2PF_33_RT_OFFSET					29458
#घोषणा QM_REG_PQTX2PF_34_RT_OFFSET					29459
#घोषणा QM_REG_PQTX2PF_35_RT_OFFSET					29460
#घोषणा QM_REG_PQTX2PF_36_RT_OFFSET					29461
#घोषणा QM_REG_PQTX2PF_37_RT_OFFSET					29462
#घोषणा QM_REG_PQTX2PF_38_RT_OFFSET					29463
#घोषणा QM_REG_PQTX2PF_39_RT_OFFSET					29464
#घोषणा QM_REG_PQTX2PF_40_RT_OFFSET					29465
#घोषणा QM_REG_PQTX2PF_41_RT_OFFSET					29466
#घोषणा QM_REG_PQTX2PF_42_RT_OFFSET					29467
#घोषणा QM_REG_PQTX2PF_43_RT_OFFSET					29468
#घोषणा QM_REG_PQTX2PF_44_RT_OFFSET					29469
#घोषणा QM_REG_PQTX2PF_45_RT_OFFSET					29470
#घोषणा QM_REG_PQTX2PF_46_RT_OFFSET					29471
#घोषणा QM_REG_PQTX2PF_47_RT_OFFSET					29472
#घोषणा QM_REG_PQTX2PF_48_RT_OFFSET					29473
#घोषणा QM_REG_PQTX2PF_49_RT_OFFSET					29474
#घोषणा QM_REG_PQTX2PF_50_RT_OFFSET					29475
#घोषणा QM_REG_PQTX2PF_51_RT_OFFSET					29476
#घोषणा QM_REG_PQTX2PF_52_RT_OFFSET					29477
#घोषणा QM_REG_PQTX2PF_53_RT_OFFSET					29478
#घोषणा QM_REG_PQTX2PF_54_RT_OFFSET					29479
#घोषणा QM_REG_PQTX2PF_55_RT_OFFSET					29480
#घोषणा QM_REG_PQTX2PF_56_RT_OFFSET					29481
#घोषणा QM_REG_PQTX2PF_57_RT_OFFSET					29482
#घोषणा QM_REG_PQTX2PF_58_RT_OFFSET					29483
#घोषणा QM_REG_PQTX2PF_59_RT_OFFSET					29484
#घोषणा QM_REG_PQTX2PF_60_RT_OFFSET					29485
#घोषणा QM_REG_PQTX2PF_61_RT_OFFSET					29486
#घोषणा QM_REG_PQTX2PF_62_RT_OFFSET					29487
#घोषणा QM_REG_PQTX2PF_63_RT_OFFSET					29488
#घोषणा QM_REG_PQOTHER2PF_0_RT_OFFSET					29489
#घोषणा QM_REG_PQOTHER2PF_1_RT_OFFSET					29490
#घोषणा QM_REG_PQOTHER2PF_2_RT_OFFSET					29491
#घोषणा QM_REG_PQOTHER2PF_3_RT_OFFSET					29492
#घोषणा QM_REG_PQOTHER2PF_4_RT_OFFSET					29493
#घोषणा QM_REG_PQOTHER2PF_5_RT_OFFSET					29494
#घोषणा QM_REG_PQOTHER2PF_6_RT_OFFSET					29495
#घोषणा QM_REG_PQOTHER2PF_7_RT_OFFSET					29496
#घोषणा QM_REG_PQOTHER2PF_8_RT_OFFSET					29497
#घोषणा QM_REG_PQOTHER2PF_9_RT_OFFSET					29498
#घोषणा QM_REG_PQOTHER2PF_10_RT_OFFSET					29499
#घोषणा QM_REG_PQOTHER2PF_11_RT_OFFSET					29500
#घोषणा QM_REG_PQOTHER2PF_12_RT_OFFSET					29501
#घोषणा QM_REG_PQOTHER2PF_13_RT_OFFSET					29502
#घोषणा QM_REG_PQOTHER2PF_14_RT_OFFSET					29503
#घोषणा QM_REG_PQOTHER2PF_15_RT_OFFSET					29504
#घोषणा QM_REG_RLGLBLPERIOD_0_RT_OFFSET					29505
#घोषणा QM_REG_RLGLBLPERIOD_1_RT_OFFSET					29506
#घोषणा QM_REG_RLGLBLPERIODTIMER_0_RT_OFFSET				29507
#घोषणा QM_REG_RLGLBLPERIODTIMER_1_RT_OFFSET				29508
#घोषणा QM_REG_RLGLBLPERIODSEL_0_RT_OFFSET				29509
#घोषणा QM_REG_RLGLBLPERIODSEL_1_RT_OFFSET				29510
#घोषणा QM_REG_RLGLBLPERIODSEL_2_RT_OFFSET				29511
#घोषणा QM_REG_RLGLBLPERIODSEL_3_RT_OFFSET				29512
#घोषणा QM_REG_RLGLBLPERIODSEL_4_RT_OFFSET				29513
#घोषणा QM_REG_RLGLBLPERIODSEL_5_RT_OFFSET				29514
#घोषणा QM_REG_RLGLBLPERIODSEL_6_RT_OFFSET				29515
#घोषणा QM_REG_RLGLBLPERIODSEL_7_RT_OFFSET				29516
#घोषणा QM_REG_RLGLBLINCVAL_RT_OFFSET					29517
#घोषणा QM_REG_RLGLBLINCVAL_RT_SIZE					256
#घोषणा QM_REG_RLGLBLUPPERBOUND_RT_OFFSET				29773
#घोषणा QM_REG_RLGLBLUPPERBOUND_RT_SIZE					256
#घोषणा QM_REG_RLGLBLCRD_RT_OFFSET					30029
#घोषणा QM_REG_RLGLBLCRD_RT_SIZE					256
#घोषणा QM_REG_RLGLBLENABLE_RT_OFFSET					30285
#घोषणा QM_REG_RLPFPERIOD_RT_OFFSET					30286
#घोषणा QM_REG_RLPFPERIODTIMER_RT_OFFSET				30287
#घोषणा QM_REG_RLPFINCVAL_RT_OFFSET					30288
#घोषणा QM_REG_RLPFINCVAL_RT_SIZE					16
#घोषणा QM_REG_RLPFUPPERBOUND_RT_OFFSET					30304
#घोषणा QM_REG_RLPFUPPERBOUND_RT_SIZE					16
#घोषणा QM_REG_RLPFCRD_RT_OFFSET					30320
#घोषणा QM_REG_RLPFCRD_RT_SIZE						16
#घोषणा QM_REG_RLPFENABLE_RT_OFFSET					30336
#घोषणा QM_REG_RLPFVOQENABLE_RT_OFFSET					30337
#घोषणा QM_REG_WFQPFWEIGHT_RT_OFFSET					30338
#घोषणा QM_REG_WFQPFWEIGHT_RT_SIZE					16
#घोषणा QM_REG_WFQPFUPPERBOUND_RT_OFFSET				30354
#घोषणा QM_REG_WFQPFUPPERBOUND_RT_SIZE					16
#घोषणा QM_REG_WFQPFCRD_RT_OFFSET					30370
#घोषणा QM_REG_WFQPFCRD_RT_SIZE						160
#घोषणा QM_REG_WFQPFENABLE_RT_OFFSET					30530
#घोषणा QM_REG_WFQVPENABLE_RT_OFFSET					30531
#घोषणा QM_REG_BASEADDRTXPQ_RT_OFFSET					30532
#घोषणा QM_REG_BASEADDRTXPQ_RT_SIZE					512
#घोषणा QM_REG_TXPQMAP_RT_OFFSET					31044
#घोषणा QM_REG_TXPQMAP_RT_SIZE						512
#घोषणा QM_REG_WFQVPWEIGHT_RT_OFFSET					31556
#घोषणा QM_REG_WFQVPWEIGHT_RT_SIZE					512
#घोषणा QM_REG_WFQVPCRD_RT_OFFSET					32068
#घोषणा QM_REG_WFQVPCRD_RT_SIZE						512
#घोषणा QM_REG_WFQVPMAP_RT_OFFSET					32580
#घोषणा QM_REG_WFQVPMAP_RT_SIZE						512
#घोषणा QM_REG_PTRTBLTX_RT_OFFSET					33092
#घोषणा QM_REG_PTRTBLTX_RT_SIZE						1024
#घोषणा QM_REG_WFQPFCRD_MSB_RT_OFFSET					34116
#घोषणा QM_REG_WFQPFCRD_MSB_RT_SIZE					160
#घोषणा NIG_REG_TAG_ETHERTYPE_0_RT_OFFSET				34276
#घोषणा NIG_REG_BRB_GATE_DNTFWD_PORT_RT_OFFSET				34277
#घोषणा NIG_REG_OUTER_TAG_VALUE_LIST0_RT_OFFSET				34278
#घोषणा NIG_REG_OUTER_TAG_VALUE_LIST1_RT_OFFSET				34279
#घोषणा NIG_REG_OUTER_TAG_VALUE_LIST2_RT_OFFSET				34280
#घोषणा NIG_REG_OUTER_TAG_VALUE_LIST3_RT_OFFSET				34281
#घोषणा NIG_REG_LLH_FUNC_TAGMAC_CLS_TYPE_RT_OFFSET			34282
#घोषणा NIG_REG_LLH_FUNC_TAG_EN_RT_OFFSET				34283
#घोषणा NIG_REG_LLH_FUNC_TAG_EN_RT_SIZE					4
#घोषणा NIG_REG_LLH_FUNC_TAG_VALUE_RT_OFFSET				34287
#घोषणा NIG_REG_LLH_FUNC_TAG_VALUE_RT_SIZE				4
#घोषणा NIG_REG_LLH_FUNC_FILTER_VALUE_RT_OFFSET				34291
#घोषणा NIG_REG_LLH_FUNC_FILTER_VALUE_RT_SIZE				32
#घोषणा NIG_REG_LLH_FUNC_FILTER_EN_RT_OFFSET				34323
#घोषणा NIG_REG_LLH_FUNC_FILTER_EN_RT_SIZE				16
#घोषणा NIG_REG_LLH_FUNC_FILTER_MODE_RT_OFFSET				34339
#घोषणा NIG_REG_LLH_FUNC_FILTER_MODE_RT_SIZE				16
#घोषणा NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE_RT_OFFSET			34355
#घोषणा NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE_RT_SIZE			16
#घोषणा NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_OFFSET			34371
#घोषणा NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_SIZE				16
#घोषणा NIG_REG_TX_EDPM_CTRL_RT_OFFSET					34387
#घोषणा NIG_REG_PPF_TO_ENGINE_SEL_RT_OFFSET				34388
#घोषणा NIG_REG_PPF_TO_ENGINE_SEL_RT_SIZE				8
#घोषणा CDU_REG_CID_ADDR_PARAMS_RT_OFFSET				34396
#घोषणा CDU_REG_SEGMENT0_PARAMS_RT_OFFSET				34397
#घोषणा CDU_REG_SEGMENT1_PARAMS_RT_OFFSET				34398
#घोषणा CDU_REG_PF_SEG0_TYPE_OFFSET_RT_OFFSET				34399
#घोषणा CDU_REG_PF_SEG1_TYPE_OFFSET_RT_OFFSET				34400
#घोषणा CDU_REG_PF_SEG2_TYPE_OFFSET_RT_OFFSET				34401
#घोषणा CDU_REG_PF_SEG3_TYPE_OFFSET_RT_OFFSET				34402
#घोषणा CDU_REG_PF_FL_SEG0_TYPE_OFFSET_RT_OFFSET			34403
#घोषणा CDU_REG_PF_FL_SEG1_TYPE_OFFSET_RT_OFFSET			34404
#घोषणा CDU_REG_PF_FL_SEG2_TYPE_OFFSET_RT_OFFSET			34405
#घोषणा CDU_REG_PF_FL_SEG3_TYPE_OFFSET_RT_OFFSET			34406
#घोषणा CDU_REG_VF_SEG_TYPE_OFFSET_RT_OFFSET				34407
#घोषणा CDU_REG_VF_FL_SEG_TYPE_OFFSET_RT_OFFSET				34408
#घोषणा PBF_REG_TAG_ETHERTYPE_0_RT_OFFSET				34409
#घोषणा PBF_REG_BTB_SHARED_AREA_SIZE_RT_OFFSET				34410
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ0_RT_OFFSET			34411
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ0_RT_OFFSET				34412
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ0_RT_OFFSET			34413
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ1_RT_OFFSET			34414
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ1_RT_OFFSET				34415
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ1_RT_OFFSET			34416
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ2_RT_OFFSET			34417
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ2_RT_OFFSET				34418
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ2_RT_OFFSET			34419
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ3_RT_OFFSET			34420
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ3_RT_OFFSET				34421
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ3_RT_OFFSET			34422
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ4_RT_OFFSET			34423
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ4_RT_OFFSET				34424
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ4_RT_OFFSET			34425
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ5_RT_OFFSET			34426
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ5_RT_OFFSET				34427
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ5_RT_OFFSET			34428
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ6_RT_OFFSET			34429
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ6_RT_OFFSET				34430
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ6_RT_OFFSET			34431
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ7_RT_OFFSET			34432
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ7_RT_OFFSET				34433
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ7_RT_OFFSET			34434
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ8_RT_OFFSET			34435
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ8_RT_OFFSET				34436
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ8_RT_OFFSET			34437
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ9_RT_OFFSET			34438
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ9_RT_OFFSET				34439
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ9_RT_OFFSET			34440
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ10_RT_OFFSET			34441
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ10_RT_OFFSET				34442
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ10_RT_OFFSET			34443
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ11_RT_OFFSET			34444
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ11_RT_OFFSET				34445
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ11_RT_OFFSET			34446
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ12_RT_OFFSET			34447
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ12_RT_OFFSET				34448
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ12_RT_OFFSET			34449
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ13_RT_OFFSET			34450
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ13_RT_OFFSET				34451
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ13_RT_OFFSET			34452
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ14_RT_OFFSET			34453
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ14_RT_OFFSET				34454
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ14_RT_OFFSET			34455
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ15_RT_OFFSET			34456
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ15_RT_OFFSET				34457
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ15_RT_OFFSET			34458
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ16_RT_OFFSET			34459
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ16_RT_OFFSET				34460
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ16_RT_OFFSET			34461
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ17_RT_OFFSET			34462
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ17_RT_OFFSET				34463
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ17_RT_OFFSET			34464
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ18_RT_OFFSET			34465
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ18_RT_OFFSET				34466
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ18_RT_OFFSET			34467
#घोषणा PBF_REG_YCMD_QS_NUM_LINES_VOQ19_RT_OFFSET			34468
#घोषणा PBF_REG_BTB_GUARANTEED_VOQ19_RT_OFFSET				34469
#घोषणा PBF_REG_BTB_SHARED_AREA_SETUP_VOQ19_RT_OFFSET			34470
#घोषणा XCM_REG_CON_PHY_Q3_RT_OFFSET					34471

#घोषणा RUNTIME_ARRAY_SIZE 34472

/* Init Callbacks */
#घोषणा DMAE_READY_CB	0

/* The eth storm context क्रम the Tstorm */
काष्ठा tstorm_eth_conn_st_ctx अणु
	__le32 reserved[4];
पूर्ण;

/* The eth storm context क्रम the Pstorm */
काष्ठा pstorm_eth_conn_st_ctx अणु
	__le32 reserved[8];
पूर्ण;

/* The eth storm context क्रम the Xstorm */
काष्ठा xstorm_eth_conn_st_ctx अणु
	__le32 reserved[60];
पूर्ण;

काष्ठा e4_xstorm_eth_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED1_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED3_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED4_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED5_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED6_SHIFT	7
		u8 flags1;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED7_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED8_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED9_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_BIT11_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_E5_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_E5_RESERVED2_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_E5_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_E5_RESERVED3_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TX_RULE_ACTIVE_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TX_RULE_ACTIVE_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_DQ_CF_ACTIVE_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_DQ_CF_ACTIVE_SHIFT	7
	u8 flags2;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF0_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF1_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF2_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF4_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF5_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF6_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF7_SHIFT	6
		u8 flags4;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF12_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF12_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF13_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF13_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF14_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF14_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF15_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_GO_TO_BD_CONS_CF_MASK		0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_GO_TO_BD_CONS_CF_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_MULTI_UNICAST_CF_MASK		0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_MULTI_UNICAST_CF_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_DQ_CF_MASK			0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_DQ_CF_SHIFT			4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TERMINATE_CF_MASK		0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TERMINATE_CF_SHIFT		6
	u8 flags7;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_FLUSH_Q0_MASK		0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_FLUSH_Q0_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED10_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED10_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF0EN_SHIFT		6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF1EN_SHIFT		7
	u8 flags8;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF2EN_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF3EN_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF4EN_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF5EN_SHIFT	3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF6EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF6EN_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF7EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF7EN_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF8EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF8EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF9EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF9EN_SHIFT	7
	u8 flags9;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF10EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF10EN_SHIFT			0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF11EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF11EN_SHIFT			1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF12EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF12EN_SHIFT			2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF13EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF13EN_SHIFT			3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF14EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF14EN_SHIFT			4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF15EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_CF15EN_SHIFT			5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_GO_TO_BD_CONS_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_GO_TO_BD_CONS_CF_EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_MULTI_UNICAST_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_MULTI_UNICAST_CF_EN_SHIFT	7
	u8 flags10;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_DQ_CF_EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_DQ_CF_EN_SHIFT		0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TERMINATE_CF_EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TERMINATE_CF_EN_SHIFT		1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_FLUSH_Q0_EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_FLUSH_Q0_EN_SHIFT		2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED11_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED11_SHIFT		3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_SLOW_PATH_EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_SLOW_PATH_EN_SHIFT		4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TPH_ENABLE_EN_RESERVED_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TPH_ENABLE_EN_RESERVED_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED12_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED12_SHIFT		6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED13_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED13_SHIFT		7
	u8 flags11;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED14_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED14_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED15_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RESERVED15_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TX_DEC_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TX_DEC_RULE_EN_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE5EN_SHIFT		3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE6EN_SHIFT		4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE7EN_SHIFT		5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED1_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE9EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE9EN_SHIFT		7
	u8 flags12;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE10EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE10EN_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE11EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE11EN_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED3_SHIFT	3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE14EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE14EN_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE15EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE15EN_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE16EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE16EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE17EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE17EN_SHIFT	7
	u8 flags13;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE18EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE18EN_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE19EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_RULE19EN_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED4_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED5_SHIFT	3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED6_SHIFT	4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED7_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED8_SHIFT	6
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_USE_EXT_HDR_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_USE_EXT_HDR_SHIFT	0
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_SEND_RAW_L3L4_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_SEND_RAW_L3L4_SHIFT	1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_INBAND_PROP_HDR_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_INBAND_PROP_HDR_SHIFT	2
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_SEND_EXT_TUNNEL_MASK	0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_EDPM_SEND_EXT_TUNNEL_SHIFT	3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_L2_EDPM_ENABLE_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_L2_EDPM_ENABLE_SHIFT		4
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_ROCE_EDPM_ENABLE_MASK		0x1
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_ROCE_EDPM_ENABLE_SHIFT	5
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TPH_ENABLE_MASK		0x3
#घोषणा E4_XSTORM_ETH_CONN_AG_CTX_TPH_ENABLE_SHIFT		6
	u8 edpm_event_id;
	__le16 physical_q0;
	__le16 e5_reserved1;
	__le16 edpm_num_bds;
	__le16 tx_bd_cons;
	__le16 tx_bd_prod;
	__le16 updated_qm_pq_id;
	__le16 conn_dpi;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le16 word7;
	__le16 word8;
	__le16 word9;
	__le16 word10;
	__le32 reg7;
	__le32 reg8;
	__le32 reg9;
	u8 byte7;
	u8 byte8;
	u8 byte9;
	u8 byte10;
	u8 byte11;
	u8 byte12;
	u8 byte13;
	u8 byte14;
	u8 byte15;
	u8 e5_reserved;
	__le16 word11;
	__le32 reg10;
	__le32 reg11;
	__le32 reg12;
	__le32 reg13;
	__le32 reg14;
	__le32 reg15;
	__le32 reg16;
	__le32 reg17;
	__le32 reg18;
	__le32 reg19;
	__le16 word12;
	__le16 word13;
	__le16 word14;
	__le16 word15;
पूर्ण;

/* The eth storm context क्रम the Ystorm */
काष्ठा ystorm_eth_conn_st_ctx अणु
	__le32 reserved[8];
पूर्ण;

काष्ठा e4_ystorm_eth_conn_ag_ctx अणु
	u8 byte0;
	u8 state;
	u8 flags0;
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_BIT0_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_BIT0_SHIFT			0
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_BIT1_SHIFT			1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_MASK	0x3
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_SHIFT	2
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_PMD_TERMINATE_CF_MASK		0x3
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_PMD_TERMINATE_CF_SHIFT	4
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_CF2_MASK			0x3
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_CF2_SHIFT			6
	u8 flags1;
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_EN_MASK	0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_EN_SHIFT	0
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_PMD_TERMINATE_CF_EN_MASK	0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_PMD_TERMINATE_CF_EN_SHIFT	1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_CF2EN_SHIFT			2
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE0EN_SHIFT			3
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE1EN_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE1EN_SHIFT			4
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE2EN_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE2EN_SHIFT			5
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE3EN_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE3EN_SHIFT			6
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE4EN_MASK			0x1
#घोषणा E4_YSTORM_ETH_CONN_AG_CTX_RULE4EN_SHIFT			7
	u8 tx_q0_पूर्णांक_coallecing_बारet;
	u8 byte3;
	__le16 word0;
	__le32 terminate_spqe;
	__le32 reg1;
	__le16 tx_bd_cons_upd;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

काष्ठा e4_tstorm_eth_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT2_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT2_SHIFT	2
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT3_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT3_SHIFT	3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT4_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT4_SHIFT	4
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT5_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_BIT5_SHIFT	5
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF0_SHIFT	6
	u8 flags1;
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF1_SHIFT	0
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF2_SHIFT	2
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF3_SHIFT	4
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF4_SHIFT	6
	u8 flags2;
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF5_SHIFT	0
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF6_SHIFT	2
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF7_SHIFT	4
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF8_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF9_SHIFT	0
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF10_SHIFT	2
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF0EN_SHIFT	4
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF1EN_SHIFT	5
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF2EN_SHIFT	6
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF3EN_SHIFT	7
	u8 flags4;
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF4EN_SHIFT	0
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF5EN_SHIFT	1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF6EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF6EN_SHIFT	2
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF7EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF7EN_SHIFT	3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF8EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF8EN_SHIFT	4
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF9EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF9EN_SHIFT	5
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF10EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_CF10EN_SHIFT	6
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags5;
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE1EN_SHIFT		0
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE2EN_SHIFT		1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE3EN_SHIFT		2
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE4EN_SHIFT		3
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE5EN_SHIFT		4
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RX_BD_EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RX_BD_EN_SHIFT	5
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE7EN_SHIFT		6
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_TSTORM_ETH_CONN_AG_CTX_RULE8EN_SHIFT		7
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le32 reg7;
	__le32 reg8;
	u8 byte2;
	u8 byte3;
	__le16 rx_bd_cons;
	u8 byte4;
	u8 byte5;
	__le16 rx_bd_prod;
	__le16 word2;
	__le16 word3;
	__le32 reg9;
	__le32 reg10;
पूर्ण;

काष्ठा e4_ustorm_eth_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_BIT0_MASK			0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_BIT0_SHIFT			0
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_BIT1_SHIFT			1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_PMD_TERMINATE_CF_MASK	0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_PMD_TERMINATE_CF_SHIFT	2
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_PMD_TERMINATE_CF_MASK	0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_PMD_TERMINATE_CF_SHIFT	4
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF2_MASK			0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF2_SHIFT			6
	u8 flags1;
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF3_MASK			0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF3_SHIFT			0
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_ARM_CF_MASK		0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_ARM_CF_SHIFT		2
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_ARM_CF_MASK		0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_ARM_CF_SHIFT		4
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_MASK	0x3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_PMD_TERMINATE_CF_EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_PMD_TERMINATE_CF_EN_SHIFT	0
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_PMD_TERMINATE_CF_EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_PMD_TERMINATE_CF_EN_SHIFT	1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF2EN_SHIFT			2
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF3EN_MASK			0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_CF3EN_SHIFT			3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_ARM_CF_EN_MASK		0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_ARM_CF_EN_SHIFT		4
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_ARM_CF_EN_MASK		0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RX_ARM_CF_EN_SHIFT		5
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_TX_BD_CONS_UPD_CF_EN_SHIFT	6
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE0EN_SHIFT			7
	u8 flags3;
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE8EN_MASK	0x1
#घोषणा E4_USTORM_ETH_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 tx_bd_cons;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 tx_पूर्णांक_coallecing_बारet;
	__le16 tx_drv_bd_cons;
	__le16 rx_drv_cqe_cons;
पूर्ण;

/* The eth storm context क्रम the Ustorm */
काष्ठा ustorm_eth_conn_st_ctx अणु
	__le32 reserved[40];
पूर्ण;

/* The eth storm context क्रम the Mstorm */
काष्ठा mstorm_eth_conn_st_ctx अणु
	__le32 reserved[8];
पूर्ण;

/* eth connection context */
काष्ठा e4_eth_conn_context अणु
	काष्ठा tstorm_eth_conn_st_ctx tstorm_st_context;
	काष्ठा regpair tstorm_st_padding[2];
	काष्ठा pstorm_eth_conn_st_ctx pstorm_st_context;
	काष्ठा xstorm_eth_conn_st_ctx xstorm_st_context;
	काष्ठा e4_xstorm_eth_conn_ag_ctx xstorm_ag_context;
	काष्ठा e4_tstorm_eth_conn_ag_ctx tstorm_ag_context;
	काष्ठा ystorm_eth_conn_st_ctx ystorm_st_context;
	काष्ठा e4_ystorm_eth_conn_ag_ctx ystorm_ag_context;
	काष्ठा e4_ustorm_eth_conn_ag_ctx ustorm_ag_context;
	काष्ठा ustorm_eth_conn_st_ctx ustorm_st_context;
	काष्ठा mstorm_eth_conn_st_ctx mstorm_st_context;
पूर्ण;

/* Ethernet filter types: mac/vlan/pair */
क्रमागत eth_error_code अणु
	ETH_OK = 0x00,
	ETH_FILTERS_MAC_ADD_FAIL_FULL,
	ETH_FILTERS_MAC_ADD_FAIL_FULL_MTT2,
	ETH_FILTERS_MAC_ADD_FAIL_DUP_MTT2,
	ETH_FILTERS_MAC_ADD_FAIL_DUP_STT2,
	ETH_FILTERS_MAC_DEL_FAIL_NOF,
	ETH_FILTERS_MAC_DEL_FAIL_NOF_MTT2,
	ETH_FILTERS_MAC_DEL_FAIL_NOF_STT2,
	ETH_FILTERS_MAC_ADD_FAIL_ZERO_MAC,
	ETH_FILTERS_VLAN_ADD_FAIL_FULL,
	ETH_FILTERS_VLAN_ADD_FAIL_DUP,
	ETH_FILTERS_VLAN_DEL_FAIL_NOF,
	ETH_FILTERS_VLAN_DEL_FAIL_NOF_TT1,
	ETH_FILTERS_PAIR_ADD_FAIL_DUP,
	ETH_FILTERS_PAIR_ADD_FAIL_FULL,
	ETH_FILTERS_PAIR_ADD_FAIL_FULL_MAC,
	ETH_FILTERS_PAIR_DEL_FAIL_NOF,
	ETH_FILTERS_PAIR_DEL_FAIL_NOF_TT1,
	ETH_FILTERS_PAIR_ADD_FAIL_ZERO_MAC,
	ETH_FILTERS_VNI_ADD_FAIL_FULL,
	ETH_FILTERS_VNI_ADD_FAIL_DUP,
	ETH_FILTERS_GFT_UPDATE_FAIL,
	ETH_RX_QUEUE_FAIL_LOAD_VF_DATA,
	ETH_FILTERS_GFS_ADD_FILTER_FAIL_MAX_HOPS,
	ETH_FILTERS_GFS_ADD_FILTER_FAIL_NO_FREE_ENRTY,
	ETH_FILTERS_GFS_ADD_FILTER_FAIL_ALREADY_EXISTS,
	ETH_FILTERS_GFS_ADD_FILTER_FAIL_PCI_ERROR,
	ETH_FILTERS_GFS_ADD_FINLER_FAIL_MAGIC_NUM_ERROR,
	ETH_FILTERS_GFS_DEL_FILTER_FAIL_MAX_HOPS,
	ETH_FILTERS_GFS_DEL_FILTER_FAIL_NO_MATCH_ENRTY,
	ETH_FILTERS_GFS_DEL_FILTER_FAIL_PCI_ERROR,
	ETH_FILTERS_GFS_DEL_FILTER_FAIL_MAGIC_NUM_ERROR,
	MAX_ETH_ERROR_CODE
पूर्ण;

/* Opcodes क्रम the event ring */
क्रमागत eth_event_opcode अणु
	ETH_EVENT_UNUSED,
	ETH_EVENT_VPORT_START,
	ETH_EVENT_VPORT_UPDATE,
	ETH_EVENT_VPORT_STOP,
	ETH_EVENT_TX_QUEUE_START,
	ETH_EVENT_TX_QUEUE_STOP,
	ETH_EVENT_RX_QUEUE_START,
	ETH_EVENT_RX_QUEUE_UPDATE,
	ETH_EVENT_RX_QUEUE_STOP,
	ETH_EVENT_FILTERS_UPDATE,
	ETH_EVENT_RX_ADD_OPENFLOW_FILTER,
	ETH_EVENT_RX_DELETE_OPENFLOW_FILTER,
	ETH_EVENT_RX_CREATE_OPENFLOW_ACTION,
	ETH_EVENT_RX_ADD_UDP_FILTER,
	ETH_EVENT_RX_DELETE_UDP_FILTER,
	ETH_EVENT_RX_CREATE_GFT_ACTION,
	ETH_EVENT_RX_GFT_UPDATE_FILTER,
	ETH_EVENT_TX_QUEUE_UPDATE,
	ETH_EVENT_RGFS_ADD_FILTER,
	ETH_EVENT_RGFS_DEL_FILTER,
	ETH_EVENT_TGFS_ADD_FILTER,
	ETH_EVENT_TGFS_DEL_FILTER,
	ETH_EVENT_GFS_COUNTERS_REPORT_REQUEST,
	MAX_ETH_EVENT_OPCODE
पूर्ण;

/* Classअगरy rule types in E2/E3 */
क्रमागत eth_filter_action अणु
	ETH_FILTER_ACTION_UNUSED,
	ETH_FILTER_ACTION_REMOVE,
	ETH_FILTER_ACTION_ADD,
	ETH_FILTER_ACTION_REMOVE_ALL,
	MAX_ETH_FILTER_ACTION
पूर्ण;

/* Command क्रम adding/removing a classअगरication rule $$KEEP_ENDIANNESS$$ */
काष्ठा eth_filter_cmd अणु
	u8 type;
	u8 vport_id;
	u8 action;
	u8 reserved0;
	__le32 vni;
	__le16 mac_lsb;
	__le16 mac_mid;
	__le16 mac_msb;
	__le16 vlan_id;
पूर्ण;

/*	$$KEEP_ENDIANNESS$$ */
काष्ठा eth_filter_cmd_header अणु
	u8 rx;
	u8 tx;
	u8 cmd_cnt;
	u8 निश्चित_on_error;
	u8 reserved1[4];
पूर्ण;

/* Ethernet filter types: mac/vlan/pair */
क्रमागत eth_filter_type अणु
	ETH_FILTER_TYPE_UNUSED,
	ETH_FILTER_TYPE_MAC,
	ETH_FILTER_TYPE_VLAN,
	ETH_FILTER_TYPE_PAIR,
	ETH_FILTER_TYPE_INNER_MAC,
	ETH_FILTER_TYPE_INNER_VLAN,
	ETH_FILTER_TYPE_INNER_PAIR,
	ETH_FILTER_TYPE_INNER_MAC_VNI_PAIR,
	ETH_FILTER_TYPE_MAC_VNI_PAIR,
	ETH_FILTER_TYPE_VNI,
	MAX_ETH_FILTER_TYPE
पूर्ण;

/* inner to inner vlan priority translation configurations */
काष्ठा eth_in_to_in_pri_map_cfg अणु
	u8 inner_vlan_pri_remap_en;
	u8 reserved[7];
	u8 non_rdma_in_to_in_pri_map[8];
	u8 rdma_in_to_in_pri_map[8];
पूर्ण;

/* Eth IPv4 Fragment Type */
क्रमागत eth_ipv4_frag_type अणु
	ETH_IPV4_NOT_FRAG,
	ETH_IPV4_FIRST_FRAG,
	ETH_IPV4_NON_FIRST_FRAG,
	MAX_ETH_IPV4_FRAG_TYPE
पूर्ण;

/* eth IPv4 Fragment Type */
क्रमागत eth_ip_type अणु
	ETH_IPV4,
	ETH_IPV6,
	MAX_ETH_IP_TYPE
पूर्ण;

/* Ethernet Ramrod Command IDs */
क्रमागत eth_ramrod_cmd_id अणु
	ETH_RAMROD_UNUSED,
	ETH_RAMROD_VPORT_START,
	ETH_RAMROD_VPORT_UPDATE,
	ETH_RAMROD_VPORT_STOP,
	ETH_RAMROD_RX_QUEUE_START,
	ETH_RAMROD_RX_QUEUE_STOP,
	ETH_RAMROD_TX_QUEUE_START,
	ETH_RAMROD_TX_QUEUE_STOP,
	ETH_RAMROD_FILTERS_UPDATE,
	ETH_RAMROD_RX_QUEUE_UPDATE,
	ETH_RAMROD_RX_CREATE_OPENFLOW_ACTION,
	ETH_RAMROD_RX_ADD_OPENFLOW_FILTER,
	ETH_RAMROD_RX_DELETE_OPENFLOW_FILTER,
	ETH_RAMROD_RX_ADD_UDP_FILTER,
	ETH_RAMROD_RX_DELETE_UDP_FILTER,
	ETH_RAMROD_RX_CREATE_GFT_ACTION,
	ETH_RAMROD_GFT_UPDATE_FILTER,
	ETH_RAMROD_TX_QUEUE_UPDATE,
	ETH_RAMROD_RGFS_FILTER_ADD,
	ETH_RAMROD_RGFS_FILTER_DEL,
	ETH_RAMROD_TGFS_FILTER_ADD,
	ETH_RAMROD_TGFS_FILTER_DEL,
	ETH_RAMROD_GFS_COUNTERS_REPORT_REQUEST,
	MAX_ETH_RAMROD_CMD_ID
पूर्ण;

/* Return code from eth sp ramrods */
काष्ठा eth_वापस_code अणु
	u8 value;
#घोषणा ETH_RETURN_CODE_ERR_CODE_MASK  0x3F
#घोषणा ETH_RETURN_CODE_ERR_CODE_SHIFT 0
#घोषणा ETH_RETURN_CODE_RESERVED_MASK  0x1
#घोषणा ETH_RETURN_CODE_RESERVED_SHIFT 6
#घोषणा ETH_RETURN_CODE_RX_TX_MASK     0x1
#घोषणा ETH_RETURN_CODE_RX_TX_SHIFT    7
पूर्ण;

/* tx destination क्रमागत */
क्रमागत eth_tx_dst_mode_config_क्रमागत अणु
	ETH_TX_DST_MODE_CONFIG_DISABLE,
	ETH_TX_DST_MODE_CONFIG_FORWARD_DATA_IN_BD,
	ETH_TX_DST_MODE_CONFIG_FORWARD_DATA_IN_VPORT,
	MAX_ETH_TX_DST_MODE_CONFIG_ENUM
पूर्ण;

/* What to करो in हाल an error occurs */
क्रमागत eth_tx_err अणु
	ETH_TX_ERR_DROP,
	ETH_TX_ERR_ASSERT_MALICIOUS,
	MAX_ETH_TX_ERR
पूर्ण;

/* Array of the dअगरferent error type behaviors */
काष्ठा eth_tx_err_vals अणु
	__le16 values;
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_VLAN_MODE_MASK			0x1
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_VLAN_MODE_SHIFT			0
#घोषणा ETH_TX_ERR_VALS_PACKET_TOO_SMALL_MASK			0x1
#घोषणा ETH_TX_ERR_VALS_PACKET_TOO_SMALL_SHIFT			1
#घोषणा ETH_TX_ERR_VALS_ANTI_SPOOFING_ERR_MASK			0x1
#घोषणा ETH_TX_ERR_VALS_ANTI_SPOOFING_ERR_SHIFT			2
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_INBAND_TAGS_MASK		0x1
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_INBAND_TAGS_SHIFT		3
#घोषणा ETH_TX_ERR_VALS_VLAN_INSERTION_W_INBAND_TAG_MASK	0x1
#घोषणा ETH_TX_ERR_VALS_VLAN_INSERTION_W_INBAND_TAG_SHIFT	4
#घोषणा ETH_TX_ERR_VALS_MTU_VIOLATION_MASK			0x1
#घोषणा ETH_TX_ERR_VALS_MTU_VIOLATION_SHIFT			5
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_CONTROL_FRAME_MASK		0x1
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_CONTROL_FRAME_SHIFT		6
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_BD_FLAGS_MASK			0x1
#घोषणा ETH_TX_ERR_VALS_ILLEGAL_BD_FLAGS_SHIFT			7
#घोषणा ETH_TX_ERR_VALS_RESERVED_MASK				0xFF
#घोषणा ETH_TX_ERR_VALS_RESERVED_SHIFT				8
पूर्ण;

/* vport rss configuration data */
काष्ठा eth_vport_rss_config अणु
	__le16 capabilities;
#घोषणा ETH_VPORT_RSS_CONFIG_IPV4_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV4_CAPABILITY_SHIFT		0
#घोषणा ETH_VPORT_RSS_CONFIG_IPV6_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV6_CAPABILITY_SHIFT		1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV4_TCP_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV4_TCP_CAPABILITY_SHIFT		2
#घोषणा ETH_VPORT_RSS_CONFIG_IPV6_TCP_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV6_TCP_CAPABILITY_SHIFT		3
#घोषणा ETH_VPORT_RSS_CONFIG_IPV4_UDP_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV4_UDP_CAPABILITY_SHIFT		4
#घोषणा ETH_VPORT_RSS_CONFIG_IPV6_UDP_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_IPV6_UDP_CAPABILITY_SHIFT		5
#घोषणा ETH_VPORT_RSS_CONFIG_EN_5_TUPLE_CAPABILITY_MASK		0x1
#घोषणा ETH_VPORT_RSS_CONFIG_EN_5_TUPLE_CAPABILITY_SHIFT	6
#घोषणा ETH_VPORT_RSS_CONFIG_RESERVED0_MASK			0x1FF
#घोषणा ETH_VPORT_RSS_CONFIG_RESERVED0_SHIFT			7
	u8 rss_id;
	u8 rss_mode;
	u8 update_rss_key;
	u8 update_rss_ind_table;
	u8 update_rss_capabilities;
	u8 tbl_size;
	__le32 reserved2[2];
	__le16 indirection_table[ETH_RSS_IND_TABLE_ENTRIES_NUM];
	__le32 rss_key[ETH_RSS_KEY_SIZE_REGS];
	__le32 reserved3[2];
पूर्ण;

/* eth vport RSS mode */
क्रमागत eth_vport_rss_mode अणु
	ETH_VPORT_RSS_MODE_DISABLED,
	ETH_VPORT_RSS_MODE_REGULAR,
	MAX_ETH_VPORT_RSS_MODE
पूर्ण;

/* Command क्रम setting classअगरication flags क्रम a vport $$KEEP_ENDIANNESS$$ */
काष्ठा eth_vport_rx_mode अणु
	__le16 state;
#घोषणा ETH_VPORT_RX_MODE_UCAST_DROP_ALL_MASK		0x1
#घोषणा ETH_VPORT_RX_MODE_UCAST_DROP_ALL_SHIFT		0
#घोषणा ETH_VPORT_RX_MODE_UCAST_ACCEPT_ALL_MASK		0x1
#घोषणा ETH_VPORT_RX_MODE_UCAST_ACCEPT_ALL_SHIFT	1
#घोषणा ETH_VPORT_RX_MODE_UCAST_ACCEPT_UNMATCHED_MASK	0x1
#घोषणा ETH_VPORT_RX_MODE_UCAST_ACCEPT_UNMATCHED_SHIFT	2
#घोषणा ETH_VPORT_RX_MODE_MCAST_DROP_ALL_MASK		0x1
#घोषणा ETH_VPORT_RX_MODE_MCAST_DROP_ALL_SHIFT		3
#घोषणा ETH_VPORT_RX_MODE_MCAST_ACCEPT_ALL_MASK		0x1
#घोषणा ETH_VPORT_RX_MODE_MCAST_ACCEPT_ALL_SHIFT	4
#घोषणा ETH_VPORT_RX_MODE_BCAST_ACCEPT_ALL_MASK		0x1
#घोषणा ETH_VPORT_RX_MODE_BCAST_ACCEPT_ALL_SHIFT	5
#घोषणा ETH_VPORT_RX_MODE_ACCEPT_ANY_VNI_MASK		0x1
#घोषणा ETH_VPORT_RX_MODE_ACCEPT_ANY_VNI_SHIFT		6
#घोषणा ETH_VPORT_RX_MODE_RESERVED1_MASK		0x1FF
#घोषणा ETH_VPORT_RX_MODE_RESERVED1_SHIFT		7
पूर्ण;

/* Command क्रम setting tpa parameters */
काष्ठा eth_vport_tpa_param अणु
	u8 tpa_ipv4_en_flg;
	u8 tpa_ipv6_en_flg;
	u8 tpa_ipv4_tunn_en_flg;
	u8 tpa_ipv6_tunn_en_flg;
	u8 tpa_pkt_split_flg;
	u8 tpa_hdr_data_split_flg;
	u8 tpa_gro_consistent_flg;

	u8 tpa_max_aggs_num;

	__le16 tpa_max_size;
	__le16 tpa_min_माप_प्रकारo_start;

	__le16 tpa_min_माप_प्रकारo_cont;
	u8 max_buff_num;
	u8 reserved;
पूर्ण;

/* Command क्रम setting classअगरication flags क्रम a vport $$KEEP_ENDIANNESS$$ */
काष्ठा eth_vport_tx_mode अणु
	__le16 state;
#घोषणा ETH_VPORT_TX_MODE_UCAST_DROP_ALL_MASK		0x1
#घोषणा ETH_VPORT_TX_MODE_UCAST_DROP_ALL_SHIFT		0
#घोषणा ETH_VPORT_TX_MODE_UCAST_ACCEPT_ALL_MASK		0x1
#घोषणा ETH_VPORT_TX_MODE_UCAST_ACCEPT_ALL_SHIFT	1
#घोषणा ETH_VPORT_TX_MODE_MCAST_DROP_ALL_MASK		0x1
#घोषणा ETH_VPORT_TX_MODE_MCAST_DROP_ALL_SHIFT		2
#घोषणा ETH_VPORT_TX_MODE_MCAST_ACCEPT_ALL_MASK		0x1
#घोषणा ETH_VPORT_TX_MODE_MCAST_ACCEPT_ALL_SHIFT	3
#घोषणा ETH_VPORT_TX_MODE_BCAST_ACCEPT_ALL_MASK		0x1
#घोषणा ETH_VPORT_TX_MODE_BCAST_ACCEPT_ALL_SHIFT	4
#घोषणा ETH_VPORT_TX_MODE_RESERVED1_MASK		0x7FF
#घोषणा ETH_VPORT_TX_MODE_RESERVED1_SHIFT		5
पूर्ण;

/* GFT filter update action type */
क्रमागत gft_filter_update_action अणु
	GFT_ADD_FILTER,
	GFT_DELETE_FILTER,
	MAX_GFT_FILTER_UPDATE_ACTION
पूर्ण;

/* Ramrod data क्रम rx add खोलोflow filter */
काष्ठा rx_add_खोलोflow_filter_data अणु
	__le16 action_icid;
	u8 priority;
	u8 reserved0;
	__le32 tenant_id;
	__le16 dst_mac_hi;
	__le16 dst_mac_mid;
	__le16 dst_mac_lo;
	__le16 src_mac_hi;
	__le16 src_mac_mid;
	__le16 src_mac_lo;
	__le16 vlan_id;
	__le16 l2_eth_type;
	u8 ipv4_dscp;
	u8 ipv4_frag_type;
	u8 ipv4_over_ip;
	u8 tenant_id_exists;
	__le32 ipv4_dst_addr;
	__le32 ipv4_src_addr;
	__le16 l4_dst_port;
	__le16 l4_src_port;
पूर्ण;

/* Ramrod data क्रम rx create gft action */
काष्ठा rx_create_gft_action_data अणु
	u8 vport_id;
	u8 reserved[7];
पूर्ण;

/* Ramrod data क्रम rx create खोलोflow action */
काष्ठा rx_create_खोलोflow_action_data अणु
	u8 vport_id;
	u8 reserved[7];
पूर्ण;

/* Ramrod data क्रम rx queue start ramrod */
काष्ठा rx_queue_start_ramrod_data अणु
	__le16 rx_queue_id;
	__le16 num_of_pbl_pages;
	__le16 bd_max_bytes;
	__le16 sb_id;
	u8 sb_index;
	u8 vport_id;
	u8 शेष_rss_queue_flg;
	u8 complete_cqe_flg;
	u8 complete_event_flg;
	u8 stats_counter_id;
	u8 pin_context;
	u8 pxp_tph_valid_bd;
	u8 pxp_tph_valid_pkt;
	u8 pxp_st_hपूर्णांक;

	__le16 pxp_st_index;
	u8 pmd_mode;

	u8 notअगरy_en;
	u8 toggle_val;

	u8 vf_rx_prod_index;
	u8 vf_rx_prod_use_zone_a;
	u8 reserved[5];
	__le16 reserved1;
	काष्ठा regpair cqe_pbl_addr;
	काष्ठा regpair bd_base;
	काष्ठा regpair reserved2;
पूर्ण;

/* Ramrod data क्रम rx queue stop ramrod */
काष्ठा rx_queue_stop_ramrod_data अणु
	__le16 rx_queue_id;
	u8 complete_cqe_flg;
	u8 complete_event_flg;
	u8 vport_id;
	u8 reserved[3];
पूर्ण;

/* Ramrod data क्रम rx queue update ramrod */
काष्ठा rx_queue_update_ramrod_data अणु
	__le16 rx_queue_id;
	u8 complete_cqe_flg;
	u8 complete_event_flg;
	u8 vport_id;
	u8 set_शेष_rss_queue;
	u8 reserved[3];
	u8 reserved1;
	u8 reserved2;
	u8 reserved3;
	__le16 reserved4;
	__le16 reserved5;
	काष्ठा regpair reserved6;
पूर्ण;

/* Ramrod data क्रम rx Add UDP Filter */
काष्ठा rx_udp_filter_data अणु
	__le16 action_icid;
	__le16 vlan_id;
	u8 ip_type;
	u8 tenant_id_exists;
	__le16 reserved1;
	__le32 ip_dst_addr[4];
	__le32 ip_src_addr[4];
	__le16 udp_dst_port;
	__le16 udp_src_port;
	__le32 tenant_id;
पूर्ण;

/* Add or delete GFT filter - filter is packet header of type of packet wished
 * to pass certain FW flow.
 */
काष्ठा rx_update_gft_filter_data अणु
	काष्ठा regpair pkt_hdr_addr;
	__le16 pkt_hdr_length;
	__le16 action_icid;
	__le16 rx_qid;
	__le16 flow_id;
	__le16 vport_id;
	u8 action_icid_valid;
	u8 rx_qid_valid;
	u8 flow_id_valid;
	u8 filter_action;
	u8 निश्चित_on_error;
	u8 inner_vlan_removal_en;
पूर्ण;

/* Ramrod data क्रम tx queue start ramrod */
काष्ठा tx_queue_start_ramrod_data अणु
	__le16 sb_id;
	u8 sb_index;
	u8 vport_id;
	u8 reserved0;
	u8 stats_counter_id;
	__le16 qm_pq_id;
	u8 flags;
#घोषणा TX_QUEUE_START_RAMROD_DATA_DISABLE_OPPORTUNISTIC_MASK	0x1
#घोषणा TX_QUEUE_START_RAMROD_DATA_DISABLE_OPPORTUNISTIC_SHIFT	0
#घोषणा TX_QUEUE_START_RAMROD_DATA_TEST_MODE_PKT_DUP_MASK	0x1
#घोषणा TX_QUEUE_START_RAMROD_DATA_TEST_MODE_PKT_DUP_SHIFT	1
#घोषणा TX_QUEUE_START_RAMROD_DATA_PMD_MODE_MASK		0x1
#घोषणा TX_QUEUE_START_RAMROD_DATA_PMD_MODE_SHIFT		2
#घोषणा TX_QUEUE_START_RAMROD_DATA_NOTIFY_EN_MASK		0x1
#घोषणा TX_QUEUE_START_RAMROD_DATA_NOTIFY_EN_SHIFT		3
#घोषणा TX_QUEUE_START_RAMROD_DATA_PIN_CONTEXT_MASK		0x1
#घोषणा TX_QUEUE_START_RAMROD_DATA_PIN_CONTEXT_SHIFT		4
#घोषणा TX_QUEUE_START_RAMROD_DATA_RESERVED1_MASK		0x7
#घोषणा TX_QUEUE_START_RAMROD_DATA_RESERVED1_SHIFT		5
	u8 pxp_st_hपूर्णांक;
	u8 pxp_tph_valid_bd;
	u8 pxp_tph_valid_pkt;
	__le16 pxp_st_index;
	__le16 comp_agg_size;
	__le16 queue_zone_id;
	__le16 reserved2;
	__le16 pbl_size;
	__le16 tx_queue_id;
	__le16 same_as_last_id;
	__le16 reserved[3];
	काष्ठा regpair pbl_base_addr;
	काष्ठा regpair bd_cons_address;
पूर्ण;

/* Ramrod data क्रम tx queue stop ramrod */
काष्ठा tx_queue_stop_ramrod_data अणु
	__le16 reserved[4];
पूर्ण;

/* Ramrod data क्रम tx queue update ramrod */
काष्ठा tx_queue_update_ramrod_data अणु
	__le16 update_qm_pq_id_flg;
	__le16 qm_pq_id;
	__le32 reserved0;
	काष्ठा regpair reserved1[5];
पूर्ण;

/* Inner to Inner VLAN priority map update mode */
क्रमागत update_in_to_in_pri_map_mode_क्रमागत अणु
	ETH_IN_TO_IN_PRI_MAP_UPDATE_DISABLED,
	ETH_IN_TO_IN_PRI_MAP_UPDATE_NON_RDMA_TBL,
	ETH_IN_TO_IN_PRI_MAP_UPDATE_RDMA_TBL,
	MAX_UPDATE_IN_TO_IN_PRI_MAP_MODE_ENUM
पूर्ण;

/* Ramrod data क्रम vport update ramrod */
काष्ठा vport_filter_update_ramrod_data अणु
	काष्ठा eth_filter_cmd_header filter_cmd_hdr;
	काष्ठा eth_filter_cmd filter_cmds[ETH_FILTER_RULES_COUNT];
पूर्ण;

/* Ramrod data क्रम vport start ramrod */
काष्ठा vport_start_ramrod_data अणु
	u8 vport_id;
	u8 sw_fid;
	__le16 mtu;
	u8 drop_ttl0_en;
	u8 inner_vlan_removal_en;
	काष्ठा eth_vport_rx_mode rx_mode;
	काष्ठा eth_vport_tx_mode tx_mode;
	काष्ठा eth_vport_tpa_param tpa_param;
	__le16 शेष_vlan;
	u8 tx_चयनing_en;
	u8 anti_spoofing_en;
	u8 शेष_vlan_en;
	u8 handle_ptp_pkts;
	u8 silent_vlan_removal_en;
	u8 untagged;
	काष्ठा eth_tx_err_vals tx_err_behav;
	u8 zero_placement_offset;
	u8 ctl_frame_mac_check_en;
	u8 ctl_frame_ethtype_check_en;
	u8 reserved0;
	u8 reserved1;
	u8 tx_dst_port_mode_config;
	u8 dst_vport_id;
	u8 tx_dst_port_mode;
	u8 dst_vport_id_valid;
	u8 wipe_inner_vlan_pri_en;
	u8 reserved2[2];
	काष्ठा eth_in_to_in_pri_map_cfg in_to_in_vlan_pri_map_cfg;
पूर्ण;

/* Ramrod data क्रम vport stop ramrod */
काष्ठा vport_stop_ramrod_data अणु
	u8 vport_id;
	u8 reserved[7];
पूर्ण;

/* Ramrod data क्रम vport update ramrod */
काष्ठा vport_update_ramrod_data_cmn अणु
	u8 vport_id;
	u8 update_rx_active_flg;
	u8 rx_active_flg;
	u8 update_tx_active_flg;
	u8 tx_active_flg;
	u8 update_rx_mode_flg;
	u8 update_tx_mode_flg;
	u8 update_approx_mcast_flg;

	u8 update_rss_flg;
	u8 update_inner_vlan_removal_en_flg;

	u8 inner_vlan_removal_en;
	u8 update_tpa_param_flg;
	u8 update_tpa_en_flg;
	u8 update_tx_चयनing_en_flg;

	u8 tx_चयनing_en;
	u8 update_anti_spoofing_en_flg;

	u8 anti_spoofing_en;
	u8 update_handle_ptp_pkts;

	u8 handle_ptp_pkts;
	u8 update_शेष_vlan_en_flg;

	u8 शेष_vlan_en;

	u8 update_शेष_vlan_flg;

	__le16 शेष_vlan;
	u8 update_accept_any_vlan_flg;

	u8 accept_any_vlan;
	u8 silent_vlan_removal_en;
	u8 update_mtu_flg;

	__le16 mtu;
	u8 update_ctl_frame_checks_en_flg;
	u8 ctl_frame_mac_check_en;
	u8 ctl_frame_ethtype_check_en;
	u8 update_in_to_in_pri_map_mode;
	u8 in_to_in_pri_map[8];
	u8 reserved[6];
पूर्ण;

काष्ठा vport_update_ramrod_mcast अणु
	__le32 bins[ETH_MULTICAST_MAC_BINS_IN_REGS];
पूर्ण;

/* Ramrod data क्रम vport update ramrod */
काष्ठा vport_update_ramrod_data अणु
	काष्ठा vport_update_ramrod_data_cmn common;

	काष्ठा eth_vport_rx_mode rx_mode;
	काष्ठा eth_vport_tx_mode tx_mode;
	__le32 reserved[3];
	काष्ठा eth_vport_tpa_param tpa_param;
	काष्ठा vport_update_ramrod_mcast approx_mcast;
	काष्ठा eth_vport_rss_config rss_config;
पूर्ण;

काष्ठा e4_xstorm_eth_conn_ag_ctx_dq_ext_ldpart अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EXIST_IN_QM0_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EXIST_IN_QM0_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED1_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED1_SHIFT		1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED2_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED2_SHIFT		2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EXIST_IN_QM3_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EXIST_IN_QM3_SHIFT	3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED3_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED3_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED4_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED4_SHIFT		5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED5_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED5_SHIFT		6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED6_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED6_SHIFT		7
	u8 flags1;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED7_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED7_SHIFT		0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED8_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED8_SHIFT		1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED9_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED9_SHIFT		2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_BIT11_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_BIT11_SHIFT		3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_E5_RESERVED2_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_E5_RESERVED2_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_E5_RESERVED3_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_E5_RESERVED3_SHIFT	5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TX_RULE_ACTIVE_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TX_RULE_ACTIVE_SHIFT	6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_DQ_CF_ACTIVE_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_DQ_CF_ACTIVE_SHIFT	7
	u8 flags2;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF0_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF0_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF1_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF1_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF2_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF2_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF3_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF4_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF4_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF5_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF5_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF6_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF6_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF7_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF7_SHIFT	6
	u8 flags4;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF8_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF8_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF9_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF9_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF10_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF10_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF11_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF12_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF12_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF13_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF13_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF14_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF14_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF15_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_GO_TO_BD_CONS_CF_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_GO_TO_BD_CONS_CF_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_MULTI_UNICAST_CF_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_MULTI_UNICAST_CF_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_DQ_CF_MASK		0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_DQ_CF_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TERMINATE_CF_MASK	0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TERMINATE_CF_SHIFT	6
	u8 flags7;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_FLUSH_Q0_MASK		0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_FLUSH_Q0_SHIFT		0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED10_MASK		0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED10_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_SLOW_PATH_MASK		0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_SLOW_PATH_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF0EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF0EN_SHIFT		6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF1EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF1EN_SHIFT		7
	u8 flags8;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF2EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF2EN_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF3EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF3EN_SHIFT	1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF4EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF4EN_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF5EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF5EN_SHIFT	3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF6EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF6EN_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF7EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF7EN_SHIFT	5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF8EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF8EN_SHIFT	6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF9EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF9EN_SHIFT	7
	u8 flags9;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF10EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF10EN_SHIFT			0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF11EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF11EN_SHIFT			1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF12EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF12EN_SHIFT			2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF13EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF13EN_SHIFT			3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF14EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF14EN_SHIFT			4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF15EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_CF15EN_SHIFT			5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_GO_TO_BD_CONS_CF_EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_GO_TO_BD_CONS_CF_EN_SHIFT	6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_MULTI_UNICAST_CF_EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_MULTI_UNICAST_CF_EN_SHIFT	7
	u8 flags10;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_DQ_CF_EN_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_DQ_CF_EN_SHIFT			0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TERMINATE_CF_EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TERMINATE_CF_EN_SHIFT		1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_FLUSH_Q0_EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_FLUSH_Q0_EN_SHIFT		2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED11_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED11_SHIFT		3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_SLOW_PATH_EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_SLOW_PATH_EN_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TPH_ENABLE_EN_RESERVED_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TPH_ENABLE_EN_RESERVED_SHIFT	5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED12_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED12_SHIFT		6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED13_MASK			0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED13_SHIFT		7
	u8 flags11;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED14_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED14_SHIFT	0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED15_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RESERVED15_SHIFT	1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TX_DEC_RULE_EN_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TX_DEC_RULE_EN_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE5EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE5EN_SHIFT		3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE6EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE6EN_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE7EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE7EN_SHIFT		5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED1_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED1_SHIFT	6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE9EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE9EN_SHIFT		7
	u8 flags12;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE10EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE10EN_SHIFT		0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE11EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE11EN_SHIFT		1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED2_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED2_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED3_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED3_SHIFT	3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE14EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE14EN_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE15EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE15EN_SHIFT		5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE16EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE16EN_SHIFT		6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE17EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE17EN_SHIFT		7
	u8 flags13;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE18EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE18EN_SHIFT		0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE19EN_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_RULE19EN_SHIFT		1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED4_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED4_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED5_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED5_SHIFT	3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED6_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED6_SHIFT	4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED7_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED7_SHIFT	5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED8_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED8_SHIFT	6
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED9_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_USE_EXT_HDR_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_USE_EXT_HDR_SHIFT		0
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_SEND_RAW_L3L4_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_SEND_RAW_L3L4_SHIFT	1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_INBAND_PROP_HDR_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_INBAND_PROP_HDR_SHIFT	2
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_SEND_EXT_TUNNEL_MASK	0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_EDPM_SEND_EXT_TUNNEL_SHIFT	3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_L2_EDPM_ENABLE_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_L2_EDPM_ENABLE_SHIFT		4
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_ROCE_EDPM_ENABLE_MASK		0x1
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_ROCE_EDPM_ENABLE_SHIFT		5
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TPH_ENABLE_MASK			0x3
#घोषणा E4XSTORMETHCONNAGCTXDQEXTLDPART_TPH_ENABLE_SHIFT		6
	u8 edpm_event_id;
	__le16 physical_q0;
	__le16 e5_reserved1;
	__le16 edpm_num_bds;
	__le16 tx_bd_cons;
	__le16 tx_bd_prod;
	__le16 updated_qm_pq_id;
	__le16 conn_dpi;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
पूर्ण;

काष्ठा e4_mstorm_eth_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	 0
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_BIT1_SHIFT		1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF0_SHIFT		2
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF1_SHIFT		4
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF2_SHIFT		6
	u8 flags1;
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_MSTORM_ETH_CONN_AG_CTX_RULE4EN_SHIFT	7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_xstorm_eth_hw_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED1_SHIFT	1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED3_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED4_SHIFT	5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED5_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED6_SHIFT	7
	u8 flags1;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED7_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED7_SHIFT		0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED8_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED8_SHIFT		1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED9_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED9_SHIFT		2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_BIT11_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_E5_RESERVED2_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_E5_RESERVED2_SHIFT		4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_E5_RESERVED3_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_E5_RESERVED3_SHIFT		5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TX_RULE_ACTIVE_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TX_RULE_ACTIVE_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_DQ_CF_ACTIVE_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_DQ_CF_ACTIVE_SHIFT		7
	u8 flags2;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF0_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF1_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF2_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF4_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF5_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF6_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF7_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF12_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF12_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF13_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF13_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF14_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF14_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF15_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_GO_TO_BD_CONS_CF_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_GO_TO_BD_CONS_CF_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_MULTI_UNICAST_CF_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_MULTI_UNICAST_CF_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_DQ_CF_MASK			0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_DQ_CF_SHIFT		4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TERMINATE_CF_MASK		0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TERMINATE_CF_SHIFT		6
	u8 flags7;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_FLUSH_Q0_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_FLUSH_Q0_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED10_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED10_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF0EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF1EN_SHIFT	7
	u8 flags8;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF2EN_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF3EN_SHIFT	1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF4EN_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF5EN_SHIFT	3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF6EN_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF7EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF7EN_SHIFT	5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF8EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF8EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF9EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF9EN_SHIFT	7
	u8 flags9;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF10EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF10EN_SHIFT		0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF11EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF11EN_SHIFT		1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF12EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF12EN_SHIFT		2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF13EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF13EN_SHIFT		3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF14EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF14EN_SHIFT		4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF15EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_CF15EN_SHIFT		5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_GO_TO_BD_CONS_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_GO_TO_BD_CONS_CF_EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_MULTI_UNICAST_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_MULTI_UNICAST_CF_EN_SHIFT	7
	u8 flags10;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_DQ_CF_EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_DQ_CF_EN_SHIFT			0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TERMINATE_CF_EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TERMINATE_CF_EN_SHIFT		1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_FLUSH_Q0_EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_FLUSH_Q0_EN_SHIFT			2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED11_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED11_SHIFT			3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_SLOW_PATH_EN_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_SLOW_PATH_EN_SHIFT			4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TPH_ENABLE_EN_RESERVED_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TPH_ENABLE_EN_RESERVED_SHIFT	5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED12_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED12_SHIFT			6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED13_MASK			0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED13_SHIFT			7
	u8 flags11;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED14_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED14_SHIFT		0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED15_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RESERVED15_SHIFT		1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TX_DEC_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TX_DEC_RULE_EN_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE5EN_SHIFT		3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE6EN_SHIFT		4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE7EN_SHIFT		5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED1_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED1_SHIFT		6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE9EN_MASK		0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE9EN_SHIFT		7
	u8 flags12;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE10EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE10EN_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE11EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE11EN_SHIFT	1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED3_SHIFT	3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE14EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE14EN_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE15EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE15EN_SHIFT	5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE16EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE16EN_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE17EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE17EN_SHIFT	7
	u8 flags13;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE18EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE18EN_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE19EN_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_RULE19EN_SHIFT	1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED4_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED5_SHIFT	3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED6_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED7_SHIFT	5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED8_SHIFT	6
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_USE_EXT_HDR_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_USE_EXT_HDR_SHIFT	0
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_SEND_RAW_L3L4_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_SEND_RAW_L3L4_SHIFT	1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_INBAND_PROP_HDR_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_INBAND_PROP_HDR_SHIFT	2
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_SEND_EXT_TUNNEL_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_EDPM_SEND_EXT_TUNNEL_SHIFT	3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_L2_EDPM_ENABLE_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_L2_EDPM_ENABLE_SHIFT	4
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_ROCE_EDPM_ENABLE_MASK	0x1
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_ROCE_EDPM_ENABLE_SHIFT	5
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TPH_ENABLE_MASK		0x3
#घोषणा E4_XSTORM_ETH_HW_CONN_AG_CTX_TPH_ENABLE_SHIFT		6
	u8 edpm_event_id;
	__le16 physical_q0;
	__le16 e5_reserved1;
	__le16 edpm_num_bds;
	__le16 tx_bd_cons;
	__le16 tx_bd_prod;
	__le16 updated_qm_pq_id;
	__le16 conn_dpi;
पूर्ण;

/* GFT CAM line काष्ठा with fields अवरोधout */
काष्ठा gft_cam_line_mapped अणु
	__le32 camline;
#घोषणा GFT_CAM_LINE_MAPPED_VALID_MASK				0x1
#घोषणा GFT_CAM_LINE_MAPPED_VALID_SHIFT				0
#घोषणा GFT_CAM_LINE_MAPPED_IP_VERSION_MASK			0x1
#घोषणा GFT_CAM_LINE_MAPPED_IP_VERSION_SHIFT			1
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_IP_VERSION_MASK		0x1
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_IP_VERSION_SHIFT		2
#घोषणा GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK		0xF
#घोषणा GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_SHIFT		3
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_TYPE_MASK			0xF
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_TYPE_SHIFT			7
#घोषणा GFT_CAM_LINE_MAPPED_PF_ID_MASK				0xF
#घोषणा GFT_CAM_LINE_MAPPED_PF_ID_SHIFT				11
#घोषणा GFT_CAM_LINE_MAPPED_IP_VERSION_MASK_MASK		0x1
#घोषणा GFT_CAM_LINE_MAPPED_IP_VERSION_MASK_SHIFT		15
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_IP_VERSION_MASK_MASK		0x1
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_IP_VERSION_MASK_SHIFT	16
#घोषणा GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK_MASK	0xF
#घोषणा GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK_SHIFT	17
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_TYPE_MASK_MASK		0xF
#घोषणा GFT_CAM_LINE_MAPPED_TUNNEL_TYPE_MASK_SHIFT		21
#घोषणा GFT_CAM_LINE_MAPPED_PF_ID_MASK_MASK			0xF
#घोषणा GFT_CAM_LINE_MAPPED_PF_ID_MASK_SHIFT			25
#घोषणा GFT_CAM_LINE_MAPPED_RESERVED1_MASK			0x7
#घोषणा GFT_CAM_LINE_MAPPED_RESERVED1_SHIFT			29
पूर्ण;


/* Used in gft_profile_key: Indication क्रम ip version */
क्रमागत gft_profile_ip_version अणु
	GFT_PROखाता_IPV4 = 0,
	GFT_PROखाता_IPV6 = 1,
	MAX_GFT_PROखाता_IP_VERSION
पूर्ण;

/* Profile key stucr fot GFT logic in Prs */
काष्ठा gft_profile_key अणु
	__le16 profile_key;
#घोषणा GFT_PROखाता_KEY_IP_VERSION_MASK			0x1
#घोषणा GFT_PROखाता_KEY_IP_VERSION_SHIFT		0
#घोषणा GFT_PROखाता_KEY_TUNNEL_IP_VERSION_MASK		0x1
#घोषणा GFT_PROखाता_KEY_TUNNEL_IP_VERSION_SHIFT		1
#घोषणा GFT_PROखाता_KEY_UPPER_PROTOCOL_TYPE_MASK	0xF
#घोषणा GFT_PROखाता_KEY_UPPER_PROTOCOL_TYPE_SHIFT	2
#घोषणा GFT_PROखाता_KEY_TUNNEL_TYPE_MASK		0xF
#घोषणा GFT_PROखाता_KEY_TUNNEL_TYPE_SHIFT		6
#घोषणा GFT_PROखाता_KEY_PF_ID_MASK			0xF
#घोषणा GFT_PROखाता_KEY_PF_ID_SHIFT			10
#घोषणा GFT_PROखाता_KEY_RESERVED0_MASK			0x3
#घोषणा GFT_PROखाता_KEY_RESERVED0_SHIFT			14
पूर्ण;

/* Used in gft_profile_key: Indication क्रम tunnel type */
क्रमागत gft_profile_tunnel_type अणु
	GFT_PROखाता_NO_TUNNEL = 0,
	GFT_PROखाता_VXLAN_TUNNEL = 1,
	GFT_PROखाता_GRE_MAC_OR_NVGRE_TUNNEL = 2,
	GFT_PROखाता_GRE_IP_TUNNEL = 3,
	GFT_PROखाता_GENEVE_MAC_TUNNEL = 4,
	GFT_PROखाता_GENEVE_IP_TUNNEL = 5,
	MAX_GFT_PROखाता_TUNNEL_TYPE
पूर्ण;

/* Used in gft_profile_key: Indication क्रम protocol type */
क्रमागत gft_profile_upper_protocol_type अणु
	GFT_PROखाता_ROCE_PROTOCOL = 0,
	GFT_PROखाता_RROCE_PROTOCOL = 1,
	GFT_PROखाता_FCOE_PROTOCOL = 2,
	GFT_PROखाता_ICMP_PROTOCOL = 3,
	GFT_PROखाता_ARP_PROTOCOL = 4,
	GFT_PROखाता_USER_TCP_SRC_PORT_1_INNER = 5,
	GFT_PROखाता_USER_TCP_DST_PORT_1_INNER = 6,
	GFT_PROखाता_TCP_PROTOCOL = 7,
	GFT_PROखाता_USER_UDP_DST_PORT_1_INNER = 8,
	GFT_PROखाता_USER_UDP_DST_PORT_2_OUTER = 9,
	GFT_PROखाता_UDP_PROTOCOL = 10,
	GFT_PROखाता_USER_IP_1_INNER = 11,
	GFT_PROखाता_USER_IP_2_OUTER = 12,
	GFT_PROखाता_USER_ETH_1_INNER = 13,
	GFT_PROखाता_USER_ETH_2_OUTER = 14,
	GFT_PROखाता_RAW = 15,
	MAX_GFT_PROखाता_UPPER_PROTOCOL_TYPE
पूर्ण;

/* GFT RAM line काष्ठा */
काष्ठा gft_ram_line अणु
	__le32 lo;
#घोषणा GFT_RAM_LINE_VLAN_SELECT_MASK			0x3
#घोषणा GFT_RAM_LINE_VLAN_SELECT_SHIFT			0
#घोषणा GFT_RAM_LINE_TUNNEL_ENTROPHY_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_ENTROPHY_SHIFT		2
#घोषणा GFT_RAM_LINE_TUNNEL_TTL_EQUAL_ONE_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_TTL_EQUAL_ONE_SHIFT		3
#घोषणा GFT_RAM_LINE_TUNNEL_TTL_MASK			0x1
#घोषणा GFT_RAM_LINE_TUNNEL_TTL_SHIFT			4
#घोषणा GFT_RAM_LINE_TUNNEL_ETHERTYPE_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_ETHERTYPE_SHIFT		5
#घोषणा GFT_RAM_LINE_TUNNEL_DST_PORT_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_DST_PORT_SHIFT		6
#घोषणा GFT_RAM_LINE_TUNNEL_SRC_PORT_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_SRC_PORT_SHIFT		7
#घोषणा GFT_RAM_LINE_TUNNEL_DSCP_MASK			0x1
#घोषणा GFT_RAM_LINE_TUNNEL_DSCP_SHIFT			8
#घोषणा GFT_RAM_LINE_TUNNEL_OVER_IP_PROTOCOL_MASK	0x1
#घोषणा GFT_RAM_LINE_TUNNEL_OVER_IP_PROTOCOL_SHIFT	9
#घोषणा GFT_RAM_LINE_TUNNEL_DST_IP_MASK			0x1
#घोषणा GFT_RAM_LINE_TUNNEL_DST_IP_SHIFT		10
#घोषणा GFT_RAM_LINE_TUNNEL_SRC_IP_MASK			0x1
#घोषणा GFT_RAM_LINE_TUNNEL_SRC_IP_SHIFT		11
#घोषणा GFT_RAM_LINE_TUNNEL_PRIORITY_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_PRIORITY_SHIFT		12
#घोषणा GFT_RAM_LINE_TUNNEL_PROVIDER_VLAN_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_PROVIDER_VLAN_SHIFT		13
#घोषणा GFT_RAM_LINE_TUNNEL_VLAN_MASK			0x1
#घोषणा GFT_RAM_LINE_TUNNEL_VLAN_SHIFT			14
#घोषणा GFT_RAM_LINE_TUNNEL_DST_MAC_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_DST_MAC_SHIFT		15
#घोषणा GFT_RAM_LINE_TUNNEL_SRC_MAC_MASK		0x1
#घोषणा GFT_RAM_LINE_TUNNEL_SRC_MAC_SHIFT		16
#घोषणा GFT_RAM_LINE_TTL_EQUAL_ONE_MASK			0x1
#घोषणा GFT_RAM_LINE_TTL_EQUAL_ONE_SHIFT		17
#घोषणा GFT_RAM_LINE_TTL_MASK				0x1
#घोषणा GFT_RAM_LINE_TTL_SHIFT				18
#घोषणा GFT_RAM_LINE_ETHERTYPE_MASK			0x1
#घोषणा GFT_RAM_LINE_ETHERTYPE_SHIFT			19
#घोषणा GFT_RAM_LINE_RESERVED0_MASK			0x1
#घोषणा GFT_RAM_LINE_RESERVED0_SHIFT			20
#घोषणा GFT_RAM_LINE_TCP_FLAG_FIN_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_FIN_SHIFT			21
#घोषणा GFT_RAM_LINE_TCP_FLAG_SYN_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_SYN_SHIFT			22
#घोषणा GFT_RAM_LINE_TCP_FLAG_RST_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_RST_SHIFT			23
#घोषणा GFT_RAM_LINE_TCP_FLAG_PSH_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_PSH_SHIFT			24
#घोषणा GFT_RAM_LINE_TCP_FLAG_ACK_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_ACK_SHIFT			25
#घोषणा GFT_RAM_LINE_TCP_FLAG_URG_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_URG_SHIFT			26
#घोषणा GFT_RAM_LINE_TCP_FLAG_ECE_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_ECE_SHIFT			27
#घोषणा GFT_RAM_LINE_TCP_FLAG_CWR_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_CWR_SHIFT			28
#घोषणा GFT_RAM_LINE_TCP_FLAG_NS_MASK			0x1
#घोषणा GFT_RAM_LINE_TCP_FLAG_NS_SHIFT			29
#घोषणा GFT_RAM_LINE_DST_PORT_MASK			0x1
#घोषणा GFT_RAM_LINE_DST_PORT_SHIFT			30
#घोषणा GFT_RAM_LINE_SRC_PORT_MASK			0x1
#घोषणा GFT_RAM_LINE_SRC_PORT_SHIFT			31
	__le32 hi;
#घोषणा GFT_RAM_LINE_DSCP_MASK				0x1
#घोषणा GFT_RAM_LINE_DSCP_SHIFT				0
#घोषणा GFT_RAM_LINE_OVER_IP_PROTOCOL_MASK		0x1
#घोषणा GFT_RAM_LINE_OVER_IP_PROTOCOL_SHIFT		1
#घोषणा GFT_RAM_LINE_DST_IP_MASK			0x1
#घोषणा GFT_RAM_LINE_DST_IP_SHIFT			2
#घोषणा GFT_RAM_LINE_SRC_IP_MASK			0x1
#घोषणा GFT_RAM_LINE_SRC_IP_SHIFT			3
#घोषणा GFT_RAM_LINE_PRIORITY_MASK			0x1
#घोषणा GFT_RAM_LINE_PRIORITY_SHIFT			4
#घोषणा GFT_RAM_LINE_PROVIDER_VLAN_MASK			0x1
#घोषणा GFT_RAM_LINE_PROVIDER_VLAN_SHIFT		5
#घोषणा GFT_RAM_LINE_VLAN_MASK				0x1
#घोषणा GFT_RAM_LINE_VLAN_SHIFT				6
#घोषणा GFT_RAM_LINE_DST_MAC_MASK			0x1
#घोषणा GFT_RAM_LINE_DST_MAC_SHIFT			7
#घोषणा GFT_RAM_LINE_SRC_MAC_MASK			0x1
#घोषणा GFT_RAM_LINE_SRC_MAC_SHIFT			8
#घोषणा GFT_RAM_LINE_TEन_अंकT_ID_MASK			0x1
#घोषणा GFT_RAM_LINE_TEन_अंकT_ID_SHIFT			9
#घोषणा GFT_RAM_LINE_RESERVED1_MASK			0x3FFFFF
#घोषणा GFT_RAM_LINE_RESERVED1_SHIFT			10
पूर्ण;

/* Used in the first 2 bits क्रम gft_ram_line: Indication क्रम vlan mask */
क्रमागत gft_vlan_select अणु
	INNER_PROVIDER_VLAN = 0,
	INNER_VLAN = 1,
	OUTER_PROVIDER_VLAN = 2,
	OUTER_VLAN = 3,
	MAX_GFT_VLAN_SELECT
पूर्ण;

/* The rdma task context of Mstorm */
काष्ठा ystorm_rdma_task_st_ctx अणु
	काष्ठा regpair temp[4];
पूर्ण;

काष्ठा e4_ystorm_rdma_task_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	__le16 msem_ctx_upd_seq;
	u8 flags0;
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_BIT1_SHIFT			5
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_VALID_MASK			0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_VALID_SHIFT			6
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_DIF_FIRST_IO_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_DIF_FIRST_IO_SHIFT		7
	u8 flags1;
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF0_MASK		0x3
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF0_SHIFT		0
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF1_MASK		0x3
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF1_SHIFT		2
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF2SPECIAL_MASK	0x3
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF2SPECIAL_SHIFT	4
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF0EN_SHIFT		6
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_CF1EN_SHIFT		7
	u8 flags2;
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_BIT4_SHIFT		0
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE0EN_SHIFT	1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE1EN_SHIFT	2
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE2EN_SHIFT	3
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE3EN_SHIFT	4
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE4EN_SHIFT	5
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE5EN_SHIFT	6
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_YSTORM_RDMA_TASK_AG_CTX_RULE6EN_SHIFT	7
	u8 key;
	__le32 mw_cnt_or_qp_id;
	u8 ref_cnt_seq;
	u8 ctx_upd_seq;
	__le16 dअगर_flags;
	__le16 tx_ref_count;
	__le16 last_used_ltid;
	__le16 parent_mr_lo;
	__le16 parent_mr_hi;
	__le32 fbo_lo;
	__le32 fbo_hi;
पूर्ण;

काष्ठा e4_mstorm_rdma_task_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	__le16 icid;
	u8 flags0;
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_BIT1_SHIFT			5
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_BIT2_MASK			0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_BIT2_SHIFT			6
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_DIF_FIRST_IO_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_DIF_FIRST_IO_SHIFT		7
	u8 flags1;
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF0_MASK	0x3
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF0_SHIFT	0
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF1_MASK	0x3
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF1_SHIFT	2
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF2_MASK	0x3
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF2_SHIFT	4
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF0EN_SHIFT	6
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF1EN_SHIFT	7
	u8 flags2;
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_CF2EN_SHIFT		0
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE0EN_SHIFT	1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE1EN_SHIFT	2
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE2EN_SHIFT	3
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE3EN_SHIFT	4
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE4EN_SHIFT	5
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE5EN_SHIFT	6
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_MSTORM_RDMA_TASK_AG_CTX_RULE6EN_SHIFT	7
	u8 key;
	__le32 mw_cnt_or_qp_id;
	u8 ref_cnt_seq;
	u8 ctx_upd_seq;
	__le16 dअगर_flags;
	__le16 tx_ref_count;
	__le16 last_used_ltid;
	__le16 parent_mr_lo;
	__le16 parent_mr_hi;
	__le32 fbo_lo;
	__le32 fbo_hi;
पूर्ण;

/* The roce task context of Mstorm */
काष्ठा mstorm_rdma_task_st_ctx अणु
	काष्ठा regpair temp[4];
पूर्ण;

/* The roce task context of Ustorm */
काष्ठा ustorm_rdma_task_st_ctx अणु
	काष्ठा regpair temp[6];
पूर्ण;

काष्ठा e4_ustorm_rdma_task_ag_ctx अणु
	u8 reserved;
	u8 state;
	__le16 icid;
	u8 flags0;
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_BIT1_SHIFT			5
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_WRITE_RESULT_CF_MASK	0x3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_WRITE_RESULT_CF_SHIFT	6
	u8 flags1;
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_RESULT_TOGGLE_BIT_MASK	0x3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_RESULT_TOGGLE_BIT_SHIFT	0
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_TX_IO_FLG_MASK		0x3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_TX_IO_FLG_SHIFT		2
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_BLOCK_SIZE_MASK          0x3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_BLOCK_SIZE_SHIFT         4
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_ERROR_CF_MASK		0x3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_ERROR_CF_SHIFT		6
	u8 flags2;
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_WRITE_RESULT_CF_EN_MASK	0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_WRITE_RESULT_CF_EN_SHIFT	0
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RESERVED2_MASK		0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RESERVED2_SHIFT		1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RESERVED3_MASK		0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RESERVED3_SHIFT		2
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RESERVED4_MASK               0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RESERVED4_SHIFT              3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_ERROR_CF_EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_ERROR_CF_EN_SHIFT	4
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE0EN_SHIFT		5
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE1EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE1EN_SHIFT		6
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE2EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE2EN_SHIFT		7
	u8 flags3;
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_RXMIT_PROD_CONS_EN_MASK	0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_RXMIT_PROD_CONS_EN_SHIFT	0
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE4EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE4EN_SHIFT		1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_WRITE_PROD_CONS_EN_MASK	0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_WRITE_PROD_CONS_EN_SHIFT	2
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE6EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_RULE6EN_SHIFT		3
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_ERROR_TYPE_MASK		0xF
#घोषणा E4_USTORM_RDMA_TASK_AG_CTX_DIF_ERROR_TYPE_SHIFT		4
	__le32 dअगर_err_पूर्णांकervals;
	__le32 dअगर_error_1st_पूर्णांकerval;
	__le32 dअगर_rxmit_cons;
	__le32 dअगर_rxmit_prod;
	__le32 sge_index;
	__le32 sq_cons;
	u8 byte2;
	u8 byte3;
	__le16 dअगर_ग_लिखो_cons;
	__le16 dअगर_ग_लिखो_prod;
	__le16 word3;
	__le32 dअगर_error_buffer_address_lo;
	__le32 dअगर_error_buffer_address_hi;
पूर्ण;

/* RDMA task context */
काष्ठा e4_rdma_task_context अणु
	काष्ठा ystorm_rdma_task_st_ctx ystorm_st_context;
	काष्ठा e4_ystorm_rdma_task_ag_ctx ystorm_ag_context;
	काष्ठा tdअगर_task_context tdअगर_context;
	काष्ठा e4_mstorm_rdma_task_ag_ctx mstorm_ag_context;
	काष्ठा mstorm_rdma_task_st_ctx mstorm_st_context;
	काष्ठा rdअगर_task_context rdअगर_context;
	काष्ठा ustorm_rdma_task_st_ctx ustorm_st_context;
	काष्ठा regpair ustorm_st_padding[2];
	काष्ठा e4_ustorm_rdma_task_ag_ctx ustorm_ag_context;
पूर्ण;

/* rdma function init ramrod data */
काष्ठा rdma_बंद_func_ramrod_data अणु
	u8 cnq_start_offset;
	u8 num_cnqs;
	u8 vf_id;
	u8 vf_valid;
	u8 reserved[4];
पूर्ण;

/* rdma function init CNQ parameters */
काष्ठा rdma_cnq_params अणु
	__le16 sb_num;
	u8 sb_index;
	u8 num_pbl_pages;
	__le32 reserved;
	काष्ठा regpair pbl_base_addr;
	__le16 queue_zone_num;
	u8 reserved1[6];
पूर्ण;

/* rdma create cq ramrod data */
काष्ठा rdma_create_cq_ramrod_data अणु
	काष्ठा regpair cq_handle;
	काष्ठा regpair pbl_addr;
	__le32 max_cqes;
	__le16 pbl_num_pages;
	__le16 dpi;
	u8 is_two_level_pbl;
	u8 cnq_id;
	u8 pbl_log_page_size;
	u8 toggle_bit;
	__le16 पूर्णांक_समयout;
	u8 vf_id;
	u8 flags;
#घोषणा RDMA_CREATE_CQ_RAMROD_DATA_VF_ID_VALID_MASK  0x1
#घोषणा RDMA_CREATE_CQ_RAMROD_DATA_VF_ID_VALID_SHIFT 0
#घोषणा RDMA_CREATE_CQ_RAMROD_DATA_RESERVED1_MASK    0x7F
#घोषणा RDMA_CREATE_CQ_RAMROD_DATA_RESERVED1_SHIFT   1
पूर्ण;

/* rdma deरेजिस्टर tid ramrod data */
काष्ठा rdma_deरेजिस्टर_tid_ramrod_data अणु
	__le32 itid;
	__le32 reserved;
पूर्ण;

/* rdma destroy cq output params */
काष्ठा rdma_destroy_cq_output_params अणु
	__le16 cnq_num;
	__le16 reserved0;
	__le32 reserved1;
पूर्ण;

/* rdma destroy cq ramrod data */
काष्ठा rdma_destroy_cq_ramrod_data अणु
	काष्ठा regpair output_params_addr;
पूर्ण;

/* RDMA slow path EQ cmd IDs */
क्रमागत rdma_event_opcode अणु
	RDMA_EVENT_UNUSED,
	RDMA_EVENT_FUNC_INIT,
	RDMA_EVENT_FUNC_CLOSE,
	RDMA_EVENT_REGISTER_MR,
	RDMA_EVENT_DEREGISTER_MR,
	RDMA_EVENT_CREATE_CQ,
	RDMA_EVENT_RESIZE_CQ,
	RDMA_EVENT_DESTROY_CQ,
	RDMA_EVENT_CREATE_SRQ,
	RDMA_EVENT_MODIFY_SRQ,
	RDMA_EVENT_DESTROY_SRQ,
	MAX_RDMA_EVENT_OPCODE
पूर्ण;

/* RDMA FW वापस code क्रम slow path ramrods */
क्रमागत rdma_fw_वापस_code अणु
	RDMA_RETURN_OK = 0,
	RDMA_RETURN_REGISTER_MR_BAD_STATE_ERR,
	RDMA_RETURN_DEREGISTER_MR_BAD_STATE_ERR,
	RDMA_RETURN_RESIZE_CQ_ERR,
	RDMA_RETURN_NIG_DRAIN_REQ,
	RDMA_RETURN_GENERAL_ERR,
	MAX_RDMA_FW_RETURN_CODE
पूर्ण;

/* rdma function init header */
काष्ठा rdma_init_func_hdr अणु
	u8 cnq_start_offset;
	u8 num_cnqs;
	u8 cq_ring_mode;
	u8 vf_id;
	u8 vf_valid;
	u8 relaxed_ordering;
	__le16 first_reg_srq_id;
	__le32 reg_srq_base_addr;
	u8 searcher_mode;
	u8 pvrdma_mode;
	u8 max_num_ns_log;
	u8 reserved;
पूर्ण;

/* rdma function init ramrod data */
काष्ठा rdma_init_func_ramrod_data अणु
	काष्ठा rdma_init_func_hdr params_header;
	काष्ठा rdma_cnq_params cnq_params[NUM_OF_GLOBAL_QUEUES];
पूर्ण;

/* RDMA ramrod command IDs */
क्रमागत rdma_ramrod_cmd_id अणु
	RDMA_RAMROD_UNUSED,
	RDMA_RAMROD_FUNC_INIT,
	RDMA_RAMROD_FUNC_CLOSE,
	RDMA_RAMROD_REGISTER_MR,
	RDMA_RAMROD_DEREGISTER_MR,
	RDMA_RAMROD_CREATE_CQ,
	RDMA_RAMROD_RESIZE_CQ,
	RDMA_RAMROD_DESTROY_CQ,
	RDMA_RAMROD_CREATE_SRQ,
	RDMA_RAMROD_MODIFY_SRQ,
	RDMA_RAMROD_DESTROY_SRQ,
	MAX_RDMA_RAMROD_CMD_ID
पूर्ण;

/* rdma रेजिस्टर tid ramrod data */
काष्ठा rdma_रेजिस्टर_tid_ramrod_data अणु
	__le16 flags;
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_PAGE_SIZE_LOG_MASK	0x1F
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_PAGE_SIZE_LOG_SHIFT	0
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_TWO_LEVEL_PBL_MASK	0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_TWO_LEVEL_PBL_SHIFT	5
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_ZERO_BASED_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_ZERO_BASED_SHIFT		6
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_PHY_MR_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_PHY_MR_SHIFT		7
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_READ_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_READ_SHIFT		8
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_WRITE_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_WRITE_SHIFT	9
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_ATOMIC_MASK	0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_ATOMIC_SHIFT	10
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_LOCAL_WRITE_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_LOCAL_WRITE_SHIFT		11
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_LOCAL_READ_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_LOCAL_READ_SHIFT		12
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_ENABLE_MW_BIND_MASK	0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_ENABLE_MW_BIND_SHIFT	13
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_RESERVED_MASK		0x3
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_RESERVED_SHIFT		14
	u8 flags1;
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_PBL_PAGE_SIZE_LOG_MASK	0x1F
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_PBL_PAGE_SIZE_LOG_SHIFT	0
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_TID_TYPE_MASK		0x7
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_TID_TYPE_SHIFT		5
	u8 flags2;
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_DMA_MR_MASK		0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_DMA_MR_SHIFT		0
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_DIF_ON_HOST_FLG_MASK	0x1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_DIF_ON_HOST_FLG_SHIFT	1
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_RESERVED1_MASK		0x3F
#घोषणा RDMA_REGISTER_TID_RAMROD_DATA_RESERVED1_SHIFT		2
	u8 key;
	u8 length_hi;
	u8 vf_id;
	u8 vf_valid;
	__le16 pd;
	__le16 reserved2;
	__le32 length_lo;
	__le32 itid;
	__le32 reserved3;
	काष्ठा regpair va;
	काष्ठा regpair pbl_base;
	काष्ठा regpair dअगर_error_addr;
	__le32 reserved4[4];
पूर्ण;

/* rdma resize cq output params */
काष्ठा rdma_resize_cq_output_params अणु
	__le32 old_cq_cons;
	__le32 old_cq_prod;
पूर्ण;

/* rdma resize cq ramrod data */
काष्ठा rdma_resize_cq_ramrod_data अणु
	u8 flags;
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_TOGGLE_BIT_MASK		0x1
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_TOGGLE_BIT_SHIFT		0
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_IS_TWO_LEVEL_PBL_MASK	0x1
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_IS_TWO_LEVEL_PBL_SHIFT	1
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_VF_ID_VALID_MASK		0x1
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_VF_ID_VALID_SHIFT		2
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_RESERVED_MASK		0x1F
#घोषणा RDMA_RESIZE_CQ_RAMROD_DATA_RESERVED_SHIFT		3
	u8 pbl_log_page_size;
	__le16 pbl_num_pages;
	__le32 max_cqes;
	काष्ठा regpair pbl_addr;
	काष्ठा regpair output_params_addr;
	u8 vf_id;
	u8 reserved1[7];
पूर्ण;

/* The rdma SRQ context */
काष्ठा rdma_srq_context अणु
	काष्ठा regpair temp[8];
पूर्ण;

/* rdma create qp requester ramrod data */
काष्ठा rdma_srq_create_ramrod_data अणु
	u8 flags;
#घोषणा RDMA_SRQ_CREATE_RAMROD_DATA_XRC_FLAG_MASK         0x1
#घोषणा RDMA_SRQ_CREATE_RAMROD_DATA_XRC_FLAG_SHIFT        0
#घोषणा RDMA_SRQ_CREATE_RAMROD_DATA_RESERVED_KEY_EN_MASK  0x1
#घोषणा RDMA_SRQ_CREATE_RAMROD_DATA_RESERVED_KEY_EN_SHIFT 1
#घोषणा RDMA_SRQ_CREATE_RAMROD_DATA_RESERVED1_MASK        0x3F
#घोषणा RDMA_SRQ_CREATE_RAMROD_DATA_RESERVED1_SHIFT       2
	u8 reserved2;
	__le16 xrc_करोमुख्य;
	__le32 xrc_srq_cq_cid;
	काष्ठा regpair pbl_base_addr;
	__le16 pages_in_srq_pbl;
	__le16 pd_id;
	काष्ठा rdma_srq_id srq_id;
	__le16 page_size;
	__le16 reserved3;
	__le32 reserved4;
	काष्ठा regpair producers_addr;
पूर्ण;

/* rdma create qp requester ramrod data */
काष्ठा rdma_srq_destroy_ramrod_data अणु
	काष्ठा rdma_srq_id srq_id;
	__le32 reserved;
पूर्ण;

/* rdma create qp requester ramrod data */
काष्ठा rdma_srq_modअगरy_ramrod_data अणु
	काष्ठा rdma_srq_id srq_id;
	__le32 wqe_limit;
पूर्ण;

/* RDMA Tid type क्रमागतeration (क्रम रेजिस्टर_tid ramrod) */
क्रमागत rdma_tid_type अणु
	RDMA_TID_REGISTERED_MR,
	RDMA_TID_FMR,
	RDMA_TID_MW,
	MAX_RDMA_TID_TYPE
पूर्ण;

/* The rdma XRC SRQ context */
काष्ठा rdma_xrc_srq_context अणु
	काष्ठा regpair temp[9];
पूर्ण;

काष्ठा e4_tstorm_rdma_task_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	__le16 word0;
	u8 flags0;
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_NIBBLE0_MASK		0xF
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_NIBBLE0_SHIFT	0
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT0_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT0_SHIFT		4
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT1_SHIFT		5
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT2_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT2_SHIFT		6
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT3_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT3_SHIFT		7
	u8 flags1;
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT4_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT4_SHIFT	0
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT5_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_BIT5_SHIFT	1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF0_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF0_SHIFT	2
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF1_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF1_SHIFT	4
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF2_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF2_SHIFT	6
	u8 flags2;
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF3_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF3_SHIFT	0
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF4_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF4_SHIFT	2
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF5_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF5_SHIFT	4
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF6_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF6_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF7_MASK	0x3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF7_SHIFT	0
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF0EN_SHIFT	2
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF1EN_SHIFT	3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF2EN_SHIFT	4
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF3EN_SHIFT	5
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF4EN_SHIFT	6
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF5EN_SHIFT	7
	u8 flags4;
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF6EN_SHIFT		0
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF7EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_CF7EN_SHIFT		1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE0EN_SHIFT	2
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE1EN_SHIFT	3
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE2EN_SHIFT	4
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE3EN_SHIFT	5
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE4EN_SHIFT	6
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_RDMA_TASK_AG_CTX_RULE5EN_SHIFT	7
	u8 byte2;
	__le16 word1;
	__le32 reg0;
	u8 byte3;
	u8 byte4;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg1;
	__le32 reg2;
पूर्ण;

काष्ठा e4_ustorm_rdma_conn_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_DIF_ERROR_REPORTED_MASK  0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_DIF_ERROR_REPORTED_SHIFT 1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_FLUSH_Q0_CF_MASK	0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT	2
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF1_SHIFT		4
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF2_SHIFT		6
	u8 flags1;
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF3_MASK		0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF3_SHIFT		0
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_SE_CF_MASK	0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_SE_CF_SHIFT	2
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_CF_MASK	0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_CF_SHIFT	4
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF6_MASK		0x3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF6_SHIFT		6
	u8 flags2;
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT		0
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF1EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF1EN_SHIFT			1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF2EN_SHIFT			2
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF3EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF3EN_SHIFT			3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_SE_CF_EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_SE_CF_EN_SHIFT	4
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_CF_EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_ARM_CF_EN_SHIFT		5
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF6EN_MASK			0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CF6EN_SHIFT			6
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_SE_EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_SE_EN_SHIFT		7
	u8 flags3;
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_CQ_EN_SHIFT		0
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_USTORM_RDMA_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 nvmf_only;
	__le16 conn_dpi;
	__le16 word1;
	__le32 cq_cons;
	__le32 cq_se_prod;
	__le32 cq_prod;
	__le32 reg3;
	__le16 पूर्णांक_समयout;
	__le16 word3;
पूर्ण;

काष्ठा e4_xstorm_roce_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_EXIST_IN_QM0_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_EXIST_IN_QM0_SHIFT     0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT1_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT1_SHIFT             1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT2_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT2_SHIFT             2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_EXIST_IN_QM3_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_EXIST_IN_QM3_SHIFT     3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT4_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT4_SHIFT             4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT5_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT5_SHIFT             5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT6_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT6_SHIFT             6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT7_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT7_SHIFT             7
	u8 flags1;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT8_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT8_SHIFT             0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT9_MASK              0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT9_SHIFT             1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT10_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT10_SHIFT            2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT11_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT11_SHIFT            3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_MSDM_FLUSH_MASK        0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_MSDM_FLUSH_SHIFT       4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_MSEM_FLUSH_MASK        0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_MSEM_FLUSH_SHIFT       5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT14_MASK	       0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT14_SHIFT	       6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_YSTORM_FLUSH_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_YSTORM_FLUSH_SHIFT     7
	u8 flags2;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF0_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF0_SHIFT              0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF1_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF1_SHIFT              2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF2_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF2_SHIFT              4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF3_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF3_SHIFT              6
	u8 flags3;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF4_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF4_SHIFT              0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF5_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF5_SHIFT              2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF6_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF6_SHIFT              4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_MASK       0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT      6
	u8 flags4;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF8_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF8_SHIFT              0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF9_MASK               0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF9_SHIFT              2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF10_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF10_SHIFT             4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF11_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF11_SHIFT             6
	u8 flags5;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF12_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF12_SHIFT             0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF13_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF13_SHIFT             2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF14_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF14_SHIFT             4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF15_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF15_SHIFT             6
	u8 flags6;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF16_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF16_SHIFT             0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF17_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF17_SHIFT             2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF18_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF18_SHIFT             4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF19_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF19_SHIFT             6
	u8 flags7;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF20_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF20_SHIFT             0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF21_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF21_SHIFT             2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_SLOW_PATH_MASK         0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_SLOW_PATH_SHIFT        4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF0EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF0EN_SHIFT            6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF1EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF1EN_SHIFT            7
	u8 flags8;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF2EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF2EN_SHIFT            0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF3EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF3EN_SHIFT            1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF4EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF4EN_SHIFT            2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF5EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF5EN_SHIFT            3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF6EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF6EN_SHIFT            4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK    0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT   5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF8EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF8EN_SHIFT            6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF9EN_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF9EN_SHIFT            7
	u8 flags9;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF10EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF10EN_SHIFT           0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF11EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF11EN_SHIFT           1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF12EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF12EN_SHIFT           2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF13EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF13EN_SHIFT           3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF14EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF14EN_SHIFT           4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF15EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF15EN_SHIFT           5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF16EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF16EN_SHIFT           6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF17EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF17EN_SHIFT           7
	u8 flags10;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF18EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF18EN_SHIFT           0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF19EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF19EN_SHIFT           1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF20EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF20EN_SHIFT           2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF21EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF21EN_SHIFT           3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_SLOW_PATH_EN_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_SLOW_PATH_EN_SHIFT     4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF23EN_MASK            0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF23EN_SHIFT           5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE0EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE0EN_SHIFT          6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE1EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE1EN_SHIFT          7
	u8 flags11;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE2EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE2EN_SHIFT          0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE3EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE3EN_SHIFT          1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE4EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE4EN_SHIFT          2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE5EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE5EN_SHIFT          3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE6EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE6EN_SHIFT          4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE7EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE7EN_SHIFT          5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED1_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED1_SHIFT     6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE9EN_MASK           0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE9EN_SHIFT          7
	u8 flags12;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE10EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE10EN_SHIFT         0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE11EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE11EN_SHIFT         1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED2_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED2_SHIFT     2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED3_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED3_SHIFT     3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE14EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE14EN_SHIFT         4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE15EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE15EN_SHIFT         5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE16EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE16EN_SHIFT         6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE17EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE17EN_SHIFT         7
	u8 flags13;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE18EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE18EN_SHIFT         0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE19EN_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RULE19EN_SHIFT         1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED4_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED4_SHIFT     2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED5_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED5_SHIFT     3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED6_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED6_SHIFT     4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED7_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED7_SHIFT     5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED8_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED8_SHIFT     6
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED9_MASK      0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_A0_RESERVED9_SHIFT     7
	u8 flags14;
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_MIGRATION_MASK         0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_MIGRATION_SHIFT        0
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT17_MASK             0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_BIT17_SHIFT            1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_DPM_PORT_NUM_MASK      0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_DPM_PORT_NUM_SHIFT     2
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RESERVED_MASK          0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_RESERVED_SHIFT         4
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_ROCE_EDPM_ENABLE_MASK  0x1
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_ROCE_EDPM_ENABLE_SHIFT 5
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF23_MASK              0x3
#घोषणा E4_XSTORM_ROCE_CONN_AG_CTX_CF23_SHIFT             6
	u8 byte2;
	__le16 physical_q0;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le16 word5;
	__le16 conn_dpi;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 snd_nxt_psn;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
पूर्ण;

काष्ठा e4_tstorm_roce_conn_ag_ctx अणु
	u8 reserved0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_EXIST_IN_QM0_MASK          0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_EXIST_IN_QM0_SHIFT         0
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT1_MASK                  0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT1_SHIFT                 1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT2_MASK                  0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT2_SHIFT                 2
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT3_MASK                  0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT3_SHIFT                 3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT4_MASK                  0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT4_SHIFT                 4
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT5_MASK                  0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_BIT5_SHIFT                 5
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF0_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF0_SHIFT                  6
	u8 flags1;
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_MSTORM_FLUSH_CF_MASK       0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_MSTORM_FLUSH_CF_SHIFT      0
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF2_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF2_SHIFT                  2
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_TIMER_STOP_ALL_CF_MASK     0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_TIMER_STOP_ALL_CF_SHIFT    4
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_MASK           0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT          6
	u8 flags2;
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF5_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF5_SHIFT                  0
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF6_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF6_SHIFT                  2
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF7_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF7_SHIFT                  4
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF8_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF8_SHIFT                  6
	u8 flags3;
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF9_MASK                   0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF9_SHIFT                  0
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF10_MASK                  0x3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF10_SHIFT                 2
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF0EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF0EN_SHIFT                4
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_MSTORM_FLUSH_CF_EN_MASK    0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_MSTORM_FLUSH_CF_EN_SHIFT   5
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF2EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF2EN_SHIFT                6
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_TIMER_STOP_ALL_CF_EN_MASK  0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_TIMER_STOP_ALL_CF_EN_SHIFT 7
	u8 flags4;
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK        0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT       0
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF5EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF5EN_SHIFT                1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF6EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF6EN_SHIFT                2
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF7EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF7EN_SHIFT                3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF8EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF8EN_SHIFT                4
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF9EN_MASK                 0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF9EN_SHIFT                5
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF10EN_MASK                0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_CF10EN_SHIFT               6
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE0EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE0EN_SHIFT              7
	u8 flags5;
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE1EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE1EN_SHIFT              0
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE2EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE2EN_SHIFT              1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE3EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE3EN_SHIFT              2
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE4EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE4EN_SHIFT              3
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE5EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE5EN_SHIFT              4
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE6EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE6EN_SHIFT              5
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE7EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE7EN_SHIFT              6
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE8EN_MASK               0x1
#घोषणा E4_TSTORM_ROCE_CONN_AG_CTX_RULE8EN_SHIFT              7
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le32 reg7;
	__le32 reg8;
	u8 byte2;
	u8 byte3;
	__le16 word0;
	u8 byte4;
	u8 byte5;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le32 reg9;
	__le32 reg10;
पूर्ण;

/* The roce storm context of Ystorm */
काष्ठा ystorm_roce_conn_st_ctx अणु
	काष्ठा regpair temp[2];
पूर्ण;

/* The roce storm context of Mstorm */
काष्ठा pstorm_roce_conn_st_ctx अणु
	काष्ठा regpair temp[16];
पूर्ण;

/* The roce storm context of Xstorm */
काष्ठा xstorm_roce_conn_st_ctx अणु
	काष्ठा regpair temp[24];
पूर्ण;

/* The roce storm context of Tstorm */
काष्ठा tstorm_roce_conn_st_ctx अणु
	काष्ठा regpair temp[30];
पूर्ण;

/* The roce storm context of Mstorm */
काष्ठा mstorm_roce_conn_st_ctx अणु
	काष्ठा regpair temp[6];
पूर्ण;

/* The roce storm context of Ustorm */
काष्ठा ustorm_roce_conn_st_ctx अणु
	काष्ठा regpair temp[14];
पूर्ण;

/* roce connection context */
काष्ठा e4_roce_conn_context अणु
	काष्ठा ystorm_roce_conn_st_ctx ystorm_st_context;
	काष्ठा regpair ystorm_st_padding[2];
	काष्ठा pstorm_roce_conn_st_ctx pstorm_st_context;
	काष्ठा xstorm_roce_conn_st_ctx xstorm_st_context;
	काष्ठा e4_xstorm_roce_conn_ag_ctx xstorm_ag_context;
	काष्ठा e4_tstorm_roce_conn_ag_ctx tstorm_ag_context;
	काष्ठा समयrs_context समयr_context;
	काष्ठा e4_ustorm_rdma_conn_ag_ctx ustorm_ag_context;
	काष्ठा tstorm_roce_conn_st_ctx tstorm_st_context;
	काष्ठा regpair tstorm_st_padding[2];
	काष्ठा mstorm_roce_conn_st_ctx mstorm_st_context;
	काष्ठा regpair mstorm_st_padding[2];
	काष्ठा ustorm_roce_conn_st_ctx ustorm_st_context;
	काष्ठा regpair ustorm_st_padding[2];
पूर्ण;

/* roce cqes statistics */
काष्ठा roce_cqe_stats अणु
	__le32 req_cqe_error;
	__le32 req_remote_access_errors;
	__le32 req_remote_invalid_request;
	__le32 resp_cqe_error;
	__le32 resp_local_length_error;
	__le32 reserved;
पूर्ण;

/* roce create qp requester ramrod data */
काष्ठा roce_create_qp_req_ramrod_data अणु
	__le16 flags;
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_ROCE_FLAVOR_MASK			0x3
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_ROCE_FLAVOR_SHIFT		0
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_FMR_AND_RESERVED_EN_MASK		0x1
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_FMR_AND_RESERVED_EN_SHIFT	2
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_SIGNALED_COMP_MASK		0x1
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_SIGNALED_COMP_SHIFT		3
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_PRI_MASK				0x7
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_PRI_SHIFT			4
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_XRC_FLAG_MASK			0x1
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_XRC_FLAG_SHIFT			7
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_MASK		0xF
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_SHIFT		8
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_MASK			0xF
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_SHIFT		12
	u8 max_ord;
	u8 traffic_class;
	u8 hop_limit;
	u8 orq_num_pages;
	__le16 p_key;
	__le32 flow_label;
	__le32 dst_qp_id;
	__le32 ack_समयout_val;
	__le32 initial_psn;
	__le16 mtu;
	__le16 pd;
	__le16 sq_num_pages;
	__le16 low_latency_phy_queue;
	काष्ठा regpair sq_pbl_addr;
	काष्ठा regpair orq_pbl_addr;
	__le16 local_mac_addr[3];
	__le16 remote_mac_addr[3];
	__le16 vlan_id;
	__le16 udp_src_port;
	__le32 src_gid[4];
	__le32 dst_gid[4];
	__le32 cq_cid;
	काष्ठा regpair qp_handle_क्रम_cqe;
	काष्ठा regpair qp_handle_क्रम_async;
	u8 stats_counter_id;
	u8 vf_id;
	u8 vport_id;
	u8 flags2;
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_EDPM_MODE_MASK			0x1
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_EDPM_MODE_SHIFT			0
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_VF_ID_VALID_MASK			0x1
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_VF_ID_VALID_SHIFT		1
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_RESERVED_MASK			0x3F
#घोषणा ROCE_CREATE_QP_REQ_RAMROD_DATA_RESERVED_SHIFT			2
	u8 name_space;
	u8 reserved3[3];
	__le16 regular_latency_phy_queue;
	__le16 dpi;
पूर्ण;

/* roce create qp responder ramrod data */
काष्ठा roce_create_qp_resp_ramrod_data अणु
	__le32 flags;
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_ROCE_FLAVOR_MASK		0x3
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_ROCE_FLAVOR_SHIFT		0
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_RD_EN_MASK			0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_RD_EN_SHIFT		2
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_WR_EN_MASK			0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_WR_EN_SHIFT		3
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_ATOMIC_EN_MASK			0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_ATOMIC_EN_SHIFT			4
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_SRQ_FLG_MASK			0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_SRQ_FLG_SHIFT			5
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN_MASK	0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN_SHIFT	6
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_KEY_EN_MASK		0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_KEY_EN_SHIFT		7
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_PRI_MASK			0x7
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_PRI_SHIFT			8
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_MASK		0x1F
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_SHIFT		11
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_XRC_FLAG_MASK             0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_XRC_FLAG_SHIFT            16
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_VF_ID_VALID_MASK	0x1
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_VF_ID_VALID_SHIFT	17
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_MASK		0x3FFF
#घोषणा ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_SHIFT		18
	__le16 xrc_करोमुख्य;
	u8 max_ird;
	u8 traffic_class;
	u8 hop_limit;
	u8 irq_num_pages;
	__le16 p_key;
	__le32 flow_label;
	__le32 dst_qp_id;
	u8 stats_counter_id;
	u8 reserved1;
	__le16 mtu;
	__le32 initial_psn;
	__le16 pd;
	__le16 rq_num_pages;
	काष्ठा rdma_srq_id srq_id;
	काष्ठा regpair rq_pbl_addr;
	काष्ठा regpair irq_pbl_addr;
	__le16 local_mac_addr[3];
	__le16 remote_mac_addr[3];
	__le16 vlan_id;
	__le16 udp_src_port;
	__le32 src_gid[4];
	__le32 dst_gid[4];
	काष्ठा regpair qp_handle_क्रम_cqe;
	काष्ठा regpair qp_handle_क्रम_async;
	__le16 low_latency_phy_queue;
	u8 vf_id;
	u8 vport_id;
	__le32 cq_cid;
	__le16 regular_latency_phy_queue;
	__le16 dpi;
	__le32 src_qp_id;
	u8 name_space;
	u8 reserved3[3];
पूर्ण;

/* roce DCQCN received statistics */
काष्ठा roce_dcqcn_received_stats अणु
	काष्ठा regpair ecn_pkt_rcv;
	काष्ठा regpair cnp_pkt_rcv;
पूर्ण;

/* roce DCQCN sent statistics */
काष्ठा roce_dcqcn_sent_stats अणु
	काष्ठा regpair cnp_pkt_sent;
पूर्ण;

/* RoCE destroy qp requester output params */
काष्ठा roce_destroy_qp_req_output_params अणु
	__le32 cq_prod;
	__le32 reserved;
पूर्ण;

/* RoCE destroy qp requester ramrod data */
काष्ठा roce_destroy_qp_req_ramrod_data अणु
	काष्ठा regpair output_params_addr;
पूर्ण;

/* RoCE destroy qp responder output params */
काष्ठा roce_destroy_qp_resp_output_params अणु
	__le32 cq_prod;
	__le32 reserved;
पूर्ण;

/* RoCE destroy qp responder ramrod data */
काष्ठा roce_destroy_qp_resp_ramrod_data अणु
	काष्ठा regpair output_params_addr;
	__le32 src_qp_id;
	__le32 reserved;
पूर्ण;

/* roce error statistics */
काष्ठा roce_error_stats अणु
	__le32 resp_remote_access_errors;
	__le32 reserved;
पूर्ण;

/* roce special events statistics */
काष्ठा roce_events_stats अणु
	__le32 silent_drops;
	__le32 rnr_naks_sent;
	__le32 retransmit_count;
	__le32 icrc_error_count;
	__le32 implied_nak_seq_err;
	__le32 duplicate_request;
	__le32 local_ack_समयout_err;
	__le32 out_of_sequence;
	__le32 packet_seq_err;
	__le32 rnr_nak_retry_err;
पूर्ण;

/* roce slow path EQ cmd IDs */
क्रमागत roce_event_opcode अणु
	ROCE_EVENT_CREATE_QP = 11,
	ROCE_EVENT_MODIFY_QP,
	ROCE_EVENT_QUERY_QP,
	ROCE_EVENT_DESTROY_QP,
	ROCE_EVENT_CREATE_UD_QP,
	ROCE_EVENT_DESTROY_UD_QP,
	ROCE_EVENT_FUNC_UPDATE,
	MAX_ROCE_EVENT_OPCODE
पूर्ण;

/* roce func init ramrod data */
काष्ठा roce_init_func_params अणु
	u8 ll2_queue_id;
	u8 cnp_vlan_priority;
	u8 cnp_dscp;
	u8 flags;
#घोषणा ROCE_INIT_FUNC_PARAMS_DCQCN_NP_EN_MASK		0x1
#घोषणा ROCE_INIT_FUNC_PARAMS_DCQCN_NP_EN_SHIFT		0
#घोषणा ROCE_INIT_FUNC_PARAMS_DCQCN_RP_EN_MASK		0x1
#घोषणा ROCE_INIT_FUNC_PARAMS_DCQCN_RP_EN_SHIFT		1
#घोषणा ROCE_INIT_FUNC_PARAMS_RESERVED0_MASK		0x3F
#घोषणा ROCE_INIT_FUNC_PARAMS_RESERVED0_SHIFT		2
	__le32 cnp_send_समयout;
	__le16 rl_offset;
	u8 rl_count_log;
	u8 reserved1[5];
पूर्ण;

/* roce func init ramrod data */
काष्ठा roce_init_func_ramrod_data अणु
	काष्ठा rdma_init_func_ramrod_data rdma;
	काष्ठा roce_init_func_params roce;
पूर्ण;

/* roce modअगरy qp requester ramrod data */
काष्ठा roce_modअगरy_qp_req_ramrod_data अणु
	__le16 flags;
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_ERR_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_ERR_FLG_SHIFT		0
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_SQD_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_MOVE_TO_SQD_FLG_SHIFT		1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_EN_SQD_ASYNC_NOTIFY_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_EN_SQD_ASYNC_NOTIFY_SHIFT	2
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_P_KEY_FLG_MASK			0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_P_KEY_FLG_SHIFT			3
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ADDRESS_VECTOR_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ADDRESS_VECTOR_FLG_SHIFT		4
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_MAX_ORD_FLG_MASK			0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_MAX_ORD_FLG_SHIFT		5
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_FLG_SHIFT		6
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_FLG_SHIFT		7
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ACK_TIMEOUT_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ACK_TIMEOUT_FLG_SHIFT		8
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_PRI_FLG_MASK			0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_PRI_FLG_SHIFT			9
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_PRI_MASK				0x7
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_PRI_SHIFT			10
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_PHYSICAL_QUEUE_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_PHYSICAL_QUEUE_FLG_SHIFT		13
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_RESERVED1_MASK			0x3
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_RESERVED1_SHIFT			14
	u8 fields;
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_MASK	0xF
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_ERR_RETRY_CNT_SHIFT	0
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_MASK		0xF
#घोषणा ROCE_MODIFY_QP_REQ_RAMROD_DATA_RNR_NAK_CNT_SHIFT	4
	u8 max_ord;
	u8 traffic_class;
	u8 hop_limit;
	__le16 p_key;
	__le32 flow_label;
	__le32 ack_समयout_val;
	__le16 mtu;
	__le16 reserved2;
	__le32 reserved3[2];
	__le16 low_latency_phy_queue;
	__le16 regular_latency_phy_queue;
	__le32 src_gid[4];
	__le32 dst_gid[4];
पूर्ण;

/* roce modअगरy qp responder ramrod data */
काष्ठा roce_modअगरy_qp_resp_ramrod_data अणु
	__le16 flags;
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MOVE_TO_ERR_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MOVE_TO_ERR_FLG_SHIFT		0
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_RD_EN_MASK			0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_RD_EN_SHIFT		1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_WR_EN_MASK			0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_WR_EN_SHIFT		2
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_ATOMIC_EN_MASK			0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_ATOMIC_EN_SHIFT			3
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_P_KEY_FLG_MASK			0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_P_KEY_FLG_SHIFT			4
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_ADDRESS_VECTOR_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_ADDRESS_VECTOR_FLG_SHIFT	5
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MAX_IRD_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MAX_IRD_FLG_SHIFT		6
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_PRI_FLG_MASK			0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_PRI_FLG_SHIFT			7
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_FLG_MASK	0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_FLG_SHIFT	8
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_OPS_EN_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_OPS_EN_FLG_SHIFT		9
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_PHYSICAL_QUEUE_FLG_MASK		0x1
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_PHYSICAL_QUEUE_FLG_SHIFT	10
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RESERVED1_MASK			0x1F
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_RESERVED1_SHIFT			11
	u8 fields;
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_PRI_MASK		0x7
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_PRI_SHIFT		0
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_MASK	0x1F
#घोषणा ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_SHIFT	3
	u8 max_ird;
	u8 traffic_class;
	u8 hop_limit;
	__le16 p_key;
	__le32 flow_label;
	__le16 mtu;
	__le16 low_latency_phy_queue;
	__le16 regular_latency_phy_queue;
	u8 reserved2[6];
	__le32 src_gid[4];
	__le32 dst_gid[4];
पूर्ण;

/* RoCE query qp requester output params */
काष्ठा roce_query_qp_req_output_params अणु
	__le32 psn;
	__le32 flags;
#घोषणा ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_ERR_FLG_MASK		0x1
#घोषणा ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_ERR_FLG_SHIFT		0
#घोषणा ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_SQ_DRAINING_FLG_MASK	0x1
#घोषणा ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_SQ_DRAINING_FLG_SHIFT	1
#घोषणा ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_RESERVED0_MASK		0x3FFFFFFF
#घोषणा ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_RESERVED0_SHIFT		2
पूर्ण;

/* RoCE query qp requester ramrod data */
काष्ठा roce_query_qp_req_ramrod_data अणु
	काष्ठा regpair output_params_addr;
पूर्ण;

/* RoCE query qp responder output params */
काष्ठा roce_query_qp_resp_output_params अणु
	__le32 psn;
	__le32 flags;
#घोषणा ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_ERROR_FLG_MASK  0x1
#घोषणा ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_ERROR_FLG_SHIFT 0
#घोषणा ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_RESERVED0_MASK  0x7FFFFFFF
#घोषणा ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_RESERVED0_SHIFT 1
पूर्ण;

/* RoCE query qp responder ramrod data */
काष्ठा roce_query_qp_resp_ramrod_data अणु
	काष्ठा regpair output_params_addr;
पूर्ण;

/* ROCE ramrod command IDs */
क्रमागत roce_ramrod_cmd_id अणु
	ROCE_RAMROD_CREATE_QP = 11,
	ROCE_RAMROD_MODIFY_QP,
	ROCE_RAMROD_QUERY_QP,
	ROCE_RAMROD_DESTROY_QP,
	ROCE_RAMROD_CREATE_UD_QP,
	ROCE_RAMROD_DESTROY_UD_QP,
	ROCE_RAMROD_FUNC_UPDATE,
	MAX_ROCE_RAMROD_CMD_ID
पूर्ण;

/* RoCE func init ramrod data */
काष्ठा roce_update_func_params अणु
	u8 cnp_vlan_priority;
	u8 cnp_dscp;
	__le16 flags;
#घोषणा ROCE_UPDATE_FUNC_PARAMS_DCQCN_NP_EN_MASK	0x1
#घोषणा ROCE_UPDATE_FUNC_PARAMS_DCQCN_NP_EN_SHIFT	0
#घोषणा ROCE_UPDATE_FUNC_PARAMS_DCQCN_RP_EN_MASK	0x1
#घोषणा ROCE_UPDATE_FUNC_PARAMS_DCQCN_RP_EN_SHIFT	1
#घोषणा ROCE_UPDATE_FUNC_PARAMS_RESERVED0_MASK		0x3FFF
#घोषणा ROCE_UPDATE_FUNC_PARAMS_RESERVED0_SHIFT		2
	__le32 cnp_send_समयout;
पूर्ण;

काष्ठा e4_xstorm_roce_conn_ag_ctx_dq_ext_ld_part अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_EXIST_IN_QM0_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_EXIST_IN_QM0_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT1_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT1_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT2_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT2_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_EXIST_IN_QM3_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_EXIST_IN_QM3_SHIFT	3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT4_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT4_SHIFT		4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT5_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT5_SHIFT		5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT6_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT6_SHIFT		6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT7_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT7_SHIFT		7
	u8 flags1;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT8_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT8_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT9_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT9_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT10_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT10_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT11_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT11_SHIFT		3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_MSDM_FLUSH_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_MSDM_FLUSH_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_MSEM_FLUSH_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_MSEM_FLUSH_SHIFT	5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT14_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT14_SHIFT		6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_YSTORM_FLUSH_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_YSTORM_FLUSH_SHIFT	7
	u8 flags2;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF0_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF0_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF1_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF1_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF2_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF2_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF3_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF4_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF4_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF5_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF5_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF6_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF6_SHIFT		4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_FLUSH_Q0_CF_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_FLUSH_Q0_CF_SHIFT	6
	u8 flags4;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF8_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF8_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF9_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF9_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF10_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF10_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF11_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF12_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF12_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF13_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF13_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF14_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF14_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF15_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF16_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF16_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF17_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF17_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF18_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF18_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF19_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF19_SHIFT	6
	u8 flags7;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF20_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF20_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF21_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF21_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_SLOW_PATH_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_SLOW_PATH_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF0EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF0EN_SHIFT		6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF1EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF1EN_SHIFT		7
	u8 flags8;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF2EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF2EN_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF3EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF3EN_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF4EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF4EN_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF5EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF5EN_SHIFT		3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF6EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF6EN_SHIFT		4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_FLUSH_Q0_CF_EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_FLUSH_Q0_CF_EN_SHIFT	5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF8EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF8EN_SHIFT		6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF9EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF9EN_SHIFT		7
	u8 flags9;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF10EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF10EN_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF11EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF11EN_SHIFT	1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF12EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF12EN_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF13EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF13EN_SHIFT	3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF14EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF14EN_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF15EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF15EN_SHIFT	5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF16EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF16EN_SHIFT	6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF17EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF17EN_SHIFT	7
	u8 flags10;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF18EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF18EN_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF19EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF19EN_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF20EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF20EN_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF21EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF21EN_SHIFT		3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_SLOW_PATH_EN_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_SLOW_PATH_EN_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF23EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF23EN_SHIFT		5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE0EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE0EN_SHIFT		6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE1EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE1EN_SHIFT		7
	u8 flags11;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE2EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE2EN_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE3EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE3EN_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE4EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE4EN_SHIFT		2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE5EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE5EN_SHIFT		3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE6EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE6EN_SHIFT		4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE7EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE7EN_SHIFT		5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED1_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED1_SHIFT	6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE9EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE9EN_SHIFT		7
	u8 flags12;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE10EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE10EN_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE11EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE11EN_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED2_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED2_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED3_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED3_SHIFT	3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE14EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE14EN_SHIFT		4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE15EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE15EN_SHIFT		5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE16EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE16EN_SHIFT		6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE17EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE17EN_SHIFT		7
	u8 flags13;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE18EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE18EN_SHIFT		0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE19EN_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RULE19EN_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED4_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED4_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED5_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED5_SHIFT	3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED6_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED6_SHIFT	4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED7_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED7_SHIFT	5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED8_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED8_SHIFT	6
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED9_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_MIGRATION_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_MIGRATION_SHIFT	0
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT17_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_BIT17_SHIFT		1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_DPM_PORT_NUM_MASK	0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_DPM_PORT_NUM_SHIFT	2
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RESERVED_MASK		0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_RESERVED_SHIFT		4
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_ROCE_EDPM_ENABLE_MASK	0x1
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_ROCE_EDPM_ENABLE_SHIFT	5
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF23_MASK		0x3
#घोषणा E4XSTORMROCECONNAGCTXDQEXTLDPART_CF23_SHIFT		6
	u8 byte2;
	__le16 physical_q0;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le16 word5;
	__le16 conn_dpi;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 snd_nxt_psn;
	__le32 reg4;
पूर्ण;

काष्ठा e4_mstorm_roce_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_BIT0_MASK     0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_BIT0_SHIFT    0
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_BIT1_MASK     0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_BIT1_SHIFT    1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF0_MASK      0x3
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF0_SHIFT     2
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF1_MASK      0x3
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF1_SHIFT     4
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF2_MASK      0x3
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF2_SHIFT     6
	u8 flags1;
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF0EN_MASK    0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF0EN_SHIFT   0
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF1EN_MASK    0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF1EN_SHIFT   1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF2EN_MASK    0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_CF2EN_SHIFT   2
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE0EN_MASK  0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE0EN_SHIFT 3
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE1EN_MASK  0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE1EN_SHIFT 4
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE2EN_MASK  0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE2EN_SHIFT 5
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE3EN_MASK  0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE3EN_SHIFT 6
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE4EN_MASK  0x1
#घोषणा E4_MSTORM_ROCE_CONN_AG_CTX_RULE4EN_SHIFT 7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_mstorm_roce_req_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_SHIFT	7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_mstorm_roce_resp_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_MSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_SHIFT	7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_tstorm_roce_req_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_EXIST_IN_QM0_SHIFT		0
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RX_ERROR_OCCURRED_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RX_ERROR_OCCURRED_SHIFT		1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TX_CQE_ERROR_OCCURRED_MASK	0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TX_CQE_ERROR_OCCURRED_SHIFT	2
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_BIT3_MASK			0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_BIT3_SHIFT			3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_MSTORM_FLUSH_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_MSTORM_FLUSH_SHIFT		4
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_CACHED_ORQ_MASK			0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_CACHED_ORQ_SHIFT			5
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_CF_MASK			0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_CF_SHIFT			6
	u8 flags1;
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_MSTORM_FLUSH_CF_MASK             0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_MSTORM_FLUSH_CF_SHIFT            0
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_SQ_CF_MASK			0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_SQ_CF_SHIFT		2
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_STOP_ALL_CF_MASK		0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_STOP_ALL_CF_SHIFT		4
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_MASK			0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT		6
	u8 flags2;
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FORCE_COMP_CF_MASK               0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FORCE_COMP_CF_SHIFT              0
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SET_TIMER_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SET_TIMER_CF_SHIFT	2
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TX_ASYNC_ERROR_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TX_ASYNC_ERROR_CF_SHIFT	4
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RXMIT_DONE_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RXMIT_DONE_CF_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_ERROR_SCAN_COMPLETED_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_ERROR_SCAN_COMPLETED_CF_SHIFT	0
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SQ_DRAIN_COMPLETED_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SQ_DRAIN_COMPLETED_CF_SHIFT	2
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_CF_EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_CF_EN_SHIFT		4
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_MSTORM_FLUSH_CF_EN_MASK          0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_MSTORM_FLUSH_CF_EN_SHIFT         5
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_SQ_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_SQ_CF_EN_SHIFT		6
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_STOP_ALL_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TIMER_STOP_ALL_CF_EN_SHIFT	7
	u8 flags4;
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT		0
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FORCE_COMP_CF_EN_MASK            0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_FORCE_COMP_CF_EN_SHIFT           1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SET_TIMER_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SET_TIMER_CF_EN_SHIFT		2
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TX_ASYNC_ERROR_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_TX_ASYNC_ERROR_CF_EN_SHIFT	3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RXMIT_DONE_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RXMIT_DONE_CF_EN_SHIFT		4
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_ERROR_SCAN_COMPLETED_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_ERROR_SCAN_COMPLETED_CF_EN_SHIFT	5
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SQ_DRAIN_COMPLETED_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SQ_DRAIN_COMPLETED_CF_EN_SHIFT	6
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_SHIFT			7
	u8 flags5;
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_SHIFT		0
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_DIF_CNT_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_DIF_CNT_EN_SHIFT		1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_SHIFT		2
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_SHIFT		3
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE5EN_SHIFT		4
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SND_SQ_CONS_EN_MASK	0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_SND_SQ_CONS_EN_SHIFT	5
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE7EN_SHIFT		6
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_REQ_CONN_AG_CTX_RULE8EN_SHIFT		7
	__le32 dअगर_rxmit_cnt;
	__le32 snd_nxt_psn;
	__le32 snd_max_psn;
	__le32 orq_prod;
	__le32 reg4;
	__le32 dअगर_acked_cnt;
	__le32 dअगर_cnt;
	__le32 reg7;
	__le32 reg8;
	u8 tx_cqe_error_type;
	u8 orq_cache_idx;
	__le16 snd_sq_cons_th;
	u8 byte4;
	u8 byte5;
	__le16 snd_sq_cons;
	__le16 conn_dpi;
	__le16 क्रमce_comp_cons;
	__le32 dअगर_rxmit_acked_cnt;
	__le32 reg10;
पूर्ण;

काष्ठा e4_tstorm_roce_resp_conn_ag_ctx अणु
	u8 byte0;
	u8 state;
	u8 flags0;
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_EXIST_IN_QM0_SHIFT		0
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_NOTIFY_REQUESTER_MASK	0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_NOTIFY_REQUESTER_SHIFT	1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_BIT2_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_BIT2_SHIFT			2
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_BIT3_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_BIT3_SHIFT			3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_MSTORM_FLUSH_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_MSTORM_FLUSH_SHIFT		4
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_BIT5_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_BIT5_SHIFT			5
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF0_MASK			0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF0_SHIFT			6
	u8 flags1;
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_MSTORM_FLUSH_CF_MASK            0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_MSTORM_FLUSH_CF_SHIFT           0
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_TX_ERROR_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_TX_ERROR_CF_SHIFT	2
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF3_MASK		0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF3_SHIFT		4
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_MASK	0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT	6
	u8 flags2;
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_MASK                0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_SHIFT               0
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF6_MASK		0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF6_SHIFT		2
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF7_MASK		0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF7_SHIFT		4
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF8_MASK		0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF8_SHIFT		6
	u8 flags3;
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF9_MASK		0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF9_SHIFT		0
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF10_MASK		0x3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF10_SHIFT		2
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_SHIFT		4
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_MSTORM_FLUSH_CF_EN_MASK         0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_MSTORM_FLUSH_CF_EN_SHIFT        5
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_TX_ERROR_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_TX_ERROR_CF_EN_SHIFT	6
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF3EN_SHIFT		7
	u8 flags4;
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT		0
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_EN_MASK             0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_EN_SHIFT            1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF6EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF6EN_SHIFT			2
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF7EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF7EN_SHIFT			3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF8EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF8EN_SHIFT			4
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF9EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF9EN_SHIFT			5
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF10EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_CF10EN_SHIFT			6
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_SHIFT			7
	u8 flags5;
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_SHIFT		0
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_SHIFT		1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_SHIFT		2
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_SHIFT		3
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE5EN_SHIFT		4
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RQ_RULE_EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RQ_RULE_EN_SHIFT	5
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE7EN_SHIFT		6
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_TSTORM_ROCE_RESP_CONN_AG_CTX_RULE8EN_SHIFT		7
	__le32 psn_and_rxmit_id_echo;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le32 reg7;
	__le32 reg8;
	u8 tx_async_error_type;
	u8 byte3;
	__le16 rq_cons;
	u8 byte4;
	u8 byte5;
	__le16 rq_prod;
	__le16 conn_dpi;
	__le16 irq_cons;
	__le32 reg9;
	__le32 reg10;
पूर्ण;

काष्ठा e4_ustorm_roce_req_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF3_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF3_SHIFT	0
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF4_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF4_SHIFT	2
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF5_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF5_SHIFT	4
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF6_MASK		0x3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF6_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF3EN_SHIFT	3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF4EN_SHIFT	4
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF5EN_SHIFT	5
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF6EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_CF6EN_SHIFT	6
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags3;
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE8EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_REQ_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le16 word2;
	__le16 word3;
पूर्ण;

काष्ठा e4_ustorm_roce_resp_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF3_SHIFT	0
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF4_SHIFT	2
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF5_SHIFT	4
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF6_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF3EN_SHIFT	3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF4EN_SHIFT	4
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF5EN_SHIFT	5
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF6EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_CF6EN_SHIFT	6
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags3;
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE8EN_MASK	0x1
#घोषणा E4_USTORM_ROCE_RESP_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le16 word2;
	__le16 word3;
पूर्ण;

काष्ठा e4_xstorm_roce_req_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED1_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED1_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED2_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED2_SHIFT		2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED3_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED3_SHIFT		4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED4_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED4_SHIFT		5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED5_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED5_SHIFT		6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED6_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED6_SHIFT		7
	u8 flags1;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED7_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED7_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED8_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED8_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_BIT10_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_BIT10_SHIFT		2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_BIT11_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MSDM_FLUSH_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MSDM_FLUSH_SHIFT		4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MSEM_FLUSH_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MSEM_FLUSH_SHIFT		5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_ERROR_STATE_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_ERROR_STATE_SHIFT	6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_YSTORM_FLUSH_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_YSTORM_FLUSH_SHIFT	7
	u8 flags2;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF0_SHIFT	0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF1_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF2_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF3_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SQ_FLUSH_CF_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SQ_FLUSH_CF_SHIFT	0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RX_ERROR_CF_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RX_ERROR_CF_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SND_RXMIT_CF_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SND_RXMIT_CF_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_DIF_ERROR_CF_MASK        0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_DIF_ERROR_CF_SHIFT       0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SCAN_SQ_FOR_COMP_CF_MASK     0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SCAN_SQ_FOR_COMP_CF_SHIFT    2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF12_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF12_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF13_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF13_SHIFT		2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FMR_ENDED_CF_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FMR_ENDED_CF_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF15_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF15_SHIFT		6
	u8 flags6;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF16_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF16_SHIFT	0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF17_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF17_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF18_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF18_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF19_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF19_SHIFT	6
	u8 flags7;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF20_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF20_SHIFT	0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF21_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF21_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_SHIFT	6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_SHIFT	7
	u8 flags8;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF3EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SQ_FLUSH_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SQ_FLUSH_CF_EN_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RX_ERROR_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RX_ERROR_CF_EN_SHIFT	3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SND_RXMIT_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SND_RXMIT_CF_EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT	5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_DIF_ERROR_CF_EN_MASK     0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_DIF_ERROR_CF_EN_SHIFT    6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SCAN_SQ_FOR_COMP_CF_EN_MASK  0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SCAN_SQ_FOR_COMP_CF_EN_SHIFT 7
	u8 flags9;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF10EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF10EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF11EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF11EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF12EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF12EN_SHIFT		2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF13EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF13EN_SHIFT		3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FME_ENDED_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_FME_ENDED_CF_EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF15EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF15EN_SHIFT		5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF16EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF16EN_SHIFT		6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF17EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF17EN_SHIFT		7
	u8 flags10;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF18EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF18EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF19EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF19EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF20EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF20EN_SHIFT		2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF21EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF21EN_SHIFT		3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SLOW_PATH_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SLOW_PATH_EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF23EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF23EN_SHIFT		5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_SHIFT		6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_SHIFT		7
	u8 flags11;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_SHIFT		2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE5EN_SHIFT		3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE6EN_SHIFT		4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_E2E_CREDIT_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_E2E_CREDIT_RULE_EN_SHIFT	5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED1_SHIFT	6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE9EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE9EN_SHIFT		7
	u8 flags12;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SQ_PROD_EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_SQ_PROD_EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE11EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE11EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED3_SHIFT	3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_INV_FENCE_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_INV_FENCE_RULE_EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE15EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE15EN_SHIFT		5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_ORQ_FENCE_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_ORQ_FENCE_RULE_EN_SHIFT	6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MAX_ORD_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MAX_ORD_RULE_EN_SHIFT	7
	u8 flags13;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE18EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE18EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE19EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RULE19EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED4_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED5_SHIFT	3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED6_SHIFT	4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED7_SHIFT	5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED8_SHIFT	6
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MIGRATION_FLAG_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_MIGRATION_FLAG_SHIFT	0
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_BIT17_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_BIT17_SHIFT		1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_DPM_PORT_NUM_MASK	0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_DPM_PORT_NUM_SHIFT	2
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED_MASK		0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_RESERVED_SHIFT		4
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_ROCE_EDPM_ENABLE_MASK	0x1
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_ROCE_EDPM_ENABLE_SHIFT	5
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF23_MASK		0x3
#घोषणा E4_XSTORM_ROCE_REQ_CONN_AG_CTX_CF23_SHIFT		6
	u8 byte2;
	__le16 physical_q0;
	__le16 word1;
	__le16 sq_cmp_cons;
	__le16 sq_cons;
	__le16 sq_prod;
	__le16 dअगर_error_first_sq_cons;
	__le16 conn_dpi;
	u8 dअगर_error_sge_index;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 lsn;
	__le32 ssn;
	__le32 snd_una_psn;
	__le32 snd_nxt_psn;
	__le32 dअगर_error_offset;
	__le32 orq_cons_th;
	__le32 orq_cons;
पूर्ण;

काष्ठा e4_xstorm_roce_resp_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED1_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED1_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED2_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED2_SHIFT		2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED3_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED3_SHIFT		4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED4_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED4_SHIFT		5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED5_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED5_SHIFT		6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED6_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED6_SHIFT		7
	u8 flags1;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED7_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED7_SHIFT		0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED8_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RESERVED8_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT10_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT10_SHIFT		2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT11_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_MSDM_FLUSH_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_MSDM_FLUSH_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_MSEM_FLUSH_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_MSEM_FLUSH_SHIFT	5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_ERROR_STATE_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_ERROR_STATE_SHIFT	6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_YSTORM_FLUSH_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_YSTORM_FLUSH_SHIFT	7
	u8 flags2;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF0_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF1_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF2_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RXMIT_CF_MASK		0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RXMIT_CF_SHIFT		0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FORCE_ACK_CF_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FORCE_ACK_CF_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF12_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF12_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF13_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF13_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF14_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF14_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF15_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF16_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF16_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF17_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF17_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF18_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF18_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF19_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF19_SHIFT	6
	u8 flags7;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF20_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF20_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF21_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF21_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_SHIFT	6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_SHIFT	7
	u8 flags8;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF3EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RXMIT_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RXMIT_CF_EN_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RX_ERROR_CF_EN_SHIFT	3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FORCE_ACK_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FORCE_ACK_CF_EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT	5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF8EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF8EN_SHIFT		6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF9EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF9EN_SHIFT		7
	u8 flags9;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF10EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF10EN_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF11EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF11EN_SHIFT	1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF12EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF12EN_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF13EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF13EN_SHIFT	3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF14EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF14EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF15EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF15EN_SHIFT	5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF16EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF16EN_SHIFT	6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF17EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF17EN_SHIFT	7
	u8 flags10;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF18EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF18EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF19EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF19EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF20EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF20EN_SHIFT		2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF21EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF21EN_SHIFT		3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_SLOW_PATH_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_SLOW_PATH_EN_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF23EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF23EN_SHIFT		5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_SHIFT		6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_SHIFT		7
	u8 flags11;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_SHIFT		2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE5EN_SHIFT		3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE6EN_SHIFT		4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE7EN_SHIFT		5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED1_SHIFT	6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE9EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE9EN_SHIFT		7
	u8 flags12;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_IRQ_PROD_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_IRQ_PROD_RULE_EN_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE11EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE11EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED3_SHIFT	3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE14EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE14EN_SHIFT		4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE15EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE15EN_SHIFT		5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE16EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE16EN_SHIFT		6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE17EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE17EN_SHIFT		7
	u8 flags13;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE18EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE18EN_SHIFT		0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE19EN_MASK		0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_RULE19EN_SHIFT		1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED4_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED5_SHIFT	3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED6_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED7_SHIFT	5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED8_SHIFT	6
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_A0_RESERVED9_SHIFT	7
	u8 flags14;
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT16_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT16_SHIFT	0
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT17_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT17_SHIFT	1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT18_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT18_SHIFT	2
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT19_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT19_SHIFT	3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT20_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT20_SHIFT	4
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT21_MASK	0x1
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_BIT21_SHIFT	5
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF23_MASK	0x3
#घोषणा E4_XSTORM_ROCE_RESP_CONN_AG_CTX_CF23_SHIFT	6
	u8 byte2;
	__le16 physical_q0;
	__le16 irq_prod_shaकरोw;
	__le16 word2;
	__le16 irq_cons;
	__le16 irq_prod;
	__le16 e5_reserved1;
	__le16 conn_dpi;
	u8 rxmit_opcode;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 rxmit_psn_and_id;
	__le32 rxmit_bytes_length;
	__le32 psn;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 msn_and_syndrome;
पूर्ण;

काष्ठा e4_ystorm_roce_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_BIT0_MASK     0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_BIT0_SHIFT    0
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_BIT1_MASK     0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_BIT1_SHIFT    1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF0_MASK      0x3
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF0_SHIFT     2
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF1_MASK      0x3
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF1_SHIFT     4
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF2_MASK      0x3
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF2_SHIFT     6
	u8 flags1;
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF0EN_MASK    0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF0EN_SHIFT   0
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF1EN_MASK    0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF1EN_SHIFT   1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF2EN_MASK    0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_CF2EN_SHIFT   2
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE0EN_MASK  0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE0EN_SHIFT 3
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE1EN_MASK  0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE1EN_SHIFT 4
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE2EN_MASK  0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE2EN_SHIFT 5
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE3EN_MASK  0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE3EN_SHIFT 6
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE4EN_MASK  0x1
#घोषणा E4_YSTORM_ROCE_CONN_AG_CTX_RULE4EN_SHIFT 7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

काष्ठा e4_ystorm_roce_req_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_REQ_CONN_AG_CTX_RULE4EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

काष्ठा e4_ystorm_roce_resp_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF0EN_SHIFT	0
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF1EN_SHIFT	1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_CF2EN_SHIFT	2
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_YSTORM_ROCE_RESP_CONN_AG_CTX_RULE4EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

/* Roce करोorbell data */
क्रमागत roce_flavor अणु
	PLAIN_ROCE,
	RROCE_IPV4,
	RROCE_IPV6,
	MAX_ROCE_FLAVOR
पूर्ण;

/* The iwarp storm context of Ystorm */
काष्ठा ystorm_iwarp_conn_st_ctx अणु
	__le32 reserved[4];
पूर्ण;

/* The iwarp storm context of Pstorm */
काष्ठा pstorm_iwarp_conn_st_ctx अणु
	__le32 reserved[36];
पूर्ण;

/* The iwarp storm context of Xstorm */
काष्ठा xstorm_iwarp_conn_st_ctx अणु
	__le32 reserved[48];
पूर्ण;

काष्ठा e4_xstorm_iwarp_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM1_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM1_SHIFT	1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM2_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM2_SHIFT	2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT4_SHIFT		4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RESERVED2_SHIFT	5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT6_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT6_SHIFT		6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT7_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT7_SHIFT		7
	u8 flags1;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT8_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT8_SHIFT				0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT9_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT9_SHIFT				1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT10_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT10_SHIFT				2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT11_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT11_SHIFT				3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT12_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT12_SHIFT				4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT13_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT13_SHIFT				5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT14_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT14_SHIFT				6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_YSTORM_FLUSH_OR_REWIND_SND_MAX_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_YSTORM_FLUSH_OR_REWIND_SND_MAX_SHIFT 7
	u8 flags2;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF0_MASK			0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF0_SHIFT			0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF1_MASK			0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF1_SHIFT			2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF2_MASK			0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF2_SHIFT			4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_MASK		0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF4_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF5_SHIFT	2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF6_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF7_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF12_MASK		0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF12_SHIFT		0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF13_MASK		0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF13_SHIFT		2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_FLUSH_CF_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_FLUSH_CF_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF15_MASK		0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF15_SHIFT		6
	u8 flags6;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_MPA_OR_ERROR_WAKEUP_TRIGGER_CF_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_MPA_OR_ERROR_WAKEUP_TRIGGER_CF_SHIFT 0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF17_MASK				0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF17_SHIFT				2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF18_MASK				0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF18_SHIFT				4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_DQ_FLUSH_MASK			0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_DQ_FLUSH_SHIFT			6
	u8 flags7;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q1_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q1_SHIFT	2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF0EN_SHIFT		6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF1EN_SHIFT		7
	u8 flags8;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF2EN_SHIFT			0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_EN_SHIFT	1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF4EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF4EN_SHIFT			2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF5EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF5EN_SHIFT			3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF6EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF6EN_SHIFT			4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF7EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF7EN_SHIFT			5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF8EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF8EN_SHIFT			6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF9EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF9EN_SHIFT			7
	u8 flags9;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF10EN_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF10EN_SHIFT			0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF11EN_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF11EN_SHIFT			1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF12EN_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF12EN_SHIFT			2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF13EN_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF13EN_SHIFT			3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_FLUSH_CF_EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_FLUSH_CF_EN_SHIFT		4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF15EN_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF15EN_SHIFT			5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_MPA_OR_ERROR_WAKEUP_TRIGGER_CF_EN_MASK 0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_MPA_OR_ERROR_WAKEUP_TRIGGER_CF_EN_SHIFT 6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF17EN_MASK				0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF17EN_SHIFT			7
	u8 flags10;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF18EN_MASK			0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_CF18EN_SHIFT		0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_DQ_FLUSH_EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_DQ_FLUSH_EN_SHIFT		1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_EN_SHIFT		2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q1_EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_FLUSH_Q1_EN_SHIFT		3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SLOW_PATH_EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SLOW_PATH_EN_SHIFT		4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SEND_TERMINATE_CF_EN_MASK               0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SEND_TERMINATE_CF_EN_SHIFT              5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE0EN_SHIFT		6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_MORE_TO_SEND_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_MORE_TO_SEND_RULE_EN_SHIFT	7
	u8 flags11;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_TX_BLOCKED_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_TX_BLOCKED_EN_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE3EN_SHIFT	1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RESERVED3_SHIFT	2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE5EN_SHIFT	3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE6EN_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE7EN_SHIFT	5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED1_SHIFT	6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE9EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE9EN_SHIFT	7
	u8 flags12;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_NOT_EMPTY_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_NOT_EMPTY_RULE_EN_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE11EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE11EN_SHIFT		1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED2_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED2_SHIFT		2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED3_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED3_SHIFT		3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_FENCE_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SQ_FENCE_RULE_EN_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE15EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE15EN_SHIFT		5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE16EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE16EN_SHIFT		6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE17EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE17EN_SHIFT		7
	u8 flags13;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_IRQ_NOT_EMPTY_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_IRQ_NOT_EMPTY_RULE_EN_SHIFT	0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_HQ_NOT_FULL_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_HQ_NOT_FULL_RULE_EN_SHIFT	1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_ORQ_RD_FENCE_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_ORQ_RD_FENCE_RULE_EN_SHIFT	2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE21EN_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_RULE21EN_SHIFT		3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED6_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED6_SHIFT		4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_ORQ_NOT_FULL_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_ORQ_NOT_FULL_RULE_EN_SHIFT	5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED8_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED8_SHIFT		6
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED9_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_A0_RESERVED9_SHIFT		7
	u8 flags14;
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT16_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT16_SHIFT		0
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT17_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT17_SHIFT		1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT18_MASK		0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_BIT18_SHIFT		2
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_E5_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_E5_RESERVED1_SHIFT	3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_E5_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_E5_RESERVED2_SHIFT	4
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_E5_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_E5_RESERVED3_SHIFT	5
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SEND_TERMINATE_CF_MASK	0x3
#घोषणा E4_XSTORM_IWARP_CONN_AG_CTX_SEND_TERMINATE_CF_SHIFT	6
	u8 byte2;
	__le16 physical_q0;
	__le16 physical_q1;
	__le16 sq_comp_cons;
	__le16 sq_tx_cons;
	__le16 sq_prod;
	__le16 word5;
	__le16 conn_dpi;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 more_to_send_seq;
	__le32 reg4;
	__le32 शुरुआतed_snd_max_or_term_opcode;
	__le32 rd_msn;
	__le16 irq_prod_via_msdm;
	__le16 irq_cons;
	__le16 hq_cons_th_or_mpa_data;
	__le16 hq_cons;
	__le32 atom_msn;
	__le32 orq_cons;
	__le32 orq_cons_th;
	u8 byte7;
	u8 wqe_data_pad_bytes;
	u8 max_ord;
	u8 क्रमmer_hq_prod;
	u8 irq_prod_via_msem;
	u8 byte12;
	u8 max_pkt_pdu_size_lo;
	u8 max_pkt_pdu_size_hi;
	u8 byte15;
	u8 e5_reserved;
	__le16 e5_reserved4;
	__le32 reg10;
	__le32 reg11;
	__le32 shared_queue_page_addr_lo;
	__le32 shared_queue_page_addr_hi;
	__le32 reg14;
	__le32 reg15;
	__le32 reg16;
	__le32 reg17;
पूर्ण;

काष्ठा e4_tstorm_iwarp_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_BIT1_SHIFT		1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_BIT2_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_BIT2_SHIFT		2
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_MSTORM_FLUSH_OR_TERMINATE_SENT_MASK  0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_MSTORM_FLUSH_OR_TERMINATE_SENT_SHIFT 3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_BIT4_SHIFT		4
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CACHED_ORQ_MASK	0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CACHED_ORQ_SHIFT	5
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF0_SHIFT		6
	u8 flags1;
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RQ_POST_CF_MASK		0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RQ_POST_CF_SHIFT		0
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_MPA_TIMEOUT_CF_MASK		0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_MPA_TIMEOUT_CF_SHIFT	2
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_MASK		0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_SHIFT	4
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF4_MASK			0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF4_SHIFT			6
	u8 flags2;
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF5_SHIFT	0
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF6_SHIFT	2
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF7_SHIFT	4
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF8_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_AND_TCP_HANDSHAKE_COMPLETE_MASK 0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_AND_TCP_HANDSHAKE_COMPLETE_SHIFT 0
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_OR_ERROR_DETECTED_MASK	0x3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_OR_ERROR_DETECTED_SHIFT	2
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF0EN_MASK				0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF0EN_SHIFT				4
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RQ_POST_CF_EN_MASK			0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RQ_POST_CF_EN_SHIFT			5
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_MPA_TIMEOUT_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_MPA_TIMEOUT_CF_EN_SHIFT		6
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_TIMER_STOP_ALL_EN_SHIFT		7
	u8 flags4;
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF4EN_MASK				0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF4EN_SHIFT				0
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF5EN_MASK				0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF5EN_SHIFT				1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF6EN_MASK				0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF6EN_SHIFT				2
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF7EN_MASK				0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF7EN_SHIFT				3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF8EN_MASK				0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_CF8EN_SHIFT				4
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_AND_TCP_HANDSHAKE_COMPL_EN_MASK 0x1
#घोषणा	E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_Q0_AND_TCP_HANDSHAKE_COMPL_EN_SHIFT 5
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_OR_ERROR_DETECTED_EN_MASK	0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_FLUSH_OR_ERROR_DETECTED_EN_SHIFT	6
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE0EN_SHIFT			7
	u8 flags5;
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE1EN_SHIFT		0
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE2EN_SHIFT		1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE3EN_SHIFT		2
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE4EN_SHIFT		3
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE5EN_SHIFT		4
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_SND_SQ_CONS_RULE_MASK	0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_SND_SQ_CONS_RULE_SHIFT	5
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE7EN_SHIFT		6
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_TSTORM_IWARP_CONN_AG_CTX_RULE8EN_SHIFT		7
	__le32 reg0;
	__le32 reg1;
	__le32 unaligned_nxt_seq;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le32 reg7;
	__le32 reg8;
	u8 orq_cache_idx;
	u8 hq_prod;
	__le16 sq_tx_cons_th;
	u8 orq_prod;
	u8 irq_cons;
	__le16 sq_tx_cons;
	__le16 conn_dpi;
	__le16 rq_prod;
	__le32 snd_seq;
	__le32 last_hq_sequence;
पूर्ण;

/* The iwarp storm context of Tstorm */
काष्ठा tstorm_iwarp_conn_st_ctx अणु
	__le32 reserved[60];
पूर्ण;

/* The iwarp storm context of Mstorm */
काष्ठा mstorm_iwarp_conn_st_ctx अणु
	__le32 reserved[32];
पूर्ण;

/* The iwarp storm context of Ustorm */
काष्ठा ustorm_iwarp_conn_st_ctx अणु
	काष्ठा regpair reserved[14];
पूर्ण;

/* iwarp connection context */
काष्ठा e4_iwarp_conn_context अणु
	काष्ठा ystorm_iwarp_conn_st_ctx ystorm_st_context;
	काष्ठा regpair ystorm_st_padding[2];
	काष्ठा pstorm_iwarp_conn_st_ctx pstorm_st_context;
	काष्ठा regpair pstorm_st_padding[2];
	काष्ठा xstorm_iwarp_conn_st_ctx xstorm_st_context;
	काष्ठा e4_xstorm_iwarp_conn_ag_ctx xstorm_ag_context;
	काष्ठा e4_tstorm_iwarp_conn_ag_ctx tstorm_ag_context;
	काष्ठा समयrs_context समयr_context;
	काष्ठा e4_ustorm_rdma_conn_ag_ctx ustorm_ag_context;
	काष्ठा tstorm_iwarp_conn_st_ctx tstorm_st_context;
	काष्ठा regpair tstorm_st_padding[2];
	काष्ठा mstorm_iwarp_conn_st_ctx mstorm_st_context;
	काष्ठा ustorm_iwarp_conn_st_ctx ustorm_st_context;
	काष्ठा regpair ustorm_st_padding[2];
पूर्ण;

/* iWARP create QP params passed by driver to FW in CreateQP Request Ramrod */
काष्ठा iwarp_create_qp_ramrod_data अणु
	u8 flags;
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN_MASK	0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN_SHIFT	0
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP_MASK		0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP_SHIFT		1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN_MASK		0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN_SHIFT		2
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN_MASK		0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN_SHIFT		3
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN_MASK		0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN_SHIFT		4
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG_MASK		0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG_SHIFT		5
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_LOW_LATENCY_QUEUE_EN_MASK	0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_LOW_LATENCY_QUEUE_EN_SHIFT	6
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_RESERVED0_MASK		0x1
#घोषणा IWARP_CREATE_QP_RAMROD_DATA_RESERVED0_SHIFT		7
	u8 reserved1;
	__le16 pd;
	__le16 sq_num_pages;
	__le16 rq_num_pages;
	__le32 reserved3[2];
	काष्ठा regpair qp_handle_क्रम_cqe;
	काष्ठा rdma_srq_id srq_id;
	__le32 cq_cid_क्रम_sq;
	__le32 cq_cid_क्रम_rq;
	__le16 dpi;
	__le16 physical_q0;
	__le16 physical_q1;
	u8 reserved2[6];
पूर्ण;

/* iWARP completion queue types */
क्रमागत iwarp_eqe_async_opcode अणु
	IWARP_EVENT_TYPE_ASYNC_CONNECT_COMPLETE,
	IWARP_EVENT_TYPE_ASYNC_ENHANCED_MPA_REPLY_ARRIVED,
	IWARP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPLETE,
	IWARP_EVENT_TYPE_ASYNC_CID_CLEANED,
	IWARP_EVENT_TYPE_ASYNC_EXCEPTION_DETECTED,
	IWARP_EVENT_TYPE_ASYNC_QP_IN_ERROR_STATE,
	IWARP_EVENT_TYPE_ASYNC_CQ_OVERFLOW,
	IWARP_EVENT_TYPE_ASYNC_SRQ_EMPTY,
	IWARP_EVENT_TYPE_ASYNC_SRQ_LIMIT,
	MAX_IWARP_EQE_ASYNC_OPCODE
पूर्ण;

काष्ठा iwarp_eqe_data_mpa_async_completion अणु
	__le16 ulp_data_len;
	u8 rtr_type_sent;
	u8 reserved[5];
पूर्ण;

काष्ठा iwarp_eqe_data_tcp_async_completion अणु
	__le16 ulp_data_len;
	u8 mpa_handshake_mode;
	u8 reserved[5];
पूर्ण;

/* iWARP completion queue types */
क्रमागत iwarp_eqe_sync_opcode अणु
	IWARP_EVENT_TYPE_TCP_OFFLOAD =
	11,
	IWARP_EVENT_TYPE_MPA_OFFLOAD,
	IWARP_EVENT_TYPE_MPA_OFFLOAD_SEND_RTR,
	IWARP_EVENT_TYPE_CREATE_QP,
	IWARP_EVENT_TYPE_QUERY_QP,
	IWARP_EVENT_TYPE_MODIFY_QP,
	IWARP_EVENT_TYPE_DESTROY_QP,
	IWARP_EVENT_TYPE_ABORT_TCP_OFFLOAD,
	MAX_IWARP_EQE_SYNC_OPCODE
पूर्ण;

/* iWARP EQE completion status */
क्रमागत iwarp_fw_वापस_code अणु
	IWARP_CONN_ERROR_TCP_CONNECT_INVALID_PACKET = 6,
	IWARP_CONN_ERROR_TCP_CONNECTION_RST,
	IWARP_CONN_ERROR_TCP_CONNECT_TIMEOUT,
	IWARP_CONN_ERROR_MPA_ERROR_REJECT,
	IWARP_CONN_ERROR_MPA_NOT_SUPPORTED_VER,
	IWARP_CONN_ERROR_MPA_RST,
	IWARP_CONN_ERROR_MPA_FIN,
	IWARP_CONN_ERROR_MPA_RTR_MISMATCH,
	IWARP_CONN_ERROR_MPA_INSUF_IRD,
	IWARP_CONN_ERROR_MPA_INVALID_PACKET,
	IWARP_CONN_ERROR_MPA_LOCAL_ERROR,
	IWARP_CONN_ERROR_MPA_TIMEOUT,
	IWARP_CONN_ERROR_MPA_TERMINATE,
	IWARP_QP_IN_ERROR_GOOD_CLOSE,
	IWARP_QP_IN_ERROR_BAD_CLOSE,
	IWARP_EXCEPTION_DETECTED_LLP_CLOSED,
	IWARP_EXCEPTION_DETECTED_LLP_RESET,
	IWARP_EXCEPTION_DETECTED_IRQ_FULL,
	IWARP_EXCEPTION_DETECTED_RQ_EMPTY,
	IWARP_EXCEPTION_DETECTED_SRQ_EMPTY,
	IWARP_EXCEPTION_DETECTED_SRQ_LIMIT,
	IWARP_EXCEPTION_DETECTED_LLP_TIMEOUT,
	IWARP_EXCEPTION_DETECTED_REMOTE_PROTECTION_ERROR,
	IWARP_EXCEPTION_DETECTED_CQ_OVERFLOW,
	IWARP_EXCEPTION_DETECTED_LOCAL_CATASTROPHIC,
	IWARP_EXCEPTION_DETECTED_LOCAL_ACCESS_ERROR,
	IWARP_EXCEPTION_DETECTED_REMOTE_OPERATION_ERROR,
	IWARP_EXCEPTION_DETECTED_TERMINATE_RECEIVED,
	MAX_IWARP_FW_RETURN_CODE
पूर्ण;

/* unaligned opaque data received from LL2 */
काष्ठा iwarp_init_func_params अणु
	u8 ll2_ooo_q_index;
	u8 reserved1[7];
पूर्ण;

/* iwarp func init ramrod data */
काष्ठा iwarp_init_func_ramrod_data अणु
	काष्ठा rdma_init_func_ramrod_data rdma;
	काष्ठा tcp_init_params tcp;
	काष्ठा iwarp_init_func_params iwarp;
पूर्ण;

/* iWARP QP - possible states to transition to */
क्रमागत iwarp_modअगरy_qp_new_state_type अणु
	IWARP_MODIFY_QP_STATE_CLOSING = 1,
	IWARP_MODIFY_QP_STATE_ERROR = 2,
	MAX_IWARP_MODIFY_QP_NEW_STATE_TYPE
पूर्ण;

/* iwarp modअगरy qp responder ramrod data */
काष्ठा iwarp_modअगरy_qp_ramrod_data अणु
	__le16 transition_to_state;
	__le16 flags;
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RDMA_RD_EN_MASK		0x1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RDMA_RD_EN_SHIFT		0
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RDMA_WR_EN_MASK		0x1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RDMA_WR_EN_SHIFT		1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_ATOMIC_EN_MASK		0x1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_ATOMIC_EN_SHIFT		2
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_STATE_TRANS_EN_MASK		0x1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_STATE_TRANS_EN_SHIFT	3
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RDMA_OPS_EN_FLG_MASK	0x1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RDMA_OPS_EN_FLG_SHIFT	4
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_PHYSICAL_QUEUE_FLG_MASK	0x1
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_PHYSICAL_QUEUE_FLG_SHIFT	5
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RESERVED_MASK		0x3FF
#घोषणा IWARP_MODIFY_QP_RAMROD_DATA_RESERVED_SHIFT		6
	__le16 physical_q0;
	__le16 physical_q1;
	__le32 reserved1[10];
पूर्ण;

/* MPA params क्रम Enhanced mode */
काष्ठा mpa_rq_params अणु
	__le32 ird;
	__le32 ord;
पूर्ण;

/* MPA host Address-Len क्रम निजी data */
काष्ठा mpa_ulp_buffer अणु
	काष्ठा regpair addr;
	__le16 len;
	__le16 reserved[3];
पूर्ण;

/* iWARP MPA offload params common to Basic and Enhanced modes */
काष्ठा mpa_outgoing_params अणु
	u8 crc_needed;
	u8 reject;
	u8 reserved[6];
	काष्ठा mpa_rq_params out_rq;
	काष्ठा mpa_ulp_buffer outgoing_ulp_buffer;
पूर्ण;

/* iWARP MPA offload params passed by driver to FW in MPA Offload Request
 * Ramrod.
 */
काष्ठा iwarp_mpa_offload_ramrod_data अणु
	काष्ठा mpa_outgoing_params common;
	__le32 tcp_cid;
	u8 mode;
	u8 tcp_connect_side;
	u8 rtr_pref;
#घोषणा IWARP_MPA_OFFLOAD_RAMROD_DATA_RTR_SUPPORTED_MASK	0x7
#घोषणा IWARP_MPA_OFFLOAD_RAMROD_DATA_RTR_SUPPORTED_SHIFT	0
#घोषणा IWARP_MPA_OFFLOAD_RAMROD_DATA_RESERVED1_MASK		0x1F
#घोषणा IWARP_MPA_OFFLOAD_RAMROD_DATA_RESERVED1_SHIFT		3
	u8 reserved2;
	काष्ठा mpa_ulp_buffer incoming_ulp_buffer;
	काष्ठा regpair async_eqe_output_buf;
	काष्ठा regpair handle_क्रम_async;
	काष्ठा regpair shared_queue_addr;
	__le16 rcv_wnd;
	u8 stats_counter_id;
	u8 reserved3[13];
पूर्ण;

/* iWARP TCP connection offload params passed by driver to FW */
काष्ठा iwarp_offload_params अणु
	काष्ठा mpa_ulp_buffer incoming_ulp_buffer;
	काष्ठा regpair async_eqe_output_buf;
	काष्ठा regpair handle_क्रम_async;
	__le16 physical_q0;
	__le16 physical_q1;
	u8 stats_counter_id;
	u8 mpa_mode;
	u8 reserved[10];
पूर्ण;

/* iWARP query QP output params */
काष्ठा iwarp_query_qp_output_params अणु
	__le32 flags;
#घोषणा IWARP_QUERY_QP_OUTPUT_PARAMS_ERROR_FLG_MASK	0x1
#घोषणा IWARP_QUERY_QP_OUTPUT_PARAMS_ERROR_FLG_SHIFT	0
#घोषणा IWARP_QUERY_QP_OUTPUT_PARAMS_RESERVED0_MASK	0x7FFFFFFF
#घोषणा IWARP_QUERY_QP_OUTPUT_PARAMS_RESERVED0_SHIFT	1
	u8 reserved1[4];
पूर्ण;

/* iWARP query QP ramrod data */
काष्ठा iwarp_query_qp_ramrod_data अणु
	काष्ठा regpair output_params_addr;
पूर्ण;

/* iWARP Ramrod Command IDs */
क्रमागत iwarp_ramrod_cmd_id अणु
	IWARP_RAMROD_CMD_ID_TCP_OFFLOAD = 11,
	IWARP_RAMROD_CMD_ID_MPA_OFFLOAD,
	IWARP_RAMROD_CMD_ID_MPA_OFFLOAD_SEND_RTR,
	IWARP_RAMROD_CMD_ID_CREATE_QP,
	IWARP_RAMROD_CMD_ID_QUERY_QP,
	IWARP_RAMROD_CMD_ID_MODIFY_QP,
	IWARP_RAMROD_CMD_ID_DESTROY_QP,
	IWARP_RAMROD_CMD_ID_ABORT_TCP_OFFLOAD,
	MAX_IWARP_RAMROD_CMD_ID
पूर्ण;

/* Per PF iWARP retransmit path statistics */
काष्ठा iwarp_rxmit_stats_drv अणु
	काष्ठा regpair tx_go_to_slow_start_event_cnt;
	काष्ठा regpair tx_fast_retransmit_event_cnt;
पूर्ण;

/* iWARP and TCP connection offload params passed by driver to FW in iWARP
 * offload ramrod.
 */
काष्ठा iwarp_tcp_offload_ramrod_data अणु
	काष्ठा tcp_offload_params_opt2 tcp;
	काष्ठा iwarp_offload_params iwarp;
पूर्ण;

/* iWARP MPA negotiation types */
क्रमागत mpa_negotiation_mode अणु
	MPA_NEGOTIATION_TYPE_BASIC = 1,
	MPA_NEGOTIATION_TYPE_ENHANCED = 2,
	MAX_MPA_NEGOTIATION_MODE
पूर्ण;

/* iWARP MPA Enhanced mode RTR types */
क्रमागत mpa_rtr_type अणु
	MPA_RTR_TYPE_NONE = 0,
	MPA_RTR_TYPE_ZERO_SEND = 1,
	MPA_RTR_TYPE_ZERO_WRITE = 2,
	MPA_RTR_TYPE_ZERO_SEND_AND_WRITE = 3,
	MPA_RTR_TYPE_ZERO_READ = 4,
	MPA_RTR_TYPE_ZERO_SEND_AND_READ = 5,
	MPA_RTR_TYPE_ZERO_WRITE_AND_READ = 6,
	MPA_RTR_TYPE_ZERO_SEND_AND_WRITE_AND_READ = 7,
	MAX_MPA_RTR_TYPE
पूर्ण;

/* unaligned opaque data received from LL2 */
काष्ठा unaligned_opaque_data अणु
	__le16 first_mpa_offset;
	u8 tcp_payload_offset;
	u8 flags;
#घोषणा UNALIGNED_OPAQUE_DATA_PKT_REACHED_WIN_RIGHT_EDGE_MASK	0x1
#घोषणा UNALIGNED_OPAQUE_DATA_PKT_REACHED_WIN_RIGHT_EDGE_SHIFT	0
#घोषणा UNALIGNED_OPAQUE_DATA_CONNECTION_CLOSED_MASK		0x1
#घोषणा UNALIGNED_OPAQUE_DATA_CONNECTION_CLOSED_SHIFT		1
#घोषणा UNALIGNED_OPAQUE_DATA_RESERVED_MASK			0x3F
#घोषणा UNALIGNED_OPAQUE_DATA_RESERVED_SHIFT			2
	__le32 cid;
पूर्ण;

काष्ठा e4_mstorm_iwarp_conn_ag_ctx अणु
	u8 reserved;
	u8 state;
	u8 flags0;
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_SHIFT		0
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_BIT1_SHIFT			1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_INV_STAG_DONE_CF_MASK	0x3
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_INV_STAG_DONE_CF_SHIFT	2
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF1_MASK			0x3
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF1_SHIFT			4
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF2_MASK			0x3
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF2_SHIFT			6
	u8 flags1;
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_INV_STAG_DONE_CF_EN_MASK	0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_INV_STAG_DONE_CF_EN_SHIFT	0
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF1EN_MASK			0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF1EN_SHIFT			1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_CF2EN_SHIFT			2
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE0EN_SHIFT		3
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE1EN_SHIFT		4
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE2EN_SHIFT		5
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RCQ_CONS_EN_MASK		0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RCQ_CONS_EN_SHIFT		6
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_MSTORM_IWARP_CONN_AG_CTX_RULE4EN_SHIFT		7
	__le16 rcq_cons;
	__le16 rcq_cons_th;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_ustorm_iwarp_conn_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_BIT1_SHIFT		1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF0_SHIFT		2
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF1_MASK		0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF1_SHIFT		4
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF2_MASK		0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF2_SHIFT		6
	u8 flags1;
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF3_MASK		0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF3_SHIFT		0
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_SE_CF_MASK	0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_SE_CF_SHIFT	2
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_CF_MASK	0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_CF_SHIFT	4
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF6_MASK		0x3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF6_SHIFT		6
	u8 flags2;
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF0EN_MASK			0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF0EN_SHIFT			0
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF1EN_MASK			0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF1EN_SHIFT			1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF2EN_SHIFT			2
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF3EN_MASK			0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF3EN_SHIFT			3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_SE_CF_EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_SE_CF_EN_SHIFT	4
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_CF_EN_MASK		0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_ARM_CF_EN_SHIFT		5
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF6EN_MASK			0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CF6EN_SHIFT			6
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_SE_EN_MASK		0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_SE_EN_SHIFT		7
	u8 flags3;
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_EN_MASK		0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_CQ_EN_SHIFT		0
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE8EN_MASK	0x1
#घोषणा E4_USTORM_IWARP_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 word1;
	__le32 cq_cons;
	__le32 cq_se_prod;
	__le32 cq_prod;
	__le32 reg3;
	__le16 word2;
	__le16 word3;
पूर्ण;

काष्ठा e4_ystorm_iwarp_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_YSTORM_IWARP_CONN_AG_CTX_RULE4EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

/* The fcoe storm context of Ystorm */
काष्ठा ystorm_fcoe_conn_st_ctx अणु
	u8 func_mode;
	u8 cos;
	u8 conf_version;
	u8 eth_hdr_size;
	__le16 stat_ram_addr;
	__le16 mtu;
	__le16 max_fc_payload_len;
	__le16 tx_max_fc_pay_len;
	u8 fcp_cmd_size;
	u8 fcp_rsp_size;
	__le16 mss;
	काष्ठा regpair reserved;
	__le16 min_frame_size;
	u8 protection_info_flags;
#घोषणा YSTORM_FCOE_CONN_ST_CTX_SUPPORT_PROTECTION_MASK		0x1
#घोषणा YSTORM_FCOE_CONN_ST_CTX_SUPPORT_PROTECTION_SHIFT	0
#घोषणा YSTORM_FCOE_CONN_ST_CTX_VALID_MASK			0x1
#घोषणा YSTORM_FCOE_CONN_ST_CTX_VALID_SHIFT			1
#घोषणा YSTORM_FCOE_CONN_ST_CTX_RESERVED1_MASK			0x3F
#घोषणा YSTORM_FCOE_CONN_ST_CTX_RESERVED1_SHIFT			2
	u8 dst_protection_per_mss;
	u8 src_protection_per_mss;
	u8 ptu_log_page_size;
	u8 flags;
#घोषणा YSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_MASK	0x1
#घोषणा YSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_SHIFT	0
#घोषणा YSTORM_FCOE_CONN_ST_CTX_OUTER_VLAN_FLAG_MASK	0x1
#घोषणा YSTORM_FCOE_CONN_ST_CTX_OUTER_VLAN_FLAG_SHIFT	1
#घोषणा YSTORM_FCOE_CONN_ST_CTX_RSRV_MASK		0x3F
#घोषणा YSTORM_FCOE_CONN_ST_CTX_RSRV_SHIFT		2
	u8 fcp_xfer_size;
पूर्ण;

/* FCoE 16-bits vlan काष्ठाure */
काष्ठा fcoe_vlan_fields अणु
	__le16 fields;
#घोषणा FCOE_VLAN_FIELDS_VID_MASK	0xFFF
#घोषणा FCOE_VLAN_FIELDS_VID_SHIFT	0
#घोषणा FCOE_VLAN_FIELDS_CLI_MASK	0x1
#घोषणा FCOE_VLAN_FIELDS_CLI_SHIFT	12
#घोषणा FCOE_VLAN_FIELDS_PRI_MASK	0x7
#घोषणा FCOE_VLAN_FIELDS_PRI_SHIFT	13
पूर्ण;

/* FCoE 16-bits vlan जोड़ */
जोड़ fcoe_vlan_field_जोड़ अणु
	काष्ठा fcoe_vlan_fields fields;
	__le16 val;
पूर्ण;

/* FCoE 16-bits vlan, vअगर जोड़ */
जोड़ fcoe_vlan_vअगर_field_जोड़ अणु
	जोड़ fcoe_vlan_field_जोड़ vlan;
	__le16 vअगर;
पूर्ण;

/* Ethernet context section */
काष्ठा pstorm_fcoe_eth_context_section अणु
	u8 remote_addr_3;
	u8 remote_addr_2;
	u8 remote_addr_1;
	u8 remote_addr_0;
	u8 local_addr_1;
	u8 local_addr_0;
	u8 remote_addr_5;
	u8 remote_addr_4;
	u8 local_addr_5;
	u8 local_addr_4;
	u8 local_addr_3;
	u8 local_addr_2;
	जोड़ fcoe_vlan_vअगर_field_जोड़ vअगर_outer_vlan;
	__le16 vअगर_outer_eth_type;
	जोड़ fcoe_vlan_vअगर_field_जोड़ inner_vlan;
	__le16 inner_eth_type;
पूर्ण;

/* The fcoe storm context of Pstorm */
काष्ठा pstorm_fcoe_conn_st_ctx अणु
	u8 func_mode;
	u8 cos;
	u8 conf_version;
	u8 rsrv;
	__le16 stat_ram_addr;
	__le16 mss;
	काष्ठा regpair abts_cleanup_addr;
	काष्ठा pstorm_fcoe_eth_context_section eth;
	u8 sid_2;
	u8 sid_1;
	u8 sid_0;
	u8 flags;
#घोषणा PSTORM_FCOE_CONN_ST_CTX_VNTAG_VLAN_MASK			0x1
#घोषणा PSTORM_FCOE_CONN_ST_CTX_VNTAG_VLAN_SHIFT		0
#घोषणा PSTORM_FCOE_CONN_ST_CTX_SUPPORT_REC_RR_TOV_MASK		0x1
#घोषणा PSTORM_FCOE_CONN_ST_CTX_SUPPORT_REC_RR_TOV_SHIFT	1
#घोषणा PSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_MASK		0x1
#घोषणा PSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_SHIFT		2
#घोषणा PSTORM_FCOE_CONN_ST_CTX_OUTER_VLAN_FLAG_MASK		0x1
#घोषणा PSTORM_FCOE_CONN_ST_CTX_OUTER_VLAN_FLAG_SHIFT		3
#घोषणा PSTORM_FCOE_CONN_ST_CTX_SINGLE_VLAN_FLAG_MASK		0x1
#घोषणा PSTORM_FCOE_CONN_ST_CTX_SINGLE_VLAN_FLAG_SHIFT		4
#घोषणा PSTORM_FCOE_CONN_ST_CTX_RESERVED_MASK			0x7
#घोषणा PSTORM_FCOE_CONN_ST_CTX_RESERVED_SHIFT			5
	u8 did_2;
	u8 did_1;
	u8 did_0;
	u8 src_mac_index;
	__le16 rec_rr_tov_val;
	u8 q_relative_offset;
	u8 reserved1;
पूर्ण;

/* The fcoe storm context of Xstorm */
काष्ठा xstorm_fcoe_conn_st_ctx अणु
	u8 func_mode;
	u8 src_mac_index;
	u8 conf_version;
	u8 cached_wqes_avail;
	__le16 stat_ram_addr;
	u8 flags;
#घोषणा XSTORM_FCOE_CONN_ST_CTX_SQ_DEFERRED_MASK		0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_SQ_DEFERRED_SHIFT		0
#घोषणा XSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_MASK		0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_SHIFT		1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_ORIG_MASK	0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_INNER_VLAN_FLAG_ORIG_SHIFT	2
#घोषणा XSTORM_FCOE_CONN_ST_CTX_LAST_QUEUE_HANDLED_MASK		0x3
#घोषणा XSTORM_FCOE_CONN_ST_CTX_LAST_QUEUE_HANDLED_SHIFT	3
#घोषणा XSTORM_FCOE_CONN_ST_CTX_RSRV_MASK			0x7
#घोषणा XSTORM_FCOE_CONN_ST_CTX_RSRV_SHIFT			5
	u8 cached_wqes_offset;
	u8 reserved2;
	u8 eth_hdr_size;
	u8 seq_id;
	u8 max_conc_seqs;
	__le16 num_pages_in_pbl;
	__le16 reserved;
	काष्ठा regpair sq_pbl_addr;
	काष्ठा regpair sq_curr_page_addr;
	काष्ठा regpair sq_next_page_addr;
	काष्ठा regpair xferq_pbl_addr;
	काष्ठा regpair xferq_curr_page_addr;
	काष्ठा regpair xferq_next_page_addr;
	काष्ठा regpair respq_pbl_addr;
	काष्ठा regpair respq_curr_page_addr;
	काष्ठा regpair respq_next_page_addr;
	__le16 mtu;
	__le16 tx_max_fc_pay_len;
	__le16 max_fc_payload_len;
	__le16 min_frame_size;
	__le16 sq_pbl_next_index;
	__le16 respq_pbl_next_index;
	u8 fcp_cmd_byte_credit;
	u8 fcp_rsp_byte_credit;
	__le16 protection_info;
#घोषणा XSTORM_FCOE_CONN_ST_CTX_PROTECTION_PERF_MASK		0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_PROTECTION_PERF_SHIFT		0
#घोषणा XSTORM_FCOE_CONN_ST_CTX_SUPPORT_PROTECTION_MASK		0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_SUPPORT_PROTECTION_SHIFT	1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_VALID_MASK			0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_VALID_SHIFT			2
#घोषणा XSTORM_FCOE_CONN_ST_CTX_FRAME_PROT_ALIGNED_MASK		0x1
#घोषणा XSTORM_FCOE_CONN_ST_CTX_FRAME_PROT_ALIGNED_SHIFT	3
#घोषणा XSTORM_FCOE_CONN_ST_CTX_RESERVED3_MASK			0xF
#घोषणा XSTORM_FCOE_CONN_ST_CTX_RESERVED3_SHIFT			4
#घोषणा XSTORM_FCOE_CONN_ST_CTX_DST_PROTECTION_PER_MSS_MASK	0xFF
#घोषणा XSTORM_FCOE_CONN_ST_CTX_DST_PROTECTION_PER_MSS_SHIFT	8
	__le16 xferq_pbl_next_index;
	__le16 page_size;
	u8 mid_seq;
	u8 fcp_xfer_byte_credit;
	u8 reserved1[2];
	काष्ठा fcoe_wqe cached_wqes[16];
पूर्ण;

काष्ठा e4_xstorm_fcoe_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED1_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED3_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED4_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED4_SHIFT	5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED5_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED5_SHIFT	6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED6_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED6_SHIFT	7
	u8 flags1;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED7_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED7_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED8_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED8_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED9_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED9_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT11_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT12_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT12_SHIFT		4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT13_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT13_SHIFT		5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT14_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT14_SHIFT		6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT15_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT15_SHIFT		7
	u8 flags2;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF0_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF1_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF2_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF3_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF4_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF5_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF6_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF7_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF12_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF12_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF13_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF13_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF14_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF14_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF15_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF15_SHIFT	6
	u8 flags6;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF16_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF16_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF17_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF17_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF18_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF18_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_DQ_CF_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_DQ_CF_SHIFT	6
	u8 flags7;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED10_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED10_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_SLOW_PATH_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_SLOW_PATH_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF0EN_SHIFT		6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF1EN_SHIFT		7
	u8 flags8;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF2EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF2EN_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF3EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF3EN_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF4EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF4EN_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF5EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF5EN_SHIFT	3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF6EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF6EN_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF7EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF7EN_SHIFT	5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF8EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF8EN_SHIFT	6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF9EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF9EN_SHIFT	7
	u8 flags9;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF10EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF10EN_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF11EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF11EN_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF12EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF12EN_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF13EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF13EN_SHIFT	3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF14EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF14EN_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF15EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF15EN_SHIFT	5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF16EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF16EN_SHIFT	6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF17EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF17EN_SHIFT	7
	u8 flags10;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF18EN_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF18EN_SHIFT		0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_DQ_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_DQ_CF_EN_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_EN_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED11_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED11_SHIFT	3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_SLOW_PATH_EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_SLOW_PATH_EN_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF23EN_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF23EN_SHIFT		5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED12_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED12_SHIFT	6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED13_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED13_SHIFT	7
	u8 flags11;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED14_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED14_SHIFT		0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED15_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED15_SHIFT		1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED16_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESERVED16_SHIFT		2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE5EN_MASK			0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE5EN_SHIFT		3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE6EN_MASK			0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE6EN_SHIFT		4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE7EN_MASK			0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE7EN_SHIFT		5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED1_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED1_SHIFT		6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_XFERQ_DECISION_EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_XFERQ_DECISION_EN_SHIFT	7
	u8 flags12;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_SQ_DECISION_EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_SQ_DECISION_EN_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE11EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE11EN_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED2_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED3_SHIFT	3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE14EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE14EN_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE15EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE15EN_SHIFT	5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE16EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE16EN_SHIFT	6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE17EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE17EN_SHIFT	7
	u8 flags13;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESPQ_DECISION_EN_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RESPQ_DECISION_EN_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE19EN_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_RULE19EN_SHIFT		1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED4_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED4_SHIFT		2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED5_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED5_SHIFT		3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED6_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED6_SHIFT		4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED7_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED7_SHIFT		5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED8_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED8_SHIFT		6
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED9_MASK		0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_A0_RESERVED9_SHIFT		7
	u8 flags14;
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT16_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT16_SHIFT	0
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT17_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT17_SHIFT	1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT18_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT18_SHIFT	2
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT19_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT19_SHIFT	3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT20_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT20_SHIFT	4
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT21_MASK	0x1
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_BIT21_SHIFT	5
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF23_MASK	0x3
#घोषणा E4_XSTORM_FCOE_CONN_AG_CTX_CF23_SHIFT	6
	u8 byte2;
	__le16 physical_q0;
	__le16 word1;
	__le16 word2;
	__le16 sq_cons;
	__le16 sq_prod;
	__le16 xferq_prod;
	__le16 xferq_cons;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reमुख्य_io;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le16 respq_prod;
	__le16 respq_cons;
	__le16 word9;
	__le16 word10;
	__le32 reg7;
	__le32 reg8;
पूर्ण;

/* The fcoe storm context of Ustorm */
काष्ठा ustorm_fcoe_conn_st_ctx अणु
	काष्ठा regpair respq_pbl_addr;
	__le16 num_pages_in_pbl;
	u8 ptu_log_page_size;
	u8 log_page_size;
	__le16 respq_prod;
	u8 reserved[2];
पूर्ण;

काष्ठा e4_tstorm_fcoe_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT1_SHIFT		1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT2_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT2_SHIFT		2
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT3_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT3_SHIFT		3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT4_SHIFT		4
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT5_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_BIT5_SHIFT		5
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_MASK	0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_SHIFT	6
	u8 flags1;
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_CF_MASK		0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_CF_SHIFT		0
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF2_MASK			0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF2_SHIFT			2
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_TIMER_STOP_ALL_CF_MASK	0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_TIMER_STOP_ALL_CF_SHIFT	4
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF4_MASK			0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF4_SHIFT			6
	u8 flags2;
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF5_SHIFT	0
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF6_SHIFT	2
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF7_SHIFT	4
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF8_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF9_MASK			0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF9_SHIFT			0
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF10_MASK			0x3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF10_SHIFT			2
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_EN_SHIFT	4
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_FLUSH_Q0_CF_EN_SHIFT		5
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF2EN_SHIFT			6
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_TIMER_STOP_ALL_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_TIMER_STOP_ALL_CF_EN_SHIFT	7
	u8 flags4;
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF4EN_SHIFT		0
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF5EN_SHIFT		1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF6EN_SHIFT		2
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF7EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF7EN_SHIFT		3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF8EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF8EN_SHIFT		4
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF9EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF9EN_SHIFT		5
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF10EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_CF10EN_SHIFT		6
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags5;
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_CONN_AG_CTX_RULE8EN_SHIFT	7
	__le32 reg0;
	__le32 reg1;
पूर्ण;

काष्ठा e4_ustorm_fcoe_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF3_SHIFT	0
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF4_SHIFT	2
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF5_SHIFT	4
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF6_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF3EN_SHIFT		3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF4EN_SHIFT		4
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF5EN_SHIFT		5
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_CF6EN_SHIFT		6
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags3;
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE7EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE8EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le16 word2;
	__le16 word3;
पूर्ण;

/* The fcoe storm context of Tstorm */
काष्ठा tstorm_fcoe_conn_st_ctx अणु
	__le16 stat_ram_addr;
	__le16 rx_max_fc_payload_len;
	__le16 e_d_tov_val;
	u8 flags;
#घोषणा TSTORM_FCOE_CONN_ST_CTX_INC_SEQ_CNT_MASK	0x1
#घोषणा TSTORM_FCOE_CONN_ST_CTX_INC_SEQ_CNT_SHIFT	0
#घोषणा TSTORM_FCOE_CONN_ST_CTX_SUPPORT_CONF_MASK	0x1
#घोषणा TSTORM_FCOE_CONN_ST_CTX_SUPPORT_CONF_SHIFT	1
#घोषणा TSTORM_FCOE_CONN_ST_CTX_DEF_Q_IDX_MASK		0x3F
#घोषणा TSTORM_FCOE_CONN_ST_CTX_DEF_Q_IDX_SHIFT		2
	u8 समयrs_cleanup_invocation_cnt;
	__le32 reserved1[2];
	__le32 dst_mac_address_bytes_0_to_3;
	__le16 dst_mac_address_bytes_4_to_5;
	__le16 ramrod_echo;
	u8 flags1;
#घोषणा TSTORM_FCOE_CONN_ST_CTX_MODE_MASK	0x3
#घोषणा TSTORM_FCOE_CONN_ST_CTX_MODE_SHIFT	0
#घोषणा TSTORM_FCOE_CONN_ST_CTX_RESERVED_MASK	0x3F
#घोषणा TSTORM_FCOE_CONN_ST_CTX_RESERVED_SHIFT	2
	u8 cq_relative_offset;
	u8 cmdq_relative_offset;
	u8 bdq_resource_id;
	u8 reserved0[4];
पूर्ण;

काष्ठा e4_mstorm_fcoe_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_MSTORM_FCOE_CONN_AG_CTX_RULE4EN_SHIFT	7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

/* Fast path part of the fcoe storm context of Mstorm */
काष्ठा fcoe_mstorm_fcoe_conn_st_ctx_fp अणु
	__le16 xfer_prod;
	u8 num_cqs;
	u8 reserved1;
	u8 protection_info;
#घोषणा FCOE_MSTORM_FCOE_CONN_ST_CTX_FP_SUPPORT_PROTECTION_MASK  0x1
#घोषणा FCOE_MSTORM_FCOE_CONN_ST_CTX_FP_SUPPORT_PROTECTION_SHIFT 0
#घोषणा FCOE_MSTORM_FCOE_CONN_ST_CTX_FP_VALID_MASK               0x1
#घोषणा FCOE_MSTORM_FCOE_CONN_ST_CTX_FP_VALID_SHIFT              1
#घोषणा FCOE_MSTORM_FCOE_CONN_ST_CTX_FP_RESERVED0_MASK           0x3F
#घोषणा FCOE_MSTORM_FCOE_CONN_ST_CTX_FP_RESERVED0_SHIFT          2
	u8 q_relative_offset;
	u8 reserved2[2];
पूर्ण;

/* Non fast path part of the fcoe storm context of Mstorm */
काष्ठा fcoe_mstorm_fcoe_conn_st_ctx_non_fp अणु
	__le16 conn_id;
	__le16 stat_ram_addr;
	__le16 num_pages_in_pbl;
	u8 ptu_log_page_size;
	u8 log_page_size;
	__le16 unsolicited_cq_count;
	__le16 cmdq_count;
	u8 bdq_resource_id;
	u8 reserved0[3];
	काष्ठा regpair xferq_pbl_addr;
	काष्ठा regpair reserved1;
	काष्ठा regpair reserved2[3];
पूर्ण;

/* The fcoe storm context of Mstorm */
काष्ठा mstorm_fcoe_conn_st_ctx अणु
	काष्ठा fcoe_mstorm_fcoe_conn_st_ctx_fp fp;
	काष्ठा fcoe_mstorm_fcoe_conn_st_ctx_non_fp non_fp;
पूर्ण;

/* fcoe connection context */
काष्ठा e4_fcoe_conn_context अणु
	काष्ठा ystorm_fcoe_conn_st_ctx ystorm_st_context;
	काष्ठा pstorm_fcoe_conn_st_ctx pstorm_st_context;
	काष्ठा regpair pstorm_st_padding[2];
	काष्ठा xstorm_fcoe_conn_st_ctx xstorm_st_context;
	काष्ठा e4_xstorm_fcoe_conn_ag_ctx xstorm_ag_context;
	काष्ठा regpair xstorm_ag_padding[6];
	काष्ठा ustorm_fcoe_conn_st_ctx ustorm_st_context;
	काष्ठा regpair ustorm_st_padding[2];
	काष्ठा e4_tstorm_fcoe_conn_ag_ctx tstorm_ag_context;
	काष्ठा regpair tstorm_ag_padding[2];
	काष्ठा समयrs_context समयr_context;
	काष्ठा e4_ustorm_fcoe_conn_ag_ctx ustorm_ag_context;
	काष्ठा tstorm_fcoe_conn_st_ctx tstorm_st_context;
	काष्ठा e4_mstorm_fcoe_conn_ag_ctx mstorm_ag_context;
	काष्ठा mstorm_fcoe_conn_st_ctx mstorm_st_context;
पूर्ण;

/* FCoE connection offload params passed by driver to FW in FCoE offload
 * ramrod.
 */
काष्ठा fcoe_conn_offload_ramrod_params अणु
	काष्ठा fcoe_conn_offload_ramrod_data offload_ramrod_data;
पूर्ण;

/* FCoE connection terminate params passed by driver to FW in FCoE terminate
 * conn ramrod.
 */
काष्ठा fcoe_conn_terminate_ramrod_params अणु
	काष्ठा fcoe_conn_terminate_ramrod_data terminate_ramrod_data;
पूर्ण;

/* FCoE event type */
क्रमागत fcoe_event_type अणु
	FCOE_EVENT_INIT_FUNC,
	FCOE_EVENT_DESTROY_FUNC,
	FCOE_EVENT_STAT_FUNC,
	FCOE_EVENT_OFFLOAD_CONN,
	FCOE_EVENT_TERMINATE_CONN,
	FCOE_EVENT_ERROR,
	MAX_FCOE_EVENT_TYPE
पूर्ण;

/* FCoE init params passed by driver to FW in FCoE init ramrod */
काष्ठा fcoe_init_ramrod_params अणु
	काष्ठा fcoe_init_func_ramrod_data init_ramrod_data;
पूर्ण;

/* FCoE ramrod Command IDs */
क्रमागत fcoe_ramrod_cmd_id अणु
	FCOE_RAMROD_CMD_ID_INIT_FUNC,
	FCOE_RAMROD_CMD_ID_DESTROY_FUNC,
	FCOE_RAMROD_CMD_ID_STAT_FUNC,
	FCOE_RAMROD_CMD_ID_OFFLOAD_CONN,
	FCOE_RAMROD_CMD_ID_TERMINATE_CONN,
	MAX_FCOE_RAMROD_CMD_ID
पूर्ण;

/* FCoE statistics params buffer passed by driver to FW in FCoE statistics
 * ramrod.
 */
काष्ठा fcoe_stat_ramrod_params अणु
	काष्ठा fcoe_stat_ramrod_data stat_ramrod_data;
पूर्ण;

काष्ठा e4_ystorm_fcoe_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_CONN_AG_CTX_RULE4EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

/* The iscsi storm connection context of Ystorm */
काष्ठा ystorm_iscsi_conn_st_ctx अणु
	__le32 reserved[8];
पूर्ण;

/* Combined iSCSI and TCP storm connection of Pstorm */
काष्ठा pstorm_iscsi_tcp_conn_st_ctx अणु
	__le32 tcp[32];
	__le32 iscsi[4];
पूर्ण;

/* The combined tcp and iscsi storm context of Xstorm */
काष्ठा xstorm_iscsi_tcp_conn_st_ctx अणु
	__le32 reserved_tcp[4];
	__le32 reserved_iscsi[44];
पूर्ण;

काष्ठा e4_xstorm_iscsi_conn_ag_ctx अणु
	u8 cdu_validation;
	u8 state;
	u8 flags0;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM1_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM1_SHIFT	1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RESERVED1_SHIFT	2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM3_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM3_SHIFT	3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT4_SHIFT		4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RESERVED2_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RESERVED2_SHIFT	5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT6_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT6_SHIFT		6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT7_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT7_SHIFT		7
	u8 flags1;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT8_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT8_SHIFT		0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT9_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT9_SHIFT		1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT10_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT10_SHIFT		2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT11_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT11_SHIFT		3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT12_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT12_SHIFT		4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT13_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT13_SHIFT		5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT14_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT14_SHIFT		6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TX_TRUNCATE_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TX_TRUNCATE_SHIFT	7
	u8 flags2;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF0_MASK			0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF0_SHIFT			0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF1_MASK			0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF1_SHIFT			2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF2_MASK			0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF2_SHIFT			4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_MASK		0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_SHIFT	6
	u8 flags3;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF4_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF5_SHIFT	2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF6_SHIFT	4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF7_SHIFT	6
	u8 flags4;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF8_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF9_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF9_SHIFT	2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF10_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF10_SHIFT	4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF11_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF11_SHIFT	6
	u8 flags5;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF12_MASK				0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF12_SHIFT				0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF13_MASK				0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF13_SHIFT				2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF14_MASK				0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF14_SHIFT				4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UPDATE_STATE_TO_BASE_CF_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UPDATE_STATE_TO_BASE_CF_SHIFT	6
	u8 flags6;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF16_MASK		0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF16_SHIFT		0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF17_MASK		0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF17_SHIFT		2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF18_MASK		0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF18_SHIFT		4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_DQ_FLUSH_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_DQ_FLUSH_SHIFT	6
	u8 flags7;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_MST_XCM_Q0_FLUSH_CF_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_MST_XCM_Q0_FLUSH_CF_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UST_XCM_Q1_FLUSH_CF_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UST_XCM_Q1_FLUSH_CF_SHIFT	2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_SLOW_PATH_MASK		0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_SLOW_PATH_SHIFT		4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF0EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF0EN_SHIFT			6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF1EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF1EN_SHIFT			7
	u8 flags8;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF2EN_SHIFT			0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_EN_SHIFT	1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF4EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF4EN_SHIFT			2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF5EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF5EN_SHIFT			3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF6EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF6EN_SHIFT			4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF7EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF7EN_SHIFT			5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF8EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF8EN_SHIFT			6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF9EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF9EN_SHIFT			7
	u8 flags9;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF10EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF10EN_SHIFT			0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF11EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF11EN_SHIFT			1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF12EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF12EN_SHIFT			2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF13EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF13EN_SHIFT			3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF14EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF14EN_SHIFT			4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UPDATE_STATE_TO_BASE_CF_EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UPDATE_STATE_TO_BASE_CF_EN_SHIFT	5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF16EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF16EN_SHIFT			6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF17EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF17EN_SHIFT			7
	u8 flags10;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF18EN_MASK				0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_CF18EN_SHIFT			0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_DQ_FLUSH_EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_DQ_FLUSH_EN_SHIFT			1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_MST_XCM_Q0_FLUSH_CF_EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_MST_XCM_Q0_FLUSH_CF_EN_SHIFT	2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UST_XCM_Q1_FLUSH_CF_EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_UST_XCM_Q1_FLUSH_CF_EN_SHIFT	3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_SLOW_PATH_EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_SLOW_PATH_EN_SHIFT			4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_PROC_ONLY_CLEANUP_EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_PROC_ONLY_CLEANUP_EN_SHIFT		5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE0EN_SHIFT			6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_MORE_TO_SEND_DEC_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_MORE_TO_SEND_DEC_RULE_EN_SHIFT	7
	u8 flags11;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TX_BLOCKED_EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_TX_BLOCKED_EN_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE3EN_SHIFT	1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RESERVED3_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RESERVED3_SHIFT	2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE5EN_SHIFT	3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE6EN_SHIFT	4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE7EN_SHIFT	5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED1_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED1_SHIFT	6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE9EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE9EN_SHIFT	7
	u8 flags12;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_SQ_DEC_RULE_EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_SQ_DEC_RULE_EN_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE11EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE11EN_SHIFT		1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED2_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED2_SHIFT		2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED3_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED3_SHIFT		3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE14EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE14EN_SHIFT		4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE15EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE15EN_SHIFT		5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE16EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE16EN_SHIFT		6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE17EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_RULE17EN_SHIFT		7
	u8 flags13;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_R2TQ_DEC_RULE_EN_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_R2TQ_DEC_RULE_EN_SHIFT	0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_HQ_DEC_RULE_EN_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_HQ_DEC_RULE_EN_SHIFT	1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED4_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED4_SHIFT		2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED5_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED5_SHIFT		3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED6_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED6_SHIFT		4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED7_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED7_SHIFT		5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED8_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED8_SHIFT		6
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED9_MASK		0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_A0_RESERVED9_SHIFT		7
	u8 flags14;
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT16_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT16_SHIFT			0
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT17_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT17_SHIFT			1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT18_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT18_SHIFT			2
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT19_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT19_SHIFT			3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT20_MASK			0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_BIT20_SHIFT			4
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_DUMMY_READ_DONE_MASK	0x1
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_DUMMY_READ_DONE_SHIFT	5
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_PROC_ONLY_CLEANUP_MASK	0x3
#घोषणा E4_XSTORM_ISCSI_CONN_AG_CTX_PROC_ONLY_CLEANUP_SHIFT	6
	u8 byte2;
	__le16 physical_q0;
	__le16 physical_q1;
	__le16 dummy_करोrq_var;
	__le16 sq_cons;
	__le16 sq_prod;
	__le16 word5;
	__le16 slow_io_total_data_tx_update;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 more_to_send_seq;
	__le32 reg4;
	__le32 reg5;
	__le32 hq_scan_next_relevant_ack;
	__le16 r2tq_prod;
	__le16 r2tq_cons;
	__le16 hq_prod;
	__le16 hq_cons;
	__le32 reमुख्य_seq;
	__le32 bytes_to_next_pdu;
	__le32 hq_tcp_seq;
	u8 byte7;
	u8 byte8;
	u8 byte9;
	u8 byte10;
	u8 byte11;
	u8 byte12;
	u8 byte13;
	u8 byte14;
	u8 byte15;
	u8 e5_reserved;
	__le16 word11;
	__le32 reg10;
	__le32 reg11;
	__le32 exp_stat_sn;
	__le32 ongoing_fast_rxmit_seq;
	__le32 reg14;
	__le32 reg15;
	__le32 reg16;
	__le32 reg17;
पूर्ण;

काष्ठा e4_tstorm_iscsi_conn_ag_ctx अणु
	u8 reserved0;
	u8 state;
	u8 flags0;
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM0_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_EXIST_IN_QM0_SHIFT	0
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT1_SHIFT		1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT2_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT2_SHIFT		2
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT3_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT3_SHIFT		3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT4_SHIFT		4
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT5_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_BIT5_SHIFT		5
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF0_MASK		0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF0_SHIFT		6
	u8 flags1;
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_P2T_FLUSH_CF_MASK		0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_P2T_FLUSH_CF_SHIFT		0
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_M2T_FLUSH_CF_MASK		0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_M2T_FLUSH_CF_SHIFT		2
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_MASK		0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_SHIFT	4
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF4_MASK			0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF4_SHIFT			6
	u8 flags2;
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF5_SHIFT	0
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF6_SHIFT	2
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF7_MASK	0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF7_SHIFT	4
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF8_MASK	0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF8_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_Q0_MASK		0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_Q0_SHIFT		0
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_OOO_ISLES_CF_MASK	0x3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_OOO_ISLES_CF_SHIFT	2
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF0EN_MASK			0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF0EN_SHIFT			4
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_P2T_FLUSH_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_P2T_FLUSH_CF_EN_SHIFT	5
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_M2T_FLUSH_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_M2T_FLUSH_CF_EN_SHIFT	6
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_TIMER_STOP_ALL_EN_SHIFT	7
	u8 flags4;
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF4EN_SHIFT		0
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF5EN_SHIFT		1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF6EN_SHIFT		2
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF7EN_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF7EN_SHIFT		3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF8EN_MASK		0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_CF8EN_SHIFT		4
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_Q0_EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_Q0_EN_SHIFT	5
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_OOO_ISLES_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_FLUSH_OOO_ISLES_CF_EN_SHIFT	6
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags5;
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE8EN_MASK	0x1
#घोषणा E4_TSTORM_ISCSI_CONN_AG_CTX_RULE8EN_SHIFT	7
	__le32 reg0;
	__le32 reg1;
	__le32 rx_tcp_checksum_err_cnt;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
	__le32 reg6;
	__le32 reg7;
	__le32 reg8;
	u8 cid_offload_cnt;
	u8 byte3;
	__le16 word0;
पूर्ण;

काष्ठा e4_ustorm_iscsi_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF3_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF3_SHIFT	0
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF4_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF4_SHIFT	2
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF5_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF5_SHIFT	4
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF6_MASK	0x3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF6_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF3EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF3EN_SHIFT		3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF4EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF4EN_SHIFT		4
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF5EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF5EN_SHIFT		5
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF6EN_MASK		0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_CF6EN_SHIFT		6
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE0EN_SHIFT	7
	u8 flags3;
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE1EN_SHIFT	0
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE2EN_SHIFT	1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE3EN_SHIFT	2
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE4EN_SHIFT	3
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE5EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE5EN_SHIFT	4
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE6EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE6EN_SHIFT	5
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE7EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE7EN_SHIFT	6
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE8EN_MASK	0x1
#घोषणा E4_USTORM_ISCSI_CONN_AG_CTX_RULE8EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
	__le32 reg2;
	__le32 reg3;
	__le16 word2;
	__le16 word3;
पूर्ण;

/* The iscsi storm connection context of Tstorm */
काष्ठा tstorm_iscsi_conn_st_ctx अणु
	__le32 reserved[44];
पूर्ण;

काष्ठा e4_mstorm_iscsi_conn_ag_ctx अणु
	u8 reserved;
	u8 state;
	u8 flags0;
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_MSTORM_ISCSI_CONN_AG_CTX_RULE4EN_SHIFT	7
	__le16 word0;
	__le16 word1;
	__le32 reg0;
	__le32 reg1;
पूर्ण;

/* Combined iSCSI and TCP storm connection of Mstorm */
काष्ठा mstorm_iscsi_tcp_conn_st_ctx अणु
	__le32 reserved_tcp[20];
	__le32 reserved_iscsi[12];
पूर्ण;

/* The iscsi storm context of Ustorm */
काष्ठा ustorm_iscsi_conn_st_ctx अणु
	__le32 reserved[52];
पूर्ण;

/* iscsi connection context */
काष्ठा e4_iscsi_conn_context अणु
	काष्ठा ystorm_iscsi_conn_st_ctx ystorm_st_context;
	काष्ठा pstorm_iscsi_tcp_conn_st_ctx pstorm_st_context;
	काष्ठा regpair pstorm_st_padding[2];
	काष्ठा pb_context xpb2_context;
	काष्ठा xstorm_iscsi_tcp_conn_st_ctx xstorm_st_context;
	काष्ठा regpair xstorm_st_padding[2];
	काष्ठा e4_xstorm_iscsi_conn_ag_ctx xstorm_ag_context;
	काष्ठा e4_tstorm_iscsi_conn_ag_ctx tstorm_ag_context;
	काष्ठा regpair tstorm_ag_padding[2];
	काष्ठा समयrs_context समयr_context;
	काष्ठा e4_ustorm_iscsi_conn_ag_ctx ustorm_ag_context;
	काष्ठा pb_context upb_context;
	काष्ठा tstorm_iscsi_conn_st_ctx tstorm_st_context;
	काष्ठा regpair tstorm_st_padding[2];
	काष्ठा e4_mstorm_iscsi_conn_ag_ctx mstorm_ag_context;
	काष्ठा mstorm_iscsi_tcp_conn_st_ctx mstorm_st_context;
	काष्ठा ustorm_iscsi_conn_st_ctx ustorm_st_context;
पूर्ण;

/* iSCSI init params passed by driver to FW in iSCSI init ramrod */
काष्ठा iscsi_init_ramrod_params अणु
	काष्ठा iscsi_spe_func_init iscsi_init_spe;
	काष्ठा tcp_init_params tcp_init;
पूर्ण;

काष्ठा e4_ystorm_iscsi_conn_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	u8 flags0;
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_BIT0_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_BIT0_SHIFT	0
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_BIT1_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_BIT1_SHIFT	1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF0_MASK	0x3
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF0_SHIFT	2
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF1_MASK	0x3
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF1_SHIFT	4
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF2_MASK	0x3
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF2_SHIFT	6
	u8 flags1;
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF0EN_SHIFT		0
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF1EN_SHIFT		1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF2EN_MASK		0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_CF2EN_SHIFT		2
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE0EN_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE0EN_SHIFT	3
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE1EN_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE1EN_SHIFT	4
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE2EN_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE2EN_SHIFT	5
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE3EN_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE3EN_SHIFT	6
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE4EN_MASK	0x1
#घोषणा E4_YSTORM_ISCSI_CONN_AG_CTX_RULE4EN_SHIFT	7
	u8 byte2;
	u8 byte3;
	__le16 word0;
	__le32 reg0;
	__le32 reg1;
	__le16 word1;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 reg2;
	__le32 reg3;
पूर्ण;

#घोषणा MFW_TRACE_SIGNATURE     0x25071946

/* The trace in the buffer */
#घोषणा MFW_TRACE_EVENTID_MASK          0x00ffff
#घोषणा MFW_TRACE_PRM_SIZE_MASK         0x0f0000
#घोषणा MFW_TRACE_PRM_SIZE_OFFSET	16
#घोषणा MFW_TRACE_ENTRY_SIZE            3

काष्ठा mcp_trace अणु
	u32 signature;		/* Help to identअगरy that the trace is valid */
	u32 size;		/* the size of the trace buffer in bytes */
	u32 curr_level;		/* 2 - all will be written to the buffer
				 * 1 - debug trace will not be written
				 * 0 - just errors will be written to the buffer
				 */
	u32 modules_mask[2];	/* a bit per module, 1 means ग_लिखो it, 0 means
				 * mask it.
				 */

	/* Warning: the following poपूर्णांकers are assumed to be 32bits as they are
	 * used only in the MFW.
	 */
	u32 trace_prod; /* The next trace will be written to this offset */
	u32 trace_oldest; /* The oldest valid trace starts at this offset
			   * (usually very बंद after the current producer).
			   */
पूर्ण;

#घोषणा VF_MAX_STATIC 192

#घोषणा MCP_GLOB_PATH_MAX	2
#घोषणा MCP_PORT_MAX		2
#घोषणा MCP_GLOB_PORT_MAX	4
#घोषणा MCP_GLOB_FUNC_MAX	16

प्रकार u32 offमाप_प्रकार;		/* In DWORDS !!! */
/* Offset from the beginning of the MCP scratchpad */
#घोषणा OFFSIZE_OFFSET_SHIFT	0
#घोषणा OFFSIZE_OFFSET_MASK	0x0000ffff
/* Size of specअगरic element (not the whole array अगर any) */
#घोषणा OFFSIZE_SIZE_SHIFT	16
#घोषणा OFFSIZE_SIZE_MASK	0xffff0000

#घोषणा SECTION_OFFSET(_offsize) ((((_offsize &			\
				     OFFSIZE_OFFSET_MASK) >>	\
				    OFFSIZE_OFFSET_SHIFT) << 2))

#घोषणा QED_SECTION_SIZE(_offsize) (((_offsize &		\
				      OFFSIZE_SIZE_MASK) >>	\
				     OFFSIZE_SIZE_SHIFT) << 2)

#घोषणा SECTION_ADDR(_offsize, idx) (MCP_REG_SCRATCH +			\
				     SECTION_OFFSET(_offsize) +		\
				     (QED_SECTION_SIZE(_offsize) * idx))

#घोषणा SECTION_OFFSIZE_ADDR(_pub_base, _section)	\
	(_pub_base + दुरत्व(काष्ठा mcp_खुला_data, sections[_section]))

/* PHY configuration */
काष्ठा eth_phy_cfg अणु
	u32					speed;
#घोषणा ETH_SPEED_AUTONEG			0x0
#घोषणा ETH_SPEED_SMARTLINQ			0x8

	u32					छोड़ो;
#घोषणा ETH_PAUSE_NONE				0x0
#घोषणा ETH_PAUSE_AUTONEG			0x1
#घोषणा ETH_PAUSE_RX				0x2
#घोषणा ETH_PAUSE_TX				0x4

	u32					adv_speed;

	u32					loopback_mode;
#घोषणा ETH_LOOPBACK_NONE			0x0
#घोषणा ETH_LOOPBACK_INT_PHY			0x1
#घोषणा ETH_LOOPBACK_EXT_PHY			0x2
#घोषणा ETH_LOOPBACK_EXT			0x3
#घोषणा ETH_LOOPBACK_MAC			0x4
#घोषणा ETH_LOOPBACK_CNIG_AH_ONLY_0123		0x5
#घोषणा ETH_LOOPBACK_CNIG_AH_ONLY_2301		0x6
#घोषणा ETH_LOOPBACK_PCS_AH_ONLY		0x7
#घोषणा ETH_LOOPBACK_REVERSE_MAC_AH_ONLY	0x8
#घोषणा ETH_LOOPBACK_INT_PHY_FEA_AH_ONLY	0x9

	u32					eee_cfg;
#घोषणा EEE_CFG_EEE_ENABLED			BIT(0)
#घोषणा EEE_CFG_TX_LPI				BIT(1)
#घोषणा EEE_CFG_ADV_SPEED_1G			BIT(2)
#घोषणा EEE_CFG_ADV_SPEED_10G			BIT(3)
#घोषणा EEE_TX_TIMER_USEC_MASK			0xfffffff0
#घोषणा EEE_TX_TIMER_USEC_OFFSET		4
#घोषणा EEE_TX_TIMER_USEC_BALANCED_TIME		0xa00
#घोषणा EEE_TX_TIMER_USEC_AGGRESSIVE_TIME	0x100
#घोषणा EEE_TX_TIMER_USEC_LATENCY_TIME		0x6000

	u32					deprecated;

	u32					fec_mode;
#घोषणा FEC_FORCE_MODE_MASK			0x000000ff
#घोषणा FEC_FORCE_MODE_OFFSET			0
#घोषणा FEC_FORCE_MODE_NONE			0x00
#घोषणा FEC_FORCE_MODE_FIRECODE			0x01
#घोषणा FEC_FORCE_MODE_RS			0x02
#घोषणा FEC_FORCE_MODE_AUTO			0x07
#घोषणा FEC_EXTENDED_MODE_MASK			0xffffff00
#घोषणा FEC_EXTENDED_MODE_OFFSET		8
#घोषणा ETH_EXT_FEC_NONE			0x00000100
#घोषणा ETH_EXT_FEC_10G_NONE			0x00000200
#घोषणा ETH_EXT_FEC_10G_BASE_R			0x00000400
#घोषणा ETH_EXT_FEC_20G_NONE			0x00000800
#घोषणा ETH_EXT_FEC_20G_BASE_R			0x00001000
#घोषणा ETH_EXT_FEC_25G_NONE			0x00002000
#घोषणा ETH_EXT_FEC_25G_BASE_R			0x00004000
#घोषणा ETH_EXT_FEC_25G_RS528			0x00008000
#घोषणा ETH_EXT_FEC_40G_NONE			0x00010000
#घोषणा ETH_EXT_FEC_40G_BASE_R			0x00020000
#घोषणा ETH_EXT_FEC_50G_NONE			0x00040000
#घोषणा ETH_EXT_FEC_50G_BASE_R			0x00080000
#घोषणा ETH_EXT_FEC_50G_RS528			0x00100000
#घोषणा ETH_EXT_FEC_50G_RS544			0x00200000
#घोषणा ETH_EXT_FEC_100G_NONE			0x00400000
#घोषणा ETH_EXT_FEC_100G_BASE_R			0x00800000
#घोषणा ETH_EXT_FEC_100G_RS528			0x01000000
#घोषणा ETH_EXT_FEC_100G_RS544			0x02000000

	u32					extended_speed;
#घोषणा ETH_EXT_SPEED_MASK			0x0000ffff
#घोषणा ETH_EXT_SPEED_OFFSET			0
#घोषणा ETH_EXT_SPEED_AN			0x00000001
#घोषणा ETH_EXT_SPEED_1G			0x00000002
#घोषणा ETH_EXT_SPEED_10G			0x00000004
#घोषणा ETH_EXT_SPEED_20G			0x00000008
#घोषणा ETH_EXT_SPEED_25G			0x00000010
#घोषणा ETH_EXT_SPEED_40G			0x00000020
#घोषणा ETH_EXT_SPEED_50G_BASE_R		0x00000040
#घोषणा ETH_EXT_SPEED_50G_BASE_R2		0x00000080
#घोषणा ETH_EXT_SPEED_100G_BASE_R2		0x00000100
#घोषणा ETH_EXT_SPEED_100G_BASE_R4		0x00000200
#घोषणा ETH_EXT_SPEED_100G_BASE_P4		0x00000400
#घोषणा ETH_EXT_ADV_SPEED_MASK			0xffff0000
#घोषणा ETH_EXT_ADV_SPEED_OFFSET		16
#घोषणा ETH_EXT_ADV_SPEED_RESERVED		0x00010000
#घोषणा ETH_EXT_ADV_SPEED_1G			0x00020000
#घोषणा ETH_EXT_ADV_SPEED_10G			0x00040000
#घोषणा ETH_EXT_ADV_SPEED_20G			0x00080000
#घोषणा ETH_EXT_ADV_SPEED_25G			0x00100000
#घोषणा ETH_EXT_ADV_SPEED_40G			0x00200000
#घोषणा ETH_EXT_ADV_SPEED_50G_BASE_R		0x00400000
#घोषणा ETH_EXT_ADV_SPEED_50G_BASE_R2		0x00800000
#घोषणा ETH_EXT_ADV_SPEED_100G_BASE_R2		0x01000000
#घोषणा ETH_EXT_ADV_SPEED_100G_BASE_R4		0x02000000
#घोषणा ETH_EXT_ADV_SPEED_100G_BASE_P4		0x04000000
पूर्ण;

काष्ठा port_mf_cfg अणु
	u32 dynamic_cfg;
#घोषणा PORT_MF_CFG_OV_TAG_MASK		0x0000ffff
#घोषणा PORT_MF_CFG_OV_TAG_SHIFT	0
#घोषणा PORT_MF_CFG_OV_TAG_DEFAULT	PORT_MF_CFG_OV_TAG_MASK

	u32 reserved[1];
पूर्ण;

काष्ठा eth_stats अणु
	u64 r64;
	u64 r127;
	u64 r255;
	u64 r511;
	u64 r1023;
	u64 r1518;

	जोड़ अणु
		काष्ठा अणु
			u64 r1522;
			u64 r2047;
			u64 r4095;
			u64 r9216;
			u64 r16383;
		पूर्ण bb0;
		काष्ठा अणु
			u64 unused1;
			u64 r1519_to_max;
			u64 unused2;
			u64 unused3;
			u64 unused4;
		पूर्ण ah0;
	पूर्ण u0;

	u64 rfcs;
	u64 rxcf;
	u64 rxpf;
	u64 rxpp;
	u64 raln;
	u64 rfcr;
	u64 rovr;
	u64 rjbr;
	u64 rund;
	u64 rfrg;
	u64 t64;
	u64 t127;
	u64 t255;
	u64 t511;
	u64 t1023;
	u64 t1518;

	जोड़ अणु
		काष्ठा अणु
			u64 t2047;
			u64 t4095;
			u64 t9216;
			u64 t16383;
		पूर्ण bb1;
		काष्ठा अणु
			u64 t1519_to_max;
			u64 unused6;
			u64 unused7;
			u64 unused8;
		पूर्ण ah1;
	पूर्ण u1;

	u64 txpf;
	u64 txpp;

	जोड़ अणु
		काष्ठा अणु
			u64 tlpiec;
			u64 tncl;
		पूर्ण bb2;
		काष्ठा अणु
			u64 unused9;
			u64 unused10;
		पूर्ण ah2;
	पूर्ण u2;

	u64 rbyte;
	u64 rxuca;
	u64 rxmca;
	u64 rxbca;
	u64 rxpok;
	u64 tbyte;
	u64 txuca;
	u64 txmca;
	u64 txbca;
	u64 txcf;
पूर्ण;

काष्ठा brb_stats अणु
	u64 brb_truncate[8];
	u64 brb_discard[8];
पूर्ण;

काष्ठा port_stats अणु
	काष्ठा brb_stats brb;
	काष्ठा eth_stats eth;
पूर्ण;

काष्ठा couple_mode_teaming अणु
	u8 port_cmt[MCP_GLOB_PORT_MAX];
#घोषणा PORT_CMT_IN_TEAM	(1 << 0)

#घोषणा PORT_CMT_PORT_ROLE	(1 << 1)
#घोषणा PORT_CMT_PORT_INACTIVE	(0 << 1)
#घोषणा PORT_CMT_PORT_ACTIVE	(1 << 1)

#घोषणा PORT_CMT_TEAM_MASK	(1 << 2)
#घोषणा PORT_CMT_TEAM0		(0 << 2)
#घोषणा PORT_CMT_TEAM1		(1 << 2)
पूर्ण;

#घोषणा LLDP_CHASSIS_ID_STAT_LEN	4
#घोषणा LLDP_PORT_ID_STAT_LEN		4
#घोषणा DCBX_MAX_APP_PROTOCOL		32
#घोषणा MAX_SYSTEM_LLDP_TLV_DATA	32

क्रमागत _lldp_agent अणु
	LLDP_NEAREST_BRIDGE = 0,
	LLDP_NEAREST_NON_TPMR_BRIDGE,
	LLDP_NEAREST_CUSTOMER_BRIDGE,
	LLDP_MAX_LLDP_AGENTS
पूर्ण;

काष्ठा lldp_config_params_s अणु
	u32 config;
#घोषणा LLDP_CONFIG_TX_INTERVAL_MASK	0x000000ff
#घोषणा LLDP_CONFIG_TX_INTERVAL_SHIFT	0
#घोषणा LLDP_CONFIG_HOLD_MASK		0x00000f00
#घोषणा LLDP_CONFIG_HOLD_SHIFT		8
#घोषणा LLDP_CONFIG_MAX_CREDIT_MASK	0x0000f000
#घोषणा LLDP_CONFIG_MAX_CREDIT_SHIFT	12
#घोषणा LLDP_CONFIG_ENABLE_RX_MASK	0x40000000
#घोषणा LLDP_CONFIG_ENABLE_RX_SHIFT	30
#घोषणा LLDP_CONFIG_ENABLE_TX_MASK	0x80000000
#घोषणा LLDP_CONFIG_ENABLE_TX_SHIFT	31
	u32 local_chassis_id[LLDP_CHASSIS_ID_STAT_LEN];
	u32 local_port_id[LLDP_PORT_ID_STAT_LEN];
पूर्ण;

काष्ठा lldp_status_params_s अणु
	u32 prefix_seq_num;
	u32 status;
	u32 peer_chassis_id[LLDP_CHASSIS_ID_STAT_LEN];
	u32 peer_port_id[LLDP_PORT_ID_STAT_LEN];
	u32 suffix_seq_num;
पूर्ण;

काष्ठा dcbx_ets_feature अणु
	u32 flags;
#घोषणा DCBX_ETS_ENABLED_MASK	0x00000001
#घोषणा DCBX_ETS_ENABLED_SHIFT	0
#घोषणा DCBX_ETS_WILLING_MASK	0x00000002
#घोषणा DCBX_ETS_WILLING_SHIFT	1
#घोषणा DCBX_ETS_ERROR_MASK	0x00000004
#घोषणा DCBX_ETS_ERROR_SHIFT	2
#घोषणा DCBX_ETS_CBS_MASK	0x00000008
#घोषणा DCBX_ETS_CBS_SHIFT	3
#घोषणा DCBX_ETS_MAX_TCS_MASK	0x000000f0
#घोषणा DCBX_ETS_MAX_TCS_SHIFT	4
#घोषणा DCBX_OOO_TC_MASK	0x00000f00
#घोषणा DCBX_OOO_TC_SHIFT	8
	u32 pri_tc_tbl[1];
#घोषणा DCBX_TCP_OOO_TC		(4)

#घोषणा NIG_ETS_ISCSI_OOO_CLIENT_OFFSET	(DCBX_TCP_OOO_TC + 1)
#घोषणा DCBX_CEE_STRICT_PRIORITY	0xf
	u32 tc_bw_tbl[2];
	u32 tc_tsa_tbl[2];
#घोषणा DCBX_ETS_TSA_STRICT	0
#घोषणा DCBX_ETS_TSA_CBS	1
#घोषणा DCBX_ETS_TSA_ETS	2
पूर्ण;

#घोषणा DCBX_TCP_OOO_TC			(4)
#घोषणा DCBX_TCP_OOO_K2_4PORT_TC	(3)

काष्ठा dcbx_app_priority_entry अणु
	u32 entry;
#घोषणा DCBX_APP_PRI_MAP_MASK		0x000000ff
#घोषणा DCBX_APP_PRI_MAP_SHIFT		0
#घोषणा DCBX_APP_PRI_0			0x01
#घोषणा DCBX_APP_PRI_1			0x02
#घोषणा DCBX_APP_PRI_2			0x04
#घोषणा DCBX_APP_PRI_3			0x08
#घोषणा DCBX_APP_PRI_4			0x10
#घोषणा DCBX_APP_PRI_5			0x20
#घोषणा DCBX_APP_PRI_6			0x40
#घोषणा DCBX_APP_PRI_7			0x80
#घोषणा DCBX_APP_SF_MASK		0x00000300
#घोषणा DCBX_APP_SF_SHIFT		8
#घोषणा DCBX_APP_SF_ETHTYPE		0
#घोषणा DCBX_APP_SF_PORT		1
#घोषणा DCBX_APP_SF_IEEE_MASK		0x0000f000
#घोषणा DCBX_APP_SF_IEEE_SHIFT		12
#घोषणा DCBX_APP_SF_IEEE_RESERVED	0
#घोषणा DCBX_APP_SF_IEEE_ETHTYPE	1
#घोषणा DCBX_APP_SF_IEEE_TCP_PORT	2
#घोषणा DCBX_APP_SF_IEEE_UDP_PORT	3
#घोषणा DCBX_APP_SF_IEEE_TCP_UDP_PORT	4

#घोषणा DCBX_APP_PROTOCOL_ID_MASK	0xffff0000
#घोषणा DCBX_APP_PROTOCOL_ID_SHIFT	16
पूर्ण;

काष्ठा dcbx_app_priority_feature अणु
	u32 flags;
#घोषणा DCBX_APP_ENABLED_MASK		0x00000001
#घोषणा DCBX_APP_ENABLED_SHIFT		0
#घोषणा DCBX_APP_WILLING_MASK		0x00000002
#घोषणा DCBX_APP_WILLING_SHIFT		1
#घोषणा DCBX_APP_ERROR_MASK		0x00000004
#घोषणा DCBX_APP_ERROR_SHIFT		2
#घोषणा DCBX_APP_MAX_TCS_MASK		0x0000f000
#घोषणा DCBX_APP_MAX_TCS_SHIFT		12
#घोषणा DCBX_APP_NUM_ENTRIES_MASK	0x00ff0000
#घोषणा DCBX_APP_NUM_ENTRIES_SHIFT	16
	काष्ठा dcbx_app_priority_entry app_pri_tbl[DCBX_MAX_APP_PROTOCOL];
पूर्ण;

काष्ठा dcbx_features अणु
	काष्ठा dcbx_ets_feature ets;
	u32 pfc;
#घोषणा DCBX_PFC_PRI_EN_BITMAP_MASK	0x000000ff
#घोषणा DCBX_PFC_PRI_EN_BITMAP_SHIFT	0
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_0	0x01
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_1	0x02
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_2	0x04
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_3	0x08
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_4	0x10
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_5	0x20
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_6	0x40
#घोषणा DCBX_PFC_PRI_EN_BITMAP_PRI_7	0x80

#घोषणा DCBX_PFC_FLAGS_MASK		0x0000ff00
#घोषणा DCBX_PFC_FLAGS_SHIFT		8
#घोषणा DCBX_PFC_CAPS_MASK		0x00000f00
#घोषणा DCBX_PFC_CAPS_SHIFT		8
#घोषणा DCBX_PFC_MBC_MASK		0x00004000
#घोषणा DCBX_PFC_MBC_SHIFT		14
#घोषणा DCBX_PFC_WILLING_MASK		0x00008000
#घोषणा DCBX_PFC_WILLING_SHIFT		15
#घोषणा DCBX_PFC_ENABLED_MASK		0x00010000
#घोषणा DCBX_PFC_ENABLED_SHIFT		16
#घोषणा DCBX_PFC_ERROR_MASK		0x00020000
#घोषणा DCBX_PFC_ERROR_SHIFT		17

	काष्ठा dcbx_app_priority_feature app;
पूर्ण;

काष्ठा dcbx_local_params अणु
	u32 config;
#घोषणा DCBX_CONFIG_VERSION_MASK	0x00000007
#घोषणा DCBX_CONFIG_VERSION_SHIFT	0
#घोषणा DCBX_CONFIG_VERSION_DISABLED	0
#घोषणा DCBX_CONFIG_VERSION_IEEE	1
#घोषणा DCBX_CONFIG_VERSION_CEE		2
#घोषणा DCBX_CONFIG_VERSION_STATIC	4

	u32 flags;
	काष्ठा dcbx_features features;
पूर्ण;

काष्ठा dcbx_mib अणु
	u32 prefix_seq_num;
	u32 flags;
	काष्ठा dcbx_features features;
	u32 suffix_seq_num;
पूर्ण;

काष्ठा lldp_प्रणाली_tlvs_buffer_s अणु
	u16 valid;
	u16 length;
	u32 data[MAX_SYSTEM_LLDP_TLV_DATA];
पूर्ण;

काष्ठा dcb_dscp_map अणु
	u32 flags;
#घोषणा DCB_DSCP_ENABLE_MASK	0x1
#घोषणा DCB_DSCP_ENABLE_SHIFT	0
#घोषणा DCB_DSCP_ENABLE	1
	u32 dscp_pri_map[8];
पूर्ण;

काष्ठा खुला_global अणु
	u32 max_path;
	u32 max_ports;
#घोषणा MODE_1P 1
#घोषणा MODE_2P 2
#घोषणा MODE_3P 3
#घोषणा MODE_4P 4
	u32 debug_mb_offset;
	u32 phymod_dbg_mb_offset;
	काष्ठा couple_mode_teaming cmt;
	s32 पूर्णांकernal_temperature;
	u32 mfw_ver;
	u32 running_bundle_id;
	s32 बाह्यal_temperature;
	u32 mdump_reason;
	u64 reserved;
	u32 data_ptr;
	u32 data_size;
पूर्ण;

काष्ठा fw_flr_mb अणु
	u32 aggपूर्णांक;
	u32 opgen_addr;
	u32 accum_ack;
पूर्ण;

काष्ठा खुला_path अणु
	काष्ठा fw_flr_mb flr_mb;
	u32 mcp_vf_disabled[VF_MAX_STATIC / 32];

	u32 process_समाप्त;
#घोषणा PROCESS_KILL_COUNTER_MASK	0x0000ffff
#घोषणा PROCESS_KILL_COUNTER_SHIFT	0
#घोषणा PROCESS_KILL_GLOB_AEU_BIT_MASK	0xffff0000
#घोषणा PROCESS_KILL_GLOB_AEU_BIT_SHIFT	16
#घोषणा GLOBAL_AEU_BIT(aeu_reg_id, aeu_bit) (aeu_reg_id * 32 + aeu_bit)
पूर्ण;

काष्ठा खुला_port अणु
	u32						validity_map;

	u32						link_status;
#घोषणा LINK_STATUS_LINK_UP				0x00000001
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_MASK		0x0000001e
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_1000THD		(1 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_1000TFD		(2 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_10G		(3 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_20G		(4 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_40G		(5 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_50G		(6 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_100G		(7 << 1)
#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_25G		(8 << 1)
#घोषणा LINK_STATUS_AUTO_NEGOTIATE_ENABLED		0x00000020
#घोषणा LINK_STATUS_AUTO_NEGOTIATE_COMPLETE		0x00000040
#घोषणा LINK_STATUS_PARALLEL_DETECTION_USED		0x00000080
#घोषणा LINK_STATUS_PFC_ENABLED				0x00000100
#घोषणा LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE	0x00000200
#घोषणा LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE	0x00000400
#घोषणा LINK_STATUS_LINK_PARTNER_10G_CAPABLE		0x00000800
#घोषणा LINK_STATUS_LINK_PARTNER_20G_CAPABLE		0x00001000
#घोषणा LINK_STATUS_LINK_PARTNER_40G_CAPABLE		0x00002000
#घोषणा LINK_STATUS_LINK_PARTNER_50G_CAPABLE		0x00004000
#घोषणा LINK_STATUS_LINK_PARTNER_100G_CAPABLE		0x00008000
#घोषणा LINK_STATUS_LINK_PARTNER_25G_CAPABLE		0x00010000
#घोषणा LINK_STATUS_LINK_PARTNER_FLOW_CONTROL_MASK	0x000c0000
#घोषणा LINK_STATUS_LINK_PARTNER_NOT_PAUSE_CAPABLE	(0 << 18)
#घोषणा LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE	(1 << 18)
#घोषणा LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE	(2 << 18)
#घोषणा LINK_STATUS_LINK_PARTNER_BOTH_PAUSE		(3 << 18)
#घोषणा LINK_STATUS_SFP_TX_FAULT			0x00100000
#घोषणा LINK_STATUS_TX_FLOW_CONTROL_ENABLED		0x00200000
#घोषणा LINK_STATUS_RX_FLOW_CONTROL_ENABLED		0x00400000
#घोषणा LINK_STATUS_RX_SIGNAL_PRESENT			0x00800000
#घोषणा LINK_STATUS_MAC_LOCAL_FAULT			0x01000000
#घोषणा LINK_STATUS_MAC_REMOTE_FAULT			0x02000000
#घोषणा LINK_STATUS_UNSUPPORTED_SPD_REQ			0x04000000

#घोषणा LINK_STATUS_FEC_MODE_MASK			0x38000000
#घोषणा LINK_STATUS_FEC_MODE_NONE			(0 << 27)
#घोषणा LINK_STATUS_FEC_MODE_FIRECODE_CL74		(1 << 27)
#घोषणा LINK_STATUS_FEC_MODE_RS_CL91			(2 << 27)

	u32 link_status1;
	u32 ext_phy_fw_version;
	u32 drv_phy_cfg_addr;

	u32 port_stx;

	u32 stat_nig_समयr;

	काष्ठा port_mf_cfg port_mf_config;
	काष्ठा port_stats stats;

	u32 media_type;
#घोषणा MEDIA_UNSPECIFIED	0x0
#घोषणा MEDIA_SFPP_10G_FIBER	0x1
#घोषणा MEDIA_XFP_FIBER		0x2
#घोषणा MEDIA_DA_TWINAX		0x3
#घोषणा MEDIA_BASE_T		0x4
#घोषणा MEDIA_SFP_1G_FIBER	0x5
#घोषणा MEDIA_MODULE_FIBER	0x6
#घोषणा MEDIA_KR		0xf0
#घोषणा MEDIA_NOT_PRESENT	0xff

	u32 lfa_status;
	u32 link_change_count;

	काष्ठा lldp_config_params_s lldp_config_params[LLDP_MAX_LLDP_AGENTS];
	काष्ठा lldp_status_params_s lldp_status_params[LLDP_MAX_LLDP_AGENTS];
	काष्ठा lldp_प्रणाली_tlvs_buffer_s प्रणाली_lldp_tlvs_buf;

	/* DCBX related MIB */
	काष्ठा dcbx_local_params local_admin_dcbx_mib;
	काष्ठा dcbx_mib remote_dcbx_mib;
	काष्ठा dcbx_mib operational_dcbx_mib;

	u32 reserved[2];

	u32						transceiver_data;
#घोषणा ETH_TRANSCEIVER_STATE_MASK			0x000000ff
#घोषणा ETH_TRANSCEIVER_STATE_SHIFT			0x00000000
#घोषणा ETH_TRANSCEIVER_STATE_OFFSET			0x00000000
#घोषणा ETH_TRANSCEIVER_STATE_UNPLUGGED			0x00000000
#घोषणा ETH_TRANSCEIVER_STATE_PRESENT			0x00000001
#घोषणा ETH_TRANSCEIVER_STATE_VALID			0x00000003
#घोषणा ETH_TRANSCEIVER_STATE_UPDATING			0x00000008
#घोषणा ETH_TRANSCEIVER_TYPE_MASK			0x0000ff00
#घोषणा ETH_TRANSCEIVER_TYPE_OFFSET			0x8
#घोषणा ETH_TRANSCEIVER_TYPE_NONE			0x00
#घोषणा ETH_TRANSCEIVER_TYPE_UNKNOWN			0xff
#घोषणा ETH_TRANSCEIVER_TYPE_1G_PCC			0x01
#घोषणा ETH_TRANSCEIVER_TYPE_1G_ACC			0x02
#घोषणा ETH_TRANSCEIVER_TYPE_1G_LX			0x03
#घोषणा ETH_TRANSCEIVER_TYPE_1G_SX			0x04
#घोषणा ETH_TRANSCEIVER_TYPE_10G_SR			0x05
#घोषणा ETH_TRANSCEIVER_TYPE_10G_LR			0x06
#घोषणा ETH_TRANSCEIVER_TYPE_10G_LRM			0x07
#घोषणा ETH_TRANSCEIVER_TYPE_10G_ER			0x08
#घोषणा ETH_TRANSCEIVER_TYPE_10G_PCC			0x09
#घोषणा ETH_TRANSCEIVER_TYPE_10G_ACC			0x0a
#घोषणा ETH_TRANSCEIVER_TYPE_XLPPI			0x0b
#घोषणा ETH_TRANSCEIVER_TYPE_40G_LR4			0x0c
#घोषणा ETH_TRANSCEIVER_TYPE_40G_SR4			0x0d
#घोषणा ETH_TRANSCEIVER_TYPE_40G_CR4			0x0e
#घोषणा ETH_TRANSCEIVER_TYPE_100G_AOC			0x0f
#घोषणा ETH_TRANSCEIVER_TYPE_100G_SR4			0x10
#घोषणा ETH_TRANSCEIVER_TYPE_100G_LR4			0x11
#घोषणा ETH_TRANSCEIVER_TYPE_100G_ER4			0x12
#घोषणा ETH_TRANSCEIVER_TYPE_100G_ACC			0x13
#घोषणा ETH_TRANSCEIVER_TYPE_100G_CR4			0x14
#घोषणा ETH_TRANSCEIVER_TYPE_4x10G_SR			0x15
#घोषणा ETH_TRANSCEIVER_TYPE_25G_CA_N			0x16
#घोषणा ETH_TRANSCEIVER_TYPE_25G_ACC_S			0x17
#घोषणा ETH_TRANSCEIVER_TYPE_25G_CA_S			0x18
#घोषणा ETH_TRANSCEIVER_TYPE_25G_ACC_M			0x19
#घोषणा ETH_TRANSCEIVER_TYPE_25G_CA_L			0x1a
#घोषणा ETH_TRANSCEIVER_TYPE_25G_ACC_L			0x1b
#घोषणा ETH_TRANSCEIVER_TYPE_25G_SR			0x1c
#घोषणा ETH_TRANSCEIVER_TYPE_25G_LR			0x1d
#घोषणा ETH_TRANSCEIVER_TYPE_25G_AOC			0x1e
#घोषणा ETH_TRANSCEIVER_TYPE_4x10G			0x1f
#घोषणा ETH_TRANSCEIVER_TYPE_4x25G_CR			0x20
#घोषणा ETH_TRANSCEIVER_TYPE_1000BASET			0x21
#घोषणा ETH_TRANSCEIVER_TYPE_10G_BASET			0x22
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_SR	0x30
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_CR	0x31
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_LR	0x32
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_SR	0x33
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_CR	0x34
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_LR	0x35
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_AOC	0x36
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_SR	0x37
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_LR	0x38
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_SR	0x39
#घोषणा ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_LR	0x3a

	u32 wol_info;
	u32 wol_pkt_len;
	u32 wol_pkt_details;
	काष्ठा dcb_dscp_map dcb_dscp_map;

	u32 eee_status;
#घोषणा EEE_ACTIVE_BIT			BIT(0)
#घोषणा EEE_LD_ADV_STATUS_MASK		0x000000f0
#घोषणा EEE_LD_ADV_STATUS_OFFSET	4
#घोषणा EEE_1G_ADV			BIT(1)
#घोषणा EEE_10G_ADV			BIT(2)
#घोषणा EEE_LP_ADV_STATUS_MASK		0x00000f00
#घोषणा EEE_LP_ADV_STATUS_OFFSET	8
#घोषणा EEE_SUPPORTED_SPEED_MASK	0x0000f000
#घोषणा EEE_SUPPORTED_SPEED_OFFSET	12
#घोषणा EEE_1G_SUPPORTED		BIT(1)
#घोषणा EEE_10G_SUPPORTED		BIT(2)

	u32 eee_remote;
#घोषणा EEE_REMOTE_TW_TX_MASK   0x0000ffff
#घोषणा EEE_REMOTE_TW_TX_OFFSET 0
#घोषणा EEE_REMOTE_TW_RX_MASK   0xffff0000
#घोषणा EEE_REMOTE_TW_RX_OFFSET 16

	u32 reserved1;
	u32 oem_cfg_port;
#घोषणा OEM_CFG_CHANNEL_TYPE_MASK                       0x00000003
#घोषणा OEM_CFG_CHANNEL_TYPE_OFFSET                     0
#घोषणा OEM_CFG_CHANNEL_TYPE_VLAN_PARTITION             0x1
#घोषणा OEM_CFG_CHANNEL_TYPE_STAGGED                    0x2
#घोषणा OEM_CFG_SCHED_TYPE_MASK                         0x0000000C
#घोषणा OEM_CFG_SCHED_TYPE_OFFSET                       2
#घोषणा OEM_CFG_SCHED_TYPE_ETS                          0x1
#घोषणा OEM_CFG_SCHED_TYPE_VNIC_BW                      0x2
पूर्ण;

काष्ठा खुला_func अणु
	u32 reserved0[2];

	u32 mtu_size;

	u32 reserved[7];

	u32 config;
#घोषणा FUNC_MF_CFG_FUNC_HIDE			0x00000001
#घोषणा FUNC_MF_CFG_PAUSE_ON_HOST_RING		0x00000002
#घोषणा FUNC_MF_CFG_PAUSE_ON_HOST_RING_SHIFT	0x00000001

#घोषणा FUNC_MF_CFG_PROTOCOL_MASK	0x000000f0
#घोषणा FUNC_MF_CFG_PROTOCOL_SHIFT	4
#घोषणा FUNC_MF_CFG_PROTOCOL_ETHERNET	0x00000000
#घोषणा FUNC_MF_CFG_PROTOCOL_ISCSI              0x00000010
#घोषणा FUNC_MF_CFG_PROTOCOL_FCOE               0x00000020
#घोषणा FUNC_MF_CFG_PROTOCOL_ROCE               0x00000030
#घोषणा FUNC_MF_CFG_PROTOCOL_MAX	0x00000030

#घोषणा FUNC_MF_CFG_MIN_BW_MASK		0x0000ff00
#घोषणा FUNC_MF_CFG_MIN_BW_SHIFT	8
#घोषणा FUNC_MF_CFG_MIN_BW_DEFAULT	0x00000000
#घोषणा FUNC_MF_CFG_MAX_BW_MASK		0x00ff0000
#घोषणा FUNC_MF_CFG_MAX_BW_SHIFT	16
#घोषणा FUNC_MF_CFG_MAX_BW_DEFAULT	0x00640000

	u32 status;
#घोषणा FUNC_STATUS_VIRTUAL_LINK_UP	0x00000001

	u32 mac_upper;
#घोषणा FUNC_MF_CFG_UPPERMAC_MASK	0x0000ffff
#घोषणा FUNC_MF_CFG_UPPERMAC_SHIFT	0
#घोषणा FUNC_MF_CFG_UPPERMAC_DEFAULT	FUNC_MF_CFG_UPPERMAC_MASK
	u32 mac_lower;
#घोषणा FUNC_MF_CFG_LOWERMAC_DEFAULT	0xffffffff

	u32 fcoe_wwn_port_name_upper;
	u32 fcoe_wwn_port_name_lower;

	u32 fcoe_wwn_node_name_upper;
	u32 fcoe_wwn_node_name_lower;

	u32 ovlan_stag;
#घोषणा FUNC_MF_CFG_OV_STAG_MASK	0x0000ffff
#घोषणा FUNC_MF_CFG_OV_STAG_SHIFT	0
#घोषणा FUNC_MF_CFG_OV_STAG_DEFAULT	FUNC_MF_CFG_OV_STAG_MASK

	u32 pf_allocation;

	u32 preserve_data;

	u32 driver_last_activity_ts;

	u32 drv_ack_vf_disabled[VF_MAX_STATIC / 32];

	u32 drv_id;
#घोषणा DRV_ID_PDA_COMP_VER_MASK	0x0000ffff
#घोषणा DRV_ID_PDA_COMP_VER_SHIFT	0

#घोषणा LOAD_REQ_HSI_VERSION		2
#घोषणा DRV_ID_MCP_HSI_VER_MASK		0x00ff0000
#घोषणा DRV_ID_MCP_HSI_VER_SHIFT	16
#घोषणा DRV_ID_MCP_HSI_VER_CURRENT	(LOAD_REQ_HSI_VERSION << \
					 DRV_ID_MCP_HSI_VER_SHIFT)

#घोषणा DRV_ID_DRV_TYPE_MASK		0x7f000000
#घोषणा DRV_ID_DRV_TYPE_SHIFT		24
#घोषणा DRV_ID_DRV_TYPE_UNKNOWN		(0 << DRV_ID_DRV_TYPE_SHIFT)
#घोषणा DRV_ID_DRV_TYPE_LINUX		(1 << DRV_ID_DRV_TYPE_SHIFT)

#घोषणा DRV_ID_DRV_INIT_HW_MASK		0x80000000
#घोषणा DRV_ID_DRV_INIT_HW_SHIFT	31
#घोषणा DRV_ID_DRV_INIT_HW_FLAG		(1 << DRV_ID_DRV_INIT_HW_SHIFT)

	u32 oem_cfg_func;
#घोषणा OEM_CFG_FUNC_TC_MASK                    0x0000000F
#घोषणा OEM_CFG_FUNC_TC_OFFSET                  0
#घोषणा OEM_CFG_FUNC_TC_0                       0x0
#घोषणा OEM_CFG_FUNC_TC_1                       0x1
#घोषणा OEM_CFG_FUNC_TC_2                       0x2
#घोषणा OEM_CFG_FUNC_TC_3                       0x3
#घोषणा OEM_CFG_FUNC_TC_4                       0x4
#घोषणा OEM_CFG_FUNC_TC_5                       0x5
#घोषणा OEM_CFG_FUNC_TC_6                       0x6
#घोषणा OEM_CFG_FUNC_TC_7                       0x7

#घोषणा OEM_CFG_FUNC_HOST_PRI_CTRL_MASK         0x00000030
#घोषणा OEM_CFG_FUNC_HOST_PRI_CTRL_OFFSET       4
#घोषणा OEM_CFG_FUNC_HOST_PRI_CTRL_VNIC         0x1
#घोषणा OEM_CFG_FUNC_HOST_PRI_CTRL_OS           0x2
पूर्ण;

काष्ठा mcp_mac अणु
	u32 mac_upper;
	u32 mac_lower;
पूर्ण;

काष्ठा mcp_val64 अणु
	u32 lo;
	u32 hi;
पूर्ण;

काष्ठा mcp_file_att अणु
	u32 nvm_start_addr;
	u32 len;
पूर्ण;

काष्ठा bist_nvm_image_att अणु
	u32 वापस_code;
	u32 image_type;
	u32 nvm_start_addr;
	u32 len;
पूर्ण;

#घोषणा MCP_DRV_VER_STR_SIZE 16
#घोषणा MCP_DRV_VER_STR_SIZE_DWORD (MCP_DRV_VER_STR_SIZE / माप(u32))
#घोषणा MCP_DRV_NVM_BUF_LEN 32
काष्ठा drv_version_stc अणु
	u32 version;
	u8 name[MCP_DRV_VER_STR_SIZE - 4];
पूर्ण;

काष्ठा lan_stats_stc अणु
	u64 ucast_rx_pkts;
	u64 ucast_tx_pkts;
	u32 fcs_err;
	u32 rserved;
पूर्ण;

काष्ठा fcoe_stats_stc अणु
	u64 rx_pkts;
	u64 tx_pkts;
	u32 fcs_err;
	u32 login_failure;
पूर्ण;

काष्ठा ocbb_data_stc अणु
	u32 ocbb_host_addr;
	u32 ocsd_host_addr;
	u32 ocsd_req_update_पूर्णांकerval;
पूर्ण;

#घोषणा MAX_NUM_OF_SENSORS 7
काष्ठा temperature_status_stc अणु
	u32 num_of_sensors;
	u32 sensor[MAX_NUM_OF_SENSORS];
पूर्ण;

/* crash dump configuration header */
काष्ठा mdump_config_stc अणु
	u32 version;
	u32 config;
	u32 epoc;
	u32 num_of_logs;
	u32 valid_logs;
पूर्ण;

क्रमागत resource_id_क्रमागत अणु
	RESOURCE_NUM_SB_E = 0,
	RESOURCE_NUM_L2_QUEUE_E = 1,
	RESOURCE_NUM_VPORT_E = 2,
	RESOURCE_NUM_VMQ_E = 3,
	RESOURCE_FACTOR_NUM_RSS_PF_E = 4,
	RESOURCE_FACTOR_RSS_PER_VF_E = 5,
	RESOURCE_NUM_RL_E = 6,
	RESOURCE_NUM_PQ_E = 7,
	RESOURCE_NUM_VF_E = 8,
	RESOURCE_VFC_FILTER_E = 9,
	RESOURCE_ILT_E = 10,
	RESOURCE_CQS_E = 11,
	RESOURCE_GFT_PROखाताS_E = 12,
	RESOURCE_NUM_TC_E = 13,
	RESOURCE_NUM_RSS_ENGINES_E = 14,
	RESOURCE_LL2_QUEUE_E = 15,
	RESOURCE_RDMA_STATS_QUEUE_E = 16,
	RESOURCE_BDQ_E = 17,
	RESOURCE_QCN_E = 18,
	RESOURCE_LLH_FILTER_E = 19,
	RESOURCE_VF_MAC_ADDR = 20,
	RESOURCE_LL2_CQS_E = 21,
	RESOURCE_VF_CNQS = 22,
	RESOURCE_MAX_NUM,
	RESOURCE_NUM_INVALID = 0xFFFFFFFF
पूर्ण;

/* Resource ID is to be filled by the driver in the MB request
 * Size, offset & flags to be filled by the MFW in the MB response
 */
काष्ठा resource_info अणु
	क्रमागत resource_id_क्रमागत res_id;
	u32 size;		/* number of allocated resources */
	u32 offset;		/* Offset of the 1st resource */
	u32 vf_size;
	u32 vf_offset;
	u32 flags;
#घोषणा RESOURCE_ELEMENT_STRICT (1 << 0)
पूर्ण;

#घोषणा DRV_ROLE_NONE           0
#घोषणा DRV_ROLE_PREBOOT        1
#घोषणा DRV_ROLE_OS             2
#घोषणा DRV_ROLE_KDUMP          3

काष्ठा load_req_stc अणु
	u32 drv_ver_0;
	u32 drv_ver_1;
	u32 fw_ver;
	u32 misc0;
#घोषणा LOAD_REQ_ROLE_MASK              0x000000FF
#घोषणा LOAD_REQ_ROLE_SHIFT             0
#घोषणा LOAD_REQ_LOCK_TO_MASK           0x0000FF00
#घोषणा LOAD_REQ_LOCK_TO_SHIFT          8
#घोषणा LOAD_REQ_LOCK_TO_DEFAULT        0
#घोषणा LOAD_REQ_LOCK_TO_NONE           255
#घोषणा LOAD_REQ_FORCE_MASK             0x000F0000
#घोषणा LOAD_REQ_FORCE_SHIFT            16
#घोषणा LOAD_REQ_FORCE_NONE             0
#घोषणा LOAD_REQ_FORCE_PF               1
#घोषणा LOAD_REQ_FORCE_ALL              2
#घोषणा LOAD_REQ_FLAGS0_MASK            0x00F00000
#घोषणा LOAD_REQ_FLAGS0_SHIFT           20
#घोषणा LOAD_REQ_FLAGS0_AVOID_RESET     (0x1 << 0)
पूर्ण;

काष्ठा load_rsp_stc अणु
	u32 drv_ver_0;
	u32 drv_ver_1;
	u32 fw_ver;
	u32 misc0;
#घोषणा LOAD_RSP_ROLE_MASK              0x000000FF
#घोषणा LOAD_RSP_ROLE_SHIFT             0
#घोषणा LOAD_RSP_HSI_MASK               0x0000FF00
#घोषणा LOAD_RSP_HSI_SHIFT              8
#घोषणा LOAD_RSP_FLAGS0_MASK            0x000F0000
#घोषणा LOAD_RSP_FLAGS0_SHIFT           16
#घोषणा LOAD_RSP_FLAGS0_DRV_EXISTS      (0x1 << 0)
पूर्ण;

काष्ठा mdump_retain_data_stc अणु
	u32 valid;
	u32 epoch;
	u32 pf;
	u32 status;
पूर्ण;

जोड़ drv_जोड़_data अणु
	u32 ver_str[MCP_DRV_VER_STR_SIZE_DWORD];
	काष्ठा mcp_mac wol_mac;

	काष्ठा eth_phy_cfg drv_phy_cfg;

	काष्ठा mcp_val64 val64;

	u8 raw_data[MCP_DRV_NVM_BUF_LEN];

	काष्ठा mcp_file_att file_att;

	u32 ack_vf_disabled[VF_MAX_STATIC / 32];

	काष्ठा drv_version_stc drv_version;

	काष्ठा lan_stats_stc lan_stats;
	काष्ठा fcoe_stats_stc fcoe_stats;
	काष्ठा ocbb_data_stc ocbb_info;
	काष्ठा temperature_status_stc temp_info;
	काष्ठा resource_info resource;
	काष्ठा bist_nvm_image_att nvm_image_att;
	काष्ठा mdump_config_stc mdump_config;
पूर्ण;

काष्ठा खुला_drv_mb अणु
	u32 drv_mb_header;
#घोषणा DRV_MSG_CODE_MASK			0xffff0000
#घोषणा DRV_MSG_CODE_LOAD_REQ			0x10000000
#घोषणा DRV_MSG_CODE_LOAD_DONE			0x11000000
#घोषणा DRV_MSG_CODE_INIT_HW			0x12000000
#घोषणा DRV_MSG_CODE_CANCEL_LOAD_REQ            0x13000000
#घोषणा DRV_MSG_CODE_UNLOAD_REQ			0x20000000
#घोषणा DRV_MSG_CODE_UNLOAD_DONE		0x21000000
#घोषणा DRV_MSG_CODE_INIT_PHY			0x22000000
#घोषणा DRV_MSG_CODE_LINK_RESET			0x23000000
#घोषणा DRV_MSG_CODE_SET_DCBX			0x25000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_CURR_CFG         0x26000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_BUS_NUM          0x27000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_BOOT_PROGRESS    0x28000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_STORM_FW_VER     0x29000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE     0x31000000
#घोषणा DRV_MSG_CODE_BW_UPDATE_ACK              0x32000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_MTU              0x33000000
#घोषणा DRV_MSG_GET_RESOURCE_ALLOC_MSG		0x34000000
#घोषणा DRV_MSG_SET_RESOURCE_VALUE_MSG		0x35000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_WOL              0x38000000
#घोषणा DRV_MSG_CODE_OV_UPDATE_ESWITCH_MODE     0x39000000
#घोषणा DRV_MSG_CODE_GET_OEM_UPDATES            0x41000000

#घोषणा DRV_MSG_CODE_BW_UPDATE_ACK		0x32000000
#घोषणा DRV_MSG_CODE_NIG_DRAIN			0x30000000
#घोषणा DRV_MSG_CODE_S_TAG_UPDATE_ACK		0x3b000000
#घोषणा DRV_MSG_CODE_GET_NVM_CFG_OPTION		0x003e0000
#घोषणा DRV_MSG_CODE_SET_NVM_CFG_OPTION		0x003f0000
#घोषणा DRV_MSG_CODE_INITIATE_PF_FLR            0x02010000
#घोषणा DRV_MSG_CODE_VF_DISABLED_DONE		0xc0000000
#घोषणा DRV_MSG_CODE_CFG_VF_MSIX		0xc0010000
#घोषणा DRV_MSG_CODE_CFG_PF_VFS_MSIX		0xc0020000
#घोषणा DRV_MSG_CODE_NVM_PUT_खाता_BEGIN		0x00010000
#घोषणा DRV_MSG_CODE_NVM_PUT_खाता_DATA		0x00020000
#घोषणा DRV_MSG_CODE_NVM_GET_खाता_ATT		0x00030000
#घोषणा DRV_MSG_CODE_NVM_READ_NVRAM		0x00050000
#घोषणा DRV_MSG_CODE_NVM_WRITE_NVRAM		0x00060000
#घोषणा DRV_MSG_CODE_MCP_RESET			0x00090000
#घोषणा DRV_MSG_CODE_SET_VERSION		0x000f0000
#घोषणा DRV_MSG_CODE_MCP_HALT                   0x00100000
#घोषणा DRV_MSG_CODE_SET_VMAC                   0x00110000
#घोषणा DRV_MSG_CODE_GET_VMAC                   0x00120000
#घोषणा DRV_MSG_CODE_VMAC_TYPE_SHIFT            4
#घोषणा DRV_MSG_CODE_VMAC_TYPE_MASK             0x30
#घोषणा DRV_MSG_CODE_VMAC_TYPE_MAC              1
#घोषणा DRV_MSG_CODE_VMAC_TYPE_WWNN             2
#घोषणा DRV_MSG_CODE_VMAC_TYPE_WWPN             3

#घोषणा DRV_MSG_CODE_GET_STATS                  0x00130000
#घोषणा DRV_MSG_CODE_STATS_TYPE_LAN             1
#घोषणा DRV_MSG_CODE_STATS_TYPE_FCOE            2
#घोषणा DRV_MSG_CODE_STATS_TYPE_ISCSI           3
#घोषणा DRV_MSG_CODE_STATS_TYPE_RDMA            4

#घोषणा DRV_MSG_CODE_TRANSCEIVER_READ           0x00160000

#घोषणा DRV_MSG_CODE_MASK_PARITIES              0x001a0000

#घोषणा DRV_MSG_CODE_BIST_TEST			0x001e0000
#घोषणा DRV_MSG_CODE_SET_LED_MODE		0x00200000
#घोषणा DRV_MSG_CODE_RESOURCE_CMD		0x00230000
/* Send crash dump commands with param[3:0] - opcode */
#घोषणा DRV_MSG_CODE_MDUMP_CMD			0x00250000
#घोषणा DRV_MSG_CODE_GET_TLV_DONE		0x002f0000
#घोषणा DRV_MSG_CODE_GET_ENGINE_CONFIG		0x00370000
#घोषणा DRV_MSG_CODE_GET_PPFID_BITMAP		0x43000000

#घोषणा DRV_MSG_CODE_DEBUG_DATA_SEND		0xc0040000

#घोषणा RESOURCE_CMD_REQ_RESC_MASK		0x0000001F
#घोषणा RESOURCE_CMD_REQ_RESC_SHIFT		0
#घोषणा RESOURCE_CMD_REQ_OPCODE_MASK		0x000000E0
#घोषणा RESOURCE_CMD_REQ_OPCODE_SHIFT		5
#घोषणा RESOURCE_OPCODE_REQ			1
#घोषणा RESOURCE_OPCODE_REQ_WO_AGING		2
#घोषणा RESOURCE_OPCODE_REQ_W_AGING		3
#घोषणा RESOURCE_OPCODE_RELEASE			4
#घोषणा RESOURCE_OPCODE_FORCE_RELEASE		5
#घोषणा RESOURCE_CMD_REQ_AGE_MASK		0x0000FF00
#घोषणा RESOURCE_CMD_REQ_AGE_SHIFT		8

#घोषणा RESOURCE_CMD_RSP_OWNER_MASK		0x000000FF
#घोषणा RESOURCE_CMD_RSP_OWNER_SHIFT		0
#घोषणा RESOURCE_CMD_RSP_OPCODE_MASK		0x00000700
#घोषणा RESOURCE_CMD_RSP_OPCODE_SHIFT		8
#घोषणा RESOURCE_OPCODE_GNT			1
#घोषणा RESOURCE_OPCODE_BUSY			2
#घोषणा RESOURCE_OPCODE_RELEASED		3
#घोषणा RESOURCE_OPCODE_RELEASED_PREVIOUS	4
#घोषणा RESOURCE_OPCODE_WRONG_OWNER		5
#घोषणा RESOURCE_OPCODE_UNKNOWN_CMD		255

#घोषणा RESOURCE_DUMP				0

/* DRV_MSG_CODE_MDUMP_CMD parameters */
#घोषणा MDUMP_DRV_PARAM_OPCODE_MASK             0x0000000f
#घोषणा DRV_MSG_CODE_MDUMP_ACK                  0x01
#घोषणा DRV_MSG_CODE_MDUMP_SET_VALUES           0x02
#घोषणा DRV_MSG_CODE_MDUMP_TRIGGER              0x03
#घोषणा DRV_MSG_CODE_MDUMP_GET_CONFIG           0x04
#घोषणा DRV_MSG_CODE_MDUMP_SET_ENABLE           0x05
#घोषणा DRV_MSG_CODE_MDUMP_CLEAR_LOGS           0x06
#घोषणा DRV_MSG_CODE_MDUMP_GET_RETAIN           0x07
#घोषणा DRV_MSG_CODE_MDUMP_CLR_RETAIN           0x08

#घोषणा DRV_MSG_CODE_HW_DUMP_TRIGGER            0x0a
#घोषणा DRV_MSG_CODE_MDUMP_GEN_MDUMP2           0x0b
#घोषणा DRV_MSG_CODE_MDUMP_FREE_MDUMP2          0x0c

#घोषणा DRV_MSG_CODE_GET_PF_RDMA_PROTOCOL	0x002b0000
#घोषणा DRV_MSG_CODE_OS_WOL			0x002e0000

#घोषणा DRV_MSG_CODE_FEATURE_SUPPORT		0x00300000
#घोषणा DRV_MSG_CODE_GET_MFW_FEATURE_SUPPORT	0x00310000
#घोषणा DRV_MSG_SEQ_NUMBER_MASK			0x0000ffff

	u32 drv_mb_param;
#घोषणा DRV_MB_PARAM_UNLOAD_WOL_UNKNOWN         0x00000000
#घोषणा DRV_MB_PARAM_UNLOAD_WOL_MCP             0x00000001
#घोषणा DRV_MB_PARAM_UNLOAD_WOL_DISABLED        0x00000002
#घोषणा DRV_MB_PARAM_UNLOAD_WOL_ENABLED         0x00000003
#घोषणा DRV_MB_PARAM_DCBX_NOTIFY_MASK		0x000000FF
#घोषणा DRV_MB_PARAM_DCBX_NOTIFY_SHIFT		3

#घोषणा DRV_MB_PARAM_NVM_PUT_खाता_BEGIN_MBI     0x3
#घोषणा DRV_MB_PARAM_NVM_OFFSET_OFFSET          0
#घोषणा DRV_MB_PARAM_NVM_OFFSET_MASK            0x00FFFFFF
#घोषणा DRV_MB_PARAM_NVM_LEN_OFFSET		24
#घोषणा DRV_MB_PARAM_NVM_LEN_MASK               0xFF000000

#घोषणा DRV_MB_PARAM_CFG_VF_MSIX_VF_ID_SHIFT	0
#घोषणा DRV_MB_PARAM_CFG_VF_MSIX_VF_ID_MASK	0x000000FF
#घोषणा DRV_MB_PARAM_CFG_VF_MSIX_SB_NUM_SHIFT	8
#घोषणा DRV_MB_PARAM_CFG_VF_MSIX_SB_NUM_MASK	0x0000FF00
#घोषणा DRV_MB_PARAM_LLDP_SEND_MASK		0x00000001
#घोषणा DRV_MB_PARAM_LLDP_SEND_SHIFT		0

#घोषणा DRV_MB_PARAM_OV_CURR_CFG_SHIFT		0
#घोषणा DRV_MB_PARAM_OV_CURR_CFG_MASK		0x0000000F
#घोषणा DRV_MB_PARAM_OV_CURR_CFG_NONE		0
#घोषणा DRV_MB_PARAM_OV_CURR_CFG_OS		1
#घोषणा DRV_MB_PARAM_OV_CURR_CFG_VENDOR_SPEC	2
#घोषणा DRV_MB_PARAM_OV_CURR_CFG_OTHER		3

#घोषणा DRV_MB_PARAM_OV_STORM_FW_VER_SHIFT	0
#घोषणा DRV_MB_PARAM_OV_STORM_FW_VER_MASK	0xFFFFFFFF
#घोषणा DRV_MB_PARAM_OV_STORM_FW_VER_MAJOR_MASK	0xFF000000
#घोषणा DRV_MB_PARAM_OV_STORM_FW_VER_MINOR_MASK	0x00FF0000
#घोषणा DRV_MB_PARAM_OV_STORM_FW_VER_BUILD_MASK	0x0000FF00
#घोषणा DRV_MB_PARAM_OV_STORM_FW_VER_DROP_MASK	0x000000FF

#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_SHIFT	0
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_MASK	0xF
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_UNKNOWN	0x1
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_NOT_LOADED	0x2
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_LOADING	0x3
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_DISABLED	0x4
#घोषणा DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_ACTIVE	0x5

#घोषणा DRV_MB_PARAM_OV_MTU_SIZE_SHIFT	0
#घोषणा DRV_MB_PARAM_OV_MTU_SIZE_MASK	0xFFFFFFFF

#घोषणा DRV_MB_PARAM_WOL_MASK	(DRV_MB_PARAM_WOL_DEFAULT | \
				 DRV_MB_PARAM_WOL_DISABLED | \
				 DRV_MB_PARAM_WOL_ENABLED)
#घोषणा DRV_MB_PARAM_WOL_DEFAULT	DRV_MB_PARAM_UNLOAD_WOL_MCP
#घोषणा DRV_MB_PARAM_WOL_DISABLED	DRV_MB_PARAM_UNLOAD_WOL_DISABLED
#घोषणा DRV_MB_PARAM_WOL_ENABLED	DRV_MB_PARAM_UNLOAD_WOL_ENABLED

#घोषणा DRV_MB_PARAM_ESWITCH_MODE_MASK	(DRV_MB_PARAM_ESWITCH_MODE_NONE | \
					 DRV_MB_PARAM_ESWITCH_MODE_VEB | \
					 DRV_MB_PARAM_ESWITCH_MODE_VEPA)
#घोषणा DRV_MB_PARAM_ESWITCH_MODE_NONE	0x0
#घोषणा DRV_MB_PARAM_ESWITCH_MODE_VEB	0x1
#घोषणा DRV_MB_PARAM_ESWITCH_MODE_VEPA	0x2

#घोषणा DRV_MB_PARAM_DUMMY_OEM_UPDATES_MASK	0x1
#घोषणा DRV_MB_PARAM_DUMMY_OEM_UPDATES_OFFSET	0

#घोषणा DRV_MB_PARAM_SET_LED_MODE_OPER		0x0
#घोषणा DRV_MB_PARAM_SET_LED_MODE_ON		0x1
#घोषणा DRV_MB_PARAM_SET_LED_MODE_OFF		0x2

#घोषणा DRV_MB_PARAM_TRANSCEIVER_PORT_OFFSET			0
#घोषणा DRV_MB_PARAM_TRANSCEIVER_PORT_MASK			0x00000003
#घोषणा DRV_MB_PARAM_TRANSCEIVER_SIZE_OFFSET			2
#घोषणा DRV_MB_PARAM_TRANSCEIVER_SIZE_MASK			0x000000fc
#घोषणा DRV_MB_PARAM_TRANSCEIVER_I2C_ADDRESS_OFFSET		8
#घोषणा DRV_MB_PARAM_TRANSCEIVER_I2C_ADDRESS_MASK		0x0000ff00
#घोषणा DRV_MB_PARAM_TRANSCEIVER_OFFSET_OFFSET			16
#घोषणा DRV_MB_PARAM_TRANSCEIVER_OFFSET_MASK			0xffff0000

	/* Resource Allocation params - Driver version support */
#घोषणा DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR_MASK		0xffff0000
#घोषणा DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR_SHIFT		16
#घोषणा DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR_MASK		0x0000ffff
#घोषणा DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR_SHIFT		0

#घोषणा DRV_MB_PARAM_BIST_REGISTER_TEST				1
#घोषणा DRV_MB_PARAM_BIST_CLOCK_TEST				2
#घोषणा DRV_MB_PARAM_BIST_NVM_TEST_NUM_IMAGES			3
#घोषणा DRV_MB_PARAM_BIST_NVM_TEST_IMAGE_BY_INDEX		4

#घोषणा DRV_MB_PARAM_BIST_RC_UNKNOWN				0
#घोषणा DRV_MB_PARAM_BIST_RC_PASSED				1
#घोषणा DRV_MB_PARAM_BIST_RC_FAILED				2
#घोषणा DRV_MB_PARAM_BIST_RC_INVALID_PARAMETER			3

#घोषणा DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT			0
#घोषणा DRV_MB_PARAM_BIST_TEST_INDEX_MASK			0x000000ff
#घोषणा DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_SHIFT		8
#घोषणा DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_MASK			0x0000ff00

#घोषणा DRV_MB_PARAM_FEATURE_SUPPORT_PORT_MASK			0x0000ffff
#घोषणा DRV_MB_PARAM_FEATURE_SUPPORT_PORT_OFFSET		0
#घोषणा DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EEE			0x00000002
#घोषणा DRV_MB_PARAM_FEATURE_SUPPORT_PORT_FEC_CONTROL		0x00000004
#घोषणा DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EXT_SPEED_FEC_CONTROL	0x00000008
#घोषणा DRV_MB_PARAM_FEATURE_SUPPORT_FUNC_VLINK			0x00010000

/* DRV_MSG_CODE_DEBUG_DATA_SEND parameters */
#घोषणा DRV_MSG_CODE_DEBUG_DATA_SEND_SIZE_OFFSET		0
#घोषणा DRV_MSG_CODE_DEBUG_DATA_SEND_SIZE_MASK			0xff

/* Driver attributes params */
#घोषणा DRV_MB_PARAM_ATTRIBUTE_KEY_OFFSET			0
#घोषणा DRV_MB_PARAM_ATTRIBUTE_KEY_MASK				0x00ffffff
#घोषणा DRV_MB_PARAM_ATTRIBUTE_CMD_OFFSET			24
#घोषणा DRV_MB_PARAM_ATTRIBUTE_CMD_MASK				0xff000000

#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ID_OFFSET			0
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ID_SHIFT			0
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ID_MASK			0x0000ffff
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ALL_SHIFT			16
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ALL_MASK			0x00010000
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_INIT_SHIFT			17
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_INIT_MASK			0x00020000
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_COMMIT_SHIFT		18
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_COMMIT_MASK			0x00040000
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_FREE_SHIFT			19
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_FREE_MASK			0x00080000
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_SEL_SHIFT		20
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_SEL_MASK		0x00100000
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_ID_SHIFT		24
#घोषणा DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_ID_MASK		0x0f000000

	u32 fw_mb_header;
#घोषणा FW_MSG_CODE_MASK			0xffff0000
#घोषणा FW_MSG_CODE_UNSUPPORTED                 0x00000000
#घोषणा FW_MSG_CODE_DRV_LOAD_ENGINE		0x10100000
#घोषणा FW_MSG_CODE_DRV_LOAD_PORT		0x10110000
#घोषणा FW_MSG_CODE_DRV_LOAD_FUNCTION		0x10120000
#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED_PDA	0x10200000
#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED_HSI_1	0x10210000
#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED_DIAG	0x10220000
#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED_HSI        0x10230000
#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED_REQUIRES_FORCE 0x10300000
#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED_REJECT     0x10310000
#घोषणा FW_MSG_CODE_DRV_LOAD_DONE		0x11100000
#घोषणा FW_MSG_CODE_DRV_UNLOAD_ENGINE		0x20110000
#घोषणा FW_MSG_CODE_DRV_UNLOAD_PORT		0x20120000
#घोषणा FW_MSG_CODE_DRV_UNLOAD_FUNCTION		0x20130000
#घोषणा FW_MSG_CODE_DRV_UNLOAD_DONE		0x21100000
#घोषणा FW_MSG_CODE_RESOURCE_ALLOC_OK           0x34000000
#घोषणा FW_MSG_CODE_RESOURCE_ALLOC_UNKNOWN      0x35000000
#घोषणा FW_MSG_CODE_RESOURCE_ALLOC_DEPRECATED   0x36000000
#घोषणा FW_MSG_CODE_S_TAG_UPDATE_ACK_DONE	0x3b000000
#घोषणा FW_MSG_CODE_DRV_CFG_VF_MSIX_DONE	0xb0010000

#घोषणा FW_MSG_CODE_NVM_OK			0x00010000
#घोषणा FW_MSG_CODE_NVM_PUT_खाता_FINISH_OK	0x00400000
#घोषणा FW_MSG_CODE_PHY_OK			0x00110000
#घोषणा FW_MSG_CODE_OK				0x00160000
#घोषणा FW_MSG_CODE_ERROR			0x00170000
#घोषणा FW_MSG_CODE_TRANSCEIVER_DIAG_OK		0x00160000
#घोषणा FW_MSG_CODE_TRANSCEIVER_DIAG_ERROR	0x00170000
#घोषणा FW_MSG_CODE_TRANSCEIVER_NOT_PRESENT	0x00020000

#घोषणा FW_MSG_CODE_OS_WOL_SUPPORTED            0x00800000
#घोषणा FW_MSG_CODE_OS_WOL_NOT_SUPPORTED        0x00810000
#घोषणा FW_MSG_CODE_DRV_CFG_PF_VFS_MSIX_DONE	0x00870000
#घोषणा FW_MSG_SEQ_NUMBER_MASK			0x0000ffff

#घोषणा FW_MSG_CODE_DEBUG_DATA_SEND_INV_ARG	0xb0070000
#घोषणा FW_MSG_CODE_DEBUG_DATA_SEND_BUF_FULL	0xb0080000
#घोषणा FW_MSG_CODE_DEBUG_DATA_SEND_NO_BUF	0xb0090000
#घोषणा FW_MSG_CODE_DEBUG_NOT_ENABLED		0xb00a0000
#घोषणा FW_MSG_CODE_DEBUG_DATA_SEND_OK		0xb00b0000

#घोषणा FW_MSG_CODE_MDUMP_INVALID_CMD		0x00030000

	u32							fw_mb_param;
#घोषणा FW_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR_MASK		0xffff0000
#घोषणा FW_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR_SHIFT		16
#घोषणा FW_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR_MASK		0x0000ffff
#घोषणा FW_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR_SHIFT		0

	/* Get PF RDMA protocol command response */
#घोषणा FW_MB_PARAM_GET_PF_RDMA_NONE				0x0
#घोषणा FW_MB_PARAM_GET_PF_RDMA_ROCE				0x1
#घोषणा FW_MB_PARAM_GET_PF_RDMA_IWARP				0x2
#घोषणा FW_MB_PARAM_GET_PF_RDMA_BOTH				0x3

	/* Get MFW feature support response */
#घोषणा FW_MB_PARAM_FEATURE_SUPPORT_SMARTLINQ			BIT(0)
#घोषणा FW_MB_PARAM_FEATURE_SUPPORT_EEE				BIT(1)
#घोषणा FW_MB_PARAM_FEATURE_SUPPORT_FEC_CONTROL			BIT(5)
#घोषणा FW_MB_PARAM_FEATURE_SUPPORT_EXT_SPEED_FEC_CONTROL	BIT(6)
#घोषणा FW_MB_PARAM_FEATURE_SUPPORT_VLINK			BIT(16)

#घोषणा FW_MB_PARAM_LOAD_DONE_DID_EFUSE_ERROR			BIT(0)

#घोषणा FW_MB_PARAM_ENG_CFG_FIR_AFFIN_VALID_MASK		0x00000001
#घोषणा FW_MB_PARAM_ENG_CFG_FIR_AFFIN_VALID_SHIFT		0
#घोषणा FW_MB_PARAM_ENG_CFG_FIR_AFFIN_VALUE_MASK		0x00000002
#घोषणा FW_MB_PARAM_ENG_CFG_FIR_AFFIN_VALUE_SHIFT		1
#घोषणा FW_MB_PARAM_ENG_CFG_L2_AFFIN_VALID_MASK			0x00000004
#घोषणा FW_MB_PARAM_ENG_CFG_L2_AFFIN_VALID_SHIFT		2
#घोषणा FW_MB_PARAM_ENG_CFG_L2_AFFIN_VALUE_MASK			0x00000008
#घोषणा FW_MB_PARAM_ENG_CFG_L2_AFFIN_VALUE_SHIFT		3

#घोषणा FW_MB_PARAM_PPFID_BITMAP_MASK				0xff
#घोषणा FW_MB_PARAM_PPFID_BITMAP_SHIFT				0

	u32							drv_pulse_mb;
#घोषणा DRV_PULSE_SEQ_MASK					0x00007fff
#घोषणा DRV_PULSE_SYSTEM_TIME_MASK				0xffff0000
#घोषणा DRV_PULSE_ALWAYS_ALIVE					0x00008000

	u32							mcp_pulse_mb;
#घोषणा MCP_PULSE_SEQ_MASK					0x00007fff
#घोषणा MCP_PULSE_ALWAYS_ALIVE					0x00008000
#घोषणा MCP_EVENT_MASK						0xffff0000
#घोषणा MCP_EVENT_OTHER_DRIVER_RESET_REQ			0x00010000

	जोड़ drv_जोड़_data					जोड़_data;
पूर्ण;

#घोषणा FW_MB_PARAM_NVM_PUT_खाता_REQ_OFFSET_MASK		0x00ffffff
#घोषणा FW_MB_PARAM_NVM_PUT_खाता_REQ_OFFSET_SHIFT		0
#घोषणा FW_MB_PARAM_NVM_PUT_खाता_REQ_SIZE_MASK			0xff000000
#घोषणा FW_MB_PARAM_NVM_PUT_खाता_REQ_SIZE_SHIFT			24

क्रमागत MFW_DRV_MSG_TYPE अणु
	MFW_DRV_MSG_LINK_CHANGE,
	MFW_DRV_MSG_FLR_FW_ACK_FAILED,
	MFW_DRV_MSG_VF_DISABLED,
	MFW_DRV_MSG_LLDP_DATA_UPDATED,
	MFW_DRV_MSG_DCBX_REMOTE_MIB_UPDATED,
	MFW_DRV_MSG_DCBX_OPERATIONAL_MIB_UPDATED,
	MFW_DRV_MSG_ERROR_RECOVERY,
	MFW_DRV_MSG_BW_UPDATE,
	MFW_DRV_MSG_S_TAG_UPDATE,
	MFW_DRV_MSG_GET_LAN_STATS,
	MFW_DRV_MSG_GET_FCOE_STATS,
	MFW_DRV_MSG_GET_ISCSI_STATS,
	MFW_DRV_MSG_GET_RDMA_STATS,
	MFW_DRV_MSG_FAILURE_DETECTED,
	MFW_DRV_MSG_TRANSCEIVER_STATE_CHANGE,
	MFW_DRV_MSG_CRITICAL_ERROR_OCCURRED,
	MFW_DRV_MSG_RESERVED,
	MFW_DRV_MSG_GET_TLV_REQ,
	MFW_DRV_MSG_OEM_CFG_UPDATE,
	MFW_DRV_MSG_MAX
पूर्ण;

#घोषणा MFW_DRV_MSG_MAX_DWORDS(msgs)	(((msgs - 1) >> 2) + 1)
#घोषणा MFW_DRV_MSG_DWORD(msg_id)	(msg_id >> 2)
#घोषणा MFW_DRV_MSG_OFFSET(msg_id)	((msg_id & 0x3) << 3)
#घोषणा MFW_DRV_MSG_MASK(msg_id)	(0xff << MFW_DRV_MSG_OFFSET(msg_id))

काष्ठा खुला_mfw_mb अणु
	u32 sup_msgs;
	u32 msg[MFW_DRV_MSG_MAX_DWORDS(MFW_DRV_MSG_MAX)];
	u32 ack[MFW_DRV_MSG_MAX_DWORDS(MFW_DRV_MSG_MAX)];
पूर्ण;

क्रमागत खुला_sections अणु
	PUBLIC_DRV_MB,
	PUBLIC_MFW_MB,
	PUBLIC_GLOBAL,
	PUBLIC_PATH,
	PUBLIC_PORT,
	PUBLIC_FUNC,
	PUBLIC_MAX_SECTIONS
पूर्ण;

काष्ठा mcp_खुला_data अणु
	u32 num_sections;
	u32 sections[PUBLIC_MAX_SECTIONS];
	काष्ठा खुला_drv_mb drv_mb[MCP_GLOB_FUNC_MAX];
	काष्ठा खुला_mfw_mb mfw_mb[MCP_GLOB_FUNC_MAX];
	काष्ठा खुला_global global;
	काष्ठा खुला_path path[MCP_GLOB_PATH_MAX];
	काष्ठा खुला_port port[MCP_GLOB_PORT_MAX];
	काष्ठा खुला_func func[MCP_GLOB_FUNC_MAX];
पूर्ण;

#घोषणा MAX_I2C_TRANSACTION_SIZE	16

/* OCBB definitions */
क्रमागत tlvs अणु
	/* Category 1: Device Properties */
	DRV_TLV_CLP_STR,
	DRV_TLV_CLP_STR_CTD,
	/* Category 6: Device Configuration */
	DRV_TLV_SCSI_TO,
	DRV_TLV_R_T_TOV,
	DRV_TLV_R_A_TOV,
	DRV_TLV_E_D_TOV,
	DRV_TLV_CR_TOV,
	DRV_TLV_BOOT_TYPE,
	/* Category 8: Port Configuration */
	DRV_TLV_NPIV_ENABLED,
	/* Category 10: Function Configuration */
	DRV_TLV_FEATURE_FLAGS,
	DRV_TLV_LOCAL_ADMIN_ADDR,
	DRV_TLV_ADDITIONAL_MAC_ADDR_1,
	DRV_TLV_ADDITIONAL_MAC_ADDR_2,
	DRV_TLV_LSO_MAX_OFFLOAD_SIZE,
	DRV_TLV_LSO_MIN_SEGMENT_COUNT,
	DRV_TLV_PROMISCUOUS_MODE,
	DRV_TLV_TX_DESCRIPTORS_QUEUE_SIZE,
	DRV_TLV_RX_DESCRIPTORS_QUEUE_SIZE,
	DRV_TLV_NUM_OF_NET_QUEUE_VMQ_CFG,
	DRV_TLV_FLEX_NIC_OUTER_VLAN_ID,
	DRV_TLV_OS_DRIVER_STATES,
	DRV_TLV_PXE_BOOT_PROGRESS,
	/* Category 12: FC/FCoE Configuration */
	DRV_TLV_NPIV_STATE,
	DRV_TLV_NUM_OF_NPIV_IDS,
	DRV_TLV_SWITCH_NAME,
	DRV_TLV_SWITCH_PORT_NUM,
	DRV_TLV_SWITCH_PORT_ID,
	DRV_TLV_VENDOR_NAME,
	DRV_TLV_SWITCH_MODEL,
	DRV_TLV_SWITCH_FW_VER,
	DRV_TLV_QOS_PRIORITY_PER_802_1P,
	DRV_TLV_PORT_ALIAS,
	DRV_TLV_PORT_STATE,
	DRV_TLV_FIP_TX_DESCRIPTORS_QUEUE_SIZE,
	DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_SIZE,
	DRV_TLV_LINK_FAILURE_COUNT,
	DRV_TLV_FCOE_BOOT_PROGRESS,
	/* Category 13: iSCSI Configuration */
	DRV_TLV_TARGET_LLMNR_ENABLED,
	DRV_TLV_HEADER_DIGEST_FLAG_ENABLED,
	DRV_TLV_DATA_DIGEST_FLAG_ENABLED,
	DRV_TLV_AUTHENTICATION_METHOD,
	DRV_TLV_ISCSI_BOOT_TARGET_PORTAL,
	DRV_TLV_MAX_FRAME_SIZE,
	DRV_TLV_PDU_TX_DESCRIPTORS_QUEUE_SIZE,
	DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_SIZE,
	DRV_TLV_ISCSI_BOOT_PROGRESS,
	/* Category 20: Device Data */
	DRV_TLV_PCIE_BUS_RX_UTILIZATION,
	DRV_TLV_PCIE_BUS_TX_UTILIZATION,
	DRV_TLV_DEVICE_CPU_CORES_UTILIZATION,
	DRV_TLV_LAST_VALID_DCC_TLV_RECEIVED,
	DRV_TLV_NCSI_RX_BYTES_RECEIVED,
	DRV_TLV_NCSI_TX_BYTES_SENT,
	/* Category 22: Base Port Data */
	DRV_TLV_RX_DISCARDS,
	DRV_TLV_RX_ERRORS,
	DRV_TLV_TX_ERRORS,
	DRV_TLV_TX_DISCARDS,
	DRV_TLV_RX_FRAMES_RECEIVED,
	DRV_TLV_TX_FRAMES_SENT,
	/* Category 23: FC/FCoE Port Data */
	DRV_TLV_RX_BROADCAST_PACKETS,
	DRV_TLV_TX_BROADCAST_PACKETS,
	/* Category 28: Base Function Data */
	DRV_TLV_NUM_OFFLOADED_CONNECTIONS_TCP_IPV4,
	DRV_TLV_NUM_OFFLOADED_CONNECTIONS_TCP_IPV6,
	DRV_TLV_TX_DESCRIPTOR_QUEUE_AVG_DEPTH,
	DRV_TLV_RX_DESCRIPTORS_QUEUE_AVG_DEPTH,
	DRV_TLV_PF_RX_FRAMES_RECEIVED,
	DRV_TLV_RX_BYTES_RECEIVED,
	DRV_TLV_PF_TX_FRAMES_SENT,
	DRV_TLV_TX_BYTES_SENT,
	DRV_TLV_IOV_OFFLOAD,
	DRV_TLV_PCI_ERRORS_CAP_ID,
	DRV_TLV_UNCORRECTABLE_ERROR_STATUS,
	DRV_TLV_UNCORRECTABLE_ERROR_MASK,
	DRV_TLV_CORRECTABLE_ERROR_STATUS,
	DRV_TLV_CORRECTABLE_ERROR_MASK,
	DRV_TLV_PCI_ERRORS_AECC_REGISTER,
	DRV_TLV_TX_QUEUES_EMPTY,
	DRV_TLV_RX_QUEUES_EMPTY,
	DRV_TLV_TX_QUEUES_FULL,
	DRV_TLV_RX_QUEUES_FULL,
	/* Category 29: FC/FCoE Function Data */
	DRV_TLV_FCOE_TX_DESCRIPTOR_QUEUE_AVG_DEPTH,
	DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_AVG_DEPTH,
	DRV_TLV_FCOE_RX_FRAMES_RECEIVED,
	DRV_TLV_FCOE_RX_BYTES_RECEIVED,
	DRV_TLV_FCOE_TX_FRAMES_SENT,
	DRV_TLV_FCOE_TX_BYTES_SENT,
	DRV_TLV_CRC_ERROR_COUNT,
	DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_CRC_ERROR_1_TIMESTAMP,
	DRV_TLV_CRC_ERROR_2_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_CRC_ERROR_2_TIMESTAMP,
	DRV_TLV_CRC_ERROR_3_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_CRC_ERROR_3_TIMESTAMP,
	DRV_TLV_CRC_ERROR_4_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_CRC_ERROR_4_TIMESTAMP,
	DRV_TLV_CRC_ERROR_5_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_CRC_ERROR_5_TIMESTAMP,
	DRV_TLV_LOSS_OF_SYNC_ERROR_COUNT,
	DRV_TLV_LOSS_OF_SIGNAL_ERRORS,
	DRV_TLV_PRIMITIVE_SEQUENCE_PROTOCOL_ERROR_COUNT,
	DRV_TLV_DISPARITY_ERROR_COUNT,
	DRV_TLV_CODE_VIOLATION_ERROR_COUNT,
	DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1,
	DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_2,
	DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_3,
	DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_4,
	DRV_TLV_LAST_FLOGI_TIMESTAMP,
	DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1,
	DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_2,
	DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_3,
	DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_4,
	DRV_TLV_LAST_FLOGI_ACC_TIMESTAMP,
	DRV_TLV_LAST_FLOGI_RJT,
	DRV_TLV_LAST_FLOGI_RJT_TIMESTAMP,
	DRV_TLV_FDISCS_SENT_COUNT,
	DRV_TLV_FDISC_ACCS_RECEIVED,
	DRV_TLV_FDISC_RJTS_RECEIVED,
	DRV_TLV_PLOGI_SENT_COUNT,
	DRV_TLV_PLOGI_ACCS_RECEIVED,
	DRV_TLV_PLOGI_RJTS_RECEIVED,
	DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID,
	DRV_TLV_PLOGI_1_TIMESTAMP,
	DRV_TLV_PLOGI_2_SENT_DESTINATION_FC_ID,
	DRV_TLV_PLOGI_2_TIMESTAMP,
	DRV_TLV_PLOGI_3_SENT_DESTINATION_FC_ID,
	DRV_TLV_PLOGI_3_TIMESTAMP,
	DRV_TLV_PLOGI_4_SENT_DESTINATION_FC_ID,
	DRV_TLV_PLOGI_4_TIMESTAMP,
	DRV_TLV_PLOGI_5_SENT_DESTINATION_FC_ID,
	DRV_TLV_PLOGI_5_TIMESTAMP,
	DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_PLOGI_1_ACC_TIMESTAMP,
	DRV_TLV_PLOGI_2_ACC_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_PLOGI_2_ACC_TIMESTAMP,
	DRV_TLV_PLOGI_3_ACC_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_PLOGI_3_ACC_TIMESTAMP,
	DRV_TLV_PLOGI_4_ACC_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_PLOGI_4_ACC_TIMESTAMP,
	DRV_TLV_PLOGI_5_ACC_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_PLOGI_5_ACC_TIMESTAMP,
	DRV_TLV_LOGOS_ISSUED,
	DRV_TLV_LOGO_ACCS_RECEIVED,
	DRV_TLV_LOGO_RJTS_RECEIVED,
	DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_LOGO_1_TIMESTAMP,
	DRV_TLV_LOGO_2_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_LOGO_2_TIMESTAMP,
	DRV_TLV_LOGO_3_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_LOGO_3_TIMESTAMP,
	DRV_TLV_LOGO_4_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_LOGO_4_TIMESTAMP,
	DRV_TLV_LOGO_5_RECEIVED_SOURCE_FC_ID,
	DRV_TLV_LOGO_5_TIMESTAMP,
	DRV_TLV_LOGOS_RECEIVED,
	DRV_TLV_ACCS_ISSUED,
	DRV_TLV_PRLIS_ISSUED,
	DRV_TLV_ACCS_RECEIVED,
	DRV_TLV_ABTS_SENT_COUNT,
	DRV_TLV_ABTS_ACCS_RECEIVED,
	DRV_TLV_ABTS_RJTS_RECEIVED,
	DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID,
	DRV_TLV_ABTS_1_TIMESTAMP,
	DRV_TLV_ABTS_2_SENT_DESTINATION_FC_ID,
	DRV_TLV_ABTS_2_TIMESTAMP,
	DRV_TLV_ABTS_3_SENT_DESTINATION_FC_ID,
	DRV_TLV_ABTS_3_TIMESTAMP,
	DRV_TLV_ABTS_4_SENT_DESTINATION_FC_ID,
	DRV_TLV_ABTS_4_TIMESTAMP,
	DRV_TLV_ABTS_5_SENT_DESTINATION_FC_ID,
	DRV_TLV_ABTS_5_TIMESTAMP,
	DRV_TLV_RSCNS_RECEIVED,
	DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1,
	DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_2,
	DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_3,
	DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_4,
	DRV_TLV_LUN_RESETS_ISSUED,
	DRV_TLV_ABORT_TASK_SETS_ISSUED,
	DRV_TLV_TPRLOS_SENT,
	DRV_TLV_NOS_SENT_COUNT,
	DRV_TLV_NOS_RECEIVED_COUNT,
	DRV_TLV_OLS_COUNT,
	DRV_TLV_LR_COUNT,
	DRV_TLV_LRR_COUNT,
	DRV_TLV_LIP_SENT_COUNT,
	DRV_TLV_LIP_RECEIVED_COUNT,
	DRV_TLV_खातापूर्णA_COUNT,
	DRV_TLV_खातापूर्णNI_COUNT,
	DRV_TLV_SCSI_STATUS_CHECK_CONDITION_COUNT,
	DRV_TLV_SCSI_STATUS_CONDITION_MET_COUNT,
	DRV_TLV_SCSI_STATUS_BUSY_COUNT,
	DRV_TLV_SCSI_STATUS_INTERMEDIATE_COUNT,
	DRV_TLV_SCSI_STATUS_INTERMEDIATE_CONDITION_MET_COUNT,
	DRV_TLV_SCSI_STATUS_RESERVATION_CONFLICT_COUNT,
	DRV_TLV_SCSI_STATUS_TASK_SET_FULL_COUNT,
	DRV_TLV_SCSI_STATUS_ACA_ACTIVE_COUNT,
	DRV_TLV_SCSI_STATUS_TASK_ABORTED_COUNT,
	DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ,
	DRV_TLV_SCSI_CHECK_1_TIMESTAMP,
	DRV_TLV_SCSI_CHECK_CONDITION_2_RECEIVED_SK_ASC_ASCQ,
	DRV_TLV_SCSI_CHECK_2_TIMESTAMP,
	DRV_TLV_SCSI_CHECK_CONDITION_3_RECEIVED_SK_ASC_ASCQ,
	DRV_TLV_SCSI_CHECK_3_TIMESTAMP,
	DRV_TLV_SCSI_CHECK_CONDITION_4_RECEIVED_SK_ASC_ASCQ,
	DRV_TLV_SCSI_CHECK_4_TIMESTAMP,
	DRV_TLV_SCSI_CHECK_CONDITION_5_RECEIVED_SK_ASC_ASCQ,
	DRV_TLV_SCSI_CHECK_5_TIMESTAMP,
	/* Category 30: iSCSI Function Data */
	DRV_TLV_PDU_TX_DESCRIPTOR_QUEUE_AVG_DEPTH,
	DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_AVG_DEPTH,
	DRV_TLV_ISCSI_PDU_RX_FRAMES_RECEIVED,
	DRV_TLV_ISCSI_PDU_RX_BYTES_RECEIVED,
	DRV_TLV_ISCSI_PDU_TX_FRAMES_SENT,
	DRV_TLV_ISCSI_PDU_TX_BYTES_SENT
पूर्ण;

काष्ठा nvm_cfg_mac_address अणु
	u32							mac_addr_hi;
#घोषणा NVM_CFG_MAC_ADDRESS_HI_MASK				0x0000ffff
#घोषणा NVM_CFG_MAC_ADDRESS_HI_OFFSET				0

	u32							mac_addr_lo;
पूर्ण;

काष्ठा nvm_cfg1_glob अणु
	u32							generic_cont0;
#घोषणा NVM_CFG1_GLOB_MF_MODE_MASK				0x00000ff0
#घोषणा NVM_CFG1_GLOB_MF_MODE_OFFSET				4
#घोषणा NVM_CFG1_GLOB_MF_MODE_MF_ALLOWED			0x0
#घोषणा NVM_CFG1_GLOB_MF_MODE_DEFAULT				0x1
#घोषणा NVM_CFG1_GLOB_MF_MODE_SPIO4				0x2
#घोषणा NVM_CFG1_GLOB_MF_MODE_NPAR1_0				0x3
#घोषणा NVM_CFG1_GLOB_MF_MODE_NPAR1_5				0x4
#घोषणा NVM_CFG1_GLOB_MF_MODE_NPAR2_0				0x5
#घोषणा NVM_CFG1_GLOB_MF_MODE_BD				0x6
#घोषणा NVM_CFG1_GLOB_MF_MODE_UFP				0x7

	u32							engineering_change[3];
	u32							manufacturing_id;
	u32							serial_number[4];
	u32							pcie_cfg;
	u32							mgmt_traffic;

	u32							core_cfg;
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_MASK			0x000000ff
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_OFFSET			0
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_2X40G		0x0
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_2X50G			0x1
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_1X100G		0x2
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_4X10G_F			0x3
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_4X10G_E		0x4
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_4X20G		0x5
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_1X40G			0xb
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_2X25G			0xc
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_1X25G			0xd
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_4X25G			0xe
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_2X10G			0xf
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_2X50G_R1		0x11
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_4X50G_R1		0x12
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_1X100G_R2		0x13
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_2X100G_R2		0x14
#घोषणा NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_1X100G_R4		0x15

	u32							e_lane_cfg1;
	u32							e_lane_cfg2;
	u32							f_lane_cfg1;
	u32							f_lane_cfg2;
	u32							mps10_preemphasis;
	u32							mps10_driver_current;
	u32							mps25_preemphasis;
	u32							mps25_driver_current;
	u32							pci_id;
	u32							pci_subsys_id;
	u32							bar;
	u32							mps10_txfir_मुख्य;
	u32							mps10_txfir_post;
	u32							mps25_txfir_मुख्य;
	u32							mps25_txfir_post;
	u32							manufacture_ver;
	u32							manufacture_समय;
	u32							led_global_settings;
	u32							generic_cont1;

	u32							mbi_version;
#घोषणा NVM_CFG1_GLOB_MBI_VERSION_0_MASK			0x000000ff
#घोषणा NVM_CFG1_GLOB_MBI_VERSION_0_OFFSET			0
#घोषणा NVM_CFG1_GLOB_MBI_VERSION_1_MASK			0x0000ff00
#घोषणा NVM_CFG1_GLOB_MBI_VERSION_1_OFFSET			8
#घोषणा NVM_CFG1_GLOB_MBI_VERSION_2_MASK			0x00ff0000
#घोषणा NVM_CFG1_GLOB_MBI_VERSION_2_OFFSET			16

	u32							mbi_date;
	u32							misc_sig;

	u32							device_capabilities;
#घोषणा NVM_CFG1_GLOB_DEVICE_CAPABILITIES_ETHERNET		0x1
#घोषणा NVM_CFG1_GLOB_DEVICE_CAPABILITIES_FCOE			0x2
#घोषणा NVM_CFG1_GLOB_DEVICE_CAPABILITIES_ISCSI			0x4
#घोषणा NVM_CFG1_GLOB_DEVICE_CAPABILITIES_ROCE			0x8

	u32							घातer_dissipated;
	u32							घातer_consumed;
	u32							efi_version;
	u32							multi_net_modes_cap;
	u32							reserved[41];
पूर्ण;

काष्ठा nvm_cfg1_path अणु
	u32							reserved[30];
पूर्ण;

काष्ठा nvm_cfg1_port अणु
	u32							rel_to_opt123;
	u32							rel_to_opt124;

	u32							generic_cont0;
#घोषणा NVM_CFG1_PORT_DCBX_MODE_MASK				0x000f0000
#घोषणा NVM_CFG1_PORT_DCBX_MODE_OFFSET				16
#घोषणा NVM_CFG1_PORT_DCBX_MODE_DISABLED			0x0
#घोषणा NVM_CFG1_PORT_DCBX_MODE_IEEE				0x1
#घोषणा NVM_CFG1_PORT_DCBX_MODE_CEE				0x2
#घोषणा NVM_CFG1_PORT_DCBX_MODE_DYNAMIC				0x3
#घोषणा NVM_CFG1_PORT_DEFAULT_ENABLED_PROTOCOLS_MASK		0x00f00000
#घोषणा NVM_CFG1_PORT_DEFAULT_ENABLED_PROTOCOLS_OFFSET		20
#घोषणा NVM_CFG1_PORT_DEFAULT_ENABLED_PROTOCOLS_ETHERNET	0x1
#घोषणा NVM_CFG1_PORT_DEFAULT_ENABLED_PROTOCOLS_FCOE		0x2
#घोषणा NVM_CFG1_PORT_DEFAULT_ENABLED_PROTOCOLS_ISCSI		0x4

	u32							pcie_cfg;
	u32							features;

	u32							speed_cap_mask;
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_MASK		0x0000ffff
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_OFFSET		0
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G		0x1
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G		0x2
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G		0x4
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G		0x8
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G		0x10
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G		0x20
#घोषणा NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G		0x40

	u32							link_settings;
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_MASK			0x0000000f
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_OFFSET			0
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_AUTONEG			0x0
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_1G				0x1
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_10G			0x2
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_20G			0x3
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_25G			0x4
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_40G			0x5
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_50G			0x6
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_BB_100G			0x7
#घोषणा NVM_CFG1_PORT_DRV_LINK_SPEED_SMARTLINQ			0x8
#घोषणा NVM_CFG1_PORT_DRV_FLOW_CONTROL_MASK			0x00000070
#घोषणा NVM_CFG1_PORT_DRV_FLOW_CONTROL_OFFSET			4
#घोषणा NVM_CFG1_PORT_DRV_FLOW_CONTROL_AUTONEG			0x1
#घोषणा NVM_CFG1_PORT_DRV_FLOW_CONTROL_RX			0x2
#घोषणा NVM_CFG1_PORT_DRV_FLOW_CONTROL_TX			0x4
#घोषणा NVM_CFG1_PORT_FEC_FORCE_MODE_MASK			0x000e0000
#घोषणा NVM_CFG1_PORT_FEC_FORCE_MODE_OFFSET			17
#घोषणा NVM_CFG1_PORT_FEC_FORCE_MODE_NONE			0x0
#घोषणा NVM_CFG1_PORT_FEC_FORCE_MODE_FIRECODE			0x1
#घोषणा NVM_CFG1_PORT_FEC_FORCE_MODE_RS				0x2
#घोषणा NVM_CFG1_PORT_FEC_FORCE_MODE_AUTO			0x7

	u32							phy_cfg;
	u32							mgmt_traffic;

	u32							ext_phy;
	/* EEE घातer saving mode */
#घोषणा NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_MASK		0x00ff0000
#घोषणा NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_OFFSET		16
#घोषणा NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_DISABLED		0x0
#घोषणा NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_BALANCED		0x1
#घोषणा NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_AGGRESSIVE		0x2
#घोषणा NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_LOW_LATENCY		0x3

	u32							mba_cfg1;
	u32							mba_cfg2;
	u32							vf_cfg;
	काष्ठा nvm_cfg_mac_address				lldp_mac_address;
	u32							led_port_settings;
	u32							transceiver_00;
	u32							device_ids;

	u32							board_cfg;
#घोषणा NVM_CFG1_PORT_PORT_TYPE_MASK				0x000000ff
#घोषणा NVM_CFG1_PORT_PORT_TYPE_OFFSET				0
#घोषणा NVM_CFG1_PORT_PORT_TYPE_UNDEFINED			0x0
#घोषणा NVM_CFG1_PORT_PORT_TYPE_MODULE				0x1
#घोषणा NVM_CFG1_PORT_PORT_TYPE_BACKPLANE			0x2
#घोषणा NVM_CFG1_PORT_PORT_TYPE_EXT_PHY				0x3
#घोषणा NVM_CFG1_PORT_PORT_TYPE_MODULE_SLAVE			0x4

	u32							mnm_10g_cap;
	u32							mnm_10g_ctrl;
	u32							mnm_10g_misc;
	u32							mnm_25g_cap;
	u32							mnm_25g_ctrl;
	u32							mnm_25g_misc;
	u32							mnm_40g_cap;
	u32							mnm_40g_ctrl;
	u32							mnm_40g_misc;
	u32							mnm_50g_cap;
	u32							mnm_50g_ctrl;
	u32							mnm_50g_misc;
	u32							mnm_100g_cap;
	u32							mnm_100g_ctrl;
	u32							mnm_100g_misc;

	u32							temperature;
	u32							ext_phy_cfg1;

	u32							extended_speed;
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_MASK			0x0000ffff
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_OFFSET			0
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_AN		0x1
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_1G		0x2
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_10G		0x4
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_20G		0x8
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_25G		0x10
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_40G		0x20
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_50G_R		0x40
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_50G_R2		0x80
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_100G_R2		0x100
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_100G_R4		0x200
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_100G_P4		0x400
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_MASK			0xffff0000
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_OFFSET			16
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_RESERVED	0x1
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_1G		0x2
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_10G		0x4
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_20G		0x8
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_25G		0x10
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_40G		0x20
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_50G_R	0x40
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_50G_R2	0x80
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_100G_R2	0x100
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_100G_R4	0x200
#घोषणा NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_100G_P4	0x400

	u32							extended_fec_mode;

	u32							reserved[112];
पूर्ण;

काष्ठा nvm_cfg1_func अणु
	काष्ठा nvm_cfg_mac_address mac_address;
	u32 rsrv1;
	u32 rsrv2;
	u32 device_id;
	u32 cmn_cfg;
	u32 pci_cfg;
	काष्ठा nvm_cfg_mac_address fcoe_node_wwn_mac_addr;
	काष्ठा nvm_cfg_mac_address fcoe_port_wwn_mac_addr;
	u32 preboot_generic_cfg;
	u32 reserved[8];
पूर्ण;

काष्ठा nvm_cfg1 अणु
	काष्ठा nvm_cfg1_glob glob;
	काष्ठा nvm_cfg1_path path[MCP_GLOB_PATH_MAX];
	काष्ठा nvm_cfg1_port port[MCP_GLOB_PORT_MAX];
	काष्ठा nvm_cfg1_func func[MCP_GLOB_FUNC_MAX];
पूर्ण;

क्रमागत spad_sections अणु
	SPAD_SECTION_TRACE,
	SPAD_SECTION_NVM_CFG,
	SPAD_SECTION_PUBLIC,
	SPAD_SECTION_PRIVATE,
	SPAD_SECTION_MAX
पूर्ण;

#घोषणा MCP_TRACE_SIZE          2048	/* 2kb */

/* This section is located at a fixed location in the beginning of the
 * scratchpad, to ensure that the MCP trace is not run over during MFW upgrade.
 * All the rest of data has a भग्नing location which dअगरfers from version to
 * version, and is poपूर्णांकed by the mcp_meta_data below.
 * Moreover, the spad_layout section is part of the MFW firmware, and is loaded
 * with it from nvram in order to clear this portion.
 */
काष्ठा अटल_init अणु
	u32 num_sections;
	offमाप_प्रकार sections[SPAD_SECTION_MAX];
#घोषणा SECTION(_sec_) (*((offमाप_प्रकार *)(STRUCT_OFFSET(sections[_sec_]))))

	काष्ठा mcp_trace trace;
#घोषणा MCP_TRACE_P ((काष्ठा mcp_trace *)(STRUCT_OFFSET(trace)))
	u8 trace_buffer[MCP_TRACE_SIZE];
#घोषणा MCP_TRACE_BUF ((u8 *)(STRUCT_OFFSET(trace_buffer)))
	/* running_mfw has the same definition as in nvm_map.h.
	 * This bit indicate both the running dir, and the running bundle.
	 * It is set once when the LIM is loaded.
	 */
	u32 running_mfw;
#घोषणा RUNNING_MFW (*((u32 *)(STRUCT_OFFSET(running_mfw))))
	u32 build_समय;
#घोषणा MFW_BUILD_TIME (*((u32 *)(STRUCT_OFFSET(build_समय))))
	u32 reset_type;
#घोषणा RESET_TYPE (*((u32 *)(STRUCT_OFFSET(reset_type))))
	u32 mfw_secure_mode;
#घोषणा MFW_SECURE_MODE (*((u32 *)(STRUCT_OFFSET(mfw_secure_mode))))
	u16 pme_status_pf_biपंचांगap;
#घोषणा PME_STATUS_PF_BITMAP (*((u16 *)(STRUCT_OFFSET(pme_status_pf_biपंचांगap))))
	u16 pme_enable_pf_biपंचांगap;
#घोषणा PME_ENABLE_PF_BITMAP (*((u16 *)(STRUCT_OFFSET(pme_enable_pf_biपंचांगap))))
	u32 mim_nvm_addr;
	u32 mim_start_addr;
	u32 ah_pcie_link_params;
#घोषणा AH_PCIE_LINK_PARAMS_LINK_SPEED_MASK     (0x000000ff)
#घोषणा AH_PCIE_LINK_PARAMS_LINK_SPEED_SHIFT    (0)
#घोषणा AH_PCIE_LINK_PARAMS_LINK_WIDTH_MASK     (0x0000ff00)
#घोषणा AH_PCIE_LINK_PARAMS_LINK_WIDTH_SHIFT    (8)
#घोषणा AH_PCIE_LINK_PARAMS_ASPM_MODE_MASK      (0x00ff0000)
#घोषणा AH_PCIE_LINK_PARAMS_ASPM_MODE_SHIFT     (16)
#घोषणा AH_PCIE_LINK_PARAMS_ASPM_CAP_MASK       (0xff000000)
#घोषणा AH_PCIE_LINK_PARAMS_ASPM_CAP_SHIFT      (24)
#घोषणा AH_PCIE_LINK_PARAMS (*((u32 *)(STRUCT_OFFSET(ah_pcie_link_params))))

	u32 rsrv_persist[5];	/* Persist reserved क्रम MFW upgrades */
पूर्ण;

#घोषणा NVM_MAGIC_VALUE		0x669955aa

क्रमागत nvm_image_type अणु
	NVM_TYPE_TIM1 = 0x01,
	NVM_TYPE_TIM2 = 0x02,
	NVM_TYPE_MIM1 = 0x03,
	NVM_TYPE_MIM2 = 0x04,
	NVM_TYPE_MBA = 0x05,
	NVM_TYPE_MODULES_PN = 0x06,
	NVM_TYPE_VPD = 0x07,
	NVM_TYPE_MFW_TRACE1 = 0x08,
	NVM_TYPE_MFW_TRACE2 = 0x09,
	NVM_TYPE_NVM_CFG1 = 0x0a,
	NVM_TYPE_L2B = 0x0b,
	NVM_TYPE_सूची1 = 0x0c,
	NVM_TYPE_EAGLE_FW1 = 0x0d,
	NVM_TYPE_FALCON_FW1 = 0x0e,
	NVM_TYPE_PCIE_FW1 = 0x0f,
	NVM_TYPE_HW_SET = 0x10,
	NVM_TYPE_LIM = 0x11,
	NVM_TYPE_AVS_FW1 = 0x12,
	NVM_TYPE_सूची2 = 0x13,
	NVM_TYPE_CCM = 0x14,
	NVM_TYPE_EAGLE_FW2 = 0x15,
	NVM_TYPE_FALCON_FW2 = 0x16,
	NVM_TYPE_PCIE_FW2 = 0x17,
	NVM_TYPE_AVS_FW2 = 0x18,
	NVM_TYPE_INIT_HW = 0x19,
	NVM_TYPE_DEFAULT_CFG = 0x1a,
	NVM_TYPE_MDUMP = 0x1b,
	NVM_TYPE_META = 0x1c,
	NVM_TYPE_ISCSI_CFG = 0x1d,
	NVM_TYPE_FCOE_CFG = 0x1f,
	NVM_TYPE_ETH_PHY_FW1 = 0x20,
	NVM_TYPE_ETH_PHY_FW2 = 0x21,
	NVM_TYPE_BDN = 0x22,
	NVM_TYPE_8485X_PHY_FW = 0x23,
	NVM_TYPE_PUB_KEY = 0x24,
	NVM_TYPE_RECOVERY = 0x25,
	NVM_TYPE_PLDM = 0x26,
	NVM_TYPE_UPK1 = 0x27,
	NVM_TYPE_UPK2 = 0x28,
	NVM_TYPE_MASTER_KC = 0x29,
	NVM_TYPE_BACKUP_KC = 0x2a,
	NVM_TYPE_HW_DUMP = 0x2b,
	NVM_TYPE_HW_DUMP_OUT = 0x2c,
	NVM_TYPE_BIN_NVM_META = 0x30,
	NVM_TYPE_ROM_TEST = 0xf0,
	NVM_TYPE_88X33X0_PHY_FW = 0x31,
	NVM_TYPE_88X33X0_PHY_SLAVE_FW = 0x32,
	NVM_TYPE_MAX,
पूर्ण;

#घोषणा सूची_ID_1    (0)

#पूर्ण_अगर
