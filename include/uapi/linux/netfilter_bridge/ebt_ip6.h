<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  ebt_ip6
 *
 *	Authors:
 * Kuo-Lang Tseng <kuo-lang.tseng@पूर्णांकel.com>
 * Manohar Castelino <manohar.r.castelino@पूर्णांकel.com>
 *
 *  Jan 11, 2008
 *
 */

#अगर_अघोषित __LINUX_BRIDGE_EBT_IP6_H
#घोषणा __LINUX_BRIDGE_EBT_IP6_H

#समावेश <linux/types.h>
#समावेश <linux/in6.h>

#घोषणा EBT_IP6_SOURCE 0x01
#घोषणा EBT_IP6_DEST 0x02
#घोषणा EBT_IP6_TCLASS 0x04
#घोषणा EBT_IP6_PROTO 0x08
#घोषणा EBT_IP6_SPORT 0x10
#घोषणा EBT_IP6_DPORT 0x20
#घोषणा EBT_IP6_ICMP6 0x40

#घोषणा EBT_IP6_MASK (EBT_IP6_SOURCE | EBT_IP6_DEST | EBT_IP6_TCLASS |\
		      EBT_IP6_PROTO | EBT_IP6_SPORT | EBT_IP6_DPORT | \
		      EBT_IP6_ICMP6)
#घोषणा EBT_IP6_MATCH "ip6"

/* the same values are used क्रम the invflags */
काष्ठा ebt_ip6_info अणु
	काष्ठा in6_addr saddr;
	काष्ठा in6_addr daddr;
	काष्ठा in6_addr smsk;
	काष्ठा in6_addr dmsk;
	__u8  tclass;
	__u8  protocol;
	__u8  biपंचांगask;
	__u8  invflags;
	जोड़ अणु
		__u16 sport[2];
		__u8 icmpv6_type[2];
	पूर्ण;
	जोड़ अणु
		__u16 dport[2];
		__u8 icmpv6_code[2];
	पूर्ण;
पूर्ण;

#पूर्ण_अगर
