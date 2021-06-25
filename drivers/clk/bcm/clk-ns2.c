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

#समावेश <dt-bindings/घड़ी/bcm-ns2.h>
#समावेश "clk-iproc.h"

#घोषणा REG_VAL(o, s, w) अणु .offset = o, .shअगरt = s, .width = w, पूर्ण

#घोषणा AON_VAL(o, pw, ps, is) अणु .offset = o, .pwr_width = pw, \
	.pwr_shअगरt = ps, .iso_shअगरt = is पूर्ण

#घोषणा RESET_VAL(o, rs, prs) अणु .offset = o, .reset_shअगरt = rs, \
	.p_reset_shअगरt = prs पूर्ण

#घोषणा DF_VAL(o, kis, kiw, kps, kpw, kas, kaw) अणु .offset = o, .ki_shअगरt = kis,\
	.ki_width = kiw, .kp_shअगरt = kps, .kp_width = kpw, .ka_shअगरt = kas,    \
	.ka_width = kaw पूर्ण

#घोषणा VCO_CTRL_VAL(uo, lo) अणु .u_offset = uo, .l_offset = lo पूर्ण

#घोषणा ENABLE_VAL(o, es, hs, bs) अणु .offset = o, .enable_shअगरt = es, \
	.hold_shअगरt = hs, .bypass_shअगरt = bs पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl genpll_scr = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_SPLIT_STAT_CTRL,
	.aon = AON_VAL(0x0, 1, 15, 12),
	.reset = RESET_VAL(0x4, 2, 1),
	.dig_filter = DF_VAL(0x0, 9, 3, 5, 4, 2, 3),
	.nभाग_पूर्णांक = REG_VAL(0x8, 4, 10),
	.pभाग = REG_VAL(0x8, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x10, 0xc),
	.status = REG_VAL(0x0, 27, 1),
पूर्ण;


अटल स्थिर काष्ठा iproc_clk_ctrl genpll_scr_clk[] = अणु
	/* bypass_shअगरt, the last value passed पूर्णांकo ENABLE_VAL(), is not defined
	 * in NS2.  However, it करोesn't appear to be used anywhere, so setting
	 * it to 0.
	 */
	[BCM_NS2_GENPLL_SCR_SCR_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SCR_SCR_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 18, 12, 0),
		.mभाग = REG_VAL(0x18, 0, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SCR_FS_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SCR_FS_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 19, 13, 0),
		.mभाग = REG_VAL(0x18, 8, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SCR_AUDIO_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SCR_AUDIO_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 20, 14, 0),
		.mभाग = REG_VAL(0x14, 0, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SCR_CH3_UNUSED] = अणु
		.channel = BCM_NS2_GENPLL_SCR_CH3_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 21, 15, 0),
		.mभाग = REG_VAL(0x14, 8, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SCR_CH4_UNUSED] = अणु
		.channel = BCM_NS2_GENPLL_SCR_CH4_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 22, 16, 0),
		.mभाग = REG_VAL(0x14, 16, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SCR_CH5_UNUSED] = अणु
		.channel = BCM_NS2_GENPLL_SCR_CH5_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 23, 17, 0),
		.mभाग = REG_VAL(0x14, 24, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init ns2_genpll_scr_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &genpll_scr, शून्य, 0, genpll_scr_clk,
			    ARRAY_SIZE(genpll_scr_clk));
पूर्ण
CLK_OF_DECLARE(ns2_genpll_src_clk, "brcm,ns2-genpll-scr",
	       ns2_genpll_scr_clk_init);

अटल स्थिर काष्ठा iproc_pll_ctrl genpll_sw = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_SPLIT_STAT_CTRL,
	.aon = AON_VAL(0x0, 1, 11, 10),
	.reset = RESET_VAL(0x4, 2, 1),
	.dig_filter = DF_VAL(0x0, 9, 3, 5, 4, 2, 3),
	.nभाग_पूर्णांक = REG_VAL(0x8, 4, 10),
	.pभाग = REG_VAL(0x8, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x10, 0xc),
	.status = REG_VAL(0x0, 13, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl genpll_sw_clk[] = अणु
	/* bypass_shअगरt, the last value passed पूर्णांकo ENABLE_VAL(), is not defined
	 * in NS2.  However, it करोesn't appear to be used anywhere, so setting
	 * it to 0.
	 */
	[BCM_NS2_GENPLL_SW_RPE_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SW_RPE_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 18, 12, 0),
		.mभाग = REG_VAL(0x18, 0, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SW_250_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SW_250_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 19, 13, 0),
		.mभाग = REG_VAL(0x18, 8, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SW_NIC_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SW_NIC_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 20, 14, 0),
		.mभाग = REG_VAL(0x14, 0, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SW_CHIMP_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SW_CHIMP_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 21, 15, 0),
		.mभाग = REG_VAL(0x14, 8, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SW_PORT_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SW_PORT_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 22, 16, 0),
		.mभाग = REG_VAL(0x14, 16, 8),
	पूर्ण,
	[BCM_NS2_GENPLL_SW_SDIO_CLK] = अणु
		.channel = BCM_NS2_GENPLL_SW_SDIO_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 23, 17, 0),
		.mभाग = REG_VAL(0x14, 24, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init ns2_genpll_sw_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &genpll_sw, शून्य, 0, genpll_sw_clk,
			    ARRAY_SIZE(genpll_sw_clk));
पूर्ण
CLK_OF_DECLARE(ns2_genpll_sw_clk, "brcm,ns2-genpll-sw",
	       ns2_genpll_sw_clk_init);

अटल स्थिर काष्ठा iproc_pll_ctrl lcpll_ddr = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_SPLIT_STAT_CTRL,
	.aon = AON_VAL(0x0, 2, 1, 0),
	.reset = RESET_VAL(0x4, 2, 1),
	.dig_filter = DF_VAL(0x0, 9, 3, 5, 4, 1, 4),
	.nभाग_पूर्णांक = REG_VAL(0x8, 4, 10),
	.pभाग = REG_VAL(0x8, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x10, 0xc),
	.status = REG_VAL(0x0, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl lcpll_ddr_clk[] = अणु
	/* bypass_shअगरt, the last value passed पूर्णांकo ENABLE_VAL(), is not defined
	 * in NS2.  However, it करोesn't appear to be used anywhere, so setting
	 * it to 0.
	 */
	[BCM_NS2_LCPLL_DDR_PCIE_SATA_USB_CLK] = अणु
		.channel = BCM_NS2_LCPLL_DDR_PCIE_SATA_USB_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 18, 12, 0),
		.mभाग = REG_VAL(0x14, 0, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_DDR_DDR_CLK] = अणु
		.channel = BCM_NS2_LCPLL_DDR_DDR_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 19, 13, 0),
		.mभाग = REG_VAL(0x14, 8, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_DDR_CH2_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_DDR_CH2_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 20, 14, 0),
		.mभाग = REG_VAL(0x10, 0, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_DDR_CH3_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_DDR_CH3_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 21, 15, 0),
		.mभाग = REG_VAL(0x10, 8, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_DDR_CH4_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_DDR_CH4_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 22, 16, 0),
		.mभाग = REG_VAL(0x10, 16, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_DDR_CH5_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_DDR_CH5_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 23, 17, 0),
		.mभाग = REG_VAL(0x10, 24, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init ns2_lcpll_ddr_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &lcpll_ddr, शून्य, 0, lcpll_ddr_clk,
			    ARRAY_SIZE(lcpll_ddr_clk));
पूर्ण
CLK_OF_DECLARE(ns2_lcpll_ddr_clk, "brcm,ns2-lcpll-ddr",
	       ns2_lcpll_ddr_clk_init);

अटल स्थिर काष्ठा iproc_pll_ctrl lcpll_ports = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_SPLIT_STAT_CTRL,
	.aon = AON_VAL(0x0, 2, 5, 4),
	.reset = RESET_VAL(0x4, 2, 1),
	.dig_filter = DF_VAL(0x0, 9, 3, 5, 4, 1, 4),
	.nभाग_पूर्णांक = REG_VAL(0x8, 4, 10),
	.pभाग = REG_VAL(0x8, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x10, 0xc),
	.status = REG_VAL(0x0, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl lcpll_ports_clk[] = अणु
	/* bypass_shअगरt, the last value passed पूर्णांकo ENABLE_VAL(), is not defined
	 * in NS2.  However, it करोesn't appear to be used anywhere, so setting
	 * it to 0.
	 */
	[BCM_NS2_LCPLL_PORTS_WAN_CLK] = अणु
		.channel = BCM_NS2_LCPLL_PORTS_WAN_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 18, 12, 0),
		.mभाग = REG_VAL(0x14, 0, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_PORTS_RGMII_CLK] = अणु
		.channel = BCM_NS2_LCPLL_PORTS_RGMII_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 19, 13, 0),
		.mभाग = REG_VAL(0x14, 8, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_PORTS_CH2_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_PORTS_CH2_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 20, 14, 0),
		.mभाग = REG_VAL(0x10, 0, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_PORTS_CH3_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_PORTS_CH3_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 21, 15, 0),
		.mभाग = REG_VAL(0x10, 8, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_PORTS_CH4_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_PORTS_CH4_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 22, 16, 0),
		.mभाग = REG_VAL(0x10, 16, 8),
	पूर्ण,
	[BCM_NS2_LCPLL_PORTS_CH5_UNUSED] = अणु
		.channel = BCM_NS2_LCPLL_PORTS_CH5_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 23, 17, 0),
		.mभाग = REG_VAL(0x10, 24, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init ns2_lcpll_ports_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &lcpll_ports, शून्य, 0, lcpll_ports_clk,
			    ARRAY_SIZE(lcpll_ports_clk));
पूर्ण
CLK_OF_DECLARE(ns2_lcpll_ports_clk, "brcm,ns2-lcpll-ports",
	       ns2_lcpll_ports_clk_init);
