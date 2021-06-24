<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_ICMPV6_H
#घोषणा _UAPI_LINUX_ICMPV6_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

काष्ठा icmp6hdr अणु

	__u8		icmp6_type;
	__u8		icmp6_code;
	__sum16		icmp6_cksum;


	जोड़ अणु
		__be32			un_data32[1];
		__be16			un_data16[2];
		__u8			un_data8[4];

		काष्ठा icmpv6_echo अणु
			__be16		identअगरier;
			__be16		sequence;
		पूर्ण u_echo;

                काष्ठा icmpv6_nd_advt अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
                        __u32		reserved:5,
                        		override:1,
                        		solicited:1,
                        		router:1,
					reserved2:24;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
                        __u32		router:1,
					solicited:1,
                        		override:1,
                        		reserved:29;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर						
                पूर्ण u_nd_advt;

                काष्ठा icmpv6_nd_ra अणु
			__u8		hop_limit;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
			__u8		reserved:3,
					router_pref:2,
					home_agent:1,
					other:1,
					managed:1;

#या_अगर defined(__BIG_ENDIAN_BITFIELD)
			__u8		managed:1,
					other:1,
					home_agent:1,
					router_pref:2,
					reserved:3;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
			__be16		rt_lअगरeसमय;
                पूर्ण u_nd_ra;

	पूर्ण icmp6_dataun;

#घोषणा icmp6_identअगरier	icmp6_dataun.u_echo.identअगरier
#घोषणा icmp6_sequence		icmp6_dataun.u_echo.sequence
#घोषणा icmp6_poपूर्णांकer		icmp6_dataun.un_data32[0]
#घोषणा icmp6_mtu		icmp6_dataun.un_data32[0]
#घोषणा icmp6_unused		icmp6_dataun.un_data32[0]
#घोषणा icmp6_maxdelay		icmp6_dataun.un_data16[0]
#घोषणा icmp6_datagram_len	icmp6_dataun.un_data8[0]
#घोषणा icmp6_router		icmp6_dataun.u_nd_advt.router
#घोषणा icmp6_solicited		icmp6_dataun.u_nd_advt.solicited
#घोषणा icmp6_override		icmp6_dataun.u_nd_advt.override
#घोषणा icmp6_ndiscreserved	icmp6_dataun.u_nd_advt.reserved
#घोषणा icmp6_hop_limit		icmp6_dataun.u_nd_ra.hop_limit
#घोषणा icmp6_addrconf_managed	icmp6_dataun.u_nd_ra.managed
#घोषणा icmp6_addrconf_other	icmp6_dataun.u_nd_ra.other
#घोषणा icmp6_rt_lअगरeसमय	icmp6_dataun.u_nd_ra.rt_lअगरeसमय
#घोषणा icmp6_router_pref	icmp6_dataun.u_nd_ra.router_pref
पूर्ण;


#घोषणा ICMPV6_ROUTER_PREF_LOW		0x3
#घोषणा ICMPV6_ROUTER_PREF_MEDIUM	0x0
#घोषणा ICMPV6_ROUTER_PREF_HIGH		0x1
#घोषणा ICMPV6_ROUTER_PREF_INVALID	0x2

#घोषणा ICMPV6_DEST_UNREACH		1
#घोषणा ICMPV6_PKT_TOOBIG		2
#घोषणा ICMPV6_TIME_EXCEED		3
#घोषणा ICMPV6_PARAMPROB		4

#घोषणा ICMPV6_ERRMSG_MAX       127

#घोषणा ICMPV6_INFOMSG_MASK		0x80

#घोषणा ICMPV6_ECHO_REQUEST		128
#घोषणा ICMPV6_ECHO_REPLY		129
#घोषणा ICMPV6_MGM_QUERY		130
#घोषणा ICMPV6_MGM_REPORT       	131
#घोषणा ICMPV6_MGM_REDUCTION    	132

#घोषणा ICMPV6_NI_QUERY			139
#घोषणा ICMPV6_NI_REPLY			140

#घोषणा ICMPV6_MLD2_REPORT		143

#घोषणा ICMPV6_DHAAD_REQUEST		144
#घोषणा ICMPV6_DHAAD_REPLY		145
#घोषणा ICMPV6_MOBILE_PREFIX_SOL	146
#घोषणा ICMPV6_MOBILE_PREFIX_ADV	147

#घोषणा ICMPV6_MRDISC_ADV		151

#घोषणा ICMPV6_MSG_MAX          255

/*
 *	Codes क्रम Destination Unreachable
 */
#घोषणा ICMPV6_NOROUTE			0
#घोषणा ICMPV6_ADM_PROHIBITED		1
#घोषणा ICMPV6_NOT_NEIGHBOUR		2
#घोषणा ICMPV6_ADDR_UNREACH		3
#घोषणा ICMPV6_PORT_UNREACH		4
#घोषणा ICMPV6_POLICY_FAIL		5
#घोषणा ICMPV6_REJECT_ROUTE		6

/*
 *	Codes क्रम Time Exceeded
 */
#घोषणा ICMPV6_EXC_HOPLIMIT		0
#घोषणा ICMPV6_EXC_FRAGTIME		1

/*
 *	Codes क्रम Parameter Problem
 */
#घोषणा ICMPV6_HDR_FIELD		0
#घोषणा ICMPV6_UNK_NEXTHDR		1
#घोषणा ICMPV6_UNK_OPTION		2
#घोषणा ICMPV6_HDR_INCOMP		3

/* Codes क्रम EXT_ECHO (PROBE) */
#घोषणा ICMPV6_EXT_ECHO_REQUEST		160
#घोषणा ICMPV6_EXT_ECHO_REPLY		161
/*
 *	स्थिरants क्रम (set|get)sockopt
 */

#घोषणा ICMPV6_FILTER			1

/*
 *	ICMPV6 filter
 */

#घोषणा ICMPV6_FILTER_BLOCK		1
#घोषणा ICMPV6_FILTER_PASS		2
#घोषणा ICMPV6_FILTER_BLOCKOTHERS	3
#घोषणा ICMPV6_FILTER_PASSONLY		4

काष्ठा icmp6_filter अणु
	__u32		data[8];
पूर्ण;

/*
 *	Definitions क्रम MLDv2
 */
#घोषणा MLD2_MODE_IS_INCLUDE	1
#घोषणा MLD2_MODE_IS_EXCLUDE	2
#घोषणा MLD2_CHANGE_TO_INCLUDE	3
#घोषणा MLD2_CHANGE_TO_EXCLUDE	4
#घोषणा MLD2_ALLOW_NEW_SOURCES	5
#घोषणा MLD2_BLOCK_OLD_SOURCES	6

#घोषणा MLD2_ALL_MCR_INIT अणु अणु अणु 0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,0x16 पूर्ण पूर्ण पूर्ण


#पूर्ण_अगर /* _UAPI_LINUX_ICMPV6_H */
