<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/delay.h>
#समावेश <dt-bindings/घड़ी/tegra20-car.h>

#समावेश "clk.h"
#समावेश "clk-id.h"

#घोषणा MISC_CLK_ENB 0x48

#घोषणा OSC_CTRL 0x50
#घोषणा OSC_CTRL_OSC_FREQ_MASK (3<<30)
#घोषणा OSC_CTRL_OSC_FREQ_13MHZ (0<<30)
#घोषणा OSC_CTRL_OSC_FREQ_19_2MHZ (1<<30)
#घोषणा OSC_CTRL_OSC_FREQ_12MHZ (2<<30)
#घोषणा OSC_CTRL_OSC_FREQ_26MHZ (3<<30)
#घोषणा OSC_CTRL_MASK (0x3f2 | OSC_CTRL_OSC_FREQ_MASK)

#घोषणा OSC_CTRL_PLL_REF_DIV_MASK (3<<28)
#घोषणा OSC_CTRL_PLL_REF_DIV_1		(0<<28)
#घोषणा OSC_CTRL_PLL_REF_DIV_2		(1<<28)
#घोषणा OSC_CTRL_PLL_REF_DIV_4		(2<<28)

#घोषणा OSC_FREQ_DET 0x58
#घोषणा OSC_FREQ_DET_TRIG (1<<31)

#घोषणा OSC_FREQ_DET_STATUS 0x5c
#घोषणा OSC_FREQ_DET_BUSY (1<<31)
#घोषणा OSC_FREQ_DET_CNT_MASK 0xFFFF

#घोषणा TEGRA20_CLK_PERIPH_BANKS	3

#घोषणा PLLS_BASE 0xf0
#घोषणा PLLS_MISC 0xf4
#घोषणा PLLC_BASE 0x80
#घोषणा PLLC_MISC 0x8c
#घोषणा PLLM_BASE 0x90
#घोषणा PLLM_MISC 0x9c
#घोषणा PLLP_BASE 0xa0
#घोषणा PLLP_MISC 0xac
#घोषणा PLLA_BASE 0xb0
#घोषणा PLLA_MISC 0xbc
#घोषणा PLLU_BASE 0xc0
#घोषणा PLLU_MISC 0xcc
#घोषणा PLLD_BASE 0xd0
#घोषणा PLLD_MISC 0xdc
#घोषणा PLLX_BASE 0xe0
#घोषणा PLLX_MISC 0xe4
#घोषणा PLLE_BASE 0xe8
#घोषणा PLLE_MISC 0xec

#घोषणा PLL_BASE_LOCK BIT(27)
#घोषणा PLLE_MISC_LOCK BIT(11)

#घोषणा PLL_MISC_LOCK_ENABLE 18
#घोषणा PLLDU_MISC_LOCK_ENABLE 22
#घोषणा PLLE_MISC_LOCK_ENABLE 9

#घोषणा PLLC_OUT 0x84
#घोषणा PLLM_OUT 0x94
#घोषणा PLLP_OUTA 0xa4
#घोषणा PLLP_OUTB 0xa8
#घोषणा PLLA_OUT 0xb4

#घोषणा CCLK_BURST_POLICY 0x20
#घोषणा SUPER_CCLK_DIVIDER 0x24
#घोषणा SCLK_BURST_POLICY 0x28
#घोषणा SUPER_SCLK_DIVIDER 0x2c
#घोषणा CLK_SYSTEM_RATE 0x30

#घोषणा CCLK_BURST_POLICY_SHIFT	28
#घोषणा CCLK_RUN_POLICY_SHIFT	4
#घोषणा CCLK_IDLE_POLICY_SHIFT	0
#घोषणा CCLK_IDLE_POLICY	1
#घोषणा CCLK_RUN_POLICY		2
#घोषणा CCLK_BURST_POLICY_PLLX	8

#घोषणा CLK_SOURCE_I2S1 0x100
#घोषणा CLK_SOURCE_I2S2 0x104
#घोषणा CLK_SOURCE_PWM 0x110
#घोषणा CLK_SOURCE_SPI 0x114
#घोषणा CLK_SOURCE_XIO 0x120
#घोषणा CLK_SOURCE_TWC 0x12c
#घोषणा CLK_SOURCE_IDE 0x144
#घोषणा CLK_SOURCE_HDMI 0x18c
#घोषणा CLK_SOURCE_DISP1 0x138
#घोषणा CLK_SOURCE_DISP2 0x13c
#घोषणा CLK_SOURCE_CSITE 0x1d4
#घोषणा CLK_SOURCE_I2C1 0x124
#घोषणा CLK_SOURCE_I2C2 0x198
#घोषणा CLK_SOURCE_I2C3 0x1b8
#घोषणा CLK_SOURCE_DVC 0x128
#घोषणा CLK_SOURCE_UARTA 0x178
#घोषणा CLK_SOURCE_UARTB 0x17c
#घोषणा CLK_SOURCE_UARTC 0x1a0
#घोषणा CLK_SOURCE_UARTD 0x1c0
#घोषणा CLK_SOURCE_UARTE 0x1c4
#घोषणा CLK_SOURCE_EMC 0x19c

#घोषणा AUDIO_SYNC_CLK 0x38

/* Tegra CPU घड़ी and reset control regs */
#घोषणा TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX		0x4c
#घोषणा TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_SET	0x340
#घोषणा TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_CLR	0x344

#घोषणा CPU_CLOCK(cpu)	(0x1 << (8 + cpu))
#घोषणा CPU_RESET(cpu)	(0x1111ul << (cpu))

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा cpu_clk_suspend_context अणु
	u32 pllx_misc;
	u32 pllx_base;

	u32 cpu_burst;
	u32 clk_csite_src;
	u32 cclk_भागider;
पूर्ण tegra20_cpu_clk_sctx;
#पूर्ण_अगर

अटल व्योम __iomem *clk_base;
अटल व्योम __iomem *pmc_base;

#घोषणा TEGRA_INIT_DATA_MUX(_name, _parents, _offset,	\
			    _clk_num, _gate_flags, _clk_id)	\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			30, 2, 0, 0, 8, 1, TEGRA_DIVIDER_ROUND_UP,	\
			_clk_num, \
			_gate_flags, _clk_id)

#घोषणा TEGRA_INIT_DATA_DIV16(_name, _parents, _offset, \
			      _clk_num, _gate_flags, _clk_id)	\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			30, 2, 0, 0, 16, 0, TEGRA_DIVIDER_ROUND_UP, \
			_clk_num, _gate_flags,	\
			_clk_id)

#घोषणा TEGRA_INIT_DATA_NODIV(_name, _parents, _offset, \
			      _mux_shअगरt, _mux_width, _clk_num, \
			      _gate_flags, _clk_id)			\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			_mux_shअगरt, _mux_width, 0, 0, 0, 0, 0, \
			_clk_num, _gate_flags,	\
			_clk_id)

अटल काष्ठा clk **clks;

अटल काष्ठा tegra_clk_pll_freq_table pll_c_freq_table[] = अणु
	अणु 12000000, 600000000, 600, 12, 1, 8 पूर्ण,
	अणु 13000000, 600000000, 600, 13, 1, 8 पूर्ण,
	अणु 19200000, 600000000, 500, 16, 1, 6 पूर्ण,
	अणु 26000000, 600000000, 600, 26, 1, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_m_freq_table[] = अणु
	अणु 12000000, 666000000, 666, 12, 1, 8 पूर्ण,
	अणु 13000000, 666000000, 666, 13, 1, 8 पूर्ण,
	अणु 19200000, 666000000, 555, 16, 1, 8 पूर्ण,
	अणु 26000000, 666000000, 666, 26, 1, 8 पूर्ण,
	अणु 12000000, 600000000, 600, 12, 1, 8 पूर्ण,
	अणु 13000000, 600000000, 600, 13, 1, 8 पूर्ण,
	अणु 19200000, 600000000, 375, 12, 1, 6 पूर्ण,
	अणु 26000000, 600000000, 600, 26, 1, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_p_freq_table[] = अणु
	अणु 12000000, 216000000, 432, 12, 2, 8 पूर्ण,
	अणु 13000000, 216000000, 432, 13, 2, 8 पूर्ण,
	अणु 19200000, 216000000,  90,  4, 2, 1 पूर्ण,
	अणु 26000000, 216000000, 432, 26, 2, 8 पूर्ण,
	अणु 12000000, 432000000, 432, 12, 1, 8 पूर्ण,
	अणु 13000000, 432000000, 432, 13, 1, 8 पूर्ण,
	अणु 19200000, 432000000,  90,  4, 1, 1 पूर्ण,
	अणु 26000000, 432000000, 432, 26, 1, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_a_freq_table[] = अणु
	अणु 28800000, 56448000, 49, 25, 1, 1 पूर्ण,
	अणु 28800000, 73728000, 64, 25, 1, 1 पूर्ण,
	अणु 28800000, 24000000,  5,  6, 1, 1 पूर्ण,
	अणु        0,        0,  0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_d_freq_table[] = अणु
	अणु 12000000,  216000000,  216, 12, 1,  4 पूर्ण,
	अणु 13000000,  216000000,  216, 13, 1,  4 पूर्ण,
	अणु 19200000,  216000000,  135, 12, 1,  3 पूर्ण,
	अणु 26000000,  216000000,  216, 26, 1,  4 पूर्ण,
	अणु 12000000,  594000000,  594, 12, 1,  8 पूर्ण,
	अणु 13000000,  594000000,  594, 13, 1,  8 पूर्ण,
	अणु 19200000,  594000000,  495, 16, 1,  8 पूर्ण,
	अणु 26000000,  594000000,  594, 26, 1,  8 पूर्ण,
	अणु 12000000, 1000000000, 1000, 12, 1, 12 पूर्ण,
	अणु 13000000, 1000000000, 1000, 13, 1, 12 पूर्ण,
	अणु 19200000, 1000000000,  625, 12, 1,  8 पूर्ण,
	अणु 26000000, 1000000000, 1000, 26, 1, 12 पूर्ण,
	अणु        0,          0,    0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_u_freq_table[] = अणु
	अणु 12000000, 480000000, 960, 12, 1, 0 पूर्ण,
	अणु 13000000, 480000000, 960, 13, 1, 0 पूर्ण,
	अणु 19200000, 480000000, 200,  4, 1, 0 पूर्ण,
	अणु 26000000, 480000000, 960, 26, 1, 0 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_x_freq_table[] = अणु
	/* 1 GHz */
	अणु 12000000, 1000000000, 1000, 12, 1, 12 पूर्ण,
	अणु 13000000, 1000000000, 1000, 13, 1, 12 पूर्ण,
	अणु 19200000, 1000000000,  625, 12, 1,  8 पूर्ण,
	अणु 26000000, 1000000000, 1000, 26, 1, 12 पूर्ण,
	/* 912 MHz */
	अणु 12000000,  912000000,  912, 12, 1, 12 पूर्ण,
	अणु 13000000,  912000000,  912, 13, 1, 12 पूर्ण,
	अणु 19200000,  912000000,  760, 16, 1,  8 पूर्ण,
	अणु 26000000,  912000000,  912, 26, 1, 12 पूर्ण,
	/* 816 MHz */
	अणु 12000000,  816000000,  816, 12, 1, 12 पूर्ण,
	अणु 13000000,  816000000,  816, 13, 1, 12 पूर्ण,
	अणु 19200000,  816000000,  680, 16, 1,  8 पूर्ण,
	अणु 26000000,  816000000,  816, 26, 1, 12 पूर्ण,
	/* 760 MHz */
	अणु 12000000,  760000000,  760, 12, 1, 12 पूर्ण,
	अणु 13000000,  760000000,  760, 13, 1, 12 पूर्ण,
	अणु 19200000,  760000000,  950, 24, 1,  8 पूर्ण,
	अणु 26000000,  760000000,  760, 26, 1, 12 पूर्ण,
	/* 750 MHz */
	अणु 12000000,  750000000,  750, 12, 1, 12 पूर्ण,
	अणु 13000000,  750000000,  750, 13, 1, 12 पूर्ण,
	अणु 19200000,  750000000,  625, 16, 1,  8 पूर्ण,
	अणु 26000000,  750000000,  750, 26, 1, 12 पूर्ण,
	/* 608 MHz */
	अणु 12000000,  608000000,  608, 12, 1, 12 पूर्ण,
	अणु 13000000,  608000000,  608, 13, 1, 12 पूर्ण,
	अणु 19200000,  608000000,  380, 12, 1,  8 पूर्ण,
	अणु 26000000,  608000000,  608, 26, 1, 12 पूर्ण,
	/* 456 MHz */
	अणु 12000000,  456000000,  456, 12, 1, 12 पूर्ण,
	अणु 13000000,  456000000,  456, 13, 1, 12 पूर्ण,
	अणु 19200000,  456000000,  380, 16, 1,  8 पूर्ण,
	अणु 26000000,  456000000,  456, 26, 1, 12 पूर्ण,
	/* 312 MHz */
	अणु 12000000,  312000000,  312, 12, 1, 12 पूर्ण,
	अणु 13000000,  312000000,  312, 13, 1, 12 पूर्ण,
	अणु 19200000,  312000000,  260, 16, 1,  8 पूर्ण,
	अणु 26000000,  312000000,  312, 26, 1, 12 पूर्ण,
	अणु        0,          0,    0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map plle_p[] = अणु
	अणु .pभाग = 1, .hw_val = 1 पूर्ण,
	अणु .pभाग = 0, .hw_val = 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_e_freq_table[] = अणु
	अणु 12000000, 100000000, 200, 24, 1, 0 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

/* PLL parameters */
अटल काष्ठा tegra_clk_pll_params pll_c_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1400000000,
	.base_reg = PLLC_BASE,
	.misc_reg = PLLC_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.freq_table = pll_c_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_m_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1200000000,
	.base_reg = PLLM_BASE,
	.misc_reg = PLLM_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.freq_table = pll_m_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_p_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1400000000,
	.base_reg = PLLP_BASE,
	.misc_reg = PLLP_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.freq_table = pll_p_freq_table,
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_HAS_CPCON |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
	.fixed_rate =  216000000,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_a_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1400000000,
	.base_reg = PLLA_BASE,
	.misc_reg = PLLA_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.freq_table = pll_a_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_d_params = अणु
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 40000000,
	.vco_max = 1000000000,
	.base_reg = PLLD_BASE,
	.misc_reg = PLLD_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLDU_MISC_LOCK_ENABLE,
	.lock_delay = 1000,
	.freq_table = pll_d_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pllu_p[] = अणु
	अणु .pभाग = 1, .hw_val = 1 पूर्ण,
	अणु .pभाग = 2, .hw_val = 0 पूर्ण,
	अणु .pभाग = 0, .hw_val = 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_u_params = अणु
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 48000000,
	.vco_max = 960000000,
	.base_reg = PLLU_BASE,
	.misc_reg = PLLU_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLDU_MISC_LOCK_ENABLE,
	.lock_delay = 1000,
	.pभाग_प्रकारohw = pllu_p,
	.freq_table = pll_u_freq_table,
	.flags = TEGRA_PLLU | TEGRA_PLL_HAS_CPCON | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_x_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1200000000,
	.base_reg = PLLX_BASE,
	.misc_reg = PLLX_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.freq_table = pll_x_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_HAS_LOCK_ENABLE,
	.pre_rate_change = tegra_cclk_pre_pllx_rate_change,
	.post_rate_change = tegra_cclk_post_pllx_rate_change,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_e_params = अणु
	.input_min = 12000000,
	.input_max = 12000000,
	.cf_min = 0,
	.cf_max = 0,
	.vco_min = 0,
	.vco_max = 0,
	.base_reg = PLLE_BASE,
	.misc_reg = PLLE_MISC,
	.lock_mask = PLLE_MISC_LOCK,
	.lock_enable_bit_idx = PLLE_MISC_LOCK_ENABLE,
	.lock_delay = 0,
	.pभाग_प्रकारohw = plle_p,
	.freq_table = pll_e_freq_table,
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_LOCK_MISC |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
	.fixed_rate = 100000000,
पूर्ण;

अटल काष्ठा tegra_devclk devclks[] __initdata = अणु
	अणु .con_id = "pll_c", .dt_id = TEGRA20_CLK_PLL_C पूर्ण,
	अणु .con_id = "pll_c_out1", .dt_id = TEGRA20_CLK_PLL_C_OUT1 पूर्ण,
	अणु .con_id = "pll_p", .dt_id = TEGRA20_CLK_PLL_P पूर्ण,
	अणु .con_id = "pll_p_out1", .dt_id = TEGRA20_CLK_PLL_P_OUT1 पूर्ण,
	अणु .con_id = "pll_p_out2", .dt_id = TEGRA20_CLK_PLL_P_OUT2 पूर्ण,
	अणु .con_id = "pll_p_out3", .dt_id = TEGRA20_CLK_PLL_P_OUT3 पूर्ण,
	अणु .con_id = "pll_p_out4", .dt_id = TEGRA20_CLK_PLL_P_OUT4 पूर्ण,
	अणु .con_id = "pll_m", .dt_id = TEGRA20_CLK_PLL_M पूर्ण,
	अणु .con_id = "pll_m_out1", .dt_id = TEGRA20_CLK_PLL_M_OUT1 पूर्ण,
	अणु .con_id = "pll_x", .dt_id = TEGRA20_CLK_PLL_X पूर्ण,
	अणु .con_id = "pll_u", .dt_id = TEGRA20_CLK_PLL_U पूर्ण,
	अणु .con_id = "pll_d", .dt_id = TEGRA20_CLK_PLL_D पूर्ण,
	अणु .con_id = "pll_d_out0", .dt_id = TEGRA20_CLK_PLL_D_OUT0 पूर्ण,
	अणु .con_id = "pll_a", .dt_id = TEGRA20_CLK_PLL_A पूर्ण,
	अणु .con_id = "pll_a_out0", .dt_id = TEGRA20_CLK_PLL_A_OUT0 पूर्ण,
	अणु .con_id = "pll_e", .dt_id = TEGRA20_CLK_PLL_E पूर्ण,
	अणु .con_id = "cclk", .dt_id = TEGRA20_CLK_CCLK पूर्ण,
	अणु .con_id = "sclk", .dt_id = TEGRA20_CLK_SCLK पूर्ण,
	अणु .con_id = "hclk", .dt_id = TEGRA20_CLK_HCLK पूर्ण,
	अणु .con_id = "pclk", .dt_id = TEGRA20_CLK_PCLK पूर्ण,
	अणु .con_id = "fuse", .dt_id = TEGRA20_CLK_FUSE पूर्ण,
	अणु .con_id = "twd", .dt_id = TEGRA20_CLK_TWD पूर्ण,
	अणु .con_id = "audio", .dt_id = TEGRA20_CLK_AUDIO पूर्ण,
	अणु .con_id = "audio_2x", .dt_id = TEGRA20_CLK_AUDIO_2X पूर्ण,
	अणु .dev_id = "tegra20-ac97", .dt_id = TEGRA20_CLK_AC97 पूर्ण,
	अणु .dev_id = "tegra-apbdma", .dt_id = TEGRA20_CLK_APBDMA पूर्ण,
	अणु .dev_id = "rtc-tegra", .dt_id = TEGRA20_CLK_RTC पूर्ण,
	अणु .dev_id = "timer", .dt_id = TEGRA20_CLK_TIMER पूर्ण,
	अणु .dev_id = "tegra-kbc", .dt_id = TEGRA20_CLK_KBC पूर्ण,
	अणु .con_id = "csus", .dev_id =  "tegra_camera", .dt_id = TEGRA20_CLK_CSUS पूर्ण,
	अणु .con_id = "vcp", .dev_id = "tegra-avp", .dt_id = TEGRA20_CLK_VCP पूर्ण,
	अणु .con_id = "bsea", .dev_id = "tegra-avp", .dt_id = TEGRA20_CLK_BSEA पूर्ण,
	अणु .con_id = "bsev", .dev_id = "tegra-aes", .dt_id = TEGRA20_CLK_BSEV पूर्ण,
	अणु .con_id = "emc", .dt_id = TEGRA20_CLK_EMC पूर्ण,
	अणु .dev_id = "fsl-tegra-udc", .dt_id = TEGRA20_CLK_USBD पूर्ण,
	अणु .dev_id = "tegra-ehci.1", .dt_id = TEGRA20_CLK_USB2 पूर्ण,
	अणु .dev_id = "tegra-ehci.2", .dt_id = TEGRA20_CLK_USB3 पूर्ण,
	अणु .dev_id = "dsi", .dt_id = TEGRA20_CLK_DSI पूर्ण,
	अणु .con_id = "csi", .dev_id = "tegra_camera", .dt_id = TEGRA20_CLK_CSI पूर्ण,
	अणु .con_id = "isp", .dev_id = "tegra_camera", .dt_id = TEGRA20_CLK_ISP पूर्ण,
	अणु .con_id = "pex", .dt_id = TEGRA20_CLK_PEX पूर्ण,
	अणु .con_id = "afi", .dt_id = TEGRA20_CLK_AFI पूर्ण,
	अणु .con_id = "cdev1", .dt_id = TEGRA20_CLK_CDEV1 पूर्ण,
	अणु .con_id = "cdev2", .dt_id = TEGRA20_CLK_CDEV2 पूर्ण,
	अणु .con_id = "clk_32k", .dt_id = TEGRA20_CLK_CLK_32K पूर्ण,
	अणु .con_id = "clk_m", .dt_id = TEGRA20_CLK_CLK_M पूर्ण,
	अणु .con_id = "pll_ref", .dt_id = TEGRA20_CLK_PLL_REF पूर्ण,
	अणु .dev_id = "tegra20-i2s.0", .dt_id = TEGRA20_CLK_I2S1 पूर्ण,
	अणु .dev_id = "tegra20-i2s.1", .dt_id = TEGRA20_CLK_I2S2 पूर्ण,
	अणु .con_id = "spdif_out", .dev_id = "tegra20-spdif", .dt_id = TEGRA20_CLK_SPDIF_OUT पूर्ण,
	अणु .con_id = "spdif_in", .dev_id = "tegra20-spdif", .dt_id = TEGRA20_CLK_SPDIF_IN पूर्ण,
	अणु .dev_id = "spi_tegra.0", .dt_id = TEGRA20_CLK_SBC1 पूर्ण,
	अणु .dev_id = "spi_tegra.1", .dt_id = TEGRA20_CLK_SBC2 पूर्ण,
	अणु .dev_id = "spi_tegra.2", .dt_id = TEGRA20_CLK_SBC3 पूर्ण,
	अणु .dev_id = "spi_tegra.3", .dt_id = TEGRA20_CLK_SBC4 पूर्ण,
	अणु .dev_id = "spi", .dt_id = TEGRA20_CLK_SPI पूर्ण,
	अणु .dev_id = "xio", .dt_id = TEGRA20_CLK_XIO पूर्ण,
	अणु .dev_id = "twc", .dt_id = TEGRA20_CLK_TWC पूर्ण,
	अणु .dev_id = "ide", .dt_id = TEGRA20_CLK_IDE पूर्ण,
	अणु .dev_id = "tegra_nand", .dt_id = TEGRA20_CLK_NDFLASH पूर्ण,
	अणु .dev_id = "vfir", .dt_id = TEGRA20_CLK_VFIR पूर्ण,
	अणु .dev_id = "csite", .dt_id = TEGRA20_CLK_CSITE पूर्ण,
	अणु .dev_id = "la", .dt_id = TEGRA20_CLK_LA पूर्ण,
	अणु .dev_id = "tegra_w1", .dt_id = TEGRA20_CLK_OWR पूर्ण,
	अणु .dev_id = "mipi", .dt_id = TEGRA20_CLK_MIPI पूर्ण,
	अणु .dev_id = "vde", .dt_id = TEGRA20_CLK_VDE पूर्ण,
	अणु .con_id = "vi", .dev_id =  "tegra_camera", .dt_id = TEGRA20_CLK_VI पूर्ण,
	अणु .dev_id = "epp", .dt_id = TEGRA20_CLK_EPP पूर्ण,
	अणु .dev_id = "mpe", .dt_id = TEGRA20_CLK_MPE पूर्ण,
	अणु .dev_id = "host1x", .dt_id = TEGRA20_CLK_HOST1X पूर्ण,
	अणु .dev_id = "3d", .dt_id = TEGRA20_CLK_GR3D पूर्ण,
	अणु .dev_id = "2d", .dt_id = TEGRA20_CLK_GR2D पूर्ण,
	अणु .dev_id = "tegra-nor", .dt_id = TEGRA20_CLK_NOR पूर्ण,
	अणु .dev_id = "sdhci-tegra.0", .dt_id = TEGRA20_CLK_SDMMC1 पूर्ण,
	अणु .dev_id = "sdhci-tegra.1", .dt_id = TEGRA20_CLK_SDMMC2 पूर्ण,
	अणु .dev_id = "sdhci-tegra.2", .dt_id = TEGRA20_CLK_SDMMC3 पूर्ण,
	अणु .dev_id = "sdhci-tegra.3", .dt_id = TEGRA20_CLK_SDMMC4 पूर्ण,
	अणु .dev_id = "cve", .dt_id = TEGRA20_CLK_CVE पूर्ण,
	अणु .dev_id = "tvo", .dt_id = TEGRA20_CLK_TVO पूर्ण,
	अणु .dev_id = "tvdac", .dt_id = TEGRA20_CLK_TVDAC पूर्ण,
	अणु .con_id = "vi_sensor", .dev_id = "tegra_camera", .dt_id = TEGRA20_CLK_VI_SENSOR पूर्ण,
	अणु .dev_id = "hdmi", .dt_id = TEGRA20_CLK_HDMI पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.0", .dt_id = TEGRA20_CLK_I2C1 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.1", .dt_id = TEGRA20_CLK_I2C2 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.2", .dt_id = TEGRA20_CLK_I2C3 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.3", .dt_id = TEGRA20_CLK_DVC पूर्ण,
	अणु .dev_id = "tegra-pwm", .dt_id = TEGRA20_CLK_PWM पूर्ण,
	अणु .dev_id = "tegra_uart.0", .dt_id = TEGRA20_CLK_UARTA पूर्ण,
	अणु .dev_id = "tegra_uart.1", .dt_id = TEGRA20_CLK_UARTB पूर्ण,
	अणु .dev_id = "tegra_uart.2", .dt_id = TEGRA20_CLK_UARTC पूर्ण,
	अणु .dev_id = "tegra_uart.3", .dt_id = TEGRA20_CLK_UARTD पूर्ण,
	अणु .dev_id = "tegra_uart.4", .dt_id = TEGRA20_CLK_UARTE पूर्ण,
	अणु .dev_id = "tegradc.0", .dt_id = TEGRA20_CLK_DISP1 पूर्ण,
	अणु .dev_id = "tegradc.1", .dt_id = TEGRA20_CLK_DISP2 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk tegra20_clks[tegra_clk_max] __initdata = अणु
	[tegra_clk_ahbdma] = अणु .dt_id = TEGRA20_CLK_AHBDMA, .present = true पूर्ण,
	[tegra_clk_apbdma] = अणु .dt_id = TEGRA20_CLK_APBDMA, .present = true पूर्ण,
	[tegra_clk_spdअगर_out] = अणु .dt_id = TEGRA20_CLK_SPDIF_OUT, .present = true पूर्ण,
	[tegra_clk_spdअगर_in] = अणु .dt_id = TEGRA20_CLK_SPDIF_IN, .present = true पूर्ण,
	[tegra_clk_sdmmc1] = अणु .dt_id = TEGRA20_CLK_SDMMC1, .present = true पूर्ण,
	[tegra_clk_sdmmc2] = अणु .dt_id = TEGRA20_CLK_SDMMC2, .present = true पूर्ण,
	[tegra_clk_sdmmc3] = अणु .dt_id = TEGRA20_CLK_SDMMC3, .present = true पूर्ण,
	[tegra_clk_sdmmc4] = अणु .dt_id = TEGRA20_CLK_SDMMC4, .present = true पूर्ण,
	[tegra_clk_la] = अणु .dt_id = TEGRA20_CLK_LA, .present = true पूर्ण,
	[tegra_clk_csite] = अणु .dt_id = TEGRA20_CLK_CSITE, .present = true पूर्ण,
	[tegra_clk_vfir] = अणु .dt_id = TEGRA20_CLK_VFIR, .present = true पूर्ण,
	[tegra_clk_mipi] = अणु .dt_id = TEGRA20_CLK_MIPI, .present = true पूर्ण,
	[tegra_clk_nor] = अणु .dt_id = TEGRA20_CLK_NOR, .present = true पूर्ण,
	[tegra_clk_rtc] = अणु .dt_id = TEGRA20_CLK_RTC, .present = true पूर्ण,
	[tegra_clk_समयr] = अणु .dt_id = TEGRA20_CLK_TIMER, .present = true पूर्ण,
	[tegra_clk_kbc] = अणु .dt_id = TEGRA20_CLK_KBC, .present = true पूर्ण,
	[tegra_clk_csus] = अणु .dt_id = TEGRA20_CLK_CSUS, .present = true पूर्ण,
	[tegra_clk_vcp] = अणु .dt_id = TEGRA20_CLK_VCP, .present = true पूर्ण,
	[tegra_clk_bsea] = अणु .dt_id = TEGRA20_CLK_BSEA, .present = true पूर्ण,
	[tegra_clk_bsev] = अणु .dt_id = TEGRA20_CLK_BSEV, .present = true पूर्ण,
	[tegra_clk_usbd] = अणु .dt_id = TEGRA20_CLK_USBD, .present = true पूर्ण,
	[tegra_clk_usb2] = अणु .dt_id = TEGRA20_CLK_USB2, .present = true पूर्ण,
	[tegra_clk_usb3] = अणु .dt_id = TEGRA20_CLK_USB3, .present = true पूर्ण,
	[tegra_clk_csi] = अणु .dt_id = TEGRA20_CLK_CSI, .present = true पूर्ण,
	[tegra_clk_isp] = अणु .dt_id = TEGRA20_CLK_ISP, .present = true पूर्ण,
	[tegra_clk_clk_32k] = अणु .dt_id = TEGRA20_CLK_CLK_32K, .present = true पूर्ण,
	[tegra_clk_hclk] = अणु .dt_id = TEGRA20_CLK_HCLK, .present = true पूर्ण,
	[tegra_clk_pclk] = अणु .dt_id = TEGRA20_CLK_PCLK, .present = true पूर्ण,
	[tegra_clk_pll_p_out1] = अणु .dt_id = TEGRA20_CLK_PLL_P_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_p_out2] = अणु .dt_id = TEGRA20_CLK_PLL_P_OUT2, .present = true पूर्ण,
	[tegra_clk_pll_p_out3] = अणु .dt_id = TEGRA20_CLK_PLL_P_OUT3, .present = true पूर्ण,
	[tegra_clk_pll_p_out4] = अणु .dt_id = TEGRA20_CLK_PLL_P_OUT4, .present = true पूर्ण,
	[tegra_clk_pll_p] = अणु .dt_id = TEGRA20_CLK_PLL_P, .present = true पूर्ण,
	[tegra_clk_owr] = अणु .dt_id = TEGRA20_CLK_OWR, .present = true पूर्ण,
	[tegra_clk_sbc1] = अणु .dt_id = TEGRA20_CLK_SBC1, .present = true पूर्ण,
	[tegra_clk_sbc2] = अणु .dt_id = TEGRA20_CLK_SBC2, .present = true पूर्ण,
	[tegra_clk_sbc3] = अणु .dt_id = TEGRA20_CLK_SBC3, .present = true पूर्ण,
	[tegra_clk_sbc4] = अणु .dt_id = TEGRA20_CLK_SBC4, .present = true पूर्ण,
	[tegra_clk_vde] = अणु .dt_id = TEGRA20_CLK_VDE, .present = true पूर्ण,
	[tegra_clk_vi] = अणु .dt_id = TEGRA20_CLK_VI, .present = true पूर्ण,
	[tegra_clk_epp] = अणु .dt_id = TEGRA20_CLK_EPP, .present = true पूर्ण,
	[tegra_clk_mpe] = अणु .dt_id = TEGRA20_CLK_MPE, .present = true पूर्ण,
	[tegra_clk_host1x] = अणु .dt_id = TEGRA20_CLK_HOST1X, .present = true पूर्ण,
	[tegra_clk_gr2d] = अणु .dt_id = TEGRA20_CLK_GR2D, .present = true पूर्ण,
	[tegra_clk_gr3d] = अणु .dt_id = TEGRA20_CLK_GR3D, .present = true पूर्ण,
	[tegra_clk_ndflash] = अणु .dt_id = TEGRA20_CLK_NDFLASH, .present = true पूर्ण,
	[tegra_clk_cve] = अणु .dt_id = TEGRA20_CLK_CVE, .present = true पूर्ण,
	[tegra_clk_tvo] = अणु .dt_id = TEGRA20_CLK_TVO, .present = true पूर्ण,
	[tegra_clk_tvdac] = अणु .dt_id = TEGRA20_CLK_TVDAC, .present = true पूर्ण,
	[tegra_clk_vi_sensor] = अणु .dt_id = TEGRA20_CLK_VI_SENSOR, .present = true पूर्ण,
	[tegra_clk_afi] = अणु .dt_id = TEGRA20_CLK_AFI, .present = true पूर्ण,
	[tegra_clk_fuse] = अणु .dt_id = TEGRA20_CLK_FUSE, .present = true पूर्ण,
	[tegra_clk_kfuse] = अणु .dt_id = TEGRA20_CLK_KFUSE, .present = true पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ tegra20_clk_measure_input_freq(व्योम)
अणु
	u32 osc_ctrl = पढ़ोl_relaxed(clk_base + OSC_CTRL);
	u32 स्वतः_clk_control = osc_ctrl & OSC_CTRL_OSC_FREQ_MASK;
	u32 pll_ref_भाग = osc_ctrl & OSC_CTRL_PLL_REF_DIV_MASK;
	अचिन्हित दीर्घ input_freq;

	चयन (स्वतः_clk_control) अणु
	हाल OSC_CTRL_OSC_FREQ_12MHZ:
		BUG_ON(pll_ref_भाग != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 12000000;
		अवरोध;
	हाल OSC_CTRL_OSC_FREQ_13MHZ:
		BUG_ON(pll_ref_भाग != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 13000000;
		अवरोध;
	हाल OSC_CTRL_OSC_FREQ_19_2MHZ:
		BUG_ON(pll_ref_भाग != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 19200000;
		अवरोध;
	हाल OSC_CTRL_OSC_FREQ_26MHZ:
		BUG_ON(pll_ref_भाग != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 26000000;
		अवरोध;
	शेष:
		pr_err("Unexpected clock autodetect value %d",
		       स्वतः_clk_control);
		BUG();
		वापस 0;
	पूर्ण

	वापस input_freq;
पूर्ण

अटल अचिन्हित पूर्णांक tegra20_get_pll_ref_भाग(व्योम)
अणु
	u32 pll_ref_भाग = पढ़ोl_relaxed(clk_base + OSC_CTRL) &
		OSC_CTRL_PLL_REF_DIV_MASK;

	चयन (pll_ref_भाग) अणु
	हाल OSC_CTRL_PLL_REF_DIV_1:
		वापस 1;
	हाल OSC_CTRL_PLL_REF_DIV_2:
		वापस 2;
	हाल OSC_CTRL_PLL_REF_DIV_4:
		वापस 4;
	शेष:
		pr_err("Invalid pll ref divider %d\n", pll_ref_भाग);
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tegra20_pll_init(व्योम)
अणु
	काष्ठा clk *clk;

	/* PLLC */
	clk = tegra_clk_रेजिस्टर_pll("pll_c", "pll_ref", clk_base, शून्य, 0,
			    &pll_c_params, शून्य);
	clks[TEGRA20_CLK_PLL_C] = clk;

	/* PLLC_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_c_out1_div", "pll_c",
				clk_base + PLLC_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_c_out1", "pll_c_out1_div",
				clk_base + PLLC_OUT, 1, 0, CLK_SET_RATE_PARENT,
				0, शून्य);
	clks[TEGRA20_CLK_PLL_C_OUT1] = clk;

	/* PLLM */
	clk = tegra_clk_रेजिस्टर_pll("pll_m", "pll_ref", clk_base, शून्य,
			    CLK_SET_RATE_GATE, &pll_m_params, शून्य);
	clks[TEGRA20_CLK_PLL_M] = clk;

	/* PLLM_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_m_out1_div", "pll_m",
				clk_base + PLLM_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_m_out1", "pll_m_out1_div",
				clk_base + PLLM_OUT, 1, 0,
				CLK_SET_RATE_PARENT, 0, शून्य);
	clks[TEGRA20_CLK_PLL_M_OUT1] = clk;

	/* PLLX */
	clk = tegra_clk_रेजिस्टर_pll("pll_x", "pll_ref", clk_base, शून्य, 0,
			    &pll_x_params, शून्य);
	clks[TEGRA20_CLK_PLL_X] = clk;

	/* PLLU */
	clk = tegra_clk_रेजिस्टर_pll("pll_u", "pll_ref", clk_base, शून्य, 0,
			    &pll_u_params, शून्य);
	clks[TEGRA20_CLK_PLL_U] = clk;

	/* PLLD */
	clk = tegra_clk_रेजिस्टर_pll("pll_d", "pll_ref", clk_base, शून्य, 0,
			    &pll_d_params, शून्य);
	clks[TEGRA20_CLK_PLL_D] = clk;

	/* PLLD_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d_out0", "pll_d",
					CLK_SET_RATE_PARENT, 1, 2);
	clks[TEGRA20_CLK_PLL_D_OUT0] = clk;

	/* PLLA */
	clk = tegra_clk_रेजिस्टर_pll("pll_a", "pll_p_out1", clk_base, शून्य, 0,
			    &pll_a_params, शून्य);
	clks[TEGRA20_CLK_PLL_A] = clk;

	/* PLLA_OUT0 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_a_out0_div", "pll_a",
				clk_base + PLLA_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_a_out0", "pll_a_out0_div",
				clk_base + PLLA_OUT, 1, 0, CLK_IGNORE_UNUSED |
				CLK_SET_RATE_PARENT, 0, शून्य);
	clks[TEGRA20_CLK_PLL_A_OUT0] = clk;

	/* PLLE */
	clk = tegra_clk_रेजिस्टर_plle("pll_e", "pll_ref", clk_base, pmc_base,
			     0, &pll_e_params, शून्य);
	clks[TEGRA20_CLK_PLL_E] = clk;
पूर्ण

अटल स्थिर अक्षर *cclk_parents[] = अणु "clk_m", "pll_c", "clk_32k", "pll_m",
				      "pll_p", "pll_p_out4",
				      "pll_p_out3", "clk_d", "pll_x" पूर्ण;
अटल स्थिर अक्षर *sclk_parents[] = अणु "clk_m", "pll_c_out1", "pll_p_out4",
				      "pll_p_out3", "pll_p_out2", "clk_d",
				      "clk_32k", "pll_m_out1" पूर्ण;

अटल व्योम tegra20_super_clk_init(व्योम)
अणु
	काष्ठा clk *clk;

	/* CCLK */
	clk = tegra_clk_रेजिस्टर_super_cclk("cclk", cclk_parents,
			      ARRAY_SIZE(cclk_parents), CLK_SET_RATE_PARENT,
			      clk_base + CCLK_BURST_POLICY, TEGRA20_SUPER_CLK,
			      शून्य);
	clks[TEGRA20_CLK_CCLK] = clk;

	/* SCLK */
	clk = tegra_clk_रेजिस्टर_super_mux("sclk", sclk_parents,
			      ARRAY_SIZE(sclk_parents),
			      CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
			      clk_base + SCLK_BURST_POLICY, 0, 4, 0, 0, शून्य);
	clks[TEGRA20_CLK_SCLK] = clk;

	/* twd */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "twd", "cclk", 0, 1, 4);
	clks[TEGRA20_CLK_TWD] = clk;
पूर्ण

अटल स्थिर अक्षर *audio_parents[] = अणु "spdif_in", "i2s1", "i2s2", "unused",
				       "pll_a_out0", "unused", "unused",
				       "unused" पूर्ण;

अटल व्योम __init tegra20_audio_clk_init(व्योम)
अणु
	काष्ठा clk *clk;

	/* audio */
	clk = clk_रेजिस्टर_mux(शून्य, "audio_mux", audio_parents,
				ARRAY_SIZE(audio_parents),
				CLK_SET_RATE_NO_REPARENT,
				clk_base + AUDIO_SYNC_CLK, 0, 3, 0, शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "audio", "audio_mux", 0,
				clk_base + AUDIO_SYNC_CLK, 4,
				CLK_GATE_SET_TO_DISABLE, शून्य);
	clks[TEGRA20_CLK_AUDIO] = clk;

	/* audio_2x */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "audio_doubler", "audio",
					CLK_SET_RATE_PARENT, 2, 1);
	clk = tegra_clk_रेजिस्टर_periph_gate("audio_2x", "audio_doubler",
				    TEGRA_PERIPH_NO_RESET, clk_base,
				    CLK_SET_RATE_PARENT, 89,
				    periph_clk_enb_refcnt);
	clks[TEGRA20_CLK_AUDIO_2X] = clk;
पूर्ण

अटल स्थिर अक्षर *i2s1_parents[] = अणु "pll_a_out0", "audio_2x", "pll_p",
				      "clk_m" पूर्ण;
अटल स्थिर अक्षर *i2s2_parents[] = अणु "pll_a_out0", "audio_2x", "pll_p",
				      "clk_m" पूर्ण;
अटल स्थिर अक्षर *pwm_parents[] = अणु "pll_p", "pll_c", "audio", "clk_m",
				     "clk_32k" पूर्ण;
अटल स्थिर अक्षर *mux_pllpcm_clkm[] = अणु "pll_p", "pll_c", "pll_m", "clk_m" पूर्ण;
अटल स्थिर अक्षर *mux_pllpdc_clkm[] = अणु "pll_p", "pll_d_out0", "pll_c",
					 "clk_m" पूर्ण;

अटल काष्ठा tegra_periph_init_data tegra_periph_clk_list[] = अणु
	TEGRA_INIT_DATA_MUX("i2s1", i2s1_parents,     CLK_SOURCE_I2S1,   11, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_I2S1),
	TEGRA_INIT_DATA_MUX("i2s2", i2s2_parents,     CLK_SOURCE_I2S2,   18, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_I2S2),
	TEGRA_INIT_DATA_MUX("spi",   mux_pllpcm_clkm,   CLK_SOURCE_SPI,   43, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_SPI),
	TEGRA_INIT_DATA_MUX("xio",   mux_pllpcm_clkm,   CLK_SOURCE_XIO,   45, 0, TEGRA20_CLK_XIO),
	TEGRA_INIT_DATA_MUX("twc",   mux_pllpcm_clkm,   CLK_SOURCE_TWC,   16, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_TWC),
	TEGRA_INIT_DATA_MUX("ide",   mux_pllpcm_clkm,   CLK_SOURCE_XIO,   25, 0, TEGRA20_CLK_IDE),
	TEGRA_INIT_DATA_DIV16("dvc", mux_pllpcm_clkm,   CLK_SOURCE_DVC,   47, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_DVC),
	TEGRA_INIT_DATA_DIV16("i2c1", mux_pllpcm_clkm,   CLK_SOURCE_I2C1,   12, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_I2C1),
	TEGRA_INIT_DATA_DIV16("i2c2", mux_pllpcm_clkm,   CLK_SOURCE_I2C2,   54, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_I2C2),
	TEGRA_INIT_DATA_DIV16("i2c3", mux_pllpcm_clkm,   CLK_SOURCE_I2C3,   67, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_I2C3),
	TEGRA_INIT_DATA_MUX("hdmi", mux_pllpdc_clkm,   CLK_SOURCE_HDMI,   51, 0, TEGRA20_CLK_HDMI),
	TEGRA_INIT_DATA("pwm", शून्य, शून्य, pwm_parents,     CLK_SOURCE_PWM,   28, 3, 0, 0, 8, 1, 0, 17, TEGRA_PERIPH_ON_APB, TEGRA20_CLK_PWM),
पूर्ण;

अटल काष्ठा tegra_periph_init_data tegra_periph_noभाग_clk_list[] = अणु
	TEGRA_INIT_DATA_NODIV("uarta",	mux_pllpcm_clkm, CLK_SOURCE_UARTA, 30, 2, 6,   TEGRA_PERIPH_ON_APB, TEGRA20_CLK_UARTA),
	TEGRA_INIT_DATA_NODIV("uartb",	mux_pllpcm_clkm, CLK_SOURCE_UARTB, 30, 2, 7,   TEGRA_PERIPH_ON_APB, TEGRA20_CLK_UARTB),
	TEGRA_INIT_DATA_NODIV("uartc",	mux_pllpcm_clkm, CLK_SOURCE_UARTC, 30, 2, 55,  TEGRA_PERIPH_ON_APB, TEGRA20_CLK_UARTC),
	TEGRA_INIT_DATA_NODIV("uartd",	mux_pllpcm_clkm, CLK_SOURCE_UARTD, 30, 2, 65,  TEGRA_PERIPH_ON_APB, TEGRA20_CLK_UARTD),
	TEGRA_INIT_DATA_NODIV("uarte",	mux_pllpcm_clkm, CLK_SOURCE_UARTE, 30, 2, 66,  TEGRA_PERIPH_ON_APB, TEGRA20_CLK_UARTE),
	TEGRA_INIT_DATA_NODIV("disp1",	mux_pllpdc_clkm, CLK_SOURCE_DISP1, 30, 2, 27,  0, TEGRA20_CLK_DISP1),
	TEGRA_INIT_DATA_NODIV("disp2",	mux_pllpdc_clkm, CLK_SOURCE_DISP2, 30, 2, 26,  0, TEGRA20_CLK_DISP2),
पूर्ण;

अटल व्योम __init tegra20_periph_clk_init(व्योम)
अणु
	काष्ठा tegra_periph_init_data *data;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	/* ac97 */
	clk = tegra_clk_रेजिस्टर_periph_gate("ac97", "pll_a_out0",
				    TEGRA_PERIPH_ON_APB,
				    clk_base, 0, 3, periph_clk_enb_refcnt);
	clks[TEGRA20_CLK_AC97] = clk;

	/* emc */
	clk = tegra20_clk_रेजिस्टर_emc(clk_base + CLK_SOURCE_EMC, false);

	clks[TEGRA20_CLK_EMC] = clk;

	clk = tegra_clk_रेजिस्टर_mc("mc", "emc", clk_base + CLK_SOURCE_EMC,
				    शून्य);
	clks[TEGRA20_CLK_MC] = clk;

	/* dsi */
	clk = tegra_clk_रेजिस्टर_periph_gate("dsi", "pll_d", 0, clk_base, 0,
				    48, periph_clk_enb_refcnt);
	clk_रेजिस्टर_clkdev(clk, शून्य, "dsi");
	clks[TEGRA20_CLK_DSI] = clk;

	/* pex */
	clk = tegra_clk_रेजिस्टर_periph_gate("pex", "clk_m", 0, clk_base, 0, 70,
				    periph_clk_enb_refcnt);
	clks[TEGRA20_CLK_PEX] = clk;

	/* dev1 OSC भागider */
	clk_रेजिस्टर_भागider(शून्य, "dev1_osc_div", "clk_m",
			     0, clk_base + MISC_CLK_ENB, 22, 2,
			     CLK_DIVIDER_POWER_OF_TWO | CLK_DIVIDER_READ_ONLY,
			     शून्य);

	/* dev2 OSC भागider */
	clk_रेजिस्टर_भागider(शून्य, "dev2_osc_div", "clk_m",
			     0, clk_base + MISC_CLK_ENB, 20, 2,
			     CLK_DIVIDER_POWER_OF_TWO | CLK_DIVIDER_READ_ONLY,
			     शून्य);

	/* cdev1 */
	clk = tegra_clk_रेजिस्टर_periph_gate("cdev1", "cdev1_mux", 0,
				    clk_base, 0, 94, periph_clk_enb_refcnt);
	clks[TEGRA20_CLK_CDEV1] = clk;

	/* cdev2 */
	clk = tegra_clk_रेजिस्टर_periph_gate("cdev2", "cdev2_mux", 0,
				    clk_base, 0, 93, periph_clk_enb_refcnt);
	clks[TEGRA20_CLK_CDEV2] = clk;

	क्रम (i = 0; i < ARRAY_SIZE(tegra_periph_clk_list); i++) अणु
		data = &tegra_periph_clk_list[i];
		clk = tegra_clk_रेजिस्टर_periph_data(clk_base, data);
		clks[data->clk_id] = clk;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tegra_periph_noभाग_clk_list); i++) अणु
		data = &tegra_periph_noभाग_clk_list[i];
		clk = tegra_clk_रेजिस्टर_periph_noभाग(data->name,
					data->p.parent_names,
					data->num_parents, &data->periph,
					clk_base, data->offset);
		clks[data->clk_id] = clk;
	पूर्ण

	tegra_periph_clk_init(clk_base, pmc_base, tegra20_clks, &pll_p_params);
पूर्ण

अटल व्योम __init tegra20_osc_clk_init(व्योम)
अणु
	काष्ठा clk *clk;
	अचिन्हित दीर्घ input_freq;
	अचिन्हित पूर्णांक pll_ref_भाग;

	input_freq = tegra20_clk_measure_input_freq();

	/* clk_m */
	clk = clk_रेजिस्टर_fixed_rate(शून्य, "clk_m", शून्य, CLK_IGNORE_UNUSED,
				      input_freq);
	clks[TEGRA20_CLK_CLK_M] = clk;

	/* pll_ref */
	pll_ref_भाग = tegra20_get_pll_ref_भाग();
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_ref", "clk_m",
					CLK_SET_RATE_PARENT, 1, pll_ref_भाग);
	clks[TEGRA20_CLK_PLL_REF] = clk;
पूर्ण

/* Tegra20 CPU घड़ी and reset control functions */
अटल व्योम tegra20_रुको_cpu_in_reset(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	करो अणु
		reg = पढ़ोl(clk_base +
			    TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_SET);
		cpu_relax();
	पूर्ण जबतक (!(reg & (1 << cpu)));	/* check CPU been reset or not */

	वापस;
पूर्ण

अटल व्योम tegra20_put_cpu_in_reset(u32 cpu)
अणु
	ग_लिखोl(CPU_RESET(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_SET);
	dmb();
पूर्ण

अटल व्योम tegra20_cpu_out_of_reset(u32 cpu)
अणु
	ग_लिखोl(CPU_RESET(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_CLR);
	wmb();
पूर्ण

अटल व्योम tegra20_enable_cpu_घड़ी(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
	ग_लिखोl(reg & ~CPU_CLOCK(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
	barrier();
	reg = पढ़ोl(clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
पूर्ण

अटल व्योम tegra20_disable_cpu_घड़ी(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
	ग_लिखोl(reg | CPU_CLOCK(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool tegra20_cpu_rail_off_पढ़ोy(व्योम)
अणु
	अचिन्हित पूर्णांक cpu_rst_status;

	cpu_rst_status = पढ़ोl(clk_base +
			       TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_SET);

	वापस !!(cpu_rst_status & 0x2);
पूर्ण

अटल व्योम tegra20_cpu_घड़ी_suspend(व्योम)
अणु
	/* चयन coresite to clk_m, save off original source */
	tegra20_cpu_clk_sctx.clk_csite_src =
				पढ़ोl(clk_base + CLK_SOURCE_CSITE);
	ग_लिखोl(3<<30, clk_base + CLK_SOURCE_CSITE);

	tegra20_cpu_clk_sctx.cpu_burst =
				पढ़ोl(clk_base + CCLK_BURST_POLICY);
	tegra20_cpu_clk_sctx.pllx_base =
				पढ़ोl(clk_base + PLLX_BASE);
	tegra20_cpu_clk_sctx.pllx_misc =
				पढ़ोl(clk_base + PLLX_MISC);
	tegra20_cpu_clk_sctx.cclk_भागider =
				पढ़ोl(clk_base + SUPER_CCLK_DIVIDER);
पूर्ण

अटल व्योम tegra20_cpu_घड़ी_resume(व्योम)
अणु
	अचिन्हित पूर्णांक reg, policy;
	u32 misc, base;

	/* Is CPU complex alपढ़ोy running on PLLX? */
	reg = पढ़ोl(clk_base + CCLK_BURST_POLICY);
	policy = (reg >> CCLK_BURST_POLICY_SHIFT) & 0xF;

	अगर (policy == CCLK_IDLE_POLICY)
		reg = (reg >> CCLK_IDLE_POLICY_SHIFT) & 0xF;
	अन्यथा अगर (policy == CCLK_RUN_POLICY)
		reg = (reg >> CCLK_RUN_POLICY_SHIFT) & 0xF;
	अन्यथा
		BUG();

	अगर (reg != CCLK_BURST_POLICY_PLLX) अणु
		misc = पढ़ोl_relaxed(clk_base + PLLX_MISC);
		base = पढ़ोl_relaxed(clk_base + PLLX_BASE);

		अगर (misc != tegra20_cpu_clk_sctx.pllx_misc ||
		    base != tegra20_cpu_clk_sctx.pllx_base) अणु
			/* restore PLLX settings अगर CPU is on dअगरferent PLL */
			ग_लिखोl(tegra20_cpu_clk_sctx.pllx_misc,
						clk_base + PLLX_MISC);
			ग_लिखोl(tegra20_cpu_clk_sctx.pllx_base,
						clk_base + PLLX_BASE);

			/* रुको क्रम PLL stabilization अगर PLLX was enabled */
			अगर (tegra20_cpu_clk_sctx.pllx_base & (1 << 30))
				udelay(300);
		पूर्ण
	पूर्ण

	/*
	 * Restore original burst policy setting क्रम calls resulting from CPU
	 * LP2 in idle or प्रणाली suspend.
	 */
	ग_लिखोl(tegra20_cpu_clk_sctx.cclk_भागider,
					clk_base + SUPER_CCLK_DIVIDER);
	ग_लिखोl(tegra20_cpu_clk_sctx.cpu_burst,
					clk_base + CCLK_BURST_POLICY);

	ग_लिखोl(tegra20_cpu_clk_sctx.clk_csite_src,
					clk_base + CLK_SOURCE_CSITE);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा tegra_cpu_car_ops tegra20_cpu_car_ops = अणु
	.रुको_क्रम_reset	= tegra20_रुको_cpu_in_reset,
	.put_in_reset	= tegra20_put_cpu_in_reset,
	.out_of_reset	= tegra20_cpu_out_of_reset,
	.enable_घड़ी	= tegra20_enable_cpu_घड़ी,
	.disable_घड़ी	= tegra20_disable_cpu_घड़ी,
#अगर_घोषित CONFIG_PM_SLEEP
	.rail_off_पढ़ोy = tegra20_cpu_rail_off_पढ़ोy,
	.suspend	= tegra20_cpu_घड़ी_suspend,
	.resume		= tegra20_cpu_घड़ी_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा tegra_clk_init_table init_table[] __initdata = अणु
	अणु TEGRA20_CLK_PLL_P, TEGRA20_CLK_CLK_MAX, 216000000, 1 पूर्ण,
	अणु TEGRA20_CLK_PLL_P_OUT1, TEGRA20_CLK_CLK_MAX, 28800000, 1 पूर्ण,
	अणु TEGRA20_CLK_PLL_P_OUT2, TEGRA20_CLK_CLK_MAX, 48000000, 1 पूर्ण,
	अणु TEGRA20_CLK_PLL_P_OUT3, TEGRA20_CLK_CLK_MAX, 72000000, 1 पूर्ण,
	अणु TEGRA20_CLK_PLL_P_OUT4, TEGRA20_CLK_CLK_MAX, 24000000, 1 पूर्ण,
	अणु TEGRA20_CLK_PLL_C, TEGRA20_CLK_CLK_MAX, 600000000, 0 पूर्ण,
	अणु TEGRA20_CLK_PLL_C_OUT1, TEGRA20_CLK_CLK_MAX, 240000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SCLK, TEGRA20_CLK_PLL_C_OUT1, 240000000, 0 पूर्ण,
	अणु TEGRA20_CLK_HCLK, TEGRA20_CLK_CLK_MAX, 240000000, 0 पूर्ण,
	अणु TEGRA20_CLK_PCLK, TEGRA20_CLK_CLK_MAX, 60000000, 0 पूर्ण,
	अणु TEGRA20_CLK_CSITE, TEGRA20_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA20_CLK_CCLK, TEGRA20_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA20_CLK_UARTA, TEGRA20_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA20_CLK_UARTB, TEGRA20_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA20_CLK_UARTC, TEGRA20_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA20_CLK_UARTD, TEGRA20_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA20_CLK_UARTE, TEGRA20_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA20_CLK_PLL_A, TEGRA20_CLK_CLK_MAX, 56448000, 0 पूर्ण,
	अणु TEGRA20_CLK_PLL_A_OUT0, TEGRA20_CLK_CLK_MAX, 11289600, 0 पूर्ण,
	अणु TEGRA20_CLK_I2S1, TEGRA20_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA20_CLK_I2S2, TEGRA20_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA20_CLK_SDMMC1, TEGRA20_CLK_PLL_P, 48000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SDMMC3, TEGRA20_CLK_PLL_P, 48000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SDMMC4, TEGRA20_CLK_PLL_P, 48000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SPI, TEGRA20_CLK_PLL_P, 20000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SBC1, TEGRA20_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SBC2, TEGRA20_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SBC3, TEGRA20_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA20_CLK_SBC4, TEGRA20_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA20_CLK_HOST1X, TEGRA20_CLK_PLL_C, 150000000, 0 पूर्ण,
	अणु TEGRA20_CLK_GR2D, TEGRA20_CLK_PLL_C, 300000000, 0 पूर्ण,
	अणु TEGRA20_CLK_GR3D, TEGRA20_CLK_PLL_C, 300000000, 0 पूर्ण,
	अणु TEGRA20_CLK_VDE, TEGRA20_CLK_PLL_C, 300000000, 0 पूर्ण,
	/* must be the last entry */
	अणु TEGRA20_CLK_CLK_MAX, TEGRA20_CLK_CLK_MAX, 0, 0 पूर्ण,
पूर्ण;

अटल व्योम __init tegra20_घड़ी_apply_init_table(व्योम)
अणु
	tegra_init_from_table(init_table, clks, TEGRA20_CLK_CLK_MAX);
पूर्ण

/*
 * Some घड़ीs may be used by dअगरferent drivers depending on the board
 * configuration.  List those here to रेजिस्टर them twice in the घड़ी lookup
 * table under two names.
 */
अटल काष्ठा tegra_clk_duplicate tegra_clk_duplicates[] = अणु
	TEGRA_CLK_DUPLICATE(TEGRA20_CLK_USBD,    "utmip-pad",     शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA20_CLK_USBD,    "tegra-ehci.0",  शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA20_CLK_USBD,    "tegra-otg",     शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA20_CLK_CCLK,    शून्य,           "cpu"),
	/* must be the last entry */
	TEGRA_CLK_DUPLICATE(TEGRA20_CLK_CLK_MAX, शून्य,            शून्य),
पूर्ण;

अटल स्थिर काष्ठा of_device_id pmc_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra20-pmc" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा clk *tegra20_clk_src_onecell_get(काष्ठा of_phandle_args *clkspec,
					       व्योम *data)
अणु
	काष्ठा clk_hw *parent_hw;
	काष्ठा clk_hw *hw;
	काष्ठा clk *clk;

	clk = of_clk_src_onecell_get(clkspec, data);
	अगर (IS_ERR(clk))
		वापस clk;

	hw = __clk_get_hw(clk);

	/*
	 * Tegra20 CDEV1 and CDEV2 घड़ीs are a bit special हाल, their parent
	 * घड़ी is created by the pinctrl driver. It is possible क्रम clk user
	 * to request these घड़ीs beक्रमe pinctrl driver got probed and hence
	 * user will get an orphaned घड़ी. That might be undesirable because
	 * user may expect parent घड़ी to be enabled by the child.
	 */
	अगर (clkspec->args[0] == TEGRA20_CLK_CDEV1 ||
	    clkspec->args[0] == TEGRA20_CLK_CDEV2) अणु
		parent_hw = clk_hw_get_parent(hw);
		अगर (!parent_hw)
			वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	अगर (clkspec->args[0] == TEGRA20_CLK_EMC) अणु
		अगर (!tegra20_clk_emc_driver_available(hw))
			वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	वापस clk;
पूर्ण

अटल व्योम __init tegra20_घड़ी_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *node;

	clk_base = of_iomap(np, 0);
	अगर (!clk_base) अणु
		pr_err("Can't map CAR registers\n");
		BUG();
	पूर्ण

	node = of_find_matching_node(शून्य, pmc_match);
	अगर (!node) अणु
		pr_err("Failed to find pmc node\n");
		BUG();
	पूर्ण

	pmc_base = of_iomap(node, 0);
	अगर (!pmc_base) अणु
		pr_err("Can't map pmc registers\n");
		BUG();
	पूर्ण

	clks = tegra_clk_init(clk_base, TEGRA20_CLK_CLK_MAX,
				TEGRA20_CLK_PERIPH_BANKS);
	अगर (!clks)
		वापस;

	tegra20_osc_clk_init();
	tegra_fixed_clk_init(tegra20_clks);
	tegra20_pll_init();
	tegra20_super_clk_init();
	tegra_super_clk_gen4_init(clk_base, pmc_base, tegra20_clks, शून्य);
	tegra20_periph_clk_init();
	tegra20_audio_clk_init();

	tegra_init_dup_clks(tegra_clk_duplicates, clks, TEGRA20_CLK_CLK_MAX);

	tegra_add_of_provider(np, tegra20_clk_src_onecell_get);
	tegra_रेजिस्टर_devclks(devclks, ARRAY_SIZE(devclks));

	tegra_clk_apply_init_table = tegra20_घड़ी_apply_init_table;

	tegra_cpu_car_ops = &tegra20_cpu_car_ops;
पूर्ण
CLK_OF_DECLARE(tegra20, "nvidia,tegra20-car", tegra20_घड़ी_init);
