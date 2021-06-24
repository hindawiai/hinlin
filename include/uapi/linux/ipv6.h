<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_IPV6_H
#घोषणा _UAPI_IPV6_H

#समावेश <linux/libc-compat.h>
#समावेश <linux/types.h>
#समावेश <linux/in6.h>
#समावेश <यंत्र/byteorder.h>

/* The latest drafts declared increase in minimal mtu up to 1280. */

#घोषणा IPV6_MIN_MTU	1280

/*
 *	Advanced API
 *	source पूर्णांकerface/address selection, source routing, etc...
 *	*under स्थिरruction*
 */

#अगर __UAPI_DEF_IN6_PKTINFO
काष्ठा in6_pktinfo अणु
	काष्ठा in6_addr	ipi6_addr;
	पूर्णांक		ipi6_अगरindex;
पूर्ण;
#पूर्ण_अगर

#अगर __UAPI_DEF_IP6_MTUINFO
काष्ठा ip6_mtuinfo अणु
	काष्ठा sockaddr_in6	ip6m_addr;
	__u32			ip6m_mtu;
पूर्ण;
#पूर्ण_अगर

काष्ठा in6_अगरreq अणु
	काष्ठा in6_addr	अगरr6_addr;
	__u32		अगरr6_prefixlen;
	पूर्णांक		अगरr6_अगरindex; 
पूर्ण;

#घोषणा IPV6_SRCRT_STRICT	0x01	/* Deprecated; will be हटाओd */
#घोषणा IPV6_SRCRT_TYPE_0	0	/* Deprecated; will be हटाओd */
#घोषणा IPV6_SRCRT_TYPE_2	2	/* IPv6 type 2 Routing Header	*/
#घोषणा IPV6_SRCRT_TYPE_3	3	/* RPL Segment Routing with IPv6 */
#घोषणा IPV6_SRCRT_TYPE_4	4	/* Segment Routing with IPv6 */

/*
 *	routing header
 */
काष्ठा ipv6_rt_hdr अणु
	__u8		nexthdr;
	__u8		hdrlen;
	__u8		type;
	__u8		segments_left;

	/*
	 *	type specअगरic data
	 *	variable length field
	 */
पूर्ण;


काष्ठा ipv6_opt_hdr अणु
	__u8 		nexthdr;
	__u8 		hdrlen;
	/* 
	 * TLV encoded option data follows.
	 */
पूर्ण __attribute__((packed));	/* required क्रम some archs */

#घोषणा ipv6_destopt_hdr ipv6_opt_hdr
#घोषणा ipv6_hopopt_hdr  ipv6_opt_hdr

/* Router Alert option values (RFC2711) */
#घोषणा IPV6_OPT_ROUTERALERT_MLD	0x0000	/* MLD(RFC2710) */

/*
 *	routing header type 0 (used in cmsghdr काष्ठा)
 */

काष्ठा rt0_hdr अणु
	काष्ठा ipv6_rt_hdr	rt_hdr;
	__u32			reserved;
	काष्ठा in6_addr		addr[0];

#घोषणा rt0_type		rt_hdr.type
पूर्ण;

/*
 *	routing header type 2
 */

काष्ठा rt2_hdr अणु
	काष्ठा ipv6_rt_hdr	rt_hdr;
	__u32			reserved;
	काष्ठा in6_addr		addr;

#घोषणा rt2_type		rt_hdr.type
पूर्ण;

/*
 *	home address option in destination options header
 */

काष्ठा ipv6_destopt_hao अणु
	__u8			type;
	__u8			length;
	काष्ठा in6_addr		addr;
पूर्ण __attribute__((packed));

/*
 *	IPv6 fixed header
 *
 *	BEWARE, it is incorrect. The first 4 bits of flow_lbl
 *	are glued to priority now, क्रमming "class".
 */

काष्ठा ipv6hdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8			priority:4,
				version:4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8			version:4,
				priority:4;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8			flow_lbl[3];

	__be16			payload_len;
	__u8			nexthdr;
	__u8			hop_limit;

	काष्ठा	in6_addr	saddr;
	काष्ठा	in6_addr	daddr;
पूर्ण;


/* index values क्रम the variables in ipv6_devconf */
क्रमागत अणु
	DEVCONF_FORWARDING = 0,
	DEVCONF_HOPLIMIT,
	DEVCONF_MTU6,
	DEVCONF_ACCEPT_RA,
	DEVCONF_ACCEPT_REसूचीECTS,
	DEVCONF_AUTOCONF,
	DEVCONF_DAD_TRANSMITS,
	DEVCONF_RTR_SOLICITS,
	DEVCONF_RTR_SOLICIT_INTERVAL,
	DEVCONF_RTR_SOLICIT_DELAY,
	DEVCONF_USE_TEMPADDR,
	DEVCONF_TEMP_VALID_LFT,
	DEVCONF_TEMP_PREFERED_LFT,
	DEVCONF_REGEN_MAX_RETRY,
	DEVCONF_MAX_DESYNC_FACTOR,
	DEVCONF_MAX_ADDRESSES,
	DEVCONF_FORCE_MLD_VERSION,
	DEVCONF_ACCEPT_RA_DEFRTR,
	DEVCONF_ACCEPT_RA_PINFO,
	DEVCONF_ACCEPT_RA_RTR_PREF,
	DEVCONF_RTR_PROBE_INTERVAL,
	DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN,
	DEVCONF_PROXY_NDP,
	DEVCONF_OPTIMISTIC_DAD,
	DEVCONF_ACCEPT_SOURCE_ROUTE,
	DEVCONF_MC_FORWARDING,
	DEVCONF_DISABLE_IPV6,
	DEVCONF_ACCEPT_DAD,
	DEVCONF_FORCE_TLLAO,
	DEVCONF_NDISC_NOTIFY,
	DEVCONF_MLDV1_UNSOLICITED_REPORT_INTERVAL,
	DEVCONF_MLDV2_UNSOLICITED_REPORT_INTERVAL,
	DEVCONF_SUPPRESS_FRAG_NDISC,
	DEVCONF_ACCEPT_RA_FROM_LOCAL,
	DEVCONF_USE_OPTIMISTIC,
	DEVCONF_ACCEPT_RA_MTU,
	DEVCONF_STABLE_SECRET,
	DEVCONF_USE_OIF_ADDRS_ONLY,
	DEVCONF_ACCEPT_RA_MIN_HOP_LIMIT,
	DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN,
	DEVCONF_DROP_UNICAST_IN_L2_MULTICAST,
	DEVCONF_DROP_UNSOLICITED_NA,
	DEVCONF_KEEP_ADDR_ON_DOWN,
	DEVCONF_RTR_SOLICIT_MAX_INTERVAL,
	DEVCONF_SEG6_ENABLED,
	DEVCONF_SEG6_REQUIRE_HMAC,
	DEVCONF_ENHANCED_DAD,
	DEVCONF_ADDR_GEN_MODE,
	DEVCONF_DISABLE_POLICY,
	DEVCONF_ACCEPT_RA_RT_INFO_MIN_PLEN,
	DEVCONF_NDISC_TCLASS,
	DEVCONF_RPL_SEG_ENABLED,
	DEVCONF_RA_DEFRTR_METRIC,
	DEVCONF_MAX
पूर्ण;


#पूर्ण_अगर /* _UAPI_IPV6_H */
