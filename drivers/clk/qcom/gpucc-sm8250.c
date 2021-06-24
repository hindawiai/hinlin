<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,gpucc-sm8250.h>

#समावेश "common.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-branch.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

#घोषणा CX_GMU_CBCR_SLEEP_MASK		0xf
#घोषणा CX_GMU_CBCR_SLEEP_SHIFT		4
#घोषणा CX_GMU_CBCR_WAKE_MASK		0xf
#घोषणा CX_GMU_CBCR_WAKE_SHIFT		8

क्रमागत अणु
	P_BI_TCXO,
	P_GPLL0_OUT_MAIN,
	P_GPLL0_OUT_MAIN_DIV,
	P_GPU_CC_PLL0_OUT_MAIN,
	P_GPU_CC_PLL1_OUT_MAIN,
पूर्ण;

अटल काष्ठा pll_vco lucid_vco[] = अणु
	अणु 249600000, 2000000000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config gpu_cc_pll1_config = अणु
	.l = 0x1a,
	.alpha = 0xaaa,
	.config_ctl_val = 0x20485699,
	.config_ctl_hi_val = 0x00002261,
	.config_ctl_hi1_val = 0x029a699c,
	.user_ctl_val = 0x00000000,
	.user_ctl_hi_val = 0x00000805,
	.user_ctl_hi1_val = 0x00000000,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpu_cc_pll1 = अणु
	.offset = 0x100,
	.vco_table = lucid_vco,
	.num_vco = ARRAY_SIZE(lucid_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_LUCID],
	.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_pll1",
			.parent_data =  &(स्थिर काष्ठा clk_parent_data)अणु
				.fw_name = "bi_tcxo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_lucid_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map gpu_cc_parent_map_0[] = अणु
	अणु P_BI_TCXO, 0 पूर्ण,
	अणु P_GPU_CC_PLL1_OUT_MAIN, 3 पूर्ण,
	अणु P_GPLL0_OUT_MAIN, 5 पूर्ण,
	अणु P_GPLL0_OUT_MAIN_DIV, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gpu_cc_parent_data_0[] = अणु
	अणु .fw_name = "bi_tcxo" पूर्ण,
	अणु .hw = &gpu_cc_pll1.clkr.hw पूर्ण,
	अणु .fw_name = "gcc_gpu_gpll0_clk_src" पूर्ण,
	अणु .fw_name = "gcc_gpu_gpll0_div_clk_src" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gpu_cc_gmu_clk_src[] = अणु
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPLL0_OUT_MAIN_DIV, 1.5, 0, 0),
	F(500000000, P_GPU_CC_PLL1_OUT_MAIN, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gpu_cc_gmu_clk_src = अणु
	.cmd_rcgr = 0x1120,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = gpu_cc_parent_map_0,
	.freq_tbl = ftbl_gpu_cc_gmu_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpu_cc_gmu_clk_src",
		.parent_data = gpu_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(gpu_cc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_ahb_clk = अणु
	.halt_reg = 0x1078,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1078,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_crc_ahb_clk = अणु
	.halt_reg = 0x107c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x107c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_crc_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_cx_apb_clk = अणु
	.halt_reg = 0x1088,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1088,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_cx_apb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_cx_gmu_clk = अणु
	.halt_reg = 0x1098,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1098,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_cx_gmu_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gpu_cc_gmu_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_cx_snoc_dvm_clk = अणु
	.halt_reg = 0x108c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x108c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_cx_snoc_dvm_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_cxo_aon_clk = अणु
	.halt_reg = 0x1004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_cxo_aon_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_cxo_clk = अणु
	.halt_reg = 0x109c,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x109c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_cxo_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_gx_gmu_clk = अणु
	.halt_reg = 0x1064,
	.halt_check = BRANCH_HALT,
	.clkr = अणु
		.enable_reg = 0x1064,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gpu_cc_gx_gmu_clk",
			.parent_hws = (स्थिर काष्ठा clk_hw*[])अणु
				&gpu_cc_gmu_clk_src.clkr.hw,
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gpu_cc_hlos1_vote_gpu_smmu_clk = अणु
	.halt_reg = 0x5000,
	.halt_check = BRANCH_VOTED,
	.clkr = अणु
		.enable_reg = 0x5000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			 .name = "gpu_cc_hlos1_vote_gpu_smmu_clk",
			 .ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc gpu_cx_gdsc = अणु
	.gdscr = 0x106c,
	.gds_hw_ctrl = 0x1540,
	.pd = अणु
		.name = "gpu_cx_gdsc",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = VOTABLE,
पूर्ण;

अटल काष्ठा gdsc gpu_gx_gdsc = अणु
	.gdscr = 0x100c,
	.clamp_io_ctrl = 0x1508,
	.pd = अणु
		.name = "gpu_gx_gdsc",
		.घातer_on = gdsc_gx_करो_nothing_enable,
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
	.flags = CLAMP_IO | AON_RESET | POLL_CFG_GDSCR,
पूर्ण;

अटल काष्ठा clk_regmap *gpu_cc_sm8250_घड़ीs[] = अणु
	[GPU_CC_AHB_CLK] = &gpu_cc_ahb_clk.clkr,
	[GPU_CC_CRC_AHB_CLK] = &gpu_cc_crc_ahb_clk.clkr,
	[GPU_CC_CX_APB_CLK] = &gpu_cc_cx_apb_clk.clkr,
	[GPU_CC_CX_GMU_CLK] = &gpu_cc_cx_gmu_clk.clkr,
	[GPU_CC_CX_SNOC_DVM_CLK] = &gpu_cc_cx_snoc_dvm_clk.clkr,
	[GPU_CC_CXO_AON_CLK] = &gpu_cc_cxo_aon_clk.clkr,
	[GPU_CC_CXO_CLK] = &gpu_cc_cxo_clk.clkr,
	[GPU_CC_GMU_CLK_SRC] = &gpu_cc_gmu_clk_src.clkr,
	[GPU_CC_GX_GMU_CLK] = &gpu_cc_gx_gmu_clk.clkr,
	[GPU_CC_PLL1] = &gpu_cc_pll1.clkr,
	[GPU_CC_HLOS1_VOTE_GPU_SMMU_CLK] = &gpu_cc_hlos1_vote_gpu_smmu_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gpu_cc_sm8250_resets[] = अणु
	[GPUCC_GPU_CC_ACD_BCR] = अणु 0x1160 पूर्ण,
	[GPUCC_GPU_CC_CX_BCR] = अणु 0x1068 पूर्ण,
	[GPUCC_GPU_CC_GFX3D_AON_BCR] = अणु 0x10a0 पूर्ण,
	[GPUCC_GPU_CC_GMU_BCR] = अणु 0x111c पूर्ण,
	[GPUCC_GPU_CC_GX_BCR] = अणु 0x1008 पूर्ण,
	[GPUCC_GPU_CC_XO_BCR] = अणु 0x1000 पूर्ण,
पूर्ण;

अटल काष्ठा gdsc *gpu_cc_sm8250_gdscs[] = अणु
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gpu_cc_sm8250_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0x8008,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gpu_cc_sm8250_desc = अणु
	.config = &gpu_cc_sm8250_regmap_config,
	.clks = gpu_cc_sm8250_घड़ीs,
	.num_clks = ARRAY_SIZE(gpu_cc_sm8250_घड़ीs),
	.resets = gpu_cc_sm8250_resets,
	.num_resets = ARRAY_SIZE(gpu_cc_sm8250_resets),
	.gdscs = gpu_cc_sm8250_gdscs,
	.num_gdscs = ARRAY_SIZE(gpu_cc_sm8250_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gpu_cc_sm8250_match_table[] = अणु
	अणु .compatible = "qcom,sm8250-gpucc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpu_cc_sm8250_match_table);

अटल पूर्णांक gpu_cc_sm8250_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक value, mask;

	regmap = qcom_cc_map(pdev, &gpu_cc_sm8250_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	clk_lucid_pll_configure(&gpu_cc_pll1, regmap, &gpu_cc_pll1_config);

	/*
	 * Configure gpu_cc_cx_gmu_clk with recommended
	 * wakeup/sleep settings
	 */
	mask = CX_GMU_CBCR_WAKE_MASK << CX_GMU_CBCR_WAKE_SHIFT;
	mask |= CX_GMU_CBCR_SLEEP_MASK << CX_GMU_CBCR_SLEEP_SHIFT;
	value = 0xf << CX_GMU_CBCR_WAKE_SHIFT | 0xf << CX_GMU_CBCR_SLEEP_SHIFT;
	regmap_update_bits(regmap, 0x1098, mask, value);

	वापस qcom_cc_really_probe(pdev, &gpu_cc_sm8250_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver gpu_cc_sm8250_driver = अणु
	.probe = gpu_cc_sm8250_probe,
	.driver = अणु
		.name = "sm8250-gpucc",
		.of_match_table = gpu_cc_sm8250_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gpu_cc_sm8250_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpu_cc_sm8250_driver);
पूर्ण
subsys_initcall(gpu_cc_sm8250_init);

अटल व्योम __निकास gpu_cc_sm8250_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gpu_cc_sm8250_driver);
पूर्ण
module_निकास(gpu_cc_sm8250_निकास);

MODULE_DESCRIPTION("QTI GPU_CC SM8250 Driver");
MODULE_LICENSE("GPL v2");
