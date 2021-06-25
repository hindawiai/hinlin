<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/mach-sa1100/घड़ी.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश <mach/hardware.h>
#समावेश <mach/generic.h>

अटल स्थिर अक्षर * स्थिर clk_tucr_parents[] = अणु
	"clk32768", "clk3686400",
पूर्ण;

अटल DEFINE_SPINLOCK(tucr_lock);

अटल पूर्णांक clk_gpio27_enable(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * First, set up the 3.6864MHz घड़ी on GPIO 27 क्रम the SA-1111:
	 * (SA-1110 Developer's Manual, section 9.1.2.1)
	 */
	local_irq_save(flags);
	GAFR |= GPIO_32_768kHz;
	GPDR |= GPIO_32_768kHz;
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम clk_gpio27_disable(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	GPDR &= ~GPIO_32_768kHz;
	GAFR &= ~GPIO_32_768kHz;
	local_irq_restore(flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gpio27_ops = अणु
	.enable = clk_gpio27_enable,
	.disable = clk_gpio27_disable,
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_gpio27_parents[] = अणु
	"tucr-mux",
पूर्ण;

अटल स्थिर काष्ठा clk_init_data clk_gpio27_init_data __initस्थिर = अणु
	.name = "gpio27",
	.ops = &clk_gpio27_ops,
	.parent_names = clk_gpio27_parents,
	.num_parents = ARRAY_SIZE(clk_gpio27_parents),
पूर्ण;

/*
 * Derived from the table 8-1 in the SA1110 manual, the MPLL appears to
 * multiply its input rate by 4 x (4 + PPCR).  This calculation gives
 * the exact rate.  The figures given in the table are the rates rounded
 * to 100kHz.  Stick with sa11x0_माला_लोpeed() क्रम the समय being.
 */
अटल अचिन्हित दीर्घ clk_mpll_recalc_rate(काष्ठा clk_hw *hw,
	अचिन्हित दीर्घ prate)
अणु
	वापस sa11x0_माला_लोpeed(0) * 1000;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_mpll_ops = अणु
	.recalc_rate = clk_mpll_recalc_rate,
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_mpll_parents[] = अणु
	"clk3686400",
पूर्ण;

अटल स्थिर काष्ठा clk_init_data clk_mpll_init_data __initस्थिर = अणु
	.name = "mpll",
	.ops = &clk_mpll_ops,
	.parent_names = clk_mpll_parents,
	.num_parents = ARRAY_SIZE(clk_mpll_parents),
	.flags = CLK_GET_RATE_NOCACHE | CLK_IS_CRITICAL,
पूर्ण;

पूर्णांक __init sa11xx_clk_init(व्योम)
अणु
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk32768", शून्य, 0, 32768);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "sa1100-rtc");

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk3686400", शून्य, 0, 3686400);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	clk_hw_रेजिस्टर_clkdev(hw, "OSTIMER0", शून्य);

	hw = kzalloc(माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;
	hw->init = &clk_mpll_init_data;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(hw);
		वापस ret;
	पूर्ण

	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "sa11x0-fb");
	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "sa11x0-pcmcia");
	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "sa11x0-pcmcia.0");
	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "sa11x0-pcmcia.1");
	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "1800");

	hw = clk_hw_रेजिस्टर_mux(शून्य, "tucr-mux", clk_tucr_parents,
				 ARRAY_SIZE(clk_tucr_parents), 0,
				 (व्योम __iomem *)&TUCR, FShft(TUCR_TSEL),
				 FAlnMsk(TUCR_TSEL), 0, &tucr_lock);
	clk_set_rate(hw->clk, 3686400);

	hw = kzalloc(माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;
	hw->init = &clk_gpio27_init_data;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(hw);
		वापस ret;
	पूर्ण

	clk_hw_रेजिस्टर_clkdev(hw, शून्य, "sa1111.0");

	वापस 0;
पूर्ण
