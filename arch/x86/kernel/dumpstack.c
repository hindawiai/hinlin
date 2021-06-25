<शैली गुरु>
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen, SuSE Lअसल
 */
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/utsname.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kexec.h>
#समावेश <linux/bug.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kasan.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>

पूर्णांक panic_on_unrecovered_nmi;
पूर्णांक panic_on_io_nmi;
अटल पूर्णांक die_counter;

अटल काष्ठा pt_regs exec_summary_regs;

bool noinstr in_task_stack(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
			   काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ *begin = task_stack_page(task);
	अचिन्हित दीर्घ *end   = task_stack_page(task) + THREAD_SIZE;

	अगर (stack < begin || stack >= end)
		वापस false;

	info->type	= STACK_TYPE_TASK;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= शून्य;

	वापस true;
पूर्ण

/* Called from get_stack_info_noinstr - so must be noinstr too */
bool noinstr in_entry_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info)
अणु
	काष्ठा entry_stack *ss = cpu_entry_stack(smp_processor_id());

	व्योम *begin = ss;
	व्योम *end = ss + 1;

	अगर ((व्योम *)stack < begin || (व्योम *)stack >= end)
		वापस false;

	info->type	= STACK_TYPE_ENTRY;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= शून्य;

	वापस true;
पूर्ण

अटल व्योम prपूर्णांकk_stack_address(अचिन्हित दीर्घ address, पूर्णांक reliable,
				 स्थिर अक्षर *log_lvl)
अणु
	touch_nmi_watchकरोg();
	prपूर्णांकk("%s %s%pB\n", log_lvl, reliable ? "" : "? ", (व्योम *)address);
पूर्ण

अटल पूर्णांक copy_code(काष्ठा pt_regs *regs, u8 *buf, अचिन्हित दीर्घ src,
		     अचिन्हित पूर्णांक nbytes)
अणु
	अगर (!user_mode(regs))
		वापस copy_from_kernel_nofault(buf, (u8 *)src, nbytes);

	/* The user space code from other tasks cannot be accessed. */
	अगर (regs != task_pt_regs(current))
		वापस -EPERM;
	/*
	 * Make sure userspace isn't trying to trick us पूर्णांकo dumping kernel
	 * memory by poपूर्णांकing the userspace inकाष्ठाion poपूर्णांकer at it.
	 */
	अगर (__chk_range_not_ok(src, nbytes, TASK_SIZE_MAX))
		वापस -EINVAL;

	/*
	 * Even अगर named copy_from_user_nmi() this can be invoked from
	 * other contexts and will not try to resolve a pagefault, which is
	 * the correct thing to करो here as this code can be called from any
	 * context.
	 */
	वापस copy_from_user_nmi(buf, (व्योम __user *)src, nbytes);
पूर्ण

/*
 * There are a couple of reasons क्रम the 2/3rd prologue, courtesy of Linus:
 *
 * In हाल where we करोn't have the exact kernel image (which, अगर we did, we can
 * simply disassemble and navigate to the RIP), the purpose of the bigger
 * prologue is to have more context and to be able to correlate the code from
 * the dअगरferent toolchains better.
 *
 * In addition, it helps in recreating the रेजिस्टर allocation of the failing
 * kernel and thus make sense of the रेजिस्टर dump.
 *
 * What is more, the additional complication of a variable length insn arch like
 * x86 warrants having दीर्घer byte sequence beक्रमe rIP so that the disassembler
 * can "sync" up properly and find inकाष्ठाion boundaries when decoding the
 * opcode bytes.
 *
 * Thus, the 2/3rds prologue and 64 byte OPCODE_बफ_मानE is just a अक्रमom
 * guesstimate in attempt to achieve all of the above.
 */
व्योम show_opcodes(काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl)
अणु
#घोषणा PROLOGUE_SIZE 42
#घोषणा EPILOGUE_SIZE 21
#घोषणा OPCODE_बफ_मानE (PROLOGUE_SIZE + 1 + EPILOGUE_SIZE)
	u8 opcodes[OPCODE_बफ_मानE];
	अचिन्हित दीर्घ prologue = regs->ip - PROLOGUE_SIZE;

	चयन (copy_code(regs, opcodes, prologue, माप(opcodes))) अणु
	हाल 0:
		prपूर्णांकk("%sCode: %" __stringअगरy(PROLOGUE_SIZE) "ph <%02x> %"
		       __stringअगरy(EPILOGUE_SIZE) "ph\n", loglvl, opcodes,
		       opcodes[PROLOGUE_SIZE], opcodes + PROLOGUE_SIZE + 1);
		अवरोध;
	हाल -EPERM:
		/* No access to the user space stack of other tasks. Ignore. */
		अवरोध;
	शेष:
		prपूर्णांकk("%sCode: Unable to access opcode bytes at RIP 0x%lx.\n",
		       loglvl, prologue);
		अवरोध;
	पूर्ण
पूर्ण

व्योम show_ip(काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl)
अणु
#अगर_घोषित CONFIG_X86_32
	prपूर्णांकk("%sEIP: %pS\n", loglvl, (व्योम *)regs->ip);
#अन्यथा
	prपूर्णांकk("%sRIP: %04x:%pS\n", loglvl, (पूर्णांक)regs->cs, (व्योम *)regs->ip);
#पूर्ण_अगर
	show_opcodes(regs, loglvl);
पूर्ण

व्योम show_iret_regs(काष्ठा pt_regs *regs, स्थिर अक्षर *log_lvl)
अणु
	show_ip(regs, log_lvl);
	prपूर्णांकk("%sRSP: %04x:%016lx EFLAGS: %08lx", log_lvl, (पूर्णांक)regs->ss,
		regs->sp, regs->flags);
पूर्ण

अटल व्योम show_regs_अगर_on_stack(काष्ठा stack_info *info, काष्ठा pt_regs *regs,
				  bool partial, स्थिर अक्षर *log_lvl)
अणु
	/*
	 * These on_stack() checks aren't strictly necessary: the unwind code
	 * has alपढ़ोy validated the 'regs' poपूर्णांकer.  The checks are करोne क्रम
	 * ordering reasons: अगर the रेजिस्टरs are on the next stack, we करोn't
	 * want to prपूर्णांक them out yet.  Otherwise they'll be shown as part of
	 * the wrong stack.  Later, when show_trace_log_lvl() चयनes to the
	 * next stack, this function will be called again with the same regs so
	 * they can be prपूर्णांकed in the right context.
	 */
	अगर (!partial && on_stack(info, regs, माप(*regs))) अणु
		__show_regs(regs, SHOW_REGS_SHORT, log_lvl);

	पूर्ण अन्यथा अगर (partial && on_stack(info, (व्योम *)regs + IRET_FRAME_OFFSET,
				       IRET_FRAME_SIZE)) अणु
		/*
		 * When an पूर्णांकerrupt or exception occurs in entry code, the
		 * full pt_regs might not have been saved yet.  In that हाल
		 * just prपूर्णांक the iret frame.
		 */
		show_iret_regs(regs, log_lvl);
	पूर्ण
पूर्ण

अटल व्योम show_trace_log_lvl(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
			अचिन्हित दीर्घ *stack, स्थिर अक्षर *log_lvl)
अणु
	काष्ठा unwind_state state;
	काष्ठा stack_info stack_info = अणु0पूर्ण;
	अचिन्हित दीर्घ visit_mask = 0;
	पूर्णांक graph_idx = 0;
	bool partial = false;

	prपूर्णांकk("%sCall Trace:\n", log_lvl);

	unwind_start(&state, task, regs, stack);
	stack = stack ? : get_stack_poपूर्णांकer(task, regs);
	regs = unwind_get_entry_regs(&state, &partial);

	/*
	 * Iterate through the stacks, starting with the current stack poपूर्णांकer.
	 * Each stack has a poपूर्णांकer to the next one.
	 *
	 * x86-64 can have several stacks:
	 * - task stack
	 * - पूर्णांकerrupt stack
	 * - HW exception stacks (द्विगुन fault, nmi, debug, mce)
	 * - entry stack
	 *
	 * x86-32 can have up to four stacks:
	 * - task stack
	 * - softirq stack
	 * - hardirq stack
	 * - entry stack
	 */
	क्रम ( ; stack; stack = PTR_ALIGN(stack_info.next_sp, माप(दीर्घ))) अणु
		स्थिर अक्षर *stack_name;

		अगर (get_stack_info(stack, task, &stack_info, &visit_mask)) अणु
			/*
			 * We weren't on a valid stack.  It's possible that
			 * we overflowed a valid stack पूर्णांकo a guard page.
			 * See अगर the next page up is valid so that we can
			 * generate some kind of backtrace अगर this happens.
			 */
			stack = (अचिन्हित दीर्घ *)PAGE_ALIGN((अचिन्हित दीर्घ)stack);
			अगर (get_stack_info(stack, task, &stack_info, &visit_mask))
				अवरोध;
		पूर्ण

		stack_name = stack_type_name(stack_info.type);
		अगर (stack_name)
			prपूर्णांकk("%s <%s>\n", log_lvl, stack_name);

		अगर (regs)
			show_regs_अगर_on_stack(&stack_info, regs, partial, log_lvl);

		/*
		 * Scan the stack, prपूर्णांकing any text addresses we find.  At the
		 * same समय, follow proper stack frames with the unwinder.
		 *
		 * Addresses found during the scan which are not reported by
		 * the unwinder are considered to be additional clues which are
		 * someबार useful क्रम debugging and are prefixed with '?'.
		 * This also serves as a failsafe option in हाल the unwinder
		 * goes off in the weeds.
		 */
		क्रम (; stack < stack_info.end; stack++) अणु
			अचिन्हित दीर्घ real_addr;
			पूर्णांक reliable = 0;
			अचिन्हित दीर्घ addr = READ_ONCE_NOCHECK(*stack);
			अचिन्हित दीर्घ *ret_addr_p =
				unwind_get_वापस_address_ptr(&state);

			अगर (!__kernel_text_address(addr))
				जारी;

			/*
			 * Don't prपूर्णांक regs->ip again अगर it was alपढ़ोy prपूर्णांकed
			 * by show_regs_अगर_on_stack().
			 */
			अगर (regs && stack == &regs->ip)
				जाओ next;

			अगर (stack == ret_addr_p)
				reliable = 1;

			/*
			 * When function graph tracing is enabled क्रम a
			 * function, its वापस address on the stack is
			 * replaced with the address of an ftrace handler
			 * (वापस_to_handler).  In that हाल, beक्रमe prपूर्णांकing
			 * the "real" address, we want to prपूर्णांक the handler
			 * address as an "unreliable" hपूर्णांक that function graph
			 * tracing was involved.
			 */
			real_addr = ftrace_graph_ret_addr(task, &graph_idx,
							  addr, stack);
			अगर (real_addr != addr)
				prपूर्णांकk_stack_address(addr, 0, log_lvl);
			prपूर्णांकk_stack_address(real_addr, reliable, log_lvl);

			अगर (!reliable)
				जारी;

next:
			/*
			 * Get the next frame from the unwinder.  No need to
			 * check क्रम an error: अगर anything goes wrong, the rest
			 * of the addresses will just be prपूर्णांकed as unreliable.
			 */
			unwind_next_frame(&state);

			/* अगर the frame has entry regs, prपूर्णांक them */
			regs = unwind_get_entry_regs(&state, &partial);
			अगर (regs)
				show_regs_अगर_on_stack(&stack_info, regs, partial, log_lvl);
		पूर्ण

		अगर (stack_name)
			prपूर्णांकk("%s </%s>\n", log_lvl, stack_name);
	पूर्ण
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp,
		       स्थिर अक्षर *loglvl)
अणु
	task = task ? : current;

	/*
	 * Stack frames below this one aren't interesting.  Don't show them
	 * अगर we're prपूर्णांकing क्रम %current.
	 */
	अगर (!sp && task == current)
		sp = get_stack_poपूर्णांकer(current, शून्य);

	show_trace_log_lvl(task, शून्य, sp, loglvl);
पूर्ण

व्योम show_stack_regs(काष्ठा pt_regs *regs)
अणु
	show_trace_log_lvl(current, regs, शून्य, KERN_DEFAULT);
पूर्ण

अटल arch_spinlock_t die_lock = __ARCH_SPIN_LOCK_UNLOCKED;
अटल पूर्णांक die_owner = -1;
अटल अचिन्हित पूर्णांक die_nest_count;

अचिन्हित दीर्घ oops_begin(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	oops_enter();

	/* racy, but better than risking deadlock. */
	raw_local_irq_save(flags);
	cpu = smp_processor_id();
	अगर (!arch_spin_trylock(&die_lock)) अणु
		अगर (cpu == die_owner)
			/* nested oops. should stop eventually */;
		अन्यथा
			arch_spin_lock(&die_lock);
	पूर्ण
	die_nest_count++;
	die_owner = cpu;
	console_verbose();
	bust_spinlocks(1);
	वापस flags;
पूर्ण
NOKPROBE_SYMBOL(oops_begin);

व्योम __noवापस शुरुआत_stack_करो_निकास(पूर्णांक signr);

व्योम oops_end(अचिन्हित दीर्घ flags, काष्ठा pt_regs *regs, पूर्णांक signr)
अणु
	अगर (regs && kexec_should_crash(current))
		crash_kexec(regs);

	bust_spinlocks(0);
	die_owner = -1;
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	die_nest_count--;
	अगर (!die_nest_count)
		/* Nest count reaches zero, release the lock. */
		arch_spin_unlock(&die_lock);
	raw_local_irq_restore(flags);
	oops_निकास();

	/* Executive summary in हाल the oops scrolled away */
	__show_regs(&exec_summary_regs, SHOW_REGS_ALL, KERN_DEFAULT);

	अगर (!signr)
		वापस;
	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");
	अगर (panic_on_oops)
		panic("Fatal exception");

	/*
	 * We're not going to वापस, but we might be on an IST stack or
	 * have very little stack space left.  Rewind the stack and समाप्त
	 * the task.
	 * Beक्रमe we शुरुआत the stack, we have to tell KASAN that we're going to
	 * reuse the task stack and that existing poisons are invalid.
	 */
	kasan_unpoison_task_stack(current);
	शुरुआत_stack_करो_निकास(signr);
पूर्ण
NOKPROBE_SYMBOL(oops_end);

अटल व्योम __die_header(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	स्थिर अक्षर *pr = "";

	/* Save the regs of the first oops क्रम the executive summary later. */
	अगर (!die_counter)
		exec_summary_regs = *regs;

	अगर (IS_ENABLED(CONFIG_PREEMPTION))
		pr = IS_ENABLED(CONFIG_PREEMPT_RT) ? " PREEMPT_RT" : " PREEMPT";

	prपूर्णांकk(KERN_DEFAULT
	       "%s: %04lx [#%d]%s%s%s%s%s\n", str, err & 0xffff, ++die_counter,
	       pr,
	       IS_ENABLED(CONFIG_SMP)     ? " SMP"             : "",
	       debug_pagealloc_enabled()  ? " DEBUG_PAGEALLOC" : "",
	       IS_ENABLED(CONFIG_KASAN)   ? " KASAN"           : "",
	       IS_ENABLED(CONFIG_PAGE_TABLE_ISOLATION) ?
	       (boot_cpu_has(X86_FEATURE_PTI) ? " PTI" : " NOPTI") : "");
पूर्ण
NOKPROBE_SYMBOL(__die_header);

अटल पूर्णांक __die_body(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	show_regs(regs);
	prपूर्णांक_modules();

	अगर (notअगरy_die(DIE_OOPS, str, regs, err,
			current->thपढ़ो.trap_nr, संक_अंश) == NOTIFY_STOP)
		वापस 1;

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(__die_body);

पूर्णांक __die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	__die_header(str, regs, err);
	वापस __die_body(str, regs, err);
पूर्ण
NOKPROBE_SYMBOL(__die);

/*
 * This is gone through when something in the kernel has करोne something bad
 * and is about to be terminated:
 */
व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अचिन्हित दीर्घ flags = oops_begin();
	पूर्णांक sig = संक_अंश;

	अगर (__die(str, regs, err))
		sig = 0;
	oops_end(flags, regs, sig);
पूर्ण

व्योम die_addr(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err, दीर्घ gp_addr)
अणु
	अचिन्हित दीर्घ flags = oops_begin();
	पूर्णांक sig = संक_अंश;

	__die_header(str, regs, err);
	अगर (gp_addr)
		kasan_non_canonical_hook(gp_addr);
	अगर (__die_body(str, regs, err))
		sig = 0;
	oops_end(flags, regs, sig);
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	क्रमागत show_regs_mode prपूर्णांक_kernel_regs;

	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	prपूर्णांक_kernel_regs = user_mode(regs) ? SHOW_REGS_USER : SHOW_REGS_ALL;
	__show_regs(regs, prपूर्णांक_kernel_regs, KERN_DEFAULT);

	/*
	 * When in-kernel, we also prपूर्णांक out the stack at the समय of the fault..
	 */
	अगर (!user_mode(regs))
		show_trace_log_lvl(current, regs, शून्य, KERN_DEFAULT);
पूर्ण
