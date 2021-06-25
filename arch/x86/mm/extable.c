<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/debug.h>
#समावेश <xen/xen.h>

#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/sev.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/kdebug.h>

प्रकार bool (*ex_handler_t)(स्थिर काष्ठा exception_table_entry *,
			    काष्ठा pt_regs *, पूर्णांक, अचिन्हित दीर्घ,
			    अचिन्हित दीर्घ);

अटल अंतरभूत अचिन्हित दीर्घ
ex_fixup_addr(स्थिर काष्ठा exception_table_entry *x)
अणु
	वापस (अचिन्हित दीर्घ)&x->fixup + x->fixup;
पूर्ण
अटल अंतरभूत ex_handler_t
ex_fixup_handler(स्थिर काष्ठा exception_table_entry *x)
अणु
	वापस (ex_handler_t)((अचिन्हित दीर्घ)&x->handler + x->handler);
पूर्ण

__visible bool ex_handler_शेष(स्थिर काष्ठा exception_table_entry *fixup,
				  काष्ठा pt_regs *regs, पूर्णांक trapnr,
				  अचिन्हित दीर्घ error_code,
				  अचिन्हित दीर्घ fault_addr)
अणु
	regs->ip = ex_fixup_addr(fixup);
	वापस true;
पूर्ण
EXPORT_SYMBOL(ex_handler_शेष);

__visible bool ex_handler_fault(स्थिर काष्ठा exception_table_entry *fixup,
				काष्ठा pt_regs *regs, पूर्णांक trapnr,
				अचिन्हित दीर्घ error_code,
				अचिन्हित दीर्घ fault_addr)
अणु
	regs->ip = ex_fixup_addr(fixup);
	regs->ax = trapnr;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ex_handler_fault);

/*
 * Handler क्रम when we fail to restore a task's FPU state.  We should never get
 * here because the FPU state of a task using the FPU (task->thपढ़ो.fpu.state)
 * should always be valid.  However, past bugs have allowed userspace to set
 * reserved bits in the XSAVE area using PTRACE_SETREGSET or sys_rt_sigवापस().
 * These caused XRSTOR to fail when चयनing to the task, leaking the FPU
 * रेजिस्टरs of the task previously executing on the CPU.  Mitigate this class
 * of vulnerability by restoring from the initial state (essentially, zeroing
 * out all the FPU रेजिस्टरs) अगर we can't restore from the task's FPU state.
 */
__visible bool ex_handler_fprestore(स्थिर काष्ठा exception_table_entry *fixup,
				    काष्ठा pt_regs *regs, पूर्णांक trapnr,
				    अचिन्हित दीर्घ error_code,
				    अचिन्हित दीर्घ fault_addr)
अणु
	regs->ip = ex_fixup_addr(fixup);

	WARN_ONCE(1, "Bad FPU state detected at %pB, reinitializing FPU registers.",
		  (व्योम *)inकाष्ठाion_poपूर्णांकer(regs));

	__copy_kernel_to_fpregs(&init_fpstate, -1);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ex_handler_fprestore);

__visible bool ex_handler_uaccess(स्थिर काष्ठा exception_table_entry *fixup,
				  काष्ठा pt_regs *regs, पूर्णांक trapnr,
				  अचिन्हित दीर्घ error_code,
				  अचिन्हित दीर्घ fault_addr)
अणु
	WARN_ONCE(trapnr == X86_TRAP_GP, "General protection fault in user access. Non-canonical address?");
	regs->ip = ex_fixup_addr(fixup);
	वापस true;
पूर्ण
EXPORT_SYMBOL(ex_handler_uaccess);

__visible bool ex_handler_copy(स्थिर काष्ठा exception_table_entry *fixup,
			       काष्ठा pt_regs *regs, पूर्णांक trapnr,
			       अचिन्हित दीर्घ error_code,
			       अचिन्हित दीर्घ fault_addr)
अणु
	WARN_ONCE(trapnr == X86_TRAP_GP, "General protection fault in user access. Non-canonical address?");
	regs->ip = ex_fixup_addr(fixup);
	regs->ax = trapnr;
	वापस true;
पूर्ण
EXPORT_SYMBOL(ex_handler_copy);

__visible bool ex_handler_rdmsr_unsafe(स्थिर काष्ठा exception_table_entry *fixup,
				       काष्ठा pt_regs *regs, पूर्णांक trapnr,
				       अचिन्हित दीर्घ error_code,
				       अचिन्हित दीर्घ fault_addr)
अणु
	अगर (pr_warn_once("unchecked MSR access error: RDMSR from 0x%x at rIP: 0x%lx (%pS)\n",
			 (अचिन्हित पूर्णांक)regs->cx, regs->ip, (व्योम *)regs->ip))
		show_stack_regs(regs);

	/* Pretend that the पढ़ो succeeded and वापसed 0. */
	regs->ip = ex_fixup_addr(fixup);
	regs->ax = 0;
	regs->dx = 0;
	वापस true;
पूर्ण
EXPORT_SYMBOL(ex_handler_rdmsr_unsafe);

__visible bool ex_handler_wrmsr_unsafe(स्थिर काष्ठा exception_table_entry *fixup,
				       काष्ठा pt_regs *regs, पूर्णांक trapnr,
				       अचिन्हित दीर्घ error_code,
				       अचिन्हित दीर्घ fault_addr)
अणु
	अगर (pr_warn_once("unchecked MSR access error: WRMSR to 0x%x (tried to write 0x%08x%08x) at rIP: 0x%lx (%pS)\n",
			 (अचिन्हित पूर्णांक)regs->cx, (अचिन्हित पूर्णांक)regs->dx,
			 (अचिन्हित पूर्णांक)regs->ax,  regs->ip, (व्योम *)regs->ip))
		show_stack_regs(regs);

	/* Pretend that the ग_लिखो succeeded. */
	regs->ip = ex_fixup_addr(fixup);
	वापस true;
पूर्ण
EXPORT_SYMBOL(ex_handler_wrmsr_unsafe);

__visible bool ex_handler_clear_fs(स्थिर काष्ठा exception_table_entry *fixup,
				   काष्ठा pt_regs *regs, पूर्णांक trapnr,
				   अचिन्हित दीर्घ error_code,
				   अचिन्हित दीर्घ fault_addr)
अणु
	अगर (अटल_cpu_has(X86_BUG_शून्य_SEG))
		यंत्र अस्थिर ("mov %0, %%fs" : : "rm" (__USER_DS));
	यंत्र अस्थिर ("mov %0, %%fs" : : "rm" (0));
	वापस ex_handler_शेष(fixup, regs, trapnr, error_code, fault_addr);
पूर्ण
EXPORT_SYMBOL(ex_handler_clear_fs);

क्रमागत handler_type ex_get_fault_handler_type(अचिन्हित दीर्घ ip)
अणु
	स्थिर काष्ठा exception_table_entry *e;
	ex_handler_t handler;

	e = search_exception_tables(ip);
	अगर (!e)
		वापस EX_HANDLER_NONE;
	handler = ex_fixup_handler(e);
	अगर (handler == ex_handler_fault)
		वापस EX_HANDLER_FAULT;
	अन्यथा अगर (handler == ex_handler_uaccess || handler == ex_handler_copy)
		वापस EX_HANDLER_UACCESS;
	अन्यथा
		वापस EX_HANDLER_OTHER;
पूर्ण

पूर्णांक fixup_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr, अचिन्हित दीर्घ error_code,
		    अचिन्हित दीर्घ fault_addr)
अणु
	स्थिर काष्ठा exception_table_entry *e;
	ex_handler_t handler;

#अगर_घोषित CONFIG_PNPBIOS
	अगर (unlikely(SEGMENT_IS_PNP_CODE(regs->cs))) अणु
		बाह्य u32 pnp_bios_fault_eip, pnp_bios_fault_esp;
		बाह्य u32 pnp_bios_is_utter_crap;
		pnp_bios_is_utter_crap = 1;
		prपूर्णांकk(KERN_CRIT "PNPBIOS fault.. attempting recovery.\n");
		__यंत्र__ अस्थिर(
			"movl %0, %%esp\n\t"
			"jmp *%1\n\t"
			: : "g" (pnp_bios_fault_esp), "g" (pnp_bios_fault_eip));
		panic("do_trap: can't hit this");
	पूर्ण
#पूर्ण_अगर

	e = search_exception_tables(regs->ip);
	अगर (!e)
		वापस 0;

	handler = ex_fixup_handler(e);
	वापस handler(e, regs, trapnr, error_code, fault_addr);
पूर्ण

बाह्य अचिन्हित पूर्णांक early_recursion_flag;

/* Restricted version used during very early boot */
व्योम __init early_fixup_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	/* Ignore early NMIs. */
	अगर (trapnr == X86_TRAP_NMI)
		वापस;

	अगर (early_recursion_flag > 2)
		जाओ halt_loop;

	/*
	 * Old CPUs leave the high bits of CS on the stack
	 * undefined.  I'm not sure which CPUs करो this, but at least
	 * the 486 DX works this way.
	 * Xen pv करोमुख्यs are not using the शेष __KERNEL_CS.
	 */
	अगर (!xen_pv_करोमुख्य() && regs->cs != __KERNEL_CS)
		जाओ fail;

	/*
	 * The full exception fixup machinery is available as soon as
	 * the early IDT is loaded.  This means that it is the
	 * responsibility of extable users to either function correctly
	 * when handlers are invoked early or to simply aव्योम causing
	 * exceptions beक्रमe they're पढ़ोy to handle them.
	 *
	 * This is better than filtering which handlers can be used,
	 * because refusing to call a handler here is guaranteed to
	 * result in a hard-to-debug panic.
	 *
	 * Keep in mind that not all vectors actually get here.  Early
	 * page faults, क्रम example, are special.
	 */
	अगर (fixup_exception(regs, trapnr, regs->orig_ax, 0))
		वापस;

	अगर (trapnr == X86_TRAP_UD) अणु
		अगर (report_bug(regs->ip, regs) == BUG_TRAP_TYPE_WARN) अणु
			/* Skip the ud2. */
			regs->ip += LEN_UD2;
			वापस;
		पूर्ण

		/*
		 * If this was a BUG and report_bug वापसs or अगर this
		 * was just a normal #UD, we want to जारी onward and
		 * crash.
		 */
	पूर्ण

fail:
	early_prपूर्णांकk("PANIC: early exception 0x%02x IP %lx:%lx error %lx cr2 0x%lx\n",
		     (अचिन्हित)trapnr, (अचिन्हित दीर्घ)regs->cs, regs->ip,
		     regs->orig_ax, पढ़ो_cr2());

	show_regs(regs);

halt_loop:
	जबतक (true)
		halt();
पूर्ण
