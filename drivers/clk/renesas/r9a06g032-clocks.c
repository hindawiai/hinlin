<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R9A06G032 घड़ी driver
 *
 * Copyright (C) 2018 Renesas Electronics Europe Limited
 *
 * Michel Pollet <michel.pollet@bp.renesas.com>, <buserror@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <dt-bindings/घड़ी/r9a06g032-sysctrl.h>

काष्ठा r9a06g032_gate अणु
	u16 gate, reset, पढ़ोy, midle,
		scon, mirack, mistat;
पूर्ण;

/* This is used to describe a घड़ी क्रम instantiation */
काष्ठा r9a06g032_clkdesc अणु
	स्थिर अक्षर *name;
	uपूर्णांक32_t managed: 1;
	uपूर्णांक32_t type: 3;
	uपूर्णांक32_t index: 8;
	uपूर्णांक32_t source : 8; /* source index + 1 (0 == none) */
	/* these are used to populate the bitsel काष्ठा */
	जोड़ अणु
		काष्ठा r9a06g032_gate gate;
		/* क्रम भागiders */
		काष्ठा अणु
			अचिन्हित पूर्णांक भाग_min : 10, भाग_max : 10, reg: 10;
			u16 भाग_प्रकारable[4];
		पूर्ण;
		/* For fixed-factor ones */
		काष्ठा अणु
			u16 भाग, mul;
		पूर्ण;
		अचिन्हित पूर्णांक factor;
		अचिन्हित पूर्णांक frequency;
		/* क्रम dual gate */
		काष्ठा अणु
			uपूर्णांक16_t group : 1, index: 3;
			u16 sel, g1, r1, g2, r2;
		पूर्ण dual;
	पूर्ण;
पूर्ण;

#घोषणा I_GATE(_clk, _rst, _rdy, _midle, _scon, _mirack, _mistat) \
	अणु .gate = _clk, .reset = _rst, \
		.पढ़ोy = _rdy, .midle = _midle, \
		.scon = _scon, .mirack = _mirack, .mistat = _mistat पूर्ण
#घोषणा D_GATE(_idx, _n, _src, ...) \
	अणु .type = K_GATE, .index = R9A06G032_##_idx, \
		.source = 1 + R9A06G032_##_src, .name = _n, \
		.gate = I_GATE(__VA_ARGS__) पूर्ण
#घोषणा D_MODULE(_idx, _n, _src, ...) \
	अणु .type = K_GATE, .index = R9A06G032_##_idx, \
		.source = 1 + R9A06G032_##_src, .name = _n, \
		.managed = 1, .gate = I_GATE(__VA_ARGS__) पूर्ण
#घोषणा D_ROOT(_idx, _n, _mul, _भाग) \
	अणु .type = K_FFC, .index = R9A06G032_##_idx, .name = _n, \
		.भाग = _भाग, .mul = _mul पूर्ण
#घोषणा D_FFC(_idx, _n, _src, _भाग) \
	अणु .type = K_FFC, .index = R9A06G032_##_idx, \
		.source = 1 + R9A06G032_##_src, .name = _n, \
		.भाग = _भाग, .mul = 1पूर्ण
#घोषणा D_DIV(_idx, _n, _src, _reg, _min, _max, ...) \
	अणु .type = K_DIV, .index = R9A06G032_##_idx, \
		.source = 1 + R9A06G032_##_src, .name = _n, \
		.reg = _reg, .भाग_min = _min, .भाग_max = _max, \
		.भाग_प्रकारable = अणु __VA_ARGS__ पूर्ण पूर्ण
#घोषणा D_UGATE(_idx, _n, _src, _g, _gi, _g1, _r1, _g2, _r2) \
	अणु .type = K_DUALGATE, .index = R9A06G032_##_idx, \
		.source = 1 + R9A06G032_##_src, .name = _n, \
		.dual = अणु .group = _g, .index = _gi, \
			.g1 = _g1, .r1 = _r1, .g2 = _g2, .r2 = _r2 पूर्ण, पूर्ण

क्रमागत अणु K_GATE = 0, K_FFC, K_DIV, K_BITSEL, K_DUALGATE पूर्ण;

/* Internal घड़ी IDs */
#घोषणा R9A06G032_CLKOUT		0
#घोषणा R9A06G032_CLKOUT_D10		2
#घोषणा R9A06G032_CLKOUT_D16		3
#घोषणा R9A06G032_CLKOUT_D160		4
#घोषणा R9A06G032_CLKOUT_D1OR2		5
#घोषणा R9A06G032_CLKOUT_D20		6
#घोषणा R9A06G032_CLKOUT_D40		7
#घोषणा R9A06G032_CLKOUT_D5		8
#घोषणा R9A06G032_CLKOUT_D8		9
#घोषणा R9A06G032_DIV_ADC		10
#घोषणा R9A06G032_DIV_I2C		11
#घोषणा R9A06G032_DIV_न_अंकD		12
#घोषणा R9A06G032_DIV_P1_PG		13
#घोषणा R9A06G032_DIV_P2_PG		14
#घोषणा R9A06G032_DIV_P3_PG		15
#घोषणा R9A06G032_DIV_P4_PG		16
#घोषणा R9A06G032_DIV_P5_PG		17
#घोषणा R9A06G032_DIV_P6_PG		18
#घोषणा R9A06G032_DIV_QSPI0		19
#घोषणा R9A06G032_DIV_QSPI1		20
#घोषणा R9A06G032_DIV_REF_SYNC		21
#घोषणा R9A06G032_DIV_SDIO0		22
#घोषणा R9A06G032_DIV_SDIO1		23
#घोषणा R9A06G032_DIV_SWITCH		24
#घोषणा R9A06G032_DIV_UART		25
#घोषणा R9A06G032_DIV_MOTOR		64
#घोषणा R9A06G032_CLK_DDRPHY_PLLCLK_D4	78
#घोषणा R9A06G032_CLK_ECAT100_D4	79
#घोषणा R9A06G032_CLK_HSR100_D2		80
#घोषणा R9A06G032_CLK_REF_SYNC_D4	81
#घोषणा R9A06G032_CLK_REF_SYNC_D8	82
#घोषणा R9A06G032_CLK_SERCOS100_D2	83
#घोषणा R9A06G032_DIV_CA7		84

#घोषणा R9A06G032_UART_GROUP_012	154
#घोषणा R9A06G032_UART_GROUP_34567	155

#घोषणा R9A06G032_CLOCK_COUNT		(R9A06G032_UART_GROUP_34567 + 1)

अटल स्थिर काष्ठा r9a06g032_clkdesc r9a06g032_घड़ीs[] = अणु
	D_ROOT(CLKOUT, "clkout", 25, 1),
	D_ROOT(CLK_PLL_USB, "clk_pll_usb", 12, 10),
	D_FFC(CLKOUT_D10, "clkout_d10", CLKOUT, 10),
	D_FFC(CLKOUT_D16, "clkout_d16", CLKOUT, 16),
	D_FFC(CLKOUT_D160, "clkout_d160", CLKOUT, 160),
	D_DIV(CLKOUT_D1OR2, "clkout_d1or2", CLKOUT, 0, 1, 2),
	D_FFC(CLKOUT_D20, "clkout_d20", CLKOUT, 20),
	D_FFC(CLKOUT_D40, "clkout_d40", CLKOUT, 40),
	D_FFC(CLKOUT_D5, "clkout_d5", CLKOUT, 5),
	D_FFC(CLKOUT_D8, "clkout_d8", CLKOUT, 8),
	D_DIV(DIV_ADC, "div_adc", CLKOUT, 77, 50, 250),
	D_DIV(DIV_I2C, "div_i2c", CLKOUT, 78, 12, 16),
	D_DIV(DIV_न_अंकD, "div_nand", CLKOUT, 82, 12, 32),
	D_DIV(DIV_P1_PG, "div_p1_pg", CLKOUT, 68, 12, 200),
	D_DIV(DIV_P2_PG, "div_p2_pg", CLKOUT, 62, 12, 128),
	D_DIV(DIV_P3_PG, "div_p3_pg", CLKOUT, 64, 8, 128),
	D_DIV(DIV_P4_PG, "div_p4_pg", CLKOUT, 66, 8, 128),
	D_DIV(DIV_P5_PG, "div_p5_pg", CLKOUT, 71, 10, 40),
	D_DIV(DIV_P6_PG, "div_p6_pg", CLKOUT, 18, 12, 64),
	D_DIV(DIV_QSPI0, "div_qspi0", CLKOUT, 73, 3, 7),
	D_DIV(DIV_QSPI1, "div_qspi1", CLKOUT, 25, 3, 7),
	D_DIV(DIV_REF_SYNC, "div_ref_sync", CLKOUT, 56, 2, 16, 2, 4, 8, 16),
	D_DIV(DIV_SDIO0, "div_sdio0", CLKOUT, 74, 20, 128),
	D_DIV(DIV_SDIO1, "div_sdio1", CLKOUT, 75, 20, 128),
	D_DIV(DIV_SWITCH, "div_switch", CLKOUT, 37, 5, 40),
	D_DIV(DIV_UART, "div_uart", CLKOUT, 79, 12, 128),
	D_GATE(CLK_25_PG4, "clk_25_pg4", CLKOUT_D40, 0x749, 0x74a, 0x74b, 0, 0xae3, 0, 0),
	D_GATE(CLK_25_PG5, "clk_25_pg5", CLKOUT_D40, 0x74c, 0x74d, 0x74e, 0, 0xae4, 0, 0),
	D_GATE(CLK_25_PG6, "clk_25_pg6", CLKOUT_D40, 0x74f, 0x750, 0x751, 0, 0xae5, 0, 0),
	D_GATE(CLK_25_PG7, "clk_25_pg7", CLKOUT_D40, 0x752, 0x753, 0x754, 0, 0xae6, 0, 0),
	D_GATE(CLK_25_PG8, "clk_25_pg8", CLKOUT_D40, 0x755, 0x756, 0x757, 0, 0xae7, 0, 0),
	D_GATE(CLK_ADC, "clk_adc", DIV_ADC, 0x1ea, 0x1eb, 0, 0, 0, 0, 0),
	D_GATE(CLK_ECAT100, "clk_ecat100", CLKOUT_D10, 0x405, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_HSR100, "clk_hsr100", CLKOUT_D10, 0x483, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_I2C0, "clk_i2c0", DIV_I2C, 0x1e6, 0x1e7, 0, 0, 0, 0, 0),
	D_GATE(CLK_I2C1, "clk_i2c1", DIV_I2C, 0x1e8, 0x1e9, 0, 0, 0, 0, 0),
	D_GATE(CLK_MII_REF, "clk_mii_ref", CLKOUT_D40, 0x342, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_न_अंकD, "clk_nand", DIV_न_अंकD, 0x284, 0x285, 0, 0, 0, 0, 0),
	D_GATE(CLK_NOUSBP2_PG6, "clk_nousbp2_pg6", DIV_P2_PG, 0x774, 0x775, 0, 0, 0, 0, 0),
	D_GATE(CLK_P1_PG2, "clk_p1_pg2", DIV_P1_PG, 0x862, 0x863, 0, 0, 0, 0, 0),
	D_GATE(CLK_P1_PG3, "clk_p1_pg3", DIV_P1_PG, 0x864, 0x865, 0, 0, 0, 0, 0),
	D_GATE(CLK_P1_PG4, "clk_p1_pg4", DIV_P1_PG, 0x866, 0x867, 0, 0, 0, 0, 0),
	D_GATE(CLK_P4_PG3, "clk_p4_pg3", DIV_P4_PG, 0x824, 0x825, 0, 0, 0, 0, 0),
	D_GATE(CLK_P4_PG4, "clk_p4_pg4", DIV_P4_PG, 0x826, 0x827, 0, 0, 0, 0, 0),
	D_GATE(CLK_P6_PG1, "clk_p6_pg1", DIV_P6_PG, 0x8a0, 0x8a1, 0x8a2, 0, 0xb60, 0, 0),
	D_GATE(CLK_P6_PG2, "clk_p6_pg2", DIV_P6_PG, 0x8a3, 0x8a4, 0x8a5, 0, 0xb61, 0, 0),
	D_GATE(CLK_P6_PG3, "clk_p6_pg3", DIV_P6_PG, 0x8a6, 0x8a7, 0x8a8, 0, 0xb62, 0, 0),
	D_GATE(CLK_P6_PG4, "clk_p6_pg4", DIV_P6_PG, 0x8a9, 0x8aa, 0x8ab, 0, 0xb63, 0, 0),
	D_MODULE(CLK_PCI_USB, "clk_pci_usb", CLKOUT_D40, 0xe6, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_QSPI0, "clk_qspi0", DIV_QSPI0, 0x2a4, 0x2a5, 0, 0, 0, 0, 0),
	D_GATE(CLK_QSPI1, "clk_qspi1", DIV_QSPI1, 0x484, 0x485, 0, 0, 0, 0, 0),
	D_GATE(CLK_RGMII_REF, "clk_rgmii_ref", CLKOUT_D8, 0x340, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_RMII_REF, "clk_rmii_ref", CLKOUT_D20, 0x341, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_SDIO0, "clk_sdio0", DIV_SDIO0, 0x64, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_SDIO1, "clk_sdio1", DIV_SDIO1, 0x644, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_SERCOS100, "clk_sercos100", CLKOUT_D10, 0x425, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_SLCD, "clk_slcd", DIV_P1_PG, 0x860, 0x861, 0, 0, 0, 0, 0),
	D_GATE(CLK_SPI0, "clk_spi0", DIV_P3_PG, 0x7e0, 0x7e1, 0, 0, 0, 0, 0),
	D_GATE(CLK_SPI1, "clk_spi1", DIV_P3_PG, 0x7e2, 0x7e3, 0, 0, 0, 0, 0),
	D_GATE(CLK_SPI2, "clk_spi2", DIV_P3_PG, 0x7e4, 0x7e5, 0, 0, 0, 0, 0),
	D_GATE(CLK_SPI3, "clk_spi3", DIV_P3_PG, 0x7e6, 0x7e7, 0, 0, 0, 0, 0),
	D_GATE(CLK_SPI4, "clk_spi4", DIV_P4_PG, 0x820, 0x821, 0, 0, 0, 0, 0),
	D_GATE(CLK_SPI5, "clk_spi5", DIV_P4_PG, 0x822, 0x823, 0, 0, 0, 0, 0),
	D_GATE(CLK_SWITCH, "clk_switch", DIV_SWITCH, 0x982, 0x983, 0, 0, 0, 0, 0),
	D_DIV(DIV_MOTOR, "div_motor", CLKOUT_D5, 84, 2, 8),
	D_MODULE(HCLK_ECAT125, "hclk_ecat125", CLKOUT_D8, 0x400, 0x401, 0, 0x402, 0, 0x440, 0x441),
	D_MODULE(HCLK_PINCONFIG, "hclk_pinconfig", CLKOUT_D40, 0x740, 0x741, 0x742, 0, 0xae0, 0, 0),
	D_MODULE(HCLK_SERCOS, "hclk_sercos", CLKOUT_D10, 0x420, 0x422, 0, 0x421, 0, 0x460, 0x461),
	D_MODULE(HCLK_SGPIO2, "hclk_sgpio2", DIV_P5_PG, 0x8c3, 0x8c4, 0x8c5, 0, 0xb41, 0, 0),
	D_MODULE(HCLK_SGPIO3, "hclk_sgpio3", DIV_P5_PG, 0x8c6, 0x8c7, 0x8c8, 0, 0xb42, 0, 0),
	D_MODULE(HCLK_SGPIO4, "hclk_sgpio4", DIV_P5_PG, 0x8c9, 0x8ca, 0x8cb, 0, 0xb43, 0, 0),
	D_MODULE(HCLK_TIMER0, "hclk_timer0", CLKOUT_D40, 0x743, 0x744, 0x745, 0, 0xae1, 0, 0),
	D_MODULE(HCLK_TIMER1, "hclk_timer1", CLKOUT_D40, 0x746, 0x747, 0x748, 0, 0xae2, 0, 0),
	D_MODULE(HCLK_USBF, "hclk_usbf", CLKOUT_D8, 0xe3, 0, 0, 0xe4, 0, 0x102, 0x103),
	D_MODULE(HCLK_USBH, "hclk_usbh", CLKOUT_D8, 0xe0, 0xe1, 0, 0xe2, 0, 0x100, 0x101),
	D_MODULE(HCLK_USBPM, "hclk_usbpm", CLKOUT_D8, 0xe5, 0, 0, 0, 0, 0, 0),
	D_GATE(CLK_48_PG_F, "clk_48_pg_f", CLK_48, 0x78c, 0x78d, 0, 0x78e, 0, 0xb04, 0xb05),
	D_GATE(CLK_48_PG4, "clk_48_pg4", CLK_48, 0x789, 0x78a, 0x78b, 0, 0xb03, 0, 0),
	D_FFC(CLK_DDRPHY_PLLCLK_D4, "clk_ddrphy_pllclk_d4", CLK_DDRPHY_PLLCLK, 4),
	D_FFC(CLK_ECAT100_D4, "clk_ecat100_d4", CLK_ECAT100, 4),
	D_FFC(CLK_HSR100_D2, "clk_hsr100_d2", CLK_HSR100, 2),
	D_FFC(CLK_REF_SYNC_D4, "clk_ref_sync_d4", CLK_REF_SYNC, 4),
	D_FFC(CLK_REF_SYNC_D8, "clk_ref_sync_d8", CLK_REF_SYNC, 8),
	D_FFC(CLK_SERCOS100_D2, "clk_sercos100_d2", CLK_SERCOS100, 2),
	D_DIV(DIV_CA7, "div_ca7", CLK_REF_SYNC, 57, 1, 4, 1, 2, 4),
	D_MODULE(HCLK_CAN0, "hclk_can0", CLK_48, 0x783, 0x784, 0x785, 0, 0xb01, 0, 0),
	D_MODULE(HCLK_CAN1, "hclk_can1", CLK_48, 0x786, 0x787, 0x788, 0, 0xb02, 0, 0),
	D_MODULE(HCLK_DELTASIGMA, "hclk_deltasigma", DIV_MOTOR, 0x1ef, 0x1f0, 0x1f1, 0, 0, 0, 0),
	D_MODULE(HCLK_PWMPTO, "hclk_pwmpto", DIV_MOTOR, 0x1ec, 0x1ed, 0x1ee, 0, 0, 0, 0),
	D_MODULE(HCLK_RSV, "hclk_rsv", CLK_48, 0x780, 0x781, 0x782, 0, 0xb00, 0, 0),
	D_MODULE(HCLK_SGPIO0, "hclk_sgpio0", DIV_MOTOR, 0x1e0, 0x1e1, 0x1e2, 0, 0, 0, 0),
	D_MODULE(HCLK_SGPIO1, "hclk_sgpio1", DIV_MOTOR, 0x1e3, 0x1e4, 0x1e5, 0, 0, 0, 0),
	D_DIV(RTOS_MDC, "rtos_mdc", CLK_REF_SYNC, 100, 80, 640, 80, 160, 320, 640),
	D_GATE(CLK_CM3, "clk_cm3", CLK_REF_SYNC_D4, 0xba0, 0xba1, 0, 0xba2, 0, 0xbc0, 0xbc1),
	D_GATE(CLK_DDRC, "clk_ddrc", CLK_DDRPHY_PLLCLK_D4, 0x323, 0x324, 0, 0, 0, 0, 0),
	D_GATE(CLK_ECAT25, "clk_ecat25", CLK_ECAT100_D4, 0x403, 0x404, 0, 0, 0, 0, 0),
	D_GATE(CLK_HSR50, "clk_hsr50", CLK_HSR100_D2, 0x484, 0x485, 0, 0, 0, 0, 0),
	D_GATE(CLK_HW_RTOS, "clk_hw_rtos", CLK_REF_SYNC_D4, 0xc60, 0xc61, 0, 0, 0, 0, 0),
	D_GATE(CLK_SERCOS50, "clk_sercos50", CLK_SERCOS100_D2, 0x424, 0x423, 0, 0, 0, 0, 0),
	D_MODULE(HCLK_ADC, "hclk_adc", CLK_REF_SYNC_D8, 0x1af, 0x1b0, 0x1b1, 0, 0, 0, 0),
	D_MODULE(HCLK_CM3, "hclk_cm3", CLK_REF_SYNC_D4, 0xc20, 0xc21, 0xc22, 0, 0, 0, 0),
	D_MODULE(HCLK_CRYPTO_EIP150, "hclk_crypto_eip150", CLK_REF_SYNC_D4, 0x123, 0x124, 0x125, 0, 0x142, 0, 0),
	D_MODULE(HCLK_CRYPTO_EIP93, "hclk_crypto_eip93", CLK_REF_SYNC_D4, 0x120, 0x121, 0, 0x122, 0, 0x140, 0x141),
	D_MODULE(HCLK_DDRC, "hclk_ddrc", CLK_REF_SYNC_D4, 0x320, 0x322, 0, 0x321, 0, 0x3a0, 0x3a1),
	D_MODULE(HCLK_DMA0, "hclk_dma0", CLK_REF_SYNC_D4, 0x260, 0x261, 0x262, 0x263, 0x2c0, 0x2c1, 0x2c2),
	D_MODULE(HCLK_DMA1, "hclk_dma1", CLK_REF_SYNC_D4, 0x264, 0x265, 0x266, 0x267, 0x2c3, 0x2c4, 0x2c5),
	D_MODULE(HCLK_GMAC0, "hclk_gmac0", CLK_REF_SYNC_D4, 0x360, 0x361, 0x362, 0x363, 0x3c0, 0x3c1, 0x3c2),
	D_MODULE(HCLK_GMAC1, "hclk_gmac1", CLK_REF_SYNC_D4, 0x380, 0x381, 0x382, 0x383, 0x3e0, 0x3e1, 0x3e2),
	D_MODULE(HCLK_GPIO0, "hclk_gpio0", CLK_REF_SYNC_D4, 0x212, 0x213, 0x214, 0, 0, 0, 0),
	D_MODULE(HCLK_GPIO1, "hclk_gpio1", CLK_REF_SYNC_D4, 0x215, 0x216, 0x217, 0, 0, 0, 0),
	D_MODULE(HCLK_GPIO2, "hclk_gpio2", CLK_REF_SYNC_D4, 0x229, 0x22a, 0x22b, 0, 0, 0, 0),
	D_MODULE(HCLK_HSR, "hclk_hsr", CLK_HSR100_D2, 0x480, 0x482, 0, 0x481, 0, 0x4c0, 0x4c1),
	D_MODULE(HCLK_I2C0, "hclk_i2c0", CLK_REF_SYNC_D8, 0x1a9, 0x1aa, 0x1ab, 0, 0, 0, 0),
	D_MODULE(HCLK_I2C1, "hclk_i2c1", CLK_REF_SYNC_D8, 0x1ac, 0x1ad, 0x1ae, 0, 0, 0, 0),
	D_MODULE(HCLK_LCD, "hclk_lcd", CLK_REF_SYNC_D4, 0x7a0, 0x7a1, 0x7a2, 0, 0xb20, 0, 0),
	D_MODULE(HCLK_MSEBI_M, "hclk_msebi_m", CLK_REF_SYNC_D4, 0x164, 0x165, 0x166, 0, 0x183, 0, 0),
	D_MODULE(HCLK_MSEBI_S, "hclk_msebi_s", CLK_REF_SYNC_D4, 0x160, 0x161, 0x162, 0x163, 0x180, 0x181, 0x182),
	D_MODULE(HCLK_न_अंकD, "hclk_nand", CLK_REF_SYNC_D4, 0x280, 0x281, 0x282, 0x283, 0x2e0, 0x2e1, 0x2e2),
	D_MODULE(HCLK_PG_I, "hclk_pg_i", CLK_REF_SYNC_D4, 0x7ac, 0x7ad, 0, 0x7ae, 0, 0xb24, 0xb25),
	D_MODULE(HCLK_PG19, "hclk_pg19", CLK_REF_SYNC_D4, 0x22c, 0x22d, 0x22e, 0, 0, 0, 0),
	D_MODULE(HCLK_PG20, "hclk_pg20", CLK_REF_SYNC_D4, 0x22f, 0x230, 0x231, 0, 0, 0, 0),
	D_MODULE(HCLK_PG3, "hclk_pg3", CLK_REF_SYNC_D4, 0x7a6, 0x7a7, 0x7a8, 0, 0xb22, 0, 0),
	D_MODULE(HCLK_PG4, "hclk_pg4", CLK_REF_SYNC_D4, 0x7a9, 0x7aa, 0x7ab, 0, 0xb23, 0, 0),
	D_MODULE(HCLK_QSPI0, "hclk_qspi0", CLK_REF_SYNC_D4, 0x2a0, 0x2a1, 0x2a2, 0x2a3, 0x300, 0x301, 0x302),
	D_MODULE(HCLK_QSPI1, "hclk_qspi1", CLK_REF_SYNC_D4, 0x480, 0x481, 0x482, 0x483, 0x4c0, 0x4c1, 0x4c2),
	D_MODULE(HCLK_ROM, "hclk_rom", CLK_REF_SYNC_D4, 0xaa0, 0xaa1, 0xaa2, 0, 0xb80, 0, 0),
	D_MODULE(HCLK_RTC, "hclk_rtc", CLK_REF_SYNC_D8, 0xa00, 0, 0, 0, 0, 0, 0),
	D_MODULE(HCLK_SDIO0, "hclk_sdio0", CLK_REF_SYNC_D4, 0x60, 0x61, 0x62, 0x63, 0x80, 0x81, 0x82),
	D_MODULE(HCLK_SDIO1, "hclk_sdio1", CLK_REF_SYNC_D4, 0x640, 0x641, 0x642, 0x643, 0x660, 0x661, 0x662),
	D_MODULE(HCLK_SEMAP, "hclk_semap", CLK_REF_SYNC_D4, 0x7a3, 0x7a4, 0x7a5, 0, 0xb21, 0, 0),
	D_MODULE(HCLK_SPI0, "hclk_spi0", CLK_REF_SYNC_D4, 0x200, 0x201, 0x202, 0, 0, 0, 0),
	D_MODULE(HCLK_SPI1, "hclk_spi1", CLK_REF_SYNC_D4, 0x203, 0x204, 0x205, 0, 0, 0, 0),
	D_MODULE(HCLK_SPI2, "hclk_spi2", CLK_REF_SYNC_D4, 0x206, 0x207, 0x208, 0, 0, 0, 0),
	D_MODULE(HCLK_SPI3, "hclk_spi3", CLK_REF_SYNC_D4, 0x209, 0x20a, 0x20b, 0, 0, 0, 0),
	D_MODULE(HCLK_SPI4, "hclk_spi4", CLK_REF_SYNC_D4, 0x20c, 0x20d, 0x20e, 0, 0, 0, 0),
	D_MODULE(HCLK_SPI5, "hclk_spi5", CLK_REF_SYNC_D4, 0x20f, 0x210, 0x211, 0, 0, 0, 0),
	D_MODULE(HCLK_SWITCH, "hclk_switch", CLK_REF_SYNC_D4, 0x980, 0, 0x981, 0, 0, 0, 0),
	D_MODULE(HCLK_SWITCH_RG, "hclk_switch_rg", CLK_REF_SYNC_D4, 0xc40, 0xc41, 0xc42, 0, 0, 0, 0),
	D_MODULE(HCLK_UART0, "hclk_uart0", CLK_REF_SYNC_D8, 0x1a0, 0x1a1, 0x1a2, 0, 0, 0, 0),
	D_MODULE(HCLK_UART1, "hclk_uart1", CLK_REF_SYNC_D8, 0x1a3, 0x1a4, 0x1a5, 0, 0, 0, 0),
	D_MODULE(HCLK_UART2, "hclk_uart2", CLK_REF_SYNC_D8, 0x1a6, 0x1a7, 0x1a8, 0, 0, 0, 0),
	D_MODULE(HCLK_UART3, "hclk_uart3", CLK_REF_SYNC_D4, 0x218, 0x219, 0x21a, 0, 0, 0, 0),
	D_MODULE(HCLK_UART4, "hclk_uart4", CLK_REF_SYNC_D4, 0x21b, 0x21c, 0x21d, 0, 0, 0, 0),
	D_MODULE(HCLK_UART5, "hclk_uart5", CLK_REF_SYNC_D4, 0x220, 0x221, 0x222, 0, 0, 0, 0),
	D_MODULE(HCLK_UART6, "hclk_uart6", CLK_REF_SYNC_D4, 0x223, 0x224, 0x225, 0, 0, 0, 0),
	D_MODULE(HCLK_UART7, "hclk_uart7", CLK_REF_SYNC_D4, 0x226, 0x227, 0x228, 0, 0, 0, 0),
	/*
	 * These are not hardware घड़ीs, but are needed to handle the special
	 * हाल where we have a 'selector bit' that doesn't just change the
	 * parent क्रम a घड़ी, but also the gate it's supposed to use.
	 */
	अणु
		.index = R9A06G032_UART_GROUP_012,
		.name = "uart_group_012",
		.type = K_BITSEL,
		.source = 1 + R9A06G032_DIV_UART,
		/* R9A06G032_SYSCTRL_REG_PWRCTRL_PG1_PR2 */
		.dual.sel = ((0xec / 4) << 5) | 24,
		.dual.group = 0,
	पूर्ण,
	अणु
		.index = R9A06G032_UART_GROUP_34567,
		.name = "uart_group_34567",
		.type = K_BITSEL,
		.source = 1 + R9A06G032_DIV_P2_PG,
		/* R9A06G032_SYSCTRL_REG_PWRCTRL_PG0_0 */
		.dual.sel = ((0x34 / 4) << 5) | 30,
		.dual.group = 1,
	पूर्ण,
	D_UGATE(CLK_UART0, "clk_uart0", UART_GROUP_012, 0, 0, 0x1b2, 0x1b3, 0x1b4, 0x1b5),
	D_UGATE(CLK_UART1, "clk_uart1", UART_GROUP_012, 0, 1, 0x1b6, 0x1b7, 0x1b8, 0x1b9),
	D_UGATE(CLK_UART2, "clk_uart2", UART_GROUP_012, 0, 2, 0x1ba, 0x1bb, 0x1bc, 0x1bd),
	D_UGATE(CLK_UART3, "clk_uart3", UART_GROUP_34567, 1, 0, 0x760, 0x761, 0x762, 0x763),
	D_UGATE(CLK_UART4, "clk_uart4", UART_GROUP_34567, 1, 1, 0x764, 0x765, 0x766, 0x767),
	D_UGATE(CLK_UART5, "clk_uart5", UART_GROUP_34567, 1, 2, 0x768, 0x769, 0x76a, 0x76b),
	D_UGATE(CLK_UART6, "clk_uart6", UART_GROUP_34567, 1, 3, 0x76c, 0x76d, 0x76e, 0x76f),
	D_UGATE(CLK_UART7, "clk_uart7", UART_GROUP_34567, 1, 4, 0x770, 0x771, 0x772, 0x773),
पूर्ण;

काष्ठा r9a06g032_priv अणु
	काष्ठा clk_onecell_data data;
	spinlock_t lock; /* protects concurrent access to gates */
	व्योम __iomem *reg;
पूर्ण;

/* रेजिस्टर/bit pairs are encoded as an uपूर्णांक16_t */
अटल व्योम
clk_rdesc_set(काष्ठा r9a06g032_priv *घड़ीs,
	      u16 one, अचिन्हित पूर्णांक on)
अणु
	u32 __iomem *reg = घड़ीs->reg + (4 * (one >> 5));
	u32 val = पढ़ोl(reg);

	val = (val & ~(1U << (one & 0x1f))) | ((!!on) << (one & 0x1f));
	ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक
clk_rdesc_get(काष्ठा r9a06g032_priv *घड़ीs,
	      uपूर्णांक16_t one)
अणु
	u32 __iomem *reg = घड़ीs->reg + (4 * (one >> 5));
	u32 val = पढ़ोl(reg);

	वापस !!(val & (1U << (one & 0x1f)));
पूर्ण

/*
 * This implements the R9A06G032 घड़ी gate 'driver'. We cannot use the system's
 * घड़ी gate framework as the gates on the R9A06G032 have a special enabling
 * sequence, thereक्रमe we use this little proxy.
 */
काष्ठा r9a06g032_clk_gate अणु
	काष्ठा clk_hw hw;
	काष्ठा r9a06g032_priv *घड़ीs;
	u16 index;

	काष्ठा r9a06g032_gate gate;
पूर्ण;

#घोषणा to_r9a06g032_gate(_hw) container_of(_hw, काष्ठा r9a06g032_clk_gate, hw)

अटल पूर्णांक create_add_module_घड़ी(काष्ठा of_phandle_args *clkspec,
				   काष्ठा device *dev)
अणु
	काष्ठा clk *clk;
	पूर्णांक error;

	clk = of_clk_get_from_provider(clkspec);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	error = pm_clk_create(dev);
	अगर (error) अणु
		clk_put(clk);
		वापस error;
	पूर्ण

	error = pm_clk_add_clk(dev, clk);
	अगर (error) अणु
		pm_clk_destroy(dev);
		clk_put(clk);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक r9a06g032_attach_dev(काष्ठा generic_pm_करोमुख्य *pd,
				काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args clkspec;
	पूर्णांक i = 0;
	पूर्णांक error;
	पूर्णांक index;

	जबतक (!of_parse_phandle_with_args(np, "clocks", "#clock-cells", i,
					   &clkspec)) अणु
		अगर (clkspec.np != pd->dev.of_node)
			जारी;

		index = clkspec.args[0];
		अगर (index < R9A06G032_CLOCK_COUNT &&
		    r9a06g032_घड़ीs[index].managed) अणु
			error = create_add_module_घड़ी(&clkspec, dev);
			of_node_put(clkspec.np);
			अगर (error)
				वापस error;
		पूर्ण
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम r9a06g032_detach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev)
अणु
	अगर (!pm_clk_no_घड़ीs(dev))
		pm_clk_destroy(dev);
पूर्ण

अटल पूर्णांक r9a06g032_add_clk_करोमुख्य(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा generic_pm_करोमुख्य *pd;

	pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pd->name = np->name;
	pd->flags = GENPD_FLAG_PM_CLK | GENPD_FLAG_ALWAYS_ON |
		    GENPD_FLAG_ACTIVE_WAKEUP;
	pd->attach_dev = r9a06g032_attach_dev;
	pd->detach_dev = r9a06g032_detach_dev;
	pm_genpd_init(pd, &pm_करोमुख्य_always_on_gov, false);

	of_genpd_add_provider_simple(np, pd);
	वापस 0;
पूर्ण

अटल व्योम
r9a06g032_clk_gate_set(काष्ठा r9a06g032_priv *घड़ीs,
		       काष्ठा r9a06g032_gate *g, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;

	WARN_ON(!g->gate);

	spin_lock_irqsave(&घड़ीs->lock, flags);
	clk_rdesc_set(घड़ीs, g->gate, on);
	/* De-निश्चित reset */
	अगर (g->reset)
		clk_rdesc_set(घड़ीs, g->reset, 1);
	spin_unlock_irqrestore(&घड़ीs->lock, flags);

	/* Hardware manual recommends 5us delay after enabling घड़ी & reset */
	udelay(5);

	/* If the peripheral is memory mapped (i.e. an AXI slave), there is an
	 * associated SLVRDY bit in the System Controller that needs to be set
	 * so that the FlexWAY bus fabric passes on the पढ़ो/ग_लिखो requests.
	 */
	अगर (g->पढ़ोy || g->midle) अणु
		spin_lock_irqsave(&घड़ीs->lock, flags);
		अगर (g->पढ़ोy)
			clk_rdesc_set(घड़ीs, g->पढ़ोy, on);
		/* Clear 'Master Idle Request' bit */
		अगर (g->midle)
			clk_rdesc_set(घड़ीs, g->midle, !on);
		spin_unlock_irqrestore(&घड़ीs->lock, flags);
	पूर्ण
	/* Note: We करोn't रुको क्रम FlexWAY Socket Connection संकेत */
पूर्ण

अटल पूर्णांक r9a06g032_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_gate *g = to_r9a06g032_gate(hw);

	r9a06g032_clk_gate_set(g->घड़ीs, &g->gate, 1);
	वापस 0;
पूर्ण

अटल व्योम r9a06g032_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_gate *g = to_r9a06g032_gate(hw);

	r9a06g032_clk_gate_set(g->घड़ीs, &g->gate, 0);
पूर्ण

अटल पूर्णांक r9a06g032_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_gate *g = to_r9a06g032_gate(hw);

	/* अगर घड़ी is in reset, the gate might be on, and still not 'be' on */
	अगर (g->gate.reset && !clk_rdesc_get(g->घड़ीs, g->gate.reset))
		वापस 0;

	वापस clk_rdesc_get(g->घड़ीs, g->gate.gate);
पूर्ण

अटल स्थिर काष्ठा clk_ops r9a06g032_clk_gate_ops = अणु
	.enable = r9a06g032_clk_gate_enable,
	.disable = r9a06g032_clk_gate_disable,
	.is_enabled = r9a06g032_clk_gate_is_enabled,
पूर्ण;

अटल काष्ठा clk *
r9a06g032_रेजिस्टर_gate(काष्ठा r9a06g032_priv *घड़ीs,
			स्थिर अक्षर *parent_name,
			स्थिर काष्ठा r9a06g032_clkdesc *desc)
अणु
	काष्ठा clk *clk;
	काष्ठा r9a06g032_clk_gate *g;
	काष्ठा clk_init_data init = अणुपूर्ण;

	g = kzalloc(माप(*g), GFP_KERNEL);
	अगर (!g)
		वापस शून्य;

	init.name = desc->name;
	init.ops = &r9a06g032_clk_gate_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	g->घड़ीs = घड़ीs;
	g->index = desc->index;
	g->gate = desc->gate;
	g->hw.init = &init;

	/*
	 * important here, some घड़ीs are alपढ़ोy in use by the CM3, we
	 * have to assume they are not Linux's to play with and try to disable
	 * at the end of the boot!
	 */
	अगर (r9a06g032_clk_gate_is_enabled(&g->hw)) अणु
		init.flags |= CLK_IS_CRITICAL;
		pr_debug("%s was enabled, making read-only\n", desc->name);
	पूर्ण

	clk = clk_रेजिस्टर(शून्य, &g->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(g);
		वापस शून्य;
	पूर्ण
	वापस clk;
पूर्ण

काष्ठा r9a06g032_clk_भाग अणु
	काष्ठा clk_hw hw;
	काष्ठा r9a06g032_priv *घड़ीs;
	u16 index;
	u16 reg;
	u16 min, max;
	u8 table_size;
	u16 table[8];	/* we know there are no more than 8 */
पूर्ण;

#घोषणा to_r9a06g032_भाग(_hw) \
		container_of(_hw, काष्ठा r9a06g032_clk_भाग, hw)

अटल अचिन्हित दीर्घ
r9a06g032_भाग_recalc_rate(काष्ठा clk_hw *hw,
			  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा r9a06g032_clk_भाग *clk = to_r9a06g032_भाग(hw);
	u32 __iomem *reg = clk->घड़ीs->reg + (4 * clk->reg);
	u32 भाग = पढ़ोl(reg);

	अगर (भाग < clk->min)
		भाग = clk->min;
	अन्यथा अगर (भाग > clk->max)
		भाग = clk->max;
	वापस DIV_ROUND_UP(parent_rate, भाग);
पूर्ण

/*
 * Attempts to find a value that is in range of min,max,
 * and अगर a table of set भागiders was specअगरied क्रम this
 * रेजिस्टर, try to find the fixed भागider that is the बंदst
 * to the target frequency
 */
अटल दीर्घ
r9a06g032_भाग_clamp_भाग(काष्ठा r9a06g032_clk_भाग *clk,
			अचिन्हित दीर्घ rate, अचिन्हित दीर्घ prate)
अणु
	/* + 1 to cope with rates that have the reमुख्यder dropped */
	u32 भाग = DIV_ROUND_UP(prate, rate + 1);
	पूर्णांक i;

	अगर (भाग <= clk->min)
		वापस clk->min;
	अगर (भाग >= clk->max)
		वापस clk->max;

	क्रम (i = 0; clk->table_size && i < clk->table_size - 1; i++) अणु
		अगर (भाग >= clk->table[i] && भाग <= clk->table[i + 1]) अणु
			अचिन्हित दीर्घ m = rate -
				DIV_ROUND_UP(prate, clk->table[i]);
			अचिन्हित दीर्घ p =
				DIV_ROUND_UP(prate, clk->table[i + 1]) -
				rate;
			/*
			 * select the भागider that generates
			 * the value बंदst to the ideal frequency
			 */
			भाग = p >= m ? clk->table[i] : clk->table[i + 1];
			वापस भाग;
		पूर्ण
	पूर्ण
	वापस भाग;
पूर्ण

अटल दीर्घ
r9a06g032_भाग_round_rate(काष्ठा clk_hw *hw,
			 अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *prate)
अणु
	काष्ठा r9a06g032_clk_भाग *clk = to_r9a06g032_भाग(hw);
	u32 भाग = DIV_ROUND_UP(*prate, rate);

	pr_devel("%s %pC %ld (prate %ld) (wanted div %u)\n", __func__,
		 hw->clk, rate, *prate, भाग);
	pr_devel("   min %d (%ld) max %d (%ld)\n",
		 clk->min, DIV_ROUND_UP(*prate, clk->min),
		clk->max, DIV_ROUND_UP(*prate, clk->max));

	भाग = r9a06g032_भाग_clamp_भाग(clk, rate, *prate);
	/*
	 * this is a hack. Currently the serial driver asks क्रम a घड़ी rate
	 * that is 16 बार the baud rate -- and that is wildly outside the
	 * range of the UART भागider, somehow there is no provision क्रम that
	 * हाल of 'let the divider as is if outside range'.
	 * The serial driver *shouldn't* play with these clocks anyway, there's
	 * several uarts attached to this भागider, and changing this impacts
	 * everyone.
	 */
	अगर (clk->index == R9A06G032_DIV_UART ||
	    clk->index == R9A06G032_DIV_P2_PG) अणु
		pr_devel("%s div uart hack!\n", __func__);
		वापस clk_get_rate(hw->clk);
	पूर्ण
	pr_devel("%s %pC %ld / %u = %ld\n", __func__, hw->clk,
		 *prate, भाग, DIV_ROUND_UP(*prate, भाग));
	वापस DIV_ROUND_UP(*prate, भाग);
पूर्ण

अटल पूर्णांक
r9a06g032_भाग_set_rate(काष्ठा clk_hw *hw,
		       अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा r9a06g032_clk_भाग *clk = to_r9a06g032_भाग(hw);
	/* + 1 to cope with rates that have the reमुख्यder dropped */
	u32 भाग = DIV_ROUND_UP(parent_rate, rate + 1);
	u32 __iomem *reg = clk->घड़ीs->reg + (4 * clk->reg);

	pr_devel("%s %pC rate %ld parent %ld div %d\n", __func__, hw->clk,
		 rate, parent_rate, भाग);

	/*
	 * Need to ग_लिखो the bit 31 with the भागider value to
	 * latch it. Technically we should रुको until it has been
	 * cleared too.
	 * TODO: Find whether this callback is sleepable, in हाल
	 * the hardware /करोes/ require some sort of spinloop here.
	 */
	ग_लिखोl(भाग | BIT(31), reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops r9a06g032_clk_भाग_ops = अणु
	.recalc_rate = r9a06g032_भाग_recalc_rate,
	.round_rate = r9a06g032_भाग_round_rate,
	.set_rate = r9a06g032_भाग_set_rate,
पूर्ण;

अटल काष्ठा clk *
r9a06g032_रेजिस्टर_भाग(काष्ठा r9a06g032_priv *घड़ीs,
		       स्थिर अक्षर *parent_name,
		       स्थिर काष्ठा r9a06g032_clkdesc *desc)
अणु
	काष्ठा r9a06g032_clk_भाग *भाग;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init = अणुपूर्ण;
	अचिन्हित पूर्णांक i;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस शून्य;

	init.name = desc->name;
	init.ops = &r9a06g032_clk_भाग_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	भाग->घड़ीs = घड़ीs;
	भाग->index = desc->index;
	भाग->reg = desc->reg;
	भाग->hw.init = &init;
	भाग->min = desc->भाग_min;
	भाग->max = desc->भाग_max;
	/* populate (optional) भागider table fixed values */
	क्रम (i = 0; i < ARRAY_SIZE(भाग->table) &&
	     i < ARRAY_SIZE(desc->भाग_प्रकारable) && desc->भाग_प्रकारable[i]; i++) अणु
		भाग->table[भाग->table_size++] = desc->भाग_प्रकारable[i];
	पूर्ण

	clk = clk_रेजिस्टर(शून्य, &भाग->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(भाग);
		वापस शून्य;
	पूर्ण
	वापस clk;
पूर्ण

/*
 * This घड़ी provider handles the हाल of the R9A06G032 where you have
 * peripherals that have two potential घड़ी source and two gates, one क्रम
 * each of the घड़ी source - the used घड़ी source (क्रम all sub घड़ीs)
 * is selected by a single bit.
 * That single bit affects all sub-घड़ीs, and thereक्रमe needs to change the
 * active gate (and turn the others off) and क्रमce a recalculation of the rates.
 *
 * This implements two घड़ी providers, one 'bitselect' that
 * handles the चयन between both parents, and another 'dualgate'
 * that knows which gate to poke at, depending on the parent's bit position.
 */
काष्ठा r9a06g032_clk_bitsel अणु
	काष्ठा clk_hw	hw;
	काष्ठा r9a06g032_priv *घड़ीs;
	u16 index;
	u16 selector;		/* selector रेजिस्टर + bit */
पूर्ण;

#घोषणा to_clk_bitselect(_hw) \
		container_of(_hw, काष्ठा r9a06g032_clk_bitsel, hw)

अटल u8 r9a06g032_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_bitsel *set = to_clk_bitselect(hw);

	वापस clk_rdesc_get(set->घड़ीs, set->selector);
पूर्ण

अटल पूर्णांक r9a06g032_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा r9a06g032_clk_bitsel *set = to_clk_bitselect(hw);

	/* a single bit in the रेजिस्टर selects one of two parent घड़ीs */
	clk_rdesc_set(set->घड़ीs, set->selector, !!index);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_bitselect_ops = अणु
	.get_parent = r9a06g032_clk_mux_get_parent,
	.set_parent = r9a06g032_clk_mux_set_parent,
पूर्ण;

अटल काष्ठा clk *
r9a06g032_रेजिस्टर_bitsel(काष्ठा r9a06g032_priv *घड़ीs,
			  स्थिर अक्षर *parent_name,
			  स्थिर काष्ठा r9a06g032_clkdesc *desc)
अणु
	काष्ठा clk *clk;
	काष्ठा r9a06g032_clk_bitsel *g;
	काष्ठा clk_init_data init = अणुपूर्ण;
	स्थिर अक्षर *names[2];

	/* allocate the gate */
	g = kzalloc(माप(*g), GFP_KERNEL);
	अगर (!g)
		वापस शून्य;

	names[0] = parent_name;
	names[1] = "clk_pll_usb";

	init.name = desc->name;
	init.ops = &clk_bitselect_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = names;
	init.num_parents = 2;

	g->घड़ीs = घड़ीs;
	g->index = desc->index;
	g->selector = desc->dual.sel;
	g->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &g->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(g);
		वापस शून्य;
	पूर्ण
	वापस clk;
पूर्ण

काष्ठा r9a06g032_clk_dualgate अणु
	काष्ठा clk_hw	hw;
	काष्ठा r9a06g032_priv *घड़ीs;
	u16 index;
	u16 selector;		/* selector रेजिस्टर + bit */
	काष्ठा r9a06g032_gate gate[2];
पूर्ण;

#घोषणा to_clk_dualgate(_hw) \
		container_of(_hw, काष्ठा r9a06g032_clk_dualgate, hw)

अटल पूर्णांक
r9a06g032_clk_dualgate_setenable(काष्ठा r9a06g032_clk_dualgate *g, पूर्णांक enable)
अणु
	u8 sel_bit = clk_rdesc_get(g->घड़ीs, g->selector);

	/* we always turn off the 'other' gate, regardless */
	r9a06g032_clk_gate_set(g->घड़ीs, &g->gate[!sel_bit], 0);
	r9a06g032_clk_gate_set(g->घड़ीs, &g->gate[sel_bit], enable);

	वापस 0;
पूर्ण

अटल पूर्णांक r9a06g032_clk_dualgate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_dualgate *gate = to_clk_dualgate(hw);

	r9a06g032_clk_dualgate_setenable(gate, 1);

	वापस 0;
पूर्ण

अटल व्योम r9a06g032_clk_dualgate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_dualgate *gate = to_clk_dualgate(hw);

	r9a06g032_clk_dualgate_setenable(gate, 0);
पूर्ण

अटल पूर्णांक r9a06g032_clk_dualgate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा r9a06g032_clk_dualgate *g = to_clk_dualgate(hw);
	u8 sel_bit = clk_rdesc_get(g->घड़ीs, g->selector);

	वापस clk_rdesc_get(g->घड़ीs, g->gate[sel_bit].gate);
पूर्ण

अटल स्थिर काष्ठा clk_ops r9a06g032_clk_dualgate_ops = अणु
	.enable = r9a06g032_clk_dualgate_enable,
	.disable = r9a06g032_clk_dualgate_disable,
	.is_enabled = r9a06g032_clk_dualgate_is_enabled,
पूर्ण;

अटल काष्ठा clk *
r9a06g032_रेजिस्टर_dualgate(काष्ठा r9a06g032_priv *घड़ीs,
			    स्थिर अक्षर *parent_name,
			    स्थिर काष्ठा r9a06g032_clkdesc *desc,
			    uपूर्णांक16_t sel)
अणु
	काष्ठा r9a06g032_clk_dualgate *g;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init = अणुपूर्ण;

	/* allocate the gate */
	g = kzalloc(माप(*g), GFP_KERNEL);
	अगर (!g)
		वापस शून्य;
	g->घड़ीs = घड़ीs;
	g->index = desc->index;
	g->selector = sel;
	g->gate[0].gate = desc->dual.g1;
	g->gate[0].reset = desc->dual.r1;
	g->gate[1].gate = desc->dual.g2;
	g->gate[1].reset = desc->dual.r2;

	init.name = desc->name;
	init.ops = &r9a06g032_clk_dualgate_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	g->hw.init = &init;
	/*
	 * important here, some घड़ीs are alपढ़ोy in use by the CM3, we
	 * have to assume they are not Linux's to play with and try to disable
	 * at the end of the boot!
	 */
	अगर (r9a06g032_clk_dualgate_is_enabled(&g->hw)) अणु
		init.flags |= CLK_IS_CRITICAL;
		pr_debug("%s was enabled, making read-only\n", desc->name);
	पूर्ण

	clk = clk_रेजिस्टर(शून्य, &g->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(g);
		वापस शून्य;
	पूर्ण
	वापस clk;
पूर्ण

अटल व्योम r9a06g032_घड़ीs_del_clk_provider(व्योम *data)
अणु
	of_clk_del_provider(data);
पूर्ण

अटल पूर्णांक __init r9a06g032_घड़ीs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा r9a06g032_priv *घड़ीs;
	काष्ठा clk **clks;
	काष्ठा clk *mclk;
	अचिन्हित पूर्णांक i;
	u16 uart_group_sel[2];
	पूर्णांक error;

	घड़ीs = devm_kzalloc(dev, माप(*घड़ीs), GFP_KERNEL);
	clks = devm_kसुस्मृति(dev, R9A06G032_CLOCK_COUNT, माप(काष्ठा clk *),
			    GFP_KERNEL);
	अगर (!घड़ीs || !clks)
		वापस -ENOMEM;

	spin_lock_init(&घड़ीs->lock);

	घड़ीs->data.clks = clks;
	घड़ीs->data.clk_num = R9A06G032_CLOCK_COUNT;

	mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(mclk))
		वापस PTR_ERR(mclk);

	घड़ीs->reg = of_iomap(np, 0);
	अगर (WARN_ON(!घड़ीs->reg))
		वापस -ENOMEM;
	क्रम (i = 0; i < ARRAY_SIZE(r9a06g032_घड़ीs); ++i) अणु
		स्थिर काष्ठा r9a06g032_clkdesc *d = &r9a06g032_घड़ीs[i];
		स्थिर अक्षर *parent_name = d->source ?
			__clk_get_name(घड़ीs->data.clks[d->source - 1]) :
			__clk_get_name(mclk);
		काष्ठा clk *clk = शून्य;

		चयन (d->type) अणु
		हाल K_FFC:
			clk = clk_रेजिस्टर_fixed_factor(शून्य, d->name,
							parent_name, 0,
							d->mul, d->भाग);
			अवरोध;
		हाल K_GATE:
			clk = r9a06g032_रेजिस्टर_gate(घड़ीs, parent_name, d);
			अवरोध;
		हाल K_DIV:
			clk = r9a06g032_रेजिस्टर_भाग(घड़ीs, parent_name, d);
			अवरोध;
		हाल K_BITSEL:
			/* keep that selector रेजिस्टर around */
			uart_group_sel[d->dual.group] = d->dual.sel;
			clk = r9a06g032_रेजिस्टर_bitsel(घड़ीs, parent_name, d);
			अवरोध;
		हाल K_DUALGATE:
			clk = r9a06g032_रेजिस्टर_dualgate(घड़ीs, parent_name,
							  d,
							  uart_group_sel[d->dual.group]);
			अवरोध;
		पूर्ण
		घड़ीs->data.clks[d->index] = clk;
	पूर्ण
	error = of_clk_add_provider(np, of_clk_src_onecell_get, &घड़ीs->data);
	अगर (error)
		वापस error;

	error = devm_add_action_or_reset(dev,
					r9a06g032_घड़ीs_del_clk_provider, np);
	अगर (error)
		वापस error;

	वापस r9a06g032_add_clk_करोमुख्य(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id r9a06g032_match[] = अणु
	अणु .compatible = "renesas,r9a06g032-sysctrl" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver r9a06g032_घड़ी_driver = अणु
	.driver		= अणु
		.name	= "renesas,r9a06g032-sysctrl",
		.of_match_table = r9a06g032_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init r9a06g032_घड़ीs_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&r9a06g032_घड़ी_driver,
			r9a06g032_घड़ीs_probe);
पूर्ण

subsys_initcall(r9a06g032_घड़ीs_init);
