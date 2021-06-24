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

#समावेश <dt-bindings/घड़ी/qcom,lcc-ipq806x.h>

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

अटल स्थिर काष्ठा pll_config pll4_config = अणु
	.l = 0xf,
	.m = 0x91,
	.n = 0xc7,
	.vco_val = 0x0,
	.vco_mask = BIT(17) | BIT(16),
	.pre_भाग_val = 0x0,
	.pre_भाग_mask = BIT(19),
	.post_भाग_val = 0x0,
	.post_भाग_mask = BIT(21) | BIT(20),
	.mn_ena_mask = BIT(22),
	.मुख्य_output_mask = BIT(23),
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

अटल काष्ठा freq_tbl clk_tbl_aअगर_mi2s[] = अणु
	अणु  1024000, P_PLL4, 4,  1,  96 पूर्ण,
	अणु  1411200, P_PLL4, 4,  2, 139 पूर्ण,
	अणु  1536000, P_PLL4, 4,  1,  64 पूर्ण,
	अणु  2048000, P_PLL4, 4,  1,  48 पूर्ण,
	अणु  2116800, P_PLL4, 4,  2,  93 पूर्ण,
	अणु  2304000, P_PLL4, 4,  2,  85 पूर्ण,
	अणु  2822400, P_PLL4, 4,  6, 209 पूर्ण,
	अणु  3072000, P_PLL4, 4,  1,  32 पूर्ण,
	अणु  3175200, P_PLL4, 4,  1,  31 पूर्ण,
	अणु  4096000, P_PLL4, 4,  1,  24 पूर्ण,
	अणु  4233600, P_PLL4, 4,  9, 209 पूर्ण,
	अणु  4608000, P_PLL4, 4,  3,  64 पूर्ण,
	अणु  5644800, P_PLL4, 4, 12, 209 पूर्ण,
	अणु  6144000, P_PLL4, 4,  1,  16 पूर्ण,
	अणु  6350400, P_PLL4, 4,  2,  31 पूर्ण,
	अणु  8192000, P_PLL4, 4,  1,  12 पूर्ण,
	अणु  8467200, P_PLL4, 4, 18, 209 पूर्ण,
	अणु  9216000, P_PLL4, 4,  3,  32 पूर्ण,
	अणु 11289600, P_PLL4, 4, 24, 209 पूर्ण,
	अणु 12288000, P_PLL4, 4,  1,   8 पूर्ण,
	अणु 12700800, P_PLL4, 4, 27, 209 पूर्ण,
	अणु 13824000, P_PLL4, 4,  9,  64 पूर्ण,
	अणु 16384000, P_PLL4, 4,  1,   6 पूर्ण,
	अणु 16934400, P_PLL4, 4, 41, 238 पूर्ण,
	अणु 18432000, P_PLL4, 4,  3,  16 पूर्ण,
	अणु 22579200, P_PLL4, 2, 24, 209 पूर्ण,
	अणु 24576000, P_PLL4, 4,  1,   4 पूर्ण,
	अणु 27648000, P_PLL4, 4,  9,  32 पूर्ण,
	अणु 33868800, P_PLL4, 4, 41, 119 पूर्ण,
	अणु 36864000, P_PLL4, 4,  3,   8 पूर्ण,
	अणु 45158400, P_PLL4, 1, 24, 209 पूर्ण,
	अणु 49152000, P_PLL4, 4,  1,   2 पूर्ण,
	अणु 50803200, P_PLL4, 1, 27, 209 पूर्ण,
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
	.freq_tbl = clk_tbl_aअगर_mi2s,
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

अटल काष्ठा freq_tbl clk_tbl_pcm[] = अणु
	अणु   64000, P_PLL4, 4, 1, 1536 पूर्ण,
	अणु  128000, P_PLL4, 4, 1,  768 पूर्ण,
	अणु  256000, P_PLL4, 4, 1,  384 पूर्ण,
	अणु  512000, P_PLL4, 4, 1,  192 पूर्ण,
	अणु 1024000, P_PLL4, 4, 1,   96 पूर्ण,
	अणु 2048000, P_PLL4, 4, 1,   48 पूर्ण,
	अणु पूर्ण,
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
	.freq_tbl = clk_tbl_pcm,
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

अटल काष्ठा freq_tbl clk_tbl_aअगर_osr[] = अणु
	अणु  2822400, P_PLL4, 1, 147, 20480 पूर्ण,
	अणु  4096000, P_PLL4, 1,   1,    96 पूर्ण,
	अणु  5644800, P_PLL4, 1, 147, 10240 पूर्ण,
	अणु  6144000, P_PLL4, 1,   1,    64 पूर्ण,
	अणु 11289600, P_PLL4, 1, 147,  5120 पूर्ण,
	अणु 12288000, P_PLL4, 1,   1,    32 पूर्ण,
	अणु 22579200, P_PLL4, 1, 147,  2560 पूर्ण,
	अणु 24576000, P_PLL4, 1,   1,    16 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg spdअगर_src = अणु
	.ns_reg = 0xcc,
	.md_reg = 0xd0,
	.mn = अणु
		.mnctr_en_bit = 8,
		.mnctr_reset_bit = 7,
		.mnctr_mode_shअगरt = 5,
		.n_val_shअगरt = 16,
		.m_val_shअगरt = 16,
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
	.freq_tbl = clk_tbl_aअगर_osr,
	.clkr = अणु
		.enable_reg = 0xcc,
		.enable_mask = BIT(9),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "spdif_src",
			.parent_names = lcc_pxo_pll4,
			.num_parents = 2,
			.ops = &clk_rcg_ops,
			.flags = CLK_SET_RATE_GATE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lcc_spdअगर_parents[] = अणु
	"spdif_src",
पूर्ण;

अटल काष्ठा clk_branch spdअगर_clk = अणु
	.halt_reg = 0xd4,
	.halt_bit = 1,
	.halt_check = BRANCH_HALT_ENABLE,
	.clkr = अणु
		.enable_reg = 0xcc,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "spdif_clk",
			.parent_names = lcc_spdअगर_parents,
			.num_parents = 1,
			.ops = &clk_branch_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl clk_tbl_ahbix[] = अणु
	अणु 131072000, P_PLL4, 1, 1, 3 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg ahbix_clk = अणु
	.ns_reg = 0x38,
	.md_reg = 0x3c,
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
	.freq_tbl = clk_tbl_ahbix,
	.clkr = अणु
		.enable_reg = 0x38,
		.enable_mask = BIT(11),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ahbix",
			.parent_names = lcc_pxo_pll4,
			.num_parents = 2,
			.ops = &clk_rcg_lcc_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *lcc_ipq806x_clks[] = अणु
	[PLL4] = &pll4.clkr,
	[MI2S_OSR_SRC] = &mi2s_osr_src.clkr,
	[MI2S_OSR_CLK] = &mi2s_osr_clk.clkr,
	[MI2S_DIV_CLK] = &mi2s_भाग_clk.clkr,
	[MI2S_BIT_DIV_CLK] = &mi2s_bit_भाग_clk.clkr,
	[MI2S_BIT_CLK] = &mi2s_bit_clk.clkr,
	[PCM_SRC] = &pcm_src.clkr,
	[PCM_CLK_OUT] = &pcm_clk_out.clkr,
	[PCM_CLK] = &pcm_clk.clkr,
	[SPDIF_SRC] = &spdअगर_src.clkr,
	[SPDIF_CLK] = &spdअगर_clk.clkr,
	[AHBIX_CLK] = &ahbix_clk.clkr,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lcc_ipq806x_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xfc,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc lcc_ipq806x_desc = अणु
	.config = &lcc_ipq806x_regmap_config,
	.clks = lcc_ipq806x_clks,
	.num_clks = ARRAY_SIZE(lcc_ipq806x_clks),
पूर्ण;

अटल स्थिर काष्ठा of_device_id lcc_ipq806x_match_table[] = अणु
	अणु .compatible = "qcom,lcc-ipq8064" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lcc_ipq806x_match_table);

अटल पूर्णांक lcc_ipq806x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 val;
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, &lcc_ipq806x_desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Configure the rate of PLL4 अगर the bootloader hasn't alपढ़ोy */
	regmap_पढ़ो(regmap, 0x0, &val);
	अगर (!val)
		clk_pll_configure_sr(&pll4, regmap, &pll4_config, true);
	/* Enable PLL4 source on the LPASS Primary PLL Mux */
	regmap_ग_लिखो(regmap, 0xc4, 0x1);

	वापस qcom_cc_really_probe(pdev, &lcc_ipq806x_desc, regmap);
पूर्ण

अटल काष्ठा platक्रमm_driver lcc_ipq806x_driver = अणु
	.probe		= lcc_ipq806x_probe,
	.driver		= अणु
		.name	= "lcc-ipq806x",
		.of_match_table = lcc_ipq806x_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lcc_ipq806x_driver);

MODULE_DESCRIPTION("QCOM LCC IPQ806x Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lcc-ipq806x");
