<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/kernel/irq.c
 *
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 *
 * SuperH version:  Copyright (C) 1999  Niibe Yutaka
 */
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/delay.h>
#समावेश <linux/ratelimit.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/machvec.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <cpu/mmu_context.h>
#समावेश <यंत्र/softirq_stack.h>

atomic_t irq_err_count;

/*
 * 'what should we do if we get a hw irq event on an illegal vector'.
 * each architecture has to answer this themselves, it करोesn't deserve
 * a generic callback i think.
 */
व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	atomic_inc(&irq_err_count);
	prपूर्णांकk("unexpected IRQ trap at vector %02x\n", irq);
पूर्ण

#अगर defined(CONFIG_PROC_FS)
/*
 * /proc/पूर्णांकerrupts prपूर्णांकing क्रम arch specअगरic पूर्णांकerrupts
 */
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

	seq_म_लिखो(p, "%*s: ", prec, "NMI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat.__nmi_count, j));
	seq_म_लिखो(p, "  Non-maskable interrupts\n");

	seq_म_लिखो(p, "%*s: %10u\n", prec, "ERR", atomic_पढ़ो(&irq_err_count));

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQSTACKS
/*
 * per-CPU IRQ handling contexts (thपढ़ो inक्रमmation and stack)
 */
जोड़ irq_ctx अणु
	काष्ठा thपढ़ो_info	tinfo;
	u32			stack[THREAD_SIZE/माप(u32)];
पूर्ण;

अटल जोड़ irq_ctx *hardirq_ctx[NR_CPUS] __पढ़ो_mostly;
अटल जोड़ irq_ctx *softirq_ctx[NR_CPUS] __पढ़ो_mostly;

अटल अक्षर softirq_stack[NR_CPUS * THREAD_SIZE] __page_aligned_bss;
अटल अक्षर hardirq_stack[NR_CPUS * THREAD_SIZE] __page_aligned_bss;

अटल अंतरभूत व्योम handle_one_irq(अचिन्हित पूर्णांक irq)
अणु
	जोड़ irq_ctx *curctx, *irqctx;

	curctx = (जोड़ irq_ctx *)current_thपढ़ो_info();
	irqctx = hardirq_ctx[smp_processor_id()];

	/*
	 * this is where we चयन to the IRQ stack. However, अगर we are
	 * alपढ़ोy using the IRQ stack (because we पूर्णांकerrupted a hardirq
	 * handler) we can't करो that and just have to keep using the
	 * current stack (which is the irq stack alपढ़ोy after all)
	 */
	अगर (curctx != irqctx) अणु
		u32 *isp;

		isp = (u32 *)((अक्षर *)irqctx + माप(*irqctx));
		irqctx->tinfo.task = curctx->tinfo.task;
		irqctx->tinfo.previous_sp = current_stack_poपूर्णांकer;

		/*
		 * Copy the softirq bits in preempt_count so that the
		 * softirq checks work in the hardirq context.
		 */
		irqctx->tinfo.preempt_count =
			(irqctx->tinfo.preempt_count & ~SOFTIRQ_MASK) |
			(curctx->tinfo.preempt_count & SOFTIRQ_MASK);

		__यंत्र__ __अस्थिर__ (
			"mov	%0, r4		\n"
			"mov	r15, r8		\n"
			"jsr	@%1		\n"
			/* चयन to the irq stack */
			" mov	%2, r15		\n"
			/* restore the stack (ring zero) */
			"mov	r8, r15		\n"
			: /* no outमाला_दो */
			: "r" (irq), "r" (generic_handle_irq), "r" (isp)
			: "memory", "r0", "r1", "r2", "r3", "r4",
			  "r5", "r6", "r7", "r8", "t", "pr"
		);
	पूर्ण अन्यथा
		generic_handle_irq(irq);
पूर्ण

/*
 * allocate per-cpu stacks क्रम hardirq and क्रम softirq processing
 */
व्योम irq_ctx_init(पूर्णांक cpu)
अणु
	जोड़ irq_ctx *irqctx;

	अगर (hardirq_ctx[cpu])
		वापस;

	irqctx = (जोड़ irq_ctx *)&hardirq_stack[cpu * THREAD_SIZE];
	irqctx->tinfo.task		= शून्य;
	irqctx->tinfo.cpu		= cpu;
	irqctx->tinfo.preempt_count	= HARसूचीQ_OFFSET;
	irqctx->tinfo.addr_limit	= MAKE_MM_SEG(0);

	hardirq_ctx[cpu] = irqctx;

	irqctx = (जोड़ irq_ctx *)&softirq_stack[cpu * THREAD_SIZE];
	irqctx->tinfo.task		= शून्य;
	irqctx->tinfo.cpu		= cpu;
	irqctx->tinfo.preempt_count	= 0;
	irqctx->tinfo.addr_limit	= MAKE_MM_SEG(0);

	softirq_ctx[cpu] = irqctx;

	prपूर्णांकk("CPU %u irqstacks, hard=%p soft=%p\n",
		cpu, hardirq_ctx[cpu], softirq_ctx[cpu]);
पूर्ण

व्योम irq_ctx_निकास(पूर्णांक cpu)
अणु
	hardirq_ctx[cpu] = शून्य;
पूर्ण

व्योम करो_softirq_own_stack(व्योम)
अणु
	काष्ठा thपढ़ो_info *curctx;
	जोड़ irq_ctx *irqctx;
	u32 *isp;

	curctx = current_thपढ़ो_info();
	irqctx = softirq_ctx[smp_processor_id()];
	irqctx->tinfo.task = curctx->task;
	irqctx->tinfo.previous_sp = current_stack_poपूर्णांकer;

	/* build the stack frame on the softirq stack */
	isp = (u32 *)((अक्षर *)irqctx + माप(*irqctx));

	__यंत्र__ __अस्थिर__ (
		"mov	r15, r9		\n"
		"jsr	@%0		\n"
		/* चयन to the softirq stack */
		" mov	%1, r15		\n"
		/* restore the thपढ़ो stack */
		"mov	r9, r15		\n"
		: /* no outमाला_दो */
		: "r" (__करो_softirq), "r" (isp)
		: "memory", "r0", "r1", "r2", "r3", "r4",
		  "r5", "r6", "r7", "r8", "r9", "r15", "t", "pr"
	);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम handle_one_irq(अचिन्हित पूर्णांक irq)
अणु
	generic_handle_irq(irq);
पूर्ण
#पूर्ण_अगर

यंत्रlinkage __irq_entry पूर्णांक करो_IRQ(अचिन्हित पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();

	irq = irq_demux(irq_lookup(irq));

	अगर (irq != NO_IRQ_IGNORE) अणु
		handle_one_irq(irq);
		irq_finish(irq);
	पूर्ण

	irq_निकास();

	set_irq_regs(old_regs);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	plat_irq_setup();

	/* Perक्रमm the machine specअगरic initialisation */
	अगर (sh_mv.mv_init_irq)
		sh_mv.mv_init_irq();

	पूर्णांकc_finalize();

	irq_ctx_init(smp_processor_id());
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * The CPU has been marked offline.  Migrate IRQs off this CPU.  If
 * the affinity settings करो not allow other CPUs, क्रमce them onto any
 * available CPU.
 */
व्योम migrate_irqs(व्योम)
अणु
	अचिन्हित पूर्णांक irq, cpu = smp_processor_id();

	क्रम_each_active_irq(irq) अणु
		काष्ठा irq_data *data = irq_get_irq_data(irq);

		अगर (irq_data_get_node(data) == cpu) अणु
			काष्ठा cpumask *mask = irq_data_get_affinity_mask(data);
			अचिन्हित पूर्णांक newcpu = cpumask_any_and(mask,
							      cpu_online_mask);
			अगर (newcpu >= nr_cpu_ids) अणु
				pr_info_ratelimited("IRQ%u no longer affine to CPU%u\n",
						    irq, cpu);

				cpumask_setall(mask);
			पूर्ण
			irq_set_affinity(irq, mask);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर
