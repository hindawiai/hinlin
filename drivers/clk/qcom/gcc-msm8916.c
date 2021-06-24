<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015 Linaro Limited
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
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-msm8916.h>
#समावेश <dt-bindings/reset/qcom,gcc-msm8916.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_XO,
	P_GPLL0,
	P_GPLL0_AUX,
	P_BIMC,
	P_GPLL1,
	P_GPLL1_AUX,
	P_GPLL2,
	P_GPLL2_AUX,
	P_SLEEP_CLK,
	P_DSI0_PHYPLL_BYTE,
	P_DSI0_PHYPLL_DSI,
	P_EXT_PRI_I2S,
	P_EXT_SEC_I2S,
	P_EXT_MCLK,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0[] = अणु
	"xo",
	"gpll0_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_bimc_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_BIMC, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_bimc[] = अणु
	"xo",
	"gpll0_vote",
	"bimc_pll_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0a_gpll1_gpll2a_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_AUX, 3 पूर्ण,
	अणु P_GPLL1, 1 पूर्ण,
	अणु P_GPLL2_AUX, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0a_gpll1_gpll2a[] = अणु
	"xo",
	"gpll0_vote",
	"gpll1_vote",
	"gpll2_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_gpll2_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_GPLL2, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_gpll2[] = अणु
	"xo",
	"gpll0_vote",
	"gpll2_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0a_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_AUX, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0a[] = अणु
	"xo",
	"gpll0_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_gpll1a_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_GPLL1_AUX, 2 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_gpll1a_sleep[] = अणु
	"xo",
	"gpll0_vote",
	"gpll1_vote",
	"sleep_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_gpll1a_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_GPLL1_AUX, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_gpll1a[] = अणु
	"xo",
	"gpll0_vote",
	"gpll1_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_dsibyte_map[] = अणु
	अणु P_XO, 0, पूर्ण,
	अणु P_DSI0_PHYPLL_BYTE, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_dsibyte[] = अणु
	"xo",
	"dsi0pllbyte",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0a_dsibyte_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_AUX, 2 पूर्ण,
	अणु P_DSI0_PHYPLL_BYTE, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0a_dsibyte[] = अणु
	"xo",
	"gpll0_vote",
	"dsi0pllbyte",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_dsiphy_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_DSI0_PHYPLL_DSI, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_dsiphy[] = अणु
	"xo",
	"gpll0_vote",
	"dsi0pll",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0a_dsiphy_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_AUX, 2 पूर्ण,
	अणु P_DSI0_PHYPLL_DSI, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0a_dsiphy[] = अणु
	"xo",
	"gpll0_vote",
	"dsi0pll",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0a_gpll1_gpll2_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0_AUX, 1 पूर्ण,
	अणु P_GPLL1, 3 पूर्ण,
	अणु P_GPLL2, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0a_gpll1_gpll2[] = अणु
	"xo",
	"gpll0_vote",
	"gpll1_vote",
	"gpll2_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_gpll1_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_GPLL1, 2 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_gpll1_sleep[] = अणु
	"xo",
	"gpll0_vote",
	"gpll1_vote",
	"sleep_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll1_epi2s_emclk_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL1, 1 पूर्ण,
	अणु P_EXT_PRI_I2S, 2 पूर्ण,
	अणु P_EXT_MCLK, 3 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll1_epi2s_emclk_sleep[] = अणु
	"xo",
	"gpll1_vote",
	"ext_pri_i2s",
	"ext_mclk",
	"sleep_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll1_esi2s_emclk_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL1, 1 पूर्ण,
	अणु P_EXT_SEC_I2S, 2 पूर्ण,
	अणु P_EXT_MCLK, 3 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll1_esi2s_emclk_sleep[] = अणु
	"xo",
	"gpll1_vote",
	"ext_sec_i2s",
	"ext_mclk",
	"sleep_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_sleep[] = अणु
	"xo",
	"sleep_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll1_emclk_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL1, 1 पूर्ण,
	अणु P_EXT_MCLK, 2 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll1_emclk_sleep[] = अणु
	"xo",
	"gpll1_vote",
	"ext_mclk",
	"sleep_clk",
पूर्ण;

अटल काष्ठा clk_pll gpll0 = अणु
	.l_reg = 0x21004,
	.m_reg = 0x21008,
	.n_reg = 0x2100c,
	.config_reg = 0x21010,
	.mode_reg = 0x21000,
	.status_reg = 0x2101c,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap gpll0_vote = अणु
	.enable_reg = 0x45000,
	.enable_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll gpll1 = अणु
	.l_reg = 0x20004,
	.m_reg = 0x20008,
	.n_reg = 0x2000c,
	.config_reg = 0x20010,
	.mode_reg = 0x20000,
	.status_reg = 0x2001c,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap gpll1_vote = अणु
	.enable_reg = 0x45000,
	.enable_mask = BIT(1),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll gpll2 = अणु
	.l_reg = 0x4a004,
	.m_reg = 0x4a008,
	.n_reg = 0x4a00c,
	.config_reg = 0x4a010,
	.mode_reg = 0x4a000,
	.status_reg = 0x4a01c,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll2",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap gpll2_vote = अणु
	.enable_reg = 0x45000,
	.enable_mask = BIT(2),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll2_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll bimc_pll = अणु
	.l_reg = 0x23004,
	.m_reg = 0x23008,
	.n_reg = 0x2300c,
	.config_reg = 0x23010,
	.mode_reg = 0x23000,
	.status_reg = 0x2301c,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "bimc_pll",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap bimc_pll_vote = अणु
	.enable_reg = 0x45000,
	.enable_mask = BIT(3),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "bimc_pll_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "bimc_pll" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pcnoc_bfdcd_clk_src = अणु
	.cmd_rcgr = 0x27000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_bimc_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcnoc_bfdcd_clk_src",
		.parent_names = gcc_xo_gpll0_bimc,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 प्रणाली_noc_bfdcd_clk_src = अणु
	.cmd_rcgr = 0x26004,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_bimc_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "system_noc_bfdcd_clk_src",
		.parent_names = gcc_xo_gpll0_bimc,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_ahb_clk[] = अणु
	F(40000000, P_GPLL0, 10, 1, 2),
	F(80000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 camss_ahb_clk_src = अणु
	.cmd_rcgr = 0x5a000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_camss_ahb_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_ahb_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_apss_ahb_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 16, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(133330000, P_GPLL0, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 apss_ahb_clk_src = अणु
	.cmd_rcgr = 0x46000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_apss_ahb_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apss_ahb_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_csi0_1_clk[] = अणु
	F(100000000, P_GPLL0, 8, 0,	0),
	F(200000000, P_GPLL0, 4, 0,	0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0_clk_src = अणु
	.cmd_rcgr = 0x4e020,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_camss_csi0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1_clk_src = अणु
	.cmd_rcgr = 0x4f020,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_camss_csi0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_oxili_gfx3d_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0_AUX, 16, 0, 0),
	F(80000000, P_GPLL0_AUX, 10, 0, 0),
	F(100000000, P_GPLL0_AUX, 8, 0, 0),
	F(160000000, P_GPLL0_AUX, 5, 0, 0),
	F(177780000, P_GPLL0_AUX, 4.5, 0, 0),
	F(200000000, P_GPLL0_AUX, 4, 0, 0),
	F(266670000, P_GPLL0_AUX, 3, 0, 0),
	F(294912000, P_GPLL1, 3, 0, 0),
	F(310000000, P_GPLL2, 3, 0, 0),
	F(400000000, P_GPLL0_AUX, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gfx3d_clk_src = अणु
	.cmd_rcgr = 0x59000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0a_gpll1_gpll2a_map,
	.freq_tbl = ftbl_gcc_oxili_gfx3d_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gfx3d_clk_src",
		.parent_names = gcc_xo_gpll0a_gpll1_gpll2a,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_vfe0_clk[] = अणु
	F(50000000, P_GPLL0, 16, 0, 0),
	F(80000000, P_GPLL0, 10, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(160000000, P_GPLL0, 5, 0, 0),
	F(177780000, P_GPLL0, 4.5, 0, 0),
	F(200000000, P_GPLL0, 4, 0, 0),
	F(266670000, P_GPLL0, 3, 0, 0),
	F(320000000, P_GPLL0, 2.5, 0, 0),
	F(400000000, P_GPLL0, 2, 0, 0),
	F(465000000, P_GPLL2, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vfe0_clk_src = अणु
	.cmd_rcgr = 0x58000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll2_map,
	.freq_tbl = ftbl_gcc_camss_vfe0_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vfe0_clk_src",
		.parent_names = gcc_xo_gpll0_gpll2,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_qup1_6_i2c_apps_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 16, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0200c,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_qup1_6_spi_apps_clk[] = अणु
	F(100000, P_XO, 16, 2, 24),
	F(250000, P_XO, 16, 5, 24),
	F(500000, P_XO, 8, 5, 24),
	F(960000, P_XO, 10, 1, 2),
	F(1000000, P_XO, 4, 5, 24),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(16000000, P_GPLL0, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPLL0, 16, 1, 2),
	F(50000000, P_GPLL0, 16, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x02024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x03000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup2_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x03014,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup2_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup3_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x04000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup3_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup3_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x04024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup3_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup4_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x05000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup4_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup4_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x05024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup4_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup5_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x06000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup5_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup5_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x06024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup5_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup6_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x07000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup6_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup6_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x07024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup6_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_uart1_6_apps_clk[] = अणु
	F(3686400, P_GPLL0, 1, 72, 15625),
	F(7372800, P_GPLL0, 1, 144, 15625),
	F(14745600, P_GPLL0, 1, 288, 15625),
	F(16000000, P_GPLL0, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPLL0, 1, 3, 100),
	F(25000000, P_GPLL0, 16, 1, 2),
	F(32000000, P_GPLL0, 1, 1, 25),
	F(40000000, P_GPLL0, 1, 1, 20),
	F(46400000, P_GPLL0, 1, 29, 500),
	F(48000000, P_GPLL0, 1, 3, 50),
	F(51200000, P_GPLL0, 1, 8, 125),
	F(56000000, P_GPLL0, 1, 7, 100),
	F(58982400, P_GPLL0, 1, 1152, 15625),
	F(60000000, P_GPLL0, 1, 3, 40),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart1_apps_clk_src = अणु
	.cmd_rcgr = 0x02044,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart1_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart2_apps_clk_src = अणु
	.cmd_rcgr = 0x03034,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart2_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_cci_clk[] = अणु
	F(19200000,	P_XO, 1, 0,	0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cci_clk_src = अणु
	.cmd_rcgr = 0x51000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0a_map,
	.freq_tbl = ftbl_gcc_camss_cci_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cci_clk_src",
		.parent_names = gcc_xo_gpll0a,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_gp0_1_clk[] = अणु
	F(100000000, P_GPLL0, 8, 0, 0),
	F(200000000, P_GPLL0, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 camss_gp0_clk_src = अणु
	.cmd_rcgr = 0x54000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_camss_gp0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_gp0_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 camss_gp1_clk_src = अणु
	.cmd_rcgr = 0x55000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_camss_gp0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "camss_gp1_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_jpeg0_clk[] = अणु
	F(133330000, P_GPLL0, 6, 0,	0),
	F(266670000, P_GPLL0, 3, 0,	0),
	F(320000000, P_GPLL0, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 jpeg0_clk_src = अणु
	.cmd_rcgr = 0x57000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_camss_jpeg0_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "jpeg0_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_mclk0_1_clk[] = अणु
	F(9600000, P_XO, 2, 0, 0),
	F(23880000, P_GPLL0, 1, 2, 67),
	F(66670000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mclk0_clk_src = अणु
	.cmd_rcgr = 0x52000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_camss_mclk0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk0_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 mclk1_clk_src = अणु
	.cmd_rcgr = 0x53000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_camss_mclk0_1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mclk1_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_csi0_1phyसमयr_clk[] = अणु
	F(100000000, P_GPLL0, 8, 0,	0),
	F(200000000, P_GPLL0, 4, 0,	0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 csi0phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x4e000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_map,
	.freq_tbl = ftbl_gcc_camss_csi0_1phyसमयr_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi0phytimer_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 csi1phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x4f000,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_map,
	.freq_tbl = ftbl_gcc_camss_csi0_1phyसमयr_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "csi1phytimer_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_camss_cpp_clk[] = अणु
	F(160000000, P_GPLL0, 5, 0, 0),
	F(320000000, P_GPLL0, 2.5, 0, 0),
	F(465000000, P_GPLL2, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cpp_clk_src = अणु
	.cmd_rcgr = 0x58018,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll2_map,
	.freq_tbl = ftbl_gcc_camss_cpp_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cpp_clk_src",
		.parent_names = gcc_xo_gpll0_gpll2,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_crypto_clk[] = अणु
	F(50000000, P_GPLL0, 16, 0, 0),
	F(80000000, P_GPLL0, 10, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(160000000, P_GPLL0, 5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 crypto_clk_src = अणु
	.cmd_rcgr = 0x16004,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_crypto_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "crypto_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_gp1_3_clk[] = अणु
	F(19200000, P_XO, 1, 0,	0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gp1_clk_src = अणु
	.cmd_rcgr = 0x08004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_gp1_3_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp1_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp2_clk_src = अणु
	.cmd_rcgr = 0x09004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_gp1_3_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp2_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp3_clk_src = अणु
	.cmd_rcgr = 0x0a004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll1a_sleep_map,
	.freq_tbl = ftbl_gcc_gp1_3_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp3_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1a_sleep,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 byte0_clk_src = अणु
	.cmd_rcgr = 0x4d044,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0a_dsibyte_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "byte0_clk_src",
		.parent_names = gcc_xo_gpll0a_dsibyte,
		.num_parents = 3,
		.ops = &clk_byte2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_mdss_esc0_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 esc0_clk_src = अणु
	.cmd_rcgr = 0x4d05c,
	.hid_width = 5,
	.parent_map = gcc_xo_dsibyte_map,
	.freq_tbl = ftbl_gcc_mdss_esc0_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "esc0_clk_src",
		.parent_names = gcc_xo_dsibyte,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_mdss_mdp_clk[] = अणु
	F(50000000, P_GPLL0, 16, 0, 0),
	F(80000000, P_GPLL0, 10, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(160000000, P_GPLL0, 5, 0, 0),
	F(177780000, P_GPLL0, 4.5, 0, 0),
	F(200000000, P_GPLL0, 4, 0, 0),
	F(266670000, P_GPLL0, 3, 0, 0),
	F(320000000, P_GPLL0, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 mdp_clk_src = अणु
	.cmd_rcgr = 0x4d014,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_dsiphy_map,
	.freq_tbl = ftbl_gcc_mdss_mdp_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "mdp_clk_src",
		.parent_names = gcc_xo_gpll0_dsiphy,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pclk0_clk_src = अणु
	.cmd_rcgr = 0x4d000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0a_dsiphy_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pclk0_clk_src",
		.parent_names = gcc_xo_gpll0a_dsiphy,
		.num_parents = 3,
		.ops = &clk_pixel_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_mdss_vsync_clk[] = अणु
	F(19200000, P_XO, 1, 0,	0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vsync_clk_src = अणु
	.cmd_rcgr = 0x4d02c,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0a_map,
	.freq_tbl = ftbl_gcc_mdss_vsync_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vsync_clk_src",
		.parent_names = gcc_xo_gpll0a,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pdm2_clk[] = अणु
	F(64000000, P_GPLL0, 12.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pdm2_clk_src = अणु
	.cmd_rcgr = 0x44010,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_pdm2_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pdm2_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_apps_clk[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0, 10, 1, 4),
	F(25000000, P_GPLL0, 16, 1, 2),
	F(50000000, P_GPLL0, 16, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(177770000, P_GPLL0, 4.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc1_apps_clk_src = अणु
	.cmd_rcgr = 0x42004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_sdcc1_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc1_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc2_apps_clk[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0, 10, 1, 4),
	F(25000000, P_GPLL0, 16, 1, 2),
	F(50000000, P_GPLL0, 16, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(200000000, P_GPLL0, 4, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x43004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_sdcc2_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc2_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_apss_tcu_clk[] = अणु
	F(155000000, P_GPLL2, 6, 0, 0),
	F(310000000, P_GPLL2, 3, 0, 0),
	F(400000000, P_GPLL0, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 apss_tcu_clk_src = अणु
	.cmd_rcgr = 0x1207c,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0a_gpll1_gpll2_map,
	.freq_tbl = ftbl_gcc_apss_tcu_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apss_tcu_clk_src",
		.parent_names = gcc_xo_gpll0a_gpll1_gpll2,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_bimc_gpu_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	F(200000000, P_GPLL0, 4, 0, 0),
	F(266500000, P_BIMC, 4, 0, 0),
	F(400000000, P_GPLL0, 2, 0, 0),
	F(533000000, P_BIMC, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 bimc_gpu_clk_src = अणु
	.cmd_rcgr = 0x31028,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_bimc_map,
	.freq_tbl = ftbl_gcc_bimc_gpu_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "bimc_gpu_clk_src",
		.parent_names = gcc_xo_gpll0_bimc,
		.num_parents = 3,
		.flags = CLK_GET_RATE_NOCACHE,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hs_प्रणाली_clk[] = अणु
	F(80000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hs_प्रणाली_clk_src = अणु
	.cmd_rcgr = 0x41010,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb_hs_प्रणाली_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb_hs_system_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ultaudio_ahb_clk[] = अणु
	F(3200000, P_XO, 6, 0, 0),
	F(6400000, P_XO, 3, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPLL0, 10, 1, 2),
	F(66670000, P_GPLL0, 12, 0, 0),
	F(80000000, P_GPLL0, 10, 0, 0),
	F(100000000, P_GPLL0, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ultaudio_ahbfabric_clk_src = अणु
	.cmd_rcgr = 0x1c010,
	.hid_width = 5,
	.mnd_width = 8,
	.parent_map = gcc_xo_gpll0_gpll1_sleep_map,
	.freq_tbl = ftbl_gcc_ultaudio_ahb_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ultaudio_ahbfabric_clk_src",
		.parent_names = gcc_xo_gpll0_gpll1_sleep,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_ahbfabric_ixfabric_clk = अणु
	.halt_reg = 0x1c028,
	.clkr = अणु
		.enable_reg = 0x1c028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_ahbfabric_ixfabric_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_ahbfabric_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_ahbfabric_ixfabric_lpm_clk = अणु
	.halt_reg = 0x1c024,
	.clkr = अणु
		.enable_reg = 0x1c024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_ahbfabric_ixfabric_lpm_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_ahbfabric_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ultaudio_lpaअगर_i2s_clk[] = अणु
	F(128000, P_XO, 10, 1, 15),
	F(256000, P_XO, 5, 1, 15),
	F(384000, P_XO, 5, 1, 10),
	F(512000, P_XO, 5, 2, 15),
	F(576000, P_XO, 5, 3, 20),
	F(705600, P_GPLL1, 16, 1, 80),
	F(768000, P_XO, 5, 1, 5),
	F(800000, P_XO, 5, 5, 24),
	F(1024000, P_XO, 5, 4, 15),
	F(1152000, P_XO, 1, 3, 50),
	F(1411200, P_GPLL1, 16, 1, 40),
	F(1536000, P_XO, 1, 2, 25),
	F(1600000, P_XO, 12, 0, 0),
	F(1728000, P_XO, 5, 9, 20),
	F(2048000, P_XO, 5, 8, 15),
	F(2304000, P_XO, 5, 3, 5),
	F(2400000, P_XO, 8, 0, 0),
	F(2822400, P_GPLL1, 16, 1, 20),
	F(3072000, P_XO, 5, 4, 5),
	F(4096000, P_GPLL1, 9, 2, 49),
	F(4800000, P_XO, 4, 0, 0),
	F(5644800, P_GPLL1, 16, 1, 10),
	F(6144000, P_GPLL1, 7, 1, 21),
	F(8192000, P_GPLL1, 9, 4, 49),
	F(9600000, P_XO, 2, 0, 0),
	F(11289600, P_GPLL1, 16, 1, 5),
	F(12288000, P_GPLL1, 7, 2, 21),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ultaudio_lpaअगर_pri_i2s_clk_src = अणु
	.cmd_rcgr = 0x1c054,
	.hid_width = 5,
	.mnd_width = 8,
	.parent_map = gcc_xo_gpll1_epi2s_emclk_sleep_map,
	.freq_tbl = ftbl_gcc_ultaudio_lpaअगर_i2s_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ultaudio_lpaif_pri_i2s_clk_src",
		.parent_names = gcc_xo_gpll1_epi2s_emclk_sleep,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_lpaअगर_pri_i2s_clk = अणु
	.halt_reg = 0x1c068,
	.clkr = अणु
		.enable_reg = 0x1c068,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_lpaif_pri_i2s_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_lpaif_pri_i2s_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 ultaudio_lpaअगर_sec_i2s_clk_src = अणु
	.cmd_rcgr = 0x1c06c,
	.hid_width = 5,
	.mnd_width = 8,
	.parent_map = gcc_xo_gpll1_esi2s_emclk_sleep_map,
	.freq_tbl = ftbl_gcc_ultaudio_lpaअगर_i2s_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ultaudio_lpaif_sec_i2s_clk_src",
		.parent_names = gcc_xo_gpll1_esi2s_emclk_sleep,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_lpaअगर_sec_i2s_clk = अणु
	.halt_reg = 0x1c080,
	.clkr = अणु
		.enable_reg = 0x1c080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_lpaif_sec_i2s_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_lpaif_sec_i2s_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 ultaudio_lpaअगर_aux_i2s_clk_src = अणु
	.cmd_rcgr = 0x1c084,
	.hid_width = 5,
	.mnd_width = 8,
	.parent_map = gcc_xo_gpll1_emclk_sleep_map,
	.freq_tbl = ftbl_gcc_ultaudio_lpaअगर_i2s_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ultaudio_lpaif_aux_i2s_clk_src",
		.parent_names = gcc_xo_gpll1_esi2s_emclk_sleep,
		.num_parents = 5,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_lpaअगर_aux_i2s_clk = अणु
	.halt_reg = 0x1c098,
	.clkr = अणु
		.enable_reg = 0x1c098,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_lpaif_aux_i2s_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_lpaif_aux_i2s_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ultaudio_xo_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ultaudio_xo_clk_src = अणु
	.cmd_rcgr = 0x1c034,
	.hid_width = 5,
	.parent_map = gcc_xo_sleep_map,
	.freq_tbl = ftbl_gcc_ultaudio_xo_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ultaudio_xo_clk_src",
		.parent_names = gcc_xo_sleep,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_avsync_xo_clk = अणु
	.halt_reg = 0x1c04c,
	.clkr = अणु
		.enable_reg = 0x1c04c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_avsync_xo_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_xo_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_stc_xo_clk = अणु
	.halt_reg = 0x1c050,
	.clkr = अणु
		.enable_reg = 0x1c050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_stc_xo_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ultaudio_xo_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_codec_clk[] = अणु
	F(9600000, P_XO, 2, 0, 0),
	F(12288000, P_XO, 1, 16, 25),
	F(19200000, P_XO, 1, 0, 0),
	F(11289600, P_EXT_MCLK, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 codec_digcodec_clk_src = अणु
	.cmd_rcgr = 0x1c09c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll1_emclk_sleep_map,
	.freq_tbl = ftbl_codec_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "codec_digcodec_clk_src",
		.parent_names = gcc_xo_gpll1_emclk_sleep,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_codec_digcodec_clk = अणु
	.halt_reg = 0x1c0b0,
	.clkr = अणु
		.enable_reg = 0x1c0b0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_codec_digcodec_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"codec_digcodec_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_pcnoc_mport_clk = अणु
	.halt_reg = 0x1c000,
	.clkr = अणु
		.enable_reg = 0x1c000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_pcnoc_mport_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ultaudio_pcnoc_sway_clk = अणु
	.halt_reg = 0x1c004,
	.clkr = अणु
		.enable_reg = 0x1c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ultaudio_pcnoc_sway_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_venus0_vcodec0_clk[] = अणु
	F(100000000, P_GPLL0, 8, 0, 0),
	F(160000000, P_GPLL0, 5, 0, 0),
	F(228570000, P_GPLL0, 3.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 vcodec0_clk_src = अणु
	.cmd_rcgr = 0x4C000,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_venus0_vcodec0_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "vcodec0_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_ahb_clk = अणु
	.halt_reg = 0x01008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x45004,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_sleep_clk = अणु
	.halt_reg = 0x01004,
	.clkr = अणु
		.enable_reg = 0x01004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x02008,
	.clkr = अणु
		.enable_reg = 0x02008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup1_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_spi_apps_clk = अणु
	.halt_reg = 0x02004,
	.clkr = अणु
		.enable_reg = 0x02004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup1_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_i2c_apps_clk = अणु
	.halt_reg = 0x03010,
	.clkr = अणु
		.enable_reg = 0x03010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup2_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_spi_apps_clk = अणु
	.halt_reg = 0x0300c,
	.clkr = अणु
		.enable_reg = 0x0300c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup2_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup3_i2c_apps_clk = अणु
	.halt_reg = 0x04020,
	.clkr = अणु
		.enable_reg = 0x04020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup3_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup3_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup3_spi_apps_clk = अणु
	.halt_reg = 0x0401c,
	.clkr = अणु
		.enable_reg = 0x0401c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup3_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup3_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup4_i2c_apps_clk = अणु
	.halt_reg = 0x05020,
	.clkr = अणु
		.enable_reg = 0x05020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup4_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup4_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup4_spi_apps_clk = अणु
	.halt_reg = 0x0501c,
	.clkr = अणु
		.enable_reg = 0x0501c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup4_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup4_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup5_i2c_apps_clk = अणु
	.halt_reg = 0x06020,
	.clkr = अणु
		.enable_reg = 0x06020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup5_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup5_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup5_spi_apps_clk = अणु
	.halt_reg = 0x0601c,
	.clkr = अणु
		.enable_reg = 0x0601c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup5_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup5_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup6_i2c_apps_clk = अणु
	.halt_reg = 0x07020,
	.clkr = अणु
		.enable_reg = 0x07020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup6_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup6_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup6_spi_apps_clk = अणु
	.halt_reg = 0x0701c,
	.clkr = अणु
		.enable_reg = 0x0701c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup6_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup6_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart1_apps_clk = अणु
	.halt_reg = 0x0203c,
	.clkr = अणु
		.enable_reg = 0x0203c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart2_apps_clk = अणु
	.halt_reg = 0x0302c,
	.clkr = अणु
		.enable_reg = 0x0302c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_boot_rom_ahb_clk = अणु
	.halt_reg = 0x1300c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x45004,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_boot_rom_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_cci_ahb_clk = अणु
	.halt_reg = 0x5101c,
	.clkr = अणु
		.enable_reg = 0x5101c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_cci_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_cci_clk = अणु
	.halt_reg = 0x51018,
	.clkr = अणु
		.enable_reg = 0x51018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_cci_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cci_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi0_ahb_clk = अणु
	.halt_reg = 0x4e040,
	.clkr = अणु
		.enable_reg = 0x4e040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi0_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi0_clk = अणु
	.halt_reg = 0x4e03c,
	.clkr = अणु
		.enable_reg = 0x4e03c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi0phy_clk = अणु
	.halt_reg = 0x4e048,
	.clkr = अणु
		.enable_reg = 0x4e048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi0phy_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi0pix_clk = अणु
	.halt_reg = 0x4e058,
	.clkr = अणु
		.enable_reg = 0x4e058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi0pix_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi0rdi_clk = अणु
	.halt_reg = 0x4e050,
	.clkr = अणु
		.enable_reg = 0x4e050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi0rdi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi1_ahb_clk = अणु
	.halt_reg = 0x4f040,
	.clkr = अणु
		.enable_reg = 0x4f040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi1_clk = अणु
	.halt_reg = 0x4f03c,
	.clkr = अणु
		.enable_reg = 0x4f03c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi1phy_clk = अणु
	.halt_reg = 0x4f048,
	.clkr = अणु
		.enable_reg = 0x4f048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi1phy_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi1pix_clk = अणु
	.halt_reg = 0x4f058,
	.clkr = अणु
		.enable_reg = 0x4f058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi1pix_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi1rdi_clk = अणु
	.halt_reg = 0x4f050,
	.clkr = अणु
		.enable_reg = 0x4f050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi1rdi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi_vfe0_clk = अणु
	.halt_reg = 0x58050,
	.clkr = अणु
		.enable_reg = 0x58050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi_vfe0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"vfe0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_gp0_clk = अणु
	.halt_reg = 0x54018,
	.clkr = अणु
		.enable_reg = 0x54018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_gp0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_gp0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_gp1_clk = अणु
	.halt_reg = 0x55018,
	.clkr = अणु
		.enable_reg = 0x55018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_gp1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_gp1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_ispअगर_ahb_clk = अणु
	.halt_reg = 0x50004,
	.clkr = अणु
		.enable_reg = 0x50004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_ispif_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_jpeg0_clk = अणु
	.halt_reg = 0x57020,
	.clkr = अणु
		.enable_reg = 0x57020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_jpeg0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"jpeg0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_jpeg_ahb_clk = अणु
	.halt_reg = 0x57024,
	.clkr = अणु
		.enable_reg = 0x57024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_jpeg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_jpeg_axi_clk = अणु
	.halt_reg = 0x57028,
	.clkr = अणु
		.enable_reg = 0x57028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_jpeg_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_mclk0_clk = अणु
	.halt_reg = 0x52018,
	.clkr = अणु
		.enable_reg = 0x52018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_mclk0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"mclk0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_mclk1_clk = अणु
	.halt_reg = 0x53018,
	.clkr = अणु
		.enable_reg = 0x53018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_mclk1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"mclk1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_micro_ahb_clk = अणु
	.halt_reg = 0x5600c,
	.clkr = अणु
		.enable_reg = 0x5600c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_micro_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi0phyसमयr_clk = अणु
	.halt_reg = 0x4e01c,
	.clkr = अणु
		.enable_reg = 0x4e01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi0phytimer_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi0phytimer_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_csi1phyसमयr_clk = अणु
	.halt_reg = 0x4f01c,
	.clkr = अणु
		.enable_reg = 0x4f01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_csi1phytimer_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"csi1phytimer_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_ahb_clk = अणु
	.halt_reg = 0x5a014,
	.clkr = अणु
		.enable_reg = 0x5a014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_top_ahb_clk = अणु
	.halt_reg = 0x56004,
	.clkr = अणु
		.enable_reg = 0x56004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_top_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_cpp_ahb_clk = अणु
	.halt_reg = 0x58040,
	.clkr = अणु
		.enable_reg = 0x58040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_cpp_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_cpp_clk = अणु
	.halt_reg = 0x5803c,
	.clkr = अणु
		.enable_reg = 0x5803c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_cpp_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cpp_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_vfe0_clk = अणु
	.halt_reg = 0x58038,
	.clkr = अणु
		.enable_reg = 0x58038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_vfe0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"vfe0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_vfe_ahb_clk = अणु
	.halt_reg = 0x58044,
	.clkr = अणु
		.enable_reg = 0x58044,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_vfe_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"camss_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_camss_vfe_axi_clk = अणु
	.halt_reg = 0x58048,
	.clkr = अणु
		.enable_reg = 0x58048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_camss_vfe_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_crypto_ahb_clk = अणु
	.halt_reg = 0x16024,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x45004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_crypto_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_crypto_axi_clk = अणु
	.halt_reg = 0x16020,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x45004,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_crypto_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_crypto_clk = अणु
	.halt_reg = 0x1601c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x45004,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_crypto_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"crypto_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_oxili_gmem_clk = अणु
	.halt_reg = 0x59024,
	.clkr = अणु
		.enable_reg = 0x59024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_oxili_gmem_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gfx3d_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp1_clk = अणु
	.halt_reg = 0x08000,
	.clkr = अणु
		.enable_reg = 0x08000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp2_clk = अणु
	.halt_reg = 0x09000,
	.clkr = अणु
		.enable_reg = 0x09000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp2_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp3_clk = अणु
	.halt_reg = 0x0a000,
	.clkr = अणु
		.enable_reg = 0x0a000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp3_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp3_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_ahb_clk = अणु
	.halt_reg = 0x4d07c,
	.clkr = अणु
		.enable_reg = 0x4d07c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_axi_clk = अणु
	.halt_reg = 0x4d080,
	.clkr = अणु
		.enable_reg = 0x4d080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_byte0_clk = अणु
	.halt_reg = 0x4d094,
	.clkr = अणु
		.enable_reg = 0x4d094,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_byte0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"byte0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_esc0_clk = अणु
	.halt_reg = 0x4d098,
	.clkr = अणु
		.enable_reg = 0x4d098,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_esc0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"esc0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_mdp_clk = अणु
	.halt_reg = 0x4D088,
	.clkr = अणु
		.enable_reg = 0x4D088,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_mdp_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"mdp_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_pclk0_clk = अणु
	.halt_reg = 0x4d084,
	.clkr = अणु
		.enable_reg = 0x4d084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_pclk0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pclk0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdss_vsync_clk = अणु
	.halt_reg = 0x4d090,
	.clkr = अणु
		.enable_reg = 0x4d090,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdss_vsync_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"vsync_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_cfg_ahb_clk = अणु
	.halt_reg = 0x49000,
	.clkr = अणु
		.enable_reg = 0x49000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_q6_bimc_axi_clk = अणु
	.halt_reg = 0x49004,
	.clkr = अणु
		.enable_reg = 0x49004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mss_q6_bimc_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"bimc_ddr_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_oxili_ahb_clk = अणु
	.halt_reg = 0x59028,
	.clkr = अणु
		.enable_reg = 0x59028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_oxili_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_oxili_gfx3d_clk = अणु
	.halt_reg = 0x59020,
	.clkr = अणु
		.enable_reg = 0x59020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_oxili_gfx3d_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gfx3d_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm2_clk = अणु
	.halt_reg = 0x4400c,
	.clkr = अणु
		.enable_reg = 0x4400c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pdm2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pdm2_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm_ahb_clk = अणु
	.halt_reg = 0x44004,
	.clkr = अणु
		.enable_reg = 0x44004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pdm_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_prng_ahb_clk = अणु
	.halt_reg = 0x13004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x45004,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_prng_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_ahb_clk = अणु
	.halt_reg = 0x4201c,
	.clkr = अणु
		.enable_reg = 0x4201c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_apps_clk = अणु
	.halt_reg = 0x42018,
	.clkr = अणु
		.enable_reg = 0x42018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sdcc1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc2_ahb_clk = अणु
	.halt_reg = 0x4301c,
	.clkr = अणु
		.enable_reg = 0x4301c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc2_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc2_apps_clk = अणु
	.halt_reg = 0x43018,
	.clkr = अणु
		.enable_reg = 0x43018,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc2_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sdcc2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 bimc_ddr_clk_src = अणु
	.cmd_rcgr = 0x32004,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_bimc_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "bimc_ddr_clk_src",
		.parent_names = gcc_xo_gpll0_bimc,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
		.flags = CLK_GET_RATE_NOCACHE,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_apss_tcu_clk = अणु
	.halt_reg = 0x12018,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_apss_tcu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"bimc_ddr_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gfx_tcu_clk = अणु
	.halt_reg = 0x12020,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gfx_tcu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"bimc_ddr_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gtcu_ahb_clk = अणु
	.halt_reg = 0x12044,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gtcu_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_bimc_gfx_clk = अणु
	.halt_reg = 0x31024,
	.clkr = अणु
		.enable_reg = 0x31024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_bimc_gfx_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"bimc_gpu_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_bimc_gpu_clk = अणु
	.halt_reg = 0x31040,
	.clkr = अणु
		.enable_reg = 0x31040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_bimc_gpu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"bimc_gpu_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_jpeg_tbu_clk = अणु
	.halt_reg = 0x12034,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_jpeg_tbu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mdp_tbu_clk = अणु
	.halt_reg = 0x1201c,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_mdp_tbu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_smmu_cfg_clk = अणु
	.halt_reg = 0x12038,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_smmu_cfg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_venus_tbu_clk = अणु
	.halt_reg = 0x12014,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_venus_tbu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_vfe_tbu_clk = अणु
	.halt_reg = 0x1203c,
	.clkr = अणु
		.enable_reg = 0x4500c,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_vfe_tbu_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2a_phy_sleep_clk = अणु
	.halt_reg = 0x4102c,
	.clkr = अणु
		.enable_reg = 0x4102c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb2a_phy_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_ahb_clk = अणु
	.halt_reg = 0x41008,
	.clkr = अणु
		.enable_reg = 0x41008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hs_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_प्रणाली_clk = अणु
	.halt_reg = 0x41004,
	.clkr = अणु
		.enable_reg = 0x41004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hs_system_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb_hs_system_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_venus0_ahb_clk = अणु
	.halt_reg = 0x4c020,
	.clkr = अणु
		.enable_reg = 0x4c020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_venus0_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_venus0_axi_clk = अणु
	.halt_reg = 0x4c024,
	.clkr = अणु
		.enable_reg = 0x4c024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_venus0_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_bfdcd_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_venus0_vcodec0_clk = अणु
	.halt_reg = 0x4c01c,
	.clkr = अणु
		.enable_reg = 0x4c01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_venus0_vcodec0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"vcodec0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc venus_gdsc = अणु
	.gdscr = 0x4c018,
	.pd = अणु
		.name = "venus",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc mdss_gdsc = अणु
	.gdscr = 0x4d078,
	.pd = अणु
		.name = "mdss",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc jpeg_gdsc = अणु
	.gdscr = 0x5701c,
	.pd = अणु
		.name = "jpeg",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc vfe_gdsc = अणु
	.gdscr = 0x58034,
	.pd = अणु
		.name = "vfe",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc oxili_gdsc = अणु
	.gdscr = 0x5901c,
	.pd = अणु
		.name = "oxili",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_msm8916_घड़ीs[] = अणु
	[GPLL0] = &gpll0.clkr,
	[GPLL0_VOTE] = &gpll0_vote,
	[BIMC_PLL] = &bimc_pll.clkr,
	[BIMC_PLL_VOTE] = &bimc_pll_vote,
	[GPLL1] = &gpll1.clkr,
	[GPLL1_VOTE] = &gpll1_vote,
	[GPLL2] = &gpll2.clkr,
	[GPLL2_VOTE] = &gpll2_vote,
	[PCNOC_BFDCD_CLK_SRC] = &pcnoc_bfdcd_clk_src.clkr,
	[SYSTEM_NOC_BFDCD_CLK_SRC] = &प्रणाली_noc_bfdcd_clk_src.clkr,
	[CAMSS_AHB_CLK_SRC] = &camss_ahb_clk_src.clkr,
	[APSS_AHB_CLK_SRC] = &apss_ahb_clk_src.clkr,
	[CSI0_CLK_SRC] = &csi0_clk_src.clkr,
	[CSI1_CLK_SRC] = &csi1_clk_src.clkr,
	[GFX3D_CLK_SRC] = &gfx3d_clk_src.clkr,
	[VFE0_CLK_SRC] = &vfe0_clk_src.clkr,
	[BLSP1_QUP1_I2C_APPS_CLK_SRC] = &blsp1_qup1_i2c_apps_clk_src.clkr,
	[BLSP1_QUP1_SPI_APPS_CLK_SRC] = &blsp1_qup1_spi_apps_clk_src.clkr,
	[BLSP1_QUP2_I2C_APPS_CLK_SRC] = &blsp1_qup2_i2c_apps_clk_src.clkr,
	[BLSP1_QUP2_SPI_APPS_CLK_SRC] = &blsp1_qup2_spi_apps_clk_src.clkr,
	[BLSP1_QUP3_I2C_APPS_CLK_SRC] = &blsp1_qup3_i2c_apps_clk_src.clkr,
	[BLSP1_QUP3_SPI_APPS_CLK_SRC] = &blsp1_qup3_spi_apps_clk_src.clkr,
	[BLSP1_QUP4_I2C_APPS_CLK_SRC] = &blsp1_qup4_i2c_apps_clk_src.clkr,
	[BLSP1_QUP4_SPI_APPS_CLK_SRC] = &blsp1_qup4_spi_apps_clk_src.clkr,
	[BLSP1_QUP5_I2C_APPS_CLK_SRC] = &blsp1_qup5_i2c_apps_clk_src.clkr,
	[BLSP1_QUP5_SPI_APPS_CLK_SRC] = &blsp1_qup5_spi_apps_clk_src.clkr,
	[BLSP1_QUP6_I2C_APPS_CLK_SRC] = &blsp1_qup6_i2c_apps_clk_src.clkr,
	[BLSP1_QUP6_SPI_APPS_CLK_SRC] = &blsp1_qup6_spi_apps_clk_src.clkr,
	[BLSP1_UART1_APPS_CLK_SRC] = &blsp1_uart1_apps_clk_src.clkr,
	[BLSP1_UART2_APPS_CLK_SRC] = &blsp1_uart2_apps_clk_src.clkr,
	[CCI_CLK_SRC] = &cci_clk_src.clkr,
	[CAMSS_GP0_CLK_SRC] = &camss_gp0_clk_src.clkr,
	[CAMSS_GP1_CLK_SRC] = &camss_gp1_clk_src.clkr,
	[JPEG0_CLK_SRC] = &jpeg0_clk_src.clkr,
	[MCLK0_CLK_SRC] = &mclk0_clk_src.clkr,
	[MCLK1_CLK_SRC] = &mclk1_clk_src.clkr,
	[CSI0PHYTIMER_CLK_SRC] = &csi0phyसमयr_clk_src.clkr,
	[CSI1PHYTIMER_CLK_SRC] = &csi1phyसमयr_clk_src.clkr,
	[CPP_CLK_SRC] = &cpp_clk_src.clkr,
	[CRYPTO_CLK_SRC] = &crypto_clk_src.clkr,
	[GP1_CLK_SRC] = &gp1_clk_src.clkr,
	[GP2_CLK_SRC] = &gp2_clk_src.clkr,
	[GP3_CLK_SRC] = &gp3_clk_src.clkr,
	[BYTE0_CLK_SRC] = &byte0_clk_src.clkr,
	[ESC0_CLK_SRC] = &esc0_clk_src.clkr,
	[MDP_CLK_SRC] = &mdp_clk_src.clkr,
	[PCLK0_CLK_SRC] = &pclk0_clk_src.clkr,
	[VSYNC_CLK_SRC] = &vsync_clk_src.clkr,
	[PDM2_CLK_SRC] = &pdm2_clk_src.clkr,
	[SDCC1_APPS_CLK_SRC] = &sdcc1_apps_clk_src.clkr,
	[SDCC2_APPS_CLK_SRC] = &sdcc2_apps_clk_src.clkr,
	[APSS_TCU_CLK_SRC] = &apss_tcu_clk_src.clkr,
	[USB_HS_SYSTEM_CLK_SRC] = &usb_hs_प्रणाली_clk_src.clkr,
	[VCODEC0_CLK_SRC] = &vcodec0_clk_src.clkr,
	[GCC_BLSP1_AHB_CLK] = &gcc_blsp1_ahb_clk.clkr,
	[GCC_BLSP1_SLEEP_CLK] = &gcc_blsp1_sleep_clk.clkr,
	[GCC_BLSP1_QUP1_I2C_APPS_CLK] = &gcc_blsp1_qup1_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP1_SPI_APPS_CLK] = &gcc_blsp1_qup1_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP2_I2C_APPS_CLK] = &gcc_blsp1_qup2_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP2_SPI_APPS_CLK] = &gcc_blsp1_qup2_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP3_I2C_APPS_CLK] = &gcc_blsp1_qup3_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP3_SPI_APPS_CLK] = &gcc_blsp1_qup3_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP4_I2C_APPS_CLK] = &gcc_blsp1_qup4_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP4_SPI_APPS_CLK] = &gcc_blsp1_qup4_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP5_I2C_APPS_CLK] = &gcc_blsp1_qup5_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP5_SPI_APPS_CLK] = &gcc_blsp1_qup5_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP6_I2C_APPS_CLK] = &gcc_blsp1_qup6_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP6_SPI_APPS_CLK] = &gcc_blsp1_qup6_spi_apps_clk.clkr,
	[GCC_BLSP1_UART1_APPS_CLK] = &gcc_blsp1_uart1_apps_clk.clkr,
	[GCC_BLSP1_UART2_APPS_CLK] = &gcc_blsp1_uart2_apps_clk.clkr,
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_CAMSS_CCI_AHB_CLK] = &gcc_camss_cci_ahb_clk.clkr,
	[GCC_CAMSS_CCI_CLK] = &gcc_camss_cci_clk.clkr,
	[GCC_CAMSS_CSI0_AHB_CLK] = &gcc_camss_csi0_ahb_clk.clkr,
	[GCC_CAMSS_CSI0_CLK] = &gcc_camss_csi0_clk.clkr,
	[GCC_CAMSS_CSI0PHY_CLK] = &gcc_camss_csi0phy_clk.clkr,
	[GCC_CAMSS_CSI0PIX_CLK] = &gcc_camss_csi0pix_clk.clkr,
	[GCC_CAMSS_CSI0RDI_CLK] = &gcc_camss_csi0rdi_clk.clkr,
	[GCC_CAMSS_CSI1_AHB_CLK] = &gcc_camss_csi1_ahb_clk.clkr,
	[GCC_CAMSS_CSI1_CLK] = &gcc_camss_csi1_clk.clkr,
	[GCC_CAMSS_CSI1PHY_CLK] = &gcc_camss_csi1phy_clk.clkr,
	[GCC_CAMSS_CSI1PIX_CLK] = &gcc_camss_csi1pix_clk.clkr,
	[GCC_CAMSS_CSI1RDI_CLK] = &gcc_camss_csi1rdi_clk.clkr,
	[GCC_CAMSS_CSI_VFE0_CLK] = &gcc_camss_csi_vfe0_clk.clkr,
	[GCC_CAMSS_GP0_CLK] = &gcc_camss_gp0_clk.clkr,
	[GCC_CAMSS_GP1_CLK] = &gcc_camss_gp1_clk.clkr,
	[GCC_CAMSS_ISPIF_AHB_CLK] = &gcc_camss_ispअगर_ahb_clk.clkr,
	[GCC_CAMSS_JPEG0_CLK] = &gcc_camss_jpeg0_clk.clkr,
	[GCC_CAMSS_JPEG_AHB_CLK] = &gcc_camss_jpeg_ahb_clk.clkr,
	[GCC_CAMSS_JPEG_AXI_CLK] = &gcc_camss_jpeg_axi_clk.clkr,
	[GCC_CAMSS_MCLK0_CLK] = &gcc_camss_mclk0_clk.clkr,
	[GCC_CAMSS_MCLK1_CLK] = &gcc_camss_mclk1_clk.clkr,
	[GCC_CAMSS_MICRO_AHB_CLK] = &gcc_camss_micro_ahb_clk.clkr,
	[GCC_CAMSS_CSI0PHYTIMER_CLK] = &gcc_camss_csi0phyसमयr_clk.clkr,
	[GCC_CAMSS_CSI1PHYTIMER_CLK] = &gcc_camss_csi1phyसमयr_clk.clkr,
	[GCC_CAMSS_AHB_CLK] = &gcc_camss_ahb_clk.clkr,
	[GCC_CAMSS_TOP_AHB_CLK] = &gcc_camss_top_ahb_clk.clkr,
	[GCC_CAMSS_CPP_AHB_CLK] = &gcc_camss_cpp_ahb_clk.clkr,
	[GCC_CAMSS_CPP_CLK] = &gcc_camss_cpp_clk.clkr,
	[GCC_CAMSS_VFE0_CLK] = &gcc_camss_vfe0_clk.clkr,
	[GCC_CAMSS_VFE_AHB_CLK] = &gcc_camss_vfe_ahb_clk.clkr,
	[GCC_CAMSS_VFE_AXI_CLK] = &gcc_camss_vfe_axi_clk.clkr,
	[GCC_CRYPTO_AHB_CLK] = &gcc_crypto_ahb_clk.clkr,
	[GCC_CRYPTO_AXI_CLK] = &gcc_crypto_axi_clk.clkr,
	[GCC_CRYPTO_CLK] = &gcc_crypto_clk.clkr,
	[GCC_OXILI_GMEM_CLK] = &gcc_oxili_gmem_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_MDSS_AHB_CLK] = &gcc_mdss_ahb_clk.clkr,
	[GCC_MDSS_AXI_CLK] = &gcc_mdss_axi_clk.clkr,
	[GCC_MDSS_BYTE0_CLK] = &gcc_mdss_byte0_clk.clkr,
	[GCC_MDSS_ESC0_CLK] = &gcc_mdss_esc0_clk.clkr,
	[GCC_MDSS_MDP_CLK] = &gcc_mdss_mdp_clk.clkr,
	[GCC_MDSS_PCLK0_CLK] = &gcc_mdss_pclk0_clk.clkr,
	[GCC_MDSS_VSYNC_CLK] = &gcc_mdss_vsync_clk.clkr,
	[GCC_MSS_CFG_AHB_CLK] = &gcc_mss_cfg_ahb_clk.clkr,
	[GCC_OXILI_AHB_CLK] = &gcc_oxili_ahb_clk.clkr,
	[GCC_OXILI_GFX3D_CLK] = &gcc_oxili_gfx3d_clk.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
	[GCC_SDCC1_AHB_CLK] = &gcc_sdcc1_ahb_clk.clkr,
	[GCC_SDCC1_APPS_CLK] = &gcc_sdcc1_apps_clk.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_GTCU_AHB_CLK] = &gcc_gtcu_ahb_clk.clkr,
	[GCC_JPEG_TBU_CLK] = &gcc_jpeg_tbu_clk.clkr,
	[GCC_MDP_TBU_CLK] = &gcc_mdp_tbu_clk.clkr,
	[GCC_SMMU_CFG_CLK] = &gcc_smmu_cfg_clk.clkr,
	[GCC_VENUS_TBU_CLK] = &gcc_venus_tbu_clk.clkr,
	[GCC_VFE_TBU_CLK] = &gcc_vfe_tbu_clk.clkr,
	[GCC_USB2A_PHY_SLEEP_CLK] = &gcc_usb2a_phy_sleep_clk.clkr,
	[GCC_USB_HS_AHB_CLK] = &gcc_usb_hs_ahb_clk.clkr,
	[GCC_USB_HS_SYSTEM_CLK] = &gcc_usb_hs_प्रणाली_clk.clkr,
	[GCC_VENUS0_AHB_CLK] = &gcc_venus0_ahb_clk.clkr,
	[GCC_VENUS0_AXI_CLK] = &gcc_venus0_axi_clk.clkr,
	[GCC_VENUS0_VCODEC0_CLK] = &gcc_venus0_vcodec0_clk.clkr,
	[BIMC_DDR_CLK_SRC] = &bimc_ddr_clk_src.clkr,
	[GCC_APSS_TCU_CLK] = &gcc_apss_tcu_clk.clkr,
	[GCC_GFX_TCU_CLK] = &gcc_gfx_tcu_clk.clkr,
	[BIMC_GPU_CLK_SRC] = &bimc_gpu_clk_src.clkr,
	[GCC_BIMC_GFX_CLK] = &gcc_bimc_gfx_clk.clkr,
	[GCC_BIMC_GPU_CLK] = &gcc_bimc_gpu_clk.clkr,
	[ULTAUDIO_AHBFABRIC_CLK_SRC] = &ultaudio_ahbfabric_clk_src.clkr,
	[ULTAUDIO_LPAIF_PRI_I2S_CLK_SRC] = &ultaudio_lpaअगर_pri_i2s_clk_src.clkr,
	[ULTAUDIO_LPAIF_SEC_I2S_CLK_SRC] = &ultaudio_lpaअगर_sec_i2s_clk_src.clkr,
	[ULTAUDIO_LPAIF_AUX_I2S_CLK_SRC] = &ultaudio_lpaअगर_aux_i2s_clk_src.clkr,
	[ULTAUDIO_XO_CLK_SRC] = &ultaudio_xo_clk_src.clkr,
	[CODEC_DIGCODEC_CLK_SRC] = &codec_digcodec_clk_src.clkr,
	[GCC_ULTAUDIO_PCNOC_MPORT_CLK] = &gcc_ultaudio_pcnoc_mport_clk.clkr,
	[GCC_ULTAUDIO_PCNOC_SWAY_CLK] = &gcc_ultaudio_pcnoc_sway_clk.clkr,
	[GCC_ULTAUDIO_AVSYNC_XO_CLK] = &gcc_ultaudio_avsync_xo_clk.clkr,
	[GCC_ULTAUDIO_STC_XO_CLK] = &gcc_ultaudio_stc_xo_clk.clkr,
	[GCC_ULTAUDIO_AHBFABRIC_IXFABRIC_CLK] =	&gcc_ultaudio_ahbfabric_ixfabric_clk.clkr,
	[GCC_ULTAUDIO_AHBFABRIC_IXFABRIC_LPM_CLK] = &gcc_ultaudio_ahbfabric_ixfabric_lpm_clk.clkr,
	[GCC_ULTAUDIO_LPAIF_PRI_I2S_CLK] = &gcc_ultaudio_lpaअगर_pri_i2s_clk.clkr,
	[GCC_ULTAUDIO_LPAIF_SEC_I2S_CLK] = &gcc_ultaudio_lpaअगर_sec_i2s_clk.clkr,
	[GCC_ULTAUDIO_LPAIF_AUX_I2S_CLK] = &gcc_ultaudio_lpaअगर_aux_i2s_clk.clkr,
	[GCC_CODEC_DIGCODEC_CLK] = &gcc_codec_digcodec_clk.clkr,
	[GCC_MSS_Q6_BIMC_AXI_CLK] = &gcc_mss_q6_bimc_axi_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *gcc_msm8916_gdscs[] = अणु
	[VENUS_GDSC] = &venus_gdsc,
	[MDSS_GDSC] = &mdss_gdsc,
	[JPEG_GDSC] = &jpeg_gdsc,
	[VFE_GDSC] = &vfe_gdsc,
	[OXILI_GDSC] = &oxili_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_msm8916_resets[] = अणु
	[GCC_BLSP1_BCR] = अणु 0x01000 पूर्ण,
	[GCC_BLSP1_QUP1_BCR] = अणु 0x02000 पूर्ण,
	[GCC_BLSP1_UART1_BCR] = अणु 0x02038 पूर्ण,
	[GCC_BLSP1_QUP2_BCR] = अणु 0x03008 पूर्ण,
	[GCC_BLSP1_UART2_BCR] = अणु 0x03028 पूर्ण,
	[GCC_BLSP1_QUP3_BCR] = अणु 0x04018 पूर्ण,
	[GCC_BLSP1_QUP4_BCR] = अणु 0x05018 पूर्ण,
	[GCC_BLSP1_QUP5_BCR] = अणु 0x06018 पूर्ण,
	[GCC_BLSP1_QUP6_BCR] = अणु 0x07018 पूर्ण,
	[GCC_IMEM_BCR] = अणु 0x0e000 पूर्ण,
	[GCC_SMMU_BCR] = अणु 0x12000 पूर्ण,
	[GCC_APSS_TCU_BCR] = अणु 0x12050 पूर्ण,
	[GCC_SMMU_XPU_BCR] = अणु 0x12054 पूर्ण,
	[GCC_PCNOC_TBU_BCR] = अणु 0x12058 पूर्ण,
	[GCC_PRNG_BCR] = अणु 0x13000 पूर्ण,
	[GCC_BOOT_ROM_BCR] = अणु 0x13008 पूर्ण,
	[GCC_CRYPTO_BCR] = अणु 0x16000 पूर्ण,
	[GCC_SEC_CTRL_BCR] = अणु 0x1a000 पूर्ण,
	[GCC_AUDIO_CORE_BCR] = अणु 0x1c008 पूर्ण,
	[GCC_ULT_AUDIO_BCR] = अणु 0x1c0b4 पूर्ण,
	[GCC_DEHR_BCR] = अणु 0x1f000 पूर्ण,
	[GCC_SYSTEM_NOC_BCR] = अणु 0x26000 पूर्ण,
	[GCC_PCNOC_BCR] = अणु 0x27018 पूर्ण,
	[GCC_TCSR_BCR] = अणु 0x28000 पूर्ण,
	[GCC_QDSS_BCR] = अणु 0x29000 पूर्ण,
	[GCC_DCD_BCR] = अणु 0x2a000 पूर्ण,
	[GCC_MSG_RAM_BCR] = अणु 0x2b000 पूर्ण,
	[GCC_MPM_BCR] = अणु 0x2c000 पूर्ण,
	[GCC_SPMI_BCR] = अणु 0x2e000 पूर्ण,
	[GCC_SPDM_BCR] = अणु 0x2f000 पूर्ण,
	[GCC_MM_SPDM_BCR] = अणु 0x2f024 पूर्ण,
	[GCC_BIMC_BCR] = अणु 0x31000 पूर्ण,
	[GCC_RBCPR_BCR] = अणु 0x33000 पूर्ण,
	[GCC_TLMM_BCR] = अणु 0x34000 पूर्ण,
	[GCC_USB_HS_BCR] = अणु 0x41000 पूर्ण,
	[GCC_USB2A_PHY_BCR] = अणु 0x41028 पूर्ण,
	[GCC_SDCC1_BCR] = अणु 0x42000 पूर्ण,
	[GCC_SDCC2_BCR] = अणु 0x43000 पूर्ण,
	[GCC_PDM_BCR] = अणु 0x44000 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT0_BCR] = अणु 0x47000 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT0_BCR] = अणु 0x48000 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT1_BCR] = अणु 0x48008 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT2_BCR] = अणु 0x48010 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT3_BCR] = अणु 0x48018 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT4_BCR] = अणु 0x48020 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT5_BCR] = अणु 0x48028 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT6_BCR] = अणु 0x48030 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT7_BCR] = अणु 0x48038 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT8_BCR] = अणु 0x48040 पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT9_BCR] = अणु 0x48048 पूर्ण,
	[GCC_MMSS_BCR] = अणु 0x4b000 पूर्ण,
	[GCC_VENUS0_BCR] = अणु 0x4c014 पूर्ण,
	[GCC_MDSS_BCR] = अणु 0x4d074 पूर्ण,
	[GCC_CAMSS_PHY0_BCR] = अणु 0x4e018 पूर्ण,
	[GCC_CAMSS_CSI0_BCR] = अणु 0x4e038 पूर्ण,
	[GCC_CAMSS_CSI0PHY_BCR] = अणु 0x4e044 पूर्ण,
	[GCC_CAMSS_CSI0RDI_BCR] = अणु 0x4e04c पूर्ण,
	[GCC_CAMSS_CSI0PIX_BCR] = अणु 0x4e054 पूर्ण,
	[GCC_CAMSS_PHY1_BCR] = अणु 0x4f018 पूर्ण,
	[GCC_CAMSS_CSI1_BCR] = अणु 0x4f038 पूर्ण,
	[GCC_CAMSS_CSI1PHY_BCR] = अणु 0x4f044 पूर्ण,
	[GCC_CAMSS_CSI1RDI_BCR] = अणु 0x4f04c पूर्ण,
	[GCC_CAMSS_CSI1PIX_BCR] = अणु 0x4f054 पूर्ण,
	[GCC_CAMSS_ISPIF_BCR] = अणु 0x50000 पूर्ण,
	[GCC_CAMSS_CCI_BCR] = अणु 0x51014 पूर्ण,
	[GCC_CAMSS_MCLK0_BCR] = अणु 0x52014 पूर्ण,
	[GCC_CAMSS_MCLK1_BCR] = अणु 0x53014 पूर्ण,
	[GCC_CAMSS_GP0_BCR] = अणु 0x54014 पूर्ण,
	[GCC_CAMSS_GP1_BCR] = अणु 0x55014 पूर्ण,
	[GCC_CAMSS_TOP_BCR] = अणु 0x56000 पूर्ण,
	[GCC_CAMSS_MICRO_BCR] = अणु 0x56008 पूर्ण,
	[GCC_CAMSS_JPEG_BCR] = अणु 0x57018 पूर्ण,
	[GCC_CAMSS_VFE_BCR] = अणु 0x58030 पूर्ण,
	[GCC_CAMSS_CSI_VFE0_BCR] = अणु 0x5804c पूर्ण,
	[GCC_OXILI_BCR] = अणु 0x59018 पूर्ण,
	[GCC_GMEM_BCR] = अणु 0x5902c पूर्ण,
	[GCC_CAMSS_AHB_BCR] = अणु 0x5a018 पूर्ण,
	[GCC_MDP_TBU_BCR] = अणु 0x62000 पूर्ण,
	[GCC_GFX_TBU_BCR] = अणु 0x63000 पूर्ण,
	[GCC_GFX_TCU_BCR] = अणु 0x64000 पूर्ण,
	[GCC_MSS_TBU_AXI_BCR] = अणु 0x65000 पूर्ण,
	[GCC_MSS_TBU_GSS_AXI_BCR] = अणु 0x66000 पूर्ण,
	[GCC_MSS_TBU_Q6_AXI_BCR] = अणु 0x67000 पूर्ण,
	[GCC_GTCU_AHB_BCR] = अणु 0x68000 पूर्ण,
	[GCC_SMMU_CFG_BCR] = अणु 0x69000 पूर्ण,
	[GCC_VFE_TBU_BCR] = अणु 0x6a000 पूर्ण,
	[GCC_VENUS_TBU_BCR] = अणु 0x6b000 पूर्ण,
	[GCC_JPEG_TBU_BCR] = अणु 0x6c000 पूर्ण,
	[GCC_PRONTO_TBU_BCR] = अणु 0x6d000 पूर्ण,
	[GCC_SMMU_CATS_BCR] = अणु 0x7c000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_msm8916_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x80000,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_msm8916_desc = अणु
	.config = &gcc_msm8916_regmap_config,
	.clks = gcc_msm8916_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_msm8916_घड़ीs),
	.resets = gcc_msm8916_resets,
	.num_resets = ARRAY_SIZE(gcc_msm8916_resets),
	.gdscs = gcc_msm8916_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_msm8916_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_msm8916_match_table[] = अणु
	अणु .compatible = "qcom,gcc-msm8916" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_msm8916_match_table);

अटल पूर्णांक gcc_msm8916_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	ret = qcom_cc_रेजिस्टर_board_clk(dev, "xo_board", "xo", 19200000);
	अगर (ret)
		वापस ret;

	ret = qcom_cc_रेजिस्टर_sleep_clk(dev);
	अगर (ret)
		वापस ret;

	वापस qcom_cc_probe(pdev, &gcc_msm8916_desc);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_msm8916_driver = अणु
	.probe		= gcc_msm8916_probe,
	.driver		= अणु
		.name	= "gcc-msm8916",
		.of_match_table = gcc_msm8916_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_msm8916_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_msm8916_driver);
पूर्ण
core_initcall(gcc_msm8916_init);

अटल व्योम __निकास gcc_msm8916_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_msm8916_driver);
पूर्ण
module_निकास(gcc_msm8916_निकास);

MODULE_DESCRIPTION("Qualcomm GCC MSM8916 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-msm8916");
