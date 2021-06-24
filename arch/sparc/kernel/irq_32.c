<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interrupt request handling routines. On the
 * Sparc the IRQs are basically 'cast in stone'
 * and you are supposed to probe the prom's device
 * node trees to find out who's got which IRQ.
 *
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)
 *  Copyright (C) 1995,2002 Pete A. Zaitcev (zaitcev@yahoo.com)
 *  Copyright (C) 1996 Dave Redman (djhr@tadpole.co.uk)
 *  Copyright (C) 1998-2000 Anton Blanअक्षरd (anton@samba.org)
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/pcic.h>
#समावेश <यंत्र/leon.h>

#समावेश "kernel.h"
#समावेश "irq.h"

/* platक्रमm specअगरic irq setup */
काष्ठा sparc_config sparc_config;

अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ retval;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"rd	%%psr, %0\n\t"
		"or	%0, %2, %1\n\t"
		"wr	%1, 0, %%psr\n\t"
		"nop; nop; nop\n"
		: "=&r" (retval), "=r" (पंचांगp)
		: "i" (PSR_PIL)
		: "memory");

	वापस retval;
पूर्ण
EXPORT_SYMBOL(arch_local_irq_save);

व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"rd	%%psr, %0\n\t"
		"andn	%0, %1, %0\n\t"
		"wr	%0, 0, %%psr\n\t"
		"nop; nop; nop\n"
		: "=&r" (पंचांगp)
		: "i" (PSR_PIL)
		: "memory");
पूर्ण
EXPORT_SYMBOL(arch_local_irq_enable);

व्योम arch_local_irq_restore(अचिन्हित दीर्घ old_psr)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"rd	%%psr, %0\n\t"
		"and	%2, %1, %2\n\t"
		"andn	%0, %1, %0\n\t"
		"wr	%0, %2, %%psr\n\t"
		"nop; nop; nop\n"
		: "=&r" (पंचांगp)
		: "i" (PSR_PIL), "r" (old_psr)
		: "memory");
पूर्ण
EXPORT_SYMBOL(arch_local_irq_restore);

/*
 * Dave Redman (djhr@tadpole.co.uk)
 *
 * IRQ numbers.. These are no दीर्घer restricted to 15..
 *
 * this is करोne to enable SBUS cards and onboard IO to be masked
 * correctly. using the पूर्णांकerrupt level isn't good enough.
 *
 * For example:
 *   A device पूर्णांकerrupting at sbus level6 and the Floppy both come in
 *   at IRQ11, but enabling and disabling them requires writing to
 *   dअगरferent bits in the SLAVIO/SEC.
 *
 * As a result of these changes sun4m machines could now support
 * directed CPU पूर्णांकerrupts using the existing enable/disable irq code
 * with tweaks.
 *
 * Sun4d complicates things even further.  IRQ numbers are arbitrary
 * 32-bit values in that हाल.  Since this is similar to sparc64,
 * we aकरोpt a भव IRQ numbering scheme as is करोne there.
 * Virutal पूर्णांकerrupt numbers are allocated by build_irq().  So NR_IRQS
 * just becomes a limit of how many पूर्णांकerrupt sources we can handle in
 * a single प्रणाली.  Even fully loaded SS2000 machines top off at
 * about 32 पूर्णांकerrupt sources or so, thereक्रमe a NR_IRQS value of 64
 * is more than enough.
  *
 * We keep a map of per-PIL enable पूर्णांकerrupts.  These get wired
 * up via the irq_chip->startup() method which माला_लो invoked by
 * the generic IRQ layer during request_irq().
 */


/* Table of allocated irqs. Unused entries has irq == 0 */
अटल काष्ठा irq_bucket irq_table[NR_IRQS];
/* Protect access to irq_table */
अटल DEFINE_SPINLOCK(irq_table_lock);

/* Map between the irq identअगरier used in hw to the irq_bucket. */
काष्ठा irq_bucket *irq_map[SUN4D_MAX_IRQ];
/* Protect access to irq_map */
अटल DEFINE_SPINLOCK(irq_map_lock);

/* Allocate a new irq from the irq_table */
अचिन्हित पूर्णांक irq_alloc(अचिन्हित पूर्णांक real_irq, अचिन्हित पूर्णांक pil)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&irq_table_lock, flags);
	क्रम (i = 1; i < NR_IRQS; i++) अणु
		अगर (irq_table[i].real_irq == real_irq && irq_table[i].pil == pil)
			जाओ found;
	पूर्ण

	क्रम (i = 1; i < NR_IRQS; i++) अणु
		अगर (!irq_table[i].irq)
			अवरोध;
	पूर्ण

	अगर (i < NR_IRQS) अणु
		irq_table[i].real_irq = real_irq;
		irq_table[i].irq = i;
		irq_table[i].pil = pil;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "IRQ: Out of virtual IRQs.\n");
		i = 0;
	पूर्ण
found:
	spin_unlock_irqrestore(&irq_table_lock, flags);

	वापस i;
पूर्ण

/* Based on a single pil handler_irq may need to call several
 * पूर्णांकerrupt handlers. Use irq_map as entry to irq_table,
 * and let each entry in irq_table poपूर्णांक to the next entry.
 */
व्योम irq_link(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_bucket *p;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pil;

	BUG_ON(irq >= NR_IRQS);

	spin_lock_irqsave(&irq_map_lock, flags);

	p = &irq_table[irq];
	pil = p->pil;
	BUG_ON(pil >= SUN4D_MAX_IRQ);
	p->next = irq_map[pil];
	irq_map[pil] = p;

	spin_unlock_irqrestore(&irq_map_lock, flags);
पूर्ण

व्योम irq_unlink(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_bucket *p, **pnext;
	अचिन्हित दीर्घ flags;

	BUG_ON(irq >= NR_IRQS);

	spin_lock_irqsave(&irq_map_lock, flags);

	p = &irq_table[irq];
	BUG_ON(p->pil >= SUN4D_MAX_IRQ);
	pnext = &irq_map[p->pil];
	जबतक (*pnext != p)
		pnext = &(*pnext)->next;
	*pnext = p->next;

	spin_unlock_irqrestore(&irq_map_lock, flags);
पूर्ण


/* /proc/पूर्णांकerrupts prपूर्णांकing */
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(p, "RES: ");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", cpu_data(j).irq_resched_count);
	seq_म_लिखो(p, "     IPI rescheduling interrupts\n");
	seq_म_लिखो(p, "CAL: ");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", cpu_data(j).irq_call_count);
	seq_म_लिखो(p, "     IPI function call interrupts\n");
#पूर्ण_अगर
	seq_म_लिखो(p, "NMI: ");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", cpu_data(j).counter);
	seq_म_लिखो(p, "     Non-maskable interrupts\n");
	वापस 0;
पूर्ण

व्योम handler_irq(अचिन्हित पूर्णांक pil, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;
	काष्ठा irq_bucket *p;

	BUG_ON(pil > 15);
	old_regs = set_irq_regs(regs);
	irq_enter();

	p = irq_map[pil];
	जबतक (p) अणु
		काष्ठा irq_bucket *next = p->next;

		generic_handle_irq(p->irq);
		p = next;
	पूर्ण
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

#अगर defined(CONFIG_BLK_DEV_FD) || defined(CONFIG_BLK_DEV_FD_MODULE)
अटल अचिन्हित पूर्णांक floppy_irq;

पूर्णांक sparc_floppy_request_irq(अचिन्हित पूर्णांक irq, irq_handler_t irq_handler)
अणु
	अचिन्हित पूर्णांक cpu_irq;
	पूर्णांक err;


	err = request_irq(irq, irq_handler, 0, "floppy", शून्य);
	अगर (err)
		वापस -1;

	/* Save क्रम later use in floppy पूर्णांकerrupt handler */
	floppy_irq = irq;

	cpu_irq = (irq & (NR_IRQS - 1));

	/* Dork with trap table अगर we get this far. */
#घोषणा INSTANTIATE(table) \
	table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_one = SPARC_RD_PSR_L0; \
	table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_two = \
		SPARC_BRANCH((अचिन्हित दीर्घ) floppy_hardपूर्णांक, \
			     (अचिन्हित दीर्घ) &table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_two);\
	table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_three = SPARC_RD_WIM_L3; \
	table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_four = SPARC_NOP;

	INSTANTIATE(sparc_ttable)

#अगर defined CONFIG_SMP
	अगर (sparc_cpu_model != sparc_leon) अणु
		काष्ठा tt_entry *trap_table;

		trap_table = &trapbase_cpu1;
		INSTANTIATE(trap_table)
		trap_table = &trapbase_cpu2;
		INSTANTIATE(trap_table)
		trap_table = &trapbase_cpu3;
		INSTANTIATE(trap_table)
	पूर्ण
#पूर्ण_अगर
#अघोषित INSTANTIATE
	/*
	 * XXX Correct thing whould be to flush only I- and D-cache lines
	 * which contain the handler in question. But as of समय of the
	 * writing we have no CPU-neutral पूर्णांकerface to fine-grained flushes.
	 */
	flush_cache_all();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sparc_floppy_request_irq);

/*
 * These variables are used to access state from the assembler
 * पूर्णांकerrupt handler, floppy_hardपूर्णांक, so we cannot put these in
 * the floppy driver image because that would not work in the
 * modular हाल.
 */
अस्थिर अचिन्हित अक्षर *fdc_status;
EXPORT_SYMBOL(fdc_status);

अक्षर *pdma_vaddr;
EXPORT_SYMBOL(pdma_vaddr);

अचिन्हित दीर्घ pdma_size;
EXPORT_SYMBOL(pdma_size);

अस्थिर पूर्णांक करोing_pdma;
EXPORT_SYMBOL(करोing_pdma);

अक्षर *pdma_base;
EXPORT_SYMBOL(pdma_base);

अचिन्हित दीर्घ pdma_areasize;
EXPORT_SYMBOL(pdma_areasize);

/* Use the generic irq support to call floppy_पूर्णांकerrupt
 * which was setup using request_irq() in sparc_floppy_request_irq().
 * We only have one floppy पूर्णांकerrupt so we करो not need to check
 * क्रम additional handlers being wired up by irq_link()
 */
व्योम sparc_floppy_irq(पूर्णांक irq, व्योम *dev_id, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;

	old_regs = set_irq_regs(regs);
	irq_enter();
	generic_handle_irq(floppy_irq);
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण
#पूर्ण_अगर

/* djhr
 * This could probably be made indirect too and asचिन्हित in the CPU
 * bits of the code. That would be much nicer I think and would also
 * fit in with the idea of being able to tune your kernel क्रम your machine
 * by removing unrequired machine and device support.
 *
 */

व्योम __init init_IRQ(व्योम)
अणु
	चयन (sparc_cpu_model) अणु
	हाल sun4m:
		pcic_probe();
		अगर (pcic_present())
			sun4m_pci_init_IRQ();
		अन्यथा
			sun4m_init_IRQ();
		अवरोध;

	हाल sun4d:
		sun4d_init_IRQ();
		अवरोध;

	हाल sparc_leon:
		leon_init_IRQ();
		अवरोध;

	शेष:
		prom_म_लिखो("Cannot initialize IRQs on this Sun machine...");
		अवरोध;
	पूर्ण
पूर्ण

