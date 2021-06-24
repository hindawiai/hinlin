<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Oleksij Rempel <linux@rempel-privat.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/bitops.h>

#घोषणा DRIVER_NAME	"asm9260-timer"

/*
 * this device provide 4 offsets क्रम each रेजिस्टर:
 * 0x0 - plain पढ़ो ग_लिखो mode
 * 0x4 - set mode, OR logic.
 * 0x8 - clr mode, XOR logic.
 * 0xc - togle mode.
 */
#घोषणा SET_REG 4
#घोषणा CLR_REG 8

#घोषणा HW_IR           0x0000 /* RW. Interrupt */
#घोषणा BM_IR_CR0	BIT(4)
#घोषणा BM_IR_MR3	BIT(3)
#घोषणा BM_IR_MR2	BIT(2)
#घोषणा BM_IR_MR1	BIT(1)
#घोषणा BM_IR_MR0	BIT(0)

#घोषणा HW_TCR		0x0010 /* RW. Timer controller */
/* BM_C*_RST
 * Timer Counter and the Prescale Counter are synchronously reset on the
 * next positive edge of PCLK. The counters reमुख्य reset until TCR[1] is
 * वापसed to zero. */
#घोषणा BM_C3_RST	BIT(7)
#घोषणा BM_C2_RST	BIT(6)
#घोषणा BM_C1_RST	BIT(5)
#घोषणा BM_C0_RST	BIT(4)
/* BM_C*_EN
 * 1 - Timer Counter and Prescale Counter are enabled क्रम counting
 * 0 - counters are disabled */
#घोषणा BM_C3_EN	BIT(3)
#घोषणा BM_C2_EN	BIT(2)
#घोषणा BM_C1_EN	BIT(1)
#घोषणा BM_C0_EN	BIT(0)

#घोषणा HW_सूची		0x0020 /* RW. Direction? */
/* 00 - count up
 * 01 - count करोwn
 * 10 - ?? 2^n/2 */
#घोषणा BM_सूची_COUNT_UP		0
#घोषणा BM_सूची_COUNT_DOWN	1
#घोषणा BM_सूची0_SHIFT	0
#घोषणा BM_सूची1_SHIFT	4
#घोषणा BM_सूची2_SHIFT	8
#घोषणा BM_सूची3_SHIFT	12
#घोषणा BM_सूची_DEFAULT		(BM_सूची_COUNT_UP << BM_सूची0_SHIFT | \
				 BM_सूची_COUNT_UP << BM_सूची1_SHIFT | \
				 BM_सूची_COUNT_UP << BM_सूची2_SHIFT | \
				 BM_सूची_COUNT_UP << BM_सूची3_SHIFT)

#घोषणा HW_TC0		0x0030 /* RO. Timer counter 0 */
/* HW_TC*. Timer counter owerflow (0xffff.ffff to 0x0000.0000) करो not generate
 * पूर्णांकerrupt. This रेजिस्टरs can be used to detect overflow */
#घोषणा HW_TC1          0x0040
#घोषणा HW_TC2		0x0050
#घोषणा HW_TC3		0x0060

#घोषणा HW_PR		0x0070 /* RW. prescaler */
#घोषणा BM_PR_DISABLE	0
#घोषणा HW_PC		0x0080 /* RO. Prescaler counter */
#घोषणा HW_MCR		0x0090 /* RW. Match control */
/* enable पूर्णांकerrupt on match */
#घोषणा BM_MCR_INT_EN(n)	(1 << (n * 3 + 0))
/* enable TC reset on match */
#घोषणा BM_MCR_RES_EN(n)	(1 << (n * 3 + 1))
/* enable stop TC on match */
#घोषणा BM_MCR_STOP_EN(n)	(1 << (n * 3 + 2))

#घोषणा HW_MR0		0x00a0 /* RW. Match reg */
#घोषणा HW_MR1		0x00b0
#घोषणा HW_MR2		0x00C0
#घोषणा HW_MR3		0x00D0

#घोषणा HW_CTCR		0x0180 /* Counter control */
#घोषणा BM_CTCR0_SHIFT	0
#घोषणा BM_CTCR1_SHIFT	2
#घोषणा BM_CTCR2_SHIFT	4
#घोषणा BM_CTCR3_SHIFT	6
#घोषणा BM_CTCR_TM	0	/* Timer mode. Every rising PCLK edge. */
#घोषणा BM_CTCR_DEFAULT	(BM_CTCR_TM << BM_CTCR0_SHIFT | \
			 BM_CTCR_TM << BM_CTCR1_SHIFT | \
			 BM_CTCR_TM << BM_CTCR2_SHIFT | \
			 BM_CTCR_TM << BM_CTCR3_SHIFT)

अटल काष्ठा यंत्र9260_समयr_priv अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ ticks_per_jअगरfy;
पूर्ण priv;

अटल पूर्णांक यंत्र9260_समयr_set_next_event(अचिन्हित दीर्घ delta,
					 काष्ठा घड़ी_event_device *evt)
अणु
	/* configure match count क्रम TC0 */
	ग_लिखोl_relaxed(delta, priv.base + HW_MR0);
	/* enable TC0 */
	ग_लिखोl_relaxed(BM_C0_EN, priv.base + HW_TCR + SET_REG);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __यंत्र9260_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	/* stop समयr0 */
	ग_लिखोl_relaxed(BM_C0_EN, priv.base + HW_TCR + CLR_REG);
पूर्ण

अटल पूर्णांक यंत्र9260_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	__यंत्र9260_समयr_shutकरोwn(evt);
	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_समयr_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	__यंत्र9260_समयr_shutकरोwn(evt);

	/* enable reset and stop on match */
	ग_लिखोl_relaxed(BM_MCR_RES_EN(0) | BM_MCR_STOP_EN(0),
		       priv.base + HW_MCR + SET_REG);
	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	__यंत्र9260_समयr_shutकरोwn(evt);

	/* disable reset and stop on match */
	ग_लिखोl_relaxed(BM_MCR_RES_EN(0) | BM_MCR_STOP_EN(0),
		       priv.base + HW_MCR + CLR_REG);
	/* configure match count क्रम TC0 */
	ग_लिखोl_relaxed(priv.ticks_per_jअगरfy, priv.base + HW_MR0);
	/* enable TC0 */
	ग_लिखोl_relaxed(BM_C0_EN, priv.base + HW_TCR + SET_REG);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device event_dev = अणु
	.name			= DRIVER_NAME,
	.rating			= 200,
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event		= यंत्र9260_समयr_set_next_event,
	.set_state_shutकरोwn	= यंत्र9260_समयr_shutकरोwn,
	.set_state_periodic	= यंत्र9260_समयr_set_periodic,
	.set_state_oneshot	= यंत्र9260_समयr_set_oneshot,
	.tick_resume		= यंत्र9260_समयr_shutकरोwn,
पूर्ण;

अटल irqवापस_t यंत्र9260_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	evt->event_handler(evt);

	ग_लिखोl_relaxed(BM_IR_MR0, priv.base + HW_IR);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * Timer initialization
 * ---------------------------------------------------------------------------
 */
अटल पूर्णांक __init यंत्र9260_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक irq;
	काष्ठा clk *clk;
	पूर्णांक ret;
	अचिन्हित दीर्घ rate;

	priv.base = of_io_request_and_map(np, 0, np->name);
	अगर (IS_ERR(priv.base)) अणु
		pr_err("%pOFn: unable to map resource\n", np);
		वापस PTR_ERR(priv.base);
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Failed to get clk!\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("Failed to enable clk!\n");
		वापस ret;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	ret = request_irq(irq, यंत्र9260_समयr_पूर्णांकerrupt, IRQF_TIMER,
			DRIVER_NAME, &event_dev);
	अगर (ret) अणु
		pr_err("Failed to setup irq!\n");
		वापस ret;
	पूर्ण

	/* set all समयrs क्रम count-up */
	ग_लिखोl_relaxed(BM_सूची_DEFAULT, priv.base + HW_सूची);
	/* disable भागider */
	ग_लिखोl_relaxed(BM_PR_DISABLE, priv.base + HW_PR);
	/* make sure all समयrs use every rising PCLK edge. */
	ग_लिखोl_relaxed(BM_CTCR_DEFAULT, priv.base + HW_CTCR);
	/* enable पूर्णांकerrupt क्रम TC0 and clean setting क्रम all other lines */
	ग_लिखोl_relaxed(BM_MCR_INT_EN(0) , priv.base + HW_MCR);

	rate = clk_get_rate(clk);
	घड़ीsource_mmio_init(priv.base + HW_TC1, DRIVER_NAME, rate,
			200, 32, घड़ीsource_mmio_पढ़ोl_up);

	/* Seems like we can't use counter without match रेजिस्टर even अगर
	 * actions क्रम MR are disabled. So, set MR to max value. */
	ग_लिखोl_relaxed(0xffffffff, priv.base + HW_MR1);
	/* enable TC1 */
	ग_लिखोl_relaxed(BM_C1_EN, priv.base + HW_TCR + SET_REG);

	priv.ticks_per_jअगरfy = DIV_ROUND_CLOSEST(rate, HZ);
	event_dev.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&event_dev, rate, 0x2c00, 0xfffffffe);

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(यंत्र9260_समयr, "alphascale,asm9260-timer",
		यंत्र9260_समयr_init);
