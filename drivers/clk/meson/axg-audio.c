<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>

#समावेश "axg-audio.h"
#समावेश "clk-regmap.h"
#समावेश "clk-phase.h"
#समावेश "sclk-div.h"

#घोषणा AUD_GATE(_name, _reg, _bit, _pname, _अगरlags) अणु			\
	.data = &(काष्ठा clk_regmap_gate_data)अणु				\
		.offset = (_reg),					\
		.bit_idx = (_bit),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = "aud_"#_name,					\
		.ops = &clk_regmap_gate_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु #_pname पूर्ण,		\
		.num_parents = 1,					\
		.flags = CLK_DUTY_CYCLE_PARENT | (_अगरlags),		\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_MUX(_name, _reg, _mask, _shअगरt, _dflags, _pdata, _अगरlags) अणु	\
	.data = &(काष्ठा clk_regmap_mux_data)अणु				\
		.offset = (_reg),					\
		.mask = (_mask),					\
		.shअगरt = (_shअगरt),					\
		.flags = (_dflags),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data)अणु				\
		.name = "aud_"#_name,					\
		.ops = &clk_regmap_mux_ops,				\
		.parent_data = _pdata,					\
		.num_parents = ARRAY_SIZE(_pdata),			\
		.flags = CLK_DUTY_CYCLE_PARENT | (_अगरlags),		\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_DIV(_name, _reg, _shअगरt, _width, _dflags, _pname, _अगरlags) अणु \
	.data = &(काष्ठा clk_regmap_भाग_data)अणु				\
		.offset = (_reg),					\
		.shअगरt = (_shअगरt),					\
		.width = (_width),					\
		.flags = (_dflags),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data)अणु				\
		.name = "aud_"#_name,					\
		.ops = &clk_regmap_भागider_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु #_pname पूर्ण,		\
		.num_parents = 1,					\
		.flags = (_अगरlags),					\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_PCLK_GATE(_name, _reg, _bit) अणु				\
	.data = &(काष्ठा clk_regmap_gate_data)अणु				\
		.offset = (_reg),					\
		.bit_idx = (_bit),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = "aud_"#_name,					\
		.ops = &clk_regmap_gate_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु "aud_top" पूर्ण,		\
		.num_parents = 1,					\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_SCLK_DIV(_name, _reg, _भाग_shअगरt, _भाग_width,		\
		     _hi_shअगरt, _hi_width, _pname, _अगरlags) अणु		\
	.data = &(काष्ठा meson_sclk_भाग_data) अणु				\
		.भाग = अणु						\
			.reg_off = (_reg),				\
			.shअगरt   = (_भाग_shअगरt),			\
			.width   = (_भाग_width),			\
		पूर्ण,							\
		.hi = अणु							\
			.reg_off = (_reg),				\
			.shअगरt   = (_hi_shअगरt),				\
			.width   = (_hi_width),				\
		पूर्ण,							\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = "aud_"#_name,					\
		.ops = &meson_sclk_भाग_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु #_pname पूर्ण,		\
		.num_parents = 1,					\
		.flags = (_अगरlags),					\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_TRIPHASE(_name, _reg, _width, _shअगरt0, _shअगरt1, _shअगरt2,	\
		     _pname, _अगरlags) अणु					\
	.data = &(काष्ठा meson_clk_triphase_data) अणु			\
		.ph0 = अणु						\
			.reg_off = (_reg),				\
			.shअगरt   = (_shअगरt0),				\
			.width   = (_width),				\
		पूर्ण,							\
		.ph1 = अणु						\
			.reg_off = (_reg),				\
			.shअगरt   = (_shअगरt1),				\
			.width   = (_width),				\
		पूर्ण,							\
		.ph2 = अणु						\
			.reg_off = (_reg),				\
			.shअगरt   = (_shअगरt2),				\
			.width   = (_width),				\
		पूर्ण,							\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = "aud_"#_name,					\
		.ops = &meson_clk_triphase_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु #_pname पूर्ण,		\
		.num_parents = 1,					\
		.flags = CLK_DUTY_CYCLE_PARENT | (_अगरlags),		\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_PHASE(_name, _reg, _width, _shअगरt, _pname, _अगरlags) अणु	\
	.data = &(काष्ठा meson_clk_phase_data) अणु			\
		.ph = अणु							\
			.reg_off = (_reg),				\
			.shअगरt   = (_shअगरt),				\
			.width   = (_width),				\
		पूर्ण,							\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = "aud_"#_name,					\
		.ops = &meson_clk_phase_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु #_pname पूर्ण,		\
		.num_parents = 1,					\
		.flags = (_अगरlags),					\
	पूर्ण,								\
पूर्ण

#घोषणा AUD_SCLK_WS(_name, _reg, _width, _shअगरt_ph, _shअगरt_ws, _pname,	\
		    _अगरlags) अणु						\
	.data = &(काष्ठा meson_sclk_ws_inv_data) अणु			\
		.ph = अणु							\
			.reg_off = (_reg),				\
			.shअगरt   = (_shअगरt_ph),				\
			.width   = (_width),				\
		पूर्ण,							\
		.ws = अणु							\
			.reg_off = (_reg),				\
			.shअगरt   = (_shअगरt_ws),				\
			.width   = (_width),				\
		पूर्ण,							\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = "aud_"#_name,					\
		.ops = &meson_clk_phase_ops,				\
		.parent_names = (स्थिर अक्षर *[])अणु #_pname पूर्ण,		\
		.num_parents = 1,					\
		.flags = (_अगरlags),					\
	पूर्ण,								\
पूर्ण

/* Audio Master Clocks */
अटल स्थिर काष्ठा clk_parent_data mst_mux_parent_data[] = अणु
	अणु .fw_name = "mst_in0", पूर्ण,
	अणु .fw_name = "mst_in1", पूर्ण,
	अणु .fw_name = "mst_in2", पूर्ण,
	अणु .fw_name = "mst_in3", पूर्ण,
	अणु .fw_name = "mst_in4", पूर्ण,
	अणु .fw_name = "mst_in5", पूर्ण,
	अणु .fw_name = "mst_in6", पूर्ण,
	अणु .fw_name = "mst_in7", पूर्ण,
पूर्ण;

#घोषणा AUD_MST_MUX(_name, _reg, _flag)					\
	AUD_MUX(_name##_sel, _reg, 0x7, 24, _flag,			\
		mst_mux_parent_data, 0)
#घोषणा AUD_MST_DIV(_name, _reg, _flag)					\
	AUD_DIV(_name##_भाग, _reg, 0, 16, _flag,			\
		aud_##_name##_sel, CLK_SET_RATE_PARENT)
#घोषणा AUD_MST_MCLK_GATE(_name, _reg)					\
	AUD_GATE(_name, _reg, 31, aud_##_name##_भाग,			\
		 CLK_SET_RATE_PARENT)

#घोषणा AUD_MST_MCLK_MUX(_name, _reg)					\
	AUD_MST_MUX(_name, _reg, CLK_MUX_ROUND_CLOSEST)
#घोषणा AUD_MST_MCLK_DIV(_name, _reg)					\
	AUD_MST_DIV(_name, _reg, CLK_DIVIDER_ROUND_CLOSEST)

#घोषणा AUD_MST_SYS_MUX(_name, _reg)					\
	AUD_MST_MUX(_name, _reg, 0)
#घोषणा AUD_MST_SYS_DIV(_name, _reg)					\
	AUD_MST_DIV(_name, _reg, 0)

/* Sample Clocks */
#घोषणा AUD_MST_SCLK_PRE_EN(_name, _reg)				\
	AUD_GATE(mst_##_name##_sclk_pre_en, _reg, 31,			\
		 aud_mst_##_name##_mclk, 0)
#घोषणा AUD_MST_SCLK_DIV(_name, _reg)					\
	AUD_SCLK_DIV(mst_##_name##_sclk_भाग, _reg, 20, 10, 0, 0,	\
		     aud_mst_##_name##_sclk_pre_en,			\
		     CLK_SET_RATE_PARENT)
#घोषणा AUD_MST_SCLK_POST_EN(_name, _reg)				\
	AUD_GATE(mst_##_name##_sclk_post_en, _reg, 30,			\
		 aud_mst_##_name##_sclk_भाग, CLK_SET_RATE_PARENT)
#घोषणा AUD_MST_SCLK(_name, _reg)					\
	AUD_TRIPHASE(mst_##_name##_sclk, _reg, 1, 0, 2, 4,		\
		     aud_mst_##_name##_sclk_post_en, CLK_SET_RATE_PARENT)

#घोषणा AUD_MST_LRCLK_DIV(_name, _reg)					\
	AUD_SCLK_DIV(mst_##_name##_lrclk_भाग, _reg, 0, 10, 10, 10,	\
		     aud_mst_##_name##_sclk_post_en, 0)
#घोषणा AUD_MST_LRCLK(_name, _reg)					\
	AUD_TRIPHASE(mst_##_name##_lrclk, _reg, 1, 1, 3, 5,		\
		     aud_mst_##_name##_lrclk_भाग, CLK_SET_RATE_PARENT)

/* TDM bit घड़ी sources */
अटल स्थिर काष्ठा clk_parent_data tdm_sclk_parent_data[] = अणु
	अणु .name = "aud_mst_a_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_b_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_c_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_d_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_e_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_f_sclk", .index = -1, पूर्ण,
	अणु .fw_name = "slv_sclk0", पूर्ण,
	अणु .fw_name = "slv_sclk1", पूर्ण,
	अणु .fw_name = "slv_sclk2", पूर्ण,
	अणु .fw_name = "slv_sclk3", पूर्ण,
	अणु .fw_name = "slv_sclk4", पूर्ण,
	अणु .fw_name = "slv_sclk5", पूर्ण,
	अणु .fw_name = "slv_sclk6", पूर्ण,
	अणु .fw_name = "slv_sclk7", पूर्ण,
	अणु .fw_name = "slv_sclk8", पूर्ण,
	अणु .fw_name = "slv_sclk9", पूर्ण,
पूर्ण;

/* TDM sample घड़ी sources */
अटल स्थिर काष्ठा clk_parent_data tdm_lrclk_parent_data[] = अणु
	अणु .name = "aud_mst_a_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_b_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_c_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_d_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_e_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_f_lrclk", .index = -1, पूर्ण,
	अणु .fw_name = "slv_lrclk0", पूर्ण,
	अणु .fw_name = "slv_lrclk1", पूर्ण,
	अणु .fw_name = "slv_lrclk2", पूर्ण,
	अणु .fw_name = "slv_lrclk3", पूर्ण,
	अणु .fw_name = "slv_lrclk4", पूर्ण,
	अणु .fw_name = "slv_lrclk5", पूर्ण,
	अणु .fw_name = "slv_lrclk6", पूर्ण,
	अणु .fw_name = "slv_lrclk7", पूर्ण,
	अणु .fw_name = "slv_lrclk8", पूर्ण,
	अणु .fw_name = "slv_lrclk9", पूर्ण,
पूर्ण;

#घोषणा AUD_TDM_SCLK_MUX(_name, _reg)					\
	AUD_MUX(tdm##_name##_sclk_sel, _reg, 0xf, 24,			\
		CLK_MUX_ROUND_CLOSEST, tdm_sclk_parent_data, 0)
#घोषणा AUD_TDM_SCLK_PRE_EN(_name, _reg)				\
	AUD_GATE(tdm##_name##_sclk_pre_en, _reg, 31,			\
		 aud_tdm##_name##_sclk_sel, CLK_SET_RATE_PARENT)
#घोषणा AUD_TDM_SCLK_POST_EN(_name, _reg)				\
	AUD_GATE(tdm##_name##_sclk_post_en, _reg, 30,			\
		 aud_tdm##_name##_sclk_pre_en, CLK_SET_RATE_PARENT)
#घोषणा AUD_TDM_SCLK(_name, _reg)					\
	AUD_PHASE(tdm##_name##_sclk, _reg, 1, 29,			\
		  aud_tdm##_name##_sclk_post_en,			\
		  CLK_DUTY_CYCLE_PARENT | CLK_SET_RATE_PARENT)
#घोषणा AUD_TDM_SCLK_WS(_name, _reg)					\
	AUD_SCLK_WS(tdm##_name##_sclk, _reg, 1, 29, 28,			\
		    aud_tdm##_name##_sclk_post_en,			\
		    CLK_DUTY_CYCLE_PARENT | CLK_SET_RATE_PARENT)

#घोषणा AUD_TDM_LRLCK(_name, _reg)					\
	AUD_MUX(tdm##_name##_lrclk, _reg, 0xf, 20,			\
		CLK_MUX_ROUND_CLOSEST, tdm_lrclk_parent_data, 0)

/* Pad master घड़ी sources */
अटल स्थिर काष्ठा clk_parent_data mclk_pad_ctrl_parent_data[] = अणु
	अणु .name = "aud_mst_a_mclk", .index = -1,  पूर्ण,
	अणु .name = "aud_mst_b_mclk", .index = -1,  पूर्ण,
	अणु .name = "aud_mst_c_mclk", .index = -1,  पूर्ण,
	अणु .name = "aud_mst_d_mclk", .index = -1,  पूर्ण,
	अणु .name = "aud_mst_e_mclk", .index = -1,  पूर्ण,
	अणु .name = "aud_mst_f_mclk", .index = -1,  पूर्ण,
पूर्ण;

/* Pad bit घड़ी sources */
अटल स्थिर काष्ठा clk_parent_data sclk_pad_ctrl_parent_data[] = अणु
	अणु .name = "aud_mst_a_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_b_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_c_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_d_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_e_sclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_f_sclk", .index = -1, पूर्ण,
पूर्ण;

/* Pad sample घड़ी sources */
अटल स्थिर काष्ठा clk_parent_data lrclk_pad_ctrl_parent_data[] = अणु
	अणु .name = "aud_mst_a_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_b_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_c_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_d_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_e_lrclk", .index = -1, पूर्ण,
	अणु .name = "aud_mst_f_lrclk", .index = -1, पूर्ण,
पूर्ण;

#घोषणा AUD_TDM_PAD_CTRL(_name, _reg, _shअगरt, _parents)		\
	AUD_MUX(_name, _reg, 0x7, _shअगरt, 0, _parents,		\
		CLK_SET_RATE_NO_REPARENT)

/* Common Clocks */
अटल काष्ठा clk_regmap ddr_arb =
	AUD_PCLK_GATE(ddr_arb, AUDIO_CLK_GATE_EN, 0);
अटल काष्ठा clk_regmap pdm =
	AUD_PCLK_GATE(pdm, AUDIO_CLK_GATE_EN, 1);
अटल काष्ठा clk_regmap tdmin_a =
	AUD_PCLK_GATE(tdmin_a, AUDIO_CLK_GATE_EN, 2);
अटल काष्ठा clk_regmap tdmin_b =
	AUD_PCLK_GATE(tdmin_b, AUDIO_CLK_GATE_EN, 3);
अटल काष्ठा clk_regmap tdmin_c =
	AUD_PCLK_GATE(tdmin_c, AUDIO_CLK_GATE_EN, 4);
अटल काष्ठा clk_regmap tdmin_lb =
	AUD_PCLK_GATE(tdmin_lb, AUDIO_CLK_GATE_EN, 5);
अटल काष्ठा clk_regmap tdmout_a =
	AUD_PCLK_GATE(tdmout_a, AUDIO_CLK_GATE_EN, 6);
अटल काष्ठा clk_regmap tdmout_b =
	AUD_PCLK_GATE(tdmout_b, AUDIO_CLK_GATE_EN, 7);
अटल काष्ठा clk_regmap tdmout_c =
	AUD_PCLK_GATE(tdmout_c, AUDIO_CLK_GATE_EN, 8);
अटल काष्ठा clk_regmap frddr_a =
	AUD_PCLK_GATE(frddr_a, AUDIO_CLK_GATE_EN, 9);
अटल काष्ठा clk_regmap frddr_b =
	AUD_PCLK_GATE(frddr_b, AUDIO_CLK_GATE_EN, 10);
अटल काष्ठा clk_regmap frddr_c =
	AUD_PCLK_GATE(frddr_c, AUDIO_CLK_GATE_EN, 11);
अटल काष्ठा clk_regmap toddr_a =
	AUD_PCLK_GATE(toddr_a, AUDIO_CLK_GATE_EN, 12);
अटल काष्ठा clk_regmap toddr_b =
	AUD_PCLK_GATE(toddr_b, AUDIO_CLK_GATE_EN, 13);
अटल काष्ठा clk_regmap toddr_c =
	AUD_PCLK_GATE(toddr_c, AUDIO_CLK_GATE_EN, 14);
अटल काष्ठा clk_regmap loopback =
	AUD_PCLK_GATE(loopback, AUDIO_CLK_GATE_EN, 15);
अटल काष्ठा clk_regmap spdअगरin =
	AUD_PCLK_GATE(spdअगरin, AUDIO_CLK_GATE_EN, 16);
अटल काष्ठा clk_regmap spdअगरout =
	AUD_PCLK_GATE(spdअगरout, AUDIO_CLK_GATE_EN, 17);
अटल काष्ठा clk_regmap resample =
	AUD_PCLK_GATE(resample, AUDIO_CLK_GATE_EN, 18);
अटल काष्ठा clk_regmap घातer_detect =
	AUD_PCLK_GATE(घातer_detect, AUDIO_CLK_GATE_EN, 19);

अटल काष्ठा clk_regmap spdअगरout_clk_sel =
	AUD_MST_MCLK_MUX(spdअगरout_clk, AUDIO_CLK_SPDIFOUT_CTRL);
अटल काष्ठा clk_regmap pdm_dclk_sel =
	AUD_MST_MCLK_MUX(pdm_dclk, AUDIO_CLK_PDMIN_CTRL0);
अटल काष्ठा clk_regmap spdअगरin_clk_sel =
	AUD_MST_SYS_MUX(spdअगरin_clk, AUDIO_CLK_SPDIFIN_CTRL);
अटल काष्ठा clk_regmap pdm_sysclk_sel =
	AUD_MST_SYS_MUX(pdm_sysclk, AUDIO_CLK_PDMIN_CTRL1);
अटल काष्ठा clk_regmap spdअगरout_b_clk_sel =
	AUD_MST_MCLK_MUX(spdअगरout_b_clk, AUDIO_CLK_SPDIFOUT_B_CTRL);

अटल काष्ठा clk_regmap spdअगरout_clk_भाग =
	AUD_MST_MCLK_DIV(spdअगरout_clk, AUDIO_CLK_SPDIFOUT_CTRL);
अटल काष्ठा clk_regmap pdm_dclk_भाग =
	AUD_MST_MCLK_DIV(pdm_dclk, AUDIO_CLK_PDMIN_CTRL0);
अटल काष्ठा clk_regmap spdअगरin_clk_भाग =
	AUD_MST_SYS_DIV(spdअगरin_clk, AUDIO_CLK_SPDIFIN_CTRL);
अटल काष्ठा clk_regmap pdm_sysclk_भाग =
	AUD_MST_SYS_DIV(pdm_sysclk, AUDIO_CLK_PDMIN_CTRL1);
अटल काष्ठा clk_regmap spdअगरout_b_clk_भाग =
	AUD_MST_MCLK_DIV(spdअगरout_b_clk, AUDIO_CLK_SPDIFOUT_B_CTRL);

अटल काष्ठा clk_regmap spdअगरout_clk =
	AUD_MST_MCLK_GATE(spdअगरout_clk, AUDIO_CLK_SPDIFOUT_CTRL);
अटल काष्ठा clk_regmap spdअगरin_clk =
	AUD_MST_MCLK_GATE(spdअगरin_clk, AUDIO_CLK_SPDIFIN_CTRL);
अटल काष्ठा clk_regmap pdm_dclk =
	AUD_MST_MCLK_GATE(pdm_dclk, AUDIO_CLK_PDMIN_CTRL0);
अटल काष्ठा clk_regmap pdm_sysclk =
	AUD_MST_MCLK_GATE(pdm_sysclk, AUDIO_CLK_PDMIN_CTRL1);
अटल काष्ठा clk_regmap spdअगरout_b_clk =
	AUD_MST_MCLK_GATE(spdअगरout_b_clk, AUDIO_CLK_SPDIFOUT_B_CTRL);

अटल काष्ठा clk_regmap mst_a_sclk_pre_en =
	AUD_MST_SCLK_PRE_EN(a, AUDIO_MST_A_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_b_sclk_pre_en =
	AUD_MST_SCLK_PRE_EN(b, AUDIO_MST_B_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_c_sclk_pre_en =
	AUD_MST_SCLK_PRE_EN(c, AUDIO_MST_C_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_d_sclk_pre_en =
	AUD_MST_SCLK_PRE_EN(d, AUDIO_MST_D_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_e_sclk_pre_en =
	AUD_MST_SCLK_PRE_EN(e, AUDIO_MST_E_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_f_sclk_pre_en =
	AUD_MST_SCLK_PRE_EN(f, AUDIO_MST_F_SCLK_CTRL0);

अटल काष्ठा clk_regmap mst_a_sclk_भाग =
	AUD_MST_SCLK_DIV(a, AUDIO_MST_A_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_b_sclk_भाग =
	AUD_MST_SCLK_DIV(b, AUDIO_MST_B_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_c_sclk_भाग =
	AUD_MST_SCLK_DIV(c, AUDIO_MST_C_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_d_sclk_भाग =
	AUD_MST_SCLK_DIV(d, AUDIO_MST_D_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_e_sclk_भाग =
	AUD_MST_SCLK_DIV(e, AUDIO_MST_E_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_f_sclk_भाग =
	AUD_MST_SCLK_DIV(f, AUDIO_MST_F_SCLK_CTRL0);

अटल काष्ठा clk_regmap mst_a_sclk_post_en =
	AUD_MST_SCLK_POST_EN(a, AUDIO_MST_A_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_b_sclk_post_en =
	AUD_MST_SCLK_POST_EN(b, AUDIO_MST_B_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_c_sclk_post_en =
	AUD_MST_SCLK_POST_EN(c, AUDIO_MST_C_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_d_sclk_post_en =
	AUD_MST_SCLK_POST_EN(d, AUDIO_MST_D_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_e_sclk_post_en =
	AUD_MST_SCLK_POST_EN(e, AUDIO_MST_E_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_f_sclk_post_en =
	AUD_MST_SCLK_POST_EN(f, AUDIO_MST_F_SCLK_CTRL0);

अटल काष्ठा clk_regmap mst_a_sclk =
	AUD_MST_SCLK(a, AUDIO_MST_A_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_b_sclk =
	AUD_MST_SCLK(b, AUDIO_MST_B_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_c_sclk =
	AUD_MST_SCLK(c, AUDIO_MST_C_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_d_sclk =
	AUD_MST_SCLK(d, AUDIO_MST_D_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_e_sclk =
	AUD_MST_SCLK(e, AUDIO_MST_E_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_f_sclk =
	AUD_MST_SCLK(f, AUDIO_MST_F_SCLK_CTRL1);

अटल काष्ठा clk_regmap mst_a_lrclk_भाग =
	AUD_MST_LRCLK_DIV(a, AUDIO_MST_A_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_b_lrclk_भाग =
	AUD_MST_LRCLK_DIV(b, AUDIO_MST_B_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_c_lrclk_भाग =
	AUD_MST_LRCLK_DIV(c, AUDIO_MST_C_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_d_lrclk_भाग =
	AUD_MST_LRCLK_DIV(d, AUDIO_MST_D_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_e_lrclk_भाग =
	AUD_MST_LRCLK_DIV(e, AUDIO_MST_E_SCLK_CTRL0);
अटल काष्ठा clk_regmap mst_f_lrclk_भाग =
	AUD_MST_LRCLK_DIV(f, AUDIO_MST_F_SCLK_CTRL0);

अटल काष्ठा clk_regmap mst_a_lrclk =
	AUD_MST_LRCLK(a, AUDIO_MST_A_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_b_lrclk =
	AUD_MST_LRCLK(b, AUDIO_MST_B_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_c_lrclk =
	AUD_MST_LRCLK(c, AUDIO_MST_C_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_d_lrclk =
	AUD_MST_LRCLK(d, AUDIO_MST_D_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_e_lrclk =
	AUD_MST_LRCLK(e, AUDIO_MST_E_SCLK_CTRL1);
अटल काष्ठा clk_regmap mst_f_lrclk =
	AUD_MST_LRCLK(f, AUDIO_MST_F_SCLK_CTRL1);

अटल काष्ठा clk_regmap tdmin_a_sclk_sel =
	AUD_TDM_SCLK_MUX(in_a, AUDIO_CLK_TDMIN_A_CTRL);
अटल काष्ठा clk_regmap tdmin_b_sclk_sel =
	AUD_TDM_SCLK_MUX(in_b, AUDIO_CLK_TDMIN_B_CTRL);
अटल काष्ठा clk_regmap tdmin_c_sclk_sel =
	AUD_TDM_SCLK_MUX(in_c, AUDIO_CLK_TDMIN_C_CTRL);
अटल काष्ठा clk_regmap tdmin_lb_sclk_sel =
	AUD_TDM_SCLK_MUX(in_lb, AUDIO_CLK_TDMIN_LB_CTRL);
अटल काष्ठा clk_regmap tdmout_a_sclk_sel =
	AUD_TDM_SCLK_MUX(out_a, AUDIO_CLK_TDMOUT_A_CTRL);
अटल काष्ठा clk_regmap tdmout_b_sclk_sel =
	AUD_TDM_SCLK_MUX(out_b, AUDIO_CLK_TDMOUT_B_CTRL);
अटल काष्ठा clk_regmap tdmout_c_sclk_sel =
	AUD_TDM_SCLK_MUX(out_c, AUDIO_CLK_TDMOUT_C_CTRL);

अटल काष्ठा clk_regmap tdmin_a_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(in_a, AUDIO_CLK_TDMIN_A_CTRL);
अटल काष्ठा clk_regmap tdmin_b_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(in_b, AUDIO_CLK_TDMIN_B_CTRL);
अटल काष्ठा clk_regmap tdmin_c_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(in_c, AUDIO_CLK_TDMIN_C_CTRL);
अटल काष्ठा clk_regmap tdmin_lb_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(in_lb, AUDIO_CLK_TDMIN_LB_CTRL);
अटल काष्ठा clk_regmap tdmout_a_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(out_a, AUDIO_CLK_TDMOUT_A_CTRL);
अटल काष्ठा clk_regmap tdmout_b_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(out_b, AUDIO_CLK_TDMOUT_B_CTRL);
अटल काष्ठा clk_regmap tdmout_c_sclk_pre_en =
	AUD_TDM_SCLK_PRE_EN(out_c, AUDIO_CLK_TDMOUT_C_CTRL);

अटल काष्ठा clk_regmap tdmin_a_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(in_a, AUDIO_CLK_TDMIN_A_CTRL);
अटल काष्ठा clk_regmap tdmin_b_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(in_b, AUDIO_CLK_TDMIN_B_CTRL);
अटल काष्ठा clk_regmap tdmin_c_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(in_c, AUDIO_CLK_TDMIN_C_CTRL);
अटल काष्ठा clk_regmap tdmin_lb_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(in_lb, AUDIO_CLK_TDMIN_LB_CTRL);
अटल काष्ठा clk_regmap tdmout_a_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(out_a, AUDIO_CLK_TDMOUT_A_CTRL);
अटल काष्ठा clk_regmap tdmout_b_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(out_b, AUDIO_CLK_TDMOUT_B_CTRL);
अटल काष्ठा clk_regmap tdmout_c_sclk_post_en =
	AUD_TDM_SCLK_POST_EN(out_c, AUDIO_CLK_TDMOUT_C_CTRL);

अटल काष्ठा clk_regmap tdmin_a_sclk =
	AUD_TDM_SCLK(in_a, AUDIO_CLK_TDMIN_A_CTRL);
अटल काष्ठा clk_regmap tdmin_b_sclk =
	AUD_TDM_SCLK(in_b, AUDIO_CLK_TDMIN_B_CTRL);
अटल काष्ठा clk_regmap tdmin_c_sclk =
	AUD_TDM_SCLK(in_c, AUDIO_CLK_TDMIN_C_CTRL);
अटल काष्ठा clk_regmap tdmin_lb_sclk =
	AUD_TDM_SCLK(in_lb, AUDIO_CLK_TDMIN_LB_CTRL);

अटल काष्ठा clk_regmap tdmin_a_lrclk =
	AUD_TDM_LRLCK(in_a, AUDIO_CLK_TDMIN_A_CTRL);
अटल काष्ठा clk_regmap tdmin_b_lrclk =
	AUD_TDM_LRLCK(in_b, AUDIO_CLK_TDMIN_B_CTRL);
अटल काष्ठा clk_regmap tdmin_c_lrclk =
	AUD_TDM_LRLCK(in_c, AUDIO_CLK_TDMIN_C_CTRL);
अटल काष्ठा clk_regmap tdmin_lb_lrclk =
	AUD_TDM_LRLCK(in_lb, AUDIO_CLK_TDMIN_LB_CTRL);
अटल काष्ठा clk_regmap tdmout_a_lrclk =
	AUD_TDM_LRLCK(out_a, AUDIO_CLK_TDMOUT_A_CTRL);
अटल काष्ठा clk_regmap tdmout_b_lrclk =
	AUD_TDM_LRLCK(out_b, AUDIO_CLK_TDMOUT_B_CTRL);
अटल काष्ठा clk_regmap tdmout_c_lrclk =
	AUD_TDM_LRLCK(out_c, AUDIO_CLK_TDMOUT_C_CTRL);

/* AXG Clocks */
अटल काष्ठा clk_regmap axg_tdmout_a_sclk =
	AUD_TDM_SCLK(out_a, AUDIO_CLK_TDMOUT_A_CTRL);
अटल काष्ठा clk_regmap axg_tdmout_b_sclk =
	AUD_TDM_SCLK(out_b, AUDIO_CLK_TDMOUT_B_CTRL);
अटल काष्ठा clk_regmap axg_tdmout_c_sclk =
	AUD_TDM_SCLK(out_c, AUDIO_CLK_TDMOUT_C_CTRL);

/* AXG/G12A Clocks */
अटल काष्ठा clk_hw axg_aud_top = अणु
	.init = &(काष्ठा clk_init_data) अणु
		/* Provide aud_top संकेत name on axg and g12a */
		.name = "aud_top",
		.ops = &(स्थिर काष्ठा clk_ops) अणुपूर्ण,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "pclk",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap mst_a_mclk_sel =
	AUD_MST_MCLK_MUX(mst_a_mclk, AUDIO_MCLK_A_CTRL);
अटल काष्ठा clk_regmap mst_b_mclk_sel =
	AUD_MST_MCLK_MUX(mst_b_mclk, AUDIO_MCLK_B_CTRL);
अटल काष्ठा clk_regmap mst_c_mclk_sel =
	AUD_MST_MCLK_MUX(mst_c_mclk, AUDIO_MCLK_C_CTRL);
अटल काष्ठा clk_regmap mst_d_mclk_sel =
	AUD_MST_MCLK_MUX(mst_d_mclk, AUDIO_MCLK_D_CTRL);
अटल काष्ठा clk_regmap mst_e_mclk_sel =
	AUD_MST_MCLK_MUX(mst_e_mclk, AUDIO_MCLK_E_CTRL);
अटल काष्ठा clk_regmap mst_f_mclk_sel =
	AUD_MST_MCLK_MUX(mst_f_mclk, AUDIO_MCLK_F_CTRL);

अटल काष्ठा clk_regmap mst_a_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_a_mclk, AUDIO_MCLK_A_CTRL);
अटल काष्ठा clk_regmap mst_b_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_b_mclk, AUDIO_MCLK_B_CTRL);
अटल काष्ठा clk_regmap mst_c_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_c_mclk, AUDIO_MCLK_C_CTRL);
अटल काष्ठा clk_regmap mst_d_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_d_mclk, AUDIO_MCLK_D_CTRL);
अटल काष्ठा clk_regmap mst_e_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_e_mclk, AUDIO_MCLK_E_CTRL);
अटल काष्ठा clk_regmap mst_f_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_f_mclk, AUDIO_MCLK_F_CTRL);

अटल काष्ठा clk_regmap mst_a_mclk =
	AUD_MST_MCLK_GATE(mst_a_mclk, AUDIO_MCLK_A_CTRL);
अटल काष्ठा clk_regmap mst_b_mclk =
	AUD_MST_MCLK_GATE(mst_b_mclk, AUDIO_MCLK_B_CTRL);
अटल काष्ठा clk_regmap mst_c_mclk =
	AUD_MST_MCLK_GATE(mst_c_mclk, AUDIO_MCLK_C_CTRL);
अटल काष्ठा clk_regmap mst_d_mclk =
	AUD_MST_MCLK_GATE(mst_d_mclk, AUDIO_MCLK_D_CTRL);
अटल काष्ठा clk_regmap mst_e_mclk =
	AUD_MST_MCLK_GATE(mst_e_mclk, AUDIO_MCLK_E_CTRL);
अटल काष्ठा clk_regmap mst_f_mclk =
	AUD_MST_MCLK_GATE(mst_f_mclk, AUDIO_MCLK_F_CTRL);

/* G12a घड़ीs */
अटल काष्ठा clk_regmap g12a_tdm_mclk_pad_0 = AUD_TDM_PAD_CTRL(
	mclk_pad_0, AUDIO_MST_PAD_CTRL0, 0, mclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_mclk_pad_1 = AUD_TDM_PAD_CTRL(
	mclk_pad_1, AUDIO_MST_PAD_CTRL0, 4, mclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_lrclk_pad_0 = AUD_TDM_PAD_CTRL(
	lrclk_pad_0, AUDIO_MST_PAD_CTRL1, 16, lrclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_lrclk_pad_1 = AUD_TDM_PAD_CTRL(
	lrclk_pad_1, AUDIO_MST_PAD_CTRL1, 20, lrclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_lrclk_pad_2 = AUD_TDM_PAD_CTRL(
	lrclk_pad_2, AUDIO_MST_PAD_CTRL1, 24, lrclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_sclk_pad_0 = AUD_TDM_PAD_CTRL(
	sclk_pad_0, AUDIO_MST_PAD_CTRL1, 0, sclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_sclk_pad_1 = AUD_TDM_PAD_CTRL(
	sclk_pad_1, AUDIO_MST_PAD_CTRL1, 4, sclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap g12a_tdm_sclk_pad_2 = AUD_TDM_PAD_CTRL(
	sclk_pad_2, AUDIO_MST_PAD_CTRL1, 8, sclk_pad_ctrl_parent_data);

अटल काष्ठा clk_regmap g12a_tdmout_a_sclk =
	AUD_TDM_SCLK_WS(out_a, AUDIO_CLK_TDMOUT_A_CTRL);
अटल काष्ठा clk_regmap g12a_tdmout_b_sclk =
	AUD_TDM_SCLK_WS(out_b, AUDIO_CLK_TDMOUT_B_CTRL);
अटल काष्ठा clk_regmap g12a_tdmout_c_sclk =
	AUD_TDM_SCLK_WS(out_c, AUDIO_CLK_TDMOUT_C_CTRL);

अटल काष्ठा clk_regmap toram =
	AUD_PCLK_GATE(toram, AUDIO_CLK_GATE_EN, 20);
अटल काष्ठा clk_regmap spdअगरout_b =
	AUD_PCLK_GATE(spdअगरout_b, AUDIO_CLK_GATE_EN, 21);
अटल काष्ठा clk_regmap eqdrc =
	AUD_PCLK_GATE(eqdrc, AUDIO_CLK_GATE_EN, 22);

/* SM1 Clocks */
अटल काष्ठा clk_regmap sm1_clk81_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AUDIO_CLK81_EN,
		.bit_idx = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "aud_clk81_en",
		.ops = &clk_regmap_gate_ops,
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु
			.fw_name = "pclk",
		पूर्ण,
		.num_parents = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_sysclk_a_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = AUDIO_CLK81_CTRL,
		.shअगरt = 0,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "aud_sysclk_a_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_clk81_en.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_sysclk_a_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AUDIO_CLK81_CTRL,
		.bit_idx = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "aud_sysclk_a_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_sysclk_a_भाग.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_sysclk_b_भाग = अणु
	.data = &(काष्ठा clk_regmap_भाग_data)अणु
		.offset = AUDIO_CLK81_CTRL,
		.shअगरt = 16,
		.width = 8,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "aud_sysclk_b_div",
		.ops = &clk_regmap_भागider_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_clk81_en.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap sm1_sysclk_b_en = अणु
	.data = &(काष्ठा clk_regmap_gate_data)अणु
		.offset = AUDIO_CLK81_CTRL,
		.bit_idx = 24,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "aud_sysclk_b_en",
		.ops = &clk_regmap_gate_ops,
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु
			&sm1_sysclk_b_भाग.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_hw *sm1_aud_top_parents[] = अणु
	&sm1_sysclk_a_en.hw,
	&sm1_sysclk_b_en.hw,
पूर्ण;

अटल काष्ठा clk_regmap sm1_aud_top = अणु
	.data = &(काष्ठा clk_regmap_mux_data)अणु
		.offset = AUDIO_CLK81_CTRL,
		.mask = 0x1,
		.shअगरt = 31,
	पूर्ण,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "aud_top",
		.ops = &clk_regmap_mux_ops,
		.parent_hws = sm1_aud_top_parents,
		.num_parents = ARRAY_SIZE(sm1_aud_top_parents),
		.flags = CLK_SET_RATE_NO_REPARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap resample_b =
	AUD_PCLK_GATE(resample_b, AUDIO_CLK_GATE_EN, 26);
अटल काष्ठा clk_regmap tovad =
	AUD_PCLK_GATE(tovad, AUDIO_CLK_GATE_EN, 27);
अटल काष्ठा clk_regmap locker =
	AUD_PCLK_GATE(locker, AUDIO_CLK_GATE_EN, 28);
अटल काष्ठा clk_regmap spdअगरin_lb =
	AUD_PCLK_GATE(spdअगरin_lb, AUDIO_CLK_GATE_EN, 29);
अटल काष्ठा clk_regmap frddr_d =
	AUD_PCLK_GATE(frddr_d, AUDIO_CLK_GATE_EN1, 0);
अटल काष्ठा clk_regmap toddr_d =
	AUD_PCLK_GATE(toddr_d, AUDIO_CLK_GATE_EN1, 1);
अटल काष्ठा clk_regmap loopback_b =
	AUD_PCLK_GATE(loopback_b, AUDIO_CLK_GATE_EN1, 2);

अटल काष्ठा clk_regmap sm1_mst_a_mclk_sel =
	AUD_MST_MCLK_MUX(mst_a_mclk, AUDIO_SM1_MCLK_A_CTRL);
अटल काष्ठा clk_regmap sm1_mst_b_mclk_sel =
	AUD_MST_MCLK_MUX(mst_b_mclk, AUDIO_SM1_MCLK_B_CTRL);
अटल काष्ठा clk_regmap sm1_mst_c_mclk_sel =
	AUD_MST_MCLK_MUX(mst_c_mclk, AUDIO_SM1_MCLK_C_CTRL);
अटल काष्ठा clk_regmap sm1_mst_d_mclk_sel =
	AUD_MST_MCLK_MUX(mst_d_mclk, AUDIO_SM1_MCLK_D_CTRL);
अटल काष्ठा clk_regmap sm1_mst_e_mclk_sel =
	AUD_MST_MCLK_MUX(mst_e_mclk, AUDIO_SM1_MCLK_E_CTRL);
अटल काष्ठा clk_regmap sm1_mst_f_mclk_sel =
	AUD_MST_MCLK_MUX(mst_f_mclk, AUDIO_SM1_MCLK_F_CTRL);

अटल काष्ठा clk_regmap sm1_mst_a_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_a_mclk, AUDIO_SM1_MCLK_A_CTRL);
अटल काष्ठा clk_regmap sm1_mst_b_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_b_mclk, AUDIO_SM1_MCLK_B_CTRL);
अटल काष्ठा clk_regmap sm1_mst_c_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_c_mclk, AUDIO_SM1_MCLK_C_CTRL);
अटल काष्ठा clk_regmap sm1_mst_d_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_d_mclk, AUDIO_SM1_MCLK_D_CTRL);
अटल काष्ठा clk_regmap sm1_mst_e_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_e_mclk, AUDIO_SM1_MCLK_E_CTRL);
अटल काष्ठा clk_regmap sm1_mst_f_mclk_भाग =
	AUD_MST_MCLK_DIV(mst_f_mclk, AUDIO_SM1_MCLK_F_CTRL);

अटल काष्ठा clk_regmap sm1_mst_a_mclk =
	AUD_MST_MCLK_GATE(mst_a_mclk, AUDIO_SM1_MCLK_A_CTRL);
अटल काष्ठा clk_regmap sm1_mst_b_mclk =
	AUD_MST_MCLK_GATE(mst_b_mclk, AUDIO_SM1_MCLK_B_CTRL);
अटल काष्ठा clk_regmap sm1_mst_c_mclk =
	AUD_MST_MCLK_GATE(mst_c_mclk, AUDIO_SM1_MCLK_C_CTRL);
अटल काष्ठा clk_regmap sm1_mst_d_mclk =
	AUD_MST_MCLK_GATE(mst_d_mclk, AUDIO_SM1_MCLK_D_CTRL);
अटल काष्ठा clk_regmap sm1_mst_e_mclk =
	AUD_MST_MCLK_GATE(mst_e_mclk, AUDIO_SM1_MCLK_E_CTRL);
अटल काष्ठा clk_regmap sm1_mst_f_mclk =
	AUD_MST_MCLK_GATE(mst_f_mclk, AUDIO_SM1_MCLK_F_CTRL);

अटल काष्ठा clk_regmap sm1_tdm_mclk_pad_0 = AUD_TDM_PAD_CTRL(
	tdm_mclk_pad_0, AUDIO_SM1_MST_PAD_CTRL0, 0, mclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_mclk_pad_1 = AUD_TDM_PAD_CTRL(
	tdm_mclk_pad_1, AUDIO_SM1_MST_PAD_CTRL0, 4, mclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_lrclk_pad_0 = AUD_TDM_PAD_CTRL(
	tdm_lrclk_pad_0, AUDIO_SM1_MST_PAD_CTRL1, 16, lrclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_lrclk_pad_1 = AUD_TDM_PAD_CTRL(
	tdm_lrclk_pad_1, AUDIO_SM1_MST_PAD_CTRL1, 20, lrclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_lrclk_pad_2 = AUD_TDM_PAD_CTRL(
	tdm_lrclk_pad_2, AUDIO_SM1_MST_PAD_CTRL1, 24, lrclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_sclk_pad_0 = AUD_TDM_PAD_CTRL(
	tdm_sclk_pad_0, AUDIO_SM1_MST_PAD_CTRL1, 0, sclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_sclk_pad_1 = AUD_TDM_PAD_CTRL(
	tdm_sclk_pad_1, AUDIO_SM1_MST_PAD_CTRL1, 4, sclk_pad_ctrl_parent_data);
अटल काष्ठा clk_regmap sm1_tdm_sclk_pad_2 = AUD_TDM_PAD_CTRL(
	tdm_sclk_pad_2, AUDIO_SM1_MST_PAD_CTRL1, 8, sclk_pad_ctrl_parent_data);

/*
 * Array of all घड़ीs provided by this provider
 * The input घड़ीs of the controller will be populated at runसमय
 */
अटल काष्ठा clk_hw_onecell_data axg_audio_hw_onecell_data = अणु
	.hws = अणु
		[AUD_CLKID_DDR_ARB]		= &ddr_arb.hw,
		[AUD_CLKID_PDM]			= &pdm.hw,
		[AUD_CLKID_TDMIN_A]		= &tdmin_a.hw,
		[AUD_CLKID_TDMIN_B]		= &tdmin_b.hw,
		[AUD_CLKID_TDMIN_C]		= &tdmin_c.hw,
		[AUD_CLKID_TDMIN_LB]		= &tdmin_lb.hw,
		[AUD_CLKID_TDMOUT_A]		= &tdmout_a.hw,
		[AUD_CLKID_TDMOUT_B]		= &tdmout_b.hw,
		[AUD_CLKID_TDMOUT_C]		= &tdmout_c.hw,
		[AUD_CLKID_FRDDR_A]		= &frddr_a.hw,
		[AUD_CLKID_FRDDR_B]		= &frddr_b.hw,
		[AUD_CLKID_FRDDR_C]		= &frddr_c.hw,
		[AUD_CLKID_TODDR_A]		= &toddr_a.hw,
		[AUD_CLKID_TODDR_B]		= &toddr_b.hw,
		[AUD_CLKID_TODDR_C]		= &toddr_c.hw,
		[AUD_CLKID_LOOPBACK]		= &loopback.hw,
		[AUD_CLKID_SPDIFIN]		= &spdअगरin.hw,
		[AUD_CLKID_SPDIFOUT]		= &spdअगरout.hw,
		[AUD_CLKID_RESAMPLE]		= &resample.hw,
		[AUD_CLKID_POWER_DETECT]	= &घातer_detect.hw,
		[AUD_CLKID_MST_A_MCLK_SEL]	= &mst_a_mclk_sel.hw,
		[AUD_CLKID_MST_B_MCLK_SEL]	= &mst_b_mclk_sel.hw,
		[AUD_CLKID_MST_C_MCLK_SEL]	= &mst_c_mclk_sel.hw,
		[AUD_CLKID_MST_D_MCLK_SEL]	= &mst_d_mclk_sel.hw,
		[AUD_CLKID_MST_E_MCLK_SEL]	= &mst_e_mclk_sel.hw,
		[AUD_CLKID_MST_F_MCLK_SEL]	= &mst_f_mclk_sel.hw,
		[AUD_CLKID_MST_A_MCLK_DIV]	= &mst_a_mclk_भाग.hw,
		[AUD_CLKID_MST_B_MCLK_DIV]	= &mst_b_mclk_भाग.hw,
		[AUD_CLKID_MST_C_MCLK_DIV]	= &mst_c_mclk_भाग.hw,
		[AUD_CLKID_MST_D_MCLK_DIV]	= &mst_d_mclk_भाग.hw,
		[AUD_CLKID_MST_E_MCLK_DIV]	= &mst_e_mclk_भाग.hw,
		[AUD_CLKID_MST_F_MCLK_DIV]	= &mst_f_mclk_भाग.hw,
		[AUD_CLKID_MST_A_MCLK]		= &mst_a_mclk.hw,
		[AUD_CLKID_MST_B_MCLK]		= &mst_b_mclk.hw,
		[AUD_CLKID_MST_C_MCLK]		= &mst_c_mclk.hw,
		[AUD_CLKID_MST_D_MCLK]		= &mst_d_mclk.hw,
		[AUD_CLKID_MST_E_MCLK]		= &mst_e_mclk.hw,
		[AUD_CLKID_MST_F_MCLK]		= &mst_f_mclk.hw,
		[AUD_CLKID_SPDIFOUT_CLK_SEL]	= &spdअगरout_clk_sel.hw,
		[AUD_CLKID_SPDIFOUT_CLK_DIV]	= &spdअगरout_clk_भाग.hw,
		[AUD_CLKID_SPDIFOUT_CLK]	= &spdअगरout_clk.hw,
		[AUD_CLKID_SPDIFIN_CLK_SEL]	= &spdअगरin_clk_sel.hw,
		[AUD_CLKID_SPDIFIN_CLK_DIV]	= &spdअगरin_clk_भाग.hw,
		[AUD_CLKID_SPDIFIN_CLK]		= &spdअगरin_clk.hw,
		[AUD_CLKID_PDM_DCLK_SEL]	= &pdm_dclk_sel.hw,
		[AUD_CLKID_PDM_DCLK_DIV]	= &pdm_dclk_भाग.hw,
		[AUD_CLKID_PDM_DCLK]		= &pdm_dclk.hw,
		[AUD_CLKID_PDM_SYSCLK_SEL]	= &pdm_sysclk_sel.hw,
		[AUD_CLKID_PDM_SYSCLK_DIV]	= &pdm_sysclk_भाग.hw,
		[AUD_CLKID_PDM_SYSCLK]		= &pdm_sysclk.hw,
		[AUD_CLKID_MST_A_SCLK_PRE_EN]	= &mst_a_sclk_pre_en.hw,
		[AUD_CLKID_MST_B_SCLK_PRE_EN]	= &mst_b_sclk_pre_en.hw,
		[AUD_CLKID_MST_C_SCLK_PRE_EN]	= &mst_c_sclk_pre_en.hw,
		[AUD_CLKID_MST_D_SCLK_PRE_EN]	= &mst_d_sclk_pre_en.hw,
		[AUD_CLKID_MST_E_SCLK_PRE_EN]	= &mst_e_sclk_pre_en.hw,
		[AUD_CLKID_MST_F_SCLK_PRE_EN]	= &mst_f_sclk_pre_en.hw,
		[AUD_CLKID_MST_A_SCLK_DIV]	= &mst_a_sclk_भाग.hw,
		[AUD_CLKID_MST_B_SCLK_DIV]	= &mst_b_sclk_भाग.hw,
		[AUD_CLKID_MST_C_SCLK_DIV]	= &mst_c_sclk_भाग.hw,
		[AUD_CLKID_MST_D_SCLK_DIV]	= &mst_d_sclk_भाग.hw,
		[AUD_CLKID_MST_E_SCLK_DIV]	= &mst_e_sclk_भाग.hw,
		[AUD_CLKID_MST_F_SCLK_DIV]	= &mst_f_sclk_भाग.hw,
		[AUD_CLKID_MST_A_SCLK_POST_EN]	= &mst_a_sclk_post_en.hw,
		[AUD_CLKID_MST_B_SCLK_POST_EN]	= &mst_b_sclk_post_en.hw,
		[AUD_CLKID_MST_C_SCLK_POST_EN]	= &mst_c_sclk_post_en.hw,
		[AUD_CLKID_MST_D_SCLK_POST_EN]	= &mst_d_sclk_post_en.hw,
		[AUD_CLKID_MST_E_SCLK_POST_EN]	= &mst_e_sclk_post_en.hw,
		[AUD_CLKID_MST_F_SCLK_POST_EN]	= &mst_f_sclk_post_en.hw,
		[AUD_CLKID_MST_A_SCLK]		= &mst_a_sclk.hw,
		[AUD_CLKID_MST_B_SCLK]		= &mst_b_sclk.hw,
		[AUD_CLKID_MST_C_SCLK]		= &mst_c_sclk.hw,
		[AUD_CLKID_MST_D_SCLK]		= &mst_d_sclk.hw,
		[AUD_CLKID_MST_E_SCLK]		= &mst_e_sclk.hw,
		[AUD_CLKID_MST_F_SCLK]		= &mst_f_sclk.hw,
		[AUD_CLKID_MST_A_LRCLK_DIV]	= &mst_a_lrclk_भाग.hw,
		[AUD_CLKID_MST_B_LRCLK_DIV]	= &mst_b_lrclk_भाग.hw,
		[AUD_CLKID_MST_C_LRCLK_DIV]	= &mst_c_lrclk_भाग.hw,
		[AUD_CLKID_MST_D_LRCLK_DIV]	= &mst_d_lrclk_भाग.hw,
		[AUD_CLKID_MST_E_LRCLK_DIV]	= &mst_e_lrclk_भाग.hw,
		[AUD_CLKID_MST_F_LRCLK_DIV]	= &mst_f_lrclk_भाग.hw,
		[AUD_CLKID_MST_A_LRCLK]		= &mst_a_lrclk.hw,
		[AUD_CLKID_MST_B_LRCLK]		= &mst_b_lrclk.hw,
		[AUD_CLKID_MST_C_LRCLK]		= &mst_c_lrclk.hw,
		[AUD_CLKID_MST_D_LRCLK]		= &mst_d_lrclk.hw,
		[AUD_CLKID_MST_E_LRCLK]		= &mst_e_lrclk.hw,
		[AUD_CLKID_MST_F_LRCLK]		= &mst_f_lrclk.hw,
		[AUD_CLKID_TDMIN_A_SCLK_SEL]	= &tdmin_a_sclk_sel.hw,
		[AUD_CLKID_TDMIN_B_SCLK_SEL]	= &tdmin_b_sclk_sel.hw,
		[AUD_CLKID_TDMIN_C_SCLK_SEL]	= &tdmin_c_sclk_sel.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_SEL]	= &tdmin_lb_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_SEL]	= &tdmout_a_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_SEL]	= &tdmout_b_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_SEL]	= &tdmout_c_sclk_sel.hw,
		[AUD_CLKID_TDMIN_A_SCLK_PRE_EN]	= &tdmin_a_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_B_SCLK_PRE_EN]	= &tdmin_b_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_C_SCLK_PRE_EN]	= &tdmin_c_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_PRE_EN] = &tdmin_lb_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_PRE_EN] = &tdmout_a_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_PRE_EN] = &tdmout_b_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_PRE_EN] = &tdmout_c_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_A_SCLK_POST_EN] = &tdmin_a_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_B_SCLK_POST_EN] = &tdmin_b_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_C_SCLK_POST_EN] = &tdmin_c_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_POST_EN] = &tdmin_lb_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_POST_EN] = &tdmout_a_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_POST_EN] = &tdmout_b_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_POST_EN] = &tdmout_c_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_A_SCLK]	= &tdmin_a_sclk.hw,
		[AUD_CLKID_TDMIN_B_SCLK]	= &tdmin_b_sclk.hw,
		[AUD_CLKID_TDMIN_C_SCLK]	= &tdmin_c_sclk.hw,
		[AUD_CLKID_TDMIN_LB_SCLK]	= &tdmin_lb_sclk.hw,
		[AUD_CLKID_TDMOUT_A_SCLK]	= &axg_tdmout_a_sclk.hw,
		[AUD_CLKID_TDMOUT_B_SCLK]	= &axg_tdmout_b_sclk.hw,
		[AUD_CLKID_TDMOUT_C_SCLK]	= &axg_tdmout_c_sclk.hw,
		[AUD_CLKID_TDMIN_A_LRCLK]	= &tdmin_a_lrclk.hw,
		[AUD_CLKID_TDMIN_B_LRCLK]	= &tdmin_b_lrclk.hw,
		[AUD_CLKID_TDMIN_C_LRCLK]	= &tdmin_c_lrclk.hw,
		[AUD_CLKID_TDMIN_LB_LRCLK]	= &tdmin_lb_lrclk.hw,
		[AUD_CLKID_TDMOUT_A_LRCLK]	= &tdmout_a_lrclk.hw,
		[AUD_CLKID_TDMOUT_B_LRCLK]	= &tdmout_b_lrclk.hw,
		[AUD_CLKID_TDMOUT_C_LRCLK]	= &tdmout_c_lrclk.hw,
		[AUD_CLKID_TOP]			= &axg_aud_top,
		[NR_CLKS] = शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

/*
 * Array of all G12A घड़ीs provided by this provider
 * The input घड़ीs of the controller will be populated at runसमय
 */
अटल काष्ठा clk_hw_onecell_data g12a_audio_hw_onecell_data = अणु
	.hws = अणु
		[AUD_CLKID_DDR_ARB]		= &ddr_arb.hw,
		[AUD_CLKID_PDM]			= &pdm.hw,
		[AUD_CLKID_TDMIN_A]		= &tdmin_a.hw,
		[AUD_CLKID_TDMIN_B]		= &tdmin_b.hw,
		[AUD_CLKID_TDMIN_C]		= &tdmin_c.hw,
		[AUD_CLKID_TDMIN_LB]		= &tdmin_lb.hw,
		[AUD_CLKID_TDMOUT_A]		= &tdmout_a.hw,
		[AUD_CLKID_TDMOUT_B]		= &tdmout_b.hw,
		[AUD_CLKID_TDMOUT_C]		= &tdmout_c.hw,
		[AUD_CLKID_FRDDR_A]		= &frddr_a.hw,
		[AUD_CLKID_FRDDR_B]		= &frddr_b.hw,
		[AUD_CLKID_FRDDR_C]		= &frddr_c.hw,
		[AUD_CLKID_TODDR_A]		= &toddr_a.hw,
		[AUD_CLKID_TODDR_B]		= &toddr_b.hw,
		[AUD_CLKID_TODDR_C]		= &toddr_c.hw,
		[AUD_CLKID_LOOPBACK]		= &loopback.hw,
		[AUD_CLKID_SPDIFIN]		= &spdअगरin.hw,
		[AUD_CLKID_SPDIFOUT]		= &spdअगरout.hw,
		[AUD_CLKID_RESAMPLE]		= &resample.hw,
		[AUD_CLKID_POWER_DETECT]	= &घातer_detect.hw,
		[AUD_CLKID_SPDIFOUT_B]		= &spdअगरout_b.hw,
		[AUD_CLKID_MST_A_MCLK_SEL]	= &mst_a_mclk_sel.hw,
		[AUD_CLKID_MST_B_MCLK_SEL]	= &mst_b_mclk_sel.hw,
		[AUD_CLKID_MST_C_MCLK_SEL]	= &mst_c_mclk_sel.hw,
		[AUD_CLKID_MST_D_MCLK_SEL]	= &mst_d_mclk_sel.hw,
		[AUD_CLKID_MST_E_MCLK_SEL]	= &mst_e_mclk_sel.hw,
		[AUD_CLKID_MST_F_MCLK_SEL]	= &mst_f_mclk_sel.hw,
		[AUD_CLKID_MST_A_MCLK_DIV]	= &mst_a_mclk_भाग.hw,
		[AUD_CLKID_MST_B_MCLK_DIV]	= &mst_b_mclk_भाग.hw,
		[AUD_CLKID_MST_C_MCLK_DIV]	= &mst_c_mclk_भाग.hw,
		[AUD_CLKID_MST_D_MCLK_DIV]	= &mst_d_mclk_भाग.hw,
		[AUD_CLKID_MST_E_MCLK_DIV]	= &mst_e_mclk_भाग.hw,
		[AUD_CLKID_MST_F_MCLK_DIV]	= &mst_f_mclk_भाग.hw,
		[AUD_CLKID_MST_A_MCLK]		= &mst_a_mclk.hw,
		[AUD_CLKID_MST_B_MCLK]		= &mst_b_mclk.hw,
		[AUD_CLKID_MST_C_MCLK]		= &mst_c_mclk.hw,
		[AUD_CLKID_MST_D_MCLK]		= &mst_d_mclk.hw,
		[AUD_CLKID_MST_E_MCLK]		= &mst_e_mclk.hw,
		[AUD_CLKID_MST_F_MCLK]		= &mst_f_mclk.hw,
		[AUD_CLKID_SPDIFOUT_CLK_SEL]	= &spdअगरout_clk_sel.hw,
		[AUD_CLKID_SPDIFOUT_CLK_DIV]	= &spdअगरout_clk_भाग.hw,
		[AUD_CLKID_SPDIFOUT_CLK]	= &spdअगरout_clk.hw,
		[AUD_CLKID_SPDIFOUT_B_CLK_SEL]	= &spdअगरout_b_clk_sel.hw,
		[AUD_CLKID_SPDIFOUT_B_CLK_DIV]	= &spdअगरout_b_clk_भाग.hw,
		[AUD_CLKID_SPDIFOUT_B_CLK]	= &spdअगरout_b_clk.hw,
		[AUD_CLKID_SPDIFIN_CLK_SEL]	= &spdअगरin_clk_sel.hw,
		[AUD_CLKID_SPDIFIN_CLK_DIV]	= &spdअगरin_clk_भाग.hw,
		[AUD_CLKID_SPDIFIN_CLK]		= &spdअगरin_clk.hw,
		[AUD_CLKID_PDM_DCLK_SEL]	= &pdm_dclk_sel.hw,
		[AUD_CLKID_PDM_DCLK_DIV]	= &pdm_dclk_भाग.hw,
		[AUD_CLKID_PDM_DCLK]		= &pdm_dclk.hw,
		[AUD_CLKID_PDM_SYSCLK_SEL]	= &pdm_sysclk_sel.hw,
		[AUD_CLKID_PDM_SYSCLK_DIV]	= &pdm_sysclk_भाग.hw,
		[AUD_CLKID_PDM_SYSCLK]		= &pdm_sysclk.hw,
		[AUD_CLKID_MST_A_SCLK_PRE_EN]	= &mst_a_sclk_pre_en.hw,
		[AUD_CLKID_MST_B_SCLK_PRE_EN]	= &mst_b_sclk_pre_en.hw,
		[AUD_CLKID_MST_C_SCLK_PRE_EN]	= &mst_c_sclk_pre_en.hw,
		[AUD_CLKID_MST_D_SCLK_PRE_EN]	= &mst_d_sclk_pre_en.hw,
		[AUD_CLKID_MST_E_SCLK_PRE_EN]	= &mst_e_sclk_pre_en.hw,
		[AUD_CLKID_MST_F_SCLK_PRE_EN]	= &mst_f_sclk_pre_en.hw,
		[AUD_CLKID_MST_A_SCLK_DIV]	= &mst_a_sclk_भाग.hw,
		[AUD_CLKID_MST_B_SCLK_DIV]	= &mst_b_sclk_भाग.hw,
		[AUD_CLKID_MST_C_SCLK_DIV]	= &mst_c_sclk_भाग.hw,
		[AUD_CLKID_MST_D_SCLK_DIV]	= &mst_d_sclk_भाग.hw,
		[AUD_CLKID_MST_E_SCLK_DIV]	= &mst_e_sclk_भाग.hw,
		[AUD_CLKID_MST_F_SCLK_DIV]	= &mst_f_sclk_भाग.hw,
		[AUD_CLKID_MST_A_SCLK_POST_EN]	= &mst_a_sclk_post_en.hw,
		[AUD_CLKID_MST_B_SCLK_POST_EN]	= &mst_b_sclk_post_en.hw,
		[AUD_CLKID_MST_C_SCLK_POST_EN]	= &mst_c_sclk_post_en.hw,
		[AUD_CLKID_MST_D_SCLK_POST_EN]	= &mst_d_sclk_post_en.hw,
		[AUD_CLKID_MST_E_SCLK_POST_EN]	= &mst_e_sclk_post_en.hw,
		[AUD_CLKID_MST_F_SCLK_POST_EN]	= &mst_f_sclk_post_en.hw,
		[AUD_CLKID_MST_A_SCLK]		= &mst_a_sclk.hw,
		[AUD_CLKID_MST_B_SCLK]		= &mst_b_sclk.hw,
		[AUD_CLKID_MST_C_SCLK]		= &mst_c_sclk.hw,
		[AUD_CLKID_MST_D_SCLK]		= &mst_d_sclk.hw,
		[AUD_CLKID_MST_E_SCLK]		= &mst_e_sclk.hw,
		[AUD_CLKID_MST_F_SCLK]		= &mst_f_sclk.hw,
		[AUD_CLKID_MST_A_LRCLK_DIV]	= &mst_a_lrclk_भाग.hw,
		[AUD_CLKID_MST_B_LRCLK_DIV]	= &mst_b_lrclk_भाग.hw,
		[AUD_CLKID_MST_C_LRCLK_DIV]	= &mst_c_lrclk_भाग.hw,
		[AUD_CLKID_MST_D_LRCLK_DIV]	= &mst_d_lrclk_भाग.hw,
		[AUD_CLKID_MST_E_LRCLK_DIV]	= &mst_e_lrclk_भाग.hw,
		[AUD_CLKID_MST_F_LRCLK_DIV]	= &mst_f_lrclk_भाग.hw,
		[AUD_CLKID_MST_A_LRCLK]		= &mst_a_lrclk.hw,
		[AUD_CLKID_MST_B_LRCLK]		= &mst_b_lrclk.hw,
		[AUD_CLKID_MST_C_LRCLK]		= &mst_c_lrclk.hw,
		[AUD_CLKID_MST_D_LRCLK]		= &mst_d_lrclk.hw,
		[AUD_CLKID_MST_E_LRCLK]		= &mst_e_lrclk.hw,
		[AUD_CLKID_MST_F_LRCLK]		= &mst_f_lrclk.hw,
		[AUD_CLKID_TDMIN_A_SCLK_SEL]	= &tdmin_a_sclk_sel.hw,
		[AUD_CLKID_TDMIN_B_SCLK_SEL]	= &tdmin_b_sclk_sel.hw,
		[AUD_CLKID_TDMIN_C_SCLK_SEL]	= &tdmin_c_sclk_sel.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_SEL]	= &tdmin_lb_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_SEL]	= &tdmout_a_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_SEL]	= &tdmout_b_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_SEL]	= &tdmout_c_sclk_sel.hw,
		[AUD_CLKID_TDMIN_A_SCLK_PRE_EN]	= &tdmin_a_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_B_SCLK_PRE_EN]	= &tdmin_b_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_C_SCLK_PRE_EN]	= &tdmin_c_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_PRE_EN] = &tdmin_lb_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_PRE_EN] = &tdmout_a_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_PRE_EN] = &tdmout_b_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_PRE_EN] = &tdmout_c_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_A_SCLK_POST_EN] = &tdmin_a_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_B_SCLK_POST_EN] = &tdmin_b_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_C_SCLK_POST_EN] = &tdmin_c_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_POST_EN] = &tdmin_lb_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_POST_EN] = &tdmout_a_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_POST_EN] = &tdmout_b_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_POST_EN] = &tdmout_c_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_A_SCLK]	= &tdmin_a_sclk.hw,
		[AUD_CLKID_TDMIN_B_SCLK]	= &tdmin_b_sclk.hw,
		[AUD_CLKID_TDMIN_C_SCLK]	= &tdmin_c_sclk.hw,
		[AUD_CLKID_TDMIN_LB_SCLK]	= &tdmin_lb_sclk.hw,
		[AUD_CLKID_TDMOUT_A_SCLK]	= &g12a_tdmout_a_sclk.hw,
		[AUD_CLKID_TDMOUT_B_SCLK]	= &g12a_tdmout_b_sclk.hw,
		[AUD_CLKID_TDMOUT_C_SCLK]	= &g12a_tdmout_c_sclk.hw,
		[AUD_CLKID_TDMIN_A_LRCLK]	= &tdmin_a_lrclk.hw,
		[AUD_CLKID_TDMIN_B_LRCLK]	= &tdmin_b_lrclk.hw,
		[AUD_CLKID_TDMIN_C_LRCLK]	= &tdmin_c_lrclk.hw,
		[AUD_CLKID_TDMIN_LB_LRCLK]	= &tdmin_lb_lrclk.hw,
		[AUD_CLKID_TDMOUT_A_LRCLK]	= &tdmout_a_lrclk.hw,
		[AUD_CLKID_TDMOUT_B_LRCLK]	= &tdmout_b_lrclk.hw,
		[AUD_CLKID_TDMOUT_C_LRCLK]	= &tdmout_c_lrclk.hw,
		[AUD_CLKID_TDM_MCLK_PAD0]	= &g12a_tdm_mclk_pad_0.hw,
		[AUD_CLKID_TDM_MCLK_PAD1]	= &g12a_tdm_mclk_pad_1.hw,
		[AUD_CLKID_TDM_LRCLK_PAD0]	= &g12a_tdm_lrclk_pad_0.hw,
		[AUD_CLKID_TDM_LRCLK_PAD1]	= &g12a_tdm_lrclk_pad_1.hw,
		[AUD_CLKID_TDM_LRCLK_PAD2]	= &g12a_tdm_lrclk_pad_2.hw,
		[AUD_CLKID_TDM_SCLK_PAD0]	= &g12a_tdm_sclk_pad_0.hw,
		[AUD_CLKID_TDM_SCLK_PAD1]	= &g12a_tdm_sclk_pad_1.hw,
		[AUD_CLKID_TDM_SCLK_PAD2]	= &g12a_tdm_sclk_pad_2.hw,
		[AUD_CLKID_TOP]			= &axg_aud_top,
		[NR_CLKS] = शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;

/*
 * Array of all SM1 घड़ीs provided by this provider
 * The input घड़ीs of the controller will be populated at runसमय
 */
अटल काष्ठा clk_hw_onecell_data sm1_audio_hw_onecell_data = अणु
	.hws = अणु
		[AUD_CLKID_DDR_ARB]		= &ddr_arb.hw,
		[AUD_CLKID_PDM]			= &pdm.hw,
		[AUD_CLKID_TDMIN_A]		= &tdmin_a.hw,
		[AUD_CLKID_TDMIN_B]		= &tdmin_b.hw,
		[AUD_CLKID_TDMIN_C]		= &tdmin_c.hw,
		[AUD_CLKID_TDMIN_LB]		= &tdmin_lb.hw,
		[AUD_CLKID_TDMOUT_A]		= &tdmout_a.hw,
		[AUD_CLKID_TDMOUT_B]		= &tdmout_b.hw,
		[AUD_CLKID_TDMOUT_C]		= &tdmout_c.hw,
		[AUD_CLKID_FRDDR_A]		= &frddr_a.hw,
		[AUD_CLKID_FRDDR_B]		= &frddr_b.hw,
		[AUD_CLKID_FRDDR_C]		= &frddr_c.hw,
		[AUD_CLKID_TODDR_A]		= &toddr_a.hw,
		[AUD_CLKID_TODDR_B]		= &toddr_b.hw,
		[AUD_CLKID_TODDR_C]		= &toddr_c.hw,
		[AUD_CLKID_LOOPBACK]		= &loopback.hw,
		[AUD_CLKID_SPDIFIN]		= &spdअगरin.hw,
		[AUD_CLKID_SPDIFOUT]		= &spdअगरout.hw,
		[AUD_CLKID_RESAMPLE]		= &resample.hw,
		[AUD_CLKID_SPDIFOUT_B]		= &spdअगरout_b.hw,
		[AUD_CLKID_MST_A_MCLK_SEL]	= &sm1_mst_a_mclk_sel.hw,
		[AUD_CLKID_MST_B_MCLK_SEL]	= &sm1_mst_b_mclk_sel.hw,
		[AUD_CLKID_MST_C_MCLK_SEL]	= &sm1_mst_c_mclk_sel.hw,
		[AUD_CLKID_MST_D_MCLK_SEL]	= &sm1_mst_d_mclk_sel.hw,
		[AUD_CLKID_MST_E_MCLK_SEL]	= &sm1_mst_e_mclk_sel.hw,
		[AUD_CLKID_MST_F_MCLK_SEL]	= &sm1_mst_f_mclk_sel.hw,
		[AUD_CLKID_MST_A_MCLK_DIV]	= &sm1_mst_a_mclk_भाग.hw,
		[AUD_CLKID_MST_B_MCLK_DIV]	= &sm1_mst_b_mclk_भाग.hw,
		[AUD_CLKID_MST_C_MCLK_DIV]	= &sm1_mst_c_mclk_भाग.hw,
		[AUD_CLKID_MST_D_MCLK_DIV]	= &sm1_mst_d_mclk_भाग.hw,
		[AUD_CLKID_MST_E_MCLK_DIV]	= &sm1_mst_e_mclk_भाग.hw,
		[AUD_CLKID_MST_F_MCLK_DIV]	= &sm1_mst_f_mclk_भाग.hw,
		[AUD_CLKID_MST_A_MCLK]		= &sm1_mst_a_mclk.hw,
		[AUD_CLKID_MST_B_MCLK]		= &sm1_mst_b_mclk.hw,
		[AUD_CLKID_MST_C_MCLK]		= &sm1_mst_c_mclk.hw,
		[AUD_CLKID_MST_D_MCLK]		= &sm1_mst_d_mclk.hw,
		[AUD_CLKID_MST_E_MCLK]		= &sm1_mst_e_mclk.hw,
		[AUD_CLKID_MST_F_MCLK]		= &sm1_mst_f_mclk.hw,
		[AUD_CLKID_SPDIFOUT_CLK_SEL]	= &spdअगरout_clk_sel.hw,
		[AUD_CLKID_SPDIFOUT_CLK_DIV]	= &spdअगरout_clk_भाग.hw,
		[AUD_CLKID_SPDIFOUT_CLK]	= &spdअगरout_clk.hw,
		[AUD_CLKID_SPDIFOUT_B_CLK_SEL]	= &spdअगरout_b_clk_sel.hw,
		[AUD_CLKID_SPDIFOUT_B_CLK_DIV]	= &spdअगरout_b_clk_भाग.hw,
		[AUD_CLKID_SPDIFOUT_B_CLK]	= &spdअगरout_b_clk.hw,
		[AUD_CLKID_SPDIFIN_CLK_SEL]	= &spdअगरin_clk_sel.hw,
		[AUD_CLKID_SPDIFIN_CLK_DIV]	= &spdअगरin_clk_भाग.hw,
		[AUD_CLKID_SPDIFIN_CLK]		= &spdअगरin_clk.hw,
		[AUD_CLKID_PDM_DCLK_SEL]	= &pdm_dclk_sel.hw,
		[AUD_CLKID_PDM_DCLK_DIV]	= &pdm_dclk_भाग.hw,
		[AUD_CLKID_PDM_DCLK]		= &pdm_dclk.hw,
		[AUD_CLKID_PDM_SYSCLK_SEL]	= &pdm_sysclk_sel.hw,
		[AUD_CLKID_PDM_SYSCLK_DIV]	= &pdm_sysclk_भाग.hw,
		[AUD_CLKID_PDM_SYSCLK]		= &pdm_sysclk.hw,
		[AUD_CLKID_MST_A_SCLK_PRE_EN]	= &mst_a_sclk_pre_en.hw,
		[AUD_CLKID_MST_B_SCLK_PRE_EN]	= &mst_b_sclk_pre_en.hw,
		[AUD_CLKID_MST_C_SCLK_PRE_EN]	= &mst_c_sclk_pre_en.hw,
		[AUD_CLKID_MST_D_SCLK_PRE_EN]	= &mst_d_sclk_pre_en.hw,
		[AUD_CLKID_MST_E_SCLK_PRE_EN]	= &mst_e_sclk_pre_en.hw,
		[AUD_CLKID_MST_F_SCLK_PRE_EN]	= &mst_f_sclk_pre_en.hw,
		[AUD_CLKID_MST_A_SCLK_DIV]	= &mst_a_sclk_भाग.hw,
		[AUD_CLKID_MST_B_SCLK_DIV]	= &mst_b_sclk_भाग.hw,
		[AUD_CLKID_MST_C_SCLK_DIV]	= &mst_c_sclk_भाग.hw,
		[AUD_CLKID_MST_D_SCLK_DIV]	= &mst_d_sclk_भाग.hw,
		[AUD_CLKID_MST_E_SCLK_DIV]	= &mst_e_sclk_भाग.hw,
		[AUD_CLKID_MST_F_SCLK_DIV]	= &mst_f_sclk_भाग.hw,
		[AUD_CLKID_MST_A_SCLK_POST_EN]	= &mst_a_sclk_post_en.hw,
		[AUD_CLKID_MST_B_SCLK_POST_EN]	= &mst_b_sclk_post_en.hw,
		[AUD_CLKID_MST_C_SCLK_POST_EN]	= &mst_c_sclk_post_en.hw,
		[AUD_CLKID_MST_D_SCLK_POST_EN]	= &mst_d_sclk_post_en.hw,
		[AUD_CLKID_MST_E_SCLK_POST_EN]	= &mst_e_sclk_post_en.hw,
		[AUD_CLKID_MST_F_SCLK_POST_EN]	= &mst_f_sclk_post_en.hw,
		[AUD_CLKID_MST_A_SCLK]		= &mst_a_sclk.hw,
		[AUD_CLKID_MST_B_SCLK]		= &mst_b_sclk.hw,
		[AUD_CLKID_MST_C_SCLK]		= &mst_c_sclk.hw,
		[AUD_CLKID_MST_D_SCLK]		= &mst_d_sclk.hw,
		[AUD_CLKID_MST_E_SCLK]		= &mst_e_sclk.hw,
		[AUD_CLKID_MST_F_SCLK]		= &mst_f_sclk.hw,
		[AUD_CLKID_MST_A_LRCLK_DIV]	= &mst_a_lrclk_भाग.hw,
		[AUD_CLKID_MST_B_LRCLK_DIV]	= &mst_b_lrclk_भाग.hw,
		[AUD_CLKID_MST_C_LRCLK_DIV]	= &mst_c_lrclk_भाग.hw,
		[AUD_CLKID_MST_D_LRCLK_DIV]	= &mst_d_lrclk_भाग.hw,
		[AUD_CLKID_MST_E_LRCLK_DIV]	= &mst_e_lrclk_भाग.hw,
		[AUD_CLKID_MST_F_LRCLK_DIV]	= &mst_f_lrclk_भाग.hw,
		[AUD_CLKID_MST_A_LRCLK]		= &mst_a_lrclk.hw,
		[AUD_CLKID_MST_B_LRCLK]		= &mst_b_lrclk.hw,
		[AUD_CLKID_MST_C_LRCLK]		= &mst_c_lrclk.hw,
		[AUD_CLKID_MST_D_LRCLK]		= &mst_d_lrclk.hw,
		[AUD_CLKID_MST_E_LRCLK]		= &mst_e_lrclk.hw,
		[AUD_CLKID_MST_F_LRCLK]		= &mst_f_lrclk.hw,
		[AUD_CLKID_TDMIN_A_SCLK_SEL]	= &tdmin_a_sclk_sel.hw,
		[AUD_CLKID_TDMIN_B_SCLK_SEL]	= &tdmin_b_sclk_sel.hw,
		[AUD_CLKID_TDMIN_C_SCLK_SEL]	= &tdmin_c_sclk_sel.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_SEL]	= &tdmin_lb_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_SEL]	= &tdmout_a_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_SEL]	= &tdmout_b_sclk_sel.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_SEL]	= &tdmout_c_sclk_sel.hw,
		[AUD_CLKID_TDMIN_A_SCLK_PRE_EN]	= &tdmin_a_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_B_SCLK_PRE_EN]	= &tdmin_b_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_C_SCLK_PRE_EN]	= &tdmin_c_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_PRE_EN] = &tdmin_lb_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_PRE_EN] = &tdmout_a_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_PRE_EN] = &tdmout_b_sclk_pre_en.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_PRE_EN] = &tdmout_c_sclk_pre_en.hw,
		[AUD_CLKID_TDMIN_A_SCLK_POST_EN] = &tdmin_a_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_B_SCLK_POST_EN] = &tdmin_b_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_C_SCLK_POST_EN] = &tdmin_c_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_LB_SCLK_POST_EN] = &tdmin_lb_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_A_SCLK_POST_EN] = &tdmout_a_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_B_SCLK_POST_EN] = &tdmout_b_sclk_post_en.hw,
		[AUD_CLKID_TDMOUT_C_SCLK_POST_EN] = &tdmout_c_sclk_post_en.hw,
		[AUD_CLKID_TDMIN_A_SCLK]	= &tdmin_a_sclk.hw,
		[AUD_CLKID_TDMIN_B_SCLK]	= &tdmin_b_sclk.hw,
		[AUD_CLKID_TDMIN_C_SCLK]	= &tdmin_c_sclk.hw,
		[AUD_CLKID_TDMIN_LB_SCLK]	= &tdmin_lb_sclk.hw,
		[AUD_CLKID_TDMOUT_A_SCLK]	= &g12a_tdmout_a_sclk.hw,
		[AUD_CLKID_TDMOUT_B_SCLK]	= &g12a_tdmout_b_sclk.hw,
		[AUD_CLKID_TDMOUT_C_SCLK]	= &g12a_tdmout_c_sclk.hw,
		[AUD_CLKID_TDMIN_A_LRCLK]	= &tdmin_a_lrclk.hw,
		[AUD_CLKID_TDMIN_B_LRCLK]	= &tdmin_b_lrclk.hw,
		[AUD_CLKID_TDMIN_C_LRCLK]	= &tdmin_c_lrclk.hw,
		[AUD_CLKID_TDMIN_LB_LRCLK]	= &tdmin_lb_lrclk.hw,
		[AUD_CLKID_TDMOUT_A_LRCLK]	= &tdmout_a_lrclk.hw,
		[AUD_CLKID_TDMOUT_B_LRCLK]	= &tdmout_b_lrclk.hw,
		[AUD_CLKID_TDMOUT_C_LRCLK]	= &tdmout_c_lrclk.hw,
		[AUD_CLKID_TDM_MCLK_PAD0]	= &sm1_tdm_mclk_pad_0.hw,
		[AUD_CLKID_TDM_MCLK_PAD1]	= &sm1_tdm_mclk_pad_1.hw,
		[AUD_CLKID_TDM_LRCLK_PAD0]	= &sm1_tdm_lrclk_pad_0.hw,
		[AUD_CLKID_TDM_LRCLK_PAD1]	= &sm1_tdm_lrclk_pad_1.hw,
		[AUD_CLKID_TDM_LRCLK_PAD2]	= &sm1_tdm_lrclk_pad_2.hw,
		[AUD_CLKID_TDM_SCLK_PAD0]	= &sm1_tdm_sclk_pad_0.hw,
		[AUD_CLKID_TDM_SCLK_PAD1]	= &sm1_tdm_sclk_pad_1.hw,
		[AUD_CLKID_TDM_SCLK_PAD2]	= &sm1_tdm_sclk_pad_2.hw,
		[AUD_CLKID_TOP]			= &sm1_aud_top.hw,
		[AUD_CLKID_TORAM]		= &toram.hw,
		[AUD_CLKID_EQDRC]		= &eqdrc.hw,
		[AUD_CLKID_RESAMPLE_B]		= &resample_b.hw,
		[AUD_CLKID_TOVAD]		= &tovad.hw,
		[AUD_CLKID_LOCKER]		= &locker.hw,
		[AUD_CLKID_SPDIFIN_LB]		= &spdअगरin_lb.hw,
		[AUD_CLKID_FRDDR_D]		= &frddr_d.hw,
		[AUD_CLKID_TODDR_D]		= &toddr_d.hw,
		[AUD_CLKID_LOOPBACK_B]		= &loopback_b.hw,
		[AUD_CLKID_CLK81_EN]		= &sm1_clk81_en.hw,
		[AUD_CLKID_SYSCLK_A_DIV]	= &sm1_sysclk_a_भाग.hw,
		[AUD_CLKID_SYSCLK_A_EN]		= &sm1_sysclk_a_en.hw,
		[AUD_CLKID_SYSCLK_B_DIV]	= &sm1_sysclk_b_भाग.hw,
		[AUD_CLKID_SYSCLK_B_EN]		= &sm1_sysclk_b_en.hw,
		[NR_CLKS] = शून्य,
	पूर्ण,
	.num = NR_CLKS,
पूर्ण;


/* Convenience table to populate regmap in .probe(). */
अटल काष्ठा clk_regmap *स्थिर axg_clk_regmaps[] = अणु
	&ddr_arb,
	&pdm,
	&tdmin_a,
	&tdmin_b,
	&tdmin_c,
	&tdmin_lb,
	&tdmout_a,
	&tdmout_b,
	&tdmout_c,
	&frddr_a,
	&frddr_b,
	&frddr_c,
	&toddr_a,
	&toddr_b,
	&toddr_c,
	&loopback,
	&spdअगरin,
	&spdअगरout,
	&resample,
	&घातer_detect,
	&mst_a_mclk_sel,
	&mst_b_mclk_sel,
	&mst_c_mclk_sel,
	&mst_d_mclk_sel,
	&mst_e_mclk_sel,
	&mst_f_mclk_sel,
	&mst_a_mclk_भाग,
	&mst_b_mclk_भाग,
	&mst_c_mclk_भाग,
	&mst_d_mclk_भाग,
	&mst_e_mclk_भाग,
	&mst_f_mclk_भाग,
	&mst_a_mclk,
	&mst_b_mclk,
	&mst_c_mclk,
	&mst_d_mclk,
	&mst_e_mclk,
	&mst_f_mclk,
	&spdअगरout_clk_sel,
	&spdअगरout_clk_भाग,
	&spdअगरout_clk,
	&spdअगरin_clk_sel,
	&spdअगरin_clk_भाग,
	&spdअगरin_clk,
	&pdm_dclk_sel,
	&pdm_dclk_भाग,
	&pdm_dclk,
	&pdm_sysclk_sel,
	&pdm_sysclk_भाग,
	&pdm_sysclk,
	&mst_a_sclk_pre_en,
	&mst_b_sclk_pre_en,
	&mst_c_sclk_pre_en,
	&mst_d_sclk_pre_en,
	&mst_e_sclk_pre_en,
	&mst_f_sclk_pre_en,
	&mst_a_sclk_भाग,
	&mst_b_sclk_भाग,
	&mst_c_sclk_भाग,
	&mst_d_sclk_भाग,
	&mst_e_sclk_भाग,
	&mst_f_sclk_भाग,
	&mst_a_sclk_post_en,
	&mst_b_sclk_post_en,
	&mst_c_sclk_post_en,
	&mst_d_sclk_post_en,
	&mst_e_sclk_post_en,
	&mst_f_sclk_post_en,
	&mst_a_sclk,
	&mst_b_sclk,
	&mst_c_sclk,
	&mst_d_sclk,
	&mst_e_sclk,
	&mst_f_sclk,
	&mst_a_lrclk_भाग,
	&mst_b_lrclk_भाग,
	&mst_c_lrclk_भाग,
	&mst_d_lrclk_भाग,
	&mst_e_lrclk_भाग,
	&mst_f_lrclk_भाग,
	&mst_a_lrclk,
	&mst_b_lrclk,
	&mst_c_lrclk,
	&mst_d_lrclk,
	&mst_e_lrclk,
	&mst_f_lrclk,
	&tdmin_a_sclk_sel,
	&tdmin_b_sclk_sel,
	&tdmin_c_sclk_sel,
	&tdmin_lb_sclk_sel,
	&tdmout_a_sclk_sel,
	&tdmout_b_sclk_sel,
	&tdmout_c_sclk_sel,
	&tdmin_a_sclk_pre_en,
	&tdmin_b_sclk_pre_en,
	&tdmin_c_sclk_pre_en,
	&tdmin_lb_sclk_pre_en,
	&tdmout_a_sclk_pre_en,
	&tdmout_b_sclk_pre_en,
	&tdmout_c_sclk_pre_en,
	&tdmin_a_sclk_post_en,
	&tdmin_b_sclk_post_en,
	&tdmin_c_sclk_post_en,
	&tdmin_lb_sclk_post_en,
	&tdmout_a_sclk_post_en,
	&tdmout_b_sclk_post_en,
	&tdmout_c_sclk_post_en,
	&tdmin_a_sclk,
	&tdmin_b_sclk,
	&tdmin_c_sclk,
	&tdmin_lb_sclk,
	&axg_tdmout_a_sclk,
	&axg_tdmout_b_sclk,
	&axg_tdmout_c_sclk,
	&tdmin_a_lrclk,
	&tdmin_b_lrclk,
	&tdmin_c_lrclk,
	&tdmin_lb_lrclk,
	&tdmout_a_lrclk,
	&tdmout_b_lrclk,
	&tdmout_c_lrclk,
पूर्ण;

अटल काष्ठा clk_regmap *स्थिर g12a_clk_regmaps[] = अणु
	&ddr_arb,
	&pdm,
	&tdmin_a,
	&tdmin_b,
	&tdmin_c,
	&tdmin_lb,
	&tdmout_a,
	&tdmout_b,
	&tdmout_c,
	&frddr_a,
	&frddr_b,
	&frddr_c,
	&toddr_a,
	&toddr_b,
	&toddr_c,
	&loopback,
	&spdअगरin,
	&spdअगरout,
	&resample,
	&घातer_detect,
	&spdअगरout_b,
	&mst_a_mclk_sel,
	&mst_b_mclk_sel,
	&mst_c_mclk_sel,
	&mst_d_mclk_sel,
	&mst_e_mclk_sel,
	&mst_f_mclk_sel,
	&mst_a_mclk_भाग,
	&mst_b_mclk_भाग,
	&mst_c_mclk_भाग,
	&mst_d_mclk_भाग,
	&mst_e_mclk_भाग,
	&mst_f_mclk_भाग,
	&mst_a_mclk,
	&mst_b_mclk,
	&mst_c_mclk,
	&mst_d_mclk,
	&mst_e_mclk,
	&mst_f_mclk,
	&spdअगरout_clk_sel,
	&spdअगरout_clk_भाग,
	&spdअगरout_clk,
	&spdअगरin_clk_sel,
	&spdअगरin_clk_भाग,
	&spdअगरin_clk,
	&pdm_dclk_sel,
	&pdm_dclk_भाग,
	&pdm_dclk,
	&pdm_sysclk_sel,
	&pdm_sysclk_भाग,
	&pdm_sysclk,
	&mst_a_sclk_pre_en,
	&mst_b_sclk_pre_en,
	&mst_c_sclk_pre_en,
	&mst_d_sclk_pre_en,
	&mst_e_sclk_pre_en,
	&mst_f_sclk_pre_en,
	&mst_a_sclk_भाग,
	&mst_b_sclk_भाग,
	&mst_c_sclk_भाग,
	&mst_d_sclk_भाग,
	&mst_e_sclk_भाग,
	&mst_f_sclk_भाग,
	&mst_a_sclk_post_en,
	&mst_b_sclk_post_en,
	&mst_c_sclk_post_en,
	&mst_d_sclk_post_en,
	&mst_e_sclk_post_en,
	&mst_f_sclk_post_en,
	&mst_a_sclk,
	&mst_b_sclk,
	&mst_c_sclk,
	&mst_d_sclk,
	&mst_e_sclk,
	&mst_f_sclk,
	&mst_a_lrclk_भाग,
	&mst_b_lrclk_भाग,
	&mst_c_lrclk_भाग,
	&mst_d_lrclk_भाग,
	&mst_e_lrclk_भाग,
	&mst_f_lrclk_भाग,
	&mst_a_lrclk,
	&mst_b_lrclk,
	&mst_c_lrclk,
	&mst_d_lrclk,
	&mst_e_lrclk,
	&mst_f_lrclk,
	&tdmin_a_sclk_sel,
	&tdmin_b_sclk_sel,
	&tdmin_c_sclk_sel,
	&tdmin_lb_sclk_sel,
	&tdmout_a_sclk_sel,
	&tdmout_b_sclk_sel,
	&tdmout_c_sclk_sel,
	&tdmin_a_sclk_pre_en,
	&tdmin_b_sclk_pre_en,
	&tdmin_c_sclk_pre_en,
	&tdmin_lb_sclk_pre_en,
	&tdmout_a_sclk_pre_en,
	&tdmout_b_sclk_pre_en,
	&tdmout_c_sclk_pre_en,
	&tdmin_a_sclk_post_en,
	&tdmin_b_sclk_post_en,
	&tdmin_c_sclk_post_en,
	&tdmin_lb_sclk_post_en,
	&tdmout_a_sclk_post_en,
	&tdmout_b_sclk_post_en,
	&tdmout_c_sclk_post_en,
	&tdmin_a_sclk,
	&tdmin_b_sclk,
	&tdmin_c_sclk,
	&tdmin_lb_sclk,
	&g12a_tdmout_a_sclk,
	&g12a_tdmout_b_sclk,
	&g12a_tdmout_c_sclk,
	&tdmin_a_lrclk,
	&tdmin_b_lrclk,
	&tdmin_c_lrclk,
	&tdmin_lb_lrclk,
	&tdmout_a_lrclk,
	&tdmout_b_lrclk,
	&tdmout_c_lrclk,
	&spdअगरout_b_clk_sel,
	&spdअगरout_b_clk_भाग,
	&spdअगरout_b_clk,
	&g12a_tdm_mclk_pad_0,
	&g12a_tdm_mclk_pad_1,
	&g12a_tdm_lrclk_pad_0,
	&g12a_tdm_lrclk_pad_1,
	&g12a_tdm_lrclk_pad_2,
	&g12a_tdm_sclk_pad_0,
	&g12a_tdm_sclk_pad_1,
	&g12a_tdm_sclk_pad_2,
	&toram,
	&eqdrc,
पूर्ण;

अटल काष्ठा clk_regmap *स्थिर sm1_clk_regmaps[] = अणु
	&ddr_arb,
	&pdm,
	&tdmin_a,
	&tdmin_b,
	&tdmin_c,
	&tdmin_lb,
	&tdmout_a,
	&tdmout_b,
	&tdmout_c,
	&frddr_a,
	&frddr_b,
	&frddr_c,
	&toddr_a,
	&toddr_b,
	&toddr_c,
	&loopback,
	&spdअगरin,
	&spdअगरout,
	&resample,
	&spdअगरout_b,
	&sm1_mst_a_mclk_sel,
	&sm1_mst_b_mclk_sel,
	&sm1_mst_c_mclk_sel,
	&sm1_mst_d_mclk_sel,
	&sm1_mst_e_mclk_sel,
	&sm1_mst_f_mclk_sel,
	&sm1_mst_a_mclk_भाग,
	&sm1_mst_b_mclk_भाग,
	&sm1_mst_c_mclk_भाग,
	&sm1_mst_d_mclk_भाग,
	&sm1_mst_e_mclk_भाग,
	&sm1_mst_f_mclk_भाग,
	&sm1_mst_a_mclk,
	&sm1_mst_b_mclk,
	&sm1_mst_c_mclk,
	&sm1_mst_d_mclk,
	&sm1_mst_e_mclk,
	&sm1_mst_f_mclk,
	&spdअगरout_clk_sel,
	&spdअगरout_clk_भाग,
	&spdअगरout_clk,
	&spdअगरin_clk_sel,
	&spdअगरin_clk_भाग,
	&spdअगरin_clk,
	&pdm_dclk_sel,
	&pdm_dclk_भाग,
	&pdm_dclk,
	&pdm_sysclk_sel,
	&pdm_sysclk_भाग,
	&pdm_sysclk,
	&mst_a_sclk_pre_en,
	&mst_b_sclk_pre_en,
	&mst_c_sclk_pre_en,
	&mst_d_sclk_pre_en,
	&mst_e_sclk_pre_en,
	&mst_f_sclk_pre_en,
	&mst_a_sclk_भाग,
	&mst_b_sclk_भाग,
	&mst_c_sclk_भाग,
	&mst_d_sclk_भाग,
	&mst_e_sclk_भाग,
	&mst_f_sclk_भाग,
	&mst_a_sclk_post_en,
	&mst_b_sclk_post_en,
	&mst_c_sclk_post_en,
	&mst_d_sclk_post_en,
	&mst_e_sclk_post_en,
	&mst_f_sclk_post_en,
	&mst_a_sclk,
	&mst_b_sclk,
	&mst_c_sclk,
	&mst_d_sclk,
	&mst_e_sclk,
	&mst_f_sclk,
	&mst_a_lrclk_भाग,
	&mst_b_lrclk_भाग,
	&mst_c_lrclk_भाग,
	&mst_d_lrclk_भाग,
	&mst_e_lrclk_भाग,
	&mst_f_lrclk_भाग,
	&mst_a_lrclk,
	&mst_b_lrclk,
	&mst_c_lrclk,
	&mst_d_lrclk,
	&mst_e_lrclk,
	&mst_f_lrclk,
	&tdmin_a_sclk_sel,
	&tdmin_b_sclk_sel,
	&tdmin_c_sclk_sel,
	&tdmin_lb_sclk_sel,
	&tdmout_a_sclk_sel,
	&tdmout_b_sclk_sel,
	&tdmout_c_sclk_sel,
	&tdmin_a_sclk_pre_en,
	&tdmin_b_sclk_pre_en,
	&tdmin_c_sclk_pre_en,
	&tdmin_lb_sclk_pre_en,
	&tdmout_a_sclk_pre_en,
	&tdmout_b_sclk_pre_en,
	&tdmout_c_sclk_pre_en,
	&tdmin_a_sclk_post_en,
	&tdmin_b_sclk_post_en,
	&tdmin_c_sclk_post_en,
	&tdmin_lb_sclk_post_en,
	&tdmout_a_sclk_post_en,
	&tdmout_b_sclk_post_en,
	&tdmout_c_sclk_post_en,
	&tdmin_a_sclk,
	&tdmin_b_sclk,
	&tdmin_c_sclk,
	&tdmin_lb_sclk,
	&g12a_tdmout_a_sclk,
	&g12a_tdmout_b_sclk,
	&g12a_tdmout_c_sclk,
	&tdmin_a_lrclk,
	&tdmin_b_lrclk,
	&tdmin_c_lrclk,
	&tdmin_lb_lrclk,
	&tdmout_a_lrclk,
	&tdmout_b_lrclk,
	&tdmout_c_lrclk,
	&spdअगरout_b_clk_sel,
	&spdअगरout_b_clk_भाग,
	&spdअगरout_b_clk,
	&sm1_tdm_mclk_pad_0,
	&sm1_tdm_mclk_pad_1,
	&sm1_tdm_lrclk_pad_0,
	&sm1_tdm_lrclk_pad_1,
	&sm1_tdm_lrclk_pad_2,
	&sm1_tdm_sclk_pad_0,
	&sm1_tdm_sclk_pad_1,
	&sm1_tdm_sclk_pad_2,
	&sm1_aud_top,
	&toram,
	&eqdrc,
	&resample_b,
	&tovad,
	&locker,
	&spdअगरin_lb,
	&frddr_d,
	&toddr_d,
	&loopback_b,
	&sm1_clk81_en,
	&sm1_sysclk_a_भाग,
	&sm1_sysclk_a_en,
	&sm1_sysclk_b_भाग,
	&sm1_sysclk_b_en,
पूर्ण;

अटल पूर्णांक devm_clk_get_enable(काष्ठा device *dev, अक्षर *id)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = devm_clk_get(dev, id);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get %s", id);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable %s", id);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev,
				       (व्योम(*)(व्योम *))clk_disable_unprepare,
				       clk);
	अगर (ret) अणु
		dev_err(dev, "failed to add reset action on %s", id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा axg_audio_reset_data अणु
	काष्ठा reset_controller_dev rstc;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल व्योम axg_audio_reset_reg_and_bit(काष्ठा axg_audio_reset_data *rst,
					अचिन्हित दीर्घ id,
					अचिन्हित पूर्णांक *reg,
					अचिन्हित पूर्णांक *bit)
अणु
	अचिन्हित पूर्णांक stride = regmap_get_reg_stride(rst->map);

	*reg = (id / (stride * BITS_PER_BYTE)) * stride;
	*reg += rst->offset;
	*bit = id % (stride * BITS_PER_BYTE);
पूर्ण

अटल पूर्णांक axg_audio_reset_update(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा axg_audio_reset_data *rst =
		container_of(rcdev, काष्ठा axg_audio_reset_data, rstc);
	अचिन्हित पूर्णांक offset, bit;

	axg_audio_reset_reg_and_bit(rst, id, &offset, &bit);

	regmap_update_bits(rst->map, offset, BIT(bit),
			निश्चित ? BIT(bit) : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_audio_reset_status(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा axg_audio_reset_data *rst =
		container_of(rcdev, काष्ठा axg_audio_reset_data, rstc);
	अचिन्हित पूर्णांक val, offset, bit;

	axg_audio_reset_reg_and_bit(rst, id, &offset, &bit);

	regmap_पढ़ो(rst->map, offset, &val);

	वापस !!(val & BIT(bit));
पूर्ण

अटल पूर्णांक axg_audio_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस axg_audio_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक axg_audio_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस axg_audio_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक axg_audio_reset_toggle(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;

	ret = axg_audio_reset_निश्चित(rcdev, id);
	अगर (ret)
		वापस ret;

	वापस axg_audio_reset_deनिश्चित(rcdev, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops axg_audio_rstc_ops = अणु
	.निश्चित = axg_audio_reset_निश्चित,
	.deनिश्चित = axg_audio_reset_deनिश्चित,
	.reset = axg_audio_reset_toggle,
	.status = axg_audio_reset_status,
पूर्ण;

अटल स्थिर काष्ठा regmap_config axg_audio_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= AUDIO_CLK_SPDIFOUT_B_CTRL,
पूर्ण;

काष्ठा audioclk_data अणु
	काष्ठा clk_regmap *स्थिर *regmap_clks;
	अचिन्हित पूर्णांक regmap_clk_num;
	काष्ठा clk_hw_onecell_data *hw_onecell_data;
	अचिन्हित पूर्णांक reset_offset;
	अचिन्हित पूर्णांक reset_num;
पूर्ण;

अटल पूर्णांक axg_audio_clkc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा audioclk_data *data;
	काष्ठा axg_audio_reset_data *rst;
	काष्ठा regmap *map;
	व्योम __iomem *regs;
	काष्ठा clk_hw *hw;
	पूर्णांक ret, i;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	map = devm_regmap_init_mmio(dev, regs, &axg_audio_regmap_cfg);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n", PTR_ERR(map));
		वापस PTR_ERR(map);
	पूर्ण

	/* Get the mandatory peripheral घड़ी */
	ret = devm_clk_get_enable(dev, "pclk");
	अगर (ret)
		वापस ret;

	ret = device_reset(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to reset device\n");
		वापस ret;
	पूर्ण

	/* Populate regmap क्रम the regmap backed घड़ीs */
	क्रम (i = 0; i < data->regmap_clk_num; i++)
		data->regmap_clks[i]->map = map;

	/* Take care to skip the रेजिस्टरed input घड़ीs */
	क्रम (i = AUD_CLKID_DDR_ARB; i < data->hw_onecell_data->num; i++) अणु
		स्थिर अक्षर *name;

		hw = data->hw_onecell_data->hws[i];
		/* array might be sparse */
		अगर (!hw)
			जारी;

		name = hw->init->name;

		ret = devm_clk_hw_रेजिस्टर(dev, hw);
		अगर (ret) अणु
			dev_err(dev, "failed to register clock %s\n", name);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					data->hw_onecell_data);
	अगर (ret)
		वापस ret;

	/* Stop here अगर there is no reset */
	अगर (!data->reset_num)
		वापस 0;

	rst = devm_kzalloc(dev, माप(*rst), GFP_KERNEL);
	अगर (!rst)
		वापस -ENOMEM;

	rst->map = map;
	rst->offset = data->reset_offset;
	rst->rstc.nr_resets = data->reset_num;
	rst->rstc.ops = &axg_audio_rstc_ops;
	rst->rstc.of_node = dev->of_node;
	rst->rstc.owner = THIS_MODULE;

	वापस devm_reset_controller_रेजिस्टर(dev, &rst->rstc);
पूर्ण

अटल स्थिर काष्ठा audioclk_data axg_audioclk_data = अणु
	.regmap_clks = axg_clk_regmaps,
	.regmap_clk_num = ARRAY_SIZE(axg_clk_regmaps),
	.hw_onecell_data = &axg_audio_hw_onecell_data,
पूर्ण;

अटल स्थिर काष्ठा audioclk_data g12a_audioclk_data = अणु
	.regmap_clks = g12a_clk_regmaps,
	.regmap_clk_num = ARRAY_SIZE(g12a_clk_regmaps),
	.hw_onecell_data = &g12a_audio_hw_onecell_data,
	.reset_offset = AUDIO_SW_RESET,
	.reset_num = 26,
पूर्ण;

अटल स्थिर काष्ठा audioclk_data sm1_audioclk_data = अणु
	.regmap_clks = sm1_clk_regmaps,
	.regmap_clk_num = ARRAY_SIZE(sm1_clk_regmaps),
	.hw_onecell_data = &sm1_audio_hw_onecell_data,
	.reset_offset = AUDIO_SM1_SW_RESET0,
	.reset_num = 39,
पूर्ण;

अटल स्थिर काष्ठा of_device_id clkc_match_table[] = अणु
	अणु
		.compatible = "amlogic,axg-audio-clkc",
		.data = &axg_audioclk_data
	पूर्ण, अणु
		.compatible = "amlogic,g12a-audio-clkc",
		.data = &g12a_audioclk_data
	पूर्ण, अणु
		.compatible = "amlogic,sm1-audio-clkc",
		.data = &sm1_audioclk_data
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clkc_match_table);

अटल काष्ठा platक्रमm_driver axg_audio_driver = अणु
	.probe		= axg_audio_clkc_probe,
	.driver		= अणु
		.name	= "axg-audio-clkc",
		.of_match_table = clkc_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_audio_driver);

MODULE_DESCRIPTION("Amlogic AXG/G12A/SM1 Audio Clock driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
