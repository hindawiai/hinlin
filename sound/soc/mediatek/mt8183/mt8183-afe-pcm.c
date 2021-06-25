<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Mediatek ALSA SoC AFE platक्रमm driver क्रम 8183
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश "mt8183-afe-common.h"
#समावेश "mt8183-afe-clk.h"
#समावेश "mt8183-interconnection.h"
#समावेश "mt8183-reg.h"
#समावेश "../common/mtk-afe-platform-driver.h"
#समावेश "../common/mtk-afe-fe-dai.h"

क्रमागत अणु
	MTK_AFE_RATE_8K = 0,
	MTK_AFE_RATE_11K = 1,
	MTK_AFE_RATE_12K = 2,
	MTK_AFE_RATE_384K = 3,
	MTK_AFE_RATE_16K = 4,
	MTK_AFE_RATE_22K = 5,
	MTK_AFE_RATE_24K = 6,
	MTK_AFE_RATE_130K = 7,
	MTK_AFE_RATE_32K = 8,
	MTK_AFE_RATE_44K = 9,
	MTK_AFE_RATE_48K = 10,
	MTK_AFE_RATE_88K = 11,
	MTK_AFE_RATE_96K = 12,
	MTK_AFE_RATE_176K = 13,
	MTK_AFE_RATE_192K = 14,
	MTK_AFE_RATE_260K = 15,
पूर्ण;

क्रमागत अणु
	MTK_AFE_DAI_MEMIF_RATE_8K = 0,
	MTK_AFE_DAI_MEMIF_RATE_16K = 1,
	MTK_AFE_DAI_MEMIF_RATE_32K = 2,
	MTK_AFE_DAI_MEMIF_RATE_48K = 3,
पूर्ण;

क्रमागत अणु
	MTK_AFE_PCM_RATE_8K = 0,
	MTK_AFE_PCM_RATE_16K = 1,
	MTK_AFE_PCM_RATE_32K = 2,
	MTK_AFE_PCM_RATE_48K = 3,
पूर्ण;

अचिन्हित पूर्णांक mt8183_general_rate_transक्रमm(काष्ठा device *dev,
					   अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_RATE_8K;
	हाल 11025:
		वापस MTK_AFE_RATE_11K;
	हाल 12000:
		वापस MTK_AFE_RATE_12K;
	हाल 16000:
		वापस MTK_AFE_RATE_16K;
	हाल 22050:
		वापस MTK_AFE_RATE_22K;
	हाल 24000:
		वापस MTK_AFE_RATE_24K;
	हाल 32000:
		वापस MTK_AFE_RATE_32K;
	हाल 44100:
		वापस MTK_AFE_RATE_44K;
	हाल 48000:
		वापस MTK_AFE_RATE_48K;
	हाल 88200:
		वापस MTK_AFE_RATE_88K;
	हाल 96000:
		वापस MTK_AFE_RATE_96K;
	हाल 130000:
		वापस MTK_AFE_RATE_130K;
	हाल 176400:
		वापस MTK_AFE_RATE_176K;
	हाल 192000:
		वापस MTK_AFE_RATE_192K;
	हाल 260000:
		वापस MTK_AFE_RATE_260K;
	शेष:
		dev_warn(dev, "%s(), rate %u invalid, use %d!!!\n",
			 __func__, rate, MTK_AFE_RATE_48K);
		वापस MTK_AFE_RATE_48K;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक dai_memअगर_rate_transक्रमm(काष्ठा device *dev,
					     अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_DAI_MEMIF_RATE_8K;
	हाल 16000:
		वापस MTK_AFE_DAI_MEMIF_RATE_16K;
	हाल 32000:
		वापस MTK_AFE_DAI_MEMIF_RATE_32K;
	हाल 48000:
		वापस MTK_AFE_DAI_MEMIF_RATE_48K;
	शेष:
		dev_warn(dev, "%s(), rate %u invalid, use %d!!!\n",
			 __func__, rate, MTK_AFE_DAI_MEMIF_RATE_16K);
		वापस MTK_AFE_DAI_MEMIF_RATE_16K;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक mt8183_rate_transक्रमm(काष्ठा device *dev,
				   अचिन्हित पूर्णांक rate, पूर्णांक aud_blk)
अणु
	चयन (aud_blk) अणु
	हाल MT8183_MEMIF_MOD_DAI:
		वापस dai_memअगर_rate_transक्रमm(dev, rate);
	शेष:
		वापस mt8183_general_rate_transक्रमm(dev, rate);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware mt8183_afe_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		   SNDRV_PCM_FMTBIT_S24_LE |
		   SNDRV_PCM_FMTBIT_S32_LE,
	.period_bytes_min = 256,
	.period_bytes_max = 4 * 48 * 1024,
	.periods_min = 2,
	.periods_max = 256,
	.buffer_bytes_max = 8 * 48 * 1024,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक mt8183_memअगर_fs(काष्ठा snd_pcm_substream *substream,
			   अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	पूर्णांक id = asoc_rtd_to_cpu(rtd, 0)->id;

	वापस mt8183_rate_transक्रमm(afe->dev, rate, id);
पूर्ण

अटल पूर्णांक mt8183_irq_fs(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);

	वापस mt8183_general_rate_transक्रमm(afe->dev, rate);
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

अटल काष्ठा snd_soc_dai_driver mt8183_memअगर_dai_driver[] = अणु
	/* FE DAIs: memory पूर्णांकefaces to CPU */
	अणु
		.name = "DL1",
		.id = MT8183_MEMIF_DL1,
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
		.name = "DL2",
		.id = MT8183_MEMIF_DL2,
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
		.id = MT8183_MEMIF_DL3,
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
		.name = "UL1",
		.id = MT8183_MEMIF_VUL12,
		.capture = अणु
			.stream_name = "UL1",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_PCM_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "UL2",
		.id = MT8183_MEMIF_AWB,
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
		.id = MT8183_MEMIF_VUL2,
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
		.id = MT8183_MEMIF_AWB2,
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
		.name = "UL_MONO_1",
		.id = MT8183_MEMIF_MOD_DAI,
		.capture = अणु
			.stream_name = "UL_MONO_1",
			.channels_min = 1,
			.channels_max = 1,
			.rates = MTK_PCM_DAI_RATES,
			.क्रमmats = MTK_PCM_FORMATS,
		पूर्ण,
		.ops = &mtk_afe_fe_ops,
	पूर्ण,
	अणु
		.name = "HDMI",
		.id = MT8183_MEMIF_HDMI,
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

/* dma widget & routes*/
अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul1_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN21,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S0_CH1", AFE_CONN21,
				    I_I2S0_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul1_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN22,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S0_CH2", AFE_CONN21,
				    I_I2S0_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul2_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN5,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN5,
				    I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN5,
				    I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN5,
				    I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S2_CH1", AFE_CONN5,
				    I_I2S2_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul2_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN6,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN6,
				    I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN6,
				    I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN6,
				    I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S2_CH2", AFE_CONN6,
				    I_I2S2_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul3_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN32,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S2_CH1", AFE_CONN32,
				    I_I2S2_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul3_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN33,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("I2S2_CH2", AFE_CONN33,
				    I_I2S2_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul4_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN38,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul4_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN39,
				    I_ADDA_UL_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new memअगर_ul_mono_1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN12,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN12,
				    I_ADDA_UL_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mt8183_memअगर_widमाला_लो[] = अणु
	/* memअगर */
	SND_SOC_DAPM_MIXER("UL1_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul1_ch1_mix, ARRAY_SIZE(memअगर_ul1_ch1_mix)),
	SND_SOC_DAPM_MIXER("UL1_CH2", SND_SOC_NOPM, 0, 0,
			   memअगर_ul1_ch2_mix, ARRAY_SIZE(memअगर_ul1_ch2_mix)),

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

	SND_SOC_DAPM_MIXER("UL_MONO_1_CH1", SND_SOC_NOPM, 0, 0,
			   memअगर_ul_mono_1_mix,
			   ARRAY_SIZE(memअगर_ul_mono_1_mix)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8183_memअगर_routes[] = अणु
	/* capture */
	अणु"UL1", शून्य, "UL1_CH1"पूर्ण,
	अणु"UL1", शून्य, "UL1_CH2"पूर्ण,
	अणु"UL1_CH1", "ADDA_UL_CH1", "ADDA Capture"पूर्ण,
	अणु"UL1_CH2", "ADDA_UL_CH2", "ADDA Capture"पूर्ण,
	अणु"UL1_CH1", "I2S0_CH1", "I2S0"पूर्ण,
	अणु"UL1_CH2", "I2S0_CH2", "I2S0"पूर्ण,

	अणु"UL2", शून्य, "UL2_CH1"पूर्ण,
	अणु"UL2", शून्य, "UL2_CH2"पूर्ण,
	अणु"UL2_CH1", "ADDA_UL_CH1", "ADDA Capture"पूर्ण,
	अणु"UL2_CH2", "ADDA_UL_CH2", "ADDA Capture"पूर्ण,
	अणु"UL2_CH1", "I2S2_CH1", "I2S2"पूर्ण,
	अणु"UL2_CH2", "I2S2_CH2", "I2S2"पूर्ण,

	अणु"UL3", शून्य, "UL3_CH1"पूर्ण,
	अणु"UL3", शून्य, "UL3_CH2"पूर्ण,
	अणु"UL3_CH1", "ADDA_UL_CH1", "ADDA Capture"पूर्ण,
	अणु"UL3_CH2", "ADDA_UL_CH2", "ADDA Capture"पूर्ण,
	अणु"UL3_CH1", "I2S2_CH1", "I2S2"पूर्ण,
	अणु"UL3_CH2", "I2S2_CH2", "I2S2"पूर्ण,

	अणु"UL4", शून्य, "UL4_CH1"पूर्ण,
	अणु"UL4", शून्य, "UL4_CH2"पूर्ण,
	अणु"UL4_CH1", "ADDA_UL_CH1", "ADDA Capture"पूर्ण,
	अणु"UL4_CH2", "ADDA_UL_CH2", "ADDA Capture"पूर्ण,

	अणु"UL_MONO_1", शून्य, "UL_MONO_1_CH1"पूर्ण,
	अणु"UL_MONO_1_CH1", "ADDA_UL_CH1", "ADDA Capture"पूर्ण,
	अणु"UL_MONO_1_CH1", "ADDA_UL_CH2", "ADDA Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mt8183_afe_pcm_dai_component = अणु
	.name = "mt8183-afe-pcm-dai",
पूर्ण;

अटल स्थिर काष्ठा mtk_base_memअगर_data memअगर_data[MT8183_MEMIF_NUM] = अणु
	[MT8183_MEMIF_DL1] = अणु
		.name = "DL1",
		.id = MT8183_MEMIF_DL1,
		.reg_ofs_base = AFE_DL1_BASE,
		.reg_ofs_cur = AFE_DL1_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = DL1_MODE_SFT,
		.fs_maskbit = DL1_MODE_MASK,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = DL1_DATA_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL1_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = DL1_HD_SFT,
		.hd_align_mshअगरt = DL1_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_DL2] = अणु
		.name = "DL2",
		.id = MT8183_MEMIF_DL2,
		.reg_ofs_base = AFE_DL2_BASE,
		.reg_ofs_cur = AFE_DL2_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = DL2_MODE_SFT,
		.fs_maskbit = DL2_MODE_MASK,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = DL2_DATA_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL2_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = DL2_HD_SFT,
		.hd_align_mshअगरt = DL2_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_DL3] = अणु
		.name = "DL3",
		.id = MT8183_MEMIF_DL3,
		.reg_ofs_base = AFE_DL3_BASE,
		.reg_ofs_cur = AFE_DL3_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = DL3_MODE_SFT,
		.fs_maskbit = DL3_MODE_MASK,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = DL3_DATA_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = DL3_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = DL3_HD_SFT,
		.hd_align_mshअगरt = DL3_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_VUL2] = अणु
		.name = "VUL2",
		.id = MT8183_MEMIF_VUL2,
		.reg_ofs_base = AFE_VUL2_BASE,
		.reg_ofs_cur = AFE_VUL2_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = VUL2_MODE_SFT,
		.fs_maskbit = VUL2_MODE_MASK,
		.mono_reg = AFE_DAC_CON2,
		.mono_shअगरt = VUL2_DATA_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL2_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = VUL2_HD_SFT,
		.hd_align_mshअगरt = VUL2_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_AWB] = अणु
		.name = "AWB",
		.id = MT8183_MEMIF_AWB,
		.reg_ofs_base = AFE_AWB_BASE,
		.reg_ofs_cur = AFE_AWB_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = AWB_MODE_SFT,
		.fs_maskbit = AWB_MODE_MASK,
		.mono_reg = AFE_DAC_CON1,
		.mono_shअगरt = AWB_DATA_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = AWB_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = AWB_HD_SFT,
		.hd_align_mshअगरt = AWB_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_AWB2] = अणु
		.name = "AWB2",
		.id = MT8183_MEMIF_AWB2,
		.reg_ofs_base = AFE_AWB2_BASE,
		.reg_ofs_cur = AFE_AWB2_CUR,
		.fs_reg = AFE_DAC_CON2,
		.fs_shअगरt = AWB2_MODE_SFT,
		.fs_maskbit = AWB2_MODE_MASK,
		.mono_reg = AFE_DAC_CON2,
		.mono_shअगरt = AWB2_DATA_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = AWB2_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = AWB2_HD_SFT,
		.hd_align_mshअगरt = AWB2_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_VUL12] = अणु
		.name = "VUL12",
		.id = MT8183_MEMIF_VUL12,
		.reg_ofs_base = AFE_VUL_D2_BASE,
		.reg_ofs_cur = AFE_VUL_D2_CUR,
		.fs_reg = AFE_DAC_CON0,
		.fs_shअगरt = VUL12_MODE_SFT,
		.fs_maskbit = VUL12_MODE_MASK,
		.mono_reg = AFE_DAC_CON0,
		.mono_shअगरt = VUL12_MONO_SFT,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = VUL12_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = VUL12_HD_SFT,
		.hd_align_mshअगरt = VUL12_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_MOD_DAI] = अणु
		.name = "MOD_DAI",
		.id = MT8183_MEMIF_MOD_DAI,
		.reg_ofs_base = AFE_MOD_DAI_BASE,
		.reg_ofs_cur = AFE_MOD_DAI_CUR,
		.fs_reg = AFE_DAC_CON1,
		.fs_shअगरt = MOD_DAI_MODE_SFT,
		.fs_maskbit = MOD_DAI_MODE_MASK,
		.mono_reg = -1,
		.mono_shअगरt = 0,
		.enable_reg = AFE_DAC_CON0,
		.enable_shअगरt = MOD_DAI_ON_SFT,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = MOD_DAI_HD_SFT,
		.hd_align_mshअगरt = MOD_DAI_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
	[MT8183_MEMIF_HDMI] = अणु
		.name = "HDMI",
		.id = MT8183_MEMIF_HDMI,
		.reg_ofs_base = AFE_HDMI_OUT_BASE,
		.reg_ofs_cur = AFE_HDMI_OUT_CUR,
		.fs_reg = -1,
		.fs_shअगरt = -1,
		.fs_maskbit = -1,
		.mono_reg = -1,
		.mono_shअगरt = -1,
		.enable_reg = -1,	/* control in tdm क्रम sync start */
		.enable_shअगरt = -1,
		.hd_reg = AFE_MEMIF_HD_MODE,
		.hd_align_reg = AFE_MEMIF_HDALIGN,
		.hd_shअगरt = HDMI_HD_SFT,
		.hd_align_mshअगरt = HDMI_HD_ALIGN_SFT,
		.agent_disable_reg = -1,
		.agent_disable_shअगरt = -1,
		.msb_reg = -1,
		.msb_shअगरt = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_base_irq_data irq_data[MT8183_IRQ_NUM] = अणु
	[MT8183_IRQ_0] = अणु
		.id = MT8183_IRQ_0,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT0,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ0_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ0_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ0_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ0_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_1] = अणु
		.id = MT8183_IRQ_1,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT1,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ1_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ1_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ1_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ1_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_2] = अणु
		.id = MT8183_IRQ_2,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT2,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ2_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ2_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ2_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ2_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_3] = अणु
		.id = MT8183_IRQ_3,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT3,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ3_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ3_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ3_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ3_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_4] = अणु
		.id = MT8183_IRQ_4,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT4,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ4_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ4_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ4_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ4_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_5] = अणु
		.id = MT8183_IRQ_5,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT5,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ5_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ5_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ5_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ5_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_6] = अणु
		.id = MT8183_IRQ_6,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT6,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ6_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ6_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ6_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ6_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_7] = अणु
		.id = MT8183_IRQ_7,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT7,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON1,
		.irq_fs_shअगरt = IRQ7_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ7_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ7_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ7_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_8] = अणु
		.id = MT8183_IRQ_8,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT8,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = -1,
		.irq_fs_shअगरt = -1,
		.irq_fs_maskbit = -1,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ8_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ8_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_11] = अणु
		.id = MT8183_IRQ_11,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT11,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ11_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ11_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ11_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ11_MCU_CLR_SFT,
	पूर्ण,
	[MT8183_IRQ_12] = अणु
		.id = MT8183_IRQ_12,
		.irq_cnt_reg = AFE_IRQ_MCU_CNT12,
		.irq_cnt_shअगरt = 0,
		.irq_cnt_maskbit = 0x3ffff,
		.irq_fs_reg = AFE_IRQ_MCU_CON2,
		.irq_fs_shअगरt = IRQ12_MCU_MODE_SFT,
		.irq_fs_maskbit = IRQ12_MCU_MODE_MASK,
		.irq_en_reg = AFE_IRQ_MCU_CON0,
		.irq_en_shअगरt = IRQ12_MCU_ON_SFT,
		.irq_clr_reg = AFE_IRQ_MCU_CLR,
		.irq_clr_shअगरt = IRQ12_MCU_CLR_SFT,
	पूर्ण,
पूर्ण;

अटल bool mt8183_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* these स्वतः-gen reg has पढ़ो-only bit, so put it as अस्थिर */
	/* अस्थिर reg cannot be cached, so cannot be set when घातer off */
	चयन (reg) अणु
	हाल AUDIO_TOP_CON0:	/* reg bit controlled by CCF */
	हाल AUDIO_TOP_CON1:	/* reg bit controlled by CCF */
	हाल AUDIO_TOP_CON3:
	हाल AFE_DL1_CUR:
	हाल AFE_DL1_END:
	हाल AFE_DL2_CUR:
	हाल AFE_DL2_END:
	हाल AFE_AWB_END:
	हाल AFE_AWB_CUR:
	हाल AFE_VUL_END:
	हाल AFE_VUL_CUR:
	हाल AFE_MEMIF_MON0:
	हाल AFE_MEMIF_MON1:
	हाल AFE_MEMIF_MON2:
	हाल AFE_MEMIF_MON3:
	हाल AFE_MEMIF_MON4:
	हाल AFE_MEMIF_MON5:
	हाल AFE_MEMIF_MON6:
	हाल AFE_MEMIF_MON7:
	हाल AFE_MEMIF_MON8:
	हाल AFE_MEMIF_MON9:
	हाल AFE_ADDA_SRC_DEBUG_MON0:
	हाल AFE_ADDA_SRC_DEBUG_MON1:
	हाल AFE_ADDA_UL_SRC_MON0:
	हाल AFE_ADDA_UL_SRC_MON1:
	हाल AFE_SIDETONE_MON:
	हाल AFE_SIDETONE_CON0:
	हाल AFE_SIDETONE_COEFF:
	हाल AFE_BUS_MON0:
	हाल AFE_MRGIF_MON0:
	हाल AFE_MRGIF_MON1:
	हाल AFE_MRGIF_MON2:
	हाल AFE_I2S_MON:
	हाल AFE_DAC_MON:
	हाल AFE_VUL2_END:
	हाल AFE_VUL2_CUR:
	हाल AFE_IRQ0_MCU_CNT_MON:
	हाल AFE_IRQ6_MCU_CNT_MON:
	हाल AFE_MOD_DAI_END:
	हाल AFE_MOD_DAI_CUR:
	हाल AFE_VUL_D2_END:
	हाल AFE_VUL_D2_CUR:
	हाल AFE_DL3_CUR:
	हाल AFE_DL3_END:
	हाल AFE_HDMI_OUT_CON0:
	हाल AFE_HDMI_OUT_CUR:
	हाल AFE_HDMI_OUT_END:
	हाल AFE_IRQ3_MCU_CNT_MON:
	हाल AFE_IRQ4_MCU_CNT_MON:
	हाल AFE_IRQ_MCU_STATUS:
	हाल AFE_IRQ_MCU_CLR:
	हाल AFE_IRQ_MCU_MON2:
	हाल AFE_IRQ1_MCU_CNT_MON:
	हाल AFE_IRQ2_MCU_CNT_MON:
	हाल AFE_IRQ1_MCU_EN_CNT_MON:
	हाल AFE_IRQ5_MCU_CNT_MON:
	हाल AFE_IRQ7_MCU_CNT_MON:
	हाल AFE_GAIN1_CUR:
	हाल AFE_GAIN2_CUR:
	हाल AFE_SRAM_DELSEL_CON0:
	हाल AFE_SRAM_DELSEL_CON2:
	हाल AFE_SRAM_DELSEL_CON3:
	हाल AFE_ASRC_2CH_CON12:
	हाल AFE_ASRC_2CH_CON13:
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
	हाल AFE_CBIP_MON0:
	हाल AFE_CBIP_SLV_MUX_MON0:
	हाल AFE_CBIP_SLV_DECODER_MON0:
	हाल AFE_ADDA6_SRC_DEBUG_MON0:
	हाल AFE_ADD6A_UL_SRC_MON0:
	हाल AFE_ADDA6_UL_SRC_MON1:
	हाल AFE_DL1_CUR_MSB:
	हाल AFE_DL2_CUR_MSB:
	हाल AFE_AWB_CUR_MSB:
	हाल AFE_VUL_CUR_MSB:
	हाल AFE_VUL2_CUR_MSB:
	हाल AFE_MOD_DAI_CUR_MSB:
	हाल AFE_VUL_D2_CUR_MSB:
	हाल AFE_DL3_CUR_MSB:
	हाल AFE_HDMI_OUT_CUR_MSB:
	हाल AFE_AWB2_END:
	हाल AFE_AWB2_CUR:
	हाल AFE_AWB2_CUR_MSB:
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
	हाल AFE_MEMIF_MON12:
	हाल AFE_MEMIF_MON13:
	हाल AFE_MEMIF_MON14:
	हाल AFE_MEMIF_MON15:
	हाल AFE_MEMIF_MON16:
	हाल AFE_MEMIF_MON17:
	हाल AFE_MEMIF_MON18:
	हाल AFE_MEMIF_MON19:
	हाल AFE_MEMIF_MON20:
	हाल AFE_MEMIF_MON21:
	हाल AFE_MEMIF_MON22:
	हाल AFE_MEMIF_MON23:
	हाल AFE_MEMIF_MON24:
	हाल AFE_ADDA_MTKAIF_MON0:
	हाल AFE_ADDA_MTKAIF_MON1:
	हाल AFE_AUD_PAD_TOP:
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
		वापस true;
	शेष:
		वापस false;
	पूर्ण;
पूर्ण

अटल स्थिर काष्ठा regmap_config mt8183_afe_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.अस्थिर_reg = mt8183_is_अस्थिर_reg,

	.max_रेजिस्टर = AFE_MAX_REGISTER,
	.num_reg_शेषs_raw = AFE_MAX_REGISTER,

	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल irqवापस_t mt8183_afe_irq_handler(पूर्णांक irq_id, व्योम *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev;
	काष्ठा mtk_base_afe_irq *irq;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक status_mcu;
	अचिन्हित पूर्णांक mcu_en;
	पूर्णांक ret;
	पूर्णांक i;
	irqवापस_t irq_ret = IRQ_HANDLED;

	/* get irq that is sent to MCU */
	regmap_पढ़ो(afe->regmap, AFE_IRQ_MCU_EN, &mcu_en);

	ret = regmap_पढ़ो(afe->regmap, AFE_IRQ_MCU_STATUS, &status);
	/* only care IRQ which is sent to MCU */
	status_mcu = status & mcu_en & AFE_IRQ_STATUS_BITS;

	अगर (ret || status_mcu == 0) अणु
		dev_err(afe->dev, "%s(), irq status err, ret %d, status 0x%x, mcu_en 0x%x\n",
			__func__, ret, status, mcu_en);

		irq_ret = IRQ_NONE;
		जाओ err_irq;
	पूर्ण

	क्रम (i = 0; i < MT8183_MEMIF_NUM; i++) अणु
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

	वापस irq_ret;
पूर्ण

अटल पूर्णांक mt8183_afe_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

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

	/* make sure all irq status are cleared, twice पूर्णांकended */
	regmap_update_bits(afe->regmap, AFE_IRQ_MCU_CLR, 0xffff, 0xffff);
	regmap_update_bits(afe->regmap, AFE_IRQ_MCU_CLR, 0xffff, 0xffff);

	/* cache only */
	regcache_cache_only(afe->regmap, true);
	regcache_mark_dirty(afe->regmap);

skip_regmap:
	वापस mt8183_afe_disable_घड़ी(afe);
पूर्ण

अटल पूर्णांक mt8183_afe_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_base_afe *afe = dev_get_drvdata(dev);
	काष्ठा mt8183_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक ret;

	ret = mt8183_afe_enable_घड़ी(afe);
	अगर (ret)
		वापस ret;

	अगर (!afe->regmap || afe_priv->pm_runसमय_bypass_reg_ctl)
		जाओ skip_regmap;

	regcache_cache_only(afe->regmap, false);
	regcache_sync(afe->regmap);

	/* enable audio sys DCM क्रम घातer saving */
	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0, 0x1 << 29, 0x1 << 29);

	/* क्रमce cpu use 8_24 क्रमmat when writing 32bit data */
	regmap_update_bits(afe->regmap, AFE_MEMIF_MSB,
			   CPU_HD_ALIGN_MASK_SFT, 0 << CPU_HD_ALIGN_SFT);

	/* set all output port to 24bit */
	regmap_ग_लिखो(afe->regmap, AFE_CONN_24BIT, 0xffffffff);
	regmap_ग_लिखो(afe->regmap, AFE_CONN_24BIT_1, 0xffffffff);

	/* enable AFE */
	regmap_update_bits(afe->regmap, AFE_DAC_CON0, 0x1, 0x1);

skip_regmap:
	वापस 0;
पूर्ण

अटल पूर्णांक mt8183_afe_component_probe(काष्ठा snd_soc_component *component)
अणु
	वापस mtk_afe_add_sub_dai_control(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mt8183_afe_component = अणु
	.name		= AFE_PCM_NAME,
	.probe		= mt8183_afe_component_probe,
	.poपूर्णांकer	= mtk_afe_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= mtk_afe_pcm_new,
पूर्ण;

अटल पूर्णांक mt8183_dai_memअगर_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mt8183_memअगर_dai_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mt8183_memअगर_dai_driver);

	dai->dapm_widमाला_लो = mt8183_memअगर_widमाला_लो;
	dai->num_dapm_widमाला_लो = ARRAY_SIZE(mt8183_memअगर_widमाला_लो);
	dai->dapm_routes = mt8183_memअगर_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mt8183_memअगर_routes);
	वापस 0;
पूर्ण

प्रकार पूर्णांक (*dai_रेजिस्टर_cb)(काष्ठा mtk_base_afe *);
अटल स्थिर dai_रेजिस्टर_cb dai_रेजिस्टर_cbs[] = अणु
	mt8183_dai_adda_रेजिस्टर,
	mt8183_dai_i2s_रेजिस्टर,
	mt8183_dai_pcm_रेजिस्टर,
	mt8183_dai_tdm_रेजिस्टर,
	mt8183_dai_hostless_रेजिस्टर,
	mt8183_dai_memअगर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक mt8183_afe_pcm_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_base_afe *afe;
	काष्ठा mt8183_afe_निजी *afe_priv;
	काष्ठा device *dev;
	काष्ठा reset_control *rstc;
	पूर्णांक i, irq_id, ret;

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

	/* initial audio related घड़ी */
	ret = mt8183_init_घड़ी(afe);
	अगर (ret) अणु
		dev_err(dev, "init clock error\n");
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

	/* regmap init */
	afe->regmap = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(afe->regmap)) अणु
		dev_err(dev, "could not get regmap from parent\n");
		वापस PTR_ERR(afe->regmap);
	पूर्ण
	ret = regmap_attach_dev(dev, afe->regmap, &mt8183_afe_regmap_config);
	अगर (ret) अणु
		dev_warn(dev, "regmap_attach_dev fail, ret %d\n", ret);
		वापस ret;
	पूर्ण

	rstc = devm_reset_control_get(dev, "audiosys");
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

	/* enable घड़ी क्रम regcache get शेष value from hw */
	afe_priv->pm_runसमय_bypass_reg_ctl = true;
	pm_runसमय_get_sync(&pdev->dev);

	ret = regmap_reinit_cache(afe->regmap, &mt8183_afe_regmap_config);
	अगर (ret) अणु
		dev_err(dev, "regmap_reinit_cache fail, ret %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_put_sync(&pdev->dev);
	afe_priv->pm_runसमय_bypass_reg_ctl = false;

	regcache_cache_only(afe->regmap, true);
	regcache_mark_dirty(afe->regmap);

	/* init memअगर */
	afe->memअगर_size = MT8183_MEMIF_NUM;
	afe->memअगर = devm_kसुस्मृति(dev, afe->memअगर_size, माप(*afe->memअगर),
				  GFP_KERNEL);
	अगर (!afe->memअगर)
		वापस -ENOMEM;

	क्रम (i = 0; i < afe->memअगर_size; i++) अणु
		afe->memअगर[i].data = &memअगर_data[i];
		afe->memअगर[i].irq_usage = -1;
	पूर्ण

	afe->memअगर[MT8183_MEMIF_HDMI].irq_usage = MT8183_IRQ_8;
	afe->memअगर[MT8183_MEMIF_HDMI].स्थिर_irq = 1;

	mutex_init(&afe->irq_alloc_lock);

	/* init memअगर */
	/* irq initialize */
	afe->irqs_size = MT8183_IRQ_NUM;
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

	ret = devm_request_irq(dev, irq_id, mt8183_afe_irq_handler,
			       IRQF_TRIGGER_NONE, "asys-isr", (व्योम *)afe);
	अगर (ret) अणु
		dev_err(dev, "could not request_irq for asys-isr\n");
		वापस ret;
	पूर्ण

	/* init sub_dais */
	INIT_LIST_HEAD(&afe->sub_dais);

	क्रम (i = 0; i < ARRAY_SIZE(dai_रेजिस्टर_cbs); i++) अणु
		ret = dai_रेजिस्टर_cbs[i](afe);
		अगर (ret) अणु
			dev_warn(afe->dev, "dai register i %d fail, ret %d\n",
				 i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* init dai_driver and component_driver */
	ret = mtk_afe_combine_sub_dai(afe);
	अगर (ret) अणु
		dev_warn(afe->dev, "mtk_afe_combine_sub_dai fail, ret %d\n",
			 ret);
		वापस ret;
	पूर्ण

	afe->mtk_afe_hardware = &mt8183_afe_hardware;
	afe->memअगर_fs = mt8183_memअगर_fs;
	afe->irq_fs = mt8183_irq_fs;

	afe->runसमय_resume = mt8183_afe_runसमय_resume;
	afe->runसमय_suspend = mt8183_afe_runसमय_suspend;

	/* रेजिस्टर component */
	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mt8183_afe_component,
					      शून्य, 0);
	अगर (ret) अणु
		dev_warn(dev, "err_platform\n");
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(afe->dev,
					      &mt8183_afe_pcm_dai_component,
					      afe->dai_drivers,
					      afe->num_dai_drivers);
	अगर (ret) अणु
		dev_warn(dev, "err_dai_component\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt8183_afe_pcm_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		mt8183_afe_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt8183_afe_pcm_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8183-audio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt8183_afe_pcm_dt_match);

अटल स्थिर काष्ठा dev_pm_ops mt8183_afe_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mt8183_afe_runसमय_suspend,
			   mt8183_afe_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mt8183_afe_pcm_driver = अणु
	.driver = अणु
		   .name = "mt8183-audio",
		   .of_match_table = mt8183_afe_pcm_dt_match,
#अगर_घोषित CONFIG_PM
		   .pm = &mt8183_afe_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt8183_afe_pcm_dev_probe,
	.हटाओ = mt8183_afe_pcm_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(mt8183_afe_pcm_driver);

MODULE_DESCRIPTION("Mediatek ALSA SoC AFE platform driver for 8183");
MODULE_AUTHOR("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODULE_LICENSE("GPL v2");
