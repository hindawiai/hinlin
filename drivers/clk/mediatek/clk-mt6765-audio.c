<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Owen Chen <owen.chen@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt6765-clk.h>

अटल स्थिर काष्ठा mtk_gate_regs audio0_cg_regs = अणु
	.set_ofs = 0x0,
	.clr_ofs = 0x0,
	.sta_ofs = 0x0,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs audio1_cg_regs = अणु
	.set_ofs = 0x4,
	.clr_ofs = 0x4,
	.sta_ofs = 0x4,
पूर्ण;

#घोषणा GATE_AUDIO0(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audio0_cg_regs,		\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

#घोषणा GATE_AUDIO1(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audio1_cg_regs,		\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate audio_clks[] = अणु
	/* AUDIO0 */
	GATE_AUDIO0(CLK_AUDIO_AFE, "aud_afe", "audio_ck", 2),
	GATE_AUDIO0(CLK_AUDIO_22M, "aud_22m", "aud_engen1_ck", 8),
	GATE_AUDIO0(CLK_AUDIO_APLL_TUNER, "aud_apll_tuner",
		    "aud_engen1_ck", 19),
	GATE_AUDIO0(CLK_AUDIO_ADC, "aud_adc", "audio_ck", 24),
	GATE_AUDIO0(CLK_AUDIO_DAC, "aud_dac", "audio_ck", 25),
	GATE_AUDIO0(CLK_AUDIO_DAC_PREDIS, "aud_dac_predis",
		    "audio_ck", 26),
	GATE_AUDIO0(CLK_AUDIO_TML, "aud_tml", "audio_ck", 27),
	/* AUDIO1 */
	GATE_AUDIO1(CLK_AUDIO_I2S1_BCLK, "aud_i2s1_bclk",
		    "audio_ck", 4),
	GATE_AUDIO1(CLK_AUDIO_I2S2_BCLK, "aud_i2s2_bclk",
		    "audio_ck", 5),
	GATE_AUDIO1(CLK_AUDIO_I2S3_BCLK, "aud_i2s3_bclk",
		    "audio_ck", 6),
	GATE_AUDIO1(CLK_AUDIO_I2S4_BCLK, "aud_i2s4_bclk",
		    "audio_ck", 7),
पूर्ण;

अटल पूर्णांक clk_mt6765_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_AUDIO_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, audio_clks,
			       ARRAY_SIZE(audio_clks), clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	अगर (r)
		pr_err("%s(): could not register clock provider: %d\n",
		       __func__, r);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6765_audio[] = अणु
	अणु .compatible = "mediatek,mt6765-audsys", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_mt6765_audio_drv = अणु
	.probe = clk_mt6765_audio_probe,
	.driver = अणु
		.name = "clk-mt6765-audio",
		.of_match_table = of_match_clk_mt6765_audio,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6765_audio_drv);
