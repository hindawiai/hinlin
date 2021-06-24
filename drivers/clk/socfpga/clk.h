<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013, Steffen Trumtrar <s.trumtrar@pengutronix.de>
 *
 * based on drivers/clk/tegra/clk.h
 */

#अगर_अघोषित __SOCFPGA_CLK_H
#घोषणा __SOCFPGA_CLK_H

#समावेश <linux/clk-provider.h>

/* Clock Manager offsets */
#घोषणा CLKMGR_CTRL		0x0
#घोषणा CLKMGR_BYPASS		0x4
#घोषणा CLKMGR_DBCTRL		0x10
#घोषणा CLKMGR_L4SRC		0x70
#घोषणा CLKMGR_PERPLL_SRC	0xAC

#घोषणा SOCFPGA_MAX_PARENTS		5

#घोषणा streq(a, b) (म_भेद((a), (b)) == 0)
#घोषणा SYSMGR_SDMMC_CTRL_SET(smplsel, drvsel) \
	((((smplsel) & 0x7) << 3) | (((drvsel) & 0x7) << 0))

#घोषणा SYSMGR_SDMMC_CTRL_SET_AS10(smplsel, drvsel) \
	((((smplsel) & 0x7) << 4) | (((drvsel) & 0x7) << 0))

बाह्य व्योम __iomem *clk_mgr_base_addr;
बाह्य व्योम __iomem *clk_mgr_a10_base_addr;

व्योम __init socfpga_pll_init(काष्ठा device_node *node);
व्योम __init socfpga_periph_init(काष्ठा device_node *node);
व्योम __init socfpga_gate_init(काष्ठा device_node *node);
व्योम socfpga_a10_pll_init(काष्ठा device_node *node);
व्योम socfpga_a10_periph_init(काष्ठा device_node *node);
व्योम socfpga_a10_gate_init(काष्ठा device_node *node);

काष्ठा socfpga_pll अणु
	काष्ठा clk_gate	hw;
पूर्ण;

काष्ठा socfpga_gate_clk अणु
	काष्ठा clk_gate hw;
	अक्षर *parent_name;
	u32 fixed_भाग;
	व्योम __iomem *भाग_reg;
	व्योम __iomem *bypass_reg;
	काष्ठा regmap *sys_mgr_base_addr;
	u32 width;	/* only valid अगर भाग_reg != 0 */
	u32 shअगरt;	/* only valid अगर भाग_reg != 0 */
	u32 bypass_shअगरt;      /* only valid अगर bypass_reg != 0 */
	u32 clk_phase[2];
पूर्ण;

काष्ठा socfpga_periph_clk अणु
	काष्ठा clk_gate hw;
	अक्षर *parent_name;
	u32 fixed_भाग;
	व्योम __iomem *भाग_reg;
	व्योम __iomem *bypass_reg;
	u32 width;      /* only valid अगर भाग_reg != 0 */
	u32 shअगरt;      /* only valid अगर भाग_reg != 0 */
	u32 bypass_shअगरt;      /* only valid अगर bypass_reg != 0 */
पूर्ण;

#पूर्ण_अगर /* SOCFPGA_CLK_H */
