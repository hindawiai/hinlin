<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Cirrus Logic CLPS711X CLK driver
 *
 *  Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon/clps711x.h>

#समावेश <dt-bindings/घड़ी/clps711x-घड़ी.h>

#घोषणा CLPS711X_SYSCON1	(0x0100)
#घोषणा CLPS711X_SYSCON2	(0x1100)
#घोषणा CLPS711X_SYSFLG2	(CLPS711X_SYSCON2 + SYSFLG_OFFSET)
#घोषणा CLPS711X_PLLR		(0xa5a8)

#घोषणा CLPS711X_EXT_FREQ	(13000000)
#घोषणा CLPS711X_OSC_FREQ	(3686400)

अटल स्थिर काष्ठा clk_भाग_प्रकारable spi_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 32, पूर्ण,
	अणु .val = 1, .भाग = 8, पूर्ण,
	अणु .val = 2, .भाग = 2, पूर्ण,
	अणु .val = 3, .भाग = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable समयr_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 256, पूर्ण,
	अणु .val = 1, .भाग = 1, पूर्ण,
पूर्ण;

काष्ठा clps711x_clk अणु
	spinlock_t			lock;
	काष्ठा clk_hw_onecell_data	clk_data;
पूर्ण;

अटल व्योम __init clps711x_clk_init_dt(काष्ठा device_node *np)
अणु
	u32 पंचांगp, f_cpu, f_pll, f_bus, f_tim, f_pwm, f_spi, fref = 0;
	काष्ठा clps711x_clk *clps711x_clk;
	व्योम __iomem *base;

	WARN_ON(of_property_पढ़ो_u32(np, "startup-frequency", &fref));

	base = of_iomap(np, 0);
	BUG_ON(!base);

	clps711x_clk = kzalloc(काष्ठा_size(clps711x_clk, clk_data.hws,
					   CLPS711X_CLK_MAX),
			       GFP_KERNEL);
	BUG_ON(!clps711x_clk);

	spin_lock_init(&clps711x_clk->lock);

	/* Read PLL multiplier value and sanity check */
	पंचांगp = पढ़ोl(base + CLPS711X_PLLR) >> 24;
	अगर (((पंचांगp >= 10) && (पंचांगp <= 50)) || !fref)
		f_pll = DIV_ROUND_UP(CLPS711X_OSC_FREQ * पंचांगp, 2);
	अन्यथा
		f_pll = fref;

	पंचांगp = पढ़ोl(base + CLPS711X_SYSFLG2);
	अगर (पंचांगp & SYSFLG2_CKMODE) अणु
		f_cpu = CLPS711X_EXT_FREQ;
		f_bus = CLPS711X_EXT_FREQ;
		f_spi = DIV_ROUND_CLOSEST(CLPS711X_EXT_FREQ, 96);
		f_pll = 0;
		f_pwm = DIV_ROUND_CLOSEST(CLPS711X_EXT_FREQ, 128);
	पूर्ण अन्यथा अणु
		f_cpu = f_pll;
		अगर (f_cpu > 36864000)
			f_bus = DIV_ROUND_UP(f_cpu, 2);
		अन्यथा
			f_bus = 36864000 / 2;
		f_spi = DIV_ROUND_CLOSEST(f_cpu, 576);
		f_pwm = DIV_ROUND_CLOSEST(f_cpu, 768);
	पूर्ण

	अगर (पंचांगp & SYSFLG2_CKMODE) अणु
		अगर (पढ़ोl(base + CLPS711X_SYSCON2) & SYSCON2_OSTB)
			f_tim = DIV_ROUND_CLOSEST(CLPS711X_EXT_FREQ, 26);
		अन्यथा
			f_tim = DIV_ROUND_CLOSEST(CLPS711X_EXT_FREQ, 24);
	पूर्ण अन्यथा
		f_tim = DIV_ROUND_CLOSEST(f_cpu, 144);

	पंचांगp = पढ़ोl(base + CLPS711X_SYSCON1);
	/* Timer1 in मुक्त running mode.
	 * Counter will wrap around to 0xffff when it underflows
	 * and will जारी to count करोwn.
	 */
	पंचांगp &= ~(SYSCON1_TC1M | SYSCON1_TC1S);
	/* Timer2 in prescale mode.
	 * Value ग_लिखोn is स्वतःmatically re-loaded when
	 * the counter underflows.
	 */
	पंचांगp |= SYSCON1_TC2M | SYSCON1_TC2S;
	ग_लिखोl(पंचांगp, base + CLPS711X_SYSCON1);

	clps711x_clk->clk_data.hws[CLPS711X_CLK_DUMMY] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "dummy", शून्य, 0, 0);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_CPU] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "cpu", शून्य, 0, f_cpu);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_BUS] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "bus", शून्य, 0, f_bus);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_PLL] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "pll", शून्य, 0, f_pll);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_TIMERREF] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "timer_ref", शून्य, 0, f_tim);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_TIMER1] =
		clk_hw_रेजिस्टर_भागider_table(शून्य, "timer1", "timer_ref", 0,
					   base + CLPS711X_SYSCON1, 5, 1, 0,
					   समयr_भाग_प्रकारable, &clps711x_clk->lock);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_TIMER2] =
		clk_hw_रेजिस्टर_भागider_table(शून्य, "timer2", "timer_ref", 0,
					   base + CLPS711X_SYSCON1, 7, 1, 0,
					   समयr_भाग_प्रकारable, &clps711x_clk->lock);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_PWM] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "pwm", शून्य, 0, f_pwm);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_SPIREF] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "spi_ref", शून्य, 0, f_spi);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_SPI] =
		clk_hw_रेजिस्टर_भागider_table(शून्य, "spi", "spi_ref", 0,
					   base + CLPS711X_SYSCON1, 16, 2, 0,
					   spi_भाग_प्रकारable, &clps711x_clk->lock);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_UART] =
		clk_hw_रेजिस्टर_fixed_factor(शून्य, "uart", "bus", 0, 1, 10);
	clps711x_clk->clk_data.hws[CLPS711X_CLK_TICK] =
		clk_hw_रेजिस्टर_fixed_rate(शून्य, "tick", शून्य, 0, 64);
	क्रम (पंचांगp = 0; पंचांगp < CLPS711X_CLK_MAX; पंचांगp++)
		अगर (IS_ERR(clps711x_clk->clk_data.hws[पंचांगp]))
			pr_err("clk %i: register failed with %ld\n",
			       पंचांगp, PTR_ERR(clps711x_clk->clk_data.hws[पंचांगp]));

	clps711x_clk->clk_data.num = CLPS711X_CLK_MAX;
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
			       &clps711x_clk->clk_data);
पूर्ण
CLK_OF_DECLARE(clps711x, "cirrus,ep7209-clk", clps711x_clk_init_dt);
