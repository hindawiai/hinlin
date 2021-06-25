<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Types and definitions क्रम AF_INET6 
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 *
 *	Sources:
 *	IPv6 Program Interfaces क्रम BSD Systems
 *      <draft-ietf-ipngwg-bsd-api-05.txt>
 *
 *	Advanced Sockets API क्रम IPv6
 *	<draft-stevens-advanced-api-00.txt>
 */
#अगर_अघोषित _LINUX_IN6_H
#घोषणा _LINUX_IN6_H

#समावेश <uapi/linux/in6.h>

/* IPv6 Wildcard Address (::) and Loopback Address (::1) defined in RFC2553
 * NOTE: Be aware the IN6ADDR_* स्थिरants and in6addr_* बाह्यals are defined
 * in network byte order, not in host byte order as are the IPv4 equivalents
 */
बाह्य स्थिर काष्ठा in6_addr in6addr_any;
#घोषणा IN6ADDR_ANY_INIT अणु अणु अणु 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 पूर्ण पूर्ण पूर्ण
बाह्य स्थिर काष्ठा in6_addr in6addr_loopback;
#घोषणा IN6ADDR_LOOPBACK_INIT अणु अणु अणु 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 पूर्ण पूर्ण पूर्ण
बाह्य स्थिर काष्ठा in6_addr in6addr_linklocal_allnodes;
#घोषणा IN6ADDR_LINKLOCAL_ALLNODES_INIT	\
		अणु अणु अणु 0xff,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1 पूर्ण पूर्ण पूर्ण
बाह्य स्थिर काष्ठा in6_addr in6addr_linklocal_allrouters;
#घोषणा IN6ADDR_LINKLOCAL_ALLROUTERS_INIT \
		अणु अणु अणु 0xff,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2 पूर्ण पूर्ण पूर्ण
बाह्य स्थिर काष्ठा in6_addr in6addr_पूर्णांकerfacelocal_allnodes;
#घोषणा IN6ADDR_INTERFACELOCAL_ALLNODES_INIT \
		अणु अणु अणु 0xff,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 पूर्ण पूर्ण पूर्ण
बाह्य स्थिर काष्ठा in6_addr in6addr_पूर्णांकerfacelocal_allrouters;
#घोषणा IN6ADDR_INTERFACELOCAL_ALLROUTERS_INIT \
		अणु अणु अणु 0xff,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2 पूर्ण पूर्ण पूर्ण
बाह्य स्थिर काष्ठा in6_addr in6addr_sitelocal_allrouters;
#घोषणा IN6ADDR_SITELOCAL_ALLROUTERS_INIT \
		अणु अणु अणु 0xff,5,0,0,0,0,0,0,0,0,0,0,0,0,0,2 पूर्ण पूर्ण पूर्ण
#पूर्ण_अगर
