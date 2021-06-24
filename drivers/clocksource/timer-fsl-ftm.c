<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale FlexTimer Module (FTM) समयr driver.
 *
 * Copyright 2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/fsl/fपंचांग.h>

#घोषणा FTM_SC_CLK(c)	((c) << FTM_SC_CLK_MASK_SHIFT)

काष्ठा fपंचांग_घड़ी_device अणु
	व्योम __iomem *clksrc_base;
	व्योम __iomem *clkevt_base;
	अचिन्हित दीर्घ periodic_cyc;
	अचिन्हित दीर्घ ps;
	bool big_endian;
पूर्ण;

अटल काष्ठा fपंचांग_घड़ी_device *priv;

अटल अंतरभूत u32 fपंचांग_पढ़ोl(व्योम __iomem *addr)
अणु
	अगर (priv->big_endian)
		वापस ioपढ़ो32be(addr);
	अन्यथा
		वापस ioपढ़ो32(addr);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_ग_लिखोl(u32 val, व्योम __iomem *addr)
अणु
	अगर (priv->big_endian)
		ioग_लिखो32be(val, addr);
	अन्यथा
		ioग_लिखो32(val, addr);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_counter_enable(व्योम __iomem *base)
अणु
	u32 val;

	/* select and enable counter घड़ी source */
	val = fपंचांग_पढ़ोl(base + FTM_SC);
	val &= ~(FTM_SC_PS_MASK | FTM_SC_CLK_MASK);
	val |= priv->ps | FTM_SC_CLK(1);
	fपंचांग_ग_लिखोl(val, base + FTM_SC);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_counter_disable(व्योम __iomem *base)
अणु
	u32 val;

	/* disable counter घड़ी source */
	val = fपंचांग_पढ़ोl(base + FTM_SC);
	val &= ~(FTM_SC_PS_MASK | FTM_SC_CLK_MASK);
	fपंचांग_ग_लिखोl(val, base + FTM_SC);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_irq_acknowledge(व्योम __iomem *base)
अणु
	u32 val;

	val = fपंचांग_पढ़ोl(base + FTM_SC);
	val &= ~FTM_SC_TOF;
	fपंचांग_ग_लिखोl(val, base + FTM_SC);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_irq_enable(व्योम __iomem *base)
अणु
	u32 val;

	val = fपंचांग_पढ़ोl(base + FTM_SC);
	val |= FTM_SC_TOIE;
	fपंचांग_ग_लिखोl(val, base + FTM_SC);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_irq_disable(व्योम __iomem *base)
अणु
	u32 val;

	val = fपंचांग_पढ़ोl(base + FTM_SC);
	val &= ~FTM_SC_TOIE;
	fपंचांग_ग_लिखोl(val, base + FTM_SC);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_reset_counter(व्योम __iomem *base)
अणु
	/*
	 * The CNT रेजिस्टर contains the FTM counter value.
	 * Reset clears the CNT रेजिस्टर. Writing any value to COUNT
	 * updates the counter with its initial value, CNTIN.
	 */
	fपंचांग_ग_लिखोl(0x00, base + FTM_CNT);
पूर्ण

अटल u64 notrace fपंचांग_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस fपंचांग_पढ़ोl(priv->clksrc_base + FTM_CNT);
पूर्ण

अटल पूर्णांक fपंचांग_set_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *unused)
अणु
	/*
	 * The CNNIN and MOD are all द्विगुन buffer रेजिस्टरs, writing
	 * to the MOD रेजिस्टर latches the value पूर्णांकo a buffer. The MOD
	 * रेजिस्टर is updated with the value of its ग_लिखो buffer with
	 * the following scenario:
	 * a, the counter source घड़ी is disabled.
	 */
	fपंचांग_counter_disable(priv->clkevt_base);

	/* Force the value of CNTIN to be loaded पूर्णांकo the FTM counter */
	fपंचांग_reset_counter(priv->clkevt_base);

	/*
	 * The counter increments until the value of MOD is reached,
	 * at which poपूर्णांक the counter is reloaded with the value of CNTIN.
	 * The TOF (the overflow flag) bit is set when the FTM counter
	 * changes from MOD to CNTIN. So we should using the delta - 1.
	 */
	fपंचांग_ग_लिखोl(delta - 1, priv->clkevt_base + FTM_MOD);

	fपंचांग_counter_enable(priv->clkevt_base);

	fपंचांग_irq_enable(priv->clkevt_base);

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	fपंचांग_counter_disable(priv->clkevt_base);
	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	fपंचांग_set_next_event(priv->periodic_cyc, evt);
	वापस 0;
पूर्ण

अटल irqवापस_t fपंचांग_evt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	fपंचांग_irq_acknowledge(priv->clkevt_base);

	अगर (likely(घड़ीevent_state_oneshot(evt))) अणु
		fपंचांग_irq_disable(priv->clkevt_base);
		fपंचांग_counter_disable(priv->clkevt_base);
	पूर्ण

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा घड़ी_event_device fपंचांग_घड़ीevent = अणु
	.name			= "Freescale ftm timer",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_state_periodic	= fपंचांग_set_periodic,
	.set_state_oneshot	= fपंचांग_set_oneshot,
	.set_next_event		= fपंचांग_set_next_event,
	.rating			= 300,
पूर्ण;

अटल पूर्णांक __init fपंचांग_घड़ीevent_init(अचिन्हित दीर्घ freq, पूर्णांक irq)
अणु
	पूर्णांक err;

	fपंचांग_ग_लिखोl(0x00, priv->clkevt_base + FTM_CNTIN);
	fपंचांग_ग_लिखोl(~0u, priv->clkevt_base + FTM_MOD);

	fपंचांग_reset_counter(priv->clkevt_base);

	err = request_irq(irq, fपंचांग_evt_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			  "Freescale ftm timer", &fपंचांग_घड़ीevent);
	अगर (err) अणु
		pr_err("ftm: setup irq failed: %d\n", err);
		वापस err;
	पूर्ण

	fपंचांग_घड़ीevent.cpumask = cpumask_of(0);
	fपंचांग_घड़ीevent.irq = irq;

	घड़ीevents_config_and_रेजिस्टर(&fपंचांग_घड़ीevent,
					freq / (1 << priv->ps),
					1, 0xffff);

	fपंचांग_counter_enable(priv->clkevt_base);

	वापस 0;
पूर्ण

अटल पूर्णांक __init fपंचांग_घड़ीsource_init(अचिन्हित दीर्घ freq)
अणु
	पूर्णांक err;

	fपंचांग_ग_लिखोl(0x00, priv->clksrc_base + FTM_CNTIN);
	fपंचांग_ग_लिखोl(~0u, priv->clksrc_base + FTM_MOD);

	fपंचांग_reset_counter(priv->clksrc_base);

	sched_घड़ी_रेजिस्टर(fपंचांग_पढ़ो_sched_घड़ी, 16, freq / (1 << priv->ps));
	err = घड़ीsource_mmio_init(priv->clksrc_base + FTM_CNT, "fsl-ftm",
				    freq / (1 << priv->ps), 300, 16,
				    घड़ीsource_mmio_पढ़ोl_up);
	अगर (err) अणु
		pr_err("ftm: init clock source mmio failed: %d\n", err);
		वापस err;
	पूर्ण

	fपंचांग_counter_enable(priv->clksrc_base);

	वापस 0;
पूर्ण

अटल पूर्णांक __init __fपंचांग_clk_init(काष्ठा device_node *np, अक्षर *cnt_name,
				 अक्षर *fपंचांग_name)
अणु
	काष्ठा clk *clk;
	पूर्णांक err;

	clk = of_clk_get_by_name(np, cnt_name);
	अगर (IS_ERR(clk)) अणु
		pr_err("ftm: Cannot get \"%s\": %ld\n", cnt_name, PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण
	err = clk_prepare_enable(clk);
	अगर (err) अणु
		pr_err("ftm: clock failed to prepare+enable \"%s\": %d\n",
			cnt_name, err);
		वापस err;
	पूर्ण

	clk = of_clk_get_by_name(np, fपंचांग_name);
	अगर (IS_ERR(clk)) अणु
		pr_err("ftm: Cannot get \"%s\": %ld\n", fपंचांग_name, PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण
	err = clk_prepare_enable(clk);
	अगर (err)
		pr_err("ftm: clock failed to prepare+enable \"%s\": %d\n",
			fपंचांग_name, err);

	वापस clk_get_rate(clk);
पूर्ण

अटल अचिन्हित दीर्घ __init fपंचांग_clk_init(काष्ठा device_node *np)
अणु
	दीर्घ freq;

	freq = __fपंचांग_clk_init(np, "ftm-evt-counter-en", "ftm-evt");
	अगर (freq <= 0)
		वापस 0;

	freq = __fपंचांग_clk_init(np, "ftm-src-counter-en", "ftm-src");
	अगर (freq <= 0)
		वापस 0;

	वापस freq;
पूर्ण

अटल पूर्णांक __init fपंचांग_calc_बंदst_round_cyc(अचिन्हित दीर्घ freq)
अणु
	priv->ps = 0;

	/* The counter रेजिस्टर is only using the lower 16 bits, and
	 * अगर the 'freq' value is to big here, then the periodic_cyc
	 * may exceed 0xFFFF.
	 */
	करो अणु
		priv->periodic_cyc = DIV_ROUND_CLOSEST(freq,
						HZ * (1 << priv->ps++));
	पूर्ण जबतक (priv->periodic_cyc > 0xFFFF);

	अगर (priv->ps > FTM_PS_MAX) अणु
		pr_err("ftm: the prescaler is %lu > %d\n",
				priv->ps, FTM_PS_MAX);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init fपंचांग_समयr_init(काष्ठा device_node *np)
अणु
	अचिन्हित दीर्घ freq;
	पूर्णांक ret, irq;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = -ENXIO;
	priv->clkevt_base = of_iomap(np, 0);
	अगर (!priv->clkevt_base) अणु
		pr_err("ftm: unable to map event timer registers\n");
		जाओ err_clkevt;
	पूर्ण

	priv->clksrc_base = of_iomap(np, 1);
	अगर (!priv->clksrc_base) अणु
		pr_err("ftm: unable to map source timer registers\n");
		जाओ err_clksrc;
	पूर्ण

	ret = -EINVAL;
	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0) अणु
		pr_err("ftm: unable to get IRQ from DT, %d\n", irq);
		जाओ err;
	पूर्ण

	priv->big_endian = of_property_पढ़ो_bool(np, "big-endian");

	freq = fपंचांग_clk_init(np);
	अगर (!freq)
		जाओ err;

	ret = fपंचांग_calc_बंदst_round_cyc(freq);
	अगर (ret)
		जाओ err;

	ret = fपंचांग_घड़ीsource_init(freq);
	अगर (ret)
		जाओ err;

	ret = fपंचांग_घड़ीevent_init(freq, irq);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	iounmap(priv->clksrc_base);
err_clksrc:
	iounmap(priv->clkevt_base);
err_clkevt:
	kमुक्त(priv);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(flexसमयr, "fsl,ftm-timer", fपंचांग_समयr_init);
