<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_FLOW_DISSECTOR_H
#घोषणा _NET_FLOW_DISSECTOR_H

#समावेश <linux/types.h>
#समावेश <linux/in6.h>
#समावेश <linux/siphash.h>
#समावेश <linux/माला.स>
#समावेश <uapi/linux/अगर_ether.h>

काष्ठा bpf_prog;
काष्ठा net;
काष्ठा sk_buff;

/**
 * काष्ठा flow_dissector_key_control:
 * @thoff: Transport header offset
 */
काष्ठा flow_dissector_key_control अणु
	u16	thoff;
	u16	addr_type;
	u32	flags;
पूर्ण;

#घोषणा FLOW_DIS_IS_FRAGMENT	BIT(0)
#घोषणा FLOW_DIS_FIRST_FRAG	BIT(1)
#घोषणा FLOW_DIS_ENCAPSULATION	BIT(2)

क्रमागत flow_dissect_ret अणु
	FLOW_DISSECT_RET_OUT_GOOD,
	FLOW_DISSECT_RET_OUT_BAD,
	FLOW_DISSECT_RET_PROTO_AGAIN,
	FLOW_DISSECT_RET_IPPROTO_AGAIN,
	FLOW_DISSECT_RET_CONTINUE,
पूर्ण;

/**
 * काष्ठा flow_dissector_key_basic:
 * @n_proto: Network header protocol (eg. IPv4/IPv6)
 * @ip_proto: Transport header protocol (eg. TCP/UDP)
 */
काष्ठा flow_dissector_key_basic अणु
	__be16	n_proto;
	u8	ip_proto;
	u8	padding;
पूर्ण;

काष्ठा flow_dissector_key_tags अणु
	u32	flow_label;
पूर्ण;

काष्ठा flow_dissector_key_vlan अणु
	जोड़ अणु
		काष्ठा अणु
			u16	vlan_id:12,
				vlan_dei:1,
				vlan_priority:3;
		पूर्ण;
		__be16	vlan_tci;
	पूर्ण;
	__be16	vlan_tpid;
पूर्ण;

काष्ठा flow_dissector_mpls_lse अणु
	u32	mpls_ttl:8,
		mpls_bos:1,
		mpls_tc:3,
		mpls_label:20;
पूर्ण;

#घोषणा FLOW_DIS_MPLS_MAX 7
काष्ठा flow_dissector_key_mpls अणु
	काष्ठा flow_dissector_mpls_lse ls[FLOW_DIS_MPLS_MAX]; /* Label Stack */
	u8 used_lses; /* One bit set क्रम each Label Stack Entry in use */
पूर्ण;

अटल अंतरभूत व्योम dissector_set_mpls_lse(काष्ठा flow_dissector_key_mpls *mpls,
					  पूर्णांक lse_index)
अणु
	mpls->used_lses |= 1 << lse_index;
पूर्ण

#घोषणा FLOW_DIS_TUN_OPTS_MAX 255
/**
 * काष्ठा flow_dissector_key_enc_opts:
 * @data: tunnel option data
 * @len: length of tunnel option data
 * @dst_opt_type: tunnel option type
 */
काष्ठा flow_dissector_key_enc_opts अणु
	u8 data[FLOW_DIS_TUN_OPTS_MAX];	/* Using IP_TUNNEL_OPTS_MAX is desired
					 * here but seems dअगरficult to #समावेश
					 */
	u8 len;
	__be16 dst_opt_type;
पूर्ण;

काष्ठा flow_dissector_key_keyid अणु
	__be32	keyid;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_ipv4_addrs:
 * @src: source ip address
 * @dst: destination ip address
 */
काष्ठा flow_dissector_key_ipv4_addrs अणु
	/* (src,dst) must be grouped, in the same way than in IP header */
	__be32 src;
	__be32 dst;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_ipv6_addrs:
 * @src: source ip address
 * @dst: destination ip address
 */
काष्ठा flow_dissector_key_ipv6_addrs अणु
	/* (src,dst) must be grouped, in the same way than in IP header */
	काष्ठा in6_addr src;
	काष्ठा in6_addr dst;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_tipc:
 * @key: source node address combined with selector
 */
काष्ठा flow_dissector_key_tipc अणु
	__be32 key;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_addrs:
 * @v4addrs: IPv4 addresses
 * @v6addrs: IPv6 addresses
 */
काष्ठा flow_dissector_key_addrs अणु
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs v4addrs;
		काष्ठा flow_dissector_key_ipv6_addrs v6addrs;
		काष्ठा flow_dissector_key_tipc tipckey;
	पूर्ण;
पूर्ण;

/**
 * flow_dissector_key_arp:
 *	@ports: Operation, source and target addresses क्रम an ARP header
 *              क्रम Ethernet hardware addresses and IPv4 protocol addresses
 *		sip: Sender IP address
 *		tip: Target IP address
 *		op:  Operation
 *		sha: Sender hardware address
 *		tpa: Target hardware address
 */
काष्ठा flow_dissector_key_arp अणु
	__u32 sip;
	__u32 tip;
	__u8 op;
	अचिन्हित अक्षर sha[ETH_ALEN];
	अचिन्हित अक्षर tha[ETH_ALEN];
पूर्ण;

/**
 * flow_dissector_key_tp_ports:
 *	@ports: port numbers of Transport header
 *		src: source port number
 *		dst: destination port number
 */
काष्ठा flow_dissector_key_ports अणु
	जोड़ अणु
		__be32 ports;
		काष्ठा अणु
			__be16 src;
			__be16 dst;
		पूर्ण;
	पूर्ण;
पूर्ण;

/**
 * flow_dissector_key_icmp:
 *		type: ICMP type
 *		code: ICMP code
 *		id:   session identअगरier
 */
काष्ठा flow_dissector_key_icmp अणु
	काष्ठा अणु
		u8 type;
		u8 code;
	पूर्ण;
	u16 id;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_eth_addrs:
 * @src: source Ethernet address
 * @dst: destination Ethernet address
 */
काष्ठा flow_dissector_key_eth_addrs अणु
	/* (dst,src) must be grouped, in the same way than in ETH header */
	अचिन्हित अक्षर dst[ETH_ALEN];
	अचिन्हित अक्षर src[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा flow_dissector_key_tcp:
 * @flags: flags
 */
काष्ठा flow_dissector_key_tcp अणु
	__be16 flags;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_ip:
 * @tos: tos
 * @ttl: ttl
 */
काष्ठा flow_dissector_key_ip अणु
	__u8	tos;
	__u8	ttl;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_meta:
 * @ingress_अगरindex: ingress अगरindex
 * @ingress_अगरtype: ingress पूर्णांकerface type
 */
काष्ठा flow_dissector_key_meta अणु
	पूर्णांक ingress_अगरindex;
	u16 ingress_अगरtype;
पूर्ण;

/**
 * काष्ठा flow_dissector_key_ct:
 * @ct_state: conntrack state after converting with map
 * @ct_mark: conttrack mark
 * @ct_zone: conntrack zone
 * @ct_labels: conntrack labels
 */
काष्ठा flow_dissector_key_ct अणु
	u16	ct_state;
	u16	ct_zone;
	u32	ct_mark;
	u32	ct_labels[4];
पूर्ण;

/**
 * काष्ठा flow_dissector_key_hash:
 * @hash: hash value
 */
काष्ठा flow_dissector_key_hash अणु
	u32 hash;
पूर्ण;

क्रमागत flow_dissector_key_id अणु
	FLOW_DISSECTOR_KEY_CONTROL, /* काष्ठा flow_dissector_key_control */
	FLOW_DISSECTOR_KEY_BASIC, /* काष्ठा flow_dissector_key_basic */
	FLOW_DISSECTOR_KEY_IPV4_ADDRS, /* काष्ठा flow_dissector_key_ipv4_addrs */
	FLOW_DISSECTOR_KEY_IPV6_ADDRS, /* काष्ठा flow_dissector_key_ipv6_addrs */
	FLOW_DISSECTOR_KEY_PORTS, /* काष्ठा flow_dissector_key_ports */
	FLOW_DISSECTOR_KEY_PORTS_RANGE, /* काष्ठा flow_dissector_key_ports */
	FLOW_DISSECTOR_KEY_ICMP, /* काष्ठा flow_dissector_key_icmp */
	FLOW_DISSECTOR_KEY_ETH_ADDRS, /* काष्ठा flow_dissector_key_eth_addrs */
	FLOW_DISSECTOR_KEY_TIPC, /* काष्ठा flow_dissector_key_tipc */
	FLOW_DISSECTOR_KEY_ARP, /* काष्ठा flow_dissector_key_arp */
	FLOW_DISSECTOR_KEY_VLAN, /* काष्ठा flow_dissector_key_vlan */
	FLOW_DISSECTOR_KEY_FLOW_LABEL, /* काष्ठा flow_dissector_key_tags */
	FLOW_DISSECTOR_KEY_GRE_KEYID, /* काष्ठा flow_dissector_key_keyid */
	FLOW_DISSECTOR_KEY_MPLS_ENTROPY, /* काष्ठा flow_dissector_key_keyid */
	FLOW_DISSECTOR_KEY_ENC_KEYID, /* काष्ठा flow_dissector_key_keyid */
	FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS, /* काष्ठा flow_dissector_key_ipv4_addrs */
	FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS, /* काष्ठा flow_dissector_key_ipv6_addrs */
	FLOW_DISSECTOR_KEY_ENC_CONTROL, /* काष्ठा flow_dissector_key_control */
	FLOW_DISSECTOR_KEY_ENC_PORTS, /* काष्ठा flow_dissector_key_ports */
	FLOW_DISSECTOR_KEY_MPLS, /* काष्ठा flow_dissector_key_mpls */
	FLOW_DISSECTOR_KEY_TCP, /* काष्ठा flow_dissector_key_tcp */
	FLOW_DISSECTOR_KEY_IP, /* काष्ठा flow_dissector_key_ip */
	FLOW_DISSECTOR_KEY_CVLAN, /* काष्ठा flow_dissector_key_vlan */
	FLOW_DISSECTOR_KEY_ENC_IP, /* काष्ठा flow_dissector_key_ip */
	FLOW_DISSECTOR_KEY_ENC_OPTS, /* काष्ठा flow_dissector_key_enc_opts */
	FLOW_DISSECTOR_KEY_META, /* काष्ठा flow_dissector_key_meta */
	FLOW_DISSECTOR_KEY_CT, /* काष्ठा flow_dissector_key_ct */
	FLOW_DISSECTOR_KEY_HASH, /* काष्ठा flow_dissector_key_hash */

	FLOW_DISSECTOR_KEY_MAX,
पूर्ण;

#घोषणा FLOW_DISSECTOR_F_PARSE_1ST_FRAG		BIT(0)
#घोषणा FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL	BIT(1)
#घोषणा FLOW_DISSECTOR_F_STOP_AT_ENCAP		BIT(2)

काष्ठा flow_dissector_key अणु
	क्रमागत flow_dissector_key_id key_id;
	माप_प्रकार offset; /* offset of काष्ठा flow_dissector_key_*
			  in target the काष्ठा */
पूर्ण;

काष्ठा flow_dissector अणु
	अचिन्हित पूर्णांक used_keys; /* each bit repesents presence of one key id */
	अचिन्हित लघु पूर्णांक offset[FLOW_DISSECTOR_KEY_MAX];
पूर्ण;

काष्ठा flow_keys_basic अणु
	काष्ठा flow_dissector_key_control control;
	काष्ठा flow_dissector_key_basic basic;
पूर्ण;

काष्ठा flow_keys अणु
	काष्ठा flow_dissector_key_control control;
#घोषणा FLOW_KEYS_HASH_START_FIELD basic
	काष्ठा flow_dissector_key_basic basic __aligned(SIPHASH_ALIGNMENT);
	काष्ठा flow_dissector_key_tags tags;
	काष्ठा flow_dissector_key_vlan vlan;
	काष्ठा flow_dissector_key_vlan cvlan;
	काष्ठा flow_dissector_key_keyid keyid;
	काष्ठा flow_dissector_key_ports ports;
	काष्ठा flow_dissector_key_icmp icmp;
	/* 'addrs' must be the last member */
	काष्ठा flow_dissector_key_addrs addrs;
पूर्ण;

#घोषणा FLOW_KEYS_HASH_OFFSET		\
	दुरत्व(काष्ठा flow_keys, FLOW_KEYS_HASH_START_FIELD)

__be32 flow_get_u32_src(स्थिर काष्ठा flow_keys *flow);
__be32 flow_get_u32_dst(स्थिर काष्ठा flow_keys *flow);

बाह्य काष्ठा flow_dissector flow_keys_dissector;
बाह्य काष्ठा flow_dissector flow_keys_basic_dissector;

/* काष्ठा flow_keys_digest:
 *
 * This काष्ठाure is used to hold a digest of the full flow keys. This is a
 * larger "hash" of a flow to allow definitively matching specअगरic flows where
 * the 32 bit skb->hash is not large enough. The size is limited to 16 bytes so
 * that it can be used in CB of skb (see sch_choke क्रम an example).
 */
#घोषणा FLOW_KEYS_DIGEST_LEN	16
काष्ठा flow_keys_digest अणु
	u8	data[FLOW_KEYS_DIGEST_LEN];
पूर्ण;

व्योम make_flow_keys_digest(काष्ठा flow_keys_digest *digest,
			   स्थिर काष्ठा flow_keys *flow);

अटल अंतरभूत bool flow_keys_have_l4(स्थिर काष्ठा flow_keys *keys)
अणु
	वापस (keys->ports.ports || keys->tags.flow_label);
पूर्ण

u32 flow_hash_from_keys(काष्ठा flow_keys *keys);
व्योम skb_flow_get_icmp_tci(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा flow_dissector_key_icmp *key_icmp,
			   स्थिर व्योम *data, पूर्णांक thoff, पूर्णांक hlen);

अटल अंतरभूत bool dissector_uses_key(स्थिर काष्ठा flow_dissector *flow_dissector,
				      क्रमागत flow_dissector_key_id key_id)
अणु
	वापस flow_dissector->used_keys & (1 << key_id);
पूर्ण

अटल अंतरभूत व्योम *skb_flow_dissector_target(काष्ठा flow_dissector *flow_dissector,
					      क्रमागत flow_dissector_key_id key_id,
					      व्योम *target_container)
अणु
	वापस ((अक्षर *)target_container) + flow_dissector->offset[key_id];
पूर्ण

काष्ठा bpf_flow_dissector अणु
	काष्ठा bpf_flow_keys	*flow_keys;
	स्थिर काष्ठा sk_buff	*skb;
	स्थिर व्योम		*data;
	स्थिर व्योम		*data_end;
पूर्ण;

अटल अंतरभूत व्योम
flow_dissector_init_keys(काष्ठा flow_dissector_key_control *key_control,
			 काष्ठा flow_dissector_key_basic *key_basic)
अणु
	स_रखो(key_control, 0, माप(*key_control));
	स_रखो(key_basic, 0, माप(*key_basic));
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
पूर्णांक flow_dissector_bpf_prog_attach_check(काष्ठा net *net,
					 काष्ठा bpf_prog *prog);
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

#पूर्ण_अगर
