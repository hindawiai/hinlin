<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada 375 SoC घड़ीs
 *
 * Copyright (C) 2014 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Andrew Lunn <andrew@lunn.ch>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश "common.h"

/*
 * Core Clocks
 */

/*
 * For the Armada 375 SoCs, the CPU, DDR and L2 घड़ीs frequencies are
 * all modअगरied at the same समय, and not separately as क्रम the Armada
 * 370 or the Armada XP SoCs.
 *
 * SAR1[21:17]   : CPU frequency    DDR frequency   L2 frequency
 *		 6   =  400 MHz	    400 MHz	    200 MHz
 *		 15  =  600 MHz	    600 MHz	    300 MHz
 *		 21  =  800 MHz	    534 MHz	    400 MHz
 *		 25  = 1000 MHz	    500 MHz	    500 MHz
 *		 others reserved.
 *
 * SAR1[22]   : TCLK frequency
 *		 0 = 166 MHz
 *		 1 = 200 MHz
 */

#घोषणा SAR1_A375_TCLK_FREQ_OPT		   22
#घोषणा SAR1_A375_TCLK_FREQ_OPT_MASK	   0x1
#घोषणा SAR1_A375_CPU_DDR_L2_FREQ_OPT	   17
#घोषणा SAR1_A375_CPU_DDR_L2_FREQ_OPT_MASK 0x1F

अटल स्थिर u32 armada_375_tclk_frequencies[] __initस्थिर = अणु
	166000000,
	200000000,
पूर्ण;

अटल u32 __init armada_375_get_tclk_freq(व्योम __iomem *sar)
अणु
	u8 tclk_freq_select;

	tclk_freq_select = ((पढ़ोl(sar) >> SAR1_A375_TCLK_FREQ_OPT) &
			    SAR1_A375_TCLK_FREQ_OPT_MASK);
	वापस armada_375_tclk_frequencies[tclk_freq_select];
पूर्ण


अटल स्थिर u32 armada_375_cpu_frequencies[] __initस्थिर = अणु
	0, 0, 0, 0, 0, 0,
	400000000,
	0, 0, 0, 0, 0, 0, 0, 0,
	600000000,
	0, 0, 0, 0, 0,
	800000000,
	0, 0, 0,
	1000000000,
पूर्ण;

अटल u32 __init armada_375_get_cpu_freq(व्योम __iomem *sar)
अणु
	u8 cpu_freq_select;

	cpu_freq_select = ((पढ़ोl(sar) >> SAR1_A375_CPU_DDR_L2_FREQ_OPT) &
			   SAR1_A375_CPU_DDR_L2_FREQ_OPT_MASK);
	अगर (cpu_freq_select >= ARRAY_SIZE(armada_375_cpu_frequencies)) अणु
		pr_err("Selected CPU frequency (%d) unsupported\n",
			cpu_freq_select);
		वापस 0;
	पूर्ण अन्यथा
		वापस armada_375_cpu_frequencies[cpu_freq_select];
पूर्ण

क्रमागत अणु A375_CPU_TO_DDR, A375_CPU_TO_L2 पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio armada_375_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = A375_CPU_TO_L2,	 .name = "l2clk" पूर्ण,
	अणु .id = A375_CPU_TO_DDR, .name = "ddrclk" पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक armada_375_cpu_l2_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक armada_375_cpu_ddr_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 3पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु2, 3पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल व्योम __init armada_375_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = ((पढ़ोl(sar) >> SAR1_A375_CPU_DDR_L2_FREQ_OPT) &
		SAR1_A375_CPU_DDR_L2_FREQ_OPT_MASK);

	चयन (id) अणु
	हाल A375_CPU_TO_L2:
		*mult = armada_375_cpu_l2_ratios[opt][0];
		*भाग = armada_375_cpu_l2_ratios[opt][1];
		अवरोध;
	हाल A375_CPU_TO_DDR:
		*mult = armada_375_cpu_ddr_ratios[opt][0];
		*भाग = armada_375_cpu_ddr_ratios[opt][1];
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc armada_375_coreclks = अणु
	.get_tclk_freq = armada_375_get_tclk_freq,
	.get_cpu_freq = armada_375_get_cpu_freq,
	.get_clk_ratio = armada_375_get_clk_ratio,
	.ratios = armada_375_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(armada_375_coreclk_ratios),
पूर्ण;

अटल व्योम __init armada_375_coreclk_init(काष्ठा device_node *np)
अणु
	mvebu_coreclk_setup(np, &armada_375_coreclks);
पूर्ण
CLK_OF_DECLARE(armada_375_core_clk, "marvell,armada-375-core-clock",
	       armada_375_coreclk_init);

/*
 * Clock Gating Control
 */
अटल स्थिर काष्ठा clk_gating_soc_desc armada_375_gating_desc[] __initस्थिर = अणु
	अणु "mu", शून्य, 2 पूर्ण,
	अणु "pp", शून्य, 3 पूर्ण,
	अणु "ptp", शून्य, 4 पूर्ण,
	अणु "pex0", शून्य, 5 पूर्ण,
	अणु "pex1", शून्य, 6 पूर्ण,
	अणु "audio", शून्य, 8 पूर्ण,
	अणु "nd_clk", "nand", 11 पूर्ण,
	अणु "sata0_link", "sata0_core", 14 पूर्ण,
	अणु "sata0_core", शून्य, 15 पूर्ण,
	अणु "usb3", शून्य, 16 पूर्ण,
	अणु "sdio", शून्य, 17 पूर्ण,
	अणु "usb", शून्य, 18 पूर्ण,
	अणु "gop", शून्य, 19 पूर्ण,
	अणु "sata1_link", "sata1_core", 20 पूर्ण,
	अणु "sata1_core", शून्य, 21 पूर्ण,
	अणु "xor0", शून्य, 22 पूर्ण,
	अणु "xor1", शून्य, 23 पूर्ण,
	अणु "copro", शून्य, 24 पूर्ण,
	अणु "tdm", शून्य, 25 पूर्ण,
	अणु "crypto0_enc", शून्य, 28 पूर्ण,
	अणु "crypto0_core", शून्य, 29 पूर्ण,
	अणु "crypto1_enc", शून्य, 30 पूर्ण,
	अणु "crypto1_core", शून्य, 31 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init armada_375_clk_gating_init(काष्ठा device_node *np)
अणु
	mvebu_clk_gating_setup(np, armada_375_gating_desc);
पूर्ण
CLK_OF_DECLARE(armada_375_clk_gating, "marvell,armada-375-gating-clock",
	       armada_375_clk_gating_init);
