<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
//  Copyright (C) 2000-2001 Deep Blue Solutions
//  Copyright (C) 2002 Shane Nay (shane@minirl.com)
//  Copyright (C) 2006-2007 Pavel Pisa (ppisa@pikron.com)
//  Copyright (C) 2008 Juergen Beisert (kernel@pengutronix.de)

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <soc/imx/समयr.h>

/*
 * There are 4 versions of the समयr hardware on Freescale MXC hardware.
 *  - MX1/MXL
 *  - MX21, MX27.
 *  - MX25, MX31, MX35, MX37, MX51, MX6Q(rev1.0)
 *  - MX6DL, MX6SX, MX6Q(rev1.1+)
 */

/* defines common क्रम all i.MX */
#घोषणा MXC_TCTL		0x00
#घोषणा MXC_TCTL_TEN		(1 << 0) /* Enable module */
#घोषणा MXC_TPRER		0x04

/* MX1, MX21, MX27 */
#घोषणा MX1_2_TCTL_CLK_PCLK1	(1 << 1)
#घोषणा MX1_2_TCTL_IRQEN	(1 << 4)
#घोषणा MX1_2_TCTL_FRR		(1 << 8)
#घोषणा MX1_2_TCMP		0x08
#घोषणा MX1_2_TCN		0x10
#घोषणा MX1_2_TSTAT		0x14

/* MX21, MX27 */
#घोषणा MX2_TSTAT_CAPT		(1 << 1)
#घोषणा MX2_TSTAT_COMP		(1 << 0)

/* MX31, MX35, MX25, MX5, MX6 */
#घोषणा V2_TCTL_WAITEN		(1 << 3) /* Wait enable mode */
#घोषणा V2_TCTL_CLK_IPG		(1 << 6)
#घोषणा V2_TCTL_CLK_PER		(2 << 6)
#घोषणा V2_TCTL_CLK_OSC_DIV8	(5 << 6)
#घोषणा V2_TCTL_FRR		(1 << 9)
#घोषणा V2_TCTL_24MEN		(1 << 10)
#घोषणा V2_TPRER_PRE24M		12
#घोषणा V2_IR			0x0c
#घोषणा V2_TSTAT		0x08
#घोषणा V2_TSTAT_OF1		(1 << 0)
#घोषणा V2_TCN			0x24
#घोषणा V2_TCMP			0x10

#घोषणा V2_TIMER_RATE_OSC_DIV8	3000000

काष्ठा imx_समयr अणु
	क्रमागत imx_gpt_type type;
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा clk *clk_per;
	काष्ठा clk *clk_ipg;
	स्थिर काष्ठा imx_gpt_data *gpt;
	काष्ठा घड़ी_event_device ced;
पूर्ण;

काष्ठा imx_gpt_data अणु
	पूर्णांक reg_tstat;
	पूर्णांक reg_tcn;
	पूर्णांक reg_tcmp;
	व्योम (*gpt_setup_tctl)(काष्ठा imx_समयr *imxपंचांग);
	व्योम (*gpt_irq_enable)(काष्ठा imx_समयr *imxपंचांग);
	व्योम (*gpt_irq_disable)(काष्ठा imx_समयr *imxपंचांग);
	व्योम (*gpt_irq_acknowledge)(काष्ठा imx_समयr *imxपंचांग);
	पूर्णांक (*set_next_event)(अचिन्हित दीर्घ evt,
			      काष्ठा घड़ी_event_device *ced);
पूर्ण;

अटल अंतरभूत काष्ठा imx_समयr *to_imx_समयr(काष्ठा घड़ी_event_device *ced)
अणु
	वापस container_of(ced, काष्ठा imx_समयr, ced);
पूर्ण

अटल व्योम imx1_gpt_irq_disable(काष्ठा imx_समयr *imxपंचांग)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = पढ़ोl_relaxed(imxपंचांग->base + MXC_TCTL);
	ग_लिखोl_relaxed(पंचांगp & ~MX1_2_TCTL_IRQEN, imxपंचांग->base + MXC_TCTL);
पूर्ण
#घोषणा imx21_gpt_irq_disable imx1_gpt_irq_disable

अटल व्योम imx31_gpt_irq_disable(काष्ठा imx_समयr *imxपंचांग)
अणु
	ग_लिखोl_relaxed(0, imxपंचांग->base + V2_IR);
पूर्ण
#घोषणा imx6dl_gpt_irq_disable imx31_gpt_irq_disable

अटल व्योम imx1_gpt_irq_enable(काष्ठा imx_समयr *imxपंचांग)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = पढ़ोl_relaxed(imxपंचांग->base + MXC_TCTL);
	ग_लिखोl_relaxed(पंचांगp | MX1_2_TCTL_IRQEN, imxपंचांग->base + MXC_TCTL);
पूर्ण
#घोषणा imx21_gpt_irq_enable imx1_gpt_irq_enable

अटल व्योम imx31_gpt_irq_enable(काष्ठा imx_समयr *imxपंचांग)
अणु
	ग_लिखोl_relaxed(1<<0, imxपंचांग->base + V2_IR);
पूर्ण
#घोषणा imx6dl_gpt_irq_enable imx31_gpt_irq_enable

अटल व्योम imx1_gpt_irq_acknowledge(काष्ठा imx_समयr *imxपंचांग)
अणु
	ग_लिखोl_relaxed(0, imxपंचांग->base + MX1_2_TSTAT);
पूर्ण

अटल व्योम imx21_gpt_irq_acknowledge(काष्ठा imx_समयr *imxपंचांग)
अणु
	ग_लिखोl_relaxed(MX2_TSTAT_CAPT | MX2_TSTAT_COMP,
				imxपंचांग->base + MX1_2_TSTAT);
पूर्ण

अटल व्योम imx31_gpt_irq_acknowledge(काष्ठा imx_समयr *imxपंचांग)
अणु
	ग_लिखोl_relaxed(V2_TSTAT_OF1, imxपंचांग->base + V2_TSTAT);
पूर्ण
#घोषणा imx6dl_gpt_irq_acknowledge imx31_gpt_irq_acknowledge

अटल व्योम __iomem *sched_घड़ी_reg;

अटल u64 notrace mxc_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस sched_घड़ी_reg ? पढ़ोl_relaxed(sched_घड़ी_reg) : 0;
पूर्ण

#अगर defined(CONFIG_ARM)
अटल काष्ठा delay_समयr imx_delay_समयr;

अटल अचिन्हित दीर्घ imx_पढ़ो_current_समयr(व्योम)
अणु
	वापस पढ़ोl_relaxed(sched_घड़ी_reg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mxc_घड़ीsource_init(काष्ठा imx_समयr *imxपंचांग)
अणु
	अचिन्हित पूर्णांक c = clk_get_rate(imxपंचांग->clk_per);
	व्योम __iomem *reg = imxपंचांग->base + imxपंचांग->gpt->reg_tcn;

#अगर defined(CONFIG_ARM)
	imx_delay_समयr.पढ़ो_current_समयr = &imx_पढ़ो_current_समयr;
	imx_delay_समयr.freq = c;
	रेजिस्टर_current_समयr_delay(&imx_delay_समयr);
#पूर्ण_अगर

	sched_घड़ी_reg = reg;

	sched_घड़ी_रेजिस्टर(mxc_पढ़ो_sched_घड़ी, 32, c);
	वापस घड़ीsource_mmio_init(reg, "mxc_timer1", c, 200, 32,
			घड़ीsource_mmio_पढ़ोl_up);
पूर्ण

/* घड़ी event */

अटल पूर्णांक mx1_2_set_next_event(अचिन्हित दीर्घ evt,
			      काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा imx_समयr *imxपंचांग = to_imx_समयr(ced);
	अचिन्हित दीर्घ tcmp;

	tcmp = पढ़ोl_relaxed(imxपंचांग->base + MX1_2_TCN) + evt;

	ग_लिखोl_relaxed(tcmp, imxपंचांग->base + MX1_2_TCMP);

	वापस (पूर्णांक)(tcmp - पढ़ोl_relaxed(imxपंचांग->base + MX1_2_TCN)) < 0 ?
				-ETIME : 0;
पूर्ण

अटल पूर्णांक v2_set_next_event(अचिन्हित दीर्घ evt,
			      काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा imx_समयr *imxपंचांग = to_imx_समयr(ced);
	अचिन्हित दीर्घ tcmp;

	tcmp = पढ़ोl_relaxed(imxपंचांग->base + V2_TCN) + evt;

	ग_लिखोl_relaxed(tcmp, imxपंचांग->base + V2_TCMP);

	वापस evt < 0x7fffffff &&
		(पूर्णांक)(tcmp - पढ़ोl_relaxed(imxपंचांग->base + V2_TCN)) < 0 ?
				-ETIME : 0;
पूर्ण

अटल पूर्णांक mxc_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा imx_समयr *imxपंचांग = to_imx_समयr(ced);
	u32 tcn;

	/* Disable पूर्णांकerrupt in GPT module */
	imxपंचांग->gpt->gpt_irq_disable(imxपंचांग);

	tcn = पढ़ोl_relaxed(imxपंचांग->base + imxपंचांग->gpt->reg_tcn);
	/* Set event समय पूर्णांकo far-far future */
	ग_लिखोl_relaxed(tcn - 3, imxपंचांग->base + imxपंचांग->gpt->reg_tcmp);

	/* Clear pending पूर्णांकerrupt */
	imxपंचांग->gpt->gpt_irq_acknowledge(imxपंचांग);

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_INFO "%s: changing mode\n", __func__);
#पूर्ण_अगर /* DEBUG */

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_set_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा imx_समयr *imxपंचांग = to_imx_समयr(ced);

	/* Disable पूर्णांकerrupt in GPT module */
	imxपंचांग->gpt->gpt_irq_disable(imxपंचांग);

	अगर (!घड़ीevent_state_oneshot(ced)) अणु
		u32 tcn = पढ़ोl_relaxed(imxपंचांग->base + imxपंचांग->gpt->reg_tcn);
		/* Set event समय पूर्णांकo far-far future */
		ग_लिखोl_relaxed(tcn - 3, imxपंचांग->base + imxपंचांग->gpt->reg_tcmp);

		/* Clear pending पूर्णांकerrupt */
		imxपंचांग->gpt->gpt_irq_acknowledge(imxपंचांग);
	पूर्ण

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_INFO "%s: changing mode\n", __func__);
#पूर्ण_अगर /* DEBUG */

	/*
	 * Do not put overhead of पूर्णांकerrupt enable/disable पूर्णांकo
	 * mxc_set_next_event(), the core has about 4 minutes
	 * to call mxc_set_next_event() or shutकरोwn घड़ी after
	 * mode चयनing
	 */
	imxपंचांग->gpt->gpt_irq_enable(imxपंचांग);

	वापस 0;
पूर्ण

/*
 * IRQ handler क्रम the समयr
 */
अटल irqवापस_t mxc_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *ced = dev_id;
	काष्ठा imx_समयr *imxपंचांग = to_imx_समयr(ced);
	uपूर्णांक32_t tstat;

	tstat = पढ़ोl_relaxed(imxपंचांग->base + imxपंचांग->gpt->reg_tstat);

	imxपंचांग->gpt->gpt_irq_acknowledge(imxपंचांग);

	ced->event_handler(ced);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init mxc_घड़ीevent_init(काष्ठा imx_समयr *imxपंचांग)
अणु
	काष्ठा घड़ी_event_device *ced = &imxपंचांग->ced;

	ced->name = "mxc_timer1";
	ced->features = CLOCK_EVT_FEAT_ONESHOT | CLOCK_EVT_FEAT_DYNIRQ;
	ced->set_state_shutकरोwn = mxc_shutकरोwn;
	ced->set_state_oneshot = mxc_set_oneshot;
	ced->tick_resume = mxc_shutकरोwn;
	ced->set_next_event = imxपंचांग->gpt->set_next_event;
	ced->rating = 200;
	ced->cpumask = cpumask_of(0);
	ced->irq = imxपंचांग->irq;
	घड़ीevents_config_and_रेजिस्टर(ced, clk_get_rate(imxपंचांग->clk_per),
					0xff, 0xfffffffe);

	वापस request_irq(imxपंचांग->irq, mxc_समयr_पूर्णांकerrupt,
			   IRQF_TIMER | IRQF_IRQPOLL, "i.MX Timer Tick", ced);
पूर्ण

अटल व्योम imx1_gpt_setup_tctl(काष्ठा imx_समयr *imxपंचांग)
अणु
	u32 tctl_val;

	tctl_val = MX1_2_TCTL_FRR | MX1_2_TCTL_CLK_PCLK1 | MXC_TCTL_TEN;
	ग_लिखोl_relaxed(tctl_val, imxपंचांग->base + MXC_TCTL);
पूर्ण
#घोषणा imx21_gpt_setup_tctl imx1_gpt_setup_tctl

अटल व्योम imx31_gpt_setup_tctl(काष्ठा imx_समयr *imxपंचांग)
अणु
	u32 tctl_val;

	tctl_val = V2_TCTL_FRR | V2_TCTL_WAITEN | MXC_TCTL_TEN;
	अगर (clk_get_rate(imxपंचांग->clk_per) == V2_TIMER_RATE_OSC_DIV8)
		tctl_val |= V2_TCTL_CLK_OSC_DIV8;
	अन्यथा
		tctl_val |= V2_TCTL_CLK_PER;

	ग_लिखोl_relaxed(tctl_val, imxपंचांग->base + MXC_TCTL);
पूर्ण

अटल व्योम imx6dl_gpt_setup_tctl(काष्ठा imx_समयr *imxपंचांग)
अणु
	u32 tctl_val;

	tctl_val = V2_TCTL_FRR | V2_TCTL_WAITEN | MXC_TCTL_TEN;
	अगर (clk_get_rate(imxपंचांग->clk_per) == V2_TIMER_RATE_OSC_DIV8) अणु
		tctl_val |= V2_TCTL_CLK_OSC_DIV8;
		/* 24 / 8 = 3 MHz */
		ग_लिखोl_relaxed(7 << V2_TPRER_PRE24M, imxपंचांग->base + MXC_TPRER);
		tctl_val |= V2_TCTL_24MEN;
	पूर्ण अन्यथा अणु
		tctl_val |= V2_TCTL_CLK_PER;
	पूर्ण

	ग_लिखोl_relaxed(tctl_val, imxपंचांग->base + MXC_TCTL);
पूर्ण

अटल स्थिर काष्ठा imx_gpt_data imx1_gpt_data = अणु
	.reg_tstat = MX1_2_TSTAT,
	.reg_tcn = MX1_2_TCN,
	.reg_tcmp = MX1_2_TCMP,
	.gpt_irq_enable = imx1_gpt_irq_enable,
	.gpt_irq_disable = imx1_gpt_irq_disable,
	.gpt_irq_acknowledge = imx1_gpt_irq_acknowledge,
	.gpt_setup_tctl = imx1_gpt_setup_tctl,
	.set_next_event = mx1_2_set_next_event,
पूर्ण;

अटल स्थिर काष्ठा imx_gpt_data imx21_gpt_data = अणु
	.reg_tstat = MX1_2_TSTAT,
	.reg_tcn = MX1_2_TCN,
	.reg_tcmp = MX1_2_TCMP,
	.gpt_irq_enable = imx21_gpt_irq_enable,
	.gpt_irq_disable = imx21_gpt_irq_disable,
	.gpt_irq_acknowledge = imx21_gpt_irq_acknowledge,
	.gpt_setup_tctl = imx21_gpt_setup_tctl,
	.set_next_event = mx1_2_set_next_event,
पूर्ण;

अटल स्थिर काष्ठा imx_gpt_data imx31_gpt_data = अणु
	.reg_tstat = V2_TSTAT,
	.reg_tcn = V2_TCN,
	.reg_tcmp = V2_TCMP,
	.gpt_irq_enable = imx31_gpt_irq_enable,
	.gpt_irq_disable = imx31_gpt_irq_disable,
	.gpt_irq_acknowledge = imx31_gpt_irq_acknowledge,
	.gpt_setup_tctl = imx31_gpt_setup_tctl,
	.set_next_event = v2_set_next_event,
पूर्ण;

अटल स्थिर काष्ठा imx_gpt_data imx6dl_gpt_data = अणु
	.reg_tstat = V2_TSTAT,
	.reg_tcn = V2_TCN,
	.reg_tcmp = V2_TCMP,
	.gpt_irq_enable = imx6dl_gpt_irq_enable,
	.gpt_irq_disable = imx6dl_gpt_irq_disable,
	.gpt_irq_acknowledge = imx6dl_gpt_irq_acknowledge,
	.gpt_setup_tctl = imx6dl_gpt_setup_tctl,
	.set_next_event = v2_set_next_event,
पूर्ण;

अटल पूर्णांक __init _mxc_समयr_init(काष्ठा imx_समयr *imxपंचांग)
अणु
	पूर्णांक ret;

	चयन (imxपंचांग->type) अणु
	हाल GPT_TYPE_IMX1:
		imxपंचांग->gpt = &imx1_gpt_data;
		अवरोध;
	हाल GPT_TYPE_IMX21:
		imxपंचांग->gpt = &imx21_gpt_data;
		अवरोध;
	हाल GPT_TYPE_IMX31:
		imxपंचांग->gpt = &imx31_gpt_data;
		अवरोध;
	हाल GPT_TYPE_IMX6DL:
		imxपंचांग->gpt = &imx6dl_gpt_data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(imxपंचांग->clk_per)) अणु
		pr_err("i.MX timer: unable to get clk\n");
		वापस PTR_ERR(imxपंचांग->clk_per);
	पूर्ण

	अगर (!IS_ERR(imxपंचांग->clk_ipg))
		clk_prepare_enable(imxपंचांग->clk_ipg);

	clk_prepare_enable(imxपंचांग->clk_per);

	/*
	 * Initialise to a known state (all समयrs off, and timing reset)
	 */

	ग_लिखोl_relaxed(0, imxपंचांग->base + MXC_TCTL);
	ग_लिखोl_relaxed(0, imxपंचांग->base + MXC_TPRER); /* see datasheet note */

	imxपंचांग->gpt->gpt_setup_tctl(imxपंचांग);

	/* init and रेजिस्टर the समयr to the framework */
	ret = mxc_घड़ीsource_init(imxपंचांग);
	अगर (ret)
		वापस ret;

	वापस mxc_घड़ीevent_init(imxपंचांग);
पूर्ण

व्योम __init mxc_समयr_init(अचिन्हित दीर्घ pbase, पूर्णांक irq, क्रमागत imx_gpt_type type)
अणु
	काष्ठा imx_समयr *imxपंचांग;

	imxपंचांग = kzalloc(माप(*imxपंचांग), GFP_KERNEL);
	BUG_ON(!imxपंचांग);

	imxपंचांग->clk_per = clk_get_sys("imx-gpt.0", "per");
	imxपंचांग->clk_ipg = clk_get_sys("imx-gpt.0", "ipg");

	imxपंचांग->base = ioremap(pbase, SZ_4K);
	BUG_ON(!imxपंचांग->base);

	imxपंचांग->type = type;
	imxपंचांग->irq = irq;

	_mxc_समयr_init(imxपंचांग);
पूर्ण

अटल पूर्णांक __init mxc_समयr_init_dt(काष्ठा device_node *np,  क्रमागत imx_gpt_type type)
अणु
	काष्ठा imx_समयr *imxपंचांग;
	अटल पूर्णांक initialized;
	पूर्णांक ret;

	/* Support one instance only */
	अगर (initialized)
		वापस 0;

	imxपंचांग = kzalloc(माप(*imxपंचांग), GFP_KERNEL);
	अगर (!imxपंचांग)
		वापस -ENOMEM;

	imxपंचांग->base = of_iomap(np, 0);
	अगर (!imxपंचांग->base)
		वापस -ENXIO;

	imxपंचांग->irq = irq_of_parse_and_map(np, 0);
	अगर (imxपंचांग->irq <= 0)
		वापस -EINVAL;

	imxपंचांग->clk_ipg = of_clk_get_by_name(np, "ipg");

	/* Try osc_per first, and fall back to per otherwise */
	imxपंचांग->clk_per = of_clk_get_by_name(np, "osc_per");
	अगर (IS_ERR(imxपंचांग->clk_per))
		imxपंचांग->clk_per = of_clk_get_by_name(np, "per");

	imxपंचांग->type = type;

	ret = _mxc_समयr_init(imxपंचांग);
	अगर (ret)
		वापस ret;

	initialized = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __init imx1_समयr_init_dt(काष्ठा device_node *np)
अणु
	वापस mxc_समयr_init_dt(np, GPT_TYPE_IMX1);
पूर्ण

अटल पूर्णांक __init imx21_समयr_init_dt(काष्ठा device_node *np)
अणु
	वापस mxc_समयr_init_dt(np, GPT_TYPE_IMX21);
पूर्ण

अटल पूर्णांक __init imx31_समयr_init_dt(काष्ठा device_node *np)
अणु
	क्रमागत imx_gpt_type type = GPT_TYPE_IMX31;

	/*
	 * We were using the same compatible string क्रम i.MX6Q/D and i.MX6DL/S
	 * GPT device, जबतक they actually have dअगरferent programming model.
	 * This is a workaround to keep the existing i.MX6DL/S DTBs जारी
	 * working with the new kernel.
	 */
	अगर (of_machine_is_compatible("fsl,imx6dl"))
		type = GPT_TYPE_IMX6DL;

	वापस mxc_समयr_init_dt(np, type);
पूर्ण

अटल पूर्णांक __init imx6dl_समयr_init_dt(काष्ठा device_node *np)
अणु
	वापस mxc_समयr_init_dt(np, GPT_TYPE_IMX6DL);
पूर्ण

TIMER_OF_DECLARE(imx1_समयr, "fsl,imx1-gpt", imx1_समयr_init_dt);
TIMER_OF_DECLARE(imx21_समयr, "fsl,imx21-gpt", imx21_समयr_init_dt);
TIMER_OF_DECLARE(imx27_समयr, "fsl,imx27-gpt", imx21_समयr_init_dt);
TIMER_OF_DECLARE(imx31_समयr, "fsl,imx31-gpt", imx31_समयr_init_dt);
TIMER_OF_DECLARE(imx25_समयr, "fsl,imx25-gpt", imx31_समयr_init_dt);
TIMER_OF_DECLARE(imx50_समयr, "fsl,imx50-gpt", imx31_समयr_init_dt);
TIMER_OF_DECLARE(imx51_समयr, "fsl,imx51-gpt", imx31_समयr_init_dt);
TIMER_OF_DECLARE(imx53_समयr, "fsl,imx53-gpt", imx31_समयr_init_dt);
TIMER_OF_DECLARE(imx6q_समयr, "fsl,imx6q-gpt", imx31_समयr_init_dt);
TIMER_OF_DECLARE(imx6dl_समयr, "fsl,imx6dl-gpt", imx6dl_समयr_init_dt);
TIMER_OF_DECLARE(imx6sl_समयr, "fsl,imx6sl-gpt", imx6dl_समयr_init_dt);
TIMER_OF_DECLARE(imx6sx_समयr, "fsl,imx6sx-gpt", imx6dl_समयr_init_dt);
