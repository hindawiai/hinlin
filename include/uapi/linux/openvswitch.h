<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */

/*
 * Copyright (c) 2007-2017 Nicira, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA
 * 02110-1301, USA
 */

#अगर_अघोषित _UAPI__LINUX_OPENVSWITCH_H
#घोषणा _UAPI__LINUX_OPENVSWITCH_H 1

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

/**
 * काष्ठा ovs_header - header क्रम OVS Generic Netlink messages.
 * @dp_अगरindex: अगरindex of local port क्रम datapath (0 to make a request not
 * specअगरic to a datapath).
 *
 * Attributes following the header are specअगरic to a particular OVS Generic
 * Netlink family, but all of the OVS families use this header.
 */

काष्ठा ovs_header अणु
	पूर्णांक dp_अगरindex;
पूर्ण;

/* Datapaths. */

#घोषणा OVS_DATAPATH_FAMILY  "ovs_datapath"
#घोषणा OVS_DATAPATH_MCGROUP "ovs_datapath"

/* V2:
 *   - API users are expected to provide OVS_DP_ATTR_USER_FEATURES
 *     when creating the datapath.
 */
#घोषणा OVS_DATAPATH_VERSION 2

/* First OVS datapath version to support features */
#घोषणा OVS_DP_VER_FEATURES 2

क्रमागत ovs_datapath_cmd अणु
	OVS_DP_CMD_UNSPEC,
	OVS_DP_CMD_NEW,
	OVS_DP_CMD_DEL,
	OVS_DP_CMD_GET,
	OVS_DP_CMD_SET
पूर्ण;

/**
 * क्रमागत ovs_datapath_attr - attributes क्रम %OVS_DP_* commands.
 * @OVS_DP_ATTR_NAME: Name of the network device that serves as the "local
 * port".  This is the name of the network device whose dp_अगरindex is given in
 * the &काष्ठा ovs_header.  Always present in notअगरications.  Required in
 * %OVS_DP_NEW requests.  May be used as an alternative to specअगरying
 * dp_अगरindex in other requests (with a dp_अगरindex of 0).
 * @OVS_DP_ATTR_UPCALL_PID: The Netlink socket in userspace that is initially
 * set on the datapath port (क्रम OVS_ACTION_ATTR_MISS).  Only valid on
 * %OVS_DP_CMD_NEW requests. A value of zero indicates that upcalls should
 * not be sent.
 * @OVS_DP_ATTR_STATS: Statistics about packets that have passed through the
 * datapath.  Always present in notअगरications.
 * @OVS_DP_ATTR_MEGAFLOW_STATS: Statistics about mega flow masks usage क्रम the
 * datapath. Always present in notअगरications.
 *
 * These attributes follow the &काष्ठा ovs_header within the Generic Netlink
 * payload क्रम %OVS_DP_* commands.
 */
क्रमागत ovs_datapath_attr अणु
	OVS_DP_ATTR_UNSPEC,
	OVS_DP_ATTR_NAME,		/* name of dp_अगरindex netdev */
	OVS_DP_ATTR_UPCALL_PID,		/* Netlink PID to receive upcalls */
	OVS_DP_ATTR_STATS,		/* काष्ठा ovs_dp_stats */
	OVS_DP_ATTR_MEGAFLOW_STATS,	/* काष्ठा ovs_dp_megaflow_stats */
	OVS_DP_ATTR_USER_FEATURES,	/* OVS_DP_F_*  */
	OVS_DP_ATTR_PAD,
	OVS_DP_ATTR_MASKS_CACHE_SIZE,
	__OVS_DP_ATTR_MAX
पूर्ण;

#घोषणा OVS_DP_ATTR_MAX (__OVS_DP_ATTR_MAX - 1)

काष्ठा ovs_dp_stats अणु
	__u64 n_hit;             /* Number of flow table matches. */
	__u64 n_missed;          /* Number of flow table misses. */
	__u64 n_lost;            /* Number of misses not sent to userspace. */
	__u64 n_flows;           /* Number of flows present */
पूर्ण;

काष्ठा ovs_dp_megaflow_stats अणु
	__u64 n_mask_hit;	 /* Number of masks used क्रम flow lookups. */
	__u32 n_masks;		 /* Number of masks क्रम the datapath. */
	__u32 pad0;		 /* Pad क्रम future expension. */
	__u64 n_cache_hit;       /* Number of cache matches क्रम flow lookups. */
	__u64 pad1;		 /* Pad क्रम future expension. */
पूर्ण;

काष्ठा ovs_vport_stats अणु
	__u64   rx_packets;		/* total packets received       */
	__u64   tx_packets;		/* total packets transmitted    */
	__u64   rx_bytes;		/* total bytes received         */
	__u64   tx_bytes;		/* total bytes transmitted      */
	__u64   rx_errors;		/* bad packets received         */
	__u64   tx_errors;		/* packet transmit problems     */
	__u64   rx_dropped;		/* no space in linux buffers    */
	__u64   tx_dropped;		/* no space available in linux  */
पूर्ण;

/* Allow last Netlink attribute to be unaligned */
#घोषणा OVS_DP_F_UNALIGNED	(1 << 0)

/* Allow datapath to associate multiple Netlink PIDs to each vport */
#घोषणा OVS_DP_F_VPORT_PIDS	(1 << 1)

/* Allow tc offload recirc sharing */
#घोषणा OVS_DP_F_TC_RECIRC_SHARING	(1 << 2)

/* Fixed logical ports. */
#घोषणा OVSP_LOCAL      ((__u32)0)

/* Packet transfer. */

#घोषणा OVS_PACKET_FAMILY "ovs_packet"
#घोषणा OVS_PACKET_VERSION 0x1

क्रमागत ovs_packet_cmd अणु
	OVS_PACKET_CMD_UNSPEC,

	/* Kernel-to-user notअगरications. */
	OVS_PACKET_CMD_MISS,    /* Flow table miss. */
	OVS_PACKET_CMD_ACTION,  /* OVS_ACTION_ATTR_USERSPACE action. */

	/* Userspace commands. */
	OVS_PACKET_CMD_EXECUTE  /* Apply actions to a packet. */
पूर्ण;

/**
 * क्रमागत ovs_packet_attr - attributes क्रम %OVS_PACKET_* commands.
 * @OVS_PACKET_ATTR_PACKET: Present क्रम all notअगरications.  Contains the entire
 * packet as received, from the start of the Ethernet header onward.  For
 * %OVS_PACKET_CMD_ACTION, %OVS_PACKET_ATTR_PACKET reflects changes made by
 * actions preceding %OVS_ACTION_ATTR_USERSPACE, but %OVS_PACKET_ATTR_KEY is
 * the flow key extracted from the packet as originally received.
 * @OVS_PACKET_ATTR_KEY: Present क्रम all notअगरications.  Contains the flow key
 * extracted from the packet as nested %OVS_KEY_ATTR_* attributes.  This allows
 * userspace to adapt its flow setup strategy by comparing its notion of the
 * flow key against the kernel's.
 * @OVS_PACKET_ATTR_ACTIONS: Contains actions क्रम the packet.  Used
 * क्रम %OVS_PACKET_CMD_EXECUTE.  It has nested %OVS_ACTION_ATTR_* attributes.
 * Also used in upcall when %OVS_ACTION_ATTR_USERSPACE has optional
 * %OVS_USERSPACE_ATTR_ACTIONS attribute.
 * @OVS_PACKET_ATTR_USERDATA: Present क्रम an %OVS_PACKET_CMD_ACTION
 * notअगरication अगर the %OVS_ACTION_ATTR_USERSPACE action specअगरied an
 * %OVS_USERSPACE_ATTR_USERDATA attribute, with the same length and content
 * specअगरied there.
 * @OVS_PACKET_ATTR_EGRESS_TUN_KEY: Present क्रम an %OVS_PACKET_CMD_ACTION
 * notअगरication अगर the %OVS_ACTION_ATTR_USERSPACE action specअगरied an
 * %OVS_USERSPACE_ATTR_EGRESS_TUN_PORT attribute, which is sent only अगर the
 * output port is actually a tunnel port. Contains the output tunnel key
 * extracted from the packet as nested %OVS_TUNNEL_KEY_ATTR_* attributes.
 * @OVS_PACKET_ATTR_MRU: Present क्रम an %OVS_PACKET_CMD_ACTION and
 * @OVS_PACKET_ATTR_LEN: Packet size beक्रमe truncation.
 * %OVS_PACKET_ATTR_USERSPACE action specअगरy the Maximum received fragment
 * size.
 * @OVS_PACKET_ATTR_HASH: Packet hash info (e.g. hash, sw_hash and l4_hash in skb).
 *
 * These attributes follow the &काष्ठा ovs_header within the Generic Netlink
 * payload क्रम %OVS_PACKET_* commands.
 */
क्रमागत ovs_packet_attr अणु
	OVS_PACKET_ATTR_UNSPEC,
	OVS_PACKET_ATTR_PACKET,      /* Packet data. */
	OVS_PACKET_ATTR_KEY,         /* Nested OVS_KEY_ATTR_* attributes. */
	OVS_PACKET_ATTR_ACTIONS,     /* Nested OVS_ACTION_ATTR_* attributes. */
	OVS_PACKET_ATTR_USERDATA,    /* OVS_ACTION_ATTR_USERSPACE arg. */
	OVS_PACKET_ATTR_EGRESS_TUN_KEY,  /* Nested OVS_TUNNEL_KEY_ATTR_*
					    attributes. */
	OVS_PACKET_ATTR_UNUSED1,
	OVS_PACKET_ATTR_UNUSED2,
	OVS_PACKET_ATTR_PROBE,      /* Packet operation is a feature probe,
				       error logging should be suppressed. */
	OVS_PACKET_ATTR_MRU,	    /* Maximum received IP fragment size. */
	OVS_PACKET_ATTR_LEN,	    /* Packet size beक्रमe truncation. */
	OVS_PACKET_ATTR_HASH,	    /* Packet hash. */
	__OVS_PACKET_ATTR_MAX
पूर्ण;

#घोषणा OVS_PACKET_ATTR_MAX (__OVS_PACKET_ATTR_MAX - 1)

/* Virtual ports. */

#घोषणा OVS_VPORT_FAMILY  "ovs_vport"
#घोषणा OVS_VPORT_MCGROUP "ovs_vport"
#घोषणा OVS_VPORT_VERSION 0x1

क्रमागत ovs_vport_cmd अणु
	OVS_VPORT_CMD_UNSPEC,
	OVS_VPORT_CMD_NEW,
	OVS_VPORT_CMD_DEL,
	OVS_VPORT_CMD_GET,
	OVS_VPORT_CMD_SET
पूर्ण;

क्रमागत ovs_vport_type अणु
	OVS_VPORT_TYPE_UNSPEC,
	OVS_VPORT_TYPE_NETDEV,   /* network device */
	OVS_VPORT_TYPE_INTERNAL, /* network device implemented by datapath */
	OVS_VPORT_TYPE_GRE,      /* GRE tunnel. */
	OVS_VPORT_TYPE_VXLAN,	 /* VXLAN tunnel. */
	OVS_VPORT_TYPE_GENEVE,	 /* Geneve tunnel. */
	__OVS_VPORT_TYPE_MAX
पूर्ण;

#घोषणा OVS_VPORT_TYPE_MAX (__OVS_VPORT_TYPE_MAX - 1)

/**
 * क्रमागत ovs_vport_attr - attributes क्रम %OVS_VPORT_* commands.
 * @OVS_VPORT_ATTR_PORT_NO: 32-bit port number within datapath.
 * @OVS_VPORT_ATTR_TYPE: 32-bit %OVS_VPORT_TYPE_* स्थिरant describing the type
 * of vport.
 * @OVS_VPORT_ATTR_NAME: Name of vport.  For a vport based on a network device
 * this is the name of the network device.  Maximum length %IFNAMSIZ-1 bytes
 * plus a null terminator.
 * @OVS_VPORT_ATTR_OPTIONS: Vport-specअगरic configuration inक्रमmation.
 * @OVS_VPORT_ATTR_UPCALL_PID: The array of Netlink socket pids in userspace
 * among which OVS_PACKET_CMD_MISS upcalls will be distributed क्रम packets
 * received on this port.  If this is a single-element array of value 0,
 * upcalls should not be sent.
 * @OVS_VPORT_ATTR_STATS: A &काष्ठा ovs_vport_stats giving statistics क्रम
 * packets sent or received through the vport.
 *
 * These attributes follow the &काष्ठा ovs_header within the Generic Netlink
 * payload क्रम %OVS_VPORT_* commands.
 *
 * For %OVS_VPORT_CMD_NEW requests, the %OVS_VPORT_ATTR_TYPE and
 * %OVS_VPORT_ATTR_NAME attributes are required.  %OVS_VPORT_ATTR_PORT_NO is
 * optional; अगर not specअगरied a मुक्त port number is स्वतःmatically selected.
 * Whether %OVS_VPORT_ATTR_OPTIONS is required or optional depends on the type
 * of vport.
 *
 * For other requests, अगर %OVS_VPORT_ATTR_NAME is specअगरied then it is used to
 * look up the vport to operate on; otherwise dp_idx from the &काष्ठा
 * ovs_header plus %OVS_VPORT_ATTR_PORT_NO determine the vport.
 */
क्रमागत ovs_vport_attr अणु
	OVS_VPORT_ATTR_UNSPEC,
	OVS_VPORT_ATTR_PORT_NO,	/* u32 port number within datapath */
	OVS_VPORT_ATTR_TYPE,	/* u32 OVS_VPORT_TYPE_* स्थिरant. */
	OVS_VPORT_ATTR_NAME,	/* string name, up to IFNAMSIZ bytes दीर्घ */
	OVS_VPORT_ATTR_OPTIONS, /* nested attributes, varies by vport type */
	OVS_VPORT_ATTR_UPCALL_PID, /* array of u32 Netlink socket PIDs क्रम */
				/* receiving upcalls */
	OVS_VPORT_ATTR_STATS,	/* काष्ठा ovs_vport_stats */
	OVS_VPORT_ATTR_PAD,
	OVS_VPORT_ATTR_IFINDEX,
	OVS_VPORT_ATTR_NETNSID,
	__OVS_VPORT_ATTR_MAX
पूर्ण;

#घोषणा OVS_VPORT_ATTR_MAX (__OVS_VPORT_ATTR_MAX - 1)

क्रमागत अणु
	OVS_VXLAN_EXT_UNSPEC,
	OVS_VXLAN_EXT_GBP,	/* Flag or __u32 */
	__OVS_VXLAN_EXT_MAX,
पूर्ण;

#घोषणा OVS_VXLAN_EXT_MAX (__OVS_VXLAN_EXT_MAX - 1)


/* OVS_VPORT_ATTR_OPTIONS attributes क्रम tunnels.
 */
क्रमागत अणु
	OVS_TUNNEL_ATTR_UNSPEC,
	OVS_TUNNEL_ATTR_DST_PORT, /* 16-bit UDP port, used by L4 tunnels. */
	OVS_TUNNEL_ATTR_EXTENSION,
	__OVS_TUNNEL_ATTR_MAX
पूर्ण;

#घोषणा OVS_TUNNEL_ATTR_MAX (__OVS_TUNNEL_ATTR_MAX - 1)

/* Flows. */

#घोषणा OVS_FLOW_FAMILY  "ovs_flow"
#घोषणा OVS_FLOW_MCGROUP "ovs_flow"
#घोषणा OVS_FLOW_VERSION 0x1

क्रमागत ovs_flow_cmd अणु
	OVS_FLOW_CMD_UNSPEC,
	OVS_FLOW_CMD_NEW,
	OVS_FLOW_CMD_DEL,
	OVS_FLOW_CMD_GET,
	OVS_FLOW_CMD_SET
पूर्ण;

काष्ठा ovs_flow_stats अणु
	__u64 n_packets;         /* Number of matched packets. */
	__u64 n_bytes;           /* Number of matched bytes. */
पूर्ण;

क्रमागत ovs_key_attr अणु
	OVS_KEY_ATTR_UNSPEC,
	OVS_KEY_ATTR_ENCAP,	/* Nested set of encapsulated attributes. */
	OVS_KEY_ATTR_PRIORITY,  /* u32 skb->priority */
	OVS_KEY_ATTR_IN_PORT,   /* u32 OVS dp port number */
	OVS_KEY_ATTR_ETHERNET,  /* काष्ठा ovs_key_ethernet */
	OVS_KEY_ATTR_VLAN,	/* be16 VLAN TCI */
	OVS_KEY_ATTR_ETHERTYPE,	/* be16 Ethernet type */
	OVS_KEY_ATTR_IPV4,      /* काष्ठा ovs_key_ipv4 */
	OVS_KEY_ATTR_IPV6,      /* काष्ठा ovs_key_ipv6 */
	OVS_KEY_ATTR_TCP,       /* काष्ठा ovs_key_tcp */
	OVS_KEY_ATTR_UDP,       /* काष्ठा ovs_key_udp */
	OVS_KEY_ATTR_ICMP,      /* काष्ठा ovs_key_icmp */
	OVS_KEY_ATTR_ICMPV6,    /* काष्ठा ovs_key_icmpv6 */
	OVS_KEY_ATTR_ARP,       /* काष्ठा ovs_key_arp */
	OVS_KEY_ATTR_ND,        /* काष्ठा ovs_key_nd */
	OVS_KEY_ATTR_SKB_MARK,  /* u32 skb mark */
	OVS_KEY_ATTR_TUNNEL,    /* Nested set of ovs_tunnel attributes */
	OVS_KEY_ATTR_SCTP,      /* काष्ठा ovs_key_sctp */
	OVS_KEY_ATTR_TCP_FLAGS,	/* be16 TCP flags. */
	OVS_KEY_ATTR_DP_HASH,      /* u32 hash value. Value 0 indicates the hash
				   is not computed by the datapath. */
	OVS_KEY_ATTR_RECIRC_ID, /* u32 recirc id */
	OVS_KEY_ATTR_MPLS,      /* array of काष्ठा ovs_key_mpls.
				 * The implementation may restrict
				 * the accepted length of the array. */
	OVS_KEY_ATTR_CT_STATE,	/* u32 biपंचांगask of OVS_CS_F_* */
	OVS_KEY_ATTR_CT_ZONE,	/* u16 connection tracking zone. */
	OVS_KEY_ATTR_CT_MARK,	/* u32 connection tracking mark */
	OVS_KEY_ATTR_CT_LABELS,	/* 16-octet connection tracking label */
	OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4,   /* काष्ठा ovs_key_ct_tuple_ipv4 */
	OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6,   /* काष्ठा ovs_key_ct_tuple_ipv6 */
	OVS_KEY_ATTR_NSH,       /* Nested set of ovs_nsh_key_* */

#अगर_घोषित __KERNEL__
	OVS_KEY_ATTR_TUNNEL_INFO,  /* काष्ठा ip_tunnel_info */
#पूर्ण_अगर
	__OVS_KEY_ATTR_MAX
पूर्ण;

#घोषणा OVS_KEY_ATTR_MAX (__OVS_KEY_ATTR_MAX - 1)

क्रमागत ovs_tunnel_key_attr अणु
	/* OVS_TUNNEL_KEY_ATTR_NONE, standard nl API requires this attribute! */
	OVS_TUNNEL_KEY_ATTR_ID,                 /* be64 Tunnel ID */
	OVS_TUNNEL_KEY_ATTR_IPV4_SRC,           /* be32 src IP address. */
	OVS_TUNNEL_KEY_ATTR_IPV4_DST,           /* be32 dst IP address. */
	OVS_TUNNEL_KEY_ATTR_TOS,                /* u8 Tunnel IP ToS. */
	OVS_TUNNEL_KEY_ATTR_TTL,                /* u8 Tunnel IP TTL. */
	OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT,      /* No argument, set DF. */
	OVS_TUNNEL_KEY_ATTR_CSUM,               /* No argument. CSUM packet. */
	OVS_TUNNEL_KEY_ATTR_OAM,                /* No argument. OAM frame.  */
	OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS,        /* Array of Geneve options. */
	OVS_TUNNEL_KEY_ATTR_TP_SRC,		/* be16 src Transport Port. */
	OVS_TUNNEL_KEY_ATTR_TP_DST,		/* be16 dst Transport Port. */
	OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS,		/* Nested OVS_VXLAN_EXT_* */
	OVS_TUNNEL_KEY_ATTR_IPV6_SRC,		/* काष्ठा in6_addr src IPv6 address. */
	OVS_TUNNEL_KEY_ATTR_IPV6_DST,		/* काष्ठा in6_addr dst IPv6 address. */
	OVS_TUNNEL_KEY_ATTR_PAD,
	OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS,	/* काष्ठा erspan_metadata */
	OVS_TUNNEL_KEY_ATTR_IPV4_INFO_BRIDGE,	/* No argument. IPV4_INFO_BRIDGE mode.*/
	__OVS_TUNNEL_KEY_ATTR_MAX
पूर्ण;

#घोषणा OVS_TUNNEL_KEY_ATTR_MAX (__OVS_TUNNEL_KEY_ATTR_MAX - 1)

/**
 * क्रमागत ovs_frag_type - IPv4 and IPv6 fragment type
 * @OVS_FRAG_TYPE_NONE: Packet is not a fragment.
 * @OVS_FRAG_TYPE_FIRST: Packet is a fragment with offset 0.
 * @OVS_FRAG_TYPE_LATER: Packet is a fragment with nonzero offset.
 *
 * Used as the @ipv4_frag in &काष्ठा ovs_key_ipv4 and as @ipv6_frag &काष्ठा
 * ovs_key_ipv6.
 */
क्रमागत ovs_frag_type अणु
	OVS_FRAG_TYPE_NONE,
	OVS_FRAG_TYPE_FIRST,
	OVS_FRAG_TYPE_LATER,
	__OVS_FRAG_TYPE_MAX
पूर्ण;

#घोषणा OVS_FRAG_TYPE_MAX (__OVS_FRAG_TYPE_MAX - 1)

काष्ठा ovs_key_ethernet अणु
	__u8	 eth_src[ETH_ALEN];
	__u8	 eth_dst[ETH_ALEN];
पूर्ण;

काष्ठा ovs_key_mpls अणु
	__be32 mpls_lse;
पूर्ण;

काष्ठा ovs_key_ipv4 अणु
	__be32 ipv4_src;
	__be32 ipv4_dst;
	__u8   ipv4_proto;
	__u8   ipv4_tos;
	__u8   ipv4_ttl;
	__u8   ipv4_frag;	/* One of OVS_FRAG_TYPE_*. */
पूर्ण;

काष्ठा ovs_key_ipv6 अणु
	__be32 ipv6_src[4];
	__be32 ipv6_dst[4];
	__be32 ipv6_label;	/* 20-bits in least-signअगरicant bits. */
	__u8   ipv6_proto;
	__u8   ipv6_tclass;
	__u8   ipv6_hlimit;
	__u8   ipv6_frag;	/* One of OVS_FRAG_TYPE_*. */
पूर्ण;

काष्ठा ovs_key_tcp अणु
	__be16 tcp_src;
	__be16 tcp_dst;
पूर्ण;

काष्ठा ovs_key_udp अणु
	__be16 udp_src;
	__be16 udp_dst;
पूर्ण;

काष्ठा ovs_key_sctp अणु
	__be16 sctp_src;
	__be16 sctp_dst;
पूर्ण;

काष्ठा ovs_key_icmp अणु
	__u8 icmp_type;
	__u8 icmp_code;
पूर्ण;

काष्ठा ovs_key_icmpv6 अणु
	__u8 icmpv6_type;
	__u8 icmpv6_code;
पूर्ण;

काष्ठा ovs_key_arp अणु
	__be32 arp_sip;
	__be32 arp_tip;
	__be16 arp_op;
	__u8   arp_sha[ETH_ALEN];
	__u8   arp_tha[ETH_ALEN];
पूर्ण;

काष्ठा ovs_key_nd अणु
	__be32	nd_target[4];
	__u8	nd_sll[ETH_ALEN];
	__u8	nd_tll[ETH_ALEN];
पूर्ण;

#घोषणा OVS_CT_LABELS_LEN_32	4
#घोषणा OVS_CT_LABELS_LEN	(OVS_CT_LABELS_LEN_32 * माप(__u32))
काष्ठा ovs_key_ct_labels अणु
	जोड़ अणु
		__u8	ct_labels[OVS_CT_LABELS_LEN];
		__u32	ct_labels_32[OVS_CT_LABELS_LEN_32];
	पूर्ण;
पूर्ण;

/* OVS_KEY_ATTR_CT_STATE flags */
#घोषणा OVS_CS_F_NEW               0x01 /* Beginning of a new connection. */
#घोषणा OVS_CS_F_ESTABLISHED       0x02 /* Part of an existing connection. */
#घोषणा OVS_CS_F_RELATED           0x04 /* Related to an established
					 * connection. */
#घोषणा OVS_CS_F_REPLY_सूची         0x08 /* Flow is in the reply direction. */
#घोषणा OVS_CS_F_INVALID           0x10 /* Could not track connection. */
#घोषणा OVS_CS_F_TRACKED           0x20 /* Conntrack has occurred. */
#घोषणा OVS_CS_F_SRC_NAT           0x40 /* Packet's source address/port was
					 * mangled by NAT.
					 */
#घोषणा OVS_CS_F_DST_NAT           0x80 /* Packet's destination address/port
					 * was mangled by NAT.
					 */

#घोषणा OVS_CS_F_NAT_MASK (OVS_CS_F_SRC_NAT | OVS_CS_F_DST_NAT)

काष्ठा ovs_key_ct_tuple_ipv4 अणु
	__be32 ipv4_src;
	__be32 ipv4_dst;
	__be16 src_port;
	__be16 dst_port;
	__u8   ipv4_proto;
पूर्ण;

काष्ठा ovs_key_ct_tuple_ipv6 अणु
	__be32 ipv6_src[4];
	__be32 ipv6_dst[4];
	__be16 src_port;
	__be16 dst_port;
	__u8   ipv6_proto;
पूर्ण;

क्रमागत ovs_nsh_key_attr अणु
	OVS_NSH_KEY_ATTR_UNSPEC,
	OVS_NSH_KEY_ATTR_BASE,  /* काष्ठा ovs_nsh_key_base. */
	OVS_NSH_KEY_ATTR_MD1,   /* काष्ठा ovs_nsh_key_md1. */
	OVS_NSH_KEY_ATTR_MD2,   /* variable-length octets क्रम MD type 2. */
	__OVS_NSH_KEY_ATTR_MAX
पूर्ण;

#घोषणा OVS_NSH_KEY_ATTR_MAX (__OVS_NSH_KEY_ATTR_MAX - 1)

काष्ठा ovs_nsh_key_base अणु
	__u8 flags;
	__u8 ttl;
	__u8 mdtype;
	__u8 np;
	__be32 path_hdr;
पूर्ण;

#घोषणा NSH_MD1_CONTEXT_SIZE 4

काष्ठा ovs_nsh_key_md1 अणु
	__be32 context[NSH_MD1_CONTEXT_SIZE];
पूर्ण;

/**
 * क्रमागत ovs_flow_attr - attributes क्रम %OVS_FLOW_* commands.
 * @OVS_FLOW_ATTR_KEY: Nested %OVS_KEY_ATTR_* attributes specअगरying the flow
 * key.  Always present in notअगरications.  Required क्रम all requests (except
 * dumps).
 * @OVS_FLOW_ATTR_ACTIONS: Nested %OVS_ACTION_ATTR_* attributes specअगरying
 * the actions to take क्रम packets that match the key.  Always present in
 * notअगरications.  Required क्रम %OVS_FLOW_CMD_NEW requests, optional क्रम
 * %OVS_FLOW_CMD_SET requests.  An %OVS_FLOW_CMD_SET without
 * %OVS_FLOW_ATTR_ACTIONS will not modअगरy the actions.  To clear the actions,
 * an %OVS_FLOW_ATTR_ACTIONS without any nested attributes must be given.
 * @OVS_FLOW_ATTR_STATS: &काष्ठा ovs_flow_stats giving statistics क्रम this
 * flow.  Present in notअगरications अगर the stats would be nonzero.  Ignored in
 * requests.
 * @OVS_FLOW_ATTR_TCP_FLAGS: An 8-bit value giving the OR'd value of all of the
 * TCP flags seen on packets in this flow.  Only present in notअगरications क्रम
 * TCP flows, and only अगर it would be nonzero.  Ignored in requests.
 * @OVS_FLOW_ATTR_USED: A 64-bit पूर्णांकeger giving the समय, in milliseconds on
 * the प्रणाली monotonic घड़ी, at which a packet was last processed क्रम this
 * flow.  Only present in notअगरications अगर a packet has been processed क्रम this
 * flow.  Ignored in requests.
 * @OVS_FLOW_ATTR_CLEAR: If present in a %OVS_FLOW_CMD_SET request, clears the
 * last-used समय, accumulated TCP flags, and statistics क्रम this flow.
 * Otherwise ignored in requests.  Never present in notअगरications.
 * @OVS_FLOW_ATTR_MASK: Nested %OVS_KEY_ATTR_* attributes specअगरying the
 * mask bits क्रम wildcarded flow match. Mask bit value '1' specअगरies exact
 * match with corresponding flow key bit, जबतक mask bit value '0' specअगरies
 * a wildcarded match. Omitting attribute is treated as wildcarding all
 * corresponding fields. Optional क्रम all requests. If not present,
 * all flow key bits are exact match bits.
 * @OVS_FLOW_ATTR_UFID: A value between 1-16 octets specअगरying a unique
 * identअगरier क्रम the flow. Causes the flow to be indexed by this value rather
 * than the value of the %OVS_FLOW_ATTR_KEY attribute. Optional क्रम all
 * requests. Present in notअगरications अगर the flow was created with this
 * attribute.
 * @OVS_FLOW_ATTR_UFID_FLAGS: A 32-bit value of OR'd %OVS_UFID_F_*
 * flags that provide alternative semantics क्रम flow installation and
 * retrieval. Optional क्रम all requests.
 *
 * These attributes follow the &काष्ठा ovs_header within the Generic Netlink
 * payload क्रम %OVS_FLOW_* commands.
 */
क्रमागत ovs_flow_attr अणु
	OVS_FLOW_ATTR_UNSPEC,
	OVS_FLOW_ATTR_KEY,       /* Sequence of OVS_KEY_ATTR_* attributes. */
	OVS_FLOW_ATTR_ACTIONS,   /* Nested OVS_ACTION_ATTR_* attributes. */
	OVS_FLOW_ATTR_STATS,     /* काष्ठा ovs_flow_stats. */
	OVS_FLOW_ATTR_TCP_FLAGS, /* 8-bit OR'd TCP flags. */
	OVS_FLOW_ATTR_USED,      /* u64 msecs last used in monotonic समय. */
	OVS_FLOW_ATTR_CLEAR,     /* Flag to clear stats, tcp_flags, used. */
	OVS_FLOW_ATTR_MASK,      /* Sequence of OVS_KEY_ATTR_* attributes. */
	OVS_FLOW_ATTR_PROBE,     /* Flow operation is a feature probe, error
				  * logging should be suppressed. */
	OVS_FLOW_ATTR_UFID,      /* Variable length unique flow identअगरier. */
	OVS_FLOW_ATTR_UFID_FLAGS,/* u32 of OVS_UFID_F_*. */
	OVS_FLOW_ATTR_PAD,
	__OVS_FLOW_ATTR_MAX
पूर्ण;

#घोषणा OVS_FLOW_ATTR_MAX (__OVS_FLOW_ATTR_MAX - 1)

/**
 * Omit attributes क्रम notअगरications.
 *
 * If a datapath request contains an %OVS_UFID_F_OMIT_* flag, then the datapath
 * may omit the corresponding %OVS_FLOW_ATTR_* from the response.
 */
#घोषणा OVS_UFID_F_OMIT_KEY      (1 << 0)
#घोषणा OVS_UFID_F_OMIT_MASK     (1 << 1)
#घोषणा OVS_UFID_F_OMIT_ACTIONS  (1 << 2)

/**
 * क्रमागत ovs_sample_attr - Attributes क्रम %OVS_ACTION_ATTR_SAMPLE action.
 * @OVS_SAMPLE_ATTR_PROBABILITY: 32-bit fraction of packets to sample with
 * @OVS_ACTION_ATTR_SAMPLE.  A value of 0 samples no packets, a value of
 * %UINT32_MAX samples all packets and पूर्णांकermediate values sample पूर्णांकermediate
 * fractions of packets.
 * @OVS_SAMPLE_ATTR_ACTIONS: Set of actions to execute in sampling event.
 * Actions are passed as nested attributes.
 *
 * Executes the specअगरied actions with the given probability on a per-packet
 * basis.
 */
क्रमागत ovs_sample_attr अणु
	OVS_SAMPLE_ATTR_UNSPEC,
	OVS_SAMPLE_ATTR_PROBABILITY, /* u32 number */
	OVS_SAMPLE_ATTR_ACTIONS,     /* Nested OVS_ACTION_ATTR_* attributes. */
	__OVS_SAMPLE_ATTR_MAX,

#अगर_घोषित __KERNEL__
	OVS_SAMPLE_ATTR_ARG          /* काष्ठा sample_arg  */
#पूर्ण_अगर
पूर्ण;

#घोषणा OVS_SAMPLE_ATTR_MAX (__OVS_SAMPLE_ATTR_MAX - 1)

#अगर_घोषित __KERNEL__
काष्ठा sample_arg अणु
	bool exec;                   /* When true, actions in sample will not
				      * change flow keys. False otherwise.
				      */
	u32  probability;            /* Same value as
				      * 'OVS_SAMPLE_ATTR_PROBABILITY'.
				      */
पूर्ण;
#पूर्ण_अगर

/**
 * क्रमागत ovs_userspace_attr - Attributes क्रम %OVS_ACTION_ATTR_USERSPACE action.
 * @OVS_USERSPACE_ATTR_PID: u32 Netlink PID to which the %OVS_PACKET_CMD_ACTION
 * message should be sent.  Required.
 * @OVS_USERSPACE_ATTR_USERDATA: If present, its variable-length argument is
 * copied to the %OVS_PACKET_CMD_ACTION message as %OVS_PACKET_ATTR_USERDATA.
 * @OVS_USERSPACE_ATTR_EGRESS_TUN_PORT: If present, u32 output port to get
 * tunnel info.
 * @OVS_USERSPACE_ATTR_ACTIONS: If present, send actions with upcall.
 */
क्रमागत ovs_userspace_attr अणु
	OVS_USERSPACE_ATTR_UNSPEC,
	OVS_USERSPACE_ATTR_PID,	      /* u32 Netlink PID to receive upcalls. */
	OVS_USERSPACE_ATTR_USERDATA,  /* Optional user-specअगरied cookie. */
	OVS_USERSPACE_ATTR_EGRESS_TUN_PORT,  /* Optional, u32 output port
					      * to get tunnel info. */
	OVS_USERSPACE_ATTR_ACTIONS,   /* Optional flag to get actions. */
	__OVS_USERSPACE_ATTR_MAX
पूर्ण;

#घोषणा OVS_USERSPACE_ATTR_MAX (__OVS_USERSPACE_ATTR_MAX - 1)

काष्ठा ovs_action_trunc अणु
	__u32 max_len; /* Max packet size in bytes. */
पूर्ण;

/**
 * काष्ठा ovs_action_push_mpls - %OVS_ACTION_ATTR_PUSH_MPLS action argument.
 * @mpls_lse: MPLS label stack entry to push.
 * @mpls_ethertype: Ethertype to set in the encapsulating ethernet frame.
 *
 * The only values @mpls_ethertype should ever be given are %ETH_P_MPLS_UC and
 * %ETH_P_MPLS_MC, indicating MPLS unicast or multicast. Other are rejected.
 */
काष्ठा ovs_action_push_mpls अणु
	__be32 mpls_lse;
	__be16 mpls_ethertype; /* Either %ETH_P_MPLS_UC or %ETH_P_MPLS_MC */
पूर्ण;

/**
 * काष्ठा ovs_action_add_mpls - %OVS_ACTION_ATTR_ADD_MPLS action
 * argument.
 * @mpls_lse: MPLS label stack entry to push.
 * @mpls_ethertype: Ethertype to set in the encapsulating ethernet frame.
 * @tun_flags: MPLS tunnel attributes.
 *
 * The only values @mpls_ethertype should ever be given are %ETH_P_MPLS_UC and
 * %ETH_P_MPLS_MC, indicating MPLS unicast or multicast. Other are rejected.
 */
काष्ठा ovs_action_add_mpls अणु
	__be32 mpls_lse;
	__be16 mpls_ethertype; /* Either %ETH_P_MPLS_UC or %ETH_P_MPLS_MC */
	__u16 tun_flags;
पूर्ण;

#घोषणा OVS_MPLS_L3_TUNNEL_FLAG_MASK  (1 << 0) /* Flag to specअगरy the place of
						* insertion of MPLS header.
						* When false, the MPLS header
						* will be inserted at the start
						* of the packet.
						* When true, the MPLS header
						* will be inserted at the start
						* of the l3 header.
						*/

/**
 * काष्ठा ovs_action_push_vlan - %OVS_ACTION_ATTR_PUSH_VLAN action argument.
 * @vlan_tpid: Tag protocol identअगरier (TPID) to push.
 * @vlan_tci: Tag control identअगरier (TCI) to push.  The CFI bit must be set
 * (but it will not be set in the 802.1Q header that is pushed).
 *
 * The @vlan_tpid value is typically %ETH_P_8021Q or %ETH_P_8021AD.
 * The only acceptable TPID values are those that the kernel module also parses
 * as 802.1Q or 802.1AD headers, to prevent %OVS_ACTION_ATTR_PUSH_VLAN followed
 * by %OVS_ACTION_ATTR_POP_VLAN from having surprising results.
 */
काष्ठा ovs_action_push_vlan अणु
	__be16 vlan_tpid;	/* 802.1Q or 802.1ad TPID. */
	__be16 vlan_tci;	/* 802.1Q TCI (VLAN ID and priority). */
पूर्ण;

/* Data path hash algorithm क्रम computing Datapath hash.
 *
 * The algorithm type only specअगरies the fields in a flow
 * will be used as part of the hash. Each datapath is मुक्त
 * to use its own hash algorithm. The hash value will be
 * opaque to the user space daemon.
 */
क्रमागत ovs_hash_alg अणु
	OVS_HASH_ALG_L4,
पूर्ण;

/*
 * काष्ठा ovs_action_hash - %OVS_ACTION_ATTR_HASH action argument.
 * @hash_alg: Algorithm used to compute hash prior to recirculation.
 * @hash_basis: basis used क्रम computing hash.
 */
काष्ठा ovs_action_hash अणु
	__u32  hash_alg;     /* One of ovs_hash_alg. */
	__u32  hash_basis;
पूर्ण;

/**
 * क्रमागत ovs_ct_attr - Attributes क्रम %OVS_ACTION_ATTR_CT action.
 * @OVS_CT_ATTR_COMMIT: If present, commits the connection to the conntrack
 * table. This allows future packets क्रम the same connection to be identअगरied
 * as 'established' or 'related'. The flow key क्रम the current packet will
 * retain the pre-commit connection state.
 * @OVS_CT_ATTR_ZONE: u16 connection tracking zone.
 * @OVS_CT_ATTR_MARK: u32 value followed by u32 mask. For each bit set in the
 * mask, the corresponding bit in the value is copied to the connection
 * tracking mark field in the connection.
 * @OVS_CT_ATTR_LABELS: %OVS_CT_LABELS_LEN value followed by %OVS_CT_LABELS_LEN
 * mask. For each bit set in the mask, the corresponding bit in the value is
 * copied to the connection tracking label field in the connection.
 * @OVS_CT_ATTR_HELPER: variable length string defining conntrack ALG.
 * @OVS_CT_ATTR_NAT: Nested OVS_NAT_ATTR_* क्रम perक्रमming L3 network address
 * translation (NAT) on the packet.
 * @OVS_CT_ATTR_FORCE_COMMIT: Like %OVS_CT_ATTR_COMMIT, but instead of करोing
 * nothing अगर the connection is alपढ़ोy committed will check that the current
 * packet is in conntrack entry's original direction.  If directionality करोes
 * not match, will delete the existing conntrack entry and commit a new one.
 * @OVS_CT_ATTR_EVENTMASK: Mask of bits indicating which conntrack event types
 * (क्रमागत ip_conntrack_events IPCT_*) should be reported.  For any bit set to
 * zero, the corresponding event type is not generated.  Default behavior
 * depends on प्रणाली configuration, but typically all event types are
 * generated, hence listening on NFNLGRP_CONNTRACK_UPDATE events may get a lot
 * of events.  Explicitly passing this attribute allows limiting the updates
 * received to the events of पूर्णांकerest.  The bit 1 << IPCT_NEW, 1 <<
 * IPCT_RELATED, and 1 << IPCT_DESTROY must be set to ones क्रम those events to
 * be received on NFNLGRP_CONNTRACK_NEW and NFNLGRP_CONNTRACK_DESTROY groups,
 * respectively.  Reमुख्यing bits control the changes क्रम which an event is
 * delivered on the NFNLGRP_CONNTRACK_UPDATE group.
 * @OVS_CT_ATTR_TIMEOUT: Variable length string defining conntrack समयout.
 */
क्रमागत ovs_ct_attr अणु
	OVS_CT_ATTR_UNSPEC,
	OVS_CT_ATTR_COMMIT,     /* No argument, commits connection. */
	OVS_CT_ATTR_ZONE,       /* u16 zone id. */
	OVS_CT_ATTR_MARK,       /* mark to associate with this connection. */
	OVS_CT_ATTR_LABELS,     /* labels to associate with this connection. */
	OVS_CT_ATTR_HELPER,     /* netlink helper to assist detection of
				   related connections. */
	OVS_CT_ATTR_NAT,        /* Nested OVS_NAT_ATTR_* */
	OVS_CT_ATTR_FORCE_COMMIT,  /* No argument */
	OVS_CT_ATTR_EVENTMASK,  /* u32 mask of IPCT_* events. */
	OVS_CT_ATTR_TIMEOUT,	/* Associate समयout with this connection क्रम
				 * fine-grain समयout tuning. */
	__OVS_CT_ATTR_MAX
पूर्ण;

#घोषणा OVS_CT_ATTR_MAX (__OVS_CT_ATTR_MAX - 1)

/**
 * क्रमागत ovs_nat_attr - Attributes क्रम %OVS_CT_ATTR_NAT.
 *
 * @OVS_NAT_ATTR_SRC: Flag क्रम Source NAT (mangle source address/port).
 * @OVS_NAT_ATTR_DST: Flag क्रम Destination NAT (mangle destination
 * address/port).  Only one of (@OVS_NAT_ATTR_SRC, @OVS_NAT_ATTR_DST) may be
 * specअगरied.  Effective only क्रम packets क्रम ct_state NEW connections.
 * Packets of committed connections are mangled by the NAT action according to
 * the committed NAT type regardless of the flags specअगरied.  As a corollary, a
 * NAT action without a NAT type flag will only mangle packets of committed
 * connections.  The following NAT attributes only apply क्रम NEW
 * (non-committed) connections, and they may be included only when the CT
 * action has the @OVS_CT_ATTR_COMMIT flag and either @OVS_NAT_ATTR_SRC or
 * @OVS_NAT_ATTR_DST is also included.
 * @OVS_NAT_ATTR_IP_MIN: काष्ठा in_addr or काष्ठा in6_addr
 * @OVS_NAT_ATTR_IP_MAX: काष्ठा in_addr or काष्ठा in6_addr
 * @OVS_NAT_ATTR_PROTO_MIN: u16 L4 protocol specअगरic lower boundary (port)
 * @OVS_NAT_ATTR_PROTO_MAX: u16 L4 protocol specअगरic upper boundary (port)
 * @OVS_NAT_ATTR_PERSISTENT: Flag क्रम persistent IP mapping across reboots
 * @OVS_NAT_ATTR_PROTO_HASH: Flag क्रम pseuकरो अक्रमom L4 port mapping (MD5)
 * @OVS_NAT_ATTR_PROTO_RANDOM: Flag क्रम fully अक्रमomized L4 port mapping
 */
क्रमागत ovs_nat_attr अणु
	OVS_NAT_ATTR_UNSPEC,
	OVS_NAT_ATTR_SRC,
	OVS_NAT_ATTR_DST,
	OVS_NAT_ATTR_IP_MIN,
	OVS_NAT_ATTR_IP_MAX,
	OVS_NAT_ATTR_PROTO_MIN,
	OVS_NAT_ATTR_PROTO_MAX,
	OVS_NAT_ATTR_PERSISTENT,
	OVS_NAT_ATTR_PROTO_HASH,
	OVS_NAT_ATTR_PROTO_RANDOM,
	__OVS_NAT_ATTR_MAX,
पूर्ण;

#घोषणा OVS_NAT_ATTR_MAX (__OVS_NAT_ATTR_MAX - 1)

/*
 * काष्ठा ovs_action_push_eth - %OVS_ACTION_ATTR_PUSH_ETH action argument.
 * @addresses: Source and destination MAC addresses.
 * @eth_type: Ethernet type
 */
काष्ठा ovs_action_push_eth अणु
	काष्ठा ovs_key_ethernet addresses;
पूर्ण;

/*
 * क्रमागत ovs_check_pkt_len_attr - Attributes क्रम %OVS_ACTION_ATTR_CHECK_PKT_LEN.
 *
 * @OVS_CHECK_PKT_LEN_ATTR_PKT_LEN: u16 Packet length to check क्रम.
 * @OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER: Nested OVS_ACTION_ATTR_*
 * actions to apply अगर the packer length is greater than the specअगरied
 * length in the attr - OVS_CHECK_PKT_LEN_ATTR_PKT_LEN.
 * @OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL - Nested OVS_ACTION_ATTR_*
 * actions to apply अगर the packer length is lesser or equal to the specअगरied
 * length in the attr - OVS_CHECK_PKT_LEN_ATTR_PKT_LEN.
 */
क्रमागत ovs_check_pkt_len_attr अणु
	OVS_CHECK_PKT_LEN_ATTR_UNSPEC,
	OVS_CHECK_PKT_LEN_ATTR_PKT_LEN,
	OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER,
	OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL,
	__OVS_CHECK_PKT_LEN_ATTR_MAX,

#अगर_घोषित __KERNEL__
	OVS_CHECK_PKT_LEN_ATTR_ARG          /* काष्ठा check_pkt_len_arg  */
#पूर्ण_अगर
पूर्ण;

#घोषणा OVS_CHECK_PKT_LEN_ATTR_MAX (__OVS_CHECK_PKT_LEN_ATTR_MAX - 1)

#अगर_घोषित __KERNEL__
काष्ठा check_pkt_len_arg अणु
	u16 pkt_len;	/* Same value as OVS_CHECK_PKT_LEN_ATTR_PKT_LEN'. */
	bool exec_क्रम_greater;	/* When true, actions in IF_GREATER will
				 * not change flow keys. False otherwise.
				 */
	bool exec_क्रम_lesser_equal; /* When true, actions in IF_LESS_EQUAL
				     * will not change flow keys. False
				     * otherwise.
				     */
पूर्ण;
#पूर्ण_अगर

/**
 * क्रमागत ovs_action_attr - Action types.
 *
 * @OVS_ACTION_ATTR_OUTPUT: Output packet to port.
 * @OVS_ACTION_ATTR_TRUNC: Output packet to port with truncated packet size.
 * @OVS_ACTION_ATTR_USERSPACE: Send packet to userspace according to nested
 * %OVS_USERSPACE_ATTR_* attributes.
 * @OVS_ACTION_ATTR_SET: Replaces the contents of an existing header.  The
 * single nested %OVS_KEY_ATTR_* attribute specअगरies a header to modअगरy and its
 * value.
 * @OVS_ACTION_ATTR_SET_MASKED: Replaces the contents of an existing header.  A
 * nested %OVS_KEY_ATTR_* attribute specअगरies a header to modअगरy, its value,
 * and a mask.  For every bit set in the mask, the corresponding bit value
 * is copied from the value to the packet header field, rest of the bits are
 * left unchanged.  The non-masked value bits must be passed in as zeroes.
 * Masking is not supported क्रम the %OVS_KEY_ATTR_TUNNEL attribute.
 * @OVS_ACTION_ATTR_PUSH_VLAN: Push a new outermost 802.1Q or 802.1ad header
 * onto the packet.
 * @OVS_ACTION_ATTR_POP_VLAN: Pop the outermost 802.1Q or 802.1ad header
 * from the packet.
 * @OVS_ACTION_ATTR_SAMPLE: Probabilitically executes actions, as specअगरied in
 * the nested %OVS_SAMPLE_ATTR_* attributes.
 * @OVS_ACTION_ATTR_PUSH_MPLS: Push a new MPLS label stack entry onto the
 * top of the packets MPLS label stack.  Set the ethertype of the
 * encapsulating frame to either %ETH_P_MPLS_UC or %ETH_P_MPLS_MC to
 * indicate the new packet contents.
 * @OVS_ACTION_ATTR_POP_MPLS: Pop an MPLS label stack entry off of the
 * packet's MPLS label stack.  Set the encapsulating frame's ethertype to
 * indicate the new packet contents. This could potentially still be
 * %ETH_P_MPLS अगर the resulting MPLS label stack is not empty.  If there
 * is no MPLS label stack, as determined by ethertype, no action is taken.
 * @OVS_ACTION_ATTR_CT: Track the connection. Populate the conntrack-related
 * entries in the flow key.
 * @OVS_ACTION_ATTR_PUSH_ETH: Push a new outermost Ethernet header onto the
 * packet.
 * @OVS_ACTION_ATTR_POP_ETH: Pop the outermost Ethernet header off the
 * packet.
 * @OVS_ACTION_ATTR_CT_CLEAR: Clear conntrack state from the packet.
 * @OVS_ACTION_ATTR_PUSH_NSH: push NSH header to the packet.
 * @OVS_ACTION_ATTR_POP_NSH: pop the outermost NSH header off the packet.
 * @OVS_ACTION_ATTR_METER: Run packet through a meter, which may drop the
 * packet, or modअगरy the packet (e.g., change the DSCP field).
 * @OVS_ACTION_ATTR_CLONE: make a copy of the packet and execute a list of
 * actions without affecting the original packet and key.
 * @OVS_ACTION_ATTR_CHECK_PKT_LEN: Check the packet length and execute a set
 * of actions अगर greater than the specअगरied packet length, अन्यथा execute
 * another set of actions.
 * @OVS_ACTION_ATTR_ADD_MPLS: Push a new MPLS label stack entry at the
 * start of the packet or at the start of the l3 header depending on the value
 * of l3 tunnel flag in the tun_flags field of OVS_ACTION_ATTR_ADD_MPLS
 * argument.
 *
 * Only a single header can be set with a single %OVS_ACTION_ATTR_SET.  Not all
 * fields within a header are modअगरiable, e.g. the IPv4 protocol and fragment
 * type may not be changed.
 *
 * @OVS_ACTION_ATTR_SET_TO_MASKED: Kernel पूर्णांकernal masked set action translated
 * from the @OVS_ACTION_ATTR_SET.
 */

क्रमागत ovs_action_attr अणु
	OVS_ACTION_ATTR_UNSPEC,
	OVS_ACTION_ATTR_OUTPUT,	      /* u32 port number. */
	OVS_ACTION_ATTR_USERSPACE,    /* Nested OVS_USERSPACE_ATTR_*. */
	OVS_ACTION_ATTR_SET,          /* One nested OVS_KEY_ATTR_*. */
	OVS_ACTION_ATTR_PUSH_VLAN,    /* काष्ठा ovs_action_push_vlan. */
	OVS_ACTION_ATTR_POP_VLAN,     /* No argument. */
	OVS_ACTION_ATTR_SAMPLE,       /* Nested OVS_SAMPLE_ATTR_*. */
	OVS_ACTION_ATTR_RECIRC,       /* u32 recirc_id. */
	OVS_ACTION_ATTR_HASH,	      /* काष्ठा ovs_action_hash. */
	OVS_ACTION_ATTR_PUSH_MPLS,    /* काष्ठा ovs_action_push_mpls. */
	OVS_ACTION_ATTR_POP_MPLS,     /* __be16 ethertype. */
	OVS_ACTION_ATTR_SET_MASKED,   /* One nested OVS_KEY_ATTR_* including
				       * data immediately followed by a mask.
				       * The data must be zero क्रम the unmasked
				       * bits. */
	OVS_ACTION_ATTR_CT,           /* Nested OVS_CT_ATTR_* . */
	OVS_ACTION_ATTR_TRUNC,        /* u32 काष्ठा ovs_action_trunc. */
	OVS_ACTION_ATTR_PUSH_ETH,     /* काष्ठा ovs_action_push_eth. */
	OVS_ACTION_ATTR_POP_ETH,      /* No argument. */
	OVS_ACTION_ATTR_CT_CLEAR,     /* No argument. */
	OVS_ACTION_ATTR_PUSH_NSH,     /* Nested OVS_NSH_KEY_ATTR_*. */
	OVS_ACTION_ATTR_POP_NSH,      /* No argument. */
	OVS_ACTION_ATTR_METER,        /* u32 meter ID. */
	OVS_ACTION_ATTR_CLONE,        /* Nested OVS_CLONE_ATTR_*.  */
	OVS_ACTION_ATTR_CHECK_PKT_LEN, /* Nested OVS_CHECK_PKT_LEN_ATTR_*. */
	OVS_ACTION_ATTR_ADD_MPLS,     /* काष्ठा ovs_action_add_mpls. */
	OVS_ACTION_ATTR_DEC_TTL,      /* Nested OVS_DEC_TTL_ATTR_*. */

	__OVS_ACTION_ATTR_MAX,	      /* Nothing past this will be accepted
				       * from userspace. */

#अगर_घोषित __KERNEL__
	OVS_ACTION_ATTR_SET_TO_MASKED, /* Kernel module पूर्णांकernal masked
					* set action converted from
					* OVS_ACTION_ATTR_SET. */
#पूर्ण_अगर
पूर्ण;

#घोषणा OVS_ACTION_ATTR_MAX (__OVS_ACTION_ATTR_MAX - 1)

/* Meters. */
#घोषणा OVS_METER_FAMILY  "ovs_meter"
#घोषणा OVS_METER_MCGROUP "ovs_meter"
#घोषणा OVS_METER_VERSION 0x1

क्रमागत ovs_meter_cmd अणु
	OVS_METER_CMD_UNSPEC,
	OVS_METER_CMD_FEATURES,	/* Get features supported by the datapath. */
	OVS_METER_CMD_SET,	/* Add or modअगरy a meter. */
	OVS_METER_CMD_DEL,	/* Delete a meter. */
	OVS_METER_CMD_GET	/* Get meter stats. */
पूर्ण;

क्रमागत ovs_meter_attr अणु
	OVS_METER_ATTR_UNSPEC,
	OVS_METER_ATTR_ID,	/* u32 meter ID within datapath. */
	OVS_METER_ATTR_KBPS,	/* No argument. If set, units in kilobits
				 * per second. Otherwise, units in
				 * packets per second.
				 */
	OVS_METER_ATTR_STATS,	/* काष्ठा ovs_flow_stats क्रम the meter. */
	OVS_METER_ATTR_BANDS,	/* Nested attributes क्रम meter bands. */
	OVS_METER_ATTR_USED,	/* u64 msecs last used in monotonic समय. */
	OVS_METER_ATTR_CLEAR,	/* Flag to clear stats, used. */
	OVS_METER_ATTR_MAX_METERS, /* u32 number of meters supported. */
	OVS_METER_ATTR_MAX_BANDS,  /* u32 max number of bands per meter. */
	OVS_METER_ATTR_PAD,
	__OVS_METER_ATTR_MAX
पूर्ण;

#घोषणा OVS_METER_ATTR_MAX (__OVS_METER_ATTR_MAX - 1)

क्रमागत ovs_band_attr अणु
	OVS_BAND_ATTR_UNSPEC,
	OVS_BAND_ATTR_TYPE,	/* u32 OVS_METER_BAND_TYPE_* स्थिरant. */
	OVS_BAND_ATTR_RATE,	/* u32 band rate in meter units (see above). */
	OVS_BAND_ATTR_BURST,	/* u32 burst size in meter units. */
	OVS_BAND_ATTR_STATS,	/* काष्ठा ovs_flow_stats क्रम the band. */
	__OVS_BAND_ATTR_MAX
पूर्ण;

#घोषणा OVS_BAND_ATTR_MAX (__OVS_BAND_ATTR_MAX - 1)

क्रमागत ovs_meter_band_type अणु
	OVS_METER_BAND_TYPE_UNSPEC,
	OVS_METER_BAND_TYPE_DROP,   /* Drop exceeding packets. */
	__OVS_METER_BAND_TYPE_MAX
पूर्ण;

#घोषणा OVS_METER_BAND_TYPE_MAX (__OVS_METER_BAND_TYPE_MAX - 1)

/* Conntrack limit */
#घोषणा OVS_CT_LIMIT_FAMILY  "ovs_ct_limit"
#घोषणा OVS_CT_LIMIT_MCGROUP "ovs_ct_limit"
#घोषणा OVS_CT_LIMIT_VERSION 0x1

क्रमागत ovs_ct_limit_cmd अणु
	OVS_CT_LIMIT_CMD_UNSPEC,
	OVS_CT_LIMIT_CMD_SET,		/* Add or modअगरy ct limit. */
	OVS_CT_LIMIT_CMD_DEL,		/* Delete ct limit. */
	OVS_CT_LIMIT_CMD_GET		/* Get ct limit. */
पूर्ण;

क्रमागत ovs_ct_limit_attr अणु
	OVS_CT_LIMIT_ATTR_UNSPEC,
	OVS_CT_LIMIT_ATTR_ZONE_LIMIT,	/* Nested काष्ठा ovs_zone_limit. */
	__OVS_CT_LIMIT_ATTR_MAX
पूर्ण;

#घोषणा OVS_CT_LIMIT_ATTR_MAX (__OVS_CT_LIMIT_ATTR_MAX - 1)

#घोषणा OVS_ZONE_LIMIT_DEFAULT_ZONE -1

काष्ठा ovs_zone_limit अणु
	पूर्णांक zone_id;
	__u32 limit;
	__u32 count;
पूर्ण;

क्रमागत ovs_dec_ttl_attr अणु
	OVS_DEC_TTL_ATTR_UNSPEC,
	OVS_DEC_TTL_ATTR_ACTION,	/* Nested काष्ठा nlattr */
	__OVS_DEC_TTL_ATTR_MAX
पूर्ण;

#घोषणा OVS_DEC_TTL_ATTR_MAX (__OVS_DEC_TTL_ATTR_MAX - 1)

#पूर्ण_अगर /* _LINUX_OPENVSWITCH_H */
