<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R7S9210 Clock Pulse Generator / Module Standby
 *
 * Based on r8a7795-cpg-mssr.c
 *
 * Copyright (C) 2018 Chris Bअक्रमt
 * Copyright (C) 2018 Renesas Electronics Corp.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <dt-bindings/घड़ी/r7s9210-cpg-mssr.h>
#समावेश "renesas-cpg-mssr.h"

#घोषणा CPG_FRQCR	0x00

अटल u8 cpg_mode;

/* Internal Clock ratio table */
अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक g;
	अचिन्हित पूर्णांक b;
	अचिन्हित पूर्णांक p1;
	/* p0 is always 32 */;
पूर्ण ratio_tab[5] = अणु	/* I,  G,  B, P1 */
			अणु  2,  4,  8, 16पूर्ण,	/* FRQCR = 0x012 */
			अणु  4,  4,  8, 16पूर्ण,	/* FRQCR = 0x112 */
			अणु  8,  4,  8, 16पूर्ण,	/* FRQCR = 0x212 */
			अणु 16,  8, 16, 16पूर्ण,	/* FRQCR = 0x322 */
			अणु 16, 16, 32, 32पूर्ण,	/* FRQCR = 0x333 */
			पूर्ण;

क्रमागत rz_clk_types अणु
	CLK_TYPE_RZA_MAIN = CLK_TYPE_CUSTOM,
	CLK_TYPE_RZA_PLL,
पूर्ण;

क्रमागत clk_ids अणु
	/* Core Clock Outमाला_दो exported to DT */
	LAST_DT_CORE_CLK = R7S9210_CLK_P0,

	/* External Input Clocks */
	CLK_EXTAL,

	/* Internal Core Clocks */
	CLK_MAIN,
	CLK_PLL,

	/* Module Clocks */
	MOD_CLK_BASE
पूर्ण;

अटल काष्ठा cpg_core_clk r7s9210_early_core_clks[] = अणु
	/* External Clock Inमाला_दो */
	DEF_INPUT("extal",     CLK_EXTAL),

	/* Internal Core Clocks */
	DEF_BASE(".main",       CLK_MAIN, CLK_TYPE_RZA_MAIN, CLK_EXTAL),
	DEF_BASE(".pll",       CLK_PLL, CLK_TYPE_RZA_PLL, CLK_MAIN),

	/* Core Clock Outमाला_दो */
	DEF_FIXED("p1c",    R7S9210_CLK_P1C,   CLK_PLL,         16, 1),
पूर्ण;

अटल स्थिर काष्ठा mssr_mod_clk r7s9210_early_mod_clks[] __initस्थिर = अणु
	DEF_MOD_STB("ostm2",	 34,	R7S9210_CLK_P1C),
	DEF_MOD_STB("ostm1",	 35,	R7S9210_CLK_P1C),
	DEF_MOD_STB("ostm0",	 36,	R7S9210_CLK_P1C),
पूर्ण;

अटल काष्ठा cpg_core_clk r7s9210_core_clks[] = अणु
	/* Core Clock Outमाला_दो */
	DEF_FIXED("i",      R7S9210_CLK_I,     CLK_PLL,          2, 1),
	DEF_FIXED("g",      R7S9210_CLK_G,     CLK_PLL,          4, 1),
	DEF_FIXED("b",      R7S9210_CLK_B,     CLK_PLL,          8, 1),
	DEF_FIXED("p1",     R7S9210_CLK_P1,    CLK_PLL,         16, 1),
	DEF_FIXED("p0",     R7S9210_CLK_P0,    CLK_PLL,         32, 1),
पूर्ण;

अटल स्थिर काष्ठा mssr_mod_clk r7s9210_mod_clks[] __initस्थिर = अणु
	DEF_MOD_STB("scif4",	 43,	R7S9210_CLK_P1C),
	DEF_MOD_STB("scif3",	 44,	R7S9210_CLK_P1C),
	DEF_MOD_STB("scif2",	 45,	R7S9210_CLK_P1C),
	DEF_MOD_STB("scif1",	 46,	R7S9210_CLK_P1C),
	DEF_MOD_STB("scif0",	 47,	R7S9210_CLK_P1C),

	DEF_MOD_STB("usb1",	 60,	R7S9210_CLK_B),
	DEF_MOD_STB("usb0",	 61,	R7S9210_CLK_B),
	DEF_MOD_STB("ether1",	 64,	R7S9210_CLK_B),
	DEF_MOD_STB("ether0",	 65,	R7S9210_CLK_B),

	DEF_MOD_STB("spibsc",	 83,	R7S9210_CLK_P1),
	DEF_MOD_STB("i2c3",	 84,	R7S9210_CLK_P1),
	DEF_MOD_STB("i2c2",	 85,	R7S9210_CLK_P1),
	DEF_MOD_STB("i2c1",	 86,	R7S9210_CLK_P1),
	DEF_MOD_STB("i2c0",	 87,	R7S9210_CLK_P1),

	DEF_MOD_STB("spi2",	 95,	R7S9210_CLK_P1),
	DEF_MOD_STB("spi1",	 96,	R7S9210_CLK_P1),
	DEF_MOD_STB("spi0",	 97,	R7S9210_CLK_P1),

	DEF_MOD_STB("sdhi11",	100,	R7S9210_CLK_B),
	DEF_MOD_STB("sdhi10",	101,	R7S9210_CLK_B),
	DEF_MOD_STB("sdhi01",	102,	R7S9210_CLK_B),
	DEF_MOD_STB("sdhi00",	103,	R7S9210_CLK_B),
पूर्ण;

/* The घड़ी भागiders in the table vary based on DT and रेजिस्टर settings */
अटल व्योम __init r7s9210_update_clk_table(काष्ठा clk *extal_clk,
					    व्योम __iomem *base)
अणु
	पूर्णांक i;
	u16 frqcr;
	u8 index;

	/* If EXTAL is above 12MHz, then we know it is Mode 1 */
	अगर (clk_get_rate(extal_clk) > 12000000)
		cpg_mode = 1;

	frqcr = पढ़ोl(base + CPG_FRQCR) & 0xFFF;
	अगर (frqcr == 0x012)
		index = 0;
	अन्यथा अगर (frqcr == 0x112)
		index = 1;
	अन्यथा अगर (frqcr == 0x212)
		index = 2;
	अन्यथा अगर (frqcr == 0x322)
		index = 3;
	अन्यथा अगर (frqcr == 0x333)
		index = 4;
	अन्यथा
		BUG_ON(1);	/* Illegal FRQCR value */

	क्रम (i = 0; i < ARRAY_SIZE(r7s9210_core_clks); i++) अणु
		चयन (r7s9210_core_clks[i].id) अणु
		हाल R7S9210_CLK_I:
			r7s9210_core_clks[i].भाग = ratio_tab[index].i;
			अवरोध;
		हाल R7S9210_CLK_G:
			r7s9210_core_clks[i].भाग = ratio_tab[index].g;
			अवरोध;
		हाल R7S9210_CLK_B:
			r7s9210_core_clks[i].भाग = ratio_tab[index].b;
			अवरोध;
		हाल R7S9210_CLK_P1:
		हाल R7S9210_CLK_P1C:
			r7s9210_core_clks[i].भाग = ratio_tab[index].p1;
			अवरोध;
		हाल R7S9210_CLK_P0:
			r7s9210_core_clks[i].भाग = 32;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा clk * __init rza2_cpg_clk_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा cpg_core_clk *core, स्थिर काष्ठा cpg_mssr_info *info,
	काष्ठा clk **clks, व्योम __iomem *base,
	काष्ठा raw_notअगरier_head *notअगरiers)
अणु
	काष्ठा clk *parent;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;

	parent = clks[core->parent];
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	चयन (core->id) अणु
	हाल CLK_MAIN:
		अवरोध;

	हाल CLK_PLL:
		अगर (cpg_mode)
			mult = 44;	/* Divider 1 is 1/2 */
		अन्यथा
			mult = 88;	/* Divider 1 is 1 */
		अवरोध;

	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (core->id == CLK_MAIN)
		r7s9210_update_clk_table(parent, base);

	वापस clk_रेजिस्टर_fixed_factor(शून्य, core->name,
					 __clk_get_name(parent), 0, mult, भाग);
पूर्ण

स्थिर काष्ठा cpg_mssr_info r7s9210_cpg_mssr_info __initस्थिर = अणु
	/* Early Clocks */
	.early_core_clks = r7s9210_early_core_clks,
	.num_early_core_clks = ARRAY_SIZE(r7s9210_early_core_clks),
	.early_mod_clks = r7s9210_early_mod_clks,
	.num_early_mod_clks = ARRAY_SIZE(r7s9210_early_mod_clks),

	/* Core Clocks */
	.core_clks = r7s9210_core_clks,
	.num_core_clks = ARRAY_SIZE(r7s9210_core_clks),
	.last_dt_core_clk = LAST_DT_CORE_CLK,
	.num_total_core_clks = MOD_CLK_BASE,

	/* Module Clocks */
	.mod_clks = r7s9210_mod_clks,
	.num_mod_clks = ARRAY_SIZE(r7s9210_mod_clks),
	.num_hw_mod_clks = 11 * 32, /* includes STBCR0 which करोesn't exist */

	/* Callbacks */
	.cpg_clk_रेजिस्टर = rza2_cpg_clk_रेजिस्टर,

	/* RZ/A2 has Standby Control Registers */
	.reg_layout = CLK_REG_LAYOUT_RZ_A,
पूर्ण;

अटल व्योम __init r7s9210_cpg_mssr_early_init(काष्ठा device_node *np)
अणु
	cpg_mssr_early_init(np, &r7s9210_cpg_mssr_info);
पूर्ण

CLK_OF_DECLARE_DRIVER(cpg_mstp_clks, "renesas,r7s9210-cpg-mssr",
		      r7s9210_cpg_mssr_early_init);
