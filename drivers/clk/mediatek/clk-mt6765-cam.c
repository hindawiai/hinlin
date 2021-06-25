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

अटल स्थिर काष्ठा mtk_gate_regs cam_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_CAM(_id, _name, _parent, _shअगरt) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &cam_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate cam_clks[] = अणु
	GATE_CAM(CLK_CAM_LARB3, "cam_larb3", "mm_ck", 0),
	GATE_CAM(CLK_CAM_DFP_VAD, "cam_dfp_vad", "mm_ck", 1),
	GATE_CAM(CLK_CAM, "cam", "mm_ck", 6),
	GATE_CAM(CLK_CAMTG, "camtg", "mm_ck", 7),
	GATE_CAM(CLK_CAM_SENINF, "cam_seninf", "mm_ck", 8),
	GATE_CAM(CLK_CAMSV0, "camsv0", "mm_ck", 9),
	GATE_CAM(CLK_CAMSV1, "camsv1", "mm_ck", 10),
	GATE_CAM(CLK_CAMSV2, "camsv2", "mm_ck", 11),
	GATE_CAM(CLK_CAM_CCU, "cam_ccu", "mm_ck", 12),
पूर्ण;

अटल पूर्णांक clk_mt6765_cam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_CAM_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, cam_clks, ARRAY_SIZE(cam_clks), clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
		       __func__, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6765_cam[] = अणु
	अणु .compatible = "mediatek,mt6765-camsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt6765_cam_drv = अणु
	.probe = clk_mt6765_cam_probe,
	.driver = अणु
		.name = "clk-mt6765-cam",
		.of_match_table = of_match_clk_mt6765_cam,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6765_cam_drv);
