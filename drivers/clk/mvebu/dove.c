<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Dove SoC घड़ीs
 *
 * Copyright (C) 2012 Marvell
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
#समावेश "dove-divider.h"

/*
 * Core Clocks
 *
 * Dove PLL sample-at-reset configuration
 *
 * SAR0[8:5]   : CPU frequency
 *		 5  = 1000 MHz
 *		 6  =  933 MHz
 *		 7  =  933 MHz
 *		 8  =  800 MHz
 *		 9  =  800 MHz
 *		 10 =  800 MHz
 *		 11 = 1067 MHz
 *		 12 =  667 MHz
 *		 13 =  533 MHz
 *		 14 =  400 MHz
 *		 15 =  333 MHz
 *		 others reserved.
 *
 * SAR0[11:9]  : CPU to L2 Clock भागider ratio
 *		 0 = (1/1) * CPU
 *		 2 = (1/2) * CPU
 *		 4 = (1/3) * CPU
 *		 6 = (1/4) * CPU
 *		 others reserved.
 *
 * SAR0[15:12] : CPU to DDR DRAM Clock भागider ratio
 *		 0  = (1/1) * CPU
 *		 2  = (1/2) * CPU
 *		 3  = (2/5) * CPU
 *		 4  = (1/3) * CPU
 *		 6  = (1/4) * CPU
 *		 8  = (1/5) * CPU
 *		 10 = (1/6) * CPU
 *		 12 = (1/7) * CPU
 *		 14 = (1/8) * CPU
 *		 15 = (1/10) * CPU
 *		 others reserved.
 *
 * SAR0[24:23] : TCLK frequency
 *		 0 = 166 MHz
 *		 1 = 125 MHz
 *		 others reserved.
 */

#घोषणा SAR_DOVE_CPU_FREQ		5
#घोषणा SAR_DOVE_CPU_FREQ_MASK		0xf
#घोषणा SAR_DOVE_L2_RATIO		9
#घोषणा SAR_DOVE_L2_RATIO_MASK		0x7
#घोषणा SAR_DOVE_DDR_RATIO		12
#घोषणा SAR_DOVE_DDR_RATIO_MASK		0xf
#घोषणा SAR_DOVE_TCLK_FREQ		23
#घोषणा SAR_DOVE_TCLK_FREQ_MASK		0x3

क्रमागत अणु DOVE_CPU_TO_L2, DOVE_CPU_TO_DDR पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio करोve_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = DOVE_CPU_TO_L2, .name = "l2clk", पूर्ण,
	अणु .id = DOVE_CPU_TO_DDR, .name = "ddrclk", पूर्ण
पूर्ण;

अटल स्थिर u32 करोve_tclk_freqs[] __initस्थिर = अणु
	166666667,
	125000000,
	0, 0
पूर्ण;

अटल u32 __init करोve_get_tclk_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_DOVE_TCLK_FREQ) &
		SAR_DOVE_TCLK_FREQ_MASK;
	वापस करोve_tclk_freqs[opt];
पूर्ण

अटल स्थिर u32 करोve_cpu_freqs[] __initस्थिर = अणु
	0, 0, 0, 0, 0,
	1000000000,
	933333333, 933333333,
	800000000, 800000000, 800000000,
	1066666667,
	666666667,
	533333333,
	400000000,
	333333333
पूर्ण;

अटल u32 __init करोve_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_DOVE_CPU_FREQ) &
		SAR_DOVE_CPU_FREQ_MASK;
	वापस करोve_cpu_freqs[opt];
पूर्ण

अटल स्थिर पूर्णांक करोve_cpu_l2_ratios[8][2] __initस्थिर = अणु
	अणु 1, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 0, 1 पूर्ण,
	अणु 1, 3 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 4 पूर्ण, अणु 0, 1 पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक करोve_cpu_ddr_ratios[16][2] __initस्थिर = अणु
	अणु 1, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 5 पूर्ण,
	अणु 1, 3 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 4 पूर्ण, अणु 0, 1 पूर्ण,
	अणु 1, 5 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 6 पूर्ण, अणु 0, 1 पूर्ण,
	अणु 1, 7 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 8 पूर्ण, अणु 1, 10 पूर्ण
पूर्ण;

अटल व्योम __init करोve_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	चयन (id) अणु
	हाल DOVE_CPU_TO_L2:
	अणु
		u32 opt = (पढ़ोl(sar) >> SAR_DOVE_L2_RATIO) &
			SAR_DOVE_L2_RATIO_MASK;
		*mult = करोve_cpu_l2_ratios[opt][0];
		*भाग = करोve_cpu_l2_ratios[opt][1];
		अवरोध;
	पूर्ण
	हाल DOVE_CPU_TO_DDR:
	अणु
		u32 opt = (पढ़ोl(sar) >> SAR_DOVE_DDR_RATIO) &
			SAR_DOVE_DDR_RATIO_MASK;
		*mult = करोve_cpu_ddr_ratios[opt][0];
		*भाग = करोve_cpu_ddr_ratios[opt][1];
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc करोve_coreclks = अणु
	.get_tclk_freq = करोve_get_tclk_freq,
	.get_cpu_freq = करोve_get_cpu_freq,
	.get_clk_ratio = करोve_get_clk_ratio,
	.ratios = करोve_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(करोve_coreclk_ratios),
पूर्ण;

/*
 * Clock Gating Control
 */

अटल स्थिर काष्ठा clk_gating_soc_desc करोve_gating_desc[] __initस्थिर = अणु
	अणु "usb0", शून्य, 0, 0 पूर्ण,
	अणु "usb1", शून्य, 1, 0 पूर्ण,
	अणु "ge",	"gephy", 2, 0 पूर्ण,
	अणु "sata", शून्य, 3, 0 पूर्ण,
	अणु "pex0", शून्य, 4, 0 पूर्ण,
	अणु "pex1", शून्य, 5, 0 पूर्ण,
	अणु "sdio0", शून्य, 8, 0 पूर्ण,
	अणु "sdio1", शून्य, 9, 0 पूर्ण,
	अणु "nand", शून्य, 10, 0 पूर्ण,
	अणु "camera", शून्य, 11, 0 पूर्ण,
	अणु "i2s0", शून्य, 12, 0 पूर्ण,
	अणु "i2s1", शून्य, 13, 0 पूर्ण,
	अणु "crypto", शून्य, 15, 0 पूर्ण,
	अणु "ac97", शून्य, 21, 0 पूर्ण,
	अणु "pdma", शून्य, 22, 0 पूर्ण,
	अणु "xor0", शून्य, 23, 0 पूर्ण,
	अणु "xor1", शून्य, 24, 0 पूर्ण,
	अणु "gephy", शून्य, 30, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init करोve_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cgnp =
		of_find_compatible_node(शून्य, शून्य, "marvell,dove-gating-clock");
	काष्ठा device_node *ddnp =
		of_find_compatible_node(शून्य, शून्य, "marvell,dove-divider-clock");

	mvebu_coreclk_setup(np, &करोve_coreclks);

	अगर (ddnp) अणु
		करोve_भागider_clk_init(ddnp);
		of_node_put(ddnp);
	पूर्ण

	अगर (cgnp) अणु
		mvebu_clk_gating_setup(cgnp, करोve_gating_desc);
		of_node_put(cgnp);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(करोve_clk, "marvell,dove-core-clock", करोve_clk_init);
