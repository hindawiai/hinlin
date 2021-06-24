<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/irq.c
 *
 * Copyright (C) 1992 Linus Torvalds
 * Modअगरications क्रम ARM processor Copyright (C) 1995-2000 Russell King.
 * Support क्रम Dynamic Tick Timer Copyright (C) 2004-2005 Nokia Corporation.
 * Dynamic Tick Timer written by Tony Lindgren <tony@atomide.com> and
 * Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/irq.h>
#समावेश <linux/memory.h>
#समावेश <linux/smp.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/scs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/vmap_stack.h>

/* Only access this in an NMI enter/निकास */
DEFINE_PER_CPU(काष्ठा nmi_ctx, nmi_contexts);

DEFINE_PER_CPU(अचिन्हित दीर्घ *, irq_stack_ptr);


DECLARE_PER_CPU(अचिन्हित दीर्घ *, irq_shaकरोw_call_stack_ptr);

#अगर_घोषित CONFIG_SHADOW_CALL_STACK
DEFINE_PER_CPU(अचिन्हित दीर्घ *, irq_shaकरोw_call_stack_ptr);
#पूर्ण_अगर

अटल व्योम init_irq_scs(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!IS_ENABLED(CONFIG_SHADOW_CALL_STACK))
		वापस;

	क्रम_each_possible_cpu(cpu)
		per_cpu(irq_shaकरोw_call_stack_ptr, cpu) =
			scs_alloc(cpu_to_node(cpu));
पूर्ण

#अगर_घोषित CONFIG_VMAP_STACK
अटल व्योम init_irq_stacks(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ *p;

	क्रम_each_possible_cpu(cpu) अणु
		p = arch_alloc_vmap_stack(IRQ_STACK_SIZE, cpu_to_node(cpu));
		per_cpu(irq_stack_ptr, cpu) = p;
	पूर्ण
पूर्ण
#अन्यथा
/* irq stack only needs to be 16 byte aligned - not IRQ_STACK_SIZE aligned. */
DEFINE_PER_CPU_ALIGNED(अचिन्हित दीर्घ [IRQ_STACK_SIZE/माप(दीर्घ)], irq_stack);

अटल व्योम init_irq_stacks(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		per_cpu(irq_stack_ptr, cpu) = per_cpu(irq_stack, cpu);
पूर्ण
#पूर्ण_अगर

अटल व्योम शेष_handle_irq(काष्ठा pt_regs *regs)
अणु
	panic("IRQ taken without a root IRQ handler\n");
पूर्ण

अटल व्योम शेष_handle_fiq(काष्ठा pt_regs *regs)
अणु
	panic("FIQ taken without a root FIQ handler\n");
पूर्ण

व्योम (*handle_arch_irq)(काष्ठा pt_regs *) __ro_after_init = शेष_handle_irq;
व्योम (*handle_arch_fiq)(काष्ठा pt_regs *) __ro_after_init = शेष_handle_fiq;

पूर्णांक __init set_handle_irq(व्योम (*handle_irq)(काष्ठा pt_regs *))
अणु
	अगर (handle_arch_irq != शेष_handle_irq)
		वापस -EBUSY;

	handle_arch_irq = handle_irq;
	pr_info("Root IRQ handler: %ps\n", handle_irq);
	वापस 0;
पूर्ण

पूर्णांक __init set_handle_fiq(व्योम (*handle_fiq)(काष्ठा pt_regs *))
अणु
	अगर (handle_arch_fiq != शेष_handle_fiq)
		वापस -EBUSY;

	handle_arch_fiq = handle_fiq;
	pr_info("Root FIQ handler: %ps\n", handle_fiq);
	वापस 0;
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	init_irq_stacks();
	init_irq_scs();
	irqchip_init();

	अगर (प्रणाली_uses_irq_prio_masking()) अणु
		/*
		 * Now that we have a stack क्रम our IRQ handler, set
		 * the PMR/PSR pair to a consistent state.
		 */
		WARN_ON(पढ़ो_sysreg(daअगर) & PSR_A_BIT);
		local_daअगर_restore(DAIF_PROCCTX_NOIRQ);
	पूर्ण
पूर्ण
