<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_FILTER_H
#घोषणा EF4_FILTER_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <यंत्र/byteorder.h>

/**
 * क्रमागत ef4_filter_match_flags - Flags क्रम hardware filter match type
 * @EF4_FILTER_MATCH_REM_HOST: Match by remote IP host address
 * @EF4_FILTER_MATCH_LOC_HOST: Match by local IP host address
 * @EF4_FILTER_MATCH_REM_MAC: Match by remote MAC address
 * @EF4_FILTER_MATCH_REM_PORT: Match by remote TCP/UDP port
 * @EF4_FILTER_MATCH_LOC_MAC: Match by local MAC address
 * @EF4_FILTER_MATCH_LOC_PORT: Match by local TCP/UDP port
 * @EF4_FILTER_MATCH_ETHER_TYPE: Match by Ether-type
 * @EF4_FILTER_MATCH_INNER_VID: Match by inner VLAN ID
 * @EF4_FILTER_MATCH_OUTER_VID: Match by outer VLAN ID
 * @EF4_FILTER_MATCH_IP_PROTO: Match by IP transport protocol
 * @EF4_FILTER_MATCH_LOC_MAC_IG: Match by local MAC address I/G bit.
 *	Used क्रम RX शेष unicast and multicast/broadcast filters.
 *
 * Only some combinations are supported, depending on NIC type:
 *
 * - Falcon supports RX filters matching by अणुTCP,UDPपूर्ण/IPv4 4-tuple or
 *   local 2-tuple (only implemented क्रम Falcon B0)
 *
 * - Siena supports RX and TX filters matching by अणुTCP,UDPपूर्ण/IPv4 4-tuple
 *   or local 2-tuple, or local MAC with or without outer VID, and RX
 *   शेष filters
 *
 * - Huntington supports filter matching controlled by firmware, potentially
 *   using अणुTCP,UDPपूर्ण/IPvअणु4,6पूर्ण 4-tuple or local 2-tuple, local MAC or I/G bit,
 *   with or without outer and inner VID
 */
क्रमागत ef4_filter_match_flags अणु
	EF4_FILTER_MATCH_REM_HOST =	0x0001,
	EF4_FILTER_MATCH_LOC_HOST =	0x0002,
	EF4_FILTER_MATCH_REM_MAC =	0x0004,
	EF4_FILTER_MATCH_REM_PORT =	0x0008,
	EF4_FILTER_MATCH_LOC_MAC =	0x0010,
	EF4_FILTER_MATCH_LOC_PORT =	0x0020,
	EF4_FILTER_MATCH_ETHER_TYPE =	0x0040,
	EF4_FILTER_MATCH_INNER_VID =	0x0080,
	EF4_FILTER_MATCH_OUTER_VID =	0x0100,
	EF4_FILTER_MATCH_IP_PROTO =	0x0200,
	EF4_FILTER_MATCH_LOC_MAC_IG =	0x0400,
पूर्ण;

/**
 * क्रमागत ef4_filter_priority - priority of a hardware filter specअगरication
 * @EF4_FILTER_PRI_HINT: Perक्रमmance hपूर्णांक
 * @EF4_FILTER_PRI_AUTO: Automatic filter based on device address list
 *	or hardware requirements.  This may only be used by the filter
 *	implementation क्रम each NIC type.
 * @EF4_FILTER_PRI_MANUAL: Manually configured filter
 * @EF4_FILTER_PRI_REQUIRED: Required क्रम correct behaviour (user-level
 *	networking and SR-IOV)
 */
क्रमागत ef4_filter_priority अणु
	EF4_FILTER_PRI_HINT = 0,
	EF4_FILTER_PRI_AUTO,
	EF4_FILTER_PRI_MANUAL,
	EF4_FILTER_PRI_REQUIRED,
पूर्ण;

/**
 * क्रमागत ef4_filter_flags - flags क्रम hardware filter specअगरications
 * @EF4_FILTER_FLAG_RX_RSS: Use RSS to spपढ़ो across multiple queues.
 *	By शेष, matching packets will be delivered only to the
 *	specअगरied queue. If this flag is set, they will be delivered
 *	to a range of queues offset from the specअगरied queue number
 *	according to the indirection table.
 * @EF4_FILTER_FLAG_RX_SCATTER: Enable DMA scatter on the receiving
 *	queue.
 * @EF4_FILTER_FLAG_RX_OVER_AUTO: Indicates a filter that is
 *	overriding an स्वतःmatic filter (priority
 *	%EF4_FILTER_PRI_AUTO).  This may only be set by the filter
 *	implementation क्रम each type.  A removal request will restore
 *	the स्वतःmatic filter in its place.
 * @EF4_FILTER_FLAG_RX: Filter is क्रम RX
 * @EF4_FILTER_FLAG_TX: Filter is क्रम TX
 */
क्रमागत ef4_filter_flags अणु
	EF4_FILTER_FLAG_RX_RSS = 0x01,
	EF4_FILTER_FLAG_RX_SCATTER = 0x02,
	EF4_FILTER_FLAG_RX_OVER_AUTO = 0x04,
	EF4_FILTER_FLAG_RX = 0x08,
	EF4_FILTER_FLAG_TX = 0x10,
पूर्ण;

/**
 * काष्ठा ef4_filter_spec - specअगरication क्रम a hardware filter
 * @match_flags: Match type flags, from &क्रमागत ef4_filter_match_flags
 * @priority: Priority of the filter, from &क्रमागत ef4_filter_priority
 * @flags: Miscellaneous flags, from &क्रमागत ef4_filter_flags
 * @rss_context: RSS context to use, अगर %EF4_FILTER_FLAG_RX_RSS is set
 * @dmaq_id: Source/target queue index, or %EF4_FILTER_RX_DMAQ_ID_DROP क्रम
 *	an RX drop filter
 * @outer_vid: Outer VLAN ID to match, अगर %EF4_FILTER_MATCH_OUTER_VID is set
 * @inner_vid: Inner VLAN ID to match, अगर %EF4_FILTER_MATCH_INNER_VID is set
 * @loc_mac: Local MAC address to match, अगर %EF4_FILTER_MATCH_LOC_MAC or
 *	%EF4_FILTER_MATCH_LOC_MAC_IG is set
 * @rem_mac: Remote MAC address to match, अगर %EF4_FILTER_MATCH_REM_MAC is set
 * @ether_type: Ether-type to match, अगर %EF4_FILTER_MATCH_ETHER_TYPE is set
 * @ip_proto: IP transport protocol to match, अगर %EF4_FILTER_MATCH_IP_PROTO
 *	is set
 * @loc_host: Local IP host to match, अगर %EF4_FILTER_MATCH_LOC_HOST is set
 * @rem_host: Remote IP host to match, अगर %EF4_FILTER_MATCH_REM_HOST is set
 * @loc_port: Local TCP/UDP port to match, अगर %EF4_FILTER_MATCH_LOC_PORT is set
 * @rem_port: Remote TCP/UDP port to match, अगर %EF4_FILTER_MATCH_REM_PORT is set
 *
 * The ef4_filter_init_rx() or ef4_filter_init_tx() function *must* be
 * used to initialise the काष्ठाure.  The ef4_filter_set_*() functions
 * may then be used to set @rss_context, @match_flags and related
 * fields.
 *
 * The @priority field is used by software to determine whether a new
 * filter may replace an old one.  The hardware priority of a filter
 * depends on which fields are matched.
 */
काष्ठा ef4_filter_spec अणु
	u32	match_flags:12;
	u32	priority:2;
	u32	flags:6;
	u32	dmaq_id:12;
	u32	rss_context;
	__be16	outer_vid __aligned(4); /* allow jhash2() of match values */
	__be16	inner_vid;
	u8	loc_mac[ETH_ALEN];
	u8	rem_mac[ETH_ALEN];
	__be16	ether_type;
	u8	ip_proto;
	__be32	loc_host[4];
	__be32	rem_host[4];
	__be16	loc_port;
	__be16	rem_port;
	/* total 64 bytes */
पूर्ण;

क्रमागत अणु
	EF4_FILTER_RSS_CONTEXT_DEFAULT = 0xffffffff,
	EF4_FILTER_RX_DMAQ_ID_DROP = 0xfff
पूर्ण;

अटल अंतरभूत व्योम ef4_filter_init_rx(काष्ठा ef4_filter_spec *spec,
				      क्रमागत ef4_filter_priority priority,
				      क्रमागत ef4_filter_flags flags,
				      अचिन्हित rxq_id)
अणु
	स_रखो(spec, 0, माप(*spec));
	spec->priority = priority;
	spec->flags = EF4_FILTER_FLAG_RX | flags;
	spec->rss_context = EF4_FILTER_RSS_CONTEXT_DEFAULT;
	spec->dmaq_id = rxq_id;
पूर्ण

अटल अंतरभूत व्योम ef4_filter_init_tx(काष्ठा ef4_filter_spec *spec,
				      अचिन्हित txq_id)
अणु
	स_रखो(spec, 0, माप(*spec));
	spec->priority = EF4_FILTER_PRI_REQUIRED;
	spec->flags = EF4_FILTER_FLAG_TX;
	spec->dmaq_id = txq_id;
पूर्ण

/**
 * ef4_filter_set_ipv4_local - specअगरy IPv4 host, transport protocol and port
 * @spec: Specअगरication to initialise
 * @proto: Transport layer protocol number
 * @host: Local host address (network byte order)
 * @port: Local port (network byte order)
 */
अटल अंतरभूत पूर्णांक
ef4_filter_set_ipv4_local(काष्ठा ef4_filter_spec *spec, u8 proto,
			  __be32 host, __be16 port)
अणु
	spec->match_flags |=
		EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_LOC_PORT;
	spec->ether_type = htons(ETH_P_IP);
	spec->ip_proto = proto;
	spec->loc_host[0] = host;
	spec->loc_port = port;
	वापस 0;
पूर्ण

/**
 * ef4_filter_set_ipv4_full - specअगरy IPv4 hosts, transport protocol and ports
 * @spec: Specअगरication to initialise
 * @proto: Transport layer protocol number
 * @lhost: Local host address (network byte order)
 * @lport: Local port (network byte order)
 * @rhost: Remote host address (network byte order)
 * @rport: Remote port (network byte order)
 */
अटल अंतरभूत पूर्णांक
ef4_filter_set_ipv4_full(काष्ठा ef4_filter_spec *spec, u8 proto,
			 __be32 lhost, __be16 lport,
			 __be32 rhost, __be16 rport)
अणु
	spec->match_flags |=
		EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_LOC_PORT |
		EF4_FILTER_MATCH_REM_HOST | EF4_FILTER_MATCH_REM_PORT;
	spec->ether_type = htons(ETH_P_IP);
	spec->ip_proto = proto;
	spec->loc_host[0] = lhost;
	spec->loc_port = lport;
	spec->rem_host[0] = rhost;
	spec->rem_port = rport;
	वापस 0;
पूर्ण

क्रमागत अणु
	EF4_FILTER_VID_UNSPEC = 0xffff,
पूर्ण;

/**
 * ef4_filter_set_eth_local - specअगरy local Ethernet address and/or VID
 * @spec: Specअगरication to initialise
 * @vid: Outer VLAN ID to match, or %EF4_FILTER_VID_UNSPEC
 * @addr: Local Ethernet MAC address, or %शून्य
 */
अटल अंतरभूत पूर्णांक ef4_filter_set_eth_local(काष्ठा ef4_filter_spec *spec,
					   u16 vid, स्थिर u8 *addr)
अणु
	अगर (vid == EF4_FILTER_VID_UNSPEC && addr == शून्य)
		वापस -EINVAL;

	अगर (vid != EF4_FILTER_VID_UNSPEC) अणु
		spec->match_flags |= EF4_FILTER_MATCH_OUTER_VID;
		spec->outer_vid = htons(vid);
	पूर्ण
	अगर (addr != शून्य) अणु
		spec->match_flags |= EF4_FILTER_MATCH_LOC_MAC;
		ether_addr_copy(spec->loc_mac, addr);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ef4_filter_set_uc_def - specअगरy matching otherwise-unmatched unicast
 * @spec: Specअगरication to initialise
 */
अटल अंतरभूत पूर्णांक ef4_filter_set_uc_def(काष्ठा ef4_filter_spec *spec)
अणु
	spec->match_flags |= EF4_FILTER_MATCH_LOC_MAC_IG;
	वापस 0;
पूर्ण

/**
 * ef4_filter_set_mc_def - specअगरy matching otherwise-unmatched multicast
 * @spec: Specअगरication to initialise
 */
अटल अंतरभूत पूर्णांक ef4_filter_set_mc_def(काष्ठा ef4_filter_spec *spec)
अणु
	spec->match_flags |= EF4_FILTER_MATCH_LOC_MAC_IG;
	spec->loc_mac[0] = 1;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* EF4_FILTER_H */
