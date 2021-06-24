<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *      modअगरy it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_IPV6_ROUTE_H
#घोषणा _UAPI_LINUX_IPV6_ROUTE_H

#समावेश <linux/types.h>
#समावेश <linux/in6.h>			/* For काष्ठा in6_addr. */

#घोषणा RTF_DEFAULT	0x00010000	/* शेष - learned via ND	*/
#घोषणा RTF_ALLONLINK	0x00020000	/* (deprecated and will be हटाओd)
					   fallback, no routers on link */
#घोषणा RTF_ADDRCONF	0x00040000	/* addrconf route - RA		*/
#घोषणा RTF_PREFIX_RT	0x00080000	/* A prefix only route - RA	*/
#घोषणा RTF_ANYCAST	0x00100000	/* Anycast			*/

#घोषणा RTF_NONEXTHOP	0x00200000	/* route with no nexthop	*/
#घोषणा RTF_EXPIRES	0x00400000

#घोषणा RTF_ROUTEINFO	0x00800000	/* route inक्रमmation - RA	*/

#घोषणा RTF_CACHE	0x01000000	/* पढ़ो-only: can not be set by user */
#घोषणा RTF_FLOW	0x02000000	/* flow signअगरicant route	*/
#घोषणा RTF_POLICY	0x04000000	/* policy route			*/

#घोषणा RTF_PREF(pref)	((pref) << 27)
#घोषणा RTF_PREF_MASK	0x18000000

#घोषणा RTF_PCPU	0x40000000	/* पढ़ो-only: can not be set by user */
#घोषणा RTF_LOCAL	0x80000000


काष्ठा in6_rपंचांगsg अणु
	काष्ठा in6_addr		rपंचांगsg_dst;
	काष्ठा in6_addr		rपंचांगsg_src;
	काष्ठा in6_addr		rपंचांगsg_gateway;
	__u32			rपंचांगsg_type;
	__u16			rपंचांगsg_dst_len;
	__u16			rपंचांगsg_src_len;
	__u32			rपंचांगsg_metric;
	अचिन्हित दीर्घ		rपंचांगsg_info;
        __u32			rपंचांगsg_flags;
	पूर्णांक			rपंचांगsg_अगरindex;
पूर्ण;

#घोषणा RTMSG_NEWDEVICE		0x11
#घोषणा RTMSG_DELDEVICE		0x12
#घोषणा RTMSG_NEWROUTE		0x21
#घोषणा RTMSG_DELROUTE		0x22

#घोषणा IP6_RT_PRIO_USER	1024
#घोषणा IP6_RT_PRIO_ADDRCONF	256

#पूर्ण_अगर /* _UAPI_LINUX_IPV6_ROUTE_H */
