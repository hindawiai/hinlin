<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max98390.c  --  MAX98390 ALSA Soc Audio driver
 *
 * Copyright (C) 2020 Maxim Integrated Products
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cdev.h>
#समावेश <linux/dmi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "max98390.h"

अटल काष्ठा reg_शेष max98390_reg_शेषs[] = अणु
	अणुMAX98390_INT_EN1, 0xf0पूर्ण,
	अणुMAX98390_INT_EN2, 0x00पूर्ण,
	अणुMAX98390_INT_EN3, 0x00पूर्ण,
	अणुMAX98390_INT_FLAG_CLR1, 0x00पूर्ण,
	अणुMAX98390_INT_FLAG_CLR2, 0x00पूर्ण,
	अणुMAX98390_INT_FLAG_CLR3, 0x00पूर्ण,
	अणुMAX98390_IRQ_CTRL, 0x01पूर्ण,
	अणुMAX98390_CLK_MON, 0x6dपूर्ण,
	अणुMAX98390_DAT_MON, 0x03पूर्ण,
	अणुMAX98390_WDOG_CTRL, 0x00पूर्ण,
	अणुMAX98390_WDOG_RST, 0x00पूर्ण,
	अणुMAX98390_MEAS_ADC_THERM_WARN_THRESH, 0x75पूर्ण,
	अणुMAX98390_MEAS_ADC_THERM_SHDN_THRESH, 0x8cपूर्ण,
	अणुMAX98390_MEAS_ADC_THERM_HYSTERESIS, 0x08पूर्ण,
	अणुMAX98390_PIN_CFG, 0x55पूर्ण,
	अणुMAX98390_PCM_RX_EN_A, 0x00पूर्ण,
	अणुMAX98390_PCM_RX_EN_B, 0x00पूर्ण,
	अणुMAX98390_PCM_TX_EN_A, 0x00पूर्ण,
	अणुMAX98390_PCM_TX_EN_B, 0x00पूर्ण,
	अणुMAX98390_PCM_TX_HIZ_CTRL_A, 0xffपूर्ण,
	अणुMAX98390_PCM_TX_HIZ_CTRL_B, 0xffपूर्ण,
	अणुMAX98390_PCM_CH_SRC_1, 0x00पूर्ण,
	अणुMAX98390_PCM_CH_SRC_2, 0x00पूर्ण,
	अणुMAX98390_PCM_CH_SRC_3, 0x00पूर्ण,
	अणुMAX98390_PCM_MODE_CFG, 0xc0पूर्ण,
	अणुMAX98390_PCM_MASTER_MODE, 0x1cपूर्ण,
	अणुMAX98390_PCM_CLK_SETUP, 0x44पूर्ण,
	अणुMAX98390_PCM_SR_SETUP, 0x08पूर्ण,
	अणुMAX98390_ICC_RX_EN_A, 0x00पूर्ण,
	अणुMAX98390_ICC_RX_EN_B, 0x00पूर्ण,
	अणुMAX98390_ICC_TX_EN_A, 0x00पूर्ण,
	अणुMAX98390_ICC_TX_EN_B, 0x00पूर्ण,
	अणुMAX98390_ICC_HIZ_MANUAL_MODE, 0x00पूर्ण,
	अणुMAX98390_ICC_TX_HIZ_EN_A, 0x00पूर्ण,
	अणुMAX98390_ICC_TX_HIZ_EN_B, 0x00पूर्ण,
	अणुMAX98390_ICC_LNK_EN, 0x00पूर्ण,
	अणुMAX98390_R2039_AMP_DSP_CFG, 0x0fपूर्ण,
	अणुMAX98390_R203A_AMP_EN, 0x81पूर्ण,
	अणुMAX98390_TONE_GEN_DC_CFG, 0x00पूर्ण,
	अणुMAX98390_SPK_SRC_SEL, 0x00पूर्ण,
	अणुMAX98390_SSM_CFG, 0x85पूर्ण,
	अणुMAX98390_MEAS_EN, 0x03पूर्ण,
	अणुMAX98390_MEAS_DSP_CFG, 0x0fपूर्ण,
	अणुMAX98390_BOOST_CTRL0, 0x1cपूर्ण,
	अणुMAX98390_BOOST_CTRL3, 0x01पूर्ण,
	अणुMAX98390_BOOST_CTRL1, 0x40पूर्ण,
	अणुMAX98390_MEAS_ADC_CFG, 0x07पूर्ण,
	अणुMAX98390_MEAS_ADC_BASE_MSB, 0x00पूर्ण,
	अणुMAX98390_MEAS_ADC_BASE_LSB, 0x23पूर्ण,
	अणुMAX98390_ADC_CH0_DIVIDE, 0x00पूर्ण,
	अणुMAX98390_ADC_CH1_DIVIDE, 0x00पूर्ण,
	अणुMAX98390_ADC_CH2_DIVIDE, 0x00पूर्ण,
	अणुMAX98390_ADC_CH0_FILT_CFG, 0x00पूर्ण,
	अणुMAX98390_ADC_CH1_FILT_CFG, 0x00पूर्ण,
	अणुMAX98390_ADC_CH2_FILT_CFG, 0x00पूर्ण,
	अणुMAX98390_PWR_GATE_CTL, 0x2cपूर्ण,
	अणुMAX98390_BROWNOUT_EN, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_INFINITE_HOLD, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_INFINITE_HOLD_CLR, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL_HOLD, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL1_THRESH, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL2_THRESH, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL3_THRESH, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL4_THRESH, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_THRESH_HYSTERYSIS, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_AMP_LIMITER_ATK_REL, 0x1fपूर्ण,
	अणुMAX98390_BROWNOUT_AMP_GAIN_ATK_REL, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_AMP1_CLIP_MODE, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL1_CUR_LIMIT, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL1_AMP1_CTRL1, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL1_AMP1_CTRL2, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL1_AMP1_CTRL3, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL2_CUR_LIMIT, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL2_AMP1_CTRL1, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL2_AMP1_CTRL2, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL2_AMP1_CTRL3, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL3_CUR_LIMIT, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL3_AMP1_CTRL1, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL3_AMP1_CTRL2, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL3_AMP1_CTRL3, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL4_CUR_LIMIT, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL4_AMP1_CTRL1, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL4_AMP1_CTRL2, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LVL4_AMP1_CTRL3, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_ILIM_HLD, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_LIM_HLD, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_CLIP_HLD, 0x00पूर्ण,
	अणुMAX98390_BROWNOUT_GAIN_HLD, 0x00पूर्ण,
	अणुMAX98390_ENV_TRACK_VOUT_HEADROOM, 0x0fपूर्ण,
	अणुMAX98390_ENV_TRACK_BOOST_VOUT_DELAY, 0x80पूर्ण,
	अणुMAX98390_ENV_TRACK_REL_RATE, 0x07पूर्ण,
	अणुMAX98390_ENV_TRACK_HOLD_RATE, 0x07पूर्ण,
	अणुMAX98390_ENV_TRACK_CTRL, 0x01पूर्ण,
	अणुMAX98390_BOOST_BYPASS1, 0x49पूर्ण,
	अणुMAX98390_BOOST_BYPASS2, 0x2bपूर्ण,
	अणुMAX98390_BOOST_BYPASS3, 0x08पूर्ण,
	अणुMAX98390_FET_SCALING1, 0x00पूर्ण,
	अणुMAX98390_FET_SCALING2, 0x03पूर्ण,
	अणुMAX98390_FET_SCALING3, 0x00पूर्ण,
	अणुMAX98390_FET_SCALING4, 0x07पूर्ण,
	अणुMAX98390_SPK_SPEEDUP, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_RELEASE_TIME_1, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_RELEASE_TIME_2, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_ATTACK_TIME_1, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_ATTACK_TIME_2, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_COMPRESSION_RATIO, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_COMPRESSION_THRESHOLD, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_MAKEUPGAIN, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_NOISE_GATE_THRESHOLD, 0x00पूर्ण,
	अणुDSMIG_WBDRC_HPF_ENABLE, 0x00पूर्ण,
	अणुDSMIG_WB_DRC_TEST_SMOOTHER_OUT_EN, 0x00पूर्ण,
	अणुDSMIG_PPR_THRESHOLD, 0x00पूर्ण,
	अणुDSM_STEREO_BASS_CHANNEL_SELECT, 0x00पूर्ण,
	अणुDSM_TPROT_THRESHOLD_BYTE0, 0x00पूर्ण,
	अणुDSM_TPROT_THRESHOLD_BYTE1, 0x00पूर्ण,
	अणुDSM_TPROT_ROOM_TEMPERATURE_BYTE0, 0x00पूर्ण,
	अणुDSM_TPROT_ROOM_TEMPERATURE_BYTE1, 0x00पूर्ण,
	अणुDSM_TPROT_RECIP_RDC_ROOM_BYTE0, 0x00पूर्ण,
	अणुDSM_TPROT_RECIP_RDC_ROOM_BYTE1, 0x00पूर्ण,
	अणुDSM_TPROT_RECIP_RDC_ROOM_BYTE2, 0x00पूर्ण,
	अणुDSM_TPROT_RECIP_TCONST_BYTE0, 0x00पूर्ण,
	अणुDSM_TPROT_RECIP_TCONST_BYTE1, 0x00पूर्ण,
	अणुDSM_TPROT_RECIP_TCONST_BYTE2, 0x00पूर्ण,
	अणुDSM_THERMAL_ATTENUATION_SETTINGS, 0x00पूर्ण,
	अणुDSM_THERMAL_PILOT_TONE_ATTENUATION, 0x00पूर्ण,
	अणुDSM_TPROT_PG_TEMP_THRESH_BYTE0, 0x00पूर्ण,
	अणुDSM_TPROT_PG_TEMP_THRESH_BYTE1, 0x00पूर्ण,
	अणुDSMIG_DEBUZZER_THRESHOLD, 0x00पूर्ण,
	अणुDSMIG_DEBUZZER_ALPHA_COEF_TEST_ONLY, 0x08पूर्ण,
	अणुDSM_VOL_ENA, 0x20पूर्ण,
	अणुDSM_VOL_CTRL, 0xa0पूर्ण,
	अणुDSMIG_EN, 0x00पूर्ण,
	अणुMAX98390_R23E1_DSP_GLOBAL_EN, 0x00पूर्ण,
	अणुMAX98390_R23FF_GLOBAL_EN, 0x00पूर्ण,
पूर्ण;

अटल पूर्णांक max98390_dsm_calibrate(काष्ठा snd_soc_component *component);

अटल पूर्णांक max98390_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक invert = 0;

	dev_dbg(component->dev, "%s: fmt 0x%08X\n", __func__, fmt);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		mode = MAX98390_PCM_MASTER_MODE_SLAVE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		max98390->master = true;
		mode = MAX98390_PCM_MASTER_MODE_MASTER;
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI clock mode unsupported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_MASTER_MODE,
		MAX98390_PCM_MASTER_MODE_MASK,
		mode);

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		invert = MAX98390_PCM_MODE_CFG_PCM_BCLKEDGE;
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI invert mode unsupported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_MODE_CFG,
		MAX98390_PCM_MODE_CFG_PCM_BCLKEDGE,
		invert);

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat = MAX98390_PCM_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat = MAX98390_PCM_FORMAT_LJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		क्रमmat = MAX98390_PCM_FORMAT_TDM_MODE1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat = MAX98390_PCM_FORMAT_TDM_MODE0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_MODE_CFG,
		MAX98390_PCM_MODE_CFG_FORMAT_MASK,
		क्रमmat << MAX98390_PCM_MODE_CFG_FORMAT_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_get_bclk_sel(पूर्णांक bclk)
अणु
	पूर्णांक i;
	/* BCLKs per LRCLK */
	अटल पूर्णांक bclk_sel_table[] = अणु
		32, 48, 64, 96, 128, 192, 256, 320, 384, 512,
	पूर्ण;
	/* match BCLKs per LRCLK */
	क्रम (i = 0; i < ARRAY_SIZE(bclk_sel_table); i++) अणु
		अगर (bclk_sel_table[i] == bclk)
			वापस i + 2;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max98390_set_घड़ी(काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);
	/* codec MCLK rate in master mode */
	अटल पूर्णांक rate_table[] = अणु
		5644800, 6000000, 6144000, 6500000,
		9600000, 11289600, 12000000, 12288000,
		13000000, 19200000,
	पूर्ण;
	/* BCLK/LRCLK ratio calculation */
	पूर्णांक blr_clk_ratio = params_channels(params)
		* snd_pcm_क्रमmat_width(params_क्रमmat(params));
	पूर्णांक value;

	अगर (max98390->master) अणु
		पूर्णांक i;
		/* match rate to बंदst value */
		क्रम (i = 0; i < ARRAY_SIZE(rate_table); i++) अणु
			अगर (rate_table[i] >= max98390->sysclk)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(rate_table)) अणु
			dev_err(component->dev, "failed to find proper clock rate.\n");
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_MASTER_MODE,
			MAX98390_PCM_MASTER_MODE_MCLK_MASK,
			i << MAX98390_PCM_MASTER_MODE_MCLK_RATE_SHIFT);
	पूर्ण

	अगर (!max98390->tdm_mode) अणु
		/* BCLK configuration */
		value = max98390_get_bclk_sel(blr_clk_ratio);
		अगर (!value) अणु
			dev_err(component->dev, "format unsupported %d\n",
				params_क्रमmat(params));
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_CLK_SETUP,
			MAX98390_PCM_CLK_SETUP_BSEL_MASK,
			value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max98390_dai_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component =
		dai->component;
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	अचिन्हित पूर्णांक sampling_rate;
	अचिन्हित पूर्णांक chan_sz;

	/* pcm mode configuration */
	चयन (snd_pcm_क्रमmat_width(params_क्रमmat(params))) अणु
	हाल 16:
		chan_sz = MAX98390_PCM_MODE_CFG_CHANSZ_16;
		अवरोध;
	हाल 24:
		chan_sz = MAX98390_PCM_MODE_CFG_CHANSZ_24;
		अवरोध;
	हाल 32:
		chan_sz = MAX98390_PCM_MODE_CFG_CHANSZ_32;
		अवरोध;
	शेष:
		dev_err(component->dev, "format unsupported %d\n",
			params_क्रमmat(params));
		जाओ err;
	पूर्ण

	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_MODE_CFG,
		MAX98390_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "format supported %d",
		params_क्रमmat(params));

	/* sampling rate configuration */
	चयन (params_rate(params)) अणु
	हाल 8000:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_8000;
		अवरोध;
	हाल 11025:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_11025;
		अवरोध;
	हाल 12000:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_12000;
		अवरोध;
	हाल 16000:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_16000;
		अवरोध;
	हाल 22050:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_22050;
		अवरोध;
	हाल 24000:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_24000;
		अवरोध;
	हाल 32000:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_32000;
		अवरोध;
	हाल 44100:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_44100;
		अवरोध;
	हाल 48000:
		sampling_rate = MAX98390_PCM_SR_SET1_SR_48000;
		अवरोध;
	शेष:
		dev_err(component->dev, "rate %d not supported\n",
			params_rate(params));
		जाओ err;
	पूर्ण

	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_SR_SETUP,
		MAX98390_PCM_SR_SET1_SR_MASK,
		sampling_rate);

	वापस max98390_set_घड़ी(component, params);
err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max98390_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
		पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	पूर्णांक bsel;
	अचिन्हित पूर्णांक chan_sz;

	अगर (!tx_mask && !rx_mask && !slots && !slot_width)
		max98390->tdm_mode = false;
	अन्यथा
		max98390->tdm_mode = true;

	dev_dbg(component->dev,
		"Tdm mode : %d\n", max98390->tdm_mode);

	/* BCLK configuration */
	bsel = max98390_get_bclk_sel(slots * slot_width);
	अगर (!bsel) अणु
		dev_err(component->dev, "BCLK %d not supported\n",
			slots * slot_width);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_CLK_SETUP,
		MAX98390_PCM_CLK_SETUP_BSEL_MASK,
		bsel);

	/* Channel size configuration */
	चयन (slot_width) अणु
	हाल 16:
		chan_sz = MAX98390_PCM_MODE_CFG_CHANSZ_16;
		अवरोध;
	हाल 24:
		chan_sz = MAX98390_PCM_MODE_CFG_CHANSZ_24;
		अवरोध;
	हाल 32:
		chan_sz = MAX98390_PCM_MODE_CFG_CHANSZ_32;
		अवरोध;
	शेष:
		dev_err(component->dev, "format unsupported %d\n",
			slot_width);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98390->regmap,
		MAX98390_PCM_MODE_CFG,
		MAX98390_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	/* Rx slot configuration */
	regmap_ग_लिखो(max98390->regmap,
		MAX98390_PCM_RX_EN_A,
		rx_mask & 0xFF);
	regmap_ग_लिखो(max98390->regmap,
		MAX98390_PCM_RX_EN_B,
		(rx_mask & 0xFF00) >> 8);

	/* Tx slot Hi-Z configuration */
	regmap_ग_लिखो(max98390->regmap,
		MAX98390_PCM_TX_HIZ_CTRL_A,
		~tx_mask & 0xFF);
	regmap_ग_लिखो(max98390->regmap,
		MAX98390_PCM_TX_HIZ_CTRL_B,
		(~tx_mask & 0xFF00) >> 8);

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	max98390->sysclk = freq;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops max98390_dai_ops = अणु
	.set_sysclk = max98390_dai_set_sysclk,
	.set_fmt = max98390_dai_set_fmt,
	.hw_params = max98390_dai_hw_params,
	.set_tdm_slot = max98390_dai_tdm_slot,
पूर्ण;

अटल पूर्णांक max98390_dac_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(max98390->regmap,
			MAX98390_R203A_AMP_EN,
			MAX98390_AMP_EN_MASK, 1);
		regmap_update_bits(max98390->regmap,
			MAX98390_R23FF_GLOBAL_EN,
			MAX98390_GLOBAL_EN_MASK, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(max98390->regmap,
			MAX98390_R23FF_GLOBAL_EN,
			MAX98390_GLOBAL_EN_MASK, 0);
		regmap_update_bits(max98390->regmap,
			MAX98390_R203A_AMP_EN,
			MAX98390_AMP_EN_MASK, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर max98390_चयन_text[] = अणु
	"Left", "Right", "LeftRight"पूर्ण;

अटल स्थिर अक्षर * स्थिर max98390_boost_voltage_text[] = अणु
	"6.5V", "6.625V", "6.75V", "6.875V", "7V", "7.125V", "7.25V", "7.375V",
	"7.5V", "7.625V", "7.75V", "7.875V", "8V", "8.125V", "8.25V", "8.375V",
	"8.5V", "8.625V", "8.75V", "8.875V", "9V", "9.125V", "9.25V", "9.375V",
	"9.5V", "9.625V", "9.75V", "9.875V", "10V"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98390_boost_voltage,
		MAX98390_BOOST_CTRL0, 0,
		max98390_boost_voltage_text);

अटल DECLARE_TLV_DB_SCALE(max98390_spk_tlv, 300, 300, 0);
अटल DECLARE_TLV_DB_SCALE(max98390_digital_tlv, -8000, 50, 0);

अटल स्थिर अक्षर * स्थिर max98390_current_limit_text[] = अणु
	"0.00A", "0.50A", "1.00A", "1.05A", "1.10A", "1.15A", "1.20A", "1.25A",
	"1.30A", "1.35A", "1.40A", "1.45A", "1.50A", "1.55A", "1.60A", "1.65A",
	"1.70A", "1.75A", "1.80A", "1.85A", "1.90A", "1.95A", "2.00A", "2.05A",
	"2.10A", "2.15A", "2.20A", "2.25A", "2.30A", "2.35A", "2.40A", "2.45A",
	"2.50A", "2.55A", "2.60A", "2.65A", "2.70A", "2.75A", "2.80A", "2.85A",
	"2.90A", "2.95A", "3.00A", "3.05A", "3.10A", "3.15A", "3.20A", "3.25A",
	"3.30A", "3.35A", "3.40A", "3.45A", "3.50A", "3.55A", "3.60A", "3.65A",
	"3.70A", "3.75A", "3.80A", "3.85A", "3.90A", "3.95A", "4.00A", "4.05A",
	"4.10A"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98390_current_limit,
		MAX98390_BOOST_CTRL1, 0,
		max98390_current_limit_text);

अटल पूर्णांक max98390_ref_rdc_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	max98390->ref_rdc_value = ucontrol->value.पूर्णांकeger.value[0];

	regmap_ग_लिखो(max98390->regmap, DSM_TPROT_RECIP_RDC_ROOM_BYTE0,
		max98390->ref_rdc_value & 0x000000ff);
	regmap_ग_लिखो(max98390->regmap, DSM_TPROT_RECIP_RDC_ROOM_BYTE1,
		(max98390->ref_rdc_value >> 8) & 0x000000ff);
	regmap_ग_लिखो(max98390->regmap, DSM_TPROT_RECIP_RDC_ROOM_BYTE2,
		(max98390->ref_rdc_value >> 16) & 0x000000ff);

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_ref_rdc_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = max98390->ref_rdc_value;

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_ambient_temp_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	max98390->ambient_temp_value = ucontrol->value.पूर्णांकeger.value[0];

	regmap_ग_लिखो(max98390->regmap, DSM_TPROT_ROOM_TEMPERATURE_BYTE1,
		(max98390->ambient_temp_value >> 8) & 0x000000ff);
	regmap_ग_लिखो(max98390->regmap, DSM_TPROT_ROOM_TEMPERATURE_BYTE0,
		(max98390->ambient_temp_value) & 0x000000ff);

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_ambient_temp_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = max98390->ambient_temp_value;

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_adaptive_rdc_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);

	dev_warn(component->dev, "Put adaptive rdc not supported\n");

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_adaptive_rdc_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक rdc, rdc0;
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	regmap_पढ़ो(max98390->regmap, THERMAL_RDC_RD_BACK_BYTE1, &rdc);
	regmap_पढ़ो(max98390->regmap, THERMAL_RDC_RD_BACK_BYTE0, &rdc0);
	ucontrol->value.पूर्णांकeger.value[0] = rdc0 | rdc << 8;

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_dsm_calib_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/* Do nothing */
	वापस 0;
पूर्ण

अटल पूर्णांक max98390_dsm_calib_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);

	max98390_dsm_calibrate(component);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new max98390_snd_controls[] = अणु
	SOC_SINGLE_TLV("Digital Volume", DSM_VOL_CTRL,
		0, 184, 0,
		max98390_digital_tlv),
	SOC_SINGLE_TLV("Speaker Volume", MAX98390_R203D_SPK_GAIN,
		0, 6, 0,
		max98390_spk_tlv),
	SOC_SINGLE("Ramp Up Bypass Switch", MAX98390_R2039_AMP_DSP_CFG,
		MAX98390_AMP_DSP_CFG_RMP_UP_SHIFT, 1, 0),
	SOC_SINGLE("Ramp Down Bypass Switch", MAX98390_R2039_AMP_DSP_CFG,
		MAX98390_AMP_DSP_CFG_RMP_DN_SHIFT, 1, 0),
	SOC_SINGLE("Boost Clock Phase", MAX98390_BOOST_CTRL3,
		MAX98390_BOOST_CLK_PHASE_CFG_SHIFT, 3, 0),
	SOC_ENUM("Boost Output Voltage", max98390_boost_voltage),
	SOC_ENUM("Current Limit", max98390_current_limit),
	SOC_SINGLE_EXT("DSM Rdc", SND_SOC_NOPM, 0, 0xffffff, 0,
		max98390_ref_rdc_get, max98390_ref_rdc_put),
	SOC_SINGLE_EXT("DSM Ambient Temp", SND_SOC_NOPM, 0, 0xffff, 0,
		max98390_ambient_temp_get, max98390_ambient_temp_put),
	SOC_SINGLE_EXT("DSM Adaptive Rdc", SND_SOC_NOPM, 0, 0xffff, 0,
		max98390_adaptive_rdc_get, max98390_adaptive_rdc_put),
	SOC_SINGLE_EXT("DSM Calibration", SND_SOC_NOPM, 0, 1, 0,
		max98390_dsm_calib_get, max98390_dsm_calib_put),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत dai_sel_क्रमागत =
	SOC_ENUM_SINGLE(MAX98390_PCM_CH_SRC_1,
		MAX98390_PCM_RX_CH_SRC_SHIFT,
		3, max98390_चयन_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98390_dai_controls =
	SOC_DAPM_ENUM("DAI Sel", dai_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget max98390_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC_E("Amp Enable", "HiFi Playback",
		SND_SOC_NOPM, 0, 0, max98390_dac_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("DAI Sel Mux", SND_SOC_NOPM, 0, 0,
		&max98390_dai_controls),
	SND_SOC_DAPM_OUTPUT("BE_OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98390_audio_map[] = अणु
	/* Plabyack */
	अणु"DAI Sel Mux", "Left", "Amp Enable"पूर्ण,
	अणु"DAI Sel Mux", "Right", "Amp Enable"पूर्ण,
	अणु"DAI Sel Mux", "LeftRight", "Amp Enable"पूर्ण,
	अणु"BE_OUT", शून्य, "DAI Sel Mux"पूर्ण,
पूर्ण;

अटल bool max98390_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98390_SOFTWARE_RESET ... MAX98390_INT_EN3:
	हाल MAX98390_IRQ_CTRL ... MAX98390_WDOG_CTRL:
	हाल MAX98390_MEAS_ADC_THERM_WARN_THRESH
		... MAX98390_BROWNOUT_INFINITE_HOLD:
	हाल MAX98390_BROWNOUT_LVL_HOLD ... DSMIG_DEBUZZER_THRESHOLD:
	हाल DSM_VOL_ENA ... MAX98390_R24FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण;

अटल bool max98390_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98390_SOFTWARE_RESET ... MAX98390_INT_EN3:
	हाल MAX98390_MEAS_ADC_CH0_READ ... MAX98390_MEAS_ADC_CH2_READ:
	हाल MAX98390_PWR_GATE_STATUS ... MAX98390_BROWNOUT_STATUS:
	हाल MAX98390_BROWNOUT_LOWEST_STATUS:
	हाल MAX98390_ENV_TRACK_BOOST_VOUT_READ:
	हाल DSM_STBASS_HPF_B0_BYTE0 ... DSM_DEBUZZER_ATTACK_TIME_BYTE2:
	हाल THERMAL_RDC_RD_BACK_BYTE1 ... DSMIG_DEBUZZER_THRESHOLD:
	हाल DSM_THERMAL_GAIN ... DSM_WBDRC_GAIN:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#घोषणा MAX98390_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा MAX98390_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver max98390_dai[] = अणु
	अणु
		.name = "max98390-aif1",
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MAX98390_RATES,
			.क्रमmats = MAX98390_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "HiFi Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MAX98390_RATES,
			.क्रमmats = MAX98390_FORMATS,
		पूर्ण,
		.ops = &max98390_dai_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक max98390_dsm_init(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	पूर्णांक param_size, param_start_addr;
	अक्षर filename[128];
	स्थिर अक्षर *venकरोr, *product;
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा firmware *fw;
	अक्षर *dsm_param;

	venकरोr = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);

	अगर (venकरोr && product) अणु
		snम_लिखो(filename, माप(filename), "dsm_param_%s_%s.bin",
			venकरोr, product);
	पूर्ण अन्यथा अणु
		प्र_लिखो(filename, "dsm_param.bin");
	पूर्ण
	ret = request_firmware(&fw, filename, component->dev);
	अगर (ret) अणु
		ret = request_firmware(&fw, "dsm_param.bin", component->dev);
		अगर (ret)
			जाओ err;
	पूर्ण

	dev_dbg(component->dev,
		"max98390: param fw size %zd\n",
		fw->size);
	अगर (fw->size < MAX98390_DSM_PARAM_MIN_SIZE) अणु
		dev_err(component->dev,
			"param fw is invalid.\n");
		ret = -EINVAL;
		जाओ err_alloc;
	पूर्ण
	dsm_param = (अक्षर *)fw->data;
	param_start_addr = (dsm_param[0] & 0xff) | (dsm_param[1] & 0xff) << 8;
	param_size = (dsm_param[2] & 0xff) | (dsm_param[3] & 0xff) << 8;
	अगर (param_size > MAX98390_DSM_PARAM_MAX_SIZE ||
		param_start_addr < MAX98390_IRQ_CTRL ||
		fw->size < param_size + MAX98390_DSM_PAYLOAD_OFFSET) अणु
		dev_err(component->dev,
			"param fw is invalid.\n");
		ret = -EINVAL;
		जाओ err_alloc;
	पूर्ण
	regmap_ग_लिखो(max98390->regmap, MAX98390_R203A_AMP_EN, 0x80);
	dsm_param += MAX98390_DSM_PAYLOAD_OFFSET;
	regmap_bulk_ग_लिखो(max98390->regmap, param_start_addr,
		dsm_param, param_size);
	regmap_ग_लिखो(max98390->regmap, MAX98390_R23E1_DSP_GLOBAL_EN, 0x01);

err_alloc:
	release_firmware(fw);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक max98390_dsm_calibrate(काष्ठा snd_soc_component *component)
अणु
	अचिन्हित पूर्णांक rdc, rdc_cal_result, temp;
	अचिन्हित पूर्णांक rdc_पूर्णांकeger, rdc_factor;
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(max98390->regmap, MAX98390_R203A_AMP_EN, 0x81);
	regmap_ग_लिखो(max98390->regmap, MAX98390_R23FF_GLOBAL_EN, 0x01);

	regmap_पढ़ो(max98390->regmap,
		THERMAL_RDC_RD_BACK_BYTE1, &rdc);
	regmap_पढ़ो(max98390->regmap,
		THERMAL_RDC_RD_BACK_BYTE0, &rdc_cal_result);
	rdc_cal_result |= (rdc << 8) & 0x0000FFFF;
	अगर (rdc_cal_result)
		max98390->ref_rdc_value = 268435456U / rdc_cal_result;

	regmap_पढ़ो(max98390->regmap, MAX98390_MEAS_ADC_CH2_READ, &temp);
	max98390->ambient_temp_value = temp * 52 - 1188;

	rdc_पूर्णांकeger =  rdc_cal_result * 937  / 65536;
	rdc_factor = ((rdc_cal_result * 937 * 100) / 65536)
					- (rdc_पूर्णांकeger * 100);

	dev_info(component->dev, "rdc resistance about %d.%02d ohm, reg=0x%X temp reg=0x%X\n",
		 rdc_पूर्णांकeger, rdc_factor, rdc_cal_result, temp);

	regmap_ग_लिखो(max98390->regmap, MAX98390_R23FF_GLOBAL_EN, 0x00);
	regmap_ग_लिखो(max98390->regmap, MAX98390_R203A_AMP_EN, 0x80);

	वापस 0;
पूर्ण

अटल व्योम max98390_init_regs(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(max98390->regmap, MAX98390_CLK_MON, 0x6f);
	regmap_ग_लिखो(max98390->regmap, MAX98390_DAT_MON, 0x00);
	regmap_ग_लिखो(max98390->regmap, MAX98390_PWR_GATE_CTL, 0x00);
	regmap_ग_लिखो(max98390->regmap, MAX98390_PCM_RX_EN_A, 0x03);
	regmap_ग_लिखो(max98390->regmap, MAX98390_ENV_TRACK_VOUT_HEADROOM, 0x0e);
	regmap_ग_लिखो(max98390->regmap, MAX98390_BOOST_BYPASS1, 0x46);
	regmap_ग_लिखो(max98390->regmap, MAX98390_FET_SCALING3, 0x03);

	/* voltage, current slot configuration */
	regmap_ग_लिखो(max98390->regmap,
		MAX98390_PCM_CH_SRC_2,
		(max98390->i_l_slot << 4 |
		max98390->v_l_slot)&0xFF);

	अगर (max98390->v_l_slot < 8) अणु
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_HIZ_CTRL_A,
			1 << max98390->v_l_slot, 0);
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_EN_A,
			1 << max98390->v_l_slot,
			1 << max98390->v_l_slot);
	पूर्ण अन्यथा अणु
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_HIZ_CTRL_B,
			1 << (max98390->v_l_slot - 8), 0);
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_EN_B,
			1 << (max98390->v_l_slot - 8),
			1 << (max98390->v_l_slot - 8));
	पूर्ण

	अगर (max98390->i_l_slot < 8) अणु
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_HIZ_CTRL_A,
			1 << max98390->i_l_slot, 0);
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_EN_A,
			1 << max98390->i_l_slot,
			1 << max98390->i_l_slot);
	पूर्ण अन्यथा अणु
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_HIZ_CTRL_B,
			1 << (max98390->i_l_slot - 8), 0);
		regmap_update_bits(max98390->regmap,
			MAX98390_PCM_TX_EN_B,
			1 << (max98390->i_l_slot - 8),
			1 << (max98390->i_l_slot - 8));
	पूर्ण
पूर्ण

अटल पूर्णांक max98390_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98390_priv *max98390 =
		snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(max98390->regmap, MAX98390_SOFTWARE_RESET, 0x01);
	/* Sleep reset settle समय */
	msleep(20);

	/* Amp init setting */
	max98390_init_regs(component);
	/* Update dsm bin param */
	max98390_dsm_init(component);

	/* Dsm Setting */
	अगर (max98390->ref_rdc_value) अणु
		regmap_ग_लिखो(max98390->regmap, DSM_TPROT_RECIP_RDC_ROOM_BYTE0,
			max98390->ref_rdc_value & 0x000000ff);
		regmap_ग_लिखो(max98390->regmap, DSM_TPROT_RECIP_RDC_ROOM_BYTE1,
			(max98390->ref_rdc_value >> 8) & 0x000000ff);
		regmap_ग_लिखो(max98390->regmap, DSM_TPROT_RECIP_RDC_ROOM_BYTE2,
			(max98390->ref_rdc_value >> 16) & 0x000000ff);
	पूर्ण
	अगर (max98390->ambient_temp_value) अणु
		regmap_ग_लिखो(max98390->regmap, DSM_TPROT_ROOM_TEMPERATURE_BYTE1,
			(max98390->ambient_temp_value >> 8) & 0x000000ff);
		regmap_ग_लिखो(max98390->regmap, DSM_TPROT_ROOM_TEMPERATURE_BYTE0,
			(max98390->ambient_temp_value) & 0x000000ff);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max98390_suspend(काष्ठा device *dev)
अणु
	काष्ठा max98390_priv *max98390 = dev_get_drvdata(dev);

	dev_dbg(dev, "%s:Enter\n", __func__);

	regcache_cache_only(max98390->regmap, true);
	regcache_mark_dirty(max98390->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक max98390_resume(काष्ठा device *dev)
अणु
	काष्ठा max98390_priv *max98390 = dev_get_drvdata(dev);

	dev_dbg(dev, "%s:Enter\n", __func__);

	regcache_cache_only(max98390->regmap, false);
	regcache_sync(max98390->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops max98390_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(max98390_suspend, max98390_resume)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_max98390 = अणु
	.probe			= max98390_probe,
	.controls		= max98390_snd_controls,
	.num_controls		= ARRAY_SIZE(max98390_snd_controls),
	.dapm_widमाला_लो		= max98390_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98390_dapm_widमाला_लो),
	.dapm_routes		= max98390_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98390_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98390_regmap = अणु
	.reg_bits         = 16,
	.val_bits         = 8,
	.max_रेजिस्टर     = MAX98390_R24FF_REV_ID,
	.reg_शेषs     = max98390_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(max98390_reg_शेषs),
	.पढ़ोable_reg	  = max98390_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg	  = max98390_अस्थिर_reg,
	.cache_type       = REGCACHE_RBTREE,
पूर्ण;

अटल व्योम max98390_slot_config(काष्ठा i2c_client *i2c,
	काष्ठा max98390_priv *max98390)
अणु
	पूर्णांक value;
	काष्ठा device *dev = &i2c->dev;

	अगर (!device_property_पढ़ो_u32(dev, "maxim,vmon-slot-no", &value))
		max98390->v_l_slot = value & 0xF;
	अन्यथा
		max98390->v_l_slot = 0;

	अगर (!device_property_पढ़ो_u32(dev, "maxim,imon-slot-no", &value))
		max98390->i_l_slot = value & 0xF;
	अन्यथा
		max98390->i_l_slot = 1;
पूर्ण

अटल पूर्णांक max98390_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	पूर्णांक reg = 0;

	काष्ठा max98390_priv *max98390 = शून्य;
	काष्ठा i2c_adapter *adapter = to_i2c_adapter(i2c->dev.parent);

	ret = i2c_check_functionality(adapter,
		I2C_FUNC_SMBUS_BYTE
		| I2C_FUNC_SMBUS_BYTE_DATA);
	अगर (!ret) अणु
		dev_err(&i2c->dev, "I2C check functionality failed\n");
		वापस -ENXIO;
	पूर्ण

	max98390 = devm_kzalloc(&i2c->dev, माप(*max98390), GFP_KERNEL);
	अगर (!max98390) अणु
		ret = -ENOMEM;
		वापस ret;
	पूर्ण
	i2c_set_clientdata(i2c, max98390);

	ret = device_property_पढ़ो_u32(&i2c->dev, "maxim,temperature_calib",
				       &max98390->ambient_temp_value);
	अगर (ret) अणु
		dev_info(&i2c->dev,
			 "no optional property 'temperature_calib' found, default:\n");
	पूर्ण
	ret = device_property_पढ़ो_u32(&i2c->dev, "maxim,r0_calib",
				       &max98390->ref_rdc_value);
	अगर (ret) अणु
		dev_info(&i2c->dev,
			 "no optional property 'r0_calib' found, default:\n");
	पूर्ण

	dev_info(&i2c->dev,
		"%s: r0_calib: 0x%x,temperature_calib: 0x%x",
		__func__, max98390->ref_rdc_value,
		max98390->ambient_temp_value);

	/* voltage/current slot configuration */
	max98390_slot_config(i2c, max98390);

	/* regmap initialization */
	max98390->regmap = devm_regmap_init_i2c(i2c, &max98390_regmap);
	अगर (IS_ERR(max98390->regmap)) अणु
		ret = PTR_ERR(max98390->regmap);
		dev_err(&i2c->dev,
			"Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Check Revision ID */
	ret = regmap_पढ़ो(max98390->regmap,
		MAX98390_R24FF_REV_ID, &reg);
	अगर (ret) अणु
		dev_err(&i2c->dev,
			"ret=%d, Failed to read: 0x%02X\n",
			ret, MAX98390_R24FF_REV_ID);
		वापस ret;
	पूर्ण
	dev_info(&i2c->dev, "MAX98390 revisionID: 0x%02X\n", reg);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_codec_dev_max98390,
			max98390_dai, ARRAY_SIZE(max98390_dai));

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98390_i2c_id[] = अणु
	अणु "max98390", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max98390_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id max98390_of_match[] = अणु
	अणु .compatible = "maxim,max98390", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98390_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max98390_acpi_match[] = अणु
	अणु "MX98390", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max98390_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98390_i2c_driver = अणु
	.driver = अणु
		.name = "max98390",
		.of_match_table = of_match_ptr(max98390_of_match),
		.acpi_match_table = ACPI_PTR(max98390_acpi_match),
		.pm = &max98390_pm,
	पूर्ण,
	.probe = max98390_i2c_probe,
	.id_table = max98390_i2c_id,
पूर्ण;

module_i2c_driver(max98390_i2c_driver)

MODULE_DESCRIPTION("ALSA SoC MAX98390 driver");
MODULE_AUTHOR("Steve Lee <steves.lee@maximintegrated.com>");
MODULE_LICENSE("GPL");
