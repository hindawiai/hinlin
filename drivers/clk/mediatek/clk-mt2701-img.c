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

अटल स्थिर काष्ठा mtk_gate_regs img_cg_regs = अणु
	.set_ofs = 0x0004,
	.clr_ofs = 0x0008,
	.sta_ofs = 0x0000,
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
	GATE_IMG(CLK_IMG_SMI_COMM, "img_smi_comm", "mm_sel", 0),
	GATE_IMG(CLK_IMG_RESZ, "img_resz", "mm_sel", 1),
	GATE_IMG(CLK_IMG_JPGDEC_SMI, "img_jpgdec_smi", "mm_sel", 5),
	GATE_IMG(CLK_IMG_JPGDEC, "img_jpgdec", "mm_sel", 6),
	GATE_IMG(CLK_IMG_VENC_LT, "img_venc_lt", "mm_sel", 8),
	GATE_IMG(CLK_IMG_VENC, "img_venc", "mm_sel", 9),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt2701_img[] = अणु
	अणु .compatible = "mediatek,mt2701-imgsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt2701_img_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_IMG_NR);

	mtk_clk_रेजिस्टर_gates(node, img_clks, ARRAY_SIZE(img_clks),
						clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt2701_img_drv = अणु
	.probe = clk_mt2701_img_probe,
	.driver = अणु
		.name = "clk-mt2701-img",
		.of_match_table = of_match_clk_mt2701_img,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2701_img_drv);
