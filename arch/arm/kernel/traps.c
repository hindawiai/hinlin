<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/traps.c
 *
 *  Copyright (C) 1995-2009 Russell King
 *  Fragments that appear the same as linux/arch/i386/kernel/traps.c (C) Linus Torvalds
 *
 *  'traps.c' handles hardware exceptions after we have saved some state in
 *  'linux/arch/arm/lib/traps.S'.  Mostly a debugging aid, but will probably
 *  समाप्त the offending process.
 */
#समावेश <linux/संकेत.स>
#समावेश <linux/personality.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/kexec.h>
#समावेश <linux/bug.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/irq.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/tls.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/opcodes.h>


अटल स्थिर अक्षर *handler[]= अणु
	"prefetch abort",
	"data abort",
	"address exception",
	"interrupt",
	"undefined instruction",
पूर्ण;

व्योम *vectors_page;

#अगर_घोषित CONFIG_DEBUG_USER
अचिन्हित पूर्णांक user_debug;

अटल पूर्णांक __init user_debug_setup(अक्षर *str)
अणु
	get_option(&str, &user_debug);
	वापस 1;
पूर्ण
__setup("user_debug=", user_debug_setup);
#पूर्ण_अगर

अटल व्योम dump_mem(स्थिर अक्षर *, स्थिर अक्षर *, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

व्योम dump_backtrace_entry(अचिन्हित दीर्घ where, अचिन्हित दीर्घ from,
			  अचिन्हित दीर्घ frame, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ end = frame + 4 + माप(काष्ठा pt_regs);

#अगर_घोषित CONFIG_KALLSYMS
	prपूर्णांकk("%s[<%08lx>] (%ps) from [<%08lx>] (%pS)\n",
		loglvl, where, (व्योम *)where, from, (व्योम *)from);
#अन्यथा
	prपूर्णांकk("%sFunction entered at [<%08lx>] from [<%08lx>]\n",
		loglvl, where, from);
#पूर्ण_अगर

	अगर (in_entry_text(from) && end <= ALIGN(frame, THREAD_SIZE))
		dump_mem(loglvl, "Exception stack", frame + 4, end);
पूर्ण

व्योम dump_backtrace_sपंचांग(u32 *stack, u32 inकाष्ठाion, स्थिर अक्षर *loglvl)
अणु
	अक्षर str[80], *p;
	अचिन्हित पूर्णांक x;
	पूर्णांक reg;

	क्रम (reg = 10, x = 0, p = str; reg >= 0; reg--) अणु
		अगर (inकाष्ठाion & BIT(reg)) अणु
			p += प्र_लिखो(p, " r%d:%08x", reg, *stack--);
			अगर (++x == 6) अणु
				x = 0;
				p = str;
				prपूर्णांकk("%s%s\n", loglvl, str);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (p != str)
		prपूर्णांकk("%s%s\n", loglvl, str);
पूर्ण

#अगर_अघोषित CONFIG_ARM_UNWIND
/*
 * Stack poपूर्णांकers should always be within the kernels view of
 * physical memory.  If it is not there, then we can't dump
 * out any inक्रमmation relating to the stack.
 */
अटल पूर्णांक verअगरy_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (sp < PAGE_OFFSET ||
	    (sp > (अचिन्हित दीर्घ)high_memory && high_memory != शून्य))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Dump out the contents of some memory nicely...
 */
अटल व्योम dump_mem(स्थिर अक्षर *lvl, स्थिर अक्षर *str, अचिन्हित दीर्घ bottom,
		     अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ first;
	mm_segment_t fs;
	पूर्णांक i;

	/*
	 * We need to चयन to kernel mode so that we can use __get_user
	 * to safely पढ़ो from kernel space.  Note that we now dump the
	 * code first, just in हाल the backtrace समाप्तs us.
	 */
	fs = get_fs();
	set_fs(KERNEL_DS);

	prपूर्णांकk("%s%s(0x%08lx to 0x%08lx)\n", lvl, str, bottom, top);

	क्रम (first = bottom & ~31; first < top; first += 32) अणु
		अचिन्हित दीर्घ p;
		अक्षर str[माप(" 12345678") * 8 + 1];

		स_रखो(str, ' ', माप(str));
		str[माप(str) - 1] = '\0';

		क्रम (p = first, i = 0; i < 8 && p < top; i++, p += 4) अणु
			अगर (p >= bottom && p < top) अणु
				अचिन्हित दीर्घ val;
				अगर (__get_user(val, (अचिन्हित दीर्घ *)p) == 0)
					प्र_लिखो(str + i * 9, " %08lx", val);
				अन्यथा
					प्र_लिखो(str + i * 9, " ????????");
			पूर्ण
		पूर्ण
		prपूर्णांकk("%s%04lx:%s\n", lvl, first & 0xffff, str);
	पूर्ण

	set_fs(fs);
पूर्ण

अटल व्योम __dump_instr(स्थिर अक्षर *lvl, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = inकाष्ठाion_poपूर्णांकer(regs);
	स्थिर पूर्णांक thumb = thumb_mode(regs);
	स्थिर पूर्णांक width = thumb ? 4 : 8;
	अक्षर str[माप("00000000 ") * 5 + 2 + 1], *p = str;
	पूर्णांक i;

	/*
	 * Note that we now dump the code first, just in हाल the backtrace
	 * समाप्तs us.
	 */

	क्रम (i = -4; i < 1 + !!thumb; i++) अणु
		अचिन्हित पूर्णांक val, bad;

		अगर (thumb)
			bad = get_user(val, &((u16 *)addr)[i]);
		अन्यथा
			bad = get_user(val, &((u32 *)addr)[i]);

		अगर (!bad)
			p += प्र_लिखो(p, i == 0 ? "(%0*x) " : "%0*x ",
					width, val);
		अन्यथा अणु
			p += प्र_लिखो(p, "bad PC value");
			अवरोध;
		पूर्ण
	पूर्ण
	prपूर्णांकk("%sCode: %s\n", lvl, str);
पूर्ण

अटल व्योम dump_instr(स्थिर अक्षर *lvl, काष्ठा pt_regs *regs)
अणु
	mm_segment_t fs;

	अगर (!user_mode(regs)) अणु
		fs = get_fs();
		set_fs(KERNEL_DS);
		__dump_instr(lvl, regs);
		set_fs(fs);
	पूर्ण अन्यथा अणु
		__dump_instr(lvl, regs);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARM_UNWIND
अटल अंतरभूत व्योम dump_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *tsk,
				  स्थिर अक्षर *loglvl)
अणु
	unwind_backtrace(regs, tsk, loglvl);
पूर्ण
#अन्यथा
अटल व्योम dump_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *tsk,
			   स्थिर अक्षर *loglvl)
अणु
	अचिन्हित पूर्णांक fp, mode;
	पूर्णांक ok = 1;

	prपूर्णांकk("%sBacktrace: ", loglvl);

	अगर (!tsk)
		tsk = current;

	अगर (regs) अणु
		fp = frame_poपूर्णांकer(regs);
		mode = processor_mode(regs);
	पूर्ण अन्यथा अगर (tsk != current) अणु
		fp = thपढ़ो_saved_fp(tsk);
		mode = 0x10;
	पूर्ण अन्यथा अणु
		यंत्र("mov %0, fp" : "=r" (fp) : : "cc");
		mode = 0x10;
	पूर्ण

	अगर (!fp) अणु
		pr_cont("no frame pointer");
		ok = 0;
	पूर्ण अन्यथा अगर (verअगरy_stack(fp)) अणु
		pr_cont("invalid frame pointer 0x%08x", fp);
		ok = 0;
	पूर्ण अन्यथा अगर (fp < (अचिन्हित दीर्घ)end_of_stack(tsk))
		pr_cont("frame pointer underflow");
	pr_cont("\n");

	अगर (ok)
		c_backtrace(fp, mode, loglvl);
पूर्ण
#पूर्ण_अगर

व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	dump_backtrace(शून्य, tsk, loglvl);
	barrier();
पूर्ण

#अगर_घोषित CONFIG_PREEMPT
#घोषणा S_PREEMPT " PREEMPT"
#या_अगर defined(CONFIG_PREEMPT_RT)
#घोषणा S_PREEMPT " PREEMPT_RT"
#अन्यथा
#घोषणा S_PREEMPT ""
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
#घोषणा S_SMP " SMP"
#अन्यथा
#घोषणा S_SMP ""
#पूर्ण_अगर
#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा S_ISA " THUMB2"
#अन्यथा
#घोषणा S_ISA " ARM"
#पूर्ण_अगर

अटल पूर्णांक __die(स्थिर अक्षर *str, पूर्णांक err, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	अटल पूर्णांक die_counter;
	पूर्णांक ret;

	pr_emerg("Internal error: %s: %x [#%d]" S_PREEMPT S_SMP S_ISA "\n",
	         str, err, ++die_counter);

	/* trap and error numbers are mostly meaningless on ARM */
	ret = notअगरy_die(DIE_OOPS, str, regs, err, tsk->thपढ़ो.trap_no, संक_अंश);
	अगर (ret == NOTIFY_STOP)
		वापस 1;

	prपूर्णांक_modules();
	__show_regs(regs);
	__show_regs_alloc_मुक्त(regs);
	pr_emerg("Process %.*s (pid: %d, stack limit = 0x%p)\n",
		 TASK_COMM_LEN, tsk->comm, task_pid_nr(tsk), end_of_stack(tsk));

	अगर (!user_mode(regs) || in_पूर्णांकerrupt()) अणु
		dump_mem(KERN_EMERG, "Stack: ", regs->ARM_sp,
			 THREAD_SIZE + (अचिन्हित दीर्घ)task_stack_page(tsk));
		dump_backtrace(regs, tsk, KERN_EMERG);
		dump_instr(KERN_EMERG, regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल arch_spinlock_t die_lock = __ARCH_SPIN_LOCK_UNLOCKED;
अटल पूर्णांक die_owner = -1;
अटल अचिन्हित पूर्णांक die_nest_count;

अटल अचिन्हित दीर्घ oops_begin(व्योम)
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

अटल व्योम oops_end(अचिन्हित दीर्घ flags, काष्ठा pt_regs *regs, पूर्णांक signr)
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

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");
	अगर (panic_on_oops)
		panic("Fatal exception");
	अगर (signr)
		करो_निकास(signr);
पूर्ण

/*
 * This function is रक्षित against re-entrancy.
 */
व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, पूर्णांक err)
अणु
	क्रमागत bug_trap_type bug_type = BUG_TRAP_TYPE_NONE;
	अचिन्हित दीर्घ flags = oops_begin();
	पूर्णांक sig = संक_अंश;

	अगर (!user_mode(regs))
		bug_type = report_bug(regs->ARM_pc, regs);
	अगर (bug_type != BUG_TRAP_TYPE_NONE)
		str = "Oops - BUG";

	अगर (__die(str, err, regs))
		sig = 0;

	oops_end(flags, regs, sig);
पूर्ण

व्योम arm_notअगरy_die(स्थिर अक्षर *str, काष्ठा pt_regs *regs,
		पूर्णांक signo, पूर्णांक si_code, व्योम __user *addr,
		अचिन्हित दीर्घ err, अचिन्हित दीर्घ trap)
अणु
	अगर (user_mode(regs)) अणु
		current->thपढ़ो.error_code = err;
		current->thपढ़ो.trap_no = trap;

		क्रमce_sig_fault(signo, si_code, addr);
	पूर्ण अन्यथा अणु
		die(str, regs, err);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_GENERIC_BUG

पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ pc)
अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	u16 bkpt;
	u16 insn = __opcode_to_mem_thumb16(BUG_INSTR_VALUE);
#अन्यथा
	u32 bkpt;
	u32 insn = __opcode_to_mem_arm(BUG_INSTR_VALUE);
#पूर्ण_अगर

	अगर (get_kernel_nofault(bkpt, (व्योम *)pc))
		वापस 0;

	वापस bkpt == insn;
पूर्ण

#पूर्ण_अगर

अटल LIST_HEAD(undef_hook);
अटल DEFINE_RAW_SPINLOCK(undef_lock);

व्योम रेजिस्टर_undef_hook(काष्ठा undef_hook *hook)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_add(&hook->node, &undef_hook);
	raw_spin_unlock_irqrestore(&undef_lock, flags);
पूर्ण

व्योम unरेजिस्टर_undef_hook(काष्ठा undef_hook *hook)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_del(&hook->node);
	raw_spin_unlock_irqrestore(&undef_lock, flags);
पूर्ण

अटल nokprobe_अंतरभूत
पूर्णांक call_undef_hook(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	काष्ठा undef_hook *hook;
	अचिन्हित दीर्घ flags;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr) = शून्य;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_क्रम_each_entry(hook, &undef_hook, node)
		अगर ((instr & hook->instr_mask) == hook->instr_val &&
		    (regs->ARM_cpsr & hook->cpsr_mask) == hook->cpsr_val)
			fn = hook->fn;
	raw_spin_unlock_irqrestore(&undef_lock, flags);

	वापस fn ? fn(regs, instr) : 1;
पूर्ण

यंत्रlinkage व्योम करो_undefinstr(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक instr;
	व्योम __user *pc;

	pc = (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs);

	अगर (processor_mode(regs) == SVC_MODE) अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
		अगर (thumb_mode(regs)) अणु
			instr = __mem_to_opcode_thumb16(((u16 *)pc)[0]);
			अगर (is_wide_inकाष्ठाion(instr)) अणु
				u16 inst2;
				inst2 = __mem_to_opcode_thumb16(((u16 *)pc)[1]);
				instr = __opcode_thumb32_compose(instr, inst2);
			पूर्ण
		पूर्ण अन्यथा
#पूर्ण_अगर
			instr = __mem_to_opcode_arm(*(u32 *) pc);
	पूर्ण अन्यथा अगर (thumb_mode(regs)) अणु
		अगर (get_user(instr, (u16 __user *)pc))
			जाओ die_sig;
		instr = __mem_to_opcode_thumb16(instr);
		अगर (is_wide_inकाष्ठाion(instr)) अणु
			अचिन्हित पूर्णांक instr2;
			अगर (get_user(instr2, (u16 __user *)pc+1))
				जाओ die_sig;
			instr2 = __mem_to_opcode_thumb16(instr2);
			instr = __opcode_thumb32_compose(instr, instr2);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (get_user(instr, (u32 __user *)pc))
			जाओ die_sig;
		instr = __mem_to_opcode_arm(instr);
	पूर्ण

	अगर (call_undef_hook(regs, instr) == 0)
		वापस;

die_sig:
#अगर_घोषित CONFIG_DEBUG_USER
	अगर (user_debug & UDBG_UNDEFINED) अणु
		pr_info("%s (%d): undefined instruction: pc=%p\n",
			current->comm, task_pid_nr(current), pc);
		__show_regs(regs);
		dump_instr(KERN_INFO, regs);
	पूर्ण
#पूर्ण_अगर
	arm_notअगरy_die("Oops - undefined instruction", regs,
		       संक_अवैध, ILL_ILLOPC, pc, 0, 6);
पूर्ण
NOKPROBE_SYMBOL(करो_undefinstr)

/*
 * Handle FIQ similarly to NMI on x86 प्रणालीs.
 *
 * The runसमय environment क्रम NMIs is extremely restrictive
 * (NMIs can pre-empt critical sections meaning almost all locking is
 * क्रमbidden) meaning this शेष FIQ handling must only be used in
 * circumstances where non-maskability improves robustness, such as
 * watchकरोg or debug logic.
 *
 * This handler is not appropriate क्रम general purpose use in drivers
 * platक्रमm code and can be overrideen using set_fiq_handler.
 */
यंत्रlinkage व्योम __exception_irq_entry handle_fiq_as_nmi(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	nmi_enter();

	/* nop. FIQ handlers क्रम special arch/arm features can be added here. */

	nmi_निकास();

	set_irq_regs(old_regs);
पूर्ण

/*
 * bad_mode handles the impossible हाल in the vectors.  If you see one of
 * these, then it's extremely serious, and could mean you have buggy hardware.
 * It never वापसs, and never tries to sync.  We hope that we can at least
 * dump out some state inक्रमmation...
 */
यंत्रlinkage व्योम bad_mode(काष्ठा pt_regs *regs, पूर्णांक reason)
अणु
	console_verbose();

	pr_crit("Bad mode in %s handler detected\n", handler[reason]);

	die("Oops - bad mode", regs, 0);
	local_irq_disable();
	panic("bad mode");
पूर्ण

अटल पूर्णांक bad_syscall(पूर्णांक n, काष्ठा pt_regs *regs)
अणु
	अगर ((current->personality & PER_MASK) != PER_LINUX) अणु
		send_sig(संक_अंश, current, 1);
		वापस regs->ARM_r0;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_USER
	अगर (user_debug & UDBG_SYSCALL) अणु
		pr_err("[%d] %s: obsolete system call %08x.\n",
			task_pid_nr(current), current->comm, n);
		dump_instr(KERN_ERR, regs);
	पूर्ण
#पूर्ण_अगर

	arm_notअगरy_die("Oops - bad syscall", regs, संक_अवैध, ILL_ILLTRP,
		       (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs) -
			 (thumb_mode(regs) ? 2 : 4),
		       n, 0);

	वापस regs->ARM_r0;
पूर्ण

अटल अंतरभूत पूर्णांक
__करो_cache_op(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक ret;

	करो अणु
		अचिन्हित दीर्घ chunk = min(PAGE_SIZE, end - start);

		अगर (fatal_संकेत_pending(current))
			वापस 0;

		ret = flush_icache_user_range(start, start + chunk);
		अगर (ret)
			वापस ret;

		cond_resched();
		start += chunk;
	पूर्ण जबतक (start < end);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
करो_cache_op(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक flags)
अणु
	अगर (end < start || flags)
		वापस -EINVAL;

	अगर (!access_ok(start, end - start))
		वापस -EFAULT;

	वापस __करो_cache_op(start, end);
पूर्ण

/*
 * Handle all unrecognised प्रणाली calls.
 *  0x9f0000 - 0x9fffff are some more esoteric प्रणाली calls
 */
#घोषणा NR(x) ((__ARM_NR_##x) - __ARM_NR_BASE)
यंत्रlinkage पूर्णांक arm_syscall(पूर्णांक no, काष्ठा pt_regs *regs)
अणु
	अगर ((no >> 16) != (__ARM_NR_BASE>> 16))
		वापस bad_syscall(no, regs);

	चयन (no & 0xffff) अणु
	हाल 0: /* branch through 0 */
		arm_notअगरy_die("branch through zero", regs,
			       संक_अंश, SEGV_MAPERR, शून्य, 0, 0);
		वापस 0;

	हाल NR(अवरोधpoपूर्णांक): /* SWI BREAK_POINT */
		regs->ARM_pc -= thumb_mode(regs) ? 2 : 4;
		ptrace_अवरोध(regs);
		वापस regs->ARM_r0;

	/*
	 * Flush a region from भव address 'r0' to virtual address 'r1'
	 * _exclusive_.  There is no alignment requirement on either address;
	 * user space करोes not need to know the hardware cache layout.
	 *
	 * r2 contains flags.  It should ALWAYS be passed as ZERO until it
	 * is defined to be something अन्यथा.  For now we ignore it, but may
	 * the fires of hell burn in your belly अगर you अवरोध this rule. ;)
	 *
	 * (at a later date, we may want to allow this call to not flush
	 * various aspects of the cache.  Passing '0' will guarantee that
	 * everything necessary माला_लो flushed to मुख्यtain consistency in
	 * the specअगरied region).
	 */
	हाल NR(cacheflush):
		वापस करो_cache_op(regs->ARM_r0, regs->ARM_r1, regs->ARM_r2);

	हाल NR(usr26):
		अगर (!(elf_hwcap & HWCAP_26BIT))
			अवरोध;
		regs->ARM_cpsr &= ~MODE32_BIT;
		वापस regs->ARM_r0;

	हाल NR(usr32):
		अगर (!(elf_hwcap & HWCAP_26BIT))
			अवरोध;
		regs->ARM_cpsr |= MODE32_BIT;
		वापस regs->ARM_r0;

	हाल NR(set_tls):
		set_tls(regs->ARM_r0);
		वापस 0;

	हाल NR(get_tls):
		वापस current_thपढ़ो_info()->tp_value[0];

	शेष:
		/* Calls 9f00xx..9f07ff are defined to वापस -ENOSYS
		   अगर not implemented, rather than raising संक_अवैध.  This
		   way the calling program can gracefully determine whether
		   a feature is supported.  */
		अगर ((no & 0xffff) <= 0x7ff)
			वापस -ENOSYS;
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_DEBUG_USER
	/*
	 * experience shows that these seem to indicate that
	 * something catastrophic has happened
	 */
	अगर (user_debug & UDBG_SYSCALL) अणु
		pr_err("[%d] %s: arm syscall %d\n",
		       task_pid_nr(current), current->comm, no);
		dump_instr(KERN_ERR, regs);
		अगर (user_mode(regs)) अणु
			__show_regs(regs);
			c_backtrace(frame_poपूर्णांकer(regs), processor_mode(regs), KERN_ERR);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	arm_notअगरy_die("Oops - bad syscall(2)", regs, संक_अवैध, ILL_ILLTRP,
		       (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs) -
			 (thumb_mode(regs) ? 2 : 4),
		       no, 0);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TLS_REG_EMUL

/*
 * We might be running on an ARMv6+ processor which should have the TLS
 * रेजिस्टर but क्रम some reason we can't use it, or maybe an SMP प्रणाली
 * using a pre-ARMv6 processor (there are apparently a few prototypes like
 * that in existence) and thereक्रमe access to that रेजिस्टर must be
 * emulated.
 */

अटल पूर्णांक get_tp_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	पूर्णांक reg = (instr >> 12) & 15;
	अगर (reg == 15)
		वापस 1;
	regs->uregs[reg] = current_thपढ़ो_info()->tp_value[0];
	regs->ARM_pc += 4;
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook arm_mrc_hook = अणु
	.instr_mask	= 0x0fff0fff,
	.instr_val	= 0x0e1d0f70,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= 0,
	.fn		= get_tp_trap,
पूर्ण;

अटल पूर्णांक __init arm_mrc_hook_init(व्योम)
अणु
	रेजिस्टर_undef_hook(&arm_mrc_hook);
	वापस 0;
पूर्ण

late_initcall(arm_mrc_hook_init);

#पूर्ण_अगर

/*
 * A data पात trap was taken, but we did not handle the inकाष्ठाion.
 * Try to पात the user program, or panic अगर it was the kernel.
 */
यंत्रlinkage व्योम
baddataपात(पूर्णांक code, अचिन्हित दीर्घ instr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = inकाष्ठाion_poपूर्णांकer(regs);

#अगर_घोषित CONFIG_DEBUG_USER
	अगर (user_debug & UDBG_BADABORT) अणु
		pr_err("8<--- cut here ---\n");
		pr_err("[%d] %s: bad data abort: code %d instr 0x%08lx\n",
		       task_pid_nr(current), current->comm, code, instr);
		dump_instr(KERN_ERR, regs);
		show_pte(KERN_ERR, current->mm, addr);
	पूर्ण
#पूर्ण_अगर

	arm_notअगरy_die("unknown data abort code", regs,
		       संक_अवैध, ILL_ILLOPC, (व्योम __user *)addr, instr, 0);
पूर्ण

व्योम __पढ़ोग_लिखो_bug(स्थिर अक्षर *fn)
अणु
	pr_err("%s called, but not implemented\n", fn);
	BUG();
पूर्ण
EXPORT_SYMBOL(__पढ़ोग_लिखो_bug);

व्योम __pte_error(स्थिर अक्षर *file, पूर्णांक line, pte_t pte)
अणु
	pr_err("%s:%d: bad pte %08llx.\n", file, line, (दीर्घ दीर्घ)pte_val(pte));
पूर्ण

व्योम __pmd_error(स्थिर अक्षर *file, पूर्णांक line, pmd_t pmd)
अणु
	pr_err("%s:%d: bad pmd %08llx.\n", file, line, (दीर्घ दीर्घ)pmd_val(pmd));
पूर्ण

व्योम __pgd_error(स्थिर अक्षर *file, पूर्णांक line, pgd_t pgd)
अणु
	pr_err("%s:%d: bad pgd %08llx.\n", file, line, (दीर्घ दीर्घ)pgd_val(pgd));
पूर्ण

यंत्रlinkage व्योम __भाग0(व्योम)
अणु
	pr_err("Division by zero in kernel.\n");
	dump_stack();
पूर्ण
EXPORT_SYMBOL(__भाग0);

व्योम पात(व्योम)
अणु
	BUG();

	/* अगर that करोesn't समाप्त us, halt */
	panic("Oops failed to kill thread");
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	वापस;
पूर्ण

#अगर_घोषित CONFIG_KUSER_HELPERS
अटल व्योम __init kuser_init(व्योम *vectors)
अणु
	बाह्य अक्षर __kuser_helper_start[], __kuser_helper_end[];
	पूर्णांक kuser_sz = __kuser_helper_end - __kuser_helper_start;

	स_नकल(vectors + 0x1000 - kuser_sz, __kuser_helper_start, kuser_sz);

	/*
	 * vectors + 0xfe0 = __kuser_get_tls
	 * vectors + 0xfe8 = hardware TLS inकाष्ठाion at 0xffff0fe8
	 */
	अगर (tls_emu || has_tls_reg)
		स_नकल(vectors + 0xfe0, vectors + 0xfe8, 4);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init kuser_init(व्योम *vectors)
अणु
पूर्ण
#पूर्ण_अगर

व्योम __init early_trap_init(व्योम *vectors_base)
अणु
#अगर_अघोषित CONFIG_CPU_V7M
	अचिन्हित दीर्घ vectors = (अचिन्हित दीर्घ)vectors_base;
	बाह्य अक्षर __stubs_start[], __stubs_end[];
	बाह्य अक्षर __vectors_start[], __vectors_end[];
	अचिन्हित i;

	vectors_page = vectors_base;

	/*
	 * Poison the vectors page with an undefined inकाष्ठाion.  This
	 * inकाष्ठाion is chosen to be undefined क्रम both ARM and Thumb
	 * ISAs.  The Thumb version is an undefined inकाष्ठाion with a
	 * branch back to the undefined inकाष्ठाion.
	 */
	क्रम (i = 0; i < PAGE_SIZE / माप(u32); i++)
		((u32 *)vectors_base)[i] = 0xe7fddef1;

	/*
	 * Copy the vectors, stubs and kuser helpers (in entry-armv.S)
	 * पूर्णांकo the vector page, mapped at 0xffff0000, and ensure these
	 * are visible to the inकाष्ठाion stream.
	 */
	स_नकल((व्योम *)vectors, __vectors_start, __vectors_end - __vectors_start);
	स_नकल((व्योम *)vectors + 0x1000, __stubs_start, __stubs_end - __stubs_start);

	kuser_init(vectors_base);

	flush_icache_range(vectors, vectors + PAGE_SIZE * 2);
#अन्यथा /* अगरndef CONFIG_CPU_V7M */
	/*
	 * on V7-M there is no need to copy the vector table to a dedicated
	 * memory area. The address is configurable and so a table in the kernel
	 * image can be used.
	 */
#पूर्ण_अगर
पूर्ण
