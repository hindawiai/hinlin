<शैली गुरु>
/*
 * pxa910 घड़ी framework source file
 *
 * Copyright (C) 2012 Marvell
 * Chao Xie <xiechao.mail@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/mmp.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>

#समावेश "clk.h"

#घोषणा APBC_RTC	0x28
#घोषणा APBC_TWSI0	0x2c
#घोषणा APBC_KPC	0x18
#घोषणा APBC_UART0	0x0
#घोषणा APBC_UART1	0x4
#घोषणा APBC_GPIO	0x8
#घोषणा APBC_PWM0	0xc
#घोषणा APBC_PWM1	0x10
#घोषणा APBC_PWM2	0x14
#घोषणा APBC_PWM3	0x18
#घोषणा APBC_SSP0	0x1c
#घोषणा APBC_SSP1	0x20
#घोषणा APBC_SSP2	0x4c
#घोषणा APBCP_TWSI1	0x28
#घोषणा APBCP_UART2	0x1c
#घोषणा APMU_SDH0	0x54
#घोषणा APMU_SDH1	0x58
#घोषणा APMU_USB	0x5c
#घोषणा APMU_DISP0	0x4c
#घोषणा APMU_CCIC0	0x50
#घोषणा APMU_DFC	0x60
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
पूर्ण;

अटल स्थिर अक्षर *uart_parent[] = अणु"pll1_3_16", "uart_pll"पूर्ण;
अटल स्थिर अक्षर *ssp_parent[] = अणु"pll1_96", "pll1_48", "pll1_24", "pll1_12"पूर्ण;
अटल स्थिर अक्षर *sdh_parent[] = अणु"pll1_12", "pll1_13"पूर्ण;
अटल स्थिर अक्षर *disp_parent[] = अणु"pll1_2", "pll1_12"पूर्ण;
अटल स्थिर अक्षर *ccic_parent[] = अणु"pll1_2", "pll1_12"पूर्ण;
अटल स्थिर अक्षर *ccic_phy_parent[] = अणु"pll1_6", "pll1_12"पूर्ण;

व्योम __init pxa910_clk_init(phys_addr_t mpmu_phys, phys_addr_t apmu_phys,
			    phys_addr_t apbc_phys, phys_addr_t apbcp_phys)
अणु
	काष्ठा clk *clk;
	काष्ठा clk *uart_pll;
	व्योम __iomem *mpmu_base;
	व्योम __iomem *apmu_base;
	व्योम __iomem *apbcp_base;
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

	apbcp_base = ioremap(apbcp_phys, SZ_4K);
	अगर (!apbcp_base) अणु
		pr_err("error to ioremap APBC extension base\n");
		वापस;
	पूर्ण

	apbc_base = ioremap(apbc_phys, SZ_4K);
	अगर (!apbc_base) अणु
		pr_err("error to ioremap APBC base\n");
		वापस;
	पूर्ण

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "clk32", शून्य, 0, 3200);
	clk_रेजिस्टर_clkdev(clk, "clk32", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "vctcxo", शून्य, 0, 26000000);
	clk_रेजिस्टर_clkdev(clk, "vctcxo", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll1", शून्य, 0, 624000000);
	clk_रेजिस्टर_clkdev(clk, "pll1", शून्य);

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

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_6", "pll1_2",
				CLK_SET_RATE_PARENT, 1, 3);
	clk_रेजिस्टर_clkdev(clk, "pll1_6", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_12", "pll1_6",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_12", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_24", "pll1_12",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_24", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_48", "pll1_24",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_48", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_96", "pll1_48",
				CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll1_96", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_13", "pll1",
				CLK_SET_RATE_PARENT, 1, 13);
	clk_रेजिस्टर_clkdev(clk, "pll1_13", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_13_1_5", "pll1",
				CLK_SET_RATE_PARENT, 2, 3);
	clk_रेजिस्टर_clkdev(clk, "pll1_13_1_5", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_2_1_5", "pll1",
				CLK_SET_RATE_PARENT, 2, 3);
	clk_रेजिस्टर_clkdev(clk, "pll1_2_1_5", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll1_3_16", "pll1",
				CLK_SET_RATE_PARENT, 3, 16);
	clk_रेजिस्टर_clkdev(clk, "pll1_3_16", शून्य);

	uart_pll =  mmp_clk_रेजिस्टर_factor("uart_pll", "pll1_4", 0,
				mpmu_base + MPMU_UART_PLL,
				&uart_factor_masks, uart_factor_tbl,
				ARRAY_SIZE(uart_factor_tbl), &clk_lock);
	clk_set_rate(uart_pll, 14745600);
	clk_रेजिस्टर_clkdev(uart_pll, "uart_pll", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("twsi0", "pll1_13_1_5",
				apbc_base + APBC_TWSI0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.0");

	clk = mmp_clk_रेजिस्टर_apbc("twsi1", "pll1_13_1_5",
				apbcp_base + APBCP_TWSI1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-i2c.1");

	clk = mmp_clk_रेजिस्टर_apbc("gpio", "vctcxo",
				apbc_base + APBC_GPIO, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-gpio");

	clk = mmp_clk_रेजिस्टर_apbc("kpc", "clk32",
				apbc_base + APBC_KPC, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa27x-keypad");

	clk = mmp_clk_रेजिस्टर_apbc("rtc", "clk32",
				apbc_base + APBC_RTC, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sa1100-rtc");

	clk = mmp_clk_रेजिस्टर_apbc("pwm0", "pll1_48",
				apbc_base + APBC_PWM0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa910-pwm.0");

	clk = mmp_clk_रेजिस्टर_apbc("pwm1", "pll1_48",
				apbc_base + APBC_PWM1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa910-pwm.1");

	clk = mmp_clk_रेजिस्टर_apbc("pwm2", "pll1_48",
				apbc_base + APBC_PWM2, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa910-pwm.2");

	clk = mmp_clk_रेजिस्टर_apbc("pwm3", "pll1_48",
				apbc_base + APBC_PWM3, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa910-pwm.3");

	clk = clk_रेजिस्टर_mux(शून्य, "uart0_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_UART0, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, uart_pll);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart0", "uart0_mux",
				apbc_base + APBC_UART0, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.0");

	clk = clk_रेजिस्टर_mux(शून्य, "uart1_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbc_base + APBC_UART1, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, uart_pll);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.1", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart1", "uart1_mux",
				apbc_base + APBC_UART1, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.1");

	clk = clk_रेजिस्टर_mux(शून्य, "uart2_mux", uart_parent,
				ARRAY_SIZE(uart_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apbcp_base + APBCP_UART2, 4, 3, 0, &clk_lock);
	clk_set_parent(clk, uart_pll);
	clk_रेजिस्टर_clkdev(clk, "uart_mux.2", शून्य);

	clk = mmp_clk_रेजिस्टर_apbc("uart2", "uart2_mux",
				apbcp_base + APBCP_UART2, 10, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa2xx-uart.2");

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

	clk = mmp_clk_रेजिस्टर_apmu("dfc", "pll1_4",
				apmu_base + APMU_DFC, 0x19b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "pxa3xx-nand.0");

	clk = clk_रेजिस्टर_mux(शून्य, "sdh0_mux", sdh_parent,
				ARRAY_SIZE(sdh_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_SDH0, 6, 1, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sdh0_mux", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("sdh0", "sdh_mux",
				apmu_base + APMU_SDH0, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sdhci-pxa.0");

	clk = clk_रेजिस्टर_mux(शून्य, "sdh1_mux", sdh_parent,
				ARRAY_SIZE(sdh_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_SDH1, 6, 1, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sdh1_mux", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("sdh1", "sdh1_mux",
				apmu_base + APMU_SDH1, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "sdhci-pxa.1");

	clk = mmp_clk_रेजिस्टर_apmu("usb", "usb_pll",
				apmu_base + APMU_USB, 0x9, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "usb_clk", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("sph", "usb_pll",
				apmu_base + APMU_USB, 0x12, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sph_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "disp0_mux", disp_parent,
				ARRAY_SIZE(disp_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_DISP0, 6, 1, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "disp_mux.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("disp0", "disp0_mux",
				apmu_base + APMU_DISP0, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mmp-disp.0");

	clk = clk_रेजिस्टर_mux(शून्य, "ccic0_mux", ccic_parent,
				ARRAY_SIZE(ccic_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_CCIC0, 6, 1, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_mux.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("ccic0", "ccic0_mux",
				apmu_base + APMU_CCIC0, 0x1b, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "fnclk", "mmp-ccic.0");

	clk = clk_रेजिस्टर_mux(शून्य, "ccic0_phy_mux", ccic_phy_parent,
				ARRAY_SIZE(ccic_phy_parent),
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				apmu_base + APMU_CCIC0, 7, 1, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "ccic_phy_mux.0", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("ccic0_phy", "ccic0_phy_mux",
				apmu_base + APMU_CCIC0, 0x24, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "phyclk", "mmp-ccic.0");

	clk = clk_रेजिस्टर_भागider(शून्य, "ccic0_sphy_div", "ccic0_mux",
				CLK_SET_RATE_PARENT, apmu_base + APMU_CCIC0,
				10, 5, 0, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sphyclk_div", शून्य);

	clk = mmp_clk_रेजिस्टर_apmu("ccic0_sphy", "ccic0_sphy_div",
				apmu_base + APMU_CCIC0, 0x300, &clk_lock);
	clk_रेजिस्टर_clkdev(clk, "sphyclk", "mmp-ccic.0");
पूर्ण
