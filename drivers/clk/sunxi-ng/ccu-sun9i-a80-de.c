<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chen-Yu Tsai. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_reset.h"

#समावेश "ccu-sun9i-a80-de.h"

अटल SUNXI_CCU_GATE(fe0_clk,		"fe0",		"fe0-div",
		      0x00, BIT(0), 0);
अटल SUNXI_CCU_GATE(fe1_clk,		"fe1",		"fe1-div",
		      0x00, BIT(1), 0);
अटल SUNXI_CCU_GATE(fe2_clk,		"fe2",		"fe2-div",
		      0x00, BIT(2), 0);
अटल SUNXI_CCU_GATE(iep_deu0_clk,	"iep-deu0",	"de",
		      0x00, BIT(4), 0);
अटल SUNXI_CCU_GATE(iep_deu1_clk,	"iep-deu1",	"de",
		      0x00, BIT(5), 0);
अटल SUNXI_CCU_GATE(be0_clk,		"be0",		"be0-div",
		      0x00, BIT(8), 0);
अटल SUNXI_CCU_GATE(be1_clk,		"be1",		"be1-div",
		      0x00, BIT(9), 0);
अटल SUNXI_CCU_GATE(be2_clk,		"be2",		"be2-div",
		      0x00, BIT(10), 0);
अटल SUNXI_CCU_GATE(iep_drc0_clk,	"iep-drc0",	"de",
		      0x00, BIT(12), 0);
अटल SUNXI_CCU_GATE(iep_drc1_clk,	"iep-drc1",	"de",
		      0x00, BIT(13), 0);
अटल SUNXI_CCU_GATE(merge_clk,	"merge",	"de",
		      0x00, BIT(20), 0);

अटल SUNXI_CCU_GATE(dram_fe0_clk,	"dram-fe0",	"sdram",
		      0x04, BIT(0), 0);
अटल SUNXI_CCU_GATE(dram_fe1_clk,	"dram-fe1",	"sdram",
		      0x04, BIT(1), 0);
अटल SUNXI_CCU_GATE(dram_fe2_clk,	"dram-fe2",	"sdram",
		      0x04, BIT(2), 0);
अटल SUNXI_CCU_GATE(dram_deu0_clk,	"dram-deu0",	"sdram",
		      0x04, BIT(4), 0);
अटल SUNXI_CCU_GATE(dram_deu1_clk,	"dram-deu1",	"sdram",
		      0x04, BIT(5), 0);
अटल SUNXI_CCU_GATE(dram_be0_clk,	"dram-be0",	"sdram",
		      0x04, BIT(8), 0);
अटल SUNXI_CCU_GATE(dram_be1_clk,	"dram-be1",	"sdram",
		      0x04, BIT(9), 0);
अटल SUNXI_CCU_GATE(dram_be2_clk,	"dram-be2",	"sdram",
		      0x04, BIT(10), 0);
अटल SUNXI_CCU_GATE(dram_drc0_clk,	"dram-drc0",	"sdram",
		      0x04, BIT(12), 0);
अटल SUNXI_CCU_GATE(dram_drc1_clk,	"dram-drc1",	"sdram",
		      0x04, BIT(13), 0);

अटल SUNXI_CCU_GATE(bus_fe0_clk,	"bus-fe0",	"bus-de",
		      0x08, BIT(0), 0);
अटल SUNXI_CCU_GATE(bus_fe1_clk,	"bus-fe1",	"bus-de",
		      0x08, BIT(1), 0);
अटल SUNXI_CCU_GATE(bus_fe2_clk,	"bus-fe2",	"bus-de",
		      0x08, BIT(2), 0);
अटल SUNXI_CCU_GATE(bus_deu0_clk,	"bus-deu0",	"bus-de",
		      0x08, BIT(4), 0);
अटल SUNXI_CCU_GATE(bus_deu1_clk,	"bus-deu1",	"bus-de",
		      0x08, BIT(5), 0);
अटल SUNXI_CCU_GATE(bus_be0_clk,	"bus-be0",	"bus-de",
		      0x08, BIT(8), 0);
अटल SUNXI_CCU_GATE(bus_be1_clk,	"bus-be1",	"bus-de",
		      0x08, BIT(9), 0);
अटल SUNXI_CCU_GATE(bus_be2_clk,	"bus-be2",	"bus-de",
		      0x08, BIT(10), 0);
अटल SUNXI_CCU_GATE(bus_drc0_clk,	"bus-drc0",	"bus-de",
		      0x08, BIT(12), 0);
अटल SUNXI_CCU_GATE(bus_drc1_clk,	"bus-drc1",	"bus-de",
		      0x08, BIT(13), 0);

अटल SUNXI_CCU_M(fe0_भाग_clk, "fe0-div", "de", 0x20, 0, 4, 0);
अटल SUNXI_CCU_M(fe1_भाग_clk, "fe1-div", "de", 0x20, 4, 4, 0);
अटल SUNXI_CCU_M(fe2_भाग_clk, "fe2-div", "de", 0x20, 8, 4, 0);
अटल SUNXI_CCU_M(be0_भाग_clk, "be0-div", "de", 0x20, 16, 4, 0);
अटल SUNXI_CCU_M(be1_भाग_clk, "be1-div", "de", 0x20, 20, 4, 0);
अटल SUNXI_CCU_M(be2_भाग_clk, "be2-div", "de", 0x20, 24, 4, 0);

अटल काष्ठा ccu_common *sun9i_a80_de_clks[] = अणु
	&fe0_clk.common,
	&fe1_clk.common,
	&fe2_clk.common,
	&iep_deu0_clk.common,
	&iep_deu1_clk.common,
	&be0_clk.common,
	&be1_clk.common,
	&be2_clk.common,
	&iep_drc0_clk.common,
	&iep_drc1_clk.common,
	&merge_clk.common,

	&dram_fe0_clk.common,
	&dram_fe1_clk.common,
	&dram_fe2_clk.common,
	&dram_deu0_clk.common,
	&dram_deu1_clk.common,
	&dram_be0_clk.common,
	&dram_be1_clk.common,
	&dram_be2_clk.common,
	&dram_drc0_clk.common,
	&dram_drc1_clk.common,

	&bus_fe0_clk.common,
	&bus_fe1_clk.common,
	&bus_fe2_clk.common,
	&bus_deu0_clk.common,
	&bus_deu1_clk.common,
	&bus_be0_clk.common,
	&bus_be1_clk.common,
	&bus_be2_clk.common,
	&bus_drc0_clk.common,
	&bus_drc1_clk.common,

	&fe0_भाग_clk.common,
	&fe1_भाग_clk.common,
	&fe2_भाग_clk.common,
	&be0_भाग_clk.common,
	&be1_भाग_clk.common,
	&be2_भाग_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun9i_a80_de_hw_clks = अणु
	.hws	= अणु
		[CLK_FE0]	= &fe0_clk.common.hw,
		[CLK_FE1]	= &fe1_clk.common.hw,
		[CLK_FE2]	= &fe2_clk.common.hw,
		[CLK_IEP_DEU0]	= &iep_deu0_clk.common.hw,
		[CLK_IEP_DEU1]	= &iep_deu1_clk.common.hw,
		[CLK_BE0]	= &be0_clk.common.hw,
		[CLK_BE1]	= &be1_clk.common.hw,
		[CLK_BE2]	= &be2_clk.common.hw,
		[CLK_IEP_DRC0]	= &iep_drc0_clk.common.hw,
		[CLK_IEP_DRC1]	= &iep_drc1_clk.common.hw,
		[CLK_MERGE]	= &merge_clk.common.hw,

		[CLK_DRAM_FE0]	= &dram_fe0_clk.common.hw,
		[CLK_DRAM_FE1]	= &dram_fe1_clk.common.hw,
		[CLK_DRAM_FE2]	= &dram_fe2_clk.common.hw,
		[CLK_DRAM_DEU0]	= &dram_deu0_clk.common.hw,
		[CLK_DRAM_DEU1]	= &dram_deu1_clk.common.hw,
		[CLK_DRAM_BE0]	= &dram_be0_clk.common.hw,
		[CLK_DRAM_BE1]	= &dram_be1_clk.common.hw,
		[CLK_DRAM_BE2]	= &dram_be2_clk.common.hw,
		[CLK_DRAM_DRC0]	= &dram_drc0_clk.common.hw,
		[CLK_DRAM_DRC1]	= &dram_drc1_clk.common.hw,

		[CLK_BUS_FE0]	= &bus_fe0_clk.common.hw,
		[CLK_BUS_FE1]	= &bus_fe1_clk.common.hw,
		[CLK_BUS_FE2]	= &bus_fe2_clk.common.hw,
		[CLK_BUS_DEU0]	= &bus_deu0_clk.common.hw,
		[CLK_BUS_DEU1]	= &bus_deu1_clk.common.hw,
		[CLK_BUS_BE0]	= &bus_be0_clk.common.hw,
		[CLK_BUS_BE1]	= &bus_be1_clk.common.hw,
		[CLK_BUS_BE2]	= &bus_be2_clk.common.hw,
		[CLK_BUS_DRC0]	= &bus_drc0_clk.common.hw,
		[CLK_BUS_DRC1]	= &bus_drc1_clk.common.hw,

		[CLK_FE0_DIV]	= &fe0_भाग_clk.common.hw,
		[CLK_FE1_DIV]	= &fe1_भाग_clk.common.hw,
		[CLK_FE2_DIV]	= &fe2_भाग_clk.common.hw,
		[CLK_BE0_DIV]	= &be0_भाग_clk.common.hw,
		[CLK_BE1_DIV]	= &be1_भाग_clk.common.hw,
		[CLK_BE2_DIV]	= &be2_भाग_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun9i_a80_de_resets[] = अणु
	[RST_FE0]	= अणु 0x0c, BIT(0) पूर्ण,
	[RST_FE1]	= अणु 0x0c, BIT(1) पूर्ण,
	[RST_FE2]	= अणु 0x0c, BIT(2) पूर्ण,
	[RST_DEU0]	= अणु 0x0c, BIT(4) पूर्ण,
	[RST_DEU1]	= अणु 0x0c, BIT(5) पूर्ण,
	[RST_BE0]	= अणु 0x0c, BIT(8) पूर्ण,
	[RST_BE1]	= अणु 0x0c, BIT(9) पूर्ण,
	[RST_BE2]	= अणु 0x0c, BIT(10) पूर्ण,
	[RST_DRC0]	= अणु 0x0c, BIT(12) पूर्ण,
	[RST_DRC1]	= अणु 0x0c, BIT(13) पूर्ण,
	[RST_MERGE]	= अणु 0x0c, BIT(20) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun9i_a80_de_clk_desc = अणु
	.ccu_clks	= sun9i_a80_de_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun9i_a80_de_clks),

	.hw_clks	= &sun9i_a80_de_hw_clks,

	.resets		= sun9i_a80_de_resets,
	.num_resets	= ARRAY_SIZE(sun9i_a80_de_resets),
पूर्ण;

अटल पूर्णांक sun9i_a80_de_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा clk *bus_clk;
	काष्ठा reset_control *rstc;
	व्योम __iomem *reg;
	पूर्णांक ret;

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

	rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"Couldn't get reset control: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The bus घड़ी needs to be enabled क्रम us to access the रेजिस्टरs */
	ret = clk_prepare_enable(bus_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable bus clk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The reset control needs to be निश्चितed क्रम the controls to work */
	ret = reset_control_deनिश्चित(rstc);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Couldn't deassert reset control: %d\n", ret);
		जाओ err_disable_clk;
	पूर्ण

	ret = sunxi_ccu_probe(pdev->dev.of_node, reg,
			      &sun9i_a80_de_clk_desc);
	अगर (ret)
		जाओ err_निश्चित_reset;

	वापस 0;

err_निश्चित_reset:
	reset_control_निश्चित(rstc);
err_disable_clk:
	clk_disable_unprepare(bus_clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun9i_a80_de_clk_ids[] = अणु
	अणु .compatible = "allwinner,sun9i-a80-de-clks" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun9i_a80_de_clk_driver = अणु
	.probe	= sun9i_a80_de_clk_probe,
	.driver	= अणु
		.name	= "sun9i-a80-de-clks",
		.of_match_table	= sun9i_a80_de_clk_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun9i_a80_de_clk_driver);
