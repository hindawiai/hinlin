<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Kevin Chen <kevin-cw.chen@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt6797-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs venc_cg_regs = अणु
	.set_ofs = 0x0004,
	.clr_ofs = 0x0008,
	.sta_ofs = 0x0000,
पूर्ण;

#घोषणा GATE_VENC(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &venc_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate venc_clks[] = अणु
	GATE_VENC(CLK_VENC_0, "venc_0", "mm_sel", 0),
	GATE_VENC(CLK_VENC_1, "venc_1", "venc_sel", 4),
	GATE_VENC(CLK_VENC_2, "venc_2", "venc_sel", 8),
	GATE_VENC(CLK_VENC_3, "venc_3", "venc_sel", 12),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6797_venc[] = अणु
	अणु .compatible = "mediatek,mt6797-vencsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6797_venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_VENC_NR);

	mtk_clk_रेजिस्टर_gates(node, venc_clks, ARRAY_SIZE(venc_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6797_venc_drv = अणु
	.probe = clk_mt6797_venc_probe,
	.driver = अणु
		.name = "clk-mt6797-venc",
		.of_match_table = of_match_clk_mt6797_venc,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6797_venc_drv);
