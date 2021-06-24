<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_EM_CMP_H
#घोषणा __LINUX_TC_EM_CMP_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

काष्ठा tcf_em_cmp अणु
	__u32		val;
	__u32		mask;
	__u16		off;
	__u8		align:4;
	__u8		flags:4;
	__u8		layer:4;
	__u8		opnd:4;
पूर्ण;

क्रमागत अणु
	TCF_EM_ALIGN_U8  = 1,
	TCF_EM_ALIGN_U16 = 2,
	TCF_EM_ALIGN_U32 = 4
पूर्ण;

#घोषणा TCF_EM_CMP_TRANS	1

#पूर्ण_अगर
