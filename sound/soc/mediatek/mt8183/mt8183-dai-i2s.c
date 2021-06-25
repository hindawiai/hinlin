<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI I2S Control
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश "mt8183-afe-clk.h"
#समावेश "mt8183-afe-common.h"
#समावेश "mt8183-interconnection.h"
#समावेश "mt8183-reg.h"

क्रमागत अणु
	I2S_FMT_EIAJ = 0,
	I2S_FMT_I2S = 1,
पूर्ण;

क्रमागत अणु
	I2S_WLEN_16_BIT = 0,
	I2S_WLEN_32_BIT = 1,
पूर्ण;

क्रमागत अणु
	I2S_HD_NORMAL = 0,
	I2S_HD_LOW_JITTER = 1,
पूर्ण;

क्रमागत अणु
	I2S1_SEL_O28_O29 = 0,
	I2S1_SEL_O03_O04 = 1,
पूर्ण;

क्रमागत अणु
	I2S_IN_PAD_CONNSYS = 0,
	I2S_IN_PAD_IO_MUX = 1,
पूर्ण;

काष्ठा mtk_afe_i2s_priv अणु
	पूर्णांक id;
	पूर्णांक rate; /* क्रम determine which apll to use */
	पूर्णांक low_jitter_en;

	स्थिर अक्षर *share_property_name;
	पूर्णांक share_i2s_id;

	पूर्णांक mclk_id;
	पूर्णांक mclk_rate;
	पूर्णांक mclk_apll;

	पूर्णांक use_eiaj;
पूर्ण;

अटल अचिन्हित पूर्णांक get_i2s_wlen(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_pcm_क्रमmat_physical_width(क्रमmat) <= 16 ?
	       I2S_WLEN_16_BIT : I2S_WLEN_32_BIT;
पूर्ण

#घोषणा MTK_AFE_I2S0_KCONTROL_NAME "I2S0_HD_Mux"
#घोषणा MTK_AFE_I2S1_KCONTROL_NAME "I2S1_HD_Mux"
#घोषणा MTK_AFE_I2S2_KCONTROL_NAME "I2S2_HD_Mux"
#घोषणा MTK_AFE_I2S3_KCONTROL_NAME "I2S3_HD_Mux"
#घोषणा MTK_AFE_I2S5_KCONTROL_NAME "I2S5_HD_Mux"

#घोषणा I2S0_HD_EN_W_NAME "I2S0_HD_EN"
#घोषणा I2S1_HD_EN_W_NAME "I2S1_HD_EN"
#घोषणा I2S2_HD_EN_W_NAME "I2S2_HD_EN"
#घोषणा I2S3_HD_EN_W_NAME "I2S3_HD_EN"
#घोषणा I2S5_HD_EN_W_NAME "I2S5_HD_EN"

#घोषणा I2S0_MCLK_EN_W_NAME "I2S0_MCLK_EN"
#घोषणा I2S1_MCLK_EN_W_NAME "I2S1_MCLK_EN"
#घोषणा I2S2_MCLK_EN_W_NAME "I2S2_MCLK_EN"
#घोषणा I2S3_MCLK_EN_W_NAME "I2S3_MCLK_EN"
#घोषणा I2S5_MCLK_EN_W_NAME "I2S5_MCLK_EN"

अटल पूर्णांक get_i2s_id_by_name(काष्ठा mtk_base_afe *afe,
			      स्थिर अक्षर *name)
अणु
	अगर (म_भेदन(name, "I2S0", 4) == 0)
		वापस MT8183_DAI_I2S_0;
	अन्यथा अगर (म_भेदन(name, "I2S1", 4) == 0)
		वापस MT8183_DAI_I2S_1;
	अन्यथा अगर (म_भेदन(name, "I2S2", 4) == 0)
		वापस MT8183_DAI_I2S_2;
	अन्यथा अगर (म_भेदन(name, "I2S3", 4) == 0)
		वापस MT8183_DAI_I2S_3;
	अन्यथा अगर (म_भेदन(name, "I2S5", 4) == 0)
		वापस MT8183_DAI_I2S_5;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल काष्ठा mtk_afe_i2s_priv *get_i2s_priv_by_name(काष्ठा mtk_base_afe *afe,
						     स्थिर अक्षर *name)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक dai_id = get_i2s_id_by_name(afe, name);

	अगर (dai_id < 0)
		वापस शून्य;

	वापस afe_priv->dai_priv[dai_id];
पूर्ण

/* low jitter control */
अटल स्थिर अक्षर * स्थिर mt8183_i2s_hd_str[] = अणु
	"Normal", "Low_Jitter"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत mt8183_i2s_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(mt8183_i2s_hd_str),
			    mt8183_i2s_hd_str),
पूर्ण;

अटल पूर्णांक mt8183_i2s_hd_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;

	i2s_priv = get_i2s_priv_by_name(afe, kcontrol->id.name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस -EINVAL;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = i2s_priv->low_jitter_en;

	वापस 0;
पूर्ण

अटल पूर्णांक mt8183_i2s_hd_set(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	पूर्णांक hd_en;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= e->items)
		वापस -EINVAL;

	hd_en = ucontrol->value.पूर्णांकeger.value[0];

	dev_info(afe->dev, "%s(), kcontrol name %s, hd_en %d\n",
		 __func__, kcontrol->id.name, hd_en);

	i2s_priv = get_i2s_priv_by_name(afe, kcontrol->id.name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस -EINVAL;
	पूर्ण

	i2s_priv->low_jitter_en = hd_en;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mtk_dai_i2s_controls[] = अणु
	SOC_ENUM_EXT(MTK_AFE_I2S0_KCONTROL_NAME, mt8183_i2s_क्रमागत[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S1_KCONTROL_NAME, mt8183_i2s_क्रमागत[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S2_KCONTROL_NAME, mt8183_i2s_क्रमागत[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S3_KCONTROL_NAME, mt8183_i2s_क्रमागत[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S5_KCONTROL_NAME, mt8183_i2s_क्रमागत[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
पूर्ण;

/* dai component */
/* पूर्णांकerconnection */
अटल स्थिर काष्ठा snd_kcontrol_new mtk_i2s3_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN0, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN0, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN0, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN0,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN0,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN0,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_i2s3_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN1, I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN1, I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN1, I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN1,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN1,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN1,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH2", AFE_CONN1,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH2", AFE_CONN1,
				    I_PCM_2_CAP_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_i2s1_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN28, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN28, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN28, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN28,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN28,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN28,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_i2s1_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN29, I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN29, I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN29, I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN29,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN29,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN29,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH2", AFE_CONN29,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH2", AFE_CONN29,
				    I_PCM_2_CAP_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_i2s5_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN30, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN30, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN30, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN30,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN30,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN30,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_i2s5_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN31, I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN31, I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN31, I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN31,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN31,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN31,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH2", AFE_CONN31,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH2", AFE_CONN31,
				    I_PCM_2_CAP_CH2, 1, 0),
पूर्ण;

क्रमागत अणु
	SUPPLY_SEQ_APLL,
	SUPPLY_SEQ_I2S_MCLK_EN,
	SUPPLY_SEQ_I2S_HD_EN,
	SUPPLY_SEQ_I2S_EN,
पूर्ण;

अटल पूर्णांक mtk_apll_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);

	dev_info(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (म_भेद(w->name, APLL1_W_NAME) == 0)
			mt8183_apll1_enable(afe);
		अन्यथा
			mt8183_apll2_enable(afe);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (म_भेद(w->name, APLL1_W_NAME) == 0)
			mt8183_apll1_disable(afe);
		अन्यथा
			mt8183_apll2_disable(afe);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mclk_en_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;

	dev_info(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	i2s_priv = get_i2s_priv_by_name(afe, w->name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8183_mck_enable(afe, i2s_priv->mclk_id, i2s_priv->mclk_rate);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		i2s_priv->mclk_rate = 0;
		mt8183_mck_disable(afe, i2s_priv->mclk_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget mtk_dai_i2s_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("I2S1_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s1_ch1_mix,
			   ARRAY_SIZE(mtk_i2s1_ch1_mix)),
	SND_SOC_DAPM_MIXER("I2S1_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s1_ch2_mix,
			   ARRAY_SIZE(mtk_i2s1_ch2_mix)),

	SND_SOC_DAPM_MIXER("I2S3_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s3_ch1_mix,
			   ARRAY_SIZE(mtk_i2s3_ch1_mix)),
	SND_SOC_DAPM_MIXER("I2S3_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s3_ch2_mix,
			   ARRAY_SIZE(mtk_i2s3_ch2_mix)),

	SND_SOC_DAPM_MIXER("I2S5_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s5_ch1_mix,
			   ARRAY_SIZE(mtk_i2s5_ch1_mix)),
	SND_SOC_DAPM_MIXER("I2S5_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s5_ch2_mix,
			   ARRAY_SIZE(mtk_i2s5_ch2_mix)),

	/* i2s en*/
	SND_SOC_DAPM_SUPPLY_S("I2S0_EN", SUPPLY_SEQ_I2S_EN,
			      AFE_I2S_CON, I2S_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S1_EN", SUPPLY_SEQ_I2S_EN,
			      AFE_I2S_CON1, I2S_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2_EN", SUPPLY_SEQ_I2S_EN,
			      AFE_I2S_CON2, I2S_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S3_EN", SUPPLY_SEQ_I2S_EN,
			      AFE_I2S_CON3, I2S_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S5_EN", SUPPLY_SEQ_I2S_EN,
			      AFE_I2S_CON4, I2S5_EN_SFT, 0,
			      शून्य, 0),
	/* i2s hd en */
	SND_SOC_DAPM_SUPPLY_S(I2S0_HD_EN_W_NAME, SUPPLY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON, I2S1_HD_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S(I2S1_HD_EN_W_NAME, SUPPLY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON1, I2S2_HD_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S(I2S2_HD_EN_W_NAME, SUPPLY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON2, I2S3_HD_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S(I2S3_HD_EN_W_NAME, SUPPLY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON3, I2S4_HD_EN_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S(I2S5_HD_EN_W_NAME, SUPPLY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON4, I2S5_HD_EN_SFT, 0,
			      शून्य, 0),

	/* i2s mclk en */
	SND_SOC_DAPM_SUPPLY_S(I2S0_MCLK_EN_W_NAME, SUPPLY_SEQ_I2S_MCLK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mclk_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S(I2S1_MCLK_EN_W_NAME, SUPPLY_SEQ_I2S_MCLK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mclk_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S(I2S2_MCLK_EN_W_NAME, SUPPLY_SEQ_I2S_MCLK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mclk_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S(I2S3_MCLK_EN_W_NAME, SUPPLY_SEQ_I2S_MCLK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mclk_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S(I2S5_MCLK_EN_W_NAME, SUPPLY_SEQ_I2S_MCLK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mclk_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* apll */
	SND_SOC_DAPM_SUPPLY_S(APLL1_W_NAME, SUPPLY_SEQ_APLL,
			      SND_SOC_NOPM, 0, 0,
			      mtk_apll_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S(APLL2_W_NAME, SUPPLY_SEQ_APLL,
			      SND_SOC_NOPM, 0, 0,
			      mtk_apll_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल पूर्णांक mtk_afe_i2s_share_connect(काष्ठा snd_soc_dapm_widget *source,
				     काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;

	i2s_priv = get_i2s_priv_by_name(afe, sink->name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस 0;
	पूर्ण

	अगर (i2s_priv->share_i2s_id < 0)
		वापस 0;

	वापस i2s_priv->share_i2s_id == get_i2s_id_by_name(afe, source->name);
पूर्ण

अटल पूर्णांक mtk_afe_i2s_hd_connect(काष्ठा snd_soc_dapm_widget *source,
				  काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;

	i2s_priv = get_i2s_priv_by_name(afe, sink->name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस 0;
	पूर्ण

	अगर (get_i2s_id_by_name(afe, sink->name) ==
	    get_i2s_id_by_name(afe, source->name))
		वापस i2s_priv->low_jitter_en;

	/* check अगर share i2s need hd en */
	अगर (i2s_priv->share_i2s_id < 0)
		वापस 0;

	अगर (i2s_priv->share_i2s_id == get_i2s_id_by_name(afe, source->name))
		वापस i2s_priv->low_jitter_en;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_afe_i2s_apll_connect(काष्ठा snd_soc_dapm_widget *source,
				    काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;
	पूर्णांक cur_apll;
	पूर्णांक i2s_need_apll;

	i2s_priv = get_i2s_priv_by_name(afe, w->name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस 0;
	पूर्ण

	/* which apll */
	cur_apll = mt8183_get_apll_by_name(afe, source->name);

	/* choose APLL from i2s rate */
	i2s_need_apll = mt8183_get_apll_by_rate(afe, i2s_priv->rate);

	वापस (i2s_need_apll == cur_apll) ? 1 : 0;
पूर्ण

अटल पूर्णांक mtk_afe_i2s_mclk_connect(काष्ठा snd_soc_dapm_widget *source,
				    काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;

	i2s_priv = get_i2s_priv_by_name(afe, sink->name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस 0;
	पूर्ण

	अगर (get_i2s_id_by_name(afe, sink->name) ==
	    get_i2s_id_by_name(afe, source->name))
		वापस (i2s_priv->mclk_rate > 0) ? 1 : 0;

	/* check अगर share i2s need mclk */
	अगर (i2s_priv->share_i2s_id < 0)
		वापस 0;

	अगर (i2s_priv->share_i2s_id == get_i2s_id_by_name(afe, source->name))
		वापस (i2s_priv->mclk_rate > 0) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_afe_mclk_apll_connect(काष्ठा snd_soc_dapm_widget *source,
				     काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mtk_afe_i2s_priv *i2s_priv;
	पूर्णांक cur_apll;

	i2s_priv = get_i2s_priv_by_name(afe, w->name);

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस 0;
	पूर्ण

	/* which apll */
	cur_apll = mt8183_get_apll_by_name(afe, source->name);

	वापस (i2s_priv->mclk_apll == cur_apll) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route mtk_dai_i2s_routes[] = अणु
	/* i2s0 */
	अणु"I2S0", शून्य, "I2S0_EN"पूर्ण,
	अणु"I2S0", शून्य, "I2S1_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S0", शून्य, "I2S2_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S0", शून्य, "I2S3_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S0", शून्य, "I2S5_EN", mtk_afe_i2s_share_connectपूर्ण,

	अणु"I2S0", शून्य, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S0", शून्य, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S0", शून्य, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S0", शून्य, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S0", शून्य, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणुI2S0_HD_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,
	अणुI2S0_HD_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,

	अणु"I2S0", शून्य, I2S0_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S0", शून्य, I2S1_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S0", शून्य, I2S2_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S0", शून्य, I2S3_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S0", शून्य, I2S5_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणुI2S0_MCLK_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,
	अणुI2S0_MCLK_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,

	/* i2s1 */
	अणु"I2S1_CH1", "DL1_CH1", "DL1"पूर्ण,
	अणु"I2S1_CH2", "DL1_CH2", "DL1"पूर्ण,

	अणु"I2S1_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"I2S1_CH2", "DL2_CH2", "DL2"पूर्ण,

	अणु"I2S1_CH1", "DL3_CH1", "DL3"पूर्ण,
	अणु"I2S1_CH2", "DL3_CH2", "DL3"पूर्ण,

	अणु"I2S1", शून्य, "I2S1_CH1"पूर्ण,
	अणु"I2S1", शून्य, "I2S1_CH2"पूर्ण,

	अणु"I2S1", शून्य, "I2S0_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S1", शून्य, "I2S1_EN"पूर्ण,
	अणु"I2S1", शून्य, "I2S2_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S1", शून्य, "I2S3_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S1", शून्य, "I2S5_EN", mtk_afe_i2s_share_connectपूर्ण,

	अणु"I2S1", शून्य, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S1", शून्य, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S1", शून्य, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S1", शून्य, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S1", शून्य, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणुI2S1_HD_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,
	अणुI2S1_HD_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,

	अणु"I2S1", शून्य, I2S0_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S1", शून्य, I2S1_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S1", शून्य, I2S2_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S1", शून्य, I2S3_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S1", शून्य, I2S5_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणुI2S1_MCLK_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,
	अणुI2S1_MCLK_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,

	/* i2s2 */
	अणु"I2S2", शून्य, "I2S0_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S2", शून्य, "I2S1_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S2", शून्य, "I2S2_EN"पूर्ण,
	अणु"I2S2", शून्य, "I2S3_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S2", शून्य, "I2S5_EN", mtk_afe_i2s_share_connectपूर्ण,

	अणु"I2S2", शून्य, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S2", शून्य, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S2", शून्य, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S2", शून्य, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S2", शून्य, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणुI2S2_HD_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,
	अणुI2S2_HD_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,

	अणु"I2S2", शून्य, I2S0_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S2", शून्य, I2S1_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S2", शून्य, I2S2_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S2", शून्य, I2S3_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S2", शून्य, I2S5_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणुI2S2_MCLK_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,
	अणुI2S2_MCLK_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,

	/* i2s3 */
	अणु"I2S3_CH1", "DL1_CH1", "DL1"पूर्ण,
	अणु"I2S3_CH2", "DL1_CH2", "DL1"पूर्ण,

	अणु"I2S3_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"I2S3_CH2", "DL2_CH2", "DL2"पूर्ण,

	अणु"I2S3_CH1", "DL3_CH1", "DL3"पूर्ण,
	अणु"I2S3_CH2", "DL3_CH2", "DL3"पूर्ण,

	अणु"I2S3", शून्य, "I2S3_CH1"पूर्ण,
	अणु"I2S3", शून्य, "I2S3_CH2"पूर्ण,

	अणु"I2S3", शून्य, "I2S0_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S3", शून्य, "I2S1_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S3", शून्य, "I2S2_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S3", शून्य, "I2S3_EN"पूर्ण,
	अणु"I2S3", शून्य, "I2S5_EN", mtk_afe_i2s_share_connectपूर्ण,

	अणु"I2S3", शून्य, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S3", शून्य, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S3", शून्य, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S3", शून्य, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S3", शून्य, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणुI2S3_HD_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,
	अणुI2S3_HD_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,

	अणु"I2S3", शून्य, I2S0_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S3", शून्य, I2S1_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S3", शून्य, I2S2_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S3", शून्य, I2S3_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S3", शून्य, I2S5_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणुI2S3_MCLK_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,
	अणुI2S3_MCLK_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,

	/* i2s5 */
	अणु"I2S5_CH1", "DL1_CH1", "DL1"पूर्ण,
	अणु"I2S5_CH2", "DL1_CH2", "DL1"पूर्ण,

	अणु"I2S5_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"I2S5_CH2", "DL2_CH2", "DL2"पूर्ण,

	अणु"I2S5_CH1", "DL3_CH1", "DL3"पूर्ण,
	अणु"I2S5_CH2", "DL3_CH2", "DL3"पूर्ण,

	अणु"I2S5", शून्य, "I2S5_CH1"पूर्ण,
	अणु"I2S5", शून्य, "I2S5_CH2"पूर्ण,

	अणु"I2S5", शून्य, "I2S0_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S5", शून्य, "I2S1_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S5", शून्य, "I2S2_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S5", शून्य, "I2S3_EN", mtk_afe_i2s_share_connectपूर्ण,
	अणु"I2S5", शून्य, "I2S5_EN"पूर्ण,

	अणु"I2S5", शून्य, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S5", शून्य, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S5", शून्य, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S5", शून्य, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणु"I2S5", शून्य, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connectपूर्ण,
	अणुI2S5_HD_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,
	अणुI2S5_HD_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_i2s_apll_connectपूर्ण,

	अणु"I2S5", शून्य, I2S0_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S5", शून्य, I2S1_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S5", शून्य, I2S2_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S5", शून्य, I2S3_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणु"I2S5", शून्य, I2S5_MCLK_EN_W_NAME, mtk_afe_i2s_mclk_connectपूर्ण,
	अणुI2S5_MCLK_EN_W_NAME, शून्य, APLL1_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,
	अणुI2S5_MCLK_EN_W_NAME, शून्य, APLL2_W_NAME, mtk_afe_mclk_apll_connectपूर्ण,
पूर्ण;

/* dai ops */
अटल पूर्णांक mtk_dai_i2s_config(काष्ठा mtk_base_afe *afe,
			      काष्ठा snd_pcm_hw_params *params,
			      पूर्णांक i2s_id)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_i2s_priv *i2s_priv = afe_priv->dai_priv[i2s_id];

	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक rate_reg = mt8183_rate_transक्रमm(afe->dev,
						      rate, i2s_id);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक i2s_con = 0, fmt_con = I2S_FMT_I2S << I2S_FMT_SFT;
	पूर्णांक ret = 0;

	dev_info(afe->dev, "%s(), id %d, rate %d, format %d\n",
		 __func__,
		 i2s_id,
		 rate, क्रमmat);

	अगर (i2s_priv) अणु
		i2s_priv->rate = rate;

		अगर (i2s_priv->use_eiaj)
			fmt_con = I2S_FMT_EIAJ << I2S_FMT_SFT;
	पूर्ण अन्यथा अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
	पूर्ण

	चयन (i2s_id) अणु
	हाल MT8183_DAI_I2S_0:
		regmap_update_bits(afe->regmap, AFE_DAC_CON1,
				   I2S_MODE_MASK_SFT, rate_reg << I2S_MODE_SFT);
		i2s_con = I2S_IN_PAD_IO_MUX << I2SIN_PAD_SEL_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wlen(क्रमmat) << I2S_WLEN_SFT;
		regmap_update_bits(afe->regmap, AFE_I2S_CON,
				   0xffffeffe, i2s_con);
		अवरोध;
	हाल MT8183_DAI_I2S_1:
		i2s_con = I2S1_SEL_O28_O29 << I2S2_SEL_O03_O04_SFT;
		i2s_con |= rate_reg << I2S2_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wlen(क्रमmat) << I2S2_WLEN_SFT;
		regmap_update_bits(afe->regmap, AFE_I2S_CON1,
				   0xffffeffe, i2s_con);
		अवरोध;
	हाल MT8183_DAI_I2S_2:
		i2s_con = 8 << I2S3_UPDATE_WORD_SFT;
		i2s_con |= rate_reg << I2S3_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wlen(क्रमmat) << I2S3_WLEN_SFT;
		regmap_update_bits(afe->regmap, AFE_I2S_CON2,
				   0xffffeffe, i2s_con);
		अवरोध;
	हाल MT8183_DAI_I2S_3:
		i2s_con = rate_reg << I2S4_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wlen(क्रमmat) << I2S4_WLEN_SFT;
		regmap_update_bits(afe->regmap, AFE_I2S_CON3,
				   0xffffeffe, i2s_con);
		अवरोध;
	हाल MT8183_DAI_I2S_5:
		i2s_con = rate_reg << I2S5_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wlen(क्रमmat) << I2S5_WLEN_SFT;
		regmap_update_bits(afe->regmap, AFE_I2S_CON4,
				   0xffffeffe, i2s_con);
		अवरोध;
	शेष:
		dev_warn(afe->dev, "%s(), id %d not support\n",
			 __func__, i2s_id);
		वापस -EINVAL;
	पूर्ण

	/* set share i2s */
	अगर (i2s_priv && i2s_priv->share_i2s_id >= 0)
		ret = mtk_dai_i2s_config(afe, params, i2s_priv->share_i2s_id);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_dai_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	वापस mtk_dai_i2s_config(afe, params, dai->id);
पूर्ण

अटल पूर्णांक mtk_dai_i2s_set_sysclk(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dai->dev);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_i2s_priv *i2s_priv = afe_priv->dai_priv[dai->id];
	पूर्णांक apll;
	पूर्णांक apll_rate;

	अगर (!i2s_priv) अणु
		dev_warn(afe->dev, "%s(), i2s_priv == NULL", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (dir != SND_SOC_CLOCK_OUT) अणु
		dev_warn(afe->dev, "%s(), dir != SND_SOC_CLOCK_OUT", __func__);
		वापस -EINVAL;
	पूर्ण

	dev_info(afe->dev, "%s(), freq %d\n", __func__, freq);

	apll = mt8183_get_apll_by_rate(afe, freq);
	apll_rate = mt8183_get_apll_rate(afe, apll);

	अगर (freq > apll_rate) अणु
		dev_warn(afe->dev, "%s(), freq > apll rate", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (apll_rate % freq != 0) अणु
		dev_warn(afe->dev, "%s(), APLL cannot generate freq Hz",
			 __func__);
		वापस -EINVAL;
	पूर्ण

	i2s_priv->mclk_rate = freq;
	i2s_priv->mclk_apll = apll;

	अगर (i2s_priv->share_i2s_id > 0) अणु
		काष्ठा mtk_afe_i2s_priv *share_i2s_priv;

		share_i2s_priv = afe_priv->dai_priv[i2s_priv->share_i2s_id];
		अगर (!share_i2s_priv) अणु
			dev_warn(afe->dev, "%s(), share_i2s_priv == NULL",
				 __func__);
			वापस -EINVAL;
		पूर्ण

		share_i2s_priv->mclk_rate = i2s_priv->mclk_rate;
		share_i2s_priv->mclk_apll = i2s_priv->mclk_apll;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_dai_i2s_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_i2s_priv *i2s_priv;

	चयन (dai->id) अणु
	हाल MT8183_DAI_I2S_0:
	हाल MT8183_DAI_I2S_1:
	हाल MT8183_DAI_I2S_2:
	हाल MT8183_DAI_I2S_3:
	हाल MT8183_DAI_I2S_5:
		अवरोध;
	शेष:
		dev_warn(afe->dev, "%s(), id %d not support\n",
			 __func__, dai->id);
		वापस -EINVAL;
	पूर्ण
	i2s_priv = afe_priv->dai_priv[dai->id];

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		i2s_priv->use_eiaj = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		i2s_priv->use_eiaj = 0;
		अवरोध;
	शेष:
		dev_warn(afe->dev, "%s(), DAI format %d not support\n",
			 __func__, fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mtk_dai_i2s_ops = अणु
	.hw_params = mtk_dai_i2s_hw_params,
	.set_sysclk = mtk_dai_i2s_set_sysclk,
	.set_fmt = mtk_dai_i2s_set_fmt,
पूर्ण;

/* dai driver */
#घोषणा MTK_I2S_RATES (SNDRV_PCM_RATE_8000_48000 |\
		       SNDRV_PCM_RATE_88200 |\
		       SNDRV_PCM_RATE_96000 |\
		       SNDRV_PCM_RATE_176400 |\
		       SNDRV_PCM_RATE_192000)

#घोषणा MTK_I2S_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mtk_dai_i2s_driver[] = अणु
	अणु
		.name = "I2S0",
		.id = MT8183_DAI_I2S_0,
		.capture = अणु
			.stream_name = "I2S0",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_I2S_RATES,
			.क्रमmats = MTK_I2S_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_i2s_ops,
	पूर्ण,
	अणु
		.name = "I2S1",
		.id = MT8183_DAI_I2S_1,
		.playback = अणु
			.stream_name = "I2S1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_I2S_RATES,
			.क्रमmats = MTK_I2S_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_i2s_ops,
	पूर्ण,
	अणु
		.name = "I2S2",
		.id = MT8183_DAI_I2S_2,
		.capture = अणु
			.stream_name = "I2S2",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_I2S_RATES,
			.क्रमmats = MTK_I2S_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_i2s_ops,
	पूर्ण,
	अणु
		.name = "I2S3",
		.id = MT8183_DAI_I2S_3,
		.playback = अणु
			.stream_name = "I2S3",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_I2S_RATES,
			.क्रमmats = MTK_I2S_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_i2s_ops,
	पूर्ण,
	अणु
		.name = "I2S5",
		.id = MT8183_DAI_I2S_5,
		.playback = अणु
			.stream_name = "I2S5",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_I2S_RATES,
			.क्रमmats = MTK_I2S_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_i2s_ops,
	पूर्ण,
पूर्ण;

/* this क्रमागत is merely क्रम mtk_afe_i2s_priv declare */
क्रमागत अणु
	DAI_I2S0 = 0,
	DAI_I2S1,
	DAI_I2S2,
	DAI_I2S3,
	DAI_I2S5,
	DAI_I2S_NUM,
पूर्ण;

अटल स्थिर काष्ठा mtk_afe_i2s_priv mt8183_i2s_priv[DAI_I2S_NUM] = अणु
	[DAI_I2S0] = अणु
		.id = MT8183_DAI_I2S_0,
		.mclk_id = MT8183_I2S0_MCK,
		.share_property_name = "i2s0-share",
		.share_i2s_id = -1,
	पूर्ण,
	[DAI_I2S1] = अणु
		.id = MT8183_DAI_I2S_1,
		.mclk_id = MT8183_I2S1_MCK,
		.share_property_name = "i2s1-share",
		.share_i2s_id = -1,
	पूर्ण,
	[DAI_I2S2] = अणु
		.id = MT8183_DAI_I2S_2,
		.mclk_id = MT8183_I2S2_MCK,
		.share_property_name = "i2s2-share",
		.share_i2s_id = -1,
	पूर्ण,
	[DAI_I2S3] = अणु
		.id = MT8183_DAI_I2S_3,
		.mclk_id = MT8183_I2S3_MCK,
		.share_property_name = "i2s3-share",
		.share_i2s_id = -1,
	पूर्ण,
	[DAI_I2S5] = अणु
		.id = MT8183_DAI_I2S_5,
		.mclk_id = MT8183_I2S5_MCK,
		.share_property_name = "i2s5-share",
		.share_i2s_id = -1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mt8183_dai_i2s_get_share(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	स्थिर काष्ठा device_node *of_node = afe->dev->of_node;
	स्थिर अक्षर *of_str;
	स्थिर अक्षर *property_name;
	काष्ठा mtk_afe_i2s_priv *i2s_priv;
	पूर्णांक i;

	क्रम (i = 0; i < DAI_I2S_NUM; i++) अणु
		i2s_priv = afe_priv->dai_priv[mt8183_i2s_priv[i].id];
		property_name = mt8183_i2s_priv[i].share_property_name;
		अगर (of_property_पढ़ो_string(of_node, property_name, &of_str))
			जारी;
		i2s_priv->share_i2s_id = get_i2s_id_by_name(afe, of_str);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt8183_dai_i2s_set_priv(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_i2s_priv *i2s_priv;
	पूर्णांक i;

	क्रम (i = 0; i < DAI_I2S_NUM; i++) अणु
		i2s_priv = devm_kzalloc(afe->dev,
					माप(काष्ठा mtk_afe_i2s_priv),
					GFP_KERNEL);
		अगर (!i2s_priv)
			वापस -ENOMEM;

		स_नकल(i2s_priv, &mt8183_i2s_priv[i],
		       माप(काष्ठा mtk_afe_i2s_priv));

		afe_priv->dai_priv[mt8183_i2s_priv[i].id] = i2s_priv;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt8183_dai_i2s_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;
	पूर्णांक ret;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mtk_dai_i2s_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mtk_dai_i2s_driver);

	dai->controls = mtk_dai_i2s_controls;
	dai->num_controls = ARRAY_SIZE(mtk_dai_i2s_controls);
	dai->dapm_widमाला_लो = mtk_dai_i2s_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mtk_dai_i2s_widमाला_लो);
	dai->dapm_routes = mtk_dai_i2s_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mtk_dai_i2s_routes);

	/* set all dai i2s निजी data */
	ret = mt8183_dai_i2s_set_priv(afe);
	अगर (ret)
		वापस ret;

	/* parse share i2s */
	ret = mt8183_dai_i2s_get_share(afe);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
