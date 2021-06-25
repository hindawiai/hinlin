<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_VLAN_H
#घोषणा __LINUX_BRIDGE_EBT_VLAN_H

#समावेश <linux/types.h>

#घोषणा EBT_VLAN_ID	0x01
#घोषणा EBT_VLAN_PRIO	0x02
#घोषणा EBT_VLAN_ENCAP	0x04
#घोषणा EBT_VLAN_MASK (EBT_VLAN_ID | EBT_VLAN_PRIO | EBT_VLAN_ENCAP)
#घोषणा EBT_VLAN_MATCH "vlan"

काष्ठा ebt_vlan_info अणु
	__u16 id;		/* VLAN ID अणु1-4095पूर्ण */
	__u8 prio;		/* VLAN User Priority अणु0-7पूर्ण */
	__be16 encap;		/* VLAN Encapsulated frame code अणु0-65535पूर्ण */
	__u8 biपंचांगask;		/* Args biपंचांगask bit 1=1 - ID arg,
				   bit 2=1 User-Priority arg, bit 3=1 encap*/
	__u8 invflags;		/* Inverse biपंचांगask  bit 1=1 - inversed ID arg, 
				   bit 2=1 - inversed Pirority arg */
पूर्ण;

#पूर्ण_अगर
