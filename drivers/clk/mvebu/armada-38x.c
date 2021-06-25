<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada 380/385 SoC घड़ीs
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
 * SAR[14:10] : Ratios between PCLK0, NBCLK, HCLK and DRAM घड़ीs
 *
 * SAR[15]    : TCLK frequency
 *		 0 = 250 MHz
 *		 1 = 200 MHz
 */

#घोषणा SAR_A380_TCLK_FREQ_OPT		  15
#घोषणा SAR_A380_TCLK_FREQ_OPT_MASK	  0x1
#घोषणा SAR_A380_CPU_DDR_L2_FREQ_OPT	  10
#घोषणा SAR_A380_CPU_DDR_L2_FREQ_OPT_MASK 0x1F

अटल स्थिर u32 armada_38x_tclk_frequencies[] __initस्थिर = अणु
	250000000,
	200000000,
पूर्ण;

अटल u32 __init armada_38x_get_tclk_freq(व्योम __iomem *sar)
अणु
	u8 tclk_freq_select;

	tclk_freq_select = ((पढ़ोl(sar) >> SAR_A380_TCLK_FREQ_OPT) &
			    SAR_A380_TCLK_FREQ_OPT_MASK);
	वापस armada_38x_tclk_frequencies[tclk_freq_select];
पूर्ण

अटल स्थिर u32 armada_38x_cpu_frequencies[] __initस्थिर = अणु
	666 * 1000 * 1000,  0, 800 * 1000 * 1000, 0,
	1066 * 1000 * 1000, 0, 1200 * 1000 * 1000, 0,
	1332 * 1000 * 1000, 0, 0, 0,
	1600 * 1000 * 1000, 0, 0, 0,
	1866 * 1000 * 1000, 0, 0, 2000 * 1000 * 1000,
पूर्ण;

अटल u32 __init armada_38x_get_cpu_freq(व्योम __iomem *sar)
अणु
	u8 cpu_freq_select;

	cpu_freq_select = ((पढ़ोl(sar) >> SAR_A380_CPU_DDR_L2_FREQ_OPT) &
			   SAR_A380_CPU_DDR_L2_FREQ_OPT_MASK);
	अगर (cpu_freq_select >= ARRAY_SIZE(armada_38x_cpu_frequencies)) अणु
		pr_err("Selected CPU frequency (%d) unsupported\n",
			cpu_freq_select);
		वापस 0;
	पूर्ण

	वापस armada_38x_cpu_frequencies[cpu_freq_select];
पूर्ण

क्रमागत अणु A380_CPU_TO_DDR, A380_CPU_TO_L2 पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio armada_38x_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = A380_CPU_TO_L2,	 .name = "l2clk" पूर्ण,
	अणु .id = A380_CPU_TO_DDR, .name = "ddrclk" पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक armada_38x_cpu_l2_ratios[32][2] __initस्थिर = अणु
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक armada_38x_cpu_ddr_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु7, 15पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल व्योम __init armada_38x_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = ((पढ़ोl(sar) >> SAR_A380_CPU_DDR_L2_FREQ_OPT) &
		SAR_A380_CPU_DDR_L2_FREQ_OPT_MASK);

	चयन (id) अणु
	हाल A380_CPU_TO_L2:
		*mult = armada_38x_cpu_l2_ratios[opt][0];
		*भाग = armada_38x_cpu_l2_ratios[opt][1];
		अवरोध;
	हाल A380_CPU_TO_DDR:
		*mult = armada_38x_cpu_ddr_ratios[opt][0];
		*भाग = armada_38x_cpu_ddr_ratios[opt][1];
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc armada_38x_coreclks = अणु
	.get_tclk_freq = armada_38x_get_tclk_freq,
	.get_cpu_freq = armada_38x_get_cpu_freq,
	.get_clk_ratio = armada_38x_get_clk_ratio,
	.ratios = armada_38x_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(armada_38x_coreclk_ratios),
पूर्ण;

अटल व्योम __init armada_38x_coreclk_init(काष्ठा device_node *np)
अणु
	mvebu_coreclk_setup(np, &armada_38x_coreclks);
पूर्ण
CLK_OF_DECLARE(armada_38x_core_clk, "marvell,armada-380-core-clock",
	       armada_38x_coreclk_init);

/*
 * Clock Gating Control
 */
अटल स्थिर काष्ठा clk_gating_soc_desc armada_38x_gating_desc[] __initस्थिर = अणु
	अणु "audio", शून्य, 0 पूर्ण,
	अणु "ge2", शून्य, 2 पूर्ण,
	अणु "ge1", शून्य, 3 पूर्ण,
	अणु "ge0", शून्य, 4 पूर्ण,
	अणु "pex1", शून्य, 5 पूर्ण,
	अणु "pex2", शून्य, 6 पूर्ण,
	अणु "pex3", शून्य, 7 पूर्ण,
	अणु "pex0", शून्य, 8 पूर्ण,
	अणु "usb3h0", शून्य, 9 पूर्ण,
	अणु "usb3h1", शून्य, 10 पूर्ण,
	अणु "usb3d", शून्य, 11 पूर्ण,
	अणु "bm", शून्य, 13 पूर्ण,
	अणु "crypto0z", शून्य, 14 पूर्ण,
	अणु "sata0", शून्य, 15 पूर्ण,
	अणु "crypto1z", शून्य, 16 पूर्ण,
	अणु "sdio", शून्य, 17 पूर्ण,
	अणु "usb2", शून्य, 18 पूर्ण,
	अणु "crypto1", शून्य, 21 पूर्ण,
	अणु "xor0", शून्य, 22 पूर्ण,
	अणु "crypto0", शून्य, 23 पूर्ण,
	अणु "tdm", शून्य, 25 पूर्ण,
	अणु "xor1", शून्य, 28 पूर्ण,
	अणु "sata1", शून्य, 30 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init armada_38x_clk_gating_init(काष्ठा device_node *np)
अणु
	mvebu_clk_gating_setup(np, armada_38x_gating_desc);
पूर्ण
CLK_OF_DECLARE(armada_38x_clk_gating, "marvell,armada-380-gating-clock",
	       armada_38x_clk_gating_init);
