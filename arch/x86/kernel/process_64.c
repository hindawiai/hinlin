<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1995  Linus Torvalds
 *
 *  Pentium III FXSR, SSE support
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 *
 *  X86-64 port
 *	Andi Kleen.
 *
 *	CPU hotplug support - ashok.raj@पूर्णांकel.com
 */

/*
 * This file handles the architecture-dependent parts of process handling..
 */

#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>
#समावेश <linux/user.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/prctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/ftrace.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/prctl.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/ia32.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/resctrl.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/fsgsbase.h>
#अगर_घोषित CONFIG_IA32_EMULATION
/* Not included via unistd.h */
#समावेश <यंत्र/unistd_32_ia32.h>
#पूर्ण_अगर

#समावेश "process.h"

/* Prपूर्णांकs also some state that isn't saved in the pt_regs */
व्योम __show_regs(काष्ठा pt_regs *regs, क्रमागत show_regs_mode mode,
		 स्थिर अक्षर *log_lvl)
अणु
	अचिन्हित दीर्घ cr0 = 0L, cr2 = 0L, cr3 = 0L, cr4 = 0L, fs, gs, shaकरोwgs;
	अचिन्हित दीर्घ d0, d1, d2, d3, d6, d7;
	अचिन्हित पूर्णांक fsindex, gsindex;
	अचिन्हित पूर्णांक ds, es;

	show_iret_regs(regs, log_lvl);

	अगर (regs->orig_ax != -1)
		pr_cont(" ORIG_RAX: %016lx\n", regs->orig_ax);
	अन्यथा
		pr_cont("\n");

	prपूर्णांकk("%sRAX: %016lx RBX: %016lx RCX: %016lx\n",
	       log_lvl, regs->ax, regs->bx, regs->cx);
	prपूर्णांकk("%sRDX: %016lx RSI: %016lx RDI: %016lx\n",
	       log_lvl, regs->dx, regs->si, regs->di);
	prपूर्णांकk("%sRBP: %016lx R08: %016lx R09: %016lx\n",
	       log_lvl, regs->bp, regs->r8, regs->r9);
	prपूर्णांकk("%sR10: %016lx R11: %016lx R12: %016lx\n",
	       log_lvl, regs->r10, regs->r11, regs->r12);
	prपूर्णांकk("%sR13: %016lx R14: %016lx R15: %016lx\n",
	       log_lvl, regs->r13, regs->r14, regs->r15);

	अगर (mode == SHOW_REGS_SHORT)
		वापस;

	अगर (mode == SHOW_REGS_USER) अणु
		rdmsrl(MSR_FS_BASE, fs);
		rdmsrl(MSR_KERNEL_GS_BASE, shaकरोwgs);
		prपूर्णांकk("%sFS:  %016lx GS:  %016lx\n",
		       log_lvl, fs, shaकरोwgs);
		वापस;
	पूर्ण

	यंत्र("movl %%ds,%0" : "=r" (ds));
	यंत्र("movl %%es,%0" : "=r" (es));
	यंत्र("movl %%fs,%0" : "=r" (fsindex));
	यंत्र("movl %%gs,%0" : "=r" (gsindex));

	rdmsrl(MSR_FS_BASE, fs);
	rdmsrl(MSR_GS_BASE, gs);
	rdmsrl(MSR_KERNEL_GS_BASE, shaकरोwgs);

	cr0 = पढ़ो_cr0();
	cr2 = पढ़ो_cr2();
	cr3 = __पढ़ो_cr3();
	cr4 = __पढ़ो_cr4();

	prपूर्णांकk("%sFS:  %016lx(%04x) GS:%016lx(%04x) knlGS:%016lx\n",
	       log_lvl, fs, fsindex, gs, gsindex, shaकरोwgs);
	prपूर्णांकk("%sCS:  %04lx DS: %04x ES: %04x CR0: %016lx\n",
		log_lvl, regs->cs, ds, es, cr0);
	prपूर्णांकk("%sCR2: %016lx CR3: %016lx CR4: %016lx\n",
		log_lvl, cr2, cr3, cr4);

	get_debugreg(d0, 0);
	get_debugreg(d1, 1);
	get_debugreg(d2, 2);
	get_debugreg(d3, 3);
	get_debugreg(d6, 6);
	get_debugreg(d7, 7);

	/* Only prपूर्णांक out debug रेजिस्टरs अगर they are in their non-शेष state. */
	अगर (!((d0 == 0) && (d1 == 0) && (d2 == 0) && (d3 == 0) &&
	    (d6 == DR6_RESERVED) && (d7 == 0x400))) अणु
		prपूर्णांकk("%sDR0: %016lx DR1: %016lx DR2: %016lx\n",
		       log_lvl, d0, d1, d2);
		prपूर्णांकk("%sDR3: %016lx DR6: %016lx DR7: %016lx\n",
		       log_lvl, d3, d6, d7);
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_OSPKE))
		prपूर्णांकk("%sPKRU: %08x\n", log_lvl, पढ़ो_pkru());
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
	WARN_ON(dead_task->mm);
पूर्ण

क्रमागत which_selector अणु
	FS,
	GS
पूर्ण;

/*
 * Out of line to be रक्षित from kprobes and tracing. If this would be
 * traced or probed than any access to a per CPU variable happens with
 * the wrong GS.
 *
 * It is not used on Xen paravirt. When paravirt support is needed, it
 * needs to be नामd with native_ prefix.
 */
अटल noinstr अचिन्हित दीर्घ __rdgsbase_inactive(व्योम)
अणु
	अचिन्हित दीर्घ gsbase;

	lockdep_निश्चित_irqs_disabled();

	अगर (!अटल_cpu_has(X86_FEATURE_XENPV)) अणु
		native_swapgs();
		gsbase = rdgsbase();
		native_swapgs();
	पूर्ण अन्यथा अणु
		instrumentation_begin();
		rdmsrl(MSR_KERNEL_GS_BASE, gsbase);
		instrumentation_end();
	पूर्ण

	वापस gsbase;
पूर्ण

/*
 * Out of line to be रक्षित from kprobes and tracing. If this would be
 * traced or probed than any access to a per CPU variable happens with
 * the wrong GS.
 *
 * It is not used on Xen paravirt. When paravirt support is needed, it
 * needs to be नामd with native_ prefix.
 */
अटल noinstr व्योम __wrgsbase_inactive(अचिन्हित दीर्घ gsbase)
अणु
	lockdep_निश्चित_irqs_disabled();

	अगर (!अटल_cpu_has(X86_FEATURE_XENPV)) अणु
		native_swapgs();
		wrgsbase(gsbase);
		native_swapgs();
	पूर्ण अन्यथा अणु
		instrumentation_begin();
		wrmsrl(MSR_KERNEL_GS_BASE, gsbase);
		instrumentation_end();
	पूर्ण
पूर्ण

/*
 * Saves the FS or GS base क्रम an outgoing thपढ़ो अगर FSGSBASE extensions are
 * not available.  The goal is to be reasonably fast on non-FSGSBASE प्रणालीs.
 * It's forcibly inlined because it'll generate better code and this function
 * is hot.
 */
अटल __always_अंतरभूत व्योम save_base_legacy(काष्ठा task_काष्ठा *prev_p,
					     अचिन्हित लघु selector,
					     क्रमागत which_selector which)
अणु
	अगर (likely(selector == 0)) अणु
		/*
		 * On Intel (without X86_BUG_शून्य_SEG), the segment base could
		 * be the pre-existing saved base or it could be zero.  On AMD
		 * (with X86_BUG_शून्य_SEG), the segment base could be almost
		 * anything.
		 *
		 * This branch is very hot (it's hit twice on almost every
		 * context चयन between 64-bit programs), and aव्योमing
		 * the RDMSR helps a lot, so we just assume that whatever
		 * value is alपढ़ोy saved is correct.  This matches historical
		 * Linux behavior, so it won't अवरोध existing applications.
		 *
		 * To aव्योम leaking state, on non-X86_BUG_शून्य_SEG CPUs, अगर we
		 * report that the base is zero, it needs to actually be zero:
		 * see the corresponding logic in load_seg_legacy.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * If the selector is 1, 2, or 3, then the base is zero on
		 * !X86_BUG_शून्य_SEG CPUs and could be anything on
		 * X86_BUG_शून्य_SEG CPUs.  In the latter हाल, Linux
		 * has never attempted to preserve the base across context
		 * चयनes.
		 *
		 * If selector > 3, then it refers to a real segment, and
		 * saving the base isn't necessary.
		 */
		अगर (which == FS)
			prev_p->thपढ़ो.fsbase = 0;
		अन्यथा
			prev_p->thपढ़ो.gsbase = 0;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम save_fsgs(काष्ठा task_काष्ठा *task)
अणु
	savesegment(fs, task->thपढ़ो.fsindex);
	savesegment(gs, task->thपढ़ो.gsindex);
	अगर (अटल_cpu_has(X86_FEATURE_FSGSBASE)) अणु
		/*
		 * If FSGSBASE is enabled, we can't make any useful guesses
		 * about the base, and user code expects us to save the current
		 * value.  Fortunately, पढ़ोing the base directly is efficient.
		 */
		task->thपढ़ो.fsbase = rdfsbase();
		task->thपढ़ो.gsbase = __rdgsbase_inactive();
	पूर्ण अन्यथा अणु
		save_base_legacy(task, task->thपढ़ो.fsindex, FS);
		save_base_legacy(task, task->thपढ़ो.gsindex, GS);
	पूर्ण
पूर्ण

/*
 * While a process is running,current->thपढ़ो.fsbase and current->thपढ़ो.gsbase
 * may not match the corresponding CPU रेजिस्टरs (see save_base_legacy()).
 */
व्योम current_save_fsgs(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/* Interrupts need to be off क्रम FSGSBASE */
	local_irq_save(flags);
	save_fsgs(current);
	local_irq_restore(flags);
पूर्ण
#अगर IS_ENABLED(CONFIG_KVM)
EXPORT_SYMBOL_GPL(current_save_fsgs);
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम loadseg(क्रमागत which_selector which,
				    अचिन्हित लघु sel)
अणु
	अगर (which == FS)
		loadsegment(fs, sel);
	अन्यथा
		load_gs_index(sel);
पूर्ण

अटल __always_अंतरभूत व्योम load_seg_legacy(अचिन्हित लघु prev_index,
					    अचिन्हित दीर्घ prev_base,
					    अचिन्हित लघु next_index,
					    अचिन्हित दीर्घ next_base,
					    क्रमागत which_selector which)
अणु
	अगर (likely(next_index <= 3)) अणु
		/*
		 * The next task is using 64-bit TLS, is not using this
		 * segment at all, or is having fun with arcane CPU features.
		 */
		अगर (next_base == 0) अणु
			/*
			 * Nasty हाल: on AMD CPUs, we need to क्रमcibly zero
			 * the base.
			 */
			अगर (अटल_cpu_has_bug(X86_BUG_शून्य_SEG)) अणु
				loadseg(which, __USER_DS);
				loadseg(which, next_index);
			पूर्ण अन्यथा अणु
				/*
				 * We could try to exhaustively detect हालs
				 * under which we can skip the segment load,
				 * but there's really only one हाल that matters
				 * क्रम perक्रमmance: अगर both the previous and
				 * next states are fully zeroed, we can skip
				 * the load.
				 *
				 * (This assumes that prev_base == 0 has no
				 * false positives.  This is the हाल on
				 * Intel-style CPUs.)
				 */
				अगर (likely(prev_index | next_index | prev_base))
					loadseg(which, next_index);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (prev_index != next_index)
				loadseg(which, next_index);
			wrmsrl(which == FS ? MSR_FS_BASE : MSR_KERNEL_GS_BASE,
			       next_base);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The next task is using a real segment.  Loading the selector
		 * is sufficient.
		 */
		loadseg(which, next_index);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम x86_fsgsbase_load(काष्ठा thपढ़ो_काष्ठा *prev,
					      काष्ठा thपढ़ो_काष्ठा *next)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_FSGSBASE)) अणु
		/* Update the FS and GS selectors अगर they could have changed. */
		अगर (unlikely(prev->fsindex || next->fsindex))
			loadseg(FS, next->fsindex);
		अगर (unlikely(prev->gsindex || next->gsindex))
			loadseg(GS, next->gsindex);

		/* Update the bases. */
		wrfsbase(next->fsbase);
		__wrgsbase_inactive(next->gsbase);
	पूर्ण अन्यथा अणु
		load_seg_legacy(prev->fsindex, prev->fsbase,
				next->fsindex, next->fsbase, FS);
		load_seg_legacy(prev->gsindex, prev->gsbase,
				next->gsindex, next->gsbase, GS);
	पूर्ण
पूर्ण

अचिन्हित दीर्घ x86_fsgsbase_पढ़ो_task(काष्ठा task_काष्ठा *task,
				     अचिन्हित लघु selector)
अणु
	अचिन्हित लघु idx = selector >> 3;
	अचिन्हित दीर्घ base;

	अगर (likely((selector & SEGMENT_TI_MASK) == 0)) अणु
		अगर (unlikely(idx >= GDT_ENTRIES))
			वापस 0;

		/*
		 * There are no user segments in the GDT with nonzero bases
		 * other than the TLS segments.
		 */
		अगर (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
			वापस 0;

		idx -= GDT_ENTRY_TLS_MIN;
		base = get_desc_base(&task->thपढ़ो.tls_array[idx]);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
		काष्ठा ldt_काष्ठा *ldt;

		/*
		 * If perक्रमmance here mattered, we could protect the LDT
		 * with RCU.  This is a slow path, though, so we can just
		 * take the mutex.
		 */
		mutex_lock(&task->mm->context.lock);
		ldt = task->mm->context.ldt;
		अगर (unlikely(!ldt || idx >= ldt->nr_entries))
			base = 0;
		अन्यथा
			base = get_desc_base(ldt->entries + idx);
		mutex_unlock(&task->mm->context.lock);
#अन्यथा
		base = 0;
#पूर्ण_अगर
	पूर्ण

	वापस base;
पूर्ण

अचिन्हित दीर्घ x86_gsbase_पढ़ो_cpu_inactive(व्योम)
अणु
	अचिन्हित दीर्घ gsbase;

	अगर (boot_cpu_has(X86_FEATURE_FSGSBASE)) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		gsbase = __rdgsbase_inactive();
		local_irq_restore(flags);
	पूर्ण अन्यथा अणु
		rdmsrl(MSR_KERNEL_GS_BASE, gsbase);
	पूर्ण

	वापस gsbase;
पूर्ण

व्योम x86_gsbase_ग_लिखो_cpu_inactive(अचिन्हित दीर्घ gsbase)
अणु
	अगर (boot_cpu_has(X86_FEATURE_FSGSBASE)) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		__wrgsbase_inactive(gsbase);
		local_irq_restore(flags);
	पूर्ण अन्यथा अणु
		wrmsrl(MSR_KERNEL_GS_BASE, gsbase);
	पूर्ण
पूर्ण

अचिन्हित दीर्घ x86_fsbase_पढ़ो_task(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ fsbase;

	अगर (task == current)
		fsbase = x86_fsbase_पढ़ो_cpu();
	अन्यथा अगर (boot_cpu_has(X86_FEATURE_FSGSBASE) ||
		 (task->thपढ़ो.fsindex == 0))
		fsbase = task->thपढ़ो.fsbase;
	अन्यथा
		fsbase = x86_fsgsbase_पढ़ो_task(task, task->thपढ़ो.fsindex);

	वापस fsbase;
पूर्ण

अचिन्हित दीर्घ x86_gsbase_पढ़ो_task(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ gsbase;

	अगर (task == current)
		gsbase = x86_gsbase_पढ़ो_cpu_inactive();
	अन्यथा अगर (boot_cpu_has(X86_FEATURE_FSGSBASE) ||
		 (task->thपढ़ो.gsindex == 0))
		gsbase = task->thपढ़ो.gsbase;
	अन्यथा
		gsbase = x86_fsgsbase_पढ़ो_task(task, task->thपढ़ो.gsindex);

	वापस gsbase;
पूर्ण

व्योम x86_fsbase_ग_लिखो_task(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ fsbase)
अणु
	WARN_ON_ONCE(task == current);

	task->thपढ़ो.fsbase = fsbase;
पूर्ण

व्योम x86_gsbase_ग_लिखो_task(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ gsbase)
अणु
	WARN_ON_ONCE(task == current);

	task->thपढ़ो.gsbase = gsbase;
पूर्ण

अटल व्योम
start_thपढ़ो_common(काष्ठा pt_regs *regs, अचिन्हित दीर्घ new_ip,
		    अचिन्हित दीर्घ new_sp,
		    अचिन्हित पूर्णांक _cs, अचिन्हित पूर्णांक _ss, अचिन्हित पूर्णांक _ds)
अणु
	WARN_ON_ONCE(regs != current_pt_regs());

	अगर (अटल_cpu_has(X86_BUG_शून्य_SEG)) अणु
		/* Loading zero below won't clear the base. */
		loadsegment(fs, __USER_DS);
		load_gs_index(__USER_DS);
	पूर्ण

	loadsegment(fs, 0);
	loadsegment(es, _ds);
	loadsegment(ds, _ds);
	load_gs_index(0);

	regs->ip		= new_ip;
	regs->sp		= new_sp;
	regs->cs		= _cs;
	regs->ss		= _ss;
	regs->flags		= X86_EFLAGS_IF;
पूर्ण

व्योम
start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ new_ip, अचिन्हित दीर्घ new_sp)
अणु
	start_thपढ़ो_common(regs, new_ip, new_sp,
			    __USER_CS, __USER_DS, 0);
पूर्ण
EXPORT_SYMBOL_GPL(start_thपढ़ो);

#अगर_घोषित CONFIG_COMPAT
व्योम compat_start_thपढ़ो(काष्ठा pt_regs *regs, u32 new_ip, u32 new_sp, bool x32)
अणु
	start_thपढ़ो_common(regs, new_ip, new_sp,
			    x32 ? __USER_CS : __USER32_CS,
			    __USER_DS, __USER_DS);
पूर्ण
#पूर्ण_अगर

/*
 *	चयन_to(x,y) should चयन tasks from x to y.
 *
 * This could still be optimized:
 * - fold all the options पूर्णांकo a flag word and test it with a single test.
 * - could test fs/gs bitsliced
 *
 * Kprobes not supported here. Set the probe on schedule instead.
 * Function graph tracer not supported too.
 */
__visible __notrace_funcgraph काष्ठा task_काष्ठा *
__चयन_to(काष्ठा task_काष्ठा *prev_p, काष्ठा task_काष्ठा *next_p)
अणु
	काष्ठा thपढ़ो_काष्ठा *prev = &prev_p->thपढ़ो;
	काष्ठा thपढ़ो_काष्ठा *next = &next_p->thपढ़ो;
	काष्ठा fpu *prev_fpu = &prev->fpu;
	काष्ठा fpu *next_fpu = &next->fpu;
	पूर्णांक cpu = smp_processor_id();

	WARN_ON_ONCE(IS_ENABLED(CONFIG_DEBUG_ENTRY) &&
		     this_cpu_पढ़ो(hardirq_stack_inuse));

	अगर (!test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		चयन_fpu_prepare(prev_fpu, cpu);

	/* We must save %fs and %gs beक्रमe load_TLS() because
	 * %fs and %gs may be cleared by load_TLS().
	 *
	 * (e.g. xen_load_tls())
	 */
	save_fsgs(prev_p);

	/*
	 * Load TLS beक्रमe restoring any segments so that segment loads
	 * reference the correct GDT entries.
	 */
	load_TLS(next, cpu);

	/*
	 * Leave lazy mode, flushing any hypercalls made here.  This
	 * must be करोne after loading TLS entries in the GDT but beक्रमe
	 * loading segments that might reference them.
	 */
	arch_end_context_चयन(next_p);

	/* Switch DS and ES.
	 *
	 * Reading them only वापसs the selectors, but writing them (अगर
	 * nonzero) loads the full descriptor from the GDT or LDT.  The
	 * LDT क्रम next is loaded in चयन_mm, and the GDT is loaded
	 * above.
	 *
	 * We thereक्रमe need to ग_लिखो new values to the segment
	 * रेजिस्टरs on every context चयन unless both the new and old
	 * values are zero.
	 *
	 * Note that we करोn't need to करो anything क्रम CS and SS, as
	 * those are saved and restored as part of pt_regs.
	 */
	savesegment(es, prev->es);
	अगर (unlikely(next->es | prev->es))
		loadsegment(es, next->es);

	savesegment(ds, prev->ds);
	अगर (unlikely(next->ds | prev->ds))
		loadsegment(ds, next->ds);

	x86_fsgsbase_load(prev, next);

	/*
	 * Switch the PDA and FPU contexts.
	 */
	this_cpu_ग_लिखो(current_task, next_p);
	this_cpu_ग_लिखो(cpu_current_top_of_stack, task_top_of_stack(next_p));

	चयन_fpu_finish(next_fpu);

	/* Reload sp0. */
	update_task_stack(next_p);

	चयन_to_extra(prev_p, next_p);

	अगर (अटल_cpu_has_bug(X86_BUG_SYSRET_SS_ATTRS)) अणु
		/*
		 * AMD CPUs have a misfeature: SYSRET sets the SS selector but
		 * करोes not update the cached descriptor.  As a result, अगर we
		 * करो SYSRET जबतक SS is शून्य, we'll end up in user mode with
		 * SS apparently equal to __USER_DS but actually unusable.
		 *
		 * The straightक्रमward workaround would be to fix it up just
		 * beक्रमe SYSRET, but that would slow करोwn the प्रणाली call
		 * fast paths.  Instead, we ensure that SS is never शून्य in
		 * प्रणाली call context.  We करो this by replacing शून्य SS
		 * selectors at every context चयन.  SYSCALL sets up a valid
		 * SS, so the only way to get शून्य is to re-enter the kernel
		 * from CPL 3 through an पूर्णांकerrupt.  Since that can't happen
		 * in the same task as a running syscall, we are guaranteed to
		 * context चयन between every पूर्णांकerrupt vector entry and a
		 * subsequent SYSRET.
		 *
		 * We पढ़ो SS first because SS पढ़ोs are much faster than
		 * ग_लिखोs.  Out of caution, we क्रमce SS to __KERNEL_DS even अगर
		 * it previously had a dअगरferent non-शून्य value.
		 */
		अचिन्हित लघु ss_sel;
		savesegment(ss, ss_sel);
		अगर (ss_sel != __KERNEL_DS)
			loadsegment(ss, __KERNEL_DS);
	पूर्ण

	/* Load the Intel cache allocation PQR MSR. */
	resctrl_sched_in();

	वापस prev_p;
पूर्ण

व्योम set_personality_64bit(व्योम)
अणु
	/* inherit personality from parent */

	/* Make sure to be in 64bit mode */
	clear_thपढ़ो_flag(TIF_ADDR32);
	/* Pretend that this comes from a 64bit execve */
	task_pt_regs(current)->orig_ax = __NR_execve;
	current_thपढ़ो_info()->status &= ~TS_COMPAT;
	अगर (current->mm)
		current->mm->context.flags = MM_CONTEXT_HAS_VSYSCALL;

	/* TBD: overग_लिखोs user setup. Should have two bits.
	   But 64bit processes have always behaved this way,
	   so it's not too bad. The मुख्य problem is just that
	   32bit children are affected again. */
	current->personality &= ~READ_IMPLIES_EXEC;
पूर्ण

अटल व्योम __set_personality_x32(व्योम)
अणु
#अगर_घोषित CONFIG_X86_X32
	अगर (current->mm)
		current->mm->context.flags = 0;

	current->personality &= ~READ_IMPLIES_EXEC;
	/*
	 * in_32bit_syscall() uses the presence of the x32 syscall bit
	 * flag to determine compat status.  The x86 mmap() code relies on
	 * the syscall bitness so set x32 syscall bit right here to make
	 * in_32bit_syscall() work during exec().
	 *
	 * Pretend to come from a x32 execve.
	 */
	task_pt_regs(current)->orig_ax = __NR_x32_execve | __X32_SYSCALL_BIT;
	current_thपढ़ो_info()->status &= ~TS_COMPAT;
#पूर्ण_अगर
पूर्ण

अटल व्योम __set_personality_ia32(व्योम)
अणु
#अगर_घोषित CONFIG_IA32_EMULATION
	अगर (current->mm) अणु
		/*
		 * uprobes applied to this MM need to know this and
		 * cannot use user_64bit_mode() at that समय.
		 */
		current->mm->context.flags = MM_CONTEXT_UPROBE_IA32;
	पूर्ण

	current->personality |= क्रमce_personality32;
	/* Prepare the first "return" to user space */
	task_pt_regs(current)->orig_ax = __NR_ia32_execve;
	current_thपढ़ो_info()->status |= TS_COMPAT;
#पूर्ण_अगर
पूर्ण

व्योम set_personality_ia32(bool x32)
अणु
	/* Make sure to be in 32bit mode */
	set_thपढ़ो_flag(TIF_ADDR32);

	अगर (x32)
		__set_personality_x32();
	अन्यथा
		__set_personality_ia32();
पूर्ण
EXPORT_SYMBOL_GPL(set_personality_ia32);

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल दीर्घ prctl_map_vdso(स्थिर काष्ठा vdso_image *image, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret;

	ret = map_vdso_once(image, addr);
	अगर (ret)
		वापस ret;

	वापस (दीर्घ)image->size;
पूर्ण
#पूर्ण_अगर

दीर्घ करो_arch_prctl_64(काष्ठा task_काष्ठा *task, पूर्णांक option, अचिन्हित दीर्घ arg2)
अणु
	पूर्णांक ret = 0;

	चयन (option) अणु
	हाल ARCH_SET_GS: अणु
		अगर (unlikely(arg2 >= TASK_SIZE_MAX))
			वापस -EPERM;

		preempt_disable();
		/*
		 * ARCH_SET_GS has always overwritten the index
		 * and the base. Zero is the most sensible value
		 * to put in the index, and is the only value that
		 * makes any sense अगर FSGSBASE is unavailable.
		 */
		अगर (task == current) अणु
			loadseg(GS, 0);
			x86_gsbase_ग_लिखो_cpu_inactive(arg2);

			/*
			 * On non-FSGSBASE प्रणालीs, save_base_legacy() expects
			 * that we also fill in thपढ़ो.gsbase.
			 */
			task->thपढ़ो.gsbase = arg2;

		पूर्ण अन्यथा अणु
			task->thपढ़ो.gsindex = 0;
			x86_gsbase_ग_लिखो_task(task, arg2);
		पूर्ण
		preempt_enable();
		अवरोध;
	पूर्ण
	हाल ARCH_SET_FS: अणु
		/*
		 * Not strictly needed क्रम %fs, but करो it क्रम symmetry
		 * with %gs
		 */
		अगर (unlikely(arg2 >= TASK_SIZE_MAX))
			वापस -EPERM;

		preempt_disable();
		/*
		 * Set the selector to 0 क्रम the same reason
		 * as %gs above.
		 */
		अगर (task == current) अणु
			loadseg(FS, 0);
			x86_fsbase_ग_लिखो_cpu(arg2);

			/*
			 * On non-FSGSBASE प्रणालीs, save_base_legacy() expects
			 * that we also fill in thपढ़ो.fsbase.
			 */
			task->thपढ़ो.fsbase = arg2;
		पूर्ण अन्यथा अणु
			task->thपढ़ो.fsindex = 0;
			x86_fsbase_ग_लिखो_task(task, arg2);
		पूर्ण
		preempt_enable();
		अवरोध;
	पूर्ण
	हाल ARCH_GET_FS: अणु
		अचिन्हित दीर्घ base = x86_fsbase_पढ़ो_task(task);

		ret = put_user(base, (अचिन्हित दीर्घ __user *)arg2);
		अवरोध;
	पूर्ण
	हाल ARCH_GET_GS: अणु
		अचिन्हित दीर्घ base = x86_gsbase_पढ़ो_task(task);

		ret = put_user(base, (अचिन्हित दीर्घ __user *)arg2);
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
# अगरdef CONFIG_X86_X32_ABI
	हाल ARCH_MAP_VDSO_X32:
		वापस prctl_map_vdso(&vdso_image_x32, arg2);
# endअगर
# अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	हाल ARCH_MAP_VDSO_32:
		वापस prctl_map_vdso(&vdso_image_32, arg2);
# endअगर
	हाल ARCH_MAP_VDSO_64:
		वापस prctl_map_vdso(&vdso_image_64, arg2);
#पूर्ण_अगर

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE2(arch_prctl, पूर्णांक, option, अचिन्हित दीर्घ, arg2)
अणु
	दीर्घ ret;

	ret = करो_arch_prctl_64(current, option, arg2);
	अगर (ret == -EINVAL)
		ret = करो_arch_prctl_common(current, option, arg2);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IA32_EMULATION
COMPAT_SYSCALL_DEFINE2(arch_prctl, पूर्णांक, option, अचिन्हित दीर्घ, arg2)
अणु
	वापस करो_arch_prctl_common(current, option, arg2);
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ KSTK_ESP(काष्ठा task_काष्ठा *task)
अणु
	वापस task_pt_regs(task)->sp;
पूर्ण
