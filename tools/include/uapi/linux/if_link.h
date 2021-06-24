<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_IF_LINK_H
#घोषणा _UAPI_LINUX_IF_LINK_H

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>

/* This काष्ठा should be in sync with काष्ठा rtnl_link_stats64 */
काष्ठा rtnl_link_stats अणु
	__u32	rx_packets;		/* total packets received	*/
	__u32	tx_packets;		/* total packets transmitted	*/
	__u32	rx_bytes;		/* total bytes received 	*/
	__u32	tx_bytes;		/* total bytes transmitted	*/
	__u32	rx_errors;		/* bad packets received		*/
	__u32	tx_errors;		/* packet transmit problems	*/
	__u32	rx_dropped;		/* no space in linux buffers	*/
	__u32	tx_dropped;		/* no space available in linux	*/
	__u32	multicast;		/* multicast packets received	*/
	__u32	collisions;

	/* detailed rx_errors: */
	__u32	rx_length_errors;
	__u32	rx_over_errors;		/* receiver ring buff overflow	*/
	__u32	rx_crc_errors;		/* recved pkt with crc error	*/
	__u32	rx_frame_errors;	/* recv'd frame alignment error */
	__u32	rx_fअगरo_errors;		/* recv'r fअगरo overrun		*/
	__u32	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	__u32	tx_पातed_errors;
	__u32	tx_carrier_errors;
	__u32	tx_fअगरo_errors;
	__u32	tx_heartbeat_errors;
	__u32	tx_winकरोw_errors;

	/* क्रम cslip etc */
	__u32	rx_compressed;
	__u32	tx_compressed;

	__u32	rx_nohandler;		/* dropped, no handler found	*/
पूर्ण;

/* The मुख्य device statistics काष्ठाure */
काष्ठा rtnl_link_stats64 अणु
	__u64	rx_packets;		/* total packets received	*/
	__u64	tx_packets;		/* total packets transmitted	*/
	__u64	rx_bytes;		/* total bytes received 	*/
	__u64	tx_bytes;		/* total bytes transmitted	*/
	__u64	rx_errors;		/* bad packets received		*/
	__u64	tx_errors;		/* packet transmit problems	*/
	__u64	rx_dropped;		/* no space in linux buffers	*/
	__u64	tx_dropped;		/* no space available in linux	*/
	__u64	multicast;		/* multicast packets received	*/
	__u64	collisions;

	/* detailed rx_errors: */
	__u64	rx_length_errors;
	__u64	rx_over_errors;		/* receiver ring buff overflow	*/
	__u64	rx_crc_errors;		/* recved pkt with crc error	*/
	__u64	rx_frame_errors;	/* recv'd frame alignment error */
	__u64	rx_fअगरo_errors;		/* recv'r fअगरo overrun		*/
	__u64	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	__u64	tx_पातed_errors;
	__u64	tx_carrier_errors;
	__u64	tx_fअगरo_errors;
	__u64	tx_heartbeat_errors;
	__u64	tx_winकरोw_errors;

	/* क्रम cslip etc */
	__u64	rx_compressed;
	__u64	tx_compressed;

	__u64	rx_nohandler;		/* dropped, no handler found	*/
पूर्ण;

/* The काष्ठा should be in sync with काष्ठा अगरmap */
काष्ठा rtnl_link_अगरmap अणु
	__u64	mem_start;
	__u64	mem_end;
	__u64	base_addr;
	__u16	irq;
	__u8	dma;
	__u8	port;
पूर्ण;

/*
 * IFLA_AF_SPEC
 *   Contains nested attributes क्रम address family specअगरic attributes.
 *   Each address family may create a attribute with the address family
 *   number as type and create its own attribute काष्ठाure in it.
 *
 *   Example:
 *   [IFLA_AF_SPEC] = अणु
 *       [AF_INET] = अणु
 *           [IFLA_INET_CONF] = ...,
 *       पूर्ण,
 *       [AF_INET6] = अणु
 *           [IFLA_INET6_FLAGS] = ...,
 *           [IFLA_INET6_CONF] = ...,
 *       पूर्ण
 *   पूर्ण
 */

क्रमागत अणु
	IFLA_UNSPEC,
	IFLA_ADDRESS,
	IFLA_BROADCAST,
	IFLA_IFNAME,
	IFLA_MTU,
	IFLA_LINK,
	IFLA_QDISC,
	IFLA_STATS,
	IFLA_COST,
#घोषणा IFLA_COST IFLA_COST
	IFLA_PRIORITY,
#घोषणा IFLA_PRIORITY IFLA_PRIORITY
	IFLA_MASTER,
#घोषणा IFLA_MASTER IFLA_MASTER
	IFLA_WIRELESS,		/* Wireless Extension event - see wireless.h */
#घोषणा IFLA_WIRELESS IFLA_WIRELESS
	IFLA_PROTINFO,		/* Protocol specअगरic inक्रमmation क्रम a link */
#घोषणा IFLA_PROTINFO IFLA_PROTINFO
	IFLA_TXQLEN,
#घोषणा IFLA_TXQLEN IFLA_TXQLEN
	IFLA_MAP,
#घोषणा IFLA_MAP IFLA_MAP
	IFLA_WEIGHT,
#घोषणा IFLA_WEIGHT IFLA_WEIGHT
	IFLA_OPERSTATE,
	IFLA_LINKMODE,
	IFLA_LINKINFO,
#घोषणा IFLA_LINKINFO IFLA_LINKINFO
	IFLA_NET_NS_PID,
	IFLA_IFALIAS,
	IFLA_NUM_VF,		/* Number of VFs अगर device is SR-IOV PF */
	IFLA_VFINFO_LIST,
	IFLA_STATS64,
	IFLA_VF_PORTS,
	IFLA_PORT_SELF,
	IFLA_AF_SPEC,
	IFLA_GROUP,		/* Group the device beदीर्घs to */
	IFLA_NET_NS_FD,
	IFLA_EXT_MASK,		/* Extended info mask, VFs, etc */
	IFLA_PROMISCUITY,	/* Promiscuity count: > 0 means acts PROMISC */
#घोषणा IFLA_PROMISCUITY IFLA_PROMISCUITY
	IFLA_NUM_TX_QUEUES,
	IFLA_NUM_RX_QUEUES,
	IFLA_CARRIER,
	IFLA_PHYS_PORT_ID,
	IFLA_CARRIER_CHANGES,
	IFLA_PHYS_SWITCH_ID,
	IFLA_LINK_NETNSID,
	IFLA_PHYS_PORT_NAME,
	IFLA_PROTO_DOWN,
	IFLA_GSO_MAX_SEGS,
	IFLA_GSO_MAX_SIZE,
	IFLA_PAD,
	IFLA_XDP,
	IFLA_EVENT,
	IFLA_NEW_NETNSID,
	IFLA_IF_NETNSID,
	IFLA_TARGET_NETNSID = IFLA_IF_NETNSID, /* new alias */
	IFLA_CARRIER_UP_COUNT,
	IFLA_CARRIER_DOWN_COUNT,
	IFLA_NEW_IFINDEX,
	IFLA_MIN_MTU,
	IFLA_MAX_MTU,
	IFLA_PROP_LIST,
	IFLA_ALT_IFNAME, /* Alternative अगरname */
	IFLA_PERM_ADDRESS,
	__IFLA_MAX
पूर्ण;


#घोषणा IFLA_MAX (__IFLA_MAX - 1)

/* backwards compatibility क्रम userspace */
#अगर_अघोषित __KERNEL__
#घोषणा IFLA_RTA(r)  ((काष्ठा rtattr*)(((अक्षर*)(r)) + NLMSG_ALIGN(माप(काष्ठा अगरinfomsg))))
#घोषणा IFLA_PAYLOAD(n) NLMSG_PAYLOAD(n,माप(काष्ठा अगरinfomsg))
#पूर्ण_अगर

क्रमागत अणु
	IFLA_INET_UNSPEC,
	IFLA_INET_CONF,
	__IFLA_INET_MAX,
पूर्ण;

#घोषणा IFLA_INET_MAX (__IFLA_INET_MAX - 1)

/* अगरi_flags.

   IFF_* flags.

   The only change is:
   IFF_LOOPBACK, IFF_BROADCAST and IFF_POINTOPOINT are
   more not changeable by user. They describe link media
   अक्षरacteristics and set by device driver.

   Comments:
   - Combination IFF_BROADCAST|IFF_POINTOPOINT is invalid
   - If neither of these three flags are set;
     the पूर्णांकerface is NBMA.

   - IFF_MULTICAST करोes not mean anything special:
   multicasts can be used on all not-NBMA links.
   IFF_MULTICAST means that this media uses special encapsulation
   क्रम multicast frames. Apparently, all IFF_POINTOPOINT and
   IFF_BROADCAST devices are able to use multicasts too.
 */

/* IFLA_LINK.
   For usual devices it is equal अगरi_index.
   If it is a "virtual interface" (f.e. tunnel), अगरi_link
   can poपूर्णांक to real physical पूर्णांकerface (f.e. क्रम bandwidth calculations),
   or maybe 0, what means, that real media is unknown (usual
   क्रम IPIP tunnels, when route to endpoपूर्णांक is allowed to change)
 */

/* Subtype attributes क्रम IFLA_PROTINFO */
क्रमागत अणु
	IFLA_INET6_UNSPEC,
	IFLA_INET6_FLAGS,	/* link flags			*/
	IFLA_INET6_CONF,	/* sysctl parameters		*/
	IFLA_INET6_STATS,	/* statistics			*/
	IFLA_INET6_MCAST,	/* MC things. What of them?	*/
	IFLA_INET6_CACHEINFO,	/* समय values and max reयंत्र size */
	IFLA_INET6_ICMP6STATS,	/* statistics (icmpv6)		*/
	IFLA_INET6_TOKEN,	/* device token			*/
	IFLA_INET6_ADDR_GEN_MODE, /* implicit address generator mode */
	__IFLA_INET6_MAX
पूर्ण;

#घोषणा IFLA_INET6_MAX	(__IFLA_INET6_MAX - 1)

क्रमागत in6_addr_gen_mode अणु
	IN6_ADDR_GEN_MODE_EUI64,
	IN6_ADDR_GEN_MODE_NONE,
	IN6_ADDR_GEN_MODE_STABLE_PRIVACY,
	IN6_ADDR_GEN_MODE_RANDOM,
पूर्ण;

/* Bridge section */

क्रमागत अणु
	IFLA_BR_UNSPEC,
	IFLA_BR_FORWARD_DELAY,
	IFLA_BR_HELLO_TIME,
	IFLA_BR_MAX_AGE,
	IFLA_BR_AGEING_TIME,
	IFLA_BR_STP_STATE,
	IFLA_BR_PRIORITY,
	IFLA_BR_VLAN_FILTERING,
	IFLA_BR_VLAN_PROTOCOL,
	IFLA_BR_GROUP_FWD_MASK,
	IFLA_BR_ROOT_ID,
	IFLA_BR_BRIDGE_ID,
	IFLA_BR_ROOT_PORT,
	IFLA_BR_ROOT_PATH_COST,
	IFLA_BR_TOPOLOGY_CHANGE,
	IFLA_BR_TOPOLOGY_CHANGE_DETECTED,
	IFLA_BR_HELLO_TIMER,
	IFLA_BR_TCN_TIMER,
	IFLA_BR_TOPOLOGY_CHANGE_TIMER,
	IFLA_BR_GC_TIMER,
	IFLA_BR_GROUP_ADDR,
	IFLA_BR_FDB_FLUSH,
	IFLA_BR_MCAST_ROUTER,
	IFLA_BR_MCAST_SNOOPING,
	IFLA_BR_MCAST_QUERY_USE_IFADDR,
	IFLA_BR_MCAST_QUERIER,
	IFLA_BR_MCAST_HASH_ELASTICITY,
	IFLA_BR_MCAST_HASH_MAX,
	IFLA_BR_MCAST_LAST_MEMBER_CNT,
	IFLA_BR_MCAST_STARTUP_QUERY_CNT,
	IFLA_BR_MCAST_LAST_MEMBER_INTVL,
	IFLA_BR_MCAST_MEMBERSHIP_INTVL,
	IFLA_BR_MCAST_QUERIER_INTVL,
	IFLA_BR_MCAST_QUERY_INTVL,
	IFLA_BR_MCAST_QUERY_RESPONSE_INTVL,
	IFLA_BR_MCAST_STARTUP_QUERY_INTVL,
	IFLA_BR_NF_CALL_IPTABLES,
	IFLA_BR_NF_CALL_IP6TABLES,
	IFLA_BR_NF_CALL_ARPTABLES,
	IFLA_BR_VLAN_DEFAULT_PVID,
	IFLA_BR_PAD,
	IFLA_BR_VLAN_STATS_ENABLED,
	IFLA_BR_MCAST_STATS_ENABLED,
	IFLA_BR_MCAST_IGMP_VERSION,
	IFLA_BR_MCAST_MLD_VERSION,
	IFLA_BR_VLAN_STATS_PER_PORT,
	IFLA_BR_MULTI_BOOLOPT,
	__IFLA_BR_MAX,
पूर्ण;

#घोषणा IFLA_BR_MAX	(__IFLA_BR_MAX - 1)

काष्ठा अगरla_bridge_id अणु
	__u8	prio[2];
	__u8	addr[6]; /* ETH_ALEN */
पूर्ण;

क्रमागत अणु
	BRIDGE_MODE_UNSPEC,
	BRIDGE_MODE_HAIRPIN,
पूर्ण;

क्रमागत अणु
	IFLA_BRPORT_UNSPEC,
	IFLA_BRPORT_STATE,	/* Spanning tree state     */
	IFLA_BRPORT_PRIORITY,	/* "             priority  */
	IFLA_BRPORT_COST,	/* "             cost      */
	IFLA_BRPORT_MODE,	/* mode (hairpin)          */
	IFLA_BRPORT_GUARD,	/* bpdu guard              */
	IFLA_BRPORT_PROTECT,	/* root port protection    */
	IFLA_BRPORT_FAST_LEAVE,	/* multicast fast leave    */
	IFLA_BRPORT_LEARNING,	/* mac learning */
	IFLA_BRPORT_UNICAST_FLOOD, /* flood unicast traffic */
	IFLA_BRPORT_PROXYARP,	/* proxy ARP */
	IFLA_BRPORT_LEARNING_SYNC, /* mac learning sync from device */
	IFLA_BRPORT_PROXYARP_WIFI, /* proxy ARP क्रम Wi-Fi */
	IFLA_BRPORT_ROOT_ID,	/* designated root */
	IFLA_BRPORT_BRIDGE_ID,	/* designated bridge */
	IFLA_BRPORT_DESIGNATED_PORT,
	IFLA_BRPORT_DESIGNATED_COST,
	IFLA_BRPORT_ID,
	IFLA_BRPORT_NO,
	IFLA_BRPORT_TOPOLOGY_CHANGE_ACK,
	IFLA_BRPORT_CONFIG_PENDING,
	IFLA_BRPORT_MESSAGE_AGE_TIMER,
	IFLA_BRPORT_FORWARD_DELAY_TIMER,
	IFLA_BRPORT_HOLD_TIMER,
	IFLA_BRPORT_FLUSH,
	IFLA_BRPORT_MULTICAST_ROUTER,
	IFLA_BRPORT_PAD,
	IFLA_BRPORT_MCAST_FLOOD,
	IFLA_BRPORT_MCAST_TO_UCAST,
	IFLA_BRPORT_VLAN_TUNNEL,
	IFLA_BRPORT_BCAST_FLOOD,
	IFLA_BRPORT_GROUP_FWD_MASK,
	IFLA_BRPORT_NEIGH_SUPPRESS,
	IFLA_BRPORT_ISOLATED,
	IFLA_BRPORT_BACKUP_PORT,
	IFLA_BRPORT_MRP_RING_OPEN,
	IFLA_BRPORT_MRP_IN_OPEN,
	__IFLA_BRPORT_MAX
पूर्ण;
#घोषणा IFLA_BRPORT_MAX (__IFLA_BRPORT_MAX - 1)

काष्ठा अगरla_cacheinfo अणु
	__u32	max_reयंत्र_len;
	__u32	tstamp;		/* ipv6InterfaceTable updated बारtamp */
	__u32	reachable_समय;
	__u32	retrans_समय;
पूर्ण;

क्रमागत अणु
	IFLA_INFO_UNSPEC,
	IFLA_INFO_KIND,
	IFLA_INFO_DATA,
	IFLA_INFO_XSTATS,
	IFLA_INFO_SLAVE_KIND,
	IFLA_INFO_SLAVE_DATA,
	__IFLA_INFO_MAX,
पूर्ण;

#घोषणा IFLA_INFO_MAX	(__IFLA_INFO_MAX - 1)

/* VLAN section */

क्रमागत अणु
	IFLA_VLAN_UNSPEC,
	IFLA_VLAN_ID,
	IFLA_VLAN_FLAGS,
	IFLA_VLAN_EGRESS_QOS,
	IFLA_VLAN_INGRESS_QOS,
	IFLA_VLAN_PROTOCOL,
	__IFLA_VLAN_MAX,
पूर्ण;

#घोषणा IFLA_VLAN_MAX	(__IFLA_VLAN_MAX - 1)

काष्ठा अगरla_vlan_flags अणु
	__u32	flags;
	__u32	mask;
पूर्ण;

क्रमागत अणु
	IFLA_VLAN_QOS_UNSPEC,
	IFLA_VLAN_QOS_MAPPING,
	__IFLA_VLAN_QOS_MAX
पूर्ण;

#घोषणा IFLA_VLAN_QOS_MAX	(__IFLA_VLAN_QOS_MAX - 1)

काष्ठा अगरla_vlan_qos_mapping अणु
	__u32 from;
	__u32 to;
पूर्ण;

/* MACVLAN section */
क्रमागत अणु
	IFLA_MACVLAN_UNSPEC,
	IFLA_MACVLAN_MODE,
	IFLA_MACVLAN_FLAGS,
	IFLA_MACVLAN_MACADDR_MODE,
	IFLA_MACVLAN_MACADDR,
	IFLA_MACVLAN_MACADDR_DATA,
	IFLA_MACVLAN_MACADDR_COUNT,
	IFLA_MACVLAN_BC_QUEUE_LEN,
	IFLA_MACVLAN_BC_QUEUE_LEN_USED,
	__IFLA_MACVLAN_MAX,
पूर्ण;

#घोषणा IFLA_MACVLAN_MAX (__IFLA_MACVLAN_MAX - 1)

क्रमागत macvlan_mode अणु
	MACVLAN_MODE_PRIVATE = 1, /* करोn't talk to other macvlans */
	MACVLAN_MODE_VEPA    = 2, /* talk to other ports through ext bridge */
	MACVLAN_MODE_BRIDGE  = 4, /* talk to bridge ports directly */
	MACVLAN_MODE_PASSTHRU = 8,/* take over the underlying device */
	MACVLAN_MODE_SOURCE  = 16,/* use source MAC address list to assign */
पूर्ण;

क्रमागत macvlan_macaddr_mode अणु
	MACVLAN_MACADDR_ADD,
	MACVLAN_MACADDR_DEL,
	MACVLAN_MACADDR_FLUSH,
	MACVLAN_MACADDR_SET,
पूर्ण;

#घोषणा MACVLAN_FLAG_NOPROMISC	1

/* VRF section */
क्रमागत अणु
	IFLA_VRF_UNSPEC,
	IFLA_VRF_TABLE,
	__IFLA_VRF_MAX
पूर्ण;

#घोषणा IFLA_VRF_MAX (__IFLA_VRF_MAX - 1)

क्रमागत अणु
	IFLA_VRF_PORT_UNSPEC,
	IFLA_VRF_PORT_TABLE,
	__IFLA_VRF_PORT_MAX
पूर्ण;

#घोषणा IFLA_VRF_PORT_MAX (__IFLA_VRF_PORT_MAX - 1)

/* MACSEC section */
क्रमागत अणु
	IFLA_MACSEC_UNSPEC,
	IFLA_MACSEC_SCI,
	IFLA_MACSEC_PORT,
	IFLA_MACSEC_ICV_LEN,
	IFLA_MACSEC_CIPHER_SUITE,
	IFLA_MACSEC_WINDOW,
	IFLA_MACSEC_ENCODING_SA,
	IFLA_MACSEC_ENCRYPT,
	IFLA_MACSEC_PROTECT,
	IFLA_MACSEC_INC_SCI,
	IFLA_MACSEC_ES,
	IFLA_MACSEC_SCB,
	IFLA_MACSEC_REPLAY_PROTECT,
	IFLA_MACSEC_VALIDATION,
	IFLA_MACSEC_PAD,
	IFLA_MACSEC_OFFLOAD,
	__IFLA_MACSEC_MAX,
पूर्ण;

#घोषणा IFLA_MACSEC_MAX (__IFLA_MACSEC_MAX - 1)

/* XFRM section */
क्रमागत अणु
	IFLA_XFRM_UNSPEC,
	IFLA_XFRM_LINK,
	IFLA_XFRM_IF_ID,
	__IFLA_XFRM_MAX
पूर्ण;

#घोषणा IFLA_XFRM_MAX (__IFLA_XFRM_MAX - 1)

क्रमागत macsec_validation_type अणु
	MACSEC_VALIDATE_DISABLED = 0,
	MACSEC_VALIDATE_CHECK = 1,
	MACSEC_VALIDATE_STRICT = 2,
	__MACSEC_VALIDATE_END,
	MACSEC_VALIDATE_MAX = __MACSEC_VALIDATE_END - 1,
पूर्ण;

क्रमागत macsec_offload अणु
	MACSEC_OFFLOAD_OFF = 0,
	MACSEC_OFFLOAD_PHY = 1,
	MACSEC_OFFLOAD_MAC = 2,
	__MACSEC_OFFLOAD_END,
	MACSEC_OFFLOAD_MAX = __MACSEC_OFFLOAD_END - 1,
पूर्ण;

/* IPVLAN section */
क्रमागत अणु
	IFLA_IPVLAN_UNSPEC,
	IFLA_IPVLAN_MODE,
	IFLA_IPVLAN_FLAGS,
	__IFLA_IPVLAN_MAX
पूर्ण;

#घोषणा IFLA_IPVLAN_MAX (__IFLA_IPVLAN_MAX - 1)

क्रमागत ipvlan_mode अणु
	IPVLAN_MODE_L2 = 0,
	IPVLAN_MODE_L3,
	IPVLAN_MODE_L3S,
	IPVLAN_MODE_MAX
पूर्ण;

#घोषणा IPVLAN_F_PRIVATE	0x01
#घोषणा IPVLAN_F_VEPA		0x02

/* VXLAN section */
क्रमागत अणु
	IFLA_VXLAN_UNSPEC,
	IFLA_VXLAN_ID,
	IFLA_VXLAN_GROUP,	/* group or remote address */
	IFLA_VXLAN_LINK,
	IFLA_VXLAN_LOCAL,
	IFLA_VXLAN_TTL,
	IFLA_VXLAN_TOS,
	IFLA_VXLAN_LEARNING,
	IFLA_VXLAN_AGEING,
	IFLA_VXLAN_LIMIT,
	IFLA_VXLAN_PORT_RANGE,	/* source port */
	IFLA_VXLAN_PROXY,
	IFLA_VXLAN_RSC,
	IFLA_VXLAN_L2MISS,
	IFLA_VXLAN_L3MISS,
	IFLA_VXLAN_PORT,	/* destination port */
	IFLA_VXLAN_GROUP6,
	IFLA_VXLAN_LOCAL6,
	IFLA_VXLAN_UDP_CSUM,
	IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
	IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
	IFLA_VXLAN_REMCSUM_TX,
	IFLA_VXLAN_REMCSUM_RX,
	IFLA_VXLAN_GBP,
	IFLA_VXLAN_REMCSUM_NOPARTIAL,
	IFLA_VXLAN_COLLECT_METADATA,
	IFLA_VXLAN_LABEL,
	IFLA_VXLAN_GPE,
	IFLA_VXLAN_TTL_INHERIT,
	IFLA_VXLAN_DF,
	__IFLA_VXLAN_MAX
पूर्ण;
#घोषणा IFLA_VXLAN_MAX	(__IFLA_VXLAN_MAX - 1)

काष्ठा अगरla_vxlan_port_range अणु
	__be16	low;
	__be16	high;
पूर्ण;

क्रमागत अगरla_vxlan_df अणु
	VXLAN_DF_UNSET = 0,
	VXLAN_DF_SET,
	VXLAN_DF_INHERIT,
	__VXLAN_DF_END,
	VXLAN_DF_MAX = __VXLAN_DF_END - 1,
पूर्ण;

/* GENEVE section */
क्रमागत अणु
	IFLA_GENEVE_UNSPEC,
	IFLA_GENEVE_ID,
	IFLA_GENEVE_REMOTE,
	IFLA_GENEVE_TTL,
	IFLA_GENEVE_TOS,
	IFLA_GENEVE_PORT,	/* destination port */
	IFLA_GENEVE_COLLECT_METADATA,
	IFLA_GENEVE_REMOTE6,
	IFLA_GENEVE_UDP_CSUM,
	IFLA_GENEVE_UDP_ZERO_CSUM6_TX,
	IFLA_GENEVE_UDP_ZERO_CSUM6_RX,
	IFLA_GENEVE_LABEL,
	IFLA_GENEVE_TTL_INHERIT,
	IFLA_GENEVE_DF,
	__IFLA_GENEVE_MAX
पूर्ण;
#घोषणा IFLA_GENEVE_MAX	(__IFLA_GENEVE_MAX - 1)

क्रमागत अगरla_geneve_df अणु
	GENEVE_DF_UNSET = 0,
	GENEVE_DF_SET,
	GENEVE_DF_INHERIT,
	__GENEVE_DF_END,
	GENEVE_DF_MAX = __GENEVE_DF_END - 1,
पूर्ण;

/* PPP section */
क्रमागत अणु
	IFLA_PPP_UNSPEC,
	IFLA_PPP_DEV_FD,
	__IFLA_PPP_MAX
पूर्ण;
#घोषणा IFLA_PPP_MAX (__IFLA_PPP_MAX - 1)

/* GTP section */

क्रमागत अगरla_gtp_role अणु
	GTP_ROLE_GGSN = 0,
	GTP_ROLE_SGSN,
पूर्ण;

क्रमागत अणु
	IFLA_GTP_UNSPEC,
	IFLA_GTP_FD0,
	IFLA_GTP_FD1,
	IFLA_GTP_PDP_HASHSIZE,
	IFLA_GTP_ROLE,
	__IFLA_GTP_MAX,
पूर्ण;
#घोषणा IFLA_GTP_MAX (__IFLA_GTP_MAX - 1)

/* Bonding section */

क्रमागत अणु
	IFLA_BOND_UNSPEC,
	IFLA_BOND_MODE,
	IFLA_BOND_ACTIVE_SLAVE,
	IFLA_BOND_MIIMON,
	IFLA_BOND_UPDELAY,
	IFLA_BOND_DOWNDELAY,
	IFLA_BOND_USE_CARRIER,
	IFLA_BOND_ARP_INTERVAL,
	IFLA_BOND_ARP_IP_TARGET,
	IFLA_BOND_ARP_VALIDATE,
	IFLA_BOND_ARP_ALL_TARGETS,
	IFLA_BOND_PRIMARY,
	IFLA_BOND_PRIMARY_RESELECT,
	IFLA_BOND_FAIL_OVER_MAC,
	IFLA_BOND_XMIT_HASH_POLICY,
	IFLA_BOND_RESEND_IGMP,
	IFLA_BOND_NUM_PEER_NOTIF,
	IFLA_BOND_ALL_SLAVES_ACTIVE,
	IFLA_BOND_MIN_LINKS,
	IFLA_BOND_LP_INTERVAL,
	IFLA_BOND_PACKETS_PER_SLAVE,
	IFLA_BOND_AD_LACP_RATE,
	IFLA_BOND_AD_SELECT,
	IFLA_BOND_AD_INFO,
	IFLA_BOND_AD_ACTOR_SYS_PRIO,
	IFLA_BOND_AD_USER_PORT_KEY,
	IFLA_BOND_AD_ACTOR_SYSTEM,
	IFLA_BOND_TLB_DYNAMIC_LB,
	IFLA_BOND_PEER_NOTIF_DELAY,
	__IFLA_BOND_MAX,
पूर्ण;

#घोषणा IFLA_BOND_MAX	(__IFLA_BOND_MAX - 1)

क्रमागत अणु
	IFLA_BOND_AD_INFO_UNSPEC,
	IFLA_BOND_AD_INFO_AGGREGATOR,
	IFLA_BOND_AD_INFO_NUM_PORTS,
	IFLA_BOND_AD_INFO_ACTOR_KEY,
	IFLA_BOND_AD_INFO_PARTNER_KEY,
	IFLA_BOND_AD_INFO_PARTNER_MAC,
	__IFLA_BOND_AD_INFO_MAX,
पूर्ण;

#घोषणा IFLA_BOND_AD_INFO_MAX	(__IFLA_BOND_AD_INFO_MAX - 1)

क्रमागत अणु
	IFLA_BOND_SLAVE_UNSPEC,
	IFLA_BOND_SLAVE_STATE,
	IFLA_BOND_SLAVE_MII_STATUS,
	IFLA_BOND_SLAVE_LINK_FAILURE_COUNT,
	IFLA_BOND_SLAVE_PERM_HWADDR,
	IFLA_BOND_SLAVE_QUEUE_ID,
	IFLA_BOND_SLAVE_AD_AGGREGATOR_ID,
	IFLA_BOND_SLAVE_AD_ACTOR_OPER_PORT_STATE,
	IFLA_BOND_SLAVE_AD_PARTNER_OPER_PORT_STATE,
	__IFLA_BOND_SLAVE_MAX,
पूर्ण;

#घोषणा IFLA_BOND_SLAVE_MAX	(__IFLA_BOND_SLAVE_MAX - 1)

/* SR-IOV भव function management section */

क्रमागत अणु
	IFLA_VF_INFO_UNSPEC,
	IFLA_VF_INFO,
	__IFLA_VF_INFO_MAX,
पूर्ण;

#घोषणा IFLA_VF_INFO_MAX (__IFLA_VF_INFO_MAX - 1)

क्रमागत अणु
	IFLA_VF_UNSPEC,
	IFLA_VF_MAC,		/* Hardware queue specअगरic attributes */
	IFLA_VF_VLAN,		/* VLAN ID and QoS */
	IFLA_VF_TX_RATE,	/* Max TX Bandwidth Allocation */
	IFLA_VF_SPOOFCHK,	/* Spoof Checking on/off चयन */
	IFLA_VF_LINK_STATE,	/* link state enable/disable/स्वतः चयन */
	IFLA_VF_RATE,		/* Min and Max TX Bandwidth Allocation */
	IFLA_VF_RSS_QUERY_EN,	/* RSS Redirection Table and Hash Key query
				 * on/off चयन
				 */
	IFLA_VF_STATS,		/* network device statistics */
	IFLA_VF_TRUST,		/* Trust VF */
	IFLA_VF_IB_NODE_GUID,	/* VF Infiniband node GUID */
	IFLA_VF_IB_PORT_GUID,	/* VF Infiniband port GUID */
	IFLA_VF_VLAN_LIST,	/* nested list of vlans, option क्रम QinQ */
	IFLA_VF_BROADCAST,	/* VF broadcast */
	__IFLA_VF_MAX,
पूर्ण;

#घोषणा IFLA_VF_MAX (__IFLA_VF_MAX - 1)

काष्ठा अगरla_vf_mac अणु
	__u32 vf;
	__u8 mac[32]; /* MAX_ADDR_LEN */
पूर्ण;

काष्ठा अगरla_vf_broadcast अणु
	__u8 broadcast[32];
पूर्ण;

काष्ठा अगरla_vf_vlan अणु
	__u32 vf;
	__u32 vlan; /* 0 - 4095, 0 disables VLAN filter */
	__u32 qos;
पूर्ण;

क्रमागत अणु
	IFLA_VF_VLAN_INFO_UNSPEC,
	IFLA_VF_VLAN_INFO,	/* VLAN ID, QoS and VLAN protocol */
	__IFLA_VF_VLAN_INFO_MAX,
पूर्ण;

#घोषणा IFLA_VF_VLAN_INFO_MAX (__IFLA_VF_VLAN_INFO_MAX - 1)
#घोषणा MAX_VLAN_LIST_LEN 1

काष्ठा अगरla_vf_vlan_info अणु
	__u32 vf;
	__u32 vlan; /* 0 - 4095, 0 disables VLAN filter */
	__u32 qos;
	__be16 vlan_proto; /* VLAN protocol either 802.1Q or 802.1ad */
पूर्ण;

काष्ठा अगरla_vf_tx_rate अणु
	__u32 vf;
	__u32 rate; /* Max TX bandwidth in Mbps, 0 disables throttling */
पूर्ण;

काष्ठा अगरla_vf_rate अणु
	__u32 vf;
	__u32 min_tx_rate; /* Min Bandwidth in Mbps */
	__u32 max_tx_rate; /* Max Bandwidth in Mbps */
पूर्ण;

काष्ठा अगरla_vf_spoofchk अणु
	__u32 vf;
	__u32 setting;
पूर्ण;

काष्ठा अगरla_vf_guid अणु
	__u32 vf;
	__u64 guid;
पूर्ण;

क्रमागत अणु
	IFLA_VF_LINK_STATE_AUTO,	/* link state of the uplink */
	IFLA_VF_LINK_STATE_ENABLE,	/* link always up */
	IFLA_VF_LINK_STATE_DISABLE,	/* link always करोwn */
	__IFLA_VF_LINK_STATE_MAX,
पूर्ण;

काष्ठा अगरla_vf_link_state अणु
	__u32 vf;
	__u32 link_state;
पूर्ण;

काष्ठा अगरla_vf_rss_query_en अणु
	__u32 vf;
	__u32 setting;
पूर्ण;

क्रमागत अणु
	IFLA_VF_STATS_RX_PACKETS,
	IFLA_VF_STATS_TX_PACKETS,
	IFLA_VF_STATS_RX_BYTES,
	IFLA_VF_STATS_TX_BYTES,
	IFLA_VF_STATS_BROADCAST,
	IFLA_VF_STATS_MULTICAST,
	IFLA_VF_STATS_PAD,
	IFLA_VF_STATS_RX_DROPPED,
	IFLA_VF_STATS_TX_DROPPED,
	__IFLA_VF_STATS_MAX,
पूर्ण;

#घोषणा IFLA_VF_STATS_MAX (__IFLA_VF_STATS_MAX - 1)

काष्ठा अगरla_vf_trust अणु
	__u32 vf;
	__u32 setting;
पूर्ण;

/* VF ports management section
 *
 *	Nested layout of set/get msg is:
 *
 *		[IFLA_NUM_VF]
 *		[IFLA_VF_PORTS]
 *			[IFLA_VF_PORT]
 *				[IFLA_PORT_*], ...
 *			[IFLA_VF_PORT]
 *				[IFLA_PORT_*], ...
 *			...
 *		[IFLA_PORT_SELF]
 *			[IFLA_PORT_*], ...
 */

क्रमागत अणु
	IFLA_VF_PORT_UNSPEC,
	IFLA_VF_PORT,			/* nest */
	__IFLA_VF_PORT_MAX,
पूर्ण;

#घोषणा IFLA_VF_PORT_MAX (__IFLA_VF_PORT_MAX - 1)

क्रमागत अणु
	IFLA_PORT_UNSPEC,
	IFLA_PORT_VF,			/* __u32 */
	IFLA_PORT_PROखाता,		/* string */
	IFLA_PORT_VSI_TYPE,		/* 802.1Qbg (pre-)standard VDP */
	IFLA_PORT_INSTANCE_UUID,	/* binary UUID */
	IFLA_PORT_HOST_UUID,		/* binary UUID */
	IFLA_PORT_REQUEST,		/* __u8 */
	IFLA_PORT_RESPONSE,		/* __u16, output only */
	__IFLA_PORT_MAX,
पूर्ण;

#घोषणा IFLA_PORT_MAX (__IFLA_PORT_MAX - 1)

#घोषणा PORT_PROखाता_MAX	40
#घोषणा PORT_UUID_MAX		16
#घोषणा PORT_SELF_VF		-1

क्रमागत अणु
	PORT_REQUEST_PREASSOCIATE = 0,
	PORT_REQUEST_PREASSOCIATE_RR,
	PORT_REQUEST_ASSOCIATE,
	PORT_REQUEST_DISASSOCIATE,
पूर्ण;

क्रमागत अणु
	PORT_VDP_RESPONSE_SUCCESS = 0,
	PORT_VDP_RESPONSE_INVALID_FORMAT,
	PORT_VDP_RESPONSE_INSUFFICIENT_RESOURCES,
	PORT_VDP_RESPONSE_UNUSED_VTID,
	PORT_VDP_RESPONSE_VTID_VIOLATION,
	PORT_VDP_RESPONSE_VTID_VERSION_VIOALTION,
	PORT_VDP_RESPONSE_OUT_OF_SYNC,
	/* 0x08-0xFF reserved क्रम future VDP use */
	PORT_PROखाता_RESPONSE_SUCCESS = 0x100,
	PORT_PROखाता_RESPONSE_INPROGRESS,
	PORT_PROखाता_RESPONSE_INVALID,
	PORT_PROखाता_RESPONSE_BADSTATE,
	PORT_PROखाता_RESPONSE_INSUFFICIENT_RESOURCES,
	PORT_PROखाता_RESPONSE_ERROR,
पूर्ण;

काष्ठा अगरla_port_vsi अणु
	__u8 vsi_mgr_id;
	__u8 vsi_type_id[3];
	__u8 vsi_type_version;
	__u8 pad[3];
पूर्ण;


/* IPoIB section */

क्रमागत अणु
	IFLA_IPOIB_UNSPEC,
	IFLA_IPOIB_PKEY,
	IFLA_IPOIB_MODE,
	IFLA_IPOIB_UMCAST,
	__IFLA_IPOIB_MAX
पूर्ण;

क्रमागत अणु
	IPOIB_MODE_DATAGRAM  = 0, /* using unreliable datagram QPs */
	IPOIB_MODE_CONNECTED = 1, /* using connected QPs */
पूर्ण;

#घोषणा IFLA_IPOIB_MAX (__IFLA_IPOIB_MAX - 1)


/* HSR section */

क्रमागत अणु
	IFLA_HSR_UNSPEC,
	IFLA_HSR_SLAVE1,
	IFLA_HSR_SLAVE2,
	IFLA_HSR_MULTICAST_SPEC,	/* Last byte of supervision addr */
	IFLA_HSR_SUPERVISION_ADDR,	/* Supervision frame multicast addr */
	IFLA_HSR_SEQ_NR,
	IFLA_HSR_VERSION,		/* HSR version */
	__IFLA_HSR_MAX,
पूर्ण;

#घोषणा IFLA_HSR_MAX (__IFLA_HSR_MAX - 1)

/* STATS section */

काष्ठा अगर_stats_msg अणु
	__u8  family;
	__u8  pad1;
	__u16 pad2;
	__u32 अगरindex;
	__u32 filter_mask;
पूर्ण;

/* A stats attribute can be netdev specअगरic or a global stat.
 * For netdev stats, lets use the prefix IFLA_STATS_LINK_*
 */
क्रमागत अणु
	IFLA_STATS_UNSPEC, /* also used as 64bit pad attribute */
	IFLA_STATS_LINK_64,
	IFLA_STATS_LINK_XSTATS,
	IFLA_STATS_LINK_XSTATS_SLAVE,
	IFLA_STATS_LINK_OFFLOAD_XSTATS,
	IFLA_STATS_AF_SPEC,
	__IFLA_STATS_MAX,
पूर्ण;

#घोषणा IFLA_STATS_MAX (__IFLA_STATS_MAX - 1)

#घोषणा IFLA_STATS_FILTER_BIT(ATTR)	(1 << (ATTR - 1))

/* These are embedded पूर्णांकo IFLA_STATS_LINK_XSTATS:
 * [IFLA_STATS_LINK_XSTATS]
 * -> [LINK_XSTATS_TYPE_xxx]
 *    -> [rtnl link type specअगरic attributes]
 */
क्रमागत अणु
	LINK_XSTATS_TYPE_UNSPEC,
	LINK_XSTATS_TYPE_BRIDGE,
	LINK_XSTATS_TYPE_BOND,
	__LINK_XSTATS_TYPE_MAX
पूर्ण;
#घोषणा LINK_XSTATS_TYPE_MAX (__LINK_XSTATS_TYPE_MAX - 1)

/* These are stats embedded पूर्णांकo IFLA_STATS_LINK_OFFLOAD_XSTATS */
क्रमागत अणु
	IFLA_OFFLOAD_XSTATS_UNSPEC,
	IFLA_OFFLOAD_XSTATS_CPU_HIT, /* काष्ठा rtnl_link_stats64 */
	__IFLA_OFFLOAD_XSTATS_MAX
पूर्ण;
#घोषणा IFLA_OFFLOAD_XSTATS_MAX (__IFLA_OFFLOAD_XSTATS_MAX - 1)

/* XDP section */

#घोषणा XDP_FLAGS_UPDATE_IF_NOEXIST	(1U << 0)
#घोषणा XDP_FLAGS_SKB_MODE		(1U << 1)
#घोषणा XDP_FLAGS_DRV_MODE		(1U << 2)
#घोषणा XDP_FLAGS_HW_MODE		(1U << 3)
#घोषणा XDP_FLAGS_REPLACE		(1U << 4)
#घोषणा XDP_FLAGS_MODES			(XDP_FLAGS_SKB_MODE | \
					 XDP_FLAGS_DRV_MODE | \
					 XDP_FLAGS_HW_MODE)
#घोषणा XDP_FLAGS_MASK			(XDP_FLAGS_UPDATE_IF_NOEXIST | \
					 XDP_FLAGS_MODES | XDP_FLAGS_REPLACE)

/* These are stored पूर्णांकo IFLA_XDP_ATTACHED on dump. */
क्रमागत अणु
	XDP_ATTACHED_NONE = 0,
	XDP_ATTACHED_DRV,
	XDP_ATTACHED_SKB,
	XDP_ATTACHED_HW,
	XDP_ATTACHED_MULTI,
पूर्ण;

क्रमागत अणु
	IFLA_XDP_UNSPEC,
	IFLA_XDP_FD,
	IFLA_XDP_ATTACHED,
	IFLA_XDP_FLAGS,
	IFLA_XDP_PROG_ID,
	IFLA_XDP_DRV_PROG_ID,
	IFLA_XDP_SKB_PROG_ID,
	IFLA_XDP_HW_PROG_ID,
	IFLA_XDP_EXPECTED_FD,
	__IFLA_XDP_MAX,
पूर्ण;

#घोषणा IFLA_XDP_MAX (__IFLA_XDP_MAX - 1)

क्रमागत अणु
	IFLA_EVENT_NONE,
	IFLA_EVENT_REBOOT,		/* पूर्णांकernal reset / reboot */
	IFLA_EVENT_FEATURES,		/* change in offload features */
	IFLA_EVENT_BONDING_FAILOVER,	/* change in active slave */
	IFLA_EVENT_NOTIFY_PEERS,	/* re-sent grat. arp/ndisc */
	IFLA_EVENT_IGMP_RESEND,		/* re-sent IGMP JOIN */
	IFLA_EVENT_BONDING_OPTIONS,	/* change in bonding options */
पूर्ण;

/* tun section */

क्रमागत अणु
	IFLA_TUN_UNSPEC,
	IFLA_TUN_OWNER,
	IFLA_TUN_GROUP,
	IFLA_TUN_TYPE,
	IFLA_TUN_PI,
	IFLA_TUN_VNET_HDR,
	IFLA_TUN_PERSIST,
	IFLA_TUN_MULTI_QUEUE,
	IFLA_TUN_NUM_QUEUES,
	IFLA_TUN_NUM_DISABLED_QUEUES,
	__IFLA_TUN_MAX,
पूर्ण;

#घोषणा IFLA_TUN_MAX (__IFLA_TUN_MAX - 1)

/* rmnet section */

#घोषणा RMNET_FLAGS_INGRESS_DEAGGREGATION         (1U << 0)
#घोषणा RMNET_FLAGS_INGRESS_MAP_COMMANDS          (1U << 1)
#घोषणा RMNET_FLAGS_INGRESS_MAP_CKSUMV4           (1U << 2)
#घोषणा RMNET_FLAGS_EGRESS_MAP_CKSUMV4            (1U << 3)

क्रमागत अणु
	IFLA_RMNET_UNSPEC,
	IFLA_RMNET_MUX_ID,
	IFLA_RMNET_FLAGS,
	__IFLA_RMNET_MAX,
पूर्ण;

#घोषणा IFLA_RMNET_MAX	(__IFLA_RMNET_MAX - 1)

काष्ठा अगरla_rmnet_flags अणु
	__u32	flags;
	__u32	mask;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_IF_LINK_H */
