<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <linux/clk/clk-conf.h>

#समावेश <घड़ीsource/समयr-ti-dm.h>
#समावेश <dt-bindings/bus/ti-sysc.h>

/* For type1, set SYSC_OMAP2_CLOCKACTIVITY क्रम fck off on idle, l4 घड़ी on */
#घोषणा DMTIMER_TYPE1_ENABLE	((1 << 9) | (SYSC_IDLE_SMART << 3) | \
				 SYSC_OMAP2_ENAWAKEUP | SYSC_OMAP2_AUTOIDLE)
#घोषणा DMTIMER_TYPE1_DISABLE	(SYSC_OMAP2_SOFTRESET | SYSC_OMAP2_AUTOIDLE)
#घोषणा DMTIMER_TYPE2_ENABLE	(SYSC_IDLE_SMART_WKUP << 2)
#घोषणा DMTIMER_RESET_WAIT	100000

#घोषणा DMTIMER_INST_DONT_CARE	~0U

अटल पूर्णांक counter_32k;
अटल u32 घड़ीsource;
अटल u32 घड़ीevent;

/*
 * Subset of the समयr रेजिस्टरs we use. Note that the रेजिस्टर offsets
 * depend on the समयr revision detected.
 */
काष्ठा dmसमयr_sysसमयr अणु
	व्योम __iomem *base;
	u8 sysc;
	u8 irq_stat;
	u8 irq_ena;
	u8 pend;
	u8 load;
	u8 counter;
	u8 ctrl;
	u8 wakeup;
	u8 अगरctrl;
	काष्ठा clk *fck;
	काष्ठा clk *ick;
	अचिन्हित दीर्घ rate;
पूर्ण;

काष्ठा dmसमयr_घड़ीevent अणु
	काष्ठा घड़ी_event_device dev;
	काष्ठा dmसमयr_sysसमयr t;
	u32 period;
पूर्ण;

काष्ठा dmसमयr_घड़ीsource अणु
	काष्ठा घड़ीsource dev;
	काष्ठा dmसमयr_sysसमयr t;
	अचिन्हित पूर्णांक loadval;
पूर्ण;

/* Assumes v1 ip अगर bits [31:16] are zero */
अटल bool dmसमयr_sysसमयr_revision1(काष्ठा dmसमयr_sysसमयr *t)
अणु
	u32 tidr = पढ़ोl_relaxed(t->base);

	वापस !(tidr >> 16);
पूर्ण

अटल व्योम dmसमयr_sysसमयr_enable(काष्ठा dmसमयr_sysसमयr *t)
अणु
	u32 val;

	अगर (dmसमयr_sysसमयr_revision1(t))
		val = DMTIMER_TYPE1_ENABLE;
	अन्यथा
		val = DMTIMER_TYPE2_ENABLE;

	ग_लिखोl_relaxed(val, t->base + t->sysc);
पूर्ण

अटल व्योम dmसमयr_sysसमयr_disable(काष्ठा dmसमयr_sysसमयr *t)
अणु
	अगर (!dmसमयr_sysसमयr_revision1(t))
		वापस;

	ग_लिखोl_relaxed(DMTIMER_TYPE1_DISABLE, t->base + t->sysc);
पूर्ण

अटल पूर्णांक __init dmसमयr_sysसमयr_type1_reset(काष्ठा dmसमयr_sysसमयr *t)
अणु
	व्योम __iomem *syss = t->base + OMAP_TIMER_V1_SYS_STAT_OFFSET;
	पूर्णांक ret;
	u32 l;

	dmसमयr_sysसमयr_enable(t);
	ग_लिखोl_relaxed(BIT(1) | BIT(2), t->base + t->अगरctrl);
	ret = पढ़ोl_poll_समयout_atomic(syss, l, l & BIT(0), 100,
					DMTIMER_RESET_WAIT);

	वापस ret;
पूर्ण

/* Note we must use io_base instead of func_base क्रम type2 OCP regs */
अटल पूर्णांक __init dmसमयr_sysसमयr_type2_reset(काष्ठा dmसमयr_sysसमयr *t)
अणु
	व्योम __iomem *sysc = t->base + t->sysc;
	u32 l;

	dmसमयr_sysसमयr_enable(t);
	l = पढ़ोl_relaxed(sysc);
	l |= BIT(0);
	ग_लिखोl_relaxed(l, sysc);

	वापस पढ़ोl_poll_समयout_atomic(sysc, l, !(l & BIT(0)), 100,
					 DMTIMER_RESET_WAIT);
पूर्ण

अटल पूर्णांक __init dmसमयr_sysसमयr_reset(काष्ठा dmसमयr_sysसमयr *t)
अणु
	पूर्णांक ret;

	अगर (dmसमयr_sysसमयr_revision1(t))
		ret = dmसमयr_sysसमयr_type1_reset(t);
	अन्यथा
		ret = dmसमयr_sysसमयr_type2_reset(t);
	अगर (ret < 0) अणु
		pr_err("%s failed with %i\n", __func__, ret);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id counter_match_table[] = अणु
	अणु .compatible = "ti,omap-counter32k" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

/*
 * Check अगर the SoC als has a usable working 32 KiHz counter. The 32 KiHz
 * counter is handled by समयr-ti-32k, but we need to detect it as it
 * affects the preferred dmसमयr प्रणाली समयr configuration. There is
 * typically no use क्रम a dmसमयr घड़ीsource अगर the 32 KiHz counter is
 * present, except on am437x as described below.
 */
अटल व्योम __init dmसमयr_sysसमयr_check_counter32k(व्योम)
अणु
	काष्ठा device_node *np;

	अगर (counter_32k)
		वापस;

	np = of_find_matching_node(शून्य, counter_match_table);
	अगर (!np) अणु
		counter_32k = -ENODEV;

		वापस;
	पूर्ण

	अगर (of_device_is_available(np))
		counter_32k = 1;
	अन्यथा
		counter_32k = -ENODEV;

	of_node_put(np);
पूर्ण

अटल स्थिर काष्ठा of_device_id dmसमयr_match_table[] = अणु
	अणु .compatible = "ti,omap2420-timer", पूर्ण,
	अणु .compatible = "ti,omap3430-timer", पूर्ण,
	अणु .compatible = "ti,omap4430-timer", पूर्ण,
	अणु .compatible = "ti,omap5430-timer", पूर्ण,
	अणु .compatible = "ti,am335x-timer", पूर्ण,
	अणु .compatible = "ti,am335x-timer-1ms", पूर्ण,
	अणु .compatible = "ti,dm814-timer", पूर्ण,
	अणु .compatible = "ti,dm816-timer", पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

/*
 * Checks that प्रणाली समयrs are configured to not reset and idle during
 * the generic समयr-ti-dm device driver probe. And that the प्रणाली समयr
 * source घड़ीs are properly configured. Also, let's not hog any DSP and
 * PWM capable समयrs unnecessarily as प्रणाली समयrs.
 */
अटल bool __init dmसमयr_is_preferred(काष्ठा device_node *np)
अणु
	अगर (!of_device_is_available(np))
		वापस false;

	अगर (!of_property_पढ़ो_bool(np->parent,
				   "ti,no-reset-on-init"))
		वापस false;

	अगर (!of_property_पढ़ो_bool(np->parent, "ti,no-idle"))
		वापस false;

	/* Secure gpसमयr12 is always घड़ीed with a fixed source */
	अगर (!of_property_पढ़ो_bool(np, "ti,timer-secure")) अणु
		अगर (!of_property_पढ़ो_bool(np, "assigned-clocks"))
			वापस false;

		अगर (!of_property_पढ़ो_bool(np, "assigned-clock-parents"))
			वापस false;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "ti,timer-dsp"))
		वापस false;

	अगर (of_property_पढ़ो_bool(np, "ti,timer-pwm"))
		वापस false;

	वापस true;
पूर्ण

/*
 * Finds the first available usable always-on समयr, and assigns it to either
 * घड़ीevent or घड़ीsource depending अगर the counter_32k is available on the
 * SoC or not.
 *
 * Some omap3 boards with unreliable oscillator must not use the counter_32k
 * or dmसमयr1 with 32 KiHz source. Additionally, the boards with unreliable
 * oscillator should really set counter_32k as disabled, and delete dmसमयr1
 * ti,always-on property, but let's not count on it. For these quirky हालs,
 * we prefer using the always-on secure dmसमयr12 with the पूर्णांकernal 32 KiHz
 * घड़ी as the घड़ीsource, and any available dmसमयr as घड़ीevent.
 *
 * For am437x, we are using am335x style dmसमयr घड़ीsource. It is unclear
 * अगर this quirk handling is really needed, but let's change it separately
 * based on testing as it might cause side effects.
 */
अटल व्योम __init dmसमयr_sysसमयr_assign_alwon(व्योम)
अणु
	काष्ठा device_node *np;
	u32 pa = 0;
	bool quirk_unreliable_oscillator = false;

	/* Quirk unreliable 32 KiHz oscillator with incomplete dts */
	अगर (of_machine_is_compatible("ti,omap3-beagle") ||
	    of_machine_is_compatible("timll,omap3-devkit8000")) अणु
		quirk_unreliable_oscillator = true;
		counter_32k = -ENODEV;
	पूर्ण

	/* Quirk am437x using am335x style dmसमयr घड़ीsource */
	अगर (of_machine_is_compatible("ti,am43"))
		counter_32k = -ENODEV;

	क्रम_each_matching_node(np, dmसमयr_match_table) अणु
		अगर (!dmसमयr_is_preferred(np))
			जारी;

		अगर (of_property_पढ़ो_bool(np, "ti,timer-alwon")) अणु
			स्थिर __be32 *addr;

			addr = of_get_address(np, 0, शून्य, शून्य);
			pa = of_translate_address(np, addr);
			अगर (pa) अणु
				/* Quirky omap3 boards must use dmसमयr12 */
				अगर (quirk_unreliable_oscillator &&
				    pa == 0x48318000)
					जारी;

				of_node_put(np);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Usually no need क्रम dmसमयr घड़ीsource अगर we have counter32 */
	अगर (counter_32k >= 0) अणु
		घड़ीevent = pa;
		घड़ीsource = 0;
	पूर्ण अन्यथा अणु
		घड़ीsource = pa;
		घड़ीevent = DMTIMER_INST_DONT_CARE;
	पूर्ण
पूर्ण

/* Finds the first usable dmसमयr, used क्रम the करोn't care हाल */
अटल u32 __init dmसमयr_sysसमयr_find_first_available(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *addr;
	u32 pa = 0;

	क्रम_each_matching_node(np, dmसमयr_match_table) अणु
		अगर (!dmसमयr_is_preferred(np))
			जारी;

		addr = of_get_address(np, 0, शून्य, शून्य);
		pa = of_translate_address(np, addr);
		अगर (pa) अणु
			अगर (pa == घड़ीsource || pa == घड़ीevent) अणु
				pa = 0;
				जारी;
			पूर्ण

			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pa;
पूर्ण

/* Selects the best घड़ीsource and घड़ीevent to use */
अटल व्योम __init dmसमयr_sysसमयr_select_best(व्योम)
अणु
	dmसमयr_sysसमयr_check_counter32k();
	dmसमयr_sysसमयr_assign_alwon();

	अगर (घड़ीevent == DMTIMER_INST_DONT_CARE)
		घड़ीevent = dmसमयr_sysसमयr_find_first_available();

	pr_debug("%s: counter_32k: %i clocksource: %08x clockevent: %08x\n",
		 __func__, counter_32k, घड़ीsource, घड़ीevent);
पूर्ण

/* Interface घड़ीs are only available on some SoCs variants */
अटल पूर्णांक __init dmसमयr_sysसमयr_init_घड़ी(काष्ठा dmसमयr_sysसमयr *t,
					      काष्ठा device_node *np,
					      स्थिर अक्षर *name,
					      अचिन्हित दीर्घ *rate)
अणु
	काष्ठा clk *घड़ी;
	अचिन्हित दीर्घ r;
	bool is_ick = false;
	पूर्णांक error;

	is_ick = !म_भेदन(name, "ick", 3);

	घड़ी = of_clk_get_by_name(np, name);
	अगर ((PTR_ERR(घड़ी) == -EINVAL) && is_ick)
		वापस 0;
	अन्यथा अगर (IS_ERR(घड़ी))
		वापस PTR_ERR(घड़ी);

	error = clk_prepare_enable(घड़ी);
	अगर (error)
		वापस error;

	r = clk_get_rate(घड़ी);
	अगर (!r)
		वापस -ENODEV;

	अगर (is_ick)
		t->ick = घड़ी;
	अन्यथा
		t->fck = घड़ी;

	*rate = r;

	वापस 0;
पूर्ण

अटल पूर्णांक __init dmसमयr_sysसमयr_setup(काष्ठा device_node *np,
					 काष्ठा dmसमयr_sysसमयr *t)
अणु
	अचिन्हित दीर्घ rate;
	u8 regbase;
	पूर्णांक error;

	अगर (!of_device_is_compatible(np->parent, "ti,sysc"))
		वापस -EINVAL;

	t->base = of_iomap(np, 0);
	अगर (!t->base)
		वापस -ENXIO;

	/*
	 * Enable optional asचिन्हित-घड़ी-parents configured at the समयr
	 * node level. For regular device drivers, this is करोne स्वतःmatically
	 * by bus related code such as platक्रमm_drv_probe().
	 */
	error = of_clk_set_शेषs(np, false);
	अगर (error < 0)
		pr_err("%s: clock source init failed: %i\n", __func__, error);

	/* For ti-sysc, we have समयr घड़ीs at the parent module level */
	error = dmसमयr_sysसमयr_init_घड़ी(t, np->parent, "fck", &rate);
	अगर (error)
		जाओ err_unmap;

	t->rate = rate;

	error = dmसमयr_sysसमयr_init_घड़ी(t, np->parent, "ick", &rate);
	अगर (error)
		जाओ err_unmap;

	अगर (dmसमयr_sysसमयr_revision1(t)) अणु
		t->irq_stat = OMAP_TIMER_V1_STAT_OFFSET;
		t->irq_ena = OMAP_TIMER_V1_INT_EN_OFFSET;
		t->pend = _OMAP_TIMER_WRITE_PEND_OFFSET;
		regbase = 0;
	पूर्ण अन्यथा अणु
		t->irq_stat = OMAP_TIMER_V2_IRQSTATUS;
		t->irq_ena = OMAP_TIMER_V2_IRQENABLE_SET;
		regbase = OMAP_TIMER_V2_FUNC_OFFSET;
		t->pend = regbase + _OMAP_TIMER_WRITE_PEND_OFFSET;
	पूर्ण

	t->sysc = OMAP_TIMER_OCP_CFG_OFFSET;
	t->load = regbase + _OMAP_TIMER_LOAD_OFFSET;
	t->counter = regbase + _OMAP_TIMER_COUNTER_OFFSET;
	t->ctrl = regbase + _OMAP_TIMER_CTRL_OFFSET;
	t->wakeup = regbase + _OMAP_TIMER_WAKEUP_EN_OFFSET;
	t->अगरctrl = regbase + _OMAP_TIMER_IF_CTRL_OFFSET;

	dmसमयr_sysसमयr_reset(t);
	dmसमयr_sysसमयr_enable(t);
	pr_debug("dmtimer rev %08x sysc %08x\n", पढ़ोl_relaxed(t->base),
		 पढ़ोl_relaxed(t->base + t->sysc));

	वापस 0;

err_unmap:
	iounmap(t->base);

	वापस error;
पूर्ण

/* Clockevent */
अटल काष्ठा dmसमयr_घड़ीevent *
to_dmसमयr_घड़ीevent(काष्ठा घड़ी_event_device *घड़ीevent)
अणु
	वापस container_of(घड़ीevent, काष्ठा dmसमयr_घड़ीevent, dev);
पूर्ण

अटल irqवापस_t dmसमयr_घड़ीevent_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = data;
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;

	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, t->base + t->irq_stat);
	clkevt->dev.event_handler(&clkevt->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dmसमयr_set_next_event(अचिन्हित दीर्घ cycles,
				  काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = to_dmसमयr_घड़ीevent(evt);
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;
	व्योम __iomem *pend = t->base + t->pend;

	जबतक (पढ़ोl_relaxed(pend) & WP_TCRR)
		cpu_relax();
	ग_लिखोl_relaxed(0xffffffff - cycles, t->base + t->counter);

	जबतक (पढ़ोl_relaxed(pend) & WP_TCLR)
		cpu_relax();
	ग_लिखोl_relaxed(OMAP_TIMER_CTRL_ST, t->base + t->ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक dmसमयr_घड़ीevent_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = to_dmसमयr_घड़ीevent(evt);
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;
	व्योम __iomem *ctrl = t->base + t->ctrl;
	u32 l;

	l = पढ़ोl_relaxed(ctrl);
	अगर (l & OMAP_TIMER_CTRL_ST) अणु
		l &= ~BIT(0);
		ग_लिखोl_relaxed(l, ctrl);
		/* Flush posted ग_लिखो */
		l = पढ़ोl_relaxed(ctrl);
		/*  Wait क्रम functional घड़ी period x 3.5 */
		udelay(3500000 / t->rate + 1);
	पूर्ण
	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, t->base + t->irq_stat);

	वापस 0;
पूर्ण

अटल पूर्णांक dmसमयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = to_dmसमयr_घड़ीevent(evt);
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;
	व्योम __iomem *pend = t->base + t->pend;

	dmसमयr_घड़ीevent_shutकरोwn(evt);

	/* Looks like we need to first set the load value separately */
	जबतक (पढ़ोl_relaxed(pend) & WP_TLDR)
		cpu_relax();
	ग_लिखोl_relaxed(clkevt->period, t->base + t->load);

	जबतक (पढ़ोl_relaxed(pend) & WP_TCRR)
		cpu_relax();
	ग_लिखोl_relaxed(clkevt->period, t->base + t->counter);

	जबतक (पढ़ोl_relaxed(pend) & WP_TCLR)
		cpu_relax();
	ग_लिखोl_relaxed(OMAP_TIMER_CTRL_AR | OMAP_TIMER_CTRL_ST,
		       t->base + t->ctrl);

	वापस 0;
पूर्ण

अटल व्योम omap_घड़ीevent_idle(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = to_dmसमयr_घड़ीevent(evt);
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;

	dmसमयr_sysसमयr_disable(t);
	clk_disable(t->fck);
पूर्ण

अटल व्योम omap_घड़ीevent_unidle(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = to_dmसमयr_घड़ीevent(evt);
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;
	पूर्णांक error;

	error = clk_enable(t->fck);
	अगर (error)
		pr_err("could not enable timer fck on resume: %i\n", error);

	dmसमयr_sysसमयr_enable(t);
	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, t->base + t->irq_ena);
	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, t->base + t->wakeup);
पूर्ण

अटल पूर्णांक __init dmसमयr_clkevt_init_common(काष्ठा dmसमयr_घड़ीevent *clkevt,
					     काष्ठा device_node *np,
					     अचिन्हित पूर्णांक features,
					     स्थिर काष्ठा cpumask *cpumask,
					     स्थिर अक्षर *name,
					     पूर्णांक rating)
अणु
	काष्ठा घड़ी_event_device *dev;
	काष्ठा dmसमयr_sysसमयr *t;
	पूर्णांक error;

	t = &clkevt->t;
	dev = &clkevt->dev;

	/*
	 * We mostly use cpuidle_coupled with ARM local समयrs क्रम runसमय,
	 * so there's probably no use क्रम CLOCK_EVT_FEAT_DYNIRQ here.
	 */
	dev->features = features;
	dev->rating = rating;
	dev->set_next_event = dmसमयr_set_next_event;
	dev->set_state_shutकरोwn = dmसमयr_घड़ीevent_shutकरोwn;
	dev->set_state_periodic = dmसमयr_set_periodic;
	dev->set_state_oneshot = dmसमयr_घड़ीevent_shutकरोwn;
	dev->set_state_oneshot_stopped = dmसमयr_घड़ीevent_shutकरोwn;
	dev->tick_resume = dmसमयr_घड़ीevent_shutकरोwn;
	dev->cpumask = cpumask;

	dev->irq = irq_of_parse_and_map(np, 0);
	अगर (!dev->irq)
		वापस -ENXIO;

	error = dmसमयr_sysसमयr_setup(np, &clkevt->t);
	अगर (error)
		वापस error;

	clkevt->period = 0xffffffff - DIV_ROUND_CLOSEST(t->rate, HZ);

	/*
	 * For घड़ी-event समयrs we never पढ़ो the समयr counter and
	 * so we are not impacted by errata i103 and i767. Thereक्रमe,
	 * we can safely ignore this errata क्रम घड़ी-event समयrs.
	 */
	ग_लिखोl_relaxed(OMAP_TIMER_CTRL_POSTED, t->base + t->अगरctrl);

	error = request_irq(dev->irq, dmसमयr_घड़ीevent_पूर्णांकerrupt,
			    IRQF_TIMER, name, clkevt);
	अगर (error)
		जाओ err_out_unmap;

	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, t->base + t->irq_ena);
	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, t->base + t->wakeup);

	pr_info("TI gptimer %s: %s%lu Hz at %pOF\n",
		name, of_find_property(np, "ti,timer-alwon", शून्य) ?
		"always-on " : "", t->rate, np->parent);

	वापस 0;

err_out_unmap:
	iounmap(t->base);

	वापस error;
पूर्ण

अटल पूर्णांक __init dmसमयr_घड़ीevent_init(काष्ठा device_node *np)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt;
	पूर्णांक error;

	clkevt = kzalloc(माप(*clkevt), GFP_KERNEL);
	अगर (!clkevt)
		वापस -ENOMEM;

	error = dmसमयr_clkevt_init_common(clkevt, np,
					   CLOCK_EVT_FEAT_PERIODIC |
					   CLOCK_EVT_FEAT_ONESHOT,
					   cpu_possible_mask, "clockevent",
					   300);
	अगर (error)
		जाओ err_out_मुक्त;

	घड़ीevents_config_and_रेजिस्टर(&clkevt->dev, clkevt->t.rate,
					3, /* Timer पूर्णांकernal resync latency */
					0xffffffff);

	अगर (of_machine_is_compatible("ti,am33xx") ||
	    of_machine_is_compatible("ti,am43")) अणु
		clkevt->dev.suspend = omap_घड़ीevent_idle;
		clkevt->dev.resume = omap_घड़ीevent_unidle;
	पूर्ण

	वापस 0;

err_out_मुक्त:
	kमुक्त(clkevt);

	वापस error;
पूर्ण

/* Dmसमयr as percpu समयr. See dra7 ARM architected समयr wrap erratum i940 */
अटल DEFINE_PER_CPU(काष्ठा dmसमयr_घड़ीevent, dmसमयr_percpu_समयr);

अटल पूर्णांक __init dmसमयr_percpu_समयr_init(काष्ठा device_node *np, पूर्णांक cpu)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt;
	पूर्णांक error;

	अगर (!cpu_possible(cpu))
		वापस -EINVAL;

	अगर (!of_property_पढ़ो_bool(np->parent, "ti,no-reset-on-init") ||
	    !of_property_पढ़ो_bool(np->parent, "ti,no-idle"))
		pr_warn("Incomplete dtb for percpu dmtimer %pOF\n", np->parent);

	clkevt = per_cpu_ptr(&dmसमयr_percpu_समयr, cpu);

	error = dmसमयr_clkevt_init_common(clkevt, np, CLOCK_EVT_FEAT_ONESHOT,
					   cpumask_of(cpu), "percpu-dmtimer",
					   500);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/* See TRM क्रम समयr पूर्णांकernal resynch latency */
अटल पूर्णांक omap_dmसमयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = per_cpu_ptr(&dmसमयr_percpu_समयr, cpu);
	काष्ठा घड़ी_event_device *dev = &clkevt->dev;
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;

	घड़ीevents_config_and_रेजिस्टर(dev, t->rate, 3, अच_दीर्घ_उच्च);
	irq_क्रमce_affinity(dev->irq, cpumask_of(cpu));

	वापस 0;
पूर्ण

अटल पूर्णांक __init dmसमयr_percpu_समयr_startup(व्योम)
अणु
	काष्ठा dmसमयr_घड़ीevent *clkevt = per_cpu_ptr(&dmसमयr_percpu_समयr, 0);
	काष्ठा dmसमयr_sysसमयr *t = &clkevt->t;

	अगर (t->sysc) अणु
		cpuhp_setup_state(CPUHP_AP_TI_GP_TIMER_STARTING,
				  "clockevents/omap/gptimer:starting",
				  omap_dmसमयr_starting_cpu, शून्य);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(dmसमयr_percpu_समयr_startup);

अटल पूर्णांक __init dmसमयr_percpu_quirk_init(काष्ठा device_node *np, u32 pa)
अणु
	काष्ठा device_node *arm_समयr;

	arm_समयr = of_find_compatible_node(शून्य, शून्य, "arm,armv7-timer");
	अगर (of_device_is_available(arm_समयr)) अणु
		pr_warn_once("ARM architected timer wrap issue i940 detected\n");
		वापस 0;
	पूर्ण

	अगर (pa == 0x48034000)		/* dra7 dmसमयr3 */
		वापस dmसमयr_percpu_समयr_init(np, 0);
	अन्यथा अगर (pa == 0x48036000)	/* dra7 dmसमयr4 */
		वापस dmसमयr_percpu_समयr_init(np, 1);

	वापस 0;
पूर्ण

/* Clocksource */
अटल काष्ठा dmसमयr_घड़ीsource *
to_dmसमयr_घड़ीsource(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा dmसमयr_घड़ीsource, dev);
पूर्ण

अटल u64 dmसमयr_घड़ीsource_पढ़ो_cycles(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा dmसमयr_घड़ीsource *clksrc = to_dmसमयr_घड़ीsource(cs);
	काष्ठा dmसमयr_sysसमयr *t = &clksrc->t;

	वापस (u64)पढ़ोl_relaxed(t->base + t->counter);
पूर्ण

अटल व्योम __iomem *dmसमयr_sched_घड़ी_counter;

अटल u64 notrace dmसमयr_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl_relaxed(dmसमयr_sched_घड़ी_counter);
पूर्ण

अटल व्योम dmसमयr_घड़ीsource_suspend(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा dmसमयr_घड़ीsource *clksrc = to_dmसमयr_घड़ीsource(cs);
	काष्ठा dmसमयr_sysसमयr *t = &clksrc->t;

	clksrc->loadval = पढ़ोl_relaxed(t->base + t->counter);
	dmसमयr_sysसमयr_disable(t);
	clk_disable(t->fck);
पूर्ण

अटल व्योम dmसमयr_घड़ीsource_resume(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा dmसमयr_घड़ीsource *clksrc = to_dmसमयr_घड़ीsource(cs);
	काष्ठा dmसमयr_sysसमयr *t = &clksrc->t;
	पूर्णांक error;

	error = clk_enable(t->fck);
	अगर (error)
		pr_err("could not enable timer fck on resume: %i\n", error);

	dmसमयr_sysसमयr_enable(t);
	ग_लिखोl_relaxed(clksrc->loadval, t->base + t->counter);
	ग_लिखोl_relaxed(OMAP_TIMER_CTRL_ST | OMAP_TIMER_CTRL_AR,
		       t->base + t->ctrl);
पूर्ण

अटल पूर्णांक __init dmसमयr_घड़ीsource_init(काष्ठा device_node *np)
अणु
	काष्ठा dmसमयr_घड़ीsource *clksrc;
	काष्ठा dmसमयr_sysसमयr *t;
	काष्ठा घड़ीsource *dev;
	पूर्णांक error;

	clksrc = kzalloc(माप(*clksrc), GFP_KERNEL);
	अगर (!clksrc)
		वापस -ENOMEM;

	dev = &clksrc->dev;
	t = &clksrc->t;

	error = dmसमयr_sysसमयr_setup(np, t);
	अगर (error)
		जाओ err_out_मुक्त;

	dev->name = "dmtimer";
	dev->rating = 300;
	dev->पढ़ो = dmसमयr_घड़ीsource_पढ़ो_cycles;
	dev->mask = CLOCKSOURCE_MASK(32);
	dev->flags = CLOCK_SOURCE_IS_CONTINUOUS;

	/* Unlike क्रम घड़ीevent, legacy code sets suspend only क्रम am4 */
	अगर (of_machine_is_compatible("ti,am43")) अणु
		dev->suspend = dmसमयr_घड़ीsource_suspend;
		dev->resume = dmसमयr_घड़ीsource_resume;
	पूर्ण

	ग_लिखोl_relaxed(0, t->base + t->counter);
	ग_लिखोl_relaxed(OMAP_TIMER_CTRL_ST | OMAP_TIMER_CTRL_AR,
		       t->base + t->ctrl);

	pr_info("TI gptimer clocksource: %s%pOF\n",
		of_find_property(np, "ti,timer-alwon", शून्य) ?
		"always-on " : "", np->parent);

	अगर (!dmसमयr_sched_घड़ी_counter) अणु
		dmसमयr_sched_घड़ी_counter = t->base + t->counter;
		sched_घड़ी_रेजिस्टर(dmसमयr_पढ़ो_sched_घड़ी, 32, t->rate);
	पूर्ण

	अगर (घड़ीsource_रेजिस्टर_hz(dev, t->rate))
		pr_err("Could not register clocksource %pOF\n", np);

	वापस 0;

err_out_मुक्त:
	kमुक्त(clksrc);

	वापस -ENODEV;
पूर्ण

/*
 * To detect between a घड़ीsource and घड़ीevent, we assume the device tree
 * has no पूर्णांकerrupts configured क्रम a घड़ीsource समयr.
 */
अटल पूर्णांक __init dmसमयr_sysसमयr_init(काष्ठा device_node *np)
अणु
	स्थिर __be32 *addr;
	u32 pa;

	/* One समय init क्रम the preferred समयr configuration */
	अगर (!घड़ीsource && !घड़ीevent)
		dmसमयr_sysसमयr_select_best();

	अगर (!घड़ीsource && !घड़ीevent) अणु
		pr_err("%s: unable to detect system timers, update dtb?\n",
		       __func__);

		वापस -EINVAL;
	पूर्ण

	addr = of_get_address(np, 0, शून्य, शून्य);
	pa = of_translate_address(np, addr);
	अगर (!pa)
		वापस -EINVAL;

	अगर (counter_32k <= 0 && घड़ीsource == pa)
		वापस dmसमयr_घड़ीsource_init(np);

	अगर (घड़ीevent == pa)
		वापस dmसमयr_घड़ीevent_init(np);

	अगर (of_machine_is_compatible("ti,dra7"))
		वापस dmसमयr_percpu_quirk_init(np, pa);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(sysसमयr_omap2, "ti,omap2420-timer", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_omap3, "ti,omap3430-timer", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_omap4, "ti,omap4430-timer", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_omap5, "ti,omap5430-timer", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_am33x, "ti,am335x-timer", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_am3ms, "ti,am335x-timer-1ms", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_dm814, "ti,dm814-timer", dmसमयr_sysसमयr_init);
TIMER_OF_DECLARE(sysसमयr_dm816, "ti,dm816-timer", dmसमयr_sysसमयr_init);
