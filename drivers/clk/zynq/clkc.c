<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Zynq घड़ी controller
 *
 *  Copyright (C) 2012 - 2013 Xilinx
 *
 *  Sथघren Brinkmann <soren.brinkmann@xilinx.com>
 */

#समावेश <linux/clk/zynq.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/पन.स>

अटल व्योम __iomem *zynq_clkc_base;

#घोषणा SLCR_ARMPLL_CTRL		(zynq_clkc_base + 0x00)
#घोषणा SLCR_DDRPLL_CTRL		(zynq_clkc_base + 0x04)
#घोषणा SLCR_IOPLL_CTRL			(zynq_clkc_base + 0x08)
#घोषणा SLCR_PLL_STATUS			(zynq_clkc_base + 0x0c)
#घोषणा SLCR_ARM_CLK_CTRL		(zynq_clkc_base + 0x20)
#घोषणा SLCR_DDR_CLK_CTRL		(zynq_clkc_base + 0x24)
#घोषणा SLCR_DCI_CLK_CTRL		(zynq_clkc_base + 0x28)
#घोषणा SLCR_APER_CLK_CTRL		(zynq_clkc_base + 0x2c)
#घोषणा SLCR_GEM0_CLK_CTRL		(zynq_clkc_base + 0x40)
#घोषणा SLCR_GEM1_CLK_CTRL		(zynq_clkc_base + 0x44)
#घोषणा SLCR_SMC_CLK_CTRL		(zynq_clkc_base + 0x48)
#घोषणा SLCR_LQSPI_CLK_CTRL		(zynq_clkc_base + 0x4c)
#घोषणा SLCR_SDIO_CLK_CTRL		(zynq_clkc_base + 0x50)
#घोषणा SLCR_UART_CLK_CTRL		(zynq_clkc_base + 0x54)
#घोषणा SLCR_SPI_CLK_CTRL		(zynq_clkc_base + 0x58)
#घोषणा SLCR_CAN_CLK_CTRL		(zynq_clkc_base + 0x5c)
#घोषणा SLCR_CAN_MIOCLK_CTRL		(zynq_clkc_base + 0x60)
#घोषणा SLCR_DBG_CLK_CTRL		(zynq_clkc_base + 0x64)
#घोषणा SLCR_PCAP_CLK_CTRL		(zynq_clkc_base + 0x68)
#घोषणा SLCR_FPGA0_CLK_CTRL		(zynq_clkc_base + 0x70)
#घोषणा SLCR_621_TRUE			(zynq_clkc_base + 0xc4)
#घोषणा SLCR_SWDT_CLK_SEL		(zynq_clkc_base + 0x204)

#घोषणा NUM_MIO_PINS	54

#घोषणा DBG_CLK_CTRL_CLKACT_TRC		BIT(0)
#घोषणा DBG_CLK_CTRL_CPU_1XCLKACT	BIT(1)

क्रमागत zynq_clk अणु
	armpll, ddrpll, iopll,
	cpu_6or4x, cpu_3or2x, cpu_2x, cpu_1x,
	ddr2x, ddr3x, dci,
	lqspi, smc, pcap, gem0, gem1, fclk0, fclk1, fclk2, fclk3, can0, can1,
	sdio0, sdio1, uart0, uart1, spi0, spi1, dma,
	usb0_aper, usb1_aper, gem0_aper, gem1_aper,
	sdio0_aper, sdio1_aper, spi0_aper, spi1_aper, can0_aper, can1_aper,
	i2c0_aper, i2c1_aper, uart0_aper, uart1_aper, gpio_aper, lqspi_aper,
	smc_aper, swdt, dbg_trc, dbg_apb, clk_maxपूर्ण;

अटल काष्ठा clk *ps_clk;
अटल काष्ठा clk *clks[clk_max];
अटल काष्ठा clk_onecell_data clk_data;

अटल DEFINE_SPINLOCK(armpll_lock);
अटल DEFINE_SPINLOCK(ddrpll_lock);
अटल DEFINE_SPINLOCK(iopll_lock);
अटल DEFINE_SPINLOCK(armclk_lock);
अटल DEFINE_SPINLOCK(swdtclk_lock);
अटल DEFINE_SPINLOCK(ddrclk_lock);
अटल DEFINE_SPINLOCK(dciclk_lock);
अटल DEFINE_SPINLOCK(gem0clk_lock);
अटल DEFINE_SPINLOCK(gem1clk_lock);
अटल DEFINE_SPINLOCK(canclk_lock);
अटल DEFINE_SPINLOCK(canmioclk_lock);
अटल DEFINE_SPINLOCK(dbgclk_lock);
अटल DEFINE_SPINLOCK(aperclk_lock);

अटल स्थिर अक्षर *स्थिर armpll_parents[] __initस्थिर = अणु"armpll_int",
	"ps_clk"पूर्ण;
अटल स्थिर अक्षर *स्थिर ddrpll_parents[] __initस्थिर = अणु"ddrpll_int",
	"ps_clk"पूर्ण;
अटल स्थिर अक्षर *स्थिर iopll_parents[] __initस्थिर = अणु"iopll_int",
	"ps_clk"पूर्ण;
अटल स्थिर अक्षर *gem0_mux_parents[] __initdata = अणु"gem0_div1", "dummy_name"पूर्ण;
अटल स्थिर अक्षर *gem1_mux_parents[] __initdata = अणु"gem1_div1", "dummy_name"पूर्ण;
अटल स्थिर अक्षर *स्थिर can0_mio_mux2_parents[] __initस्थिर = अणु"can0_gate",
	"can0_mio_mux"पूर्ण;
अटल स्थिर अक्षर *स्थिर can1_mio_mux2_parents[] __initस्थिर = अणु"can1_gate",
	"can1_mio_mux"पूर्ण;
अटल स्थिर अक्षर *dbg_emio_mux_parents[] __initdata = अणु"dbg_div",
	"dummy_name"पूर्ण;

अटल स्थिर अक्षर *स्थिर dbgtrc_emio_input_names[] __initस्थिर = अणु
	"trace_emio_clk"पूर्ण;
अटल स्थिर अक्षर *स्थिर gem0_emio_input_names[] __initस्थिर = अणु
	"gem0_emio_clk"पूर्ण;
अटल स्थिर अक्षर *स्थिर gem1_emio_input_names[] __initस्थिर = अणु
	"gem1_emio_clk"पूर्ण;
अटल स्थिर अक्षर *स्थिर swdt_ext_clk_input_names[] __initस्थिर = अणु
	"swdt_ext_clk"पूर्ण;

अटल व्योम __init zynq_clk_रेजिस्टर_fclk(क्रमागत zynq_clk fclk,
		स्थिर अक्षर *clk_name, व्योम __iomem *fclk_ctrl_reg,
		स्थिर अक्षर **parents, पूर्णांक enable)
अणु
	u32 enable_reg;
	अक्षर *mux_name;
	अक्षर *भाग0_name;
	अक्षर *भाग1_name;
	spinlock_t *fclk_lock;
	spinlock_t *fclk_gate_lock;
	व्योम __iomem *fclk_gate_reg = fclk_ctrl_reg + 8;

	fclk_lock = kदो_स्मृति(माप(*fclk_lock), GFP_KERNEL);
	अगर (!fclk_lock)
		जाओ err;
	fclk_gate_lock = kदो_स्मृति(माप(*fclk_gate_lock), GFP_KERNEL);
	अगर (!fclk_gate_lock)
		जाओ err_fclk_gate_lock;
	spin_lock_init(fclk_lock);
	spin_lock_init(fclk_gate_lock);

	mux_name = kaप्र_लिखो(GFP_KERNEL, "%s_mux", clk_name);
	अगर (!mux_name)
		जाओ err_mux_name;
	भाग0_name = kaप्र_लिखो(GFP_KERNEL, "%s_div0", clk_name);
	अगर (!भाग0_name)
		जाओ err_भाग0_name;
	भाग1_name = kaप्र_लिखो(GFP_KERNEL, "%s_div1", clk_name);
	अगर (!भाग1_name)
		जाओ err_भाग1_name;

	clk_रेजिस्टर_mux(शून्य, mux_name, parents, 4,
			CLK_SET_RATE_NO_REPARENT, fclk_ctrl_reg, 4, 2, 0,
			fclk_lock);

	clk_रेजिस्टर_भागider(शून्य, भाग0_name, mux_name,
			0, fclk_ctrl_reg, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, fclk_lock);

	clk_रेजिस्टर_भागider(शून्य, भाग1_name, भाग0_name,
			CLK_SET_RATE_PARENT, fclk_ctrl_reg, 20, 6,
			CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
			fclk_lock);

	clks[fclk] = clk_रेजिस्टर_gate(शून्य, clk_name,
			भाग1_name, CLK_SET_RATE_PARENT, fclk_gate_reg,
			0, CLK_GATE_SET_TO_DISABLE, fclk_gate_lock);
	enable_reg = पढ़ोl(fclk_gate_reg) & 1;
	अगर (enable && !enable_reg) अणु
		अगर (clk_prepare_enable(clks[fclk]))
			pr_warn("%s: FCLK%u enable failed\n", __func__,
					fclk - fclk0);
	पूर्ण
	kमुक्त(mux_name);
	kमुक्त(भाग0_name);
	kमुक्त(भाग1_name);

	वापस;

err_भाग1_name:
	kमुक्त(भाग0_name);
err_भाग0_name:
	kमुक्त(mux_name);
err_mux_name:
	kमुक्त(fclk_gate_lock);
err_fclk_gate_lock:
	kमुक्त(fclk_lock);
err:
	clks[fclk] = ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम __init zynq_clk_रेजिस्टर_periph_clk(क्रमागत zynq_clk clk0,
		क्रमागत zynq_clk clk1, स्थिर अक्षर *clk_name0,
		स्थिर अक्षर *clk_name1, व्योम __iomem *clk_ctrl,
		स्थिर अक्षर **parents, अचिन्हित पूर्णांक two_gates)
अणु
	अक्षर *mux_name;
	अक्षर *भाग_name;
	spinlock_t *lock;

	lock = kदो_स्मृति(माप(*lock), GFP_KERNEL);
	अगर (!lock)
		जाओ err;
	spin_lock_init(lock);

	mux_name = kaप्र_लिखो(GFP_KERNEL, "%s_mux", clk_name0);
	भाग_name = kaप्र_लिखो(GFP_KERNEL, "%s_div", clk_name0);

	clk_रेजिस्टर_mux(शून्य, mux_name, parents, 4,
			CLK_SET_RATE_NO_REPARENT, clk_ctrl, 4, 2, 0, lock);

	clk_रेजिस्टर_भागider(शून्य, भाग_name, mux_name, 0, clk_ctrl, 8, 6,
			CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO, lock);

	clks[clk0] = clk_रेजिस्टर_gate(शून्य, clk_name0, भाग_name,
			CLK_SET_RATE_PARENT, clk_ctrl, 0, 0, lock);
	अगर (two_gates)
		clks[clk1] = clk_रेजिस्टर_gate(शून्य, clk_name1, भाग_name,
				CLK_SET_RATE_PARENT, clk_ctrl, 1, 0, lock);

	kमुक्त(mux_name);
	kमुक्त(भाग_name);

	वापस;

err:
	clks[clk0] = ERR_PTR(-ENOMEM);
	अगर (two_gates)
		clks[clk1] = ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम __init zynq_clk_setup(काष्ठा device_node *np)
अणु
	पूर्णांक i;
	u32 पंचांगp;
	पूर्णांक ret;
	अक्षर *clk_name;
	अचिन्हित पूर्णांक fclk_enable = 0;
	स्थिर अक्षर *clk_output_name[clk_max];
	स्थिर अक्षर *cpu_parents[4];
	स्थिर अक्षर *periph_parents[4];
	स्थिर अक्षर *swdt_ext_clk_mux_parents[2];
	स्थिर अक्षर *can_mio_mux_parents[NUM_MIO_PINS];
	स्थिर अक्षर *dummy_nm = "dummy_name";

	pr_info("Zynq clock init\n");

	/* get घड़ी output names from DT */
	क्रम (i = 0; i < clk_max; i++) अणु
		अगर (of_property_पढ़ो_string_index(np, "clock-output-names",
				  i, &clk_output_name[i])) अणु
			pr_err("%s: clock output name not in DT\n", __func__);
			BUG();
		पूर्ण
	पूर्ण
	cpu_parents[0] = clk_output_name[armpll];
	cpu_parents[1] = clk_output_name[armpll];
	cpu_parents[2] = clk_output_name[ddrpll];
	cpu_parents[3] = clk_output_name[iopll];
	periph_parents[0] = clk_output_name[iopll];
	periph_parents[1] = clk_output_name[iopll];
	periph_parents[2] = clk_output_name[armpll];
	periph_parents[3] = clk_output_name[ddrpll];

	of_property_पढ़ो_u32(np, "fclk-enable", &fclk_enable);

	/* ps_clk */
	ret = of_property_पढ़ो_u32(np, "ps-clk-frequency", &पंचांगp);
	अगर (ret) अणु
		pr_warn("ps_clk frequency not specified, using 33 MHz.\n");
		पंचांगp = 33333333;
	पूर्ण
	ps_clk = clk_रेजिस्टर_fixed_rate(शून्य, "ps_clk", शून्य, 0, पंचांगp);

	/* PLLs */
	clk_रेजिस्टर_zynq_pll("armpll_int", "ps_clk", SLCR_ARMPLL_CTRL,
			SLCR_PLL_STATUS, 0, &armpll_lock);
	clks[armpll] = clk_रेजिस्टर_mux(शून्य, clk_output_name[armpll],
			armpll_parents, 2, CLK_SET_RATE_NO_REPARENT,
			SLCR_ARMPLL_CTRL, 4, 1, 0, &armpll_lock);

	clk_रेजिस्टर_zynq_pll("ddrpll_int", "ps_clk", SLCR_DDRPLL_CTRL,
			SLCR_PLL_STATUS, 1, &ddrpll_lock);
	clks[ddrpll] = clk_रेजिस्टर_mux(शून्य, clk_output_name[ddrpll],
			ddrpll_parents, 2, CLK_SET_RATE_NO_REPARENT,
			SLCR_DDRPLL_CTRL, 4, 1, 0, &ddrpll_lock);

	clk_रेजिस्टर_zynq_pll("iopll_int", "ps_clk", SLCR_IOPLL_CTRL,
			SLCR_PLL_STATUS, 2, &iopll_lock);
	clks[iopll] = clk_रेजिस्टर_mux(शून्य, clk_output_name[iopll],
			iopll_parents, 2, CLK_SET_RATE_NO_REPARENT,
			SLCR_IOPLL_CTRL, 4, 1, 0, &iopll_lock);

	/* CPU घड़ीs */
	पंचांगp = पढ़ोl(SLCR_621_TRUE) & 1;
	clk_रेजिस्टर_mux(शून्य, "cpu_mux", cpu_parents, 4,
			CLK_SET_RATE_NO_REPARENT, SLCR_ARM_CLK_CTRL, 4, 2, 0,
			&armclk_lock);
	clk_रेजिस्टर_भागider(शून्य, "cpu_div", "cpu_mux", 0,
			SLCR_ARM_CLK_CTRL, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &armclk_lock);

	clks[cpu_6or4x] = clk_रेजिस्टर_gate(शून्य, clk_output_name[cpu_6or4x],
			"cpu_div", CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
			SLCR_ARM_CLK_CTRL, 24, 0, &armclk_lock);

	clk_रेजिस्टर_fixed_factor(शून्य, "cpu_3or2x_div", "cpu_div", 0,
			1, 2);
	clks[cpu_3or2x] = clk_रेजिस्टर_gate(शून्य, clk_output_name[cpu_3or2x],
			"cpu_3or2x_div", CLK_IGNORE_UNUSED,
			SLCR_ARM_CLK_CTRL, 25, 0, &armclk_lock);

	clk_रेजिस्टर_fixed_factor(शून्य, "cpu_2x_div", "cpu_div", 0, 1,
			2 + पंचांगp);
	clks[cpu_2x] = clk_रेजिस्टर_gate(शून्य, clk_output_name[cpu_2x],
			"cpu_2x_div", CLK_IGNORE_UNUSED, SLCR_ARM_CLK_CTRL,
			26, 0, &armclk_lock);
	clk_prepare_enable(clks[cpu_2x]);

	clk_रेजिस्टर_fixed_factor(शून्य, "cpu_1x_div", "cpu_div", 0, 1,
			4 + 2 * पंचांगp);
	clks[cpu_1x] = clk_रेजिस्टर_gate(शून्य, clk_output_name[cpu_1x],
			"cpu_1x_div", CLK_IGNORE_UNUSED, SLCR_ARM_CLK_CTRL, 27,
			0, &armclk_lock);

	/* Timers */
	swdt_ext_clk_mux_parents[0] = clk_output_name[cpu_1x];
	क्रम (i = 0; i < ARRAY_SIZE(swdt_ext_clk_input_names); i++) अणु
		पूर्णांक idx = of_property_match_string(np, "clock-names",
				swdt_ext_clk_input_names[i]);
		अगर (idx >= 0)
			swdt_ext_clk_mux_parents[i + 1] =
				of_clk_get_parent_name(np, idx);
		अन्यथा
			swdt_ext_clk_mux_parents[i + 1] = dummy_nm;
	पूर्ण
	clks[swdt] = clk_रेजिस्टर_mux(शून्य, clk_output_name[swdt],
			swdt_ext_clk_mux_parents, 2, CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT, SLCR_SWDT_CLK_SEL, 0, 1, 0,
			&swdtclk_lock);

	/* DDR घड़ीs */
	clk_रेजिस्टर_भागider(शून्य, "ddr2x_div", "ddrpll", 0,
			SLCR_DDR_CLK_CTRL, 26, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &ddrclk_lock);
	clks[ddr2x] = clk_रेजिस्टर_gate(शून्य, clk_output_name[ddr2x],
			"ddr2x_div", 0, SLCR_DDR_CLK_CTRL, 1, 0, &ddrclk_lock);
	clk_prepare_enable(clks[ddr2x]);
	clk_रेजिस्टर_भागider(शून्य, "ddr3x_div", "ddrpll", 0,
			SLCR_DDR_CLK_CTRL, 20, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &ddrclk_lock);
	clks[ddr3x] = clk_रेजिस्टर_gate(शून्य, clk_output_name[ddr3x],
			"ddr3x_div", 0, SLCR_DDR_CLK_CTRL, 0, 0, &ddrclk_lock);
	clk_prepare_enable(clks[ddr3x]);

	clk_रेजिस्टर_भागider(शून्य, "dci_div0", "ddrpll", 0,
			SLCR_DCI_CLK_CTRL, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &dciclk_lock);
	clk_रेजिस्टर_भागider(शून्य, "dci_div1", "dci_div0",
			CLK_SET_RATE_PARENT, SLCR_DCI_CLK_CTRL, 20, 6,
			CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
			&dciclk_lock);
	clks[dci] = clk_रेजिस्टर_gate(शून्य, clk_output_name[dci], "dci_div1",
			CLK_SET_RATE_PARENT, SLCR_DCI_CLK_CTRL, 0, 0,
			&dciclk_lock);
	clk_prepare_enable(clks[dci]);

	/* Peripheral घड़ीs */
	क्रम (i = fclk0; i <= fclk3; i++) अणु
		पूर्णांक enable = !!(fclk_enable & BIT(i - fclk0));
		zynq_clk_रेजिस्टर_fclk(i, clk_output_name[i],
				SLCR_FPGA0_CLK_CTRL + 0x10 * (i - fclk0),
				periph_parents, enable);
	पूर्ण

	zynq_clk_रेजिस्टर_periph_clk(lqspi, 0, clk_output_name[lqspi], शून्य,
			SLCR_LQSPI_CLK_CTRL, periph_parents, 0);

	zynq_clk_रेजिस्टर_periph_clk(smc, 0, clk_output_name[smc], शून्य,
			SLCR_SMC_CLK_CTRL, periph_parents, 0);

	zynq_clk_रेजिस्टर_periph_clk(pcap, 0, clk_output_name[pcap], शून्य,
			SLCR_PCAP_CLK_CTRL, periph_parents, 0);

	zynq_clk_रेजिस्टर_periph_clk(sdio0, sdio1, clk_output_name[sdio0],
			clk_output_name[sdio1], SLCR_SDIO_CLK_CTRL,
			periph_parents, 1);

	zynq_clk_रेजिस्टर_periph_clk(uart0, uart1, clk_output_name[uart0],
			clk_output_name[uart1], SLCR_UART_CLK_CTRL,
			periph_parents, 1);

	zynq_clk_रेजिस्टर_periph_clk(spi0, spi1, clk_output_name[spi0],
			clk_output_name[spi1], SLCR_SPI_CLK_CTRL,
			periph_parents, 1);

	क्रम (i = 0; i < ARRAY_SIZE(gem0_emio_input_names); i++) अणु
		पूर्णांक idx = of_property_match_string(np, "clock-names",
				gem0_emio_input_names[i]);
		अगर (idx >= 0)
			gem0_mux_parents[i + 1] = of_clk_get_parent_name(np,
					idx);
	पूर्ण
	clk_रेजिस्टर_mux(शून्य, "gem0_mux", periph_parents, 4,
			CLK_SET_RATE_NO_REPARENT, SLCR_GEM0_CLK_CTRL, 4, 2, 0,
			&gem0clk_lock);
	clk_रेजिस्टर_भागider(शून्य, "gem0_div0", "gem0_mux", 0,
			SLCR_GEM0_CLK_CTRL, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &gem0clk_lock);
	clk_रेजिस्टर_भागider(शून्य, "gem0_div1", "gem0_div0",
			CLK_SET_RATE_PARENT, SLCR_GEM0_CLK_CTRL, 20, 6,
			CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
			&gem0clk_lock);
	clk_रेजिस्टर_mux(शून्य, "gem0_emio_mux", gem0_mux_parents, 2,
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SLCR_GEM0_CLK_CTRL, 6, 1, 0,
			&gem0clk_lock);
	clks[gem0] = clk_रेजिस्टर_gate(शून्य, clk_output_name[gem0],
			"gem0_emio_mux", CLK_SET_RATE_PARENT,
			SLCR_GEM0_CLK_CTRL, 0, 0, &gem0clk_lock);

	क्रम (i = 0; i < ARRAY_SIZE(gem1_emio_input_names); i++) अणु
		पूर्णांक idx = of_property_match_string(np, "clock-names",
				gem1_emio_input_names[i]);
		अगर (idx >= 0)
			gem1_mux_parents[i + 1] = of_clk_get_parent_name(np,
					idx);
	पूर्ण
	clk_रेजिस्टर_mux(शून्य, "gem1_mux", periph_parents, 4,
			CLK_SET_RATE_NO_REPARENT, SLCR_GEM1_CLK_CTRL, 4, 2, 0,
			&gem1clk_lock);
	clk_रेजिस्टर_भागider(शून्य, "gem1_div0", "gem1_mux", 0,
			SLCR_GEM1_CLK_CTRL, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &gem1clk_lock);
	clk_रेजिस्टर_भागider(शून्य, "gem1_div1", "gem1_div0",
			CLK_SET_RATE_PARENT, SLCR_GEM1_CLK_CTRL, 20, 6,
			CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
			&gem1clk_lock);
	clk_रेजिस्टर_mux(शून्य, "gem1_emio_mux", gem1_mux_parents, 2,
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SLCR_GEM1_CLK_CTRL, 6, 1, 0,
			&gem1clk_lock);
	clks[gem1] = clk_रेजिस्टर_gate(शून्य, clk_output_name[gem1],
			"gem1_emio_mux", CLK_SET_RATE_PARENT,
			SLCR_GEM1_CLK_CTRL, 0, 0, &gem1clk_lock);

	पंचांगp = म_माप("mio_clk_00x");
	clk_name = kदो_स्मृति(पंचांगp, GFP_KERNEL);
	क्रम (i = 0; i < NUM_MIO_PINS; i++) अणु
		पूर्णांक idx;

		snम_लिखो(clk_name, पंचांगp, "mio_clk_%2.2d", i);
		idx = of_property_match_string(np, "clock-names", clk_name);
		अगर (idx >= 0)
			can_mio_mux_parents[i] = of_clk_get_parent_name(np,
						idx);
		अन्यथा
			can_mio_mux_parents[i] = dummy_nm;
	पूर्ण
	kमुक्त(clk_name);
	clk_रेजिस्टर_mux(शून्य, "can_mux", periph_parents, 4,
			CLK_SET_RATE_NO_REPARENT, SLCR_CAN_CLK_CTRL, 4, 2, 0,
			&canclk_lock);
	clk_रेजिस्टर_भागider(शून्य, "can_div0", "can_mux", 0,
			SLCR_CAN_CLK_CTRL, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &canclk_lock);
	clk_रेजिस्टर_भागider(शून्य, "can_div1", "can_div0",
			CLK_SET_RATE_PARENT, SLCR_CAN_CLK_CTRL, 20, 6,
			CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
			&canclk_lock);
	clk_रेजिस्टर_gate(शून्य, "can0_gate", "can_div1",
			CLK_SET_RATE_PARENT, SLCR_CAN_CLK_CTRL, 0, 0,
			&canclk_lock);
	clk_रेजिस्टर_gate(शून्य, "can1_gate", "can_div1",
			CLK_SET_RATE_PARENT, SLCR_CAN_CLK_CTRL, 1, 0,
			&canclk_lock);
	clk_रेजिस्टर_mux(शून्य, "can0_mio_mux",
			can_mio_mux_parents, 54, CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT, SLCR_CAN_MIOCLK_CTRL, 0, 6, 0,
			&canmioclk_lock);
	clk_रेजिस्टर_mux(शून्य, "can1_mio_mux",
			can_mio_mux_parents, 54, CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT, SLCR_CAN_MIOCLK_CTRL, 16, 6,
			0, &canmioclk_lock);
	clks[can0] = clk_रेजिस्टर_mux(शून्य, clk_output_name[can0],
			can0_mio_mux2_parents, 2, CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT, SLCR_CAN_MIOCLK_CTRL, 6, 1, 0,
			&canmioclk_lock);
	clks[can1] = clk_रेजिस्टर_mux(शून्य, clk_output_name[can1],
			can1_mio_mux2_parents, 2, CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT, SLCR_CAN_MIOCLK_CTRL, 22, 1,
			0, &canmioclk_lock);

	क्रम (i = 0; i < ARRAY_SIZE(dbgtrc_emio_input_names); i++) अणु
		पूर्णांक idx = of_property_match_string(np, "clock-names",
				dbgtrc_emio_input_names[i]);
		अगर (idx >= 0)
			dbg_emio_mux_parents[i + 1] = of_clk_get_parent_name(np,
					idx);
	पूर्ण
	clk_रेजिस्टर_mux(शून्य, "dbg_mux", periph_parents, 4,
			CLK_SET_RATE_NO_REPARENT, SLCR_DBG_CLK_CTRL, 4, 2, 0,
			&dbgclk_lock);
	clk_रेजिस्टर_भागider(शून्य, "dbg_div", "dbg_mux", 0,
			SLCR_DBG_CLK_CTRL, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &dbgclk_lock);
	clk_रेजिस्टर_mux(शून्य, "dbg_emio_mux", dbg_emio_mux_parents, 2,
			CLK_SET_RATE_NO_REPARENT, SLCR_DBG_CLK_CTRL, 6, 1, 0,
			&dbgclk_lock);
	clks[dbg_trc] = clk_रेजिस्टर_gate(शून्य, clk_output_name[dbg_trc],
			"dbg_emio_mux", CLK_SET_RATE_PARENT, SLCR_DBG_CLK_CTRL,
			0, 0, &dbgclk_lock);
	clks[dbg_apb] = clk_रेजिस्टर_gate(शून्य, clk_output_name[dbg_apb],
			clk_output_name[cpu_1x], 0, SLCR_DBG_CLK_CTRL, 1, 0,
			&dbgclk_lock);

	/* leave debug घड़ीs in the state the bootloader set them up to */
	पंचांगp = पढ़ोl(SLCR_DBG_CLK_CTRL);
	अगर (पंचांगp & DBG_CLK_CTRL_CLKACT_TRC)
		अगर (clk_prepare_enable(clks[dbg_trc]))
			pr_warn("%s: trace clk enable failed\n", __func__);
	अगर (पंचांगp & DBG_CLK_CTRL_CPU_1XCLKACT)
		अगर (clk_prepare_enable(clks[dbg_apb]))
			pr_warn("%s: debug APB clk enable failed\n", __func__);

	/* One gated घड़ी क्रम all APER घड़ीs. */
	clks[dma] = clk_रेजिस्टर_gate(शून्य, clk_output_name[dma],
			clk_output_name[cpu_2x], 0, SLCR_APER_CLK_CTRL, 0, 0,
			&aperclk_lock);
	clks[usb0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[usb0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 2, 0,
			&aperclk_lock);
	clks[usb1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[usb1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 3, 0,
			&aperclk_lock);
	clks[gem0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[gem0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 6, 0,
			&aperclk_lock);
	clks[gem1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[gem1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 7, 0,
			&aperclk_lock);
	clks[sdio0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[sdio0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 10, 0,
			&aperclk_lock);
	clks[sdio1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[sdio1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 11, 0,
			&aperclk_lock);
	clks[spi0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[spi0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 14, 0,
			&aperclk_lock);
	clks[spi1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[spi1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 15, 0,
			&aperclk_lock);
	clks[can0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[can0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 16, 0,
			&aperclk_lock);
	clks[can1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[can1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 17, 0,
			&aperclk_lock);
	clks[i2c0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[i2c0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 18, 0,
			&aperclk_lock);
	clks[i2c1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[i2c1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 19, 0,
			&aperclk_lock);
	clks[uart0_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[uart0_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 20, 0,
			&aperclk_lock);
	clks[uart1_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[uart1_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 21, 0,
			&aperclk_lock);
	clks[gpio_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[gpio_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 22, 0,
			&aperclk_lock);
	clks[lqspi_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[lqspi_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 23, 0,
			&aperclk_lock);
	clks[smc_aper] = clk_रेजिस्टर_gate(शून्य, clk_output_name[smc_aper],
			clk_output_name[cpu_1x], 0, SLCR_APER_CLK_CTRL, 24, 0,
			&aperclk_lock);

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++) अणु
		अगर (IS_ERR(clks[i])) अणु
			pr_err("Zynq clk %d: register failed with %ld\n",
			       i, PTR_ERR(clks[i]));
			BUG();
		पूर्ण
	पूर्ण

	clk_data.clks = clks;
	clk_data.clk_num = ARRAY_SIZE(clks);
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);
पूर्ण

CLK_OF_DECLARE(zynq_clkc, "xlnx,ps7-clkc", zynq_clk_setup);

व्योम __init zynq_घड़ी_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा device_node *slcr;
	काष्ठा resource res;

	np = of_find_compatible_node(शून्य, शून्य, "xlnx,ps7-clkc");
	अगर (!np) अणु
		pr_err("%s: clkc node not found\n", __func__);
		जाओ np_err;
	पूर्ण

	अगर (of_address_to_resource(np, 0, &res)) अणु
		pr_err("%pOFn: failed to get resource\n", np);
		जाओ np_err;
	पूर्ण

	slcr = of_get_parent(np);

	अगर (slcr->data) अणु
		zynq_clkc_base = (__क्रमce व्योम __iomem *)slcr->data + res.start;
	पूर्ण अन्यथा अणु
		pr_err("%pOFn: Unable to get I/O memory\n", np);
		of_node_put(slcr);
		जाओ np_err;
	पूर्ण

	pr_info("%s: clkc starts at %p\n", __func__, zynq_clkc_base);

	of_node_put(slcr);
	of_node_put(np);

	वापस;

np_err:
	of_node_put(np);
	BUG();
पूर्ण
