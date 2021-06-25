<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Mediatek ALSA SoC AFE platक्रमm driver क्रम 8192
//
// Copyright (c) 2020 MediaTek Inc.
// Author: Shane Chien <shane.chien@mediatek.com>
//

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <sound/soc.h>

#समावेश "../common/mtk-afe-fe-dai.h"
#समावेश "../common/mtk-afe-platform-driver.h"

#समावेश "mt8192-afe-common.h"
#समावेश "mt8192-afe-clk.h"
#समावेश "mt8192-afe-gpio.h"
#समावेश "mt8192-interconnection.h"

अटल स्थिर काष्ठा snd_pcm_hardware mt8192_afe_hardware = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |
		    SNDRV_PCM_FMTBIT_S24_LE |
		    SNDRV_PCM_FMTBIT_S32_LE),
	.period_bytes_min = 96,
	.period_bytes_max = 4 * 48 * 1024,
	.periods_min = 2,
	.periods_max = 256,
	.buffer_bytes_max = 4 * 48 * 1024,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक mt8192_memअगर_fs(काष्ठा snd_pcm_substream *substream,
			   अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	पूर्णांक id = asoc_rtd_to_cpu(rtd, 0)->id;

	वापस mt8192_rate_transक्रमm(afe->dev, rate, id);
पूर्ण

अटल पूर्णांक mt8192_get_dai_fs(काष्ठा mtk_base_afe *afe,
			     पूर्णांक dai_id, अचिन्हित पूर्णांक rate)
अणु
	वापस mt8192_rate_transक्रमm(afe->dev, rate, dai_id);
पूर्ण

अटल पूर्णांक mt8192_irq_fs(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);

	वापस mt8192_general_rate_transक्रमm(afe->dev, rate);
पूर्ण

अटल पूर्णांक mt8192_get_memअगर_pbuf_size(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर ((runसमय->period_size * 1000) / runसमय->rate > 10)
		वापस MT8192_MEMIF_PBUF_SIZE_256_BYTES;
	अन्यथा
		वापस MT8192_MEMIF_PBUF_SIZE_32_BYTES;
पूर्ण

#घोषणा MTK_PCM_RATES (SNDRV_PCM_RATE_8000_48000 |\
		       SNDRV_PCM_RATE_88200 |\
		       SNDRV_PCM_RATE_96000 |\
		       SNDRV_PCM_RATE_176400 |\
		       SNDRV_PCM_RATE_192000)

#घोषणा MTK_PCM_DAI_RATES (SNDRV_PCM_RATE_8000 |\
			   SNDRV_PCM_RATE_16000 |\
			   SNDRV_PCM_RATE_32000 |\
			   SNDRV_PCM_RATE_48000)

#घोषणा MTK_PCM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mt8192_memअगर_dai_driver[] = अणु
	/* FE DAIs: memory पूर्णांकefaces to CPU */
	अणु
		.name = "DL1",
		.id = MT8192_MEMIF_DL1,
		.playback = अणु
			.stream_name = "DL1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL12",
		.id = MT8192_MEMIF_DL12,
		.playback = अणु
			.stream_name = "DL12",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL2",
		.id = MT8192_MEMIF_DL2,
		.playback = अणु
			.stream_name = "DL2",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL3",
		.id = MT8192_MEMIF_DL3,
		.playback = अणु
			.stream_name = "DL3",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL4",
		.id = MT8192_MEMIF_DL4,
		.playback = अणु
			.stream_name = "DL4",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL5",
		.id = MT8192_MEMIF_DL5,
		.playback = अणु
			.stream_name = "DL5",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL6",
		.id = MT8192_MEMIF_DL6,
		.playback = अणु
			.stream_name = "DL6",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL7",
		.id = MT8192_MEMIF_DL7,
		.playback = अणु
			.stream_name = "DL7",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL8",
		.id = MT8192_MEMIF_DL8,
		.playback = अणु
			.stream_name = "DL8",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "DL9",
		.id = MT8192_MEMIF_DL9,
		.playback = अणु
			.stream_name = "DL9",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL1",
		.id = MT8192_MEMIF_VUL12,
		.capture = अणु
			.stream_name = "UL1",
			.channels_min = 1,
			.channels_max = 4,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL2",
		.id = MT8192_MEMIF_AWB,
		.capture = अणु
			.stream_name = "UL2",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL3",
		.id = MT8192_MEMIF_VUL2,
		.capture = अणु
			.stream_name = "UL3",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL4",
		.id = MT8192_MEMIF_AWB2,
		.capture = अणु
			.stream_name = "UL4",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL5",
		.id = MT8192_MEMIF_VUL3,
		.capture = अणु
			.stream_name = "UL5",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL6",
		.id = MT8192_MEMIF_VUL4,
		.capture = अणु
			.stream_name = "UL6",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL7",
		.id = MT8192_MEMIF_VUL5,
		.capture = अणु
			.stream_name = "UL7",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL8",
		.id = MT8192_MEMIF_VUL6,
		.capture = अणु
			.stream_name = "UL8",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL_MONO_1",
		.id = MT8192_MEMIF_MOD_DAI,
		.capture = अणु
			.stream_name = "UL_MONO_1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_DAI_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL_MONO_2",
		.id = MT8192_MEMIF_DAI,
		.capture = अणु
			.stream_name = "UL_MONO_2",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_DAI_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL_MONO_3",
		.id = MT8192_MEMIF_DAI2,
		.capture = अणु
			.stream_name = "UL_MONO_3",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_DAI_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "HDMI",
		.id = MT8192_MEMIF_HDMI,
		.playback = अणु
			.stream_name = "HDMI",
			.channels_min = 2,
			.channels_max = 8,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ul_tinyconn_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक reg_shअगरt;
	अचिन्हित पूर्णांक reg_mask_shअगरt;

	dev_info(afe->dev, "%s(), event 0x%x\n", __func__, event);

	अगर (म_माला(w->name, "UL1")) अणु
		reg_shअगरt = VUL1_USE_TINY_SFT;
		reg_mask_shअगरt = VUL1_USE_TINY_MASK_SFT;
	पूर्ण अन्यथा अगर (म_माला(w->name, "UL2")) अणु
		reg_shअगरt = VUL2_USE_TINY_SFT;
		reg_mask_shअगरt = VUL2_USE_TINY_MASK_SFT;
	पूर्ण अन्यथा अगर (म_माला(w->name, "UL3")) अणु
		reg_shअगरt = VUL12_USE_TINY_SFT;
		reg_mask_shअगरt = VUL12_USE_TINY_MASK_SFT;
	पूर्ण अन्यथा अगर (म_माला(w->name, "UL4")) अणु
		reg_shअगरt = AWB2_USE_TINY_SFT;
		reg_mask_shअगरt = AWB2_USE_TINY_MASK_SFT;
	पूर्ण अन्यथा अणु
		reg_shअगरt = AWB2_USE_TINY_SFT;
		reg_mask_shअगरt = AWB2_USE_TINY_MASK_SFT;
		dev_warn(afe->dev, "%s(), err widget name %s, default use UL4",
			 __func__, w->name);
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(afe->regmap, AFE_MEMIF_CONN, reg_mask_shअगरt,
				   0x1 << reg_shअगरt);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(afe->regmap, AFE_MEMIF_CONN, reg_mask_shअगरt,
				   0x0 << reg_shअगरt);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* dma widget & routes*/
अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul1_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN21,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN21,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN21,
				    I_ADDA_UL_CH3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul1_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN22,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN22,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN22,
				    I_ADDA_UL_CH3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH4", AFE_CONN22,
				    I_ADDA_UL_CH4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul1_ch3_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN9,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN9,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN9,
				    I_ADDA_UL_CH3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul1_ch4_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN10,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN10,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN10,
				    I_ADDA_UL_CH3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH4", AFE_CONN10,
				    I_ADDA_UL_CH4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul2_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I2S0_CH1", AFE_CONN5,
				    I_I2S0_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN5,
				    I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH1", AFE_CONN5,
				    I_DL12_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN5,
				    I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN5,
				    I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH1", AFE_CONN5_1,
				    I_DL4_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL5_CH1", AFE_CONN5_1,
				    I_DL5_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH1", AFE_CONN5_1,
				    I_DL6_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN5,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN5,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S2_CH1", AFE_CONN5,
				    I_I2S2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S6_CH1", AFE_CONN5_1,
				    I_I2S6_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S8_CH1", AFE_CONN5_1,
				    I_I2S8_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("CONNSYS_I2S_CH1", AFE_CONN5_1,
				    I_CONNSYS_I2S_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("SRC_1_OUT_CH1", AFE_CONN5_1,
				    I_SRC_1_OUT_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul2_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("I2S0_CH2", AFE_CONN6,
				    I_I2S0_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN6,
				    I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH2", AFE_CONN6,
				    I_DL12_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN6,
				    I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN6,
				    I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH2", AFE_CONN6_1,
				    I_DL4_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL5_CH2", AFE_CONN6_1,
				    I_DL5_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH2", AFE_CONN6_1,
				    I_DL6_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN6,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN6,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S2_CH2", AFE_CONN6,
				    I_I2S2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S6_CH2", AFE_CONN6_1,
				    I_I2S6_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S8_CH2", AFE_CONN6_1,
				    I_I2S8_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("CONNSYS_I2S_CH2", AFE_CONN6_1,
				    I_CONNSYS_I2S_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("SRC_1_OUT_CH2", AFE_CONN6_1,
				    I_SRC_1_OUT_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul3_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("CONNSYS_I2S_CH1", AFE_CONN32_1,
				    I_CONNSYS_I2S_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN32,
				    I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN32,
				    I_DL2_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul3_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("CONNSYS_I2S_CH2", AFE_CONN33_1,
				    I_CONNSYS_I2S_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul4_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN38,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S0_CH1", AFE_CONN38,
				    I_I2S0_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul4_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN39,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S0_CH2", AFE_CONN39,
				    I_I2S0_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul5_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN44,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul5_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN45,
				    I_ADDA_UL_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul6_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN46,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN46,
				    I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH1", AFE_CONN46,
				    I_DL12_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH1", AFE_CONN46_1,
				    I_DL6_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN46,
				    I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN46,
				    I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH1", AFE_CONN46_1,
				    I_DL4_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN46,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN46,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul6_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN47,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN47,
				    I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH2", AFE_CONN47,
				    I_DL12_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH2", AFE_CONN47_1,
				    I_DL6_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN47,
				    I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN47,
				    I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH2", AFE_CONN47_1,
				    I_DL4_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN47,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN47,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul7_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN48,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul7_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN49,
				    I_ADDA_UL_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul8_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN50,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul8_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN51,
				    I_ADDA_UL_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul_mono_1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN12,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN12,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul_mono_2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN11,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul_mono_3_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN35,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

/* TINYCONN MUX */
क्रमागत अणु
	TINYCONN_CH1_MUX_I2S0 = 0x14,
	TINYCONN_CH2_MUX_I2S0 = 0x15,
	TINYCONN_CH1_MUX_I2S6 = 0x1a,
	TINYCONN_CH2_MUX_I2S6 = 0x1b,
	TINYCONN_CH1_MUX_I2S8 = 0x1c,
	TINYCONN_CH2_MUX_I2S8 = 0x1d,
	TINYCONN_MUX_NONE = 0x1f,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tinyconn_mux_map[] = अणु
	"NONE",
	"I2S0_CH1",
	"I2S0_CH2",
	"I2S6_CH1",
	"I2S6_CH2",
	"I2S8_CH1",
	"I2S8_CH2",
पूर्ण;

अटल पूर्णांक tinyconn_mux_map_value[] = अणु
	TINYCONN_MUX_NONE,
	TINYCONN_CH1_MUX_I2S0,
	TINYCONN_CH2_MUX_I2S0,
	TINYCONN_CH1_MUX_I2S6,
	TINYCONN_CH2_MUX_I2S6,
	TINYCONN_CH1_MUX_I2S8,
	TINYCONN_CH2_MUX_I2S8,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(ul4_tinyconn_ch1_mux_map_क्रमागत,
				  AFE_TINY_CONN0,
				  O_2_CFG_SFT,
				  O_2_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_value);
अटल SOC_VALUE_ENUM_SINGLE_DECL(ul4_tinyconn_ch2_mux_map_क्रमागत,
				  AFE_TINY_CONN0,
				  O_3_CFG_SFT,
				  O_3_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new ul4_tinyconn_ch1_mux_control =
	SOC_DAPM_ENUM("UL4_TINYCONN_CH1_MUX", ul4_tinyconn_ch1_mux_map_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new ul4_tinyconn_ch2_mux_control =
	SOC_DAPM_ENUM("UL4_TINYCONN_CH2_MUX", ul4_tinyconn_ch2_mux_map_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget mt8192_memअगर_widमाला_लो[] = अणु
	/* पूर्णांकer-connections */
	SND_SOC_DAPM_MIXER("UL1_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul1_ch1_mix, ARRAY_SIZE(memअगर_ul1_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL1_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul1_ch2_mix, ARRAY_SIZE(memअगर_ul1_ch2_mix)),
	SND_SOC_DAPM_MIXER("UL1_CH3", SND_SOC_NOPM, 0, 0,
			   memअगर_ul1_ch3_mix, ARRAY_SIZE(memअगर_ul1_ch3_mix)),
	SND_SOC_DAPM_MIXER("UL1_CH4", SND_SOC_NOPM, 0, 0,
			   memअगर_ul1_ch4_mix, ARRAY_SIZE(memअगर_ul1_ch4_mix)),

	SND_SOC_DAPM_MIXER("UL2_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul2_ch1_mix, ARRAY_SIZE(memअगर_ul2_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL2_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul2_ch2_mix, ARRAY_SIZE(memअगर_ul2_ch2_mix)),

	SND_SOC_DAPM_MIXER("UL3_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul3_ch1_mix, ARRAY_SIZE(memअगर_ul3_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL3_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul3_ch2_mix, ARRAY_SIZE(memअगर_ul3_ch2_mix)),

	SND_SOC_DAPM_MIXER("UL4_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul4_ch1_mix, ARRAY_SIZE(memअगर_ul4_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL4_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul4_ch2_mix, ARRAY_SIZE(memअगर_ul4_ch2_mix)),
	SND_SOC_DAPM_MUX_E("UL4_TINYCONN_CH1_MUX", SND_SOC_NOPM, 0, 0,
			   &ul4_tinyconn_ch1_mux_control,
			   ul_tinyconn_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_MUX_E("UL4_TINYCONN_CH2_MUX", SND_SOC_NOPM, 0, 0,
			   &ul4_tinyconn_ch2_mux_control,
			   ul_tinyconn_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_MIXER("UL5_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul5_ch1_mix, ARRAY_SIZE(memअगर_ul5_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL5_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul5_ch2_mix, ARRAY_SIZE(memअगर_ul5_ch2_mix)),

	SND_SOC_DAPM_MIXER("UL6_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul6_ch1_mix, ARRAY_SIZE(memअगर_ul6_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL6_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul6_ch2_mix, ARRAY_SIZE(memअगर_ul6_ch2_mix)),

	SND_SOC_DAPM_MIXER("UL7_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul7_ch1_mix, ARRAY_SIZE(memअगर_ul7_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL7_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul7_ch2_mix, ARRAY_SIZE(memअगर_ul7_ch2_mix)),

	SND_SOC_DAPM_MIXER("UL8_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul8_ch1_mix, ARRAY_SIZE(memअगर_ul8_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL8_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul8_ch2_mix, ARRAY_SIZE(memअगर_ul8_ch2_mix)),

	SND_SOC_DAPM_MIXER("UL_MONO_1_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul_mono_1_mix,
			   ARRAY_SIZE(memअगर_ul_mono_1_mix)),

	SND_SOC_DAPM_MIXER("UL_MONO_2_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul_mono_2_mix,
			   ARRAY_SIZE(memअगर_ul_mono_2_mix)),

	SND_SOC_DAPM_MIXER("UL_MONO_3_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul_mono_3_mix,
			   ARRAY_SIZE(memअगर_ul_mono_3_mix)),

	SND_SOC_DAPM_INPUT("UL1_VIRTUAL_INPUT"),
	SND_SOC_DAPM_INPUT("UL2_VIRTUAL_INPUT"),
	SND_SOC_DAPM_INPUT("UL6_VIRTUAL_INPUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8192_memअगर_routes[] = अणु
	अणु"UL1", शून्य, "UL1_CH1"पूर्ण,
	अणु"UL1", शून्य, "UL1_CH2"पूर्ण,
	अणु"UL1", शून्य, "UL1_CH3"पूर्ण,
	अणु"UL1", शून्य, "UL1_CH4"पूर्ण,
	अणु"UL1_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH1", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH1", "ADDA_UL_CH3", "ADDA_CH34_UL_Mux"पूर्ण,
	अणु"UL1_CH2", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH2", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH2", "ADDA_UL_CH3", "ADDA_CH34_UL_Mux"पूर्ण,
	अणु"UL1_CH2", "ADDA_UL_CH4", "ADDA_CH34_UL_Mux"पूर्ण,
	अणु"UL1_CH3", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH3", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH3", "ADDA_UL_CH3", "ADDA_CH34_UL_Mux"पूर्ण,
	अणु"UL1_CH4", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH4", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
	अणु"UL1_CH4", "ADDA_UL_CH3", "ADDA_CH34_UL_Mux"पूर्ण,
	अणु"UL1_CH4", "ADDA_UL_CH4", "ADDA_CH34_UL_Mux"पूर्ण,

	अणु"UL2", शून्य, "UL2_CH1"पूर्ण,
	अणु"UL2", शून्य, "UL2_CH2"पूर्ण,
	अणु"UL2_CH1", "I2S0_CH1", "I2S0"पूर्ण,
	अणु"UL2_CH2", "I2S0_CH2", "I2S0"पूर्ण,
	अणु"UL2_CH1", "I2S2_CH1", "I2S2"पूर्ण,
	अणु"UL2_CH2", "I2S2_CH2", "I2S2"पूर्ण,
	अणु"UL2_CH1", "I2S6_CH1", "I2S6"पूर्ण,
	अणु"UL2_CH2", "I2S6_CH2", "I2S6"पूर्ण,
	अणु"UL2_CH1", "I2S8_CH1", "I2S8"पूर्ण,
	अणु"UL2_CH2", "I2S8_CH2", "I2S8"पूर्ण,

	अणु"UL2_CH1", "PCM_1_CAP_CH1", "PCM 1 Capture"पूर्ण,
	अणु"UL2_CH2", "PCM_1_CAP_CH1", "PCM 1 Capture"पूर्ण,
	अणु"UL2_CH1", "PCM_2_CAP_CH1", "PCM 2 Capture"पूर्ण,
	अणु"UL2_CH2", "PCM_2_CAP_CH1", "PCM 2 Capture"पूर्ण,

	अणु"UL_MONO_1", शून्य, "UL_MONO_1_CH1"पूर्ण,
	अणु"UL_MONO_1_CH1", "PCM_1_CAP_CH1", "PCM 1 Capture"पूर्ण,
	अणु"UL_MONO_1_CH1", "PCM_2_CAP_CH1", "PCM 2 Capture"पूर्ण,

	अणु"UL_MONO_2", शून्य, "UL_MONO_2_CH1"पूर्ण,
	अणु"UL_MONO_2_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,

	अणु"UL_MONO_3", शून्य, "UL_MONO_3_CH1"पूर्ण,
	अणु"UL_MONO_3_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,

	अणु"UL2_CH1", "CONNSYS_I2S_CH1", "Connsys I2S"पूर्ण,
	अणु"UL2_CH2", "CONNSYS_I2S_CH2", "Connsys I2S"पूर्ण,

	अणु"UL3", शून्य, "UL3_CH1"पूर्ण,
	अणु"UL3", शून्य, "UL3_CH2"पूर्ण,
	अणु"UL3_CH1", "CONNSYS_I2S_CH1", "Connsys I2S"पूर्ण,
	अणु"UL3_CH2", "CONNSYS_I2S_CH2", "Connsys I2S"पूर्ण,

	अणु"UL4", शून्य, "UL4_CH1"पूर्ण,
	अणु"UL4", शून्य, "UL4_CH2"पूर्ण,
	अणु"UL4", शून्य, "UL4_TINYCONN_CH1_MUX"पूर्ण,
	अणु"UL4", शून्य, "UL4_TINYCONN_CH2_MUX"पूर्ण,
	अणु"UL4_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL4_CH2", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
	अणु"UL4_CH1", "I2S0_CH1", "I2S0"पूर्ण,
	अणु"UL4_CH2", "I2S0_CH2", "I2S0"पूर्ण,
	अणु"UL4_TINYCONN_CH1_MUX", "I2S0_CH1", "I2S0"पूर्ण,
	अणु"UL4_TINYCONN_CH2_MUX", "I2S0_CH2", "I2S0"पूर्ण,

	अणु"UL5", शून्य, "UL5_CH1"पूर्ण,
	अणु"UL5", शून्य, "UL5_CH2"पूर्ण,
	अणु"UL5_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL5_CH2", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,

	अणु"UL6", शून्य, "UL6_CH1"पूर्ण,
	अणु"UL6", शून्य, "UL6_CH2"पूर्ण,

	अणु"UL6_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL6_CH2", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
	अणु"UL6_CH1", "PCM_1_CAP_CH1", "PCM 1 Capture"पूर्ण,
	अणु"UL6_CH2", "PCM_1_CAP_CH1", "PCM 1 Capture"पूर्ण,
	अणु"UL6_CH1", "PCM_2_CAP_CH1", "PCM 2 Capture"पूर्ण,
	अणु"UL6_CH2", "PCM_2_CAP_CH1", "PCM 2 Capture"पूर्ण,

	अणु"UL7", शून्य, "UL7_CH1"पूर्ण,
	अणु"UL7", शून्य, "UL7_CH2"पूर्ण,
	अणु"UL7_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL7_CH2", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,

	अणु"UL8", शून्य, "UL8_CH1"पूर्ण,
	अणु"UL8", शून्य, "UL8_CH2"पूर्ण,
	अणु"UL8_CH1", "ADDA_UL_CH1", "ADDA_UL_Mux"पूर्ण,
	अणु"UL8_CH2", "ADDA_UL_CH2", "ADDA_UL_Mux"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_base_memअगर_data memअगर_data[MT8192_MEMIF_NUM] = अणु
	[MT8192_MEMIF_DL1] = अणु
		.name = "DL1",
		.id = MT8192_MEMIF_DL1,
		.reg_ofs_base = AFE_DL1_BASE,
		.reg_ofs_cur = AFE_DL1_CUR,
		.reg_ofs_end = AFE_DL1_END,
		.reg_ofs_base_msb = AFE_DL1_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL1_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL1_END_MSB,
		.fs_reg = AFE_DL1_CON0,
		.fs_shअगरt = DL1_MODE_SFT,
		.fs_maskbit = DL1_MODE_MASK,
		.mono_reg = AFE_DL1_CON0,
		.mono_shअगरt = DL1_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL1_ON_SFT,
		.hd_reg = AFE_DL1_CON0,
		.hd_shअगरt = DL1_HD_MODE_SFT,
		.hd_align_reg = AFE_DL1_CON0,
		.hd_align_mshअगरt = DL1_HALIGN_SFT,
		.pbuf_reg = AFE_DL1_CON0,
		.pbuf_shअगरt = DL1_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL1_CON0,
		.minlen_shअगरt = DL1_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL12] = अणु
		.name = "DL12",
		.id = MT8192_MEMIF_DL12,
		.reg_ofs_base = AFE_DL12_BASE,
		.reg_ofs_cur = AFE_DL12_CUR,
		.reg_ofs_end = AFE_DL12_END,
		.reg_ofs_base_msb = AFE_DL12_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL12_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL12_END_MSB,
		.fs_reg = AFE_DL12_CON0,
		.fs_shअगरt = DL12_MODE_SFT,
		.fs_maskbit = DL12_MODE_MASK,
		.mono_reg = AFE_DL12_CON0,
		.mono_shअगरt = DL12_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL12_ON_SFT,
		.hd_reg = AFE_DL12_CON0,
		.hd_shअगरt = DL12_HD_MODE_SFT,
		.hd_align_reg = AFE_DL12_CON0,
		.hd_align_mshअगरt = DL12_HALIGN_SFT,
		.pbuf_reg = AFE_DL12_CON0,
		.pbuf_shअगरt = DL12_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL12_CON0,
		.minlen_shअगरt = DL12_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL2] = अणु
		.name = "DL2",
		.id = MT8192_MEMIF_DL2,
		.reg_ofs_base = AFE_DL2_BASE,
		.reg_ofs_cur = AFE_DL2_CUR,
		.reg_ofs_end = AFE_DL2_END,
		.reg_ofs_base_msb = AFE_DL2_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL2_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL2_END_MSB,
		.fs_reg = AFE_DL2_CON0,
		.fs_shअगरt = DL2_MODE_SFT,
		.fs_maskbit = DL2_MODE_MASK,
		.mono_reg = AFE_DL2_CON0,
		.mono_shअगरt = DL2_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL2_ON_SFT,
		.hd_reg = AFE_DL2_CON0,
		.hd_shअगरt = DL2_HD_MODE_SFT,
		.hd_align_reg = AFE_DL2_CON0,
		.hd_align_mshअगरt = DL2_HALIGN_SFT,
		.pbuf_reg = AFE_DL2_CON0,
		.pbuf_shअगरt = DL2_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL2_CON0,
		.minlen_shअगरt = DL2_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL3] = अणु
		.name = "DL3",
		.id = MT8192_MEMIF_DL3,
		.reg_ofs_base = AFE_DL3_BASE,
		.reg_ofs_cur = AFE_DL3_CUR,
		.reg_ofs_end = AFE_DL3_END,
		.reg_ofs_base_msb = AFE_DL3_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL3_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL3_END_MSB,
		.fs_reg = AFE_DL3_CON0,
		.fs_shअगरt = DL3_MODE_SFT,
		.fs_maskbit = DL3_MODE_MASK,
		.mono_reg = AFE_DL3_CON0,
		.mono_shअगरt = DL3_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL3_ON_SFT,
		.hd_reg = AFE_DL3_CON0,
		.hd_shअगरt = DL3_HD_MODE_SFT,
		.hd_align_reg = AFE_DL3_CON0,
		.hd_align_mshअगरt = DL3_HALIGN_SFT,
		.pbuf_reg = AFE_DL3_CON0,
		.pbuf_shअगरt = DL3_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL3_CON0,
		.minlen_shअगरt = DL3_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL4] = अणु
		.name = "DL4",
		.id = MT8192_MEMIF_DL4,
		.reg_ofs_base = AFE_DL4_BASE,
		.reg_ofs_cur = AFE_DL4_CUR,
		.reg_ofs_end = AFE_DL4_END,
		.reg_ofs_base_msb = AFE_DL4_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL4_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL4_END_MSB,
		.fs_reg = AFE_DL4_CON0,
		.fs_shअगरt = DL4_MODE_SFT,
		.fs_maskbit = DL4_MODE_MASK,
		.mono_reg = AFE_DL4_CON0,
		.mono_shअगरt = DL4_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL4_ON_SFT,
		.hd_reg = AFE_DL4_CON0,
		.hd_shअगरt = DL4_HD_MODE_SFT,
		.hd_align_reg = AFE_DL4_CON0,
		.hd_align_mshअगरt = DL4_HALIGN_SFT,
		.pbuf_reg = AFE_DL4_CON0,
		.pbuf_shअगरt = DL4_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL4_CON0,
		.minlen_shअगरt = DL4_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL5] = अणु
		.name = "DL5",
		.id = MT8192_MEMIF_DL5,
		.reg_ofs_base = AFE_DL5_BASE,
		.reg_ofs_cur = AFE_DL5_CUR,
		.reg_ofs_end = AFE_DL5_END,
		.reg_ofs_base_msb = AFE_DL5_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL5_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL5_END_MSB,
		.fs_reg = AFE_DL5_CON0,
		.fs_shअगरt = DL5_MODE_SFT,
		.fs_maskbit = DL5_MODE_MASK,
		.mono_reg = AFE_DL5_CON0,
		.mono_shअगरt = DL5_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL5_ON_SFT,
		.hd_reg = AFE_DL5_CON0,
		.hd_shअगरt = DL5_HD_MODE_SFT,
		.hd_align_reg = AFE_DL5_CON0,
		.hd_align_mshअगरt = DL5_HALIGN_SFT,
		.pbuf_reg = AFE_DL5_CON0,
		.pbuf_shअगरt = DL5_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL5_CON0,
		.minlen_shअगरt = DL5_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL6] = अणु
		.name = "DL6",
		.id = MT8192_MEMIF_DL6,
		.reg_ofs_base = AFE_DL6_BASE,
		.reg_ofs_cur = AFE_DL6_CUR,
		.reg_ofs_end = AFE_DL6_END,
		.reg_ofs_base_msb = AFE_DL6_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL6_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL6_END_MSB,
		.fs_reg = AFE_DL6_CON0,
		.fs_shअगरt = DL6_MODE_SFT,
		.fs_maskbit = DL6_MODE_MASK,
		.mono_reg = AFE_DL6_CON0,
		.mono_shअगरt = DL6_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL6_ON_SFT,
		.hd_reg = AFE_DL6_CON0,
		.hd_shअगरt = DL6_HD_MODE_SFT,
		.hd_align_reg = AFE_DL6_CON0,
		.hd_align_mshअगरt = DL6_HALIGN_SFT,
		.pbuf_reg = AFE_DL6_CON0,
		.pbuf_shअगरt = DL6_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL6_CON0,
		.minlen_shअगरt = DL6_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL7] = अणु
		.name = "DL7",
		.id = MT8192_MEMIF_DL7,
		.reg_ofs_base = AFE_DL7_BASE,
		.reg_ofs_cur = AFE_DL7_CUR,
		.reg_ofs_end = AFE_DL7_END,
		.reg_ofs_base_msb = AFE_DL7_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL7_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL7_END_MSB,
		.fs_reg = AFE_DL7_CON0,
		.fs_shअगरt = DL7_MODE_SFT,
		.fs_maskbit = DL7_MODE_MASK,
		.mono_reg = AFE_DL7_CON0,
		.mono_shअगरt = DL7_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL7_ON_SFT,
		.hd_reg = AFE_DL7_CON0,
		.hd_shअगरt = DL7_HD_MODE_SFT,
		.hd_align_reg = AFE_DL7_CON0,
		.hd_align_mshअगरt = DL7_HALIGN_SFT,
		.pbuf_reg = AFE_DL7_CON0,
		.pbuf_shअगरt = DL7_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL7_CON0,
		.minlen_shअगरt = DL7_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL8] = अणु
		.name = "DL8",
		.id = MT8192_MEMIF_DL8,
		.reg_ofs_base = AFE_DL8_BASE,
		.reg_ofs_cur = AFE_DL8_CUR,
		.reg_ofs_end = AFE_DL8_END,
		.reg_ofs_base_msb = AFE_DL8_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL8_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL8_END_MSB,
		.fs_reg = AFE_DL8_CON0,
		.fs_shअगरt = DL8_MODE_SFT,
		.fs_maskbit = DL8_MODE_MASK,
		.mono_reg = AFE_DL8_CON0,
		.mono_shअगरt = DL8_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL8_ON_SFT,
		.hd_reg = AFE_DL8_CON0,
		.hd_shअगरt = DL8_HD_MODE_SFT,
		.hd_align_reg = AFE_DL8_CON0,
		.hd_align_mshअगरt = DL8_HALIGN_SFT,
		.pbuf_reg = AFE_DL8_CON0,
		.pbuf_shअगरt = DL8_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL8_CON0,
		.minlen_shअगरt = DL8_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DL9] = अणु
		.name = "DL9",
		.id = MT8192_MEMIF_DL9,
		.reg_ofs_base = AFE_DL9_BASE,
		.reg_ofs_cur = AFE_DL9_CUR,
		.reg_ofs_end = AFE_DL9_END,
		.reg_ofs_base_msb = AFE_DL9_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DL9_CUR_MSB,
		.reg_ofs_end_msb = AFE_DL9_END_MSB,
		.fs_reg = AFE_DL9_CON0,
		.fs_shअगरt = DL9_MODE_SFT,
		.fs_maskbit = DL9_MODE_MASK,
		.mono_reg = AFE_DL9_CON0,
		.mono_shअगरt = DL9_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL9_ON_SFT,
		.hd_reg = AFE_DL9_CON0,
		.hd_shअगरt = DL9_HD_MODE_SFT,
		.hd_align_reg = AFE_DL9_CON0,
		.hd_align_mshअगरt = DL9_HALIGN_SFT,
		.pbuf_reg = AFE_DL9_CON0,
		.pbuf_shअगरt = DL9_PBUF_SIZE_SFT,
		.minlen_reg = AFE_DL9_CON0,
		.minlen_shअगरt = DL9_MINLEN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DAI] = अणु
		.name = "DAI",
		.id = MT8192_MEMIF_DAI,
		.reg_ofs_base = AFE_DAI_BASE,
		.reg_ofs_cur = AFE_DAI_CUR,
		.reg_ofs_end = AFE_DAI_END,
		.reg_ofs_base_msb = AFE_DAI_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DAI_CUR_MSB,
		.reg_ofs_end_msb = AFE_DAI_END_MSB,
		.fs_reg = AFE_DAI_CON0,
		.fs_shअगरt = DAI_MODE_SFT,
		.fs_maskbit = DAI_MODE_MASK,
		.mono_reg = AFE_DAI_CON0,
		.mono_shअगरt = DAI_DUPLICATE_WR_SFT,
		.mono_invert = 1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DAI_ON_SFT,
		.hd_reg = AFE_DAI_CON0,
		.hd_shअगरt = DAI_HD_MODE_SFT,
		.hd_align_reg = AFE_DAI_CON0,
		.hd_align_mshअगरt = DAI_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_MOD_DAI] = अणु
		.name = "MOD_DAI",
		.id = MT8192_MEMIF_MOD_DAI,
		.reg_ofs_base = AFE_MOD_DAI_BASE,
		.reg_ofs_cur = AFE_MOD_DAI_CUR,
		.reg_ofs_end = AFE_MOD_DAI_END,
		.reg_ofs_base_msb = AFE_MOD_DAI_BASE_MSB,
		.reg_ofs_cur_msb = AFE_MOD_DAI_CUR_MSB,
		.reg_ofs_end_msb = AFE_MOD_DAI_END_MSB,
		.fs_reg = AFE_MOD_DAI_CON0,
		.fs_shअगरt = MOD_DAI_MODE_SFT,
		.fs_maskbit = MOD_DAI_MODE_MASK,
		.mono_reg = AFE_MOD_DAI_CON0,
		.mono_shअगरt = MOD_DAI_DUPLICATE_WR_SFT,
		.mono_invert = 1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = MOD_DAI_ON_SFT,
		.hd_reg = AFE_MOD_DAI_CON0,
		.hd_shअगरt = MOD_DAI_HD_MODE_SFT,
		.hd_align_reg = AFE_MOD_DAI_CON0,
		.hd_align_mshअगरt = MOD_DAI_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_DAI2] = अणु
		.name = "DAI2",
		.id = MT8192_MEMIF_DAI2,
		.reg_ofs_base = AFE_DAI2_BASE,
		.reg_ofs_cur = AFE_DAI2_CUR,
		.reg_ofs_end = AFE_DAI2_END,
		.reg_ofs_base_msb = AFE_DAI2_BASE_MSB,
		.reg_ofs_cur_msb = AFE_DAI2_CUR_MSB,
		.reg_ofs_end_msb = AFE_DAI2_END_MSB,
		.fs_reg = AFE_DAI2_CON0,
		.fs_shअगरt = DAI2_MODE_SFT,
		.fs_maskbit = DAI2_MODE_MASK,
		.mono_reg = AFE_DAI2_CON0,
		.mono_shअगरt = DAI2_DUPLICATE_WR_SFT,
		.mono_invert = 1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DAI2_ON_SFT,
		.hd_reg = AFE_DAI2_CON0,
		.hd_shअगरt = DAI2_HD_MODE_SFT,
		.hd_align_reg = AFE_DAI2_CON0,
		.hd_align_mshअगरt = DAI2_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_VUL12] = अणु
		.name = "VUL12",
		.id = MT8192_MEMIF_VUL12,
		.reg_ofs_base = AFE_VUL12_BASE,
		.reg_ofs_cur = AFE_VUL12_CUR,
		.reg_ofs_end = AFE_VUL12_END,
		.reg_ofs_base_msb = AFE_VUL12_BASE_MSB,
		.reg_ofs_cur_msb = AFE_VUL12_CUR_MSB,
		.reg_ofs_end_msb = AFE_VUL12_END_MSB,
		.fs_reg = AFE_VUL12_CON0,
		.fs_shअगरt = VUL12_MODE_SFT,
		.fs_maskbit = VUL12_MODE_MASK,
		.mono_reg = AFE_VUL12_CON0,
		.mono_shअगरt = VUL12_MONO_SFT,
		.quad_ch_reg = AFE_VUL12_CON0,
		.quad_ch_shअगरt = VUL12_4CH_EN_SFT,
		.quad_ch_mask = VUL12_4CH_EN_MASK,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL12_ON_SFT,
		.hd_reg = AFE_VUL12_CON0,
		.hd_shअगरt = VUL12_HD_MODE_SFT,
		.hd_align_reg = AFE_VUL12_CON0,
		.hd_align_mshअगरt = VUL12_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_VUL2] = अणु
		.name = "VUL2",
		.id = MT8192_MEMIF_VUL2,
		.reg_ofs_base = AFE_VUL2_BASE,
		.reg_ofs_cur = AFE_VUL2_CUR,
		.reg_ofs_end = AFE_VUL2_END,
		.reg_ofs_base_msb = AFE_VUL2_BASE_MSB,
		.reg_ofs_cur_msb = AFE_VUL2_CUR_MSB,
		.reg_ofs_end_msb = AFE_VUL2_END_MSB,
		.fs_reg = AFE_VUL2_CON0,
		.fs_shअगरt = VUL2_MODE_SFT,
		.fs_maskbit = VUL2_MODE_MASK,
		.mono_reg = AFE_VUL2_CON0,
		.mono_shअगरt = VUL2_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL2_ON_SFT,
		.hd_reg = AFE_VUL2_CON0,
		.hd_shअगरt = VUL2_HD_MODE_SFT,
		.hd_align_reg = AFE_VUL2_CON0,
		.hd_align_mshअगरt = VUL2_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_AWB] = अणु
		.name = "AWB",
		.id = MT8192_MEMIF_AWB,
		.reg_ofs_base = AFE_AWB_BASE,
		.reg_ofs_cur = AFE_AWB_CUR,
		.reg_ofs_end = AFE_AWB_END,
		.reg_ofs_base_msb = AFE_AWB_BASE_MSB,
		.reg_ofs_cur_msb = AFE_AWB_CUR_MSB,
		.reg_ofs_end_msb = AFE_AWB_END_MSB,
		.fs_reg = AFE_AWB_CON0,
		.fs_shअगरt = AWB_MODE_SFT,
		.fs_maskbit = AWB_MODE_MASK,
		.mono_reg = AFE_AWB_CON0,
		.mono_shअगरt = AWB_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = AWB_ON_SFT,
		.hd_reg = AFE_AWB_CON0,
		.hd_shअगरt = AWB_HD_MODE_SFT,
		.hd_align_reg = AFE_AWB_CON0,
		.hd_align_mshअगरt = AWB_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_AWB2] = अणु
		.name = "AWB2",
		.id = MT8192_MEMIF_AWB2,
		.reg_ofs_base = AFE_AWB2_BASE,
		.reg_ofs_cur = AFE_AWB2_CUR,
		.reg_ofs_end = AFE_AWB2_END,
		.reg_ofs_base_msb = AFE_AWB2_BASE_MSB,
		.reg_ofs_cur_msb = AFE_AWB2_CUR_MSB,
		.reg_ofs_end_msb = AFE_AWB2_END_MSB,
		.fs_reg = AFE_AWB2_CON0,
		.fs_shअगरt = AWB2_MODE_SFT,
		.fs_maskbit = AWB2_MODE_MASK,
		.mono_reg = AFE_AWB2_CON0,
		.mono_shअगरt = AWB2_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = AWB2_ON_SFT,
		.hd_reg = AFE_AWB2_CON0,
		.hd_shअगरt = AWB2_HD_MODE_SFT,
		.hd_align_reg = AFE_AWB2_CON0,
		.hd_align_mshअगरt = AWB2_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_VUL3] = अणु
		.name = "VUL3",
		.id = MT8192_MEMIF_VUL3,
		.reg_ofs_base = AFE_VUL3_BASE,
		.reg_ofs_cur = AFE_VUL3_CUR,
		.reg_ofs_end = AFE_VUL3_END,
		.reg_ofs_base_msb = AFE_VUL3_BASE_MSB,
		.reg_ofs_cur_msb = AFE_VUL3_CUR_MSB,
		.reg_ofs_end_msb = AFE_VUL3_END_MSB,
		.fs_reg = AFE_VUL3_CON0,
		.fs_shअगरt = VUL3_MODE_SFT,
		.fs_maskbit = VUL3_MODE_MASK,
		.mono_reg = AFE_VUL3_CON0,
		.mono_shअगरt = VUL3_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL3_ON_SFT,
		.hd_reg = AFE_VUL3_CON0,
		.hd_shअगरt = VUL3_HD_MODE_SFT,
		.hd_align_reg = AFE_VUL3_CON0,
		.hd_align_mshअगरt = VUL3_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_VUL4] = अणु
		.name = "VUL4",
		.id = MT8192_MEMIF_VUL4,
		.reg_ofs_base = AFE_VUL4_BASE,
		.reg_ofs_cur = AFE_VUL4_CUR,
		.reg_ofs_end = AFE_VUL4_END,
		.reg_ofs_base_msb = AFE_VUL4_BASE_MSB,
		.reg_ofs_cur_msb = AFE_VUL4_CUR_MSB,
		.reg_ofs_end_msb = AFE_VUL4_END_MSB,
		.fs_reg = AFE_VUL4_CON0,
		.fs_shअगरt = VUL4_MODE_SFT,
		.fs_maskbit = VUL4_MODE_MASK,
		.mono_reg = AFE_VUL4_CON0,
		.mono_shअगरt = VUL4_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL4_ON_SFT,
		.hd_reg = AFE_VUL4_CON0,
		.hd_shअगरt = VUL4_HD_MODE_SFT,
		.hd_align_reg = AFE_VUL4_CON0,
		.hd_align_mshअगरt = VUL4_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_VUL5] = अणु
		.name = "VUL5",
		.id = MT8192_MEMIF_VUL5,
		.reg_ofs_base = AFE_VUL5_BASE,
		.reg_ofs_cur = AFE_VUL5_CUR,
		.reg_ofs_end = AFE_VUL5_END,
		.reg_ofs_base_msb = AFE_VUL5_BASE_MSB,
		.reg_ofs_cur_msb = AFE_VUL5_CUR_MSB,
		.reg_ofs_end_msb = AFE_VUL5_END_MSB,
		.fs_reg = AFE_VUL5_CON0,
		.fs_shअगरt = VUL5_MODE_SFT,
		.fs_maskbit = VUL5_MODE_MASK,
		.mono_reg = AFE_VUL5_CON0,
		.mono_shअगरt = VUL5_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL5_ON_SFT,
		.hd_reg = AFE_VUL5_CON0,
		.hd_shअगरt = VUL5_HD_MODE_SFT,
		.hd_align_reg = AFE_VUL5_CON0,
		.hd_align_mshअगरt = VUL5_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_VUL6] = अणु
		.name = "VUL6",
		.id = MT8192_MEMIF_VUL6,
		.reg_ofs_base = AFE_VUL6_BASE,
		.reg_ofs_cur = AFE_VUL6_CUR,
		.reg_ofs_end = AFE_VUL6_END,
		.reg_ofs_base_msb = AFE_VUL6_BASE_MSB,
		.reg_ofs_cur_msb = AFE_VUL6_CUR_MSB,
		.reg_ofs_end_msb = AFE_VUL6_END_MSB,
		.fs_reg = AFE_VUL6_CON0,
		.fs_shअगरt = VUL6_MODE_SFT,
		.fs_maskbit = VUL6_MODE_MASK,
		.mono_reg = AFE_VUL6_CON0,
		.mono_shअगरt = VUL6_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL6_ON_SFT,
		.hd_reg = AFE_VUL6_CON0,
		.hd_shअगरt = VUL6_HD_MODE_SFT,
		.hd_align_reg = AFE_VUL6_CON0,
		.hd_align_mshअगरt = VUL6_HALIGN_SFT,
	पूर्ण,
	[MT8192_MEMIF_HDMI] = अणु
		.name = "HDMI",
		.id = MT8192_MEMIF_HDMI,
		.reg_ofs_base = AFE_HDMI_OUT_BASE,
		.reg_ofs_cur = AFE_HDMI_OUT_CUR,
		.reg_ofs_end = AFE_HDMI_OUT_END,
		.reg_ofs_base_msb = AFE_HDMI_OUT_BASE_MSB,
		.reg_ofs_cur_msb = AFE_HDMI_OUT_CUR_MSB,
		.reg_ofs_end_msb = AFE_HDMI_OUT_END_MSB,
		.fs_reg = -1,
		.fs_shअगरt = -1,
		.fs_maskbit = -1,
		.mono_reg = -1,
		.mono_shअगरt = -1,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = HDMI_OUT_ON_SFT,
		.hd_reg = AFE_HDMI_OUT_CON0,
		.hd_shअगरt = HDMI_OUT_HD_MODE_SFT,
		.hd_align_reg = AFE_HDMI_OUT_CON0,
		.hd_align_mshअगरt = HDMI_OUT_HALIGN_SFT,
		.pbuf_reg = AFE_HDMI_OUT_CON0,
		.minlen_reg = AFE_HDMI_OUT_CON0,
		.minlen_shअगरt = HDMI_OUT_MINLEN_SFT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_base_irq_data irq_data[MT8192_IRQ_NUM] = अणु
	[MT8192_IRQ_0] = अणु
		.id = MT8192_IRQ_0,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT0,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ0_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ0_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ0_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ0_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_1] = अणु
		.id = MT8192_IRQ_1,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT1,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ1_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ1_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ1_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ1_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_2] = अणु
		.id = MT8192_IRQ_2,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT2,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ2_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ2_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ2_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ2_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_3] = अणु
		.id = MT8192_IRQ_3,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT3,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ3_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ3_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ3_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ3_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_4] = अणु
		.id = MT8192_IRQ_4,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT4,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ4_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ4_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ4_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ4_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_5] = अणु
		.id = MT8192_IRQ_5,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT5,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ5_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ5_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ5_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ5_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_6] = अणु
		.id = MT8192_IRQ_6,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT6,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ6_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ6_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ6_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ6_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_7] = अणु
		.id = MT8192_IRQ_7,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT7,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ7_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ7_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ7_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ7_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_8] = अणु
		.id = MT8192_IRQ_8,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT8,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ8_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ8_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ8_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ8_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_9] = अणु
		.id = MT8192_IRQ_9,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT9,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ9_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ9_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ9_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ9_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_10] = अणु
		.id = MT8192_IRQ_10,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT10,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ10_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ10_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ10_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ10_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_11] = अणु
		.id = MT8192_IRQ_11,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT11,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ11_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ11_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ11_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ11_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_12] = अणु
		.id = MT8192_IRQ_12,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT12,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ12_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ12_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ12_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ12_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_13] = अणु
		.id = MT8192_IRQ_13,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT13,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ13_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ13_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ13_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ13_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_14] = अणु
		.id = MT8192_IRQ_14,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT14,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ14_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ14_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ14_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ14_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_15] = अणु
		.id = MT8192_IRQ_15,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT15,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ15_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ15_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ15_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ15_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_16] = अणु
		.id = MT8192_IRQ_16,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT16,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ16_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ16_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ16_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ16_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_17] = अणु
		.id = MT8192_IRQ_17,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT17,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ17_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ17_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ17_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ17_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_18] = अणु
		.id = MT8192_IRQ_18,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT18,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ18_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ18_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ18_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ18_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_19] = अणु
		.id = MT8192_IRQ_19,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT19,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ19_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ19_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ19_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ19_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_20] = अणु
		.id = MT8192_IRQ_20,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT20,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ20_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ20_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ20_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ20_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_21] = अणु
		.id = MT8192_IRQ_21,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT21,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ21_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ21_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ21_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ21_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_22] = अणु
		.id = MT8192_IRQ_22,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT22,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ22_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ22_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ22_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ22_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_23] = अणु
		.id = MT8192_IRQ_23,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT23,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON3,
		.irq_fs_shअगरt = IRQ23_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ23_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ23_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ23_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_24] = अणु
		.id = MT8192_IRQ_24,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT24,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON4,
		.irq_fs_shअगरt = IRQ24_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ24_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ24_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ24_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_25] = अणु
		.id = MT8192_IRQ_25,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT25,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON4,
		.irq_fs_shअगरt = IRQ25_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ25_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ25_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ25_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_26] = अणु
		.id = MT8192_IRQ_26,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT26,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = AFE_IRQ_MCU_CON4,
		.irq_fs_shअगरt = IRQ26_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ26_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ26_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ26_MCU_CLR_SFT,
	पूर्ण,
	[MT8192_IRQ_31] = अणु
		.id = MT8192_IRQ_31,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT31,
		.irq_cnt_shअगरt = AFE_IRQ_CNT_SHIFT,
		.irq_cnt_maskbit = AFE_IRQ_CNT_MASK,
		.irq_fs_reg = -1,
		.irq_fs_shअगरt = -1,
		.irq_fs_maskbit = -1,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ31_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ31_MCU_CLR_SFT,
	पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक memअगर_irq_usage[MT8192_MEMIF_NUM] = अणु
	[MT8192_MEMIF_DL1] = MT8192_IRQ_0,
	[MT8192_MEMIF_DL2] = MT8192_IRQ_1,
	[MT8192_MEMIF_DL3] = MT8192_IRQ_2,
	[MT8192_MEMIF_DL4] = MT8192_IRQ_3,
	[MT8192_MEMIF_DL5] = MT8192_IRQ_4,
	[MT8192_MEMIF_DL6] = MT8192_IRQ_5,
	[MT8192_MEMIF_DL7] = MT8192_IRQ_6,
	[MT8192_MEMIF_DL8] = MT8192_IRQ_7,
	[MT8192_MEMIF_DL9] = MT8192_IRQ_8,
	[MT8192_MEMIF_DL12] = MT8192_IRQ_9,
	[MT8192_MEMIF_DAI] = MT8192_IRQ_10,
	[MT8192_MEMIF_MOD_DAI] = MT8192_IRQ_11,
	[MT8192_MEMIF_DAI2] = MT8192_IRQ_12,
	[MT8192_MEMIF_VUL12] = MT8192_IRQ_13,
	[MT8192_MEMIF_VUL2] = MT8192_IRQ_14,
	[MT8192_MEMIF_AWB] = MT8192_IRQ_15,
	[MT8192_MEMIF_AWB2] = MT8192_IRQ_16,
	[MT8192_MEMIF_VUL3] = MT8192_IRQ_17,
	[MT8192_MEMIF_VUL4] = MT8192_IRQ_18,
	[MT8192_MEMIF_VUL5] = MT8192_IRQ_19,
	[MT8192_MEMIF_VUL6] = MT8192_IRQ_20,
	[MT8192_MEMIF_HDMI] = MT8192_IRQ_31,
पूर्ण;

अटल bool mt8192_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* these स्वतः-gen reg has पढ़ो-only bit, so put it as अस्थिर */
	/* अस्थिर reg cannot be cached, so cannot be set when घातer off */
	चयन (reg) अणु
	हाल AUDIO_TOP_CON0:	/* reg bit controlled by CCF */
	हाल AUDIO_TOP_CON1:	/* reg bit controlled by CCF */
	हाल AUDIO_TOP_CON2:
	हाल AUDIO_TOP_CON3:
	हाल AFE_DL1_CUR_MSB:
	हाल AFE_DL1_CUR:
	हाल AFE_DL1_END:
	हाल AFE_DL2_CUR_MSB:
	हाल AFE_DL2_CUR:
	हाल AFE_DL2_END:
	हाल AFE_DL3_CUR_MSB:
	हाल AFE_DL3_CUR:
	हाल AFE_DL3_END:
	हाल AFE_DL4_CUR_MSB:
	हाल AFE_DL4_CUR:
	हाल AFE_DL4_END:
	हाल AFE_DL12_CUR_MSB:
	हाल AFE_DL12_CUR:
	हाल AFE_DL12_END:
	हाल AFE_ADDA_SRC_DEBUG_MON0:
	हाल AFE_ADDA_SRC_DEBUG_MON1:
	हाल AFE_ADDA_UL_SRC_MON0:
	हाल AFE_ADDA_UL_SRC_MON1:
	हाल AFE_SECURE_CON0:
	हाल AFE_SRAM_BOUND:
	हाल AFE_SECURE_CON1:
	हाल AFE_VUL_CUR_MSB:
	हाल AFE_VUL_CUR:
	हाल AFE_VUL_END:
	हाल AFE_ADDA_3RD_DAC_DL_SDM_FIFO_MON:
	हाल AFE_ADDA_3RD_DAC_DL_SRC_LCH_MON:
	हाल AFE_ADDA_3RD_DAC_DL_SRC_RCH_MON:
	हाल AFE_ADDA_3RD_DAC_DL_SDM_OUT_MON:
	हाल AFE_SIDETONE_MON:
	हाल AFE_SIDETONE_CON0:
	हाल AFE_SIDETONE_COEFF:
	हाल AFE_VUL2_CUR_MSB:
	हाल AFE_VUL2_CUR:
	हाल AFE_VUL2_END:
	हाल AFE_VUL3_CUR_MSB:
	हाल AFE_VUL3_CUR:
	हाल AFE_VUL3_END:
	हाल AFE_I2S_MON:
	हाल AFE_DAC_MON:
	हाल AFE_IRQ0_MCU_CNT_MON:
	हाल AFE_IRQ6_MCU_CNT_MON:
	हाल AFE_VUL4_CUR_MSB:
	हाल AFE_VUL4_CUR:
	हाल AFE_VUL4_END:
	हाल AFE_VUL12_CUR_MSB:
	हाल AFE_VUL12_CUR:
	हाल AFE_VUL12_END:
	हाल AFE_IRQ3_MCU_CNT_MON:
	हाल AFE_IRQ4_MCU_CNT_MON:
	हाल AFE_IRQ_MCU_STATUS:
	हाल AFE_IRQ_MCU_CLR:
	हाल AFE_IRQ_MCU_MON2:
	हाल AFE_IRQ1_MCU_CNT_MON:
	हाल AFE_IRQ2_MCU_CNT_MON:
	हाल AFE_IRQ5_MCU_CNT_MON:
	हाल AFE_IRQ7_MCU_CNT_MON:
	हाल AFE_IRQ_MCU_MISS_CLR:
	हाल AFE_GAIN1_CUR:
	हाल AFE_GAIN2_CUR:
	हाल AFE_SRAM_DELSEL_CON1:
	हाल PCM_INTF_CON2:
	हाल FPGA_CFG0:
	हाल FPGA_CFG1:
	हाल FPGA_CFG2:
	हाल FPGA_CFG3:
	हाल AUDIO_TOP_DBG_MON0:
	हाल AUDIO_TOP_DBG_MON1:
	हाल AFE_IRQ8_MCU_CNT_MON:
	हाल AFE_IRQ11_MCU_CNT_MON:
	हाल AFE_IRQ12_MCU_CNT_MON:
	हाल AFE_IRQ9_MCU_CNT_MON:
	हाल AFE_IRQ10_MCU_CNT_MON:
	हाल AFE_IRQ13_MCU_CNT_MON:
	हाल AFE_IRQ14_MCU_CNT_MON:
	हाल AFE_IRQ15_MCU_CNT_MON:
	हाल AFE_IRQ16_MCU_CNT_MON:
	हाल AFE_IRQ17_MCU_CNT_MON:
	हाल AFE_IRQ18_MCU_CNT_MON:
	हाल AFE_IRQ19_MCU_CNT_MON:
	हाल AFE_IRQ20_MCU_CNT_MON:
	हाल AFE_IRQ21_MCU_CNT_MON:
	हाल AFE_IRQ22_MCU_CNT_MON:
	हाल AFE_IRQ23_MCU_CNT_MON:
	हाल AFE_IRQ24_MCU_CNT_MON:
	हाल AFE_IRQ25_MCU_CNT_MON:
	हाल AFE_IRQ26_MCU_CNT_MON:
	हाल AFE_IRQ31_MCU_CNT_MON:
	हाल AFE_CBIP_MON0:
	हाल AFE_CBIP_SLV_MUX_MON0:
	हाल AFE_CBIP_SLV_DECODER_MON0:
	हाल AFE_ADDA6_MTKAIF_MON0:
	हाल AFE_ADDA6_MTKAIF_MON1:
	हाल AFE_AWB_CUR_MSB:
	हाल AFE_AWB_CUR:
	हाल AFE_AWB_END:
	हाल AFE_AWB2_CUR_MSB:
	हाल AFE_AWB2_CUR:
	हाल AFE_AWB2_END:
	हाल AFE_DAI_CUR_MSB:
	हाल AFE_DAI_CUR:
	हाल AFE_DAI_END:
	हाल AFE_DAI2_CUR_MSB:
	हाल AFE_DAI2_CUR:
	हाल AFE_DAI2_END:
	हाल AFE_ADDA6_SRC_DEBUG_MON0:
	हाल AFE_ADD6A_UL_SRC_MON0:
	हाल AFE_ADDA6_UL_SRC_MON1:
	हाल AFE_MOD_DAI_CUR_MSB:
	हाल AFE_MOD_DAI_CUR:
	हाल AFE_MOD_DAI_END:
	हाल AFE_HDMI_OUT_CUR_MSB:
	हाल AFE_HDMI_OUT_CUR:
	हाल AFE_HDMI_OUT_END:
	हाल AFE_AWB_RCH_MON:
	हाल AFE_AWB_LCH_MON:
	हाल AFE_VUL_RCH_MON:
	हाल AFE_VUL_LCH_MON:
	हाल AFE_VUL12_RCH_MON:
	हाल AFE_VUL12_LCH_MON:
	हाल AFE_VUL2_RCH_MON:
	हाल AFE_VUL2_LCH_MON:
	हाल AFE_DAI_DATA_MON:
	हाल AFE_MOD_DAI_DATA_MON:
	हाल AFE_DAI2_DATA_MON:
	हाल AFE_AWB2_RCH_MON:
	हाल AFE_AWB2_LCH_MON:
	हाल AFE_VUL3_RCH_MON:
	हाल AFE_VUL3_LCH_MON:
	हाल AFE_VUL4_RCH_MON:
	हाल AFE_VUL4_LCH_MON:
	हाल AFE_VUL5_RCH_MON:
	हाल AFE_VUL5_LCH_MON:
	हाल AFE_VUL6_RCH_MON:
	हाल AFE_VUL6_LCH_MON:
	हाल AFE_DL1_RCH_MON:
	हाल AFE_DL1_LCH_MON:
	हाल AFE_DL2_RCH_MON:
	हाल AFE_DL2_LCH_MON:
	हाल AFE_DL12_RCH1_MON:
	हाल AFE_DL12_LCH1_MON:
	हाल AFE_DL12_RCH2_MON:
	हाल AFE_DL12_LCH2_MON:
	हाल AFE_DL3_RCH_MON:
	हाल AFE_DL3_LCH_MON:
	हाल AFE_DL4_RCH_MON:
	हाल AFE_DL4_LCH_MON:
	हाल AFE_DL5_RCH_MON:
	हाल AFE_DL5_LCH_MON:
	हाल AFE_DL6_RCH_MON:
	हाल AFE_DL6_LCH_MON:
	हाल AFE_DL7_RCH_MON:
	हाल AFE_DL7_LCH_MON:
	हाल AFE_DL8_RCH_MON:
	हाल AFE_DL8_LCH_MON:
	हाल AFE_VUL5_CUR_MSB:
	हाल AFE_VUL5_CUR:
	हाल AFE_VUL5_END:
	हाल AFE_VUL6_CUR_MSB:
	हाल AFE_VUL6_CUR:
	हाल AFE_VUL6_END:
	हाल AFE_ADDA_DL_SDM_FIFO_MON:
	हाल AFE_ADDA_DL_SRC_LCH_MON:
	हाल AFE_ADDA_DL_SRC_RCH_MON:
	हाल AFE_ADDA_DL_SDM_OUT_MON:
	हाल AFE_CONNSYS_I2S_MON:
	हाल AFE_ASRC_2CH_CON0:
	हाल AFE_ASRC_2CH_CON2:
	हाल AFE_ASRC_2CH_CON3:
	हाल AFE_ASRC_2CH_CON4:
	हाल AFE_ASRC_2CH_CON5:
	हाल AFE_ASRC_2CH_CON7:
	हाल AFE_ASRC_2CH_CON8:
	हाल AFE_ASRC_2CH_CON12:
	हाल AFE_ASRC_2CH_CON13:
	हाल AFE_DL9_CUR_MSB:
	हाल AFE_DL9_CUR:
	हाल AFE_DL9_END:
	हाल AFE_ADDA_MTKAIF_MON0:
	हाल AFE_ADDA_MTKAIF_MON1:
	हाल AFE_DL_NLE_R_MON0:
	हाल AFE_DL_NLE_R_MON1:
	हाल AFE_DL_NLE_R_MON2:
	हाल AFE_DL_NLE_L_MON0:
	हाल AFE_DL_NLE_L_MON1:
	हाल AFE_DL_NLE_L_MON2:
	हाल AFE_GENERAL1_ASRC_2CH_CON0:
	हाल AFE_GENERAL1_ASRC_2CH_CON2:
	हाल AFE_GENERAL1_ASRC_2CH_CON3:
	हाल AFE_GENERAL1_ASRC_2CH_CON4:
	हाल AFE_GENERAL1_ASRC_2CH_CON5:
	हाल AFE_GENERAL1_ASRC_2CH_CON7:
	हाल AFE_GENERAL1_ASRC_2CH_CON8:
	हाल AFE_GENERAL1_ASRC_2CH_CON12:
	हाल AFE_GENERAL1_ASRC_2CH_CON13:
	हाल AFE_GENERAL2_ASRC_2CH_CON0:
	हाल AFE_GENERAL2_ASRC_2CH_CON2:
	हाल AFE_GENERAL2_ASRC_2CH_CON3:
	हाल AFE_GENERAL2_ASRC_2CH_CON4:
	हाल AFE_GENERAL2_ASRC_2CH_CON5:
	हाल AFE_GENERAL2_ASRC_2CH_CON7:
	हाल AFE_GENERAL2_ASRC_2CH_CON8:
	हाल AFE_GENERAL2_ASRC_2CH_CON12:
	हाल AFE_GENERAL2_ASRC_2CH_CON13:
	हाल AFE_DL9_RCH_MON:
	हाल AFE_DL9_LCH_MON:
	हाल AFE_DL5_CUR_MSB:
	हाल AFE_DL5_CUR:
	हाल AFE_DL5_END:
	हाल AFE_DL6_CUR_MSB:
	हाल AFE_DL6_CUR:
	हाल AFE_DL6_END:
	हाल AFE_DL7_CUR_MSB:
	हाल AFE_DL7_CUR:
	हाल AFE_DL7_END:
	हाल AFE_DL8_CUR_MSB:
	हाल AFE_DL8_CUR:
	हाल AFE_DL8_END:
	हाल AFE_PROT_SIDEBAND_MON:
	हाल AFE_DOMAIN_SIDEBAND0_MON:
	हाल AFE_DOMAIN_SIDEBAND1_MON:
	हाल AFE_DOMAIN_SIDEBAND2_MON:
	हाल AFE_DOMAIN_SIDEBAND3_MON:
	हाल AFE_APLL1_TUNER_CFG:	/* [20:31] is monitor */
	हाल AFE_APLL2_TUNER_CFG:	/* [20:31] is monitor */
	हाल AFE_DAC_CON0:
	हाल AFE_IRQ_MCU_CON0:
	हाल AFE_IRQ_MCU_EN:
		वापस true;
	शेष:
		वापस false;
	पूर्ण;
पूर्ण

अटल स्थिर काष्ठा regmap_config mt8192_afe_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.अस्थिर_reg = mt8192_is_अस्थिर_reg,
	.max_रेजिस्टर = AFE_MAX_REGISTER,
	.num_reg_शेषs_raw = AFE_MAX_REGISTER,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल irqवापस_t mt8192_afe_irq_handler(पूर्णांक irq_id, व्योम *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev;
	काष्ठा mtk_base_afe_irq *irq;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक status_mcu;
	अचिन्हित पूर्णांक mcu_en;
	पूर्णांक ret;
	पूर्णांक i;

	/* get irq that is sent to MCU */
	regmap_पढ़ो(afe->regmap, AFE_IRQ_MCU_EN, &mcu_en);

	ret = regmap_पढ़ो(afe->regmap, AFE_IRQ_MCU_STATUS, &status);
	/* only care IRQ which is sent to MCU */
	status_mcu = status & mcu_en & AFE_IRQ_STATUS_BITS;

	अगर (ret || status_mcu == 0) अणु
		dev_err(afe->dev, "%s(), irq status err, ret %d, status 0x%x, mcu_en 0x%x\n",
			__func__, ret, status, mcu_en);

		जाओ err_irq;
	पूर्ण

	क्रम (i = 0; i < MT8192_MEMIF_NUM; i++) अणु
		काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[i];

		अगर (!memअगर->substream)
			जारी;

		अगर (memअगर->irq_usage < 0)
			जारी;

		irq = &afe->irqs[memअगर->irq_usage];

		अगर (status_mcu & (1 << irq->irq_data->irq_en_shअगरt))
			snd_pcm_period_elapsed(memअगर->substream);
	पूर्ण

err_irq:
	/* clear irq */
	regmap_ग_लिखो(afe->regmap,
		     AFE_IRQ_MCU_CLR,
		     status_mcu);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mt8192_afe_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	dev_info(afe->dev, "%s()\n", __func__);

	अगर (!afe->regmap || afe_priv->pm_runसमय_bypass_reg_ctl)
		जाओ skip_regmap;

	/* disable AFE */
	regmap_update_bits(afe->regmap, AFE_DAC_CON0, AFE_ON_MASK_SFT, 0x0);

	ret = regmap_पढ़ो_poll_समयout(afe->regmap,
				       AFE_DAC_MON,
				       value,
				       (value & AFE_ON_RETM_MASK_SFT) == 0,
				       20,
				       1 * 1000 * 1000);
	अगर (ret)
		dev_warn(afe->dev, "%s(), ret %d\n", __func__, ret);

	/* make sure all irq status are cleared */
	regmap_ग_लिखो(afe->regmap, AFE_IRQ_MCU_CLR, 0xffffffff);
	regmap_ग_लिखो(afe->regmap, AFE_IRQ_MCU_CLR, 0xffffffff);

	/* reset sgen */
	regmap_ग_लिखो(afe->regmap, AFE_SINEGEN_CON0, 0x0);
	regmap_update_bits(afe->regmap, AFE_SINEGEN_CON2,
			   INNER_LOOP_BACK_MODE_MASK_SFT,
			   0x3f << INNER_LOOP_BACK_MODE_SFT);

	/* cache only */
	regcache_cache_only(afe->regmap, true);
	regcache_mark_dirty(afe->regmap);

skip_regmap:
	mt8192_afe_disable_घड़ी(afe);
	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_afe_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	dev_info(afe->dev, "%s()\n", __func__);

	ret = mt8192_afe_enable_घड़ी(afe);
	अगर (ret)
		वापस ret;

	अगर (!afe->regmap || afe_priv->pm_runसमय_bypass_reg_ctl)
		जाओ skip_regmap;

	regcache_cache_only(afe->regmap, false);
	regcache_sync(afe->regmap);

	/* enable audio sys DCM क्रम घातer saving */
	regmap_update_bits(afe_priv->infracfg,
			   PERI_BUS_DCM_CTRL, 0x1 << 29, 0x1 << 29);
	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0, 0x1 << 29, 0x1 << 29);

	/* क्रमce cpu use 8_24 क्रमmat when writing 32bit data */
	regmap_update_bits(afe->regmap, AFE_MEMIF_CON0,
			   CPU_HD_ALIGN_MASK_SFT, 0 << CPU_HD_ALIGN_SFT);

	/* set all output port to 24bit */
	regmap_ग_लिखो(afe->regmap, AFE_CONN_24BIT, 0xffffffff);
	regmap_ग_लिखो(afe->regmap, AFE_CONN_24BIT_1, 0xffffffff);

	/* enable AFE */
	regmap_update_bits(afe->regmap, AFE_DAC_CON0, AFE_ON_MASK_SFT, 0x1);

skip_regmap:
	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_afe_component_probe(काष्ठा snd_soc_component *component)
अणु
	वापस mtk_afe_add_sub_dai_control(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mt8192_afe_component = अणु
	.name = AFE_PCM_NAME,
	.probe = mt8192_afe_component_probe,
	.poपूर्णांकer = mtk_afe_pcm_poपूर्णांकer,
	.pcm_स्थिरruct = mtk_afe_pcm_new,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mt8192_afe_pcm_component = अणु
	.name = "mt8192-afe-pcm-dai",
पूर्ण;

अटल पूर्णांक mt8192_dai_memअगर_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mt8192_memअगर_dai_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mt8192_memअगर_dai_driver);

	dai->dapm_widमाला_लो = mt8192_memअगर_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mt8192_memअगर_widमाला_लो);
	dai->dapm_routes = mt8192_memअगर_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mt8192_memअगर_routes);
	वापस 0;
पूर्ण

प्रकार पूर्णांक (*dai_रेजिस्टर_cb)(काष्ठा mtk_base_afe *);
अटल स्थिर dai_रेजिस्टर_cb dai_रेजिस्टर_cbs[] = अणु
	mt8192_dai_adda_रेजिस्टर,
	mt8192_dai_i2s_रेजिस्टर,
	mt8192_dai_pcm_रेजिस्टर,
	mt8192_dai_tdm_रेजिस्टर,
	mt8192_dai_memअगर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक mt8192_afe_pcm_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_base_afe *afe;
	काष्ठा mt8192_afe_निजी *afe_priv;
	काष्ठा device *dev;
	काष्ठा reset_control *rstc;
	पूर्णांक i, ret, irq_id;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(34));
	अगर (ret)
		वापस ret;

	afe = devm_kzalloc(&pdev->dev, माप(*afe), GFP_KERNEL);
	अगर (!afe)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, afe);

	afe->platक्रमm_priv = devm_kzalloc(&pdev->dev, माप(*afe_priv),
					  GFP_KERNEL);
	अगर (!afe->platक्रमm_priv)
		वापस -ENOMEM;
	afe_priv = afe->platक्रमm_priv;

	afe->dev = &pdev->dev;
	dev = afe->dev;

	/* init audio related घड़ी */
	ret = mt8192_init_घड़ी(afe);
	अगर (ret) अणु
		dev_err(dev, "init clock error\n");
		वापस ret;
	पूर्ण

	/* reset controller to reset audio regs beक्रमe regmap cache */
	rstc = devm_reset_control_get_exclusive(dev, "audiosys");
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		dev_err(dev, "could not get audiosys reset:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_reset(rstc);
	अगर (ret) अणु
		dev_err(dev, "failed to trigger audio reset:%d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev))
		जाओ err_pm_disable;

	/* regmap init */
	afe->regmap = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(afe->regmap)) अणु
		dev_err(dev, "could not get regmap from parent\n");
		वापस PTR_ERR(afe->regmap);
	पूर्ण
	ret = regmap_attach_dev(dev, afe->regmap, &mt8192_afe_regmap_config);
	अगर (ret) अणु
		dev_warn(dev, "regmap_attach_dev fail, ret %d\n", ret);
		वापस ret;
	पूर्ण

	/* enable घड़ी क्रम regcache get शेष value from hw */
	afe_priv->pm_runसमय_bypass_reg_ctl = true;
	pm_runसमय_get_sync(&pdev->dev);

	ret = regmap_reinit_cache(afe->regmap, &mt8192_afe_regmap_config);
	अगर (ret) अणु
		dev_err(dev, "regmap_reinit_cache fail, ret %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_put_sync(&pdev->dev);
	afe_priv->pm_runसमय_bypass_reg_ctl = false;

	regcache_cache_only(afe->regmap, true);
	regcache_mark_dirty(afe->regmap);

	/* init memअगर */
	afe->memअगर_size = MT8192_MEMIF_NUM;
	afe->memअगर = devm_kसुस्मृति(dev, afe->memअगर_size, माप(*afe->memअगर),
				  GFP_KERNEL);
	अगर (!afe->memअगर)
		वापस -ENOMEM;

	क्रम (i = 0; i < afe->memअगर_size; i++) अणु
		afe->memअगर[i].data = &memअगर_data[i];
		afe->memअगर[i].irq_usage = memअगर_irq_usage[i];
		afe->memअगर[i].स्थिर_irq = 1;
	पूर्ण

	mutex_init(&afe->irq_alloc_lock);	/* needed when dynamic irq */

	/* init irq */
	afe->irqs_size = MT8192_IRQ_NUM;
	afe->irqs = devm_kसुस्मृति(dev, afe->irqs_size, माप(*afe->irqs),
				 GFP_KERNEL);
	अगर (!afe->irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < afe->irqs_size; i++)
		afe->irqs[i].irq_data = &irq_data[i];

	/* request irq */
	irq_id = platक्रमm_get_irq(pdev, 0);
	अगर (irq_id < 0)
		वापस irq_id;

	ret = devm_request_irq(dev, irq_id, mt8192_afe_irq_handler,
			       IRQF_TRIGGER_NONE, "asys-isr", (व्योम *)afe);
	अगर (ret) अणु
		dev_err(dev, "could not request_irq for Afe_ISR_Handle\n");
		वापस ret;
	पूर्ण

	/* init sub_dais */
	INIT_LIST_HEAD(&afe->sub_dais);

	क्रम (i = 0; i < ARRAY_SIZE(dai_रेजिस्टर_cbs); i++) अणु
		ret = dai_रेजिस्टर_cbs[i](afe);
		अगर (ret) अणु
			dev_warn(afe->dev, "dai register i %d fail, ret %d\n",
				 i, ret);
			जाओ err_pm_disable;
		पूर्ण
	पूर्ण

	/* init dai_driver and component_driver */
	ret = mtk_afe_combine_sub_dai(afe);
	अगर (ret) अणु
		dev_warn(afe->dev, "mtk_afe_combine_sub_dai fail, ret %d\n",
			 ret);
		जाओ err_pm_disable;
	पूर्ण

	/* others */
	afe->mtk_afe_hardware = &mt8192_afe_hardware;
	afe->memअगर_fs = mt8192_memअगर_fs;
	afe->irq_fs = mt8192_irq_fs;
	afe->get_dai_fs = mt8192_get_dai_fs;
	afe->get_memअगर_pbuf_size = mt8192_get_memअगर_pbuf_size;
	afe->memअगर_32bit_supported = 1;

	afe->runसमय_resume = mt8192_afe_runसमय_resume;
	afe->runसमय_suspend = mt8192_afe_runसमय_suspend;

	/* रेजिस्टर platक्रमm */
	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mt8192_afe_component, शून्य, 0);
	अगर (ret) अणु
		dev_warn(dev, "err_platform\n");
		जाओ err_pm_disable;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mt8192_afe_pcm_component,
					      afe->dai_drivers,
					      afe->num_dai_drivers);
	अगर (ret) अणु
		dev_warn(dev, "err_dai_component\n");
		जाओ err_pm_disable;
	पूर्ण

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mt8192_afe_pcm_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_base_afe *afe = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		mt8192_afe_runसमय_suspend(&pdev->dev);

	/* disable afe घड़ी */
	mt8192_afe_disable_घड़ी(afe);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt8192_afe_pcm_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8192-audio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt8192_afe_pcm_dt_match);

अटल स्थिर काष्ठा dev_pm_ops mt8192_afe_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mt8192_afe_runसमय_suspend,
			   mt8192_afe_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mt8192_afe_pcm_driver = अणु
	.driver = अणु
		   .name = "mt8192-audio",
		   .of_match_table = mt8192_afe_pcm_dt_match,
#अगर_घोषित CONFIG_PM
		   .pm = &mt8192_afe_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt8192_afe_pcm_dev_probe,
	.हटाओ = mt8192_afe_pcm_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(mt8192_afe_pcm_driver);

MODULE_DESCRIPTION("Mediatek ALSA SoC AFE platform driver for 8192");
MODULE_AUTHOR("Shane Chien <shane.chien@mediatek.com>");
MODULE_LICENSE("GPL v2");
