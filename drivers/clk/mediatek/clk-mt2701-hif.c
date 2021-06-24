<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Shunli Wang <shunli.wang@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt2701-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs hअगर_cg_regs = अणु
	.sta_ofs = 0x0030,
पूर्ण;

#घोषणा GATE_HIF(_id, _name, _parent, _shअगरt) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &hअगर_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate hअगर_clks[] = अणु
	GATE_HIF(CLK_HIFSYS_USB0PHY, "usb0_phy_clk", "ethpll_500m_ck", 21),
	GATE_HIF(CLK_HIFSYS_USB1PHY, "usb1_phy_clk", "ethpll_500m_ck", 22),
	GATE_HIF(CLK_HIFSYS_PCIE0, "pcie0_clk", "ethpll_500m_ck", 24),
	GATE_HIF(CLK_HIFSYS_PCIE1, "pcie1_clk", "ethpll_500m_ck", 25),
	GATE_HIF(CLK_HIFSYS_PCIE2, "pcie2_clk", "ethpll_500m_ck", 26),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt2701_hअगर[] = अणु
	अणु .compatible = "mediatek,mt2701-hifsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt2701_hअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_HIFSYS_NR);

	mtk_clk_रेजिस्टर_gates(node, hअगर_clks, ARRAY_SIZE(hअगर_clks),
						clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r) अणु
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);
		वापस r;
	पूर्ण

	mtk_रेजिस्टर_reset_controller(node, 1, 0x34);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt2701_hअगर_drv = अणु
	.probe = clk_mt2701_hअगर_probe,
	.driver = अणु
		.name = "clk-mt2701-hif",
		.of_match_table = of_match_clk_mt2701_hअगर,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2701_hअगर_drv);
