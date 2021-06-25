<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 *
 * Most of the M-mode (i.e. NoMMU) RISC-V प्रणालीs usually have a
 * CLINT MMIO समयr device.
 */

#घोषणा pr_fmt(fmt) "clint: " fmt
#समावेश <linux/bitops.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/समयx.h>

#अगर_अघोषित CONFIG_RISCV_M_MODE
#समावेश <यंत्र/clपूर्णांक.h>
#पूर्ण_अगर

#घोषणा CLINT_IPI_OFF		0
#घोषणा CLINT_TIMER_CMP_OFF	0x4000
#घोषणा CLINT_TIMER_VAL_OFF	0xbff8

/* CLINT manages IPI and Timer क्रम RISC-V M-mode  */
अटल u32 __iomem *clपूर्णांक_ipi_base;
अटल u64 __iomem *clपूर्णांक_समयr_cmp;
अटल u64 __iomem *clपूर्णांक_समयr_val;
अटल अचिन्हित दीर्घ clपूर्णांक_समयr_freq;
अटल अचिन्हित पूर्णांक clपूर्णांक_समयr_irq;

#अगर_घोषित CONFIG_RISCV_M_MODE
u64 __iomem *clपूर्णांक_समय_val;
EXPORT_SYMBOL(clपूर्णांक_समय_val);
#पूर्ण_अगर

अटल व्योम clपूर्णांक_send_ipi(स्थिर काष्ठा cpumask *target)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, target)
		ग_लिखोl(1, clपूर्णांक_ipi_base + cpuid_to_hartid_map(cpu));
पूर्ण

अटल व्योम clपूर्णांक_clear_ipi(व्योम)
अणु
	ग_लिखोl(0, clपूर्णांक_ipi_base + cpuid_to_hartid_map(smp_processor_id()));
पूर्ण

अटल काष्ठा riscv_ipi_ops clपूर्णांक_ipi_ops = अणु
	.ipi_inject = clपूर्णांक_send_ipi,
	.ipi_clear = clपूर्णांक_clear_ipi,
पूर्ण;

#अगर_घोषित CONFIG_64BIT
#घोषणा clपूर्णांक_get_cycles()	पढ़ोq_relaxed(clपूर्णांक_समयr_val)
#अन्यथा
#घोषणा clपूर्णांक_get_cycles()	पढ़ोl_relaxed(clपूर्णांक_समयr_val)
#घोषणा clपूर्णांक_get_cycles_hi()	पढ़ोl_relaxed(((u32 *)clपूर्णांक_समयr_val) + 1)
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
अटल u64 notrace clपूर्णांक_get_cycles64(व्योम)
अणु
	वापस clपूर्णांक_get_cycles();
पूर्ण
#अन्यथा /* CONFIG_64BIT */
अटल u64 notrace clपूर्णांक_get_cycles64(व्योम)
अणु
	u32 hi, lo;

	करो अणु
		hi = clपूर्णांक_get_cycles_hi();
		lo = clपूर्णांक_get_cycles();
	पूर्ण जबतक (hi != clपूर्णांक_get_cycles_hi());

	वापस ((u64)hi << 32) | lo;
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

अटल u64 clपूर्णांक_rdसमय(काष्ठा घड़ीsource *cs)
अणु
	वापस clपूर्णांक_get_cycles64();
पूर्ण

अटल काष्ठा घड़ीsource clपूर्णांक_घड़ीsource = अणु
	.name		= "clint_clocksource",
	.rating		= 300,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.पढ़ो		= clपूर्णांक_rdसमय,
पूर्ण;

अटल पूर्णांक clपूर्णांक_घड़ी_next_event(अचिन्हित दीर्घ delta,
				   काष्ठा घड़ी_event_device *ce)
अणु
	व्योम __iomem *r = clपूर्णांक_समयr_cmp +
			  cpuid_to_hartid_map(smp_processor_id());

	csr_set(CSR_IE, IE_TIE);
	ग_लिखोq_relaxed(clपूर्णांक_get_cycles64() + delta, r);
	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, clपूर्णांक_घड़ी_event) = अणु
	.name		= "clint_clockevent",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.rating		= 100,
	.set_next_event	= clपूर्णांक_घड़ी_next_event,
पूर्ण;

अटल पूर्णांक clपूर्णांक_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *ce = per_cpu_ptr(&clपूर्णांक_घड़ी_event, cpu);

	ce->cpumask = cpumask_of(cpu);
	घड़ीevents_config_and_रेजिस्टर(ce, clपूर्णांक_समयr_freq, 100, 0x7fffffff);

	enable_percpu_irq(clपूर्णांक_समयr_irq,
			  irq_get_trigger_type(clपूर्णांक_समयr_irq));
	वापस 0;
पूर्ण

अटल पूर्णांक clपूर्णांक_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(clपूर्णांक_समयr_irq);
	वापस 0;
पूर्ण

अटल irqवापस_t clपूर्णांक_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evdev = this_cpu_ptr(&clपूर्णांक_घड़ी_event);

	csr_clear(CSR_IE, IE_TIE);
	evdev->event_handler(evdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init clपूर्णांक_समयr_init_dt(काष्ठा device_node *np)
अणु
	पूर्णांक rc;
	u32 i, nr_irqs;
	व्योम __iomem *base;
	काष्ठा of_phandle_args oirq;

	/*
	 * Ensure that CLINT device पूर्णांकerrupts are either RV_IRQ_TIMER or
	 * RV_IRQ_SOFT. If it's anything अन्यथा then we ignore the device.
	 */
	nr_irqs = of_irq_count(np);
	क्रम (i = 0; i < nr_irqs; i++) अणु
		अगर (of_irq_parse_one(np, i, &oirq)) अणु
			pr_err("%pOFP: failed to parse irq %d.\n", np, i);
			जारी;
		पूर्ण

		अगर ((oirq.args_count != 1) ||
		    (oirq.args[0] != RV_IRQ_TIMER &&
		     oirq.args[0] != RV_IRQ_SOFT)) अणु
			pr_err("%pOFP: invalid irq %d (hwirq %d)\n",
			       np, i, oirq.args[0]);
			वापस -ENODEV;
		पूर्ण

		/* Find parent irq करोमुख्य and map समयr irq */
		अगर (!clपूर्णांक_समयr_irq &&
		    oirq.args[0] == RV_IRQ_TIMER &&
		    irq_find_host(oirq.np))
			clपूर्णांक_समयr_irq = irq_of_parse_and_map(np, i);
	पूर्ण

	/* If CLINT समयr irq not found then fail */
	अगर (!clपूर्णांक_समयr_irq) अणु
		pr_err("%pOFP: timer irq not found\n", np);
		वापस -ENODEV;
	पूर्ण

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("%pOFP: could not map registers\n", np);
		वापस -ENODEV;
	पूर्ण

	clपूर्णांक_ipi_base = base + CLINT_IPI_OFF;
	clपूर्णांक_समयr_cmp = base + CLINT_TIMER_CMP_OFF;
	clपूर्णांक_समयr_val = base + CLINT_TIMER_VAL_OFF;
	clपूर्णांक_समयr_freq = riscv_समयbase;

#अगर_घोषित CONFIG_RISCV_M_MODE
	/*
	 * Yes, that's an odd naming scheme.  समय_val is खुला, but hopefully
	 * will die in favor of something cleaner.
	 */
	clपूर्णांक_समय_val = clपूर्णांक_समयr_val;
#पूर्ण_अगर

	pr_info("%pOFP: timer running at %ld Hz\n", np, clपूर्णांक_समयr_freq);

	rc = घड़ीsource_रेजिस्टर_hz(&clपूर्णांक_घड़ीsource, clपूर्णांक_समयr_freq);
	अगर (rc) अणु
		pr_err("%pOFP: clocksource register failed [%d]\n", np, rc);
		जाओ fail_iounmap;
	पूर्ण

	sched_घड़ी_रेजिस्टर(clपूर्णांक_get_cycles64, 64, clपूर्णांक_समयr_freq);

	rc = request_percpu_irq(clपूर्णांक_समयr_irq, clपूर्णांक_समयr_पूर्णांकerrupt,
				 "clint-timer", &clपूर्णांक_घड़ी_event);
	अगर (rc) अणु
		pr_err("registering percpu irq failed [%d]\n", rc);
		जाओ fail_iounmap;
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_AP_CLINT_TIMER_STARTING,
				"clockevents/clint/timer:starting",
				clपूर्णांक_समयr_starting_cpu,
				clपूर्णांक_समयr_dying_cpu);
	अगर (rc) अणु
		pr_err("%pOFP: cpuhp setup state failed [%d]\n", np, rc);
		जाओ fail_मुक्त_irq;
	पूर्ण

	riscv_set_ipi_ops(&clपूर्णांक_ipi_ops);
	clपूर्णांक_clear_ipi();

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(clपूर्णांक_समयr_irq, &clपूर्णांक_घड़ी_event);
fail_iounmap:
	iounmap(base);
	वापस rc;
पूर्ण

TIMER_OF_DECLARE(clपूर्णांक_समयr, "riscv,clint0", clपूर्णांक_समयr_init_dt);
TIMER_OF_DECLARE(clपूर्णांक_समयr1, "sifive,clint0", clपूर्णांक_समयr_init_dt);
