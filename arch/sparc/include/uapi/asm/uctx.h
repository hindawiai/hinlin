<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * uctx.h: Sparc64 अणुset,getपूर्णcontext() रेजिस्टर state layouts.
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित __SPARC64_UCTX_H
#घोषणा __SPARC64_UCTX_H

#घोषणा MC_TSTATE	0
#घोषणा MC_PC		1
#घोषणा MC_NPC		2
#घोषणा MC_Y		3
#घोषणा MC_G1		4
#घोषणा MC_G2		5
#घोषणा MC_G3		6
#घोषणा MC_G4		7
#घोषणा MC_G5		8
#घोषणा MC_G6		9
#घोषणा MC_G7		10
#घोषणा MC_O0		11
#घोषणा MC_O1		12
#घोषणा MC_O2		13
#घोषणा MC_O3		14
#घोषणा MC_O4		15
#घोषणा MC_O5		16
#घोषणा MC_O6		17
#घोषणा MC_O7		18
#घोषणा MC_NGREG	19

प्रकार अचिन्हित दीर्घ mc_greg_t;
प्रकार mc_greg_t mc_gregset_t[MC_NGREG];

#घोषणा MC_MAXFPQ	16
काष्ठा mc_fq अणु
	अचिन्हित दीर्घ	*mcfq_addr;
	अचिन्हित पूर्णांक	mcfq_insn;
पूर्ण;

काष्ठा mc_fpu अणु
	जोड़ अणु
		अचिन्हित पूर्णांक	sregs[32];
		अचिन्हित दीर्घ	dregs[32];
		दीर्घ द्विगुन	qregs[16];
	पूर्ण mcfpu_fregs;
	अचिन्हित दीर्घ	mcfpu_fsr;
	अचिन्हित दीर्घ	mcfpu_fprs;
	अचिन्हित दीर्घ	mcfpu_gsr;
	काष्ठा mc_fq	*mcfpu_fq;
	अचिन्हित अक्षर	mcfpu_qcnt;
	अचिन्हित अक्षर	mcfpu_qentsz;
	अचिन्हित अक्षर	mcfpu_enab;
पूर्ण;
प्रकार काष्ठा mc_fpu mc_fpu_t;

प्रकार काष्ठा अणु
	mc_gregset_t	mc_gregs;
	mc_greg_t	mc_fp;
	mc_greg_t	mc_i7;
	mc_fpu_t	mc_fpregs;
पूर्ण mcontext_t;

काष्ठा ucontext अणु
	काष्ठा ucontext		*uc_link;
	अचिन्हित दीर्घ		uc_flags;
	sigset_t		uc_sigmask;
	mcontext_t		uc_mcontext;
पूर्ण;
प्रकार काष्ठा ucontext ucontext_t;

#पूर्ण_अगर /* __SPARC64_UCTX_H */
