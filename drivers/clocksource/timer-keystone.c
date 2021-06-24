<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keystone broadcast घड़ी-event
 *
 * Copyright 2013 Texas Instruments, Inc.
 *
 * Author: Ivan Khoronzhuk <ivan.khoronzhuk@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा TIMER_NAME			"timer-keystone"

/* Timer रेजिस्टर offsets */
#घोषणा TIM12				0x10
#घोषणा TIM34				0x14
#घोषणा PRD12				0x18
#घोषणा PRD34				0x1c
#घोषणा TCR				0x20
#घोषणा TGCR				0x24
#घोषणा INTCTLSTAT			0x44

/* Timer रेजिस्टर bitfields */
#घोषणा TCR_ENAMODE_MASK		0xC0
#घोषणा TCR_ENAMODE_ONESHOT_MASK	0x40
#घोषणा TCR_ENAMODE_PERIODIC_MASK	0x80

#घोषणा TGCR_TIM_UNRESET_MASK		0x03
#घोषणा INTCTLSTAT_ENINT_MASK		0x01

/**
 * काष्ठा keystone_समयr: holds समयr's data
 * @base: समयr memory base address
 * @hz_period: cycles per HZ period
 * @event_dev: event device based on समयr
 */
अटल काष्ठा keystone_समयr अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ hz_period;
	काष्ठा घड़ी_event_device event_dev;
पूर्ण समयr;

अटल अंतरभूत u32 keystone_समयr_पढ़ोl(अचिन्हित दीर्घ rg)
अणु
	वापस पढ़ोl_relaxed(समयr.base + rg);
पूर्ण

अटल अंतरभूत व्योम keystone_समयr_ग_लिखोl(u32 val, अचिन्हित दीर्घ rg)
अणु
	ग_लिखोl_relaxed(val, समयr.base + rg);
पूर्ण

/**
 * keystone_समयr_barrier: ग_लिखो memory barrier
 * use explicit barrier to aव्योम using पढ़ोl/ग_लिखोl non relaxed function
 * variants, because in our हाल non relaxed variants hide the true places
 * where barrier is needed.
 */
अटल अंतरभूत व्योम keystone_समयr_barrier(व्योम)
अणु
	__iowmb();
पूर्ण

/**
 * keystone_समयr_config: configures समयr to work in oneshot/periodic modes.
 * @ mask: mask of the mode to configure
 * @ period: cycles number to configure क्रम
 */
अटल पूर्णांक keystone_समयr_config(u64 period, पूर्णांक mask)
अणु
	u32 tcr;
	u32 off;

	tcr = keystone_समयr_पढ़ोl(TCR);
	off = tcr & ~(TCR_ENAMODE_MASK);

	/* set enable mode */
	tcr |= mask;

	/* disable समयr */
	keystone_समयr_ग_लिखोl(off, TCR);
	/* here we have to be sure the समयr has been disabled */
	keystone_समयr_barrier();

	/* reset counter to zero, set new period */
	keystone_समयr_ग_लिखोl(0, TIM12);
	keystone_समयr_ग_लिखोl(0, TIM34);
	keystone_समयr_ग_लिखोl(period & 0xffffffff, PRD12);
	keystone_समयr_ग_लिखोl(period >> 32, PRD34);

	/*
	 * enable समयr
	 * here we have to be sure that CNTLO, CNTHI, PRDLO, PRDHI रेजिस्टरs
	 * have been written.
	 */
	keystone_समयr_barrier();
	keystone_समयr_ग_लिखोl(tcr, TCR);
	वापस 0;
पूर्ण

अटल व्योम keystone_समयr_disable(व्योम)
अणु
	u32 tcr;

	tcr = keystone_समयr_पढ़ोl(TCR);

	/* disable समयr */
	tcr &= ~(TCR_ENAMODE_MASK);
	keystone_समयr_ग_लिखोl(tcr, TCR);
पूर्ण

अटल irqवापस_t keystone_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक keystone_set_next_event(अचिन्हित दीर्घ cycles,
				  काष्ठा घड़ी_event_device *evt)
अणु
	वापस keystone_समयr_config(cycles, TCR_ENAMODE_ONESHOT_MASK);
पूर्ण

अटल पूर्णांक keystone_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	keystone_समयr_disable();
	वापस 0;
पूर्ण

अटल पूर्णांक keystone_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	keystone_समयr_config(समयr.hz_period, TCR_ENAMODE_PERIODIC_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक __init keystone_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा घड़ी_event_device *event_dev = &समयr.event_dev;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक irq, error;

	irq  = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		pr_err("%s: failed to map interrupts\n", __func__);
		वापस -EINVAL;
	पूर्ण

	समयr.base = of_iomap(np, 0);
	अगर (!समयr.base) अणु
		pr_err("%s: failed to map registers\n", __func__);
		वापस -ENXIO;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to get clock\n", __func__);
		iounmap(समयr.base);
		वापस PTR_ERR(clk);
	पूर्ण

	error = clk_prepare_enable(clk);
	अगर (error) अणु
		pr_err("%s: failed to enable clock\n", __func__);
		जाओ err;
	पूर्ण

	rate = clk_get_rate(clk);

	/* disable, use पूर्णांकernal घड़ी source */
	keystone_समयr_ग_लिखोl(0, TCR);
	/* here we have to be sure the समयr has been disabled */
	keystone_समयr_barrier();

	/* reset समयr as 64-bit, no pre-scaler, plus features are disabled */
	keystone_समयr_ग_लिखोl(0, TGCR);

	/* unreset समयr */
	keystone_समयr_ग_लिखोl(TGCR_TIM_UNRESET_MASK, TGCR);

	/* init counter to zero */
	keystone_समयr_ग_लिखोl(0, TIM12);
	keystone_समयr_ग_लिखोl(0, TIM34);

	समयr.hz_period = DIV_ROUND_UP(rate, HZ);

	/* enable समयr पूर्णांकerrupts */
	keystone_समयr_ग_लिखोl(INTCTLSTAT_ENINT_MASK, INTCTLSTAT);

	error = request_irq(irq, keystone_समयr_पूर्णांकerrupt, IRQF_TIMER,
			    TIMER_NAME, event_dev);
	अगर (error) अणु
		pr_err("%s: failed to setup irq\n", __func__);
		जाओ err;
	पूर्ण

	/* setup घड़ीevent */
	event_dev->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	event_dev->set_next_event = keystone_set_next_event;
	event_dev->set_state_shutकरोwn = keystone_shutकरोwn;
	event_dev->set_state_periodic = keystone_set_periodic;
	event_dev->set_state_oneshot = keystone_shutकरोwn;
	event_dev->cpumask = cpu_possible_mask;
	event_dev->owner = THIS_MODULE;
	event_dev->name = TIMER_NAME;
	event_dev->irq = irq;

	घड़ीevents_config_and_रेजिस्टर(event_dev, rate, 1, अच_दीर्घ_उच्च);

	pr_info("keystone timer clock @%lu Hz\n", rate);
	वापस 0;
err:
	clk_put(clk);
	iounmap(समयr.base);
	वापस error;
पूर्ण

TIMER_OF_DECLARE(keystone_समयr, "ti,keystone-timer",
			   keystone_समयr_init);
