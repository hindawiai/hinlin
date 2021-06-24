<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 * Copyright (c) 2020 BayLibre, SAS
 * Author: James Liao <jamesjj.liao@mediatek.com>
 *         Fabien Parent <fparent@baylibre.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt8167-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs mm0_cg_regs = अणु
	.set_ofs = 0x104,
	.clr_ofs = 0x108,
	.sta_ofs = 0x100,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs mm1_cg_regs = अणु
	.set_ofs = 0x114,
	.clr_ofs = 0x118,
	.sta_ofs = 0x110,
पूर्ण;

#घोषणा GATE_MM0(_id, _name, _parent, _shअगरt) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &mm0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_MM1(_id, _name, _parent, _shअगरt) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &mm1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate mm_clks[] = अणु
	/* MM0 */
	GATE_MM0(CLK_MM_SMI_COMMON, "mm_smi_common", "smi_mm", 0),
	GATE_MM0(CLK_MM_SMI_LARB0, "mm_smi_larb0", "smi_mm", 1),
	GATE_MM0(CLK_MM_CAM_MDP, "mm_cam_mdp", "smi_mm", 2),
	GATE_MM0(CLK_MM_MDP_RDMA, "mm_mdp_rdma", "smi_mm", 3),
	GATE_MM0(CLK_MM_MDP_RSZ0, "mm_mdp_rsz0", "smi_mm", 4),
	GATE_MM0(CLK_MM_MDP_RSZ1, "mm_mdp_rsz1", "smi_mm", 5),
	GATE_MM0(CLK_MM_MDP_TDSHP, "mm_mdp_tdshp", "smi_mm", 6),
	GATE_MM0(CLK_MM_MDP_WDMA, "mm_mdp_wdma", "smi_mm", 7),
	GATE_MM0(CLK_MM_MDP_WROT, "mm_mdp_wrot", "smi_mm", 8),
	GATE_MM0(CLK_MM_FAKE_ENG, "mm_fake_eng", "smi_mm", 9),
	GATE_MM0(CLK_MM_DISP_OVL0, "mm_disp_ovl0", "smi_mm", 10),
	GATE_MM0(CLK_MM_DISP_RDMA0, "mm_disp_rdma0", "smi_mm", 11),
	GATE_MM0(CLK_MM_DISP_RDMA1, "mm_disp_rdma1", "smi_mm", 12),
	GATE_MM0(CLK_MM_DISP_WDMA, "mm_disp_wdma", "smi_mm", 13),
	GATE_MM0(CLK_MM_DISP_COLOR, "mm_disp_color", "smi_mm", 14),
	GATE_MM0(CLK_MM_DISP_CCORR, "mm_disp_ccorr", "smi_mm", 15),
	GATE_MM0(CLK_MM_DISP_AAL, "mm_disp_aal", "smi_mm", 16),
	GATE_MM0(CLK_MM_DISP_GAMMA, "mm_disp_gamma", "smi_mm", 17),
	GATE_MM0(CLK_MM_DISP_DITHER, "mm_disp_dither", "smi_mm", 18),
	GATE_MM0(CLK_MM_DISP_UFOE, "mm_disp_ufoe", "smi_mm", 19),
	/* MM1 */
	GATE_MM1(CLK_MM_DISP_PWM_MM, "mm_disp_pwm_mm", "smi_mm", 0),
	GATE_MM1(CLK_MM_DISP_PWM_26M, "mm_disp_pwm_26m", "smi_mm", 1),
	GATE_MM1(CLK_MM_DSI_ENGINE, "mm_dsi_engine", "smi_mm", 2),
	GATE_MM1(CLK_MM_DSI_DIGITAL, "mm_dsi_digital", "dsi0_lntc_dsick", 3),
	GATE_MM1(CLK_MM_DPI0_ENGINE, "mm_dpi0_engine", "smi_mm", 4),
	GATE_MM1(CLK_MM_DPI0_PXL, "mm_dpi0_pxl", "rg_fdpi0", 5),
	GATE_MM1(CLK_MM_LVDS_PXL, "mm_lvds_pxl", "vpll_dpix", 14),
	GATE_MM1(CLK_MM_LVDS_CTS, "mm_lvds_cts", "lvdstx_dig_cts", 15),
	GATE_MM1(CLK_MM_DPI1_ENGINE, "mm_dpi1_engine", "smi_mm", 16),
	GATE_MM1(CLK_MM_DPI1_PXL, "mm_dpi1_pxl", "rg_fdpi1", 17),
	GATE_MM1(CLK_MM_HDMI_PXL, "mm_hdmi_pxl", "rg_fdpi1", 18),
	GATE_MM1(CLK_MM_HDMI_SPDIF, "mm_hdmi_spdif", "apll12_div6", 19),
	GATE_MM1(CLK_MM_HDMI_ADSP_BCK, "mm_hdmi_adsp_b", "apll12_div4b", 20),
	GATE_MM1(CLK_MM_HDMI_PLL, "mm_hdmi_pll", "hdmtx_dig_cts", 21),
पूर्ण;

काष्ठा clk_mt8167_mm_driver_data अणु
	स्थिर काष्ठा mtk_gate *gates_clk;
	पूर्णांक gates_num;
पूर्ण;

अटल स्थिर काष्ठा clk_mt8167_mm_driver_data mt8167_mmsys_driver_data = अणु
	.gates_clk = mm_clks,
	.gates_num = ARRAY_SIZE(mm_clks),
पूर्ण;

अटल पूर्णांक clk_mt8167_mm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->parent->of_node;
	स्थिर काष्ठा clk_mt8167_mm_driver_data *data;
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक ret;

	clk_data = mtk_alloc_clk_data(CLK_MM_NR_CLK);
	अगर (!clk_data)
		वापस -ENOMEM;

	data = &mt8167_mmsys_driver_data;

	ret = mtk_clk_रेजिस्टर_gates(node, data->gates_clk, data->gates_num,
				     clk_data);
	अगर (ret)
		वापस ret;

	ret = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt8173_mm_drv = अणु
	.driver = अणु
		.name = "clk-mt8167-mm",
	पूर्ण,
	.probe = clk_mt8167_mm_probe,
पूर्ण;

builtin_platक्रमm_driver(clk_mt8173_mm_drv);
