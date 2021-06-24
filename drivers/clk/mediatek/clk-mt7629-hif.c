<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 MediaTek Inc.
 * Author: Wenzhen Yu <Wenzhen Yu@mediatek.com>
 *	   Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt7629-clk.h>

#घोषणा GATE_PCIE(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &pcie_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

#घोषणा GATE_SSUSB(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &ssusb_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate_regs pcie_cg_regs = अणु
	.set_ofs = 0x30,
	.clr_ofs = 0x30,
	.sta_ofs = 0x30,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs ssusb_cg_regs = अणु
	.set_ofs = 0x30,
	.clr_ofs = 0x30,
	.sta_ofs = 0x30,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate ssusb_clks[] = अणु
	GATE_SSUSB(CLK_SSUSB_U2_PHY_1P_EN, "ssusb_u2_phy_1p",
		   "to_u2_phy_1p", 0),
	GATE_SSUSB(CLK_SSUSB_U2_PHY_EN, "ssusb_u2_phy_en", "to_u2_phy", 1),
	GATE_SSUSB(CLK_SSUSB_REF_EN, "ssusb_ref_en", "to_usb3_ref", 5),
	GATE_SSUSB(CLK_SSUSB_SYS_EN, "ssusb_sys_en", "to_usb3_sys", 6),
	GATE_SSUSB(CLK_SSUSB_MCU_EN, "ssusb_mcu_en", "to_usb3_mcu", 7),
	GATE_SSUSB(CLK_SSUSB_DMA_EN, "ssusb_dma_en", "to_usb3_dma", 8),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate pcie_clks[] = अणु
	GATE_PCIE(CLK_PCIE_P1_AUX_EN, "pcie_p1_aux_en", "p1_1mhz", 12),
	GATE_PCIE(CLK_PCIE_P1_OBFF_EN, "pcie_p1_obff_en", "free_run_4mhz", 13),
	GATE_PCIE(CLK_PCIE_P1_AHB_EN, "pcie_p1_ahb_en", "from_top_ahb", 14),
	GATE_PCIE(CLK_PCIE_P1_AXI_EN, "pcie_p1_axi_en", "from_top_axi", 15),
	GATE_PCIE(CLK_PCIE_P1_MAC_EN, "pcie_p1_mac_en", "pcie1_mac_en", 16),
	GATE_PCIE(CLK_PCIE_P1_PIPE_EN, "pcie_p1_pipe_en", "pcie1_pipe_en", 17),
	GATE_PCIE(CLK_PCIE_P0_AUX_EN, "pcie_p0_aux_en", "p0_1mhz", 18),
	GATE_PCIE(CLK_PCIE_P0_OBFF_EN, "pcie_p0_obff_en", "free_run_4mhz", 19),
	GATE_PCIE(CLK_PCIE_P0_AHB_EN, "pcie_p0_ahb_en", "from_top_ahb", 20),
	GATE_PCIE(CLK_PCIE_P0_AXI_EN, "pcie_p0_axi_en", "from_top_axi", 21),
	GATE_PCIE(CLK_PCIE_P0_MAC_EN, "pcie_p0_mac_en", "pcie0_mac_en", 22),
	GATE_PCIE(CLK_PCIE_P0_PIPE_EN, "pcie_p0_pipe_en", "pcie0_pipe_en", 23),
पूर्ण;

अटल पूर्णांक clk_mt7629_ssusbsys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_SSUSB_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, ssusb_clks, ARRAY_SIZE(ssusb_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	mtk_रेजिस्टर_reset_controller(node, 1, 0x34);

	वापस r;
पूर्ण

अटल पूर्णांक clk_mt7629_pciesys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_PCIE_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, pcie_clks, ARRAY_SIZE(pcie_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	mtk_रेजिस्टर_reset_controller(node, 1, 0x34);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt7629_hअगर[] = अणु
	अणु
		.compatible = "mediatek,mt7629-pciesys",
		.data = clk_mt7629_pciesys_init,
	पूर्ण, अणु
		.compatible = "mediatek,mt7629-ssusbsys",
		.data = clk_mt7629_ssusbsys_init,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक clk_mt7629_hअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*clk_init)(काष्ठा platक्रमm_device *);
	पूर्णांक r;

	clk_init = of_device_get_match_data(&pdev->dev);
	अगर (!clk_init)
		वापस -EINVAL;

	r = clk_init(pdev);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt7629_hअगर_drv = अणु
	.probe = clk_mt7629_hअगर_probe,
	.driver = अणु
		.name = "clk-mt7629-hif",
		.of_match_table = of_match_clk_mt7629_hअगर,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt7629_hअगर_drv);
