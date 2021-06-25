<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-msm8994.h>

#समावेश "common.h"
#समावेश "clk-regmap.h"
#समावेश "clk-alpha-pll.h"
#समावेश "clk-rcg.h"
#समावेश "clk-branch.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

क्रमागत अणु
	P_XO,
	P_GPLL0,
	P_GPLL4,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0[] = अणु
	"xo",
	"gpll0",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_gpll4_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_GPLL4, 5 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_gpll4[] = अणु
	"xo",
	"gpll0",
	"gpll4",
पूर्ण;

अटल काष्ठा clk_fixed_factor xo = अणु
	.mult = 1,
	.भाग = 1,
	.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "xo",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo_board" पूर्ण,
		.num_parents = 1,
		.ops = &clk_fixed_factor_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll0_early = अणु
	.offset = 0x00000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr = अणु
		.enable_reg = 0x1480,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gpll0_early",
			.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll0 = अणु
	.offset = 0x00000,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "gpll0",
		.parent_names = (स्थिर अक्षर *[]) अणु "gpll0_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll gpll4_early = अणु
	.offset = 0x1dc0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr = अणु
		.enable_reg = 0x1480,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gpll4_early",
			.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll_postभाग gpll4 = अणु
	.offset = 0x1dc0,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "gpll4",
		.parent_names = (स्थिर अक्षर *[]) अणु "gpll4_early" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_postभाग_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_ufs_axi_clk_src[] = अणु
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(150000000, P_GPLL0, 4, 0, 0),
	F(171430000, P_GPLL0, 3.5, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(240000000, P_GPLL0, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ufs_axi_clk_src = अणु
	.cmd_rcgr = 0x1d68,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_ufs_axi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "ufs_axi_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_usb30_master_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(125000000, P_GPLL0, 1, 5, 24),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_master_clk_src = अणु
	.cmd_rcgr = 0x03d4,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_usb30_master_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "usb30_master_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_blsp_i2c_apps_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0660,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup1_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_blspqup_spi_apps_clk_src[] = अणु
	F(960000, P_XO, 10, 1, 2),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(15000000, P_GPLL0, 10, 1, 4),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPLL0, 12.5, 1, 2),
	F(25000000, P_GPLL0, 12, 1, 2),
	F(48000000, P_GPLL0, 12.5, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x064c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup1_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x06e0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup2_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup2_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x06cc,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup2_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup3_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0760,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup3_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup3_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x074c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup3_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup4_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x07e0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup4_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup4_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x07cc,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup4_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup5_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0860,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup5_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup5_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x084c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup5_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup6_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x08e0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup6_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup6_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x08cc,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_qup6_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_blsp_uart_apps_clk_src[] = अणु
	F(3686400, P_GPLL0, 1, 96, 15625),
	F(7372800, P_GPLL0, 1, 192, 15625),
	F(14745600, P_GPLL0, 1, 384, 15625),
	F(16000000, P_GPLL0, 5, 2, 15),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPLL0, 5, 1, 5),
	F(32000000, P_GPLL0, 1, 4, 75),
	F(40000000, P_GPLL0, 15, 0, 0),
	F(46400000, P_GPLL0, 1, 29, 375),
	F(48000000, P_GPLL0, 12.5, 0, 0),
	F(51200000, P_GPLL0, 1, 32, 375),
	F(56000000, P_GPLL0, 1, 7, 75),
	F(58982400, P_GPLL0, 1, 1536, 15625),
	F(60000000, P_GPLL0, 10, 0, 0),
	F(63160000, P_GPLL0, 9.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart1_apps_clk_src = अणु
	.cmd_rcgr = 0x068c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_uart1_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart2_apps_clk_src = अणु
	.cmd_rcgr = 0x070c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_uart2_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart3_apps_clk_src = अणु
	.cmd_rcgr = 0x078c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_uart3_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart4_apps_clk_src = अणु
	.cmd_rcgr = 0x080c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_uart4_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart5_apps_clk_src = अणु
	.cmd_rcgr = 0x088c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_uart5_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_uart6_apps_clk_src = अणु
	.cmd_rcgr = 0x090c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp1_uart6_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x09a0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup1_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x098c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup1_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup2_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0a20,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup2_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup2_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x0a0c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup2_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup3_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0aa0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup3_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup3_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x0a8c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup3_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup4_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0b20,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup4_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup4_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x0b0c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup4_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup5_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0ba0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup5_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup5_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x0b8c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup5_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup6_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0c20,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_i2c_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup6_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_qup6_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x0c0c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blspqup_spi_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_qup6_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart1_apps_clk_src = अणु
	.cmd_rcgr = 0x09cc,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_uart1_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart2_apps_clk_src = अणु
	.cmd_rcgr = 0x0a4c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_uart2_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart3_apps_clk_src = अणु
	.cmd_rcgr = 0x0acc,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_uart3_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart4_apps_clk_src = अणु
	.cmd_rcgr = 0x0b4c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_uart4_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart5_apps_clk_src = अणु
	.cmd_rcgr = 0x0bcc,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_uart5_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 blsp2_uart6_apps_clk_src = अणु
	.cmd_rcgr = 0x0c4c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_blsp_uart_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "blsp2_uart6_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_gp1_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gp1_clk_src = अणु
	.cmd_rcgr = 0x1904,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gp1_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "gp1_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_gp2_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gp2_clk_src = अणु
	.cmd_rcgr = 0x1944,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gp2_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "gp2_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_gp3_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 gp3_clk_src = अणु
	.cmd_rcgr = 0x1984,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gp3_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "gp3_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_pcie_0_aux_clk_src[] = अणु
	F(1011000, P_XO, 1, 1, 19),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_0_aux_clk_src = अणु
	.cmd_rcgr = 0x1b00,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_pcie_0_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "pcie_0_aux_clk_src",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_pcie_pipe_clk_src[] = अणु
	F(125000000, P_XO, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_0_pipe_clk_src = अणु
	.cmd_rcgr = 0x1adc,
	.hid_width = 5,
	.freq_tbl = ftbl_pcie_pipe_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "pcie_0_pipe_clk_src",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_pcie_1_aux_clk_src[] = अणु
	F(1011000, P_XO, 1, 1, 19),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_1_aux_clk_src = अणु
	.cmd_rcgr = 0x1b80,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_pcie_1_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "pcie_1_aux_clk_src",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_1_pipe_clk_src = अणु
	.cmd_rcgr = 0x1b5c,
	.hid_width = 5,
	.freq_tbl = ftbl_pcie_pipe_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "pcie_1_pipe_clk_src",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_pdm2_clk_src[] = अणु
	F(60000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pdm2_clk_src = अणु
	.cmd_rcgr = 0x0cd0,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_pdm2_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "pdm2_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_sdcc1_apps_clk_src[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0, 15, 1, 2),
	F(25000000, P_GPLL0, 12, 1, 2),
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(192000000, P_GPLL4, 2, 0, 0),
	F(384000000, P_GPLL4, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc1_apps_clk_src = अणु
	.cmd_rcgr = 0x04d0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll4_map,
	.freq_tbl = ftbl_sdcc1_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "sdcc1_apps_clk_src",
		.parent_names = gcc_xo_gpll0_gpll4,
		.num_parents = 3,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_sdcc2_4_apps_clk_src[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0, 15, 1, 2),
	F(25000000, P_GPLL0, 12, 1, 2),
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x0510,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_sdcc2_4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "sdcc2_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc3_apps_clk_src = अणु
	.cmd_rcgr = 0x0550,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_sdcc2_4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "sdcc3_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc4_apps_clk_src = अणु
	.cmd_rcgr = 0x0590,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_sdcc2_4_apps_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "sdcc4_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_tsअगर_ref_clk_src[] = अणु
	F(105500, P_XO, 1, 1, 182),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 tsअगर_ref_clk_src = अणु
	.cmd_rcgr = 0x0d90,
	.mnd_width = 8,
	.hid_width = 5,
	.freq_tbl = ftbl_tsअगर_ref_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "tsif_ref_clk_src",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_usb30_mock_uपंचांगi_clk_src[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(60000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x03e8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_usb30_mock_uपंचांगi_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "usb30_mock_utmi_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_usb3_phy_aux_clk_src[] = अणु
	F(1200000, P_XO, 16, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb3_phy_aux_clk_src = अणु
	.cmd_rcgr = 0x1414,
	.hid_width = 5,
	.freq_tbl = ftbl_usb3_phy_aux_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "usb3_phy_aux_clk_src",
		.parent_names = (स्थिर अक्षर *[]) अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा freq_tbl ftbl_usb_hs_प्रणाली_clk_src[] = अणु
	F(75000000, P_GPLL0, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hs_प्रणाली_clk_src = अणु
	.cmd_rcgr = 0x0490,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_usb_hs_प्रणाली_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)
	अणु
		.name = "usb_hs_system_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_ahb_clk = अणु
	.halt_reg = 0x05c4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x0648,
	.clkr = अणु
		.enable_reg = 0x0648,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup1_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_spi_apps_clk = अणु
	.halt_reg = 0x0644,
	.clkr = अणु
		.enable_reg = 0x0644,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup1_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_i2c_apps_clk = अणु
	.halt_reg = 0x06c8,
	.clkr = अणु
		.enable_reg = 0x06c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup2_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup2_spi_apps_clk = अणु
	.halt_reg = 0x06c4,
	.clkr = अणु
		.enable_reg = 0x06c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup2_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup3_i2c_apps_clk = अणु
	.halt_reg = 0x0748,
	.clkr = अणु
		.enable_reg = 0x0748,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup3_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup3_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup3_spi_apps_clk = अणु
	.halt_reg = 0x0744,
	.clkr = अणु
		.enable_reg = 0x0744,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup3_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup3_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup4_i2c_apps_clk = अणु
	.halt_reg = 0x07c8,
	.clkr = अणु
		.enable_reg = 0x07c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup4_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup4_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup4_spi_apps_clk = अणु
	.halt_reg = 0x07c4,
	.clkr = अणु
		.enable_reg = 0x07c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup4_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup4_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup5_i2c_apps_clk = अणु
	.halt_reg = 0x0848,
	.clkr = अणु
		.enable_reg = 0x0848,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup5_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup5_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup5_spi_apps_clk = अणु
	.halt_reg = 0x0844,
	.clkr = अणु
		.enable_reg = 0x0844,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup5_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup5_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup6_i2c_apps_clk = अणु
	.halt_reg = 0x08c8,
	.clkr = अणु
		.enable_reg = 0x08c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup6_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup6_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup6_spi_apps_clk = अणु
	.halt_reg = 0x08c4,
	.clkr = अणु
		.enable_reg = 0x08c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_qup6_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_qup6_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart1_apps_clk = अणु
	.halt_reg = 0x0684,
	.clkr = अणु
		.enable_reg = 0x0684,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_uart1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart2_apps_clk = अणु
	.halt_reg = 0x0704,
	.clkr = अणु
		.enable_reg = 0x0704,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_uart2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart3_apps_clk = अणु
	.halt_reg = 0x0784,
	.clkr = अणु
		.enable_reg = 0x0784,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_uart3_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_uart3_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart4_apps_clk = अणु
	.halt_reg = 0x0804,
	.clkr = अणु
		.enable_reg = 0x0804,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_uart4_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_uart4_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart5_apps_clk = अणु
	.halt_reg = 0x0884,
	.clkr = अणु
		.enable_reg = 0x0884,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_uart5_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_uart5_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_uart6_apps_clk = अणु
	.halt_reg = 0x0904,
	.clkr = अणु
		.enable_reg = 0x0904,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp1_uart6_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp1_uart6_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_ahb_clk = अणु
	.halt_reg = 0x0944,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(15),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x0988,
	.clkr = अणु
		.enable_reg = 0x0988,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup1_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup1_spi_apps_clk = अणु
	.halt_reg = 0x0984,
	.clkr = अणु
		.enable_reg = 0x0984,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup1_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup2_i2c_apps_clk = अणु
	.halt_reg = 0x0a08,
	.clkr = अणु
		.enable_reg = 0x0a08,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup2_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup2_spi_apps_clk = अणु
	.halt_reg = 0x0a04,
	.clkr = अणु
		.enable_reg = 0x0a04,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup2_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup3_i2c_apps_clk = अणु
	.halt_reg = 0x0a88,
	.clkr = अणु
		.enable_reg = 0x0a88,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup3_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup3_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup3_spi_apps_clk = अणु
	.halt_reg = 0x0a84,
	.clkr = अणु
		.enable_reg = 0x0a84,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup3_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup3_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup4_i2c_apps_clk = अणु
	.halt_reg = 0x0b08,
	.clkr = अणु
		.enable_reg = 0x0b08,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup4_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup4_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup4_spi_apps_clk = अणु
	.halt_reg = 0x0b04,
	.clkr = अणु
		.enable_reg = 0x0b04,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup4_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup4_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup5_i2c_apps_clk = अणु
	.halt_reg = 0x0b88,
	.clkr = अणु
		.enable_reg = 0x0b88,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup5_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup5_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup5_spi_apps_clk = अणु
	.halt_reg = 0x0b84,
	.clkr = अणु
		.enable_reg = 0x0b84,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup5_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup5_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup6_i2c_apps_clk = अणु
	.halt_reg = 0x0c08,
	.clkr = अणु
		.enable_reg = 0x0c08,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup6_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup6_i2c_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup6_spi_apps_clk = अणु
	.halt_reg = 0x0c04,
	.clkr = अणु
		.enable_reg = 0x0c04,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_qup6_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_qup6_spi_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart1_apps_clk = अणु
	.halt_reg = 0x09c4,
	.clkr = अणु
		.enable_reg = 0x09c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_uart1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart2_apps_clk = अणु
	.halt_reg = 0x0a44,
	.clkr = अणु
		.enable_reg = 0x0a44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_uart2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart3_apps_clk = अणु
	.halt_reg = 0x0ac4,
	.clkr = अणु
		.enable_reg = 0x0ac4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_uart3_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_uart3_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart4_apps_clk = अणु
	.halt_reg = 0x0b44,
	.clkr = अणु
		.enable_reg = 0x0b44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_uart4_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_uart4_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart5_apps_clk = अणु
	.halt_reg = 0x0bc4,
	.clkr = अणु
		.enable_reg = 0x0bc4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_uart5_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_uart5_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_uart6_apps_clk = अणु
	.halt_reg = 0x0c44,
	.clkr = अणु
		.enable_reg = 0x0c44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_blsp2_uart6_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"blsp2_uart6_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp1_clk = अणु
	.halt_reg = 0x1900,
	.clkr = अणु
		.enable_reg = 0x1900,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_gp1_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"gp1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp2_clk = अणु
	.halt_reg = 0x1940,
	.clkr = अणु
		.enable_reg = 0x1940,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_gp2_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"gp2_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_gp3_clk = अणु
	.halt_reg = 0x1980,
	.clkr = अणु
		.enable_reg = 0x1980,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_gp3_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"gp3_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_lpass_q6_axi_clk = अणु
	.halt_reg = 0x0280,
	.clkr = अणु
		.enable_reg = 0x0280,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_lpass_q6_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_mss_q6_bimc_axi_clk = अणु
	.halt_reg = 0x0284,
	.clkr = अणु
		.enable_reg = 0x0284,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_mss_q6_bimc_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_aux_clk = अणु
	.halt_reg = 0x1ad4,
	.clkr = अणु
		.enable_reg = 0x1ad4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_0_aux_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"pcie_0_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_cfg_ahb_clk = अणु
	.halt_reg = 0x1ad0,
	.clkr = अणु
		.enable_reg = 0x1ad0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_0_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_mstr_axi_clk = अणु
	.halt_reg = 0x1acc,
	.clkr = अणु
		.enable_reg = 0x1acc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_0_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_pipe_clk = अणु
	.halt_reg = 0x1ad8,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1ad8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_0_pipe_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"pcie_0_pipe_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_axi_clk = अणु
	.halt_reg = 0x1ac8,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1ac8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_0_slv_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_aux_clk = अणु
	.halt_reg = 0x1b54,
	.clkr = अणु
		.enable_reg = 0x1b54,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_1_aux_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"pcie_1_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_cfg_ahb_clk = अणु
	.halt_reg = 0x1b54,
	.clkr = अणु
		.enable_reg = 0x1b54,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_1_cfg_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_mstr_axi_clk = अणु
	.halt_reg = 0x1b50,
	.clkr = अणु
		.enable_reg = 0x1b50,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_1_mstr_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_pipe_clk = अणु
	.halt_reg = 0x1b58,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1b58,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_1_pipe_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"pcie_1_pipe_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_slv_axi_clk = अणु
	.halt_reg = 0x1b48,
	.clkr = अणु
		.enable_reg = 0x1b48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pcie_1_slv_axi_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm2_clk = अणु
	.halt_reg = 0x0ccc,
	.clkr = अणु
		.enable_reg = 0x0ccc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pdm2_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"pdm2_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm_ahb_clk = अणु
	.halt_reg = 0x0cc4,
	.clkr = अणु
		.enable_reg = 0x0cc4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_pdm_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_apps_clk = अणु
	.halt_reg = 0x04c4,
	.clkr = अणु
		.enable_reg = 0x04c4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc1_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"sdcc1_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_ahb_clk = अणु
	.halt_reg = 0x04c8,
	.clkr = अणु
		.enable_reg = 0x04c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc2_ahb_clk = अणु
	.halt_reg = 0x0508,
	.clkr = अणु
		.enable_reg = 0x0508,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc2_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc2_apps_clk = अणु
	.halt_reg = 0x0504,
	.clkr = अणु
		.enable_reg = 0x0504,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc2_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"sdcc2_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc3_ahb_clk = अणु
	.halt_reg = 0x0548,
	.clkr = अणु
		.enable_reg = 0x0548,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc3_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc3_apps_clk = अणु
	.halt_reg = 0x0544,
	.clkr = अणु
		.enable_reg = 0x0544,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc3_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"sdcc3_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc4_ahb_clk = अणु
	.halt_reg = 0x0588,
	.clkr = अणु
		.enable_reg = 0x0588,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc4_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc4_apps_clk = अणु
	.halt_reg = 0x0584,
	.clkr = अणु
		.enable_reg = 0x0584,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sdcc4_apps_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"sdcc4_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sys_noc_ufs_axi_clk = अणु
	.halt_reg = 0x1d7c,
	.clkr = अणु
		.enable_reg = 0x1d7c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sys_noc_ufs_axi_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sys_noc_usb3_axi_clk = अणु
	.halt_reg = 0x03fc,
	.clkr = अणु
		.enable_reg = 0x03fc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_sys_noc_usb3_axi_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_ahb_clk = अणु
	.halt_reg = 0x0d84,
	.clkr = अणु
		.enable_reg = 0x0d84,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_tsif_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_ref_clk = अणु
	.halt_reg = 0x0d88,
	.clkr = अणु
		.enable_reg = 0x0d88,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_tsif_ref_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"tsif_ref_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_ahb_clk = अणु
	.halt_reg = 0x1d4c,
	.clkr = अणु
		.enable_reg = 0x1d4c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_axi_clk = अणु
	.halt_reg = 0x1d48,
	.clkr = अणु
		.enable_reg = 0x1d48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_axi_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_cfg_clk = अणु
	.halt_reg = 0x1d54,
	.clkr = अणु
		.enable_reg = 0x1d54,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_rx_cfg_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_symbol_0_clk = अणु
	.halt_reg = 0x1d60,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1d60,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_rx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_symbol_1_clk = अणु
	.halt_reg = 0x1d64,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1d64,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_rx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_cfg_clk = अणु
	.halt_reg = 0x1d50,
	.clkr = अणु
		.enable_reg = 0x1d50,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_tx_cfg_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_symbol_0_clk = अणु
	.halt_reg = 0x1d58,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1d58,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_tx_symbol_0_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_symbol_1_clk = अणु
	.halt_reg = 0x1d5c,
	.halt_check = BRANCH_HALT_DELAY,
	.clkr = अणु
		.enable_reg = 0x1d5c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_ufs_tx_symbol_1_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2_hs_phy_sleep_clk = अणु
	.halt_reg = 0x04ac,
	.clkr = अणु
		.enable_reg = 0x04ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb2_hs_phy_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_master_clk = अणु
	.halt_reg = 0x03c8,
	.clkr = अणु
		.enable_reg = 0x03c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb30_master_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x03d0,
	.clkr = अणु
		.enable_reg = 0x03d0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb30_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"usb30_mock_utmi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sleep_clk = अणु
	.halt_reg = 0x03cc,
	.clkr = अणु
		.enable_reg = 0x03cc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb30_sleep_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb3_phy_aux_clk = अणु
	.halt_reg = 0x1408,
	.clkr = अणु
		.enable_reg = 0x1408,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb3_phy_aux_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"usb3_phy_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_ahb_clk = अणु
	.halt_reg = 0x0488,
	.clkr = अणु
		.enable_reg = 0x0488,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb_hs_ahb_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_प्रणाली_clk = अणु
	.halt_reg = 0x0484,
	.clkr = अणु
		.enable_reg = 0x0484,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb_hs_system_clk",
			.parent_names = (स्थिर अक्षर *[]) अणु
				"usb_hs_system_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_phy_cfg_ahb2phy_clk = अणु
	.halt_reg = 0x1a84,
	.clkr = अणु
		.enable_reg = 0x1a84,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)
		अणु
			.name = "gcc_usb_phy_cfg_ahb2phy_clk",
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc pcie_gdsc = अणु
		.gdscr = 0x1e18,
		.pd = अणु
			.name = "pcie",
		पूर्ण,
		.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc pcie_0_gdsc = अणु
		.gdscr = 0x1ac4,
		.pd = अणु
			.name = "pcie_0",
		पूर्ण,
		.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc pcie_1_gdsc = अणु
		.gdscr = 0x1b44,
		.pd = अणु
			.name = "pcie_1",
		पूर्ण,
		.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc usb30_gdsc = अणु
		.gdscr = 0x3c4,
		.pd = अणु
			.name = "usb30",
		पूर्ण,
		.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc ufs_gdsc = अणु
		.gdscr = 0x1d44,
		.pd = अणु
			.name = "ufs",
		पूर्ण,
		.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_msm8994_घड़ीs[] = अणु
	[GPLL0_EARLY] = &gpll0_early.clkr,
	[GPLL0] = &gpll0.clkr,
	[GPLL4_EARLY] = &gpll4_early.clkr,
	[GPLL4] = &gpll4.clkr,
	[UFS_AXI_CLK_SRC] = &ufs_axi_clk_src.clkr,
	[USB30_MASTER_CLK_SRC] = &usb30_master_clk_src.clkr,
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
	[BLSP1_UART3_APPS_CLK_SRC] = &blsp1_uart3_apps_clk_src.clkr,
	[BLSP1_UART4_APPS_CLK_SRC] = &blsp1_uart4_apps_clk_src.clkr,
	[BLSP1_UART5_APPS_CLK_SRC] = &blsp1_uart5_apps_clk_src.clkr,
	[BLSP1_UART6_APPS_CLK_SRC] = &blsp1_uart6_apps_clk_src.clkr,
	[BLSP2_QUP1_I2C_APPS_CLK_SRC] = &blsp2_qup1_i2c_apps_clk_src.clkr,
	[BLSP2_QUP1_SPI_APPS_CLK_SRC] = &blsp2_qup1_spi_apps_clk_src.clkr,
	[BLSP2_QUP2_I2C_APPS_CLK_SRC] = &blsp2_qup2_i2c_apps_clk_src.clkr,
	[BLSP2_QUP2_SPI_APPS_CLK_SRC] = &blsp2_qup2_spi_apps_clk_src.clkr,
	[BLSP2_QUP3_I2C_APPS_CLK_SRC] = &blsp2_qup3_i2c_apps_clk_src.clkr,
	[BLSP2_QUP3_SPI_APPS_CLK_SRC] = &blsp2_qup3_spi_apps_clk_src.clkr,
	[BLSP2_QUP4_I2C_APPS_CLK_SRC] = &blsp2_qup4_i2c_apps_clk_src.clkr,
	[BLSP2_QUP4_SPI_APPS_CLK_SRC] = &blsp2_qup4_spi_apps_clk_src.clkr,
	[BLSP2_QUP5_I2C_APPS_CLK_SRC] = &blsp2_qup5_i2c_apps_clk_src.clkr,
	[BLSP2_QUP5_SPI_APPS_CLK_SRC] = &blsp2_qup5_spi_apps_clk_src.clkr,
	[BLSP2_QUP6_I2C_APPS_CLK_SRC] = &blsp2_qup6_i2c_apps_clk_src.clkr,
	[BLSP2_QUP6_SPI_APPS_CLK_SRC] = &blsp2_qup6_spi_apps_clk_src.clkr,
	[BLSP2_UART1_APPS_CLK_SRC] = &blsp2_uart1_apps_clk_src.clkr,
	[BLSP2_UART2_APPS_CLK_SRC] = &blsp2_uart2_apps_clk_src.clkr,
	[BLSP2_UART3_APPS_CLK_SRC] = &blsp2_uart3_apps_clk_src.clkr,
	[BLSP2_UART4_APPS_CLK_SRC] = &blsp2_uart4_apps_clk_src.clkr,
	[BLSP2_UART5_APPS_CLK_SRC] = &blsp2_uart5_apps_clk_src.clkr,
	[BLSP2_UART6_APPS_CLK_SRC] = &blsp2_uart6_apps_clk_src.clkr,
	[GP1_CLK_SRC] = &gp1_clk_src.clkr,
	[GP2_CLK_SRC] = &gp2_clk_src.clkr,
	[GP3_CLK_SRC] = &gp3_clk_src.clkr,
	[PCIE_0_AUX_CLK_SRC] = &pcie_0_aux_clk_src.clkr,
	[PCIE_0_PIPE_CLK_SRC] = &pcie_0_pipe_clk_src.clkr,
	[PCIE_1_AUX_CLK_SRC] = &pcie_1_aux_clk_src.clkr,
	[PCIE_1_PIPE_CLK_SRC] = &pcie_1_pipe_clk_src.clkr,
	[PDM2_CLK_SRC] = &pdm2_clk_src.clkr,
	[SDCC1_APPS_CLK_SRC] = &sdcc1_apps_clk_src.clkr,
	[SDCC2_APPS_CLK_SRC] = &sdcc2_apps_clk_src.clkr,
	[SDCC3_APPS_CLK_SRC] = &sdcc3_apps_clk_src.clkr,
	[SDCC4_APPS_CLK_SRC] = &sdcc4_apps_clk_src.clkr,
	[TSIF_REF_CLK_SRC] = &tsअगर_ref_clk_src.clkr,
	[USB30_MOCK_UTMI_CLK_SRC] = &usb30_mock_uपंचांगi_clk_src.clkr,
	[USB3_PHY_AUX_CLK_SRC] = &usb3_phy_aux_clk_src.clkr,
	[USB_HS_SYSTEM_CLK_SRC] = &usb_hs_प्रणाली_clk_src.clkr,
	[GCC_BLSP1_AHB_CLK] = &gcc_blsp1_ahb_clk.clkr,
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
	[GCC_BLSP1_UART3_APPS_CLK] = &gcc_blsp1_uart3_apps_clk.clkr,
	[GCC_BLSP1_UART4_APPS_CLK] = &gcc_blsp1_uart4_apps_clk.clkr,
	[GCC_BLSP1_UART5_APPS_CLK] = &gcc_blsp1_uart5_apps_clk.clkr,
	[GCC_BLSP1_UART6_APPS_CLK] = &gcc_blsp1_uart6_apps_clk.clkr,
	[GCC_BLSP2_AHB_CLK] = &gcc_blsp2_ahb_clk.clkr,
	[GCC_BLSP2_QUP1_I2C_APPS_CLK] = &gcc_blsp2_qup1_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP1_SPI_APPS_CLK] = &gcc_blsp2_qup1_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP2_I2C_APPS_CLK] = &gcc_blsp2_qup2_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP2_SPI_APPS_CLK] = &gcc_blsp2_qup2_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP3_I2C_APPS_CLK] = &gcc_blsp2_qup3_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP3_SPI_APPS_CLK] = &gcc_blsp2_qup3_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP4_I2C_APPS_CLK] = &gcc_blsp2_qup4_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP4_SPI_APPS_CLK] = &gcc_blsp2_qup4_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP5_I2C_APPS_CLK] = &gcc_blsp2_qup5_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP5_SPI_APPS_CLK] = &gcc_blsp2_qup5_spi_apps_clk.clkr,
	[GCC_BLSP2_QUP6_I2C_APPS_CLK] = &gcc_blsp2_qup6_i2c_apps_clk.clkr,
	[GCC_BLSP2_QUP6_SPI_APPS_CLK] = &gcc_blsp2_qup6_spi_apps_clk.clkr,
	[GCC_BLSP2_UART1_APPS_CLK] = &gcc_blsp2_uart1_apps_clk.clkr,
	[GCC_BLSP2_UART2_APPS_CLK] = &gcc_blsp2_uart2_apps_clk.clkr,
	[GCC_BLSP2_UART3_APPS_CLK] = &gcc_blsp2_uart3_apps_clk.clkr,
	[GCC_BLSP2_UART4_APPS_CLK] = &gcc_blsp2_uart4_apps_clk.clkr,
	[GCC_BLSP2_UART5_APPS_CLK] = &gcc_blsp2_uart5_apps_clk.clkr,
	[GCC_BLSP2_UART6_APPS_CLK] = &gcc_blsp2_uart6_apps_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_LPASS_Q6_AXI_CLK] = &gcc_lpass_q6_axi_clk.clkr,
	[GCC_MSS_Q6_BIMC_AXI_CLK] = &gcc_mss_q6_bimc_axi_clk.clkr,
	[GCC_PCIE_0_AUX_CLK] = &gcc_pcie_0_aux_clk.clkr,
	[GCC_PCIE_0_CFG_AHB_CLK] = &gcc_pcie_0_cfg_ahb_clk.clkr,
	[GCC_PCIE_0_MSTR_AXI_CLK] = &gcc_pcie_0_mstr_axi_clk.clkr,
	[GCC_PCIE_0_PIPE_CLK] = &gcc_pcie_0_pipe_clk.clkr,
	[GCC_PCIE_0_SLV_AXI_CLK] = &gcc_pcie_0_slv_axi_clk.clkr,
	[GCC_PCIE_1_AUX_CLK] = &gcc_pcie_1_aux_clk.clkr,
	[GCC_PCIE_1_CFG_AHB_CLK] = &gcc_pcie_1_cfg_ahb_clk.clkr,
	[GCC_PCIE_1_MSTR_AXI_CLK] = &gcc_pcie_1_mstr_axi_clk.clkr,
	[GCC_PCIE_1_PIPE_CLK] = &gcc_pcie_1_pipe_clk.clkr,
	[GCC_PCIE_1_SLV_AXI_CLK] = &gcc_pcie_1_slv_axi_clk.clkr,
	[GCC_PDM2_CLK] = &gcc_pdm2_clk.clkr,
	[GCC_PDM_AHB_CLK] = &gcc_pdm_ahb_clk.clkr,
	[GCC_SDCC1_AHB_CLK] = &gcc_sdcc1_ahb_clk.clkr,
	[GCC_SDCC1_APPS_CLK] = &gcc_sdcc1_apps_clk.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_SDCC3_AHB_CLK] = &gcc_sdcc3_ahb_clk.clkr,
	[GCC_SDCC3_APPS_CLK] = &gcc_sdcc3_apps_clk.clkr,
	[GCC_SDCC4_AHB_CLK] = &gcc_sdcc4_ahb_clk.clkr,
	[GCC_SDCC4_APPS_CLK] = &gcc_sdcc4_apps_clk.clkr,
	[GCC_SYS_NOC_UFS_AXI_CLK] = &gcc_sys_noc_ufs_axi_clk.clkr,
	[GCC_SYS_NOC_USB3_AXI_CLK] = &gcc_sys_noc_usb3_axi_clk.clkr,
	[GCC_TSIF_AHB_CLK] = &gcc_tsअगर_ahb_clk.clkr,
	[GCC_TSIF_REF_CLK] = &gcc_tsअगर_ref_clk.clkr,
	[GCC_UFS_AHB_CLK] = &gcc_ufs_ahb_clk.clkr,
	[GCC_UFS_AXI_CLK] = &gcc_ufs_axi_clk.clkr,
	[GCC_UFS_RX_CFG_CLK] = &gcc_ufs_rx_cfg_clk.clkr,
	[GCC_UFS_RX_SYMBOL_0_CLK] = &gcc_ufs_rx_symbol_0_clk.clkr,
	[GCC_UFS_RX_SYMBOL_1_CLK] = &gcc_ufs_rx_symbol_1_clk.clkr,
	[GCC_UFS_TX_CFG_CLK] = &gcc_ufs_tx_cfg_clk.clkr,
	[GCC_UFS_TX_SYMBOL_0_CLK] = &gcc_ufs_tx_symbol_0_clk.clkr,
	[GCC_UFS_TX_SYMBOL_1_CLK] = &gcc_ufs_tx_symbol_1_clk.clkr,
	[GCC_USB2_HS_PHY_SLEEP_CLK] = &gcc_usb2_hs_phy_sleep_clk.clkr,
	[GCC_USB30_MASTER_CLK] = &gcc_usb30_master_clk.clkr,
	[GCC_USB30_MOCK_UTMI_CLK] = &gcc_usb30_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SLEEP_CLK] = &gcc_usb30_sleep_clk.clkr,
	[GCC_USB3_PHY_AUX_CLK] = &gcc_usb3_phy_aux_clk.clkr,
	[GCC_USB_HS_AHB_CLK] = &gcc_usb_hs_ahb_clk.clkr,
	[GCC_USB_HS_SYSTEM_CLK] = &gcc_usb_hs_प्रणाली_clk.clkr,
	[GCC_USB_PHY_CFG_AHB2PHY_CLK] = &gcc_usb_phy_cfg_ahb2phy_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *gcc_msm8994_gdscs[] = अणु
	[PCIE_GDSC] = &pcie_gdsc,
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_1_GDSC] = &pcie_1_gdsc,
	[USB30_GDSC] = &usb30_gdsc,
	[UFS_GDSC] = &ufs_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_msm8994_resets[] = अणु
	[USB3_PHY_RESET] = अणु 0x1400 पूर्ण,
	[USB3PHY_PHY_RESET] = अणु 0x1404 पूर्ण,
	[PCIE_PHY_0_RESET] = अणु 0x1b18 पूर्ण,
	[PCIE_PHY_1_RESET] = अणु 0x1b98 पूर्ण,
	[QUSB2_PHY_RESET] = अणु 0x04b8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_msm8994_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x2000,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_msm8994_desc = अणु
	.config = &gcc_msm8994_regmap_config,
	.clks = gcc_msm8994_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_msm8994_घड़ीs),
	.resets = gcc_msm8994_resets,
	.num_resets = ARRAY_SIZE(gcc_msm8994_resets),
	.gdscs = gcc_msm8994_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_msm8994_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_msm8994_match_table[] = अणु
	अणु .compatible = "qcom,gcc-msm8994" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_msm8994_match_table);

अटल पूर्णांक gcc_msm8994_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk;

	clk = devm_clk_रेजिस्टर(dev, &xo.hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	वापस qcom_cc_probe(pdev, &gcc_msm8994_desc);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_msm8994_driver = अणु
	.probe		= gcc_msm8994_probe,
	.driver		= अणु
		.name	= "gcc-msm8994",
		.of_match_table = gcc_msm8994_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_msm8994_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_msm8994_driver);
पूर्ण
core_initcall(gcc_msm8994_init);

अटल व्योम __निकास gcc_msm8994_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_msm8994_driver);
पूर्ण
module_निकास(gcc_msm8994_निकास);

MODULE_DESCRIPTION("Qualcomm GCC MSM8994 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-msm8994");
