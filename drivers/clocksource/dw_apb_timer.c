<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) Copyright 2009 Intel Corporation
 * Author: Jacob Pan (jacob.jun.pan@पूर्णांकel.com)
 *
 * Shared with ARM platक्रमms, Jamie Iles, Picochip 2011
 *
 * Support क्रम the Synopsys DesignWare APB Timers.
 */
#समावेश <linux/dw_apb_समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा APBT_MIN_PERIOD			4
#घोषणा APBT_MIN_DELTA_USEC		200

#घोषणा APBTMR_N_LOAD_COUNT		0x00
#घोषणा APBTMR_N_CURRENT_VALUE		0x04
#घोषणा APBTMR_N_CONTROL		0x08
#घोषणा APBTMR_N_EOI			0x0c
#घोषणा APBTMR_N_INT_STATUS		0x10

#घोषणा APBTMRS_INT_STATUS		0xa0
#घोषणा APBTMRS_EOI			0xa4
#घोषणा APBTMRS_RAW_INT_STATUS		0xa8
#घोषणा APBTMRS_COMP_VERSION		0xac

#घोषणा APBTMR_CONTROL_ENABLE		(1 << 0)
/* 1: periodic, 0:मुक्त running. */
#घोषणा APBTMR_CONTROL_MODE_PERIODIC	(1 << 1)
#घोषणा APBTMR_CONTROL_INT		(1 << 2)

अटल अंतरभूत काष्ठा dw_apb_घड़ी_event_device *
ced_to_dw_apb_ced(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा dw_apb_घड़ी_event_device, ced);
पूर्ण

अटल अंतरभूत काष्ठा dw_apb_घड़ीsource *
घड़ीsource_to_dw_apb_घड़ीsource(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा dw_apb_घड़ीsource, cs);
पूर्ण

अटल अंतरभूत u32 apbt_पढ़ोl(काष्ठा dw_apb_समयr *समयr, अचिन्हित दीर्घ offs)
अणु
	वापस पढ़ोl(समयr->base + offs);
पूर्ण

अटल अंतरभूत व्योम apbt_ग_लिखोl(काष्ठा dw_apb_समयr *समयr, u32 val,
			अचिन्हित दीर्घ offs)
अणु
	ग_लिखोl(val, समयr->base + offs);
पूर्ण

अटल अंतरभूत u32 apbt_पढ़ोl_relaxed(काष्ठा dw_apb_समयr *समयr, अचिन्हित दीर्घ offs)
अणु
	वापस पढ़ोl_relaxed(समयr->base + offs);
पूर्ण

अटल अंतरभूत व्योम apbt_ग_लिखोl_relaxed(काष्ठा dw_apb_समयr *समयr, u32 val,
			अचिन्हित दीर्घ offs)
अणु
	ग_लिखोl_relaxed(val, समयr->base + offs);
पूर्ण

अटल व्योम apbt_disable_पूर्णांक(काष्ठा dw_apb_समयr *समयr)
अणु
	u32 ctrl = apbt_पढ़ोl(समयr, APBTMR_N_CONTROL);

	ctrl |= APBTMR_CONTROL_INT;
	apbt_ग_लिखोl(समयr, ctrl, APBTMR_N_CONTROL);
पूर्ण

/**
 * dw_apb_घड़ीevent_छोड़ो() - stop the घड़ी_event_device from running
 *
 * @dw_ced:	The APB घड़ी to stop generating events.
 */
व्योम dw_apb_घड़ीevent_छोड़ो(काष्ठा dw_apb_घड़ी_event_device *dw_ced)
अणु
	disable_irq(dw_ced->समयr.irq);
	apbt_disable_पूर्णांक(&dw_ced->समयr);
पूर्ण

अटल व्योम apbt_eoi(काष्ठा dw_apb_समयr *समयr)
अणु
	apbt_पढ़ोl_relaxed(समयr, APBTMR_N_EOI);
पूर्ण

अटल irqवापस_t dw_apb_घड़ीevent_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा घड़ी_event_device *evt = data;
	काष्ठा dw_apb_घड़ी_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	अगर (!evt->event_handler) अणु
		pr_info("Spurious APBT timer interrupt %d\n", irq);
		वापस IRQ_NONE;
	पूर्ण

	अगर (dw_ced->eoi)
		dw_ced->eoi(&dw_ced->समयr);

	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम apbt_enable_पूर्णांक(काष्ठा dw_apb_समयr *समयr)
अणु
	u32 ctrl = apbt_पढ़ोl(समयr, APBTMR_N_CONTROL);
	/* clear pending पूर्णांकr */
	apbt_पढ़ोl(समयr, APBTMR_N_EOI);
	ctrl &= ~APBTMR_CONTROL_INT;
	apbt_ग_लिखोl(समयr, ctrl, APBTMR_N_CONTROL);
पूर्ण

अटल पूर्णांक apbt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dw_apb_घड़ी_event_device *dw_ced = ced_to_dw_apb_ced(evt);
	u32 ctrl;

	pr_debug("%s CPU %d state=shutdown\n", __func__,
		 cpumask_first(evt->cpumask));

	ctrl = apbt_पढ़ोl(&dw_ced->समयr, APBTMR_N_CONTROL);
	ctrl &= ~APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक apbt_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dw_apb_घड़ी_event_device *dw_ced = ced_to_dw_apb_ced(evt);
	u32 ctrl;

	pr_debug("%s CPU %d state=oneshot\n", __func__,
		 cpumask_first(evt->cpumask));

	ctrl = apbt_पढ़ोl(&dw_ced->समयr, APBTMR_N_CONTROL);
	/*
	 * set मुक्त running mode, this mode will let समयr reload max
	 * समयout which will give समय (3min on 25MHz घड़ी) to rearm
	 * the next event, thereक्रमe emulate the one-shot mode.
	 */
	ctrl &= ~APBTMR_CONTROL_ENABLE;
	ctrl &= ~APBTMR_CONTROL_MODE_PERIODIC;

	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	/* ग_लिखो again to set मुक्त running mode */
	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);

	/*
	 * DW APB p. 46, load counter with all 1s beक्रमe starting मुक्त
	 * running mode.
	 */
	apbt_ग_लिखोl(&dw_ced->समयr, ~0, APBTMR_N_LOAD_COUNT);
	ctrl &= ~APBTMR_CONTROL_INT;
	ctrl |= APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक apbt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dw_apb_घड़ी_event_device *dw_ced = ced_to_dw_apb_ced(evt);
	अचिन्हित दीर्घ period = DIV_ROUND_UP(dw_ced->समयr.freq, HZ);
	u32 ctrl;

	pr_debug("%s CPU %d state=periodic\n", __func__,
		 cpumask_first(evt->cpumask));

	ctrl = apbt_पढ़ोl(&dw_ced->समयr, APBTMR_N_CONTROL);
	ctrl |= APBTMR_CONTROL_MODE_PERIODIC;
	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	/*
	 * DW APB p. 46, have to disable समयr beक्रमe load counter,
	 * may cause sync problem.
	 */
	ctrl &= ~APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	udelay(1);
	pr_debug("Setting clock period %lu for HZ %d\n", period, HZ);
	apbt_ग_लिखोl(&dw_ced->समयr, period, APBTMR_N_LOAD_COUNT);
	ctrl |= APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक apbt_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dw_apb_घड़ी_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	pr_debug("%s CPU %d state=resume\n", __func__,
		 cpumask_first(evt->cpumask));

	apbt_enable_पूर्णांक(&dw_ced->समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक apbt_next_event(अचिन्हित दीर्घ delta,
			   काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl;
	काष्ठा dw_apb_घड़ी_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	/* Disable समयr */
	ctrl = apbt_पढ़ोl_relaxed(&dw_ced->समयr, APBTMR_N_CONTROL);
	ctrl &= ~APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl_relaxed(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);
	/* ग_लिखो new count */
	apbt_ग_लिखोl_relaxed(&dw_ced->समयr, delta, APBTMR_N_LOAD_COUNT);
	ctrl |= APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl_relaxed(&dw_ced->समयr, ctrl, APBTMR_N_CONTROL);

	वापस 0;
पूर्ण

/**
 * dw_apb_घड़ीevent_init() - use an APB समयr as a घड़ी_event_device
 *
 * @cpu:	The CPU the events will be targeted at or -1 अगर CPU affiliation
 *		isn't required.
 * @name:	The name used क्रम the समयr and the IRQ क्रम it.
 * @rating:	The rating to give the समयr.
 * @base:	I/O base क्रम the समयr रेजिस्टरs.
 * @irq:	The पूर्णांकerrupt number to use क्रम the समयr.
 * @freq:	The frequency that the समयr counts at.
 *
 * This creates a घड़ी_event_device क्रम using with the generic घड़ी layer
 * but करोes not start and रेजिस्टर it.  This should be करोne with
 * dw_apb_घड़ीevent_रेजिस्टर() as the next step.  If this is the first समय
 * it has been called क्रम a समयr then the IRQ will be requested, अगर not it
 * just be enabled to allow CPU hotplug to aव्योम repeatedly requesting and
 * releasing the IRQ.
 */
काष्ठा dw_apb_घड़ी_event_device *
dw_apb_घड़ीevent_init(पूर्णांक cpu, स्थिर अक्षर *name, अचिन्हित rating,
		       व्योम __iomem *base, पूर्णांक irq, अचिन्हित दीर्घ freq)
अणु
	काष्ठा dw_apb_घड़ी_event_device *dw_ced =
		kzalloc(माप(*dw_ced), GFP_KERNEL);
	पूर्णांक err;

	अगर (!dw_ced)
		वापस शून्य;

	dw_ced->समयr.base = base;
	dw_ced->समयr.irq = irq;
	dw_ced->समयr.freq = freq;

	घड़ीevents_calc_mult_shअगरt(&dw_ced->ced, freq, APBT_MIN_PERIOD);
	dw_ced->ced.max_delta_ns = घड़ीevent_delta2ns(0x7fffffff,
						       &dw_ced->ced);
	dw_ced->ced.max_delta_ticks = 0x7fffffff;
	dw_ced->ced.min_delta_ns = घड़ीevent_delta2ns(5000, &dw_ced->ced);
	dw_ced->ced.min_delta_ticks = 5000;
	dw_ced->ced.cpumask = cpu < 0 ? cpu_possible_mask : cpumask_of(cpu);
	dw_ced->ced.features = CLOCK_EVT_FEAT_PERIODIC |
				CLOCK_EVT_FEAT_ONESHOT | CLOCK_EVT_FEAT_DYNIRQ;
	dw_ced->ced.set_state_shutकरोwn = apbt_shutकरोwn;
	dw_ced->ced.set_state_periodic = apbt_set_periodic;
	dw_ced->ced.set_state_oneshot = apbt_set_oneshot;
	dw_ced->ced.set_state_oneshot_stopped = apbt_shutकरोwn;
	dw_ced->ced.tick_resume = apbt_resume;
	dw_ced->ced.set_next_event = apbt_next_event;
	dw_ced->ced.irq = dw_ced->समयr.irq;
	dw_ced->ced.rating = rating;
	dw_ced->ced.name = name;

	dw_ced->eoi = apbt_eoi;
	err = request_irq(irq, dw_apb_घड़ीevent_irq,
			  IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			  dw_ced->ced.name, &dw_ced->ced);
	अगर (err) अणु
		pr_err("failed to request timer irq\n");
		kमुक्त(dw_ced);
		dw_ced = शून्य;
	पूर्ण

	वापस dw_ced;
पूर्ण

/**
 * dw_apb_घड़ीevent_resume() - resume a घड़ी that has been छोड़ोd.
 *
 * @dw_ced:	The APB घड़ी to resume.
 */
व्योम dw_apb_घड़ीevent_resume(काष्ठा dw_apb_घड़ी_event_device *dw_ced)
अणु
	enable_irq(dw_ced->समयr.irq);
पूर्ण

/**
 * dw_apb_घड़ीevent_stop() - stop the घड़ी_event_device and release the IRQ.
 *
 * @dw_ced:	The APB घड़ी to stop generating the events.
 */
व्योम dw_apb_घड़ीevent_stop(काष्ठा dw_apb_घड़ी_event_device *dw_ced)
अणु
	मुक्त_irq(dw_ced->समयr.irq, &dw_ced->ced);
पूर्ण

/**
 * dw_apb_घड़ीevent_रेजिस्टर() - रेजिस्टर the घड़ी with the generic layer
 *
 * @dw_ced:	The APB घड़ी to रेजिस्टर as a घड़ी_event_device.
 */
व्योम dw_apb_घड़ीevent_रेजिस्टर(काष्ठा dw_apb_घड़ी_event_device *dw_ced)
अणु
	apbt_ग_लिखोl(&dw_ced->समयr, 0, APBTMR_N_CONTROL);
	घड़ीevents_रेजिस्टर_device(&dw_ced->ced);
	apbt_enable_पूर्णांक(&dw_ced->समयr);
पूर्ण

/**
 * dw_apb_घड़ीsource_start() - start the घड़ीsource counting.
 *
 * @dw_cs:	The घड़ीsource to start.
 *
 * This is used to start the घड़ीsource beक्रमe registration and can be used
 * to enable calibration of समयrs.
 */
व्योम dw_apb_घड़ीsource_start(काष्ठा dw_apb_घड़ीsource *dw_cs)
अणु
	/*
	 * start count करोwn from 0xffff_ffff. this is करोne by toggling the
	 * enable bit then load initial load count to ~0.
	 */
	u32 ctrl = apbt_पढ़ोl(&dw_cs->समयr, APBTMR_N_CONTROL);

	ctrl &= ~APBTMR_CONTROL_ENABLE;
	apbt_ग_लिखोl(&dw_cs->समयr, ctrl, APBTMR_N_CONTROL);
	apbt_ग_लिखोl(&dw_cs->समयr, ~0, APBTMR_N_LOAD_COUNT);
	/* enable, mask पूर्णांकerrupt */
	ctrl &= ~APBTMR_CONTROL_MODE_PERIODIC;
	ctrl |= (APBTMR_CONTROL_ENABLE | APBTMR_CONTROL_INT);
	apbt_ग_लिखोl(&dw_cs->समयr, ctrl, APBTMR_N_CONTROL);
	/* पढ़ो it once to get cached counter value initialized */
	dw_apb_घड़ीsource_पढ़ो(dw_cs);
पूर्ण

अटल u64 __apbt_पढ़ो_घड़ीsource(काष्ठा घड़ीsource *cs)
अणु
	u32 current_count;
	काष्ठा dw_apb_घड़ीsource *dw_cs =
		घड़ीsource_to_dw_apb_घड़ीsource(cs);

	current_count = apbt_पढ़ोl_relaxed(&dw_cs->समयr,
					APBTMR_N_CURRENT_VALUE);

	वापस (u64)~current_count;
पूर्ण

अटल व्योम apbt_restart_घड़ीsource(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा dw_apb_घड़ीsource *dw_cs =
		घड़ीsource_to_dw_apb_घड़ीsource(cs);

	dw_apb_घड़ीsource_start(dw_cs);
पूर्ण

/**
 * dw_apb_घड़ीsource_init() - use an APB समयr as a घड़ीsource.
 *
 * @rating:	The rating to give the घड़ीsource.
 * @name:	The name क्रम the घड़ीsource.
 * @base:	The I/O base क्रम the समयr रेजिस्टरs.
 * @freq:	The frequency that the समयr counts at.
 *
 * This creates a घड़ीsource using an APB समयr but करोes not yet रेजिस्टर it
 * with the घड़ीsource प्रणाली.  This should be करोne with
 * dw_apb_घड़ीsource_रेजिस्टर() as the next step.
 */
काष्ठा dw_apb_घड़ीsource *
dw_apb_घड़ीsource_init(अचिन्हित rating, स्थिर अक्षर *name, व्योम __iomem *base,
			अचिन्हित दीर्घ freq)
अणु
	काष्ठा dw_apb_घड़ीsource *dw_cs = kzalloc(माप(*dw_cs), GFP_KERNEL);

	अगर (!dw_cs)
		वापस शून्य;

	dw_cs->समयr.base = base;
	dw_cs->समयr.freq = freq;
	dw_cs->cs.name = name;
	dw_cs->cs.rating = rating;
	dw_cs->cs.पढ़ो = __apbt_पढ़ो_घड़ीsource;
	dw_cs->cs.mask = CLOCKSOURCE_MASK(32);
	dw_cs->cs.flags = CLOCK_SOURCE_IS_CONTINUOUS;
	dw_cs->cs.resume = apbt_restart_घड़ीsource;

	वापस dw_cs;
पूर्ण

/**
 * dw_apb_घड़ीsource_रेजिस्टर() - रेजिस्टर the APB घड़ीsource.
 *
 * @dw_cs:	The घड़ीsource to रेजिस्टर.
 */
व्योम dw_apb_घड़ीsource_रेजिस्टर(काष्ठा dw_apb_घड़ीsource *dw_cs)
अणु
	घड़ीsource_रेजिस्टर_hz(&dw_cs->cs, dw_cs->समयr.freq);
पूर्ण

/**
 * dw_apb_घड़ीsource_पढ़ो() - पढ़ो the current value of a घड़ीsource.
 *
 * @dw_cs:	The घड़ीsource to पढ़ो.
 */
u64 dw_apb_घड़ीsource_पढ़ो(काष्ठा dw_apb_घड़ीsource *dw_cs)
अणु
	वापस (u64)~apbt_पढ़ोl(&dw_cs->समयr, APBTMR_N_CURRENT_VALUE);
पूर्ण
