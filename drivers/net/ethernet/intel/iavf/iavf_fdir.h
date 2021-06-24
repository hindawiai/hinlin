<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2021, Intel Corporation. */

#अगर_अघोषित _IAVF_Fसूची_H_
#घोषणा _IAVF_Fसूची_H_

काष्ठा iavf_adapter;

/* State of Flow Director filter */
क्रमागत iavf_fdir_fltr_state_t अणु
	IAVF_Fसूची_FLTR_ADD_REQUEST,	/* User requests to add filter */
	IAVF_Fसूची_FLTR_ADD_PENDING,	/* Filter pending add by the PF */
	IAVF_Fसूची_FLTR_DEL_REQUEST,	/* User requests to delete filter */
	IAVF_Fसूची_FLTR_DEL_PENDING,	/* Filter pending delete by the PF */
	IAVF_Fसूची_FLTR_ACTIVE,		/* Filter is active */
पूर्ण;

क्रमागत iavf_fdir_flow_type अणु
	/* NONE - used क्रम undef/error */
	IAVF_Fसूची_FLOW_NONE = 0,
	IAVF_Fसूची_FLOW_IPV4_TCP,
	IAVF_Fसूची_FLOW_IPV4_UDP,
	IAVF_Fसूची_FLOW_IPV4_SCTP,
	IAVF_Fसूची_FLOW_IPV4_AH,
	IAVF_Fसूची_FLOW_IPV4_ESP,
	IAVF_Fसूची_FLOW_IPV4_OTHER,
	IAVF_Fसूची_FLOW_IPV6_TCP,
	IAVF_Fसूची_FLOW_IPV6_UDP,
	IAVF_Fसूची_FLOW_IPV6_SCTP,
	IAVF_Fसूची_FLOW_IPV6_AH,
	IAVF_Fसूची_FLOW_IPV6_ESP,
	IAVF_Fसूची_FLOW_IPV6_OTHER,
	IAVF_Fसूची_FLOW_NON_IP_L2,
	/* MAX - this must be last and add anything new just above it */
	IAVF_Fसूची_FLOW_PTYPE_MAX,
पूर्ण;

/* Must not exceed the array element number of '__be32 data[2]' in the ethtool
 * 'struct ethtool_rx_flow_spec.m_ext.data[2]' to express the flex-byte (word).
 */
#घोषणा IAVF_FLEX_WORD_NUM	2

काष्ठा iavf_flex_word अणु
	u16 offset;
	u16 word;
पूर्ण;

काष्ठा iavf_ipv4_addrs अणु
	__be32 src_ip;
	__be32 dst_ip;
पूर्ण;

काष्ठा iavf_ipv6_addrs अणु
	काष्ठा in6_addr src_ip;
	काष्ठा in6_addr dst_ip;
पूर्ण;

काष्ठा iavf_fdir_eth अणु
	__be16 etype;
पूर्ण;

काष्ठा iavf_fdir_ip अणु
	जोड़ अणु
		काष्ठा iavf_ipv4_addrs v4_addrs;
		काष्ठा iavf_ipv6_addrs v6_addrs;
	पूर्ण;
	__be16 src_port;
	__be16 dst_port;
	__be32 l4_header;	/* first 4 bytes of the layer 4 header */
	__be32 spi;		/* security parameter index क्रम AH/ESP */
	जोड़ अणु
		u8 tos;
		u8 tclass;
	पूर्ण;
	u8 proto;
पूर्ण;

काष्ठा iavf_fdir_extra अणु
	u32 usr_def[IAVF_FLEX_WORD_NUM];
पूर्ण;

/* bookkeeping of Flow Director filters */
काष्ठा iavf_fdir_fltr अणु
	क्रमागत iavf_fdir_fltr_state_t state;
	काष्ठा list_head list;

	क्रमागत iavf_fdir_flow_type flow_type;

	काष्ठा iavf_fdir_eth eth_data;
	काष्ठा iavf_fdir_eth eth_mask;

	काष्ठा iavf_fdir_ip ip_data;
	काष्ठा iavf_fdir_ip ip_mask;

	काष्ठा iavf_fdir_extra ext_data;
	काष्ठा iavf_fdir_extra ext_mask;

	क्रमागत virtchnl_action action;

	/* flex byte filter data */
	u8 ip_ver; /* used to adjust the flex offset, 4 : IPv4, 6 : IPv6 */
	u8 flex_cnt;
	काष्ठा iavf_flex_word flex_words[IAVF_FLEX_WORD_NUM];

	u32 flow_id;

	u32 loc;	/* Rule location inside the flow table */
	u32 q_index;

	काष्ठा virtchnl_fdir_add vc_add_msg;
पूर्ण;

पूर्णांक iavf_fill_fdir_add_msg(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr);
व्योम iavf_prपूर्णांक_fdir_fltr(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr);
bool iavf_fdir_is_dup_fltr(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr);
व्योम iavf_fdir_list_add_fltr(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr);
काष्ठा iavf_fdir_fltr *iavf_find_fdir_fltr_by_loc(काष्ठा iavf_adapter *adapter, u32 loc);
#पूर्ण_अगर /* _IAVF_Fसूची_H_ */
