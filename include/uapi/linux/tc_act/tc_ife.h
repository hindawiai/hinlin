<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __UAPI_TC_IFE_H
#घोषणा __UAPI_TC_IFE_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/अगरe.h>

/* Flag bits क्रम now just encoding/decoding; mutually exclusive */
#घोषणा IFE_ENCODE 1
#घोषणा IFE_DECODE 0

काष्ठा tc_अगरe अणु
	tc_gen;
	__u16 flags;
पूर्ण;

/*XXX: We need to encode the total number of bytes consumed */
क्रमागत अणु
	TCA_IFE_UNSPEC,
	TCA_IFE_PARMS,
	TCA_IFE_TM,
	TCA_IFE_DMAC,
	TCA_IFE_SMAC,
	TCA_IFE_TYPE,
	TCA_IFE_METALST,
	TCA_IFE_PAD,
	__TCA_IFE_MAX
पूर्ण;
#घोषणा TCA_IFE_MAX (__TCA_IFE_MAX - 1)

#पूर्ण_अगर
