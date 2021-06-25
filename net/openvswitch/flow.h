<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2017 Nicira, Inc.
 */

#अगर_अघोषित FLOW_H
#घोषणा FLOW_H 1

#समावेश <linux/cache.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in6.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समय.स>
#समावेश <linux/cpumask.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/nsh.h>

काष्ठा sk_buff;

क्रमागत sw_flow_mac_proto अणु
	MAC_PROTO_NONE = 0,
	MAC_PROTO_ETHERNET,
पूर्ण;
#घोषणा SW_FLOW_KEY_INVALID	0x80
#घोषणा MPLS_LABEL_DEPTH       3

/* Store options at the end of the array अगर they are less than the
 * maximum size. This allows us to get the benefits of variable length
 * matching क्रम small options.
 */
#घोषणा TUN_METADATA_OFFSET(opt_len) \
	(माप_field(काष्ठा sw_flow_key, tun_opts) - opt_len)
#घोषणा TUN_METADATA_OPTS(flow_key, opt_len) \
	((व्योम *)((flow_key)->tun_opts + TUN_METADATA_OFFSET(opt_len)))

काष्ठा ovs_tunnel_info अणु
	काष्ठा metadata_dst	*tun_dst;
पूर्ण;

काष्ठा vlan_head अणु
	__be16 tpid; /* Vlan type. Generally 802.1q or 802.1ad.*/
	__be16 tci;  /* 0 अगर no VLAN, VLAN_CFI_MASK set otherwise. */
पूर्ण;

#घोषणा OVS_SW_FLOW_KEY_METADATA_SIZE			\
	(दुरत्व(काष्ठा sw_flow_key, recirc_id) +	\
	माप_field(काष्ठा sw_flow_key, recirc_id))

काष्ठा ovs_key_nsh अणु
	काष्ठा ovs_nsh_key_base base;
	__be32 context[NSH_MD1_CONTEXT_SIZE];
पूर्ण;

काष्ठा sw_flow_key अणु
	u8 tun_opts[IP_TUNNEL_OPTS_MAX];
	u8 tun_opts_len;
	काष्ठा ip_tunnel_key tun_key;	/* Encapsulating tunnel key. */
	काष्ठा अणु
		u32	priority;	/* Packet QoS priority. */
		u32	skb_mark;	/* SKB mark. */
		u16	in_port;	/* Input चयन port (or DP_MAX_PORTS). */
	पूर्ण __packed phy; /* Safe when right after 'tun_key'. */
	u8 mac_proto;			/* MAC layer protocol (e.g. Ethernet). */
	u8 tun_proto;			/* Protocol of encapsulating tunnel. */
	u32 ovs_flow_hash;		/* Datapath computed hash value.  */
	u32 recirc_id;			/* Recirculation ID.  */
	काष्ठा अणु
		u8     src[ETH_ALEN];	/* Ethernet source address. */
		u8     dst[ETH_ALEN];	/* Ethernet destination address. */
		काष्ठा vlan_head vlan;
		काष्ठा vlan_head cvlan;
		__be16 type;		/* Ethernet frame type. */
	पूर्ण eth;
	/* Filling a hole of two bytes. */
	u8 ct_state;
	u8 ct_orig_proto;		/* CT original direction tuple IP
					 * protocol.
					 */
	जोड़ अणु
		काष्ठा अणु
			u8     proto;	/* IP protocol or lower 8 bits of ARP opcode. */
			u8     tos;	    /* IP ToS. */
			u8     ttl;	    /* IP TTL/hop limit. */
			u8     frag;	/* One of OVS_FRAG_TYPE_*. */
		पूर्ण ip;
	पूर्ण;
	u16 ct_zone;			/* Conntrack zone. */
	काष्ठा अणु
		__be16 src;		/* TCP/UDP/SCTP source port. */
		__be16 dst;		/* TCP/UDP/SCTP destination port. */
		__be16 flags;		/* TCP flags. */
	पूर्ण tp;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा अणु
				__be32 src;	/* IP source address. */
				__be32 dst;	/* IP destination address. */
			पूर्ण addr;
			जोड़ अणु
				काष्ठा अणु
					__be32 src;
					__be32 dst;
				पूर्ण ct_orig;	/* Conntrack original direction fields. */
				काष्ठा अणु
					u8 sha[ETH_ALEN];	/* ARP source hardware address. */
					u8 tha[ETH_ALEN];	/* ARP target hardware address. */
				पूर्ण arp;
			पूर्ण;
		पूर्ण ipv4;
		काष्ठा अणु
			काष्ठा अणु
				काष्ठा in6_addr src;	/* IPv6 source address. */
				काष्ठा in6_addr dst;	/* IPv6 destination address. */
			पूर्ण addr;
			__be32 label;			/* IPv6 flow label. */
			जोड़ अणु
				काष्ठा अणु
					काष्ठा in6_addr src;
					काष्ठा in6_addr dst;
				पूर्ण ct_orig;	/* Conntrack original direction fields. */
				काष्ठा अणु
					काष्ठा in6_addr target;	/* ND target address. */
					u8 sll[ETH_ALEN];	/* ND source link layer address. */
					u8 tll[ETH_ALEN];	/* ND target link layer address. */
				पूर्ण nd;
			पूर्ण;
		पूर्ण ipv6;
		काष्ठा अणु
			u32 num_labels_mask;    /* labels present biपंचांगap of effective length MPLS_LABEL_DEPTH */
			__be32 lse[MPLS_LABEL_DEPTH];     /* label stack entry  */
		पूर्ण mpls;

		काष्ठा ovs_key_nsh nsh;         /* network service header */
	पूर्ण;
	काष्ठा अणु
		/* Connection tracking fields not packed above. */
		काष्ठा अणु
			__be16 src;	/* CT orig tuple tp src port. */
			__be16 dst;	/* CT orig tuple tp dst port. */
		पूर्ण orig_tp;
		u32 mark;
		काष्ठा ovs_key_ct_labels labels;
	पूर्ण ct;

पूर्ण __aligned(BITS_PER_LONG/8); /* Ensure that we can करो comparisons as दीर्घs. */

अटल अंतरभूत bool sw_flow_key_is_nd(स्थिर काष्ठा sw_flow_key *key)
अणु
	वापस key->eth.type == htons(ETH_P_IPV6) &&
		key->ip.proto == NEXTHDR_ICMP &&
		key->tp.dst == 0 &&
		(key->tp.src == htons(NDISC_NEIGHBOUR_SOLICITATION) ||
		 key->tp.src == htons(NDISC_NEIGHBOUR_ADVERTISEMENT));
पूर्ण

काष्ठा sw_flow_key_range अणु
	अचिन्हित लघु पूर्णांक start;
	अचिन्हित लघु पूर्णांक end;
पूर्ण;

काष्ठा sw_flow_mask अणु
	पूर्णांक ref_count;
	काष्ठा rcu_head rcu;
	काष्ठा sw_flow_key_range range;
	काष्ठा sw_flow_key key;
पूर्ण;

काष्ठा sw_flow_match अणु
	काष्ठा sw_flow_key *key;
	काष्ठा sw_flow_key_range range;
	काष्ठा sw_flow_mask *mask;
पूर्ण;

#घोषणा MAX_UFID_LENGTH 16 /* 128 bits */

काष्ठा sw_flow_id अणु
	u32 ufid_len;
	जोड़ अणु
		u32 ufid[MAX_UFID_LENGTH / 4];
		काष्ठा sw_flow_key *unmasked_key;
	पूर्ण;
पूर्ण;

काष्ठा sw_flow_actions अणु
	काष्ठा rcu_head rcu;
	माप_प्रकार orig_len;	/* From flow_cmd_new netlink actions size */
	u32 actions_len;
	काष्ठा nlattr actions[];
पूर्ण;

काष्ठा sw_flow_stats अणु
	u64 packet_count;		/* Number of packets matched. */
	u64 byte_count;			/* Number of bytes matched. */
	अचिन्हित दीर्घ used;		/* Last used समय (in jअगरfies). */
	spinlock_t lock;		/* Lock क्रम atomic stats update. */
	__be16 tcp_flags;		/* Union of seen TCP flags. */
पूर्ण;

काष्ठा sw_flow अणु
	काष्ठा rcu_head rcu;
	काष्ठा अणु
		काष्ठा hlist_node node[2];
		u32 hash;
	पूर्ण flow_table, ufid_table;
	पूर्णांक stats_last_ग_लिखोr;		/* CPU id of the last ग_लिखोr on
					 * 'stats[0]'.
					 */
	काष्ठा sw_flow_key key;
	काष्ठा sw_flow_id id;
	काष्ठा cpumask cpu_used_mask;
	काष्ठा sw_flow_mask *mask;
	काष्ठा sw_flow_actions __rcu *sf_acts;
	काष्ठा sw_flow_stats __rcu *stats[]; /* One क्रम each CPU.  First one
					   * is allocated at flow creation समय,
					   * the rest are allocated on demand
					   * जबतक holding the 'stats[0].lock'.
					   */
पूर्ण;

काष्ठा arp_eth_header अणु
	__be16      ar_hrd;	/* क्रमmat of hardware address   */
	__be16      ar_pro;	/* क्रमmat of protocol address   */
	अचिन्हित अक्षर   ar_hln;	/* length of hardware address   */
	अचिन्हित अक्षर   ar_pln;	/* length of protocol address   */
	__be16      ar_op;	/* ARP opcode (command)     */

	/* Ethernet+IPv4 specअगरic members. */
	अचिन्हित अक्षर       ar_sha[ETH_ALEN];	/* sender hardware address  */
	अचिन्हित अक्षर       ar_sip[4];		/* sender IP address        */
	अचिन्हित अक्षर       ar_tha[ETH_ALEN];	/* target hardware address  */
	अचिन्हित अक्षर       ar_tip[4];		/* target IP address        */
पूर्ण __packed;

अटल अंतरभूत u8 ovs_key_mac_proto(स्थिर काष्ठा sw_flow_key *key)
अणु
	वापस key->mac_proto & ~SW_FLOW_KEY_INVALID;
पूर्ण

अटल अंतरभूत u16 __ovs_mac_header_len(u8 mac_proto)
अणु
	वापस mac_proto == MAC_PROTO_ETHERNET ? ETH_HLEN : 0;
पूर्ण

अटल अंतरभूत u16 ovs_mac_header_len(स्थिर काष्ठा sw_flow_key *key)
अणु
	वापस __ovs_mac_header_len(ovs_key_mac_proto(key));
पूर्ण

अटल अंतरभूत bool ovs_identअगरier_is_ufid(स्थिर काष्ठा sw_flow_id *sfid)
अणु
	वापस sfid->ufid_len;
पूर्ण

अटल अंतरभूत bool ovs_identअगरier_is_key(स्थिर काष्ठा sw_flow_id *sfid)
अणु
	वापस !ovs_identअगरier_is_ufid(sfid);
पूर्ण

व्योम ovs_flow_stats_update(काष्ठा sw_flow *, __be16 tcp_flags,
			   स्थिर काष्ठा sk_buff *);
व्योम ovs_flow_stats_get(स्थिर काष्ठा sw_flow *, काष्ठा ovs_flow_stats *,
			अचिन्हित दीर्घ *used, __be16 *tcp_flags);
व्योम ovs_flow_stats_clear(काष्ठा sw_flow *);
u64 ovs_flow_used_समय(अचिन्हित दीर्घ flow_jअगरfies);

पूर्णांक ovs_flow_key_update(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key);
पूर्णांक ovs_flow_key_update_l3l4(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key);
पूर्णांक ovs_flow_key_extract(स्थिर काष्ठा ip_tunnel_info *tun_info,
			 काष्ठा sk_buff *skb,
			 काष्ठा sw_flow_key *key);
/* Extract key from packet coming from userspace. */
पूर्णांक ovs_flow_key_extract_userspace(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
				   काष्ठा sk_buff *skb,
				   काष्ठा sw_flow_key *key, bool log);

#पूर्ण_अगर /* flow.h */
