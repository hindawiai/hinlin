<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI TDM Control
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश "mt8183-afe-clk.h"
#समावेश "mt8183-afe-common.h"
#समावेश "mt8183-interconnection.h"
#समावेश "mt8183-reg.h"

काष्ठा mtk_afe_tdm_priv अणु
	पूर्णांक bck_id;
	पूर्णांक bck_rate;
	पूर्णांक tdm_out_mode;
	पूर्णांक bck_invert;
	पूर्णांक lck_invert;
	पूर्णांक mclk_id;
	पूर्णांक mclk_multiple; /* according to sample rate */
	पूर्णांक mclk_rate;
	पूर्णांक mclk_apll;
पूर्ण;

क्रमागत अणु
	TDM_OUT_I2S = 0,
	TDM_OUT_TDM = 1,
पूर्ण;

क्रमागत अणु
	TDM_BCK_NON_INV = 0,
	TDM_BCK_INV = 1,
पूर्ण;

क्रमागत अणु
	TDM_LCK_NON_INV = 0,
	TDM_LCK_INV = 1,
पूर्ण;

क्रमागत अणु
	TDM_WLEN_16_BIT = 1,
	TDM_WLEN_32_BIT = 2,
पूर्ण;

क्रमागत अणु
	TDM_CHANNEL_BCK_16 = 0,
	TDM_CHANNEL_BCK_24 = 1,
	TDM_CHANNEL_BCK_32 = 2,
पूर्ण;

क्रमागत अणु
	TDM_CHANNEL_NUM_2 = 0,
	TDM_CHANNEL_NUM_4 = 1,
	TDM_CHANNEL_NUM_8 = 2,
पूर्ण;

क्रमागत  अणु
	TDM_CH_START_O30_O31 = 0,
	TDM_CH_START_O32_O33,
	TDM_CH_START_O34_O35,
	TDM_CH_START_O36_O37,
	TDM_CH_ZERO,
पूर्ण;

क्रमागत अणु
	HDMI_BIT_WIDTH_16_BIT = 0,
	HDMI_BIT_WIDTH_32_BIT = 1,
पूर्ण;

अटल अचिन्हित पूर्णांक get_hdmi_wlen(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_pcm_क्रमmat_physical_width(क्रमmat) <= 16 ?
	       HDMI_BIT_WIDTH_16_BIT : HDMI_BIT_WIDTH_32_BIT;
पूर्ण

अटल अचिन्हित पूर्णांक get_tdm_wlen(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_pcm_क्रमmat_physical_width(क्रमmat) <= 16 ?
	       TDM_WLEN_16_BIT : TDM_WLEN_32_BIT;
पूर्ण

अटल अचिन्हित पूर्णांक get_tdm_channel_bck(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_pcm_क्रमmat_physical_width(क्रमmat) <= 16 ?
	       TDM_CHANNEL_BCK_16 : TDM_CHANNEL_BCK_32;
पूर्ण

अटल अचिन्हित पूर्णांक get_tdm_lrck_width(snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_pcm_क्रमmat_physical_width(क्रमmat) - 1;
पूर्ण

अटल अचिन्हित पूर्णांक get_tdm_ch(अचिन्हित पूर्णांक ch)
अणु
	चयन (ch) अणु
	हाल 1:
	हाल 2:
		वापस TDM_CHANNEL_NUM_2;
	हाल 3:
	हाल 4:
		वापस TDM_CHANNEL_NUM_4;
	हाल 5:
	हाल 6:
	हाल 7:
	हाल 8:
	शेष:
		वापस TDM_CHANNEL_NUM_8;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक get_tdm_ch_fixup(अचिन्हित पूर्णांक channels)
अणु
	अगर (channels > 4)
		वापस 8;
	अन्यथा अगर (channels > 2)
		वापस 4;
	अन्यथा
		वापस 2;
पूर्ण

अटल अचिन्हित पूर्णांक get_tdm_ch_per_sdata(अचिन्हित पूर्णांक mode,
					 अचिन्हित पूर्णांक channels)
अणु
	अगर (mode == TDM_OUT_TDM)
		वापस get_tdm_ch_fixup(channels);
	अन्यथा
		वापस 2;
पूर्ण

/* पूर्णांकerconnection */
क्रमागत अणु
	HDMI_CONN_CH0 = 0,
	HDMI_CONN_CH1,
	HDMI_CONN_CH2,
	HDMI_CONN_CH3,
	HDMI_CONN_CH4,
	HDMI_CONN_CH5,
	HDMI_CONN_CH6,
	HDMI_CONN_CH7,
पूर्ण;

अटल स्थिर अक्षर *स्थिर hdmi_conn_mux_map[] = अणु
	"CH0", "CH1", "CH2", "CH3",
	"CH4", "CH5", "CH6", "CH7",
पूर्ण;

अटल पूर्णांक hdmi_conn_mux_map_value[] = अणु
	HDMI_CONN_CH0,
	HDMI_CONN_CH1,
	HDMI_CONN_CH2,
	HDMI_CONN_CH3,
	HDMI_CONN_CH4,
	HDMI_CONN_CH5,
	HDMI_CONN_CH6,
	HDMI_CONN_CH7,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch0_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_0_SFT,
				  HDMI_O_0_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch0_mux_control =
	SOC_DAPM_ENUM("HDMI_CH0_MUX", hdmi_ch0_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch1_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_1_SFT,
				  HDMI_O_1_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch1_mux_control =
	SOC_DAPM_ENUM("HDMI_CH1_MUX", hdmi_ch1_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch2_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_2_SFT,
				  HDMI_O_2_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch2_mux_control =
	SOC_DAPM_ENUM("HDMI_CH2_MUX", hdmi_ch2_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch3_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_3_SFT,
				  HDMI_O_3_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch3_mux_control =
	SOC_DAPM_ENUM("HDMI_CH3_MUX", hdmi_ch3_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch4_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_4_SFT,
				  HDMI_O_4_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch4_mux_control =
	SOC_DAPM_ENUM("HDMI_CH4_MUX", hdmi_ch4_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch5_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_5_SFT,
				  HDMI_O_5_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch5_mux_control =
	SOC_DAPM_ENUM("HDMI_CH5_MUX", hdmi_ch5_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch6_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_6_SFT,
				  HDMI_O_6_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch6_mux_control =
	SOC_DAPM_ENUM("HDMI_CH6_MUX", hdmi_ch6_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hdmi_ch7_mux_map_क्रमागत,
				  AFE_HDMI_CONN0,
				  HDMI_O_7_SFT,
				  HDMI_O_7_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_ch7_mux_control =
	SOC_DAPM_ENUM("HDMI_CH7_MUX", hdmi_ch7_mux_map_क्रमागत);

क्रमागत अणु
	SUPPLY_SEQ_APLL,
	SUPPLY_SEQ_TDM_MCK_EN,
	SUPPLY_SEQ_TDM_BCK_EN,
पूर्ण;

अटल पूर्णांक mtk_tdm_bck_en_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol,
				पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_tdm_priv *tdm_priv = afe_priv->dai_priv[MT8183_DAI_TDM];

	dev_info(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8183_mck_enable(afe, tdm_priv->bck_id, tdm_priv->bck_rate);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		mt8183_mck_disable(afe, tdm_priv->bck_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_tdm_mck_en_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol,
				पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_tdm_priv *tdm_priv = afe_priv->dai_priv[MT8183_DAI_TDM];

	dev_info(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8183_mck_enable(afe, tdm_priv->mclk_id, tdm_priv->mclk_rate);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		tdm_priv->mclk_rate = 0;
		mt8183_mck_disable(afe, tdm_priv->mclk_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget mtk_dai_tdm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("HDMI_CH0_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch0_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH1_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch1_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH2_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch2_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH3_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch3_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH4_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch4_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH5_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch5_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH6_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch6_mux_control),
	SND_SOC_DAPM_MUX("HDMI_CH7_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch7_mux_control),

	SND_SOC_DAPM_CLOCK_SUPPLY("aud_tdm_clk"),

	SND_SOC_DAPM_SUPPLY_S("TDM_BCK", SUPPLY_SEQ_TDM_BCK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_tdm_bck_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("TDM_MCK", SUPPLY_SEQ_TDM_MCK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_tdm_mck_en_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल पूर्णांक mtk_afe_tdm_apll_connect(काष्ठा snd_soc_dapm_widget *source,
				    काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_dapm_widget *w = sink;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_tdm_priv *tdm_priv = afe_priv->dai_priv[MT8183_DAI_TDM];
	पूर्णांक cur_apll;

	/* which apll */
	cur_apll = mt8183_get_apll_by_name(afe, source->name);

	वापस (tdm_priv->mclk_apll == cur_apll) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route mtk_dai_tdm_routes[] = अणु
	अणु"HDMI_CH0_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH0_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH1_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH1_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH2_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH2_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH3_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH3_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH4_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH4_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH5_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH5_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH6_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH6_MUX", "CH7", "HDMI"पूर्ण,

	अणु"HDMI_CH7_MUX", "CH0", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH1", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH2", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH3", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH4", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH5", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH6", "HDMI"पूर्ण,
	अणु"HDMI_CH7_MUX", "CH7", "HDMI"पूर्ण,

	अणु"TDM", शून्य, "HDMI_CH0_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH1_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH2_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH3_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH4_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH5_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH6_MUX"पूर्ण,
	अणु"TDM", शून्य, "HDMI_CH7_MUX"पूर्ण,

	अणु"TDM", शून्य, "aud_tdm_clk"पूर्ण,
	अणु"TDM", शून्य, "TDM_BCK"पूर्ण,
	अणु"TDM_BCK", शून्य, "TDM_MCK"पूर्ण,
	अणु"TDM_MCK", शून्य, APLL1_W_NAME, mtk_afe_tdm_apll_connectपूर्ण,
	अणु"TDM_MCK", शून्य, APLL2_W_NAME, mtk_afe_tdm_apll_connectपूर्ण,
पूर्ण;

/* dai ops */
अटल पूर्णांक mtk_dai_tdm_cal_mclk(काष्ठा mtk_base_afe *afe,
				काष्ठा mtk_afe_tdm_priv *tdm_priv,
				पूर्णांक freq)
अणु
	पूर्णांक apll;
	पूर्णांक apll_rate;

	apll = mt8183_get_apll_by_rate(afe, freq);
	apll_rate = mt8183_get_apll_rate(afe, apll);

	अगर (!freq || freq > apll_rate) अणु
		dev_warn(afe->dev,
			 "%s(), freq(%d Hz) invalid\n", __func__, freq);
		वापस -EINVAL;
	पूर्ण

	अगर (apll_rate % freq != 0) अणु
		dev_warn(afe->dev,
			 "%s(), APLL cannot generate %d Hz", __func__, freq);
		वापस -EINVAL;
	पूर्ण

	tdm_priv->mclk_rate = freq;
	tdm_priv->mclk_apll = apll;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_dai_tdm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक tdm_id = dai->id;
	काष्ठा mtk_afe_tdm_priv *tdm_priv = afe_priv->dai_priv[tdm_id];
	अचिन्हित पूर्णांक tdm_out_mode = tdm_priv->tdm_out_mode;
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक out_channels_per_sdata =
		get_tdm_ch_per_sdata(tdm_out_mode, channels);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक tdm_con = 0;

	/* calculate mclk_rate, अगर not set explicitly */
	अगर (!tdm_priv->mclk_rate) अणु
		tdm_priv->mclk_rate = rate * tdm_priv->mclk_multiple;
		mtk_dai_tdm_cal_mclk(afe,
				     tdm_priv,
				     tdm_priv->mclk_rate);
	पूर्ण

	/* calculate bck */
	tdm_priv->bck_rate = rate *
			     out_channels_per_sdata *
			     snd_pcm_क्रमmat_physical_width(क्रमmat);

	अगर (tdm_priv->bck_rate > tdm_priv->mclk_rate)
		dev_warn(afe->dev, "%s(), bck_rate > mclk_rate rate", __func__);

	अगर (tdm_priv->mclk_rate % tdm_priv->bck_rate != 0)
		dev_warn(afe->dev, "%s(), bck cannot generate", __func__);

	dev_info(afe->dev, "%s(), id %d, rate %d, channels %d, format %d, mclk_rate %d, bck_rate %d\n",
		 __func__,
		 tdm_id, rate, channels, क्रमmat,
		 tdm_priv->mclk_rate, tdm_priv->bck_rate);
	dev_info(afe->dev, "%s(), out_channels_per_sdata = %d\n",
		 __func__, out_channels_per_sdata);

	/* set tdm */
	अगर (tdm_priv->bck_invert)
		regmap_update_bits(afe->regmap, AUDIO_TOP_CON3,
				   BCK_INVERSE_MASK_SFT,
				   0x1 << BCK_INVERSE_SFT);

	अगर (tdm_priv->lck_invert)
		tdm_con |= 1 << LRCK_INVERSE_SFT;

	अगर (tdm_priv->tdm_out_mode == TDM_OUT_I2S) अणु
		tdm_con |= 1 << DELAY_DATA_SFT;
		tdm_con |= get_tdm_lrck_width(क्रमmat) << LRCK_TDM_WIDTH_SFT;
	पूर्ण अन्यथा अगर (tdm_priv->tdm_out_mode == TDM_OUT_TDM) अणु
		tdm_con |= 0 << DELAY_DATA_SFT;
		tdm_con |= 0 << LRCK_TDM_WIDTH_SFT;
	पूर्ण

	tdm_con |= 1 << LEFT_ALIGN_SFT;
	tdm_con |= get_tdm_wlen(क्रमmat) << WLEN_SFT;
	tdm_con |= get_tdm_ch(out_channels_per_sdata) << CHANNEL_NUM_SFT;
	tdm_con |= get_tdm_channel_bck(क्रमmat) << CHANNEL_BCK_CYCLES_SFT;
	regmap_ग_लिखो(afe->regmap, AFE_TDM_CON1, tdm_con);

	अगर (out_channels_per_sdata == 2) अणु
		चयन (channels) अणु
		हाल 1:
		हाल 2:
			tdm_con = TDM_CH_START_O30_O31 << ST_CH_PAIR_SOUT0_SFT;
			tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT1_SFT;
			tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT2_SFT;
			tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT3_SFT;
			अवरोध;
		हाल 3:
		हाल 4:
			tdm_con = TDM_CH_START_O30_O31 << ST_CH_PAIR_SOUT0_SFT;
			tdm_con |= TDM_CH_START_O32_O33 << ST_CH_PAIR_SOUT1_SFT;
			tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT2_SFT;
			tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT3_SFT;
			अवरोध;
		हाल 5:
		हाल 6:
			tdm_con = TDM_CH_START_O30_O31 << ST_CH_PAIR_SOUT0_SFT;
			tdm_con |= TDM_CH_START_O32_O33 << ST_CH_PAIR_SOUT1_SFT;
			tdm_con |= TDM_CH_START_O34_O35 << ST_CH_PAIR_SOUT2_SFT;
			tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT3_SFT;
			अवरोध;
		हाल 7:
		हाल 8:
			tdm_con = TDM_CH_START_O30_O31 << ST_CH_PAIR_SOUT0_SFT;
			tdm_con |= TDM_CH_START_O32_O33 << ST_CH_PAIR_SOUT1_SFT;
			tdm_con |= TDM_CH_START_O34_O35 << ST_CH_PAIR_SOUT2_SFT;
			tdm_con |= TDM_CH_START_O36_O37 << ST_CH_PAIR_SOUT3_SFT;
			अवरोध;
		शेष:
			tdm_con = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		tdm_con = TDM_CH_START_O30_O31 << ST_CH_PAIR_SOUT0_SFT;
		tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT1_SFT;
		tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT2_SFT;
		tdm_con |= TDM_CH_ZERO << ST_CH_PAIR_SOUT3_SFT;
	पूर्ण

	regmap_ग_लिखो(afe->regmap, AFE_TDM_CON2, tdm_con);

	regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
			   AFE_HDMI_OUT_CH_NUM_MASK_SFT,
			   channels << AFE_HDMI_OUT_CH_NUM_SFT);

	regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
			   AFE_HDMI_OUT_BIT_WIDTH_MASK_SFT,
			   get_hdmi_wlen(क्रमmat) << AFE_HDMI_OUT_BIT_WIDTH_SFT);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_dai_tdm_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* enable Out control */
		regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
				   AFE_HDMI_OUT_ON_MASK_SFT,
				   0x1 << AFE_HDMI_OUT_ON_SFT);
		/* enable tdm */
		regmap_update_bits(afe->regmap, AFE_TDM_CON1,
				   TDM_EN_MASK_SFT, 0x1 << TDM_EN_SFT);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		/* disable tdm */
		regmap_update_bits(afe->regmap, AFE_TDM_CON1,
				   TDM_EN_MASK_SFT, 0);
		/* disable Out control */
		regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
				   AFE_HDMI_OUT_ON_MASK_SFT,
				   0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_dai_tdm_set_sysclk(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dai->dev);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_tdm_priv *tdm_priv = afe_priv->dai_priv[dai->id];

	अगर (!tdm_priv) अणु
		dev_warn(afe->dev, "%s(), tdm_priv == NULL", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (dir != SND_SOC_CLOCK_OUT) अणु
		dev_warn(afe->dev, "%s(), dir != SND_SOC_CLOCK_OUT", __func__);
		वापस -EINVAL;
	पूर्ण

	dev_info(afe->dev, "%s(), freq %d\n", __func__, freq);

	वापस mtk_dai_tdm_cal_mclk(afe, tdm_priv, freq);
पूर्ण

अटल पूर्णांक mtk_dai_tdm_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dai->dev);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_tdm_priv *tdm_priv = afe_priv->dai_priv[dai->id];

	अगर (!tdm_priv) अणु
		dev_warn(afe->dev, "%s(), tdm_priv == NULL", __func__);
		वापस -EINVAL;
	पूर्ण

	/* DAI mode*/
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		tdm_priv->tdm_out_mode = TDM_OUT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		tdm_priv->tdm_out_mode = TDM_OUT_TDM;
		अवरोध;
	शेष:
		tdm_priv->tdm_out_mode = TDM_OUT_I2S;
	पूर्ण

	/* DAI घड़ी inversion*/
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		tdm_priv->bck_invert = TDM_BCK_NON_INV;
		tdm_priv->lck_invert = TDM_LCK_NON_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		tdm_priv->bck_invert = TDM_BCK_NON_INV;
		tdm_priv->lck_invert = TDM_LCK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		tdm_priv->bck_invert = TDM_BCK_INV;
		tdm_priv->lck_invert = TDM_LCK_NON_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
	शेष:
		tdm_priv->bck_invert = TDM_BCK_INV;
		tdm_priv->lck_invert = TDM_LCK_INV;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mtk_dai_tdm_ops = अणु
	.hw_params = mtk_dai_tdm_hw_params,
	.trigger = mtk_dai_tdm_trigger,
	.set_sysclk = mtk_dai_tdm_set_sysclk,
	.set_fmt = mtk_dai_tdm_set_fmt,
पूर्ण;

/* dai driver */
#घोषणा MTK_TDM_RATES (SNDRV_PCM_RATE_8000_48000 |\
		       SNDRV_PCM_RATE_88200 |\
		       SNDRV_PCM_RATE_96000 |\
		       SNDRV_PCM_RATE_176400 |\
		       SNDRV_PCM_RATE_192000)

#घोषणा MTK_TDM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mtk_dai_tdm_driver[] = अणु
	अणु
		.name = "TDM",
		.id = MT8183_DAI_TDM,
		.playback = अणु
			.stream_name = "TDM",
			.channels_min = 2,
			.channels_max = 8,
			.rates = MTK_TDM_RATES,
			.क्रमmats = MTK_TDM_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_tdm_ops,
	पूर्ण,
पूर्ण;

पूर्णांक mt8183_dai_tdm_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा mtk_afe_tdm_priv *tdm_priv;
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mtk_dai_tdm_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mtk_dai_tdm_driver);

	dai->dapm_widमाला_लो = mtk_dai_tdm_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mtk_dai_tdm_widमाला_लो);
	dai->dapm_routes = mtk_dai_tdm_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mtk_dai_tdm_routes);

	tdm_priv = devm_kzalloc(afe->dev, माप(काष्ठा mtk_afe_tdm_priv),
				GFP_KERNEL);
	अगर (!tdm_priv)
		वापस -ENOMEM;

	tdm_priv->mclk_multiple = 128;
	tdm_priv->bck_id = MT8183_I2S4_BCK;
	tdm_priv->mclk_id = MT8183_I2S4_MCK;

	afe_priv->dai_priv[MT8183_DAI_TDM] = tdm_priv;
	वापस 0;
पूर्ण
