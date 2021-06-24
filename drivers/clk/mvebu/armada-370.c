<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada 370 SoC घड़ीs
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
 */

#घोषणा SARL				0	/* Low part [0:31] */
#घोषणा	 SARL_A370_SSCG_ENABLE		BIT(10)
#घोषणा	 SARL_A370_PCLK_FREQ_OPT	11
#घोषणा	 SARL_A370_PCLK_FREQ_OPT_MASK	0xF
#घोषणा	 SARL_A370_FAB_FREQ_OPT		15
#घोषणा	 SARL_A370_FAB_FREQ_OPT_MASK	0x1F
#घोषणा	 SARL_A370_TCLK_FREQ_OPT	20
#घोषणा	 SARL_A370_TCLK_FREQ_OPT_MASK	0x1

क्रमागत अणु A370_CPU_TO_NBCLK, A370_CPU_TO_HCLK, A370_CPU_TO_DRAMCLK पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio a370_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = A370_CPU_TO_NBCLK, .name = "nbclk" पूर्ण,
	अणु .id = A370_CPU_TO_HCLK, .name = "hclk" पूर्ण,
	अणु .id = A370_CPU_TO_DRAMCLK, .name = "dramclk" पूर्ण,
पूर्ण;

अटल स्थिर u32 a370_tclk_freqs[] __initस्थिर = अणु
	166000000,
	200000000,
पूर्ण;

अटल u32 __init a370_get_tclk_freq(व्योम __iomem *sar)
अणु
	u8 tclk_freq_select = 0;

	tclk_freq_select = ((पढ़ोl(sar) >> SARL_A370_TCLK_FREQ_OPT) &
			    SARL_A370_TCLK_FREQ_OPT_MASK);
	वापस a370_tclk_freqs[tclk_freq_select];
पूर्ण

अटल स्थिर u32 a370_cpu_freqs[] __initस्थिर = अणु
	400000000,
	533000000,
	667000000,
	800000000,
	1000000000,
	1067000000,
	1200000000,
पूर्ण;

अटल u32 __init a370_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 cpu_freq;
	u8 cpu_freq_select = 0;

	cpu_freq_select = ((पढ़ोl(sar) >> SARL_A370_PCLK_FREQ_OPT) &
			   SARL_A370_PCLK_FREQ_OPT_MASK);
	अगर (cpu_freq_select >= ARRAY_SIZE(a370_cpu_freqs)) अणु
		pr_err("CPU freq select unsupported %d\n", cpu_freq_select);
		cpu_freq = 0;
	पूर्ण अन्यथा
		cpu_freq = a370_cpu_freqs[cpu_freq_select];

	वापस cpu_freq;
पूर्ण

अटल स्थिर पूर्णांक a370_nbclk_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 2पूर्ण, अणु2, 2पूर्ण,
	अणु1, 2पूर्ण, अणु1, 2पूर्ण, अणु1, 1पूर्ण, अणु2, 3पूर्ण,
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 4पूर्ण, अणु0, 1पूर्ण,
	अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 2पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु2, 3पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक a370_hclk_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 6पूर्ण, अणु2, 3पूर्ण,
	अणु1, 3पूर्ण, अणु1, 4पूर्ण, अणु1, 2पूर्ण, अणु2, 6पूर्ण,
	अणु0, 1पूर्ण, अणु1, 6पूर्ण, अणु2, 10पूर्ण, अणु0, 1पूर्ण,
	अणु1, 4पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 5पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 2पूर्ण,
	अणु2, 6पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक a370_dramclk_ratios[32][2] __initस्थिर = अणु
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु2, 3पूर्ण, अणु2, 3पूर्ण,
	अणु1, 3पूर्ण, अणु1, 2पूर्ण, अणु1, 2पूर्ण, अणु2, 6पूर्ण,
	अणु0, 1पूर्ण, अणु1, 3पूर्ण, अणु2, 5पूर्ण, अणु0, 1पूर्ण,
	अणु1, 4पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु2, 5पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु2, 3पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल व्योम __init a370_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = ((पढ़ोl(sar) >> SARL_A370_FAB_FREQ_OPT) &
		SARL_A370_FAB_FREQ_OPT_MASK);

	चयन (id) अणु
	हाल A370_CPU_TO_NBCLK:
		*mult = a370_nbclk_ratios[opt][0];
		*भाग = a370_nbclk_ratios[opt][1];
		अवरोध;
	हाल A370_CPU_TO_HCLK:
		*mult = a370_hclk_ratios[opt][0];
		*भाग = a370_hclk_ratios[opt][1];
		अवरोध;
	हाल A370_CPU_TO_DRAMCLK:
		*mult = a370_dramclk_ratios[opt][0];
		*भाग = a370_dramclk_ratios[opt][1];
		अवरोध;
	पूर्ण
पूर्ण

अटल bool a370_is_sscg_enabled(व्योम __iomem *sar)
अणु
	वापस !(पढ़ोl(sar) & SARL_A370_SSCG_ENABLE);
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc a370_coreclks = अणु
	.get_tclk_freq = a370_get_tclk_freq,
	.get_cpu_freq = a370_get_cpu_freq,
	.get_clk_ratio = a370_get_clk_ratio,
	.is_sscg_enabled = a370_is_sscg_enabled,
	.fix_sscg_deviation = kirkwood_fix_sscg_deviation,
	.ratios = a370_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(a370_coreclk_ratios),
पूर्ण;

/*
 * Clock Gating Control
 */

अटल स्थिर काष्ठा clk_gating_soc_desc a370_gating_desc[] __initस्थिर = अणु
	अणु "audio", शून्य, 0, 0 पूर्ण,
	अणु "pex0_en", शून्य, 1, 0 पूर्ण,
	अणु "pex1_en", शून्य,  2, 0 पूर्ण,
	अणु "ge1", शून्य, 3, 0 पूर्ण,
	अणु "ge0", शून्य, 4, 0 पूर्ण,
	अणु "pex0", "pex0_en", 5, 0 पूर्ण,
	अणु "pex1", "pex1_en", 9, 0 पूर्ण,
	अणु "sata0", शून्य, 15, 0 पूर्ण,
	अणु "sdio", शून्य, 17, 0 पूर्ण,
	अणु "crypto", शून्य, 23, CLK_IGNORE_UNUSED पूर्ण,
	अणु "tdm", शून्य, 25, 0 पूर्ण,
	अणु "ddr", शून्य, 28, CLK_IGNORE_UNUSED पूर्ण,
	अणु "sata1", शून्य, 30, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init a370_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cgnp =
		of_find_compatible_node(शून्य, शून्य, "marvell,armada-370-gating-clock");

	mvebu_coreclk_setup(np, &a370_coreclks);

	अगर (cgnp) अणु
		mvebu_clk_gating_setup(cgnp, a370_gating_desc);
		of_node_put(cgnp);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(a370_clk, "marvell,armada-370-core-clock", a370_clk_init);

