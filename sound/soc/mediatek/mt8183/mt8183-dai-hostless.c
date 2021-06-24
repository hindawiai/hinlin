<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI Hostless Control
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश "mt8183-afe-common.h"

/* dai component */
अटल स्थिर काष्ठा snd_soc_dapm_route mtk_dai_hostless_routes[] = अणु
	/* Hostless ADDA Loopback */
	अणु"ADDA_DL_CH1", "ADDA_UL_CH1", "Hostless LPBK DL"पूर्ण,
	अणु"ADDA_DL_CH1", "ADDA_UL_CH2", "Hostless LPBK DL"पूर्ण,
	अणु"ADDA_DL_CH2", "ADDA_UL_CH1", "Hostless LPBK DL"पूर्ण,
	अणु"ADDA_DL_CH2", "ADDA_UL_CH2", "Hostless LPBK DL"पूर्ण,
	अणु"Hostless LPBK UL", शून्य, "ADDA Capture"पूर्ण,

	/* Hostless Speech */
	अणु"ADDA_DL_CH1", "PCM_1_CAP_CH1", "Hostless Speech DL"पूर्ण,
	अणु"ADDA_DL_CH2", "PCM_1_CAP_CH1", "Hostless Speech DL"पूर्ण,
	अणु"ADDA_DL_CH2", "PCM_1_CAP_CH2", "Hostless Speech DL"पूर्ण,
	अणु"ADDA_DL_CH1", "PCM_2_CAP_CH1", "Hostless Speech DL"पूर्ण,
	अणु"ADDA_DL_CH2", "PCM_2_CAP_CH1", "Hostless Speech DL"पूर्ण,
	अणु"ADDA_DL_CH2", "PCM_2_CAP_CH2", "Hostless Speech DL"पूर्ण,
	अणु"PCM_1_PB_CH1", "ADDA_UL_CH1", "Hostless Speech DL"पूर्ण,
	अणु"PCM_1_PB_CH2", "ADDA_UL_CH2", "Hostless Speech DL"पूर्ण,
	अणु"PCM_2_PB_CH1", "ADDA_UL_CH1", "Hostless Speech DL"पूर्ण,
	अणु"PCM_2_PB_CH2", "ADDA_UL_CH2", "Hostless Speech DL"पूर्ण,

	अणु"Hostless Speech UL", शून्य, "PCM 1 Capture"पूर्ण,
	अणु"Hostless Speech UL", शून्य, "PCM 2 Capture"पूर्ण,
	अणु"Hostless Speech UL", शून्य, "ADDA Capture"पूर्ण,
पूर्ण;

/* dai ops */
अटल पूर्णांक mtk_dai_hostless_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	वापस snd_soc_set_runसमय_hwparams(substream, afe->mtk_afe_hardware);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mtk_dai_hostless_ops = अणु
	.startup = mtk_dai_hostless_startup,
पूर्ण;

/* dai driver */
#घोषणा MTK_HOSTLESS_RATES (SNDRV_PCM_RATE_8000_48000 |\
			   SNDRV_PCM_RATE_88200 |\
			   SNDRV_PCM_RATE_96000 |\
			   SNDRV_PCM_RATE_176400 |\
			   SNDRV_PCM_RATE_192000)

#घोषणा MTK_HOSTLESS_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			     SNDRV_PCM_FMTBIT_S24_LE |\
			     SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mtk_dai_hostless_driver[] = अणु
	अणु
		.name = "Hostless LPBK DAI",
		.id = MT8183_DAI_HOSTLESS_LPBK,
		.playback = अणु
			.stream_name = "Hostless LPBK DL",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_HOSTLESS_RATES,
			.क्रमmats = MTK_HOSTLESS_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Hostless LPBK UL",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_HOSTLESS_RATES,
			.क्रमmats = MTK_HOSTLESS_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_hostless_ops,
	पूर्ण,
	अणु
		.name = "Hostless Speech DAI",
		.id = MT8183_DAI_HOSTLESS_SPEECH,
		.playback = अणु
			.stream_name = "Hostless Speech DL",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_HOSTLESS_RATES,
			.क्रमmats = MTK_HOSTLESS_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Hostless Speech UL",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_HOSTLESS_RATES,
			.क्रमmats = MTK_HOSTLESS_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_hostless_ops,
	पूर्ण,
पूर्ण;

पूर्णांक mt8183_dai_hostless_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mtk_dai_hostless_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mtk_dai_hostless_driver);

	dai->dapm_routes = mtk_dai_hostless_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mtk_dai_hostless_routes);

	वापस 0;
पूर्ण
