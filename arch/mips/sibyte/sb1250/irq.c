<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>
#समावेश <यंत्र/sibyte/sb1250_uart.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>
#समावेश <यंत्र/sibyte/sb1250.h>

/*
 * These are the routines that handle all the low level पूर्णांकerrupt stuff.
 * Actions handled here are: initialization of the पूर्णांकerrupt map, requesting of
 * पूर्णांकerrupt lines by handlers, dispatching अगर पूर्णांकerrupts to handlers, probing
 * क्रम पूर्णांकerrupt lines
 */

#अगर_घोषित CONFIG_SIBYTE_HAS_LDT
बाह्य अचिन्हित दीर्घ ldt_eoi_space;
#पूर्ण_अगर

/* Store the CPU id (not the logical number) */
पूर्णांक sb1250_irq_owner[SB1250_NR_IRQS];

अटल DEFINE_RAW_SPINLOCK(sb1250_imr_lock);

व्योम sb1250_mask_irq(पूर्णांक cpu, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	u64 cur_पूर्णांकs;

	raw_spin_lock_irqsave(&sb1250_imr_lock, flags);
	cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	cur_पूर्णांकs |= (((u64) 1) << irq);
	____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	raw_spin_unlock_irqrestore(&sb1250_imr_lock, flags);
पूर्ण

व्योम sb1250_unmask_irq(पूर्णांक cpu, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	u64 cur_पूर्णांकs;

	raw_spin_lock_irqsave(&sb1250_imr_lock, flags);
	cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	cur_पूर्णांकs &= ~(((u64) 1) << irq);
	____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	raw_spin_unlock_irqrestore(&sb1250_imr_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक sb1250_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask,
			       bool क्रमce)
अणु
	पूर्णांक i = 0, old_cpu, cpu, पूर्णांक_on;
	अचिन्हित पूर्णांक irq = d->irq;
	u64 cur_पूर्णांकs;
	अचिन्हित दीर्घ flags;

	i = cpumask_first_and(mask, cpu_online_mask);

	/* Convert logical CPU to physical CPU */
	cpu = cpu_logical_map(i);

	/* Protect against other affinity changers and IMR manipulation */
	raw_spin_lock_irqsave(&sb1250_imr_lock, flags);

	/* Swizzle each CPU's IMR (but leave the IP selection alone) */
	old_cpu = sb1250_irq_owner[irq];
	cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_IMR_MAPPER(old_cpu) +
					R_IMR_INTERRUPT_MASK));
	पूर्णांक_on = !(cur_पूर्णांकs & (((u64) 1) << irq));
	अगर (पूर्णांक_on) अणु
		/* If it was on, mask it */
		cur_पूर्णांकs |= (((u64) 1) << irq);
		____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_IMR_MAPPER(old_cpu) +
					R_IMR_INTERRUPT_MASK));
	पूर्ण
	sb1250_irq_owner[irq] = cpu;
	अगर (पूर्णांक_on) अणु
		/* unmask क्रम the new CPU */
		cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
		cur_पूर्णांकs &= ~(((u64) 1) << irq);
		____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	पूर्ण
	raw_spin_unlock_irqrestore(&sb1250_imr_lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम disable_sb1250_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	sb1250_mask_irq(sb1250_irq_owner[irq], irq);
पूर्ण

अटल व्योम enable_sb1250_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	sb1250_unmask_irq(sb1250_irq_owner[irq], irq);
पूर्ण


अटल व्योम ack_sb1250_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
#अगर_घोषित CONFIG_SIBYTE_HAS_LDT
	u64 pending;

	/*
	 * If the पूर्णांकerrupt was an HT पूर्णांकerrupt, now is the समय to
	 * clear it.  NOTE: we assume the HT bridge was set up to
	 * deliver the पूर्णांकerrupts to all CPUs (which makes affinity
	 * changing easier क्रम us)
	 */
	pending = __raw_पढ़ोq(IOADDR(A_IMR_REGISTER(sb1250_irq_owner[irq],
						    R_IMR_LDT_INTERRUPT)));
	pending &= ((u64)1 << (irq));
	अगर (pending) अणु
		पूर्णांक i;
		क्रम (i=0; i<NR_CPUS; i++) अणु
			पूर्णांक cpu;
#अगर_घोषित CONFIG_SMP
			cpu = cpu_logical_map(i);
#अन्यथा
			cpu = i;
#पूर्ण_अगर
			/*
			 * Clear क्रम all CPUs so an affinity चयन
			 * करोesn't find an old status
			 */
			__raw_ग_लिखोq(pending,
				     IOADDR(A_IMR_REGISTER(cpu,
						R_IMR_LDT_INTERRUPT_CLR)));
		पूर्ण

		/*
		 * Generate EOI.  For Pass 1 parts, EOI is a nop.  For
		 * Pass 2, the LDT world may be edge-triggered, but
		 * this EOI shouldn't hurt.  If they are
		 * level-sensitive, the EOI is required.
		 */
		*(uपूर्णांक32_t *)(ldt_eoi_space+(irq<<16)+(7<<2)) = 0;
	पूर्ण
#पूर्ण_अगर
	sb1250_mask_irq(sb1250_irq_owner[irq], irq);
पूर्ण

अटल काष्ठा irq_chip sb1250_irq_type = अणु
	.name = "SB1250-IMR",
	.irq_mask_ack = ack_sb1250_irq,
	.irq_unmask = enable_sb1250_irq,
	.irq_mask = disable_sb1250_irq,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = sb1250_set_affinity
#पूर्ण_अगर
पूर्ण;

व्योम __init init_sb1250_irqs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SB1250_NR_IRQS; i++) अणु
		irq_set_chip_and_handler(i, &sb1250_irq_type,
					 handle_level_irq);
		sb1250_irq_owner[i] = 0;
	पूर्ण
पूर्ण


/*
 *  arch_init_irq is called early in the boot sequence from init/मुख्य.c via
 *  init_IRQ.  It is responsible क्रम setting up the पूर्णांकerrupt mapper and
 *  installing the handler that will be responsible क्रम dispatching पूर्णांकerrupts
 *  to the "right" place.
 */
/*
 * For now, map all पूर्णांकerrupts to IP[2].  We could save
 * some cycles by parceling out प्रणाली पूर्णांकerrupts to dअगरferent
 * IP lines, but keep it simple क्रम bringup.  We'll also direct
 * all पूर्णांकerrupts to a single CPU; we should probably route
 * PCI and LDT to one cpu and everything अन्यथा to the other
 * to balance the load a bit.
 *
 * On the second cpu, everything is set to IP5, which is
 * ignored, EXCEPT the mailbox पूर्णांकerrupt.  That one is
 * set to IP[2] so it is handled.  This is needed so we
 * can करो cross-cpu function calls, as required by SMP
 */

#घोषणा IMR_IP2_VAL	K_INT_MAP_I0
#घोषणा IMR_IP3_VAL	K_INT_MAP_I1
#घोषणा IMR_IP4_VAL	K_INT_MAP_I2
#घोषणा IMR_IP5_VAL	K_INT_MAP_I3
#घोषणा IMR_IP6_VAL	K_INT_MAP_I4

व्योम __init arch_init_irq(व्योम)
अणु

	अचिन्हित पूर्णांक i;
	u64 पंचांगp;
	अचिन्हित पूर्णांक imask = STATUSF_IP4 | STATUSF_IP3 | STATUSF_IP2 |
		STATUSF_IP1 | STATUSF_IP0;

	/* Default everything to IP2 */
	क्रम (i = 0; i < SB1250_NR_IRQS; i++) अणु	/* was I0 */
		__raw_ग_लिखोq(IMR_IP2_VAL,
			     IOADDR(A_IMR_REGISTER(0,
						   R_IMR_INTERRUPT_MAP_BASE) +
				    (i << 3)));
		__raw_ग_लिखोq(IMR_IP2_VAL,
			     IOADDR(A_IMR_REGISTER(1,
						   R_IMR_INTERRUPT_MAP_BASE) +
				    (i << 3)));
	पूर्ण

	init_sb1250_irqs();

	/*
	 * Map the high 16 bits of the mailbox रेजिस्टरs to IP[3], क्रम
	 * पूर्णांकer-cpu messages
	 */
	/* Was I1 */
	__raw_ग_लिखोq(IMR_IP3_VAL,
		     IOADDR(A_IMR_REGISTER(0, R_IMR_INTERRUPT_MAP_BASE) +
			    (K_INT_MBOX_0 << 3)));
	__raw_ग_लिखोq(IMR_IP3_VAL,
		     IOADDR(A_IMR_REGISTER(1, R_IMR_INTERRUPT_MAP_BASE) +
			    (K_INT_MBOX_0 << 3)));

	/* Clear the mailboxes.	 The firmware may leave them dirty */
	__raw_ग_लिखोq(0xffffffffffffffffULL,
		     IOADDR(A_IMR_REGISTER(0, R_IMR_MAILBOX_CLR_CPU)));
	__raw_ग_लिखोq(0xffffffffffffffffULL,
		     IOADDR(A_IMR_REGISTER(1, R_IMR_MAILBOX_CLR_CPU)));

	/* Mask everything except the mailbox रेजिस्टरs क्रम both cpus */
	पंचांगp = ~((u64) 0) ^ (((u64) 1) << K_INT_MBOX_0);
	__raw_ग_लिखोq(पंचांगp, IOADDR(A_IMR_REGISTER(0, R_IMR_INTERRUPT_MASK)));
	__raw_ग_लिखोq(पंचांगp, IOADDR(A_IMR_REGISTER(1, R_IMR_INTERRUPT_MASK)));

	/*
	 * Note that the समयr पूर्णांकerrupts are also mapped, but this is
	 * करोne in sb1250_समय_init().	Also, the profiling driver
	 * करोes its own management of IP7.
	 */

	/* Enable necessary IPs, disable the rest */
	change_c0_status(ST0_IM, imask);
पूर्ण

बाह्य व्योम sb1250_mailbox_पूर्णांकerrupt(व्योम);

अटल अंतरभूत व्योम dispatch_ip2(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ दीर्घ mask;

	/*
	 * Default...we've hit an IP[2] interrupt, which means we've got to
	 * check the 1250 पूर्णांकerrupt रेजिस्टरs to figure out what to करो.	 Need
	 * to detect which CPU we're on, now that smp_affinity is supported.
	 */
	mask = __raw_पढ़ोq(IOADDR(A_IMR_REGISTER(cpu,
				  R_IMR_INTERRUPT_STATUS_BASE)));
	अगर (mask)
		करो_IRQ(fls64(mask) - 1);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक pending;

	/*
	 * What a pain. We have to be really careful saving the upper 32 bits
	 * of any * रेजिस्टर across function calls अगर we करोn't want them
	 * trashed--since were running in -o32, the calling routing never saves
	 * the full 64 bits of a रेजिस्टर across a function call.  Being the
	 * पूर्णांकerrupt handler, we're guaranteed that पूर्णांकerrupts are disabled
	 * during this code so we करोn't have to worry about अक्रमom पूर्णांकerrupts
	 * blasting the high 32 bits.
	 */

	pending = पढ़ो_c0_cause() & पढ़ो_c0_status() & ST0_IM;

	अगर (pending & CAUSEF_IP7) /* CPU perक्रमmance counter पूर्णांकerrupt */
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
	अन्यथा अगर (pending & CAUSEF_IP4)
		करो_IRQ(K_INT_TIMER_0 + cpu);	/* sb1250_समयr_पूर्णांकerrupt() */

#अगर_घोषित CONFIG_SMP
	अन्यथा अगर (pending & CAUSEF_IP3)
		sb1250_mailbox_पूर्णांकerrupt();
#पूर्ण_अगर

	अन्यथा अगर (pending & CAUSEF_IP2)
		dispatch_ip2();
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण
