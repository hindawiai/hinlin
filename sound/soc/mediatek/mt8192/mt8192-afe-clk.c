<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt8192-afe-clk.c  --  Mediatek 8192 afe घड़ी ctrl
//
// Copyright (c) 2020 MediaTek Inc.
// Author: Shane Chien <shane.chien@mediatek.com>
//

#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "mt8192-afe-clk.h"
#समावेश "mt8192-afe-common.h"

अटल स्थिर अक्षर *aud_clks[CLK_NUM] = अणु
	[CLK_AFE] = "aud_afe_clk",
	[CLK_TML] = "aud_tml_clk",
	[CLK_APLL22M] = "aud_apll22m_clk",
	[CLK_APLL24M] = "aud_apll24m_clk",
	[CLK_APLL1_TUNER] = "aud_apll1_tuner_clk",
	[CLK_APLL2_TUNER] = "aud_apll2_tuner_clk",
	[CLK_NLE] = "aud_nle",
	[CLK_INFRA_SYS_AUDIO] = "aud_infra_clk",
	[CLK_INFRA_AUDIO_26M] = "aud_infra_26m_clk",
	[CLK_MUX_AUDIO] = "top_mux_audio",
	[CLK_MUX_AUDIOINTBUS] = "top_mux_audio_int",
	[CLK_TOP_MAINPLL_D4_D4] = "top_mainpll_d4_d4",
	[CLK_TOP_MUX_AUD_1] = "top_mux_aud_1",
	[CLK_TOP_APLL1_CK] = "top_apll1_ck",
	[CLK_TOP_MUX_AUD_2] = "top_mux_aud_2",
	[CLK_TOP_APLL2_CK] = "top_apll2_ck",
	[CLK_TOP_MUX_AUD_ENG1] = "top_mux_aud_eng1",
	[CLK_TOP_APLL1_D4] = "top_apll1_d4",
	[CLK_TOP_MUX_AUD_ENG2] = "top_mux_aud_eng2",
	[CLK_TOP_APLL2_D4] = "top_apll2_d4",
	[CLK_TOP_MUX_AUDIO_H] = "top_mux_audio_h",
	[CLK_TOP_I2S0_M_SEL] = "top_i2s0_m_sel",
	[CLK_TOP_I2S1_M_SEL] = "top_i2s1_m_sel",
	[CLK_TOP_I2S2_M_SEL] = "top_i2s2_m_sel",
	[CLK_TOP_I2S3_M_SEL] = "top_i2s3_m_sel",
	[CLK_TOP_I2S4_M_SEL] = "top_i2s4_m_sel",
	[CLK_TOP_I2S5_M_SEL] = "top_i2s5_m_sel",
	[CLK_TOP_I2S6_M_SEL] = "top_i2s6_m_sel",
	[CLK_TOP_I2S7_M_SEL] = "top_i2s7_m_sel",
	[CLK_TOP_I2S8_M_SEL] = "top_i2s8_m_sel",
	[CLK_TOP_I2S9_M_SEL] = "top_i2s9_m_sel",
	[CLK_TOP_APLL12_DIV0] = "top_apll12_div0",
	[CLK_TOP_APLL12_DIV1] = "top_apll12_div1",
	[CLK_TOP_APLL12_DIV2] = "top_apll12_div2",
	[CLK_TOP_APLL12_DIV3] = "top_apll12_div3",
	[CLK_TOP_APLL12_DIV4] = "top_apll12_div4",
	[CLK_TOP_APLL12_DIVB] = "top_apll12_divb",
	[CLK_TOP_APLL12_DIV5] = "top_apll12_div5",
	[CLK_TOP_APLL12_DIV6] = "top_apll12_div6",
	[CLK_TOP_APLL12_DIV7] = "top_apll12_div7",
	[CLK_TOP_APLL12_DIV8] = "top_apll12_div8",
	[CLK_TOP_APLL12_DIV9] = "top_apll12_div9",
	[CLK_CLK26M] = "top_clk26m_clk",
पूर्ण;

पूर्णांक mt8192_set_audio_पूर्णांक_bus_parent(काष्ठा mtk_base_afe *afe,
				    पूर्णांक clk_id)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	ret = clk_set_parent(afe_priv->clk[CLK_MUX_AUDIOINTBUS],
			     afe_priv->clk[clk_id]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIOINTBUS],
			aud_clks[clk_id], ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apll1_mux_setting(काष्ठा mtk_base_afe *afe, bool enable)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	अगर (enable) अणु
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_1]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_1], ret);
			जाओ EXIT;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_1],
				     afe_priv->clk[CLK_TOP_APLL1_CK]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_1],
				aud_clks[CLK_TOP_APLL1_CK], ret);
			जाओ EXIT;
		पूर्ण

		/* 180.6336 / 4 = 45.1584MHz */
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG1], ret);
			जाओ EXIT;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1],
				     afe_priv->clk[CLK_TOP_APLL1_D4]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG1],
				aud_clks[CLK_TOP_APLL1_D4], ret);
			जाओ EXIT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1],
				     afe_priv->clk[CLK_CLK26M]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG1],
				aud_clks[CLK_CLK26M], ret);
			जाओ EXIT;
		पूर्ण
		clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1]);

		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_1],
				     afe_priv->clk[CLK_CLK26M]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_1],
				aud_clks[CLK_CLK26M], ret);
			जाओ EXIT;
		पूर्ण
		clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_1]);
	पूर्ण

EXIT:
	वापस ret;
पूर्ण

अटल पूर्णांक apll2_mux_setting(काष्ठा mtk_base_afe *afe, bool enable)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	अगर (enable) अणु
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_2]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_2], ret);
			जाओ EXIT;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_2],
				     afe_priv->clk[CLK_TOP_APLL2_CK]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_2],
				aud_clks[CLK_TOP_APLL2_CK], ret);
			जाओ EXIT;
		पूर्ण

		/* 196.608 / 4 = 49.152MHz */
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG2], ret);
			जाओ EXIT;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2],
				     afe_priv->clk[CLK_TOP_APLL2_D4]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG2],
				aud_clks[CLK_TOP_APLL2_D4], ret);
			जाओ EXIT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2],
				     afe_priv->clk[CLK_CLK26M]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG2],
				aud_clks[CLK_CLK26M], ret);
			जाओ EXIT;
		पूर्ण
		clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2]);

		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_2],
				     afe_priv->clk[CLK_CLK26M]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_2],
				aud_clks[CLK_CLK26M], ret);
			जाओ EXIT;
		पूर्ण
		clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_2]);
	पूर्ण

EXIT:
	वापस ret;
पूर्ण

पूर्णांक mt8192_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	dev_info(afe->dev, "%s()\n", __func__);

	ret = clk_prepare_enable(afe_priv->clk[CLK_INFRA_SYS_AUDIO]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_INFRA_SYS_AUDIO], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_INFRA_AUDIO_26M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_INFRA_AUDIO_26M], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_MUX_AUDIO]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIO], ret);
		जाओ EXIT;
	पूर्ण
	ret = clk_set_parent(afe_priv->clk[CLK_MUX_AUDIO],
			     afe_priv->clk[CLK_CLK26M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIO],
			aud_clks[CLK_CLK26M], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_MUX_AUDIOINTBUS]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIOINTBUS], ret);
		जाओ EXIT;
	पूर्ण

	ret = mt8192_set_audio_पूर्णांक_bus_parent(afe, CLK_CLK26M);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIOINTBUS],
			aud_clks[CLK_CLK26M], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUDIO_H],
			     afe_priv->clk[CLK_TOP_APLL2_CK]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_TOP_MUX_AUDIO_H],
			aud_clks[CLK_TOP_APLL2_CK], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_AFE]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_AFE], ret);
		जाओ EXIT;
	पूर्ण

EXIT:
	वापस ret;
पूर्ण

व्योम mt8192_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	dev_info(afe->dev, "%s()\n", __func__);

	clk_disable_unprepare(afe_priv->clk[CLK_AFE]);
	mt8192_set_audio_पूर्णांक_bus_parent(afe, CLK_CLK26M);
	clk_disable_unprepare(afe_priv->clk[CLK_MUX_AUDIOINTBUS]);
	clk_disable_unprepare(afe_priv->clk[CLK_MUX_AUDIO]);
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_AUDIO_26M]);
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUDIO]);
पूर्ण

पूर्णांक mt8192_apll1_enable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	/* setting क्रम APLL */
	apll1_mux_setting(afe, true);

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL22M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL22M], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL1_TUNER]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL1_TUNER], ret);
		जाओ EXIT;
	पूर्ण

	regmap_update_bits(afe->regmap, AFE_APLL1_TUNER_CFG,
			   0x0000FFF7, 0x00000832);
	regmap_update_bits(afe->regmap, AFE_APLL1_TUNER_CFG, 0x1, 0x1);

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_22M_ON_MASK_SFT,
			   0x1 << AFE_22M_ON_SFT);

EXIT:
	वापस ret;
पूर्ण

व्योम mt8192_apll1_disable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_22M_ON_MASK_SFT,
			   0x0 << AFE_22M_ON_SFT);

	regmap_update_bits(afe->regmap, AFE_APLL1_TUNER_CFG, 0x1, 0x0);

	clk_disable_unprepare(afe_priv->clk[CLK_APLL1_TUNER]);
	clk_disable_unprepare(afe_priv->clk[CLK_APLL22M]);

	apll1_mux_setting(afe, false);
पूर्ण

पूर्णांक mt8192_apll2_enable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	/* setting क्रम APLL */
	apll2_mux_setting(afe, true);

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL24M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL24M], ret);
		जाओ EXIT;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL2_TUNER]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL2_TUNER], ret);
		जाओ EXIT;
	पूर्ण

	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG,
			   0x0000FFF7, 0x00000634);
	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG, 0x1, 0x1);

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_24M_ON_MASK_SFT,
			   0x1 << AFE_24M_ON_SFT);

EXIT:
	वापस ret;
पूर्ण

व्योम mt8192_apll2_disable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_24M_ON_MASK_SFT,
			   0x0 << AFE_24M_ON_SFT);

	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG, 0x1, 0x0);

	clk_disable_unprepare(afe_priv->clk[CLK_APLL2_TUNER]);
	clk_disable_unprepare(afe_priv->clk[CLK_APLL24M]);

	apll2_mux_setting(afe, false);
पूर्ण

पूर्णांक mt8192_get_apll_rate(काष्ठा mtk_base_afe *afe, पूर्णांक apll)
अणु
	वापस (apll == MT8192_APLL1) ? 180633600 : 196608000;
पूर्ण

पूर्णांक mt8192_get_apll_by_rate(काष्ठा mtk_base_afe *afe, पूर्णांक rate)
अणु
	वापस ((rate % 8000) == 0) ? MT8192_APLL2 : MT8192_APLL1;
पूर्ण

पूर्णांक mt8192_get_apll_by_name(काष्ठा mtk_base_afe *afe, स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, APLL1_W_NAME) == 0)
		वापस MT8192_APLL1;
	अन्यथा
		वापस MT8192_APLL2;
पूर्ण

/* mck */
काष्ठा mt8192_mck_भाग अणु
	पूर्णांक m_sel_id;
	पूर्णांक भाग_clk_id;
	/* below will be deprecated */
	पूर्णांक भाग_pdn_reg;
	पूर्णांक भाग_pdn_mask_sft;
	पूर्णांक भाग_reg;
	पूर्णांक भाग_mask_sft;
	पूर्णांक भाग_mask;
	पूर्णांक भाग_sft;
	पूर्णांक भाग_apll_sel_reg;
	पूर्णांक भाग_apll_sel_mask_sft;
	पूर्णांक भाग_apll_sel_sft;
पूर्ण;

अटल स्थिर काष्ठा mt8192_mck_भाग mck_भाग[MT8192_MCK_NUM] = अणु
	[MT8192_I2S0_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S0_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV0,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV0_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_2,
		.भाग_mask_sft = APLL12_CK_DIV0_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV0_MASK,
		.भाग_sft = APLL12_CK_DIV0_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S0_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S0_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S1_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S1_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV1,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV1_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_2,
		.भाग_mask_sft = APLL12_CK_DIV1_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV1_MASK,
		.भाग_sft = APLL12_CK_DIV1_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S1_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S1_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S2_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S2_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV2,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV2_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_2,
		.भाग_mask_sft = APLL12_CK_DIV2_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV2_MASK,
		.भाग_sft = APLL12_CK_DIV2_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S2_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S2_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S3_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S3_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV3,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV3_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_2,
		.भाग_mask_sft = APLL12_CK_DIV3_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV3_MASK,
		.भाग_sft = APLL12_CK_DIV3_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S3_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S3_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S4_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S4_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV4,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV4_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_3,
		.भाग_mask_sft = APLL12_CK_DIV4_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV4_MASK,
		.भाग_sft = APLL12_CK_DIV4_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S4_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S4_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S4_BCK] = अणु
		.m_sel_id = -1,
		.भाग_clk_id = CLK_TOP_APLL12_DIVB,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIVB_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_2,
		.भाग_mask_sft = APLL12_CK_DIVB_MASK_SFT,
		.भाग_mask = APLL12_CK_DIVB_MASK,
		.भाग_sft = APLL12_CK_DIVB_SFT,
	पूर्ण,
	[MT8192_I2S5_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S5_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV5,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV5_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_3,
		.भाग_mask_sft = APLL12_CK_DIV5_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV5_MASK,
		.भाग_sft = APLL12_CK_DIV5_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S5_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S5_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S6_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S6_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV6,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV6_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_3,
		.भाग_mask_sft = APLL12_CK_DIV6_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV6_MASK,
		.भाग_sft = APLL12_CK_DIV6_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S6_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S6_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S7_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S7_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV7,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV7_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_4,
		.भाग_mask_sft = APLL12_CK_DIV7_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV7_MASK,
		.भाग_sft = APLL12_CK_DIV7_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S7_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S7_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S8_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S8_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV8,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV8_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_4,
		.भाग_mask_sft = APLL12_CK_DIV8_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV8_MASK,
		.भाग_sft = APLL12_CK_DIV8_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S8_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S8_MCK_SEL_SFT,
	पूर्ण,
	[MT8192_I2S9_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S9_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV9,
		.भाग_pdn_reg = CLK_AUDDIV_0,
		.भाग_pdn_mask_sft = APLL12_DIV9_PDN_MASK_SFT,
		.भाग_reg = CLK_AUDDIV_4,
		.भाग_mask_sft = APLL12_CK_DIV9_MASK_SFT,
		.भाग_mask = APLL12_CK_DIV9_MASK,
		.भाग_sft = APLL12_CK_DIV9_SFT,
		.भाग_apll_sel_reg = CLK_AUDDIV_0,
		.भाग_apll_sel_mask_sft = APLL_I2S9_MCK_SEL_MASK_SFT,
		.भाग_apll_sel_sft = APLL_I2S9_MCK_SEL_SFT,
	पूर्ण,
पूर्ण;

पूर्णांक mt8192_mck_enable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id, पूर्णांक rate)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक apll = mt8192_get_apll_by_rate(afe, rate);
	पूर्णांक apll_clk_id = apll == MT8192_APLL1 ?
			  CLK_TOP_MUX_AUD_1 : CLK_TOP_MUX_AUD_2;
	पूर्णांक m_sel_id = mck_भाग[mck_id].m_sel_id;
	पूर्णांक भाग_clk_id = mck_भाग[mck_id].भाग_clk_id;
	पूर्णांक ret;

	/* select apll */
	अगर (m_sel_id >= 0) अणु
		ret = clk_prepare_enable(afe_priv->clk[m_sel_id]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[m_sel_id], ret);
			वापस ret;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[m_sel_id],
				     afe_priv->clk[apll_clk_id]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s(), clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[m_sel_id],
				aud_clks[apll_clk_id], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* enable भाग, set rate */
	ret = clk_prepare_enable(afe_priv->clk[भाग_clk_id]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[भाग_clk_id], ret);
		वापस ret;
	पूर्ण
	ret = clk_set_rate(afe_priv->clk[भाग_clk_id], rate);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_set_rate %s, rate %d, fail %d\n",
			__func__, aud_clks[भाग_clk_id],
			rate, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt8192_mck_disable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक m_sel_id = mck_भाग[mck_id].m_sel_id;
	पूर्णांक भाग_clk_id = mck_भाग[mck_id].भाग_clk_id;

	clk_disable_unprepare(afe_priv->clk[भाग_clk_id]);
	अगर (m_sel_id >= 0)
		clk_disable_unprepare(afe_priv->clk[m_sel_id]);
पूर्ण

पूर्णांक mt8192_init_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा device_node *of_node = afe->dev->of_node;
	पूर्णांक i = 0;

	afe_priv->clk = devm_kसुस्मृति(afe->dev, CLK_NUM, माप(*afe_priv->clk),
				     GFP_KERNEL);
	अगर (!afe_priv->clk)
		वापस -ENOMEM;

	क्रम (i = 0; i < CLK_NUM; i++) अणु
		afe_priv->clk[i] = devm_clk_get(afe->dev, aud_clks[i]);
		अगर (IS_ERR(afe_priv->clk[i])) अणु
			dev_warn(afe->dev, "%s devm_clk_get %s fail, ret %ld\n",
				 __func__,
				 aud_clks[i], PTR_ERR(afe_priv->clk[i]));
			afe_priv->clk[i] = शून्य;
		पूर्ण
	पूर्ण

	afe_priv->apmixedsys = syscon_regmap_lookup_by_phandle(of_node,
							       "mediatek,apmixedsys");
	अगर (IS_ERR(afe_priv->apmixedsys)) अणु
		dev_err(afe->dev, "%s() Cannot find apmixedsys controller: %ld\n",
			__func__, PTR_ERR(afe_priv->apmixedsys));
		वापस PTR_ERR(afe_priv->apmixedsys);
	पूर्ण

	afe_priv->topckgen = syscon_regmap_lookup_by_phandle(of_node,
							     "mediatek,topckgen");
	अगर (IS_ERR(afe_priv->topckgen)) अणु
		dev_err(afe->dev, "%s() Cannot find topckgen controller: %ld\n",
			__func__, PTR_ERR(afe_priv->topckgen));
		वापस PTR_ERR(afe_priv->topckgen);
	पूर्ण

	afe_priv->infracfg = syscon_regmap_lookup_by_phandle(of_node,
							     "mediatek,infracfg");
	अगर (IS_ERR(afe_priv->infracfg)) अणु
		dev_err(afe->dev, "%s() Cannot find infracfg: %ld\n",
			__func__, PTR_ERR(afe_priv->infracfg));
		वापस PTR_ERR(afe_priv->infracfg);
	पूर्ण

	वापस 0;
पूर्ण
