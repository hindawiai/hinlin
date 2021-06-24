<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon Hi3620 घड़ी driver
 *
 * Copyright (c) 2012-2013 Hisilicon Limited.
 * Copyright (c) 2012-2013 Linaro Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 *	   Xin Li <li.xin@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/hi3620-घड़ी.h>

#समावेश "clk.h"

/* घड़ी parent list */
अटल स्थिर अक्षर *स्थिर समयr0_mux_p[] __initस्थिर = अणु "osc32k", "timerclk01", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr1_mux_p[] __initस्थिर = अणु "osc32k", "timerclk01", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr2_mux_p[] __initस्थिर = अणु "osc32k", "timerclk23", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr3_mux_p[] __initस्थिर = अणु "osc32k", "timerclk23", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr4_mux_p[] __initस्थिर = अणु "osc32k", "timerclk45", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr5_mux_p[] __initस्थिर = अणु "osc32k", "timerclk45", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr6_mux_p[] __initस्थिर = अणु "osc32k", "timerclk67", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr7_mux_p[] __initस्थिर = अणु "osc32k", "timerclk67", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr8_mux_p[] __initस्थिर = अणु "osc32k", "timerclk89", पूर्ण;
अटल स्थिर अक्षर *स्थिर समयr9_mux_p[] __initस्थिर = अणु "osc32k", "timerclk89", पूर्ण;
अटल स्थिर अक्षर *स्थिर uart0_mux_p[] __initस्थिर = अणु "osc26m", "pclk", पूर्ण;
अटल स्थिर अक्षर *स्थिर uart1_mux_p[] __initस्थिर = अणु "osc26m", "pclk", पूर्ण;
अटल स्थिर अक्षर *स्थिर uart2_mux_p[] __initस्थिर = अणु "osc26m", "pclk", पूर्ण;
अटल स्थिर अक्षर *स्थिर uart3_mux_p[] __initस्थिर = अणु "osc26m", "pclk", पूर्ण;
अटल स्थिर अक्षर *स्थिर uart4_mux_p[] __initस्थिर = अणु "osc26m", "pclk", पूर्ण;
अटल स्थिर अक्षर *स्थिर spi0_mux_p[] __initस्थिर = अणु "osc26m", "rclk_cfgaxi", पूर्ण;
अटल स्थिर अक्षर *स्थिर spi1_mux_p[] __initस्थिर = अणु "osc26m", "rclk_cfgaxi", पूर्ण;
अटल स्थिर अक्षर *स्थिर spi2_mux_p[] __initस्थिर = अणु "osc26m", "rclk_cfgaxi", पूर्ण;
/* share axi parent */
अटल स्थिर अक्षर *स्थिर saxi_mux_p[] __initस्थिर = अणु "armpll3", "armpll2", पूर्ण;
अटल स्थिर अक्षर *स्थिर pwm0_mux_p[] __initस्थिर = अणु "osc32k", "osc26m", पूर्ण;
अटल स्थिर अक्षर *स्थिर pwm1_mux_p[] __initस्थिर = अणु "osc32k", "osc26m", पूर्ण;
अटल स्थिर अक्षर *स्थिर sd_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर mmc1_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर mmc1_mux2_p[] __initस्थिर = अणु "osc26m", "mmc1_div", पूर्ण;
अटल स्थिर अक्षर *स्थिर g2d_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर venc_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर vdec_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर vpp_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर edc0_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर ldi0_mux_p[] __initस्थिर = अणु "armpll2", "armpll4",
					     "armpll3", "armpll5", पूर्ण;
अटल स्थिर अक्षर *स्थिर edc1_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर ldi1_mux_p[] __initस्थिर = अणु "armpll2", "armpll4",
					     "armpll3", "armpll5", पूर्ण;
अटल स्थिर अक्षर *स्थिर rclk_hsic_p[] __initस्थिर = अणु "armpll3", "armpll2", पूर्ण;
अटल स्थिर अक्षर *स्थिर mmc2_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;
अटल स्थिर अक्षर *स्थिर mmc3_mux_p[] __initस्थिर = अणु "armpll2", "armpll3", पूर्ण;


/* fixed rate घड़ीs */
अटल काष्ठा hisi_fixed_rate_घड़ी hi3620_fixed_rate_clks[] __initdata = अणु
	अणु HI3620_OSC32K,   "osc32k",   शून्य, 0, 32768, पूर्ण,
	अणु HI3620_OSC26M,   "osc26m",   शून्य, 0, 26000000, पूर्ण,
	अणु HI3620_PCLK,     "pclk",     शून्य, 0, 26000000, पूर्ण,
	अणु HI3620_PLL_ARM0, "armpll0",  शून्य, 0, 1600000000, पूर्ण,
	अणु HI3620_PLL_ARM1, "armpll1",  शून्य, 0, 1600000000, पूर्ण,
	अणु HI3620_PLL_PERI, "armpll2",  शून्य, 0, 1440000000, पूर्ण,
	अणु HI3620_PLL_USB,  "armpll3",  शून्य, 0, 1440000000, पूर्ण,
	अणु HI3620_PLL_HDMI, "armpll4",  शून्य, 0, 1188000000, पूर्ण,
	अणु HI3620_PLL_GPU,  "armpll5",  शून्य, 0, 1300000000, पूर्ण,
पूर्ण;

/* fixed factor घड़ीs */
अटल काष्ठा hisi_fixed_factor_घड़ी hi3620_fixed_factor_clks[] __initdata = अणु
	अणु HI3620_RCLK_TCXO,   "rclk_tcxo",   "osc26m",   1, 4,  0, पूर्ण,
	अणु HI3620_RCLK_CFGAXI, "rclk_cfgaxi", "armpll2",  1, 30, 0, पूर्ण,
	अणु HI3620_RCLK_PICO,   "rclk_pico",   "hsic_div", 1, 40, 0, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_mux_घड़ी hi3620_mux_clks[] __initdata = अणु
	अणु HI3620_TIMER0_MUX, "timer0_mux", समयr0_mux_p, ARRAY_SIZE(समयr0_mux_p), CLK_SET_RATE_PARENT, 0,     15, 2, 0,                   पूर्ण,
	अणु HI3620_TIMER1_MUX, "timer1_mux", समयr1_mux_p, ARRAY_SIZE(समयr1_mux_p), CLK_SET_RATE_PARENT, 0,     17, 2, 0,                   पूर्ण,
	अणु HI3620_TIMER2_MUX, "timer2_mux", समयr2_mux_p, ARRAY_SIZE(समयr2_mux_p), CLK_SET_RATE_PARENT, 0,     19, 2, 0,                   पूर्ण,
	अणु HI3620_TIMER3_MUX, "timer3_mux", समयr3_mux_p, ARRAY_SIZE(समयr3_mux_p), CLK_SET_RATE_PARENT, 0,     21, 2, 0,                   पूर्ण,
	अणु HI3620_TIMER4_MUX, "timer4_mux", समयr4_mux_p, ARRAY_SIZE(समयr4_mux_p), CLK_SET_RATE_PARENT, 0x18,  0,  2, 0,                   पूर्ण,
	अणु HI3620_TIMER5_MUX, "timer5_mux", समयr5_mux_p, ARRAY_SIZE(समयr5_mux_p), CLK_SET_RATE_PARENT, 0x18,  2,  2, 0,                   पूर्ण,
	अणु HI3620_TIMER6_MUX, "timer6_mux", समयr6_mux_p, ARRAY_SIZE(समयr6_mux_p), CLK_SET_RATE_PARENT, 0x18,  4,  2, 0,                   पूर्ण,
	अणु HI3620_TIMER7_MUX, "timer7_mux", समयr7_mux_p, ARRAY_SIZE(समयr7_mux_p), CLK_SET_RATE_PARENT, 0x18,  6,  2, 0,                   पूर्ण,
	अणु HI3620_TIMER8_MUX, "timer8_mux", समयr8_mux_p, ARRAY_SIZE(समयr8_mux_p), CLK_SET_RATE_PARENT, 0x18,  8,  2, 0,                   पूर्ण,
	अणु HI3620_TIMER9_MUX, "timer9_mux", समयr9_mux_p, ARRAY_SIZE(समयr9_mux_p), CLK_SET_RATE_PARENT, 0x18,  10, 2, 0,                   पूर्ण,
	अणु HI3620_UART0_MUX,  "uart0_mux",  uart0_mux_p,  ARRAY_SIZE(uart0_mux_p),  CLK_SET_RATE_PARENT, 0x100, 7,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_UART1_MUX,  "uart1_mux",  uart1_mux_p,  ARRAY_SIZE(uart1_mux_p),  CLK_SET_RATE_PARENT, 0x100, 8,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_UART2_MUX,  "uart2_mux",  uart2_mux_p,  ARRAY_SIZE(uart2_mux_p),  CLK_SET_RATE_PARENT, 0x100, 9,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_UART3_MUX,  "uart3_mux",  uart3_mux_p,  ARRAY_SIZE(uart3_mux_p),  CLK_SET_RATE_PARENT, 0x100, 10, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_UART4_MUX,  "uart4_mux",  uart4_mux_p,  ARRAY_SIZE(uart4_mux_p),  CLK_SET_RATE_PARENT, 0x100, 11, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_SPI0_MUX,   "spi0_mux",   spi0_mux_p,   ARRAY_SIZE(spi0_mux_p),   CLK_SET_RATE_PARENT, 0x100, 12, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_SPI1_MUX,   "spi1_mux",   spi1_mux_p,   ARRAY_SIZE(spi1_mux_p),   CLK_SET_RATE_PARENT, 0x100, 13, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_SPI2_MUX,   "spi2_mux",   spi2_mux_p,   ARRAY_SIZE(spi2_mux_p),   CLK_SET_RATE_PARENT, 0x100, 14, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_SAXI_MUX,   "saxi_mux",   saxi_mux_p,   ARRAY_SIZE(saxi_mux_p),   CLK_SET_RATE_PARENT, 0x100, 15, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_PWM0_MUX,   "pwm0_mux",   pwm0_mux_p,   ARRAY_SIZE(pwm0_mux_p),   CLK_SET_RATE_PARENT, 0x104, 10, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_PWM1_MUX,   "pwm1_mux",   pwm1_mux_p,   ARRAY_SIZE(pwm1_mux_p),   CLK_SET_RATE_PARENT, 0x104, 11, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_SD_MUX,     "sd_mux",     sd_mux_p,     ARRAY_SIZE(sd_mux_p),     CLK_SET_RATE_PARENT, 0x108, 4,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_MMC1_MUX,   "mmc1_mux",   mmc1_mux_p,   ARRAY_SIZE(mmc1_mux_p),   CLK_SET_RATE_PARENT, 0x108, 9,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_MMC1_MUX2,  "mmc1_mux2",  mmc1_mux2_p,  ARRAY_SIZE(mmc1_mux2_p),  CLK_SET_RATE_PARENT, 0x108, 10, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_G2D_MUX,    "g2d_mux",    g2d_mux_p,    ARRAY_SIZE(g2d_mux_p),    CLK_SET_RATE_PARENT, 0x10c, 5,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_VENC_MUX,   "venc_mux",   venc_mux_p,   ARRAY_SIZE(venc_mux_p),   CLK_SET_RATE_PARENT, 0x10c, 11, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_VDEC_MUX,   "vdec_mux",   vdec_mux_p,   ARRAY_SIZE(vdec_mux_p),   CLK_SET_RATE_PARENT, 0x110, 5,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_VPP_MUX,    "vpp_mux",    vpp_mux_p,    ARRAY_SIZE(vpp_mux_p),    CLK_SET_RATE_PARENT, 0x110, 11, 1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_EDC0_MUX,   "edc0_mux",   edc0_mux_p,   ARRAY_SIZE(edc0_mux_p),   CLK_SET_RATE_PARENT, 0x114, 6,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_LDI0_MUX,   "ldi0_mux",   ldi0_mux_p,   ARRAY_SIZE(ldi0_mux_p),   CLK_SET_RATE_PARENT, 0x114, 13, 2, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_EDC1_MUX,   "edc1_mux",   edc1_mux_p,   ARRAY_SIZE(edc1_mux_p),   CLK_SET_RATE_PARENT, 0x118, 6,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_LDI1_MUX,   "ldi1_mux",   ldi1_mux_p,   ARRAY_SIZE(ldi1_mux_p),   CLK_SET_RATE_PARENT, 0x118, 14, 2, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_RCLK_HSIC,  "rclk_hsic",  rclk_hsic_p,  ARRAY_SIZE(rclk_hsic_p),  CLK_SET_RATE_PARENT, 0x130, 2,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_MMC2_MUX,   "mmc2_mux",   mmc2_mux_p,   ARRAY_SIZE(mmc2_mux_p),   CLK_SET_RATE_PARENT, 0x140, 4,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
	अणु HI3620_MMC3_MUX,   "mmc3_mux",   mmc3_mux_p,   ARRAY_SIZE(mmc3_mux_p),   CLK_SET_RATE_PARENT, 0x140, 9,  1, CLK_MUX_HIWORD_MASK, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_भागider_घड़ी hi3620_भाग_clks[] __initdata = अणु
	अणु HI3620_SHAREAXI_DIV, "saxi_div",   "saxi_mux",  0, 0x100, 0, 5, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
	अणु HI3620_CFGAXI_DIV,   "cfgaxi_div", "saxi_div",  0, 0x100, 5, 2, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
	अणु HI3620_SD_DIV,       "sd_div",     "sd_mux",	  0, 0x108, 0, 4, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
	अणु HI3620_MMC1_DIV,     "mmc1_div",   "mmc1_mux",  0, 0x108, 5, 4, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
	अणु HI3620_HSIC_DIV,     "hsic_div",   "rclk_hsic", 0, 0x130, 0, 2, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
	अणु HI3620_MMC2_DIV,     "mmc2_div",   "mmc2_mux",  0, 0x140, 0, 4, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
	अणु HI3620_MMC3_DIV,     "mmc3_div",   "mmc3_mux",  0, 0x140, 5, 4, CLK_DIVIDER_HIWORD_MASK, शून्य, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_gate_घड़ी hi3620_separated_gate_clks[] __initdata = अणु
	अणु HI3620_TIMERCLK01,   "timerclk01",   "timer_rclk01", CLK_SET_RATE_PARENT, 0x20, 0, 0, पूर्ण,
	अणु HI3620_TIMER_RCLK01, "timer_rclk01", "rclk_tcxo",    CLK_SET_RATE_PARENT, 0x20, 1, 0, पूर्ण,
	अणु HI3620_TIMERCLK23,   "timerclk23",   "timer_rclk23", CLK_SET_RATE_PARENT, 0x20, 2, 0, पूर्ण,
	अणु HI3620_TIMER_RCLK23, "timer_rclk23", "rclk_tcxo",    CLK_SET_RATE_PARENT, 0x20, 3, 0, पूर्ण,
	अणु HI3620_RTCCLK,       "rtcclk",       "pclk",         CLK_SET_RATE_PARENT, 0x20, 5, 0, पूर्ण,
	अणु HI3620_KPC_CLK,      "kpc_clk",      "pclk",         CLK_SET_RATE_PARENT, 0x20, 6, 0, पूर्ण,
	अणु HI3620_GPIOCLK0,     "gpioclk0",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 8, 0, पूर्ण,
	अणु HI3620_GPIOCLK1,     "gpioclk1",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 9, 0, पूर्ण,
	अणु HI3620_GPIOCLK2,     "gpioclk2",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 10, 0, पूर्ण,
	अणु HI3620_GPIOCLK3,     "gpioclk3",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 11, 0, पूर्ण,
	अणु HI3620_GPIOCLK4,     "gpioclk4",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 12, 0, पूर्ण,
	अणु HI3620_GPIOCLK5,     "gpioclk5",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 13, 0, पूर्ण,
	अणु HI3620_GPIOCLK6,     "gpioclk6",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 14, 0, पूर्ण,
	अणु HI3620_GPIOCLK7,     "gpioclk7",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 15, 0, पूर्ण,
	अणु HI3620_GPIOCLK8,     "gpioclk8",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 16, 0, पूर्ण,
	अणु HI3620_GPIOCLK9,     "gpioclk9",     "pclk",         CLK_SET_RATE_PARENT, 0x20, 17, 0, पूर्ण,
	अणु HI3620_GPIOCLK10,    "gpioclk10",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 18, 0, पूर्ण,
	अणु HI3620_GPIOCLK11,    "gpioclk11",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 19, 0, पूर्ण,
	अणु HI3620_GPIOCLK12,    "gpioclk12",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 20, 0, पूर्ण,
	अणु HI3620_GPIOCLK13,    "gpioclk13",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 21, 0, पूर्ण,
	अणु HI3620_GPIOCLK14,    "gpioclk14",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 22, 0, पूर्ण,
	अणु HI3620_GPIOCLK15,    "gpioclk15",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 23, 0, पूर्ण,
	अणु HI3620_GPIOCLK16,    "gpioclk16",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 24, 0, पूर्ण,
	अणु HI3620_GPIOCLK17,    "gpioclk17",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 25, 0, पूर्ण,
	अणु HI3620_GPIOCLK18,    "gpioclk18",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 26, 0, पूर्ण,
	अणु HI3620_GPIOCLK19,    "gpioclk19",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 27, 0, पूर्ण,
	अणु HI3620_GPIOCLK20,    "gpioclk20",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 28, 0, पूर्ण,
	अणु HI3620_GPIOCLK21,    "gpioclk21",    "pclk",         CLK_SET_RATE_PARENT, 0x20, 29, 0, पूर्ण,
	अणु HI3620_DPHY0_CLK,    "dphy0_clk",    "osc26m",       CLK_SET_RATE_PARENT, 0x30, 15, 0, पूर्ण,
	अणु HI3620_DPHY1_CLK,    "dphy1_clk",    "osc26m",       CLK_SET_RATE_PARENT, 0x30, 16, 0, पूर्ण,
	अणु HI3620_DPHY2_CLK,    "dphy2_clk",    "osc26m",       CLK_SET_RATE_PARENT, 0x30, 17, 0, पूर्ण,
	अणु HI3620_USBPHY_CLK,   "usbphy_clk",   "rclk_pico",    CLK_SET_RATE_PARENT, 0x30, 24, 0, पूर्ण,
	अणु HI3620_ACP_CLK,      "acp_clk",      "rclk_cfgaxi",  CLK_SET_RATE_PARENT, 0x30, 28, 0, पूर्ण,
	अणु HI3620_TIMERCLK45,   "timerclk45",   "rclk_tcxo",    CLK_SET_RATE_PARENT, 0x40, 3, 0, पूर्ण,
	अणु HI3620_TIMERCLK67,   "timerclk67",   "rclk_tcxo",    CLK_SET_RATE_PARENT, 0x40, 4, 0, पूर्ण,
	अणु HI3620_TIMERCLK89,   "timerclk89",   "rclk_tcxo",    CLK_SET_RATE_PARENT, 0x40, 5, 0, पूर्ण,
	अणु HI3620_PWMCLK0,      "pwmclk0",      "pwm0_mux",     CLK_SET_RATE_PARENT, 0x40, 7, 0, पूर्ण,
	अणु HI3620_PWMCLK1,      "pwmclk1",      "pwm1_mux",     CLK_SET_RATE_PARENT, 0x40, 8, 0, पूर्ण,
	अणु HI3620_UARTCLK0,     "uartclk0",     "uart0_mux",    CLK_SET_RATE_PARENT, 0x40, 16, 0, पूर्ण,
	अणु HI3620_UARTCLK1,     "uartclk1",     "uart1_mux",    CLK_SET_RATE_PARENT, 0x40, 17, 0, पूर्ण,
	अणु HI3620_UARTCLK2,     "uartclk2",     "uart2_mux",    CLK_SET_RATE_PARENT, 0x40, 18, 0, पूर्ण,
	अणु HI3620_UARTCLK3,     "uartclk3",     "uart3_mux",    CLK_SET_RATE_PARENT, 0x40, 19, 0, पूर्ण,
	अणु HI3620_UARTCLK4,     "uartclk4",     "uart4_mux",    CLK_SET_RATE_PARENT, 0x40, 20, 0, पूर्ण,
	अणु HI3620_SPICLK0,      "spiclk0",      "spi0_mux",     CLK_SET_RATE_PARENT, 0x40, 21, 0, पूर्ण,
	अणु HI3620_SPICLK1,      "spiclk1",      "spi1_mux",     CLK_SET_RATE_PARENT, 0x40, 22, 0, पूर्ण,
	अणु HI3620_SPICLK2,      "spiclk2",      "spi2_mux",     CLK_SET_RATE_PARENT, 0x40, 23, 0, पूर्ण,
	अणु HI3620_I2CCLK0,      "i2cclk0",      "pclk",         CLK_SET_RATE_PARENT, 0x40, 24, 0, पूर्ण,
	अणु HI3620_I2CCLK1,      "i2cclk1",      "pclk",         CLK_SET_RATE_PARENT, 0x40, 25, 0, पूर्ण,
	अणु HI3620_SCI_CLK,      "sci_clk",      "osc26m",       CLK_SET_RATE_PARENT, 0x40, 26, 0, पूर्ण,
	अणु HI3620_I2CCLK2,      "i2cclk2",      "pclk",         CLK_SET_RATE_PARENT, 0x40, 28, 0, पूर्ण,
	अणु HI3620_I2CCLK3,      "i2cclk3",      "pclk",         CLK_SET_RATE_PARENT, 0x40, 29, 0, पूर्ण,
	अणु HI3620_DDRC_PER_CLK, "ddrc_per_clk", "rclk_cfgaxi",  CLK_SET_RATE_PARENT, 0x50, 9, 0, पूर्ण,
	अणु HI3620_DMAC_CLK,     "dmac_clk",     "rclk_cfgaxi",  CLK_SET_RATE_PARENT, 0x50, 10, 0, पूर्ण,
	अणु HI3620_USB2DVC_CLK,  "usb2dvc_clk",  "rclk_cfgaxi",  CLK_SET_RATE_PARENT, 0x50, 17, 0, पूर्ण,
	अणु HI3620_SD_CLK,       "sd_clk",       "sd_div",       CLK_SET_RATE_PARENT, 0x50, 20, 0, पूर्ण,
	अणु HI3620_MMC_CLK1,     "mmc_clk1",     "mmc1_mux2",    CLK_SET_RATE_PARENT, 0x50, 21, 0, पूर्ण,
	अणु HI3620_MMC_CLK2,     "mmc_clk2",     "mmc2_div",     CLK_SET_RATE_PARENT, 0x50, 22, 0, पूर्ण,
	अणु HI3620_MMC_CLK3,     "mmc_clk3",     "mmc3_div",     CLK_SET_RATE_PARENT, 0x50, 23, 0, पूर्ण,
	अणु HI3620_MCU_CLK,      "mcu_clk",      "acp_clk",      CLK_SET_RATE_PARENT, 0x50, 24, 0, पूर्ण,
पूर्ण;

अटल व्योम __init hi3620_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;

	clk_data = hisi_clk_init(np, HI3620_NR_CLKS);
	अगर (!clk_data)
		वापस;

	hisi_clk_रेजिस्टर_fixed_rate(hi3620_fixed_rate_clks,
				     ARRAY_SIZE(hi3620_fixed_rate_clks),
				     clk_data);
	hisi_clk_रेजिस्टर_fixed_factor(hi3620_fixed_factor_clks,
				       ARRAY_SIZE(hi3620_fixed_factor_clks),
				       clk_data);
	hisi_clk_रेजिस्टर_mux(hi3620_mux_clks, ARRAY_SIZE(hi3620_mux_clks),
			      clk_data);
	hisi_clk_रेजिस्टर_भागider(hi3620_भाग_clks, ARRAY_SIZE(hi3620_भाग_clks),
				  clk_data);
	hisi_clk_रेजिस्टर_gate_sep(hi3620_separated_gate_clks,
				   ARRAY_SIZE(hi3620_separated_gate_clks),
				   clk_data);
पूर्ण
CLK_OF_DECLARE(hi3620_clk, "hisilicon,hi3620-clock", hi3620_clk_init);

काष्ठा hisi_mmc_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	u32			clken_reg;
	u32			clken_bit;
	u32			भाग_reg;
	u32			भाग_off;
	u32			भाग_bits;
	u32			drv_reg;
	u32			drv_off;
	u32			drv_bits;
	u32			sam_reg;
	u32			sam_off;
	u32			sam_bits;
पूर्ण;

काष्ठा clk_mmc अणु
	काष्ठा clk_hw	hw;
	u32		id;
	व्योम __iomem	*clken_reg;
	u32		clken_bit;
	व्योम __iomem	*भाग_reg;
	u32		भाग_off;
	u32		भाग_bits;
	व्योम __iomem	*drv_reg;
	u32		drv_off;
	u32		drv_bits;
	व्योम __iomem	*sam_reg;
	u32		sam_off;
	u32		sam_bits;
पूर्ण;

#घोषणा to_mmc(_hw) container_of(_hw, काष्ठा clk_mmc, hw)

अटल काष्ठा hisi_mmc_घड़ी hi3620_mmc_clks[] __initdata = अणु
	अणु HI3620_SD_CIUCLK,	"sd_bclk1", "sd_clk", CLK_SET_RATE_PARENT, 0x1f8, 0, 0x1f8, 1, 3, 0x1f8, 4, 4, 0x1f8, 8, 4पूर्ण,
	अणु HI3620_MMC_CIUCLK1,   "mmc_bclk1", "mmc_clk1", CLK_SET_RATE_PARENT, 0x1f8, 12, 0x1f8, 13, 3, 0x1f8, 16, 4, 0x1f8, 20, 4पूर्ण,
	अणु HI3620_MMC_CIUCLK2,   "mmc_bclk2", "mmc_clk2", CLK_SET_RATE_PARENT, 0x1f8, 24, 0x1f8, 25, 3, 0x1f8, 28, 4, 0x1fc, 0, 4पूर्ण,
	अणु HI3620_MMC_CIUCLK3,   "mmc_bclk3", "mmc_clk3", CLK_SET_RATE_PARENT, 0x1fc, 4, 0x1fc, 5, 3, 0x1fc, 8, 4, 0x1fc, 12, 4पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ mmc_clk_recalc_rate(काष्ठा clk_hw *hw,
		       अचिन्हित दीर्घ parent_rate)
अणु
	चयन (parent_rate) अणु
	हाल 26000000:
		वापस 13000000;
	हाल 180000000:
		वापस 25000000;
	हाल 360000000:
		वापस 50000000;
	हाल 720000000:
		वापस 100000000;
	हाल 1440000000:
		वापस 180000000;
	शेष:
		वापस parent_rate;
	पूर्ण
पूर्ण

अटल पूर्णांक mmc_clk_determine_rate(काष्ठा clk_hw *hw,
				  काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_mmc *mclk = to_mmc(hw);

	अगर ((req->rate <= 13000000) && (mclk->id == HI3620_MMC_CIUCLK1)) अणु
		req->rate = 13000000;
		req->best_parent_rate = 26000000;
	पूर्ण अन्यथा अगर (req->rate <= 26000000) अणु
		req->rate = 25000000;
		req->best_parent_rate = 180000000;
	पूर्ण अन्यथा अगर (req->rate <= 52000000) अणु
		req->rate = 50000000;
		req->best_parent_rate = 360000000;
	पूर्ण अन्यथा अगर (req->rate <= 100000000) अणु
		req->rate = 100000000;
		req->best_parent_rate = 720000000;
	पूर्ण अन्यथा अणु
		/* max is 180M */
		req->rate = 180000000;
		req->best_parent_rate = 1440000000;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल u32 mmc_clk_delay(u32 val, u32 para, u32 off, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (para % 2)
			val |= 1 << (off + i);
		अन्यथा
			val &= ~(1 << (off + i));
		para = para >> 1;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक mmc_clk_set_timing(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_mmc *mclk = to_mmc(hw);
	अचिन्हित दीर्घ flags;
	u32 sam, drv, भाग, val;
	अटल DEFINE_SPINLOCK(mmc_clk_lock);

	चयन (rate) अणु
	हाल 13000000:
		sam = 3;
		drv = 1;
		भाग = 1;
		अवरोध;
	हाल 25000000:
		sam = 13;
		drv = 6;
		भाग = 6;
		अवरोध;
	हाल 50000000:
		sam = 3;
		drv = 6;
		भाग = 6;
		अवरोध;
	हाल 100000000:
		sam = 6;
		drv = 4;
		भाग = 6;
		अवरोध;
	हाल 180000000:
		sam = 6;
		drv = 4;
		भाग = 7;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&mmc_clk_lock, flags);

	val = पढ़ोl_relaxed(mclk->clken_reg);
	val &= ~(1 << mclk->clken_bit);
	ग_लिखोl_relaxed(val, mclk->clken_reg);

	val = पढ़ोl_relaxed(mclk->sam_reg);
	val = mmc_clk_delay(val, sam, mclk->sam_off, mclk->sam_bits);
	ग_लिखोl_relaxed(val, mclk->sam_reg);

	val = पढ़ोl_relaxed(mclk->drv_reg);
	val = mmc_clk_delay(val, drv, mclk->drv_off, mclk->drv_bits);
	ग_लिखोl_relaxed(val, mclk->drv_reg);

	val = पढ़ोl_relaxed(mclk->भाग_reg);
	val = mmc_clk_delay(val, भाग, mclk->भाग_off, mclk->भाग_bits);
	ग_लिखोl_relaxed(val, mclk->भाग_reg);

	val = पढ़ोl_relaxed(mclk->clken_reg);
	val |= 1 << mclk->clken_bit;
	ग_लिखोl_relaxed(val, mclk->clken_reg);

	spin_unlock_irqrestore(&mmc_clk_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_mmc *mclk = to_mmc(hw);
	अचिन्हित दीर्घ rate;

	अगर (mclk->id == HI3620_MMC_CIUCLK1)
		rate = 13000000;
	अन्यथा
		rate = 25000000;

	वापस mmc_clk_set_timing(hw, rate);
पूर्ण

अटल पूर्णांक mmc_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	वापस mmc_clk_set_timing(hw, rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_mmc_ops = अणु
	.prepare = mmc_clk_prepare,
	.determine_rate = mmc_clk_determine_rate,
	.set_rate = mmc_clk_set_rate,
	.recalc_rate = mmc_clk_recalc_rate,
पूर्ण;

अटल काष्ठा clk *hisi_रेजिस्टर_clk_mmc(काष्ठा hisi_mmc_घड़ी *mmc_clk,
			व्योम __iomem *base, काष्ठा device_node *np)
अणु
	काष्ठा clk_mmc *mclk;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	mclk = kzalloc(माप(*mclk), GFP_KERNEL);
	अगर (!mclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = mmc_clk->name;
	init.ops = &clk_mmc_ops;
	init.flags = mmc_clk->flags;
	init.parent_names = (mmc_clk->parent_name ? &mmc_clk->parent_name : शून्य);
	init.num_parents = (mmc_clk->parent_name ? 1 : 0);
	mclk->hw.init = &init;

	mclk->id = mmc_clk->id;
	mclk->clken_reg = base + mmc_clk->clken_reg;
	mclk->clken_bit = mmc_clk->clken_bit;
	mclk->भाग_reg = base + mmc_clk->भाग_reg;
	mclk->भाग_off = mmc_clk->भाग_off;
	mclk->भाग_bits = mmc_clk->भाग_bits;
	mclk->drv_reg = base + mmc_clk->drv_reg;
	mclk->drv_off = mmc_clk->drv_off;
	mclk->drv_bits = mmc_clk->drv_bits;
	mclk->sam_reg = base + mmc_clk->sam_reg;
	mclk->sam_off = mmc_clk->sam_off;
	mclk->sam_bits = mmc_clk->sam_bits;

	clk = clk_रेजिस्टर(शून्य, &mclk->hw);
	अगर (WARN_ON(IS_ERR(clk)))
		kमुक्त(mclk);
	वापस clk;
पूर्ण

अटल व्योम __init hi3620_mmc_clk_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base;
	पूर्णांक i, num = ARRAY_SIZE(hi3620_mmc_clks);
	काष्ठा clk_onecell_data *clk_data;

	अगर (!node) अणु
		pr_err("failed to find pctrl node in DTS\n");
		वापस;
	पूर्ण

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("failed to map pctrl\n");
		वापस;
	पूर्ण

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (WARN_ON(!clk_data))
		वापस;

	clk_data->clks = kसुस्मृति(num, माप(*clk_data->clks), GFP_KERNEL);
	अगर (!clk_data->clks)
		वापस;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा hisi_mmc_घड़ी *mmc_clk = &hi3620_mmc_clks[i];
		clk_data->clks[mmc_clk->id] =
			hisi_रेजिस्टर_clk_mmc(mmc_clk, base, node);
	पूर्ण

	clk_data->clk_num = num;
	of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

CLK_OF_DECLARE(hi3620_mmc_clk, "hisilicon,hi3620-mmc-clock", hi3620_mmc_clk_init);
