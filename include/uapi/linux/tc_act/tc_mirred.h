<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_MIR_H
#घोषणा __LINUX_TC_MIR_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

#घोषणा TCA_EGRESS_REसूची 1  /* packet redirect to EGRESS*/
#घोषणा TCA_EGRESS_MIRROR 2 /* mirror packet to EGRESS */
#घोषणा TCA_INGRESS_REसूची 3  /* packet redirect to INGRESS*/
#घोषणा TCA_INGRESS_MIRROR 4 /* mirror packet to INGRESS */

काष्ठा tc_mirred अणु
	tc_gen;
	पूर्णांक                     eaction;   /* one of IN/EGRESS_MIRROR/REसूची */
	__u32                   अगरindex;  /* अगरindex of egress port */
पूर्ण;

क्रमागत अणु
	TCA_MIRRED_UNSPEC,
	TCA_MIRRED_TM,
	TCA_MIRRED_PARMS,
	TCA_MIRRED_PAD,
	__TCA_MIRRED_MAX
पूर्ण;
#घोषणा TCA_MIRRED_MAX (__TCA_MIRRED_MAX - 1)

#पूर्ण_अगर
