<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/clk/tegra.h>
#समावेश <dt-bindings/घड़ी/tegra124-car.h>
#समावेश <dt-bindings/reset/tegra124-car.h>

#समावेश "clk.h"
#समावेश "clk-id.h"

/*
 * TEGRA124_CAR_BANK_COUNT: the number of peripheral घड़ी रेजिस्टर
 * banks present in the Tegra124/132 CAR IP block.  The banks are
 * identअगरied by single letters, e.g.: L, H, U, V, W, X.  See
 * periph_regs[] in drivers/clk/tegra/clk.c
 */
#घोषणा TEGRA124_CAR_BANK_COUNT			6

#घोषणा CLK_SOURCE_CSITE 0x1d4
#घोषणा CLK_SOURCE_EMC 0x19c
#घोषणा CLK_SOURCE_SOR0 0x414

#घोषणा RST_DFLL_DVCO			0x2f4
#घोषणा DVFS_DFLL_RESET_SHIFT		0

#घोषणा PLLC_BASE 0x80
#घोषणा PLLC_OUT 0x84
#घोषणा PLLC_MISC2 0x88
#घोषणा PLLC_MISC 0x8c
#घोषणा PLLC2_BASE 0x4e8
#घोषणा PLLC2_MISC 0x4ec
#घोषणा PLLC3_BASE 0x4fc
#घोषणा PLLC3_MISC 0x500
#घोषणा PLLM_BASE 0x90
#घोषणा PLLM_OUT 0x94
#घोषणा PLLM_MISC 0x9c
#घोषणा PLLP_BASE 0xa0
#घोषणा PLLP_MISC 0xac
#घोषणा PLLA_BASE 0xb0
#घोषणा PLLA_MISC 0xbc
#घोषणा PLLD_BASE 0xd0
#घोषणा PLLD_MISC 0xdc
#घोषणा PLLU_BASE 0xc0
#घोषणा PLLU_MISC 0xcc
#घोषणा PLLX_BASE 0xe0
#घोषणा PLLX_MISC 0xe4
#घोषणा PLLX_MISC2 0x514
#घोषणा PLLX_MISC3 0x518
#घोषणा PLLE_BASE 0xe8
#घोषणा PLLE_MISC 0xec
#घोषणा PLLD2_BASE 0x4b8
#घोषणा PLLD2_MISC 0x4bc
#घोषणा PLLE_AUX 0x48c
#घोषणा PLLRE_BASE 0x4c4
#घोषणा PLLRE_MISC 0x4c8
#घोषणा PLLDP_BASE 0x590
#घोषणा PLLDP_MISC 0x594
#घोषणा PLLC4_BASE 0x5a4
#घोषणा PLLC4_MISC 0x5a8

#घोषणा PLLC_IDDQ_BIT 26
#घोषणा PLLRE_IDDQ_BIT 16
#घोषणा PLLSS_IDDQ_BIT 19

#घोषणा PLL_BASE_LOCK BIT(27)
#घोषणा PLLE_MISC_LOCK BIT(11)
#घोषणा PLLRE_MISC_LOCK BIT(24)

#घोषणा PLL_MISC_LOCK_ENABLE 18
#घोषणा PLLC_MISC_LOCK_ENABLE 24
#घोषणा PLLDU_MISC_LOCK_ENABLE 22
#घोषणा PLLE_MISC_LOCK_ENABLE 9
#घोषणा PLLRE_MISC_LOCK_ENABLE 30
#घोषणा PLLSS_MISC_LOCK_ENABLE 30

#घोषणा PLLXC_SW_MAX_P 6

#घोषणा PMC_PLLM_WB0_OVERRIDE 0x1dc
#घोषणा PMC_PLLM_WB0_OVERRIDE_2 0x2b0

#घोषणा CCLKG_BURST_POLICY 0x368

/* Tegra CPU घड़ी and reset control regs */
#घोषणा CLK_RST_CONTROLLER_CPU_CMPLX_STATUS	0x470

#घोषणा MASK(x) (BIT(x) - 1)

#घोषणा MUX8_NOGATE_LOCK(_name, _parents, _offset, _clk_id, _lock)	\
	TEGRA_INIT_DATA_TABLE(_name, शून्य, शून्य, _parents, _offset,	\
			      29, MASK(3), 0, 0, 8, 1, TEGRA_DIVIDER_ROUND_UP,\
			      0, TEGRA_PERIPH_NO_GATE, _clk_id,\
			      _parents##_idx, 0, _lock)

#घोषणा NODIV(_name, _parents, _offset, \
			      _mux_shअगरt, _mux_mask, _clk_num, \
			      _gate_flags, _clk_id, _lock)		\
	TEGRA_INIT_DATA_TABLE(_name, शून्य, शून्य, _parents, _offset,\
			_mux_shअगरt, _mux_mask, 0, 0, 0, 0, 0,\
			_clk_num, (_gate_flags) | TEGRA_PERIPH_NO_DIV,\
			_clk_id, _parents##_idx, 0, _lock)

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा cpu_clk_suspend_context अणु
	u32 clk_csite_src;
	u32 cclkg_burst;
	u32 cclkg_भागider;
पूर्ण tegra124_cpu_clk_sctx;
#पूर्ण_अगर

अटल व्योम __iomem *clk_base;
अटल व्योम __iomem *pmc_base;

अटल अचिन्हित दीर्घ osc_freq;
अटल अचिन्हित दीर्घ pll_ref_freq;

अटल DEFINE_SPINLOCK(pll_d_lock);
अटल DEFINE_SPINLOCK(pll_e_lock);
अटल DEFINE_SPINLOCK(pll_re_lock);
अटल DEFINE_SPINLOCK(pll_u_lock);
अटल DEFINE_SPINLOCK(emc_lock);
अटल DEFINE_SPINLOCK(sor0_lock);

/* possible OSC frequencies in Hz */
अटल अचिन्हित दीर्घ tegra124_input_freq[] = अणु
	[ 0] = 13000000,
	[ 1] = 16800000,
	[ 4] = 19200000,
	[ 5] = 38400000,
	[ 8] = 12000000,
	[ 9] = 48000000,
	[12] = 26000000,
पूर्ण;

अटल काष्ठा भाग_nmp pllxc_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 4,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pllxc_p[] = अणु
	अणु .pभाग =  1, .hw_val =  0 पूर्ण,
	अणु .pभाग =  2, .hw_val =  1 पूर्ण,
	अणु .pभाग =  3, .hw_val =  2 पूर्ण,
	अणु .pभाग =  4, .hw_val =  3 पूर्ण,
	अणु .pभाग =  5, .hw_val =  4 पूर्ण,
	अणु .pभाग =  6, .hw_val =  5 पूर्ण,
	अणु .pभाग =  8, .hw_val =  6 पूर्ण,
	अणु .pभाग = 10, .hw_val =  7 पूर्ण,
	अणु .pभाग = 12, .hw_val =  8 पूर्ण,
	अणु .pभाग = 16, .hw_val =  9 पूर्ण,
	अणु .pभाग = 12, .hw_val = 10 पूर्ण,
	अणु .pभाग = 16, .hw_val = 11 पूर्ण,
	अणु .pभाग = 20, .hw_val = 12 पूर्ण,
	अणु .pभाग = 24, .hw_val = 13 पूर्ण,
	अणु .pभाग = 32, .hw_val = 14 पूर्ण,
	अणु .pभाग =  0, .hw_val =  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_x_freq_table[] = अणु
	/* 1 GHz */
	अणु 12000000, 1000000000, 83, 1, 1, 0 पूर्ण, /* actual: 996.0 MHz */
	अणु 13000000, 1000000000, 76, 1, 1, 0 पूर्ण, /* actual: 988.0 MHz */
	अणु 16800000, 1000000000, 59, 1, 1, 0 पूर्ण, /* actual: 991.2 MHz */
	अणु 19200000, 1000000000, 52, 1, 1, 0 पूर्ण, /* actual: 998.4 MHz */
	अणु 26000000, 1000000000, 76, 2, 1, 0 पूर्ण, /* actual: 988.0 MHz */
	अणु        0,          0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_x_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 19200000,	/* s/w policy, h/w capability 50 MHz */
	.vco_min = 700000000,
	.vco_max = 3000000000UL,
	.base_reg = PLLX_BASE,
	.misc_reg = PLLX_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLX_MISC3,
	.iddq_bit_idx = 3,
	.max_p = 6,
	.dyn_ramp_reg = PLLX_MISC2,
	.stepa_shअगरt = 16,
	.stepb_shअगरt = 24,
	.pभाग_प्रकारohw = pllxc_p,
	.भाग_nmp = &pllxc_nmp,
	.freq_table = pll_x_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_c_freq_table[] = अणु
	अणु 12000000, 624000000, 104, 1, 2, 0 पूर्ण,
	अणु 12000000, 600000000, 100, 1, 2, 0 पूर्ण,
	अणु 13000000, 600000000,  92, 1, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु 16800000, 600000000,  71, 1, 2, 0 पूर्ण, /* actual: 596.4 MHz */
	अणु 19200000, 600000000,  62, 1, 2, 0 पूर्ण, /* actual: 595.2 MHz */
	अणु 26000000, 600000000,  92, 2, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु        0,         0,   0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w policy, h/w capability 50 MHz */
	.vco_min = 600000000,
	.vco_max = 1400000000,
	.base_reg = PLLC_BASE,
	.misc_reg = PLLC_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLC_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLC_MISC,
	.iddq_bit_idx = PLLC_IDDQ_BIT,
	.max_p = PLLXC_SW_MAX_P,
	.dyn_ramp_reg = PLLC_MISC2,
	.stepa_shअगरt = 17,
	.stepb_shअगरt = 9,
	.pभाग_प्रकारohw = pllxc_p,
	.भाग_nmp = &pllxc_nmp,
	.freq_table = pll_c_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा भाग_nmp pllcx_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 2,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 3,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pllc_p[] = अणु
	अणु .pभाग =  1, .hw_val = 0 पूर्ण,
	अणु .pभाग =  2, .hw_val = 1 पूर्ण,
	अणु .pभाग =  3, .hw_val = 2 पूर्ण,
	अणु .pभाग =  4, .hw_val = 3 पूर्ण,
	अणु .pभाग =  6, .hw_val = 4 पूर्ण,
	अणु .pभाग =  8, .hw_val = 5 पूर्ण,
	अणु .pभाग = 12, .hw_val = 6 पूर्ण,
	अणु .pभाग = 16, .hw_val = 7 पूर्ण,
	अणु .pभाग =  0, .hw_val = 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_cx_freq_table[] = अणु
	अणु 12000000, 600000000, 100, 1, 2, 0 पूर्ण,
	अणु 13000000, 600000000,  92, 1, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु 16800000, 600000000,  71, 1, 2, 0 पूर्ण, /* actual: 596.4 MHz */
	अणु 19200000, 600000000,  62, 1, 2, 0 पूर्ण, /* actual: 595.2 MHz */
	अणु 26000000, 600000000,  92, 2, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु        0,         0,   0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c2_params = अणु
	.input_min = 12000000,
	.input_max = 48000000,
	.cf_min = 12000000,
	.cf_max = 19200000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLC2_BASE,
	.misc_reg = PLLC2_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.pभाग_प्रकारohw = pllc_p,
	.भाग_nmp = &pllcx_nmp,
	.max_p = 7,
	.ext_misc_reg[0] = 0x4f0,
	.ext_misc_reg[1] = 0x4f4,
	.ext_misc_reg[2] = 0x4f8,
	.freq_table = pll_cx_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c3_params = अणु
	.input_min = 12000000,
	.input_max = 48000000,
	.cf_min = 12000000,
	.cf_max = 19200000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLC3_BASE,
	.misc_reg = PLLC3_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.pभाग_प्रकारohw = pllc_p,
	.भाग_nmp = &pllcx_nmp,
	.max_p = 7,
	.ext_misc_reg[0] = 0x504,
	.ext_misc_reg[1] = 0x508,
	.ext_misc_reg[2] = 0x50c,
	.freq_table = pll_cx_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
पूर्ण;

अटल काष्ठा भाग_nmp pllss_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 4,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pll12g_ssd_esd_p[] = अणु
	अणु .pभाग =  1, .hw_val =  0 पूर्ण,
	अणु .pभाग =  2, .hw_val =  1 पूर्ण,
	अणु .pभाग =  3, .hw_val =  2 पूर्ण,
	अणु .pभाग =  4, .hw_val =  3 पूर्ण,
	अणु .pभाग =  5, .hw_val =  4 पूर्ण,
	अणु .pभाग =  6, .hw_val =  5 पूर्ण,
	अणु .pभाग =  8, .hw_val =  6 पूर्ण,
	अणु .pभाग = 10, .hw_val =  7 पूर्ण,
	अणु .pभाग = 12, .hw_val =  8 पूर्ण,
	अणु .pभाग = 16, .hw_val =  9 पूर्ण,
	अणु .pभाग = 12, .hw_val = 10 पूर्ण,
	अणु .pभाग = 16, .hw_val = 11 पूर्ण,
	अणु .pभाग = 20, .hw_val = 12 पूर्ण,
	अणु .pभाग = 24, .hw_val = 13 पूर्ण,
	अणु .pभाग = 32, .hw_val = 14 पूर्ण,
	अणु .pभाग =  0, .hw_val =  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_c4_freq_table[] = अणु
	अणु 12000000, 600000000, 100, 1, 2, 0 पूर्ण,
	अणु 13000000, 600000000,  92, 1, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु 16800000, 600000000,  71, 1, 2, 0 पूर्ण, /* actual: 596.4 MHz */
	अणु 19200000, 600000000,  62, 1, 2, 0 पूर्ण, /* actual: 595.2 MHz */
	अणु 26000000, 600000000,  92, 2, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु        0,         0,   0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c4_params = अणु
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w policy, h/w capability 38 MHz */
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLC4_BASE,
	.misc_reg = PLLC4_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLSS_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLC4_BASE,
	.iddq_bit_idx = PLLSS_IDDQ_BIT,
	.pभाग_प्रकारohw = pll12g_ssd_esd_p,
	.भाग_nmp = &pllss_nmp,
	.ext_misc_reg[0] = 0x5ac,
	.ext_misc_reg[1] = 0x5b0,
	.ext_misc_reg[2] = 0x5b4,
	.freq_table = pll_c4_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pllm_p[] = अणु
	अणु .pभाग =  1, .hw_val =  0 पूर्ण,
	अणु .pभाग =  2, .hw_val =  1 पूर्ण,
	अणु .pभाग =  3, .hw_val =  2 पूर्ण,
	अणु .pभाग =  4, .hw_val =  3 पूर्ण,
	अणु .pभाग =  5, .hw_val =  4 पूर्ण,
	अणु .pभाग =  6, .hw_val =  5 पूर्ण,
	अणु .pभाग =  8, .hw_val =  6 पूर्ण,
	अणु .pभाग = 10, .hw_val =  7 पूर्ण,
	अणु .pभाग = 12, .hw_val =  8 पूर्ण,
	अणु .pभाग = 16, .hw_val =  9 पूर्ण,
	अणु .pभाग = 12, .hw_val = 10 पूर्ण,
	अणु .pभाग = 16, .hw_val = 11 पूर्ण,
	अणु .pभाग = 20, .hw_val = 12 पूर्ण,
	अणु .pभाग = 24, .hw_val = 13 पूर्ण,
	अणु .pभाग = 32, .hw_val = 14 पूर्ण,
	अणु .pभाग =  0, .hw_val =  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_m_freq_table[] = अणु
	अणु 12000000, 800000000, 66, 1, 1, 0 पूर्ण, /* actual: 792.0 MHz */
	अणु 13000000, 800000000, 61, 1, 1, 0 पूर्ण, /* actual: 793.0 MHz */
	अणु 16800000, 800000000, 47, 1, 1, 0 पूर्ण, /* actual: 789.6 MHz */
	अणु 19200000, 800000000, 41, 1, 1, 0 पूर्ण, /* actual: 787.2 MHz */
	अणु 26000000, 800000000, 61, 2, 1, 0 पूर्ण, /* actual: 793.0 MHz */
	अणु        0,         0,  0, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp pllm_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.override_भागm_shअगरt = 0,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.override_भागn_shअगरt = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 1,
	.override_भागp_shअगरt = 27,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_m_params = अणु
	.input_min = 12000000,
	.input_max = 500000000,
	.cf_min = 12000000,
	.cf_max = 19200000,	/* s/w policy, h/w capability 50 MHz */
	.vco_min = 400000000,
	.vco_max = 1066000000,
	.base_reg = PLLM_BASE,
	.misc_reg = PLLM_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.max_p = 5,
	.pभाग_प्रकारohw = pllm_p,
	.भाग_nmp = &pllm_nmp,
	.pmc_भागnm_reg = PMC_PLLM_WB0_OVERRIDE,
	.pmc_भागp_reg = PMC_PLLM_WB0_OVERRIDE_2,
	.freq_table = pll_m_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_e_freq_table[] = अणु
	/* PLLE special हाल: use cpcon field to store cml भागider value */
	अणु 336000000, 100000000, 100, 21, 16, 11 पूर्ण,
	अणु 312000000, 100000000, 200, 26, 24, 13 पूर्ण,
	अणु  13000000, 100000000, 200,  1, 26, 13 पूर्ण,
	अणु  12000000, 100000000, 200,  1, 24, 13 पूर्ण,
	अणु         0,         0,   0,  0,  0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map plle_p[] = अणु
	अणु .pभाग =  1, .hw_val =  0 पूर्ण,
	अणु .pभाग =  2, .hw_val =  1 पूर्ण,
	अणु .pभाग =  3, .hw_val =  2 पूर्ण,
	अणु .pभाग =  4, .hw_val =  3 पूर्ण,
	अणु .pभाग =  5, .hw_val =  4 पूर्ण,
	अणु .pभाग =  6, .hw_val =  5 पूर्ण,
	अणु .pभाग =  8, .hw_val =  6 पूर्ण,
	अणु .pभाग = 10, .hw_val =  7 पूर्ण,
	अणु .pभाग = 12, .hw_val =  8 पूर्ण,
	अणु .pभाग = 16, .hw_val =  9 पूर्ण,
	अणु .pभाग = 12, .hw_val = 10 पूर्ण,
	अणु .pभाग = 16, .hw_val = 11 पूर्ण,
	अणु .pभाग = 20, .hw_val = 12 पूर्ण,
	अणु .pभाग = 24, .hw_val = 13 पूर्ण,
	अणु .pभाग = 32, .hw_val = 14 पूर्ण,
	अणु .pभाग =  1, .hw_val =  0 पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp plle_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 24,
	.भागp_width = 4,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_e_params = अणु
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 75000000,
	.vco_min = 1600000000,
	.vco_max = 2400000000U,
	.base_reg = PLLE_BASE,
	.misc_reg = PLLE_MISC,
	.aux_reg = PLLE_AUX,
	.lock_mask = PLLE_MISC_LOCK,
	.lock_enable_bit_idx = PLLE_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.pभाग_प्रकारohw = plle_p,
	.भाग_nmp = &plle_nmp,
	.freq_table = pll_e_freq_table,
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_HAS_LOCK_ENABLE,
	.fixed_rate = 100000000,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable pll_re_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 3 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 4, .भाग = 5 पूर्ण,
	अणु .val = 5, .भाग = 6 पूर्ण,
	अणु .val = 0, .भाग = 0 पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp pllre_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 16,
	.भागp_width = 4,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_re_vco_params = अणु
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w policy, h/w capability 38 MHz */
	.vco_min = 300000000,
	.vco_max = 600000000,
	.base_reg = PLLRE_BASE,
	.misc_reg = PLLRE_MISC,
	.lock_mask = PLLRE_MISC_LOCK,
	.lock_enable_bit_idx = PLLRE_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLRE_MISC,
	.iddq_bit_idx = PLLRE_IDDQ_BIT,
	.भाग_nmp = &pllre_nmp,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE |
		 TEGRA_PLL_LOCK_MISC,
पूर्ण;

अटल काष्ठा भाग_nmp pllp_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 5,
	.भागn_shअगरt = 8,
	.भागn_width = 10,
	.भागp_shअगरt = 20,
	.भागp_width = 3,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_p_freq_table[] = अणु
	अणु 12000000, 408000000, 408, 12, 1, 8 पूर्ण,
	अणु 13000000, 408000000, 408, 13, 1, 8 पूर्ण,
	अणु 16800000, 408000000, 340, 14, 1, 8 पूर्ण,
	अणु 19200000, 408000000, 340, 16, 1, 8 पूर्ण,
	अणु 26000000, 408000000, 408, 26, 1, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_p_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 200000000,
	.vco_max = 700000000,
	.base_reg = PLLP_BASE,
	.misc_reg = PLLP_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.भाग_nmp = &pllp_nmp,
	.freq_table = pll_p_freq_table,
	.fixed_rate = 408000000,
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_a_freq_table[] = अणु
	अणु  9600000, 282240000, 147,  5, 1, 4 पूर्ण,
	अणु  9600000, 368640000, 192,  5, 1, 4 पूर्ण,
	अणु  9600000, 240000000, 200,  8, 1, 8 पूर्ण,
	अणु 28800000, 282240000, 245, 25, 1, 8 पूर्ण,
	अणु 28800000, 368640000, 320, 25, 1, 8 पूर्ण,
	अणु 28800000, 240000000, 200, 24, 1, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_a_params = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 200000000,
	.vco_max = 700000000,
	.base_reg = PLLA_BASE,
	.misc_reg = PLLA_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.भाग_nmp = &pllp_nmp,
	.freq_table = pll_a_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा भाग_nmp plld_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 5,
	.भागn_shअगरt = 8,
	.भागn_width = 11,
	.भागp_shअगरt = 20,
	.भागp_width = 3,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_d_freq_table[] = अणु
	अणु 12000000,  216000000,  864, 12, 4, 12 पूर्ण,
	अणु 13000000,  216000000,  864, 13, 4, 12 पूर्ण,
	अणु 16800000,  216000000,  720, 14, 4, 12 पूर्ण,
	अणु 19200000,  216000000,  720, 16, 4, 12 पूर्ण,
	अणु 26000000,  216000000,  864, 26, 4, 12 पूर्ण,
	अणु 12000000,  594000000,  594, 12, 1, 12 पूर्ण,
	अणु 13000000,  594000000,  594, 13, 1, 12 पूर्ण,
	अणु 16800000,  594000000,  495, 14, 1, 12 पूर्ण,
	अणु 19200000,  594000000,  495, 16, 1, 12 पूर्ण,
	अणु 26000000,  594000000,  594, 26, 1, 12 पूर्ण,
	अणु 12000000, 1000000000, 1000, 12, 1, 12 पूर्ण,
	अणु 13000000, 1000000000, 1000, 13, 1, 12 पूर्ण,
	अणु 19200000, 1000000000,  625, 12, 1, 12 पूर्ण,
	अणु 26000000, 1000000000, 1000, 26, 1, 12 पूर्ण,
	अणु        0,          0,    0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_d_params = अणु
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 500000000,
	.vco_max = 1000000000,
	.base_reg = PLLD_BASE,
	.misc_reg = PLLD_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLDU_MISC_LOCK_ENABLE,
	.lock_delay = 1000,
	.भाग_nmp = &plld_nmp,
	.freq_table = pll_d_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_SET_LFCON |
		 TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table tegra124_pll_d2_freq_table[] = अणु
	अणु 12000000, 594000000, 99, 1, 2, 0 पूर्ण,
	अणु 13000000, 594000000, 91, 1, 2, 0 पूर्ण, /* actual: 591.5 MHz */
	अणु 16800000, 594000000, 71, 1, 2, 0 पूर्ण, /* actual: 596.4 MHz */
	अणु 19200000, 594000000, 62, 1, 2, 0 पूर्ण, /* actual: 595.2 MHz */
	अणु 26000000, 594000000, 91, 2, 2, 0 पूर्ण, /* actual: 591.5 MHz */
	अणु        0,         0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params tegra124_pll_d2_params = अणु
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w policy, h/w capability 38 MHz */
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLD2_BASE,
	.misc_reg = PLLD2_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLSS_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLD2_BASE,
	.iddq_bit_idx = PLLSS_IDDQ_BIT,
	.pभाग_प्रकारohw = pll12g_ssd_esd_p,
	.भाग_nmp = &pllss_nmp,
	.ext_misc_reg[0] = 0x570,
	.ext_misc_reg[1] = 0x574,
	.ext_misc_reg[2] = 0x578,
	.max_p = 15,
	.freq_table = tegra124_pll_d2_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_dp_freq_table[] = अणु
	अणु 12000000, 600000000, 100, 1, 2, 0 पूर्ण,
	अणु 13000000, 600000000,  92, 1, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु 16800000, 600000000,  71, 1, 2, 0 पूर्ण, /* actual: 596.4 MHz */
	अणु 19200000, 600000000,  62, 1, 2, 0 पूर्ण, /* actual: 595.2 MHz */
	अणु 26000000, 600000000,  92, 2, 2, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु        0,         0,   0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_dp_params = अणु
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w policy, h/w capability 38 MHz */
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLDP_BASE,
	.misc_reg = PLLDP_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLSS_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLDP_BASE,
	.iddq_bit_idx = PLLSS_IDDQ_BIT,
	.pभाग_प्रकारohw = pll12g_ssd_esd_p,
	.भाग_nmp = &pllss_nmp,
	.ext_misc_reg[0] = 0x598,
	.ext_misc_reg[1] = 0x59c,
	.ext_misc_reg[2] = 0x5a0,
	.max_p = 5,
	.freq_table = pll_dp_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pllu_p[] = अणु
	अणु .pभाग = 1, .hw_val = 1 पूर्ण,
	अणु .pभाग = 2, .hw_val = 0 पूर्ण,
	अणु .pभाग = 0, .hw_val = 0 पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp pllu_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 5,
	.भागn_shअगरt = 8,
	.भागn_width = 10,
	.भागp_shअगरt = 20,
	.भागp_width = 1,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_u_freq_table[] = अणु
	अणु 12000000, 480000000, 960, 12, 2, 12 पूर्ण,
	अणु 13000000, 480000000, 960, 13, 2, 12 पूर्ण,
	अणु 16800000, 480000000, 400,  7, 2,  5 पूर्ण,
	अणु 19200000, 480000000, 200,  4, 2,  3 पूर्ण,
	अणु 26000000, 480000000, 960, 26, 2, 12 पूर्ण,
	अणु        0,         0,   0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_u_params = अणु
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 480000000,
	.vco_max = 960000000,
	.base_reg = PLLU_BASE,
	.misc_reg = PLLU_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLDU_MISC_LOCK_ENABLE,
	.lock_delay = 1000,
	.pभाग_प्रकारohw = pllu_p,
	.भाग_nmp = &pllu_nmp,
	.freq_table = pll_u_freq_table,
	.flags = TEGRA_PLLU | TEGRA_PLL_HAS_CPCON | TEGRA_PLL_SET_LFCON |
		 TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk tegra124_clks[tegra_clk_max] __initdata = अणु
	[tegra_clk_ispb] = अणु .dt_id = TEGRA124_CLK_ISPB, .present = true पूर्ण,
	[tegra_clk_rtc] = अणु .dt_id = TEGRA124_CLK_RTC, .present = true पूर्ण,
	[tegra_clk_समयr] = अणु .dt_id = TEGRA124_CLK_TIMER, .present = true पूर्ण,
	[tegra_clk_uarta] = अणु .dt_id = TEGRA124_CLK_UARTA, .present = true पूर्ण,
	[tegra_clk_sdmmc2_8] = अणु .dt_id = TEGRA124_CLK_SDMMC2, .present = true पूर्ण,
	[tegra_clk_i2s1] = अणु .dt_id = TEGRA124_CLK_I2S1, .present = true पूर्ण,
	[tegra_clk_i2c1] = अणु .dt_id = TEGRA124_CLK_I2C1, .present = true पूर्ण,
	[tegra_clk_sdmmc1_8] = अणु .dt_id = TEGRA124_CLK_SDMMC1, .present = true पूर्ण,
	[tegra_clk_sdmmc4_8] = अणु .dt_id = TEGRA124_CLK_SDMMC4, .present = true पूर्ण,
	[tegra_clk_pwm] = अणु .dt_id = TEGRA124_CLK_PWM, .present = true पूर्ण,
	[tegra_clk_i2s2] = अणु .dt_id = TEGRA124_CLK_I2S2, .present = true पूर्ण,
	[tegra_clk_usbd] = अणु .dt_id = TEGRA124_CLK_USBD, .present = true पूर्ण,
	[tegra_clk_isp_8] = अणु .dt_id = TEGRA124_CLK_ISP, .present = true पूर्ण,
	[tegra_clk_disp2] = अणु .dt_id = TEGRA124_CLK_DISP2, .present = true पूर्ण,
	[tegra_clk_disp1] = अणु .dt_id = TEGRA124_CLK_DISP1, .present = true पूर्ण,
	[tegra_clk_host1x_8] = अणु .dt_id = TEGRA124_CLK_HOST1X, .present = true पूर्ण,
	[tegra_clk_vcp] = अणु .dt_id = TEGRA124_CLK_VCP, .present = true पूर्ण,
	[tegra_clk_i2s0] = अणु .dt_id = TEGRA124_CLK_I2S0, .present = true पूर्ण,
	[tegra_clk_apbdma] = अणु .dt_id = TEGRA124_CLK_APBDMA, .present = true पूर्ण,
	[tegra_clk_kbc] = अणु .dt_id = TEGRA124_CLK_KBC, .present = true पूर्ण,
	[tegra_clk_kfuse] = अणु .dt_id = TEGRA124_CLK_KFUSE, .present = true पूर्ण,
	[tegra_clk_sbc1] = अणु .dt_id = TEGRA124_CLK_SBC1, .present = true पूर्ण,
	[tegra_clk_nor] = अणु .dt_id = TEGRA124_CLK_NOR, .present = true पूर्ण,
	[tegra_clk_sbc2] = अणु .dt_id = TEGRA124_CLK_SBC2, .present = true पूर्ण,
	[tegra_clk_sbc3] = अणु .dt_id = TEGRA124_CLK_SBC3, .present = true पूर्ण,
	[tegra_clk_i2c5] = अणु .dt_id = TEGRA124_CLK_I2C5, .present = true पूर्ण,
	[tegra_clk_mipi] = अणु .dt_id = TEGRA124_CLK_MIPI, .present = true पूर्ण,
	[tegra_clk_hdmi] = अणु .dt_id = TEGRA124_CLK_HDMI, .present = true पूर्ण,
	[tegra_clk_csi] = अणु .dt_id = TEGRA124_CLK_CSI, .present = true पूर्ण,
	[tegra_clk_i2c2] = अणु .dt_id = TEGRA124_CLK_I2C2, .present = true पूर्ण,
	[tegra_clk_uartc] = अणु .dt_id = TEGRA124_CLK_UARTC, .present = true पूर्ण,
	[tegra_clk_mipi_cal] = अणु .dt_id = TEGRA124_CLK_MIPI_CAL, .present = true पूर्ण,
	[tegra_clk_usb2] = अणु .dt_id = TEGRA124_CLK_USB2, .present = true पूर्ण,
	[tegra_clk_usb3] = अणु .dt_id = TEGRA124_CLK_USB3, .present = true पूर्ण,
	[tegra_clk_vde_8] = अणु .dt_id = TEGRA124_CLK_VDE, .present = true पूर्ण,
	[tegra_clk_bsea] = अणु .dt_id = TEGRA124_CLK_BSEA, .present = true पूर्ण,
	[tegra_clk_bsev] = अणु .dt_id = TEGRA124_CLK_BSEV, .present = true पूर्ण,
	[tegra_clk_uartd] = अणु .dt_id = TEGRA124_CLK_UARTD, .present = true पूर्ण,
	[tegra_clk_i2c3] = अणु .dt_id = TEGRA124_CLK_I2C3, .present = true पूर्ण,
	[tegra_clk_sbc4] = अणु .dt_id = TEGRA124_CLK_SBC4, .present = true पूर्ण,
	[tegra_clk_sdmmc3_8] = अणु .dt_id = TEGRA124_CLK_SDMMC3, .present = true पूर्ण,
	[tegra_clk_pcie] = अणु .dt_id = TEGRA124_CLK_PCIE, .present = true पूर्ण,
	[tegra_clk_owr] = अणु .dt_id = TEGRA124_CLK_OWR, .present = true पूर्ण,
	[tegra_clk_afi] = अणु .dt_id = TEGRA124_CLK_AFI, .present = true पूर्ण,
	[tegra_clk_csite] = अणु .dt_id = TEGRA124_CLK_CSITE, .present = true पूर्ण,
	[tegra_clk_la] = अणु .dt_id = TEGRA124_CLK_LA, .present = true पूर्ण,
	[tegra_clk_trace] = अणु .dt_id = TEGRA124_CLK_TRACE, .present = true पूर्ण,
	[tegra_clk_soc_therm] = अणु .dt_id = TEGRA124_CLK_SOC_THERM, .present = true पूर्ण,
	[tegra_clk_dtv] = अणु .dt_id = TEGRA124_CLK_DTV, .present = true पूर्ण,
	[tegra_clk_i2cslow] = अणु .dt_id = TEGRA124_CLK_I2CSLOW, .present = true पूर्ण,
	[tegra_clk_tsec] = अणु .dt_id = TEGRA124_CLK_TSEC, .present = true पूर्ण,
	[tegra_clk_xusb_host] = अणु .dt_id = TEGRA124_CLK_XUSB_HOST, .present = true पूर्ण,
	[tegra_clk_msenc] = अणु .dt_id = TEGRA124_CLK_MSENC, .present = true पूर्ण,
	[tegra_clk_csus] = अणु .dt_id = TEGRA124_CLK_CSUS, .present = true पूर्ण,
	[tegra_clk_mselect] = अणु .dt_id = TEGRA124_CLK_MSELECT, .present = true पूर्ण,
	[tegra_clk_tsensor] = अणु .dt_id = TEGRA124_CLK_TSENSOR, .present = true पूर्ण,
	[tegra_clk_i2s3] = अणु .dt_id = TEGRA124_CLK_I2S3, .present = true पूर्ण,
	[tegra_clk_i2s4] = अणु .dt_id = TEGRA124_CLK_I2S4, .present = true पूर्ण,
	[tegra_clk_i2c4] = अणु .dt_id = TEGRA124_CLK_I2C4, .present = true पूर्ण,
	[tegra_clk_sbc5] = अणु .dt_id = TEGRA124_CLK_SBC5, .present = true पूर्ण,
	[tegra_clk_sbc6] = अणु .dt_id = TEGRA124_CLK_SBC6, .present = true पूर्ण,
	[tegra_clk_d_audio] = अणु .dt_id = TEGRA124_CLK_D_AUDIO, .present = true पूर्ण,
	[tegra_clk_apbअगर] = अणु .dt_id = TEGRA124_CLK_APBIF, .present = true पूर्ण,
	[tegra_clk_dam0] = अणु .dt_id = TEGRA124_CLK_DAM0, .present = true पूर्ण,
	[tegra_clk_dam1] = अणु .dt_id = TEGRA124_CLK_DAM1, .present = true पूर्ण,
	[tegra_clk_dam2] = अणु .dt_id = TEGRA124_CLK_DAM2, .present = true पूर्ण,
	[tegra_clk_hda2codec_2x] = अणु .dt_id = TEGRA124_CLK_HDA2CODEC_2X, .present = true पूर्ण,
	[tegra_clk_audio0_2x] = अणु .dt_id = TEGRA124_CLK_AUDIO0_2X, .present = true पूर्ण,
	[tegra_clk_audio1_2x] = अणु .dt_id = TEGRA124_CLK_AUDIO1_2X, .present = true पूर्ण,
	[tegra_clk_audio2_2x] = अणु .dt_id = TEGRA124_CLK_AUDIO2_2X, .present = true पूर्ण,
	[tegra_clk_audio3_2x] = अणु .dt_id = TEGRA124_CLK_AUDIO3_2X, .present = true पूर्ण,
	[tegra_clk_audio4_2x] = अणु .dt_id = TEGRA124_CLK_AUDIO4_2X, .present = true पूर्ण,
	[tegra_clk_spdअगर_2x] = अणु .dt_id = TEGRA124_CLK_SPDIF_2X, .present = true पूर्ण,
	[tegra_clk_acपंचांगon] = अणु .dt_id = TEGRA124_CLK_ACTMON, .present = true पूर्ण,
	[tegra_clk_बाह्य1] = अणु .dt_id = TEGRA124_CLK_EXTERN1, .present = true पूर्ण,
	[tegra_clk_बाह्य2] = अणु .dt_id = TEGRA124_CLK_EXTERN2, .present = true पूर्ण,
	[tegra_clk_बाह्य3] = अणु .dt_id = TEGRA124_CLK_EXTERN3, .present = true पूर्ण,
	[tegra_clk_sata_oob] = अणु .dt_id = TEGRA124_CLK_SATA_OOB, .present = true पूर्ण,
	[tegra_clk_sata] = अणु .dt_id = TEGRA124_CLK_SATA, .present = true पूर्ण,
	[tegra_clk_hda] = अणु .dt_id = TEGRA124_CLK_HDA, .present = true पूर्ण,
	[tegra_clk_se] = अणु .dt_id = TEGRA124_CLK_SE, .present = true पूर्ण,
	[tegra_clk_hda2hdmi] = अणु .dt_id = TEGRA124_CLK_HDA2HDMI, .present = true पूर्ण,
	[tegra_clk_sata_cold] = अणु .dt_id = TEGRA124_CLK_SATA_COLD, .present = true पूर्ण,
	[tegra_clk_cilab] = अणु .dt_id = TEGRA124_CLK_CILAB, .present = true पूर्ण,
	[tegra_clk_cilcd] = अणु .dt_id = TEGRA124_CLK_CILCD, .present = true पूर्ण,
	[tegra_clk_cile] = अणु .dt_id = TEGRA124_CLK_CILE, .present = true पूर्ण,
	[tegra_clk_dsialp] = अणु .dt_id = TEGRA124_CLK_DSIALP, .present = true पूर्ण,
	[tegra_clk_dsiblp] = अणु .dt_id = TEGRA124_CLK_DSIBLP, .present = true पूर्ण,
	[tegra_clk_entropy] = अणु .dt_id = TEGRA124_CLK_ENTROPY, .present = true पूर्ण,
	[tegra_clk_dds] = अणु .dt_id = TEGRA124_CLK_DDS, .present = true पूर्ण,
	[tegra_clk_dp2] = अणु .dt_id = TEGRA124_CLK_DP2, .present = true पूर्ण,
	[tegra_clk_amx] = अणु .dt_id = TEGRA124_CLK_AMX, .present = true पूर्ण,
	[tegra_clk_adx] = अणु .dt_id = TEGRA124_CLK_ADX, .present = true पूर्ण,
	[tegra_clk_xusb_ss] = अणु .dt_id = TEGRA124_CLK_XUSB_SS, .present = true पूर्ण,
	[tegra_clk_i2c6] = अणु .dt_id = TEGRA124_CLK_I2C6, .present = true पूर्ण,
	[tegra_clk_vim2_clk] = अणु .dt_id = TEGRA124_CLK_VIM2_CLK, .present = true पूर्ण,
	[tegra_clk_hdmi_audio] = अणु .dt_id = TEGRA124_CLK_HDMI_AUDIO, .present = true पूर्ण,
	[tegra_clk_clk72Mhz] = अणु .dt_id = TEGRA124_CLK_CLK72MHZ, .present = true पूर्ण,
	[tegra_clk_vic03] = अणु .dt_id = TEGRA124_CLK_VIC03, .present = true पूर्ण,
	[tegra_clk_adx1] = अणु .dt_id = TEGRA124_CLK_ADX1, .present = true पूर्ण,
	[tegra_clk_dpaux] = अणु .dt_id = TEGRA124_CLK_DPAUX, .present = true पूर्ण,
	[tegra_clk_sor0] = अणु .dt_id = TEGRA124_CLK_SOR0, .present = true पूर्ण,
	[tegra_clk_sor0_out] = अणु .dt_id = TEGRA124_CLK_SOR0_OUT, .present = true पूर्ण,
	[tegra_clk_gpu] = अणु .dt_id = TEGRA124_CLK_GPU, .present = true पूर्ण,
	[tegra_clk_amx1] = अणु .dt_id = TEGRA124_CLK_AMX1, .present = true पूर्ण,
	[tegra_clk_uartb] = अणु .dt_id = TEGRA124_CLK_UARTB, .present = true पूर्ण,
	[tegra_clk_vfir] = अणु .dt_id = TEGRA124_CLK_VFIR, .present = true पूर्ण,
	[tegra_clk_spdअगर_in] = अणु .dt_id = TEGRA124_CLK_SPDIF_IN, .present = true पूर्ण,
	[tegra_clk_spdअगर_out] = अणु .dt_id = TEGRA124_CLK_SPDIF_OUT, .present = true पूर्ण,
	[tegra_clk_vi_9] = अणु .dt_id = TEGRA124_CLK_VI, .present = true पूर्ण,
	[tegra_clk_vi_sensor_8] = अणु .dt_id = TEGRA124_CLK_VI_SENSOR, .present = true पूर्ण,
	[tegra_clk_fuse] = अणु .dt_id = TEGRA124_CLK_FUSE, .present = true पूर्ण,
	[tegra_clk_fuse_burn] = अणु .dt_id = TEGRA124_CLK_FUSE_BURN, .present = true पूर्ण,
	[tegra_clk_clk_32k] = अणु .dt_id = TEGRA124_CLK_CLK_32K, .present = true पूर्ण,
	[tegra_clk_clk_m] = अणु .dt_id = TEGRA124_CLK_CLK_M, .present = true पूर्ण,
	[tegra_clk_osc] = अणु .dt_id = TEGRA124_CLK_OSC, .present = true पूर्ण,
	[tegra_clk_osc_भाग2] = अणु .dt_id = TEGRA124_CLK_OSC_DIV2, .present = true पूर्ण,
	[tegra_clk_osc_भाग4] = अणु .dt_id = TEGRA124_CLK_OSC_DIV4, .present = true पूर्ण,
	[tegra_clk_pll_ref] = अणु .dt_id = TEGRA124_CLK_PLL_REF, .present = true पूर्ण,
	[tegra_clk_pll_c] = अणु .dt_id = TEGRA124_CLK_PLL_C, .present = true पूर्ण,
	[tegra_clk_pll_c_out1] = अणु .dt_id = TEGRA124_CLK_PLL_C_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_c2] = अणु .dt_id = TEGRA124_CLK_PLL_C2, .present = true पूर्ण,
	[tegra_clk_pll_c3] = अणु .dt_id = TEGRA124_CLK_PLL_C3, .present = true पूर्ण,
	[tegra_clk_pll_m] = अणु .dt_id = TEGRA124_CLK_PLL_M, .present = true पूर्ण,
	[tegra_clk_pll_m_out1] = अणु .dt_id = TEGRA124_CLK_PLL_M_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_p] = अणु .dt_id = TEGRA124_CLK_PLL_P, .present = true पूर्ण,
	[tegra_clk_pll_p_out1] = अणु .dt_id = TEGRA124_CLK_PLL_P_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_p_out2] = अणु .dt_id = TEGRA124_CLK_PLL_P_OUT2, .present = true पूर्ण,
	[tegra_clk_pll_p_out3] = अणु .dt_id = TEGRA124_CLK_PLL_P_OUT3, .present = true पूर्ण,
	[tegra_clk_pll_p_out4] = अणु .dt_id = TEGRA124_CLK_PLL_P_OUT4, .present = true पूर्ण,
	[tegra_clk_pll_a] = अणु .dt_id = TEGRA124_CLK_PLL_A, .present = true पूर्ण,
	[tegra_clk_pll_a_out0] = अणु .dt_id = TEGRA124_CLK_PLL_A_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_d] = अणु .dt_id = TEGRA124_CLK_PLL_D, .present = true पूर्ण,
	[tegra_clk_pll_d_out0] = अणु .dt_id = TEGRA124_CLK_PLL_D_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_d2] = अणु .dt_id = TEGRA124_CLK_PLL_D2, .present = true पूर्ण,
	[tegra_clk_pll_d2_out0] = अणु .dt_id = TEGRA124_CLK_PLL_D2_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_u] = अणु .dt_id = TEGRA124_CLK_PLL_U, .present = true पूर्ण,
	[tegra_clk_pll_u_480m] = अणु .dt_id = TEGRA124_CLK_PLL_U_480M, .present = true पूर्ण,
	[tegra_clk_pll_u_60m] = अणु .dt_id = TEGRA124_CLK_PLL_U_60M, .present = true पूर्ण,
	[tegra_clk_pll_u_48m] = अणु .dt_id = TEGRA124_CLK_PLL_U_48M, .present = true पूर्ण,
	[tegra_clk_pll_u_12m] = अणु .dt_id = TEGRA124_CLK_PLL_U_12M, .present = true पूर्ण,
	[tegra_clk_pll_x] = अणु .dt_id = TEGRA124_CLK_PLL_X, .present = true पूर्ण,
	[tegra_clk_pll_x_out0] = अणु .dt_id = TEGRA124_CLK_PLL_X_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_re_vco] = अणु .dt_id = TEGRA124_CLK_PLL_RE_VCO, .present = true पूर्ण,
	[tegra_clk_pll_re_out] = अणु .dt_id = TEGRA124_CLK_PLL_RE_OUT, .present = true पूर्ण,
	[tegra_clk_spdअगर_in_sync] = अणु .dt_id = TEGRA124_CLK_SPDIF_IN_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s0_sync] = अणु .dt_id = TEGRA124_CLK_I2S0_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s1_sync] = अणु .dt_id = TEGRA124_CLK_I2S1_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s2_sync] = अणु .dt_id = TEGRA124_CLK_I2S2_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s3_sync] = अणु .dt_id = TEGRA124_CLK_I2S3_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s4_sync] = अणु .dt_id = TEGRA124_CLK_I2S4_SYNC, .present = true पूर्ण,
	[tegra_clk_vimclk_sync] = अणु .dt_id = TEGRA124_CLK_VIMCLK_SYNC, .present = true पूर्ण,
	[tegra_clk_audio0] = अणु .dt_id = TEGRA124_CLK_AUDIO0, .present = true पूर्ण,
	[tegra_clk_audio1] = अणु .dt_id = TEGRA124_CLK_AUDIO1, .present = true पूर्ण,
	[tegra_clk_audio2] = अणु .dt_id = TEGRA124_CLK_AUDIO2, .present = true पूर्ण,
	[tegra_clk_audio3] = अणु .dt_id = TEGRA124_CLK_AUDIO3, .present = true पूर्ण,
	[tegra_clk_audio4] = अणु .dt_id = TEGRA124_CLK_AUDIO4, .present = true पूर्ण,
	[tegra_clk_spdअगर] = अणु .dt_id = TEGRA124_CLK_SPDIF, .present = true पूर्ण,
	[tegra_clk_xusb_host_src] = अणु .dt_id = TEGRA124_CLK_XUSB_HOST_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_falcon_src] = अणु .dt_id = TEGRA124_CLK_XUSB_FALCON_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_fs_src] = अणु .dt_id = TEGRA124_CLK_XUSB_FS_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_ss_src] = अणु .dt_id = TEGRA124_CLK_XUSB_SS_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_ss_भाग2] = अणु .dt_id = TEGRA124_CLK_XUSB_SS_DIV2, .present = true पूर्ण,
	[tegra_clk_xusb_dev_src] = अणु .dt_id = TEGRA124_CLK_XUSB_DEV_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_dev] = अणु .dt_id = TEGRA124_CLK_XUSB_DEV, .present = true पूर्ण,
	[tegra_clk_xusb_hs_src] = अणु .dt_id = TEGRA124_CLK_XUSB_HS_SRC, .present = true पूर्ण,
	[tegra_clk_sclk] = अणु .dt_id = TEGRA124_CLK_SCLK, .present = true पूर्ण,
	[tegra_clk_hclk] = अणु .dt_id = TEGRA124_CLK_HCLK, .present = true पूर्ण,
	[tegra_clk_pclk] = अणु .dt_id = TEGRA124_CLK_PCLK, .present = true पूर्ण,
	[tegra_clk_cclk_g] = अणु .dt_id = TEGRA124_CLK_CCLK_G, .present = true पूर्ण,
	[tegra_clk_cclk_lp] = अणु .dt_id = TEGRA124_CLK_CCLK_LP, .present = true पूर्ण,
	[tegra_clk_dfll_ref] = अणु .dt_id = TEGRA124_CLK_DFLL_REF, .present = true पूर्ण,
	[tegra_clk_dfll_soc] = अणु .dt_id = TEGRA124_CLK_DFLL_SOC, .present = true पूर्ण,
	[tegra_clk_vi_sensor2] = अणु .dt_id = TEGRA124_CLK_VI_SENSOR2, .present = true पूर्ण,
	[tegra_clk_pll_p_out5] = अणु .dt_id = TEGRA124_CLK_PLL_P_OUT5, .present = true पूर्ण,
	[tegra_clk_pll_c4] = अणु .dt_id = TEGRA124_CLK_PLL_C4, .present = true पूर्ण,
	[tegra_clk_pll_dp] = अणु .dt_id = TEGRA124_CLK_PLL_DP, .present = true पूर्ण,
	[tegra_clk_audio0_mux] = अणु .dt_id = TEGRA124_CLK_AUDIO0_MUX, .present = true पूर्ण,
	[tegra_clk_audio1_mux] = अणु .dt_id = TEGRA124_CLK_AUDIO1_MUX, .present = true पूर्ण,
	[tegra_clk_audio2_mux] = अणु .dt_id = TEGRA124_CLK_AUDIO2_MUX, .present = true पूर्ण,
	[tegra_clk_audio3_mux] = अणु .dt_id = TEGRA124_CLK_AUDIO3_MUX, .present = true पूर्ण,
	[tegra_clk_audio4_mux] = अणु .dt_id = TEGRA124_CLK_AUDIO4_MUX, .present = true पूर्ण,
	[tegra_clk_spdअगर_mux] = अणु .dt_id = TEGRA124_CLK_SPDIF_MUX, .present = true पूर्ण,
	[tegra_clk_cec] = अणु .dt_id = TEGRA124_CLK_CEC, .present = true पूर्ण,
पूर्ण;

अटल काष्ठा tegra_devclk devclks[] __initdata = अणु
	अणु .con_id = "clk_m", .dt_id = TEGRA124_CLK_CLK_M पूर्ण,
	अणु .con_id = "pll_ref", .dt_id = TEGRA124_CLK_PLL_REF पूर्ण,
	अणु .con_id = "clk_32k", .dt_id = TEGRA124_CLK_CLK_32K पूर्ण,
	अणु .con_id = "osc", .dt_id = TEGRA124_CLK_OSC पूर्ण,
	अणु .con_id = "osc_div2", .dt_id = TEGRA124_CLK_OSC_DIV2 पूर्ण,
	अणु .con_id = "osc_div4", .dt_id = TEGRA124_CLK_OSC_DIV4 पूर्ण,
	अणु .con_id = "pll_c", .dt_id = TEGRA124_CLK_PLL_C पूर्ण,
	अणु .con_id = "pll_c_out1", .dt_id = TEGRA124_CLK_PLL_C_OUT1 पूर्ण,
	अणु .con_id = "pll_c2", .dt_id = TEGRA124_CLK_PLL_C2 पूर्ण,
	अणु .con_id = "pll_c3", .dt_id = TEGRA124_CLK_PLL_C3 पूर्ण,
	अणु .con_id = "pll_p", .dt_id = TEGRA124_CLK_PLL_P पूर्ण,
	अणु .con_id = "pll_p_out1", .dt_id = TEGRA124_CLK_PLL_P_OUT1 पूर्ण,
	अणु .con_id = "pll_p_out2", .dt_id = TEGRA124_CLK_PLL_P_OUT2 पूर्ण,
	अणु .con_id = "pll_p_out3", .dt_id = TEGRA124_CLK_PLL_P_OUT3 पूर्ण,
	अणु .con_id = "pll_p_out4", .dt_id = TEGRA124_CLK_PLL_P_OUT4 पूर्ण,
	अणु .con_id = "pll_m", .dt_id = TEGRA124_CLK_PLL_M पूर्ण,
	अणु .con_id = "pll_m_out1", .dt_id = TEGRA124_CLK_PLL_M_OUT1 पूर्ण,
	अणु .con_id = "pll_x", .dt_id = TEGRA124_CLK_PLL_X पूर्ण,
	अणु .con_id = "pll_x_out0", .dt_id = TEGRA124_CLK_PLL_X_OUT0 पूर्ण,
	अणु .con_id = "pll_u", .dt_id = TEGRA124_CLK_PLL_U पूर्ण,
	अणु .con_id = "pll_u_480M", .dt_id = TEGRA124_CLK_PLL_U_480M पूर्ण,
	अणु .con_id = "pll_u_60M", .dt_id = TEGRA124_CLK_PLL_U_60M पूर्ण,
	अणु .con_id = "pll_u_48M", .dt_id = TEGRA124_CLK_PLL_U_48M पूर्ण,
	अणु .con_id = "pll_u_12M", .dt_id = TEGRA124_CLK_PLL_U_12M पूर्ण,
	अणु .con_id = "pll_d", .dt_id = TEGRA124_CLK_PLL_D पूर्ण,
	अणु .con_id = "pll_d_out0", .dt_id = TEGRA124_CLK_PLL_D_OUT0 पूर्ण,
	अणु .con_id = "pll_d2", .dt_id = TEGRA124_CLK_PLL_D2 पूर्ण,
	अणु .con_id = "pll_d2_out0", .dt_id = TEGRA124_CLK_PLL_D2_OUT0 पूर्ण,
	अणु .con_id = "pll_a", .dt_id = TEGRA124_CLK_PLL_A पूर्ण,
	अणु .con_id = "pll_a_out0", .dt_id = TEGRA124_CLK_PLL_A_OUT0 पूर्ण,
	अणु .con_id = "pll_re_vco", .dt_id = TEGRA124_CLK_PLL_RE_VCO पूर्ण,
	अणु .con_id = "pll_re_out", .dt_id = TEGRA124_CLK_PLL_RE_OUT पूर्ण,
	अणु .con_id = "spdif_in_sync", .dt_id = TEGRA124_CLK_SPDIF_IN_SYNC पूर्ण,
	अणु .con_id = "i2s0_sync", .dt_id = TEGRA124_CLK_I2S0_SYNC पूर्ण,
	अणु .con_id = "i2s1_sync", .dt_id = TEGRA124_CLK_I2S1_SYNC पूर्ण,
	अणु .con_id = "i2s2_sync", .dt_id = TEGRA124_CLK_I2S2_SYNC पूर्ण,
	अणु .con_id = "i2s3_sync", .dt_id = TEGRA124_CLK_I2S3_SYNC पूर्ण,
	अणु .con_id = "i2s4_sync", .dt_id = TEGRA124_CLK_I2S4_SYNC पूर्ण,
	अणु .con_id = "vimclk_sync", .dt_id = TEGRA124_CLK_VIMCLK_SYNC पूर्ण,
	अणु .con_id = "audio0", .dt_id = TEGRA124_CLK_AUDIO0 पूर्ण,
	अणु .con_id = "audio1", .dt_id = TEGRA124_CLK_AUDIO1 पूर्ण,
	अणु .con_id = "audio2", .dt_id = TEGRA124_CLK_AUDIO2 पूर्ण,
	अणु .con_id = "audio3", .dt_id = TEGRA124_CLK_AUDIO3 पूर्ण,
	अणु .con_id = "audio4", .dt_id = TEGRA124_CLK_AUDIO4 पूर्ण,
	अणु .con_id = "spdif", .dt_id = TEGRA124_CLK_SPDIF पूर्ण,
	अणु .con_id = "audio0_2x", .dt_id = TEGRA124_CLK_AUDIO0_2X पूर्ण,
	अणु .con_id = "audio1_2x", .dt_id = TEGRA124_CLK_AUDIO1_2X पूर्ण,
	अणु .con_id = "audio2_2x", .dt_id = TEGRA124_CLK_AUDIO2_2X पूर्ण,
	अणु .con_id = "audio3_2x", .dt_id = TEGRA124_CLK_AUDIO3_2X पूर्ण,
	अणु .con_id = "audio4_2x", .dt_id = TEGRA124_CLK_AUDIO4_2X पूर्ण,
	अणु .con_id = "spdif_2x", .dt_id = TEGRA124_CLK_SPDIF_2X पूर्ण,
	अणु .con_id = "extern1", .dt_id = TEGRA124_CLK_EXTERN1 पूर्ण,
	अणु .con_id = "extern2", .dt_id = TEGRA124_CLK_EXTERN2 पूर्ण,
	अणु .con_id = "extern3", .dt_id = TEGRA124_CLK_EXTERN3 पूर्ण,
	अणु .con_id = "cclk_g", .dt_id = TEGRA124_CLK_CCLK_G पूर्ण,
	अणु .con_id = "cclk_lp", .dt_id = TEGRA124_CLK_CCLK_LP पूर्ण,
	अणु .con_id = "sclk", .dt_id = TEGRA124_CLK_SCLK पूर्ण,
	अणु .con_id = "hclk", .dt_id = TEGRA124_CLK_HCLK पूर्ण,
	अणु .con_id = "pclk", .dt_id = TEGRA124_CLK_PCLK पूर्ण,
	अणु .con_id = "fuse", .dt_id = TEGRA124_CLK_FUSE पूर्ण,
	अणु .dev_id = "rtc-tegra", .dt_id = TEGRA124_CLK_RTC पूर्ण,
	अणु .dev_id = "timer", .dt_id = TEGRA124_CLK_TIMER पूर्ण,
	अणु .con_id = "hda", .dt_id = TEGRA124_CLK_HDA पूर्ण,
	अणु .con_id = "hda2codec_2x", .dt_id = TEGRA124_CLK_HDA2CODEC_2X पूर्ण,
	अणु .con_id = "hda2hdmi", .dt_id = TEGRA124_CLK_HDA2HDMI पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर sor0_parents[] = अणु
	"pll_p_out0", "pll_m_out0", "pll_d_out0", "pll_a_out0", "pll_c_out0",
	"pll_d2_out0", "clk_m",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sor0_out_parents[] = अणु
	"clk_m", "sor0_pad_clkout",
पूर्ण;

अटल काष्ठा tegra_periph_init_data tegra124_periph[] = अणु
	TEGRA_INIT_DATA_TABLE("sor0", शून्य, शून्य, sor0_parents,
			      CLK_SOURCE_SOR0, 29, 0x7, 0, 0, 0, 0,
			      0, 182, 0, tegra_clk_sor0, शून्य, 0,
			      &sor0_lock),
	TEGRA_INIT_DATA_TABLE("sor0_out", शून्य, शून्य, sor0_out_parents,
			      CLK_SOURCE_SOR0, 14, 0x1, 0, 0, 0, 0,
			      0, 0, TEGRA_PERIPH_NO_GATE, tegra_clk_sor0_out,
			      शून्य, 0, &sor0_lock),
पूर्ण;

अटल काष्ठा clk **clks;

अटल __init व्योम tegra124_periph_clk_init(व्योम __iomem *clk_base,
					    व्योम __iomem *pmc_base)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	/* xusb_ss_भाग2 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "xusb_ss_div2", "xusb_ss_src", 0,
					1, 2);
	clks[TEGRA124_CLK_XUSB_SS_DIV2] = clk;

	clk = tegra_clk_रेजिस्टर_periph_fixed("dpaux", "pll_p", 0, clk_base,
					      1, 17, 181);
	clks[TEGRA124_CLK_DPAUX] = clk;

	clk = clk_रेजिस्टर_gate(शून्य, "pll_d_dsi_out", "pll_d_out0", 0,
				clk_base + PLLD_MISC, 30, 0, &pll_d_lock);
	clks[TEGRA124_CLK_PLL_D_DSI_OUT] = clk;

	clk = tegra_clk_रेजिस्टर_periph_gate("dsia", "pll_d_dsi_out", 0,
					     clk_base, 0, 48,
					     periph_clk_enb_refcnt);
	clks[TEGRA124_CLK_DSIA] = clk;

	clk = tegra_clk_रेजिस्टर_periph_gate("dsib", "pll_d_dsi_out", 0,
					     clk_base, 0, 82,
					     periph_clk_enb_refcnt);
	clks[TEGRA124_CLK_DSIB] = clk;

	clk = tegra_clk_रेजिस्टर_mc("mc", "emc", clk_base + CLK_SOURCE_EMC,
				    &emc_lock);
	clks[TEGRA124_CLK_MC] = clk;

	/* cml0 */
	clk = clk_रेजिस्टर_gate(शून्य, "cml0", "pll_e", 0, clk_base + PLLE_AUX,
				0, 0, &pll_e_lock);
	clk_रेजिस्टर_clkdev(clk, "cml0", शून्य);
	clks[TEGRA124_CLK_CML0] = clk;

	/* cml1 */
	clk = clk_रेजिस्टर_gate(शून्य, "cml1", "pll_e", 0, clk_base + PLLE_AUX,
				1, 0, &pll_e_lock);
	clk_रेजिस्टर_clkdev(clk, "cml1", शून्य);
	clks[TEGRA124_CLK_CML1] = clk;

	क्रम (i = 0; i < ARRAY_SIZE(tegra124_periph); i++) अणु
		काष्ठा tegra_periph_init_data *init = &tegra124_periph[i];
		काष्ठा clk **clkp;

		clkp = tegra_lookup_dt_id(init->clk_id, tegra124_clks);
		अगर (!clkp) अणु
			pr_warn("clock %u not found\n", init->clk_id);
			जारी;
		पूर्ण

		clk = tegra_clk_रेजिस्टर_periph_data(clk_base, init);
		*clkp = clk;
	पूर्ण

	tegra_periph_clk_init(clk_base, pmc_base, tegra124_clks, &pll_p_params);
पूर्ण

अटल व्योम __init tegra124_pll_init(व्योम __iomem *clk_base,
				     व्योम __iomem *pmc)
अणु
	काष्ठा clk *clk;

	/* PLLC */
	clk = tegra_clk_रेजिस्टर_pllxc("pll_c", "pll_ref", clk_base,
			pmc, 0, &pll_c_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c", शून्य);
	clks[TEGRA124_CLK_PLL_C] = clk;

	/* PLLC_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_c_out1_div", "pll_c",
			clk_base + PLLC_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
			8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_c_out1", "pll_c_out1_div",
				clk_base + PLLC_OUT, 1, 0,
				CLK_SET_RATE_PARENT, 0, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c_out1", शून्य);
	clks[TEGRA124_CLK_PLL_C_OUT1] = clk;

	/* PLLC_UD */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_c_ud", "pll_c",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_c_ud", शून्य);
	clks[TEGRA124_CLK_PLL_C_UD] = clk;

	/* PLLC2 */
	clk = tegra_clk_रेजिस्टर_pllc("pll_c2", "pll_ref", clk_base, pmc, 0,
			     &pll_c2_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c2", शून्य);
	clks[TEGRA124_CLK_PLL_C2] = clk;

	/* PLLC3 */
	clk = tegra_clk_रेजिस्टर_pllc("pll_c3", "pll_ref", clk_base, pmc, 0,
			     &pll_c3_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c3", शून्य);
	clks[TEGRA124_CLK_PLL_C3] = clk;

	/* PLLM */
	clk = tegra_clk_रेजिस्टर_pllm("pll_m", "pll_ref", clk_base, pmc,
			     CLK_SET_RATE_GATE, &pll_m_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_m", शून्य);
	clks[TEGRA124_CLK_PLL_M] = clk;

	/* PLLM_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_m_out1_div", "pll_m",
				clk_base + PLLM_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_m_out1", "pll_m_out1_div",
				clk_base + PLLM_OUT, 1, 0,
				CLK_SET_RATE_PARENT, 0, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_m_out1", शून्य);
	clks[TEGRA124_CLK_PLL_M_OUT1] = clk;

	/* PLLM_UD */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_m_ud", "pll_m",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_m_ud", शून्य);
	clks[TEGRA124_CLK_PLL_M_UD] = clk;

	/* PLLU */
	clk = tegra_clk_रेजिस्टर_pllu_tegra114("pll_u", "pll_ref", clk_base, 0,
					       &pll_u_params, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u", शून्य);
	clks[TEGRA124_CLK_PLL_U] = clk;

	/* PLLU_480M */
	clk = clk_रेजिस्टर_gate(शून्य, "pll_u_480M", "pll_u",
				CLK_SET_RATE_PARENT, clk_base + PLLU_BASE,
				22, 0, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u_480M", शून्य);
	clks[TEGRA124_CLK_PLL_U_480M] = clk;

	/* PLLU_60M */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_u_60M", "pll_u",
					CLK_SET_RATE_PARENT, 1, 8);
	clk_रेजिस्टर_clkdev(clk, "pll_u_60M", शून्य);
	clks[TEGRA124_CLK_PLL_U_60M] = clk;

	/* PLLU_48M */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_u_48M", "pll_u",
					CLK_SET_RATE_PARENT, 1, 10);
	clk_रेजिस्टर_clkdev(clk, "pll_u_48M", शून्य);
	clks[TEGRA124_CLK_PLL_U_48M] = clk;

	/* PLLU_12M */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_u_12M", "pll_u",
					CLK_SET_RATE_PARENT, 1, 40);
	clk_रेजिस्टर_clkdev(clk, "pll_u_12M", शून्य);
	clks[TEGRA124_CLK_PLL_U_12M] = clk;

	/* PLLD */
	clk = tegra_clk_रेजिस्टर_pll("pll_d", "pll_ref", clk_base, pmc, 0,
			    &pll_d_params, &pll_d_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_d", शून्य);
	clks[TEGRA124_CLK_PLL_D] = clk;

	/* PLLD_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d_out0", "pll_d",
					CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll_d_out0", शून्य);
	clks[TEGRA124_CLK_PLL_D_OUT0] = clk;

	/* PLLRE */
	clk = tegra_clk_रेजिस्टर_pllre("pll_re_vco", "pll_ref", clk_base, pmc,
			     0, &pll_re_vco_params, &pll_re_lock, pll_ref_freq);
	clk_रेजिस्टर_clkdev(clk, "pll_re_vco", शून्य);
	clks[TEGRA124_CLK_PLL_RE_VCO] = clk;

	clk = clk_रेजिस्टर_भागider_table(शून्य, "pll_re_out", "pll_re_vco", 0,
					 clk_base + PLLRE_BASE, 16, 4, 0,
					 pll_re_भाग_प्रकारable, &pll_re_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_re_out", शून्य);
	clks[TEGRA124_CLK_PLL_RE_OUT] = clk;

	/* PLLE */
	clk = tegra_clk_रेजिस्टर_plle_tegra114("pll_e", "pll_ref",
				      clk_base, 0, &pll_e_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_e", शून्य);
	clks[TEGRA124_CLK_PLL_E] = clk;

	/* PLLC4 */
	clk = tegra_clk_रेजिस्टर_pllss("pll_c4", "pll_ref", clk_base, 0,
					&pll_c4_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c4", शून्य);
	clks[TEGRA124_CLK_PLL_C4] = clk;

	/* PLLDP */
	clk = tegra_clk_रेजिस्टर_pllss("pll_dp", "pll_ref", clk_base, 0,
					&pll_dp_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_dp", शून्य);
	clks[TEGRA124_CLK_PLL_DP] = clk;

	/* PLLD2 */
	clk = tegra_clk_रेजिस्टर_pllss("pll_d2", "pll_ref", clk_base, 0,
					&tegra124_pll_d2_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_d2", शून्य);
	clks[TEGRA124_CLK_PLL_D2] = clk;

	/* PLLD2_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d2_out0", "pll_d2",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_d2_out0", शून्य);
	clks[TEGRA124_CLK_PLL_D2_OUT0] = clk;

पूर्ण

/* Tegra124 CPU घड़ी and reset control functions */
अटल व्योम tegra124_रुको_cpu_in_reset(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	करो अणु
		reg = पढ़ोl(clk_base + CLK_RST_CONTROLLER_CPU_CMPLX_STATUS);
		cpu_relax();
	पूर्ण जबतक (!(reg & (1 << cpu)));  /* check CPU been reset or not */
पूर्ण

अटल व्योम tegra124_disable_cpu_घड़ी(u32 cpu)
अणु
	/* flow controller would take care in the घातer sequence. */
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम tegra124_cpu_घड़ी_suspend(व्योम)
अणु
	/* चयन coresite to clk_m, save off original source */
	tegra124_cpu_clk_sctx.clk_csite_src =
				पढ़ोl(clk_base + CLK_SOURCE_CSITE);
	ग_लिखोl(3 << 30, clk_base + CLK_SOURCE_CSITE);

	tegra124_cpu_clk_sctx.cclkg_burst =
				पढ़ोl(clk_base + CCLKG_BURST_POLICY);
	tegra124_cpu_clk_sctx.cclkg_भागider =
				पढ़ोl(clk_base + CCLKG_BURST_POLICY + 4);
पूर्ण

अटल व्योम tegra124_cpu_घड़ी_resume(व्योम)
अणु
	ग_लिखोl(tegra124_cpu_clk_sctx.clk_csite_src,
				clk_base + CLK_SOURCE_CSITE);

	ग_लिखोl(tegra124_cpu_clk_sctx.cclkg_burst,
					clk_base + CCLKG_BURST_POLICY);
	ग_लिखोl(tegra124_cpu_clk_sctx.cclkg_भागider,
					clk_base + CCLKG_BURST_POLICY + 4);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा tegra_cpu_car_ops tegra124_cpu_car_ops = अणु
	.रुको_क्रम_reset	= tegra124_रुको_cpu_in_reset,
	.disable_घड़ी	= tegra124_disable_cpu_घड़ी,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= tegra124_cpu_घड़ी_suspend,
	.resume		= tegra124_cpu_घड़ी_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा of_device_id pmc_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra124-pmc" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_init_table common_init_table[] __initdata = अणु
	अणु TEGRA124_CLK_UARTA, TEGRA124_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA124_CLK_UARTB, TEGRA124_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA124_CLK_UARTC, TEGRA124_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA124_CLK_UARTD, TEGRA124_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA124_CLK_PLL_A, TEGRA124_CLK_CLK_MAX, 282240000, 0 पूर्ण,
	अणु TEGRA124_CLK_PLL_A_OUT0, TEGRA124_CLK_CLK_MAX, 11289600, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S0, TEGRA124_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S1, TEGRA124_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S2, TEGRA124_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S3, TEGRA124_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S4, TEGRA124_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA124_CLK_VDE, TEGRA124_CLK_PLL_C3, 600000000, 0 पूर्ण,
	अणु TEGRA124_CLK_HOST1X, TEGRA124_CLK_PLL_P, 136000000, 1 पूर्ण,
	अणु TEGRA124_CLK_DSIALP, TEGRA124_CLK_PLL_P, 68000000, 0 पूर्ण,
	अणु TEGRA124_CLK_DSIBLP, TEGRA124_CLK_PLL_P, 68000000, 0 पूर्ण,
	अणु TEGRA124_CLK_SCLK, TEGRA124_CLK_PLL_P_OUT2, 102000000, 0 पूर्ण,
	अणु TEGRA124_CLK_DFLL_SOC, TEGRA124_CLK_PLL_P, 51000000, 1 पूर्ण,
	अणु TEGRA124_CLK_DFLL_REF, TEGRA124_CLK_PLL_P, 51000000, 1 पूर्ण,
	अणु TEGRA124_CLK_PLL_C, TEGRA124_CLK_CLK_MAX, 768000000, 0 पूर्ण,
	अणु TEGRA124_CLK_PLL_C_OUT1, TEGRA124_CLK_CLK_MAX, 100000000, 0 पूर्ण,
	अणु TEGRA124_CLK_SBC4, TEGRA124_CLK_PLL_P, 12000000, 1 पूर्ण,
	अणु TEGRA124_CLK_TSEC, TEGRA124_CLK_PLL_C3, 0, 0 पूर्ण,
	अणु TEGRA124_CLK_MSENC, TEGRA124_CLK_PLL_C3, 0, 0 पूर्ण,
	अणु TEGRA124_CLK_PLL_RE_VCO, TEGRA124_CLK_CLK_MAX, 672000000, 0 पूर्ण,
	अणु TEGRA124_CLK_XUSB_SS_SRC, TEGRA124_CLK_PLL_U_480M, 120000000, 0 पूर्ण,
	अणु TEGRA124_CLK_XUSB_FS_SRC, TEGRA124_CLK_PLL_U_48M, 48000000, 0 पूर्ण,
	अणु TEGRA124_CLK_XUSB_HS_SRC, TEGRA124_CLK_PLL_U_60M, 60000000, 0 पूर्ण,
	अणु TEGRA124_CLK_XUSB_FALCON_SRC, TEGRA124_CLK_PLL_RE_OUT, 224000000, 0 पूर्ण,
	अणु TEGRA124_CLK_XUSB_HOST_SRC, TEGRA124_CLK_PLL_RE_OUT, 112000000, 0 पूर्ण,
	अणु TEGRA124_CLK_SATA, TEGRA124_CLK_PLL_P, 104000000, 0 पूर्ण,
	अणु TEGRA124_CLK_SATA_OOB, TEGRA124_CLK_PLL_P, 204000000, 0 पूर्ण,
	अणु TEGRA124_CLK_MSELECT, TEGRA124_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA124_CLK_CSITE, TEGRA124_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA124_CLK_TSENSOR, TEGRA124_CLK_CLK_M, 400000, 0 पूर्ण,
	अणु TEGRA124_CLK_VIC03, TEGRA124_CLK_PLL_C3, 0, 0 पूर्ण,
	अणु TEGRA124_CLK_SPDIF_IN_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S0_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S1_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S2_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S3_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA124_CLK_I2S4_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA124_CLK_VIMCLK_SYNC, TEGRA124_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	/* must be the last entry */
	अणु TEGRA124_CLK_CLK_MAX, TEGRA124_CLK_CLK_MAX, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_init_table tegra124_init_table[] __initdata = अणु
	अणु TEGRA124_CLK_SOC_THERM, TEGRA124_CLK_PLL_P, 51000000, 0 पूर्ण,
	अणु TEGRA124_CLK_CCLK_G, TEGRA124_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA124_CLK_HDA, TEGRA124_CLK_PLL_P, 102000000, 0 पूर्ण,
	अणु TEGRA124_CLK_HDA2CODEC_2X, TEGRA124_CLK_PLL_P, 48000000, 0 पूर्ण,
	/* must be the last entry */
	अणु TEGRA124_CLK_CLK_MAX, TEGRA124_CLK_CLK_MAX, 0, 0 पूर्ण,
पूर्ण;

/* Tegra132 requires the SOC_THERM घड़ी to reमुख्य active */
अटल काष्ठा tegra_clk_init_table tegra132_init_table[] __initdata = अणु
	अणु TEGRA124_CLK_SOC_THERM, TEGRA124_CLK_PLL_P, 51000000, 1 पूर्ण,
	/* must be the last entry */
	अणु TEGRA124_CLK_CLK_MAX, TEGRA124_CLK_CLK_MAX, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_audio_clk_info tegra124_audio_plls[] = अणु
	अणु "pll_a", &pll_a_params, tegra_clk_pll_a, "pll_p_out1" पूर्ण,
पूर्ण;

/**
 * tegra124_घड़ी_apply_init_table - initialize घड़ीs on Tegra124 SoCs
 *
 * Program an initial घड़ी rate and enable or disable घड़ीs needed
 * by the rest of the kernel, क्रम Tegra124 SoCs.  It is पूर्णांकended to be
 * called by assigning a poपूर्णांकer to it to tegra_clk_apply_init_table -
 * this will be called as an arch_initcall.  No वापस value.
 */
अटल व्योम __init tegra124_घड़ी_apply_init_table(व्योम)
अणु
	tegra_init_from_table(common_init_table, clks, TEGRA124_CLK_CLK_MAX);
	tegra_init_from_table(tegra124_init_table, clks, TEGRA124_CLK_CLK_MAX);
पूर्ण

/**
 * tegra124_car_barrier - रुको क्रम pending ग_लिखोs to the CAR to complete
 *
 * Wait क्रम any outstanding ग_लिखोs to the CAR MMIO space from this CPU
 * to complete beक्रमe continuing execution.  No वापस value.
 */
अटल व्योम tegra124_car_barrier(व्योम)
अणु
	पढ़ोl_relaxed(clk_base + RST_DFLL_DVCO);
पूर्ण

/**
 * tegra124_घड़ी_निश्चित_dfll_dvco_reset - निश्चित the DFLL's DVCO reset
 *
 * Assert the reset line of the DFLL's DVCO.  No वापस value.
 */
अटल व्योम tegra124_घड़ी_निश्चित_dfll_dvco_reset(व्योम)
अणु
	u32 v;

	v = पढ़ोl_relaxed(clk_base + RST_DFLL_DVCO);
	v |= (1 << DVFS_DFLL_RESET_SHIFT);
	ग_लिखोl_relaxed(v, clk_base + RST_DFLL_DVCO);
	tegra124_car_barrier();
पूर्ण

/**
 * tegra124_घड़ी_deनिश्चित_dfll_dvco_reset - deनिश्चित the DFLL's DVCO reset
 *
 * Deनिश्चित the reset line of the DFLL's DVCO, allowing the DVCO to
 * operate.  No वापस value.
 */
अटल व्योम tegra124_घड़ी_deनिश्चित_dfll_dvco_reset(व्योम)
अणु
	u32 v;

	v = पढ़ोl_relaxed(clk_base + RST_DFLL_DVCO);
	v &= ~(1 << DVFS_DFLL_RESET_SHIFT);
	ग_लिखोl_relaxed(v, clk_base + RST_DFLL_DVCO);
	tegra124_car_barrier();
पूर्ण

अटल पूर्णांक tegra124_reset_निश्चित(अचिन्हित दीर्घ id)
अणु
	अगर (id == TEGRA124_RST_DFLL_DVCO)
		tegra124_घड़ी_निश्चित_dfll_dvco_reset();
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_reset_deनिश्चित(अचिन्हित दीर्घ id)
अणु
	अगर (id == TEGRA124_RST_DFLL_DVCO)
		tegra124_घड़ी_deनिश्चित_dfll_dvco_reset();
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * tegra132_घड़ी_apply_init_table - initialize घड़ीs on Tegra132 SoCs
 *
 * Program an initial घड़ी rate and enable or disable घड़ीs needed
 * by the rest of the kernel, क्रम Tegra132 SoCs.  It is पूर्णांकended to be
 * called by assigning a poपूर्णांकer to it to tegra_clk_apply_init_table -
 * this will be called as an arch_initcall.  No वापस value.
 */
अटल व्योम __init tegra132_घड़ी_apply_init_table(व्योम)
अणु
	tegra_init_from_table(common_init_table, clks, TEGRA124_CLK_CLK_MAX);
	tegra_init_from_table(tegra132_init_table, clks, TEGRA124_CLK_CLK_MAX);
पूर्ण

/**
 * tegra124_132_घड़ी_init_pre - घड़ी initialization preamble क्रम T124/T132
 * @np: काष्ठा device_node * of the DT node क्रम the SoC CAR IP block
 *
 * Register most of the घड़ीs controlled by the CAR IP block.
 * Everything in this function should be common to Tegra124 and Tegra132.
 * No वापस value.
 */
अटल व्योम __init tegra124_132_घड़ी_init_pre(काष्ठा device_node *np)
अणु
	काष्ठा device_node *node;
	u32 plld_base;

	clk_base = of_iomap(np, 0);
	अगर (!clk_base) अणु
		pr_err("ioremap tegra124/tegra132 CAR failed\n");
		वापस;
	पूर्ण

	node = of_find_matching_node(शून्य, pmc_match);
	अगर (!node) अणु
		pr_err("Failed to find pmc node\n");
		WARN_ON(1);
		वापस;
	पूर्ण

	pmc_base = of_iomap(node, 0);
	अगर (!pmc_base) अणु
		pr_err("Can't map pmc registers\n");
		WARN_ON(1);
		वापस;
	पूर्ण

	clks = tegra_clk_init(clk_base, TEGRA124_CLK_CLK_MAX,
			      TEGRA124_CAR_BANK_COUNT);
	अगर (!clks)
		वापस;

	अगर (tegra_osc_clk_init(clk_base, tegra124_clks, tegra124_input_freq,
			       ARRAY_SIZE(tegra124_input_freq), 1, &osc_freq,
			       &pll_ref_freq) < 0)
		वापस;

	tegra_fixed_clk_init(tegra124_clks);
	tegra124_pll_init(clk_base, pmc_base);
	tegra124_periph_clk_init(clk_base, pmc_base);
	tegra_audio_clk_init(clk_base, pmc_base, tegra124_clks,
			     tegra124_audio_plls,
			     ARRAY_SIZE(tegra124_audio_plls), 24576000);

	/* For Tegra124 & Tegra132, PLLD is the only source क्रम DSIA & DSIB */
	plld_base = पढ़ोl(clk_base + PLLD_BASE);
	plld_base &= ~BIT(25);
	ग_लिखोl(plld_base, clk_base + PLLD_BASE);
पूर्ण

अटल काष्ठा clk *tegra124_clk_src_onecell_get(काष्ठा of_phandle_args *clkspec,
						व्योम *data)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk *clk;

	clk = of_clk_src_onecell_get(clkspec, data);
	अगर (IS_ERR(clk))
		वापस clk;

	hw = __clk_get_hw(clk);

	अगर (clkspec->args[0] == TEGRA124_CLK_EMC) अणु
		अगर (!tegra124_clk_emc_driver_available(hw))
			वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	वापस clk;
पूर्ण

/**
 * tegra124_132_घड़ी_init_post - घड़ी initialization postamble क्रम T124/T132
 * @np: काष्ठा device_node * of the DT node क्रम the SoC CAR IP block
 *
 * Register most of the घड़ीs controlled by the CAR IP block.
 * Everything in this function should be common to Tegra124
 * and Tegra132.  This function must be called after
 * tegra124_132_घड़ी_init_pre(), otherwise clk_base will not be set.
 * No वापस value.
 */
अटल व्योम __init tegra124_132_घड़ी_init_post(काष्ठा device_node *np)
अणु
	tegra_super_clk_gen4_init(clk_base, pmc_base, tegra124_clks,
				  &pll_x_params);
	tegra_init_special_resets(1, tegra124_reset_निश्चित,
				  tegra124_reset_deनिश्चित);
	tegra_add_of_provider(np, tegra124_clk_src_onecell_get);

	clks[TEGRA124_CLK_EMC] = tegra124_clk_रेजिस्टर_emc(clk_base, np,
							   &emc_lock);

	tegra_रेजिस्टर_devclks(devclks, ARRAY_SIZE(devclks));

	tegra_cpu_car_ops = &tegra124_cpu_car_ops;
पूर्ण

/**
 * tegra124_घड़ी_init - Tegra124-specअगरic घड़ी initialization
 * @np: काष्ठा device_node * of the DT node क्रम the SoC CAR IP block
 *
 * Register most SoC घड़ीs क्रम the Tegra124 प्रणाली-on-chip.  Most of
 * this code is shared between the Tegra124 and Tegra132 SoCs,
 * although some of the initial घड़ी settings and CPU घड़ीs dअगरfer.
 * Intended to be called by the OF init code when a DT node with the
 * "nvidia,tegra124-car" string is encountered, and declared with
 * CLK_OF_DECLARE.  No वापस value.
 */
अटल व्योम __init tegra124_घड़ी_init(काष्ठा device_node *np)
अणु
	tegra124_132_घड़ी_init_pre(np);
	tegra_clk_apply_init_table = tegra124_घड़ी_apply_init_table;
	tegra124_132_घड़ी_init_post(np);
पूर्ण

/**
 * tegra132_घड़ी_init - Tegra132-specअगरic घड़ी initialization
 * @np: काष्ठा device_node * of the DT node क्रम the SoC CAR IP block
 *
 * Register most SoC घड़ीs क्रम the Tegra132 प्रणाली-on-chip.  Most of
 * this code is shared between the Tegra124 and Tegra132 SoCs,
 * although some of the initial घड़ी settings and CPU घड़ीs dअगरfer.
 * Intended to be called by the OF init code when a DT node with the
 * "nvidia,tegra132-car" string is encountered, and declared with
 * CLK_OF_DECLARE.  No वापस value.
 */
अटल व्योम __init tegra132_घड़ी_init(काष्ठा device_node *np)
अणु
	tegra124_132_घड़ी_init_pre(np);

	/*
	 * On Tegra132, these घड़ीs are controlled by the
	 * CLUSTER_घड़ीs IP block, located in the CPU complex
	 */
	tegra124_clks[tegra_clk_cclk_g].present = false;
	tegra124_clks[tegra_clk_cclk_lp].present = false;
	tegra124_clks[tegra_clk_pll_x].present = false;
	tegra124_clks[tegra_clk_pll_x_out0].present = false;

	tegra_clk_apply_init_table = tegra132_घड़ी_apply_init_table;
	tegra124_132_घड़ी_init_post(np);
पूर्ण
CLK_OF_DECLARE(tegra124, "nvidia,tegra124-car", tegra124_घड़ी_init);
CLK_OF_DECLARE(tegra132, "nvidia,tegra132-car", tegra132_घड़ी_init);
