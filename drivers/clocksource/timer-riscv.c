<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 *
 * All RISC-V प्रणालीs have a समयr attached to every hart.  These समयrs can
 * either be पढ़ो from the "time" and "timeh" CSRs, and can use the SBI to
 * setup events, or directly accessed using MMIO रेजिस्टरs.
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/समयx.h>

अटल पूर्णांक riscv_घड़ी_next_event(अचिन्हित दीर्घ delta,
		काष्ठा घड़ी_event_device *ce)
अणु
	csr_set(CSR_IE, IE_TIE);
	sbi_set_समयr(get_cycles64() + delta);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक riscv_घड़ी_event_irq;
अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, riscv_घड़ी_event) = अणु
	.name			= "riscv_timer_clockevent",
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 100,
	.set_next_event		= riscv_घड़ी_next_event,
पूर्ण;

/*
 * It is guaranteed that all the समयrs across all the harts are synchronized
 * within one tick of each other, so जबतक this could technically go
 * backwards when hopping between CPUs, practically it won't happen.
 */
अटल अचिन्हित दीर्घ दीर्घ riscv_घड़ीsource_rdसमय(काष्ठा घड़ीsource *cs)
अणु
	वापस get_cycles64();
पूर्ण

अटल u64 notrace riscv_sched_घड़ी(व्योम)
अणु
	वापस get_cycles64();
पूर्ण

अटल काष्ठा घड़ीsource riscv_घड़ीsource = अणु
	.name		= "riscv_clocksource",
	.rating		= 300,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.पढ़ो		= riscv_घड़ीsource_rdसमय,
पूर्ण;

अटल पूर्णांक riscv_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *ce = per_cpu_ptr(&riscv_घड़ी_event, cpu);

	ce->cpumask = cpumask_of(cpu);
	ce->irq = riscv_घड़ी_event_irq;
	घड़ीevents_config_and_रेजिस्टर(ce, riscv_समयbase, 100, 0x7fffffff);

	enable_percpu_irq(riscv_घड़ी_event_irq,
			  irq_get_trigger_type(riscv_घड़ी_event_irq));
	वापस 0;
पूर्ण

अटल पूर्णांक riscv_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(riscv_घड़ी_event_irq);
	वापस 0;
पूर्ण

/* called directly from the low-level पूर्णांकerrupt handler */
अटल irqवापस_t riscv_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evdev = this_cpu_ptr(&riscv_घड़ी_event);

	csr_clear(CSR_IE, IE_TIE);
	evdev->event_handler(evdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init riscv_समयr_init_dt(काष्ठा device_node *n)
अणु
	पूर्णांक cpuid, hartid, error;
	काष्ठा device_node *child;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	hartid = riscv_of_processor_hartid(n);
	अगर (hartid < 0) अणु
		pr_warn("Not valid hartid for node [%pOF] error = [%d]\n",
			n, hartid);
		वापस hartid;
	पूर्ण

	cpuid = riscv_hartid_to_cpuid(hartid);
	अगर (cpuid < 0) अणु
		pr_warn("Invalid cpuid for hartid [%d]\n", hartid);
		वापस cpuid;
	पूर्ण

	अगर (cpuid != smp_processor_id())
		वापस 0;

	करोमुख्य = शून्य;
	child = of_get_compatible_child(n, "riscv,cpu-intc");
	अगर (!child) अणु
		pr_err("Failed to find INTC node [%pOF]\n", n);
		वापस -ENODEV;
	पूर्ण
	करोमुख्य = irq_find_host(child);
	of_node_put(child);
	अगर (!करोमुख्य) अणु
		pr_err("Failed to find IRQ domain for node [%pOF]\n", n);
		वापस -ENODEV;
	पूर्ण

	riscv_घड़ी_event_irq = irq_create_mapping(करोमुख्य, RV_IRQ_TIMER);
	अगर (!riscv_घड़ी_event_irq) अणु
		pr_err("Failed to map timer interrupt for node [%pOF]\n", n);
		वापस -ENODEV;
	पूर्ण

	pr_info("%s: Registering clocksource cpuid [%d] hartid [%d]\n",
	       __func__, cpuid, hartid);
	error = घड़ीsource_रेजिस्टर_hz(&riscv_घड़ीsource, riscv_समयbase);
	अगर (error) अणु
		pr_err("RISCV timer register failed [%d] for cpu = [%d]\n",
		       error, cpuid);
		वापस error;
	पूर्ण

	sched_घड़ी_रेजिस्टर(riscv_sched_घड़ी, 64, riscv_समयbase);

	error = request_percpu_irq(riscv_घड़ी_event_irq,
				    riscv_समयr_पूर्णांकerrupt,
				    "riscv-timer", &riscv_घड़ी_event);
	अगर (error) अणु
		pr_err("registering percpu irq failed [%d]\n", error);
		वापस error;
	पूर्ण

	error = cpuhp_setup_state(CPUHP_AP_RISCV_TIMER_STARTING,
			 "clockevents/riscv/timer:starting",
			 riscv_समयr_starting_cpu, riscv_समयr_dying_cpu);
	अगर (error)
		pr_err("cpu hp setup state failed for RISCV timer [%d]\n",
		       error);
	वापस error;
पूर्ण

TIMER_OF_DECLARE(riscv_समयr, "riscv", riscv_समयr_init_dt);
