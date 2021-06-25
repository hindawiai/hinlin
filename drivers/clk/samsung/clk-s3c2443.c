<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Common Clock Framework support क्रम S3C2443 and following SoCs.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/samsung.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reboot.h>

#समावेश <dt-bindings/घड़ी/s3c2443.h>

#समावेश "clk.h"
#समावेश "clk-pll.h"

/* S3C2416 घड़ी controller रेजिस्टर offsets */
#घोषणा LOCKCON0	0x00
#घोषणा LOCKCON1	0x04
#घोषणा MPLLCON		0x10
#घोषणा EPLLCON		0x18
#घोषणा EPLLCON_K	0x1C
#घोषणा CLKSRC		0x20
#घोषणा CLKDIV0		0x24
#घोषणा CLKDIV1		0x28
#घोषणा CLKDIV2		0x2C
#घोषणा HCLKCON		0x30
#घोषणा PCLKCON		0x34
#घोषणा SCLKCON		0x38
#घोषणा SWRST		0x44

/* the soc types */
क्रमागत supported_socs अणु
	S3C2416,
	S3C2443,
	S3C2450,
पूर्ण;

अटल व्योम __iomem *reg_base;

/*
 * list of controller रेजिस्टरs to be saved and restored during a
 * suspend/resume cycle.
 */
अटल अचिन्हित दीर्घ s3c2443_clk_regs[] __initdata = अणु
	LOCKCON0,
	LOCKCON1,
	MPLLCON,
	EPLLCON,
	EPLLCON_K,
	CLKSRC,
	CLKDIV0,
	CLKDIV1,
	CLKDIV2,
	PCLKCON,
	HCLKCON,
	SCLKCON,
पूर्ण;

PNAME(epllref_p) = अणु "mpllref", "mpllref", "xti", "ext" पूर्ण;
PNAME(esysclk_p) = अणु "epllref", "epll" पूर्ण;
PNAME(mpllref_p) = अणु "xti", "mdivclk" पूर्ण;
PNAME(msysclk_p) = अणु "mpllref", "mpll" पूर्ण;
PNAME(armclk_p) = अणु "armdiv" , "hclk" पूर्ण;
PNAME(i2s0_p) = अणु "div_i2s0", "ext_i2s", "epllref", "epllref" पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2443_common_muxes[] __initdata = अणु
	MUX(0, "epllref", epllref_p, CLKSRC, 7, 2),
	MUX(ESYSCLK, "esysclk", esysclk_p, CLKSRC, 6, 1),
	MUX(0, "mpllref", mpllref_p, CLKSRC, 3, 1),
	MUX(MSYSCLK, "msysclk", msysclk_p, CLKSRC, 4, 1),
	MUX(ARMCLK, "armclk", armclk_p, CLKDIV0, 13, 1),
	MUX(0, "mux_i2s0", i2s0_p, CLKSRC, 14, 2),
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable hclk_d[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable mभागclk_d[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 3 पूर्ण,
	अणु .val = 2, .भाग = 5 पूर्ण,
	अणु .val = 3, .भाग = 7 पूर्ण,
	अणु .val = 4, .भाग = 9 पूर्ण,
	अणु .val = 5, .भाग = 11 पूर्ण,
	अणु .val = 6, .भाग = 13 पूर्ण,
	अणु .val = 7, .भाग = 15 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c2443_common_भागiders[] __initdata = अणु
	DIV_T(0, "mdivclk", "xti", CLKDIV0, 6, 3, mभागclk_d),
	DIV(0, "prediv", "msysclk", CLKDIV0, 4, 2),
	DIV_T(HCLK, "hclk", "prediv", CLKDIV0, 0, 2, hclk_d),
	DIV(PCLK, "pclk", "hclk", CLKDIV0, 2, 1),
	DIV(0, "div_hsspi0_epll", "esysclk", CLKDIV1, 24, 2),
	DIV(0, "div_fimd", "esysclk", CLKDIV1, 16, 8),
	DIV(0, "div_i2s0", "esysclk", CLKDIV1, 12, 4),
	DIV(0, "div_uart", "esysclk", CLKDIV1, 8, 4),
	DIV(0, "div_hsmmc1", "esysclk", CLKDIV1, 6, 2),
	DIV(0, "div_usbhost", "esysclk", CLKDIV1, 4, 2),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2443_common_gates[] __initdata = अणु
	GATE(SCLK_HSMMC_EXT, "sclk_hsmmcext", "ext", SCLKCON, 13, 0, 0),
	GATE(SCLK_HSMMC1, "sclk_hsmmc1", "div_hsmmc1", SCLKCON, 12, 0, 0),
	GATE(SCLK_FIMD, "sclk_fimd", "div_fimd", SCLKCON, 10, 0, 0),
	GATE(SCLK_I2S0, "sclk_i2s0", "mux_i2s0", SCLKCON, 9, 0, 0),
	GATE(SCLK_UART, "sclk_uart", "div_uart", SCLKCON, 8, 0, 0),
	GATE(SCLK_USBH, "sclk_usbhost", "div_usbhost", SCLKCON, 1, 0, 0),
	GATE(HCLK_DRAM, "dram", "hclk", HCLKCON, 19, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_SSMC, "ssmc", "hclk", HCLKCON, 18, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_HSMMC1, "hsmmc1", "hclk", HCLKCON, 16, 0, 0),
	GATE(HCLK_USBD, "usb-device", "hclk", HCLKCON, 12, 0, 0),
	GATE(HCLK_USBH, "usb-host", "hclk", HCLKCON, 11, 0, 0),
	GATE(HCLK_LCD, "lcd", "hclk", HCLKCON, 9, 0, 0),
	GATE(HCLK_DMA5, "dma5", "hclk", HCLKCON, 5, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA4, "dma4", "hclk", HCLKCON, 4, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA3, "dma3", "hclk", HCLKCON, 3, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA2, "dma2", "hclk", HCLKCON, 2, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA1, "dma1", "hclk", HCLKCON, 1, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA0, "dma0", "hclk", HCLKCON, 0, CLK_IGNORE_UNUSED, 0),
	GATE(PCLK_GPIO, "gpio", "pclk", PCLKCON, 13, CLK_IGNORE_UNUSED, 0),
	GATE(PCLK_RTC, "rtc", "pclk", PCLKCON, 12, 0, 0),
	GATE(PCLK_WDT, "wdt", "pclk", PCLKCON, 11, 0, 0),
	GATE(PCLK_PWM, "pwm", "pclk", PCLKCON, 10, 0, 0),
	GATE(PCLK_I2S0, "i2s0", "pclk", PCLKCON, 9, 0, 0),
	GATE(PCLK_AC97, "ac97", "pclk", PCLKCON, 8, 0, 0),
	GATE(PCLK_ADC, "adc", "pclk", PCLKCON, 7, 0, 0),
	GATE(PCLK_SPI0, "spi0", "pclk", PCLKCON, 6, 0, 0),
	GATE(PCLK_I2C0, "i2c0", "pclk", PCLKCON, 4, 0, 0),
	GATE(PCLK_UART3, "uart3", "pclk", PCLKCON, 3, 0, 0),
	GATE(PCLK_UART2, "uart2", "pclk", PCLKCON, 2, 0, 0),
	GATE(PCLK_UART1, "uart1", "pclk", PCLKCON, 1, 0, 0),
	GATE(PCLK_UART0, "uart0", "pclk", PCLKCON, 0, 0, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c2443_common_aliases[] __initdata = अणु
	ALIAS(MSYSCLK, शून्य, "msysclk"),
	ALIAS(ARMCLK, शून्य, "armclk"),
	ALIAS(MPLL, शून्य, "mpll"),
	ALIAS(EPLL, शून्य, "epll"),
	ALIAS(HCLK, शून्य, "hclk"),
	ALIAS(HCLK_SSMC, शून्य, "nand"),
	ALIAS(PCLK_UART0, "s3c2440-uart.0", "uart"),
	ALIAS(PCLK_UART1, "s3c2440-uart.1", "uart"),
	ALIAS(PCLK_UART2, "s3c2440-uart.2", "uart"),
	ALIAS(PCLK_UART3, "s3c2440-uart.3", "uart"),
	ALIAS(PCLK_UART0, "s3c2440-uart.0", "clk_uart_baud2"),
	ALIAS(PCLK_UART1, "s3c2440-uart.1", "clk_uart_baud2"),
	ALIAS(PCLK_UART2, "s3c2440-uart.2", "clk_uart_baud2"),
	ALIAS(PCLK_UART3, "s3c2440-uart.3", "clk_uart_baud2"),
	ALIAS(SCLK_UART, शून्य, "clk_uart_baud3"),
	ALIAS(PCLK_PWM, शून्य, "timers"),
	ALIAS(PCLK_RTC, शून्य, "rtc"),
	ALIAS(PCLK_WDT, शून्य, "watchdog"),
	ALIAS(PCLK_ADC, शून्य, "adc"),
	ALIAS(PCLK_I2C0, "s3c2410-i2c.0", "i2c"),
	ALIAS(HCLK_USBD, शून्य, "usb-device"),
	ALIAS(HCLK_USBH, शून्य, "usb-host"),
	ALIAS(SCLK_USBH, शून्य, "usb-bus-host"),
	ALIAS(PCLK_SPI0, "s3c2443-spi.0", "spi"),
	ALIAS(PCLK_SPI0, "s3c2443-spi.0", "spi_busclk0"),
	ALIAS(HCLK_HSMMC1, "s3c-sdhci.1", "hsmmc"),
	ALIAS(HCLK_HSMMC1, "s3c-sdhci.1", "mmc_busclk.0"),
	ALIAS(PCLK_I2S0, "samsung-i2s.0", "iis"),
	ALIAS(SCLK_I2S0, शून्य, "i2s-if"),
	ALIAS(HCLK_LCD, शून्य, "lcd"),
	ALIAS(SCLK_FIMD, शून्य, "sclk_fimd"),
पूर्ण;

/* S3C2416 specअगरic घड़ीs */

अटल काष्ठा samsung_pll_घड़ी s3c2416_pll_clks[] __initdata = अणु
	PLL(pll_6552_s3c2416, MPLL, "mpll", "mpllref", LOCKCON0, MPLLCON, शून्य),
	PLL(pll_6553, EPLL, "epll", "epllref", LOCKCON1, EPLLCON, शून्य),
पूर्ण;

PNAME(s3c2416_hsmmc0_p) = अणु "sclk_hsmmc0", "sclk_hsmmcext" पूर्ण;
PNAME(s3c2416_hsmmc1_p) = अणु "sclk_hsmmc1", "sclk_hsmmcext" पूर्ण;
PNAME(s3c2416_hsspi0_p) = अणु "hsspi0_epll", "hsspi0_mpll" पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable armभाग_s3c2416_d[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 3 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 5, .भाग = 6 पूर्ण,
	अणु .val = 7, .भाग = 8 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c2416_भागiders[] __initdata = अणु
	DIV_T(ARMDIV, "armdiv", "msysclk", CLKDIV0, 9, 3, armभाग_s3c2416_d),
	DIV(0, "div_hsspi0_mpll", "msysclk", CLKDIV2, 0, 4),
	DIV(0, "div_hsmmc0", "esysclk", CLKDIV2, 6, 2),
पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2416_muxes[] __initdata = अणु
	MUX(MUX_HSMMC0, "mux_hsmmc0", s3c2416_hsmmc0_p, CLKSRC, 16, 1),
	MUX(MUX_HSMMC1, "mux_hsmmc1", s3c2416_hsmmc1_p, CLKSRC, 17, 1),
	MUX(MUX_HSSPI0, "mux_hsspi0", s3c2416_hsspi0_p, CLKSRC, 18, 1),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2416_gates[] __initdata = अणु
	GATE(0, "hsspi0_mpll", "div_hsspi0_mpll", SCLKCON, 19, 0, 0),
	GATE(0, "hsspi0_epll", "div_hsspi0_epll", SCLKCON, 14, 0, 0),
	GATE(0, "sclk_hsmmc0", "div_hsmmc0", SCLKCON, 6, 0, 0),
	GATE(HCLK_2D, "2d", "hclk", HCLKCON, 20, 0, 0),
	GATE(HCLK_HSMMC0, "hsmmc0", "hclk", HCLKCON, 15, 0, 0),
	GATE(HCLK_IROM, "irom", "hclk", HCLKCON, 13, CLK_IGNORE_UNUSED, 0),
	GATE(PCLK_PCM, "pcm", "pclk", PCLKCON, 19, 0, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c2416_aliases[] __initdata = अणु
	ALIAS(HCLK_HSMMC0, "s3c-sdhci.0", "hsmmc"),
	ALIAS(HCLK_HSMMC0, "s3c-sdhci.0", "mmc_busclk.0"),
	ALIAS(MUX_HSMMC0, "s3c-sdhci.0", "mmc_busclk.2"),
	ALIAS(MUX_HSMMC1, "s3c-sdhci.1", "mmc_busclk.2"),
	ALIAS(MUX_HSSPI0, "s3c2443-spi.0", "spi_busclk2"),
	ALIAS(ARMDIV, शून्य, "armdiv"),
पूर्ण;

/* S3C2443 specअगरic घड़ीs */

अटल काष्ठा samsung_pll_घड़ी s3c2443_pll_clks[] __initdata = अणु
	PLL(pll_3000, MPLL, "mpll", "mpllref", LOCKCON0, MPLLCON, शून्य),
	PLL(pll_2126, EPLL, "epll", "epllref", LOCKCON1, EPLLCON, शून्य),
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable armभाग_s3c2443_d[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 8, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 3 पूर्ण,
	अणु .val = 9, .भाग = 4 पूर्ण,
	अणु .val = 10, .भाग = 6 पूर्ण,
	अणु .val = 11, .भाग = 8 पूर्ण,
	अणु .val = 13, .भाग = 12 पूर्ण,
	अणु .val = 15, .भाग = 16 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c2443_भागiders[] __initdata = अणु
	DIV_T(ARMDIV, "armdiv", "msysclk", CLKDIV0, 9, 4, armभाग_s3c2443_d),
	DIV(0, "div_cam", "esysclk", CLKDIV1, 26, 4),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2443_gates[] __initdata = अणु
	GATE(SCLK_HSSPI0, "sclk_hsspi0", "div_hsspi0_epll", SCLKCON, 14, 0, 0),
	GATE(SCLK_CAM, "sclk_cam", "div_cam", SCLKCON, 11, 0, 0),
	GATE(HCLK_CFC, "cfc", "hclk", HCLKCON, 17, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_CAM, "cam", "hclk", HCLKCON, 8, 0, 0),
	GATE(PCLK_SPI1, "spi1", "pclk", PCLKCON, 15, 0, 0),
	GATE(PCLK_SDI, "sdi", "pclk", PCLKCON, 5, 0, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c2443_aliases[] __initdata = अणु
	ALIAS(SCLK_HSSPI0, "s3c2443-spi.0", "spi_busclk2"),
	ALIAS(SCLK_HSMMC1, "s3c-sdhci.1", "mmc_busclk.2"),
	ALIAS(SCLK_CAM, शून्य, "camif-upll"),
	ALIAS(PCLK_SPI1, "s3c2410-spi.0", "spi"),
	ALIAS(PCLK_SDI, शून्य, "sdi"),
	ALIAS(HCLK_CFC, शून्य, "cfc"),
	ALIAS(ARMDIV, शून्य, "armdiv"),
पूर्ण;

/* S3C2450 specअगरic घड़ीs */

PNAME(s3c2450_cam_p) = अणु "div_cam", "hclk" पूर्ण;
PNAME(s3c2450_hsspi1_p) = अणु "hsspi1_epll", "hsspi1_mpll" पूर्ण;
PNAME(i2s1_p) = अणु "div_i2s1", "ext_i2s", "epllref", "epllref" पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c2450_भागiders[] __initdata = अणु
	DIV(0, "div_cam", "esysclk", CLKDIV1, 26, 4),
	DIV(0, "div_hsspi1_epll", "esysclk", CLKDIV2, 24, 2),
	DIV(0, "div_hsspi1_mpll", "msysclk", CLKDIV2, 16, 4),
	DIV(0, "div_i2s1", "esysclk", CLKDIV2, 12, 4),
पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2450_muxes[] __initdata = अणु
	MUX(0, "mux_cam", s3c2450_cam_p, CLKSRC, 20, 1),
	MUX(MUX_HSSPI1, "mux_hsspi1", s3c2450_hsspi1_p, CLKSRC, 19, 1),
	MUX(0, "mux_i2s1", i2s1_p, CLKSRC, 12, 2),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2450_gates[] __initdata = अणु
	GATE(SCLK_I2S1, "sclk_i2s1", "div_i2s1", SCLKCON, 5, 0, 0),
	GATE(HCLK_CFC, "cfc", "hclk", HCLKCON, 17, 0, 0),
	GATE(HCLK_CAM, "cam", "hclk", HCLKCON, 8, 0, 0),
	GATE(HCLK_DMA7, "dma7", "hclk", HCLKCON, 7, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA6, "dma6", "hclk", HCLKCON, 6, CLK_IGNORE_UNUSED, 0),
	GATE(PCLK_I2S1, "i2s1", "pclk", PCLKCON, 17, 0, 0),
	GATE(PCLK_I2C1, "i2c1", "pclk", PCLKCON, 16, 0, 0),
	GATE(PCLK_SPI1, "spi1", "pclk", PCLKCON, 14, 0, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c2450_aliases[] __initdata = अणु
	ALIAS(PCLK_SPI1, "s3c2443-spi.1", "spi"),
	ALIAS(PCLK_SPI1, "s3c2443-spi.1", "spi_busclk0"),
	ALIAS(MUX_HSSPI1, "s3c2443-spi.1", "spi_busclk2"),
	ALIAS(PCLK_I2C1, "s3c2410-i2c.1", "i2c"),
पूर्ण;

अटल पूर्णांक s3c2443_restart(काष्ठा notअगरier_block *this,
			   अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	__raw_ग_लिखोl(0x533c2443, reg_base + SWRST);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block s3c2443_restart_handler = अणु
	.notअगरier_call = s3c2443_restart,
	.priority = 129,
पूर्ण;

/*
 * fixed rate घड़ीs generated outside the soc
 * Only necessary until the devicetree-move is complete
 */
अटल काष्ठा samsung_fixed_rate_घड़ी s3c2443_common_frate_clks[] __initdata = अणु
	FRATE(0, "xti", शून्य, 0, 0),
	FRATE(0, "ext", शून्य, 0, 0),
	FRATE(0, "ext_i2s", शून्य, 0, 0),
	FRATE(0, "ext_uart", शून्य, 0, 0),
पूर्ण;

अटल व्योम __init s3c2443_common_clk_रेजिस्टर_fixed_ext(
		काष्ठा samsung_clk_provider *ctx, अचिन्हित दीर्घ xti_f)
अणु
	s3c2443_common_frate_clks[0].fixed_rate = xti_f;
	samsung_clk_रेजिस्टर_fixed_rate(ctx, s3c2443_common_frate_clks,
				ARRAY_SIZE(s3c2443_common_frate_clks));
पूर्ण

व्योम __init s3c2443_common_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xti_f,
				    पूर्णांक current_soc,
				    व्योम __iomem *base)
अणु
	काष्ठा samsung_clk_provider *ctx;
	पूर्णांक ret;
	reg_base = base;

	अगर (np) अणु
		reg_base = of_iomap(np, 0);
		अगर (!reg_base)
			panic("%s: failed to map registers\n", __func__);
	पूर्ण

	ctx = samsung_clk_init(np, reg_base, NR_CLKS);

	/* Register बाह्यal घड़ीs only in non-dt हालs */
	अगर (!np)
		s3c2443_common_clk_रेजिस्टर_fixed_ext(ctx, xti_f);

	/* Register PLLs. */
	अगर (current_soc == S3C2416 || current_soc == S3C2450)
		samsung_clk_रेजिस्टर_pll(ctx, s3c2416_pll_clks,
				ARRAY_SIZE(s3c2416_pll_clks), reg_base);
	अन्यथा
		samsung_clk_रेजिस्टर_pll(ctx, s3c2443_pll_clks,
				ARRAY_SIZE(s3c2443_pll_clks), reg_base);

	/* Register common पूर्णांकernal घड़ीs. */
	samsung_clk_रेजिस्टर_mux(ctx, s3c2443_common_muxes,
			ARRAY_SIZE(s3c2443_common_muxes));
	samsung_clk_रेजिस्टर_भाग(ctx, s3c2443_common_भागiders,
			ARRAY_SIZE(s3c2443_common_भागiders));
	samsung_clk_रेजिस्टर_gate(ctx, s3c2443_common_gates,
		ARRAY_SIZE(s3c2443_common_gates));
	samsung_clk_रेजिस्टर_alias(ctx, s3c2443_common_aliases,
		ARRAY_SIZE(s3c2443_common_aliases));

	/* Register SoC-specअगरic घड़ीs. */
	चयन (current_soc) अणु
	हाल S3C2450:
		samsung_clk_रेजिस्टर_भाग(ctx, s3c2450_भागiders,
				ARRAY_SIZE(s3c2450_भागiders));
		samsung_clk_रेजिस्टर_mux(ctx, s3c2450_muxes,
				ARRAY_SIZE(s3c2450_muxes));
		samsung_clk_रेजिस्टर_gate(ctx, s3c2450_gates,
				ARRAY_SIZE(s3c2450_gates));
		samsung_clk_रेजिस्टर_alias(ctx, s3c2450_aliases,
				ARRAY_SIZE(s3c2450_aliases));
		fallthrough;	/* as s3c2450 extends the s3c2416 घड़ीs */
	हाल S3C2416:
		samsung_clk_रेजिस्टर_भाग(ctx, s3c2416_भागiders,
				ARRAY_SIZE(s3c2416_भागiders));
		samsung_clk_रेजिस्टर_mux(ctx, s3c2416_muxes,
				ARRAY_SIZE(s3c2416_muxes));
		samsung_clk_रेजिस्टर_gate(ctx, s3c2416_gates,
				ARRAY_SIZE(s3c2416_gates));
		samsung_clk_रेजिस्टर_alias(ctx, s3c2416_aliases,
				ARRAY_SIZE(s3c2416_aliases));
		अवरोध;
	हाल S3C2443:
		samsung_clk_रेजिस्टर_भाग(ctx, s3c2443_भागiders,
				ARRAY_SIZE(s3c2443_भागiders));
		samsung_clk_रेजिस्टर_gate(ctx, s3c2443_gates,
				ARRAY_SIZE(s3c2443_gates));
		samsung_clk_रेजिस्टर_alias(ctx, s3c2443_aliases,
				ARRAY_SIZE(s3c2443_aliases));
		अवरोध;
	पूर्ण

	samsung_clk_sleep_init(reg_base, s3c2443_clk_regs,
			       ARRAY_SIZE(s3c2443_clk_regs));

	samsung_clk_of_add_provider(np, ctx);

	ret = रेजिस्टर_restart_handler(&s3c2443_restart_handler);
	अगर (ret)
		pr_warn("cannot register restart handler, %d\n", ret);
पूर्ण

अटल व्योम __init s3c2416_clk_init(काष्ठा device_node *np)
अणु
	s3c2443_common_clk_init(np, 0, S3C2416, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2416_clk, "samsung,s3c2416-clock", s3c2416_clk_init);

अटल व्योम __init s3c2443_clk_init(काष्ठा device_node *np)
अणु
	s3c2443_common_clk_init(np, 0, S3C2443, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2443_clk, "samsung,s3c2443-clock", s3c2443_clk_init);

अटल व्योम __init s3c2450_clk_init(काष्ठा device_node *np)
अणु
	s3c2443_common_clk_init(np, 0, S3C2450, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2450_clk, "samsung,s3c2450-clock", s3c2450_clk_init);
