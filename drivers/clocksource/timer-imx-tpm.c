<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2016 Freescale Semiconductor, Inc.
// Copyright 2017 NXP

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश "timer-of.h"

#घोषणा TPM_PARAM			0x4
#घोषणा TPM_PARAM_WIDTH_SHIFT		16
#घोषणा TPM_PARAM_WIDTH_MASK		(0xff << 16)
#घोषणा TPM_SC				0x10
#घोषणा TPM_SC_CMOD_INC_PER_CNT		(0x1 << 3)
#घोषणा TPM_SC_CMOD_DIV_DEFAULT		0x3
#घोषणा TPM_SC_CMOD_DIV_MAX		0x7
#घोषणा TPM_SC_TOF_MASK			(0x1 << 7)
#घोषणा TPM_CNT				0x14
#घोषणा TPM_MOD				0x18
#घोषणा TPM_STATUS			0x1c
#घोषणा TPM_STATUS_CH0F			BIT(0)
#घोषणा TPM_C0SC			0x20
#घोषणा TPM_C0SC_CHIE			BIT(6)
#घोषणा TPM_C0SC_MODE_SHIFT		2
#घोषणा TPM_C0SC_MODE_MASK		0x3c
#घोषणा TPM_C0SC_MODE_SW_COMPARE	0x4
#घोषणा TPM_C0SC_CHF_MASK		(0x1 << 7)
#घोषणा TPM_C0V				0x24

अटल पूर्णांक counter_width;
अटल व्योम __iomem *समयr_base;

अटल अंतरभूत व्योम tpm_समयr_disable(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* channel disable */
	val = पढ़ोl(समयr_base + TPM_C0SC);
	val &= ~(TPM_C0SC_MODE_MASK | TPM_C0SC_CHIE);
	ग_लिखोl(val, समयr_base + TPM_C0SC);
पूर्ण

अटल अंतरभूत व्योम tpm_समयr_enable(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* channel enabled in sw compare mode */
	val = पढ़ोl(समयr_base + TPM_C0SC);
	val |= (TPM_C0SC_MODE_SW_COMPARE << TPM_C0SC_MODE_SHIFT) |
	       TPM_C0SC_CHIE;
	ग_लिखोl(val, समयr_base + TPM_C0SC);
पूर्ण

अटल अंतरभूत व्योम tpm_irq_acknowledge(व्योम)
अणु
	ग_लिखोl(TPM_STATUS_CH0F, समयr_base + TPM_STATUS);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tpm_पढ़ो_counter(व्योम)
अणु
	वापस पढ़ोl(समयr_base + TPM_CNT);
पूर्ण

#अगर defined(CONFIG_ARM)
अटल काष्ठा delay_समयr tpm_delay_समयr;

अटल अचिन्हित दीर्घ tpm_पढ़ो_current_समयr(व्योम)
अणु
	वापस tpm_पढ़ो_counter();
पूर्ण
#पूर्ण_अगर

अटल u64 notrace tpm_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस tpm_पढ़ो_counter();
पूर्ण

अटल पूर्णांक tpm_set_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ next, now;

	next = tpm_पढ़ो_counter();
	next += delta;
	ग_लिखोl(next, समयr_base + TPM_C0V);
	now = tpm_पढ़ो_counter();

	/*
	 * NOTE: We observed in a very small probability, the bus fabric
	 * contention between GPU and A7 may results a few cycles delay
	 * of writing CNT रेजिस्टरs which may cause the min_delta event got
	 * missed, so we need add a ETIME check here in हाल it happened.
	 */
	वापस (पूर्णांक)(next - now) <= 0 ? -ETIME : 0;
पूर्ण

अटल पूर्णांक tpm_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	tpm_समयr_enable();

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	tpm_समयr_disable();

	वापस 0;
पूर्ण

अटल irqवापस_t tpm_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	tpm_irq_acknowledge();

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of to_tpm = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE | TIMER_OF_CLOCK,
	.clkevt = अणु
		.name			= "i.MX7ULP TPM Timer",
		.rating			= 200,
		.features		= CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn	= tpm_set_state_shutकरोwn,
		.set_state_oneshot	= tpm_set_state_oneshot,
		.set_next_event		= tpm_set_next_event,
		.cpumask		= cpu_possible_mask,
	पूर्ण,
	.of_irq = अणु
		.handler		= tpm_समयr_पूर्णांकerrupt,
		.flags			= IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
	.of_clk = अणु
		.name = "per",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tpm_घड़ीsource_init(व्योम)
अणु
#अगर defined(CONFIG_ARM)
	tpm_delay_समयr.पढ़ो_current_समयr = &tpm_पढ़ो_current_समयr;
	tpm_delay_समयr.freq = समयr_of_rate(&to_tpm) >> 3;
	रेजिस्टर_current_समयr_delay(&tpm_delay_समयr);
#पूर्ण_अगर

	sched_घड़ी_रेजिस्टर(tpm_पढ़ो_sched_घड़ी, counter_width,
			     समयr_of_rate(&to_tpm) >> 3);

	वापस घड़ीsource_mmio_init(समयr_base + TPM_CNT,
				     "imx-tpm",
				     समयr_of_rate(&to_tpm) >> 3,
				     to_tpm.clkevt.rating,
				     counter_width,
				     घड़ीsource_mmio_पढ़ोl_up);
पूर्ण

अटल व्योम __init tpm_घड़ीevent_init(व्योम)
अणु
	घड़ीevents_config_and_रेजिस्टर(&to_tpm.clkevt,
					समयr_of_rate(&to_tpm) >> 3,
					300,
					GENMASK(counter_width - 1,
					1));
पूर्ण

अटल पूर्णांक __init tpm_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *ipg;
	पूर्णांक ret;

	ipg = of_clk_get_by_name(np, "ipg");
	अगर (IS_ERR(ipg)) अणु
		pr_err("tpm: failed to get ipg clk\n");
		वापस -ENODEV;
	पूर्ण
	/* enable clk beक्रमe accessing रेजिस्टरs */
	ret = clk_prepare_enable(ipg);
	अगर (ret) अणु
		pr_err("tpm: ipg clock enable failed (%d)\n", ret);
		clk_put(ipg);
		वापस ret;
	पूर्ण

	ret = समयr_of_init(np, &to_tpm);
	अगर (ret)
		वापस ret;

	समयr_base = समयr_of_base(&to_tpm);

	counter_width = (पढ़ोl(समयr_base + TPM_PARAM)
		& TPM_PARAM_WIDTH_MASK) >> TPM_PARAM_WIDTH_SHIFT;
	/* use rating 200 क्रम 32-bit counter and 150 क्रम 16-bit counter */
	to_tpm.clkevt.rating = counter_width == 0x20 ? 200 : 150;

	/*
	 * Initialize tpm module to a known state
	 * 1) Counter disabled
	 * 2) TPM counter operates in up counting mode
	 * 3) Timer Overflow Interrupt disabled
	 * 4) Channel0 disabled
	 * 5) DMA transfers disabled
	 */
	/* make sure counter is disabled */
	ग_लिखोl(0, समयr_base + TPM_SC);
	/* TOF is W1C */
	ग_लिखोl(TPM_SC_TOF_MASK, समयr_base + TPM_SC);
	ग_लिखोl(0, समयr_base + TPM_CNT);
	/* CHF is W1C */
	ग_लिखोl(TPM_C0SC_CHF_MASK, समयr_base + TPM_C0SC);

	/*
	 * increase per cnt,
	 * भाग 8 क्रम 32-bit counter and भाग 128 क्रम 16-bit counter
	 */
	ग_लिखोl(TPM_SC_CMOD_INC_PER_CNT |
		(counter_width == 0x20 ?
		TPM_SC_CMOD_DIV_DEFAULT : TPM_SC_CMOD_DIV_MAX),
		समयr_base + TPM_SC);

	/* set MOD रेजिस्टर to maximum क्रम मुक्त running mode */
	ग_लिखोl(GENMASK(counter_width - 1, 0), समयr_base + TPM_MOD);

	tpm_घड़ीevent_init();

	वापस tpm_घड़ीsource_init();
पूर्ण
TIMER_OF_DECLARE(imx7ulp, "fsl,imx7ulp-tpm", tpm_समयr_init);
