<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RSS and Classअगरier helpers क्रम Marvell PPv2 Network Controller
 *
 * Copyright (C) 2014 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 */

#समावेश "mvpp2.h"
#समावेश "mvpp2_cls.h"
#समावेश "mvpp2_prs.h"

#घोषणा MVPP2_DEF_FLOW(_type, _id, _opts, _ri, _ri_mask)	\
अणु								\
	.flow_type = _type,					\
	.flow_id = _id,						\
	.supported_hash_opts = _opts,				\
	.prs_ri = अणु						\
		.ri = _ri,					\
		.ri_mask = _ri_mask				\
	पूर्ण							\
पूर्ण

अटल स्थिर काष्ठा mvpp2_cls_flow cls_flows[MVPP2_N_PRS_FLOWS] = अणु
	/* TCP over IPv4 flows, Not fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP4_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4 |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP4_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OPT |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP4_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OTHER |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* TCP over IPv4 flows, Not fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_NF_TAG,
		       MVPP22_CLS_HEK_IP4_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4 | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_NF_TAG,
		       MVPP22_CLS_HEK_IP4_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OPT | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_NF_TAG,
		       MVPP22_CLS_HEK_IP4_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OTHER | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	/* TCP over IPv4 flows, fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4 |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OPT |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OTHER |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* TCP over IPv4 flows, fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4 | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OPT | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP4, MVPP2_FL_IP4_TCP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OTHER | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	/* UDP over IPv4 flows, Not fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP4_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4 |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP4_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OPT |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP4_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OTHER |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* UDP over IPv4 flows, Not fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_NF_TAG,
		       MVPP22_CLS_HEK_IP4_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4 | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_NF_TAG,
		       MVPP22_CLS_HEK_IP4_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OPT | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_NF_TAG,
		       MVPP22_CLS_HEK_IP4_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OTHER | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	/* UDP over IPv4 flows, fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4 |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OPT |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OTHER |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* UDP over IPv4 flows, fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4 | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OPT | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP4, MVPP2_FL_IP4_UDP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OTHER | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	/* TCP over IPv6 flows, not fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP6_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6 |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP6_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6_EXT |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* TCP over IPv6 flows, not fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_NF_TAG,
		       MVPP22_CLS_HEK_IP6_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6 | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_NF_TAG,
		       MVPP22_CLS_HEK_IP6_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6_EXT | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	/* TCP over IPv6 flows, fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP6_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6 |
		       MVPP2_PRS_RI_IP_FRAG_TRUE | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP6_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6_EXT |
		       MVPP2_PRS_RI_IP_FRAG_TRUE | MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* TCP over IPv6 flows, fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP6_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6 | MVPP2_PRS_RI_IP_FRAG_TRUE |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_TCP6, MVPP2_FL_IP6_TCP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP6_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6_EXT | MVPP2_PRS_RI_IP_FRAG_TRUE |
		       MVPP2_PRS_RI_L4_TCP,
		       MVPP2_PRS_IP_MASK),

	/* UDP over IPv6 flows, not fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP6_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6 |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_NF_UNTAG,
		       MVPP22_CLS_HEK_IP6_5T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6_EXT |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* UDP over IPv6 flows, not fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_NF_TAG,
		       MVPP22_CLS_HEK_IP6_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6 | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_NF_TAG,
		       MVPP22_CLS_HEK_IP6_5T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6_EXT | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	/* UDP over IPv6 flows, fragmented, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP6_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6 |
		       MVPP2_PRS_RI_IP_FRAG_TRUE | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_FRAG_UNTAG,
		       MVPP22_CLS_HEK_IP6_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6_EXT |
		       MVPP2_PRS_RI_IP_FRAG_TRUE | MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK | MVPP2_PRS_RI_VLAN_MASK),

	/* UDP over IPv6 flows, fragmented, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP6_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6 | MVPP2_PRS_RI_IP_FRAG_TRUE |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	MVPP2_DEF_FLOW(MVPP22_FLOW_UDP6, MVPP2_FL_IP6_UDP_FRAG_TAG,
		       MVPP22_CLS_HEK_IP6_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6_EXT | MVPP2_PRS_RI_IP_FRAG_TRUE |
		       MVPP2_PRS_RI_L4_UDP,
		       MVPP2_PRS_IP_MASK),

	/* IPv4 flows, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP4, MVPP2_FL_IP4_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4,
		       MVPP2_PRS_RI_VLAN_MASK | MVPP2_PRS_RI_L3_PROTO_MASK),
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP4, MVPP2_FL_IP4_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OPT,
		       MVPP2_PRS_RI_VLAN_MASK | MVPP2_PRS_RI_L3_PROTO_MASK),
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP4, MVPP2_FL_IP4_UNTAG,
		       MVPP22_CLS_HEK_IP4_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP4_OTHER,
		       MVPP2_PRS_RI_VLAN_MASK | MVPP2_PRS_RI_L3_PROTO_MASK),

	/* IPv4 flows, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP4, MVPP2_FL_IP4_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4,
		       MVPP2_PRS_RI_L3_PROTO_MASK),
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP4, MVPP2_FL_IP4_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OPT,
		       MVPP2_PRS_RI_L3_PROTO_MASK),
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP4, MVPP2_FL_IP4_TAG,
		       MVPP22_CLS_HEK_IP4_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP4_OTHER,
		       MVPP2_PRS_RI_L3_PROTO_MASK),

	/* IPv6 flows, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP6, MVPP2_FL_IP6_UNTAG,
		       MVPP22_CLS_HEK_IP6_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6,
		       MVPP2_PRS_RI_VLAN_MASK | MVPP2_PRS_RI_L3_PROTO_MASK),
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP6, MVPP2_FL_IP6_UNTAG,
		       MVPP22_CLS_HEK_IP6_2T,
		       MVPP2_PRS_RI_VLAN_NONE | MVPP2_PRS_RI_L3_IP6,
		       MVPP2_PRS_RI_VLAN_MASK | MVPP2_PRS_RI_L3_PROTO_MASK),

	/* IPv6 flows, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP6, MVPP2_FL_IP6_TAG,
		       MVPP22_CLS_HEK_IP6_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6,
		       MVPP2_PRS_RI_L3_PROTO_MASK),
	MVPP2_DEF_FLOW(MVPP22_FLOW_IP6, MVPP2_FL_IP6_TAG,
		       MVPP22_CLS_HEK_IP6_2T | MVPP22_CLS_HEK_TAGGED,
		       MVPP2_PRS_RI_L3_IP6,
		       MVPP2_PRS_RI_L3_PROTO_MASK),

	/* Non IP flow, no vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_ETHERNET, MVPP2_FL_NON_IP_UNTAG,
		       0,
		       MVPP2_PRS_RI_VLAN_NONE,
		       MVPP2_PRS_RI_VLAN_MASK),
	/* Non IP flow, with vlan tag */
	MVPP2_DEF_FLOW(MVPP22_FLOW_ETHERNET, MVPP2_FL_NON_IP_TAG,
		       MVPP22_CLS_HEK_OPT_VLAN,
		       0, 0),
पूर्ण;

u32 mvpp2_cls_flow_hits(काष्ठा mvpp2 *priv, पूर्णांक index)
अणु
	mvpp2_ग_लिखो(priv, MVPP2_CTRS_IDX, index);

	वापस mvpp2_पढ़ो(priv, MVPP2_CLS_FLOW_TBL_HIT_CTR);
पूर्ण

व्योम mvpp2_cls_flow_पढ़ो(काष्ठा mvpp2 *priv, पूर्णांक index,
			 काष्ठा mvpp2_cls_flow_entry *fe)
अणु
	fe->index = index;
	mvpp2_ग_लिखो(priv, MVPP2_CLS_FLOW_INDEX_REG, index);
	fe->data[0] = mvpp2_पढ़ो(priv, MVPP2_CLS_FLOW_TBL0_REG);
	fe->data[1] = mvpp2_पढ़ो(priv, MVPP2_CLS_FLOW_TBL1_REG);
	fe->data[2] = mvpp2_पढ़ो(priv, MVPP2_CLS_FLOW_TBL2_REG);
पूर्ण

/* Update classअगरication flow table रेजिस्टरs */
अटल व्योम mvpp2_cls_flow_ग_लिखो(काष्ठा mvpp2 *priv,
				 काष्ठा mvpp2_cls_flow_entry *fe)
अणु
	mvpp2_ग_लिखो(priv, MVPP2_CLS_FLOW_INDEX_REG, fe->index);
	mvpp2_ग_लिखो(priv, MVPP2_CLS_FLOW_TBL0_REG, fe->data[0]);
	mvpp2_ग_लिखो(priv, MVPP2_CLS_FLOW_TBL1_REG, fe->data[1]);
	mvpp2_ग_लिखो(priv, MVPP2_CLS_FLOW_TBL2_REG, fe->data[2]);
पूर्ण

u32 mvpp2_cls_lookup_hits(काष्ठा mvpp2 *priv, पूर्णांक index)
अणु
	mvpp2_ग_लिखो(priv, MVPP2_CTRS_IDX, index);

	वापस mvpp2_पढ़ो(priv, MVPP2_CLS_DEC_TBL_HIT_CTR);
पूर्ण

व्योम mvpp2_cls_lookup_पढ़ो(काष्ठा mvpp2 *priv, पूर्णांक lkpid, पूर्णांक way,
			   काष्ठा mvpp2_cls_lookup_entry *le)
अणु
	u32 val;

	val = (way << MVPP2_CLS_LKP_INDEX_WAY_OFFS) | lkpid;
	mvpp2_ग_लिखो(priv, MVPP2_CLS_LKP_INDEX_REG, val);
	le->way = way;
	le->lkpid = lkpid;
	le->data = mvpp2_पढ़ो(priv, MVPP2_CLS_LKP_TBL_REG);
पूर्ण

/* Update classअगरication lookup table रेजिस्टर */
अटल व्योम mvpp2_cls_lookup_ग_लिखो(काष्ठा mvpp2 *priv,
				   काष्ठा mvpp2_cls_lookup_entry *le)
अणु
	u32 val;

	val = (le->way << MVPP2_CLS_LKP_INDEX_WAY_OFFS) | le->lkpid;
	mvpp2_ग_लिखो(priv, MVPP2_CLS_LKP_INDEX_REG, val);
	mvpp2_ग_लिखो(priv, MVPP2_CLS_LKP_TBL_REG, le->data);
पूर्ण

/* Operations on flow entry */
अटल पूर्णांक mvpp2_cls_flow_hek_num_get(काष्ठा mvpp2_cls_flow_entry *fe)
अणु
	वापस fe->data[1] & MVPP2_CLS_FLOW_TBL1_N_FIELDS_MASK;
पूर्ण

अटल व्योम mvpp2_cls_flow_hek_num_set(काष्ठा mvpp2_cls_flow_entry *fe,
				       पूर्णांक num_of_fields)
अणु
	fe->data[1] &= ~MVPP2_CLS_FLOW_TBL1_N_FIELDS_MASK;
	fe->data[1] |= MVPP2_CLS_FLOW_TBL1_N_FIELDS(num_of_fields);
पूर्ण

अटल पूर्णांक mvpp2_cls_flow_hek_get(काष्ठा mvpp2_cls_flow_entry *fe,
				  पूर्णांक field_index)
अणु
	वापस (fe->data[2] >> MVPP2_CLS_FLOW_TBL2_FLD_OFFS(field_index)) &
		MVPP2_CLS_FLOW_TBL2_FLD_MASK;
पूर्ण

अटल व्योम mvpp2_cls_flow_hek_set(काष्ठा mvpp2_cls_flow_entry *fe,
				   पूर्णांक field_index, पूर्णांक field_id)
अणु
	fe->data[2] &= ~MVPP2_CLS_FLOW_TBL2_FLD(field_index,
						MVPP2_CLS_FLOW_TBL2_FLD_MASK);
	fe->data[2] |= MVPP2_CLS_FLOW_TBL2_FLD(field_index, field_id);
पूर्ण

अटल व्योम mvpp2_cls_flow_eng_set(काष्ठा mvpp2_cls_flow_entry *fe,
				   पूर्णांक engine)
अणु
	fe->data[0] &= ~MVPP2_CLS_FLOW_TBL0_ENG(MVPP2_CLS_FLOW_TBL0_ENG_MASK);
	fe->data[0] |= MVPP2_CLS_FLOW_TBL0_ENG(engine);
पूर्ण

पूर्णांक mvpp2_cls_flow_eng_get(काष्ठा mvpp2_cls_flow_entry *fe)
अणु
	वापस (fe->data[0] >> MVPP2_CLS_FLOW_TBL0_OFFS) &
		MVPP2_CLS_FLOW_TBL0_ENG_MASK;
पूर्ण

अटल व्योम mvpp2_cls_flow_port_id_sel(काष्ठा mvpp2_cls_flow_entry *fe,
				       bool from_packet)
अणु
	अगर (from_packet)
		fe->data[0] |= MVPP2_CLS_FLOW_TBL0_PORT_ID_SEL;
	अन्यथा
		fe->data[0] &= ~MVPP2_CLS_FLOW_TBL0_PORT_ID_SEL;
पूर्ण

अटल व्योम mvpp2_cls_flow_last_set(काष्ठा mvpp2_cls_flow_entry *fe,
				    bool is_last)
अणु
	fe->data[0] &= ~MVPP2_CLS_FLOW_TBL0_LAST;
	fe->data[0] |= !!is_last;
पूर्ण

अटल व्योम mvpp2_cls_flow_pri_set(काष्ठा mvpp2_cls_flow_entry *fe, पूर्णांक prio)
अणु
	fe->data[1] &= ~MVPP2_CLS_FLOW_TBL1_PRIO(MVPP2_CLS_FLOW_TBL1_PRIO_MASK);
	fe->data[1] |= MVPP2_CLS_FLOW_TBL1_PRIO(prio);
पूर्ण

अटल व्योम mvpp2_cls_flow_port_add(काष्ठा mvpp2_cls_flow_entry *fe,
				    u32 port)
अणु
	fe->data[0] |= MVPP2_CLS_FLOW_TBL0_PORT_ID(port);
पूर्ण

अटल व्योम mvpp2_cls_flow_port_हटाओ(काष्ठा mvpp2_cls_flow_entry *fe,
				       u32 port)
अणु
	fe->data[0] &= ~MVPP2_CLS_FLOW_TBL0_PORT_ID(port);
पूर्ण

अटल व्योम mvpp2_cls_flow_lu_type_set(काष्ठा mvpp2_cls_flow_entry *fe,
				       u8 lu_type)
अणु
	fe->data[1] &= ~MVPP2_CLS_FLOW_TBL1_LU_TYPE(MVPP2_CLS_LU_TYPE_MASK);
	fe->data[1] |= MVPP2_CLS_FLOW_TBL1_LU_TYPE(lu_type);
पूर्ण

/* Initialize the parser entry क्रम the given flow */
अटल व्योम mvpp2_cls_flow_prs_init(काष्ठा mvpp2 *priv,
				    स्थिर काष्ठा mvpp2_cls_flow *flow)
अणु
	mvpp2_prs_add_flow(priv, flow->flow_id, flow->prs_ri.ri,
			   flow->prs_ri.ri_mask);
पूर्ण

/* Initialize the Lookup Id table entry क्रम the given flow */
अटल व्योम mvpp2_cls_flow_lkp_init(काष्ठा mvpp2 *priv,
				    स्थिर काष्ठा mvpp2_cls_flow *flow)
अणु
	काष्ठा mvpp2_cls_lookup_entry le;

	le.way = 0;
	le.lkpid = flow->flow_id;

	/* The शेष RxQ क्रम this port is set in the C2 lookup */
	le.data = 0;

	/* We poपूर्णांक on the first lookup in the sequence क्रम the flow, that is
	 * the C2 lookup.
	 */
	le.data |= MVPP2_CLS_LKP_FLOW_PTR(MVPP2_CLS_FLT_FIRST(flow->flow_id));

	/* CLS is always enabled, RSS is enabled/disabled in C2 lookup */
	le.data |= MVPP2_CLS_LKP_TBL_LOOKUP_EN_MASK;

	mvpp2_cls_lookup_ग_लिखो(priv, &le);
पूर्ण

अटल व्योम mvpp2_cls_c2_ग_लिखो(काष्ठा mvpp2 *priv,
			       काष्ठा mvpp2_cls_c2_entry *c2)
अणु
	u32 val;
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_IDX, c2->index);

	val = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_INV);
	अगर (c2->valid)
		val &= ~MVPP22_CLS_C2_TCAM_INV_BIT;
	अन्यथा
		val |= MVPP22_CLS_C2_TCAM_INV_BIT;
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_INV, val);

	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_ACT, c2->act);

	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_ATTR0, c2->attr[0]);
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_ATTR1, c2->attr[1]);
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_ATTR2, c2->attr[2]);
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_ATTR3, c2->attr[3]);

	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_DATA0, c2->tcam[0]);
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_DATA1, c2->tcam[1]);
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_DATA2, c2->tcam[2]);
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_DATA3, c2->tcam[3]);
	/* Writing TCAM_DATA4 flushes ग_लिखोs to TCAM_DATA0-4 and INV to HW */
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_DATA4, c2->tcam[4]);
पूर्ण

व्योम mvpp2_cls_c2_पढ़ो(काष्ठा mvpp2 *priv, पूर्णांक index,
		       काष्ठा mvpp2_cls_c2_entry *c2)
अणु
	u32 val;
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_IDX, index);

	c2->index = index;

	c2->tcam[0] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_DATA0);
	c2->tcam[1] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_DATA1);
	c2->tcam[2] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_DATA2);
	c2->tcam[3] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_DATA3);
	c2->tcam[4] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_DATA4);

	c2->act = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_ACT);

	c2->attr[0] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_ATTR0);
	c2->attr[1] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_ATTR1);
	c2->attr[2] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_ATTR2);
	c2->attr[3] = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_ATTR3);

	val = mvpp2_पढ़ो(priv, MVPP22_CLS_C2_TCAM_INV);
	c2->valid = !(val & MVPP22_CLS_C2_TCAM_INV_BIT);
पूर्ण

अटल पूर्णांक mvpp2_cls_ethtool_flow_to_type(पूर्णांक flow_type)
अणु
	चयन (flow_type & ~(FLOW_EXT | FLOW_MAC_EXT | FLOW_RSS)) अणु
	हाल ETHER_FLOW:
		वापस MVPP22_FLOW_ETHERNET;
	हाल TCP_V4_FLOW:
		वापस MVPP22_FLOW_TCP4;
	हाल TCP_V6_FLOW:
		वापस MVPP22_FLOW_TCP6;
	हाल UDP_V4_FLOW:
		वापस MVPP22_FLOW_UDP4;
	हाल UDP_V6_FLOW:
		वापस MVPP22_FLOW_UDP6;
	हाल IPV4_FLOW:
		वापस MVPP22_FLOW_IP4;
	हाल IPV6_FLOW:
		वापस MVPP22_FLOW_IP6;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mvpp2_cls_c2_port_flow_index(काष्ठा mvpp2_port *port, पूर्णांक loc)
अणु
	वापस MVPP22_CLS_C2_RFS_LOC(port->id, loc);
पूर्ण

/* Initialize the flow table entries क्रम the given flow */
अटल व्योम mvpp2_cls_flow_init(काष्ठा mvpp2 *priv,
				स्थिर काष्ठा mvpp2_cls_flow *flow)
अणु
	काष्ठा mvpp2_cls_flow_entry fe;
	पूर्णांक i, pri = 0;

	/* Assign शेष values to all entries in the flow */
	क्रम (i = MVPP2_CLS_FLT_FIRST(flow->flow_id);
	     i <= MVPP2_CLS_FLT_LAST(flow->flow_id); i++) अणु
		स_रखो(&fe, 0, माप(fe));
		fe.index = i;
		mvpp2_cls_flow_pri_set(&fe, pri++);

		अगर (i == MVPP2_CLS_FLT_LAST(flow->flow_id))
			mvpp2_cls_flow_last_set(&fe, 1);

		mvpp2_cls_flow_ग_लिखो(priv, &fe);
	पूर्ण

	/* RSS config C2 lookup */
	mvpp2_cls_flow_पढ़ो(priv, MVPP2_CLS_FLT_C2_RSS_ENTRY(flow->flow_id),
			    &fe);

	mvpp2_cls_flow_eng_set(&fe, MVPP22_CLS_ENGINE_C2);
	mvpp2_cls_flow_port_id_sel(&fe, true);
	mvpp2_cls_flow_lu_type_set(&fe, MVPP22_CLS_LU_TYPE_ALL);

	/* Add all ports */
	क्रम (i = 0; i < MVPP2_MAX_PORTS; i++)
		mvpp2_cls_flow_port_add(&fe, BIT(i));

	mvpp2_cls_flow_ग_लिखो(priv, &fe);

	/* C3Hx lookups */
	क्रम (i = 0; i < MVPP2_MAX_PORTS; i++) अणु
		mvpp2_cls_flow_पढ़ो(priv,
				    MVPP2_CLS_FLT_HASH_ENTRY(i, flow->flow_id),
				    &fe);

		/* Set a शेष engine. Will be overwritten when setting the
		 * real HEK parameters
		 */
		mvpp2_cls_flow_eng_set(&fe, MVPP22_CLS_ENGINE_C3HA);
		mvpp2_cls_flow_port_id_sel(&fe, true);
		mvpp2_cls_flow_port_add(&fe, BIT(i));

		mvpp2_cls_flow_ग_लिखो(priv, &fe);
	पूर्ण
पूर्ण

/* Adds a field to the Header Extracted Key generation parameters*/
अटल पूर्णांक mvpp2_flow_add_hek_field(काष्ठा mvpp2_cls_flow_entry *fe,
				    u32 field_id)
अणु
	पूर्णांक nb_fields = mvpp2_cls_flow_hek_num_get(fe);

	अगर (nb_fields == MVPP2_FLOW_N_FIELDS)
		वापस -EINVAL;

	mvpp2_cls_flow_hek_set(fe, nb_fields, field_id);

	mvpp2_cls_flow_hek_num_set(fe, nb_fields + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_flow_set_hek_fields(काष्ठा mvpp2_cls_flow_entry *fe,
				     अचिन्हित दीर्घ hash_opts)
अणु
	u32 field_id;
	पूर्णांक i;

	/* Clear old fields */
	mvpp2_cls_flow_hek_num_set(fe, 0);
	fe->data[2] = 0;

	क्रम_each_set_bit(i, &hash_opts, MVPP22_CLS_HEK_N_FIELDS) अणु
		चयन (BIT(i)) अणु
		हाल MVPP22_CLS_HEK_OPT_MAC_DA:
			field_id = MVPP22_CLS_FIELD_MAC_DA;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_VLAN:
			field_id = MVPP22_CLS_FIELD_VLAN;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_VLAN_PRI:
			field_id = MVPP22_CLS_FIELD_VLAN_PRI;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_IP4SA:
			field_id = MVPP22_CLS_FIELD_IP4SA;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_IP4DA:
			field_id = MVPP22_CLS_FIELD_IP4DA;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_IP6SA:
			field_id = MVPP22_CLS_FIELD_IP6SA;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_IP6DA:
			field_id = MVPP22_CLS_FIELD_IP6DA;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_L4SIP:
			field_id = MVPP22_CLS_FIELD_L4SIP;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_L4DIP:
			field_id = MVPP22_CLS_FIELD_L4DIP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (mvpp2_flow_add_hek_field(fe, field_id))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Returns the size, in bits, of the corresponding HEK field */
अटल पूर्णांक mvpp2_cls_hek_field_size(u32 field)
अणु
	चयन (field) अणु
	हाल MVPP22_CLS_HEK_OPT_MAC_DA:
		वापस 48;
	हाल MVPP22_CLS_HEK_OPT_VLAN:
		वापस 12;
	हाल MVPP22_CLS_HEK_OPT_VLAN_PRI:
		वापस 3;
	हाल MVPP22_CLS_HEK_OPT_IP4SA:
	हाल MVPP22_CLS_HEK_OPT_IP4DA:
		वापस 32;
	हाल MVPP22_CLS_HEK_OPT_IP6SA:
	हाल MVPP22_CLS_HEK_OPT_IP6DA:
		वापस 128;
	हाल MVPP22_CLS_HEK_OPT_L4SIP:
	हाल MVPP22_CLS_HEK_OPT_L4DIP:
		वापस 16;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

स्थिर काष्ठा mvpp2_cls_flow *mvpp2_cls_flow_get(पूर्णांक flow)
अणु
	अगर (flow >= MVPP2_N_PRS_FLOWS)
		वापस शून्य;

	वापस &cls_flows[flow];
पूर्ण

/* Set the hash generation options क्रम the given traffic flow.
 * One traffic flow (in the ethtool sense) has multiple classअगरication flows,
 * to handle specअगरic हालs such as fragmentation, or the presence of a
 * VLAN / DSA Tag.
 *
 * Each of these inभागidual flows has dअगरferent स्थिरraपूर्णांकs, क्रम example we
 * can't hash fragmented packets on L4 data (अन्यथा we would risk having packet
 * re-ordering), so each classअगरication flows masks the options with their
 * supported ones.
 *
 */
अटल पूर्णांक mvpp2_port_rss_hash_opts_set(काष्ठा mvpp2_port *port, पूर्णांक flow_type,
					u16 requested_opts)
अणु
	स्थिर काष्ठा mvpp2_cls_flow *flow;
	काष्ठा mvpp2_cls_flow_entry fe;
	पूर्णांक i, engine, flow_index;
	u16 hash_opts;

	क्रम_each_cls_flow_id_with_type(i, flow_type) अणु
		flow = mvpp2_cls_flow_get(i);
		अगर (!flow)
			वापस -EINVAL;

		flow_index = MVPP2_CLS_FLT_HASH_ENTRY(port->id, flow->flow_id);

		mvpp2_cls_flow_पढ़ो(port->priv, flow_index, &fe);

		hash_opts = flow->supported_hash_opts & requested_opts;

		/* Use C3HB engine to access L4 infos. This adds L4 infos to the
		 * hash parameters
		 */
		अगर (hash_opts & MVPP22_CLS_HEK_L4_OPTS)
			engine = MVPP22_CLS_ENGINE_C3HB;
		अन्यथा
			engine = MVPP22_CLS_ENGINE_C3HA;

		अगर (mvpp2_flow_set_hek_fields(&fe, hash_opts))
			वापस -EINVAL;

		mvpp2_cls_flow_eng_set(&fe, engine);

		mvpp2_cls_flow_ग_लिखो(port->priv, &fe);
	पूर्ण

	वापस 0;
पूर्ण

u16 mvpp2_flow_get_hek_fields(काष्ठा mvpp2_cls_flow_entry *fe)
अणु
	u16 hash_opts = 0;
	पूर्णांक n_fields, i, field;

	n_fields = mvpp2_cls_flow_hek_num_get(fe);

	क्रम (i = 0; i < n_fields; i++) अणु
		field = mvpp2_cls_flow_hek_get(fe, i);

		चयन (field) अणु
		हाल MVPP22_CLS_FIELD_MAC_DA:
			hash_opts |= MVPP22_CLS_HEK_OPT_MAC_DA;
			अवरोध;
		हाल MVPP22_CLS_FIELD_VLAN:
			hash_opts |= MVPP22_CLS_HEK_OPT_VLAN;
			अवरोध;
		हाल MVPP22_CLS_FIELD_VLAN_PRI:
			hash_opts |= MVPP22_CLS_HEK_OPT_VLAN_PRI;
			अवरोध;
		हाल MVPP22_CLS_FIELD_L3_PROTO:
			hash_opts |= MVPP22_CLS_HEK_OPT_L3_PROTO;
			अवरोध;
		हाल MVPP22_CLS_FIELD_IP4SA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP4SA;
			अवरोध;
		हाल MVPP22_CLS_FIELD_IP4DA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP4DA;
			अवरोध;
		हाल MVPP22_CLS_FIELD_IP6SA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP6SA;
			अवरोध;
		हाल MVPP22_CLS_FIELD_IP6DA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP6DA;
			अवरोध;
		हाल MVPP22_CLS_FIELD_L4SIP:
			hash_opts |= MVPP22_CLS_HEK_OPT_L4SIP;
			अवरोध;
		हाल MVPP22_CLS_FIELD_L4DIP:
			hash_opts |= MVPP22_CLS_HEK_OPT_L4DIP;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस hash_opts;
पूर्ण

/* Returns the hash opts क्रम this flow. There are several classअगरier flows
 * क्रम one traffic flow, this वापसs an aggregation of all configurations.
 */
अटल u16 mvpp2_port_rss_hash_opts_get(काष्ठा mvpp2_port *port, पूर्णांक flow_type)
अणु
	स्थिर काष्ठा mvpp2_cls_flow *flow;
	काष्ठा mvpp2_cls_flow_entry fe;
	पूर्णांक i, flow_index;
	u16 hash_opts = 0;

	क्रम_each_cls_flow_id_with_type(i, flow_type) अणु
		flow = mvpp2_cls_flow_get(i);
		अगर (!flow)
			वापस 0;

		flow_index = MVPP2_CLS_FLT_HASH_ENTRY(port->id, flow->flow_id);

		mvpp2_cls_flow_पढ़ो(port->priv, flow_index, &fe);

		hash_opts |= mvpp2_flow_get_hek_fields(&fe);
	पूर्ण

	वापस hash_opts;
पूर्ण

अटल व्योम mvpp2_cls_port_init_flows(काष्ठा mvpp2 *priv)
अणु
	स्थिर काष्ठा mvpp2_cls_flow *flow;
	पूर्णांक i;

	क्रम (i = 0; i < MVPP2_N_PRS_FLOWS; i++) अणु
		flow = mvpp2_cls_flow_get(i);
		अगर (!flow)
			अवरोध;

		mvpp2_cls_flow_prs_init(priv, flow);
		mvpp2_cls_flow_lkp_init(priv, flow);
		mvpp2_cls_flow_init(priv, flow);
	पूर्ण
पूर्ण

अटल व्योम mvpp2_port_c2_cls_init(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_cls_c2_entry c2;
	u8 qh, ql, pmap;

	स_रखो(&c2, 0, माप(c2));

	c2.index = MVPP22_CLS_C2_RSS_ENTRY(port->id);

	pmap = BIT(port->id);
	c2.tcam[4] = MVPP22_CLS_C2_PORT_ID(pmap);
	c2.tcam[4] |= MVPP22_CLS_C2_TCAM_EN(MVPP22_CLS_C2_PORT_ID(pmap));

	/* Match on Lookup Type */
	c2.tcam[4] |= MVPP22_CLS_C2_TCAM_EN(MVPP22_CLS_C2_LU_TYPE(MVPP2_CLS_LU_TYPE_MASK));
	c2.tcam[4] |= MVPP22_CLS_C2_LU_TYPE(MVPP22_CLS_LU_TYPE_ALL);

	/* Update RSS status after matching this entry */
	c2.act = MVPP22_CLS_C2_ACT_RSS_EN(MVPP22_C2_UPD_LOCK);

	/* Mark packet as "forwarded to software", needed क्रम RSS */
	c2.act |= MVPP22_CLS_C2_ACT_FWD(MVPP22_C2_FWD_SW_LOCK);

	/* Configure the शेष rx queue : Update Queue Low and Queue High, but
	 * करोn't lock, since the rx queue selection might be overridden by RSS
	 */
	c2.act |= MVPP22_CLS_C2_ACT_QHIGH(MVPP22_C2_UPD) |
		   MVPP22_CLS_C2_ACT_QLOW(MVPP22_C2_UPD);

	qh = (port->first_rxq >> 3) & MVPP22_CLS_C2_ATTR0_QHIGH_MASK;
	ql = port->first_rxq & MVPP22_CLS_C2_ATTR0_QLOW_MASK;

	c2.attr[0] = MVPP22_CLS_C2_ATTR0_QHIGH(qh) |
		      MVPP22_CLS_C2_ATTR0_QLOW(ql);

	c2.valid = true;

	mvpp2_cls_c2_ग_लिखो(port->priv, &c2);
पूर्ण

/* Classअगरier शेष initialization */
व्योम mvpp2_cls_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_cls_lookup_entry le;
	काष्ठा mvpp2_cls_flow_entry fe;
	काष्ठा mvpp2_cls_c2_entry c2;
	पूर्णांक index;

	/* Enable classअगरier */
	mvpp2_ग_लिखो(priv, MVPP2_CLS_MODE_REG, MVPP2_CLS_MODE_ACTIVE_MASK);

	/* Clear classअगरier flow table */
	स_रखो(&fe.data, 0, माप(fe.data));
	क्रम (index = 0; index < MVPP2_CLS_FLOWS_TBL_SIZE; index++) अणु
		fe.index = index;
		mvpp2_cls_flow_ग_लिखो(priv, &fe);
	पूर्ण

	/* Clear classअगरier lookup table */
	le.data = 0;
	क्रम (index = 0; index < MVPP2_CLS_LKP_TBL_SIZE; index++) अणु
		le.lkpid = index;
		le.way = 0;
		mvpp2_cls_lookup_ग_लिखो(priv, &le);

		le.way = 1;
		mvpp2_cls_lookup_ग_लिखो(priv, &le);
	पूर्ण

	/* Clear C2 TCAM engine table */
	स_रखो(&c2, 0, माप(c2));
	c2.valid = false;
	क्रम (index = 0; index < MVPP22_CLS_C2_N_ENTRIES; index++) अणु
		c2.index = index;
		mvpp2_cls_c2_ग_लिखो(priv, &c2);
	पूर्ण

	/* Disable the FIFO stages in C2 engine, which are only used in BIST
	 * mode
	 */
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_CTRL,
		    MVPP22_CLS_C2_TCAM_BYPASS_FIFO);

	mvpp2_cls_port_init_flows(priv);
पूर्ण

व्योम mvpp2_cls_port_config(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_cls_lookup_entry le;
	u32 val;

	/* Set way क्रम the port */
	val = mvpp2_पढ़ो(port->priv, MVPP2_CLS_PORT_WAY_REG);
	val &= ~MVPP2_CLS_PORT_WAY_MASK(port->id);
	mvpp2_ग_लिखो(port->priv, MVPP2_CLS_PORT_WAY_REG, val);

	/* Pick the entry to be accessed in lookup ID decoding table
	 * according to the way and lkpid.
	 */
	le.lkpid = port->id;
	le.way = 0;
	le.data = 0;

	/* Set initial CPU queue क्रम receiving packets */
	le.data &= ~MVPP2_CLS_LKP_TBL_RXQ_MASK;
	le.data |= port->first_rxq;

	/* Disable classअगरication engines */
	le.data &= ~MVPP2_CLS_LKP_TBL_LOOKUP_EN_MASK;

	/* Update lookup ID table entry */
	mvpp2_cls_lookup_ग_लिखो(port->priv, &le);

	mvpp2_port_c2_cls_init(port);
पूर्ण

u32 mvpp2_cls_c2_hit_count(काष्ठा mvpp2 *priv, पूर्णांक c2_index)
अणु
	mvpp2_ग_लिखो(priv, MVPP22_CLS_C2_TCAM_IDX, c2_index);

	वापस mvpp2_पढ़ो(priv, MVPP22_CLS_C2_HIT_CTR);
पूर्ण

अटल व्योम mvpp2_rss_port_c2_enable(काष्ठा mvpp2_port *port, u32 ctx)
अणु
	काष्ठा mvpp2_cls_c2_entry c2;
	u8 qh, ql;

	mvpp2_cls_c2_पढ़ो(port->priv, MVPP22_CLS_C2_RSS_ENTRY(port->id), &c2);

	/* The RxQ number is used to select the RSS table. It that हाल, we set
	 * it to be the ctx number.
	 */
	qh = (ctx >> 3) & MVPP22_CLS_C2_ATTR0_QHIGH_MASK;
	ql = ctx & MVPP22_CLS_C2_ATTR0_QLOW_MASK;

	c2.attr[0] = MVPP22_CLS_C2_ATTR0_QHIGH(qh) |
		     MVPP22_CLS_C2_ATTR0_QLOW(ql);

	c2.attr[2] |= MVPP22_CLS_C2_ATTR2_RSS_EN;

	mvpp2_cls_c2_ग_लिखो(port->priv, &c2);
पूर्ण

अटल व्योम mvpp2_rss_port_c2_disable(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_cls_c2_entry c2;
	u8 qh, ql;

	mvpp2_cls_c2_पढ़ो(port->priv, MVPP22_CLS_C2_RSS_ENTRY(port->id), &c2);

	/* Reset the शेष destination RxQ to the port's first rx queue. */
	qh = (port->first_rxq >> 3) & MVPP22_CLS_C2_ATTR0_QHIGH_MASK;
	ql = port->first_rxq & MVPP22_CLS_C2_ATTR0_QLOW_MASK;

	c2.attr[0] = MVPP22_CLS_C2_ATTR0_QHIGH(qh) |
		      MVPP22_CLS_C2_ATTR0_QLOW(ql);

	c2.attr[2] &= ~MVPP22_CLS_C2_ATTR2_RSS_EN;

	mvpp2_cls_c2_ग_लिखो(port->priv, &c2);
पूर्ण

अटल अंतरभूत पूर्णांक mvpp22_rss_ctx(काष्ठा mvpp2_port *port, पूर्णांक port_rss_ctx)
अणु
	वापस port->rss_ctx[port_rss_ctx];
पूर्ण

पूर्णांक mvpp22_port_rss_enable(काष्ठा mvpp2_port *port)
अणु
	अगर (mvpp22_rss_ctx(port, 0) < 0)
		वापस -EINVAL;

	mvpp2_rss_port_c2_enable(port, mvpp22_rss_ctx(port, 0));

	वापस 0;
पूर्ण

पूर्णांक mvpp22_port_rss_disable(काष्ठा mvpp2_port *port)
अणु
	अगर (mvpp22_rss_ctx(port, 0) < 0)
		वापस -EINVAL;

	mvpp2_rss_port_c2_disable(port);

	वापस 0;
पूर्ण

अटल व्योम mvpp22_port_c2_lookup_disable(काष्ठा mvpp2_port *port, पूर्णांक entry)
अणु
	काष्ठा mvpp2_cls_c2_entry c2;

	mvpp2_cls_c2_पढ़ो(port->priv, entry, &c2);

	/* Clear the port map so that the entry करोesn't match anymore */
	c2.tcam[4] &= ~(MVPP22_CLS_C2_PORT_ID(BIT(port->id)));

	mvpp2_cls_c2_ग_लिखो(port->priv, &c2);
पूर्ण

/* Set CPU queue number क्रम oversize packets */
व्योम mvpp2_cls_oversize_rxq_set(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	mvpp2_ग_लिखो(port->priv, MVPP2_CLS_OVERSIZE_RXQ_LOW_REG(port->id),
		    port->first_rxq & MVPP2_CLS_OVERSIZE_RXQ_LOW_MASK);

	mvpp2_ग_लिखो(port->priv, MVPP2_CLS_SWFWD_P2HQ_REG(port->id),
		    (port->first_rxq >> MVPP2_CLS_OVERSIZE_RXQ_LOW_BITS));

	val = mvpp2_पढ़ो(port->priv, MVPP2_CLS_SWFWD_PCTRL_REG);
	val &= ~MVPP2_CLS_SWFWD_PCTRL_MASK(port->id);
	mvpp2_ग_लिखो(port->priv, MVPP2_CLS_SWFWD_PCTRL_REG, val);
पूर्ण

अटल पूर्णांक mvpp2_port_c2_tcam_rule_add(काष्ठा mvpp2_port *port,
				       काष्ठा mvpp2_rfs_rule *rule)
अणु
	काष्ठा flow_action_entry *act;
	काष्ठा mvpp2_cls_c2_entry c2;
	u8 qh, ql, pmap;
	पूर्णांक index, ctx;

	अगर (!flow_action_basic_hw_stats_check(&rule->flow->action, शून्य))
		वापस -EOPNOTSUPP;

	स_रखो(&c2, 0, माप(c2));

	index = mvpp2_cls_c2_port_flow_index(port, rule->loc);
	अगर (index < 0)
		वापस -EINVAL;
	c2.index = index;

	act = &rule->flow->action.entries[0];

	rule->c2_index = c2.index;

	c2.tcam[3] = (rule->c2_tcam & 0xffff) |
		     ((rule->c2_tcam_mask & 0xffff) << 16);
	c2.tcam[2] = ((rule->c2_tcam >> 16) & 0xffff) |
		     (((rule->c2_tcam_mask >> 16) & 0xffff) << 16);
	c2.tcam[1] = ((rule->c2_tcam >> 32) & 0xffff) |
		     (((rule->c2_tcam_mask >> 32) & 0xffff) << 16);
	c2.tcam[0] = ((rule->c2_tcam >> 48) & 0xffff) |
		     (((rule->c2_tcam_mask >> 48) & 0xffff) << 16);

	pmap = BIT(port->id);
	c2.tcam[4] = MVPP22_CLS_C2_PORT_ID(pmap);
	c2.tcam[4] |= MVPP22_CLS_C2_TCAM_EN(MVPP22_CLS_C2_PORT_ID(pmap));

	/* Match on Lookup Type */
	c2.tcam[4] |= MVPP22_CLS_C2_TCAM_EN(MVPP22_CLS_C2_LU_TYPE(MVPP2_CLS_LU_TYPE_MASK));
	c2.tcam[4] |= MVPP22_CLS_C2_LU_TYPE(rule->loc);

	अगर (act->id == FLOW_ACTION_DROP) अणु
		c2.act = MVPP22_CLS_C2_ACT_COLOR(MVPP22_C2_COL_RED_LOCK);
	पूर्ण अन्यथा अणु
		/* We want to keep the शेष color derived from the Header
		 * Parser drop entries, क्रम VLAN and MAC filtering. This will
		 * assign a शेष color of Green or Red, and we want matches
		 * with a non-drop action to keep that color.
		 */
		c2.act = MVPP22_CLS_C2_ACT_COLOR(MVPP22_C2_COL_NO_UPD_LOCK);

		/* Update RSS status after matching this entry */
		अगर (act->queue.ctx)
			c2.attr[2] |= MVPP22_CLS_C2_ATTR2_RSS_EN;

		/* Always lock the RSS_EN decision. We might have high prio
		 * rules steering to an RXQ, and a lower one steering to RSS,
		 * we करोn't want the low prio RSS rule overwriting this flag.
		 */
		c2.act = MVPP22_CLS_C2_ACT_RSS_EN(MVPP22_C2_UPD_LOCK);

		/* Mark packet as "forwarded to software", needed क्रम RSS */
		c2.act |= MVPP22_CLS_C2_ACT_FWD(MVPP22_C2_FWD_SW_LOCK);

		c2.act |= MVPP22_CLS_C2_ACT_QHIGH(MVPP22_C2_UPD_LOCK) |
			   MVPP22_CLS_C2_ACT_QLOW(MVPP22_C2_UPD_LOCK);

		अगर (act->queue.ctx) अणु
			/* Get the global ctx number */
			ctx = mvpp22_rss_ctx(port, act->queue.ctx);
			अगर (ctx < 0)
				वापस -EINVAL;

			qh = (ctx >> 3) & MVPP22_CLS_C2_ATTR0_QHIGH_MASK;
			ql = ctx & MVPP22_CLS_C2_ATTR0_QLOW_MASK;
		पूर्ण अन्यथा अणु
			qh = ((act->queue.index + port->first_rxq) >> 3) &
			      MVPP22_CLS_C2_ATTR0_QHIGH_MASK;
			ql = (act->queue.index + port->first_rxq) &
			      MVPP22_CLS_C2_ATTR0_QLOW_MASK;
		पूर्ण

		c2.attr[0] = MVPP22_CLS_C2_ATTR0_QHIGH(qh) |
			      MVPP22_CLS_C2_ATTR0_QLOW(ql);
	पूर्ण

	c2.valid = true;

	mvpp2_cls_c2_ग_लिखो(port->priv, &c2);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_port_c2_rfs_rule_insert(काष्ठा mvpp2_port *port,
					 काष्ठा mvpp2_rfs_rule *rule)
अणु
	वापस mvpp2_port_c2_tcam_rule_add(port, rule);
पूर्ण

अटल पूर्णांक mvpp2_port_cls_rfs_rule_हटाओ(काष्ठा mvpp2_port *port,
					  काष्ठा mvpp2_rfs_rule *rule)
अणु
	स्थिर काष्ठा mvpp2_cls_flow *flow;
	काष्ठा mvpp2_cls_flow_entry fe;
	पूर्णांक index, i;

	क्रम_each_cls_flow_id_containing_type(i, rule->flow_type) अणु
		flow = mvpp2_cls_flow_get(i);
		अगर (!flow)
			वापस 0;

		index = MVPP2_CLS_FLT_C2_RFS(port->id, flow->flow_id, rule->loc);

		mvpp2_cls_flow_पढ़ो(port->priv, index, &fe);
		mvpp2_cls_flow_port_हटाओ(&fe, BIT(port->id));
		mvpp2_cls_flow_ग_लिखो(port->priv, &fe);
	पूर्ण

	अगर (rule->c2_index >= 0)
		mvpp22_port_c2_lookup_disable(port, rule->c2_index);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_port_flt_rfs_rule_insert(काष्ठा mvpp2_port *port,
					  काष्ठा mvpp2_rfs_rule *rule)
अणु
	स्थिर काष्ठा mvpp2_cls_flow *flow;
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_cls_flow_entry fe;
	पूर्णांक index, ret, i;

	अगर (rule->engine != MVPP22_CLS_ENGINE_C2)
		वापस -EOPNOTSUPP;

	ret = mvpp2_port_c2_rfs_rule_insert(port, rule);
	अगर (ret)
		वापस ret;

	क्रम_each_cls_flow_id_containing_type(i, rule->flow_type) अणु
		flow = mvpp2_cls_flow_get(i);
		अगर (!flow)
			वापस 0;

		अगर ((rule->hek_fields & flow->supported_hash_opts) != rule->hek_fields)
			जारी;

		index = MVPP2_CLS_FLT_C2_RFS(port->id, flow->flow_id, rule->loc);

		mvpp2_cls_flow_पढ़ो(priv, index, &fe);
		mvpp2_cls_flow_eng_set(&fe, rule->engine);
		mvpp2_cls_flow_port_id_sel(&fe, true);
		mvpp2_flow_set_hek_fields(&fe, rule->hek_fields);
		mvpp2_cls_flow_lu_type_set(&fe, rule->loc);
		mvpp2_cls_flow_port_add(&fe, 0xf);

		mvpp2_cls_flow_ग_लिखो(priv, &fe);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_cls_c2_build_match(काष्ठा mvpp2_rfs_rule *rule)
अणु
	काष्ठा flow_rule *flow = rule->flow;
	पूर्णांक offs = 0;

	/* The order of insertion in C2 tcam must match the order in which
	 * the fields are found in the header
	 */
	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(flow, &match);
		अगर (match.mask->vlan_id) अणु
			rule->hek_fields |= MVPP22_CLS_HEK_OPT_VLAN;

			rule->c2_tcam |= ((u64)match.key->vlan_id) << offs;
			rule->c2_tcam_mask |= ((u64)match.mask->vlan_id) << offs;

			/* Don't update the offset yet */
		पूर्ण

		अगर (match.mask->vlan_priority) अणु
			rule->hek_fields |= MVPP22_CLS_HEK_OPT_VLAN_PRI;

			/* VLAN pri is always at offset 13 relative to the
			 * current offset
			 */
			rule->c2_tcam |= ((u64)match.key->vlan_priority) <<
				(offs + 13);
			rule->c2_tcam_mask |= ((u64)match.mask->vlan_priority) <<
				(offs + 13);
		पूर्ण

		अगर (match.mask->vlan_dei)
			वापस -EOPNOTSUPP;

		/* vlan id and prio always seem to take a full 16-bit slot in
		 * the Header Extracted Key.
		 */
		offs += 16;
	पूर्ण

	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(flow, &match);
		अगर (match.mask->src) अणु
			rule->hek_fields |= MVPP22_CLS_HEK_OPT_L4SIP;

			rule->c2_tcam |= ((u64)ntohs(match.key->src)) << offs;
			rule->c2_tcam_mask |= ((u64)ntohs(match.mask->src)) << offs;
			offs += mvpp2_cls_hek_field_size(MVPP22_CLS_HEK_OPT_L4SIP);
		पूर्ण

		अगर (match.mask->dst) अणु
			rule->hek_fields |= MVPP22_CLS_HEK_OPT_L4DIP;

			rule->c2_tcam |= ((u64)ntohs(match.key->dst)) << offs;
			rule->c2_tcam_mask |= ((u64)ntohs(match.mask->dst)) << offs;
			offs += mvpp2_cls_hek_field_size(MVPP22_CLS_HEK_OPT_L4DIP);
		पूर्ण
	पूर्ण

	अगर (hweight16(rule->hek_fields) > MVPP2_FLOW_N_FIELDS)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_cls_rfs_parse_rule(काष्ठा mvpp2_rfs_rule *rule)
अणु
	काष्ठा flow_rule *flow = rule->flow;
	काष्ठा flow_action_entry *act;

	अगर (!flow_action_basic_hw_stats_check(&rule->flow->action, शून्य))
		वापस -EOPNOTSUPP;

	act = &flow->action.entries[0];
	अगर (act->id != FLOW_ACTION_QUEUE && act->id != FLOW_ACTION_DROP)
		वापस -EOPNOTSUPP;

	/* When both an RSS context and an queue index are set, the index
	 * is considered as an offset to be added to the indirection table
	 * entries. We करोn't support this, so reject this rule.
	 */
	अगर (act->queue.ctx && act->queue.index)
		वापस -EOPNOTSUPP;

	/* For now, only use the C2 engine which has a HEK size limited to 64
	 * bits क्रम TCAM matching.
	 */
	rule->engine = MVPP22_CLS_ENGINE_C2;

	अगर (mvpp2_cls_c2_build_match(rule))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक mvpp2_ethtool_cls_rule_get(काष्ठा mvpp2_port *port,
			       काष्ठा ethtool_rxnfc *rxnfc)
अणु
	काष्ठा mvpp2_ethtool_fs *efs;

	अगर (rxnfc->fs.location >= MVPP2_N_RFS_ENTRIES_PER_FLOW)
		वापस -EINVAL;

	efs = port->rfs_rules[rxnfc->fs.location];
	अगर (!efs)
		वापस -ENOENT;

	स_नकल(rxnfc, &efs->rxnfc, माप(efs->rxnfc));

	वापस 0;
पूर्ण

पूर्णांक mvpp2_ethtool_cls_rule_ins(काष्ठा mvpp2_port *port,
			       काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा ethtool_rx_flow_spec_input input = अणुपूर्ण;
	काष्ठा ethtool_rx_flow_rule *ethtool_rule;
	काष्ठा mvpp2_ethtool_fs *efs, *old_efs;
	पूर्णांक ret = 0;

	अगर (info->fs.location >= MVPP2_N_RFS_ENTRIES_PER_FLOW)
		वापस -EINVAL;

	efs = kzalloc(माप(*efs), GFP_KERNEL);
	अगर (!efs)
		वापस -ENOMEM;

	input.fs = &info->fs;

	/* We need to manually set the rss_ctx, since this info isn't present
	 * in info->fs
	 */
	अगर (info->fs.flow_type & FLOW_RSS)
		input.rss_ctx = info->rss_context;

	ethtool_rule = ethtool_rx_flow_rule_create(&input);
	अगर (IS_ERR(ethtool_rule)) अणु
		ret = PTR_ERR(ethtool_rule);
		जाओ clean_rule;
	पूर्ण

	efs->rule.flow = ethtool_rule->rule;
	efs->rule.flow_type = mvpp2_cls_ethtool_flow_to_type(info->fs.flow_type);
	अगर (efs->rule.flow_type < 0) अणु
		ret = efs->rule.flow_type;
		जाओ clean_rule;
	पूर्ण

	ret = mvpp2_cls_rfs_parse_rule(&efs->rule);
	अगर (ret)
		जाओ clean_eth_rule;

	efs->rule.loc = info->fs.location;

	/* Replace an alपढ़ोy existing rule */
	अगर (port->rfs_rules[efs->rule.loc]) अणु
		old_efs = port->rfs_rules[efs->rule.loc];
		ret = mvpp2_port_cls_rfs_rule_हटाओ(port, &old_efs->rule);
		अगर (ret)
			जाओ clean_eth_rule;
		kमुक्त(old_efs);
		port->n_rfs_rules--;
	पूर्ण

	ret = mvpp2_port_flt_rfs_rule_insert(port, &efs->rule);
	अगर (ret)
		जाओ clean_eth_rule;

	ethtool_rx_flow_rule_destroy(ethtool_rule);
	efs->rule.flow = शून्य;

	स_नकल(&efs->rxnfc, info, माप(*info));
	port->rfs_rules[efs->rule.loc] = efs;
	port->n_rfs_rules++;

	वापस ret;

clean_eth_rule:
	ethtool_rx_flow_rule_destroy(ethtool_rule);
clean_rule:
	kमुक्त(efs);
	वापस ret;
पूर्ण

पूर्णांक mvpp2_ethtool_cls_rule_del(काष्ठा mvpp2_port *port,
			       काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा mvpp2_ethtool_fs *efs;
	पूर्णांक ret;

	अगर (info->fs.location >= MVPP2_N_RFS_ENTRIES_PER_FLOW)
		वापस -EINVAL;

	efs = port->rfs_rules[info->fs.location];
	अगर (!efs)
		वापस -EINVAL;

	/* Remove the rule from the engines. */
	ret = mvpp2_port_cls_rfs_rule_हटाओ(port, &efs->rule);
	अगर (ret)
		वापस ret;

	port->n_rfs_rules--;
	port->rfs_rules[info->fs.location] = शून्य;
	kमुक्त(efs);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 mvpp22_rxfh_indir(काष्ठा mvpp2_port *port, u32 rxq)
अणु
	पूर्णांक nrxqs, cpu, cpus = num_possible_cpus();

	/* Number of RXQs per CPU */
	nrxqs = port->nrxqs / cpus;

	/* CPU that will handle this rx queue */
	cpu = rxq / nrxqs;

	अगर (!cpu_online(cpu))
		वापस port->first_rxq;

	/* Indirection to better distribute the paquets on the CPUs when
	 * configuring the RSS queues.
	 */
	वापस port->first_rxq + ((rxq * nrxqs + rxq / cpus) % port->nrxqs);
पूर्ण

अटल व्योम mvpp22_rss_fill_table(काष्ठा mvpp2_port *port,
				  काष्ठा mvpp2_rss_table *table,
				  u32 rss_ctx)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	पूर्णांक i;

	क्रम (i = 0; i < MVPP22_RSS_TABLE_ENTRIES; i++) अणु
		u32 sel = MVPP22_RSS_INDEX_TABLE(rss_ctx) |
			  MVPP22_RSS_INDEX_TABLE_ENTRY(i);
		mvpp2_ग_लिखो(priv, MVPP22_RSS_INDEX, sel);

		mvpp2_ग_लिखो(priv, MVPP22_RSS_TABLE_ENTRY,
			    mvpp22_rxfh_indir(port, table->indir[i]));
	पूर्ण
पूर्ण

अटल पूर्णांक mvpp22_rss_context_create(काष्ठा mvpp2_port *port, u32 *rss_ctx)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	u32 ctx;

	/* Find the first मुक्त RSS table */
	क्रम (ctx = 0; ctx < MVPP22_N_RSS_TABLES; ctx++) अणु
		अगर (!priv->rss_tables[ctx])
			अवरोध;
	पूर्ण

	अगर (ctx == MVPP22_N_RSS_TABLES)
		वापस -EINVAL;

	priv->rss_tables[ctx] = kzalloc(माप(*priv->rss_tables[ctx]),
					GFP_KERNEL);
	अगर (!priv->rss_tables[ctx])
		वापस -ENOMEM;

	*rss_ctx = ctx;

	/* Set the table width: replace the whole classअगरier Rx queue number
	 * with the ones configured in RSS table entries.
	 */
	mvpp2_ग_लिखो(priv, MVPP22_RSS_INDEX, MVPP22_RSS_INDEX_TABLE(ctx));
	mvpp2_ग_लिखो(priv, MVPP22_RSS_WIDTH, 8);

	mvpp2_ग_लिखो(priv, MVPP22_RSS_INDEX, MVPP22_RSS_INDEX_QUEUE(ctx));
	mvpp2_ग_लिखो(priv, MVPP22_RXQ2RSS_TABLE, MVPP22_RSS_TABLE_POINTER(ctx));

	वापस 0;
पूर्ण

पूर्णांक mvpp22_port_rss_ctx_create(काष्ठा mvpp2_port *port, u32 *port_ctx)
अणु
	u32 rss_ctx;
	पूर्णांक ret, i;

	ret = mvpp22_rss_context_create(port, &rss_ctx);
	अगर (ret)
		वापस ret;

	/* Find the first available context number in the port, starting from 1.
	 * Context 0 on each port is reserved क्रम the शेष context.
	 */
	क्रम (i = 1; i < MVPP22_N_RSS_TABLES; i++) अणु
		अगर (port->rss_ctx[i] < 0)
			अवरोध;
	पूर्ण

	अगर (i == MVPP22_N_RSS_TABLES)
		वापस -EINVAL;

	port->rss_ctx[i] = rss_ctx;
	*port_ctx = i;

	वापस 0;
पूर्ण

अटल काष्ठा mvpp2_rss_table *mvpp22_rss_table_get(काष्ठा mvpp2 *priv,
						    पूर्णांक rss_ctx)
अणु
	अगर (rss_ctx < 0 || rss_ctx >= MVPP22_N_RSS_TABLES)
		वापस शून्य;

	वापस priv->rss_tables[rss_ctx];
पूर्ण

पूर्णांक mvpp22_port_rss_ctx_delete(काष्ठा mvpp2_port *port, u32 port_ctx)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा ethtool_rxnfc *rxnfc;
	पूर्णांक i, rss_ctx, ret;

	rss_ctx = mvpp22_rss_ctx(port, port_ctx);

	अगर (rss_ctx < 0 || rss_ctx >= MVPP22_N_RSS_TABLES)
		वापस -EINVAL;

	/* Invalidate any active classअगरication rule that use this context */
	क्रम (i = 0; i < MVPP2_N_RFS_ENTRIES_PER_FLOW; i++) अणु
		अगर (!port->rfs_rules[i])
			जारी;

		rxnfc = &port->rfs_rules[i]->rxnfc;
		अगर (!(rxnfc->fs.flow_type & FLOW_RSS) ||
		    rxnfc->rss_context != port_ctx)
			जारी;

		ret = mvpp2_ethtool_cls_rule_del(port, rxnfc);
		अगर (ret) अणु
			netdev_warn(port->dev,
				    "couldn't remove classification rule %d associated to this context",
				    rxnfc->fs.location);
		पूर्ण
	पूर्ण

	kमुक्त(priv->rss_tables[rss_ctx]);

	priv->rss_tables[rss_ctx] = शून्य;
	port->rss_ctx[port_ctx] = -1;

	वापस 0;
पूर्ण

पूर्णांक mvpp22_port_rss_ctx_indir_set(काष्ठा mvpp2_port *port, u32 port_ctx,
				  स्थिर u32 *indir)
अणु
	पूर्णांक rss_ctx = mvpp22_rss_ctx(port, port_ctx);
	काष्ठा mvpp2_rss_table *rss_table = mvpp22_rss_table_get(port->priv,
								 rss_ctx);

	अगर (!rss_table)
		वापस -EINVAL;

	स_नकल(rss_table->indir, indir,
	       MVPP22_RSS_TABLE_ENTRIES * माप(rss_table->indir[0]));

	mvpp22_rss_fill_table(port, rss_table, rss_ctx);

	वापस 0;
पूर्ण

पूर्णांक mvpp22_port_rss_ctx_indir_get(काष्ठा mvpp2_port *port, u32 port_ctx,
				  u32 *indir)
अणु
	पूर्णांक rss_ctx =  mvpp22_rss_ctx(port, port_ctx);
	काष्ठा mvpp2_rss_table *rss_table = mvpp22_rss_table_get(port->priv,
								 rss_ctx);

	अगर (!rss_table)
		वापस -EINVAL;

	स_नकल(indir, rss_table->indir,
	       MVPP22_RSS_TABLE_ENTRIES * माप(rss_table->indir[0]));

	वापस 0;
पूर्ण

पूर्णांक mvpp2_ethtool_rxfh_set(काष्ठा mvpp2_port *port, काष्ठा ethtool_rxnfc *info)
अणु
	u16 hash_opts = 0;
	u32 flow_type;

	flow_type = mvpp2_cls_ethtool_flow_to_type(info->flow_type);

	चयन (flow_type) अणु
	हाल MVPP22_FLOW_TCP4:
	हाल MVPP22_FLOW_UDP4:
	हाल MVPP22_FLOW_TCP6:
	हाल MVPP22_FLOW_UDP6:
		अगर (info->data & RXH_L4_B_0_1)
			hash_opts |= MVPP22_CLS_HEK_OPT_L4SIP;
		अगर (info->data & RXH_L4_B_2_3)
			hash_opts |= MVPP22_CLS_HEK_OPT_L4DIP;
		fallthrough;
	हाल MVPP22_FLOW_IP4:
	हाल MVPP22_FLOW_IP6:
		अगर (info->data & RXH_L2DA)
			hash_opts |= MVPP22_CLS_HEK_OPT_MAC_DA;
		अगर (info->data & RXH_VLAN)
			hash_opts |= MVPP22_CLS_HEK_OPT_VLAN;
		अगर (info->data & RXH_L3_PROTO)
			hash_opts |= MVPP22_CLS_HEK_OPT_L3_PROTO;
		अगर (info->data & RXH_IP_SRC)
			hash_opts |= (MVPP22_CLS_HEK_OPT_IP4SA |
				     MVPP22_CLS_HEK_OPT_IP6SA);
		अगर (info->data & RXH_IP_DST)
			hash_opts |= (MVPP22_CLS_HEK_OPT_IP4DA |
				     MVPP22_CLS_HEK_OPT_IP6DA);
		अवरोध;
	शेष: वापस -EOPNOTSUPP;
	पूर्ण

	वापस mvpp2_port_rss_hash_opts_set(port, flow_type, hash_opts);
पूर्ण

पूर्णांक mvpp2_ethtool_rxfh_get(काष्ठा mvpp2_port *port, काष्ठा ethtool_rxnfc *info)
अणु
	अचिन्हित दीर्घ hash_opts;
	u32 flow_type;
	पूर्णांक i;

	flow_type = mvpp2_cls_ethtool_flow_to_type(info->flow_type);

	hash_opts = mvpp2_port_rss_hash_opts_get(port, flow_type);
	info->data = 0;

	क्रम_each_set_bit(i, &hash_opts, MVPP22_CLS_HEK_N_FIELDS) अणु
		चयन (BIT(i)) अणु
		हाल MVPP22_CLS_HEK_OPT_MAC_DA:
			info->data |= RXH_L2DA;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_VLAN:
			info->data |= RXH_VLAN;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_L3_PROTO:
			info->data |= RXH_L3_PROTO;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_IP4SA:
		हाल MVPP22_CLS_HEK_OPT_IP6SA:
			info->data |= RXH_IP_SRC;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_IP4DA:
		हाल MVPP22_CLS_HEK_OPT_IP6DA:
			info->data |= RXH_IP_DST;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_L4SIP:
			info->data |= RXH_L4_B_0_1;
			अवरोध;
		हाल MVPP22_CLS_HEK_OPT_L4DIP:
			info->data |= RXH_L4_B_2_3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mvpp22_port_rss_init(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_rss_table *table;
	u32 context = 0;
	पूर्णांक i, ret;

	क्रम (i = 0; i < MVPP22_N_RSS_TABLES; i++)
		port->rss_ctx[i] = -1;

	ret = mvpp22_rss_context_create(port, &context);
	अगर (ret)
		वापस ret;

	table = mvpp22_rss_table_get(port->priv, context);
	अगर (!table)
		वापस -EINVAL;

	port->rss_ctx[0] = context;

	/* Configure the first table to evenly distribute the packets across
	 * real Rx Queues. The table entries map a hash to a port Rx Queue.
	 */
	क्रम (i = 0; i < MVPP22_RSS_TABLE_ENTRIES; i++)
		table->indir[i] = ethtool_rxfh_indir_शेष(i, port->nrxqs);

	mvpp22_rss_fill_table(port, table, mvpp22_rss_ctx(port, 0));

	/* Configure शेष flows */
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_IP4, MVPP22_CLS_HEK_IP4_2T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_IP6, MVPP22_CLS_HEK_IP6_2T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_TCP4, MVPP22_CLS_HEK_IP4_5T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_TCP6, MVPP22_CLS_HEK_IP6_5T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_UDP4, MVPP22_CLS_HEK_IP4_5T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_UDP6, MVPP22_CLS_HEK_IP6_5T);

	वापस 0;
पूर्ण
