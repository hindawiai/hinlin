<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/kernel/traps.c
 *
 * (C) Copyright 1994 Linus Torvalds
 */

/*
 * This file initializes the trap entry poपूर्णांकs
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/tty.h>
#समावेश <linux/delay.h>
#समावेश <linux/extable.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/ratelimit.h>

#समावेश <यंत्र/gentrap.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/special_insns.h>

#समावेश "proto.h"

/* Work-around क्रम some SRMs which mishandle opDEC faults.  */

अटल पूर्णांक opDEC_fix;

अटल व्योम
opDEC_check(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
	/* Load the address of... */
	"	br	$16, 1f\n"
	/* A stub inकाष्ठाion fault handler.  Just add 4 to the
	   pc and जारी.  */
	"	ldq	$16, 8($sp)\n"
	"	addq	$16, 4, $16\n"
	"	stq	$16, 8($sp)\n"
	"	call_pal %[rti]\n"
	/* Install the inकाष्ठाion fault handler.  */
	"1:	lda	$17, 3\n"
	"	call_pal %[wrent]\n"
	/* With that in place, the fault from the round-to-minf fp
	   insn will arrive either at the "lda 4" insn (bad) or one
	   past that (good).  This places the correct fixup in %0.  */
	"	lda %[fix], 0\n"
	"	cvttq/svm $f31,$f31\n"
	"	lda %[fix], 4"
	: [fix] "=r" (opDEC_fix)
	: [rti] "n" (PAL_rti), [wrent] "n" (PAL_wrent)
	: "$0", "$1", "$16", "$17", "$22", "$23", "$24", "$25");

	अगर (opDEC_fix)
		prपूर्णांकk("opDEC fixup enabled.\n");
पूर्ण

व्योम
dik_show_regs(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *r9_15)
अणु
	prपूर्णांकk("pc = [<%016lx>]  ra = [<%016lx>]  ps = %04lx    %s\n",
	       regs->pc, regs->r26, regs->ps, prपूर्णांक_taपूर्णांकed());
	prपूर्णांकk("pc is at %pSR\n", (व्योम *)regs->pc);
	prपूर्णांकk("ra is at %pSR\n", (व्योम *)regs->r26);
	prपूर्णांकk("v0 = %016lx  t0 = %016lx  t1 = %016lx\n",
	       regs->r0, regs->r1, regs->r2);
	prपूर्णांकk("t2 = %016lx  t3 = %016lx  t4 = %016lx\n",
 	       regs->r3, regs->r4, regs->r5);
	prपूर्णांकk("t5 = %016lx  t6 = %016lx  t7 = %016lx\n",
	       regs->r6, regs->r7, regs->r8);

	अगर (r9_15) अणु
		prपूर्णांकk("s0 = %016lx  s1 = %016lx  s2 = %016lx\n",
		       r9_15[9], r9_15[10], r9_15[11]);
		prपूर्णांकk("s3 = %016lx  s4 = %016lx  s5 = %016lx\n",
		       r9_15[12], r9_15[13], r9_15[14]);
		prपूर्णांकk("s6 = %016lx\n", r9_15[15]);
	पूर्ण

	prपूर्णांकk("a0 = %016lx  a1 = %016lx  a2 = %016lx\n",
	       regs->r16, regs->r17, regs->r18);
	prपूर्णांकk("a3 = %016lx  a4 = %016lx  a5 = %016lx\n",
 	       regs->r19, regs->r20, regs->r21);
 	prपूर्णांकk("t8 = %016lx  t9 = %016lx  t10= %016lx\n",
	       regs->r22, regs->r23, regs->r24);
	prपूर्णांकk("t11= %016lx  pv = %016lx  at = %016lx\n",
	       regs->r25, regs->r27, regs->r28);
	prपूर्णांकk("gp = %016lx  sp = %p\n", regs->gp, regs+1);
#अगर 0
__halt();
#पूर्ण_अगर
पूर्ण

#अगर 0
अटल अक्षर * ireg_name[] = अणु"v0", "t0", "t1", "t2", "t3", "t4", "t5", "t6",
			   "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6",
			   "a0", "a1", "a2", "a3", "a4", "a5", "t8", "t9",
			   "t10", "t11", "ra", "pv", "at", "gp", "sp", "zero"पूर्ण;
#पूर्ण_अगर

अटल व्योम
dik_show_code(अचिन्हित पूर्णांक *pc)
अणु
	दीर्घ i;

	prपूर्णांकk("Code:");
	क्रम (i = -6; i < 2; i++) अणु
		अचिन्हित पूर्णांक insn;
		अगर (__get_user(insn, (अचिन्हित पूर्णांक __user *)pc + i))
			अवरोध;
		prपूर्णांकk("%c%08x%c", i ? ' ' : '<', insn, i ? ' ' : '>');
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम
dik_show_trace(अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	दीर्घ i = 0;
	prपूर्णांकk("%sTrace:\n", loglvl);
	जबतक (0x1ff8 & (अचिन्हित दीर्घ) sp) अणु
		बाह्य अक्षर _stext[], _etext[];
		अचिन्हित दीर्घ पंचांगp = *sp;
		sp++;
		अगर (पंचांगp < (अचिन्हित दीर्घ) &_stext)
			जारी;
		अगर (पंचांगp >= (अचिन्हित दीर्घ) &_etext)
			जारी;
		prपूर्णांकk("%s[<%lx>] %pSR\n", loglvl, पंचांगp, (व्योम *)पंचांगp);
		अगर (i > 40) अणु
			prपूर्णांकk("%s ...", loglvl);
			अवरोध;
		पूर्ण
	पूर्ण
	prपूर्णांकk("%s\n", loglvl);
पूर्ण

अटल पूर्णांक kstack_depth_to_prपूर्णांक = 24;

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ *stack;
	पूर्णांक i;

	/*
	 * debugging aid: "show_stack(NULL, NULL, KERN_EMERG);" prपूर्णांकs the
	 * back trace क्रम this cpu.
	 */
	अगर(sp==शून्य)
		sp=(अचिन्हित दीर्घ*)&sp;

	stack = sp;
	क्रम(i=0; i < kstack_depth_to_prपूर्णांक; i++) अणु
		अगर (((दीर्घ) stack & (THREAD_SIZE-1)) == 0)
			अवरोध;
		अगर ((i % 4) == 0) अणु
			अगर (i)
				pr_cont("\n");
			prपूर्णांकk("%s       ", loglvl);
		पूर्ण अन्यथा अणु
			pr_cont(" ");
		पूर्ण
		pr_cont("%016lx", *stack++);
	पूर्ण
	pr_cont("\n");
	dik_show_trace(sp, loglvl);
पूर्ण

व्योम
die_अगर_kernel(अक्षर * str, काष्ठा pt_regs *regs, दीर्घ err, अचिन्हित दीर्घ *r9_15)
अणु
	अगर (regs->ps & 8)
		वापस;
#अगर_घोषित CONFIG_SMP
	prपूर्णांकk("CPU %d ", hard_smp_processor_id());
#पूर्ण_अगर
	prपूर्णांकk("%s(%d): %s %ld\n", current->comm, task_pid_nr(current), str, err);
	dik_show_regs(regs, r9_15);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	dik_show_trace((अचिन्हित दीर्घ *)(regs+1), KERN_DEFAULT);
	dik_show_code((अचिन्हित पूर्णांक *)regs->pc);

	अगर (test_and_set_thपढ़ो_flag (TIF_DIE_IF_KERNEL)) अणु
		prपूर्णांकk("die_if_kernel recursion detected.\n");
		local_irq_enable();
		जबतक (1);
	पूर्ण
	करो_निकास(संक_अंश);
पूर्ण

#अगर_अघोषित CONFIG_MATHEMU
अटल दीर्घ dummy_emul(व्योम) अणु वापस 0; पूर्ण
दीर्घ (*alpha_fp_emul_imprecise)(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ग_लिखोmask)
  = (व्योम *)dummy_emul;
EXPORT_SYMBOL_GPL(alpha_fp_emul_imprecise);
दीर्घ (*alpha_fp_emul) (अचिन्हित दीर्घ pc)
  = (व्योम *)dummy_emul;
EXPORT_SYMBOL_GPL(alpha_fp_emul);
#अन्यथा
दीर्घ alpha_fp_emul_imprecise(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ग_लिखोmask);
दीर्घ alpha_fp_emul (अचिन्हित दीर्घ pc);
#पूर्ण_अगर

यंत्रlinkage व्योम
करो_entArith(अचिन्हित दीर्घ summary, अचिन्हित दीर्घ ग_लिखो_mask,
	    काष्ठा pt_regs *regs)
अणु
	दीर्घ si_code = FPE_FLTINV;

	अगर (summary & 1) अणु
		/* Software-completion summary bit is set, so try to
		   emulate the inकाष्ठाion.  If the processor supports
		   precise exceptions, we करोn't have to search.  */
		अगर (!amask(AMASK_PRECISE_TRAP))
			si_code = alpha_fp_emul(regs->pc - 4);
		अन्यथा
			si_code = alpha_fp_emul_imprecise(regs, ग_लिखो_mask);
		अगर (si_code == 0)
			वापस;
	पूर्ण
	die_अगर_kernel("Arithmetic fault", regs, 0, शून्य);

	send_sig_fault(संक_भ_त्रुटि, si_code, (व्योम __user *) regs->pc, 0, current);
पूर्ण

यंत्रlinkage व्योम
करो_entIF(अचिन्हित दीर्घ type, काष्ठा pt_regs *regs)
अणु
	पूर्णांक signo, code;

	अगर ((regs->ps & ~IPL_MAX) == 0) अणु
		अगर (type == 1) अणु
			स्थिर अचिन्हित पूर्णांक *data
			  = (स्थिर अचिन्हित पूर्णांक *) regs->pc;
			prपूर्णांकk("Kernel bug at %s:%d\n",
			       (स्थिर अक्षर *)(data[1] | (दीर्घ)data[2] << 32), 
			       data[0]);
		पूर्ण
#अगर_घोषित CONFIG_ALPHA_WTINT
		अगर (type == 4) अणु
			/* If CALL_PAL WTINT is totally unsupported by the
			   PALcode, e.g. MILO, "emulate" it by overwriting
			   the insn.  */
			अचिन्हित पूर्णांक *pinsn
			  = (अचिन्हित पूर्णांक *) regs->pc - 1;
			अगर (*pinsn == PAL_wtपूर्णांक) अणु
				*pinsn = 0x47e01400; /* mov 0,$0 */
				imb();
				regs->r0 = 0;
				वापस;
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* ALPHA_WTINT */
		die_अगर_kernel((type == 1 ? "Kernel Bug" : "Instruction fault"),
			      regs, type, शून्य);
	पूर्ण

	चयन (type) अणु
	      हाल 0: /* अवरोधpoपूर्णांक */
		अगर (ptrace_cancel_bpt(current)) अणु
			regs->pc -= 4;	/* make pc poपूर्णांक to क्रमmer bpt */
		पूर्ण

		send_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *)regs->pc, 0,
			       current);
		वापस;

	      हाल 1: /* bugcheck */
		send_sig_fault(SIGTRAP, TRAP_UNK, (व्योम __user *) regs->pc, 0,
			       current);
		वापस;
		
	      हाल 2: /* gentrap */
		चयन ((दीर्घ) regs->r16) अणु
		हाल GEN_INTOVF:
			signo = संक_भ_त्रुटि;
			code = FPE_INTOVF;
			अवरोध;
		हाल GEN_INTDIV:
			signo = संक_भ_त्रुटि;
			code = FPE_INTDIV;
			अवरोध;
		हाल GEN_FLTOVF:
			signo = संक_भ_त्रुटि;
			code = FPE_FLTOVF;
			अवरोध;
		हाल GEN_FLTDIV:
			signo = संक_भ_त्रुटि;
			code = FPE_FLTDIV;
			अवरोध;
		हाल GEN_FLTUND:
			signo = संक_भ_त्रुटि;
			code = FPE_FLTUND;
			अवरोध;
		हाल GEN_FLTINV:
			signo = संक_भ_त्रुटि;
			code = FPE_FLTINV;
			अवरोध;
		हाल GEN_FLTINE:
			signo = संक_भ_त्रुटि;
			code = FPE_FLTRES;
			अवरोध;
		हाल GEN_ROPRAND:
			signo = संक_भ_त्रुटि;
			code = FPE_FLTUNK;
			अवरोध;

		हाल GEN_DECOVF:
		हाल GEN_DECDIV:
		हाल GEN_DECINV:
		हाल GEN_ASSERTERR:
		हाल GEN_NULPTRERR:
		हाल GEN_STKOVF:
		हाल GEN_STRLENERR:
		हाल GEN_SUBSTRERR:
		हाल GEN_RANGERR:
		हाल GEN_SUBRNG:
		हाल GEN_SUBRNG1:
		हाल GEN_SUBRNG2:
		हाल GEN_SUBRNG3:
		हाल GEN_SUBRNG4:
		हाल GEN_SUBRNG5:
		हाल GEN_SUBRNG6:
		हाल GEN_SUBRNG7:
		शेष:
			signo = SIGTRAP;
			code = TRAP_UNK;
			अवरोध;
		पूर्ण

		send_sig_fault(signo, code, (व्योम __user *) regs->pc, regs->r16,
			       current);
		वापस;

	      हाल 4: /* opDEC */
		अगर (implver() == IMPLVER_EV4) अणु
			दीर्घ si_code;

			/* The some versions of SRM करो not handle
			   the opDEC properly - they वापस the PC of the
			   opDEC fault, not the inकाष्ठाion after as the
			   Alpha architecture requires.  Here we fix it up.
			   We करो this by पूर्णांकentionally causing an opDEC
			   fault during the boot sequence and testing अगर
			   we get the correct PC.  If not, we set a flag
			   to correct it every समय through.  */
			regs->pc += opDEC_fix; 
			
			/* EV4 करोes not implement anything except normal
			   rounding.  Everything अन्यथा will come here as
			   an illegal inकाष्ठाion.  Emulate them.  */
			si_code = alpha_fp_emul(regs->pc - 4);
			अगर (si_code == 0)
				वापस;
			अगर (si_code > 0) अणु
				send_sig_fault(संक_भ_त्रुटि, si_code,
					       (व्योम __user *) regs->pc, 0,
					       current);
				वापस;
			पूर्ण
		पूर्ण
		अवरोध;

	      हाल 3: /* FEN fault */
		/* Irritating users can call PAL_clrfen to disable the
		   FPU क्रम the process.  The kernel will then trap in
		   करो_चयन_stack and unकरो_चयन_stack when we try
		   to save and restore the FP रेजिस्टरs.

		   Given that GCC by शेष generates code that uses the
		   FP रेजिस्टरs, PAL_clrfen is not useful except क्रम DoS
		   attacks.  So turn the bleeding FPU back on and be करोne
		   with it.  */
		current_thपढ़ो_info()->pcb.flags |= 1;
		__reload_thपढ़ो(&current_thपढ़ो_info()->pcb);
		वापस;

	      हाल 5: /* illoc */
	      शेष: /* unexpected inकाष्ठाion-fault type */
		      ;
	पूर्ण

	send_sig_fault(संक_अवैध, ILL_ILLOPC, (व्योम __user *)regs->pc, 0, current);
पूर्ण

/* There is an अगरdef in the PALcode in MILO that enables a 
   "kernel debugging entry point" as an unprivileged call_pal.

   We करोn't want to have anything to करो with it, but unक्रमtunately
   several versions of MILO included in distributions have it enabled,
   and अगर we करोn't put something on the entry point we'll oops.  */

यंत्रlinkage व्योम
करो_entDbg(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("Instruction fault", regs, 0, शून्य);

	क्रमce_sig_fault(संक_अवैध, ILL_ILLOPC, (व्योम __user *)regs->pc, 0);
पूर्ण


/*
 * entUna has a dअगरferent रेजिस्टर layout to be reasonably simple. It
 * needs access to all the पूर्णांकeger रेजिस्टरs (the kernel करोesn't use
 * fp-regs), and it needs to have them in order क्रम simpler access.
 *
 * Due to the non-standard रेजिस्टर layout (and because we करोn't want
 * to handle भग्नing-poपूर्णांक regs), user-mode unaligned accesses are
 * handled separately by करो_entUnaUser below.
 *
 * Oh, btw, we करोn't handle the "gp" रेजिस्टर correctly, but अगर we fault
 * on a gp-रेजिस्टर unaligned load/store, something is _very_ wrong
 * in the kernel anyway..
 */
काष्ठा allregs अणु
	अचिन्हित दीर्घ regs[32];
	अचिन्हित दीर्घ ps, pc, gp, a0, a1, a2;
पूर्ण;

काष्ठा unaligned_stat अणु
	अचिन्हित दीर्घ count, va, pc;
पूर्ण unaligned[2];


/* Macro क्रम exception fixup code to access पूर्णांकeger रेजिस्टरs.  */
#घोषणा una_reg(r)  (_regs[(r) >= 16 && (r) <= 18 ? (r)+19 : (r)])


यंत्रlinkage व्योम
करो_entUna(व्योम * va, अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ reg,
	  काष्ठा allregs *regs)
अणु
	दीर्घ error, पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4;
	अचिन्हित दीर्घ pc = regs->pc - 4;
	अचिन्हित दीर्घ *_regs = regs->regs;
	स्थिर काष्ठा exception_table_entry *fixup;

	unaligned[0].count++;
	unaligned[0].va = (अचिन्हित दीर्घ) va;
	unaligned[0].pc = pc;

	/* We करोn't want to use the generic get/put unaligned macros as
	   we want to trap exceptions.  Only अगर we actually get an
	   exception will we decide whether we should have caught it.  */

	चयन (opcode) अणु
	हाल 0x0c: /* ldwu */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,1(%3)\n"
		"	extwl %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ got_exception;
		una_reg(reg) = पंचांगp1|पंचांगp2;
		वापस;

	हाल 0x28: /* ldl */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,3(%3)\n"
		"	extll %1,%3,%1\n"
		"	extlh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ got_exception;
		una_reg(reg) = (पूर्णांक)(पंचांगp1|पंचांगp2);
		वापस;

	हाल 0x29: /* ldq */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,7(%3)\n"
		"	extql %1,%3,%1\n"
		"	extqh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ got_exception;
		una_reg(reg) = पंचांगp1|पंचांगp2;
		वापस;

	/* Note that the store sequences करो not indicate that they change
	   memory because it _should_ be affecting nothing in this context.
	   (Otherwise we have other, much larger, problems.)  */
	हाल 0x0d: /* stw */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %2,1(%5)\n"
		"2:	ldq_u %1,0(%5)\n"
		"	inswh %6,%5,%4\n"
		"	inswl %6,%5,%3\n"
		"	mskwh %2,%5,%2\n"
		"	mskwl %1,%5,%1\n"
		"	or %2,%4,%2\n"
		"	or %1,%3,%1\n"
		"3:	stq_u %2,1(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2),
			  "=&r"(पंचांगp3), "=&r"(पंचांगp4)
			: "r"(va), "r"(una_reg(reg)), "0"(0));
		अगर (error)
			जाओ got_exception;
		वापस;

	हाल 0x2c: /* stl */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %2,3(%5)\n"
		"2:	ldq_u %1,0(%5)\n"
		"	inslh %6,%5,%4\n"
		"	insll %6,%5,%3\n"
		"	msklh %2,%5,%2\n"
		"	mskll %1,%5,%1\n"
		"	or %2,%4,%2\n"
		"	or %1,%3,%1\n"
		"3:	stq_u %2,3(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2),
			  "=&r"(पंचांगp3), "=&r"(पंचांगp4)
			: "r"(va), "r"(una_reg(reg)), "0"(0));
		अगर (error)
			जाओ got_exception;
		वापस;

	हाल 0x2d: /* stq */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %2,7(%5)\n"
		"2:	ldq_u %1,0(%5)\n"
		"	insqh %6,%5,%4\n"
		"	insql %6,%5,%3\n"
		"	mskqh %2,%5,%2\n"
		"	mskql %1,%5,%1\n"
		"	or %2,%4,%2\n"
		"	or %1,%3,%1\n"
		"3:	stq_u %2,7(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2),
			  "=&r"(पंचांगp3), "=&r"(पंचांगp4)
			: "r"(va), "r"(una_reg(reg)), "0"(0));
		अगर (error)
			जाओ got_exception;
		वापस;
	पूर्ण

	prपूर्णांकk("Bad unaligned kernel access at %016lx: %p %lx %lu\n",
		pc, va, opcode, reg);
	करो_निकास(संक_अंश);

got_exception:
	/* Ok, we caught the exception, but we करोn't want it.  Is there
	   someone to pass it aदीर्घ to?  */
	अगर ((fixup = search_exception_tables(pc)) != 0) अणु
		अचिन्हित दीर्घ newpc;
		newpc = fixup_exception(una_reg, fixup, pc);

		prपूर्णांकk("Forwarding unaligned exception at %lx (%lx)\n",
		       pc, newpc);

		regs->pc = newpc;
		वापस;
	पूर्ण

	/*
	 * Yikes!  No one to क्रमward the exception to.
	 * Since the रेजिस्टरs are in a weird क्रमmat, dump them ourselves.
 	 */

	prपूर्णांकk("%s(%d): unhandled unaligned exception\n",
	       current->comm, task_pid_nr(current));

	prपूर्णांकk("pc = [<%016lx>]  ra = [<%016lx>]  ps = %04lx\n",
	       pc, una_reg(26), regs->ps);
	prपूर्णांकk("r0 = %016lx  r1 = %016lx  r2 = %016lx\n",
	       una_reg(0), una_reg(1), una_reg(2));
	prपूर्णांकk("r3 = %016lx  r4 = %016lx  r5 = %016lx\n",
 	       una_reg(3), una_reg(4), una_reg(5));
	prपूर्णांकk("r6 = %016lx  r7 = %016lx  r8 = %016lx\n",
	       una_reg(6), una_reg(7), una_reg(8));
	prपूर्णांकk("r9 = %016lx  r10= %016lx  r11= %016lx\n",
	       una_reg(9), una_reg(10), una_reg(11));
	prपूर्णांकk("r12= %016lx  r13= %016lx  r14= %016lx\n",
	       una_reg(12), una_reg(13), una_reg(14));
	prपूर्णांकk("r15= %016lx\n", una_reg(15));
	prपूर्णांकk("r16= %016lx  r17= %016lx  r18= %016lx\n",
	       una_reg(16), una_reg(17), una_reg(18));
	prपूर्णांकk("r19= %016lx  r20= %016lx  r21= %016lx\n",
 	       una_reg(19), una_reg(20), una_reg(21));
 	prपूर्णांकk("r22= %016lx  r23= %016lx  r24= %016lx\n",
	       una_reg(22), una_reg(23), una_reg(24));
	prपूर्णांकk("r25= %016lx  r27= %016lx  r28= %016lx\n",
	       una_reg(25), una_reg(27), una_reg(28));
	prपूर्णांकk("gp = %016lx  sp = %p\n", regs->gp, regs+1);

	dik_show_code((अचिन्हित पूर्णांक *)pc);
	dik_show_trace((अचिन्हित दीर्घ *)(regs+1), KERN_DEFAULT);

	अगर (test_and_set_thपढ़ो_flag (TIF_DIE_IF_KERNEL)) अणु
		prपूर्णांकk("die_if_kernel recursion detected.\n");
		local_irq_enable();
		जबतक (1);
	पूर्ण
	करो_निकास(संक_अंश);
पूर्ण

/*
 * Convert an s-भग्नing poपूर्णांक value in memory क्रमmat to the
 * corresponding value in रेजिस्टर क्रमmat.  The exponent
 * needs to be remapped to preserve non-finite values
 * (infinities, not-a-numbers, denormals).
 */
अटल अंतरभूत अचिन्हित दीर्घ
s_mem_to_reg (अचिन्हित दीर्घ s_mem)
अणु
	अचिन्हित दीर्घ frac    = (s_mem >>  0) & 0x7fffff;
	अचिन्हित दीर्घ sign    = (s_mem >> 31) & 0x1;
	अचिन्हित दीर्घ exp_msb = (s_mem >> 30) & 0x1;
	अचिन्हित दीर्घ exp_low = (s_mem >> 23) & 0x7f;
	अचिन्हित दीर्घ exp;

	exp = (exp_msb << 10) | exp_low;	/* common हाल */
	अगर (exp_msb) अणु
		अगर (exp_low == 0x7f) अणु
			exp = 0x7ff;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (exp_low == 0x00) अणु
			exp = 0x000;
		पूर्ण अन्यथा अणु
			exp |= (0x7 << 7);
		पूर्ण
	पूर्ण
	वापस (sign << 63) | (exp << 52) | (frac << 29);
पूर्ण

/*
 * Convert an s-भग्नing poपूर्णांक value in रेजिस्टर क्रमmat to the
 * corresponding value in memory क्रमmat.
 */
अटल अंतरभूत अचिन्हित दीर्घ
s_reg_to_mem (अचिन्हित दीर्घ s_reg)
अणु
	वापस ((s_reg >> 62) << 30) | ((s_reg << 5) >> 34);
पूर्ण

/*
 * Handle user-level unaligned fault.  Handling user-level unaligned
 * faults is *extremely* slow and produces nasty messages.  A user
 * program *should* fix unaligned faults ASAP.
 *
 * Notice that we have (almost) the regular kernel stack layout here,
 * so finding the appropriate रेजिस्टरs is a little more dअगरficult
 * than in the kernel हाल.
 *
 * Finally, we handle regular पूर्णांकeger load/stores only.  In
 * particular, load-linked/store-conditionally and भग्नing poपूर्णांक
 * load/stores are not supported.  The क्रमmer make no sense with
 * unaligned faults (they are guaranteed to fail) and I करोn't think
 * the latter will occur in any decent program.
 *
 * Sigh. We *करो* have to handle some FP operations, because GCC will
 * uses them as temporary storage क्रम पूर्णांकeger memory to memory copies.
 * However, we need to deal with stt/ldt and sts/lds only.
 */

#घोषणा OP_INT_MASK	( 1L << 0x28 | 1L << 0x2c   /* ldl stl */	\
			| 1L << 0x29 | 1L << 0x2d   /* ldq stq */	\
			| 1L << 0x0c | 1L << 0x0d   /* ldwu stw */	\
			| 1L << 0x0a | 1L << 0x0e ) /* ldbu stb */

#घोषणा OP_WRITE_MASK	( 1L << 0x26 | 1L << 0x27   /* sts stt */	\
			| 1L << 0x2c | 1L << 0x2d   /* stl stq */	\
			| 1L << 0x0d | 1L << 0x0e ) /* stw stb */

#घोषणा R(x)	((माप_प्रकार) &((काष्ठा pt_regs *)0)->x)

अटल पूर्णांक unauser_reg_offsets[32] = अणु
	R(r0), R(r1), R(r2), R(r3), R(r4), R(r5), R(r6), R(r7), R(r8),
	/* r9 ... r15 are stored in front of regs.  */
	-56, -48, -40, -32, -24, -16, -8,
	R(r16), R(r17), R(r18),
	R(r19), R(r20), R(r21), R(r22), R(r23), R(r24), R(r25), R(r26),
	R(r27), R(r28), R(gp),
	0, 0
पूर्ण;

#अघोषित R

यंत्रlinkage व्योम
करो_entUnaUser(व्योम __user * va, अचिन्हित दीर्घ opcode,
	      अचिन्हित दीर्घ reg, काष्ठा pt_regs *regs)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 5);

	अचिन्हित दीर्घ पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4;
	अचिन्हित दीर्घ fake_reg, *reg_addr = &fake_reg;
	पूर्णांक si_code;
	दीर्घ error;

	/* Check the UAC bits to decide what the user wants us to करो
	   with the unaliged access.  */

	अगर (!(current_thपढ़ो_info()->status & TS_UAC_NOPRINT)) अणु
		अगर (__ratelimit(&ratelimit)) अणु
			prपूर्णांकk("%s(%d): unaligned trap at %016lx: %p %lx %ld\n",
			       current->comm, task_pid_nr(current),
			       regs->pc - 4, va, opcode, reg);
		पूर्ण
	पूर्ण
	अगर ((current_thपढ़ो_info()->status & TS_UAC_SIGBUS))
		जाओ give_sigbus;
	/* Not sure why you'd want to use this, but... */
	अगर ((current_thपढ़ो_info()->status & TS_UAC_NOFIX))
		वापस;

	/* Don't bother पढ़ोing ds in the access check since we alपढ़ोy
	   know that this came from the user.  Also rely on the fact that
	   the page at TASK_SIZE is unmapped and so can't be touched anyway. */
	अगर ((अचिन्हित दीर्घ)va >= TASK_SIZE)
		जाओ give_sigsegv;

	++unaligned[1].count;
	unaligned[1].va = (अचिन्हित दीर्घ)va;
	unaligned[1].pc = regs->pc - 4;

	अगर ((1L << opcode) & OP_INT_MASK) अणु
		/* it's an पूर्णांकeger load/store */
		अगर (reg < 30) अणु
			reg_addr = (अचिन्हित दीर्घ *)
			  ((अक्षर *)regs + unauser_reg_offsets[reg]);
		पूर्ण अन्यथा अगर (reg == 30) अणु
			/* usp in PAL regs */
			fake_reg = rdusp();
		पूर्ण अन्यथा अणु
			/* zero "register" */
			fake_reg = 0;
		पूर्ण
	पूर्ण

	/* We करोn't want to use the generic get/put unaligned macros as
	   we want to trap exceptions.  Only अगर we actually get an
	   exception will we decide whether we should have caught it.  */

	चयन (opcode) अणु
	हाल 0x0c: /* ldwu */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,1(%3)\n"
		"	extwl %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		*reg_addr = पंचांगp1|पंचांगp2;
		अवरोध;

	हाल 0x22: /* lds */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,3(%3)\n"
		"	extll %1,%3,%1\n"
		"	extlh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		alpha_ग_लिखो_fp_reg(reg, s_mem_to_reg((पूर्णांक)(पंचांगp1|पंचांगp2)));
		वापस;

	हाल 0x23: /* ldt */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,7(%3)\n"
		"	extql %1,%3,%1\n"
		"	extqh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		alpha_ग_लिखो_fp_reg(reg, पंचांगp1|पंचांगp2);
		वापस;

	हाल 0x28: /* ldl */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,3(%3)\n"
		"	extll %1,%3,%1\n"
		"	extlh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		*reg_addr = (पूर्णांक)(पंचांगp1|पंचांगp2);
		अवरोध;

	हाल 0x29: /* ldq */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %1,0(%3)\n"
		"2:	ldq_u %2,7(%3)\n"
		"	extql %1,%3,%1\n"
		"	extqh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2)
			: "r"(va), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		*reg_addr = पंचांगp1|पंचांगp2;
		अवरोध;

	/* Note that the store sequences करो not indicate that they change
	   memory because it _should_ be affecting nothing in this context.
	   (Otherwise we have other, much larger, problems.)  */
	हाल 0x0d: /* stw */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %2,1(%5)\n"
		"2:	ldq_u %1,0(%5)\n"
		"	inswh %6,%5,%4\n"
		"	inswl %6,%5,%3\n"
		"	mskwh %2,%5,%2\n"
		"	mskwl %1,%5,%1\n"
		"	or %2,%4,%2\n"
		"	or %1,%3,%1\n"
		"3:	stq_u %2,1(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2),
			  "=&r"(पंचांगp3), "=&r"(पंचांगp4)
			: "r"(va), "r"(*reg_addr), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		वापस;

	हाल 0x26: /* sts */
		fake_reg = s_reg_to_mem(alpha_पढ़ो_fp_reg(reg));
		fallthrough;

	हाल 0x2c: /* stl */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %2,3(%5)\n"
		"2:	ldq_u %1,0(%5)\n"
		"	inslh %6,%5,%4\n"
		"	insll %6,%5,%3\n"
		"	msklh %2,%5,%2\n"
		"	mskll %1,%5,%1\n"
		"	or %2,%4,%2\n"
		"	or %1,%3,%1\n"
		"3:	stq_u %2,3(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2),
			  "=&r"(पंचांगp3), "=&r"(पंचांगp4)
			: "r"(va), "r"(*reg_addr), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		वापस;

	हाल 0x27: /* stt */
		fake_reg = alpha_पढ़ो_fp_reg(reg);
		fallthrough;

	हाल 0x2d: /* stq */
		__यंत्र__ __अस्थिर__(
		"1:	ldq_u %2,7(%5)\n"
		"2:	ldq_u %1,0(%5)\n"
		"	insqh %6,%5,%4\n"
		"	insql %6,%5,%3\n"
		"	mskqh %2,%5,%2\n"
		"	mskql %1,%5,%1\n"
		"	or %2,%4,%2\n"
		"	or %1,%3,%1\n"
		"3:	stq_u %2,7(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=r"(error), "=&r"(पंचांगp1), "=&r"(पंचांगp2),
			  "=&r"(पंचांगp3), "=&r"(पंचांगp4)
			: "r"(va), "r"(*reg_addr), "0"(0));
		अगर (error)
			जाओ give_sigsegv;
		वापस;

	शेष:
		/* What inकाष्ठाion were you trying to use, exactly?  */
		जाओ give_sigbus;
	पूर्ण

	/* Only पूर्णांकeger loads should get here; everyone अन्यथा वापसs early. */
	अगर (reg == 30)
		wrusp(fake_reg);
	वापस;

give_sigsegv:
	regs->pc -= 4;  /* make pc poपूर्णांक to faulting insn */

	/* We need to replicate some of the logic in mm/fault.c,
	   since we करोn't have access to the fault code in the
	   exception handling वापस path.  */
	अगर ((अचिन्हित दीर्घ)va >= TASK_SIZE)
		si_code = SEGV_ACCERR;
	अन्यथा अणु
		काष्ठा mm_काष्ठा *mm = current->mm;
		mmap_पढ़ो_lock(mm);
		अगर (find_vma(mm, (अचिन्हित दीर्घ)va))
			si_code = SEGV_ACCERR;
		अन्यथा
			si_code = SEGV_MAPERR;
		mmap_पढ़ो_unlock(mm);
	पूर्ण
	send_sig_fault(संक_अंश, si_code, va, 0, current);
	वापस;

give_sigbus:
	regs->pc -= 4;
	send_sig_fault(SIGBUS, BUS_ADRALN, va, 0, current);
	वापस;
पूर्ण

व्योम
trap_init(व्योम)
अणु
	/* Tell PAL-code what global poपूर्णांकer we want in the kernel.  */
	रेजिस्टर अचिन्हित दीर्घ gptr __यंत्र__("$29");
	wrkgp(gptr);

	/* Hack क्रम Multia (UDB) and JENSEN: some of their SRMs have
	   a bug in the handling of the opDEC fault.  Fix it up अगर so.  */
	अगर (implver() == IMPLVER_EV4)
		opDEC_check();

	wrent(entArith, 1);
	wrent(entMM, 2);
	wrent(entIF, 3);
	wrent(entUna, 4);
	wrent(entSys, 5);
	wrent(entDbg, 6);
पूर्ण
