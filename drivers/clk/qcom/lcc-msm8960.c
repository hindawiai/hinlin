<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,lcc-msm8960.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "clk-regmap-divider.h"
#समावेश "clk-regmap-mux.h"

अटल काष्ठा clk_pll pll4 = अणु
	.l_reg = 0x4,
	.m_reg = 0x8,
	.n_reg = 0xc,
	.config_reg = 0x14,
	.mode_reg = 0x0,
	.status_reg = 0x18,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll4",
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	P_PXO,
	P_PLL4,
पूर्ण;

अटल स्थिर काष्ठा parent_map lcc_pxo_pll4_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL4, 2 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर lcc_pxo_pll4[] = अणु
	"pxo",
	"pll4_vote",
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_aअगर_osr_492[] = अणु
	अणु   512000, P_PLL4, 4, 1, 240 पूर्ण,
	अणु   768000, P_PLL4, 4, 1, 160 पूर्ण,
	अणु  1024000, P_PLL4, 4, 1, 120 पूर्ण,
	अणु  1536000, P_PLL4, 4, 1,  80 पूर्ण,
	अणु  2048000, P_PLL4, 4, 1,  60 पूर्ण,
	अणु  3072000, P_PLL4, 4, 1,  40 पूर्ण,
	अणु  4096000, P_PLL4, 4, 1,  30 पूर्ण,
	अणु  6144000, P_PLL4, 4, 1,  20 पूर्ण,
	अणु  8192000, P_PLL4, 4, 1,  15 पूर्ण,
	अणु 12288000, P_PLL4, 4, 1,  10 पूर्ण,
	अणु 24576000, P_PLL4, 4, 1,   5 पूर्ण,
	अणु 27000000, P_PXO,  1, 0,   0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_aअगर_osr_393[] = अणु
	अणु   512000, P_PLL4, 4, 1, 192 पूर्ण,
	अणु   768000, P_PLL4, 4, 1, 128 पूर्ण,
	अणु  1024000, P_PLL4, 4, 1,  96 पूर्ण,
	अणु  1536000, P_PLL4, 4, 1,  64 पूर्ण,
	अणु  2048000, P_PLL4, 4, 1,  48 पूर्ण,
	अणु  3072000, P_PLL4, 4, 1,  32 पूर्ण,
	अणु  4096000, P_PLL4, 4, 1,  24 पूर्ण,
	अणु  6144000, P_PLL4, 4, 1,  16 पूर्ण,
	अणु  8192000, P_PLL4, 4, 1,  12 पूर्ण,
	अणु 12288000, P_PLL4, 4, 1,   8 पूर्ण,
	अणु 24576000, P_PLL4, 4, 1,   4 पूर्ण,
	अणु 27000000, P_PXO,  1, 0,   0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg mi2s_osr_src = अणु
	.ns_reg = 0x48,
	.md_reg = 0x4c,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = lcc_pxo_pll4_map,
	पूर्ण,
	.freq_tbl = clk_tbl_aअगर_osr_393,
	.clkr = अणु
		.enable_reg = 0x48,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mi2s_osr_src",
			.parent_names = lcc_pxo_pll4,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lcc_mi2s_parents[] = अणु
	"mi2s_osr_src",
पूर्ण;

अटल काष्ठा clk_branch mi2s_osr_clk = अणु
	.halt_reg = 0x50,
	.halt_bit = 1,
	.halt_check = BRANCH_HALT_ENABLE,
	.clkr = अणु
		.enable_reg = 0x48,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mi2s_osr_clk",
			.parent_names = lcc_mi2s_parents,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_भाग mi2s_भाग_clk = अणु
	.reg = 0x48,
	.shअगरt = 10,
	.width = 4,
	.clkr = अणु
		.enable_reg = 0x48,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mi2s_div_clk",
			.parent_names = lcc_mi2s_parents,
			.num_parents = 1,
			.ops = &clk_regmap_भाग_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mi2s_bit_भाग_clk = अणु
	.halt_reg = 0x50,
	.halt_bit = 0,
	.halt_check = BRANCH_HALT_ENABLE,
	.clkr = अणु
		.enable_reg = 0x48,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mi2s_bit_div_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "mi2s_div_clk" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux mi2s_bit_clk = अणु
	.reg = 0x48,
	.shअगरt = 14,
	.width = 1,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mi2s_bit_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"mi2s_bit_div_clk",
				"mi2s_codec_clk",
			पूर्ण,
			.num_parents = 2,
			.ops = &clk_regmap_mux_बंदst_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा CLK_AIF_OSR_DIV(prefix, _ns, _md, hr)			\
अटल काष्ठा clk_rcg prefix##_osr_src = अणु			\
	.ns_reg = _ns,						\
	.md_reg = _md,						\
	.mn = अणु							\
		.mnctr_en_bit = 8,				\
		.mnctr_reset_bit = 7,				\
		.mnctr_mode_shअगरt = 5,				\
		.n_val_shअगरt = 24,				\
		.m_val_shअगरt = 8,				\
		.width = 8,					\
	पूर्ण,							\
	.p = अणु							\
		.pre_भाग_shअगरt = 3,				\
		.pre_भाग_width = 2,				\
	पूर्ण,							\
	.s = अणु							\
		.src_sel_shअगरt = 0,				\
		.parent_map = lcc_pxo_pll4_map,			\
	पूर्ण,							\
	.freq_tbl = clk_tbl_aअगर_osr_393,			\
	.clkr = अणु						\
		.enable_reg = _ns,				\
		.enable_mask = BIT(9),				\
		.hw.init = &(काष्ठा clk_init_data)अणु		\
			.name = #prefix "_osr_src",		\
			.parent_names = lcc_pxo_pll4,		\
			.num_parents = 2,			\
			.ops = &clk_rcg_ops,			\
			.flags = CLK_SET_RATE_GATE,		\
		पूर्ण,						\
	पूर्ण,							\
पूर्ण;								\
								\
अटल स्थिर अक्षर * स्थिर lcc_##prefix##_parents[] = अणु		\
	#prefix "_osr_src",					\
पूर्ण;								\
								\
अटल काष्ठा clk_branch prefix##_osr_clk = अणु			\
	.halt_reg = hr,						\
	.halt_bit = 1,						\
	.halt_check = BRANCH_HALT_ENABLE,			\
	.clkr = अणु						\
		.enable_reg = _ns,				\
		.enable_mask = BIT(21),				\
		.hw.init = &(काष्ठा clk_init_data)अणु		\
			.name = #prefix "_osr_clk",		\
			.parent_names = lcc_##prefix##_parents,	\
			.num_parents = 1,			\
			.ops = &clk_branch_ops,			\
			.flags = CLK_SET_RATE_PARENT,		\
		पूर्ण,						\
	पूर्ण,							\
पूर्ण;								\
								\
अटल काष्ठा clk_regmap_भाग prefix##_भाग_clk = अणु		\
	.reg = _ns,						\
	.shअगरt = 10,						\
	.width = 8,						\
	.clkr = अणु						\
		.hw.init = &(काष्ठा clk_init_data)अणु		\
			.name = #prefix "_div_clk",		\
			.parent_names = lcc_##prefix##_parents,	\
			.num_parents = 1,			\
			.ops = &clk_regmap_भाग_ops,		\
		पूर्ण,						\
	पूर्ण,							\
पूर्ण;								\
								\
अटल काष्ठा clk_branch prefix##_bit_भाग_clk = अणु		\
	.halt_reg = hr,						\
	.halt_bit = 0,						\
	.halt_check = BRANCH_HALT_ENABLE,			\
	.clkr = अणु						\
		.enable_reg = _ns,				\
		.enable_mask = BIT(19),				\
		.hw.init = &(काष्ठा clk_init_data)अणु		\
			.name = #prefix "_bit_div_clk",		\
			.parent_names = (स्थिर अक्षर *[])अणु	\
				#prefix "_div_clk"		\
			पूर्ण, 					\
			.num_parents = 1,			\
			.ops = &clk_branch_ops,			\
			.flags = CLK_SET_RATE_PARENT,		\
		पूर्ण,						\
	पूर्ण,							\
पूर्ण;								\
								\
अटल काष्ठा clk_regmap_mux prefix##_bit_clk = अणु		\
	.reg = _ns,						\
	.shअगरt = 18,						\
	.width = 1,						\
	.clkr = अणु						\
		.hw.init = &(काष्ठा clk_init_data)अणु		\
			.name = #prefix "_bit_clk",		\
			.parent_names = (स्थिर अक्षर *[])अणु	\
				#prefix "_bit_div_clk",		\
				#prefix "_codec_clk",		\
			पूर्ण,					\
			.num_parents = 2,			\
			.ops = &clk_regmap_mux_बंदst_ops,	\
			.flags = CLK_SET_RATE_PARENT,		\
		पूर्ण,						\
	पूर्ण,							\
पूर्ण

CLK_AIF_OSR_DIV(codec_i2s_mic, 0x60, 0x64, 0x68);
CLK_AIF_OSR_DIV(spare_i2s_mic, 0x78, 0x7c, 0x80);
CLK_AIF_OSR_DIV(codec_i2s_spkr, 0x6c, 0x70, 0x74);
CLK_AIF_OSR_DIV(spare_i2s_spkr, 0x84, 0x88, 0x8c);

अटल काष्ठा freq_tbl clk_tbl_pcm_492[] = अणु
	अणु   256000, P_PLL4, 4, 1, 480 पूर्ण,
	अणु   512000, P_PLL4, 4, 1, 240 पूर्ण,
	अणु   768000, P_PLL4, 4, 1, 160 पूर्ण,
	अणु  1024000, P_PLL4, 4, 1, 120 पूर्ण,
	अणु  1536000, P_PLL4, 4, 1,  80 पूर्ण,
	अणु  2048000, P_PLL4, 4, 1,  60 पूर्ण,
	अणु  3072000, P_PLL4, 4, 1,  40 पूर्ण,
	अणु  4096000, P_PLL4, 4, 1,  30 पूर्ण,
	अणु  6144000, P_PLL4, 4, 1,  20 पूर्ण,
	अणु  8192000, P_PLL4, 4, 1,  15 पूर्ण,
	अणु 12288000, P_PLL4, 4, 1,  10 पूर्ण,
	अणु 24576000, P_PLL4, 4, 1,   5 पूर्ण,
	अणु 27000000, P_PXO,  1, 0,   0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_pcm_393[] = अणु
	अणु   256000, P_PLL4, 4, 1, 384 पूर्ण,
	अणु   512000, P_PLL4, 4, 1, 192 पूर्ण,
	अणु   768000, P_PLL4, 4, 1, 128 पूर्ण,
	अणु  1024000, P_PLL4, 4, 1,  96 पूर्ण,
	अणु  1536000, P_PLL4, 4, 1,  64 पूर्ण,
	अणु  2048000, P_PLL4, 4, 1,  48 पूर्ण,
	अणु  3072000, P_PLL4, 4, 1,  32 पूर्ण,
	अणु  4096000, P_PLL4, 4, 1,  24 पूर्ण,
	अणु  6144000, P_PLL4, 4, 1,  16 पूर्ण,
	अणु  8192000, P_PLL4, 4, 1,  12 पूर्ण,
	अणु 12288000, P_PLL4, 4, 1,   8 पूर्ण,
	अणु 24576000, P_PLL4, 4, 1,   4 पूर्ण,
	अणु 27000000, P_PXO,  1, 0,   0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg pcm_src = अणु
	.ns_reg = 0x54,
	.md_reg = 0x58,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
		.width = 16,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = lcc_pxo_pll4_map,
	पूर्ण,
	.freq_tbl = clk_tbl_pcm_393,
	.clkr = अणु
		.enable_reg = 0x54,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcm_src",
			.parent_names = lcc_pxo_pll4,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pcm_clk_out = अणु
	.halt_reg = 0x5c,
	.halt_bit = 0,
	.halt_check = BRANCH_HALT_ENABLE,
	.clkr = अणु
		.enable_reg = 0x54,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcm_clk_out",
			.parent_names = (स्थिर अक्षर *[])अणु "pcm_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap_mux pcm_clk = अणु
	.reg = 0x54,
	.shअगरt = 10,
	.width = 1,
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcm_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcm_clk_out",
				"pcm_codec_clk",
			पूर्ण,
			.num_parents = 2,
			.ops = &clk_regmap_mux_बंदst_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg slimbus_src = अणु
	.ns_reg = 0xcc,
	.md_reg = 0xd0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 3,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = lcc_pxo_pll4_map,
	पूर्ण,
	.freq_tbl = clk_tbl_aअगर_osr_393,
	.clkr = अणु
		.enable_reg = 0xcc,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "slimbus_src",
			.parent_names = lcc_pxo_pll4,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lcc_slimbus_parents[] = अणु
	"slimbus_src",
पूर्ण;

अटल काष्ठा clk_branch audio_slimbus_clk = अणु
	.halt_reg = 0xd4,
	.halt_bit = 0,
	.halt_check = BRANCH_HALT_ENABLE,
	.clkr = अणु
		.enable_reg = 0xcc,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "audio_slimbus_clk",
			.parent_names = lcc_slimbus_parents,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch sps_slimbus_clk = अणु
	.halt_reg = 0xd4,
	.halt_bit = 1,
	.halt_check = BRANCH_HALT_ENABLE,
	.clkr = अणु
		.enable_reg = 0xcc,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "sps_slimbus_clk",
			.parent_names = lcc_slimbus_parents,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *lcc_msm8960_clks[] = अणु
	[PLL4] = &pll4.clkr,
	[MI2S_OSR_SRC] = &mi2s_osr_src.clkr,
	[MI2S_OSR_CLK] = &mi2s_osr_clk.clkr,
	[MI2S_DIV_CLK] = &mi2s_भाग_clk.clkr,
	[MI2S_BIT_DIV_CLK] = &mi2s_bit_भाग_clk.clkr,
	[MI2S_BIT_CLK] = &mi2s_bit_clk.clkr,
	[PCM_SRC] = &pcm_src.clkr,
	[PCM_CLK_OUT] = &pcm_clk_out.clkr,
	[PCM_CLK] = &pcm_clk.clkr,
	[SLIMBUS_SRC] = &slimbus_src.clkr,
	[AUDIO_SLIMBUS_CLK] = &audio_slimbus_clk.clkr,
	[SPS_SLIMBUS_CLK] = &sps_slimbus_clk.clkr,
	[CODEC_I2S_MIC_OSR_SRC] = &codec_i2s_mic_osr_src.clkr,
	[CODEC_I2S_MIC_OSR_CLK] = &codec_i2s_mic_osr_clk.clkr,
	[CODEC_I2S_MIC_DIV_CLK] = &codec_i2s_mic_भाग_clk.clkr,
	[CODEC_I2S_MIC_BIT_DIV_CLK] = &codec_i2s_mic_bit_भाग_clk.clkr,
	[CODEC_I2S_MIC_BIT_CLK] = &codec_i2s_mic_bit_clk.clkr,
	[SPARE_I2S_MIC_OSR_SRC] = &spare_i2s_mic_osr_src.clkr,
	[SPARE_I2S_MIC_OSR_CLK] = &spare_i2s_mic_osr_clk.clkr,
	[SPARE_I2S_MIC_DIV_CLK] = &spare_i2s_mic_भाग_clk.clkr,
	[SPARE_I2S_MIC_BIT_DIV_CLK] = &spare_i2s_mic_bit_भाग_clk.clkr,
	[SPARE_I2S_MIC_BIT_CLK] = &spare_i2s_mic_bit_clk.clkr,
	[CODEC_I2S_SPKR_OSR_SRC] = &codec_i2s_spkr_osr_src.clkr,
	[CODEC_I2S_SPKR_OSR_CLK] = &codec_i2s_spkr_osr_clk.clkr,
	[CODEC_I2S_SPKR_DIV_CLK] = &codec_i2s_spkr_भाग_clk.clkr,
	[CODEC_I2S_SPKR_BIT_DIV_CLK] = &codec_i2s_spkr_bit_भाग_clk.clkr,
	[CODEC_I2S_SPKR_BIT_CLK] = &codec_i2s_spkr_bit_clk.clkr,
	[SPARE_I2S_SPKR_OSR_SRC] = &spare_i2s_spkr_osr_src.clkr,
	[SPARE_I2S_SPKR_OSR_CLK] = &spare_i2s_spkr_osr_clk.clkr,
	[SPARE_I2S_SPKR_DIV_CLK] = &spare_i2s_spkr_भाग_clk.clkr,
	[SPARE_I2S_SPKR_BIT_DIV_CLK] = &spare_i2s_spkr_bit_भाग_clk.clkr,
	[SPARE_I2S_SPKR_BIT_CLK] = &spare_i2s_spkr_bit_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lcc_msm8960_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xfc,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lcc_msm8960_desc = अणु
	.config = &lcc_msm8960_regmap_config,
	.clks = lcc_msm8960_clks,
	.num_clks = ARRAY_SIZE(lcc_msm8960_clks),
पूर्ण;

अटल स्थिर काष्ठा of_device_id lcc_msm8960_match_table[] = अणु
	अणु .compatible = "qcom,lcc-msm8960" पूर्ण,
	अणु .compatible = "qcom,lcc-apq8064" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lcc_msm8960_match_table);

अटल पूर्णांक lcc_msm8960_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 val;
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &lcc_msm8960_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Use the correct frequency plan depending on speed of PLL4 */
	regmap_पढ़ो(regmap, 0x4, &val);
	अगर (val == 0x12) अणु
		slimbus_src.freq_tbl = clk_tbl_aअगर_osr_492;
		mi2s_osr_src.freq_tbl = clk_tbl_aअगर_osr_492;
		codec_i2s_mic_osr_src.freq_tbl = clk_tbl_aअगर_osr_492;
		spare_i2s_mic_osr_src.freq_tbl = clk_tbl_aअगर_osr_492;
		codec_i2s_spkr_osr_src.freq_tbl = clk_tbl_aअगर_osr_492;
		spare_i2s_spkr_osr_src.freq_tbl = clk_tbl_aअगर_osr_492;
		pcm_src.freq_tbl = clk_tbl_pcm_492;
	पूर्ण
	/* Enable PLL4 source on the LPASS Primary PLL Mux */
	regmap_ग_लिखो(regmap, 0xc4, 0x1);

	वापस qcom_cc_really_probe(pdev, &lcc_msm8960_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver lcc_msm8960_driver = अणु
	.probe		= lcc_msm8960_probe,
	.driver		= अणु
		.name	= "lcc-msm8960",
		.of_match_table = lcc_msm8960_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lcc_msm8960_driver);

MODULE_DESCRIPTION("QCOM LCC MSM8960 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lcc-msm8960");
