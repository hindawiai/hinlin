<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 * Code to handle x86 style IRQs plus some generic पूर्णांकerrupt stuff.
 *
 * Copyright (C) 1992 Linus Torvalds
 * Copyright (C) 1994, 1995, 1996, 1997, 1998 Ralf Baechle
 * Copyright (C) 1999 SuSE GmbH (Philipp Rumpf, prumpf@tux.org)
 * Copyright (C) 1999-2000 Grant Grundler
 * Copyright (c) 2005 Matthew Wilcox
 */
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/softirq_stack.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/ldcw.h>

#अघोषित PARISC_IRQ_CR16_COUNTS

बाह्य irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक, व्योम *);
बाह्य irqवापस_t ipi_पूर्णांकerrupt(पूर्णांक, व्योम *);

#घोषणा EIEM_MASK(irq)       (1UL<<(CPU_IRQ_MAX - irq))

/* Bits in EIEM correlate with cpu_irq_action[].
** Numbered *Big Endian*! (ie bit 0 is MSB)
*/
अटल अस्थिर अचिन्हित दीर्घ cpu_eiem = 0;

/*
** local ACK biपंचांगap ... habitually set to 1, but reset to zero
** between ->ack() and ->end() of the पूर्णांकerrupt to prevent
** re-पूर्णांकerruption of a processing पूर्णांकerrupt.
*/
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, local_ack_eiem) = ~0UL;

अटल व्योम cpu_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ eirr_bit = EIEM_MASK(d->irq);

	cpu_eiem &= ~eirr_bit;
	/* Do nothing on the other CPUs.  If they get this पूर्णांकerrupt,
	 * The & cpu_eiem in the करो_cpu_irq_mask() ensures they won't
	 * handle it, and the set_eiem() at the bottom will ensure it
	 * then माला_लो disabled */
पूर्ण

अटल व्योम __cpu_unmask_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ eirr_bit = EIEM_MASK(irq);

	cpu_eiem |= eirr_bit;

	/* This is just a simple NOP IPI.  But what it करोes is cause
	 * all the other CPUs to करो a set_eiem(cpu_eiem) at the end
	 * of the पूर्णांकerrupt handler */
	smp_send_all_nop();
पूर्ण

अटल व्योम cpu_unmask_irq(काष्ठा irq_data *d)
अणु
	__cpu_unmask_irq(d->irq);
पूर्ण

व्योम cpu_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ mask = EIEM_MASK(d->irq);
	पूर्णांक cpu = smp_processor_id();

	/* Clear in EIEM so we can no दीर्घer process */
	per_cpu(local_ack_eiem, cpu) &= ~mask;

	/* disable the पूर्णांकerrupt */
	set_eiem(cpu_eiem & per_cpu(local_ack_eiem, cpu));

	/* and now ack it */
	mtctl(mask, 23);
पूर्ण

व्योम cpu_eoi_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ mask = EIEM_MASK(d->irq);
	पूर्णांक cpu = smp_processor_id();

	/* set it in the eiems---it's no दीर्घer in process */
	per_cpu(local_ack_eiem, cpu) |= mask;

	/* enable the पूर्णांकerrupt */
	set_eiem(cpu_eiem & per_cpu(local_ack_eiem, cpu));
पूर्ण

#अगर_घोषित CONFIG_SMP
पूर्णांक cpu_check_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *dest)
अणु
	पूर्णांक cpu_dest;

	/* समयr and ipi have to always be received on all CPUs */
	अगर (irqd_is_per_cpu(d))
		वापस -EINVAL;

	/* whatever mask they set, we just allow one CPU */
	cpu_dest = cpumask_next_and(d->irq & (num_online_cpus()-1),
					dest, cpu_online_mask);
	अगर (cpu_dest >= nr_cpu_ids)
		cpu_dest = cpumask_first_and(dest, cpu_online_mask);

	वापस cpu_dest;
पूर्ण

अटल पूर्णांक cpu_set_affinity_irq(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *dest,
				bool क्रमce)
अणु
	पूर्णांक cpu_dest;

	cpu_dest = cpu_check_affinity(d, dest);
	अगर (cpu_dest < 0)
		वापस -1;

	cpumask_copy(irq_data_get_affinity_mask(d), dest);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip cpu_पूर्णांकerrupt_type = अणु
	.name			= "CPU",
	.irq_mask		= cpu_mask_irq,
	.irq_unmask		= cpu_unmask_irq,
	.irq_ack		= cpu_ack_irq,
	.irq_eoi		= cpu_eoi_irq,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= cpu_set_affinity_irq,
#पूर्ण_अगर
	/* XXX: Needs to be written.  We managed without it so far, but
	 * we really ought to ग_लिखो it.
	 */
	.irq_retrigger	= शून्य,
पूर्ण;

DEFINE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);
#घोषणा irq_stats(x)		(&per_cpu(irq_stat, x))

/*
 * /proc/पूर्णांकerrupts prपूर्णांकing क्रम arch specअगरic पूर्णांकerrupts
 */
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

#अगर_घोषित CONFIG_DEBUG_STACKOVERFLOW
	seq_म_लिखो(p, "%*s: ", prec, "STK");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->kernel_stack_usage);
	seq_माला_दो(p, "  Kernel stack usage\n");
# अगरdef CONFIG_IRQSTACKS
	seq_म_लिखो(p, "%*s: ", prec, "IST");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_stack_usage);
	seq_माला_दो(p, "  Interrupt stack usage\n");
# endअगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	अगर (num_online_cpus() > 1) अणु
		seq_म_लिखो(p, "%*s: ", prec, "RES");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_resched_count);
		seq_माला_दो(p, "  Rescheduling interrupts\n");
		seq_म_लिखो(p, "%*s: ", prec, "CAL");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_call_count);
		seq_माला_दो(p, "  Function call interrupts\n");
	पूर्ण
#पूर्ण_अगर
	seq_म_लिखो(p, "%*s: ", prec, "UAH");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_unaligned_count);
	seq_माला_दो(p, "  Unaligned access handler traps\n");
	seq_म_लिखो(p, "%*s: ", prec, "FPA");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_fpassist_count);
	seq_माला_दो(p, "  Floating point assist traps\n");
	seq_म_लिखो(p, "%*s: ", prec, "TLB");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_tlb_count);
	seq_माला_दो(p, "  TLB shootdowns\n");
	वापस 0;
पूर्ण

पूर्णांक show_पूर्णांकerrupts(काष्ठा seq_file *p, व्योम *v)
अणु
	पूर्णांक i = *(loff_t *) v, j;
	अचिन्हित दीर्घ flags;

	अगर (i == 0) अणु
		seq_माला_दो(p, "    ");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "       CPU%d", j);

#अगर_घोषित PARISC_IRQ_CR16_COUNTS
		seq_म_लिखो(p, " [min/avg/max] (CPU cycle counts)");
#पूर्ण_अगर
		seq_अ_दो(p, '\n');
	पूर्ण

	अगर (i < NR_IRQS) अणु
		काष्ठा irq_desc *desc = irq_to_desc(i);
		काष्ठा irqaction *action;

		raw_spin_lock_irqsave(&desc->lock, flags);
		action = desc->action;
		अगर (!action)
			जाओ skip;
		seq_म_लिखो(p, "%3d: ", i);

		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", irq_desc_kstat_cpu(desc, j));

		seq_म_लिखो(p, " %14s", irq_desc_get_chip(desc)->name);
#अगर_अघोषित PARISC_IRQ_CR16_COUNTS
		seq_म_लिखो(p, "  %s", action->name);

		जबतक ((action = action->next))
			seq_म_लिखो(p, ", %s", action->name);
#अन्यथा
		क्रम ( ;action; action = action->next) अणु
			अचिन्हित पूर्णांक k, avg, min, max;

			min = max = action->cr16_hist[0];

			क्रम (avg = k = 0; k < PARISC_CR16_HIST_SIZE; k++) अणु
				पूर्णांक hist = action->cr16_hist[k];

				अगर (hist) अणु
					avg += hist;
				पूर्ण अन्यथा
					अवरोध;

				अगर (hist > max) max = hist;
				अगर (hist < min) min = hist;
			पूर्ण

			avg /= k;
			seq_म_लिखो(p, " %s[%d/%d/%d]", action->name,
					min,avg,max);
		पूर्ण
#पूर्ण_अगर

		seq_अ_दो(p, '\n');
 skip:
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण

	अगर (i == NR_IRQS)
		arch_show_पूर्णांकerrupts(p, 3);

	वापस 0;
पूर्ण



/*
** The following क्रमm a "set": Virtual IRQ, Transaction Address, Trans Data.
** Respectively, these map to IRQ region+EIRR, Processor HPA, EIRR bit.
**
** To use txn_XXX() पूर्णांकerfaces, get a Virtual IRQ first.
** Then use that to get the Transaction address and data.
*/

पूर्णांक cpu_claim_irq(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *type, व्योम *data)
अणु
	अगर (irq_has_action(irq))
		वापस -EBUSY;
	अगर (irq_get_chip(irq) != &cpu_पूर्णांकerrupt_type)
		वापस -EBUSY;

	/* क्रम iosapic पूर्णांकerrupts */
	अगर (type) अणु
		irq_set_chip_and_handler(irq, type, handle_percpu_irq);
		irq_set_chip_data(irq, data);
		__cpu_unmask_irq(irq);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक txn_claim_irq(पूर्णांक irq)
अणु
	वापस cpu_claim_irq(irq, शून्य, शून्य) ? -1 : irq;
पूर्ण

/*
 * The bits_wide parameter accommodates the limitations of the HW/SW which
 * use these bits:
 * Legacy PA I/O (GSC/NIO): 5 bits (architected EIM रेजिस्टर)
 * V-class (EPIC):          6 bits
 * N/L/A-class (iosapic):   8 bits
 * PCI 2.2 MSI:            16 bits
 * Some PCI devices:       32 bits (Symbios SCSI/ATM/HyperFabric)
 *
 * On the service provider side:
 * o PA 1.1 (and PA2.0 narrow mode)     5-bits (width of EIR रेजिस्टर)
 * o PA 2.0 wide mode                   6-bits (per processor)
 * o IA64                               8-bits (0-256 total)
 *
 * So a Legacy PA I/O device on a PA 2.0 box can't use all the bits supported
 * by the processor...and the N/L-class I/O subप्रणाली supports more bits than
 * PA2.0 has. The first हाल is the problem.
 */
पूर्णांक txn_alloc_irq(अचिन्हित पूर्णांक bits_wide)
अणु
	पूर्णांक irq;

	/* never वापस irq 0 cause that's the पूर्णांकerval समयr */
	क्रम (irq = CPU_IRQ_BASE + 1; irq <= CPU_IRQ_MAX; irq++) अणु
		अगर (cpu_claim_irq(irq, शून्य, शून्य) < 0)
			जारी;
		अगर ((irq - CPU_IRQ_BASE) >= (1 << bits_wide))
			जारी;
		वापस irq;
	पूर्ण

	/* unlikely, but be prepared */
	वापस -1;
पूर्ण


अचिन्हित दीर्घ txn_affinity_addr(अचिन्हित पूर्णांक irq, पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	cpumask_copy(irq_data_get_affinity_mask(d), cpumask_of(cpu));
#पूर्ण_अगर

	वापस per_cpu(cpu_data, cpu).txn_addr;
पूर्ण


अचिन्हित दीर्घ txn_alloc_addr(अचिन्हित पूर्णांक virt_irq)
अणु
	अटल पूर्णांक next_cpu = -1;

	next_cpu++; /* assign to "next" CPU we want this bugger on */

	/* validate entry */
	जबतक ((next_cpu < nr_cpu_ids) &&
		(!per_cpu(cpu_data, next_cpu).txn_addr ||
		 !cpu_online(next_cpu)))
		next_cpu++;

	अगर (next_cpu >= nr_cpu_ids) 
		next_cpu = 0;	/* nothing अन्यथा, assign monarch */

	वापस txn_affinity_addr(virt_irq, next_cpu);
पूर्ण


अचिन्हित पूर्णांक txn_alloc_data(अचिन्हित पूर्णांक virt_irq)
अणु
	वापस virt_irq - CPU_IRQ_BASE;
पूर्ण

अटल अंतरभूत पूर्णांक eirr_to_irq(अचिन्हित दीर्घ eirr)
अणु
	पूर्णांक bit = fls_दीर्घ(eirr);
	वापस (BITS_PER_LONG - bit) + TIMER_IRQ;
पूर्ण

#अगर_घोषित CONFIG_IRQSTACKS
/*
 * IRQ STACK - used क्रम irq handler
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा IRQ_STACK_SIZE      (4096 << 4) /* 64k irq stack size */
#अन्यथा
#घोषणा IRQ_STACK_SIZE      (4096 << 3) /* 32k irq stack size */
#पूर्ण_अगर

जोड़ irq_stack_जोड़ अणु
	अचिन्हित दीर्घ stack[IRQ_STACK_SIZE/माप(अचिन्हित दीर्घ)];
	अस्थिर अचिन्हित पूर्णांक slock[4];
	अस्थिर अचिन्हित पूर्णांक lock[1];
पूर्ण;

DEFINE_PER_CPU(जोड़ irq_stack_जोड़, irq_stack_जोड़) = अणु
		.slock = अणु 1,1,1,1 पूर्ण,
	पूर्ण;
#पूर्ण_अगर


पूर्णांक sysctl_panic_on_stackoverflow = 1;

अटल अंतरभूत व्योम stack_overflow_check(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_DEBUG_STACKOVERFLOW
	#घोषणा STACK_MARGIN	(256*6)

	/* Our stack starts directly behind the thपढ़ो_info काष्ठा. */
	अचिन्हित दीर्घ stack_start = (अचिन्हित दीर्घ) current_thपढ़ो_info();
	अचिन्हित दीर्घ sp = regs->gr[30];
	अचिन्हित दीर्घ stack_usage;
	अचिन्हित पूर्णांक *last_usage;
	पूर्णांक cpu = smp_processor_id();

	/* अगर sr7 != 0, we पूर्णांकerrupted a userspace process which we करो not want
	 * to check क्रम stack overflow. We will only check the kernel stack. */
	अगर (regs->sr[7])
		वापस;

	/* निकास अगर alपढ़ोy in panic */
	अगर (sysctl_panic_on_stackoverflow < 0)
		वापस;

	/* calculate kernel stack usage */
	stack_usage = sp - stack_start;
#अगर_घोषित CONFIG_IRQSTACKS
	अगर (likely(stack_usage <= THREAD_SIZE))
		जाओ check_kernel_stack; /* found kernel stack */

	/* check irq stack usage */
	stack_start = (अचिन्हित दीर्घ) &per_cpu(irq_stack_जोड़, cpu).stack;
	stack_usage = sp - stack_start;

	last_usage = &per_cpu(irq_stat.irq_stack_usage, cpu);
	अगर (unlikely(stack_usage > *last_usage))
		*last_usage = stack_usage;

	अगर (likely(stack_usage < (IRQ_STACK_SIZE - STACK_MARGIN)))
		वापस;

	pr_emerg("stackcheck: %s will most likely overflow irq stack "
		 "(sp:%lx, stk bottom-top:%lx-%lx)\n",
		current->comm, sp, stack_start, stack_start + IRQ_STACK_SIZE);
	जाओ panic_check;

check_kernel_stack:
#पूर्ण_अगर

	/* check kernel stack usage */
	last_usage = &per_cpu(irq_stat.kernel_stack_usage, cpu);

	अगर (unlikely(stack_usage > *last_usage))
		*last_usage = stack_usage;

	अगर (likely(stack_usage < (THREAD_SIZE - STACK_MARGIN)))
		वापस;

	pr_emerg("stackcheck: %s will most likely overflow kernel stack "
		 "(sp:%lx, stk bottom-top:%lx-%lx)\n",
		current->comm, sp, stack_start, stack_start + THREAD_SIZE);

#अगर_घोषित CONFIG_IRQSTACKS
panic_check:
#पूर्ण_अगर
	अगर (sysctl_panic_on_stackoverflow) अणु
		sysctl_panic_on_stackoverflow = -1; /* disable further checks */
		panic("low stack detected by irq handler - check messages\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_IRQSTACKS
/* in entry.S: */
व्योम call_on_stack(अचिन्हित दीर्घ p1, व्योम *func, अचिन्हित दीर्घ new_stack);

अटल व्योम execute_on_irq_stack(व्योम *func, अचिन्हित दीर्घ param1)
अणु
	जोड़ irq_stack_जोड़ *जोड़_ptr;
	अचिन्हित दीर्घ irq_stack;
	अस्थिर अचिन्हित पूर्णांक *irq_stack_in_use;

	जोड़_ptr = &per_cpu(irq_stack_जोड़, smp_processor_id());
	irq_stack = (अचिन्हित दीर्घ) &जोड़_ptr->stack;
	irq_stack = ALIGN(irq_stack + माप(irq_stack_जोड़.slock),
			 64); /* align क्रम stack frame usage */

	/* We may be called recursive. If we are alपढ़ोy using the irq stack,
	 * just जारी to use it. Use spinlocks to serialize
	 * the irq stack usage.
	 */
	irq_stack_in_use = (अस्थिर अचिन्हित पूर्णांक *)__ldcw_align(जोड़_ptr);
	अगर (!__ldcw(irq_stack_in_use)) अणु
		व्योम (*direct_call)(अचिन्हित दीर्घ p1) = func;

		/* We are using the IRQ stack alपढ़ोy.
		 * Do direct call on current stack. */
		direct_call(param1);
		वापस;
	पूर्ण

	/* This is where we चयन to the IRQ stack. */
	call_on_stack(param1, func, irq_stack);

	/* मुक्त up irq stack usage. */
	*irq_stack_in_use = 1;
पूर्ण

व्योम करो_softirq_own_stack(व्योम)
अणु
	execute_on_irq_stack(__करो_softirq, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_IRQSTACKS */

/* ONLY called from entry.S:पूर्णांकr_extपूर्णांक() */
व्योम करो_cpu_irq_mask(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;
	अचिन्हित दीर्घ eirr_val;
	पूर्णांक irq, cpu = smp_processor_id();
	काष्ठा irq_data *irq_data;
#अगर_घोषित CONFIG_SMP
	cpumask_t dest;
#पूर्ण_अगर

	old_regs = set_irq_regs(regs);
	local_irq_disable();
	irq_enter();

	eirr_val = mfctl(23) & cpu_eiem & per_cpu(local_ack_eiem, cpu);
	अगर (!eirr_val)
		जाओ set_out;
	irq = eirr_to_irq(eirr_val);

	irq_data = irq_get_irq_data(irq);

	/* Filter out spurious पूर्णांकerrupts, mostly from serial port at bootup */
	अगर (unlikely(!irq_desc_has_action(irq_data_to_desc(irq_data))))
		जाओ set_out;

#अगर_घोषित CONFIG_SMP
	cpumask_copy(&dest, irq_data_get_affinity_mask(irq_data));
	अगर (irqd_is_per_cpu(irq_data) &&
	    !cpumask_test_cpu(smp_processor_id(), &dest)) अणु
		पूर्णांक cpu = cpumask_first(&dest);

		prपूर्णांकk(KERN_DEBUG "redirecting irq %d from CPU %d to %d\n",
		       irq, smp_processor_id(), cpu);
		gsc_ग_लिखोl(irq + CPU_IRQ_BASE,
			   per_cpu(cpu_data, cpu).hpa);
		जाओ set_out;
	पूर्ण
#पूर्ण_अगर
	stack_overflow_check(regs);

#अगर_घोषित CONFIG_IRQSTACKS
	execute_on_irq_stack(&generic_handle_irq, irq);
#अन्यथा
	generic_handle_irq(irq);
#पूर्ण_अगर /* CONFIG_IRQSTACKS */

 out:
	irq_निकास();
	set_irq_regs(old_regs);
	वापस;

 set_out:
	set_eiem(cpu_eiem & per_cpu(local_ack_eiem, cpu));
	जाओ out;
पूर्ण

अटल व्योम claim_cpu_irqs(व्योम)
अणु
	अचिन्हित दीर्घ flags = IRQF_TIMER | IRQF_PERCPU | IRQF_IRQPOLL;
	पूर्णांक i;

	क्रम (i = CPU_IRQ_BASE; i <= CPU_IRQ_MAX; i++) अणु
		irq_set_chip_and_handler(i, &cpu_पूर्णांकerrupt_type,
					 handle_percpu_irq);
	पूर्ण

	irq_set_handler(TIMER_IRQ, handle_percpu_irq);
	अगर (request_irq(TIMER_IRQ, समयr_पूर्णांकerrupt, flags, "timer", शून्य))
		pr_err("Failed to register timer interrupt\n");
#अगर_घोषित CONFIG_SMP
	irq_set_handler(IPI_IRQ, handle_percpu_irq);
	अगर (request_irq(IPI_IRQ, ipi_पूर्णांकerrupt, IRQF_PERCPU, "IPI", शून्य))
		pr_err("Failed to register IPI interrupt\n");
#पूर्ण_अगर
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	local_irq_disable();	/* PARANOID - should alपढ़ोy be disabled */
	mtctl(~0UL, 23);	/* EIRR : clear all pending बाह्यal पूर्णांकr */
#अगर_घोषित CONFIG_SMP
	अगर (!cpu_eiem) अणु
		claim_cpu_irqs();
		cpu_eiem = EIEM_MASK(IPI_IRQ) | EIEM_MASK(TIMER_IRQ);
	पूर्ण
#अन्यथा
	claim_cpu_irqs();
	cpu_eiem = EIEM_MASK(TIMER_IRQ);
#पूर्ण_अगर
        set_eiem(cpu_eiem);	/* EIEM : enable all बाह्यal पूर्णांकr */
पूर्ण
