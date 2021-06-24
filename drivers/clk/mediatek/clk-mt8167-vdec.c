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

अटल स्थिर काष्ठा mtk_gate_regs vdec0_cg_regs = अणु
	.set_ofs = 0x0,
	.clr_ofs = 0x4,
	.sta_ofs = 0x0,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs vdec1_cg_regs = अणु
	.set_ofs = 0x8,
	.clr_ofs = 0xc,
	.sta_ofs = 0x8,
पूर्ण;

#घोषणा GATE_VDEC0_I(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &vdec0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	पूर्ण

#घोषणा GATE_VDEC1_I(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &vdec1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate vdec_clks[] __initस्थिर = अणु
	/* VDEC0 */
	GATE_VDEC0_I(CLK_VDEC_CKEN, "vdec_cken", "rg_vdec", 0),
	/* VDEC1 */
	GATE_VDEC1_I(CLK_VDEC_LARB1_CKEN, "vdec_larb1_cken", "smi_mm", 0),
पूर्ण;

अटल व्योम __init mtk_vdecsys_init(काष्ठा device_node *node)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_VDEC_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, vdec_clks, ARRAY_SIZE(vdec_clks), clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
			__func__, r);

पूर्ण
CLK_OF_DECLARE(mtk_vdecsys, "mediatek,mt8167-vdecsys", mtk_vdecsys_init);
