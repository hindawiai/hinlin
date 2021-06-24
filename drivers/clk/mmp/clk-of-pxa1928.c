<शैली गुरु>
/*
 * pxa1928 घड़ी framework source file
 *
 * Copyright (C) 2015 Linaro, Ltd.
 * Rob Herring <robh@kernel.org>
 *
 * Based on drivers/clk/mmp/clk-of-mmp2.c:
 * Copyright (C) 2012 Marvell
 * Chao Xie <xiechao.mail@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <dt-bindings/घड़ी/marvell,pxa1928.h>

#समावेश "clk.h"
#समावेश "reset.h"

#घोषणा MPMU_UART_PLL	0x14

काष्ठा pxa1928_clk_unit अणु
	काष्ठा mmp_clk_unit unit;
	व्योम __iomem *mpmu_base;
	व्योम __iomem *apmu_base;
	व्योम __iomem *apbc_base;
	व्योम __iomem *apbcp_base;
पूर्ण;

अटल काष्ठा mmp_param_fixed_rate_clk fixed_rate_clks[] = अणु
	अणु0, "clk32", शून्य, 0, 32768पूर्ण,
	अणु0, "vctcxo", शून्य, 0, 26000000पूर्ण,
	अणु0, "pll1_624", शून्य, 0, 624000000पूर्ण,
	अणु0, "pll5p", शून्य, 0, 832000000पूर्ण,
	अणु0, "pll5", शून्य, 0, 1248000000पूर्ण,
	अणु0, "usb_pll", शून्य, 0, 480000000पूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_fixed_factor_clk fixed_factor_clks[] = अणु
	अणु0, "pll1_d2", "pll1_624", 1, 2, 0पूर्ण,
	अणु0, "pll1_d9", "pll1_624", 1, 9, 0पूर्ण,
	अणु0, "pll1_d12", "pll1_624", 1, 12, 0पूर्ण,
	अणु0, "pll1_d16", "pll1_624", 1, 16, 0पूर्ण,
	अणु0, "pll1_d20", "pll1_624", 1, 20, 0पूर्ण,
	अणु0, "pll1_416", "pll1_624", 2, 3, 0पूर्ण,
	अणु0, "vctcxo_d2", "vctcxo", 1, 2, 0पूर्ण,
	अणु0, "vctcxo_d4", "vctcxo", 1, 4, 0पूर्ण,
पूर्ण;

अटल काष्ठा mmp_clk_factor_masks uart_factor_masks = अणु
	.factor = 2,
	.num_mask = 0x1fff,
	.den_mask = 0x1fff,
	.num_shअगरt = 16,
	.den_shअगरt = 0,
पूर्ण;

अटल काष्ठा mmp_clk_factor_tbl uart_factor_tbl[] = अणु
	अणु.num = 832, .den = 234पूर्ण,	/*58.5MHZ */
	अणु.num = 1, .den = 1पूर्ण,		/*26MHZ */
पूर्ण;

अटल व्योम pxa1928_pll_init(काष्ठा pxa1928_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_रेजिस्टर_fixed_rate_clks(unit, fixed_rate_clks,
					ARRAY_SIZE(fixed_rate_clks));

	mmp_रेजिस्टर_fixed_factor_clks(unit, fixed_factor_clks,
					ARRAY_SIZE(fixed_factor_clks));

	mmp_clk_रेजिस्टर_factor("uart_pll", "pll1_416",
				CLK_SET_RATE_PARENT,
				pxa_unit->mpmu_base + MPMU_UART_PLL,
				&uart_factor_masks, uart_factor_tbl,
				ARRAY_SIZE(uart_factor_tbl), शून्य);
पूर्ण

अटल DEFINE_SPINLOCK(uart0_lock);
अटल DEFINE_SPINLOCK(uart1_lock);
अटल DEFINE_SPINLOCK(uart2_lock);
अटल DEFINE_SPINLOCK(uart3_lock);
अटल स्थिर अक्षर *uart_parent_names[] = अणु"uart_pll", "vctcxo"पूर्ण;

अटल DEFINE_SPINLOCK(ssp0_lock);
अटल DEFINE_SPINLOCK(ssp1_lock);
अटल स्थिर अक्षर *ssp_parent_names[] = अणु"vctcxo_d4", "vctcxo_d2", "vctcxo", "pll1_d12"पूर्ण;

अटल DEFINE_SPINLOCK(reset_lock);

अटल काष्ठा mmp_param_mux_clk apbc_mux_clks[] = अणु
	अणु0, "uart0_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_UART0 * 4, 4, 3, 0, &uart0_lockपूर्ण,
	अणु0, "uart1_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_UART1 * 4, 4, 3, 0, &uart1_lockपूर्ण,
	अणु0, "uart2_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_UART2 * 4, 4, 3, 0, &uart2_lockपूर्ण,
	अणु0, "uart3_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_UART3 * 4, 4, 3, 0, &uart3_lockपूर्ण,
	अणु0, "ssp0_mux", ssp_parent_names, ARRAY_SIZE(ssp_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_SSP0 * 4, 4, 3, 0, &ssp0_lockपूर्ण,
	अणु0, "ssp1_mux", ssp_parent_names, ARRAY_SIZE(ssp_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_SSP1 * 4, 4, 3, 0, &ssp1_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_gate_clk apbc_gate_clks[] = अणु
	अणुPXA1928_CLK_TWSI0, "twsi0_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_TWSI0 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_TWSI1, "twsi1_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_TWSI1 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_TWSI2, "twsi2_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_TWSI2 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_TWSI3, "twsi3_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_TWSI3 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_TWSI4, "twsi4_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_TWSI4 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_TWSI5, "twsi5_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_TWSI5 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_GPIO, "gpio_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_GPIO * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_KPC, "kpc_clk", "clk32", CLK_SET_RATE_PARENT, PXA1928_CLK_KPC * 4, 0x3, 0x3, 0x0, MMP_CLK_GATE_NEED_DELAY, शून्यपूर्ण,
	अणुPXA1928_CLK_RTC, "rtc_clk", "clk32", CLK_SET_RATE_PARENT, PXA1928_CLK_RTC * 4, 0x83, 0x83, 0x0, MMP_CLK_GATE_NEED_DELAY, शून्यपूर्ण,
	अणुPXA1928_CLK_PWM0, "pwm0_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_PWM0 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_PWM1, "pwm1_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_PWM1 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_PWM2, "pwm2_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_PWM2 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA1928_CLK_PWM3, "pwm3_clk", "vctcxo", CLK_SET_RATE_PARENT, PXA1928_CLK_PWM3 * 4, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	/* The gate घड़ीs has mux parent. */
	अणुPXA1928_CLK_UART0, "uart0_clk", "uart0_mux", CLK_SET_RATE_PARENT, PXA1928_CLK_UART0 * 4, 0x3, 0x3, 0x0, 0, &uart0_lockपूर्ण,
	अणुPXA1928_CLK_UART1, "uart1_clk", "uart1_mux", CLK_SET_RATE_PARENT, PXA1928_CLK_UART1 * 4, 0x3, 0x3, 0x0, 0, &uart1_lockपूर्ण,
	अणुPXA1928_CLK_UART2, "uart2_clk", "uart2_mux", CLK_SET_RATE_PARENT, PXA1928_CLK_UART2 * 4, 0x3, 0x3, 0x0, 0, &uart2_lockपूर्ण,
	अणुPXA1928_CLK_UART3, "uart3_clk", "uart3_mux", CLK_SET_RATE_PARENT, PXA1928_CLK_UART3 * 4, 0x3, 0x3, 0x0, 0, &uart3_lockपूर्ण,
	अणुPXA1928_CLK_SSP0, "ssp0_clk", "ssp0_mux", CLK_SET_RATE_PARENT, PXA1928_CLK_SSP0 * 4, 0x3, 0x3, 0x0, 0, &ssp0_lockपूर्ण,
	अणुPXA1928_CLK_SSP1, "ssp1_clk", "ssp1_mux", CLK_SET_RATE_PARENT, PXA1928_CLK_SSP1 * 4, 0x3, 0x3, 0x0, 0, &ssp1_lockपूर्ण,
पूर्ण;

अटल व्योम pxa1928_apb_periph_clk_init(काष्ठा pxa1928_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_रेजिस्टर_mux_clks(unit, apbc_mux_clks, pxa_unit->apbc_base,
				ARRAY_SIZE(apbc_mux_clks));

	mmp_रेजिस्टर_gate_clks(unit, apbc_gate_clks, pxa_unit->apbc_base,
				ARRAY_SIZE(apbc_gate_clks));
पूर्ण

अटल DEFINE_SPINLOCK(sdh0_lock);
अटल DEFINE_SPINLOCK(sdh1_lock);
अटल DEFINE_SPINLOCK(sdh2_lock);
अटल DEFINE_SPINLOCK(sdh3_lock);
अटल DEFINE_SPINLOCK(sdh4_lock);
अटल स्थिर अक्षर *sdh_parent_names[] = अणु"pll1_624", "pll5p", "pll5", "pll1_416"पूर्ण;

अटल DEFINE_SPINLOCK(usb_lock);

अटल काष्ठा mmp_param_mux_clk apmu_mux_clks[] = अणु
	अणु0, "sdh_mux", sdh_parent_names, ARRAY_SIZE(sdh_parent_names), CLK_SET_RATE_PARENT, PXA1928_CLK_SDH0 * 4, 8, 2, 0, &sdh0_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_भाग_clk apmu_भाग_clks[] = अणु
	अणु0, "sdh_div", "sdh_mux", 0, PXA1928_CLK_SDH0 * 4, 10, 4, CLK_DIVIDER_ONE_BASED, &sdh0_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_gate_clk apmu_gate_clks[] = अणु
	अणुPXA1928_CLK_USB, "usb_clk", "usb_pll", 0, PXA1928_CLK_USB * 4, 0x9, 0x9, 0x0, 0, &usb_lockपूर्ण,
	अणुPXA1928_CLK_HSIC, "hsic_clk", "usb_pll", 0, PXA1928_CLK_HSIC * 4, 0x9, 0x9, 0x0, 0, &usb_lockपूर्ण,
	/* The gate घड़ीs has mux parent. */
	अणुPXA1928_CLK_SDH0, "sdh0_clk", "sdh_div", CLK_SET_RATE_PARENT, PXA1928_CLK_SDH0 * 4, 0x1b, 0x1b, 0x0, 0, &sdh0_lockपूर्ण,
	अणुPXA1928_CLK_SDH1, "sdh1_clk", "sdh_div", CLK_SET_RATE_PARENT, PXA1928_CLK_SDH1 * 4, 0x1b, 0x1b, 0x0, 0, &sdh1_lockपूर्ण,
	अणुPXA1928_CLK_SDH2, "sdh2_clk", "sdh_div", CLK_SET_RATE_PARENT, PXA1928_CLK_SDH2 * 4, 0x1b, 0x1b, 0x0, 0, &sdh2_lockपूर्ण,
	अणुPXA1928_CLK_SDH3, "sdh3_clk", "sdh_div", CLK_SET_RATE_PARENT, PXA1928_CLK_SDH3 * 4, 0x1b, 0x1b, 0x0, 0, &sdh3_lockपूर्ण,
	अणुPXA1928_CLK_SDH4, "sdh4_clk", "sdh_div", CLK_SET_RATE_PARENT, PXA1928_CLK_SDH4 * 4, 0x1b, 0x1b, 0x0, 0, &sdh4_lockपूर्ण,
पूर्ण;

अटल व्योम pxa1928_axi_periph_clk_init(काष्ठा pxa1928_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_रेजिस्टर_mux_clks(unit, apmu_mux_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_mux_clks));

	mmp_रेजिस्टर_भाग_clks(unit, apmu_भाग_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_भाग_clks));

	mmp_रेजिस्टर_gate_clks(unit, apmu_gate_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_gate_clks));
पूर्ण

अटल व्योम pxa1928_clk_reset_init(काष्ठा device_node *np,
				काष्ठा pxa1928_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_reset_cell *cells;
	पूर्णांक i, base, nr_resets;

	nr_resets = ARRAY_SIZE(apbc_gate_clks);
	cells = kसुस्मृति(nr_resets, माप(*cells), GFP_KERNEL);
	अगर (!cells)
		वापस;

	base = 0;
	क्रम (i = 0; i < nr_resets; i++) अणु
		cells[base + i].clk_id = apbc_gate_clks[i].id;
		cells[base + i].reg =
			pxa_unit->apbc_base + apbc_gate_clks[i].offset;
		cells[base + i].flags = 0;
		cells[base + i].lock = apbc_gate_clks[i].lock;
		cells[base + i].bits = 0x4;
	पूर्ण

	mmp_clk_reset_रेजिस्टर(np, cells, nr_resets);
पूर्ण

अटल व्योम __init pxa1928_mpmu_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा pxa1928_clk_unit *pxa_unit;

	pxa_unit = kzalloc(माप(*pxa_unit), GFP_KERNEL);
	अगर (!pxa_unit)
		वापस;

	pxa_unit->mpmu_base = of_iomap(np, 0);
	अगर (!pxa_unit->mpmu_base) अणु
		pr_err("failed to map mpmu registers\n");
		kमुक्त(pxa_unit);
		वापस;
	पूर्ण

	pxa1928_pll_init(pxa_unit);
पूर्ण
CLK_OF_DECLARE(pxa1928_mpmu_clk, "marvell,pxa1928-mpmu", pxa1928_mpmu_clk_init);

अटल व्योम __init pxa1928_apmu_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा pxa1928_clk_unit *pxa_unit;

	pxa_unit = kzalloc(माप(*pxa_unit), GFP_KERNEL);
	अगर (!pxa_unit)
		वापस;

	pxa_unit->apmu_base = of_iomap(np, 0);
	अगर (!pxa_unit->apmu_base) अणु
		pr_err("failed to map apmu registers\n");
		kमुक्त(pxa_unit);
		वापस;
	पूर्ण

	mmp_clk_init(np, &pxa_unit->unit, PXA1928_APMU_NR_CLKS);

	pxa1928_axi_periph_clk_init(pxa_unit);
पूर्ण
CLK_OF_DECLARE(pxa1928_apmu_clk, "marvell,pxa1928-apmu", pxa1928_apmu_clk_init);

अटल व्योम __init pxa1928_apbc_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा pxa1928_clk_unit *pxa_unit;

	pxa_unit = kzalloc(माप(*pxa_unit), GFP_KERNEL);
	अगर (!pxa_unit)
		वापस;

	pxa_unit->apbc_base = of_iomap(np, 0);
	अगर (!pxa_unit->apbc_base) अणु
		pr_err("failed to map apbc registers\n");
		kमुक्त(pxa_unit);
		वापस;
	पूर्ण

	mmp_clk_init(np, &pxa_unit->unit, PXA1928_APBC_NR_CLKS);

	pxa1928_apb_periph_clk_init(pxa_unit);
	pxa1928_clk_reset_init(np, pxa_unit);
पूर्ण
CLK_OF_DECLARE(pxa1928_apbc_clk, "marvell,pxa1928-apbc", pxa1928_apbc_clk_init);
