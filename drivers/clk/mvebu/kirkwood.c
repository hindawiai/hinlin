<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Kirkwood SoC घड़ीs
 *
 * Copyright (C) 2012 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Andrew Lunn <andrew@lunn.ch>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश "common.h"

/*
 * Core Clocks
 *
 * Kirkwood PLL sample-at-reset configuration
 * (6180 has dअगरferent SAR layout than other Kirkwood SoCs)
 *
 * SAR0[4:3,22,1] : CPU frequency (6281,6292,6282)
 *	4  =  600 MHz
 *	6  =  800 MHz
 *	7  = 1000 MHz
 *	9  = 1200 MHz
 *	12 = 1500 MHz
 *	13 = 1600 MHz
 *	14 = 1800 MHz
 *	15 = 2000 MHz
 *	others reserved.
 *
 * SAR0[19,10:9] : CPU to L2 Clock भागider ratio (6281,6292,6282)
 *	1 = (1/2) * CPU
 *	3 = (1/3) * CPU
 *	5 = (1/4) * CPU
 *	others reserved.
 *
 * SAR0[8:5] : CPU to DDR DRAM Clock भागider ratio (6281,6292,6282)
 *	2 = (1/2) * CPU
 *	4 = (1/3) * CPU
 *	6 = (1/4) * CPU
 *	7 = (2/9) * CPU
 *	8 = (1/5) * CPU
 *	9 = (1/6) * CPU
 *	others reserved.
 *
 * SAR0[4:2] : Kirkwood 6180 cpu/l2/ddr घड़ी configuration (6180 only)
 *	5 = [CPU =  600 MHz, L2 = (1/2) * CPU, DDR = 200 MHz = (1/3) * CPU]
 *	6 = [CPU =  800 MHz, L2 = (1/2) * CPU, DDR = 200 MHz = (1/4) * CPU]
 *	7 = [CPU = 1000 MHz, L2 = (1/2) * CPU, DDR = 200 MHz = (1/5) * CPU]
 *	others reserved.
 *
 * SAR0[21] : TCLK frequency
 *	0 = 200 MHz
 *	1 = 166 MHz
 *	others reserved.
 */

#घोषणा SAR_KIRKWOOD_CPU_FREQ(x)	\
	(((x & (1 <<  1)) >>  1) |	\
	 ((x & (1 << 22)) >> 21) |	\
	 ((x & (3 <<  3)) >>  1))
#घोषणा SAR_KIRKWOOD_L2_RATIO(x)	\
	(((x & (3 <<  9)) >> 9) |	\
	 (((x & (1 << 19)) >> 17)))
#घोषणा SAR_KIRKWOOD_DDR_RATIO		5
#घोषणा SAR_KIRKWOOD_DDR_RATIO_MASK	0xf
#घोषणा SAR_MV88F6180_CLK		2
#घोषणा SAR_MV88F6180_CLK_MASK		0x7
#घोषणा SAR_KIRKWOOD_TCLK_FREQ		21
#घोषणा SAR_KIRKWOOD_TCLK_FREQ_MASK	0x1

क्रमागत अणु KIRKWOOD_CPU_TO_L2, KIRKWOOD_CPU_TO_DDR पूर्ण;

अटल स्थिर काष्ठा coreclk_ratio kirkwood_coreclk_ratios[] __initस्थिर = अणु
	अणु .id = KIRKWOOD_CPU_TO_L2, .name = "l2clk", पूर्ण,
	अणु .id = KIRKWOOD_CPU_TO_DDR, .name = "ddrclk", पूर्ण
पूर्ण;

अटल u32 __init kirkwood_get_tclk_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_KIRKWOOD_TCLK_FREQ) &
		SAR_KIRKWOOD_TCLK_FREQ_MASK;
	वापस (opt) ? 166666667 : 200000000;
पूर्ण

अटल स्थिर u32 kirkwood_cpu_freqs[] __initस्थिर = अणु
	0, 0, 0, 0,
	600000000,
	0,
	800000000,
	1000000000,
	0,
	1200000000,
	0, 0,
	1500000000,
	1600000000,
	1800000000,
	2000000000
पूर्ण;

अटल u32 __init kirkwood_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = SAR_KIRKWOOD_CPU_FREQ(पढ़ोl(sar));
	वापस kirkwood_cpu_freqs[opt];
पूर्ण

अटल स्थिर पूर्णांक kirkwood_cpu_l2_ratios[8][2] __initस्थिर = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 3 पूर्ण,
	अणु 0, 1 पूर्ण, अणु 1, 4 पूर्ण, अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक kirkwood_cpu_ddr_ratios[16][2] __initस्थिर = अणु
	अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 0, 1 पूर्ण,
	अणु 1, 3 पूर्ण, अणु 0, 1 पूर्ण, अणु 1, 4 पूर्ण, अणु 2, 9 पूर्ण,
	अणु 1, 5 पूर्ण, अणु 1, 6 पूर्ण, अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण,
	अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण
पूर्ण;

अटल व्योम __init kirkwood_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	चयन (id) अणु
	हाल KIRKWOOD_CPU_TO_L2:
	अणु
		u32 opt = SAR_KIRKWOOD_L2_RATIO(पढ़ोl(sar));
		*mult = kirkwood_cpu_l2_ratios[opt][0];
		*भाग = kirkwood_cpu_l2_ratios[opt][1];
		अवरोध;
	पूर्ण
	हाल KIRKWOOD_CPU_TO_DDR:
	अणु
		u32 opt = (पढ़ोl(sar) >> SAR_KIRKWOOD_DDR_RATIO) &
			SAR_KIRKWOOD_DDR_RATIO_MASK;
		*mult = kirkwood_cpu_ddr_ratios[opt][0];
		*भाग = kirkwood_cpu_ddr_ratios[opt][1];
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर u32 mv88f6180_cpu_freqs[] __initस्थिर = अणु
	0, 0, 0, 0, 0,
	600000000,
	800000000,
	1000000000
पूर्ण;

अटल u32 __init mv88f6180_get_cpu_freq(व्योम __iomem *sar)
अणु
	u32 opt = (पढ़ोl(sar) >> SAR_MV88F6180_CLK) & SAR_MV88F6180_CLK_MASK;
	वापस mv88f6180_cpu_freqs[opt];
पूर्ण

अटल स्थिर पूर्णांक mv88f6180_cpu_ddr_ratios[8][2] __initस्थिर = अणु
	अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण, अणु 0, 1 पूर्ण,
	अणु 0, 1 पूर्ण, अणु 1, 3 पूर्ण, अणु 1, 4 पूर्ण, अणु 1, 5 पूर्ण
पूर्ण;

अटल व्योम __init mv88f6180_get_clk_ratio(
	व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग)
अणु
	चयन (id) अणु
	हाल KIRKWOOD_CPU_TO_L2:
	अणु
		/* mv88f6180 has a fixed 1:2 CPU-to-L2 ratio */
		*mult = 1;
		*भाग = 2;
		अवरोध;
	पूर्ण
	हाल KIRKWOOD_CPU_TO_DDR:
	अणु
		u32 opt = (पढ़ोl(sar) >> SAR_MV88F6180_CLK) &
			SAR_MV88F6180_CLK_MASK;
		*mult = mv88f6180_cpu_ddr_ratios[opt][0];
		*भाग = mv88f6180_cpu_ddr_ratios[opt][1];
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल u32 __init mv98dx1135_get_tclk_freq(व्योम __iomem *sar)
अणु
	वापस 166666667;
पूर्ण

अटल स्थिर काष्ठा coreclk_soc_desc kirkwood_coreclks = अणु
	.get_tclk_freq = kirkwood_get_tclk_freq,
	.get_cpu_freq = kirkwood_get_cpu_freq,
	.get_clk_ratio = kirkwood_get_clk_ratio,
	.ratios = kirkwood_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(kirkwood_coreclk_ratios),
पूर्ण;

अटल स्थिर काष्ठा coreclk_soc_desc mv88f6180_coreclks = अणु
	.get_tclk_freq = kirkwood_get_tclk_freq,
	.get_cpu_freq = mv88f6180_get_cpu_freq,
	.get_clk_ratio = mv88f6180_get_clk_ratio,
	.ratios = kirkwood_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(kirkwood_coreclk_ratios),
पूर्ण;

अटल स्थिर काष्ठा coreclk_soc_desc mv98dx1135_coreclks = अणु
	.get_tclk_freq = mv98dx1135_get_tclk_freq,
	.get_cpu_freq = kirkwood_get_cpu_freq,
	.get_clk_ratio = kirkwood_get_clk_ratio,
	.ratios = kirkwood_coreclk_ratios,
	.num_ratios = ARRAY_SIZE(kirkwood_coreclk_ratios),
पूर्ण;

/*
 * Clock Gating Control
 */

अटल स्थिर काष्ठा clk_gating_soc_desc kirkwood_gating_desc[] __initस्थिर = अणु
	अणु "ge0", शून्य, 0, 0 पूर्ण,
	अणु "pex0", शून्य, 2, 0 पूर्ण,
	अणु "usb0", शून्य, 3, 0 पूर्ण,
	अणु "sdio", शून्य, 4, 0 पूर्ण,
	अणु "tsu", शून्य, 5, 0 पूर्ण,
	अणु "runit", शून्य, 7, 0 पूर्ण,
	अणु "xor0", शून्य, 8, 0 पूर्ण,
	अणु "audio", शून्य, 9, 0 पूर्ण,
	अणु "sata0", शून्य, 14, 0 पूर्ण,
	अणु "sata1", शून्य, 15, 0 पूर्ण,
	अणु "xor1", शून्य, 16, 0 पूर्ण,
	अणु "crypto", शून्य, 17, 0 पूर्ण,
	अणु "pex1", शून्य, 18, 0 पूर्ण,
	अणु "ge1", शून्य, 19, 0 पूर्ण,
	अणु "tdm", शून्य, 20, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;


/*
 * Clock Muxing Control
 */

काष्ठा clk_muxing_soc_desc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **parents;
	पूर्णांक num_parents;
	पूर्णांक shअगरt;
	पूर्णांक width;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा clk_muxing_ctrl अणु
	spinlock_t *lock;
	काष्ठा clk **muxes;
	पूर्णांक num_muxes;
पूर्ण;

अटल स्थिर अक्षर *घातersave_parents[] = अणु
	"cpuclk",
	"ddrclk",
पूर्ण;

अटल स्थिर काष्ठा clk_muxing_soc_desc kirkwood_mux_desc[] __initस्थिर = अणु
	अणु "powersave", घातersave_parents, ARRAY_SIZE(घातersave_parents),
		11, 1, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk *clk_muxing_get_src(
	काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा clk_muxing_ctrl *ctrl = (काष्ठा clk_muxing_ctrl *)data;
	पूर्णांक n;

	अगर (clkspec->args_count < 1)
		वापस ERR_PTR(-EINVAL);

	क्रम (n = 0; n < ctrl->num_muxes; n++) अणु
		काष्ठा clk_mux *mux =
			to_clk_mux(__clk_get_hw(ctrl->muxes[n]));
		अगर (clkspec->args[0] == mux->shअगरt)
			वापस ctrl->muxes[n];
	पूर्ण
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल व्योम __init kirkwood_clk_muxing_setup(काष्ठा device_node *np,
				   स्थिर काष्ठा clk_muxing_soc_desc *desc)
अणु
	काष्ठा clk_muxing_ctrl *ctrl;
	व्योम __iomem *base;
	पूर्णांक n;

	base = of_iomap(np, 0);
	अगर (WARN_ON(!base))
		वापस;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (WARN_ON(!ctrl))
		जाओ ctrl_out;

	/* lock must alपढ़ोy be initialized */
	ctrl->lock = &ctrl_gating_lock;

	/* Count, allocate, and रेजिस्टर घड़ी muxes */
	क्रम (n = 0; desc[n].name;)
		n++;

	ctrl->num_muxes = n;
	ctrl->muxes = kसुस्मृति(ctrl->num_muxes, माप(काष्ठा clk *),
			GFP_KERNEL);
	अगर (WARN_ON(!ctrl->muxes))
		जाओ muxes_out;

	क्रम (n = 0; n < ctrl->num_muxes; n++) अणु
		ctrl->muxes[n] = clk_रेजिस्टर_mux(शून्य, desc[n].name,
				desc[n].parents, desc[n].num_parents,
				desc[n].flags, base, desc[n].shअगरt,
				desc[n].width, desc[n].flags, ctrl->lock);
		WARN_ON(IS_ERR(ctrl->muxes[n]));
	पूर्ण

	of_clk_add_provider(np, clk_muxing_get_src, ctrl);

	वापस;
muxes_out:
	kमुक्त(ctrl);
ctrl_out:
	iounmap(base);
पूर्ण

अटल व्योम __init kirkwood_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cgnp =
		of_find_compatible_node(शून्य, शून्य, "marvell,kirkwood-gating-clock");


	अगर (of_device_is_compatible(np, "marvell,mv88f6180-core-clock"))
		mvebu_coreclk_setup(np, &mv88f6180_coreclks);
	अन्यथा अगर (of_device_is_compatible(np, "marvell,mv98dx1135-core-clock"))
		mvebu_coreclk_setup(np, &mv98dx1135_coreclks);
	अन्यथा
		mvebu_coreclk_setup(np, &kirkwood_coreclks);

	अगर (cgnp) अणु
		mvebu_clk_gating_setup(cgnp, kirkwood_gating_desc);
		kirkwood_clk_muxing_setup(cgnp, kirkwood_mux_desc);

		of_node_put(cgnp);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(kirkwood_clk, "marvell,kirkwood-core-clock",
	       kirkwood_clk_init);
CLK_OF_DECLARE(mv88f6180_clk, "marvell,mv88f6180-core-clock",
	       kirkwood_clk_init);
CLK_OF_DECLARE(98dx1135_clk, "marvell,mv98dx1135-core-clock",
	       kirkwood_clk_init);
