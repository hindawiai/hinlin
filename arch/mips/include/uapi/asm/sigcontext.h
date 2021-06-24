<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1999 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_SIGCONTEXT_H
#घोषणा _UAPI_ASM_SIGCONTEXT_H

#समावेश <linux/types.h>
#समावेश <यंत्र/sgidefs.h>

/* scalar FP context was used */
#घोषणा USED_FP			(1 << 0)

/* the value of Status.FR when context was saved */
#घोषणा USED_FR1		(1 << 1)

/* FR=1, but with odd singles in bits 63:32 of preceding even द्विगुन */
#घोषणा USED_HYBRID_FPRS	(1 << 2)

/* extended context was used, see काष्ठा extcontext क्रम details */
#घोषणा USED_EXTCONTEXT		(1 << 3)

#अगर _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * Keep this काष्ठा definition in sync with the sigcontext fragment
 * in arch/mips/kernel/यंत्र-offsets.c
 */
काष्ठा sigcontext अणु
	अचिन्हित पूर्णांक		sc_regmask;	/* Unused */
	अचिन्हित पूर्णांक		sc_status;	/* Unused */
	अचिन्हित दीर्घ दीर्घ	sc_pc;
	अचिन्हित दीर्घ दीर्घ	sc_regs[32];
	अचिन्हित दीर्घ दीर्घ	sc_fpregs[32];
	अचिन्हित पूर्णांक		sc_acx;		/* Was sc_ownedfp */
	अचिन्हित पूर्णांक		sc_fpc_csr;
	अचिन्हित पूर्णांक		sc_fpc_eir;	/* Unused */
	अचिन्हित पूर्णांक		sc_used_math;
	अचिन्हित पूर्णांक		sc_dsp;		/* dsp status, was sc_ssflags */
	अचिन्हित दीर्घ दीर्घ	sc_mdhi;
	अचिन्हित दीर्घ दीर्घ	sc_mdlo;
	अचिन्हित दीर्घ		sc_hi1;		/* Was sc_cause */
	अचिन्हित दीर्घ		sc_lo1;		/* Was sc_badvaddr */
	अचिन्हित दीर्घ		sc_hi2;		/* Was sc_sigset[4] */
	अचिन्हित दीर्घ		sc_lo2;
	अचिन्हित दीर्घ		sc_hi3;
	अचिन्हित दीर्घ		sc_lo3;
पूर्ण;

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#समावेश <linux/posix_types.h>
/*
 * Keep this काष्ठा definition in sync with the sigcontext fragment
 * in arch/mips/kernel/यंत्र-offsets.c
 *
 * Warning: this काष्ठाure illdefined with sc_badvaddr being just an अचिन्हित
 * पूर्णांक so it was changed to अचिन्हित दीर्घ in 2.6.0-test1.  This may अवरोध
 * binary compatibility - no prisoners.
 * DSP ASE in 2.6.12-rc4.  Turn sc_mdhi and sc_mdlo पूर्णांकo an array of four
 * entries, add sc_dsp and sc_reserved क्रम padding.  No prisoners.
 */
काष्ठा sigcontext अणु
	__u64	sc_regs[32];
	__u64	sc_fpregs[32];
	__u64	sc_mdhi;
	__u64	sc_hi1;
	__u64	sc_hi2;
	__u64	sc_hi3;
	__u64	sc_mdlo;
	__u64	sc_lo1;
	__u64	sc_lo2;
	__u64	sc_lo3;
	__u64	sc_pc;
	__u32	sc_fpc_csr;
	__u32	sc_used_math;
	__u32	sc_dsp;
	__u32	sc_reserved;
पूर्ण;


#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#पूर्ण_अगर /* _UAPI_ASM_SIGCONTEXT_H */
