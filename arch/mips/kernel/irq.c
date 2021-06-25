<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Code to handle x86 style IRQs plus some generic पूर्णांकerrupt stuff.
 *
 * Copyright (C) 1992 Linus Torvalds
 * Copyright (C) 1994 - 2000 Ralf Baechle
 */
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/ftrace.h>

#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>

व्योम *irq_stack[NR_CPUS];

/*
 * 'what should we do if we get a hw irq event on an illegal vector'.
 * each architecture has to answer this themselves.
 */
व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	prपूर्णांकk("unexpected IRQ # %d\n", irq);
पूर्ण

atomic_t irq_err_count;

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	seq_म_लिखो(p, "%*s: %10u\n", prec, "ERR", atomic_पढ़ो(&irq_err_count));
	वापस 0;
पूर्ण

यंत्रlinkage व्योम spurious_पूर्णांकerrupt(व्योम)
अणु
	atomic_inc(&irq_err_count);
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक order = get_order(IRQ_STACK_SIZE);

	क्रम (i = 0; i < NR_IRQS; i++)
		irq_set_noprobe(i);

	अगर (cpu_has_veic)
		clear_c0_status(ST0_IM);

	arch_init_irq();

	क्रम_each_possible_cpu(i) अणु
		व्योम *s = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, order);

		irq_stack[i] = s;
		pr_debug("CPU%d IRQ stack at 0x%p - 0x%p\n", i,
			irq_stack[i], irq_stack[i] + IRQ_STACK_SIZE);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_STACKOVERFLOW
अटल अंतरभूत व्योम check_stack_overflow(व्योम)
अणु
	अचिन्हित दीर्घ sp;

	__यंत्र__ __अस्थिर__("move %0, $sp" : "=r" (sp));
	sp &= THREAD_MASK;

	/*
	 * Check क्रम stack overflow: is there less than STACK_WARN मुक्त?
	 * STACK_WARN is defined as 1/8 of THREAD_SIZE by शेष.
	 */
	अगर (unlikely(sp < (माप(काष्ठा thपढ़ो_info) + STACK_WARN))) अणु
		prपूर्णांकk("do_IRQ: stack overflow: %ld\n",
		       sp - माप(काष्ठा thपढ़ो_info));
		dump_stack();
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम check_stack_overflow(व्योम) अणुपूर्ण
#पूर्ण_अगर


/*
 * करो_IRQ handles all normal device IRQ's (the special
 * SMP cross-CPU पूर्णांकerrupts have their own specअगरic
 * handlers).
 */
व्योम __irq_entry करो_IRQ(अचिन्हित पूर्णांक irq)
अणु
	irq_enter();
	check_stack_overflow();
	generic_handle_irq(irq);
	irq_निकास();
पूर्ण

