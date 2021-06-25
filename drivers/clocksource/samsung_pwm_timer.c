<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * samsung - Common hr-समयr support (s3c and s5p)
*/

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <घड़ीsource/samsung_pwm.h>


/*
 * Clocksource driver
 */

#घोषणा REG_TCFG0			0x00
#घोषणा REG_TCFG1			0x04
#घोषणा REG_TCON			0x08
#घोषणा REG_TINT_CSTAT			0x44

#घोषणा REG_TCNTB(chan)			(0x0c + 12 * (chan))
#घोषणा REG_TCMPB(chan)			(0x10 + 12 * (chan))

#घोषणा TCFG0_PRESCALER_MASK		0xff
#घोषणा TCFG0_PRESCALER1_SHIFT		8

#घोषणा TCFG1_SHIFT(x)	  		((x) * 4)
#घोषणा TCFG1_MUX_MASK	  		0xf

/*
 * Each channel occupies 4 bits in TCON रेजिस्टर, but there is a gap of 4
 * bits (one channel) after channel 0, so channels have dअगरferent numbering
 * when accessing TCON रेजिस्टर.
 *
 * In addition, the location of स्वतःreload bit क्रम channel 4 (TCON channel 5)
 * in its set of bits is 2 as opposed to 3 क्रम other channels.
 */
#घोषणा TCON_START(chan)		(1 << (4 * (chan) + 0))
#घोषणा TCON_MANUALUPDATE(chan)		(1 << (4 * (chan) + 1))
#घोषणा TCON_INVERT(chan)		(1 << (4 * (chan) + 2))
#घोषणा _TCON_AUTORELOAD(chan)		(1 << (4 * (chan) + 3))
#घोषणा _TCON_AUTORELOAD4(chan)		(1 << (4 * (chan) + 2))
#घोषणा TCON_AUTORELOAD(chan)		\
	((chan < 5) ? _TCON_AUTORELOAD(chan) : _TCON_AUTORELOAD4(chan))

DEFINE_SPINLOCK(samsung_pwm_lock);
EXPORT_SYMBOL(samsung_pwm_lock);

काष्ठा samsung_pwm_घड़ीsource अणु
	व्योम __iomem *base;
	व्योम __iomem *source_reg;
	अचिन्हित पूर्णांक irq[SAMSUNG_PWM_NUM];
	काष्ठा samsung_pwm_variant variant;

	काष्ठा clk *समयrclk;

	अचिन्हित पूर्णांक event_id;
	अचिन्हित पूर्णांक source_id;
	अचिन्हित पूर्णांक tcnt_max;
	अचिन्हित पूर्णांक tscaler_भाग;
	अचिन्हित पूर्णांक tभाग;

	अचिन्हित दीर्घ घड़ी_count_per_tick;
पूर्ण;

अटल काष्ठा samsung_pwm_घड़ीsource pwm;

अटल व्योम samsung_समयr_set_prescale(अचिन्हित पूर्णांक channel, u16 prescale)
अणु
	अचिन्हित दीर्घ flags;
	u8 shअगरt = 0;
	u32 reg;

	अगर (channel >= 2)
		shअगरt = TCFG0_PRESCALER1_SHIFT;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	reg = पढ़ोl(pwm.base + REG_TCFG0);
	reg &= ~(TCFG0_PRESCALER_MASK << shअगरt);
	reg |= (prescale - 1) << shअगरt;
	ग_लिखोl(reg, pwm.base + REG_TCFG0);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल व्योम samsung_समयr_set_भागisor(अचिन्हित पूर्णांक channel, u8 भागisor)
अणु
	u8 shअगरt = TCFG1_SHIFT(channel);
	अचिन्हित दीर्घ flags;
	u32 reg;
	u8 bits;

	bits = (fls(भागisor) - 1) - pwm.variant.भाग_base;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	reg = पढ़ोl(pwm.base + REG_TCFG1);
	reg &= ~(TCFG1_MUX_MASK << shअगरt);
	reg |= bits << shअगरt;
	ग_लिखोl(reg, pwm.base + REG_TCFG1);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल व्योम samsung_समय_stop(अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित दीर्घ tcon;
	अचिन्हित दीर्घ flags;

	अगर (channel > 0)
		++channel;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl_relaxed(pwm.base + REG_TCON);
	tcon &= ~TCON_START(channel);
	ग_लिखोl_relaxed(tcon, pwm.base + REG_TCON);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल व्योम samsung_समय_setup(अचिन्हित पूर्णांक channel, अचिन्हित दीर्घ tcnt)
अणु
	अचिन्हित दीर्घ tcon;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक tcon_chan = channel;

	अगर (tcon_chan > 0)
		++tcon_chan;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl_relaxed(pwm.base + REG_TCON);

	tcon &= ~(TCON_START(tcon_chan) | TCON_AUTORELOAD(tcon_chan));
	tcon |= TCON_MANUALUPDATE(tcon_chan);

	ग_लिखोl_relaxed(tcnt, pwm.base + REG_TCNTB(channel));
	ग_लिखोl_relaxed(tcnt, pwm.base + REG_TCMPB(channel));
	ग_लिखोl_relaxed(tcon, pwm.base + REG_TCON);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल व्योम samsung_समय_start(अचिन्हित पूर्णांक channel, bool periodic)
अणु
	अचिन्हित दीर्घ tcon;
	अचिन्हित दीर्घ flags;

	अगर (channel > 0)
		++channel;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl_relaxed(pwm.base + REG_TCON);

	tcon &= ~TCON_MANUALUPDATE(channel);
	tcon |= TCON_START(channel);

	अगर (periodic)
		tcon |= TCON_AUTORELOAD(channel);
	अन्यथा
		tcon &= ~TCON_AUTORELOAD(channel);

	ग_लिखोl_relaxed(tcon, pwm.base + REG_TCON);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल पूर्णांक samsung_set_next_event(अचिन्हित दीर्घ cycles,
				काष्ठा घड़ी_event_device *evt)
अणु
	/*
	 * This check is needed to account क्रम पूर्णांकernal rounding
	 * errors inside घड़ीevents core, which might result in
	 * passing cycles = 0, which in turn would not generate any
	 * समयr पूर्णांकerrupt and hang the प्रणाली.
	 *
	 * Another solution would be to set up the घड़ीevent device
	 * with min_delta = 2, but this would unnecessarily increase
	 * the minimum sleep period.
	 */
	अगर (!cycles)
		cycles = 1;

	samsung_समय_setup(pwm.event_id, cycles);
	samsung_समय_start(pwm.event_id, false);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	samsung_समय_stop(pwm.event_id);
	वापस 0;
पूर्ण

अटल पूर्णांक samsung_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	samsung_समय_stop(pwm.event_id);
	samsung_समय_setup(pwm.event_id, pwm.घड़ी_count_per_tick - 1);
	samsung_समय_start(pwm.event_id, true);
	वापस 0;
पूर्ण

अटल व्योम samsung_घड़ीevent_resume(काष्ठा घड़ी_event_device *cev)
अणु
	samsung_समयr_set_prescale(pwm.event_id, pwm.tscaler_भाग);
	samsung_समयr_set_भागisor(pwm.event_id, pwm.tभाग);

	अगर (pwm.variant.has_tपूर्णांक_cstat) अणु
		u32 mask = (1 << pwm.event_id);
		ग_लिखोl(mask | (mask << 5), pwm.base + REG_TINT_CSTAT);
	पूर्ण
पूर्ण

अटल काष्ठा घड़ी_event_device समय_event_device = अणु
	.name			= "samsung_event_timer",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 200,
	.set_next_event		= samsung_set_next_event,
	.set_state_shutकरोwn	= samsung_shutकरोwn,
	.set_state_periodic	= samsung_set_periodic,
	.set_state_oneshot	= samsung_shutकरोwn,
	.tick_resume		= samsung_shutकरोwn,
	.resume			= samsung_घड़ीevent_resume,
पूर्ण;

अटल irqवापस_t samsung_घड़ी_event_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	अगर (pwm.variant.has_tपूर्णांक_cstat) अणु
		u32 mask = (1 << pwm.event_id);
		ग_लिखोl(mask | (mask << 5), pwm.base + REG_TINT_CSTAT);
	पूर्ण

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init samsung_घड़ीevent_init(व्योम)
अणु
	अचिन्हित दीर्घ pclk;
	अचिन्हित दीर्घ घड़ी_rate;
	अचिन्हित पूर्णांक irq_number;

	pclk = clk_get_rate(pwm.समयrclk);

	samsung_समयr_set_prescale(pwm.event_id, pwm.tscaler_भाग);
	samsung_समयr_set_भागisor(pwm.event_id, pwm.tभाग);

	घड़ी_rate = pclk / (pwm.tscaler_भाग * pwm.tभाग);
	pwm.घड़ी_count_per_tick = घड़ी_rate / HZ;

	समय_event_device.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&समय_event_device,
						घड़ी_rate, 1, pwm.tcnt_max);

	irq_number = pwm.irq[pwm.event_id];
	अगर (request_irq(irq_number, samsung_घड़ी_event_isr,
			IRQF_TIMER | IRQF_IRQPOLL, "samsung_time_irq",
			&समय_event_device))
		pr_err("%s: request_irq() failed\n", "samsung_time_irq");

	अगर (pwm.variant.has_tपूर्णांक_cstat) अणु
		u32 mask = (1 << pwm.event_id);
		ग_लिखोl(mask | (mask << 5), pwm.base + REG_TINT_CSTAT);
	पूर्ण
पूर्ण

अटल व्योम samsung_घड़ीsource_suspend(काष्ठा घड़ीsource *cs)
अणु
	samsung_समय_stop(pwm.source_id);
पूर्ण

अटल व्योम samsung_घड़ीsource_resume(काष्ठा घड़ीsource *cs)
अणु
	samsung_समयr_set_prescale(pwm.source_id, pwm.tscaler_भाग);
	samsung_समयr_set_भागisor(pwm.source_id, pwm.tभाग);

	samsung_समय_setup(pwm.source_id, pwm.tcnt_max);
	samsung_समय_start(pwm.source_id, true);
पूर्ण

अटल u64 notrace samsung_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *c)
अणु
	वापस ~पढ़ोl_relaxed(pwm.source_reg);
पूर्ण

अटल काष्ठा घड़ीsource samsung_घड़ीsource = अणु
	.name		= "samsung_clocksource_timer",
	.rating		= 250,
	.पढ़ो		= samsung_घड़ीsource_पढ़ो,
	.suspend	= samsung_घड़ीsource_suspend,
	.resume		= samsung_घड़ीsource_resume,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

/*
 * Override the global weak sched_घड़ी symbol with this
 * local implementation which uses the घड़ीsource to get some
 * better resolution when scheduling the kernel. We accept that
 * this wraps around क्रम now, since it is just a relative समय
 * stamp. (Inspired by U300 implementation.)
 */
अटल u64 notrace samsung_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस samsung_घड़ीsource_पढ़ो(शून्य);
पूर्ण

अटल पूर्णांक __init samsung_घड़ीsource_init(व्योम)
अणु
	अचिन्हित दीर्घ pclk;
	अचिन्हित दीर्घ घड़ी_rate;

	pclk = clk_get_rate(pwm.समयrclk);

	samsung_समयr_set_prescale(pwm.source_id, pwm.tscaler_भाग);
	samsung_समयr_set_भागisor(pwm.source_id, pwm.tभाग);

	घड़ी_rate = pclk / (pwm.tscaler_भाग * pwm.tभाग);

	samsung_समय_setup(pwm.source_id, pwm.tcnt_max);
	samsung_समय_start(pwm.source_id, true);

	अगर (pwm.source_id == 4)
		pwm.source_reg = pwm.base + 0x40;
	अन्यथा
		pwm.source_reg = pwm.base + pwm.source_id * 0x0c + 0x14;

	sched_घड़ी_रेजिस्टर(samsung_पढ़ो_sched_घड़ी,
						pwm.variant.bits, घड़ी_rate);

	samsung_घड़ीsource.mask = CLOCKSOURCE_MASK(pwm.variant.bits);
	वापस घड़ीsource_रेजिस्टर_hz(&samsung_घड़ीsource, घड़ी_rate);
पूर्ण

अटल व्योम __init samsung_समयr_resources(व्योम)
अणु
	clk_prepare_enable(pwm.समयrclk);

	pwm.tcnt_max = (1UL << pwm.variant.bits) - 1;
	अगर (pwm.variant.bits == 16) अणु
		pwm.tscaler_भाग = 25;
		pwm.tभाग = 2;
	पूर्ण अन्यथा अणु
		pwm.tscaler_भाग = 2;
		pwm.tभाग = 1;
	पूर्ण
पूर्ण

/*
 * PWM master driver
 */
अटल पूर्णांक __init _samsung_pwm_घड़ीsource_init(व्योम)
अणु
	u8 mask;
	पूर्णांक channel;

	mask = ~pwm.variant.output_mask & ((1 << SAMSUNG_PWM_NUM) - 1);
	channel = fls(mask) - 1;
	अगर (channel < 0) अणु
		pr_crit("failed to find PWM channel for clocksource\n");
		वापस -EINVAL;
	पूर्ण
	pwm.source_id = channel;

	mask &= ~(1 << channel);
	channel = fls(mask) - 1;
	अगर (channel < 0) अणु
		pr_crit("failed to find PWM channel for clock event\n");
		वापस -EINVAL;
	पूर्ण
	pwm.event_id = channel;

	samsung_समयr_resources();
	samsung_घड़ीevent_init();

	वापस samsung_घड़ीsource_init();
पूर्ण

व्योम __init samsung_pwm_घड़ीsource_init(व्योम __iomem *base,
			अचिन्हित पूर्णांक *irqs, काष्ठा samsung_pwm_variant *variant)
अणु
	pwm.base = base;
	स_नकल(&pwm.variant, variant, माप(pwm.variant));
	स_नकल(pwm.irq, irqs, SAMSUNG_PWM_NUM * माप(*irqs));

	pwm.समयrclk = clk_get(शून्य, "timers");
	अगर (IS_ERR(pwm.समयrclk))
		panic("failed to get timers clock for timer");

	_samsung_pwm_घड़ीsource_init();
पूर्ण

#अगर_घोषित CONFIG_TIMER_OF
अटल पूर्णांक __init samsung_pwm_alloc(काष्ठा device_node *np,
				    स्थिर काष्ठा samsung_pwm_variant *variant)
अणु
	काष्ठा property *prop;
	स्थिर __be32 *cur;
	u32 val;
	पूर्णांक i;

	स_नकल(&pwm.variant, variant, माप(pwm.variant));
	क्रम (i = 0; i < SAMSUNG_PWM_NUM; ++i)
		pwm.irq[i] = irq_of_parse_and_map(np, i);

	of_property_क्रम_each_u32(np, "samsung,pwm-outputs", prop, cur, val) अणु
		अगर (val >= SAMSUNG_PWM_NUM) अणु
			pr_warn("%s: invalid channel index in samsung,pwm-outputs property\n", __func__);
			जारी;
		पूर्ण
		pwm.variant.output_mask |= 1 << val;
	पूर्ण

	pwm.base = of_iomap(np, 0);
	अगर (!pwm.base) अणु
		pr_err("%s: failed to map PWM registers\n", __func__);
		वापस -ENXIO;
	पूर्ण

	pwm.समयrclk = of_clk_get_by_name(np, "timers");
	अगर (IS_ERR(pwm.समयrclk)) अणु
		pr_crit("failed to get timers clock for timer\n");
		वापस PTR_ERR(pwm.समयrclk);
	पूर्ण

	वापस _samsung_pwm_घड़ीsource_init();
पूर्ण

अटल स्थिर काष्ठा samsung_pwm_variant s3c24xx_variant = अणु
	.bits		= 16,
	.भाग_base	= 1,
	.has_tपूर्णांक_cstat	= false,
	.tclk_mask	= (1 << 4),
पूर्ण;

अटल पूर्णांक __init s3c2410_pwm_घड़ीsource_init(काष्ठा device_node *np)
अणु
	वापस samsung_pwm_alloc(np, &s3c24xx_variant);
पूर्ण
TIMER_OF_DECLARE(s3c2410_pwm, "samsung,s3c2410-pwm", s3c2410_pwm_घड़ीsource_init);

अटल स्थिर काष्ठा samsung_pwm_variant s3c64xx_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= (1 << 7) | (1 << 6) | (1 << 5),
पूर्ण;

अटल पूर्णांक __init s3c64xx_pwm_घड़ीsource_init(काष्ठा device_node *np)
अणु
	वापस samsung_pwm_alloc(np, &s3c64xx_variant);
पूर्ण
TIMER_OF_DECLARE(s3c6400_pwm, "samsung,s3c6400-pwm", s3c64xx_pwm_घड़ीsource_init);

अटल स्थिर काष्ठा samsung_pwm_variant s5p64x0_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= 0,
पूर्ण;

अटल पूर्णांक __init s5p64x0_pwm_घड़ीsource_init(काष्ठा device_node *np)
अणु
	वापस samsung_pwm_alloc(np, &s5p64x0_variant);
पूर्ण
TIMER_OF_DECLARE(s5p6440_pwm, "samsung,s5p6440-pwm", s5p64x0_pwm_घड़ीsource_init);

अटल स्थिर काष्ठा samsung_pwm_variant s5p_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= (1 << 5),
पूर्ण;

अटल पूर्णांक __init s5p_pwm_घड़ीsource_init(काष्ठा device_node *np)
अणु
	वापस samsung_pwm_alloc(np, &s5p_variant);
पूर्ण
TIMER_OF_DECLARE(s5pc100_pwm, "samsung,s5pc100-pwm", s5p_pwm_घड़ीsource_init);
#पूर्ण_अगर
