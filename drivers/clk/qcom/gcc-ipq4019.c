<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/math64.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-ipq4019.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"
#समावेश "clk-regmap-divider.h"

#घोषणा to_clk_regmap_भाग(_hw) container_of(to_clk_regmap(_hw),\
					काष्ठा clk_regmap_भाग, clkr)

#घोषणा to_clk_fepll(_hw) container_of(to_clk_regmap_भाग(_hw),\
						काष्ठा clk_fepll, cभाग)

क्रमागत अणु
	P_XO,
	P_FEPLL200,
	P_FEPLL500,
	P_DDRPLL,
	P_FEPLLWCSS2G,
	P_FEPLLWCSS5G,
	P_FEPLL125DLY,
	P_DDRPLLAPSS,
पूर्ण;

/*
 * काष्ठा clk_fepll_vco - vco feedback भागider corresponds क्रम FEPLL घड़ीs
 * @fdbkभाग_shअगरt: lowest bit क्रम FDBKDIV
 * @fdbkभाग_width: number of bits in FDBKDIV
 * @refclkभाग_shअगरt: lowest bit क्रम REFCLKDIV
 * @refclkभाग_width: number of bits in REFCLKDIV
 * @reg: PLL_DIV रेजिस्टर address
 */
काष्ठा clk_fepll_vco अणु
	u32 fdbkभाग_shअगरt;
	u32 fdbkभाग_width;
	u32 refclkभाग_shअगरt;
	u32 refclkभाग_width;
	u32 reg;
पूर्ण;

/*
 * काष्ठा clk_fepll - clk भागider corresponds to FEPLL घड़ीs
 * @fixed_भाग: fixed भागider value अगर भागider is fixed
 * @parent_map: map from software's parent index to hardware's src_sel field
 * @cभाग: भागider values क्रम PLL_DIV
 * @pll_vco: vco feedback भागider
 * @भाग_प्रकारable: mapping क्रम actual भागider value to रेजिस्टर भागider value
 *             in हाल of non fixed भागider
 * @freq_tbl: frequency table
 */
काष्ठा clk_fepll अणु
	u32 fixed_भाग;
	स्थिर u8 *parent_map;
	काष्ठा clk_regmap_भाग cभाग;
	स्थिर काष्ठा clk_fepll_vco *pll_vco;
	स्थिर काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
	स्थिर काष्ठा freq_tbl *freq_tbl;
पूर्ण;

अटल काष्ठा parent_map gcc_xo_200_500_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_FEPLL200, 1 पूर्ण,
	अणु P_FEPLL500, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_200_500[] = अणु
	"xo",
	"fepll200",
	"fepll500",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_200_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_FEPLL200, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_200[] = अणु
	"xo",
	"fepll200",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_200_spi_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_FEPLL200, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_200_spi[] = अणु
	"xo",
	"fepll200",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_sdcc1_500_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_DDRPLL, 1 पूर्ण,
	अणु  P_FEPLL500, 2 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_sdcc1_500[] = अणु
	"xo",
	"ddrpllsdcc",
	"fepll500",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_wcss2g_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_FEPLLWCSS2G, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_wcss2g[] = अणु
	"xo",
	"fepllwcss2g",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_wcss5g_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_FEPLLWCSS5G, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_wcss5g[] = अणु
	"xo",
	"fepllwcss5g",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_125_dly_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_FEPLL125DLY, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_125_dly[] = अणु
	"xo",
	"fepll125dly",
पूर्ण;

अटल काष्ठा parent_map gcc_xo_ddr_500_200_map[] = अणु
	अणु  P_XO, 0 पूर्ण,
	अणु  P_FEPLL200, 3 पूर्ण,
	अणु  P_FEPLL500, 2 पूर्ण,
	अणु  P_DDRPLLAPSS, 1 पूर्ण,
पूर्ण;

/*
 * Contains index क्रम safe घड़ी during APSS freq change.
 * fepll500 is being used as safe घड़ी so initialize it
 * with its index in parents list gcc_xo_ddr_500_200.
 */
अटल स्थिर पूर्णांक gcc_ipq4019_cpu_safe_parent = 2;
अटल स्थिर अक्षर * स्थिर gcc_xo_ddr_500_200[] = अणु
	"xo",
	"fepll200",
	"fepll500",
	"ddrpllapss",
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_audio_pwm_clk[] = अणु
	F(48000000, P_XO, 1, 0, 0),
	F(200000000, P_FEPLL200, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 audio_clk_src = अणु
	.cmd_rcgr = 0x1b000,
	.hid_width = 5,
	.parent_map = gcc_xo_200_map,
	.freq_tbl = ftbl_gcc_audio_pwm_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "audio_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,

	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_audio_ahb_clk = अणु
	.halt_reg = 0x1b010,
	.clkr = अणु
		.enable_reg = 0x1b010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_audio_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.flags = CLK_SET_RATE_PARENT,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_audio_pwm_clk = अणु
	.halt_reg = 0x1b00C,
	.clkr = अणु
		.enable_reg = 0x1b00C,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_audio_pwm_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"audio_clk_src",
			पूर्ण,
			.flags = CLK_SET_RATE_PARENT,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_qup1_2_i2c_apps_clk[] = अणु
	F(19050000, P_FEPLL200, 10.5, 1, 1),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x200c,
	.hid_width = 5,
	.parent_map = gcc_xo_200_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_2_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_i2c_apps_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x2008,
	.clkr = अणु
		.enable_reg = 0x2008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup1_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x3000,
	.hid_width = 5,
	.parent_map = gcc_xo_200_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_2_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup2_i2c_apps_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_i2c_apps_clk = अणु
	.halt_reg = 0x3010,
	.clkr = अणु
		.enable_reg = 0x3010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup2_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_qup1_2_spi_apps_clk[] = अणु
	F(960000, P_XO, 12, 1, 4),
	F(4800000, P_XO, 1, 1, 10),
	F(9600000, P_XO, 1, 1, 5),
	F(15000000, P_XO, 1, 1, 3),
	F(19200000, P_XO, 1, 2, 5),
	F(24000000, P_XO, 1, 1, 2),
	F(48000000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x2024,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_200_spi_map,
	.freq_tbl = ftbl_gcc_blsp1_qup1_2_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_spi_apps_clk_src",
		.parent_names = gcc_xo_200_spi,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_spi_apps_clk = अणु
	.halt_reg = 0x2004,
	.clkr = अणु
		.enable_reg = 0x2004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup1_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x3014,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_blsp1_qup1_2_spi_apps_clk,
	.parent_map = gcc_xo_200_spi_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup2_spi_apps_clk_src",
		.parent_names = gcc_xo_200_spi,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_spi_apps_clk = अणु
	.halt_reg = 0x300c,
	.clkr = अणु
		.enable_reg = 0x300c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_qup2_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_uart1_2_apps_clk[] = अणु
	F(1843200, P_FEPLL200, 1, 144, 15625),
	F(3686400, P_FEPLL200, 1, 288, 15625),
	F(7372800, P_FEPLL200, 1, 576, 15625),
	F(14745600, P_FEPLL200, 1, 1152, 15625),
	F(16000000, P_FEPLL200, 1, 2, 25),
	F(24000000, P_XO, 1, 1, 2),
	F(32000000, P_FEPLL200, 1, 4, 25),
	F(40000000, P_FEPLL200, 1, 1, 5),
	F(46400000, P_FEPLL200, 1, 29, 125),
	F(48000000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart1_apps_clk_src = अणु
	.cmd_rcgr = 0x2044,
	.mnd_width = 16,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_blsp1_uart1_2_apps_clk,
	.parent_map = gcc_xo_200_spi_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart1_apps_clk_src",
		.parent_names = gcc_xo_200_spi,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart1_apps_clk = अणु
	.halt_reg = 0x203c,
	.clkr = अणु
		.enable_reg = 0x203c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart1_apps_clk_src",
			पूर्ण,
			.flags = CLK_SET_RATE_PARENT,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart2_apps_clk_src = अणु
	.cmd_rcgr = 0x3034,
	.mnd_width = 16,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_blsp1_uart1_2_apps_clk,
	.parent_map = gcc_xo_200_spi_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_uart2_apps_clk_src",
		.parent_names = gcc_xo_200_spi,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart2_apps_clk = अणु
	.halt_reg = 0x302c,
	.clkr = अणु
		.enable_reg = 0x302c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp1_uart2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_gp_clk[] = अणु
	F(1250000,  P_FEPLL200, 1, 16, 0),
	F(2500000,  P_FEPLL200, 1,  8, 0),
	F(5000000,  P_FEPLL200, 1,  4, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gp1_clk_src = अणु
	.cmd_rcgr = 0x8004,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_gp_clk,
	.parent_map = gcc_xo_200_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp1_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp1_clk = अणु
	.halt_reg = 0x8000,
	.clkr = अणु
		.enable_reg = 0x8000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp2_clk_src = अणु
	.cmd_rcgr = 0x9004,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_gp_clk,
	.parent_map = gcc_xo_200_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp2_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp2_clk = अणु
	.halt_reg = 0x9000,
	.clkr = अणु
		.enable_reg = 0x9000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp2_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp3_clk_src = अणु
	.cmd_rcgr = 0xa004,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_gp_clk,
	.parent_map = gcc_xo_200_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp3_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp3_clk = अणु
	.halt_reg = 0xa000,
	.clkr = अणु
		.enable_reg = 0xa000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_gp3_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gp3_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_apps_clk[] = अणु
	F(144000,    P_XO,			1,  3, 240),
	F(400000,    P_XO,			1,  1, 0),
	F(20000000,  P_FEPLL500,		1,  1, 25),
	F(25000000,  P_FEPLL500,		1,  1, 20),
	F(50000000,  P_FEPLL500,		1,  1, 10),
	F(100000000, P_FEPLL500,		1,  1, 5),
	F(192000000, P_DDRPLL,			1,  0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2  sdcc1_apps_clk_src = अणु
	.cmd_rcgr = 0x18004,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_sdcc1_apps_clk,
	.parent_map = gcc_xo_sdcc1_500_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc1_apps_clk_src",
		.parent_names = gcc_xo_sdcc1_500,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_apps_clk[] = अणु
	F(48000000,  P_XO,         1, 0, 0),
	F(200000000, P_FEPLL200,   1, 0, 0),
	F(384000000, P_DDRPLLAPSS, 1, 0, 0),
	F(413000000, P_DDRPLLAPSS, 1, 0, 0),
	F(448000000, P_DDRPLLAPSS, 1, 0, 0),
	F(488000000, P_DDRPLLAPSS, 1, 0, 0),
	F(500000000, P_FEPLL500,   1, 0, 0),
	F(512000000, P_DDRPLLAPSS, 1, 0, 0),
	F(537000000, P_DDRPLLAPSS, 1, 0, 0),
	F(565000000, P_DDRPLLAPSS, 1, 0, 0),
	F(597000000, P_DDRPLLAPSS, 1, 0, 0),
	F(632000000, P_DDRPLLAPSS, 1, 0, 0),
	F(672000000, P_DDRPLLAPSS, 1, 0, 0),
	F(716000000, P_DDRPLLAPSS, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 apps_clk_src = अणु
	.cmd_rcgr = 0x1900c,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_apps_clk,
	.parent_map = gcc_xo_ddr_500_200_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apps_clk_src",
		.parent_names = gcc_xo_ddr_500_200,
		.num_parents = 4,
		.ops = &clk_rcg2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_apps_ahb_clk[] = अणु
	F(48000000, P_XO,	   1, 0, 0),
	F(100000000, P_FEPLL200,   2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 apps_ahb_clk_src = अणु
	.cmd_rcgr = 0x19014,
	.hid_width = 5,
	.parent_map = gcc_xo_200_500_map,
	.freq_tbl = ftbl_gcc_apps_ahb_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "apps_ahb_clk_src",
		.parent_names = gcc_xo_200_500,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_apss_ahb_clk = अणु
	.halt_reg = 0x19004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(14),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_apss_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"apps_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_ahb_clk = अणु
	.halt_reg = 0x1008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_dcd_xo_clk = अणु
	.halt_reg = 0x2103c,
	.clkr = अणु
		.enable_reg = 0x2103c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_dcd_xo_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_boot_rom_ahb_clk = अणु
	.halt_reg = 0x1300c,
	.clkr = अणु
		.enable_reg = 0x1300c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_boot_rom_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_crypto_ahb_clk = अणु
	.halt_reg = 0x16024,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_crypto_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_crypto_axi_clk = अणु
	.halt_reg = 0x16020,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_crypto_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fepll125",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_crypto_clk = अणु
	.halt_reg = 0x1601c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_crypto_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fepll125",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ess_clk = अणु
	.halt_reg = 0x12010,
	.clkr = अणु
		.enable_reg = 0x12010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ess_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fephy_125m_dly_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_imem_axi_clk = अणु
	.halt_reg = 0xe004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_imem_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fepll200",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_imem_cfg_ahb_clk = अणु
	.halt_reg = 0xe008,
	.clkr = अणु
		.enable_reg = 0xe008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_imem_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_ahb_clk = अणु
	.halt_reg = 0x1d00c,
	.clkr = अणु
		.enable_reg = 0x1d00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_axi_m_clk = अणु
	.halt_reg = 0x1d004,
	.clkr = अणु
		.enable_reg = 0x1d004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_axi_m_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fepll200",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_axi_s_clk = अणु
	.halt_reg = 0x1d008,
	.clkr = अणु
		.enable_reg = 0x1d008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_axi_s_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fepll200",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_prng_ahb_clk = अणु
	.halt_reg = 0x13004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(8),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_prng_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qpic_ahb_clk = अणु
	.halt_reg = 0x1c008,
	.clkr = अणु
		.enable_reg = 0x1c008,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qpic_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_qpic_clk = अणु
	.halt_reg = 0x1c004,
	.clkr = अणु
		.enable_reg = 0x1c004,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_qpic_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_ahb_clk = अणु
	.halt_reg = 0x18010,
	.clkr = अणु
		.enable_reg = 0x18010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_apps_clk = अणु
	.halt_reg = 0x1800c,
	.clkr = अणु
		.enable_reg = 0x1800c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sdcc1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tlmm_ahb_clk = अणु
	.halt_reg = 0x5004,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x6000,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tlmm_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2_master_clk = अणु
	.halt_reg = 0x1e00c,
	.clkr = अणु
		.enable_reg = 0x1e00c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb2_master_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcnoc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2_sleep_clk = अणु
	.halt_reg = 0x1e010,
	.clkr = अणु
		.enable_reg = 0x1e010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb2_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gcc_sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x1e014,
	.clkr = अणु
		.enable_reg = 0x1e014,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb2_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_mock_utmi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_mock_uपंचांगi_clk[] = अणु
	F(2000000, P_FEPLL200, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x1e000,
	.hid_width = 5,
	.parent_map = gcc_xo_200_map,
	.freq_tbl = ftbl_gcc_usb30_mock_uपंचांगi_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_mock_utmi_clk_src",
		.parent_names = gcc_xo_200,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_master_clk = अणु
	.halt_reg = 0x1e028,
	.clkr = अणु
		.enable_reg = 0x1e028,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_master_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"fepll125",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_sleep_clk = अणु
	.halt_reg = 0x1e02C,
	.clkr = अणु
		.enable_reg = 0x1e02C,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gcc_sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x1e030,
	.clkr = अणु
		.enable_reg = 0x1e030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb3_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_mock_utmi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_fephy_dly_clk[] = अणु
	F(125000000, P_FEPLL125DLY, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 fephy_125m_dly_clk_src = अणु
	.cmd_rcgr = 0x12000,
	.hid_width = 5,
	.parent_map = gcc_xo_125_dly_map,
	.freq_tbl = ftbl_gcc_fephy_dly_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "fephy_125m_dly_clk_src",
		.parent_names = gcc_xo_125_dly,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा freq_tbl ftbl_gcc_wcss2g_clk[] = अणु
	F(48000000, P_XO, 1, 0, 0),
	F(250000000, P_FEPLLWCSS2G, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 wcss2g_clk_src = अणु
	.cmd_rcgr = 0x1f000,
	.hid_width = 5,
	.freq_tbl = ftbl_gcc_wcss2g_clk,
	.parent_map = gcc_xo_wcss2g_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "wcss2g_clk_src",
		.parent_names = gcc_xo_wcss2g,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wcss2g_clk = अणु
	.halt_reg = 0x1f00C,
	.clkr = अणु
		.enable_reg = 0x1f00C,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wcss2g_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"wcss2g_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wcss2g_ref_clk = अणु
	.halt_reg = 0x1f00C,
	.clkr = अणु
		.enable_reg = 0x1f00C,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wcss2g_ref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wcss2g_rtc_clk = अणु
	.halt_reg = 0x1f010,
	.clkr = अणु
		.enable_reg = 0x1f010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wcss2g_rtc_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gcc_sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_wcss5g_clk[] = अणु
	F(48000000, P_XO, 1, 0, 0),
	F(250000000, P_FEPLLWCSS5G, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 wcss5g_clk_src = अणु
	.cmd_rcgr = 0x20000,
	.hid_width = 5,
	.parent_map = gcc_xo_wcss5g_map,
	.freq_tbl = ftbl_gcc_wcss5g_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "wcss5g_clk_src",
		.parent_names = gcc_xo_wcss5g,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wcss5g_clk = अणु
	.halt_reg = 0x2000c,
	.clkr = अणु
		.enable_reg = 0x2000c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wcss5g_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"wcss5g_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wcss5g_ref_clk = अणु
	.halt_reg = 0x2000c,
	.clkr = अणु
		.enable_reg = 0x2000c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wcss5g_ref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_wcss5g_rtc_clk = अणु
	.halt_reg = 0x20010,
	.clkr = अणु
		.enable_reg = 0x20010,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_wcss5g_rtc_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gcc_sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* Calculates the VCO rate क्रम FEPLL. */
अटल u64 clk_fepll_vco_calc_rate(काष्ठा clk_fepll *pll_भाग,
				   अचिन्हित दीर्घ parent_rate)
अणु
	स्थिर काष्ठा clk_fepll_vco *pll_vco = pll_भाग->pll_vco;
	u32 fdbkभाग, refclkभाग, cभाग;
	u64 vco;

	regmap_पढ़ो(pll_भाग->cभाग.clkr.regmap, pll_vco->reg, &cभाग);
	refclkभाग = (cभाग >> pll_vco->refclkभाग_shअगरt) &
		    (BIT(pll_vco->refclkभाग_width) - 1);
	fdbkभाग = (cभाग >> pll_vco->fdbkभाग_shअगरt) &
		  (BIT(pll_vco->fdbkभाग_width) - 1);

	vco = parent_rate / refclkभाग;
	vco *= 2;
	vco *= fdbkभाग;

	वापस vco;
पूर्ण

अटल स्थिर काष्ठा clk_fepll_vco gcc_apss_ddrpll_vco = अणु
	.fdbkभाग_shअगरt = 16,
	.fdbkभाग_width = 8,
	.refclkभाग_shअगरt = 24,
	.refclkभाग_width = 5,
	.reg = 0x2e020,
पूर्ण;

अटल स्थिर काष्ठा clk_fepll_vco gcc_fepll_vco = अणु
	.fdbkभाग_shअगरt = 16,
	.fdbkभाग_width = 8,
	.refclkभाग_shअगरt = 24,
	.refclkभाग_width = 5,
	.reg = 0x2f020,
पूर्ण;

/*
 * Round rate function क्रम APSS CPU PLL Clock भागider.
 * It looks up the frequency table and वापसs the next higher frequency
 * supported in hardware.
 */
अटल दीर्घ clk_cpu_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *p_rate)
अणु
	काष्ठा clk_fepll *pll = to_clk_fepll(hw);
	काष्ठा clk_hw *p_hw;
	स्थिर काष्ठा freq_tbl *f;

	f = qcom_find_freq(pll->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	p_hw = clk_hw_get_parent_by_index(hw, f->src);
	*p_rate = clk_hw_get_rate(p_hw);

	वापस f->freq;
पूर्ण;

/*
 * Clock set rate function क्रम APSS CPU PLL Clock भागider.
 * It looks up the frequency table and updates the PLL भागider to corresponding
 * भागider value.
 */
अटल पूर्णांक clk_cpu_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fepll *pll = to_clk_fepll(hw);
	स्थिर काष्ठा freq_tbl *f;
	u32 mask;

	f = qcom_find_freq(pll->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	mask = (BIT(pll->cभाग.width) - 1) << pll->cभाग.shअगरt;
	regmap_update_bits(pll->cभाग.clkr.regmap,
			   pll->cभाग.reg, mask,
			   f->pre_भाग << pll->cभाग.shअगरt);
	/*
	 * There is no status bit which can be checked क्रम successful CPU
	 * भागider update operation so using delay क्रम the same.
	 */
	udelay(1);

	वापस 0;
पूर्ण;

/*
 * Clock frequency calculation function क्रम APSS CPU PLL Clock भागider.
 * This घड़ी भागider is nonlinear so this function calculates the actual
 * भागider and वापसs the output frequency by भागiding VCO Frequency
 * with this actual भागider value.
 */
अटल अचिन्हित दीर्घ
clk_cpu_भाग_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fepll *pll = to_clk_fepll(hw);
	u32 cभाग, pre_भाग;
	u64 rate;

	regmap_पढ़ो(pll->cभाग.clkr.regmap, pll->cभाग.reg, &cभाग);
	cभाग = (cभाग >> pll->cभाग.shअगरt) & (BIT(pll->cभाग.width) - 1);

	/*
	 * Some भागiders have value in 0.5 fraction so multiply both VCO
	 * frequency(parent_rate) and pre_भाग with 2 to make पूर्णांकeger
	 * calculation.
	 */
	अगर (cभाग > 10)
		pre_भाग = (cभाग + 1) * 2;
	अन्यथा
		pre_भाग = cभाग + 12;

	rate = clk_fepll_vco_calc_rate(pll, parent_rate) * 2;
	करो_भाग(rate, pre_भाग);

	वापस rate;
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_regmap_cpu_भाग_ops = अणु
	.round_rate = clk_cpu_भाग_round_rate,
	.set_rate = clk_cpu_भाग_set_rate,
	.recalc_rate = clk_cpu_भाग_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_apss_ddr_pll[] = अणु
	अणु 384000000, P_XO, 0xd, 0, 0 पूर्ण,
	अणु 413000000, P_XO, 0xc, 0, 0 पूर्ण,
	अणु 448000000, P_XO, 0xb, 0, 0 पूर्ण,
	अणु 488000000, P_XO, 0xa, 0, 0 पूर्ण,
	अणु 512000000, P_XO, 0x9, 0, 0 पूर्ण,
	अणु 537000000, P_XO, 0x8, 0, 0 पूर्ण,
	अणु 565000000, P_XO, 0x7, 0, 0 पूर्ण,
	अणु 597000000, P_XO, 0x6, 0, 0 पूर्ण,
	अणु 632000000, P_XO, 0x5, 0, 0 पूर्ण,
	अणु 672000000, P_XO, 0x4, 0, 0 पूर्ण,
	अणु 716000000, P_XO, 0x3, 0, 0 पूर्ण,
	अणु 768000000, P_XO, 0x2, 0, 0 पूर्ण,
	अणु 823000000, P_XO, 0x1, 0, 0 पूर्ण,
	अणु 896000000, P_XO, 0x0, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_fepll gcc_apss_cpu_plद_भाग_clk = अणु
	.cभाग.reg = 0x2e020,
	.cभाग.shअगरt = 4,
	.cभाग.width = 4,
	.cभाग.clkr = अणु
		.enable_reg = 0x2e000,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ddrpllapss",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_regmap_cpu_भाग_ops,
		पूर्ण,
	पूर्ण,
	.freq_tbl = ftbl_apss_ddr_pll,
	.pll_vco = &gcc_apss_ddrpll_vco,
पूर्ण;

/* Calculates the rate क्रम PLL भागider.
 * If the भागider value is not fixed then it माला_लो the actual भागider value
 * from भागider table. Then, it calculate the घड़ी rate by भागiding the
 * parent rate with actual भागider value.
 */
अटल अचिन्हित दीर्घ
clk_regmap_clk_भाग_recalc_rate(काष्ठा clk_hw *hw,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fepll *pll = to_clk_fepll(hw);
	u32 cभाग, pre_भाग = 1;
	u64 rate;
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	अगर (pll->fixed_भाग) अणु
		pre_भाग = pll->fixed_भाग;
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(pll->cभाग.clkr.regmap, pll->cभाग.reg, &cभाग);
		cभाग = (cभाग >> pll->cभाग.shअगरt) & (BIT(pll->cभाग.width) - 1);

		क्रम (clkt = pll->भाग_प्रकारable; clkt->भाग; clkt++) अणु
			अगर (clkt->val == cभाग)
				pre_भाग = clkt->भाग;
		पूर्ण
	पूर्ण

	rate = clk_fepll_vco_calc_rate(pll, parent_rate);
	करो_भाग(rate, pre_भाग);

	वापस rate;
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_fepll_भाग_ops = अणु
	.recalc_rate = clk_regmap_clk_भाग_recalc_rate,
पूर्ण;

अटल काष्ठा clk_fepll gcc_apss_sdcc_clk = अणु
	.fixed_भाग = 28,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "ddrpllsdcc",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.pll_vco = &gcc_apss_ddrpll_vco,
पूर्ण;

अटल काष्ठा clk_fepll gcc_fepll125_clk = अणु
	.fixed_भाग = 32,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fepll125",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.pll_vco = &gcc_fepll_vco,
पूर्ण;

अटल काष्ठा clk_fepll gcc_fepll125dly_clk = अणु
	.fixed_भाग = 32,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fepll125dly",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.pll_vco = &gcc_fepll_vco,
पूर्ण;

अटल काष्ठा clk_fepll gcc_fepll200_clk = अणु
	.fixed_भाग = 20,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fepll200",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.pll_vco = &gcc_fepll_vco,
पूर्ण;

अटल काष्ठा clk_fepll gcc_fepll500_clk = अणु
	.fixed_भाग = 8,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fepll500",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.pll_vco = &gcc_fepll_vco,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable fepllwcss_clk_भाग_प्रकारable[] = अणु
	अणु 0, 15 पूर्ण,
	अणु 1, 16 पूर्ण,
	अणु 2, 18 पूर्ण,
	अणु 3, 20 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा clk_fepll gcc_fepllwcss2g_clk = अणु
	.cभाग.reg = 0x2f020,
	.cभाग.shअगरt = 8,
	.cभाग.width = 2,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fepllwcss2g",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.भाग_प्रकारable = fepllwcss_clk_भाग_प्रकारable,
	.pll_vco = &gcc_fepll_vco,
पूर्ण;

अटल काष्ठा clk_fepll gcc_fepllwcss5g_clk = अणु
	.cभाग.reg = 0x2f020,
	.cभाग.shअगरt = 12,
	.cभाग.width = 2,
	.cभाग.clkr = अणु
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "fepllwcss5g",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_fepll_भाग_ops,
		पूर्ण,
	पूर्ण,
	.भाग_प्रकारable = fepllwcss_clk_भाग_प्रकारable,
	.pll_vco = &gcc_fepll_vco,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcnoc_ahb_clk[] = अणु
	F(48000000,  P_XO,	 1, 0, 0),
	F(100000000, P_FEPLL200, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gcc_pcnoc_ahb_clk_src = अणु
	.cmd_rcgr = 0x21024,
	.hid_width = 5,
	.parent_map = gcc_xo_200_500_map,
	.freq_tbl = ftbl_gcc_pcnoc_ahb_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gcc_pcnoc_ahb_clk_src",
		.parent_names = gcc_xo_200_500,
		.num_parents = 3,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch pcnoc_clk_src = अणु
	.halt_reg = 0x21030,
	.clkr = अणु
		.enable_reg = 0x21030,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "pcnoc_clk_src",
			.parent_names = (स्थिर अक्षर *[])अणु
				"gcc_pcnoc_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
			.flags = CLK_SET_RATE_PARENT |
				CLK_IS_CRITICAL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_ipq4019_घड़ीs[] = अणु
	[AUDIO_CLK_SRC] = &audio_clk_src.clkr,
	[BLSP1_QUP1_I2C_APPS_CLK_SRC] = &blsp1_qup1_i2c_apps_clk_src.clkr,
	[BLSP1_QUP1_SPI_APPS_CLK_SRC] = &blsp1_qup1_spi_apps_clk_src.clkr,
	[BLSP1_QUP2_I2C_APPS_CLK_SRC] = &blsp1_qup2_i2c_apps_clk_src.clkr,
	[BLSP1_QUP2_SPI_APPS_CLK_SRC] = &blsp1_qup2_spi_apps_clk_src.clkr,
	[BLSP1_UART1_APPS_CLK_SRC] = &blsp1_uart1_apps_clk_src.clkr,
	[BLSP1_UART2_APPS_CLK_SRC] = &blsp1_uart2_apps_clk_src.clkr,
	[GCC_USB3_MOCK_UTMI_CLK_SRC] = &usb30_mock_uपंचांगi_clk_src.clkr,
	[GCC_APPS_CLK_SRC] = &apps_clk_src.clkr,
	[GCC_APPS_AHB_CLK_SRC] = &apps_ahb_clk_src.clkr,
	[GP1_CLK_SRC] = &gp1_clk_src.clkr,
	[GP2_CLK_SRC] = &gp2_clk_src.clkr,
	[GP3_CLK_SRC] = &gp3_clk_src.clkr,
	[SDCC1_APPS_CLK_SRC] = &sdcc1_apps_clk_src.clkr,
	[FEPHY_125M_DLY_CLK_SRC] = &fephy_125m_dly_clk_src.clkr,
	[WCSS2G_CLK_SRC] = &wcss2g_clk_src.clkr,
	[WCSS5G_CLK_SRC] = &wcss5g_clk_src.clkr,
	[GCC_APSS_AHB_CLK] = &gcc_apss_ahb_clk.clkr,
	[GCC_AUDIO_AHB_CLK] = &gcc_audio_ahb_clk.clkr,
	[GCC_AUDIO_PWM_CLK] = &gcc_audio_pwm_clk.clkr,
	[GCC_BLSP1_AHB_CLK] = &gcc_blsp1_ahb_clk.clkr,
	[GCC_BLSP1_QUP1_I2C_APPS_CLK] = &gcc_blsp1_qup1_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP1_SPI_APPS_CLK] = &gcc_blsp1_qup1_spi_apps_clk.clkr,
	[GCC_BLSP1_QUP2_I2C_APPS_CLK] = &gcc_blsp1_qup2_i2c_apps_clk.clkr,
	[GCC_BLSP1_QUP2_SPI_APPS_CLK] = &gcc_blsp1_qup2_spi_apps_clk.clkr,
	[GCC_BLSP1_UART1_APPS_CLK] = &gcc_blsp1_uart1_apps_clk.clkr,
	[GCC_BLSP1_UART2_APPS_CLK] = &gcc_blsp1_uart2_apps_clk.clkr,
	[GCC_DCD_XO_CLK] = &gcc_dcd_xo_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_CRYPTO_AHB_CLK] = &gcc_crypto_ahb_clk.clkr,
	[GCC_CRYPTO_AXI_CLK] = &gcc_crypto_axi_clk.clkr,
	[GCC_CRYPTO_CLK] = &gcc_crypto_clk.clkr,
	[GCC_ESS_CLK] = &gcc_ess_clk.clkr,
	[GCC_IMEM_AXI_CLK] = &gcc_imem_axi_clk.clkr,
	[GCC_IMEM_CFG_AHB_CLK] = &gcc_imem_cfg_ahb_clk.clkr,
	[GCC_PCIE_AHB_CLK] = &gcc_pcie_ahb_clk.clkr,
	[GCC_PCIE_AXI_M_CLK] = &gcc_pcie_axi_m_clk.clkr,
	[GCC_PCIE_AXI_S_CLK] = &gcc_pcie_axi_s_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
	[GCC_QPIC_AHB_CLK] = &gcc_qpic_ahb_clk.clkr,
	[GCC_QPIC_CLK] = &gcc_qpic_clk.clkr,
	[GCC_SDCC1_AHB_CLK] = &gcc_sdcc1_ahb_clk.clkr,
	[GCC_SDCC1_APPS_CLK] = &gcc_sdcc1_apps_clk.clkr,
	[GCC_TLMM_AHB_CLK] = &gcc_tlmm_ahb_clk.clkr,
	[GCC_USB2_MASTER_CLK] = &gcc_usb2_master_clk.clkr,
	[GCC_USB2_SLEEP_CLK] = &gcc_usb2_sleep_clk.clkr,
	[GCC_USB2_MOCK_UTMI_CLK] = &gcc_usb2_mock_uपंचांगi_clk.clkr,
	[GCC_USB3_MASTER_CLK] = &gcc_usb3_master_clk.clkr,
	[GCC_USB3_SLEEP_CLK] = &gcc_usb3_sleep_clk.clkr,
	[GCC_USB3_MOCK_UTMI_CLK] = &gcc_usb3_mock_uपंचांगi_clk.clkr,
	[GCC_WCSS2G_CLK] = &gcc_wcss2g_clk.clkr,
	[GCC_WCSS2G_REF_CLK] = &gcc_wcss2g_ref_clk.clkr,
	[GCC_WCSS2G_RTC_CLK] = &gcc_wcss2g_rtc_clk.clkr,
	[GCC_WCSS5G_CLK] = &gcc_wcss5g_clk.clkr,
	[GCC_WCSS5G_REF_CLK] = &gcc_wcss5g_ref_clk.clkr,
	[GCC_WCSS5G_RTC_CLK] = &gcc_wcss5g_rtc_clk.clkr,
	[GCC_SDCC_PLLDIV_CLK] = &gcc_apss_sdcc_clk.cभाग.clkr,
	[GCC_FEPLL125_CLK] = &gcc_fepll125_clk.cभाग.clkr,
	[GCC_FEPLL125DLY_CLK] = &gcc_fepll125dly_clk.cभाग.clkr,
	[GCC_FEPLL200_CLK] = &gcc_fepll200_clk.cभाग.clkr,
	[GCC_FEPLL500_CLK] = &gcc_fepll500_clk.cभाग.clkr,
	[GCC_FEPLL_WCSS2G_CLK] = &gcc_fepllwcss2g_clk.cभाग.clkr,
	[GCC_FEPLL_WCSS5G_CLK] = &gcc_fepllwcss5g_clk.cभाग.clkr,
	[GCC_APSS_CPU_PLLDIV_CLK] = &gcc_apss_cpu_plद_भाग_clk.cभाग.clkr,
	[GCC_PCNOC_AHB_CLK_SRC] = &gcc_pcnoc_ahb_clk_src.clkr,
	[GCC_PCNOC_AHB_CLK] = &pcnoc_clk_src.clkr,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_ipq4019_resets[] = अणु
	[WIFI0_CPU_INIT_RESET] = अणु 0x1f008, 5 पूर्ण,
	[WIFI0_RADIO_SRIF_RESET] = अणु 0x1f008, 4 पूर्ण,
	[WIFI0_RADIO_WARM_RESET] = अणु 0x1f008, 3 पूर्ण,
	[WIFI0_RADIO_COLD_RESET] = अणु 0x1f008, 2 पूर्ण,
	[WIFI0_CORE_WARM_RESET] = अणु 0x1f008, 1 पूर्ण,
	[WIFI0_CORE_COLD_RESET] = अणु 0x1f008, 0 पूर्ण,
	[WIFI1_CPU_INIT_RESET] = अणु 0x20008, 5 पूर्ण,
	[WIFI1_RADIO_SRIF_RESET] = अणु 0x20008, 4 पूर्ण,
	[WIFI1_RADIO_WARM_RESET] = अणु 0x20008, 3 पूर्ण,
	[WIFI1_RADIO_COLD_RESET] = अणु 0x20008, 2 पूर्ण,
	[WIFI1_CORE_WARM_RESET] = अणु 0x20008, 1 पूर्ण,
	[WIFI1_CORE_COLD_RESET] = अणु 0x20008, 0 पूर्ण,
	[USB3_UNIPHY_PHY_ARES] = अणु 0x1e038, 5 पूर्ण,
	[USB3_HSPHY_POR_ARES] = अणु 0x1e038, 4 पूर्ण,
	[USB3_HSPHY_S_ARES] = अणु 0x1e038, 2 पूर्ण,
	[USB2_HSPHY_POR_ARES] = अणु 0x1e01c, 4 पूर्ण,
	[USB2_HSPHY_S_ARES] = अणु 0x1e01c, 2 पूर्ण,
	[PCIE_PHY_AHB_ARES] = अणु 0x1d010, 11 पूर्ण,
	[PCIE_AHB_ARES] = अणु 0x1d010, 10 पूर्ण,
	[PCIE_PWR_ARES] = अणु 0x1d010, 9 पूर्ण,
	[PCIE_PIPE_STICKY_ARES] = अणु 0x1d010, 8 पूर्ण,
	[PCIE_AXI_M_STICKY_ARES] = अणु 0x1d010, 7 पूर्ण,
	[PCIE_PHY_ARES] = अणु 0x1d010, 6 पूर्ण,
	[PCIE_PARF_XPU_ARES] = अणु 0x1d010, 5 पूर्ण,
	[PCIE_AXI_S_XPU_ARES] = अणु 0x1d010, 4 पूर्ण,
	[PCIE_AXI_M_VMIDMT_ARES] = अणु 0x1d010, 3 पूर्ण,
	[PCIE_PIPE_ARES] = अणु 0x1d010, 2 पूर्ण,
	[PCIE_AXI_S_ARES] = अणु 0x1d010, 1 पूर्ण,
	[PCIE_AXI_M_ARES] = अणु 0x1d010, 0 पूर्ण,
	[ESS_RESET] = अणु 0x12008, 0पूर्ण,
	[GCC_BLSP1_BCR] = अणु0x01000, 0पूर्ण,
	[GCC_BLSP1_QUP1_BCR] = अणु0x02000, 0पूर्ण,
	[GCC_BLSP1_UART1_BCR] = अणु0x02038, 0पूर्ण,
	[GCC_BLSP1_QUP2_BCR] = अणु0x03008, 0पूर्ण,
	[GCC_BLSP1_UART2_BCR] = अणु0x03028, 0पूर्ण,
	[GCC_BIMC_BCR] = अणु0x04000, 0पूर्ण,
	[GCC_TLMM_BCR] = अणु0x05000, 0पूर्ण,
	[GCC_IMEM_BCR] = अणु0x0E000, 0पूर्ण,
	[GCC_ESS_BCR] = अणु0x12008, 0पूर्ण,
	[GCC_PRNG_BCR] = अणु0x13000, 0पूर्ण,
	[GCC_BOOT_ROM_BCR] = अणु0x13008, 0पूर्ण,
	[GCC_CRYPTO_BCR] = अणु0x16000, 0पूर्ण,
	[GCC_SDCC1_BCR] = अणु0x18000, 0पूर्ण,
	[GCC_SEC_CTRL_BCR] = अणु0x1A000, 0पूर्ण,
	[GCC_AUDIO_BCR] = अणु0x1B008, 0पूर्ण,
	[GCC_QPIC_BCR] = अणु0x1C000, 0पूर्ण,
	[GCC_PCIE_BCR] = अणु0x1D000, 0पूर्ण,
	[GCC_USB2_BCR] = अणु0x1E008, 0पूर्ण,
	[GCC_USB2_PHY_BCR] = अणु0x1E018, 0पूर्ण,
	[GCC_USB3_BCR] = अणु0x1E024, 0पूर्ण,
	[GCC_USB3_PHY_BCR] = अणु0x1E034, 0पूर्ण,
	[GCC_SYSTEM_NOC_BCR] = अणु0x21000, 0पूर्ण,
	[GCC_PCNOC_BCR] = अणु0x2102C, 0पूर्ण,
	[GCC_DCD_BCR] = अणु0x21038, 0पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT0_BCR] = अणु0x21064, 0पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT1_BCR] = अणु0x2106C, 0पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT2_BCR] = अणु0x21074, 0पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT3_BCR] = अणु0x2107C, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT0_BCR] = अणु0x21084, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT1_BCR] = अणु0x2108C, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT2_BCR] = अणु0x21094, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT3_BCR] = अणु0x2109C, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT4_BCR] = अणु0x210A4, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT5_BCR] = अणु0x210AC, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT6_BCR] = अणु0x210B4, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT7_BCR] = अणु0x210BC, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT8_BCR] = अणु0x210C4, 0पूर्ण,
	[GCC_PCNOC_BUS_TIMEOUT9_BCR] = अणु0x210CC, 0पूर्ण,
	[GCC_TCSR_BCR] = अणु0x22000, 0पूर्ण,
	[GCC_MPM_BCR] = अणु0x24000, 0पूर्ण,
	[GCC_SPDM_BCR] = अणु0x25000, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_ipq4019_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x2ffff,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_ipq4019_desc = अणु
	.config = &gcc_ipq4019_regmap_config,
	.clks = gcc_ipq4019_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_ipq4019_घड़ीs),
	.resets = gcc_ipq4019_resets,
	.num_resets = ARRAY_SIZE(gcc_ipq4019_resets),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_ipq4019_match_table[] = अणु
	अणु .compatible = "qcom,gcc-ipq4019" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_ipq4019_match_table);

अटल पूर्णांक
gcc_ipq4019_cpu_clk_notअगरier_fn(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *data)
अणु
	पूर्णांक err = 0;

	अगर (action == PRE_RATE_CHANGE)
		err = clk_rcg2_ops.set_parent(&apps_clk_src.clkr.hw,
					      gcc_ipq4019_cpu_safe_parent);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल काष्ठा notअगरier_block gcc_ipq4019_cpu_clk_notअगरier = अणु
	.notअगरier_call = gcc_ipq4019_cpu_clk_notअगरier_fn,
पूर्ण;

अटल पूर्णांक gcc_ipq4019_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	err = qcom_cc_probe(pdev, &gcc_ipq4019_desc);
	अगर (err)
		वापस err;

	वापस clk_notअगरier_रेजिस्टर(apps_clk_src.clkr.hw.clk,
				     &gcc_ipq4019_cpu_clk_notअगरier);
पूर्ण

अटल पूर्णांक gcc_ipq4019_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस clk_notअगरier_unरेजिस्टर(apps_clk_src.clkr.hw.clk,
				       &gcc_ipq4019_cpu_clk_notअगरier);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_ipq4019_driver = अणु
	.probe		= gcc_ipq4019_probe,
	.हटाओ		= gcc_ipq4019_हटाओ,
	.driver		= अणु
		.name	= "qcom,gcc-ipq4019",
		.of_match_table = gcc_ipq4019_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_ipq4019_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_ipq4019_driver);
पूर्ण
core_initcall(gcc_ipq4019_init);

अटल व्योम __निकास gcc_ipq4019_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_ipq4019_driver);
पूर्ण
module_निकास(gcc_ipq4019_निकास);

MODULE_ALIAS("platform:gcc-ipq4019");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("QCOM GCC IPQ4019 driver");
