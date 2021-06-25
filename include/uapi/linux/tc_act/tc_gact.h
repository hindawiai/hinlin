<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_GACT_H
#घोषणा __LINUX_TC_GACT_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

काष्ठा tc_gact अणु
	tc_gen;

पूर्ण;

काष्ठा tc_gact_p अणु
#घोषणा PGACT_NONE              0
#घोषणा PGACT_NETRAND           1
#घोषणा PGACT_DETERM            2
#घोषणा MAX_RAND                (PGACT_DETERM + 1 )
	__u16                 ptype;
	__u16                 pval;
	पूर्णांक                   paction;
पूर्ण;
 
क्रमागत अणु
	TCA_GACT_UNSPEC,
	TCA_GACT_TM,
	TCA_GACT_PARMS,
	TCA_GACT_PROB,
	TCA_GACT_PAD,
	__TCA_GACT_MAX
पूर्ण;
#घोषणा TCA_GACT_MAX (__TCA_GACT_MAX - 1)
 
#पूर्ण_अगर
