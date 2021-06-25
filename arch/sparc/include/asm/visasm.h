<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_VISASM_H
#घोषणा _SPARC64_VISASM_H

/* visयंत्र.h:  FPU saving macros क्रम VIS routines
 *
 * Copyright (C) 1998 Jakub Jelinek (jj@ultra.linux.cz)
 */

#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/ptrace.h>

/* Clobbers %o5, %g1, %g2, %g3, %g7, %icc, %xcc */

#घोषणा VISEntry					\
	rd		%fprs, %o5;			\
	andcc		%o5, (FPRS_FEF|FPRS_DU), %g0;	\
	be,pt		%icc, 297f;			\
	 sethi		%hi(297f), %g7;			\
	sethi		%hi(VISenter), %g1;		\
	jmpl		%g1 + %lo(VISenter), %g0;	\
	 or		%g7, %lo(297f), %g7;		\
297:	wr		%g0, FPRS_FEF, %fprs;		\

#घोषणा VISExit						\
	wr		%g0, 0, %fprs;

/* Clobbers %o5, %g1, %g2, %g3, %g7, %icc, %xcc.
 * Must preserve %o5 between VISEntryHalf and VISExitHalf */

#घोषणा VISEntryHalf					\
	VISEntry

#घोषणा VISExitHalf					\
	VISExit

#घोषणा VISEntryHalfFast(fail_label)			\
	rd		%fprs, %o5;			\
	andcc		%o5, FPRS_FEF, %g0;		\
	be,pt		%icc, 297f;			\
	 nop;						\
	ba,a,pt		%xcc, fail_label;		\
297:	wr		%o5, FPRS_FEF, %fprs;

#घोषणा VISExitHalfFast					\
	wr		%o5, 0, %fprs;

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत व्योम save_and_clear_fpu(व्योम) अणु
	__यंत्र__ __अस्थिर__ (
"		rd %%fprs, %%o5\n"
"		andcc %%o5, %0, %%g0\n"
"		be,pt %%icc, 299f\n"
"		 sethi %%hi(298f), %%g7\n"
"		sethi %%hi(VISenter), %%g1\n"
"		jmpl %%g1 + %%lo(VISenter), %%g0\n"
"		 or %%g7, %%lo(298f), %%g7\n"
"	298:	wr %%g0, 0, %%fprs\n"
"	299:\n"
"		" : : "i" (FPRS_FEF|FPRS_DU) :
		"o5", "g1", "g2", "g3", "g7", "cc");
पूर्ण

पूर्णांक vis_emul(काष्ठा pt_regs *, अचिन्हित पूर्णांक);
#पूर्ण_अगर

#पूर्ण_अगर /* _SPARC64_ASI_H */
