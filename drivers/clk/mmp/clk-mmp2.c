<शैली गुरु>
/*
 * mmp2 घड़ी framework source file
 *
 * Copyright (C) 2012 Marvell
 * Chao Xie <xiechao.mail@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/clk/mmp.h>

#समावेश "clk.h"

#घोषणा APBC_RTC	0x0
#घोषणा APBC_TWSI0	0x4
#घोषणा APBC_TWSI1	0x8
#घोषणा APBC_TWSI2	0xc
#घोषणा APBC_TWSI3	0x10
#घोषणा APBC_TWSI4	0x7c
#घोषणा APBC_TWSI5	0x80
#घोषणा APBC_KPC	0x18
#घोषणा APBC_UART0	0x2c
#घोषणा APBC_UART1	0x30
#घोषणा APBC_UART2	0x34
#घोषणा APBC_UART3	0x88
#घोषणा APBC_GPIO	0x38
#घोषणा APBC_PWM0	0x3c
#घोषणा APBC_PWM1	0x40
#घोषणा APBC_PWM2	0x44
#घोषणा APBC_PWM3	0x48
#घोषणा APBC_SSP0	0x50
#घोषणा APBC_SSP1	0x54
#घोषणा APBC_SSP2	0x58
#घोषणा APBC_SSP3	0x5c
#घोषणा APMU_SDH0	0x54
#घोषणा APMU_SDH1	0x58
#घोषणा APMU_SDH2	0xe8
#घोषणा APMU_SDH3	0xec
#घोषणा APMU_USB	0x5c
#घोषणा APMU_DISP0	0x4c
#घोषणा APMU_DISP1	0x110
#घोषणा APMU_CCIC0	0x50
#घोषणा APMU_CCIC1	0xf4
#घोषणा MPMU_UART_PLL	0x14

अटल DEFINE_SPINLOCK(clk_lock);

अटल काष्ठा mmp_clk_factor_masks uart_factor_masks = अणु
	.factor = 2,
	.num_mask = 0x1fff,
	.den_mask = 0x1fff,
	.num_shअगरt = 16,
	.den_shअगरt = 0,
पूर्ण;

अटल काष्ठा mmp_clk_factor_tbl uart_factor_tbl[] = अणु
	अणु.num = 8125, .den = 1536पूर्ण,	/*14.745MHZ */
	अणु.num = 3521, .den = 689पूर्ण,	/*19.23MHZ */
पूर्ण;

अटल स्थिर अक्षर *uart_parent[] = अणु"uart_pll", "vctcxo"पूर्ण;
अटल स्थिर अक्षर *ssp_parent[] = अणु"vctcxo_4", "vctcxo_2", "vctcxo", "pll1_16"पूर्ण;
अटल स्थिर अक्षर *sdh_parent[] = अणु"pll1_4", "pll2", "usb_pll", "pll1"पूर्ण;
अटल स्थिर अक्षर *disp_parent[] = अणु"pll1", "pll1_16", "pll2", "vctcxo"पूर्ण;
अटल स्थिर अक्षर *ccic_parent[] = अणु"pll1_2", "pll1_16", "vctcxo"पूर्ण;

व्योम __init mmp2_clk_init(phys_addr_t mpmu_phys, phys_addr_t apmu_phys,
			  phys_addr_t apbc_phys)
अणु
	काष्ठा clk *clk;
	काष्ठा clk *vctcxo;
	व्योम __iomem *mpmu_base;
	व्योम __iomem *apmu_base;
	व्योम __iomem *apbc_base;

	mpmu_base = ioremap(mpmu_phys, SZ_4K);
	अगर (!mpmu_base) अणु
		pr_err("error to ioremap MPMU base\n");
		वापस;
	पूर्ण

	apmu_base = ioremap(apmu_phys, SZ_4K);
	अगर (!apmu_base) अणु
		pr_err("error to ioremap APMU base\n");
		वापस;
	पूर्ण

	apbc_base = ioremap(apbc_phys, SZ_4K);
	अगर (!apbc_base) अणु
		pr_err("error to ioremap APBC base\n");
		वापस;
	पूर्ण

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "clk32", शून्य, 0, 3200);
	clk_रेजिस्टर_clkdev(clk, "clk32", शून्य);

	vctcxo = clk_रेजिस्टर_fixed_rate(शून्य, "vctcxo", शून्य, 0, 26000000);
	clk_रेजिस्टर_clkdev(vctcxo, "vctcxo", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll1", शून्य, 0, 800000000);
	clk_रेजिस्टर_clkdev(clk, "pll1", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "usb_pll", शून्य, 0, 480000000);
	clk_रेजिस्टर_clkdev(clk, "usb_pll", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll2", शून्य, 0, 960000000);
	clk_रेजिस्टर_clkdev(clk, "pll2", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_2", "pll1",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_2", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_4", "pll1_2",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_4", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_8", "pll1_4",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_8", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_16", "pll1_8",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_16", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_20", "pll1_4",
				CLK_SET_RATE_PARENT, 1, 5);
	clk_रेजिस्टर_clkdev(clk, "pll1_20", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_3", "pll1",
				CLK_SET_RATE_PARENT, 1, 3);
	clk_रेजिस्टर_clkdev(clk, "pll1_3", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_6", "pll1_3",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_6", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_12", "pll1_6",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_12", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_2", "pll2",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll2_2", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_4", "pll2_2",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll2_4", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_8", "pll2_4",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll2_8", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_16", "pll2_8",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll2_16", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_3", "pll2",
				CLK_SET_RATE_PARENT, 1, 3);
	clk_रेजिस्टर_clkdev(clk, "pll2_3", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_6", "pll2_3",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll2_6", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll2_12", "pll2_6",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll2_12", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "vctcxo_2", "vctcxo",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "vctcxo_2", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "vctcxo_4", "vctcxo_2",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "vctcxo_4", शून्य);

	clk = mmp_clk_रेजिस्टर_factor("uart_pll", "pll1_4", 0,
				mpmu_base + MPMU_UART_PLL,
				&uart_factor_masks, uart_factor_tbl,
				ARRAY_SIZE(uart_factor_tbl), &clk_lock);
	clk_set_rate(clk, 14745600);
	clk_रेजिस्टर_clkdev(clk, "uart_pll", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("twsi0", "vctcxo",
				apbc_base + APBC_TWSI0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.0");

	clk = mmp_clk_रेजिस्टर_apbc("twsi1", "vctcxo",
				apbc_base + APBC_TWSI1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.1");

	clk = mmp_clk_रेजिस्टर_apbc("twsi2", "vctcxo",
				apbc_base + APBC_TWSI2, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.2");

	clk = mmp_clk_रेजिस्टर_apbc("twsi3", "vctcxo",
				apbc_base + APBC_TWSI3, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.3");

	clk = mmp_clk_रेजिस्टर_apbc("twsi4", "vctcxo",
				apbc_base + APBC_TWSI4, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.4");

	clk = mmp_clk_रेजिस्टर_apbc("twsi5", "vctcxo",
				apbc_base + APBC_TWSI5, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.5");

	clk = mmp_clk_रेजिस्टर_apbc("gpio", "vctcxo",
				apbc_base + APBC_GPIO, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp2-gpio");

	clk = mmp_clk_रेजिस्टर_apbc("kpc", "clk32",
				apbc_base + APBC_KPC, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa27x-keypad");

	clk = mmp_clk_रेजिस्टर_apbc("rtc", "clk32",
				apbc_base + APBC_RTC, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-rtc");

	clk = mmp_clk_रेजिस्टर_apbc("pwm0", "vctcxo",
				apbc_base + APBC_PWM0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp2-pwm.0");

	clk = mmp_clk_रेजिस्टर_apbc("pwm1", "vctcxo",
				apbc_base + APBC_PWM1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp2-pwm.1");

	clk = mmp_clk_रेजिस्टर_apbc("pwm2", "vctcxo",
				apbc_base + APBC_PWM2, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp2-pwm.2");

	clk = mmp_clk_रेजिस्टर_apbc("pwm3", "vctcxo",
				apbc_base + APBC_PWM3, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp2-pwm.3");

	clk = clk_रेजिस्टर_mux(शून्य, "uart0_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_UART0, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, vctcxo);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart0", "uart0_mux",
				apbc_base + APBC_UART0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.0");

	clk = clk_रेजिस्टर_mux(शून्य, "uart1_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_UART1, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, vctcxo);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.1", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart1", "uart1_mux",
				apbc_base + APBC_UART1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.1");

	clk = clk_रेजिस्टर_mux(शून्य, "uart2_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_UART2, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, vctcxo);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.2", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart2", "uart2_mux",
				apbc_base + APBC_UART2, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.2");

	clk = clk_रेजिस्टर_mux(शून्य, "uart3_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_UART3, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, vctcxo);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.3", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart3", "uart3_mux",
				apbc_base + APBC_UART3, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.3");

	clk = clk_रेजिस्टर_mux(शून्य, "ssp0_mux", ssp_parent,
				ARRAY_SIZE(ssp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_SSP0, 4, 3, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("ssp0", "ssp0_mux",
				apbc_base + APBC_SSP0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-ssp.0");

	clk = clk_रेजिस्टर_mux(शून्य, "ssp1_mux", ssp_parent,
				ARRAY_SIZE(ssp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_SSP1, 4, 3, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ssp_mux.1", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("ssp1", "ssp1_mux",
				apbc_base + APBC_SSP1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-ssp.1");

	clk = clk_रेजिस्टर_mux(शून्य, "ssp2_mux", ssp_parent,
				ARRAY_SIZE(ssp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_SSP2, 4, 3, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ssp_mux.2", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("ssp2", "ssp2_mux",
				apbc_base + APBC_SSP2, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-ssp.2");

	clk = clk_रेजिस्टर_mux(शून्य, "ssp3_mux", ssp_parent,
				ARRAY_SIZE(ssp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_SSP3, 4, 3, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ssp_mux.3", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("ssp3", "ssp3_mux",
				apbc_base + APBC_SSP3, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-ssp.3");

	clk = clk_रेजिस्टर_mux(शून्य, "sdh_mux", sdh_parent,
				ARRAY_SIZE(sdh_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_SDH0, 8, 2, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sdh_mux", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "sdh_div", "sdh_mux",
				CLK_SET_RATE_PARENT, apmu_base + APMU_SDH0,
				10, 4, CLK_DIVIDER_ONE_BASED, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sdh_div", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("sdh0", "sdh_div", apmu_base + APMU_SDH0,
				0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sdhci-pxav3.0");

	clk = mmp_clk_रेजिस्टर_apmu("sdh1", "sdh_div", apmu_base + APMU_SDH1,
				0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sdhci-pxav3.1");

	clk = mmp_clk_रेजिस्टर_apmu("sdh2", "sdh_div", apmu_base + APMU_SDH2,
				0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sdhci-pxav3.2");

	clk = mmp_clk_रेजिस्टर_apmu("sdh3", "sdh_div", apmu_base + APMU_SDH3,
				0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sdhci-pxav3.3");

	clk = mmp_clk_रेजिस्टर_apmu("usb", "usb_pll", apmu_base + APMU_USB,
				0x9, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "usb_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "disp0_mux", disp_parent,
				ARRAY_SIZE(disp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_DISP0, 6, 2, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_mux.0", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "disp0_div", "disp0_mux",
				CLK_SET_RATE_PARENT, apmu_base + APMU_DISP0,
				8, 4, CLK_DIVIDER_ONE_BASED, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_div.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("disp0", "disp0_div",
				apmu_base + APMU_DISP0, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-disp.0");

	clk = clk_रेजिस्टर_भागider(शून्य, "disp0_sphy_div", "disp0_mux", 0,
				apmu_base + APMU_DISP0, 15, 5, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_sphy_div.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("disp0_sphy", "disp0_sphy_div",
				apmu_base + APMU_DISP0, 0x1024, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_sphy.0", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "disp1_mux", disp_parent,
				ARRAY_SIZE(disp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_DISP1, 6, 2, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_mux.1", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "disp1_div", "disp1_mux",
				CLK_SET_RATE_PARENT, apmu_base + APMU_DISP1,
				8, 4, CLK_DIVIDER_ONE_BASED, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_div.1", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("disp1", "disp1_div",
				apmu_base + APMU_DISP1, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-disp.1");

	clk = mmp_clk_रेजिस्टर_apmu("ccic_arbiter", "vctcxo",
				apmu_base + APMU_CCIC0, 0x1800, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_arbiter", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "ccic0_mux", ccic_parent,
				ARRAY_SIZE(ccic_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_CCIC0, 6, 2, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_mux.0", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "ccic0_div", "ccic0_mux",
				CLK_SET_RATE_PARENT, apmu_base + APMU_CCIC0,
				17, 4, CLK_DIVIDER_ONE_BASED, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_div.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("ccic0", "ccic0_div",
				apmu_base + APMU_CCIC0, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "fnclk", "mmp-ccic.0");

	clk = mmp_clk_रेजिस्टर_apmu("ccic0_phy", "ccic0_div",
				apmu_base + APMU_CCIC0, 0x24, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "phyclk", "mmp-ccic.0");

	clk = clk_रेजिस्टर_भागider(शून्य, "ccic0_sphy_div", "ccic0_div",
				CLK_SET_RATE_PARENT, apmu_base + APMU_CCIC0,
				10, 5, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sphyclk_div", "mmp-ccic.0");

	clk = mmp_clk_रेजिस्टर_apmu("ccic0_sphy", "ccic0_sphy_div",
				apmu_base + APMU_CCIC0, 0x300, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sphyclk", "mmp-ccic.0");

	clk = clk_रेजिस्टर_mux(शून्य, "ccic1_mux", ccic_parent,
				ARRAY_SIZE(ccic_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_CCIC1, 6, 2, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_mux.1", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "ccic1_div", "ccic1_mux",
				CLK_SET_RATE_PARENT, apmu_base + APMU_CCIC1,
				16, 4, CLK_DIVIDER_ONE_BASED, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_div.1", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("ccic1", "ccic1_div",
				apmu_base + APMU_CCIC1, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "fnclk", "mmp-ccic.1");

	clk = mmp_clk_रेजिस्टर_apmu("ccic1_phy", "ccic1_div",
				apmu_base + APMU_CCIC1, 0x24, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "phyclk", "mmp-ccic.1");

	clk = clk_रेजिस्टर_भागider(शून्य, "ccic1_sphy_div", "ccic1_div",
				CLK_SET_RATE_PARENT, apmu_base + APMU_CCIC1,
				10, 5, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sphyclk_div", "mmp-ccic.1");

	clk = mmp_clk_रेजिस्टर_apmu("ccic1_sphy", "ccic1_sphy_div",
				apmu_base + APMU_CCIC1, 0x300, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sphyclk", "mmp-ccic.1");
पूर्ण
