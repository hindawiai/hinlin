<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2018 MediaTek Inc.
// Author: Weiyi Lu <weiyi.lu@mediatek.com>

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt8183-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs mfg_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_MFG(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &mfg_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate mfg_clks[] = अणु
	GATE_MFG(CLK_MFG_BG3D, "mfg_bg3d", "mfg_sel", 0)
पूर्ण;

अटल पूर्णांक clk_mt8183_mfg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	pm_runसमय_enable(&pdev->dev);

	clk_data = mtk_alloc_clk_data(CLK_MFG_NR_CLK);

	mtk_clk_रेजिस्टर_gates_with_dev(node, mfg_clks, ARRAY_SIZE(mfg_clks),
			clk_data, &pdev->dev);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt8183_mfg[] = अणु
	अणु .compatible = "mediatek,mt8183-mfgcfg", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt8183_mfg_drv = अणु
	.probe = clk_mt8183_mfg_probe,
	.driver = अणु
		.name = "clk-mt8183-mfg",
		.of_match_table = of_match_clk_mt8183_mfg,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8183_mfg_drv);
