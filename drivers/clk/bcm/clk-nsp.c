<शैली गुरु>
/*
 * Copyright (C) 2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <dt-bindings/घड़ी/bcm-nsp.h>
#समावेश "clk-iproc.h"

#घोषणा REG_VAL(o, s, w) अणु .offset = o, .shअगरt = s, .width = w, पूर्ण

#घोषणा AON_VAL(o, pw, ps, is) अणु .offset = o, .pwr_width = pw, \
	.pwr_shअगरt = ps, .iso_shअगरt = is पूर्ण

#घोषणा RESET_VAL(o, rs, prs) अणु .offset = o, .reset_shअगरt = rs, \
	.p_reset_shअगरt = prs पूर्ण

#घोषणा DF_VAL(o, kis, kiw, kps, kpw, kas, kaw) अणु .offset = o, .ki_shअगरt = kis,\
	.ki_width = kiw, .kp_shअगरt = kps, .kp_width = kpw, .ka_shअगरt = kas,    \
	.ka_width = kaw पूर्ण

#घोषणा ENABLE_VAL(o, es, hs, bs) अणु .offset = o, .enable_shअगरt = es, \
	.hold_shअगरt = hs, .bypass_shअगरt = bs पूर्ण

अटल व्योम __init nsp_armpll_init(काष्ठा device_node *node)
अणु
	iproc_armpll_setup(node);
पूर्ण
CLK_OF_DECLARE(nsp_armpll, "brcm,nsp-armpll", nsp_armpll_init);

अटल स्थिर काष्ठा iproc_pll_ctrl genpll = अणु
	.flags = IPROC_CLK_PLL_HAS_NDIV_FRAC | IPROC_CLK_EMBED_PWRCTRL,
	.aon = AON_VAL(0x0, 1, 12, 0),
	.reset = RESET_VAL(0x0, 11, 10),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.nभाग_पूर्णांक = REG_VAL(0x14, 20, 10),
	.nभाग_frac = REG_VAL(0x14, 0, 20),
	.pभाग = REG_VAL(0x18, 24, 3),
	.status = REG_VAL(0x20, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl genpll_clk[] = अणु
	[BCM_NSP_GENPLL_PHY_CLK] = अणु
		.channel = BCM_NSP_GENPLL_PHY_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 12, 6, 18),
		.mभाग = REG_VAL(0x18, 16, 8),
	पूर्ण,
	[BCM_NSP_GENPLL_ENET_SW_CLK] = अणु
		.channel = BCM_NSP_GENPLL_ENET_SW_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 13, 7, 19),
		.mभाग = REG_VAL(0x18, 8, 8),
	पूर्ण,
	[BCM_NSP_GENPLL_USB_PHY_REF_CLK] = अणु
		.channel = BCM_NSP_GENPLL_USB_PHY_REF_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 14, 8, 20),
		.mभाग = REG_VAL(0x18, 0, 8),
	पूर्ण,
	[BCM_NSP_GENPLL_IPROCFAST_CLK] = अणु
		.channel = BCM_NSP_GENPLL_IPROCFAST_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 15, 9, 21),
		.mभाग = REG_VAL(0x1c, 16, 8),
	पूर्ण,
	[BCM_NSP_GENPLL_SATA1_CLK] = अणु
		.channel = BCM_NSP_GENPLL_SATA1_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 16, 10, 22),
		.mभाग = REG_VAL(0x1c, 8, 8),
	पूर्ण,
	[BCM_NSP_GENPLL_SATA2_CLK] = अणु
		.channel = BCM_NSP_GENPLL_SATA2_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 17, 11, 23),
		.mभाग = REG_VAL(0x1c, 0, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init nsp_genpll_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &genpll, शून्य, 0, genpll_clk,
			    ARRAY_SIZE(genpll_clk));
पूर्ण
CLK_OF_DECLARE(nsp_genpll_clk, "brcm,nsp-genpll", nsp_genpll_clk_init);

अटल स्थिर काष्ठा iproc_pll_ctrl lcpll0 = अणु
	.flags = IPROC_CLK_PLL_HAS_NDIV_FRAC | IPROC_CLK_EMBED_PWRCTRL,
	.aon = AON_VAL(0x0, 1, 24, 0),
	.reset = RESET_VAL(0x0, 23, 22),
	.dig_filter = DF_VAL(0x0, 16, 3, 12, 4, 19, 4),
	.nभाग_पूर्णांक = REG_VAL(0x4, 20, 8),
	.nभाग_frac = REG_VAL(0x4, 0, 20),
	.pभाग = REG_VAL(0x4, 28, 3),
	.status = REG_VAL(0x10, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl lcpll0_clk[] = अणु
	[BCM_NSP_LCPLL0_PCIE_PHY_REF_CLK] = अणु
		.channel = BCM_NSP_LCPLL0_PCIE_PHY_REF_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 6, 3, 9),
		.mभाग = REG_VAL(0x8, 24, 8),
	पूर्ण,
	[BCM_NSP_LCPLL0_SDIO_CLK] = अणु
		.channel = BCM_NSP_LCPLL0_SDIO_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 7, 4, 10),
		.mभाग = REG_VAL(0x8, 16, 8),
	पूर्ण,
	[BCM_NSP_LCPLL0_DDR_PHY_CLK] = अणु
		.channel = BCM_NSP_LCPLL0_DDR_PHY_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 8, 5, 11),
		.mभाग = REG_VAL(0x8, 8, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init nsp_lcpll0_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &lcpll0, शून्य, 0, lcpll0_clk,
			    ARRAY_SIZE(lcpll0_clk));
पूर्ण
CLK_OF_DECLARE(nsp_lcpll0_clk, "brcm,nsp-lcpll0", nsp_lcpll0_clk_init);
