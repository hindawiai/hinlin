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

अटल स्थिर काष्ठा mtk_gate_regs cam_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_CAM(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &cam_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate cam_clks[] = अणु
	GATE_CAM(CLK_CAM_LARB6, "cam_larb6", "cam_sel", 0),
	GATE_CAM(CLK_CAM_DFP_VAD, "cam_dfp_vad", "cam_sel", 1),
	GATE_CAM(CLK_CAM_LARB3, "cam_larb3", "cam_sel", 2),
	GATE_CAM(CLK_CAM_CAM, "cam_cam", "cam_sel", 6),
	GATE_CAM(CLK_CAM_CAMTG, "cam_camtg", "cam_sel", 7),
	GATE_CAM(CLK_CAM_SENINF, "cam_seninf", "cam_sel", 8),
	GATE_CAM(CLK_CAM_CAMSV0, "cam_camsv0", "cam_sel", 9),
	GATE_CAM(CLK_CAM_CAMSV1, "cam_camsv1", "cam_sel", 10),
	GATE_CAM(CLK_CAM_CAMSV2, "cam_camsv2", "cam_sel", 11),
	GATE_CAM(CLK_CAM_CCU, "cam_ccu", "cam_sel", 12),
पूर्ण;

अटल पूर्णांक clk_mt8183_cam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_CAM_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, cam_clks, ARRAY_SIZE(cam_clks),
			clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt8183_cam[] = अणु
	अणु .compatible = "mediatek,mt8183-camsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt8183_cam_drv = अणु
	.probe = clk_mt8183_cam_probe,
	.driver = अणु
		.name = "clk-mt8183-cam",
		.of_match_table = of_match_clk_mt8183_cam,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8183_cam_drv);
