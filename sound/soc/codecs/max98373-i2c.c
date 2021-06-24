<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017, Maxim Integrated

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/cdev.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "max98373.h"

अटल स्थिर u32 max98373_i2c_cache_reg[] = अणु
	MAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK,
	MAX98373_R2055_MEAS_ADC_THERM_CH_READBACK,
	MAX98373_R20B6_BDE_CUR_STATE_READBACK,
पूर्ण;

अटल काष्ठा reg_शेष max98373_reg[] = अणु
	अणुMAX98373_R2000_SW_RESET, 0x00पूर्ण,
	अणुMAX98373_R2001_INT_RAW1, 0x00पूर्ण,
	अणुMAX98373_R2002_INT_RAW2, 0x00पूर्ण,
	अणुMAX98373_R2003_INT_RAW3, 0x00पूर्ण,
	अणुMAX98373_R2004_INT_STATE1, 0x00पूर्ण,
	अणुMAX98373_R2005_INT_STATE2, 0x00पूर्ण,
	अणुMAX98373_R2006_INT_STATE3, 0x00पूर्ण,
	अणुMAX98373_R2007_INT_FLAG1, 0x00पूर्ण,
	अणुMAX98373_R2008_INT_FLAG2, 0x00पूर्ण,
	अणुMAX98373_R2009_INT_FLAG3, 0x00पूर्ण,
	अणुMAX98373_R200A_INT_EN1, 0x00पूर्ण,
	अणुMAX98373_R200B_INT_EN2, 0x00पूर्ण,
	अणुMAX98373_R200C_INT_EN3, 0x00पूर्ण,
	अणुMAX98373_R200D_INT_FLAG_CLR1, 0x00पूर्ण,
	अणुMAX98373_R200E_INT_FLAG_CLR2, 0x00पूर्ण,
	अणुMAX98373_R200F_INT_FLAG_CLR3, 0x00पूर्ण,
	अणुMAX98373_R2010_IRQ_CTRL, 0x00पूर्ण,
	अणुMAX98373_R2014_THERM_WARN_THRESH, 0x10पूर्ण,
	अणुMAX98373_R2015_THERM_SHDN_THRESH, 0x27पूर्ण,
	अणुMAX98373_R2016_THERM_HYSTERESIS, 0x01पूर्ण,
	अणुMAX98373_R2017_THERM_FOLDBACK_SET, 0xC0पूर्ण,
	अणुMAX98373_R2018_THERM_FOLDBACK_EN, 0x00पूर्ण,
	अणुMAX98373_R201E_PIN_DRIVE_STRENGTH, 0x55पूर्ण,
	अणुMAX98373_R2020_PCM_TX_HIZ_EN_1, 0xFEपूर्ण,
	अणुMAX98373_R2021_PCM_TX_HIZ_EN_2, 0xFFपूर्ण,
	अणुMAX98373_R2022_PCM_TX_SRC_1, 0x00पूर्ण,
	अणुMAX98373_R2023_PCM_TX_SRC_2, 0x00पूर्ण,
	अणुMAX98373_R2024_PCM_DATA_FMT_CFG, 0xC0पूर्ण,
	अणुMAX98373_R2025_AUDIO_IF_MODE, 0x00पूर्ण,
	अणुMAX98373_R2026_PCM_CLOCK_RATIO, 0x04पूर्ण,
	अणुMAX98373_R2027_PCM_SR_SETUP_1, 0x08पूर्ण,
	अणुMAX98373_R2028_PCM_SR_SETUP_2, 0x88पूर्ण,
	अणुMAX98373_R2029_PCM_TO_SPK_MONO_MIX_1, 0x00पूर्ण,
	अणुMAX98373_R202A_PCM_TO_SPK_MONO_MIX_2, 0x00पूर्ण,
	अणुMAX98373_R202B_PCM_RX_EN, 0x00पूर्ण,
	अणुMAX98373_R202C_PCM_TX_EN, 0x00पूर्ण,
	अणुMAX98373_R202E_ICC_RX_CH_EN_1, 0x00पूर्ण,
	अणुMAX98373_R202F_ICC_RX_CH_EN_2, 0x00पूर्ण,
	अणुMAX98373_R2030_ICC_TX_HIZ_EN_1, 0xFFपूर्ण,
	अणुMAX98373_R2031_ICC_TX_HIZ_EN_2, 0xFFपूर्ण,
	अणुMAX98373_R2032_ICC_LINK_EN_CFG, 0x30पूर्ण,
	अणुMAX98373_R2034_ICC_TX_CNTL, 0x00पूर्ण,
	अणुMAX98373_R2035_ICC_TX_EN, 0x00पूर्ण,
	अणुMAX98373_R2036_SOUNDWIRE_CTRL, 0x05पूर्ण,
	अणुMAX98373_R203D_AMP_DIG_VOL_CTRL, 0x00पूर्ण,
	अणुMAX98373_R203E_AMP_PATH_GAIN, 0x08पूर्ण,
	अणुMAX98373_R203F_AMP_DSP_CFG, 0x02पूर्ण,
	अणुMAX98373_R2040_TONE_GEN_CFG, 0x00पूर्ण,
	अणुMAX98373_R2041_AMP_CFG, 0x03पूर्ण,
	अणुMAX98373_R2042_AMP_EDGE_RATE_CFG, 0x00पूर्ण,
	अणुMAX98373_R2043_AMP_EN, 0x00पूर्ण,
	अणुMAX98373_R2046_IV_SENSE_ADC_DSP_CFG, 0x04पूर्ण,
	अणुMAX98373_R2047_IV_SENSE_ADC_EN, 0x00पूर्ण,
	अणुMAX98373_R2051_MEAS_ADC_SAMPLING_RATE, 0x00पूर्ण,
	अणुMAX98373_R2052_MEAS_ADC_PVDD_FLT_CFG, 0x00पूर्ण,
	अणुMAX98373_R2053_MEAS_ADC_THERM_FLT_CFG, 0x00पूर्ण,
	अणुMAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK, 0x00पूर्ण,
	अणुMAX98373_R2055_MEAS_ADC_THERM_CH_READBACK, 0x00पूर्ण,
	अणुMAX98373_R2056_MEAS_ADC_PVDD_CH_EN, 0x00पूर्ण,
	अणुMAX98373_R2090_BDE_LVL_HOLD, 0x00पूर्ण,
	अणुMAX98373_R2091_BDE_GAIN_ATK_REL_RATE, 0x00पूर्ण,
	अणुMAX98373_R2092_BDE_CLIPPER_MODE, 0x00पूर्ण,
	अणुMAX98373_R2097_BDE_L1_THRESH, 0x00पूर्ण,
	अणुMAX98373_R2098_BDE_L2_THRESH, 0x00पूर्ण,
	अणुMAX98373_R2099_BDE_L3_THRESH, 0x00पूर्ण,
	अणुMAX98373_R209A_BDE_L4_THRESH, 0x00पूर्ण,
	अणुMAX98373_R209B_BDE_THRESH_HYST, 0x00पूर्ण,
	अणुMAX98373_R20A8_BDE_L1_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20A9_BDE_L1_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20AA_BDE_L1_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20AB_BDE_L2_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20AC_BDE_L2_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20AD_BDE_L2_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20AE_BDE_L3_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20AF_BDE_L3_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20B0_BDE_L3_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20B1_BDE_L4_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20B2_BDE_L4_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20B3_BDE_L4_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20B4_BDE_INFINITE_HOLD_RELEASE, 0x00पूर्ण,
	अणुMAX98373_R20B5_BDE_EN, 0x00पूर्ण,
	अणुMAX98373_R20B6_BDE_CUR_STATE_READBACK, 0x00पूर्ण,
	अणुMAX98373_R20D1_DHT_CFG, 0x01पूर्ण,
	अणुMAX98373_R20D2_DHT_ATTACK_CFG, 0x02पूर्ण,
	अणुMAX98373_R20D3_DHT_RELEASE_CFG, 0x03पूर्ण,
	अणुMAX98373_R20D4_DHT_EN, 0x00पूर्ण,
	अणुMAX98373_R20E0_LIMITER_THRESH_CFG, 0x00पूर्ण,
	अणुMAX98373_R20E1_LIMITER_ATK_REL_RATES, 0x00पूर्ण,
	अणुMAX98373_R20E2_LIMITER_EN, 0x00पूर्ण,
	अणुMAX98373_R20FE_DEVICE_AUTO_RESTART_CFG, 0x00पूर्ण,
	अणुMAX98373_R20FF_GLOBAL_SHDN, 0x00पूर्ण,
	अणुMAX98373_R21FF_REV_ID, 0x42पूर्ण,
पूर्ण;

अटल पूर्णांक max98373_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक क्रमmat = 0;
	अचिन्हित पूर्णांक invert = 0;

	dev_dbg(component->dev, "%s: fmt 0x%08X\n", __func__, fmt);

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		invert = MAX98373_PCM_MODE_CFG_PCM_BCLKEDGE;
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI invert mode unsupported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98373->regmap,
			   MAX98373_R2026_PCM_CLOCK_RATIO,
			   MAX98373_PCM_MODE_CFG_PCM_BCLKEDGE,
			   invert);

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat = MAX98373_PCM_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat = MAX98373_PCM_FORMAT_LJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		क्रमmat = MAX98373_PCM_FORMAT_TDM_MODE1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat = MAX98373_PCM_FORMAT_TDM_MODE0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98373->regmap,
			   MAX98373_R2024_PCM_DATA_FMT_CFG,
			   MAX98373_PCM_MODE_CFG_FORMAT_MASK,
			   क्रमmat << MAX98373_PCM_MODE_CFG_FORMAT_SHIFT);

	वापस 0;
पूर्ण

/* BCLKs per LRCLK */
अटल स्थिर पूर्णांक bclk_sel_table[] = अणु
	32, 48, 64, 96, 128, 192, 256, 384, 512, 320,
पूर्ण;

अटल पूर्णांक max98373_get_bclk_sel(पूर्णांक bclk)
अणु
	पूर्णांक i;
	/* match BCLKs per LRCLK */
	क्रम (i = 0; i < ARRAY_SIZE(bclk_sel_table); i++) अणु
		अगर (bclk_sel_table[i] == bclk)
			वापस i + 2;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max98373_set_घड़ी(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	/* BCLK/LRCLK ratio calculation */
	पूर्णांक blr_clk_ratio = params_channels(params) * max98373->ch_size;
	पूर्णांक value;

	अगर (!max98373->tdm_mode) अणु
		/* BCLK configuration */
		value = max98373_get_bclk_sel(blr_clk_ratio);
		अगर (!value) अणु
			dev_err(component->dev, "format unsupported %d\n",
				params_क्रमmat(params));
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(max98373->regmap,
				   MAX98373_R2026_PCM_CLOCK_RATIO,
				   MAX98373_PCM_CLK_SETUP_BSEL_MASK,
				   value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max98373_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक sampling_rate = 0;
	अचिन्हित पूर्णांक chan_sz = 0;

	/* pcm mode configuration */
	चयन (snd_pcm_क्रमmat_width(params_क्रमmat(params))) अणु
	हाल 16:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_16;
		अवरोध;
	हाल 24:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_24;
		अवरोध;
	हाल 32:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_32;
		अवरोध;
	शेष:
		dev_err(component->dev, "format unsupported %d\n",
			params_क्रमmat(params));
		जाओ err;
	पूर्ण

	max98373->ch_size = snd_pcm_क्रमmat_width(params_क्रमmat(params));

	regmap_update_bits(max98373->regmap,
			   MAX98373_R2024_PCM_DATA_FMT_CFG,
			   MAX98373_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "format supported %d",
		params_क्रमmat(params));

	/* sampling rate configuration */
	चयन (params_rate(params)) अणु
	हाल 8000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_8000;
		अवरोध;
	हाल 11025:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_11025;
		अवरोध;
	हाल 12000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_12000;
		अवरोध;
	हाल 16000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_16000;
		अवरोध;
	हाल 22050:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_22050;
		अवरोध;
	हाल 24000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_24000;
		अवरोध;
	हाल 32000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_32000;
		अवरोध;
	हाल 44100:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_44100;
		अवरोध;
	हाल 48000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_48000;
		अवरोध;
	हाल 88200:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_88200;
		अवरोध;
	हाल 96000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_96000;
		अवरोध;
	शेष:
		dev_err(component->dev, "rate %d not supported\n",
			params_rate(params));
		जाओ err;
	पूर्ण

	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98373->regmap,
			   MAX98373_R2027_PCM_SR_SETUP_1,
			   MAX98373_PCM_SR_SET1_SR_MASK,
			   sampling_rate);
	regmap_update_bits(max98373->regmap,
			   MAX98373_R2028_PCM_SR_SETUP_2,
			   MAX98373_PCM_SR_SET2_SR_MASK,
			   sampling_rate << MAX98373_PCM_SR_SET2_SR_SHIFT);

	/* set sampling rate of IV */
	अगर (max98373->पूर्णांकerleave_mode &&
	    sampling_rate > MAX98373_PCM_SR_SET1_SR_16000)
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2028_PCM_SR_SETUP_2,
				   MAX98373_PCM_SR_SET2_IVADC_SR_MASK,
				   sampling_rate - 3);
	अन्यथा
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2028_PCM_SR_SETUP_2,
				   MAX98373_PCM_SR_SET2_IVADC_SR_MASK,
				   sampling_rate);

	वापस max98373_set_घड़ी(component, params);
err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max98373_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				 अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				 पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	पूर्णांक bsel = 0;
	अचिन्हित पूर्णांक chan_sz = 0;
	अचिन्हित पूर्णांक mask;
	पूर्णांक x, slot_found;

	अगर (!tx_mask && !rx_mask && !slots && !slot_width)
		max98373->tdm_mode = false;
	अन्यथा
		max98373->tdm_mode = true;

	/* BCLK configuration */
	bsel = max98373_get_bclk_sel(slots * slot_width);
	अगर (bsel == 0) अणु
		dev_err(component->dev, "BCLK %d not supported\n",
			slots * slot_width);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98373->regmap,
			   MAX98373_R2026_PCM_CLOCK_RATIO,
			   MAX98373_PCM_CLK_SETUP_BSEL_MASK,
			   bsel);

	/* Channel size configuration */
	चयन (slot_width) अणु
	हाल 16:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_16;
		अवरोध;
	हाल 24:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_24;
		अवरोध;
	हाल 32:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_32;
		अवरोध;
	शेष:
		dev_err(component->dev, "format unsupported %d\n",
			slot_width);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98373->regmap,
			   MAX98373_R2024_PCM_DATA_FMT_CFG,
			   MAX98373_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	/* Rx slot configuration */
	slot_found = 0;
	mask = rx_mask;
	क्रम (x = 0 ; x < 16 ; x++, mask >>= 1) अणु
		अगर (mask & 0x1) अणु
			अगर (slot_found == 0)
				regmap_update_bits(max98373->regmap,
						   MAX98373_R2029_PCM_TO_SPK_MONO_MIX_1,
						   MAX98373_PCM_TO_SPK_CH0_SRC_MASK, x);
			अन्यथा
				regmap_ग_लिखो(max98373->regmap,
					     MAX98373_R202A_PCM_TO_SPK_MONO_MIX_2,
					     x);
			slot_found++;
			अगर (slot_found > 1)
				अवरोध;
		पूर्ण
	पूर्ण

	/* Tx slot Hi-Z configuration */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2020_PCM_TX_HIZ_EN_1,
		     ~tx_mask & 0xFF);
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2021_PCM_TX_HIZ_EN_2,
		     (~tx_mask & 0xFF00) >> 8);

	वापस 0;
पूर्ण

#घोषणा MAX98373_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा MAX98373_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98373_dai_ops = अणु
	.set_fmt = max98373_dai_set_fmt,
	.hw_params = max98373_dai_hw_params,
	.set_tdm_slot = max98373_dai_tdm_slot,
पूर्ण;

अटल bool max98373_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98373_R2000_SW_RESET:
	हाल MAX98373_R2001_INT_RAW1 ... MAX98373_R200C_INT_EN3:
	हाल MAX98373_R2010_IRQ_CTRL:
	हाल MAX98373_R2014_THERM_WARN_THRESH
		... MAX98373_R2018_THERM_FOLDBACK_EN:
	हाल MAX98373_R201E_PIN_DRIVE_STRENGTH
		... MAX98373_R2036_SOUNDWIRE_CTRL:
	हाल MAX98373_R203D_AMP_DIG_VOL_CTRL ... MAX98373_R2043_AMP_EN:
	हाल MAX98373_R2046_IV_SENSE_ADC_DSP_CFG
		... MAX98373_R2047_IV_SENSE_ADC_EN:
	हाल MAX98373_R2051_MEAS_ADC_SAMPLING_RATE
		... MAX98373_R2056_MEAS_ADC_PVDD_CH_EN:
	हाल MAX98373_R2090_BDE_LVL_HOLD ... MAX98373_R2092_BDE_CLIPPER_MODE:
	हाल MAX98373_R2097_BDE_L1_THRESH
		... MAX98373_R209B_BDE_THRESH_HYST:
	हाल MAX98373_R20A8_BDE_L1_CFG_1 ... MAX98373_R20B3_BDE_L4_CFG_3:
	हाल MAX98373_R20B5_BDE_EN ... MAX98373_R20B6_BDE_CUR_STATE_READBACK:
	हाल MAX98373_R20D1_DHT_CFG ... MAX98373_R20D4_DHT_EN:
	हाल MAX98373_R20E0_LIMITER_THRESH_CFG ... MAX98373_R20E2_LIMITER_EN:
	हाल MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG
		... MAX98373_R20FF_GLOBAL_SHDN:
	हाल MAX98373_R21FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण;

अटल bool max98373_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98373_R2000_SW_RESET ... MAX98373_R2009_INT_FLAG3:
	हाल MAX98373_R203E_AMP_PATH_GAIN:
	हाल MAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK:
	हाल MAX98373_R2055_MEAS_ADC_THERM_CH_READBACK:
	हाल MAX98373_R20B6_BDE_CUR_STATE_READBACK:
	हाल MAX98373_R20FF_GLOBAL_SHDN:
	हाल MAX98373_R21FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा snd_soc_dai_driver max98373_dai[] = अणु
	अणु
		.name = "max98373-aif1",
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MAX98373_RATES,
			.क्रमmats = MAX98373_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "HiFi Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MAX98373_RATES,
			.क्रमmats = MAX98373_FORMATS,
		पूर्ण,
		.ops = &max98373_dai_ops,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max98373_suspend(काष्ठा device *dev)
अणु
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(dev);
	पूर्णांक i;

	/* cache feedback रेजिस्टर values beक्रमe suspend */
	क्रम (i = 0; i < max98373->cache_num; i++)
		regmap_पढ़ो(max98373->regmap, max98373->cache[i].reg, &max98373->cache[i].val);

	regcache_cache_only(max98373->regmap, true);
	regcache_mark_dirty(max98373->regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक max98373_resume(काष्ठा device *dev)
अणु
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(dev);

	regcache_cache_only(max98373->regmap, false);
	max98373_reset(max98373, dev);
	regcache_sync(max98373->regmap);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops max98373_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(max98373_suspend, max98373_resume)
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98373_regmap = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.max_रेजिस्टर = MAX98373_R21FF_REV_ID,
	.reg_शेषs  = max98373_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98373_reg),
	.पढ़ोable_reg = max98373_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = max98373_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max98373_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	पूर्णांक reg = 0;
	पूर्णांक i;
	काष्ठा max98373_priv *max98373 = शून्य;

	max98373 = devm_kzalloc(&i2c->dev, माप(*max98373), GFP_KERNEL);

	अगर (!max98373) अणु
		ret = -ENOMEM;
		वापस ret;
	पूर्ण
	i2c_set_clientdata(i2c, max98373);

	/* update पूर्णांकerleave mode info */
	अगर (device_property_पढ़ो_bool(&i2c->dev, "maxim,interleave_mode"))
		max98373->पूर्णांकerleave_mode = true;
	अन्यथा
		max98373->पूर्णांकerleave_mode = false;

	/* regmap initialization */
	max98373->regmap = devm_regmap_init_i2c(i2c, &max98373_regmap);
	अगर (IS_ERR(max98373->regmap)) अणु
		ret = PTR_ERR(max98373->regmap);
		dev_err(&i2c->dev,
			"Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	max98373->cache_num = ARRAY_SIZE(max98373_i2c_cache_reg);
	max98373->cache = devm_kसुस्मृति(&i2c->dev, max98373->cache_num,
				       माप(*max98373->cache),
				       GFP_KERNEL);

	क्रम (i = 0; i < max98373->cache_num; i++)
		max98373->cache[i].reg = max98373_i2c_cache_reg[i];

	/* voltage/current slot & gpio configuration */
	max98373_slot_config(&i2c->dev, max98373);

	/* Power on device */
	अगर (gpio_is_valid(max98373->reset_gpio)) अणु
		ret = devm_gpio_request(&i2c->dev, max98373->reset_gpio,
					"MAX98373_RESET");
		अगर (ret) अणु
			dev_err(&i2c->dev, "%s: Failed to request gpio %d\n",
				__func__, max98373->reset_gpio);
			वापस -EINVAL;
		पूर्ण
		gpio_direction_output(max98373->reset_gpio, 0);
		msleep(50);
		gpio_direction_output(max98373->reset_gpio, 1);
		msleep(20);
	पूर्ण

	/* Check Revision ID */
	ret = regmap_पढ़ो(max98373->regmap,
			  MAX98373_R21FF_REV_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev,
			"Failed to read: 0x%02X\n", MAX98373_R21FF_REV_ID);
		वापस ret;
	पूर्ण
	dev_info(&i2c->dev, "MAX98373 revisionID: 0x%02X\n", reg);

	/* codec registration */
	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &soc_codec_dev_max98373,
					      max98373_dai, ARRAY_SIZE(max98373_dai));
	अगर (ret < 0)
		dev_err(&i2c->dev, "Failed to register codec: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98373_i2c_id[] = अणु
	अणु "max98373", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max98373_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id max98373_of_match[] = अणु
	अणु .compatible = "maxim,max98373", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98373_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max98373_acpi_match[] = अणु
	अणु "MX98373", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max98373_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98373_i2c_driver = अणु
	.driver = अणु
		.name = "max98373",
		.of_match_table = of_match_ptr(max98373_of_match),
		.acpi_match_table = ACPI_PTR(max98373_acpi_match),
		.pm = &max98373_pm,
	पूर्ण,
	.probe = max98373_i2c_probe,
	.id_table = max98373_i2c_id,
पूर्ण;

module_i2c_driver(max98373_i2c_driver)

MODULE_DESCRIPTION("ALSA SoC MAX98373 driver");
MODULE_AUTHOR("Ryan Lee <ryans.lee@maximintegrated.com>");
MODULE_LICENSE("GPL");
