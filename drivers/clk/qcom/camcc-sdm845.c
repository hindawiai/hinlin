<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,camcc-sdm845.h>

#समावेश "common.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_BI_TCXO,
	P_CAM_CC_PLL0_OUT_EVEN,
	P_CAM_CC_PLL1_OUT_EVEN,
	P_CAM_CC_PLL2_OUT_EVEN,
	P_CAM_CC_PLL3_OUT_EVEN,
	P_CORE_BI_PLL_TEST_SE,
पूर्ण;

अटल स्थिर काष्ठा parent_map cam_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_CAM_CC_PLL2_OUT_EVEN, 1 पूर्ण,
	अणु P_CAM_CC_PLL1_OUT_EVEN, 2 पूर्ण,
	अणु P_CAM_CC_PLL3_OUT_EVEN, 5 पूर्ण,
	अणु P_CAM_CC_PLL0_OUT_EVEN, 6 पूर्ण,
	अणु P_CORE_BI_PLL_TEST_SE, 7 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam_cc_parent_names_0[] = अणु
	"bi_tcxo",
	"cam_cc_pll2_out_even",
	"cam_cc_pll1_out_even",
	"cam_cc_pll3_out_even",
	"cam_cc_pll0_out_even",
	"core_bi_pll_test_se",
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll0",
			.parent_names = (स्थिर अक्षर *[])अणु "bi_tcxo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_fabia_even[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग cam_cc_pll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_pll0_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "cam_cc_pll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll1 = अणु
	.offset = 0x1000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll1",
			.parent_names = (स्थिर अक्षर *[])अणु "bi_tcxo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग cam_cc_pll1_out_even = अणु
	.offset = 0x1000,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_pll1_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "cam_cc_pll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll2 = अणु
	.offset = 0x2000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll2",
			.parent_names = (स्थिर अक्षर *[])अणु "bi_tcxo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग cam_cc_pll2_out_even = अणु
	.offset = 0x2000,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_pll2_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "cam_cc_pll2" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll cam_cc_pll3 = अणु
	.offset = 0x3000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_pll3",
			.parent_names = (स्थिर अक्षर *[])अणु "bi_tcxo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_fabia_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग cam_cc_pll3_out_even = अणु
	.offset = 0x3000,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_pll3_out_even",
		.parent_names = (स्थिर अक्षर *[])अणु "cam_cc_pll3" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_bps_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PLL0_OUT_EVEN, 3, 0, 0),
	F(404000000, P_CAM_CC_PLL1_OUT_EVEN, 2, 0, 0),
	F(480000000, P_CAM_CC_PLL2_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

/*
 * As per HW design, some of the CAMCC RCGs needs to
 * move to XO घड़ी during their घड़ी disable so using
 * clk_rcg2_shared_ops क्रम such RCGs. This is required
 * to घातer करोwn the camera memories gracefully.
 * Also, use CLK_SET_RATE_PARENT flag क्रम the RCGs which
 * have CAM_CC_PLL2_OUT_EVEN PLL as parent in frequency
 * table and requires reconfiguration of the PLL frequency.
 */
अटल काष्ठा clk_rcg2 cam_cc_bps_clk_src = अणु
	.cmd_rcgr = 0x600c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_bps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_bps_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_cci_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_CAM_CC_PLL0_OUT_EVEN, 16, 0, 0),
	F(50000000, P_CAM_CC_PLL0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_cci_clk_src = अणु
	.cmd_rcgr = 0xb0d8,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_cci_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_cci_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_cphy_rx_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(384000000, P_CAM_CC_PLL3_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_cphy_rx_clk_src = अणु
	.cmd_rcgr = 0x9060,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_cphy_rx_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_cphy_rx_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_csi0phyसमयr_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(240000000, P_CAM_CC_PLL2_OUT_EVEN, 2, 0, 0),
	F(269333333, P_CAM_CC_PLL1_OUT_EVEN, 3, 0, 0),
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
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
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
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
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
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
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
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_fast_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_CAM_CC_PLL0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PLL0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAM_CC_PLL0_OUT_EVEN, 2, 0, 0),
	F(400000000, P_CAM_CC_PLL0_OUT_EVEN, 1.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_fast_ahb_clk_src = अणु
	.cmd_rcgr = 0x6038,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_fast_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_fast_ahb_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_fd_core_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(384000000, P_CAM_CC_PLL3_OUT_EVEN, 1, 0, 0),
	F(400000000, P_CAM_CC_PLL0_OUT_EVEN, 1.5, 0, 0),
	F(538666667, P_CAM_CC_PLL1_OUT_EVEN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_fd_core_clk_src = अणु
	.cmd_rcgr = 0xb0b0,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_fd_core_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_fd_core_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_icp_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(384000000, P_CAM_CC_PLL3_OUT_EVEN, 1, 0, 0),
	F(400000000, P_CAM_CC_PLL0_OUT_EVEN, 1.5, 0, 0),
	F(538666667, P_CAM_CC_PLL1_OUT_EVEN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_icp_clk_src = अणु
	.cmd_rcgr = 0xb088,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_icp_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_icp_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_अगरe_0_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	F(320000000, P_CAM_CC_PLL2_OUT_EVEN, 1.5, 0, 0),
	F(404000000, P_CAM_CC_PLL1_OUT_EVEN, 2, 0, 0),
	F(480000000, P_CAM_CC_PLL2_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_0_clk_src = अणु
	.cmd_rcgr = 0x900c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_अगरe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_0_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_अगरe_0_csid_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_CAM_CC_PLL0_OUT_EVEN, 8, 0, 0),
	F(384000000, P_CAM_CC_PLL3_OUT_EVEN, 1, 0, 0),
	F(538666667, P_CAM_CC_PLL1_OUT_EVEN, 1.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_0_csid_clk_src = अणु
	.cmd_rcgr = 0x9038,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_अगरe_0_csid_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_0_csid_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_1_clk_src = अणु
	.cmd_rcgr = 0xa00c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_अगरe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_1_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_1_csid_clk_src = अणु
	.cmd_rcgr = 0xa030,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_अगरe_0_csid_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_1_csid_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_lite_clk_src = अणु
	.cmd_rcgr = 0xb004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_अगरe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_lite_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_अगरe_lite_csid_clk_src = अणु
	.cmd_rcgr = 0xb024,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_अगरe_0_csid_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ife_lite_csid_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_ipe_0_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	F(240000000, P_CAM_CC_PLL0_OUT_EVEN, 2.5, 0, 0),
	F(404000000, P_CAM_CC_PLL1_OUT_EVEN, 2, 0, 0),
	F(480000000, P_CAM_CC_PLL2_OUT_EVEN, 1, 0, 0),
	F(538666667, P_CAM_CC_PLL1_OUT_EVEN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PLL0_OUT_EVEN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_ipe_0_clk_src = अणु
	.cmd_rcgr = 0x700c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_ipe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ipe_0_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_ipe_1_clk_src = अणु
	.cmd_rcgr = 0x800c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_ipe_0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_ipe_1_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_jpeg_clk_src = अणु
	.cmd_rcgr = 0xb04c,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_bps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_jpeg_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_lrme_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PLL0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PLL0_OUT_EVEN, 3, 0, 0),
	F(269333333, P_CAM_CC_PLL1_OUT_EVEN, 3, 0, 0),
	F(320000000, P_CAM_CC_PLL2_OUT_EVEN, 1.5, 0, 0),
	F(400000000, P_CAM_CC_PLL0_OUT_EVEN, 1.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_lrme_clk_src = अणु
	.cmd_rcgr = 0xb0f8,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_lrme_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_lrme_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_shared_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_mclk0_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_CAM_CC_PLL2_OUT_EVEN, 10, 1, 2),
	F(33333333, P_CAM_CC_PLL0_OUT_EVEN, 2, 1, 9),
	F(34285714, P_CAM_CC_PLL2_OUT_EVEN, 14, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk0_clk_src = अणु
	.cmd_rcgr = 0x4004,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk0_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk1_clk_src = अणु
	.cmd_rcgr = 0x4024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk1_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk2_clk_src = अणु
	.cmd_rcgr = 0x4044,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk2_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_mclk3_clk_src = अणु
	.cmd_rcgr = 0x4064,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_mclk0_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_mclk3_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_cam_cc_slow_ahb_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_CAM_CC_PLL0_OUT_EVEN, 10, 0, 0),
	F(66666667, P_CAM_CC_PLL0_OUT_EVEN, 9, 0, 0),
	F(73846154, P_CAM_CC_PLL2_OUT_EVEN, 6.5, 0, 0),
	F(80000000, P_CAM_CC_PLL2_OUT_EVEN, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 cam_cc_slow_ahb_clk_src = अणु
	.cmd_rcgr = 0x6054,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = cam_cc_parent_map_0,
	.freq_tbl = ftbl_cam_cc_slow_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "cam_cc_slow_ahb_clk_src",
		.parent_names = cam_cc_parent_names_0,
		.num_parents = 6,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_ahb_clk = अणु
	.halt_reg = 0x606c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x606c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_slow_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_areg_clk = अणु
	.halt_reg = 0x6050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_areg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_fast_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_axi_clk = अणु
	.halt_reg = 0x6034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_bps_clk = अणु
	.halt_reg = 0x6024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x6024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_bps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_bps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_camnoc_atb_clk = अणु
	.halt_reg = 0xb12c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb12c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_camnoc_atb_clk",
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

अटल काष्ठा clk_branch cam_cc_cci_clk = अणु
	.halt_reg = 0xb0f0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb0f0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_cci_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cci_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_slow_ahb_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_csi0phytimer_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_csi1phytimer_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_csi2phytimer_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_csi3phytimer_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_fd_core_clk = अणु
	.halt_reg = 0xb0c8,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb0c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_fd_core_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_fd_core_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_fd_core_uar_clk = अणु
	.halt_reg = 0xb0d0,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb0d0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_fd_core_uar_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_fd_core_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_icp_apb_clk = अणु
	.halt_reg = 0xb084,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb084,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_icp_apb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_icp_atb_clk = अणु
	.halt_reg = 0xb078,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb078,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_icp_atb_clk",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_icp_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_icp_cti_clk = अणु
	.halt_reg = 0xb07c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb07c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_icp_cti_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_icp_ts_clk = अणु
	.halt_reg = 0xb080,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_icp_ts_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_axi_clk = अणु
	.halt_reg = 0x907c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x907c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_clk = अणु
	.halt_reg = 0x9024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_cphy_rx_clk = अणु
	.halt_reg = 0x9078,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9078,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_cphy_rx_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_csid_clk = अणु
	.halt_reg = 0x9050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_csid_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_0_csid_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_0_dsp_clk = अणु
	.halt_reg = 0x9034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x9034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_0_dsp_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_axi_clk = अणु
	.halt_reg = 0xa054,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_clk = अणु
	.halt_reg = 0xa024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_cphy_rx_clk = अणु
	.halt_reg = 0xa050,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa050,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_cphy_rx_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_csid_clk = अणु
	.halt_reg = 0xa048,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa048,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_csid_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_1_csid_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_अगरe_1_dsp_clk = अणु
	.halt_reg = 0xa02c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xa02c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ife_1_dsp_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_1_clk_src",
			पूर्ण,
			.num_parents = 1,
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_lite_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_cphy_rx_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ife_lite_csid_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_ahb_clk = अणु
	.halt_reg = 0x703c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x703c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_slow_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_areg_clk = अणु
	.halt_reg = 0x7038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_areg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_fast_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_axi_clk = अणु
	.halt_reg = 0x7034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_0_clk = अणु
	.halt_reg = 0x7024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x7024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ipe_0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_1_ahb_clk = अणु
	.halt_reg = 0x803c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x803c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_slow_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_1_areg_clk = अणु
	.halt_reg = 0x8038,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8038,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_1_areg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_fast_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_1_axi_clk = अणु
	.halt_reg = 0x8034,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8034,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_1_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_ipe_1_clk = अणु
	.halt_reg = 0x8024,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x8024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "cam_cc_ipe_1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_ipe_1_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_jpeg_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_lrme_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_mclk0_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_mclk1_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_mclk2_clk_src",
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
			.parent_names = (स्थिर अक्षर *[])अणु
				"cam_cc_mclk3_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch cam_cc_soc_ahb_clk = अणु
	.halt_reg = 0xb13c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0xb13c,
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
	.flags = HW_CTRL | POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc ipe_0_gdsc = अणु
	.gdscr = 0x7004,
	.pd = अणु
		.name = "ipe_0_gdsc",
	पूर्ण,
	.flags = HW_CTRL | POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc ipe_1_gdsc = अणु
	.gdscr = 0x8004,
	.pd = अणु
		.name = "ipe_1_gdsc",
	पूर्ण,
	.flags = HW_CTRL | POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc अगरe_0_gdsc = अणु
	.gdscr = 0x9004,
	.pd = अणु
		.name = "ife_0_gdsc",
	पूर्ण,
	.flags = POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc अगरe_1_gdsc = अणु
	.gdscr = 0xa004,
	.pd = अणु
		.name = "ife_1_gdsc",
	पूर्ण,
	.flags = POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc titan_top_gdsc = अणु
	.gdscr = 0xb134,
	.pd = अणु
		.name = "titan_top_gdsc",
	पूर्ण,
	.flags = POLL_CFG_GDSCR,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा clk_regmap *cam_cc_sdm845_घड़ीs[] = अणु
	[CAM_CC_BPS_AHB_CLK] = &cam_cc_bps_ahb_clk.clkr,
	[CAM_CC_BPS_AREG_CLK] = &cam_cc_bps_areg_clk.clkr,
	[CAM_CC_BPS_AXI_CLK] = &cam_cc_bps_axi_clk.clkr,
	[CAM_CC_BPS_CLK] = &cam_cc_bps_clk.clkr,
	[CAM_CC_BPS_CLK_SRC] = &cam_cc_bps_clk_src.clkr,
	[CAM_CC_CAMNOC_ATB_CLK] = &cam_cc_camnoc_atb_clk.clkr,
	[CAM_CC_CAMNOC_AXI_CLK] = &cam_cc_camnoc_axi_clk.clkr,
	[CAM_CC_CCI_CLK] = &cam_cc_cci_clk.clkr,
	[CAM_CC_CCI_CLK_SRC] = &cam_cc_cci_clk_src.clkr,
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
	[CAM_CC_FD_CORE_CLK] = &cam_cc_fd_core_clk.clkr,
	[CAM_CC_FD_CORE_CLK_SRC] = &cam_cc_fd_core_clk_src.clkr,
	[CAM_CC_FD_CORE_UAR_CLK] = &cam_cc_fd_core_uar_clk.clkr,
	[CAM_CC_ICP_APB_CLK] = &cam_cc_icp_apb_clk.clkr,
	[CAM_CC_ICP_ATB_CLK] = &cam_cc_icp_atb_clk.clkr,
	[CAM_CC_ICP_CLK] = &cam_cc_icp_clk.clkr,
	[CAM_CC_ICP_CLK_SRC] = &cam_cc_icp_clk_src.clkr,
	[CAM_CC_ICP_CTI_CLK] = &cam_cc_icp_cti_clk.clkr,
	[CAM_CC_ICP_TS_CLK] = &cam_cc_icp_ts_clk.clkr,
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
	[CAM_CC_IPE_1_AHB_CLK] = &cam_cc_ipe_1_ahb_clk.clkr,
	[CAM_CC_IPE_1_AREG_CLK] = &cam_cc_ipe_1_areg_clk.clkr,
	[CAM_CC_IPE_1_AXI_CLK] = &cam_cc_ipe_1_axi_clk.clkr,
	[CAM_CC_IPE_1_CLK] = &cam_cc_ipe_1_clk.clkr,
	[CAM_CC_IPE_1_CLK_SRC] = &cam_cc_ipe_1_clk_src.clkr,
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
	[CAM_CC_PLL0] = &cam_cc_pll0.clkr,
	[CAM_CC_PLL0_OUT_EVEN] = &cam_cc_pll0_out_even.clkr,
	[CAM_CC_PLL1] = &cam_cc_pll1.clkr,
	[CAM_CC_PLL1_OUT_EVEN] = &cam_cc_pll1_out_even.clkr,
	[CAM_CC_PLL2] = &cam_cc_pll2.clkr,
	[CAM_CC_PLL2_OUT_EVEN] = &cam_cc_pll2_out_even.clkr,
	[CAM_CC_PLL3] = &cam_cc_pll3.clkr,
	[CAM_CC_PLL3_OUT_EVEN] = &cam_cc_pll3_out_even.clkr,
	[CAM_CC_SLOW_AHB_CLK_SRC] = &cam_cc_slow_ahb_clk_src.clkr,
	[CAM_CC_SOC_AHB_CLK] = &cam_cc_soc_ahb_clk.clkr,
	[CAM_CC_SYS_TMR_CLK] = &cam_cc_sys_पंचांगr_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *cam_cc_sdm845_gdscs[] = अणु
	[BPS_GDSC] = &bps_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[IPE_1_GDSC] = &ipe_1_gdsc,
	[IFE_0_GDSC] = &अगरe_0_gdsc,
	[IFE_1_GDSC] = &अगरe_1_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cam_cc_sdm845_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xd004,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc cam_cc_sdm845_desc = अणु
	.config = &cam_cc_sdm845_regmap_config,
	.clks = cam_cc_sdm845_घड़ीs,
	.num_clks = ARRAY_SIZE(cam_cc_sdm845_घड़ीs),
	.gdscs = cam_cc_sdm845_gdscs,
	.num_gdscs = ARRAY_SIZE(cam_cc_sdm845_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id cam_cc_sdm845_match_table[] = अणु
	अणु .compatible = "qcom,sdm845-camcc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cam_cc_sdm845_match_table);

अटल पूर्णांक cam_cc_sdm845_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा alpha_pll_config cam_cc_pll_config = अणु पूर्ण;

	regmap = qcom_cc_map(pdev, &cam_cc_sdm845_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	cam_cc_pll_config.l = 0x1f;
	cam_cc_pll_config.alpha = 0x4000;
	clk_fabia_pll_configure(&cam_cc_pll0, regmap, &cam_cc_pll_config);

	cam_cc_pll_config.l = 0x2a;
	cam_cc_pll_config.alpha = 0x1556;
	clk_fabia_pll_configure(&cam_cc_pll1, regmap, &cam_cc_pll_config);

	cam_cc_pll_config.l = 0x32;
	cam_cc_pll_config.alpha = 0x0;
	clk_fabia_pll_configure(&cam_cc_pll2, regmap, &cam_cc_pll_config);

	cam_cc_pll_config.l = 0x14;
	clk_fabia_pll_configure(&cam_cc_pll3, regmap, &cam_cc_pll_config);

	वापस qcom_cc_really_probe(pdev, &cam_cc_sdm845_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver cam_cc_sdm845_driver = अणु
	.probe	= cam_cc_sdm845_probe,
	.driver	= अणु
		.name = "sdm845-camcc",
		.of_match_table = cam_cc_sdm845_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cam_cc_sdm845_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cam_cc_sdm845_driver);
पूर्ण
subsys_initcall(cam_cc_sdm845_init);

अटल व्योम __निकास cam_cc_sdm845_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cam_cc_sdm845_driver);
पूर्ण
module_निकास(cam_cc_sdm845_निकास);

MODULE_DESCRIPTION("QTI CAM_CC SDM845 Driver");
MODULE_LICENSE("GPL v2");
