<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Wendell Lin <wendell.lin@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/घड़ी/mt6779-clk.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

अटल स्थिर काष्ठा mtk_gate_regs img_cg_regs = अणु
	.set_ofs = 0x0004,
	.clr_ofs = 0x0008,
	.sta_ofs = 0x0000,
पूर्ण;

#घोषणा GATE_IMG(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &img_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate img_clks[] = अणु
	GATE_IMG(CLK_IMG_LARB5, "imgsys_larb5", "img_sel", 0),
	GATE_IMG(CLK_IMG_LARB6, "imgsys_larb6", "img_sel", 1),
	GATE_IMG(CLK_IMG_DIP, "imgsys_dip", "img_sel", 2),
	GATE_IMG(CLK_IMG_MFB, "imgsys_mfb", "img_sel", 6),
	GATE_IMG(CLK_IMG_WPE_A, "imgsys_wpe_a", "img_sel", 7),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6779_img[] = अणु
	अणु .compatible = "mediatek,mt6779-imgsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6779_img_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_IMG_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, img_clks, ARRAY_SIZE(img_clks),
			       clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6779_img_drv = अणु
	.probe = clk_mt6779_img_probe,
	.driver = अणु
		.name = "clk-mt6779-img",
		.of_match_table = of_match_clk_mt6779_img,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6779_img_drv);
