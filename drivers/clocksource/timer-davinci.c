<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI DaVinci घड़ीsource driver
 *
 * Copyright (C) 2019 Texas Instruments
 * Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
 * (with tiny parts aकरोpted from code by Kevin Hilman <khilman@baylibre.com>)
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <घड़ीsource/समयr-davinci.h>

#घोषणा DAVINCI_TIMER_REG_TIM12			0x10
#घोषणा DAVINCI_TIMER_REG_TIM34			0x14
#घोषणा DAVINCI_TIMER_REG_PRD12			0x18
#घोषणा DAVINCI_TIMER_REG_PRD34			0x1c
#घोषणा DAVINCI_TIMER_REG_TCR			0x20
#घोषणा DAVINCI_TIMER_REG_TGCR			0x24

#घोषणा DAVINCI_TIMER_TIMMODE_MASK		GENMASK(3, 2)
#घोषणा DAVINCI_TIMER_RESET_MASK		GENMASK(1, 0)
#घोषणा DAVINCI_TIMER_TIMMODE_32BIT_UNCHAINED	BIT(2)
#घोषणा DAVINCI_TIMER_UNRESET			GENMASK(1, 0)

#घोषणा DAVINCI_TIMER_ENAMODE_MASK		GENMASK(1, 0)
#घोषणा DAVINCI_TIMER_ENAMODE_DISABLED		0x00
#घोषणा DAVINCI_TIMER_ENAMODE_ONESHOT		BIT(0)
#घोषणा DAVINCI_TIMER_ENAMODE_PERIODIC		BIT(1)

#घोषणा DAVINCI_TIMER_ENAMODE_SHIFT_TIM12	6
#घोषणा DAVINCI_TIMER_ENAMODE_SHIFT_TIM34	22

#घोषणा DAVINCI_TIMER_MIN_DELTA			0x01
#घोषणा DAVINCI_TIMER_MAX_DELTA			0xfffffffe

#घोषणा DAVINCI_TIMER_CLKSRC_BITS		32

#घोषणा DAVINCI_TIMER_TGCR_DEFAULT \
		(DAVINCI_TIMER_TIMMODE_32BIT_UNCHAINED | DAVINCI_TIMER_UNRESET)

काष्ठा davinci_घड़ीevent अणु
	काष्ठा घड़ी_event_device dev;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक cmp_off;
पूर्ण;

/*
 * This must be globally accessible by davinci_समयr_पढ़ो_sched_घड़ी(), so
 * let's keep it here.
 */
अटल काष्ठा अणु
	काष्ठा घड़ीsource dev;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक tim_off;
पूर्ण davinci_घड़ीsource;

अटल काष्ठा davinci_घड़ीevent *
to_davinci_घड़ीevent(काष्ठा घड़ी_event_device *घड़ीevent)
अणु
	वापस container_of(घड़ीevent, काष्ठा davinci_घड़ीevent, dev);
पूर्ण

अटल अचिन्हित पूर्णांक
davinci_घड़ीevent_पढ़ो(काष्ठा davinci_घड़ीevent *घड़ीevent,
			अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(घड़ीevent->base + reg);
पूर्ण

अटल व्योम davinci_घड़ीevent_ग_लिखो(काष्ठा davinci_घड़ीevent *घड़ीevent,
				     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl_relaxed(val, घड़ीevent->base + reg);
पूर्ण

अटल व्योम davinci_tim12_shutकरोwn(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक tcr;

	tcr = DAVINCI_TIMER_ENAMODE_DISABLED <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM12;
	/*
	 * This function is only ever called अगर we're using both समयr
	 * halves. In this हाल TIM34 runs in periodic mode and we must
	 * not modअगरy it.
	 */
	tcr |= DAVINCI_TIMER_ENAMODE_PERIODIC <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM34;

	ग_लिखोl_relaxed(tcr, base + DAVINCI_TIMER_REG_TCR);
पूर्ण

अटल व्योम davinci_tim12_set_oneshot(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक tcr;

	tcr = DAVINCI_TIMER_ENAMODE_ONESHOT <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM12;
	/* Same as above. */
	tcr |= DAVINCI_TIMER_ENAMODE_PERIODIC <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM34;

	ग_लिखोl_relaxed(tcr, base + DAVINCI_TIMER_REG_TCR);
पूर्ण

अटल पूर्णांक davinci_घड़ीevent_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा davinci_घड़ीevent *घड़ीevent;

	घड़ीevent = to_davinci_घड़ीevent(dev);

	davinci_tim12_shutकरोwn(घड़ीevent->base);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_घड़ीevent_set_oneshot(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा davinci_घड़ीevent *घड़ीevent = to_davinci_घड़ीevent(dev);

	davinci_घड़ीevent_ग_लिखो(घड़ीevent, DAVINCI_TIMER_REG_TIM12, 0x0);

	davinci_tim12_set_oneshot(घड़ीevent->base);

	वापस 0;
पूर्ण

अटल पूर्णांक
davinci_घड़ीevent_set_next_event_std(अचिन्हित दीर्घ cycles,
				      काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा davinci_घड़ीevent *घड़ीevent = to_davinci_घड़ीevent(dev);

	davinci_घड़ीevent_shutकरोwn(dev);

	davinci_घड़ीevent_ग_लिखो(घड़ीevent, DAVINCI_TIMER_REG_TIM12, 0x0);
	davinci_घड़ीevent_ग_लिखो(घड़ीevent, DAVINCI_TIMER_REG_PRD12, cycles);

	davinci_घड़ीevent_set_oneshot(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
davinci_घड़ीevent_set_next_event_cmp(अचिन्हित दीर्घ cycles,
				      काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा davinci_घड़ीevent *घड़ीevent = to_davinci_घड़ीevent(dev);
	अचिन्हित पूर्णांक curr_समय;

	curr_समय = davinci_घड़ीevent_पढ़ो(घड़ीevent,
					    DAVINCI_TIMER_REG_TIM12);
	davinci_घड़ीevent_ग_लिखो(घड़ीevent,
				 घड़ीevent->cmp_off, curr_समय + cycles);

	वापस 0;
पूर्ण

अटल irqवापस_t davinci_समयr_irq_समयr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा davinci_घड़ीevent *घड़ीevent = data;

	अगर (!घड़ीevent_state_oneshot(&घड़ीevent->dev))
		davinci_tim12_shutकरोwn(घड़ीevent->base);

	घड़ीevent->dev.event_handler(&घड़ीevent->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल u64 notrace davinci_समयr_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl_relaxed(davinci_घड़ीsource.base +
			     davinci_घड़ीsource.tim_off);
पूर्ण

अटल u64 davinci_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *dev)
अणु
	वापस davinci_समयr_पढ़ो_sched_घड़ी();
पूर्ण

/*
 * Standard use-हाल: we're using tim12 क्रम घड़ीevent and tim34 क्रम
 * घड़ीsource. The शेष is making the क्रमmer run in oneshot mode
 * and the latter in periodic mode.
 */
अटल व्योम davinci_घड़ीsource_init_tim34(व्योम __iomem *base)
अणु
	पूर्णांक tcr;

	tcr = DAVINCI_TIMER_ENAMODE_PERIODIC <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM34;
	tcr |= DAVINCI_TIMER_ENAMODE_ONESHOT <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM12;

	ग_लिखोl_relaxed(0x0, base + DAVINCI_TIMER_REG_TIM34);
	ग_लिखोl_relaxed(अच_पूर्णांक_उच्च, base + DAVINCI_TIMER_REG_PRD34);
	ग_लिखोl_relaxed(tcr, base + DAVINCI_TIMER_REG_TCR);
पूर्ण

/*
 * Special use-हाल on da830: the DSP may use tim34. We're using tim12 क्रम
 * both घड़ीsource and घड़ीevent. We set tim12 to periodic and करोn't touch
 * tim34.
 */
अटल व्योम davinci_घड़ीsource_init_tim12(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक tcr;

	tcr = DAVINCI_TIMER_ENAMODE_PERIODIC <<
		DAVINCI_TIMER_ENAMODE_SHIFT_TIM12;

	ग_लिखोl_relaxed(0x0, base + DAVINCI_TIMER_REG_TIM12);
	ग_लिखोl_relaxed(अच_पूर्णांक_उच्च, base + DAVINCI_TIMER_REG_PRD12);
	ग_लिखोl_relaxed(tcr, base + DAVINCI_TIMER_REG_TCR);
पूर्ण

अटल व्योम davinci_समयr_init(व्योम __iomem *base)
अणु
	/* Set घड़ी to पूर्णांकernal mode and disable it. */
	ग_लिखोl_relaxed(0x0, base + DAVINCI_TIMER_REG_TCR);
	/*
	 * Reset both 32-bit समयrs, set no prescaler क्रम समयr 34, set the
	 * समयr to dual 32-bit unchained mode, unreset both 32-bit समयrs.
	 */
	ग_लिखोl_relaxed(DAVINCI_TIMER_TGCR_DEFAULT,
		       base + DAVINCI_TIMER_REG_TGCR);
	/* Init both counters to zero. */
	ग_लिखोl_relaxed(0x0, base + DAVINCI_TIMER_REG_TIM12);
	ग_लिखोl_relaxed(0x0, base + DAVINCI_TIMER_REG_TIM34);
पूर्ण

पूर्णांक __init davinci_समयr_रेजिस्टर(काष्ठा clk *clk,
				  स्थिर काष्ठा davinci_समयr_cfg *समयr_cfg)
अणु
	काष्ठा davinci_घड़ीevent *घड़ीevent;
	अचिन्हित पूर्णांक tick_rate;
	व्योम __iomem *base;
	पूर्णांक rv;

	rv = clk_prepare_enable(clk);
	अगर (rv) अणु
		pr_err("Unable to prepare and enable the timer clock\n");
		वापस rv;
	पूर्ण

	अगर (!request_mem_region(समयr_cfg->reg.start,
				resource_size(&समयr_cfg->reg),
				"davinci-timer")) अणु
		pr_err("Unable to request memory region\n");
		वापस -EBUSY;
	पूर्ण

	base = ioremap(समयr_cfg->reg.start, resource_size(&समयr_cfg->reg));
	अगर (!base) अणु
		pr_err("Unable to map the register range\n");
		वापस -ENOMEM;
	पूर्ण

	davinci_समयr_init(base);
	tick_rate = clk_get_rate(clk);

	घड़ीevent = kzalloc(माप(*घड़ीevent), GFP_KERNEL);
	अगर (!घड़ीevent)
		वापस -ENOMEM;

	घड़ीevent->dev.name = "tim12";
	घड़ीevent->dev.features = CLOCK_EVT_FEAT_ONESHOT;
	घड़ीevent->dev.cpumask = cpumask_of(0);
	घड़ीevent->base = base;

	अगर (समयr_cfg->cmp_off) अणु
		घड़ीevent->cmp_off = समयr_cfg->cmp_off;
		घड़ीevent->dev.set_next_event =
				davinci_घड़ीevent_set_next_event_cmp;
	पूर्ण अन्यथा अणु
		घड़ीevent->dev.set_next_event =
				davinci_घड़ीevent_set_next_event_std;
		घड़ीevent->dev.set_state_oneshot =
				davinci_घड़ीevent_set_oneshot;
		घड़ीevent->dev.set_state_shutकरोwn =
				davinci_घड़ीevent_shutकरोwn;
	पूर्ण

	rv = request_irq(समयr_cfg->irq[DAVINCI_TIMER_CLOCKEVENT_IRQ].start,
			 davinci_समयr_irq_समयr, IRQF_TIMER,
			 "clockevent/tim12", घड़ीevent);
	अगर (rv) अणु
		pr_err("Unable to request the clockevent interrupt\n");
		वापस rv;
	पूर्ण

	davinci_घड़ीsource.dev.rating = 300;
	davinci_घड़ीsource.dev.पढ़ो = davinci_घड़ीsource_पढ़ो;
	davinci_घड़ीsource.dev.mask =
			CLOCKSOURCE_MASK(DAVINCI_TIMER_CLKSRC_BITS);
	davinci_घड़ीsource.dev.flags = CLOCK_SOURCE_IS_CONTINUOUS;
	davinci_घड़ीsource.base = base;

	अगर (समयr_cfg->cmp_off) अणु
		davinci_घड़ीsource.dev.name = "tim12";
		davinci_घड़ीsource.tim_off = DAVINCI_TIMER_REG_TIM12;
		davinci_घड़ीsource_init_tim12(base);
	पूर्ण अन्यथा अणु
		davinci_घड़ीsource.dev.name = "tim34";
		davinci_घड़ीsource.tim_off = DAVINCI_TIMER_REG_TIM34;
		davinci_घड़ीsource_init_tim34(base);
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&घड़ीevent->dev, tick_rate,
					DAVINCI_TIMER_MIN_DELTA,
					DAVINCI_TIMER_MAX_DELTA);

	rv = घड़ीsource_रेजिस्टर_hz(&davinci_घड़ीsource.dev, tick_rate);
	अगर (rv) अणु
		pr_err("Unable to register clocksource\n");
		वापस rv;
	पूर्ण

	sched_घड़ी_रेजिस्टर(davinci_समयr_पढ़ो_sched_घड़ी,
			     DAVINCI_TIMER_CLKSRC_BITS, tick_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक __init of_davinci_समयr_रेजिस्टर(काष्ठा device_node *np)
अणु
	काष्ठा davinci_समयr_cfg समयr_cfg = अणु पूर्ण;
	काष्ठा clk *clk;
	पूर्णांक rv;

	rv = of_address_to_resource(np, 0, &समयr_cfg.reg);
	अगर (rv) अणु
		pr_err("Unable to get the register range for timer\n");
		वापस rv;
	पूर्ण

	rv = of_irq_to_resource_table(np, समयr_cfg.irq,
				      DAVINCI_TIMER_NUM_IRQS);
	अगर (rv != DAVINCI_TIMER_NUM_IRQS) अणु
		pr_err("Unable to get the interrupts for timer\n");
		वापस rv;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Unable to get the timer clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	rv = davinci_समयr_रेजिस्टर(clk, &समयr_cfg);
	अगर (rv)
		clk_put(clk);

	वापस rv;
पूर्ण
TIMER_OF_DECLARE(davinci_समयr, "ti,da830-timer", of_davinci_समयr_रेजिस्टर);
