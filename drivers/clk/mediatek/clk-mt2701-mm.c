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

अटल स्थिर काष्ठा mtk_gate_regs disp0_cg_regs = अणु
	.set_ofs = 0x0104,
	.clr_ofs = 0x0108,
	.sta_ofs = 0x0100,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs disp1_cg_regs = अणु
	.set_ofs = 0x0114,
	.clr_ofs = 0x0118,
	.sta_ofs = 0x0110,
पूर्ण;

#घोषणा GATE_DISP0(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &disp0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_DISP1(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &disp1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate mm_clks[] = अणु
	GATE_DISP0(CLK_MM_SMI_COMMON, "mm_smi_comm", "mm_sel", 0),
	GATE_DISP0(CLK_MM_SMI_LARB0, "mm_smi_larb0", "mm_sel", 1),
	GATE_DISP0(CLK_MM_CMDQ, "mm_cmdq", "mm_sel", 2),
	GATE_DISP0(CLK_MM_MUTEX, "mm_mutex", "mm_sel", 3),
	GATE_DISP0(CLK_MM_DISP_COLOR, "mm_disp_color", "mm_sel", 4),
	GATE_DISP0(CLK_MM_DISP_BLS, "mm_disp_bls", "mm_sel", 5),
	GATE_DISP0(CLK_MM_DISP_WDMA, "mm_disp_wdma", "mm_sel", 6),
	GATE_DISP0(CLK_MM_DISP_RDMA, "mm_disp_rdma", "mm_sel", 7),
	GATE_DISP0(CLK_MM_DISP_OVL, "mm_disp_ovl", "mm_sel", 8),
	GATE_DISP0(CLK_MM_MDP_TDSHP, "mm_mdp_tdshp", "mm_sel", 9),
	GATE_DISP0(CLK_MM_MDP_WROT, "mm_mdp_wrot", "mm_sel", 10),
	GATE_DISP0(CLK_MM_MDP_WDMA, "mm_mdp_wdma", "mm_sel", 11),
	GATE_DISP0(CLK_MM_MDP_RSZ1, "mm_mdp_rsz1", "mm_sel", 12),
	GATE_DISP0(CLK_MM_MDP_RSZ0, "mm_mdp_rsz0", "mm_sel", 13),
	GATE_DISP0(CLK_MM_MDP_RDMA, "mm_mdp_rdma", "mm_sel", 14),
	GATE_DISP0(CLK_MM_MDP_BLS_26M, "mm_mdp_bls_26m", "pwm_sel", 15),
	GATE_DISP0(CLK_MM_CAM_MDP, "mm_cam_mdp", "mm_sel", 16),
	GATE_DISP0(CLK_MM_FAKE_ENG, "mm_fake_eng", "mm_sel", 17),
	GATE_DISP0(CLK_MM_MUTEX_32K, "mm_mutex_32k", "rtc_sel", 18),
	GATE_DISP0(CLK_MM_DISP_RDMA1, "mm_disp_rdma1", "mm_sel", 19),
	GATE_DISP0(CLK_MM_DISP_UFOE, "mm_disp_ufoe", "mm_sel", 20),
	GATE_DISP1(CLK_MM_DSI_ENGINE, "mm_dsi_eng", "mm_sel", 0),
	GATE_DISP1(CLK_MM_DSI_DIG, "mm_dsi_dig", "dsi0_lntc_dsi", 1),
	GATE_DISP1(CLK_MM_DPI_DIGL, "mm_dpi_digl", "dpi0_sel", 2),
	GATE_DISP1(CLK_MM_DPI_ENGINE, "mm_dpi_eng", "mm_sel", 3),
	GATE_DISP1(CLK_MM_DPI1_DIGL, "mm_dpi1_digl", "dpi1_sel", 4),
	GATE_DISP1(CLK_MM_DPI1_ENGINE, "mm_dpi1_eng", "mm_sel", 5),
	GATE_DISP1(CLK_MM_TVE_OUTPUT, "mm_tve_output", "tve_sel", 6),
	GATE_DISP1(CLK_MM_TVE_INPUT, "mm_tve_input", "dpi0_sel", 7),
	GATE_DISP1(CLK_MM_HDMI_PIXEL, "mm_hdmi_pixel", "dpi1_sel", 8),
	GATE_DISP1(CLK_MM_HDMI_PLL, "mm_hdmi_pll", "hdmi_sel", 9),
	GATE_DISP1(CLK_MM_HDMI_AUDIO, "mm_hdmi_audio", "apll_sel", 10),
	GATE_DISP1(CLK_MM_HDMI_SPDIF, "mm_hdmi_spdif", "apll_sel", 11),
	GATE_DISP1(CLK_MM_TVE_FMM, "mm_tve_fmm", "mm_sel", 14),
पूर्ण;

अटल पूर्णांक clk_mt2701_mm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->parent->of_node;
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_MM_NR);

	mtk_clk_रेजिस्टर_gates(node, mm_clks, ARRAY_SIZE(mm_clks),
						clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt2701_mm_drv = अणु
	.probe = clk_mt2701_mm_probe,
	.driver = अणु
		.name = "clk-mt2701-mm",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2701_mm_drv);
