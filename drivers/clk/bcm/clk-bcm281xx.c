<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 * Copyright 2013 Linaro Limited
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश "clk-kona.h"
#समावेश "dt-bindings/clock/bcm281xx.h"

#घोषणा BCM281XX_CCU_COMMON(_name, _uहाल_name) \
	KONA_CCU_COMMON(BCM281XX, _name, _uहाल_name)

/* Root CCU */

अटल काष्ठा peri_clk_data frac_1m_data = अणु
	.gate		= HW_SW_GATE(0x214, 16, 0, 1),
	.trig		= TRIGGER(0x0e04, 0),
	.भाग		= FRAC_DIVIDER(0x0e00, 0, 22, 16),
	.घड़ीs		= CLOCKS("ref_crystal"),
पूर्ण;

अटल काष्ठा ccu_data root_ccu_data = अणु
	BCM281XX_CCU_COMMON(root, ROOT),
	.kona_clks	= अणु
		[BCM281XX_ROOT_CCU_FRAC_1M] =
			KONA_CLK(root, frac_1m, peri),
		[BCM281XX_ROOT_CCU_CLOCK_COUNT] = LAST_KONA_CLK,
	पूर्ण,
पूर्ण;

/* AON CCU */

अटल काष्ठा peri_clk_data hub_समयr_data = अणु
	.gate		= HW_SW_GATE(0x0414, 16, 0, 1),
	.घड़ीs		= CLOCKS("bbl_32k",
				 "frac_1m",
				 "dft_19_5m"),
	.sel		= SELECTOR(0x0a10, 0, 2),
	.trig		= TRIGGER(0x0a40, 4),
पूर्ण;

अटल काष्ठा peri_clk_data pmu_bsc_data = अणु
	.gate		= HW_SW_GATE(0x0418, 16, 0, 1),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "pmu_bsc_var",
				 "bbl_32k"),
	.sel		= SELECTOR(0x0a04, 0, 2),
	.भाग		= DIVIDER(0x0a04, 3, 4),
	.trig		= TRIGGER(0x0a40, 0),
पूर्ण;

अटल काष्ठा peri_clk_data pmu_bsc_var_data = अणु
	.घड़ीs		= CLOCKS("var_312m",
				 "ref_312m"),
	.sel		= SELECTOR(0x0a00, 0, 2),
	.भाग		= DIVIDER(0x0a00, 4, 5),
	.trig		= TRIGGER(0x0a40, 2),
पूर्ण;

अटल काष्ठा ccu_data aon_ccu_data = अणु
	BCM281XX_CCU_COMMON(aon, AON),
	.kona_clks	= अणु
		[BCM281XX_AON_CCU_HUB_TIMER] =
			KONA_CLK(aon, hub_समयr, peri),
		[BCM281XX_AON_CCU_PMU_BSC] =
			KONA_CLK(aon, pmu_bsc, peri),
		[BCM281XX_AON_CCU_PMU_BSC_VAR] =
			KONA_CLK(aon, pmu_bsc_var, peri),
		[BCM281XX_AON_CCU_CLOCK_COUNT] = LAST_KONA_CLK,
	पूर्ण,
पूर्ण;

/* Hub CCU */

अटल काष्ठा peri_clk_data पंचांगon_1m_data = अणु
	.gate		= HW_SW_GATE(0x04a4, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "frac_1m"),
	.sel		= SELECTOR(0x0e74, 0, 2),
	.trig		= TRIGGER(0x0e84, 1),
पूर्ण;

अटल काष्ठा ccu_data hub_ccu_data = अणु
	BCM281XX_CCU_COMMON(hub, HUB),
	.kona_clks	= अणु
		[BCM281XX_HUB_CCU_TMON_1M] =
			KONA_CLK(hub, पंचांगon_1m, peri),
		[BCM281XX_HUB_CCU_CLOCK_COUNT] = LAST_KONA_CLK,
	पूर्ण,
पूर्ण;

/* Master CCU */

अटल काष्ठा peri_clk_data sdio1_data = अणु
	.gate		= HW_SW_GATE(0x0358, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_52m",
				 "ref_52m",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a28, 0, 3),
	.भाग		= DIVIDER(0x0a28, 4, 14),
	.trig		= TRIGGER(0x0afc, 9),
पूर्ण;

अटल काष्ठा peri_clk_data sdio2_data = अणु
	.gate		= HW_SW_GATE(0x035c, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_52m",
				 "ref_52m",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a2c, 0, 3),
	.भाग		= DIVIDER(0x0a2c, 4, 14),
	.trig		= TRIGGER(0x0afc, 10),
पूर्ण;

अटल काष्ठा peri_clk_data sdio3_data = अणु
	.gate		= HW_SW_GATE(0x0364, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_52m",
				 "ref_52m",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a34, 0, 3),
	.भाग		= DIVIDER(0x0a34, 4, 14),
	.trig		= TRIGGER(0x0afc, 12),
पूर्ण;

अटल काष्ठा peri_clk_data sdio4_data = अणु
	.gate		= HW_SW_GATE(0x0360, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_52m",
				 "ref_52m",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a30, 0, 3),
	.भाग		= DIVIDER(0x0a30, 4, 14),
	.trig		= TRIGGER(0x0afc, 11),
पूर्ण;

अटल काष्ठा peri_clk_data usb_ic_data = अणु
	.gate		= HW_SW_GATE(0x0354, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_96m",
				 "ref_96m"),
	.भाग		= FIXED_DIVIDER(2),
	.sel		= SELECTOR(0x0a24, 0, 2),
	.trig		= TRIGGER(0x0afc, 7),
पूर्ण;

/* also called usbh_48m */
अटल काष्ठा peri_clk_data hsic2_48m_data = अणु
	.gate		= HW_SW_GATE(0x0370, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a38, 0, 2),
	.भाग		= FIXED_DIVIDER(2),
	.trig		= TRIGGER(0x0afc, 5),
पूर्ण;

/* also called usbh_12m */
अटल काष्ठा peri_clk_data hsic2_12m_data = अणु
	.gate		= HW_SW_GATE(0x0370, 20, 4, 5),
	.भाग		= DIVIDER(0x0a38, 12, 2),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_96m",
				 "ref_96m"),
	.pre_भाग	= FIXED_DIVIDER(2),
	.sel		= SELECTOR(0x0a38, 0, 2),
	.trig		= TRIGGER(0x0afc, 5),
पूर्ण;

अटल काष्ठा ccu_data master_ccu_data = अणु
	BCM281XX_CCU_COMMON(master, MASTER),
	.kona_clks	= अणु
		[BCM281XX_MASTER_CCU_SDIO1] =
			KONA_CLK(master, sdio1, peri),
		[BCM281XX_MASTER_CCU_SDIO2] =
			KONA_CLK(master, sdio2, peri),
		[BCM281XX_MASTER_CCU_SDIO3] =
			KONA_CLK(master, sdio3, peri),
		[BCM281XX_MASTER_CCU_SDIO4] =
			KONA_CLK(master, sdio4, peri),
		[BCM281XX_MASTER_CCU_USB_IC] =
			KONA_CLK(master, usb_ic, peri),
		[BCM281XX_MASTER_CCU_HSIC2_48M] =
			KONA_CLK(master, hsic2_48m, peri),
		[BCM281XX_MASTER_CCU_HSIC2_12M] =
			KONA_CLK(master, hsic2_12m, peri),
		[BCM281XX_MASTER_CCU_CLOCK_COUNT] = LAST_KONA_CLK,
	पूर्ण,
पूर्ण;

/* Slave CCU */

अटल काष्ठा peri_clk_data uartb_data = अणु
	.gate		= HW_SW_GATE(0x0400, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_156m",
				 "ref_156m"),
	.sel		= SELECTOR(0x0a10, 0, 2),
	.भाग		= FRAC_DIVIDER(0x0a10, 4, 12, 8),
	.trig		= TRIGGER(0x0afc, 2),
पूर्ण;

अटल काष्ठा peri_clk_data uartb2_data = अणु
	.gate		= HW_SW_GATE(0x0404, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_156m",
				 "ref_156m"),
	.sel		= SELECTOR(0x0a14, 0, 2),
	.भाग		= FRAC_DIVIDER(0x0a14, 4, 12, 8),
	.trig		= TRIGGER(0x0afc, 3),
पूर्ण;

अटल काष्ठा peri_clk_data uartb3_data = अणु
	.gate		= HW_SW_GATE(0x0408, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_156m",
				 "ref_156m"),
	.sel		= SELECTOR(0x0a18, 0, 2),
	.भाग		= FRAC_DIVIDER(0x0a18, 4, 12, 8),
	.trig		= TRIGGER(0x0afc, 4),
पूर्ण;

अटल काष्ठा peri_clk_data uartb4_data = अणु
	.gate		= HW_SW_GATE(0x0408, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_156m",
				 "ref_156m"),
	.sel		= SELECTOR(0x0a1c, 0, 2),
	.भाग		= FRAC_DIVIDER(0x0a1c, 4, 12, 8),
	.trig		= TRIGGER(0x0afc, 5),
पूर्ण;

अटल काष्ठा peri_clk_data ssp0_data = अणु
	.gate		= HW_SW_GATE(0x0410, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_104m",
				 "ref_104m",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a20, 0, 3),
	.भाग		= DIVIDER(0x0a20, 4, 14),
	.trig		= TRIGGER(0x0afc, 6),
पूर्ण;

अटल काष्ठा peri_clk_data ssp2_data = अणु
	.gate		= HW_SW_GATE(0x0418, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_104m",
				 "ref_104m",
				 "var_96m",
				 "ref_96m"),
	.sel		= SELECTOR(0x0a28, 0, 3),
	.भाग		= DIVIDER(0x0a28, 4, 14),
	.trig		= TRIGGER(0x0afc, 8),
पूर्ण;

अटल काष्ठा peri_clk_data bsc1_data = अणु
	.gate		= HW_SW_GATE(0x0458, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_104m",
				 "ref_104m",
				 "var_13m",
				 "ref_13m"),
	.sel		= SELECTOR(0x0a64, 0, 3),
	.trig		= TRIGGER(0x0afc, 23),
पूर्ण;

अटल काष्ठा peri_clk_data bsc2_data = अणु
	.gate		= HW_SW_GATE(0x045c, 18, 2, 3),
	.घड़ीs	= CLOCKS("ref_crystal",
				 "var_104m",
				 "ref_104m",
				 "var_13m",
				 "ref_13m"),
	.sel		= SELECTOR(0x0a68, 0, 3),
	.trig		= TRIGGER(0x0afc, 24),
पूर्ण;

अटल काष्ठा peri_clk_data bsc3_data = अणु
	.gate		= HW_SW_GATE(0x0484, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_104m",
				 "ref_104m",
				 "var_13m",
				 "ref_13m"),
	.sel		= SELECTOR(0x0a84, 0, 3),
	.trig		= TRIGGER(0x0b00, 2),
पूर्ण;

अटल काष्ठा peri_clk_data pwm_data = अणु
	.gate		= HW_SW_GATE(0x0468, 18, 2, 3),
	.घड़ीs		= CLOCKS("ref_crystal",
				 "var_104m"),
	.sel		= SELECTOR(0x0a70, 0, 2),
	.भाग		= DIVIDER(0x0a70, 4, 3),
	.trig		= TRIGGER(0x0afc, 15),
पूर्ण;

अटल काष्ठा ccu_data slave_ccu_data = अणु
	BCM281XX_CCU_COMMON(slave, SLAVE),
	.kona_clks	= अणु
		[BCM281XX_SLAVE_CCU_UARTB] =
			KONA_CLK(slave, uartb, peri),
		[BCM281XX_SLAVE_CCU_UARTB2] =
			KONA_CLK(slave, uartb2, peri),
		[BCM281XX_SLAVE_CCU_UARTB3] =
			KONA_CLK(slave, uartb3, peri),
		[BCM281XX_SLAVE_CCU_UARTB4] =
			KONA_CLK(slave, uartb4, peri),
		[BCM281XX_SLAVE_CCU_SSP0] =
			KONA_CLK(slave, ssp0, peri),
		[BCM281XX_SLAVE_CCU_SSP2] =
			KONA_CLK(slave, ssp2, peri),
		[BCM281XX_SLAVE_CCU_BSC1] =
			KONA_CLK(slave, bsc1, peri),
		[BCM281XX_SLAVE_CCU_BSC2] =
			KONA_CLK(slave, bsc2, peri),
		[BCM281XX_SLAVE_CCU_BSC3] =
			KONA_CLK(slave, bsc3, peri),
		[BCM281XX_SLAVE_CCU_PWM] =
			KONA_CLK(slave, pwm, peri),
		[BCM281XX_SLAVE_CCU_CLOCK_COUNT] = LAST_KONA_CLK,
	पूर्ण,
पूर्ण;

/* Device tree match table callback functions */

अटल व्योम __init kona_dt_root_ccu_setup(काष्ठा device_node *node)
अणु
	kona_dt_ccu_setup(&root_ccu_data, node);
पूर्ण

अटल व्योम __init kona_dt_aon_ccu_setup(काष्ठा device_node *node)
अणु
	kona_dt_ccu_setup(&aon_ccu_data, node);
पूर्ण

अटल व्योम __init kona_dt_hub_ccu_setup(काष्ठा device_node *node)
अणु
	kona_dt_ccu_setup(&hub_ccu_data, node);
पूर्ण

अटल व्योम __init kona_dt_master_ccu_setup(काष्ठा device_node *node)
अणु
	kona_dt_ccu_setup(&master_ccu_data, node);
पूर्ण

अटल व्योम __init kona_dt_slave_ccu_setup(काष्ठा device_node *node)
अणु
	kona_dt_ccu_setup(&slave_ccu_data, node);
पूर्ण

CLK_OF_DECLARE(bcm281xx_root_ccu, BCM281XX_DT_ROOT_CCU_COMPAT,
			kona_dt_root_ccu_setup);
CLK_OF_DECLARE(bcm281xx_aon_ccu, BCM281XX_DT_AON_CCU_COMPAT,
			kona_dt_aon_ccu_setup);
CLK_OF_DECLARE(bcm281xx_hub_ccu, BCM281XX_DT_HUB_CCU_COMPAT,
			kona_dt_hub_ccu_setup);
CLK_OF_DECLARE(bcm281xx_master_ccu, BCM281XX_DT_MASTER_CCU_COMPAT,
			kona_dt_master_ccu_setup);
CLK_OF_DECLARE(bcm281xx_slave_ccu, BCM281XX_DT_SLAVE_CCU_COMPAT,
			kona_dt_slave_ccu_setup);
