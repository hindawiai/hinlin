<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
// Copyright (c) 2016-2017 Hisilicon Limited.

#अगर_अघोषित __HCLGE_MAIN_H
#घोषणा __HCLGE_MAIN_H
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kfअगरo.h>

#समावेश "hclge_cmd.h"
#समावेश "hnae3.h"

#घोषणा HCLGE_MOD_VERSION "1.0"
#घोषणा HCLGE_DRIVER_NAME "hclge"

#घोषणा HCLGE_MAX_PF_NUM		8

#घोषणा HCLGE_VF_VPORT_START_NUM	1

#घोषणा HCLGE_RD_FIRST_STATS_NUM        2
#घोषणा HCLGE_RD_OTHER_STATS_NUM        4

#घोषणा HCLGE_INVALID_VPORT 0xffff

#घोषणा HCLGE_PF_CFG_BLOCK_SIZE		32
#घोषणा HCLGE_PF_CFG_DESC_NUM \
	(HCLGE_PF_CFG_BLOCK_SIZE / HCLGE_CFG_RD_LEN_BYTES)

#घोषणा HCLGE_VECTOR_REG_BASE		0x20000
#घोषणा HCLGE_VECTOR_EXT_REG_BASE	0x30000
#घोषणा HCLGE_MISC_VECTOR_REG_BASE	0x20400

#घोषणा HCLGE_VECTOR_REG_OFFSET		0x4
#घोषणा HCLGE_VECTOR_REG_OFFSET_H	0x1000
#घोषणा HCLGE_VECTOR_VF_OFFSET		0x100000

#घोषणा HCLGE_CMDQ_TX_ADDR_L_REG	0x27000
#घोषणा HCLGE_CMDQ_TX_ADDR_H_REG	0x27004
#घोषणा HCLGE_CMDQ_TX_DEPTH_REG		0x27008
#घोषणा HCLGE_CMDQ_TX_TAIL_REG		0x27010
#घोषणा HCLGE_CMDQ_TX_HEAD_REG		0x27014
#घोषणा HCLGE_CMDQ_RX_ADDR_L_REG	0x27018
#घोषणा HCLGE_CMDQ_RX_ADDR_H_REG	0x2701C
#घोषणा HCLGE_CMDQ_RX_DEPTH_REG		0x27020
#घोषणा HCLGE_CMDQ_RX_TAIL_REG		0x27024
#घोषणा HCLGE_CMDQ_RX_HEAD_REG		0x27028
#घोषणा HCLGE_CMDQ_INTR_STS_REG		0x27104
#घोषणा HCLGE_CMDQ_INTR_EN_REG		0x27108
#घोषणा HCLGE_CMDQ_INTR_GEN_REG		0x2710C

/* bar रेजिस्टरs क्रम common func */
#घोषणा HCLGE_VECTOR0_OTER_EN_REG	0x20600
#घोषणा HCLGE_GRO_EN_REG		0x28000

/* bar रेजिस्टरs क्रम rcb */
#घोषणा HCLGE_RING_RX_ADDR_L_REG	0x80000
#घोषणा HCLGE_RING_RX_ADDR_H_REG	0x80004
#घोषणा HCLGE_RING_RX_BD_NUM_REG	0x80008
#घोषणा HCLGE_RING_RX_BD_LENGTH_REG	0x8000C
#घोषणा HCLGE_RING_RX_MERGE_EN_REG	0x80014
#घोषणा HCLGE_RING_RX_TAIL_REG		0x80018
#घोषणा HCLGE_RING_RX_HEAD_REG		0x8001C
#घोषणा HCLGE_RING_RX_FBD_NUM_REG	0x80020
#घोषणा HCLGE_RING_RX_OFFSET_REG	0x80024
#घोषणा HCLGE_RING_RX_FBD_OFFSET_REG	0x80028
#घोषणा HCLGE_RING_RX_STASH_REG		0x80030
#घोषणा HCLGE_RING_RX_BD_ERR_REG	0x80034
#घोषणा HCLGE_RING_TX_ADDR_L_REG	0x80040
#घोषणा HCLGE_RING_TX_ADDR_H_REG	0x80044
#घोषणा HCLGE_RING_TX_BD_NUM_REG	0x80048
#घोषणा HCLGE_RING_TX_PRIORITY_REG	0x8004C
#घोषणा HCLGE_RING_TX_TC_REG		0x80050
#घोषणा HCLGE_RING_TX_MERGE_EN_REG	0x80054
#घोषणा HCLGE_RING_TX_TAIL_REG		0x80058
#घोषणा HCLGE_RING_TX_HEAD_REG		0x8005C
#घोषणा HCLGE_RING_TX_FBD_NUM_REG	0x80060
#घोषणा HCLGE_RING_TX_OFFSET_REG	0x80064
#घोषणा HCLGE_RING_TX_EBD_NUM_REG	0x80068
#घोषणा HCLGE_RING_TX_EBD_OFFSET_REG	0x80070
#घोषणा HCLGE_RING_TX_BD_ERR_REG	0x80074
#घोषणा HCLGE_RING_EN_REG		0x80090

/* bar रेजिस्टरs क्रम tqp पूर्णांकerrupt */
#घोषणा HCLGE_TQP_INTR_CTRL_REG		0x20000
#घोषणा HCLGE_TQP_INTR_GL0_REG		0x20100
#घोषणा HCLGE_TQP_INTR_GL1_REG		0x20200
#घोषणा HCLGE_TQP_INTR_GL2_REG		0x20300
#घोषणा HCLGE_TQP_INTR_RL_REG		0x20900

#घोषणा HCLGE_RSS_IND_TBL_SIZE		512
#घोषणा HCLGE_RSS_SET_BITMAP_MSK	GENMASK(15, 0)
#घोषणा HCLGE_RSS_KEY_SIZE		40
#घोषणा HCLGE_RSS_HASH_ALGO_TOEPLITZ	0
#घोषणा HCLGE_RSS_HASH_ALGO_SIMPLE	1
#घोषणा HCLGE_RSS_HASH_ALGO_SYMMETRIC	2
#घोषणा HCLGE_RSS_HASH_ALGO_MASK	GENMASK(3, 0)

#घोषणा HCLGE_RSS_INPUT_TUPLE_OTHER	GENMASK(3, 0)
#घोषणा HCLGE_RSS_INPUT_TUPLE_SCTP	GENMASK(4, 0)
#घोषणा HCLGE_D_PORT_BIT		BIT(0)
#घोषणा HCLGE_S_PORT_BIT		BIT(1)
#घोषणा HCLGE_D_IP_BIT			BIT(2)
#घोषणा HCLGE_S_IP_BIT			BIT(3)
#घोषणा HCLGE_V_TAG_BIT			BIT(4)
#घोषणा HCLGE_RSS_INPUT_TUPLE_SCTP_NO_PORT	\
		(HCLGE_D_IP_BIT | HCLGE_S_IP_BIT | HCLGE_V_TAG_BIT)

#घोषणा HCLGE_RSS_TC_SIZE_0		1
#घोषणा HCLGE_RSS_TC_SIZE_1		2
#घोषणा HCLGE_RSS_TC_SIZE_2		4
#घोषणा HCLGE_RSS_TC_SIZE_3		8
#घोषणा HCLGE_RSS_TC_SIZE_4		16
#घोषणा HCLGE_RSS_TC_SIZE_5		32
#घोषणा HCLGE_RSS_TC_SIZE_6		64
#घोषणा HCLGE_RSS_TC_SIZE_7		128

#घोषणा HCLGE_UMV_TBL_SIZE		3072
#घोषणा HCLGE_DEFAULT_UMV_SPACE_PER_PF \
	(HCLGE_UMV_TBL_SIZE / HCLGE_MAX_PF_NUM)

#घोषणा HCLGE_TQP_RESET_TRY_TIMES	200

#घोषणा HCLGE_PHY_PAGE_MDIX		0
#घोषणा HCLGE_PHY_PAGE_COPPER		0

/* Page Selection Reg. */
#घोषणा HCLGE_PHY_PAGE_REG		22

/* Copper Specअगरic Control Register */
#घोषणा HCLGE_PHY_CSC_REG		16

/* Copper Specअगरic Status Register */
#घोषणा HCLGE_PHY_CSS_REG		17

#घोषणा HCLGE_PHY_MDIX_CTRL_S		5
#घोषणा HCLGE_PHY_MDIX_CTRL_M		GENMASK(6, 5)

#घोषणा HCLGE_PHY_MDIX_STATUS_B		6
#घोषणा HCLGE_PHY_SPEED_DUP_RESOLVE_B	11

#घोषणा HCLGE_GET_DFX_REG_TYPE_CNT	4

/* Factor used to calculate offset and biपंचांगap of VF num */
#घोषणा HCLGE_VF_NUM_PER_CMD           64

#घोषणा HCLGE_MAX_QSET_NUM		1024

क्रमागत HLCGE_PORT_TYPE अणु
	HOST_PORT,
	NETWORK_PORT
पूर्ण;

#घोषणा PF_VPORT_ID			0

#घोषणा HCLGE_PF_ID_S			0
#घोषणा HCLGE_PF_ID_M			GENMASK(2, 0)
#घोषणा HCLGE_VF_ID_S			3
#घोषणा HCLGE_VF_ID_M			GENMASK(10, 3)
#घोषणा HCLGE_PORT_TYPE_B		11
#घोषणा HCLGE_NETWORK_PORT_ID_S		0
#घोषणा HCLGE_NETWORK_PORT_ID_M		GENMASK(3, 0)

/* Reset related Registers */
#घोषणा HCLGE_PF_OTHER_INT_REG		0x20600
#घोषणा HCLGE_MISC_RESET_STS_REG	0x20700
#घोषणा HCLGE_MISC_VECTOR_INT_STS	0x20800
#घोषणा HCLGE_GLOBAL_RESET_REG		0x20A00
#घोषणा HCLGE_GLOBAL_RESET_BIT		0
#घोषणा HCLGE_CORE_RESET_BIT		1
#घोषणा HCLGE_IMP_RESET_BIT		2
#घोषणा HCLGE_RESET_INT_M		GENMASK(7, 5)
#घोषणा HCLGE_FUN_RST_ING		0x20C00
#घोषणा HCLGE_FUN_RST_ING_B		0

/* Vector0 रेजिस्टर bits define */
#घोषणा HCLGE_VECTOR0_GLOBALRESET_INT_B	5
#घोषणा HCLGE_VECTOR0_CORERESET_INT_B	6
#घोषणा HCLGE_VECTOR0_IMPRESET_INT_B	7

/* Vector0 पूर्णांकerrupt CMDQ event source रेजिस्टर(RW) */
#घोषणा HCLGE_VECTOR0_CMDQ_SRC_REG	0x27100
/* CMDQ रेजिस्टर bits क्रम RX event(=MBX event) */
#घोषणा HCLGE_VECTOR0_RX_CMDQ_INT_B	1

#घोषणा HCLGE_VECTOR0_IMP_RESET_INT_B	1
#घोषणा HCLGE_VECTOR0_IMP_CMDQ_ERR_B	4U
#घोषणा HCLGE_VECTOR0_IMP_RD_POISON_B	5U

#घोषणा HCLGE_MAC_DEFAULT_FRAME \
	(ETH_HLEN + ETH_FCS_LEN + 2 * VLAN_HLEN + ETH_DATA_LEN)
#घोषणा HCLGE_MAC_MIN_FRAME		64
#घोषणा HCLGE_MAC_MAX_FRAME		9728

#घोषणा HCLGE_SUPPORT_1G_BIT		BIT(0)
#घोषणा HCLGE_SUPPORT_10G_BIT		BIT(1)
#घोषणा HCLGE_SUPPORT_25G_BIT		BIT(2)
#घोषणा HCLGE_SUPPORT_50G_BIT		BIT(3)
#घोषणा HCLGE_SUPPORT_100G_BIT		BIT(4)
/* to be compatible with exsit board */
#घोषणा HCLGE_SUPPORT_40G_BIT		BIT(5)
#घोषणा HCLGE_SUPPORT_100M_BIT		BIT(6)
#घोषणा HCLGE_SUPPORT_10M_BIT		BIT(7)
#घोषणा HCLGE_SUPPORT_200G_BIT		BIT(8)
#घोषणा HCLGE_SUPPORT_GE \
	(HCLGE_SUPPORT_1G_BIT | HCLGE_SUPPORT_100M_BIT | HCLGE_SUPPORT_10M_BIT)

क्रमागत HCLGE_DEV_STATE अणु
	HCLGE_STATE_REINITING,
	HCLGE_STATE_DOWN,
	HCLGE_STATE_DISABLED,
	HCLGE_STATE_REMOVING,
	HCLGE_STATE_NIC_REGISTERED,
	HCLGE_STATE_ROCE_REGISTERED,
	HCLGE_STATE_SERVICE_INITED,
	HCLGE_STATE_RST_SERVICE_SCHED,
	HCLGE_STATE_RST_HANDLING,
	HCLGE_STATE_MBX_SERVICE_SCHED,
	HCLGE_STATE_MBX_HANDLING,
	HCLGE_STATE_STATISTICS_UPDATING,
	HCLGE_STATE_CMD_DISABLE,
	HCLGE_STATE_LINK_UPDATING,
	HCLGE_STATE_PROMISC_CHANGED,
	HCLGE_STATE_RST_FAIL,
	HCLGE_STATE_FD_TBL_CHANGED,
	HCLGE_STATE_FD_CLEAR_ALL,
	HCLGE_STATE_FD_USER_DEF_CHANGED,
	HCLGE_STATE_MAX
पूर्ण;

क्रमागत hclge_evt_cause अणु
	HCLGE_VECTOR0_EVENT_RST,
	HCLGE_VECTOR0_EVENT_MBX,
	HCLGE_VECTOR0_EVENT_ERR,
	HCLGE_VECTOR0_EVENT_OTHER,
पूर्ण;

क्रमागत HCLGE_MAC_SPEED अणु
	HCLGE_MAC_SPEED_UNKNOWN = 0,		/* unknown */
	HCLGE_MAC_SPEED_10M	= 10,		/* 10 Mbps */
	HCLGE_MAC_SPEED_100M	= 100,		/* 100 Mbps */
	HCLGE_MAC_SPEED_1G	= 1000,		/* 1000 Mbps   = 1 Gbps */
	HCLGE_MAC_SPEED_10G	= 10000,	/* 10000 Mbps  = 10 Gbps */
	HCLGE_MAC_SPEED_25G	= 25000,	/* 25000 Mbps  = 25 Gbps */
	HCLGE_MAC_SPEED_40G	= 40000,	/* 40000 Mbps  = 40 Gbps */
	HCLGE_MAC_SPEED_50G	= 50000,	/* 50000 Mbps  = 50 Gbps */
	HCLGE_MAC_SPEED_100G	= 100000,	/* 100000 Mbps = 100 Gbps */
	HCLGE_MAC_SPEED_200G	= 200000	/* 200000 Mbps = 200 Gbps */
पूर्ण;

क्रमागत HCLGE_MAC_DUPLEX अणु
	HCLGE_MAC_HALF,
	HCLGE_MAC_FULL
पूर्ण;

#घोषणा QUERY_SFP_SPEED		0
#घोषणा QUERY_ACTIVE_SPEED	1

काष्ठा hclge_mac अणु
	u8 mac_id;
	u8 phy_addr;
	u8 flag;
	u8 media_type;	/* port media type, e.g. fibre/copper/backplane */
	u8 mac_addr[ETH_ALEN];
	u8 स्वतःneg;
	u8 duplex;
	u8 support_स्वतःneg;
	u8 speed_type;	/* 0: sfp speed, 1: active speed */
	u32 speed;
	u32 max_speed;
	u32 speed_ability; /* speed ability supported by current media */
	u32 module_type; /* sub media type, e.g. kr/cr/sr/lr */
	u32 fec_mode; /* active fec mode */
	u32 user_fec_mode;
	u32 fec_ability;
	पूर्णांक link;	/* store the link status of mac & phy (अगर phy exists) */
	काष्ठा phy_device *phydev;
	काष्ठा mii_bus *mdio_bus;
	phy_पूर्णांकerface_t phy_अगर;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising);
पूर्ण;

काष्ठा hclge_hw अणु
	व्योम __iomem *io_base;
	व्योम __iomem *mem_base;
	काष्ठा hclge_mac mac;
	पूर्णांक num_vec;
	काष्ठा hclge_cmq cmq;
पूर्ण;

/* TQP stats */
काष्ठा hlcge_tqp_stats अणु
	/* query_tqp_tx_queue_statistics ,opcode id:  0x0B03 */
	u64 rcb_tx_ring_pktnum_rcd; /* 32bit */
	/* query_tqp_rx_queue_statistics ,opcode id:  0x0B13 */
	u64 rcb_rx_ring_pktnum_rcd; /* 32bit */
पूर्ण;

काष्ठा hclge_tqp अणु
	/* copy of device poपूर्णांकer from pci_dev,
	 * used when perक्रमm DMA mapping
	 */
	काष्ठा device *dev;
	काष्ठा hnae3_queue q;
	काष्ठा hlcge_tqp_stats tqp_stats;
	u16 index;	/* Global index in a NIC controller */

	bool alloced;
पूर्ण;

क्रमागत hclge_fc_mode अणु
	HCLGE_FC_NONE,
	HCLGE_FC_RX_PAUSE,
	HCLGE_FC_TX_PAUSE,
	HCLGE_FC_FULL,
	HCLGE_FC_PFC,
	HCLGE_FC_DEFAULT
पूर्ण;

क्रमागत hclge_link_fail_code अणु
	HCLGE_LF_NORMAL,
	HCLGE_LF_REF_CLOCK_LOST,
	HCLGE_LF_XSFP_TX_DISABLE,
	HCLGE_LF_XSFP_ABSENT,
पूर्ण;

#घोषणा HCLGE_LINK_STATUS_DOWN 0
#घोषणा HCLGE_LINK_STATUS_UP   1

#घोषणा HCLGE_PG_NUM		4
#घोषणा HCLGE_SCH_MODE_SP	0
#घोषणा HCLGE_SCH_MODE_DWRR	1
काष्ठा hclge_pg_info अणु
	u8 pg_id;
	u8 pg_sch_mode;		/* 0: sp; 1: dwrr */
	u8 tc_bit_map;
	u32 bw_limit;
	u8 tc_dwrr[HNAE3_MAX_TC];
पूर्ण;

काष्ठा hclge_tc_info अणु
	u8 tc_id;
	u8 tc_sch_mode;		/* 0: sp; 1: dwrr */
	u8 pgid;
	u32 bw_limit;
पूर्ण;

काष्ठा hclge_cfg अणु
	u8 tc_num;
	u16 tqp_desc_num;
	u16 rx_buf_len;
	u16 vf_rss_size_max;
	u16 pf_rss_size_max;
	u8 phy_addr;
	u8 media_type;
	u8 mac_addr[ETH_ALEN];
	u8 शेष_speed;
	u32 numa_node_map;
	u16 speed_ability;
	u16 umv_space;
पूर्ण;

काष्ठा hclge_पंचांग_info अणु
	u8 num_tc;
	u8 num_pg;      /* It must be 1 अगर vNET-Base schd */
	u8 pg_dwrr[HCLGE_PG_NUM];
	u8 prio_tc[HNAE3_MAX_USER_PRIO];
	काष्ठा hclge_pg_info pg_info[HCLGE_PG_NUM];
	काष्ठा hclge_tc_info tc_info[HNAE3_MAX_TC];
	क्रमागत hclge_fc_mode fc_mode;
	u8 hw_pfc_map; /* Allow क्रम packet drop or not on this TC */
	u8 pfc_en;	/* PFC enabled or not क्रम user priority */
पूर्ण;

काष्ठा hclge_comm_stats_str अणु
	अक्षर desc[ETH_GSTRING_LEN];
	अचिन्हित दीर्घ offset;
पूर्ण;

/* mac stats ,opcode id: 0x0032 */
काष्ठा hclge_mac_stats अणु
	u64 mac_tx_mac_छोड़ो_num;
	u64 mac_rx_mac_छोड़ो_num;
	u64 mac_tx_pfc_pri0_pkt_num;
	u64 mac_tx_pfc_pri1_pkt_num;
	u64 mac_tx_pfc_pri2_pkt_num;
	u64 mac_tx_pfc_pri3_pkt_num;
	u64 mac_tx_pfc_pri4_pkt_num;
	u64 mac_tx_pfc_pri5_pkt_num;
	u64 mac_tx_pfc_pri6_pkt_num;
	u64 mac_tx_pfc_pri7_pkt_num;
	u64 mac_rx_pfc_pri0_pkt_num;
	u64 mac_rx_pfc_pri1_pkt_num;
	u64 mac_rx_pfc_pri2_pkt_num;
	u64 mac_rx_pfc_pri3_pkt_num;
	u64 mac_rx_pfc_pri4_pkt_num;
	u64 mac_rx_pfc_pri5_pkt_num;
	u64 mac_rx_pfc_pri6_pkt_num;
	u64 mac_rx_pfc_pri7_pkt_num;
	u64 mac_tx_total_pkt_num;
	u64 mac_tx_total_oct_num;
	u64 mac_tx_good_pkt_num;
	u64 mac_tx_bad_pkt_num;
	u64 mac_tx_good_oct_num;
	u64 mac_tx_bad_oct_num;
	u64 mac_tx_uni_pkt_num;
	u64 mac_tx_multi_pkt_num;
	u64 mac_tx_broad_pkt_num;
	u64 mac_tx_undersize_pkt_num;
	u64 mac_tx_oversize_pkt_num;
	u64 mac_tx_64_oct_pkt_num;
	u64 mac_tx_65_127_oct_pkt_num;
	u64 mac_tx_128_255_oct_pkt_num;
	u64 mac_tx_256_511_oct_pkt_num;
	u64 mac_tx_512_1023_oct_pkt_num;
	u64 mac_tx_1024_1518_oct_pkt_num;
	u64 mac_tx_1519_2047_oct_pkt_num;
	u64 mac_tx_2048_4095_oct_pkt_num;
	u64 mac_tx_4096_8191_oct_pkt_num;
	u64 rsv0;
	u64 mac_tx_8192_9216_oct_pkt_num;
	u64 mac_tx_9217_12287_oct_pkt_num;
	u64 mac_tx_12288_16383_oct_pkt_num;
	u64 mac_tx_1519_max_good_oct_pkt_num;
	u64 mac_tx_1519_max_bad_oct_pkt_num;

	u64 mac_rx_total_pkt_num;
	u64 mac_rx_total_oct_num;
	u64 mac_rx_good_pkt_num;
	u64 mac_rx_bad_pkt_num;
	u64 mac_rx_good_oct_num;
	u64 mac_rx_bad_oct_num;
	u64 mac_rx_uni_pkt_num;
	u64 mac_rx_multi_pkt_num;
	u64 mac_rx_broad_pkt_num;
	u64 mac_rx_undersize_pkt_num;
	u64 mac_rx_oversize_pkt_num;
	u64 mac_rx_64_oct_pkt_num;
	u64 mac_rx_65_127_oct_pkt_num;
	u64 mac_rx_128_255_oct_pkt_num;
	u64 mac_rx_256_511_oct_pkt_num;
	u64 mac_rx_512_1023_oct_pkt_num;
	u64 mac_rx_1024_1518_oct_pkt_num;
	u64 mac_rx_1519_2047_oct_pkt_num;
	u64 mac_rx_2048_4095_oct_pkt_num;
	u64 mac_rx_4096_8191_oct_pkt_num;
	u64 rsv1;
	u64 mac_rx_8192_9216_oct_pkt_num;
	u64 mac_rx_9217_12287_oct_pkt_num;
	u64 mac_rx_12288_16383_oct_pkt_num;
	u64 mac_rx_1519_max_good_oct_pkt_num;
	u64 mac_rx_1519_max_bad_oct_pkt_num;

	u64 mac_tx_fragment_pkt_num;
	u64 mac_tx_undermin_pkt_num;
	u64 mac_tx_jabber_pkt_num;
	u64 mac_tx_err_all_pkt_num;
	u64 mac_tx_from_app_good_pkt_num;
	u64 mac_tx_from_app_bad_pkt_num;
	u64 mac_rx_fragment_pkt_num;
	u64 mac_rx_undermin_pkt_num;
	u64 mac_rx_jabber_pkt_num;
	u64 mac_rx_fcs_err_pkt_num;
	u64 mac_rx_send_app_good_pkt_num;
	u64 mac_rx_send_app_bad_pkt_num;
	u64 mac_tx_pfc_छोड़ो_pkt_num;
	u64 mac_rx_pfc_छोड़ो_pkt_num;
	u64 mac_tx_ctrl_pkt_num;
	u64 mac_rx_ctrl_pkt_num;
पूर्ण;

#घोषणा HCLGE_STATS_TIMER_INTERVAL	300UL

काष्ठा hclge_vlan_type_cfg अणु
	u16 rx_ot_fst_vlan_type;
	u16 rx_ot_sec_vlan_type;
	u16 rx_in_fst_vlan_type;
	u16 rx_in_sec_vlan_type;
	u16 tx_ot_vlan_type;
	u16 tx_in_vlan_type;
पूर्ण;

क्रमागत HCLGE_FD_MODE अणु
	HCLGE_FD_MODE_DEPTH_2K_WIDTH_400B_STAGE_1,
	HCLGE_FD_MODE_DEPTH_1K_WIDTH_400B_STAGE_2,
	HCLGE_FD_MODE_DEPTH_4K_WIDTH_200B_STAGE_1,
	HCLGE_FD_MODE_DEPTH_2K_WIDTH_200B_STAGE_2,
पूर्ण;

क्रमागत HCLGE_FD_KEY_TYPE अणु
	HCLGE_FD_KEY_BASE_ON_PTYPE,
	HCLGE_FD_KEY_BASE_ON_TUPLE,
पूर्ण;

क्रमागत HCLGE_FD_STAGE अणु
	HCLGE_FD_STAGE_1,
	HCLGE_FD_STAGE_2,
	MAX_STAGE_NUM,
पूर्ण;

/* OUTER_XXX indicates tuples in tunnel header of tunnel packet
 * INNER_XXX indicate tuples in tunneled header of tunnel packet or
 *           tuples of non-tunnel packet
 */
क्रमागत HCLGE_FD_TUPLE अणु
	OUTER_DST_MAC,
	OUTER_SRC_MAC,
	OUTER_VLAN_TAG_FST,
	OUTER_VLAN_TAG_SEC,
	OUTER_ETH_TYPE,
	OUTER_L2_RSV,
	OUTER_IP_TOS,
	OUTER_IP_PROTO,
	OUTER_SRC_IP,
	OUTER_DST_IP,
	OUTER_L3_RSV,
	OUTER_SRC_PORT,
	OUTER_DST_PORT,
	OUTER_L4_RSV,
	OUTER_TUN_VNI,
	OUTER_TUN_FLOW_ID,
	INNER_DST_MAC,
	INNER_SRC_MAC,
	INNER_VLAN_TAG_FST,
	INNER_VLAN_TAG_SEC,
	INNER_ETH_TYPE,
	INNER_L2_RSV,
	INNER_IP_TOS,
	INNER_IP_PROTO,
	INNER_SRC_IP,
	INNER_DST_IP,
	INNER_L3_RSV,
	INNER_SRC_PORT,
	INNER_DST_PORT,
	INNER_L4_RSV,
	MAX_TUPLE,
पूर्ण;

#घोषणा HCLGE_FD_TUPLE_USER_DEF_TUPLES \
	(BIT(INNER_L2_RSV) | BIT(INNER_L3_RSV) | BIT(INNER_L4_RSV))

क्रमागत HCLGE_FD_META_DATA अणु
	PACKET_TYPE_ID,
	IP_FRAGEMENT,
	ROCE_TYPE,
	NEXT_KEY,
	VLAN_NUMBER,
	SRC_VPORT,
	DST_VPORT,
	TUNNEL_PACKET,
	MAX_META_DATA,
पूर्ण;

क्रमागत HCLGE_FD_KEY_OPT अणु
	KEY_OPT_U8,
	KEY_OPT_LE16,
	KEY_OPT_LE32,
	KEY_OPT_MAC,
	KEY_OPT_IP,
	KEY_OPT_VNI,
पूर्ण;

काष्ठा key_info अणु
	u8 key_type;
	u8 key_length; /* use bit as unit */
	क्रमागत HCLGE_FD_KEY_OPT key_opt;
	पूर्णांक offset;
	पूर्णांक moffset;
पूर्ण;

#घोषणा MAX_KEY_LENGTH	400
#घोषणा MAX_KEY_DWORDS	DIV_ROUND_UP(MAX_KEY_LENGTH / 8, 4)
#घोषणा MAX_KEY_BYTES	(MAX_KEY_DWORDS * 4)
#घोषणा MAX_META_DATA_LENGTH	32

#घोषणा HCLGE_FD_MAX_USER_DEF_OFFSET	9000
#घोषणा HCLGE_FD_USER_DEF_DATA		GENMASK(15, 0)
#घोषणा HCLGE_FD_USER_DEF_OFFSET	GENMASK(15, 0)
#घोषणा HCLGE_FD_USER_DEF_OFFSET_UNMASK	GENMASK(15, 0)

/* asचिन्हित by firmware, the real filter number क्रम each pf may be less */
#घोषणा MAX_FD_FILTER_NUM	4096
#घोषणा HCLGE_ARFS_EXPIRE_INTERVAL	5UL

क्रमागत HCLGE_FD_ACTIVE_RULE_TYPE अणु
	HCLGE_FD_RULE_NONE,
	HCLGE_FD_ARFS_ACTIVE,
	HCLGE_FD_EP_ACTIVE,
	HCLGE_FD_TC_FLOWER_ACTIVE,
पूर्ण;

क्रमागत HCLGE_FD_PACKET_TYPE अणु
	NIC_PACKET,
	ROCE_PACKET,
पूर्ण;

क्रमागत HCLGE_FD_ACTION अणु
	HCLGE_FD_ACTION_SELECT_QUEUE,
	HCLGE_FD_ACTION_DROP_PACKET,
	HCLGE_FD_ACTION_SELECT_TC,
पूर्ण;

क्रमागत HCLGE_FD_NODE_STATE अणु
	HCLGE_FD_TO_ADD,
	HCLGE_FD_TO_DEL,
	HCLGE_FD_ACTIVE,
	HCLGE_FD_DELETED,
पूर्ण;

क्रमागत HCLGE_FD_USER_DEF_LAYER अणु
	HCLGE_FD_USER_DEF_NONE,
	HCLGE_FD_USER_DEF_L2,
	HCLGE_FD_USER_DEF_L3,
	HCLGE_FD_USER_DEF_L4,
पूर्ण;

#घोषणा HCLGE_FD_USER_DEF_LAYER_NUM 3
काष्ठा hclge_fd_user_def_cfg अणु
	u16 ref_cnt;
	u16 offset;
पूर्ण;

काष्ठा hclge_fd_user_def_info अणु
	क्रमागत HCLGE_FD_USER_DEF_LAYER layer;
	u16 data;
	u16 data_mask;
	u16 offset;
पूर्ण;

काष्ठा hclge_fd_key_cfg अणु
	u8 key_sel;
	u8 inner_sipv6_word_en;
	u8 inner_dipv6_word_en;
	u8 outer_sipv6_word_en;
	u8 outer_dipv6_word_en;
	u32 tuple_active;
	u32 meta_data_active;
पूर्ण;

काष्ठा hclge_fd_cfg अणु
	u8 fd_mode;
	u16 max_key_length; /* use bit as unit */
	u32 rule_num[MAX_STAGE_NUM]; /* rule entry number */
	u16 cnt_num[MAX_STAGE_NUM]; /* rule hit counter number */
	काष्ठा hclge_fd_key_cfg key_cfg[MAX_STAGE_NUM];
	काष्ठा hclge_fd_user_def_cfg user_def_cfg[HCLGE_FD_USER_DEF_LAYER_NUM];
पूर्ण;

#घोषणा IPV4_INDEX	3
#घोषणा IPV6_SIZE	4
काष्ठा hclge_fd_rule_tuples अणु
	u8 src_mac[ETH_ALEN];
	u8 dst_mac[ETH_ALEN];
	/* Be compatible क्रम ip address of both ipv4 and ipv6.
	 * For ipv4 address, we store it in src/dst_ip[3].
	 */
	u32 src_ip[IPV6_SIZE];
	u32 dst_ip[IPV6_SIZE];
	u16 src_port;
	u16 dst_port;
	u16 vlan_tag1;
	u16 ether_proto;
	u16 l2_user_def;
	u16 l3_user_def;
	u32 l4_user_def;
	u8 ip_tos;
	u8 ip_proto;
पूर्ण;

काष्ठा hclge_fd_rule अणु
	काष्ठा hlist_node rule_node;
	काष्ठा hclge_fd_rule_tuples tuples;
	काष्ठा hclge_fd_rule_tuples tuples_mask;
	u32 unused_tuple;
	u32 flow_type;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ cookie;
			u8 tc;
		पूर्ण cls_flower;
		काष्ठा अणु
			u16 flow_id; /* only used क्रम arfs */
		पूर्ण arfs;
		काष्ठा अणु
			काष्ठा hclge_fd_user_def_info user_def;
		पूर्ण ep;
	पूर्ण;
	u16 queue_id;
	u16 vf_id;
	u16 location;
	क्रमागत HCLGE_FD_ACTIVE_RULE_TYPE rule_type;
	क्रमागत HCLGE_FD_NODE_STATE state;
	u8 action;
पूर्ण;

काष्ठा hclge_fd_ad_data अणु
	u16 ad_id;
	u8 drop_packet;
	u8 क्रमward_to_direct_queue;
	u16 queue_id;
	u8 use_counter;
	u8 counter_id;
	u8 use_next_stage;
	u8 ग_लिखो_rule_id_to_bd;
	u8 next_input_key;
	u16 rule_id;
	u16 tc_size;
	u8 override_tc;
पूर्ण;

क्रमागत HCLGE_MAC_NODE_STATE अणु
	HCLGE_MAC_TO_ADD,
	HCLGE_MAC_TO_DEL,
	HCLGE_MAC_ACTIVE
पूर्ण;

काष्ठा hclge_mac_node अणु
	काष्ठा list_head node;
	क्रमागत HCLGE_MAC_NODE_STATE state;
	u8 mac_addr[ETH_ALEN];
पूर्ण;

क्रमागत HCLGE_MAC_ADDR_TYPE अणु
	HCLGE_MAC_ADDR_UC,
	HCLGE_MAC_ADDR_MC
पूर्ण;

काष्ठा hclge_vport_vlan_cfg अणु
	काष्ठा list_head node;
	पूर्णांक hd_tbl_status;
	u16 vlan_id;
पूर्ण;

काष्ठा hclge_rst_stats अणु
	u32 reset_करोne_cnt;	/* the number of reset has completed */
	u32 hw_reset_करोne_cnt;	/* the number of HW reset has completed */
	u32 pf_rst_cnt;		/* the number of PF reset */
	u32 flr_rst_cnt;	/* the number of FLR */
	u32 global_rst_cnt;	/* the number of GLOBAL */
	u32 imp_rst_cnt;	/* the number of IMP reset */
	u32 reset_cnt;		/* the number of reset */
	u32 reset_fail_cnt;	/* the number of reset fail */
पूर्ण;

/* समय and रेजिस्टर status when mac tunnel पूर्णांकerruption occur */
काष्ठा hclge_mac_tnl_stats अणु
	u64 समय;
	u32 status;
पूर्ण;

#घोषणा HCLGE_RESET_INTERVAL	(10 * HZ)
#घोषणा HCLGE_WAIT_RESET_DONE	100

#आशय pack(1)
काष्ठा hclge_vf_vlan_cfg अणु
	u8 mbx_cmd;
	u8 subcode;
	u8 is_समाप्त;
	u16 vlan;
	u16 proto;
पूर्ण;

#आशय pack()

/* For each bit of TCAM entry, it uses a pair of 'x' and
 * 'y' to indicate which value to match, like below:
 * ----------------------------------
 * | bit x | bit y |  search value  |
 * ----------------------------------
 * |   0   |   0   |   always hit   |
 * ----------------------------------
 * |   1   |   0   |   match '0'    |
 * ----------------------------------
 * |   0   |   1   |   match '1'    |
 * ----------------------------------
 * |   1   |   1   |   invalid      |
 * ----------------------------------
 * Then क्रम input key(k) and mask(v), we can calculate the value by
 * the क्रमmulae:
 *	x = (~k) & v
 *	y = (k ^ ~v) & k
 */
#घोषणा calc_x(x, k, v) (x = ~(k) & (v))
#घोषणा calc_y(y, k, v) \
	करो अणु \
		स्थिर typeof(k) _k_ = (k); \
		स्थिर typeof(v) _v_ = (v); \
		(y) = (_k_ ^ ~_v_) & (_k_); \
	पूर्ण जबतक (0)

#घोषणा HCLGE_MAC_TNL_LOG_SIZE	8
#घोषणा HCLGE_VPORT_NUM 256
काष्ठा hclge_dev अणु
	काष्ठा pci_dev *pdev;
	काष्ठा hnae3_ae_dev *ae_dev;
	काष्ठा hclge_hw hw;
	काष्ठा hclge_misc_vector misc_vector;
	काष्ठा hclge_mac_stats mac_stats;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ flr_state;
	अचिन्हित दीर्घ last_reset_समय;

	क्रमागत hnae3_reset_type reset_type;
	क्रमागत hnae3_reset_type reset_level;
	अचिन्हित दीर्घ शेष_reset_request;
	अचिन्हित दीर्घ reset_request;	/* reset has been requested */
	अचिन्हित दीर्घ reset_pending;	/* client rst is pending to be served */
	काष्ठा hclge_rst_stats rst_stats;
	काष्ठा semaphore reset_sem;	/* protect reset process */
	u32 fw_version;
	u16 num_tqps;			/* Num task queue pairs of this PF */
	u16 num_req_vfs;		/* Num VFs requested क्रम this PF */

	u16 base_tqp_pid;	/* Base task tqp physical id of this PF */
	u16 alloc_rss_size;		/* Allocated RSS task queue */
	u16 vf_rss_size_max;		/* HW defined VF max RSS task queue */
	u16 pf_rss_size_max;		/* HW defined PF max RSS task queue */

	u16 fdir_pf_filter_count; /* Num of guaranteed filters क्रम this PF */
	u16 num_alloc_vport;		/* Num vports this driver supports */
	u32 numa_node_mask;
	u16 rx_buf_len;
	u16 num_tx_desc;		/* desc num of per tx queue */
	u16 num_rx_desc;		/* desc num of per rx queue */
	u8 hw_tc_map;
	क्रमागत hclge_fc_mode fc_mode_last_समय;
	u8 support_sfp_query;

#घोषणा HCLGE_FLAG_TC_BASE_SCH_MODE		1
#घोषणा HCLGE_FLAG_VNET_BASE_SCH_MODE		2
	u8 tx_sch_mode;
	u8 tc_max;
	u8 pfc_max;

	u8 शेष_up;
	u8 dcbx_cap;
	काष्ठा hclge_पंचांग_info पंचांग_info;

	u16 num_msi;
	u16 num_msi_left;
	u16 num_msi_used;
	u32 base_msi_vector;
	u16 *vector_status;
	पूर्णांक *vector_irq;
	u16 num_nic_msi;	/* Num of nic vectors क्रम this PF */
	u16 num_roce_msi;	/* Num of roce vectors क्रम this PF */
	पूर्णांक roce_base_vector;

	अचिन्हित दीर्घ service_समयr_period;
	अचिन्हित दीर्घ service_समयr_previous;
	काष्ठा समयr_list reset_समयr;
	काष्ठा delayed_work service_task;

	bool cur_promisc;
	पूर्णांक num_alloc_vfs;	/* Actual number of VFs allocated */

	काष्ठा hclge_tqp *htqp;
	काष्ठा hclge_vport *vport;

	काष्ठा dentry *hclge_dbgfs;

	काष्ठा hnae3_client *nic_client;
	काष्ठा hnae3_client *roce_client;

#घोषणा HCLGE_FLAG_MAIN			BIT(0)
#घोषणा HCLGE_FLAG_DCB_CAPABLE		BIT(1)
#घोषणा HCLGE_FLAG_DCB_ENABLE		BIT(2)
#घोषणा HCLGE_FLAG_MQPRIO_ENABLE	BIT(3)
	u32 flag;

	u32 pkt_buf_size; /* Total pf buf size क्रम tx/rx */
	u32 tx_buf_size; /* Tx buffer size क्रम each TC */
	u32 dv_buf_size; /* Dv buffer size क्रम each TC */

	u32 mps; /* Max packet size */
	/* vport_lock protect resource shared by vports */
	काष्ठा mutex vport_lock;

	काष्ठा hclge_vlan_type_cfg vlan_type_cfg;

	अचिन्हित दीर्घ vlan_table[VLAN_N_VID][BITS_TO_LONGS(HCLGE_VPORT_NUM)];
	अचिन्हित दीर्घ vf_vlan_full[BITS_TO_LONGS(HCLGE_VPORT_NUM)];

	अचिन्हित दीर्घ vport_config_block[BITS_TO_LONGS(HCLGE_VPORT_NUM)];

	काष्ठा hclge_fd_cfg fd_cfg;
	काष्ठा hlist_head fd_rule_list;
	spinlock_t fd_rule_lock; /* protect fd_rule_list and fd_bmap */
	u16 hclge_fd_rule_num;
	अचिन्हित दीर्घ serv_processed_cnt;
	अचिन्हित दीर्घ last_serv_processed;
	अचिन्हित दीर्घ fd_bmap[BITS_TO_LONGS(MAX_FD_FILTER_NUM)];
	क्रमागत HCLGE_FD_ACTIVE_RULE_TYPE fd_active_type;
	u8 fd_en;

	u16 wanted_umv_size;
	/* max available unicast mac vlan space */
	u16 max_umv_size;
	/* निजी unicast mac vlan space, it's same क्रम PF and its VFs */
	u16 priv_umv_size;
	/* unicast mac vlan space shared by PF and its VFs */
	u16 share_umv_size;

	DECLARE_KFIFO(mac_tnl_log, काष्ठा hclge_mac_tnl_stats,
		      HCLGE_MAC_TNL_LOG_SIZE);

	/* affinity mask and notअगरy क्रम misc पूर्णांकerrupt */
	cpumask_t affinity_mask;
	काष्ठा irq_affinity_notअगरy affinity_notअगरy;
पूर्ण;

/* VPort level vlan tag configuration क्रम TX direction */
काष्ठा hclge_tx_vtag_cfg अणु
	bool accept_tag1;	/* Whether accept tag1 packet from host */
	bool accept_untag1;	/* Whether accept untag1 packet from host */
	bool accept_tag2;
	bool accept_untag2;
	bool insert_tag1_en;	/* Whether insert inner vlan tag */
	bool insert_tag2_en;	/* Whether insert outer vlan tag */
	u16  शेष_tag1;	/* The शेष inner vlan tag to insert */
	u16  शेष_tag2;	/* The शेष outer vlan tag to insert */
	bool tag_shअगरt_mode_en;
पूर्ण;

/* VPort level vlan tag configuration क्रम RX direction */
काष्ठा hclge_rx_vtag_cfg अणु
	bool rx_vlan_offload_en; /* Whether enable rx vlan offload */
	bool strip_tag1_en;	 /* Whether strip inner vlan tag */
	bool strip_tag2_en;	 /* Whether strip outer vlan tag */
	bool vlan1_vlan_prionly; /* Inner vlan tag up to descriptor enable */
	bool vlan2_vlan_prionly; /* Outer vlan tag up to descriptor enable */
	bool strip_tag1_discard_en; /* Inner vlan tag discard क्रम BD enable */
	bool strip_tag2_discard_en; /* Outer vlan tag discard क्रम BD enable */
पूर्ण;

काष्ठा hclge_rss_tuple_cfg अणु
	u8 ipv4_tcp_en;
	u8 ipv4_udp_en;
	u8 ipv4_sctp_en;
	u8 ipv4_fragment_en;
	u8 ipv6_tcp_en;
	u8 ipv6_udp_en;
	u8 ipv6_sctp_en;
	u8 ipv6_fragment_en;
पूर्ण;

क्रमागत HCLGE_VPORT_STATE अणु
	HCLGE_VPORT_STATE_ALIVE,
	HCLGE_VPORT_STATE_MAC_TBL_CHANGE,
	HCLGE_VPORT_STATE_MAX
पूर्ण;

काष्ठा hclge_vlan_info अणु
	u16 vlan_proto; /* so far support 802.1Q only */
	u16 qos;
	u16 vlan_tag;
पूर्ण;

काष्ठा hclge_port_base_vlan_config अणु
	u16 state;
	काष्ठा hclge_vlan_info vlan_info;
पूर्ण;

काष्ठा hclge_vf_info अणु
	पूर्णांक link_state;
	u8 mac[ETH_ALEN];
	u32 spoofchk;
	u32 max_tx_rate;
	u32 trusted;
	u16 promisc_enable;
पूर्ण;

काष्ठा hclge_vport अणु
	u16 alloc_tqps;	/* Allocated Tx/Rx queues */

	u8  rss_hash_key[HCLGE_RSS_KEY_SIZE]; /* User configured hash keys */
	/* User configured lookup table entries */
	u16 *rss_indirection_tbl;
	पूर्णांक rss_algo;		/* User configured hash algorithm */
	/* User configured rss tuple sets */
	काष्ठा hclge_rss_tuple_cfg rss_tuple_sets;

	u16 alloc_rss_size;

	u16 qs_offset;
	u32 bw_limit;		/* VSI BW Limit (0 = disabled) */
	u8  dwrr;

	अचिन्हित दीर्घ vlan_del_fail_bmap[BITS_TO_LONGS(VLAN_N_VID)];
	काष्ठा hclge_port_base_vlan_config port_base_vlan_cfg;
	काष्ठा hclge_tx_vtag_cfg  txvlan_cfg;
	काष्ठा hclge_rx_vtag_cfg  rxvlan_cfg;

	u16 used_umv_num;

	u16 vport_id;
	काष्ठा hclge_dev *back;  /* Back reference to associated dev */
	काष्ठा hnae3_handle nic;
	काष्ठा hnae3_handle roce;

	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ last_active_jअगरfies;
	u32 mps; /* Max packet size */
	काष्ठा hclge_vf_info vf_info;

	u8 overflow_promisc_flags;
	u8 last_promisc_flags;

	spinlock_t mac_list_lock; /* protect mac address need to add/detele */
	काष्ठा list_head uc_mac_list;   /* Store VF unicast table */
	काष्ठा list_head mc_mac_list;   /* Store VF multicast table */
	काष्ठा list_head vlan_list;     /* Store VF vlan table */
पूर्ण;

पूर्णांक hclge_set_vport_promisc_mode(काष्ठा hclge_vport *vport, bool en_uc_pmc,
				 bool en_mc_pmc, bool en_bc_pmc);
पूर्णांक hclge_add_uc_addr_common(काष्ठा hclge_vport *vport,
			     स्थिर अचिन्हित अक्षर *addr);
पूर्णांक hclge_rm_uc_addr_common(काष्ठा hclge_vport *vport,
			    स्थिर अचिन्हित अक्षर *addr);
पूर्णांक hclge_add_mc_addr_common(काष्ठा hclge_vport *vport,
			     स्थिर अचिन्हित अक्षर *addr);
पूर्णांक hclge_rm_mc_addr_common(काष्ठा hclge_vport *vport,
			    स्थिर अचिन्हित अक्षर *addr);

काष्ठा hclge_vport *hclge_get_vport(काष्ठा hnae3_handle *handle);
पूर्णांक hclge_bind_ring_with_vector(काष्ठा hclge_vport *vport,
				पूर्णांक vector_id, bool en,
				काष्ठा hnae3_ring_chain_node *ring_chain);

अटल अंतरभूत पूर्णांक hclge_get_queue_id(काष्ठा hnae3_queue *queue)
अणु
	काष्ठा hclge_tqp *tqp = container_of(queue, काष्ठा hclge_tqp, q);

	वापस tqp->index;
पूर्ण

अटल अंतरभूत bool hclge_is_reset_pending(काष्ठा hclge_dev *hdev)
अणु
	वापस !!hdev->reset_pending;
पूर्ण

पूर्णांक hclge_inक्रमm_reset_निश्चित_to_vf(काष्ठा hclge_vport *vport);
पूर्णांक hclge_cfg_mac_speed_dup(काष्ठा hclge_dev *hdev, पूर्णांक speed, u8 duplex);
पूर्णांक hclge_set_vlan_filter(काष्ठा hnae3_handle *handle, __be16 proto,
			  u16 vlan_id, bool is_समाप्त);
पूर्णांक hclge_en_hw_strip_rxvtag(काष्ठा hnae3_handle *handle, bool enable);

पूर्णांक hclge_buffer_alloc(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_rss_init_hw(काष्ठा hclge_dev *hdev);
व्योम hclge_rss_indir_init_cfg(काष्ठा hclge_dev *hdev);

व्योम hclge_mbx_handler(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_reset_tqp(काष्ठा hnae3_handle *handle);
पूर्णांक hclge_cfg_flowctrl(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_func_reset_cmd(काष्ठा hclge_dev *hdev, पूर्णांक func_id);
पूर्णांक hclge_vport_start(काष्ठा hclge_vport *vport);
व्योम hclge_vport_stop(काष्ठा hclge_vport *vport);
पूर्णांक hclge_set_vport_mtu(काष्ठा hclge_vport *vport, पूर्णांक new_mtu);
पूर्णांक hclge_dbg_run_cmd(काष्ठा hnae3_handle *handle, स्थिर अक्षर *cmd_buf);
पूर्णांक hclge_dbg_पढ़ो_cmd(काष्ठा hnae3_handle *handle, स्थिर अक्षर *cmd_buf,
		       अक्षर *buf, पूर्णांक len);
u16 hclge_covert_handle_qid_global(काष्ठा hnae3_handle *handle, u16 queue_id);
पूर्णांक hclge_notअगरy_client(काष्ठा hclge_dev *hdev,
			क्रमागत hnae3_reset_notअगरy_type type);
पूर्णांक hclge_update_mac_list(काष्ठा hclge_vport *vport,
			  क्रमागत HCLGE_MAC_NODE_STATE state,
			  क्रमागत HCLGE_MAC_ADDR_TYPE mac_type,
			  स्थिर अचिन्हित अक्षर *addr);
पूर्णांक hclge_update_mac_node_क्रम_dev_addr(काष्ठा hclge_vport *vport,
				       स्थिर u8 *old_addr, स्थिर u8 *new_addr);
व्योम hclge_rm_vport_all_mac_table(काष्ठा hclge_vport *vport, bool is_del_list,
				  क्रमागत HCLGE_MAC_ADDR_TYPE mac_type);
व्योम hclge_rm_vport_all_vlan_table(काष्ठा hclge_vport *vport, bool is_del_list);
व्योम hclge_uninit_vport_vlan_table(काष्ठा hclge_dev *hdev);
व्योम hclge_restore_mac_table_common(काष्ठा hclge_vport *vport);
व्योम hclge_restore_vport_vlan_table(काष्ठा hclge_vport *vport);
पूर्णांक hclge_update_port_base_vlan_cfg(काष्ठा hclge_vport *vport, u16 state,
				    काष्ठा hclge_vlan_info *vlan_info);
पूर्णांक hclge_push_vf_port_base_vlan_info(काष्ठा hclge_vport *vport, u8 vfid,
				      u16 state, u16 vlan_tag, u16 qos,
				      u16 vlan_proto);
व्योम hclge_task_schedule(काष्ठा hclge_dev *hdev, अचिन्हित दीर्घ delay_समय);
पूर्णांक hclge_query_bd_num_cmd_send(काष्ठा hclge_dev *hdev,
				काष्ठा hclge_desc *desc);
व्योम hclge_report_hw_error(काष्ठा hclge_dev *hdev,
			   क्रमागत hnae3_hw_error_type type);
व्योम hclge_inक्रमm_vf_promisc_info(काष्ठा hclge_vport *vport);
व्योम hclge_dbg_dump_rst_info(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_push_vf_link_status(काष्ठा hclge_vport *vport);
#पूर्ण_अगर
