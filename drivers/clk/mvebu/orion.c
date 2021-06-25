<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Orion SoC घड़ीs
 *
 * Copyright (C) 2014 Thomas Petazzoni
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश "common.h"

अटल स्थिर काष्ठा coreclk_ratio orion_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = 0, .name = "ddrclk", पूर्ण
पूर्ण;

/*
 * Orion 5181
 */

#घोषणा SAR_MV88F5181_TCLK_FREQ      8
#घोषणा SAR_MV88F5181_TCLK_FREQ_MASK 0x3

अटल u32 __init mv88f5181_get_tclk_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5181_TCLK_FREQ) &
		SAR_MV88F5181_TCLK_FREQ_MASK;
	अगर (opt == 0)
		वापस 133333333;
	अन्यथा अगर (opt == 1)
		वापस 150000000;
	अन्यथा अगर (opt == 2)
		वापस 166666667;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा SAR_MV88F5181_CPU_FREQ       4
#घोषणा SAR_MV88F5181_CPU_FREQ_MASK  0xf

अटल u32 __init mv88f5181_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5181_CPU_FREQ) &
		SAR_MV88F5181_CPU_FREQ_MASK;
	अगर (opt == 0)
		वापस 333333333;
	अन्यथा अगर (opt == 1 || opt == 2)
		वापस 400000000;
	अन्यथा अगर (opt == 3)
		वापस 500000000;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम __init mv88f5181_get_clk_ratio(व्योम __iomem *sar, पूर्णांक id,
					   पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5181_CPU_FREQ) &
		SAR_MV88F5181_CPU_FREQ_MASK;
	अगर (opt == 0 || opt == 1) अणु
		*mult = 1;
		*भाग  = 2;
	पूर्ण अन्यथा अगर (opt == 2 || opt == 3) अणु
		*mult = 1;
		*भाग  = 3;
	पूर्ण अन्यथा अणु
		*mult = 0;
		*भाग  = 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc mv88f5181_coreclks = अणु
	.get_tclk_freq = mv88f5181_get_tclk_freq,
	.get_cpu_freq = mv88f5181_get_cpu_freq,
	.get_clk_ratio = mv88f5181_get_clk_ratio,
	.ratios = orion_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(orion_coreclk_ratios),
पूर्ण;

अटल व्योम __init mv88f5181_clk_init(काष्ठा device_node *np)
अणु
	वापस mvebu_coreclk_setup(np, &mv88f5181_coreclks);
पूर्ण

CLK_OF_DECLARE(mv88f5181_clk, "marvell,mv88f5181-core-clock", mv88f5181_clk_init);

/*
 * Orion 5182
 */

#घोषणा SAR_MV88F5182_TCLK_FREQ      8
#घोषणा SAR_MV88F5182_TCLK_FREQ_MASK 0x3

अटल u32 __init mv88f5182_get_tclk_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5182_TCLK_FREQ) &
		SAR_MV88F5182_TCLK_FREQ_MASK;
	अगर (opt == 1)
		वापस 150000000;
	अन्यथा अगर (opt == 2)
		वापस 166666667;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा SAR_MV88F5182_CPU_FREQ       4
#घोषणा SAR_MV88F5182_CPU_FREQ_MASK  0xf

अटल u32 __init mv88f5182_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5182_CPU_FREQ) &
		SAR_MV88F5182_CPU_FREQ_MASK;
	अगर (opt == 0)
		वापस 333333333;
	अन्यथा अगर (opt == 1 || opt == 2)
		वापस 400000000;
	अन्यथा अगर (opt == 3)
		वापस 500000000;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम __init mv88f5182_get_clk_ratio(व्योम __iomem *sar, पूर्णांक id,
					   पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5182_CPU_FREQ) &
		SAR_MV88F5182_CPU_FREQ_MASK;
	अगर (opt == 0 || opt == 1) अणु
		*mult = 1;
		*भाग  = 2;
	पूर्ण अन्यथा अगर (opt == 2 || opt == 3) अणु
		*mult = 1;
		*भाग  = 3;
	पूर्ण अन्यथा अणु
		*mult = 0;
		*भाग  = 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc mv88f5182_coreclks = अणु
	.get_tclk_freq = mv88f5182_get_tclk_freq,
	.get_cpu_freq = mv88f5182_get_cpu_freq,
	.get_clk_ratio = mv88f5182_get_clk_ratio,
	.ratios = orion_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(orion_coreclk_ratios),
पूर्ण;

अटल व्योम __init mv88f5182_clk_init(काष्ठा device_node *np)
अणु
	वापस mvebu_coreclk_setup(np, &mv88f5182_coreclks);
पूर्ण

CLK_OF_DECLARE(mv88f5182_clk, "marvell,mv88f5182-core-clock", mv88f5182_clk_init);

/*
 * Orion 5281
 */

अटल u32 __init mv88f5281_get_tclk_freq(व्योम __iomem *sar)
अणु
	/* On 5281, tclk is always 166 Mhz */
	वापस 166666667;
पूर्ण

#घोषणा SAR_MV88F5281_CPU_FREQ       4
#घोषणा SAR_MV88F5281_CPU_FREQ_MASK  0xf

अटल u32 __init mv88f5281_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5281_CPU_FREQ) &
		SAR_MV88F5281_CPU_FREQ_MASK;
	अगर (opt == 1 || opt == 2)
		वापस 400000000;
	अन्यथा अगर (opt == 3)
		वापस 500000000;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम __init mv88f5281_get_clk_ratio(व्योम __iomem *sar, पूर्णांक id,
					   पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F5281_CPU_FREQ) &
		SAR_MV88F5281_CPU_FREQ_MASK;
	अगर (opt == 1) अणु
		*mult = 1;
		*भाग = 2;
	पूर्ण अन्यथा अगर (opt == 2 || opt == 3) अणु
		*mult = 1;
		*भाग = 3;
	पूर्ण अन्यथा अणु
		*mult = 0;
		*भाग = 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc mv88f5281_coreclks = अणु
	.get_tclk_freq = mv88f5281_get_tclk_freq,
	.get_cpu_freq = mv88f5281_get_cpu_freq,
	.get_clk_ratio = mv88f5281_get_clk_ratio,
	.ratios = orion_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(orion_coreclk_ratios),
पूर्ण;

अटल व्योम __init mv88f5281_clk_init(काष्ठा device_node *np)
अणु
	वापस mvebu_coreclk_setup(np, &mv88f5281_coreclks);
पूर्ण

CLK_OF_DECLARE(mv88f5281_clk, "marvell,mv88f5281-core-clock", mv88f5281_clk_init);

/*
 * Orion 6183
 */

#घोषणा SAR_MV88F6183_TCLK_FREQ      9
#घोषणा SAR_MV88F6183_TCLK_FREQ_MASK 0x1

अटल u32 __init mv88f6183_get_tclk_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F6183_TCLK_FREQ) &
		SAR_MV88F6183_TCLK_FREQ_MASK;
	अगर (opt == 0)
		वापस 133333333;
	अन्यथा अगर (opt == 1)
		वापस 166666667;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा SAR_MV88F6183_CPU_FREQ       1
#घोषणा SAR_MV88F6183_CPU_FREQ_MASK  0x3f

अटल u32 __init mv88f6183_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F6183_CPU_FREQ) &
		SAR_MV88F6183_CPU_FREQ_MASK;
	अगर (opt == 9)
		वापस 333333333;
	अन्यथा अगर (opt == 17)
		वापस 400000000;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम __init mv88f6183_get_clk_ratio(व्योम __iomem *sar, पूर्णांक id,
					   पूर्णांक *mult, पूर्णांक *भाग)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F6183_CPU_FREQ) &
		SAR_MV88F6183_CPU_FREQ_MASK;
	अगर (opt == 9 || opt == 17) अणु
		*mult = 1;
		*भाग  = 2;
	पूर्ण अन्यथा अणु
		*mult = 0;
		*भाग  = 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc mv88f6183_coreclks = अणु
	.get_tclk_freq = mv88f6183_get_tclk_freq,
	.get_cpu_freq = mv88f6183_get_cpu_freq,
	.get_clk_ratio = mv88f6183_get_clk_ratio,
	.ratios = orion_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(orion_coreclk_ratios),
पूर्ण;


अटल व्योम __init mv88f6183_clk_init(काष्ठा device_node *np)
अणु
	वापस mvebu_coreclk_setup(np, &mv88f6183_coreclks);
पूर्ण

CLK_OF_DECLARE(mv88f6183_clk, "marvell,mv88f6183-core-clock", mv88f6183_clk_init);
