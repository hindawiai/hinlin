<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mach/समय.स>
#समावेश "soc.h"

/*************************************************************************
 * Timer handling क्रम EP93xx
 *************************************************************************
 * The ep93xx has four पूर्णांकernal समयrs.  Timers 1, 2 (both 16 bit) and
 * 3 (32 bit) count करोwn at 508 kHz, are self-reloading, and can generate
 * an पूर्णांकerrupt on underflow.  Timer 4 (40 bit) counts करोwn at 983.04 kHz,
 * is मुक्त-running, and can't generate पूर्णांकerrupts.
 *
 * The 508 kHz समयrs are ideal क्रम use क्रम the समयr पूर्णांकerrupt, as the
 * most common values of HZ भागide 508 kHz nicely.  We pick the 32 bit
 * समयr (समयr 3) to get as दीर्घ sleep पूर्णांकervals as possible when using
 * CONFIG_NO_HZ.
 *
 * The higher घड़ी rate of समयr 4 makes it a better choice than the
 * other समयrs क्रम use as घड़ी source and क्रम sched_घड़ी(), providing
 * a stable 40 bit समय base.
 *************************************************************************
 */
#घोषणा EP93XX_TIMER_REG(x)		(EP93XX_TIMER_BASE + (x))
#घोषणा EP93XX_TIMER1_LOAD		EP93XX_TIMER_REG(0x00)
#घोषणा EP93XX_TIMER1_VALUE		EP93XX_TIMER_REG(0x04)
#घोषणा EP93XX_TIMER1_CONTROL		EP93XX_TIMER_REG(0x08)
#घोषणा EP93XX_TIMER123_CONTROL_ENABLE	(1 << 7)
#घोषणा EP93XX_TIMER123_CONTROL_MODE	(1 << 6)
#घोषणा EP93XX_TIMER123_CONTROL_CLKSEL	(1 << 3)
#घोषणा EP93XX_TIMER1_CLEAR		EP93XX_TIMER_REG(0x0c)
#घोषणा EP93XX_TIMER2_LOAD		EP93XX_TIMER_REG(0x20)
#घोषणा EP93XX_TIMER2_VALUE		EP93XX_TIMER_REG(0x24)
#घोषणा EP93XX_TIMER2_CONTROL		EP93XX_TIMER_REG(0x28)
#घोषणा EP93XX_TIMER2_CLEAR		EP93XX_TIMER_REG(0x2c)
#घोषणा EP93XX_TIMER4_VALUE_LOW		EP93XX_TIMER_REG(0x60)
#घोषणा EP93XX_TIMER4_VALUE_HIGH	EP93XX_TIMER_REG(0x64)
#घोषणा EP93XX_TIMER4_VALUE_HIGH_ENABLE	(1 << 8)
#घोषणा EP93XX_TIMER3_LOAD		EP93XX_TIMER_REG(0x80)
#घोषणा EP93XX_TIMER3_VALUE		EP93XX_TIMER_REG(0x84)
#घोषणा EP93XX_TIMER3_CONTROL		EP93XX_TIMER_REG(0x88)
#घोषणा EP93XX_TIMER3_CLEAR		EP93XX_TIMER_REG(0x8c)

#घोषणा EP93XX_TIMER123_RATE		508469
#घोषणा EP93XX_TIMER4_RATE		983040

अटल u64 notrace ep93xx_पढ़ो_sched_घड़ी(व्योम)
अणु
	u64 ret;

	ret = पढ़ोl(EP93XX_TIMER4_VALUE_LOW);
	ret |= ((u64) (पढ़ोl(EP93XX_TIMER4_VALUE_HIGH) & 0xff) << 32);
	वापस ret;
पूर्ण

u64 ep93xx_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *c)
अणु
	u64 ret;

	ret = पढ़ोl(EP93XX_TIMER4_VALUE_LOW);
	ret |= ((u64) (पढ़ोl(EP93XX_TIMER4_VALUE_HIGH) & 0xff) << 32);
	वापस (u64) ret;
पूर्ण

अटल पूर्णांक ep93xx_clkevt_set_next_event(अचिन्हित दीर्घ next,
					काष्ठा घड़ी_event_device *evt)
अणु
	/* Default mode: periodic, off, 508 kHz */
	u32 पंचांगode = EP93XX_TIMER123_CONTROL_MODE |
		    EP93XX_TIMER123_CONTROL_CLKSEL;

	/* Clear समयr */
	ग_लिखोl(पंचांगode, EP93XX_TIMER3_CONTROL);

	/* Set next event */
	ग_लिखोl(next, EP93XX_TIMER3_LOAD);
	ग_लिखोl(पंचांगode | EP93XX_TIMER123_CONTROL_ENABLE,
	       EP93XX_TIMER3_CONTROL);
        वापस 0;
पूर्ण


अटल पूर्णांक ep93xx_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	/* Disable समयr */
	ग_लिखोl(0, EP93XX_TIMER3_CONTROL);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device ep93xx_घड़ीevent = अणु
	.name			= "timer1",
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= ep93xx_clkevt_shutकरोwn,
	.set_state_oneshot	= ep93xx_clkevt_shutकरोwn,
	.tick_resume		= ep93xx_clkevt_shutकरोwn,
	.set_next_event		= ep93xx_clkevt_set_next_event,
	.rating			= 300,
पूर्ण;

अटल irqवापस_t ep93xx_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	/* Writing any value clears the समयr पूर्णांकerrupt */
	ग_लिखोl(1, EP93XX_TIMER3_CLEAR);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init ep93xx_समयr_init(व्योम)
अणु
	पूर्णांक irq = IRQ_EP93XX_TIMER3;
	अचिन्हित दीर्घ flags = IRQF_TIMER | IRQF_IRQPOLL;

	/* Enable and रेजिस्टर घड़ीsource and sched_घड़ी on समयr 4 */
	ग_लिखोl(EP93XX_TIMER4_VALUE_HIGH_ENABLE,
	       EP93XX_TIMER4_VALUE_HIGH);
	घड़ीsource_mmio_init(शून्य, "timer4",
			      EP93XX_TIMER4_RATE, 200, 40,
			      ep93xx_घड़ीsource_पढ़ो);
	sched_घड़ी_रेजिस्टर(ep93xx_पढ़ो_sched_घड़ी, 40,
			     EP93XX_TIMER4_RATE);

	/* Set up घड़ीevent on समयr 3 */
	अगर (request_irq(irq, ep93xx_समयr_पूर्णांकerrupt, flags, "ep93xx timer",
			&ep93xx_घड़ीevent))
		pr_err("Failed to request irq %d (ep93xx timer)\n", irq);
	घड़ीevents_config_and_रेजिस्टर(&ep93xx_घड़ीevent,
					EP93XX_TIMER123_RATE,
					1,
					0xffffffffU);
पूर्ण
