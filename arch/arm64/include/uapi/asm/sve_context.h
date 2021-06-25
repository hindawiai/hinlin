<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (C) 2017-2018 ARM Limited */

/*
 * For use by other UAPI headers only.
 * Do not make direct use of header or its definitions.
 */

#अगर_अघोषित _UAPI__ASM_SVE_CONTEXT_H
#घोषणा _UAPI__ASM_SVE_CONTEXT_H

#समावेश <linux/types.h>

#घोषणा __SVE_VQ_BYTES		16	/* number of bytes per quadword */

#घोषणा __SVE_VQ_MIN		1
#घोषणा __SVE_VQ_MAX		512

#घोषणा __SVE_VL_MIN		(__SVE_VQ_MIN * __SVE_VQ_BYTES)
#घोषणा __SVE_VL_MAX		(__SVE_VQ_MAX * __SVE_VQ_BYTES)

#घोषणा __SVE_NUM_ZREGS		32
#घोषणा __SVE_NUM_PREGS		16

#घोषणा __sve_vl_valid(vl)			\
	((vl) % __SVE_VQ_BYTES == 0 &&		\
	 (vl) >= __SVE_VL_MIN &&		\
	 (vl) <= __SVE_VL_MAX)

#घोषणा __sve_vq_from_vl(vl)	((vl) / __SVE_VQ_BYTES)
#घोषणा __sve_vl_from_vq(vq)	((vq) * __SVE_VQ_BYTES)

#घोषणा __SVE_ZREG_SIZE(vq)	((__u32)(vq) * __SVE_VQ_BYTES)
#घोषणा __SVE_PREG_SIZE(vq)	((__u32)(vq) * (__SVE_VQ_BYTES / 8))
#घोषणा __SVE_FFR_SIZE(vq)	__SVE_PREG_SIZE(vq)

#घोषणा __SVE_ZREGS_OFFSET	0
#घोषणा __SVE_ZREG_OFFSET(vq, n) \
	(__SVE_ZREGS_OFFSET + __SVE_ZREG_SIZE(vq) * (n))
#घोषणा __SVE_ZREGS_SIZE(vq) \
	(__SVE_ZREG_OFFSET(vq, __SVE_NUM_ZREGS) - __SVE_ZREGS_OFFSET)

#घोषणा __SVE_PREGS_OFFSET(vq) \
	(__SVE_ZREGS_OFFSET + __SVE_ZREGS_SIZE(vq))
#घोषणा __SVE_PREG_OFFSET(vq, n) \
	(__SVE_PREGS_OFFSET(vq) + __SVE_PREG_SIZE(vq) * (n))
#घोषणा __SVE_PREGS_SIZE(vq) \
	(__SVE_PREG_OFFSET(vq, __SVE_NUM_PREGS) - __SVE_PREGS_OFFSET(vq))

#घोषणा __SVE_FFR_OFFSET(vq) \
	(__SVE_PREGS_OFFSET(vq) + __SVE_PREGS_SIZE(vq))

#पूर्ण_अगर /* ! _UAPI__ASM_SVE_CONTEXT_H */
