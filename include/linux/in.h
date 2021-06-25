<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions of the Internet Protocol.
 *
 * Version:	@(#)in.h	1.0.1	04/21/93
 *
 * Authors:	Original taken from the GNU Project <netinet/in.h> file.
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _LINUX_IN_H
#घोषणा _LINUX_IN_H


#समावेश <linux/त्रुटिसं.स>
#समावेश <uapi/linux/in.h>

अटल अंतरभूत पूर्णांक proto_ports_offset(पूर्णांक proto)
अणु
	चयन (proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_DCCP:
	हाल IPPROTO_ESP:	/* SPI */
	हाल IPPROTO_SCTP:
	हाल IPPROTO_UDPLITE:
		वापस 0;
	हाल IPPROTO_AH:	/* SPI */
		वापस 4;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत bool ipv4_is_loopback(__be32 addr)
अणु
	वापस (addr & htonl(0xff000000)) == htonl(0x7f000000);
पूर्ण

अटल अंतरभूत bool ipv4_is_multicast(__be32 addr)
अणु
	वापस (addr & htonl(0xf0000000)) == htonl(0xe0000000);
पूर्ण

अटल अंतरभूत bool ipv4_is_local_multicast(__be32 addr)
अणु
	वापस (addr & htonl(0xffffff00)) == htonl(0xe0000000);
पूर्ण

अटल अंतरभूत bool ipv4_is_lbcast(__be32 addr)
अणु
	/* limited broadcast */
	वापस addr == htonl(INADDR_BROADCAST);
पूर्ण

अटल अंतरभूत bool ipv4_is_all_snoopers(__be32 addr)
अणु
	वापस addr == htonl(INADDR_ALLSNOOPERS_GROUP);
पूर्ण

अटल अंतरभूत bool ipv4_is_zeronet(__be32 addr)
अणु
	वापस (addr == 0);
पूर्ण

/* Special-Use IPv4 Addresses (RFC3330) */

अटल अंतरभूत bool ipv4_is_निजी_10(__be32 addr)
अणु
	वापस (addr & htonl(0xff000000)) == htonl(0x0a000000);
पूर्ण

अटल अंतरभूत bool ipv4_is_निजी_172(__be32 addr)
अणु
	वापस (addr & htonl(0xfff00000)) == htonl(0xac100000);
पूर्ण

अटल अंतरभूत bool ipv4_is_निजी_192(__be32 addr)
अणु
	वापस (addr & htonl(0xffff0000)) == htonl(0xc0a80000);
पूर्ण

अटल अंतरभूत bool ipv4_is_linklocal_169(__be32 addr)
अणु
	वापस (addr & htonl(0xffff0000)) == htonl(0xa9fe0000);
पूर्ण

अटल अंतरभूत bool ipv4_is_anycast_6to4(__be32 addr)
अणु
	वापस (addr & htonl(0xffffff00)) == htonl(0xc0586300);
पूर्ण

अटल अंतरभूत bool ipv4_is_test_192(__be32 addr)
अणु
	वापस (addr & htonl(0xffffff00)) == htonl(0xc0000200);
पूर्ण

अटल अंतरभूत bool ipv4_is_test_198(__be32 addr)
अणु
	वापस (addr & htonl(0xfffe0000)) == htonl(0xc6120000);
पूर्ण
#पूर्ण_अगर	/* _LINUX_IN_H */
