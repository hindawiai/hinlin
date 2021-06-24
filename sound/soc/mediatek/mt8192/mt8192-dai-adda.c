<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio DAI ADDA Control
//
// Copyright (c) 2020 MediaTek Inc.
// Author: Shane Chien <shane.chien@mediatek.com>
//

#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>

#समावेश "mt8192-afe-clk.h"
#समावेश "mt8192-afe-common.h"
#समावेश "mt8192-afe-gpio.h"
#समावेश "mt8192-interconnection.h"

क्रमागत अणु
	UL_IIR_SW = 0,
	UL_IIR_5HZ,
	UL_IIR_10HZ,
	UL_IIR_25HZ,
	UL_IIR_50HZ,
	UL_IIR_75HZ,
पूर्ण;

क्रमागत अणु
	AUDIO_SDM_LEVEL_MUTE = 0,
	AUDIO_SDM_LEVEL_NORMAL = 0x1d,
	/* अगर you change level normal */
	/* you need to change क्रमmula of hp impedance and dc trim too */
पूर्ण;

क्रमागत अणु
	AUDIO_SDM_2ND = 0,
	AUDIO_SDM_3RD,
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

#घोषणा SDM_AUTO_RESET_THRESHOLD 0x190000

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
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH1", AFE_CONN3, I_DL12_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN3, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN3, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH1", AFE_CONN3_1, I_DL4_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL5_CH1", AFE_CONN3_1, I_DL5_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH1", AFE_CONN3_1, I_DL6_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL8_CH1", AFE_CONN3_1, I_DL8_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN3,
				    I_ADDA_UL_CH3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN3,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN3,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("GAIN1_OUT_CH1", AFE_CONN3,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN3,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN3,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("SRC_1_OUT_CH1", AFE_CONN3_1,
				    I_SRC_1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("SRC_2_OUT_CH1", AFE_CONN3_1,
				    I_SRC_2_OUT_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_dl_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN4, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN4, I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH2", AFE_CONN4, I_DL12_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN4, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN4, I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN4, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN4, I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH2", AFE_CONN4_1, I_DL4_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL5_CH2", AFE_CONN4_1, I_DL5_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH2", AFE_CONN4_1, I_DL6_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL8_CH2", AFE_CONN4_1, I_DL8_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN4,
				    I_ADDA_UL_CH3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN4,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN4,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("GAIN1_OUT_CH2", AFE_CONN4,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN4,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN4,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH2", AFE_CONN4,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH2", AFE_CONN4,
				    I_PCM_2_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("SRC_1_OUT_CH2", AFE_CONN4_1,
				    I_SRC_1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("SRC_2_OUT_CH2", AFE_CONN4_1,
				    I_SRC_2_OUT_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_dl_ch3_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN52, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH1", AFE_CONN52, I_DL12_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN52, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN52, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH1", AFE_CONN52_1, I_DL4_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL5_CH1", AFE_CONN52_1, I_DL5_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH1", AFE_CONN52_1, I_DL6_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN52,
				    I_ADDA_UL_CH3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN52,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN52,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("GAIN1_OUT_CH1", AFE_CONN52,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN52,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN52,
				    I_PCM_2_CAP_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_dl_ch4_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH1", AFE_CONN53, I_DL1_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL1_CH2", AFE_CONN53, I_DL1_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL12_CH2", AFE_CONN53, I_DL12_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH1", AFE_CONN53, I_DL2_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL2_CH2", AFE_CONN53, I_DL2_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH1", AFE_CONN53, I_DL3_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL3_CH2", AFE_CONN53, I_DL3_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL4_CH2", AFE_CONN53_1, I_DL4_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL5_CH2", AFE_CONN53_1, I_DL5_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("DL6_CH2", AFE_CONN53_1, I_DL6_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH3", AFE_CONN53,
				    I_ADDA_UL_CH3, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN53,
				    I_ADDA_UL_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN53,
				    I_ADDA_UL_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("GAIN1_OUT_CH2", AFE_CONN53,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH1", AFE_CONN53,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH1", AFE_CONN53,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_1_CAP_CH2", AFE_CONN53,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("PCM_2_CAP_CH2", AFE_CONN53,
				    I_PCM_2_CAP_CH2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_stf_ch1_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH1", AFE_CONN19,
				    I_ADDA_UL_CH1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mtk_stf_ch2_mix[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("ADDA_UL_CH2", AFE_CONN20,
				    I_ADDA_UL_CH2, 1, 0),
पूर्ण;

क्रमागत अणु
	SUPPLY_SEQ_ADDA_AFE_ON,
	SUPPLY_SEQ_ADDA_DL_ON,
	SUPPLY_SEQ_ADDA_AUD_PAD_TOP,
	SUPPLY_SEQ_ADDA_MTKAIF_CFG,
	SUPPLY_SEQ_ADDA6_MTKAIF_CFG,
	SUPPLY_SEQ_ADDA_FIFO,
	SUPPLY_SEQ_ADDA_AP_DMIC,
	SUPPLY_SEQ_ADDA_UL_ON,
पूर्ण;

अटल पूर्णांक mtk_adda_ul_src_dmic(काष्ठा mtk_base_afe *afe, पूर्णांक id)
अणु
	अचिन्हित पूर्णांक reg;

	चयन (id) अणु
	हाल MT8192_DAI_ADDA:
	हाल MT8192_DAI_AP_DMIC:
		reg = AFE_ADDA_UL_SRC_CON0;
		अवरोध;
	हाल MT8192_DAI_ADDA_CH34:
	हाल MT8192_DAI_AP_DMIC_CH34:
		reg = AFE_ADDA6_UL_SRC_CON0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* dmic mode, 3.25M*/
	regmap_update_bits(afe->regmap, reg,
			   DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT,
			   0x0);
	regmap_update_bits(afe->regmap, reg,
			   DMIC_LOW_POWER_MODE_CTL_MASK_SFT,
			   0x0);

	/* turn on dmic, ch1, ch2 */
	regmap_update_bits(afe->regmap, reg,
			   UL_SDM_3_LEVEL_CTL_MASK_SFT,
			   0x1 << UL_SDM_3_LEVEL_CTL_SFT);
	regmap_update_bits(afe->regmap, reg,
			   UL_MODE_3P25M_CH1_CTL_MASK_SFT,
			   0x1 << UL_MODE_3P25M_CH1_CTL_SFT);
	regmap_update_bits(afe->regmap, reg,
			   UL_MODE_3P25M_CH2_CTL_MASK_SFT,
			   0x1 << UL_MODE_3P25M_CH2_CTL_SFT);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_adda_ul_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक mtkaअगर_dmic = afe_priv->mtkaअगर_dmic;

	dev_info(afe->dev, "%s(), name %s, event 0x%x, mtkaif_dmic %d\n",
		 __func__, w->name, event, mtkaअगर_dmic);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA, 1);

		/* update setting to dmic */
		अगर (mtkaअगर_dmic) अणु
			/* mtkaअगर_rxअगर_data_mode = 1, dmic */
			regmap_update_bits(afe->regmap, AFE_ADDA_MTKAIF_RX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			regmap_update_bits(afe->regmap, AFE_ADDA_MTKAIF_RX_CFG0,
					   MTKAIF_RXIF_VOICE_MODE_MASK_SFT,
					   0x0);
			mtk_adda_ul_src_dmic(afe, MT8192_DAI_ADDA);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* should delayed 1/fs(smallest is 8k) = 125us beक्रमe afe off */
		usleep_range(125, 135);
		mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_adda_ch34_ul_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol,
				  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक mtkaअगर_dmic = afe_priv->mtkaअगर_dmic_ch34;
	पूर्णांक mtkaअगर_adda6_only = afe_priv->mtkaअगर_adda6_only;

	dev_info(afe->dev,
		 "%s(), name %s, event 0x%x, mtkaif_dmic %d, mtkaif_adda6_only %d\n",
		 __func__, w->name, event, mtkaअगर_dmic, mtkaअगर_adda6_only);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA_CH34,
					1);

		/* update setting to dmic */
		अगर (mtkaअगर_dmic) अणु
			/* mtkaअगर_rxअगर_data_mode = 1, dmic */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA6_MTKAIF_RX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			regmap_update_bits(afe->regmap,
					   AFE_ADDA6_MTKAIF_RX_CFG0,
					   MTKAIF_RXIF_VOICE_MODE_MASK_SFT,
					   0x0);
			mtk_adda_ul_src_dmic(afe, MT8192_DAI_ADDA_CH34);
		पूर्ण

		/* when using adda6 without adda enabled,
		 * RG_ADDA6_MTKAIF_RX_SYNC_WORD2_DISABLE_SFT need to be set or
		 * data cannot be received.
		 */
		अगर (mtkaअगर_adda6_only) अणु
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_MTKAIF_SYNCWORD_CFG,
					   0x1 << 23, 0x1 << 23);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* should delayed 1/fs(smallest is 8k) = 125us beक्रमe afe off */
		usleep_range(125, 135);
		mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA_CH34,
					1);

		/* reset dmic */
		afe_priv->mtkaअगर_dmic_ch34 = 0;

		अगर (mtkaअगर_adda6_only) अणु
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_MTKAIF_SYNCWORD_CFG,
					   0x1 << 23, 0x0 << 23);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_adda_pad_top_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol,
				  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (afe_priv->mtkaअगर_protocol == MTKAIF_PROTOCOL_2_CLK_P2)
			regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x38);
		अन्यथा अगर (afe_priv->mtkaअगर_protocol == MTKAIF_PROTOCOL_2)
			regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x30);
		अन्यथा
			regmap_ग_लिखो(afe->regmap, AFE_AUD_PAD_TOP, 0x30);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_adda_mtkaअगर_cfg_event(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *kcontrol,
				     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक delay_data;
	पूर्णांक delay_cycle;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (afe_priv->mtkaअगर_protocol == MTKAIF_PROTOCOL_2_CLK_P2) अणु
			/* set protocol 2 */
			regmap_ग_लिखो(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
				     0x00010000);
			regmap_ग_लिखो(afe->regmap, AFE_ADDA6_MTKAIF_CFG0,
				     0x00010000);

			अगर (म_भेद(w->name, "ADDA_MTKAIF_CFG") == 0 &&
			    (afe_priv->mtkaअगर_chosen_phase[0] < 0 ||
			     afe_priv->mtkaअगर_chosen_phase[1] < 0)) अणु
				dev_warn(afe->dev,
					 "%s(), mtkaif_chosen_phase[0/1]:%d/%d\n",
					 __func__,
					 afe_priv->mtkaअगर_chosen_phase[0],
					 afe_priv->mtkaअगर_chosen_phase[1]);
				अवरोध;
			पूर्ण अन्यथा अगर (म_भेद(w->name, "ADDA6_MTKAIF_CFG") == 0 &&
				   afe_priv->mtkaअगर_chosen_phase[2] < 0) अणु
				dev_warn(afe->dev,
					 "%s(), mtkaif_chosen_phase[2]:%d\n",
					 __func__,
					 afe_priv->mtkaअगर_chosen_phase[2]);
				अवरोध;
			पूर्ण

			/* mtkaअगर_rxअगर_clkinv_adc inverse क्रम calibration */
			regmap_update_bits(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
					   MTKAIF_RXIF_CLKINV_ADC_MASK_SFT,
					   0x1 << MTKAIF_RXIF_CLKINV_ADC_SFT);
			regmap_update_bits(afe->regmap, AFE_ADDA6_MTKAIF_CFG0,
					   MTKAIF_RXIF_CLKINV_ADC_MASK_SFT,
					   0x1 << MTKAIF_RXIF_CLKINV_ADC_SFT);

			/* set delay क्रम ch12 */
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
					   delay_data <<
					   MTKAIF_RXIF_DELAY_DATA_SFT);

			regmap_update_bits(afe->regmap,
					   AFE_ADDA_MTKAIF_RX_CFG2,
					   MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT,
					   delay_cycle <<
					   MTKAIF_RXIF_DELAY_CYCLE_SFT);

			/* set delay between ch3 and ch2 */
			अगर (afe_priv->mtkaअगर_phase_cycle[2] >=
			    afe_priv->mtkaअगर_phase_cycle[1]) अणु
				delay_data = DELAY_DATA_MISO1;	/* ch3 */
				delay_cycle = afe_priv->mtkaअगर_phase_cycle[2] -
					      afe_priv->mtkaअगर_phase_cycle[1];
			पूर्ण अन्यथा अणु
				delay_data = DELAY_DATA_MISO2;	/* ch2 */
				delay_cycle = afe_priv->mtkaअगर_phase_cycle[1] -
					      afe_priv->mtkaअगर_phase_cycle[2];
			पूर्ण

			regmap_update_bits(afe->regmap,
					   AFE_ADDA6_MTKAIF_RX_CFG2,
					   MTKAIF_RXIF_DELAY_DATA_MASK_SFT,
					   delay_data <<
					   MTKAIF_RXIF_DELAY_DATA_SFT);
			regmap_update_bits(afe->regmap,
					   AFE_ADDA6_MTKAIF_RX_CFG2,
					   MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT,
					   delay_cycle <<
					   MTKAIF_RXIF_DELAY_CYCLE_SFT);
		पूर्ण अन्यथा अगर (afe_priv->mtkaअगर_protocol == MTKAIF_PROTOCOL_2) अणु
			regmap_ग_लिखो(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
				     0x00010000);
			regmap_ग_लिखो(afe->regmap, AFE_ADDA6_MTKAIF_CFG0,
				     0x00010000);
		पूर्ण अन्यथा अणु
			regmap_ग_लिखो(afe->regmap, AFE_ADDA_MTKAIF_CFG0, 0x0);
			regmap_ग_लिखो(afe->regmap, AFE_ADDA6_MTKAIF_CFG0, 0x0);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_adda_dl_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);

	dev_info(afe->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* should delayed 1/fs(smallest is 8k) = 125us beक्रमe afe off */
		usleep_range(125, 135);
		mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_adda_ch34_dl_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol,
				  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);

	dev_info(afe->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA_CH34,
					0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* should delayed 1/fs(smallest is 8k) = 125us beक्रमe afe off */
		usleep_range(125, 135);
		mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA_CH34,
					0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* stf */
अटल पूर्णांक stf_positive_gain_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	ucontrol->value.पूर्णांकeger.value[0] = afe_priv->stf_positive_gain_db;
	वापस 0;
पूर्ण

अटल पूर्णांक stf_positive_gain_set(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक gain_db = ucontrol->value.पूर्णांकeger.value[0];

	afe_priv->stf_positive_gain_db = gain_db;

	अगर (gain_db >= 0 && gain_db <= 24) अणु
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_GAIN,
				   POSITIVE_GAIN_MASK_SFT,
				   (gain_db / 6) << POSITIVE_GAIN_SFT);
	पूर्ण अन्यथा अणु
		dev_warn(afe->dev, "%s(), gain_db %d invalid\n",
			 __func__, gain_db);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_adda_dmic_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	ucontrol->value.पूर्णांकeger.value[0] = afe_priv->mtkaअगर_dmic;
	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_adda_dmic_set(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक dmic_on;

	dmic_on = ucontrol->value.पूर्णांकeger.value[0];

	dev_info(afe->dev, "%s(), kcontrol name %s, dmic_on %d\n",
		 __func__, kcontrol->id.name, dmic_on);

	afe_priv->mtkaअगर_dmic = dmic_on;
	afe_priv->mtkaअगर_dmic_ch34 = dmic_on;
	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_adda6_only_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	ucontrol->value.पूर्णांकeger.value[0] = afe_priv->mtkaअगर_adda6_only;
	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_adda6_only_set(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक mtkaअगर_adda6_only;

	mtkaअगर_adda6_only = ucontrol->value.पूर्णांकeger.value[0];

	dev_info(afe->dev, "%s(), kcontrol name %s, mtkaif_adda6_only %d\n",
		 __func__, kcontrol->id.name, mtkaअगर_adda6_only);

	afe_priv->mtkaअगर_adda6_only = mtkaअगर_adda6_only;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mtk_adda_controls[] = अणु
	SOC_SINGLE("Sidetone_Gain", AFE_SIDETONE_GAIN,
		   SIDE_TONE_GAIN_SFT, SIDE_TONE_GAIN_MASK, 0),
	SOC_SINGLE_EXT("Sidetone_Positive_Gain_dB", SND_SOC_NOPM, 0, 100, 0,
		       stf_positive_gain_get, stf_positive_gain_set),
	SOC_SINGLE("ADDA_DL_GAIN", AFE_ADDA_DL_SRC2_CON1,
		   DL_2_GAIN_CTL_PRE_SFT, DL_2_GAIN_CTL_PRE_MASK, 0),
	SOC_SINGLE_BOOL_EXT("MTKAIF_DMIC Switch", 0,
			    mt8192_adda_dmic_get, mt8192_adda_dmic_set),
	SOC_SINGLE_BOOL_EXT("MTKAIF_ADDA6_ONLY Switch", 0,
			    mt8192_adda6_only_get, mt8192_adda6_only_set),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new stf_ctl =
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0);

अटल स्थिर u16 stf_coeff_table_16k[] = अणु
	0x049C, 0x09E8, 0x09E0, 0x089C,
	0xFF54, 0xF488, 0xEAFC, 0xEBAC,
	0xfA40, 0x17AC, 0x3D1C, 0x6028,
	0x7538
पूर्ण;

अटल स्थिर u16 stf_coeff_table_32k[] = अणु
	0xFE52, 0x0042, 0x00C5, 0x0194,
	0x029A, 0x03B7, 0x04BF, 0x057D,
	0x05BE, 0x0555, 0x0426, 0x0230,
	0xFF92, 0xFC89, 0xF973, 0xF6C6,
	0xF500, 0xF49D, 0xF603, 0xF970,
	0xFEF3, 0x065F, 0x0F4F, 0x1928,
	0x2329, 0x2C80, 0x345E, 0x3A0D,
	0x3D08
पूर्ण;

अटल स्थिर u16 stf_coeff_table_48k[] = अणु
	0x0401, 0xFFB0, 0xFF5A, 0xFECE,
	0xFE10, 0xFD28, 0xFC21, 0xFB08,
	0xF9EF, 0xF8E8, 0xF80A, 0xF76C,
	0xF724, 0xF746, 0xF7E6, 0xF90F,
	0xFACC, 0xFD1E, 0xFFFF, 0x0364,
	0x0737, 0x0B62, 0x0FC1, 0x1431,
	0x188A, 0x1CA4, 0x2056, 0x237D,
	0x25F9, 0x27B0, 0x2890
पूर्ण;

अटल पूर्णांक mtk_stf_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt);

	माप_प्रकार half_tap_num;
	स्थिर u16 *stf_coeff_table;
	अचिन्हित पूर्णांक ul_rate, reg_value;
	माप_प्रकार coef_addr;

	regmap_पढ़ो(afe->regmap, AFE_ADDA_UL_SRC_CON0, &ul_rate);
	ul_rate = ul_rate >> UL_VOICE_MODE_CH1_CH2_CTL_SFT;
	ul_rate = ul_rate & UL_VOICE_MODE_CH1_CH2_CTL_MASK;

	अगर (ul_rate == MTK_AFE_ADDA_UL_RATE_48K) अणु
		half_tap_num = ARRAY_SIZE(stf_coeff_table_48k);
		stf_coeff_table = stf_coeff_table_48k;
	पूर्ण अन्यथा अगर (ul_rate == MTK_AFE_ADDA_UL_RATE_32K) अणु
		half_tap_num = ARRAY_SIZE(stf_coeff_table_32k);
		stf_coeff_table = stf_coeff_table_32k;
	पूर्ण अन्यथा अणु
		half_tap_num = ARRAY_SIZE(stf_coeff_table_16k);
		stf_coeff_table = stf_coeff_table_16k;
	पूर्ण

	regmap_पढ़ो(afe->regmap, AFE_SIDETONE_CON1, &reg_value);

	dev_info(afe->dev, "%s(), name %s, event 0x%x, ul_rate 0x%x, AFE_SIDETONE_CON1 0x%x\n",
		 __func__, w->name, event, ul_rate, reg_value);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* set side tone gain = 0 */
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_GAIN,
				   SIDE_TONE_GAIN_MASK_SFT,
				   0);
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_GAIN,
				   POSITIVE_GAIN_MASK_SFT,
				   0);
		/* करोn't bypass stf */
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_CON1,
				   0x1f << 27,
				   0x0);
		/* set stf half tap num */
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_CON1,
				   SIDE_TONE_HALF_TAP_NUM_MASK_SFT,
				   half_tap_num << SIDE_TONE_HALF_TAP_NUM_SFT);

		/* set side tone coefficient */
		regmap_पढ़ो(afe->regmap, AFE_SIDETONE_CON0, &reg_value);
		क्रम (coef_addr = 0; coef_addr < half_tap_num; coef_addr++) अणु
			bool old_w_पढ़ोy = (reg_value >> W_RDY_SFT) & 0x1;
			bool new_w_पढ़ोy = 0;
			पूर्णांक try_cnt = 0;

			regmap_update_bits(afe->regmap,
					   AFE_SIDETONE_CON0,
					   0x39FFFFF,
					   (1 << R_W_EN_SFT) |
					   (1 << R_W_SEL_SFT) |
					   (0 << SEL_CH2_SFT) |
					   (coef_addr <<
					   SIDE_TONE_COEFFICIENT_ADDR_SFT) |
					   stf_coeff_table[coef_addr]);

			/* रुको until flag ग_लिखो_पढ़ोy changed */
			क्रम (try_cnt = 0; try_cnt < 10; try_cnt++) अणु
				regmap_पढ़ो(afe->regmap,
					    AFE_SIDETONE_CON0, &reg_value);
				new_w_पढ़ोy = (reg_value >> W_RDY_SFT) & 0x1;

				/* flip => ok */
				अगर (new_w_पढ़ोy == old_w_पढ़ोy) अणु
					udelay(3);
					अगर (try_cnt == 9) अणु
						dev_warn(afe->dev,
							 "%s(), write coeff not ready",
							 __func__);
					पूर्ण
				पूर्ण अन्यथा अणु
					अवरोध;
				पूर्ण
			पूर्ण
			/* need ग_लिखो -> पढ़ो -> ग_लिखो to ग_लिखो next coeff */
			regmap_update_bits(afe->regmap,
					   AFE_SIDETONE_CON0,
					   R_W_SEL_MASK_SFT,
					   0x0);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* bypass stf */
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_CON1,
				   0x1f << 27,
				   0x1f << 27);

		/* set side tone gain = 0 */
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_GAIN,
				   SIDE_TONE_GAIN_MASK_SFT,
				   0);
		regmap_update_bits(afe->regmap,
				   AFE_SIDETONE_GAIN,
				   POSITIVE_GAIN_MASK_SFT,
				   0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* stf mux */
क्रमागत अणु
	STF_SRC_ADDA_ADDA6 = 0,
	STF_SRC_O19O20,
पूर्ण;

अटल स्थिर अक्षर *स्थिर stf_o19o20_mux_map[] = अणु
	"ADDA_ADDA6",
	"O19O20",
पूर्ण;

अटल पूर्णांक stf_o19o20_mux_map_value[] = अणु
	STF_SRC_ADDA_ADDA6,
	STF_SRC_O19O20,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(stf_o19o20_mux_map_क्रमागत,
				  AFE_SIDETONE_CON1,
				  STF_SOURCE_FROM_O19O20_SFT,
				  STF_SOURCE_FROM_O19O20_MASK,
				  stf_o19o20_mux_map,
				  stf_o19o20_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new stf_o19O20_mux_control =
	SOC_DAPM_ENUM("STF_O19O20_MUX", stf_o19o20_mux_map_क्रमागत);

क्रमागत अणु
	STF_SRC_ADDA = 0,
	STF_SRC_ADDA6,
पूर्ण;

अटल स्थिर अक्षर *स्थिर stf_adda_mux_map[] = अणु
	"ADDA",
	"ADDA6",
पूर्ण;

अटल पूर्णांक stf_adda_mux_map_value[] = अणु
	STF_SRC_ADDA,
	STF_SRC_ADDA6,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(stf_adda_mux_map_क्रमागत,
				  AFE_SIDETONE_CON1,
				  STF_O19O20_OUT_EN_SEL_SFT,
				  STF_O19O20_OUT_EN_SEL_MASK,
				  stf_adda_mux_map,
				  stf_adda_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new stf_adda_mux_control =
	SOC_DAPM_ENUM("STF_ADDA_MUX", stf_adda_mux_map_क्रमागत);

/* ADDA UL MUX */
क्रमागत अणु
	ADDA_UL_MUX_MTKAIF = 0,
	ADDA_UL_MUX_AP_DMIC,
	ADDA_UL_MUX_MASK = 0x1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adda_ul_mux_map[] = अणु
	"MTKAIF", "AP_DMIC"
पूर्ण;

अटल पूर्णांक adda_ul_map_value[] = अणु
	ADDA_UL_MUX_MTKAIF,
	ADDA_UL_MUX_AP_DMIC,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adda_ul_mux_map_क्रमागत,
				  SND_SOC_NOPM,
				  0,
				  ADDA_UL_MUX_MASK,
				  adda_ul_mux_map,
				  adda_ul_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adda_ul_mux_control =
	SOC_DAPM_ENUM("ADDA_UL_MUX Select", adda_ul_mux_map_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adda_ch34_ul_mux_control =
	SOC_DAPM_ENUM("ADDA_CH34_UL_MUX Select", adda_ul_mux_map_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget mtk_dai_adda_widमाला_लो[] = अणु
	/* पूर्णांकer-connections */
	SND_SOC_DAPM_MIXER("ADDA_DL_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dl_ch1_mix,
			   ARRAY_SIZE(mtk_adda_dl_ch1_mix)),
	SND_SOC_DAPM_MIXER("ADDA_DL_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dl_ch2_mix,
			   ARRAY_SIZE(mtk_adda_dl_ch2_mix)),

	SND_SOC_DAPM_MIXER("ADDA_DL_CH3", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dl_ch3_mix,
			   ARRAY_SIZE(mtk_adda_dl_ch3_mix)),
	SND_SOC_DAPM_MIXER("ADDA_DL_CH4", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dl_ch4_mix,
			   ARRAY_SIZE(mtk_adda_dl_ch4_mix)),

	SND_SOC_DAPM_SUPPLY_S("ADDA Enable", SUPPLY_SEQ_ADDA_AFE_ON,
			      AFE_ADDA_UL_DL_CON0, ADDA_AFE_ON_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("ADDA Playback Enable", SUPPLY_SEQ_ADDA_DL_ON,
			      AFE_ADDA_DL_SRC2_CON0,
			      DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0,
			      mtk_adda_dl_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("ADDA CH34 Playback Enable",
			      SUPPLY_SEQ_ADDA_DL_ON,
			      AFE_ADDA_3RD_DAC_DL_SRC2_CON0,
			      DL_2_SRC_ON_TMP_CTL_PRE_SFT, 0,
			      mtk_adda_ch34_dl_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("ADDA Capture Enable", SUPPLY_SEQ_ADDA_UL_ON,
			      AFE_ADDA_UL_SRC_CON0,
			      UL_SRC_ON_TMP_CTL_SFT, 0,
			      mtk_adda_ul_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("ADDA CH34 Capture Enable", SUPPLY_SEQ_ADDA_UL_ON,
			      AFE_ADDA6_UL_SRC_CON0,
			      UL_SRC_ON_TMP_CTL_SFT, 0,
			      mtk_adda_ch34_ul_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY_S("AUD_PAD_TOP", SUPPLY_SEQ_ADDA_AUD_PAD_TOP,
			      AFE_AUD_PAD_TOP,
			      RG_RX_FIFO_ON_SFT, 0,
			      mtk_adda_pad_top_event,
			      SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY_S("ADDA_MTKAIF_CFG", SUPPLY_SEQ_ADDA_MTKAIF_CFG,
			      SND_SOC_NOPM, 0, 0,
			      mtk_adda_mtkaअगर_cfg_event,
			      SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY_S("ADDA6_MTKAIF_CFG", SUPPLY_SEQ_ADDA6_MTKAIF_CFG,
			      SND_SOC_NOPM, 0, 0,
			      mtk_adda_mtkaअगर_cfg_event,
			      SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_SUPPLY_S("AP_DMIC_EN", SUPPLY_SEQ_ADDA_AP_DMIC,
			      AFE_ADDA_UL_SRC_CON0,
			      UL_AP_DMIC_ON_SFT, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("AP_DMIC_CH34_EN", SUPPLY_SEQ_ADDA_AP_DMIC,
			      AFE_ADDA6_UL_SRC_CON0,
			      UL_AP_DMIC_ON_SFT, 0,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("ADDA_FIFO", SUPPLY_SEQ_ADDA_FIFO,
			      AFE_ADDA_UL_DL_CON0,
			      AFE_ADDA_FIFO_AUTO_RST_SFT, 1,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADDA_CH34_FIFO", SUPPLY_SEQ_ADDA_FIFO,
			      AFE_ADDA_UL_DL_CON0,
			      AFE_ADDA6_FIFO_AUTO_RST_SFT, 1,
			      शून्य, 0),

	SND_SOC_DAPM_MUX("ADDA_UL_Mux", SND_SOC_NOPM, 0, 0,
			 &adda_ul_mux_control),
	SND_SOC_DAPM_MUX("ADDA_CH34_UL_Mux", SND_SOC_NOPM, 0, 0,
			 &adda_ch34_ul_mux_control),

	SND_SOC_DAPM_INPUT("AP_DMIC_INPUT"),
	SND_SOC_DAPM_INPUT("AP_DMIC_CH34_INPUT"),

	/* stf */
	SND_SOC_DAPM_SWITCH_E("Sidetone Filter",
			      AFE_SIDETONE_CON1, SIDE_TONE_ON_SFT, 0,
			      &stf_ctl,
			      mtk_stf_event,
			      SND_SOC_DAPM_PRE_PMU |
			      SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("STF_O19O20_MUX", SND_SOC_NOPM, 0, 0,
			 &stf_o19O20_mux_control),
	SND_SOC_DAPM_MUX("STF_ADDA_MUX", SND_SOC_NOPM, 0, 0,
			 &stf_adda_mux_control),
	SND_SOC_DAPM_MIXER("STF_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_stf_ch1_mix,
			   ARRAY_SIZE(mtk_stf_ch1_mix)),
	SND_SOC_DAPM_MIXER("STF_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_stf_ch2_mix,
			   ARRAY_SIZE(mtk_stf_ch2_mix)),
	SND_SOC_DAPM_OUTPUT("STF_OUTPUT"),

	/* घड़ी */
	SND_SOC_DAPM_CLOCK_SUPPLY("top_mux_audio_h"),

	SND_SOC_DAPM_CLOCK_SUPPLY("aud_dac_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("aud_dac_predis_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("aud_3rd_dac_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("aud_3rd_dac_predis_clk"),

	SND_SOC_DAPM_CLOCK_SUPPLY("aud_adc_clk"),
	SND_SOC_DAPM_CLOCK_SUPPLY("aud_adda6_adc_clk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mtk_dai_adda_routes[] = अणु
	/* playback */
	अणु"ADDA_DL_CH1", "DL1_CH1", "DL1"पूर्ण,
	अणु"ADDA_DL_CH2", "DL1_CH1", "DL1"पूर्ण,
	अणु"ADDA_DL_CH2", "DL1_CH2", "DL1"पूर्ण,

	अणु"ADDA_DL_CH1", "DL12_CH1", "DL12"पूर्ण,
	अणु"ADDA_DL_CH2", "DL12_CH2", "DL12"पूर्ण,

	अणु"ADDA_DL_CH1", "DL6_CH1", "DL6"पूर्ण,
	अणु"ADDA_DL_CH2", "DL6_CH2", "DL6"पूर्ण,

	अणु"ADDA_DL_CH1", "DL8_CH1", "DL8"पूर्ण,
	अणु"ADDA_DL_CH2", "DL8_CH2", "DL8"पूर्ण,

	अणु"ADDA_DL_CH1", "DL2_CH1", "DL2"पूर्ण,
	अणु"ADDA_DL_CH2", "DL2_CH1", "DL2"पूर्ण,
	अणु"ADDA_DL_CH2", "DL2_CH2", "DL2"पूर्ण,

	अणु"ADDA_DL_CH1", "DL3_CH1", "DL3"पूर्ण,
	अणु"ADDA_DL_CH2", "DL3_CH1", "DL3"पूर्ण,
	अणु"ADDA_DL_CH2", "DL3_CH2", "DL3"पूर्ण,

	अणु"ADDA_DL_CH1", "DL4_CH1", "DL4"पूर्ण,
	अणु"ADDA_DL_CH2", "DL4_CH2", "DL4"पूर्ण,

	अणु"ADDA_DL_CH1", "DL5_CH1", "DL5"पूर्ण,
	अणु"ADDA_DL_CH2", "DL5_CH2", "DL5"पूर्ण,

	अणु"ADDA Playback", शून्य, "ADDA_DL_CH1"पूर्ण,
	अणु"ADDA Playback", शून्य, "ADDA_DL_CH2"पूर्ण,

	अणु"ADDA Playback", शून्य, "ADDA Enable"पूर्ण,
	अणु"ADDA Playback", शून्य, "ADDA Playback Enable"पूर्ण,

	अणु"ADDA_DL_CH3", "DL1_CH1", "DL1"पूर्ण,
	अणु"ADDA_DL_CH4", "DL1_CH1", "DL1"पूर्ण,
	अणु"ADDA_DL_CH4", "DL1_CH2", "DL1"पूर्ण,

	अणु"ADDA_DL_CH3", "DL12_CH1", "DL12"पूर्ण,
	अणु"ADDA_DL_CH4", "DL12_CH2", "DL12"पूर्ण,

	अणु"ADDA_DL_CH3", "DL6_CH1", "DL6"पूर्ण,
	अणु"ADDA_DL_CH4", "DL6_CH2", "DL6"पूर्ण,

	अणु"ADDA_DL_CH3", "DL2_CH1", "DL2"पूर्ण,
	अणु"ADDA_DL_CH4", "DL2_CH1", "DL2"पूर्ण,
	अणु"ADDA_DL_CH4", "DL2_CH2", "DL2"पूर्ण,

	अणु"ADDA_DL_CH3", "DL3_CH1", "DL3"पूर्ण,
	अणु"ADDA_DL_CH4", "DL3_CH1", "DL3"पूर्ण,
	अणु"ADDA_DL_CH4", "DL3_CH2", "DL3"पूर्ण,

	अणु"ADDA_DL_CH3", "DL4_CH1", "DL4"पूर्ण,
	अणु"ADDA_DL_CH4", "DL4_CH2", "DL4"पूर्ण,

	अणु"ADDA_DL_CH3", "DL5_CH1", "DL5"पूर्ण,
	अणु"ADDA_DL_CH4", "DL5_CH2", "DL5"पूर्ण,

	अणु"ADDA CH34 Playback", शून्य, "ADDA_DL_CH3"पूर्ण,
	अणु"ADDA CH34 Playback", शून्य, "ADDA_DL_CH4"पूर्ण,

	अणु"ADDA CH34 Playback", शून्य, "ADDA Enable"पूर्ण,
	अणु"ADDA CH34 Playback", शून्य, "ADDA CH34 Playback Enable"पूर्ण,

	/* capture */
	अणु"ADDA_UL_Mux", "MTKAIF", "ADDA Capture"पूर्ण,
	अणु"ADDA_UL_Mux", "AP_DMIC", "AP DMIC Capture"पूर्ण,

	अणु"ADDA_CH34_UL_Mux", "MTKAIF", "ADDA CH34 Capture"पूर्ण,
	अणु"ADDA_CH34_UL_Mux", "AP_DMIC", "AP DMIC CH34 Capture"पूर्ण,

	अणु"ADDA Capture", शून्य, "ADDA Enable"पूर्ण,
	अणु"ADDA Capture", शून्य, "ADDA Capture Enable"पूर्ण,
	अणु"ADDA Capture", शून्य, "AUD_PAD_TOP"पूर्ण,
	अणु"ADDA Capture", शून्य, "ADDA_MTKAIF_CFG"पूर्ण,

	अणु"AP DMIC Capture", शून्य, "ADDA Enable"पूर्ण,
	अणु"AP DMIC Capture", शून्य, "ADDA Capture Enable"पूर्ण,
	अणु"AP DMIC Capture", शून्य, "ADDA_FIFO"पूर्ण,
	अणु"AP DMIC Capture", शून्य, "AP_DMIC_EN"पूर्ण,

	अणु"ADDA CH34 Capture", शून्य, "ADDA Enable"पूर्ण,
	अणु"ADDA CH34 Capture", शून्य, "ADDA CH34 Capture Enable"पूर्ण,
	अणु"ADDA CH34 Capture", शून्य, "AUD_PAD_TOP"पूर्ण,
	अणु"ADDA CH34 Capture", शून्य, "ADDA6_MTKAIF_CFG"पूर्ण,

	अणु"AP DMIC CH34 Capture", शून्य, "ADDA Enable"पूर्ण,
	अणु"AP DMIC CH34 Capture", शून्य, "ADDA CH34 Capture Enable"पूर्ण,
	अणु"AP DMIC CH34 Capture", शून्य, "ADDA_CH34_FIFO"पूर्ण,
	अणु"AP DMIC CH34 Capture", शून्य, "AP_DMIC_CH34_EN"पूर्ण,

	अणु"AP DMIC Capture", शून्य, "AP_DMIC_INPUT"पूर्ण,
	अणु"AP DMIC CH34 Capture", शून्य, "AP_DMIC_CH34_INPUT"पूर्ण,

	/* sidetone filter */
	अणु"STF_ADDA_MUX", "ADDA", "ADDA_UL_Mux"पूर्ण,
	अणु"STF_ADDA_MUX", "ADDA6", "ADDA_CH34_UL_Mux"पूर्ण,

	अणु"STF_O19O20_MUX", "ADDA_ADDA6", "STF_ADDA_MUX"पूर्ण,
	अणु"STF_O19O20_MUX", "O19O20", "STF_CH1"पूर्ण,
	अणु"STF_O19O20_MUX", "O19O20", "STF_CH2"पूर्ण,

	अणु"Sidetone Filter", "Switch", "STF_O19O20_MUX"पूर्ण,
	अणु"STF_OUTPUT", शून्य, "Sidetone Filter"पूर्ण,
	अणु"ADDA Playback", शून्य, "Sidetone Filter"पूर्ण,
	अणु"ADDA CH34 Playback", शून्य, "Sidetone Filter"पूर्ण,

	/* clk */
	अणु"ADDA Playback", शून्य, "aud_dac_clk"पूर्ण,
	अणु"ADDA Playback", शून्य, "aud_dac_predis_clk"पूर्ण,

	अणु"ADDA CH34 Playback", शून्य, "aud_3rd_dac_clk"पूर्ण,
	अणु"ADDA CH34 Playback", शून्य, "aud_3rd_dac_predis_clk"पूर्ण,

	अणु"ADDA Capture Enable", शून्य, "aud_adc_clk"पूर्ण,
	अणु"ADDA CH34 Capture Enable", शून्य, "aud_adda6_adc_clk"पूर्ण,
पूर्ण;

/* dai ops */
अटल पूर्णांक mtk_dai_adda_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक id = dai->id;

	dev_info(afe->dev, "%s(), id %d, stream %d, rate %d\n",
		 __func__,
		 id,
		 substream->stream,
		 rate);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अचिन्हित पूर्णांक dl_src2_con0 = 0;
		अचिन्हित पूर्णांक dl_src2_con1 = 0;

		/* set sampling rate */
		dl_src2_con0 = adda_dl_rate_transक्रमm(afe, rate) <<
			       DL_2_INPUT_MODE_CTL_SFT;

		/* set output mode, UP_SAMPLING_RATE_X8 */
		dl_src2_con0 |= (0x3 << DL_2_OUTPUT_SEL_CTL_SFT);

		/* turn off mute function */
		dl_src2_con0 |= (0x01 << DL_2_MUTE_CH2_OFF_CTL_PRE_SFT);
		dl_src2_con0 |= (0x01 << DL_2_MUTE_CH1_OFF_CTL_PRE_SFT);

		/* set voice input data अगर input sample rate is 8k or 16k */
		अगर (rate == 8000 || rate == 16000)
			dl_src2_con0 |= 0x01 << DL_2_VOICE_MODE_CTL_PRE_SFT;

		/* SA suggest apply -0.3db to audio/speech path */
		dl_src2_con1 = MTK_AFE_ADDA_DL_GAIN_NORMAL <<
			       DL_2_GAIN_CTL_PRE_SFT;

		/* turn on करोwn-link gain */
		dl_src2_con0 |= (0x01 << DL_2_GAIN_ON_CTL_PRE_SFT);

		अगर (id == MT8192_DAI_ADDA) अणु
			/* clean predistortion */
			regmap_ग_लिखो(afe->regmap, AFE_ADDA_PREDIS_CON0, 0);
			regmap_ग_लिखो(afe->regmap, AFE_ADDA_PREDIS_CON1, 0);

			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_DL_SRC2_CON0, dl_src2_con0);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_DL_SRC2_CON1, dl_src2_con1);

			/* set sdm gain */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_DL_SDM_DCCOMP_CON,
					   ATTGAIN_CTL_MASK_SFT,
					   AUDIO_SDM_LEVEL_NORMAL <<
					   ATTGAIN_CTL_SFT);

			/* 2nd sdm */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_DL_SDM_DCCOMP_CON,
					   USE_3RD_SDM_MASK_SFT,
					   AUDIO_SDM_2ND << USE_3RD_SDM_SFT);

			/* sdm स्वतः reset */
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_DL_SDM_AUTO_RESET_CON,
				     SDM_AUTO_RESET_THRESHOLD);
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_DL_SDM_AUTO_RESET_CON,
					   ADDA_SDM_AUTO_RESET_ONOFF_MASK_SFT,
					   0x1 << ADDA_SDM_AUTO_RESET_ONOFF_SFT);
		पूर्ण अन्यथा अणु
			/* clean predistortion */
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_3RD_DAC_PREDIS_CON0, 0);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_3RD_DAC_PREDIS_CON1, 0);

			regmap_ग_लिखो(afe->regmap, AFE_ADDA_3RD_DAC_DL_SRC2_CON0,
				     dl_src2_con0);
			regmap_ग_लिखो(afe->regmap, AFE_ADDA_3RD_DAC_DL_SRC2_CON1,
				     dl_src2_con1);

			/* set sdm gain */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_3RD_DAC_DL_SDM_DCCOMP_CON,
					   ATTGAIN_CTL_MASK_SFT,
					   AUDIO_SDM_LEVEL_NORMAL <<
					   ATTGAIN_CTL_SFT);

			/* 2nd sdm */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_3RD_DAC_DL_SDM_DCCOMP_CON,
					   USE_3RD_SDM_MASK_SFT,
					   AUDIO_SDM_2ND << USE_3RD_SDM_SFT);

			/* sdm स्वतः reset */
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_3RD_DAC_DL_SDM_AUTO_RESET_CON,
				     SDM_AUTO_RESET_THRESHOLD);
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_3RD_DAC_DL_SDM_AUTO_RESET_CON,
					   ADDA_3RD_DAC_SDM_AUTO_RESET_ONOFF_MASK_SFT,
					   0x1 << ADDA_3RD_DAC_SDM_AUTO_RESET_ONOFF_SFT);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक voice_mode = 0;
		अचिन्हित पूर्णांक ul_src_con0 = 0;	/* शेष value */

		voice_mode = adda_ul_rate_transक्रमm(afe, rate);

		ul_src_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* enable iir */
		ul_src_con0 |= (1 << UL_IIR_ON_TMP_CTL_SFT) &
			       UL_IIR_ON_TMP_CTL_MASK_SFT;
		ul_src_con0 |= (UL_IIR_SW << UL_IIRMODE_CTL_SFT) &
			       UL_IIRMODE_CTL_MASK_SFT;

		चयन (id) अणु
		हाल MT8192_DAI_ADDA:
		हाल MT8192_DAI_AP_DMIC:
			/* 35Hz @ 48k */
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_IIR_COEF_02_01, 0x00000000);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_IIR_COEF_04_03, 0x00003FB8);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_IIR_COEF_06_05, 0x3FB80000);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_IIR_COEF_08_07, 0x3FB80000);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_IIR_COEF_10_09, 0x0000C048);

			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA_UL_SRC_CON0, ul_src_con0);

			/* Using Internal ADC */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_TOP_CON0,
					   0x1 << 0,
					   0x0 << 0);

			/* mtkaअगर_rxअगर_data_mode = 0, amic */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA_MTKAIF_RX_CFG0,
					   0x1 << 0,
					   0x0 << 0);
			अवरोध;
		हाल MT8192_DAI_ADDA_CH34:
		हाल MT8192_DAI_AP_DMIC_CH34:
			/* 35Hz @ 48k */
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA6_IIR_COEF_02_01, 0x00000000);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA6_IIR_COEF_04_03, 0x00003FB8);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA6_IIR_COEF_06_05, 0x3FB80000);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA6_IIR_COEF_08_07, 0x3FB80000);
			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA6_IIR_COEF_10_09, 0x0000C048);

			regmap_ग_लिखो(afe->regmap,
				     AFE_ADDA6_UL_SRC_CON0, ul_src_con0);

			/* Using Internal ADC */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA6_TOP_CON0,
					   0x1 << 0,
					   0x0 << 0);

			/* mtkaअगर_rxअगर_data_mode = 0, amic */
			regmap_update_bits(afe->regmap,
					   AFE_ADDA6_MTKAIF_RX_CFG0,
					   0x1 << 0,
					   0x0 << 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* ap dmic */
		चयन (id) अणु
		हाल MT8192_DAI_AP_DMIC:
		हाल MT8192_DAI_AP_DMIC_CH34:
			mtk_adda_ul_src_dmic(afe, id);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
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
		.id = MT8192_DAI_ADDA,
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
	अणु
		.name = "ADDA_CH34",
		.id = MT8192_DAI_ADDA_CH34,
		.playback = अणु
			.stream_name = "ADDA CH34 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_ADDA_PLAYBACK_RATES,
			.क्रमmats = MTK_ADDA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "ADDA CH34 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_ADDA_CAPTURE_RATES,
			.क्रमmats = MTK_ADDA_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_adda_ops,
	पूर्ण,
	अणु
		.name = "AP_DMIC",
		.id = MT8192_DAI_AP_DMIC,
		.capture = अणु
			.stream_name = "AP DMIC Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_ADDA_CAPTURE_RATES,
			.क्रमmats = MTK_ADDA_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_adda_ops,
	पूर्ण,
	अणु
		.name = "AP_DMIC_CH34",
		.id = MT8192_DAI_AP_DMIC_CH34,
		.capture = अणु
			.stream_name = "AP DMIC CH34 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MTK_ADDA_CAPTURE_RATES,
			.क्रमmats = MTK_ADDA_FORMATS,
		पूर्ण,
		.ops = &mtk_dai_adda_ops,
	पूर्ण,
पूर्ण;

पूर्णांक mt8192_dai_adda_रेजिस्टर(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	dev_info(afe->dev, "%s()\n", __func__);

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

	/* ap dmic priv share with adda */
	afe_priv->dai_priv[MT8192_DAI_AP_DMIC] =
		afe_priv->dai_priv[MT8192_DAI_ADDA];
	afe_priv->dai_priv[MT8192_DAI_AP_DMIC_CH34] =
		afe_priv->dai_priv[MT8192_DAI_ADDA_CH34];

	वापस 0;
पूर्ण
