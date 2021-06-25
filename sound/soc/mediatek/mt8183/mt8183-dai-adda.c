<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI ADDA Control
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश "mt8183-afe-common.h"
#समावेश "mt8183-interconnection.h"
#समावेश "mt8183-reg.h"

क्रमागत अणु
	AUDIO_SDM_LEVEL_MUTE = 0,
	AUDIO_SDM_LEVEL_NORMAL = 0x1d,
	/* अगर you change level normal */
	/* you need to change क्रमmula of hp impedance and dc trim too */
पूर्ण;

क्रमागत अणु
	DELAY_DATA_MISO1 = 0,
	DELAY_DATA_MISO2,
पूर्ण;

क्रमागत अणु
	MTK_AFE_ADDA_DL_RATE_8K = 0,
	MTK_AFE_ADDA_DL_RATE_11K = 1,
	MTK_AFE_ADDA_DL_RATE_12K = 2,
	MTK_AFE_ADDA_DL_RATE_16K = 3,
	MTK_AFE_ADDA_DL_RATE_22K = 4,
	MTK_AFE_ADDA_DL_RATE_24K = 5,
	MTK_AFE_ADDA_DL_RATE_32K = 6,
	MTK_AFE_ADDA_DL_RATE_44K = 7,
	MTK_AFE_ADDA_DL_RATE_48K = 8,
	MTK_AFE_ADDA_DL_RATE_96K = 9,
	MTK_AFE_ADDA_DL_RATE_192K = 10,
पूर्ण;

क्रमागत अणु
	MTK_AFE_ADDA_UL_RATE_8K = 0,
	MTK_AFE_ADDA_UL_RATE_16K = 1,
	MTK_AFE_ADDA_UL_RATE_32K = 2,
	MTK_AFE_ADDA_UL_RATE_48K = 3,
	MTK_AFE_ADDA_UL_RATE_96K = 4,
	MTK_AFE_ADDA_UL_RATE_192K = 5,
	MTK_AFE_ADDA_UL_RATE_48K_HD = 6,
पूर्ण;

अटल अचिन्हित पूर्णांक adda_dl_rate_transक्रमm(काष्ठा mtk_base_afe *afe,
					   अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_ADDA_DL_RATE_8K;
	हाल 11025:
		वापस MTK_AFE_ADDA_DL_RATE_11K;
	हाल 12000:
		वापस MTK_AFE_ADDA_DL_RATE_12K;
	हाल 16000:
		वापस MTK_AFE_ADDA_DL_RATE_16K;
	हाल 22050:
		वापस MTK_AFE_ADDA_DL_RATE_22K;
	हाल 24000:
		वापस MTK_AFE_ADDA_DL_RATE_24K;
	हाल 32000:
		वापस MTK_AFE_ADDA_DL_RATE_32K;
	हाल 44100:
		वापस MTK_AFE_ADDA_DL_RATE_44K;
	हाल 48000:
		वापस MTK_AFE_ADDA_DL_RATE_48K;
	हाल 96000:
		वापस MTK_AFE_ADDA_DL_RATE_96K;
	हाल 192000:
		वापस MTK_AFE_ADDA_DL_RATE_192K;
	शेष:
		dev_warn(afe->dev, "%s(), rate %d invalid, use 48kHz!!!\n",
			 __func__, rate);
		वापस MTK_AFE_ADDA_DL_RATE_48K;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक adda_ul_rate_transक्रमm(काष्ठा mtk_base_afe *afe,
					   अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_ADDA_UL_RATE_8K;
	हाल 16000:
		वापस MTK_AFE_ADDA_UL_RATE_16K;
	हाल 32000:
		वापस MTK_AFE_ADDA_UL_RATE_32K;
	हाल 48000:
		वापस MTK_AFE_ADDA_UL_RATE_48K;
	हाल 96000:
		वापस MTK_AFE_ADDA_UL_RATE_96K;
	हाल 192000:
		वापस MTK_AFE_ADDA_UL_RATE_192K;
	शेष:
		dev_warn(afe->dev, "%s(), rate %d invalid, use 48kHz!!!\n",
			 __func__, rate);
		वापस MTK_AFE_ADDA_UL_RATE_48K;
	पूर्ण
पूर्ण

/* dai component */
अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_dl_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN3, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN3, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN3, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN3,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN3,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN3,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN3,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_dl_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN4, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN4, I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN4, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN4, I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN4, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN4, I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN4,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN4,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN4,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN4,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH2", AFE_CONN4,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH2", AFE_CONN4,
				    I_PCM_2_CAP_CH2, 1, 0),
पूर्ण;

अटल पूर्णांक mtk_adda_ul_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* update setting to dmic */
		अगर (afe_priv->mtkaअगर_dmic) अणु
			/* mtkaअगर_rxअगर_data_mode = 1, dmic */
			regmap_update_bits(afe->regmap, AFE_ADDA_MTKAIF_RX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			regmap_update_bits(afe->regmap, AFE_ADDA_MTKAIF_RX_CFG0,
					   0x0, 0xf << 20);
			regmap_update_bits(afe->regmap, AFE_ADDA_UL_SRC_CON0,
					   0x0, 0x1 << 5);
			regmap_update_bits(afe->regmap, AFE_ADDA_UL_SRC_CON0,
					   0x0, 0x3 << 14);

			/* turn on dmic, ch1, ch2 */
			regmap_update_bits(afe->regmap, AFE_ADDA_UL_SRC_CON0,
					   0x1 << 1, 0x1 << 1);
			regmap_update_bits(afe->regmap, AFE_ADDA_UL_SRC_CON0,
					   0x3 << 21, 0x3 << 21);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* should delayed 1/fs(smallest is 8k) = 125us beक्रमe afe off */
		usleep_range(125, 135);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* mtkaअगर dmic */
अटल स्थिर अक्षर * स्थिर mt8183_adda_off_on_str[] = अणु
	"Off", "On"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत mt8183_adda_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(mt8183_adda_off_on_str),
			    mt8183_adda_off_on_str),
पूर्ण;

अटल पूर्णांक mt8183_adda_dmic_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;

	ucontrol->value.पूर्णांकeger.value[0] = afe_priv->mtkaअगर_dmic;

	वापस 0;
पूर्ण

अटल पूर्णांक mt8183_adda_dmic_set(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= e->items)
		वापस -EINVAL;

	afe_priv->mtkaअगर_dmic = ucontrol->value.पूर्णांकeger.value[0];

	dev_info(afe->dev, "%s(), kcontrol name %s, mtkaif_dmic %d\n",
		 __func__, kcontrol->id.name, afe_priv->mtkaअगर_dmic);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_controls[] = अणु
	SOC_ENUM_EXT("MTKAIF_DMIC", mt8183_adda_क्रमागत[0],
		     mt8183_adda_dmic_get, mt8183_adda_dmic_set),
पूर्ण;

क्रमागत अणु
	SUPPLY_SEQ_ADDA_AFE_ON,
	SUPPLY_SEQ_ADDA_DL_ON,
	SUPPLY_SEQ_ADDA_UL_ON,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mtk_dai_adda_widमाला_लो[] = अणु
	/* adda */
	SND_SOC_DAPM_MIXER("ADDA_DL_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dl_ch1_mix,
			   ARRAY_SIZE(mtk_adda_dl_ch1_mix)),
	SND_SOC_DAPM_MIXER("ADDA_DL_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dl_ch2_mix,
			   ARRAY_SIZE(mtk_adda_dl_ch2_mix)),

	SND_SOC_DAPM_SUPPLY_S("ADDA Enable", SUPPLY_SEQ_ADDA_AFE_ON,
			      AFE_ADDA_UL_DL_CON0, ADDA_AFE_ON_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("ADDA Playback Enable", SUPPLY_SEQ_ADDA_DL_ON,
			      AFE_ADDA_DL_SRC2_CON0,
			      DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("ADDA Capture Enable", SUPPLY_SEQ_ADDA_UL_ON,
			      AFE_ADDA_UL_SRC_CON0,
			      UL_SRC_ON_TMP_CTL_SFT, 0,
			      mtk_adda_ul_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_CLOCK_SUPPLY("aud_dac_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("aud_dac_predis_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("aud_adc_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("mtkaif_26m_clk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mtk_dai_adda_routes[] = अणु
	/* playback */
	अणु"ADDA_DL_CH1", "DL1_CH1", "DL1"पूर्ण,
	अणु"ADDA_DL_CH2", "DL1_CH1", "DL1"पूर्ण,
	अणु"ADDA_DL_CH2", "DL1_CH2", "DL1"पूर्ण,

	अणु"ADDA_DL_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"ADDA_DL_CH2", "DL2_CH1", "DL2"पूर्ण,
	अणु"ADDA_DL_CH2", "DL2_CH2", "DL2"पूर्ण,

	अणु"ADDA_DL_CH1", "DL3_CH1", "DL3"पूर्ण,
	अणु"ADDA_DL_CH2", "DL3_CH1", "DL3"पूर्ण,
	अणु"ADDA_DL_CH2", "DL3_CH2", "DL3"पूर्ण,

	अणु"ADDA Playback", शून्य, "ADDA_DL_CH1"पूर्ण,
	अणु"ADDA Playback", शून्य, "ADDA_DL_CH2"पूर्ण,

	/* adda enable */
	अणु"ADDA Playback", शून्य, "ADDA Enable"पूर्ण,
	अणु"ADDA Playback", शून्य, "ADDA Playback Enable"पूर्ण,
	अणु"ADDA Capture", शून्य, "ADDA Enable"पूर्ण,
	अणु"ADDA Capture", शून्य, "ADDA Capture Enable"पूर्ण,

	/* clk */
	अणु"ADDA Playback", शून्य, "mtkaif_26m_clk"पूर्ण,
	अणु"ADDA Playback", शून्य, "aud_dac_clk"पूर्ण,
	अणु"ADDA Playback", शून्य, "aud_dac_predis_clk"पूर्ण,

	अणु"ADDA Capture", शून्य, "mtkaif_26m_clk"पूर्ण,
	अणु"ADDA Capture", शून्य, "aud_adc_clk"पूर्ण,
पूर्ण;

अटल पूर्णांक set_mtkaअगर_rx(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक delay_data;
	पूर्णांक delay_cycle;

	चयन (afe_priv->mtkaअगर_protocol) अणु
	हाल MT8183_MTKAIF_PROTOCOL_2_CLK_P2:
		regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x38);
		regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x39);
		/* mtkaअगर_rxअगर_clkinv_adc inverse क्रम calibration */
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
			     0x80010000);

		अगर (afe_priv->mtkaअगर_phase_cycle[0] >=
		    afe_priv->mtkaअगर_phase_cycle[1]) अणु
			delay_data = DELAY_DATA_MISO1;
			delay_cycle = afe_priv->mtkaअगर_phase_cycle[0] -
				      afe_priv->mtkaअगर_phase_cycle[1];
		पूर्ण अन्यथा अणु
			delay_data = DELAY_DATA_MISO2;
			delay_cycle = afe_priv->mtkaअगर_phase_cycle[1] -
				      afe_priv->mtkaअगर_phase_cycle[0];
		पूर्ण

		regmap_update_bits(afe->regmap,
				   AFE_ADDA_MTKAIF_RX_CFG2,
				   MTKAIF_RXIF_DELAY_DATA_MASK_SFT,
				   delay_data << MTKAIF_RXIF_DELAY_DATA_SFT);

		regmap_update_bits(afe->regmap,
				   AFE_ADDA_MTKAIF_RX_CFG2,
				   MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT,
				   delay_cycle << MTKAIF_RXIF_DELAY_CYCLE_SFT);
		अवरोध;
	हाल MT8183_MTKAIF_PROTOCOL_2:
		regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x31);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
			     0x00010000);
		अवरोध;
	हाल MT8183_MTKAIF_PROTOCOL_1:
		regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x31);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_MTKAIF_CFG0, 0x0);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* dai ops */
अटल पूर्णांक mtk_dai_adda_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);

	dev_dbg(afe->dev, "%s(), id %d, stream %d, rate %d\n",
		__func__, dai->id, substream->stream, rate);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अचिन्हित पूर्णांक dl_src2_con0 = 0;
		अचिन्हित पूर्णांक dl_src2_con1 = 0;

		/* clean predistortion */
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_PREDIS_CON0, 0);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_PREDIS_CON1, 0);

		/* set sampling rate */
		dl_src2_con0 = adda_dl_rate_transक्रमm(afe, rate) << 28;

		/* set output mode */
		चयन (rate) अणु
		हाल 192000:
			dl_src2_con0 |= (0x1 << 24); /* UP_SAMPLING_RATE_X2 */
			dl_src2_con0 |= 1 << 14;
			अवरोध;
		हाल 96000:
			dl_src2_con0 |= (0x2 << 24); /* UP_SAMPLING_RATE_X4 */
			dl_src2_con0 |= 1 << 14;
			अवरोध;
		शेष:
			dl_src2_con0 |= (0x3 << 24); /* UP_SAMPLING_RATE_X8 */
			अवरोध;
		पूर्ण

		/* turn off mute function */
		dl_src2_con0 |= (0x03 << 11);

		/* set voice input data अगर input sample rate is 8k or 16k */
		अगर (rate == 8000 || rate == 16000)
			dl_src2_con0 |= 0x01 << 5;

		/* SA suggest apply -0.3db to audio/speech path */
		dl_src2_con1 = 0xf74f0000;

		/* turn on करोwn-link gain */
		dl_src2_con0 = dl_src2_con0 | (0x01 << 1);

		regmap_ग_लिखो(afe->regmap, AFE_ADDA_DL_SRC2_CON0, dl_src2_con0);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_DL_SRC2_CON1, dl_src2_con1);

		/* set sdm gain */
		regmap_update_bits(afe->regmap,
				   AFE_ADDA_DL_SDM_DCCOMP_CON,
				   ATTGAIN_CTL_MASK_SFT,
				   AUDIO_SDM_LEVEL_NORMAL << ATTGAIN_CTL_SFT);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक voice_mode = 0;
		अचिन्हित पूर्णांक ul_src_con0 = 0;	/* शेष value */

		/* set mtkaअगर protocol */
		set_mtkaअगर_rx(afe);

		/* Using Internal ADC */
		regmap_update_bits(afe->regmap,
				   AFE_ADDA_TOP_CON0,
				   0x1 << 0,
				   0x0 << 0);

		voice_mode = adda_ul_rate_transक्रमm(afe, rate);

		ul_src_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* enable iir */
		ul_src_con0 |= (1 << UL_IIR_ON_TMP_CTL_SFT) &
			       UL_IIR_ON_TMP_CTL_MASK_SFT;

		/* 35Hz @ 48k */
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_IIR_COEF_02_01, 0x00000000);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_IIR_COEF_04_03, 0x00003FB8);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_IIR_COEF_06_05, 0x3FB80000);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_IIR_COEF_08_07, 0x3FB80000);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_IIR_COEF_10_09, 0x0000C048);

		regmap_ग_लिखो(afe->regmap, AFE_ADDA_UL_SRC_CON0, ul_src_con0);

		/* mtkaअगर_rxअगर_data_mode = 0, amic */
		regmap_update_bits(afe->regmap,
				   AFE_ADDA_MTKAIF_RX_CFG0,
				   0x1 << 0,
				   0x0 << 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mtk_dai_adda_ops = अणु
	.hw_params = mtk_dai_adda_hw_params,
पूर्ण;

/* dai driver */
#घोषणा MTK_ADDA_PLAYBACK_RATES (SNDRV_PCM_RATE_8000_48000 |\
				 SNDRV_PCM_RATE_96000 |\
				 SNDRV_PCM_RATE_192000)

#घोषणा MTK_ADDA_CAPTURE_RATES (SNDRV_PCM_RATE_8000 |\
				SNDRV_PCM_RATE_16000 |\
				SNDRV_PCM_RATE_32000 |\
				SNDRV_PCM_RATE_48000)

#घोषणा MTK_ADDA_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			  SNDRV_PCM_FMTBIT_S24_LE |\
			  SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mtk_dai_adda_driver[] = अणु
	अणु
		.name = "ADDA",
		.id = MT8183_DAI_ADDA,
		.playback = अणु
			.stream_name = "ADDA Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_ADDA_PLAYBACK_RATES,
			.क्रमmats = MTK_ADDA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "ADDA Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_ADDA_CAPTURE_RATES,
			.क्रमmats = MTK_ADDA_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_adda_ops,
	पूर्ण,
पूर्ण;

पूर्णांक mt8183_dai_adda_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mtk_dai_adda_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mtk_dai_adda_driver);

	dai->controls = mtk_adda_controls;
	dai->num_controls = ARRAY_SIZE(mtk_adda_controls);
	dai->dapm_widमाला_लो = mtk_dai_adda_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mtk_dai_adda_widमाला_लो);
	dai->dapm_routes = mtk_dai_adda_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mtk_dai_adda_routes);
	वापस 0;
पूर्ण
