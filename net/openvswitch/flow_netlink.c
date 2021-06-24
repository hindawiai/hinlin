<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2017 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "flow.h"
#समावेश "datapath.h"
#समावेश <linux/uaccess.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/llc_pdu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/llc.h>
#समावेश <linux/module.h>
#समावेश <linux/in.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/sctp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/rculist.h>
#समावेश <net/geneve.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/mpls.h>
#समावेश <net/vxlan.h>
#समावेश <net/tun_proto.h>
#समावेश <net/erspan.h>

#समावेश "flow_netlink.h"

काष्ठा ovs_len_tbl अणु
	पूर्णांक len;
	स्थिर काष्ठा ovs_len_tbl *next;
पूर्ण;

#घोषणा OVS_ATTR_NESTED -1
#घोषणा OVS_ATTR_VARIABLE -2

अटल bool actions_may_change_flow(स्थिर काष्ठा nlattr *actions)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक rem;

	nla_क्रम_each_nested(nla, actions, rem) अणु
		u16 action = nla_type(nla);

		चयन (action) अणु
		हाल OVS_ACTION_ATTR_OUTPUT:
		हाल OVS_ACTION_ATTR_RECIRC:
		हाल OVS_ACTION_ATTR_TRUNC:
		हाल OVS_ACTION_ATTR_USERSPACE:
			अवरोध;

		हाल OVS_ACTION_ATTR_CT:
		हाल OVS_ACTION_ATTR_CT_CLEAR:
		हाल OVS_ACTION_ATTR_HASH:
		हाल OVS_ACTION_ATTR_POP_ETH:
		हाल OVS_ACTION_ATTR_POP_MPLS:
		हाल OVS_ACTION_ATTR_POP_NSH:
		हाल OVS_ACTION_ATTR_POP_VLAN:
		हाल OVS_ACTION_ATTR_PUSH_ETH:
		हाल OVS_ACTION_ATTR_PUSH_MPLS:
		हाल OVS_ACTION_ATTR_PUSH_NSH:
		हाल OVS_ACTION_ATTR_PUSH_VLAN:
		हाल OVS_ACTION_ATTR_SAMPLE:
		हाल OVS_ACTION_ATTR_SET:
		हाल OVS_ACTION_ATTR_SET_MASKED:
		हाल OVS_ACTION_ATTR_METER:
		हाल OVS_ACTION_ATTR_CHECK_PKT_LEN:
		हाल OVS_ACTION_ATTR_ADD_MPLS:
		हाल OVS_ACTION_ATTR_DEC_TTL:
		शेष:
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम update_range(काष्ठा sw_flow_match *match,
			 माप_प्रकार offset, माप_प्रकार size, bool is_mask)
अणु
	काष्ठा sw_flow_key_range *range;
	माप_प्रकार start = roundकरोwn(offset, माप(दीर्घ));
	माप_प्रकार end = roundup(offset + size, माप(दीर्घ));

	अगर (!is_mask)
		range = &match->range;
	अन्यथा
		range = &match->mask->range;

	अगर (range->start == range->end) अणु
		range->start = start;
		range->end = end;
		वापस;
	पूर्ण

	अगर (range->start > start)
		range->start = start;

	अगर (range->end < end)
		range->end = end;
पूर्ण

#घोषणा SW_FLOW_KEY_PUT(match, field, value, is_mask) \
	करो अणु \
		update_range(match, दुरत्व(काष्ठा sw_flow_key, field),    \
			     माप((match)->key->field), is_mask);	    \
		अगर (is_mask)						    \
			(match)->mask->key.field = value;		    \
		अन्यथा							    \
			(match)->key->field = value;		            \
	पूर्ण जबतक (0)

#घोषणा SW_FLOW_KEY_MEMCPY_OFFSET(match, offset, value_p, len, is_mask)	    \
	करो अणु								    \
		update_range(match, offset, len, is_mask);		    \
		अगर (is_mask)						    \
			स_नकल((u8 *)&(match)->mask->key + offset, value_p, \
			       len);					   \
		अन्यथा							    \
			स_नकल((u8 *)(match)->key + offset, value_p, len);  \
	पूर्ण जबतक (0)

#घोषणा SW_FLOW_KEY_MEMCPY(match, field, value_p, len, is_mask)		      \
	SW_FLOW_KEY_MEMCPY_OFFSET(match, दुरत्व(काष्ठा sw_flow_key, field), \
				  value_p, len, is_mask)

#घोषणा SW_FLOW_KEY_MEMSET_FIELD(match, field, value, is_mask)		    \
	करो अणु								    \
		update_range(match, दुरत्व(काष्ठा sw_flow_key, field),    \
			     माप((match)->key->field), is_mask);	    \
		अगर (is_mask)						    \
			स_रखो((u8 *)&(match)->mask->key.field, value,      \
			       माप((match)->mask->key.field));	    \
		अन्यथा							    \
			स_रखो((u8 *)&(match)->key->field, value,           \
			       माप((match)->key->field));                \
	पूर्ण जबतक (0)

अटल bool match_validate(स्थिर काष्ठा sw_flow_match *match,
			   u64 key_attrs, u64 mask_attrs, bool log)
अणु
	u64 key_expected = 0;
	u64 mask_allowed = key_attrs;  /* At most allow all key attributes */

	/* The following mask attributes allowed only अगर they
	 * pass the validation tests. */
	mask_allowed &= ~((1 << OVS_KEY_ATTR_IPV4)
			| (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4)
			| (1 << OVS_KEY_ATTR_IPV6)
			| (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6)
			| (1 << OVS_KEY_ATTR_TCP)
			| (1 << OVS_KEY_ATTR_TCP_FLAGS)
			| (1 << OVS_KEY_ATTR_UDP)
			| (1 << OVS_KEY_ATTR_SCTP)
			| (1 << OVS_KEY_ATTR_ICMP)
			| (1 << OVS_KEY_ATTR_ICMPV6)
			| (1 << OVS_KEY_ATTR_ARP)
			| (1 << OVS_KEY_ATTR_ND)
			| (1 << OVS_KEY_ATTR_MPLS)
			| (1 << OVS_KEY_ATTR_NSH));

	/* Always allowed mask fields. */
	mask_allowed |= ((1 << OVS_KEY_ATTR_TUNNEL)
		       | (1 << OVS_KEY_ATTR_IN_PORT)
		       | (1 << OVS_KEY_ATTR_ETHERTYPE));

	/* Check key attributes. */
	अगर (match->key->eth.type == htons(ETH_P_ARP)
			|| match->key->eth.type == htons(ETH_P_RARP)) अणु
		key_expected |= 1 << OVS_KEY_ATTR_ARP;
		अगर (match->mask && (match->mask->key.eth.type == htons(0xffff)))
			mask_allowed |= 1 << OVS_KEY_ATTR_ARP;
	पूर्ण

	अगर (eth_p_mpls(match->key->eth.type)) अणु
		key_expected |= 1 << OVS_KEY_ATTR_MPLS;
		अगर (match->mask && (match->mask->key.eth.type == htons(0xffff)))
			mask_allowed |= 1 << OVS_KEY_ATTR_MPLS;
	पूर्ण

	अगर (match->key->eth.type == htons(ETH_P_IP)) अणु
		key_expected |= 1 << OVS_KEY_ATTR_IPV4;
		अगर (match->mask && match->mask->key.eth.type == htons(0xffff)) अणु
			mask_allowed |= 1 << OVS_KEY_ATTR_IPV4;
			mask_allowed |= 1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4;
		पूर्ण

		अगर (match->key->ip.frag != OVS_FRAG_TYPE_LATER) अणु
			अगर (match->key->ip.proto == IPPROTO_UDP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_UDP;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_UDP;
			पूर्ण

			अगर (match->key->ip.proto == IPPROTO_SCTP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_SCTP;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_SCTP;
			पूर्ण

			अगर (match->key->ip.proto == IPPROTO_TCP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_TCP;
				key_expected |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff)) अणु
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP;
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				पूर्ण
			पूर्ण

			अगर (match->key->ip.proto == IPPROTO_ICMP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_ICMP;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_ICMP;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (match->key->eth.type == htons(ETH_P_IPV6)) अणु
		key_expected |= 1 << OVS_KEY_ATTR_IPV6;
		अगर (match->mask && match->mask->key.eth.type == htons(0xffff)) अणु
			mask_allowed |= 1 << OVS_KEY_ATTR_IPV6;
			mask_allowed |= 1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6;
		पूर्ण

		अगर (match->key->ip.frag != OVS_FRAG_TYPE_LATER) अणु
			अगर (match->key->ip.proto == IPPROTO_UDP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_UDP;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_UDP;
			पूर्ण

			अगर (match->key->ip.proto == IPPROTO_SCTP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_SCTP;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_SCTP;
			पूर्ण

			अगर (match->key->ip.proto == IPPROTO_TCP) अणु
				key_expected |= 1 << OVS_KEY_ATTR_TCP;
				key_expected |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff)) अणु
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP;
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				पूर्ण
			पूर्ण

			अगर (match->key->ip.proto == IPPROTO_ICMPV6) अणु
				key_expected |= 1 << OVS_KEY_ATTR_ICMPV6;
				अगर (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_ICMPV6;

				अगर (match->key->tp.src ==
						htons(NDISC_NEIGHBOUR_SOLICITATION) ||
				    match->key->tp.src == htons(NDISC_NEIGHBOUR_ADVERTISEMENT)) अणु
					key_expected |= 1 << OVS_KEY_ATTR_ND;
					/* Original direction conntrack tuple
					 * uses the same space as the ND fields
					 * in the key, so both are not allowed
					 * at the same समय.
					 */
					mask_allowed &= ~(1ULL << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6);
					अगर (match->mask && (match->mask->key.tp.src == htons(0xff)))
						mask_allowed |= 1 << OVS_KEY_ATTR_ND;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (match->key->eth.type == htons(ETH_P_NSH)) अणु
		key_expected |= 1 << OVS_KEY_ATTR_NSH;
		अगर (match->mask &&
		    match->mask->key.eth.type == htons(0xffff)) अणु
			mask_allowed |= 1 << OVS_KEY_ATTR_NSH;
		पूर्ण
	पूर्ण

	अगर ((key_attrs & key_expected) != key_expected) अणु
		/* Key attributes check failed. */
		OVS_NLERR(log, "Missing key (keys=%llx, expected=%llx)",
			  (अचिन्हित दीर्घ दीर्घ)key_attrs,
			  (अचिन्हित दीर्घ दीर्घ)key_expected);
		वापस false;
	पूर्ण

	अगर ((mask_attrs & mask_allowed) != mask_attrs) अणु
		/* Mask attributes check failed. */
		OVS_NLERR(log, "Unexpected mask (mask=%llx, allowed=%llx)",
			  (अचिन्हित दीर्घ दीर्घ)mask_attrs,
			  (अचिन्हित दीर्घ दीर्घ)mask_allowed);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

माप_प्रकार ovs_tun_key_attr_size(व्योम)
अणु
	/* Whenever adding new OVS_TUNNEL_KEY_ FIELDS, we should consider
	 * updating this function.
	 */
	वापस    nla_total_size_64bit(8) /* OVS_TUNNEL_KEY_ATTR_ID */
		+ nla_total_size(16)   /* OVS_TUNNEL_KEY_ATTR_IPV[46]_SRC */
		+ nla_total_size(16)   /* OVS_TUNNEL_KEY_ATTR_IPV[46]_DST */
		+ nla_total_size(1)    /* OVS_TUNNEL_KEY_ATTR_TOS */
		+ nla_total_size(1)    /* OVS_TUNNEL_KEY_ATTR_TTL */
		+ nla_total_size(0)    /* OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT */
		+ nla_total_size(0)    /* OVS_TUNNEL_KEY_ATTR_CSUM */
		+ nla_total_size(0)    /* OVS_TUNNEL_KEY_ATTR_OAM */
		+ nla_total_size(256)  /* OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS */
		/* OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS and
		 * OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS is mutually exclusive with
		 * OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS and covered by it.
		 */
		+ nla_total_size(2)    /* OVS_TUNNEL_KEY_ATTR_TP_SRC */
		+ nla_total_size(2);   /* OVS_TUNNEL_KEY_ATTR_TP_DST */
पूर्ण

अटल माप_प्रकार ovs_nsh_key_attr_size(व्योम)
अणु
	/* Whenever adding new OVS_NSH_KEY_ FIELDS, we should consider
	 * updating this function.
	 */
	वापस  nla_total_size(NSH_BASE_HDR_LEN) /* OVS_NSH_KEY_ATTR_BASE */
		/* OVS_NSH_KEY_ATTR_MD1 and OVS_NSH_KEY_ATTR_MD2 are
		 * mutually exclusive, so the bigger one can cover
		 * the small one.
		 */
		+ nla_total_size(NSH_CTX_HDRS_MAX_LEN);
पूर्ण

माप_प्रकार ovs_key_attr_size(व्योम)
अणु
	/* Whenever adding new OVS_KEY_ FIELDS, we should consider
	 * updating this function.
	 */
	BUILD_BUG_ON(OVS_KEY_ATTR_TUNNEL_INFO != 29);

	वापस    nla_total_size(4)   /* OVS_KEY_ATTR_PRIORITY */
		+ nla_total_size(0)   /* OVS_KEY_ATTR_TUNNEL */
		  + ovs_tun_key_attr_size()
		+ nla_total_size(4)   /* OVS_KEY_ATTR_IN_PORT */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_SKB_MARK */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_DP_HASH */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_RECIRC_ID */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_CT_STATE */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_CT_ZONE */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_CT_MARK */
		+ nla_total_size(16)  /* OVS_KEY_ATTR_CT_LABELS */
		+ nla_total_size(40)  /* OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6 */
		+ nla_total_size(0)   /* OVS_KEY_ATTR_NSH */
		  + ovs_nsh_key_attr_size()
		+ nla_total_size(12)  /* OVS_KEY_ATTR_ETHERNET */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_ETHERTYPE */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_VLAN */
		+ nla_total_size(0)   /* OVS_KEY_ATTR_ENCAP */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_ETHERTYPE */
		+ nla_total_size(40)  /* OVS_KEY_ATTR_IPV6 */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_ICMPV6 */
		+ nla_total_size(28); /* OVS_KEY_ATTR_ND */
पूर्ण

अटल स्थिर काष्ठा ovs_len_tbl ovs_vxlan_ext_key_lens[OVS_VXLAN_EXT_MAX + 1] = अणु
	[OVS_VXLAN_EXT_GBP]	    = अणु .len = माप(u32) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ovs_len_tbl ovs_tunnel_key_lens[OVS_TUNNEL_KEY_ATTR_MAX + 1] = अणु
	[OVS_TUNNEL_KEY_ATTR_ID]	    = अणु .len = माप(u64) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_IPV4_SRC]	    = अणु .len = माप(u32) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_IPV4_DST]	    = अणु .len = माप(u32) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_TOS]	    = अणु .len = 1 पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_TTL]	    = अणु .len = 1 पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT] = अणु .len = 0 पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_CSUM]	    = अणु .len = 0 पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_TP_SRC]	    = अणु .len = माप(u16) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_TP_DST]	    = अणु .len = माप(u16) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_OAM]	    = अणु .len = 0 पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS]   = अणु .len = OVS_ATTR_VARIABLE पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS]    = अणु .len = OVS_ATTR_NESTED,
						.next = ovs_vxlan_ext_key_lens पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_IPV6_SRC]      = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_IPV6_DST]      = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS]   = अणु .len = OVS_ATTR_VARIABLE पूर्ण,
	[OVS_TUNNEL_KEY_ATTR_IPV4_INFO_BRIDGE]   = अणु .len = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ovs_len_tbl
ovs_nsh_key_attr_lens[OVS_NSH_KEY_ATTR_MAX + 1] = अणु
	[OVS_NSH_KEY_ATTR_BASE] = अणु .len = माप(काष्ठा ovs_nsh_key_base) पूर्ण,
	[OVS_NSH_KEY_ATTR_MD1]  = अणु .len = माप(काष्ठा ovs_nsh_key_md1) पूर्ण,
	[OVS_NSH_KEY_ATTR_MD2]  = अणु .len = OVS_ATTR_VARIABLE पूर्ण,
पूर्ण;

/* The size of the argument क्रम each %OVS_KEY_ATTR_* Netlink attribute.  */
अटल स्थिर काष्ठा ovs_len_tbl ovs_key_lens[OVS_KEY_ATTR_MAX + 1] = अणु
	[OVS_KEY_ATTR_ENCAP]	 = अणु .len = OVS_ATTR_NESTED पूर्ण,
	[OVS_KEY_ATTR_PRIORITY]	 = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_IN_PORT]	 = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_SKB_MARK]	 = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_ETHERNET]	 = अणु .len = माप(काष्ठा ovs_key_ethernet) पूर्ण,
	[OVS_KEY_ATTR_VLAN]	 = अणु .len = माप(__be16) पूर्ण,
	[OVS_KEY_ATTR_ETHERTYPE] = अणु .len = माप(__be16) पूर्ण,
	[OVS_KEY_ATTR_IPV4]	 = अणु .len = माप(काष्ठा ovs_key_ipv4) पूर्ण,
	[OVS_KEY_ATTR_IPV6]	 = अणु .len = माप(काष्ठा ovs_key_ipv6) पूर्ण,
	[OVS_KEY_ATTR_TCP]	 = अणु .len = माप(काष्ठा ovs_key_tcp) पूर्ण,
	[OVS_KEY_ATTR_TCP_FLAGS] = अणु .len = माप(__be16) पूर्ण,
	[OVS_KEY_ATTR_UDP]	 = अणु .len = माप(काष्ठा ovs_key_udp) पूर्ण,
	[OVS_KEY_ATTR_SCTP]	 = अणु .len = माप(काष्ठा ovs_key_sctp) पूर्ण,
	[OVS_KEY_ATTR_ICMP]	 = अणु .len = माप(काष्ठा ovs_key_icmp) पूर्ण,
	[OVS_KEY_ATTR_ICMPV6]	 = अणु .len = माप(काष्ठा ovs_key_icmpv6) पूर्ण,
	[OVS_KEY_ATTR_ARP]	 = अणु .len = माप(काष्ठा ovs_key_arp) पूर्ण,
	[OVS_KEY_ATTR_ND]	 = अणु .len = माप(काष्ठा ovs_key_nd) पूर्ण,
	[OVS_KEY_ATTR_RECIRC_ID] = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_DP_HASH]	 = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_TUNNEL]	 = अणु .len = OVS_ATTR_NESTED,
				     .next = ovs_tunnel_key_lens, पूर्ण,
	[OVS_KEY_ATTR_MPLS]	 = अणु .len = OVS_ATTR_VARIABLE पूर्ण,
	[OVS_KEY_ATTR_CT_STATE]	 = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_CT_ZONE]	 = अणु .len = माप(u16) पूर्ण,
	[OVS_KEY_ATTR_CT_MARK]	 = अणु .len = माप(u32) पूर्ण,
	[OVS_KEY_ATTR_CT_LABELS] = अणु .len = माप(काष्ठा ovs_key_ct_labels) पूर्ण,
	[OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4] = अणु
		.len = माप(काष्ठा ovs_key_ct_tuple_ipv4) पूर्ण,
	[OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6] = अणु
		.len = माप(काष्ठा ovs_key_ct_tuple_ipv6) पूर्ण,
	[OVS_KEY_ATTR_NSH]       = अणु .len = OVS_ATTR_NESTED,
				     .next = ovs_nsh_key_attr_lens, पूर्ण,
पूर्ण;

अटल bool check_attr_len(अचिन्हित पूर्णांक attr_len, अचिन्हित पूर्णांक expected_len)
अणु
	वापस expected_len == attr_len ||
	       expected_len == OVS_ATTR_NESTED ||
	       expected_len == OVS_ATTR_VARIABLE;
पूर्ण

अटल bool is_all_zero(स्थिर u8 *fp, माप_प्रकार size)
अणु
	पूर्णांक i;

	अगर (!fp)
		वापस false;

	क्रम (i = 0; i < size; i++)
		अगर (fp[i])
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __parse_flow_nlattrs(स्थिर काष्ठा nlattr *attr,
				स्थिर काष्ठा nlattr *a[],
				u64 *attrsp, bool log, bool nz)
अणु
	स्थिर काष्ठा nlattr *nla;
	u64 attrs;
	पूर्णांक rem;

	attrs = *attrsp;
	nla_क्रम_each_nested(nla, attr, rem) अणु
		u16 type = nla_type(nla);
		पूर्णांक expected_len;

		अगर (type > OVS_KEY_ATTR_MAX) अणु
			OVS_NLERR(log, "Key type %d is out of range max %d",
				  type, OVS_KEY_ATTR_MAX);
			वापस -EINVAL;
		पूर्ण

		अगर (attrs & (1 << type)) अणु
			OVS_NLERR(log, "Duplicate key (type %d).", type);
			वापस -EINVAL;
		पूर्ण

		expected_len = ovs_key_lens[type].len;
		अगर (!check_attr_len(nla_len(nla), expected_len)) अणु
			OVS_NLERR(log, "Key %d has unexpected len %d expected %d",
				  type, nla_len(nla), expected_len);
			वापस -EINVAL;
		पूर्ण

		अगर (!nz || !is_all_zero(nla_data(nla), nla_len(nla))) अणु
			attrs |= 1 << type;
			a[type] = nla;
		पूर्ण
	पूर्ण
	अगर (rem) अणु
		OVS_NLERR(log, "Message has %d unknown bytes.", rem);
		वापस -EINVAL;
	पूर्ण

	*attrsp = attrs;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_flow_mask_nlattrs(स्थिर काष्ठा nlattr *attr,
				   स्थिर काष्ठा nlattr *a[], u64 *attrsp,
				   bool log)
अणु
	वापस __parse_flow_nlattrs(attr, a, attrsp, log, true);
पूर्ण

पूर्णांक parse_flow_nlattrs(स्थिर काष्ठा nlattr *attr, स्थिर काष्ठा nlattr *a[],
		       u64 *attrsp, bool log)
अणु
	वापस __parse_flow_nlattrs(attr, a, attrsp, log, false);
पूर्ण

अटल पूर्णांक genev_tun_opt_from_nlattr(स्थिर काष्ठा nlattr *a,
				     काष्ठा sw_flow_match *match, bool is_mask,
				     bool log)
अणु
	अचिन्हित दीर्घ opt_key_offset;

	अगर (nla_len(a) > माप(match->key->tun_opts)) अणु
		OVS_NLERR(log, "Geneve option length err (len %d, max %zu).",
			  nla_len(a), माप(match->key->tun_opts));
		वापस -EINVAL;
	पूर्ण

	अगर (nla_len(a) % 4 != 0) अणु
		OVS_NLERR(log, "Geneve opt len %d is not a multiple of 4.",
			  nla_len(a));
		वापस -EINVAL;
	पूर्ण

	/* We need to record the length of the options passed
	 * करोwn, otherwise packets with the same क्रमmat but
	 * additional options will be silently matched.
	 */
	अगर (!is_mask) अणु
		SW_FLOW_KEY_PUT(match, tun_opts_len, nla_len(a),
				false);
	पूर्ण अन्यथा अणु
		/* This is somewhat unusual because it looks at
		 * both the key and mask जबतक parsing the
		 * attributes (and by extension assumes the key
		 * is parsed first). Normally, we would verअगरy
		 * that each is the correct length and that the
		 * attributes line up in the validate function.
		 * However, that is dअगरficult because this is
		 * variable length and we won't have the
		 * inक्रमmation later.
		 */
		अगर (match->key->tun_opts_len != nla_len(a)) अणु
			OVS_NLERR(log, "Geneve option len %d != mask len %d",
				  match->key->tun_opts_len, nla_len(a));
			वापस -EINVAL;
		पूर्ण

		SW_FLOW_KEY_PUT(match, tun_opts_len, 0xff, true);
	पूर्ण

	opt_key_offset = TUN_METADATA_OFFSET(nla_len(a));
	SW_FLOW_KEY_MEMCPY_OFFSET(match, opt_key_offset, nla_data(a),
				  nla_len(a), is_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक vxlan_tun_opt_from_nlattr(स्थिर काष्ठा nlattr *attr,
				     काष्ठा sw_flow_match *match, bool is_mask,
				     bool log)
अणु
	काष्ठा nlattr *a;
	पूर्णांक rem;
	अचिन्हित दीर्घ opt_key_offset;
	काष्ठा vxlan_metadata opts;

	BUILD_BUG_ON(माप(opts) > माप(match->key->tun_opts));

	स_रखो(&opts, 0, माप(opts));
	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);

		अगर (type > OVS_VXLAN_EXT_MAX) अणु
			OVS_NLERR(log, "VXLAN extension %d out of range max %d",
				  type, OVS_VXLAN_EXT_MAX);
			वापस -EINVAL;
		पूर्ण

		अगर (!check_attr_len(nla_len(a),
				    ovs_vxlan_ext_key_lens[type].len)) अणु
			OVS_NLERR(log, "VXLAN extension %d has unexpected len %d expected %d",
				  type, nla_len(a),
				  ovs_vxlan_ext_key_lens[type].len);
			वापस -EINVAL;
		पूर्ण

		चयन (type) अणु
		हाल OVS_VXLAN_EXT_GBP:
			opts.gbp = nla_get_u32(a);
			अवरोध;
		शेष:
			OVS_NLERR(log, "Unknown VXLAN extension attribute %d",
				  type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (rem) अणु
		OVS_NLERR(log, "VXLAN extension message has %d unknown bytes.",
			  rem);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_mask)
		SW_FLOW_KEY_PUT(match, tun_opts_len, माप(opts), false);
	अन्यथा
		SW_FLOW_KEY_PUT(match, tun_opts_len, 0xff, true);

	opt_key_offset = TUN_METADATA_OFFSET(माप(opts));
	SW_FLOW_KEY_MEMCPY_OFFSET(match, opt_key_offset, &opts, माप(opts),
				  is_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक erspan_tun_opt_from_nlattr(स्थिर काष्ठा nlattr *a,
				      काष्ठा sw_flow_match *match, bool is_mask,
				      bool log)
अणु
	अचिन्हित दीर्घ opt_key_offset;

	BUILD_BUG_ON(माप(काष्ठा erspan_metadata) >
		     माप(match->key->tun_opts));

	अगर (nla_len(a) > माप(match->key->tun_opts)) अणु
		OVS_NLERR(log, "ERSPAN option length err (len %d, max %zu).",
			  nla_len(a), माप(match->key->tun_opts));
		वापस -EINVAL;
	पूर्ण

	अगर (!is_mask)
		SW_FLOW_KEY_PUT(match, tun_opts_len,
				माप(काष्ठा erspan_metadata), false);
	अन्यथा
		SW_FLOW_KEY_PUT(match, tun_opts_len, 0xff, true);

	opt_key_offset = TUN_METADATA_OFFSET(nla_len(a));
	SW_FLOW_KEY_MEMCPY_OFFSET(match, opt_key_offset, nla_data(a),
				  nla_len(a), is_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक ip_tun_from_nlattr(स्थिर काष्ठा nlattr *attr,
			      काष्ठा sw_flow_match *match, bool is_mask,
			      bool log)
अणु
	bool ttl = false, ipv4 = false, ipv6 = false;
	bool info_bridge_mode = false;
	__be16 tun_flags = 0;
	पूर्णांक opts_type = 0;
	काष्ठा nlattr *a;
	पूर्णांक rem;

	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);
		पूर्णांक err;

		अगर (type > OVS_TUNNEL_KEY_ATTR_MAX) अणु
			OVS_NLERR(log, "Tunnel attr %d out of range max %d",
				  type, OVS_TUNNEL_KEY_ATTR_MAX);
			वापस -EINVAL;
		पूर्ण

		अगर (!check_attr_len(nla_len(a),
				    ovs_tunnel_key_lens[type].len)) अणु
			OVS_NLERR(log, "Tunnel attr %d has unexpected len %d expected %d",
				  type, nla_len(a), ovs_tunnel_key_lens[type].len);
			वापस -EINVAL;
		पूर्ण

		चयन (type) अणु
		हाल OVS_TUNNEL_KEY_ATTR_ID:
			SW_FLOW_KEY_PUT(match, tun_key.tun_id,
					nla_get_be64(a), is_mask);
			tun_flags |= TUNNEL_KEY;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_IPV4_SRC:
			SW_FLOW_KEY_PUT(match, tun_key.u.ipv4.src,
					nla_get_in_addr(a), is_mask);
			ipv4 = true;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_IPV4_DST:
			SW_FLOW_KEY_PUT(match, tun_key.u.ipv4.dst,
					nla_get_in_addr(a), is_mask);
			ipv4 = true;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_IPV6_SRC:
			SW_FLOW_KEY_PUT(match, tun_key.u.ipv6.src,
					nla_get_in6_addr(a), is_mask);
			ipv6 = true;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_IPV6_DST:
			SW_FLOW_KEY_PUT(match, tun_key.u.ipv6.dst,
					nla_get_in6_addr(a), is_mask);
			ipv6 = true;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_TOS:
			SW_FLOW_KEY_PUT(match, tun_key.tos,
					nla_get_u8(a), is_mask);
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_TTL:
			SW_FLOW_KEY_PUT(match, tun_key.ttl,
					nla_get_u8(a), is_mask);
			ttl = true;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT:
			tun_flags |= TUNNEL_DONT_FRAGMENT;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_CSUM:
			tun_flags |= TUNNEL_CSUM;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_TP_SRC:
			SW_FLOW_KEY_PUT(match, tun_key.tp_src,
					nla_get_be16(a), is_mask);
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_TP_DST:
			SW_FLOW_KEY_PUT(match, tun_key.tp_dst,
					nla_get_be16(a), is_mask);
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_OAM:
			tun_flags |= TUNNEL_OAM;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS:
			अगर (opts_type) अणु
				OVS_NLERR(log, "Multiple metadata blocks provided");
				वापस -EINVAL;
			पूर्ण

			err = genev_tun_opt_from_nlattr(a, match, is_mask, log);
			अगर (err)
				वापस err;

			tun_flags |= TUNNEL_GENEVE_OPT;
			opts_type = type;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS:
			अगर (opts_type) अणु
				OVS_NLERR(log, "Multiple metadata blocks provided");
				वापस -EINVAL;
			पूर्ण

			err = vxlan_tun_opt_from_nlattr(a, match, is_mask, log);
			अगर (err)
				वापस err;

			tun_flags |= TUNNEL_VXLAN_OPT;
			opts_type = type;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_PAD:
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS:
			अगर (opts_type) अणु
				OVS_NLERR(log, "Multiple metadata blocks provided");
				वापस -EINVAL;
			पूर्ण

			err = erspan_tun_opt_from_nlattr(a, match, is_mask,
							 log);
			अगर (err)
				वापस err;

			tun_flags |= TUNNEL_ERSPAN_OPT;
			opts_type = type;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_IPV4_INFO_BRIDGE:
			info_bridge_mode = true;
			ipv4 = true;
			अवरोध;
		शेष:
			OVS_NLERR(log, "Unknown IP tunnel attribute %d",
				  type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	SW_FLOW_KEY_PUT(match, tun_key.tun_flags, tun_flags, is_mask);
	अगर (is_mask)
		SW_FLOW_KEY_MEMSET_FIELD(match, tun_proto, 0xff, true);
	अन्यथा
		SW_FLOW_KEY_PUT(match, tun_proto, ipv6 ? AF_INET6 : AF_INET,
				false);

	अगर (rem > 0) अणु
		OVS_NLERR(log, "IP tunnel attribute has %d unknown bytes.",
			  rem);
		वापस -EINVAL;
	पूर्ण

	अगर (ipv4 && ipv6) अणु
		OVS_NLERR(log, "Mixed IPv4 and IPv6 tunnel attributes");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_mask) अणु
		अगर (!ipv4 && !ipv6) अणु
			OVS_NLERR(log, "IP tunnel dst address not specified");
			वापस -EINVAL;
		पूर्ण
		अगर (ipv4) अणु
			अगर (info_bridge_mode) अणु
				अगर (match->key->tun_key.u.ipv4.src ||
				    match->key->tun_key.u.ipv4.dst ||
				    match->key->tun_key.tp_src ||
				    match->key->tun_key.tp_dst ||
				    match->key->tun_key.ttl ||
				    match->key->tun_key.tos ||
				    tun_flags & ~TUNNEL_KEY) अणु
					OVS_NLERR(log, "IPv4 tun info is not correct");
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अगर (!match->key->tun_key.u.ipv4.dst) अणु
				OVS_NLERR(log, "IPv4 tunnel dst address is zero");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (ipv6 && ipv6_addr_any(&match->key->tun_key.u.ipv6.dst)) अणु
			OVS_NLERR(log, "IPv6 tunnel dst address is zero");
			वापस -EINVAL;
		पूर्ण

		अगर (!ttl && !info_bridge_mode) अणु
			OVS_NLERR(log, "IP tunnel TTL not specified.");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस opts_type;
पूर्ण

अटल पूर्णांक vxlan_opt_to_nlattr(काष्ठा sk_buff *skb,
			       स्थिर व्योम *tun_opts, पूर्णांक swkey_tun_opts_len)
अणु
	स्थिर काष्ठा vxlan_metadata *opts = tun_opts;
	काष्ठा nlattr *nla;

	nla = nla_nest_start_noflag(skb, OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS);
	अगर (!nla)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, OVS_VXLAN_EXT_GBP, opts->gbp) < 0)
		वापस -EMSGSIZE;

	nla_nest_end(skb, nla);
	वापस 0;
पूर्ण

अटल पूर्णांक __ip_tun_to_nlattr(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा ip_tunnel_key *output,
			      स्थिर व्योम *tun_opts, पूर्णांक swkey_tun_opts_len,
			      अचिन्हित लघु tun_proto, u8 mode)
अणु
	अगर (output->tun_flags & TUNNEL_KEY &&
	    nla_put_be64(skb, OVS_TUNNEL_KEY_ATTR_ID, output->tun_id,
			 OVS_TUNNEL_KEY_ATTR_PAD))
		वापस -EMSGSIZE;

	अगर (mode & IP_TUNNEL_INFO_BRIDGE)
		वापस nla_put_flag(skb, OVS_TUNNEL_KEY_ATTR_IPV4_INFO_BRIDGE)
		       ? -EMSGSIZE : 0;

	चयन (tun_proto) अणु
	हाल AF_INET:
		अगर (output->u.ipv4.src &&
		    nla_put_in_addr(skb, OVS_TUNNEL_KEY_ATTR_IPV4_SRC,
				    output->u.ipv4.src))
			वापस -EMSGSIZE;
		अगर (output->u.ipv4.dst &&
		    nla_put_in_addr(skb, OVS_TUNNEL_KEY_ATTR_IPV4_DST,
				    output->u.ipv4.dst))
			वापस -EMSGSIZE;
		अवरोध;
	हाल AF_INET6:
		अगर (!ipv6_addr_any(&output->u.ipv6.src) &&
		    nla_put_in6_addr(skb, OVS_TUNNEL_KEY_ATTR_IPV6_SRC,
				     &output->u.ipv6.src))
			वापस -EMSGSIZE;
		अगर (!ipv6_addr_any(&output->u.ipv6.dst) &&
		    nla_put_in6_addr(skb, OVS_TUNNEL_KEY_ATTR_IPV6_DST,
				     &output->u.ipv6.dst))
			वापस -EMSGSIZE;
		अवरोध;
	पूर्ण
	अगर (output->tos &&
	    nla_put_u8(skb, OVS_TUNNEL_KEY_ATTR_TOS, output->tos))
		वापस -EMSGSIZE;
	अगर (nla_put_u8(skb, OVS_TUNNEL_KEY_ATTR_TTL, output->ttl))
		वापस -EMSGSIZE;
	अगर ((output->tun_flags & TUNNEL_DONT_FRAGMENT) &&
	    nla_put_flag(skb, OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT))
		वापस -EMSGSIZE;
	अगर ((output->tun_flags & TUNNEL_CSUM) &&
	    nla_put_flag(skb, OVS_TUNNEL_KEY_ATTR_CSUM))
		वापस -EMSGSIZE;
	अगर (output->tp_src &&
	    nla_put_be16(skb, OVS_TUNNEL_KEY_ATTR_TP_SRC, output->tp_src))
		वापस -EMSGSIZE;
	अगर (output->tp_dst &&
	    nla_put_be16(skb, OVS_TUNNEL_KEY_ATTR_TP_DST, output->tp_dst))
		वापस -EMSGSIZE;
	अगर ((output->tun_flags & TUNNEL_OAM) &&
	    nla_put_flag(skb, OVS_TUNNEL_KEY_ATTR_OAM))
		वापस -EMSGSIZE;
	अगर (swkey_tun_opts_len) अणु
		अगर (output->tun_flags & TUNNEL_GENEVE_OPT &&
		    nla_put(skb, OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS,
			    swkey_tun_opts_len, tun_opts))
			वापस -EMSGSIZE;
		अन्यथा अगर (output->tun_flags & TUNNEL_VXLAN_OPT &&
			 vxlan_opt_to_nlattr(skb, tun_opts, swkey_tun_opts_len))
			वापस -EMSGSIZE;
		अन्यथा अगर (output->tun_flags & TUNNEL_ERSPAN_OPT &&
			 nla_put(skb, OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS,
				 swkey_tun_opts_len, tun_opts))
			वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip_tun_to_nlattr(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ip_tunnel_key *output,
			    स्थिर व्योम *tun_opts, पूर्णांक swkey_tun_opts_len,
			    अचिन्हित लघु tun_proto, u8 mode)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक err;

	nla = nla_nest_start_noflag(skb, OVS_KEY_ATTR_TUNNEL);
	अगर (!nla)
		वापस -EMSGSIZE;

	err = __ip_tun_to_nlattr(skb, output, tun_opts, swkey_tun_opts_len,
				 tun_proto, mode);
	अगर (err)
		वापस err;

	nla_nest_end(skb, nla);
	वापस 0;
पूर्ण

पूर्णांक ovs_nla_put_tunnel_info(काष्ठा sk_buff *skb,
			    काष्ठा ip_tunnel_info *tun_info)
अणु
	वापस __ip_tun_to_nlattr(skb, &tun_info->key,
				  ip_tunnel_info_opts(tun_info),
				  tun_info->options_len,
				  ip_tunnel_info_af(tun_info), tun_info->mode);
पूर्ण

अटल पूर्णांक encode_vlan_from_nlattrs(काष्ठा sw_flow_match *match,
				    स्थिर काष्ठा nlattr *a[],
				    bool is_mask, bool inner)
अणु
	__be16 tci = 0;
	__be16 tpid = 0;

	अगर (a[OVS_KEY_ATTR_VLAN])
		tci = nla_get_be16(a[OVS_KEY_ATTR_VLAN]);

	अगर (a[OVS_KEY_ATTR_ETHERTYPE])
		tpid = nla_get_be16(a[OVS_KEY_ATTR_ETHERTYPE]);

	अगर (likely(!inner)) अणु
		SW_FLOW_KEY_PUT(match, eth.vlan.tpid, tpid, is_mask);
		SW_FLOW_KEY_PUT(match, eth.vlan.tci, tci, is_mask);
	पूर्ण अन्यथा अणु
		SW_FLOW_KEY_PUT(match, eth.cvlan.tpid, tpid, is_mask);
		SW_FLOW_KEY_PUT(match, eth.cvlan.tci, tci, is_mask);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक validate_vlan_from_nlattrs(स्थिर काष्ठा sw_flow_match *match,
				      u64 key_attrs, bool inner,
				      स्थिर काष्ठा nlattr **a, bool log)
अणु
	__be16 tci = 0;

	अगर (!((key_attrs & (1 << OVS_KEY_ATTR_ETHERNET)) &&
	      (key_attrs & (1 << OVS_KEY_ATTR_ETHERTYPE)) &&
	       eth_type_vlan(nla_get_be16(a[OVS_KEY_ATTR_ETHERTYPE])))) अणु
		/* Not a VLAN. */
		वापस 0;
	पूर्ण

	अगर (!((key_attrs & (1 << OVS_KEY_ATTR_VLAN)) &&
	      (key_attrs & (1 << OVS_KEY_ATTR_ENCAP)))) अणु
		OVS_NLERR(log, "Invalid %s frame", (inner) ? "C-VLAN" : "VLAN");
		वापस -EINVAL;
	पूर्ण

	अगर (a[OVS_KEY_ATTR_VLAN])
		tci = nla_get_be16(a[OVS_KEY_ATTR_VLAN]);

	अगर (!(tci & htons(VLAN_CFI_MASK))) अणु
		अगर (tci) अणु
			OVS_NLERR(log, "%s TCI does not have VLAN_CFI_MASK bit set.",
				  (inner) ? "C-VLAN" : "VLAN");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (nla_len(a[OVS_KEY_ATTR_ENCAP])) अणु
			/* Corner हाल क्रम truncated VLAN header. */
			OVS_NLERR(log, "Truncated %s header has non-zero encap attribute.",
				  (inner) ? "C-VLAN" : "VLAN");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक validate_vlan_mask_from_nlattrs(स्थिर काष्ठा sw_flow_match *match,
					   u64 key_attrs, bool inner,
					   स्थिर काष्ठा nlattr **a, bool log)
अणु
	__be16 tci = 0;
	__be16 tpid = 0;
	bool encap_valid = !!(match->key->eth.vlan.tci &
			      htons(VLAN_CFI_MASK));
	bool i_encap_valid = !!(match->key->eth.cvlan.tci &
				htons(VLAN_CFI_MASK));

	अगर (!(key_attrs & (1 << OVS_KEY_ATTR_ENCAP))) अणु
		/* Not a VLAN. */
		वापस 0;
	पूर्ण

	अगर ((!inner && !encap_valid) || (inner && !i_encap_valid)) अणु
		OVS_NLERR(log, "Encap mask attribute is set for non-%s frame.",
			  (inner) ? "C-VLAN" : "VLAN");
		वापस -EINVAL;
	पूर्ण

	अगर (a[OVS_KEY_ATTR_VLAN])
		tci = nla_get_be16(a[OVS_KEY_ATTR_VLAN]);

	अगर (a[OVS_KEY_ATTR_ETHERTYPE])
		tpid = nla_get_be16(a[OVS_KEY_ATTR_ETHERTYPE]);

	अगर (tpid != htons(0xffff)) अणु
		OVS_NLERR(log, "Must have an exact match on %s TPID (mask=%x).",
			  (inner) ? "C-VLAN" : "VLAN", ntohs(tpid));
		वापस -EINVAL;
	पूर्ण
	अगर (!(tci & htons(VLAN_CFI_MASK))) अणु
		OVS_NLERR(log, "%s TCI mask does not have exact match for VLAN_CFI_MASK bit.",
			  (inner) ? "C-VLAN" : "VLAN");
		वापस -EINVAL;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक __parse_vlan_from_nlattrs(काष्ठा sw_flow_match *match,
				     u64 *key_attrs, bool inner,
				     स्थिर काष्ठा nlattr **a, bool is_mask,
				     bool log)
अणु
	पूर्णांक err;
	स्थिर काष्ठा nlattr *encap;

	अगर (!is_mask)
		err = validate_vlan_from_nlattrs(match, *key_attrs, inner,
						 a, log);
	अन्यथा
		err = validate_vlan_mask_from_nlattrs(match, *key_attrs, inner,
						      a, log);
	अगर (err <= 0)
		वापस err;

	err = encode_vlan_from_nlattrs(match, a, is_mask, inner);
	अगर (err)
		वापस err;

	*key_attrs &= ~(1 << OVS_KEY_ATTR_ENCAP);
	*key_attrs &= ~(1 << OVS_KEY_ATTR_VLAN);
	*key_attrs &= ~(1 << OVS_KEY_ATTR_ETHERTYPE);

	encap = a[OVS_KEY_ATTR_ENCAP];

	अगर (!is_mask)
		err = parse_flow_nlattrs(encap, a, key_attrs, log);
	अन्यथा
		err = parse_flow_mask_nlattrs(encap, a, key_attrs, log);

	वापस err;
पूर्ण

अटल पूर्णांक parse_vlan_from_nlattrs(काष्ठा sw_flow_match *match,
				   u64 *key_attrs, स्थिर काष्ठा nlattr **a,
				   bool is_mask, bool log)
अणु
	पूर्णांक err;
	bool encap_valid = false;

	err = __parse_vlan_from_nlattrs(match, key_attrs, false, a,
					is_mask, log);
	अगर (err)
		वापस err;

	encap_valid = !!(match->key->eth.vlan.tci & htons(VLAN_CFI_MASK));
	अगर (encap_valid) अणु
		err = __parse_vlan_from_nlattrs(match, key_attrs, true, a,
						is_mask, log);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_eth_type_from_nlattrs(काष्ठा sw_flow_match *match,
				       u64 *attrs, स्थिर काष्ठा nlattr **a,
				       bool is_mask, bool log)
अणु
	__be16 eth_type;

	eth_type = nla_get_be16(a[OVS_KEY_ATTR_ETHERTYPE]);
	अगर (is_mask) अणु
		/* Always exact match EtherType. */
		eth_type = htons(0xffff);
	पूर्ण अन्यथा अगर (!eth_proto_is_802_3(eth_type)) अणु
		OVS_NLERR(log, "EtherType %x is less than min %x",
				ntohs(eth_type), ETH_P_802_3_MIN);
		वापस -EINVAL;
	पूर्ण

	SW_FLOW_KEY_PUT(match, eth.type, eth_type, is_mask);
	*attrs &= ~(1 << OVS_KEY_ATTR_ETHERTYPE);
	वापस 0;
पूर्ण

अटल पूर्णांक metadata_from_nlattrs(काष्ठा net *net, काष्ठा sw_flow_match *match,
				 u64 *attrs, स्थिर काष्ठा nlattr **a,
				 bool is_mask, bool log)
अणु
	u8 mac_proto = MAC_PROTO_ETHERNET;

	अगर (*attrs & (1 << OVS_KEY_ATTR_DP_HASH)) अणु
		u32 hash_val = nla_get_u32(a[OVS_KEY_ATTR_DP_HASH]);

		SW_FLOW_KEY_PUT(match, ovs_flow_hash, hash_val, is_mask);
		*attrs &= ~(1 << OVS_KEY_ATTR_DP_HASH);
	पूर्ण

	अगर (*attrs & (1 << OVS_KEY_ATTR_RECIRC_ID)) अणु
		u32 recirc_id = nla_get_u32(a[OVS_KEY_ATTR_RECIRC_ID]);

		SW_FLOW_KEY_PUT(match, recirc_id, recirc_id, is_mask);
		*attrs &= ~(1 << OVS_KEY_ATTR_RECIRC_ID);
	पूर्ण

	अगर (*attrs & (1 << OVS_KEY_ATTR_PRIORITY)) अणु
		SW_FLOW_KEY_PUT(match, phy.priority,
			  nla_get_u32(a[OVS_KEY_ATTR_PRIORITY]), is_mask);
		*attrs &= ~(1 << OVS_KEY_ATTR_PRIORITY);
	पूर्ण

	अगर (*attrs & (1 << OVS_KEY_ATTR_IN_PORT)) अणु
		u32 in_port = nla_get_u32(a[OVS_KEY_ATTR_IN_PORT]);

		अगर (is_mask) अणु
			in_port = 0xffffffff; /* Always exact match in_port. */
		पूर्ण अन्यथा अगर (in_port >= DP_MAX_PORTS) अणु
			OVS_NLERR(log, "Port %d exceeds max allowable %d",
				  in_port, DP_MAX_PORTS);
			वापस -EINVAL;
		पूर्ण

		SW_FLOW_KEY_PUT(match, phy.in_port, in_port, is_mask);
		*attrs &= ~(1 << OVS_KEY_ATTR_IN_PORT);
	पूर्ण अन्यथा अगर (!is_mask) अणु
		SW_FLOW_KEY_PUT(match, phy.in_port, DP_MAX_PORTS, is_mask);
	पूर्ण

	अगर (*attrs & (1 << OVS_KEY_ATTR_SKB_MARK)) अणु
		uपूर्णांक32_t mark = nla_get_u32(a[OVS_KEY_ATTR_SKB_MARK]);

		SW_FLOW_KEY_PUT(match, phy.skb_mark, mark, is_mask);
		*attrs &= ~(1 << OVS_KEY_ATTR_SKB_MARK);
	पूर्ण
	अगर (*attrs & (1 << OVS_KEY_ATTR_TUNNEL)) अणु
		अगर (ip_tun_from_nlattr(a[OVS_KEY_ATTR_TUNNEL], match,
				       is_mask, log) < 0)
			वापस -EINVAL;
		*attrs &= ~(1 << OVS_KEY_ATTR_TUNNEL);
	पूर्ण

	अगर (*attrs & (1 << OVS_KEY_ATTR_CT_STATE) &&
	    ovs_ct_verअगरy(net, OVS_KEY_ATTR_CT_STATE)) अणु
		u32 ct_state = nla_get_u32(a[OVS_KEY_ATTR_CT_STATE]);

		अगर (ct_state & ~CT_SUPPORTED_MASK) अणु
			OVS_NLERR(log, "ct_state flags %08x unsupported",
				  ct_state);
			वापस -EINVAL;
		पूर्ण

		SW_FLOW_KEY_PUT(match, ct_state, ct_state, is_mask);
		*attrs &= ~(1ULL << OVS_KEY_ATTR_CT_STATE);
	पूर्ण
	अगर (*attrs & (1 << OVS_KEY_ATTR_CT_ZONE) &&
	    ovs_ct_verअगरy(net, OVS_KEY_ATTR_CT_ZONE)) अणु
		u16 ct_zone = nla_get_u16(a[OVS_KEY_ATTR_CT_ZONE]);

		SW_FLOW_KEY_PUT(match, ct_zone, ct_zone, is_mask);
		*attrs &= ~(1ULL << OVS_KEY_ATTR_CT_ZONE);
	पूर्ण
	अगर (*attrs & (1 << OVS_KEY_ATTR_CT_MARK) &&
	    ovs_ct_verअगरy(net, OVS_KEY_ATTR_CT_MARK)) अणु
		u32 mark = nla_get_u32(a[OVS_KEY_ATTR_CT_MARK]);

		SW_FLOW_KEY_PUT(match, ct.mark, mark, is_mask);
		*attrs &= ~(1ULL << OVS_KEY_ATTR_CT_MARK);
	पूर्ण
	अगर (*attrs & (1 << OVS_KEY_ATTR_CT_LABELS) &&
	    ovs_ct_verअगरy(net, OVS_KEY_ATTR_CT_LABELS)) अणु
		स्थिर काष्ठा ovs_key_ct_labels *cl;

		cl = nla_data(a[OVS_KEY_ATTR_CT_LABELS]);
		SW_FLOW_KEY_MEMCPY(match, ct.labels, cl->ct_labels,
				   माप(*cl), is_mask);
		*attrs &= ~(1ULL << OVS_KEY_ATTR_CT_LABELS);
	पूर्ण
	अगर (*attrs & (1ULL << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4)) अणु
		स्थिर काष्ठा ovs_key_ct_tuple_ipv4 *ct;

		ct = nla_data(a[OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4]);

		SW_FLOW_KEY_PUT(match, ipv4.ct_orig.src, ct->ipv4_src, is_mask);
		SW_FLOW_KEY_PUT(match, ipv4.ct_orig.dst, ct->ipv4_dst, is_mask);
		SW_FLOW_KEY_PUT(match, ct.orig_tp.src, ct->src_port, is_mask);
		SW_FLOW_KEY_PUT(match, ct.orig_tp.dst, ct->dst_port, is_mask);
		SW_FLOW_KEY_PUT(match, ct_orig_proto, ct->ipv4_proto, is_mask);
		*attrs &= ~(1ULL << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4);
	पूर्ण
	अगर (*attrs & (1ULL << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6)) अणु
		स्थिर काष्ठा ovs_key_ct_tuple_ipv6 *ct;

		ct = nla_data(a[OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6]);

		SW_FLOW_KEY_MEMCPY(match, ipv6.ct_orig.src, &ct->ipv6_src,
				   माप(match->key->ipv6.ct_orig.src),
				   is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv6.ct_orig.dst, &ct->ipv6_dst,
				   माप(match->key->ipv6.ct_orig.dst),
				   is_mask);
		SW_FLOW_KEY_PUT(match, ct.orig_tp.src, ct->src_port, is_mask);
		SW_FLOW_KEY_PUT(match, ct.orig_tp.dst, ct->dst_port, is_mask);
		SW_FLOW_KEY_PUT(match, ct_orig_proto, ct->ipv6_proto, is_mask);
		*attrs &= ~(1ULL << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6);
	पूर्ण

	/* For layer 3 packets the Ethernet type is provided
	 * and treated as metadata but no MAC addresses are provided.
	 */
	अगर (!(*attrs & (1ULL << OVS_KEY_ATTR_ETHERNET)) &&
	    (*attrs & (1ULL << OVS_KEY_ATTR_ETHERTYPE)))
		mac_proto = MAC_PROTO_NONE;

	/* Always exact match mac_proto */
	SW_FLOW_KEY_PUT(match, mac_proto, is_mask ? 0xff : mac_proto, is_mask);

	अगर (mac_proto == MAC_PROTO_NONE)
		वापस parse_eth_type_from_nlattrs(match, attrs, a, is_mask,
						   log);

	वापस 0;
पूर्ण

पूर्णांक nsh_hdr_from_nlattr(स्थिर काष्ठा nlattr *attr,
			काष्ठा nshhdr *nh, माप_प्रकार size)
अणु
	काष्ठा nlattr *a;
	पूर्णांक rem;
	u8 flags = 0;
	u8 ttl = 0;
	पूर्णांक mdlen = 0;

	/* validate_nsh has check this, so we needn't करो duplicate check here
	 */
	अगर (size < NSH_BASE_HDR_LEN)
		वापस -ENOBUFS;

	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);

		चयन (type) अणु
		हाल OVS_NSH_KEY_ATTR_BASE: अणु
			स्थिर काष्ठा ovs_nsh_key_base *base = nla_data(a);

			flags = base->flags;
			ttl = base->ttl;
			nh->np = base->np;
			nh->mdtype = base->mdtype;
			nh->path_hdr = base->path_hdr;
			अवरोध;
		पूर्ण
		हाल OVS_NSH_KEY_ATTR_MD1:
			mdlen = nla_len(a);
			अगर (mdlen > size - NSH_BASE_HDR_LEN)
				वापस -ENOBUFS;
			स_नकल(&nh->md1, nla_data(a), mdlen);
			अवरोध;

		हाल OVS_NSH_KEY_ATTR_MD2:
			mdlen = nla_len(a);
			अगर (mdlen > size - NSH_BASE_HDR_LEN)
				वापस -ENOBUFS;
			स_नकल(&nh->md2, nla_data(a), mdlen);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* nsh header length  = NSH_BASE_HDR_LEN + mdlen */
	nh->ver_flags_ttl_len = 0;
	nsh_set_flags_ttl_len(nh, flags, ttl, NSH_BASE_HDR_LEN + mdlen);

	वापस 0;
पूर्ण

पूर्णांक nsh_key_from_nlattr(स्थिर काष्ठा nlattr *attr,
			काष्ठा ovs_key_nsh *nsh, काष्ठा ovs_key_nsh *nsh_mask)
अणु
	काष्ठा nlattr *a;
	पूर्णांक rem;

	/* validate_nsh has check this, so we needn't करो duplicate check here
	 */
	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);

		चयन (type) अणु
		हाल OVS_NSH_KEY_ATTR_BASE: अणु
			स्थिर काष्ठा ovs_nsh_key_base *base = nla_data(a);
			स्थिर काष्ठा ovs_nsh_key_base *base_mask = base + 1;

			nsh->base = *base;
			nsh_mask->base = *base_mask;
			अवरोध;
		पूर्ण
		हाल OVS_NSH_KEY_ATTR_MD1: अणु
			स्थिर काष्ठा ovs_nsh_key_md1 *md1 = nla_data(a);
			स्थिर काष्ठा ovs_nsh_key_md1 *md1_mask = md1 + 1;

			स_नकल(nsh->context, md1->context, माप(*md1));
			स_नकल(nsh_mask->context, md1_mask->context,
			       माप(*md1_mask));
			अवरोध;
		पूर्ण
		हाल OVS_NSH_KEY_ATTR_MD2:
			/* Not supported yet */
			वापस -ENOTSUPP;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nsh_key_put_from_nlattr(स्थिर काष्ठा nlattr *attr,
				   काष्ठा sw_flow_match *match, bool is_mask,
				   bool is_push_nsh, bool log)
अणु
	काष्ठा nlattr *a;
	पूर्णांक rem;
	bool has_base = false;
	bool has_md1 = false;
	bool has_md2 = false;
	u8 mdtype = 0;
	पूर्णांक mdlen = 0;

	अगर (WARN_ON(is_push_nsh && is_mask))
		वापस -EINVAL;

	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);
		पूर्णांक i;

		अगर (type > OVS_NSH_KEY_ATTR_MAX) अणु
			OVS_NLERR(log, "nsh attr %d is out of range max %d",
				  type, OVS_NSH_KEY_ATTR_MAX);
			वापस -EINVAL;
		पूर्ण

		अगर (!check_attr_len(nla_len(a),
				    ovs_nsh_key_attr_lens[type].len)) अणु
			OVS_NLERR(
			    log,
			    "nsh attr %d has unexpected len %d expected %d",
			    type,
			    nla_len(a),
			    ovs_nsh_key_attr_lens[type].len
			);
			वापस -EINVAL;
		पूर्ण

		चयन (type) अणु
		हाल OVS_NSH_KEY_ATTR_BASE: अणु
			स्थिर काष्ठा ovs_nsh_key_base *base = nla_data(a);

			has_base = true;
			mdtype = base->mdtype;
			SW_FLOW_KEY_PUT(match, nsh.base.flags,
					base->flags, is_mask);
			SW_FLOW_KEY_PUT(match, nsh.base.ttl,
					base->ttl, is_mask);
			SW_FLOW_KEY_PUT(match, nsh.base.mdtype,
					base->mdtype, is_mask);
			SW_FLOW_KEY_PUT(match, nsh.base.np,
					base->np, is_mask);
			SW_FLOW_KEY_PUT(match, nsh.base.path_hdr,
					base->path_hdr, is_mask);
			अवरोध;
		पूर्ण
		हाल OVS_NSH_KEY_ATTR_MD1: अणु
			स्थिर काष्ठा ovs_nsh_key_md1 *md1 = nla_data(a);

			has_md1 = true;
			क्रम (i = 0; i < NSH_MD1_CONTEXT_SIZE; i++)
				SW_FLOW_KEY_PUT(match, nsh.context[i],
						md1->context[i], is_mask);
			अवरोध;
		पूर्ण
		हाल OVS_NSH_KEY_ATTR_MD2:
			अगर (!is_push_nsh) /* Not supported MD type 2 yet */
				वापस -ENOTSUPP;

			has_md2 = true;
			mdlen = nla_len(a);
			अगर (mdlen > NSH_CTX_HDRS_MAX_LEN || mdlen <= 0) अणु
				OVS_NLERR(
				    log,
				    "Invalid MD length %d for MD type %d",
				    mdlen,
				    mdtype
				);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			OVS_NLERR(log, "Unknown nsh attribute %d",
				  type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (rem > 0) अणु
		OVS_NLERR(log, "nsh attribute has %d unknown bytes.", rem);
		वापस -EINVAL;
	पूर्ण

	अगर (has_md1 && has_md2) अणु
		OVS_NLERR(
		    1,
		    "invalid nsh attribute: md1 and md2 are exclusive."
		);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_mask) अणु
		अगर ((has_md1 && mdtype != NSH_M_TYPE1) ||
		    (has_md2 && mdtype != NSH_M_TYPE2)) अणु
			OVS_NLERR(1, "nsh attribute has unmatched MD type %d.",
				  mdtype);
			वापस -EINVAL;
		पूर्ण

		अगर (is_push_nsh &&
		    (!has_base || (!has_md1 && !has_md2))) अणु
			OVS_NLERR(
			    1,
			    "push_nsh: missing base or metadata attributes"
			);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_key_from_nlattrs(काष्ठा net *net, काष्ठा sw_flow_match *match,
				u64 attrs, स्थिर काष्ठा nlattr **a,
				bool is_mask, bool log)
अणु
	पूर्णांक err;

	err = metadata_from_nlattrs(net, match, &attrs, a, is_mask, log);
	अगर (err)
		वापस err;

	अगर (attrs & (1 << OVS_KEY_ATTR_ETHERNET)) अणु
		स्थिर काष्ठा ovs_key_ethernet *eth_key;

		eth_key = nla_data(a[OVS_KEY_ATTR_ETHERNET]);
		SW_FLOW_KEY_MEMCPY(match, eth.src,
				eth_key->eth_src, ETH_ALEN, is_mask);
		SW_FLOW_KEY_MEMCPY(match, eth.dst,
				eth_key->eth_dst, ETH_ALEN, is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_ETHERNET);

		अगर (attrs & (1 << OVS_KEY_ATTR_VLAN)) अणु
			/* VLAN attribute is always parsed beक्रमe getting here since it
			 * may occur multiple बार.
			 */
			OVS_NLERR(log, "VLAN attribute unexpected.");
			वापस -EINVAL;
		पूर्ण

		अगर (attrs & (1 << OVS_KEY_ATTR_ETHERTYPE)) अणु
			err = parse_eth_type_from_nlattrs(match, &attrs, a, is_mask,
							  log);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (!is_mask) अणु
			SW_FLOW_KEY_PUT(match, eth.type, htons(ETH_P_802_2), is_mask);
		पूर्ण
	पूर्ण अन्यथा अगर (!match->key->eth.type) अणु
		OVS_NLERR(log, "Either Ethernet header or EtherType is required.");
		वापस -EINVAL;
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_IPV4)) अणु
		स्थिर काष्ठा ovs_key_ipv4 *ipv4_key;

		ipv4_key = nla_data(a[OVS_KEY_ATTR_IPV4]);
		अगर (!is_mask && ipv4_key->ipv4_frag > OVS_FRAG_TYPE_MAX) अणु
			OVS_NLERR(log, "IPv4 frag type %d is out of range max %d",
				  ipv4_key->ipv4_frag, OVS_FRAG_TYPE_MAX);
			वापस -EINVAL;
		पूर्ण
		SW_FLOW_KEY_PUT(match, ip.proto,
				ipv4_key->ipv4_proto, is_mask);
		SW_FLOW_KEY_PUT(match, ip.tos,
				ipv4_key->ipv4_tos, is_mask);
		SW_FLOW_KEY_PUT(match, ip.ttl,
				ipv4_key->ipv4_ttl, is_mask);
		SW_FLOW_KEY_PUT(match, ip.frag,
				ipv4_key->ipv4_frag, is_mask);
		SW_FLOW_KEY_PUT(match, ipv4.addr.src,
				ipv4_key->ipv4_src, is_mask);
		SW_FLOW_KEY_PUT(match, ipv4.addr.dst,
				ipv4_key->ipv4_dst, is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_IPV4);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_IPV6)) अणु
		स्थिर काष्ठा ovs_key_ipv6 *ipv6_key;

		ipv6_key = nla_data(a[OVS_KEY_ATTR_IPV6]);
		अगर (!is_mask && ipv6_key->ipv6_frag > OVS_FRAG_TYPE_MAX) अणु
			OVS_NLERR(log, "IPv6 frag type %d is out of range max %d",
				  ipv6_key->ipv6_frag, OVS_FRAG_TYPE_MAX);
			वापस -EINVAL;
		पूर्ण

		अगर (!is_mask && ipv6_key->ipv6_label & htonl(0xFFF00000)) अणु
			OVS_NLERR(log, "IPv6 flow label %x is out of range (max=%x)",
				  ntohl(ipv6_key->ipv6_label), (1 << 20) - 1);
			वापस -EINVAL;
		पूर्ण

		SW_FLOW_KEY_PUT(match, ipv6.label,
				ipv6_key->ipv6_label, is_mask);
		SW_FLOW_KEY_PUT(match, ip.proto,
				ipv6_key->ipv6_proto, is_mask);
		SW_FLOW_KEY_PUT(match, ip.tos,
				ipv6_key->ipv6_tclass, is_mask);
		SW_FLOW_KEY_PUT(match, ip.ttl,
				ipv6_key->ipv6_hlimit, is_mask);
		SW_FLOW_KEY_PUT(match, ip.frag,
				ipv6_key->ipv6_frag, is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv6.addr.src,
				ipv6_key->ipv6_src,
				माप(match->key->ipv6.addr.src),
				is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv6.addr.dst,
				ipv6_key->ipv6_dst,
				माप(match->key->ipv6.addr.dst),
				is_mask);

		attrs &= ~(1 << OVS_KEY_ATTR_IPV6);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_ARP)) अणु
		स्थिर काष्ठा ovs_key_arp *arp_key;

		arp_key = nla_data(a[OVS_KEY_ATTR_ARP]);
		अगर (!is_mask && (arp_key->arp_op & htons(0xff00))) अणु
			OVS_NLERR(log, "Unknown ARP opcode (opcode=%d).",
				  arp_key->arp_op);
			वापस -EINVAL;
		पूर्ण

		SW_FLOW_KEY_PUT(match, ipv4.addr.src,
				arp_key->arp_sip, is_mask);
		SW_FLOW_KEY_PUT(match, ipv4.addr.dst,
			arp_key->arp_tip, is_mask);
		SW_FLOW_KEY_PUT(match, ip.proto,
				ntohs(arp_key->arp_op), is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv4.arp.sha,
				arp_key->arp_sha, ETH_ALEN, is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv4.arp.tha,
				arp_key->arp_tha, ETH_ALEN, is_mask);

		attrs &= ~(1 << OVS_KEY_ATTR_ARP);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_NSH)) अणु
		अगर (nsh_key_put_from_nlattr(a[OVS_KEY_ATTR_NSH], match,
					    is_mask, false, log) < 0)
			वापस -EINVAL;
		attrs &= ~(1 << OVS_KEY_ATTR_NSH);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_MPLS)) अणु
		स्थिर काष्ठा ovs_key_mpls *mpls_key;
		u32 hdr_len;
		u32 label_count, label_count_mask, i;

		mpls_key = nla_data(a[OVS_KEY_ATTR_MPLS]);
		hdr_len = nla_len(a[OVS_KEY_ATTR_MPLS]);
		label_count = hdr_len / माप(काष्ठा ovs_key_mpls);

		अगर (label_count == 0 || label_count > MPLS_LABEL_DEPTH ||
		    hdr_len % माप(काष्ठा ovs_key_mpls))
			वापस -EINVAL;

		label_count_mask =  GENMASK(label_count - 1, 0);

		क्रम (i = 0 ; i < label_count; i++)
			SW_FLOW_KEY_PUT(match, mpls.lse[i],
					mpls_key[i].mpls_lse, is_mask);

		SW_FLOW_KEY_PUT(match, mpls.num_labels_mask,
				label_count_mask, is_mask);

		attrs &= ~(1 << OVS_KEY_ATTR_MPLS);
	 पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_TCP)) अणु
		स्थिर काष्ठा ovs_key_tcp *tcp_key;

		tcp_key = nla_data(a[OVS_KEY_ATTR_TCP]);
		SW_FLOW_KEY_PUT(match, tp.src, tcp_key->tcp_src, is_mask);
		SW_FLOW_KEY_PUT(match, tp.dst, tcp_key->tcp_dst, is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_TCP);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_TCP_FLAGS)) अणु
		SW_FLOW_KEY_PUT(match, tp.flags,
				nla_get_be16(a[OVS_KEY_ATTR_TCP_FLAGS]),
				is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_TCP_FLAGS);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_UDP)) अणु
		स्थिर काष्ठा ovs_key_udp *udp_key;

		udp_key = nla_data(a[OVS_KEY_ATTR_UDP]);
		SW_FLOW_KEY_PUT(match, tp.src, udp_key->udp_src, is_mask);
		SW_FLOW_KEY_PUT(match, tp.dst, udp_key->udp_dst, is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_UDP);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_SCTP)) अणु
		स्थिर काष्ठा ovs_key_sctp *sctp_key;

		sctp_key = nla_data(a[OVS_KEY_ATTR_SCTP]);
		SW_FLOW_KEY_PUT(match, tp.src, sctp_key->sctp_src, is_mask);
		SW_FLOW_KEY_PUT(match, tp.dst, sctp_key->sctp_dst, is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_SCTP);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_ICMP)) अणु
		स्थिर काष्ठा ovs_key_icmp *icmp_key;

		icmp_key = nla_data(a[OVS_KEY_ATTR_ICMP]);
		SW_FLOW_KEY_PUT(match, tp.src,
				htons(icmp_key->icmp_type), is_mask);
		SW_FLOW_KEY_PUT(match, tp.dst,
				htons(icmp_key->icmp_code), is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_ICMP);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_ICMPV6)) अणु
		स्थिर काष्ठा ovs_key_icmpv6 *icmpv6_key;

		icmpv6_key = nla_data(a[OVS_KEY_ATTR_ICMPV6]);
		SW_FLOW_KEY_PUT(match, tp.src,
				htons(icmpv6_key->icmpv6_type), is_mask);
		SW_FLOW_KEY_PUT(match, tp.dst,
				htons(icmpv6_key->icmpv6_code), is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_ICMPV6);
	पूर्ण

	अगर (attrs & (1 << OVS_KEY_ATTR_ND)) अणु
		स्थिर काष्ठा ovs_key_nd *nd_key;

		nd_key = nla_data(a[OVS_KEY_ATTR_ND]);
		SW_FLOW_KEY_MEMCPY(match, ipv6.nd.target,
			nd_key->nd_target,
			माप(match->key->ipv6.nd.target),
			is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv6.nd.sll,
			nd_key->nd_sll, ETH_ALEN, is_mask);
		SW_FLOW_KEY_MEMCPY(match, ipv6.nd.tll,
				nd_key->nd_tll, ETH_ALEN, is_mask);
		attrs &= ~(1 << OVS_KEY_ATTR_ND);
	पूर्ण

	अगर (attrs != 0) अणु
		OVS_NLERR(log, "Unknown key attributes %llx",
			  (अचिन्हित दीर्घ दीर्घ)attrs);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nlattr_set(काष्ठा nlattr *attr, u8 val,
		       स्थिर काष्ठा ovs_len_tbl *tbl)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक rem;

	/* The nlattr stream should alपढ़ोy have been validated */
	nla_क्रम_each_nested(nla, attr, rem) अणु
		अगर (tbl[nla_type(nla)].len == OVS_ATTR_NESTED)
			nlattr_set(nla, val, tbl[nla_type(nla)].next ? : tbl);
		अन्यथा
			स_रखो(nla_data(nla), val, nla_len(nla));

		अगर (nla_type(nla) == OVS_KEY_ATTR_CT_STATE)
			*(u32 *)nla_data(nla) &= CT_SUPPORTED_MASK;
	पूर्ण
पूर्ण

अटल व्योम mask_set_nlattr(काष्ठा nlattr *attr, u8 val)
अणु
	nlattr_set(attr, val, ovs_key_lens);
पूर्ण

/**
 * ovs_nla_get_match - parses Netlink attributes पूर्णांकo a flow key and
 * mask. In हाल the 'mask' is शून्य, the flow is treated as exact match
 * flow. Otherwise, it is treated as a wildcarded flow, except the mask
 * करोes not include any करोn't care bit.
 * @net: Used to determine per-namespace field support.
 * @match: receives the extracted flow match inक्रमmation.
 * @nla_key: Netlink attribute holding nested %OVS_KEY_ATTR_* Netlink attribute
 * sequence. The fields should of the packet that triggered the creation
 * of this flow.
 * @nla_mask: Optional. Netlink attribute holding nested %OVS_KEY_ATTR_*
 * Netlink attribute specअगरies the mask field of the wildcarded flow.
 * @log: Boolean to allow kernel error logging.  Normally true, but when
 * probing क्रम feature compatibility this should be passed in as false to
 * suppress unnecessary error logging.
 */
पूर्णांक ovs_nla_get_match(काष्ठा net *net, काष्ठा sw_flow_match *match,
		      स्थिर काष्ठा nlattr *nla_key,
		      स्थिर काष्ठा nlattr *nla_mask,
		      bool log)
अणु
	स्थिर काष्ठा nlattr *a[OVS_KEY_ATTR_MAX + 1];
	काष्ठा nlattr *newmask = शून्य;
	u64 key_attrs = 0;
	u64 mask_attrs = 0;
	पूर्णांक err;

	err = parse_flow_nlattrs(nla_key, a, &key_attrs, log);
	अगर (err)
		वापस err;

	err = parse_vlan_from_nlattrs(match, &key_attrs, a, false, log);
	अगर (err)
		वापस err;

	err = ovs_key_from_nlattrs(net, match, key_attrs, a, false, log);
	अगर (err)
		वापस err;

	अगर (match->mask) अणु
		अगर (!nla_mask) अणु
			/* Create an exact match mask. We need to set to 0xff
			 * all the 'match->mask' fields that have been touched
			 * in 'match->key'. We cannot simply स_रखो
			 * 'match->mask', because padding bytes and fields not
			 * specअगरied in 'match->key' should be left to 0.
			 * Instead, we use a stream of netlink attributes,
			 * copied from 'key' and set to 0xff.
			 * ovs_key_from_nlattrs() will take care of filling
			 * 'match->mask' appropriately.
			 */
			newmask = kmemdup(nla_key,
					  nla_total_size(nla_len(nla_key)),
					  GFP_KERNEL);
			अगर (!newmask)
				वापस -ENOMEM;

			mask_set_nlattr(newmask, 0xff);

			/* The userspace करोes not send tunnel attributes that
			 * are 0, but we should not wildcard them nonetheless.
			 */
			अगर (match->key->tun_proto)
				SW_FLOW_KEY_MEMSET_FIELD(match, tun_key,
							 0xff, true);

			nla_mask = newmask;
		पूर्ण

		err = parse_flow_mask_nlattrs(nla_mask, a, &mask_attrs, log);
		अगर (err)
			जाओ मुक्त_newmask;

		/* Always match on tci. */
		SW_FLOW_KEY_PUT(match, eth.vlan.tci, htons(0xffff), true);
		SW_FLOW_KEY_PUT(match, eth.cvlan.tci, htons(0xffff), true);

		err = parse_vlan_from_nlattrs(match, &mask_attrs, a, true, log);
		अगर (err)
			जाओ मुक्त_newmask;

		err = ovs_key_from_nlattrs(net, match, mask_attrs, a, true,
					   log);
		अगर (err)
			जाओ मुक्त_newmask;
	पूर्ण

	अगर (!match_validate(match, key_attrs, mask_attrs, log))
		err = -EINVAL;

मुक्त_newmask:
	kमुक्त(newmask);
	वापस err;
पूर्ण

अटल माप_प्रकार get_ufid_len(स्थिर काष्ठा nlattr *attr, bool log)
अणु
	माप_प्रकार len;

	अगर (!attr)
		वापस 0;

	len = nla_len(attr);
	अगर (len < 1 || len > MAX_UFID_LENGTH) अणु
		OVS_NLERR(log, "ufid size %u bytes exceeds the range (1, %d)",
			  nla_len(attr), MAX_UFID_LENGTH);
		वापस 0;
	पूर्ण

	वापस len;
पूर्ण

/* Initializes 'flow->ufid', returning true if 'attr' contains a valid UFID,
 * or false otherwise.
 */
bool ovs_nla_get_ufid(काष्ठा sw_flow_id *sfid, स्थिर काष्ठा nlattr *attr,
		      bool log)
अणु
	sfid->ufid_len = get_ufid_len(attr, log);
	अगर (sfid->ufid_len)
		स_नकल(sfid->ufid, nla_data(attr), sfid->ufid_len);

	वापस sfid->ufid_len;
पूर्ण

पूर्णांक ovs_nla_get_identअगरier(काष्ठा sw_flow_id *sfid, स्थिर काष्ठा nlattr *ufid,
			   स्थिर काष्ठा sw_flow_key *key, bool log)
अणु
	काष्ठा sw_flow_key *new_key;

	अगर (ovs_nla_get_ufid(sfid, ufid, log))
		वापस 0;

	/* If UFID was not provided, use unmasked key. */
	new_key = kदो_स्मृति(माप(*new_key), GFP_KERNEL);
	अगर (!new_key)
		वापस -ENOMEM;
	स_नकल(new_key, key, माप(*key));
	sfid->unmasked_key = new_key;

	वापस 0;
पूर्ण

u32 ovs_nla_get_ufid_flags(स्थिर काष्ठा nlattr *attr)
अणु
	वापस attr ? nla_get_u32(attr) : 0;
पूर्ण

/**
 * ovs_nla_get_flow_metadata - parses Netlink attributes पूर्णांकo a flow key.
 * @net: Network namespace.
 * @key: Receives extracted in_port, priority, tun_key, skb_mark and conntrack
 * metadata.
 * @a: Array of netlink attributes holding parsed %OVS_KEY_ATTR_* Netlink
 * attributes.
 * @attrs: Bit mask क्रम the netlink attributes included in @a.
 * @log: Boolean to allow kernel error logging.  Normally true, but when
 * probing क्रम feature compatibility this should be passed in as false to
 * suppress unnecessary error logging.
 *
 * This parses a series of Netlink attributes that क्रमm a flow key, which must
 * take the same क्रमm accepted by flow_from_nlattrs(), but only enough of it to
 * get the metadata, that is, the parts of the flow key that cannot be
 * extracted from the packet itself.
 *
 * This must be called beक्रमe the packet key fields are filled in 'key'.
 */

पूर्णांक ovs_nla_get_flow_metadata(काष्ठा net *net,
			      स्थिर काष्ठा nlattr *a[OVS_KEY_ATTR_MAX + 1],
			      u64 attrs, काष्ठा sw_flow_key *key, bool log)
अणु
	काष्ठा sw_flow_match match;

	स_रखो(&match, 0, माप(match));
	match.key = key;

	key->ct_state = 0;
	key->ct_zone = 0;
	key->ct_orig_proto = 0;
	स_रखो(&key->ct, 0, माप(key->ct));
	स_रखो(&key->ipv4.ct_orig, 0, माप(key->ipv4.ct_orig));
	स_रखो(&key->ipv6.ct_orig, 0, माप(key->ipv6.ct_orig));

	key->phy.in_port = DP_MAX_PORTS;

	वापस metadata_from_nlattrs(net, &match, &attrs, a, false, log);
पूर्ण

अटल पूर्णांक ovs_nla_put_vlan(काष्ठा sk_buff *skb, स्थिर काष्ठा vlan_head *vh,
			    bool is_mask)
अणु
	__be16 eth_type = !is_mask ? vh->tpid : htons(0xffff);

	अगर (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE, eth_type) ||
	    nla_put_be16(skb, OVS_KEY_ATTR_VLAN, vh->tci))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक nsh_key_to_nlattr(स्थिर काष्ठा ovs_key_nsh *nsh, bool is_mask,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start;

	start = nla_nest_start_noflag(skb, OVS_KEY_ATTR_NSH);
	अगर (!start)
		वापस -EMSGSIZE;

	अगर (nla_put(skb, OVS_NSH_KEY_ATTR_BASE, माप(nsh->base), &nsh->base))
		जाओ nla_put_failure;

	अगर (is_mask || nsh->base.mdtype == NSH_M_TYPE1) अणु
		अगर (nla_put(skb, OVS_NSH_KEY_ATTR_MD1,
			    माप(nsh->context), nsh->context))
			जाओ nla_put_failure;
	पूर्ण

	/* Don't support MD type 2 yet */

	nla_nest_end(skb, start);

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक __ovs_nla_put_key(स्थिर काष्ठा sw_flow_key *swkey,
			     स्थिर काष्ठा sw_flow_key *output, bool is_mask,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा ovs_key_ethernet *eth_key;
	काष्ठा nlattr *nla;
	काष्ठा nlattr *encap = शून्य;
	काष्ठा nlattr *in_encap = शून्य;

	अगर (nla_put_u32(skb, OVS_KEY_ATTR_RECIRC_ID, output->recirc_id))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, OVS_KEY_ATTR_DP_HASH, output->ovs_flow_hash))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, OVS_KEY_ATTR_PRIORITY, output->phy.priority))
		जाओ nla_put_failure;

	अगर ((swkey->tun_proto || is_mask)) अणु
		स्थिर व्योम *opts = शून्य;

		अगर (output->tun_key.tun_flags & TUNNEL_OPTIONS_PRESENT)
			opts = TUN_METADATA_OPTS(output, swkey->tun_opts_len);

		अगर (ip_tun_to_nlattr(skb, &output->tun_key, opts,
				     swkey->tun_opts_len, swkey->tun_proto, 0))
			जाओ nla_put_failure;
	पूर्ण

	अगर (swkey->phy.in_port == DP_MAX_PORTS) अणु
		अगर (is_mask && (output->phy.in_port == 0xffff))
			अगर (nla_put_u32(skb, OVS_KEY_ATTR_IN_PORT, 0xffffffff))
				जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		u16 upper_u16;
		upper_u16 = !is_mask ? 0 : 0xffff;

		अगर (nla_put_u32(skb, OVS_KEY_ATTR_IN_PORT,
				(upper_u16 << 16) | output->phy.in_port))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u32(skb, OVS_KEY_ATTR_SKB_MARK, output->phy.skb_mark))
		जाओ nla_put_failure;

	अगर (ovs_ct_put_key(swkey, output, skb))
		जाओ nla_put_failure;

	अगर (ovs_key_mac_proto(swkey) == MAC_PROTO_ETHERNET) अणु
		nla = nla_reserve(skb, OVS_KEY_ATTR_ETHERNET, माप(*eth_key));
		अगर (!nla)
			जाओ nla_put_failure;

		eth_key = nla_data(nla);
		ether_addr_copy(eth_key->eth_src, output->eth.src);
		ether_addr_copy(eth_key->eth_dst, output->eth.dst);

		अगर (swkey->eth.vlan.tci || eth_type_vlan(swkey->eth.type)) अणु
			अगर (ovs_nla_put_vlan(skb, &output->eth.vlan, is_mask))
				जाओ nla_put_failure;
			encap = nla_nest_start_noflag(skb, OVS_KEY_ATTR_ENCAP);
			अगर (!swkey->eth.vlan.tci)
				जाओ unencap;

			अगर (swkey->eth.cvlan.tci || eth_type_vlan(swkey->eth.type)) अणु
				अगर (ovs_nla_put_vlan(skb, &output->eth.cvlan, is_mask))
					जाओ nla_put_failure;
				in_encap = nla_nest_start_noflag(skb,
								 OVS_KEY_ATTR_ENCAP);
				अगर (!swkey->eth.cvlan.tci)
					जाओ unencap;
			पूर्ण
		पूर्ण

		अगर (swkey->eth.type == htons(ETH_P_802_2)) अणु
			/*
			* Ethertype 802.2 is represented in the netlink with omitted
			* OVS_KEY_ATTR_ETHERTYPE in the flow key attribute, and
			* 0xffff in the mask attribute.  Ethertype can also
			* be wildcarded.
			*/
			अगर (is_mask && output->eth.type)
				अगर (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE,
							output->eth.type))
					जाओ nla_put_failure;
			जाओ unencap;
		पूर्ण
	पूर्ण

	अगर (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE, output->eth.type))
		जाओ nla_put_failure;

	अगर (eth_type_vlan(swkey->eth.type)) अणु
		/* There are 3 VLAN tags, we करोn't know anything about the rest
		 * of the packet, so truncate here.
		 */
		WARN_ON_ONCE(!(encap && in_encap));
		जाओ unencap;
	पूर्ण

	अगर (swkey->eth.type == htons(ETH_P_IP)) अणु
		काष्ठा ovs_key_ipv4 *ipv4_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_IPV4, माप(*ipv4_key));
		अगर (!nla)
			जाओ nla_put_failure;
		ipv4_key = nla_data(nla);
		ipv4_key->ipv4_src = output->ipv4.addr.src;
		ipv4_key->ipv4_dst = output->ipv4.addr.dst;
		ipv4_key->ipv4_proto = output->ip.proto;
		ipv4_key->ipv4_tos = output->ip.tos;
		ipv4_key->ipv4_ttl = output->ip.ttl;
		ipv4_key->ipv4_frag = output->ip.frag;
	पूर्ण अन्यथा अगर (swkey->eth.type == htons(ETH_P_IPV6)) अणु
		काष्ठा ovs_key_ipv6 *ipv6_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_IPV6, माप(*ipv6_key));
		अगर (!nla)
			जाओ nla_put_failure;
		ipv6_key = nla_data(nla);
		स_नकल(ipv6_key->ipv6_src, &output->ipv6.addr.src,
				माप(ipv6_key->ipv6_src));
		स_नकल(ipv6_key->ipv6_dst, &output->ipv6.addr.dst,
				माप(ipv6_key->ipv6_dst));
		ipv6_key->ipv6_label = output->ipv6.label;
		ipv6_key->ipv6_proto = output->ip.proto;
		ipv6_key->ipv6_tclass = output->ip.tos;
		ipv6_key->ipv6_hlimit = output->ip.ttl;
		ipv6_key->ipv6_frag = output->ip.frag;
	पूर्ण अन्यथा अगर (swkey->eth.type == htons(ETH_P_NSH)) अणु
		अगर (nsh_key_to_nlattr(&output->nsh, is_mask, skb))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अगर (swkey->eth.type == htons(ETH_P_ARP) ||
		   swkey->eth.type == htons(ETH_P_RARP)) अणु
		काष्ठा ovs_key_arp *arp_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_ARP, माप(*arp_key));
		अगर (!nla)
			जाओ nla_put_failure;
		arp_key = nla_data(nla);
		स_रखो(arp_key, 0, माप(काष्ठा ovs_key_arp));
		arp_key->arp_sip = output->ipv4.addr.src;
		arp_key->arp_tip = output->ipv4.addr.dst;
		arp_key->arp_op = htons(output->ip.proto);
		ether_addr_copy(arp_key->arp_sha, output->ipv4.arp.sha);
		ether_addr_copy(arp_key->arp_tha, output->ipv4.arp.tha);
	पूर्ण अन्यथा अगर (eth_p_mpls(swkey->eth.type)) अणु
		u8 i, num_labels;
		काष्ठा ovs_key_mpls *mpls_key;

		num_labels = hweight_दीर्घ(output->mpls.num_labels_mask);
		nla = nla_reserve(skb, OVS_KEY_ATTR_MPLS,
				  num_labels * माप(*mpls_key));
		अगर (!nla)
			जाओ nla_put_failure;

		mpls_key = nla_data(nla);
		क्रम (i = 0; i < num_labels; i++)
			mpls_key[i].mpls_lse = output->mpls.lse[i];
	पूर्ण

	अगर ((swkey->eth.type == htons(ETH_P_IP) ||
	     swkey->eth.type == htons(ETH_P_IPV6)) &&
	     swkey->ip.frag != OVS_FRAG_TYPE_LATER) अणु

		अगर (swkey->ip.proto == IPPROTO_TCP) अणु
			काष्ठा ovs_key_tcp *tcp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_TCP, माप(*tcp_key));
			अगर (!nla)
				जाओ nla_put_failure;
			tcp_key = nla_data(nla);
			tcp_key->tcp_src = output->tp.src;
			tcp_key->tcp_dst = output->tp.dst;
			अगर (nla_put_be16(skb, OVS_KEY_ATTR_TCP_FLAGS,
					 output->tp.flags))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (swkey->ip.proto == IPPROTO_UDP) अणु
			काष्ठा ovs_key_udp *udp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_UDP, माप(*udp_key));
			अगर (!nla)
				जाओ nla_put_failure;
			udp_key = nla_data(nla);
			udp_key->udp_src = output->tp.src;
			udp_key->udp_dst = output->tp.dst;
		पूर्ण अन्यथा अगर (swkey->ip.proto == IPPROTO_SCTP) अणु
			काष्ठा ovs_key_sctp *sctp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_SCTP, माप(*sctp_key));
			अगर (!nla)
				जाओ nla_put_failure;
			sctp_key = nla_data(nla);
			sctp_key->sctp_src = output->tp.src;
			sctp_key->sctp_dst = output->tp.dst;
		पूर्ण अन्यथा अगर (swkey->eth.type == htons(ETH_P_IP) &&
			   swkey->ip.proto == IPPROTO_ICMP) अणु
			काष्ठा ovs_key_icmp *icmp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_ICMP, माप(*icmp_key));
			अगर (!nla)
				जाओ nla_put_failure;
			icmp_key = nla_data(nla);
			icmp_key->icmp_type = ntohs(output->tp.src);
			icmp_key->icmp_code = ntohs(output->tp.dst);
		पूर्ण अन्यथा अगर (swkey->eth.type == htons(ETH_P_IPV6) &&
			   swkey->ip.proto == IPPROTO_ICMPV6) अणु
			काष्ठा ovs_key_icmpv6 *icmpv6_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_ICMPV6,
						माप(*icmpv6_key));
			अगर (!nla)
				जाओ nla_put_failure;
			icmpv6_key = nla_data(nla);
			icmpv6_key->icmpv6_type = ntohs(output->tp.src);
			icmpv6_key->icmpv6_code = ntohs(output->tp.dst);

			अगर (icmpv6_key->icmpv6_type == NDISC_NEIGHBOUR_SOLICITATION ||
			    icmpv6_key->icmpv6_type == NDISC_NEIGHBOUR_ADVERTISEMENT) अणु
				काष्ठा ovs_key_nd *nd_key;

				nla = nla_reserve(skb, OVS_KEY_ATTR_ND, माप(*nd_key));
				अगर (!nla)
					जाओ nla_put_failure;
				nd_key = nla_data(nla);
				स_नकल(nd_key->nd_target, &output->ipv6.nd.target,
							माप(nd_key->nd_target));
				ether_addr_copy(nd_key->nd_sll, output->ipv6.nd.sll);
				ether_addr_copy(nd_key->nd_tll, output->ipv6.nd.tll);
			पूर्ण
		पूर्ण
	पूर्ण

unencap:
	अगर (in_encap)
		nla_nest_end(skb, in_encap);
	अगर (encap)
		nla_nest_end(skb, encap);

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक ovs_nla_put_key(स्थिर काष्ठा sw_flow_key *swkey,
		    स्थिर काष्ठा sw_flow_key *output, पूर्णांक attr, bool is_mask,
		    काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	काष्ठा nlattr *nla;

	nla = nla_nest_start_noflag(skb, attr);
	अगर (!nla)
		वापस -EMSGSIZE;
	err = __ovs_nla_put_key(swkey, output, is_mask, skb);
	अगर (err)
		वापस err;
	nla_nest_end(skb, nla);

	वापस 0;
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
पूर्णांक ovs_nla_put_identअगरier(स्थिर काष्ठा sw_flow *flow, काष्ठा sk_buff *skb)
अणु
	अगर (ovs_identअगरier_is_ufid(&flow->id))
		वापस nla_put(skb, OVS_FLOW_ATTR_UFID, flow->id.ufid_len,
			       flow->id.ufid);

	वापस ovs_nla_put_key(flow->id.unmasked_key, flow->id.unmasked_key,
			       OVS_FLOW_ATTR_KEY, false, skb);
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
पूर्णांक ovs_nla_put_masked_key(स्थिर काष्ठा sw_flow *flow, काष्ठा sk_buff *skb)
अणु
	वापस ovs_nla_put_key(&flow->key, &flow->key,
				OVS_FLOW_ATTR_KEY, false, skb);
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
पूर्णांक ovs_nla_put_mask(स्थिर काष्ठा sw_flow *flow, काष्ठा sk_buff *skb)
अणु
	वापस ovs_nla_put_key(&flow->key, &flow->mask->key,
				OVS_FLOW_ATTR_MASK, true, skb);
पूर्ण

#घोषणा MAX_ACTIONS_बफ_मानE	(32 * 1024)

अटल काष्ठा sw_flow_actions *nla_alloc_flow_actions(पूर्णांक size)
अणु
	काष्ठा sw_flow_actions *sfa;

	WARN_ON_ONCE(size > MAX_ACTIONS_बफ_मानE);

	sfa = kदो_स्मृति(माप(*sfa) + size, GFP_KERNEL);
	अगर (!sfa)
		वापस ERR_PTR(-ENOMEM);

	sfa->actions_len = 0;
	वापस sfa;
पूर्ण

अटल व्योम ovs_nla_मुक्त_set_action(स्थिर काष्ठा nlattr *a)
अणु
	स्थिर काष्ठा nlattr *ovs_key = nla_data(a);
	काष्ठा ovs_tunnel_info *ovs_tun;

	चयन (nla_type(ovs_key)) अणु
	हाल OVS_KEY_ATTR_TUNNEL_INFO:
		ovs_tun = nla_data(ovs_key);
		dst_release((काष्ठा dst_entry *)ovs_tun->tun_dst);
		अवरोध;
	पूर्ण
पूर्ण

व्योम ovs_nla_मुक्त_flow_actions(काष्ठा sw_flow_actions *sf_acts)
अणु
	स्थिर काष्ठा nlattr *a;
	पूर्णांक rem;

	अगर (!sf_acts)
		वापस;

	nla_क्रम_each_attr(a, sf_acts->actions, sf_acts->actions_len, rem) अणु
		चयन (nla_type(a)) अणु
		हाल OVS_ACTION_ATTR_SET:
			ovs_nla_मुक्त_set_action(a);
			अवरोध;
		हाल OVS_ACTION_ATTR_CT:
			ovs_ct_मुक्त_action(a);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(sf_acts);
पूर्ण

अटल व्योम __ovs_nla_मुक्त_flow_actions(काष्ठा rcu_head *head)
अणु
	ovs_nla_मुक्त_flow_actions(container_of(head, काष्ठा sw_flow_actions, rcu));
पूर्ण

/* Schedules 'sf_acts' to be मुक्तd after the next RCU grace period.
 * The caller must hold rcu_पढ़ो_lock क्रम this to be sensible. */
व्योम ovs_nla_मुक्त_flow_actions_rcu(काष्ठा sw_flow_actions *sf_acts)
अणु
	call_rcu(&sf_acts->rcu, __ovs_nla_मुक्त_flow_actions);
पूर्ण

अटल काष्ठा nlattr *reserve_sfa_size(काष्ठा sw_flow_actions **sfa,
				       पूर्णांक attr_len, bool log)
अणु

	काष्ठा sw_flow_actions *acts;
	पूर्णांक new_acts_size;
	माप_प्रकार req_size = NLA_ALIGN(attr_len);
	पूर्णांक next_offset = दुरत्व(काष्ठा sw_flow_actions, actions) +
					(*sfa)->actions_len;

	अगर (req_size <= (ksize(*sfa) - next_offset))
		जाओ out;

	new_acts_size = max(next_offset + req_size, ksize(*sfa) * 2);

	अगर (new_acts_size > MAX_ACTIONS_बफ_मानE) अणु
		अगर ((MAX_ACTIONS_बफ_मानE - next_offset) < req_size) अणु
			OVS_NLERR(log, "Flow action size exceeds max %u",
				  MAX_ACTIONS_बफ_मानE);
			वापस ERR_PTR(-EMSGSIZE);
		पूर्ण
		new_acts_size = MAX_ACTIONS_बफ_मानE;
	पूर्ण

	acts = nla_alloc_flow_actions(new_acts_size);
	अगर (IS_ERR(acts))
		वापस (व्योम *)acts;

	स_नकल(acts->actions, (*sfa)->actions, (*sfa)->actions_len);
	acts->actions_len = (*sfa)->actions_len;
	acts->orig_len = (*sfa)->orig_len;
	kमुक्त(*sfa);
	*sfa = acts;

out:
	(*sfa)->actions_len += req_size;
	वापस  (काष्ठा nlattr *) ((अचिन्हित अक्षर *)(*sfa) + next_offset);
पूर्ण

अटल काष्ठा nlattr *__add_action(काष्ठा sw_flow_actions **sfa,
				   पूर्णांक attrtype, व्योम *data, पूर्णांक len, bool log)
अणु
	काष्ठा nlattr *a;

	a = reserve_sfa_size(sfa, nla_attr_size(len), log);
	अगर (IS_ERR(a))
		वापस a;

	a->nla_type = attrtype;
	a->nla_len = nla_attr_size(len);

	अगर (data)
		स_नकल(nla_data(a), data, len);
	स_रखो((अचिन्हित अक्षर *) a + a->nla_len, 0, nla_padlen(len));

	वापस a;
पूर्ण

पूर्णांक ovs_nla_add_action(काष्ठा sw_flow_actions **sfa, पूर्णांक attrtype, व्योम *data,
		       पूर्णांक len, bool log)
अणु
	काष्ठा nlattr *a;

	a = __add_action(sfa, attrtype, data, len, log);

	वापस PTR_ERR_OR_ZERO(a);
पूर्ण

अटल अंतरभूत पूर्णांक add_nested_action_start(काष्ठा sw_flow_actions **sfa,
					  पूर्णांक attrtype, bool log)
अणु
	पूर्णांक used = (*sfa)->actions_len;
	पूर्णांक err;

	err = ovs_nla_add_action(sfa, attrtype, शून्य, 0, log);
	अगर (err)
		वापस err;

	वापस used;
पूर्ण

अटल अंतरभूत व्योम add_nested_action_end(काष्ठा sw_flow_actions *sfa,
					 पूर्णांक st_offset)
अणु
	काष्ठा nlattr *a = (काष्ठा nlattr *) ((अचिन्हित अक्षर *)sfa->actions +
							       st_offset);

	a->nla_len = sfa->actions_len - st_offset;
पूर्ण

अटल पूर्णांक __ovs_nla_copy_actions(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
				  स्थिर काष्ठा sw_flow_key *key,
				  काष्ठा sw_flow_actions **sfa,
				  __be16 eth_type, __be16 vlan_tci,
				  u32 mpls_label_count, bool log);

अटल पूर्णांक validate_and_copy_sample(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
				    स्थिर काष्ठा sw_flow_key *key,
				    काष्ठा sw_flow_actions **sfa,
				    __be16 eth_type, __be16 vlan_tci,
				    u32 mpls_label_count, bool log, bool last)
अणु
	स्थिर काष्ठा nlattr *attrs[OVS_SAMPLE_ATTR_MAX + 1];
	स्थिर काष्ठा nlattr *probability, *actions;
	स्थिर काष्ठा nlattr *a;
	पूर्णांक rem, start, err;
	काष्ठा sample_arg arg;

	स_रखो(attrs, 0, माप(attrs));
	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);
		अगर (!type || type > OVS_SAMPLE_ATTR_MAX || attrs[type])
			वापस -EINVAL;
		attrs[type] = a;
	पूर्ण
	अगर (rem)
		वापस -EINVAL;

	probability = attrs[OVS_SAMPLE_ATTR_PROBABILITY];
	अगर (!probability || nla_len(probability) != माप(u32))
		वापस -EINVAL;

	actions = attrs[OVS_SAMPLE_ATTR_ACTIONS];
	अगर (!actions || (nla_len(actions) && nla_len(actions) < NLA_HDRLEN))
		वापस -EINVAL;

	/* validation करोne, copy sample action. */
	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_SAMPLE, log);
	अगर (start < 0)
		वापस start;

	/* When both skb and flow may be changed, put the sample
	 * पूर्णांकo a deferred fअगरo. On the other hand, अगर only skb
	 * may be modअगरied, the actions can be executed in place.
	 *
	 * Do this analysis at the flow installation समय.
	 * Set 'clone_action->exec' to true अगर the actions can be
	 * executed without being deferred.
	 *
	 * If the sample is the last action, it can always be excuted
	 * rather than deferred.
	 */
	arg.exec = last || !actions_may_change_flow(actions);
	arg.probability = nla_get_u32(probability);

	err = ovs_nla_add_action(sfa, OVS_SAMPLE_ATTR_ARG, &arg, माप(arg),
				 log);
	अगर (err)
		वापस err;

	err = __ovs_nla_copy_actions(net, actions, key, sfa,
				     eth_type, vlan_tci, mpls_label_count, log);

	अगर (err)
		वापस err;

	add_nested_action_end(*sfa, start);

	वापस 0;
पूर्ण

अटल पूर्णांक validate_and_copy_dec_ttl(काष्ठा net *net,
				     स्थिर काष्ठा nlattr *attr,
				     स्थिर काष्ठा sw_flow_key *key,
				     काष्ठा sw_flow_actions **sfa,
				     __be16 eth_type, __be16 vlan_tci,
				     u32 mpls_label_count, bool log)
अणु
	स्थिर काष्ठा nlattr *attrs[OVS_DEC_TTL_ATTR_MAX + 1];
	पूर्णांक start, action_start, err, rem;
	स्थिर काष्ठा nlattr *a, *actions;

	स_रखो(attrs, 0, माप(attrs));
	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);

		/* Ignore unknown attributes to be future proof. */
		अगर (type > OVS_DEC_TTL_ATTR_MAX)
			जारी;

		अगर (!type || attrs[type]) अणु
			OVS_NLERR(log, "Duplicate or invalid key (type %d).",
				  type);
			वापस -EINVAL;
		पूर्ण

		attrs[type] = a;
	पूर्ण

	अगर (rem) अणु
		OVS_NLERR(log, "Message has %d unknown bytes.", rem);
		वापस -EINVAL;
	पूर्ण

	actions = attrs[OVS_DEC_TTL_ATTR_ACTION];
	अगर (!actions || (nla_len(actions) && nla_len(actions) < NLA_HDRLEN)) अणु
		OVS_NLERR(log, "Missing valid actions attribute.");
		वापस -EINVAL;
	पूर्ण

	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_DEC_TTL, log);
	अगर (start < 0)
		वापस start;

	action_start = add_nested_action_start(sfa, OVS_DEC_TTL_ATTR_ACTION, log);
	अगर (action_start < 0)
		वापस action_start;

	err = __ovs_nla_copy_actions(net, actions, key, sfa, eth_type,
				     vlan_tci, mpls_label_count, log);
	अगर (err)
		वापस err;

	add_nested_action_end(*sfa, action_start);
	add_nested_action_end(*sfa, start);
	वापस 0;
पूर्ण

अटल पूर्णांक validate_and_copy_clone(काष्ठा net *net,
				   स्थिर काष्ठा nlattr *attr,
				   स्थिर काष्ठा sw_flow_key *key,
				   काष्ठा sw_flow_actions **sfa,
				   __be16 eth_type, __be16 vlan_tci,
				   u32 mpls_label_count, bool log, bool last)
अणु
	पूर्णांक start, err;
	u32 exec;

	अगर (nla_len(attr) && nla_len(attr) < NLA_HDRLEN)
		वापस -EINVAL;

	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_CLONE, log);
	अगर (start < 0)
		वापस start;

	exec = last || !actions_may_change_flow(attr);

	err = ovs_nla_add_action(sfa, OVS_CLONE_ATTR_EXEC, &exec,
				 माप(exec), log);
	अगर (err)
		वापस err;

	err = __ovs_nla_copy_actions(net, attr, key, sfa,
				     eth_type, vlan_tci, mpls_label_count, log);
	अगर (err)
		वापस err;

	add_nested_action_end(*sfa, start);

	वापस 0;
पूर्ण

व्योम ovs_match_init(काष्ठा sw_flow_match *match,
		    काष्ठा sw_flow_key *key,
		    bool reset_key,
		    काष्ठा sw_flow_mask *mask)
अणु
	स_रखो(match, 0, माप(*match));
	match->key = key;
	match->mask = mask;

	अगर (reset_key)
		स_रखो(key, 0, माप(*key));

	अगर (mask) अणु
		स_रखो(&mask->key, 0, माप(mask->key));
		mask->range.start = mask->range.end = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक validate_geneve_opts(काष्ठा sw_flow_key *key)
अणु
	काष्ठा geneve_opt *option;
	पूर्णांक opts_len = key->tun_opts_len;
	bool crit_opt = false;

	option = (काष्ठा geneve_opt *)TUN_METADATA_OPTS(key, key->tun_opts_len);
	जबतक (opts_len > 0) अणु
		पूर्णांक len;

		अगर (opts_len < माप(*option))
			वापस -EINVAL;

		len = माप(*option) + option->length * 4;
		अगर (len > opts_len)
			वापस -EINVAL;

		crit_opt |= !!(option->type & GENEVE_CRIT_OPT_TYPE);

		option = (काष्ठा geneve_opt *)((u8 *)option + len);
		opts_len -= len;
	पूर्ण

	key->tun_key.tun_flags |= crit_opt ? TUNNEL_CRIT_OPT : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_and_copy_set_tun(स्थिर काष्ठा nlattr *attr,
				     काष्ठा sw_flow_actions **sfa, bool log)
अणु
	काष्ठा sw_flow_match match;
	काष्ठा sw_flow_key key;
	काष्ठा metadata_dst *tun_dst;
	काष्ठा ip_tunnel_info *tun_info;
	काष्ठा ovs_tunnel_info *ovs_tun;
	काष्ठा nlattr *a;
	पूर्णांक err = 0, start, opts_type;
	__be16 dst_opt_type;

	dst_opt_type = 0;
	ovs_match_init(&match, &key, true, शून्य);
	opts_type = ip_tun_from_nlattr(nla_data(attr), &match, false, log);
	अगर (opts_type < 0)
		वापस opts_type;

	अगर (key.tun_opts_len) अणु
		चयन (opts_type) अणु
		हाल OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS:
			err = validate_geneve_opts(&key);
			अगर (err < 0)
				वापस err;
			dst_opt_type = TUNNEL_GENEVE_OPT;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS:
			dst_opt_type = TUNNEL_VXLAN_OPT;
			अवरोध;
		हाल OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS:
			dst_opt_type = TUNNEL_ERSPAN_OPT;
			अवरोध;
		पूर्ण
	पूर्ण

	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_SET, log);
	अगर (start < 0)
		वापस start;

	tun_dst = metadata_dst_alloc(key.tun_opts_len, METADATA_IP_TUNNEL,
				     GFP_KERNEL);

	अगर (!tun_dst)
		वापस -ENOMEM;

	err = dst_cache_init(&tun_dst->u.tun_info.dst_cache, GFP_KERNEL);
	अगर (err) अणु
		dst_release((काष्ठा dst_entry *)tun_dst);
		वापस err;
	पूर्ण

	a = __add_action(sfa, OVS_KEY_ATTR_TUNNEL_INFO, शून्य,
			 माप(*ovs_tun), log);
	अगर (IS_ERR(a)) अणु
		dst_release((काष्ठा dst_entry *)tun_dst);
		वापस PTR_ERR(a);
	पूर्ण

	ovs_tun = nla_data(a);
	ovs_tun->tun_dst = tun_dst;

	tun_info = &tun_dst->u.tun_info;
	tun_info->mode = IP_TUNNEL_INFO_TX;
	अगर (key.tun_proto == AF_INET6)
		tun_info->mode |= IP_TUNNEL_INFO_IPV6;
	अन्यथा अगर (key.tun_proto == AF_INET && key.tun_key.u.ipv4.dst == 0)
		tun_info->mode |= IP_TUNNEL_INFO_BRIDGE;
	tun_info->key = key.tun_key;

	/* We need to store the options in the action itself since
	 * everything अन्यथा will go away after flow setup. We can append
	 * it to tun_info and then poपूर्णांक there.
	 */
	ip_tunnel_info_opts_set(tun_info,
				TUN_METADATA_OPTS(&key, key.tun_opts_len),
				key.tun_opts_len, dst_opt_type);
	add_nested_action_end(*sfa, start);

	वापस err;
पूर्ण

अटल bool validate_nsh(स्थिर काष्ठा nlattr *attr, bool is_mask,
			 bool is_push_nsh, bool log)
अणु
	काष्ठा sw_flow_match match;
	काष्ठा sw_flow_key key;
	पूर्णांक ret = 0;

	ovs_match_init(&match, &key, true, शून्य);
	ret = nsh_key_put_from_nlattr(attr, &match, is_mask,
				      is_push_nsh, log);
	वापस !ret;
पूर्ण

/* Return false अगर there are any non-masked bits set.
 * Mask follows data immediately, beक्रमe any netlink padding.
 */
अटल bool validate_masked(u8 *data, पूर्णांक len)
अणु
	u8 *mask = data + len;

	जबतक (len--)
		अगर (*data++ & ~*mask++)
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक validate_set(स्थिर काष्ठा nlattr *a,
			स्थिर काष्ठा sw_flow_key *flow_key,
			काष्ठा sw_flow_actions **sfa, bool *skip_copy,
			u8 mac_proto, __be16 eth_type, bool masked, bool log)
अणु
	स्थिर काष्ठा nlattr *ovs_key = nla_data(a);
	पूर्णांक key_type = nla_type(ovs_key);
	माप_प्रकार key_len;

	/* There can be only one key in a action */
	अगर (nla_total_size(nla_len(ovs_key)) != nla_len(a))
		वापस -EINVAL;

	key_len = nla_len(ovs_key);
	अगर (masked)
		key_len /= 2;

	अगर (key_type > OVS_KEY_ATTR_MAX ||
	    !check_attr_len(key_len, ovs_key_lens[key_type].len))
		वापस -EINVAL;

	अगर (masked && !validate_masked(nla_data(ovs_key), key_len))
		वापस -EINVAL;

	चयन (key_type) अणु
	हाल OVS_KEY_ATTR_PRIORITY:
	हाल OVS_KEY_ATTR_SKB_MARK:
	हाल OVS_KEY_ATTR_CT_MARK:
	हाल OVS_KEY_ATTR_CT_LABELS:
		अवरोध;

	हाल OVS_KEY_ATTR_ETHERNET:
		अगर (mac_proto != MAC_PROTO_ETHERNET)
			वापस -EINVAL;
		अवरोध;

	हाल OVS_KEY_ATTR_TUNNEL: अणु
		पूर्णांक err;

		अगर (masked)
			वापस -EINVAL; /* Masked tunnel set not supported. */

		*skip_copy = true;
		err = validate_and_copy_set_tun(a, sfa, log);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण
	हाल OVS_KEY_ATTR_IPV4: अणु
		स्थिर काष्ठा ovs_key_ipv4 *ipv4_key;

		अगर (eth_type != htons(ETH_P_IP))
			वापस -EINVAL;

		ipv4_key = nla_data(ovs_key);

		अगर (masked) अणु
			स्थिर काष्ठा ovs_key_ipv4 *mask = ipv4_key + 1;

			/* Non-ग_लिखोable fields. */
			अगर (mask->ipv4_proto || mask->ipv4_frag)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (ipv4_key->ipv4_proto != flow_key->ip.proto)
				वापस -EINVAL;

			अगर (ipv4_key->ipv4_frag != flow_key->ip.frag)
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल OVS_KEY_ATTR_IPV6: अणु
		स्थिर काष्ठा ovs_key_ipv6 *ipv6_key;

		अगर (eth_type != htons(ETH_P_IPV6))
			वापस -EINVAL;

		ipv6_key = nla_data(ovs_key);

		अगर (masked) अणु
			स्थिर काष्ठा ovs_key_ipv6 *mask = ipv6_key + 1;

			/* Non-ग_लिखोable fields. */
			अगर (mask->ipv6_proto || mask->ipv6_frag)
				वापस -EINVAL;

			/* Invalid bits in the flow label mask? */
			अगर (ntohl(mask->ipv6_label) & 0xFFF00000)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (ipv6_key->ipv6_proto != flow_key->ip.proto)
				वापस -EINVAL;

			अगर (ipv6_key->ipv6_frag != flow_key->ip.frag)
				वापस -EINVAL;
		पूर्ण
		अगर (ntohl(ipv6_key->ipv6_label) & 0xFFF00000)
			वापस -EINVAL;

		अवरोध;
	पूर्ण
	हाल OVS_KEY_ATTR_TCP:
		अगर ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    flow_key->ip.proto != IPPROTO_TCP)
			वापस -EINVAL;

		अवरोध;

	हाल OVS_KEY_ATTR_UDP:
		अगर ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    flow_key->ip.proto != IPPROTO_UDP)
			वापस -EINVAL;

		अवरोध;

	हाल OVS_KEY_ATTR_MPLS:
		अगर (!eth_p_mpls(eth_type))
			वापस -EINVAL;
		अवरोध;

	हाल OVS_KEY_ATTR_SCTP:
		अगर ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    flow_key->ip.proto != IPPROTO_SCTP)
			वापस -EINVAL;

		अवरोध;

	हाल OVS_KEY_ATTR_NSH:
		अगर (eth_type != htons(ETH_P_NSH))
			वापस -EINVAL;
		अगर (!validate_nsh(nla_data(a), masked, false, log))
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Convert non-masked non-tunnel set actions to masked set actions. */
	अगर (!masked && key_type != OVS_KEY_ATTR_TUNNEL) अणु
		पूर्णांक start, len = key_len * 2;
		काष्ठा nlattr *at;

		*skip_copy = true;

		start = add_nested_action_start(sfa,
						OVS_ACTION_ATTR_SET_TO_MASKED,
						log);
		अगर (start < 0)
			वापस start;

		at = __add_action(sfa, key_type, शून्य, len, log);
		अगर (IS_ERR(at))
			वापस PTR_ERR(at);

		स_नकल(nla_data(at), nla_data(ovs_key), key_len); /* Key. */
		स_रखो(nla_data(at) + key_len, 0xff, key_len);    /* Mask. */
		/* Clear non-ग_लिखोable bits from otherwise ग_लिखोable fields. */
		अगर (key_type == OVS_KEY_ATTR_IPV6) अणु
			काष्ठा ovs_key_ipv6 *mask = nla_data(at) + key_len;

			mask->ipv6_label &= htonl(0x000FFFFF);
		पूर्ण
		add_nested_action_end(*sfa, start);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_userspace(स्थिर काष्ठा nlattr *attr)
अणु
	अटल स्थिर काष्ठा nla_policy userspace_policy[OVS_USERSPACE_ATTR_MAX + 1] = अणु
		[OVS_USERSPACE_ATTR_PID] = अणु.type = NLA_U32 पूर्ण,
		[OVS_USERSPACE_ATTR_USERDATA] = अणु.type = NLA_UNSPEC पूर्ण,
		[OVS_USERSPACE_ATTR_EGRESS_TUN_PORT] = अणु.type = NLA_U32 पूर्ण,
	पूर्ण;
	काष्ठा nlattr *a[OVS_USERSPACE_ATTR_MAX + 1];
	पूर्णांक error;

	error = nla_parse_nested_deprecated(a, OVS_USERSPACE_ATTR_MAX, attr,
					    userspace_policy, शून्य);
	अगर (error)
		वापस error;

	अगर (!a[OVS_USERSPACE_ATTR_PID] ||
	    !nla_get_u32(a[OVS_USERSPACE_ATTR_PID]))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy cpl_policy[OVS_CHECK_PKT_LEN_ATTR_MAX + 1] = अणु
	[OVS_CHECK_PKT_LEN_ATTR_PKT_LEN] = अणु.type = NLA_U16 पूर्ण,
	[OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER] = अणु.type = NLA_NESTED पूर्ण,
	[OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL] = अणु.type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक validate_and_copy_check_pkt_len(काष्ठा net *net,
					   स्थिर काष्ठा nlattr *attr,
					   स्थिर काष्ठा sw_flow_key *key,
					   काष्ठा sw_flow_actions **sfa,
					   __be16 eth_type, __be16 vlan_tci,
					   u32 mpls_label_count,
					   bool log, bool last)
अणु
	स्थिर काष्ठा nlattr *acts_अगर_greater, *acts_अगर_lesser_eq;
	काष्ठा nlattr *a[OVS_CHECK_PKT_LEN_ATTR_MAX + 1];
	काष्ठा check_pkt_len_arg arg;
	पूर्णांक nested_acts_start;
	पूर्णांक start, err;

	err = nla_parse_deprecated_strict(a, OVS_CHECK_PKT_LEN_ATTR_MAX,
					  nla_data(attr), nla_len(attr),
					  cpl_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!a[OVS_CHECK_PKT_LEN_ATTR_PKT_LEN] ||
	    !nla_get_u16(a[OVS_CHECK_PKT_LEN_ATTR_PKT_LEN]))
		वापस -EINVAL;

	acts_अगर_lesser_eq = a[OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL];
	acts_अगर_greater = a[OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER];

	/* Both the nested action should be present. */
	अगर (!acts_अगर_greater || !acts_अगर_lesser_eq)
		वापस -EINVAL;

	/* validation करोne, copy the nested actions. */
	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_CHECK_PKT_LEN,
					log);
	अगर (start < 0)
		वापस start;

	arg.pkt_len = nla_get_u16(a[OVS_CHECK_PKT_LEN_ATTR_PKT_LEN]);
	arg.exec_क्रम_lesser_equal =
		last || !actions_may_change_flow(acts_अगर_lesser_eq);
	arg.exec_क्रम_greater =
		last || !actions_may_change_flow(acts_अगर_greater);

	err = ovs_nla_add_action(sfa, OVS_CHECK_PKT_LEN_ATTR_ARG, &arg,
				 माप(arg), log);
	अगर (err)
		वापस err;

	nested_acts_start = add_nested_action_start(sfa,
		OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL, log);
	अगर (nested_acts_start < 0)
		वापस nested_acts_start;

	err = __ovs_nla_copy_actions(net, acts_अगर_lesser_eq, key, sfa,
				     eth_type, vlan_tci, mpls_label_count, log);

	अगर (err)
		वापस err;

	add_nested_action_end(*sfa, nested_acts_start);

	nested_acts_start = add_nested_action_start(sfa,
		OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER, log);
	अगर (nested_acts_start < 0)
		वापस nested_acts_start;

	err = __ovs_nla_copy_actions(net, acts_अगर_greater, key, sfa,
				     eth_type, vlan_tci, mpls_label_count, log);

	अगर (err)
		वापस err;

	add_nested_action_end(*sfa, nested_acts_start);
	add_nested_action_end(*sfa, start);
	वापस 0;
पूर्ण

अटल पूर्णांक copy_action(स्थिर काष्ठा nlattr *from,
		       काष्ठा sw_flow_actions **sfa, bool log)
अणु
	पूर्णांक totlen = NLA_ALIGN(from->nla_len);
	काष्ठा nlattr *to;

	to = reserve_sfa_size(sfa, from->nla_len, log);
	अगर (IS_ERR(to))
		वापस PTR_ERR(to);

	स_नकल(to, from, totlen);
	वापस 0;
पूर्ण

अटल पूर्णांक __ovs_nla_copy_actions(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
				  स्थिर काष्ठा sw_flow_key *key,
				  काष्ठा sw_flow_actions **sfa,
				  __be16 eth_type, __be16 vlan_tci,
				  u32 mpls_label_count, bool log)
अणु
	u8 mac_proto = ovs_key_mac_proto(key);
	स्थिर काष्ठा nlattr *a;
	पूर्णांक rem, err;

	nla_क्रम_each_nested(a, attr, rem) अणु
		/* Expected argument lengths, (u32)-1 क्रम variable length. */
		अटल स्थिर u32 action_lens[OVS_ACTION_ATTR_MAX + 1] = अणु
			[OVS_ACTION_ATTR_OUTPUT] = माप(u32),
			[OVS_ACTION_ATTR_RECIRC] = माप(u32),
			[OVS_ACTION_ATTR_USERSPACE] = (u32)-1,
			[OVS_ACTION_ATTR_PUSH_MPLS] = माप(काष्ठा ovs_action_push_mpls),
			[OVS_ACTION_ATTR_POP_MPLS] = माप(__be16),
			[OVS_ACTION_ATTR_PUSH_VLAN] = माप(काष्ठा ovs_action_push_vlan),
			[OVS_ACTION_ATTR_POP_VLAN] = 0,
			[OVS_ACTION_ATTR_SET] = (u32)-1,
			[OVS_ACTION_ATTR_SET_MASKED] = (u32)-1,
			[OVS_ACTION_ATTR_SAMPLE] = (u32)-1,
			[OVS_ACTION_ATTR_HASH] = माप(काष्ठा ovs_action_hash),
			[OVS_ACTION_ATTR_CT] = (u32)-1,
			[OVS_ACTION_ATTR_CT_CLEAR] = 0,
			[OVS_ACTION_ATTR_TRUNC] = माप(काष्ठा ovs_action_trunc),
			[OVS_ACTION_ATTR_PUSH_ETH] = माप(काष्ठा ovs_action_push_eth),
			[OVS_ACTION_ATTR_POP_ETH] = 0,
			[OVS_ACTION_ATTR_PUSH_NSH] = (u32)-1,
			[OVS_ACTION_ATTR_POP_NSH] = 0,
			[OVS_ACTION_ATTR_METER] = माप(u32),
			[OVS_ACTION_ATTR_CLONE] = (u32)-1,
			[OVS_ACTION_ATTR_CHECK_PKT_LEN] = (u32)-1,
			[OVS_ACTION_ATTR_ADD_MPLS] = माप(काष्ठा ovs_action_add_mpls),
			[OVS_ACTION_ATTR_DEC_TTL] = (u32)-1,
		पूर्ण;
		स्थिर काष्ठा ovs_action_push_vlan *vlan;
		पूर्णांक type = nla_type(a);
		bool skip_copy;

		अगर (type > OVS_ACTION_ATTR_MAX ||
		    (action_lens[type] != nla_len(a) &&
		     action_lens[type] != (u32)-1))
			वापस -EINVAL;

		skip_copy = false;
		चयन (type) अणु
		हाल OVS_ACTION_ATTR_UNSPEC:
			वापस -EINVAL;

		हाल OVS_ACTION_ATTR_USERSPACE:
			err = validate_userspace(a);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_OUTPUT:
			अगर (nla_get_u32(a) >= DP_MAX_PORTS)
				वापस -EINVAL;
			अवरोध;

		हाल OVS_ACTION_ATTR_TRUNC: अणु
			स्थिर काष्ठा ovs_action_trunc *trunc = nla_data(a);

			अगर (trunc->max_len < ETH_HLEN)
				वापस -EINVAL;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_HASH: अणु
			स्थिर काष्ठा ovs_action_hash *act_hash = nla_data(a);

			चयन (act_hash->hash_alg) अणु
			हाल OVS_HASH_ALG_L4:
				अवरोध;
			शेष:
				वापस  -EINVAL;
			पूर्ण

			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_POP_VLAN:
			अगर (mac_proto != MAC_PROTO_ETHERNET)
				वापस -EINVAL;
			vlan_tci = htons(0);
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_VLAN:
			अगर (mac_proto != MAC_PROTO_ETHERNET)
				वापस -EINVAL;
			vlan = nla_data(a);
			अगर (!eth_type_vlan(vlan->vlan_tpid))
				वापस -EINVAL;
			अगर (!(vlan->vlan_tci & htons(VLAN_CFI_MASK)))
				वापस -EINVAL;
			vlan_tci = vlan->vlan_tci;
			अवरोध;

		हाल OVS_ACTION_ATTR_RECIRC:
			अवरोध;

		हाल OVS_ACTION_ATTR_ADD_MPLS: अणु
			स्थिर काष्ठा ovs_action_add_mpls *mpls = nla_data(a);

			अगर (!eth_p_mpls(mpls->mpls_ethertype))
				वापस -EINVAL;

			अगर (mpls->tun_flags & OVS_MPLS_L3_TUNNEL_FLAG_MASK) अणु
				अगर (vlan_tci & htons(VLAN_CFI_MASK) ||
				    (eth_type != htons(ETH_P_IP) &&
				     eth_type != htons(ETH_P_IPV6) &&
				     eth_type != htons(ETH_P_ARP) &&
				     eth_type != htons(ETH_P_RARP) &&
				     !eth_p_mpls(eth_type)))
					वापस -EINVAL;
				mpls_label_count++;
			पूर्ण अन्यथा अणु
				अगर (mac_proto == MAC_PROTO_ETHERNET) अणु
					mpls_label_count = 1;
					mac_proto = MAC_PROTO_NONE;
				पूर्ण अन्यथा अणु
					mpls_label_count++;
				पूर्ण
			पूर्ण
			eth_type = mpls->mpls_ethertype;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_PUSH_MPLS: अणु
			स्थिर काष्ठा ovs_action_push_mpls *mpls = nla_data(a);

			अगर (!eth_p_mpls(mpls->mpls_ethertype))
				वापस -EINVAL;
			/* Prohibit push MPLS other than to a white list
			 * क्रम packets that have a known tag order.
			 */
			अगर (vlan_tci & htons(VLAN_CFI_MASK) ||
			    (eth_type != htons(ETH_P_IP) &&
			     eth_type != htons(ETH_P_IPV6) &&
			     eth_type != htons(ETH_P_ARP) &&
			     eth_type != htons(ETH_P_RARP) &&
			     !eth_p_mpls(eth_type)))
				वापस -EINVAL;
			eth_type = mpls->mpls_ethertype;
			mpls_label_count++;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_POP_MPLS: अणु
			__be16  proto;
			अगर (vlan_tci & htons(VLAN_CFI_MASK) ||
			    !eth_p_mpls(eth_type))
				वापस -EINVAL;

			/* Disallow subsequent L2.5+ set actions and mpls_pop
			 * actions once the last MPLS label in the packet is
			 * is popped as there is no check here to ensure that
			 * the new eth type is valid and thus set actions could
			 * ग_लिखो off the end of the packet or otherwise corrupt
			 * it.
			 *
			 * Support क्रम these actions is planned using packet
			 * recirculation.
			 */
			proto = nla_get_be16(a);

			अगर (proto == htons(ETH_P_TEB) &&
			    mac_proto != MAC_PROTO_NONE)
				वापस -EINVAL;

			mpls_label_count--;

			अगर (!eth_p_mpls(proto) || !mpls_label_count)
				eth_type = htons(0);
			अन्यथा
				eth_type =  proto;

			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_SET:
			err = validate_set(a, key, sfa,
					   &skip_copy, mac_proto, eth_type,
					   false, log);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_SET_MASKED:
			err = validate_set(a, key, sfa,
					   &skip_copy, mac_proto, eth_type,
					   true, log);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_SAMPLE: अणु
			bool last = nla_is_last(a, rem);

			err = validate_and_copy_sample(net, a, key, sfa,
						       eth_type, vlan_tci,
						       mpls_label_count,
						       log, last);
			अगर (err)
				वापस err;
			skip_copy = true;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_CT:
			err = ovs_ct_copy_action(net, a, key, sfa, log);
			अगर (err)
				वापस err;
			skip_copy = true;
			अवरोध;

		हाल OVS_ACTION_ATTR_CT_CLEAR:
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_ETH:
			/* Disallow pushing an Ethernet header अगर one
			 * is alपढ़ोy present */
			अगर (mac_proto != MAC_PROTO_NONE)
				वापस -EINVAL;
			mac_proto = MAC_PROTO_ETHERNET;
			अवरोध;

		हाल OVS_ACTION_ATTR_POP_ETH:
			अगर (mac_proto != MAC_PROTO_ETHERNET)
				वापस -EINVAL;
			अगर (vlan_tci & htons(VLAN_CFI_MASK))
				वापस -EINVAL;
			mac_proto = MAC_PROTO_NONE;
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_NSH:
			अगर (mac_proto != MAC_PROTO_ETHERNET) अणु
				u8 next_proto;

				next_proto = tun_p_from_eth_p(eth_type);
				अगर (!next_proto)
					वापस -EINVAL;
			पूर्ण
			mac_proto = MAC_PROTO_NONE;
			अगर (!validate_nsh(nla_data(a), false, true, true))
				वापस -EINVAL;
			अवरोध;

		हाल OVS_ACTION_ATTR_POP_NSH: अणु
			__be16 inner_proto;

			अगर (eth_type != htons(ETH_P_NSH))
				वापस -EINVAL;
			inner_proto = tun_p_to_eth_p(key->nsh.base.np);
			अगर (!inner_proto)
				वापस -EINVAL;
			अगर (key->nsh.base.np == TUN_P_ETHERNET)
				mac_proto = MAC_PROTO_ETHERNET;
			अन्यथा
				mac_proto = MAC_PROTO_NONE;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_METER:
			/* Non-existent meters are simply ignored.  */
			अवरोध;

		हाल OVS_ACTION_ATTR_CLONE: अणु
			bool last = nla_is_last(a, rem);

			err = validate_and_copy_clone(net, a, key, sfa,
						      eth_type, vlan_tci,
						      mpls_label_count,
						      log, last);
			अगर (err)
				वापस err;
			skip_copy = true;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_CHECK_PKT_LEN: अणु
			bool last = nla_is_last(a, rem);

			err = validate_and_copy_check_pkt_len(net, a, key, sfa,
							      eth_type,
							      vlan_tci,
							      mpls_label_count,
							      log, last);
			अगर (err)
				वापस err;
			skip_copy = true;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_DEC_TTL:
			err = validate_and_copy_dec_ttl(net, a, key, sfa,
							eth_type, vlan_tci,
							mpls_label_count, log);
			अगर (err)
				वापस err;
			skip_copy = true;
			अवरोध;

		शेष:
			OVS_NLERR(log, "Unknown Action type %d", type);
			वापस -EINVAL;
		पूर्ण
		अगर (!skip_copy) अणु
			err = copy_action(a, sfa, log);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (rem > 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* 'key' must be the masked key. */
पूर्णांक ovs_nla_copy_actions(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
			 स्थिर काष्ठा sw_flow_key *key,
			 काष्ठा sw_flow_actions **sfa, bool log)
अणु
	पूर्णांक err;
	u32 mpls_label_count = 0;

	*sfa = nla_alloc_flow_actions(min(nla_len(attr), MAX_ACTIONS_बफ_मानE));
	अगर (IS_ERR(*sfa))
		वापस PTR_ERR(*sfa);

	अगर (eth_p_mpls(key->eth.type))
		mpls_label_count = hweight_दीर्घ(key->mpls.num_labels_mask);

	(*sfa)->orig_len = nla_len(attr);
	err = __ovs_nla_copy_actions(net, attr, key, sfa, key->eth.type,
				     key->eth.vlan.tci, mpls_label_count, log);
	अगर (err)
		ovs_nla_मुक्त_flow_actions(*sfa);

	वापस err;
पूर्ण

अटल पूर्णांक sample_action_to_attr(स्थिर काष्ठा nlattr *attr,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start, *ac_start = शून्य, *sample_arg;
	पूर्णांक err = 0, rem = nla_len(attr);
	स्थिर काष्ठा sample_arg *arg;
	काष्ठा nlattr *actions;

	start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_SAMPLE);
	अगर (!start)
		वापस -EMSGSIZE;

	sample_arg = nla_data(attr);
	arg = nla_data(sample_arg);
	actions = nla_next(sample_arg, &rem);

	अगर (nla_put_u32(skb, OVS_SAMPLE_ATTR_PROBABILITY, arg->probability)) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	ac_start = nla_nest_start_noflag(skb, OVS_SAMPLE_ATTR_ACTIONS);
	अगर (!ac_start) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	err = ovs_nla_put_actions(actions, rem, skb);

out:
	अगर (err) अणु
		nla_nest_cancel(skb, ac_start);
		nla_nest_cancel(skb, start);
	पूर्ण अन्यथा अणु
		nla_nest_end(skb, ac_start);
		nla_nest_end(skb, start);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक clone_action_to_attr(स्थिर काष्ठा nlattr *attr,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start;
	पूर्णांक err = 0, rem = nla_len(attr);

	start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_CLONE);
	अगर (!start)
		वापस -EMSGSIZE;

	err = ovs_nla_put_actions(nla_data(attr), rem, skb);

	अगर (err)
		nla_nest_cancel(skb, start);
	अन्यथा
		nla_nest_end(skb, start);

	वापस err;
पूर्ण

अटल पूर्णांक check_pkt_len_action_to_attr(स्थिर काष्ठा nlattr *attr,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start, *ac_start = शून्य;
	स्थिर काष्ठा check_pkt_len_arg *arg;
	स्थिर काष्ठा nlattr *a, *cpl_arg;
	पूर्णांक err = 0, rem = nla_len(attr);

	start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_CHECK_PKT_LEN);
	अगर (!start)
		वापस -EMSGSIZE;

	/* The first nested attribute in 'attr' is always
	 * 'OVS_CHECK_PKT_LEN_ATTR_ARG'.
	 */
	cpl_arg = nla_data(attr);
	arg = nla_data(cpl_arg);

	अगर (nla_put_u16(skb, OVS_CHECK_PKT_LEN_ATTR_PKT_LEN, arg->pkt_len)) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	/* Second nested attribute in 'attr' is always
	 * 'OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL'.
	 */
	a = nla_next(cpl_arg, &rem);
	ac_start =  nla_nest_start_noflag(skb,
					  OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL);
	अगर (!ac_start) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	err = ovs_nla_put_actions(nla_data(a), nla_len(a), skb);
	अगर (err) अणु
		nla_nest_cancel(skb, ac_start);
		जाओ out;
	पूर्ण अन्यथा अणु
		nla_nest_end(skb, ac_start);
	पूर्ण

	/* Third nested attribute in 'attr' is always
	 * OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER.
	 */
	a = nla_next(a, &rem);
	ac_start =  nla_nest_start_noflag(skb,
					  OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER);
	अगर (!ac_start) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	err = ovs_nla_put_actions(nla_data(a), nla_len(a), skb);
	अगर (err) अणु
		nla_nest_cancel(skb, ac_start);
		जाओ out;
	पूर्ण अन्यथा अणु
		nla_nest_end(skb, ac_start);
	पूर्ण

	nla_nest_end(skb, start);
	वापस 0;

out:
	nla_nest_cancel(skb, start);
	वापस err;
पूर्ण

अटल पूर्णांक dec_ttl_action_to_attr(स्थिर काष्ठा nlattr *attr,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start, *action_start;
	स्थिर काष्ठा nlattr *a;
	पूर्णांक err = 0, rem;

	start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_DEC_TTL);
	अगर (!start)
		वापस -EMSGSIZE;

	nla_क्रम_each_attr(a, nla_data(attr), nla_len(attr), rem) अणु
		चयन (nla_type(a)) अणु
		हाल OVS_DEC_TTL_ATTR_ACTION:

			action_start = nla_nest_start_noflag(skb, OVS_DEC_TTL_ATTR_ACTION);
			अगर (!action_start) अणु
				err = -EMSGSIZE;
				जाओ out;
			पूर्ण

			err = ovs_nla_put_actions(nla_data(a), nla_len(a), skb);
			अगर (err)
				जाओ out;

			nla_nest_end(skb, action_start);
			अवरोध;

		शेष:
			/* Ignore all other option to be future compatible */
			अवरोध;
		पूर्ण
	पूर्ण

	nla_nest_end(skb, start);
	वापस 0;

out:
	nla_nest_cancel(skb, start);
	वापस err;
पूर्ण

अटल पूर्णांक set_action_to_attr(स्थिर काष्ठा nlattr *a, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nlattr *ovs_key = nla_data(a);
	पूर्णांक key_type = nla_type(ovs_key);
	काष्ठा nlattr *start;
	पूर्णांक err;

	चयन (key_type) अणु
	हाल OVS_KEY_ATTR_TUNNEL_INFO: अणु
		काष्ठा ovs_tunnel_info *ovs_tun = nla_data(ovs_key);
		काष्ठा ip_tunnel_info *tun_info = &ovs_tun->tun_dst->u.tun_info;

		start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_SET);
		अगर (!start)
			वापस -EMSGSIZE;

		err =  ip_tun_to_nlattr(skb, &tun_info->key,
					ip_tunnel_info_opts(tun_info),
					tun_info->options_len,
					ip_tunnel_info_af(tun_info), tun_info->mode);
		अगर (err)
			वापस err;
		nla_nest_end(skb, start);
		अवरोध;
	पूर्ण
	शेष:
		अगर (nla_put(skb, OVS_ACTION_ATTR_SET, nla_len(a), ovs_key))
			वापस -EMSGSIZE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक masked_set_action_to_set_action_attr(स्थिर काष्ठा nlattr *a,
						काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nlattr *ovs_key = nla_data(a);
	काष्ठा nlattr *nla;
	माप_प्रकार key_len = nla_len(ovs_key) / 2;

	/* Revert the conversion we did from a non-masked set action to
	 * masked set action.
	 */
	nla = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_SET);
	अगर (!nla)
		वापस -EMSGSIZE;

	अगर (nla_put(skb, nla_type(ovs_key), key_len, nla_data(ovs_key)))
		वापस -EMSGSIZE;

	nla_nest_end(skb, nla);
	वापस 0;
पूर्ण

पूर्णांक ovs_nla_put_actions(स्थिर काष्ठा nlattr *attr, पूर्णांक len, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nlattr *a;
	पूर्णांक rem, err;

	nla_क्रम_each_attr(a, attr, len, rem) अणु
		पूर्णांक type = nla_type(a);

		चयन (type) अणु
		हाल OVS_ACTION_ATTR_SET:
			err = set_action_to_attr(a, skb);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_SET_TO_MASKED:
			err = masked_set_action_to_set_action_attr(a, skb);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_SAMPLE:
			err = sample_action_to_attr(a, skb);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_CT:
			err = ovs_ct_action_to_attr(nla_data(a), skb);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_CLONE:
			err = clone_action_to_attr(a, skb);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_CHECK_PKT_LEN:
			err = check_pkt_len_action_to_attr(a, skb);
			अगर (err)
				वापस err;
			अवरोध;

		हाल OVS_ACTION_ATTR_DEC_TTL:
			err = dec_ttl_action_to_attr(a, skb);
			अगर (err)
				वापस err;
			अवरोध;

		शेष:
			अगर (nla_put(skb, type, nla_len(a), nla_data(a)))
				वापस -EMSGSIZE;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
