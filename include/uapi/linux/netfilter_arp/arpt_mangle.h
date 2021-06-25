<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ARPT_MANGLE_H
#घोषणा _ARPT_MANGLE_H
#समावेश <linux/netfilter_arp/arp_tables.h>

#घोषणा ARPT_MANGLE_ADDR_LEN_MAX माप(काष्ठा in_addr)
काष्ठा arpt_mangle
अणु
	अक्षर src_devaddr[ARPT_DEV_ADDR_LEN_MAX];
	अक्षर tgt_devaddr[ARPT_DEV_ADDR_LEN_MAX];
	जोड़ अणु
		काष्ठा in_addr src_ip;
	पूर्ण u_s;
	जोड़ अणु
		काष्ठा in_addr tgt_ip;
	पूर्ण u_t;
	__u8 flags;
	पूर्णांक target;
पूर्ण;

#घोषणा ARPT_MANGLE_SDEV 0x01
#घोषणा ARPT_MANGLE_TDEV 0x02
#घोषणा ARPT_MANGLE_SIP 0x04
#घोषणा ARPT_MANGLE_TIP 0x08
#घोषणा ARPT_MANGLE_MASK 0x0f

#पूर्ण_अगर /* _ARPT_MANGLE_H */
