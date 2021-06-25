<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt8183-afe-clk.c  --  Mediatek 8183 afe घड़ी ctrl
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/clk.h>

#समावेश "mt8183-afe-common.h"
#समावेश "mt8183-afe-clk.h"
#समावेश "mt8183-reg.h"

क्रमागत अणु
	CLK_AFE = 0,
	CLK_TML,
	CLK_APLL22M,
	CLK_APLL24M,
	CLK_APLL1_TUNER,
	CLK_APLL2_TUNER,
	CLK_I2S1_BCLK_SW,
	CLK_I2S2_BCLK_SW,
	CLK_I2S3_BCLK_SW,
	CLK_I2S4_BCLK_SW,
	CLK_INFRA_SYS_AUDIO,
	CLK_MUX_AUDIO,
	CLK_MUX_AUDIOINTBUS,
	CLK_TOP_SYSPLL_D2_D4,
	/* apll related mux */
	CLK_TOP_MUX_AUD_1,
	CLK_TOP_APLL1_CK,
	CLK_TOP_MUX_AUD_2,
	CLK_TOP_APLL2_CK,
	CLK_TOP_MUX_AUD_ENG1,
	CLK_TOP_APLL1_D8,
	CLK_TOP_MUX_AUD_ENG2,
	CLK_TOP_APLL2_D8,
	CLK_TOP_I2S0_M_SEL,
	CLK_TOP_I2S1_M_SEL,
	CLK_TOP_I2S2_M_SEL,
	CLK_TOP_I2S3_M_SEL,
	CLK_TOP_I2S4_M_SEL,
	CLK_TOP_I2S5_M_SEL,
	CLK_TOP_APLL12_DIV0,
	CLK_TOP_APLL12_DIV1,
	CLK_TOP_APLL12_DIV2,
	CLK_TOP_APLL12_DIV3,
	CLK_TOP_APLL12_DIV4,
	CLK_TOP_APLL12_DIVB,
	CLK_CLK26M,
	CLK_NUM
पूर्ण;

अटल स्थिर अक्षर *aud_clks[CLK_NUM] = अणु
	[CLK_AFE] = "aud_afe_clk",
	[CLK_TML] = "aud_tml_clk",
	[CLK_APLL22M] = "aud_apll22m_clk",
	[CLK_APLL24M] = "aud_apll24m_clk",
	[CLK_APLL1_TUNER] = "aud_apll1_tuner_clk",
	[CLK_APLL2_TUNER] = "aud_apll2_tuner_clk",
	[CLK_I2S1_BCLK_SW] = "aud_i2s1_bclk_sw",
	[CLK_I2S2_BCLK_SW] = "aud_i2s2_bclk_sw",
	[CLK_I2S3_BCLK_SW] = "aud_i2s3_bclk_sw",
	[CLK_I2S4_BCLK_SW] = "aud_i2s4_bclk_sw",
	[CLK_INFRA_SYS_AUDIO] = "aud_infra_clk",
	[CLK_MUX_AUDIO] = "top_mux_audio",
	[CLK_MUX_AUDIOINTBUS] = "top_mux_aud_intbus",
	[CLK_TOP_SYSPLL_D2_D4] = "top_syspll_d2_d4",
	[CLK_TOP_MUX_AUD_1] = "top_mux_aud_1",
	[CLK_TOP_APLL1_CK] = "top_apll1_ck",
	[CLK_TOP_MUX_AUD_2] = "top_mux_aud_2",
	[CLK_TOP_APLL2_CK] = "top_apll2_ck",
	[CLK_TOP_MUX_AUD_ENG1] = "top_mux_aud_eng1",
	[CLK_TOP_APLL1_D8] = "top_apll1_d8",
	[CLK_TOP_MUX_AUD_ENG2] = "top_mux_aud_eng2",
	[CLK_TOP_APLL2_D8] = "top_apll2_d8",
	[CLK_TOP_I2S0_M_SEL] = "top_i2s0_m_sel",
	[CLK_TOP_I2S1_M_SEL] = "top_i2s1_m_sel",
	[CLK_TOP_I2S2_M_SEL] = "top_i2s2_m_sel",
	[CLK_TOP_I2S3_M_SEL] = "top_i2s3_m_sel",
	[CLK_TOP_I2S4_M_SEL] = "top_i2s4_m_sel",
	[CLK_TOP_I2S5_M_SEL] = "top_i2s5_m_sel",
	[CLK_TOP_APLL12_DIV0] = "top_apll12_div0",
	[CLK_TOP_APLL12_DIV1] = "top_apll12_div1",
	[CLK_TOP_APLL12_DIV2] = "top_apll12_div2",
	[CLK_TOP_APLL12_DIV3] = "top_apll12_div3",
	[CLK_TOP_APLL12_DIV4] = "top_apll12_div4",
	[CLK_TOP_APLL12_DIVB] = "top_apll12_divb",
	[CLK_CLK26M] = "top_clk26m_clk",
पूर्ण;

पूर्णांक mt8183_init_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक i;

	afe_priv->clk = devm_kसुस्मृति(afe->dev, CLK_NUM, माप(*afe_priv->clk),
				     GFP_KERNEL);
	अगर (!afe_priv->clk)
		वापस -ENOMEM;

	क्रम (i = 0; i < CLK_NUM; i++) अणु
		afe_priv->clk[i] = devm_clk_get(afe->dev, aud_clks[i]);
		अगर (IS_ERR(afe_priv->clk[i])) अणु
			dev_err(afe->dev, "%s(), devm_clk_get %s fail, ret %ld\n",
				__func__, aud_clks[i],
				PTR_ERR(afe_priv->clk[i]));
			वापस PTR_ERR(afe_priv->clk[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt8183_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(afe_priv->clk[CLK_INFRA_SYS_AUDIO]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_INFRA_SYS_AUDIO], ret);
		जाओ CLK_INFRA_SYS_AUDIO_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_MUX_AUDIO]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIO], ret);
		जाओ CLK_MUX_AUDIO_ERR;
	पूर्ण

	ret = clk_set_parent(afe_priv->clk[CLK_MUX_AUDIO],
			     afe_priv->clk[CLK_CLK26M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIO],
			aud_clks[CLK_CLK26M], ret);
		जाओ CLK_MUX_AUDIO_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_MUX_AUDIOINTBUS]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIOINTBUS], ret);
		जाओ CLK_MUX_AUDIO_INTBUS_ERR;
	पूर्ण

	ret = clk_set_parent(afe_priv->clk[CLK_MUX_AUDIOINTBUS],
			     afe_priv->clk[CLK_TOP_SYSPLL_D2_D4]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_set_parent %s-%s fail %d\n",
			__func__, aud_clks[CLK_MUX_AUDIOINTBUS],
			aud_clks[CLK_TOP_SYSPLL_D2_D4], ret);
		जाओ CLK_MUX_AUDIO_INTBUS_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_AFE]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_AFE], ret);
		जाओ CLK_AFE_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_I2S1_BCLK_SW]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_I2S1_BCLK_SW], ret);
		जाओ CLK_I2S1_BCLK_SW_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_I2S2_BCLK_SW]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_I2S2_BCLK_SW], ret);
		जाओ CLK_I2S2_BCLK_SW_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_I2S3_BCLK_SW]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_I2S3_BCLK_SW], ret);
		जाओ CLK_I2S3_BCLK_SW_ERR;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_I2S4_BCLK_SW]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_I2S4_BCLK_SW], ret);
		जाओ CLK_I2S4_BCLK_SW_ERR;
	पूर्ण

	वापस 0;

CLK_I2S4_BCLK_SW_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_I2S3_BCLK_SW]);
CLK_I2S3_BCLK_SW_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_I2S2_BCLK_SW]);
CLK_I2S2_BCLK_SW_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_I2S1_BCLK_SW]);
CLK_I2S1_BCLK_SW_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_AFE]);
CLK_AFE_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_MUX_AUDIOINTBUS]);
CLK_MUX_AUDIO_INTBUS_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_MUX_AUDIO]);
CLK_MUX_AUDIO_ERR:
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUDIO]);
CLK_INFRA_SYS_AUDIO_ERR:
	वापस ret;
पूर्ण

पूर्णांक mt8183_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;

	clk_disable_unprepare(afe_priv->clk[CLK_I2S4_BCLK_SW]);
	clk_disable_unprepare(afe_priv->clk[CLK_I2S3_BCLK_SW]);
	clk_disable_unprepare(afe_priv->clk[CLK_I2S2_BCLK_SW]);
	clk_disable_unprepare(afe_priv->clk[CLK_I2S1_BCLK_SW]);
	clk_disable_unprepare(afe_priv->clk[CLK_AFE]);
	clk_disable_unprepare(afe_priv->clk[CLK_MUX_AUDIOINTBUS]);
	clk_disable_unprepare(afe_priv->clk[CLK_MUX_AUDIO]);
	clk_disable_unprepare(afe_priv->clk[CLK_INFRA_SYS_AUDIO]);

	वापस 0;
पूर्ण

/* apll */
अटल पूर्णांक apll1_mux_setting(काष्ठा mtk_base_afe *afe, bool enable)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	अगर (enable) अणु
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_1]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_1], ret);
			जाओ ERR_ENABLE_CLK_TOP_MUX_AUD_1;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_1],
				     afe_priv->clk[CLK_TOP_APLL1_CK]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_1],
				aud_clks[CLK_TOP_APLL1_CK], ret);
			जाओ ERR_SELECT_CLK_TOP_MUX_AUD_1;
		पूर्ण

		/* 180.6336 / 8 = 22.5792MHz */
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG1], ret);
			जाओ ERR_ENABLE_CLK_TOP_MUX_AUD_ENG1;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1],
				     afe_priv->clk[CLK_TOP_APLL1_D8]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG1],
				aud_clks[CLK_TOP_APLL1_D8], ret);
			जाओ ERR_SELECT_CLK_TOP_MUX_AUD_ENG1;
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

	वापस 0;

ERR_SELECT_CLK_TOP_MUX_AUD_ENG1:
	clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1],
		       afe_priv->clk[CLK_CLK26M]);
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_ENG1]);
ERR_ENABLE_CLK_TOP_MUX_AUD_ENG1:
ERR_SELECT_CLK_TOP_MUX_AUD_1:
	clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_1],
		       afe_priv->clk[CLK_CLK26M]);
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_1]);
ERR_ENABLE_CLK_TOP_MUX_AUD_1:
EXIT:
	वापस ret;
पूर्ण

अटल पूर्णांक apll2_mux_setting(काष्ठा mtk_base_afe *afe, bool enable)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	अगर (enable) अणु
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_2]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_2], ret);
			जाओ ERR_ENABLE_CLK_TOP_MUX_AUD_2;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_2],
				     afe_priv->clk[CLK_TOP_APLL2_CK]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_2],
				aud_clks[CLK_TOP_APLL2_CK], ret);
			जाओ ERR_SELECT_CLK_TOP_MUX_AUD_2;
		पूर्ण

		/* 196.608 / 8 = 24.576MHz */
		ret = clk_prepare_enable(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG2], ret);
			जाओ ERR_ENABLE_CLK_TOP_MUX_AUD_ENG2;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2],
				     afe_priv->clk[CLK_TOP_APLL2_D8]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[CLK_TOP_MUX_AUD_ENG2],
				aud_clks[CLK_TOP_APLL2_D8], ret);
			जाओ ERR_SELECT_CLK_TOP_MUX_AUD_ENG2;
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

	वापस 0;

ERR_SELECT_CLK_TOP_MUX_AUD_ENG2:
	clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2],
		       afe_priv->clk[CLK_CLK26M]);
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_ENG2]);
ERR_ENABLE_CLK_TOP_MUX_AUD_ENG2:
ERR_SELECT_CLK_TOP_MUX_AUD_2:
	clk_set_parent(afe_priv->clk[CLK_TOP_MUX_AUD_2],
		       afe_priv->clk[CLK_CLK26M]);
	clk_disable_unprepare(afe_priv->clk[CLK_TOP_MUX_AUD_2]);
ERR_ENABLE_CLK_TOP_MUX_AUD_2:
EXIT:
	वापस ret;
पूर्ण

पूर्णांक mt8183_apll1_enable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	/* setting क्रम APLL */
	apll1_mux_setting(afe, true);

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL22M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL22M], ret);
		जाओ ERR_CLK_APLL22M;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL1_TUNER]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL1_TUNER], ret);
		जाओ ERR_CLK_APLL1_TUNER;
	पूर्ण

	regmap_update_bits(afe->regmap, AFE_APLL1_TUNER_CFG,
			   0x0000FFF7, 0x00000832);
	regmap_update_bits(afe->regmap, AFE_APLL1_TUNER_CFG, 0x1, 0x1);

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_22M_ON_MASK_SFT,
			   0x1 << AFE_22M_ON_SFT);

	वापस 0;

ERR_CLK_APLL1_TUNER:
	clk_disable_unprepare(afe_priv->clk[CLK_APLL22M]);
ERR_CLK_APLL22M:
	वापस ret;
पूर्ण

व्योम mt8183_apll1_disable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_22M_ON_MASK_SFT,
			   0x0 << AFE_22M_ON_SFT);

	regmap_update_bits(afe->regmap, AFE_APLL1_TUNER_CFG, 0x1, 0x0);

	clk_disable_unprepare(afe_priv->clk[CLK_APLL1_TUNER]);
	clk_disable_unprepare(afe_priv->clk[CLK_APLL22M]);

	apll1_mux_setting(afe, false);
पूर्ण

पूर्णांक mt8183_apll2_enable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	/* setting क्रम APLL */
	apll2_mux_setting(afe, true);

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL24M]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL24M], ret);
		जाओ ERR_CLK_APLL24M;
	पूर्ण

	ret = clk_prepare_enable(afe_priv->clk[CLK_APLL2_TUNER]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[CLK_APLL2_TUNER], ret);
		जाओ ERR_CLK_APLL2_TUNER;
	पूर्ण

	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG,
			   0x0000FFF7, 0x00000634);
	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG, 0x1, 0x1);

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_24M_ON_MASK_SFT,
			   0x1 << AFE_24M_ON_SFT);

	वापस 0;

ERR_CLK_APLL2_TUNER:
	clk_disable_unprepare(afe_priv->clk[CLK_APLL24M]);
ERR_CLK_APLL24M:
	वापस ret;
पूर्ण

व्योम mt8183_apll2_disable(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_24M_ON_MASK_SFT,
			   0x0 << AFE_24M_ON_SFT);

	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG, 0x1, 0x0);

	clk_disable_unprepare(afe_priv->clk[CLK_APLL2_TUNER]);
	clk_disable_unprepare(afe_priv->clk[CLK_APLL24M]);

	apll2_mux_setting(afe, false);
पूर्ण

पूर्णांक mt8183_get_apll_rate(काष्ठा mtk_base_afe *afe, पूर्णांक apll)
अणु
	वापस (apll == MT8183_APLL1) ? 180633600 : 196608000;
पूर्ण

पूर्णांक mt8183_get_apll_by_rate(काष्ठा mtk_base_afe *afe, पूर्णांक rate)
अणु
	वापस ((rate % 8000) == 0) ? MT8183_APLL2 : MT8183_APLL1;
पूर्ण

पूर्णांक mt8183_get_apll_by_name(काष्ठा mtk_base_afe *afe, स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, APLL1_W_NAME) == 0)
		वापस MT8183_APLL1;
	अन्यथा
		वापस MT8183_APLL2;
पूर्ण

/* mck */
काष्ठा mt8183_mck_भाग अणु
	पूर्णांक m_sel_id;
	पूर्णांक भाग_clk_id;
पूर्ण;

अटल स्थिर काष्ठा mt8183_mck_भाग mck_भाग[MT8183_MCK_NUM] = अणु
	[MT8183_I2S0_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S0_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV0,
	पूर्ण,
	[MT8183_I2S1_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S1_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV1,
	पूर्ण,
	[MT8183_I2S2_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S2_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV2,
	पूर्ण,
	[MT8183_I2S3_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S3_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV3,
	पूर्ण,
	[MT8183_I2S4_MCK] = अणु
		.m_sel_id = CLK_TOP_I2S4_M_SEL,
		.भाग_clk_id = CLK_TOP_APLL12_DIV4,
	पूर्ण,
	[MT8183_I2S4_BCK] = अणु
		.m_sel_id = -1,
		.भाग_clk_id = CLK_TOP_APLL12_DIVB,
	पूर्ण,
	[MT8183_I2S5_MCK] = अणु
		.m_sel_id = -1,
		.भाग_clk_id = -1,
	पूर्ण,
पूर्ण;

पूर्णांक mt8183_mck_enable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id, पूर्णांक rate)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक apll = mt8183_get_apll_by_rate(afe, rate);
	पूर्णांक apll_clk_id = apll == MT8183_APLL1 ?
			  CLK_TOP_MUX_AUD_1 : CLK_TOP_MUX_AUD_2;
	पूर्णांक m_sel_id = mck_भाग[mck_id].m_sel_id;
	पूर्णांक भाग_clk_id = mck_भाग[mck_id].भाग_clk_id;
	पूर्णांक ret;

	/* i2s5 mck not support */
	अगर (mck_id == MT8183_I2S5_MCK)
		वापस 0;

	/* select apll */
	अगर (m_sel_id >= 0) अणु
		ret = clk_prepare_enable(afe_priv->clk[m_sel_id]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
				__func__, aud_clks[m_sel_id], ret);
			जाओ ERR_ENABLE_MCLK;
		पूर्ण
		ret = clk_set_parent(afe_priv->clk[m_sel_id],
				     afe_priv->clk[apll_clk_id]);
		अगर (ret) अणु
			dev_err(afe->dev, "%s(), clk_set_parent %s-%s fail %d\n",
				__func__, aud_clks[m_sel_id],
				aud_clks[apll_clk_id], ret);
			जाओ ERR_SELECT_MCLK;
		पूर्ण
	पूर्ण

	/* enable भाग, set rate */
	ret = clk_prepare_enable(afe_priv->clk[भाग_clk_id]);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_prepare_enable %s fail %d\n",
			__func__, aud_clks[भाग_clk_id], ret);
		जाओ ERR_ENABLE_MCLK_DIV;
	पूर्ण
	ret = clk_set_rate(afe_priv->clk[भाग_clk_id], rate);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), clk_set_rate %s, rate %d, fail %d\n",
			__func__, aud_clks[भाग_clk_id],
			rate, ret);
		जाओ ERR_SET_MCLK_RATE;
	पूर्ण

	वापस 0;

ERR_SET_MCLK_RATE:
	clk_disable_unprepare(afe_priv->clk[भाग_clk_id]);
ERR_ENABLE_MCLK_DIV:
ERR_SELECT_MCLK:
	अगर (m_sel_id >= 0)
		clk_disable_unprepare(afe_priv->clk[m_sel_id]);
ERR_ENABLE_MCLK:
	वापस ret;
पूर्ण

व्योम mt8183_mck_disable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक m_sel_id = mck_भाग[mck_id].m_sel_id;
	पूर्णांक भाग_clk_id = mck_भाग[mck_id].भाग_clk_id;

	/* i2s5 mck not support */
	अगर (mck_id == MT8183_I2S5_MCK)
		वापस;

	clk_disable_unprepare(afe_priv->clk[भाग_clk_id]);
	अगर (m_sel_id >= 0)
		clk_disable_unprepare(afe_priv->clk[m_sel_id]);
पूर्ण
