<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada 39x SoC घड़ीs
 *
 * Copyright (C) 2015 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Andrew Lunn <andrew@lunn.ch>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश "common.h"

/*
 * SARL[14:10] : Ratios between CPU, NBCLK, HCLK and DCLK.
 *
 * SARL[15]    : TCLK frequency
 *		 0 = 250 MHz
 *		 1 = 200 MHz
 *
 * SARH[0]     : Reference घड़ी frequency
 *               0 = 25 Mhz
 *               1 = 40 Mhz
 */

#घोषणा SARL 					0
#घोषणा  SARL_A390_TCLK_FREQ_OPT		15
#घोषणा  SARL_A390_TCLK_FREQ_OPT_MASK		0x1
#घोषणा  SARL_A390_CPU_DDR_L2_FREQ_OPT		10
#घोषणा  SARL_A390_CPU_DDR_L2_FREQ_OPT_MASK	0x1F
#घोषणा SARH					4
#घोषणा  SARH_A390_REFCLK_FREQ			BIT(0)

अटल स्थिर u32 armada_39x_tclk_frequencies[] __initस्थिर = अणु
	250000000,
	200000000,
पूर्ण;

अटल u32 __init armada_39x_get_tclk_freq(व्योम __iomem *sar)
अणु
	u8 tclk_freq_select;

	tclk_freq_select = ((पढ़ोl(sar + SARL) >> SARL_A390_TCLK_FREQ_OPT) &
			    SARL_A390_TCLK_FREQ_OPT_MASK);
	वापस armada_39x_tclk_frequencies[tclk_freq_select];
पूर्ण

अटल स्थिर u32 armada_39x_cpu_frequencies[] __initस्थिर = अणु
	[0x0] = 666 * 1000 * 1000,
	[0x2] = 800 * 1000 * 1000,
	[0x3] = 800 * 1000 * 1000,
	[0x4] = 1066 * 1000 * 1000,
	[0x5] = 1066 * 1000 * 1000,
	[0x6] = 1200 * 1000 * 1000,
	[0x8] = 1332 * 1000 * 1000,
	[0xB] = 1600 * 1000 * 1000,
	[0xC] = 1600 * 1000 * 1000,
	[0x12] = 1800 * 1000 * 1000,
	[0x1E] = 1800 * 1000 * 1000,
पूर्ण;

अटल u32 __init armada_39x_get_cpu_freq(व्योम __iomem *sar)
अणु
	u8 cpu_freq_select;

	cpu_freq_select = ((पढ़ोl(sar + SARL) >> SARL_A390_CPU_DDR_L2_FREQ_OPT) &
			   SARL_A390_CPU_DDR_L2_FREQ_OPT_MASK);
	अगर (cpu_freq_select >= ARRAY_SIZE(armada_39x_cpu_frequencies)) अणु
		pr_err("Selected CPU frequency (%d) unsupported\n",
			cpu_freq_select);
		वापस 0;
	पूर्ण

	वापस armada_39x_cpu_frequencies[cpu_freq_select];
पूर्ण

क्रमागत अणु A390_CPU_TO_NBCLK, A390_CPU_TO_HCLK, A390_CPU_TO_DCLK पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio armada_39x_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = A390_CPU_TO_NBCLK, .name = "nbclk" पूर्ण,
	अणु .id = A390_CPU_TO_HCLK, .name = "hclk" पूर्ण,
	अणु .id = A390_CPU_TO_DCLK, .name = "dclk" पूर्ण,
पूर्ण;

अटल व्योम __init armada_39x_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	चयन (id) अणु
	हाल A390_CPU_TO_NBCLK:
		*mult = 1;
		*भाग = 2;
		अवरोध;
	हाल A390_CPU_TO_HCLK:
		*mult = 1;
		*भाग = 4;
		अवरोध;
	हाल A390_CPU_TO_DCLK:
		*mult = 1;
		*भाग = 2;
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 __init armada_39x_refclk_ratio(व्योम __iomem *sar)
अणु
	अगर (पढ़ोl(sar + SARH) & SARH_A390_REFCLK_FREQ)
		वापस 40 * 1000 * 1000;
	अन्यथा
		वापस 25 * 1000 * 1000;
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc armada_39x_coreclks = अणु
	.get_tclk_freq = armada_39x_get_tclk_freq,
	.get_cpu_freq = armada_39x_get_cpu_freq,
	.get_clk_ratio = armada_39x_get_clk_ratio,
	.get_refclk_freq = armada_39x_refclk_ratio,
	.ratios = armada_39x_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(armada_39x_coreclk_ratios),
पूर्ण;

अटल व्योम __init armada_39x_coreclk_init(काष्ठा device_node *np)
अणु
	mvebu_coreclk_setup(np, &armada_39x_coreclks);
पूर्ण
CLK_OF_DECLARE(armada_39x_core_clk, "marvell,armada-390-core-clock",
	       armada_39x_coreclk_init);

/*
 * Clock Gating Control
 */
अटल स्थिर काष्ठा clk_gating_soc_desc armada_39x_gating_desc[] __initस्थिर = अणु
	अणु "pex1", शून्य, 5 पूर्ण,
	अणु "pex2", शून्य, 6 पूर्ण,
	अणु "pex3", शून्य, 7 पूर्ण,
	अणु "pex0", शून्य, 8 पूर्ण,
	अणु "usb3h0", शून्य, 9 पूर्ण,
	अणु "usb3h1", शून्य, 10 पूर्ण,
	अणु "sata0", शून्य, 15 पूर्ण,
	अणु "sdio", शून्य, 17 पूर्ण,
	अणु "xor0", शून्य, 22 पूर्ण,
	अणु "xor1", शून्य, 28 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init armada_39x_clk_gating_init(काष्ठा device_node *np)
अणु
	mvebu_clk_gating_setup(np, armada_39x_gating_desc);
पूर्ण
CLK_OF_DECLARE(armada_39x_clk_gating, "marvell,armada-390-gating-clock",
	       armada_39x_clk_gating_init);
