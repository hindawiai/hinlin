<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/ia64/kernel/irq.c
 *
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 * This file contains the code used by various IRQ handling routines:
 * asking क्रम dअगरferent IRQs should be करोne through these routines
 * instead of just grabbing them. Thus setups with dअगरferent IRQ numbers
 * shouldn't result in any weird surprises, and installing new handlers
 * should be easier.
 *
 * Copyright (C) Ashok Raj<ashok.raj@पूर्णांकel.com>, Intel Corporation 2004
 *
 * 4/14/2004: Added code to handle cpu migration and करो safe irq
 *			migration without losing पूर्णांकerrupts क्रम iosapic
 *			architecture.
 */

#समावेश <यंत्र/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <यंत्र/mca.h>
#समावेश <यंत्र/xtp.h>

/*
 * 'what should we do if we get a hw irq event on an illegal vector'.
 * each architecture has to answer this themselves.
 */
व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	prपूर्णांकk(KERN_ERR "Unexpected irq vector 0x%x on CPU %u!\n", irq, smp_processor_id());
पूर्ण

/*
 * Interrupt statistics:
 */

atomic_t irq_err_count;

/*
 * /proc/पूर्णांकerrupts prपूर्णांकing:
 */
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	seq_म_लिखो(p, "ERR: %10u\n", atomic_पढ़ो(&irq_err_count));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल अक्षर irq_redir [NR_IRQS]; // = अणु [0 ... NR_IRQS-1] = 1 पूर्ण;

व्योम set_irq_affinity_info (अचिन्हित पूर्णांक irq, पूर्णांक hwid, पूर्णांक redir)
अणु
	अगर (irq < NR_IRQS) अणु
		cpumask_copy(irq_get_affinity_mask(irq),
			     cpumask_of(cpu_logical_id(hwid)));
		irq_redir[irq] = (अक्षर) (redir & 0xff);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

पूर्णांक __init arch_early_irq_init(व्योम)
अणु
	ia64_mca_irq_init();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अचिन्हित पूर्णांक vectors_in_migration[NR_IRQS];

/*
 * Since cpu_online_mask is alपढ़ोy updated, we just need to check क्रम
 * affinity that has zeros
 */
अटल व्योम migrate_irqs(व्योम)
अणु
	पूर्णांक 		irq, new_cpu;

	क्रम (irq=0; irq < NR_IRQS; irq++) अणु
		काष्ठा irq_desc *desc = irq_to_desc(irq);
		काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
		काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);

		अगर (irqd_irq_disabled(data))
			जारी;

		/*
		 * No handling क्रम now.
		 * TBD: Implement a disable function so we can now
		 * tell CPU not to respond to these local पूर्णांकr sources.
		 * such as ITV,CPEI,MCA etc.
		 */
		अगर (irqd_is_per_cpu(data))
			जारी;

		अगर (cpumask_any_and(irq_data_get_affinity_mask(data),
				    cpu_online_mask) >= nr_cpu_ids) अणु
			/*
			 * Save it क्रम phase 2 processing
			 */
			vectors_in_migration[irq] = irq;

			new_cpu = cpumask_any(cpu_online_mask);

			/*
			 * Al three are essential, currently WARN_ON.. maybe panic?
			 */
			अगर (chip && chip->irq_disable &&
				chip->irq_enable && chip->irq_set_affinity) अणु
				chip->irq_disable(data);
				chip->irq_set_affinity(data,
						       cpumask_of(new_cpu), false);
				chip->irq_enable(data);
			पूर्ण अन्यथा अणु
				WARN_ON((!chip || !chip->irq_disable ||
					 !chip->irq_enable ||
					 !chip->irq_set_affinity));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम fixup_irqs(व्योम)
अणु
	अचिन्हित पूर्णांक irq;
	बाह्य व्योम ia64_process_pending_पूर्णांकr(व्योम);
	बाह्य अस्थिर पूर्णांक समय_keeper_id;

	/* Mask ITV to disable समयr */
	ia64_set_itv(1 << 16);

	/*
	 * Find a new बारync master
	 */
	अगर (smp_processor_id() == समय_keeper_id) अणु
		समय_keeper_id = cpumask_first(cpu_online_mask);
		prपूर्णांकk ("CPU %d is now promoted to time-keeper master\n", समय_keeper_id);
	पूर्ण

	/*
	 * Phase 1: Locate IRQs bound to this cpu and
	 * relocate them क्रम cpu removal.
	 */
	migrate_irqs();

	/*
	 * Phase 2: Perक्रमm पूर्णांकerrupt processing क्रम all entries reported in
	 * local APIC.
	 */
	ia64_process_pending_पूर्णांकr();

	/*
	 * Phase 3: Now handle any पूर्णांकerrupts not captured in local APIC.
	 * This is to account क्रम हालs that device पूर्णांकerrupted during the समय the
	 * rte was being disabled and re-programmed.
	 */
	क्रम (irq=0; irq < NR_IRQS; irq++) अणु
		अगर (vectors_in_migration[irq]) अणु
			काष्ठा pt_regs *old_regs = set_irq_regs(शून्य);

			vectors_in_migration[irq]=0;
			generic_handle_irq(irq);
			set_irq_regs(old_regs);
		पूर्ण
	पूर्ण

	/*
	 * Now let processor die. We करो irq disable and max_xtp() to
	 * ensure there is no more पूर्णांकerrupts routed to this processor.
	 * But the local समयr पूर्णांकerrupt can have 1 pending which we
	 * take care in समयr_पूर्णांकerrupt().
	 */
	max_xtp();
	local_irq_disable();
पूर्ण
#पूर्ण_अगर
