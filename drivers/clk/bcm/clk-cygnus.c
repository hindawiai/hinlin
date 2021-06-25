<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
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
#समावेश <linux/clkdev.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>

#समावेश <dt-bindings/घड़ी/bcm-cygnus.h>
#समावेश "clk-iproc.h"

#घोषणा REG_VAL(o, s, w) अणु .offset = o, .shअगरt = s, .width = w, पूर्ण

#घोषणा AON_VAL(o, pw, ps, is) अणु .offset = o, .pwr_width = pw, \
	.pwr_shअगरt = ps, .iso_shअगरt = is पूर्ण

#घोषणा SW_CTRL_VAL(o, s) अणु .offset = o, .shअगरt = s, पूर्ण

#घोषणा ASIU_DIV_VAL(o, es, hs, hw, ls, lw) \
		अणु .offset = o, .en_shअगरt = es, .high_shअगरt = hs, \
		.high_width = hw, .low_shअगरt = ls, .low_width = lw पूर्ण

#घोषणा RESET_VAL(o, rs, prs) अणु .offset = o, .reset_shअगरt = rs, \
	.p_reset_shअगरt = prs पूर्ण

#घोषणा DF_VAL(o, kis, kiw, kps, kpw, kas, kaw) अणु .offset = o, .ki_shअगरt = kis,\
	.ki_width = kiw, .kp_shअगरt = kps, .kp_width = kpw, .ka_shअगरt = kas,    \
	.ka_width = kaw पूर्ण

#घोषणा VCO_CTRL_VAL(uo, lo) अणु .u_offset = uo, .l_offset = lo पूर्ण

#घोषणा ENABLE_VAL(o, es, hs, bs) अणु .offset = o, .enable_shअगरt = es, \
	.hold_shअगरt = hs, .bypass_shअगरt = bs पूर्ण

#घोषणा ASIU_GATE_VAL(o, es) अणु .offset = o, .en_shअगरt = es पूर्ण

अटल व्योम __init cygnus_armpll_init(काष्ठा device_node *node)
अणु
	iproc_armpll_setup(node);
पूर्ण
CLK_OF_DECLARE(cygnus_armpll, "brcm,cygnus-armpll", cygnus_armpll_init);

अटल स्थिर काष्ठा iproc_pll_ctrl genpll = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 2, 1, 0),
	.reset = RESET_VAL(0x0, 11, 10),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctrl = SW_CTRL_VAL(0x10, 31),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x18, 0x1c),
	.status = REG_VAL(0x28, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl genpll_clk[] = अणु
	[BCM_CYGNUS_GENPLL_AXI21_CLK] = अणु
		.channel = BCM_CYGNUS_GENPLL_AXI21_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 6, 0, 12),
		.mभाग = REG_VAL(0x20, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_GENPLL_250MHZ_CLK] = अणु
		.channel = BCM_CYGNUS_GENPLL_250MHZ_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 7, 1, 13),
		.mभाग = REG_VAL(0x20, 10, 8),
	पूर्ण,
	[BCM_CYGNUS_GENPLL_IHOST_SYS_CLK] = अणु
		.channel = BCM_CYGNUS_GENPLL_IHOST_SYS_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 8, 2, 14),
		.mभाग = REG_VAL(0x20, 20, 8),
	पूर्ण,
	[BCM_CYGNUS_GENPLL_ENET_SW_CLK] = अणु
		.channel = BCM_CYGNUS_GENPLL_ENET_SW_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 9, 3, 15),
		.mभाग = REG_VAL(0x24, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_GENPLL_AUDIO_125_CLK] = अणु
		.channel = BCM_CYGNUS_GENPLL_AUDIO_125_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 10, 4, 16),
		.mभाग = REG_VAL(0x24, 10, 8),
	पूर्ण,
	[BCM_CYGNUS_GENPLL_CAN_CLK] = अणु
		.channel = BCM_CYGNUS_GENPLL_CAN_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 11, 5, 17),
		.mभाग = REG_VAL(0x24, 20, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init cygnus_genpll_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &genpll, शून्य, 0, genpll_clk,
			    ARRAY_SIZE(genpll_clk));
पूर्ण
CLK_OF_DECLARE(cygnus_genpll, "brcm,cygnus-genpll", cygnus_genpll_clk_init);

अटल स्थिर काष्ठा iproc_pll_ctrl lcpll0 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 2, 5, 4),
	.reset = RESET_VAL(0x0, 31, 30),
	.dig_filter = DF_VAL(0x0, 27, 3, 23, 4, 19, 4),
	.sw_ctrl = SW_CTRL_VAL(0x4, 31),
	.nभाग_पूर्णांक = REG_VAL(0x4, 16, 10),
	.pभाग = REG_VAL(0x4, 26, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x10, 0x14),
	.status = REG_VAL(0x18, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl lcpll0_clk[] = अणु
	[BCM_CYGNUS_LCPLL0_PCIE_PHY_REF_CLK] = अणु
		.channel = BCM_CYGNUS_LCPLL0_PCIE_PHY_REF_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 7, 1, 13),
		.mभाग = REG_VAL(0x8, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_LCPLL0_DDR_PHY_CLK] = अणु
		.channel = BCM_CYGNUS_LCPLL0_DDR_PHY_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 8, 2, 14),
		.mभाग = REG_VAL(0x8, 10, 8),
	पूर्ण,
	[BCM_CYGNUS_LCPLL0_SDIO_CLK] = अणु
		.channel = BCM_CYGNUS_LCPLL0_SDIO_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 9, 3, 15),
		.mभाग = REG_VAL(0x8, 20, 8),
	पूर्ण,
	[BCM_CYGNUS_LCPLL0_USB_PHY_REF_CLK] = अणु
		.channel = BCM_CYGNUS_LCPLL0_USB_PHY_REF_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 10, 4, 16),
		.mभाग = REG_VAL(0xc, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_LCPLL0_SMART_CARD_CLK] = अणु
		.channel = BCM_CYGNUS_LCPLL0_SMART_CARD_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 11, 5, 17),
		.mभाग = REG_VAL(0xc, 10, 8),
	पूर्ण,
	[BCM_CYGNUS_LCPLL0_CH5_UNUSED] = अणु
		.channel = BCM_CYGNUS_LCPLL0_CH5_UNUSED,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 12, 6, 18),
		.mभाग = REG_VAL(0xc, 20, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init cygnus_lcpll0_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &lcpll0, शून्य, 0, lcpll0_clk,
			    ARRAY_SIZE(lcpll0_clk));
पूर्ण
CLK_OF_DECLARE(cygnus_lcpll0, "brcm,cygnus-lcpll0", cygnus_lcpll0_clk_init);

/*
 * MIPI PLL VCO frequency parameter table
 */
अटल स्थिर काष्ठा iproc_pll_vco_param mipipll_vco_params[] = अणु
	/* rate (Hz) nभाग_पूर्णांक nभाग_frac pभाग */
	अणु 750000000UL,   30,     0,        1 पूर्ण,
	अणु 1000000000UL,  40,     0,        1 पूर्ण,
	अणु 1350000000ul,  54,     0,        1 पूर्ण,
	अणु 2000000000UL,  80,     0,        1 पूर्ण,
	अणु 2100000000UL,  84,     0,        1 पूर्ण,
	अणु 2250000000UL,  90,     0,        1 पूर्ण,
	अणु 2500000000UL,  100,    0,        1 पूर्ण,
	अणु 2700000000UL,  54,     0,        0 पूर्ण,
	अणु 2975000000UL,  119,    0,        1 पूर्ण,
	अणु 3100000000UL,  124,    0,        1 पूर्ण,
	अणु 3150000000UL,  126,    0,        1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iproc_pll_ctrl mipipll = अणु
	.flags = IPROC_CLK_PLL_ASIU | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		 IPROC_CLK_NEEDS_READ_BACK,
	.aon = AON_VAL(0x0, 4, 17, 16),
	.asiu = ASIU_GATE_VAL(0x0, 3),
	.reset = RESET_VAL(0x0, 11, 10),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 4),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x18, 0x1c),
	.status = REG_VAL(0x28, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl mipipll_clk[] = अणु
	[BCM_CYGNUS_MIPIPLL_CH0_UNUSED] = अणु
		.channel = BCM_CYGNUS_MIPIPLL_CH0_UNUSED,
		.flags = IPROC_CLK_NEEDS_READ_BACK,
		.enable = ENABLE_VAL(0x4, 12, 6, 18),
		.mभाग = REG_VAL(0x20, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_MIPIPLL_CH1_LCD] = अणु
		.channel = BCM_CYGNUS_MIPIPLL_CH1_LCD,
		.flags = IPROC_CLK_NEEDS_READ_BACK,
		.enable = ENABLE_VAL(0x4, 13, 7, 19),
		.mभाग = REG_VAL(0x20, 10, 8),
	पूर्ण,
	[BCM_CYGNUS_MIPIPLL_CH2_V3D] = अणु
		.channel = BCM_CYGNUS_MIPIPLL_CH2_V3D,
		.flags = IPROC_CLK_NEEDS_READ_BACK,
		.enable = ENABLE_VAL(0x4, 14, 8, 20),
		.mभाग = REG_VAL(0x20, 20, 8),
	पूर्ण,
	[BCM_CYGNUS_MIPIPLL_CH3_UNUSED] = अणु
		.channel = BCM_CYGNUS_MIPIPLL_CH3_UNUSED,
		.flags = IPROC_CLK_NEEDS_READ_BACK,
		.enable = ENABLE_VAL(0x4, 15, 9, 21),
		.mभाग = REG_VAL(0x24, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_MIPIPLL_CH4_UNUSED] = अणु
		.channel = BCM_CYGNUS_MIPIPLL_CH4_UNUSED,
		.flags = IPROC_CLK_NEEDS_READ_BACK,
		.enable = ENABLE_VAL(0x4, 16, 10, 22),
		.mभाग = REG_VAL(0x24, 10, 8),
	पूर्ण,
	[BCM_CYGNUS_MIPIPLL_CH5_UNUSED] = अणु
		.channel = BCM_CYGNUS_MIPIPLL_CH5_UNUSED,
		.flags = IPROC_CLK_NEEDS_READ_BACK,
		.enable = ENABLE_VAL(0x4, 17, 11, 23),
		.mभाग = REG_VAL(0x24, 20, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init cygnus_mipipll_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &mipipll, mipipll_vco_params,
			    ARRAY_SIZE(mipipll_vco_params), mipipll_clk,
			    ARRAY_SIZE(mipipll_clk));
पूर्ण
CLK_OF_DECLARE(cygnus_mipipll, "brcm,cygnus-mipipll", cygnus_mipipll_clk_init);

अटल स्थिर काष्ठा iproc_asiu_भाग asiu_भाग[] = अणु
	[BCM_CYGNUS_ASIU_KEYPAD_CLK] = ASIU_DIV_VAL(0x0, 31, 16, 10, 0, 10),
	[BCM_CYGNUS_ASIU_ADC_CLK] = ASIU_DIV_VAL(0x4, 31, 16, 10, 0, 10),
	[BCM_CYGNUS_ASIU_PWM_CLK] = ASIU_DIV_VAL(0x8, 31, 16, 10, 0, 10),
पूर्ण;

अटल स्थिर काष्ठा iproc_asiu_gate asiu_gate[] = अणु
	[BCM_CYGNUS_ASIU_KEYPAD_CLK] = ASIU_GATE_VAL(0x0, 7),
	[BCM_CYGNUS_ASIU_ADC_CLK] = ASIU_GATE_VAL(0x0, 9),
	[BCM_CYGNUS_ASIU_PWM_CLK] = ASIU_GATE_VAL(IPROC_CLK_INVALID_OFFSET, 0),
पूर्ण;

अटल व्योम __init cygnus_asiu_init(काष्ठा device_node *node)
अणु
	iproc_asiu_setup(node, asiu_भाग, asiu_gate, ARRAY_SIZE(asiu_भाग));
पूर्ण
CLK_OF_DECLARE(cygnus_asiu_clk, "brcm,cygnus-asiu-clk", cygnus_asiu_init);

अटल स्थिर काष्ठा iproc_pll_ctrl audiopll = अणु
	.flags = IPROC_CLK_PLL_NEEDS_SW_CFG | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_USER_MODE_ON | IPROC_CLK_PLL_RESET_ACTIVE_LOW |
		IPROC_CLK_PLL_CALC_PARAM,
	.reset = RESET_VAL(0x5c, 0, 1),
	.dig_filter = DF_VAL(0x48, 0, 3, 6, 4, 3, 3),
	.sw_ctrl = SW_CTRL_VAL(0x4, 0),
	.nभाग_पूर्णांक = REG_VAL(0x8, 0, 10),
	.nभाग_frac = REG_VAL(0x8, 10, 20),
	.pभाग = REG_VAL(0x44, 0, 4),
	.vco_ctrl = VCO_CTRL_VAL(0x0c, 0x10),
	.status = REG_VAL(0x54, 0, 1),
	.macro_mode = REG_VAL(0x0, 0, 3),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl audiopll_clk[] = अणु
	[BCM_CYGNUS_AUDIOPLL_CH0] = अणु
		.channel = BCM_CYGNUS_AUDIOPLL_CH0,
		.flags = IPROC_CLK_AON | IPROC_CLK_MCLK_DIV_BY_2,
		.enable = ENABLE_VAL(0x14, 8, 10, 9),
		.mभाग = REG_VAL(0x14, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_AUDIOPLL_CH1] = अणु
		.channel = BCM_CYGNUS_AUDIOPLL_CH1,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x18, 8, 10, 9),
		.mभाग = REG_VAL(0x18, 0, 8),
	पूर्ण,
	[BCM_CYGNUS_AUDIOPLL_CH2] = अणु
		.channel = BCM_CYGNUS_AUDIOPLL_CH2,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x1c, 8, 10, 9),
		.mभाग = REG_VAL(0x1c, 0, 8),
	पूर्ण,
पूर्ण;

अटल व्योम __init cygnus_audiopll_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &audiopll, शून्य, 0,
			    audiopll_clk,  ARRAY_SIZE(audiopll_clk));
पूर्ण
CLK_OF_DECLARE(cygnus_audiopll, "brcm,cygnus-audiopll",
			cygnus_audiopll_clk_init);
