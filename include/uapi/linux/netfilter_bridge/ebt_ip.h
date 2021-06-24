<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  ebt_ip
 *
 *	Authors:
 *	Bart De Schuymer <bart.de.schuymer@panकरोra.be>
 *
 *  April, 2002
 *
 *  Changes:
 *    added ip-sport and ip-dport
 *    Innominate Security Technologies AG <mhopf@innominate.com>
 *    September, 2002
 */

#अगर_अघोषित __LINUX_BRIDGE_EBT_IP_H
#घोषणा __LINUX_BRIDGE_EBT_IP_H

#समावेश <linux/types.h>

#घोषणा EBT_IP_SOURCE 0x01
#घोषणा EBT_IP_DEST 0x02
#घोषणा EBT_IP_TOS 0x04
#घोषणा EBT_IP_PROTO 0x08
#घोषणा EBT_IP_SPORT 0x10
#घोषणा EBT_IP_DPORT 0x20
#घोषणा EBT_IP_ICMP 0x40
#घोषणा EBT_IP_IGMP 0x80
#घोषणा EBT_IP_MASK (EBT_IP_SOURCE | EBT_IP_DEST | EBT_IP_TOS | EBT_IP_PROTO |\
		     EBT_IP_SPORT | EBT_IP_DPORT | EBT_IP_ICMP | EBT_IP_IGMP)
#घोषणा EBT_IP_MATCH "ip"

/* the same values are used क्रम the invflags */
काष्ठा ebt_ip_info अणु
	__be32 saddr;
	__be32 daddr;
	__be32 smsk;
	__be32 dmsk;
	__u8  tos;
	__u8  protocol;
	__u8  biपंचांगask;
	__u8  invflags;
	जोड़ अणु
		__u16 sport[2];
		__u8 icmp_type[2];
		__u8 igmp_type[2];
	पूर्ण;
	जोड़ अणु
		__u16 dport[2];
		__u8 icmp_code[2];
	पूर्ण;
पूर्ण;

#पूर्ण_अगर
