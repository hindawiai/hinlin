<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
// Copyright (c) 2016-2017 Hisilicon Limited.

#अगर_अघोषित __HNS3_ENET_H
#घोषणा __HNS3_ENET_H

#समावेश <linux/अगर_vlan.h>

#समावेश "hnae3.h"

क्रमागत hns3_nic_state अणु
	HNS3_NIC_STATE_TESTING,
	HNS3_NIC_STATE_RESETTING,
	HNS3_NIC_STATE_INITED,
	HNS3_NIC_STATE_DOWN,
	HNS3_NIC_STATE_DISABLED,
	HNS3_NIC_STATE_REMOVING,
	HNS3_NIC_STATE_SERVICE_INITED,
	HNS3_NIC_STATE_SERVICE_SCHED,
	HNS3_NIC_STATE2_RESET_REQUESTED,
	HNS3_NIC_STATE_HW_TX_CSUM_ENABLE,
	HNS3_NIC_STATE_MAX
पूर्ण;

#घोषणा HNS3_RING_RX_RING_BASEADDR_L_REG	0x00000
#घोषणा HNS3_RING_RX_RING_BASEADDR_H_REG	0x00004
#घोषणा HNS3_RING_RX_RING_BD_NUM_REG		0x00008
#घोषणा HNS3_RING_RX_RING_BD_LEN_REG		0x0000C
#घोषणा HNS3_RING_RX_RING_TAIL_REG		0x00018
#घोषणा HNS3_RING_RX_RING_HEAD_REG		0x0001C
#घोषणा HNS3_RING_RX_RING_FBDNUM_REG		0x00020
#घोषणा HNS3_RING_RX_RING_PKTNUM_RECORD_REG	0x0002C

#घोषणा HNS3_RING_TX_RING_BASEADDR_L_REG	0x00040
#घोषणा HNS3_RING_TX_RING_BASEADDR_H_REG	0x00044
#घोषणा HNS3_RING_TX_RING_BD_NUM_REG		0x00048
#घोषणा HNS3_RING_TX_RING_TC_REG		0x00050
#घोषणा HNS3_RING_TX_RING_TAIL_REG		0x00058
#घोषणा HNS3_RING_TX_RING_HEAD_REG		0x0005C
#घोषणा HNS3_RING_TX_RING_FBDNUM_REG		0x00060
#घोषणा HNS3_RING_TX_RING_OFFSET_REG		0x00064
#घोषणा HNS3_RING_TX_RING_EBDNUM_REG		0x00068
#घोषणा HNS3_RING_TX_RING_PKTNUM_RECORD_REG	0x0006C
#घोषणा HNS3_RING_TX_RING_EBD_OFFSET_REG	0x00070
#घोषणा HNS3_RING_TX_RING_BD_ERR_REG		0x00074
#घोषणा HNS3_RING_EN_REG			0x00090
#घोषणा HNS3_RING_RX_EN_REG			0x00098
#घोषणा HNS3_RING_TX_EN_REG			0x000D4

#घोषणा HNS3_RX_HEAD_SIZE			256

#घोषणा HNS3_TX_TIMEOUT (5 * HZ)
#घोषणा HNS3_RING_NAME_LEN			16
#घोषणा HNS3_BUFFER_SIZE_2048			2048
#घोषणा HNS3_RING_MAX_PENDING			32760
#घोषणा HNS3_RING_MIN_PENDING			72
#घोषणा HNS3_RING_BD_MULTIPLE			8
/* max frame size of mac */
#घोषणा HNS3_MAX_MTU(max_frm_size) \
	((max_frm_size) - (ETH_HLEN + ETH_FCS_LEN + 2 * VLAN_HLEN))

#घोषणा HNS3_BD_SIZE_512_TYPE			0
#घोषणा HNS3_BD_SIZE_1024_TYPE			1
#घोषणा HNS3_BD_SIZE_2048_TYPE			2
#घोषणा HNS3_BD_SIZE_4096_TYPE			3

#घोषणा HNS3_RX_FLAG_VLAN_PRESENT		0x1
#घोषणा HNS3_RX_FLAG_L3ID_IPV4			0x0
#घोषणा HNS3_RX_FLAG_L3ID_IPV6			0x1
#घोषणा HNS3_RX_FLAG_L4ID_UDP			0x0
#घोषणा HNS3_RX_FLAG_L4ID_TCP			0x1

#घोषणा HNS3_RXD_DMAC_S				0
#घोषणा HNS3_RXD_DMAC_M				(0x3 << HNS3_RXD_DMAC_S)
#घोषणा HNS3_RXD_VLAN_S				2
#घोषणा HNS3_RXD_VLAN_M				(0x3 << HNS3_RXD_VLAN_S)
#घोषणा HNS3_RXD_L3ID_S				4
#घोषणा HNS3_RXD_L3ID_M				(0xf << HNS3_RXD_L3ID_S)
#घोषणा HNS3_RXD_L4ID_S				8
#घोषणा HNS3_RXD_L4ID_M				(0xf << HNS3_RXD_L4ID_S)
#घोषणा HNS3_RXD_FRAG_B				12
#घोषणा HNS3_RXD_STRP_TAGP_S			13
#घोषणा HNS3_RXD_STRP_TAGP_M			(0x3 << HNS3_RXD_STRP_TAGP_S)

#घोषणा HNS3_RXD_L2_CSUM_B			15
#घोषणा HNS3_RXD_L2_CSUM_L_S			4
#घोषणा HNS3_RXD_L2_CSUM_L_M			(0xff << HNS3_RXD_L2_CSUM_L_S)
#घोषणा HNS3_RXD_L2_CSUM_H_S			24
#घोषणा HNS3_RXD_L2_CSUM_H_M			(0xff << HNS3_RXD_L2_CSUM_H_S)

#घोषणा HNS3_RXD_L2E_B				16
#घोषणा HNS3_RXD_L3E_B				17
#घोषणा HNS3_RXD_L4E_B				18
#घोषणा HNS3_RXD_TRUNCAT_B			19
#घोषणा HNS3_RXD_HOI_B				20
#घोषणा HNS3_RXD_DOI_B				21
#घोषणा HNS3_RXD_OL3E_B				22
#घोषणा HNS3_RXD_OL4E_B				23
#घोषणा HNS3_RXD_GRO_COUNT_S			24
#घोषणा HNS3_RXD_GRO_COUNT_M			(0x3f << HNS3_RXD_GRO_COUNT_S)
#घोषणा HNS3_RXD_GRO_FIXID_B			30
#घोषणा HNS3_RXD_GRO_ECN_B			31

#घोषणा HNS3_RXD_ODMAC_S			0
#घोषणा HNS3_RXD_ODMAC_M			(0x3 << HNS3_RXD_ODMAC_S)
#घोषणा HNS3_RXD_OVLAN_S			2
#घोषणा HNS3_RXD_OVLAN_M			(0x3 << HNS3_RXD_OVLAN_S)
#घोषणा HNS3_RXD_OL3ID_S			4
#घोषणा HNS3_RXD_OL3ID_M			(0xf << HNS3_RXD_OL3ID_S)
#घोषणा HNS3_RXD_OL4ID_S			8
#घोषणा HNS3_RXD_OL4ID_M			(0xf << HNS3_RXD_OL4ID_S)
#घोषणा HNS3_RXD_FBHI_S				12
#घोषणा HNS3_RXD_FBHI_M				(0x3 << HNS3_RXD_FBHI_S)
#घोषणा HNS3_RXD_FBLI_S				14
#घोषणा HNS3_RXD_FBLI_M				(0x3 << HNS3_RXD_FBLI_S)

#घोषणा HNS3_RXD_BDTYPE_S			0
#घोषणा HNS3_RXD_BDTYPE_M			(0xf << HNS3_RXD_BDTYPE_S)
#घोषणा HNS3_RXD_VLD_B				4
#घोषणा HNS3_RXD_UDP0_B				5
#घोषणा HNS3_RXD_EXTEND_B			7
#घोषणा HNS3_RXD_FE_B				8
#घोषणा HNS3_RXD_LUM_B				9
#घोषणा HNS3_RXD_CRCP_B				10
#घोषणा HNS3_RXD_L3L4P_B			11
#घोषणा HNS3_RXD_TSIND_S			12
#घोषणा HNS3_RXD_TSIND_M			(0x7 << HNS3_RXD_TSIND_S)
#घोषणा HNS3_RXD_LKBK_B				15
#घोषणा HNS3_RXD_GRO_SIZE_S			16
#घोषणा HNS3_RXD_GRO_SIZE_M			(0x3fff << HNS3_RXD_GRO_SIZE_S)

#घोषणा HNS3_TXD_L3T_S				0
#घोषणा HNS3_TXD_L3T_M				(0x3 << HNS3_TXD_L3T_S)
#घोषणा HNS3_TXD_L4T_S				2
#घोषणा HNS3_TXD_L4T_M				(0x3 << HNS3_TXD_L4T_S)
#घोषणा HNS3_TXD_L3CS_B				4
#घोषणा HNS3_TXD_L4CS_B				5
#घोषणा HNS3_TXD_VLAN_B				6
#घोषणा HNS3_TXD_TSO_B				7

#घोषणा HNS3_TXD_L2LEN_S			8
#घोषणा HNS3_TXD_L2LEN_M			(0xff << HNS3_TXD_L2LEN_S)
#घोषणा HNS3_TXD_L3LEN_S			16
#घोषणा HNS3_TXD_L3LEN_M			(0xff << HNS3_TXD_L3LEN_S)
#घोषणा HNS3_TXD_L4LEN_S			24
#घोषणा HNS3_TXD_L4LEN_M			(0xff << HNS3_TXD_L4LEN_S)

#घोषणा HNS3_TXD_CSUM_START_S		8
#घोषणा HNS3_TXD_CSUM_START_M		(0xffff << HNS3_TXD_CSUM_START_S)

#घोषणा HNS3_TXD_OL3T_S				0
#घोषणा HNS3_TXD_OL3T_M				(0x3 << HNS3_TXD_OL3T_S)
#घोषणा HNS3_TXD_OVLAN_B			2
#घोषणा HNS3_TXD_MACSEC_B			3
#घोषणा HNS3_TXD_TUNTYPE_S			4
#घोषणा HNS3_TXD_TUNTYPE_M			(0xf << HNS3_TXD_TUNTYPE_S)

#घोषणा HNS3_TXD_CSUM_OFFSET_S		8
#घोषणा HNS3_TXD_CSUM_OFFSET_M		(0xffff << HNS3_TXD_CSUM_OFFSET_S)

#घोषणा HNS3_TXD_BDTYPE_S			0
#घोषणा HNS3_TXD_BDTYPE_M			(0xf << HNS3_TXD_BDTYPE_S)
#घोषणा HNS3_TXD_FE_B				4
#घोषणा HNS3_TXD_SC_S				5
#घोषणा HNS3_TXD_SC_M				(0x3 << HNS3_TXD_SC_S)
#घोषणा HNS3_TXD_EXTEND_B			7
#घोषणा HNS3_TXD_VLD_B				8
#घोषणा HNS3_TXD_RI_B				9
#घोषणा HNS3_TXD_RA_B				10
#घोषणा HNS3_TXD_TSYN_B				11
#घोषणा HNS3_TXD_DECTTL_S			12
#घोषणा HNS3_TXD_DECTTL_M			(0xf << HNS3_TXD_DECTTL_S)

#घोषणा HNS3_TXD_OL4CS_B			22

#घोषणा HNS3_TXD_MSS_S				0
#घोषणा HNS3_TXD_MSS_M				(0x3fff << HNS3_TXD_MSS_S)
#घोषणा HNS3_TXD_HW_CS_B			14

#घोषणा HNS3_VECTOR_TX_IRQ			BIT_ULL(0)
#घोषणा HNS3_VECTOR_RX_IRQ			BIT_ULL(1)

#घोषणा HNS3_VECTOR_NOT_INITED			0
#घोषणा HNS3_VECTOR_INITED			1

#घोषणा HNS3_MAX_BD_SIZE			65535
#घोषणा HNS3_MAX_TSO_BD_NUM			63U
#घोषणा HNS3_MAX_TSO_SIZE \
	(HNS3_MAX_BD_SIZE * HNS3_MAX_TSO_BD_NUM)

#घोषणा HNS3_MAX_NON_TSO_SIZE(max_non_tso_bd_num) \
	(HNS3_MAX_BD_SIZE * (max_non_tso_bd_num))

#घोषणा HNS3_VECTOR_GL0_OFFSET			0x100
#घोषणा HNS3_VECTOR_GL1_OFFSET			0x200
#घोषणा HNS3_VECTOR_GL2_OFFSET			0x300
#घोषणा HNS3_VECTOR_RL_OFFSET			0x900
#घोषणा HNS3_VECTOR_RL_EN_B			6
#घोषणा HNS3_VECTOR_TX_QL_OFFSET		0xe00
#घोषणा HNS3_VECTOR_RX_QL_OFFSET		0xf00

#घोषणा HNS3_RING_EN_B				0

क्रमागत hns3_pkt_l2t_type अणु
	HNS3_L2_TYPE_UNICAST,
	HNS3_L2_TYPE_MULTICAST,
	HNS3_L2_TYPE_BROADCAST,
	HNS3_L2_TYPE_INVALID,
पूर्ण;

क्रमागत hns3_pkt_l3t_type अणु
	HNS3_L3T_NONE,
	HNS3_L3T_IPV6,
	HNS3_L3T_IPV4,
	HNS3_L3T_RESERVED
पूर्ण;

क्रमागत hns3_pkt_l4t_type अणु
	HNS3_L4T_UNKNOWN,
	HNS3_L4T_TCP,
	HNS3_L4T_UDP,
	HNS3_L4T_SCTP
पूर्ण;

क्रमागत hns3_pkt_ol3t_type अणु
	HNS3_OL3T_NONE,
	HNS3_OL3T_IPV6,
	HNS3_OL3T_IPV4_NO_CSUM,
	HNS3_OL3T_IPV4_CSUM
पूर्ण;

क्रमागत hns3_pkt_tun_type अणु
	HNS3_TUN_NONE,
	HNS3_TUN_MAC_IN_UDP,
	HNS3_TUN_NVGRE,
	HNS3_TUN_OTHER
पूर्ण;

/* hardware spec ring buffer क्रमmat */
काष्ठा __packed hns3_desc अणु
	__le64 addr;
	जोड़ अणु
		काष्ठा अणु
			__le16 vlan_tag;
			__le16 send_size;
			जोड़ अणु
				__le32 type_cs_vlan_tso_len;
				काष्ठा अणु
					__u8 type_cs_vlan_tso;
					__u8 l2_len;
					__u8 l3_len;
					__u8 l4_len;
				पूर्ण;
			पूर्ण;
			__le16 outer_vlan_tag;
			__le16 tv;

		जोड़ अणु
			__le32 ol_type_vlan_len_msec;
			काष्ठा अणु
				__u8 ol_type_vlan_msec;
				__u8 ol2_len;
				__u8 ol3_len;
				__u8 ol4_len;
			पूर्ण;
		पूर्ण;

			__le32 paylen_ol4cs;
			__le16 bdtp_fe_sc_vld_ra_ri;
			__le16 mss_hw_csum;
		पूर्ण tx;

		काष्ठा अणु
			__le32 l234_info;
			__le16 pkt_len;
			__le16 size;

			__le32 rss_hash;
			__le16 fd_id;
			__le16 vlan_tag;

			जोड़ अणु
				__le32 ol_info;
				काष्ठा अणु
					__le16 o_dm_vlan_id_fb;
					__le16 ot_vlan_tag;
				पूर्ण;
			पूर्ण;

			__le32 bd_base_info;
		पूर्ण rx;
	पूर्ण;
पूर्ण;

काष्ठा hns3_desc_cb अणु
	dma_addr_t dma; /* dma address of this desc */
	व्योम *buf;      /* cpu addr क्रम a desc */

	/* priv data क्रम the desc, e.g. skb when use with ip stack */
	व्योम *priv;

	जोड़ अणु
		u32 page_offset;	/* क्रम rx */
		u32 send_bytes;		/* क्रम tx */
	पूर्ण;

	u32 length;     /* length of the buffer */

	u16 reuse_flag;

	/* desc type, used by the ring user to mark the type of the priv data */
	u16 type;
	u16 pagecnt_bias;
पूर्ण;

क्रमागत hns3_pkt_l3type अणु
	HNS3_L3_TYPE_IPV4,
	HNS3_L3_TYPE_IPV6,
	HNS3_L3_TYPE_ARP,
	HNS3_L3_TYPE_RARP,
	HNS3_L3_TYPE_IPV4_OPT,
	HNS3_L3_TYPE_IPV6_EXT,
	HNS3_L3_TYPE_LLDP,
	HNS3_L3_TYPE_BPDU,
	HNS3_L3_TYPE_MAC_PAUSE,
	HNS3_L3_TYPE_PFC_PAUSE,/* 0x9*/

	/* reserved क्रम 0xA~0xB */

	HNS3_L3_TYPE_CNM = 0xc,

	/* reserved क्रम 0xD~0xE */

	HNS3_L3_TYPE_PARSE_FAIL	= 0xf /* must be last */
पूर्ण;

क्रमागत hns3_pkt_l4type अणु
	HNS3_L4_TYPE_UDP,
	HNS3_L4_TYPE_TCP,
	HNS3_L4_TYPE_GRE,
	HNS3_L4_TYPE_SCTP,
	HNS3_L4_TYPE_IGMP,
	HNS3_L4_TYPE_ICMP,

	/* reserved क्रम 0x6~0xE */

	HNS3_L4_TYPE_PARSE_FAIL	= 0xf /* must be last */
पूर्ण;

क्रमागत hns3_pkt_ol3type अणु
	HNS3_OL3_TYPE_IPV4 = 0,
	HNS3_OL3_TYPE_IPV6,
	/* reserved क्रम 0x2~0x3 */
	HNS3_OL3_TYPE_IPV4_OPT = 4,
	HNS3_OL3_TYPE_IPV6_EXT,

	/* reserved क्रम 0x6~0xE */

	HNS3_OL3_TYPE_PARSE_FAIL = 0xf	/* must be last */
पूर्ण;

क्रमागत hns3_pkt_ol4type अणु
	HNS3_OL4_TYPE_NO_TUN,
	HNS3_OL4_TYPE_MAC_IN_UDP,
	HNS3_OL4_TYPE_NVGRE,
	HNS3_OL4_TYPE_UNKNOWN
पूर्ण;

काष्ठा ring_stats अणु
	u64 sw_err_cnt;
	u64 seg_pkt_cnt;
	जोड़ अणु
		काष्ठा अणु
			u64 tx_pkts;
			u64 tx_bytes;
			u64 tx_more;
			u64 restart_queue;
			u64 tx_busy;
			u64 tx_copy;
			u64 tx_vlan_err;
			u64 tx_l4_proto_err;
			u64 tx_l2l3l4_err;
			u64 tx_tso_err;
			u64 over_max_recursion;
			u64 hw_limitation;
		पूर्ण;
		काष्ठा अणु
			u64 rx_pkts;
			u64 rx_bytes;
			u64 rx_err_cnt;
			u64 reuse_pg_cnt;
			u64 err_pkt_len;
			u64 err_bd_num;
			u64 l2_err;
			u64 l3l4_csum_err;
			u64 csum_complete;
			u64 rx_multicast;
			u64 non_reuse_pg;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा hns3_enet_ring अणु
	काष्ठा hns3_desc *desc; /* dma map address space */
	काष्ठा hns3_desc_cb *desc_cb;
	काष्ठा hns3_enet_ring *next;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	काष्ठा hnae3_queue *tqp;
	पूर्णांक queue_index;
	काष्ठा device *dev; /* will be used क्रम DMA mapping of descriptors */

	/* statistic */
	काष्ठा ring_stats stats;
	काष्ठा u64_stats_sync syncp;

	dma_addr_t desc_dma_addr;
	u32 buf_size;       /* size क्रम hnae_desc->addr, preset by AE */
	u16 desc_num;       /* total number of desc */
	पूर्णांक next_to_use;    /* idx of next spare desc */

	/* idx of lastest sent desc, the ring is empty when equal to
	 * next_to_use
	 */
	पूर्णांक next_to_clean;
	जोड़ अणु
		पूर्णांक last_to_use;	/* last idx used by xmit */
		u32 pull_len;		/* स_नकल len क्रम current rx packet */
	पूर्ण;
	u32 frag_num;
	व्योम *va; /* first buffer address क्रम current packet */

	u32 flag;          /* ring attribute */

	पूर्णांक pending_buf;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *tail_skb;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

क्रमागत hns3_flow_level_range अणु
	HNS3_FLOW_LOW = 0,
	HNS3_FLOW_MID = 1,
	HNS3_FLOW_HIGH = 2,
	HNS3_FLOW_ULTRA = 3,
पूर्ण;

#घोषणा HNS3_INT_GL_50K			0x0014
#घोषणा HNS3_INT_GL_20K			0x0032
#घोषणा HNS3_INT_GL_18K			0x0036
#घोषणा HNS3_INT_GL_8K			0x007C

#घोषणा HNS3_INT_GL_1US			BIT(31)

#घोषणा HNS3_INT_RL_MAX			0x00EC
#घोषणा HNS3_INT_RL_ENABLE_MASK		0x40

#घोषणा HNS3_INT_QL_DEFAULT_CFG		0x20

काष्ठा hns3_enet_coalesce अणु
	u16 पूर्णांक_gl;
	u16 पूर्णांक_ql;
	u16 पूर्णांक_ql_max;
	u8 adapt_enable:1;
	u8 ql_enable:1;
	u8 unit_1us:1;
	क्रमागत hns3_flow_level_range flow_level;
पूर्ण;

काष्ठा hns3_enet_ring_group अणु
	/* array of poपूर्णांकers to rings */
	काष्ठा hns3_enet_ring *ring;
	u64 total_bytes;	/* total bytes processed this group */
	u64 total_packets;	/* total packets processed this group */
	u16 count;
	काष्ठा hns3_enet_coalesce coal;
पूर्ण;

काष्ठा hns3_enet_tqp_vector अणु
	काष्ठा hnae3_handle *handle;
	u8 __iomem *mask_addr;
	पूर्णांक vector_irq;
	पूर्णांक irq_init_flag;

	u16 idx;		/* index in the TQP vector array per handle. */

	काष्ठा napi_काष्ठा napi;

	काष्ठा hns3_enet_ring_group rx_group;
	काष्ठा hns3_enet_ring_group tx_group;

	cpumask_t affinity_mask;
	u16 num_tqps;	/* total number of tqps in TQP vector */
	काष्ठा irq_affinity_notअगरy affinity_notअगरy;

	अक्षर name[HNAE3_INT_NAME_LEN];

	अचिन्हित दीर्घ last_jअगरfies;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

काष्ठा hns3_nic_priv अणु
	काष्ठा hnae3_handle *ae_handle;
	काष्ठा net_device *netdev;
	काष्ठा device *dev;

	/**
	 * the cb क्रम nic to manage the ring buffer, the first half of the
	 * array is क्रम tx_ring and vice versa क्रम the second half
	 */
	काष्ठा hns3_enet_ring *ring;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	u16 vector_num;
	u8 max_non_tso_bd_num;

	u64 tx_समयout_count;

	अचिन्हित दीर्घ state;

	काष्ठा hns3_enet_coalesce tx_coal;
	काष्ठा hns3_enet_coalesce rx_coal;
पूर्ण;

जोड़ l3_hdr_info अणु
	काष्ठा iphdr *v4;
	काष्ठा ipv6hdr *v6;
	अचिन्हित अक्षर *hdr;
पूर्ण;

जोड़ l4_hdr_info अणु
	काष्ठा tcphdr *tcp;
	काष्ठा udphdr *udp;
	काष्ठा gre_base_hdr *gre;
	अचिन्हित अक्षर *hdr;
पूर्ण;

काष्ठा hns3_hw_error_info अणु
	क्रमागत hnae3_hw_error_type type;
	स्थिर अक्षर *msg;
पूर्ण;

अटल अंतरभूत पूर्णांक ring_space(काष्ठा hns3_enet_ring *ring)
अणु
	/* This smp_load_acquire() pairs with smp_store_release() in
	 * hns3_nic_reclaim_one_desc called by hns3_clean_tx_ring.
	 */
	पूर्णांक begin = smp_load_acquire(&ring->next_to_clean);
	पूर्णांक end = READ_ONCE(ring->next_to_use);

	वापस ((end >= begin) ? (ring->desc_num - end + begin) :
			(begin - end)) - 1;
पूर्ण

अटल अंतरभूत u32 hns3_पढ़ो_reg(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl(base + reg);
पूर्ण

अटल अंतरभूत व्योम hns3_ग_लिखो_reg(व्योम __iomem *base, u32 reg, u32 value)
अणु
	u8 __iomem *reg_addr = READ_ONCE(base);

	ग_लिखोl(value, reg_addr + reg);
पूर्ण

#घोषणा hns3_पढ़ो_dev(a, reg) \
	hns3_पढ़ो_reg((a)->io_base, reg)

अटल अंतरभूत bool hns3_nic_resetting(काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);

	वापस test_bit(HNS3_NIC_STATE_RESETTING, &priv->state);
पूर्ण

#घोषणा hns3_ग_लिखो_dev(a, reg, value) \
	hns3_ग_लिखो_reg((a)->io_base, reg, value)

#घोषणा ring_to_dev(ring) ((ring)->dev)

#घोषणा ring_to_netdev(ring)	((ring)->tqp_vector->napi.dev)

#घोषणा ring_to_dma_dir(ring) (HNAE3_IS_TX_RING(ring) ? \
	DMA_TO_DEVICE : DMA_FROM_DEVICE)

#घोषणा hns3_buf_size(_ring) ((_ring)->buf_size)

अटल अंतरभूत अचिन्हित पूर्णांक hns3_page_order(काष्ठा hns3_enet_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring->buf_size > (PAGE_SIZE / 2))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा hns3_page_size(_ring) (PAGE_SIZE << hns3_page_order(_ring))

/* iterator क्रम handling rings in ring group */
#घोषणा hns3_क्रम_each_ring(pos, head) \
	क्रम (pos = (head).ring; (pos); pos = (pos)->next)

#घोषणा hns3_get_handle(ndev) \
	(((काष्ठा hns3_nic_priv *)netdev_priv(ndev))->ae_handle)

#घोषणा hns3_gl_usec_to_reg(पूर्णांक_gl) ((पूर्णांक_gl) >> 1)
#घोषणा hns3_gl_round_करोwn(पूर्णांक_gl) round_करोwn(पूर्णांक_gl, 2)

#घोषणा hns3_rl_usec_to_reg(पूर्णांक_rl) ((पूर्णांक_rl) >> 2)
#घोषणा hns3_rl_round_करोwn(पूर्णांक_rl) round_करोwn(पूर्णांक_rl, 4)

व्योम hns3_ethtool_set_ops(काष्ठा net_device *netdev);
पूर्णांक hns3_set_channels(काष्ठा net_device *netdev,
		      काष्ठा ethtool_channels *ch);

व्योम hns3_clean_tx_ring(काष्ठा hns3_enet_ring *ring, पूर्णांक budget);
पूर्णांक hns3_init_all_ring(काष्ठा hns3_nic_priv *priv);
पूर्णांक hns3_nic_reset_all_ring(काष्ठा hnae3_handle *h);
व्योम hns3_fini_ring(काष्ठा hns3_enet_ring *ring);
netdev_tx_t hns3_nic_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);
bool hns3_is_phys_func(काष्ठा pci_dev *pdev);
पूर्णांक hns3_clean_rx_ring(
		काष्ठा hns3_enet_ring *ring, पूर्णांक budget,
		व्योम (*rx_fn)(काष्ठा hns3_enet_ring *, काष्ठा sk_buff *));

व्योम hns3_set_vector_coalesce_rx_gl(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 gl_value);
व्योम hns3_set_vector_coalesce_tx_gl(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 gl_value);
व्योम hns3_set_vector_coalesce_rl(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				 u32 rl_value);
व्योम hns3_set_vector_coalesce_rx_ql(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 ql_value);
व्योम hns3_set_vector_coalesce_tx_ql(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 ql_value);

व्योम hns3_enable_vlan_filter(काष्ठा net_device *netdev, bool enable);
व्योम hns3_request_update_promisc_mode(काष्ठा hnae3_handle *handle);

#अगर_घोषित CONFIG_HNS3_DCB
व्योम hns3_dcbnl_setup(काष्ठा hnae3_handle *handle);
#अन्यथा
अटल अंतरभूत व्योम hns3_dcbnl_setup(काष्ठा hnae3_handle *handle) अणुपूर्ण
#पूर्ण_अगर

व्योम hns3_dbg_init(काष्ठा hnae3_handle *handle);
व्योम hns3_dbg_uninit(काष्ठा hnae3_handle *handle);
व्योम hns3_dbg_रेजिस्टर_debugfs(स्थिर अक्षर *debugfs_dir_name);
व्योम hns3_dbg_unरेजिस्टर_debugfs(व्योम);
व्योम hns3_shinfo_pack(काष्ठा skb_shared_info *shinfo, __u32 *size);
#पूर्ण_अगर
