<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 1998-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2003 Intel Co
 *	Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 *	Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *	Arun Sharma <arun.sharma@पूर्णांकel.com>
 *
 * 12/07/98	S. Eranian	added pt_regs & चयन_stack
 * 12/21/98	D. Mosberger	updated to match latest code
 *  6/17/99	D. Mosberger	added second unat member to "struct switch_stack"
 *
 */
#अगर_अघोषित _UAPI_ASM_IA64_PTRACE_H
#घोषणा _UAPI_ASM_IA64_PTRACE_H

/*
 * When a user process is blocked, its state looks as follows:
 *
 *            +----------------------+	-------	IA64_STK_OFFSET
 *     	      |			     |	 ^
 *            | काष्ठा pt_regs       |	 |
 *	      |			     |	 |
 *            +----------------------+	 |
 *	      |			     |	 |
 *     	      |	   memory stack	     |	 |
 *	      |	(growing करोwnwards)  |	 |
 *	      //.....................//	 |
 *					 |
 *	      //.....................//	 |
 *	      |			     |	 |
 *            +----------------------+	 |
 *            | काष्ठा चयन_stack  |	 |
 *	      |			     |	 |
 *	      +----------------------+	 |
 *	      |			     |	 |
 *	      //.....................//	 |
 *					 |
 *	      //.....................//	 |
 *	      |			     |	 |
 *	      |	 रेजिस्टर stack	     |	 |
 *	      |	(growing upwards)    |	 |
 *            |			     |	 |
 *	      +----------------------+	 |  ---	IA64_RBS_OFFSET
 *            |  काष्ठा thपढ़ो_info  |	 |  ^
 *	      +----------------------+	 |  |
 *	      |			     |	 |  |
 *            |  काष्ठा task_काष्ठा  |	 |  |
 * current -> |			     |   |  |
 *	      +----------------------+ -------
 *
 * Note that ar.ec is not saved explicitly in pt_reg or चयन_stack.
 * This is because ar.ec is saved as part of ar.pfs.
 */


#समावेश <यंत्र/fpu.h>


#अगर_अघोषित __ASSEMBLY__

/*
 * This काष्ठा defines the way the रेजिस्टरs are saved on प्रणाली
 * calls.
 *
 * We करोn't save all भग्नing poपूर्णांक रेजिस्टर because the kernel
 * is compiled to use only a very small subset, so the other are
 * untouched.
 *
 * THIS STRUCTURE MUST BE A MULTIPLE 16-BYTE IN SIZE
 * (because the memory stack poपूर्णांकer MUST ALWAYS be aligned this way)
 *
 */
काष्ठा pt_regs अणु
	/* The following रेजिस्टरs are saved by SAVE_MIN: */
	अचिन्हित दीर्घ b6;		/* scratch */
	अचिन्हित दीर्घ b7;		/* scratch */

	अचिन्हित दीर्घ ar_csd;           /* used by cmp8xchg16 (scratch) */
	अचिन्हित दीर्घ ar_ssd;           /* reserved क्रम future use (scratch) */

	अचिन्हित दीर्घ r8;		/* scratch (वापस value रेजिस्टर 0) */
	अचिन्हित दीर्घ r9;		/* scratch (वापस value रेजिस्टर 1) */
	अचिन्हित दीर्घ r10;		/* scratch (वापस value रेजिस्टर 2) */
	अचिन्हित दीर्घ r11;		/* scratch (वापस value रेजिस्टर 3) */

	अचिन्हित दीर्घ cr_ipsr;		/* पूर्णांकerrupted task's psr */
	अचिन्हित दीर्घ cr_iip;		/* पूर्णांकerrupted task's inकाष्ठाion poपूर्णांकer */
	/*
	 * पूर्णांकerrupted task's function state; अगर bit 63 is cleared, it
	 * contains syscall's ar.pfs.pfm:
	 */
	अचिन्हित दीर्घ cr_अगरs;

	अचिन्हित दीर्घ ar_unat;		/* पूर्णांकerrupted task's NaT रेजिस्टर (preserved) */
	अचिन्हित दीर्घ ar_pfs;		/* prev function state  */
	अचिन्हित दीर्घ ar_rsc;		/* RSE configuration */
	/* The following two are valid only अगर cr_ipsr.cpl > 0 || ti->flags & _TIF_MCA_INIT */
	अचिन्हित दीर्घ ar_rnat;		/* RSE NaT */
	अचिन्हित दीर्घ ar_bspstore;	/* RSE bspstore */

	अचिन्हित दीर्घ pr;		/* 64 predicate रेजिस्टरs (1 bit each) */
	अचिन्हित दीर्घ b0;		/* वापस poपूर्णांकer (bp) */
	अचिन्हित दीर्घ loadrs;		/* size of dirty partition << 16 */

	अचिन्हित दीर्घ r1;		/* the gp poपूर्णांकer */
	अचिन्हित दीर्घ r12;		/* पूर्णांकerrupted task's memory stack poपूर्णांकer */
	अचिन्हित दीर्घ r13;		/* thपढ़ो poपूर्णांकer */

	अचिन्हित दीर्घ ar_fpsr;		/* भग्नing poपूर्णांक status (preserved) */
	अचिन्हित दीर्घ r15;		/* scratch */

	/* The reमुख्यing रेजिस्टरs are NOT saved क्रम प्रणाली calls.  */

	अचिन्हित दीर्घ r14;		/* scratch */
	अचिन्हित दीर्घ r2;		/* scratch */
	अचिन्हित दीर्घ r3;		/* scratch */

	/* The following रेजिस्टरs are saved by SAVE_REST: */
	अचिन्हित दीर्घ r16;		/* scratch */
	अचिन्हित दीर्घ r17;		/* scratch */
	अचिन्हित दीर्घ r18;		/* scratch */
	अचिन्हित दीर्घ r19;		/* scratch */
	अचिन्हित दीर्घ r20;		/* scratch */
	अचिन्हित दीर्घ r21;		/* scratch */
	अचिन्हित दीर्घ r22;		/* scratch */
	अचिन्हित दीर्घ r23;		/* scratch */
	अचिन्हित दीर्घ r24;		/* scratch */
	अचिन्हित दीर्घ r25;		/* scratch */
	अचिन्हित दीर्घ r26;		/* scratch */
	अचिन्हित दीर्घ r27;		/* scratch */
	अचिन्हित दीर्घ r28;		/* scratch */
	अचिन्हित दीर्घ r29;		/* scratch */
	अचिन्हित दीर्घ r30;		/* scratch */
	अचिन्हित दीर्घ r31;		/* scratch */

	अचिन्हित दीर्घ ar_ccv;		/* compare/exchange value (scratch) */

	/*
	 * Floating poपूर्णांक रेजिस्टरs that the kernel considers scratch:
	 */
	काष्ठा ia64_fpreg f6;		/* scratch */
	काष्ठा ia64_fpreg f7;		/* scratch */
	काष्ठा ia64_fpreg f8;		/* scratch */
	काष्ठा ia64_fpreg f9;		/* scratch */
	काष्ठा ia64_fpreg f10;		/* scratch */
	काष्ठा ia64_fpreg f11;		/* scratch */
पूर्ण;

/*
 * This काष्ठाure contains the addition रेजिस्टरs that need to
 * preserved across a context चयन.  This generally consists of
 * "preserved" रेजिस्टरs.
 */
काष्ठा चयन_stack अणु
	अचिन्हित दीर्घ caller_unat;	/* user NaT collection रेजिस्टर (preserved) */
	अचिन्हित दीर्घ ar_fpsr;		/* भग्नing-poपूर्णांक status रेजिस्टर */

	काष्ठा ia64_fpreg f2;		/* preserved */
	काष्ठा ia64_fpreg f3;		/* preserved */
	काष्ठा ia64_fpreg f4;		/* preserved */
	काष्ठा ia64_fpreg f5;		/* preserved */

	काष्ठा ia64_fpreg f12;		/* scratch, but untouched by kernel */
	काष्ठा ia64_fpreg f13;		/* scratch, but untouched by kernel */
	काष्ठा ia64_fpreg f14;		/* scratch, but untouched by kernel */
	काष्ठा ia64_fpreg f15;		/* scratch, but untouched by kernel */
	काष्ठा ia64_fpreg f16;		/* preserved */
	काष्ठा ia64_fpreg f17;		/* preserved */
	काष्ठा ia64_fpreg f18;		/* preserved */
	काष्ठा ia64_fpreg f19;		/* preserved */
	काष्ठा ia64_fpreg f20;		/* preserved */
	काष्ठा ia64_fpreg f21;		/* preserved */
	काष्ठा ia64_fpreg f22;		/* preserved */
	काष्ठा ia64_fpreg f23;		/* preserved */
	काष्ठा ia64_fpreg f24;		/* preserved */
	काष्ठा ia64_fpreg f25;		/* preserved */
	काष्ठा ia64_fpreg f26;		/* preserved */
	काष्ठा ia64_fpreg f27;		/* preserved */
	काष्ठा ia64_fpreg f28;		/* preserved */
	काष्ठा ia64_fpreg f29;		/* preserved */
	काष्ठा ia64_fpreg f30;		/* preserved */
	काष्ठा ia64_fpreg f31;		/* preserved */

	अचिन्हित दीर्घ r4;		/* preserved */
	अचिन्हित दीर्घ r5;		/* preserved */
	अचिन्हित दीर्घ r6;		/* preserved */
	अचिन्हित दीर्घ r7;		/* preserved */

	अचिन्हित दीर्घ b0;		/* so we can क्रमce a direct वापस in copy_thपढ़ो */
	अचिन्हित दीर्घ b1;
	अचिन्हित दीर्घ b2;
	अचिन्हित दीर्घ b3;
	अचिन्हित दीर्घ b4;
	अचिन्हित दीर्घ b5;

	अचिन्हित दीर्घ ar_pfs;		/* previous function state */
	अचिन्हित दीर्घ ar_lc;		/* loop counter (preserved) */
	अचिन्हित दीर्घ ar_unat;		/* NaT bits क्रम r4-r7 */
	अचिन्हित दीर्घ ar_rnat;		/* RSE NaT collection रेजिस्टर */
	अचिन्हित दीर्घ ar_bspstore;	/* RSE dirty base (preserved) */
	अचिन्हित दीर्घ pr;		/* 64 predicate रेजिस्टरs (1 bit each) */
पूर्ण;


/* pt_all_user_regs is used क्रम PTRACE_GETREGS PTRACE_SETREGS */
काष्ठा pt_all_user_regs अणु
	अचिन्हित दीर्घ nat;
	अचिन्हित दीर्घ cr_iip;
	अचिन्हित दीर्घ cfm;
	अचिन्हित दीर्घ cr_ipsr;
	अचिन्हित दीर्घ pr;

	अचिन्हित दीर्घ gr[32];
	अचिन्हित दीर्घ br[8];
	अचिन्हित दीर्घ ar[128];
	काष्ठा ia64_fpreg fr[128];
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* indices to application-रेजिस्टरs array in pt_all_user_regs */
#घोषणा PT_AUR_RSC	16
#घोषणा PT_AUR_BSP	17
#घोषणा PT_AUR_BSPSTORE	18
#घोषणा PT_AUR_RNAT	19
#घोषणा PT_AUR_CCV	32
#घोषणा PT_AUR_UNAT	36
#घोषणा PT_AUR_FPSR	40
#घोषणा PT_AUR_PFS	64
#घोषणा PT_AUR_LC	65
#घोषणा PT_AUR_EC	66

/*
 * The numbers chosen here are somewhat arbitrary but असलolutely MUST
 * not overlap with any of the number asचिन्हित in <linux/ptrace.h>.
 */
#घोषणा PTRACE_SINGLEBLOCK	12	/* resume execution until next branch */
#घोषणा PTRACE_OLD_GETSIGINFO	13	/* (replaced by PTRACE_GETSIGINFO in <linux/ptrace.h>)  */
#घोषणा PTRACE_OLD_SETSIGINFO	14	/* (replaced by PTRACE_SETSIGINFO in <linux/ptrace.h>)  */
#घोषणा PTRACE_GETREGS		18	/* get all रेजिस्टरs (pt_all_user_regs) in one shot */
#घोषणा PTRACE_SETREGS		19	/* set all रेजिस्टरs (pt_all_user_regs) in one shot */

#घोषणा PTRACE_OLDSETOPTIONS	21

#पूर्ण_अगर /* _UAPI_ASM_IA64_PTRACE_H */
