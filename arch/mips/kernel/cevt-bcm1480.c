<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000,2001,2004 Broadcom Corporation
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समय.स>

#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>

#समावेश <यंत्र/sibyte/sb1250.h>

#घोषणा IMR_IP2_VAL	K_BCM1480_INT_MAP_I0
#घोषणा IMR_IP3_VAL	K_BCM1480_INT_MAP_I1
#घोषणा IMR_IP4_VAL	K_BCM1480_INT_MAP_I2

/*
 * The general purpose समयr ticks at 1MHz independent अगर
 * the rest of the प्रणाली
 */

अटल पूर्णांक sibyte_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	व्योम __iomem *cfg, *init;

	cfg = IOADDR(A_SCD_TIMER_REGISTER(cpu, R_SCD_TIMER_CFG));
	init = IOADDR(A_SCD_TIMER_REGISTER(cpu, R_SCD_TIMER_INIT));

	__raw_ग_लिखोq(0, cfg);
	__raw_ग_लिखोq((V_SCD_TIMER_FREQ / HZ) - 1, init);
	__raw_ग_लिखोq(M_SCD_TIMER_ENABLE | M_SCD_TIMER_MODE_CONTINUOUS, cfg);
	वापस 0;
पूर्ण

अटल पूर्णांक sibyte_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	व्योम __iomem *cfg;

	cfg = IOADDR(A_SCD_TIMER_REGISTER(cpu, R_SCD_TIMER_CFG));

	/* Stop the समयr until we actually program a shot */
	__raw_ग_लिखोq(0, cfg);
	वापस 0;
पूर्ण

अटल पूर्णांक sibyte_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *cd)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	व्योम __iomem *cfg, *init;

	cfg = IOADDR(A_SCD_TIMER_REGISTER(cpu, R_SCD_TIMER_CFG));
	init = IOADDR(A_SCD_TIMER_REGISTER(cpu, R_SCD_TIMER_INIT));

	__raw_ग_लिखोq(0, cfg);
	__raw_ग_लिखोq(delta - 1, init);
	__raw_ग_लिखोq(M_SCD_TIMER_ENABLE, cfg);

	वापस 0;
पूर्ण

अटल irqवापस_t sibyte_counter_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *cd = dev_id;
	व्योम __iomem *cfg;
	अचिन्हित दीर्घ पंचांगode;

	अगर (घड़ीevent_state_periodic(cd))
		पंचांगode = M_SCD_TIMER_ENABLE | M_SCD_TIMER_MODE_CONTINUOUS;
	अन्यथा
		पंचांगode = 0;

	/* ACK पूर्णांकerrupt */
	cfg = IOADDR(A_SCD_TIMER_REGISTER(cpu, R_SCD_TIMER_CFG));
	____raw_ग_लिखोq(पंचांगode, cfg);

	cd->event_handler(cd);

	वापस IRQ_HANDLED;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, sibyte_hpt_घड़ीevent);
अटल DEFINE_PER_CPU(अक्षर [18], sibyte_hpt_name);

व्योम sb1480_घड़ीevent_init(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक irq = K_BCM1480_INT_TIMER_0 + cpu;
	काष्ठा घड़ी_event_device *cd = &per_cpu(sibyte_hpt_घड़ीevent, cpu);
	अचिन्हित अक्षर *name = per_cpu(sibyte_hpt_name, cpu);
	अचिन्हित दीर्घ flags =  IRQF_PERCPU | IRQF_TIMER;

	BUG_ON(cpu > 3);	/* Only have 4 general purpose समयrs */

	प्र_लिखो(name, "bcm1480-counter-%d", cpu);
	cd->name		= name;
	cd->features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT;
	घड़ीevent_set_घड़ी(cd, V_SCD_TIMER_FREQ);
	cd->max_delta_ns	= घड़ीevent_delta2ns(0x7fffff, cd);
	cd->max_delta_ticks	= 0x7fffff;
	cd->min_delta_ns	= घड़ीevent_delta2ns(2, cd);
	cd->min_delta_ticks	= 2;
	cd->rating		= 200;
	cd->irq			= irq;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= sibyte_next_event;
	cd->set_state_shutकरोwn	= sibyte_shutकरोwn;
	cd->set_state_periodic	= sibyte_set_periodic;
	cd->set_state_oneshot	= sibyte_shutकरोwn;
	घड़ीevents_रेजिस्टर_device(cd);

	bcm1480_mask_irq(cpu, irq);

	/*
	 * Map the समयr पूर्णांकerrupt to IP[4] of this cpu
	 */
	__raw_ग_लिखोq(IMR_IP4_VAL,
		     IOADDR(A_BCM1480_IMR_REGISTER(cpu,
			R_BCM1480_IMR_INTERRUPT_MAP_BASE_H) + (irq << 3)));

	bcm1480_unmask_irq(cpu, irq);

	irq_set_affinity(irq, cpumask_of(cpu));
	अगर (request_irq(irq, sibyte_counter_handler, flags, name, cd))
		pr_err("Failed to request irq %d (%s)\n", irq, name);
पूर्ण
