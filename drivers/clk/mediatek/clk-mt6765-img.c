<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Owen Chen <owen.chen@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt6765-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs img_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_IMG(_id, _name, _parent, _shअगरt) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &img_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate img_clks[] = अणु
	GATE_IMG(CLK_IMG_LARB2, "img_larb2", "mm_ck", 0),
	GATE_IMG(CLK_IMG_DIP, "img_dip", "mm_ck", 2),
	GATE_IMG(CLK_IMG_FDVT, "img_fdvt", "mm_ck", 3),
	GATE_IMG(CLK_IMG_DPE, "img_dpe", "mm_ck", 4),
	GATE_IMG(CLK_IMG_RSC, "img_rsc", "mm_ck", 5),
पूर्ण;

अटल पूर्णांक clk_mt6765_img_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_IMG_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, img_clks, ARRAY_SIZE(img_clks), clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
		       __func__, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6765_img[] = अणु
	अणु .compatible = "mediatek,mt6765-imgsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt6765_img_drv = अणु
	.probe = clk_mt6765_img_probe,
	.driver = अणु
		.name = "clk-mt6765-img",
		.of_match_table = of_match_clk_mt6765_img,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6765_img_drv);
