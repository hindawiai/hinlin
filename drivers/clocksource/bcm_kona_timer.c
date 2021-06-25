<शैली गुरु>
/*
 * Copyright (C) 2012 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/types.h>
#समावेश <linux/clk.h>

#समावेश <linux/पन.स>

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>


#घोषणा KONA_GPTIMER_STCS_OFFSET			0x00000000
#घोषणा KONA_GPTIMER_STCLO_OFFSET			0x00000004
#घोषणा KONA_GPTIMER_STCHI_OFFSET			0x00000008
#घोषणा KONA_GPTIMER_STCM0_OFFSET			0x0000000C

#घोषणा KONA_GPTIMER_STCS_TIMER_MATCH_SHIFT		0
#घोषणा KONA_GPTIMER_STCS_COMPARE_ENABLE_SHIFT		4

काष्ठा kona_bcm_समयrs अणु
	पूर्णांक पंचांगr_irq;
	व्योम __iomem *पंचांगr_regs;
पूर्ण;

अटल काष्ठा kona_bcm_समयrs समयrs;

अटल u32 arch_समयr_rate;

/*
 * We use the peripheral समयrs क्रम प्रणाली tick, the cpu global समयr क्रम
 * profile tick
 */
अटल व्योम kona_समयr_disable_and_clear(व्योम __iomem *base)
अणु
	uपूर्णांक32_t reg;

	/*
	 * clear and disable पूर्णांकerrupts
	 * We are using compare/match रेजिस्टर 0 क्रम our प्रणाली पूर्णांकerrupts
	 */
	reg = पढ़ोl(base + KONA_GPTIMER_STCS_OFFSET);

	/* Clear compare (0) पूर्णांकerrupt */
	reg |= 1 << KONA_GPTIMER_STCS_TIMER_MATCH_SHIFT;
	/* disable compare */
	reg &= ~(1 << KONA_GPTIMER_STCS_COMPARE_ENABLE_SHIFT);

	ग_लिखोl(reg, base + KONA_GPTIMER_STCS_OFFSET);

पूर्ण

अटल पूर्णांक
kona_समयr_get_counter(व्योम __iomem *समयr_base, uपूर्णांक32_t *msw, uपूर्णांक32_t *lsw)
अणु
	पूर्णांक loop_limit = 3;

	/*
	 * Read 64-bit मुक्त running counter
	 * 1. Read hi-word
	 * 2. Read low-word
	 * 3. Read hi-word again
	 * 4.1
	 *      अगर new hi-word is not equal to previously पढ़ो hi-word, then
	 *      start from #1
	 * 4.2
	 *      अगर new hi-word is equal to previously पढ़ो hi-word then stop.
	 */

	करो अणु
		*msw = पढ़ोl(समयr_base + KONA_GPTIMER_STCHI_OFFSET);
		*lsw = पढ़ोl(समयr_base + KONA_GPTIMER_STCLO_OFFSET);
		अगर (*msw == पढ़ोl(समयr_base + KONA_GPTIMER_STCHI_OFFSET))
			अवरोध;
	पूर्ण जबतक (--loop_limit);
	अगर (!loop_limit) अणु
		pr_err("bcm_kona_timer: getting counter failed.\n");
		pr_err(" Timer will be impacted\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kona_समयr_set_next_event(अचिन्हित दीर्घ clc,
				  काष्ठा घड़ी_event_device *unused)
अणु
	/*
	 * समयr (0) is disabled by the समयr पूर्णांकerrupt alपढ़ोy
	 * so, here we reload the next event value and re-enable
	 * the समयr.
	 *
	 * This way, we are potentially losing the समय between
	 * समयr-पूर्णांकerrupt->set_next_event. CPU local समयrs, when
	 * they come in should get rid of skew.
	 */

	uपूर्णांक32_t lsw, msw;
	uपूर्णांक32_t reg;
	पूर्णांक ret;

	ret = kona_समयr_get_counter(समयrs.पंचांगr_regs, &msw, &lsw);
	अगर (ret)
		वापस ret;

	/* Load the "next" event tick value */
	ग_लिखोl(lsw + clc, समयrs.पंचांगr_regs + KONA_GPTIMER_STCM0_OFFSET);

	/* Enable compare */
	reg = पढ़ोl(समयrs.पंचांगr_regs + KONA_GPTIMER_STCS_OFFSET);
	reg |= (1 << KONA_GPTIMER_STCS_COMPARE_ENABLE_SHIFT);
	ग_लिखोl(reg, समयrs.पंचांगr_regs + KONA_GPTIMER_STCS_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक kona_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	kona_समयr_disable_and_clear(समयrs.पंचांगr_regs);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device kona_घड़ीevent_समयr = अणु
	.name = "timer 1",
	.features = CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event = kona_समयr_set_next_event,
	.set_state_shutकरोwn = kona_समयr_shutकरोwn,
	.tick_resume = kona_समयr_shutकरोwn,
पूर्ण;

अटल व्योम __init kona_समयr_घड़ीevents_init(व्योम)
अणु
	kona_घड़ीevent_समयr.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&kona_घड़ीevent_समयr,
		arch_समयr_rate, 6, 0xffffffff);
पूर्ण

अटल irqवापस_t kona_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &kona_घड़ीevent_समयr;

	kona_समयr_disable_and_clear(समयrs.पंचांगr_regs);
	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init kona_समयr_init(काष्ठा device_node *node)
अणु
	u32 freq;
	काष्ठा clk *बाह्यal_clk;

	बाह्यal_clk = of_clk_get_by_name(node, शून्य);

	अगर (!IS_ERR(बाह्यal_clk)) अणु
		arch_समयr_rate = clk_get_rate(बाह्यal_clk);
		clk_prepare_enable(बाह्यal_clk);
	पूर्ण अन्यथा अगर (!of_property_पढ़ो_u32(node, "clock-frequency", &freq)) अणु
		arch_समयr_rate = freq;
	पूर्ण अन्यथा अणु
		pr_err("Kona Timer v1 unable to determine clock-frequency\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup IRQ numbers */
	समयrs.पंचांगr_irq = irq_of_parse_and_map(node, 0);

	/* Setup IO addresses */
	समयrs.पंचांगr_regs = of_iomap(node, 0);

	kona_समयr_disable_and_clear(समयrs.पंचांगr_regs);

	kona_समयr_घड़ीevents_init();
	अगर (request_irq(समयrs.पंचांगr_irq, kona_समयr_पूर्णांकerrupt, IRQF_TIMER,
			"Kona Timer Tick", शून्य))
		pr_err("%s: request_irq() failed\n", "Kona Timer Tick");
	kona_समयr_set_next_event((arch_समयr_rate / HZ), शून्य);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(brcm_kona, "brcm,kona-timer", kona_समयr_init);
/*
 * bcm,kona-समयr is deprecated by brcm,kona-समयr
 * being kept here क्रम driver compatibility
 */
TIMER_OF_DECLARE(bcm_kona, "bcm,kona-timer", kona_समयr_init);
