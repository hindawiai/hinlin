<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/xtensa/kernel/irq.c
 *
 * Xtensa built-in पूर्णांकerrupt controller and some generic functions copied
 * from i386.
 *
 * Copyright (C) 2002 - 2013 Tensilica, Inc.
 * Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 *
 * Chris Zankel <chris@zankel.net>
 * Kevin Chea
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/xtensa-mx.h>
#समावेश <linux/irqchip/xtensa-pic.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/mxregs.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/platक्रमm.h>

DECLARE_PER_CPU(अचिन्हित दीर्घ, nmi_count);

यंत्रlinkage व्योम करो_IRQ(पूर्णांक hwirq, काष्ठा pt_regs *regs)
अणु
	पूर्णांक irq = irq_find_mapping(शून्य, hwirq);

#अगर_घोषित CONFIG_DEBUG_STACKOVERFLOW
	/* Debugging check क्रम stack overflow: is there less than 1KB मुक्त? */
	अणु
		अचिन्हित दीर्घ sp;

		__यंत्र__ __अस्थिर__ ("mov %0, a1\n" : "=a" (sp));
		sp &= THREAD_SIZE - 1;

		अगर (unlikely(sp < (माप(thपढ़ो_info) + 1024)))
			prपूर्णांकk("Stack overflow in do_IRQ: %ld\n",
			       sp - माप(काष्ठा thपढ़ो_info));
	पूर्ण
#पूर्ण_अगर
	generic_handle_irq(irq);
पूर्ण

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अचिन्हित cpu __maybe_unused;
#अगर_घोषित CONFIG_SMP
	show_ipi_list(p, prec);
#पूर्ण_अगर
#अगर XTENSA_FAKE_NMI
	seq_म_लिखो(p, "%*s:", prec, "NMI");
	क्रम_each_online_cpu(cpu)
		seq_म_लिखो(p, " %10lu", per_cpu(nmi_count, cpu));
	seq_माला_दो(p, "   Non-maskable interrupts\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक xtensa_irq_करोमुख्य_xlate(स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
		अचिन्हित दीर्घ पूर्णांक_irq, अचिन्हित दीर्घ ext_irq,
		अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 1 || पूर्णांकsize > 2))
		वापस -EINVAL;
	अगर (पूर्णांकsize == 2 && पूर्णांकspec[1] == 1) अणु
		पूर्णांक_irq = xtensa_map_ext_irq(ext_irq);
		अगर (पूर्णांक_irq < XCHAL_NUM_INTERRUPTS)
			*out_hwirq = पूर्णांक_irq;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		*out_hwirq = पूर्णांक_irq;
	पूर्ण
	*out_type = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण

पूर्णांक xtensa_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		irq_hw_number_t hw)
अणु
	काष्ठा irq_chip *irq_chip = d->host_data;
	u32 mask = 1 << hw;

	अगर (mask & XCHAL_INTTYPE_MASK_SOFTWARE) अणु
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_simple_irq, "level");
		irq_set_status_flags(irq, IRQ_LEVEL);
	पूर्ण अन्यथा अगर (mask & XCHAL_INTTYPE_MASK_EXTERN_EDGE) अणु
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_edge_irq, "edge");
		irq_clear_status_flags(irq, IRQ_LEVEL);
	पूर्ण अन्यथा अगर (mask & XCHAL_INTTYPE_MASK_EXTERN_LEVEL) अणु
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_level_irq, "level");
		irq_set_status_flags(irq, IRQ_LEVEL);
	पूर्ण अन्यथा अगर (mask & XCHAL_INTTYPE_MASK_TIMER) अणु
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_percpu_irq, "timer");
		irq_clear_status_flags(irq, IRQ_LEVEL);
#अगर_घोषित XCHAL_INTTYPE_MASK_PROFILING
	पूर्ण अन्यथा अगर (mask & XCHAL_INTTYPE_MASK_PROFILING) अणु
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_percpu_irq, "profiling");
		irq_set_status_flags(irq, IRQ_LEVEL);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु/* XCHAL_INTTYPE_MASK_WRITE_ERROR */
		/* XCHAL_INTTYPE_MASK_NMI */
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_level_irq, "level");
		irq_set_status_flags(irq, IRQ_LEVEL);
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित xtensa_map_ext_irq(अचिन्हित ext_irq)
अणु
	अचिन्हित mask = XCHAL_INTTYPE_MASK_EXTERN_EDGE |
		XCHAL_INTTYPE_MASK_EXTERN_LEVEL;
	अचिन्हित i;

	क्रम (i = 0; mask; ++i, mask >>= 1) अणु
		अगर ((mask & 1) && ext_irq-- == 0)
			वापस i;
	पूर्ण
	वापस XCHAL_NUM_INTERRUPTS;
पूर्ण

अचिन्हित xtensa_get_ext_irq_no(अचिन्हित irq)
अणु
	अचिन्हित mask = (XCHAL_INTTYPE_MASK_EXTERN_EDGE |
		XCHAL_INTTYPE_MASK_EXTERN_LEVEL) &
		((1u << irq) - 1);
	वापस hweight32(mask);
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
#अगर_घोषित CONFIG_OF
	irqchip_init();
#अन्यथा
#अगर_घोषित CONFIG_HAVE_SMP
	xtensa_mx_init_legacy(शून्य);
#अन्यथा
	xtensa_pic_init_legacy(शून्य);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	ipi_init();
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * The CPU has been marked offline.  Migrate IRQs off this CPU.  If
 * the affinity settings करो not allow other CPUs, क्रमce them onto any
 * available CPU.
 */
व्योम migrate_irqs(व्योम)
अणु
	अचिन्हित पूर्णांक i, cpu = smp_processor_id();

	क्रम_each_active_irq(i) अणु
		काष्ठा irq_data *data = irq_get_irq_data(i);
		काष्ठा cpumask *mask;
		अचिन्हित पूर्णांक newcpu;

		अगर (irqd_is_per_cpu(data))
			जारी;

		mask = irq_data_get_affinity_mask(data);
		अगर (!cpumask_test_cpu(cpu, mask))
			जारी;

		newcpu = cpumask_any_and(mask, cpu_online_mask);

		अगर (newcpu >= nr_cpu_ids) अणु
			pr_info_ratelimited("IRQ%u no longer affine to CPU%u\n",
					    i, cpu);

			cpumask_setall(mask);
		पूर्ण
		irq_set_affinity(i, mask);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */
