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

अटल स्थिर काष्ठा mtk_gate_regs ipu_conn_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs ipu_conn_apb_cg_regs = अणु
	.set_ofs = 0x10,
	.clr_ofs = 0x10,
	.sta_ofs = 0x10,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs ipu_conn_axi_cg_regs = अणु
	.set_ofs = 0x18,
	.clr_ofs = 0x18,
	.sta_ofs = 0x18,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs ipu_conn_axi1_cg_regs = अणु
	.set_ofs = 0x1c,
	.clr_ofs = 0x1c,
	.sta_ofs = 0x1c,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs ipu_conn_axi2_cg_regs = अणु
	.set_ofs = 0x20,
	.clr_ofs = 0x20,
	.sta_ofs = 0x20,
पूर्ण;

#घोषणा GATE_IPU_CONN(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &ipu_conn_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

#घोषणा GATE_IPU_CONN_APB(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &ipu_conn_apb_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_no_setclr)

#घोषणा GATE_IPU_CONN_AXI_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &ipu_conn_axi_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_no_setclr_inv)

#घोषणा GATE_IPU_CONN_AXI1_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &ipu_conn_axi1_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_no_setclr_inv)

#घोषणा GATE_IPU_CONN_AXI2_I(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &ipu_conn_axi2_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_no_setclr_inv)

अटल स्थिर काष्ठा mtk_gate ipu_conn_clks[] = अणु
	GATE_IPU_CONN(CLK_IPU_CONN_IPU,
		"ipu_conn_ipu", "dsp_sel", 0),
	GATE_IPU_CONN(CLK_IPU_CONN_AHB,
		"ipu_conn_ahb", "dsp_sel", 1),
	GATE_IPU_CONN(CLK_IPU_CONN_AXI,
		"ipu_conn_axi", "dsp_sel", 2),
	GATE_IPU_CONN(CLK_IPU_CONN_ISP,
		"ipu_conn_isp", "dsp_sel", 3),
	GATE_IPU_CONN(CLK_IPU_CONN_CAM_ADL,
		"ipu_conn_cam_adl", "dsp_sel", 4),
	GATE_IPU_CONN(CLK_IPU_CONN_IMG_ADL,
		"ipu_conn_img_adl", "dsp_sel", 5),
	GATE_IPU_CONN_APB(CLK_IPU_CONN_DAP_RX,
		"ipu_conn_dap_rx", "dsp1_sel", 0),
	GATE_IPU_CONN_APB(CLK_IPU_CONN_APB2AXI,
		"ipu_conn_apb2axi", "dsp1_sel", 3),
	GATE_IPU_CONN_APB(CLK_IPU_CONN_APB2AHB,
		"ipu_conn_apb2ahb", "dsp1_sel", 20),
	GATE_IPU_CONN_AXI_I(CLK_IPU_CONN_IPU_CAB1TO2,
		"ipu_conn_ipu_cab1to2", "dsp1_sel", 6),
	GATE_IPU_CONN_AXI_I(CLK_IPU_CONN_IPU1_CAB1TO2,
		"ipu_conn_ipu1_cab1to2", "dsp1_sel", 13),
	GATE_IPU_CONN_AXI_I(CLK_IPU_CONN_IPU2_CAB1TO2,
		"ipu_conn_ipu2_cab1to2", "dsp1_sel", 20),
	GATE_IPU_CONN_AXI1_I(CLK_IPU_CONN_CAB3TO3,
		"ipu_conn_cab3to3", "dsp1_sel", 0),
	GATE_IPU_CONN_AXI2_I(CLK_IPU_CONN_CAB2TO1,
		"ipu_conn_cab2to1", "dsp1_sel", 14),
	GATE_IPU_CONN_AXI2_I(CLK_IPU_CONN_CAB3TO1_SLICE,
		"ipu_conn_cab3to1_slice", "dsp1_sel", 17),
पूर्ण;

अटल पूर्णांक clk_mt8183_ipu_conn_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_IPU_CONN_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, ipu_conn_clks, ARRAY_SIZE(ipu_conn_clks),
			clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt8183_ipu_conn[] = अणु
	अणु .compatible = "mediatek,mt8183-ipu_conn", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt8183_ipu_conn_drv = अणु
	.probe = clk_mt8183_ipu_conn_probe,
	.driver = अणु
		.name = "clk-mt8183-ipu_conn",
		.of_match_table = of_match_clk_mt8183_ipu_conn,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8183_ipu_conn_drv);
