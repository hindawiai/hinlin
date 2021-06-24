<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Chen Zhong <chen.zhong@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt7622-clk.h>

#घोषणा GATE_ETH(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &eth_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate_regs eth_cg_regs = अणु
	.set_ofs = 0x30,
	.clr_ofs = 0x30,
	.sta_ofs = 0x30,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate eth_clks[] = अणु
	GATE_ETH(CLK_ETH_HSDMA_EN, "eth_hsdma_en", "eth_sel", 5),
	GATE_ETH(CLK_ETH_ESW_EN, "eth_esw_en", "eth_500m", 6),
	GATE_ETH(CLK_ETH_GP2_EN, "eth_gp2_en", "txclk_src_pre", 7),
	GATE_ETH(CLK_ETH_GP1_EN, "eth_gp1_en", "txclk_src_pre", 8),
	GATE_ETH(CLK_ETH_GP0_EN, "eth_gp0_en", "txclk_src_pre", 9),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs sgmii_cg_regs = अणु
	.set_ofs = 0xE4,
	.clr_ofs = 0xE4,
	.sta_ofs = 0xE4,
पूर्ण;

#घोषणा GATE_SGMII(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &sgmii_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate sgmii_clks[] = अणु
	GATE_SGMII(CLK_SGMII_TX250M_EN, "sgmii_tx250m_en",
		   "ssusb_tx250m", 2),
	GATE_SGMII(CLK_SGMII_RX250M_EN, "sgmii_rx250m_en",
		   "ssusb_eq_rx250m", 3),
	GATE_SGMII(CLK_SGMII_CDR_REF, "sgmii_cdr_ref",
		   "ssusb_cdr_ref", 4),
	GATE_SGMII(CLK_SGMII_CDR_FB, "sgmii_cdr_fb",
		   "ssusb_cdr_fb", 5),
पूर्ण;

अटल पूर्णांक clk_mt7622_ethsys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_ETH_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, eth_clks, ARRAY_SIZE(eth_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	mtk_रेजिस्टर_reset_controller(node, 1, 0x34);

	वापस r;
पूर्ण

अटल पूर्णांक clk_mt7622_sgmiisys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_SGMII_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, sgmii_clks, ARRAY_SIZE(sgmii_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt7622_eth[] = अणु
	अणु
		.compatible = "mediatek,mt7622-ethsys",
		.data = clk_mt7622_ethsys_init,
	पूर्ण, अणु
		.compatible = "mediatek,mt7622-sgmiisys",
		.data = clk_mt7622_sgmiisys_init,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक clk_mt7622_eth_probe(काष्ठा platक्रमm_device *pdev)
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

अटल काष्ठा platक्रमm_driver clk_mt7622_eth_drv = अणु
	.probe = clk_mt7622_eth_probe,
	.driver = अणु
		.name = "clk-mt7622-eth",
		.of_match_table = of_match_clk_mt7622_eth,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt7622_eth_drv);
