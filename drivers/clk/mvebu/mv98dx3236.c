<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell MV98DX3236 SoC घड़ीs
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
 * For 98DX4251 Sample At Reset the CPU, DDR and Main PLL घड़ीs are all
 * defined at the same समय
 *
 * SAR1[20:18]   : CPU frequency    DDR frequency   MPLL frequency
 *		 0  =  400 MHz	    400 MHz	    800 MHz
 *		 2  =  667 MHz	    667 MHz	    2000 MHz
 *		 3  =  800 MHz	    800 MHz	    1600 MHz
 *		 others reserved.
 *
 * For 98DX3236 Sample At Reset the CPU, DDR and Main PLL घड़ीs are all
 * defined at the same समय
 *
 * SAR1[20:18]   : CPU frequency    DDR frequency   MPLL frequency
 *		 1  =  667 MHz	    667 MHz	    2000 MHz
 *		 2  =  400 MHz	    400 MHz	    400 MHz
 *		 3  =  800 MHz	    800 MHz	    800 MHz
 *		 5  =  800 MHz	    400 MHz	    800 MHz
 *		 others reserved.
 */

#घोषणा SAR1_MV98DX3236_CPU_DDR_MPLL_FREQ_OPT		18
#घोषणा SAR1_MV98DX3236_CPU_DDR_MPLL_FREQ_OPT_MASK	0x7

अटल u32 __init mv98dx3236_get_tclk_freq(व्योम __iomem *sar)
अणु
	/* Tclk = 200MHz, no SaR dependency */
	वापस 200000000;
पूर्ण

अटल स्थिर u32 mv98dx3236_cpu_frequencies[] __initस्थिर = अणु
	0,
	667000000,
	400000000,
	800000000,
	0,
	800000000,
	0, 0,
पूर्ण;

अटल स्थिर u32 mv98dx4251_cpu_frequencies[] __initस्थिर = अणु
	400000000,
	0,
	667000000,
	800000000,
	0, 0, 0, 0,
पूर्ण;

अटल u32 __init mv98dx3236_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 cpu_freq = 0;
	u8 cpu_freq_select = 0;

	cpu_freq_select = ((पढ़ोl(sar) >> SAR1_MV98DX3236_CPU_DDR_MPLL_FREQ_OPT) &
			   SAR1_MV98DX3236_CPU_DDR_MPLL_FREQ_OPT_MASK);

	अगर (of_machine_is_compatible("marvell,armadaxp-98dx4251"))
		cpu_freq = mv98dx4251_cpu_frequencies[cpu_freq_select];
	अन्यथा अगर (of_machine_is_compatible("marvell,armadaxp-98dx3236"))
		cpu_freq = mv98dx3236_cpu_frequencies[cpu_freq_select];

	अगर (!cpu_freq)
		pr_err("CPU freq select unsupported %d\n", cpu_freq_select);

	वापस cpu_freq;
पूर्ण

क्रमागत अणु
	MV98DX3236_CPU_TO_DDR,
	MV98DX3236_CPU_TO_MPLL
पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio mv98dx3236_core_ratios[] __initस्थिर = अणु
	अणु .id = MV98DX3236_CPU_TO_DDR, .name = "ddrclk" पूर्ण,
	अणु .id = MV98DX3236_CPU_TO_MPLL, .name = "mpll" पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक __initस्थिर mv98dx3236_cpu_mpll_ratios[8][2] = अणु
	अणु0, 1पूर्ण, अणु3, 1पूर्ण, अणु1, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु1, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक __initस्थिर mv98dx3236_cpu_ddr_ratios[8][2] = अणु
	अणु0, 1पूर्ण, अणु1, 1पूर्ण, अणु1, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु1, 2पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक __initस्थिर mv98dx4251_cpu_mpll_ratios[8][2] = अणु
	अणु2, 1पूर्ण, अणु0, 1पूर्ण, अणु3, 1पूर्ण, अणु2, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक __initस्थिर mv98dx4251_cpu_ddr_ratios[8][2] = अणु
	अणु1, 1पूर्ण, अणु0, 1पूर्ण, अणु1, 1पूर्ण, अणु1, 1पूर्ण,
	अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण, अणु0, 1पूर्ण,
पूर्ण;

अटल व्योम __init mv98dx3236_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = ((पढ़ोl(sar) >> SAR1_MV98DX3236_CPU_DDR_MPLL_FREQ_OPT) &
		SAR1_MV98DX3236_CPU_DDR_MPLL_FREQ_OPT_MASK);

	चयन (id) अणु
	हाल MV98DX3236_CPU_TO_DDR:
		अगर (of_machine_is_compatible("marvell,armadaxp-98dx4251")) अणु
			*mult = mv98dx4251_cpu_ddr_ratios[opt][0];
			*भाग = mv98dx4251_cpu_ddr_ratios[opt][1];
		पूर्ण अन्यथा अगर (of_machine_is_compatible("marvell,armadaxp-98dx3236")) अणु
			*mult = mv98dx3236_cpu_ddr_ratios[opt][0];
			*भाग = mv98dx3236_cpu_ddr_ratios[opt][1];
		पूर्ण
		अवरोध;
	हाल MV98DX3236_CPU_TO_MPLL:
		अगर (of_machine_is_compatible("marvell,armadaxp-98dx4251")) अणु
			*mult = mv98dx4251_cpu_mpll_ratios[opt][0];
			*भाग = mv98dx4251_cpu_mpll_ratios[opt][1];
		पूर्ण अन्यथा अगर (of_machine_is_compatible("marvell,armadaxp-98dx3236")) अणु
			*mult = mv98dx3236_cpu_mpll_ratios[opt][0];
			*भाग = mv98dx3236_cpu_mpll_ratios[opt][1];
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc mv98dx3236_core_घड़ीs = अणु
	.get_tclk_freq = mv98dx3236_get_tclk_freq,
	.get_cpu_freq = mv98dx3236_get_cpu_freq,
	.get_clk_ratio = mv98dx3236_get_clk_ratio,
	.ratios = mv98dx3236_core_ratios,
	.num_ratios = ARRAY_SIZE(mv98dx3236_core_ratios),
पूर्ण;


/*
 * Clock Gating Control
 */

अटल स्थिर काष्ठा clk_gating_soc_desc mv98dx3236_gating_desc[] __initस्थिर = अणु
	अणु "ge1", शून्य, 3, 0 पूर्ण,
	अणु "ge0", शून्य, 4, 0 पूर्ण,
	अणु "pex00", शून्य, 5, 0 पूर्ण,
	अणु "sdio", शून्य, 17, 0 पूर्ण,
	अणु "usb0", शून्य, 18, 0 पूर्ण,
	अणु "xor0", शून्य, 22, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init mv98dx3236_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cgnp =
		of_find_compatible_node(शून्य, शून्य, "marvell,mv98dx3236-gating-clock");

	mvebu_coreclk_setup(np, &mv98dx3236_core_घड़ीs);

	अगर (cgnp) अणु
		mvebu_clk_gating_setup(cgnp, mv98dx3236_gating_desc);
		of_node_put(cgnp);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(mv98dx3236_clk, "marvell,mv98dx3236-core-clock", mv98dx3236_clk_init);
