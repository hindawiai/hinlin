<शैली गुरु>
/*
 * TI DA850/OMAP-L138 chip specअगरic setup
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Derived from: arch/arm/mach-davinci/da830.c
 * Original Copyrights follow:
 *
 * 2009 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/irq-davinci-cp-पूर्णांकc.h>
#समावेश <linux/mfd/da8xx-cfgchip.h>
#समावेश <linux/platक्रमm_data/clk-da8xx-cfgchip.h>
#समावेश <linux/platक्रमm_data/clk-davinci-pll.h>
#समावेश <linux/platक्रमm_data/davinci-cpufreq.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <यंत्र/mach/map.h>

#समावेश <mach/common.h>
#समावेश <mach/cputype.h>
#समावेश <mach/da8xx.h>
#समावेश <mach/pm.h>

#समावेश <घड़ीsource/समयr-davinci.h>

#समावेश "irqs.h"
#समावेश "mux.h"

#घोषणा DA850_PLL1_BASE		0x01e1a000
#घोषणा DA850_TIMER64P2_BASE	0x01f0c000
#घोषणा DA850_TIMER64P3_BASE	0x01f0d000

#घोषणा DA850_REF_FREQ		24000000

/*
 * Device specअगरic mux setup
 *
 *		soc	description	mux	mode	mode	mux	dbg
 *					reg	offset	mask	mode
 */
अटल स्थिर काष्ठा mux_config da850_pins[] = अणु
#अगर_घोषित CONFIG_DAVINCI_MUX
	/* UART0 function */
	MUX_CFG(DA850, NUART0_CTS,	3,	24,	15,	2,	false)
	MUX_CFG(DA850, NUART0_RTS,	3,	28,	15,	2,	false)
	MUX_CFG(DA850, UART0_RXD,	3,	16,	15,	2,	false)
	MUX_CFG(DA850, UART0_TXD,	3,	20,	15,	2,	false)
	/* UART1 function */
	MUX_CFG(DA850, UART1_RXD,	4,	24,	15,	2,	false)
	MUX_CFG(DA850, UART1_TXD,	4,	28,	15,	2,	false)
	/* UART2 function */
	MUX_CFG(DA850, UART2_RXD,	4,	16,	15,	2,	false)
	MUX_CFG(DA850, UART2_TXD,	4,	20,	15,	2,	false)
	/* I2C1 function */
	MUX_CFG(DA850, I2C1_SCL,	4,	16,	15,	4,	false)
	MUX_CFG(DA850, I2C1_SDA,	4,	20,	15,	4,	false)
	/* I2C0 function */
	MUX_CFG(DA850, I2C0_SDA,	4,	12,	15,	2,	false)
	MUX_CFG(DA850, I2C0_SCL,	4,	8,	15,	2,	false)
	/* EMAC function */
	MUX_CFG(DA850, MII_TXEN,	2,	4,	15,	8,	false)
	MUX_CFG(DA850, MII_TXCLK,	2,	8,	15,	8,	false)
	MUX_CFG(DA850, MII_COL,		2,	12,	15,	8,	false)
	MUX_CFG(DA850, MII_TXD_3,	2,	16,	15,	8,	false)
	MUX_CFG(DA850, MII_TXD_2,	2,	20,	15,	8,	false)
	MUX_CFG(DA850, MII_TXD_1,	2,	24,	15,	8,	false)
	MUX_CFG(DA850, MII_TXD_0,	2,	28,	15,	8,	false)
	MUX_CFG(DA850, MII_RXCLK,	3,	0,	15,	8,	false)
	MUX_CFG(DA850, MII_RXDV,	3,	4,	15,	8,	false)
	MUX_CFG(DA850, MII_RXER,	3,	8,	15,	8,	false)
	MUX_CFG(DA850, MII_CRS,		3,	12,	15,	8,	false)
	MUX_CFG(DA850, MII_RXD_3,	3,	16,	15,	8,	false)
	MUX_CFG(DA850, MII_RXD_2,	3,	20,	15,	8,	false)
	MUX_CFG(DA850, MII_RXD_1,	3,	24,	15,	8,	false)
	MUX_CFG(DA850, MII_RXD_0,	3,	28,	15,	8,	false)
	MUX_CFG(DA850, MDIO_CLK,	4,	0,	15,	8,	false)
	MUX_CFG(DA850, MDIO_D,		4,	4,	15,	8,	false)
	MUX_CFG(DA850, RMII_TXD_0,	14,	12,	15,	8,	false)
	MUX_CFG(DA850, RMII_TXD_1,	14,	8,	15,	8,	false)
	MUX_CFG(DA850, RMII_TXEN,	14,	16,	15,	8,	false)
	MUX_CFG(DA850, RMII_CRS_DV,	15,	4,	15,	8,	false)
	MUX_CFG(DA850, RMII_RXD_0,	14,	24,	15,	8,	false)
	MUX_CFG(DA850, RMII_RXD_1,	14,	20,	15,	8,	false)
	MUX_CFG(DA850, RMII_RXER,	14,	28,	15,	8,	false)
	MUX_CFG(DA850, RMII_MHZ_50_CLK,	15,	0,	15,	0,	false)
	/* McASP function */
	MUX_CFG(DA850,	ACLKR,		0,	0,	15,	1,	false)
	MUX_CFG(DA850,	ACLKX,		0,	4,	15,	1,	false)
	MUX_CFG(DA850,	AFSR,		0,	8,	15,	1,	false)
	MUX_CFG(DA850,	AFSX,		0,	12,	15,	1,	false)
	MUX_CFG(DA850,	AHCLKR,		0,	16,	15,	1,	false)
	MUX_CFG(DA850,	AHCLKX,		0,	20,	15,	1,	false)
	MUX_CFG(DA850,	AMUTE,		0,	24,	15,	1,	false)
	MUX_CFG(DA850,	AXR_15,		1,	0,	15,	1,	false)
	MUX_CFG(DA850,	AXR_14,		1,	4,	15,	1,	false)
	MUX_CFG(DA850,	AXR_13,		1,	8,	15,	1,	false)
	MUX_CFG(DA850,	AXR_12,		1,	12,	15,	1,	false)
	MUX_CFG(DA850,	AXR_11,		1,	16,	15,	1,	false)
	MUX_CFG(DA850,	AXR_10,		1,	20,	15,	1,	false)
	MUX_CFG(DA850,	AXR_9,		1,	24,	15,	1,	false)
	MUX_CFG(DA850,	AXR_8,		1,	28,	15,	1,	false)
	MUX_CFG(DA850,	AXR_7,		2,	0,	15,	1,	false)
	MUX_CFG(DA850,	AXR_6,		2,	4,	15,	1,	false)
	MUX_CFG(DA850,	AXR_5,		2,	8,	15,	1,	false)
	MUX_CFG(DA850,	AXR_4,		2,	12,	15,	1,	false)
	MUX_CFG(DA850,	AXR_3,		2,	16,	15,	1,	false)
	MUX_CFG(DA850,	AXR_2,		2,	20,	15,	1,	false)
	MUX_CFG(DA850,	AXR_1,		2,	24,	15,	1,	false)
	MUX_CFG(DA850,	AXR_0,		2,	28,	15,	1,	false)
	/* LCD function */
	MUX_CFG(DA850, LCD_D_7,		16,	8,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_6,		16,	12,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_5,		16,	16,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_4,		16,	20,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_3,		16,	24,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_2,		16,	28,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_1,		17,	0,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_0,		17,	4,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_15,	17,	8,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_14,	17,	12,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_13,	17,	16,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_12,	17,	20,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_11,	17,	24,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_10,	17,	28,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_9,		18,	0,	15,	2,	false)
	MUX_CFG(DA850, LCD_D_8,		18,	4,	15,	2,	false)
	MUX_CFG(DA850, LCD_PCLK,	18,	24,	15,	2,	false)
	MUX_CFG(DA850, LCD_HSYNC,	19,	0,	15,	2,	false)
	MUX_CFG(DA850, LCD_VSYNC,	19,	4,	15,	2,	false)
	MUX_CFG(DA850, NLCD_AC_ENB_CS,	19,	24,	15,	2,	false)
	/* MMC/SD0 function */
	MUX_CFG(DA850, MMCSD0_DAT_0,	10,	8,	15,	2,	false)
	MUX_CFG(DA850, MMCSD0_DAT_1,	10,	12,	15,	2,	false)
	MUX_CFG(DA850, MMCSD0_DAT_2,	10,	16,	15,	2,	false)
	MUX_CFG(DA850, MMCSD0_DAT_3,	10,	20,	15,	2,	false)
	MUX_CFG(DA850, MMCSD0_CLK,	10,	0,	15,	2,	false)
	MUX_CFG(DA850, MMCSD0_CMD,	10,	4,	15,	2,	false)
	/* MMC/SD1 function */
	MUX_CFG(DA850, MMCSD1_DAT_0,	18,	8,	15,	2,	false)
	MUX_CFG(DA850, MMCSD1_DAT_1,	19,	16,	15,	2,	false)
	MUX_CFG(DA850, MMCSD1_DAT_2,	19,	12,	15,	2,	false)
	MUX_CFG(DA850, MMCSD1_DAT_3,	19,	8,	15,	2,	false)
	MUX_CFG(DA850, MMCSD1_CLK,	18,	12,	15,	2,	false)
	MUX_CFG(DA850, MMCSD1_CMD,	18,	16,	15,	2,	false)
	/* EMIF2.5/EMIFA function */
	MUX_CFG(DA850, EMA_D_7,		9,	0,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_6,		9,	4,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_5,		9,	8,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_4,		9,	12,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_3,		9,	16,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_2,		9,	20,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_1,		9,	24,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_0,		9,	28,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_1,		12,	24,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_2,		12,	20,	15,	1,	false)
	MUX_CFG(DA850, NEMA_CS_3,	7,	4,	15,	1,	false)
	MUX_CFG(DA850, NEMA_CS_4,	7,	8,	15,	1,	false)
	MUX_CFG(DA850, NEMA_WE,		7,	16,	15,	1,	false)
	MUX_CFG(DA850, NEMA_OE,		7,	20,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_0,		12,	28,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_3,		12,	16,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_4,		12,	12,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_5,		12,	8,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_6,		12,	4,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_7,		12,	0,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_8,		11,	28,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_9,		11,	24,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_10,	11,	20,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_11,	11,	16,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_12,	11,	12,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_13,	11,	8,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_14,	11,	4,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_15,	11,	0,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_16,	10,	28,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_17,	10,	24,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_18,	10,	20,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_19,	10,	16,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_20,	10,	12,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_21,	10,	8,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_22,	10,	4,	15,	1,	false)
	MUX_CFG(DA850, EMA_A_23,	10,	0,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_8,		8,	28,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_9,		8,	24,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_10,	8,	20,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_11,	8,	16,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_12,	8,	12,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_13,	8,	8,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_14,	8,	4,	15,	1,	false)
	MUX_CFG(DA850, EMA_D_15,	8,	0,	15,	1,	false)
	MUX_CFG(DA850, EMA_BA_1,	5,	24,	15,	1,	false)
	MUX_CFG(DA850, EMA_CLK,		6,	0,	15,	1,	false)
	MUX_CFG(DA850, EMA_WAIT_1,	6,	24,	15,	1,	false)
	MUX_CFG(DA850, NEMA_CS_2,	7,	0,	15,	1,	false)
	/* GPIO function */
	MUX_CFG(DA850, GPIO2_4,		6,	12,	15,	8,	false)
	MUX_CFG(DA850, GPIO2_6,		6,	4,	15,	8,	false)
	MUX_CFG(DA850, GPIO2_8,		5,	28,	15,	8,	false)
	MUX_CFG(DA850, GPIO2_15,	5,	0,	15,	8,	false)
	MUX_CFG(DA850, GPIO3_12,	7,	12,	15,	8,	false)
	MUX_CFG(DA850, GPIO3_13,	7,	8,	15,	8,	false)
	MUX_CFG(DA850, GPIO4_0,		10,	28,	15,	8,	false)
	MUX_CFG(DA850, GPIO4_1,		10,	24,	15,	8,	false)
	MUX_CFG(DA850, GPIO6_9,		13,	24,	15,	8,	false)
	MUX_CFG(DA850, GPIO6_10,	13,	20,	15,	8,	false)
	MUX_CFG(DA850, GPIO6_13,	13,	8,	15,	8,	false)
	MUX_CFG(DA850, RTC_ALARM,	0,	28,	15,	2,	false)
	/* VPIF Capture */
	MUX_CFG(DA850, VPIF_DIN0,	15,	4,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN1,	15,	0,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN2,	14,	28,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN3,	14,	24,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN4,	14,	20,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN5,	14,	16,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN6,	14,	12,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN7,	14,	8,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN8,	16,	4,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN9,	16,	0,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN10,	15,	28,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN11,	15,	24,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN12,	15,	20,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN13,	15,	16,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN14,	15,	12,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DIN15,	15,	8,	15,	1,	false)
	MUX_CFG(DA850, VPIF_CLKIN0,	14,	0,	15,	1,	false)
	MUX_CFG(DA850, VPIF_CLKIN1,	14,	4,	15,	1,	false)
	MUX_CFG(DA850, VPIF_CLKIN2,	19,	8,	15,	1,	false)
	MUX_CFG(DA850, VPIF_CLKIN3,	19,	16,	15,	1,	false)
	/* VPIF Display */
	MUX_CFG(DA850, VPIF_DOUT0,	17,	4,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT1,	17,	0,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT2,	16,	28,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT3,	16,	24,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT4,	16,	20,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT5,	16,	16,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT6,	16,	12,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT7,	16,	8,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT8,	18,	4,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT9,	18,	0,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT10,	17,	28,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT11,	17,	24,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT12,	17,	20,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT13,	17,	16,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT14,	17,	12,	15,	1,	false)
	MUX_CFG(DA850, VPIF_DOUT15,	17,	8,	15,	1,	false)
	MUX_CFG(DA850, VPIF_CLKO2,	19,	12,	15,	1,	false)
	MUX_CFG(DA850, VPIF_CLKO3,	19,	20,	15,	1,	false)
#पूर्ण_अगर
पूर्ण;

स्थिर लघु da850_i2c0_pins[] __initस्थिर = अणु
	DA850_I2C0_SDA, DA850_I2C0_SCL,
	-1
पूर्ण;

स्थिर लघु da850_i2c1_pins[] __initस्थिर = अणु
	DA850_I2C1_SCL, DA850_I2C1_SDA,
	-1
पूर्ण;

स्थिर लघु da850_lcdcntl_pins[] __initस्थिर = अणु
	DA850_LCD_D_0, DA850_LCD_D_1, DA850_LCD_D_2, DA850_LCD_D_3,
	DA850_LCD_D_4, DA850_LCD_D_5, DA850_LCD_D_6, DA850_LCD_D_7,
	DA850_LCD_D_8, DA850_LCD_D_9, DA850_LCD_D_10, DA850_LCD_D_11,
	DA850_LCD_D_12, DA850_LCD_D_13, DA850_LCD_D_14, DA850_LCD_D_15,
	DA850_LCD_PCLK, DA850_LCD_HSYNC, DA850_LCD_VSYNC, DA850_NLCD_AC_ENB_CS,
	-1
पूर्ण;

स्थिर लघु da850_vpअगर_capture_pins[] __initस्थिर = अणु
	DA850_VPIF_DIN0, DA850_VPIF_DIN1, DA850_VPIF_DIN2, DA850_VPIF_DIN3,
	DA850_VPIF_DIN4, DA850_VPIF_DIN5, DA850_VPIF_DIN6, DA850_VPIF_DIN7,
	DA850_VPIF_DIN8, DA850_VPIF_DIN9, DA850_VPIF_DIN10, DA850_VPIF_DIN11,
	DA850_VPIF_DIN12, DA850_VPIF_DIN13, DA850_VPIF_DIN14, DA850_VPIF_DIN15,
	DA850_VPIF_CLKIN0, DA850_VPIF_CLKIN1, DA850_VPIF_CLKIN2,
	DA850_VPIF_CLKIN3,
	-1
पूर्ण;

स्थिर लघु da850_vpअगर_display_pins[] __initस्थिर = अणु
	DA850_VPIF_DOUT0, DA850_VPIF_DOUT1, DA850_VPIF_DOUT2, DA850_VPIF_DOUT3,
	DA850_VPIF_DOUT4, DA850_VPIF_DOUT5, DA850_VPIF_DOUT6, DA850_VPIF_DOUT7,
	DA850_VPIF_DOUT8, DA850_VPIF_DOUT9, DA850_VPIF_DOUT10,
	DA850_VPIF_DOUT11, DA850_VPIF_DOUT12, DA850_VPIF_DOUT13,
	DA850_VPIF_DOUT14, DA850_VPIF_DOUT15, DA850_VPIF_CLKO2,
	DA850_VPIF_CLKO3,
	-1
पूर्ण;

अटल काष्ठा map_desc da850_io_desc[] = अणु
	अणु
		.भव	= IO_VIRT,
		.pfn		= __phys_to_pfn(IO_PHYS),
		.length		= IO_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= DA8XX_CP_INTC_VIRT,
		.pfn		= __phys_to_pfn(DA8XX_CP_INTC_BASE),
		.length		= DA8XX_CP_INTC_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

/* Contents of JTAG ID रेजिस्टर used to identअगरy exact cpu type */
अटल काष्ठा davinci_id da850_ids[] = अणु
	अणु
		.variant	= 0x0,
		.part_no	= 0xb7d1,
		.manufacturer	= 0x017,	/* 0x02f >> 1 */
		.cpu_id		= DAVINCI_CPU_ID_DA850,
		.name		= "da850/omap-l138",
	पूर्ण,
	अणु
		.variant	= 0x1,
		.part_no	= 0xb7d1,
		.manufacturer	= 0x017,	/* 0x02f >> 1 */
		.cpu_id		= DAVINCI_CPU_ID_DA850,
		.name		= "da850/omap-l138/am18x",
	पूर्ण,
पूर्ण;

/*
 * Bottom half of समयr 0 is used क्रम घड़ी_event, top half क्रम
 * घड़ीsource.
 */
अटल स्थिर काष्ठा davinci_समयr_cfg da850_समयr_cfg = अणु
	.reg = DEFINE_RES_IO(DA8XX_TIMER64P0_BASE, SZ_4K),
	.irq = अणु
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_DA8XX_TINT12_0)),
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_DA8XX_TINT34_0)),
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_CPU_FREQ
/*
 * Notes:
 * According to the TRM, minimum PLLM results in maximum घातer savings.
 * The OPP definitions below should keep the PLLM as low as possible.
 *
 * The output of the PLLM must be between 300 to 600 MHz.
 */
काष्ठा da850_opp अणु
	अचिन्हित पूर्णांक	freq;	/* in KHz */
	अचिन्हित पूर्णांक	preभाग;
	अचिन्हित पूर्णांक	mult;
	अचिन्हित पूर्णांक	postभाग;
	अचिन्हित पूर्णांक	cvdd_min; /* in uV */
	अचिन्हित पूर्णांक	cvdd_max; /* in uV */
पूर्ण;

अटल स्थिर काष्ठा da850_opp da850_opp_456 = अणु
	.freq		= 456000,
	.preभाग		= 1,
	.mult		= 19,
	.postभाग	= 1,
	.cvdd_min	= 1300000,
	.cvdd_max	= 1350000,
पूर्ण;

अटल स्थिर काष्ठा da850_opp da850_opp_408 = अणु
	.freq		= 408000,
	.preभाग		= 1,
	.mult		= 17,
	.postभाग	= 1,
	.cvdd_min	= 1300000,
	.cvdd_max	= 1350000,
पूर्ण;

अटल स्थिर काष्ठा da850_opp da850_opp_372 = अणु
	.freq		= 372000,
	.preभाग		= 2,
	.mult		= 31,
	.postभाग	= 1,
	.cvdd_min	= 1200000,
	.cvdd_max	= 1320000,
पूर्ण;

अटल स्थिर काष्ठा da850_opp da850_opp_300 = अणु
	.freq		= 300000,
	.preभाग		= 1,
	.mult		= 25,
	.postभाग	= 2,
	.cvdd_min	= 1200000,
	.cvdd_max	= 1320000,
पूर्ण;

अटल स्थिर काष्ठा da850_opp da850_opp_200 = अणु
	.freq		= 200000,
	.preभाग		= 1,
	.mult		= 25,
	.postभाग	= 3,
	.cvdd_min	= 1100000,
	.cvdd_max	= 1160000,
पूर्ण;

अटल स्थिर काष्ठा da850_opp da850_opp_96 = अणु
	.freq		= 96000,
	.preभाग		= 1,
	.mult		= 20,
	.postभाग	= 5,
	.cvdd_min	= 1000000,
	.cvdd_max	= 1050000,
पूर्ण;

#घोषणा OPP(freq) 		\
	अणु				\
		.driver_data = (अचिन्हित पूर्णांक) &da850_opp_##freq,	\
		.frequency = freq * 1000, \
	पूर्ण

अटल काष्ठा cpufreq_frequency_table da850_freq_table[] = अणु
	OPP(456),
	OPP(408),
	OPP(372),
	OPP(300),
	OPP(200),
	OPP(96),
	अणु
		.driver_data		= 0,
		.frequency	= CPUFREQ_TABLE_END,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_REGULATOR
अटल पूर्णांक da850_set_voltage(अचिन्हित पूर्णांक index);
अटल पूर्णांक da850_regulator_init(व्योम);
#पूर्ण_अगर

अटल काष्ठा davinci_cpufreq_config cpufreq_info = अणु
	.freq_table = da850_freq_table,
#अगर_घोषित CONFIG_REGULATOR
	.init = da850_regulator_init,
	.set_voltage = da850_set_voltage,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_REGULATOR
अटल काष्ठा regulator *cvdd;

अटल पूर्णांक da850_set_voltage(अचिन्हित पूर्णांक index)
अणु
	काष्ठा da850_opp *opp;

	अगर (!cvdd)
		वापस -ENODEV;

	opp = (काष्ठा da850_opp *) cpufreq_info.freq_table[index].driver_data;

	वापस regulator_set_voltage(cvdd, opp->cvdd_min, opp->cvdd_max);
पूर्ण

अटल पूर्णांक da850_regulator_init(व्योम)
अणु
	cvdd = regulator_get(शून्य, "cvdd");
	अगर (WARN(IS_ERR(cvdd), "Unable to obtain voltage regulator for CVDD;"
					" voltage scaling unsupported\n")) अणु
		वापस PTR_ERR(cvdd);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device da850_cpufreq_device = अणु
	.name			= "cpufreq-davinci",
	.dev = अणु
		.platक्रमm_data	= &cpufreq_info,
	पूर्ण,
	.id = -1,
पूर्ण;

अचिन्हित पूर्णांक da850_max_speed = 300000;

पूर्णांक da850_रेजिस्टर_cpufreq(अक्षर *async_clk)
अणु
	पूर्णांक i;

	/* cpufreq driver can help keep an "async" घड़ी स्थिरant */
	अगर (async_clk)
		clk_add_alias("async", da850_cpufreq_device.name,
							async_clk, शून्य);
	क्रम (i = 0; i < ARRAY_SIZE(da850_freq_table); i++) अणु
		अगर (da850_freq_table[i].frequency <= da850_max_speed) अणु
			cpufreq_info.freq_table = &da850_freq_table[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस platक्रमm_device_रेजिस्टर(&da850_cpufreq_device);
पूर्ण
#अन्यथा
पूर्णांक __init da850_रेजिस्टर_cpufreq(अक्षर *async_clk)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* VPIF resource, platक्रमm data */
अटल u64 da850_vpअगर_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource da850_vpअगर_resource[] = अणु
	अणु
		.start = DA8XX_VPIF_BASE,
		.end   = DA8XX_VPIF_BASE + 0xfff,
		.flags = IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device da850_vpअगर_dev = अणु
	.name		= "vpif",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &da850_vpअगर_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= da850_vpअगर_resource,
	.num_resources	= ARRAY_SIZE(da850_vpअगर_resource),
पूर्ण;

अटल काष्ठा resource da850_vpअगर_display_resource[] = अणु
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DA850_VPIFINT),
		.end   = DAVINCI_INTC_IRQ(IRQ_DA850_VPIFINT),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_vpअगर_display_dev = अणु
	.name		= "vpif_display",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &da850_vpअगर_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource       = da850_vpअगर_display_resource,
	.num_resources  = ARRAY_SIZE(da850_vpअगर_display_resource),
पूर्ण;

अटल काष्ठा resource da850_vpअगर_capture_resource[] = अणु
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DA850_VPIFINT),
		.end   = DAVINCI_INTC_IRQ(IRQ_DA850_VPIFINT),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DA850_VPIFINT),
		.end   = DAVINCI_INTC_IRQ(IRQ_DA850_VPIFINT),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_vpअगर_capture_dev = अणु
	.name		= "vpif_capture",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &da850_vpअगर_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource       = da850_vpअगर_capture_resource,
	.num_resources  = ARRAY_SIZE(da850_vpअगर_capture_resource),
पूर्ण;

पूर्णांक __init da850_रेजिस्टर_vpअगर(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&da850_vpअगर_dev);
पूर्ण

पूर्णांक __init da850_रेजिस्टर_vpअगर_display(काष्ठा vpअगर_display_config
						*display_config)
अणु
	da850_vpअगर_display_dev.dev.platक्रमm_data = display_config;
	वापस platक्रमm_device_रेजिस्टर(&da850_vpअगर_display_dev);
पूर्ण

पूर्णांक __init da850_रेजिस्टर_vpअगर_capture(काष्ठा vpअगर_capture_config
							*capture_config)
अणु
	da850_vpअगर_capture_dev.dev.platक्रमm_data = capture_config;
	वापस platक्रमm_device_रेजिस्टर(&da850_vpअगर_capture_dev);
पूर्ण

अटल काष्ठा davinci_gpio_platक्रमm_data da850_gpio_platक्रमm_data = अणु
	.no_स्वतः_base	= true,
	.base		= 0,
	.ngpio		= 144,
पूर्ण;

पूर्णांक __init da850_रेजिस्टर_gpio(व्योम)
अणु
	वापस da8xx_रेजिस्टर_gpio(&da850_gpio_platक्रमm_data);
पूर्ण

अटल स्थिर काष्ठा davinci_soc_info davinci_soc_info_da850 = अणु
	.io_desc		= da850_io_desc,
	.io_desc_num		= ARRAY_SIZE(da850_io_desc),
	.jtag_id_reg		= DA8XX_SYSCFG0_BASE + DA8XX_JTAG_ID_REG,
	.ids			= da850_ids,
	.ids_num		= ARRAY_SIZE(da850_ids),
	.pinmux_base		= DA8XX_SYSCFG0_BASE + 0x120,
	.pinmux_pins		= da850_pins,
	.pinmux_pins_num	= ARRAY_SIZE(da850_pins),
	.emac_pdata		= &da8xx_emac_pdata,
	.sram_dma		= DA8XX_SHARED_RAM_BASE,
	.sram_len		= SZ_128K,
पूर्ण;

व्योम __init da850_init(व्योम)
अणु
	davinci_common_init(&davinci_soc_info_da850);

	da8xx_syscfg0_base = ioremap(DA8XX_SYSCFG0_BASE, SZ_4K);
	अगर (WARN(!da8xx_syscfg0_base, "Unable to map syscfg0 module"))
		वापस;

	da8xx_syscfg1_base = ioremap(DA8XX_SYSCFG1_BASE, SZ_4K);
	WARN(!da8xx_syscfg1_base, "Unable to map syscfg1 module");
पूर्ण

अटल स्थिर काष्ठा davinci_cp_पूर्णांकc_config da850_cp_पूर्णांकc_config = अणु
	.reg = अणु
		.start		= DA8XX_CP_INTC_BASE,
		.end		= DA8XX_CP_INTC_BASE + SZ_8K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	.num_irqs		= DA850_N_CP_INTC_IRQ,
पूर्ण;

व्योम __init da850_init_irq(व्योम)
अणु
	davinci_cp_पूर्णांकc_init(&da850_cp_पूर्णांकc_config);
पूर्ण

व्योम __init da850_init_समय(व्योम)
अणु
	व्योम __iomem *pll0;
	काष्ठा regmap *cfgchip;
	काष्ठा clk *clk;
	पूर्णांक rv;

	clk_रेजिस्टर_fixed_rate(शून्य, "ref_clk", शून्य, 0, DA850_REF_FREQ);

	pll0 = ioremap(DA8XX_PLL0_BASE, SZ_4K);
	cfgchip = da8xx_get_cfgchip();

	da850_pll0_init(शून्य, pll0, cfgchip);

	clk = clk_get(शून्य, "timer0");
	अगर (WARN_ON(IS_ERR(clk))) अणु
		pr_err("Unable to get the timer clock\n");
		वापस;
	पूर्ण

	rv = davinci_समयr_रेजिस्टर(clk, &da850_समयr_cfg);
	WARN(rv, "Unable to register the timer: %d\n", rv);
पूर्ण

अटल काष्ठा resource da850_pll1_resources[] = अणु
	अणु
		.start	= DA850_PLL1_BASE,
		.end	= DA850_PLL1_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_pll_platक्रमm_data da850_pll1_pdata;

अटल काष्ठा platक्रमm_device da850_pll1_device = अणु
	.name		= "da850-pll1",
	.id		= -1,
	.resource	= da850_pll1_resources,
	.num_resources	= ARRAY_SIZE(da850_pll1_resources),
	.dev		= अणु
		.platक्रमm_data	= &da850_pll1_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource da850_psc0_resources[] = अणु
	अणु
		.start	= DA8XX_PSC0_BASE,
		.end	= DA8XX_PSC0_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_psc0_device = अणु
	.name		= "da850-psc0",
	.id		= -1,
	.resource	= da850_psc0_resources,
	.num_resources	= ARRAY_SIZE(da850_psc0_resources),
पूर्ण;

अटल काष्ठा resource da850_psc1_resources[] = अणु
	अणु
		.start	= DA8XX_PSC1_BASE,
		.end	= DA8XX_PSC1_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_psc1_device = अणु
	.name		= "da850-psc1",
	.id		= -1,
	.resource	= da850_psc1_resources,
	.num_resources	= ARRAY_SIZE(da850_psc1_resources),
पूर्ण;

अटल काष्ठा da8xx_cfgchip_clk_platक्रमm_data da850_async1_pdata;

अटल काष्ठा platक्रमm_device da850_async1_clksrc_device = अणु
	.name		= "da850-async1-clksrc",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &da850_async1_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा da8xx_cfgchip_clk_platक्रमm_data da850_async3_pdata;

अटल काष्ठा platक्रमm_device da850_async3_clksrc_device = अणु
	.name		= "da850-async3-clksrc",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &da850_async3_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा da8xx_cfgchip_clk_platक्रमm_data da850_tbclksync_pdata;

अटल काष्ठा platक्रमm_device da850_tbclksync_device = अणु
	.name		= "da830-tbclksync",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &da850_tbclksync_pdata,
	पूर्ण,
पूर्ण;

व्योम __init da850_रेजिस्टर_घड़ीs(व्योम)
अणु
	/* PLL0 is रेजिस्टरed in da850_init_समय() */

	da850_pll1_pdata.cfgchip = da8xx_get_cfgchip();
	platक्रमm_device_रेजिस्टर(&da850_pll1_device);

	da850_async1_pdata.cfgchip = da8xx_get_cfgchip();
	platक्रमm_device_रेजिस्टर(&da850_async1_clksrc_device);

	da850_async3_pdata.cfgchip = da8xx_get_cfgchip();
	platक्रमm_device_रेजिस्टर(&da850_async3_clksrc_device);

	platक्रमm_device_रेजिस्टर(&da850_psc0_device);

	platक्रमm_device_रेजिस्टर(&da850_psc1_device);

	da850_tbclksync_pdata.cfgchip = da8xx_get_cfgchip();
	platक्रमm_device_रेजिस्टर(&da850_tbclksync_device);
पूर्ण
