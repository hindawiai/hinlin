<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_NF_CONNTRACK_COMMON_H
#घोषणा _UAPI_NF_CONNTRACK_COMMON_H
/* Connection state tracking क्रम netfilter.  This is separated from,
   but required by, the NAT layer; it can also be used by an iptables
   extension. */
क्रमागत ip_conntrack_info अणु
	/* Part of an established connection (either direction). */
	IP_CT_ESTABLISHED,

	/* Like NEW, but related to an existing connection, or ICMP error
	   (in either direction). */
	IP_CT_RELATED,

	/* Started a new connection to track (only
           IP_CT_सूची_ORIGINAL); may be a retransmission. */
	IP_CT_NEW,

	/* >= this indicates reply direction */
	IP_CT_IS_REPLY,

	IP_CT_ESTABLISHED_REPLY = IP_CT_ESTABLISHED + IP_CT_IS_REPLY,
	IP_CT_RELATED_REPLY = IP_CT_RELATED + IP_CT_IS_REPLY,
	/* No NEW in reply direction. */

	/* Number of distinct IP_CT types. */
	IP_CT_NUMBER,

	/* only क्रम userspace compatibility */
#अगर_अघोषित __KERNEL__
	IP_CT_NEW_REPLY = IP_CT_NUMBER,
#अन्यथा
	IP_CT_UNTRACKED = 7,
#पूर्ण_अगर
पूर्ण;

#घोषणा NF_CT_STATE_INVALID_BIT			(1 << 0)
#घोषणा NF_CT_STATE_BIT(ctinfo)			(1 << ((ctinfo) % IP_CT_IS_REPLY + 1))
#घोषणा NF_CT_STATE_UNTRACKED_BIT		(1 << 6)

/* Bitset representing status of connection. */
क्रमागत ip_conntrack_status अणु
	/* It's an expected connection: bit 0 set.  This bit never changed */
	IPS_EXPECTED_BIT = 0,
	IPS_EXPECTED = (1 << IPS_EXPECTED_BIT),

	/* We've seen packets both ways: bit 1 set.  Can be set, not unset. */
	IPS_SEEN_REPLY_BIT = 1,
	IPS_SEEN_REPLY = (1 << IPS_SEEN_REPLY_BIT),

	/* Conntrack should never be early-expired. */
	IPS_ASSURED_BIT = 2,
	IPS_ASSURED = (1 << IPS_ASSURED_BIT),

	/* Connection is confirmed: originating packet has left box */
	IPS_CONFIRMED_BIT = 3,
	IPS_CONFIRMED = (1 << IPS_CONFIRMED_BIT),

	/* Connection needs src nat in orig dir.  This bit never changed. */
	IPS_SRC_NAT_BIT = 4,
	IPS_SRC_NAT = (1 << IPS_SRC_NAT_BIT),

	/* Connection needs dst nat in orig dir.  This bit never changed. */
	IPS_DST_NAT_BIT = 5,
	IPS_DST_NAT = (1 << IPS_DST_NAT_BIT),

	/* Both together. */
	IPS_NAT_MASK = (IPS_DST_NAT | IPS_SRC_NAT),

	/* Connection needs TCP sequence adjusted. */
	IPS_SEQ_ADJUST_BIT = 6,
	IPS_SEQ_ADJUST = (1 << IPS_SEQ_ADJUST_BIT),

	/* NAT initialization bits. */
	IPS_SRC_NAT_DONE_BIT = 7,
	IPS_SRC_NAT_DONE = (1 << IPS_SRC_NAT_DONE_BIT),

	IPS_DST_NAT_DONE_BIT = 8,
	IPS_DST_NAT_DONE = (1 << IPS_DST_NAT_DONE_BIT),

	/* Both together */
	IPS_NAT_DONE_MASK = (IPS_DST_NAT_DONE | IPS_SRC_NAT_DONE),

	/* Connection is dying (हटाओd from lists), can not be unset. */
	IPS_DYING_BIT = 9,
	IPS_DYING = (1 << IPS_DYING_BIT),

	/* Connection has fixed समयout. */
	IPS_FIXED_TIMEOUT_BIT = 10,
	IPS_FIXED_TIMEOUT = (1 << IPS_FIXED_TIMEOUT_BIT),

	/* Conntrack is a ढाँचा */
	IPS_TEMPLATE_BIT = 11,
	IPS_TEMPLATE = (1 << IPS_TEMPLATE_BIT),

	/* Conntrack is a fake untracked entry.  Obsolete and not used anymore */
	IPS_UNTRACKED_BIT = 12,
	IPS_UNTRACKED = (1 << IPS_UNTRACKED_BIT),

#अगर_घोषित __KERNEL__
	/* Re-purposed क्रम in-kernel use:
	 * Tags a conntrack entry that clashed with an existing entry
	 * on insert.
	 */
	IPS_NAT_CLASH_BIT = IPS_UNTRACKED_BIT,
	IPS_NAT_CLASH = IPS_UNTRACKED,
#पूर्ण_अगर

	/* Conntrack got a helper explicitly attached via CT target. */
	IPS_HELPER_BIT = 13,
	IPS_HELPER = (1 << IPS_HELPER_BIT),

	/* Conntrack has been offloaded to flow table. */
	IPS_OFFLOAD_BIT = 14,
	IPS_OFFLOAD = (1 << IPS_OFFLOAD_BIT),

	/* Conntrack has been offloaded to hardware. */
	IPS_HW_OFFLOAD_BIT = 15,
	IPS_HW_OFFLOAD = (1 << IPS_HW_OFFLOAD_BIT),

	/* Be careful here, modअगरying these bits can make things messy,
	 * so करोn't let users modअगरy them directly.
	 */
	IPS_UNCHANGEABLE_MASK = (IPS_NAT_DONE_MASK | IPS_NAT_MASK |
				 IPS_EXPECTED | IPS_CONFIRMED | IPS_DYING |
				 IPS_SEQ_ADJUST | IPS_TEMPLATE | IPS_UNTRACKED |
				 IPS_OFFLOAD | IPS_HW_OFFLOAD),

	__IPS_MAX_BIT = 16,
पूर्ण;

/* Connection tracking event types */
क्रमागत ip_conntrack_events अणु
	IPCT_NEW,		/* new conntrack */
	IPCT_RELATED,		/* related conntrack */
	IPCT_DESTROY,		/* destroyed conntrack */
	IPCT_REPLY,		/* connection has seen two-way traffic */
	IPCT_ASSURED,		/* connection status has changed to assured */
	IPCT_PROTOINFO,		/* protocol inक्रमmation has changed */
	IPCT_HELPER,		/* new helper has been set */
	IPCT_MARK,		/* new mark has been set */
	IPCT_SEQADJ,		/* sequence adjusपंचांगent has changed */
	IPCT_NATSEQADJ = IPCT_SEQADJ,
	IPCT_SECMARK,		/* new security mark has been set */
	IPCT_LABEL,		/* new connlabel has been set */
	IPCT_SYNPROXY,		/* synproxy has been set */
#अगर_घोषित __KERNEL__
	__IPCT_MAX
#पूर्ण_अगर
पूर्ण;

क्रमागत ip_conntrack_expect_events अणु
	IPEXP_NEW,		/* new expectation */
	IPEXP_DESTROY,		/* destroyed expectation */
पूर्ण;

/* expectation flags */
#घोषणा NF_CT_EXPECT_PERMANENT		0x1
#घोषणा NF_CT_EXPECT_INACTIVE		0x2
#घोषणा NF_CT_EXPECT_USERSPACE		0x4


#पूर्ण_अगर /* _UAPI_NF_CONNTRACK_COMMON_H */
