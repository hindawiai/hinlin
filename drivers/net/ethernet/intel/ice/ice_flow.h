<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_FLOW_H_
#घोषणा _ICE_FLOW_H_

#घोषणा ICE_FLOW_ENTRY_HANDLE_INVAL	0
#घोषणा ICE_FLOW_FLD_OFF_INVAL		0xffff

/* Generate flow hash field from flow field type(s) */
#घोषणा ICE_FLOW_HASH_ETH	\
	(BIT_ULL(ICE_FLOW_FIELD_IDX_ETH_DA) | \
	 BIT_ULL(ICE_FLOW_FIELD_IDX_ETH_SA))
#घोषणा ICE_FLOW_HASH_IPV4	\
	(BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_SA) | \
	 BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_DA))
#घोषणा ICE_FLOW_HASH_IPV6	\
	(BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_SA) | \
	 BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_DA))
#घोषणा ICE_FLOW_HASH_TCP_PORT	\
	(BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_SRC_PORT) | \
	 BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_DST_PORT))
#घोषणा ICE_FLOW_HASH_UDP_PORT	\
	(BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_SRC_PORT) | \
	 BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_DST_PORT))
#घोषणा ICE_FLOW_HASH_SCTP_PORT	\
	(BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT) | \
	 BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_DST_PORT))

#घोषणा ICE_HASH_INVALID	0
#घोषणा ICE_HASH_TCP_IPV4	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_TCP_PORT)
#घोषणा ICE_HASH_TCP_IPV6	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_TCP_PORT)
#घोषणा ICE_HASH_UDP_IPV4	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_UDP_PORT)
#घोषणा ICE_HASH_UDP_IPV6	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_UDP_PORT)

#घोषणा ICE_FLOW_HASH_GTP_TEID \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_GTPC_TEID))

#घोषणा ICE_FLOW_HASH_GTP_IPV4_TEID \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_GTP_TEID)
#घोषणा ICE_FLOW_HASH_GTP_IPV6_TEID \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_GTP_TEID)

#घोषणा ICE_FLOW_HASH_GTP_U_TEID \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_GTPU_IP_TEID))

#घोषणा ICE_FLOW_HASH_GTP_U_IPV4_TEID \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_GTP_U_TEID)
#घोषणा ICE_FLOW_HASH_GTP_U_IPV6_TEID \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_GTP_U_TEID)

#घोषणा ICE_FLOW_HASH_GTP_U_EH_TEID \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_GTPU_EH_TEID))

#घोषणा ICE_FLOW_HASH_GTP_U_EH_QFI \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_GTPU_EH_QFI))

#घोषणा ICE_FLOW_HASH_GTP_U_IPV4_EH \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_GTP_U_EH_TEID | \
	 ICE_FLOW_HASH_GTP_U_EH_QFI)
#घोषणा ICE_FLOW_HASH_GTP_U_IPV6_EH \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_GTP_U_EH_TEID | \
	 ICE_FLOW_HASH_GTP_U_EH_QFI)

#घोषणा ICE_FLOW_HASH_PPPOE_SESS_ID \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_PPPOE_SESS_ID))

#घोषणा ICE_FLOW_HASH_PPPOE_SESS_ID_ETH \
	(ICE_FLOW_HASH_ETH | ICE_FLOW_HASH_PPPOE_SESS_ID)
#घोषणा ICE_FLOW_HASH_PPPOE_TCP_ID \
	(ICE_FLOW_HASH_TCP_PORT | ICE_FLOW_HASH_PPPOE_SESS_ID)
#घोषणा ICE_FLOW_HASH_PPPOE_UDP_ID \
	(ICE_FLOW_HASH_UDP_PORT | ICE_FLOW_HASH_PPPOE_SESS_ID)

#घोषणा ICE_FLOW_HASH_PFCP_SEID \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_PFCP_SEID))
#घोषणा ICE_FLOW_HASH_PFCP_IPV4_SEID \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_PFCP_SEID)
#घोषणा ICE_FLOW_HASH_PFCP_IPV6_SEID \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_PFCP_SEID)

#घोषणा ICE_FLOW_HASH_L2TPV3_SESS_ID \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_L2TPV3_SESS_ID))
#घोषणा ICE_FLOW_HASH_L2TPV3_IPV4_SESS_ID \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_L2TPV3_SESS_ID)
#घोषणा ICE_FLOW_HASH_L2TPV3_IPV6_SESS_ID \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_L2TPV3_SESS_ID)

#घोषणा ICE_FLOW_HASH_ESP_SPI \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_ESP_SPI))
#घोषणा ICE_FLOW_HASH_ESP_IPV4_SPI \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_ESP_SPI)
#घोषणा ICE_FLOW_HASH_ESP_IPV6_SPI \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_ESP_SPI)

#घोषणा ICE_FLOW_HASH_AH_SPI \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_AH_SPI))
#घोषणा ICE_FLOW_HASH_AH_IPV4_SPI \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_AH_SPI)
#घोषणा ICE_FLOW_HASH_AH_IPV6_SPI \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_AH_SPI)

#घोषणा ICE_FLOW_HASH_NAT_T_ESP_SPI \
	(BIT_ULL(ICE_FLOW_FIELD_IDX_NAT_T_ESP_SPI))
#घोषणा ICE_FLOW_HASH_NAT_T_ESP_IPV4_SPI \
	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_NAT_T_ESP_SPI)
#घोषणा ICE_FLOW_HASH_NAT_T_ESP_IPV6_SPI \
	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_NAT_T_ESP_SPI)

/* Protocol header fields within a packet segment. A segment consists of one or
 * more protocol headers that make up a logical group of protocol headers. Each
 * logical group of protocol headers encapsulates or is encapsulated using/by
 * tunneling or encapsulation protocols क्रम network भवization such as GRE,
 * VxLAN, etc.
 */
क्रमागत ice_flow_seg_hdr अणु
	ICE_FLOW_SEG_HDR_NONE		= 0x00000000,
	ICE_FLOW_SEG_HDR_ETH		= 0x00000001,
	ICE_FLOW_SEG_HDR_VLAN		= 0x00000002,
	ICE_FLOW_SEG_HDR_IPV4		= 0x00000004,
	ICE_FLOW_SEG_HDR_IPV6		= 0x00000008,
	ICE_FLOW_SEG_HDR_ARP		= 0x00000010,
	ICE_FLOW_SEG_HDR_ICMP		= 0x00000020,
	ICE_FLOW_SEG_HDR_TCP		= 0x00000040,
	ICE_FLOW_SEG_HDR_UDP		= 0x00000080,
	ICE_FLOW_SEG_HDR_SCTP		= 0x00000100,
	ICE_FLOW_SEG_HDR_GRE		= 0x00000200,
	ICE_FLOW_SEG_HDR_GTPC		= 0x00000400,
	ICE_FLOW_SEG_HDR_GTPC_TEID	= 0x00000800,
	ICE_FLOW_SEG_HDR_GTPU_IP	= 0x00001000,
	ICE_FLOW_SEG_HDR_GTPU_EH	= 0x00002000,
	ICE_FLOW_SEG_HDR_GTPU_DWN	= 0x00004000,
	ICE_FLOW_SEG_HDR_GTPU_UP	= 0x00008000,
	ICE_FLOW_SEG_HDR_PPPOE		= 0x00010000,
	ICE_FLOW_SEG_HDR_PFCP_NODE	= 0x00020000,
	ICE_FLOW_SEG_HDR_PFCP_SESSION	= 0x00040000,
	ICE_FLOW_SEG_HDR_L2TPV3		= 0x00080000,
	ICE_FLOW_SEG_HDR_ESP		= 0x00100000,
	ICE_FLOW_SEG_HDR_AH		= 0x00200000,
	ICE_FLOW_SEG_HDR_NAT_T_ESP	= 0x00400000,
	ICE_FLOW_SEG_HDR_ETH_NON_IP	= 0x00800000,
	/* The following is an additive bit क्रम ICE_FLOW_SEG_HDR_IPV4 and
	 * ICE_FLOW_SEG_HDR_IPV6 which include the IPV4 other PTYPEs
	 */
	ICE_FLOW_SEG_HDR_IPV_OTHER      = 0x20000000,
पूर्ण;

/* These segments all have the same PTYPES, but are otherwise distinguished by
 * the value of the gtp_eh_pdu and gtp_eh_pdu_link flags:
 *
 *                                gtp_eh_pdu     gtp_eh_pdu_link
 * ICE_FLOW_SEG_HDR_GTPU_IP           0              0
 * ICE_FLOW_SEG_HDR_GTPU_EH           1              करोn't care
 * ICE_FLOW_SEG_HDR_GTPU_DWN          1              0
 * ICE_FLOW_SEG_HDR_GTPU_UP           1              1
 */
#घोषणा ICE_FLOW_SEG_HDR_GTPU (ICE_FLOW_SEG_HDR_GTPU_IP | \
			       ICE_FLOW_SEG_HDR_GTPU_EH | \
			       ICE_FLOW_SEG_HDR_GTPU_DWN | \
			       ICE_FLOW_SEG_HDR_GTPU_UP)
#घोषणा ICE_FLOW_SEG_HDR_PFCP (ICE_FLOW_SEG_HDR_PFCP_NODE | \
			       ICE_FLOW_SEG_HDR_PFCP_SESSION)

क्रमागत ice_flow_field अणु
	/* L2 */
	ICE_FLOW_FIELD_IDX_ETH_DA,
	ICE_FLOW_FIELD_IDX_ETH_SA,
	ICE_FLOW_FIELD_IDX_S_VLAN,
	ICE_FLOW_FIELD_IDX_C_VLAN,
	ICE_FLOW_FIELD_IDX_ETH_TYPE,
	/* L3 */
	ICE_FLOW_FIELD_IDX_IPV4_DSCP,
	ICE_FLOW_FIELD_IDX_IPV6_DSCP,
	ICE_FLOW_FIELD_IDX_IPV4_TTL,
	ICE_FLOW_FIELD_IDX_IPV4_PROT,
	ICE_FLOW_FIELD_IDX_IPV6_TTL,
	ICE_FLOW_FIELD_IDX_IPV6_PROT,
	ICE_FLOW_FIELD_IDX_IPV4_SA,
	ICE_FLOW_FIELD_IDX_IPV4_DA,
	ICE_FLOW_FIELD_IDX_IPV6_SA,
	ICE_FLOW_FIELD_IDX_IPV6_DA,
	/* L4 */
	ICE_FLOW_FIELD_IDX_TCP_SRC_PORT,
	ICE_FLOW_FIELD_IDX_TCP_DST_PORT,
	ICE_FLOW_FIELD_IDX_UDP_SRC_PORT,
	ICE_FLOW_FIELD_IDX_UDP_DST_PORT,
	ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT,
	ICE_FLOW_FIELD_IDX_SCTP_DST_PORT,
	ICE_FLOW_FIELD_IDX_TCP_FLAGS,
	/* ARP */
	ICE_FLOW_FIELD_IDX_ARP_SIP,
	ICE_FLOW_FIELD_IDX_ARP_DIP,
	ICE_FLOW_FIELD_IDX_ARP_SHA,
	ICE_FLOW_FIELD_IDX_ARP_DHA,
	ICE_FLOW_FIELD_IDX_ARP_OP,
	/* ICMP */
	ICE_FLOW_FIELD_IDX_ICMP_TYPE,
	ICE_FLOW_FIELD_IDX_ICMP_CODE,
	/* GRE */
	ICE_FLOW_FIELD_IDX_GRE_KEYID,
	/* GTPC_TEID */
	ICE_FLOW_FIELD_IDX_GTPC_TEID,
	/* GTPU_IP */
	ICE_FLOW_FIELD_IDX_GTPU_IP_TEID,
	/* GTPU_EH */
	ICE_FLOW_FIELD_IDX_GTPU_EH_TEID,
	ICE_FLOW_FIELD_IDX_GTPU_EH_QFI,
	/* GTPU_UP */
	ICE_FLOW_FIELD_IDX_GTPU_UP_TEID,
	/* GTPU_DWN */
	ICE_FLOW_FIELD_IDX_GTPU_DWN_TEID,
	/* PPPoE */
	ICE_FLOW_FIELD_IDX_PPPOE_SESS_ID,
	/* PFCP */
	ICE_FLOW_FIELD_IDX_PFCP_SEID,
	/* L2TPv3 */
	ICE_FLOW_FIELD_IDX_L2TPV3_SESS_ID,
	/* ESP */
	ICE_FLOW_FIELD_IDX_ESP_SPI,
	/* AH */
	ICE_FLOW_FIELD_IDX_AH_SPI,
	/* NAT_T ESP */
	ICE_FLOW_FIELD_IDX_NAT_T_ESP_SPI,
	 /* The total number of क्रमागतs must not exceed 64 */
	ICE_FLOW_FIELD_IDX_MAX
पूर्ण;

/* Flow headers and fields क्रम AVF support */
क्रमागत ice_flow_avf_hdr_field अणु
	/* Values 0 - 28 are reserved क्रम future use */
	ICE_AVF_FLOW_FIELD_INVALID		= 0,
	ICE_AVF_FLOW_FIELD_UNICAST_IPV4_UDP	= 29,
	ICE_AVF_FLOW_FIELD_MULTICAST_IPV4_UDP,
	ICE_AVF_FLOW_FIELD_IPV4_UDP,
	ICE_AVF_FLOW_FIELD_IPV4_TCP_SYN_NO_ACK,
	ICE_AVF_FLOW_FIELD_IPV4_TCP,
	ICE_AVF_FLOW_FIELD_IPV4_SCTP,
	ICE_AVF_FLOW_FIELD_IPV4_OTHER,
	ICE_AVF_FLOW_FIELD_FRAG_IPV4,
	/* Values 37-38 are reserved */
	ICE_AVF_FLOW_FIELD_UNICAST_IPV6_UDP	= 39,
	ICE_AVF_FLOW_FIELD_MULTICAST_IPV6_UDP,
	ICE_AVF_FLOW_FIELD_IPV6_UDP,
	ICE_AVF_FLOW_FIELD_IPV6_TCP_SYN_NO_ACK,
	ICE_AVF_FLOW_FIELD_IPV6_TCP,
	ICE_AVF_FLOW_FIELD_IPV6_SCTP,
	ICE_AVF_FLOW_FIELD_IPV6_OTHER,
	ICE_AVF_FLOW_FIELD_FRAG_IPV6,
	ICE_AVF_FLOW_FIELD_RSVD47,
	ICE_AVF_FLOW_FIELD_FCOE_OX,
	ICE_AVF_FLOW_FIELD_FCOE_RX,
	ICE_AVF_FLOW_FIELD_FCOE_OTHER,
	/* Values 51-62 are reserved */
	ICE_AVF_FLOW_FIELD_L2_PAYLOAD		= 63,
	ICE_AVF_FLOW_FIELD_MAX
पूर्ण;

/* Supported RSS offloads  This macro is defined to support
 * VIRTCHNL_OP_GET_RSS_HENA_CAPS ops. PF driver sends the RSS hardware
 * capabilities to the caller of this ops.
 */
#घोषणा ICE_DEFAULT_RSS_HENA ( \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_SCTP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_TCP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_OTHER) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_FRAG_IPV4) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_TCP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_SCTP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_OTHER) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_FRAG_IPV6) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_TCP_SYN_NO_ACK) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_UNICAST_IPV4_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_MULTICAST_IPV4_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_TCP_SYN_NO_ACK) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_UNICAST_IPV6_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_MULTICAST_IPV6_UDP))

क्रमागत ice_flow_dir अणु
	ICE_FLOW_RX		= 0x02,
पूर्ण;

क्रमागत ice_flow_priority अणु
	ICE_FLOW_PRIO_LOW,
	ICE_FLOW_PRIO_NORMAL,
	ICE_FLOW_PRIO_HIGH
पूर्ण;

#घोषणा ICE_FLOW_SEG_MAX		2
#घोषणा ICE_FLOW_SEG_RAW_FLD_MAX	2
#घोषणा ICE_FLOW_FV_EXTRACT_SZ		2

#घोषणा ICE_FLOW_SET_HDRS(seg, val)	((seg)->hdrs |= (u32)(val))

काष्ठा ice_flow_seg_xtrct अणु
	u8 prot_id;	/* Protocol ID of extracted header field */
	u16 off;	/* Starting offset of the field in header in bytes */
	u8 idx;		/* Index of FV entry used */
	u8 disp;	/* Displacement of field in bits fr. FV entry's start */
	u16 mask;	/* Mask क्रम field */
पूर्ण;

क्रमागत ice_flow_fld_match_type अणु
	ICE_FLOW_FLD_TYPE_REG,		/* Value, mask */
	ICE_FLOW_FLD_TYPE_RANGE,	/* Value, mask, last (upper bound) */
	ICE_FLOW_FLD_TYPE_PREFIX,	/* IP address, prefix, size of prefix */
	ICE_FLOW_FLD_TYPE_SIZE,		/* Value, mask, size of match */
पूर्ण;

काष्ठा ice_flow_fld_loc अणु
	/* Describe offsets of field inक्रमmation relative to the beginning of
	 * input buffer provided when adding flow entries.
	 */
	u16 val;	/* Offset where the value is located */
	u16 mask;	/* Offset where the mask/prefix value is located */
	u16 last;	/* Length or offset where the upper value is located */
पूर्ण;

काष्ठा ice_flow_fld_info अणु
	क्रमागत ice_flow_fld_match_type type;
	/* Location where to retrieve data from an input buffer */
	काष्ठा ice_flow_fld_loc src;
	/* Location where to put the data पूर्णांकo the final entry buffer */
	काष्ठा ice_flow_fld_loc entry;
	काष्ठा ice_flow_seg_xtrct xtrct;
पूर्ण;

काष्ठा ice_flow_seg_fld_raw अणु
	काष्ठा ice_flow_fld_info info;
	u16 off;	/* Offset from the start of the segment */
पूर्ण;

काष्ठा ice_flow_seg_info अणु
	u32 hdrs;	/* Biपंचांगask indicating protocol headers present */
	u64 match;	/* Biपंचांगask indicating header fields to be matched */
	u64 range;	/* Biपंचांगask indicating header fields matched as ranges */

	काष्ठा ice_flow_fld_info fields[ICE_FLOW_FIELD_IDX_MAX];

	u8 raws_cnt;	/* Number of raw fields to be matched */
	काष्ठा ice_flow_seg_fld_raw raws[ICE_FLOW_SEG_RAW_FLD_MAX];
पूर्ण;

/* This काष्ठाure describes a flow entry, and is tracked only in this file */
काष्ठा ice_flow_entry अणु
	काष्ठा list_head l_entry;

	u64 id;
	काष्ठा ice_flow_prof *prof;
	/* Flow entry's content */
	व्योम *entry;
	क्रमागत ice_flow_priority priority;
	u16 vsi_handle;
	u16 entry_sz;
पूर्ण;

#घोषणा ICE_FLOW_ENTRY_HNDL(e)	((u64)(uपूर्णांकptr_t)e)
#घोषणा ICE_FLOW_ENTRY_PTR(h)	((काष्ठा ice_flow_entry *)(uपूर्णांकptr_t)(h))

काष्ठा ice_flow_prof अणु
	काष्ठा list_head l_entry;

	u64 id;
	क्रमागत ice_flow_dir dir;
	u8 segs_cnt;

	/* Keep track of flow entries associated with this flow profile */
	काष्ठा mutex entries_lock;
	काष्ठा list_head entries;

	काष्ठा ice_flow_seg_info segs[ICE_FLOW_SEG_MAX];

	/* software VSI handles referenced by this flow profile */
	DECLARE_BITMAP(vsis, ICE_MAX_VSI);
पूर्ण;

काष्ठा ice_rss_cfg अणु
	काष्ठा list_head l_entry;
	/* biपंचांगap of VSIs added to the RSS entry */
	DECLARE_BITMAP(vsis, ICE_MAX_VSI);
	u64 hashed_flds;
	u32 packet_hdr;
पूर्ण;

क्रमागत ice_status
ice_flow_add_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, क्रमागत ice_flow_dir dir,
		  u64 prof_id, काष्ठा ice_flow_seg_info *segs, u8 segs_cnt,
		  काष्ठा ice_flow_prof **prof);
क्रमागत ice_status
ice_flow_rem_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 prof_id);
क्रमागत ice_status
ice_flow_add_entry(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 prof_id,
		   u64 entry_id, u16 vsi, क्रमागत ice_flow_priority prio,
		   व्योम *data, u64 *entry_h);
क्रमागत ice_status
ice_flow_rem_entry(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 entry_h);
व्योम
ice_flow_set_fld(काष्ठा ice_flow_seg_info *seg, क्रमागत ice_flow_field fld,
		 u16 val_loc, u16 mask_loc, u16 last_loc, bool range);
व्योम
ice_flow_add_fld_raw(काष्ठा ice_flow_seg_info *seg, u16 off, u8 len,
		     u16 val_loc, u16 mask_loc);
व्योम ice_rem_vsi_rss_list(काष्ठा ice_hw *hw, u16 vsi_handle);
क्रमागत ice_status ice_replay_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle);
क्रमागत ice_status
ice_add_avf_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds);
क्रमागत ice_status ice_rem_vsi_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle);
क्रमागत ice_status
ice_add_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		u32 addl_hdrs);
क्रमागत ice_status
ice_rem_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		u32 addl_hdrs);
u64 ice_get_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u32 hdrs);
#पूर्ण_अगर /* _ICE_FLOW_H_ */
