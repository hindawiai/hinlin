<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/process.c
 *
 *  Copyright (C) 1996-2000 Russell King - Converted to ARM.
 *  Original Copyright (C) 1995  Linus Torvalds
 */
#समावेश <मानकतर्क.स>

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/user.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/pm.h>
#समावेश <linux/tick.h>
#समावेश <linux/utsname.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/thपढ़ो_notअगरy.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/tls.h>
#समावेश <यंत्र/vdso.h>

#समावेश "signal.h"

#अगर defined(CONFIG_STACKPROTECTOR) && !defined(CONFIG_STACKPROTECTOR_PER_TASK)
#समावेश <linux/stackprotector.h>
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

अटल स्थिर अक्षर *processor_modes[] __maybe_unused = अणु
  "USER_26", "FIQ_26" , "IRQ_26" , "SVC_26" , "UK4_26" , "UK5_26" , "UK6_26" , "UK7_26" ,
  "UK8_26" , "UK9_26" , "UK10_26", "UK11_26", "UK12_26", "UK13_26", "UK14_26", "UK15_26",
  "USER_32", "FIQ_32" , "IRQ_32" , "SVC_32" , "UK4_32" , "UK5_32" , "MON_32" , "ABT_32" ,
  "UK8_32" , "UK9_32" , "HYP_32", "UND_32" , "UK12_32", "UK13_32", "UK14_32", "SYS_32"
पूर्ण;

अटल स्थिर अक्षर *isa_modes[] __maybe_unused = अणु
  "ARM" , "Thumb" , "Jazelle", "ThumbEE"
पूर्ण;

/*
 * This is our शेष idle handler.
 */

व्योम (*arm_pm_idle)(व्योम);

/*
 * Called from the core idle loop.
 */

व्योम arch_cpu_idle(व्योम)
अणु
	अगर (arm_pm_idle)
		arm_pm_idle();
	अन्यथा
		cpu_करो_idle();
	raw_local_irq_enable();
पूर्ण

व्योम arch_cpu_idle_prepare(व्योम)
अणु
	local_fiq_enable();
पूर्ण

व्योम arch_cpu_idle_enter(व्योम)
अणु
	ledtrig_cpu(CPU_LED_IDLE_START);
#अगर_घोषित CONFIG_PL310_ERRATA_769419
	wmb();
#पूर्ण_अगर
पूर्ण

व्योम arch_cpu_idle_निकास(व्योम)
अणु
	ledtrig_cpu(CPU_LED_IDLE_END);
पूर्ण

व्योम __show_regs_alloc_मुक्त(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;

	/* check क्रम r0 - r12 only */
	क्रम (i = 0; i < 13; i++) अणु
		pr_alert("Register r%d information:", i);
		mem_dump_obj((व्योम *)regs->uregs[i]);
	पूर्ण
पूर्ण

व्योम __show_regs(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर buf[64];
#अगर_अघोषित CONFIG_CPU_V7M
	अचिन्हित पूर्णांक करोमुख्य, fs;
#अगर_घोषित CONFIG_CPU_SW_DOMAIN_PAN
	/*
	 * Get the करोमुख्य रेजिस्टर क्रम the parent context. In user
	 * mode, we करोn't save the DACR, so lets use what it should
	 * be. For other modes, we place it after the pt_regs काष्ठा.
	 */
	अगर (user_mode(regs)) अणु
		करोमुख्य = DACR_UACCESS_ENABLE;
		fs = get_fs();
	पूर्ण अन्यथा अणु
		करोमुख्य = to_svc_pt_regs(regs)->dacr;
		fs = to_svc_pt_regs(regs)->addr_limit;
	पूर्ण
#अन्यथा
	करोमुख्य = get_करोमुख्य();
	fs = get_fs();
#पूर्ण_अगर
#पूर्ण_अगर

	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	prपूर्णांकk("PC is at %pS\n", (व्योम *)inकाष्ठाion_poपूर्णांकer(regs));
	prपूर्णांकk("LR is at %pS\n", (व्योम *)regs->ARM_lr);
	prपूर्णांकk("pc : [<%08lx>]    lr : [<%08lx>]    psr: %08lx\n",
	       regs->ARM_pc, regs->ARM_lr, regs->ARM_cpsr);
	prपूर्णांकk("sp : %08lx  ip : %08lx  fp : %08lx\n",
	       regs->ARM_sp, regs->ARM_ip, regs->ARM_fp);
	prपूर्णांकk("r10: %08lx  r9 : %08lx  r8 : %08lx\n",
		regs->ARM_r10, regs->ARM_r9,
		regs->ARM_r8);
	prपूर्णांकk("r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx\n",
		regs->ARM_r7, regs->ARM_r6,
		regs->ARM_r5, regs->ARM_r4);
	prपूर्णांकk("r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx\n",
		regs->ARM_r3, regs->ARM_r2,
		regs->ARM_r1, regs->ARM_r0);

	flags = regs->ARM_cpsr;
	buf[0] = flags & PSR_N_BIT ? 'N' : 'n';
	buf[1] = flags & PSR_Z_BIT ? 'Z' : 'z';
	buf[2] = flags & PSR_C_BIT ? 'C' : 'c';
	buf[3] = flags & PSR_V_BIT ? 'V' : 'v';
	buf[4] = '\0';

#अगर_अघोषित CONFIG_CPU_V7M
	अणु
		स्थिर अक्षर *segment;

		अगर ((करोमुख्य & करोमुख्य_mask(DOMAIN_USER)) ==
		    करोमुख्य_val(DOMAIN_USER, DOMAIN_NOACCESS))
			segment = "none";
		अन्यथा अगर (fs == KERNEL_DS)
			segment = "kernel";
		अन्यथा
			segment = "user";

		prपूर्णांकk("Flags: %s  IRQs o%s  FIQs o%s  Mode %s  ISA %s  Segment %s\n",
			buf, पूर्णांकerrupts_enabled(regs) ? "n" : "ff",
			fast_पूर्णांकerrupts_enabled(regs) ? "n" : "ff",
			processor_modes[processor_mode(regs)],
			isa_modes[isa_mode(regs)], segment);
	पूर्ण
#अन्यथा
	prपूर्णांकk("xPSR: %08lx\n", regs->ARM_cpsr);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_CP15
	अणु
		अचिन्हित पूर्णांक ctrl;

		buf[0] = '\0';
#अगर_घोषित CONFIG_CPU_CP15_MMU
		अणु
			अचिन्हित पूर्णांक transbase;
			यंत्र("mrc p15, 0, %0, c2, c0\n\t"
			    : "=r" (transbase));
			snम_लिखो(buf, माप(buf), "  Table: %08x  DAC: %08x",
				transbase, करोमुख्य);
		पूर्ण
#पूर्ण_अगर
		यंत्र("mrc p15, 0, %0, c1, c0\n" : "=r" (ctrl));

		prपूर्णांकk("Control: %08x%s\n", ctrl, buf);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम show_regs(काष्ठा pt_regs * regs)
अणु
	__show_regs(regs);
	dump_stack();
पूर्ण

ATOMIC_NOTIFIER_HEAD(thपढ़ो_notअगरy_head);

EXPORT_SYMBOL_GPL(thपढ़ो_notअगरy_head);

/*
 * Free current thपढ़ो data काष्ठाures etc..
 */
व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	thपढ़ो_notअगरy(THREAD_NOTIFY_EXIT, task_thपढ़ो_info(tsk));
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = current_thपढ़ो_info();
	काष्ठा task_काष्ठा *tsk = current;

	flush_ptrace_hw_अवरोधpoपूर्णांक(tsk);

	स_रखो(thपढ़ो->used_cp, 0, माप(thपढ़ो->used_cp));
	स_रखो(&tsk->thपढ़ो.debug, 0, माप(काष्ठा debug_info));
	स_रखो(&thपढ़ो->fpstate, 0, माप(जोड़ fp_state));

	flush_tls();

	thपढ़ो_notअगरy(THREAD_NOTIFY_FLUSH, thपढ़ो);
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

यंत्रlinkage व्योम ret_from_विभाजन(व्योम) __यंत्र__("ret_from_fork");

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ stack_start,
		अचिन्हित दीर्घ stk_sz, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(p);
	काष्ठा pt_regs *childregs = task_pt_regs(p);

	स_रखो(&thपढ़ो->cpu_context, 0, माप(काष्ठा cpu_context_save));

#अगर_घोषित CONFIG_CPU_USE_DOMAINS
	/*
	 * Copy the initial value of the करोमुख्य access control रेजिस्टर
	 * from the current thपढ़ो: thपढ़ो->addr_limit will have been
	 * copied from the current thपढ़ो via setup_thपढ़ो_stack() in
	 * kernel/विभाजन.c
	 */
	thपढ़ो->cpu_करोमुख्य = get_करोमुख्य();
#पूर्ण_अगर

	अगर (likely(!(p->flags & (PF_KTHREAD | PF_IO_WORKER)))) अणु
		*childregs = *current_pt_regs();
		childregs->ARM_r0 = 0;
		अगर (stack_start)
			childregs->ARM_sp = stack_start;
	पूर्ण अन्यथा अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		thपढ़ो->cpu_context.r4 = stk_sz;
		thपढ़ो->cpu_context.r5 = stack_start;
		childregs->ARM_cpsr = SVC_MODE;
	पूर्ण
	thपढ़ो->cpu_context.pc = (अचिन्हित दीर्घ)ret_from_विभाजन;
	thपढ़ो->cpu_context.sp = (अचिन्हित दीर्घ)childregs;

	clear_ptrace_hw_अवरोधpoपूर्णांक(p);

	अगर (clone_flags & CLONE_SETTLS)
		thपढ़ो->tp_value[0] = tls;
	thपढ़ो->tp_value[1] = get_tpuser();

	thपढ़ो_notअगरy(THREAD_NOTIFY_COPY, thपढ़ो);

#अगर_घोषित CONFIG_STACKPROTECTOR_PER_TASK
	thपढ़ो->stack_canary = p->stack_canary;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा stackframe frame;
	अचिन्हित दीर्घ stack_page;
	पूर्णांक count = 0;
	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	frame.fp = thपढ़ो_saved_fp(p);
	frame.sp = thपढ़ो_saved_sp(p);
	frame.lr = 0;			/* recovered from the stack */
	frame.pc = thपढ़ो_saved_pc(p);
	stack_page = (अचिन्हित दीर्घ)task_stack_page(p);
	करो अणु
		अगर (frame.sp < stack_page ||
		    frame.sp >= stack_page + THREAD_SIZE ||
		    unwind_frame(&frame) < 0)
			वापस 0;
		अगर (!in_sched_functions(frame.pc))
			वापस frame.pc;
	पूर्ण जबतक (count ++ < 16);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MMU
#अगर_घोषित CONFIG_KUSER_HELPERS
/*
 * The vectors page is always पढ़ोable from user space क्रम the
 * atomic helpers. Insert it पूर्णांकo the gate_vma so that it is visible
 * through ptrace and /proc/<pid>/mem.
 */
अटल काष्ठा vm_area_काष्ठा gate_vma;

अटल पूर्णांक __init gate_vma_init(व्योम)
अणु
	vma_init(&gate_vma, शून्य);
	gate_vma.vm_page_prot = PAGE_READONLY_EXEC;
	gate_vma.vm_start = 0xffff0000;
	gate_vma.vm_end	= 0xffff0000 + PAGE_SIZE;
	gate_vma.vm_flags = VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYEXEC;
	वापस 0;
पूर्ण
arch_initcall(gate_vma_init);

काष्ठा vm_area_काष्ठा *get_gate_vma(काष्ठा mm_काष्ठा *mm)
अणु
	वापस &gate_vma;
पूर्ण

पूर्णांक in_gate_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस (addr >= gate_vma.vm_start) && (addr < gate_vma.vm_end);
पूर्ण

पूर्णांक in_gate_area_no_mm(अचिन्हित दीर्घ addr)
अणु
	वापस in_gate_area(शून्य, addr);
पूर्ण
#घोषणा is_gate_vma(vma)	((vma) == &gate_vma)
#अन्यथा
#घोषणा is_gate_vma(vma)	0
#पूर्ण_अगर

स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस is_gate_vma(vma) ? "[vectors]" : शून्य;
पूर्ण

/* If possible, provide a placement hपूर्णांक at a अक्रमom offset from the
 * stack क्रम the sigpage and vdso pages.
 */
अटल अचिन्हित दीर्घ sigpage_addr(स्थिर काष्ठा mm_काष्ठा *mm,
				  अचिन्हित पूर्णांक npages)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ first;
	अचिन्हित दीर्घ last;
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक slots;

	first = PAGE_ALIGN(mm->start_stack);

	last = TASK_SIZE - (npages << PAGE_SHIFT);

	/* No room after stack? */
	अगर (first > last)
		वापस 0;

	/* Just enough room? */
	अगर (first == last)
		वापस first;

	slots = ((last - first) >> PAGE_SHIFT) + 1;

	offset = get_अक्रमom_पूर्णांक() % slots;

	addr = first + (offset << PAGE_SHIFT);

	वापस addr;
पूर्ण

अटल काष्ठा page *संकेत_page;
बाह्य काष्ठा page *get_संकेत_page(व्योम);

अटल पूर्णांक sigpage_mremap(स्थिर काष्ठा vm_special_mapping *sm,
		काष्ठा vm_area_काष्ठा *new_vma)
अणु
	current->mm->context.sigpage = new_vma->vm_start;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_special_mapping sigpage_mapping = अणु
	.name = "[sigpage]",
	.pages = &संकेत_page,
	.mremap = sigpage_mremap,
पूर्ण;

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ hपूर्णांक;
	पूर्णांक ret = 0;

	अगर (!संकेत_page)
		संकेत_page = get_संकेत_page();
	अगर (!संकेत_page)
		वापस -ENOMEM;

	npages = 1; /* क्रम sigpage */
	npages += vdso_total_pages;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;
	hपूर्णांक = sigpage_addr(mm, npages);
	addr = get_unmapped_area(शून्य, hपूर्णांक, npages << PAGE_SHIFT, 0, 0);
	अगर (IS_ERR_VALUE(addr)) अणु
		ret = addr;
		जाओ up_fail;
	पूर्ण

	vma = _install_special_mapping(mm, addr, PAGE_SIZE,
		VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
		&sigpage_mapping);

	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ up_fail;
	पूर्ण

	mm->context.sigpage = addr;

	/* Unlike the sigpage, failure to install the vdso is unlikely
	 * to be fatal to the process, so no error check needed
	 * here.
	 */
	arm_install_vdso(mm, addr + PAGE_SIZE);

 up_fail:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
#पूर्ण_अगर
