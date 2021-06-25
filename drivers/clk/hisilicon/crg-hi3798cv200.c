<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hi3798CV200 Clock and Reset Generator Driver
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <dt-bindings/घड़ी/histb-घड़ी.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "clk.h"
#समावेश "crg.h"
#समावेश "reset.h"

/* hi3798CV200 core CRG */
#घोषणा HI3798CV200_INNER_CLK_OFFSET		64
#घोषणा HI3798CV200_FIXED_24M			65
#घोषणा HI3798CV200_FIXED_25M			66
#घोषणा HI3798CV200_FIXED_50M			67
#घोषणा HI3798CV200_FIXED_75M			68
#घोषणा HI3798CV200_FIXED_100M			69
#घोषणा HI3798CV200_FIXED_150M			70
#घोषणा HI3798CV200_FIXED_200M			71
#घोषणा HI3798CV200_FIXED_250M			72
#घोषणा HI3798CV200_FIXED_300M			73
#घोषणा HI3798CV200_FIXED_400M			74
#घोषणा HI3798CV200_MMC_MUX			75
#घोषणा HI3798CV200_ETH_PUB_CLK			76
#घोषणा HI3798CV200_ETH_BUS_CLK			77
#घोषणा HI3798CV200_ETH_BUS0_CLK		78
#घोषणा HI3798CV200_ETH_BUS1_CLK		79
#घोषणा HI3798CV200_COMBPHY1_MUX		80
#घोषणा HI3798CV200_FIXED_12M			81
#घोषणा HI3798CV200_FIXED_48M			82
#घोषणा HI3798CV200_FIXED_60M			83
#घोषणा HI3798CV200_FIXED_166P5M		84
#घोषणा HI3798CV200_SDIO0_MUX			85
#घोषणा HI3798CV200_COMBPHY0_MUX		86

#घोषणा HI3798CV200_CRG_NR_CLKS			128

अटल स्थिर काष्ठा hisi_fixed_rate_घड़ी hi3798cv200_fixed_rate_clks[] = अणु
	अणु HISTB_OSC_CLK, "clk_osc", शून्य, 0, 24000000, पूर्ण,
	अणु HISTB_APB_CLK, "clk_apb", शून्य, 0, 100000000, पूर्ण,
	अणु HISTB_AHB_CLK, "clk_ahb", शून्य, 0, 200000000, पूर्ण,
	अणु HI3798CV200_FIXED_12M, "12m", शून्य, 0, 12000000, पूर्ण,
	अणु HI3798CV200_FIXED_24M, "24m", शून्य, 0, 24000000, पूर्ण,
	अणु HI3798CV200_FIXED_25M, "25m", शून्य, 0, 25000000, पूर्ण,
	अणु HI3798CV200_FIXED_48M, "48m", शून्य, 0, 48000000, पूर्ण,
	अणु HI3798CV200_FIXED_50M, "50m", शून्य, 0, 50000000, पूर्ण,
	अणु HI3798CV200_FIXED_60M, "60m", शून्य, 0, 60000000, पूर्ण,
	अणु HI3798CV200_FIXED_75M, "75m", शून्य, 0, 75000000, पूर्ण,
	अणु HI3798CV200_FIXED_100M, "100m", शून्य, 0, 100000000, पूर्ण,
	अणु HI3798CV200_FIXED_150M, "150m", शून्य, 0, 150000000, पूर्ण,
	अणु HI3798CV200_FIXED_166P5M, "166p5m", शून्य, 0, 165000000, पूर्ण,
	अणु HI3798CV200_FIXED_200M, "200m", शून्य, 0, 200000000, पूर्ण,
	अणु HI3798CV200_FIXED_250M, "250m", शून्य, 0, 250000000, पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर mmc_mux_p[] = अणु
		"100m", "50m", "25m", "200m", "150m" पूर्ण;
अटल u32 mmc_mux_table[] = अणु0, 1, 2, 3, 6पूर्ण;

अटल स्थिर अक्षर *स्थिर comphy_mux_p[] = अणु
		"100m", "25m"पूर्ण;
अटल u32 comphy_mux_table[] = अणु2, 3पूर्ण;

अटल स्थिर अक्षर *स्थिर sdio_mux_p[] = अणु
		"100m", "50m", "150m", "166p5m" पूर्ण;
अटल u32 sdio_mux_table[] = अणु0, 1, 2, 3पूर्ण;

अटल काष्ठा hisi_mux_घड़ी hi3798cv200_mux_clks[] = अणु
	अणु HI3798CV200_MMC_MUX, "mmc_mux", mmc_mux_p, ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xa0, 8, 3, 0, mmc_mux_table, पूर्ण,
	अणु HI3798CV200_COMBPHY0_MUX, "combphy0_mux",
		comphy_mux_p, ARRAY_SIZE(comphy_mux_p),
		CLK_SET_RATE_PARENT, 0x188, 2, 2, 0, comphy_mux_table, पूर्ण,
	अणु HI3798CV200_COMBPHY1_MUX, "combphy1_mux",
		comphy_mux_p, ARRAY_SIZE(comphy_mux_p),
		CLK_SET_RATE_PARENT, 0x188, 10, 2, 0, comphy_mux_table, पूर्ण,
	अणु HI3798CV200_SDIO0_MUX, "sdio0_mux", sdio_mux_p,
		ARRAY_SIZE(sdio_mux_p), CLK_SET_RATE_PARENT,
		0x9c, 8, 2, 0, sdio_mux_table, पूर्ण,
पूर्ण;

अटल u32 mmc_phase_regvals[] = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण;
अटल u32 mmc_phase_degrees[] = अणु0, 45, 90, 135, 180, 225, 270, 315पूर्ण;

अटल काष्ठा hisi_phase_घड़ी hi3798cv200_phase_clks[] = अणु
	अणु HISTB_MMC_SAMPLE_CLK, "mmc_sample", "clk_mmc_ciu",
		CLK_SET_RATE_PARENT, 0xa0, 12, 3, mmc_phase_degrees,
		mmc_phase_regvals, ARRAY_SIZE(mmc_phase_regvals) पूर्ण,
	अणु HISTB_MMC_DRV_CLK, "mmc_drive", "clk_mmc_ciu",
		CLK_SET_RATE_PARENT, 0xa0, 16, 3, mmc_phase_degrees,
		mmc_phase_regvals, ARRAY_SIZE(mmc_phase_regvals) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hisi_gate_घड़ी hi3798cv200_gate_clks[] = अणु
	/* UART */
	अणु HISTB_UART2_CLK, "clk_uart2", "75m",
		CLK_SET_RATE_PARENT, 0x68, 4, 0, पूर्ण,
	/* I2C */
	अणु HISTB_I2C0_CLK, "clk_i2c0", "clk_apb",
		CLK_SET_RATE_PARENT, 0x6C, 4, 0, पूर्ण,
	अणु HISTB_I2C1_CLK, "clk_i2c1", "clk_apb",
		CLK_SET_RATE_PARENT, 0x6C, 8, 0, पूर्ण,
	अणु HISTB_I2C2_CLK, "clk_i2c2", "clk_apb",
		CLK_SET_RATE_PARENT, 0x6C, 12, 0, पूर्ण,
	अणु HISTB_I2C3_CLK, "clk_i2c3", "clk_apb",
		CLK_SET_RATE_PARENT, 0x6C, 16, 0, पूर्ण,
	अणु HISTB_I2C4_CLK, "clk_i2c4", "clk_apb",
		CLK_SET_RATE_PARENT, 0x6C, 20, 0, पूर्ण,
	/* SPI */
	अणु HISTB_SPI0_CLK, "clk_spi0", "clk_apb",
		CLK_SET_RATE_PARENT, 0x70, 0, 0, पूर्ण,
	/* SDIO */
	अणु HISTB_SDIO0_BIU_CLK, "clk_sdio0_biu", "200m",
			CLK_SET_RATE_PARENT, 0x9c, 0, 0, पूर्ण,
	अणु HISTB_SDIO0_CIU_CLK, "clk_sdio0_ciu", "sdio0_mux",
		CLK_SET_RATE_PARENT, 0x9c, 1, 0, पूर्ण,
	/* EMMC */
	अणु HISTB_MMC_BIU_CLK, "clk_mmc_biu", "200m",
		CLK_SET_RATE_PARENT, 0xa0, 0, 0, पूर्ण,
	अणु HISTB_MMC_CIU_CLK, "clk_mmc_ciu", "mmc_mux",
		CLK_SET_RATE_PARENT, 0xa0, 1, 0, पूर्ण,
	/* PCIE*/
	अणु HISTB_PCIE_BUS_CLK, "clk_pcie_bus", "200m",
		CLK_SET_RATE_PARENT, 0x18c, 0, 0, पूर्ण,
	अणु HISTB_PCIE_SYS_CLK, "clk_pcie_sys", "100m",
		CLK_SET_RATE_PARENT, 0x18c, 1, 0, पूर्ण,
	अणु HISTB_PCIE_PIPE_CLK, "clk_pcie_pipe", "250m",
		CLK_SET_RATE_PARENT, 0x18c, 2, 0, पूर्ण,
	अणु HISTB_PCIE_AUX_CLK, "clk_pcie_aux", "24m",
		CLK_SET_RATE_PARENT, 0x18c, 3, 0, पूर्ण,
	/* Ethernet */
	अणु HI3798CV200_ETH_PUB_CLK, "clk_pub", शून्य,
		CLK_SET_RATE_PARENT, 0xcc, 5, 0, पूर्ण,
	अणु HI3798CV200_ETH_BUS_CLK, "clk_bus", "clk_pub",
		CLK_SET_RATE_PARENT, 0xcc, 0, 0, पूर्ण,
	अणु HI3798CV200_ETH_BUS0_CLK, "clk_bus_m0", "clk_bus",
		CLK_SET_RATE_PARENT, 0xcc, 1, 0, पूर्ण,
	अणु HI3798CV200_ETH_BUS1_CLK, "clk_bus_m1", "clk_bus",
		CLK_SET_RATE_PARENT, 0xcc, 2, 0, पूर्ण,
	अणु HISTB_ETH0_MAC_CLK, "clk_mac0", "clk_bus_m0",
		CLK_SET_RATE_PARENT, 0xcc, 3, 0, पूर्ण,
	अणु HISTB_ETH0_MACIF_CLK, "clk_macif0", "clk_bus_m0",
		CLK_SET_RATE_PARENT, 0xcc, 24, 0, पूर्ण,
	अणु HISTB_ETH1_MAC_CLK, "clk_mac1", "clk_bus_m1",
		CLK_SET_RATE_PARENT, 0xcc, 4, 0, पूर्ण,
	अणु HISTB_ETH1_MACIF_CLK, "clk_macif1", "clk_bus_m1",
		CLK_SET_RATE_PARENT, 0xcc, 25, 0, पूर्ण,
	/* COMBPHY0 */
	अणु HISTB_COMBPHY0_CLK, "clk_combphy0", "combphy0_mux",
		CLK_SET_RATE_PARENT, 0x188, 0, 0, पूर्ण,
	/* COMBPHY1 */
	अणु HISTB_COMBPHY1_CLK, "clk_combphy1", "combphy1_mux",
		CLK_SET_RATE_PARENT, 0x188, 8, 0, पूर्ण,
	/* USB2 */
	अणु HISTB_USB2_BUS_CLK, "clk_u2_bus", "clk_ahb",
		CLK_SET_RATE_PARENT, 0xb8, 0, 0, पूर्ण,
	अणु HISTB_USB2_PHY_CLK, "clk_u2_phy", "60m",
		CLK_SET_RATE_PARENT, 0xb8, 4, 0, पूर्ण,
	अणु HISTB_USB2_12M_CLK, "clk_u2_12m", "12m",
		CLK_SET_RATE_PARENT, 0xb8, 2, 0 पूर्ण,
	अणु HISTB_USB2_48M_CLK, "clk_u2_48m", "48m",
		CLK_SET_RATE_PARENT, 0xb8, 1, 0 पूर्ण,
	अणु HISTB_USB2_UTMI_CLK, "clk_u2_utmi", "60m",
		CLK_SET_RATE_PARENT, 0xb8, 5, 0 पूर्ण,
	अणु HISTB_USB2_OTG_UTMI_CLK, "clk_u2_otg_utmi", "60m",
		CLK_SET_RATE_PARENT, 0xb8, 3, 0 पूर्ण,
	अणु HISTB_USB2_PHY1_REF_CLK, "clk_u2_phy1_ref", "24m",
		CLK_SET_RATE_PARENT, 0xbc, 0, 0 पूर्ण,
	अणु HISTB_USB2_PHY2_REF_CLK, "clk_u2_phy2_ref", "24m",
		CLK_SET_RATE_PARENT, 0xbc, 2, 0 पूर्ण,
	/* USB3 */
	अणु HISTB_USB3_BUS_CLK, "clk_u3_bus", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 0, 0 पूर्ण,
	अणु HISTB_USB3_UTMI_CLK, "clk_u3_utmi", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 4, 0 पूर्ण,
	अणु HISTB_USB3_PIPE_CLK, "clk_u3_pipe", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 3, 0 पूर्ण,
	अणु HISTB_USB3_SUSPEND_CLK, "clk_u3_suspend", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 2, 0 पूर्ण,
	अणु HISTB_USB3_BUS_CLK1, "clk_u3_bus1", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 16, 0 पूर्ण,
	अणु HISTB_USB3_UTMI_CLK1, "clk_u3_utmi1", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 20, 0 पूर्ण,
	अणु HISTB_USB3_PIPE_CLK1, "clk_u3_pipe1", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 19, 0 पूर्ण,
	अणु HISTB_USB3_SUSPEND_CLK1, "clk_u3_suspend1", शून्य,
		CLK_SET_RATE_PARENT, 0xb0, 18, 0 पूर्ण,
पूर्ण;

अटल काष्ठा hisi_घड़ी_data *hi3798cv200_clk_रेजिस्टर(
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	पूर्णांक ret;

	clk_data = hisi_clk_alloc(pdev, HI3798CV200_CRG_NR_CLKS);
	अगर (!clk_data)
		वापस ERR_PTR(-ENOMEM);

	/* hisi_phase_घड़ी is resource managed */
	ret = hisi_clk_रेजिस्टर_phase(&pdev->dev,
				hi3798cv200_phase_clks,
				ARRAY_SIZE(hi3798cv200_phase_clks),
				clk_data);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = hisi_clk_रेजिस्टर_fixed_rate(hi3798cv200_fixed_rate_clks,
				     ARRAY_SIZE(hi3798cv200_fixed_rate_clks),
				     clk_data);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = hisi_clk_रेजिस्टर_mux(hi3798cv200_mux_clks,
				ARRAY_SIZE(hi3798cv200_mux_clks),
				clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_fixed_rate;

	ret = hisi_clk_रेजिस्टर_gate(hi3798cv200_gate_clks,
				ARRAY_SIZE(hi3798cv200_gate_clks),
				clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_mux;

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_gate;

	वापस clk_data;

unरेजिस्टर_gate:
	hisi_clk_unरेजिस्टर_gate(hi3798cv200_gate_clks,
				ARRAY_SIZE(hi3798cv200_gate_clks),
				clk_data);
unरेजिस्टर_mux:
	hisi_clk_unरेजिस्टर_mux(hi3798cv200_mux_clks,
				ARRAY_SIZE(hi3798cv200_mux_clks),
				clk_data);
unरेजिस्टर_fixed_rate:
	hisi_clk_unरेजिस्टर_fixed_rate(hi3798cv200_fixed_rate_clks,
				ARRAY_SIZE(hi3798cv200_fixed_rate_clks),
				clk_data);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम hi3798cv200_clk_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unरेजिस्टर_gate(hi3798cv200_gate_clks,
				ARRAY_SIZE(hi3798cv200_gate_clks),
				crg->clk_data);
	hisi_clk_unरेजिस्टर_mux(hi3798cv200_mux_clks,
				ARRAY_SIZE(hi3798cv200_mux_clks),
				crg->clk_data);
	hisi_clk_unरेजिस्टर_fixed_rate(hi3798cv200_fixed_rate_clks,
				ARRAY_SIZE(hi3798cv200_fixed_rate_clks),
				crg->clk_data);
पूर्ण

अटल स्थिर काष्ठा hisi_crg_funcs hi3798cv200_crg_funcs = अणु
	.रेजिस्टर_clks = hi3798cv200_clk_रेजिस्टर,
	.unरेजिस्टर_clks = hi3798cv200_clk_unरेजिस्टर,
पूर्ण;

/* hi3798CV200 sysctrl CRG */

#घोषणा HI3798CV200_SYSCTRL_NR_CLKS 16

अटल स्थिर काष्ठा hisi_gate_घड़ी hi3798cv200_sysctrl_gate_clks[] = अणु
	अणु HISTB_IR_CLK, "clk_ir", "24m",
		CLK_SET_RATE_PARENT, 0x48, 4, 0, पूर्ण,
	अणु HISTB_TIMER01_CLK, "clk_timer01", "24m",
		CLK_SET_RATE_PARENT, 0x48, 6, 0, पूर्ण,
	अणु HISTB_UART0_CLK, "clk_uart0", "75m",
		CLK_SET_RATE_PARENT, 0x48, 10, 0, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_घड़ी_data *hi3798cv200_sysctrl_clk_रेजिस्टर(
					काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	पूर्णांक ret;

	clk_data = hisi_clk_alloc(pdev, HI3798CV200_SYSCTRL_NR_CLKS);
	अगर (!clk_data)
		वापस ERR_PTR(-ENOMEM);

	ret = hisi_clk_रेजिस्टर_gate(hi3798cv200_sysctrl_gate_clks,
				ARRAY_SIZE(hi3798cv200_sysctrl_gate_clks),
				clk_data);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	अगर (ret)
		जाओ unरेजिस्टर_gate;

	वापस clk_data;

unरेजिस्टर_gate:
	hisi_clk_unरेजिस्टर_gate(hi3798cv200_sysctrl_gate_clks,
				ARRAY_SIZE(hi3798cv200_sysctrl_gate_clks),
				clk_data);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम hi3798cv200_sysctrl_clk_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unरेजिस्टर_gate(hi3798cv200_sysctrl_gate_clks,
				ARRAY_SIZE(hi3798cv200_sysctrl_gate_clks),
				crg->clk_data);
पूर्ण

अटल स्थिर काष्ठा hisi_crg_funcs hi3798cv200_sysctrl_funcs = अणु
	.रेजिस्टर_clks = hi3798cv200_sysctrl_clk_रेजिस्टर,
	.unरेजिस्टर_clks = hi3798cv200_sysctrl_clk_unरेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hi3798cv200_crg_match_table[] = अणु
	अणु .compatible = "hisilicon,hi3798cv200-crg",
		.data = &hi3798cv200_crg_funcs पूर्ण,
	अणु .compatible = "hisilicon,hi3798cv200-sysctrl",
		.data = &hi3798cv200_sysctrl_funcs पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3798cv200_crg_match_table);

अटल पूर्णांक hi3798cv200_crg_probe(काष्ठा platक्रमm_device *pdev)
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

अटल पूर्णांक hi3798cv200_crg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_crg_dev *crg = platक्रमm_get_drvdata(pdev);

	hisi_reset_निकास(crg->rstc);
	crg->funcs->unरेजिस्टर_clks(pdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hi3798cv200_crg_driver = अणु
	.probe          = hi3798cv200_crg_probe,
	.हटाओ		= hi3798cv200_crg_हटाओ,
	.driver         = अणु
		.name   = "hi3798cv200-crg",
		.of_match_table = hi3798cv200_crg_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi3798cv200_crg_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi3798cv200_crg_driver);
पूर्ण
core_initcall(hi3798cv200_crg_init);

अटल व्योम __निकास hi3798cv200_crg_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hi3798cv200_crg_driver);
पूर्ण
module_निकास(hi3798cv200_crg_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiSilicon Hi3798CV200 CRG Driver");
