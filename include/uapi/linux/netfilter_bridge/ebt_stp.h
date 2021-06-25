<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_STP_H
#घोषणा __LINUX_BRIDGE_EBT_STP_H

#समावेश <linux/types.h>

#घोषणा EBT_STP_TYPE		0x0001

#घोषणा EBT_STP_FLAGS		0x0002
#घोषणा EBT_STP_ROOTPRIO	0x0004
#घोषणा EBT_STP_ROOTADDR	0x0008
#घोषणा EBT_STP_ROOTCOST	0x0010
#घोषणा EBT_STP_SENDERPRIO	0x0020
#घोषणा EBT_STP_SENDERADDR	0x0040
#घोषणा EBT_STP_PORT		0x0080
#घोषणा EBT_STP_MSGAGE		0x0100
#घोषणा EBT_STP_MAXAGE		0x0200
#घोषणा EBT_STP_HELLOTIME	0x0400
#घोषणा EBT_STP_FWDD		0x0800

#घोषणा EBT_STP_MASK		0x0fff
#घोषणा EBT_STP_CONFIG_MASK	0x0ffe

#घोषणा EBT_STP_MATCH "stp"

काष्ठा ebt_stp_config_info अणु
	__u8 flags;
	__u16 root_priol, root_priou;
	अक्षर root_addr[6], root_addrmsk[6];
	__u32 root_costl, root_costu;
	__u16 sender_priol, sender_priou;
	अक्षर sender_addr[6], sender_addrmsk[6];
	__u16 portl, portu;
	__u16 msg_agel, msg_ageu;
	__u16 max_agel, max_ageu;
	__u16 hello_समयl, hello_समयu;
	__u16 क्रमward_delayl, क्रमward_delayu;
पूर्ण;

काष्ठा ebt_stp_info अणु
	__u8 type;
	काष्ठा ebt_stp_config_info config;
	__u16 biपंचांगask;
	__u16 invflags;
पूर्ण;

#पूर्ण_अगर
