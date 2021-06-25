<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 */
#अगर_अघोषित _LINUX_IPV6_ROUTE_H
#घोषणा _LINUX_IPV6_ROUTE_H

#समावेश <uapi/linux/ipv6_route.h>

#घोषणा IPV6_EXTRACT_PREF(flag)	(((flag) & RTF_PREF_MASK) >> 27)
#घोषणा IPV6_DECODE_PREF(pref)	((pref) ^ 2)	/* 1:low,2:med,3:high */
#पूर्ण_अगर
