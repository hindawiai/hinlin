<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * RSS and Classअगरier definitions क्रम Marvell PPv2 Network Controller
 *
 * Copyright (C) 2014 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 */

#अगर_अघोषित _MVPP2_CLS_H_
#घोषणा _MVPP2_CLS_H_

#समावेश "mvpp2.h"
#समावेश "mvpp2_prs.h"

/* Classअगरier स्थिरants */
#घोषणा MVPP2_CLS_FLOWS_TBL_SIZE	512
#घोषणा MVPP2_CLS_FLOWS_TBL_DATA_WORDS	3
#घोषणा MVPP2_CLS_LKP_TBL_SIZE		64
#घोषणा MVPP2_CLS_RX_QUEUES		256

/* Classअगरier flow स्थिरants */

#घोषणा MVPP2_FLOW_N_FIELDS		4

क्रमागत mvpp2_cls_engine अणु
	MVPP22_CLS_ENGINE_C2 = 1,
	MVPP22_CLS_ENGINE_C3A,
	MVPP22_CLS_ENGINE_C3B,
	MVPP22_CLS_ENGINE_C4,
	MVPP22_CLS_ENGINE_C3HA = 6,
	MVPP22_CLS_ENGINE_C3HB = 7,
पूर्ण;

#घोषणा MVPP22_CLS_HEK_OPT_MAC_DA	BIT(0)
#घोषणा MVPP22_CLS_HEK_OPT_VLAN_PRI	BIT(1)
#घोषणा MVPP22_CLS_HEK_OPT_VLAN		BIT(2)
#घोषणा MVPP22_CLS_HEK_OPT_L3_PROTO	BIT(3)
#घोषणा MVPP22_CLS_HEK_OPT_IP4SA	BIT(4)
#घोषणा MVPP22_CLS_HEK_OPT_IP4DA	BIT(5)
#घोषणा MVPP22_CLS_HEK_OPT_IP6SA	BIT(6)
#घोषणा MVPP22_CLS_HEK_OPT_IP6DA	BIT(7)
#घोषणा MVPP22_CLS_HEK_OPT_L4SIP	BIT(8)
#घोषणा MVPP22_CLS_HEK_OPT_L4DIP	BIT(9)
#घोषणा MVPP22_CLS_HEK_N_FIELDS		10

#घोषणा MVPP22_CLS_HEK_L4_OPTS	(MVPP22_CLS_HEK_OPT_L4SIP | \
				 MVPP22_CLS_HEK_OPT_L4DIP)

#घोषणा MVPP22_CLS_HEK_IP4_2T	(MVPP22_CLS_HEK_OPT_IP4SA | \
				 MVPP22_CLS_HEK_OPT_IP4DA)

#घोषणा MVPP22_CLS_HEK_IP6_2T	(MVPP22_CLS_HEK_OPT_IP6SA | \
				 MVPP22_CLS_HEK_OPT_IP6DA)

/* The fअगरth tuple in "5T" is the L4_Info field */
#घोषणा MVPP22_CLS_HEK_IP4_5T	(MVPP22_CLS_HEK_IP4_2T | \
				 MVPP22_CLS_HEK_L4_OPTS)

#घोषणा MVPP22_CLS_HEK_IP6_5T	(MVPP22_CLS_HEK_IP6_2T | \
				 MVPP22_CLS_HEK_L4_OPTS)

#घोषणा MVPP22_CLS_HEK_TAGGED	(MVPP22_CLS_HEK_OPT_VLAN | \
				 MVPP22_CLS_HEK_OPT_VLAN_PRI)

क्रमागत mvpp2_cls_field_id अणु
	MVPP22_CLS_FIELD_MAC_DA = 0x03,
	MVPP22_CLS_FIELD_VLAN_PRI = 0x05,
	MVPP22_CLS_FIELD_VLAN = 0x06,
	MVPP22_CLS_FIELD_L3_PROTO = 0x0f,
	MVPP22_CLS_FIELD_IP4SA = 0x10,
	MVPP22_CLS_FIELD_IP4DA = 0x11,
	MVPP22_CLS_FIELD_IP6SA = 0x17,
	MVPP22_CLS_FIELD_IP6DA = 0x1a,
	MVPP22_CLS_FIELD_L4SIP = 0x1d,
	MVPP22_CLS_FIELD_L4DIP = 0x1e,
पूर्ण;

/* Classअगरier C2 engine स्थिरants */
#घोषणा MVPP22_CLS_C2_TCAM_EN(data)		((data) << 16)

क्रमागत mvpp22_cls_c2_action अणु
	MVPP22_C2_NO_UPD = 0,
	MVPP22_C2_NO_UPD_LOCK,
	MVPP22_C2_UPD,
	MVPP22_C2_UPD_LOCK,
पूर्ण;

क्रमागत mvpp22_cls_c2_fwd_action अणु
	MVPP22_C2_FWD_NO_UPD = 0,
	MVPP22_C2_FWD_NO_UPD_LOCK,
	MVPP22_C2_FWD_SW,
	MVPP22_C2_FWD_SW_LOCK,
	MVPP22_C2_FWD_HW,
	MVPP22_C2_FWD_HW_LOCK,
	MVPP22_C2_FWD_HW_LOW_LAT,
	MVPP22_C2_FWD_HW_LOW_LAT_LOCK,
पूर्ण;

क्रमागत mvpp22_cls_c2_color_action अणु
	MVPP22_C2_COL_NO_UPD = 0,
	MVPP22_C2_COL_NO_UPD_LOCK,
	MVPP22_C2_COL_GREEN,
	MVPP22_C2_COL_GREEN_LOCK,
	MVPP22_C2_COL_YELLOW,
	MVPP22_C2_COL_YELLOW_LOCK,
	MVPP22_C2_COL_RED,		/* Drop */
	MVPP22_C2_COL_RED_LOCK,		/* Drop */
पूर्ण;

#घोषणा MVPP2_CLS_C2_TCAM_WORDS			5
#घोषणा MVPP2_CLS_C2_ATTR_WORDS			5

काष्ठा mvpp2_cls_c2_entry अणु
	u32 index;
	/* TCAM lookup key */
	u32 tcam[MVPP2_CLS_C2_TCAM_WORDS];
	/* Actions to perक्रमm upon TCAM match */
	u32 act;
	/* Attributes relative to the actions to perक्रमm */
	u32 attr[MVPP2_CLS_C2_ATTR_WORDS];
	/* Entry validity */
	u8 valid;
पूर्ण;

#घोषणा MVPP22_FLOW_ETHER_BIT	BIT(0)
#घोषणा MVPP22_FLOW_IP4_BIT	BIT(1)
#घोषणा MVPP22_FLOW_IP6_BIT	BIT(2)
#घोषणा MVPP22_FLOW_TCP_BIT	BIT(3)
#घोषणा MVPP22_FLOW_UDP_BIT	BIT(4)

#घोषणा MVPP22_FLOW_TCP4	(MVPP22_FLOW_ETHER_BIT | MVPP22_FLOW_IP4_BIT | MVPP22_FLOW_TCP_BIT)
#घोषणा MVPP22_FLOW_TCP6	(MVPP22_FLOW_ETHER_BIT | MVPP22_FLOW_IP6_BIT | MVPP22_FLOW_TCP_BIT)
#घोषणा MVPP22_FLOW_UDP4	(MVPP22_FLOW_ETHER_BIT | MVPP22_FLOW_IP4_BIT | MVPP22_FLOW_UDP_BIT)
#घोषणा MVPP22_FLOW_UDP6	(MVPP22_FLOW_ETHER_BIT | MVPP22_FLOW_IP6_BIT | MVPP22_FLOW_UDP_BIT)
#घोषणा MVPP22_FLOW_IP4		(MVPP22_FLOW_ETHER_BIT | MVPP22_FLOW_IP4_BIT)
#घोषणा MVPP22_FLOW_IP6		(MVPP22_FLOW_ETHER_BIT | MVPP22_FLOW_IP6_BIT)
#घोषणा MVPP22_FLOW_ETHERNET	(MVPP22_FLOW_ETHER_BIT)

/* Classअगरier C2 engine entries */
#घोषणा MVPP22_CLS_C2_N_ENTRIES		256

/* Number of per-port dedicated entries in the C2 TCAM */
#घोषणा MVPP22_CLS_C2_PORT_N_FLOWS	MVPP2_N_RFS_ENTRIES_PER_FLOW

/* Each port has one range per flow type + one entry controlling the global RSS
 * setting and the शेष rx queue
 */
#घोषणा MVPP22_CLS_C2_PORT_RANGE	(MVPP22_CLS_C2_PORT_N_FLOWS + 1)
#घोषणा MVPP22_CLS_C2_PORT_FIRST(p)	((p) * MVPP22_CLS_C2_PORT_RANGE)
#घोषणा MVPP22_CLS_C2_RSS_ENTRY(p)	(MVPP22_CLS_C2_PORT_FIRST((p) + 1) - 1)

#घोषणा MVPP22_CLS_C2_PORT_FLOW_FIRST(p)	(MVPP22_CLS_C2_PORT_FIRST(p))

#घोषणा MVPP22_CLS_C2_RFS_LOC(p, loc)	(MVPP22_CLS_C2_PORT_FLOW_FIRST(p) + (loc))

/* Packet flow ID */
क्रमागत mvpp2_prs_flow अणु
	MVPP2_FL_START = 8,
	MVPP2_FL_IP4_TCP_NF_UNTAG = MVPP2_FL_START,
	MVPP2_FL_IP4_UDP_NF_UNTAG,
	MVPP2_FL_IP4_TCP_NF_TAG,
	MVPP2_FL_IP4_UDP_NF_TAG,
	MVPP2_FL_IP6_TCP_NF_UNTAG,
	MVPP2_FL_IP6_UDP_NF_UNTAG,
	MVPP2_FL_IP6_TCP_NF_TAG,
	MVPP2_FL_IP6_UDP_NF_TAG,
	MVPP2_FL_IP4_TCP_FRAG_UNTAG,
	MVPP2_FL_IP4_UDP_FRAG_UNTAG,
	MVPP2_FL_IP4_TCP_FRAG_TAG,
	MVPP2_FL_IP4_UDP_FRAG_TAG,
	MVPP2_FL_IP6_TCP_FRAG_UNTAG,
	MVPP2_FL_IP6_UDP_FRAG_UNTAG,
	MVPP2_FL_IP6_TCP_FRAG_TAG,
	MVPP2_FL_IP6_UDP_FRAG_TAG,
	MVPP2_FL_IP4_UNTAG, /* non-TCP, non-UDP, same क्रम below */
	MVPP2_FL_IP4_TAG,
	MVPP2_FL_IP6_UNTAG,
	MVPP2_FL_IP6_TAG,
	MVPP2_FL_NON_IP_UNTAG,
	MVPP2_FL_NON_IP_TAG,
	MVPP2_FL_LAST,
पूर्ण;

/* LU Type defined क्रम all engines, and specअगरied in the flow table */
#घोषणा MVPP2_CLS_LU_TYPE_MASK			0x3f

क्रमागत mvpp2_cls_lu_type अणु
	/* rule->loc is used as a lu-type क्रम the entries 0 - 62. */
	MVPP22_CLS_LU_TYPE_ALL = 63,
पूर्ण;

#घोषणा MVPP2_N_FLOWS		(MVPP2_FL_LAST - MVPP2_FL_START)

काष्ठा mvpp2_cls_flow अणु
	/* The L2-L4 traffic flow type */
	पूर्णांक flow_type;

	/* The first id in the flow table क्रम this flow */
	u16 flow_id;

	/* The supported HEK fields क्रम this flow */
	u16 supported_hash_opts;

	/* The Header Parser result_info that matches this flow */
	काष्ठा mvpp2_prs_result_info prs_ri;
पूर्ण;

#घोषणा MVPP2_CLS_FLT_ENTRIES_PER_FLOW		(MVPP2_MAX_PORTS + 1 + 16)
#घोषणा MVPP2_CLS_FLT_FIRST(id)			(((id) - MVPP2_FL_START) * \
						 MVPP2_CLS_FLT_ENTRIES_PER_FLOW)

#घोषणा MVPP2_CLS_FLT_C2_RFS(port, id, rfs_n)	(MVPP2_CLS_FLT_FIRST(id) + \
						 ((port) * MVPP2_MAX_PORTS) + \
						 (rfs_n))

#घोषणा MVPP2_CLS_FLT_C2_RSS_ENTRY(id)		(MVPP2_CLS_FLT_C2_RFS(MVPP2_MAX_PORTS, id, 0))
#घोषणा MVPP2_CLS_FLT_HASH_ENTRY(port, id)	(MVPP2_CLS_FLT_C2_RSS_ENTRY(id) + 1 + (port))
#घोषणा MVPP2_CLS_FLT_LAST(id)			(MVPP2_CLS_FLT_FIRST(id) + \
						 MVPP2_CLS_FLT_ENTRIES_PER_FLOW - 1)

/* Iterate on each classअगरier flow id. Sets 'i' to be the index of the first
 * entry in the cls_flows table क्रम each dअगरferent flow_id.
 * This relies on entries having the same flow_id in the cls_flows table being
 * contiguous.
 */
#घोषणा क्रम_each_cls_flow_id(i)						      \
	क्रम ((i) = 0; (i) < MVPP2_N_PRS_FLOWS; (i)++)			      \
		अगर ((i) > 0 &&						      \
		    cls_flows[(i)].flow_id == cls_flows[(i) - 1].flow_id)       \
			जारी;					      \
		अन्यथा

/* Iterate on each classअगरier flow that has a given flow_type. Sets 'i' to be
 * the index of the first entry in the cls_flow table क्रम each dअगरferent flow_id
 * that has the given flow_type. This allows to operate on all flows that
 * matches a given ethtool flow type.
 */
#घोषणा क्रम_each_cls_flow_id_with_type(i, type)				      \
	क्रम_each_cls_flow_id((i))					      \
		अगर (cls_flows[(i)].flow_type != (type))			      \
			जारी;					      \
		अन्यथा

#घोषणा क्रम_each_cls_flow_id_containing_type(i, type)			      \
	क्रम_each_cls_flow_id((i))					      \
		अगर ((cls_flows[(i)].flow_type & (type)) != (type))	      \
			जारी;					      \
		अन्यथा

काष्ठा mvpp2_cls_flow_entry अणु
	u32 index;
	u32 data[MVPP2_CLS_FLOWS_TBL_DATA_WORDS];
पूर्ण;

काष्ठा mvpp2_cls_lookup_entry अणु
	u32 lkpid;
	u32 way;
	u32 data;
पूर्ण;

पूर्णांक mvpp22_port_rss_init(काष्ठा mvpp2_port *port);

पूर्णांक mvpp22_port_rss_enable(काष्ठा mvpp2_port *port);
पूर्णांक mvpp22_port_rss_disable(काष्ठा mvpp2_port *port);

पूर्णांक mvpp22_port_rss_ctx_create(काष्ठा mvpp2_port *port, u32 *rss_ctx);
पूर्णांक mvpp22_port_rss_ctx_delete(काष्ठा mvpp2_port *port, u32 rss_ctx);

पूर्णांक mvpp22_port_rss_ctx_indir_set(काष्ठा mvpp2_port *port, u32 rss_ctx,
				  स्थिर u32 *indir);
पूर्णांक mvpp22_port_rss_ctx_indir_get(काष्ठा mvpp2_port *port, u32 rss_ctx,
				  u32 *indir);

पूर्णांक mvpp2_ethtool_rxfh_get(काष्ठा mvpp2_port *port, काष्ठा ethtool_rxnfc *info);
पूर्णांक mvpp2_ethtool_rxfh_set(काष्ठा mvpp2_port *port, काष्ठा ethtool_rxnfc *info);

व्योम mvpp2_cls_init(काष्ठा mvpp2 *priv);

व्योम mvpp2_cls_port_config(काष्ठा mvpp2_port *port);

व्योम mvpp2_cls_oversize_rxq_set(काष्ठा mvpp2_port *port);

पूर्णांक mvpp2_cls_flow_eng_get(काष्ठा mvpp2_cls_flow_entry *fe);

u16 mvpp2_flow_get_hek_fields(काष्ठा mvpp2_cls_flow_entry *fe);

स्थिर काष्ठा mvpp2_cls_flow *mvpp2_cls_flow_get(पूर्णांक flow);

u32 mvpp2_cls_flow_hits(काष्ठा mvpp2 *priv, पूर्णांक index);

व्योम mvpp2_cls_flow_पढ़ो(काष्ठा mvpp2 *priv, पूर्णांक index,
			 काष्ठा mvpp2_cls_flow_entry *fe);

u32 mvpp2_cls_lookup_hits(काष्ठा mvpp2 *priv, पूर्णांक index);

व्योम mvpp2_cls_lookup_पढ़ो(काष्ठा mvpp2 *priv, पूर्णांक lkpid, पूर्णांक way,
			   काष्ठा mvpp2_cls_lookup_entry *le);

u32 mvpp2_cls_c2_hit_count(काष्ठा mvpp2 *priv, पूर्णांक c2_index);

व्योम mvpp2_cls_c2_पढ़ो(काष्ठा mvpp2 *priv, पूर्णांक index,
		       काष्ठा mvpp2_cls_c2_entry *c2);

पूर्णांक mvpp2_ethtool_cls_rule_get(काष्ठा mvpp2_port *port,
			       काष्ठा ethtool_rxnfc *rxnfc);

पूर्णांक mvpp2_ethtool_cls_rule_ins(काष्ठा mvpp2_port *port,
			       काष्ठा ethtool_rxnfc *info);

पूर्णांक mvpp2_ethtool_cls_rule_del(काष्ठा mvpp2_port *port,
			       काष्ठा ethtool_rxnfc *info);

#पूर्ण_अगर
