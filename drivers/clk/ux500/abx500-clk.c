<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * abx500 घड़ी implementation क्रम ux500 platक्रमm.
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/mfd/abx500/ab8500-sysctrl.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <dt-bindings/घड़ी/ste-ab8500.h>
#समावेश "clk.h"

#घोषणा AB8500_NUM_CLKS 6

अटल काष्ठा clk *ab8500_clks[AB8500_NUM_CLKS];
अटल काष्ठा clk_onecell_data ab8500_clk_data;

/* Clock definitions क्रम ab8500 */
अटल पूर्णांक ab8500_reg_clks(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा clk *clk;
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर *पूर्णांकclk_parents[] = अणु"ab8500_sysclk", "ulpclk"पूर्ण;
	u16 पूर्णांकclk_reg_sel[] = अणु0 , AB8500_SYSULPCLKCTRL1पूर्ण;
	u8 पूर्णांकclk_reg_mask[] = अणु0 , AB8500_SYSULPCLKCTRL1_SYSULPCLKINTSEL_MASKपूर्ण;
	u8 पूर्णांकclk_reg_bits[] = अणु
		0 ,
		(1 << AB8500_SYSULPCLKCTRL1_SYSULPCLKINTSEL_SHIFT)
	पूर्ण;

	/* Enable SWAT */
	ret = ab8500_sysctrl_set(AB8500_SWATCTRL, AB8500_SWATCTRL_SWATENABLE);
	अगर (ret)
		वापस ret;

	/* ab8500_sysclk2 */
	clk = clk_reg_sysctrl_gate(dev , "ab8500_sysclk2", "ab8500_sysclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_SYSCLKBUF2REQ,
		AB8500_SYSULPCLKCTRL1_SYSCLKBUF2REQ, 0, 0);
	ab8500_clks[AB8500_SYSCLK_BUF2] = clk;

	/* ab8500_sysclk3 */
	clk = clk_reg_sysctrl_gate(dev , "ab8500_sysclk3", "ab8500_sysclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_SYSCLKBUF3REQ,
		AB8500_SYSULPCLKCTRL1_SYSCLKBUF3REQ, 0, 0);
	ab8500_clks[AB8500_SYSCLK_BUF3] = clk;

	/* ab8500_sysclk4 */
	clk = clk_reg_sysctrl_gate(dev , "ab8500_sysclk4", "ab8500_sysclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_SYSCLKBUF4REQ,
		AB8500_SYSULPCLKCTRL1_SYSCLKBUF4REQ, 0, 0);
	ab8500_clks[AB8500_SYSCLK_BUF4] = clk;

	/* ab_ulpclk */
	clk = clk_reg_sysctrl_gate_fixed_rate(dev, "ulpclk", शून्य,
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_ULPCLKREQ,
		AB8500_SYSULPCLKCTRL1_ULPCLKREQ,
		38400000, 9000, 0);
	ab8500_clks[AB8500_SYSCLK_ULP] = clk;

	/* ab8500_पूर्णांकclk */
	clk = clk_reg_sysctrl_set_parent(dev , "intclk", पूर्णांकclk_parents, 2,
		पूर्णांकclk_reg_sel, पूर्णांकclk_reg_mask, पूर्णांकclk_reg_bits, 0);
	ab8500_clks[AB8500_SYSCLK_INT] = clk;

	/* ab8500_audioclk */
	clk = clk_reg_sysctrl_gate(dev , "audioclk", "intclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_AUDIOCLKENA,
		AB8500_SYSULPCLKCTRL1_AUDIOCLKENA, 0, 0);
	ab8500_clks[AB8500_SYSCLK_AUDIO] = clk;

	ab8500_clk_data.clks = ab8500_clks;
	ab8500_clk_data.clk_num = ARRAY_SIZE(ab8500_clks);
	of_clk_add_provider(np, of_clk_src_onecell_get, &ab8500_clk_data);

	dev_info(dev, "registered clocks for ab850x\n");

	वापस 0;
पूर्ण

अटल पूर्णांक abx500_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500 *parent = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret;

	अगर (is_ab8500(parent) || is_ab8505(parent)) अणु
		ret = ab8500_reg_clks(&pdev->dev);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "non supported plf id\n");
		वापस -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id abx500_clk_match[] = अणु
	अणु .compatible = "stericsson,ab8500-clk", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver abx500_clk_driver = अणु
	.driver = अणु
		.name = "abx500-clk",
		.of_match_table = abx500_clk_match,
	पूर्ण,
	.probe	= abx500_clk_probe,
पूर्ण;

अटल पूर्णांक __init abx500_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&abx500_clk_driver);
पूर्ण
arch_initcall(abx500_clk_init);

MODULE_AUTHOR("Ulf Hansson <ulf.hansson@linaro.org");
MODULE_DESCRIPTION("ABX500 clk driver");
MODULE_LICENSE("GPL v2");
