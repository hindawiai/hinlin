<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_RTNETLINK_H
#घोषणा _UAPI__LINUX_RTNETLINK_H

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_addr.h>
#समावेश <linux/neighbour.h>

/* rtnetlink families. Values up to 127 are reserved क्रम real address
 * families, values above 128 may be used arbitrarily.
 */
#घोषणा RTNL_FAMILY_IPMR		128
#घोषणा RTNL_FAMILY_IP6MR		129
#घोषणा RTNL_FAMILY_MAX			129

/****
 *		Routing/neighbour discovery messages.
 ****/

/* Types of messages */

क्रमागत अणु
	RTM_BASE	= 16,
#घोषणा RTM_BASE	RTM_BASE

	RTM_NEWLINK	= 16,
#घोषणा RTM_NEWLINK	RTM_NEWLINK
	RTM_DELLINK,
#घोषणा RTM_DELLINK	RTM_DELLINK
	RTM_GETLINK,
#घोषणा RTM_GETLINK	RTM_GETLINK
	RTM_SETLINK,
#घोषणा RTM_SETLINK	RTM_SETLINK

	RTM_NEWADDR	= 20,
#घोषणा RTM_NEWADDR	RTM_NEWADDR
	RTM_DELADDR,
#घोषणा RTM_DELADDR	RTM_DELADDR
	RTM_GETADDR,
#घोषणा RTM_GETADDR	RTM_GETADDR

	RTM_NEWROUTE	= 24,
#घोषणा RTM_NEWROUTE	RTM_NEWROUTE
	RTM_DELROUTE,
#घोषणा RTM_DELROUTE	RTM_DELROUTE
	RTM_GETROUTE,
#घोषणा RTM_GETROUTE	RTM_GETROUTE

	RTM_NEWNEIGH	= 28,
#घोषणा RTM_NEWNEIGH	RTM_NEWNEIGH
	RTM_DELNEIGH,
#घोषणा RTM_DELNEIGH	RTM_DELNEIGH
	RTM_GETNEIGH,
#घोषणा RTM_GETNEIGH	RTM_GETNEIGH

	RTM_NEWRULE	= 32,
#घोषणा RTM_NEWRULE	RTM_NEWRULE
	RTM_DELRULE,
#घोषणा RTM_DELRULE	RTM_DELRULE
	RTM_GETRULE,
#घोषणा RTM_GETRULE	RTM_GETRULE

	RTM_NEWQDISC	= 36,
#घोषणा RTM_NEWQDISC	RTM_NEWQDISC
	RTM_DELQDISC,
#घोषणा RTM_DELQDISC	RTM_DELQDISC
	RTM_GETQDISC,
#घोषणा RTM_GETQDISC	RTM_GETQDISC

	RTM_NEWTCLASS	= 40,
#घोषणा RTM_NEWTCLASS	RTM_NEWTCLASS
	RTM_DELTCLASS,
#घोषणा RTM_DELTCLASS	RTM_DELTCLASS
	RTM_GETTCLASS,
#घोषणा RTM_GETTCLASS	RTM_GETTCLASS

	RTM_NEWTFILTER	= 44,
#घोषणा RTM_NEWTFILTER	RTM_NEWTFILTER
	RTM_DELTFILTER,
#घोषणा RTM_DELTFILTER	RTM_DELTFILTER
	RTM_GETTFILTER,
#घोषणा RTM_GETTFILTER	RTM_GETTFILTER

	RTM_NEWACTION	= 48,
#घोषणा RTM_NEWACTION   RTM_NEWACTION
	RTM_DELACTION,
#घोषणा RTM_DELACTION   RTM_DELACTION
	RTM_GETACTION,
#घोषणा RTM_GETACTION   RTM_GETACTION

	RTM_NEWPREFIX	= 52,
#घोषणा RTM_NEWPREFIX	RTM_NEWPREFIX

	RTM_GETMULTICAST = 58,
#घोषणा RTM_GETMULTICAST RTM_GETMULTICAST

	RTM_GETANYCAST	= 62,
#घोषणा RTM_GETANYCAST	RTM_GETANYCAST

	RTM_NEWNEIGHTBL	= 64,
#घोषणा RTM_NEWNEIGHTBL	RTM_NEWNEIGHTBL
	RTM_GETNEIGHTBL	= 66,
#घोषणा RTM_GETNEIGHTBL	RTM_GETNEIGHTBL
	RTM_SETNEIGHTBL,
#घोषणा RTM_SETNEIGHTBL	RTM_SETNEIGHTBL

	RTM_NEWNDUSEROPT = 68,
#घोषणा RTM_NEWNDUSEROPT RTM_NEWNDUSEROPT

	RTM_NEWADDRLABEL = 72,
#घोषणा RTM_NEWADDRLABEL RTM_NEWADDRLABEL
	RTM_DELADDRLABEL,
#घोषणा RTM_DELADDRLABEL RTM_DELADDRLABEL
	RTM_GETADDRLABEL,
#घोषणा RTM_GETADDRLABEL RTM_GETADDRLABEL

	RTM_GETDCB = 78,
#घोषणा RTM_GETDCB RTM_GETDCB
	RTM_SETDCB,
#घोषणा RTM_SETDCB RTM_SETDCB

	RTM_NEWNETCONF = 80,
#घोषणा RTM_NEWNETCONF RTM_NEWNETCONF
	RTM_DELNETCONF,
#घोषणा RTM_DELNETCONF RTM_DELNETCONF
	RTM_GETNETCONF = 82,
#घोषणा RTM_GETNETCONF RTM_GETNETCONF

	RTM_NEWMDB = 84,
#घोषणा RTM_NEWMDB RTM_NEWMDB
	RTM_DELMDB = 85,
#घोषणा RTM_DELMDB RTM_DELMDB
	RTM_GETMDB = 86,
#घोषणा RTM_GETMDB RTM_GETMDB

	RTM_NEWNSID = 88,
#घोषणा RTM_NEWNSID RTM_NEWNSID
	RTM_DELNSID = 89,
#घोषणा RTM_DELNSID RTM_DELNSID
	RTM_GETNSID = 90,
#घोषणा RTM_GETNSID RTM_GETNSID

	RTM_NEWSTATS = 92,
#घोषणा RTM_NEWSTATS RTM_NEWSTATS
	RTM_GETSTATS = 94,
#घोषणा RTM_GETSTATS RTM_GETSTATS

	RTM_NEWCACHEREPORT = 96,
#घोषणा RTM_NEWCACHEREPORT RTM_NEWCACHEREPORT

	RTM_NEWCHAIN = 100,
#घोषणा RTM_NEWCHAIN RTM_NEWCHAIN
	RTM_DELCHAIN,
#घोषणा RTM_DELCHAIN RTM_DELCHAIN
	RTM_GETCHAIN,
#घोषणा RTM_GETCHAIN RTM_GETCHAIN

	RTM_NEWNEXTHOP = 104,
#घोषणा RTM_NEWNEXTHOP	RTM_NEWNEXTHOP
	RTM_DELNEXTHOP,
#घोषणा RTM_DELNEXTHOP	RTM_DELNEXTHOP
	RTM_GETNEXTHOP,
#घोषणा RTM_GETNEXTHOP	RTM_GETNEXTHOP

	RTM_NEWLINKPROP = 108,
#घोषणा RTM_NEWLINKPROP	RTM_NEWLINKPROP
	RTM_DELLINKPROP,
#घोषणा RTM_DELLINKPROP	RTM_DELLINKPROP
	RTM_GETLINKPROP,
#घोषणा RTM_GETLINKPROP	RTM_GETLINKPROP

	RTM_NEWVLAN = 112,
#घोषणा RTM_NEWNVLAN	RTM_NEWVLAN
	RTM_DELVLAN,
#घोषणा RTM_DELVLAN	RTM_DELVLAN
	RTM_GETVLAN,
#घोषणा RTM_GETVLAN	RTM_GETVLAN

	RTM_NEWNEXTHOPBUCKET = 116,
#घोषणा RTM_NEWNEXTHOPBUCKET	RTM_NEWNEXTHOPBUCKET
	RTM_DELNEXTHOPBUCKET,
#घोषणा RTM_DELNEXTHOPBUCKET	RTM_DELNEXTHOPBUCKET
	RTM_GETNEXTHOPBUCKET,
#घोषणा RTM_GETNEXTHOPBUCKET	RTM_GETNEXTHOPBUCKET

	__RTM_MAX,
#घोषणा RTM_MAX		(((__RTM_MAX + 3) & ~3) - 1)
पूर्ण;

#घोषणा RTM_NR_MSGTYPES	(RTM_MAX + 1 - RTM_BASE)
#घोषणा RTM_NR_FAMILIES	(RTM_NR_MSGTYPES >> 2)
#घोषणा RTM_FAM(cmd)	(((cmd) - RTM_BASE) >> 2)

/* 
   Generic काष्ठाure क्रम encapsulation of optional route inक्रमmation.
   It is reminiscent of sockaddr, but with sa_family replaced
   with attribute type.
 */

काष्ठा rtattr अणु
	अचिन्हित लघु	rta_len;
	अचिन्हित लघु	rta_type;
पूर्ण;

/* Macros to handle rtattributes */

#घोषणा RTA_ALIGNTO	4U
#घोषणा RTA_ALIGN(len) ( ((len)+RTA_ALIGNTO-1) & ~(RTA_ALIGNTO-1) )
#घोषणा RTA_OK(rta,len) ((len) >= (पूर्णांक)माप(काष्ठा rtattr) && \
			 (rta)->rta_len >= माप(काष्ठा rtattr) && \
			 (rta)->rta_len <= (len))
#घोषणा RTA_NEXT(rta,attrlen)	((attrlen) -= RTA_ALIGN((rta)->rta_len), \
				 (काष्ठा rtattr*)(((अक्षर*)(rta)) + RTA_ALIGN((rta)->rta_len)))
#घोषणा RTA_LENGTH(len)	(RTA_ALIGN(माप(काष्ठा rtattr)) + (len))
#घोषणा RTA_SPACE(len)	RTA_ALIGN(RTA_LENGTH(len))
#घोषणा RTA_DATA(rta)   ((व्योम*)(((अक्षर*)(rta)) + RTA_LENGTH(0)))
#घोषणा RTA_PAYLOAD(rta) ((पूर्णांक)((rta)->rta_len) - RTA_LENGTH(0))




/******************************************************************************
 *		Definitions used in routing table administration.
 ****/

काष्ठा rपंचांगsg अणु
	अचिन्हित अक्षर		rपंचांग_family;
	अचिन्हित अक्षर		rपंचांग_dst_len;
	अचिन्हित अक्षर		rपंचांग_src_len;
	अचिन्हित अक्षर		rपंचांग_tos;

	अचिन्हित अक्षर		rपंचांग_table;	/* Routing table id */
	अचिन्हित अक्षर		rपंचांग_protocol;	/* Routing protocol; see below	*/
	अचिन्हित अक्षर		rपंचांग_scope;	/* See below */	
	अचिन्हित अक्षर		rपंचांग_type;	/* See below	*/

	अचिन्हित		rपंचांग_flags;
पूर्ण;

/* rपंचांग_type */

क्रमागत अणु
	RTN_UNSPEC,
	RTN_UNICAST,		/* Gateway or direct route	*/
	RTN_LOCAL,		/* Accept locally		*/
	RTN_BROADCAST,		/* Accept locally as broadcast,
				   send as broadcast */
	RTN_ANYCAST,		/* Accept locally as broadcast,
				   but send as unicast */
	RTN_MULTICAST,		/* Multicast route		*/
	RTN_BLACKHOLE,		/* Drop				*/
	RTN_UNREACHABLE,	/* Destination is unreachable   */
	RTN_PROHIBIT,		/* Administratively prohibited	*/
	RTN_THROW,		/* Not in this table		*/
	RTN_NAT,		/* Translate this address	*/
	RTN_XRESOLVE,		/* Use बाह्यal resolver	*/
	__RTN_MAX
पूर्ण;

#घोषणा RTN_MAX (__RTN_MAX - 1)


/* rपंचांग_protocol */

#घोषणा RTPROT_UNSPEC		0
#घोषणा RTPROT_REसूचीECT		1	/* Route installed by ICMP redirects;
					   not used by current IPv4 */
#घोषणा RTPROT_KERNEL		2	/* Route installed by kernel		*/
#घोषणा RTPROT_BOOT		3	/* Route installed during boot		*/
#घोषणा RTPROT_STATIC		4	/* Route installed by administrator	*/

/* Values of protocol >= RTPROT_STATIC are not पूर्णांकerpreted by kernel;
   they are just passed from user and back as is.
   It will be used by hypothetical multiple routing daemons.
   Note that protocol values should be standardized in order to
   aव्योम conflicts.
 */

#घोषणा RTPROT_GATED		8	/* Apparently, GateD */
#घोषणा RTPROT_RA		9	/* RDISC/ND router advertisements */
#घोषणा RTPROT_MRT		10	/* Merit MRT */
#घोषणा RTPROT_ZEBRA		11	/* Zebra */
#घोषणा RTPROT_BIRD		12	/* BIRD */
#घोषणा RTPROT_DNROUTED		13	/* DECnet routing daemon */
#घोषणा RTPROT_XORP		14	/* XORP */
#घोषणा RTPROT_NTK		15	/* Netsukuku */
#घोषणा RTPROT_DHCP		16	/* DHCP client */
#घोषणा RTPROT_MROUTED		17	/* Multicast daemon */
#घोषणा RTPROT_KEEPALIVED	18	/* Keepalived daemon */
#घोषणा RTPROT_BABEL		42	/* Babel daemon */
#घोषणा RTPROT_OPENR		99	/* Open Routing (Open/R) Routes */
#घोषणा RTPROT_BGP		186	/* BGP Routes */
#घोषणा RTPROT_ISIS		187	/* ISIS Routes */
#घोषणा RTPROT_OSPF		188	/* OSPF Routes */
#घोषणा RTPROT_RIP		189	/* RIP Routes */
#घोषणा RTPROT_EIGRP		192	/* EIGRP Routes */

/* rपंचांग_scope

   Really it is not scope, but sort of distance to the destination.
   NOWHERE are reserved क्रम not existing destinations, HOST is our
   local addresses, LINK are destinations, located on directly attached
   link and UNIVERSE is everywhere in the Universe.

   Intermediate values are also possible f.e. पूर्णांकerior routes
   could be asचिन्हित a value between UNIVERSE and LINK.
*/

क्रमागत rt_scope_t अणु
	RT_SCOPE_UNIVERSE=0,
/* User defined values  */
	RT_SCOPE_SITE=200,
	RT_SCOPE_LINK=253,
	RT_SCOPE_HOST=254,
	RT_SCOPE_NOWHERE=255
पूर्ण;

/* rपंचांग_flags */

#घोषणा RTM_F_NOTIFY		0x100	/* Notअगरy user of route change	*/
#घोषणा RTM_F_CLONED		0x200	/* This route is cloned		*/
#घोषणा RTM_F_EQUALIZE		0x400	/* Multipath equalizer: NI	*/
#घोषणा RTM_F_PREFIX		0x800	/* Prefix addresses		*/
#घोषणा RTM_F_LOOKUP_TABLE	0x1000	/* set rपंचांग_table to FIB lookup result */
#घोषणा RTM_F_FIB_MATCH	        0x2000	/* वापस full fib lookup match */
#घोषणा RTM_F_OFFLOAD		0x4000	/* route is offloaded */
#घोषणा RTM_F_TRAP		0x8000	/* route is trapping packets */
#घोषणा RTM_F_OFFLOAD_FAILED	0x20000000 /* route offload failed, this value
					    * is chosen to aव्योम conflicts with
					    * other flags defined in
					    * include/uapi/linux/ipv6_route.h
					    */

/* Reserved table identअगरiers */

क्रमागत rt_class_t अणु
	RT_TABLE_UNSPEC=0,
/* User defined values */
	RT_TABLE_COMPAT=252,
	RT_TABLE_DEFAULT=253,
	RT_TABLE_MAIN=254,
	RT_TABLE_LOCAL=255,
	RT_TABLE_MAX=0xFFFFFFFF
पूर्ण;


/* Routing message attributes */

क्रमागत rtattr_type_t अणु
	RTA_UNSPEC,
	RTA_DST,
	RTA_SRC,
	RTA_IIF,
	RTA_OIF,
	RTA_GATEWAY,
	RTA_PRIORITY,
	RTA_PREFSRC,
	RTA_METRICS,
	RTA_MULTIPATH,
	RTA_PROTOINFO, /* no दीर्घer used */
	RTA_FLOW,
	RTA_CACHEINFO,
	RTA_SESSION, /* no दीर्घer used */
	RTA_MP_ALGO, /* no दीर्घer used */
	RTA_TABLE,
	RTA_MARK,
	RTA_MFC_STATS,
	RTA_VIA,
	RTA_NEWDST,
	RTA_PREF,
	RTA_ENCAP_TYPE,
	RTA_ENCAP,
	RTA_EXPIRES,
	RTA_PAD,
	RTA_UID,
	RTA_TTL_PROPAGATE,
	RTA_IP_PROTO,
	RTA_SPORT,
	RTA_DPORT,
	RTA_NH_ID,
	__RTA_MAX
पूर्ण;

#घोषणा RTA_MAX (__RTA_MAX - 1)

#घोषणा RTM_RTA(r)  ((काष्ठा rtattr*)(((अक्षर*)(r)) + NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))))
#घोषणा RTM_PAYLOAD(n) NLMSG_PAYLOAD(n,माप(काष्ठा rपंचांगsg))

/* RTM_MULTIPATH --- array of काष्ठा rtnexthop.
 *
 * "struct rtnexthop" describes all necessary nexthop inक्रमmation,
 * i.e. parameters of path to a destination via this nexthop.
 *
 * At the moment it is impossible to set dअगरferent prefsrc, mtu, winकरोw
 * and rtt क्रम dअगरferent paths from multipath.
 */

काष्ठा rtnexthop अणु
	अचिन्हित लघु		rtnh_len;
	अचिन्हित अक्षर		rtnh_flags;
	अचिन्हित अक्षर		rtnh_hops;
	पूर्णांक			rtnh_अगरindex;
पूर्ण;

/* rtnh_flags */

#घोषणा RTNH_F_DEAD		1	/* Nexthop is dead (used by multipath)	*/
#घोषणा RTNH_F_PERVASIVE	2	/* Do recursive gateway lookup	*/
#घोषणा RTNH_F_ONLINK		4	/* Gateway is क्रमced on link	*/
#घोषणा RTNH_F_OFFLOAD		8	/* Nexthop is offloaded */
#घोषणा RTNH_F_LINKDOWN		16	/* carrier-करोwn on nexthop */
#घोषणा RTNH_F_UNRESOLVED	32	/* The entry is unresolved (ipmr) */
#घोषणा RTNH_F_TRAP		64	/* Nexthop is trapping packets */

#घोषणा RTNH_COMPARE_MASK	(RTNH_F_DEAD | RTNH_F_LINKDOWN | \
				 RTNH_F_OFFLOAD | RTNH_F_TRAP)

/* Macros to handle hexthops */

#घोषणा RTNH_ALIGNTO	4
#घोषणा RTNH_ALIGN(len) ( ((len)+RTNH_ALIGNTO-1) & ~(RTNH_ALIGNTO-1) )
#घोषणा RTNH_OK(rtnh,len) ((rtnh)->rtnh_len >= माप(काष्ठा rtnexthop) && \
			   ((पूर्णांक)(rtnh)->rtnh_len) <= (len))
#घोषणा RTNH_NEXT(rtnh)	((काष्ठा rtnexthop*)(((अक्षर*)(rtnh)) + RTNH_ALIGN((rtnh)->rtnh_len)))
#घोषणा RTNH_LENGTH(len) (RTNH_ALIGN(माप(काष्ठा rtnexthop)) + (len))
#घोषणा RTNH_SPACE(len)	RTNH_ALIGN(RTNH_LENGTH(len))
#घोषणा RTNH_DATA(rtnh)   ((काष्ठा rtattr*)(((अक्षर*)(rtnh)) + RTNH_LENGTH(0)))

/* RTA_VIA */
काष्ठा rtvia अणु
	__kernel_sa_family_t	rtvia_family;
	__u8			rtvia_addr[0];
पूर्ण;

/* RTM_CACHEINFO */

काष्ठा rta_cacheinfo अणु
	__u32	rta_clntref;
	__u32	rta_lastuse;
	__s32	rta_expires;
	__u32	rta_error;
	__u32	rta_used;

#घोषणा RTNETLINK_HAVE_PEERINFO 1
	__u32	rta_id;
	__u32	rta_ts;
	__u32	rta_tsage;
पूर्ण;

/* RTM_METRICS --- array of काष्ठा rtattr with types of RTAX_* */

क्रमागत अणु
	RTAX_UNSPEC,
#घोषणा RTAX_UNSPEC RTAX_UNSPEC
	RTAX_LOCK,
#घोषणा RTAX_LOCK RTAX_LOCK
	RTAX_MTU,
#घोषणा RTAX_MTU RTAX_MTU
	RTAX_WINDOW,
#घोषणा RTAX_WINDOW RTAX_WINDOW
	RTAX_RTT,
#घोषणा RTAX_RTT RTAX_RTT
	RTAX_RTTVAR,
#घोषणा RTAX_RTTVAR RTAX_RTTVAR
	RTAX_SSTHRESH,
#घोषणा RTAX_SSTHRESH RTAX_SSTHRESH
	RTAX_CWND,
#घोषणा RTAX_CWND RTAX_CWND
	RTAX_ADVMSS,
#घोषणा RTAX_ADVMSS RTAX_ADVMSS
	RTAX_REORDERING,
#घोषणा RTAX_REORDERING RTAX_REORDERING
	RTAX_HOPLIMIT,
#घोषणा RTAX_HOPLIMIT RTAX_HOPLIMIT
	RTAX_INITCWND,
#घोषणा RTAX_INITCWND RTAX_INITCWND
	RTAX_FEATURES,
#घोषणा RTAX_FEATURES RTAX_FEATURES
	RTAX_RTO_MIN,
#घोषणा RTAX_RTO_MIN RTAX_RTO_MIN
	RTAX_INITRWND,
#घोषणा RTAX_INITRWND RTAX_INITRWND
	RTAX_QUICKACK,
#घोषणा RTAX_QUICKACK RTAX_QUICKACK
	RTAX_CC_ALGO,
#घोषणा RTAX_CC_ALGO RTAX_CC_ALGO
	RTAX_FASTOPEN_NO_COOKIE,
#घोषणा RTAX_FASTOPEN_NO_COOKIE RTAX_FASTOPEN_NO_COOKIE
	__RTAX_MAX
पूर्ण;

#घोषणा RTAX_MAX (__RTAX_MAX - 1)

#घोषणा RTAX_FEATURE_ECN	(1 << 0)
#घोषणा RTAX_FEATURE_SACK	(1 << 1)
#घोषणा RTAX_FEATURE_TIMESTAMP	(1 << 2)
#घोषणा RTAX_FEATURE_ALLFRAG	(1 << 3)

#घोषणा RTAX_FEATURE_MASK	(RTAX_FEATURE_ECN | RTAX_FEATURE_SACK | \
				 RTAX_FEATURE_TIMESTAMP | RTAX_FEATURE_ALLFRAG)

काष्ठा rta_session अणु
	__u8	proto;
	__u8	pad1;
	__u16	pad2;

	जोड़ अणु
		काष्ठा अणु
			__u16	sport;
			__u16	dport;
		पूर्ण ports;

		काष्ठा अणु
			__u8	type;
			__u8	code;
			__u16	ident;
		पूर्ण icmpt;

		__u32		spi;
	पूर्ण u;
पूर्ण;

काष्ठा rta_mfc_stats अणु
	__u64	mfcs_packets;
	__u64	mfcs_bytes;
	__u64	mfcs_wrong_अगर;
पूर्ण;

/****
 *		General क्रमm of address family dependent message.
 ****/

काष्ठा rtgenmsg अणु
	अचिन्हित अक्षर		rtgen_family;
पूर्ण;

/*****************************************************************
 *		Link layer specअगरic messages.
 ****/

/* काष्ठा अगरinfomsg
 * passes link level specअगरic inक्रमmation, not dependent
 * on network protocol.
 */

काष्ठा अगरinfomsg अणु
	अचिन्हित अक्षर	अगरi_family;
	अचिन्हित अक्षर	__अगरi_pad;
	अचिन्हित लघु	अगरi_type;		/* ARPHRD_* */
	पूर्णांक		अगरi_index;		/* Link index	*/
	अचिन्हित	अगरi_flags;		/* IFF_* flags	*/
	अचिन्हित	अगरi_change;		/* IFF_* change mask */
पूर्ण;

/********************************************************************
 *		prefix inक्रमmation 
 ****/

काष्ठा prefixmsg अणु
	अचिन्हित अक्षर	prefix_family;
	अचिन्हित अक्षर	prefix_pad1;
	अचिन्हित लघु	prefix_pad2;
	पूर्णांक		prefix_अगरindex;
	अचिन्हित अक्षर	prefix_type;
	अचिन्हित अक्षर	prefix_len;
	अचिन्हित अक्षर	prefix_flags;
	अचिन्हित अक्षर	prefix_pad3;
पूर्ण;

क्रमागत 
अणु
	PREFIX_UNSPEC,
	PREFIX_ADDRESS,
	PREFIX_CACHEINFO,
	__PREFIX_MAX
पूर्ण;

#घोषणा PREFIX_MAX	(__PREFIX_MAX - 1)

काष्ठा prefix_cacheinfo अणु
	__u32	preferred_समय;
	__u32	valid_समय;
पूर्ण;


/*****************************************************************
 *		Traffic control messages.
 ****/

काष्ठा tcmsg अणु
	अचिन्हित अक्षर	tcm_family;
	अचिन्हित अक्षर	tcm__pad1;
	अचिन्हित लघु	tcm__pad2;
	पूर्णांक		tcm_अगरindex;
	__u32		tcm_handle;
	__u32		tcm_parent;
/* tcm_block_index is used instead of tcm_parent
 * in हाल tcm_अगरindex == TCM_IFINDEX_MAGIC_BLOCK
 */
#घोषणा tcm_block_index tcm_parent
	__u32		tcm_info;
पूर्ण;

/* For manipulation of filters in shared block, tcm_अगरindex is set to
 * TCM_IFINDEX_MAGIC_BLOCK, and tcm_parent is aliased to tcm_block_index
 * which is the block index.
 */
#घोषणा TCM_IFINDEX_MAGIC_BLOCK (0xFFFFFFFFU)

क्रमागत अणु
	TCA_UNSPEC,
	TCA_KIND,
	TCA_OPTIONS,
	TCA_STATS,
	TCA_XSTATS,
	TCA_RATE,
	TCA_FCNT,
	TCA_STATS2,
	TCA_STAB,
	TCA_PAD,
	TCA_DUMP_INVISIBLE,
	TCA_CHAIN,
	TCA_HW_OFFLOAD,
	TCA_INGRESS_BLOCK,
	TCA_EGRESS_BLOCK,
	TCA_DUMP_FLAGS,
	__TCA_MAX
पूर्ण;

#घोषणा TCA_MAX (__TCA_MAX - 1)

#घोषणा TCA_DUMP_FLAGS_TERSE (1 << 0) /* Means that in dump user माला_लो only basic
				       * data necessary to identअगरy the objects
				       * (handle, cookie, etc.) and stats.
				       */

#घोषणा TCA_RTA(r)  ((काष्ठा rtattr*)(((अक्षर*)(r)) + NLMSG_ALIGN(माप(काष्ठा tcmsg))))
#घोषणा TCA_PAYLOAD(n) NLMSG_PAYLOAD(n,माप(काष्ठा tcmsg))

/********************************************************************
 *		Neighbor Discovery userland options
 ****/

काष्ठा nduseropपंचांगsg अणु
	अचिन्हित अक्षर	nduseropt_family;
	अचिन्हित अक्षर	nduseropt_pad1;
	अचिन्हित लघु	nduseropt_opts_len;	/* Total length of options */
	पूर्णांक		nduseropt_अगरindex;
	__u8		nduseropt_icmp_type;
	__u8		nduseropt_icmp_code;
	अचिन्हित लघु	nduseropt_pad2;
	अचिन्हित पूर्णांक	nduseropt_pad3;
	/* Followed by one or more ND options */
पूर्ण;

क्रमागत अणु
	NDUSEROPT_UNSPEC,
	NDUSEROPT_SRCADDR,
	__NDUSEROPT_MAX
पूर्ण;

#घोषणा NDUSEROPT_MAX	(__NDUSEROPT_MAX - 1)

#अगर_अघोषित __KERNEL__
/* RTnetlink multicast groups - backwards compatibility क्रम userspace */
#घोषणा RTMGRP_LINK		1
#घोषणा RTMGRP_NOTIFY		2
#घोषणा RTMGRP_NEIGH		4
#घोषणा RTMGRP_TC		8

#घोषणा RTMGRP_IPV4_IFADDR	0x10
#घोषणा RTMGRP_IPV4_MROUTE	0x20
#घोषणा RTMGRP_IPV4_ROUTE	0x40
#घोषणा RTMGRP_IPV4_RULE	0x80

#घोषणा RTMGRP_IPV6_IFADDR	0x100
#घोषणा RTMGRP_IPV6_MROUTE	0x200
#घोषणा RTMGRP_IPV6_ROUTE	0x400
#घोषणा RTMGRP_IPV6_IFINFO	0x800

#घोषणा RTMGRP_DECnet_IFADDR    0x1000
#घोषणा RTMGRP_DECnet_ROUTE     0x4000

#घोषणा RTMGRP_IPV6_PREFIX	0x20000
#पूर्ण_अगर

/* RTnetlink multicast groups */
क्रमागत rtnetlink_groups अणु
	RTNLGRP_NONE,
#घोषणा RTNLGRP_NONE		RTNLGRP_NONE
	RTNLGRP_LINK,
#घोषणा RTNLGRP_LINK		RTNLGRP_LINK
	RTNLGRP_NOTIFY,
#घोषणा RTNLGRP_NOTIFY		RTNLGRP_NOTIFY
	RTNLGRP_NEIGH,
#घोषणा RTNLGRP_NEIGH		RTNLGRP_NEIGH
	RTNLGRP_TC,
#घोषणा RTNLGRP_TC		RTNLGRP_TC
	RTNLGRP_IPV4_IFADDR,
#घोषणा RTNLGRP_IPV4_IFADDR	RTNLGRP_IPV4_IFADDR
	RTNLGRP_IPV4_MROUTE,
#घोषणा	RTNLGRP_IPV4_MROUTE	RTNLGRP_IPV4_MROUTE
	RTNLGRP_IPV4_ROUTE,
#घोषणा RTNLGRP_IPV4_ROUTE	RTNLGRP_IPV4_ROUTE
	RTNLGRP_IPV4_RULE,
#घोषणा RTNLGRP_IPV4_RULE	RTNLGRP_IPV4_RULE
	RTNLGRP_IPV6_IFADDR,
#घोषणा RTNLGRP_IPV6_IFADDR	RTNLGRP_IPV6_IFADDR
	RTNLGRP_IPV6_MROUTE,
#घोषणा RTNLGRP_IPV6_MROUTE	RTNLGRP_IPV6_MROUTE
	RTNLGRP_IPV6_ROUTE,
#घोषणा RTNLGRP_IPV6_ROUTE	RTNLGRP_IPV6_ROUTE
	RTNLGRP_IPV6_IFINFO,
#घोषणा RTNLGRP_IPV6_IFINFO	RTNLGRP_IPV6_IFINFO
	RTNLGRP_DECnet_IFADDR,
#घोषणा RTNLGRP_DECnet_IFADDR	RTNLGRP_DECnet_IFADDR
	RTNLGRP_NOP2,
	RTNLGRP_DECnet_ROUTE,
#घोषणा RTNLGRP_DECnet_ROUTE	RTNLGRP_DECnet_ROUTE
	RTNLGRP_DECnet_RULE,
#घोषणा RTNLGRP_DECnet_RULE	RTNLGRP_DECnet_RULE
	RTNLGRP_NOP4,
	RTNLGRP_IPV6_PREFIX,
#घोषणा RTNLGRP_IPV6_PREFIX	RTNLGRP_IPV6_PREFIX
	RTNLGRP_IPV6_RULE,
#घोषणा RTNLGRP_IPV6_RULE	RTNLGRP_IPV6_RULE
	RTNLGRP_ND_USEROPT,
#घोषणा RTNLGRP_ND_USEROPT	RTNLGRP_ND_USEROPT
	RTNLGRP_PHONET_IFADDR,
#घोषणा RTNLGRP_PHONET_IFADDR	RTNLGRP_PHONET_IFADDR
	RTNLGRP_PHONET_ROUTE,
#घोषणा RTNLGRP_PHONET_ROUTE	RTNLGRP_PHONET_ROUTE
	RTNLGRP_DCB,
#घोषणा RTNLGRP_DCB		RTNLGRP_DCB
	RTNLGRP_IPV4_NETCONF,
#घोषणा RTNLGRP_IPV4_NETCONF	RTNLGRP_IPV4_NETCONF
	RTNLGRP_IPV6_NETCONF,
#घोषणा RTNLGRP_IPV6_NETCONF	RTNLGRP_IPV6_NETCONF
	RTNLGRP_MDB,
#घोषणा RTNLGRP_MDB		RTNLGRP_MDB
	RTNLGRP_MPLS_ROUTE,
#घोषणा RTNLGRP_MPLS_ROUTE	RTNLGRP_MPLS_ROUTE
	RTNLGRP_NSID,
#घोषणा RTNLGRP_NSID		RTNLGRP_NSID
	RTNLGRP_MPLS_NETCONF,
#घोषणा RTNLGRP_MPLS_NETCONF	RTNLGRP_MPLS_NETCONF
	RTNLGRP_IPV4_MROUTE_R,
#घोषणा RTNLGRP_IPV4_MROUTE_R	RTNLGRP_IPV4_MROUTE_R
	RTNLGRP_IPV6_MROUTE_R,
#घोषणा RTNLGRP_IPV6_MROUTE_R	RTNLGRP_IPV6_MROUTE_R
	RTNLGRP_NEXTHOP,
#घोषणा RTNLGRP_NEXTHOP		RTNLGRP_NEXTHOP
	RTNLGRP_BRVLAN,
#घोषणा RTNLGRP_BRVLAN		RTNLGRP_BRVLAN
	__RTNLGRP_MAX
पूर्ण;
#घोषणा RTNLGRP_MAX	(__RTNLGRP_MAX - 1)

/* TC action piece */
काष्ठा tcamsg अणु
	अचिन्हित अक्षर	tca_family;
	अचिन्हित अक्षर	tca__pad1;
	अचिन्हित लघु	tca__pad2;
पूर्ण;

क्रमागत अणु
	TCA_ROOT_UNSPEC,
	TCA_ROOT_TAB,
#घोषणा TCA_ACT_TAB TCA_ROOT_TAB
#घोषणा TCAA_MAX TCA_ROOT_TAB
	TCA_ROOT_FLAGS,
	TCA_ROOT_COUNT,
	TCA_ROOT_TIME_DELTA, /* in msecs */
	__TCA_ROOT_MAX,
#घोषणा	TCA_ROOT_MAX (__TCA_ROOT_MAX - 1)
पूर्ण;

#घोषणा TA_RTA(r)  ((काष्ठा rtattr*)(((अक्षर*)(r)) + NLMSG_ALIGN(माप(काष्ठा tcamsg))))
#घोषणा TA_PAYLOAD(n) NLMSG_PAYLOAD(n,माप(काष्ठा tcamsg))
/* tcamsg flags stored in attribute TCA_ROOT_FLAGS
 *
 * TCA_ACT_FLAG_LARGE_DUMP_ON user->kernel to request क्रम larger than
 * TCA_ACT_MAX_PRIO actions in a dump. All dump responses will contain the
 * number of actions being dumped stored in क्रम user app's consumption in
 * TCA_ROOT_COUNT
 *
 * TCA_ACT_FLAG_TERSE_DUMP user->kernel to request terse (brief) dump that only
 * includes essential action info (kind, index, etc.)
 *
 */
#घोषणा TCA_FLAG_LARGE_DUMP_ON		(1 << 0)
#घोषणा TCA_ACT_FLAG_LARGE_DUMP_ON	TCA_FLAG_LARGE_DUMP_ON
#घोषणा TCA_ACT_FLAG_TERSE_DUMP		(1 << 1)

/* New extended info filters क्रम IFLA_EXT_MASK */
#घोषणा RTEXT_FILTER_VF		(1 << 0)
#घोषणा RTEXT_FILTER_BRVLAN	(1 << 1)
#घोषणा RTEXT_FILTER_BRVLAN_COMPRESSED	(1 << 2)
#घोषणा	RTEXT_FILTER_SKIP_STATS	(1 << 3)
#घोषणा RTEXT_FILTER_MRP	(1 << 4)
#घोषणा RTEXT_FILTER_CFM_CONFIG	(1 << 5)
#घोषणा RTEXT_FILTER_CFM_STATUS	(1 << 6)

/* End of inक्रमmation exported to user level */



#पूर्ण_अगर /* _UAPI__LINUX_RTNETLINK_H */
