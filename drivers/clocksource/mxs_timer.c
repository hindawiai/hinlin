<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
//  Copyright (C) 2000-2001 Deep Blue Solutions
//  Copyright (C) 2002 Shane Nay (shane@minirl.com)
//  Copyright (C) 2006-2007 Pavel Pisa (ppisa@pikron.com)
//  Copyright (C) 2008 Juergen Beisert (kernel@pengutronix.de)
//  Copyright (C) 2010 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/sched_घड़ी.h>

/*
 * There are 2 versions of the timrot on Freescale MXS-based SoCs.
 * The v1 on MX23 only माला_लो 16 bits counter, जबतक v2 on MX28
 * extends the counter to 32 bits.
 *
 * The implementation uses two समयrs, one क्रम घड़ी_event and
 * another क्रम घड़ीsource. MX28 uses timrot 0 and 1, जबतक MX23
 * uses 0 and 2.
 */

#घोषणा MX23_TIMROT_VERSION_OFFSET	0x0a0
#घोषणा MX28_TIMROT_VERSION_OFFSET	0x120
#घोषणा BP_TIMROT_MAJOR_VERSION		24
#घोषणा BV_TIMROT_VERSION_1		0x01
#घोषणा BV_TIMROT_VERSION_2		0x02
#घोषणा timrot_is_v1()	(timrot_major_version == BV_TIMROT_VERSION_1)

/*
 * There are 4 रेजिस्टरs क्रम each timrotv2 instance, and 2 रेजिस्टरs
 * क्रम each timrotv1. So address step 0x40 in macros below strides
 * one instance of timrotv2 जबतक two instances of timrotv1.
 *
 * As the result, HW_TIMROT_XXXn(1) defines the address of timrot1
 * on MX28 जबतक timrot2 on MX23.
 */
/* common between v1 and v2 */
#घोषणा HW_TIMROT_ROTCTRL		0x00
#घोषणा HW_TIMROT_TIMCTRLn(n)		(0x20 + (n) * 0x40)
/* v1 only */
#घोषणा HW_TIMROT_TIMCOUNTn(n)		(0x30 + (n) * 0x40)
/* v2 only */
#घोषणा HW_TIMROT_RUNNING_COUNTn(n)	(0x30 + (n) * 0x40)
#घोषणा HW_TIMROT_FIXED_COUNTn(n)	(0x40 + (n) * 0x40)

#घोषणा BM_TIMROT_TIMCTRLn_RELOAD	(1 << 6)
#घोषणा BM_TIMROT_TIMCTRLn_UPDATE	(1 << 7)
#घोषणा BM_TIMROT_TIMCTRLn_IRQ_EN	(1 << 14)
#घोषणा BM_TIMROT_TIMCTRLn_IRQ		(1 << 15)
#घोषणा BP_TIMROT_TIMCTRLn_SELECT	0
#घोषणा BV_TIMROTv1_TIMCTRLn_SELECT__32KHZ_XTAL		0x8
#घोषणा BV_TIMROTv2_TIMCTRLn_SELECT__32KHZ_XTAL		0xb
#घोषणा BV_TIMROTv2_TIMCTRLn_SELECT__TICK_ALWAYS	0xf

अटल काष्ठा घड़ी_event_device mxs_घड़ीevent_device;

अटल व्योम __iomem *mxs_timrot_base;
अटल u32 timrot_major_version;

अटल अंतरभूत व्योम timrot_irq_disable(व्योम)
अणु
	__raw_ग_लिखोl(BM_TIMROT_TIMCTRLn_IRQ_EN, mxs_timrot_base +
		     HW_TIMROT_TIMCTRLn(0) + STMP_OFFSET_REG_CLR);
पूर्ण

अटल अंतरभूत व्योम timrot_irq_enable(व्योम)
अणु
	__raw_ग_लिखोl(BM_TIMROT_TIMCTRLn_IRQ_EN, mxs_timrot_base +
		     HW_TIMROT_TIMCTRLn(0) + STMP_OFFSET_REG_SET);
पूर्ण

अटल व्योम timrot_irq_acknowledge(व्योम)
अणु
	__raw_ग_लिखोl(BM_TIMROT_TIMCTRLn_IRQ, mxs_timrot_base +
		     HW_TIMROT_TIMCTRLn(0) + STMP_OFFSET_REG_CLR);
पूर्ण

अटल u64 timrotv1_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	वापस ~((__raw_पढ़ोl(mxs_timrot_base + HW_TIMROT_TIMCOUNTn(1))
			& 0xffff0000) >> 16);
पूर्ण

अटल पूर्णांक timrotv1_set_next_event(अचिन्हित दीर्घ evt,
					काष्ठा घड़ी_event_device *dev)
अणु
	/* timrot decrements the count */
	__raw_ग_लिखोl(evt, mxs_timrot_base + HW_TIMROT_TIMCOUNTn(0));

	वापस 0;
पूर्ण

अटल पूर्णांक timrotv2_set_next_event(अचिन्हित दीर्घ evt,
					काष्ठा घड़ी_event_device *dev)
अणु
	/* timrot decrements the count */
	__raw_ग_लिखोl(evt, mxs_timrot_base + HW_TIMROT_FIXED_COUNTn(0));

	वापस 0;
पूर्ण

अटल irqवापस_t mxs_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	timrot_irq_acknowledge();
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mxs_irq_clear(अक्षर *state)
अणु
	/* Disable पूर्णांकerrupt in समयr module */
	timrot_irq_disable();

	/* Set event समय पूर्णांकo the furthest future */
	अगर (timrot_is_v1())
		__raw_ग_लिखोl(0xffff, mxs_timrot_base + HW_TIMROT_TIMCOUNTn(1));
	अन्यथा
		__raw_ग_लिखोl(0xffffffff,
			     mxs_timrot_base + HW_TIMROT_FIXED_COUNTn(1));

	/* Clear pending पूर्णांकerrupt */
	timrot_irq_acknowledge();
	pr_debug("%s: changing mode to %s\n", __func__, state);
पूर्ण

अटल पूर्णांक mxs_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	mxs_irq_clear("shutdown");

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	अगर (घड़ीevent_state_oneshot(evt))
		mxs_irq_clear("oneshot");
	timrot_irq_enable();
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device mxs_घड़ीevent_device = अणु
	.name			= "mxs_timrot",
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= mxs_shutकरोwn,
	.set_state_oneshot	= mxs_set_oneshot,
	.tick_resume		= mxs_shutकरोwn,
	.set_next_event		= timrotv2_set_next_event,
	.rating			= 200,
पूर्ण;

अटल पूर्णांक __init mxs_घड़ीevent_init(काष्ठा clk *समयr_clk)
अणु
	अगर (timrot_is_v1())
		mxs_घड़ीevent_device.set_next_event = timrotv1_set_next_event;
	mxs_घड़ीevent_device.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&mxs_घड़ीevent_device,
					clk_get_rate(समयr_clk),
					timrot_is_v1() ? 0xf : 0x2,
					timrot_is_v1() ? 0xfffe : 0xfffffffe);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_mxs = अणु
	.name		= "mxs_timer",
	.rating		= 200,
	.पढ़ो		= timrotv1_get_cycles,
	.mask		= CLOCKSOURCE_MASK(16),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u64 notrace mxs_पढ़ो_sched_घड़ी_v2(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(mxs_timrot_base + HW_TIMROT_RUNNING_COUNTn(1));
पूर्ण

अटल पूर्णांक __init mxs_घड़ीsource_init(काष्ठा clk *समयr_clk)
अणु
	अचिन्हित पूर्णांक c = clk_get_rate(समयr_clk);

	अगर (timrot_is_v1())
		घड़ीsource_रेजिस्टर_hz(&घड़ीsource_mxs, c);
	अन्यथा अणु
		घड़ीsource_mmio_init(mxs_timrot_base + HW_TIMROT_RUNNING_COUNTn(1),
			"mxs_timer", c, 200, 32, घड़ीsource_mmio_पढ़ोl_करोwn);
		sched_घड़ी_रेजिस्टर(mxs_पढ़ो_sched_घड़ी_v2, 32, c);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init mxs_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *समयr_clk;
	पूर्णांक irq, ret;

	mxs_timrot_base = of_iomap(np, 0);
	WARN_ON(!mxs_timrot_base);

	समयr_clk = of_clk_get(np, 0);
	अगर (IS_ERR(समयr_clk)) अणु
		pr_err("%s: failed to get clk\n", __func__);
		वापस PTR_ERR(समयr_clk);
	पूर्ण

	ret = clk_prepare_enable(समयr_clk);
	अगर (ret)
		वापस ret;

	/*
	 * Initialize समयrs to a known state
	 */
	sपंचांगp_reset_block(mxs_timrot_base + HW_TIMROT_ROTCTRL);

	/* get timrot version */
	timrot_major_version = __raw_पढ़ोl(mxs_timrot_base +
			(of_device_is_compatible(np, "fsl,imx23-timrot") ?
						MX23_TIMROT_VERSION_OFFSET :
						MX28_TIMROT_VERSION_OFFSET));
	timrot_major_version >>= BP_TIMROT_MAJOR_VERSION;

	/* one क्रम घड़ी_event */
	__raw_ग_लिखोl((timrot_is_v1() ?
			BV_TIMROTv1_TIMCTRLn_SELECT__32KHZ_XTAL :
			BV_TIMROTv2_TIMCTRLn_SELECT__TICK_ALWAYS) |
			BM_TIMROT_TIMCTRLn_UPDATE |
			BM_TIMROT_TIMCTRLn_IRQ_EN,
			mxs_timrot_base + HW_TIMROT_TIMCTRLn(0));

	/* another क्रम घड़ीsource */
	__raw_ग_लिखोl((timrot_is_v1() ?
			BV_TIMROTv1_TIMCTRLn_SELECT__32KHZ_XTAL :
			BV_TIMROTv2_TIMCTRLn_SELECT__TICK_ALWAYS) |
			BM_TIMROT_TIMCTRLn_RELOAD,
			mxs_timrot_base + HW_TIMROT_TIMCTRLn(1));

	/* set घड़ीsource समयr fixed count to the maximum */
	अगर (timrot_is_v1())
		__raw_ग_लिखोl(0xffff,
			mxs_timrot_base + HW_TIMROT_TIMCOUNTn(1));
	अन्यथा
		__raw_ग_लिखोl(0xffffffff,
			mxs_timrot_base + HW_TIMROT_FIXED_COUNTn(1));

	/* init and रेजिस्टर the समयr to the framework */
	ret = mxs_घड़ीsource_init(समयr_clk);
	अगर (ret)
		वापस ret;

	ret = mxs_घड़ीevent_init(समयr_clk);
	अगर (ret)
		वापस ret;

	/* Make irqs happen */
	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0)
		वापस -EINVAL;

	वापस request_irq(irq, mxs_समयr_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			   "MXS Timer Tick", &mxs_घड़ीevent_device);
पूर्ण
TIMER_OF_DECLARE(mxs, "fsl,timrot", mxs_समयr_init);
