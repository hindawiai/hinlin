<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2018 MediaTek Inc.
// Author: Weiyi Lu <weiyi.lu@mediatek.com>

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt8183-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs venc_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_VENC_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &venc_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr_inv)

अटल स्थिर काष्ठा mtk_gate venc_clks[] = अणु
	GATE_VENC_I(CLK_VENC_LARB, "venc_larb",
		"mm_sel", 0),
	GATE_VENC_I(CLK_VENC_VENC, "venc_venc",
		"mm_sel", 4),
	GATE_VENC_I(CLK_VENC_JPGENC, "venc_jpgenc",
		"mm_sel", 8),
पूर्ण;

अटल पूर्णांक clk_mt8183_venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_VENC_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, venc_clks, ARRAY_SIZE(venc_clks),
			clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt8183_venc[] = अणु
	अणु .compatible = "mediatek,mt8183-vencsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt8183_venc_drv = अणु
	.probe = clk_mt8183_venc_probe,
	.driver = अणु
		.name = "clk-mt8183-venc",
		.of_match_table = of_match_clk_mt8183_venc,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8183_venc_drv);
