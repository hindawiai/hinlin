<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_NAT_H
#घोषणा __LINUX_TC_NAT_H

#समावेश <linux/pkt_cls.h>
#समावेश <linux/types.h>

क्रमागत अणु
	TCA_NAT_UNSPEC,
	TCA_NAT_PARMS,
	TCA_NAT_TM,
	TCA_NAT_PAD,
	__TCA_NAT_MAX
पूर्ण;
#घोषणा TCA_NAT_MAX (__TCA_NAT_MAX - 1)

#घोषणा TCA_NAT_FLAG_EGRESS 1

काष्ठा tc_nat अणु
	tc_gen;
	__be32 old_addr;
	__be32 new_addr;
	__be32 mask;
	__u32 flags;
पूर्ण;

#पूर्ण_अगर
