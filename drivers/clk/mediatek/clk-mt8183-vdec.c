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

अटल स्थिर काष्ठा mtk_gate_regs vdec0_cg_regs = अणु
	.set_ofs = 0x0,
	.clr_ofs = 0x4,
	.sta_ofs = 0x0,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs vdec1_cg_regs = अणु
	.set_ofs = 0x8,
	.clr_ofs = 0xc,
	.sta_ofs = 0x8,
पूर्ण;

#घोषणा GATE_VDEC0_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &vdec0_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr_inv)

#घोषणा GATE_VDEC1_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &vdec1_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr_inv)

अटल स्थिर काष्ठा mtk_gate vdec_clks[] = अणु
	/* VDEC0 */
	GATE_VDEC0_I(CLK_VDEC_VDEC, "vdec_vdec", "mm_sel", 0),
	/* VDEC1 */
	GATE_VDEC1_I(CLK_VDEC_LARB1, "vdec_larb1", "mm_sel", 0),
पूर्ण;

अटल पूर्णांक clk_mt8183_vdec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_VDEC_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, vdec_clks, ARRAY_SIZE(vdec_clks),
			clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt8183_vdec[] = अणु
	अणु .compatible = "mediatek,mt8183-vdecsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt8183_vdec_drv = अणु
	.probe = clk_mt8183_vdec_probe,
	.driver = अणु
		.name = "clk-mt8183-vdec",
		.of_match_table = of_match_clk_mt8183_vdec,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8183_vdec_drv);
