<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2008 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <dt-bindings/घड़ी/imx1-घड़ी.h>
#समावेश <soc/imx/समयr.h>
#समावेश <यंत्र/irq.h>

#समावेश "clk.h"

#घोषणा MX1_CCM_BASE_ADDR	0x0021b000
#घोषणा MX1_TIM1_BASE_ADDR	0x00220000
#घोषणा MX1_TIM1_INT		(NR_IRQS_LEGACY + 59)

अटल स्थिर अक्षर *prem_sel_clks[] = अणु "clk32_premult", "clk16m", पूर्ण;
अटल स्थिर अक्षर *clko_sel_clks[] = अणु "per1", "hclk", "clk48m", "clk16m",
				       "prem", "fclk", पूर्ण;

अटल काष्ठा clk *clk[IMX1_CLK_MAX];
अटल काष्ठा clk_onecell_data clk_data;

अटल व्योम __iomem *ccm __initdata;
#घोषणा CCM_CSCR	(ccm + 0x0000)
#घोषणा CCM_MPCTL0	(ccm + 0x0004)
#घोषणा CCM_SPCTL0	(ccm + 0x000c)
#घोषणा CCM_PCDR	(ccm + 0x0020)
#घोषणा SCM_GCCR	(ccm + 0x0810)

अटल व्योम __init mx1_घड़ीs_init_dt(काष्ठा device_node *np)
अणु
	ccm = of_iomap(np, 0);
	BUG_ON(!ccm);

	clk[IMX1_CLK_DUMMY] = imx_clk_fixed("dummy", 0);
	clk[IMX1_CLK_CLK32] = imx_obtain_fixed_घड़ी("clk32", 32768);
	clk[IMX1_CLK_CLK16M_EXT] = imx_clk_fixed("clk16m_ext", 16000000);
	clk[IMX1_CLK_CLK16M] = imx_clk_gate("clk16m", "clk16m_ext", CCM_CSCR, 17);
	clk[IMX1_CLK_CLK32_PREMULT] = imx_clk_fixed_factor("clk32_premult", "clk32", 512, 1);
	clk[IMX1_CLK_PREM] = imx_clk_mux("prem", CCM_CSCR, 16, 1, prem_sel_clks, ARRAY_SIZE(prem_sel_clks));
	clk[IMX1_CLK_MPLL] = imx_clk_pllv1(IMX_PLLV1_IMX1, "mpll", "clk32_premult", CCM_MPCTL0);
	clk[IMX1_CLK_MPLL_GATE] = imx_clk_gate("mpll_gate", "mpll", CCM_CSCR, 0);
	clk[IMX1_CLK_SPLL] = imx_clk_pllv1(IMX_PLLV1_IMX1, "spll", "prem", CCM_SPCTL0);
	clk[IMX1_CLK_SPLL_GATE] = imx_clk_gate("spll_gate", "spll", CCM_CSCR, 1);
	clk[IMX1_CLK_MCU] = imx_clk_भागider("mcu", "clk32_premult", CCM_CSCR, 15, 1);
	clk[IMX1_CLK_FCLK] = imx_clk_भागider("fclk", "mpll_gate", CCM_CSCR, 15, 1);
	clk[IMX1_CLK_HCLK] = imx_clk_भागider("hclk", "spll_gate", CCM_CSCR, 10, 4);
	clk[IMX1_CLK_CLK48M] = imx_clk_भागider("clk48m", "spll_gate", CCM_CSCR, 26, 3);
	clk[IMX1_CLK_PER1] = imx_clk_भागider("per1", "spll_gate", CCM_PCDR, 0, 4);
	clk[IMX1_CLK_PER2] = imx_clk_भागider("per2", "spll_gate", CCM_PCDR, 4, 4);
	clk[IMX1_CLK_PER3] = imx_clk_भागider("per3", "spll_gate", CCM_PCDR, 16, 7);
	clk[IMX1_CLK_CLKO] = imx_clk_mux("clko", CCM_CSCR, 29, 3, clko_sel_clks, ARRAY_SIZE(clko_sel_clks));
	clk[IMX1_CLK_UART3_GATE] = imx_clk_gate("uart3_gate", "hclk", SCM_GCCR, 6);
	clk[IMX1_CLK_SSI2_GATE] = imx_clk_gate("ssi2_gate", "hclk", SCM_GCCR, 5);
	clk[IMX1_CLK_BROM_GATE] = imx_clk_gate("brom_gate", "hclk", SCM_GCCR, 4);
	clk[IMX1_CLK_DMA_GATE] = imx_clk_gate("dma_gate", "hclk", SCM_GCCR, 3);
	clk[IMX1_CLK_CSI_GATE] = imx_clk_gate("csi_gate", "hclk", SCM_GCCR, 2);
	clk[IMX1_CLK_MMA_GATE] = imx_clk_gate("mma_gate", "hclk", SCM_GCCR, 1);
	clk[IMX1_CLK_USBD_GATE] = imx_clk_gate("usbd_gate", "clk48m", SCM_GCCR, 0);

	imx_check_घड़ीs(clk, ARRAY_SIZE(clk));

	clk_data.clks = clk;
	clk_data.clk_num = ARRAY_SIZE(clk);
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);
पूर्ण
CLK_OF_DECLARE(imx1_ccm, "fsl,imx1-ccm", mx1_घड़ीs_init_dt);
