<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI ADDA Control
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश "mt6797-afe-common.h"
#समावेश "mt6797-interconnection.h"
#समावेश "mt6797-reg.h"

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

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		/* should delayed 1/fs(smallest is 8k) = 125us beक्रमe afe off */
		usleep_range(125, 135);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत अणु
	SUPPLY_SEQ_AUD_TOP_PDN,
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
			      SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("aud_dac_clk", SUPPLY_SEQ_AUD_TOP_PDN,
			      AUDIO_TOP_CON0, PDN_DAC_SFT, 1,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("aud_dac_predis_clk", SUPPLY_SEQ_AUD_TOP_PDN,
			      AUDIO_TOP_CON0, PDN_DAC_PREDIS_SFT, 1,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("aud_adc_clk", SUPPLY_SEQ_AUD_TOP_PDN,
			      AUDIO_TOP_CON0, PDN_ADC_SFT, 1,
			      शून्य, 0),

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

		/* set input sampling rate */
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

		अगर (rate < 96000) अणु
			/* SA suggest apply -0.3db to audio/speech path */
			dl_src2_con1 = 0xf74f0000;
		पूर्ण अन्यथा अणु
			/* SA suggest apply -0.3db to audio/speech path
			 * with DL gain set to half,
			 * 0xFFFF = 0dB -> 0x8000 = 0dB when 96k, 192k
			 */
			dl_src2_con1 = 0x7ba70000;
		पूर्ण

		/* turn on करोwn-link gain */
		dl_src2_con0 = dl_src2_con0 | (0x01 << 1);

		regmap_ग_लिखो(afe->regmap, AFE_ADDA_DL_SRC2_CON0, dl_src2_con0);
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_DL_SRC2_CON1, dl_src2_con1);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक voice_mode = 0;
		अचिन्हित पूर्णांक ul_src_con0 = 0;	/* शेष value */

		/* Using Internal ADC */
		regmap_update_bits(afe->regmap,
				   AFE_ADDA_TOP_CON0,
				   0x1 << 0,
				   0x0 << 0);

		voice_mode = adda_ul_rate_transक्रमm(afe, rate);

		ul_src_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* up8x txअगर sat on */
		regmap_ग_लिखो(afe->regmap, AFE_ADDA_NEWIF_CFG0, 0x03F87201);

		अगर (rate >= 96000) अणु	/* hires */
			/* use hires क्रमmat [1 0 23] */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_NEWIF_CFG0,
					   0x1 << 5,
					   0x1 << 5);

			regmap_update_bits(afe->regmap,
					   AFE_ADDA_NEWIF_CFG2,
					   0xf << 28,
					   voice_mode << 28);
		पूर्ण अन्यथा अणु	/* normal 8~48k */
			/* use fixed 260k anc path */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_NEWIF_CFG2,
					   0xf << 28,
					   8 << 28);

			/* ul_use_cic_out */
			ul_src_con0 |= 0x1 << 20;
		पूर्ण

		regmap_update_bits(afe->regmap,
				   AFE_ADDA_NEWIF_CFG2,
				   0xf << 28,
				   8 << 28);

		regmap_update_bits(afe->regmap,
				   AFE_ADDA_UL_SRC_CON0,
				   0xfffffffe,
				   ul_src_con0);
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
				SNDRV_PCM_RATE_48000 |\
				SNDRV_PCM_RATE_96000 |\
				SNDRV_PCM_RATE_192000)

#घोषणा MTK_ADDA_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			  SNDRV_PCM_FMTBIT_S24_LE |\
			  SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mtk_dai_adda_driver[] = अणु
	अणु
		.name = "ADDA",
		.id = MT6797_DAI_ADDA,
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

पूर्णांक mt6797_dai_adda_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mtk_dai_adda_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mtk_dai_adda_driver);

	dai->dapm_widमाला_लो = mtk_dai_adda_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mtk_dai_adda_widमाला_लो);
	dai->dapm_routes = mtk_dai_adda_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mtk_dai_adda_routes);
	वापस 0;
पूर्ण
