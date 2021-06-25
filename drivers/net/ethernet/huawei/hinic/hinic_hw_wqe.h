<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_WQE_H
#घोषणा HINIC_HW_WQE_H

#समावेश "hinic_common.h"

#घोषणा HINIC_CMDQ_CTRL_PI_SHIFT                        0
#घोषणा HINIC_CMDQ_CTRL_CMD_SHIFT                       16
#घोषणा HINIC_CMDQ_CTRL_MOD_SHIFT                       24
#घोषणा HINIC_CMDQ_CTRL_ACK_TYPE_SHIFT                  29
#घोषणा HINIC_CMDQ_CTRL_HW_BUSY_BIT_SHIFT               31

#घोषणा HINIC_CMDQ_CTRL_PI_MASK                         0xFFFF
#घोषणा HINIC_CMDQ_CTRL_CMD_MASK                        0xFF
#घोषणा HINIC_CMDQ_CTRL_MOD_MASK                        0x1F
#घोषणा HINIC_CMDQ_CTRL_ACK_TYPE_MASK                   0x3
#घोषणा HINIC_CMDQ_CTRL_HW_BUSY_BIT_MASK                0x1

#घोषणा HINIC_CMDQ_CTRL_SET(val, member)                        \
			(((u32)(val) & HINIC_CMDQ_CTRL_##member##_MASK) \
			 << HINIC_CMDQ_CTRL_##member##_SHIFT)

#घोषणा HINIC_CMDQ_CTRL_GET(val, member)                        \
			(((val) >> HINIC_CMDQ_CTRL_##member##_SHIFT) \
			 & HINIC_CMDQ_CTRL_##member##_MASK)

#घोषणा HINIC_CMDQ_WQE_HEADER_BUFDESC_LEN_SHIFT         0
#घोषणा HINIC_CMDQ_WQE_HEADER_COMPLETE_FMT_SHIFT        15
#घोषणा HINIC_CMDQ_WQE_HEADER_DATA_FMT_SHIFT            22
#घोषणा HINIC_CMDQ_WQE_HEADER_COMPLETE_REQ_SHIFT        23
#घोषणा HINIC_CMDQ_WQE_HEADER_COMPLETE_SECT_LEN_SHIFT   27
#घोषणा HINIC_CMDQ_WQE_HEADER_CTRL_LEN_SHIFT            29
#घोषणा HINIC_CMDQ_WQE_HEADER_TOGGLED_WRAPPED_SHIFT     31

#घोषणा HINIC_CMDQ_WQE_HEADER_BUFDESC_LEN_MASK          0xFF
#घोषणा HINIC_CMDQ_WQE_HEADER_COMPLETE_FMT_MASK         0x1
#घोषणा HINIC_CMDQ_WQE_HEADER_DATA_FMT_MASK             0x1
#घोषणा HINIC_CMDQ_WQE_HEADER_COMPLETE_REQ_MASK         0x1
#घोषणा HINIC_CMDQ_WQE_HEADER_COMPLETE_SECT_LEN_MASK    0x3
#घोषणा HINIC_CMDQ_WQE_HEADER_CTRL_LEN_MASK             0x3
#घोषणा HINIC_CMDQ_WQE_HEADER_TOGGLED_WRAPPED_MASK      0x1

#घोषणा HINIC_CMDQ_WQE_HEADER_SET(val, member)                  \
			(((u32)(val) & HINIC_CMDQ_WQE_HEADER_##member##_MASK) \
			 << HINIC_CMDQ_WQE_HEADER_##member##_SHIFT)

#घोषणा HINIC_CMDQ_WQE_HEADER_GET(val, member)                  \
			(((val) >> HINIC_CMDQ_WQE_HEADER_##member##_SHIFT) \
			 & HINIC_CMDQ_WQE_HEADER_##member##_MASK)

#घोषणा HINIC_SQ_CTRL_BUFDESC_SECT_LEN_SHIFT           0
#घोषणा HINIC_SQ_CTRL_TASKSECT_LEN_SHIFT               16
#घोषणा HINIC_SQ_CTRL_DATA_FORMAT_SHIFT                22
#घोषणा HINIC_SQ_CTRL_LEN_SHIFT                        29

#घोषणा HINIC_SQ_CTRL_BUFDESC_SECT_LEN_MASK            0xFF
#घोषणा HINIC_SQ_CTRL_TASKSECT_LEN_MASK                0x1F
#घोषणा HINIC_SQ_CTRL_DATA_FORMAT_MASK                 0x1
#घोषणा HINIC_SQ_CTRL_LEN_MASK                         0x3

#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_PLDOFF_SHIFT          2
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_UFO_SHIFT             10
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_TSO_SHIFT             11
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_TCPUDP_CS_SHIFT       12
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_MSS_SHIFT             13
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_SCTP_SHIFT            27
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_UC_SHIFT              28
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_PRI_SHIFT             29

#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_PLDOFF_MASK           0xFF
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_UFO_MASK              0x1
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_TSO_MASK              0x1
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_TCPUDP_CS_MASK	       0x1
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_MSS_MASK              0x3FFF
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_SCTP_MASK             0x1
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_UC_MASK               0x1
#घोषणा HINIC_SQ_CTRL_QUEUE_INFO_PRI_MASK              0x7

#घोषणा HINIC_SQ_CTRL_SET(val, member)          \
		(((u32)(val) & HINIC_SQ_CTRL_##member##_MASK) \
		 << HINIC_SQ_CTRL_##member##_SHIFT)

#घोषणा HINIC_SQ_CTRL_GET(val, member)          \
		(((val) >> HINIC_SQ_CTRL_##member##_SHIFT) \
		 & HINIC_SQ_CTRL_##member##_MASK)

#घोषणा HINIC_SQ_CTRL_CLEAR(val, member)	\
		((u32)(val) & (~(HINIC_SQ_CTRL_##member##_MASK \
		 << HINIC_SQ_CTRL_##member##_SHIFT)))

#घोषणा HINIC_SQ_TASK_INFO0_L2HDR_LEN_SHIFT     0
#घोषणा HINIC_SQ_TASK_INFO0_L4_OFFLOAD_SHIFT    8
#घोषणा HINIC_SQ_TASK_INFO0_INNER_L3TYPE_SHIFT  10
#घोषणा HINIC_SQ_TASK_INFO0_VLAN_OFFLOAD_SHIFT  12
#घोषणा HINIC_SQ_TASK_INFO0_PARSE_FLAG_SHIFT    13
/* 1 bit reserved */
#घोषणा HINIC_SQ_TASK_INFO0_TSO_FLAG_SHIFT      15
#घोषणा HINIC_SQ_TASK_INFO0_VLAN_TAG_SHIFT      16

#घोषणा HINIC_SQ_TASK_INFO0_L2HDR_LEN_MASK      0xFF
#घोषणा HINIC_SQ_TASK_INFO0_L4_OFFLOAD_MASK     0x3
#घोषणा HINIC_SQ_TASK_INFO0_INNER_L3TYPE_MASK   0x3
#घोषणा HINIC_SQ_TASK_INFO0_VLAN_OFFLOAD_MASK   0x1
#घोषणा HINIC_SQ_TASK_INFO0_PARSE_FLAG_MASK     0x1
/* 1 bit reserved */
#घोषणा HINIC_SQ_TASK_INFO0_TSO_FLAG_MASK       0x1
#घोषणा HINIC_SQ_TASK_INFO0_VLAN_TAG_MASK       0xFFFF

#घोषणा HINIC_SQ_TASK_INFO0_SET(val, member)    \
		(((u32)(val) & HINIC_SQ_TASK_INFO0_##member##_MASK) <<  \
		 HINIC_SQ_TASK_INFO0_##member##_SHIFT)

/* 8 bits reserved */
#घोषणा HINIC_SQ_TASK_INFO1_MEDIA_TYPE_SHIFT    8
#घोषणा HINIC_SQ_TASK_INFO1_INNER_L4LEN_SHIFT   16
#घोषणा HINIC_SQ_TASK_INFO1_INNER_L3LEN_SHIFT   24

/* 8 bits reserved */
#घोषणा HINIC_SQ_TASK_INFO1_MEDIA_TYPE_MASK     0xFF
#घोषणा HINIC_SQ_TASK_INFO1_INNER_L4LEN_MASK    0xFF
#घोषणा HINIC_SQ_TASK_INFO1_INNER_L3LEN_MASK    0xFF

#घोषणा HINIC_SQ_TASK_INFO1_SET(val, member)    \
		(((u32)(val) & HINIC_SQ_TASK_INFO1_##member##_MASK) <<  \
		 HINIC_SQ_TASK_INFO1_##member##_SHIFT)

#घोषणा HINIC_SQ_TASK_INFO2_TUNNEL_L4LEN_SHIFT  0
#घोषणा HINIC_SQ_TASK_INFO2_OUTER_L3LEN_SHIFT   8
#घोषणा HINIC_SQ_TASK_INFO2_TUNNEL_L4TYPE_SHIFT 16
/* 1 bit reserved */
#घोषणा HINIC_SQ_TASK_INFO2_OUTER_L3TYPE_SHIFT  24
/* 8 bits reserved */

#घोषणा HINIC_SQ_TASK_INFO2_TUNNEL_L4LEN_MASK   0xFF
#घोषणा HINIC_SQ_TASK_INFO2_OUTER_L3LEN_MASK    0xFF
#घोषणा HINIC_SQ_TASK_INFO2_TUNNEL_L4TYPE_MASK  0x7
/* 1 bit reserved */
#घोषणा HINIC_SQ_TASK_INFO2_OUTER_L3TYPE_MASK   0x3
/* 8 bits reserved */

#घोषणा HINIC_SQ_TASK_INFO2_SET(val, member)    \
		(((u32)(val) & HINIC_SQ_TASK_INFO2_##member##_MASK) <<  \
		 HINIC_SQ_TASK_INFO2_##member##_SHIFT)

/* 31 bits reserved */
#घोषणा HINIC_SQ_TASK_INFO4_L2TYPE_SHIFT        31

/* 31 bits reserved */
#घोषणा HINIC_SQ_TASK_INFO4_L2TYPE_MASK         0x1

#घोषणा HINIC_SQ_TASK_INFO4_SET(val, member)    \
		(((u32)(val) & HINIC_SQ_TASK_INFO4_##member##_MASK) << \
		 HINIC_SQ_TASK_INFO4_##member##_SHIFT)

#घोषणा HINIC_RQ_CQE_STATUS_RXDONE_SHIFT        31

#घोषणा HINIC_RQ_CQE_STATUS_RXDONE_MASK         0x1

#घोषणा HINIC_RQ_CQE_STATUS_CSUM_ERR_SHIFT	0

#घोषणा HINIC_RQ_CQE_STATUS_CSUM_ERR_MASK	0xFFFFU

#घोषणा HINIC_RQ_CQE_STATUS_GET(val, member)    \
		(((val) >> HINIC_RQ_CQE_STATUS_##member##_SHIFT) & \
		 HINIC_RQ_CQE_STATUS_##member##_MASK)

#घोषणा HINIC_RQ_CQE_STATUS_CLEAR(val, member)  \
		((val) & (~(HINIC_RQ_CQE_STATUS_##member##_MASK << \
		 HINIC_RQ_CQE_STATUS_##member##_SHIFT)))

#घोषणा HINIC_RQ_CQE_SGE_LEN_SHIFT              16

#घोषणा HINIC_RQ_CQE_SGE_LEN_MASK               0xFFFF

#घोषणा HINIC_RQ_CQE_SGE_GET(val, member)       \
		(((val) >> HINIC_RQ_CQE_SGE_##member##_SHIFT) & \
		 HINIC_RQ_CQE_SGE_##member##_MASK)

#घोषणा HINIC_RQ_CTRL_BUFDESC_SECT_LEN_SHIFT    0
#घोषणा HINIC_RQ_CTRL_COMPLETE_FORMAT_SHIFT     15
#घोषणा HINIC_RQ_CTRL_COMPLETE_LEN_SHIFT        27
#घोषणा HINIC_RQ_CTRL_LEN_SHIFT                 29

#घोषणा HINIC_RQ_CTRL_BUFDESC_SECT_LEN_MASK     0xFF
#घोषणा HINIC_RQ_CTRL_COMPLETE_FORMAT_MASK      0x1
#घोषणा HINIC_RQ_CTRL_COMPLETE_LEN_MASK         0x3
#घोषणा HINIC_RQ_CTRL_LEN_MASK                  0x3

#घोषणा HINIC_RQ_CTRL_SET(val, member)          \
		(((u32)(val) & HINIC_RQ_CTRL_##member##_MASK) << \
		 HINIC_RQ_CTRL_##member##_SHIFT)

#घोषणा HINIC_SQ_WQE_SIZE(nr_sges)              \
		(माप(काष्ठा hinic_sq_ctrl) + \
		 माप(काष्ठा hinic_sq_task) + \
		 (nr_sges) * माप(काष्ठा hinic_sq_bufdesc))

#घोषणा HINIC_SCMD_DATA_LEN                     16

#घोषणा HINIC_MAX_SQ_BUFDESCS                   17

#घोषणा HINIC_SQ_WQE_MAX_SIZE                   320
#घोषणा HINIC_RQ_WQE_SIZE                       32

#घोषणा HINIC_MSS_DEFAULT		        0x3E00
#घोषणा HINIC_MSS_MIN		                0x50

#घोषणा RQ_CQE_STATUS_NUM_LRO_SHIFT		16
#घोषणा RQ_CQE_STATUS_NUM_LRO_MASK		0xFFU

#घोषणा RQ_CQE_STATUS_GET(val, member)		(((val) >> \
			RQ_CQE_STATUS_##member##_SHIFT) & \
			RQ_CQE_STATUS_##member##_MASK)

#घोषणा HINIC_GET_RX_NUM_LRO(status)	\
		RQ_CQE_STATUS_GET(status, NUM_LRO)

#घोषणा RQ_CQE_OFFOLAD_TYPE_PKT_TYPE_SHIFT		0
#घोषणा RQ_CQE_OFFOLAD_TYPE_PKT_TYPE_MASK		0xFFFU
#घोषणा RQ_CQE_OFFOLAD_TYPE_VLAN_EN_SHIFT		21
#घोषणा RQ_CQE_OFFOLAD_TYPE_VLAN_EN_MASK		0x1U

#घोषणा RQ_CQE_OFFOLAD_TYPE_GET(val, member)		(((val) >> \
				RQ_CQE_OFFOLAD_TYPE_##member##_SHIFT) & \
				RQ_CQE_OFFOLAD_TYPE_##member##_MASK)

#घोषणा HINIC_GET_RX_PKT_TYPE(offload_type)	\
			RQ_CQE_OFFOLAD_TYPE_GET(offload_type, PKT_TYPE)

#घोषणा HINIC_GET_RX_VLAN_OFFLOAD_EN(offload_type)	\
			RQ_CQE_OFFOLAD_TYPE_GET(offload_type, VLAN_EN)

#घोषणा RQ_CQE_SGE_VLAN_MASK				0xFFFFU
#घोषणा RQ_CQE_SGE_VLAN_SHIFT				0

#घोषणा RQ_CQE_SGE_GET(val, member)			(((val) >> \
					RQ_CQE_SGE_##member##_SHIFT) & \
					RQ_CQE_SGE_##member##_MASK)

#घोषणा HINIC_GET_RX_VLAN_TAG(vlan_len)	\
		RQ_CQE_SGE_GET(vlan_len, VLAN)

#घोषणा HINIC_RSS_TYPE_VALID_SHIFT			23
#घोषणा HINIC_RSS_TYPE_TCP_IPV6_EXT_SHIFT		24
#घोषणा HINIC_RSS_TYPE_IPV6_EXT_SHIFT			25
#घोषणा HINIC_RSS_TYPE_TCP_IPV6_SHIFT			26
#घोषणा HINIC_RSS_TYPE_IPV6_SHIFT			27
#घोषणा HINIC_RSS_TYPE_TCP_IPV4_SHIFT			28
#घोषणा HINIC_RSS_TYPE_IPV4_SHIFT			29
#घोषणा HINIC_RSS_TYPE_UDP_IPV6_SHIFT			30
#घोषणा HINIC_RSS_TYPE_UDP_IPV4_SHIFT			31

#घोषणा HINIC_RSS_TYPE_SET(val, member)                        \
		(((u32)(val) & 0x1) << HINIC_RSS_TYPE_##member##_SHIFT)

#घोषणा HINIC_RSS_TYPE_GET(val, member)                        \
		(((u32)(val) >> HINIC_RSS_TYPE_##member##_SHIFT) & 0x1)

क्रमागत hinic_l4offload_type अणु
	HINIC_L4_OFF_DISABLE            = 0,
	HINIC_TCP_OFFLOAD_ENABLE        = 1,
	HINIC_SCTP_OFFLOAD_ENABLE       = 2,
	HINIC_UDP_OFFLOAD_ENABLE        = 3,
पूर्ण;

क्रमागत hinic_vlan_offload अणु
	HINIC_VLAN_OFF_DISABLE = 0,
	HINIC_VLAN_OFF_ENABLE  = 1,
पूर्ण;

क्रमागत hinic_pkt_parsed अणु
	HINIC_PKT_NOT_PARSED = 0,
	HINIC_PKT_PARSED     = 1,
पूर्ण;

क्रमागत hinic_l3_offload_type अणु
	L3TYPE_UNKNOWN = 0,
	IPV6_PKT = 1,
	IPV4_PKT_NO_CHKSUM_OFFLOAD = 2,
	IPV4_PKT_WITH_CHKSUM_OFFLOAD = 3,
पूर्ण;

क्रमागत hinic_l4_offload_type अणु
	OFFLOAD_DISABLE     = 0,
	TCP_OFFLOAD_ENABLE  = 1,
	SCTP_OFFLOAD_ENABLE = 2,
	UDP_OFFLOAD_ENABLE  = 3,
पूर्ण;

क्रमागत hinic_l4_tunnel_type अणु
	NOT_TUNNEL,
	TUNNEL_UDP_NO_CSUM,
	TUNNEL_UDP_CSUM,
पूर्ण;

क्रमागत hinic_outer_l3type अणु
	HINIC_OUTER_L3TYPE_UNKNOWN              = 0,
	HINIC_OUTER_L3TYPE_IPV6                 = 1,
	HINIC_OUTER_L3TYPE_IPV4_NO_CHKSUM       = 2,
	HINIC_OUTER_L3TYPE_IPV4_CHKSUM          = 3,
पूर्ण;

क्रमागत hinic_media_type अणु
	HINIC_MEDIA_UNKNOWN = 0,
पूर्ण;

क्रमागत hinic_l2type अणु
	HINIC_L2TYPE_ETH = 0,
पूर्ण;

क्रमागत hinc_tunnel_l4type अणु
	HINIC_TUNNEL_L4TYPE_UNKNOWN = 0,
पूर्ण;

काष्ठा hinic_cmdq_header अणु
	u32     header_info;
	u32     saved_data;
पूर्ण;

काष्ठा hinic_status अणु
	u32 status_info;
पूर्ण;

काष्ठा hinic_ctrl अणु
	u32 ctrl_info;
पूर्ण;

काष्ठा hinic_sge_resp अणु
	काष्ठा hinic_sge        sge;
	u32                     rsvd;
पूर्ण;

काष्ठा hinic_cmdq_completion अणु
	/* HW Format */
	जोड़ अणु
		काष्ठा hinic_sge_resp   sge_resp;
		u64                     direct_resp;
	पूर्ण;
पूर्ण;

काष्ठा hinic_scmd_bufdesc अणु
	u32     buf_len;
	u32     rsvd;
	u8      data[HINIC_SCMD_DATA_LEN];
पूर्ण;

काष्ठा hinic_lcmd_bufdesc अणु
	काष्ठा hinic_sge        sge;
	u32                     rsvd1;
	u64                     rsvd2;
	u64                     rsvd3;
पूर्ण;

काष्ठा hinic_cmdq_wqe_scmd अणु
	काष्ठा hinic_cmdq_header        header;
	u64                             rsvd;
	काष्ठा hinic_status             status;
	काष्ठा hinic_ctrl               ctrl;
	काष्ठा hinic_cmdq_completion    completion;
	काष्ठा hinic_scmd_bufdesc       buf_desc;
पूर्ण;

काष्ठा hinic_cmdq_wqe_lcmd अणु
	काष्ठा hinic_cmdq_header        header;
	काष्ठा hinic_status             status;
	काष्ठा hinic_ctrl               ctrl;
	काष्ठा hinic_cmdq_completion    completion;
	काष्ठा hinic_lcmd_bufdesc       buf_desc;
पूर्ण;

काष्ठा hinic_cmdq_direct_wqe अणु
	काष्ठा hinic_cmdq_wqe_scmd      wqe_scmd;
पूर्ण;

काष्ठा hinic_cmdq_wqe अणु
	/* HW Format */
	जोड़ अणु
		काष्ठा hinic_cmdq_direct_wqe    direct_wqe;
		काष्ठा hinic_cmdq_wqe_lcmd      wqe_lcmd;
	पूर्ण;
पूर्ण;

काष्ठा hinic_sq_ctrl अणु
	u32     ctrl_info;
	u32     queue_info;
पूर्ण;

काष्ठा hinic_sq_task अणु
	u32     pkt_info0;
	u32     pkt_info1;
	u32     pkt_info2;
	u32     ufo_v6_identअगरy;
	u32     pkt_info4;
	u32     zero_pad;
पूर्ण;

काष्ठा hinic_sq_bufdesc अणु
	काष्ठा hinic_sge sge;
	u32     rsvd;
पूर्ण;

काष्ठा hinic_sq_wqe अणु
	काष्ठा hinic_sq_ctrl            ctrl;
	काष्ठा hinic_sq_task            task;
	काष्ठा hinic_sq_bufdesc         buf_descs[HINIC_MAX_SQ_BUFDESCS];
पूर्ण;

काष्ठा hinic_rq_cqe अणु
	u32     status;
	u32     len;

	u32     offload_type;
	u32     rsvd3;
	u32     rsvd4;
	u32     rsvd5;
	u32     rsvd6;
	u32     rsvd7;
पूर्ण;

काष्ठा hinic_rq_ctrl अणु
	u32     ctrl_info;
पूर्ण;

काष्ठा hinic_rq_cqe_sect अणु
	काष्ठा hinic_sge        sge;
	u32                     rsvd;
पूर्ण;

काष्ठा hinic_rq_bufdesc अणु
	u32     hi_addr;
	u32     lo_addr;
पूर्ण;

काष्ठा hinic_rq_wqe अणु
	काष्ठा hinic_rq_ctrl            ctrl;
	u32                             rsvd;
	काष्ठा hinic_rq_cqe_sect        cqe_sect;
	काष्ठा hinic_rq_bufdesc         buf_desc;
पूर्ण;

काष्ठा hinic_hw_wqe अणु
	/* HW Format */
	जोड़ अणु
		काष्ठा hinic_cmdq_wqe   cmdq_wqe;
		काष्ठा hinic_sq_wqe     sq_wqe;
		काष्ठा hinic_rq_wqe     rq_wqe;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर
