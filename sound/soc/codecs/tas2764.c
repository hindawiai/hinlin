<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम the Texas Instruments TAS2764 CODEC
// Copyright (C) 2020 Texas Instruments Inc.

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
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "tas2764.h"

काष्ठा tas2764_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *sdz_gpio;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	
	पूर्णांक v_sense_slot;
	पूर्णांक i_sense_slot;
पूर्ण;

अटल व्योम tas2764_reset(काष्ठा tas2764_priv *tas2764)
अणु
	अगर (tas2764->reset_gpio) अणु
		gpiod_set_value_cansleep(tas2764->reset_gpio, 0);
		msleep(20);
		gpiod_set_value_cansleep(tas2764->reset_gpio, 1);
	पूर्ण

	snd_soc_component_ग_लिखो(tas2764->component, TAS2764_SW_RST,
				TAS2764_RST);
पूर्ण

अटल पूर्णांक tas2764_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					      TAS2764_PWR_CTRL_MASK,
					      TAS2764_PWR_CTRL_ACTIVE);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					      TAS2764_PWR_CTRL_MASK,
					      TAS2764_PWR_CTRL_MUTE);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					      TAS2764_PWR_CTRL_MASK,
					      TAS2764_PWR_CTRL_SHUTDOWN);
		अवरोध;

	शेष:
		dev_err(tas2764->dev,
				"wrong power level setting %d\n", level);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas2764_codec_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					    TAS2764_PWR_CTRL_MASK,
					    TAS2764_PWR_CTRL_SHUTDOWN);

	अगर (ret < 0)
		वापस ret;

	अगर (tas2764->sdz_gpio)
		gpiod_set_value_cansleep(tas2764->sdz_gpio, 0);

	regcache_cache_only(tas2764->regmap, true);
	regcache_mark_dirty(tas2764->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2764_codec_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (tas2764->sdz_gpio)
		gpiod_set_value_cansleep(tas2764->sdz_gpio, 1);

	ret = snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					    TAS2764_PWR_CTRL_MASK,
					    TAS2764_PWR_CTRL_ACTIVE);

	अगर (ret < 0)
		वापस ret;

	regcache_cache_only(tas2764->regmap, false);

	वापस regcache_sync(tas2764->regmap);
पूर्ण
#अन्यथा
#घोषणा tas2764_codec_suspend शून्य
#घोषणा tas2764_codec_resume शून्य
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर tas2764_ASI1_src[] = अणु
	"I2C offset", "Left", "Right", "LeftRightDiv2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	tas2764_ASI1_src_क्रमागत, TAS2764_TDM_CFG2, 4, tas2764_ASI1_src);

अटल स्थिर काष्ठा snd_kcontrol_new tas2764_asi1_mux =
	SOC_DAPM_ENUM("ASI1 Source", tas2764_ASI1_src_क्रमागत);

अटल पूर्णांक tas2764_dac_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		ret = snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
						    TAS2764_PWR_CTRL_MASK,
						    TAS2764_PWR_CTRL_MUTE);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		ret = snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
						    TAS2764_PWR_CTRL_MASK,
						    TAS2764_PWR_CTRL_SHUTDOWN);
		अवरोध;
	शेष:
		dev_err(tas2764->dev, "Unsupported event\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new isense_चयन =
	SOC_DAPM_SINGLE("Switch", TAS2764_PWR_CTRL, TAS2764_ISENSE_POWER_EN, 1, 1);
अटल स्थिर काष्ठा snd_kcontrol_new vsense_चयन =
	SOC_DAPM_SINGLE("Switch", TAS2764_PWR_CTRL, TAS2764_VSENSE_POWER_EN, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget tas2764_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sel", SND_SOC_NOPM, 0, 0, &tas2764_asi1_mux),
	SND_SOC_DAPM_SWITCH("ISENSE", TAS2764_PWR_CTRL, TAS2764_ISENSE_POWER_EN,
			    1, &isense_चयन),
	SND_SOC_DAPM_SWITCH("VSENSE", TAS2764_PWR_CTRL, TAS2764_VSENSE_POWER_EN,
			    1, &vsense_चयन),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, tas2764_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
	SND_SOC_DAPM_SIGGEN("VMON"),
	SND_SOC_DAPM_SIGGEN("IMON")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas2764_audio_map[] = अणु
	अणु"ASI1 Sel", "I2C offset", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Left", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Right", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "LeftRightDiv2", "ASI1"पूर्ण,
	अणु"DAC", शून्य, "ASI1 Sel"पूर्ण,
	अणु"OUT", शून्य, "DAC"पूर्ण,
	अणु"ISENSE", "Switch", "IMON"पूर्ण,
	अणु"VSENSE", "Switch", "VMON"पूर्ण,
पूर्ण;

अटल पूर्णांक tas2764_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					    TAS2764_PWR_CTRL_MASK,
					    mute ? TAS2764_PWR_CTRL_MUTE : 0);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2764_set_bitwidth(काष्ठा tas2764_priv *tas2764, पूर्णांक bitwidth)
अणु
	काष्ठा snd_soc_component *component = tas2764->component;
	पूर्णांक sense_en;
	पूर्णांक val;
	पूर्णांक ret;

	चयन (bitwidth) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		ret = snd_soc_component_update_bits(component,
						    TAS2764_TDM_CFG2,
						    TAS2764_TDM_CFG2_RXW_MASK,
						    TAS2764_TDM_CFG2_RXW_16BITS);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		ret = snd_soc_component_update_bits(component,
						    TAS2764_TDM_CFG2,
						    TAS2764_TDM_CFG2_RXW_MASK,
						    TAS2764_TDM_CFG2_RXW_24BITS);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		ret = snd_soc_component_update_bits(component,
						    TAS2764_TDM_CFG2,
						    TAS2764_TDM_CFG2_RXW_MASK,
						    TAS2764_TDM_CFG2_RXW_32BITS);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	val = snd_soc_component_पढ़ो(tas2764->component, TAS2764_PWR_CTRL);
	अगर (val < 0)
		वापस val;

	अगर (val & (1 << TAS2764_VSENSE_POWER_EN))
		sense_en = 0;
	अन्यथा
		sense_en = TAS2764_TDM_CFG5_VSNS_ENABLE;

	ret = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG5,
					    TAS2764_TDM_CFG5_VSNS_ENABLE,
					    sense_en);
	अगर (ret < 0)
		वापस ret;

	अगर (val & (1 << TAS2764_ISENSE_POWER_EN))
		sense_en = 0;
	अन्यथा
		sense_en = TAS2764_TDM_CFG6_ISNS_ENABLE;

	ret = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG6,
					    TAS2764_TDM_CFG6_ISNS_ENABLE,
					    sense_en);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2764_set_samplerate(काष्ठा tas2764_priv *tas2764, पूर्णांक samplerate)
अणु
	काष्ठा snd_soc_component *component = tas2764->component;
	पूर्णांक ramp_rate_val;
	पूर्णांक ret;

	चयन (samplerate) अणु
	हाल 48000:
		ramp_rate_val = TAS2764_TDM_CFG0_SMP_48KHZ |
				TAS2764_TDM_CFG0_44_1_48KHZ;
		अवरोध;
	हाल 44100:
		ramp_rate_val = TAS2764_TDM_CFG0_SMP_44_1KHZ |
				TAS2764_TDM_CFG0_44_1_48KHZ;
		अवरोध;
	हाल 96000:
		ramp_rate_val = TAS2764_TDM_CFG0_SMP_48KHZ |
				TAS2764_TDM_CFG0_88_2_96KHZ;
		अवरोध;
	हाल 88200:
		ramp_rate_val = TAS2764_TDM_CFG0_SMP_44_1KHZ |
				TAS2764_TDM_CFG0_88_2_96KHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG0,
					    TAS2764_TDM_CFG0_SMP_MASK |
					    TAS2764_TDM_CFG0_MASK,
					    ramp_rate_val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2764_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = tas2764_set_bitwidth(tas2764, params_क्रमmat(params));
	अगर (ret < 0)
		वापस ret;

	वापस tas2764_set_samplerate(tas2764, params_rate(params));
पूर्ण

अटल पूर्णांक tas2764_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	u8 tdm_rx_start_slot = 0, asi_cfg_1 = 0;
	पूर्णांक अगरace;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		asi_cfg_1 = TAS2764_TDM_CFG1_RX_RISING;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		asi_cfg_1 = TAS2764_TDM_CFG1_RX_FALLING;
		अवरोध;
	शेष:
		dev_err(tas2764->dev, "ASI format Inverse is not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG1,
					    TAS2764_TDM_CFG1_RX_MASK,
					    asi_cfg_1);
	अगर (ret < 0)
		वापस ret;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace = TAS2764_TDM_CFG2_SCFG_I2S;
		tdm_rx_start_slot = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace = TAS2764_TDM_CFG2_SCFG_LEFT_J;
		tdm_rx_start_slot = 0;
		अवरोध;
	शेष:
		dev_err(tas2764->dev,
			"DAI Format is not found, fmt=0x%x\n", fmt);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG1,
					    TAS2764_TDM_CFG1_MASK,
					    (tdm_rx_start_slot << TAS2764_TDM_CFG1_51_SHIFT));
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG2,
					    TAS2764_TDM_CFG2_SCFG_MASK, अगरace);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2764_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask,
				पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	पूर्णांक left_slot, right_slot;
	पूर्णांक slots_cfg;
	पूर्णांक slot_size;
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

	slots_cfg = (right_slot << TAS2764_TDM_CFG3_RXS_SHIFT) | left_slot;

	ret = snd_soc_component_ग_लिखो(component, TAS2764_TDM_CFG3, slots_cfg);
	अगर (ret)
		वापस ret;

	चयन (slot_width) अणु
	हाल 16:
		slot_size = TAS2764_TDM_CFG2_RXS_16BITS;
		अवरोध;
	हाल 24:
		slot_size = TAS2764_TDM_CFG2_RXS_24BITS;
		अवरोध;
	हाल 32:
		slot_size = TAS2764_TDM_CFG2_RXS_32BITS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG2,
					    TAS2764_TDM_CFG2_RXS_MASK,
					    slot_size);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG5,
					    TAS2764_TDM_CFG5_50_MASK,
					    tas2764->v_sense_slot);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2764_TDM_CFG6,
					    TAS2764_TDM_CFG6_50_MASK,
					    tas2764->i_sense_slot);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tas2764_dai_ops = अणु
	.mute_stream = tas2764_mute,
	.hw_params  = tas2764_hw_params,
	.set_fmt    = tas2764_set_fmt,
	.set_tdm_slot = tas2764_set_dai_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा TAS2764_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा TAS2764_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |\
		       SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_88200)

अटल काष्ठा snd_soc_dai_driver tas2764_dai_driver[] = अणु
	अणु
		.name = "tas2764 ASI1",
		.id = 0,
		.playback = अणु
			.stream_name    = "ASI1 Playback",
			.channels_min   = 2,
			.channels_max   = 2,
			.rates      = TAS2764_RATES,
			.क्रमmats    = TAS2764_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name    = "ASI1 Capture",
			.channels_min   = 0,
			.channels_max   = 2,
			.rates = TAS2764_RATES,
			.क्रमmats = TAS2764_FORMATS,
		पूर्ण,
		.ops = &tas2764_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tas2764_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2764_priv *tas2764 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	tas2764->component = component;

	अगर (tas2764->sdz_gpio)
		gpiod_set_value_cansleep(tas2764->sdz_gpio, 1);

	tas2764_reset(tas2764);

	ret = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG5,
					    TAS2764_TDM_CFG5_VSNS_ENABLE, 0);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG6,
					    TAS2764_TDM_CFG6_ISNS_ENABLE, 0);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2764_PWR_CTRL,
					    TAS2764_PWR_CTRL_MASK,
					    TAS2764_PWR_CTRL_MUTE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल DECLARE_TLV_DB_SCALE(tas2764_digital_tlv, 1100, 50, 0);
अटल DECLARE_TLV_DB_SCALE(tas2764_playback_volume, -10000, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new tas2764_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Volume", TAS2764_DVC, 0,
		       TAS2764_DVC_MAX, 1, tas2764_playback_volume),
	SOC_SINGLE_TLV("Amp Gain Volume", TAS2764_CHNL_0, 0, 0x14, 0,
		       tas2764_digital_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_driver_tas2764 = अणु
	.probe			= tas2764_codec_probe,
	.suspend		= tas2764_codec_suspend,
	.resume			= tas2764_codec_resume,
	.set_bias_level		= tas2764_set_bias_level,
	.controls		= tas2764_snd_controls,
	.num_controls		= ARRAY_SIZE(tas2764_snd_controls),
	.dapm_widमाला_लो		= tas2764_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas2764_dapm_widमाला_लो),
	.dapm_routes		= tas2764_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas2764_audio_map),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tas2764_reg_शेषs[] = अणु
	अणु TAS2764_PAGE, 0x00 पूर्ण,
	अणु TAS2764_SW_RST, 0x00 पूर्ण,
	अणु TAS2764_PWR_CTRL, 0x1a पूर्ण,
	अणु TAS2764_DVC, 0x00 पूर्ण,
	अणु TAS2764_CHNL_0, 0x00 पूर्ण,
	अणु TAS2764_TDM_CFG0, 0x09 पूर्ण,
	अणु TAS2764_TDM_CFG1, 0x02 पूर्ण,
	अणु TAS2764_TDM_CFG2, 0x0a पूर्ण,
	अणु TAS2764_TDM_CFG3, 0x10 पूर्ण,
	अणु TAS2764_TDM_CFG5, 0x42 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg tas2764_regmap_ranges[] = अणु
	अणु
		.range_min = 0,
		.range_max = 1 * 128,
		.selector_reg = TAS2764_PAGE,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 128,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas2764_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.reg_शेषs = tas2764_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tas2764_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.ranges = tas2764_regmap_ranges,
	.num_ranges = ARRAY_SIZE(tas2764_regmap_ranges),
	.max_रेजिस्टर = 1 * 128,
पूर्ण;

अटल पूर्णांक tas2764_parse_dt(काष्ठा device *dev, काष्ठा tas2764_priv *tas2764)
अणु
	पूर्णांक ret = 0;

	tas2764->reset_gpio = devm_gpiod_get_optional(tas2764->dev, "reset",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(tas2764->reset_gpio)) अणु
		अगर (PTR_ERR(tas2764->reset_gpio) == -EPROBE_DEFER) अणु
			tas2764->reset_gpio = शून्य;
			वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	tas2764->sdz_gpio = devm_gpiod_get_optional(dev, "shutdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tas2764->sdz_gpio)) अणु
		अगर (PTR_ERR(tas2764->sdz_gpio) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		tas2764->sdz_gpio = शून्य;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(dev->fwnode, "ti,imon-slot-no",
				       &tas2764->i_sense_slot);
	अगर (ret)
		tas2764->i_sense_slot = 0;

	ret = fwnode_property_पढ़ो_u32(dev->fwnode, "ti,vmon-slot-no",
				       &tas2764->v_sense_slot);
	अगर (ret)
		tas2764->v_sense_slot = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2764_i2c_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tas2764_priv *tas2764;
	पूर्णांक result;

	tas2764 = devm_kzalloc(&client->dev, माप(काष्ठा tas2764_priv),
			       GFP_KERNEL);
	अगर (!tas2764)
		वापस -ENOMEM;

	tas2764->dev = &client->dev;
	i2c_set_clientdata(client, tas2764);
	dev_set_drvdata(&client->dev, tas2764);

	tas2764->regmap = devm_regmap_init_i2c(client, &tas2764_i2c_regmap);
	अगर (IS_ERR(tas2764->regmap)) अणु
		result = PTR_ERR(tas2764->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
					result);
		वापस result;
	पूर्ण

	अगर (client->dev.of_node) अणु
		result = tas2764_parse_dt(&client->dev, tas2764);
		अगर (result) अणु
			dev_err(tas2764->dev, "%s: Failed to parse devicetree\n",
				__func__);
			वापस result;
		पूर्ण
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(tas2764->dev,
					       &soc_component_driver_tas2764,
					       tas2764_dai_driver,
					       ARRAY_SIZE(tas2764_dai_driver));
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas2764_i2c_id[] = अणु
	अणु "tas2764", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas2764_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tas2764_of_match[] = अणु
	अणु .compatible = "ti,tas2764" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tas2764_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tas2764_i2c_driver = अणु
	.driver = अणु
		.name   = "tas2764",
		.of_match_table = of_match_ptr(tas2764_of_match),
	पूर्ण,
	.probe      = tas2764_i2c_probe,
	.id_table   = tas2764_i2c_id,
पूर्ण;
module_i2c_driver(tas2764_i2c_driver);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_DESCRIPTION("TAS2764 I2C Smart Amplifier driver");
MODULE_LICENSE("GPL v2");
