<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/arch/sh/kernel/cpu/sh4/sh4_fpu.h
 *
 * Copyright (C) 2006 STMicroelectronics Limited
 * Author: Carl Shaw <carl.shaw@st.com>
 *
 * Definitions क्रम SH4 FPU operations
 */

#अगर_अघोषित __CPU_SH4_FPU_H
#घोषणा __CPU_SH4_FPU_H

#घोषणा FPSCR_ENABLE_MASK	0x00000f80UL

#घोषणा FPSCR_FMOV_DOUBLE	(1<<1)

#घोषणा FPSCR_CAUSE_INEXACT	(1<<12)
#घोषणा FPSCR_CAUSE_UNDERFLOW	(1<<13)
#घोषणा FPSCR_CAUSE_OVERFLOW	(1<<14)
#घोषणा FPSCR_CAUSE_DIVZERO	(1<<15)
#घोषणा FPSCR_CAUSE_INVALID	(1<<16)
#घोषणा FPSCR_CAUSE_ERROR 	(1<<17)

#घोषणा FPSCR_DBL_PRECISION	(1<<19)
#घोषणा FPSCR_ROUNDING_MODE(x)	((x >> 20) & 3)
#घोषणा FPSCR_RM_NEAREST	(0)
#घोषणा FPSCR_RM_ZERO		(1)

#पूर्ण_अगर
