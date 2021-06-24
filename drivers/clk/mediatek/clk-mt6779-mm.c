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

अटल स्थिर काष्ठा mtk_gate_regs mm0_cg_regs = अणु
	.set_ofs = 0x0104,
	.clr_ofs = 0x0108,
	.sta_ofs = 0x0100,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs mm1_cg_regs = अणु
	.set_ofs = 0x0114,
	.clr_ofs = 0x0118,
	.sta_ofs = 0x0110,
पूर्ण;

#घोषणा GATE_MM0(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &mm0_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)
#घोषणा GATE_MM1(_id, _name, _parent, _shअगरt)			\
	GATE_MTK(_id, _name, _parent, &mm1_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_setclr)

अटल स्थिर काष्ठा mtk_gate mm_clks[] = अणु
	/* MM0 */
	GATE_MM0(CLK_MM_SMI_COMMON, "mm_smi_common", "mm_sel", 0),
	GATE_MM0(CLK_MM_SMI_LARB0, "mm_smi_larb0", "mm_sel", 1),
	GATE_MM0(CLK_MM_SMI_LARB1, "mm_smi_larb1", "mm_sel", 2),
	GATE_MM0(CLK_MM_GALS_COMM0, "mm_gals_comm0", "mm_sel", 3),
	GATE_MM0(CLK_MM_GALS_COMM1, "mm_gals_comm1", "mm_sel", 4),
	GATE_MM0(CLK_MM_GALS_CCU2MM, "mm_gals_ccu2mm", "mm_sel", 5),
	GATE_MM0(CLK_MM_GALS_IPU12MM, "mm_gals_ipu12mm", "mm_sel", 6),
	GATE_MM0(CLK_MM_GALS_IMG2MM, "mm_gals_img2mm", "mm_sel", 7),
	GATE_MM0(CLK_MM_GALS_CAM2MM, "mm_gals_cam2mm", "mm_sel", 8),
	GATE_MM0(CLK_MM_GALS_IPU2MM, "mm_gals_ipu2mm", "mm_sel", 9),
	GATE_MM0(CLK_MM_MDP_DL_TXCK, "mm_mdp_dl_txck", "mm_sel", 10),
	GATE_MM0(CLK_MM_IPU_DL_TXCK, "mm_ipu_dl_txck", "mm_sel", 11),
	GATE_MM0(CLK_MM_MDP_RDMA0, "mm_mdp_rdma0", "mm_sel", 12),
	GATE_MM0(CLK_MM_MDP_RDMA1, "mm_mdp_rdma1", "mm_sel", 13),
	GATE_MM0(CLK_MM_MDP_RSZ0, "mm_mdp_rsz0", "mm_sel", 14),
	GATE_MM0(CLK_MM_MDP_RSZ1, "mm_mdp_rsz1", "mm_sel", 15),
	GATE_MM0(CLK_MM_MDP_TDSHP, "mm_mdp_tdshp", "mm_sel", 16),
	GATE_MM0(CLK_MM_MDP_WROT0, "mm_mdp_wrot0", "mm_sel", 17),
	GATE_MM0(CLK_MM_MDP_WROT1, "mm_mdp_wrot1", "mm_sel", 18),
	GATE_MM0(CLK_MM_FAKE_ENG, "mm_fake_eng", "mm_sel", 19),
	GATE_MM0(CLK_MM_DISP_OVL0, "mm_disp_ovl0", "mm_sel", 20),
	GATE_MM0(CLK_MM_DISP_OVL0_2L, "mm_disp_ovl0_2l", "mm_sel", 21),
	GATE_MM0(CLK_MM_DISP_OVL1_2L, "mm_disp_ovl1_2l", "mm_sel", 22),
	GATE_MM0(CLK_MM_DISP_RDMA0, "mm_disp_rdma0", "mm_sel", 23),
	GATE_MM0(CLK_MM_DISP_RDMA1, "mm_disp_rdma1", "mm_sel", 24),
	GATE_MM0(CLK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_sel", 25),
	GATE_MM0(CLK_MM_DISP_COLOR0, "mm_disp_color0", "mm_sel", 26),
	GATE_MM0(CLK_MM_DISP_CCORR0, "mm_disp_ccorr0", "mm_sel", 27),
	GATE_MM0(CLK_MM_DISP_AAL0, "mm_disp_aal0", "mm_sel", 28),
	GATE_MM0(CLK_MM_DISP_GAMMA0, "mm_disp_gamma0", "mm_sel", 29),
	GATE_MM0(CLK_MM_DISP_DITHER0, "mm_disp_dither0", "mm_sel", 30),
	GATE_MM0(CLK_MM_DISP_SPLIT, "mm_disp_split", "mm_sel", 31),
	/* MM1 */
	GATE_MM1(CLK_MM_DSI0_MM_CK, "mm_dsi0_mmck", "mm_sel", 0),
	GATE_MM1(CLK_MM_DSI0_IF_CK, "mm_dsi0_ifck", "mm_sel", 1),
	GATE_MM1(CLK_MM_DPI_MM_CK, "mm_dpi_mmck", "mm_sel", 2),
	GATE_MM1(CLK_MM_DPI_IF_CK, "mm_dpi_ifck", "dpi0_sel", 3),
	GATE_MM1(CLK_MM_FAKE_ENG2, "mm_fake_eng2", "mm_sel", 4),
	GATE_MM1(CLK_MM_MDP_DL_RX_CK, "mm_mdp_dl_rxck", "mm_sel", 5),
	GATE_MM1(CLK_MM_IPU_DL_RX_CK, "mm_ipu_dl_rxck", "mm_sel", 6),
	GATE_MM1(CLK_MM_26M, "mm_26m", "f_f26m_ck", 7),
	GATE_MM1(CLK_MM_MM_R2Y, "mm_mmsys_r2y", "mm_sel", 8),
	GATE_MM1(CLK_MM_DISP_RSZ, "mm_disp_rsz", "mm_sel", 9),
	GATE_MM1(CLK_MM_MDP_AAL, "mm_mdp_aal", "mm_sel", 10),
	GATE_MM1(CLK_MM_MDP_HDR, "mm_mdp_hdr", "mm_sel", 11),
	GATE_MM1(CLK_MM_DBI_MM_CK, "mm_dbi_mmck", "mm_sel", 12),
	GATE_MM1(CLK_MM_DBI_IF_CK, "mm_dbi_ifck", "dpi0_sel", 13),
	GATE_MM1(CLK_MM_DISP_POSTMASK0, "mm_disp_pm0", "mm_sel", 14),
	GATE_MM1(CLK_MM_DISP_HRT_BW, "mm_disp_hrt_bw", "mm_sel", 15),
	GATE_MM1(CLK_MM_DISP_OVL_FBDC, "mm_disp_ovl_fbdc", "mm_sel", 16),
पूर्ण;

अटल पूर्णांक clk_mt6779_mm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->parent->of_node;
	काष्ठा clk_onecell_data *clk_data;

	clk_data = mtk_alloc_clk_data(CLK_MM_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, mm_clks, ARRAY_SIZE(mm_clks),
			       clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6779_mm_drv = अणु
	.probe = clk_mt6779_mm_probe,
	.driver = अणु
		.name = "clk-mt6779-mm",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6779_mm_drv);
