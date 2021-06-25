<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a77970 Clock Pulse Generator / Module Standby and Software Reset
 *
 * Copyright (C) 2017-2018 Cogent Embedded Inc.
 *
 * Based on r8a7795-cpg-mssr.c
 *
 * Copyright (C) 2015 Glider bvba
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/soc/renesas/rcar-rst.h>

#समावेश <dt-bindings/घड़ी/r8a77970-cpg-mssr.h>

#समावेश "renesas-cpg-mssr.h"
#समावेश "rcar-gen3-cpg.h"

#घोषणा CPG_SD0CKCR		0x0074

क्रमागत r8a77970_clk_types अणु
	CLK_TYPE_R8A77970_SD0H = CLK_TYPE_GEN3_SOC_BASE,
	CLK_TYPE_R8A77970_SD0,
पूर्ण;

क्रमागत clk_ids अणु
	/* Core Clock Outमाला_दो exported to DT */
	LAST_DT_CORE_CLK = R8A77970_CLK_OSC,

	/* External Input Clocks */
	CLK_EXTAL,
	CLK_EXTALR,

	/* Internal Core Clocks */
	CLK_MAIN,
	CLK_PLL0,
	CLK_PLL1,
	CLK_PLL3,
	CLK_PLL1_DIV2,
	CLK_PLL1_DIV4,

	/* Module Clocks */
	MOD_CLK_BASE
पूर्ण;

अटल spinlock_t cpg_lock;

अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_sd0h_भाग_प्रकारable[] = अणु
	अणु  0,  2 पूर्ण, अणु  1,  3 पूर्ण, अणु  2,  4 पूर्ण, अणु  3,  6 पूर्ण,
	अणु  4,  8 पूर्ण, अणु  5, 12 पूर्ण, अणु  6, 16 पूर्ण, अणु  7, 18 पूर्ण,
	अणु  8, 24 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण, अणु  0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_sd0_भाग_प्रकारable[] = अणु
	अणु  4,  8 पूर्ण, अणु  5, 12 पूर्ण, अणु  6, 16 पूर्ण, अणु  7, 18 पूर्ण,
	अणु  8, 24 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण, अणु 12, 10 पूर्ण,
	अणु  0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cpg_core_clk r8a77970_core_clks[] __initस्थिर = अणु
	/* External Clock Inमाला_दो */
	DEF_INPUT("extal",	CLK_EXTAL),
	DEF_INPUT("extalr",	CLK_EXTALR),

	/* Internal Core Clocks */
	DEF_BASE(".main",	CLK_MAIN, CLK_TYPE_GEN3_MAIN, CLK_EXTAL),
	DEF_BASE(".pll0",	CLK_PLL0, CLK_TYPE_GEN3_PLL0, CLK_MAIN),
	DEF_BASE(".pll1",	CLK_PLL1, CLK_TYPE_GEN3_PLL1, CLK_MAIN),
	DEF_BASE(".pll3",	CLK_PLL3, CLK_TYPE_GEN3_PLL3, CLK_MAIN),

	DEF_FIXED(".pll1_div2",	CLK_PLL1_DIV2,	CLK_PLL1,	2, 1),
	DEF_FIXED(".pll1_div4",	CLK_PLL1_DIV4,	CLK_PLL1_DIV2,	2, 1),

	/* Core Clock Outमाला_दो */
	DEF_FIXED("ztr",	R8A77970_CLK_ZTR,   CLK_PLL1_DIV2,  6, 1),
	DEF_FIXED("ztrd2",	R8A77970_CLK_ZTRD2, CLK_PLL1_DIV2, 12, 1),
	DEF_FIXED("zt",		R8A77970_CLK_ZT,    CLK_PLL1_DIV2,  4, 1),
	DEF_FIXED("zx",		R8A77970_CLK_ZX,    CLK_PLL1_DIV2,  3, 1),
	DEF_FIXED("s1d1",	R8A77970_CLK_S1D1,  CLK_PLL1_DIV2,  4, 1),
	DEF_FIXED("s1d2",	R8A77970_CLK_S1D2,  CLK_PLL1_DIV2,  8, 1),
	DEF_FIXED("s1d4",	R8A77970_CLK_S1D4,  CLK_PLL1_DIV2, 16, 1),
	DEF_FIXED("s2d1",	R8A77970_CLK_S2D1,  CLK_PLL1_DIV2,  6, 1),
	DEF_FIXED("s2d2",	R8A77970_CLK_S2D2,  CLK_PLL1_DIV2, 12, 1),
	DEF_FIXED("s2d4",	R8A77970_CLK_S2D4,  CLK_PLL1_DIV2, 24, 1),

	DEF_BASE("sd0h", R8A77970_CLK_SD0H, CLK_TYPE_R8A77970_SD0H,
		 CLK_PLL1_DIV2),
	DEF_BASE("sd0",	R8A77970_CLK_SD0, CLK_TYPE_R8A77970_SD0, CLK_PLL1_DIV2),

	DEF_FIXED("rpc",	R8A77970_CLK_RPC,   CLK_PLL1_DIV2,  5, 1),
	DEF_FIXED("rpcd2",	R8A77970_CLK_RPCD2, CLK_PLL1_DIV2, 10, 1),

	DEF_FIXED("cl",		R8A77970_CLK_CL,    CLK_PLL1_DIV2, 48, 1),
	DEF_FIXED("cp",		R8A77970_CLK_CP,    CLK_EXTAL,	    2, 1),
	DEF_FIXED("cpex",	R8A77970_CLK_CPEX,  CLK_EXTAL,	    2, 1),

	DEF_DIV6P1("canfd",	R8A77970_CLK_CANFD, CLK_PLL1_DIV4, 0x244),
	DEF_DIV6P1("mso",	R8A77970_CLK_MSO,   CLK_PLL1_DIV4, 0x014),
	DEF_DIV6P1("csi0",	R8A77970_CLK_CSI0,  CLK_PLL1_DIV4, 0x00c),

	DEF_FIXED("osc",	R8A77970_CLK_OSC,   CLK_PLL1_DIV2, 12*1024, 1),
	DEF_FIXED("r",		R8A77970_CLK_R,	    CLK_EXTALR,	   1, 1),
पूर्ण;

अटल स्थिर काष्ठा mssr_mod_clk r8a77970_mod_clks[] __initस्थिर = अणु
	DEF_MOD("tmu4",			 121,	R8A77970_CLK_S2D2),
	DEF_MOD("tmu3",			 122,	R8A77970_CLK_S2D2),
	DEF_MOD("tmu2",			 123,	R8A77970_CLK_S2D2),
	DEF_MOD("tmu1",			 124,	R8A77970_CLK_S2D2),
	DEF_MOD("tmu0",			 125,	R8A77970_CLK_CP),
	DEF_MOD("ivcp1e",		 127,	R8A77970_CLK_S2D1),
	DEF_MOD("scif4",		 203,	R8A77970_CLK_S2D4),
	DEF_MOD("scif3",		 204,	R8A77970_CLK_S2D4),
	DEF_MOD("scif1",		 206,	R8A77970_CLK_S2D4),
	DEF_MOD("scif0",		 207,	R8A77970_CLK_S2D4),
	DEF_MOD("msiof3",		 208,	R8A77970_CLK_MSO),
	DEF_MOD("msiof2",		 209,	R8A77970_CLK_MSO),
	DEF_MOD("msiof1",		 210,	R8A77970_CLK_MSO),
	DEF_MOD("msiof0",		 211,	R8A77970_CLK_MSO),
	DEF_MOD("mfis",			 213,	R8A77970_CLK_S2D2),
	DEF_MOD("sys-dmac2",		 217,	R8A77970_CLK_S2D1),
	DEF_MOD("sys-dmac1",		 218,	R8A77970_CLK_S2D1),
	DEF_MOD("cmt3",			 300,	R8A77970_CLK_R),
	DEF_MOD("cmt2",			 301,	R8A77970_CLK_R),
	DEF_MOD("cmt1",			 302,	R8A77970_CLK_R),
	DEF_MOD("cmt0",			 303,	R8A77970_CLK_R),
	DEF_MOD("tpu0",			 304,	R8A77970_CLK_S2D4),
	DEF_MOD("sd-if",		 314,	R8A77970_CLK_SD0),
	DEF_MOD("rwdt",			 402,	R8A77970_CLK_R),
	DEF_MOD("intc-ex",		 407,	R8A77970_CLK_CP),
	DEF_MOD("intc-ap",		 408,	R8A77970_CLK_S2D1),
	DEF_MOD("hscif3",		 517,	R8A77970_CLK_S2D1),
	DEF_MOD("hscif2",		 518,	R8A77970_CLK_S2D1),
	DEF_MOD("hscif1",		 519,	R8A77970_CLK_S2D1),
	DEF_MOD("hscif0",		 520,	R8A77970_CLK_S2D1),
	DEF_MOD("thermal",		 522,	R8A77970_CLK_CP),
	DEF_MOD("pwm",			 523,	R8A77970_CLK_S2D4),
	DEF_MOD("fcpvd0",		 603,	R8A77970_CLK_S2D1),
	DEF_MOD("vspd0",		 623,	R8A77970_CLK_S2D1),
	DEF_MOD("csi40",		 716,	R8A77970_CLK_CSI0),
	DEF_MOD("du0",			 724,	R8A77970_CLK_S2D1),
	DEF_MOD("lvds",			 727,	R8A77970_CLK_S2D1),
	DEF_MOD("vin3",			 808,	R8A77970_CLK_S2D1),
	DEF_MOD("vin2",			 809,	R8A77970_CLK_S2D1),
	DEF_MOD("vin1",			 810,	R8A77970_CLK_S2D1),
	DEF_MOD("vin0",			 811,	R8A77970_CLK_S2D1),
	DEF_MOD("etheravb",		 812,	R8A77970_CLK_S2D2),
	DEF_MOD("gpio5",		 907,	R8A77970_CLK_CP),
	DEF_MOD("gpio4",		 908,	R8A77970_CLK_CP),
	DEF_MOD("gpio3",		 909,	R8A77970_CLK_CP),
	DEF_MOD("gpio2",		 910,	R8A77970_CLK_CP),
	DEF_MOD("gpio1",		 911,	R8A77970_CLK_CP),
	DEF_MOD("gpio0",		 912,	R8A77970_CLK_CP),
	DEF_MOD("can-fd",		 914,	R8A77970_CLK_S2D2),
	DEF_MOD("rpc-if",		 917,	R8A77970_CLK_RPC),
	DEF_MOD("i2c4",			 927,	R8A77970_CLK_S2D2),
	DEF_MOD("i2c3",			 928,	R8A77970_CLK_S2D2),
	DEF_MOD("i2c2",			 929,	R8A77970_CLK_S2D2),
	DEF_MOD("i2c1",			 930,	R8A77970_CLK_S2D2),
	DEF_MOD("i2c0",			 931,	R8A77970_CLK_S2D2),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक r8a77970_crit_mod_clks[] __initस्थिर = अणु
	MOD_CLK_ID(402),	/* RWDT */
	MOD_CLK_ID(408),	/* INTC-AP (GIC) */
पूर्ण;

/*
 * CPG Clock Data
 */

/*
 *   MD		EXTAL		PLL0	PLL1	PLL3
 * 14 13 19	(MHz)
 *-------------------------------------------------
 * 0  0  0	16.66 x 1	x192	x192	x96
 * 0  0  1	16.66 x 1	x192	x192	x80
 * 0  1  0	20    x 1	x160	x160	x80
 * 0  1  1	20    x 1	x160	x160	x66
 * 1  0  0	27    / 2	x236	x236	x118
 * 1  0  1	27    / 2	x236	x236	x98
 * 1  1  0	33.33 / 2	x192	x192	x96
 * 1  1  1	33.33 / 2	x192	x192	x80
 */
#घोषणा CPG_PLL_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 12) | \
					 (((md) & BIT(13)) >> 12) | \
					 (((md) & BIT(19)) >> 19))

अटल स्थिर काष्ठा rcar_gen3_cpg_pll_config cpg_pll_configs[8] __initस्थिर = अणु
	/* EXTAL भाग	PLL1 mult/भाग	PLL3 mult/भाग */
	अणु 1,		192,	1,	96,	1,	पूर्ण,
	अणु 1,		192,	1,	80,	1,	पूर्ण,
	अणु 1,		160,	1,	80,	1,	पूर्ण,
	अणु 1,		160,	1,	66,	1,	पूर्ण,
	अणु 2,		236,	1,	118,	1,	पूर्ण,
	अणु 2,		236,	1,	98,	1,	पूर्ण,
	अणु 2,		192,	1,	96,	1,	पूर्ण,
	अणु 2,		192,	1,	80,	1,	पूर्ण,
पूर्ण;

अटल पूर्णांक __init r8a77970_cpg_mssr_init(काष्ठा device *dev)
अणु
	स्थिर काष्ठा rcar_gen3_cpg_pll_config *cpg_pll_config;
	u32 cpg_mode;
	पूर्णांक error;

	error = rcar_rst_पढ़ो_mode_pins(&cpg_mode);
	अगर (error)
		वापस error;

	spin_lock_init(&cpg_lock);

	cpg_pll_config = &cpg_pll_configs[CPG_PLL_CONFIG_INDEX(cpg_mode)];

	वापस rcar_gen3_cpg_init(cpg_pll_config, CLK_EXTALR, cpg_mode);
पूर्ण

अटल काष्ठा clk * __init r8a77970_cpg_clk_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा cpg_core_clk *core, स्थिर काष्ठा cpg_mssr_info *info,
	काष्ठा clk **clks, व्योम __iomem *base,
	काष्ठा raw_notअगरier_head *notअगरiers)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
	स्थिर काष्ठा clk *parent;
	अचिन्हित पूर्णांक shअगरt;

	चयन (core->type) अणु
	हाल CLK_TYPE_R8A77970_SD0H:
		table = cpg_sd0h_भाग_प्रकारable;
		shअगरt = 8;
		अवरोध;
	हाल CLK_TYPE_R8A77970_SD0:
		table = cpg_sd0_भाग_प्रकारable;
		shअगरt = 4;
		अवरोध;
	शेष:
		वापस rcar_gen3_cpg_clk_रेजिस्टर(dev, core, info, clks, base,
						  notअगरiers);
	पूर्ण

	parent = clks[core->parent];
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	वापस clk_रेजिस्टर_भागider_table(शून्य, core->name,
					  __clk_get_name(parent), 0,
					  base + CPG_SD0CKCR,
					  shअगरt, 4, 0, table, &cpg_lock);
पूर्ण

स्थिर काष्ठा cpg_mssr_info r8a77970_cpg_mssr_info __initस्थिर = अणु
	/* Core Clocks */
	.core_clks = r8a77970_core_clks,
	.num_core_clks = ARRAY_SIZE(r8a77970_core_clks),
	.last_dt_core_clk = LAST_DT_CORE_CLK,
	.num_total_core_clks = MOD_CLK_BASE,

	/* Module Clocks */
	.mod_clks = r8a77970_mod_clks,
	.num_mod_clks = ARRAY_SIZE(r8a77970_mod_clks),
	.num_hw_mod_clks = 12 * 32,

	/* Critical Module Clocks */
	.crit_mod_clks = r8a77970_crit_mod_clks,
	.num_crit_mod_clks = ARRAY_SIZE(r8a77970_crit_mod_clks),

	/* Callbacks */
	.init = r8a77970_cpg_mssr_init,
	.cpg_clk_रेजिस्टर = r8a77970_cpg_clk_रेजिस्टर,
पूर्ण;
