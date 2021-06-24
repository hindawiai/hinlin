<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,camcc-sc7180.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "common.h"
#समावेश "gdsc.h"
#समावेश "reset.h"

क्रमागत अणु
	P_BI_TCXO,
	P_CAM_CC_PLL0_OUT_EVEN,
	P_CAM_CC_PLL1_OUT_EVEN,
	P_CAM_CC_PLL2_OUT_AUX,
	P_CAM_CC_PLL2_OUT_EARLY,
	P_CAM_CC_PLL3_OUT_MAIN,
	P_CORE_BI_PLL_TEST_SE,
पूर्ण;

अटल स्थिर काष्ठा pll_vco agera_vco[] = अणु
	अणु 600000000, 3300000000UL, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_vco fabia_vco[] = अणु
	अणु 249600000, 2000000000UL, 0 पूर्ण,
पूर्ण;

/* 600MHz configuration */
अटल स्थिर काष्ठा alpha_pll_config cam_cc_pll0_config = अणु
	.l = 0x1f,
	.alpha = 0x4000,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002067,
	.test_ctl_val = 0x40000000,
	.user_ctl_hi_val = 0x00004805,
	.user_ctl_val = 0x00000001,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll0 = अणु
	.offset = 0x0,
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll0",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* 860MHz configuration */
अटल स्थिर काष्ठा alpha_pll_config cam_cc_pll1_config = अणु
	.l = 0x2a,
	.alpha = 0x1555,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002067,
	.test_ctl_val = 0x40000000,
	.user_ctl_hi_val = 0x00004805,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll1 = अणु
	.offset = 0x1000,
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll1",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* 1920MHz configuration */
अटल स्थिर काष्ठा alpha_pll_config cam_cc_pll2_config = अणु
	.l = 0x64,
	.config_ctl_val = 0x20000800,
	.config_ctl_hi_val = 0x400003D2,
	.test_ctl_val = 0x04000400,
	.test_ctl_hi_val = 0x00004000,
	.user_ctl_val = 0x0000030F,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll2 = अणु
	.offset = 0x2000,
	.vco_table = agera_vco,
	.num_vco = ARRAY_SIZE(agera_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_AGERA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll2",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_agera_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_fixed_factor cam_cc_pll2_out_early = अणु
	.mult = 1,
	.भाग = 2,
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_pll2_out_early",
		.parent_names = (स्थिर अक्षर *[])अणु "cam_cc_pll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_cam_cc_pll2_out_aux[] = अणु
	अणु 0x3, 4 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग cam_cc_pll2_out_aux = अणु
	.offset = 0x2000,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_cam_cc_pll2_out_aux,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_cam_cc_pll2_out_aux),
	.width = 2,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_AGERA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_pll2_out_aux",
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
			.hw = &cam_cc_pll2.clkr.hw,
		पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_alpha_pll_postभाग_ops,
	पूर्ण,
पूर्ण;

/* 1080MHz configuration */
अटल स्थिर काष्ठा alpha_pll_config cam_cc_pll3_config = अणु
	.l = 0x38,
	.alpha = 0x4000,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002067,
	.test_ctl_val = 0x40000000,
	.user_ctl_hi_val = 0x00004805,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll3 = अणु
	.offset = 0x3000,
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll3",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL1_OUT_EVEN, 2 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll1.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_1[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL2_OUT_AUX, 1 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_1[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll2_out_aux.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_2[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL2_OUT_EARLY, 4 पूर्ण,
	अणु P_CAM_CC_PLL3_OUT_MAIN, 5 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_2[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll2_out_early.hw पूर्ण,
	अणु .hw = &cam_cc_pll3.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_3[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL1_OUT_EVEN, 2 पूर्ण,
	अणु P_CAM_CC_PLL2_OUT_EARLY, 4 पूर्ण,
	अणु P_CAM_CC_PLL3_OUT_MAIN, 5 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_3[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll1.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll2_out_early.hw पूर्ण,
	अणु .hw = &cam_cc_pll3.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_4[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL3_OUT_MAIN, 5 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_4[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll3.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_5[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_5[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_6[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL1_OUT_EVEN, 2 पूर्ण,
	अणु P_CAM_CC_PLL3_OUT_MAIN, 5 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cam_cc_parent_data_6[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &cam_cc_pll1.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll3.clkr.hw पूर्ण,
	अणु .hw = &cam_cc_pll0.clkr.hw पूर्ण,
	अणु .fw_name = "core_bi_pll_test_se", .name = "core_bi_pll_test_se" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_bps_clk_src[] = अणु
	F(200000000, P_CAM_CC_PLL0_OUT_EVEN, 3, 0, 0),
	F(360000000, P_CAM_CC_PLL3_OUT_MAIN, 3, 0, 0),
	F(432000000, P_CAM_CC_PLL3_OUT_MAIN, 2.5, 0, 0),
	F(480000000, P_CAM_CC_PLL2_OUT_EARLY, 2, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_bps_clk_src = अणु
	.cmd_rcgr = 0x6010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_2,
	.freq_tbl = ftbl_cam_cc_bps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_bps_clk_src",
		.parent_data = cam_cc_parent_data_2,
		.num_parents = 5,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_cci_0_clk_src[] = अणु
	F(37500000, P_CAM_CC_PLL0_OUT_EVEN, 16, 0, 0),
	F(50000000, P_CAM_CC_PLL0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_cci_0_clk_src = अणु
	.cmd_rcgr = 0xb0d8,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_5,
	.freq_tbl = ftbl_cam_cc_cci_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_cci_0_clk_src",
		.parent_data = cam_cc_parent_data_5,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_cci_1_clk_src = अणु
	.cmd_rcgr = 0xb14c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_5,
	.freq_tbl = ftbl_cam_cc_cci_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_cci_1_clk_src",
		.parent_data = cam_cc_parent_data_5,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_cphy_rx_clk_src[] = अणु
	F(150000000, P_CAM_CC_PLL0_OUT_EVEN, 4, 0, 0),
	F(270000000, P_CAM_CC_PLL3_OUT_MAIN, 4, 0, 0),
	F(360000000, P_CAM_CC_PLL3_OUT_MAIN, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_cphy_rx_clk_src = अणु
	.cmd_rcgr = 0x9064,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_3,
	.freq_tbl = ftbl_cam_cc_cphy_rx_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_cphy_rx_clk_src",
		.parent_data = cam_cc_parent_data_3,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_csi0phyसमयr_clk_src[] = अणु
	F(300000000, P_CAM_CC_PLL0_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_csi0phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x5004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_csi0phytimer_clk_src",
		.parent_data = cam_cc_parent_data_0,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_csi1phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x5028,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_csi1phytimer_clk_src",
		.parent_data = cam_cc_parent_data_0,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_csi2phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x504c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_csi2phytimer_clk_src",
		.parent_data = cam_cc_parent_data_0,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_csi3phyसमयr_clk_src = अणु
	.cmd_rcgr = 0x5070,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_csi0phyसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_csi3phytimer_clk_src",
		.parent_data = cam_cc_parent_data_0,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_fast_ahb_clk_src[] = अणु
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PLL0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAM_CC_PLL0_OUT_EVEN, 2, 0, 0),
	F(404000000, P_CAM_CC_PLL1_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_fast_ahb_clk_src = अणु
	.cmd_rcgr = 0x603c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_fast_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_fast_ahb_clk_src",
		.parent_data = cam_cc_parent_data_0,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_icp_clk_src[] = अणु
	F(240000000, P_CAM_CC_PLL0_OUT_EVEN, 2.5, 0, 0),
	F(360000000, P_CAM_CC_PLL3_OUT_MAIN, 3, 0, 0),
	F(432000000, P_CAM_CC_PLL3_OUT_MAIN, 2.5, 0, 0),
	F(480000000, P_CAM_CC_PLL2_OUT_EARLY, 2, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_icp_clk_src = अणु
	.cmd_rcgr = 0xb088,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_2,
	.freq_tbl = ftbl_cam_cc_icp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_icp_clk_src",
		.parent_data = cam_cc_parent_data_2,
		.num_parents = 5,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_अगरe_0_clk_src[] = अणु
	F(240000000, P_CAM_CC_PLL0_OUT_EVEN, 2.5, 0, 0),
	F(360000000, P_CAM_CC_PLL3_OUT_MAIN, 3, 0, 0),
	F(432000000, P_CAM_CC_PLL3_OUT_MAIN, 2.5, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_0_clk_src = अणु
	.cmd_rcgr = 0x9010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_4,
	.freq_tbl = ftbl_cam_cc_अगरe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_0_clk_src",
		.parent_data = cam_cc_parent_data_4,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_अगरe_0_csid_clk_src[] = अणु
	F(150000000, P_CAM_CC_PLL0_OUT_EVEN, 4, 0, 0),
	F(270000000, P_CAM_CC_PLL3_OUT_MAIN, 4, 0, 0),
	F(360000000, P_CAM_CC_PLL3_OUT_MAIN, 3, 0, 0),
	F(480000000, P_CAM_CC_PLL2_OUT_EARLY, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_0_csid_clk_src = अणु
	.cmd_rcgr = 0x903c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_3,
	.freq_tbl = ftbl_cam_cc_अगरe_0_csid_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_0_csid_clk_src",
		.parent_data = cam_cc_parent_data_3,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_1_clk_src = अणु
	.cmd_rcgr = 0xa010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_4,
	.freq_tbl = ftbl_cam_cc_अगरe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_1_clk_src",
		.parent_data = cam_cc_parent_data_4,
		.num_parents = 4,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_1_csid_clk_src = अणु
	.cmd_rcgr = 0xa034,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_3,
	.freq_tbl = ftbl_cam_cc_अगरe_0_csid_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_1_csid_clk_src",
		.parent_data = cam_cc_parent_data_3,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_lite_clk_src = अणु
	.cmd_rcgr = 0xb004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_4,
	.freq_tbl = ftbl_cam_cc_अगरe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_lite_clk_src",
		.parent_data = cam_cc_parent_data_4,
		.num_parents = 4,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_lite_csid_clk_src = अणु
	.cmd_rcgr = 0xb024,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_3,
	.freq_tbl = ftbl_cam_cc_अगरe_0_csid_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_lite_csid_clk_src",
		.parent_data = cam_cc_parent_data_3,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_ipe_0_clk_src[] = अणु
	F(240000000, P_CAM_CC_PLL0_OUT_EVEN, 2.5, 0, 0),
	F(360000000, P_CAM_CC_PLL3_OUT_MAIN, 3, 0, 0),
	F(432000000, P_CAM_CC_PLL3_OUT_MAIN, 2.5, 0, 0),
	F(540000000, P_CAM_CC_PLL3_OUT_MAIN, 2, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_ipe_0_clk_src = अणु
	.cmd_rcgr = 0x7010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_2,
	.freq_tbl = ftbl_cam_cc_ipe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ipe_0_clk_src",
		.parent_data = cam_cc_parent_data_2,
		.num_parents = 5,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_jpeg_clk_src[] = अणु
	F(66666667, P_CAM_CC_PLL0_OUT_EVEN, 9, 0, 0),
	F(133333333, P_CAM_CC_PLL0_OUT_EVEN, 4.5, 0, 0),
	F(216000000, P_CAM_CC_PLL3_OUT_MAIN, 5, 0, 0),
	F(320000000, P_CAM_CC_PLL2_OUT_EARLY, 3, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_jpeg_clk_src = अणु
	.cmd_rcgr = 0xb04c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_2,
	.freq_tbl = ftbl_cam_cc_jpeg_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_jpeg_clk_src",
		.parent_data = cam_cc_parent_data_2,
		.num_parents = 5,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_lrme_clk_src[] = अणु
	F(200000000, P_CAM_CC_PLL0_OUT_EVEN, 3, 0, 0),
	F(216000000, P_CAM_CC_PLL3_OUT_MAIN, 5, 0, 0),
	F(300000000, P_CAM_CC_PLL0_OUT_EVEN, 2, 0, 0),
	F(404000000, P_CAM_CC_PLL1_OUT_EVEN, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_lrme_clk_src = अणु
	.cmd_rcgr = 0xb0f8,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_6,
	.freq_tbl = ftbl_cam_cc_lrme_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_lrme_clk_src",
		.parent_data = cam_cc_parent_data_6,
		.num_parents = 5,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_mclk0_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_CAM_CC_PLL2_OUT_AUX, 10, 1, 2),
	F(64000000, P_CAM_CC_PLL2_OUT_AUX, 7.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk0_clk_src = अणु
	.cmd_rcgr = 0x4004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_1,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk0_clk_src",
		.parent_data = cam_cc_parent_data_1,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk1_clk_src = अणु
	.cmd_rcgr = 0x4024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_1,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk1_clk_src",
		.parent_data = cam_cc_parent_data_1,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk2_clk_src = अणु
	.cmd_rcgr = 0x4044,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_1,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk2_clk_src",
		.parent_data = cam_cc_parent_data_1,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk3_clk_src = अणु
	.cmd_rcgr = 0x4064,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_1,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk3_clk_src",
		.parent_data = cam_cc_parent_data_1,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk4_clk_src = अणु
	.cmd_rcgr = 0x4084,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_1,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk4_clk_src",
		.parent_data = cam_cc_parent_data_1,
		.num_parents = 3,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_slow_ahb_clk_src[] = अणु
	F(80000000, P_CAM_CC_PLL0_OUT_EVEN, 7.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_slow_ahb_clk_src = अणु
	.cmd_rcgr = 0x6058,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_slow_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_slow_ahb_clk_src",
		.parent_data = cam_cc_parent_data_0,
		.num_parents = 4,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_ahb_clk = अणु
	.halt_reg = 0x6070,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6070,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_ahb_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_slow_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_areg_clk = अणु
	.halt_reg = 0x6054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_areg_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_fast_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_axi_clk = अणु
	.halt_reg = 0x6038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_clk = अणु
	.halt_reg = 0x6028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_bps_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_camnoc_axi_clk = अणु
	.halt_reg = 0xb124,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb124,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_camnoc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_cci_0_clk = अणु
	.halt_reg = 0xb0f0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb0f0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_cci_0_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cci_0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_cci_1_clk = अणु
	.halt_reg = 0xb164,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb164,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_cci_1_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cci_1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_core_ahb_clk = अणु
	.halt_reg = 0xb144,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0xb144,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_core_ahb_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_slow_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_cpas_ahb_clk = अणु
	.halt_reg = 0xb11c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb11c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_cpas_ahb_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_slow_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csi0phyसमयr_clk = अणु
	.halt_reg = 0x501c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x501c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csi0phytimer_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_csi0phyसमयr_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csi1phyसमयr_clk = अणु
	.halt_reg = 0x5040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csi1phytimer_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_csi1phyसमयr_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csi2phyसमयr_clk = अणु
	.halt_reg = 0x5064,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5064,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csi2phytimer_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_csi2phyसमयr_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csi3phyसमयr_clk = अणु
	.halt_reg = 0x5088,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5088,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csi3phytimer_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_csi3phyसमयr_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csiphy0_clk = अणु
	.halt_reg = 0x5020,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csiphy0_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csiphy1_clk = अणु
	.halt_reg = 0x5044,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5044,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csiphy1_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csiphy2_clk = अणु
	.halt_reg = 0x5068,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x5068,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csiphy2_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_csiphy3_clk = अणु
	.halt_reg = 0x508c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x508c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_csiphy3_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_icp_clk = अणु
	.halt_reg = 0xb0a0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb0a0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_icp_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_icp_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_axi_clk = अणु
	.halt_reg = 0x9080,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_clk = अणु
	.halt_reg = 0x9028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_cphy_rx_clk = अणु
	.halt_reg = 0x907c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x907c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_cphy_rx_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_csid_clk = अणु
	.halt_reg = 0x9054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_csid_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_0_csid_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_dsp_clk = अणु
	.halt_reg = 0x9038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_dsp_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_axi_clk = अणु
	.halt_reg = 0xa058,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa058,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_clk = अणु
	.halt_reg = 0xa028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_cphy_rx_clk = अणु
	.halt_reg = 0xa054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_cphy_rx_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_csid_clk = अणु
	.halt_reg = 0xa04c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa04c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_csid_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_1_csid_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_dsp_clk = अणु
	.halt_reg = 0xa030,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_dsp_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_lite_clk = अणु
	.halt_reg = 0xb01c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb01c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_lite_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_lite_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_lite_cphy_rx_clk = अणु
	.halt_reg = 0xb044,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb044,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_lite_cphy_rx_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_cphy_rx_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_lite_csid_clk = अणु
	.halt_reg = 0xb03c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb03c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_lite_csid_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_अगरe_lite_csid_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_ahb_clk = अणु
	.halt_reg = 0x7040,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_ahb_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_slow_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_areg_clk = अणु
	.halt_reg = 0x703c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x703c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_areg_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_fast_ahb_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_axi_clk = अणु
	.halt_reg = 0x7038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_clk = अणु
	.halt_reg = 0x7028,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_ipe_0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_jpeg_clk = अणु
	.halt_reg = 0xb064,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb064,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_jpeg_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_jpeg_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_lrme_clk = अणु
	.halt_reg = 0xb110,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb110,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_lrme_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_lrme_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_mclk0_clk = अणु
	.halt_reg = 0x401c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x401c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_mclk0_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_mclk0_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_mclk1_clk = अणु
	.halt_reg = 0x403c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x403c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_mclk1_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_mclk1_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_mclk2_clk = अणु
	.halt_reg = 0x405c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x405c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_mclk2_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_mclk2_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_mclk3_clk = अणु
	.halt_reg = 0x407c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x407c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_mclk3_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_mclk3_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_mclk4_clk = अणु
	.halt_reg = 0x409c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x409c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_mclk4_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.hw = &cam_cc_mclk4_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_soc_ahb_clk = अणु
	.halt_reg = 0xb140,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb140,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_soc_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_sys_पंचांगr_clk = अणु
	.halt_reg = 0xb0a8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb0a8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_sys_tmr_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc bps_gdsc = अणु
	.gdscr = 0x6004,
	.pd = अणु
		.name = "bps_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = HW_CTRL,
पूर्ण;

अटल काष्ठा gdsc अगरe_0_gdsc = अणु
	.gdscr = 0x9004,
	.pd = अणु
		.name = "ife_0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc अगरe_1_gdsc = अणु
	.gdscr = 0xa004,
	.pd = अणु
		.name = "ife_1_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc ipe_0_gdsc = अणु
	.gdscr = 0x7004,
	.pd = अणु
		.name = "ipe_0_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = HW_CTRL,
पूर्ण;

अटल काष्ठा gdsc titan_top_gdsc = अणु
	.gdscr = 0xb134,
	.pd = अणु
		.name = "titan_top_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा clk_hw *cam_cc_sc7180_hws[] = अणु
	[CAM_CC_PLL2_OUT_EARLY] = &cam_cc_pll2_out_early.hw,
पूर्ण;

अटल काष्ठा clk_regmap *cam_cc_sc7180_घड़ीs[] = अणु
	[CAM_CC_BPS_AHB_CLK] = &cam_cc_bps_ahb_clk.clkr,
	[CAM_CC_BPS_AREG_CLK] = &cam_cc_bps_areg_clk.clkr,
	[CAM_CC_BPS_AXI_CLK] = &cam_cc_bps_axi_clk.clkr,
	[CAM_CC_BPS_CLK] = &cam_cc_bps_clk.clkr,
	[CAM_CC_BPS_CLK_SRC] = &cam_cc_bps_clk_src.clkr,
	[CAM_CC_CAMNOC_AXI_CLK] = &cam_cc_camnoc_axi_clk.clkr,
	[CAM_CC_CCI_0_CLK] = &cam_cc_cci_0_clk.clkr,
	[CAM_CC_CCI_0_CLK_SRC] = &cam_cc_cci_0_clk_src.clkr,
	[CAM_CC_CCI_1_CLK] = &cam_cc_cci_1_clk.clkr,
	[CAM_CC_CCI_1_CLK_SRC] = &cam_cc_cci_1_clk_src.clkr,
	[CAM_CC_CORE_AHB_CLK] = &cam_cc_core_ahb_clk.clkr,
	[CAM_CC_CPAS_AHB_CLK] = &cam_cc_cpas_ahb_clk.clkr,
	[CAM_CC_CPHY_RX_CLK_SRC] = &cam_cc_cphy_rx_clk_src.clkr,
	[CAM_CC_CSI0PHYTIMER_CLK] = &cam_cc_csi0phyसमयr_clk.clkr,
	[CAM_CC_CSI0PHYTIMER_CLK_SRC] = &cam_cc_csi0phyसमयr_clk_src.clkr,
	[CAM_CC_CSI1PHYTIMER_CLK] = &cam_cc_csi1phyसमयr_clk.clkr,
	[CAM_CC_CSI1PHYTIMER_CLK_SRC] = &cam_cc_csi1phyसमयr_clk_src.clkr,
	[CAM_CC_CSI2PHYTIMER_CLK] = &cam_cc_csi2phyसमयr_clk.clkr,
	[CAM_CC_CSI2PHYTIMER_CLK_SRC] = &cam_cc_csi2phyसमयr_clk_src.clkr,
	[CAM_CC_CSI3PHYTIMER_CLK] = &cam_cc_csi3phyसमयr_clk.clkr,
	[CAM_CC_CSI3PHYTIMER_CLK_SRC] = &cam_cc_csi3phyसमयr_clk_src.clkr,
	[CAM_CC_CSIPHY0_CLK] = &cam_cc_csiphy0_clk.clkr,
	[CAM_CC_CSIPHY1_CLK] = &cam_cc_csiphy1_clk.clkr,
	[CAM_CC_CSIPHY2_CLK] = &cam_cc_csiphy2_clk.clkr,
	[CAM_CC_CSIPHY3_CLK] = &cam_cc_csiphy3_clk.clkr,
	[CAM_CC_FAST_AHB_CLK_SRC] = &cam_cc_fast_ahb_clk_src.clkr,
	[CAM_CC_ICP_CLK] = &cam_cc_icp_clk.clkr,
	[CAM_CC_ICP_CLK_SRC] = &cam_cc_icp_clk_src.clkr,
	[CAM_CC_IFE_0_AXI_CLK] = &cam_cc_अगरe_0_axi_clk.clkr,
	[CAM_CC_IFE_0_CLK] = &cam_cc_अगरe_0_clk.clkr,
	[CAM_CC_IFE_0_CLK_SRC] = &cam_cc_अगरe_0_clk_src.clkr,
	[CAM_CC_IFE_0_CPHY_RX_CLK] = &cam_cc_अगरe_0_cphy_rx_clk.clkr,
	[CAM_CC_IFE_0_CSID_CLK] = &cam_cc_अगरe_0_csid_clk.clkr,
	[CAM_CC_IFE_0_CSID_CLK_SRC] = &cam_cc_अगरe_0_csid_clk_src.clkr,
	[CAM_CC_IFE_0_DSP_CLK] = &cam_cc_अगरe_0_dsp_clk.clkr,
	[CAM_CC_IFE_1_AXI_CLK] = &cam_cc_अगरe_1_axi_clk.clkr,
	[CAM_CC_IFE_1_CLK] = &cam_cc_अगरe_1_clk.clkr,
	[CAM_CC_IFE_1_CLK_SRC] = &cam_cc_अगरe_1_clk_src.clkr,
	[CAM_CC_IFE_1_CPHY_RX_CLK] = &cam_cc_अगरe_1_cphy_rx_clk.clkr,
	[CAM_CC_IFE_1_CSID_CLK] = &cam_cc_अगरe_1_csid_clk.clkr,
	[CAM_CC_IFE_1_CSID_CLK_SRC] = &cam_cc_अगरe_1_csid_clk_src.clkr,
	[CAM_CC_IFE_1_DSP_CLK] = &cam_cc_अगरe_1_dsp_clk.clkr,
	[CAM_CC_IFE_LITE_CLK] = &cam_cc_अगरe_lite_clk.clkr,
	[CAM_CC_IFE_LITE_CLK_SRC] = &cam_cc_अगरe_lite_clk_src.clkr,
	[CAM_CC_IFE_LITE_CPHY_RX_CLK] = &cam_cc_अगरe_lite_cphy_rx_clk.clkr,
	[CAM_CC_IFE_LITE_CSID_CLK] = &cam_cc_अगरe_lite_csid_clk.clkr,
	[CAM_CC_IFE_LITE_CSID_CLK_SRC] = &cam_cc_अगरe_lite_csid_clk_src.clkr,
	[CAM_CC_IPE_0_AHB_CLK] = &cam_cc_ipe_0_ahb_clk.clkr,
	[CAM_CC_IPE_0_AREG_CLK] = &cam_cc_ipe_0_areg_clk.clkr,
	[CAM_CC_IPE_0_AXI_CLK] = &cam_cc_ipe_0_axi_clk.clkr,
	[CAM_CC_IPE_0_CLK] = &cam_cc_ipe_0_clk.clkr,
	[CAM_CC_IPE_0_CLK_SRC] = &cam_cc_ipe_0_clk_src.clkr,
	[CAM_CC_JPEG_CLK] = &cam_cc_jpeg_clk.clkr,
	[CAM_CC_JPEG_CLK_SRC] = &cam_cc_jpeg_clk_src.clkr,
	[CAM_CC_LRME_CLK] = &cam_cc_lrme_clk.clkr,
	[CAM_CC_LRME_CLK_SRC] = &cam_cc_lrme_clk_src.clkr,
	[CAM_CC_MCLK0_CLK] = &cam_cc_mclk0_clk.clkr,
	[CAM_CC_MCLK0_CLK_SRC] = &cam_cc_mclk0_clk_src.clkr,
	[CAM_CC_MCLK1_CLK] = &cam_cc_mclk1_clk.clkr,
	[CAM_CC_MCLK1_CLK_SRC] = &cam_cc_mclk1_clk_src.clkr,
	[CAM_CC_MCLK2_CLK] = &cam_cc_mclk2_clk.clkr,
	[CAM_CC_MCLK2_CLK_SRC] = &cam_cc_mclk2_clk_src.clkr,
	[CAM_CC_MCLK3_CLK] = &cam_cc_mclk3_clk.clkr,
	[CAM_CC_MCLK3_CLK_SRC] = &cam_cc_mclk3_clk_src.clkr,
	[CAM_CC_MCLK4_CLK] = &cam_cc_mclk4_clk.clkr,
	[CAM_CC_MCLK4_CLK_SRC] = &cam_cc_mclk4_clk_src.clkr,
	[CAM_CC_PLL0] = &cam_cc_pll0.clkr,
	[CAM_CC_PLL1] = &cam_cc_pll1.clkr,
	[CAM_CC_PLL2] = &cam_cc_pll2.clkr,
	[CAM_CC_PLL2_OUT_AUX] = &cam_cc_pll2_out_aux.clkr,
	[CAM_CC_PLL3] = &cam_cc_pll3.clkr,
	[CAM_CC_SLOW_AHB_CLK_SRC] = &cam_cc_slow_ahb_clk_src.clkr,
	[CAM_CC_SOC_AHB_CLK] = &cam_cc_soc_ahb_clk.clkr,
	[CAM_CC_SYS_TMR_CLK] = &cam_cc_sys_पंचांगr_clk.clkr,
पूर्ण;
अटल काष्ठा gdsc *cam_cc_sc7180_gdscs[] = अणु
	[BPS_GDSC] = &bps_gdsc,
	[IFE_0_GDSC] = &अगरe_0_gdsc,
	[IFE_1_GDSC] = &अगरe_1_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cam_cc_sc7180_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0xd028,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc cam_cc_sc7180_desc = अणु
	.config = &cam_cc_sc7180_regmap_config,
	.clk_hws = cam_cc_sc7180_hws,
	.num_clk_hws = ARRAY_SIZE(cam_cc_sc7180_hws),
	.clks = cam_cc_sc7180_घड़ीs,
	.num_clks = ARRAY_SIZE(cam_cc_sc7180_घड़ीs),
	.gdscs = cam_cc_sc7180_gdscs,
	.num_gdscs = ARRAY_SIZE(cam_cc_sc7180_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id cam_cc_sc7180_match_table[] = अणु
	अणु .compatible = "qcom,sc7180-camcc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cam_cc_sc7180_match_table);

अटल पूर्णांक cam_cc_sc7180_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	pm_runसमय_enable(&pdev->dev);
	ret = pm_clk_create(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	ret = pm_clk_add(&pdev->dev, "xo");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to acquire XO clock\n");
		जाओ disable_pm_runसमय;
	पूर्ण

	ret = pm_clk_add(&pdev->dev, "iface");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to acquire iface clock\n");
		जाओ disable_pm_runसमय;
	पूर्ण

	ret = pm_runसमय_get(&pdev->dev);
	अगर (ret)
		जाओ destroy_pm_clk;

	regmap = qcom_cc_map(pdev, &cam_cc_sc7180_desc);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		pm_runसमय_put(&pdev->dev);
		जाओ destroy_pm_clk;
	पूर्ण

	clk_fabia_pll_configure(&cam_cc_pll0, regmap, &cam_cc_pll0_config);
	clk_fabia_pll_configure(&cam_cc_pll1, regmap, &cam_cc_pll1_config);
	clk_agera_pll_configure(&cam_cc_pll2, regmap, &cam_cc_pll2_config);
	clk_fabia_pll_configure(&cam_cc_pll3, regmap, &cam_cc_pll3_config);

	ret = qcom_cc_really_probe(pdev, &cam_cc_sc7180_desc, regmap);
	pm_runसमय_put(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register CAM CC clocks\n");
		जाओ destroy_pm_clk;
	पूर्ण

	वापस 0;

destroy_pm_clk:
	pm_clk_destroy(&pdev->dev);

disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cam_cc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_clk_suspend, pm_clk_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver cam_cc_sc7180_driver = अणु
	.probe = cam_cc_sc7180_probe,
	.driver = अणु
		.name = "cam_cc-sc7180",
		.of_match_table = cam_cc_sc7180_match_table,
		.pm = &cam_cc_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cam_cc_sc7180_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cam_cc_sc7180_driver);
पूर्ण
subsys_initcall(cam_cc_sc7180_init);

अटल व्योम __निकास cam_cc_sc7180_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cam_cc_sc7180_driver);
पूर्ण
module_निकास(cam_cc_sc7180_निकास);

MODULE_DESCRIPTION("QTI CAM_CC SC7180 Driver");
MODULE_LICENSE("GPL v2");
