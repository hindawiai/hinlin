<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/module.h>
#समावेश <linux/personality.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/fpu.h>

#समावेश <linux/ptrace.h>
#समावेश <nds32_पूर्णांकrinsic.h>

बाह्य व्योम show_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);

/*
 * Dump out the contents of some memory nicely...
 */
व्योम dump_mem(स्थिर अक्षर *lvl, अचिन्हित दीर्घ bottom, अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ first;
	पूर्णांक i;

	pr_emerg("%s(0x%08lx to 0x%08lx)\n", lvl, bottom, top);

	क्रम (first = bottom & ~31; first < top; first += 32) अणु
		अचिन्हित दीर्घ p;
		अक्षर str[माप(" 12345678") * 8 + 1];

		स_रखो(str, ' ', माप(str));
		str[माप(str) - 1] = '\0';

		क्रम (p = first, i = 0; i < 8 && p < top; i++, p += 4) अणु
			अगर (p >= bottom && p < top) अणु
				अचिन्हित दीर्घ val;

				अगर (get_kernel_nofault(val,
						(अचिन्हित दीर्घ *)p) == 0)
					प्र_लिखो(str + i * 9, " %08lx", val);
				अन्यथा
					प्र_लिखो(str + i * 9, " ????????");
			पूर्ण
		पूर्ण
		pr_emerg("%s%04lx:%s\n", lvl, first & 0xffff, str);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(dump_mem);

#घोषणा LOOP_TIMES (100)
अटल व्योम __dump(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *base_reg,
		   स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ ret_addr;
	पूर्णांक cnt = LOOP_TIMES, graph = 0;
	prपूर्णांकk("%sCall Trace:\n", loglvl);
	अगर (!IS_ENABLED(CONFIG_FRAME_POINTER)) अणु
		जबतक (!kstack_end(base_reg)) अणु
			ret_addr = *base_reg++;
			अगर (__kernel_text_address(ret_addr)) अणु
				ret_addr = ftrace_graph_ret_addr(
						tsk, &graph, ret_addr, शून्य);
				prपूर्णांक_ip_sym(loglvl, ret_addr);
			पूर्ण
			अगर (--cnt < 0)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (!kstack_end((व्योम *)base_reg) &&
		       !((अचिन्हित दीर्घ)base_reg & 0x3) &&
		       ((अचिन्हित दीर्घ)base_reg >= TASK_SIZE)) अणु
			अचिन्हित दीर्घ next_fp;
			ret_addr = base_reg[LP_OFFSET];
			next_fp = base_reg[FP_OFFSET];
			अगर (__kernel_text_address(ret_addr)) अणु

				ret_addr = ftrace_graph_ret_addr(
						tsk, &graph, ret_addr, शून्य);
				prपूर्णांक_ip_sym(loglvl, ret_addr);
			पूर्ण
			अगर (--cnt < 0)
				अवरोध;
			base_reg = (अचिन्हित दीर्घ *)next_fp;
		पूर्ण
	पूर्ण
	prपूर्णांकk("%s\n", loglvl);
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ *base_reg;

	अगर (!tsk)
		tsk = current;
	अगर (!IS_ENABLED(CONFIG_FRAME_POINTER)) अणु
		अगर (tsk != current)
			base_reg = (अचिन्हित दीर्घ *)(tsk->thपढ़ो.cpu_context.sp);
		अन्यथा
			__यंत्र__ __अस्थिर__("\tori\t%0, $sp, #0\n":"=r"(base_reg));
	पूर्ण अन्यथा अणु
		अगर (tsk != current)
			base_reg = (अचिन्हित दीर्घ *)(tsk->thपढ़ो.cpu_context.fp);
		अन्यथा
			__यंत्र__ __अस्थिर__("\tori\t%0, $fp, #0\n":"=r"(base_reg));
	पूर्ण
	__dump(tsk, base_reg, loglvl);
	barrier();
पूर्ण

DEFINE_SPINLOCK(die_lock);

/*
 * This function is रक्षित against re-entrancy.
 */
व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, पूर्णांक err)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	अटल पूर्णांक die_counter;

	console_verbose();
	spin_lock_irq(&die_lock);
	bust_spinlocks(1);

	pr_emerg("Internal error: %s: %x [#%d]\n", str, err, ++die_counter);
	prपूर्णांक_modules();
	pr_emerg("CPU: %i\n", smp_processor_id());
	show_regs(regs);
	pr_emerg("Process %s (pid: %d, stack limit = 0x%p)\n",
		 tsk->comm, tsk->pid, end_of_stack(tsk));

	अगर (!user_mode(regs) || in_पूर्णांकerrupt()) अणु
		dump_mem("Stack: ", regs->sp, (regs->sp + PAGE_SIZE) & PAGE_MASK);
		dump_stack();
	पूर्ण

	bust_spinlocks(0);
	spin_unlock_irq(&die_lock);
	करो_निकास(संक_अंश);
पूर्ण

EXPORT_SYMBOL(die);

व्योम die_अगर_kernel(स्थिर अक्षर *str, काष्ठा pt_regs *regs, पूर्णांक err)
अणु
	अगर (user_mode(regs))
		वापस;

	die(str, regs, err);
पूर्ण

पूर्णांक bad_syscall(पूर्णांक n, काष्ठा pt_regs *regs)
अणु
	अगर (current->personality != PER_LINUX) अणु
		send_sig(संक_अंश, current, 1);
		वापस regs->uregs[0];
	पूर्ण

	क्रमce_sig_fault(संक_अवैध, ILL_ILLTRP,
			(व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs) - 4);
	die_अगर_kernel("Oops - bad syscall", regs, n);
	वापस regs->uregs[0];
पूर्ण

व्योम __pte_error(स्थिर अक्षर *file, पूर्णांक line, अचिन्हित दीर्घ val)
अणु
	pr_emerg("%s:%d: bad pte %08lx.\n", file, line, val);
पूर्ण

व्योम __pmd_error(स्थिर अक्षर *file, पूर्णांक line, अचिन्हित दीर्घ val)
अणु
	pr_emerg("%s:%d: bad pmd %08lx.\n", file, line, val);
पूर्ण

व्योम __pgd_error(स्थिर अक्षर *file, पूर्णांक line, अचिन्हित दीर्घ val)
अणु
	pr_emerg("%s:%d: bad pgd %08lx.\n", file, line, val);
पूर्ण

बाह्य अक्षर *exception_vector, *exception_vector_end;
व्योम __init trap_init(व्योम)
अणु
	वापस;
पूर्ण

व्योम __init early_trap_init(व्योम)
अणु
	अचिन्हित दीर्घ ivb = 0;
	अचिन्हित दीर्घ base = PAGE_OFFSET;

	स_नकल((अचिन्हित दीर्घ *)base, (अचिन्हित दीर्घ *)&exception_vector,
	       ((अचिन्हित दीर्घ)&exception_vector_end -
		(अचिन्हित दीर्घ)&exception_vector));
	ivb = __nds32__mfsr(NDS32_SR_IVB);
	/* Check platक्रमm support. */
	अगर (((ivb & IVB_mskNIVIC) >> IVB_offNIVIC) < 2)
		panic
		    ("IVIC mode is not allowed on the platform with interrupt controller\n");
	__nds32__mtsr((ivb & ~IVB_mskESZ) | (IVB_valESZ16 << IVB_offESZ) |
		      IVB_BASE, NDS32_SR_IVB);
	__nds32__mtsr(INT_MASK_INITAIAL_VAL, NDS32_SR_INT_MASK);

	/*
	 * 0x800 = 128 vectors * 16byte.
	 * It should be enough to flush a page.
	 */
	cpu_cache_wbinval_page(base, true);
पूर्ण

अटल व्योम send_sigtrap(काष्ठा pt_regs *regs, पूर्णांक error_code, पूर्णांक si_code)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	tsk->thपढ़ो.trap_no = ENTRY_DEBUG_RELATED;
	tsk->thपढ़ो.error_code = error_code;

	क्रमce_sig_fault(SIGTRAP, si_code,
			(व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs));
पूर्ण

व्योम करो_debug_trap(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ addr,
		   अचिन्हित दीर्घ type, काष्ठा pt_regs *regs)
अणु
	अगर (notअगरy_die(DIE_OOPS, "Oops", regs, addr, type, SIGTRAP)
	    == NOTIFY_STOP)
		वापस;

	अगर (user_mode(regs)) अणु
		/* trap_संकेत */
		send_sigtrap(regs, 0, TRAP_BRKPT);
	पूर्ण अन्यथा अणु
		/* kernel_trap */
		अगर (!fixup_exception(regs))
			die("unexpected kernel_trap", regs, 0);
	पूर्ण
पूर्ण

व्योम unhandled_पूर्णांकerruption(काष्ठा pt_regs *regs)
अणु
	pr_emerg("unhandled_interruption\n");
	show_regs(regs);
	अगर (!user_mode(regs))
		करो_निकास(SIGKILL);
	क्रमce_sig(SIGKILL);
पूर्ण

व्योम unhandled_exceptions(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ type, काष्ठा pt_regs *regs)
अणु
	pr_emerg("Unhandled Exception: entry: %lx addr:%lx itype:%lx\n", entry,
		 addr, type);
	show_regs(regs);
	अगर (!user_mode(regs))
		करो_निकास(SIGKILL);
	क्रमce_sig(SIGKILL);
पूर्ण

बाह्य पूर्णांक करो_page_fault(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ addr,
			 अचिन्हित पूर्णांक error_code, काष्ठा pt_regs *regs);

/*
 * 2:DEF dispatch क्रम TLB MISC exception handler
*/

व्योम करो_dispatch_tlb_misc(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ type, काष्ठा pt_regs *regs)
अणु
	type = type & (ITYPE_mskINST | ITYPE_mskETYPE);
	अगर ((type & ITYPE_mskETYPE) < 5) अणु
		/* Permission exceptions */
		करो_page_fault(entry, addr, type, regs);
	पूर्ण अन्यथा
		unhandled_exceptions(entry, addr, type, regs);
पूर्ण

व्योम करो_revinsn(काष्ठा pt_regs *regs)
अणु
	pr_emerg("Reserved Instruction\n");
	show_regs(regs);
	अगर (!user_mode(regs))
		करो_निकास(संक_अवैध);
	क्रमce_sig(संक_अवैध);
पूर्ण

#अगर_घोषित CONFIG_ALIGNMENT_TRAP
बाह्य पूर्णांक unalign_access_mode;
बाह्य पूर्णांक करो_unaligned_access(अचिन्हित दीर्घ addr, काष्ठा pt_regs *regs);
#पूर्ण_अगर
व्योम करो_dispatch_general(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ itype, काष्ठा pt_regs *regs,
			 अचिन्हित दीर्घ oipc)
अणु
	अचिन्हित पूर्णांक swid = itype >> ITYPE_offSWID;
	अचिन्हित दीर्घ type = itype & (ITYPE_mskINST | ITYPE_mskETYPE);
	अगर (type == ETYPE_ALIGNMENT_CHECK) अणु
#अगर_घोषित CONFIG_ALIGNMENT_TRAP
		/* Alignment check */
		अगर (user_mode(regs) && unalign_access_mode) अणु
			पूर्णांक ret;
			ret = करो_unaligned_access(addr, regs);

			अगर (ret == 0)
				वापस;

			अगर (ret == -EFAULT)
				pr_emerg
				    ("Unhandled unaligned access exception\n");
		पूर्ण
#पूर्ण_अगर
		करो_page_fault(entry, addr, type, regs);
	पूर्ण अन्यथा अगर (type == ETYPE_RESERVED_INSTRUCTION) अणु
		/* Reserved inकाष्ठाion */
		करो_revinsn(regs);
	पूर्ण अन्यथा अगर (type == ETYPE_COPROCESSOR) अणु
		/* Coprocessor */
#अगर IS_ENABLED(CONFIG_FPU)
		अचिन्हित पूर्णांक fucop_exist = __nds32__mfsr(NDS32_SR_FUCOP_EXIST);
		अचिन्हित पूर्णांक cpid = ((itype & ITYPE_mskCPID) >> ITYPE_offCPID);

		अगर ((cpid == FPU_CPID) &&
		    (fucop_exist & FUCOP_EXIST_mskCP0ISFPU)) अणु
			अचिन्हित पूर्णांक subtype = (itype & ITYPE_mskSTYPE);

			अगर (true == करो_fpu_exception(subtype, regs))
				वापस;
		पूर्ण
#पूर्ण_अगर
		unhandled_exceptions(entry, addr, type, regs);
	पूर्ण अन्यथा अगर (type == ETYPE_TRAP && swid == SWID_RAISE_INTERRUPT_LEVEL) अणु
		/* trap, used on v3 EDM target debugging workaround */
		/*
		 * DIPC(OIPC) is passed as parameter beक्रमe
		 * पूर्णांकerrupt is enabled, so the DIPC will not be corrupted
		 * even though पूर्णांकerrupts are coming in
		 */
		/*
		 * 1. update ipc
		 * 2. update pt_regs ipc with oipc
		 * 3. update pt_regs ipsw (clear DEX)
		 */
		__यंत्र__ अस्थिर ("mtsr %0, $IPC\n\t"::"r" (oipc));
		regs->ipc = oipc;
		अगर (regs->pipsw & PSW_mskDEX) अणु
			pr_emerg
			    ("Nested Debug exception is possibly happened\n");
			pr_emerg("ipc:%08x pipc:%08x\n",
				 (अचिन्हित पूर्णांक)regs->ipc,
				 (अचिन्हित पूर्णांक)regs->pipc);
		पूर्ण
		करो_debug_trap(entry, addr, itype, regs);
		regs->ipsw &= ~PSW_mskDEX;
	पूर्ण अन्यथा
		unhandled_exceptions(entry, addr, type, regs);
पूर्ण
