<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 * Copyright 2021 NXP
 *
 * घड़ी driver क्रम Freescale QorIQ SoCs.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <dt-bindings/घड़ी/fsl,qoriq-घड़ीgen.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/fsl/guts.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#घोषणा PLL_DIV1	0
#घोषणा PLL_DIV2	1
#घोषणा PLL_DIV3	2
#घोषणा PLL_DIV4	3

#घोषणा PLATFORM_PLL	0
#घोषणा CGA_PLL1	1
#घोषणा CGA_PLL2	2
#घोषणा CGA_PLL3	3
#घोषणा CGA_PLL4	4	/* only on घड़ीgen-1.0, which lacks CGB */
#घोषणा CGB_PLL1	4
#घोषणा CGB_PLL2	5
#घोषणा MAX_PLL_DIV	32

काष्ठा घड़ीgen_pll_भाग अणु
	काष्ठा clk *clk;
	अक्षर name[32];
पूर्ण;

काष्ठा घड़ीgen_pll अणु
	काष्ठा घड़ीgen_pll_भाग भाग[MAX_PLL_DIV];
पूर्ण;

#घोषणा CLKSEL_VALID	1
#घोषणा CLKSEL_80PCT	2	/* Only allowed अगर PLL <= 80% of max cpu freq */

काष्ठा घड़ीgen_sourceinfo अणु
	u32 flags;	/* CLKSEL_xxx */
	पूर्णांक pll;	/* CGx_PLLn */
	पूर्णांक भाग;	/* PLL_DIVn */
पूर्ण;

#घोषणा NUM_MUX_PARENTS	16

काष्ठा घड़ीgen_muxinfo अणु
	काष्ठा घड़ीgen_sourceinfo clksel[NUM_MUX_PARENTS];
पूर्ण;

#घोषणा NUM_HWACCEL	5
#घोषणा NUM_CMUX	8

काष्ठा घड़ीgen;

/*
 * cmux freq must be >= platक्रमm pll.
 * If not set, cmux freq must be >= platक्रमm pll/2
 */
#घोषणा CG_CMUX_GE_PLAT		1

#घोषणा CG_PLL_8BIT		2	/* PLLCnGSR[CFG] is 8 bits, not 6 */
#घोषणा CG_VER3			4	/* version 3 cg: reg layout dअगरferent */
#घोषणा CG_LITTLE_ENDIAN	8

काष्ठा घड़ीgen_chipinfo अणु
	स्थिर अक्षर *compat, *guts_compat;
	स्थिर काष्ठा घड़ीgen_muxinfo *cmux_groups[2];
	स्थिर काष्ठा घड़ीgen_muxinfo *hwaccel[NUM_HWACCEL];
	व्योम (*init_periph)(काष्ठा घड़ीgen *cg);
	पूर्णांक cmux_to_group[NUM_CMUX + 1]; /* array should be -1 terminated */
	u32 pll_mask;	/* 1 << n bit set अगर PLL n is valid */
	u32 flags;	/* CG_xxx */
पूर्ण;

काष्ठा घड़ीgen अणु
	काष्ठा device_node *node;
	व्योम __iomem *regs;
	काष्ठा घड़ीgen_chipinfo info; /* mutable copy */
	काष्ठा clk *sysclk, *coreclk;
	काष्ठा घड़ीgen_pll pll[6];
	काष्ठा clk *cmux[NUM_CMUX];
	काष्ठा clk *hwaccel[NUM_HWACCEL];
	काष्ठा clk *fman[2];
	काष्ठा ccsr_guts __iomem *guts;
पूर्ण;

अटल काष्ठा घड़ीgen घड़ीgen;
अटल bool add_cpufreq_dev __initdata;

अटल व्योम cg_out(काष्ठा घड़ीgen *cg, u32 val, u32 __iomem *reg)
अणु
	अगर (cg->info.flags & CG_LITTLE_ENDIAN)
		ioग_लिखो32(val, reg);
	अन्यथा
		ioग_लिखो32be(val, reg);
पूर्ण

अटल u32 cg_in(काष्ठा घड़ीgen *cg, u32 __iomem *reg)
अणु
	u32 val;

	अगर (cg->info.flags & CG_LITTLE_ENDIAN)
		val = ioपढ़ो32(reg);
	अन्यथा
		val = ioपढ़ो32be(reg);

	वापस val;
पूर्ण

अटल स्थिर काष्ठा घड़ीgen_muxinfo p2041_cmux_grp1 = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p2041_cmux_grp2 = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		[5] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p5020_cmux_grp1 = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		[4] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL2, PLL_DIV1 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p5020_cmux_grp2 = अणु
	अणु
		[0] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL1, PLL_DIV1 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		[5] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p5040_cmux_grp1 = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		[4] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL2, PLL_DIV1 पूर्ण,
		[5] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL2, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p5040_cmux_grp2 = अणु
	अणु
		[0] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL1, PLL_DIV2 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		[5] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p4080_cmux_grp1 = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		[5] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		[8] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL3, PLL_DIV1 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo p4080_cmux_grp2 = अणु
	अणु
		[0] = अणु CLKSEL_VALID | CLKSEL_80PCT, CGA_PLL1, PLL_DIV1 पूर्ण,
		[8] = अणु CLKSEL_VALID, CGA_PLL3, PLL_DIV1 पूर्ण,
		[9] = अणु CLKSEL_VALID, CGA_PLL3, PLL_DIV2 पूर्ण,
		[12] = अणु CLKSEL_VALID, CGA_PLL4, PLL_DIV1 पूर्ण,
		[13] = अणु CLKSEL_VALID, CGA_PLL4, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t1023_cmux = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t1040_cmux = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		[1] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		[5] = अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;


अटल स्थिर काष्ठा घड़ीgen_muxinfo घड़ीgen2_cmux_cga = अणु
	अणु
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL3, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL3, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL3, PLL_DIV4 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo घड़ीgen2_cmux_cga12 = अणु
	अणु
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV4 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo घड़ीgen2_cmux_cgb = अणु
	अणु
		अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV4 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1021a_cmux = अणु
	अणु
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1028a_hwa1 = अणु
	अणु
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1028a_hwa2 = अणु
	अणु
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1028a_hwa3 = अणु
	अणु
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1028a_hwa4 = अणु
	अणु
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1043a_hwa1 = अणु
	अणु
		अणुपूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणुपूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1043a_hwa2 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1046a_hwa1 = अणु
	अणु
		अणुपूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1046a_hwa2 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
		अणुपूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1088a_hwa1 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1088a_hwa2 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo ls1012a_cmux = अणु
	अणु
		[0] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणुपूर्ण,
		[2] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t1023_hwa1 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t1023_hwa2 = अणु
	अणु
		[6] = अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t2080_hwa1 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t2080_hwa2 = अणु
	अणु
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV4 पूर्ण,
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t4240_hwa1 = अणु
	अणु
		अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV1 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV3 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL1, PLL_DIV4 पूर्ण,
		अणुपूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV2 पूर्ण,
		अणु CLKSEL_VALID, CGA_PLL2, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t4240_hwa4 = अणु
	अणु
		[2] = अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV2 पूर्ण,
		[3] = अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV3 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV4 पूर्ण,
		[5] = अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		[6] = अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV2 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_muxinfo t4240_hwa5 = अणु
	अणु
		[2] = अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV2 पूर्ण,
		[3] = अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV3 पूर्ण,
		[4] = अणु CLKSEL_VALID, CGB_PLL2, PLL_DIV4 पूर्ण,
		[5] = अणु CLKSEL_VALID, PLATFORM_PLL, PLL_DIV1 पूर्ण,
		[6] = अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV2 पूर्ण,
		[7] = अणु CLKSEL_VALID, CGB_PLL1, PLL_DIV3 पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा RCWSR7_FM1_CLK_SEL	0x40000000
#घोषणा RCWSR7_FM2_CLK_SEL	0x20000000
#घोषणा RCWSR7_HWA_ASYNC_DIV	0x04000000

अटल व्योम __init p2041_init_periph(काष्ठा घड़ीgen *cg)
अणु
	u32 reg;

	reg = ioपढ़ो32be(&cg->guts->rcwsr[7]);

	अगर (reg & RCWSR7_FM1_CLK_SEL)
		cg->fman[0] = cg->pll[CGA_PLL2].भाग[PLL_DIV2].clk;
	अन्यथा
		cg->fman[0] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV2].clk;
पूर्ण

अटल व्योम __init p4080_init_periph(काष्ठा घड़ीgen *cg)
अणु
	u32 reg;

	reg = ioपढ़ो32be(&cg->guts->rcwsr[7]);

	अगर (reg & RCWSR7_FM1_CLK_SEL)
		cg->fman[0] = cg->pll[CGA_PLL3].भाग[PLL_DIV2].clk;
	अन्यथा
		cg->fman[0] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV2].clk;

	अगर (reg & RCWSR7_FM2_CLK_SEL)
		cg->fman[1] = cg->pll[CGA_PLL3].भाग[PLL_DIV2].clk;
	अन्यथा
		cg->fman[1] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV2].clk;
पूर्ण

अटल व्योम __init p5020_init_periph(काष्ठा घड़ीgen *cg)
अणु
	u32 reg;
	पूर्णांक भाग = PLL_DIV2;

	reg = ioपढ़ो32be(&cg->guts->rcwsr[7]);
	अगर (reg & RCWSR7_HWA_ASYNC_DIV)
		भाग = PLL_DIV4;

	अगर (reg & RCWSR7_FM1_CLK_SEL)
		cg->fman[0] = cg->pll[CGA_PLL2].भाग[भाग].clk;
	अन्यथा
		cg->fman[0] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV2].clk;
पूर्ण

अटल व्योम __init p5040_init_periph(काष्ठा घड़ीgen *cg)
अणु
	u32 reg;
	पूर्णांक भाग = PLL_DIV2;

	reg = ioपढ़ो32be(&cg->guts->rcwsr[7]);
	अगर (reg & RCWSR7_HWA_ASYNC_DIV)
		भाग = PLL_DIV4;

	अगर (reg & RCWSR7_FM1_CLK_SEL)
		cg->fman[0] = cg->pll[CGA_PLL3].भाग[भाग].clk;
	अन्यथा
		cg->fman[0] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV2].clk;

	अगर (reg & RCWSR7_FM2_CLK_SEL)
		cg->fman[1] = cg->pll[CGA_PLL3].भाग[भाग].clk;
	अन्यथा
		cg->fman[1] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV2].clk;
पूर्ण

अटल व्योम __init t1023_init_periph(काष्ठा घड़ीgen *cg)
अणु
	cg->fman[0] = cg->hwaccel[1];
पूर्ण

अटल व्योम __init t1040_init_periph(काष्ठा घड़ीgen *cg)
अणु
	cg->fman[0] = cg->pll[PLATFORM_PLL].भाग[PLL_DIV1].clk;
पूर्ण

अटल व्योम __init t2080_init_periph(काष्ठा घड़ीgen *cg)
अणु
	cg->fman[0] = cg->hwaccel[0];
पूर्ण

अटल व्योम __init t4240_init_periph(काष्ठा घड़ीgen *cg)
अणु
	cg->fman[0] = cg->hwaccel[3];
	cg->fman[1] = cg->hwaccel[4];
पूर्ण

अटल स्थिर काष्ठा घड़ीgen_chipinfo chipinfo[] = अणु
	अणु
		.compat = "fsl,b4420-clockgen",
		.guts_compat = "fsl,b4860-device-config",
		.init_periph = t2080_init_periph,
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12, &घड़ीgen2_cmux_cgb
		पूर्ण,
		.hwaccel = अणु
			&t2080_hwa1
		पूर्ण,
		.cmux_to_group = अणु
			0, 1, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) | BIT(CGA_PLL3) |
			    BIT(CGB_PLL1) | BIT(CGB_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,b4860-clockgen",
		.guts_compat = "fsl,b4860-device-config",
		.init_periph = t2080_init_periph,
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12, &घड़ीgen2_cmux_cgb
		पूर्ण,
		.hwaccel = अणु
			&t2080_hwa1
		पूर्ण,
		.cmux_to_group = अणु
			0, 1, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) | BIT(CGA_PLL3) |
			    BIT(CGB_PLL1) | BIT(CGB_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,ls1021a-clockgen",
		.cmux_groups = अणु
			&ls1021a_cmux
		पूर्ण,
		.cmux_to_group = अणु
			0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
	पूर्ण,
	अणु
		.compat = "fsl,ls1028a-clockgen",
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12
		पूर्ण,
		.hwaccel = अणु
			&ls1028a_hwa1, &ls1028a_hwa2,
			&ls1028a_hwa3, &ls1028a_hwa4
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 0, 0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
		.flags = CG_VER3 | CG_LITTLE_ENDIAN,
	पूर्ण,
	अणु
		.compat = "fsl,ls1043a-clockgen",
		.init_periph = t2080_init_periph,
		.cmux_groups = अणु
			&t1040_cmux
		पूर्ण,
		.hwaccel = अणु
			&ls1043a_hwa1, &ls1043a_hwa2
		पूर्ण,
		.cmux_to_group = अणु
			0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,ls1046a-clockgen",
		.init_periph = t2080_init_periph,
		.cmux_groups = अणु
			&t1040_cmux
		पूर्ण,
		.hwaccel = अणु
			&ls1046a_hwa1, &ls1046a_hwa2
		पूर्ण,
		.cmux_to_group = अणु
			0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,ls1088a-clockgen",
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12
		पूर्ण,
		.hwaccel = अणु
			&ls1088a_hwa1, &ls1088a_hwa2
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
		.flags = CG_VER3 | CG_LITTLE_ENDIAN,
	पूर्ण,
	अणु
		.compat = "fsl,ls1012a-clockgen",
		.cmux_groups = अणु
			&ls1012a_cmux
		पूर्ण,
		.cmux_to_group = अणु
			0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) | BIT(CGA_PLL1),
	पूर्ण,
	अणु
		.compat = "fsl,ls2080a-clockgen",
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12, &घड़ीgen2_cmux_cgb
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) |
			    BIT(CGB_PLL1) | BIT(CGB_PLL2),
		.flags = CG_VER3 | CG_LITTLE_ENDIAN,
	पूर्ण,
	अणु
		.compat = "fsl,lx2160a-clockgen",
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12, &घड़ीgen2_cmux_cgb
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 0, 0, 1, 1, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) |
			    BIT(CGB_PLL1) | BIT(CGB_PLL2),
		.flags = CG_VER3 | CG_LITTLE_ENDIAN,
	पूर्ण,
	अणु
		.compat = "fsl,p2041-clockgen",
		.guts_compat = "fsl,qoriq-device-config-1.0",
		.init_periph = p2041_init_periph,
		.cmux_groups = अणु
			&p2041_cmux_grp1, &p2041_cmux_grp2
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
	पूर्ण,
	अणु
		.compat = "fsl,p3041-clockgen",
		.guts_compat = "fsl,qoriq-device-config-1.0",
		.init_periph = p2041_init_periph,
		.cmux_groups = अणु
			&p2041_cmux_grp1, &p2041_cmux_grp2
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
	पूर्ण,
	अणु
		.compat = "fsl,p4080-clockgen",
		.guts_compat = "fsl,qoriq-device-config-1.0",
		.init_periph = p4080_init_periph,
		.cmux_groups = अणु
			&p4080_cmux_grp1, &p4080_cmux_grp2
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 0, 0, 1, 1, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) |
			    BIT(CGA_PLL3) | BIT(CGA_PLL4),
	पूर्ण,
	अणु
		.compat = "fsl,p5020-clockgen",
		.guts_compat = "fsl,qoriq-device-config-1.0",
		.init_periph = p5020_init_periph,
		.cmux_groups = अणु
			&p5020_cmux_grp1, &p5020_cmux_grp2
		पूर्ण,
		.cmux_to_group = अणु
			0, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
	पूर्ण,
	अणु
		.compat = "fsl,p5040-clockgen",
		.guts_compat = "fsl,p5040-device-config",
		.init_periph = p5040_init_periph,
		.cmux_groups = अणु
			&p5040_cmux_grp1, &p5040_cmux_grp2
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 1, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) | BIT(CGA_PLL3),
	पूर्ण,
	अणु
		.compat = "fsl,t1023-clockgen",
		.guts_compat = "fsl,t1023-device-config",
		.init_periph = t1023_init_periph,
		.cmux_groups = अणु
			&t1023_cmux
		पूर्ण,
		.hwaccel = अणु
			&t1023_hwa1, &t1023_hwa2
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) | BIT(CGA_PLL1),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,t1040-clockgen",
		.guts_compat = "fsl,t1040-device-config",
		.init_periph = t1040_init_periph,
		.cmux_groups = अणु
			&t1040_cmux
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 0, 0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,t2080-clockgen",
		.guts_compat = "fsl,t2080-device-config",
		.init_periph = t2080_init_periph,
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga12
		पूर्ण,
		.hwaccel = अणु
			&t2080_hwa1, &t2080_hwa2
		पूर्ण,
		.cmux_to_group = अणु
			0, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणु
		.compat = "fsl,t4240-clockgen",
		.guts_compat = "fsl,t4240-device-config",
		.init_periph = t4240_init_periph,
		.cmux_groups = अणु
			&घड़ीgen2_cmux_cga, &घड़ीgen2_cmux_cgb
		पूर्ण,
		.hwaccel = अणु
			&t4240_hwa1, शून्य, शून्य, &t4240_hwa4, &t4240_hwa5
		पूर्ण,
		.cmux_to_group = अणु
			0, 0, 1, -1
		पूर्ण,
		.pll_mask = BIT(PLATFORM_PLL) |
			    BIT(CGA_PLL1) | BIT(CGA_PLL2) | BIT(CGA_PLL3) |
			    BIT(CGB_PLL1) | BIT(CGB_PLL2),
		.flags = CG_PLL_8BIT,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

काष्ठा mux_hwघड़ी अणु
	काष्ठा clk_hw hw;
	काष्ठा घड़ीgen *cg;
	स्थिर काष्ठा घड़ीgen_muxinfo *info;
	u32 __iomem *reg;
	u8 parent_to_clksel[NUM_MUX_PARENTS];
	s8 clksel_to_parent[NUM_MUX_PARENTS];
	पूर्णांक num_parents;
पूर्ण;

#घोषणा to_mux_hwघड़ी(p)	container_of(p, काष्ठा mux_hwघड़ी, hw)
#घोषणा CLKSEL_MASK		0x78000000
#घोषणा	CLKSEL_SHIFT		27

अटल पूर्णांक mux_set_parent(काष्ठा clk_hw *hw, u8 idx)
अणु
	काष्ठा mux_hwघड़ी *hwc = to_mux_hwघड़ी(hw);
	u32 clksel;

	अगर (idx >= hwc->num_parents)
		वापस -EINVAL;

	clksel = hwc->parent_to_clksel[idx];
	cg_out(hwc->cg, (clksel << CLKSEL_SHIFT) & CLKSEL_MASK, hwc->reg);

	वापस 0;
पूर्ण

अटल u8 mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा mux_hwघड़ी *hwc = to_mux_hwघड़ी(hw);
	u32 clksel;
	s8 ret;

	clksel = (cg_in(hwc->cg, hwc->reg) & CLKSEL_MASK) >> CLKSEL_SHIFT;

	ret = hwc->clksel_to_parent[clksel];
	अगर (ret < 0) अणु
		pr_err("%s: mux at %p has bad clksel\n", __func__, hwc->reg);
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops cmux_ops = अणु
	.get_parent = mux_get_parent,
	.set_parent = mux_set_parent,
पूर्ण;

/*
 * Don't allow setting for now, as the clock options haven't been
 * sanitized क्रम additional restrictions.
 */
अटल स्थिर काष्ठा clk_ops hwaccel_ops = अणु
	.get_parent = mux_get_parent,
पूर्ण;

अटल स्थिर काष्ठा घड़ीgen_pll_भाग *get_pll_भाग(काष्ठा घड़ीgen *cg,
						  काष्ठा mux_hwघड़ी *hwc,
						  पूर्णांक idx)
अणु
	पूर्णांक pll, भाग;

	अगर (!(hwc->info->clksel[idx].flags & CLKSEL_VALID))
		वापस शून्य;

	pll = hwc->info->clksel[idx].pll;
	भाग = hwc->info->clksel[idx].भाग;

	वापस &cg->pll[pll].भाग[भाग];
पूर्ण

अटल काष्ठा clk * __init create_mux_common(काष्ठा घड़ीgen *cg,
					     काष्ठा mux_hwघड़ी *hwc,
					     स्थिर काष्ठा clk_ops *ops,
					     अचिन्हित दीर्घ min_rate,
					     अचिन्हित दीर्घ max_rate,
					     अचिन्हित दीर्घ pct80_rate,
					     स्थिर अक्षर *fmt, पूर्णांक idx)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk *clk;
	स्थिर काष्ठा घड़ीgen_pll_भाग *भाग;
	स्थिर अक्षर *parent_names[NUM_MUX_PARENTS];
	अक्षर name[32];
	पूर्णांक i, j;

	snम_लिखो(name, माप(name), fmt, idx);

	क्रम (i = 0, j = 0; i < NUM_MUX_PARENTS; i++) अणु
		अचिन्हित दीर्घ rate;

		hwc->clksel_to_parent[i] = -1;

		भाग = get_pll_भाग(cg, hwc, i);
		अगर (!भाग)
			जारी;

		rate = clk_get_rate(भाग->clk);

		अगर (hwc->info->clksel[i].flags & CLKSEL_80PCT &&
		    rate > pct80_rate)
			जारी;
		अगर (rate < min_rate)
			जारी;
		अगर (rate > max_rate)
			जारी;

		parent_names[j] = भाग->name;
		hwc->parent_to_clksel[j] = i;
		hwc->clksel_to_parent[i] = j;
		j++;
	पूर्ण

	init.name = name;
	init.ops = ops;
	init.parent_names = parent_names;
	init.num_parents = hwc->num_parents = j;
	init.flags = 0;
	hwc->hw.init = &init;
	hwc->cg = cg;

	clk = clk_रेजिस्टर(शून्य, &hwc->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: Couldn't register %s: %ld\n", __func__, name,
		       PTR_ERR(clk));
		kमुक्त(hwc);
		वापस शून्य;
	पूर्ण

	वापस clk;
पूर्ण

अटल काष्ठा clk * __init create_one_cmux(काष्ठा घड़ीgen *cg, पूर्णांक idx)
अणु
	काष्ठा mux_hwघड़ी *hwc;
	स्थिर काष्ठा घड़ीgen_pll_भाग *भाग;
	अचिन्हित दीर्घ plat_rate, min_rate;
	u64 max_rate, pct80_rate;
	u32 clksel;

	hwc = kzalloc(माप(*hwc), GFP_KERNEL);
	अगर (!hwc)
		वापस शून्य;

	अगर (cg->info.flags & CG_VER3)
		hwc->reg = cg->regs + 0x70000 + 0x20 * idx;
	अन्यथा
		hwc->reg = cg->regs + 0x20 * idx;

	hwc->info = cg->info.cmux_groups[cg->info.cmux_to_group[idx]];

	/*
	 * Find the rate क्रम the शेष clksel, and treat it as the
	 * maximum rated core frequency.  If this is an incorrect
	 * assumption, certain घड़ी options (possibly including the
	 * शेष clksel) may be inappropriately excluded on certain
	 * chips.
	 */
	clksel = (cg_in(cg, hwc->reg) & CLKSEL_MASK) >> CLKSEL_SHIFT;
	भाग = get_pll_भाग(cg, hwc, clksel);
	अगर (!भाग) अणु
		kमुक्त(hwc);
		वापस शून्य;
	पूर्ण

	max_rate = clk_get_rate(भाग->clk);
	pct80_rate = max_rate * 8;
	करो_भाग(pct80_rate, 10);

	plat_rate = clk_get_rate(cg->pll[PLATFORM_PLL].भाग[PLL_DIV1].clk);

	अगर (cg->info.flags & CG_CMUX_GE_PLAT)
		min_rate = plat_rate;
	अन्यथा
		min_rate = plat_rate / 2;

	वापस create_mux_common(cg, hwc, &cmux_ops, min_rate, max_rate,
				 pct80_rate, "cg-cmux%d", idx);
पूर्ण

अटल काष्ठा clk * __init create_one_hwaccel(काष्ठा घड़ीgen *cg, पूर्णांक idx)
अणु
	काष्ठा mux_hwघड़ी *hwc;

	hwc = kzalloc(माप(*hwc), GFP_KERNEL);
	अगर (!hwc)
		वापस शून्य;

	hwc->reg = cg->regs + 0x20 * idx + 0x10;
	hwc->info = cg->info.hwaccel[idx];

	वापस create_mux_common(cg, hwc, &hwaccel_ops, 0, अच_दीर्घ_उच्च, 0,
				 "cg-hwaccel%d", idx);
पूर्ण

अटल व्योम __init create_muxes(काष्ठा घड़ीgen *cg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cg->cmux); i++) अणु
		अगर (cg->info.cmux_to_group[i] < 0)
			अवरोध;
		अगर (cg->info.cmux_to_group[i] >=
		    ARRAY_SIZE(cg->info.cmux_groups)) अणु
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण

		cg->cmux[i] = create_one_cmux(cg, i);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cg->hwaccel); i++) अणु
		अगर (!cg->info.hwaccel[i])
			जारी;

		cg->hwaccel[i] = create_one_hwaccel(cg, i);
	पूर्ण
पूर्ण

अटल व्योम __init _घड़ीgen_init(काष्ठा device_node *np, bool legacy);

/*
 * Legacy nodes may get probed beक्रमe the parent घड़ीgen node.
 * It is assumed that device trees with legacy nodes will not
 * contain a "clocks" property -- otherwise the input घड़ीs may
 * not be initialized at this poपूर्णांक.
 */
अटल व्योम __init legacy_init_घड़ीgen(काष्ठा device_node *np)
अणु
	अगर (!घड़ीgen.node)
		_घड़ीgen_init(of_get_parent(np), true);
पूर्ण

/* Legacy node */
अटल व्योम __init core_mux_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	काष्ठा resource res;
	पूर्णांक idx, rc;

	legacy_init_घड़ीgen(np);

	अगर (of_address_to_resource(np, 0, &res))
		वापस;

	idx = (res.start & 0xf0) >> 5;
	clk = घड़ीgen.cmux[idx];

	rc = of_clk_add_provider(np, of_clk_src_simple_get, clk);
	अगर (rc) अणु
		pr_err("%s: Couldn't register clk provider for node %pOFn: %d\n",
		       __func__, np, rc);
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा clk __init
*sysclk_from_fixed(काष्ठा device_node *node, स्थिर अक्षर *name)
अणु
	u32 rate;

	अगर (of_property_पढ़ो_u32(node, "clock-frequency", &rate))
		वापस ERR_PTR(-ENODEV);

	वापस clk_रेजिस्टर_fixed_rate(शून्य, name, शून्य, 0, rate);
पूर्ण

अटल काष्ठा clk __init *input_घड़ी(स्थिर अक्षर *name, काष्ठा clk *clk)
अणु
	स्थिर अक्षर *input_name;

	/* Register the input घड़ी under the desired name. */
	input_name = __clk_get_name(clk);
	clk = clk_रेजिस्टर_fixed_factor(शून्य, name, input_name,
					0, 1, 1);
	अगर (IS_ERR(clk))
		pr_err("%s: Couldn't register %s: %ld\n", __func__, name,
		       PTR_ERR(clk));

	वापस clk;
पूर्ण

अटल काष्ठा clk __init *input_घड़ी_by_name(स्थिर अक्षर *name,
					      स्थिर अक्षर *dtname)
अणु
	काष्ठा clk *clk;

	clk = of_clk_get_by_name(घड़ीgen.node, dtname);
	अगर (IS_ERR(clk))
		वापस clk;

	वापस input_घड़ी(name, clk);
पूर्ण

अटल काष्ठा clk __init *input_घड़ी_by_index(स्थिर अक्षर *name, पूर्णांक idx)
अणु
	काष्ठा clk *clk;

	clk = of_clk_get(घड़ीgen.node, 0);
	अगर (IS_ERR(clk))
		वापस clk;

	वापस input_घड़ी(name, clk);
पूर्ण

अटल काष्ठा clk * __init create_sysclk(स्थिर अक्षर *name)
अणु
	काष्ठा device_node *sysclk;
	काष्ठा clk *clk;

	clk = sysclk_from_fixed(घड़ीgen.node, name);
	अगर (!IS_ERR(clk))
		वापस clk;

	clk = input_घड़ी_by_name(name, "sysclk");
	अगर (!IS_ERR(clk))
		वापस clk;

	clk = input_घड़ी_by_index(name, 0);
	अगर (!IS_ERR(clk))
		वापस clk;

	sysclk = of_get_child_by_name(घड़ीgen.node, "sysclk");
	अगर (sysclk) अणु
		clk = sysclk_from_fixed(sysclk, name);
		अगर (!IS_ERR(clk))
			वापस clk;
	पूर्ण

	pr_err("%s: No input sysclk\n", __func__);
	वापस शून्य;
पूर्ण

अटल काष्ठा clk * __init create_coreclk(स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk;

	clk = input_घड़ी_by_name(name, "coreclk");
	अगर (!IS_ERR(clk))
		वापस clk;

	/*
	 * This indicates a mix of legacy nodes with the new coreclk
	 * mechanism, which should never happen.  If this error occurs,
	 * करोn't use the wrong input clock just because coreclk isn't
	 * पढ़ोy yet.
	 */
	अगर (WARN_ON(PTR_ERR(clk) == -EPROBE_DEFER))
		वापस clk;

	वापस शून्य;
पूर्ण

/* Legacy node */
अटल व्योम __init sysclk_init(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;

	legacy_init_घड़ीgen(node);

	clk = घड़ीgen.sysclk;
	अगर (clk)
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
पूर्ण

#घोषणा PLL_KILL BIT(31)

अटल व्योम __init create_one_pll(काष्ठा घड़ीgen *cg, पूर्णांक idx)
अणु
	u32 __iomem *reg;
	u32 mult;
	काष्ठा घड़ीgen_pll *pll = &cg->pll[idx];
	स्थिर अक्षर *input = "cg-sysclk";
	पूर्णांक i;

	अगर (!(cg->info.pll_mask & (1 << idx)))
		वापस;

	अगर (cg->coreclk && idx != PLATFORM_PLL) अणु
		अगर (IS_ERR(cg->coreclk))
			वापस;

		input = "cg-coreclk";
	पूर्ण

	अगर (cg->info.flags & CG_VER3) अणु
		चयन (idx) अणु
		हाल PLATFORM_PLL:
			reg = cg->regs + 0x60080;
			अवरोध;
		हाल CGA_PLL1:
			reg = cg->regs + 0x80;
			अवरोध;
		हाल CGA_PLL2:
			reg = cg->regs + 0xa0;
			अवरोध;
		हाल CGB_PLL1:
			reg = cg->regs + 0x10080;
			अवरोध;
		हाल CGB_PLL2:
			reg = cg->regs + 0x100a0;
			अवरोध;
		शेष:
			WARN_ONCE(1, "index %d\n", idx);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (idx == PLATFORM_PLL)
			reg = cg->regs + 0xc00;
		अन्यथा
			reg = cg->regs + 0x800 + 0x20 * (idx - 1);
	पूर्ण

	/* Get the multiple of PLL */
	mult = cg_in(cg, reg);

	/* Check अगर this PLL is disabled */
	अगर (mult & PLL_KILL) अणु
		pr_debug("%s(): pll %p disabled\n", __func__, reg);
		वापस;
	पूर्ण

	अगर ((cg->info.flags & CG_VER3) ||
	    ((cg->info.flags & CG_PLL_8BIT) && idx != PLATFORM_PLL))
		mult = (mult & GENMASK(8, 1)) >> 1;
	अन्यथा
		mult = (mult & GENMASK(6, 1)) >> 1;

	क्रम (i = 0; i < ARRAY_SIZE(pll->भाग); i++) अणु
		काष्ठा clk *clk;
		पूर्णांक ret;

		/*
		 * For platक्रमm PLL, there are MAX_PLL_DIV भागider घड़ीs.
		 * For core PLL, there are 4 भागider घड़ीs at most.
		 */
		अगर (idx != PLATFORM_PLL && i >= 4)
			अवरोध;

		snम_लिखो(pll->भाग[i].name, माप(pll->भाग[i].name),
			 "cg-pll%d-div%d", idx, i + 1);

		clk = clk_रेजिस्टर_fixed_factor(शून्य,
				pll->भाग[i].name, input, 0, mult, i + 1);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: %s: register failed %ld\n",
			       __func__, pll->भाग[i].name, PTR_ERR(clk));
			जारी;
		पूर्ण

		pll->भाग[i].clk = clk;
		ret = clk_रेजिस्टर_clkdev(clk, pll->भाग[i].name, शून्य);
		अगर (ret != 0)
			pr_err("%s: %s: register to lookup table failed %d\n",
			       __func__, pll->भाग[i].name, ret);

	पूर्ण
पूर्ण

अटल व्योम __init create_plls(काष्ठा घड़ीgen *cg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cg->pll); i++)
		create_one_pll(cg, i);
पूर्ण

अटल व्योम __init legacy_pll_init(काष्ठा device_node *np, पूर्णांक idx)
अणु
	काष्ठा घड़ीgen_pll *pll;
	काष्ठा clk_onecell_data *onecell_data;
	काष्ठा clk **subclks;
	पूर्णांक count, rc;

	legacy_init_घड़ीgen(np);

	pll = &घड़ीgen.pll[idx];
	count = of_property_count_strings(np, "clock-output-names");

	BUILD_BUG_ON(ARRAY_SIZE(pll->भाग) < 4);
	subclks = kसुस्मृति(4, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!subclks)
		वापस;

	onecell_data = kदो_स्मृति(माप(*onecell_data), GFP_KERNEL);
	अगर (!onecell_data)
		जाओ err_clks;

	अगर (count <= 3) अणु
		subclks[0] = pll->भाग[0].clk;
		subclks[1] = pll->भाग[1].clk;
		subclks[2] = pll->भाग[3].clk;
	पूर्ण अन्यथा अणु
		subclks[0] = pll->भाग[0].clk;
		subclks[1] = pll->भाग[1].clk;
		subclks[2] = pll->भाग[2].clk;
		subclks[3] = pll->भाग[3].clk;
	पूर्ण

	onecell_data->clks = subclks;
	onecell_data->clk_num = count;

	rc = of_clk_add_provider(np, of_clk_src_onecell_get, onecell_data);
	अगर (rc) अणु
		pr_err("%s: Couldn't register clk provider for node %pOFn: %d\n",
		       __func__, np, rc);
		जाओ err_cell;
	पूर्ण

	वापस;
err_cell:
	kमुक्त(onecell_data);
err_clks:
	kमुक्त(subclks);
पूर्ण

/* Legacy node */
अटल व्योम __init pltfrm_pll_init(काष्ठा device_node *np)
अणु
	legacy_pll_init(np, PLATFORM_PLL);
पूर्ण

/* Legacy node */
अटल व्योम __init core_pll_init(काष्ठा device_node *np)
अणु
	काष्ठा resource res;
	पूर्णांक idx;

	अगर (of_address_to_resource(np, 0, &res))
		वापस;

	अगर ((res.start & 0xfff) == 0xc00) अणु
		/*
		 * ls1021a devtree labels the platक्रमm PLL
		 * with the core PLL compatible
		 */
		pltfrm_pll_init(np);
	पूर्ण अन्यथा अणु
		idx = (res.start & 0xf0) >> 5;
		legacy_pll_init(np, CGA_PLL1 + idx);
	पूर्ण
पूर्ण

अटल काष्ठा clk *घड़ीgen_clk_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा घड़ीgen *cg = data;
	काष्ठा clk *clk;
	काष्ठा घड़ीgen_pll *pll;
	u32 type, idx;

	अगर (clkspec->args_count < 2) अणु
		pr_err("%s: insufficient phandle args\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	type = clkspec->args[0];
	idx = clkspec->args[1];

	चयन (type) अणु
	हाल QORIQ_CLK_SYSCLK:
		अगर (idx != 0)
			जाओ bad_args;
		clk = cg->sysclk;
		अवरोध;
	हाल QORIQ_CLK_CMUX:
		अगर (idx >= ARRAY_SIZE(cg->cmux))
			जाओ bad_args;
		clk = cg->cmux[idx];
		अवरोध;
	हाल QORIQ_CLK_HWACCEL:
		अगर (idx >= ARRAY_SIZE(cg->hwaccel))
			जाओ bad_args;
		clk = cg->hwaccel[idx];
		अवरोध;
	हाल QORIQ_CLK_FMAN:
		अगर (idx >= ARRAY_SIZE(cg->fman))
			जाओ bad_args;
		clk = cg->fman[idx];
		अवरोध;
	हाल QORIQ_CLK_PLATFORM_PLL:
		pll = &cg->pll[PLATFORM_PLL];
		अगर (idx >= ARRAY_SIZE(pll->भाग))
			जाओ bad_args;
		clk = pll->भाग[idx].clk;
		अवरोध;
	हाल QORIQ_CLK_CORECLK:
		अगर (idx != 0)
			जाओ bad_args;
		clk = cg->coreclk;
		अगर (IS_ERR(clk))
			clk = शून्य;
		अवरोध;
	शेष:
		जाओ bad_args;
	पूर्ण

	अगर (!clk)
		वापस ERR_PTR(-ENOENT);
	वापस clk;

bad_args:
	pr_err("%s: Bad phandle args %u %u\n", __func__, type, idx);
	वापस ERR_PTR(-EINVAL);
पूर्ण

#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/mpc85xx.h>

अटल स्थिर u32 a4510_svrs[] __initस्थिर = अणु
	(SVR_P2040 << 8) | 0x10,	/* P2040 1.0 */
	(SVR_P2040 << 8) | 0x11,	/* P2040 1.1 */
	(SVR_P2041 << 8) | 0x10,	/* P2041 1.0 */
	(SVR_P2041 << 8) | 0x11,	/* P2041 1.1 */
	(SVR_P3041 << 8) | 0x10,	/* P3041 1.0 */
	(SVR_P3041 << 8) | 0x11,	/* P3041 1.1 */
	(SVR_P4040 << 8) | 0x20,	/* P4040 2.0 */
	(SVR_P4080 << 8) | 0x20,	/* P4080 2.0 */
	(SVR_P5010 << 8) | 0x10,	/* P5010 1.0 */
	(SVR_P5010 << 8) | 0x20,	/* P5010 2.0 */
	(SVR_P5020 << 8) | 0x10,	/* P5020 1.0 */
	(SVR_P5021 << 8) | 0x10,	/* P5021 1.0 */
	(SVR_P5040 << 8) | 0x10,	/* P5040 1.0 */
पूर्ण;

#घोषणा SVR_SECURITY	0x80000	/* The Security (E) bit */

अटल bool __init has_erratum_a4510(व्योम)
अणु
	u32 svr = mfspr(SPRN_SVR);
	पूर्णांक i;

	svr &= ~SVR_SECURITY;

	क्रम (i = 0; i < ARRAY_SIZE(a4510_svrs); i++) अणु
		अगर (svr == a4510_svrs[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा
अटल bool __init has_erratum_a4510(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init _घड़ीgen_init(काष्ठा device_node *np, bool legacy)
अणु
	पूर्णांक i, ret;
	bool is_old_ls1021a = false;

	/* May have alपढ़ोy been called by a legacy probe */
	अगर (घड़ीgen.node)
		वापस;

	घड़ीgen.node = np;
	घड़ीgen.regs = of_iomap(np, 0);
	अगर (!घड़ीgen.regs &&
	    of_device_is_compatible(of_root, "fsl,ls1021a")) अणु
		/* Compatibility hack क्रम old, broken device trees */
		घड़ीgen.regs = ioremap(0x1ee1000, 0x1000);
		is_old_ls1021a = true;
	पूर्ण
	अगर (!घड़ीgen.regs) अणु
		pr_err("%s(): %pOFn: of_iomap() failed\n", __func__, np);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(chipinfo); i++) अणु
		अगर (of_device_is_compatible(np, chipinfo[i].compat))
			अवरोध;
		अगर (is_old_ls1021a &&
		    !म_भेद(chipinfo[i].compat, "fsl,ls1021a-clockgen"))
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(chipinfo)) अणु
		pr_err("%s: unknown clockgen node %pOF\n", __func__, np);
		जाओ err;
	पूर्ण
	घड़ीgen.info = chipinfo[i];

	अगर (घड़ीgen.info.guts_compat) अणु
		काष्ठा device_node *guts;

		guts = of_find_compatible_node(शून्य, शून्य,
					       घड़ीgen.info.guts_compat);
		अगर (guts) अणु
			घड़ीgen.guts = of_iomap(guts, 0);
			अगर (!घड़ीgen.guts) अणु
				pr_err("%s: Couldn't map %pOF regs\n", __func__,
				       guts);
			पूर्ण
			of_node_put(guts);
		पूर्ण

	पूर्ण

	अगर (has_erratum_a4510())
		घड़ीgen.info.flags |= CG_CMUX_GE_PLAT;

	घड़ीgen.sysclk = create_sysclk("cg-sysclk");
	घड़ीgen.coreclk = create_coreclk("cg-coreclk");
	create_plls(&घड़ीgen);
	create_muxes(&घड़ीgen);

	अगर (घड़ीgen.info.init_periph)
		घड़ीgen.info.init_periph(&घड़ीgen);

	ret = of_clk_add_provider(np, घड़ीgen_clk_get, &घड़ीgen);
	अगर (ret) अणु
		pr_err("%s: Couldn't register clk provider for node %pOFn: %d\n",
		       __func__, np, ret);
	पूर्ण

	/* Don't create cpufreq device क्रम legacy घड़ीgen blocks */
	add_cpufreq_dev = !legacy;

	वापस;
err:
	iounmap(घड़ीgen.regs);
	घड़ीgen.regs = शून्य;
पूर्ण

अटल व्योम __init घड़ीgen_init(काष्ठा device_node *np)
अणु
	_घड़ीgen_init(np, false);
पूर्ण

अटल पूर्णांक __init घड़ीgen_cpufreq_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (add_cpufreq_dev) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("qoriq-cpufreq", -1,
				शून्य, 0);
		अगर (IS_ERR(pdev))
			pr_err("Couldn't register qoriq-cpufreq err=%ld\n",
				PTR_ERR(pdev));
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(घड़ीgen_cpufreq_init);

CLK_OF_DECLARE(qoriq_घड़ीgen_1, "fsl,qoriq-clockgen-1.0", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_2, "fsl,qoriq-clockgen-2.0", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_b4420, "fsl,b4420-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_b4860, "fsl,b4860-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls1012a, "fsl,ls1012a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls1021a, "fsl,ls1021a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls1028a, "fsl,ls1028a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls1043a, "fsl,ls1043a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls1046a, "fsl,ls1046a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls1088a, "fsl,ls1088a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_ls2080a, "fsl,ls2080a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_lx2160a, "fsl,lx2160a-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_p2041, "fsl,p2041-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_p3041, "fsl,p3041-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_p4080, "fsl,p4080-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_p5020, "fsl,p5020-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_p5040, "fsl,p5040-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_t1023, "fsl,t1023-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_t1040, "fsl,t1040-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_t2080, "fsl,t2080-clockgen", घड़ीgen_init);
CLK_OF_DECLARE(qoriq_घड़ीgen_t4240, "fsl,t4240-clockgen", घड़ीgen_init);

/* Legacy nodes */
CLK_OF_DECLARE(qoriq_sysclk_1, "fsl,qoriq-sysclk-1.0", sysclk_init);
CLK_OF_DECLARE(qoriq_sysclk_2, "fsl,qoriq-sysclk-2.0", sysclk_init);
CLK_OF_DECLARE(qoriq_core_pll_1, "fsl,qoriq-core-pll-1.0", core_pll_init);
CLK_OF_DECLARE(qoriq_core_pll_2, "fsl,qoriq-core-pll-2.0", core_pll_init);
CLK_OF_DECLARE(qoriq_core_mux_1, "fsl,qoriq-core-mux-1.0", core_mux_init);
CLK_OF_DECLARE(qoriq_core_mux_2, "fsl,qoriq-core-mux-2.0", core_mux_init);
CLK_OF_DECLARE(qoriq_pltfrm_pll_1, "fsl,qoriq-platform-pll-1.0", pltfrm_pll_init);
CLK_OF_DECLARE(qoriq_pltfrm_pll_2, "fsl,qoriq-platform-pll-2.0", pltfrm_pll_init);
