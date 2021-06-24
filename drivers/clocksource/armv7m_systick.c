<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Maxime Coquelin 2015
 * Author:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk.h>
#समावेश <linux/bitops.h>

#घोषणा SYST_CSR	0x00
#घोषणा SYST_RVR	0x04
#घोषणा SYST_CVR	0x08
#घोषणा SYST_CALIB	0x0c

#घोषणा SYST_CSR_ENABLE BIT(0)

#घोषणा SYSTICK_LOAD_RELOAD_MASK 0x00FFFFFF

अटल पूर्णांक __init प्रणाली_समयr_of_रेजिस्टर(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk = शून्य;
	व्योम __iomem *base;
	u32 rate;
	पूर्णांक ret;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_warn("system-timer: invalid base address\n");
		वापस -ENXIO;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "clock-frequency", &rate);
	अगर (ret) अणु
		clk = of_clk_get(np, 0);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			जाओ out_unmap;
		पूर्ण

		ret = clk_prepare_enable(clk);
		अगर (ret)
			जाओ out_clk_put;

		rate = clk_get_rate(clk);
		अगर (!rate) अणु
			ret = -EINVAL;
			जाओ out_clk_disable;
		पूर्ण
	पूर्ण

	ग_लिखोl_relaxed(SYSTICK_LOAD_RELOAD_MASK, base + SYST_RVR);
	ग_लिखोl_relaxed(SYST_CSR_ENABLE, base + SYST_CSR);

	ret = घड़ीsource_mmio_init(base + SYST_CVR, "arm_system_timer", rate,
			200, 24, घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret) अणु
		pr_err("failed to init clocksource (%d)\n", ret);
		अगर (clk)
			जाओ out_clk_disable;
		अन्यथा
			जाओ out_unmap;
	पूर्ण

	pr_info("ARM System timer initialized as clocksource\n");

	वापस 0;

out_clk_disable:
	clk_disable_unprepare(clk);
out_clk_put:
	clk_put(clk);
out_unmap:
	iounmap(base);
	pr_warn("ARM System timer register failed (%d)\n", ret);

	वापस ret;
पूर्ण

TIMER_OF_DECLARE(arm_systick, "arm,armv7m-systick",
			प्रणाली_समयr_of_रेजिस्टर);
