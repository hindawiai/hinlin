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

अटल स्थिर काष्ठा mtk_gate_regs img_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_IMG(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &img_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate img_clks[] = अणु
	GATE_IMG(CLK_IMG_LARB5, "img_larb5", "img_sel", 0),
	GATE_IMG(CLK_IMG_LARB2, "img_larb2", "img_sel", 1),
	GATE_IMG(CLK_IMG_DIP, "img_dip", "img_sel", 2),
	GATE_IMG(CLK_IMG_FDVT, "img_fdvt", "img_sel", 3),
	GATE_IMG(CLK_IMG_DPE, "img_dpe", "img_sel", 4),
	GATE_IMG(CLK_IMG_RSC, "img_rsc", "img_sel", 5),
	GATE_IMG(CLK_IMG_MFB, "img_mfb", "img_sel", 6),
	GATE_IMG(CLK_IMG_WPE_A, "img_wpe_a", "img_sel", 7),
	GATE_IMG(CLK_IMG_WPE_B, "img_wpe_b", "img_sel", 8),
	GATE_IMG(CLK_IMG_OWE, "img_owe", "img_sel", 9),
पूर्ण;

अटल पूर्णांक clk_mt8183_img_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_IMG_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, img_clks, ARRAY_SIZE(img_clks),
			clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt8183_img[] = अणु
	अणु .compatible = "mediatek,mt8183-imgsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt8183_img_drv = अणु
	.probe = clk_mt8183_img_probe,
	.driver = अणु
		.name = "clk-mt8183-img",
		.of_match_table = of_match_clk_mt8183_img,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8183_img_drv);
