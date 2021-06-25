<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Weiyi Lu <weiyi.lu@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt2712-clk.h>

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

#घोषणा GATE_VDEC0(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &vdec0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	पूर्ण

#घोषणा GATE_VDEC1(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &vdec1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate vdec_clks[] = अणु
	/* VDEC0 */
	GATE_VDEC0(CLK_VDEC_CKEN, "vdec_cken", "vdec_sel", 0),
	/* VDEC1 */
	GATE_VDEC1(CLK_VDEC_LARB1_CKEN, "vdec_larb1_cken", "vdec_sel", 0),
	GATE_VDEC1(CLK_VDEC_IMGRZ_CKEN, "vdec_imgrz_cken", "vdec_sel", 1),
पूर्ण;

अटल पूर्णांक clk_mt2712_vdec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_VDEC_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, vdec_clks, ARRAY_SIZE(vdec_clks),
			clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r != 0)
		pr_err("%s(): could not register clock provider: %d\n",
			__func__, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt2712_vdec[] = अणु
	अणु .compatible = "mediatek,mt2712-vdecsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt2712_vdec_drv = अणु
	.probe = clk_mt2712_vdec_probe,
	.driver = अणु
		.name = "clk-mt2712-vdec",
		.of_match_table = of_match_clk_mt2712_vdec,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2712_vdec_drv);
