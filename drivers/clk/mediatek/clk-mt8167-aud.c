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

अटल स्थिर काष्ठा mtk_gate_regs aud_cg_regs = अणु
	.set_ofs = 0x0,
	.clr_ofs = 0x0,
	.sta_ofs = 0x0,
पूर्ण;

#घोषणा GATE_AUD(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,			\
		.name = _name,			\
		.parent_name = _parent,		\
		.regs = &aud_cg_regs,		\
		.shअगरt = _shअगरt,		\
		.ops = &mtk_clk_gate_ops_no_setclr,		\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate aud_clks[] __initस्थिर = अणु
	GATE_AUD(CLK_AUD_AFE, "aud_afe", "clk26m_ck", 2),
	GATE_AUD(CLK_AUD_I2S, "aud_i2s", "i2s_infra_bck", 6),
	GATE_AUD(CLK_AUD_22M, "aud_22m", "rg_aud_engen1", 8),
	GATE_AUD(CLK_AUD_24M, "aud_24m", "rg_aud_engen2", 9),
	GATE_AUD(CLK_AUD_INTसूची, "aud_intdir", "rg_aud_spdif_in", 15),
	GATE_AUD(CLK_AUD_APLL2_TUNER, "aud_apll2_tuner", "rg_aud_engen2", 18),
	GATE_AUD(CLK_AUD_APLL_TUNER, "aud_apll_tuner", "rg_aud_engen1", 19),
	GATE_AUD(CLK_AUD_HDMI, "aud_hdmi", "apll12_div4", 20),
	GATE_AUD(CLK_AUD_SPDF, "aud_spdf", "apll12_div6", 21),
	GATE_AUD(CLK_AUD_ADC, "aud_adc", "aud_afe", 24),
	GATE_AUD(CLK_AUD_DAC, "aud_dac", "aud_afe", 25),
	GATE_AUD(CLK_AUD_DAC_PREDIS, "aud_dac_predis", "aud_afe", 26),
	GATE_AUD(CLK_AUD_TML, "aud_tml", "aud_afe", 27),
पूर्ण;

अटल व्योम __init mtk_audsys_init(काष्ठा device_node *node)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_AUD_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, aud_clks, ARRAY_SIZE(aud_clks), clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
			__func__, r);

पूर्ण
CLK_OF_DECLARE(mtk_audsys, "mediatek,mt8167-audsys", mtk_audsys_init);
