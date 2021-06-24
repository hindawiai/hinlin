<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 Linus Torvalds
 * Copyright (C) 1994 - 2001, 2003, 07 Ralf Baechle
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/i8253.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/jazz.h>
#समावेश <यंत्र/tlbmisc.h>

अटल DEFINE_RAW_SPINLOCK(r4030_lock);

अटल व्योम enable_r4030_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq - JAZZ_IRQ_START);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&r4030_lock, flags);
	mask |= r4030_पढ़ो_reg16(JAZZ_IO_IRQ_ENABLE);
	r4030_ग_लिखो_reg16(JAZZ_IO_IRQ_ENABLE, mask);
	raw_spin_unlock_irqrestore(&r4030_lock, flags);
पूर्ण

व्योम disable_r4030_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = ~(1 << (d->irq - JAZZ_IRQ_START));
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&r4030_lock, flags);
	mask &= r4030_पढ़ो_reg16(JAZZ_IO_IRQ_ENABLE);
	r4030_ग_लिखो_reg16(JAZZ_IO_IRQ_ENABLE, mask);
	raw_spin_unlock_irqrestore(&r4030_lock, flags);
पूर्ण

अटल काष्ठा irq_chip r4030_irq_type = अणु
	.name = "R4030",
	.irq_mask = disable_r4030_irq,
	.irq_unmask = enable_r4030_irq,
पूर्ण;

व्योम __init init_r4030_पूर्णांकs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = JAZZ_IRQ_START; i <= JAZZ_IRQ_END; i++)
		irq_set_chip_and_handler(i, &r4030_irq_type, handle_level_irq);

	r4030_ग_लिखो_reg16(JAZZ_IO_IRQ_ENABLE, 0);
	r4030_पढ़ो_reg16(JAZZ_IO_IRQ_SOURCE);		/* clear pending IRQs */
	r4030_पढ़ो_reg32(JAZZ_R4030_INVAL_ADDR);	/* clear error bits */
पूर्ण

/*
 * On प्रणालीs with i8259-style पूर्णांकerrupt controllers we assume क्रम
 * driver compatibility reasons पूर्णांकerrupts 0 - 15 to be the i8259
 * पूर्णांकerrupts even अगर the hardware uses a dअगरferent पूर्णांकerrupt numbering.
 */
व्योम __init arch_init_irq(व्योम)
अणु
	/*
	 * this is a hack to get back the still needed wired mapping
	 * समाप्तed by init_mm()
	 */

	/* Map 0xe0000000 -> 0x0:800005C0, 0xe0010000 -> 0x1:30000580 */
	add_wired_entry(0x02000017, 0x03c00017, 0xe0000000, PM_64K);
	/* Map 0xe2000000 -> 0x0:900005C0, 0xe3010000 -> 0x0:910005C0 */
	add_wired_entry(0x02400017, 0x02440017, 0xe2000000, PM_16M);
	/* Map 0xe4000000 -> 0x0:600005C0, 0xe4100000 -> 400005C0 */
	add_wired_entry(0x01800017, 0x01000017, 0xe4000000, PM_4M);

	init_i8259_irqs();			/* Integrated i8259  */
	mips_cpu_irq_init();
	init_r4030_पूर्णांकs();

	change_c0_status(ST0_IM, IE_IRQ2 | IE_IRQ1);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending = पढ़ो_c0_cause() & पढ़ो_c0_status();
	अचिन्हित पूर्णांक irq;

	अगर (pending & IE_IRQ4) अणु
		r4030_पढ़ो_reg32(JAZZ_TIMER_REGISTER);
		करो_IRQ(JAZZ_TIMER_IRQ);
	पूर्ण अन्यथा अगर (pending & IE_IRQ2) अणु
		irq = *(अस्थिर u8 *)JAZZ_EISA_IRQ_ACK;
		करो_IRQ(irq);
	पूर्ण अन्यथा अगर (pending & IE_IRQ1) अणु
		irq = *(अस्थिर u8 *)JAZZ_IO_IRQ_SOURCE >> 2;
		अगर (likely(irq > 0))
			करो_IRQ(irq + JAZZ_IRQ_START - 1);
		अन्यथा
			panic("Unimplemented loc_no_irq handler");
	पूर्ण
पूर्ण

काष्ठा घड़ी_event_device r4030_घड़ीevent = अणु
	.name		= "r4030",
	.features	= CLOCK_EVT_FEAT_PERIODIC,
	.rating		= 300,
	.irq		= JAZZ_TIMER_IRQ,
पूर्ण;

अटल irqवापस_t r4030_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *cd = dev_id;

	cd->event_handler(cd);
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा घड़ी_event_device *cd = &r4030_घड़ीevent;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	BUG_ON(HZ != 100);

	cd->cpumask		= cpumask_of(cpu);
	घड़ीevents_रेजिस्टर_device(cd);
	अगर (request_irq(JAZZ_TIMER_IRQ, r4030_समयr_पूर्णांकerrupt, IRQF_TIMER,
			"R4030 timer", cd))
		pr_err("Failed to register R4030 timer interrupt\n");

	/*
	 * Set घड़ी to 100Hz.
	 *
	 * The R4030 समयr receives an input घड़ी of 1kHz which is भागieded by
	 * a programmable 4-bit भागider.  This makes it fairly inflexible.
	 */
	r4030_ग_लिखो_reg32(JAZZ_TIMER_INTERVAL, 9);
	setup_pit_समयr();
पूर्ण
