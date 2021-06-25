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

अटल स्थिर काष्ठा mtk_gate_regs jpgdec_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_JPGDEC(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &jpgdec_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate jpgdec_clks[] = अणु
	GATE_JPGDEC(CLK_JPGDEC_JPGDEC1, "jpgdec_jpgdec1", "jpgdec_sel", 0),
	GATE_JPGDEC(CLK_JPGDEC_JPGDEC, "jpgdec_jpgdec", "jpgdec_sel", 4),
पूर्ण;

अटल पूर्णांक clk_mt2712_jpgdec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_JPGDEC_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, jpgdec_clks, ARRAY_SIZE(jpgdec_clks),
			clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r != 0)
		pr_err("%s(): could not register clock provider: %d\n",
			__func__, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt2712_jpgdec[] = अणु
	अणु .compatible = "mediatek,mt2712-jpgdecsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt2712_jpgdec_drv = अणु
	.probe = clk_mt2712_jpgdec_probe,
	.driver = अणु
		.name = "clk-mt2712-jpgdec",
		.of_match_table = of_match_clk_mt2712_jpgdec,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2712_jpgdec_drv);
