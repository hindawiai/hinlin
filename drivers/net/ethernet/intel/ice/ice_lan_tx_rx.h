<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_LAN_TX_RX_H_
#घोषणा _ICE_LAN_TX_RX_H_

जोड़ ice_32byte_rx_desc अणु
	काष्ठा अणु
		__le64 pkt_addr; /* Packet buffer address */
		__le64 hdr_addr; /* Header buffer address */
			/* bit 0 of hdr_addr is DD bit */
		__le64 rsvd1;
		__le64 rsvd2;
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा अणु
				__le16 mirroring_status;
				__le16 l2tag1;
			पूर्ण lo_dword;
			जोड़ अणु
				__le32 rss; /* RSS Hash */
				__le32 fd_id; /* Flow Director filter ID */
			पूर्ण hi_dword;
		पूर्ण qword0;
		काष्ठा अणु
			/* status/error/PTYPE/length */
			__le64 status_error_len;
		पूर्ण qword1;
		काष्ठा अणु
			__le16 ext_status; /* extended status */
			__le16 rsvd;
			__le16 l2tag2_1;
			__le16 l2tag2_2;
		पूर्ण qword2;
		काष्ठा अणु
			__le32 reserved;
			__le32 fd_id;
		पूर्ण qword3;
	पूर्ण wb; /* ग_लिखोback */
पूर्ण;

काष्ठा ice_fltr_desc अणु
	__le64 qidx_compq_space_stat;
	__le64 dtype_cmd_vsi_fdid;
पूर्ण;

#घोषणा ICE_FXD_FLTR_QW0_QINDEX_S	0
#घोषणा ICE_FXD_FLTR_QW0_QINDEX_M	(0x7FFULL << ICE_FXD_FLTR_QW0_QINDEX_S)
#घोषणा ICE_FXD_FLTR_QW0_COMP_Q_S	11
#घोषणा ICE_FXD_FLTR_QW0_COMP_Q_M	BIT_ULL(ICE_FXD_FLTR_QW0_COMP_Q_S)
#घोषणा ICE_FXD_FLTR_QW0_COMP_Q_ZERO	0x0ULL

#घोषणा ICE_FXD_FLTR_QW0_COMP_REPORT_S	12
#घोषणा ICE_FXD_FLTR_QW0_COMP_REPORT_M	\
				(0x3ULL << ICE_FXD_FLTR_QW0_COMP_REPORT_S)
#घोषणा ICE_FXD_FLTR_QW0_COMP_REPORT_SW_FAIL	0x1ULL
#घोषणा ICE_FXD_FLTR_QW0_COMP_REPORT_SW		0x2ULL

#घोषणा ICE_FXD_FLTR_QW0_FD_SPACE_S	14
#घोषणा ICE_FXD_FLTR_QW0_FD_SPACE_M	(0x3ULL << ICE_FXD_FLTR_QW0_FD_SPACE_S)
#घोषणा ICE_FXD_FLTR_QW0_FD_SPACE_GUAR_BEST		0x2ULL

#घोषणा ICE_FXD_FLTR_QW0_STAT_CNT_S	16
#घोषणा ICE_FXD_FLTR_QW0_STAT_CNT_M	\
				(0x1FFFULL << ICE_FXD_FLTR_QW0_STAT_CNT_S)
#घोषणा ICE_FXD_FLTR_QW0_STAT_ENA_S	29
#घोषणा ICE_FXD_FLTR_QW0_STAT_ENA_M	(0x3ULL << ICE_FXD_FLTR_QW0_STAT_ENA_S)
#घोषणा ICE_FXD_FLTR_QW0_STAT_ENA_PKTS		0x1ULL

#घोषणा ICE_FXD_FLTR_QW0_EVICT_ENA_S	31
#घोषणा ICE_FXD_FLTR_QW0_EVICT_ENA_M	BIT_ULL(ICE_FXD_FLTR_QW0_EVICT_ENA_S)
#घोषणा ICE_FXD_FLTR_QW0_EVICT_ENA_FALSE	0x0ULL
#घोषणा ICE_FXD_FLTR_QW0_EVICT_ENA_TRUE		0x1ULL

#घोषणा ICE_FXD_FLTR_QW0_TO_Q_S		32
#घोषणा ICE_FXD_FLTR_QW0_TO_Q_M		(0x7ULL << ICE_FXD_FLTR_QW0_TO_Q_S)
#घोषणा ICE_FXD_FLTR_QW0_TO_Q_EQUALS_QINDEX	0x0ULL

#घोषणा ICE_FXD_FLTR_QW0_TO_Q_PRI_S	35
#घोषणा ICE_FXD_FLTR_QW0_TO_Q_PRI_M	(0x7ULL << ICE_FXD_FLTR_QW0_TO_Q_PRI_S)
#घोषणा ICE_FXD_FLTR_QW0_TO_Q_PRIO1	0x1ULL

#घोषणा ICE_FXD_FLTR_QW0_DPU_RECIPE_S	38
#घोषणा ICE_FXD_FLTR_QW0_DPU_RECIPE_M	\
			(0x3ULL << ICE_FXD_FLTR_QW0_DPU_RECIPE_S)
#घोषणा ICE_FXD_FLTR_QW0_DPU_RECIPE_DFLT	0x0ULL

#घोषणा ICE_FXD_FLTR_QW0_DROP_S		40
#घोषणा ICE_FXD_FLTR_QW0_DROP_M		BIT_ULL(ICE_FXD_FLTR_QW0_DROP_S)
#घोषणा ICE_FXD_FLTR_QW0_DROP_NO	0x0ULL
#घोषणा ICE_FXD_FLTR_QW0_DROP_YES	0x1ULL

#घोषणा ICE_FXD_FLTR_QW0_FLEX_PRI_S	41
#घोषणा ICE_FXD_FLTR_QW0_FLEX_PRI_M	(0x7ULL << ICE_FXD_FLTR_QW0_FLEX_PRI_S)
#घोषणा ICE_FXD_FLTR_QW0_FLEX_PRI_NONE	0x0ULL

#घोषणा ICE_FXD_FLTR_QW0_FLEX_MDID_S	44
#घोषणा ICE_FXD_FLTR_QW0_FLEX_MDID_M	(0xFULL << ICE_FXD_FLTR_QW0_FLEX_MDID_S)
#घोषणा ICE_FXD_FLTR_QW0_FLEX_MDID0	0x0ULL

#घोषणा ICE_FXD_FLTR_QW0_FLEX_VAL_S	48
#घोषणा ICE_FXD_FLTR_QW0_FLEX_VAL_M	\
				(0xFFFFULL << ICE_FXD_FLTR_QW0_FLEX_VAL_S)
#घोषणा ICE_FXD_FLTR_QW0_FLEX_VAL0	0x0ULL

#घोषणा ICE_FXD_FLTR_QW1_DTYPE_S	0
#घोषणा ICE_FXD_FLTR_QW1_DTYPE_M	(0xFULL << ICE_FXD_FLTR_QW1_DTYPE_S)
#घोषणा ICE_FXD_FLTR_QW1_PCMD_S		4
#घोषणा ICE_FXD_FLTR_QW1_PCMD_M		BIT_ULL(ICE_FXD_FLTR_QW1_PCMD_S)
#घोषणा ICE_FXD_FLTR_QW1_PCMD_ADD	0x0ULL
#घोषणा ICE_FXD_FLTR_QW1_PCMD_REMOVE	0x1ULL

#घोषणा ICE_FXD_FLTR_QW1_PROF_PRI_S	5
#घोषणा ICE_FXD_FLTR_QW1_PROF_PRI_M	(0x7ULL << ICE_FXD_FLTR_QW1_PROF_PRI_S)
#घोषणा ICE_FXD_FLTR_QW1_PROF_PRIO_ZERO	0x0ULL

#घोषणा ICE_FXD_FLTR_QW1_PROF_S		8
#घोषणा ICE_FXD_FLTR_QW1_PROF_M		(0x3FULL << ICE_FXD_FLTR_QW1_PROF_S)
#घोषणा ICE_FXD_FLTR_QW1_PROF_ZERO	0x0ULL

#घोषणा ICE_FXD_FLTR_QW1_FD_VSI_S	14
#घोषणा ICE_FXD_FLTR_QW1_FD_VSI_M	(0x3FFULL << ICE_FXD_FLTR_QW1_FD_VSI_S)
#घोषणा ICE_FXD_FLTR_QW1_SWAP_S		24
#घोषणा ICE_FXD_FLTR_QW1_SWAP_M		BIT_ULL(ICE_FXD_FLTR_QW1_SWAP_S)
#घोषणा ICE_FXD_FLTR_QW1_SWAP_NOT_SET	0x0ULL
#घोषणा ICE_FXD_FLTR_QW1_SWAP_SET	0x1ULL

#घोषणा ICE_FXD_FLTR_QW1_FDID_PRI_S	25
#घोषणा ICE_FXD_FLTR_QW1_FDID_PRI_M	(0x7ULL << ICE_FXD_FLTR_QW1_FDID_PRI_S)
#घोषणा ICE_FXD_FLTR_QW1_FDID_PRI_ONE	0x1ULL
#घोषणा ICE_FXD_FLTR_QW1_FDID_PRI_THREE	0x3ULL

#घोषणा ICE_FXD_FLTR_QW1_FDID_MDID_S	28
#घोषणा ICE_FXD_FLTR_QW1_FDID_MDID_M	(0xFULL << ICE_FXD_FLTR_QW1_FDID_MDID_S)
#घोषणा ICE_FXD_FLTR_QW1_FDID_MDID_FD	0x05ULL

#घोषणा ICE_FXD_FLTR_QW1_FDID_S		32
#घोषणा ICE_FXD_FLTR_QW1_FDID_M		\
			(0xFFFFFFFFULL << ICE_FXD_FLTR_QW1_FDID_S)
#घोषणा ICE_FXD_FLTR_QW1_FDID_ZERO	0x0ULL

/* definition क्रम FD filter programming status descriptor WB क्रमmat */
#घोषणा ICE_FXD_FLTR_WB_QW1_DD_S	0
#घोषणा ICE_FXD_FLTR_WB_QW1_DD_M	(0x1ULL << ICE_FXD_FLTR_WB_QW1_DD_S)
#घोषणा ICE_FXD_FLTR_WB_QW1_DD_YES	0x1ULL

#घोषणा ICE_FXD_FLTR_WB_QW1_PROG_ID_S	1
#घोषणा ICE_FXD_FLTR_WB_QW1_PROG_ID_M	\
				(0x3ULL << ICE_FXD_FLTR_WB_QW1_PROG_ID_S)
#घोषणा ICE_FXD_FLTR_WB_QW1_PROG_ADD	0x0ULL
#घोषणा ICE_FXD_FLTR_WB_QW1_PROG_DEL	0x1ULL

#घोषणा ICE_FXD_FLTR_WB_QW1_FAIL_S	4
#घोषणा ICE_FXD_FLTR_WB_QW1_FAIL_M	(0x1ULL << ICE_FXD_FLTR_WB_QW1_FAIL_S)
#घोषणा ICE_FXD_FLTR_WB_QW1_FAIL_YES	0x1ULL

#घोषणा ICE_FXD_FLTR_WB_QW1_FAIL_PROF_S	5
#घोषणा ICE_FXD_FLTR_WB_QW1_FAIL_PROF_M	\
				(0x1ULL << ICE_FXD_FLTR_WB_QW1_FAIL_PROF_S)
#घोषणा ICE_FXD_FLTR_WB_QW1_FAIL_PROF_YES	0x1ULL

काष्ठा ice_rx_ptype_decoded अणु
	u32 ptype:10;
	u32 known:1;
	u32 outer_ip:1;
	u32 outer_ip_ver:2;
	u32 outer_frag:1;
	u32 tunnel_type:3;
	u32 tunnel_end_prot:2;
	u32 tunnel_end_frag:1;
	u32 inner_prot:4;
	u32 payload_layer:3;
पूर्ण;

क्रमागत ice_rx_ptype_outer_ip अणु
	ICE_RX_PTYPE_OUTER_L2	= 0,
	ICE_RX_PTYPE_OUTER_IP	= 1,
पूर्ण;

क्रमागत ice_rx_ptype_outer_ip_ver अणु
	ICE_RX_PTYPE_OUTER_NONE	= 0,
	ICE_RX_PTYPE_OUTER_IPV4	= 1,
	ICE_RX_PTYPE_OUTER_IPV6	= 2,
पूर्ण;

क्रमागत ice_rx_ptype_outer_fragmented अणु
	ICE_RX_PTYPE_NOT_FRAG	= 0,
	ICE_RX_PTYPE_FRAG	= 1,
पूर्ण;

क्रमागत ice_rx_ptype_tunnel_type अणु
	ICE_RX_PTYPE_TUNNEL_NONE		= 0,
	ICE_RX_PTYPE_TUNNEL_IP_IP		= 1,
	ICE_RX_PTYPE_TUNNEL_IP_GRENAT		= 2,
	ICE_RX_PTYPE_TUNNEL_IP_GRENAT_MAC	= 3,
	ICE_RX_PTYPE_TUNNEL_IP_GRENAT_MAC_VLAN	= 4,
पूर्ण;

क्रमागत ice_rx_ptype_tunnel_end_prot अणु
	ICE_RX_PTYPE_TUNNEL_END_NONE	= 0,
	ICE_RX_PTYPE_TUNNEL_END_IPV4	= 1,
	ICE_RX_PTYPE_TUNNEL_END_IPV6	= 2,
पूर्ण;

क्रमागत ice_rx_ptype_inner_prot अणु
	ICE_RX_PTYPE_INNER_PROT_NONE		= 0,
	ICE_RX_PTYPE_INNER_PROT_UDP		= 1,
	ICE_RX_PTYPE_INNER_PROT_TCP		= 2,
	ICE_RX_PTYPE_INNER_PROT_SCTP		= 3,
	ICE_RX_PTYPE_INNER_PROT_ICMP		= 4,
	ICE_RX_PTYPE_INNER_PROT_TIMESYNC	= 5,
पूर्ण;

क्रमागत ice_rx_ptype_payload_layer अणु
	ICE_RX_PTYPE_PAYLOAD_LAYER_NONE	= 0,
	ICE_RX_PTYPE_PAYLOAD_LAYER_PAY2	= 1,
	ICE_RX_PTYPE_PAYLOAD_LAYER_PAY3	= 2,
	ICE_RX_PTYPE_PAYLOAD_LAYER_PAY4	= 3,
पूर्ण;

/* Rx Flex Descriptor
 * This descriptor is used instead of the legacy version descriptor when
 * ice_rlan_ctx.adv_desc is set
 */
जोड़ ice_32b_rx_flex_desc अणु
	काष्ठा अणु
		__le64 pkt_addr; /* Packet buffer address */
		__le64 hdr_addr; /* Header buffer address */
				 /* bit 0 of hdr_addr is DD bit */
		__le64 rsvd1;
		__le64 rsvd2;
	पूर्ण पढ़ो;
	काष्ठा अणु
		/* Qword 0 */
		u8 rxdid; /* descriptor builder profile ID */
		u8 mir_id_umb_cast; /* mirror=[5:0], umb=[7:6] */
		__le16 ptype_flex_flags0; /* ptype=[9:0], ff0=[15:10] */
		__le16 pkt_len; /* [15:14] are reserved */
		__le16 hdr_len_sph_flex_flags1; /* header=[10:0] */
						/* sph=[11:11] */
						/* ff1/ext=[15:12] */

		/* Qword 1 */
		__le16 status_error0;
		__le16 l2tag1;
		__le16 flex_meta0;
		__le16 flex_meta1;

		/* Qword 2 */
		__le16 status_error1;
		u8 flex_flags2;
		u8 समय_stamp_low;
		__le16 l2tag2_1st;
		__le16 l2tag2_2nd;

		/* Qword 3 */
		__le16 flex_meta2;
		__le16 flex_meta3;
		जोड़ अणु
			काष्ठा अणु
				__le16 flex_meta4;
				__le16 flex_meta5;
			पूर्ण flex;
			__le32 ts_high;
		पूर्ण flex_ts;
	पूर्ण wb; /* ग_लिखोback */
पूर्ण;

/* Rx Flex Descriptor NIC Profile
 * This descriptor corresponds to RxDID 2 which contains
 * metadata fields क्रम RSS, flow ID and बारtamp info
 */
काष्ठा ice_32b_rx_flex_desc_nic अणु
	/* Qword 0 */
	u8 rxdid;
	u8 mir_id_umb_cast;
	__le16 ptype_flexi_flags0;
	__le16 pkt_len;
	__le16 hdr_len_sph_flex_flags1;

	/* Qword 1 */
	__le16 status_error0;
	__le16 l2tag1;
	__le32 rss_hash;

	/* Qword 2 */
	__le16 status_error1;
	u8 flexi_flags2;
	u8 ts_low;
	__le16 l2tag2_1st;
	__le16 l2tag2_2nd;

	/* Qword 3 */
	__le32 flow_id;
	जोड़ अणु
		काष्ठा अणु
			__le16 vlan_id;
			__le16 flow_id_ipv6;
		पूर्ण flex;
		__le32 ts_high;
	पूर्ण flex_ts;
पूर्ण;

/* Receive Flex Descriptor profile IDs: There are a total
 * of 64 profiles where profile IDs 0/1 are क्रम legacy; and
 * profiles 2-63 are flex profiles that can be programmed
 * with a specअगरic metadata (profile 7 reserved क्रम HW)
 */
क्रमागत ice_rxdid अणु
	ICE_RXDID_LEGACY_0		= 0,
	ICE_RXDID_LEGACY_1		= 1,
	ICE_RXDID_FLEX_NIC		= 2,
	ICE_RXDID_FLEX_NIC_2		= 6,
	ICE_RXDID_HW			= 7,
	ICE_RXDID_LAST			= 63,
पूर्ण;

/* Receive Flex Descriptor Rx opcode values */
#घोषणा ICE_RX_OPC_MDID		0x01

/* Receive Descriptor MDID values that access packet flags */
क्रमागत ice_flex_mdid_pkt_flags अणु
	ICE_RX_MDID_PKT_FLAGS_15_0	= 20,
	ICE_RX_MDID_PKT_FLAGS_31_16,
	ICE_RX_MDID_PKT_FLAGS_47_32,
	ICE_RX_MDID_PKT_FLAGS_63_48,
पूर्ण;

/* Receive Descriptor MDID values */
क्रमागत ice_flex_rx_mdid अणु
	ICE_RX_MDID_FLOW_ID_LOWER	= 5,
	ICE_RX_MDID_FLOW_ID_HIGH,
	ICE_RX_MDID_SRC_VSI		= 19,
	ICE_RX_MDID_HASH_LOW		= 56,
	ICE_RX_MDID_HASH_HIGH,
पूर्ण;

/* Rx/Tx Flag64 packet flag bits */
क्रमागत ice_flg64_bits अणु
	ICE_FLG_PKT_DSI		= 0,
	ICE_FLG_EVLAN_x8100	= 14,
	ICE_FLG_EVLAN_x9100,
	ICE_FLG_VLAN_x8100,
	ICE_FLG_TNL_MAC		= 22,
	ICE_FLG_TNL_VLAN,
	ICE_FLG_PKT_FRG,
	ICE_FLG_FIN		= 32,
	ICE_FLG_SYN,
	ICE_FLG_RST,
	ICE_FLG_TNL0		= 38,
	ICE_FLG_TNL1,
	ICE_FLG_TNL2,
	ICE_FLG_UDP_GRE,
	ICE_FLG_RSVD		= 63
पूर्ण;

/* क्रम ice_32byte_rx_flex_desc.ptype_flexi_flags0 member */
#घोषणा ICE_RX_FLEX_DESC_PTYPE_M	(0x3FF) /* 10-bits */

/* क्रम ice_32byte_rx_flex_desc.pkt_length member */
#घोषणा ICE_RX_FLX_DESC_PKT_LEN_M	(0x3FFF) /* 14-bits */

क्रमागत ice_rx_flex_desc_status_error_0_bits अणु
	/* Note: These are predefined bit offsets */
	ICE_RX_FLEX_DESC_STATUS0_DD_S = 0,
	ICE_RX_FLEX_DESC_STATUS0_खातापूर्ण_S,
	ICE_RX_FLEX_DESC_STATUS0_HBO_S,
	ICE_RX_FLEX_DESC_STATUS0_L3L4P_S,
	ICE_RX_FLEX_DESC_STATUS0_XSUM_IPE_S,
	ICE_RX_FLEX_DESC_STATUS0_XSUM_L4E_S,
	ICE_RX_FLEX_DESC_STATUS0_XSUM_EIPE_S,
	ICE_RX_FLEX_DESC_STATUS0_XSUM_EUDPE_S,
	ICE_RX_FLEX_DESC_STATUS0_LPBK_S,
	ICE_RX_FLEX_DESC_STATUS0_IPV6EXADD_S,
	ICE_RX_FLEX_DESC_STATUS0_RXE_S,
	ICE_RX_FLEX_DESC_STATUS0_CRCP_S,
	ICE_RX_FLEX_DESC_STATUS0_RSS_VALID_S,
	ICE_RX_FLEX_DESC_STATUS0_L2TAG1P_S,
	ICE_RX_FLEX_DESC_STATUS0_XTRMD0_VALID_S,
	ICE_RX_FLEX_DESC_STATUS0_XTRMD1_VALID_S,
	ICE_RX_FLEX_DESC_STATUS0_LAST /* this entry must be last!!! */
पूर्ण;

क्रमागत ice_rx_flex_desc_status_error_1_bits अणु
	/* Note: These are predefined bit offsets */
	ICE_RX_FLEX_DESC_STATUS1_NAT_S = 4,
	ICE_RX_FLEX_DESC_STATUS1_LAST /* this entry must be last!!! */
पूर्ण;

#घोषणा ICE_RXQ_CTX_SIZE_DWORDS		8
#घोषणा ICE_RXQ_CTX_SZ			(ICE_RXQ_CTX_SIZE_DWORDS * माप(u32))
#घोषणा ICE_TX_CMPLTNQ_CTX_SIZE_DWORDS	22
#घोषणा ICE_TX_DRBELL_Q_CTX_SIZE_DWORDS	5
#घोषणा GLTCLAN_CQ_CNTX(i, CQ)		(GLTCLAN_CQ_CNTX0(CQ) + ((i) * 0x0800))

/* RLAN Rx queue context data
 *
 * The sizes of the variables may be larger than needed due to crossing byte
 * boundaries. If we करो not have the width of the variable set to the correct
 * size then we could end up shअगरting bits off the top of the variable when the
 * variable is at the top of a byte and crosses over पूर्णांकo the next byte.
 */
काष्ठा ice_rlan_ctx अणु
	u16 head;
	u16 cpuid; /* bigger than needed, see above क्रम reason */
#घोषणा ICE_RLAN_BASE_S 7
	u64 base;
	u16 qlen;
#घोषणा ICE_RLAN_CTX_DBUF_S 7
	u16 dbuf; /* bigger than needed, see above क्रम reason */
#घोषणा ICE_RLAN_CTX_HBUF_S 6
	u16 hbuf; /* bigger than needed, see above क्रम reason */
	u8 dtype;
	u8 dsize;
	u8 crcstrip;
	u8 l2tsel;
	u8 hsplit_0;
	u8 hsplit_1;
	u8 showiv;
	u32 rxmax; /* bigger than needed, see above क्रम reason */
	u8 tphrdesc_ena;
	u8 tphwdesc_ena;
	u8 tphdata_ena;
	u8 tphhead_ena;
	u16 lrxqthresh; /* bigger than needed, see above क्रम reason */
	u8 prefena;	/* NOTE: normally must be set to 1 at init */
पूर्ण;

काष्ठा ice_ctx_ele अणु
	u16 offset;
	u16 size_of;
	u16 width;
	u16 lsb;
पूर्ण;

#घोषणा ICE_CTX_STORE(_काष्ठा, _ele, _width, _lsb) अणु	\
	.offset = दुरत्व(काष्ठा _काष्ठा, _ele),	\
	.size_of = माप_field(काष्ठा _काष्ठा, _ele),	\
	.width = _width,				\
	.lsb = _lsb,					\
पूर्ण

/* क्रम hsplit_0 field of Rx RLAN context */
क्रमागत ice_rlan_ctx_rx_hsplit_0 अणु
	ICE_RLAN_RX_HSPLIT_0_NO_SPLIT		= 0,
	ICE_RLAN_RX_HSPLIT_0_SPLIT_L2		= 1,
	ICE_RLAN_RX_HSPLIT_0_SPLIT_IP		= 2,
	ICE_RLAN_RX_HSPLIT_0_SPLIT_TCP_UDP	= 4,
	ICE_RLAN_RX_HSPLIT_0_SPLIT_SCTP		= 8,
पूर्ण;

/* क्रम hsplit_1 field of Rx RLAN context */
क्रमागत ice_rlan_ctx_rx_hsplit_1 अणु
	ICE_RLAN_RX_HSPLIT_1_NO_SPLIT		= 0,
	ICE_RLAN_RX_HSPLIT_1_SPLIT_L2		= 1,
	ICE_RLAN_RX_HSPLIT_1_SPLIT_ALWAYS	= 2,
पूर्ण;

/* Tx Descriptor */
काष्ठा ice_tx_desc अणु
	__le64 buf_addr; /* Address of descriptor's data buf */
	__le64 cmd_type_offset_bsz;
पूर्ण;

क्रमागत ice_tx_desc_dtype_value अणु
	ICE_TX_DESC_DTYPE_DATA		= 0x0,
	ICE_TX_DESC_DTYPE_CTX		= 0x1,
	ICE_TX_DESC_DTYPE_FLTR_PROG	= 0x8,
	/* DESC_DONE - HW has completed ग_लिखो-back of descriptor */
	ICE_TX_DESC_DTYPE_DESC_DONE	= 0xF,
पूर्ण;

#घोषणा ICE_TXD_QW1_CMD_S	4
#घोषणा ICE_TXD_QW1_CMD_M	(0xFFFUL << ICE_TXD_QW1_CMD_S)

क्रमागत ice_tx_desc_cmd_bits अणु
	ICE_TX_DESC_CMD_EOP			= 0x0001,
	ICE_TX_DESC_CMD_RS			= 0x0002,
	ICE_TX_DESC_CMD_IL2TAG1			= 0x0008,
	ICE_TX_DESC_CMD_DUMMY			= 0x0010,
	ICE_TX_DESC_CMD_IIPT_IPV6		= 0x0020,
	ICE_TX_DESC_CMD_IIPT_IPV4		= 0x0040,
	ICE_TX_DESC_CMD_IIPT_IPV4_CSUM		= 0x0060,
	ICE_TX_DESC_CMD_L4T_खातापूर्णT_TCP		= 0x0100,
	ICE_TX_DESC_CMD_L4T_खातापूर्णT_SCTP		= 0x0200,
	ICE_TX_DESC_CMD_L4T_खातापूर्णT_UDP		= 0x0300,
	ICE_TX_DESC_CMD_RE			= 0x0400,
पूर्ण;

#घोषणा ICE_TXD_QW1_OFFSET_S	16
#घोषणा ICE_TXD_QW1_OFFSET_M	(0x3FFFFULL << ICE_TXD_QW1_OFFSET_S)

क्रमागत ice_tx_desc_len_fields अणु
	/* Note: These are predefined bit offsets */
	ICE_TX_DESC_LEN_MACLEN_S	= 0, /* 7 BITS */
	ICE_TX_DESC_LEN_IPLEN_S	= 7, /* 7 BITS */
	ICE_TX_DESC_LEN_L4_LEN_S	= 14 /* 4 BITS */
पूर्ण;

#घोषणा ICE_TXD_QW1_MACLEN_M (0x7FUL << ICE_TX_DESC_LEN_MACLEN_S)
#घोषणा ICE_TXD_QW1_IPLEN_M  (0x7FUL << ICE_TX_DESC_LEN_IPLEN_S)
#घोषणा ICE_TXD_QW1_L4LEN_M  (0xFUL << ICE_TX_DESC_LEN_L4_LEN_S)

/* Tx descriptor field limits in bytes */
#घोषणा ICE_TXD_MACLEN_MAX ((ICE_TXD_QW1_MACLEN_M >> \
			     ICE_TX_DESC_LEN_MACLEN_S) * ICE_BYTES_PER_WORD)
#घोषणा ICE_TXD_IPLEN_MAX ((ICE_TXD_QW1_IPLEN_M >> \
			    ICE_TX_DESC_LEN_IPLEN_S) * ICE_BYTES_PER_DWORD)
#घोषणा ICE_TXD_L4LEN_MAX ((ICE_TXD_QW1_L4LEN_M >> \
			    ICE_TX_DESC_LEN_L4_LEN_S) * ICE_BYTES_PER_DWORD)

#घोषणा ICE_TXD_QW1_TX_BUF_SZ_S	34
#घोषणा ICE_TXD_QW1_L2TAG1_S	48

/* Context descriptors */
काष्ठा ice_tx_ctx_desc अणु
	__le32 tunneling_params;
	__le16 l2tag2;
	__le16 rsvd;
	__le64 qw1;
पूर्ण;

#घोषणा ICE_TXD_CTX_QW1_CMD_S	4
#घोषणा ICE_TXD_CTX_QW1_CMD_M	(0x7FUL << ICE_TXD_CTX_QW1_CMD_S)

#घोषणा ICE_TXD_CTX_QW1_TSO_LEN_S	30
#घोषणा ICE_TXD_CTX_QW1_TSO_LEN_M	\
			(0x3FFFFULL << ICE_TXD_CTX_QW1_TSO_LEN_S)

#घोषणा ICE_TXD_CTX_QW1_MSS_S	50

क्रमागत ice_tx_ctx_desc_cmd_bits अणु
	ICE_TX_CTX_DESC_TSO		= 0x01,
	ICE_TX_CTX_DESC_TSYN		= 0x02,
	ICE_TX_CTX_DESC_IL2TAG2		= 0x04,
	ICE_TX_CTX_DESC_IL2TAG2_IL2H	= 0x08,
	ICE_TX_CTX_DESC_SWTCH_NOTAG	= 0x00,
	ICE_TX_CTX_DESC_SWTCH_UPLINK	= 0x10,
	ICE_TX_CTX_DESC_SWTCH_LOCAL	= 0x20,
	ICE_TX_CTX_DESC_SWTCH_VSI	= 0x30,
	ICE_TX_CTX_DESC_RESERVED	= 0x40
पूर्ण;

क्रमागत ice_tx_ctx_desc_eipt_offload अणु
	ICE_TX_CTX_EIPT_NONE		= 0x0,
	ICE_TX_CTX_EIPT_IPV6		= 0x1,
	ICE_TX_CTX_EIPT_IPV4_NO_CSUM	= 0x2,
	ICE_TX_CTX_EIPT_IPV4		= 0x3
पूर्ण;

#घोषणा ICE_TXD_CTX_QW0_EIPLEN_S	2

#घोषणा ICE_TXD_CTX_QW0_L4TUNT_S	9

#घोषणा ICE_TXD_CTX_UDP_TUNNELING	BIT_ULL(ICE_TXD_CTX_QW0_L4TUNT_S)
#घोषणा ICE_TXD_CTX_GRE_TUNNELING	(0x2ULL << ICE_TXD_CTX_QW0_L4TUNT_S)

#घोषणा ICE_TXD_CTX_QW0_NATLEN_S	12

#घोषणा ICE_TXD_CTX_QW0_L4T_CS_S	23
#घोषणा ICE_TXD_CTX_QW0_L4T_CS_M	BIT_ULL(ICE_TXD_CTX_QW0_L4T_CS_S)

#घोषणा ICE_LAN_TXQ_MAX_QGRPS	127
#घोषणा ICE_LAN_TXQ_MAX_QDIS	1023

/* Tx queue context data
 *
 * The sizes of the variables may be larger than needed due to crossing byte
 * boundaries. If we करो not have the width of the variable set to the correct
 * size then we could end up shअगरting bits off the top of the variable when the
 * variable is at the top of a byte and crosses over पूर्णांकo the next byte.
 */
काष्ठा ice_tlan_ctx अणु
#घोषणा ICE_TLAN_CTX_BASE_S	7
	u64 base;		/* base is defined in 128-byte units */
	u8 port_num;
	u16 cgd_num;		/* bigger than needed, see above क्रम reason */
	u8 pf_num;
	u16 vmvf_num;
	u8 vmvf_type;
#घोषणा ICE_TLAN_CTX_VMVF_TYPE_VF	0
#घोषणा ICE_TLAN_CTX_VMVF_TYPE_VMQ	1
#घोषणा ICE_TLAN_CTX_VMVF_TYPE_PF	2
	u16 src_vsi;
	u8 tsyn_ena;
	u8 पूर्णांकernal_usage_flag;
	u8 alt_vlan;
	u16 cpuid;		/* bigger than needed, see above क्रम reason */
	u8 wb_mode;
	u8 tphrd_desc;
	u8 tphrd;
	u8 tphwr_desc;
	u16 cmpq_id;
	u16 qnum_in_func;
	u8 itr_notअगरication_mode;
	u8 adjust_prof_id;
	u32 qlen;		/* bigger than needed, see above क्रम reason */
	u8 quanta_prof_idx;
	u8 tso_ena;
	u16 tso_qnum;
	u8 legacy_पूर्णांक;
	u8 drop_ena;
	u8 cache_prof_idx;
	u8 pkt_shaper_prof_idx;
	u8 पूर्णांक_q_state;	/* width not needed - पूर्णांकernal - DO NOT WRITE!!! */
पूर्ण;

/* macro to make the table lines लघु */
#घोषणा ICE_PTT(PTYPE, OUTER_IP, OUTER_IP_VER, OUTER_FRAG, T, TE, TEF, I, PL)\
	अणु	PTYPE, \
		1, \
		ICE_RX_PTYPE_OUTER_##OUTER_IP, \
		ICE_RX_PTYPE_OUTER_##OUTER_IP_VER, \
		ICE_RX_PTYPE_##OUTER_FRAG, \
		ICE_RX_PTYPE_TUNNEL_##T, \
		ICE_RX_PTYPE_TUNNEL_END_##TE, \
		ICE_RX_PTYPE_##TEF, \
		ICE_RX_PTYPE_INNER_PROT_##I, \
		ICE_RX_PTYPE_PAYLOAD_LAYER_##PL पूर्ण

#घोषणा ICE_PTT_UNUSED_ENTRY(PTYPE) अणु PTYPE, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण

/* लघुer macros makes the table fit but are terse */
#घोषणा ICE_RX_PTYPE_NOF		ICE_RX_PTYPE_NOT_FRAG
#घोषणा ICE_RX_PTYPE_FRG		ICE_RX_PTYPE_FRAG

/* Lookup table mapping the HW PTYPE to the bit field क्रम decoding */
अटल स्थिर काष्ठा ice_rx_ptype_decoded ice_ptype_lkup[] = अणु
	/* L2 Packet types */
	ICE_PTT_UNUSED_ENTRY(0),
	ICE_PTT(1, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	ICE_PTT(2, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	ICE_PTT_UNUSED_ENTRY(3),
	ICE_PTT_UNUSED_ENTRY(4),
	ICE_PTT_UNUSED_ENTRY(5),
	ICE_PTT(6, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	ICE_PTT(7, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	ICE_PTT_UNUSED_ENTRY(8),
	ICE_PTT_UNUSED_ENTRY(9),
	ICE_PTT(10, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	ICE_PTT(11, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	ICE_PTT_UNUSED_ENTRY(12),
	ICE_PTT_UNUSED_ENTRY(13),
	ICE_PTT_UNUSED_ENTRY(14),
	ICE_PTT_UNUSED_ENTRY(15),
	ICE_PTT_UNUSED_ENTRY(16),
	ICE_PTT_UNUSED_ENTRY(17),
	ICE_PTT_UNUSED_ENTRY(18),
	ICE_PTT_UNUSED_ENTRY(19),
	ICE_PTT_UNUSED_ENTRY(20),
	ICE_PTT_UNUSED_ENTRY(21),

	/* Non Tunneled IPv4 */
	ICE_PTT(22, IP, IPV4, FRG, NONE, NONE, NOF, NONE, PAY3),
	ICE_PTT(23, IP, IPV4, NOF, NONE, NONE, NOF, NONE, PAY3),
	ICE_PTT(24, IP, IPV4, NOF, NONE, NONE, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(25),
	ICE_PTT(26, IP, IPV4, NOF, NONE, NONE, NOF, TCP,  PAY4),
	ICE_PTT(27, IP, IPV4, NOF, NONE, NONE, NOF, SCTP, PAY4),
	ICE_PTT(28, IP, IPV4, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv4 --> IPv4 */
	ICE_PTT(29, IP, IPV4, NOF, IP_IP, IPV4, FRG, NONE, PAY3),
	ICE_PTT(30, IP, IPV4, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	ICE_PTT(31, IP, IPV4, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(32),
	ICE_PTT(33, IP, IPV4, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(34, IP, IPV4, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(35, IP, IPV4, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> IPv6 */
	ICE_PTT(36, IP, IPV4, NOF, IP_IP, IPV6, FRG, NONE, PAY3),
	ICE_PTT(37, IP, IPV4, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	ICE_PTT(38, IP, IPV4, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(39),
	ICE_PTT(40, IP, IPV4, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(41, IP, IPV4, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(42, IP, IPV4, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT */
	ICE_PTT(43, IP, IPV4, NOF, IP_GRENAT, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GRE/NAT --> IPv4 */
	ICE_PTT(44, IP, IPV4, NOF, IP_GRENAT, IPV4, FRG, NONE, PAY3),
	ICE_PTT(45, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, NONE, PAY3),
	ICE_PTT(46, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(47),
	ICE_PTT(48, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(49, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(50, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> IPv6 */
	ICE_PTT(51, IP, IPV4, NOF, IP_GRENAT, IPV6, FRG, NONE, PAY3),
	ICE_PTT(52, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, NONE, PAY3),
	ICE_PTT(53, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(54),
	ICE_PTT(55, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(56, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(57, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> MAC */
	ICE_PTT(58, IP, IPV4, NOF, IP_GRENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GRE/NAT --> MAC --> IPv4 */
	ICE_PTT(59, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, FRG, NONE, PAY3),
	ICE_PTT(60, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, NONE, PAY3),
	ICE_PTT(61, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(62),
	ICE_PTT(63, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(64, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(65, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT -> MAC --> IPv6 */
	ICE_PTT(66, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, FRG, NONE, PAY3),
	ICE_PTT(67, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, NONE, PAY3),
	ICE_PTT(68, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(69),
	ICE_PTT(70, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(71, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(72, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> MAC/VLAN */
	ICE_PTT(73, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, NONE, NOF, NONE, PAY3),

	/* IPv4 ---> GRE/NAT -> MAC/VLAN --> IPv4 */
	ICE_PTT(74, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, FRG, NONE, PAY3),
	ICE_PTT(75, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, NONE, PAY3),
	ICE_PTT(76, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(77),
	ICE_PTT(78, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(79, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(80, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, ICMP, PAY4),

	/* IPv4 -> GRE/NAT -> MAC/VLAN --> IPv6 */
	ICE_PTT(81, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, FRG, NONE, PAY3),
	ICE_PTT(82, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, NONE, PAY3),
	ICE_PTT(83, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(84),
	ICE_PTT(85, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(86, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(87, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, ICMP, PAY4),

	/* Non Tunneled IPv6 */
	ICE_PTT(88, IP, IPV6, FRG, NONE, NONE, NOF, NONE, PAY3),
	ICE_PTT(89, IP, IPV6, NOF, NONE, NONE, NOF, NONE, PAY3),
	ICE_PTT(90, IP, IPV6, NOF, NONE, NONE, NOF, UDP,  PAY3),
	ICE_PTT_UNUSED_ENTRY(91),
	ICE_PTT(92, IP, IPV6, NOF, NONE, NONE, NOF, TCP,  PAY4),
	ICE_PTT(93, IP, IPV6, NOF, NONE, NONE, NOF, SCTP, PAY4),
	ICE_PTT(94, IP, IPV6, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv6 --> IPv4 */
	ICE_PTT(95, IP, IPV6, NOF, IP_IP, IPV4, FRG, NONE, PAY3),
	ICE_PTT(96, IP, IPV6, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	ICE_PTT(97, IP, IPV6, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(98),
	ICE_PTT(99, IP, IPV6, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(100, IP, IPV6, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(101, IP, IPV6, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> IPv6 */
	ICE_PTT(102, IP, IPV6, NOF, IP_IP, IPV6, FRG, NONE, PAY3),
	ICE_PTT(103, IP, IPV6, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	ICE_PTT(104, IP, IPV6, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(105),
	ICE_PTT(106, IP, IPV6, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(107, IP, IPV6, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(108, IP, IPV6, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT */
	ICE_PTT(109, IP, IPV6, NOF, IP_GRENAT, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> IPv4 */
	ICE_PTT(110, IP, IPV6, NOF, IP_GRENAT, IPV4, FRG, NONE, PAY3),
	ICE_PTT(111, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, NONE, PAY3),
	ICE_PTT(112, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(113),
	ICE_PTT(114, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(115, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(116, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> IPv6 */
	ICE_PTT(117, IP, IPV6, NOF, IP_GRENAT, IPV6, FRG, NONE, PAY3),
	ICE_PTT(118, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, NONE, PAY3),
	ICE_PTT(119, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(120),
	ICE_PTT(121, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(122, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(123, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC */
	ICE_PTT(124, IP, IPV6, NOF, IP_GRENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> MAC -> IPv4 */
	ICE_PTT(125, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, FRG, NONE, PAY3),
	ICE_PTT(126, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, NONE, PAY3),
	ICE_PTT(127, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(128),
	ICE_PTT(129, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(130, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(131, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC -> IPv6 */
	ICE_PTT(132, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, FRG, NONE, PAY3),
	ICE_PTT(133, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, NONE, PAY3),
	ICE_PTT(134, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(135),
	ICE_PTT(136, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(137, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(138, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC/VLAN */
	ICE_PTT(139, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> MAC/VLAN --> IPv4 */
	ICE_PTT(140, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, FRG, NONE, PAY3),
	ICE_PTT(141, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, NONE, PAY3),
	ICE_PTT(142, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(143),
	ICE_PTT(144, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, TCP,  PAY4),
	ICE_PTT(145, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, SCTP, PAY4),
	ICE_PTT(146, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC/VLAN --> IPv6 */
	ICE_PTT(147, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, FRG, NONE, PAY3),
	ICE_PTT(148, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, NONE, PAY3),
	ICE_PTT(149, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, UDP,  PAY4),
	ICE_PTT_UNUSED_ENTRY(150),
	ICE_PTT(151, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, TCP,  PAY4),
	ICE_PTT(152, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, SCTP, PAY4),
	ICE_PTT(153, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, ICMP, PAY4),

	/* unused entries */
	ICE_PTT_UNUSED_ENTRY(154),
	ICE_PTT_UNUSED_ENTRY(155),
	ICE_PTT_UNUSED_ENTRY(156),
	ICE_PTT_UNUSED_ENTRY(157),
	ICE_PTT_UNUSED_ENTRY(158),
	ICE_PTT_UNUSED_ENTRY(159),

	ICE_PTT_UNUSED_ENTRY(160),
	ICE_PTT_UNUSED_ENTRY(161),
	ICE_PTT_UNUSED_ENTRY(162),
	ICE_PTT_UNUSED_ENTRY(163),
	ICE_PTT_UNUSED_ENTRY(164),
	ICE_PTT_UNUSED_ENTRY(165),
	ICE_PTT_UNUSED_ENTRY(166),
	ICE_PTT_UNUSED_ENTRY(167),
	ICE_PTT_UNUSED_ENTRY(168),
	ICE_PTT_UNUSED_ENTRY(169),

	ICE_PTT_UNUSED_ENTRY(170),
	ICE_PTT_UNUSED_ENTRY(171),
	ICE_PTT_UNUSED_ENTRY(172),
	ICE_PTT_UNUSED_ENTRY(173),
	ICE_PTT_UNUSED_ENTRY(174),
	ICE_PTT_UNUSED_ENTRY(175),
	ICE_PTT_UNUSED_ENTRY(176),
	ICE_PTT_UNUSED_ENTRY(177),
	ICE_PTT_UNUSED_ENTRY(178),
	ICE_PTT_UNUSED_ENTRY(179),

	ICE_PTT_UNUSED_ENTRY(180),
	ICE_PTT_UNUSED_ENTRY(181),
	ICE_PTT_UNUSED_ENTRY(182),
	ICE_PTT_UNUSED_ENTRY(183),
	ICE_PTT_UNUSED_ENTRY(184),
	ICE_PTT_UNUSED_ENTRY(185),
	ICE_PTT_UNUSED_ENTRY(186),
	ICE_PTT_UNUSED_ENTRY(187),
	ICE_PTT_UNUSED_ENTRY(188),
	ICE_PTT_UNUSED_ENTRY(189),

	ICE_PTT_UNUSED_ENTRY(190),
	ICE_PTT_UNUSED_ENTRY(191),
	ICE_PTT_UNUSED_ENTRY(192),
	ICE_PTT_UNUSED_ENTRY(193),
	ICE_PTT_UNUSED_ENTRY(194),
	ICE_PTT_UNUSED_ENTRY(195),
	ICE_PTT_UNUSED_ENTRY(196),
	ICE_PTT_UNUSED_ENTRY(197),
	ICE_PTT_UNUSED_ENTRY(198),
	ICE_PTT_UNUSED_ENTRY(199),

	ICE_PTT_UNUSED_ENTRY(200),
	ICE_PTT_UNUSED_ENTRY(201),
	ICE_PTT_UNUSED_ENTRY(202),
	ICE_PTT_UNUSED_ENTRY(203),
	ICE_PTT_UNUSED_ENTRY(204),
	ICE_PTT_UNUSED_ENTRY(205),
	ICE_PTT_UNUSED_ENTRY(206),
	ICE_PTT_UNUSED_ENTRY(207),
	ICE_PTT_UNUSED_ENTRY(208),
	ICE_PTT_UNUSED_ENTRY(209),

	ICE_PTT_UNUSED_ENTRY(210),
	ICE_PTT_UNUSED_ENTRY(211),
	ICE_PTT_UNUSED_ENTRY(212),
	ICE_PTT_UNUSED_ENTRY(213),
	ICE_PTT_UNUSED_ENTRY(214),
	ICE_PTT_UNUSED_ENTRY(215),
	ICE_PTT_UNUSED_ENTRY(216),
	ICE_PTT_UNUSED_ENTRY(217),
	ICE_PTT_UNUSED_ENTRY(218),
	ICE_PTT_UNUSED_ENTRY(219),

	ICE_PTT_UNUSED_ENTRY(220),
	ICE_PTT_UNUSED_ENTRY(221),
	ICE_PTT_UNUSED_ENTRY(222),
	ICE_PTT_UNUSED_ENTRY(223),
	ICE_PTT_UNUSED_ENTRY(224),
	ICE_PTT_UNUSED_ENTRY(225),
	ICE_PTT_UNUSED_ENTRY(226),
	ICE_PTT_UNUSED_ENTRY(227),
	ICE_PTT_UNUSED_ENTRY(228),
	ICE_PTT_UNUSED_ENTRY(229),

	ICE_PTT_UNUSED_ENTRY(230),
	ICE_PTT_UNUSED_ENTRY(231),
	ICE_PTT_UNUSED_ENTRY(232),
	ICE_PTT_UNUSED_ENTRY(233),
	ICE_PTT_UNUSED_ENTRY(234),
	ICE_PTT_UNUSED_ENTRY(235),
	ICE_PTT_UNUSED_ENTRY(236),
	ICE_PTT_UNUSED_ENTRY(237),
	ICE_PTT_UNUSED_ENTRY(238),
	ICE_PTT_UNUSED_ENTRY(239),

	ICE_PTT_UNUSED_ENTRY(240),
	ICE_PTT_UNUSED_ENTRY(241),
	ICE_PTT_UNUSED_ENTRY(242),
	ICE_PTT_UNUSED_ENTRY(243),
	ICE_PTT_UNUSED_ENTRY(244),
	ICE_PTT_UNUSED_ENTRY(245),
	ICE_PTT_UNUSED_ENTRY(246),
	ICE_PTT_UNUSED_ENTRY(247),
	ICE_PTT_UNUSED_ENTRY(248),
	ICE_PTT_UNUSED_ENTRY(249),

	ICE_PTT_UNUSED_ENTRY(250),
	ICE_PTT_UNUSED_ENTRY(251),
	ICE_PTT_UNUSED_ENTRY(252),
	ICE_PTT_UNUSED_ENTRY(253),
	ICE_PTT_UNUSED_ENTRY(254),
	ICE_PTT_UNUSED_ENTRY(255),
पूर्ण;

अटल अंतरभूत काष्ठा ice_rx_ptype_decoded ice_decode_rx_desc_ptype(u16 ptype)
अणु
	वापस ice_ptype_lkup[ptype];
पूर्ण

#घोषणा ICE_LINK_SPEED_UNKNOWN		0
#घोषणा ICE_LINK_SPEED_10MBPS		10
#घोषणा ICE_LINK_SPEED_100MBPS		100
#घोषणा ICE_LINK_SPEED_1000MBPS		1000
#घोषणा ICE_LINK_SPEED_2500MBPS		2500
#घोषणा ICE_LINK_SPEED_5000MBPS		5000
#घोषणा ICE_LINK_SPEED_10000MBPS	10000
#घोषणा ICE_LINK_SPEED_20000MBPS	20000
#घोषणा ICE_LINK_SPEED_25000MBPS	25000
#घोषणा ICE_LINK_SPEED_40000MBPS	40000
#घोषणा ICE_LINK_SPEED_50000MBPS	50000
#घोषणा ICE_LINK_SPEED_100000MBPS	100000

#पूर्ण_अगर /* _ICE_LAN_TX_RX_H_ */
