<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2021, Intel Corporation. */

#अगर_अघोषित _IAVF_ADV_RSS_H_
#घोषणा _IAVF_ADV_RSS_H_

काष्ठा iavf_adapter;

/* State of advanced RSS configuration */
क्रमागत iavf_adv_rss_state_t अणु
	IAVF_ADV_RSS_ADD_REQUEST,	/* User requests to add RSS */
	IAVF_ADV_RSS_ADD_PENDING,	/* RSS pending add by the PF */
	IAVF_ADV_RSS_DEL_REQUEST,	/* Driver requests to delete RSS */
	IAVF_ADV_RSS_DEL_PENDING,	/* RSS pending delete by the PF */
	IAVF_ADV_RSS_ACTIVE,		/* RSS configuration is active */
पूर्ण;

क्रमागत iavf_adv_rss_flow_seg_hdr अणु
	IAVF_ADV_RSS_FLOW_SEG_HDR_NONE	= 0x00000000,
	IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4	= 0x00000001,
	IAVF_ADV_RSS_FLOW_SEG_HDR_IPV6	= 0x00000002,
	IAVF_ADV_RSS_FLOW_SEG_HDR_TCP	= 0x00000004,
	IAVF_ADV_RSS_FLOW_SEG_HDR_UDP	= 0x00000008,
	IAVF_ADV_RSS_FLOW_SEG_HDR_SCTP	= 0x00000010,
पूर्ण;

#घोषणा IAVF_ADV_RSS_FLOW_SEG_HDR_L3		\
	(IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4	|	\
	 IAVF_ADV_RSS_FLOW_SEG_HDR_IPV6)

#घोषणा IAVF_ADV_RSS_FLOW_SEG_HDR_L4		\
	(IAVF_ADV_RSS_FLOW_SEG_HDR_TCP |	\
	 IAVF_ADV_RSS_FLOW_SEG_HDR_UDP |	\
	 IAVF_ADV_RSS_FLOW_SEG_HDR_SCTP)

क्रमागत iavf_adv_rss_flow_field अणु
	/* L3 */
	IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV4_SA,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV4_DA,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV6_SA,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV6_DA,
	/* L4 */
	IAVF_ADV_RSS_FLOW_FIELD_IDX_TCP_SRC_PORT,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_TCP_DST_PORT,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_UDP_SRC_PORT,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_UDP_DST_PORT,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_SCTP_SRC_PORT,
	IAVF_ADV_RSS_FLOW_FIELD_IDX_SCTP_DST_PORT,

	/* The total number of क्रमागतs must not exceed 64 */
	IAVF_ADV_RSS_FLOW_FIELD_IDX_MAX
पूर्ण;

#घोषणा IAVF_ADV_RSS_HASH_INVALID	0
#घोषणा IAVF_ADV_RSS_HASH_FLD_IPV4_SA	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV4_SA)
#घोषणा IAVF_ADV_RSS_HASH_FLD_IPV6_SA	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV6_SA)
#घोषणा IAVF_ADV_RSS_HASH_FLD_IPV4_DA	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV4_DA)
#घोषणा IAVF_ADV_RSS_HASH_FLD_IPV6_DA	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_IPV6_DA)
#घोषणा IAVF_ADV_RSS_HASH_FLD_TCP_SRC_PORT	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_TCP_SRC_PORT)
#घोषणा IAVF_ADV_RSS_HASH_FLD_TCP_DST_PORT	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_TCP_DST_PORT)
#घोषणा IAVF_ADV_RSS_HASH_FLD_UDP_SRC_PORT	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_UDP_SRC_PORT)
#घोषणा IAVF_ADV_RSS_HASH_FLD_UDP_DST_PORT	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_UDP_DST_PORT)
#घोषणा IAVF_ADV_RSS_HASH_FLD_SCTP_SRC_PORT	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_SCTP_SRC_PORT)
#घोषणा IAVF_ADV_RSS_HASH_FLD_SCTP_DST_PORT	\
	BIT_ULL(IAVF_ADV_RSS_FLOW_FIELD_IDX_SCTP_DST_PORT)

/* bookkeeping of advanced RSS configuration */
काष्ठा iavf_adv_rss अणु
	क्रमागत iavf_adv_rss_state_t state;
	काष्ठा list_head list;

	u32 packet_hdrs;
	u64 hash_flds;

	काष्ठा virtchnl_rss_cfg cfg_msg;
पूर्ण;

पूर्णांक
iavf_fill_adv_rss_cfg_msg(काष्ठा virtchnl_rss_cfg *rss_cfg,
			  u32 packet_hdrs, u64 hash_flds);
काष्ठा iavf_adv_rss *
iavf_find_adv_rss_cfg_by_hdrs(काष्ठा iavf_adapter *adapter, u32 packet_hdrs);
व्योम
iavf_prपूर्णांक_adv_rss_cfg(काष्ठा iavf_adapter *adapter, काष्ठा iavf_adv_rss *rss,
		       स्थिर अक्षर *action, स्थिर अक्षर *result);
#पूर्ण_अगर /* _IAVF_ADV_RSS_H_ */
