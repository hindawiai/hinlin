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

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/of_address.h>

#समावेश <dt-bindings/घड़ी/marvell,pxa910.h>

#समावेश "clk.h"
#समावेश "reset.h"

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
#घोषणा APBC_TIMER0	0x30
#घोषणा APBC_TIMER1	0x44
#घोषणा APBCP_TWSI1	0x28
#घोषणा APBCP_UART2	0x1c
#घोषणा APMU_SDH0	0x54
#घोषणा APMU_SDH1	0x58
#घोषणा APMU_USB	0x5c
#घोषणा APMU_DISP0	0x4c
#घोषणा APMU_CCIC0	0x50
#घोषणा APMU_DFC	0x60
#घोषणा MPMU_UART_PLL	0x14

काष्ठा pxa910_clk_unit अणु
	काष्ठा mmp_clk_unit unit;
	व्योम __iomem *mpmu_base;
	व्योम __iomem *apmu_base;
	व्योम __iomem *apbc_base;
	व्योम __iomem *apbcp_base;
पूर्ण;

अटल काष्ठा mmp_param_fixed_rate_clk fixed_rate_clks[] = अणु
	अणुPXA910_CLK_CLK32, "clk32", शून्य, 0, 32768पूर्ण,
	अणुPXA910_CLK_VCTCXO, "vctcxo", शून्य, 0, 26000000पूर्ण,
	अणुPXA910_CLK_PLL1, "pll1", शून्य, 0, 624000000पूर्ण,
	अणुPXA910_CLK_USB_PLL, "usb_pll", शून्य, 0, 480000000पूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_fixed_factor_clk fixed_factor_clks[] = अणु
	अणुPXA910_CLK_PLL1_2, "pll1_2", "pll1", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_4, "pll1_4", "pll1_2", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_8, "pll1_8", "pll1_4", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_16, "pll1_16", "pll1_8", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_6, "pll1_6", "pll1_2", 1, 3, 0पूर्ण,
	अणुPXA910_CLK_PLL1_12, "pll1_12", "pll1_6", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_24, "pll1_24", "pll1_12", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_48, "pll1_48", "pll1_24", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_96, "pll1_96", "pll1_48", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_192, "pll1_192", "pll1_96", 1, 2, 0पूर्ण,
	अणुPXA910_CLK_PLL1_13, "pll1_13", "pll1", 1, 13, 0पूर्ण,
	अणुPXA910_CLK_PLL1_13_1_5, "pll1_13_1_5", "pll1_13", 2, 3, 0पूर्ण,
	अणुPXA910_CLK_PLL1_2_1_5, "pll1_2_1_5", "pll1_2", 2, 3, 0पूर्ण,
	अणुPXA910_CLK_PLL1_3_16, "pll1_3_16", "pll1", 3, 16, 0पूर्ण,
पूर्ण;

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

अटल व्योम pxa910_pll_init(काष्ठा pxa910_clk_unit *pxa_unit)
अणु
	काष्ठा clk *clk;
	काष्ठा mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_रेजिस्टर_fixed_rate_clks(unit, fixed_rate_clks,
					ARRAY_SIZE(fixed_rate_clks));

	mmp_रेजिस्टर_fixed_factor_clks(unit, fixed_factor_clks,
					ARRAY_SIZE(fixed_factor_clks));

	clk = mmp_clk_रेजिस्टर_factor("uart_pll", "pll1_4",
				CLK_SET_RATE_PARENT,
				pxa_unit->mpmu_base + MPMU_UART_PLL,
				&uart_factor_masks, uart_factor_tbl,
				ARRAY_SIZE(uart_factor_tbl), शून्य);
	mmp_clk_add(unit, PXA910_CLK_UART_PLL, clk);
पूर्ण

अटल DEFINE_SPINLOCK(uart0_lock);
अटल DEFINE_SPINLOCK(uart1_lock);
अटल DEFINE_SPINLOCK(uart2_lock);
अटल स्थिर अक्षर *uart_parent_names[] = अणु"pll1_3_16", "uart_pll"पूर्ण;

अटल DEFINE_SPINLOCK(ssp0_lock);
अटल DEFINE_SPINLOCK(ssp1_lock);
अटल स्थिर अक्षर *ssp_parent_names[] = अणु"pll1_96", "pll1_48", "pll1_24", "pll1_12"पूर्ण;

अटल DEFINE_SPINLOCK(समयr0_lock);
अटल DEFINE_SPINLOCK(समयr1_lock);
अटल स्थिर अक्षर *समयr_parent_names[] = अणु"pll1_48", "clk32", "pll1_96"पूर्ण;

अटल DEFINE_SPINLOCK(reset_lock);

अटल काष्ठा mmp_param_mux_clk apbc_mux_clks[] = अणु
	अणु0, "uart0_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, APBC_UART0, 4, 3, 0, &uart0_lockपूर्ण,
	अणु0, "uart1_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, APBC_UART1, 4, 3, 0, &uart1_lockपूर्ण,
	अणु0, "ssp0_mux", ssp_parent_names, ARRAY_SIZE(ssp_parent_names), CLK_SET_RATE_PARENT, APBC_SSP0, 4, 3, 0, &ssp0_lockपूर्ण,
	अणु0, "ssp1_mux", ssp_parent_names, ARRAY_SIZE(ssp_parent_names), CLK_SET_RATE_PARENT, APBC_SSP1, 4, 3, 0, &ssp1_lockपूर्ण,
	अणु0, "timer0_mux", समयr_parent_names, ARRAY_SIZE(समयr_parent_names), CLK_SET_RATE_PARENT, APBC_TIMER0, 4, 3, 0, &समयr0_lockपूर्ण,
	अणु0, "timer1_mux", समयr_parent_names, ARRAY_SIZE(समयr_parent_names), CLK_SET_RATE_PARENT, APBC_TIMER1, 4, 3, 0, &समयr1_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_mux_clk apbcp_mux_clks[] = अणु
	अणु0, "uart2_mux", uart_parent_names, ARRAY_SIZE(uart_parent_names), CLK_SET_RATE_PARENT, APBCP_UART2, 4, 3, 0, &uart2_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_gate_clk apbc_gate_clks[] = अणु
	अणुPXA910_CLK_TWSI0, "twsi0_clk", "pll1_13_1_5", CLK_SET_RATE_PARENT, APBC_TWSI0, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA910_CLK_GPIO, "gpio_clk", "vctcxo", CLK_SET_RATE_PARENT, APBC_GPIO, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA910_CLK_KPC, "kpc_clk", "clk32", CLK_SET_RATE_PARENT, APBC_KPC, 0x3, 0x3, 0x0, MMP_CLK_GATE_NEED_DELAY, शून्यपूर्ण,
	अणुPXA910_CLK_RTC, "rtc_clk", "clk32", CLK_SET_RATE_PARENT, APBC_RTC, 0x83, 0x83, 0x0, MMP_CLK_GATE_NEED_DELAY, शून्यपूर्ण,
	अणुPXA910_CLK_PWM0, "pwm0_clk", "pll1_48", CLK_SET_RATE_PARENT, APBC_PWM0, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA910_CLK_PWM1, "pwm1_clk", "pll1_48", CLK_SET_RATE_PARENT, APBC_PWM1, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA910_CLK_PWM2, "pwm2_clk", "pll1_48", CLK_SET_RATE_PARENT, APBC_PWM2, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	अणुPXA910_CLK_PWM3, "pwm3_clk", "pll1_48", CLK_SET_RATE_PARENT, APBC_PWM3, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	/* The gate घड़ीs has mux parent. */
	अणुPXA910_CLK_UART0, "uart0_clk", "uart0_mux", CLK_SET_RATE_PARENT, APBC_UART0, 0x3, 0x3, 0x0, 0, &uart0_lockपूर्ण,
	अणुPXA910_CLK_UART1, "uart1_clk", "uart1_mux", CLK_SET_RATE_PARENT, APBC_UART1, 0x3, 0x3, 0x0, 0, &uart1_lockपूर्ण,
	अणुPXA910_CLK_SSP0, "ssp0_clk", "ssp0_mux", CLK_SET_RATE_PARENT, APBC_SSP0, 0x3, 0x3, 0x0, 0, &ssp0_lockपूर्ण,
	अणुPXA910_CLK_SSP1, "ssp1_clk", "ssp1_mux", CLK_SET_RATE_PARENT, APBC_SSP1, 0x3, 0x3, 0x0, 0, &ssp1_lockपूर्ण,
	अणुPXA910_CLK_TIMER0, "timer0_clk", "timer0_mux", CLK_SET_RATE_PARENT, APBC_TIMER0, 0x3, 0x3, 0x0, 0, &समयr0_lockपूर्ण,
	अणुPXA910_CLK_TIMER1, "timer1_clk", "timer1_mux", CLK_SET_RATE_PARENT, APBC_TIMER1, 0x3, 0x3, 0x0, 0, &समयr1_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_gate_clk apbcp_gate_clks[] = अणु
	अणुPXA910_CLK_TWSI1, "twsi1_clk", "pll1_13_1_5", CLK_SET_RATE_PARENT, APBCP_TWSI1, 0x3, 0x3, 0x0, 0, &reset_lockपूर्ण,
	/* The gate घड़ीs has mux parent. */
	अणुPXA910_CLK_UART2, "uart2_clk", "uart2_mux", CLK_SET_RATE_PARENT, APBCP_UART2, 0x3, 0x3, 0x0, 0, &uart2_lockपूर्ण,
पूर्ण;

अटल व्योम pxa910_apb_periph_clk_init(काष्ठा pxa910_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_रेजिस्टर_mux_clks(unit, apbc_mux_clks, pxa_unit->apbc_base,
				ARRAY_SIZE(apbc_mux_clks));

	mmp_रेजिस्टर_mux_clks(unit, apbcp_mux_clks, pxa_unit->apbcp_base,
				ARRAY_SIZE(apbcp_mux_clks));

	mmp_रेजिस्टर_gate_clks(unit, apbc_gate_clks, pxa_unit->apbc_base,
				ARRAY_SIZE(apbc_gate_clks));

	mmp_रेजिस्टर_gate_clks(unit, apbcp_gate_clks, pxa_unit->apbcp_base,
				ARRAY_SIZE(apbcp_gate_clks));
पूर्ण

अटल DEFINE_SPINLOCK(sdh0_lock);
अटल DEFINE_SPINLOCK(sdh1_lock);
अटल स्थिर अक्षर *sdh_parent_names[] = अणु"pll1_12", "pll1_13"पूर्ण;

अटल DEFINE_SPINLOCK(usb_lock);

अटल DEFINE_SPINLOCK(disp0_lock);
अटल स्थिर अक्षर *disp_parent_names[] = अणु"pll1_2", "pll1_12"पूर्ण;

अटल DEFINE_SPINLOCK(ccic0_lock);
अटल स्थिर अक्षर *ccic_parent_names[] = अणु"pll1_2", "pll1_12"पूर्ण;
अटल स्थिर अक्षर *ccic_phy_parent_names[] = अणु"pll1_6", "pll1_12"पूर्ण;

अटल काष्ठा mmp_param_mux_clk apmu_mux_clks[] = अणु
	अणु0, "sdh0_mux", sdh_parent_names, ARRAY_SIZE(sdh_parent_names), CLK_SET_RATE_PARENT, APMU_SDH0, 6, 1, 0, &sdh0_lockपूर्ण,
	अणु0, "sdh1_mux", sdh_parent_names, ARRAY_SIZE(sdh_parent_names), CLK_SET_RATE_PARENT, APMU_SDH1, 6, 1, 0, &sdh1_lockपूर्ण,
	अणु0, "disp0_mux", disp_parent_names, ARRAY_SIZE(disp_parent_names), CLK_SET_RATE_PARENT, APMU_DISP0, 6, 1, 0, &disp0_lockपूर्ण,
	अणु0, "ccic0_mux", ccic_parent_names, ARRAY_SIZE(ccic_parent_names), CLK_SET_RATE_PARENT, APMU_CCIC0, 6, 1, 0, &ccic0_lockपूर्ण,
	अणु0, "ccic0_phy_mux", ccic_phy_parent_names, ARRAY_SIZE(ccic_phy_parent_names), CLK_SET_RATE_PARENT, APMU_CCIC0, 7, 1, 0, &ccic0_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_भाग_clk apmu_भाग_clks[] = अणु
	अणु0, "ccic0_sphy_div", "ccic0_mux", CLK_SET_RATE_PARENT, APMU_CCIC0, 10, 5, 0, &ccic0_lockपूर्ण,
पूर्ण;

अटल काष्ठा mmp_param_gate_clk apmu_gate_clks[] = अणु
	अणुPXA910_CLK_DFC, "dfc_clk", "pll1_4", CLK_SET_RATE_PARENT, APMU_DFC, 0x19b, 0x19b, 0x0, 0, शून्यपूर्ण,
	अणुPXA910_CLK_USB, "usb_clk", "usb_pll", 0, APMU_USB, 0x9, 0x9, 0x0, 0, &usb_lockपूर्ण,
	अणुPXA910_CLK_SPH, "sph_clk", "usb_pll", 0, APMU_USB, 0x12, 0x12, 0x0, 0, &usb_lockपूर्ण,
	/* The gate घड़ीs has mux parent. */
	अणुPXA910_CLK_SDH0, "sdh0_clk", "sdh0_mux", CLK_SET_RATE_PARENT, APMU_SDH0, 0x1b, 0x1b, 0x0, 0, &sdh0_lockपूर्ण,
	अणुPXA910_CLK_SDH1, "sdh1_clk", "sdh1_mux", CLK_SET_RATE_PARENT, APMU_SDH1, 0x1b, 0x1b, 0x0, 0, &sdh1_lockपूर्ण,
	अणुPXA910_CLK_DISP0, "disp0_clk", "disp0_mux", CLK_SET_RATE_PARENT, APMU_DISP0, 0x1b, 0x1b, 0x0, 0, &disp0_lockपूर्ण,
	अणुPXA910_CLK_CCIC0, "ccic0_clk", "ccic0_mux", CLK_SET_RATE_PARENT, APMU_CCIC0, 0x1b, 0x1b, 0x0, 0, &ccic0_lockपूर्ण,
	अणुPXA910_CLK_CCIC0_PHY, "ccic0_phy_clk", "ccic0_phy_mux", CLK_SET_RATE_PARENT, APMU_CCIC0, 0x24, 0x24, 0x0, 0, &ccic0_lockपूर्ण,
	अणुPXA910_CLK_CCIC0_SPHY, "ccic0_sphy_clk", "ccic0_sphy_div", CLK_SET_RATE_PARENT, APMU_CCIC0, 0x300, 0x300, 0x0, 0, &ccic0_lockपूर्ण,
पूर्ण;

अटल व्योम pxa910_axi_periph_clk_init(काष्ठा pxa910_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_रेजिस्टर_mux_clks(unit, apmu_mux_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_mux_clks));

	mmp_रेजिस्टर_भाग_clks(unit, apmu_भाग_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_भाग_clks));

	mmp_रेजिस्टर_gate_clks(unit, apmu_gate_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_gate_clks));
पूर्ण

अटल व्योम pxa910_clk_reset_init(काष्ठा device_node *np,
				काष्ठा pxa910_clk_unit *pxa_unit)
अणु
	काष्ठा mmp_clk_reset_cell *cells;
	पूर्णांक i, base, nr_resets_apbc, nr_resets_apbcp, nr_resets;

	nr_resets_apbc = ARRAY_SIZE(apbc_gate_clks);
	nr_resets_apbcp = ARRAY_SIZE(apbcp_gate_clks);
	nr_resets = nr_resets_apbc + nr_resets_apbcp;
	cells = kसुस्मृति(nr_resets, माप(*cells), GFP_KERNEL);
	अगर (!cells)
		वापस;

	base = 0;
	क्रम (i = 0; i < nr_resets_apbc; i++) अणु
		cells[base + i].clk_id = apbc_gate_clks[i].id;
		cells[base + i].reg =
			pxa_unit->apbc_base + apbc_gate_clks[i].offset;
		cells[base + i].flags = 0;
		cells[base + i].lock = apbc_gate_clks[i].lock;
		cells[base + i].bits = 0x4;
	पूर्ण

	base = nr_resets_apbc;
	क्रम (i = 0; i < nr_resets_apbcp; i++) अणु
		cells[base + i].clk_id = apbcp_gate_clks[i].id;
		cells[base + i].reg =
			pxa_unit->apbc_base + apbc_gate_clks[i].offset;
		cells[base + i].flags = 0;
		cells[base + i].lock = apbc_gate_clks[i].lock;
		cells[base + i].bits = 0x4;
	पूर्ण

	mmp_clk_reset_रेजिस्टर(np, cells, nr_resets);
पूर्ण

अटल व्योम __init pxa910_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा pxa910_clk_unit *pxa_unit;

	pxa_unit = kzalloc(माप(*pxa_unit), GFP_KERNEL);
	अगर (!pxa_unit)
		वापस;

	pxa_unit->mpmu_base = of_iomap(np, 0);
	अगर (!pxa_unit->mpmu_base) अणु
		pr_err("failed to map mpmu registers\n");
		जाओ मुक्त_memory;
	पूर्ण

	pxa_unit->apmu_base = of_iomap(np, 1);
	अगर (!pxa_unit->apmu_base) अणु
		pr_err("failed to map apmu registers\n");
		जाओ unmap_mpmu_region;
	पूर्ण

	pxa_unit->apbc_base = of_iomap(np, 2);
	अगर (!pxa_unit->apbc_base) अणु
		pr_err("failed to map apbc registers\n");
		जाओ unmap_apmu_region;
	पूर्ण

	pxa_unit->apbcp_base = of_iomap(np, 3);
	अगर (!pxa_unit->apbcp_base) अणु
		pr_err("failed to map apbcp registers\n");
		जाओ unmap_apbc_region;
	पूर्ण

	mmp_clk_init(np, &pxa_unit->unit, PXA910_NR_CLKS);

	pxa910_pll_init(pxa_unit);

	pxa910_apb_periph_clk_init(pxa_unit);

	pxa910_axi_periph_clk_init(pxa_unit);

	pxa910_clk_reset_init(np, pxa_unit);

	वापस;

unmap_apbc_region:
	iounmap(pxa_unit->apbc_base);
unmap_apmu_region:
	iounmap(pxa_unit->apmu_base);
unmap_mpmu_region:
	iounmap(pxa_unit->mpmu_base);
मुक्त_memory:
	kमुक्त(pxa_unit);
पूर्ण

CLK_OF_DECLARE(pxa910_clk, "marvell,pxa910-clock", pxa910_clk_init);
