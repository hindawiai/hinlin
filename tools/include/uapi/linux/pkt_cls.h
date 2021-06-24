<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_PKT_CLS_H
#घोषणा __LINUX_PKT_CLS_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_sched.h>

#घोषणा TC_COOKIE_MAX_SIZE 16

/* Action attributes */
क्रमागत अणु
	TCA_ACT_UNSPEC,
	TCA_ACT_KIND,
	TCA_ACT_OPTIONS,
	TCA_ACT_INDEX,
	TCA_ACT_STATS,
	TCA_ACT_PAD,
	TCA_ACT_COOKIE,
	__TCA_ACT_MAX
पूर्ण;

#घोषणा TCA_ACT_MAX __TCA_ACT_MAX
#घोषणा TCA_OLD_COMPAT (TCA_ACT_MAX+1)
#घोषणा TCA_ACT_MAX_PRIO 32
#घोषणा TCA_ACT_BIND	1
#घोषणा TCA_ACT_NOBIND	0
#घोषणा TCA_ACT_UNBIND	1
#घोषणा TCA_ACT_NOUNBIND	0
#घोषणा TCA_ACT_REPLACE		1
#घोषणा TCA_ACT_NOREPLACE	0

#घोषणा TC_ACT_UNSPEC	(-1)
#घोषणा TC_ACT_OK		0
#घोषणा TC_ACT_RECLASSIFY	1
#घोषणा TC_ACT_SHOT		2
#घोषणा TC_ACT_PIPE		3
#घोषणा TC_ACT_STOLEN		4
#घोषणा TC_ACT_QUEUED		5
#घोषणा TC_ACT_REPEAT		6
#घोषणा TC_ACT_REसूचीECT		7
#घोषणा TC_ACT_TRAP		8 /* For hw path, this means "trap to cpu"
				   * and करोn't further process the frame
				   * in hardware. For sw path, this is
				   * equivalent of TC_ACT_STOLEN - drop
				   * the skb and act like everything
				   * is alright.
				   */
#घोषणा TC_ACT_VALUE_MAX	TC_ACT_TRAP

/* There is a special kind of actions called "extended actions",
 * which need a value parameter. These have a local opcode located in
 * the highest nibble, starting from 1. The rest of the bits
 * are used to carry the value. These two parts together make
 * a combined opcode.
 */
#घोषणा __TC_ACT_EXT_SHIFT 28
#घोषणा __TC_ACT_EXT(local) ((local) << __TC_ACT_EXT_SHIFT)
#घोषणा TC_ACT_EXT_VAL_MASK ((1 << __TC_ACT_EXT_SHIFT) - 1)
#घोषणा TC_ACT_EXT_OPCODE(combined) ((combined) & (~TC_ACT_EXT_VAL_MASK))
#घोषणा TC_ACT_EXT_CMP(combined, opcode) (TC_ACT_EXT_OPCODE(combined) == opcode)

#घोषणा TC_ACT_JUMP __TC_ACT_EXT(1)
#घोषणा TC_ACT_GOTO_CHAIN __TC_ACT_EXT(2)
#घोषणा TC_ACT_EXT_OPCODE_MAX	TC_ACT_GOTO_CHAIN

/* Action type identअगरiers*/
क्रमागत अणु
	TCA_ID_UNSPEC=0,
	TCA_ID_POLICE=1,
	/* other actions go here */
	__TCA_ID_MAX=255
पूर्ण;

#घोषणा TCA_ID_MAX __TCA_ID_MAX

काष्ठा tc_police अणु
	__u32			index;
	पूर्णांक			action;
#घोषणा TC_POLICE_UNSPEC	TC_ACT_UNSPEC
#घोषणा TC_POLICE_OK		TC_ACT_OK
#घोषणा TC_POLICE_RECLASSIFY	TC_ACT_RECLASSIFY
#घोषणा TC_POLICE_SHOT		TC_ACT_SHOT
#घोषणा TC_POLICE_PIPE		TC_ACT_PIPE

	__u32			limit;
	__u32			burst;
	__u32			mtu;
	काष्ठा tc_ratespec	rate;
	काष्ठा tc_ratespec	peakrate;
	पूर्णांक			refcnt;
	पूर्णांक			bindcnt;
	__u32			capab;
पूर्ण;

काष्ठा tcf_t अणु
	__u64   install;
	__u64   lastuse;
	__u64   expires;
	__u64   firstuse;
पूर्ण;

काष्ठा tc_cnt अणु
	पूर्णांक                   refcnt;
	पूर्णांक                   bindcnt;
पूर्ण;

#घोषणा tc_gen \
	__u32                 index; \
	__u32                 capab; \
	पूर्णांक                   action; \
	पूर्णांक                   refcnt; \
	पूर्णांक                   bindcnt

क्रमागत अणु
	TCA_POLICE_UNSPEC,
	TCA_POLICE_TBF,
	TCA_POLICE_RATE,
	TCA_POLICE_PEAKRATE,
	TCA_POLICE_AVRATE,
	TCA_POLICE_RESULT,
	TCA_POLICE_TM,
	TCA_POLICE_PAD,
	__TCA_POLICE_MAX
#घोषणा TCA_POLICE_RESULT TCA_POLICE_RESULT
पूर्ण;

#घोषणा TCA_POLICE_MAX (__TCA_POLICE_MAX - 1)

/* tca flags definitions */
#घोषणा TCA_CLS_FLAGS_SKIP_HW	(1 << 0) /* करोn't offload filter to HW */
#घोषणा TCA_CLS_FLAGS_SKIP_SW	(1 << 1) /* करोn't use filter in SW */
#घोषणा TCA_CLS_FLAGS_IN_HW	(1 << 2) /* filter is offloaded to HW */
#घोषणा TCA_CLS_FLAGS_NOT_IN_HW (1 << 3) /* filter isn't offloaded to HW */
#घोषणा TCA_CLS_FLAGS_VERBOSE	(1 << 4) /* verbose logging */

/* U32 filters */

#घोषणा TC_U32_HTID(h) ((h)&0xFFF00000)
#घोषणा TC_U32_USERHTID(h) (TC_U32_HTID(h)>>20)
#घोषणा TC_U32_HASH(h) (((h)>>12)&0xFF)
#घोषणा TC_U32_NODE(h) ((h)&0xFFF)
#घोषणा TC_U32_KEY(h) ((h)&0xFFFFF)
#घोषणा TC_U32_UNSPEC	0
#घोषणा TC_U32_ROOT	(0xFFF00000)

क्रमागत अणु
	TCA_U32_UNSPEC,
	TCA_U32_CLASSID,
	TCA_U32_HASH,
	TCA_U32_LINK,
	TCA_U32_DIVISOR,
	TCA_U32_SEL,
	TCA_U32_POLICE,
	TCA_U32_ACT,
	TCA_U32_INDEV,
	TCA_U32_PCNT,
	TCA_U32_MARK,
	TCA_U32_FLAGS,
	TCA_U32_PAD,
	__TCA_U32_MAX
पूर्ण;

#घोषणा TCA_U32_MAX (__TCA_U32_MAX - 1)

काष्ठा tc_u32_key अणु
	__be32		mask;
	__be32		val;
	पूर्णांक		off;
	पूर्णांक		offmask;
पूर्ण;

काष्ठा tc_u32_sel अणु
	अचिन्हित अक्षर		flags;
	अचिन्हित अक्षर		offshअगरt;
	अचिन्हित अक्षर		nkeys;

	__be16			offmask;
	__u16			off;
	लघु			offoff;

	लघु			hoff;
	__be32			hmask;
	काष्ठा tc_u32_key	keys[0];
पूर्ण;

काष्ठा tc_u32_mark अणु
	__u32		val;
	__u32		mask;
	__u32		success;
पूर्ण;

काष्ठा tc_u32_pcnt अणु
	__u64 rcnt;
	__u64 rhit;
	__u64 kcnts[0];
पूर्ण;

/* Flags */

#घोषणा TC_U32_TERMINAL		1
#घोषणा TC_U32_OFFSET		2
#घोषणा TC_U32_VAROFFSET	4
#घोषणा TC_U32_EAT		8

#घोषणा TC_U32_MAXDEPTH 8


/* RSVP filter */

क्रमागत अणु
	TCA_RSVP_UNSPEC,
	TCA_RSVP_CLASSID,
	TCA_RSVP_DST,
	TCA_RSVP_SRC,
	TCA_RSVP_PINFO,
	TCA_RSVP_POLICE,
	TCA_RSVP_ACT,
	__TCA_RSVP_MAX
पूर्ण;

#घोषणा TCA_RSVP_MAX (__TCA_RSVP_MAX - 1 )

काष्ठा tc_rsvp_gpi अणु
	__u32	key;
	__u32	mask;
	पूर्णांक	offset;
पूर्ण;

काष्ठा tc_rsvp_pinfo अणु
	काष्ठा tc_rsvp_gpi dpi;
	काष्ठा tc_rsvp_gpi spi;
	__u8	protocol;
	__u8	tunnelid;
	__u8	tunnelhdr;
	__u8	pad;
पूर्ण;

/* ROUTE filter */

क्रमागत अणु
	TCA_ROUTE4_UNSPEC,
	TCA_ROUTE4_CLASSID,
	TCA_ROUTE4_TO,
	TCA_ROUTE4_FROM,
	TCA_ROUTE4_IIF,
	TCA_ROUTE4_POLICE,
	TCA_ROUTE4_ACT,
	__TCA_ROUTE4_MAX
पूर्ण;

#घोषणा TCA_ROUTE4_MAX (__TCA_ROUTE4_MAX - 1)


/* FW filter */

क्रमागत अणु
	TCA_FW_UNSPEC,
	TCA_FW_CLASSID,
	TCA_FW_POLICE,
	TCA_FW_INDEV,
	TCA_FW_ACT, /* used by CONFIG_NET_CLS_ACT */
	TCA_FW_MASK,
	__TCA_FW_MAX
पूर्ण;

#घोषणा TCA_FW_MAX (__TCA_FW_MAX - 1)

/* TC index filter */

क्रमागत अणु
	TCA_TCINDEX_UNSPEC,
	TCA_TCINDEX_HASH,
	TCA_TCINDEX_MASK,
	TCA_TCINDEX_SHIFT,
	TCA_TCINDEX_FALL_THROUGH,
	TCA_TCINDEX_CLASSID,
	TCA_TCINDEX_POLICE,
	TCA_TCINDEX_ACT,
	__TCA_TCINDEX_MAX
पूर्ण;

#घोषणा TCA_TCINDEX_MAX     (__TCA_TCINDEX_MAX - 1)

/* Flow filter */

क्रमागत अणु
	FLOW_KEY_SRC,
	FLOW_KEY_DST,
	FLOW_KEY_PROTO,
	FLOW_KEY_PROTO_SRC,
	FLOW_KEY_PROTO_DST,
	FLOW_KEY_IIF,
	FLOW_KEY_PRIORITY,
	FLOW_KEY_MARK,
	FLOW_KEY_NFCT,
	FLOW_KEY_NFCT_SRC,
	FLOW_KEY_NFCT_DST,
	FLOW_KEY_NFCT_PROTO_SRC,
	FLOW_KEY_NFCT_PROTO_DST,
	FLOW_KEY_RTCLASSID,
	FLOW_KEY_SKUID,
	FLOW_KEY_SKGID,
	FLOW_KEY_VLAN_TAG,
	FLOW_KEY_RXHASH,
	__FLOW_KEY_MAX,
पूर्ण;

#घोषणा FLOW_KEY_MAX	(__FLOW_KEY_MAX - 1)

क्रमागत अणु
	FLOW_MODE_MAP,
	FLOW_MODE_HASH,
पूर्ण;

क्रमागत अणु
	TCA_FLOW_UNSPEC,
	TCA_FLOW_KEYS,
	TCA_FLOW_MODE,
	TCA_FLOW_BASECLASS,
	TCA_FLOW_RSHIFT,
	TCA_FLOW_ADDEND,
	TCA_FLOW_MASK,
	TCA_FLOW_XOR,
	TCA_FLOW_DIVISOR,
	TCA_FLOW_ACT,
	TCA_FLOW_POLICE,
	TCA_FLOW_EMATCHES,
	TCA_FLOW_PERTURB,
	__TCA_FLOW_MAX
पूर्ण;

#घोषणा TCA_FLOW_MAX	(__TCA_FLOW_MAX - 1)

/* Basic filter */

क्रमागत अणु
	TCA_BASIC_UNSPEC,
	TCA_BASIC_CLASSID,
	TCA_BASIC_EMATCHES,
	TCA_BASIC_ACT,
	TCA_BASIC_POLICE,
	__TCA_BASIC_MAX
पूर्ण;

#घोषणा TCA_BASIC_MAX (__TCA_BASIC_MAX - 1)


/* Cgroup classअगरier */

क्रमागत अणु
	TCA_CGROUP_UNSPEC,
	TCA_CGROUP_ACT,
	TCA_CGROUP_POLICE,
	TCA_CGROUP_EMATCHES,
	__TCA_CGROUP_MAX,
पूर्ण;

#घोषणा TCA_CGROUP_MAX (__TCA_CGROUP_MAX - 1)

/* BPF classअगरier */

#घोषणा TCA_BPF_FLAG_ACT_सूचीECT		(1 << 0)

क्रमागत अणु
	TCA_BPF_UNSPEC,
	TCA_BPF_ACT,
	TCA_BPF_POLICE,
	TCA_BPF_CLASSID,
	TCA_BPF_OPS_LEN,
	TCA_BPF_OPS,
	TCA_BPF_FD,
	TCA_BPF_NAME,
	TCA_BPF_FLAGS,
	TCA_BPF_FLAGS_GEN,
	TCA_BPF_TAG,
	TCA_BPF_ID,
	__TCA_BPF_MAX,
पूर्ण;

#घोषणा TCA_BPF_MAX (__TCA_BPF_MAX - 1)

/* Flower classअगरier */

क्रमागत अणु
	TCA_FLOWER_UNSPEC,
	TCA_FLOWER_CLASSID,
	TCA_FLOWER_INDEV,
	TCA_FLOWER_ACT,
	TCA_FLOWER_KEY_ETH_DST,		/* ETH_ALEN */
	TCA_FLOWER_KEY_ETH_DST_MASK,	/* ETH_ALEN */
	TCA_FLOWER_KEY_ETH_SRC,		/* ETH_ALEN */
	TCA_FLOWER_KEY_ETH_SRC_MASK,	/* ETH_ALEN */
	TCA_FLOWER_KEY_ETH_TYPE,	/* be16 */
	TCA_FLOWER_KEY_IP_PROTO,	/* u8 */
	TCA_FLOWER_KEY_IPV4_SRC,	/* be32 */
	TCA_FLOWER_KEY_IPV4_SRC_MASK,	/* be32 */
	TCA_FLOWER_KEY_IPV4_DST,	/* be32 */
	TCA_FLOWER_KEY_IPV4_DST_MASK,	/* be32 */
	TCA_FLOWER_KEY_IPV6_SRC,	/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_IPV6_SRC_MASK,	/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_IPV6_DST,	/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_IPV6_DST_MASK,	/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_TCP_SRC,		/* be16 */
	TCA_FLOWER_KEY_TCP_DST,		/* be16 */
	TCA_FLOWER_KEY_UDP_SRC,		/* be16 */
	TCA_FLOWER_KEY_UDP_DST,		/* be16 */

	TCA_FLOWER_FLAGS,
	TCA_FLOWER_KEY_VLAN_ID,		/* be16 */
	TCA_FLOWER_KEY_VLAN_PRIO,	/* u8   */
	TCA_FLOWER_KEY_VLAN_ETH_TYPE,	/* be16 */

	TCA_FLOWER_KEY_ENC_KEY_ID,	/* be32 */
	TCA_FLOWER_KEY_ENC_IPV4_SRC,	/* be32 */
	TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK,/* be32 */
	TCA_FLOWER_KEY_ENC_IPV4_DST,	/* be32 */
	TCA_FLOWER_KEY_ENC_IPV4_DST_MASK,/* be32 */
	TCA_FLOWER_KEY_ENC_IPV6_SRC,	/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK,/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_ENC_IPV6_DST,	/* काष्ठा in6_addr */
	TCA_FLOWER_KEY_ENC_IPV6_DST_MASK,/* काष्ठा in6_addr */

	TCA_FLOWER_KEY_TCP_SRC_MASK,	/* be16 */
	TCA_FLOWER_KEY_TCP_DST_MASK,	/* be16 */
	TCA_FLOWER_KEY_UDP_SRC_MASK,	/* be16 */
	TCA_FLOWER_KEY_UDP_DST_MASK,	/* be16 */
	TCA_FLOWER_KEY_SCTP_SRC_MASK,	/* be16 */
	TCA_FLOWER_KEY_SCTP_DST_MASK,	/* be16 */

	TCA_FLOWER_KEY_SCTP_SRC,	/* be16 */
	TCA_FLOWER_KEY_SCTP_DST,	/* be16 */

	TCA_FLOWER_KEY_ENC_UDP_SRC_PORT,	/* be16 */
	TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK,	/* be16 */
	TCA_FLOWER_KEY_ENC_UDP_DST_PORT,	/* be16 */
	TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK,	/* be16 */

	TCA_FLOWER_KEY_FLAGS,		/* be32 */
	TCA_FLOWER_KEY_FLAGS_MASK,	/* be32 */

	TCA_FLOWER_KEY_ICMPV4_CODE,	/* u8 */
	TCA_FLOWER_KEY_ICMPV4_CODE_MASK,/* u8 */
	TCA_FLOWER_KEY_ICMPV4_TYPE,	/* u8 */
	TCA_FLOWER_KEY_ICMPV4_TYPE_MASK,/* u8 */
	TCA_FLOWER_KEY_ICMPV6_CODE,	/* u8 */
	TCA_FLOWER_KEY_ICMPV6_CODE_MASK,/* u8 */
	TCA_FLOWER_KEY_ICMPV6_TYPE,	/* u8 */
	TCA_FLOWER_KEY_ICMPV6_TYPE_MASK,/* u8 */

	TCA_FLOWER_KEY_ARP_SIP,		/* be32 */
	TCA_FLOWER_KEY_ARP_SIP_MASK,	/* be32 */
	TCA_FLOWER_KEY_ARP_TIP,		/* be32 */
	TCA_FLOWER_KEY_ARP_TIP_MASK,	/* be32 */
	TCA_FLOWER_KEY_ARP_OP,		/* u8 */
	TCA_FLOWER_KEY_ARP_OP_MASK,	/* u8 */
	TCA_FLOWER_KEY_ARP_SHA,		/* ETH_ALEN */
	TCA_FLOWER_KEY_ARP_SHA_MASK,	/* ETH_ALEN */
	TCA_FLOWER_KEY_ARP_THA,		/* ETH_ALEN */
	TCA_FLOWER_KEY_ARP_THA_MASK,	/* ETH_ALEN */

	TCA_FLOWER_KEY_MPLS_TTL,	/* u8 - 8 bits */
	TCA_FLOWER_KEY_MPLS_BOS,	/* u8 - 1 bit */
	TCA_FLOWER_KEY_MPLS_TC,		/* u8 - 3 bits */
	TCA_FLOWER_KEY_MPLS_LABEL,	/* be32 - 20 bits */

	TCA_FLOWER_KEY_TCP_FLAGS,	/* be16 */
	TCA_FLOWER_KEY_TCP_FLAGS_MASK,	/* be16 */

	TCA_FLOWER_KEY_IP_TOS,		/* u8 */
	TCA_FLOWER_KEY_IP_TOS_MASK,	/* u8 */
	TCA_FLOWER_KEY_IP_TTL,		/* u8 */
	TCA_FLOWER_KEY_IP_TTL_MASK,	/* u8 */

	TCA_FLOWER_KEY_CVLAN_ID,	/* be16 */
	TCA_FLOWER_KEY_CVLAN_PRIO,	/* u8   */
	TCA_FLOWER_KEY_CVLAN_ETH_TYPE,	/* be16 */

	TCA_FLOWER_KEY_ENC_IP_TOS,	/* u8 */
	TCA_FLOWER_KEY_ENC_IP_TOS_MASK,	/* u8 */
	TCA_FLOWER_KEY_ENC_IP_TTL,	/* u8 */
	TCA_FLOWER_KEY_ENC_IP_TTL_MASK,	/* u8 */

	TCA_FLOWER_KEY_ENC_OPTS,
	TCA_FLOWER_KEY_ENC_OPTS_MASK,

	TCA_FLOWER_IN_HW_COUNT,

	__TCA_FLOWER_MAX,
पूर्ण;

#घोषणा TCA_FLOWER_MAX (__TCA_FLOWER_MAX - 1)

क्रमागत अणु
	TCA_FLOWER_KEY_ENC_OPTS_UNSPEC,
	TCA_FLOWER_KEY_ENC_OPTS_GENEVE, /* Nested
					 * TCA_FLOWER_KEY_ENC_OPT_GENEVE_
					 * attributes
					 */
	__TCA_FLOWER_KEY_ENC_OPTS_MAX,
पूर्ण;

#घोषणा TCA_FLOWER_KEY_ENC_OPTS_MAX (__TCA_FLOWER_KEY_ENC_OPTS_MAX - 1)

क्रमागत अणु
	TCA_FLOWER_KEY_ENC_OPT_GENEVE_UNSPEC,
	TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS,            /* u16 */
	TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE,             /* u8 */
	TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA,             /* 4 to 128 bytes */

	__TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX,
पूर्ण;

#घोषणा TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX \
		(__TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX - 1)

क्रमागत अणु
	TCA_FLOWER_KEY_FLAGS_IS_FRAGMENT = (1 << 0),
	TCA_FLOWER_KEY_FLAGS_FRAG_IS_FIRST = (1 << 1),
पूर्ण;

/* Match-all classअगरier */

क्रमागत अणु
	TCA_MATCHALL_UNSPEC,
	TCA_MATCHALL_CLASSID,
	TCA_MATCHALL_ACT,
	TCA_MATCHALL_FLAGS,
	__TCA_MATCHALL_MAX,
पूर्ण;

#घोषणा TCA_MATCHALL_MAX (__TCA_MATCHALL_MAX - 1)

/* Extended Matches */

काष्ठा tcf_ematch_tree_hdr अणु
	__u16		nmatches;
	__u16		progid;
पूर्ण;

क्रमागत अणु
	TCA_EMATCH_TREE_UNSPEC,
	TCA_EMATCH_TREE_HDR,
	TCA_EMATCH_TREE_LIST,
	__TCA_EMATCH_TREE_MAX
पूर्ण;
#घोषणा TCA_EMATCH_TREE_MAX (__TCA_EMATCH_TREE_MAX - 1)

काष्ठा tcf_ematch_hdr अणु
	__u16		matchid;
	__u16		kind;
	__u16		flags;
	__u16		pad; /* currently unused */
पूर्ण;

/*  0                   1
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 
 * +-----------------------+-+-+---+
 * |         Unused        |S|I| R |
 * +-----------------------+-+-+---+
 *
 * R(2) ::= relation to next ematch
 *          where: 0 0 END (last ematch)
 *                 0 1 AND
 *                 1 0 OR
 *                 1 1 Unused (invalid)
 * I(1) ::= invert result
 * S(1) ::= simple payload
 */
#घोषणा TCF_EM_REL_END	0
#घोषणा TCF_EM_REL_AND	(1<<0)
#घोषणा TCF_EM_REL_OR	(1<<1)
#घोषणा TCF_EM_INVERT	(1<<2)
#घोषणा TCF_EM_SIMPLE	(1<<3)

#घोषणा TCF_EM_REL_MASK	3
#घोषणा TCF_EM_REL_VALID(v) (((v) & TCF_EM_REL_MASK) != TCF_EM_REL_MASK)

क्रमागत अणु
	TCF_LAYER_LINK,
	TCF_LAYER_NETWORK,
	TCF_LAYER_TRANSPORT,
	__TCF_LAYER_MAX
पूर्ण;
#घोषणा TCF_LAYER_MAX (__TCF_LAYER_MAX - 1)

/* Ematch type assignments
 *   1..32767		Reserved क्रम ematches inside kernel tree
 *   32768..65535	Free to use, not reliable
 */
#घोषणा	TCF_EM_CONTAINER	0
#घोषणा	TCF_EM_CMP		1
#घोषणा	TCF_EM_NBYTE		2
#घोषणा	TCF_EM_U32		3
#घोषणा	TCF_EM_META		4
#घोषणा	TCF_EM_TEXT		5
#घोषणा	TCF_EM_VLAN		6
#घोषणा	TCF_EM_CANID		7
#घोषणा	TCF_EM_IPSET		8
#घोषणा	TCF_EM_IPT		9
#घोषणा	TCF_EM_MAX		9

क्रमागत अणु
	TCF_EM_PROG_TC
पूर्ण;

क्रमागत अणु
	TCF_EM_OPND_EQ,
	TCF_EM_OPND_GT,
	TCF_EM_OPND_LT
पूर्ण;

#पूर्ण_अगर
