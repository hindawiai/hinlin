<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/घड़ी/qcom,mmcc-msm8960.h>
#समावेश <dt-bindings/reset/qcom,mmcc-msm8960.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"

क्रमागत अणु
	P_PXO,
	P_PLL8,
	P_PLL2,
	P_PLL3,
	P_PLL15,
	P_HDMI_PLL,
	P_DSI1_PLL_DSICLK,
	P_DSI2_PLL_DSICLK,
	P_DSI1_PLL_BYTECLK,
	P_DSI2_PLL_BYTECLK,
पूर्ण;

#घोषणा F_MN(f, s, _m, _n) अणु .freq = f, .src = s, .m = _m, .n = _n पूर्ण

अटल स्थिर काष्ठा parent_map mmcc_pxo_pll8_pll2_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL8, 2 पूर्ण,
	अणु P_PLL2, 1 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmcc_pxo_pll8_pll2[] = अणु
	"pxo",
	"pll8_vote",
	"pll2",
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_pxo_pll8_pll2_pll3_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL8, 2 पूर्ण,
	अणु P_PLL2, 1 पूर्ण,
	अणु P_PLL3, 3 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmcc_pxo_pll8_pll2_pll15[] = अणु
	"pxo",
	"pll8_vote",
	"pll2",
	"pll15",
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_pxo_pll8_pll2_pll15_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_PLL8, 2 पूर्ण,
	अणु P_PLL2, 1 पूर्ण,
	अणु P_PLL15, 3 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmcc_pxo_pll8_pll2_pll3[] = अणु
	"pxo",
	"pll8_vote",
	"pll2",
	"pll3",
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_pxo_dsi2_dsi1_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_DSI2_PLL_DSICLK, 1 पूर्ण,
	अणु P_DSI1_PLL_DSICLK, 3 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmcc_pxo_dsi2_dsi1[] = अणु
	"pxo",
	"dsi2pll",
	"dsi1pll",
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_pxo_dsi1_dsi2_byte_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_DSI1_PLL_BYTECLK, 1 पूर्ण,
	अणु P_DSI2_PLL_BYTECLK, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmcc_pxo_dsi1_dsi2_byte[] = अणु
	"pxo",
	"dsi1pllbyte",
	"dsi2pllbyte",
पूर्ण;

अटल काष्ठा clk_pll pll2 = अणु
	.l_reg = 0x320,
	.m_reg = 0x324,
	.n_reg = 0x328,
	.config_reg = 0x32c,
	.mode_reg = 0x31c,
	.status_reg = 0x334,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll2",
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll pll15 = अणु
	.l_reg = 0x33c,
	.m_reg = 0x340,
	.n_reg = 0x344,
	.config_reg = 0x348,
	.mode_reg = 0x338,
	.status_reg = 0x350,
	.status_bit = 16,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pll15",
		.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_config pll15_config = अणु
	.l = 33,
	.m = 1,
	.n = 3,
	.vco_val = 0x2 << 16,
	.vco_mask = 0x3 << 16,
	.pre_भाग_val = 0x0,
	.pre_भाग_mask = BIT(19),
	.post_भाग_val = 0x0,
	.post_भाग_mask = 0x3 << 20,
	.mn_ena_mask = BIT(22),
	.मुख्य_output_mask = BIT(23),
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_cam[] = अणु
	अणु   6000000, P_PLL8, 4, 1, 16 पूर्ण,
	अणु   8000000, P_PLL8, 4, 1, 12 पूर्ण,
	अणु  12000000, P_PLL8, 4, 1,  8 पूर्ण,
	अणु  16000000, P_PLL8, 4, 1,  6 पूर्ण,
	अणु  19200000, P_PLL8, 4, 1,  5 पूर्ण,
	अणु  24000000, P_PLL8, 4, 1,  4 पूर्ण,
	अणु  32000000, P_PLL8, 4, 1,  3 पूर्ण,
	अणु  48000000, P_PLL8, 4, 1,  2 पूर्ण,
	अणु  64000000, P_PLL8, 3, 1,  2 पूर्ण,
	अणु  96000000, P_PLL8, 4, 0,  0 पूर्ण,
	अणु 128000000, P_PLL8, 3, 0,  0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg camclk0_src = अणु
	.ns_reg = 0x0148,
	.md_reg = 0x0144,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 8,
		.reset_in_cc = true,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_cam,
	.clkr = अणु
		.enable_reg = 0x0140,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camclk0_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camclk0_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x0140,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camclk0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "camclk0_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,

पूर्ण;

अटल काष्ठा clk_rcg camclk1_src = अणु
	.ns_reg = 0x015c,
	.md_reg = 0x0158,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 8,
		.reset_in_cc = true,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_cam,
	.clkr = अणु
		.enable_reg = 0x0154,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camclk1_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camclk1_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 16,
	.clkr = अणु
		.enable_reg = 0x0154,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camclk1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "camclk1_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,

पूर्ण;

अटल काष्ठा clk_rcg camclk2_src = अणु
	.ns_reg = 0x0228,
	.md_reg = 0x0224,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 8,
		.reset_in_cc = true,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_cam,
	.clkr = अणु
		.enable_reg = 0x0220,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camclk2_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch camclk2_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 16,
	.clkr = अणु
		.enable_reg = 0x0220,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "camclk2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "camclk2_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,

पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_csi[] = अणु
	अणु  27000000, P_PXO,  1, 0, 0 पूर्ण,
	अणु  85330000, P_PLL8, 1, 2, 9 पूर्ण,
	अणु 177780000, P_PLL2, 1, 2, 9 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg csi0_src = अणु
	.ns_reg = 0x0048,
	.md_reg	= 0x0044,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_csi,
	.clkr = अणु
		.enable_reg = 0x0040,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi0_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi0_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x0040,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "csi0_src" पूर्ण,
			.num_parents = 1,
			.name = "csi0_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi0_phy_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x0040,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "csi0_src" पूर्ण,
			.num_parents = 1,
			.name = "csi0_phy_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg csi1_src = अणु
	.ns_reg = 0x0010,
	.md_reg	= 0x0028,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_csi,
	.clkr = अणु
		.enable_reg = 0x0024,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi1_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi1_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x0024,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "csi1_src" पूर्ण,
			.num_parents = 1,
			.name = "csi1_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi1_phy_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x0024,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "csi1_src" पूर्ण,
			.num_parents = 1,
			.name = "csi1_phy_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg csi2_src = अणु
	.ns_reg = 0x0234,
	.md_reg = 0x022c,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_csi,
	.clkr = अणु
		.enable_reg = 0x022c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi2_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi2_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 29,
	.clkr = अणु
		.enable_reg = 0x022c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "csi2_src" पूर्ण,
			.num_parents = 1,
			.name = "csi2_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi2_phy_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 29,
	.clkr = अणु
		.enable_reg = 0x022c,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "csi2_src" पूर्ण,
			.num_parents = 1,
			.name = "csi2_phy_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा clk_pix_rdi अणु
	u32 s_reg;
	u32 s_mask;
	u32 s2_reg;
	u32 s2_mask;
	काष्ठा clk_regmap clkr;
पूर्ण;

#घोषणा to_clk_pix_rdi(_hw) \
	container_of(to_clk_regmap(_hw), काष्ठा clk_pix_rdi, clkr)

अटल पूर्णांक pix_rdi_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	u32 val;
	काष्ठा clk_pix_rdi *rdi = to_clk_pix_rdi(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);

	/*
	 * These घड़ीs select three inमाला_दो via two muxes. One mux selects
	 * between csi0 and csi1 and the second mux selects between that mux's
	 * output and csi2. The source and destination selections क्रम each
	 * mux must be घड़ीing क्रम the चयन to succeed so just turn on
	 * all three sources because it's easier than figuring out what source
	 * needs to be on at what समय.
	 */
	क्रम (i = 0; i < num_parents; i++) अणु
		काष्ठा clk_hw *p = clk_hw_get_parent_by_index(hw, i);
		ret = clk_prepare_enable(p->clk);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (index == 2)
		val = rdi->s2_mask;
	अन्यथा
		val = 0;
	regmap_update_bits(rdi->clkr.regmap, rdi->s2_reg, rdi->s2_mask, val);
	/*
	 * Wait at least 6 cycles of slowest घड़ी
	 * क्रम the glitch-मुक्त MUX to fully चयन sources.
	 */
	udelay(1);

	अगर (index == 1)
		val = rdi->s_mask;
	अन्यथा
		val = 0;
	regmap_update_bits(rdi->clkr.regmap, rdi->s_reg, rdi->s_mask, val);
	/*
	 * Wait at least 6 cycles of slowest घड़ी
	 * क्रम the glitch-मुक्त MUX to fully चयन sources.
	 */
	udelay(1);

err:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा clk_hw *p = clk_hw_get_parent_by_index(hw, i);
		clk_disable_unprepare(p->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल u8 pix_rdi_get_parent(काष्ठा clk_hw *hw)
अणु
	u32 val;
	काष्ठा clk_pix_rdi *rdi = to_clk_pix_rdi(hw);


	regmap_पढ़ो(rdi->clkr.regmap, rdi->s2_reg, &val);
	अगर (val & rdi->s2_mask)
		वापस 2;

	regmap_पढ़ो(rdi->clkr.regmap, rdi->s_reg, &val);
	अगर (val & rdi->s_mask)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ops_pix_rdi = अणु
	.enable = clk_enable_regmap,
	.disable = clk_disable_regmap,
	.set_parent = pix_rdi_set_parent,
	.get_parent = pix_rdi_get_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल स्थिर अक्षर * स्थिर pix_rdi_parents[] = अणु
	"csi0_clk",
	"csi1_clk",
	"csi2_clk",
पूर्ण;

अटल काष्ठा clk_pix_rdi csi_pix_clk = अणु
	.s_reg = 0x0058,
	.s_mask = BIT(25),
	.s2_reg = 0x0238,
	.s2_mask = BIT(13),
	.clkr = अणु
		.enable_reg = 0x0058,
		.enable_mask = BIT(26),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi_pix_clk",
			.parent_names = pix_rdi_parents,
			.num_parents = 3,
			.ops = &clk_ops_pix_rdi,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pix_rdi csi_pix1_clk = अणु
	.s_reg = 0x0238,
	.s_mask = BIT(8),
	.s2_reg = 0x0238,
	.s2_mask = BIT(9),
	.clkr = अणु
		.enable_reg = 0x0238,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi_pix1_clk",
			.parent_names = pix_rdi_parents,
			.num_parents = 3,
			.ops = &clk_ops_pix_rdi,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pix_rdi csi_rdi_clk = अणु
	.s_reg = 0x0058,
	.s_mask = BIT(12),
	.s2_reg = 0x0238,
	.s2_mask = BIT(12),
	.clkr = अणु
		.enable_reg = 0x0058,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi_rdi_clk",
			.parent_names = pix_rdi_parents,
			.num_parents = 3,
			.ops = &clk_ops_pix_rdi,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pix_rdi csi_rdi1_clk = अणु
	.s_reg = 0x0238,
	.s_mask = BIT(0),
	.s2_reg = 0x0238,
	.s2_mask = BIT(1),
	.clkr = अणु
		.enable_reg = 0x0238,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi_rdi1_clk",
			.parent_names = pix_rdi_parents,
			.num_parents = 3,
			.ops = &clk_ops_pix_rdi,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pix_rdi csi_rdi2_clk = अणु
	.s_reg = 0x0238,
	.s_mask = BIT(4),
	.s2_reg = 0x0238,
	.s2_mask = BIT(5),
	.clkr = अणु
		.enable_reg = 0x0238,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi_rdi2_clk",
			.parent_names = pix_rdi_parents,
			.num_parents = 3,
			.ops = &clk_ops_pix_rdi,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_csiphyसमयr[] = अणु
	अणु  85330000, P_PLL8, 1, 2, 9 पूर्ण,
	अणु 177780000, P_PLL2, 1, 2, 9 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg csiphyसमयr_src = अणु
	.ns_reg = 0x0168,
	.md_reg = 0x0164,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 8,
		.reset_in_cc = true,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_csiphyसमयr,
	.clkr = अणु
		.enable_reg = 0x0160,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csiphytimer_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर csixphy_समयr_src[] = अणु "csiphytimer_src" पूर्ण;

अटल काष्ठा clk_branch csiphy0_समयr_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 17,
	.clkr = अणु
		.enable_reg = 0x0160,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = csixphy_समयr_src,
			.num_parents = 1,
			.name = "csiphy0_timer_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csiphy1_समयr_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 18,
	.clkr = अणु
		.enable_reg = 0x0160,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = csixphy_समयr_src,
			.num_parents = 1,
			.name = "csiphy1_timer_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csiphy2_समयr_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 30,
	.clkr = अणु
		.enable_reg = 0x0160,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = csixphy_समयr_src,
			.num_parents = 1,
			.name = "csiphy2_timer_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_gfx2d[] = अणु
	F_MN( 27000000, P_PXO,  1,  0),
	F_MN( 48000000, P_PLL8, 1,  8),
	F_MN( 54857000, P_PLL8, 1,  7),
	F_MN( 64000000, P_PLL8, 1,  6),
	F_MN( 76800000, P_PLL8, 1,  5),
	F_MN( 96000000, P_PLL8, 1,  4),
	F_MN(128000000, P_PLL8, 1,  3),
	F_MN(145455000, P_PLL2, 2, 11),
	F_MN(160000000, P_PLL2, 1,  5),
	F_MN(177778000, P_PLL2, 2,  9),
	F_MN(200000000, P_PLL2, 1,  4),
	F_MN(228571000, P_PLL2, 2,  7),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_dyn_rcg gfx2d0_src = अणु
	.ns_reg[0] = 0x0070,
	.ns_reg[1] = 0x0070,
	.md_reg[0] = 0x0064,
	.md_reg[1] = 0x0068,
	.bank_reg = 0x0060,
	.mn[0] = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 25,
		.mnctr_mode_shअगरt = 9,
		.n_val_shअगरt = 20,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.mn[1] = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 24,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 3,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.mux_sel_bit = 11,
	.freq_tbl = clk_tbl_gfx2d,
	.clkr = अणु
		.enable_reg = 0x0060,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx2d0_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx2d0_clk = अणु
	.halt_reg = 0x01c8,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x0060,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx2d0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gfx2d0_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_dyn_rcg gfx2d1_src = अणु
	.ns_reg[0] = 0x007c,
	.ns_reg[1] = 0x007c,
	.md_reg[0] = 0x0078,
	.md_reg[1] = 0x006c,
	.bank_reg = 0x0074,
	.mn[0] = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 25,
		.mnctr_mode_shअगरt = 9,
		.n_val_shअगरt = 20,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.mn[1] = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 24,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 3,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.mux_sel_bit = 11,
	.freq_tbl = clk_tbl_gfx2d,
	.clkr = अणु
		.enable_reg = 0x0074,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx2d1_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx2d1_clk = अणु
	.halt_reg = 0x01c8,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x0074,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx2d1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gfx2d1_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_gfx3d[] = अणु
	F_MN( 27000000, P_PXO,  1,  0),
	F_MN( 48000000, P_PLL8, 1,  8),
	F_MN( 54857000, P_PLL8, 1,  7),
	F_MN( 64000000, P_PLL8, 1,  6),
	F_MN( 76800000, P_PLL8, 1,  5),
	F_MN( 96000000, P_PLL8, 1,  4),
	F_MN(128000000, P_PLL8, 1,  3),
	F_MN(145455000, P_PLL2, 2, 11),
	F_MN(160000000, P_PLL2, 1,  5),
	F_MN(177778000, P_PLL2, 2,  9),
	F_MN(200000000, P_PLL2, 1,  4),
	F_MN(228571000, P_PLL2, 2,  7),
	F_MN(266667000, P_PLL2, 1,  3),
	F_MN(300000000, P_PLL3, 1,  4),
	F_MN(320000000, P_PLL2, 2,  5),
	F_MN(400000000, P_PLL2, 1,  2),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_gfx3d_8064[] = अणु
	F_MN( 27000000, P_PXO,   0,  0),
	F_MN( 48000000, P_PLL8,  1,  8),
	F_MN( 54857000, P_PLL8,  1,  7),
	F_MN( 64000000, P_PLL8,  1,  6),
	F_MN( 76800000, P_PLL8,  1,  5),
	F_MN( 96000000, P_PLL8,  1,  4),
	F_MN(128000000, P_PLL8,  1,  3),
	F_MN(145455000, P_PLL2,  2, 11),
	F_MN(160000000, P_PLL2,  1,  5),
	F_MN(177778000, P_PLL2,  2,  9),
	F_MN(192000000, P_PLL8,  1,  2),
	F_MN(200000000, P_PLL2,  1,  4),
	F_MN(228571000, P_PLL2,  2,  7),
	F_MN(266667000, P_PLL2,  1,  3),
	F_MN(320000000, P_PLL2,  2,  5),
	F_MN(400000000, P_PLL2,  1,  2),
	F_MN(450000000, P_PLL15, 1,  2),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_dyn_rcg gfx3d_src = अणु
	.ns_reg[0] = 0x008c,
	.ns_reg[1] = 0x008c,
	.md_reg[0] = 0x0084,
	.md_reg[1] = 0x0088,
	.bank_reg = 0x0080,
	.mn[0] = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 25,
		.mnctr_mode_shअगरt = 9,
		.n_val_shअगरt = 18,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.mn[1] = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 24,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 14,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 3,
		.parent_map = mmcc_pxo_pll8_pll2_pll3_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_pll3_map,
	पूर्ण,
	.mux_sel_bit = 11,
	.freq_tbl = clk_tbl_gfx3d,
	.clkr = अणु
		.enable_reg = 0x0080,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_src",
			.parent_names = mmcc_pxo_pll8_pll2_pll3,
			.num_parents = 4,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_init_data gfx3d_8064_init = अणु
	.name = "gfx3d_src",
	.parent_names = mmcc_pxo_pll8_pll2_pll15,
	.num_parents = 4,
	.ops = &clk_dyn_rcg_ops,
पूर्ण;

अटल काष्ठा clk_branch gfx3d_clk = अणु
	.halt_reg = 0x01c8,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x0080,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "gfx3d_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_vcap[] = अणु
	F_MN( 27000000, P_PXO,  0,  0),
	F_MN( 54860000, P_PLL8, 1,  7),
	F_MN( 64000000, P_PLL8, 1,  6),
	F_MN( 76800000, P_PLL8, 1,  5),
	F_MN(128000000, P_PLL8, 1,  3),
	F_MN(160000000, P_PLL2, 1,  5),
	F_MN(200000000, P_PLL2, 1,  4),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_dyn_rcg vcap_src = अणु
	.ns_reg[0] = 0x021c,
	.ns_reg[1] = 0x021c,
	.md_reg[0] = 0x01ec,
	.md_reg[1] = 0x0218,
	.bank_reg = 0x0178,
	.mn[0] = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 23,
		.mnctr_mode_shअगरt = 9,
		.n_val_shअगरt = 18,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.mn[1] = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 22,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 14,
		.m_val_shअगरt = 4,
		.width = 4,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 3,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.mux_sel_bit = 11,
	.freq_tbl = clk_tbl_vcap,
	.clkr = अणु
		.enable_reg = 0x0178,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcap_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcap_clk = अणु
	.halt_reg = 0x0240,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x0178,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcap_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "vcap_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcap_npl_clk = अणु
	.halt_reg = 0x0240,
	.halt_bit = 25,
	.clkr = अणु
		.enable_reg = 0x0178,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcap_npl_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "vcap_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_ijpeg[] = अणु
	अणु  27000000, P_PXO,  1, 0,  0 पूर्ण,
	अणु  36570000, P_PLL8, 1, 2, 21 पूर्ण,
	अणु  54860000, P_PLL8, 7, 0,  0 पूर्ण,
	अणु  96000000, P_PLL8, 4, 0,  0 पूर्ण,
	अणु 109710000, P_PLL8, 1, 2,  7 पूर्ण,
	अणु 128000000, P_PLL8, 3, 0,  0 पूर्ण,
	अणु 153600000, P_PLL8, 1, 2,  5 पूर्ण,
	अणु 200000000, P_PLL2, 4, 0,  0 पूर्ण,
	अणु 228571000, P_PLL2, 1, 2,  7 पूर्ण,
	अणु 266667000, P_PLL2, 1, 1,  3 पूर्ण,
	अणु 320000000, P_PLL2, 1, 2,  5 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg ijpeg_src = अणु
	.ns_reg = 0x00a0,
	.md_reg = 0x009c,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_ijpeg,
	.clkr = अणु
		.enable_reg = 0x0098,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ijpeg_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ijpeg_clk = अणु
	.halt_reg = 0x01c8,
	.halt_bit = 24,
	.clkr = अणु
		.enable_reg = 0x0098,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ijpeg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "ijpeg_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_jpegd[] = अणु
	अणु  64000000, P_PLL8, 6 पूर्ण,
	अणु  76800000, P_PLL8, 5 पूर्ण,
	अणु  96000000, P_PLL8, 4 पूर्ण,
	अणु 160000000, P_PLL2, 5 पूर्ण,
	अणु 200000000, P_PLL2, 4 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg jpegd_src = अणु
	.ns_reg = 0x00ac,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_jpegd,
	.clkr = अणु
		.enable_reg = 0x00a4,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "jpegd_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch jpegd_clk = अणु
	.halt_reg = 0x01c8,
	.halt_bit = 19,
	.clkr = अणु
		.enable_reg = 0x00a4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "jpegd_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "jpegd_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_mdp[] = अणु
	अणु   9600000, P_PLL8, 1, 1, 40 पूर्ण,
	अणु  13710000, P_PLL8, 1, 1, 28 पूर्ण,
	अणु  27000000, P_PXO,  1, 0,  0 पूर्ण,
	अणु  29540000, P_PLL8, 1, 1, 13 पूर्ण,
	अणु  34910000, P_PLL8, 1, 1, 11 पूर्ण,
	अणु  38400000, P_PLL8, 1, 1, 10 पूर्ण,
	अणु  59080000, P_PLL8, 1, 2, 13 पूर्ण,
	अणु  76800000, P_PLL8, 1, 1,  5 पूर्ण,
	अणु  85330000, P_PLL8, 1, 2,  9 पूर्ण,
	अणु  96000000, P_PLL8, 1, 1,  4 पूर्ण,
	अणु 128000000, P_PLL8, 1, 1,  3 पूर्ण,
	अणु 160000000, P_PLL2, 1, 1,  5 पूर्ण,
	अणु 177780000, P_PLL2, 1, 2,  9 पूर्ण,
	अणु 200000000, P_PLL2, 1, 1,  4 पूर्ण,
	अणु 228571000, P_PLL2, 1, 2,  7 पूर्ण,
	अणु 266667000, P_PLL2, 1, 1,  3 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_dyn_rcg mdp_src = अणु
	.ns_reg[0] = 0x00d0,
	.ns_reg[1] = 0x00d0,
	.md_reg[0] = 0x00c4,
	.md_reg[1] = 0x00c8,
	.bank_reg = 0x00c0,
	.mn[0] = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 31,
		.mnctr_mode_shअगरt = 9,
		.n_val_shअगरt = 22,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.mn[1] = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 30,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 14,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 3,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.mux_sel_bit = 11,
	.freq_tbl = clk_tbl_mdp,
	.clkr = अणु
		.enable_reg = 0x00c0,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdp_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x00c0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "mdp_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdp_lut_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x016c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "mdp_src" पूर्ण,
			.num_parents = 1,
			.name = "mdp_lut_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdp_vsync_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 22,
	.clkr = अणु
		.enable_reg = 0x0058,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_vsync_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_rot[] = अणु
	अणु  27000000, P_PXO,   1 पूर्ण,
	अणु  29540000, P_PLL8, 13 पूर्ण,
	अणु  32000000, P_PLL8, 12 पूर्ण,
	अणु  38400000, P_PLL8, 10 पूर्ण,
	अणु  48000000, P_PLL8,  8 पूर्ण,
	अणु  54860000, P_PLL8,  7 पूर्ण,
	अणु  64000000, P_PLL8,  6 पूर्ण,
	अणु  76800000, P_PLL8,  5 पूर्ण,
	अणु  96000000, P_PLL8,  4 पूर्ण,
	अणु 100000000, P_PLL2,  8 पूर्ण,
	अणु 114290000, P_PLL2,  7 पूर्ण,
	अणु 133330000, P_PLL2,  6 पूर्ण,
	अणु 160000000, P_PLL2,  5 पूर्ण,
	अणु 200000000, P_PLL2,  4 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_dyn_rcg rot_src = अणु
	.ns_reg[0] = 0x00e8,
	.ns_reg[1] = 0x00e8,
	.bank_reg = 0x00e8,
	.p[0] = अणु
		.pre_भाग_shअगरt = 22,
		.pre_भाग_width = 4,
	पूर्ण,
	.p[1] = अणु
		.pre_भाग_shअगरt = 26,
		.pre_भाग_width = 4,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 16,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 19,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.mux_sel_bit = 30,
	.freq_tbl = clk_tbl_rot,
	.clkr = अणु
		.enable_reg = 0x00e0,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rot_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rot_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x00e0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rot_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "rot_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा parent_map mmcc_pxo_hdmi_map[] = अणु
	अणु P_PXO, 0 पूर्ण,
	अणु P_HDMI_PLL, 3 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmcc_pxo_hdmi[] = अणु
	"pxo",
	"hdmi_pll",
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_tv[] = अणु
	अणु  .src = P_HDMI_PLL, .pre_भाग = 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg tv_src = अणु
	.ns_reg = 0x00f4,
	.md_reg = 0x00f0,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_hdmi_map,
	पूर्ण,
	.freq_tbl = clk_tbl_tv,
	.clkr = अणु
		.enable_reg = 0x00ec,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "tv_src",
			.parent_names = mmcc_pxo_hdmi,
			.num_parents = 2,
			.ops = &clk_rcg_bypass_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tv_src_name[] = अणु "tv_src" पूर्ण;

अटल काष्ठा clk_branch tv_enc_clk = अणु
	.halt_reg = 0x01d4,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x00ec,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = tv_src_name,
			.num_parents = 1,
			.name = "tv_enc_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch tv_dac_clk = अणु
	.halt_reg = 0x01d4,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x00ec,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = tv_src_name,
			.num_parents = 1,
			.name = "tv_dac_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdp_tv_clk = अणु
	.halt_reg = 0x01d4,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x00ec,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = tv_src_name,
			.num_parents = 1,
			.name = "mdp_tv_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch hdmi_tv_clk = अणु
	.halt_reg = 0x01d4,
	.halt_bit = 11,
	.clkr = अणु
		.enable_reg = 0x00ec,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = tv_src_name,
			.num_parents = 1,
			.name = "hdmi_tv_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rgb_tv_clk = अणु
	.halt_reg = 0x0240,
	.halt_bit = 27,
	.clkr = अणु
		.enable_reg = 0x0124,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = tv_src_name,
			.num_parents = 1,
			.name = "rgb_tv_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch npl_tv_clk = अणु
	.halt_reg = 0x0240,
	.halt_bit = 26,
	.clkr = अणु
		.enable_reg = 0x0124,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = tv_src_name,
			.num_parents = 1,
			.name = "npl_tv_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch hdmi_app_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 25,
	.clkr = अणु
		.enable_reg = 0x005c,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,
			.num_parents = 1,
			.name = "hdmi_app_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_vcodec[] = अणु
	F_MN( 27000000, P_PXO,  1,  0),
	F_MN( 32000000, P_PLL8, 1, 12),
	F_MN( 48000000, P_PLL8, 1,  8),
	F_MN( 54860000, P_PLL8, 1,  7),
	F_MN( 96000000, P_PLL8, 1,  4),
	F_MN(133330000, P_PLL2, 1,  6),
	F_MN(200000000, P_PLL2, 1,  4),
	F_MN(228570000, P_PLL2, 2,  7),
	F_MN(266670000, P_PLL2, 1,  3),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_dyn_rcg vcodec_src = अणु
	.ns_reg[0] = 0x0100,
	.ns_reg[1] = 0x0100,
	.md_reg[0] = 0x00fc,
	.md_reg[1] = 0x0128,
	.bank_reg = 0x00f8,
	.mn[0] = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 31,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 11,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.mn[1] = अणु
		.mnctr_en_bit = 10,
		.mnctr_reset_bit = 30,
		.mnctr_mode_shअगरt = 11,
		.n_val_shअगरt = 19,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.s[0] = अणु
		.src_sel_shअगरt = 27,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.s[1] = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.mux_sel_bit = 13,
	.freq_tbl = clk_tbl_vcodec,
	.clkr = अणु
		.enable_reg = 0x00f8,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcodec_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_dyn_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcodec_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 29,
	.clkr = अणु
		.enable_reg = 0x00f8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcodec_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "vcodec_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_vpe[] = अणु
	अणु  27000000, P_PXO,   1 पूर्ण,
	अणु  34909000, P_PLL8, 11 पूर्ण,
	अणु  38400000, P_PLL8, 10 पूर्ण,
	अणु  64000000, P_PLL8,  6 पूर्ण,
	अणु  76800000, P_PLL8,  5 पूर्ण,
	अणु  96000000, P_PLL8,  4 पूर्ण,
	अणु 100000000, P_PLL2,  8 पूर्ण,
	अणु 160000000, P_PLL2,  5 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg vpe_src = अणु
	.ns_reg = 0x0118,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_vpe,
	.clkr = अणु
		.enable_reg = 0x0110,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vpe_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vpe_clk = अणु
	.halt_reg = 0x01c8,
	.halt_bit = 28,
	.clkr = अणु
		.enable_reg = 0x0110,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vpe_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "vpe_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_vfe[] = अणु
	अणु  13960000, P_PLL8,  1, 2, 55 पूर्ण,
	अणु  27000000, P_PXO,   1, 0,  0 पूर्ण,
	अणु  36570000, P_PLL8,  1, 2, 21 पूर्ण,
	अणु  38400000, P_PLL8,  2, 1,  5 पूर्ण,
	अणु  45180000, P_PLL8,  1, 2, 17 पूर्ण,
	अणु  48000000, P_PLL8,  2, 1,  4 पूर्ण,
	अणु  54860000, P_PLL8,  1, 1,  7 पूर्ण,
	अणु  64000000, P_PLL8,  2, 1,  3 पूर्ण,
	अणु  76800000, P_PLL8,  1, 1,  5 पूर्ण,
	अणु  96000000, P_PLL8,  2, 1,  2 पूर्ण,
	अणु 109710000, P_PLL8,  1, 2,  7 पूर्ण,
	अणु 128000000, P_PLL8,  1, 1,  3 पूर्ण,
	अणु 153600000, P_PLL8,  1, 2,  5 पूर्ण,
	अणु 200000000, P_PLL2,  2, 1,  2 पूर्ण,
	अणु 228570000, P_PLL2,  1, 2,  7 पूर्ण,
	अणु 266667000, P_PLL2,  1, 1,  3 पूर्ण,
	अणु 320000000, P_PLL2,  1, 2,  5 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg vfe_src = अणु
	.ns_reg = 0x0108,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 10,
		.pre_भाग_width = 1,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_pll8_pll2_map,
	पूर्ण,
	.freq_tbl = clk_tbl_vfe,
	.clkr = अणु
		.enable_reg = 0x0104,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vfe_src",
			.parent_names = mmcc_pxo_pll8_pll2,
			.num_parents = 3,
			.ops = &clk_rcg_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vfe_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x0104,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vfe_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "vfe_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vfe_csi_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 8,
	.clkr = अणु
		.enable_reg = 0x0104,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.parent_names = (स्थिर अक्षर *[])अणु "vfe_src" पूर्ण,
			.num_parents = 1,
			.name = "vfe_csi_clk",
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gmem_axi_clk = अणु
	.halt_reg = 0x01d8,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(24),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gmem_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ijpeg_axi_clk = अणु
	.hwcg_reg = 0x0018,
	.hwcg_bit = 11,
	.halt_reg = 0x01d8,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ijpeg_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_imem_axi_clk = अणु
	.hwcg_reg = 0x0018,
	.hwcg_bit = 15,
	.halt_reg = 0x01d8,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_imem_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch jpegd_axi_clk = अणु
	.halt_reg = 0x01d8,
	.halt_bit = 5,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "jpegd_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcodec_axi_b_clk = अणु
	.hwcg_reg = 0x0114,
	.hwcg_bit = 22,
	.halt_reg = 0x01e8,
	.halt_bit = 25,
	.clkr = अणु
		.enable_reg = 0x0114,
		.enable_mask = BIT(23),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcodec_axi_b_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcodec_axi_a_clk = अणु
	.hwcg_reg = 0x0114,
	.hwcg_bit = 24,
	.halt_reg = 0x01e8,
	.halt_bit = 26,
	.clkr = अणु
		.enable_reg = 0x0114,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcodec_axi_a_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcodec_axi_clk = अणु
	.hwcg_reg = 0x0018,
	.hwcg_bit = 13,
	.halt_reg = 0x01d8,
	.halt_bit = 3,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcodec_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vfe_axi_clk = अणु
	.halt_reg = 0x01d8,
	.halt_bit = 0,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vfe_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdp_axi_clk = अणु
	.hwcg_reg = 0x0018,
	.hwcg_bit = 16,
	.halt_reg = 0x01d8,
	.halt_bit = 8,
	.clkr = अणु
		.enable_reg = 0x0018,
		.enable_mask = BIT(23),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rot_axi_clk = अणु
	.hwcg_reg = 0x0020,
	.hwcg_bit = 25,
	.halt_reg = 0x01d8,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x0020,
		.enable_mask = BIT(24),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rot_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcap_axi_clk = अणु
	.halt_reg = 0x0240,
	.halt_bit = 20,
	.hwcg_reg = 0x0244,
	.hwcg_bit = 11,
	.clkr = अणु
		.enable_reg = 0x0244,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcap_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vpe_axi_clk = अणु
	.hwcg_reg = 0x0020,
	.hwcg_bit = 27,
	.halt_reg = 0x01d8,
	.halt_bit = 1,
	.clkr = अणु
		.enable_reg = 0x0020,
		.enable_mask = BIT(26),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vpe_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx3d_axi_clk = अणु
	.hwcg_reg = 0x0244,
	.hwcg_bit = 24,
	.halt_reg = 0x0240,
	.halt_bit = 30,
	.clkr = अणु
		.enable_reg = 0x0244,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_axi_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch amp_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 18,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(24),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "amp_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch csi_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 16,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(7),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "csi_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi_m_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 19,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi_m_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi_s_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 20,
	.halt_reg = 0x01dc,
	.halt_bit = 21,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(18),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi_s_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi2_m_ahb_clk = अणु
	.halt_reg = 0x01d8,
	.halt_bit = 18,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_m_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi2_s_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 15,
	.halt_reg = 0x01dc,
	.halt_bit = 20,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(22),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_s_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi1_src = अणु
	.ns_reg = 0x0054,
	.md_reg = 0x0050,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi2_dsi1_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x004c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_src",
			.parent_names = mmcc_pxo_dsi2_dsi1,
			.num_parents = 3,
			.ops = &clk_rcg_bypass2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi1_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x004c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi1_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi2_src = अणु
	.ns_reg = 0x012c,
	.md_reg = 0x00a8,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 24,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 14,
		.pre_भाग_width = 2,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi2_dsi1_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x003c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_src",
			.parent_names = mmcc_pxo_dsi2_dsi1,
			.num_parents = 3,
			.ops = &clk_rcg_bypass2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi2_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 20,
	.clkr = अणु
		.enable_reg = 0x003c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi2_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi1_byte_src = अणु
	.ns_reg = 0x00b0,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi1_dsi2_byte_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x0090,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_byte_src",
			.parent_names = mmcc_pxo_dsi1_dsi2_byte,
			.num_parents = 3,
			.ops = &clk_rcg_bypass2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi1_byte_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 21,
	.clkr = अणु
		.enable_reg = 0x0090,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_byte_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi1_byte_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi2_byte_src = अणु
	.ns_reg = 0x012c,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi1_dsi2_byte_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x0130,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_byte_src",
			.parent_names = mmcc_pxo_dsi1_dsi2_byte,
			.num_parents = 3,
			.ops = &clk_rcg_bypass2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi2_byte_clk = अणु
	.halt_reg = 0x01cc,
	.halt_bit = 20,
	.clkr = अणु
		.enable_reg = 0x00b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_byte_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi2_byte_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi1_esc_src = अणु
	.ns_reg = 0x0011c,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi1_dsi2_byte_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x00cc,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_esc_src",
			.parent_names = mmcc_pxo_dsi1_dsi2_byte,
			.num_parents = 3,
			.ops = &clk_rcg_esc_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi1_esc_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 1,
	.clkr = अणु
		.enable_reg = 0x00cc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_esc_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi1_esc_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi2_esc_src = अणु
	.ns_reg = 0x0150,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi1_dsi2_byte_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x013c,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_esc_src",
			.parent_names = mmcc_pxo_dsi1_dsi2_byte,
			.num_parents = 3,
			.ops = &clk_rcg_esc_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi2_esc_clk = अणु
	.halt_reg = 0x01e8,
	.halt_bit = 3,
	.clkr = अणु
		.enable_reg = 0x013c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_esc_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi2_esc_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi1_pixel_src = अणु
	.ns_reg = 0x0138,
	.md_reg = 0x0134,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi2_dsi1_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x0130,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi1_pixel_src",
			.parent_names = mmcc_pxo_dsi2_dsi1,
			.num_parents = 3,
			.ops = &clk_rcg_pixel_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi1_pixel_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x0130,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_pclk1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi1_pixel_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg dsi2_pixel_src = अणु
	.ns_reg = 0x00e4,
	.md_reg = 0x00b8,
	.mn = अणु
		.mnctr_en_bit = 5,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 6,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 8,
		.width = 8,
	पूर्ण,
	.p = अणु
		.pre_भाग_shअगरt = 12,
		.pre_भाग_width = 4,
	पूर्ण,
	.s = अणु
		.src_sel_shअगरt = 0,
		.parent_map = mmcc_pxo_dsi2_dsi1_map,
	पूर्ण,
	.clkr = अणु
		.enable_reg = 0x0094,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "dsi2_pixel_src",
			.parent_names = mmcc_pxo_dsi2_dsi1,
			.num_parents = 3,
			.ops = &clk_rcg_pixel_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch dsi2_pixel_clk = अणु
	.halt_reg = 0x01d0,
	.halt_bit = 19,
	.clkr = अणु
		.enable_reg = 0x0094,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_pclk2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु "dsi2_pixel_src" पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx2d0_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 28,
	.halt_reg = 0x01dc,
	.halt_bit = 2,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(19),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx2d0_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx2d1_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 29,
	.halt_reg = 0x01dc,
	.halt_bit = 3,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx2d1_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gfx3d_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 27,
	.halt_reg = 0x01dc,
	.halt_bit = 4,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gfx3d_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch hdmi_m_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 21,
	.halt_reg = 0x01dc,
	.halt_bit = 5,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "hdmi_m_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch hdmi_s_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 22,
	.halt_reg = 0x01dc,
	.halt_bit = 6,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "hdmi_s_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch ijpeg_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 9,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ijpeg_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mmss_imem_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 12,
	.halt_reg = 0x01dc,
	.halt_bit = 10,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(6),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mmss_imem_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch jpegd_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 7,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(21),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "jpegd_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch mdp_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 11,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "mdp_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch rot_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 13,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "rot_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch smmu_ahb_clk = अणु
	.hwcg_reg = 0x0008,
	.hwcg_bit = 26,
	.halt_reg = 0x01dc,
	.halt_bit = 22,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "smmu_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch tv_enc_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 23,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(25),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "tv_enc_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcap_ahb_clk = अणु
	.halt_reg = 0x0240,
	.halt_bit = 23,
	.clkr = अणु
		.enable_reg = 0x0248,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcap_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vcodec_ahb_clk = अणु
	.hwcg_reg = 0x0038,
	.hwcg_bit = 26,
	.halt_reg = 0x01dc,
	.halt_bit = 12,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vcodec_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vfe_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 14,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vfe_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch vpe_ahb_clk = अणु
	.halt_reg = 0x01dc,
	.halt_bit = 15,
	.clkr = अणु
		.enable_reg = 0x0008,
		.enable_mask = BIT(16),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "vpe_ahb_clk",
			.ops = &clk_branch_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *mmcc_msm8960_clks[] = अणु
	[TV_ENC_AHB_CLK] = &tv_enc_ahb_clk.clkr,
	[AMP_AHB_CLK] = &amp_ahb_clk.clkr,
	[DSI2_S_AHB_CLK] = &dsi2_s_ahb_clk.clkr,
	[JPEGD_AHB_CLK] = &jpegd_ahb_clk.clkr,
	[GFX2D0_AHB_CLK] = &gfx2d0_ahb_clk.clkr,
	[DSI_S_AHB_CLK] = &dsi_s_ahb_clk.clkr,
	[DSI2_M_AHB_CLK] = &dsi2_m_ahb_clk.clkr,
	[VPE_AHB_CLK] = &vpe_ahb_clk.clkr,
	[SMMU_AHB_CLK] = &smmu_ahb_clk.clkr,
	[HDMI_M_AHB_CLK] = &hdmi_m_ahb_clk.clkr,
	[VFE_AHB_CLK] = &vfe_ahb_clk.clkr,
	[ROT_AHB_CLK] = &rot_ahb_clk.clkr,
	[VCODEC_AHB_CLK] = &vcodec_ahb_clk.clkr,
	[MDP_AHB_CLK] = &mdp_ahb_clk.clkr,
	[DSI_M_AHB_CLK] = &dsi_m_ahb_clk.clkr,
	[CSI_AHB_CLK] = &csi_ahb_clk.clkr,
	[MMSS_IMEM_AHB_CLK] = &mmss_imem_ahb_clk.clkr,
	[IJPEG_AHB_CLK] = &ijpeg_ahb_clk.clkr,
	[HDMI_S_AHB_CLK] = &hdmi_s_ahb_clk.clkr,
	[GFX3D_AHB_CLK] = &gfx3d_ahb_clk.clkr,
	[GFX2D1_AHB_CLK] = &gfx2d1_ahb_clk.clkr,
	[JPEGD_AXI_CLK] = &jpegd_axi_clk.clkr,
	[GMEM_AXI_CLK] = &gmem_axi_clk.clkr,
	[MDP_AXI_CLK] = &mdp_axi_clk.clkr,
	[MMSS_IMEM_AXI_CLK] = &mmss_imem_axi_clk.clkr,
	[IJPEG_AXI_CLK] = &ijpeg_axi_clk.clkr,
	[GFX3D_AXI_CLK] = &gfx3d_axi_clk.clkr,
	[VCODEC_AXI_CLK] = &vcodec_axi_clk.clkr,
	[VFE_AXI_CLK] = &vfe_axi_clk.clkr,
	[VPE_AXI_CLK] = &vpe_axi_clk.clkr,
	[ROT_AXI_CLK] = &rot_axi_clk.clkr,
	[VCODEC_AXI_A_CLK] = &vcodec_axi_a_clk.clkr,
	[VCODEC_AXI_B_CLK] = &vcodec_axi_b_clk.clkr,
	[CSI0_SRC] = &csi0_src.clkr,
	[CSI0_CLK] = &csi0_clk.clkr,
	[CSI0_PHY_CLK] = &csi0_phy_clk.clkr,
	[CSI1_SRC] = &csi1_src.clkr,
	[CSI1_CLK] = &csi1_clk.clkr,
	[CSI1_PHY_CLK] = &csi1_phy_clk.clkr,
	[CSI2_SRC] = &csi2_src.clkr,
	[CSI2_CLK] = &csi2_clk.clkr,
	[CSI2_PHY_CLK] = &csi2_phy_clk.clkr,
	[DSI_SRC] = &dsi1_src.clkr,
	[DSI_CLK] = &dsi1_clk.clkr,
	[CSI_PIX_CLK] = &csi_pix_clk.clkr,
	[CSI_RDI_CLK] = &csi_rdi_clk.clkr,
	[MDP_VSYNC_CLK] = &mdp_vsync_clk.clkr,
	[HDMI_APP_CLK] = &hdmi_app_clk.clkr,
	[CSI_PIX1_CLK] = &csi_pix1_clk.clkr,
	[CSI_RDI2_CLK] = &csi_rdi2_clk.clkr,
	[CSI_RDI1_CLK] = &csi_rdi1_clk.clkr,
	[GFX2D0_SRC] = &gfx2d0_src.clkr,
	[GFX2D0_CLK] = &gfx2d0_clk.clkr,
	[GFX2D1_SRC] = &gfx2d1_src.clkr,
	[GFX2D1_CLK] = &gfx2d1_clk.clkr,
	[GFX3D_SRC] = &gfx3d_src.clkr,
	[GFX3D_CLK] = &gfx3d_clk.clkr,
	[IJPEG_SRC] = &ijpeg_src.clkr,
	[IJPEG_CLK] = &ijpeg_clk.clkr,
	[JPEGD_SRC] = &jpegd_src.clkr,
	[JPEGD_CLK] = &jpegd_clk.clkr,
	[MDP_SRC] = &mdp_src.clkr,
	[MDP_CLK] = &mdp_clk.clkr,
	[MDP_LUT_CLK] = &mdp_lut_clk.clkr,
	[DSI2_PIXEL_SRC] = &dsi2_pixel_src.clkr,
	[DSI2_PIXEL_CLK] = &dsi2_pixel_clk.clkr,
	[DSI2_SRC] = &dsi2_src.clkr,
	[DSI2_CLK] = &dsi2_clk.clkr,
	[DSI1_BYTE_SRC] = &dsi1_byte_src.clkr,
	[DSI1_BYTE_CLK] = &dsi1_byte_clk.clkr,
	[DSI2_BYTE_SRC] = &dsi2_byte_src.clkr,
	[DSI2_BYTE_CLK] = &dsi2_byte_clk.clkr,
	[DSI1_ESC_SRC] = &dsi1_esc_src.clkr,
	[DSI1_ESC_CLK] = &dsi1_esc_clk.clkr,
	[DSI2_ESC_SRC] = &dsi2_esc_src.clkr,
	[DSI2_ESC_CLK] = &dsi2_esc_clk.clkr,
	[ROT_SRC] = &rot_src.clkr,
	[ROT_CLK] = &rot_clk.clkr,
	[TV_ENC_CLK] = &tv_enc_clk.clkr,
	[TV_DAC_CLK] = &tv_dac_clk.clkr,
	[HDMI_TV_CLK] = &hdmi_tv_clk.clkr,
	[MDP_TV_CLK] = &mdp_tv_clk.clkr,
	[TV_SRC] = &tv_src.clkr,
	[VCODEC_SRC] = &vcodec_src.clkr,
	[VCODEC_CLK] = &vcodec_clk.clkr,
	[VFE_SRC] = &vfe_src.clkr,
	[VFE_CLK] = &vfe_clk.clkr,
	[VFE_CSI_CLK] = &vfe_csi_clk.clkr,
	[VPE_SRC] = &vpe_src.clkr,
	[VPE_CLK] = &vpe_clk.clkr,
	[DSI_PIXEL_SRC] = &dsi1_pixel_src.clkr,
	[DSI_PIXEL_CLK] = &dsi1_pixel_clk.clkr,
	[CAMCLK0_SRC] = &camclk0_src.clkr,
	[CAMCLK0_CLK] = &camclk0_clk.clkr,
	[CAMCLK1_SRC] = &camclk1_src.clkr,
	[CAMCLK1_CLK] = &camclk1_clk.clkr,
	[CAMCLK2_SRC] = &camclk2_src.clkr,
	[CAMCLK2_CLK] = &camclk2_clk.clkr,
	[CSIPHYTIMER_SRC] = &csiphyसमयr_src.clkr,
	[CSIPHY2_TIMER_CLK] = &csiphy2_समयr_clk.clkr,
	[CSIPHY1_TIMER_CLK] = &csiphy1_समयr_clk.clkr,
	[CSIPHY0_TIMER_CLK] = &csiphy0_समयr_clk.clkr,
	[PLL2] = &pll2.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map mmcc_msm8960_resets[] = अणु
	[VPE_AXI_RESET] = अणु 0x0208, 15 पूर्ण,
	[IJPEG_AXI_RESET] = अणु 0x0208, 14 पूर्ण,
	[MPD_AXI_RESET] = अणु 0x0208, 13 पूर्ण,
	[VFE_AXI_RESET] = अणु 0x0208, 9 पूर्ण,
	[SP_AXI_RESET] = अणु 0x0208, 8 पूर्ण,
	[VCODEC_AXI_RESET] = अणु 0x0208, 7 पूर्ण,
	[ROT_AXI_RESET] = अणु 0x0208, 6 पूर्ण,
	[VCODEC_AXI_A_RESET] = अणु 0x0208, 5 पूर्ण,
	[VCODEC_AXI_B_RESET] = अणु 0x0208, 4 पूर्ण,
	[FAB_S3_AXI_RESET] = अणु 0x0208, 3 पूर्ण,
	[FAB_S2_AXI_RESET] = अणु 0x0208, 2 पूर्ण,
	[FAB_S1_AXI_RESET] = अणु 0x0208, 1 पूर्ण,
	[FAB_S0_AXI_RESET] = अणु 0x0208 पूर्ण,
	[SMMU_GFX3D_ABH_RESET] = अणु 0x020c, 31 पूर्ण,
	[SMMU_VPE_AHB_RESET] = अणु 0x020c, 30 पूर्ण,
	[SMMU_VFE_AHB_RESET] = अणु 0x020c, 29 पूर्ण,
	[SMMU_ROT_AHB_RESET] = अणु 0x020c, 28 पूर्ण,
	[SMMU_VCODEC_B_AHB_RESET] = अणु 0x020c, 27 पूर्ण,
	[SMMU_VCODEC_A_AHB_RESET] = अणु 0x020c, 26 पूर्ण,
	[SMMU_MDP1_AHB_RESET] = अणु 0x020c, 25 पूर्ण,
	[SMMU_MDP0_AHB_RESET] = अणु 0x020c, 24 पूर्ण,
	[SMMU_JPEGD_AHB_RESET] = अणु 0x020c, 23 पूर्ण,
	[SMMU_IJPEG_AHB_RESET] = अणु 0x020c, 22 पूर्ण,
	[SMMU_GFX2D0_AHB_RESET] = अणु 0x020c, 21 पूर्ण,
	[SMMU_GFX2D1_AHB_RESET] = अणु 0x020c, 20 पूर्ण,
	[APU_AHB_RESET] = अणु 0x020c, 18 पूर्ण,
	[CSI_AHB_RESET] = अणु 0x020c, 17 पूर्ण,
	[TV_ENC_AHB_RESET] = अणु 0x020c, 15 पूर्ण,
	[VPE_AHB_RESET] = अणु 0x020c, 14 पूर्ण,
	[FABRIC_AHB_RESET] = अणु 0x020c, 13 पूर्ण,
	[GFX2D0_AHB_RESET] = अणु 0x020c, 12 पूर्ण,
	[GFX2D1_AHB_RESET] = अणु 0x020c, 11 पूर्ण,
	[GFX3D_AHB_RESET] = अणु 0x020c, 10 पूर्ण,
	[HDMI_AHB_RESET] = अणु 0x020c, 9 पूर्ण,
	[MSSS_IMEM_AHB_RESET] = अणु 0x020c, 8 पूर्ण,
	[IJPEG_AHB_RESET] = अणु 0x020c, 7 पूर्ण,
	[DSI_M_AHB_RESET] = अणु 0x020c, 6 पूर्ण,
	[DSI_S_AHB_RESET] = अणु 0x020c, 5 पूर्ण,
	[JPEGD_AHB_RESET] = अणु 0x020c, 4 पूर्ण,
	[MDP_AHB_RESET] = अणु 0x020c, 3 पूर्ण,
	[ROT_AHB_RESET] = अणु 0x020c, 2 पूर्ण,
	[VCODEC_AHB_RESET] = अणु 0x020c, 1 पूर्ण,
	[VFE_AHB_RESET] = अणु 0x020c, 0 पूर्ण,
	[DSI2_M_AHB_RESET] = अणु 0x0210, 31 पूर्ण,
	[DSI2_S_AHB_RESET] = अणु 0x0210, 30 पूर्ण,
	[CSIPHY2_RESET] = अणु 0x0210, 29 पूर्ण,
	[CSI_PIX1_RESET] = अणु 0x0210, 28 पूर्ण,
	[CSIPHY0_RESET] = अणु 0x0210, 27 पूर्ण,
	[CSIPHY1_RESET] = अणु 0x0210, 26 पूर्ण,
	[DSI2_RESET] = अणु 0x0210, 25 पूर्ण,
	[VFE_CSI_RESET] = अणु 0x0210, 24 पूर्ण,
	[MDP_RESET] = अणु 0x0210, 21 पूर्ण,
	[AMP_RESET] = अणु 0x0210, 20 पूर्ण,
	[JPEGD_RESET] = अणु 0x0210, 19 पूर्ण,
	[CSI1_RESET] = अणु 0x0210, 18 पूर्ण,
	[VPE_RESET] = अणु 0x0210, 17 पूर्ण,
	[MMSS_FABRIC_RESET] = अणु 0x0210, 16 पूर्ण,
	[VFE_RESET] = अणु 0x0210, 15 पूर्ण,
	[GFX2D0_RESET] = अणु 0x0210, 14 पूर्ण,
	[GFX2D1_RESET] = अणु 0x0210, 13 पूर्ण,
	[GFX3D_RESET] = अणु 0x0210, 12 पूर्ण,
	[HDMI_RESET] = अणु 0x0210, 11 पूर्ण,
	[MMSS_IMEM_RESET] = अणु 0x0210, 10 पूर्ण,
	[IJPEG_RESET] = अणु 0x0210, 9 पूर्ण,
	[CSI0_RESET] = अणु 0x0210, 8 पूर्ण,
	[DSI_RESET] = अणु 0x0210, 7 पूर्ण,
	[VCODEC_RESET] = अणु 0x0210, 6 पूर्ण,
	[MDP_TV_RESET] = अणु 0x0210, 4 पूर्ण,
	[MDP_VSYNC_RESET] = अणु 0x0210, 3 पूर्ण,
	[ROT_RESET] = अणु 0x0210, 2 पूर्ण,
	[TV_HDMI_RESET] = अणु 0x0210, 1 पूर्ण,
	[TV_ENC_RESET] = अणु 0x0210 पूर्ण,
	[CSI2_RESET] = अणु 0x0214, 2 पूर्ण,
	[CSI_RDI1_RESET] = अणु 0x0214, 1 पूर्ण,
	[CSI_RDI2_RESET] = अणु 0x0214 पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *mmcc_apq8064_clks[] = अणु
	[AMP_AHB_CLK] = &amp_ahb_clk.clkr,
	[DSI2_S_AHB_CLK] = &dsi2_s_ahb_clk.clkr,
	[JPEGD_AHB_CLK] = &jpegd_ahb_clk.clkr,
	[DSI_S_AHB_CLK] = &dsi_s_ahb_clk.clkr,
	[DSI2_M_AHB_CLK] = &dsi2_m_ahb_clk.clkr,
	[VPE_AHB_CLK] = &vpe_ahb_clk.clkr,
	[SMMU_AHB_CLK] = &smmu_ahb_clk.clkr,
	[HDMI_M_AHB_CLK] = &hdmi_m_ahb_clk.clkr,
	[VFE_AHB_CLK] = &vfe_ahb_clk.clkr,
	[ROT_AHB_CLK] = &rot_ahb_clk.clkr,
	[VCODEC_AHB_CLK] = &vcodec_ahb_clk.clkr,
	[MDP_AHB_CLK] = &mdp_ahb_clk.clkr,
	[DSI_M_AHB_CLK] = &dsi_m_ahb_clk.clkr,
	[CSI_AHB_CLK] = &csi_ahb_clk.clkr,
	[MMSS_IMEM_AHB_CLK] = &mmss_imem_ahb_clk.clkr,
	[IJPEG_AHB_CLK] = &ijpeg_ahb_clk.clkr,
	[HDMI_S_AHB_CLK] = &hdmi_s_ahb_clk.clkr,
	[GFX3D_AHB_CLK] = &gfx3d_ahb_clk.clkr,
	[JPEGD_AXI_CLK] = &jpegd_axi_clk.clkr,
	[GMEM_AXI_CLK] = &gmem_axi_clk.clkr,
	[MDP_AXI_CLK] = &mdp_axi_clk.clkr,
	[MMSS_IMEM_AXI_CLK] = &mmss_imem_axi_clk.clkr,
	[IJPEG_AXI_CLK] = &ijpeg_axi_clk.clkr,
	[GFX3D_AXI_CLK] = &gfx3d_axi_clk.clkr,
	[VCODEC_AXI_CLK] = &vcodec_axi_clk.clkr,
	[VFE_AXI_CLK] = &vfe_axi_clk.clkr,
	[VPE_AXI_CLK] = &vpe_axi_clk.clkr,
	[ROT_AXI_CLK] = &rot_axi_clk.clkr,
	[VCODEC_AXI_A_CLK] = &vcodec_axi_a_clk.clkr,
	[VCODEC_AXI_B_CLK] = &vcodec_axi_b_clk.clkr,
	[CSI0_SRC] = &csi0_src.clkr,
	[CSI0_CLK] = &csi0_clk.clkr,
	[CSI0_PHY_CLK] = &csi0_phy_clk.clkr,
	[CSI1_SRC] = &csi1_src.clkr,
	[CSI1_CLK] = &csi1_clk.clkr,
	[CSI1_PHY_CLK] = &csi1_phy_clk.clkr,
	[CSI2_SRC] = &csi2_src.clkr,
	[CSI2_CLK] = &csi2_clk.clkr,
	[CSI2_PHY_CLK] = &csi2_phy_clk.clkr,
	[DSI_SRC] = &dsi1_src.clkr,
	[DSI_CLK] = &dsi1_clk.clkr,
	[CSI_PIX_CLK] = &csi_pix_clk.clkr,
	[CSI_RDI_CLK] = &csi_rdi_clk.clkr,
	[MDP_VSYNC_CLK] = &mdp_vsync_clk.clkr,
	[HDMI_APP_CLK] = &hdmi_app_clk.clkr,
	[CSI_PIX1_CLK] = &csi_pix1_clk.clkr,
	[CSI_RDI2_CLK] = &csi_rdi2_clk.clkr,
	[CSI_RDI1_CLK] = &csi_rdi1_clk.clkr,
	[GFX3D_SRC] = &gfx3d_src.clkr,
	[GFX3D_CLK] = &gfx3d_clk.clkr,
	[IJPEG_SRC] = &ijpeg_src.clkr,
	[IJPEG_CLK] = &ijpeg_clk.clkr,
	[JPEGD_SRC] = &jpegd_src.clkr,
	[JPEGD_CLK] = &jpegd_clk.clkr,
	[MDP_SRC] = &mdp_src.clkr,
	[MDP_CLK] = &mdp_clk.clkr,
	[MDP_LUT_CLK] = &mdp_lut_clk.clkr,
	[DSI2_PIXEL_SRC] = &dsi2_pixel_src.clkr,
	[DSI2_PIXEL_CLK] = &dsi2_pixel_clk.clkr,
	[DSI2_SRC] = &dsi2_src.clkr,
	[DSI2_CLK] = &dsi2_clk.clkr,
	[DSI1_BYTE_SRC] = &dsi1_byte_src.clkr,
	[DSI1_BYTE_CLK] = &dsi1_byte_clk.clkr,
	[DSI2_BYTE_SRC] = &dsi2_byte_src.clkr,
	[DSI2_BYTE_CLK] = &dsi2_byte_clk.clkr,
	[DSI1_ESC_SRC] = &dsi1_esc_src.clkr,
	[DSI1_ESC_CLK] = &dsi1_esc_clk.clkr,
	[DSI2_ESC_SRC] = &dsi2_esc_src.clkr,
	[DSI2_ESC_CLK] = &dsi2_esc_clk.clkr,
	[ROT_SRC] = &rot_src.clkr,
	[ROT_CLK] = &rot_clk.clkr,
	[TV_DAC_CLK] = &tv_dac_clk.clkr,
	[HDMI_TV_CLK] = &hdmi_tv_clk.clkr,
	[MDP_TV_CLK] = &mdp_tv_clk.clkr,
	[TV_SRC] = &tv_src.clkr,
	[VCODEC_SRC] = &vcodec_src.clkr,
	[VCODEC_CLK] = &vcodec_clk.clkr,
	[VFE_SRC] = &vfe_src.clkr,
	[VFE_CLK] = &vfe_clk.clkr,
	[VFE_CSI_CLK] = &vfe_csi_clk.clkr,
	[VPE_SRC] = &vpe_src.clkr,
	[VPE_CLK] = &vpe_clk.clkr,
	[DSI_PIXEL_SRC] = &dsi1_pixel_src.clkr,
	[DSI_PIXEL_CLK] = &dsi1_pixel_clk.clkr,
	[CAMCLK0_SRC] = &camclk0_src.clkr,
	[CAMCLK0_CLK] = &camclk0_clk.clkr,
	[CAMCLK1_SRC] = &camclk1_src.clkr,
	[CAMCLK1_CLK] = &camclk1_clk.clkr,
	[CAMCLK2_SRC] = &camclk2_src.clkr,
	[CAMCLK2_CLK] = &camclk2_clk.clkr,
	[CSIPHYTIMER_SRC] = &csiphyसमयr_src.clkr,
	[CSIPHY2_TIMER_CLK] = &csiphy2_समयr_clk.clkr,
	[CSIPHY1_TIMER_CLK] = &csiphy1_समयr_clk.clkr,
	[CSIPHY0_TIMER_CLK] = &csiphy0_समयr_clk.clkr,
	[PLL2] = &pll2.clkr,
	[RGB_TV_CLK] = &rgb_tv_clk.clkr,
	[NPL_TV_CLK] = &npl_tv_clk.clkr,
	[VCAP_AHB_CLK] = &vcap_ahb_clk.clkr,
	[VCAP_AXI_CLK] = &vcap_axi_clk.clkr,
	[VCAP_SRC] = &vcap_src.clkr,
	[VCAP_CLK] = &vcap_clk.clkr,
	[VCAP_NPL_CLK] = &vcap_npl_clk.clkr,
	[PLL15] = &pll15.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map mmcc_apq8064_resets[] = अणु
	[GFX3D_AXI_RESET] = अणु 0x0208, 17 पूर्ण,
	[VCAP_AXI_RESET] = अणु 0x0208, 16 पूर्ण,
	[VPE_AXI_RESET] = अणु 0x0208, 15 पूर्ण,
	[IJPEG_AXI_RESET] = अणु 0x0208, 14 पूर्ण,
	[MPD_AXI_RESET] = अणु 0x0208, 13 पूर्ण,
	[VFE_AXI_RESET] = अणु 0x0208, 9 पूर्ण,
	[SP_AXI_RESET] = अणु 0x0208, 8 पूर्ण,
	[VCODEC_AXI_RESET] = अणु 0x0208, 7 पूर्ण,
	[ROT_AXI_RESET] = अणु 0x0208, 6 पूर्ण,
	[VCODEC_AXI_A_RESET] = अणु 0x0208, 5 पूर्ण,
	[VCODEC_AXI_B_RESET] = अणु 0x0208, 4 पूर्ण,
	[FAB_S3_AXI_RESET] = अणु 0x0208, 3 पूर्ण,
	[FAB_S2_AXI_RESET] = अणु 0x0208, 2 पूर्ण,
	[FAB_S1_AXI_RESET] = अणु 0x0208, 1 पूर्ण,
	[FAB_S0_AXI_RESET] = अणु 0x0208 पूर्ण,
	[SMMU_GFX3D_ABH_RESET] = अणु 0x020c, 31 पूर्ण,
	[SMMU_VPE_AHB_RESET] = अणु 0x020c, 30 पूर्ण,
	[SMMU_VFE_AHB_RESET] = अणु 0x020c, 29 पूर्ण,
	[SMMU_ROT_AHB_RESET] = अणु 0x020c, 28 पूर्ण,
	[SMMU_VCODEC_B_AHB_RESET] = अणु 0x020c, 27 पूर्ण,
	[SMMU_VCODEC_A_AHB_RESET] = अणु 0x020c, 26 पूर्ण,
	[SMMU_MDP1_AHB_RESET] = अणु 0x020c, 25 पूर्ण,
	[SMMU_MDP0_AHB_RESET] = अणु 0x020c, 24 पूर्ण,
	[SMMU_JPEGD_AHB_RESET] = अणु 0x020c, 23 पूर्ण,
	[SMMU_IJPEG_AHB_RESET] = अणु 0x020c, 22 पूर्ण,
	[APU_AHB_RESET] = अणु 0x020c, 18 पूर्ण,
	[CSI_AHB_RESET] = अणु 0x020c, 17 पूर्ण,
	[TV_ENC_AHB_RESET] = अणु 0x020c, 15 पूर्ण,
	[VPE_AHB_RESET] = अणु 0x020c, 14 पूर्ण,
	[FABRIC_AHB_RESET] = अणु 0x020c, 13 पूर्ण,
	[GFX3D_AHB_RESET] = अणु 0x020c, 10 पूर्ण,
	[HDMI_AHB_RESET] = अणु 0x020c, 9 पूर्ण,
	[MSSS_IMEM_AHB_RESET] = अणु 0x020c, 8 पूर्ण,
	[IJPEG_AHB_RESET] = अणु 0x020c, 7 पूर्ण,
	[DSI_M_AHB_RESET] = अणु 0x020c, 6 पूर्ण,
	[DSI_S_AHB_RESET] = अणु 0x020c, 5 पूर्ण,
	[JPEGD_AHB_RESET] = अणु 0x020c, 4 पूर्ण,
	[MDP_AHB_RESET] = अणु 0x020c, 3 पूर्ण,
	[ROT_AHB_RESET] = अणु 0x020c, 2 पूर्ण,
	[VCODEC_AHB_RESET] = अणु 0x020c, 1 पूर्ण,
	[VFE_AHB_RESET] = अणु 0x020c, 0 पूर्ण,
	[SMMU_VCAP_AHB_RESET] = अणु 0x0200, 3 पूर्ण,
	[VCAP_AHB_RESET] = अणु 0x0200, 2 पूर्ण,
	[DSI2_M_AHB_RESET] = अणु 0x0200, 1 पूर्ण,
	[DSI2_S_AHB_RESET] = अणु 0x0200, 0 पूर्ण,
	[CSIPHY2_RESET] = अणु 0x0210, 31 पूर्ण,
	[CSI_PIX1_RESET] = अणु 0x0210, 30 पूर्ण,
	[CSIPHY0_RESET] = अणु 0x0210, 29 पूर्ण,
	[CSIPHY1_RESET] = अणु 0x0210, 28 पूर्ण,
	[CSI_RDI_RESET] = अणु 0x0210, 27 पूर्ण,
	[CSI_PIX_RESET] = अणु 0x0210, 26 पूर्ण,
	[DSI2_RESET] = अणु 0x0210, 25 पूर्ण,
	[VFE_CSI_RESET] = अणु 0x0210, 24 पूर्ण,
	[MDP_RESET] = अणु 0x0210, 21 पूर्ण,
	[AMP_RESET] = अणु 0x0210, 20 पूर्ण,
	[JPEGD_RESET] = अणु 0x0210, 19 पूर्ण,
	[CSI1_RESET] = अणु 0x0210, 18 पूर्ण,
	[VPE_RESET] = अणु 0x0210, 17 पूर्ण,
	[MMSS_FABRIC_RESET] = अणु 0x0210, 16 पूर्ण,
	[VFE_RESET] = अणु 0x0210, 15 पूर्ण,
	[GFX3D_RESET] = अणु 0x0210, 12 पूर्ण,
	[HDMI_RESET] = अणु 0x0210, 11 पूर्ण,
	[MMSS_IMEM_RESET] = अणु 0x0210, 10 पूर्ण,
	[IJPEG_RESET] = अणु 0x0210, 9 पूर्ण,
	[CSI0_RESET] = अणु 0x0210, 8 पूर्ण,
	[DSI_RESET] = अणु 0x0210, 7 पूर्ण,
	[VCODEC_RESET] = अणु 0x0210, 6 पूर्ण,
	[MDP_TV_RESET] = अणु 0x0210, 4 पूर्ण,
	[MDP_VSYNC_RESET] = अणु 0x0210, 3 पूर्ण,
	[ROT_RESET] = अणु 0x0210, 2 पूर्ण,
	[TV_HDMI_RESET] = अणु 0x0210, 1 पूर्ण,
	[VCAP_NPL_RESET] = अणु 0x0214, 4 पूर्ण,
	[VCAP_RESET] = अणु 0x0214, 3 पूर्ण,
	[CSI2_RESET] = अणु 0x0214, 2 पूर्ण,
	[CSI_RDI1_RESET] = अणु 0x0214, 1 पूर्ण,
	[CSI_RDI2_RESET] = अणु 0x0214 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mmcc_msm8960_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x334,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mmcc_apq8064_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x350,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc mmcc_msm8960_desc = अणु
	.config = &mmcc_msm8960_regmap_config,
	.clks = mmcc_msm8960_clks,
	.num_clks = ARRAY_SIZE(mmcc_msm8960_clks),
	.resets = mmcc_msm8960_resets,
	.num_resets = ARRAY_SIZE(mmcc_msm8960_resets),
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc mmcc_apq8064_desc = अणु
	.config = &mmcc_apq8064_regmap_config,
	.clks = mmcc_apq8064_clks,
	.num_clks = ARRAY_SIZE(mmcc_apq8064_clks),
	.resets = mmcc_apq8064_resets,
	.num_resets = ARRAY_SIZE(mmcc_apq8064_resets),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmcc_msm8960_match_table[] = अणु
	अणु .compatible = "qcom,mmcc-msm8960", .data = &mmcc_msm8960_desc पूर्ण,
	अणु .compatible = "qcom,mmcc-apq8064", .data = &mmcc_apq8064_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmcc_msm8960_match_table);

अटल पूर्णांक mmcc_msm8960_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा regmap *regmap;
	bool is_8064;
	काष्ठा device *dev = &pdev->dev;

	match = of_match_device(mmcc_msm8960_match_table, dev);
	अगर (!match)
		वापस -EINVAL;

	is_8064 = of_device_is_compatible(dev->of_node, "qcom,mmcc-apq8064");
	अगर (is_8064) अणु
		gfx3d_src.freq_tbl = clk_tbl_gfx3d_8064;
		gfx3d_src.clkr.hw.init = &gfx3d_8064_init;
		gfx3d_src.s[0].parent_map = mmcc_pxo_pll8_pll2_pll15_map;
		gfx3d_src.s[1].parent_map = mmcc_pxo_pll8_pll2_pll15_map;
	पूर्ण

	regmap = qcom_cc_map(pdev, match->data);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	clk_pll_configure_sr(&pll15, regmap, &pll15_config, false);

	वापस qcom_cc_really_probe(pdev, match->data, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver mmcc_msm8960_driver = अणु
	.probe		= mmcc_msm8960_probe,
	.driver		= अणु
		.name	= "mmcc-msm8960",
		.of_match_table = mmcc_msm8960_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mmcc_msm8960_driver);

MODULE_DESCRIPTION("QCOM MMCC MSM8960 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mmcc-msm8960");
