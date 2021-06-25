<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Wendell Lin <wendell.lin@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt6779-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs venc_cg_regs = अणु
	.set_ofs = 0x0004,
	.clr_ofs = 0x0008,
	.sta_ofs = 0x0000,
पूर्ण;

#घोषणा GATE_VENC_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &venc_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr_inv)

अटल स्थिर काष्ठा mtk_gate venc_clks[] = अणु
	GATE_VENC_I(CLK_VENC_GCON_LARB, "venc_larb", "venc_sel", 0),
	GATE_VENC_I(CLK_VENC_GCON_VENC, "venc_venc", "venc_sel", 4),
	GATE_VENC_I(CLK_VENC_GCON_JPGENC, "venc_jpgenc", "venc_sel", 8),
	GATE_VENC_I(CLK_VENC_GCON_GALS, "venc_gals", "venc_sel", 28),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6779_venc[] = अणु
	अणु .compatible = "mediatek,mt6779-vencsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6779_venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_VENC_GCON_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, venc_clks, ARRAY_SIZE(venc_clks),
			       clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6779_venc_drv = अणु
	.probe = clk_mt6779_venc_probe,
	.driver = अणु
		.name = "clk-mt6779-venc",
		.of_match_table = of_match_clk_mt6779_venc,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6779_venc_drv);
