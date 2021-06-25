<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/irq.c
 *
 *	Copyright (C) 1995 Linus Torvalds
 *
 * This file contains the code used by various IRQ handling routines:
 * asking क्रम dअगरferent IRQ's should be करोne through these routines
 * instead of just grabbing them. Thus setups with dअगरferent IRQ numbers
 * shouldn't result in any weird surprises, and installing new handlers
 * should be easier.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/irq.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/profile.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

अस्थिर अचिन्हित दीर्घ irq_err_count;
DEFINE_PER_CPU(अचिन्हित दीर्घ, irq_pmi_count);

व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	irq_err_count++;
	prपूर्णांकk(KERN_CRIT "Unexpected IRQ trap at vector %u\n", irq);
पूर्ण

#अगर_घोषित CONFIG_SMP 
अटल अक्षर irq_user_affinity[NR_IRQS];

पूर्णांक irq_select_affinity(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(irq);
	काष्ठा irq_chip *chip;
	अटल पूर्णांक last_cpu;
	पूर्णांक cpu = last_cpu + 1;

	अगर (!data)
		वापस 1;
	chip = irq_data_get_irq_chip(data);

	अगर (!chip->irq_set_affinity || irq_user_affinity[irq])
		वापस 1;

	जबतक (!cpu_possible(cpu) ||
	       !cpumask_test_cpu(cpu, irq_शेष_affinity))
		cpu = (cpu < (NR_CPUS-1) ? cpu + 1 : 0);
	last_cpu = cpu;

	cpumask_copy(irq_data_get_affinity_mask(data), cpumask_of(cpu));
	chip->irq_set_affinity(data, cpumask_of(cpu), false);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

#अगर_घोषित CONFIG_SMP
	seq_माला_दो(p, "IPI: ");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10lu ", cpu_data[j].ipi_count);
	seq_अ_दो(p, '\n');
#पूर्ण_अगर
	seq_माला_दो(p, "PMI: ");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10lu ", per_cpu(irq_pmi_count, j));
	seq_माला_दो(p, "          Performance Monitoring\n");
	seq_म_लिखो(p, "ERR: %10lu\n", irq_err_count);
	वापस 0;
पूर्ण

/*
 * handle_irq handles all normal device IRQ's (the special
 * SMP cross-CPU पूर्णांकerrupts have their own specअगरic
 * handlers).
 */

#घोषणा MAX_ILLEGAL_IRQS 16

व्योम
handle_irq(पूर्णांक irq)
अणु	
	/* 
	 * We ack quickly, we करोn't want the irq controller
	 * thinking we're snobs just because some other CPU has
	 * disabled global पूर्णांकerrupts (we have alपढ़ोy करोne the
	 * INT_ACK cycles, it's too late to try to pretend to the
	 * controller that we aren't taking the पूर्णांकerrupt).
	 *
	 * 0 वापस value means that this irq is alपढ़ोy being
	 * handled by some other CPU. (or is disabled)
	 */
	अटल अचिन्हित पूर्णांक illegal_count=0;
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	
	अगर (!desc || ((अचिन्हित) irq > ACTUAL_NR_IRQS &&
	    illegal_count < MAX_ILLEGAL_IRQS)) अणु
		irq_err_count++;
		illegal_count++;
		prपूर्णांकk(KERN_CRIT "device_interrupt: invalid interrupt %d\n",
		       irq);
		वापस;
	पूर्ण

	irq_enter();
	generic_handle_irq_desc(desc);
	irq_निकास();
पूर्ण
