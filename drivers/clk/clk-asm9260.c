<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Oleksij Rempel <linux@rempel-privat.de>.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <dt-bindings/घड़ी/alphascale,यंत्र9260.h>

#घोषणा HW_AHBCLKCTRL0		0x0020
#घोषणा HW_AHBCLKCTRL1		0x0030
#घोषणा HW_SYSPLLCTRL		0x0100
#घोषणा HW_MAINCLKSEL		0x0120
#घोषणा HW_MAINCLKUEN		0x0124
#घोषणा HW_UARTCLKSEL		0x0128
#घोषणा HW_UARTCLKUEN		0x012c
#घोषणा HW_I2S0CLKSEL		0x0130
#घोषणा HW_I2S0CLKUEN		0x0134
#घोषणा HW_I2S1CLKSEL		0x0138
#घोषणा HW_I2S1CLKUEN		0x013c
#घोषणा HW_WDTCLKSEL		0x0160
#घोषणा HW_WDTCLKUEN		0x0164
#घोषणा HW_CLKOUTCLKSEL		0x0170
#घोषणा HW_CLKOUTCLKUEN		0x0174
#घोषणा HW_CPUCLKDIV		0x017c
#घोषणा HW_SYSAHBCLKDIV		0x0180
#घोषणा HW_I2S0MCLKDIV		0x0190
#घोषणा HW_I2S0SCLKDIV		0x0194
#घोषणा HW_I2S1MCLKDIV		0x0188
#घोषणा HW_I2S1SCLKDIV		0x018c
#घोषणा HW_UART0CLKDIV		0x0198
#घोषणा HW_UART1CLKDIV		0x019c
#घोषणा HW_UART2CLKDIV		0x01a0
#घोषणा HW_UART3CLKDIV		0x01a4
#घोषणा HW_UART4CLKDIV		0x01a8
#घोषणा HW_UART5CLKDIV		0x01ac
#घोषणा HW_UART6CLKDIV		0x01b0
#घोषणा HW_UART7CLKDIV		0x01b4
#घोषणा HW_UART8CLKDIV		0x01b8
#घोषणा HW_UART9CLKDIV		0x01bc
#घोषणा HW_SPI0CLKDIV		0x01c0
#घोषणा HW_SPI1CLKDIV		0x01c4
#घोषणा HW_QUADSPICLKDIV	0x01c8
#घोषणा HW_SSP0CLKDIV		0x01d0
#घोषणा HW_न_अंकDCLKDIV		0x01d4
#घोषणा HW_TRACECLKDIV		0x01e0
#घोषणा HW_CAMMCLKDIV		0x01e8
#घोषणा HW_WDTCLKDIV		0x01ec
#घोषणा HW_CLKOUTCLKDIV		0x01f4
#घोषणा HW_MACCLKDIV		0x01f8
#घोषणा HW_LCDCLKDIV		0x01fc
#घोषणा HW_ADCANACLKDIV		0x0200

अटल काष्ठा clk_hw_onecell_data *clk_data;
अटल DEFINE_SPINLOCK(यंत्र9260_clk_lock);

काष्ठा यंत्र9260_भाग_clk अणु
	अचिन्हित पूर्णांक idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	u32 reg;
पूर्ण;

काष्ठा यंत्र9260_gate_data अणु
	अचिन्हित पूर्णांक idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	u32 reg;
	u8 bit_idx;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा यंत्र9260_mux_घड़ी अणु
	u8			mask;
	u32			*table;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		**parent_names;
	u8			num_parents;
	अचिन्हित दीर्घ		offset;
	अचिन्हित दीर्घ		flags;
पूर्ण;

अटल व्योम __iomem *base;

अटल स्थिर काष्ठा यंत्र9260_भाग_clk यंत्र9260_भाग_clks[] __initस्थिर = अणु
	अणु CLKID_SYS_CPU,	"cpu_div", "main_gate", HW_CPUCLKDIV पूर्ण,
	अणु CLKID_SYS_AHB,	"ahb_div", "cpu_div", HW_SYSAHBCLKDIV पूर्ण,

	/* i2s has two deviders: one क्रम only बाह्यal mclk and पूर्णांकernal
	 * devider क्रम all clks. */
	अणु CLKID_SYS_I2S0M,	"i2s0m_div", "i2s0_mclk",  HW_I2S0MCLKDIV पूर्ण,
	अणु CLKID_SYS_I2S1M,	"i2s1m_div", "i2s1_mclk",  HW_I2S1MCLKDIV पूर्ण,
	अणु CLKID_SYS_I2S0S,	"i2s0s_div", "i2s0_gate",  HW_I2S0SCLKDIV पूर्ण,
	अणु CLKID_SYS_I2S1S,	"i2s1s_div", "i2s0_gate",  HW_I2S1SCLKDIV पूर्ण,

	अणु CLKID_SYS_UART0,	"uart0_div", "uart_gate", HW_UART0CLKDIV पूर्ण,
	अणु CLKID_SYS_UART1,	"uart1_div", "uart_gate", HW_UART1CLKDIV पूर्ण,
	अणु CLKID_SYS_UART2,	"uart2_div", "uart_gate", HW_UART2CLKDIV पूर्ण,
	अणु CLKID_SYS_UART3,	"uart3_div", "uart_gate", HW_UART3CLKDIV पूर्ण,
	अणु CLKID_SYS_UART4,	"uart4_div", "uart_gate", HW_UART4CLKDIV पूर्ण,
	अणु CLKID_SYS_UART5,	"uart5_div", "uart_gate", HW_UART5CLKDIV पूर्ण,
	अणु CLKID_SYS_UART6,	"uart6_div", "uart_gate", HW_UART6CLKDIV पूर्ण,
	अणु CLKID_SYS_UART7,	"uart7_div", "uart_gate", HW_UART7CLKDIV पूर्ण,
	अणु CLKID_SYS_UART8,	"uart8_div", "uart_gate", HW_UART8CLKDIV पूर्ण,
	अणु CLKID_SYS_UART9,	"uart9_div", "uart_gate", HW_UART9CLKDIV पूर्ण,

	अणु CLKID_SYS_SPI0,	"spi0_div",	"main_gate", HW_SPI0CLKDIV पूर्ण,
	अणु CLKID_SYS_SPI1,	"spi1_div",	"main_gate", HW_SPI1CLKDIV पूर्ण,
	अणु CLKID_SYS_QUADSPI,	"quadspi_div",	"main_gate", HW_QUADSPICLKDIV पूर्ण,
	अणु CLKID_SYS_SSP0,	"ssp0_div",	"main_gate", HW_SSP0CLKDIV पूर्ण,
	अणु CLKID_SYS_न_अंकD,	"nand_div",	"main_gate", HW_न_अंकDCLKDIV पूर्ण,
	अणु CLKID_SYS_TRACE,	"trace_div",	"main_gate", HW_TRACECLKDIV पूर्ण,
	अणु CLKID_SYS_CAMM,	"camm_div",	"main_gate", HW_CAMMCLKDIV पूर्ण,
	अणु CLKID_SYS_MAC,	"mac_div",	"main_gate", HW_MACCLKDIV पूर्ण,
	अणु CLKID_SYS_LCD,	"lcd_div",	"main_gate", HW_LCDCLKDIV पूर्ण,
	अणु CLKID_SYS_ADCANA,	"adcana_div",	"main_gate", HW_ADCANACLKDIV पूर्ण,

	अणु CLKID_SYS_WDT,	"wdt_div",	"wdt_gate",    HW_WDTCLKDIV पूर्ण,
	अणु CLKID_SYS_CLKOUT,	"clkout_div",	"clkout_gate", HW_CLKOUTCLKDIV पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा यंत्र9260_gate_data यंत्र9260_mux_gates[] __initस्थिर = अणु
	अणु 0, "main_gate",	"main_mux",	HW_MAINCLKUEN,	0 पूर्ण,
	अणु 0, "uart_gate",	"uart_mux",	HW_UARTCLKUEN,	0 पूर्ण,
	अणु 0, "i2s0_gate",	"i2s0_mux",	HW_I2S0CLKUEN,	0 पूर्ण,
	अणु 0, "i2s1_gate",	"i2s1_mux",	HW_I2S1CLKUEN,	0 पूर्ण,
	अणु 0, "wdt_gate",	"wdt_mux",	HW_WDTCLKUEN,	0 पूर्ण,
	अणु 0, "clkout_gate",	"clkout_mux",	HW_CLKOUTCLKUEN, 0 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा यंत्र9260_gate_data यंत्र9260_ahb_gates[] __initस्थिर = अणु
	/* ahb gates */
	अणु CLKID_AHB_ROM,	"rom",		"ahb_div",
		HW_AHBCLKCTRL0,	1, CLK_IGNORE_UNUSEDपूर्ण,
	अणु CLKID_AHB_RAM,	"ram",		"ahb_div",
		HW_AHBCLKCTRL0,	2, CLK_IGNORE_UNUSEDपूर्ण,
	अणु CLKID_AHB_GPIO,	"gpio",		"ahb_div",
		HW_AHBCLKCTRL0,	4 पूर्ण,
	अणु CLKID_AHB_MAC,	"mac",		"ahb_div",
		HW_AHBCLKCTRL0,	5 पूर्ण,
	अणु CLKID_AHB_EMI,	"emi",		"ahb_div",
		HW_AHBCLKCTRL0,	6, CLK_IGNORE_UNUSEDपूर्ण,
	अणु CLKID_AHB_USB0,	"usb0",		"ahb_div",
		HW_AHBCLKCTRL0,	7 पूर्ण,
	अणु CLKID_AHB_USB1,	"usb1",		"ahb_div",
		HW_AHBCLKCTRL0,	8 पूर्ण,
	अणु CLKID_AHB_DMA0,	"dma0",		"ahb_div",
		HW_AHBCLKCTRL0,	9 पूर्ण,
	अणु CLKID_AHB_DMA1,	"dma1",		"ahb_div",
		HW_AHBCLKCTRL0,	10 पूर्ण,
	अणु CLKID_AHB_UART0,	"uart0",	"ahb_div",
		HW_AHBCLKCTRL0,	11 पूर्ण,
	अणु CLKID_AHB_UART1,	"uart1",	"ahb_div",
		HW_AHBCLKCTRL0,	12 पूर्ण,
	अणु CLKID_AHB_UART2,	"uart2",	"ahb_div",
		HW_AHBCLKCTRL0,	13 पूर्ण,
	अणु CLKID_AHB_UART3,	"uart3",	"ahb_div",
		HW_AHBCLKCTRL0,	14 पूर्ण,
	अणु CLKID_AHB_UART4,	"uart4",	"ahb_div",
		HW_AHBCLKCTRL0,	15 पूर्ण,
	अणु CLKID_AHB_UART5,	"uart5",	"ahb_div",
		HW_AHBCLKCTRL0,	16 पूर्ण,
	अणु CLKID_AHB_UART6,	"uart6",	"ahb_div",
		HW_AHBCLKCTRL0,	17 पूर्ण,
	अणु CLKID_AHB_UART7,	"uart7",	"ahb_div",
		HW_AHBCLKCTRL0,	18 पूर्ण,
	अणु CLKID_AHB_UART8,	"uart8",	"ahb_div",
		HW_AHBCLKCTRL0,	19 पूर्ण,
	अणु CLKID_AHB_UART9,	"uart9",	"ahb_div",
		HW_AHBCLKCTRL0,	20 पूर्ण,
	अणु CLKID_AHB_I2S0,	"i2s0",		"ahb_div",
		HW_AHBCLKCTRL0,	21 पूर्ण,
	अणु CLKID_AHB_I2C0,	"i2c0",		"ahb_div",
		HW_AHBCLKCTRL0,	22 पूर्ण,
	अणु CLKID_AHB_I2C1,	"i2c1",		"ahb_div",
		HW_AHBCLKCTRL0,	23 पूर्ण,
	अणु CLKID_AHB_SSP0,	"ssp0",		"ahb_div",
		HW_AHBCLKCTRL0,	24 पूर्ण,
	अणु CLKID_AHB_IOCONFIG,	"ioconf",	"ahb_div",
		HW_AHBCLKCTRL0,	25 पूर्ण,
	अणु CLKID_AHB_WDT,	"wdt",		"ahb_div",
		HW_AHBCLKCTRL0,	26 पूर्ण,
	अणु CLKID_AHB_CAN0,	"can0",		"ahb_div",
		HW_AHBCLKCTRL0,	27 पूर्ण,
	अणु CLKID_AHB_CAN1,	"can1",		"ahb_div",
		HW_AHBCLKCTRL0,	28 पूर्ण,
	अणु CLKID_AHB_MPWM,	"mpwm",		"ahb_div",
		HW_AHBCLKCTRL0,	29 पूर्ण,
	अणु CLKID_AHB_SPI0,	"spi0",		"ahb_div",
		HW_AHBCLKCTRL0,	30 पूर्ण,
	अणु CLKID_AHB_SPI1,	"spi1",		"ahb_div",
		HW_AHBCLKCTRL0,	31 पूर्ण,

	अणु CLKID_AHB_QEI,	"qei",		"ahb_div",
		HW_AHBCLKCTRL1,	0 पूर्ण,
	अणु CLKID_AHB_QUADSPI0,	"quadspi0",	"ahb_div",
		HW_AHBCLKCTRL1,	1 पूर्ण,
	अणु CLKID_AHB_CAMIF,	"capmif",	"ahb_div",
		HW_AHBCLKCTRL1,	2 पूर्ण,
	अणु CLKID_AHB_LCDIF,	"lcdif",	"ahb_div",
		HW_AHBCLKCTRL1,	3 पूर्ण,
	अणु CLKID_AHB_TIMER0,	"timer0",	"ahb_div",
		HW_AHBCLKCTRL1,	4 पूर्ण,
	अणु CLKID_AHB_TIMER1,	"timer1",	"ahb_div",
		HW_AHBCLKCTRL1,	5 पूर्ण,
	अणु CLKID_AHB_TIMER2,	"timer2",	"ahb_div",
		HW_AHBCLKCTRL1,	6 पूर्ण,
	अणु CLKID_AHB_TIMER3,	"timer3",	"ahb_div",
		HW_AHBCLKCTRL1,	7 पूर्ण,
	अणु CLKID_AHB_IRQ,	"irq",		"ahb_div",
		HW_AHBCLKCTRL1,	8, CLK_IGNORE_UNUSEDपूर्ण,
	अणु CLKID_AHB_RTC,	"rtc",		"ahb_div",
		HW_AHBCLKCTRL1,	9 पूर्ण,
	अणु CLKID_AHB_न_अंकD,	"nand",		"ahb_div",
		HW_AHBCLKCTRL1,	10 पूर्ण,
	अणु CLKID_AHB_ADC0,	"adc0",		"ahb_div",
		HW_AHBCLKCTRL1,	11 पूर्ण,
	अणु CLKID_AHB_LED,	"led",		"ahb_div",
		HW_AHBCLKCTRL1,	12 पूर्ण,
	अणु CLKID_AHB_DAC0,	"dac0",		"ahb_div",
		HW_AHBCLKCTRL1,	13 पूर्ण,
	अणु CLKID_AHB_LCD,	"lcd",		"ahb_div",
		HW_AHBCLKCTRL1,	14 पूर्ण,
	अणु CLKID_AHB_I2S1,	"i2s1",		"ahb_div",
		HW_AHBCLKCTRL1,	15 पूर्ण,
	अणु CLKID_AHB_MAC1,	"mac1",		"ahb_div",
		HW_AHBCLKCTRL1,	16 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर __initdata *मुख्य_mux_p[] =   अणु शून्य, शून्य पूर्ण;
अटल स्थिर अक्षर __initdata *i2s0_mux_p[] =   अणु शून्य, शून्य, "i2s0m_div"पूर्ण;
अटल स्थिर अक्षर __initdata *i2s1_mux_p[] =   अणु शून्य, शून्य, "i2s1m_div"पूर्ण;
अटल स्थिर अक्षर __initdata *clkout_mux_p[] = अणु शून्य, शून्य, "rtc"पूर्ण;
अटल u32 three_mux_table[] = अणु0, 1, 3पूर्ण;

अटल काष्ठा यंत्र9260_mux_घड़ी यंत्र9260_mux_clks[] __initdata = अणु
	अणु 1, three_mux_table, "main_mux",	मुख्य_mux_p,
		ARRAY_SIZE(मुख्य_mux_p), HW_MAINCLKSEL, पूर्ण,
	अणु 1, three_mux_table, "uart_mux",	मुख्य_mux_p,
		ARRAY_SIZE(मुख्य_mux_p), HW_UARTCLKSEL, पूर्ण,
	अणु 1, three_mux_table, "wdt_mux",	मुख्य_mux_p,
		ARRAY_SIZE(मुख्य_mux_p), HW_WDTCLKSEL, पूर्ण,
	अणु 3, three_mux_table, "i2s0_mux",	i2s0_mux_p,
		ARRAY_SIZE(i2s0_mux_p), HW_I2S0CLKSEL, पूर्ण,
	अणु 3, three_mux_table, "i2s1_mux",	i2s1_mux_p,
		ARRAY_SIZE(i2s1_mux_p), HW_I2S1CLKSEL, पूर्ण,
	अणु 3, three_mux_table, "clkout_mux",	clkout_mux_p,
		ARRAY_SIZE(clkout_mux_p), HW_CLKOUTCLKSEL, पूर्ण,
पूर्ण;

अटल व्योम __init यंत्र9260_acc_init(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_hw **hws;
	स्थिर अक्षर *ref_clk, *pll_clk = "pll";
	u32 rate;
	पूर्णांक n;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, MAX_CLKS), GFP_KERNEL);
	अगर (!clk_data)
		वापस;
	clk_data->num = MAX_CLKS;
	hws = clk_data->hws;

	base = of_io_request_and_map(np, 0, np->name);
	अगर (IS_ERR(base))
		panic("%pOFn: unable to map resource", np);

	/* रेजिस्टर pll */
	rate = (ioपढ़ो32(base + HW_SYSPLLCTRL) & 0xffff) * 1000000;

	/* TODO: Convert to DT parent scheme */
	ref_clk = of_clk_get_parent_name(np, 0);
	hw = __clk_hw_रेजिस्टर_fixed_rate(शून्य, शून्य, pll_clk,
			ref_clk, शून्य, शून्य, 0, rate, 0,
			CLK_FIXED_RATE_PARENT_ACCURACY);

	अगर (IS_ERR(hw))
		panic("%pOFn: can't register REFCLK. Check DT!", np);

	क्रम (n = 0; n < ARRAY_SIZE(यंत्र9260_mux_clks); n++) अणु
		स्थिर काष्ठा यंत्र9260_mux_घड़ी *mc = &यंत्र9260_mux_clks[n];

		mc->parent_names[0] = ref_clk;
		mc->parent_names[1] = pll_clk;
		hw = clk_hw_रेजिस्टर_mux_table(शून्य, mc->name, mc->parent_names,
				mc->num_parents, mc->flags, base + mc->offset,
				0, mc->mask, 0, mc->table, &यंत्र9260_clk_lock);
	पूर्ण

	/* घड़ी mux gate cells */
	क्रम (n = 0; n < ARRAY_SIZE(यंत्र9260_mux_gates); n++) अणु
		स्थिर काष्ठा यंत्र9260_gate_data *gd = &यंत्र9260_mux_gates[n];

		hw = clk_hw_रेजिस्टर_gate(शून्य, gd->name,
			gd->parent_name, gd->flags | CLK_SET_RATE_PARENT,
			base + gd->reg, gd->bit_idx, 0, &यंत्र9260_clk_lock);
	पूर्ण

	/* घड़ी भाग cells */
	क्रम (n = 0; n < ARRAY_SIZE(यंत्र9260_भाग_clks); n++) अणु
		स्थिर काष्ठा यंत्र9260_भाग_clk *dc = &यंत्र9260_भाग_clks[n];

		hws[dc->idx] = clk_hw_रेजिस्टर_भागider(शून्य, dc->name,
				dc->parent_name, CLK_SET_RATE_PARENT,
				base + dc->reg, 0, 8, CLK_DIVIDER_ONE_BASED,
				&यंत्र9260_clk_lock);
	पूर्ण

	/* घड़ी ahb gate cells */
	क्रम (n = 0; n < ARRAY_SIZE(यंत्र9260_ahb_gates); n++) अणु
		स्थिर काष्ठा यंत्र9260_gate_data *gd = &यंत्र9260_ahb_gates[n];

		hws[gd->idx] = clk_hw_रेजिस्टर_gate(शून्य, gd->name,
				gd->parent_name, gd->flags, base + gd->reg,
				gd->bit_idx, 0, &यंत्र9260_clk_lock);
	पूर्ण

	/* check क्रम errors on leaf घड़ीs */
	क्रम (n = 0; n < MAX_CLKS; n++) अणु
		अगर (!IS_ERR(hws[n]))
			जारी;

		pr_err("%pOF: Unable to register leaf clock %d\n",
				np, n);
		जाओ fail;
	पूर्ण

	/* रेजिस्टर clk-provider */
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);
	वापस;
fail:
	iounmap(base);
पूर्ण
CLK_OF_DECLARE(यंत्र9260_acc, "alphascale,asm9260-clock-controller",
		यंत्र9260_acc_init);
