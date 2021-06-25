<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000,2001,2002,2003,2004 Broadcom Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>

#समावेश <यंत्र/sibyte/sb1250_uart.h>
#समावेश <यंत्र/sibyte/sb1250.h>

/*
 * These are the routines that handle all the low level पूर्णांकerrupt stuff.
 * Actions handled here are: initialization of the पूर्णांकerrupt map, requesting of
 * पूर्णांकerrupt lines by handlers, dispatching अगर पूर्णांकerrupts to handlers, probing
 * क्रम पूर्णांकerrupt lines
 */

#अगर_घोषित CONFIG_PCI
बाह्य अचिन्हित दीर्घ ht_eoi_space;
#पूर्ण_अगर

/* Store the CPU id (not the logical number) */
पूर्णांक bcm1480_irq_owner[BCM1480_NR_IRQS];

अटल DEFINE_RAW_SPINLOCK(bcm1480_imr_lock);

व्योम bcm1480_mask_irq(पूर्णांक cpu, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags, hl_spacing;
	u64 cur_पूर्णांकs;

	raw_spin_lock_irqsave(&bcm1480_imr_lock, flags);
	hl_spacing = 0;
	अगर ((irq >= BCM1480_NR_IRQS_HALF) && (irq <= BCM1480_NR_IRQS)) अणु
		hl_spacing = BCM1480_IMR_HL_SPACING;
		irq -= BCM1480_NR_IRQS_HALF;
	पूर्ण
	cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_BCM1480_IMR_MAPPER(cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + hl_spacing));
	cur_पूर्णांकs |= (((u64) 1) << irq);
	____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_BCM1480_IMR_MAPPER(cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + hl_spacing));
	raw_spin_unlock_irqrestore(&bcm1480_imr_lock, flags);
पूर्ण

व्योम bcm1480_unmask_irq(पूर्णांक cpu, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags, hl_spacing;
	u64 cur_पूर्णांकs;

	raw_spin_lock_irqsave(&bcm1480_imr_lock, flags);
	hl_spacing = 0;
	अगर ((irq >= BCM1480_NR_IRQS_HALF) && (irq <= BCM1480_NR_IRQS)) अणु
		hl_spacing = BCM1480_IMR_HL_SPACING;
		irq -= BCM1480_NR_IRQS_HALF;
	पूर्ण
	cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_BCM1480_IMR_MAPPER(cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + hl_spacing));
	cur_पूर्णांकs &= ~(((u64) 1) << irq);
	____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_BCM1480_IMR_MAPPER(cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + hl_spacing));
	raw_spin_unlock_irqrestore(&bcm1480_imr_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक bcm1480_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask,
				bool क्रमce)
अणु
	अचिन्हित पूर्णांक irq_dirty, irq = d->irq;
	पूर्णांक i = 0, old_cpu, cpu, पूर्णांक_on, k;
	u64 cur_पूर्णांकs;
	अचिन्हित दीर्घ flags;

	i = cpumask_first_and(mask, cpu_online_mask);

	/* Convert logical CPU to physical CPU */
	cpu = cpu_logical_map(i);

	/* Protect against other affinity changers and IMR manipulation */
	raw_spin_lock_irqsave(&bcm1480_imr_lock, flags);

	/* Swizzle each CPU's IMR (but leave the IP selection alone) */
	old_cpu = bcm1480_irq_owner[irq];
	irq_dirty = irq;
	अगर ((irq_dirty >= BCM1480_NR_IRQS_HALF) && (irq_dirty <= BCM1480_NR_IRQS)) अणु
		irq_dirty -= BCM1480_NR_IRQS_HALF;
	पूर्ण

	क्रम (k=0; k<2; k++) अणु /* Loop through high and low पूर्णांकerrupt mask रेजिस्टर */
		cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_BCM1480_IMR_MAPPER(old_cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + (k*BCM1480_IMR_HL_SPACING)));
		पूर्णांक_on = !(cur_पूर्णांकs & (((u64) 1) << irq_dirty));
		अगर (पूर्णांक_on) अणु
			/* If it was on, mask it */
			cur_पूर्णांकs |= (((u64) 1) << irq_dirty);
			____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_BCM1480_IMR_MAPPER(old_cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + (k*BCM1480_IMR_HL_SPACING)));
		पूर्ण
		bcm1480_irq_owner[irq] = cpu;
		अगर (पूर्णांक_on) अणु
			/* unmask क्रम the new CPU */
			cur_पूर्णांकs = ____raw_पढ़ोq(IOADDR(A_BCM1480_IMR_MAPPER(cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + (k*BCM1480_IMR_HL_SPACING)));
			cur_पूर्णांकs &= ~(((u64) 1) << irq_dirty);
			____raw_ग_लिखोq(cur_पूर्णांकs, IOADDR(A_BCM1480_IMR_MAPPER(cpu) + R_BCM1480_IMR_INTERRUPT_MASK_H + (k*BCM1480_IMR_HL_SPACING)));
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&bcm1480_imr_lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************/

अटल व्योम disable_bcm1480_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	bcm1480_mask_irq(bcm1480_irq_owner[irq], irq);
पूर्ण

अटल व्योम enable_bcm1480_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	bcm1480_unmask_irq(bcm1480_irq_owner[irq], irq);
पूर्ण


अटल व्योम ack_bcm1480_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_dirty, irq = d->irq;
	u64 pending;
	पूर्णांक k;

	/*
	 * If the पूर्णांकerrupt was an HT पूर्णांकerrupt, now is the समय to
	 * clear it.  NOTE: we assume the HT bridge was set up to
	 * deliver the पूर्णांकerrupts to all CPUs (which makes affinity
	 * changing easier क्रम us)
	 */
	irq_dirty = irq;
	अगर ((irq_dirty >= BCM1480_NR_IRQS_HALF) && (irq_dirty <= BCM1480_NR_IRQS)) अणु
		irq_dirty -= BCM1480_NR_IRQS_HALF;
	पूर्ण
	क्रम (k=0; k<2; k++) अणु /* Loop through high and low LDT पूर्णांकerrupts */
		pending = __raw_पढ़ोq(IOADDR(A_BCM1480_IMR_REGISTER(bcm1480_irq_owner[irq],
						R_BCM1480_IMR_LDT_INTERRUPT_H + (k*BCM1480_IMR_HL_SPACING))));
		pending &= ((u64)1 << (irq_dirty));
		अगर (pending) अणु
#अगर_घोषित CONFIG_SMP
			पूर्णांक i;
			क्रम (i=0; i<NR_CPUS; i++) अणु
				/*
				 * Clear क्रम all CPUs so an affinity चयन
				 * करोesn't find an old status
				 */
				__raw_ग_लिखोq(pending, IOADDR(A_BCM1480_IMR_REGISTER(cpu_logical_map(i),
								R_BCM1480_IMR_LDT_INTERRUPT_CLR_H + (k*BCM1480_IMR_HL_SPACING))));
			पूर्ण
#अन्यथा
			__raw_ग_लिखोq(pending, IOADDR(A_BCM1480_IMR_REGISTER(0, R_BCM1480_IMR_LDT_INTERRUPT_CLR_H + (k*BCM1480_IMR_HL_SPACING))));
#पूर्ण_अगर

			/*
			 * Generate EOI.  For Pass 1 parts, EOI is a nop.  For
			 * Pass 2, the LDT world may be edge-triggered, but
			 * this EOI shouldn't hurt.  If they are
			 * level-sensitive, the EOI is required.
			 */
#अगर_घोषित CONFIG_PCI
			अगर (ht_eoi_space)
				*(uपूर्णांक32_t *)(ht_eoi_space+(irq<<16)+(7<<2)) = 0;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	bcm1480_mask_irq(bcm1480_irq_owner[irq], irq);
पूर्ण

अटल काष्ठा irq_chip bcm1480_irq_type = अणु
	.name = "BCM1480-IMR",
	.irq_mask_ack = ack_bcm1480_irq,
	.irq_mask = disable_bcm1480_irq,
	.irq_unmask = enable_bcm1480_irq,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = bcm1480_set_affinity
#पूर्ण_अगर
पूर्ण;

व्योम __init init_bcm1480_irqs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BCM1480_NR_IRQS; i++) अणु
		irq_set_chip_and_handler(i, &bcm1480_irq_type,
					 handle_level_irq);
		bcm1480_irq_owner[i] = 0;
	पूर्ण
पूर्ण

/*
 *  init_IRQ is called early in the boot sequence from init/मुख्य.c.  It
 *  is responsible क्रम setting up the पूर्णांकerrupt mapper and installing the
 *  handler that will be responsible क्रम dispatching पूर्णांकerrupts to the
 *  "right" place.
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

#घोषणा IMR_IP2_VAL	K_BCM1480_INT_MAP_I0
#घोषणा IMR_IP3_VAL	K_BCM1480_INT_MAP_I1
#घोषणा IMR_IP4_VAL	K_BCM1480_INT_MAP_I2
#घोषणा IMR_IP5_VAL	K_BCM1480_INT_MAP_I3
#घोषणा IMR_IP6_VAL	K_BCM1480_INT_MAP_I4

व्योम __init arch_init_irq(व्योम)
अणु
	अचिन्हित पूर्णांक i, cpu;
	u64 पंचांगp;
	अचिन्हित पूर्णांक imask = STATUSF_IP4 | STATUSF_IP3 | STATUSF_IP2 |
		STATUSF_IP1 | STATUSF_IP0;

	/* Default everything to IP2 */
	/* Start with _high रेजिस्टरs which has no bit 0 पूर्णांकerrupt source */
	क्रम (i = 1; i < BCM1480_NR_IRQS_HALF; i++) अणु	/* was I0 */
		क्रम (cpu = 0; cpu < 4; cpu++) अणु
			__raw_ग_लिखोq(IMR_IP2_VAL,
				     IOADDR(A_BCM1480_IMR_REGISTER(cpu,
								   R_BCM1480_IMR_INTERRUPT_MAP_BASE_H) + (i << 3)));
		पूर्ण
	पूर्ण

	/* Now करो _low रेजिस्टरs */
	क्रम (i = 0; i < BCM1480_NR_IRQS_HALF; i++) अणु
		क्रम (cpu = 0; cpu < 4; cpu++) अणु
			__raw_ग_लिखोq(IMR_IP2_VAL,
				     IOADDR(A_BCM1480_IMR_REGISTER(cpu,
								   R_BCM1480_IMR_INTERRUPT_MAP_BASE_L) + (i << 3)));
		पूर्ण
	पूर्ण

	init_bcm1480_irqs();

	/*
	 * Map the high 16 bits of mailbox_0 रेजिस्टरs to IP[3], क्रम
	 * पूर्णांकer-cpu messages
	 */
	/* Was I1 */
	क्रम (cpu = 0; cpu < 4; cpu++) अणु
		__raw_ग_लिखोq(IMR_IP3_VAL, IOADDR(A_BCM1480_IMR_REGISTER(cpu, R_BCM1480_IMR_INTERRUPT_MAP_BASE_H) +
						 (K_BCM1480_INT_MBOX_0_0 << 3)));
	पूर्ण


	/* Clear the mailboxes.	 The firmware may leave them dirty */
	क्रम (cpu = 0; cpu < 4; cpu++) अणु
		__raw_ग_लिखोq(0xffffffffffffffffULL,
			     IOADDR(A_BCM1480_IMR_REGISTER(cpu, R_BCM1480_IMR_MAILBOX_0_CLR_CPU)));
		__raw_ग_लिखोq(0xffffffffffffffffULL,
			     IOADDR(A_BCM1480_IMR_REGISTER(cpu, R_BCM1480_IMR_MAILBOX_1_CLR_CPU)));
	पूर्ण


	/* Mask everything except the high 16 bit of mailbox_0 रेजिस्टरs क्रम all cpus */
	पंचांगp = ~((u64) 0) ^ ( (((u64) 1) << K_BCM1480_INT_MBOX_0_0));
	क्रम (cpu = 0; cpu < 4; cpu++) अणु
		__raw_ग_लिखोq(पंचांगp, IOADDR(A_BCM1480_IMR_REGISTER(cpu, R_BCM1480_IMR_INTERRUPT_MASK_H)));
	पूर्ण
	पंचांगp = ~((u64) 0);
	क्रम (cpu = 0; cpu < 4; cpu++) अणु
		__raw_ग_लिखोq(पंचांगp, IOADDR(A_BCM1480_IMR_REGISTER(cpu, R_BCM1480_IMR_INTERRUPT_MASK_L)));
	पूर्ण

	/*
	 * Note that the समयr पूर्णांकerrupts are also mapped, but this is
	 * करोne in bcm1480_समय_init().	 Also, the profiling driver
	 * करोes its own management of IP7.
	 */

	/* Enable necessary IPs, disable the rest */
	change_c0_status(ST0_IM, imask);
पूर्ण

बाह्य व्योम bcm1480_mailbox_पूर्णांकerrupt(व्योम);

अटल अंतरभूत व्योम dispatch_ip2(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ mask_h, mask_l;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ base;

	/*
	 * Default...we've hit an IP[2] interrupt, which means we've got to
	 * check the 1480 पूर्णांकerrupt रेजिस्टरs to figure out what to करो.	 Need
	 * to detect which CPU we're on, now that smp_affinity is supported.
	 */
	base = A_BCM1480_IMR_MAPPER(cpu);
	mask_h = __raw_पढ़ोq(
		IOADDR(base + R_BCM1480_IMR_INTERRUPT_STATUS_BASE_H));
	mask_l = __raw_पढ़ोq(
		IOADDR(base + R_BCM1480_IMR_INTERRUPT_STATUS_BASE_L));

	अगर (mask_h) अणु
		अगर (mask_h ^ 1)
			करो_IRQ(fls64(mask_h) - 1);
		अन्यथा अगर (mask_l)
			करो_IRQ(63 + fls64(mask_l));
	पूर्ण
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक pending;

	pending = पढ़ो_c0_cause() & पढ़ो_c0_status();

	अगर (pending & CAUSEF_IP4)
		करो_IRQ(K_BCM1480_INT_TIMER_0 + cpu);
#अगर_घोषित CONFIG_SMP
	अन्यथा अगर (pending & CAUSEF_IP3)
		bcm1480_mailbox_पूर्णांकerrupt();
#पूर्ण_अगर

	अन्यथा अगर (pending & CAUSEF_IP2)
		dispatch_ip2();
पूर्ण
