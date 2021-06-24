<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_reset.h"

#समावेश "ccu-sun8i-de2.h"

अटल SUNXI_CCU_GATE(bus_mixer0_clk,	"bus-mixer0",	"bus-de",
		      0x04, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_mixer1_clk,	"bus-mixer1",	"bus-de",
		      0x04, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_wb_clk,	"bus-wb",	"bus-de",
		      0x04, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_rot_clk,	"bus-rot",	"bus-de",
		      0x04, BIT(3), 0);

अटल SUNXI_CCU_GATE(mixer0_clk,	"mixer0",	"mixer0-div",
		      0x00, BIT(0), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_GATE(mixer1_clk,	"mixer1",	"mixer1-div",
		      0x00, BIT(1), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_GATE(wb_clk,		"wb",		"wb-div",
		      0x00, BIT(2), CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_GATE(rot_clk,		"rot",		"rot-div",
		      0x00, BIT(3), CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M(mixer0_भाग_clk, "mixer0-div", "de", 0x0c, 0, 4,
		   CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M(mixer1_भाग_clk, "mixer1-div", "de", 0x0c, 4, 4,
		   CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M(wb_भाग_clk, "wb-div", "de", 0x0c, 8, 4,
		   CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M(rot_भाग_clk, "rot-div", "de", 0x0c, 0x0c, 4,
		   CLK_SET_RATE_PARENT);

अटल SUNXI_CCU_M(mixer0_भाग_a83_clk, "mixer0-div", "pll-de", 0x0c, 0, 4,
		   CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M(mixer1_भाग_a83_clk, "mixer1-div", "pll-de", 0x0c, 4, 4,
		   CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M(wb_भाग_a83_clk, "wb-div", "pll-de", 0x0c, 8, 4,
		   CLK_SET_RATE_PARENT);
अटल SUNXI_CCU_M(rot_भाग_a83_clk, "rot-div", "pll-de", 0x0c, 0x0c, 4,
		   CLK_SET_RATE_PARENT);

अटल काष्ठा ccu_common *sun8i_a83t_de2_clks[] = अणु
	&mixer0_clk.common,
	&mixer1_clk.common,
	&wb_clk.common,

	&bus_mixer0_clk.common,
	&bus_mixer1_clk.common,
	&bus_wb_clk.common,

	&mixer0_भाग_a83_clk.common,
	&mixer1_भाग_a83_clk.common,
	&wb_भाग_a83_clk.common,

	&bus_rot_clk.common,
	&rot_clk.common,
	&rot_भाग_a83_clk.common,
पूर्ण;

अटल काष्ठा ccu_common *sun8i_h3_de2_clks[] = अणु
	&mixer0_clk.common,
	&mixer1_clk.common,
	&wb_clk.common,

	&bus_mixer0_clk.common,
	&bus_mixer1_clk.common,
	&bus_wb_clk.common,

	&mixer0_भाग_clk.common,
	&mixer1_भाग_clk.common,
	&wb_भाग_clk.common,
पूर्ण;

अटल काष्ठा ccu_common *sun8i_v3s_de2_clks[] = अणु
	&mixer0_clk.common,
	&wb_clk.common,

	&bus_mixer0_clk.common,
	&bus_wb_clk.common,

	&mixer0_भाग_clk.common,
	&wb_भाग_clk.common,
पूर्ण;

अटल काष्ठा ccu_common *sun50i_a64_de2_clks[] = अणु
	&mixer0_clk.common,
	&mixer1_clk.common,
	&wb_clk.common,

	&bus_mixer0_clk.common,
	&bus_mixer1_clk.common,
	&bus_wb_clk.common,

	&mixer0_भाग_clk.common,
	&mixer1_भाग_clk.common,
	&wb_भाग_clk.common,

	&bus_rot_clk.common,
	&rot_clk.common,
	&rot_भाग_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_a83t_de2_hw_clks = अणु
	.hws	= अणु
		[CLK_MIXER0]		= &mixer0_clk.common.hw,
		[CLK_MIXER1]		= &mixer1_clk.common.hw,
		[CLK_WB]		= &wb_clk.common.hw,
		[CLK_ROT]		= &rot_clk.common.hw,

		[CLK_BUS_MIXER0]	= &bus_mixer0_clk.common.hw,
		[CLK_BUS_MIXER1]	= &bus_mixer1_clk.common.hw,
		[CLK_BUS_WB]		= &bus_wb_clk.common.hw,
		[CLK_BUS_ROT]		= &bus_rot_clk.common.hw,

		[CLK_MIXER0_DIV]	= &mixer0_भाग_a83_clk.common.hw,
		[CLK_MIXER1_DIV]	= &mixer1_भाग_a83_clk.common.hw,
		[CLK_WB_DIV]		= &wb_भाग_a83_clk.common.hw,
		[CLK_ROT_DIV]		= &rot_भाग_a83_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER_WITH_ROT,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_h3_de2_hw_clks = अणु
	.hws	= अणु
		[CLK_MIXER0]		= &mixer0_clk.common.hw,
		[CLK_MIXER1]		= &mixer1_clk.common.hw,
		[CLK_WB]		= &wb_clk.common.hw,

		[CLK_BUS_MIXER0]	= &bus_mixer0_clk.common.hw,
		[CLK_BUS_MIXER1]	= &bus_mixer1_clk.common.hw,
		[CLK_BUS_WB]		= &bus_wb_clk.common.hw,

		[CLK_MIXER0_DIV]	= &mixer0_भाग_clk.common.hw,
		[CLK_MIXER1_DIV]	= &mixer1_भाग_clk.common.hw,
		[CLK_WB_DIV]		= &wb_भाग_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER_WITHOUT_ROT,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun8i_v3s_de2_hw_clks = अणु
	.hws	= अणु
		[CLK_MIXER0]		= &mixer0_clk.common.hw,
		[CLK_WB]		= &wb_clk.common.hw,

		[CLK_BUS_MIXER0]	= &bus_mixer0_clk.common.hw,
		[CLK_BUS_WB]		= &bus_wb_clk.common.hw,

		[CLK_MIXER0_DIV]	= &mixer0_भाग_clk.common.hw,
		[CLK_WB_DIV]		= &wb_भाग_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER_WITHOUT_ROT,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun50i_a64_de2_hw_clks = अणु
	.hws	= अणु
		[CLK_MIXER0]		= &mixer0_clk.common.hw,
		[CLK_MIXER1]		= &mixer1_clk.common.hw,
		[CLK_WB]		= &wb_clk.common.hw,
		[CLK_ROT]		= &rot_clk.common.hw,

		[CLK_BUS_MIXER0]	= &bus_mixer0_clk.common.hw,
		[CLK_BUS_MIXER1]	= &bus_mixer1_clk.common.hw,
		[CLK_BUS_WB]		= &bus_wb_clk.common.hw,
		[CLK_BUS_ROT]		= &bus_rot_clk.common.hw,

		[CLK_MIXER0_DIV]	= &mixer0_भाग_clk.common.hw,
		[CLK_MIXER1_DIV]	= &mixer1_भाग_clk.common.hw,
		[CLK_WB_DIV]		= &wb_भाग_clk.common.hw,
		[CLK_ROT_DIV]		= &rot_भाग_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER_WITH_ROT,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_a83t_de2_resets[] = अणु
	[RST_MIXER0]	= अणु 0x08, BIT(0) पूर्ण,
	/*
	 * Mixer1 reset line is shared with wb, so only RST_WB is
	 * exported here.
	 */
	[RST_WB]	= अणु 0x08, BIT(2) पूर्ण,
	[RST_ROT]	= अणु 0x08, BIT(3) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun8i_h3_de2_resets[] = अणु
	[RST_MIXER0]	= अणु 0x08, BIT(0) पूर्ण,
	/*
	 * Mixer1 reset line is shared with wb, so only RST_WB is
	 * exported here.
	 * V3s करोesn't have mixer1, so it also shares this काष्ठा.
	 */
	[RST_WB]	= अणु 0x08, BIT(2) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_a64_de2_resets[] = अणु
	[RST_MIXER0]	= अणु 0x08, BIT(0) पूर्ण,
	[RST_MIXER1]	= अणु 0x08, BIT(1) पूर्ण,
	[RST_WB]	= अणु 0x08, BIT(2) पूर्ण,
	[RST_ROT]	= अणु 0x08, BIT(3) पूर्ण,
पूर्ण;

अटल काष्ठा ccu_reset_map sun50i_h5_de2_resets[] = अणु
	[RST_MIXER0]	= अणु 0x08, BIT(0) पूर्ण,
	[RST_MIXER1]	= अणु 0x08, BIT(1) पूर्ण,
	[RST_WB]	= अणु 0x08, BIT(2) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_a83t_de2_clk_desc = अणु
	.ccu_clks	= sun8i_a83t_de2_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_a83t_de2_clks),

	.hw_clks	= &sun8i_a83t_de2_hw_clks,

	.resets		= sun8i_a83t_de2_resets,
	.num_resets	= ARRAY_SIZE(sun8i_a83t_de2_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_h3_de2_clk_desc = अणु
	.ccu_clks	= sun8i_h3_de2_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_h3_de2_clks),

	.hw_clks	= &sun8i_h3_de2_hw_clks,

	.resets		= sun8i_h3_de2_resets,
	.num_resets	= ARRAY_SIZE(sun8i_h3_de2_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_r40_de2_clk_desc = अणु
	.ccu_clks	= sun50i_a64_de2_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_a64_de2_clks),

	.hw_clks	= &sun50i_a64_de2_hw_clks,

	.resets		= sun8i_a83t_de2_resets,
	.num_resets	= ARRAY_SIZE(sun8i_a83t_de2_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun8i_v3s_de2_clk_desc = अणु
	.ccu_clks	= sun8i_v3s_de2_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_v3s_de2_clks),

	.hw_clks	= &sun8i_v3s_de2_hw_clks,

	.resets		= sun8i_a83t_de2_resets,
	.num_resets	= ARRAY_SIZE(sun8i_a83t_de2_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_a64_de2_clk_desc = अणु
	.ccu_clks	= sun50i_a64_de2_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun50i_a64_de2_clks),

	.hw_clks	= &sun50i_a64_de2_hw_clks,

	.resets		= sun50i_a64_de2_resets,
	.num_resets	= ARRAY_SIZE(sun50i_a64_de2_resets),
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun50i_h5_de2_clk_desc = अणु
	.ccu_clks	= sun8i_h3_de2_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_h3_de2_clks),

	.hw_clks	= &sun8i_h3_de2_hw_clks,

	.resets		= sun50i_h5_de2_resets,
	.num_resets	= ARRAY_SIZE(sun50i_h5_de2_resets),
पूर्ण;

अटल पूर्णांक sunxi_de2_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा clk *bus_clk, *mod_clk;
	काष्ठा reset_control *rstc;
	व्योम __iomem *reg;
	स्थिर काष्ठा sunxi_ccu_desc *ccu_desc;
	पूर्णांक ret;

	ccu_desc = of_device_get_match_data(&pdev->dev);
	अगर (!ccu_desc)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(bus_clk)) अणु
		ret = PTR_ERR(bus_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Couldn't get bus clk: %d\n", ret);
		वापस ret;
	पूर्ण

	mod_clk = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(mod_clk)) अणु
		ret = PTR_ERR(mod_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Couldn't get mod clk: %d\n", ret);
		वापस ret;
	पूर्ण

	rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"Couldn't get reset control: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The घड़ीs need to be enabled क्रम us to access the रेजिस्टरs */
	ret = clk_prepare_enable(bus_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable bus clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(mod_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable mod clk: %d\n", ret);
		जाओ err_disable_bus_clk;
	पूर्ण

	/* The reset control needs to be निश्चितed क्रम the controls to work */
	ret = reset_control_deनिश्चित(rstc);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Couldn't deassert reset control: %d\n", ret);
		जाओ err_disable_mod_clk;
	पूर्ण

	ret = sunxi_ccu_probe(pdev->dev.of_node, reg, ccu_desc);
	अगर (ret)
		जाओ err_निश्चित_reset;

	वापस 0;

err_निश्चित_reset:
	reset_control_निश्चित(rstc);
err_disable_mod_clk:
	clk_disable_unprepare(mod_clk);
err_disable_bus_clk:
	clk_disable_unprepare(bus_clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sunxi_de2_clk_ids[] = अणु
	अणु
		.compatible = "allwinner,sun8i-a83t-de2-clk",
		.data = &sun8i_a83t_de2_clk_desc,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-de2-clk",
		.data = &sun8i_h3_de2_clk_desc,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-r40-de2-clk",
		.data = &sun8i_r40_de2_clk_desc,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-v3s-de2-clk",
		.data = &sun8i_v3s_de2_clk_desc,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-de2-clk",
		.data = &sun50i_a64_de2_clk_desc,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h5-de2-clk",
		.data = &sun50i_h5_de2_clk_desc,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-de3-clk",
		.data = &sun50i_h5_de2_clk_desc,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sunxi_de2_clk_driver = अणु
	.probe	= sunxi_de2_clk_probe,
	.driver	= अणु
		.name	= "sunxi-de2-clks",
		.of_match_table	= sunxi_de2_clk_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sunxi_de2_clk_driver);
