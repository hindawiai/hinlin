<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASMAXP_SIGCONTEXT_H
#घोषणा _ASMAXP_SIGCONTEXT_H

काष्ठा sigcontext अणु
	/*
	 * What should we have here? I'd probably better use the same
	 * stack layout as OSF/1, just in हाल we ever want to try
	 * running their binaries.. 
	 *
	 * This is the basic layout, but I करोn't know if we'll ever
	 * actually fill in all the values..
	 */
	 दीर्घ		sc_onstack;
	 दीर्घ		sc_mask;
	 दीर्घ		sc_pc;
	 दीर्घ		sc_ps;
	 दीर्घ		sc_regs[32];
	 दीर्घ		sc_ownedfp;
	 दीर्घ		sc_fpregs[32];
	 अचिन्हित दीर्घ	sc_fpcr;
	 अचिन्हित दीर्घ	sc_fp_control;
	 अचिन्हित दीर्घ	sc_reserved1, sc_reserved2;
	 अचिन्हित दीर्घ	sc_ssize;
	 अक्षर *		sc_sbase;
	 अचिन्हित दीर्घ	sc_traparg_a0;
	 अचिन्हित दीर्घ	sc_traparg_a1;
	 अचिन्हित दीर्घ	sc_traparg_a2;
	 अचिन्हित दीर्घ	sc_fp_trap_pc;
	 अचिन्हित दीर्घ	sc_fp_trigger_sum;
	 अचिन्हित दीर्घ	sc_fp_trigger_inst;
पूर्ण;


#पूर्ण_अगर
