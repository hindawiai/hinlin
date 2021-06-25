<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hi3516CV300 Clock and Reset Generator Driver
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <dt-bindings/घड़ी/hi3516cv300-घड़ी.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "clk.h"
#समावेश "crg.h"
#समावेश "reset.h"

/* hi3516CV300 core CRG */
#घोषणा HI3516CV300_INNER_CLK_OFFSET	64
#घोषणा HI3516CV300_FIXED_3M		65
#घोषणा HI3516CV300_FIXED_6M		66
#घोषणा HI3516CV300_FIXED_24M		67
#घोषणा HI3516CV300_FIXED_49P5		68
#घोषणा HI3516CV300_FIXED_50M		69
#घोषणा HI3516CV300_FIXED_83P3M		70
#घोषणा HI3516CV300_FIXED_99M		71
#घोषणा HI3516CV300_FIXED_100M		72
#घोषणा HI3516CV300_FIXED_148P5M	73
#घोषणा HI3516CV300_FIXED_198M		74
#घोषणा HI3516CV300_FIXED_297M		75
#घोषणा HI3516CV300_UART_MUX		76
#घोषणा HI3516CV300_FMC_MUX		77
#घोषणा HI3516CV300_MMC0_MUX		78
#घोषणा HI3516CV300_MMC1_MUX		79
#घोषणा HI3516CV300_MMC2_MUX		80
#घोषणा HI3516CV300_MMC3_MUX		81
#घोषणा HI3516CV300_PWM_MUX		82
#घोषणा HI3516CV300_CRG_NR_CLKS		128

अटल स्थिर काष्ठा hisi_fixed_rate_घड़ी hi3516cv300_fixed_rate_clks[] = अणु
	अणु HI3516CV300_FIXED_3M, "3m", शून्य, 0, 3000000, पूर्ण,
	अणु HI3516CV300_FIXED_6M, "6m", शून्य, 0, 6000000, पूर्ण,
	अणु HI3516CV300_FIXED_24M, "24m", शून्य, 0, 24000000, पूर्ण,
	अणु HI3516CV300_FIXED_49P5, "49.5m", शून्य, 0, 49500000, पूर्ण,
	अणु HI3516CV300_FIXED_50M, "50m", शून्य, 0, 50000000, पूर्ण,
	अणु HI3516CV300_FIXED_83P3M, "83.3m", शून्य, 0, 83300000, पूर्ण,
	अणु HI3516CV300_FIXED_99M, "99m", शून्य, 0, 99000000, पूर्ण,
	अणु HI3516CV300_FIXED_100M, "100m", शून्य, 0, 100000000, पूर्ण,
	अणु HI3516CV300_FIXED_148P5M, "148.5m", शून्य, 0, 148500000, पूर्ण,
	अणु HI3516CV300_FIXED_198M, "198m", शून्य, 0, 198000000, पूर्ण,
	अणु HI3516CV300_FIXED_297M, "297m", शून्य, 0, 297000000, पूर्ण,
	अणु HI3516CV300_APB_CLK, "apb", शून्य, 0, 50000000, पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart_mux_p[] = अणु"24m", "6m"पूर्ण;
अटल स्थिर अक्षर *स्थिर fmc_mux_p[] = अणु
	"24m", "83.3m", "148.5m", "198m", "297m"
पूर्ण;
अटल स्थिर अक्षर *स्थिर mmc_mux_p[] = अणु"49.5m"पूर्ण;
अटल स्थिर अक्षर *स्थिर mmc2_mux_p[] = अणु"99m", "49.5m"पूर्ण;
अटल स्थिर अक्षर *स्थिर pwm_mux_p[] = अणु"3m", "50m", "24m", "24m"पूर्ण;

अटल u32 uart_mux_table[] = अणु0, 1पूर्ण;
अटल u32 fmc_mux_table[] = अणु0, 1, 2, 3, 4पूर्ण;
अटल u32 mmc_mux_table[] = अणु0पूर्ण;
अटल u32 mmc2_mux_table[] = अणु0, 2पूर्ण;
अटल u32 pwm_mux_table[] = अणु0, 1, 2, 3पूर्ण;

अटल स्थिर काष्ठा hisi_mux_घड़ी hi3516cv300_mux_clks[] = अणु
	अणु HI3516CV300_UART_MUX, "uart_mux", uart_mux_p, ARRAY_SIZE(uart_mux_p),
		CLK_SET_RATE_PARENT, 0xe4, 19, 1, 0, uart_mux_table, पूर्ण,
	अणु HI3516CV300_FMC_MUX, "fmc_mux", fmc_mux_p, ARRAY_SIZE(fmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc0, 2, 3, 0, fmc_mux_table, पूर्ण,
	अणु HI3516CV300_MMC0_MUX, "mmc0_mux", mmc_mux_p, ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc4, 4, 2, 0, mmc_mux_table, पूर्ण,
	अणु HI3516CV300_MMC1_MUX, "mmc1_mux", mmc_mux_p, ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc4, 12, 2, 0, mmc_mux_table, पूर्ण,
	अणु HI3516CV300_MMC2_MUX, "mmc2_mux", mmc2_mux_p, ARRAY_SIZE(mmc2_mux_p),
		CLK_SET_RATE_PARENT, 0xc4, 20, 2, 0, mmc2_mux_table, पूर्ण,
	अणु HI3516CV300_MMC3_MUX, "mmc3_mux", mmc_mux_p, ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc8, 4, 2, 0, mmc_mux_table, पूर्ण,
	अणु HI3516CV300_PWM_MUX, "pwm_mux", pwm_mux_p, ARRAY_SIZE(pwm_mux_p),
		CLK_SET_RATE_PARENT, 0x38, 2, 2, 0, pwm_mux_table, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hisi_gate_घड़ी hi3516cv300_gate_clks[] = अणु

	अणु HI3516CV300_UART0_CLK, "clk_uart0", "uart_mux", CLK_SET_RATE_PARENT,
		0xe4, 15, 0, पूर्ण,
	अणु HI3516CV300_UART1_CLK, "clk_uart1", "uart_mux", CLK_SET_RATE_PARENT,
		0xe4, 16, 0, पूर्ण,
	अणु HI3516CV300_UART2_CLK, "clk_uart2", "uart_mux", CLK_SET_RATE_PARENT,
		0xe4, 17, 0, पूर्ण,

	अणु HI3516CV300_SPI0_CLK, "clk_spi0", "100m", CLK_SET_RATE_PARENT,
		0xe4, 13, 0, पूर्ण,
	अणु HI3516CV300_SPI1_CLK, "clk_spi1", "100m", CLK_SET_RATE_PARENT,
		0xe4, 14, 0, पूर्ण,

	अणु HI3516CV300_FMC_CLK, "clk_fmc", "fmc_mux", CLK_SET_RATE_PARENT,
		0xc0, 1, 0, पूर्ण,
	अणु HI3516CV300_MMC0_CLK, "clk_mmc0", "mmc0_mux", CLK_SET_RATE_PARENT,
		0xc4, 1, 0, पूर्ण,
	अणु HI3516CV300_MMC1_CLK, "clk_mmc1", "mmc1_mux", CLK_SET_RATE_PARENT,
		0xc4, 9, 0, पूर्ण,
	अणु HI3516CV300_MMC2_CLK, "clk_mmc2", "mmc2_mux", CLK_SET_RATE_PARENT,
		0xc4, 17, 0, पूर्ण,
	अणु HI3516CV300_MMC3_CLK, "clk_mmc3", "mmc3_mux", CLK_SET_RATE_PARENT,
		0xc8, 1, 0, पूर्ण,

	अणु HI3516CV300_ETH_CLK, "clk_eth", शून्य, 0, 0xec, 1, 0, पूर्ण,

	अणु HI3516CV300_DMAC_CLK, "clk_dmac", शून्य, 0, 0xd8, 5, 0, पूर्ण,
	अणु HI3516CV300_PWM_CLK, "clk_pwm", "pwm_mux", CLK_SET_RATE_PARENT,
		0x38, 1, 0, पूर्ण,

	अणु HI3516CV300_USB2_BUS_CLK, "clk_usb2_bus", शून्य, 0, 0xb8, 0, 0, पूर्ण,
	अणु HI3516CV300_USB2_OHCI48M_CLK, "clk_usb2_ohci48m", शून्य, 0,
		0xb8, 1, 0, पूर्ण,
	अणु HI3516CV300_USB2_OHCI12M_CLK, "clk_usb2_ohci12m", शून्य, 0,
		0xb8, 2, 0, पूर्ण,
	अणु HI3516CV300_USB2_OTG_UTMI_CLK, "clk_usb2_otg_utmi", शून्य, 0,
		0xb8, 3, 0, पूर्ण,
	अणु HI3516CV300_USB2_HST_PHY_CLK, "clk_usb2_hst_phy", शून्य, 0,
		0xb8, 4, 0, पूर्ण,
	अणु HI3516CV300_USB2_UTMI0_CLK, "clk_usb2_utmi0", शून्य, 0, 0xb8, 5, 0, पूर्ण,
	अणु HI3516CV300_USB2_PHY_CLK, "clk_usb2_phy", शून्य, 0, 0xb8, 7, 0, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_घड़ी_data *hi3516cv300_clk_रेजिस्टर(
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	पूर्णांक ret;

	clk_data = hisi_clk_alloc(pdev, HI3516CV300_CRG_NR_CLKS);
	अगर (!clk_data)
		वापस ERR_PTR(-ENOMEM);

	ret = hisi_clk_रेजिस्टर_fixed_rate(hi3516cv300_fixed_rate_clks,
			ARRAY_SIZE(hi3516cv300_fixed_rate_clks), clk_data);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = hisi_clk_रेजिस्टर_mux(hi3516cv300_mux_clks,
			ARRAY_SIZE(hi3516cv300_mux_clks), clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_fixed_rate;

	ret = hisi_clk_रेजिस्टर_gate(hi3516cv300_gate_clks,
			ARRAY_SIZE(hi3516cv300_gate_clks), clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_mux;

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_gate;

	वापस clk_data;

unरेजिस्टर_gate:
	hisi_clk_unरेजिस्टर_gate(hi3516cv300_gate_clks,
				ARRAY_SIZE(hi3516cv300_gate_clks), clk_data);
unरेजिस्टर_mux:
	hisi_clk_unरेजिस्टर_mux(hi3516cv300_mux_clks,
			ARRAY_SIZE(hi3516cv300_mux_clks), clk_data);
unरेजिस्टर_fixed_rate:
	hisi_clk_unरेजिस्टर_fixed_rate(hi3516cv300_fixed_rate_clks,
			ARRAY_SIZE(hi3516cv300_fixed_rate_clks), clk_data);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम hi3516cv300_clk_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unरेजिस्टर_gate(hi3516cv300_gate_clks,
			ARRAY_SIZE(hi3516cv300_gate_clks), crg->clk_data);
	hisi_clk_unरेजिस्टर_mux(hi3516cv300_mux_clks,
			ARRAY_SIZE(hi3516cv300_mux_clks), crg->clk_data);
	hisi_clk_unरेजिस्टर_fixed_rate(hi3516cv300_fixed_rate_clks,
			ARRAY_SIZE(hi3516cv300_fixed_rate_clks), crg->clk_data);
पूर्ण

अटल स्थिर काष्ठा hisi_crg_funcs hi3516cv300_crg_funcs = अणु
	.रेजिस्टर_clks = hi3516cv300_clk_रेजिस्टर,
	.unरेजिस्टर_clks = hi3516cv300_clk_unरेजिस्टर,
पूर्ण;

/* hi3516CV300 sysctrl CRG */
#घोषणा HI3516CV300_SYSCTRL_NR_CLKS 16

अटल स्थिर अक्षर *स्थिर wdt_mux_p[] __initस्थिर = अणु "3m", "apb" पूर्ण;
अटल u32 wdt_mux_table[] = अणु0, 1पूर्ण;

अटल स्थिर काष्ठा hisi_mux_घड़ी hi3516cv300_sysctrl_mux_clks[] = अणु
	अणु HI3516CV300_WDT_CLK, "wdt", wdt_mux_p, ARRAY_SIZE(wdt_mux_p),
		CLK_SET_RATE_PARENT, 0x0, 23, 1, 0, wdt_mux_table, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_घड़ी_data *hi3516cv300_sysctrl_clk_रेजिस्टर(
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	पूर्णांक ret;

	clk_data = hisi_clk_alloc(pdev, HI3516CV300_SYSCTRL_NR_CLKS);
	अगर (!clk_data)
		वापस ERR_PTR(-ENOMEM);

	ret = hisi_clk_रेजिस्टर_mux(hi3516cv300_sysctrl_mux_clks,
			ARRAY_SIZE(hi3516cv300_sysctrl_mux_clks), clk_data);
	अगर (ret)
		वापस ERR_PTR(ret);


	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_mux;

	वापस clk_data;

unरेजिस्टर_mux:
	hisi_clk_unरेजिस्टर_mux(hi3516cv300_sysctrl_mux_clks,
			ARRAY_SIZE(hi3516cv300_sysctrl_mux_clks), clk_data);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम hi3516cv300_sysctrl_clk_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unरेजिस्टर_mux(hi3516cv300_sysctrl_mux_clks,
			ARRAY_SIZE(hi3516cv300_sysctrl_mux_clks),
			crg->clk_data);
पूर्ण

अटल स्थिर काष्ठा hisi_crg_funcs hi3516cv300_sysctrl_funcs = अणु
	.रेजिस्टर_clks = hi3516cv300_sysctrl_clk_रेजिस्टर,
	.unरेजिस्टर_clks = hi3516cv300_sysctrl_clk_unरेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hi3516cv300_crg_match_table[] = अणु
	अणु
		.compatible = "hisilicon,hi3516cv300-crg",
		.data = &hi3516cv300_crg_funcs
	पूर्ण,
	अणु
		.compatible = "hisilicon,hi3516cv300-sysctrl",
		.data = &hi3516cv300_sysctrl_funcs
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3516cv300_crg_match_table);

अटल पूर्णांक hi3516cv300_crg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg;

	crg = devm_kदो_स्मृति(&pdev->dev, माप(*crg), GFP_KERNEL);
	अगर (!crg)
		वापस -ENOMEM;

	crg->funcs = of_device_get_match_data(&pdev->dev);
	अगर (!crg->funcs)
		वापस -ENOENT;

	crg->rstc = hisi_reset_init(pdev);
	अगर (!crg->rstc)
		वापस -ENOMEM;

	crg->clk_data = crg->funcs->रेजिस्टर_clks(pdev);
	अगर (IS_ERR(crg->clk_data)) अणु
		hisi_reset_निकास(crg->rstc);
		वापस PTR_ERR(crg->clk_data);
	पूर्ण

	platक्रमm_set_drvdata(pdev, crg);
	वापस 0;
पूर्ण

अटल पूर्णांक hi3516cv300_crg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg = platक्रमm_get_drvdata(pdev);

	hisi_reset_निकास(crg->rstc);
	crg->funcs->unरेजिस्टर_clks(pdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hi3516cv300_crg_driver = अणु
	.probe          = hi3516cv300_crg_probe,
	.हटाओ		= hi3516cv300_crg_हटाओ,
	.driver         = अणु
		.name   = "hi3516cv300-crg",
		.of_match_table = hi3516cv300_crg_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi3516cv300_crg_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi3516cv300_crg_driver);
पूर्ण
core_initcall(hi3516cv300_crg_init);

अटल व्योम __निकास hi3516cv300_crg_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hi3516cv300_crg_driver);
पूर्ण
module_निकास(hi3516cv300_crg_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiSilicon Hi3516CV300 CRG Driver");
