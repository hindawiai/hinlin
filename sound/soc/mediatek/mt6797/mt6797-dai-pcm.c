<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI I2S Control
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश "mt6797-afe-common.h"
#समावेश "mt6797-interconnection.h"
#समावेश "mt6797-reg.h"

क्रमागत AUD_TX_LCH_RPT अणु
	AUD_TX_LCH_RPT_NO_REPEAT = 0,
	AUD_TX_LCH_RPT_REPEAT = 1
पूर्ण;

क्रमागत AUD_VBT_16K_MODE अणु
	AUD_VBT_16K_MODE_DISABLE = 0,
	AUD_VBT_16K_MODE_ENABLE = 1
पूर्ण;

क्रमागत AUD_EXT_MODEM अणु
	AUD_EXT_MODEM_SELECT_INTERNAL = 0,
	AUD_EXT_MODEM_SELECT_EXTERNAL = 1
पूर्ण;

क्रमागत AUD_PCM_SYNC_TYPE अणु
	/* bck sync length = 1 */
	AUD_PCM_ONE_BCK_CYCLE_SYNC = 0,
	/* bck sync length = PCM_INTF_CON1[9:13] */
	AUD_PCM_EXTENDED_BCK_CYCLE_SYNC = 1
पूर्ण;

क्रमागत AUD_BT_MODE अणु
	AUD_BT_MODE_DUAL_MIC_ON_TX = 0,
	AUD_BT_MODE_SINGLE_MIC_ON_TX = 1
पूर्ण;

क्रमागत AUD_PCM_AFIFO_SRC अणु
	/* slave mode & बाह्यal modem uses dअगरferent crystal */
	AUD_PCM_AFIFO_ASRC = 0,
	/* slave mode & बाह्यal modem uses the same crystal */
	AUD_PCM_AFIFO_AFIFO = 1
पूर्ण;

क्रमागत AUD_PCM_CLOCK_SOURCE अणु
	AUD_PCM_CLOCK_MASTER_MODE = 0,
	AUD_PCM_CLOCK_SLAVE_MODE = 1
पूर्ण;

क्रमागत AUD_PCM_WLEN अणु
	AUD_PCM_WLEN_PCM_32_BCK_CYCLES = 0,
	AUD_PCM_WLEN_PCM_64_BCK_CYCLES = 1
पूर्ण;

क्रमागत AUD_PCM_MODE अणु
	AUD_PCM_MODE_PCM_MODE_8K = 0,
	AUD_PCM_MODE_PCM_MODE_16K = 1,
	AUD_PCM_MODE_PCM_MODE_32K = 2,
	AUD_PCM_MODE_PCM_MODE_48K = 3,
पूर्ण;

क्रमागत AUD_PCM_FMT अणु
	AUD_PCM_FMT_I2S = 0,
	AUD_PCM_FMT_EIAJ = 1,
	AUD_PCM_FMT_PCM_MODE_A = 2,
	AUD_PCM_FMT_PCM_MODE_B = 3
पूर्ण;

क्रमागत AUD_BCLK_OUT_INV अणु
	AUD_BCLK_OUT_INV_NO_INVERSE = 0,
	AUD_BCLK_OUT_INV_INVERSE = 1
पूर्ण;

क्रमागत AUD_PCM_EN अणु
	AUD_PCM_EN_DISABLE = 0,
	AUD_PCM_EN_ENABLE = 1
पूर्ण;

/* dai component */
अटल स्थिर काष्ठा snd_kcontrol_new mtk_pcm_1_playback_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN7,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN7,
				    I_DL2_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_pcm_1_playback_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN8,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN8,
				    I_DL2_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_pcm_1_playback_ch4_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN27,
				    I_DL1_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_pcm_2_playback_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN17,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN17,
				    I_DL2_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_pcm_2_playback_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN18,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN18,
				    I_DL2_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_pcm_2_playback_ch4_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN24,
				    I_DL1_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mtk_dai_pcm_widमाला_लो[] = अणु
	/* पूर्णांकer-connections */
	SND_SOC_DAPM_MIXER("PCM_1_PB_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_1_playback_ch1_mix,
			   ARRAY_SIZE(mtk_pcm_1_playback_ch1_mix)),
	SND_SOC_DAPM_MIXER("PCM_1_PB_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_1_playback_ch2_mix,
			   ARRAY_SIZE(mtk_pcm_1_playback_ch2_mix)),
	SND_SOC_DAPM_MIXER("PCM_1_PB_CH4", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_1_playback_ch4_mix,
			   ARRAY_SIZE(mtk_pcm_1_playback_ch4_mix)),
	SND_SOC_DAPM_MIXER("PCM_2_PB_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_2_playback_ch1_mix,
			   ARRAY_SIZE(mtk_pcm_2_playback_ch1_mix)),
	SND_SOC_DAPM_MIXER("PCM_2_PB_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_2_playback_ch2_mix,
			   ARRAY_SIZE(mtk_pcm_2_playback_ch2_mix)),
	SND_SOC_DAPM_MIXER("PCM_2_PB_CH4", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_2_playback_ch4_mix,
			   ARRAY_SIZE(mtk_pcm_2_playback_ch4_mix)),

	SND_SOC_DAPM_SUPPLY("PCM_1_EN", PCM_INTF_CON1, PCM_EN_SFT, 0,
			    शून्य, 0),

	SND_SOC_DAPM_SUPPLY("PCM_2_EN", PCM2_INTF_CON, PCM2_EN_SFT, 0,
			    शून्य, 0),

	SND_SOC_DAPM_INPUT("MD1_TO_AFE"),
	SND_SOC_DAPM_INPUT("MD2_TO_AFE"),
	SND_SOC_DAPM_OUTPUT("AFE_TO_MD1"),
	SND_SOC_DAPM_OUTPUT("AFE_TO_MD2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mtk_dai_pcm_routes[] = अणु
	अणु"PCM 1 Playback", शून्य, "PCM_1_PB_CH1"पूर्ण,
	अणु"PCM 1 Playback", शून्य, "PCM_1_PB_CH2"पूर्ण,
	अणु"PCM 1 Playback", शून्य, "PCM_1_PB_CH4"पूर्ण,
	अणु"PCM 2 Playback", शून्य, "PCM_2_PB_CH1"पूर्ण,
	अणु"PCM 2 Playback", शून्य, "PCM_2_PB_CH2"पूर्ण,
	अणु"PCM 2 Playback", शून्य, "PCM_2_PB_CH4"पूर्ण,

	अणु"PCM 1 Playback", शून्य, "PCM_1_EN"पूर्ण,
	अणु"PCM 2 Playback", शून्य, "PCM_2_EN"पूर्ण,
	अणु"PCM 1 Capture", शून्य, "PCM_1_EN"पूर्ण,
	अणु"PCM 2 Capture", शून्य, "PCM_2_EN"पूर्ण,

	अणु"AFE_TO_MD1", शून्य, "PCM 2 Playback"पूर्ण,
	अणु"AFE_TO_MD2", शून्य, "PCM 1 Playback"पूर्ण,
	अणु"PCM 2 Capture", शून्य, "MD1_TO_AFE"पूर्ण,
	अणु"PCM 1 Capture", शून्य, "MD2_TO_AFE"पूर्ण,

	अणु"PCM_1_PB_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"PCM_1_PB_CH2", "DL2_CH2", "DL2"पूर्ण,
	अणु"PCM_1_PB_CH4", "DL1_CH1", "DL1"पूर्ण,
	अणु"PCM_2_PB_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"PCM_2_PB_CH2", "DL2_CH2", "DL2"पूर्ण,
	अणु"PCM_2_PB_CH4", "DL1_CH1", "DL1"पूर्ण,
पूर्ण;

/* dai ops */
अटल पूर्णांक mtk_dai_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक rate_reg = mt6797_rate_transक्रमm(afe->dev, rate, dai->id);
	अचिन्हित पूर्णांक pcm_con = 0;

	dev_dbg(afe->dev, "%s(), id %d, stream %d, rate %d, rate_reg %d, widget active p %d, c %d\n",
		__func__,
		dai->id,
		substream->stream,
		rate,
		rate_reg,
		dai->playback_widget->active,
		dai->capture_widget->active);

	अगर (dai->playback_widget->active || dai->capture_widget->active)
		वापस 0;

	चयन (dai->id) अणु
	हाल MT6797_DAI_PCM_1:
		pcm_con |= AUD_BCLK_OUT_INV_NO_INVERSE << PCM_BCLK_OUT_INV_SFT;
		pcm_con |= AUD_TX_LCH_RPT_NO_REPEAT << PCM_TX_LCH_RPT_SFT;
		pcm_con |= AUD_VBT_16K_MODE_DISABLE << PCM_VBT_16K_MODE_SFT;
		pcm_con |= AUD_EXT_MODEM_SELECT_INTERNAL << PCM_EXT_MODEM_SFT;
		pcm_con |= 0 << PCM_SYNC_LENGTH_SFT;
		pcm_con |= AUD_PCM_ONE_BCK_CYCLE_SYNC << PCM_SYNC_TYPE_SFT;
		pcm_con |= AUD_BT_MODE_DUAL_MIC_ON_TX << PCM_BT_MODE_SFT;
		pcm_con |= AUD_PCM_AFIFO_AFIFO << PCM_BYP_ASRC_SFT;
		pcm_con |= AUD_PCM_CLOCK_SLAVE_MODE << PCM_SLAVE_SFT;
		pcm_con |= rate_reg << PCM_MODE_SFT;
		pcm_con |= AUD_PCM_FMT_PCM_MODE_B << PCM_FMT_SFT;

		regmap_update_bits(afe->regmap, PCM_INTF_CON1,
				   0xfffffffe, pcm_con);
		अवरोध;
	हाल MT6797_DAI_PCM_2:
		pcm_con |= AUD_TX_LCH_RPT_NO_REPEAT << PCM2_TX_LCH_RPT_SFT;
		pcm_con |= AUD_VBT_16K_MODE_DISABLE << PCM2_VBT_16K_MODE_SFT;
		pcm_con |= AUD_BT_MODE_DUAL_MIC_ON_TX << PCM2_BT_MODE_SFT;
		pcm_con |= AUD_PCM_AFIFO_AFIFO << PCM2_AFIFO_SFT;
		pcm_con |= AUD_PCM_WLEN_PCM_32_BCK_CYCLES << PCM2_WLEN_SFT;
		pcm_con |= rate_reg << PCM2_MODE_SFT;
		pcm_con |= AUD_PCM_FMT_PCM_MODE_B << PCM2_FMT_SFT;

		regmap_update_bits(afe->regmap, PCM2_INTF_CON,
				   0xfffffffe, pcm_con);
		अवरोध;
	शेष:
		dev_warn(afe->dev, "%s(), id %d not support\n",
			 __func__, dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mtk_dai_pcm_ops = अणु
	.hw_params = mtk_dai_pcm_hw_params,
पूर्ण;

/* dai driver */
#घोषणा MTK_PCM_RATES (SNDRV_PCM_RATE_8000 |\
		       SNDRV_PCM_RATE_16000 |\
		       SNDRV_PCM_RATE_32000 |\
		       SNDRV_PCM_RATE_48000)

#घोषणा MTK_PCM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mtk_dai_pcm_driver[] = अणु
	अणु
		.name = "PCM 1",
		.id = MT6797_DAI_PCM_1,
		.playback = अणु
			.stream_name = "PCM 1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "PCM 1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_pcm_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "PCM 2",
		.id = MT6797_DAI_PCM_2,
		.playback = अणु
			.stream_name = "PCM 2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "PCM 2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_pcm_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
पूर्ण;

पूर्णांक mt6797_dai_pcm_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mtk_dai_pcm_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mtk_dai_pcm_driver);

	dai->dapm_widमाला_लो = mtk_dai_pcm_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mtk_dai_pcm_widमाला_लो);
	dai->dapm_routes = mtk_dai_pcm_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mtk_dai_pcm_routes);
	वापस 0;
पूर्ण
