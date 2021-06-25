<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC Texas Instruments TAS2770 20-W Digital Input Mono Class-D
// Audio Amplअगरier with Speaker I/V Sense
//
// Copyright (C) 2016-2017 Texas Instruments Incorporated - https://www.ti.com/
//	Author: Tracy Yi <tracy-yi@ti.com>
//	Frank Shi <shअगरu0704@thundersoft.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/firmware.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "tas2770.h"

#घोषणा TAS2770_MDELAY 0xFFFFFFFE

अटल व्योम tas2770_reset(काष्ठा tas2770_priv *tas2770)
अणु
	अगर (tas2770->reset_gpio) अणु
		gpiod_set_value_cansleep(tas2770->reset_gpio, 0);
		msleep(20);
		gpiod_set_value_cansleep(tas2770->reset_gpio, 1);
	पूर्ण

	snd_soc_component_ग_लिखो(tas2770->component, TAS2770_SW_RST,
		TAS2770_RST);
पूर्ण

अटल पूर्णांक tas2770_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा tas2770_priv *tas2770 =
			snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
					      TAS2770_PWR_CTRL_MASK,
					      TAS2770_PWR_CTRL_ACTIVE);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
					      TAS2770_PWR_CTRL_MASK,
					      TAS2770_PWR_CTRL_MUTE);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
					      TAS2770_PWR_CTRL_MASK,
					      TAS2770_PWR_CTRL_SHUTDOWN);
		अवरोध;

	शेष:
		dev_err(tas2770->dev, "wrong power level setting %d\n", level);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas2770_codec_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2770_priv *tas2770 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	regcache_cache_only(tas2770->regmap, true);
	regcache_mark_dirty(tas2770->regmap);

	अगर (tas2770->sdz_gpio) अणु
		gpiod_set_value_cansleep(tas2770->sdz_gpio, 0);
	पूर्ण अन्यथा अणु
		ret = snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
						    TAS2770_PWR_CTRL_MASK,
						    TAS2770_PWR_CTRL_SHUTDOWN);
		अगर (ret < 0) अणु
			regcache_cache_only(tas2770->regmap, false);
			regcache_sync(tas2770->regmap);
			वापस ret;
		पूर्ण

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tas2770_codec_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2770_priv *tas2770 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (tas2770->sdz_gpio) अणु
		gpiod_set_value_cansleep(tas2770->sdz_gpio, 1);
	पूर्ण अन्यथा अणु
		ret = snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
						    TAS2770_PWR_CTRL_MASK,
						    TAS2770_PWR_CTRL_ACTIVE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	regcache_cache_only(tas2770->regmap, false);

	वापस regcache_sync(tas2770->regmap);
पूर्ण
#अन्यथा
#घोषणा tas2770_codec_suspend शून्य
#घोषणा tas2770_codec_resume शून्य
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर tas2770_ASI1_src[] = अणु
	"I2C offset", "Left", "Right", "LeftRightDiv2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	tas2770_ASI1_src_क्रमागत, TAS2770_TDM_CFG_REG2,
	4, tas2770_ASI1_src);

अटल स्थिर काष्ठा snd_kcontrol_new tas2770_asi1_mux =
	SOC_DAPM_ENUM("ASI1 Source", tas2770_ASI1_src_क्रमागत);

अटल पूर्णांक tas2770_dac_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	काष्ठा tas2770_priv *tas2770 =
			snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		ret = snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
						    TAS2770_PWR_CTRL_MASK,
						    TAS2770_PWR_CTRL_MUTE);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		ret = snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
						    TAS2770_PWR_CTRL_MASK,
						    TAS2770_PWR_CTRL_SHUTDOWN);
		अवरोध;
	शेष:
		dev_err(tas2770->dev, "Not supported evevt\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new isense_चयन =
	SOC_DAPM_SINGLE("Switch", TAS2770_PWR_CTRL, 3, 1, 1);
अटल स्थिर काष्ठा snd_kcontrol_new vsense_चयन =
	SOC_DAPM_SINGLE("Switch", TAS2770_PWR_CTRL, 2, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget tas2770_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sel", SND_SOC_NOPM, 0, 0, &tas2770_asi1_mux),
	SND_SOC_DAPM_SWITCH("ISENSE", TAS2770_PWR_CTRL, 3, 1, &isense_चयन),
	SND_SOC_DAPM_SWITCH("VSENSE", TAS2770_PWR_CTRL, 2, 1, &vsense_चयन),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, tas2770_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
	SND_SOC_DAPM_SIGGEN("VMON"),
	SND_SOC_DAPM_SIGGEN("IMON")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas2770_audio_map[] = अणु
	अणु"ASI1 Sel", "I2C offset", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Left", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Right", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "LeftRightDiv2", "ASI1"पूर्ण,
	अणु"DAC", शून्य, "ASI1 Sel"पूर्ण,
	अणु"OUT", शून्य, "DAC"पूर्ण,
	अणु"ISENSE", "Switch", "IMON"पूर्ण,
	अणु"VSENSE", "Switch", "VMON"पूर्ण,
पूर्ण;

अटल पूर्णांक tas2770_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	अगर (mute)
		ret = snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
						    TAS2770_PWR_CTRL_MASK,
						    TAS2770_PWR_CTRL_MUTE);
	अन्यथा
		ret = snd_soc_component_update_bits(component, TAS2770_PWR_CTRL,
						    TAS2770_PWR_CTRL_MASK,
						    TAS2770_PWR_CTRL_ACTIVE);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2770_set_bitwidth(काष्ठा tas2770_priv *tas2770, पूर्णांक bitwidth)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_component *component = tas2770->component;

	चयन (bitwidth) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG2,
						    TAS2770_TDM_CFG_REG2_RXW_MASK,
						    TAS2770_TDM_CFG_REG2_RXW_16BITS);
		tas2770->v_sense_slot = tas2770->i_sense_slot + 2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG2,
						    TAS2770_TDM_CFG_REG2_RXW_MASK,
						    TAS2770_TDM_CFG_REG2_RXW_24BITS);
		tas2770->v_sense_slot = tas2770->i_sense_slot + 4;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG2,
						    TAS2770_TDM_CFG_REG2_RXW_MASK,
						    TAS2770_TDM_CFG_REG2_RXW_32BITS);
		tas2770->v_sense_slot = tas2770->i_sense_slot + 4;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG5,
					    TAS2770_TDM_CFG_REG5_VSNS_MASK |
					    TAS2770_TDM_CFG_REG5_50_MASK,
					    TAS2770_TDM_CFG_REG5_VSNS_ENABLE |
		tas2770->v_sense_slot);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG6,
					    TAS2770_TDM_CFG_REG6_ISNS_MASK |
					    TAS2770_TDM_CFG_REG6_50_MASK,
					    TAS2770_TDM_CFG_REG6_ISNS_ENABLE |
					    tas2770->i_sense_slot);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2770_set_samplerate(काष्ठा tas2770_priv *tas2770, पूर्णांक samplerate)
अणु
	काष्ठा snd_soc_component *component = tas2770->component;
	पूर्णांक ramp_rate_val;
	पूर्णांक ret;

	चयन (samplerate) अणु
	हाल 48000:
		ramp_rate_val = TAS2770_TDM_CFG_REG0_SMP_48KHZ |
				TAS2770_TDM_CFG_REG0_31_44_1_48KHZ;
		अवरोध;
	हाल 44100:
		ramp_rate_val = TAS2770_TDM_CFG_REG0_SMP_44_1KHZ |
				TAS2770_TDM_CFG_REG0_31_44_1_48KHZ;
		अवरोध;
	हाल 96000:
		ramp_rate_val = TAS2770_TDM_CFG_REG0_SMP_48KHZ |
				TAS2770_TDM_CFG_REG0_31_88_2_96KHZ;
		अवरोध;
	हाल 88200:
		ramp_rate_val = TAS2770_TDM_CFG_REG0_SMP_44_1KHZ |
				TAS2770_TDM_CFG_REG0_31_88_2_96KHZ;
		अवरोध;
	हाल 19200:
		ramp_rate_val = TAS2770_TDM_CFG_REG0_SMP_48KHZ |
				TAS2770_TDM_CFG_REG0_31_176_4_192KHZ;
		अवरोध;
	हाल 17640:
		ramp_rate_val = TAS2770_TDM_CFG_REG0_SMP_44_1KHZ |
				TAS2770_TDM_CFG_REG0_31_176_4_192KHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG0,
					    TAS2770_TDM_CFG_REG0_SMP_MASK |
					    TAS2770_TDM_CFG_REG0_31_MASK,
					    ramp_rate_val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2770_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2770_priv *tas2770 =
			snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = tas2770_set_bitwidth(tas2770, params_क्रमmat(params));
	अगर (ret)
		वापस ret;

	वापस tas2770_set_samplerate(tas2770, params_rate(params));
पूर्ण

अटल पूर्णांक tas2770_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2770_priv *tas2770 =
			snd_soc_component_get_drvdata(component);
	u8 tdm_rx_start_slot = 0, asi_cfg_1 = 0;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		dev_err(tas2770->dev, "ASI format master is not found\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		asi_cfg_1 |= TAS2770_TDM_CFG_REG1_RX_RSING;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		asi_cfg_1 |= TAS2770_TDM_CFG_REG1_RX_FALING;
		अवरोध;
	शेष:
		dev_err(tas2770->dev, "ASI format Inverse is not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG1,
					    TAS2770_TDM_CFG_REG1_RX_MASK,
					    asi_cfg_1);
	अगर (ret < 0)
		वापस ret;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		tdm_rx_start_slot = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		tdm_rx_start_slot = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		tdm_rx_start_slot = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		tdm_rx_start_slot = 0;
		अवरोध;
	शेष:
		dev_err(tas2770->dev,
			"DAI Format is not found, fmt=0x%x\n", fmt);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG1,
					    TAS2770_TDM_CFG_REG1_MASK,
					    (tdm_rx_start_slot << TAS2770_TDM_CFG_REG1_51_SHIFT));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2770_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask,
				पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक left_slot, right_slot;
	पूर्णांक ret;

	अगर (tx_mask == 0 || rx_mask != 0)
		वापस -EINVAL;

	अगर (slots == 1) अणु
		अगर (tx_mask != 1)
			वापस -EINVAL;

		left_slot = 0;
		right_slot = 0;
	पूर्ण अन्यथा अणु
		left_slot = __ffs(tx_mask);
		tx_mask &= ~(1 << left_slot);
		अगर (tx_mask == 0) अणु
			right_slot = left_slot;
		पूर्ण अन्यथा अणु
			right_slot = __ffs(tx_mask);
			tx_mask &= ~(1 << right_slot);
		पूर्ण
	पूर्ण

	अगर (tx_mask != 0 || left_slot >= slots || right_slot >= slots)
		वापस -EINVAL;

	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG3,
					    TAS2770_TDM_CFG_REG3_30_MASK,
					    (left_slot << TAS2770_TDM_CFG_REG3_30_SHIFT));
	अगर (ret < 0)
		वापस ret;
	ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG3,
					    TAS2770_TDM_CFG_REG3_RXS_MASK,
					    (right_slot << TAS2770_TDM_CFG_REG3_RXS_SHIFT));
	अगर (ret < 0)
		वापस ret;

	चयन (slot_width) अणु
	हाल 16:
		ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG2,
						    TAS2770_TDM_CFG_REG2_RXS_MASK,
						    TAS2770_TDM_CFG_REG2_RXS_16BITS);
		अवरोध;
	हाल 24:
		ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG2,
						    TAS2770_TDM_CFG_REG2_RXS_MASK,
						    TAS2770_TDM_CFG_REG2_RXS_24BITS);
		अवरोध;
	हाल 32:
		ret = snd_soc_component_update_bits(component, TAS2770_TDM_CFG_REG2,
						    TAS2770_TDM_CFG_REG2_RXS_MASK,
						    TAS2770_TDM_CFG_REG2_RXS_32BITS);
		अवरोध;
	हाल 0:
		/* Do not change slot width */
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tas2770_dai_ops = अणु
	.mute_stream = tas2770_mute,
	.hw_params  = tas2770_hw_params,
	.set_fmt    = tas2770_set_fmt,
	.set_tdm_slot = tas2770_set_dai_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा TAS2770_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा TAS2770_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |\
					   SNDRV_PCM_RATE_96000 |\
					    SNDRV_PCM_RATE_192000\
					  )

अटल काष्ठा snd_soc_dai_driver tas2770_dai_driver[] = अणु
	अणु
		.name = "tas2770 ASI1",
		.id = 0,
		.playback = अणु
			.stream_name    = "ASI1 Playback",
			.channels_min   = 2,
			.channels_max   = 2,
			.rates      = TAS2770_RATES,
			.क्रमmats    = TAS2770_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name    = "ASI1 Capture",
			.channels_min   = 0,
			.channels_max   = 2,
			.rates          = TAS2770_RATES,
			.क्रमmats    = TAS2770_FORMATS,
		पूर्ण,
		.ops = &tas2770_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tas2770_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2770_priv *tas2770 =
			snd_soc_component_get_drvdata(component);

	tas2770->component = component;

	अगर (tas2770->sdz_gpio)
		gpiod_set_value_cansleep(tas2770->sdz_gpio, 1);

	tas2770_reset(tas2770);

	वापस 0;
पूर्ण

अटल DECLARE_TLV_DB_SCALE(tas2770_digital_tlv, 1100, 50, 0);
अटल DECLARE_TLV_DB_SCALE(tas2770_playback_volume, -12750, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new tas2770_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Playback Volume", TAS2770_PLAY_CFG_REG2,
		       0, TAS2770_PLAY_CFG_REG2_VMAX, 1, tas2770_playback_volume),
	SOC_SINGLE_TLV("Amp Gain Volume", TAS2770_PLAY_CFG_REG0, 0, 0x14, 0,
		       tas2770_digital_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_driver_tas2770 = अणु
	.probe			= tas2770_codec_probe,
	.suspend		= tas2770_codec_suspend,
	.resume			= tas2770_codec_resume,
	.set_bias_level = tas2770_set_bias_level,
	.controls		= tas2770_snd_controls,
	.num_controls		= ARRAY_SIZE(tas2770_snd_controls),
	.dapm_widमाला_लो		= tas2770_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas2770_dapm_widमाला_लो),
	.dapm_routes		= tas2770_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas2770_audio_map),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक tas2770_रेजिस्टर_codec(काष्ठा tas2770_priv *tas2770)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(tas2770->dev,
		&soc_component_driver_tas2770,
		tas2770_dai_driver, ARRAY_SIZE(tas2770_dai_driver));
पूर्ण

अटल स्थिर काष्ठा reg_शेष tas2770_reg_शेषs[] = अणु
	अणु TAS2770_PAGE, 0x00 पूर्ण,
	अणु TAS2770_SW_RST, 0x00 पूर्ण,
	अणु TAS2770_PWR_CTRL, 0x0e पूर्ण,
	अणु TAS2770_PLAY_CFG_REG0, 0x10 पूर्ण,
	अणु TAS2770_PLAY_CFG_REG1, 0x01 पूर्ण,
	अणु TAS2770_PLAY_CFG_REG2, 0x00 पूर्ण,
	अणु TAS2770_MSC_CFG_REG0, 0x07 पूर्ण,
	अणु TAS2770_TDM_CFG_REG1, 0x02 पूर्ण,
	अणु TAS2770_TDM_CFG_REG2, 0x0a पूर्ण,
	अणु TAS2770_TDM_CFG_REG3, 0x10 पूर्ण,
	अणु TAS2770_INT_MASK_REG0, 0xfc पूर्ण,
	अणु TAS2770_INT_MASK_REG1, 0xb1 पूर्ण,
	अणु TAS2770_INT_CFG, 0x05 पूर्ण,
	अणु TAS2770_MISC_IRQ, 0x81 पूर्ण,
	अणु TAS2770_CLK_CGF, 0x0c पूर्ण,

पूर्ण;

अटल bool tas2770_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS2770_PAGE: /* regmap implementation requires this */
	हाल TAS2770_SW_RST: /* always clears after ग_लिखो */
	हाल TAS2770_BO_PRV_REG0:/* has a self clearing bit */
	हाल TAS2770_LVE_INT_REG0:
	हाल TAS2770_LVE_INT_REG1:
	हाल TAS2770_LAT_INT_REG0:/* Sticky पूर्णांकerrupt flags */
	हाल TAS2770_LAT_INT_REG1:/* Sticky पूर्णांकerrupt flags */
	हाल TAS2770_VBAT_MSB:
	हाल TAS2770_VBAT_LSB:
	हाल TAS2770_TEMP_MSB:
	हाल TAS2770_TEMP_LSB:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tas2770_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS2770_LVE_INT_REG0:
	हाल TAS2770_LVE_INT_REG1:
	हाल TAS2770_LAT_INT_REG0:
	हाल TAS2770_LAT_INT_REG1:
	हाल TAS2770_VBAT_MSB:
	हाल TAS2770_VBAT_LSB:
	हाल TAS2770_TEMP_MSB:
	हाल TAS2770_TEMP_LSB:
	हाल TAS2770_TDM_CLK_DETC:
	हाल TAS2770_REV_AND_GPID:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_range_cfg tas2770_regmap_ranges[] = अणु
	अणु
		.range_min = 0,
		.range_max = 1 * 128,
		.selector_reg = TAS2770_PAGE,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 128,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas2770_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = tas2770_ग_लिखोable,
	.अस्थिर_reg = tas2770_अस्थिर,
	.reg_शेषs = tas2770_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tas2770_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.ranges = tas2770_regmap_ranges,
	.num_ranges = ARRAY_SIZE(tas2770_regmap_ranges),
	.max_रेजिस्टर = 1 * 128,
पूर्ण;

अटल पूर्णांक tas2770_parse_dt(काष्ठा device *dev, काष्ठा tas2770_priv *tas2770)
अणु
	पूर्णांक rc = 0;

	rc = fwnode_property_पढ़ो_u32(dev->fwnode, "ti,imon-slot-no",
				      &tas2770->i_sense_slot);
	अगर (rc) अणु
		dev_info(tas2770->dev, "Property %s is missing setting default slot\n",
			 "ti,imon-slot-no");

		tas2770->i_sense_slot = 0;
	पूर्ण

	rc = fwnode_property_पढ़ो_u32(dev->fwnode, "ti,vmon-slot-no",
				      &tas2770->v_sense_slot);
	अगर (rc) अणु
		dev_info(tas2770->dev, "Property %s is missing setting default slot\n",
			 "ti,vmon-slot-no");

		tas2770->v_sense_slot = 2;
	पूर्ण

	tas2770->sdz_gpio = devm_gpiod_get_optional(dev, "shutdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tas2770->sdz_gpio)) अणु
		अगर (PTR_ERR(tas2770->sdz_gpio) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		tas2770->sdz_gpio = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas2770_i2c_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tas2770_priv *tas2770;
	पूर्णांक result;

	tas2770 = devm_kzalloc(&client->dev, माप(काष्ठा tas2770_priv),
			       GFP_KERNEL);
	अगर (!tas2770)
		वापस -ENOMEM;

	tas2770->dev = &client->dev;
	i2c_set_clientdata(client, tas2770);
	dev_set_drvdata(&client->dev, tas2770);

	tas2770->regmap = devm_regmap_init_i2c(client, &tas2770_i2c_regmap);
	अगर (IS_ERR(tas2770->regmap)) अणु
		result = PTR_ERR(tas2770->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			result);
		वापस result;
	पूर्ण

	अगर (client->dev.of_node) अणु
		result = tas2770_parse_dt(&client->dev, tas2770);
		अगर (result) अणु
			dev_err(tas2770->dev, "%s: Failed to parse devicetree\n",
				__func__);
			वापस result;
		पूर्ण
	पूर्ण

	tas2770->reset_gpio = devm_gpiod_get_optional(tas2770->dev, "reset",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(tas2770->reset_gpio)) अणु
		अगर (PTR_ERR(tas2770->reset_gpio) == -EPROBE_DEFER) अणु
			tas2770->reset_gpio = शून्य;
			वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	result = tas2770_रेजिस्टर_codec(tas2770);
	अगर (result)
		dev_err(tas2770->dev, "Register codec failed.\n");

	वापस result;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas2770_i2c_id[] = अणु
	अणु "tas2770", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas2770_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tas2770_of_match[] = अणु
	अणु .compatible = "ti,tas2770" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tas2770_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tas2770_i2c_driver = अणु
	.driver = अणु
		.name   = "tas2770",
		.of_match_table = of_match_ptr(tas2770_of_match),
	पूर्ण,
	.probe      = tas2770_i2c_probe,
	.id_table   = tas2770_i2c_id,
पूर्ण;
module_i2c_driver(tas2770_i2c_driver);

MODULE_AUTHOR("Shi Fu <shifu0704@thundersoft.com>");
MODULE_DESCRIPTION("TAS2770 I2C Smart Amplifier driver");
MODULE_LICENSE("GPL v2");
