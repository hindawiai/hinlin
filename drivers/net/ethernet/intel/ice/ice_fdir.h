<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018-2020, Intel Corporation. */

#अगर_अघोषित _ICE_Fसूची_H_
#घोषणा _ICE_Fसूची_H_

#घोषणा ICE_Fसूची_TUN_PKT_OFF		50
#घोषणा ICE_Fसूची_MAX_RAW_PKT_SIZE	(512 + ICE_Fसूची_TUN_PKT_OFF)

/* macros क्रम offsets पूर्णांकo packets क्रम flow director programming */
#घोषणा ICE_IPV4_SRC_ADDR_OFFSET	26
#घोषणा ICE_IPV4_DST_ADDR_OFFSET	30
#घोषणा ICE_IPV4_TCP_SRC_PORT_OFFSET	34
#घोषणा ICE_IPV4_TCP_DST_PORT_OFFSET	36
#घोषणा ICE_IPV4_UDP_SRC_PORT_OFFSET	34
#घोषणा ICE_IPV4_UDP_DST_PORT_OFFSET	36
#घोषणा ICE_IPV4_SCTP_SRC_PORT_OFFSET	34
#घोषणा ICE_IPV4_SCTP_DST_PORT_OFFSET	36
#घोषणा ICE_IPV4_PROTO_OFFSET		23
#घोषणा ICE_IPV6_SRC_ADDR_OFFSET	22
#घोषणा ICE_IPV6_DST_ADDR_OFFSET	38
#घोषणा ICE_IPV6_TCP_SRC_PORT_OFFSET	54
#घोषणा ICE_IPV6_TCP_DST_PORT_OFFSET	56
#घोषणा ICE_IPV6_UDP_SRC_PORT_OFFSET	54
#घोषणा ICE_IPV6_UDP_DST_PORT_OFFSET	56
#घोषणा ICE_IPV6_SCTP_SRC_PORT_OFFSET	54
#घोषणा ICE_IPV6_SCTP_DST_PORT_OFFSET	56
#घोषणा ICE_MAC_ETHTYPE_OFFSET		12
#घोषणा ICE_IPV4_TOS_OFFSET		15
#घोषणा ICE_IPV4_TTL_OFFSET		22
#घोषणा ICE_IPV6_TC_OFFSET		14
#घोषणा ICE_IPV6_HLIM_OFFSET		21
#घोषणा ICE_IPV6_PROTO_OFFSET		20
#घोषणा ICE_IPV4_GTPU_TEID_OFFSET	46
#घोषणा ICE_IPV4_GTPU_QFI_OFFSET	56
#घोषणा ICE_IPV4_L2TPV3_SESS_ID_OFFSET	34
#घोषणा ICE_IPV6_L2TPV3_SESS_ID_OFFSET	54
#घोषणा ICE_IPV4_ESP_SPI_OFFSET		34
#घोषणा ICE_IPV6_ESP_SPI_OFFSET		54
#घोषणा ICE_IPV4_AH_SPI_OFFSET		38
#घोषणा ICE_IPV6_AH_SPI_OFFSET		58
#घोषणा ICE_IPV4_NAT_T_ESP_SPI_OFFSET	42
#घोषणा ICE_IPV6_NAT_T_ESP_SPI_OFFSET	62

#घोषणा ICE_Fसूची_MAX_FLTRS		16384

/* IP v4 has 2 flag bits that enable fragment processing: DF and MF. DF
 * requests that the packet not be fragmented. MF indicates that a packet has
 * been fragmented.
 */
#घोषणा ICE_Fसूची_IPV4_PKT_FLAG_DF		0x20

क्रमागत ice_fltr_prgm_desc_dest अणु
	ICE_FLTR_PRGM_DESC_DEST_DROP_PKT,
	ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_QINDEX,
	ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_QGROUP,
	ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_OTHER,
पूर्ण;

क्रमागत ice_fltr_prgm_desc_fd_status अणु
	ICE_FLTR_PRGM_DESC_FD_STATUS_NONE,
	ICE_FLTR_PRGM_DESC_FD_STATUS_FD_ID,
पूर्ण;

/* Flow Director (FD) Filter Programming descriptor */
काष्ठा ice_fd_fltr_desc_ctx अणु
	u32 fdid;
	u16 qindex;
	u16 cnt_index;
	u16 fd_vsi;
	u16 flex_val;
	u8 comp_q;
	u8 comp_report;
	u8 fd_space;
	u8 cnt_ena;
	u8 evict_ena;
	u8 toq;
	u8 toq_prio;
	u8 dpu_recipe;
	u8 drop;
	u8 flex_prio;
	u8 flex_mdid;
	u8 dtype;
	u8 pcmd;
	u8 desc_prof_prio;
	u8 desc_prof;
	u8 swap;
	u8 fdid_prio;
	u8 fdid_mdid;
पूर्ण;

#घोषणा ICE_FLTR_PRGM_FLEX_WORD_SIZE	माप(__be16)

काष्ठा ice_rx_flow_userdef अणु
	u16 flex_word;
	u16 flex_offset;
	u16 flex_fltr;
पूर्ण;

काष्ठा ice_fdir_v4 अणु
	__be32 dst_ip;
	__be32 src_ip;
	__be16 dst_port;
	__be16 src_port;
	__be32 l4_header;
	__be32 sec_parm_idx;	/* security parameter index */
	u8 tos;
	u8 ip_ver;
	u8 proto;
	u8 ttl;
पूर्ण;

#घोषणा ICE_IPV6_ADDR_LEN_AS_U32		4

काष्ठा ice_fdir_v6 अणु
	__be32 dst_ip[ICE_IPV6_ADDR_LEN_AS_U32];
	__be32 src_ip[ICE_IPV6_ADDR_LEN_AS_U32];
	__be16 dst_port;
	__be16 src_port;
	__be32 l4_header; /* next header */
	__be32 sec_parm_idx; /* security parameter index */
	u8 tc;
	u8 proto;
	u8 hlim;
पूर्ण;

काष्ठा ice_fdir_udp_gtp अणु
	u8 flags;
	u8 msg_type;
	__be16 rsrvd_len;
	__be32 teid;
	__be16 rsrvd_seq_nbr;
	u8 rsrvd_n_pdu_nbr;
	u8 rsrvd_next_ext_type;
	u8 rsvrd_ext_len;
	u8	pdu_type:4,
		spare:4;
	u8	ppp:1,
		rqi:1,
		qfi:6;
	u32 rsvrd;
	u8 next_ext;
पूर्ण;

काष्ठा ice_fdir_l2tpv3 अणु
	__be32 session_id;
पूर्ण;

काष्ठा ice_fdir_extra अणु
	u8 dst_mac[ETH_ALEN];	/* dest MAC address */
	u8 src_mac[ETH_ALEN];	/* src MAC address */
	__be16 ether_type;	/* क्रम NON_IP_L2 */
	u32 usr_def[2];		/* user data */
	__be16 vlan_type;	/* VLAN ethertype */
	__be16 vlan_tag;	/* VLAN tag info */
पूर्ण;

काष्ठा ice_fdir_fltr अणु
	काष्ठा list_head fltr_node;
	क्रमागत ice_fltr_ptype flow_type;

	जोड़ अणु
		काष्ठा ice_fdir_v4 v4;
		काष्ठा ice_fdir_v6 v6;
	पूर्ण ip, mask;

	काष्ठा ice_fdir_udp_gtp gtpu_data;
	काष्ठा ice_fdir_udp_gtp gtpu_mask;

	काष्ठा ice_fdir_l2tpv3 l2tpv3_data;
	काष्ठा ice_fdir_l2tpv3 l2tpv3_mask;

	काष्ठा ice_fdir_extra ext_data;
	काष्ठा ice_fdir_extra ext_mask;

	/* flex byte filter data */
	__be16 flex_word;
	/* queue region size (=2^q_region) */
	u8 q_region;
	u16 flex_offset;
	u16 flex_fltr;

	/* filter control */
	u16 q_index;
	u16 dest_vsi;
	u8 dest_ctl;
	u8 cnt_ena;
	u8 fltr_status;
	u16 cnt_index;
	u32 fltr_id;
	u8 fdid_prio;
	u8 comp_report;
पूर्ण;

/* Dummy packet filter definition काष्ठाure */
काष्ठा ice_fdir_base_pkt अणु
	क्रमागत ice_fltr_ptype flow;
	u16 pkt_len;
	स्थिर u8 *pkt;
	u16 tun_pkt_len;
	स्थिर u8 *tun_pkt;
पूर्ण;

क्रमागत ice_status ice_alloc_fd_res_cntr(काष्ठा ice_hw *hw, u16 *cntr_id);
क्रमागत ice_status ice_मुक्त_fd_res_cntr(काष्ठा ice_hw *hw, u16 cntr_id);
क्रमागत ice_status
ice_alloc_fd_guar_item(काष्ठा ice_hw *hw, u16 *cntr_id, u16 num_fltr);
क्रमागत ice_status
ice_alloc_fd_shrd_item(काष्ठा ice_hw *hw, u16 *cntr_id, u16 num_fltr);
व्योम
ice_fdir_get_prgm_desc(काष्ठा ice_hw *hw, काष्ठा ice_fdir_fltr *input,
		       काष्ठा ice_fltr_desc *fdesc, bool add);
क्रमागत ice_status
ice_fdir_get_gen_prgm_pkt(काष्ठा ice_hw *hw, काष्ठा ice_fdir_fltr *input,
			  u8 *pkt, bool frag, bool tun);
पूर्णांक ice_get_fdir_cnt_all(काष्ठा ice_hw *hw);
bool ice_fdir_is_dup_fltr(काष्ठा ice_hw *hw, काष्ठा ice_fdir_fltr *input);
bool ice_fdir_has_frag(क्रमागत ice_fltr_ptype flow);
काष्ठा ice_fdir_fltr *
ice_fdir_find_fltr_by_idx(काष्ठा ice_hw *hw, u32 fltr_idx);
व्योम
ice_fdir_update_cntrs(काष्ठा ice_hw *hw, क्रमागत ice_fltr_ptype flow, bool add);
व्योम ice_fdir_list_add_fltr(काष्ठा ice_hw *hw, काष्ठा ice_fdir_fltr *input);
#पूर्ण_अगर /* _ICE_Fसूची_H_ */
