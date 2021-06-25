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

अटल स्थिर काष्ठा mtk_gate_regs cam_cg_regs = अणु
	.set_ofs = 0x0004,
	.clr_ofs = 0x0008,
	.sta_ofs = 0x0000,
पूर्ण;

#घोषणा GATE_CAM(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &cam_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate cam_clks[] = अणु
	GATE_CAM(CLK_CAM_LARB10, "camsys_larb10", "cam_sel", 0),
	GATE_CAM(CLK_CAM_DFP_VAD, "camsys_dfp_vad", "cam_sel", 1),
	GATE_CAM(CLK_CAM_LARB11, "camsys_larb11", "cam_sel", 2),
	GATE_CAM(CLK_CAM_LARB9, "camsys_larb9", "cam_sel", 3),
	GATE_CAM(CLK_CAM_CAM, "camsys_cam", "cam_sel", 6),
	GATE_CAM(CLK_CAM_CAMTG, "camsys_camtg", "cam_sel", 7),
	GATE_CAM(CLK_CAM_SENINF, "camsys_seninf", "cam_sel", 8),
	GATE_CAM(CLK_CAM_CAMSV0, "camsys_camsv0", "cam_sel", 9),
	GATE_CAM(CLK_CAM_CAMSV1, "camsys_camsv1", "cam_sel", 10),
	GATE_CAM(CLK_CAM_CAMSV2, "camsys_camsv2", "cam_sel", 11),
	GATE_CAM(CLK_CAM_CAMSV3, "camsys_camsv3", "cam_sel", 12),
	GATE_CAM(CLK_CAM_CCU, "camsys_ccu", "cam_sel", 13),
	GATE_CAM(CLK_CAM_FAKE_ENG, "camsys_fake_eng", "cam_sel", 14),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6779_cam[] = अणु
	अणु .compatible = "mediatek,mt6779-camsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6779_cam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_CAM_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, cam_clks, ARRAY_SIZE(cam_clks),
			       clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6779_cam_drv = अणु
	.probe = clk_mt6779_cam_probe,
	.driver = अणु
		.name = "clk-mt6779-cam",
		.of_match_table = of_match_clk_mt6779_cam,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6779_cam_drv);
