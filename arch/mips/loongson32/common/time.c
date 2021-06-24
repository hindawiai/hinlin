<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/समय.स>

#समावेश <loongson1.h>
#समावेश <platक्रमm.h>

#अगर_घोषित CONFIG_CEVT_CSRC_LS1X

#अगर defined(CONFIG_TIMER_USE_PWM1)
#घोषणा LS1X_TIMER_BASE	LS1X_PWM1_BASE
#घोषणा LS1X_TIMER_IRQ	LS1X_PWM1_IRQ

#या_अगर defined(CONFIG_TIMER_USE_PWM2)
#घोषणा LS1X_TIMER_BASE	LS1X_PWM2_BASE
#घोषणा LS1X_TIMER_IRQ	LS1X_PWM2_IRQ

#या_अगर defined(CONFIG_TIMER_USE_PWM3)
#घोषणा LS1X_TIMER_BASE	LS1X_PWM3_BASE
#घोषणा LS1X_TIMER_IRQ	LS1X_PWM3_IRQ

#अन्यथा
#घोषणा LS1X_TIMER_BASE	LS1X_PWM0_BASE
#घोषणा LS1X_TIMER_IRQ	LS1X_PWM0_IRQ
#पूर्ण_अगर

DEFINE_RAW_SPINLOCK(ls1x_समयr_lock);

अटल व्योम __iomem *समयr_reg_base;
अटल uपूर्णांक32_t ls1x_jअगरfies_per_tick;

अटल अंतरभूत व्योम ls1x_pwmसमयr_set_period(uपूर्णांक32_t period)
अणु
	__raw_ग_लिखोl(period, समयr_reg_base + PWM_HRC);
	__raw_ग_लिखोl(period, समयr_reg_base + PWM_LRC);
पूर्ण

अटल अंतरभूत व्योम ls1x_pwmसमयr_restart(व्योम)
अणु
	__raw_ग_लिखोl(0x0, समयr_reg_base + PWM_CNT);
	__raw_ग_लिखोl(INT_EN | CNT_EN, समयr_reg_base + PWM_CTRL);
पूर्ण

व्योम __init ls1x_pwmसमयr_init(व्योम)
अणु
	समयr_reg_base = ioremap(LS1X_TIMER_BASE, SZ_16);
	अगर (!समयr_reg_base)
		panic("Failed to remap timer registers");

	ls1x_jअगरfies_per_tick = DIV_ROUND_CLOSEST(mips_hpt_frequency, HZ);

	ls1x_pwmसमयr_set_period(ls1x_jअगरfies_per_tick);
	ls1x_pwmसमयr_restart();
पूर्ण

अटल u64 ls1x_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	u32 jअगरs;
	अटल पूर्णांक old_count;
	अटल u32 old_jअगरs;

	raw_spin_lock_irqsave(&ls1x_समयr_lock, flags);
	/*
	 * Although our caller may have the पढ़ो side of xसमय_lock,
	 * this is now a seqlock, and we are cheating in this routine
	 * by having side effects on state that we cannot unकरो अगर
	 * there is a collision on the seqlock and our caller has to
	 * retry.  (Namely, old_jअगरs and old_count.)  So we must treat
	 * jअगरfies as अस्थिर despite the lock.  We पढ़ो jअगरfies
	 * beक्रमe latching the समयr count to guarantee that although
	 * the jअगरfies value might be older than the count (that is,
	 * the counter may underflow between the last poपूर्णांक where
	 * jअगरfies was incremented and the poपूर्णांक where we latch the
	 * count), it cannot be newer.
	 */
	jअगरs = jअगरfies;
	/* पढ़ो the count */
	count = __raw_पढ़ोl(समयr_reg_base + PWM_CNT);

	/*
	 * It's possible क्रम count to appear to go the wrong way क्रम this
	 * reason:
	 *
	 *  The समयr counter underflows, but we haven't handled the resulting
	 *  पूर्णांकerrupt and incremented jअगरfies yet.
	 *
	 * Previous attempts to handle these हालs पूर्णांकelligently were buggy, so
	 * we just करो the simple thing now.
	 */
	अगर (count < old_count && jअगरs == old_jअगरs)
		count = old_count;

	old_count = count;
	old_jअगरs = jअगरs;

	raw_spin_unlock_irqrestore(&ls1x_समयr_lock, flags);

	वापस (u64) (jअगरs * ls1x_jअगरfies_per_tick) + count;
पूर्ण

अटल काष्ठा घड़ीsource ls1x_घड़ीsource = अणु
	.name		= "ls1x-pwmtimer",
	.पढ़ो		= ls1x_घड़ीsource_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(24),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल irqवापस_t ls1x_घड़ीevent_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा घड़ी_event_device *cd = devid;

	ls1x_pwmसमयr_restart();
	cd->event_handler(cd);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ls1x_घड़ीevent_set_state_periodic(काष्ठा घड़ी_event_device *cd)
अणु
	raw_spin_lock(&ls1x_समयr_lock);
	ls1x_pwmसमयr_set_period(ls1x_jअगरfies_per_tick);
	ls1x_pwmसमयr_restart();
	__raw_ग_लिखोl(INT_EN | CNT_EN, समयr_reg_base + PWM_CTRL);
	raw_spin_unlock(&ls1x_समयr_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_घड़ीevent_tick_resume(काष्ठा घड़ी_event_device *cd)
अणु
	raw_spin_lock(&ls1x_समयr_lock);
	__raw_ग_लिखोl(INT_EN | CNT_EN, समयr_reg_base + PWM_CTRL);
	raw_spin_unlock(&ls1x_समयr_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_घड़ीevent_set_state_shutकरोwn(काष्ठा घड़ी_event_device *cd)
अणु
	raw_spin_lock(&ls1x_समयr_lock);
	__raw_ग_लिखोl(__raw_पढ़ोl(समयr_reg_base + PWM_CTRL) & ~CNT_EN,
		     समयr_reg_base + PWM_CTRL);
	raw_spin_unlock(&ls1x_समयr_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_घड़ीevent_set_next(अचिन्हित दीर्घ evt,
				    काष्ठा घड़ी_event_device *cd)
अणु
	raw_spin_lock(&ls1x_समयr_lock);
	ls1x_pwmसमयr_set_period(evt);
	ls1x_pwmसमयr_restart();
	raw_spin_unlock(&ls1x_समयr_lock);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device ls1x_घड़ीevent = अणु
	.name			= "ls1x-pwmtimer",
	.features		= CLOCK_EVT_FEAT_PERIODIC,
	.rating			= 300,
	.irq			= LS1X_TIMER_IRQ,
	.set_next_event		= ls1x_घड़ीevent_set_next,
	.set_state_shutकरोwn	= ls1x_घड़ीevent_set_state_shutकरोwn,
	.set_state_periodic	= ls1x_घड़ीevent_set_state_periodic,
	.set_state_oneshot	= ls1x_घड़ीevent_set_state_shutकरोwn,
	.tick_resume		= ls1x_घड़ीevent_tick_resume,
पूर्ण;

अटल व्योम __init ls1x_समय_init(व्योम)
अणु
	काष्ठा घड़ी_event_device *cd = &ls1x_घड़ीevent;
	पूर्णांक ret;

	अगर (!mips_hpt_frequency)
		panic("Invalid timer clock rate");

	ls1x_pwmसमयr_init();

	घड़ीevent_set_घड़ी(cd, mips_hpt_frequency);
	cd->max_delta_ns = घड़ीevent_delta2ns(0xffffff, cd);
	cd->max_delta_ticks = 0xffffff;
	cd->min_delta_ns = घड़ीevent_delta2ns(0x000300, cd);
	cd->min_delta_ticks = 0x000300;
	cd->cpumask = cpumask_of(smp_processor_id());
	घड़ीevents_रेजिस्टर_device(cd);

	ls1x_घड़ीsource.rating = 200 + mips_hpt_frequency / 10000000;
	ret = घड़ीsource_रेजिस्टर_hz(&ls1x_घड़ीsource, mips_hpt_frequency);
	अगर (ret)
		panic(KERN_ERR "Failed to register clocksource: %d\n", ret);

	अगर (request_irq(LS1X_TIMER_IRQ, ls1x_घड़ीevent_isr,
			IRQF_PERCPU | IRQF_TIMER, "ls1x-pwmtimer",
			&ls1x_घड़ीevent))
		pr_err("Failed to register ls1x-pwmtimer interrupt\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_CEVT_CSRC_LS1X */

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा clk *clk = शून्य;

	/* initialize LS1X घड़ीs */
	ls1x_clk_init();

#अगर_घोषित CONFIG_CEVT_CSRC_LS1X
	/* setup LS1X PWM समयr */
	clk = clk_get(शून्य, "ls1x-pwmtimer");
	अगर (IS_ERR(clk))
		panic("unable to get timer clock, err=%ld", PTR_ERR(clk));

	mips_hpt_frequency = clk_get_rate(clk);
	ls1x_समय_init();
#अन्यथा
	/* setup mips r4k समयr */
	clk = clk_get(शून्य, "cpu_clk");
	अगर (IS_ERR(clk))
		panic("unable to get cpu clock, err=%ld", PTR_ERR(clk));

	mips_hpt_frequency = clk_get_rate(clk) / 2;
#पूर्ण_अगर /* CONFIG_CEVT_CSRC_LS1X */
पूर्ण
