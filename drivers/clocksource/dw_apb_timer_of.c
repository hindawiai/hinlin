<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Altera Corporation
 * Copyright (c) 2011 Picochip Ltd., Jamie Iles
 *
 * Modअगरied from mach-picoxcell/समय.c
 */
#समावेश <linux/delay.h>
#समावेश <linux/dw_apb_समयr.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/sched_घड़ी.h>

अटल पूर्णांक __init समयr_get_base_and_rate(काष्ठा device_node *np,
				    व्योम __iomem **base, u32 *rate)
अणु
	काष्ठा clk *समयr_clk;
	काष्ठा clk *pclk;
	काष्ठा reset_control *rstc;
	पूर्णांक ret;

	*base = of_iomap(np, 0);

	अगर (!*base)
		panic("Unable to map regs for %pOFn", np);

	/*
	 * Reset the समयr अगर the reset control is available, wiping
	 * out the state the firmware may have left it
	 */
	rstc = of_reset_control_get(np, शून्य);
	अगर (!IS_ERR(rstc)) अणु
		reset_control_निश्चित(rstc);
		reset_control_deनिश्चित(rstc);
	पूर्ण

	/*
	 * Not all implementations use a peripheral घड़ी, so करोn't panic
	 * अगर it's not present
	 */
	pclk = of_clk_get_by_name(np, "pclk");
	अगर (!IS_ERR(pclk))
		अगर (clk_prepare_enable(pclk))
			pr_warn("pclk for %pOFn is present, but could not be activated\n",
				np);

	अगर (!of_property_पढ़ो_u32(np, "clock-freq", rate) &&
	    !of_property_पढ़ो_u32(np, "clock-frequency", rate))
		वापस 0;

	समयr_clk = of_clk_get_by_name(np, "timer");
	अगर (IS_ERR(समयr_clk)) अणु
		ret = PTR_ERR(समयr_clk);
		जाओ out_pclk_disable;
	पूर्ण

	ret = clk_prepare_enable(समयr_clk);
	अगर (ret)
		जाओ out_समयr_clk_put;

	*rate = clk_get_rate(समयr_clk);
	अगर (!(*rate)) अणु
		ret = -EINVAL;
		जाओ out_समयr_clk_disable;
	पूर्ण

	वापस 0;

out_समयr_clk_disable:
	clk_disable_unprepare(समयr_clk);
out_समयr_clk_put:
	clk_put(समयr_clk);
out_pclk_disable:
	अगर (!IS_ERR(pclk)) अणु
		clk_disable_unprepare(pclk);
		clk_put(pclk);
	पूर्ण
	iounmap(*base);
	वापस ret;
पूर्ण

अटल पूर्णांक __init add_घड़ीevent(काष्ठा device_node *event_समयr)
अणु
	व्योम __iomem *iobase;
	काष्ठा dw_apb_घड़ी_event_device *ced;
	u32 irq, rate;
	पूर्णांक ret = 0;

	irq = irq_of_parse_and_map(event_समयr, 0);
	अगर (irq == 0)
		panic("No IRQ for clock event timer");

	ret = समयr_get_base_and_rate(event_समयr, &iobase, &rate);
	अगर (ret)
		वापस ret;

	ced = dw_apb_घड़ीevent_init(-1, event_समयr->name, 300, iobase, irq,
				     rate);
	अगर (!ced)
		वापस -EINVAL;

	dw_apb_घड़ीevent_रेजिस्टर(ced);

	वापस 0;
पूर्ण

अटल व्योम __iomem *sched_io_base;
अटल u32 sched_rate;

अटल पूर्णांक __init add_घड़ीsource(काष्ठा device_node *source_समयr)
अणु
	व्योम __iomem *iobase;
	काष्ठा dw_apb_घड़ीsource *cs;
	u32 rate;
	पूर्णांक ret;

	ret = समयr_get_base_and_rate(source_समयr, &iobase, &rate);
	अगर (ret)
		वापस ret;

	cs = dw_apb_घड़ीsource_init(300, source_समयr->name, iobase, rate);
	अगर (!cs)
		वापस -EINVAL;

	dw_apb_घड़ीsource_start(cs);
	dw_apb_घड़ीsource_रेजिस्टर(cs);

	/*
	 * Fallback to use the घड़ीsource as sched_घड़ी अगर no separate
	 * समयr is found. sched_io_base then poपूर्णांकs to the current_value
	 * रेजिस्टर of the घड़ीsource समयr.
	 */
	sched_io_base = iobase + 0x04;
	sched_rate = rate;

	वापस 0;
पूर्ण

अटल u64 notrace पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(sched_io_base);
पूर्ण

अटल स्थिर काष्ठा of_device_id spसमयr_ids[] __initस्थिर = अणु
	अणु .compatible = "picochip,pc3x2-rtc" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल व्योम __init init_sched_घड़ी(व्योम)
अणु
	काष्ठा device_node *sched_समयr;

	sched_समयr = of_find_matching_node(शून्य, spसमयr_ids);
	अगर (sched_समयr) अणु
		समयr_get_base_and_rate(sched_समयr, &sched_io_base,
					&sched_rate);
		of_node_put(sched_समयr);
	पूर्ण

	sched_घड़ी_रेजिस्टर(पढ़ो_sched_घड़ी, 32, sched_rate);
पूर्ण

#अगर_घोषित CONFIG_ARM
अटल अचिन्हित दीर्घ dw_apb_delay_समयr_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(sched_io_base);
पूर्ण

अटल काष्ठा delay_समयr dw_apb_delay_समयr = अणु
	.पढ़ो_current_समयr	= dw_apb_delay_समयr_पढ़ो,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक num_called;
अटल पूर्णांक __init dw_apb_समयr_init(काष्ठा device_node *समयr)
अणु
	पूर्णांक ret = 0;

	चयन (num_called) अणु
	हाल 1:
		pr_debug("%s: found clocksource timer\n", __func__);
		ret = add_घड़ीsource(समयr);
		अगर (ret)
			वापस ret;
		init_sched_घड़ी();
#अगर_घोषित CONFIG_ARM
		dw_apb_delay_समयr.freq = sched_rate;
		रेजिस्टर_current_समयr_delay(&dw_apb_delay_समयr);
#पूर्ण_अगर
		अवरोध;
	शेष:
		pr_debug("%s: found clockevent timer\n", __func__);
		ret = add_घड़ीevent(समयr);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	num_called++;

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(pc3x2_समयr, "picochip,pc3x2-timer", dw_apb_समयr_init);
TIMER_OF_DECLARE(apb_समयr_osc, "snps,dw-apb-timer-osc", dw_apb_समयr_init);
TIMER_OF_DECLARE(apb_समयr_sp, "snps,dw-apb-timer-sp", dw_apb_समयr_init);
TIMER_OF_DECLARE(apb_समयr, "snps,dw-apb-timer", dw_apb_समयr_init);
