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

अटल स्थिर काष्ठा mtk_gate_regs ipe_cg_regs = अणु
	.set_ofs = 0x0004,
	.clr_ofs = 0x0008,
	.sta_ofs = 0x0000,
पूर्ण;

#घोषणा GATE_IPE(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &ipe_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate ipe_clks[] = अणु
	GATE_IPE(CLK_IPE_LARB7, "ipe_larb7", "ipe_sel", 0),
	GATE_IPE(CLK_IPE_LARB8, "ipe_larb8", "ipe_sel", 1),
	GATE_IPE(CLK_IPE_SMI_SUBCOM, "ipe_smi_subcom", "ipe_sel", 2),
	GATE_IPE(CLK_IPE_FD, "ipe_fd", "ipe_sel", 3),
	GATE_IPE(CLK_IPE_FE, "ipe_fe", "ipe_sel", 4),
	GATE_IPE(CLK_IPE_RSC, "ipe_rsc", "ipe_sel", 5),
	GATE_IPE(CLK_IPE_DPE, "ipe_dpe", "ipe_sel", 6),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6779_ipe[] = अणु
	अणु .compatible = "mediatek,mt6779-ipesys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6779_ipe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_IPE_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, ipe_clks, ARRAY_SIZE(ipe_clks),
			       clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6779_ipe_drv = अणु
	.probe = clk_mt6779_ipe_probe,
	.driver = अणु
		.name = "clk-mt6779-ipe",
		.of_match_table = of_match_clk_mt6779_ipe,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6779_ipe_drv);
