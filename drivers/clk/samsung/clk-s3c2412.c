<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Common Clock Framework support क्रम S3C2412 and S3C2413.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/samsung.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reboot.h>

#समावेश <dt-bindings/घड़ी/s3c2412.h>

#समावेश "clk.h"
#समावेश "clk-pll.h"

#घोषणा LOCKTIME	0x00
#घोषणा MPLLCON		0x04
#घोषणा UPLLCON		0x08
#घोषणा CLKCON		0x0c
#घोषणा CLKDIVN		0x14
#घोषणा CLKSRC		0x1c
#घोषणा SWRST		0x30

अटल व्योम __iomem *reg_base;

/*
 * list of controller रेजिस्टरs to be saved and restored during a
 * suspend/resume cycle.
 */
अटल अचिन्हित दीर्घ s3c2412_clk_regs[] __initdata = अणु
	LOCKTIME,
	MPLLCON,
	UPLLCON,
	CLKCON,
	CLKDIVN,
	CLKSRC,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable भागxti_d[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 4 पूर्ण,
	अणु .val = 3, .भाग = 6 पूर्ण,
	अणु .val = 4, .भाग = 8 पूर्ण,
	अणु .val = 5, .भाग = 10 पूर्ण,
	अणु .val = 6, .भाग = 12 पूर्ण,
	अणु .val = 7, .भाग = 14 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c2412_भागiders[] __initdata = अणु
	DIV_T(0, "div_xti", "xti", CLKSRC, 0, 3, भागxti_d),
	DIV(0, "div_cam", "mux_cam", CLKDIVN, 16, 4),
	DIV(0, "div_i2s", "mux_i2s", CLKDIVN, 12, 4),
	DIV(0, "div_uart", "mux_uart", CLKDIVN, 8, 4),
	DIV(0, "div_usb", "mux_usb", CLKDIVN, 6, 1),
	DIV(0, "div_hclk_half", "hclk", CLKDIVN, 5, 1),
	DIV(ARMDIV, "armdiv", "msysclk", CLKDIVN, 3, 1),
	DIV(PCLK, "pclk", "hclk", CLKDIVN, 2, 1),
	DIV(HCLK, "hclk", "armdiv", CLKDIVN, 0, 2),
पूर्ण;

अटल काष्ठा samsung_fixed_factor_घड़ी s3c2412_ffactor[] __initdata = अणु
	FFACTOR(0, "ff_hclk", "hclk", 2, 1, CLK_SET_RATE_PARENT),
पूर्ण;

/*
 * The first two use the OM[4] setting, which is not पढ़ोable from
 * software, so assume it is set to xti.
 */
PNAME(erefclk_p) = अणु "xti", "xti", "xti", "ext" पूर्ण;
PNAME(urefclk_p) = अणु "xti", "xti", "xti", "ext" पूर्ण;

PNAME(camclk_p) = अणु "usysclk", "hclk" पूर्ण;
PNAME(usbclk_p) = अणु "usysclk", "hclk" पूर्ण;
PNAME(i2sclk_p) = अणु "erefclk", "mpll" पूर्ण;
PNAME(uartclk_p) = अणु "erefclk", "mpll" पूर्ण;
PNAME(usysclk_p) = अणु "urefclk", "upll" पूर्ण;
PNAME(msysclk_p) = अणु "mdivclk", "mpll" पूर्ण;
PNAME(mभागclk_p) = अणु "xti", "div_xti" पूर्ण;
PNAME(armclk_p) = अणु "armdiv", "hclk" पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2412_muxes[] __initdata = अणु
	MUX(0, "erefclk", erefclk_p, CLKSRC, 14, 2),
	MUX(0, "urefclk", urefclk_p, CLKSRC, 12, 2),
	MUX(0, "mux_cam", camclk_p, CLKSRC, 11, 1),
	MUX(0, "mux_usb", usbclk_p, CLKSRC, 10, 1),
	MUX(0, "mux_i2s", i2sclk_p, CLKSRC, 9, 1),
	MUX(0, "mux_uart", uartclk_p, CLKSRC, 8, 1),
	MUX(USYSCLK, "usysclk", usysclk_p, CLKSRC, 5, 1),
	MUX(MSYSCLK, "msysclk", msysclk_p, CLKSRC, 4, 1),
	MUX(MDIVCLK, "mdivclk", mभागclk_p, CLKSRC, 3, 1),
	MUX(ARMCLK, "armclk", armclk_p, CLKDIVN, 4, 1),
पूर्ण;

अटल काष्ठा samsung_pll_घड़ी s3c2412_plls[] __initdata = अणु
	PLL(pll_s3c2440_mpll, MPLL, "mpll", "xti", LOCKTIME, MPLLCON, शून्य),
	PLL(pll_s3c2410_upll, UPLL, "upll", "urefclk", LOCKTIME, UPLLCON, शून्य),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2412_gates[] __initdata = अणु
	GATE(PCLK_WDT, "wdt", "pclk", CLKCON, 28, 0, 0),
	GATE(PCLK_SPI, "spi", "pclk", CLKCON, 27, 0, 0),
	GATE(PCLK_I2S, "i2s", "pclk", CLKCON, 26, 0, 0),
	GATE(PCLK_I2C, "i2c", "pclk", CLKCON, 25, 0, 0),
	GATE(PCLK_ADC, "adc", "pclk", CLKCON, 24, 0, 0),
	GATE(PCLK_RTC, "rtc", "pclk", CLKCON, 23, 0, 0),
	GATE(PCLK_GPIO, "gpio", "pclk", CLKCON, 22, CLK_IGNORE_UNUSED, 0),
	GATE(PCLK_UART2, "uart2", "pclk", CLKCON, 21, 0, 0),
	GATE(PCLK_UART1, "uart1", "pclk", CLKCON, 20, 0, 0),
	GATE(PCLK_UART0, "uart0", "pclk", CLKCON, 19, 0, 0),
	GATE(PCLK_SDI, "sdi", "pclk", CLKCON, 18, 0, 0),
	GATE(PCLK_PWM, "pwm", "pclk", CLKCON, 17, 0, 0),
	GATE(PCLK_USBD, "usb-device", "pclk", CLKCON, 16, 0, 0),
	GATE(SCLK_CAM, "sclk_cam", "div_cam", CLKCON, 15, 0, 0),
	GATE(SCLK_UART, "sclk_uart", "div_uart", CLKCON, 14, 0, 0),
	GATE(SCLK_I2S, "sclk_i2s", "div_i2s", CLKCON, 13, 0, 0),
	GATE(SCLK_USBH, "sclk_usbh", "div_usb", CLKCON, 12, 0, 0),
	GATE(SCLK_USBD, "sclk_usbd", "div_usb", CLKCON, 11, 0, 0),
	GATE(HCLK_HALF, "hclk_half", "div_hclk_half", CLKCON, 10, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_X2, "hclkx2", "ff_hclk", CLKCON, 9, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_SDRAM, "sdram", "hclk", CLKCON, 8, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_USBH, "usb-host", "hclk", CLKCON, 6, 0, 0),
	GATE(HCLK_LCD, "lcd", "hclk", CLKCON, 5, 0, 0),
	GATE(HCLK_न_अंकD, "nand", "hclk", CLKCON, 4, 0, 0),
	GATE(HCLK_DMA3, "dma3", "hclk", CLKCON, 3, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA2, "dma2", "hclk", CLKCON, 2, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA1, "dma1", "hclk", CLKCON, 1, CLK_IGNORE_UNUSED, 0),
	GATE(HCLK_DMA0, "dma0", "hclk", CLKCON, 0, CLK_IGNORE_UNUSED, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c2412_aliases[] __initdata = अणु
	ALIAS(PCLK_UART0, "s3c2412-uart.0", "uart"),
	ALIAS(PCLK_UART1, "s3c2412-uart.1", "uart"),
	ALIAS(PCLK_UART2, "s3c2412-uart.2", "uart"),
	ALIAS(PCLK_UART0, "s3c2412-uart.0", "clk_uart_baud2"),
	ALIAS(PCLK_UART1, "s3c2412-uart.1", "clk_uart_baud2"),
	ALIAS(PCLK_UART2, "s3c2412-uart.2", "clk_uart_baud2"),
	ALIAS(SCLK_UART, शून्य, "clk_uart_baud3"),
	ALIAS(PCLK_I2C, "s3c2410-i2c.0", "i2c"),
	ALIAS(PCLK_ADC, शून्य, "adc"),
	ALIAS(PCLK_RTC, शून्य, "rtc"),
	ALIAS(PCLK_PWM, शून्य, "timers"),
	ALIAS(HCLK_LCD, शून्य, "lcd"),
	ALIAS(PCLK_USBD, शून्य, "usb-device"),
	ALIAS(SCLK_USBD, शून्य, "usb-bus-gadget"),
	ALIAS(HCLK_USBH, शून्य, "usb-host"),
	ALIAS(SCLK_USBH, शून्य, "usb-bus-host"),
	ALIAS(ARMCLK, शून्य, "armclk"),
	ALIAS(HCLK, शून्य, "hclk"),
	ALIAS(MPLL, शून्य, "mpll"),
	ALIAS(MSYSCLK, शून्य, "fclk"),
पूर्ण;

अटल पूर्णांक s3c2412_restart(काष्ठा notअगरier_block *this,
			   अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	/* errata "Watch-dog/Software Reset Problem" specअगरies that
	 * this reset must be करोne with the SYSCLK sourced from
	 * EXTCLK instead of FOUT to aव्योम a glitch in the reset
	 * mechanism.
	 *
	 * See the watchकरोg section of the S3C2412 manual क्रम more
	 * inक्रमmation on this fix.
	 */

	__raw_ग_लिखोl(0x00, reg_base + CLKSRC);
	__raw_ग_लिखोl(0x533C2412, reg_base + SWRST);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block s3c2412_restart_handler = अणु
	.notअगरier_call = s3c2412_restart,
	.priority = 129,
पूर्ण;

/*
 * fixed rate घड़ीs generated outside the soc
 * Only necessary until the devicetree-move is complete
 */
#घोषणा XTI	1
अटल काष्ठा samsung_fixed_rate_घड़ी s3c2412_common_frate_clks[] __initdata = अणु
	FRATE(XTI, "xti", शून्य, 0, 0),
	FRATE(0, "ext", शून्य, 0, 0),
पूर्ण;

अटल व्योम __init s3c2412_common_clk_रेजिस्टर_fixed_ext(
		काष्ठा samsung_clk_provider *ctx,
		अचिन्हित दीर्घ xti_f, अचिन्हित दीर्घ ext_f)
अणु
	/* xtal alias is necessary क्रम the current cpufreq driver */
	काष्ठा samsung_घड़ी_alias xti_alias = ALIAS(XTI, शून्य, "xtal");

	s3c2412_common_frate_clks[0].fixed_rate = xti_f;
	s3c2412_common_frate_clks[1].fixed_rate = ext_f;
	samsung_clk_रेजिस्टर_fixed_rate(ctx, s3c2412_common_frate_clks,
				ARRAY_SIZE(s3c2412_common_frate_clks));

	samsung_clk_रेजिस्टर_alias(ctx, &xti_alias, 1);
पूर्ण

व्योम __init s3c2412_common_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xti_f,
				    अचिन्हित दीर्घ ext_f, व्योम __iomem *base)
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
		s3c2412_common_clk_रेजिस्टर_fixed_ext(ctx, xti_f, ext_f);

	/* Register PLLs. */
	samsung_clk_रेजिस्टर_pll(ctx, s3c2412_plls, ARRAY_SIZE(s3c2412_plls),
				 reg_base);

	/* Register common पूर्णांकernal घड़ीs. */
	samsung_clk_रेजिस्टर_mux(ctx, s3c2412_muxes, ARRAY_SIZE(s3c2412_muxes));
	samsung_clk_रेजिस्टर_भाग(ctx, s3c2412_भागiders,
					  ARRAY_SIZE(s3c2412_भागiders));
	samsung_clk_रेजिस्टर_gate(ctx, s3c2412_gates,
					ARRAY_SIZE(s3c2412_gates));
	samsung_clk_रेजिस्टर_fixed_factor(ctx, s3c2412_ffactor,
					  ARRAY_SIZE(s3c2412_ffactor));
	samsung_clk_रेजिस्टर_alias(ctx, s3c2412_aliases,
				   ARRAY_SIZE(s3c2412_aliases));

	samsung_clk_sleep_init(reg_base, s3c2412_clk_regs,
			       ARRAY_SIZE(s3c2412_clk_regs));

	samsung_clk_of_add_provider(np, ctx);

	ret = रेजिस्टर_restart_handler(&s3c2412_restart_handler);
	अगर (ret)
		pr_warn("cannot register restart handler, %d\n", ret);
पूर्ण

अटल व्योम __init s3c2412_clk_init(काष्ठा device_node *np)
अणु
	s3c2412_common_clk_init(np, 0, 0, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2412_clk, "samsung,s3c2412-clock", s3c2412_clk_init);
