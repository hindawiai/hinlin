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

अटल स्थिर काष्ठा mtk_gate_regs eth_cg_regs = अणु
	.sta_ofs = 0x0030,
पूर्ण;

#घोषणा GATE_ETH(_id, _name, _parent, _shअगरt) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &eth_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate eth_clks[] = अणु
	GATE_ETH(CLK_ETHSYS_HSDMA, "hsdma_clk", "ethif_sel", 5),
	GATE_ETH(CLK_ETHSYS_ESW, "esw_clk", "ethpll_500m_ck", 6),
	GATE_ETH(CLK_ETHSYS_GP2, "gp2_clk", "trgpll", 7),
	GATE_ETH(CLK_ETHSYS_GP1, "gp1_clk", "ethpll_500m_ck", 8),
	GATE_ETH(CLK_ETHSYS_PCM, "pcm_clk", "ethif_sel", 11),
	GATE_ETH(CLK_ETHSYS_GDMA, "gdma_clk", "ethif_sel", 14),
	GATE_ETH(CLK_ETHSYS_I2S, "i2s_clk", "ethif_sel", 17),
	GATE_ETH(CLK_ETHSYS_CRYPTO, "crypto_clk", "ethif_sel", 29),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt2701_eth[] = अणु
	अणु .compatible = "mediatek,mt2701-ethsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt2701_eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_ETHSYS_NR);

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

अटल काष्ठा platक्रमm_driver clk_mt2701_eth_drv = अणु
	.probe = clk_mt2701_eth_probe,
	.driver = अणु
		.name = "clk-mt2701-eth",
		.of_match_table = of_match_clk_mt2701_eth,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2701_eth_drv);
