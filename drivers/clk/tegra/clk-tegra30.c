<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/tegra.h>

#समावेश <soc/tegra/pmc.h>

#समावेश <dt-bindings/घड़ी/tegra30-car.h>

#समावेश "clk.h"
#समावेश "clk-id.h"

#घोषणा OSC_CTRL			0x50
#घोषणा OSC_CTRL_OSC_FREQ_MASK		(0xF<<28)
#घोषणा OSC_CTRL_OSC_FREQ_13MHZ		(0X0<<28)
#घोषणा OSC_CTRL_OSC_FREQ_19_2MHZ	(0X4<<28)
#घोषणा OSC_CTRL_OSC_FREQ_12MHZ		(0X8<<28)
#घोषणा OSC_CTRL_OSC_FREQ_26MHZ		(0XC<<28)
#घोषणा OSC_CTRL_OSC_FREQ_16_8MHZ	(0X1<<28)
#घोषणा OSC_CTRL_OSC_FREQ_38_4MHZ	(0X5<<28)
#घोषणा OSC_CTRL_OSC_FREQ_48MHZ		(0X9<<28)
#घोषणा OSC_CTRL_MASK			(0x3f2 | OSC_CTRL_OSC_FREQ_MASK)

#घोषणा OSC_CTRL_PLL_REF_DIV_MASK	(3<<26)
#घोषणा OSC_CTRL_PLL_REF_DIV_1		(0<<26)
#घोषणा OSC_CTRL_PLL_REF_DIV_2		(1<<26)
#घोषणा OSC_CTRL_PLL_REF_DIV_4		(2<<26)

#घोषणा OSC_FREQ_DET			0x58
#घोषणा OSC_FREQ_DET_TRIG		BIT(31)

#घोषणा OSC_FREQ_DET_STATUS		0x5c
#घोषणा OSC_FREQ_DET_BUSY		BIT(31)
#घोषणा OSC_FREQ_DET_CNT_MASK		0xffff

#घोषणा CCLKG_BURST_POLICY 0x368
#घोषणा SUPER_CCLKG_DIVIDER 0x36c
#घोषणा CCLKLP_BURST_POLICY 0x370
#घोषणा SUPER_CCLKLP_DIVIDER 0x374
#घोषणा SCLK_BURST_POLICY 0x028
#घोषणा SUPER_SCLK_DIVIDER 0x02c

#घोषणा SYSTEM_CLK_RATE 0x030

#घोषणा TEGRA30_CLK_PERIPH_BANKS	5

#घोषणा PLLC_BASE 0x80
#घोषणा PLLC_MISC 0x8c
#घोषणा PLLM_BASE 0x90
#घोषणा PLLM_MISC 0x9c
#घोषणा PLLP_BASE 0xa0
#घोषणा PLLP_MISC 0xac
#घोषणा PLLX_BASE 0xe0
#घोषणा PLLX_MISC 0xe4
#घोषणा PLLD_BASE 0xd0
#घोषणा PLLD_MISC 0xdc
#घोषणा PLLD2_BASE 0x4b8
#घोषणा PLLD2_MISC 0x4bc
#घोषणा PLLE_BASE 0xe8
#घोषणा PLLE_MISC 0xec
#घोषणा PLLA_BASE 0xb0
#घोषणा PLLA_MISC 0xbc
#घोषणा PLLU_BASE 0xc0
#घोषणा PLLU_MISC 0xcc

#घोषणा PLL_MISC_LOCK_ENABLE 18
#घोषणा PLLDU_MISC_LOCK_ENABLE 22
#घोषणा PLLE_MISC_LOCK_ENABLE 9

#घोषणा PLL_BASE_LOCK BIT(27)
#घोषणा PLLE_MISC_LOCK BIT(11)

#घोषणा PLLE_AUX 0x48c
#घोषणा PLLC_OUT 0x84
#घोषणा PLLM_OUT 0x94
#घोषणा PLLP_OUTA 0xa4
#घोषणा PLLP_OUTB 0xa8
#घोषणा PLLA_OUT 0xb4

#घोषणा AUDIO_SYNC_CLK_I2S0 0x4a0
#घोषणा AUDIO_SYNC_CLK_I2S1 0x4a4
#घोषणा AUDIO_SYNC_CLK_I2S2 0x4a8
#घोषणा AUDIO_SYNC_CLK_I2S3 0x4ac
#घोषणा AUDIO_SYNC_CLK_I2S4 0x4b0
#घोषणा AUDIO_SYNC_CLK_SPDIF 0x4b4

#घोषणा CLK_SOURCE_SPDIF_OUT 0x108
#घोषणा CLK_SOURCE_PWM 0x110
#घोषणा CLK_SOURCE_D_AUDIO 0x3d0
#घोषणा CLK_SOURCE_DAM0 0x3d8
#घोषणा CLK_SOURCE_DAM1 0x3dc
#घोषणा CLK_SOURCE_DAM2 0x3e0
#घोषणा CLK_SOURCE_3D2 0x3b0
#घोषणा CLK_SOURCE_2D 0x15c
#घोषणा CLK_SOURCE_HDMI 0x18c
#घोषणा CLK_SOURCE_DSIB 0xd0
#घोषणा CLK_SOURCE_SE 0x42c
#घोषणा CLK_SOURCE_EMC 0x19c

#घोषणा AUDIO_SYNC_DOUBLER 0x49c

/* Tegra CPU घड़ी and reset control regs */
#घोषणा TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX		0x4c
#घोषणा TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_SET	0x340
#घोषणा TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_CLR	0x344
#घोषणा TEGRA30_CLK_RST_CONTROLLER_CLK_CPU_CMPLX_CLR	0x34c
#घोषणा TEGRA30_CLK_RST_CONTROLLER_CPU_CMPLX_STATUS	0x470

#घोषणा CPU_CLOCK(cpu)	(0x1 << (8 + cpu))
#घोषणा CPU_RESET(cpu)	(0x1111ul << (cpu))

#घोषणा CLK_RESET_CCLK_BURST	0x20
#घोषणा CLK_RESET_CCLK_DIVIDER	0x24
#घोषणा CLK_RESET_PLLX_BASE	0xe0
#घोषणा CLK_RESET_PLLX_MISC	0xe4

#घोषणा CLK_RESET_SOURCE_CSITE	0x1d4

#घोषणा CLK_RESET_CCLK_BURST_POLICY_SHIFT	28
#घोषणा CLK_RESET_CCLK_RUN_POLICY_SHIFT		4
#घोषणा CLK_RESET_CCLK_IDLE_POLICY_SHIFT	0
#घोषणा CLK_RESET_CCLK_IDLE_POLICY		1
#घोषणा CLK_RESET_CCLK_RUN_POLICY		2
#घोषणा CLK_RESET_CCLK_BURST_POLICY_PLLX	8

/* PLLM override रेजिस्टरs */
#घोषणा PMC_PLLM_WB0_OVERRIDE 0x1dc

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा cpu_clk_suspend_context अणु
	u32 pllx_misc;
	u32 pllx_base;

	u32 cpu_burst;
	u32 clk_csite_src;
	u32 cclk_भागider;
पूर्ण tegra30_cpu_clk_sctx;
#पूर्ण_अगर

अटल व्योम __iomem *clk_base;
अटल व्योम __iomem *pmc_base;
अटल अचिन्हित दीर्घ input_freq;

अटल DEFINE_SPINLOCK(cml_lock);
अटल DEFINE_SPINLOCK(pll_d_lock);

#घोषणा TEGRA_INIT_DATA_MUX(_name, _parents, _offset,	\
			    _clk_num, _gate_flags, _clk_id)	\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			30, 2, 0, 0, 8, 1, TEGRA_DIVIDER_ROUND_UP, \
			_clk_num, _gate_flags, _clk_id)

#घोषणा TEGRA_INIT_DATA_MUX8(_name, _parents, _offset, \
			     _clk_num, _gate_flags, _clk_id)	\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			29, 3, 0, 0, 8, 1, TEGRA_DIVIDER_ROUND_UP, \
			_clk_num, _gate_flags, _clk_id)

#घोषणा TEGRA_INIT_DATA_INT(_name, _parents, _offset,	\
			    _clk_num, _gate_flags, _clk_id)	\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			30, 2, 0, 0, 8, 1, TEGRA_DIVIDER_INT |		\
			TEGRA_DIVIDER_ROUND_UP, _clk_num,	\
			_gate_flags, _clk_id)

#घोषणा TEGRA_INIT_DATA_NODIV(_name, _parents, _offset, \
			      _mux_shअगरt, _mux_width, _clk_num, \
			      _gate_flags, _clk_id)			\
	TEGRA_INIT_DATA(_name, शून्य, शून्य, _parents, _offset,	\
			_mux_shअगरt, _mux_width, 0, 0, 0, 0, 0,\
			_clk_num, _gate_flags,	\
			_clk_id)

अटल काष्ठा clk **clks;

अटल काष्ठा tegra_clk_pll_freq_table pll_c_freq_table[] = अणु
	अणु 12000000, 1040000000, 520,  6, 1, 8 पूर्ण,
	अणु 13000000, 1040000000, 480,  6, 1, 8 पूर्ण,
	अणु 16800000, 1040000000, 495,  8, 1, 8 पूर्ण, /* actual: 1039.5 MHz */
	अणु 19200000, 1040000000, 325,  6, 1, 6 पूर्ण,
	अणु 26000000, 1040000000, 520, 13, 1, 8 पूर्ण,
	अणु 12000000,  832000000, 416,  6, 1, 8 पूर्ण,
	अणु 13000000,  832000000, 832, 13, 1, 8 पूर्ण,
	अणु 16800000,  832000000, 396,  8, 1, 8 पूर्ण, /* actual: 831.6 MHz */
	अणु 19200000,  832000000, 260,  6, 1, 8 पूर्ण,
	अणु 26000000,  832000000, 416, 13, 1, 8 पूर्ण,
	अणु 12000000,  624000000, 624, 12, 1, 8 पूर्ण,
	अणु 13000000,  624000000, 624, 13, 1, 8 पूर्ण,
	अणु 16800000,  600000000, 520, 14, 1, 8 पूर्ण,
	अणु 19200000,  624000000, 520, 16, 1, 8 पूर्ण,
	अणु 26000000,  624000000, 624, 26, 1, 8 पूर्ण,
	अणु 12000000,  600000000, 600, 12, 1, 8 पूर्ण,
	अणु 13000000,  600000000, 600, 13, 1, 8 पूर्ण,
	अणु 16800000,  600000000, 500, 14, 1, 8 पूर्ण,
	अणु 19200000,  600000000, 375, 12, 1, 6 पूर्ण,
	अणु 26000000,  600000000, 600, 26, 1, 8 पूर्ण,
	अणु 12000000,  520000000, 520, 12, 1, 8 पूर्ण,
	अणु 13000000,  520000000, 520, 13, 1, 8 पूर्ण,
	अणु 16800000,  520000000, 495, 16, 1, 8 पूर्ण, /* actual: 519.75 MHz */
	अणु 19200000,  520000000, 325, 12, 1, 6 पूर्ण,
	अणु 26000000,  520000000, 520, 26, 1, 8 पूर्ण,
	अणु 12000000,  416000000, 416, 12, 1, 8 पूर्ण,
	अणु 13000000,  416000000, 416, 13, 1, 8 पूर्ण,
	अणु 16800000,  416000000, 396, 16, 1, 8 पूर्ण, /* actual: 415.8 MHz */
	अणु 19200000,  416000000, 260, 12, 1, 6 पूर्ण,
	अणु 26000000,  416000000, 416, 26, 1, 8 पूर्ण,
	अणु        0,          0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_m_freq_table[] = अणु
	अणु 12000000, 666000000, 666, 12, 1, 8 पूर्ण,
	अणु 13000000, 666000000, 666, 13, 1, 8 पूर्ण,
	अणु 16800000, 666000000, 555, 14, 1, 8 पूर्ण,
	अणु 19200000, 666000000, 555, 16, 1, 8 पूर्ण,
	अणु 26000000, 666000000, 666, 26, 1, 8 पूर्ण,
	अणु 12000000, 600000000, 600, 12, 1, 8 पूर्ण,
	अणु 13000000, 600000000, 600, 13, 1, 8 पूर्ण,
	अणु 16800000, 600000000, 500, 14, 1, 8 पूर्ण,
	अणु 19200000, 600000000, 375, 12, 1, 6 पूर्ण,
	अणु 26000000, 600000000, 600, 26, 1, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_p_freq_table[] = अणु
	अणु 12000000, 216000000, 432, 12, 2, 8 पूर्ण,
	अणु 13000000, 216000000, 432, 13, 2, 8 पूर्ण,
	अणु 16800000, 216000000, 360, 14, 2, 8 पूर्ण,
	अणु 19200000, 216000000, 360, 16, 2, 8 पूर्ण,
	अणु 26000000, 216000000, 432, 26, 2, 8 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_a_freq_table[] = अणु
	अणु  9600000, 564480000, 294,  5, 1, 4 पूर्ण,
	अणु  9600000, 552960000, 288,  5, 1, 4 पूर्ण,
	अणु  9600000,  24000000,   5,  2, 1, 1 पूर्ण,
	अणु 28800000,  56448000,  49, 25, 1, 1 पूर्ण,
	अणु 28800000,  73728000,  64, 25, 1, 1 पूर्ण,
	अणु 28800000,  24000000,   5,  6, 1, 1 पूर्ण,
	अणु        0,         0,   0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_d_freq_table[] = अणु
	अणु 12000000,  216000000,  216, 12, 1,  4 पूर्ण,
	अणु 13000000,  216000000,  216, 13, 1,  4 पूर्ण,
	अणु 16800000,  216000000,  180, 14, 1,  4 पूर्ण,
	अणु 19200000,  216000000,  180, 16, 1,  4 पूर्ण,
	अणु 26000000,  216000000,  216, 26, 1,  4 पूर्ण,
	अणु 12000000,  594000000,  594, 12, 1,  8 पूर्ण,
	अणु 13000000,  594000000,  594, 13, 1,  8 पूर्ण,
	अणु 16800000,  594000000,  495, 14, 1,  8 पूर्ण,
	अणु 19200000,  594000000,  495, 16, 1,  8 पूर्ण,
	अणु 26000000,  594000000,  594, 26, 1,  8 पूर्ण,
	अणु 12000000, 1000000000, 1000, 12, 1, 12 पूर्ण,
	अणु 13000000, 1000000000, 1000, 13, 1, 12 पूर्ण,
	अणु 19200000, 1000000000,  625, 12, 1,  8 पूर्ण,
	अणु 26000000, 1000000000, 1000, 26, 1, 12 पूर्ण,
	अणु        0,          0,    0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map pllu_p[] = अणु
	अणु .pभाग = 1, .hw_val = 1 पूर्ण,
	अणु .pभाग = 2, .hw_val = 0 पूर्ण,
	अणु .pभाग = 0, .hw_val = 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_u_freq_table[] = अणु
	अणु 12000000, 480000000, 960, 12, 2, 12 पूर्ण,
	अणु 13000000, 480000000, 960, 13, 2, 12 पूर्ण,
	अणु 16800000, 480000000, 400,  7, 2,  5 पूर्ण,
	अणु 19200000, 480000000, 200,  4, 2,  3 पूर्ण,
	अणु 26000000, 480000000, 960, 26, 2, 12 पूर्ण,
	अणु        0,         0,   0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_x_freq_table[] = अणु
	/* 1.7 GHz */
	अणु 12000000, 1700000000, 850,   6, 1, 8 पूर्ण,
	अणु 13000000, 1700000000, 915,   7, 1, 8 पूर्ण, /* actual: 1699.2 MHz */
	अणु 16800000, 1700000000, 708,   7, 1, 8 पूर्ण, /* actual: 1699.2 MHz */
	अणु 19200000, 1700000000, 885,  10, 1, 8 पूर्ण, /* actual: 1699.2 MHz */
	अणु 26000000, 1700000000, 850,  13, 1, 8 पूर्ण,
	/* 1.6 GHz */
	अणु 12000000, 1600000000, 800,   6, 1, 8 पूर्ण,
	अणु 13000000, 1600000000, 738,   6, 1, 8 पूर्ण, /* actual: 1599.0 MHz */
	अणु 16800000, 1600000000, 857,   9, 1, 8 पूर्ण, /* actual: 1599.7 MHz */
	अणु 19200000, 1600000000, 500,   6, 1, 8 पूर्ण,
	अणु 26000000, 1600000000, 800,  13, 1, 8 पूर्ण,
	/* 1.5 GHz */
	अणु 12000000, 1500000000, 750,   6, 1, 8 पूर्ण,
	अणु 13000000, 1500000000, 923,   8, 1, 8 पूर्ण, /* actual: 1499.8 MHz */
	अणु 16800000, 1500000000, 625,   7, 1, 8 पूर्ण,
	अणु 19200000, 1500000000, 625,   8, 1, 8 पूर्ण,
	अणु 26000000, 1500000000, 750,  13, 1, 8 पूर्ण,
	/* 1.4 GHz */
	अणु 12000000, 1400000000,  700,  6, 1, 8 पूर्ण,
	अणु 13000000, 1400000000,  969,  9, 1, 8 पूर्ण, /* actual: 1399.7 MHz */
	अणु 16800000, 1400000000, 1000, 12, 1, 8 पूर्ण,
	अणु 19200000, 1400000000,  875, 12, 1, 8 पूर्ण,
	अणु 26000000, 1400000000,  700, 13, 1, 8 पूर्ण,
	/* 1.3 GHz */
	अणु 12000000, 1300000000,  975,  9, 1, 8 पूर्ण,
	अणु 13000000, 1300000000, 1000, 10, 1, 8 पूर्ण,
	अणु 16800000, 1300000000,  928, 12, 1, 8 पूर्ण, /* actual: 1299.2 MHz */
	अणु 19200000, 1300000000,  812, 12, 1, 8 पूर्ण, /* actual: 1299.2 MHz */
	अणु 26000000, 1300000000,  650, 13, 1, 8 पूर्ण,
	/* 1.2 GHz */
	अणु 12000000, 1200000000, 1000, 10, 1, 8 पूर्ण,
	अणु 13000000, 1200000000,  923, 10, 1, 8 पूर्ण, /* actual: 1199.9 MHz */
	अणु 16800000, 1200000000, 1000, 14, 1, 8 पूर्ण,
	अणु 19200000, 1200000000, 1000, 16, 1, 8 पूर्ण,
	अणु 26000000, 1200000000,  600, 13, 1, 8 पूर्ण,
	/* 1.1 GHz */
	अणु 12000000, 1100000000, 825,   9, 1, 8 पूर्ण,
	अणु 13000000, 1100000000, 846,  10, 1, 8 पूर्ण, /* actual: 1099.8 MHz */
	अणु 16800000, 1100000000, 982,  15, 1, 8 पूर्ण, /* actual: 1099.8 MHz */
	अणु 19200000, 1100000000, 859,  15, 1, 8 पूर्ण, /* actual: 1099.5 MHz */
	अणु 26000000, 1100000000, 550,  13, 1, 8 पूर्ण,
	/* 1 GHz */
	अणु 12000000, 1000000000, 1000, 12, 1, 8 पूर्ण,
	अणु 13000000, 1000000000, 1000, 13, 1, 8 पूर्ण,
	अणु 16800000, 1000000000,  833, 14, 1, 8 पूर्ण, /* actual: 999.6 MHz */
	अणु 19200000, 1000000000,  625, 12, 1, 8 पूर्ण,
	अणु 26000000, 1000000000, 1000, 26, 1, 8 पूर्ण,
	अणु        0,          0,    0,  0, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pभाग_map plle_p[] = अणु
	अणु .pभाग = 18, .hw_val = 18 पूर्ण,
	अणु .pभाग = 24, .hw_val = 24 पूर्ण,
	अणु .pभाग =  0, .hw_val =  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_e_freq_table[] = अणु
	/* PLLE special हाल: use cpcon field to store cml भागider value */
	अणु  12000000, 100000000, 150,  1, 18, 11 पूर्ण,
	अणु 216000000, 100000000, 200, 18, 24, 13 पूर्ण,
	अणु         0,         0,   0,  0,  0,  0 पूर्ण,
पूर्ण;

/* PLL parameters */
अटल काष्ठा tegra_clk_pll_params pll_c_params __ro_after_init = अणु
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
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा भाग_nmp pllm_nmp = अणु
	.भागn_shअगरt = 8,
	.भागn_width = 10,
	.override_भागn_shअगरt = 5,
	.भागm_shअगरt = 0,
	.भागm_width = 5,
	.override_भागm_shअगरt = 0,
	.भागp_shअगरt = 20,
	.भागp_width = 3,
	.override_भागp_shअगरt = 15,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_m_params __ro_after_init = अणु
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
	.भाग_nmp = &pllm_nmp,
	.pmc_भागnm_reg = PMC_PLLM_WB0_OVERRIDE,
	.pmc_भागp_reg = PMC_PLLM_WB0_OVERRIDE,
	.freq_table = pll_m_freq_table,
	.flags = TEGRA_PLLM | TEGRA_PLL_HAS_CPCON |
		 TEGRA_PLL_SET_DCCON | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE | TEGRA_PLL_FIXED,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_p_params __ro_after_init = अणु
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
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_HAS_CPCON | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
	.fixed_rate = 408000000,
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
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_d_params __ro_after_init = अणु
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
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_SET_LFCON |
		 TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_d2_params __ro_after_init = अणु
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 40000000,
	.vco_max = 1000000000,
	.base_reg = PLLD2_BASE,
	.misc_reg = PLLD2_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLDU_MISC_LOCK_ENABLE,
	.lock_delay = 1000,
	.freq_table = pll_d_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_SET_LFCON |
		 TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_u_params __ro_after_init = अणु
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
	.flags = TEGRA_PLLU | TEGRA_PLL_HAS_CPCON | TEGRA_PLL_SET_LFCON |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_x_params __ro_after_init = अणु
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1700000000,
	.base_reg = PLLX_BASE,
	.misc_reg = PLLX_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.freq_table = pll_x_freq_table,
	.flags = TEGRA_PLL_HAS_CPCON | TEGRA_PLL_SET_DCCON |
		 TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
	.pre_rate_change = tegra_cclk_pre_pllx_rate_change,
	.post_rate_change = tegra_cclk_post_pllx_rate_change,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_e_params __ro_after_init = अणु
	.input_min = 12000000,
	.input_max = 216000000,
	.cf_min = 12000000,
	.cf_max = 12000000,
	.vco_min = 1200000000,
	.vco_max = 2400000000U,
	.base_reg = PLLE_BASE,
	.misc_reg = PLLE_MISC,
	.lock_mask = PLLE_MISC_LOCK,
	.lock_enable_bit_idx = PLLE_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.pभाग_प्रकारohw = plle_p,
	.freq_table = pll_e_freq_table,
	.flags = TEGRA_PLLE_CONFIGURE | TEGRA_PLL_FIXED |
		 TEGRA_PLL_HAS_LOCK_ENABLE | TEGRA_PLL_LOCK_MISC,
	.fixed_rate = 100000000,
पूर्ण;

अटल अचिन्हित दीर्घ tegra30_input_freq[] = अणु
	[ 0] = 13000000,
	[ 1] = 16800000,
	[ 4] = 19200000,
	[ 5] = 38400000,
	[ 8] = 12000000,
	[ 9] = 48000000,
	[12] = 26000000,
पूर्ण;

अटल काष्ठा tegra_devclk devclks[] __initdata = अणु
	अणु .con_id = "pll_c", .dt_id = TEGRA30_CLK_PLL_C पूर्ण,
	अणु .con_id = "pll_c_out1", .dt_id = TEGRA30_CLK_PLL_C_OUT1 पूर्ण,
	अणु .con_id = "pll_p", .dt_id = TEGRA30_CLK_PLL_P पूर्ण,
	अणु .con_id = "pll_p_out1", .dt_id = TEGRA30_CLK_PLL_P_OUT1 पूर्ण,
	अणु .con_id = "pll_p_out2", .dt_id = TEGRA30_CLK_PLL_P_OUT2 पूर्ण,
	अणु .con_id = "pll_p_out3", .dt_id = TEGRA30_CLK_PLL_P_OUT3 पूर्ण,
	अणु .con_id = "pll_p_out4", .dt_id = TEGRA30_CLK_PLL_P_OUT4 पूर्ण,
	अणु .con_id = "pll_m", .dt_id = TEGRA30_CLK_PLL_M पूर्ण,
	अणु .con_id = "pll_m_out1", .dt_id = TEGRA30_CLK_PLL_M_OUT1 पूर्ण,
	अणु .con_id = "pll_x", .dt_id = TEGRA30_CLK_PLL_X पूर्ण,
	अणु .con_id = "pll_x_out0", .dt_id = TEGRA30_CLK_PLL_X_OUT0 पूर्ण,
	अणु .con_id = "pll_u", .dt_id = TEGRA30_CLK_PLL_U पूर्ण,
	अणु .con_id = "pll_d", .dt_id = TEGRA30_CLK_PLL_D पूर्ण,
	अणु .con_id = "pll_d_out0", .dt_id = TEGRA30_CLK_PLL_D_OUT0 पूर्ण,
	अणु .con_id = "pll_d2", .dt_id = TEGRA30_CLK_PLL_D2 पूर्ण,
	अणु .con_id = "pll_d2_out0", .dt_id = TEGRA30_CLK_PLL_D2_OUT0 पूर्ण,
	अणु .con_id = "pll_a", .dt_id = TEGRA30_CLK_PLL_A पूर्ण,
	अणु .con_id = "pll_a_out0", .dt_id = TEGRA30_CLK_PLL_A_OUT0 पूर्ण,
	अणु .con_id = "pll_e", .dt_id = TEGRA30_CLK_PLL_E पूर्ण,
	अणु .con_id = "spdif_in_sync", .dt_id = TEGRA30_CLK_SPDIF_IN_SYNC पूर्ण,
	अणु .con_id = "i2s0_sync", .dt_id = TEGRA30_CLK_I2S0_SYNC पूर्ण,
	अणु .con_id = "i2s1_sync", .dt_id = TEGRA30_CLK_I2S1_SYNC पूर्ण,
	अणु .con_id = "i2s2_sync", .dt_id = TEGRA30_CLK_I2S2_SYNC पूर्ण,
	अणु .con_id = "i2s3_sync", .dt_id = TEGRA30_CLK_I2S3_SYNC पूर्ण,
	अणु .con_id = "i2s4_sync", .dt_id = TEGRA30_CLK_I2S4_SYNC पूर्ण,
	अणु .con_id = "vimclk_sync", .dt_id = TEGRA30_CLK_VIMCLK_SYNC पूर्ण,
	अणु .con_id = "audio0", .dt_id = TEGRA30_CLK_AUDIO0 पूर्ण,
	अणु .con_id = "audio1", .dt_id = TEGRA30_CLK_AUDIO1 पूर्ण,
	अणु .con_id = "audio2", .dt_id = TEGRA30_CLK_AUDIO2 पूर्ण,
	अणु .con_id = "audio3", .dt_id = TEGRA30_CLK_AUDIO3 पूर्ण,
	अणु .con_id = "audio4", .dt_id = TEGRA30_CLK_AUDIO4 पूर्ण,
	अणु .con_id = "spdif", .dt_id = TEGRA30_CLK_SPDIF पूर्ण,
	अणु .con_id = "audio0_2x", .dt_id = TEGRA30_CLK_AUDIO0_2X पूर्ण,
	अणु .con_id = "audio1_2x", .dt_id = TEGRA30_CLK_AUDIO1_2X पूर्ण,
	अणु .con_id = "audio2_2x", .dt_id = TEGRA30_CLK_AUDIO2_2X पूर्ण,
	अणु .con_id = "audio3_2x", .dt_id = TEGRA30_CLK_AUDIO3_2X पूर्ण,
	अणु .con_id = "audio4_2x", .dt_id = TEGRA30_CLK_AUDIO4_2X पूर्ण,
	अणु .con_id = "spdif_2x", .dt_id = TEGRA30_CLK_SPDIF_2X पूर्ण,
	अणु .con_id = "extern1", .dt_id = TEGRA30_CLK_EXTERN1 पूर्ण,
	अणु .con_id = "extern2", .dt_id = TEGRA30_CLK_EXTERN2 पूर्ण,
	अणु .con_id = "extern3", .dt_id = TEGRA30_CLK_EXTERN3 पूर्ण,
	अणु .con_id = "cclk_g", .dt_id = TEGRA30_CLK_CCLK_G पूर्ण,
	अणु .con_id = "cclk_lp", .dt_id = TEGRA30_CLK_CCLK_LP पूर्ण,
	अणु .con_id = "sclk", .dt_id = TEGRA30_CLK_SCLK पूर्ण,
	अणु .con_id = "hclk", .dt_id = TEGRA30_CLK_HCLK पूर्ण,
	अणु .con_id = "pclk", .dt_id = TEGRA30_CLK_PCLK पूर्ण,
	अणु .con_id = "twd", .dt_id = TEGRA30_CLK_TWD पूर्ण,
	अणु .con_id = "emc", .dt_id = TEGRA30_CLK_EMC पूर्ण,
	अणु .con_id = "clk_32k", .dt_id = TEGRA30_CLK_CLK_32K पूर्ण,
	अणु .con_id = "osc", .dt_id = TEGRA30_CLK_OSC पूर्ण,
	अणु .con_id = "osc_div2", .dt_id = TEGRA30_CLK_OSC_DIV2 पूर्ण,
	अणु .con_id = "osc_div4", .dt_id = TEGRA30_CLK_OSC_DIV4 पूर्ण,
	अणु .con_id = "cml0", .dt_id = TEGRA30_CLK_CML0 पूर्ण,
	अणु .con_id = "cml1", .dt_id = TEGRA30_CLK_CML1 पूर्ण,
	अणु .con_id = "clk_m", .dt_id = TEGRA30_CLK_CLK_M पूर्ण,
	अणु .con_id = "pll_ref", .dt_id = TEGRA30_CLK_PLL_REF पूर्ण,
	अणु .con_id = "csus", .dev_id = "tengra_camera", .dt_id = TEGRA30_CLK_CSUS पूर्ण,
	अणु .con_id = "vcp", .dev_id = "tegra-avp", .dt_id = TEGRA30_CLK_VCP पूर्ण,
	अणु .con_id = "bsea", .dev_id = "tegra-avp", .dt_id = TEGRA30_CLK_BSEA पूर्ण,
	अणु .con_id = "bsev", .dev_id = "tegra-aes", .dt_id = TEGRA30_CLK_BSEV पूर्ण,
	अणु .con_id = "dsia", .dev_id = "tegradc.0", .dt_id = TEGRA30_CLK_DSIA पूर्ण,
	अणु .con_id = "csi", .dev_id = "tegra_camera", .dt_id = TEGRA30_CLK_CSI पूर्ण,
	अणु .con_id = "isp", .dev_id = "tegra_camera", .dt_id = TEGRA30_CLK_ISP पूर्ण,
	अणु .con_id = "pcie", .dev_id = "tegra-pcie", .dt_id = TEGRA30_CLK_PCIE पूर्ण,
	अणु .con_id = "afi", .dev_id = "tegra-pcie", .dt_id = TEGRA30_CLK_AFI पूर्ण,
	अणु .con_id = "fuse", .dt_id = TEGRA30_CLK_FUSE पूर्ण,
	अणु .con_id = "fuse_burn", .dev_id = "fuse-tegra", .dt_id = TEGRA30_CLK_FUSE_BURN पूर्ण,
	अणु .con_id = "apbif", .dev_id = "tegra30-ahub", .dt_id = TEGRA30_CLK_APBIF पूर्ण,
	अणु .con_id = "hda2hdmi", .dev_id = "tegra30-hda", .dt_id = TEGRA30_CLK_HDA2HDMI पूर्ण,
	अणु .dev_id = "tegra-apbdma", .dt_id = TEGRA30_CLK_APBDMA पूर्ण,
	अणु .dev_id = "rtc-tegra", .dt_id = TEGRA30_CLK_RTC पूर्ण,
	अणु .dev_id = "timer", .dt_id = TEGRA30_CLK_TIMER पूर्ण,
	अणु .dev_id = "tegra-kbc", .dt_id = TEGRA30_CLK_KBC पूर्ण,
	अणु .dev_id = "fsl-tegra-udc", .dt_id = TEGRA30_CLK_USBD पूर्ण,
	अणु .dev_id = "tegra-ehci.1", .dt_id = TEGRA30_CLK_USB2 पूर्ण,
	अणु .dev_id = "tegra-ehci.2", .dt_id = TEGRA30_CLK_USB2 पूर्ण,
	अणु .dev_id = "kfuse-tegra", .dt_id = TEGRA30_CLK_KFUSE पूर्ण,
	अणु .dev_id = "tegra_sata_cold", .dt_id = TEGRA30_CLK_SATA_COLD पूर्ण,
	अणु .dev_id = "dtv", .dt_id = TEGRA30_CLK_DTV पूर्ण,
	अणु .dev_id = "tegra30-i2s.0", .dt_id = TEGRA30_CLK_I2S0 पूर्ण,
	अणु .dev_id = "tegra30-i2s.1", .dt_id = TEGRA30_CLK_I2S1 पूर्ण,
	अणु .dev_id = "tegra30-i2s.2", .dt_id = TEGRA30_CLK_I2S2 पूर्ण,
	अणु .dev_id = "tegra30-i2s.3", .dt_id = TEGRA30_CLK_I2S3 पूर्ण,
	अणु .dev_id = "tegra30-i2s.4", .dt_id = TEGRA30_CLK_I2S4 पूर्ण,
	अणु .con_id = "spdif_out", .dev_id = "tegra30-spdif", .dt_id = TEGRA30_CLK_SPDIF_OUT पूर्ण,
	अणु .con_id = "spdif_in", .dev_id = "tegra30-spdif", .dt_id = TEGRA30_CLK_SPDIF_IN पूर्ण,
	अणु .con_id = "d_audio", .dev_id = "tegra30-ahub", .dt_id = TEGRA30_CLK_D_AUDIO पूर्ण,
	अणु .dev_id = "tegra30-dam.0", .dt_id = TEGRA30_CLK_DAM0 पूर्ण,
	अणु .dev_id = "tegra30-dam.1", .dt_id = TEGRA30_CLK_DAM1 पूर्ण,
	अणु .dev_id = "tegra30-dam.2", .dt_id = TEGRA30_CLK_DAM2 पूर्ण,
	अणु .con_id = "hda", .dev_id = "tegra30-hda", .dt_id = TEGRA30_CLK_HDA पूर्ण,
	अणु .con_id = "hda2codec_2x", .dev_id = "tegra30-hda", .dt_id = TEGRA30_CLK_HDA2CODEC_2X पूर्ण,
	अणु .dev_id = "spi_tegra.0", .dt_id = TEGRA30_CLK_SBC1 पूर्ण,
	अणु .dev_id = "spi_tegra.1", .dt_id = TEGRA30_CLK_SBC2 पूर्ण,
	अणु .dev_id = "spi_tegra.2", .dt_id = TEGRA30_CLK_SBC3 पूर्ण,
	अणु .dev_id = "spi_tegra.3", .dt_id = TEGRA30_CLK_SBC4 पूर्ण,
	अणु .dev_id = "spi_tegra.4", .dt_id = TEGRA30_CLK_SBC5 पूर्ण,
	अणु .dev_id = "spi_tegra.5", .dt_id = TEGRA30_CLK_SBC6 पूर्ण,
	अणु .dev_id = "tegra_sata_oob", .dt_id = TEGRA30_CLK_SATA_OOB पूर्ण,
	अणु .dev_id = "tegra_sata", .dt_id = TEGRA30_CLK_SATA पूर्ण,
	अणु .dev_id = "tegra_nand", .dt_id = TEGRA30_CLK_NDFLASH पूर्ण,
	अणु .dev_id = "tegra_nand_speed", .dt_id = TEGRA30_CLK_NDSPEED पूर्ण,
	अणु .dev_id = "vfir", .dt_id = TEGRA30_CLK_VFIR पूर्ण,
	अणु .dev_id = "csite", .dt_id = TEGRA30_CLK_CSITE पूर्ण,
	अणु .dev_id = "la", .dt_id = TEGRA30_CLK_LA पूर्ण,
	अणु .dev_id = "tegra_w1", .dt_id = TEGRA30_CLK_OWR पूर्ण,
	अणु .dev_id = "mipi", .dt_id = TEGRA30_CLK_MIPI पूर्ण,
	अणु .dev_id = "tegra-tsensor", .dt_id = TEGRA30_CLK_TSENSOR पूर्ण,
	अणु .dev_id = "i2cslow", .dt_id = TEGRA30_CLK_I2CSLOW पूर्ण,
	अणु .dev_id = "vde", .dt_id = TEGRA30_CLK_VDE पूर्ण,
	अणु .con_id = "vi", .dev_id = "tegra_camera", .dt_id = TEGRA30_CLK_VI पूर्ण,
	अणु .dev_id = "epp", .dt_id = TEGRA30_CLK_EPP पूर्ण,
	अणु .dev_id = "mpe", .dt_id = TEGRA30_CLK_MPE पूर्ण,
	अणु .dev_id = "host1x", .dt_id = TEGRA30_CLK_HOST1X पूर्ण,
	अणु .dev_id = "3d", .dt_id = TEGRA30_CLK_GR3D पूर्ण,
	अणु .dev_id = "3d2", .dt_id = TEGRA30_CLK_GR3D2 पूर्ण,
	अणु .dev_id = "2d", .dt_id = TEGRA30_CLK_GR2D पूर्ण,
	अणु .dev_id = "se", .dt_id = TEGRA30_CLK_SE पूर्ण,
	अणु .dev_id = "mselect", .dt_id = TEGRA30_CLK_MSELECT पूर्ण,
	अणु .dev_id = "tegra-nor", .dt_id = TEGRA30_CLK_NOR पूर्ण,
	अणु .dev_id = "sdhci-tegra.0", .dt_id = TEGRA30_CLK_SDMMC1 पूर्ण,
	अणु .dev_id = "sdhci-tegra.1", .dt_id = TEGRA30_CLK_SDMMC2 पूर्ण,
	अणु .dev_id = "sdhci-tegra.2", .dt_id = TEGRA30_CLK_SDMMC3 पूर्ण,
	अणु .dev_id = "sdhci-tegra.3", .dt_id = TEGRA30_CLK_SDMMC4 पूर्ण,
	अणु .dev_id = "cve", .dt_id = TEGRA30_CLK_CVE पूर्ण,
	अणु .dev_id = "tvo", .dt_id = TEGRA30_CLK_TVO पूर्ण,
	अणु .dev_id = "tvdac", .dt_id = TEGRA30_CLK_TVDAC पूर्ण,
	अणु .dev_id = "actmon", .dt_id = TEGRA30_CLK_ACTMON पूर्ण,
	अणु .con_id = "vi_sensor", .dev_id = "tegra_camera", .dt_id = TEGRA30_CLK_VI_SENSOR पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.0", .dt_id = TEGRA30_CLK_I2C1 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.1", .dt_id = TEGRA30_CLK_I2C2 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.2", .dt_id = TEGRA30_CLK_I2C3 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.3", .dt_id = TEGRA30_CLK_I2C4 पूर्ण,
	अणु .con_id = "div-clk", .dev_id = "tegra-i2c.4", .dt_id = TEGRA30_CLK_I2C5 पूर्ण,
	अणु .dev_id = "tegra_uart.0", .dt_id = TEGRA30_CLK_UARTA पूर्ण,
	अणु .dev_id = "tegra_uart.1", .dt_id = TEGRA30_CLK_UARTB पूर्ण,
	अणु .dev_id = "tegra_uart.2", .dt_id = TEGRA30_CLK_UARTC पूर्ण,
	अणु .dev_id = "tegra_uart.3", .dt_id = TEGRA30_CLK_UARTD पूर्ण,
	अणु .dev_id = "tegra_uart.4", .dt_id = TEGRA30_CLK_UARTE पूर्ण,
	अणु .dev_id = "hdmi", .dt_id = TEGRA30_CLK_HDMI पूर्ण,
	अणु .dev_id = "extern1", .dt_id = TEGRA30_CLK_EXTERN1 पूर्ण,
	अणु .dev_id = "extern2", .dt_id = TEGRA30_CLK_EXTERN2 पूर्ण,
	अणु .dev_id = "extern3", .dt_id = TEGRA30_CLK_EXTERN3 पूर्ण,
	अणु .dev_id = "pwm", .dt_id = TEGRA30_CLK_PWM पूर्ण,
	अणु .dev_id = "tegradc.0", .dt_id = TEGRA30_CLK_DISP1 पूर्ण,
	अणु .dev_id = "tegradc.1", .dt_id = TEGRA30_CLK_DISP2 पूर्ण,
	अणु .dev_id = "tegradc.1", .dt_id = TEGRA30_CLK_DSIB पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk tegra30_clks[tegra_clk_max] __initdata = अणु
	[tegra_clk_clk_32k] = अणु .dt_id = TEGRA30_CLK_CLK_32K, .present = true पूर्ण,
	[tegra_clk_clk_m] = अणु .dt_id = TEGRA30_CLK_CLK_M, .present = true पूर्ण,
	[tegra_clk_osc] = अणु .dt_id = TEGRA30_CLK_OSC, .present = true पूर्ण,
	[tegra_clk_osc_भाग2] = अणु .dt_id = TEGRA30_CLK_OSC_DIV2, .present = true पूर्ण,
	[tegra_clk_osc_भाग4] = अणु .dt_id = TEGRA30_CLK_OSC_DIV4, .present = true पूर्ण,
	[tegra_clk_pll_ref] = अणु .dt_id = TEGRA30_CLK_PLL_REF, .present = true पूर्ण,
	[tegra_clk_spdअगर_in_sync] = अणु .dt_id = TEGRA30_CLK_SPDIF_IN_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s0_sync] = अणु .dt_id = TEGRA30_CLK_I2S0_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s1_sync] = अणु .dt_id = TEGRA30_CLK_I2S1_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s2_sync] = अणु .dt_id = TEGRA30_CLK_I2S2_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s3_sync] = अणु .dt_id = TEGRA30_CLK_I2S3_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s4_sync] = अणु .dt_id = TEGRA30_CLK_I2S4_SYNC, .present = true पूर्ण,
	[tegra_clk_vimclk_sync] = अणु .dt_id = TEGRA30_CLK_VIMCLK_SYNC, .present = true पूर्ण,
	[tegra_clk_audio0] = अणु .dt_id = TEGRA30_CLK_AUDIO0, .present = true पूर्ण,
	[tegra_clk_audio1] = अणु .dt_id = TEGRA30_CLK_AUDIO1, .present = true पूर्ण,
	[tegra_clk_audio2] = अणु .dt_id = TEGRA30_CLK_AUDIO2, .present = true पूर्ण,
	[tegra_clk_audio3] = अणु .dt_id = TEGRA30_CLK_AUDIO3, .present = true पूर्ण,
	[tegra_clk_audio4] = अणु .dt_id = TEGRA30_CLK_AUDIO4, .present = true पूर्ण,
	[tegra_clk_spdअगर] = अणु .dt_id = TEGRA30_CLK_SPDIF, .present = true पूर्ण,
	[tegra_clk_audio0_mux] = अणु .dt_id = TEGRA30_CLK_AUDIO0_MUX, .present = true पूर्ण,
	[tegra_clk_audio1_mux] = अणु .dt_id = TEGRA30_CLK_AUDIO1_MUX, .present = true पूर्ण,
	[tegra_clk_audio2_mux] = अणु .dt_id = TEGRA30_CLK_AUDIO2_MUX, .present = true पूर्ण,
	[tegra_clk_audio3_mux] = अणु .dt_id = TEGRA30_CLK_AUDIO3_MUX, .present = true पूर्ण,
	[tegra_clk_audio4_mux] = अणु .dt_id = TEGRA30_CLK_AUDIO4_MUX, .present = true पूर्ण,
	[tegra_clk_spdअगर_mux] = अणु .dt_id = TEGRA30_CLK_SPDIF_MUX, .present = true पूर्ण,
	[tegra_clk_audio0_2x] = अणु .dt_id = TEGRA30_CLK_AUDIO0_2X, .present = true पूर्ण,
	[tegra_clk_audio1_2x] = अणु .dt_id = TEGRA30_CLK_AUDIO1_2X, .present = true पूर्ण,
	[tegra_clk_audio2_2x] = अणु .dt_id = TEGRA30_CLK_AUDIO2_2X, .present = true पूर्ण,
	[tegra_clk_audio3_2x] = अणु .dt_id = TEGRA30_CLK_AUDIO3_2X, .present = true पूर्ण,
	[tegra_clk_audio4_2x] = अणु .dt_id = TEGRA30_CLK_AUDIO4_2X, .present = true पूर्ण,
	[tegra_clk_spdअगर_2x] = अणु .dt_id = TEGRA30_CLK_SPDIF_2X, .present = true पूर्ण,
	[tegra_clk_hclk] = अणु .dt_id = TEGRA30_CLK_HCLK, .present = true पूर्ण,
	[tegra_clk_pclk] = अणु .dt_id = TEGRA30_CLK_PCLK, .present = true पूर्ण,
	[tegra_clk_i2s0] = अणु .dt_id = TEGRA30_CLK_I2S0, .present = true पूर्ण,
	[tegra_clk_i2s1] = अणु .dt_id = TEGRA30_CLK_I2S1, .present = true पूर्ण,
	[tegra_clk_i2s2] = अणु .dt_id = TEGRA30_CLK_I2S2, .present = true पूर्ण,
	[tegra_clk_i2s3] = अणु .dt_id = TEGRA30_CLK_I2S3, .present = true पूर्ण,
	[tegra_clk_i2s4] = अणु .dt_id = TEGRA30_CLK_I2S4, .present = true पूर्ण,
	[tegra_clk_spdअगर_in] = अणु .dt_id = TEGRA30_CLK_SPDIF_IN, .present = true पूर्ण,
	[tegra_clk_hda] = अणु .dt_id = TEGRA30_CLK_HDA, .present = true पूर्ण,
	[tegra_clk_hda2codec_2x] = अणु .dt_id = TEGRA30_CLK_HDA2CODEC_2X, .present = true पूर्ण,
	[tegra_clk_sbc1] = अणु .dt_id = TEGRA30_CLK_SBC1, .present = true पूर्ण,
	[tegra_clk_sbc2] = अणु .dt_id = TEGRA30_CLK_SBC2, .present = true पूर्ण,
	[tegra_clk_sbc3] = अणु .dt_id = TEGRA30_CLK_SBC3, .present = true पूर्ण,
	[tegra_clk_sbc4] = अणु .dt_id = TEGRA30_CLK_SBC4, .present = true पूर्ण,
	[tegra_clk_sbc5] = अणु .dt_id = TEGRA30_CLK_SBC5, .present = true पूर्ण,
	[tegra_clk_sbc6] = अणु .dt_id = TEGRA30_CLK_SBC6, .present = true पूर्ण,
	[tegra_clk_ndflash] = अणु .dt_id = TEGRA30_CLK_NDFLASH, .present = true पूर्ण,
	[tegra_clk_ndspeed] = अणु .dt_id = TEGRA30_CLK_NDSPEED, .present = true पूर्ण,
	[tegra_clk_vfir] = अणु .dt_id = TEGRA30_CLK_VFIR, .present = true पूर्ण,
	[tegra_clk_la] = अणु .dt_id = TEGRA30_CLK_LA, .present = true पूर्ण,
	[tegra_clk_csite] = अणु .dt_id = TEGRA30_CLK_CSITE, .present = true पूर्ण,
	[tegra_clk_owr] = अणु .dt_id = TEGRA30_CLK_OWR, .present = true पूर्ण,
	[tegra_clk_mipi] = अणु .dt_id = TEGRA30_CLK_MIPI, .present = true पूर्ण,
	[tegra_clk_tsensor] = अणु .dt_id = TEGRA30_CLK_TSENSOR, .present = true पूर्ण,
	[tegra_clk_i2cslow] = अणु .dt_id = TEGRA30_CLK_I2CSLOW, .present = true पूर्ण,
	[tegra_clk_vde] = अणु .dt_id = TEGRA30_CLK_VDE, .present = true पूर्ण,
	[tegra_clk_vi] = अणु .dt_id = TEGRA30_CLK_VI, .present = true पूर्ण,
	[tegra_clk_epp] = अणु .dt_id = TEGRA30_CLK_EPP, .present = true पूर्ण,
	[tegra_clk_mpe] = अणु .dt_id = TEGRA30_CLK_MPE, .present = true पूर्ण,
	[tegra_clk_host1x] = अणु .dt_id = TEGRA30_CLK_HOST1X, .present = true पूर्ण,
	[tegra_clk_gr2d] = अणु .dt_id = TEGRA30_CLK_GR2D, .present = true पूर्ण,
	[tegra_clk_gr3d] = अणु .dt_id = TEGRA30_CLK_GR3D, .present = true पूर्ण,
	[tegra_clk_mselect] = अणु .dt_id = TEGRA30_CLK_MSELECT, .present = true पूर्ण,
	[tegra_clk_nor] = अणु .dt_id = TEGRA30_CLK_NOR, .present = true पूर्ण,
	[tegra_clk_sdmmc1] = अणु .dt_id = TEGRA30_CLK_SDMMC1, .present = true पूर्ण,
	[tegra_clk_sdmmc2] = अणु .dt_id = TEGRA30_CLK_SDMMC2, .present = true पूर्ण,
	[tegra_clk_sdmmc3] = अणु .dt_id = TEGRA30_CLK_SDMMC3, .present = true पूर्ण,
	[tegra_clk_sdmmc4] = अणु .dt_id = TEGRA30_CLK_SDMMC4, .present = true पूर्ण,
	[tegra_clk_cve] = अणु .dt_id = TEGRA30_CLK_CVE, .present = true पूर्ण,
	[tegra_clk_tvo] = अणु .dt_id = TEGRA30_CLK_TVO, .present = true पूर्ण,
	[tegra_clk_tvdac] = अणु .dt_id = TEGRA30_CLK_TVDAC, .present = true पूर्ण,
	[tegra_clk_acपंचांगon] = अणु .dt_id = TEGRA30_CLK_ACTMON, .present = true पूर्ण,
	[tegra_clk_vi_sensor] = अणु .dt_id = TEGRA30_CLK_VI_SENSOR, .present = true पूर्ण,
	[tegra_clk_i2c1] = अणु .dt_id = TEGRA30_CLK_I2C1, .present = true पूर्ण,
	[tegra_clk_i2c2] = अणु .dt_id = TEGRA30_CLK_I2C2, .present = true पूर्ण,
	[tegra_clk_i2c3] = अणु .dt_id = TEGRA30_CLK_I2C3, .present = true पूर्ण,
	[tegra_clk_i2c4] = अणु .dt_id = TEGRA30_CLK_I2C4, .present = true पूर्ण,
	[tegra_clk_i2c5] = अणु .dt_id = TEGRA30_CLK_I2C5, .present = true पूर्ण,
	[tegra_clk_uarta] = अणु .dt_id = TEGRA30_CLK_UARTA, .present = true पूर्ण,
	[tegra_clk_uartb] = अणु .dt_id = TEGRA30_CLK_UARTB, .present = true पूर्ण,
	[tegra_clk_uartc] = अणु .dt_id = TEGRA30_CLK_UARTC, .present = true पूर्ण,
	[tegra_clk_uartd] = अणु .dt_id = TEGRA30_CLK_UARTD, .present = true पूर्ण,
	[tegra_clk_uarte] = अणु .dt_id = TEGRA30_CLK_UARTE, .present = true पूर्ण,
	[tegra_clk_बाह्य1] = अणु .dt_id = TEGRA30_CLK_EXTERN1, .present = true पूर्ण,
	[tegra_clk_बाह्य2] = अणु .dt_id = TEGRA30_CLK_EXTERN2, .present = true पूर्ण,
	[tegra_clk_बाह्य3] = अणु .dt_id = TEGRA30_CLK_EXTERN3, .present = true पूर्ण,
	[tegra_clk_disp1] = अणु .dt_id = TEGRA30_CLK_DISP1, .present = true पूर्ण,
	[tegra_clk_disp2] = अणु .dt_id = TEGRA30_CLK_DISP2, .present = true पूर्ण,
	[tegra_clk_ahbdma] = अणु .dt_id = TEGRA30_CLK_AHBDMA, .present = true पूर्ण,
	[tegra_clk_apbdma] = अणु .dt_id = TEGRA30_CLK_APBDMA, .present = true पूर्ण,
	[tegra_clk_rtc] = अणु .dt_id = TEGRA30_CLK_RTC, .present = true पूर्ण,
	[tegra_clk_समयr] = अणु .dt_id = TEGRA30_CLK_TIMER, .present = true पूर्ण,
	[tegra_clk_kbc] = अणु .dt_id = TEGRA30_CLK_KBC, .present = true पूर्ण,
	[tegra_clk_csus] = अणु .dt_id = TEGRA30_CLK_CSUS, .present = true पूर्ण,
	[tegra_clk_vcp] = अणु .dt_id = TEGRA30_CLK_VCP, .present = true पूर्ण,
	[tegra_clk_bsea] = अणु .dt_id = TEGRA30_CLK_BSEA, .present = true पूर्ण,
	[tegra_clk_bsev] = अणु .dt_id = TEGRA30_CLK_BSEV, .present = true पूर्ण,
	[tegra_clk_usbd] = अणु .dt_id = TEGRA30_CLK_USBD, .present = true पूर्ण,
	[tegra_clk_usb2] = अणु .dt_id = TEGRA30_CLK_USB2, .present = true पूर्ण,
	[tegra_clk_usb3] = अणु .dt_id = TEGRA30_CLK_USB3, .present = true पूर्ण,
	[tegra_clk_csi] = अणु .dt_id = TEGRA30_CLK_CSI, .present = true पूर्ण,
	[tegra_clk_isp] = अणु .dt_id = TEGRA30_CLK_ISP, .present = true पूर्ण,
	[tegra_clk_kfuse] = अणु .dt_id = TEGRA30_CLK_KFUSE, .present = true पूर्ण,
	[tegra_clk_fuse] = अणु .dt_id = TEGRA30_CLK_FUSE, .present = true पूर्ण,
	[tegra_clk_fuse_burn] = अणु .dt_id = TEGRA30_CLK_FUSE_BURN, .present = true पूर्ण,
	[tegra_clk_apbअगर] = अणु .dt_id = TEGRA30_CLK_APBIF, .present = true पूर्ण,
	[tegra_clk_hda2hdmi] = अणु .dt_id = TEGRA30_CLK_HDA2HDMI, .present = true पूर्ण,
	[tegra_clk_sata_cold] = अणु .dt_id = TEGRA30_CLK_SATA_COLD, .present = true पूर्ण,
	[tegra_clk_sata_oob] = अणु .dt_id = TEGRA30_CLK_SATA_OOB, .present = true पूर्ण,
	[tegra_clk_sata] = अणु .dt_id = TEGRA30_CLK_SATA, .present = true पूर्ण,
	[tegra_clk_dtv] = अणु .dt_id = TEGRA30_CLK_DTV, .present = true पूर्ण,
	[tegra_clk_pll_p] = अणु .dt_id = TEGRA30_CLK_PLL_P, .present = true पूर्ण,
	[tegra_clk_pll_p_out1] = अणु .dt_id = TEGRA30_CLK_PLL_P_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_p_out2] = अणु .dt_id = TEGRA30_CLK_PLL_P_OUT2, .present = true पूर्ण,
	[tegra_clk_pll_p_out3] = अणु .dt_id = TEGRA30_CLK_PLL_P_OUT3, .present = true पूर्ण,
	[tegra_clk_pll_p_out4] = अणु .dt_id = TEGRA30_CLK_PLL_P_OUT4, .present = true पूर्ण,
	[tegra_clk_pll_a] = अणु .dt_id = TEGRA30_CLK_PLL_A, .present = true पूर्ण,
	[tegra_clk_pll_a_out0] = अणु .dt_id = TEGRA30_CLK_PLL_A_OUT0, .present = true पूर्ण,
	[tegra_clk_cec] = अणु .dt_id = TEGRA30_CLK_CEC, .present = true पूर्ण,
	[tegra_clk_emc] = अणु .dt_id = TEGRA30_CLK_EMC, .present = false पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *pll_e_parents[] = अणु "pll_ref", "pll_p" पूर्ण;

अटल व्योम __init tegra30_pll_init(व्योम)
अणु
	काष्ठा clk *clk;

	/* PLLC */
	clk = tegra_clk_रेजिस्टर_pll("pll_c", "pll_ref", clk_base, pmc_base, 0,
				     &pll_c_params, शून्य);
	clks[TEGRA30_CLK_PLL_C] = clk;

	/* PLLC_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_c_out1_div", "pll_c",
				clk_base + PLLC_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_c_out1", "pll_c_out1_div",
				clk_base + PLLC_OUT, 1, 0, CLK_SET_RATE_PARENT,
				0, शून्य);
	clks[TEGRA30_CLK_PLL_C_OUT1] = clk;

	/* PLLM */
	clk = tegra_clk_रेजिस्टर_pll("pll_m", "pll_ref", clk_base, pmc_base,
			    CLK_SET_RATE_GATE, &pll_m_params, शून्य);
	clks[TEGRA30_CLK_PLL_M] = clk;

	/* PLLM_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_m_out1_div", "pll_m",
				clk_base + PLLM_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_m_out1", "pll_m_out1_div",
				clk_base + PLLM_OUT, 1, 0,
				CLK_SET_RATE_PARENT, 0, शून्य);
	clks[TEGRA30_CLK_PLL_M_OUT1] = clk;

	/* PLLX */
	clk = tegra_clk_रेजिस्टर_pll("pll_x", "pll_ref", clk_base, pmc_base, 0,
			    &pll_x_params, शून्य);
	clks[TEGRA30_CLK_PLL_X] = clk;

	/* PLLX_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_x_out0", "pll_x",
					CLK_SET_RATE_PARENT, 1, 2);
	clks[TEGRA30_CLK_PLL_X_OUT0] = clk;

	/* PLLU */
	clk = tegra_clk_रेजिस्टर_pllu("pll_u", "pll_ref", clk_base, 0,
				      &pll_u_params, शून्य);
	clks[TEGRA30_CLK_PLL_U] = clk;

	/* PLLD */
	clk = tegra_clk_रेजिस्टर_pll("pll_d", "pll_ref", clk_base, pmc_base, 0,
			    &pll_d_params, &pll_d_lock);
	clks[TEGRA30_CLK_PLL_D] = clk;

	/* PLLD_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d_out0", "pll_d",
					CLK_SET_RATE_PARENT, 1, 2);
	clks[TEGRA30_CLK_PLL_D_OUT0] = clk;

	/* PLLD2 */
	clk = tegra_clk_रेजिस्टर_pll("pll_d2", "pll_ref", clk_base, pmc_base, 0,
			    &pll_d2_params, शून्य);
	clks[TEGRA30_CLK_PLL_D2] = clk;

	/* PLLD2_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d2_out0", "pll_d2",
					CLK_SET_RATE_PARENT, 1, 2);
	clks[TEGRA30_CLK_PLL_D2_OUT0] = clk;

	/* PLLE */
	clk = clk_रेजिस्टर_mux(शून्य, "pll_e_mux", pll_e_parents,
			       ARRAY_SIZE(pll_e_parents),
			       CLK_SET_RATE_NO_REPARENT,
			       clk_base + PLLE_AUX, 2, 1, 0, शून्य);
	clk = tegra_clk_रेजिस्टर_plle("pll_e", "pll_e_mux", clk_base, pmc_base,
			     CLK_GET_RATE_NOCACHE, &pll_e_params, शून्य);
	clks[TEGRA30_CLK_PLL_E] = clk;
पूर्ण

अटल स्थिर अक्षर *cclk_g_parents[] = अणु "clk_m", "pll_c", "clk_32k", "pll_m",
					"pll_p_cclkg", "pll_p_out4_cclkg",
					"pll_p_out3_cclkg", "unused", "pll_x" पूर्ण;
अटल स्थिर अक्षर *cclk_lp_parents[] = अणु "clk_m", "pll_c", "clk_32k", "pll_m",
					 "pll_p_cclklp", "pll_p_out4_cclklp",
					 "pll_p_out3_cclklp", "unused", "pll_x",
					 "pll_x_out0" पूर्ण;
अटल स्थिर अक्षर *sclk_parents[] = अणु "clk_m", "pll_c_out1", "pll_p_out4",
				      "pll_p_out3", "pll_p_out2", "unused",
				      "clk_32k", "pll_m_out1" पूर्ण;

अटल व्योम __init tegra30_super_clk_init(व्योम)
अणु
	काष्ठा clk *clk;

	/*
	 * Clock input to cclk_g भागided from pll_p using
	 * U71 भागider of cclk_g.
	 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_p_cclkg", "pll_p",
				clk_base + SUPER_CCLKG_DIVIDER, 0,
				TEGRA_DIVIDER_INT, 16, 8, 1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_p_cclkg", शून्य);

	/*
	 * Clock input to cclk_g भागided from pll_p_out3 using
	 * U71 भागider of cclk_g.
	 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_p_out3_cclkg", "pll_p_out3",
				clk_base + SUPER_CCLKG_DIVIDER, 0,
				TEGRA_DIVIDER_INT, 16, 8, 1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_p_out3_cclkg", शून्य);

	/*
	 * Clock input to cclk_g भागided from pll_p_out4 using
	 * U71 भागider of cclk_g.
	 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_p_out4_cclkg", "pll_p_out4",
				clk_base + SUPER_CCLKG_DIVIDER, 0,
				TEGRA_DIVIDER_INT, 16, 8, 1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_p_out4_cclkg", शून्य);

	/* CCLKG */
	clk = tegra_clk_रेजिस्टर_super_cclk("cclk_g", cclk_g_parents,
				  ARRAY_SIZE(cclk_g_parents),
				  CLK_SET_RATE_PARENT,
				  clk_base + CCLKG_BURST_POLICY,
				  0, शून्य);
	clks[TEGRA30_CLK_CCLK_G] = clk;

	/*
	 * Clock input to cclk_lp भागided from pll_p using
	 * U71 भागider of cclk_lp.
	 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_p_cclklp", "pll_p",
				clk_base + SUPER_CCLKLP_DIVIDER, 0,
				TEGRA_DIVIDER_INT, 16, 8, 1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_p_cclklp", शून्य);

	/*
	 * Clock input to cclk_lp भागided from pll_p_out3 using
	 * U71 भागider of cclk_lp.
	 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_p_out3_cclklp", "pll_p_out3",
				clk_base + SUPER_CCLKLP_DIVIDER, 0,
				TEGRA_DIVIDER_INT, 16, 8, 1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_p_out3_cclklp", शून्य);

	/*
	 * Clock input to cclk_lp भागided from pll_p_out4 using
	 * U71 भागider of cclk_lp.
	 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_p_out4_cclklp", "pll_p_out4",
				clk_base + SUPER_CCLKLP_DIVIDER, 0,
				TEGRA_DIVIDER_INT, 16, 8, 1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_p_out4_cclklp", शून्य);

	/* CCLKLP */
	clk = tegra_clk_रेजिस्टर_super_mux("cclk_lp", cclk_lp_parents,
				  ARRAY_SIZE(cclk_lp_parents),
				  CLK_SET_RATE_PARENT,
				  clk_base + CCLKLP_BURST_POLICY,
				  TEGRA_DIVIDER_2, 4, 8, 9,
			      शून्य);
	clks[TEGRA30_CLK_CCLK_LP] = clk;

	/* SCLK */
	clk = tegra_clk_रेजिस्टर_super_mux("sclk", sclk_parents,
				  ARRAY_SIZE(sclk_parents),
				  CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
				  clk_base + SCLK_BURST_POLICY,
				  0, 4, 0, 0, शून्य);
	clks[TEGRA30_CLK_SCLK] = clk;

	/* twd */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "twd", "cclk_g",
					CLK_SET_RATE_PARENT, 1, 2);
	clks[TEGRA30_CLK_TWD] = clk;

	tegra_super_clk_gen4_init(clk_base, pmc_base, tegra30_clks, शून्य);
पूर्ण

अटल स्थिर अक्षर *mux_pllacp_clkm[] = अणु "pll_a_out0", "unused", "pll_p",
					 "clk_m" पूर्ण;
अटल स्थिर अक्षर *mux_pllpcm_clkm[] = अणु "pll_p", "pll_c", "pll_m", "clk_m" पूर्ण;
अटल स्थिर अक्षर *spdअगर_out_parents[] = अणु "pll_a_out0", "spdif_2x", "pll_p",
					   "clk_m" पूर्ण;
अटल स्थिर अक्षर *mux_pllmcpa[] = अणु "pll_m", "pll_c", "pll_p", "pll_a_out0" पूर्ण;
अटल स्थिर अक्षर *mux_pllpmdacd2_clkm[] = अणु "pll_p", "pll_m", "pll_d_out0",
					     "pll_a_out0", "pll_c",
					     "pll_d2_out0", "clk_m" पूर्ण;
अटल स्थिर अक्षर *mux_plld_out0_plld2_out0[] = अणु "pll_d_out0",
						  "pll_d2_out0" पूर्ण;
अटल स्थिर अक्षर *pwm_parents[] = अणु "pll_p", "pll_c", "clk_32k", "clk_m" पूर्ण;

अटल काष्ठा tegra_periph_init_data tegra_periph_clk_list[] = अणु
	TEGRA_INIT_DATA_MUX("spdif_out", spdअगर_out_parents, CLK_SOURCE_SPDIF_OUT, 10, TEGRA_PERIPH_ON_APB, TEGRA30_CLK_SPDIF_OUT),
	TEGRA_INIT_DATA_MUX("d_audio", mux_pllacp_clkm, CLK_SOURCE_D_AUDIO, 106, 0, TEGRA30_CLK_D_AUDIO),
	TEGRA_INIT_DATA_MUX("dam0", mux_pllacp_clkm, CLK_SOURCE_DAM0, 108, 0, TEGRA30_CLK_DAM0),
	TEGRA_INIT_DATA_MUX("dam1", mux_pllacp_clkm, CLK_SOURCE_DAM1, 109, 0, TEGRA30_CLK_DAM1),
	TEGRA_INIT_DATA_MUX("dam2", mux_pllacp_clkm, CLK_SOURCE_DAM2, 110, 0, TEGRA30_CLK_DAM2),
	TEGRA_INIT_DATA_INT("3d2", mux_pllmcpa, CLK_SOURCE_3D2, 98, TEGRA_PERIPH_MANUAL_RESET, TEGRA30_CLK_GR3D2),
	TEGRA_INIT_DATA_INT("se", mux_pllpcm_clkm, CLK_SOURCE_SE, 127, 0, TEGRA30_CLK_SE),
	TEGRA_INIT_DATA_MUX8("hdmi", mux_pllpmdacd2_clkm, CLK_SOURCE_HDMI, 51, 0, TEGRA30_CLK_HDMI),
	TEGRA_INIT_DATA("pwm", शून्य, शून्य, pwm_parents, CLK_SOURCE_PWM, 28, 2, 0, 0, 8, 1, 0, 17, TEGRA_PERIPH_ON_APB, TEGRA30_CLK_PWM),
पूर्ण;

अटल काष्ठा tegra_periph_init_data tegra_periph_noभाग_clk_list[] = अणु
	TEGRA_INIT_DATA_NODIV("dsib", mux_plld_out0_plld2_out0, CLK_SOURCE_DSIB, 25, 1, 82, 0, TEGRA30_CLK_DSIB),
पूर्ण;

अटल व्योम __init tegra30_periph_clk_init(व्योम)
अणु
	काष्ठा tegra_periph_init_data *data;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	/* dsia */
	clk = tegra_clk_रेजिस्टर_periph_gate("dsia", "pll_d_out0", 0, clk_base,
				    0, 48, periph_clk_enb_refcnt);
	clks[TEGRA30_CLK_DSIA] = clk;

	/* pcie */
	clk = tegra_clk_रेजिस्टर_periph_gate("pcie", "clk_m", 0, clk_base, 0,
				    70, periph_clk_enb_refcnt);
	clks[TEGRA30_CLK_PCIE] = clk;

	/* afi */
	clk = tegra_clk_रेजिस्टर_periph_gate("afi", "clk_m", 0, clk_base, 0, 72,
				    periph_clk_enb_refcnt);
	clks[TEGRA30_CLK_AFI] = clk;

	/* emc */
	clk = tegra20_clk_रेजिस्टर_emc(clk_base + CLK_SOURCE_EMC, true);

	clks[TEGRA30_CLK_EMC] = clk;

	clk = tegra_clk_रेजिस्टर_mc("mc", "emc", clk_base + CLK_SOURCE_EMC,
				    शून्य);
	clks[TEGRA30_CLK_MC] = clk;

	/* cml0 */
	clk = clk_रेजिस्टर_gate(शून्य, "cml0", "pll_e", 0, clk_base + PLLE_AUX,
				0, 0, &cml_lock);
	clks[TEGRA30_CLK_CML0] = clk;

	/* cml1 */
	clk = clk_रेजिस्टर_gate(शून्य, "cml1", "pll_e", 0, clk_base + PLLE_AUX,
				1, 0, &cml_lock);
	clks[TEGRA30_CLK_CML1] = clk;

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

	tegra_periph_clk_init(clk_base, pmc_base, tegra30_clks, &pll_p_params);
पूर्ण

/* Tegra30 CPU घड़ी and reset control functions */
अटल व्योम tegra30_रुको_cpu_in_reset(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	करो अणु
		reg = पढ़ोl(clk_base +
			    TEGRA30_CLK_RST_CONTROLLER_CPU_CMPLX_STATUS);
		cpu_relax();
	पूर्ण जबतक (!(reg & (1 << cpu)));	/* check CPU been reset or not */

	वापस;
पूर्ण

अटल व्योम tegra30_put_cpu_in_reset(u32 cpu)
अणु
	ग_लिखोl(CPU_RESET(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_SET);
	dmb();
पूर्ण

अटल व्योम tegra30_cpu_out_of_reset(u32 cpu)
अणु
	ग_लिखोl(CPU_RESET(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_RST_CPU_CMPLX_CLR);
	wmb();
पूर्ण

अटल व्योम tegra30_enable_cpu_घड़ी(u32 cpu)
अणु
	ग_लिखोl(CPU_CLOCK(cpu),
	       clk_base + TEGRA30_CLK_RST_CONTROLLER_CLK_CPU_CMPLX_CLR);
	पढ़ोl(clk_base + TEGRA30_CLK_RST_CONTROLLER_CLK_CPU_CMPLX_CLR);
पूर्ण

अटल व्योम tegra30_disable_cpu_घड़ी(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
	ग_लिखोl(reg | CPU_CLOCK(cpu),
	       clk_base + TEGRA_CLK_RST_CONTROLLER_CLK_CPU_CMPLX);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool tegra30_cpu_rail_off_पढ़ोy(व्योम)
अणु
	अचिन्हित पूर्णांक cpu_rst_status;
	पूर्णांक cpu_pwr_status;

	cpu_rst_status = पढ़ोl(clk_base +
				TEGRA30_CLK_RST_CONTROLLER_CPU_CMPLX_STATUS);
	cpu_pwr_status = tegra_pmc_cpu_is_घातered(1) ||
			 tegra_pmc_cpu_is_घातered(2) ||
			 tegra_pmc_cpu_is_घातered(3);

	अगर (((cpu_rst_status & 0xE) != 0xE) || cpu_pwr_status)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम tegra30_cpu_घड़ी_suspend(व्योम)
अणु
	/* चयन coresite to clk_m, save off original source */
	tegra30_cpu_clk_sctx.clk_csite_src =
				पढ़ोl(clk_base + CLK_RESET_SOURCE_CSITE);
	ग_लिखोl(3 << 30, clk_base + CLK_RESET_SOURCE_CSITE);

	tegra30_cpu_clk_sctx.cpu_burst =
				पढ़ोl(clk_base + CLK_RESET_CCLK_BURST);
	tegra30_cpu_clk_sctx.pllx_base =
				पढ़ोl(clk_base + CLK_RESET_PLLX_BASE);
	tegra30_cpu_clk_sctx.pllx_misc =
				पढ़ोl(clk_base + CLK_RESET_PLLX_MISC);
	tegra30_cpu_clk_sctx.cclk_भागider =
				पढ़ोl(clk_base + CLK_RESET_CCLK_DIVIDER);
पूर्ण

अटल व्योम tegra30_cpu_घड़ी_resume(व्योम)
अणु
	अचिन्हित पूर्णांक reg, policy;
	u32 misc, base;

	/* Is CPU complex alपढ़ोy running on PLLX? */
	reg = पढ़ोl(clk_base + CLK_RESET_CCLK_BURST);
	policy = (reg >> CLK_RESET_CCLK_BURST_POLICY_SHIFT) & 0xF;

	अगर (policy == CLK_RESET_CCLK_IDLE_POLICY)
		reg = (reg >> CLK_RESET_CCLK_IDLE_POLICY_SHIFT) & 0xF;
	अन्यथा अगर (policy == CLK_RESET_CCLK_RUN_POLICY)
		reg = (reg >> CLK_RESET_CCLK_RUN_POLICY_SHIFT) & 0xF;
	अन्यथा
		BUG();

	अगर (reg != CLK_RESET_CCLK_BURST_POLICY_PLLX) अणु
		misc = पढ़ोl_relaxed(clk_base + CLK_RESET_PLLX_MISC);
		base = पढ़ोl_relaxed(clk_base + CLK_RESET_PLLX_BASE);

		अगर (misc != tegra30_cpu_clk_sctx.pllx_misc ||
		    base != tegra30_cpu_clk_sctx.pllx_base) अणु
			/* restore PLLX settings अगर CPU is on dअगरferent PLL */
			ग_लिखोl(tegra30_cpu_clk_sctx.pllx_misc,
						clk_base + CLK_RESET_PLLX_MISC);
			ग_लिखोl(tegra30_cpu_clk_sctx.pllx_base,
						clk_base + CLK_RESET_PLLX_BASE);

			/* रुको क्रम PLL stabilization अगर PLLX was enabled */
			अगर (tegra30_cpu_clk_sctx.pllx_base & (1 << 30))
				udelay(300);
		पूर्ण
	पूर्ण

	/*
	 * Restore original burst policy setting क्रम calls resulting from CPU
	 * LP2 in idle or प्रणाली suspend.
	 */
	ग_लिखोl(tegra30_cpu_clk_sctx.cclk_भागider,
					clk_base + CLK_RESET_CCLK_DIVIDER);
	ग_लिखोl(tegra30_cpu_clk_sctx.cpu_burst,
					clk_base + CLK_RESET_CCLK_BURST);

	ग_लिखोl(tegra30_cpu_clk_sctx.clk_csite_src,
					clk_base + CLK_RESET_SOURCE_CSITE);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा tegra_cpu_car_ops tegra30_cpu_car_ops = अणु
	.रुको_क्रम_reset	= tegra30_रुको_cpu_in_reset,
	.put_in_reset	= tegra30_put_cpu_in_reset,
	.out_of_reset	= tegra30_cpu_out_of_reset,
	.enable_घड़ी	= tegra30_enable_cpu_घड़ी,
	.disable_घड़ी	= tegra30_disable_cpu_घड़ी,
#अगर_घोषित CONFIG_PM_SLEEP
	.rail_off_पढ़ोy	= tegra30_cpu_rail_off_पढ़ोy,
	.suspend	= tegra30_cpu_घड़ी_suspend,
	.resume		= tegra30_cpu_घड़ी_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा tegra_clk_init_table init_table[] __initdata = अणु
	अणु TEGRA30_CLK_UARTA, TEGRA30_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA30_CLK_UARTB, TEGRA30_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA30_CLK_UARTC, TEGRA30_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA30_CLK_UARTD, TEGRA30_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA30_CLK_UARTE, TEGRA30_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA30_CLK_PLL_A, TEGRA30_CLK_CLK_MAX, 564480000, 0 पूर्ण,
	अणु TEGRA30_CLK_PLL_A_OUT0, TEGRA30_CLK_CLK_MAX, 11289600, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S0, TEGRA30_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S1, TEGRA30_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S2, TEGRA30_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S3, TEGRA30_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S4, TEGRA30_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA30_CLK_SDMMC1, TEGRA30_CLK_PLL_P, 48000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SDMMC2, TEGRA30_CLK_PLL_P, 48000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SDMMC3, TEGRA30_CLK_PLL_P, 48000000, 0 पूर्ण,
	अणु TEGRA30_CLK_CSITE, TEGRA30_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA30_CLK_MSELECT, TEGRA30_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA30_CLK_SBC1, TEGRA30_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SBC2, TEGRA30_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SBC3, TEGRA30_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SBC4, TEGRA30_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SBC5, TEGRA30_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SBC6, TEGRA30_CLK_PLL_P, 100000000, 0 पूर्ण,
	अणु TEGRA30_CLK_PLL_C, TEGRA30_CLK_CLK_MAX, 600000000, 0 पूर्ण,
	अणु TEGRA30_CLK_HOST1X, TEGRA30_CLK_PLL_C, 150000000, 0 पूर्ण,
	अणु TEGRA30_CLK_TWD, TEGRA30_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA30_CLK_GR2D, TEGRA30_CLK_PLL_C, 300000000, 0 पूर्ण,
	अणु TEGRA30_CLK_GR3D, TEGRA30_CLK_PLL_C, 300000000, 0 पूर्ण,
	अणु TEGRA30_CLK_GR3D2, TEGRA30_CLK_PLL_C, 300000000, 0 पूर्ण,
	अणु TEGRA30_CLK_PLL_U, TEGRA30_CLK_CLK_MAX, 480000000, 0 पूर्ण,
	अणु TEGRA30_CLK_VDE, TEGRA30_CLK_PLL_C, 600000000, 0 पूर्ण,
	अणु TEGRA30_CLK_SPDIF_IN_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S0_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S1_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S2_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S3_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_I2S4_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_VIMCLK_SYNC, TEGRA30_CLK_CLK_MAX, 24000000, 0 पूर्ण,
	अणु TEGRA30_CLK_HDA, TEGRA30_CLK_PLL_P, 102000000, 0 पूर्ण,
	अणु TEGRA30_CLK_HDA2CODEC_2X, TEGRA30_CLK_PLL_P, 48000000, 0 पूर्ण,
	/* must be the last entry */
	अणु TEGRA30_CLK_CLK_MAX, TEGRA30_CLK_CLK_MAX, 0, 0 पूर्ण,
पूर्ण;

अटल व्योम __init tegra30_घड़ी_apply_init_table(व्योम)
अणु
	tegra_init_from_table(init_table, clks, TEGRA30_CLK_CLK_MAX);
पूर्ण

/*
 * Some घड़ीs may be used by dअगरferent drivers depending on the board
 * configuration.  List those here to रेजिस्टर them twice in the घड़ी lookup
 * table under two names.
 */
अटल काष्ठा tegra_clk_duplicate tegra_clk_duplicates[] = अणु
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_USBD, "utmip-pad", शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_USBD, "tegra-ehci.0", शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_USBD, "tegra-otg", शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_BSEV, "tegra-avp", "bsev"),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_BSEV, "nvavp", "bsev"),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_VDE, "tegra-aes", "vde"),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_BSEA, "tegra-aes", "bsea"),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_BSEA, "nvavp", "bsea"),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_CML1, "tegra_sata_cml", शून्य),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_CML0, "tegra_pcie", "cml"),
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_VCP, "nvavp", "vcp"),
	/* must be the last entry */
	TEGRA_CLK_DUPLICATE(TEGRA30_CLK_CLK_MAX, शून्य, शून्य),
पूर्ण;

अटल स्थिर काष्ठा of_device_id pmc_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra30-pmc" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा tegra_audio_clk_info tegra30_audio_plls[] = अणु
	अणु "pll_a", &pll_a_params, tegra_clk_pll_a, "pll_p_out1" पूर्ण,
पूर्ण;

अटल काष्ठा clk *tegra30_clk_src_onecell_get(काष्ठा of_phandle_args *clkspec,
					       व्योम *data)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk *clk;

	clk = of_clk_src_onecell_get(clkspec, data);
	अगर (IS_ERR(clk))
		वापस clk;

	hw = __clk_get_hw(clk);

	अगर (clkspec->args[0] == TEGRA30_CLK_EMC) अणु
		अगर (!tegra20_clk_emc_driver_available(hw))
			वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	वापस clk;
पूर्ण

अटल व्योम __init tegra30_घड़ी_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *node;

	clk_base = of_iomap(np, 0);
	अगर (!clk_base) अणु
		pr_err("ioremap tegra30 CAR failed\n");
		वापस;
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

	clks = tegra_clk_init(clk_base, TEGRA30_CLK_CLK_MAX,
				TEGRA30_CLK_PERIPH_BANKS);
	अगर (!clks)
		वापस;

	अगर (tegra_osc_clk_init(clk_base, tegra30_clks, tegra30_input_freq,
			       ARRAY_SIZE(tegra30_input_freq), 1, &input_freq,
			       शून्य) < 0)
		वापस;

	tegra_fixed_clk_init(tegra30_clks);
	tegra30_pll_init();
	tegra30_super_clk_init();
	tegra30_periph_clk_init();
	tegra_audio_clk_init(clk_base, pmc_base, tegra30_clks,
			     tegra30_audio_plls,
			     ARRAY_SIZE(tegra30_audio_plls), 24000000);

	tegra_init_dup_clks(tegra_clk_duplicates, clks, TEGRA30_CLK_CLK_MAX);

	tegra_add_of_provider(np, tegra30_clk_src_onecell_get);
	tegra_रेजिस्टर_devclks(devclks, ARRAY_SIZE(devclks));

	tegra_clk_apply_init_table = tegra30_घड़ी_apply_init_table;

	tegra_cpu_car_ops = &tegra30_cpu_car_ops;
पूर्ण
CLK_OF_DECLARE(tegra30, "nvidia,tegra30-car", tegra30_घड़ी_init);
