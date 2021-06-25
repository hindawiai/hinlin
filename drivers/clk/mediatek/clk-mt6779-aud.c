<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Wendell Lin <wendell.lin@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt6779-clk.h>

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

#घोषणा GATE_AUDIO0(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &audio0_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_no_setclr)
#घोषणा GATE_AUDIO1(_id, _name, _parent, _shअगरt)		\
	GATE_MTK(_id, _name, _parent, &audio1_cg_regs, _shअगरt,	\
		&mtk_clk_gate_ops_no_setclr)

अटल स्थिर काष्ठा mtk_gate audio_clks[] = अणु
	/* AUDIO0 */
	GATE_AUDIO0(CLK_AUD_AFE, "aud_afe", "audio_sel", 2),
	GATE_AUDIO0(CLK_AUD_22M, "aud_22m", "aud_eng1_sel", 8),
	GATE_AUDIO0(CLK_AUD_24M, "aud_24m", "aud_eng2_sel", 9),
	GATE_AUDIO0(CLK_AUD_APLL2_TUNER, "aud_apll2_tuner",
		    "aud_eng2_sel", 18),
	GATE_AUDIO0(CLK_AUD_APLL_TUNER, "aud_apll_tuner",
		    "aud_eng1_sel", 19),
	GATE_AUDIO0(CLK_AUD_TDM, "aud_tdm", "aud_eng1_sel", 20),
	GATE_AUDIO0(CLK_AUD_ADC, "aud_adc", "audio_sel", 24),
	GATE_AUDIO0(CLK_AUD_DAC, "aud_dac", "audio_sel", 25),
	GATE_AUDIO0(CLK_AUD_DAC_PREDIS, "aud_dac_predis",
		    "audio_sel", 26),
	GATE_AUDIO0(CLK_AUD_TML, "aud_tml", "audio_sel", 27),
	GATE_AUDIO0(CLK_AUD_NLE, "aud_nle", "audio_sel", 28),
	/* AUDIO1 */
	GATE_AUDIO1(CLK_AUD_I2S1_BCLK_SW, "aud_i2s1_bclk",
		    "audio_sel", 4),
	GATE_AUDIO1(CLK_AUD_I2S2_BCLK_SW, "aud_i2s2_bclk",
		    "audio_sel", 5),
	GATE_AUDIO1(CLK_AUD_I2S3_BCLK_SW, "aud_i2s3_bclk",
		    "audio_sel", 6),
	GATE_AUDIO1(CLK_AUD_I2S4_BCLK_SW, "aud_i2s4_bclk",
		    "audio_sel", 7),
	GATE_AUDIO1(CLK_AUD_I2S5_BCLK_SW, "aud_i2s5_bclk",
		    "audio_sel", 8),
	GATE_AUDIO1(CLK_AUD_CONN_I2S_ASRC, "aud_conn_i2s",
		    "audio_sel", 12),
	GATE_AUDIO1(CLK_AUD_GENERAL1_ASRC, "aud_general1",
		    "audio_sel", 13),
	GATE_AUDIO1(CLK_AUD_GENERAL2_ASRC, "aud_general2",
		    "audio_sel", 14),
	GATE_AUDIO1(CLK_AUD_DAC_HIRES, "aud_dac_hires",
		    "audio_h_sel", 15),
	GATE_AUDIO1(CLK_AUD_ADC_HIRES, "aud_adc_hires",
		    "audio_h_sel", 16),
	GATE_AUDIO1(CLK_AUD_ADC_HIRES_TML, "aud_adc_hires_tml",
		    "audio_h_sel", 17),
	GATE_AUDIO1(CLK_AUD_PDN_ADDA6_ADC, "aud_pdn_adda6_adc",
		    "audio_sel", 20),
	GATE_AUDIO1(CLK_AUD_ADDA6_ADC_HIRES, "aud_adda6_adc_hires",
		    "audio_h_sel",
		    21),
	GATE_AUDIO1(CLK_AUD_3RD_DAC, "aud_3rd_dac", "audio_sel",
		    28),
	GATE_AUDIO1(CLK_AUD_3RD_DAC_PREDIS, "aud_3rd_dac_predis",
		    "audio_sel", 29),
	GATE_AUDIO1(CLK_AUD_3RD_DAC_TML, "aud_3rd_dac_tml",
		    "audio_sel", 30),
	GATE_AUDIO1(CLK_AUD_3RD_DAC_HIRES, "aud_3rd_dac_hires",
		    "audio_h_sel", 31),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match_clk_mt6779_aud[] = अणु
	अणु .compatible = "mediatek,mt6779-audio", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक clk_mt6779_aud_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_AUD_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, audio_clks, ARRAY_SIZE(audio_clks),
			       clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt6779_aud_drv = अणु
	.probe = clk_mt6779_aud_probe,
	.driver = अणु
		.name = "clk-mt6779-aud",
		.of_match_table = of_match_clk_mt6779_aud,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt6779_aud_drv);
