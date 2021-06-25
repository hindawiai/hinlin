<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Jeffrey Hugo
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

#समावेश <dt-bindings/घड़ी/qcom,gpucc-msm8998.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-regmap-divider.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_XO,
	P_GPLL0,
	P_GPUPLL0_OUT_EVEN,
पूर्ण;

/* Instead of going directly to the block, XO is routed through this branch */
अटल काष्ठा clk_branch gpucc_cxo_clk = अणु
	.halt_reg = 0x1020,
	.clkr = अणु
		.enable_reg = 0x1020,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpucc_cxo_clk",
			.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "xo",
				.name = "xo"
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_IS_CRITICAL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा pll_vco fabia_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
	अणु 125000000, 1000000000, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable_fabia_even[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु 0x7, 8 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_alpha_pll gpupll0 = अणु
	.offset = 0x0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.vco_table = fabia_vco,
	.num_vco = ARRAY_SIZE(fabia_vco),
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpupll0",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gpucc_cxo_clk.clkr.hw पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_fabia_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpupll0_out_even = अणु
	.offset = 0x0,
	.post_भाग_shअगरt = 8,
	.post_भाग_प्रकारable = post_भाग_प्रकारable_fabia_even,
	.num_post_भाग = ARRAY_SIZE(post_भाग_प्रकारable_fabia_even),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_FABIA],
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpupll0_out_even",
		.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gpupll0.clkr.hw पूर्ण,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_alpha_pll_postभाग_fabia_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gpu_xo_gpll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gpu_xo_gpll0[] = अणु
	अणु .hw = &gpucc_cxo_clk.clkr.hw पूर्ण,
	अणु .fw_name = "gpll0", .name = "gpll0" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gpu_xo_gpupll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPUPLL0_OUT_EVEN, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gpu_xo_gpupll0[] = अणु
	अणु .hw = &gpucc_cxo_clk.clkr.hw पूर्ण,
	अणु .hw = &gpupll0_out_even.clkr.hw पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_rbcpr_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 rbcpr_clk_src = अणु
	.cmd_rcgr = 0x1030,
	.hid_width = 5,
	.parent_map = gpu_xo_gpll0_map,
	.freq_tbl = ftbl_rbcpr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "rbcpr_clk_src",
		.parent_data = gpu_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gfx3d_clk_src[] = अणु
	अणु .src = P_GPUPLL0_OUT_EVEN, .pre_भाग = 3 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gfx3d_clk_src = अणु
	.cmd_rcgr = 0x1070,
	.hid_width = 5,
	.parent_map = gpu_xo_gpupll0_map,
	.freq_tbl = ftbl_gfx3d_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gfx3d_clk_src",
		.parent_data = gpu_xo_gpupll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
		.flags = CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_rbbmसमयr_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 rbbmसमयr_clk_src = अणु
	.cmd_rcgr = 0x10b0,
	.hid_width = 5,
	.parent_map = gpu_xo_gpll0_map,
	.freq_tbl = ftbl_rbbmसमयr_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "rbbmtimer_clk_src",
		.parent_data = gpu_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gfx3d_isense_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPLL0, 15, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(300000000, P_GPLL0, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gfx3d_isense_clk_src = अणु
	.cmd_rcgr = 0x1100,
	.hid_width = 5,
	.parent_map = gpu_xo_gpll0_map,
	.freq_tbl = ftbl_gfx3d_isense_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gfx3d_isense_clk_src",
		.parent_data = gpu_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rbcpr_clk = अणु
	.halt_reg = 0x1054,
	.clkr = अणु
		.enable_reg = 0x1054,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rbcpr_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &rbcpr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx3d_clk = अणु
	.halt_reg = 0x1098,
	.clkr = अणु
		.enable_reg = 0x1098,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gfx3d_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rbbmसमयr_clk = अणु
	.halt_reg = 0x10d0,
	.clkr = अणु
		.enable_reg = 0x10d0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rbbmtimer_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &rbbmसमयr_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx3d_isense_clk = अणु
	.halt_reg = 0x1124,
	.clkr = अणु
		.enable_reg = 0x1124,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_isense_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw *[])अणु &gfx3d_isense_clk_src.clkr.hw पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc gpu_cx_gdsc = अणु
	.gdscr = 0x1004,
	.gds_hw_ctrl = 0x1008,
	.pd = अणु
		.name = "gpu_cx",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gpu_gx_gdsc = अणु
	.gdscr = 0x1094,
	.clamp_io_ctrl = 0x130,
	.resets = (अचिन्हित पूर्णांक [])अणु GPU_GX_BCR पूर्ण,
	.reset_count = 1,
	.cxcs = (अचिन्हित पूर्णांक [])अणु 0x1098 पूर्ण,
	.cxc_count = 1,
	.pd = अणु
		.name = "gpu_gx",
	पूर्ण,
	.parent = &gpu_cx_gdsc.pd,
	.pwrsts = PWRSTS_OFF_ON | PWRSTS_RET,
	.flags = CLAMP_IO | SW_RESET | AON_RESET | NO_RET_PERIPH,
पूर्ण;

अटल काष्ठा clk_regmap *gpucc_msm8998_घड़ीs[] = अणु
	[GPUPLL0] = &gpupll0.clkr,
	[GPUPLL0_OUT_EVEN] = &gpupll0_out_even.clkr,
	[RBCPR_CLK_SRC] = &rbcpr_clk_src.clkr,
	[GFX3D_CLK_SRC] = &gfx3d_clk_src.clkr,
	[RBBMTIMER_CLK_SRC] = &rbbmसमयr_clk_src.clkr,
	[GFX3D_ISENSE_CLK_SRC] = &gfx3d_isense_clk_src.clkr,
	[RBCPR_CLK] = &rbcpr_clk.clkr,
	[GFX3D_CLK] = &gfx3d_clk.clkr,
	[RBBMTIMER_CLK] = &rbbmसमयr_clk.clkr,
	[GFX3D_ISENSE_CLK] = &gfx3d_isense_clk.clkr,
	[GPUCC_CXO_CLK] = &gpucc_cxo_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *gpucc_msm8998_gdscs[] = अणु
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gpucc_msm8998_resets[] = अणु
	[GPU_CX_BCR] = अणु 0x1000 पूर्ण,
	[RBCPR_BCR] = अणु 0x1050 पूर्ण,
	[GPU_GX_BCR] = अणु 0x1090 पूर्ण,
	[GPU_ISENSE_BCR] = अणु 0x1120 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gpucc_msm8998_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x9000,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gpucc_msm8998_desc = अणु
	.config = &gpucc_msm8998_regmap_config,
	.clks = gpucc_msm8998_घड़ीs,
	.num_clks = ARRAY_SIZE(gpucc_msm8998_घड़ीs),
	.resets = gpucc_msm8998_resets,
	.num_resets = ARRAY_SIZE(gpucc_msm8998_resets),
	.gdscs = gpucc_msm8998_gdscs,
	.num_gdscs = ARRAY_SIZE(gpucc_msm8998_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gpucc_msm8998_match_table[] = अणु
	अणु .compatible = "qcom,msm8998-gpucc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpucc_msm8998_match_table);

अटल पूर्णांक gpucc_msm8998_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &gpucc_msm8998_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* क्रमce periph logic on to aव्योम perf counter corruption */
	regmap_ग_लिखो_bits(regmap, gfx3d_clk.clkr.enable_reg, BIT(13), BIT(13));
	/* tweak droop detector (GPUCC_GPU_DD_WRAP_CTRL) to reduce leakage */
	regmap_ग_लिखो_bits(regmap, gfx3d_clk.clkr.enable_reg, BIT(0), BIT(0));

	वापस qcom_cc_really_probe(pdev, &gpucc_msm8998_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gpucc_msm8998_driver = अणु
	.probe		= gpucc_msm8998_probe,
	.driver		= अणु
		.name	= "gpucc-msm8998",
		.of_match_table = gpucc_msm8998_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gpucc_msm8998_driver);

MODULE_DESCRIPTION("QCOM GPUCC MSM8998 Driver");
MODULE_LICENSE("GPL v2");
