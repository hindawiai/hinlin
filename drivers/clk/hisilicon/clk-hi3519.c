<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hi3519 Clock Driver
 *
 * Copyright (c) 2015-2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <dt-bindings/घड़ी/hi3519-घड़ी.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "clk.h"
#समावेश "reset.h"

#घोषणा HI3519_INNER_CLK_OFFSET	64
#घोषणा HI3519_FIXED_24M	65
#घोषणा HI3519_FIXED_50M	66
#घोषणा HI3519_FIXED_75M	67
#घोषणा HI3519_FIXED_125M	68
#घोषणा HI3519_FIXED_150M	69
#घोषणा HI3519_FIXED_200M	70
#घोषणा HI3519_FIXED_250M	71
#घोषणा HI3519_FIXED_300M	72
#घोषणा HI3519_FIXED_400M	73
#घोषणा HI3519_FMC_MUX		74

#घोषणा HI3519_NR_CLKS		128

काष्ठा hi3519_crg_data अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	काष्ठा hisi_reset_controller *rstc;
पूर्ण;

अटल स्थिर काष्ठा hisi_fixed_rate_घड़ी hi3519_fixed_rate_clks[] = अणु
	अणु HI3519_FIXED_24M, "24m", शून्य, 0, 24000000, पूर्ण,
	अणु HI3519_FIXED_50M, "50m", शून्य, 0, 50000000, पूर्ण,
	अणु HI3519_FIXED_75M, "75m", शून्य, 0, 75000000, पूर्ण,
	अणु HI3519_FIXED_125M, "125m", शून्य, 0, 125000000, पूर्ण,
	अणु HI3519_FIXED_150M, "150m", शून्य, 0, 150000000, पूर्ण,
	अणु HI3519_FIXED_200M, "200m", शून्य, 0, 200000000, पूर्ण,
	अणु HI3519_FIXED_250M, "250m", शून्य, 0, 250000000, पूर्ण,
	अणु HI3519_FIXED_300M, "300m", शून्य, 0, 300000000, पूर्ण,
	अणु HI3519_FIXED_400M, "400m", शून्य, 0, 400000000, पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर fmc_mux_p[] = अणु
		"24m", "75m", "125m", "150m", "200m", "250m", "300m", "400m", पूर्ण;
अटल u32 fmc_mux_table[] = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण;

अटल स्थिर काष्ठा hisi_mux_घड़ी hi3519_mux_clks[] = अणु
	अणु HI3519_FMC_MUX, "fmc_mux", fmc_mux_p, ARRAY_SIZE(fmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc0, 2, 3, 0, fmc_mux_table, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hisi_gate_घड़ी hi3519_gate_clks[] = अणु
	अणु HI3519_FMC_CLK, "clk_fmc", "fmc_mux",
		CLK_SET_RATE_PARENT, 0xc0, 1, 0, पूर्ण,
	अणु HI3519_UART0_CLK, "clk_uart0", "24m",
		CLK_SET_RATE_PARENT, 0xe4, 20, 0, पूर्ण,
	अणु HI3519_UART1_CLK, "clk_uart1", "24m",
		CLK_SET_RATE_PARENT, 0xe4, 21, 0, पूर्ण,
	अणु HI3519_UART2_CLK, "clk_uart2", "24m",
		CLK_SET_RATE_PARENT, 0xe4, 22, 0, पूर्ण,
	अणु HI3519_UART3_CLK, "clk_uart3", "24m",
		CLK_SET_RATE_PARENT, 0xe4, 23, 0, पूर्ण,
	अणु HI3519_UART4_CLK, "clk_uart4", "24m",
		CLK_SET_RATE_PARENT, 0xe4, 24, 0, पूर्ण,
	अणु HI3519_SPI0_CLK, "clk_spi0", "50m",
		CLK_SET_RATE_PARENT, 0xe4, 16, 0, पूर्ण,
	अणु HI3519_SPI1_CLK, "clk_spi1", "50m",
		CLK_SET_RATE_PARENT, 0xe4, 17, 0, पूर्ण,
	अणु HI3519_SPI2_CLK, "clk_spi2", "50m",
		CLK_SET_RATE_PARENT, 0xe4, 18, 0, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_घड़ी_data *hi3519_clk_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	पूर्णांक ret;

	clk_data = hisi_clk_alloc(pdev, HI3519_NR_CLKS);
	अगर (!clk_data)
		वापस ERR_PTR(-ENOMEM);

	ret = hisi_clk_रेजिस्टर_fixed_rate(hi3519_fixed_rate_clks,
				     ARRAY_SIZE(hi3519_fixed_rate_clks),
				     clk_data);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = hisi_clk_रेजिस्टर_mux(hi3519_mux_clks,
				ARRAY_SIZE(hi3519_mux_clks),
				clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_fixed_rate;

	ret = hisi_clk_रेजिस्टर_gate(hi3519_gate_clks,
				ARRAY_SIZE(hi3519_gate_clks),
				clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_mux;

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_gate;

	वापस clk_data;

unरेजिस्टर_fixed_rate:
	hisi_clk_unरेजिस्टर_fixed_rate(hi3519_fixed_rate_clks,
				ARRAY_SIZE(hi3519_fixed_rate_clks),
				clk_data);

unरेजिस्टर_mux:
	hisi_clk_unरेजिस्टर_mux(hi3519_mux_clks,
				ARRAY_SIZE(hi3519_mux_clks),
				clk_data);
unरेजिस्टर_gate:
	hisi_clk_unरेजिस्टर_gate(hi3519_gate_clks,
				ARRAY_SIZE(hi3519_gate_clks),
				clk_data);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम hi3519_clk_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi3519_crg_data *crg = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unरेजिस्टर_gate(hi3519_gate_clks,
				ARRAY_SIZE(hi3519_mux_clks),
				crg->clk_data);
	hisi_clk_unरेजिस्टर_mux(hi3519_mux_clks,
				ARRAY_SIZE(hi3519_mux_clks),
				crg->clk_data);
	hisi_clk_unरेजिस्टर_fixed_rate(hi3519_fixed_rate_clks,
				ARRAY_SIZE(hi3519_fixed_rate_clks),
				crg->clk_data);
पूर्ण

अटल पूर्णांक hi3519_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi3519_crg_data *crg;

	crg = devm_kदो_स्मृति(&pdev->dev, माप(*crg), GFP_KERNEL);
	अगर (!crg)
		वापस -ENOMEM;

	crg->rstc = hisi_reset_init(pdev);
	अगर (!crg->rstc)
		वापस -ENOMEM;

	crg->clk_data = hi3519_clk_रेजिस्टर(pdev);
	अगर (IS_ERR(crg->clk_data)) अणु
		hisi_reset_निकास(crg->rstc);
		वापस PTR_ERR(crg->clk_data);
	पूर्ण

	platक्रमm_set_drvdata(pdev, crg);
	वापस 0;
पूर्ण

अटल पूर्णांक hi3519_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi3519_crg_data *crg = platक्रमm_get_drvdata(pdev);

	hisi_reset_निकास(crg->rstc);
	hi3519_clk_unरेजिस्टर(pdev);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id hi3519_clk_match_table[] = अणु
	अणु .compatible = "hisilicon,hi3519-crg" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3519_clk_match_table);

अटल काष्ठा platक्रमm_driver hi3519_clk_driver = अणु
	.probe          = hi3519_clk_probe,
	.हटाओ		= hi3519_clk_हटाओ,
	.driver         = अणु
		.name   = "hi3519-clk",
		.of_match_table = hi3519_clk_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi3519_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi3519_clk_driver);
पूर्ण
core_initcall(hi3519_clk_init);

अटल व्योम __निकास hi3519_clk_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hi3519_clk_driver);
पूर्ण
module_निकास(hi3519_clk_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiSilicon Hi3519 Clock Driver");
