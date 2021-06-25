<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/irq.c
 *
 *  Copyright (C) 1992 Linus Torvalds
 *  Modअगरications क्रम ARM processor Copyright (C) 1995-2000 Russell King.
 *
 *  Support क्रम Dynamic Tick Timer Copyright (C) 2004-2005 Nokia Corporation.
 *  Dynamic Tick Timer written by Tony Lindgren <tony@atomide.com> and
 *  Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>.
 *
 *  This file contains the code used by various IRQ handling routines:
 *  asking क्रम dअगरferent IRQ's should be करोne through these routines
 *  instead of just grabbing them. Thus setups with dअगरferent IRQ numbers
 *  shouldn't result in any weird surprises, and installing new handlers
 *  should be easier.
 *
 *  IRQ's are in fact implemented a bit like संकेत handlers क्रम the kernel.
 *  Naturally it's not a 1:1 relation, but there are similarities.
 */
#समावेश <linux/संकेत.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/hardware/cache-uniphier.h>
#समावेश <यंत्र/outercache.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/समय.स>

अचिन्हित दीर्घ irq_err_count;

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
#अगर_घोषित CONFIG_FIQ
	show_fiq_list(p, prec);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	show_ipi_list(p, prec);
#पूर्ण_अगर
	seq_म_लिखो(p, "%*s: %10lu\n", prec, "Err", irq_err_count);
	वापस 0;
पूर्ण

/*
 * handle_IRQ handles all hardware IRQ's.  Decoded IRQs should
 * not come via this function.  Instead, they should provide their
 * own 'handler'.  Used by platक्रमm code implementing C-based 1st
 * level decoding.
 */
व्योम handle_IRQ(अचिन्हित पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	__handle_करोमुख्य_irq(शून्य, irq, false, regs);
पूर्ण

/*
 * यंत्र_करो_IRQ is the पूर्णांकerface to be used from assembly code.
 */
यंत्रlinkage व्योम __exception_irq_entry
यंत्र_करो_IRQ(अचिन्हित पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	handle_IRQ(irq, regs);
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_OF) && !machine_desc->init_irq)
		irqchip_init();
	अन्यथा
		machine_desc->init_irq();

	अगर (IS_ENABLED(CONFIG_OF) && IS_ENABLED(CONFIG_CACHE_L2X0) &&
	    (machine_desc->l2c_aux_mask || machine_desc->l2c_aux_val)) अणु
		अगर (!outer_cache.ग_लिखो_sec)
			outer_cache.ग_लिखो_sec = machine_desc->l2c_ग_लिखो_sec;
		ret = l2x0_of_init(machine_desc->l2c_aux_val,
				   machine_desc->l2c_aux_mask);
		अगर (ret && ret != -ENODEV)
			pr_err("L2C: failed to init: %d\n", ret);
	पूर्ण

	uniphier_cache_init();
पूर्ण

#अगर_घोषित CONFIG_SPARSE_IRQ
पूर्णांक __init arch_probe_nr_irqs(व्योम)
अणु
	nr_irqs = machine_desc->nr_irqs ? machine_desc->nr_irqs : NR_IRQS;
	वापस nr_irqs;
पूर्ण
#पूर्ण_अगर
