<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada XP SoC घड़ीs
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

/*
 * Core Clocks
 *
 * Armada XP Sample At Reset is a 64 bit bitfiled split in two
 * रेजिस्टर of 32 bits
 */

#घोषणा SARL				0	/* Low part [0:31] */
#घोषणा	 SARL_AXP_PCLK_FREQ_OPT		21
#घोषणा	 SARL_AXP_PCLK_FREQ_OPT_MASK	0x7
#घोषणा	 SARL_AXP_FAB_FREQ_OPT		24
#घोषणा	 SARL_AXP_FAB_FREQ_OPT_MASK	0xF
#घोषणा SARH				4	/* High part [32:63] */
#घोषणा	 SARH_AXP_PCLK_FREQ_OPT		(52-32)
#घोषणा	 SARH_AXP_PCLK_FREQ_OPT_MASK	0x1
#घोषणा	 SARH_AXP_PCLK_FREQ_OPT_SHIFT	3
#घोषणा	 SARH_AXP_FAB_FREQ_OPT		(51-32)
#घोषणा	 SARH_AXP_FAB_FREQ_OPT_MASK	0x1
#घोषणा	 SARH_AXP_FAB_FREQ_OPT_SHIFT	4

क्रमागत अणु AXP_CPU_TO_NBCLK, AXP_CPU_TO_HCLK, AXP_CPU_TO_DRAMCLK पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio axp_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = AXP_CPU_TO_NBCLK, .name = "nbclk" पूर्ण,
	अणु .id = AXP_CPU_TO_HCLK, .name = "hclk" पूर्ण,
	अणु .id = AXP_CPU_TO_DRAMCLK, .name = "dramclk" पूर्ण,
पूर्ण;

/* Armada XP TCLK frequency is fixed to 250MHz */
अटल u32 __init axp_get_tclk_freq(व्योम __iomem *sar)
अणु
	वापस 250000000;
पूर्ण

अटल स्थिर u32 axp_cpu_freqs[] __initस्थिर = अणु
	1000000000,
	1066000000,
	1200000000,
	1333000000,
	1500000000,
	1666000000,
	1800000000,
	2000000000,
	667000000,
	0,
	800000000,
	1600000000,
पूर्ण;

अटल u32 __init axp_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 cpu_freq;
	u8 cpu_freq_select = 0;

	cpu_freq_select = ((पढ़ोl(sar + SARL) >> SARL_AXP_PCLK_FREQ_OPT) &
			   SARL_AXP_PCLK_FREQ_OPT_MASK);
	/*
	 * The upper bit is not contiguous to the other ones and
	 * located in the high part of the SAR रेजिस्टरs
	 */
	cpu_freq_select |= (((पढ़ोl(sar + SARH) >> SARH_AXP_PCLK_FREQ_OPT) &
	     SARH_AXP_PCLK_FREQ_OPT_MASK) << SARH_AXP_PCLK_FREQ_OPT_SHIFT);
	अगर (cpu_freq_select >= ARRAY_SIZE(axp_cpu_freqs)) अणु
		pr_err("CPU freq select unsupported: %d\n", cpu_freq_select);
		cpu_freq = 0;
	पूर्ण अन्यथा
		cpu_freq = axp_cpu_freqs[cpu_freq_select];

	वापस cpu_freq;
पूर्ण

अटल स्थिर पूर्णांक axp_nbclk_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 2पूर्ण, अणु2, 2पूर्ण,
	अणु1, 2पूर्ण, अणु1, 2पूर्ण, अणु1, 1पूर्ण, अणु2, 3पूर्ण,
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 4पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 2पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु2, 3पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक axp_hclk_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 6पूर्ण, अणु2, 3पूर्ण,
	अणु1, 3पूर्ण, अणु1, 4पूर्ण, अणु1, 2पूर्ण, अणु2, 6पूर्ण,
	अणु0, 1पूर्ण, अणु1, 6पूर्ण, अणु2, 10पूर्ण, अणु0, 1पूर्ण,
	अणु1, 4पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 5पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण,
	अणु2, 6पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक axp_dramclk_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 3पूर्ण, अणु2, 3पूर्ण,
	अणु1, 3पूर्ण, अणु1, 2पूर्ण, अणु1, 2पूर्ण, अणु2, 6पूर्ण,
	अणु0, 1पूर्ण, अणु1, 3पूर्ण, अणु2, 5पूर्ण, अणु0, 1पूर्ण,
	अणु1, 4पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 5पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु2, 3पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल व्योम __init axp_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = ((पढ़ोl(sar + SARL) >> SARL_AXP_FAB_FREQ_OPT) &
	      SARL_AXP_FAB_FREQ_OPT_MASK);
	/*
	 * The upper bit is not contiguous to the other ones and
	 * located in the high part of the SAR रेजिस्टरs
	 */
	opt |= (((पढ़ोl(sar + SARH) >> SARH_AXP_FAB_FREQ_OPT) &
		 SARH_AXP_FAB_FREQ_OPT_MASK) << SARH_AXP_FAB_FREQ_OPT_SHIFT);

	चयन (id) अणु
	हाल AXP_CPU_TO_NBCLK:
		*mult = axp_nbclk_ratios[opt][0];
		*भाग = axp_nbclk_ratios[opt][1];
		अवरोध;
	हाल AXP_CPU_TO_HCLK:
		*mult = axp_hclk_ratios[opt][0];
		*भाग = axp_hclk_ratios[opt][1];
		अवरोध;
	हाल AXP_CPU_TO_DRAMCLK:
		*mult = axp_dramclk_ratios[opt][0];
		*भाग = axp_dramclk_ratios[opt][1];
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc axp_coreclks = अणु
	.get_tclk_freq = axp_get_tclk_freq,
	.get_cpu_freq = axp_get_cpu_freq,
	.get_clk_ratio = axp_get_clk_ratio,
	.ratios = axp_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(axp_coreclk_ratios),
पूर्ण;

/*
 * Clock Gating Control
 */

अटल स्थिर काष्ठा clk_gating_soc_desc axp_gating_desc[] __initस्थिर = अणु
	अणु "audio", शून्य, 0, 0 पूर्ण,
	अणु "ge3", शून्य, 1, 0 पूर्ण,
	अणु "ge2", शून्य,  2, 0 पूर्ण,
	अणु "ge1", शून्य, 3, 0 पूर्ण,
	अणु "ge0", शून्य, 4, 0 पूर्ण,
	अणु "pex00", शून्य, 5, 0 पूर्ण,
	अणु "pex01", शून्य, 6, 0 पूर्ण,
	अणु "pex02", शून्य, 7, 0 पूर्ण,
	अणु "pex03", शून्य, 8, 0 पूर्ण,
	अणु "pex10", शून्य, 9, 0 पूर्ण,
	अणु "pex11", शून्य, 10, 0 पूर्ण,
	अणु "pex12", शून्य, 11, 0 पूर्ण,
	अणु "pex13", शून्य, 12, 0 पूर्ण,
	अणु "bp", शून्य, 13, 0 पूर्ण,
	अणु "sata0lnk", शून्य, 14, 0 पूर्ण,
	अणु "sata0", "sata0lnk", 15, 0 पूर्ण,
	अणु "lcd", शून्य, 16, 0 पूर्ण,
	अणु "sdio", शून्य, 17, 0 पूर्ण,
	अणु "usb0", शून्य, 18, 0 पूर्ण,
	अणु "usb1", शून्य, 19, 0 पूर्ण,
	अणु "usb2", शून्य, 20, 0 पूर्ण,
	अणु "xor0", शून्य, 22, 0 पूर्ण,
	अणु "crypto", शून्य, 23, 0 पूर्ण,
	अणु "tdm", शून्य, 25, 0 पूर्ण,
	अणु "pex20", शून्य, 26, 0 पूर्ण,
	अणु "pex30", शून्य, 27, 0 पूर्ण,
	अणु "xor1", शून्य, 28, 0 पूर्ण,
	अणु "sata1lnk", शून्य, 29, 0 पूर्ण,
	अणु "sata1", "sata1lnk", 30, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init axp_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cgnp =
		of_find_compatible_node(शून्य, शून्य, "marvell,armada-xp-gating-clock");

	mvebu_coreclk_setup(np, &axp_coreclks);

	अगर (cgnp) अणु
		mvebu_clk_gating_setup(cgnp, axp_gating_desc);
		of_node_put(cgnp);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(axp_clk, "marvell,armada-xp-core-clock", axp_clk_init);
