<शैली गुरु>
/*
 * J-Core SoC PIT/घड़ीsource driver
 *
 * Copyright (C) 2015-2016 Smart Energy Instruments, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा PIT_IRQ_SHIFT		12
#घोषणा PIT_PRIO_SHIFT		20
#घोषणा PIT_ENABLE_SHIFT	26
#घोषणा PIT_PRIO_MASK		0xf

#घोषणा REG_PITEN		0x00
#घोषणा REG_THROT		0x10
#घोषणा REG_COUNT		0x14
#घोषणा REG_BUSPD		0x18
#घोषणा REG_SECHI		0x20
#घोषणा REG_SECLO		0x24
#घोषणा REG_NSEC		0x28

काष्ठा jcore_pit अणु
	काष्ठा घड़ी_event_device	ced;
	व्योम __iomem			*base;
	अचिन्हित दीर्घ			periodic_delta;
	u32				enable_val;
पूर्ण;

अटल व्योम __iomem *jcore_pit_base;
अटल काष्ठा jcore_pit __percpu *jcore_pit_percpu;

अटल notrace u64 jcore_sched_घड़ी_पढ़ो(व्योम)
अणु
	u32 seclo, nsec, seclo0;
	__iomem व्योम *base = jcore_pit_base;

	seclo = पढ़ोl(base + REG_SECLO);
	करो अणु
		seclo0 = seclo;
		nsec  = पढ़ोl(base + REG_NSEC);
		seclo = पढ़ोl(base + REG_SECLO);
	पूर्ण जबतक (seclo0 != seclo);

	वापस seclo * NSEC_PER_SEC + nsec;
पूर्ण

अटल u64 jcore_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस jcore_sched_घड़ी_पढ़ो();
पूर्ण

अटल पूर्णांक jcore_pit_disable(काष्ठा jcore_pit *pit)
अणु
	ग_लिखोl(0, pit->base + REG_PITEN);
	वापस 0;
पूर्ण

अटल पूर्णांक jcore_pit_set(अचिन्हित दीर्घ delta, काष्ठा jcore_pit *pit)
अणु
	jcore_pit_disable(pit);
	ग_लिखोl(delta, pit->base + REG_THROT);
	ग_लिखोl(pit->enable_val, pit->base + REG_PITEN);
	वापस 0;
पूर्ण

अटल पूर्णांक jcore_pit_set_state_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा jcore_pit *pit = container_of(ced, काष्ठा jcore_pit, ced);

	वापस jcore_pit_disable(pit);
पूर्ण

अटल पूर्णांक jcore_pit_set_state_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा jcore_pit *pit = container_of(ced, काष्ठा jcore_pit, ced);

	वापस jcore_pit_disable(pit);
पूर्ण

अटल पूर्णांक jcore_pit_set_state_periodic(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा jcore_pit *pit = container_of(ced, काष्ठा jcore_pit, ced);

	वापस jcore_pit_set(pit->periodic_delta, pit);
पूर्ण

अटल पूर्णांक jcore_pit_set_next_event(अचिन्हित दीर्घ delta,
				    काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा jcore_pit *pit = container_of(ced, काष्ठा jcore_pit, ced);

	वापस jcore_pit_set(delta, pit);
पूर्ण

अटल पूर्णांक jcore_pit_local_init(अचिन्हित cpu)
अणु
	काष्ठा jcore_pit *pit = this_cpu_ptr(jcore_pit_percpu);
	अचिन्हित buspd, freq;

	pr_info("Local J-Core PIT init on cpu %u\n", cpu);

	buspd = पढ़ोl(pit->base + REG_BUSPD);
	freq = DIV_ROUND_CLOSEST(NSEC_PER_SEC, buspd);
	pit->periodic_delta = DIV_ROUND_CLOSEST(NSEC_PER_SEC, HZ * buspd);

	घड़ीevents_config_and_रेजिस्टर(&pit->ced, freq, 1, अच_दीर्घ_उच्च);

	वापस 0;
पूर्ण

अटल irqवापस_t jcore_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा jcore_pit *pit = this_cpu_ptr(dev_id);

	अगर (घड़ीevent_state_oneshot(&pit->ced))
		jcore_pit_disable(pit);

	pit->ced.event_handler(&pit->ced);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init jcore_pit_init(काष्ठा device_node *node)
अणु
	पूर्णांक err;
	अचिन्हित pit_irq, cpu;
	अचिन्हित दीर्घ hwirq;
	u32 irqprio, enable_val;

	jcore_pit_base = of_iomap(node, 0);
	अगर (!jcore_pit_base) अणु
		pr_err("Error: Cannot map base address for J-Core PIT\n");
		वापस -ENXIO;
	पूर्ण

	pit_irq = irq_of_parse_and_map(node, 0);
	अगर (!pit_irq) अणु
		pr_err("Error: J-Core PIT has no IRQ\n");
		वापस -ENXIO;
	पूर्ण

	pr_info("Initializing J-Core PIT at %p IRQ %d\n",
		jcore_pit_base, pit_irq);

	err = घड़ीsource_mmio_init(jcore_pit_base, "jcore_pit_cs",
				    NSEC_PER_SEC, 400, 32,
				    jcore_घड़ीsource_पढ़ो);
	अगर (err) अणु
		pr_err("Error registering clocksource device: %d\n", err);
		वापस err;
	पूर्ण

	sched_घड़ी_रेजिस्टर(jcore_sched_घड़ी_पढ़ो, 32, NSEC_PER_SEC);

	jcore_pit_percpu = alloc_percpu(काष्ठा jcore_pit);
	अगर (!jcore_pit_percpu) अणु
		pr_err("Failed to allocate memory for clock event device\n");
		वापस -ENOMEM;
	पूर्ण

	err = request_irq(pit_irq, jcore_समयr_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_PERCPU,
			  "jcore_pit", jcore_pit_percpu);
	अगर (err) अणु
		pr_err("pit irq request failed: %d\n", err);
		मुक्त_percpu(jcore_pit_percpu);
		वापस err;
	पूर्ण

	/*
	 * The J-Core PIT is not hard-wired to a particular IRQ, but
	 * पूर्णांकegrated with the पूर्णांकerrupt controller such that the IRQ it
	 * generates is programmable, as follows:
	 *
	 * The bit layout of the PIT enable रेजिस्टर is:
	 *
	 *	.....e..ppppiiiiiiii............
	 *
	 * where the .'s indicate unrelated/unused bits, e is enable,
	 * p is priority, and i is hard irq number.
	 *
	 * For the PIT included in AIC1 (obsolete but still in use),
	 * any hard irq (trap number) can be programmed via the 8
	 * iiiiiiii bits, and a priority (0-15) is programmable
	 * separately in the pppp bits.
	 *
	 * For the PIT included in AIC2 (current), the programming
	 * पूर्णांकerface is equivalent modulo पूर्णांकerrupt mapping. This is
	 * why a dअगरferent compatible tag was not used. However only
	 * traps 64-127 (the ones actually पूर्णांकended to be used क्रम
	 * पूर्णांकerrupts, rather than syscalls/exceptions/etc.) can be
	 * programmed (the high 2 bits of i are ignored) and the
	 * priority pppp is <<2'd and or'd onto the irq number. This
	 * choice seems to have been made on the hardware engineering
	 * side under an assumption that preserving old AIC1 priority
	 * mappings was important. Future models will likely ignore
	 * the pppp field.
	 */
	hwirq = irq_get_irq_data(pit_irq)->hwirq;
	irqprio = (hwirq >> 2) & PIT_PRIO_MASK;
	enable_val = (1U << PIT_ENABLE_SHIFT)
		   | (hwirq << PIT_IRQ_SHIFT)
		   | (irqprio << PIT_PRIO_SHIFT);

	क्रम_each_present_cpu(cpu) अणु
		काष्ठा jcore_pit *pit = per_cpu_ptr(jcore_pit_percpu, cpu);

		pit->base = of_iomap(node, cpu);
		अगर (!pit->base) अणु
			pr_err("Unable to map PIT for cpu %u\n", cpu);
			जारी;
		पूर्ण

		pit->ced.name = "jcore_pit";
		pit->ced.features = CLOCK_EVT_FEAT_PERIODIC
				  | CLOCK_EVT_FEAT_ONESHOT
				  | CLOCK_EVT_FEAT_PERCPU;
		pit->ced.cpumask = cpumask_of(cpu);
		pit->ced.rating = 400;
		pit->ced.irq = pit_irq;
		pit->ced.set_state_shutकरोwn = jcore_pit_set_state_shutकरोwn;
		pit->ced.set_state_periodic = jcore_pit_set_state_periodic;
		pit->ced.set_state_oneshot = jcore_pit_set_state_oneshot;
		pit->ced.set_next_event = jcore_pit_set_next_event;

		pit->enable_val = enable_val;
	पूर्ण

	cpuhp_setup_state(CPUHP_AP_JCORE_TIMER_STARTING,
			  "clockevents/jcore:starting",
			  jcore_pit_local_init, शून्य);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(jcore_pit, "jcore,pit", jcore_pit_init);
