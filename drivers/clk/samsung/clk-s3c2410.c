<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Common Clock Framework support क्रम S3C2410 and following SoCs.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/samsung.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <dt-bindings/घड़ी/s3c2410.h>

#समावेश "clk.h"
#समावेश "clk-pll.h"

#घोषणा LOCKTIME	0x00
#घोषणा MPLLCON		0x04
#घोषणा UPLLCON		0x08
#घोषणा CLKCON		0x0c
#घोषणा CLKSLOW		0x10
#घोषणा CLKDIVN		0x14
#घोषणा CAMDIVN		0x18

/* the soc types */
क्रमागत supported_socs अणु
	S3C2410,
	S3C2440,
	S3C2442,
पूर्ण;

/* list of PLLs to be रेजिस्टरed */
क्रमागत s3c2410_plls अणु
	mpll, upll,
पूर्ण;

अटल व्योम __iomem *reg_base;

/*
 * list of controller रेजिस्टरs to be saved and restored during a
 * suspend/resume cycle.
 */
अटल अचिन्हित दीर्घ s3c2410_clk_regs[] __initdata = अणु
	LOCKTIME,
	MPLLCON,
	UPLLCON,
	CLKCON,
	CLKSLOW,
	CLKDIVN,
	CAMDIVN,
पूर्ण;

PNAME(fclk_p) = अणु "mpll", "div_slow" पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2410_common_muxes[] __initdata = अणु
	MUX(FCLK, "fclk", fclk_p, CLKSLOW, 4, 1),
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable भागslow_d[] = अणु
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

अटल काष्ठा samsung_भाग_घड़ी s3c2410_common_भागiders[] __initdata = अणु
	DIV_T(0, "div_slow", "xti", CLKSLOW, 0, 3, भागslow_d),
	DIV(PCLK, "pclk", "hclk", CLKDIVN, 0, 1),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2410_common_gates[] __initdata = अणु
	GATE(PCLK_SPI, "spi", "pclk", CLKCON, 18, 0, 0),
	GATE(PCLK_I2S, "i2s", "pclk", CLKCON, 17, 0, 0),
	GATE(PCLK_I2C, "i2c", "pclk", CLKCON, 16, 0, 0),
	GATE(PCLK_ADC, "adc", "pclk", CLKCON, 15, 0, 0),
	GATE(PCLK_RTC, "rtc", "pclk", CLKCON, 14, 0, 0),
	GATE(PCLK_GPIO, "gpio", "pclk", CLKCON, 13, CLK_IGNORE_UNUSED, 0),
	GATE(PCLK_UART2, "uart2", "pclk", CLKCON, 12, 0, 0),
	GATE(PCLK_UART1, "uart1", "pclk", CLKCON, 11, 0, 0),
	GATE(PCLK_UART0, "uart0", "pclk", CLKCON, 10, 0, 0),
	GATE(PCLK_SDI, "sdi", "pclk", CLKCON, 9, 0, 0),
	GATE(PCLK_PWM, "pwm", "pclk", CLKCON, 8, 0, 0),
	GATE(HCLK_USBD, "usb-device", "hclk", CLKCON, 7, 0, 0),
	GATE(HCLK_USBH, "usb-host", "hclk", CLKCON, 6, 0, 0),
	GATE(HCLK_LCD, "lcd", "hclk", CLKCON, 5, 0, 0),
	GATE(HCLK_न_अंकD, "nand", "hclk", CLKCON, 4, 0, 0),
पूर्ण;

/* should be added _after_ the soc-specअगरic घड़ीs are created */
अटल काष्ठा samsung_घड़ी_alias s3c2410_common_aliases[] __initdata = अणु
	ALIAS(PCLK_I2C, "s3c2410-i2c.0", "i2c"),
	ALIAS(PCLK_ADC, शून्य, "adc"),
	ALIAS(PCLK_RTC, शून्य, "rtc"),
	ALIAS(PCLK_PWM, शून्य, "timers"),
	ALIAS(HCLK_LCD, शून्य, "lcd"),
	ALIAS(HCLK_USBD, शून्य, "usb-device"),
	ALIAS(HCLK_USBH, शून्य, "usb-host"),
	ALIAS(UCLK, शून्य, "usb-bus-host"),
	ALIAS(UCLK, शून्य, "usb-bus-gadget"),
	ALIAS(ARMCLK, शून्य, "armclk"),
	ALIAS(UCLK, शून्य, "uclk"),
	ALIAS(HCLK, शून्य, "hclk"),
	ALIAS(MPLL, शून्य, "mpll"),
	ALIAS(FCLK, शून्य, "fclk"),
	ALIAS(PCLK, शून्य, "watchdog"),
	ALIAS(PCLK_SDI, शून्य, "sdi"),
	ALIAS(HCLK_न_अंकD, शून्य, "nand"),
	ALIAS(PCLK_I2S, शून्य, "iis"),
	ALIAS(PCLK_I2C, शून्य, "i2c"),
पूर्ण;

/* S3C2410 specअगरic घड़ीs */

अटल काष्ठा samsung_pll_rate_table pll_s3c2410_12mhz_tbl[] __initdata = अणु
	/* sorted in descending order */
	/* 2410A extras */
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 270000000, 127, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 268000000, 126, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 266000000, 125, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 226000000, 105, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 210000000, 132, 2, 1),
	/* 2410 common */
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 202800000, 161, 3, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 192000000, 88, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 186000000, 85, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 180000000, 82, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 170000000, 77, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 158000000, 71, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 152000000, 68, 1, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 147000000, 90, 2, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 135000000, 82, 2, 1),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 124000000, 116, 1, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 118500000, 150, 2, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 113000000, 105, 1, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 101250000, 127, 2, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 90000000, 112, 2, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 84750000, 105, 2, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 79000000, 71, 1, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 67500000, 82, 2, 2),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 56250000, 142, 2, 3),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 48000000, 120, 2, 3),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 50700000, 161, 3, 3),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 45000000, 82, 1, 3),
	PLL_S3C2410_MPLL_RATE(12 * MHZ, 33750000, 82, 2, 3),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_pll_घड़ी s3c2410_plls[] __initdata = अणु
	[mpll] = PLL(pll_s3c2410_mpll, MPLL, "mpll", "xti",
						LOCKTIME, MPLLCON, शून्य),
	[upll] = PLL(pll_s3c2410_upll, UPLL, "upll", "xti",
						LOCKTIME, UPLLCON, शून्य),
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c2410_भागiders[] __initdata = अणु
	DIV(HCLK, "hclk", "mpll", CLKDIVN, 1, 1),
पूर्ण;

अटल काष्ठा samsung_fixed_factor_घड़ी s3c2410_ffactor[] __initdata = अणु
	/*
	 * armclk is directly supplied by the fclk, without
	 * चयनing possibility like on the s3c244x below.
	 */
	FFACTOR(ARMCLK, "armclk", "fclk", 1, 1, 0),

	/* uclk is fed from the unmodअगरied upll */
	FFACTOR(UCLK, "uclk", "upll", 1, 1, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c2410_aliases[] __initdata = अणु
	ALIAS(PCLK_UART0, "s3c2410-uart.0", "uart"),
	ALIAS(PCLK_UART1, "s3c2410-uart.1", "uart"),
	ALIAS(PCLK_UART2, "s3c2410-uart.2", "uart"),
	ALIAS(PCLK_UART0, "s3c2410-uart.0", "clk_uart_baud0"),
	ALIAS(PCLK_UART1, "s3c2410-uart.1", "clk_uart_baud0"),
	ALIAS(PCLK_UART2, "s3c2410-uart.2", "clk_uart_baud0"),
	ALIAS(UCLK, शून्य, "clk_uart_baud1"),
पूर्ण;

/* S3C244x specअगरic घड़ीs */

अटल काष्ठा samsung_pll_rate_table pll_s3c244x_12mhz_tbl[] __initdata = अणु
	/* sorted in descending order */
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 400000000, 0x5c, 1, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 390000000, 0x7a, 2, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 380000000, 0x57, 1, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 370000000, 0xb1, 4, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 360000000, 0x70, 2, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 350000000, 0xa7, 4, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 340000000, 0x4d, 1, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 330000000, 0x66, 2, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 320000000, 0x98, 4, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 310000000, 0x93, 4, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 300000000, 0x75, 3, 1),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 240000000, 0x70, 1, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 230000000, 0x6b, 1, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 220000000, 0x66, 1, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 210000000, 0x84, 2, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 200000000, 0x5c, 1, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 190000000, 0x57, 1, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 180000000, 0x70, 2, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 170000000, 0x4d, 1, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 160000000, 0x98, 4, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 150000000, 0x75, 3, 2),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 120000000, 0x70, 1, 3),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 110000000, 0x66, 1, 3),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 100000000, 0x5c, 1, 3),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 90000000, 0x70, 2, 3),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 80000000, 0x98, 4, 3),
	PLL_S3C2440_MPLL_RATE(12 * MHZ, 75000000, 0x75, 3, 3),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_pll_घड़ी s3c244x_common_plls[] __initdata = अणु
	[mpll] = PLL(pll_s3c2440_mpll, MPLL, "mpll", "xti",
						LOCKTIME, MPLLCON, शून्य),
	[upll] = PLL(pll_s3c2410_upll, UPLL, "upll", "xti",
						LOCKTIME, UPLLCON, शून्य),
पूर्ण;

PNAME(hclk_p) = अणु "fclk", "div_hclk_2", "div_hclk_4", "div_hclk_3" पूर्ण;
PNAME(armclk_p) = अणु "fclk", "hclk" पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c244x_common_muxes[] __initdata = अणु
	MUX(HCLK, "hclk", hclk_p, CLKDIVN, 1, 2),
	MUX(ARMCLK, "armclk", armclk_p, CAMDIVN, 12, 1),
पूर्ण;

अटल काष्ठा samsung_fixed_factor_घड़ी s3c244x_common_ffactor[] __initdata = अणु
	FFACTOR(0, "div_hclk_2", "fclk", 1, 2, 0),
	FFACTOR(0, "ff_cam", "div_cam", 2, 1, CLK_SET_RATE_PARENT),
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable भाग_hclk_4_d[] = अणु
	अणु .val = 0, .भाग = 4 पूर्ण,
	अणु .val = 1, .भाग = 8 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable भाग_hclk_3_d[] = अणु
	अणु .val = 0, .भाग = 3 पूर्ण,
	अणु .val = 1, .भाग = 6 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी s3c244x_common_भागiders[] __initdata = अणु
	DIV(UCLK, "uclk", "upll", CLKDIVN, 3, 1),
	DIV(0, "div_hclk", "fclk", CLKDIVN, 1, 1),
	DIV_T(0, "div_hclk_4", "fclk", CAMDIVN, 9, 1, भाग_hclk_4_d),
	DIV_T(0, "div_hclk_3", "fclk", CAMDIVN, 8, 1, भाग_hclk_3_d),
	DIV(0, "div_cam", "upll", CAMDIVN, 0, 3),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c244x_common_gates[] __initdata = अणु
	GATE(HCLK_CAM, "cam", "hclk", CLKCON, 19, 0, 0),
पूर्ण;

अटल काष्ठा samsung_घड़ी_alias s3c244x_common_aliases[] __initdata = अणु
	ALIAS(PCLK_UART0, "s3c2440-uart.0", "uart"),
	ALIAS(PCLK_UART1, "s3c2440-uart.1", "uart"),
	ALIAS(PCLK_UART2, "s3c2440-uart.2", "uart"),
	ALIAS(PCLK_UART0, "s3c2440-uart.0", "clk_uart_baud2"),
	ALIAS(PCLK_UART1, "s3c2440-uart.1", "clk_uart_baud2"),
	ALIAS(PCLK_UART2, "s3c2440-uart.2", "clk_uart_baud2"),
	ALIAS(HCLK_CAM, शून्य, "camif"),
	ALIAS(CAMIF, शून्य, "camif-upll"),
पूर्ण;

/* S3C2440 specअगरic घड़ीs */

PNAME(s3c2440_camअगर_p) = अणु "upll", "ff_cam" पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2440_muxes[] __initdata = अणु
	MUX(CAMIF, "camif", s3c2440_camअगर_p, CAMDIVN, 4, 1),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी s3c2440_gates[] __initdata = अणु
	GATE(PCLK_AC97, "ac97", "pclk", CLKCON, 20, 0, 0),
पूर्ण;

/* S3C2442 specअगरic घड़ीs */

अटल काष्ठा samsung_fixed_factor_घड़ी s3c2442_ffactor[] __initdata = अणु
	FFACTOR(0, "upll_3", "upll", 1, 3, 0),
पूर्ण;

PNAME(s3c2442_camअगर_p) = अणु "upll", "ff_cam", "upll", "upll_3" पूर्ण;

अटल काष्ठा samsung_mux_घड़ी s3c2442_muxes[] __initdata = अणु
	MUX(CAMIF, "camif", s3c2442_camअगर_p, CAMDIVN, 4, 2),
पूर्ण;

/*
 * fixed rate घड़ीs generated outside the soc
 * Only necessary until the devicetree-move is complete
 */
#घोषणा XTI	1
अटल काष्ठा samsung_fixed_rate_घड़ी s3c2410_common_frate_clks[] __initdata = अणु
	FRATE(XTI, "xti", शून्य, 0, 0),
पूर्ण;

अटल व्योम __init s3c2410_common_clk_रेजिस्टर_fixed_ext(
		काष्ठा samsung_clk_provider *ctx,
		अचिन्हित दीर्घ xti_f)
अणु
	काष्ठा samsung_घड़ी_alias xti_alias = ALIAS(XTI, शून्य, "xtal");

	s3c2410_common_frate_clks[0].fixed_rate = xti_f;
	samsung_clk_रेजिस्टर_fixed_rate(ctx, s3c2410_common_frate_clks,
				ARRAY_SIZE(s3c2410_common_frate_clks));

	samsung_clk_रेजिस्टर_alias(ctx, &xti_alias, 1);
पूर्ण

व्योम __init s3c2410_common_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xti_f,
				    पूर्णांक current_soc,
				    व्योम __iomem *base)
अणु
	काष्ठा samsung_clk_provider *ctx;
	reg_base = base;

	अगर (np) अणु
		reg_base = of_iomap(np, 0);
		अगर (!reg_base)
			panic("%s: failed to map registers\n", __func__);
	पूर्ण

	ctx = samsung_clk_init(np, reg_base, NR_CLKS);

	/* Register बाह्यal घड़ीs only in non-dt हालs */
	अगर (!np)
		s3c2410_common_clk_रेजिस्टर_fixed_ext(ctx, xti_f);

	अगर (current_soc == S3C2410) अणु
		अगर (_get_rate("xti") == 12 * MHZ) अणु
			s3c2410_plls[mpll].rate_table = pll_s3c2410_12mhz_tbl;
			s3c2410_plls[upll].rate_table = pll_s3c2410_12mhz_tbl;
		पूर्ण

		/* Register PLLs. */
		samsung_clk_रेजिस्टर_pll(ctx, s3c2410_plls,
				ARRAY_SIZE(s3c2410_plls), reg_base);

	पूर्ण अन्यथा अणु /* S3C2440, S3C2442 */
		अगर (_get_rate("xti") == 12 * MHZ) अणु
			/*
			 * plls follow dअगरferent calculation schemes, with the
			 * upll following the same scheme as the s3c2410 plls
			 */
			s3c244x_common_plls[mpll].rate_table =
							pll_s3c244x_12mhz_tbl;
			s3c244x_common_plls[upll].rate_table =
							pll_s3c2410_12mhz_tbl;
		पूर्ण

		/* Register PLLs. */
		samsung_clk_रेजिस्टर_pll(ctx, s3c244x_common_plls,
				ARRAY_SIZE(s3c244x_common_plls), reg_base);
	पूर्ण

	/* Register common पूर्णांकernal घड़ीs. */
	samsung_clk_रेजिस्टर_mux(ctx, s3c2410_common_muxes,
			ARRAY_SIZE(s3c2410_common_muxes));
	samsung_clk_रेजिस्टर_भाग(ctx, s3c2410_common_भागiders,
			ARRAY_SIZE(s3c2410_common_भागiders));
	samsung_clk_रेजिस्टर_gate(ctx, s3c2410_common_gates,
		ARRAY_SIZE(s3c2410_common_gates));

	अगर (current_soc == S3C2440 || current_soc == S3C2442) अणु
		samsung_clk_रेजिस्टर_भाग(ctx, s3c244x_common_भागiders,
				ARRAY_SIZE(s3c244x_common_भागiders));
		samsung_clk_रेजिस्टर_gate(ctx, s3c244x_common_gates,
				ARRAY_SIZE(s3c244x_common_gates));
		samsung_clk_रेजिस्टर_mux(ctx, s3c244x_common_muxes,
				ARRAY_SIZE(s3c244x_common_muxes));
		samsung_clk_रेजिस्टर_fixed_factor(ctx, s3c244x_common_ffactor,
				ARRAY_SIZE(s3c244x_common_ffactor));
	पूर्ण

	/* Register SoC-specअगरic घड़ीs. */
	चयन (current_soc) अणु
	हाल S3C2410:
		samsung_clk_रेजिस्टर_भाग(ctx, s3c2410_भागiders,
				ARRAY_SIZE(s3c2410_भागiders));
		samsung_clk_रेजिस्टर_fixed_factor(ctx, s3c2410_ffactor,
				ARRAY_SIZE(s3c2410_ffactor));
		samsung_clk_रेजिस्टर_alias(ctx, s3c2410_aliases,
			ARRAY_SIZE(s3c2410_aliases));
		अवरोध;
	हाल S3C2440:
		samsung_clk_रेजिस्टर_mux(ctx, s3c2440_muxes,
				ARRAY_SIZE(s3c2440_muxes));
		samsung_clk_रेजिस्टर_gate(ctx, s3c2440_gates,
				ARRAY_SIZE(s3c2440_gates));
		अवरोध;
	हाल S3C2442:
		samsung_clk_रेजिस्टर_mux(ctx, s3c2442_muxes,
				ARRAY_SIZE(s3c2442_muxes));
		samsung_clk_रेजिस्टर_fixed_factor(ctx, s3c2442_ffactor,
				ARRAY_SIZE(s3c2442_ffactor));
		अवरोध;
	पूर्ण

	/*
	 * Register common aliases at the end, as some of the aliased घड़ीs
	 * are SoC specअगरic.
	 */
	samsung_clk_रेजिस्टर_alias(ctx, s3c2410_common_aliases,
		ARRAY_SIZE(s3c2410_common_aliases));

	अगर (current_soc == S3C2440 || current_soc == S3C2442) अणु
		samsung_clk_रेजिस्टर_alias(ctx, s3c244x_common_aliases,
			ARRAY_SIZE(s3c244x_common_aliases));
	पूर्ण

	samsung_clk_sleep_init(reg_base, s3c2410_clk_regs,
			       ARRAY_SIZE(s3c2410_clk_regs));

	samsung_clk_of_add_provider(np, ctx);
पूर्ण

अटल व्योम __init s3c2410_clk_init(काष्ठा device_node *np)
अणु
	s3c2410_common_clk_init(np, 0, S3C2410, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2410_clk, "samsung,s3c2410-clock", s3c2410_clk_init);

अटल व्योम __init s3c2440_clk_init(काष्ठा device_node *np)
अणु
	s3c2410_common_clk_init(np, 0, S3C2440, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2440_clk, "samsung,s3c2440-clock", s3c2440_clk_init);

अटल व्योम __init s3c2442_clk_init(काष्ठा device_node *np)
अणु
	s3c2410_common_clk_init(np, 0, S3C2442, शून्य);
पूर्ण
CLK_OF_DECLARE(s3c2442_clk, "samsung,s3c2442-clock", s3c2442_clk_init);
