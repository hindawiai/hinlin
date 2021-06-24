<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Nuvoton NPCM7xx Clock Generator
 * All the घड़ीs are initialized by the bootloader, so this driver allow only
 * पढ़ोing of current settings directly from the hardware.
 *
 * Copyright (C) 2018 Nuvoton Technologies tali.perry@nuvoton.com
 */

#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/bitfield.h>

#समावेश <dt-bindings/घड़ी/nuvoton,npcm7xx-घड़ी.h>

काष्ठा npcm7xx_clk_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*pllcon;
	u8		flags;
पूर्ण;

#घोषणा to_npcm7xx_clk_pll(_hw) container_of(_hw, काष्ठा npcm7xx_clk_pll, hw)

#घोषणा PLLCON_LOKI	BIT(31)
#घोषणा PLLCON_LOKS	BIT(30)
#घोषणा PLLCON_FBDV	GENMASK(27, 16)
#घोषणा PLLCON_OTDV2	GENMASK(15, 13)
#घोषणा PLLCON_PWDEN	BIT(12)
#घोषणा PLLCON_OTDV1	GENMASK(10, 8)
#घोषणा PLLCON_INDV	GENMASK(5, 0)

अटल अचिन्हित दीर्घ npcm7xx_clk_pll_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा npcm7xx_clk_pll *pll = to_npcm7xx_clk_pll(hw);
	अचिन्हित दीर्घ fbdv, indv, otdv1, otdv2;
	अचिन्हित पूर्णांक val;
	u64 ret;

	अगर (parent_rate == 0) अणु
		pr_err("%s: parent rate is zero", __func__);
		वापस 0;
	पूर्ण

	val = पढ़ोl_relaxed(pll->pllcon);

	indv = FIELD_GET(PLLCON_INDV, val);
	fbdv = FIELD_GET(PLLCON_FBDV, val);
	otdv1 = FIELD_GET(PLLCON_OTDV1, val);
	otdv2 = FIELD_GET(PLLCON_OTDV2, val);

	ret = (u64)parent_rate * fbdv;
	करो_भाग(ret, indv * otdv1 * otdv2);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops npcm7xx_clk_pll_ops = अणु
	.recalc_rate = npcm7xx_clk_pll_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *
npcm7xx_clk_रेजिस्टर_pll(व्योम __iomem *pllcon, स्थिर अक्षर *name,
			 स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags)
अणु
	काष्ठा npcm7xx_clk_pll *pll;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pr_debug("%s reg, name=%s, p=%s\n", __func__, name, parent_name);

	init.name = name;
	init.ops = &npcm7xx_clk_pll_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = flags;

	pll->pllcon = pllcon;
	pll->hw.init = &init;

	hw = &pll->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

#घोषणा NPCM7XX_CLKEN1          (0x00)
#घोषणा NPCM7XX_CLKEN2          (0x28)
#घोषणा NPCM7XX_CLKEN3          (0x30)
#घोषणा NPCM7XX_CLKSEL          (0x04)
#घोषणा NPCM7XX_CLKDIV1         (0x08)
#घोषणा NPCM7XX_CLKDIV2         (0x2C)
#घोषणा NPCM7XX_CLKDIV3         (0x58)
#घोषणा NPCM7XX_PLLCON0         (0x0C)
#घोषणा NPCM7XX_PLLCON1         (0x10)
#घोषणा NPCM7XX_PLLCON2         (0x54)
#घोषणा NPCM7XX_SWRSTR          (0x14)
#घोषणा NPCM7XX_IRQWAKECON      (0x18)
#घोषणा NPCM7XX_IRQWAKEFLAG     (0x1C)
#घोषणा NPCM7XX_IPSRST1         (0x20)
#घोषणा NPCM7XX_IPSRST2         (0x24)
#घोषणा NPCM7XX_IPSRST3         (0x34)
#घोषणा NPCM7XX_WD0RCR          (0x38)
#घोषणा NPCM7XX_WD1RCR          (0x3C)
#घोषणा NPCM7XX_WD2RCR          (0x40)
#घोषणा NPCM7XX_SWRSTC1         (0x44)
#घोषणा NPCM7XX_SWRSTC2         (0x48)
#घोषणा NPCM7XX_SWRSTC3         (0x4C)
#घोषणा NPCM7XX_SWRSTC4         (0x50)
#घोषणा NPCM7XX_CORSTC          (0x5C)
#घोषणा NPCM7XX_PLLCONG         (0x60)
#घोषणा NPCM7XX_AHBCKFI         (0x64)
#घोषणा NPCM7XX_SECCNT          (0x68)
#घोषणा NPCM7XX_CNTR25M         (0x6C)

काष्ठा npcm7xx_clk_gate_data अणु
	u32 reg;
	u8 bit_idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	/*
	 * If this घड़ी is exported via DT, set onecell_idx to स्थिरant
	 * defined in include/dt-bindings/घड़ी/nuvoton, NPCM7XX-घड़ी.h क्रम
	 * this specअगरic घड़ी.  Otherwise, set to -1.
	 */
	पूर्णांक onecell_idx;
पूर्ण;

काष्ठा npcm7xx_clk_mux_data अणु
	u8 shअगरt;
	u8 mask;
	u32 *table;
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	u8 num_parents;
	अचिन्हित दीर्घ flags;
	/*
	 * If this घड़ी is exported via DT, set onecell_idx to स्थिरant
	 * defined in include/dt-bindings/घड़ी/nuvoton, NPCM7XX-घड़ी.h क्रम
	 * this specअगरic घड़ी.  Otherwise, set to -1.
	 */
	पूर्णांक onecell_idx;

पूर्ण;

काष्ठा npcm7xx_clk_भाग_fixed_data अणु
	u8 mult;
	u8 भाग;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	u8 clk_भागider_flags;
	/*
	 * If this घड़ी is exported via DT, set onecell_idx to स्थिरant
	 * defined in include/dt-bindings/घड़ी/nuvoton, NPCM7XX-घड़ी.h क्रम
	 * this specअगरic घड़ी.  Otherwise, set to -1.
	 */
	पूर्णांक onecell_idx;
पूर्ण;


काष्ठा npcm7xx_clk_भाग_data अणु
	u32 reg;
	u8 shअगरt;
	u8 width;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	u8 clk_भागider_flags;
	अचिन्हित दीर्घ flags;
	/*
	 * If this घड़ी is exported via DT, set onecell_idx to स्थिरant
	 * defined in include/dt-bindings/घड़ी/nuvoton, NPCM7XX-घड़ी.h क्रम
	 * this specअगरic घड़ी.  Otherwise, set to -1.
	 */
	पूर्णांक onecell_idx;
पूर्ण;

काष्ठा npcm7xx_clk_pll_data अणु
	u32 reg;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	/*
	 * If this घड़ी is exported via DT, set onecell_idx to स्थिरant
	 * defined in include/dt-bindings/घड़ी/nuvoton, NPCM7XX-घड़ी.h क्रम
	 * this specअगरic घड़ी.  Otherwise, set to -1.
	 */
	पूर्णांक onecell_idx;
पूर्ण;

/*
 * Single copy of strings used to refer to घड़ीs within this driver indexed by
 * above क्रमागत.
 */
#घोषणा NPCM7XX_CLK_S_REFCLK      "refclk"
#घोषणा NPCM7XX_CLK_S_SYSBYPCK    "sysbypck"
#घोषणा NPCM7XX_CLK_S_MCBYPCK     "mcbypck"
#घोषणा NPCM7XX_CLK_S_GFXBYPCK    "gfxbypck"
#घोषणा NPCM7XX_CLK_S_PLL0        "pll0"
#घोषणा NPCM7XX_CLK_S_PLL1        "pll1"
#घोषणा NPCM7XX_CLK_S_PLL1_DIV2   "pll1_div2"
#घोषणा NPCM7XX_CLK_S_PLL2        "pll2"
#घोषणा NPCM7XX_CLK_S_PLL_GFX     "pll_gfx"
#घोषणा NPCM7XX_CLK_S_PLL2_DIV2   "pll2_div2"
#घोषणा NPCM7XX_CLK_S_PIX_MUX     "gfx_pixel"
#घोषणा NPCM7XX_CLK_S_GPRFSEL_MUX "gprfsel_mux"
#घोषणा NPCM7XX_CLK_S_MC_MUX      "mc_phy"
#घोषणा NPCM7XX_CLK_S_CPU_MUX     "cpu"  /*AKA प्रणाली घड़ी.*/
#घोषणा NPCM7XX_CLK_S_MC          "mc"
#घोषणा NPCM7XX_CLK_S_AXI         "axi"  /*AKA CLK2*/
#घोषणा NPCM7XX_CLK_S_AHB         "ahb"  /*AKA CLK4*/
#घोषणा NPCM7XX_CLK_S_CLKOUT_MUX  "clkout_mux"
#घोषणा NPCM7XX_CLK_S_UART_MUX    "uart_mux"
#घोषणा NPCM7XX_CLK_S_TIM_MUX     "timer_mux"
#घोषणा NPCM7XX_CLK_S_SD_MUX      "sd_mux"
#घोषणा NPCM7XX_CLK_S_GFXM_MUX    "gfxm_mux"
#घोषणा NPCM7XX_CLK_S_SU_MUX      "serial_usb_mux"
#घोषणा NPCM7XX_CLK_S_DVC_MUX     "dvc_mux"
#घोषणा NPCM7XX_CLK_S_GFX_MUX     "gfx_mux"
#घोषणा NPCM7XX_CLK_S_GFX_PIXEL   "gfx_pixel"
#घोषणा NPCM7XX_CLK_S_SPI0        "spi0"
#घोषणा NPCM7XX_CLK_S_SPI3        "spi3"
#घोषणा NPCM7XX_CLK_S_SPIX        "spix"
#घोषणा NPCM7XX_CLK_S_APB1        "apb1"
#घोषणा NPCM7XX_CLK_S_APB2        "apb2"
#घोषणा NPCM7XX_CLK_S_APB3        "apb3"
#घोषणा NPCM7XX_CLK_S_APB4        "apb4"
#घोषणा NPCM7XX_CLK_S_APB5        "apb5"
#घोषणा NPCM7XX_CLK_S_TOCK        "tock"
#घोषणा NPCM7XX_CLK_S_CLKOUT      "clkout"
#घोषणा NPCM7XX_CLK_S_UART        "uart"
#घोषणा NPCM7XX_CLK_S_TIMER       "timer"
#घोषणा NPCM7XX_CLK_S_MMC         "mmc"
#घोषणा NPCM7XX_CLK_S_SDHC        "sdhc"
#घोषणा NPCM7XX_CLK_S_ADC         "adc"
#घोषणा NPCM7XX_CLK_S_GFX         "gfx0_gfx1_mem"
#घोषणा NPCM7XX_CLK_S_USBIF       "serial_usbif"
#घोषणा NPCM7XX_CLK_S_USB_HOST    "usb_host"
#घोषणा NPCM7XX_CLK_S_USB_BRIDGE  "usb_bridge"
#घोषणा NPCM7XX_CLK_S_PCI         "pci"

अटल u32 pll_mux_table[] = अणु0, 1, 2, 3पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_PLL0,
	NPCM7XX_CLK_S_PLL1_DIV2,
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_PLL2_DIV2,
पूर्ण;

अटल u32 cpuck_mux_table[] = अणु0, 1, 2, 3पूर्ण;
अटल स्थिर अक्षर * स्थिर cpuck_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_PLL0,
	NPCM7XX_CLK_S_PLL1_DIV2,
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_SYSBYPCK,
पूर्ण;

अटल u32 pixcksel_mux_table[] = अणु0, 2पूर्ण;
अटल स्थिर अक्षर * स्थिर pixcksel_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_PLL_GFX,
	NPCM7XX_CLK_S_REFCLK,
पूर्ण;

अटल u32 sucksel_mux_table[] = अणु2, 3पूर्ण;
अटल स्थिर अक्षर * स्थिर sucksel_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_PLL2_DIV2,
पूर्ण;

अटल u32 mccksel_mux_table[] = अणु0, 2, 3पूर्ण;
अटल स्थिर अक्षर * स्थिर mccksel_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_PLL1_DIV2,
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_MCBYPCK,
पूर्ण;

अटल u32 clkoutsel_mux_table[] = अणु0, 1, 2, 3, 4पूर्ण;
अटल स्थिर अक्षर * स्थिर clkoutsel_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_PLL0,
	NPCM7XX_CLK_S_PLL1_DIV2,
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_PLL_GFX, // भागided by 2
	NPCM7XX_CLK_S_PLL2_DIV2,
पूर्ण;

अटल u32 gfxmsel_mux_table[] = अणु2, 3पूर्ण;
अटल स्थिर अक्षर * स्थिर gfxmsel_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_PLL2_DIV2,
पूर्ण;

अटल u32 dvcssel_mux_table[] = अणु2, 3पूर्ण;
अटल स्थिर अक्षर * स्थिर dvcssel_mux_parents[] __initस्थिर = अणु
	NPCM7XX_CLK_S_REFCLK,
	NPCM7XX_CLK_S_PLL2,
पूर्ण;

अटल स्थिर काष्ठा npcm7xx_clk_pll_data npcm7xx_plls[] __initस्थिर = अणु
	अणुNPCM7XX_PLLCON0, NPCM7XX_CLK_S_PLL0, NPCM7XX_CLK_S_REFCLK, 0, -1पूर्ण,

	अणुNPCM7XX_PLLCON1, NPCM7XX_CLK_S_PLL1,
	NPCM7XX_CLK_S_REFCLK, 0, -1पूर्ण,

	अणुNPCM7XX_PLLCON2, NPCM7XX_CLK_S_PLL2,
	NPCM7XX_CLK_S_REFCLK, 0, -1पूर्ण,

	अणुNPCM7XX_PLLCONG, NPCM7XX_CLK_S_PLL_GFX,
	NPCM7XX_CLK_S_REFCLK, 0, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा npcm7xx_clk_mux_data npcm7xx_muxes[] __initस्थिर = अणु
	अणु0, GENMASK(1, 0), cpuck_mux_table, NPCM7XX_CLK_S_CPU_MUX,
	cpuck_mux_parents, ARRAY_SIZE(cpuck_mux_parents), CLK_IS_CRITICAL,
	NPCM7XX_CLK_CPUपूर्ण,

	अणु4, GENMASK(1, 0), pixcksel_mux_table, NPCM7XX_CLK_S_PIX_MUX,
	pixcksel_mux_parents, ARRAY_SIZE(pixcksel_mux_parents), 0,
	NPCM7XX_CLK_GFX_PIXELपूर्ण,

	अणु6, GENMASK(1, 0), pll_mux_table, NPCM7XX_CLK_S_SD_MUX,
	pll_mux_parents, ARRAY_SIZE(pll_mux_parents), 0, -1पूर्ण,

	अणु8, GENMASK(1, 0), pll_mux_table, NPCM7XX_CLK_S_UART_MUX,
	pll_mux_parents, ARRAY_SIZE(pll_mux_parents), 0, -1पूर्ण,

	अणु10, GENMASK(1, 0), sucksel_mux_table, NPCM7XX_CLK_S_SU_MUX,
	sucksel_mux_parents, ARRAY_SIZE(sucksel_mux_parents), 0, -1पूर्ण,

	अणु12, GENMASK(1, 0), mccksel_mux_table, NPCM7XX_CLK_S_MC_MUX,
	mccksel_mux_parents, ARRAY_SIZE(mccksel_mux_parents), 0, -1पूर्ण,

	अणु14, GENMASK(1, 0), pll_mux_table, NPCM7XX_CLK_S_TIM_MUX,
	pll_mux_parents, ARRAY_SIZE(pll_mux_parents), 0, -1पूर्ण,

	अणु16, GENMASK(1, 0), pll_mux_table, NPCM7XX_CLK_S_GFX_MUX,
	pll_mux_parents, ARRAY_SIZE(pll_mux_parents), 0, -1पूर्ण,

	अणु18, GENMASK(2, 0), clkoutsel_mux_table, NPCM7XX_CLK_S_CLKOUT_MUX,
	clkoutsel_mux_parents, ARRAY_SIZE(clkoutsel_mux_parents), 0, -1पूर्ण,

	अणु21, GENMASK(1, 0), gfxmsel_mux_table, NPCM7XX_CLK_S_GFXM_MUX,
	gfxmsel_mux_parents, ARRAY_SIZE(gfxmsel_mux_parents), 0, -1पूर्ण,

	अणु23, GENMASK(1, 0), dvcssel_mux_table, NPCM7XX_CLK_S_DVC_MUX,
	dvcssel_mux_parents, ARRAY_SIZE(dvcssel_mux_parents), 0, -1पूर्ण,
पूर्ण;

/* configurable भागiders: */
अटल स्थिर काष्ठा npcm7xx_clk_भाग_data npcm7xx_भागs[] __initस्थिर = अणु
	अणुNPCM7XX_CLKDIV1, 28, 3, NPCM7XX_CLK_S_ADC,
	NPCM7XX_CLK_S_TIMER, CLK_DIVIDER_POWER_OF_TWO, 0, NPCM7XX_CLK_ADCपूर्ण,
	/*30-28 ADCCKDIV*/
	अणुNPCM7XX_CLKDIV1, 26, 2, NPCM7XX_CLK_S_AHB,
	NPCM7XX_CLK_S_AXI, 0, CLK_IS_CRITICAL, NPCM7XX_CLK_AHBपूर्ण,
	/*27-26 CLK4DIV*/
	अणुNPCM7XX_CLKDIV1, 21, 5, NPCM7XX_CLK_S_TIMER,
	NPCM7XX_CLK_S_TIM_MUX, 0, 0, NPCM7XX_CLK_TIMERपूर्ण,
	/*25-21 TIMCKDIV*/
	अणुNPCM7XX_CLKDIV1, 16, 5, NPCM7XX_CLK_S_UART,
	NPCM7XX_CLK_S_UART_MUX, 0, 0, NPCM7XX_CLK_UARTपूर्ण,
	/*20-16 UARTDIV*/
	अणुNPCM7XX_CLKDIV1, 11, 5, NPCM7XX_CLK_S_MMC,
	NPCM7XX_CLK_S_SD_MUX, 0, 0, NPCM7XX_CLK_MMCपूर्ण,
	/*15-11 MMCCKDIV*/
	अणुNPCM7XX_CLKDIV1, 6, 5, NPCM7XX_CLK_S_SPI3,
	NPCM7XX_CLK_S_AHB, 0, 0, NPCM7XX_CLK_SPI3पूर्ण,
	/*10-6 AHB3CKDIV*/
	अणुNPCM7XX_CLKDIV1, 2, 4, NPCM7XX_CLK_S_PCI,
	NPCM7XX_CLK_S_GFX_MUX, 0, 0, NPCM7XX_CLK_PCIपूर्ण,
	/*5-2 PCICKDIV*/
	अणुNPCM7XX_CLKDIV1, 0, 1, NPCM7XX_CLK_S_AXI,
	NPCM7XX_CLK_S_CPU_MUX, CLK_DIVIDER_POWER_OF_TWO, CLK_IS_CRITICAL,
	NPCM7XX_CLK_AXIपूर्ण,/*0 CLK2DIV*/

	अणुNPCM7XX_CLKDIV2, 30, 2, NPCM7XX_CLK_S_APB4,
	NPCM7XX_CLK_S_AHB, CLK_DIVIDER_POWER_OF_TWO, 0, NPCM7XX_CLK_APB4पूर्ण,
	/*31-30 APB4CKDIV*/
	अणुNPCM7XX_CLKDIV2, 28, 2, NPCM7XX_CLK_S_APB3,
	NPCM7XX_CLK_S_AHB, CLK_DIVIDER_POWER_OF_TWO, 0, NPCM7XX_CLK_APB3पूर्ण,
	/*29-28 APB3CKDIV*/
	अणुNPCM7XX_CLKDIV2, 26, 2, NPCM7XX_CLK_S_APB2,
	NPCM7XX_CLK_S_AHB, CLK_DIVIDER_POWER_OF_TWO, 0, NPCM7XX_CLK_APB2पूर्ण,
	/*27-26 APB2CKDIV*/
	अणुNPCM7XX_CLKDIV2, 24, 2, NPCM7XX_CLK_S_APB1,
	NPCM7XX_CLK_S_AHB, CLK_DIVIDER_POWER_OF_TWO, 0, NPCM7XX_CLK_APB1पूर्ण,
	/*25-24 APB1CKDIV*/
	अणुNPCM7XX_CLKDIV2, 22, 2, NPCM7XX_CLK_S_APB5,
	NPCM7XX_CLK_S_AHB, CLK_DIVIDER_POWER_OF_TWO, 0, NPCM7XX_CLK_APB5पूर्ण,
	/*23-22 APB5CKDIV*/
	अणुNPCM7XX_CLKDIV2, 16, 5, NPCM7XX_CLK_S_CLKOUT,
	NPCM7XX_CLK_S_CLKOUT_MUX, 0, 0, NPCM7XX_CLK_CLKOUTपूर्ण,
	/*20-16 CLKOUTDIV*/
	अणुNPCM7XX_CLKDIV2, 13, 3, NPCM7XX_CLK_S_GFX,
	NPCM7XX_CLK_S_GFX_MUX, 0, 0, NPCM7XX_CLK_GFXपूर्ण,
	/*15-13 GFXCKDIV*/
	अणुNPCM7XX_CLKDIV2, 8, 5, NPCM7XX_CLK_S_USB_BRIDGE,
	NPCM7XX_CLK_S_SU_MUX, 0, 0, NPCM7XX_CLK_SUपूर्ण,
	/*12-8 SUCKDIV*/
	अणुNPCM7XX_CLKDIV2, 4, 4, NPCM7XX_CLK_S_USB_HOST,
	NPCM7XX_CLK_S_SU_MUX, 0, 0, NPCM7XX_CLK_SU48पूर्ण,
	/*7-4 SU48CKDIV*/
	अणुNPCM7XX_CLKDIV2, 0, 4, NPCM7XX_CLK_S_SDHC,
	NPCM7XX_CLK_S_SD_MUX, 0, 0, NPCM7XX_CLK_SDHCपूर्ण
	,/*3-0 SD1CKDIV*/

	अणुNPCM7XX_CLKDIV3, 6, 5, NPCM7XX_CLK_S_SPI0,
	NPCM7XX_CLK_S_AHB, 0, 0, NPCM7XX_CLK_SPI0पूर्ण,
	/*10-6 SPI0CKDV*/
	अणुNPCM7XX_CLKDIV3, 1, 5, NPCM7XX_CLK_S_SPIX,
	NPCM7XX_CLK_S_AHB, 0, 0, NPCM7XX_CLK_SPIXपूर्ण,
	/*5-1 SPIXCKDV*/

पूर्ण;

अटल DEFINE_SPINLOCK(npcm7xx_clk_lock);

अटल व्योम __init npcm7xx_clk_init(काष्ठा device_node *clk_np)
अणु
	काष्ठा clk_hw_onecell_data *npcm7xx_clk_data;
	व्योम __iomem *clk_base;
	काष्ठा resource res;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;
	पूर्णांक i;

	ret = of_address_to_resource(clk_np, 0, &res);
	अगर (ret) अणु
		pr_err("%pOFn: failed to get resource, ret %d\n", clk_np,
			ret);
		वापस;
	पूर्ण

	clk_base = ioremap(res.start, resource_size(&res));
	अगर (!clk_base)
		जाओ npcm7xx_init_error;

	npcm7xx_clk_data = kzalloc(काष्ठा_size(npcm7xx_clk_data, hws,
				   NPCM7XX_NUM_CLOCKS), GFP_KERNEL);
	अगर (!npcm7xx_clk_data)
		जाओ npcm7xx_init_np_err;

	npcm7xx_clk_data->num = NPCM7XX_NUM_CLOCKS;

	क्रम (i = 0; i < NPCM7XX_NUM_CLOCKS; i++)
		npcm7xx_clk_data->hws[i] = ERR_PTR(-EPROBE_DEFER);

	/* Register plls */
	क्रम (i = 0; i < ARRAY_SIZE(npcm7xx_plls); i++) अणु
		स्थिर काष्ठा npcm7xx_clk_pll_data *pll_data = &npcm7xx_plls[i];

		hw = npcm7xx_clk_रेजिस्टर_pll(clk_base + pll_data->reg,
			pll_data->name, pll_data->parent_name, pll_data->flags);
		अगर (IS_ERR(hw)) अणु
			pr_err("npcm7xx_clk: Can't register pll\n");
			जाओ npcm7xx_init_fail;
		पूर्ण

		अगर (pll_data->onecell_idx >= 0)
			npcm7xx_clk_data->hws[pll_data->onecell_idx] = hw;
	पूर्ण

	/* Register fixed भागiders */
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, NPCM7XX_CLK_S_PLL1_DIV2,
			NPCM7XX_CLK_S_PLL1, 0, 1, 2);
	अगर (IS_ERR(hw)) अणु
		pr_err("npcm7xx_clk: Can't register fixed div\n");
		जाओ npcm7xx_init_fail;
	पूर्ण

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, NPCM7XX_CLK_S_PLL2_DIV2,
			NPCM7XX_CLK_S_PLL2, 0, 1, 2);
	अगर (IS_ERR(hw)) अणु
		pr_err("npcm7xx_clk: Can't register div2\n");
		जाओ npcm7xx_init_fail;
	पूर्ण

	/* Register muxes */
	क्रम (i = 0; i < ARRAY_SIZE(npcm7xx_muxes); i++) अणु
		स्थिर काष्ठा npcm7xx_clk_mux_data *mux_data = &npcm7xx_muxes[i];

		hw = clk_hw_रेजिस्टर_mux_table(शून्य,
			mux_data->name,
			mux_data->parent_names, mux_data->num_parents,
			mux_data->flags, clk_base + NPCM7XX_CLKSEL,
			mux_data->shअगरt, mux_data->mask, 0,
			mux_data->table, &npcm7xx_clk_lock);

		अगर (IS_ERR(hw)) अणु
			pr_err("npcm7xx_clk: Can't register mux\n");
			जाओ npcm7xx_init_fail;
		पूर्ण

		अगर (mux_data->onecell_idx >= 0)
			npcm7xx_clk_data->hws[mux_data->onecell_idx] = hw;
	पूर्ण

	/* Register घड़ी भागiders specअगरied in npcm7xx_भागs */
	क्रम (i = 0; i < ARRAY_SIZE(npcm7xx_भागs); i++) अणु
		स्थिर काष्ठा npcm7xx_clk_भाग_data *भाग_data = &npcm7xx_भागs[i];

		hw = clk_hw_रेजिस्टर_भागider(शून्य, भाग_data->name,
				भाग_data->parent_name,
				भाग_data->flags,
				clk_base + भाग_data->reg,
				भाग_data->shअगरt, भाग_data->width,
				भाग_data->clk_भागider_flags, &npcm7xx_clk_lock);
		अगर (IS_ERR(hw)) अणु
			pr_err("npcm7xx_clk: Can't register div table\n");
			जाओ npcm7xx_init_fail;
		पूर्ण

		अगर (भाग_data->onecell_idx >= 0)
			npcm7xx_clk_data->hws[भाग_data->onecell_idx] = hw;
	पूर्ण

	ret = of_clk_add_hw_provider(clk_np, of_clk_hw_onecell_get,
					npcm7xx_clk_data);
	अगर (ret)
		pr_err("failed to add DT provider: %d\n", ret);

	of_node_put(clk_np);

	वापस;

npcm7xx_init_fail:
	kमुक्त(npcm7xx_clk_data->hws);
npcm7xx_init_np_err:
	iounmap(clk_base);
npcm7xx_init_error:
	of_node_put(clk_np);
पूर्ण
CLK_OF_DECLARE(npcm7xx_clk_init, "nuvoton,npcm750-clk", npcm7xx_clk_init);
