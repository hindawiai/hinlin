<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sparc/kernel/traps.c
 *
 * Copyright 1995, 2008 David S. Miller (davem@davemloft.net)
 * Copyright 2000 Jakub Jelinek (jakub@redhat.com)
 */

/*
 * I hate traps on the sparc, grrr...
 */

#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/traps.h>

#समावेश "entry.h"
#समावेश "kernel.h"

/* #घोषणा TRAP_DEBUG */

अटल व्योम inकाष्ठाion_dump(अचिन्हित दीर्घ *pc)
अणु
	पूर्णांक i;
	
	अगर((((अचिन्हित दीर्घ) pc) & 3))
                वापस;

	क्रम(i = -3; i < 6; i++)
		prपूर्णांकk("%c%08lx%c",i?' ':'<',pc[i],i?' ':'>');
	prपूर्णांकk("\n");
पूर्ण

#घोषणा __SAVE __यंत्र__ __अस्थिर__("save %sp, -0x40, %sp\n\t")
#घोषणा __RESTORE __यंत्र__ __अस्थिर__("restore %g0, %g0, %g0\n\t")

व्योम __noवापस die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs)
अणु
	अटल पूर्णांक die_counter;
	पूर्णांक count = 0;

	/* Amuse the user. */
	prपूर्णांकk(
"              \\|/ ____ \\|/\n"
"              \"@'/ ,. \\`@\"\n"
"              /_| \\__/ |_\\\n"
"                 \\__U_/\n");

	prपूर्णांकk("%s(%d): %s [#%d]\n", current->comm, task_pid_nr(current), str, ++die_counter);
	show_regs(regs);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);

	__SAVE; __SAVE; __SAVE; __SAVE;
	__SAVE; __SAVE; __SAVE; __SAVE;
	__RESTORE; __RESTORE; __RESTORE; __RESTORE;
	__RESTORE; __RESTORE; __RESTORE; __RESTORE;

	अणु
		काष्ठा reg_winकरोw32 *rw = (काष्ठा reg_winकरोw32 *)regs->u_regs[UREG_FP];

		/* Stop the back trace when we hit userland or we
		 * find some badly aligned kernel stack. Set an upper
		 * bound in हाल our stack is trashed and we loop.
		 */
		जबतक(rw					&&
		      count++ < 30				&&
                      (((अचिन्हित दीर्घ) rw) >= PAGE_OFFSET)	&&
		      !(((अचिन्हित दीर्घ) rw) & 0x7)) अणु
			prपूर्णांकk("Caller[%08lx]: %pS\n", rw->ins[7],
			       (व्योम *) rw->ins[7]);
			rw = (काष्ठा reg_winकरोw32 *)rw->ins[6];
		पूर्ण
	पूर्ण
	prपूर्णांकk("Instruction DUMP:");
	inकाष्ठाion_dump ((अचिन्हित दीर्घ *) regs->pc);
	अगर(regs->psr & PSR_PS)
		करो_निकास(SIGKILL);
	करो_निकास(संक_अंश);
पूर्ण

व्योम करो_hw_पूर्णांकerrupt(काष्ठा pt_regs *regs, अचिन्हित दीर्घ type)
अणु
	अगर(type < 0x80) अणु
		/* Sun OS's puke from bad traps, Linux survives! */
		prपूर्णांकk("Unimplemented Sparc TRAP, type = %02lx\n", type);
		die_अगर_kernel("Whee... Hello Mr. Penguin", regs);
	पूर्ण	

	अगर(regs->psr & PSR_PS)
		die_अगर_kernel("Kernel bad trap", regs);

	क्रमce_sig_fault(संक_अवैध, ILL_ILLTRP,
			(व्योम __user *)regs->pc, type - 0x80);
पूर्ण

व्योम करो_illegal_inकाष्ठाion(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
			    अचिन्हित दीर्घ psr)
अणु
	अगर(psr & PSR_PS)
		die_अगर_kernel("Kernel illegal instruction", regs);
#अगर_घोषित TRAP_DEBUG
	prपूर्णांकk("Ill instr. at pc=%08lx instruction is %08lx\n",
	       regs->pc, *(अचिन्हित दीर्घ *)regs->pc);
#पूर्ण_अगर

	send_sig_fault(संक_अवैध, ILL_ILLOPC, (व्योम __user *)pc, 0, current);
पूर्ण

व्योम करो_priv_inकाष्ठाion(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
			 अचिन्हित दीर्घ psr)
अणु
	अगर(psr & PSR_PS)
		die_अगर_kernel("Penguin instruction from Penguin mode??!?!", regs);
	send_sig_fault(संक_अवैध, ILL_PRVOPC, (व्योम __user *)pc, 0, current);
पूर्ण

/* XXX User may want to be allowed to करो this. XXX */

व्योम करो_memaccess_unaligned(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
			    अचिन्हित दीर्घ psr)
अणु
	अगर(regs->psr & PSR_PS) अणु
		prपूर्णांकk("KERNEL MNA at pc %08lx npc %08lx called by %08lx\n", pc, npc,
		       regs->u_regs[UREG_RETPC]);
		die_अगर_kernel("BOGUS", regs);
		/* die_अगर_kernel("Kernel MNA access", regs); */
	पूर्ण
#अगर 0
	show_regs (regs);
	inकाष्ठाion_dump ((अचिन्हित दीर्घ *) regs->pc);
	prपूर्णांकk ("do_MNA!\n");
#पूर्ण_अगर
	send_sig_fault(SIGBUS, BUS_ADRALN,
		       /* FIXME: Should dig out mna address */ (व्योम *)0,
		       0, current);
पूर्ण

अटल अचिन्हित दीर्घ init_fsr = 0x0UL;
अटल अचिन्हित दीर्घ init_fregs[32] __attribute__ ((aligned (8))) =
                अणु ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL,
		  ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL,
		  ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL,
		  ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL, ~0UL पूर्ण;

व्योम करो_fpd_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
		 अचिन्हित दीर्घ psr)
अणु
	/* Sanity check... */
	अगर(psr & PSR_PS)
		die_अगर_kernel("Kernel gets FloatingPenguinUnit disabled trap", regs);

	put_psr(get_psr() | PSR_EF);    /* Allow FPU ops. */
	regs->psr |= PSR_EF;
#अगर_अघोषित CONFIG_SMP
	अगर(last_task_used_math == current)
		वापस;
	अगर(last_task_used_math) अणु
		/* Other processes fpu state, save away */
		काष्ठा task_काष्ठा *fptask = last_task_used_math;
		fpsave(&fptask->thपढ़ो.भग्न_regs[0], &fptask->thपढ़ो.fsr,
		       &fptask->thपढ़ो.fpqueue[0], &fptask->thपढ़ो.fpqdepth);
	पूर्ण
	last_task_used_math = current;
	अगर(used_math()) अणु
		fpload(&current->thपढ़ो.भग्न_regs[0], &current->thपढ़ो.fsr);
	पूर्ण अन्यथा अणु
		/* Set initial sane state. */
		fpload(&init_fregs[0], &init_fsr);
		set_used_math();
	पूर्ण
#अन्यथा
	अगर(!used_math()) अणु
		fpload(&init_fregs[0], &init_fsr);
		set_used_math();
	पूर्ण अन्यथा अणु
		fpload(&current->thपढ़ो.भग्न_regs[0], &current->thपढ़ो.fsr);
	पूर्ण
	set_thपढ़ो_flag(TIF_USEDFPU);
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ fake_regs[32] __attribute__ ((aligned (8)));
अटल अचिन्हित दीर्घ fake_fsr;
अटल अचिन्हित दीर्घ fake_queue[32] __attribute__ ((aligned (8)));
अटल अचिन्हित दीर्घ fake_depth;

व्योम करो_fpe_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
		 अचिन्हित दीर्घ psr)
अणु
	अटल पूर्णांक calls;
	अचिन्हित दीर्घ fsr;
	पूर्णांक ret = 0;
	पूर्णांक code;
#अगर_अघोषित CONFIG_SMP
	काष्ठा task_काष्ठा *fpt = last_task_used_math;
#अन्यथा
	काष्ठा task_काष्ठा *fpt = current;
#पूर्ण_अगर
	put_psr(get_psr() | PSR_EF);
	/* If nobody owns the fpu right now, just clear the
	 * error पूर्णांकo our fake अटल buffer and hope it करोn't
	 * happen again.  Thank you crashme...
	 */
#अगर_अघोषित CONFIG_SMP
	अगर(!fpt) अणु
#अन्यथा
	अगर (!test_tsk_thपढ़ो_flag(fpt, TIF_USEDFPU)) अणु
#पूर्ण_अगर
		fpsave(&fake_regs[0], &fake_fsr, &fake_queue[0], &fake_depth);
		regs->psr &= ~PSR_EF;
		वापस;
	पूर्ण
	fpsave(&fpt->thपढ़ो.भग्न_regs[0], &fpt->thपढ़ो.fsr,
	       &fpt->thपढ़ो.fpqueue[0], &fpt->thपढ़ो.fpqdepth);
#अगर_घोषित DEBUG_FPU
	prपूर्णांकk("Hmm, FP exception, fsr was %016lx\n", fpt->thपढ़ो.fsr);
#पूर्ण_अगर

	चयन ((fpt->thपढ़ो.fsr & 0x1c000)) अणु
	/* चयन on the contents of the ftt [भग्नing poपूर्णांक trap type] field */
#अगर_घोषित DEBUG_FPU
	हाल (1 << 14):
		prपूर्णांकk("IEEE_754_exception\n");
		अवरोध;
#पूर्ण_अगर
	हाल (2 << 14):  /* unfinished_FPop (underflow & co) */
	हाल (3 << 14):  /* unimplemented_FPop (quad stuff, maybe वर्ग_मूल) */
		ret = करो_mathemu(regs, fpt);
		अवरोध;
#अगर_घोषित DEBUG_FPU
	हाल (4 << 14):
		prपूर्णांकk("sequence_error (OS bug...)\n");
		अवरोध;
	हाल (5 << 14):
		prपूर्णांकk("hardware_error (uhoh!)\n");
		अवरोध;
	हाल (6 << 14):
		prपूर्णांकk("invalid_fp_register (user error)\n");
		अवरोध;
#पूर्ण_अगर /* DEBUG_FPU */
	पूर्ण
	/* If we successfully emulated the FPop, we pretend the trap never happened :-> */
	अगर (ret) अणु
		fpload(&current->thपढ़ो.भग्न_regs[0], &current->thपढ़ो.fsr);
		वापस;
	पूर्ण
	/* nope, better संक_भ_त्रुटि the offending process... */
	       
#अगर_घोषित CONFIG_SMP
	clear_tsk_thपढ़ो_flag(fpt, TIF_USEDFPU);
#पूर्ण_अगर
	अगर(psr & PSR_PS) अणु
		/* The first fsr store/load we tried trapped,
		 * the second one will not (we hope).
		 */
		prपूर्णांकk("WARNING: FPU exception from kernel mode. at pc=%08lx\n",
		       regs->pc);
		regs->pc = regs->npc;
		regs->npc += 4;
		calls++;
		अगर(calls > 2)
			die_अगर_kernel("Too many Penguin-FPU traps from kernel mode",
				      regs);
		वापस;
	पूर्ण

	fsr = fpt->thपढ़ो.fsr;
	code = FPE_FLTUNK;
	अगर ((fsr & 0x1c000) == (1 << 14)) अणु
		अगर (fsr & 0x10)
			code = FPE_FLTINV;
		अन्यथा अगर (fsr & 0x08)
			code = FPE_FLTOVF;
		अन्यथा अगर (fsr & 0x04)
			code = FPE_FLTUND;
		अन्यथा अगर (fsr & 0x02)
			code = FPE_FLTDIV;
		अन्यथा अगर (fsr & 0x01)
			code = FPE_FLTRES;
	पूर्ण
	send_sig_fault(संक_भ_त्रुटि, code, (व्योम __user *)pc, 0, fpt);
#अगर_अघोषित CONFIG_SMP
	last_task_used_math = शून्य;
#पूर्ण_अगर
	regs->psr &= ~PSR_EF;
	अगर(calls > 0)
		calls=0;
पूर्ण

व्योम handle_tag_overflow(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
			 अचिन्हित दीर्घ psr)
अणु
	अगर(psr & PSR_PS)
		die_अगर_kernel("Penguin overflow trap from kernel mode", regs);
	send_sig_fault(SIGEMT, EMT_TAGOVF, (व्योम __user *)pc, 0, current);
पूर्ण

व्योम handle_watchpoपूर्णांक(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
		       अचिन्हित दीर्घ psr)
अणु
#अगर_घोषित TRAP_DEBUG
	prपूर्णांकk("Watchpoint detected at PC %08lx NPC %08lx PSR %08lx\n",
	       pc, npc, psr);
#पूर्ण_अगर
	अगर(psr & PSR_PS)
		panic("Tell me what a watchpoint trap is, and I'll then deal "
		      "with such a beast...");
पूर्ण

व्योम handle_reg_access(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
		       अचिन्हित दीर्घ psr)
अणु
#अगर_घोषित TRAP_DEBUG
	prपूर्णांकk("Register Access Exception at PC %08lx NPC %08lx PSR %08lx\n",
	       pc, npc, psr);
#पूर्ण_अगर
	क्रमce_sig_fault(SIGBUS, BUS_OBJERR, (व्योम __user *)pc, 0);
पूर्ण

व्योम handle_cp_disabled(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
			अचिन्हित दीर्घ psr)
अणु
	send_sig_fault(संक_अवैध, ILL_COPROC, (व्योम __user *)pc, 0, current);
पूर्ण

व्योम handle_cp_exception(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
			 अचिन्हित दीर्घ psr)
अणु
#अगर_घोषित TRAP_DEBUG
	prपूर्णांकk("Co-Processor Exception at PC %08lx NPC %08lx PSR %08lx\n",
	       pc, npc, psr);
#पूर्ण_अगर
	send_sig_fault(संक_अवैध, ILL_COPROC, (व्योम __user *)pc, 0, current);
पूर्ण

व्योम handle_hw_भागzero(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ npc,
		       अचिन्हित दीर्घ psr)
अणु
	send_sig_fault(संक_भ_त्रुटि, FPE_INTDIV, (व्योम __user *)pc, 0, current);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
व्योम करो_BUG(स्थिर अक्षर *file, पूर्णांक line)
अणु
        // bust_spinlocks(1);   XXX Not in our original BUG()
        prपूर्णांकk("kernel BUG at %s:%d!\n", file, line);
पूर्ण
EXPORT_SYMBOL(करो_BUG);
#पूर्ण_अगर

/* Since we have our mappings set up, on multiprocessors we can spin them
 * up here so that समयr पूर्णांकerrupts work during initialization.
 */

व्योम trap_init(व्योम)
अणु
	बाह्य व्योम thपढ़ो_info_offsets_are_bolixed_pete(व्योम);

	/* Force linker to barf अगर mismatched */
	अगर (TI_UWINMASK    != दुरत्व(काष्ठा thपढ़ो_info, uwinmask) ||
	    TI_TASK        != दुरत्व(काष्ठा thपढ़ो_info, task) ||
	    TI_FLAGS       != दुरत्व(काष्ठा thपढ़ो_info, flags) ||
	    TI_CPU         != दुरत्व(काष्ठा thपढ़ो_info, cpu) ||
	    TI_PREEMPT     != दुरत्व(काष्ठा thपढ़ो_info, preempt_count) ||
	    TI_SOFTIRQ     != दुरत्व(काष्ठा thपढ़ो_info, softirq_count) ||
	    TI_HARसूचीQ     != दुरत्व(काष्ठा thपढ़ो_info, hardirq_count) ||
	    TI_KSP         != दुरत्व(काष्ठा thपढ़ो_info, ksp) ||
	    TI_KPC         != दुरत्व(काष्ठा thपढ़ो_info, kpc) ||
	    TI_KPSR        != दुरत्व(काष्ठा thपढ़ो_info, kpsr) ||
	    TI_KWIM        != दुरत्व(काष्ठा thपढ़ो_info, kwim) ||
	    TI_REG_WINDOW  != दुरत्व(काष्ठा thपढ़ो_info, reg_winकरोw) ||
	    TI_RWIN_SPTRS  != दुरत्व(काष्ठा thपढ़ो_info, rwbuf_stkptrs) ||
	    TI_W_SAVED     != दुरत्व(काष्ठा thपढ़ो_info, w_saved))
		thपढ़ो_info_offsets_are_bolixed_pete();

	/* Attach to the address space of init_task. */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	/* NOTE: Other cpus have this करोne as they are started
	 *       up on SMP.
	 */
पूर्ण
