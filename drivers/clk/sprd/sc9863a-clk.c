<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Unisoc SC9863A घड़ी driver
 *
 * Copyright (C) 2019 Unisoc, Inc.
 * Author: Chunyan Zhang <chunyan.zhang@unisoc.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/sprd,sc9863a-clk.h>

#समावेश "common.h"
#समावेश "composite.h"
#समावेश "div.h"
#समावेश "gate.h"
#समावेश "mux.h"
#समावेश "pll.h"

/* mpll*_gate घड़ीs control cpu cores, they were enabled by शेष */
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(mpll0_gate, "mpll0-gate", "ext-26m", 0x94,
				    0x1000, BIT(0), CLK_IGNORE_UNUSED, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(dpll0_gate, "dpll0-gate", "ext-26m", 0x98,
				    0x1000, BIT(0), 0, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(lpll_gate, "lpll-gate", "ext-26m", 0x9c,
				    0x1000, BIT(0), 0, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(gpll_gate, "gpll-gate", "ext-26m", 0xa8,
				    0x1000, BIT(0), 0, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(dpll1_gate, "dpll1-gate", "ext-26m", 0x1dc,
				    0x1000, BIT(0), 0, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(mpll1_gate, "mpll1-gate", "ext-26m", 0x1e0,
				    0x1000, BIT(0), CLK_IGNORE_UNUSED, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(mpll2_gate, "mpll2-gate", "ext-26m", 0x1e4,
				    0x1000, BIT(0), CLK_IGNORE_UNUSED, 0, 240);
अटल SPRD_PLL_SC_GATE_CLK_FW_NAME(isppll_gate, "isppll-gate", "ext-26m",
				    0x1e8, 0x1000, BIT(0), 0, 0, 240);

अटल काष्ठा sprd_clk_common *sc9863a_pmu_gate_clks[] = अणु
	/* address base is 0x402b0000 */
	&mpll0_gate.common,
	&dpll0_gate.common,
	&lpll_gate.common,
	&gpll_gate.common,
	&dpll1_gate.common,
	&mpll1_gate.common,
	&mpll2_gate.common,
	&isppll_gate.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_pmu_gate_hws = अणु
	.hws	= अणु
		[CLK_MPLL0_GATE]	= &mpll0_gate.common.hw,
		[CLK_DPLL0_GATE]	= &dpll0_gate.common.hw,
		[CLK_LPLL_GATE]		= &lpll_gate.common.hw,
		[CLK_GPLL_GATE]		= &gpll_gate.common.hw,
		[CLK_DPLL1_GATE]	= &dpll1_gate.common.hw,
		[CLK_MPLL1_GATE]	= &mpll1_gate.common.hw,
		[CLK_MPLL2_GATE]	= &mpll2_gate.common.hw,
		[CLK_ISPPLL_GATE]	= &isppll_gate.common.hw,
	पूर्ण,
	.num	= CLK_PMU_APB_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_pmu_gate_desc = अणु
	.clk_clks	= sc9863a_pmu_gate_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_pmu_gate_clks),
	.hw_clks        = &sc9863a_pmu_gate_hws,
पूर्ण;

अटल स्थिर u64 itable[5] = अणु4, 1000000000, 1200000000,
			      1400000000, 1600000000पूर्ण;

अटल स्थिर काष्ठा clk_bit_field f_twpll[PLL_FACT_MAX] = अणु
	अणु .shअगरt = 95,	.width = 1 पूर्ण,	/* lock_करोne	*/
	अणु .shअगरt = 0,	.width = 1 पूर्ण,	/* भाग_s	*/
	अणु .shअगरt = 1,	.width = 1 पूर्ण,	/* mod_en	*/
	अणु .shअगरt = 2,	.width = 1 पूर्ण,	/* sdm_en	*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* refin	*/
	अणु .shअगरt = 3,	.width = 3 पूर्ण,	/* ibias	*/
	अणु .shअगरt = 8,	.width = 11 पूर्ण,	/* n		*/
	अणु .shअगरt = 55,	.width = 7 पूर्ण,	/* nपूर्णांक		*/
	अणु .shअगरt = 32,	.width = 23पूर्ण,	/* kपूर्णांक		*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* preभाग	*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* postभाग	*/
पूर्ण;
अटल SPRD_PLL_FW_NAME(twpll, "twpll", "ext-26m", 0x4, 3, itable,
			f_twpll, 240, 1000, 1000, 0, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_768m, "twpll-768m", &twpll.common.hw, 2, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_384m, "twpll-384m", &twpll.common.hw, 4, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_192m, "twpll-192m", &twpll.common.hw, 8, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_96m, "twpll-96m", &twpll.common.hw, 16, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_48m, "twpll-48m", &twpll.common.hw, 32, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_24m, "twpll-24m", &twpll.common.hw, 64, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_12m, "twpll-12m", &twpll.common.hw, 128, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_512m, "twpll-512m", &twpll.common.hw, 3, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_256m, "twpll-256m", &twpll.common.hw, 6, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_128m, "twpll-128m", &twpll.common.hw, 12, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_64m, "twpll-64m", &twpll.common.hw, 24, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_307m2, "twpll-307m2", &twpll.common.hw, 5, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_219m4, "twpll-219m4", &twpll.common.hw, 7, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_170m6, "twpll-170m6", &twpll.common.hw, 9, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_153m6, "twpll-153m6", &twpll.common.hw, 10, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_76m8, "twpll-76m8", &twpll.common.hw, 20, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_51m2, "twpll-51m2", &twpll.common.hw, 30, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_38m4, "twpll-38m4", &twpll.common.hw, 40, 1, 0);
अटल CLK_FIXED_FACTOR_HW(twpll_19m2, "twpll-19m2", &twpll.common.hw, 80, 1, 0);

अटल स्थिर काष्ठा clk_bit_field f_lpll[PLL_FACT_MAX] = अणु
	अणु .shअगरt = 95,	.width = 1 पूर्ण,	/* lock_करोne	*/
	अणु .shअगरt = 0,	.width = 1 पूर्ण,	/* भाग_s	*/
	अणु .shअगरt = 1,	.width = 1 पूर्ण,	/* mod_en	*/
	अणु .shअगरt = 2,	.width = 1 पूर्ण,	/* sdm_en	*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* refin	*/
	अणु .shअगरt = 6,	.width = 2 पूर्ण,	/* ibias	*/
	अणु .shअगरt = 8,	.width = 11 पूर्ण,	/* n		*/
	अणु .shअगरt = 55,	.width = 7 पूर्ण,	/* nपूर्णांक		*/
	अणु .shअगरt = 32,	.width = 23पूर्ण,	/* kपूर्णांक		*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* preभाग	*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* postभाग	*/
पूर्ण;
अटल SPRD_PLL_HW(lpll, "lpll", &lpll_gate.common.hw, 0x20, 3, itable,
		   f_lpll, 240, 1000, 1000, 0, 0);
अटल CLK_FIXED_FACTOR_HW(lpll_409m6, "lpll-409m6", &lpll.common.hw, 3, 1, 0);
अटल CLK_FIXED_FACTOR_HW(lpll_245m76, "lpll-245m76", &lpll.common.hw, 5, 1, 0);

अटल स्थिर काष्ठा clk_bit_field f_gpll[PLL_FACT_MAX] = अणु
	अणु .shअगरt = 95,	.width = 1 पूर्ण,	/* lock_करोne	*/
	अणु .shअगरt = 0,	.width = 1 पूर्ण,	/* भाग_s	*/
	अणु .shअगरt = 1,	.width = 1 पूर्ण,	/* mod_en	*/
	अणु .shअगरt = 2,	.width = 1 पूर्ण,	/* sdm_en	*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* refin	*/
	अणु .shअगरt = 6,	.width = 2 पूर्ण,	/* ibias	*/
	अणु .shअगरt = 8,	.width = 11 पूर्ण,	/* n		*/
	अणु .shअगरt = 55,	.width = 7 पूर्ण,	/* nपूर्णांक		*/
	अणु .shअगरt = 32,	.width = 23पूर्ण,	/* kपूर्णांक		*/
	अणु .shअगरt = 0,	.width = 0 पूर्ण,	/* preभाग	*/
	अणु .shअगरt = 80,	.width = 1 पूर्ण,	/* postभाग	*/
पूर्ण;
अटल SPRD_PLL_HW(gpll, "gpll", &gpll_gate.common.hw, 0x38, 3, itable,
		   f_gpll, 240, 1000, 1000, 1, 400000000);

अटल SPRD_PLL_HW(isppll, "isppll", &isppll_gate.common.hw, 0x50, 3, itable,
		   f_gpll, 240, 1000, 1000, 0, 0);
अटल CLK_FIXED_FACTOR_HW(isppll_468m, "isppll-468m", &isppll.common.hw, 2, 1, 0);

अटल काष्ठा sprd_clk_common *sc9863a_pll_clks[] = अणु
	/* address base is 0x40353000 */
	&twpll.common,
	&lpll.common,
	&gpll.common,
	&isppll.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_pll_hws = अणु
	.hws	= अणु
		[CLK_TWPLL]		= &twpll.common.hw,
		[CLK_TWPLL_768M]	= &twpll_768m.hw,
		[CLK_TWPLL_384M]	= &twpll_384m.hw,
		[CLK_TWPLL_192M]	= &twpll_192m.hw,
		[CLK_TWPLL_96M]		= &twpll_96m.hw,
		[CLK_TWPLL_48M]		= &twpll_48m.hw,
		[CLK_TWPLL_24M]		= &twpll_24m.hw,
		[CLK_TWPLL_12M]		= &twpll_12m.hw,
		[CLK_TWPLL_512M]	= &twpll_512m.hw,
		[CLK_TWPLL_256M]	= &twpll_256m.hw,
		[CLK_TWPLL_128M]	= &twpll_128m.hw,
		[CLK_TWPLL_64M]		= &twpll_64m.hw,
		[CLK_TWPLL_307M2]	= &twpll_307m2.hw,
		[CLK_TWPLL_219M4]	= &twpll_219m4.hw,
		[CLK_TWPLL_170M6]	= &twpll_170m6.hw,
		[CLK_TWPLL_153M6]	= &twpll_153m6.hw,
		[CLK_TWPLL_76M8]	= &twpll_76m8.hw,
		[CLK_TWPLL_51M2]	= &twpll_51m2.hw,
		[CLK_TWPLL_38M4]	= &twpll_38m4.hw,
		[CLK_TWPLL_19M2]	= &twpll_19m2.hw,
		[CLK_LPLL]		= &lpll.common.hw,
		[CLK_LPLL_409M6]	= &lpll_409m6.hw,
		[CLK_LPLL_245M76]	= &lpll_245m76.hw,
		[CLK_GPLL]		= &gpll.common.hw,
		[CLK_ISPPLL]		= &isppll.common.hw,
		[CLK_ISPPLL_468M]	= &isppll_468m.hw,

	पूर्ण,
	.num	= CLK_ANLG_PHY_G1_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_pll_desc = अणु
	.clk_clks	= sc9863a_pll_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_pll_clks),
	.hw_clks        = &sc9863a_pll_hws,
पूर्ण;

अटल स्थिर u64 itable_mpll[6] = अणु5, 1000000000, 1200000000, 1400000000,
				   1600000000, 1800000000पूर्ण;
अटल SPRD_PLL_HW(mpll0, "mpll0", &mpll0_gate.common.hw, 0x0, 3, itable_mpll,
		   f_gpll, 240, 1000, 1000, 1, 1000000000);
अटल SPRD_PLL_HW(mpll1, "mpll1", &mpll1_gate.common.hw, 0x18, 3, itable_mpll,
		   f_gpll, 240, 1000, 1000, 1, 1000000000);
अटल SPRD_PLL_HW(mpll2, "mpll2", &mpll2_gate.common.hw, 0x30, 3, itable_mpll,
		   f_gpll, 240, 1000, 1000, 1, 1000000000);
अटल CLK_FIXED_FACTOR_HW(mpll2_675m, "mpll2-675m", &mpll2.common.hw, 2, 1, 0);

अटल काष्ठा sprd_clk_common *sc9863a_mpll_clks[] = अणु
	/* address base is 0x40359000 */
	&mpll0.common,
	&mpll1.common,
	&mpll2.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_mpll_hws = अणु
	.hws	= अणु
		[CLK_MPLL0]		= &mpll0.common.hw,
		[CLK_MPLL1]		= &mpll1.common.hw,
		[CLK_MPLL2]		= &mpll2.common.hw,
		[CLK_MPLL2_675M]	= &mpll2_675m.hw,

	पूर्ण,
	.num	= CLK_ANLG_PHY_G4_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_mpll_desc = अणु
	.clk_clks	= sc9863a_mpll_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_mpll_clks),
	.hw_clks        = &sc9863a_mpll_hws,
पूर्ण;

अटल SPRD_SC_GATE_CLK_FW_NAME(audio_gate,	"audio-gate",	"ext-26m",
				0x4, 0x1000, BIT(8), 0, 0);

अटल SPRD_PLL_FW_NAME(rpll, "rpll", "ext-26m", 0x10,
			3, itable, f_lpll, 240, 1000, 1000, 0, 0);

अटल CLK_FIXED_FACTOR_HW(rpll_390m, "rpll-390m", &rpll.common.hw, 2, 1, 0);
अटल CLK_FIXED_FACTOR_HW(rpll_260m, "rpll-260m", &rpll.common.hw, 3, 1, 0);
अटल CLK_FIXED_FACTOR_HW(rpll_195m, "rpll-195m", &rpll.common.hw, 4, 1, 0);
अटल CLK_FIXED_FACTOR_HW(rpll_26m, "rpll-26m", &rpll.common.hw, 30, 1, 0);

अटल काष्ठा sprd_clk_common *sc9863a_rpll_clks[] = अणु
	/* address base is 0x4035c000 */
	&audio_gate.common,
	&rpll.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_rpll_hws = अणु
	.hws	= अणु
		[CLK_AUDIO_GATE]	= &audio_gate.common.hw,
		[CLK_RPLL]		= &rpll.common.hw,
		[CLK_RPLL_390M]		= &rpll_390m.hw,
		[CLK_RPLL_260M]		= &rpll_260m.hw,
		[CLK_RPLL_195M]		= &rpll_195m.hw,
		[CLK_RPLL_26M]		= &rpll_26m.hw,
	पूर्ण,
	.num	= CLK_ANLG_PHY_G5_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_rpll_desc = अणु
	.clk_clks	= sc9863a_rpll_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_rpll_clks),
	.hw_clks        = &sc9863a_rpll_hws,
पूर्ण;

अटल स्थिर u64 itable_dpll[5] = अणु4, 1211000000, 1320000000, 1570000000,
				   1866000000पूर्ण;
अटल SPRD_PLL_HW(dpll0, "dpll0", &dpll0_gate.common.hw, 0x0, 3, itable_dpll,
		   f_lpll, 240, 1000, 1000, 0, 0);
अटल SPRD_PLL_HW(dpll1, "dpll1", &dpll1_gate.common.hw, 0x18, 3, itable_dpll,
		   f_lpll, 240, 1000, 1000, 0, 0);

अटल CLK_FIXED_FACTOR_HW(dpll0_933m, "dpll0-933m", &dpll0.common.hw, 2, 1, 0);
अटल CLK_FIXED_FACTOR_HW(dpll0_622m3, "dpll0-622m3", &dpll0.common.hw, 3, 1, 0);
अटल CLK_FIXED_FACTOR_HW(dpll1_400m, "dpll1-400m", &dpll0.common.hw, 4, 1, 0);
अटल CLK_FIXED_FACTOR_HW(dpll1_266m7, "dpll1-266m7", &dpll0.common.hw, 6, 1, 0);
अटल CLK_FIXED_FACTOR_HW(dpll1_123m1, "dpll1-123m1", &dpll0.common.hw, 13, 1, 0);
अटल CLK_FIXED_FACTOR_HW(dpll1_50m, "dpll1-50m", &dpll0.common.hw, 32, 1, 0);

अटल काष्ठा sprd_clk_common *sc9863a_dpll_clks[] = अणु
	/* address base is 0x40363000 */
	&dpll0.common,
	&dpll1.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_dpll_hws = अणु
	.hws	= अणु
		[CLK_DPLL0]		= &dpll0.common.hw,
		[CLK_DPLL1]		= &dpll1.common.hw,
		[CLK_DPLL0_933M]	= &dpll0_933m.hw,
		[CLK_DPLL0_622M3]	= &dpll0_622m3.hw,
		[CLK_DPLL0_400M]	= &dpll1_400m.hw,
		[CLK_DPLL0_266M7]	= &dpll1_266m7.hw,
		[CLK_DPLL0_123M1]	= &dpll1_123m1.hw,
		[CLK_DPLL0_50M]		= &dpll1_50m.hw,

	पूर्ण,
	.num	= CLK_ANLG_PHY_G7_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_dpll_desc = अणु
	.clk_clks	= sc9863a_dpll_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_dpll_clks),
	.hw_clks        = &sc9863a_dpll_hws,
पूर्ण;

अटल CLK_FIXED_FACTOR_FW_NAME(clk_6m5, "clk-6m5", "ext-26m", 4, 1, 0);
अटल CLK_FIXED_FACTOR_FW_NAME(clk_4m3, "clk-4m3", "ext-26m", 6, 1, 0);
अटल CLK_FIXED_FACTOR_FW_NAME(clk_2m, "clk-2m", "ext-26m", 13, 1, 0);
अटल CLK_FIXED_FACTOR_FW_NAME(clk_250k, "clk-250k", "ext-26m", 104, 1, 0);
अटल CLK_FIXED_FACTOR_FW_NAME(rco_25m, "rco-25m", "rco-100m",	4, 1, 0);
अटल CLK_FIXED_FACTOR_FW_NAME(rco_4m, "rco-4m", "rco-100m", 25, 1, 0);
अटल CLK_FIXED_FACTOR_FW_NAME(rco_2m, "rco-2m", "rco-100m", 50, 1, 0);

#घोषणा SC9863A_MUX_FLAG	\
	(CLK_GET_RATE_NOCACHE | CLK_SET_RATE_NO_REPARENT)

अटल CLK_FIXED_FACTOR_FW_NAME(clk_13m, "clk-13m", "ext-26m", 2, 1, 0);
अटल स्थिर काष्ठा clk_parent_data emc_clk_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
	अणु .hw = &twpll_768m.hw  पूर्ण,
	अणु .hw = &twpll.common.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(emc_clk, "emc-clk", emc_clk_parents, 0x220,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data aon_apb_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .hw = &rco_25m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
	अणु .fw_name = "rco-100m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(aon_apb, "aon-apb", aon_apb_parents, 0x224,
			  0, 3, 8, 2, 0);

अटल स्थिर काष्ठा clk_parent_data adi_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .hw = &rco_25m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_38m4.hw  पूर्ण,
	अणु .hw = &twpll_51m2.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(adi_clk, "adi-clk", adi_parents, 0x228,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data aux_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .hw = &rpll_26m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(aux0_clk, "aux0-clk", aux_parents, 0x22c,
			  0, 5, 8, 4, 0);
अटल SPRD_COMP_CLK_DATA(aux1_clk, "aux1-clk", aux_parents, 0x230,
			  0, 5, 8, 4, 0);
अटल SPRD_COMP_CLK_DATA(aux2_clk, "aux2-clk", aux_parents, 0x234,
			  0, 5, 8, 4, 0);
अटल SPRD_COMP_CLK_DATA(probe_clk, "probe-clk", aux_parents, 0x238,
			  0, 5, 8, 4, 0);

अटल स्थिर काष्ठा clk_parent_data pwm_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .hw = &rpll_26m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_48m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(pwm0_clk, "pwm0-clk", pwm_parents, 0x23c,
			 0, 2, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(pwm1_clk, "pwm1-clk", pwm_parents, 0x240,
			 0, 2, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(pwm2_clk, "pwm2-clk", pwm_parents, 0x244,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data aon_thm_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .hw = &clk_250k.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(aon_thm_clk, "aon-thm-clk", aon_thm_parents, 0x25c,
			 0, 1, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data audअगर_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_38m4.hw  पूर्ण,
	अणु .hw = &twpll_51m2.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(audअगर_clk, "audif-clk", audअगर_parents, 0x264,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data cpu_dap_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .hw = &rco_25m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_76m8.hw  पूर्ण,
	अणु .fw_name = "rco-100m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(cpu_dap_clk, "cpu-dap-clk", cpu_dap_parents, 0x26c,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data cpu_ts_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(cpu_ts_clk, "cpu-ts-clk", cpu_ts_parents, 0x274,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data djtag_tck_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(djtag_tck_clk, "djtag-tck-clk", djtag_tck_parents, 0x28c,
			 0, 1, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data emc_ref_parents[] = अणु
	अणु .hw = &clk_6m5.hw  पूर्ण,
	अणु .hw = &clk_13m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(emc_ref_clk, "emc-ref-clk", emc_ref_parents, 0x29c,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data cssys_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
	अणु .fw_name = "rco-100m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
	अणु .hw = &mpll2_675m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(cssys_clk, "cssys-clk", cssys_parents, 0x2a0,
			  0, 4, 8, 2, 0);

अटल स्थिर काष्ठा clk_parent_data aon_pmu_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .fw_name = "ext-4m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(aon_pmu_clk, "aon-pmu-clk", aon_pmu_parents, 0x2a8,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data pmu_26m_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .hw = &rco_25m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(pmu_26m_clk, "26m-pmu-clk", pmu_26m_parents, 0x2ac,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data aon_पंचांगr_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(aon_पंचांगr_clk, "aon-tmr-clk", aon_पंचांगr_parents, 0x2b0,
			 0, 1, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data घातer_cpu_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &rco_25m.hw  पूर्ण,
	अणु .fw_name = "rco-100m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(घातer_cpu_clk, "power-cpu-clk", घातer_cpu_parents, 0x2c4,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data ap_axi_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_76m8.hw  पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(ap_axi, "ap-axi", ap_axi_parents, 0x2c8,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data sdio_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &rpll_390m.hw  पूर्ण,
	अणु .hw = &dpll1_400m.hw  पूर्ण,
	अणु .hw = &lpll_409m6.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(sdio0_2x, "sdio0-2x", sdio_parents, 0x2cc,
			 0, 3, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(sdio1_2x, "sdio1-2x", sdio_parents, 0x2d4,
			 0, 3, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(sdio2_2x, "sdio2-2x", sdio_parents, 0x2dc,
			 0, 3, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(emmc_2x, "emmc-2x", sdio_parents, 0x2e4,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data dpu_parents[] = अणु
	अणु .hw = &twpll_153m6.hw  पूर्ण,
	अणु .hw = &twpll_192m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(dpu_clk, "dpu", dpu_parents, 0x2f4,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data dpu_dpi_parents[] = अणु
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
	अणु .hw = &twpll_192m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(dpu_dpi, "dpu-dpi", dpu_dpi_parents, 0x2f8,
			  0, 2, 8, 4, 0);

अटल स्थिर काष्ठा clk_parent_data otg_ref_parents[] = अणु
	अणु .hw = &twpll_12m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(otg_ref_clk, "otg-ref-clk", otg_ref_parents, 0x308,
			 0, 1, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data sdphy_apb_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_48m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(sdphy_apb_clk, "sdphy-apb-clk", sdphy_apb_parents, 0x330,
			 0, 1, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data alg_io_apb_parents[] = अणु
	अणु .hw = &rco_4m.hw  पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_48m.hw  पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(alg_io_apb_clk, "alg-io-apb-clk", alg_io_apb_parents, 0x33c,
			 0, 1, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data gpu_parents[] = अणु
	अणु .hw = &twpll_153m6.hw  पूर्ण,
	अणु .hw = &twpll_192m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
	अणु .hw = &gpll.common.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(gpu_core, "gpu-core", gpu_parents, 0x344,
			  0, 3, 8, 2, 0);
अटल SPRD_COMP_CLK_DATA(gpu_soc, "gpu-soc", gpu_parents, 0x348,
			  0, 3, 8, 2, 0);

अटल स्थिर काष्ठा clk_parent_data mm_emc_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &isppll_468m.hw  पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(mm_emc, "mm-emc", mm_emc_parents, 0x350,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data mm_ahb_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(mm_ahb, "mm-ahb", mm_ahb_parents, 0x354,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data bpc_clk_parents[] = अणु
	अणु .hw = &twpll_192m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &isppll_468m.hw  पूर्ण,
	अणु .hw = &dpll0_622m3.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(bpc_clk, "bpc-clk", bpc_clk_parents, 0x358,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data dcam_अगर_parents[] = अणु
	अणु .hw = &twpll_192m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(dcam_अगर_clk, "dcam-if-clk", dcam_अगर_parents, 0x35c,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data isp_parents[] = अणु
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &isppll_468m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(isp_clk, "isp-clk", isp_parents, 0x360,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data jpg_parents[] = अणु
	अणु .hw = &twpll_76m8.hw  पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(jpg_clk, "jpg-clk", jpg_parents, 0x364,
			 0, 2, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(cpp_clk, "cpp-clk", jpg_parents, 0x368,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data sensor_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_48m.hw  पूर्ण,
	अणु .hw = &twpll_76m8.hw  पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(sensor0_clk, "sensor0-clk", sensor_parents, 0x36c,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(sensor1_clk, "sensor1-clk", sensor_parents, 0x370,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(sensor2_clk, "sensor2-clk", sensor_parents, 0x374,
			  0, 2, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data mm_vemc_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &isppll_468m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(mm_vemc, "mm-vemc", mm_vemc_parents, 0x378,
			 0, 2, SC9863A_MUX_FLAG);

अटल SPRD_MUX_CLK_DATA(mm_vahb, "mm-vahb", mm_ahb_parents, 0x37c,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data vsp_parents[] = अणु
	अणु .hw = &twpll_76m8.hw  पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(clk_vsp, "vsp-clk", vsp_parents, 0x380,
			 0, 3, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data core_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
	अणु .hw = &twpll_768m.hw  पूर्ण,
	अणु .hw = &lpll.common.hw  पूर्ण,
	अणु .hw = &dpll0.common.hw  पूर्ण,
	अणु .hw = &mpll2.common.hw  पूर्ण,
	अणु .hw = &mpll0.common.hw  पूर्ण,
	अणु .hw = &mpll1.common.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(core0_clk, "core0-clk", core_parents, 0xa20,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core1_clk, "core1-clk", core_parents, 0xa24,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core2_clk, "core2-clk", core_parents, 0xa28,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core3_clk, "core3-clk", core_parents, 0xa2c,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core4_clk, "core4-clk", core_parents, 0xa30,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core5_clk, "core5-clk", core_parents, 0xa34,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core6_clk, "core6-clk", core_parents, 0xa38,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(core7_clk, "core7-clk", core_parents, 0xa3c,
			  0, 3, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(scu_clk, "scu-clk", core_parents, 0xa40,
			  0, 3, 8, 3, 0);

अटल SPRD_DIV_CLK_HW(ace_clk, "ace-clk", &scu_clk.common.hw, 0xa44,
		       8, 3, 0);
अटल SPRD_DIV_CLK_HW(axi_periph_clk, "axi-periph-clk", &scu_clk.common.hw, 0xa48,
		       8, 3, 0);
अटल SPRD_DIV_CLK_HW(axi_acp_clk, "axi-acp-clk", &scu_clk.common.hw, 0xa4c,
		       8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data atb_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
	अणु .hw = &mpll2.common.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(atb_clk, "atb-clk", atb_parents, 0xa50,
			  0, 2, 8, 3, 0);
अटल SPRD_DIV_CLK_HW(debug_apb_clk, "debug-apb-clk", &atb_clk.common.hw, 0xa54,
		       8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data gic_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
	अणु .hw = &twpll_384m.hw  पूर्ण,
	अणु .hw = &twpll_512m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(gic_clk, "gic-clk", gic_parents, 0xa58,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(periph_clk, "periph-clk", gic_parents, 0xa5c,
			  0, 2, 8, 3, 0);

अटल काष्ठा sprd_clk_common *sc9863a_aon_clks[] = अणु
	/* address base is 0x402d0000 */
	&emc_clk.common,
	&aon_apb.common,
	&adi_clk.common,
	&aux0_clk.common,
	&aux1_clk.common,
	&aux2_clk.common,
	&probe_clk.common,
	&pwm0_clk.common,
	&pwm1_clk.common,
	&pwm2_clk.common,
	&aon_thm_clk.common,
	&audअगर_clk.common,
	&cpu_dap_clk.common,
	&cpu_ts_clk.common,
	&djtag_tck_clk.common,
	&emc_ref_clk.common,
	&cssys_clk.common,
	&aon_pmu_clk.common,
	&pmu_26m_clk.common,
	&aon_पंचांगr_clk.common,
	&घातer_cpu_clk.common,
	&ap_axi.common,
	&sdio0_2x.common,
	&sdio1_2x.common,
	&sdio2_2x.common,
	&emmc_2x.common,
	&dpu_clk.common,
	&dpu_dpi.common,
	&otg_ref_clk.common,
	&sdphy_apb_clk.common,
	&alg_io_apb_clk.common,
	&gpu_core.common,
	&gpu_soc.common,
	&mm_emc.common,
	&mm_ahb.common,
	&bpc_clk.common,
	&dcam_अगर_clk.common,
	&isp_clk.common,
	&jpg_clk.common,
	&cpp_clk.common,
	&sensor0_clk.common,
	&sensor1_clk.common,
	&sensor2_clk.common,
	&mm_vemc.common,
	&mm_vahb.common,
	&clk_vsp.common,
	&core0_clk.common,
	&core1_clk.common,
	&core2_clk.common,
	&core3_clk.common,
	&core4_clk.common,
	&core5_clk.common,
	&core6_clk.common,
	&core7_clk.common,
	&scu_clk.common,
	&ace_clk.common,
	&axi_periph_clk.common,
	&axi_acp_clk.common,
	&atb_clk.common,
	&debug_apb_clk.common,
	&gic_clk.common,
	&periph_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_aon_clk_hws = अणु
	.hws	= अणु
		[CLK_13M]		= &clk_13m.hw,
		[CLK_6M5]		= &clk_6m5.hw,
		[CLK_4M3]		= &clk_4m3.hw,
		[CLK_2M]		= &clk_2m.hw,
		[CLK_250K]		= &clk_250k.hw,
		[CLK_RCO_25M]		= &rco_25m.hw,
		[CLK_RCO_4M]		= &rco_4m.hw,
		[CLK_RCO_2M]		= &rco_2m.hw,
		[CLK_EMC]		= &emc_clk.common.hw,
		[CLK_AON_APB]		= &aon_apb.common.hw,
		[CLK_ADI]		= &adi_clk.common.hw,
		[CLK_AUX0]		= &aux0_clk.common.hw,
		[CLK_AUX1]		= &aux1_clk.common.hw,
		[CLK_AUX2]		= &aux2_clk.common.hw,
		[CLK_PROBE]		= &probe_clk.common.hw,
		[CLK_PWM0]		= &pwm0_clk.common.hw,
		[CLK_PWM1]		= &pwm1_clk.common.hw,
		[CLK_PWM2]		= &pwm2_clk.common.hw,
		[CLK_AON_THM]		= &aon_thm_clk.common.hw,
		[CLK_AUDIF]		= &audअगर_clk.common.hw,
		[CLK_CPU_DAP]		= &cpu_dap_clk.common.hw,
		[CLK_CPU_TS]		= &cpu_ts_clk.common.hw,
		[CLK_DJTAG_TCK]		= &djtag_tck_clk.common.hw,
		[CLK_EMC_REF]		= &emc_ref_clk.common.hw,
		[CLK_CSSYS]		= &cssys_clk.common.hw,
		[CLK_AON_PMU]		= &aon_pmu_clk.common.hw,
		[CLK_PMU_26M]		= &pmu_26m_clk.common.hw,
		[CLK_AON_TMR]		= &aon_पंचांगr_clk.common.hw,
		[CLK_POWER_CPU]		= &घातer_cpu_clk.common.hw,
		[CLK_AP_AXI]		= &ap_axi.common.hw,
		[CLK_SDIO0_2X]		= &sdio0_2x.common.hw,
		[CLK_SDIO1_2X]		= &sdio1_2x.common.hw,
		[CLK_SDIO2_2X]		= &sdio2_2x.common.hw,
		[CLK_EMMC_2X]		= &emmc_2x.common.hw,
		[CLK_DPU]		= &dpu_clk.common.hw,
		[CLK_DPU_DPI]		= &dpu_dpi.common.hw,
		[CLK_OTG_REF]		= &otg_ref_clk.common.hw,
		[CLK_SDPHY_APB]		= &sdphy_apb_clk.common.hw,
		[CLK_ALG_IO_APB]	= &alg_io_apb_clk.common.hw,
		[CLK_GPU_CORE]		= &gpu_core.common.hw,
		[CLK_GPU_SOC]		= &gpu_soc.common.hw,
		[CLK_MM_EMC]		= &mm_emc.common.hw,
		[CLK_MM_AHB]		= &mm_ahb.common.hw,
		[CLK_BPC]		= &bpc_clk.common.hw,
		[CLK_DCAM_IF]		= &dcam_अगर_clk.common.hw,
		[CLK_ISP]		= &isp_clk.common.hw,
		[CLK_JPG]		= &jpg_clk.common.hw,
		[CLK_CPP]		= &cpp_clk.common.hw,
		[CLK_SENSOR0]		= &sensor0_clk.common.hw,
		[CLK_SENSOR1]		= &sensor1_clk.common.hw,
		[CLK_SENSOR2]		= &sensor2_clk.common.hw,
		[CLK_MM_VEMC]		= &mm_vemc.common.hw,
		[CLK_MM_VAHB]		= &mm_vahb.common.hw,
		[CLK_VSP]		= &clk_vsp.common.hw,
		[CLK_CORE0]		= &core0_clk.common.hw,
		[CLK_CORE1]		= &core1_clk.common.hw,
		[CLK_CORE2]		= &core2_clk.common.hw,
		[CLK_CORE3]		= &core3_clk.common.hw,
		[CLK_CORE4]		= &core4_clk.common.hw,
		[CLK_CORE5]		= &core5_clk.common.hw,
		[CLK_CORE6]		= &core6_clk.common.hw,
		[CLK_CORE7]		= &core7_clk.common.hw,
		[CLK_SCU]		= &scu_clk.common.hw,
		[CLK_ACE]		= &ace_clk.common.hw,
		[CLK_AXI_PERIPH]	= &axi_periph_clk.common.hw,
		[CLK_AXI_ACP]		= &axi_acp_clk.common.hw,
		[CLK_ATB]		= &atb_clk.common.hw,
		[CLK_DEBUG_APB]		= &debug_apb_clk.common.hw,
		[CLK_GIC]		= &gic_clk.common.hw,
		[CLK_PERIPH]		= &periph_clk.common.hw,
	पूर्ण,
	.num	= CLK_AON_CLK_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_aon_clk_desc = अणु
	.clk_clks	= sc9863a_aon_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_aon_clks),
	.hw_clks	= &sc9863a_aon_clk_hws,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data ap_apb_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_64m.hw  पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(ap_apb, "ap-apb", ap_apb_parents, 0x20,
			 0, 2, SC9863A_MUX_FLAG);

अटल स्थिर काष्ठा clk_parent_data ap_ce_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(ap_ce, "ap-ce", ap_ce_parents, 0x24,
			  0, 1, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data nandc_ecc_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_256m.hw  पूर्ण,
	अणु .hw = &twpll_307m2.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(nandc_ecc, "nandc-ecc", nandc_ecc_parents, 0x28,
			  0, 2, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data nandc_26m_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(nandc_26m, "nandc-26m", nandc_26m_parents, 0x2c,
			 0, 1, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(emmc_32k, "emmc-32k", nandc_26m_parents, 0x30,
			 0, 1, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(sdio0_32k, "sdio0-32k", nandc_26m_parents, 0x34,
			 0, 1, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(sdio1_32k, "sdio1-32k", nandc_26m_parents, 0x38,
			 0, 1, SC9863A_MUX_FLAG);
अटल SPRD_MUX_CLK_DATA(sdio2_32k, "sdio2-32k", nandc_26m_parents, 0x3c,
			 0, 1, SC9863A_MUX_FLAG);

अटल SPRD_GATE_CLK_HW(otg_uपंचांगi, "otg-utmi", &aon_apb.common.hw, 0x40,
			BIT(16), 0, 0);

अटल स्थिर काष्ठा clk_parent_data ap_uart_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_48m.hw  पूर्ण,
	अणु .hw = &twpll_51m2.hw  पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(ap_uart0,	"ap-uart0",	ap_uart_parents, 0x44,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_uart1,	"ap-uart1",	ap_uart_parents, 0x48,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_uart2,	"ap-uart2",	ap_uart_parents, 0x4c,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_uart3,	"ap-uart3",	ap_uart_parents, 0x50,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_uart4,	"ap-uart4",	ap_uart_parents, 0x54,
			  0, 2, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data i2c_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_48m.hw  पूर्ण,
	अणु .hw = &twpll_51m2.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(ap_i2c0, "ap-i2c0", i2c_parents, 0x58,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_i2c1, "ap-i2c1", i2c_parents, 0x5c,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_i2c2, "ap-i2c2", i2c_parents, 0x60,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_i2c3, "ap-i2c3", i2c_parents, 0x64,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_i2c4, "ap-i2c4", i2c_parents, 0x68,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_i2c5, "ap-i2c5", i2c_parents, 0x6c,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_i2c6, "ap-i2c6", i2c_parents, 0x70,
			  0, 2, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data spi_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
	अणु .hw = &twpll_192m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(ap_spi0, "ap-spi0", spi_parents, 0x74,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_spi1, "ap-spi1", spi_parents, 0x78,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_spi2, "ap-spi2", spi_parents, 0x7c,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_spi3, "ap-spi3", spi_parents, 0x80,
			  0, 2, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data iis_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
	अणु .hw = &twpll_153m6.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(ap_iis0, "ap-iis0", iis_parents, 0x84,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_iis1, "ap-iis1", iis_parents, 0x88,
			  0, 2, 8, 3, 0);
अटल SPRD_COMP_CLK_DATA(ap_iis2, "ap-iis2", iis_parents, 0x8c,
			  0, 2, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data sim0_parents[] = अणु
	अणु .fw_name = "ext-26m" पूर्ण,
	अणु .hw = &twpll_51m2.hw  पूर्ण,
	अणु .hw = &twpll_64m.hw  पूर्ण,
	अणु .hw = &twpll_96m.hw  पूर्ण,
	अणु .hw = &twpll_128m.hw  पूर्ण,
पूर्ण;
अटल SPRD_COMP_CLK_DATA(sim0, "sim0", sim0_parents, 0x90,
			  0, 3, 8, 3, 0);

अटल स्थिर काष्ठा clk_parent_data sim0_32k_parents[] = अणु
	अणु .fw_name = "ext-32k" पूर्ण,
	अणु .fw_name = "ext-26m" पूर्ण,
पूर्ण;
अटल SPRD_MUX_CLK_DATA(sim0_32k, "sim0-32k", sim0_32k_parents, 0x94,
			 0, 1, SC9863A_MUX_FLAG);

अटल काष्ठा sprd_clk_common *sc9863a_ap_clks[] = अणु
	/* address base is 0x21500000 */
	&ap_apb.common,
	&ap_ce.common,
	&nandc_ecc.common,
	&nandc_26m.common,
	&emmc_32k.common,
	&sdio0_32k.common,
	&sdio1_32k.common,
	&sdio2_32k.common,
	&otg_uपंचांगi.common,
	&ap_uart0.common,
	&ap_uart1.common,
	&ap_uart2.common,
	&ap_uart3.common,
	&ap_uart4.common,
	&ap_i2c0.common,
	&ap_i2c1.common,
	&ap_i2c2.common,
	&ap_i2c3.common,
	&ap_i2c4.common,
	&ap_i2c5.common,
	&ap_i2c6.common,
	&ap_spi0.common,
	&ap_spi1.common,
	&ap_spi2.common,
	&ap_spi3.common,
	&ap_iis0.common,
	&ap_iis1.common,
	&ap_iis2.common,
	&sim0.common,
	&sim0_32k.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_ap_clk_hws = अणु
	.hws	= अणु
		[CLK_AP_APB]	= &ap_apb.common.hw,
		[CLK_AP_CE]	= &ap_ce.common.hw,
		[CLK_न_अंकDC_ECC]	= &nandc_ecc.common.hw,
		[CLK_न_अंकDC_26M]	= &nandc_26m.common.hw,
		[CLK_EMMC_32K]	= &emmc_32k.common.hw,
		[CLK_SDIO0_32K]	= &sdio0_32k.common.hw,
		[CLK_SDIO1_32K]	= &sdio1_32k.common.hw,
		[CLK_SDIO2_32K]	= &sdio2_32k.common.hw,
		[CLK_OTG_UTMI]	= &otg_uपंचांगi.common.hw,
		[CLK_AP_UART0]	= &ap_uart0.common.hw,
		[CLK_AP_UART1]	= &ap_uart1.common.hw,
		[CLK_AP_UART2]	= &ap_uart2.common.hw,
		[CLK_AP_UART3]	= &ap_uart3.common.hw,
		[CLK_AP_UART4]	= &ap_uart4.common.hw,
		[CLK_AP_I2C0]	= &ap_i2c0.common.hw,
		[CLK_AP_I2C1]	= &ap_i2c1.common.hw,
		[CLK_AP_I2C2]	= &ap_i2c2.common.hw,
		[CLK_AP_I2C3]	= &ap_i2c3.common.hw,
		[CLK_AP_I2C4]	= &ap_i2c4.common.hw,
		[CLK_AP_I2C5]	= &ap_i2c5.common.hw,
		[CLK_AP_I2C6]	= &ap_i2c6.common.hw,
		[CLK_AP_SPI0]	= &ap_spi0.common.hw,
		[CLK_AP_SPI1]	= &ap_spi1.common.hw,
		[CLK_AP_SPI2]	= &ap_spi2.common.hw,
		[CLK_AP_SPI3]	= &ap_spi3.common.hw,
		[CLK_AP_IIS0]	= &ap_iis0.common.hw,
		[CLK_AP_IIS1]	= &ap_iis1.common.hw,
		[CLK_AP_IIS2]	= &ap_iis2.common.hw,
		[CLK_SIM0]	= &sim0.common.hw,
		[CLK_SIM0_32K]	= &sim0_32k.common.hw,
	पूर्ण,
	.num	= CLK_AP_CLK_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_ap_clk_desc = अणु
	.clk_clks	= sc9863a_ap_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_ap_clks),
	.hw_clks	= &sc9863a_ap_clk_hws,
पूर्ण;

अटल SPRD_SC_GATE_CLK_HW(otg_eb, "otg-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(4), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dma_eb, "dma-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(5), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ce_eb, "ce-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(6), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(nandc_eb, "nandc-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(7), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(sdio0_eb, "sdio0-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(8), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(sdio1_eb, "sdio1-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(9), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(sdio2_eb, "sdio2-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(10), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(emmc_eb, "emmc-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(11), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(emmc_32k_eb, "emmc-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(27), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(sdio0_32k_eb, "sdio0-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(28), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(sdio1_32k_eb, "sdio1-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(29), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(sdio2_32k_eb, "sdio2-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(30), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(nandc_26m_eb, "nandc-26m-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(31), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dma_eb2, "dma-eb2", &ap_axi.common.hw, 0x18,
			   0x1000, BIT(0), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ce_eb2, "ce-eb2", &ap_axi.common.hw, 0x18,
			   0x1000, BIT(1), 0, 0);

अटल काष्ठा sprd_clk_common *sc9863a_apahb_gate_clks[] = अणु
	/* address base is 0x20e00000 */
	&otg_eb.common,
	&dma_eb.common,
	&ce_eb.common,
	&nandc_eb.common,
	&sdio0_eb.common,
	&sdio1_eb.common,
	&sdio2_eb.common,
	&emmc_eb.common,
	&emmc_32k_eb.common,
	&sdio0_32k_eb.common,
	&sdio1_32k_eb.common,
	&sdio2_32k_eb.common,
	&nandc_26m_eb.common,
	&dma_eb2.common,
	&ce_eb2.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_apahb_gate_hws = अणु
	.hws	= अणु
		[CLK_OTG_EB]		= &otg_eb.common.hw,
		[CLK_DMA_EB]		= &dma_eb.common.hw,
		[CLK_CE_EB]		= &ce_eb.common.hw,
		[CLK_न_अंकDC_EB]		= &nandc_eb.common.hw,
		[CLK_SDIO0_EB]		= &sdio0_eb.common.hw,
		[CLK_SDIO1_EB]		= &sdio1_eb.common.hw,
		[CLK_SDIO2_EB]		= &sdio2_eb.common.hw,
		[CLK_EMMC_EB]		= &emmc_eb.common.hw,
		[CLK_EMMC_32K_EB]	= &emmc_32k_eb.common.hw,
		[CLK_SDIO0_32K_EB]	= &sdio0_32k_eb.common.hw,
		[CLK_SDIO1_32K_EB]	= &sdio1_32k_eb.common.hw,
		[CLK_SDIO2_32K_EB]	= &sdio2_32k_eb.common.hw,
		[CLK_न_अंकDC_26M_EB]	= &nandc_26m_eb.common.hw,
		[CLK_DMA_EB2]		= &dma_eb2.common.hw,
		[CLK_CE_EB2]		= &ce_eb2.common.hw,
	पूर्ण,
	.num	= CLK_AP_AHB_GATE_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_apahb_gate_desc = अणु
	.clk_clks	= sc9863a_apahb_gate_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_apahb_gate_clks),
	.hw_clks	= &sc9863a_apahb_gate_hws,
पूर्ण;

/* aon gate घड़ीs */
अटल SPRD_SC_GATE_CLK_HW(gpio_eb, "gpio-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(3), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(pwm0_eb,	"pwm0-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(4), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(pwm1_eb,	"pwm1-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(5), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(pwm2_eb,	"pwm2-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(6), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(pwm3_eb,	"pwm3-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(7), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(kpd_eb,	"kpd-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(8), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_syst_eb,	"aon-syst-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(9), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_syst_eb,	"ap-syst-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(10), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_पंचांगr_eb,	"aon-tmr-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(11), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(efuse_eb,	"efuse-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(13), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(eic_eb,	"eic-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(14), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(पूर्णांकc_eb,	"intc-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(15), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(adi_eb,	"adi-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(16), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(audअगर_eb,	"audif-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(17), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aud_eb,	"aud-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(18), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(vbc_eb,	"vbc-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(19), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(pin_eb,	"pin-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(20), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_wdg_eb,	"ap-wdg-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(24), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mm_eb,	"mm-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(25), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_apb_ckg_eb, "aon-apb-ckg-eb", &aon_apb.common.hw,
			   0x0, 0x1000, BIT(26), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ca53_ts0_eb, "ca53-ts0-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(28), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ca53_ts1_eb, "ca53-ts1-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(29), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ca53_dap_eb, "ca53-dap-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(30), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(pmu_eb,	"pmu-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(0), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(thm_eb,	"thm-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(1), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(aux0_eb,	"aux0-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(2), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(aux1_eb,	"aux1-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(3), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aux2_eb,	"aux2-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(4), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(probe_eb,	"probe-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(5), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(emc_ref_eb,	"emc-ref-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(7), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ca53_wdg_eb,	"ca53-wdg-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(8), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पंचांगr1_eb,	"ap-tmr1-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(9), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पंचांगr2_eb,	"ap-tmr2-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(10), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(disp_emc_eb,	"disp-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(11), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(zip_emc_eb,	"zip-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(12), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(gsp_emc_eb,	"gsp-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(13), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mm_vsp_eb,	"mm-vsp-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(14), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mdar_eb,	"mdar-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(17), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(rtc4m0_cal_eb, "rtc4m0-cal-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(18), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(rtc4m1_cal_eb, "rtc4m1-cal-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(19), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(djtag_eb,	"djtag-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(20), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mbox_eb,	"mbox-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(21), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_dma_eb,	"aon-dma-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(22), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_apb_def_eb, "aon-apb-def-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(25), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ca5_ts0_eb,	"ca5-ts0-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(26), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dbg_eb,	"dbg-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(28), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dbg_emc_eb,	"dbg-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(29), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(cross_trig_eb, "cross-trig-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(30), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(serdes_dphy_eb, "serdes-dphy-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(31), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(arch_rtc_eb,	"arch-rtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(0), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(kpd_rtc_eb,	"kpd-rtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(1), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_syst_rtc_eb, "aon-syst-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(2), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_syst_rtc_eb, "ap-syst-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(3), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_पंचांगr_rtc_eb, "aon-tmr-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(4), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पंचांगr0_rtc_eb, "ap-tmr0-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(5), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(eic_rtc_eb, "eic-rtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(6), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(eic_rtcdv5_eb, "eic-rtcdv5-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(7), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_wdg_rtc_eb, "ap-wdg-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(8), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ca53_wdg_rtc_eb, "ca53-wdg-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(9), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(thm_rtc_eb, "thm-rtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(10), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(athma_rtc_eb, "athma-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(11), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(gthma_rtc_eb, "gthma-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(12), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(athma_rtc_a_eb, "athma-rtc-a-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(13), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(gthma_rtc_a_eb, "gthma-rtc-a-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(14), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पंचांगr1_rtc_eb, "ap-tmr1-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(15), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पंचांगr2_rtc_eb, "ap-tmr2-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(16), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dxco_lc_rtc_eb, "dxco-lc-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(17), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(bb_cal_rtc_eb, "bb-cal-rtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(18), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(gpu_eb, "gpu-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(0), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(disp_eb, "disp-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(2), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mm_emc_eb, "mm-emc-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(3), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(घातer_cpu_eb, "power-cpu-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(10), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(hw_i2c_eb, "hw-i2c-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(11), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mm_vsp_emc_eb, "mm-vsp-emc-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(14), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(vsp_eb, "vsp-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(16), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(cssys_eb, "cssys-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(4), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dmc_eb, "dmc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(5), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(rosc_eb, "rosc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(7), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(s_d_cfg_eb, "s-d-cfg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(8), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(s_d_ref_eb, "s-d-ref-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(9), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(b_dma_eb, "b-dma-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(10), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(anlg_eb, "anlg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(11), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(anlg_apb_eb, "anlg-apb-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(13), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(bsmपंचांगr_eb, "bsmtmr-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(14), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_axi_eb, "ap-axi-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(15), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पूर्णांकc0_eb, "ap-intc0-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(16), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पूर्णांकc1_eb, "ap-intc1-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(17), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पूर्णांकc2_eb, "ap-intc2-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(18), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पूर्णांकc3_eb, "ap-intc3-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(19), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पूर्णांकc4_eb, "ap-intc4-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(20), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(ap_पूर्णांकc5_eb, "ap-intc5-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(21), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_HW(scc_eb, "scc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(22), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dphy_cfg_eb, "dphy-cfg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(23), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(dphy_ref_eb, "dphy-ref-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(24), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(cphy_cfg_eb, "cphy-cfg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(25), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(otg_ref_eb, "otg-ref-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(26), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(serdes_eb, "serdes-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(27), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(aon_ap_emc_eb, "aon-ap-emc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(28), 0, 0);
अटल काष्ठा sprd_clk_common *sc9863a_aonapb_gate_clks[] = अणु
	/* address base is 0x402e0000 */
	&gpio_eb.common,
	&pwm0_eb.common,
	&pwm1_eb.common,
	&pwm2_eb.common,
	&pwm3_eb.common,
	&kpd_eb.common,
	&aon_syst_eb.common,
	&ap_syst_eb.common,
	&aon_पंचांगr_eb.common,
	&efuse_eb.common,
	&eic_eb.common,
	&पूर्णांकc_eb.common,
	&adi_eb.common,
	&audअगर_eb.common,
	&aud_eb.common,
	&vbc_eb.common,
	&pin_eb.common,
	&ap_wdg_eb.common,
	&mm_eb.common,
	&aon_apb_ckg_eb.common,
	&ca53_ts0_eb.common,
	&ca53_ts1_eb.common,
	&ca53_dap_eb.common,
	&pmu_eb.common,
	&thm_eb.common,
	&aux0_eb.common,
	&aux1_eb.common,
	&aux2_eb.common,
	&probe_eb.common,
	&emc_ref_eb.common,
	&ca53_wdg_eb.common,
	&ap_पंचांगr1_eb.common,
	&ap_पंचांगr2_eb.common,
	&disp_emc_eb.common,
	&zip_emc_eb.common,
	&gsp_emc_eb.common,
	&mm_vsp_eb.common,
	&mdar_eb.common,
	&rtc4m0_cal_eb.common,
	&rtc4m1_cal_eb.common,
	&djtag_eb.common,
	&mbox_eb.common,
	&aon_dma_eb.common,
	&aon_apb_def_eb.common,
	&ca5_ts0_eb.common,
	&dbg_eb.common,
	&dbg_emc_eb.common,
	&cross_trig_eb.common,
	&serdes_dphy_eb.common,
	&arch_rtc_eb.common,
	&kpd_rtc_eb.common,
	&aon_syst_rtc_eb.common,
	&ap_syst_rtc_eb.common,
	&aon_पंचांगr_rtc_eb.common,
	&ap_पंचांगr0_rtc_eb.common,
	&eic_rtc_eb.common,
	&eic_rtcdv5_eb.common,
	&ap_wdg_rtc_eb.common,
	&ca53_wdg_rtc_eb.common,
	&thm_rtc_eb.common,
	&athma_rtc_eb.common,
	&gthma_rtc_eb.common,
	&athma_rtc_a_eb.common,
	&gthma_rtc_a_eb.common,
	&ap_पंचांगr1_rtc_eb.common,
	&ap_पंचांगr2_rtc_eb.common,
	&dxco_lc_rtc_eb.common,
	&bb_cal_rtc_eb.common,
	&gpu_eb.common,
	&disp_eb.common,
	&mm_emc_eb.common,
	&घातer_cpu_eb.common,
	&hw_i2c_eb.common,
	&mm_vsp_emc_eb.common,
	&vsp_eb.common,
	&cssys_eb.common,
	&dmc_eb.common,
	&rosc_eb.common,
	&s_d_cfg_eb.common,
	&s_d_ref_eb.common,
	&b_dma_eb.common,
	&anlg_eb.common,
	&anlg_apb_eb.common,
	&bsmपंचांगr_eb.common,
	&ap_axi_eb.common,
	&ap_पूर्णांकc0_eb.common,
	&ap_पूर्णांकc1_eb.common,
	&ap_पूर्णांकc2_eb.common,
	&ap_पूर्णांकc3_eb.common,
	&ap_पूर्णांकc4_eb.common,
	&ap_पूर्णांकc5_eb.common,
	&scc_eb.common,
	&dphy_cfg_eb.common,
	&dphy_ref_eb.common,
	&cphy_cfg_eb.common,
	&otg_ref_eb.common,
	&serdes_eb.common,
	&aon_ap_emc_eb.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_aonapb_gate_hws = अणु
	.hws	= अणु
		[CLK_GPIO_EB]		= &gpio_eb.common.hw,
		[CLK_PWM0_EB]		= &pwm0_eb.common.hw,
		[CLK_PWM1_EB]		= &pwm1_eb.common.hw,
		[CLK_PWM2_EB]		= &pwm2_eb.common.hw,
		[CLK_PWM3_EB]		= &pwm3_eb.common.hw,
		[CLK_KPD_EB]		= &kpd_eb.common.hw,
		[CLK_AON_SYST_EB]	= &aon_syst_eb.common.hw,
		[CLK_AP_SYST_EB]	= &ap_syst_eb.common.hw,
		[CLK_AON_TMR_EB]	= &aon_पंचांगr_eb.common.hw,
		[CLK_EFUSE_EB]		= &efuse_eb.common.hw,
		[CLK_EIC_EB]		= &eic_eb.common.hw,
		[CLK_INTC_EB]		= &पूर्णांकc_eb.common.hw,
		[CLK_ADI_EB]		= &adi_eb.common.hw,
		[CLK_AUDIF_EB]		= &audअगर_eb.common.hw,
		[CLK_AUD_EB]		= &aud_eb.common.hw,
		[CLK_VBC_EB]		= &vbc_eb.common.hw,
		[CLK_PIN_EB]		= &pin_eb.common.hw,
		[CLK_AP_WDG_EB]		= &ap_wdg_eb.common.hw,
		[CLK_MM_EB]		= &mm_eb.common.hw,
		[CLK_AON_APB_CKG_EB]	= &aon_apb_ckg_eb.common.hw,
		[CLK_CA53_TS0_EB]	= &ca53_ts0_eb.common.hw,
		[CLK_CA53_TS1_EB]	= &ca53_ts1_eb.common.hw,
		[CLK_CS53_DAP_EB]	= &ca53_dap_eb.common.hw,
		[CLK_PMU_EB]		= &pmu_eb.common.hw,
		[CLK_THM_EB]		= &thm_eb.common.hw,
		[CLK_AUX0_EB]		= &aux0_eb.common.hw,
		[CLK_AUX1_EB]		= &aux1_eb.common.hw,
		[CLK_AUX2_EB]		= &aux2_eb.common.hw,
		[CLK_PROBE_EB]		= &probe_eb.common.hw,
		[CLK_EMC_REF_EB]	= &emc_ref_eb.common.hw,
		[CLK_CA53_WDG_EB]	= &ca53_wdg_eb.common.hw,
		[CLK_AP_TMR1_EB]	= &ap_पंचांगr1_eb.common.hw,
		[CLK_AP_TMR2_EB]	= &ap_पंचांगr2_eb.common.hw,
		[CLK_DISP_EMC_EB]	= &disp_emc_eb.common.hw,
		[CLK_ZIP_EMC_EB]	= &zip_emc_eb.common.hw,
		[CLK_GSP_EMC_EB]	= &gsp_emc_eb.common.hw,
		[CLK_MM_VSP_EB]		= &mm_vsp_eb.common.hw,
		[CLK_MDAR_EB]		= &mdar_eb.common.hw,
		[CLK_RTC4M0_CAL_EB]	= &rtc4m0_cal_eb.common.hw,
		[CLK_RTC4M1_CAL_EB]	= &rtc4m1_cal_eb.common.hw,
		[CLK_DJTAG_EB]		= &djtag_eb.common.hw,
		[CLK_MBOX_EB]		= &mbox_eb.common.hw,
		[CLK_AON_DMA_EB]	= &aon_dma_eb.common.hw,
		[CLK_AON_APB_DEF_EB]	= &aon_apb_def_eb.common.hw,
		[CLK_CA5_TS0_EB]	= &ca5_ts0_eb.common.hw,
		[CLK_DBG_EB]		= &dbg_eb.common.hw,
		[CLK_DBG_EMC_EB]	= &dbg_emc_eb.common.hw,
		[CLK_CROSS_TRIG_EB]	= &cross_trig_eb.common.hw,
		[CLK_SERDES_DPHY_EB]	= &serdes_dphy_eb.common.hw,
		[CLK_ARCH_RTC_EB]	= &arch_rtc_eb.common.hw,
		[CLK_KPD_RTC_EB]	= &kpd_rtc_eb.common.hw,
		[CLK_AON_SYST_RTC_EB]	= &aon_syst_rtc_eb.common.hw,
		[CLK_AP_SYST_RTC_EB]	= &ap_syst_rtc_eb.common.hw,
		[CLK_AON_TMR_RTC_EB]	= &aon_पंचांगr_rtc_eb.common.hw,
		[CLK_AP_TMR0_RTC_EB]	= &ap_पंचांगr0_rtc_eb.common.hw,
		[CLK_EIC_RTC_EB]	= &eic_rtc_eb.common.hw,
		[CLK_EIC_RTCDV5_EB]	= &eic_rtcdv5_eb.common.hw,
		[CLK_AP_WDG_RTC_EB]	= &ap_wdg_rtc_eb.common.hw,
		[CLK_CA53_WDG_RTC_EB]	= &ca53_wdg_rtc_eb.common.hw,
		[CLK_THM_RTC_EB]	= &thm_rtc_eb.common.hw,
		[CLK_ATHMA_RTC_EB]	= &athma_rtc_eb.common.hw,
		[CLK_GTHMA_RTC_EB]	= &gthma_rtc_eb.common.hw,
		[CLK_ATHMA_RTC_A_EB]	= &athma_rtc_a_eb.common.hw,
		[CLK_GTHMA_RTC_A_EB]	= &gthma_rtc_a_eb.common.hw,
		[CLK_AP_TMR1_RTC_EB]	= &ap_पंचांगr1_rtc_eb.common.hw,
		[CLK_AP_TMR2_RTC_EB]	= &ap_पंचांगr2_rtc_eb.common.hw,
		[CLK_DXCO_LC_RTC_EB]	= &dxco_lc_rtc_eb.common.hw,
		[CLK_BB_CAL_RTC_EB]	= &bb_cal_rtc_eb.common.hw,
		[CLK_GNU_EB]		= &gpu_eb.common.hw,
		[CLK_DISP_EB]		= &disp_eb.common.hw,
		[CLK_MM_EMC_EB]		= &mm_emc_eb.common.hw,
		[CLK_POWER_CPU_EB]	= &घातer_cpu_eb.common.hw,
		[CLK_HW_I2C_EB]		= &hw_i2c_eb.common.hw,
		[CLK_MM_VSP_EMC_EB]	= &mm_vsp_emc_eb.common.hw,
		[CLK_VSP_EB]		= &vsp_eb.common.hw,
		[CLK_CSSYS_EB]		= &cssys_eb.common.hw,
		[CLK_DMC_EB]		= &dmc_eb.common.hw,
		[CLK_ROSC_EB]		= &rosc_eb.common.hw,
		[CLK_S_D_CFG_EB]	= &s_d_cfg_eb.common.hw,
		[CLK_S_D_REF_EB]	= &s_d_ref_eb.common.hw,
		[CLK_B_DMA_EB]		= &b_dma_eb.common.hw,
		[CLK_ANLG_EB]		= &anlg_eb.common.hw,
		[CLK_ANLG_APB_EB]	= &anlg_apb_eb.common.hw,
		[CLK_BSMTMR_EB]		= &bsmपंचांगr_eb.common.hw,
		[CLK_AP_AXI_EB]		= &ap_axi_eb.common.hw,
		[CLK_AP_INTC0_EB]	= &ap_पूर्णांकc0_eb.common.hw,
		[CLK_AP_INTC1_EB]	= &ap_पूर्णांकc1_eb.common.hw,
		[CLK_AP_INTC2_EB]	= &ap_पूर्णांकc2_eb.common.hw,
		[CLK_AP_INTC3_EB]	= &ap_पूर्णांकc3_eb.common.hw,
		[CLK_AP_INTC4_EB]	= &ap_पूर्णांकc4_eb.common.hw,
		[CLK_AP_INTC5_EB]	= &ap_पूर्णांकc5_eb.common.hw,
		[CLK_SCC_EB]		= &scc_eb.common.hw,
		[CLK_DPHY_CFG_EB]	= &dphy_cfg_eb.common.hw,
		[CLK_DPHY_REF_EB]	= &dphy_ref_eb.common.hw,
		[CLK_CPHY_CFG_EB]	= &cphy_cfg_eb.common.hw,
		[CLK_OTG_REF_EB]	= &otg_ref_eb.common.hw,
		[CLK_SERDES_EB]		= &serdes_eb.common.hw,
		[CLK_AON_AP_EMC_EB]	= &aon_ap_emc_eb.common.hw,
	पूर्ण,
	.num	= CLK_AON_APB_GATE_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_aonapb_gate_desc = अणु
	.clk_clks	= sc9863a_aonapb_gate_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_aonapb_gate_clks),
	.hw_clks	= &sc9863a_aonapb_gate_hws,
पूर्ण;

/* mm gate घड़ीs */
अटल SPRD_SC_GATE_CLK_HW(mahb_ckg_eb, "mahb-ckg-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(0), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mdcam_eb, "mdcam-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(1), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(misp_eb, "misp-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(2), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mahbcsi_eb, "mahbcsi-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(3), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mcsi_s_eb, "mcsi-s-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(4), 0, 0);
अटल SPRD_SC_GATE_CLK_HW(mcsi_t_eb, "mcsi-t-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(5), 0, 0);
अटल SPRD_GATE_CLK_HW(dcam_axi_eb, "dcam-axi-eb", &mm_ahb.common.hw, 0x8,
			BIT(0), 0, 0);
अटल SPRD_GATE_CLK_HW(isp_axi_eb, "isp-axi-eb", &mm_ahb.common.hw, 0x8,
			BIT(1), 0, 0);
अटल SPRD_GATE_CLK_HW(mcsi_eb, "mcsi-eb", &mm_ahb.common.hw, 0x8,
			BIT(2), 0, 0);
अटल SPRD_GATE_CLK_HW(mcsi_s_ckg_eb, "mcsi-s-ckg-eb", &mm_ahb.common.hw, 0x8,
			BIT(3), 0, 0);
अटल SPRD_GATE_CLK_HW(mcsi_t_ckg_eb, "mcsi-t-ckg-eb", &mm_ahb.common.hw, 0x8,
			BIT(4), 0, 0);
अटल SPRD_GATE_CLK_HW(sensor0_eb, "sensor0-eb", &mm_ahb.common.hw, 0x8,
			BIT(5), 0, 0);
अटल SPRD_GATE_CLK_HW(sensor1_eb, "sensor1-eb", &mm_ahb.common.hw, 0x8,
			BIT(6), 0, 0);
अटल SPRD_GATE_CLK_HW(sensor2_eb, "sensor2-eb", &mm_ahb.common.hw, 0x8,
			BIT(7), 0, 0);
अटल SPRD_GATE_CLK_HW(mcphy_cfg_eb, "mcphy-cfg-eb", &mm_ahb.common.hw, 0x8,
			BIT(8), 0, 0);

अटल काष्ठा sprd_clk_common *sc9863a_mm_gate_clks[] = अणु
	/* address base is 0x60800000 */
	&mahb_ckg_eb.common,
	&mdcam_eb.common,
	&misp_eb.common,
	&mahbcsi_eb.common,
	&mcsi_s_eb.common,
	&mcsi_t_eb.common,
	&dcam_axi_eb.common,
	&isp_axi_eb.common,
	&mcsi_eb.common,
	&mcsi_s_ckg_eb.common,
	&mcsi_t_ckg_eb.common,
	&sensor0_eb.common,
	&sensor1_eb.common,
	&sensor2_eb.common,
	&mcphy_cfg_eb.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_mm_gate_hws = अणु
	.hws	= अणु
		[CLK_MAHB_CKG_EB]	= &mahb_ckg_eb.common.hw,
		[CLK_MDCAM_EB]		= &mdcam_eb.common.hw,
		[CLK_MISP_EB]		= &misp_eb.common.hw,
		[CLK_MAHBCSI_EB]	= &mahbcsi_eb.common.hw,
		[CLK_MCSI_S_EB]		= &mcsi_s_eb.common.hw,
		[CLK_MCSI_T_EB]		= &mcsi_t_eb.common.hw,
		[CLK_DCAM_AXI_EB]	= &dcam_axi_eb.common.hw,
		[CLK_ISP_AXI_EB]	= &isp_axi_eb.common.hw,
		[CLK_MCSI_EB]		= &mcsi_eb.common.hw,
		[CLK_MCSI_S_CKG_EB]	= &mcsi_s_ckg_eb.common.hw,
		[CLK_MCSI_T_CKG_EB]	= &mcsi_t_ckg_eb.common.hw,
		[CLK_SENSOR0_EB]	= &sensor0_eb.common.hw,
		[CLK_SENSOR1_EB]	= &sensor1_eb.common.hw,
		[CLK_SENSOR2_EB]	= &sensor2_eb.common.hw,
		[CLK_MCPHY_CFG_EB]	= &mcphy_cfg_eb.common.hw,
	पूर्ण,
	.num	= CLK_MM_GATE_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_mm_gate_desc = अणु
	.clk_clks	= sc9863a_mm_gate_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_mm_gate_clks),
	.hw_clks	= &sc9863a_mm_gate_hws,
पूर्ण;

/* camera sensor घड़ीs */
अटल SPRD_GATE_CLK_HW(mipi_csi_clk, "mipi-csi-clk", &mahb_ckg_eb.common.hw,
			0x20, BIT(16), 0, SPRD_GATE_NON_AON);
अटल SPRD_GATE_CLK_HW(mipi_csi_s_clk, "mipi-csi-s-clk", &mahb_ckg_eb.common.hw,
			0x24, BIT(16), 0, SPRD_GATE_NON_AON);
अटल SPRD_GATE_CLK_HW(mipi_csi_m_clk, "mipi-csi-m-clk", &mahb_ckg_eb.common.hw,
			0x28, BIT(16), 0, SPRD_GATE_NON_AON);

अटल काष्ठा sprd_clk_common *sc9863a_mm_clk_clks[] = अणु
	/* address base is 0x60900000 */
	&mipi_csi_clk.common,
	&mipi_csi_s_clk.common,
	&mipi_csi_m_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_mm_clk_hws = अणु
	.hws	= अणु
		[CLK_MIPI_CSI]		= &mipi_csi_clk.common.hw,
		[CLK_MIPI_CSI_S]	= &mipi_csi_s_clk.common.hw,
		[CLK_MIPI_CSI_M]	= &mipi_csi_m_clk.common.hw,
	पूर्ण,
	.num	= CLK_MM_CLK_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_mm_clk_desc = अणु
	.clk_clks	= sc9863a_mm_clk_clks,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_mm_clk_clks),
	.hw_clks	= &sc9863a_mm_clk_hws,
पूर्ण;

अटल SPRD_SC_GATE_CLK_FW_NAME(sim0_eb,	"sim0-eb",	"ext-26m", 0x0,
				0x1000, BIT(0), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(iis0_eb,	"iis0-eb",	"ext-26m", 0x0,
				0x1000, BIT(1), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(iis1_eb,	"iis1-eb",	"ext-26m", 0x0,
				0x1000, BIT(2), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(iis2_eb,	"iis2-eb",	"ext-26m", 0x0,
				0x1000, BIT(3), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(spi0_eb,	"spi0-eb",	"ext-26m", 0x0,
				0x1000, BIT(5), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(spi1_eb,	"spi1-eb",	"ext-26m", 0x0,
				0x1000, BIT(6), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(spi2_eb,	"spi2-eb",	"ext-26m", 0x0,
				0x1000, BIT(7), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c0_eb,	"i2c0-eb",	"ext-26m", 0x0,
				0x1000, BIT(8), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c1_eb,	"i2c1-eb",	"ext-26m", 0x0,
				0x1000, BIT(9), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c2_eb,	"i2c2-eb",	"ext-26m", 0x0,
				0x1000, BIT(10), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c3_eb,	"i2c3-eb",	"ext-26m", 0x0,
				0x1000, BIT(11), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c4_eb,	"i2c4-eb",	"ext-26m", 0x0,
				0x1000, BIT(12), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(uart0_eb,	"uart0-eb",	"ext-26m", 0x0,
				0x1000, BIT(13), 0, 0);
/* uart1_eb is क्रम console, करोn't gate even अगर unused */
अटल SPRD_SC_GATE_CLK_FW_NAME(uart1_eb,	"uart1-eb",	"ext-26m", 0x0,
				0x1000, BIT(14), CLK_IGNORE_UNUSED, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(uart2_eb,	"uart2-eb",	"ext-26m", 0x0,
				0x1000, BIT(15), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(uart3_eb,	"uart3-eb",	"ext-26m", 0x0,
				0x1000, BIT(16), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(uart4_eb,	"uart4-eb",	"ext-26m", 0x0,
				0x1000, BIT(17), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(sim0_32k_eb,	"sim0_32k-eb",	"ext-26m", 0x0,
				0x1000, BIT(18), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(spi3_eb,	"spi3-eb",	"ext-26m", 0x0,
				0x1000, BIT(19), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c5_eb,	"i2c5-eb",	"ext-26m", 0x0,
				0x1000, BIT(20), 0, 0);
अटल SPRD_SC_GATE_CLK_FW_NAME(i2c6_eb,	"i2c6-eb",	"ext-26m", 0x0,
				0x1000, BIT(21), 0, 0);

अटल काष्ठा sprd_clk_common *sc9863a_apapb_gate[] = अणु
	/* address base is 0x71300000 */
	&sim0_eb.common,
	&iis0_eb.common,
	&iis1_eb.common,
	&iis2_eb.common,
	&spi0_eb.common,
	&spi1_eb.common,
	&spi2_eb.common,
	&i2c0_eb.common,
	&i2c1_eb.common,
	&i2c2_eb.common,
	&i2c3_eb.common,
	&i2c4_eb.common,
	&uart0_eb.common,
	&uart1_eb.common,
	&uart2_eb.common,
	&uart3_eb.common,
	&uart4_eb.common,
	&sim0_32k_eb.common,
	&spi3_eb.common,
	&i2c5_eb.common,
	&i2c6_eb.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sc9863a_apapb_gate_hws = अणु
	.hws	= अणु
		[CLK_SIM0_EB]		= &sim0_eb.common.hw,
		[CLK_IIS0_EB]		= &iis0_eb.common.hw,
		[CLK_IIS1_EB]		= &iis1_eb.common.hw,
		[CLK_IIS2_EB]		= &iis2_eb.common.hw,
		[CLK_SPI0_EB]		= &spi0_eb.common.hw,
		[CLK_SPI1_EB]		= &spi1_eb.common.hw,
		[CLK_SPI2_EB]		= &spi2_eb.common.hw,
		[CLK_I2C0_EB]		= &i2c0_eb.common.hw,
		[CLK_I2C1_EB]		= &i2c1_eb.common.hw,
		[CLK_I2C2_EB]		= &i2c2_eb.common.hw,
		[CLK_I2C3_EB]		= &i2c3_eb.common.hw,
		[CLK_I2C4_EB]		= &i2c4_eb.common.hw,
		[CLK_UART0_EB]		= &uart0_eb.common.hw,
		[CLK_UART1_EB]		= &uart1_eb.common.hw,
		[CLK_UART2_EB]		= &uart2_eb.common.hw,
		[CLK_UART3_EB]		= &uart3_eb.common.hw,
		[CLK_UART4_EB]		= &uart4_eb.common.hw,
		[CLK_SIM0_32K_EB]	= &sim0_32k_eb.common.hw,
		[CLK_SPI3_EB]		= &spi3_eb.common.hw,
		[CLK_I2C5_EB]		= &i2c5_eb.common.hw,
		[CLK_I2C6_EB]		= &i2c6_eb.common.hw,
	पूर्ण,
	.num	= CLK_AP_APB_GATE_NUM,
पूर्ण;

अटल स्थिर काष्ठा sprd_clk_desc sc9863a_apapb_gate_desc = अणु
	.clk_clks	= sc9863a_apapb_gate,
	.num_clk_clks	= ARRAY_SIZE(sc9863a_apapb_gate),
	.hw_clks	= &sc9863a_apapb_gate_hws,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sprd_sc9863a_clk_ids[] = अणु
	अणु .compatible = "sprd,sc9863a-ap-clk",	/* 0x21500000 */
	  .data = &sc9863a_ap_clk_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-pmu-gate",	/* 0x402b0000 */
	  .data = &sc9863a_pmu_gate_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-pll",	/* 0x40353000 */
	  .data = &sc9863a_pll_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-mpll",	/* 0x40359000 */
	  .data = &sc9863a_mpll_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-rpll",	/* 0x4035c000 */
	  .data = &sc9863a_rpll_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-dpll",	/* 0x40363000 */
	  .data = &sc9863a_dpll_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-aon-clk",	/* 0x402d0000 */
	  .data = &sc9863a_aon_clk_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-apahb-gate",	/* 0x20e00000 */
	  .data = &sc9863a_apahb_gate_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-aonapb-gate",	/* 0x402e0000 */
	  .data = &sc9863a_aonapb_gate_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-mm-gate",	/* 0x60800000 */
	  .data = &sc9863a_mm_gate_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-mm-clk",	/* 0x60900000 */
	  .data = &sc9863a_mm_clk_desc पूर्ण,
	अणु .compatible = "sprd,sc9863a-apapb-gate",	/* 0x71300000 */
	  .data = &sc9863a_apapb_gate_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_sc9863a_clk_ids);

अटल पूर्णांक sc9863a_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sprd_clk_desc *desc;
	पूर्णांक ret;

	desc = device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -ENODEV;

	ret = sprd_clk_regmap_init(pdev, desc);
	अगर (ret)
		वापस ret;

	वापस sprd_clk_probe(&pdev->dev, desc->hw_clks);
पूर्ण

अटल काष्ठा platक्रमm_driver sc9863a_clk_driver = अणु
	.probe	= sc9863a_clk_probe,
	.driver	= अणु
		.name	= "sc9863a-clk",
		.of_match_table	= sprd_sc9863a_clk_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sc9863a_clk_driver);

MODULE_DESCRIPTION("Spreadtrum SC9863A Clock Driver");
MODULE_LICENSE("GPL v2");
