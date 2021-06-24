<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_ARP_H
#घोषणा __LINUX_BRIDGE_EBT_ARP_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#घोषणा EBT_ARP_OPCODE 0x01
#घोषणा EBT_ARP_HTYPE 0x02
#घोषणा EBT_ARP_PTYPE 0x04
#घोषणा EBT_ARP_SRC_IP 0x08
#घोषणा EBT_ARP_DST_IP 0x10
#घोषणा EBT_ARP_SRC_MAC 0x20
#घोषणा EBT_ARP_DST_MAC 0x40
#घोषणा EBT_ARP_GRAT 0x80
#घोषणा EBT_ARP_MASK (EBT_ARP_OPCODE | EBT_ARP_HTYPE | EBT_ARP_PTYPE | \
   EBT_ARP_SRC_IP | EBT_ARP_DST_IP | EBT_ARP_SRC_MAC | EBT_ARP_DST_MAC | \
   EBT_ARP_GRAT)
#घोषणा EBT_ARP_MATCH "arp"

काष्ठा ebt_arp_info
अणु
	__be16 htype;
	__be16 ptype;
	__be16 opcode;
	__be32 saddr;
	__be32 smsk;
	__be32 daddr;
	__be32 dmsk;
	अचिन्हित अक्षर smaddr[ETH_ALEN];
	अचिन्हित अक्षर smmsk[ETH_ALEN];
	अचिन्हित अक्षर dmaddr[ETH_ALEN];
	अचिन्हित अक्षर dmmsk[ETH_ALEN];
	__u8  biपंचांगask;
	__u8  invflags;
पूर्ण;

#पूर्ण_अगर
