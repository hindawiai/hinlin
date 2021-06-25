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
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/घड़ी/qcom,gcc-apq8084.h>
#समावेश <dt-bindings/reset/qcom,gcc-apq8084.h>

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
	P_GPLL1,
	P_GPLL4,
	P_PCIE_0_1_PIPE_CLK,
	P_SATA_ASIC0_CLK,
	P_SATA_RX_CLK,
	P_SLEEP_CLK,
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0[] = अणु
	"xo",
	"gpll0_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_gpll0_gpll4_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL0, 1 पूर्ण,
	अणु P_GPLL4, 5 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_gpll0_gpll4[] = अणु
	"xo",
	"gpll0_vote",
	"gpll4_vote",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_sata_asic0_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_SATA_ASIC0_CLK, 2 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_sata_asic0[] = अणु
	"xo",
	"sata_asic0_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_sata_rx_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_SATA_RX_CLK, 2पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_sata_rx[] = अणु
	"xo",
	"sata_rx_clk",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_pcie_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_PCIE_0_1_PIPE_CLK, 2 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_pcie[] = अणु
	"xo",
	"pcie_pipe",
पूर्ण;

अटल स्थिर काष्ठा parent_map gcc_xo_pcie_sleep_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_SLEEP_CLK, 6 पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_xo_pcie_sleep[] = अणु
	"xo",
	"sleep_clk_src",
पूर्ण;

अटल काष्ठा clk_pll gpll0 = अणु
	.l_reg = 0x0004,
	.m_reg = 0x0008,
	.n_reg = 0x000c,
	.config_reg = 0x0014,
	.mode_reg = 0x0000,
	.status_reg = 0x001c,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap gpll0_vote = अणु
	.enable_reg = 0x1480,
	.enable_mask = BIT(0),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll0_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll0" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 config_noc_clk_src = अणु
	.cmd_rcgr = 0x0150,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "config_noc_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 periph_noc_clk_src = अणु
	.cmd_rcgr = 0x0190,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "periph_noc_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 प्रणाली_noc_clk_src = अणु
	.cmd_rcgr = 0x0120,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "system_noc_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll gpll1 = अणु
	.l_reg = 0x0044,
	.m_reg = 0x0048,
	.n_reg = 0x004c,
	.config_reg = 0x0054,
	.mode_reg = 0x0040,
	.status_reg = 0x005c,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap gpll1_vote = अणु
	.enable_reg = 0x1480,
	.enable_mask = BIT(1),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll1_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll1" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_pll gpll4 = अणु
	.l_reg = 0x1dc4,
	.m_reg = 0x1dc8,
	.n_reg = 0x1dcc,
	.config_reg = 0x1dd4,
	.mode_reg = 0x1dc0,
	.status_reg = 0x1ddc,
	.status_bit = 17,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll4",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_regmap gpll4_vote = अणु
	.enable_reg = 0x1480,
	.enable_mask = BIT(4),
	.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gpll4_vote",
		.parent_names = (स्थिर अक्षर *[])अणु "gpll4" पूर्ण,
		.num_parents = 1,
		.ops = &clk_pll_vote_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ufs_axi_clk[] = अणु
	F(100000000, P_GPLL0, 6, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(240000000, P_GPLL0, 2.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ufs_axi_clk_src = अणु
	.cmd_rcgr = 0x1d64,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_ufs_axi_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ufs_axi_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_master_clk[] = अणु
	F(125000000, P_GPLL0, 1, 5, 24),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_master_clk_src = अणु
	.cmd_rcgr = 0x03d4,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb30_master_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_master_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_sec_master_clk[] = अणु
	F(125000000, P_GPLL0, 1, 5, 24),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_sec_master_clk_src = अणु
	.cmd_rcgr = 0x1bd4,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb30_sec_master_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_sec_master_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x1bd0,
	.clkr = अणु
		.enable_reg = 0x1bd0,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_sec_mock_utmi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_sleep_clk = अणु
	.halt_reg = 0x1bcc,
	.clkr = अणु
		.enable_reg = 0x1bcc,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_i2c_apps_clk_src = अणु
	.cmd_rcgr = 0x0660,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup1_i2c_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk[] = अणु
	F(960000, P_XO, 10, 1, 2),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(15000000, P_GPLL0, 10, 1, 4),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPLL0, 12, 1, 2),
	F(50000000, P_GPLL0, 12, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 blsp1_qup1_spi_apps_clk_src = अणु
	.cmd_rcgr = 0x064c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp1_qup6_spi_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_blsp1_2_uart1_6_apps_clk[] = अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_i2c_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_qup1_6_spi_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_blsp1_2_uart1_6_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "blsp2_uart6_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ce1_clk[] = अणु
	F(50000000, P_GPLL0, 12, 0, 0),
	F(85710000, P_GPLL0, 7, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(171430000, P_GPLL0, 3.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ce1_clk_src = अणु
	.cmd_rcgr = 0x1050,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_ce1_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ce1_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ce2_clk[] = अणु
	F(50000000, P_GPLL0, 12, 0, 0),
	F(85710000, P_GPLL0, 7, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(171430000, P_GPLL0, 3.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ce2_clk_src = अणु
	.cmd_rcgr = 0x1090,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_ce2_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ce2_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_ce3_clk[] = अणु
	F(50000000, P_GPLL0, 12, 0, 0),
	F(85710000, P_GPLL0, 7, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(171430000, P_GPLL0, 3.5, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 ce3_clk_src = अणु
	.cmd_rcgr = 0x1d10,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_ce3_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "ce3_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_gp_clk[] = अणु
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
	.freq_tbl = ftbl_gcc_gp_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp1_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp2_clk_src = अणु
	.cmd_rcgr = 0x1944,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_gp_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp2_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 gp3_clk_src = अणु
	.cmd_rcgr = 0x1984,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_gp_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "gp3_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_0_1_aux_clk[] = अणु
	F(1010000, P_XO, 1, 1, 19),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_0_aux_clk_src = अणु
	.cmd_rcgr = 0x1b2c,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_pcie_sleep_map,
	.freq_tbl = ftbl_gcc_pcie_0_1_aux_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_0_aux_clk_src",
		.parent_names = gcc_xo_pcie_sleep,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_1_aux_clk_src = अणु
	.cmd_rcgr = 0x1bac,
	.mnd_width = 16,
	.hid_width = 5,
	.parent_map = gcc_xo_pcie_sleep_map,
	.freq_tbl = ftbl_gcc_pcie_0_1_aux_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_1_aux_clk_src",
		.parent_names = gcc_xo_pcie_sleep,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pcie_0_1_pipe_clk[] = अणु
	F(125000000, P_PCIE_0_1_PIPE_CLK, 1, 0, 0),
	F(250000000, P_PCIE_0_1_PIPE_CLK, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_0_pipe_clk_src = अणु
	.cmd_rcgr = 0x1b18,
	.hid_width = 5,
	.parent_map = gcc_xo_pcie_map,
	.freq_tbl = ftbl_gcc_pcie_0_1_pipe_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_0_pipe_clk_src",
		.parent_names = gcc_xo_pcie,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 pcie_1_pipe_clk_src = अणु
	.cmd_rcgr = 0x1b98,
	.hid_width = 5,
	.parent_map = gcc_xo_pcie_map,
	.freq_tbl = ftbl_gcc_pcie_0_1_pipe_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pcie_1_pipe_clk_src",
		.parent_names = gcc_xo_pcie,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_pdm2_clk[] = अणु
	F(60000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 pdm2_clk_src = अणु
	.cmd_rcgr = 0x0cd0,
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

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sata_asic0_clk[] = अणु
	F(75000000, P_SATA_ASIC0_CLK, 1, 0, 0),
	F(150000000, P_SATA_ASIC0_CLK, 1, 0, 0),
	F(300000000, P_SATA_ASIC0_CLK, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sata_asic0_clk_src = अणु
	.cmd_rcgr = 0x1c94,
	.hid_width = 5,
	.parent_map = gcc_xo_sata_asic0_map,
	.freq_tbl = ftbl_gcc_sata_asic0_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sata_asic0_clk_src",
		.parent_names = gcc_xo_sata_asic0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sata_pmalive_clk[] = अणु
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sata_pmalive_clk_src = अणु
	.cmd_rcgr = 0x1c80,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_sata_pmalive_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sata_pmalive_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sata_rx_clk[] = अणु
	F(75000000, P_SATA_RX_CLK, 1, 0, 0),
	F(150000000, P_SATA_RX_CLK, 1, 0, 0),
	F(300000000, P_SATA_RX_CLK, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sata_rx_clk_src = अणु
	.cmd_rcgr = 0x1ca8,
	.hid_width = 5,
	.parent_map = gcc_xo_sata_rx_map,
	.freq_tbl = ftbl_gcc_sata_rx_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sata_rx_clk_src",
		.parent_names = gcc_xo_sata_rx,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sata_rx_oob_clk[] = अणु
	F(100000000, P_GPLL0, 6, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sata_rx_oob_clk_src = अणु
	.cmd_rcgr = 0x1c5c,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_sata_rx_oob_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sata_rx_oob_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_sdcc1_4_apps_clk[] = अणु
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPLL0, 15, 1, 2),
	F(25000000, P_GPLL0, 12, 1, 2),
	F(50000000, P_GPLL0, 12, 0, 0),
	F(100000000, P_GPLL0, 6, 0, 0),
	F(192000000, P_GPLL4, 4, 0, 0),
	F(200000000, P_GPLL0, 3, 0, 0),
	F(384000000, P_GPLL4, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc1_apps_clk_src = अणु
	.cmd_rcgr = 0x04d0,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_gpll4_map,
	.freq_tbl = ftbl_gcc_sdcc1_4_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc1_apps_clk_src",
		.parent_names = gcc_xo_gpll0_gpll4,
		.num_parents = 3,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_rcg2 sdcc2_apps_clk_src = अणु
	.cmd_rcgr = 0x0510,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_sdcc1_4_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_sdcc1_4_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
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
	.freq_tbl = ftbl_gcc_sdcc1_4_apps_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "sdcc4_apps_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_न्यूनमान_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_tsअगर_ref_clk[] = अणु
	F(105000, P_XO, 2, 1, 91),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 tsअगर_ref_clk_src = अणु
	.cmd_rcgr = 0x0d90,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_tsअगर_ref_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "tsif_ref_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_mock_uपंचांगi_clk[] = अणु
	F(60000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x03e8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb30_mock_uपंचांगi_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_mock_utmi_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb30_sec_mock_uपंचांगi_clk[] = अणु
	F(125000000, P_GPLL0, 1, 5, 24),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb30_sec_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x1be8,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb30_sec_mock_uपंचांगi_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb30_sec_mock_utmi_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hs_प्रणाली_clk[] = अणु
	F(75000000, P_GPLL0, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hs_प्रणाली_clk_src = अणु
	.cmd_rcgr = 0x0490,
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

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hsic_clk[] = अणु
	F(480000000, P_GPLL1, 1, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा parent_map usb_hsic_clk_src_map[] = अणु
	अणु P_XO, 0 पूर्ण,
	अणु P_GPLL1, 4 पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hsic_clk_src = अणु
	.cmd_rcgr = 0x0440,
	.hid_width = 5,
	.parent_map = usb_hsic_clk_src_map,
	.freq_tbl = ftbl_gcc_usb_hsic_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb_hsic_clk_src",
		.parent_names = (स्थिर अक्षर *[])अणु
			"xo",
			"gpll1_vote",
		पूर्ण,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hsic_ahb_clk_src[] = अणु
	F(60000000, P_GPLL1, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hsic_ahb_clk_src = अणु
	.cmd_rcgr = 0x046c,
	.mnd_width = 8,
	.hid_width = 5,
	.parent_map = usb_hsic_clk_src_map,
	.freq_tbl = ftbl_gcc_usb_hsic_ahb_clk_src,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb_hsic_ahb_clk_src",
		.parent_names = (स्थिर अक्षर *[])अणु
			"xo",
			"gpll1_vote",
		पूर्ण,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hsic_io_cal_clk[] = अणु
	F(9600000, P_XO, 2, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hsic_io_cal_clk_src = अणु
	.cmd_rcgr = 0x0458,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb_hsic_io_cal_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb_hsic_io_cal_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hsic_mock_uपंचांगi_clk = अणु
	.halt_reg = 0x1f14,
	.clkr = अणु
		.enable_reg = 0x1f14,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hsic_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb_hsic_mock_utmi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hsic_mock_uपंचांगi_clk[] = अणु
	F(60000000, P_GPLL0, 10, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hsic_mock_uपंचांगi_clk_src = अणु
	.cmd_rcgr = 0x1f00,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb_hsic_mock_uपंचांगi_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb_hsic_mock_utmi_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 1,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा freq_tbl ftbl_gcc_usb_hsic_प्रणाली_clk[] = अणु
	F(75000000, P_GPLL0, 8, 0, 0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk_rcg2 usb_hsic_प्रणाली_clk_src = अणु
	.cmd_rcgr = 0x041c,
	.hid_width = 5,
	.parent_map = gcc_xo_gpll0_map,
	.freq_tbl = ftbl_gcc_usb_hsic_प्रणाली_clk,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "usb_hsic_system_clk_src",
		.parent_names = gcc_xo_gpll0,
		.num_parents = 2,
		.ops = &clk_rcg2_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_bam_dma_ahb_clk = अणु
	.halt_reg = 0x0d44,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(12),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_bam_dma_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_ahb_clk = अणु
	.halt_reg = 0x05c4,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(17),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp1_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x0648,
	.clkr = अणु
		.enable_reg = 0x0648,
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
	.halt_reg = 0x0644,
	.clkr = अणु
		.enable_reg = 0x0644,
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
	.halt_reg = 0x06c8,
	.clkr = अणु
		.enable_reg = 0x06c8,
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
	.halt_reg = 0x06c4,
	.clkr = अणु
		.enable_reg = 0x06c4,
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
	.halt_reg = 0x0748,
	.clkr = अणु
		.enable_reg = 0x0748,
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
	.halt_reg = 0x0744,
	.clkr = अणु
		.enable_reg = 0x0744,
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
	.halt_reg = 0x07c8,
	.clkr = अणु
		.enable_reg = 0x07c8,
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
	.halt_reg = 0x07c4,
	.clkr = अणु
		.enable_reg = 0x07c4,
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
	.halt_reg = 0x0848,
	.clkr = अणु
		.enable_reg = 0x0848,
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
	.halt_reg = 0x0844,
	.clkr = अणु
		.enable_reg = 0x0844,
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
	.halt_reg = 0x08c8,
	.clkr = अणु
		.enable_reg = 0x08c8,
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
	.halt_reg = 0x08c4,
	.clkr = अणु
		.enable_reg = 0x08c4,
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
	.halt_reg = 0x0684,
	.clkr = अणु
		.enable_reg = 0x0684,
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
	.halt_reg = 0x0704,
	.clkr = अणु
		.enable_reg = 0x0704,
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

अटल काष्ठा clk_branch gcc_blsp1_uart3_apps_clk = अणु
	.halt_reg = 0x0784,
	.clkr = अणु
		.enable_reg = 0x0784,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart3_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart4_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart5_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp1_uart6_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_blsp2_qup1_i2c_apps_clk = अणु
	.halt_reg = 0x0988,
	.clkr = अणु
		.enable_reg = 0x0988,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup1_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup1_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup2_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup2_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup3_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup3_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup4_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup4_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup5_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup5_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup6_i2c_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_qup6_spi_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart1_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart2_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart3_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart4_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart5_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_blsp2_uart6_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"blsp2_uart6_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_boot_rom_ahb_clk = अणु
	.halt_reg = 0x0e04,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(10),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_boot_rom_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce1_ahb_clk = अणु
	.halt_reg = 0x104c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(3),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce1_axi_clk = अणु
	.halt_reg = 0x1048,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(4),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce1_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce1_clk = अणु
	.halt_reg = 0x1050,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(5),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ce1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce2_ahb_clk = अणु
	.halt_reg = 0x108c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce2_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce2_axi_clk = अणु
	.halt_reg = 0x1088,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(1),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce2_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce2_clk = अणु
	.halt_reg = 0x1090,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(2),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce2_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ce2_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce3_ahb_clk = अणु
	.halt_reg = 0x1d0c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1d0c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce3_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce3_axi_clk = अणु
	.halt_reg = 0x1088,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1d08,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce3_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"system_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ce3_clk = अणु
	.halt_reg = 0x1090,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1d04,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ce3_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ce3_clk_src",
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
	.halt_reg = 0x1940,
	.clkr = अणु
		.enable_reg = 0x1940,
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
	.halt_reg = 0x1980,
	.clkr = अणु
		.enable_reg = 0x1980,
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

अटल काष्ठा clk_branch gcc_ocmem_noc_cfg_ahb_clk = अणु
	.halt_reg = 0x0248,
	.clkr = अणु
		.enable_reg = 0x0248,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ocmem_noc_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_aux_clk = अणु
	.halt_reg = 0x1b10,
	.clkr = अणु
		.enable_reg = 0x1b10,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_aux_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcie_0_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_cfg_ahb_clk = अणु
	.halt_reg = 0x1b0c,
	.clkr = अणु
		.enable_reg = 0x1b0c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_mstr_axi_clk = अणु
	.halt_reg = 0x1b08,
	.clkr = अणु
		.enable_reg = 0x1b08,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_mstr_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_pipe_clk = अणु
	.halt_reg = 0x1b14,
	.clkr = अणु
		.enable_reg = 0x1b14,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_pipe_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcie_0_pipe_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_0_slv_axi_clk = अणु
	.halt_reg = 0x1b04,
	.clkr = अणु
		.enable_reg = 0x1b04,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_0_slv_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_aux_clk = अणु
	.halt_reg = 0x1b90,
	.clkr = अणु
		.enable_reg = 0x1b90,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_aux_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcie_1_aux_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_cfg_ahb_clk = अणु
	.halt_reg = 0x1b8c,
	.clkr = अणु
		.enable_reg = 0x1b8c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_mstr_axi_clk = अणु
	.halt_reg = 0x1b88,
	.clkr = अणु
		.enable_reg = 0x1b88,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_mstr_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_pipe_clk = अणु
	.halt_reg = 0x1b94,
	.clkr = अणु
		.enable_reg = 0x1b94,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_pipe_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"pcie_1_pipe_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pcie_1_slv_axi_clk = अणु
	.halt_reg = 0x1b84,
	.clkr = अणु
		.enable_reg = 0x1b84,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pcie_1_slv_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_pdm2_clk = अणु
	.halt_reg = 0x0ccc,
	.clkr = अणु
		.enable_reg = 0x0ccc,
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
	.halt_reg = 0x0cc4,
	.clkr = अणु
		.enable_reg = 0x0cc4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_pdm_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_periph_noc_usb_hsic_ahb_clk = अणु
	.halt_reg = 0x01a4,
	.clkr = अणु
		.enable_reg = 0x01a4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_periph_noc_usb_hsic_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb_hsic_ahb_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_prng_ahb_clk = अणु
	.halt_reg = 0x0d04,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = अणु
		.enable_reg = 0x1484,
		.enable_mask = BIT(13),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_prng_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sata_asic0_clk = अणु
	.halt_reg = 0x1c54,
	.clkr = अणु
		.enable_reg = 0x1c54,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sata_asic0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sata_asic0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sata_axi_clk = अणु
	.halt_reg = 0x1c44,
	.clkr = अणु
		.enable_reg = 0x1c44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sata_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sata_cfg_ahb_clk = अणु
	.halt_reg = 0x1c48,
	.clkr = अणु
		.enable_reg = 0x1c48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sata_cfg_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sata_pmalive_clk = अणु
	.halt_reg = 0x1c50,
	.clkr = अणु
		.enable_reg = 0x1c50,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sata_pmalive_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sata_pmalive_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sata_rx_clk = अणु
	.halt_reg = 0x1c58,
	.clkr = अणु
		.enable_reg = 0x1c58,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sata_rx_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sata_rx_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sata_rx_oob_clk = अणु
	.halt_reg = 0x1c4c,
	.clkr = अणु
		.enable_reg = 0x1c4c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sata_rx_oob_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sata_rx_oob_clk_src",
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_apps_clk = अणु
	.halt_reg = 0x04c4,
	.clkr = अणु
		.enable_reg = 0x04c4,
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

अटल काष्ठा clk_branch gcc_sdcc1_cdccal_ff_clk = अणु
	.halt_reg = 0x04e8,
	.clkr = अणु
		.enable_reg = 0x04e8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_cdccal_ff_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"xo"
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sdcc1_cdccal_sleep_clk = अणु
	.halt_reg = 0x04e4,
	.clkr = अणु
		.enable_reg = 0x04e4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc1_cdccal_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src"
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
		.hw.init = &(काष्ठा clk_init_data)अणु
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

अटल काष्ठा clk_branch gcc_sdcc3_ahb_clk = अणु
	.halt_reg = 0x0548,
	.clkr = अणु
		.enable_reg = 0x0548,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc3_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sdcc4_apps_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sdcc4_apps_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sys_noc_ufs_axi_clk = अणु
	.halt_reg = 0x013c,
	.clkr = अणु
		.enable_reg = 0x013c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_ufs_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sys_noc_usb3_axi_clk = अणु
	.halt_reg = 0x0108,
	.clkr = अणु
		.enable_reg = 0x0108,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_usb3_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_sys_noc_usb3_sec_axi_clk = अणु
	.halt_reg = 0x0138,
	.clkr = अणु
		.enable_reg = 0x0138,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_sys_noc_usb3_sec_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_sec_master_clk_src",
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tsif_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_inactivity_समयrs_clk = अणु
	.halt_reg = 0x0d8c,
	.clkr = अणु
		.enable_reg = 0x0d8c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tsif_inactivity_timers_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_tsअगर_ref_clk = अणु
	.halt_reg = 0x0d88,
	.clkr = अणु
		.enable_reg = 0x0d88,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_tsif_ref_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"tsif_ref_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_ahb_clk = अणु
	.halt_reg = 0x1d48,
	.clkr = अणु
		.enable_reg = 0x1d48,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"config_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_axi_clk = अणु
	.halt_reg = 0x1d44,
	.clkr = अणु
		.enable_reg = 0x1d44,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_axi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_cfg_clk = अणु
	.halt_reg = 0x1d50,
	.clkr = अणु
		.enable_reg = 0x1d50,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_rx_cfg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_symbol_0_clk = अणु
	.halt_reg = 0x1d5c,
	.clkr = अणु
		.enable_reg = 0x1d5c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_rx_symbol_0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_rx_symbol_0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_rx_symbol_1_clk = अणु
	.halt_reg = 0x1d60,
	.clkr = अणु
		.enable_reg = 0x1d60,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_rx_symbol_1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_rx_symbol_1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_cfg_clk = अणु
	.halt_reg = 0x1d4c,
	.clkr = अणु
		.enable_reg = 0x1d4c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_tx_cfg_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_axi_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_symbol_0_clk = अणु
	.halt_reg = 0x1d54,
	.clkr = अणु
		.enable_reg = 0x1d54,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_tx_symbol_0_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_tx_symbol_0_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_ufs_tx_symbol_1_clk = अणु
	.halt_reg = 0x1d58,
	.clkr = अणु
		.enable_reg = 0x1d58,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_ufs_tx_symbol_1_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"ufs_tx_symbol_1_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2a_phy_sleep_clk = अणु
	.halt_reg = 0x04ac,
	.clkr = अणु
		.enable_reg = 0x04ac,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb2a_phy_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb2b_phy_sleep_clk = अणु
	.halt_reg = 0x04b4,
	.clkr = अणु
		.enable_reg = 0x04b4,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb2b_phy_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_master_clk = अणु
	.halt_reg = 0x03c8,
	.clkr = अणु
		.enable_reg = 0x03c8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_master_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_master_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb30_sec_master_clk = अणु
	.halt_reg = 0x1bc8,
	.clkr = अणु
		.enable_reg = 0x1bc8,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sec_master_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb30_sec_master_clk_src",
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_mock_utmi_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
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
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb30_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_ahb_clk = अणु
	.halt_reg = 0x0488,
	.clkr = अणु
		.enable_reg = 0x0488,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hs_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_inactivity_समयrs_clk = अणु
	.halt_reg = 0x048c,
	.clkr = अणु
		.enable_reg = 0x048c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hs_inactivity_timers_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hs_प्रणाली_clk = अणु
	.halt_reg = 0x0484,
	.clkr = अणु
		.enable_reg = 0x0484,
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

अटल काष्ठा clk_branch gcc_usb_hsic_ahb_clk = अणु
	.halt_reg = 0x0408,
	.clkr = अणु
		.enable_reg = 0x0408,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hsic_ahb_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"periph_noc_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hsic_clk = अणु
	.halt_reg = 0x0410,
	.clkr = अणु
		.enable_reg = 0x0410,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hsic_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb_hsic_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hsic_io_cal_clk = अणु
	.halt_reg = 0x0414,
	.clkr = अणु
		.enable_reg = 0x0414,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hsic_io_cal_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb_hsic_io_cal_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hsic_io_cal_sleep_clk = अणु
	.halt_reg = 0x0418,
	.clkr = अणु
		.enable_reg = 0x0418,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hsic_io_cal_sleep_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"sleep_clk_src",
			पूर्ण,
			.num_parents = 1,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_branch gcc_usb_hsic_प्रणाली_clk = अणु
	.halt_reg = 0x040c,
	.clkr = अणु
		.enable_reg = 0x040c,
		.enable_mask = BIT(0),
		.hw.init = &(काष्ठा clk_init_data)अणु
			.name = "gcc_usb_hsic_system_clk",
			.parent_names = (स्थिर अक्षर *[])अणु
				"usb_hsic_system_clk_src",
			पूर्ण,
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gdsc usb_hs_hsic_gdsc = अणु
	.gdscr = 0x404,
	.pd = अणु
		.name = "usb_hs_hsic",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc pcie0_gdsc = अणु
	.gdscr = 0x1ac4,
	.pd = अणु
		.name = "pcie0",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc pcie1_gdsc = अणु
	.gdscr = 0x1b44,
	.pd = अणु
		.name = "pcie1",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा gdsc usb30_gdsc = अणु
	.gdscr = 0x1e84,
	.pd = अणु
		.name = "usb30",
	पूर्ण,
	.pwrsts = PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा clk_regmap *gcc_apq8084_घड़ीs[] = अणु
	[GPLL0] = &gpll0.clkr,
	[GPLL0_VOTE] = &gpll0_vote,
	[GPLL1] = &gpll1.clkr,
	[GPLL1_VOTE] = &gpll1_vote,
	[GPLL4] = &gpll4.clkr,
	[GPLL4_VOTE] = &gpll4_vote,
	[CONFIG_NOC_CLK_SRC] = &config_noc_clk_src.clkr,
	[PERIPH_NOC_CLK_SRC] = &periph_noc_clk_src.clkr,
	[SYSTEM_NOC_CLK_SRC] = &प्रणाली_noc_clk_src.clkr,
	[UFS_AXI_CLK_SRC] = &ufs_axi_clk_src.clkr,
	[USB30_MASTER_CLK_SRC] = &usb30_master_clk_src.clkr,
	[USB30_SEC_MASTER_CLK_SRC] = &usb30_sec_master_clk_src.clkr,
	[USB_HSIC_AHB_CLK_SRC] = &usb_hsic_ahb_clk_src.clkr,
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
	[CE1_CLK_SRC] = &ce1_clk_src.clkr,
	[CE2_CLK_SRC] = &ce2_clk_src.clkr,
	[CE3_CLK_SRC] = &ce3_clk_src.clkr,
	[GP1_CLK_SRC] = &gp1_clk_src.clkr,
	[GP2_CLK_SRC] = &gp2_clk_src.clkr,
	[GP3_CLK_SRC] = &gp3_clk_src.clkr,
	[PCIE_0_AUX_CLK_SRC] = &pcie_0_aux_clk_src.clkr,
	[PCIE_0_PIPE_CLK_SRC] = &pcie_0_pipe_clk_src.clkr,
	[PCIE_1_AUX_CLK_SRC] = &pcie_1_aux_clk_src.clkr,
	[PCIE_1_PIPE_CLK_SRC] = &pcie_1_pipe_clk_src.clkr,
	[PDM2_CLK_SRC] = &pdm2_clk_src.clkr,
	[SATA_ASIC0_CLK_SRC] = &sata_asic0_clk_src.clkr,
	[SATA_PMALIVE_CLK_SRC] = &sata_pmalive_clk_src.clkr,
	[SATA_RX_CLK_SRC] = &sata_rx_clk_src.clkr,
	[SATA_RX_OOB_CLK_SRC] = &sata_rx_oob_clk_src.clkr,
	[SDCC1_APPS_CLK_SRC] = &sdcc1_apps_clk_src.clkr,
	[SDCC2_APPS_CLK_SRC] = &sdcc2_apps_clk_src.clkr,
	[SDCC3_APPS_CLK_SRC] = &sdcc3_apps_clk_src.clkr,
	[SDCC4_APPS_CLK_SRC] = &sdcc4_apps_clk_src.clkr,
	[TSIF_REF_CLK_SRC] = &tsअगर_ref_clk_src.clkr,
	[USB30_MOCK_UTMI_CLK_SRC] = &usb30_mock_uपंचांगi_clk_src.clkr,
	[USB30_SEC_MOCK_UTMI_CLK_SRC] = &usb30_sec_mock_uपंचांगi_clk_src.clkr,
	[USB_HS_SYSTEM_CLK_SRC] = &usb_hs_प्रणाली_clk_src.clkr,
	[USB_HSIC_CLK_SRC] = &usb_hsic_clk_src.clkr,
	[USB_HSIC_IO_CAL_CLK_SRC] = &usb_hsic_io_cal_clk_src.clkr,
	[USB_HSIC_MOCK_UTMI_CLK_SRC] = &usb_hsic_mock_uपंचांगi_clk_src.clkr,
	[USB_HSIC_SYSTEM_CLK_SRC] = &usb_hsic_प्रणाली_clk_src.clkr,
	[GCC_BAM_DMA_AHB_CLK] = &gcc_bam_dma_ahb_clk.clkr,
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
	[GCC_BOOT_ROM_AHB_CLK] = &gcc_boot_rom_ahb_clk.clkr,
	[GCC_CE1_AHB_CLK] = &gcc_ce1_ahb_clk.clkr,
	[GCC_CE1_AXI_CLK] = &gcc_ce1_axi_clk.clkr,
	[GCC_CE1_CLK] = &gcc_ce1_clk.clkr,
	[GCC_CE2_AHB_CLK] = &gcc_ce2_ahb_clk.clkr,
	[GCC_CE2_AXI_CLK] = &gcc_ce2_axi_clk.clkr,
	[GCC_CE2_CLK] = &gcc_ce2_clk.clkr,
	[GCC_CE3_AHB_CLK] = &gcc_ce3_ahb_clk.clkr,
	[GCC_CE3_AXI_CLK] = &gcc_ce3_axi_clk.clkr,
	[GCC_CE3_CLK] = &gcc_ce3_clk.clkr,
	[GCC_GP1_CLK] = &gcc_gp1_clk.clkr,
	[GCC_GP2_CLK] = &gcc_gp2_clk.clkr,
	[GCC_GP3_CLK] = &gcc_gp3_clk.clkr,
	[GCC_OCMEM_NOC_CFG_AHB_CLK] = &gcc_ocmem_noc_cfg_ahb_clk.clkr,
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
	[GCC_PERIPH_NOC_USB_HSIC_AHB_CLK] = &gcc_periph_noc_usb_hsic_ahb_clk.clkr,
	[GCC_PRNG_AHB_CLK] = &gcc_prng_ahb_clk.clkr,
	[GCC_SATA_ASIC0_CLK] = &gcc_sata_asic0_clk.clkr,
	[GCC_SATA_AXI_CLK] = &gcc_sata_axi_clk.clkr,
	[GCC_SATA_CFG_AHB_CLK] = &gcc_sata_cfg_ahb_clk.clkr,
	[GCC_SATA_PMALIVE_CLK] = &gcc_sata_pmalive_clk.clkr,
	[GCC_SATA_RX_CLK] = &gcc_sata_rx_clk.clkr,
	[GCC_SATA_RX_OOB_CLK] = &gcc_sata_rx_oob_clk.clkr,
	[GCC_SDCC1_AHB_CLK] = &gcc_sdcc1_ahb_clk.clkr,
	[GCC_SDCC1_APPS_CLK] = &gcc_sdcc1_apps_clk.clkr,
	[GCC_SDCC1_CDCCAL_FF_CLK] = &gcc_sdcc1_cdccal_ff_clk.clkr,
	[GCC_SDCC1_CDCCAL_SLEEP_CLK] = &gcc_sdcc1_cdccal_sleep_clk.clkr,
	[GCC_SDCC2_AHB_CLK] = &gcc_sdcc2_ahb_clk.clkr,
	[GCC_SDCC2_APPS_CLK] = &gcc_sdcc2_apps_clk.clkr,
	[GCC_SDCC3_AHB_CLK] = &gcc_sdcc3_ahb_clk.clkr,
	[GCC_SDCC3_APPS_CLK] = &gcc_sdcc3_apps_clk.clkr,
	[GCC_SDCC4_AHB_CLK] = &gcc_sdcc4_ahb_clk.clkr,
	[GCC_SDCC4_APPS_CLK] = &gcc_sdcc4_apps_clk.clkr,
	[GCC_SYS_NOC_UFS_AXI_CLK] = &gcc_sys_noc_ufs_axi_clk.clkr,
	[GCC_SYS_NOC_USB3_AXI_CLK] = &gcc_sys_noc_usb3_axi_clk.clkr,
	[GCC_SYS_NOC_USB3_SEC_AXI_CLK] = &gcc_sys_noc_usb3_sec_axi_clk.clkr,
	[GCC_TSIF_AHB_CLK] = &gcc_tsअगर_ahb_clk.clkr,
	[GCC_TSIF_INACTIVITY_TIMERS_CLK] = &gcc_tsअगर_inactivity_समयrs_clk.clkr,
	[GCC_TSIF_REF_CLK] = &gcc_tsअगर_ref_clk.clkr,
	[GCC_UFS_AHB_CLK] = &gcc_ufs_ahb_clk.clkr,
	[GCC_UFS_AXI_CLK] = &gcc_ufs_axi_clk.clkr,
	[GCC_UFS_RX_CFG_CLK] = &gcc_ufs_rx_cfg_clk.clkr,
	[GCC_UFS_RX_SYMBOL_0_CLK] = &gcc_ufs_rx_symbol_0_clk.clkr,
	[GCC_UFS_RX_SYMBOL_1_CLK] = &gcc_ufs_rx_symbol_1_clk.clkr,
	[GCC_UFS_TX_CFG_CLK] = &gcc_ufs_tx_cfg_clk.clkr,
	[GCC_UFS_TX_SYMBOL_0_CLK] = &gcc_ufs_tx_symbol_0_clk.clkr,
	[GCC_UFS_TX_SYMBOL_1_CLK] = &gcc_ufs_tx_symbol_1_clk.clkr,
	[GCC_USB2A_PHY_SLEEP_CLK] = &gcc_usb2a_phy_sleep_clk.clkr,
	[GCC_USB2B_PHY_SLEEP_CLK] = &gcc_usb2b_phy_sleep_clk.clkr,
	[GCC_USB30_MASTER_CLK] = &gcc_usb30_master_clk.clkr,
	[GCC_USB30_MOCK_UTMI_CLK] = &gcc_usb30_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SLEEP_CLK] = &gcc_usb30_sleep_clk.clkr,
	[GCC_USB30_SEC_MASTER_CLK] = &gcc_usb30_sec_master_clk.clkr,
	[GCC_USB30_SEC_MOCK_UTMI_CLK] = &gcc_usb30_sec_mock_uपंचांगi_clk.clkr,
	[GCC_USB30_SEC_SLEEP_CLK] = &gcc_usb30_sec_sleep_clk.clkr,
	[GCC_USB_HS_AHB_CLK] = &gcc_usb_hs_ahb_clk.clkr,
	[GCC_USB_HS_INACTIVITY_TIMERS_CLK] = &gcc_usb_hs_inactivity_समयrs_clk.clkr,
	[GCC_USB_HS_SYSTEM_CLK] = &gcc_usb_hs_प्रणाली_clk.clkr,
	[GCC_USB_HSIC_AHB_CLK] = &gcc_usb_hsic_ahb_clk.clkr,
	[GCC_USB_HSIC_CLK] = &gcc_usb_hsic_clk.clkr,
	[GCC_USB_HSIC_IO_CAL_CLK] = &gcc_usb_hsic_io_cal_clk.clkr,
	[GCC_USB_HSIC_IO_CAL_SLEEP_CLK] = &gcc_usb_hsic_io_cal_sleep_clk.clkr,
	[GCC_USB_HSIC_MOCK_UTMI_CLK] = &gcc_usb_hsic_mock_uपंचांगi_clk.clkr,
	[GCC_USB_HSIC_SYSTEM_CLK] = &gcc_usb_hsic_प्रणाली_clk.clkr,
पूर्ण;

अटल काष्ठा gdsc *gcc_apq8084_gdscs[] = अणु
	[USB_HS_HSIC_GDSC] = &usb_hs_hsic_gdsc,
	[PCIE0_GDSC] = &pcie0_gdsc,
	[PCIE1_GDSC] = &pcie1_gdsc,
	[USB30_GDSC] = &usb30_gdsc,
पूर्ण;

अटल स्थिर काष्ठा qcom_reset_map gcc_apq8084_resets[] = अणु
	[GCC_SYSTEM_NOC_BCR] = अणु 0x0100 पूर्ण,
	[GCC_CONFIG_NOC_BCR] = अणु 0x0140 पूर्ण,
	[GCC_PERIPH_NOC_BCR] = अणु 0x0180 पूर्ण,
	[GCC_IMEM_BCR] = अणु 0x0200 पूर्ण,
	[GCC_MMSS_BCR] = अणु 0x0240 पूर्ण,
	[GCC_QDSS_BCR] = अणु 0x0300 पूर्ण,
	[GCC_USB_30_BCR] = अणु 0x03c0 पूर्ण,
	[GCC_USB3_PHY_BCR] = अणु 0x03fc पूर्ण,
	[GCC_USB_HS_HSIC_BCR] = अणु 0x0400 पूर्ण,
	[GCC_USB_HS_BCR] = अणु 0x0480 पूर्ण,
	[GCC_USB2A_PHY_BCR] = अणु 0x04a8 पूर्ण,
	[GCC_USB2B_PHY_BCR] = अणु 0x04b0 पूर्ण,
	[GCC_SDCC1_BCR] = अणु 0x04c0 पूर्ण,
	[GCC_SDCC2_BCR] = अणु 0x0500 पूर्ण,
	[GCC_SDCC3_BCR] = अणु 0x0540 पूर्ण,
	[GCC_SDCC4_BCR] = अणु 0x0580 पूर्ण,
	[GCC_BLSP1_BCR] = अणु 0x05c0 पूर्ण,
	[GCC_BLSP1_QUP1_BCR] = अणु 0x0640 पूर्ण,
	[GCC_BLSP1_UART1_BCR] = अणु 0x0680 पूर्ण,
	[GCC_BLSP1_QUP2_BCR] = अणु 0x06c0 पूर्ण,
	[GCC_BLSP1_UART2_BCR] = अणु 0x0700 पूर्ण,
	[GCC_BLSP1_QUP3_BCR] = अणु 0x0740 पूर्ण,
	[GCC_BLSP1_UART3_BCR] = अणु 0x0780 पूर्ण,
	[GCC_BLSP1_QUP4_BCR] = अणु 0x07c0 पूर्ण,
	[GCC_BLSP1_UART4_BCR] = अणु 0x0800 पूर्ण,
	[GCC_BLSP1_QUP5_BCR] = अणु 0x0840 पूर्ण,
	[GCC_BLSP1_UART5_BCR] = अणु 0x0880 पूर्ण,
	[GCC_BLSP1_QUP6_BCR] = अणु 0x08c0 पूर्ण,
	[GCC_BLSP1_UART6_BCR] = अणु 0x0900 पूर्ण,
	[GCC_BLSP2_BCR] = अणु 0x0940 पूर्ण,
	[GCC_BLSP2_QUP1_BCR] = अणु 0x0980 पूर्ण,
	[GCC_BLSP2_UART1_BCR] = अणु 0x09c0 पूर्ण,
	[GCC_BLSP2_QUP2_BCR] = अणु 0x0a00 पूर्ण,
	[GCC_BLSP2_UART2_BCR] = अणु 0x0a40 पूर्ण,
	[GCC_BLSP2_QUP3_BCR] = अणु 0x0a80 पूर्ण,
	[GCC_BLSP2_UART3_BCR] = अणु 0x0ac0 पूर्ण,
	[GCC_BLSP2_QUP4_BCR] = अणु 0x0b00 पूर्ण,
	[GCC_BLSP2_UART4_BCR] = अणु 0x0b40 पूर्ण,
	[GCC_BLSP2_QUP5_BCR] = अणु 0x0b80 पूर्ण,
	[GCC_BLSP2_UART5_BCR] = अणु 0x0bc0 पूर्ण,
	[GCC_BLSP2_QUP6_BCR] = अणु 0x0c00 पूर्ण,
	[GCC_BLSP2_UART6_BCR] = अणु 0x0c40 पूर्ण,
	[GCC_PDM_BCR] = अणु 0x0cc0 पूर्ण,
	[GCC_PRNG_BCR] = अणु 0x0d00 पूर्ण,
	[GCC_BAM_DMA_BCR] = अणु 0x0d40 पूर्ण,
	[GCC_TSIF_BCR] = अणु 0x0d80 पूर्ण,
	[GCC_TCSR_BCR] = अणु 0x0dc0 पूर्ण,
	[GCC_BOOT_ROM_BCR] = अणु 0x0e00 पूर्ण,
	[GCC_MSG_RAM_BCR] = अणु 0x0e40 पूर्ण,
	[GCC_TLMM_BCR] = अणु 0x0e80 पूर्ण,
	[GCC_MPM_BCR] = अणु 0x0ec0 पूर्ण,
	[GCC_MPM_AHB_RESET] = अणु 0x0ec4, 1 पूर्ण,
	[GCC_MPM_NON_AHB_RESET] = अणु 0x0ec4, 2 पूर्ण,
	[GCC_SEC_CTRL_BCR] = अणु 0x0f40 पूर्ण,
	[GCC_SPMI_BCR] = अणु 0x0fc0 पूर्ण,
	[GCC_SPDM_BCR] = अणु 0x1000 पूर्ण,
	[GCC_CE1_BCR] = अणु 0x1040 पूर्ण,
	[GCC_CE2_BCR] = अणु 0x1080 पूर्ण,
	[GCC_BIMC_BCR] = अणु 0x1100 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT0_BCR] = अणु 0x1240 पूर्ण,
	[GCC_SNOC_BUS_TIMEOUT2_BCR] = अणु 0x1248 पूर्ण,
	[GCC_PNOC_BUS_TIMEOUT0_BCR] = अणु 0x1280 पूर्ण,
	[GCC_PNOC_BUS_TIMEOUT1_BCR] = अणु 0x1288 पूर्ण,
	[GCC_PNOC_BUS_TIMEOUT2_BCR] = अणु 0x1290 पूर्ण,
	[GCC_PNOC_BUS_TIMEOUT3_BCR] = अणु 0x1298 पूर्ण,
	[GCC_PNOC_BUS_TIMEOUT4_BCR] = अणु 0x12a0 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT0_BCR] = अणु 0x12c0 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT1_BCR] = अणु 0x12c8 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT2_BCR] = अणु 0x12d0 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT3_BCR] = अणु 0x12d8 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT4_BCR] = अणु 0x12e0 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT5_BCR] = अणु 0x12e8 पूर्ण,
	[GCC_CNOC_BUS_TIMEOUT6_BCR] = अणु 0x12f0 पूर्ण,
	[GCC_DEHR_BCR] = अणु 0x1300 पूर्ण,
	[GCC_RBCPR_BCR] = अणु 0x1380 पूर्ण,
	[GCC_MSS_RESTART] = अणु 0x1680 पूर्ण,
	[GCC_LPASS_RESTART] = अणु 0x16c0 पूर्ण,
	[GCC_WCSS_RESTART] = अणु 0x1700 पूर्ण,
	[GCC_VENUS_RESTART] = अणु 0x1740 पूर्ण,
	[GCC_COPSS_SMMU_BCR] = अणु 0x1a40 पूर्ण,
	[GCC_SPSS_BCR] = अणु 0x1a80 पूर्ण,
	[GCC_PCIE_0_BCR] = अणु 0x1ac0 पूर्ण,
	[GCC_PCIE_0_PHY_BCR] = अणु 0x1b00 पूर्ण,
	[GCC_PCIE_1_BCR] = अणु 0x1b40 पूर्ण,
	[GCC_PCIE_1_PHY_BCR] = अणु 0x1b80 पूर्ण,
	[GCC_USB_30_SEC_BCR] = अणु 0x1bc0 पूर्ण,
	[GCC_USB3_SEC_PHY_BCR] = अणु 0x1bfc पूर्ण,
	[GCC_SATA_BCR] = अणु 0x1c40 पूर्ण,
	[GCC_CE3_BCR] = अणु 0x1d00 पूर्ण,
	[GCC_UFS_BCR] = अणु 0x1d40 पूर्ण,
	[GCC_USB30_PHY_COM_BCR] = अणु 0x1e80 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gcc_apq8084_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x1fc0,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_cc_desc gcc_apq8084_desc = अणु
	.config = &gcc_apq8084_regmap_config,
	.clks = gcc_apq8084_घड़ीs,
	.num_clks = ARRAY_SIZE(gcc_apq8084_घड़ीs),
	.resets = gcc_apq8084_resets,
	.num_resets = ARRAY_SIZE(gcc_apq8084_resets),
	.gdscs = gcc_apq8084_gdscs,
	.num_gdscs = ARRAY_SIZE(gcc_apq8084_gdscs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id gcc_apq8084_match_table[] = अणु
	अणु .compatible = "qcom,gcc-apq8084" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gcc_apq8084_match_table);

अटल पूर्णांक gcc_apq8084_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	ret = qcom_cc_रेजिस्टर_board_clk(dev, "xo_board", "xo", 19200000);
	अगर (ret)
		वापस ret;

	ret = qcom_cc_रेजिस्टर_sleep_clk(dev);
	अगर (ret)
		वापस ret;

	वापस qcom_cc_probe(pdev, &gcc_apq8084_desc);
पूर्ण

अटल काष्ठा platक्रमm_driver gcc_apq8084_driver = अणु
	.probe		= gcc_apq8084_probe,
	.driver		= अणु
		.name	= "gcc-apq8084",
		.of_match_table = gcc_apq8084_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gcc_apq8084_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gcc_apq8084_driver);
पूर्ण
core_initcall(gcc_apq8084_init);

अटल व्योम __निकास gcc_apq8084_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gcc_apq8084_driver);
पूर्ण
module_निकास(gcc_apq8084_निकास);

MODULE_DESCRIPTION("QCOM GCC APQ8084 Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gcc-apq8084");
