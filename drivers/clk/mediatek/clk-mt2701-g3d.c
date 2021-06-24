<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt2701-clk.h>

#घोषणा GATE_G3D(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &g3d_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate_regs g3d_cg_regs = अणु
	.sta_ofs = 0x0,
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate g3d_clks[] = अणु
	GATE_G3D(CLK_G3DSYS_CORE, "g3d_core", "mfg_sel", 0),
पूर्ण;

अटल पूर्णांक clk_mt2701_g3dsys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_G3DSYS_NR);

	mtk_clk_रेजिस्टर_gates(node, g3d_clks, ARRAY_SIZE(g3d_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	mtk_रेजिस्टर_reset_controller(node, 1, 0xc);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt2701_g3d[] = अणु
	अणु
		.compatible = "mediatek,mt2701-g3dsys",
		.data = clk_mt2701_g3dsys_init,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक clk_mt2701_g3d_probe(काष्ठा platक्रमm_device *pdev)
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

अटल काष्ठा platक्रमm_driver clk_mt2701_g3d_drv = अणु
	.probe = clk_mt2701_g3d_probe,
	.driver = अणु
		.name = "clk-mt2701-g3d",
		.of_match_table = of_match_clk_mt2701_g3d,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt2701_g3d_drv);
