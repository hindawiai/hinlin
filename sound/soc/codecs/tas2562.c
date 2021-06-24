<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम the Texas Instruments TAS2562 CODEC
// Copyright (C) 2019 Texas Instruments Inc.


#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/delay.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "tas2562.h"

#घोषणा TAS2562_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FORMAT_S32_LE)

/* DVC equation involves भग्नing poपूर्णांक math
 * round(10^(volume in dB/20)*2^30)
 * so create a lookup table क्रम 2dB step
 */
अटल स्थिर अचिन्हित पूर्णांक भग्न_vol_db_lookup[] = अणु
0x00000d43, 0x000010b2, 0x00001505, 0x00001a67, 0x00002151,
0x000029f1, 0x000034cd, 0x00004279, 0x000053af, 0x0000695b,
0x0000695b, 0x0000a6fa, 0x0000d236, 0x000108a4, 0x00014d2a,
0x0001a36e, 0x00021008, 0x000298c0, 0x000344df, 0x00041d8f,
0x00052e5a, 0x000685c8, 0x00083621, 0x000a566d, 0x000d03a7,
0x0010624d, 0x0014a050, 0x0019f786, 0x0020b0bc, 0x0029279d,
0x0033cf8d, 0x004139d3, 0x00521d50, 0x00676044, 0x0082248a,
0x00a3d70a, 0x00ce4328, 0x0103ab3d, 0x0146e75d, 0x019b8c27,
0x02061b89, 0x028c423f, 0x03352529, 0x0409c2b0, 0x05156d68,
0x080e9f96, 0x0a24b062, 0x0cc509ab, 0x10137987, 0x143d1362,
0x197a967f, 0x2013739e, 0x28619ae9, 0x32d64617, 0x40000000
पूर्ण;

काष्ठा tas2562_data अणु
	काष्ठा snd_soc_component *component;
	काष्ठा gpio_desc *sdz_gpio;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	पूर्णांक v_sense_slot;
	पूर्णांक i_sense_slot;
	पूर्णांक volume_lvl;
	पूर्णांक model_id;
पूर्ण;

क्रमागत tas256x_model अणु
	TAS2562,
	TAS2563,
	TAS2564,
	TAS2110,
पूर्ण;

अटल पूर्णांक tas2562_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा tas2562_data *tas2562 =
			snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component,
			TAS2562_PWR_CTRL,
			TAS2562_MODE_MASK, TAS2562_ACTIVE);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component,
			TAS2562_PWR_CTRL,
			TAS2562_MODE_MASK, TAS2562_MUTE);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component,
			TAS2562_PWR_CTRL,
			TAS2562_MODE_MASK, TAS2562_SHUTDOWN);
		अवरोध;

	शेष:
		dev_err(tas2562->dev,
				"wrong power level setting %d\n", level);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_set_samplerate(काष्ठा tas2562_data *tas2562, पूर्णांक samplerate)
अणु
	पूर्णांक samp_rate;
	पूर्णांक ramp_rate;

	चयन (samplerate) अणु
	हाल 7350:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_7305_8KHZ;
		अवरोध;
	हाल 8000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_7305_8KHZ;
		अवरोध;
	हाल 14700:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_14_7_16KHZ;
		अवरोध;
	हाल 16000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_14_7_16KHZ;
		अवरोध;
	हाल 22050:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_22_05_24KHZ;
		अवरोध;
	हाल 24000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_22_05_24KHZ;
		अवरोध;
	हाल 29400:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_29_4_32KHZ;
		अवरोध;
	हाल 32000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_29_4_32KHZ;
		अवरोध;
	हाल 44100:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_44_1_48KHZ;
		अवरोध;
	हाल 48000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_44_1_48KHZ;
		अवरोध;
	हाल 88200:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_88_2_96KHZ;
		अवरोध;
	हाल 96000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_88_2_96KHZ;
		अवरोध;
	हाल 176400:
		ramp_rate = TAS2562_TDM_CFG0_RAMPRATE_44_1;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_176_4_192KHZ;
		अवरोध;
	हाल 192000:
		ramp_rate = 0;
		samp_rate = TAS2562_TDM_CFG0_SAMPRATE_176_4_192KHZ;
		अवरोध;
	शेष:
		dev_info(tas2562->dev, "%s, unsupported sample rate, %d\n",
			__func__, samplerate);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG0,
		TAS2562_TDM_CFG0_RAMPRATE_MASK,	ramp_rate);
	snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG0,
		TAS2562_TDM_CFG0_SAMPRATE_MASK,	samp_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
		पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);
	पूर्णांक left_slot, right_slot;
	पूर्णांक slots_cfg;
	पूर्णांक ret;

	अगर (!tx_mask) अणु
		dev_err(component->dev, "tx masks must not be 0\n");
		वापस -EINVAL;
	पूर्ण

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
		पूर्ण
	पूर्ण

	slots_cfg = (right_slot << TAS2562_RIGHT_SLOT_SHIFT) | left_slot;

	ret = snd_soc_component_ग_लिखो(component, TAS2562_TDM_CFG3, slots_cfg);
	अगर (ret < 0)
		वापस ret;

	चयन (slot_width) अणु
	हाल 16:
		ret = snd_soc_component_update_bits(component,
						    TAS2562_TDM_CFG2,
						    TAS2562_TDM_CFG2_RXLEN_MASK,
						    TAS2562_TDM_CFG2_RXLEN_16B);
		अवरोध;
	हाल 24:
		ret = snd_soc_component_update_bits(component,
						    TAS2562_TDM_CFG2,
						    TAS2562_TDM_CFG2_RXLEN_MASK,
						    TAS2562_TDM_CFG2_RXLEN_24B);
		अवरोध;
	हाल 32:
		ret = snd_soc_component_update_bits(component,
						    TAS2562_TDM_CFG2,
						    TAS2562_TDM_CFG2_RXLEN_MASK,
						    TAS2562_TDM_CFG2_RXLEN_32B);
		अवरोध;

	हाल 0:
		/* Do not change slot width */
		अवरोध;
	शेष:
		dev_err(tas2562->dev, "slot width not supported");
		ret = -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2562_TDM_CFG5,
					    TAS2562_TDM_CFG5_VSNS_SLOT_MASK,
					    tas2562->v_sense_slot);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, TAS2562_TDM_CFG6,
					    TAS2562_TDM_CFG6_ISNS_SLOT_MASK,
					    tas2562->i_sense_slot);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_set_bitwidth(काष्ठा tas2562_data *tas2562, पूर्णांक bitwidth)
अणु
	पूर्णांक ret;
	पूर्णांक val;
	पूर्णांक sense_en;

	चयन (bitwidth) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		snd_soc_component_update_bits(tas2562->component,
					      TAS2562_TDM_CFG2,
					      TAS2562_TDM_CFG2_RXWLEN_MASK,
					      TAS2562_TDM_CFG2_RXWLEN_16B);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		snd_soc_component_update_bits(tas2562->component,
					      TAS2562_TDM_CFG2,
					      TAS2562_TDM_CFG2_RXWLEN_MASK,
					      TAS2562_TDM_CFG2_RXWLEN_24B);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		snd_soc_component_update_bits(tas2562->component,
					      TAS2562_TDM_CFG2,
					      TAS2562_TDM_CFG2_RXWLEN_MASK,
					      TAS2562_TDM_CFG2_RXWLEN_32B);
		अवरोध;

	शेष:
		dev_info(tas2562->dev, "Unsupported bitwidth format\n");
		वापस -EINVAL;
	पूर्ण

	val = snd_soc_component_पढ़ो(tas2562->component, TAS2562_PWR_CTRL);
	अगर (val < 0)
		वापस val;

	अगर (val & (1 << TAS2562_VSENSE_POWER_EN))
		sense_en = 0;
	अन्यथा
		sense_en = TAS2562_TDM_CFG5_VSNS_EN;

	ret = snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG5,
		TAS2562_TDM_CFG5_VSNS_EN, sense_en);
	अगर (ret < 0)
		वापस ret;

	अगर (val & (1 << TAS2562_ISENSE_POWER_EN))
		sense_en = 0;
	अन्यथा
		sense_en = TAS2562_TDM_CFG6_ISNS_EN;

	ret = snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG6,
		TAS2562_TDM_CFG6_ISNS_EN, sense_en);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = tas2562_set_bitwidth(tas2562, params_क्रमmat(params));
	अगर (ret) अणु
		dev_err(tas2562->dev, "set bitwidth failed, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tas2562_set_samplerate(tas2562, params_rate(params));
	अगर (ret)
		dev_err(tas2562->dev, "set sample rate failed, %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tas2562_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);
	u8 asi_cfg_1 = 0;
	u8 tdm_rx_start_slot = 0;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		asi_cfg_1 = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		asi_cfg_1 |= TAS2562_TDM_CFG1_RX_FALLING;
		अवरोध;
	शेष:
		dev_err(tas2562->dev, "ASI format Inverse is not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2562_TDM_CFG1,
					    TAS2562_TDM_CFG1_RX_EDGE_MASK,
					    asi_cfg_1);
	अगर (ret < 0) अणु
		dev_err(tas2562->dev, "Failed to set RX edge\n");
		वापस ret;
	पूर्ण
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_DSP_B:
		tdm_rx_start_slot = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_DSP_A:
		tdm_rx_start_slot = 1;
		अवरोध;
	शेष:
		dev_err(tas2562->dev,
			"DAI Format is not found, fmt=0x%x\n", fmt);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS2562_TDM_CFG1,
				TAS2562_RX_OFF_MASK, (tdm_rx_start_slot << 1));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	वापस snd_soc_component_update_bits(component, TAS2562_PWR_CTRL,
					     TAS2562_MODE_MASK,
					     mute ? TAS2562_MUTE : 0);
पूर्ण

अटल पूर्णांक tas2562_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	tas2562->component = component;

	अगर (tas2562->sdz_gpio)
		gpiod_set_value_cansleep(tas2562->sdz_gpio, 1);

	ret = snd_soc_component_update_bits(component, TAS2562_PWR_CTRL,
					    TAS2562_MODE_MASK, TAS2562_MUTE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas2562_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(tas2562->regmap, true);
	regcache_mark_dirty(tas2562->regmap);

	अगर (tas2562->sdz_gpio)
		gpiod_set_value_cansleep(tas2562->sdz_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);

	अगर (tas2562->sdz_gpio)
		gpiod_set_value_cansleep(tas2562->sdz_gpio, 1);

	regcache_cache_only(tas2562->regmap, false);

	वापस regcache_sync(tas2562->regmap);
पूर्ण
#अन्यथा
#घोषणा tas2562_suspend शून्य
#घोषणा tas2562_resume शून्य
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर tas2562_ASI1_src[] = अणु
	"I2C offset", "Left", "Right", "LeftRightDiv2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(tas2562_ASI1_src_क्रमागत, TAS2562_TDM_CFG2, 4,
			    tas2562_ASI1_src);

अटल स्थिर काष्ठा snd_kcontrol_new tas2562_asi1_mux =
	SOC_DAPM_ENUM("ASI1 Source", tas2562_ASI1_src_क्रमागत);

अटल पूर्णांक tas2562_dac_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
					snd_soc_dapm_to_component(w->dapm);
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		ret = snd_soc_component_update_bits(component,
			TAS2562_PWR_CTRL,
			TAS2562_MODE_MASK,
			TAS2562_MUTE);
		अगर (ret)
			जाओ end;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		ret = snd_soc_component_update_bits(component,
			TAS2562_PWR_CTRL,
			TAS2562_MODE_MASK,
			TAS2562_SHUTDOWN);
		अगर (ret)
			जाओ end;
		अवरोध;
	शेष:
		dev_err(tas2562->dev, "Not supported evevt\n");
		वापस -EINVAL;
	पूर्ण

end:
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_volume_control_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = tas2562->volume_lvl;
	वापस 0;
पूर्ण

अटल पूर्णांक tas2562_volume_control_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tas2562_data *tas2562 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	u32 reg_val;

	reg_val = भग्न_vol_db_lookup[ucontrol->value.पूर्णांकeger.value[0]/2];
	ret = snd_soc_component_ग_लिखो(component, TAS2562_DVC_CFG4,
				      (reg_val & 0xff));
	अगर (ret)
		वापस ret;
	ret = snd_soc_component_ग_लिखो(component, TAS2562_DVC_CFG3,
				      ((reg_val >> 8) & 0xff));
	अगर (ret)
		वापस ret;
	ret = snd_soc_component_ग_लिखो(component, TAS2562_DVC_CFG2,
				      ((reg_val >> 16) & 0xff));
	अगर (ret)
		वापस ret;
	ret = snd_soc_component_ग_लिखो(component, TAS2562_DVC_CFG1,
				      ((reg_val >> 24) & 0xff));
	अगर (ret)
		वापस ret;

	tas2562->volume_lvl = ucontrol->value.पूर्णांकeger.value[0];

	वापस 0;
पूर्ण

/* Digital Volume Control. From 0 dB to -110 dB in 1 dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(dvc_tlv, -11000, 100, 0);

अटल DECLARE_TLV_DB_SCALE(tas2562_dac_tlv, 850, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new isense_चयन =
	SOC_DAPM_SINGLE("Switch", TAS2562_PWR_CTRL, TAS2562_ISENSE_POWER_EN,
			1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new vsense_चयन =
	SOC_DAPM_SINGLE("Switch", TAS2562_PWR_CTRL, TAS2562_VSENSE_POWER_EN,
			1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new tas2562_snd_controls[] = अणु
	SOC_SINGLE_TLV("Amp Gain Volume", TAS2562_PB_CFG1, 1, 0x1c, 0,
		       tas2562_dac_tlv),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Digital Volume Control",
		.index = 0,
		.tlv.p = dvc_tlv,
		.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_soc_info_volsw,
		.get = tas2562_volume_control_get,
		.put = tas2562_volume_control_put,
		.निजी_value = SOC_SINGLE_VALUE(TAS2562_DVC_CFG1, 0, 110, 0, 0),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tas2110_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sel", SND_SOC_NOPM, 0, 0, &tas2562_asi1_mux),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, tas2562_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas2110_audio_map[] = अणु
	अणु"ASI1 Sel", "I2C offset", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Left", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Right", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "LeftRightDiv2", "ASI1"पूर्ण,
	अणु "DAC", शून्य, "ASI1 Sel" पूर्ण,
	अणु "OUT", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tas2110 = अणु
	.probe			= tas2562_codec_probe,
	.suspend		= tas2562_suspend,
	.resume			= tas2562_resume,
	.set_bias_level		= tas2562_set_bias_level,
	.controls		= tas2562_snd_controls,
	.num_controls		= ARRAY_SIZE(tas2562_snd_controls),
	.dapm_widमाला_लो		= tas2110_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas2110_dapm_widमाला_लो),
	.dapm_routes		= tas2110_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas2110_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tas2562_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sel", SND_SOC_NOPM, 0, 0, &tas2562_asi1_mux),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, tas2562_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SWITCH("ISENSE", TAS2562_PWR_CTRL, 3, 1, &isense_चयन),
	SND_SOC_DAPM_SWITCH("VSENSE", TAS2562_PWR_CTRL, 2, 1, &vsense_चयन),
	SND_SOC_DAPM_SIGGEN("VMON"),
	SND_SOC_DAPM_SIGGEN("IMON"),
	SND_SOC_DAPM_OUTPUT("OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas2562_audio_map[] = अणु
	अणु"ASI1 Sel", "I2C offset", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Left", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "Right", "ASI1"पूर्ण,
	अणु"ASI1 Sel", "LeftRightDiv2", "ASI1"पूर्ण,
	अणु "DAC", शून्य, "ASI1 Sel" पूर्ण,
	अणु "OUT", शून्य, "DAC" पूर्ण,
	अणु"ISENSE", "Switch", "IMON"पूर्ण,
	अणु"VSENSE", "Switch", "VMON"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tas2562 = अणु
	.probe			= tas2562_codec_probe,
	.suspend		= tas2562_suspend,
	.resume			= tas2562_resume,
	.set_bias_level		= tas2562_set_bias_level,
	.controls		= tas2562_snd_controls,
	.num_controls		= ARRAY_SIZE(tas2562_snd_controls),
	.dapm_widमाला_लो		= tas2562_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas2562_dapm_widमाला_लो),
	.dapm_routes		= tas2562_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas2562_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops tas2562_speaker_dai_ops = अणु
	.hw_params	= tas2562_hw_params,
	.set_fmt	= tas2562_set_dai_fmt,
	.set_tdm_slot	= tas2562_set_dai_tdm_slot,
	.mute_stream	= tas2562_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tas2562_dai[] = अणु
	अणु
		.name = "tas2562-amplifier",
		.id = 0,
		.playback = अणु
			.stream_name    = "ASI1 Playback",
			.channels_min   = 2,
			.channels_max   = 2,
			.rates      = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats    = TAS2562_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name    = "ASI1 Capture",
			.channels_min   = 0,
			.channels_max   = 2,
			.rates		= SNDRV_PCM_RATE_8000_192000,
			.क्रमmats	= TAS2562_FORMATS,
		पूर्ण,
		.ops = &tas2562_speaker_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg tas2562_ranges[] = अणु
	अणु
		.range_min = 0,
		.range_max = 5 * 128,
		.selector_reg = TAS2562_PAGE_CTRL,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 128,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tas2562_reg_शेषs[] = अणु
	अणु TAS2562_PAGE_CTRL, 0x00 पूर्ण,
	अणु TAS2562_SW_RESET, 0x00 पूर्ण,
	अणु TAS2562_PWR_CTRL, 0x0e पूर्ण,
	अणु TAS2562_PB_CFG1, 0x20 पूर्ण,
	अणु TAS2562_TDM_CFG0, 0x09 पूर्ण,
	अणु TAS2562_TDM_CFG1, 0x02 पूर्ण,
	अणु TAS2562_DVC_CFG1, 0x40 पूर्ण,
	अणु TAS2562_DVC_CFG2, 0x40 पूर्ण,
	अणु TAS2562_DVC_CFG3, 0x00 पूर्ण,
	अणु TAS2562_DVC_CFG4, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas2562_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 5 * 128,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = tas2562_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tas2562_reg_शेषs),
	.ranges = tas2562_ranges,
	.num_ranges = ARRAY_SIZE(tas2562_ranges),
पूर्ण;

अटल पूर्णांक tas2562_parse_dt(काष्ठा tas2562_data *tas2562)
अणु
	काष्ठा device *dev = tas2562->dev;
	पूर्णांक ret = 0;

	tas2562->sdz_gpio = devm_gpiod_get_optional(dev, "shutdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tas2562->sdz_gpio)) अणु
		अगर (PTR_ERR(tas2562->sdz_gpio) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		tas2562->sdz_gpio = शून्य;
	पूर्ण

	/*
	 * The shut-करोwn property is deprecated but needs to be checked क्रम
	 * backwards compatibility.
	 */
	अगर (tas2562->sdz_gpio == शून्य) अणु
		tas2562->sdz_gpio = devm_gpiod_get_optional(dev, "shut-down",
							      GPIOD_OUT_HIGH);
		अगर (IS_ERR(tas2562->sdz_gpio))
			अगर (PTR_ERR(tas2562->sdz_gpio) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;

		tas2562->sdz_gpio = शून्य;
	पूर्ण

	अगर (tas2562->model_id == TAS2110)
		वापस ret;

	ret = fwnode_property_पढ़ो_u32(dev->fwnode, "ti,imon-slot-no",
			&tas2562->i_sense_slot);
	अगर (ret) अणु
		dev_err(dev, "Property %s is missing setting default slot\n",
			"ti,imon-slot-no");
		tas2562->i_sense_slot = 0;
	पूर्ण


	ret = fwnode_property_पढ़ो_u32(dev->fwnode, "ti,vmon-slot-no",
			&tas2562->v_sense_slot);
	अगर (ret) अणु
		dev_info(dev, "Property %s is missing setting default slot\n",
			"ti,vmon-slot-no");
		tas2562->v_sense_slot = 2;
	पूर्ण

	अगर (tas2562->v_sense_slot < tas2562->i_sense_slot) अणु
		dev_err(dev, "Vsense slot must be greater than Isense slot\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tas2562_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tas2562_data *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->dev = &client->dev;
	data->model_id = id->driver_data;

	tas2562_parse_dt(data);

	data->regmap = devm_regmap_init_i2c(client, &tas2562_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		ret = PTR_ERR(data->regmap);
		dev_err(dev, "failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&client->dev, data);

	अगर (data->model_id == TAS2110)
		वापस devm_snd_soc_रेजिस्टर_component(dev,
						       &soc_component_dev_tas2110,
						       tas2562_dai,
						       ARRAY_SIZE(tas2562_dai));

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_tas2562,
					       tas2562_dai,
					       ARRAY_SIZE(tas2562_dai));

पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas2562_id[] = अणु
	अणु "tas2562", TAS2562 पूर्ण,
	अणु "tas2563", TAS2563 पूर्ण,
	अणु "tas2564", TAS2564 पूर्ण,
	अणु "tas2110", TAS2110 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas2562_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tas2562_of_match[] = अणु
	अणु .compatible = "ti,tas2562", पूर्ण,
	अणु .compatible = "ti,tas2563", पूर्ण,
	अणु .compatible = "ti,tas2564", पूर्ण,
	अणु .compatible = "ti,tas2110", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tas2562_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tas2562_i2c_driver = अणु
	.driver = अणु
		.name = "tas2562",
		.of_match_table = of_match_ptr(tas2562_of_match),
	पूर्ण,
	.probe = tas2562_probe,
	.id_table = tas2562_id,
पूर्ण;

module_i2c_driver(tas2562_i2c_driver);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_DESCRIPTION("TAS2562 Audio amplifier driver");
MODULE_LICENSE("GPL");
