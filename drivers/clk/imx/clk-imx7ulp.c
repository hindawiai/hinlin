<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *
 * Author: Dong Aisheng <aisheng.करोng@nxp.com>
 *
 */

#समावेश <dt-bindings/घड़ी/imx7ulp-घड़ी.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

अटल स्थिर अक्षर * स्थिर pll_pre_sels[]	= अणु "sosc", "firc", पूर्ण;
अटल स्थिर अक्षर * स्थिर spll_pfd_sels[]	= अणु "spll_pfd0", "spll_pfd1", "spll_pfd2", "spll_pfd3", पूर्ण;
अटल स्थिर अक्षर * स्थिर spll_sels[]		= अणु "spll", "spll_pfd_sel", पूर्ण;
अटल स्थिर अक्षर * स्थिर apll_pfd_sels[]	= अणु "apll_pfd0", "apll_pfd1", "apll_pfd2", "apll_pfd3", पूर्ण;
अटल स्थिर अक्षर * स्थिर apll_sels[]		= अणु "apll", "apll_pfd_sel", पूर्ण;
अटल स्थिर अक्षर * स्थिर scs_sels[]		= अणु "dummy", "sosc", "sirc", "firc", "dummy", "apll_sel", "spll_sel", "dummy", पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_sels[]		= अणु "apll_pfd_sel", "dummy", "dummy", "dummy", पूर्ण;
अटल स्थिर अक्षर * स्थिर nic_sels[]		= अणु "firc", "ddr_clk", पूर्ण;
अटल स्थिर अक्षर * स्थिर periph_plat_sels[]	= अणु "dummy", "nic1_bus_clk", "nic1_clk", "ddr_clk", "apll_pfd2", "apll_pfd1", "apll_pfd0", "upll", पूर्ण;
अटल स्थिर अक्षर * स्थिर periph_bus_sels[]	= अणु "dummy", "sosc_bus_clk", "dummy", "firc_bus_clk", "rosc", "nic1_bus_clk", "nic1_clk", "spll_bus_clk", पूर्ण;
अटल स्थिर अक्षर * स्थिर arm_sels[]		= अणु "core", "dummy", "dummy", "hsrun_core", पूर्ण;

/* used by sosc/sirc/firc/ddr/spll/apll भागiders */
अटल स्थिर काष्ठा clk_भाग_प्रकारable ulp_भाग_प्रकारable[] = अणु
	अणु .val = 1, .भाग = 1, पूर्ण,
	अणु .val = 2, .भाग = 2, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु .val = 4, .भाग = 8, पूर्ण,
	अणु .val = 5, .भाग = 16, पूर्ण,
	अणु .val = 6, .भाग = 32, पूर्ण,
	अणु .val = 7, .भाग = 64, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल व्योम __init imx7ulp_clk_scg1_init(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा clk_hw **hws;
	व्योम __iomem *base;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, IMX7ULP_CLK_SCG1_END),
			   GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->num = IMX7ULP_CLK_SCG1_END;
	hws = clk_data->hws;

	hws[IMX7ULP_CLK_DUMMY]		= imx_clk_hw_fixed("dummy", 0);

	hws[IMX7ULP_CLK_ROSC]		= imx_obtain_fixed_clk_hw(np, "rosc");
	hws[IMX7ULP_CLK_SOSC]		= imx_obtain_fixed_clk_hw(np, "sosc");
	hws[IMX7ULP_CLK_SIRC]		= imx_obtain_fixed_clk_hw(np, "sirc");
	hws[IMX7ULP_CLK_FIRC]		= imx_obtain_fixed_clk_hw(np, "firc");
	hws[IMX7ULP_CLK_UPLL]		= imx_obtain_fixed_clk_hw(np, "upll");

	/* SCG1 */
	base = of_iomap(np, 0);
	WARN_ON(!base);

	/* NOTE: xPLL config can't be changed when xPLL is enabled */
	hws[IMX7ULP_CLK_APLL_PRE_SEL]	= imx_clk_hw_mux_flags("apll_pre_sel", base + 0x508, 0, 1, pll_pre_sels, ARRAY_SIZE(pll_pre_sels), CLK_SET_PARENT_GATE);
	hws[IMX7ULP_CLK_SPLL_PRE_SEL]	= imx_clk_hw_mux_flags("spll_pre_sel", base + 0x608, 0, 1, pll_pre_sels, ARRAY_SIZE(pll_pre_sels), CLK_SET_PARENT_GATE);

	/*							   name		    parent_name	   reg			shअगरt	width	flags */
	hws[IMX7ULP_CLK_APLL_PRE_DIV]	= imx_clk_hw_भागider_flags("apll_pre_div", "apll_pre_sel", base + 0x508,	8,	3,	CLK_SET_RATE_GATE);
	hws[IMX7ULP_CLK_SPLL_PRE_DIV]	= imx_clk_hw_भागider_flags("spll_pre_div", "spll_pre_sel", base + 0x608,	8,	3,	CLK_SET_RATE_GATE);

	/*						name	 parent_name	 base */
	hws[IMX7ULP_CLK_APLL]		= imx_clk_hw_pllv4("apll",  "apll_pre_div", base + 0x500);
	hws[IMX7ULP_CLK_SPLL]		= imx_clk_hw_pllv4("spll",  "spll_pre_div", base + 0x600);

	/* APLL PFDs */
	hws[IMX7ULP_CLK_APLL_PFD0]	= imx_clk_hw_pfdv2("apll_pfd0", "apll", base + 0x50c, 0);
	hws[IMX7ULP_CLK_APLL_PFD1]	= imx_clk_hw_pfdv2("apll_pfd1", "apll", base + 0x50c, 1);
	hws[IMX7ULP_CLK_APLL_PFD2]	= imx_clk_hw_pfdv2("apll_pfd2", "apll", base + 0x50c, 2);
	hws[IMX7ULP_CLK_APLL_PFD3]	= imx_clk_hw_pfdv2("apll_pfd3", "apll", base + 0x50c, 3);

	/* SPLL PFDs */
	hws[IMX7ULP_CLK_SPLL_PFD0]	= imx_clk_hw_pfdv2("spll_pfd0", "spll", base + 0x60C, 0);
	hws[IMX7ULP_CLK_SPLL_PFD1]	= imx_clk_hw_pfdv2("spll_pfd1", "spll", base + 0x60C, 1);
	hws[IMX7ULP_CLK_SPLL_PFD2]	= imx_clk_hw_pfdv2("spll_pfd2", "spll", base + 0x60C, 2);
	hws[IMX7ULP_CLK_SPLL_PFD3]	= imx_clk_hw_pfdv2("spll_pfd3", "spll", base + 0x60C, 3);

	/* PLL Mux */
	hws[IMX7ULP_CLK_APLL_PFD_SEL]	= imx_clk_hw_mux_flags("apll_pfd_sel", base + 0x508, 14, 2, apll_pfd_sels, ARRAY_SIZE(apll_pfd_sels), CLK_SET_RATE_PARENT | CLK_SET_PARENT_GATE);
	hws[IMX7ULP_CLK_SPLL_PFD_SEL]	= imx_clk_hw_mux_flags("spll_pfd_sel", base + 0x608, 14, 2, spll_pfd_sels, ARRAY_SIZE(spll_pfd_sels), CLK_SET_RATE_PARENT | CLK_SET_PARENT_GATE);
	hws[IMX7ULP_CLK_APLL_SEL]	= imx_clk_hw_mux_flags("apll_sel", base + 0x508, 1, 1, apll_sels, ARRAY_SIZE(apll_sels), CLK_SET_RATE_PARENT | CLK_SET_PARENT_GATE);
	hws[IMX7ULP_CLK_SPLL_SEL]	= imx_clk_hw_mux_flags("spll_sel", base + 0x608, 1, 1, spll_sels, ARRAY_SIZE(spll_sels), CLK_SET_RATE_PARENT | CLK_SET_PARENT_GATE);

	hws[IMX7ULP_CLK_SPLL_BUS_CLK]	= imx_clk_hw_भागider_gate("spll_bus_clk", "spll_sel", CLK_SET_RATE_GATE, base + 0x604, 8, 3, 0, ulp_भाग_प्रकारable, &imx_ccm_lock);

	/* scs/ddr/nic select dअगरferent घड़ी source requires that घड़ी to be enabled first */
	hws[IMX7ULP_CLK_SYS_SEL]	= imx_clk_hw_mux2("scs_sel", base + 0x14, 24, 4, scs_sels, ARRAY_SIZE(scs_sels));
	hws[IMX7ULP_CLK_HSRUN_SYS_SEL] = imx_clk_hw_mux2("hsrun_scs_sel", base + 0x1c, 24, 4, scs_sels, ARRAY_SIZE(scs_sels));
	hws[IMX7ULP_CLK_NIC_SEL]	= imx_clk_hw_mux2("nic_sel", base + 0x40, 28, 1, nic_sels, ARRAY_SIZE(nic_sels));
	hws[IMX7ULP_CLK_DDR_SEL]	= imx_clk_hw_mux_flags("ddr_sel", base + 0x30, 24, 2, ddr_sels, ARRAY_SIZE(ddr_sels), CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE);

	hws[IMX7ULP_CLK_CORE_DIV]	= imx_clk_hw_भागider_flags("divcore",	"scs_sel",  base + 0x14, 16, 4, CLK_SET_RATE_PARENT);
	hws[IMX7ULP_CLK_CORE]		= imx_clk_hw_cpu("core", "divcore", hws[IMX7ULP_CLK_CORE_DIV]->clk, hws[IMX7ULP_CLK_SYS_SEL]->clk, hws[IMX7ULP_CLK_SPLL_SEL]->clk, hws[IMX7ULP_CLK_FIRC]->clk);
	hws[IMX7ULP_CLK_HSRUN_CORE_DIV] = imx_clk_hw_भागider_flags("hsrun_divcore", "hsrun_scs_sel", base + 0x1c, 16, 4, CLK_SET_RATE_PARENT);
	hws[IMX7ULP_CLK_HSRUN_CORE] = imx_clk_hw_cpu("hsrun_core", "hsrun_divcore", hws[IMX7ULP_CLK_HSRUN_CORE_DIV]->clk, hws[IMX7ULP_CLK_HSRUN_SYS_SEL]->clk, hws[IMX7ULP_CLK_SPLL_SEL]->clk, hws[IMX7ULP_CLK_FIRC]->clk);

	hws[IMX7ULP_CLK_DDR_DIV]	= imx_clk_hw_भागider_gate("ddr_clk", "ddr_sel", CLK_SET_RATE_PARENT | CLK_IS_CRITICAL, base + 0x30, 0, 3,
							       0, ulp_भाग_प्रकारable, &imx_ccm_lock);

	hws[IMX7ULP_CLK_NIC0_DIV]	= imx_clk_hw_भागider_flags("nic0_clk",		"nic_sel",  base + 0x40, 24, 4, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);
	hws[IMX7ULP_CLK_NIC1_DIV]	= imx_clk_hw_भागider_flags("nic1_clk",		"nic0_clk", base + 0x40, 16, 4, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);
	hws[IMX7ULP_CLK_NIC1_BUS_DIV]	= imx_clk_hw_भागider_flags("nic1_bus_clk",	"nic0_clk", base + 0x40, 4,  4, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

	hws[IMX7ULP_CLK_GPU_DIV]	= imx_clk_hw_भागider("gpu_clk", "nic0_clk", base + 0x40, 20, 4);

	hws[IMX7ULP_CLK_SOSC_BUS_CLK]	= imx_clk_hw_भागider_gate("sosc_bus_clk", "sosc", 0, base + 0x104, 8, 3,
							       CLK_DIVIDER_READ_ONLY, ulp_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX7ULP_CLK_FIRC_BUS_CLK]	= imx_clk_hw_भागider_gate("firc_bus_clk", "firc", 0, base + 0x304, 8, 3,
							       CLK_DIVIDER_READ_ONLY, ulp_भाग_प्रकारable, &imx_ccm_lock);

	imx_check_clk_hws(hws, clk_data->num);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);
पूर्ण
CLK_OF_DECLARE(imx7ulp_clk_scg1, "fsl,imx7ulp-scg1", imx7ulp_clk_scg1_init);

अटल व्योम __init imx7ulp_clk_pcc2_init(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा clk_hw **hws;
	व्योम __iomem *base;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, IMX7ULP_CLK_PCC2_END),
			   GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->num = IMX7ULP_CLK_PCC2_END;
	hws = clk_data->hws;

	/* PCC2 */
	base = of_iomap(np, 0);
	WARN_ON(!base);

	hws[IMX7ULP_CLK_DMA1]		= imx_clk_hw_gate("dma1", "nic1_clk", base + 0x20, 30);
	hws[IMX7ULP_CLK_RGPIO2P1]	= imx_clk_hw_gate("rgpio2p1", "nic1_bus_clk", base + 0x3c, 30);
	hws[IMX7ULP_CLK_DMA_MUX1]	= imx_clk_hw_gate("dma_mux1", "nic1_bus_clk", base + 0x84, 30);
	hws[IMX7ULP_CLK_CAAM]		= imx_clk_hw_gate("caam", "nic1_clk", base + 0x90, 30);
	hws[IMX7ULP_CLK_LPTPM4]		= imx7ulp_clk_hw_composite("lptpm4",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x94);
	hws[IMX7ULP_CLK_LPTPM5]		= imx7ulp_clk_hw_composite("lptpm5",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x98);
	hws[IMX7ULP_CLK_LPIT1]		= imx7ulp_clk_hw_composite("lpit1",   periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x9c);
	hws[IMX7ULP_CLK_LPSPI2]		= imx7ulp_clk_hw_composite("lpspi2",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xa4);
	hws[IMX7ULP_CLK_LPSPI3]		= imx7ulp_clk_hw_composite("lpspi3",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xa8);
	hws[IMX7ULP_CLK_LPI2C4]		= imx7ulp_clk_hw_composite("lpi2c4",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xac);
	hws[IMX7ULP_CLK_LPI2C5]		= imx7ulp_clk_hw_composite("lpi2c5",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xb0);
	hws[IMX7ULP_CLK_LPUART4]	= imx7ulp_clk_hw_composite("lpuart4", periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xb4);
	hws[IMX7ULP_CLK_LPUART5]	= imx7ulp_clk_hw_composite("lpuart5", periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xb8);
	hws[IMX7ULP_CLK_FLEXIO1]	= imx7ulp_clk_hw_composite("flexio1", periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0xc4);
	hws[IMX7ULP_CLK_USB0]		= imx7ulp_clk_hw_composite("usb0",    periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, true,  true, base + 0xcc);
	hws[IMX7ULP_CLK_USB1]		= imx7ulp_clk_hw_composite("usb1",    periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, true,  true, base + 0xd0);
	hws[IMX7ULP_CLK_USB_PHY]	= imx_clk_hw_gate("usb_phy", "nic1_bus_clk", base + 0xd4, 30);
	hws[IMX7ULP_CLK_USDHC0]		= imx7ulp_clk_hw_composite("usdhc0",  periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, true,  true, base + 0xdc);
	hws[IMX7ULP_CLK_USDHC1]		= imx7ulp_clk_hw_composite("usdhc1",  periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, true,  true, base + 0xe0);
	hws[IMX7ULP_CLK_WDG1]		= imx7ulp_clk_hw_composite("wdg1",    periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, true,  true, base + 0xf4);
	hws[IMX7ULP_CLK_WDG2]		= imx7ulp_clk_hw_composite("wdg2",    periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, true,  true, base + 0x10c);

	imx_check_clk_hws(hws, clk_data->num);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);

	imx_रेजिस्टर_uart_घड़ीs(2);
पूर्ण
CLK_OF_DECLARE(imx7ulp_clk_pcc2, "fsl,imx7ulp-pcc2", imx7ulp_clk_pcc2_init);

अटल व्योम __init imx7ulp_clk_pcc3_init(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा clk_hw **hws;
	व्योम __iomem *base;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, IMX7ULP_CLK_PCC3_END),
			   GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->num = IMX7ULP_CLK_PCC3_END;
	hws = clk_data->hws;

	/* PCC3 */
	base = of_iomap(np, 0);
	WARN_ON(!base);

	hws[IMX7ULP_CLK_LPTPM6]	= imx7ulp_clk_hw_composite("lptpm6",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x84);
	hws[IMX7ULP_CLK_LPTPM7]	= imx7ulp_clk_hw_composite("lptpm7",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x88);

	hws[IMX7ULP_CLK_MMDC]		= clk_hw_रेजिस्टर_gate(शून्य, "mmdc", "nic1_clk", CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
							       base + 0xac, 30, 0, &imx_ccm_lock);
	hws[IMX7ULP_CLK_LPI2C6]	= imx7ulp_clk_hw_composite("lpi2c6",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x90);
	hws[IMX7ULP_CLK_LPI2C7]	= imx7ulp_clk_hw_composite("lpi2c7",  periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x94);
	hws[IMX7ULP_CLK_LPUART6]	= imx7ulp_clk_hw_composite("lpuart6", periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x98);
	hws[IMX7ULP_CLK_LPUART7]	= imx7ulp_clk_hw_composite("lpuart7", periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, false, true, base + 0x9c);
	hws[IMX7ULP_CLK_DSI]		= imx7ulp_clk_hw_composite("dsi",     periph_bus_sels, ARRAY_SIZE(periph_bus_sels), true, true,  true, base + 0xa4);
	hws[IMX7ULP_CLK_LCDIF]		= imx7ulp_clk_hw_composite("lcdif",   periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, true,  true, base + 0xa8);

	hws[IMX7ULP_CLK_VIU]		= imx_clk_hw_gate("viu",   "nic1_clk",	   base + 0xa0, 30);
	hws[IMX7ULP_CLK_PCTLC]		= imx_clk_hw_gate("pctlc", "nic1_bus_clk", base + 0xb8, 30);
	hws[IMX7ULP_CLK_PCTLD]		= imx_clk_hw_gate("pctld", "nic1_bus_clk", base + 0xbc, 30);
	hws[IMX7ULP_CLK_PCTLE]		= imx_clk_hw_gate("pctle", "nic1_bus_clk", base + 0xc0, 30);
	hws[IMX7ULP_CLK_PCTLF]		= imx_clk_hw_gate("pctlf", "nic1_bus_clk", base + 0xc4, 30);

	hws[IMX7ULP_CLK_GPU3D]		= imx7ulp_clk_hw_composite("gpu3d",   periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, false, true, base + 0x140);
	hws[IMX7ULP_CLK_GPU2D]		= imx7ulp_clk_hw_composite("gpu2d",   periph_plat_sels, ARRAY_SIZE(periph_plat_sels), true, false, true, base + 0x144);

	imx_check_clk_hws(hws, clk_data->num);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);

	imx_रेजिस्टर_uart_घड़ीs(7);
पूर्ण
CLK_OF_DECLARE(imx7ulp_clk_pcc3, "fsl,imx7ulp-pcc3", imx7ulp_clk_pcc3_init);

अटल व्योम __init imx7ulp_clk_smc1_init(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा clk_hw **hws;
	व्योम __iomem *base;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, IMX7ULP_CLK_SMC1_END),
			   GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->num = IMX7ULP_CLK_SMC1_END;
	hws = clk_data->hws;

	/* SMC1 */
	base = of_iomap(np, 0);
	WARN_ON(!base);

	hws[IMX7ULP_CLK_ARM] = imx_clk_hw_mux_flags("arm", base + 0x10, 8, 2, arm_sels, ARRAY_SIZE(arm_sels), CLK_SET_RATE_PARENT);

	imx_check_clk_hws(hws, clk_data->num);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);
पूर्ण
CLK_OF_DECLARE(imx7ulp_clk_smc1, "fsl,imx7ulp-smc1", imx7ulp_clk_smc1_init);
