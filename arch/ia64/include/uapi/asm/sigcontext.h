<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_SIGCONTEXT_H
#घोषणा _ASM_IA64_SIGCONTEXT_H

/*
 * Copyright (C) 1998, 1999, 2001 Hewlett-Packard Co
 * Copyright (C) 1998, 1999, 2001 David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <यंत्र/fpu.h>

#घोषणा IA64_SC_FLAG_ONSTACK_BIT		0	/* is handler running on संकेत stack? */
#घोषणा IA64_SC_FLAG_IN_SYSCALL_BIT		1	/* did संकेत पूर्णांकerrupt a syscall? */
#घोषणा IA64_SC_FLAG_FPH_VALID_BIT		2	/* is state in f[32]-f[127] valid? */

#घोषणा IA64_SC_FLAG_ONSTACK		(1 << IA64_SC_FLAG_ONSTACK_BIT)
#घोषणा IA64_SC_FLAG_IN_SYSCALL		(1 << IA64_SC_FLAG_IN_SYSCALL_BIT)
#घोषणा IA64_SC_FLAG_FPH_VALID		(1 << IA64_SC_FLAG_FPH_VALID_BIT)

# अगरndef __ASSEMBLY__

/*
 * Note on handling of रेजिस्टर backing store: sc_ar_bsp contains the address that would
 * be found in ar.bsp after executing a "cover" inकाष्ठाion the context in which the
 * संकेत was उठाओd.  If संकेत delivery required चयनing to an alternate संकेत stack
 * (sc_rbs_base is not शून्य), the "dirty" partition (as it would exist after executing the
 * imaginary "cover" inकाष्ठाion) is backed by the *alternate* संकेत stack, not the
 * original one.  In this हाल, sc_rbs_base contains the base address of the new रेजिस्टर
 * backing store.  The number of रेजिस्टरs in the dirty partition can be calculated as:
 *
 *   ndirty = ia64_rse_num_regs(sc_rbs_base, sc_rbs_base + (sc_loadrs >> 16))
 *
 */

काष्ठा sigcontext अणु
	अचिन्हित दीर्घ		sc_flags;	/* see manअगरest स्थिरants above */
	अचिन्हित दीर्घ		sc_nat;		/* bit i == 1 अगरf scratch reg gr[i] is a NaT */
	stack_t			sc_stack;	/* previously active stack */

	अचिन्हित दीर्घ		sc_ip;		/* inकाष्ठाion poपूर्णांकer */
	अचिन्हित दीर्घ		sc_cfm;		/* current frame marker */
	अचिन्हित दीर्घ		sc_um;		/* user mask bits */
	अचिन्हित दीर्घ		sc_ar_rsc;	/* रेजिस्टर stack configuration रेजिस्टर */
	अचिन्हित दीर्घ		sc_ar_bsp;	/* backing store poपूर्णांकer */
	अचिन्हित दीर्घ		sc_ar_rnat;	/* RSE NaT collection रेजिस्टर */
	अचिन्हित दीर्घ		sc_ar_ccv;	/* compare and exchange compare value रेजिस्टर */
	अचिन्हित दीर्घ		sc_ar_unat;	/* ar.unat of पूर्णांकerrupted context */
	अचिन्हित दीर्घ		sc_ar_fpsr;	/* भग्नing-poपूर्णांक status रेजिस्टर */
	अचिन्हित दीर्घ		sc_ar_pfs;	/* previous function state */
	अचिन्हित दीर्घ		sc_ar_lc;	/* loop count रेजिस्टर */
	अचिन्हित दीर्घ		sc_pr;		/* predicate रेजिस्टरs */
	अचिन्हित दीर्घ		sc_br[8];	/* branch रेजिस्टरs */
	/* Note: sc_gr[0] is used as the "uc_link" member of ucontext_t */
	अचिन्हित दीर्घ		sc_gr[32];	/* general रेजिस्टरs (अटल partition) */
	काष्ठा ia64_fpreg	sc_fr[128];	/* भग्नing-poपूर्णांक रेजिस्टरs */

	अचिन्हित दीर्घ		sc_rbs_base;	/* शून्य or new base of sighandler's rbs */
	अचिन्हित दीर्घ		sc_loadrs;	/* see description above */

	अचिन्हित दीर्घ		sc_ar25;	/* cmp8xchg16 uses this */
	अचिन्हित दीर्घ		sc_ar26;	/* rsvd क्रम scratch use */
	अचिन्हित दीर्घ		sc_rsvd[12];	/* reserved क्रम future use */
	/*
	 * The mask must come last so we can increase _NSIG_WORDS
	 * without अवरोधing binary compatibility.
	 */
	sigset_t		sc_mask;	/* संकेत mask to restore after handler वापसs */
पूर्ण;

# endअगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_IA64_SIGCONTEXT_H */
