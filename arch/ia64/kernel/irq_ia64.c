<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/ia64/kernel/irq_ia64.c
 *
 * Copyright (C) 1998-2001 Hewlett-Packard Co
 *	Stephane Eranian <eranian@hpl.hp.com>
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 *  6/10/99: Updated to bring in sync with x86 version to facilitate
 *	     support क्रम SMP and dअगरferent पूर्णांकerrupt controllers.
 *
 * 09/15/00 Goutham Rao <goutham.rao@पूर्णांकel.com> Implemented pci_irq_to_vector
 *                      PCI to vector allocation routine.
 * 04/14/2004 Ashok Raj <ashok.raj@पूर्णांकel.com>
 *						Added CPU Hotplug handling क्रम IPF.
 */

#समावेश <linux/module.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/acpi.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/tlbflush.h>

#घोषणा IRQ_DEBUG	0

#घोषणा IRQ_VECTOR_UNASSIGNED	(0)

#घोषणा IRQ_UNUSED		(0)
#घोषणा IRQ_USED		(1)
#घोषणा IRQ_RSVD		(2)

पूर्णांक ia64_first_device_vector = IA64_DEF_FIRST_DEVICE_VECTOR;
पूर्णांक ia64_last_device_vector = IA64_DEF_LAST_DEVICE_VECTOR;

/* शेष base addr of IPI table */
व्योम __iomem *ipi_base_addr = ((व्योम __iomem *)
			       (__IA64_UNCACHED_OFFSET | IA64_IPI_DEFAULT_BASE_ADDR));

अटल cpumask_t vector_allocation_करोमुख्य(पूर्णांक cpu);

/*
 * Legacy IRQ to IA-64 vector translation table.
 */
__u8 isa_irq_to_vector_map[16] = अणु
	/* 8259 IRQ translation, first 16 entries */
	0x2f, 0x20, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x29,
	0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21
पूर्ण;
EXPORT_SYMBOL(isa_irq_to_vector_map);

DEFINE_SPINLOCK(vector_lock);

काष्ठा irq_cfg irq_cfg[NR_IRQS] __पढ़ो_mostly = अणु
	[0 ... NR_IRQS - 1] = अणु
		.vector = IRQ_VECTOR_UNASSIGNED,
		.करोमुख्य = CPU_MASK_NONE
	पूर्ण
पूर्ण;

DEFINE_PER_CPU(पूर्णांक[IA64_NUM_VECTORS], vector_irq) = अणु
	[0 ... IA64_NUM_VECTORS - 1] = -1
पूर्ण;

अटल cpumask_t vector_table[IA64_NUM_VECTORS] = अणु
	[0 ... IA64_NUM_VECTORS - 1] = CPU_MASK_NONE
पूर्ण;

अटल पूर्णांक irq_status[NR_IRQS] = अणु
	[0 ... NR_IRQS -1] = IRQ_UNUSED
पूर्ण;

अटल अंतरभूत पूर्णांक find_unasचिन्हित_irq(व्योम)
अणु
	पूर्णांक irq;

	क्रम (irq = IA64_FIRST_DEVICE_VECTOR; irq < NR_IRQS; irq++)
		अगर (irq_status[irq] == IRQ_UNUSED)
			वापस irq;
	वापस -ENOSPC;
पूर्ण

अटल अंतरभूत पूर्णांक find_unasचिन्हित_vector(cpumask_t करोमुख्य)
अणु
	cpumask_t mask;
	पूर्णांक pos, vector;

	cpumask_and(&mask, &करोमुख्य, cpu_online_mask);
	अगर (cpumask_empty(&mask))
		वापस -EINVAL;

	क्रम (pos = 0; pos < IA64_NUM_DEVICE_VECTORS; pos++) अणु
		vector = IA64_FIRST_DEVICE_VECTOR + pos;
		cpumask_and(&mask, &करोमुख्य, &vector_table[vector]);
		अगर (!cpumask_empty(&mask))
			जारी;
		वापस vector;
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक __bind_irq_vector(पूर्णांक irq, पूर्णांक vector, cpumask_t करोमुख्य)
अणु
	cpumask_t mask;
	पूर्णांक cpu;
	काष्ठा irq_cfg *cfg = &irq_cfg[irq];

	BUG_ON((अचिन्हित)irq >= NR_IRQS);
	BUG_ON((अचिन्हित)vector >= IA64_NUM_VECTORS);

	cpumask_and(&mask, &करोमुख्य, cpu_online_mask);
	अगर (cpumask_empty(&mask))
		वापस -EINVAL;
	अगर ((cfg->vector == vector) && cpumask_equal(&cfg->करोमुख्य, &करोमुख्य))
		वापस 0;
	अगर (cfg->vector != IRQ_VECTOR_UNASSIGNED)
		वापस -EBUSY;
	क्रम_each_cpu(cpu, &mask)
		per_cpu(vector_irq, cpu)[vector] = irq;
	cfg->vector = vector;
	cfg->करोमुख्य = करोमुख्य;
	irq_status[irq] = IRQ_USED;
	cpumask_or(&vector_table[vector], &vector_table[vector], &करोमुख्य);
	वापस 0;
पूर्ण

पूर्णांक bind_irq_vector(पूर्णांक irq, पूर्णांक vector, cpumask_t करोमुख्य)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&vector_lock, flags);
	ret = __bind_irq_vector(irq, vector, करोमुख्य);
	spin_unlock_irqrestore(&vector_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम __clear_irq_vector(पूर्णांक irq)
अणु
	पूर्णांक vector, cpu;
	cpumask_t करोमुख्य;
	काष्ठा irq_cfg *cfg = &irq_cfg[irq];

	BUG_ON((अचिन्हित)irq >= NR_IRQS);
	BUG_ON(cfg->vector == IRQ_VECTOR_UNASSIGNED);
	vector = cfg->vector;
	करोमुख्य = cfg->करोमुख्य;
	क्रम_each_cpu_and(cpu, &cfg->करोमुख्य, cpu_online_mask)
		per_cpu(vector_irq, cpu)[vector] = -1;
	cfg->vector = IRQ_VECTOR_UNASSIGNED;
	cfg->करोमुख्य = CPU_MASK_NONE;
	irq_status[irq] = IRQ_UNUSED;
	cpumask_andnot(&vector_table[vector], &vector_table[vector], &करोमुख्य);
पूर्ण

अटल व्योम clear_irq_vector(पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vector_lock, flags);
	__clear_irq_vector(irq);
	spin_unlock_irqrestore(&vector_lock, flags);
पूर्ण

पूर्णांक
ia64_native_assign_irq_vector (पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक vector, cpu;
	cpumask_t करोमुख्य = CPU_MASK_NONE;

	vector = -ENOSPC;

	spin_lock_irqsave(&vector_lock, flags);
	क्रम_each_online_cpu(cpu) अणु
		करोमुख्य = vector_allocation_करोमुख्य(cpu);
		vector = find_unasचिन्हित_vector(करोमुख्य);
		अगर (vector >= 0)
			अवरोध;
	पूर्ण
	अगर (vector < 0)
		जाओ out;
	अगर (irq == AUTO_ASSIGN)
		irq = vector;
	BUG_ON(__bind_irq_vector(irq, vector, करोमुख्य));
 out:
	spin_unlock_irqrestore(&vector_lock, flags);
	वापस vector;
पूर्ण

व्योम
ia64_native_मुक्त_irq_vector (पूर्णांक vector)
अणु
	अगर (vector < IA64_FIRST_DEVICE_VECTOR ||
	    vector > IA64_LAST_DEVICE_VECTOR)
		वापस;
	clear_irq_vector(vector);
पूर्ण

पूर्णांक
reserve_irq_vector (पूर्णांक vector)
अणु
	अगर (vector < IA64_FIRST_DEVICE_VECTOR ||
	    vector > IA64_LAST_DEVICE_VECTOR)
		वापस -EINVAL;
	वापस !!bind_irq_vector(vector, vector, CPU_MASK_ALL);
पूर्ण

/*
 * Initialize vector_irq on a new cpu. This function must be called
 * with vector_lock held.
 */
व्योम __setup_vector_irq(पूर्णांक cpu)
अणु
	पूर्णांक irq, vector;

	/* Clear vector_irq */
	क्रम (vector = 0; vector < IA64_NUM_VECTORS; ++vector)
		per_cpu(vector_irq, cpu)[vector] = -1;
	/* Mark the inuse vectors */
	क्रम (irq = 0; irq < NR_IRQS; ++irq) अणु
		अगर (!cpumask_test_cpu(cpu, &irq_cfg[irq].करोमुख्य))
			जारी;
		vector = irq_to_vector(irq);
		per_cpu(vector_irq, cpu)[vector] = irq;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल क्रमागत vector_करोमुख्य_type अणु
	VECTOR_DOMAIN_NONE,
	VECTOR_DOMAIN_PERCPU
पूर्ण vector_करोमुख्य_type = VECTOR_DOMAIN_NONE;

अटल cpumask_t vector_allocation_करोमुख्य(पूर्णांक cpu)
अणु
	अगर (vector_करोमुख्य_type == VECTOR_DOMAIN_PERCPU)
		वापस *cpumask_of(cpu);
	वापस CPU_MASK_ALL;
पूर्ण

अटल पूर्णांक __irq_prepare_move(पूर्णांक irq, पूर्णांक cpu)
अणु
	काष्ठा irq_cfg *cfg = &irq_cfg[irq];
	पूर्णांक vector;
	cpumask_t करोमुख्य;

	अगर (cfg->move_in_progress || cfg->move_cleanup_count)
		वापस -EBUSY;
	अगर (cfg->vector == IRQ_VECTOR_UNASSIGNED || !cpu_online(cpu))
		वापस -EINVAL;
	अगर (cpumask_test_cpu(cpu, &cfg->करोमुख्य))
		वापस 0;
	करोमुख्य = vector_allocation_करोमुख्य(cpu);
	vector = find_unasचिन्हित_vector(करोमुख्य);
	अगर (vector < 0)
		वापस -ENOSPC;
	cfg->move_in_progress = 1;
	cfg->old_करोमुख्य = cfg->करोमुख्य;
	cfg->vector = IRQ_VECTOR_UNASSIGNED;
	cfg->करोमुख्य = CPU_MASK_NONE;
	BUG_ON(__bind_irq_vector(irq, vector, करोमुख्य));
	वापस 0;
पूर्ण

पूर्णांक irq_prepare_move(पूर्णांक irq, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&vector_lock, flags);
	ret = __irq_prepare_move(irq, cpu);
	spin_unlock_irqrestore(&vector_lock, flags);
	वापस ret;
पूर्ण

व्योम irq_complete_move(अचिन्हित irq)
अणु
	काष्ठा irq_cfg *cfg = &irq_cfg[irq];
	cpumask_t cleanup_mask;
	पूर्णांक i;

	अगर (likely(!cfg->move_in_progress))
		वापस;

	अगर (unlikely(cpumask_test_cpu(smp_processor_id(), &cfg->old_करोमुख्य)))
		वापस;

	cpumask_and(&cleanup_mask, &cfg->old_करोमुख्य, cpu_online_mask);
	cfg->move_cleanup_count = cpumask_weight(&cleanup_mask);
	क्रम_each_cpu(i, &cleanup_mask)
		ia64_send_ipi(i, IA64_IRQ_MOVE_VECTOR, IA64_IPI_DM_INT, 0);
	cfg->move_in_progress = 0;
पूर्ण

अटल irqवापस_t smp_irq_move_cleanup_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक me = smp_processor_id();
	ia64_vector vector;
	अचिन्हित दीर्घ flags;

	क्रम (vector = IA64_FIRST_DEVICE_VECTOR;
	     vector < IA64_LAST_DEVICE_VECTOR; vector++) अणु
		पूर्णांक irq;
		काष्ठा irq_desc *desc;
		काष्ठा irq_cfg *cfg;
		irq = __this_cpu_पढ़ो(vector_irq[vector]);
		अगर (irq < 0)
			जारी;

		desc = irq_to_desc(irq);
		cfg = irq_cfg + irq;
		raw_spin_lock(&desc->lock);
		अगर (!cfg->move_cleanup_count)
			जाओ unlock;

		अगर (!cpumask_test_cpu(me, &cfg->old_करोमुख्य))
			जाओ unlock;

		spin_lock_irqsave(&vector_lock, flags);
		__this_cpu_ग_लिखो(vector_irq[vector], -1);
		cpumask_clear_cpu(me, &vector_table[vector]);
		spin_unlock_irqrestore(&vector_lock, flags);
		cfg->move_cleanup_count--;
	unlock:
		raw_spin_unlock(&desc->lock);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init parse_vector_करोमुख्य(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;
	अगर (!म_भेद(arg, "percpu")) अणु
		vector_करोमुख्य_type = VECTOR_DOMAIN_PERCPU;
		no_पूर्णांक_routing = 1;
	पूर्ण
	वापस 0;
पूर्ण
early_param("vector", parse_vector_करोमुख्य);
#अन्यथा
अटल cpumask_t vector_allocation_करोमुख्य(पूर्णांक cpu)
अणु
	वापस CPU_MASK_ALL;
पूर्ण
#पूर्ण_अगर


व्योम destroy_and_reserve_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;

	irq_init_desc(irq);
	spin_lock_irqsave(&vector_lock, flags);
	__clear_irq_vector(irq);
	irq_status[irq] = IRQ_RSVD;
	spin_unlock_irqrestore(&vector_lock, flags);
पूर्ण

/*
 * Dynamic irq allocate and deallocation क्रम MSI
 */
पूर्णांक create_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक irq, vector, cpu;
	cpumask_t करोमुख्य = CPU_MASK_NONE;

	irq = vector = -ENOSPC;
	spin_lock_irqsave(&vector_lock, flags);
	क्रम_each_online_cpu(cpu) अणु
		करोमुख्य = vector_allocation_करोमुख्य(cpu);
		vector = find_unasचिन्हित_vector(करोमुख्य);
		अगर (vector >= 0)
			अवरोध;
	पूर्ण
	अगर (vector < 0)
		जाओ out;
	irq = find_unasचिन्हित_irq();
	अगर (irq < 0)
		जाओ out;
	BUG_ON(__bind_irq_vector(irq, vector, करोमुख्य));
 out:
	spin_unlock_irqrestore(&vector_lock, flags);
	अगर (irq >= 0)
		irq_init_desc(irq);
	वापस irq;
पूर्ण

व्योम destroy_irq(अचिन्हित पूर्णांक irq)
अणु
	irq_init_desc(irq);
	clear_irq_vector(irq);
पूर्ण

#अगर_घोषित CONFIG_SMP
#	define IS_RESCHEDULE(vec)	(vec == IA64_IPI_RESCHEDULE)
#	define IS_LOCAL_TLB_FLUSH(vec)	(vec == IA64_IPI_LOCAL_TLB_FLUSH)
#अन्यथा
#	define IS_RESCHEDULE(vec)	(0)
#	define IS_LOCAL_TLB_FLUSH(vec)	(0)
#पूर्ण_अगर
/*
 * That's where the IVT branches when we get an बाह्यal
 * पूर्णांकerrupt. This branches to the correct hardware IRQ handler via
 * function ptr.
 */
व्योम
ia64_handle_irq (ia64_vector vector, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	अचिन्हित दीर्घ saved_tpr;

#अगर IRQ_DEBUG
	अणु
		अचिन्हित दीर्घ bsp, sp;

		/*
		 * Note: अगर the पूर्णांकerrupt happened जबतक executing in
		 * the context चयन routine (ia64_चयन_to), we may
		 * get a spurious stack overflow here.  This is
		 * because the रेजिस्टर and the memory stack are not
		 * चयनed atomically.
		 */
		bsp = ia64_getreg(_IA64_REG_AR_BSP);
		sp = ia64_getreg(_IA64_REG_SP);

		अगर ((sp - bsp) < 1024) अणु
			अटल DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 5);

			अगर (__ratelimit(&ratelimit)) अणु
				prपूर्णांकk("ia64_handle_irq: DANGER: less than "
				       "1KB of free stack space!!\n"
				       "(bsp=0x%lx, sp=%lx)\n", bsp, sp);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* IRQ_DEBUG */

	/*
	 * Always set TPR to limit maximum पूर्णांकerrupt nesting depth to
	 * 16 (without this, it would be ~240, which could easily lead
	 * to kernel stack overflows).
	 */
	irq_enter();
	saved_tpr = ia64_getreg(_IA64_REG_CR_TPR);
	ia64_srlz_d();
	जबतक (vector != IA64_SPURIOUS_INT_VECTOR) अणु
		पूर्णांक irq = local_vector_to_irq(vector);

		अगर (unlikely(IS_LOCAL_TLB_FLUSH(vector))) अणु
			smp_local_flush_tlb();
			kstat_incr_irq_this_cpu(irq);
		पूर्ण अन्यथा अगर (unlikely(IS_RESCHEDULE(vector))) अणु
			scheduler_ipi();
			kstat_incr_irq_this_cpu(irq);
		पूर्ण अन्यथा अणु
			ia64_setreg(_IA64_REG_CR_TPR, vector);
			ia64_srlz_d();

			अगर (unlikely(irq < 0)) अणु
				prपूर्णांकk(KERN_ERR "%s: Unexpected interrupt "
				       "vector %d on CPU %d is not mapped "
				       "to any IRQ!\n", __func__, vector,
				       smp_processor_id());
			पूर्ण अन्यथा
				generic_handle_irq(irq);

			/*
			 * Disable पूर्णांकerrupts and send EOI:
			 */
			local_irq_disable();
			ia64_setreg(_IA64_REG_CR_TPR, saved_tpr);
		पूर्ण
		ia64_eoi();
		vector = ia64_get_ivr();
	पूर्ण
	/*
	 * This must be करोne *after* the ia64_eoi().  For example, the keyboard softirq
	 * handler needs to be able to रुको क्रम further keyboard पूर्णांकerrupts, which can't
	 * come through until ia64_eoi() has been करोne.
	 */
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * This function emulates a पूर्णांकerrupt processing when a cpu is about to be
 * brought करोwn.
 */
व्योम ia64_process_pending_पूर्णांकr(व्योम)
अणु
	ia64_vector vector;
	अचिन्हित दीर्घ saved_tpr;
	बाह्य अचिन्हित पूर्णांक vectors_in_migration[NR_IRQS];

	vector = ia64_get_ivr();

	irq_enter();
	saved_tpr = ia64_getreg(_IA64_REG_CR_TPR);
	ia64_srlz_d();

	 /*
	  * Perक्रमm normal पूर्णांकerrupt style processing
	  */
	जबतक (vector != IA64_SPURIOUS_INT_VECTOR) अणु
		पूर्णांक irq = local_vector_to_irq(vector);

		अगर (unlikely(IS_LOCAL_TLB_FLUSH(vector))) अणु
			smp_local_flush_tlb();
			kstat_incr_irq_this_cpu(irq);
		पूर्ण अन्यथा अगर (unlikely(IS_RESCHEDULE(vector))) अणु
			kstat_incr_irq_this_cpu(irq);
		पूर्ण अन्यथा अणु
			काष्ठा pt_regs *old_regs = set_irq_regs(शून्य);

			ia64_setreg(_IA64_REG_CR_TPR, vector);
			ia64_srlz_d();

			/*
			 * Now try calling normal ia64_handle_irq as it would have got called
			 * from a real पूर्णांकr handler. Try passing null क्रम pt_regs, hopefully
			 * it will work. I hope it works!.
			 * Probably could shared code.
			 */
			अगर (unlikely(irq < 0)) अणु
				prपूर्णांकk(KERN_ERR "%s: Unexpected interrupt "
				       "vector %d on CPU %d not being mapped "
				       "to any IRQ!!\n", __func__, vector,
				       smp_processor_id());
			पूर्ण अन्यथा अणु
				vectors_in_migration[irq]=0;
				generic_handle_irq(irq);
			पूर्ण
			set_irq_regs(old_regs);

			/*
			 * Disable पूर्णांकerrupts and send EOI
			 */
			local_irq_disable();
			ia64_setreg(_IA64_REG_CR_TPR, saved_tpr);
		पूर्ण
		ia64_eoi();
		vector = ia64_get_ivr();
	पूर्ण
	irq_निकास();
पूर्ण
#पूर्ण_अगर


#अगर_घोषित CONFIG_SMP

अटल irqवापस_t dummy_handler (पूर्णांक irq, व्योम *dev_id)
अणु
	BUG();
	वापस IRQ_NONE;
पूर्ण

/*
 * KVM uses this पूर्णांकerrupt to क्रमce a cpu out of guest mode
 */

#पूर्ण_अगर

व्योम
रेजिस्टर_percpu_irq(ia64_vector vec, irq_handler_t handler, अचिन्हित दीर्घ flags,
		    स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक irq;

	irq = vec;
	BUG_ON(bind_irq_vector(irq, vec, CPU_MASK_ALL));
	irq_set_status_flags(irq, IRQ_PER_CPU);
	irq_set_chip(irq, &irq_type_ia64_lsapic);
	अगर (handler)
		अगर (request_irq(irq, handler, flags, name, शून्य))
			pr_err("Failed to request irq %u (%s)\n", irq, name);
	irq_set_handler(irq, handle_percpu_irq);
पूर्ण

व्योम __init
ia64_native_रेजिस्टर_ipi(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	रेजिस्टर_percpu_irq(IA64_IPI_VECTOR, handle_IPI, 0, "IPI");
	रेजिस्टर_percpu_irq(IA64_IPI_RESCHEDULE, dummy_handler, 0, "resched");
	रेजिस्टर_percpu_irq(IA64_IPI_LOCAL_TLB_FLUSH, dummy_handler, 0,
			    "tlb_flush");
#पूर्ण_अगर
पूर्ण

व्योम __init
init_IRQ (व्योम)
अणु
	acpi_boot_init();
	ia64_रेजिस्टर_ipi();
	रेजिस्टर_percpu_irq(IA64_SPURIOUS_INT_VECTOR, शून्य, 0, शून्य);
#अगर_घोषित CONFIG_SMP
	अगर (vector_करोमुख्य_type != VECTOR_DOMAIN_NONE) अणु
		रेजिस्टर_percpu_irq(IA64_IRQ_MOVE_VECTOR,
				    smp_irq_move_cleanup_पूर्णांकerrupt, 0,
				    "irq_move");
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम
ia64_send_ipi (पूर्णांक cpu, पूर्णांक vector, पूर्णांक delivery_mode, पूर्णांक redirect)
अणु
	व्योम __iomem *ipi_addr;
	अचिन्हित दीर्घ ipi_data;
	अचिन्हित दीर्घ phys_cpu_id;

	phys_cpu_id = cpu_physical_id(cpu);

	/*
	 * cpu number is in 8bit ID and 8bit EID
	 */

	ipi_data = (delivery_mode << 8) | (vector & 0xff);
	ipi_addr = ipi_base_addr + ((phys_cpu_id << 4) | ((redirect & 1) << 3));

	ग_लिखोq(ipi_data, ipi_addr);
पूर्ण
