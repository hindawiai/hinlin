<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/reg_ops.h>

#समावेश "timer-of.h"

#घोषणा PTIM_CCVR	"cr<3, 14>"
#घोषणा PTIM_CTLR	"cr<0, 14>"
#घोषणा PTIM_LVR	"cr<6, 14>"
#घोषणा PTIM_TSR	"cr<1, 14>"

अटल पूर्णांक csky_mpसमयr_irq;

अटल पूर्णांक csky_mpसमयr_set_next_event(अचिन्हित दीर्घ delta,
				       काष्ठा घड़ी_event_device *ce)
अणु
	mtcr(PTIM_LVR, delta);

	वापस 0;
पूर्ण

अटल पूर्णांक csky_mpसमयr_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	mtcr(PTIM_CTLR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक csky_mpसमयr_oneshot(काष्ठा घड़ी_event_device *ce)
अणु
	mtcr(PTIM_CTLR, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक csky_mpसमयr_oneshot_stopped(काष्ठा घड़ी_event_device *ce)
अणु
	mtcr(PTIM_CTLR, 0);

	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा समयr_of, csky_to) = अणु
	.flags					= TIMER_OF_CLOCK,
	.clkevt = अणु
		.rating				= 300,
		.features			= CLOCK_EVT_FEAT_PERCPU |
						  CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn		= csky_mpसमयr_shutकरोwn,
		.set_state_oneshot		= csky_mpसमयr_oneshot,
		.set_state_oneshot_stopped	= csky_mpसमयr_oneshot_stopped,
		.set_next_event			= csky_mpसमयr_set_next_event,
	पूर्ण,
पूर्ण;

अटल irqवापस_t csky_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा समयr_of *to = this_cpu_ptr(&csky_to);

	mtcr(PTIM_TSR, 0);

	to->clkevt.event_handler(&to->clkevt);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * घड़ी event क्रम percpu
 */
अटल पूर्णांक csky_mpसमयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_of *to = per_cpu_ptr(&csky_to, cpu);

	to->clkevt.cpumask = cpumask_of(cpu);

	enable_percpu_irq(csky_mpसमयr_irq, 0);

	घड़ीevents_config_and_रेजिस्टर(&to->clkevt, समयr_of_rate(to),
					2, अच_दीर्घ_उच्च);

	वापस 0;
पूर्ण

अटल पूर्णांक csky_mpसमयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(csky_mpसमयr_irq);

	वापस 0;
पूर्ण

/*
 * घड़ी source
 */
अटल u64 notrace sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस (u64)mfcr(PTIM_CCVR);
पूर्ण

अटल u64 clksrc_पढ़ो(काष्ठा घड़ीsource *c)
अणु
	वापस (u64)mfcr(PTIM_CCVR);
पूर्ण

काष्ठा घड़ीsource csky_घड़ीsource = अणु
	.name	= "csky",
	.rating	= 400,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	.पढ़ो	= clksrc_पढ़ो,
पूर्ण;

अटल पूर्णांक __init csky_mpसमयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret, cpu, cpu_rollback;
	काष्ठा समयr_of *to = शून्य;

	/*
	 * Csky_mpसमयr is deचिन्हित क्रम C-SKY SMP multi-processors and
	 * every core has it's own निजी irq and regs क्रम clkevt and
	 * clksrc.
	 *
	 * The regs is accessed by cpu inकाष्ठाion: mfcr/mtcr instead of
	 * mmio map style. So we needn't mmio-address in dts, but we still
	 * need to give clk and irq number.
	 *
	 * We use निजी irq क्रम the mpसमयr and irq number is the same
	 * क्रम every core. So we use request_percpu_irq() in समयr_of_init.
	 */
	csky_mpसमयr_irq = irq_of_parse_and_map(np, 0);
	अगर (csky_mpसमयr_irq <= 0)
		वापस -EINVAL;

	ret = request_percpu_irq(csky_mpसमयr_irq, csky_समयr_पूर्णांकerrupt,
				 "csky_mp_timer", &csky_to);
	अगर (ret)
		वापस -EINVAL;

	क्रम_each_possible_cpu(cpu) अणु
		to = per_cpu_ptr(&csky_to, cpu);
		ret = समयr_of_init(np, to);
		अगर (ret)
			जाओ rollback;
	पूर्ण

	घड़ीsource_रेजिस्टर_hz(&csky_घड़ीsource, समयr_of_rate(to));
	sched_घड़ी_रेजिस्टर(sched_घड़ी_पढ़ो, 32, समयr_of_rate(to));

	ret = cpuhp_setup_state(CPUHP_AP_CSKY_TIMER_STARTING,
				"clockevents/csky/timer:starting",
				csky_mpसमयr_starting_cpu,
				csky_mpसमयr_dying_cpu);
	अगर (ret)
		वापस -EINVAL;

	वापस 0;

rollback:
	क्रम_each_possible_cpu(cpu_rollback) अणु
		अगर (cpu_rollback == cpu)
			अवरोध;

		to = per_cpu_ptr(&csky_to, cpu_rollback);
		समयr_of_cleanup(to);
	पूर्ण
	वापस -EINVAL;
पूर्ण
TIMER_OF_DECLARE(csky_mpसमयr, "csky,mptimer", csky_mpसमयr_init);
