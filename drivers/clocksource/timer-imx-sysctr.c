<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2017-2019 NXP

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>

#समावेश "timer-of.h"

#घोषणा CMP_OFFSET	0x10000

#घोषणा CNTCV_LO	0x8
#घोषणा CNTCV_HI	0xc
#घोषणा CMPCV_LO	(CMP_OFFSET + 0x20)
#घोषणा CMPCV_HI	(CMP_OFFSET + 0x24)
#घोषणा CMPCR		(CMP_OFFSET + 0x2c)

#घोषणा SYS_CTR_EN		0x1
#घोषणा SYS_CTR_IRQ_MASK	0x2

#घोषणा SYS_CTR_CLK_DIV		0x3

अटल व्योम __iomem *sys_ctr_base;
अटल u32 cmpcr;

अटल व्योम sysctr_समयr_enable(bool enable)
अणु
	ग_लिखोl(enable ? cmpcr | SYS_CTR_EN : cmpcr, sys_ctr_base + CMPCR);
पूर्ण

अटल व्योम sysctr_irq_acknowledge(व्योम)
अणु
	/*
	 * clear the enable bit(EN =0) will clear
	 * the status bit(ISTAT = 0), then the पूर्णांकerrupt
	 * संकेत will be negated(acknowledged).
	 */
	sysctr_समयr_enable(false);
पूर्ण

अटल अंतरभूत u64 sysctr_पढ़ो_counter(व्योम)
अणु
	u32 cnt_hi, पंचांगp_hi, cnt_lo;

	करो अणु
		cnt_hi = पढ़ोl_relaxed(sys_ctr_base + CNTCV_HI);
		cnt_lo = पढ़ोl_relaxed(sys_ctr_base + CNTCV_LO);
		पंचांगp_hi = पढ़ोl_relaxed(sys_ctr_base + CNTCV_HI);
	पूर्ण जबतक (पंचांगp_hi != cnt_hi);

	वापस  ((u64) cnt_hi << 32) | cnt_lo;
पूर्ण

अटल पूर्णांक sysctr_set_next_event(अचिन्हित दीर्घ delta,
				 काष्ठा घड़ी_event_device *evt)
अणु
	u32 cmp_hi, cmp_lo;
	u64 next;

	sysctr_समयr_enable(false);

	next = sysctr_पढ़ो_counter();

	next += delta;

	cmp_hi = (next >> 32) & 0x00fffff;
	cmp_lo = next & 0xffffffff;

	ग_लिखोl_relaxed(cmp_hi, sys_ctr_base + CMPCV_HI);
	ग_लिखोl_relaxed(cmp_lo, sys_ctr_base + CMPCV_LO);

	sysctr_समयr_enable(true);

	वापस 0;
पूर्ण

अटल पूर्णांक sysctr_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sysctr_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	sysctr_समयr_enable(false);

	वापस 0;
पूर्ण

अटल irqवापस_t sysctr_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	sysctr_irq_acknowledge();

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of to_sysctr = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_CLOCK | TIMER_OF_BASE,
	.clkevt = अणु
		.name			= "i.MX system counter timer",
		.features		= CLOCK_EVT_FEAT_ONESHOT |
						CLOCK_EVT_FEAT_DYNIRQ,
		.set_state_oneshot	= sysctr_set_state_oneshot,
		.set_next_event		= sysctr_set_next_event,
		.set_state_shutकरोwn	= sysctr_set_state_shutकरोwn,
		.rating			= 200,
	पूर्ण,
	.of_irq = अणु
		.handler		= sysctr_समयr_पूर्णांकerrupt,
		.flags			= IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
	.of_clk = अणु
		.name = "per",
	पूर्ण,
पूर्ण;

अटल व्योम __init sysctr_घड़ीevent_init(व्योम)
अणु
	to_sysctr.clkevt.cpumask = cpumask_of(0);

	घड़ीevents_config_and_रेजिस्टर(&to_sysctr.clkevt,
					समयr_of_rate(&to_sysctr),
					0xff, 0x7fffffff);
पूर्ण

अटल पूर्णांक __init sysctr_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret = 0;

	ret = समयr_of_init(np, &to_sysctr);
	अगर (ret)
		वापस ret;

	/* प्रणाली counter घड़ी is भागided by 3 पूर्णांकernally */
	to_sysctr.of_clk.rate /= SYS_CTR_CLK_DIV;

	sys_ctr_base = समयr_of_base(&to_sysctr);
	cmpcr = पढ़ोl(sys_ctr_base + CMPCR);
	cmpcr &= ~SYS_CTR_EN;

	sysctr_घड़ीevent_init();

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(sysctr_समयr, "nxp,sysctr-timer", sysctr_समयr_init);
