<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the PCM512x CODECs
 *
 * Author:	Mark Brown <broonie@kernel.org>
 *		Copyright 2014 Linaro Ltd
 */


#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gcd.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#समावेश "pcm512x.h"

#घोषणा PCM512x_NUM_SUPPLIES 3
अटल स्थिर अक्षर * स्थिर pcm512x_supply_names[PCM512x_NUM_SUPPLIES] = अणु
	"AVDD",
	"DVDD",
	"CPVDD",
पूर्ण;

काष्ठा pcm512x_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *sclk;
	काष्ठा regulator_bulk_data supplies[PCM512x_NUM_SUPPLIES];
	काष्ठा notअगरier_block supply_nb[PCM512x_NUM_SUPPLIES];
	पूर्णांक fmt;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
	पूर्णांक pll_r;
	पूर्णांक pll_j;
	पूर्णांक pll_d;
	पूर्णांक pll_p;
	अचिन्हित दीर्घ real_pll;
	अचिन्हित दीर्घ overघड़ी_pll;
	अचिन्हित दीर्घ overघड़ी_dac;
	अचिन्हित दीर्घ overघड़ी_dsp;
	पूर्णांक mute;
	काष्ठा mutex mutex;
	अचिन्हित पूर्णांक bclk_ratio;
पूर्ण;

/*
 * We can't use the same notअगरier block क्रम more than one supply and
 * there's no way I can see to get from a callback to the caller
 * except container_of().
 */
#घोषणा PCM512x_REGULATOR_EVENT(n) \
अटल पूर्णांक pcm512x_regulator_event_##n(काष्ठा notअगरier_block *nb, \
				      अचिन्हित दीर्घ event, व्योम *data)    \
अणु \
	काष्ठा pcm512x_priv *pcm512x = container_of(nb, काष्ठा pcm512x_priv, \
						    supply_nb[n]); \
	अगर (event & REGULATOR_EVENT_DISABLE) अणु \
		regcache_mark_dirty(pcm512x->regmap);	\
		regcache_cache_only(pcm512x->regmap, true);	\
	पूर्ण \
	वापस 0; \
पूर्ण

PCM512x_REGULATOR_EVENT(0)
PCM512x_REGULATOR_EVENT(1)
PCM512x_REGULATOR_EVENT(2)

अटल स्थिर काष्ठा reg_शेष pcm512x_reg_शेषs[] = अणु
	अणु PCM512x_RESET,             0x00 पूर्ण,
	अणु PCM512x_POWER,             0x00 पूर्ण,
	अणु PCM512x_MUTE,              0x00 पूर्ण,
	अणु PCM512x_DSP,               0x00 पूर्ण,
	अणु PCM512x_PLL_REF,           0x00 पूर्ण,
	अणु PCM512x_DAC_REF,           0x00 पूर्ण,
	अणु PCM512x_DAC_ROUTING,       0x11 पूर्ण,
	अणु PCM512x_DSP_PROGRAM,       0x01 पूर्ण,
	अणु PCM512x_CLKDET,            0x00 पूर्ण,
	अणु PCM512x_AUTO_MUTE,         0x00 पूर्ण,
	अणु PCM512x_ERROR_DETECT,      0x00 पूर्ण,
	अणु PCM512x_DIGITAL_VOLUME_1,  0x00 पूर्ण,
	अणु PCM512x_DIGITAL_VOLUME_2,  0x30 पूर्ण,
	अणु PCM512x_DIGITAL_VOLUME_3,  0x30 पूर्ण,
	अणु PCM512x_DIGITAL_MUTE_1,    0x22 पूर्ण,
	अणु PCM512x_DIGITAL_MUTE_2,    0x00 पूर्ण,
	अणु PCM512x_DIGITAL_MUTE_3,    0x07 पूर्ण,
	अणु PCM512x_OUTPUT_AMPLITUDE,  0x00 पूर्ण,
	अणु PCM512x_ANALOG_GAIN_CTRL,  0x00 पूर्ण,
	अणु PCM512x_UNDERVOLTAGE_PROT, 0x00 पूर्ण,
	अणु PCM512x_ANALOG_MUTE_CTRL,  0x00 पूर्ण,
	अणु PCM512x_ANALOG_GAIN_BOOST, 0x00 पूर्ण,
	अणु PCM512x_VCOM_CTRL_1,       0x00 पूर्ण,
	अणु PCM512x_VCOM_CTRL_2,       0x01 पूर्ण,
	अणु PCM512x_BCLK_LRCLK_CFG,    0x00 पूर्ण,
	अणु PCM512x_MASTER_MODE,       0x7c पूर्ण,
	अणु PCM512x_GPIO_DACIN,        0x00 पूर्ण,
	अणु PCM512x_GPIO_PLLIN,        0x00 पूर्ण,
	अणु PCM512x_SYNCHRONIZE,       0x10 पूर्ण,
	अणु PCM512x_PLL_COEFF_0,       0x00 पूर्ण,
	अणु PCM512x_PLL_COEFF_1,       0x00 पूर्ण,
	अणु PCM512x_PLL_COEFF_2,       0x00 पूर्ण,
	अणु PCM512x_PLL_COEFF_3,       0x00 पूर्ण,
	अणु PCM512x_PLL_COEFF_4,       0x00 पूर्ण,
	अणु PCM512x_DSP_CLKDIV,        0x00 पूर्ण,
	अणु PCM512x_DAC_CLKDIV,        0x00 पूर्ण,
	अणु PCM512x_NCP_CLKDIV,        0x00 पूर्ण,
	अणु PCM512x_OSR_CLKDIV,        0x00 पूर्ण,
	अणु PCM512x_MASTER_CLKDIV_1,   0x00 पूर्ण,
	अणु PCM512x_MASTER_CLKDIV_2,   0x00 पूर्ण,
	अणु PCM512x_FS_SPEED_MODE,     0x00 पूर्ण,
	अणु PCM512x_IDAC_1,            0x01 पूर्ण,
	अणु PCM512x_IDAC_2,            0x00 पूर्ण,
पूर्ण;

अटल bool pcm512x_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PCM512x_RESET:
	हाल PCM512x_POWER:
	हाल PCM512x_MUTE:
	हाल PCM512x_PLL_EN:
	हाल PCM512x_SPI_MISO_FUNCTION:
	हाल PCM512x_DSP:
	हाल PCM512x_GPIO_EN:
	हाल PCM512x_BCLK_LRCLK_CFG:
	हाल PCM512x_DSP_GPIO_INPUT:
	हाल PCM512x_MASTER_MODE:
	हाल PCM512x_PLL_REF:
	हाल PCM512x_DAC_REF:
	हाल PCM512x_GPIO_DACIN:
	हाल PCM512x_GPIO_PLLIN:
	हाल PCM512x_SYNCHRONIZE:
	हाल PCM512x_PLL_COEFF_0:
	हाल PCM512x_PLL_COEFF_1:
	हाल PCM512x_PLL_COEFF_2:
	हाल PCM512x_PLL_COEFF_3:
	हाल PCM512x_PLL_COEFF_4:
	हाल PCM512x_DSP_CLKDIV:
	हाल PCM512x_DAC_CLKDIV:
	हाल PCM512x_NCP_CLKDIV:
	हाल PCM512x_OSR_CLKDIV:
	हाल PCM512x_MASTER_CLKDIV_1:
	हाल PCM512x_MASTER_CLKDIV_2:
	हाल PCM512x_FS_SPEED_MODE:
	हाल PCM512x_IDAC_1:
	हाल PCM512x_IDAC_2:
	हाल PCM512x_ERROR_DETECT:
	हाल PCM512x_I2S_1:
	हाल PCM512x_I2S_2:
	हाल PCM512x_DAC_ROUTING:
	हाल PCM512x_DSP_PROGRAM:
	हाल PCM512x_CLKDET:
	हाल PCM512x_AUTO_MUTE:
	हाल PCM512x_DIGITAL_VOLUME_1:
	हाल PCM512x_DIGITAL_VOLUME_2:
	हाल PCM512x_DIGITAL_VOLUME_3:
	हाल PCM512x_DIGITAL_MUTE_1:
	हाल PCM512x_DIGITAL_MUTE_2:
	हाल PCM512x_DIGITAL_MUTE_3:
	हाल PCM512x_GPIO_OUTPUT_1:
	हाल PCM512x_GPIO_OUTPUT_2:
	हाल PCM512x_GPIO_OUTPUT_3:
	हाल PCM512x_GPIO_OUTPUT_4:
	हाल PCM512x_GPIO_OUTPUT_5:
	हाल PCM512x_GPIO_OUTPUT_6:
	हाल PCM512x_GPIO_CONTROL_1:
	हाल PCM512x_GPIO_CONTROL_2:
	हाल PCM512x_OVERFLOW:
	हाल PCM512x_RATE_DET_1:
	हाल PCM512x_RATE_DET_2:
	हाल PCM512x_RATE_DET_3:
	हाल PCM512x_RATE_DET_4:
	हाल PCM512x_CLOCK_STATUS:
	हाल PCM512x_ANALOG_MUTE_DET:
	हाल PCM512x_GPIN:
	हाल PCM512x_DIGITAL_MUTE_DET:
	हाल PCM512x_OUTPUT_AMPLITUDE:
	हाल PCM512x_ANALOG_GAIN_CTRL:
	हाल PCM512x_UNDERVOLTAGE_PROT:
	हाल PCM512x_ANALOG_MUTE_CTRL:
	हाल PCM512x_ANALOG_GAIN_BOOST:
	हाल PCM512x_VCOM_CTRL_1:
	हाल PCM512x_VCOM_CTRL_2:
	हाल PCM512x_CRAM_CTRL:
	हाल PCM512x_FLEX_A:
	हाल PCM512x_FLEX_B:
		वापस true;
	शेष:
		/* There are 256 raw रेजिस्टर addresses */
		वापस reg < 0xff;
	पूर्ण
पूर्ण

अटल bool pcm512x_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PCM512x_PLL_EN:
	हाल PCM512x_OVERFLOW:
	हाल PCM512x_RATE_DET_1:
	हाल PCM512x_RATE_DET_2:
	हाल PCM512x_RATE_DET_3:
	हाल PCM512x_RATE_DET_4:
	हाल PCM512x_CLOCK_STATUS:
	हाल PCM512x_ANALOG_MUTE_DET:
	हाल PCM512x_GPIN:
	हाल PCM512x_DIGITAL_MUTE_DET:
	हाल PCM512x_CRAM_CTRL:
		वापस true;
	शेष:
		/* There are 256 raw रेजिस्टर addresses */
		वापस reg < 0xff;
	पूर्ण
पूर्ण

अटल पूर्णांक pcm512x_overघड़ी_pll_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = pcm512x->overघड़ी_pll;
	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_overघड़ी_pll_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	चयन (snd_soc_component_get_bias_level(component)) अणु
	हाल SND_SOC_BIAS_OFF:
	हाल SND_SOC_BIAS_STANDBY:
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण

	pcm512x->overघड़ी_pll = ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_overघड़ी_dsp_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = pcm512x->overघड़ी_dsp;
	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_overघड़ी_dsp_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	चयन (snd_soc_component_get_bias_level(component)) अणु
	हाल SND_SOC_BIAS_OFF:
	हाल SND_SOC_BIAS_STANDBY:
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण

	pcm512x->overघड़ी_dsp = ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_overघड़ी_dac_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = pcm512x->overघड़ी_dac;
	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_overघड़ी_dac_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	चयन (snd_soc_component_get_bias_level(component)) अणु
	हाल SND_SOC_BIAS_OFF:
	हाल SND_SOC_BIAS_STANDBY:
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण

	pcm512x->overघड़ी_dac = ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -10350, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(analog_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, 0, 80, 0);

अटल स्थिर अक्षर * स्थिर pcm512x_dsp_program_texts[] = अणु
	"FIR interpolation with de-emphasis",
	"Low latency IIR with de-emphasis",
	"High attenuation with de-emphasis",
	"Fixed process flow",
	"Ringing-less low latency FIR",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pcm512x_dsp_program_values[] = अणु
	1,
	2,
	3,
	5,
	7,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pcm512x_dsp_program,
				  PCM512x_DSP_PROGRAM, 0, 0x1f,
				  pcm512x_dsp_program_texts,
				  pcm512x_dsp_program_values);

अटल स्थिर अक्षर * स्थिर pcm512x_clk_missing_text[] = अणु
	"1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_clk_missing =
	SOC_ENUM_SINGLE(PCM512x_CLKDET, 0,  8, pcm512x_clk_missing_text);

अटल स्थिर अक्षर * स्थिर pcm512x_स्वतःm_text[] = अणु
	"21ms", "106ms", "213ms", "533ms", "1.07s", "2.13s", "5.33s", "10.66s"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_स्वतःm_l =
	SOC_ENUM_SINGLE(PCM512x_AUTO_MUTE, PCM512x_ATML_SHIFT, 8,
			pcm512x_स्वतःm_text);

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_स्वतःm_r =
	SOC_ENUM_SINGLE(PCM512x_AUTO_MUTE, PCM512x_ATMR_SHIFT, 8,
			pcm512x_स्वतःm_text);

अटल स्थिर अक्षर * स्थिर pcm512x_ramp_rate_text[] = अणु
	"1 sample/update", "2 samples/update", "4 samples/update",
	"Immediate"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_vndf =
	SOC_ENUM_SINGLE(PCM512x_DIGITAL_MUTE_1, PCM512x_VNDF_SHIFT, 4,
			pcm512x_ramp_rate_text);

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_vnuf =
	SOC_ENUM_SINGLE(PCM512x_DIGITAL_MUTE_1, PCM512x_VNUF_SHIFT, 4,
			pcm512x_ramp_rate_text);

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_vedf =
	SOC_ENUM_SINGLE(PCM512x_DIGITAL_MUTE_2, PCM512x_VEDF_SHIFT, 4,
			pcm512x_ramp_rate_text);

अटल स्थिर अक्षर * स्थिर pcm512x_ramp_step_text[] = अणु
	"4dB/step", "2dB/step", "1dB/step", "0.5dB/step"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_vnds =
	SOC_ENUM_SINGLE(PCM512x_DIGITAL_MUTE_1, PCM512x_VNDS_SHIFT, 4,
			pcm512x_ramp_step_text);

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_vnus =
	SOC_ENUM_SINGLE(PCM512x_DIGITAL_MUTE_1, PCM512x_VNUS_SHIFT, 4,
			pcm512x_ramp_step_text);

अटल स्थिर काष्ठा soc_क्रमागत pcm512x_veds =
	SOC_ENUM_SINGLE(PCM512x_DIGITAL_MUTE_2, PCM512x_VEDS_SHIFT, 4,
			pcm512x_ramp_step_text);

अटल पूर्णांक pcm512x_update_mute(काष्ठा pcm512x_priv *pcm512x)
अणु
	वापस regmap_update_bits(
		pcm512x->regmap, PCM512x_MUTE, PCM512x_RQML | PCM512x_RQMR,
		(!!(pcm512x->mute & 0x5) << PCM512x_RQML_SHIFT)
		| (!!(pcm512x->mute & 0x3) << PCM512x_RQMR_SHIFT));
पूर्ण

अटल पूर्णांक pcm512x_digital_playback_चयन_get(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	mutex_lock(&pcm512x->mutex);
	ucontrol->value.पूर्णांकeger.value[0] = !(pcm512x->mute & 0x4);
	ucontrol->value.पूर्णांकeger.value[1] = !(pcm512x->mute & 0x2);
	mutex_unlock(&pcm512x->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_digital_playback_चयन_put(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, changed = 0;

	mutex_lock(&pcm512x->mutex);

	अगर ((pcm512x->mute & 0x4) == (ucontrol->value.पूर्णांकeger.value[0] << 2)) अणु
		pcm512x->mute ^= 0x4;
		changed = 1;
	पूर्ण
	अगर ((pcm512x->mute & 0x2) == (ucontrol->value.पूर्णांकeger.value[1] << 1)) अणु
		pcm512x->mute ^= 0x2;
		changed = 1;
	पूर्ण

	अगर (changed) अणु
		ret = pcm512x_update_mute(pcm512x);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to update digital mute: %d\n", ret);
			mutex_unlock(&pcm512x->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&pcm512x->mutex);

	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcm512x_controls[] = अणु
SOC_DOUBLE_R_TLV("Digital Playback Volume", PCM512x_DIGITAL_VOLUME_2,
		 PCM512x_DIGITAL_VOLUME_3, 0, 255, 1, digital_tlv),
SOC_DOUBLE_TLV("Analogue Playback Volume", PCM512x_ANALOG_GAIN_CTRL,
	       PCM512x_LAGN_SHIFT, PCM512x_RAGN_SHIFT, 1, 1, analog_tlv),
SOC_DOUBLE_TLV("Analogue Playback Boost Volume", PCM512x_ANALOG_GAIN_BOOST,
	       PCM512x_AGBL_SHIFT, PCM512x_AGBR_SHIFT, 1, 0, boost_tlv),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Digital Playback Switch",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_ctl_boolean_stereo_info,
	.get = pcm512x_digital_playback_चयन_get,
	.put = pcm512x_digital_playback_चयन_put
पूर्ण,

SOC_SINGLE("Deemphasis Switch", PCM512x_DSP, PCM512x_DEMP_SHIFT, 1, 1),
SOC_ENUM("DSP Program", pcm512x_dsp_program),

SOC_ENUM("Clock Missing Period", pcm512x_clk_missing),
SOC_ENUM("Auto Mute Time Left", pcm512x_स्वतःm_l),
SOC_ENUM("Auto Mute Time Right", pcm512x_स्वतःm_r),
SOC_SINGLE("Auto Mute Mono Switch", PCM512x_DIGITAL_MUTE_3,
	   PCM512x_ACTL_SHIFT, 1, 0),
SOC_DOUBLE("Auto Mute Switch", PCM512x_DIGITAL_MUTE_3, PCM512x_AMLE_SHIFT,
	   PCM512x_AMRE_SHIFT, 1, 0),

SOC_ENUM("Volume Ramp Down Rate", pcm512x_vndf),
SOC_ENUM("Volume Ramp Down Step", pcm512x_vnds),
SOC_ENUM("Volume Ramp Up Rate", pcm512x_vnuf),
SOC_ENUM("Volume Ramp Up Step", pcm512x_vnus),
SOC_ENUM("Volume Ramp Down Emergency Rate", pcm512x_vedf),
SOC_ENUM("Volume Ramp Down Emergency Step", pcm512x_veds),

SOC_SINGLE_EXT("Max Overclock PLL", SND_SOC_NOPM, 0, 20, 0,
	       pcm512x_overघड़ी_pll_get, pcm512x_overघड़ी_pll_put),
SOC_SINGLE_EXT("Max Overclock DSP", SND_SOC_NOPM, 0, 40, 0,
	       pcm512x_overघड़ी_dsp_get, pcm512x_overघड़ी_dsp_put),
SOC_SINGLE_EXT("Max Overclock DAC", SND_SOC_NOPM, 0, 40, 0,
	       pcm512x_overघड़ी_dac_get, pcm512x_overघड़ी_dac_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm512x_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DACL", शून्य, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_DAC("DACR", शून्य, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_OUTPUT("OUTL"),
SND_SOC_DAPM_OUTPUT("OUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm512x_dapm_routes[] = अणु
	अणु "DACL", शून्य, "Playback" पूर्ण,
	अणु "DACR", शून्य, "Playback" पूर्ण,

	अणु "OUTL", शून्य, "DACL" पूर्ण,
	अणु "OUTR", शून्य, "DACR" पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ pcm512x_pll_max(काष्ठा pcm512x_priv *pcm512x)
अणु
	वापस 25000000 + 25000000 * pcm512x->overघड़ी_pll / 100;
पूर्ण

अटल अचिन्हित दीर्घ pcm512x_dsp_max(काष्ठा pcm512x_priv *pcm512x)
अणु
	वापस 50000000 + 50000000 * pcm512x->overघड़ी_dsp / 100;
पूर्ण

अटल अचिन्हित दीर्घ pcm512x_dac_max(काष्ठा pcm512x_priv *pcm512x,
				     अचिन्हित दीर्घ rate)
अणु
	वापस rate + rate * pcm512x->overघड़ी_dac / 100;
पूर्ण

अटल अचिन्हित दीर्घ pcm512x_sck_max(काष्ठा pcm512x_priv *pcm512x)
अणु
	अगर (!pcm512x->pll_out)
		वापस 25000000;
	वापस pcm512x_pll_max(pcm512x);
पूर्ण

अटल अचिन्हित दीर्घ pcm512x_ncp_target(काष्ठा pcm512x_priv *pcm512x,
					अचिन्हित दीर्घ dac_rate)
अणु
	/*
	 * If the DAC is not actually overघड़ीed, use the good old
	 * NCP target rate...
	 */
	अगर (dac_rate <= 6144000)
		वापस 1536000;
	/*
	 * ...but अगर the DAC is in fact overघड़ीed, bump the NCP target
	 * rate to get the recommended भागiders even when overघड़ीing.
	 */
	वापस pcm512x_dac_max(pcm512x, 1536000);
पूर्ण

अटल स्थिर u32 pcm512x_dai_rates[] = अणु
	8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000,
	88200, 96000, 176400, 192000, 384000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_slave = अणु
	.count = ARRAY_SIZE(pcm512x_dai_rates),
	.list  = pcm512x_dai_rates,
पूर्ण;

अटल पूर्णांक pcm512x_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा pcm512x_priv *pcm512x = rule->निजी;
	काष्ठा snd_पूर्णांकerval ranges[2];
	पूर्णांक frame_size;

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0)
		वापस frame_size;

	चयन (frame_size) अणु
	हाल 32:
		/* No hole when the frame size is 32. */
		वापस 0;
	हाल 48:
	हाल 64:
		/* There is only one hole in the range of supported
		 * rates, but it moves with the frame size.
		 */
		स_रखो(ranges, 0, माप(ranges));
		ranges[0].min = 8000;
		ranges[0].max = pcm512x_sck_max(pcm512x) / frame_size / 2;
		ranges[1].min = DIV_ROUND_UP(16000000, frame_size);
		ranges[1].max = 384000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_पूर्णांकerval_ranges(hw_param_पूर्णांकerval(params, rule->var),
				   ARRAY_SIZE(ranges), ranges, 0);
पूर्ण

अटल पूर्णांक pcm512x_dai_startup_master(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = dai->dev;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums *स्थिरraपूर्णांकs_no_pll;
	काष्ठा snd_ratnum *rats_no_pll;

	अगर (IS_ERR(pcm512x->sclk)) अणु
		dev_err(dev, "Need SCLK for master mode: %ld\n",
			PTR_ERR(pcm512x->sclk));
		वापस PTR_ERR(pcm512x->sclk);
	पूर्ण

	अगर (pcm512x->pll_out)
		वापस snd_pcm_hw_rule_add(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_RATE,
					   pcm512x_hw_rule_rate,
					   pcm512x,
					   SNDRV_PCM_HW_PARAM_FRAME_BITS,
					   SNDRV_PCM_HW_PARAM_CHANNELS, -1);

	स्थिरraपूर्णांकs_no_pll = devm_kzalloc(dev, माप(*स्थिरraपूर्णांकs_no_pll),
					  GFP_KERNEL);
	अगर (!स्थिरraपूर्णांकs_no_pll)
		वापस -ENOMEM;
	स्थिरraपूर्णांकs_no_pll->nrats = 1;
	rats_no_pll = devm_kzalloc(dev, माप(*rats_no_pll), GFP_KERNEL);
	अगर (!rats_no_pll)
		वापस -ENOMEM;
	स्थिरraपूर्णांकs_no_pll->rats = rats_no_pll;
	rats_no_pll->num = clk_get_rate(pcm512x->sclk) / 64;
	rats_no_pll->den_min = 1;
	rats_no_pll->den_max = 128;
	rats_no_pll->den_step = 1;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_ratnums(substream->runसमय, 0,
					     SNDRV_PCM_HW_PARAM_RATE,
					     स्थिरraपूर्णांकs_no_pll);
पूर्ण

अटल पूर्णांक pcm512x_dai_startup_slave(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = dai->dev;
	काष्ठा regmap *regmap = pcm512x->regmap;

	अगर (IS_ERR(pcm512x->sclk)) अणु
		dev_info(dev, "No SCLK, using BCLK: %ld\n",
			 PTR_ERR(pcm512x->sclk));

		/* Disable reporting of missing SCLK as an error */
		regmap_update_bits(regmap, PCM512x_ERROR_DETECT,
				   PCM512x_IDCH, PCM512x_IDCH);

		/* Switch PLL input to BCLK */
		regmap_update_bits(regmap, PCM512x_PLL_REF,
				   PCM512x_SREF, PCM512x_SREF_BCK);
	पूर्ण

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &स्थिरraपूर्णांकs_slave);
पूर्ण

अटल पूर्णांक pcm512x_dai_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	चयन (pcm512x->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
		वापस pcm512x_dai_startup_master(substream, dai);

	हाल SND_SOC_DAIFMT_CBS_CFS:
		वापस pcm512x_dai_startup_slave(substream, dai);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक pcm512x_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा pcm512x_priv *pcm512x = dev_get_drvdata(component->dev);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_POWER,
					 PCM512x_RQST, 0);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to remove standby: %d\n",
				ret);
			वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_POWER,
					 PCM512x_RQST, PCM512x_RQST);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to request standby: %d\n",
				ret);
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ pcm512x_find_sck(काष्ठा snd_soc_dai *dai,
				      अचिन्हित दीर्घ bclk_rate)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ sck_rate;
	पूर्णांक घात2;

	/* 64 MHz <= pll_rate <= 100 MHz, VREF mode */
	/* 16 MHz <= sck_rate <=  25 MHz, VREF mode */

	/* select sck_rate as a multiple of bclk_rate but still with
	 * as many factors of 2 as possible, as that makes it easier
	 * to find a fast DAC rate
	 */
	घात2 = 1 << fls((pcm512x_pll_max(pcm512x) - 16000000) / bclk_rate);
	क्रम (; घात2; घात2 >>= 1) अणु
		sck_rate = roundकरोwn(pcm512x_pll_max(pcm512x),
				     bclk_rate * घात2);
		अगर (sck_rate >= 16000000)
			अवरोध;
	पूर्ण
	अगर (!घात2) अणु
		dev_err(dev, "Impossible to generate a suitable SCK\n");
		वापस 0;
	पूर्ण

	dev_dbg(dev, "sck_rate %lu\n", sck_rate);
	वापस sck_rate;
पूर्ण

/* pll_rate = pllin_rate * R * J.D / P
 * 1 <= R <= 16
 * 1 <= J <= 63
 * 0 <= D <= 9999
 * 1 <= P <= 15
 * 64 MHz <= pll_rate <= 100 MHz
 * अगर D == 0
 *     1 MHz <= pllin_rate / P <= 20 MHz
 * अन्यथा अगर D > 0
 *     6.667 MHz <= pllin_rate / P <= 20 MHz
 *     4 <= J <= 11
 *     R = 1
 */
अटल पूर्णांक pcm512x_find_pll_coeff(काष्ठा snd_soc_dai *dai,
				  अचिन्हित दीर्घ pllin_rate,
				  अचिन्हित दीर्घ pll_rate)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ common;
	पूर्णांक R, J, D, P;
	अचिन्हित दीर्घ K; /* 10000 * J.D */
	अचिन्हित दीर्घ num;
	अचिन्हित दीर्घ den;

	common = gcd(pll_rate, pllin_rate);
	dev_dbg(dev, "pll %lu pllin %lu common %lu\n",
		pll_rate, pllin_rate, common);
	num = pll_rate / common;
	den = pllin_rate / common;

	/* pllin_rate / P (or here, den) cannot be greater than 20 MHz */
	अगर (pllin_rate / den > 20000000 && num < 8) अणु
		num *= DIV_ROUND_UP(pllin_rate / den, 20000000);
		den *= DIV_ROUND_UP(pllin_rate / den, 20000000);
	पूर्ण
	dev_dbg(dev, "num / den = %lu / %lu\n", num, den);

	P = den;
	अगर (den <= 15 && num <= 16 * 63
	    && 1000000 <= pllin_rate / P && pllin_rate / P <= 20000000) अणु
		/* Try the हाल with D = 0 */
		D = 0;
		/* factor 'num' पूर्णांकo J and R, such that R <= 16 and J <= 63 */
		क्रम (R = 16; R; R--) अणु
			अगर (num % R)
				जारी;
			J = num / R;
			अगर (J == 0 || J > 63)
				जारी;

			dev_dbg(dev, "R * J / P = %d * %d / %d\n", R, J, P);
			pcm512x->real_pll = pll_rate;
			जाओ करोne;
		पूर्ण
		/* no luck */
	पूर्ण

	R = 1;

	अगर (num > 0xffffffffUL / 10000)
		जाओ fallback;

	/* Try to find an exact pll_rate using the D > 0 हाल */
	common = gcd(10000 * num, den);
	num = 10000 * num / common;
	den /= common;
	dev_dbg(dev, "num %lu den %lu common %lu\n", num, den, common);

	क्रम (P = den; P <= 15; P++) अणु
		अगर (pllin_rate / P < 6667000 || 200000000 < pllin_rate / P)
			जारी;
		अगर (num * P % den)
			जारी;
		K = num * P / den;
		/* J == 12 is ok अगर D == 0 */
		अगर (K < 40000 || K > 120000)
			जारी;

		J = K / 10000;
		D = K % 10000;
		dev_dbg(dev, "J.D / P = %d.%04d / %d\n", J, D, P);
		pcm512x->real_pll = pll_rate;
		जाओ करोne;
	पूर्ण

	/* Fall back to an approximate pll_rate */

fallback:
	/* find smallest possible P */
	P = DIV_ROUND_UP(pllin_rate, 20000000);
	अगर (!P)
		P = 1;
	अन्यथा अगर (P > 15) अणु
		dev_err(dev, "Need a slower clock as pll-input\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pllin_rate / P < 6667000) अणु
		dev_err(dev, "Need a faster clock as pll-input\n");
		वापस -EINVAL;
	पूर्ण
	K = DIV_ROUND_CLOSEST_ULL(10000ULL * pll_rate * P, pllin_rate);
	अगर (K < 40000)
		K = 40000;
	/* J == 12 is ok अगर D == 0 */
	अगर (K > 120000)
		K = 120000;
	J = K / 10000;
	D = K % 10000;
	dev_dbg(dev, "J.D / P ~ %d.%04d / %d\n", J, D, P);
	pcm512x->real_pll = DIV_ROUND_DOWN_ULL((u64)K * pllin_rate, 10000 * P);

करोne:
	pcm512x->pll_r = R;
	pcm512x->pll_j = J;
	pcm512x->pll_d = D;
	pcm512x->pll_p = P;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ pcm512x_pllin_dac_rate(काष्ठा snd_soc_dai *dai,
					    अचिन्हित दीर्घ osr_rate,
					    अचिन्हित दीर्घ pllin_rate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ dac_rate;

	अगर (!pcm512x->pll_out)
		वापस 0; /* no PLL to bypass, क्रमce SCK as DAC input */

	अगर (pllin_rate % osr_rate)
		वापस 0; /* futile, quit early */

	/* run DAC no faster than 6144000 Hz */
	क्रम (dac_rate = roundकरोwn(pcm512x_dac_max(pcm512x, 6144000), osr_rate);
	     dac_rate;
	     dac_rate -= osr_rate) अणु

		अगर (pllin_rate / dac_rate > 128)
			वापस 0; /* DAC भागider would be too big */

		अगर (!(pllin_rate % dac_rate))
			वापस dac_rate;

		dac_rate -= osr_rate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_set_भागiders(काष्ठा snd_soc_dai *dai,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ pllin_rate = 0;
	अचिन्हित दीर्घ pll_rate;
	अचिन्हित दीर्घ sck_rate;
	अचिन्हित दीर्घ mck_rate;
	अचिन्हित दीर्घ bclk_rate;
	अचिन्हित दीर्घ sample_rate;
	अचिन्हित दीर्घ osr_rate;
	अचिन्हित दीर्घ dacsrc_rate;
	पूर्णांक bclk_भाग;
	पूर्णांक lrclk_भाग;
	पूर्णांक dsp_भाग;
	पूर्णांक dac_भाग;
	अचिन्हित दीर्घ dac_rate;
	पूर्णांक ncp_भाग;
	पूर्णांक osr_भाग;
	पूर्णांक ret;
	पूर्णांक idac;
	पूर्णांक fssp;
	पूर्णांक gpio;

	अगर (pcm512x->bclk_ratio > 0) अणु
		lrclk_भाग = pcm512x->bclk_ratio;
	पूर्ण अन्यथा अणु
		lrclk_भाग = snd_soc_params_to_frame_size(params);

		अगर (lrclk_भाग == 0) अणु
			dev_err(dev, "No LRCLK?\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!pcm512x->pll_out) अणु
		sck_rate = clk_get_rate(pcm512x->sclk);
		bclk_rate = params_rate(params) * lrclk_भाग;
		bclk_भाग = DIV_ROUND_CLOSEST(sck_rate, bclk_rate);

		mck_rate = sck_rate;
	पूर्ण अन्यथा अणु
		ret = snd_soc_params_to_bclk(params);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to find suitable BCLK: %d\n", ret);
			वापस ret;
		पूर्ण
		अगर (ret == 0) अणु
			dev_err(dev, "No BCLK?\n");
			वापस -EINVAL;
		पूर्ण
		bclk_rate = ret;

		pllin_rate = clk_get_rate(pcm512x->sclk);

		sck_rate = pcm512x_find_sck(dai, bclk_rate);
		अगर (!sck_rate)
			वापस -EINVAL;
		pll_rate = 4 * sck_rate;

		ret = pcm512x_find_pll_coeff(dai, pllin_rate, pll_rate);
		अगर (ret != 0)
			वापस ret;

		ret = regmap_ग_लिखो(pcm512x->regmap,
				   PCM512x_PLL_COEFF_0, pcm512x->pll_p - 1);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to write PLL P: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(pcm512x->regmap,
				   PCM512x_PLL_COEFF_1, pcm512x->pll_j);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to write PLL J: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(pcm512x->regmap,
				   PCM512x_PLL_COEFF_2, pcm512x->pll_d >> 8);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to write PLL D msb: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(pcm512x->regmap,
				   PCM512x_PLL_COEFF_3, pcm512x->pll_d & 0xff);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to write PLL D lsb: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(pcm512x->regmap,
				   PCM512x_PLL_COEFF_4, pcm512x->pll_r - 1);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to write PLL R: %d\n", ret);
			वापस ret;
		पूर्ण

		mck_rate = pcm512x->real_pll;

		bclk_भाग = DIV_ROUND_CLOSEST(sck_rate, bclk_rate);
	पूर्ण

	अगर (bclk_भाग > 128) अणु
		dev_err(dev, "Failed to find BCLK divider\n");
		वापस -EINVAL;
	पूर्ण

	/* the actual rate */
	sample_rate = sck_rate / bclk_भाग / lrclk_भाग;
	osr_rate = 16 * sample_rate;

	/* run DSP no faster than 50 MHz */
	dsp_भाग = mck_rate > pcm512x_dsp_max(pcm512x) ? 2 : 1;

	dac_rate = pcm512x_pllin_dac_rate(dai, osr_rate, pllin_rate);
	अगर (dac_rate) अणु
		/* the desired घड़ी rate is "compatible" with the pll input
		 * घड़ी, so use that घड़ी as dac input instead of the pll
		 * output घड़ी since the pll will पूर्णांकroduce jitter and thus
		 * noise.
		 */
		dev_dbg(dev, "using pll input as dac input\n");
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_DAC_REF,
					 PCM512x_SDAC, PCM512x_SDAC_GPIO);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to set gpio as dacref: %d\n", ret);
			वापस ret;
		पूर्ण

		gpio = PCM512x_GREF_GPIO1 + pcm512x->pll_in - 1;
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_GPIO_DACIN,
					 PCM512x_GREF, gpio);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to set gpio %d as dacin: %d\n",
				pcm512x->pll_in, ret);
			वापस ret;
		पूर्ण

		dacsrc_rate = pllin_rate;
	पूर्ण अन्यथा अणु
		/* run DAC no faster than 6144000 Hz */
		अचिन्हित दीर्घ dac_mul = pcm512x_dac_max(pcm512x, 6144000)
			/ osr_rate;
		अचिन्हित दीर्घ sck_mul = sck_rate / osr_rate;

		क्रम (; dac_mul; dac_mul--) अणु
			अगर (!(sck_mul % dac_mul))
				अवरोध;
		पूर्ण
		अगर (!dac_mul) अणु
			dev_err(dev, "Failed to find DAC rate\n");
			वापस -EINVAL;
		पूर्ण

		dac_rate = dac_mul * osr_rate;
		dev_dbg(dev, "dac_rate %lu sample_rate %lu\n",
			dac_rate, sample_rate);

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_DAC_REF,
					 PCM512x_SDAC, PCM512x_SDAC_SCK);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to set sck as dacref: %d\n", ret);
			वापस ret;
		पूर्ण

		dacsrc_rate = sck_rate;
	पूर्ण

	osr_भाग = DIV_ROUND_CLOSEST(dac_rate, osr_rate);
	अगर (osr_भाग > 128) अणु
		dev_err(dev, "Failed to find OSR divider\n");
		वापस -EINVAL;
	पूर्ण

	dac_भाग = DIV_ROUND_CLOSEST(dacsrc_rate, dac_rate);
	अगर (dac_भाग > 128) अणु
		dev_err(dev, "Failed to find DAC divider\n");
		वापस -EINVAL;
	पूर्ण
	dac_rate = dacsrc_rate / dac_भाग;

	ncp_भाग = DIV_ROUND_CLOSEST(dac_rate,
				    pcm512x_ncp_target(pcm512x, dac_rate));
	अगर (ncp_भाग > 128 || dac_rate / ncp_भाग > 2048000) अणु
		/* run NCP no faster than 2048000 Hz, but why? */
		ncp_भाग = DIV_ROUND_UP(dac_rate, 2048000);
		अगर (ncp_भाग > 128) अणु
			dev_err(dev, "Failed to find NCP divider\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	idac = mck_rate / (dsp_भाग * sample_rate);

	ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_DSP_CLKDIV, dsp_भाग - 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write DSP divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_DAC_CLKDIV, dac_भाग - 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write DAC divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_NCP_CLKDIV, ncp_भाग - 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write NCP divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_OSR_CLKDIV, osr_भाग - 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write OSR divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap,
			   PCM512x_MASTER_CLKDIV_1, bclk_भाग - 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write BCLK divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap,
			   PCM512x_MASTER_CLKDIV_2, lrclk_भाग - 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write LRCLK divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_IDAC_1, idac >> 8);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write IDAC msb divider: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_IDAC_2, idac & 0xff);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write IDAC lsb divider: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (sample_rate <= pcm512x_dac_max(pcm512x, 48000))
		fssp = PCM512x_FSSP_48KHZ;
	अन्यथा अगर (sample_rate <= pcm512x_dac_max(pcm512x, 96000))
		fssp = PCM512x_FSSP_96KHZ;
	अन्यथा अगर (sample_rate <= pcm512x_dac_max(pcm512x, 192000))
		fssp = PCM512x_FSSP_192KHZ;
	अन्यथा
		fssp = PCM512x_FSSP_384KHZ;
	ret = regmap_update_bits(pcm512x->regmap, PCM512x_FS_SPEED_MODE,
				 PCM512x_FSSP, fssp);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set fs speed: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "DSP divider %d\n", dsp_भाग);
	dev_dbg(component->dev, "DAC divider %d\n", dac_भाग);
	dev_dbg(component->dev, "NCP divider %d\n", ncp_भाग);
	dev_dbg(component->dev, "OSR divider %d\n", osr_भाग);
	dev_dbg(component->dev, "BCK divider %d\n", bclk_भाग);
	dev_dbg(component->dev, "LRCK divider %d\n", lrclk_भाग);
	dev_dbg(component->dev, "IDAC %d\n", idac);
	dev_dbg(component->dev, "1<<FSSP %d\n", 1 << fssp);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	पूर्णांक alen;
	पूर्णांक gpio;
	पूर्णांक ret;

	dev_dbg(component->dev, "hw_params %u Hz, %u channels\n",
		params_rate(params),
		params_channels(params));

	चयन (params_width(params)) अणु
	हाल 16:
		alen = PCM512x_ALEN_16;
		अवरोध;
	हाल 20:
		alen = PCM512x_ALEN_20;
		अवरोध;
	हाल 24:
		alen = PCM512x_ALEN_24;
		अवरोध;
	हाल 32:
		alen = PCM512x_ALEN_32;
		अवरोध;
	शेष:
		dev_err(component->dev, "Bad frame size: %d\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_I2S_1,
				 PCM512x_ALEN, alen);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set frame size: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर ((pcm512x->fmt & SND_SOC_DAIFMT_MASTER_MASK) ==
	    SND_SOC_DAIFMT_CBS_CFS) अणु
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_ERROR_DETECT,
					 PCM512x_DCAS, 0);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to enable clock divider autoset: %d\n",
				ret);
			वापस ret;
		पूर्ण
		जाओ skip_pll;
	पूर्ण

	अगर (pcm512x->pll_out) अणु
		ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_FLEX_A, 0x11);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to set FLEX_A: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(pcm512x->regmap, PCM512x_FLEX_B, 0xff);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to set FLEX_B: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_ERROR_DETECT,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_IDCM | PCM512x_DCAS
					 | PCM512x_IPLK,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_DCAS);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to ignore auto-clock failures: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_ERROR_DETECT,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_IDCM | PCM512x_DCAS
					 | PCM512x_IPLK,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_DCAS | PCM512x_IPLK);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to ignore auto-clock failures: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_PLL_EN,
					 PCM512x_PLLE, 0);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to disable pll: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = pcm512x_set_भागiders(dai, params);
	अगर (ret != 0)
		वापस ret;

	अगर (pcm512x->pll_out) अणु
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_PLL_REF,
					 PCM512x_SREF, PCM512x_SREF_GPIO);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to set gpio as pllref: %d\n", ret);
			वापस ret;
		पूर्ण

		gpio = PCM512x_GREF_GPIO1 + pcm512x->pll_in - 1;
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_GPIO_PLLIN,
					 PCM512x_GREF, gpio);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to set gpio %d as pllin: %d\n",
				pcm512x->pll_in, ret);
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_PLL_EN,
					 PCM512x_PLLE, PCM512x_PLLE);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to enable pll: %d\n", ret);
			वापस ret;
		पूर्ण

		gpio = PCM512x_G1OE << (pcm512x->pll_out - 1);
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_GPIO_EN,
					 gpio, gpio);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to enable gpio %d: %d\n",
				pcm512x->pll_out, ret);
			वापस ret;
		पूर्ण

		gpio = PCM512x_GPIO_OUTPUT_1 + pcm512x->pll_out - 1;
		ret = regmap_update_bits(pcm512x->regmap, gpio,
					 PCM512x_GxSL, PCM512x_GxSL_PLLCK);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to output pll on %d: %d\n",
				ret, pcm512x->pll_out);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_SYNCHRONIZE,
				 PCM512x_RQSY, PCM512x_RQSY_HALT);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to halt clocks: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_SYNCHRONIZE,
				 PCM512x_RQSY, PCM512x_RQSY_RESUME);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to resume clocks: %d\n", ret);
		वापस ret;
	पूर्ण

skip_pll:
	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	पूर्णांक afmt;
	पूर्णांक offset = 0;
	पूर्णांक घड़ी_output;
	पूर्णांक master_mode;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		घड़ी_output = 0;
		master_mode = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		घड़ी_output = PCM512x_BCKO | PCM512x_LRKO;
		master_mode = PCM512x_RLRK | PCM512x_RBCK;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		घड़ी_output = PCM512x_BCKO;
		master_mode = PCM512x_RBCK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_BCLK_LRCLK_CFG,
				 PCM512x_BCKP | PCM512x_BCKO | PCM512x_LRKO,
				 घड़ी_output);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable clock output: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_MASTER_MODE,
				 PCM512x_RLRK | PCM512x_RBCK,
				 master_mode);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable master mode: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		afmt = PCM512x_AFMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		afmt = PCM512x_AFMT_RTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		afmt = PCM512x_AFMT_LTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		offset = 1;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_B:
		afmt = PCM512x_AFMT_DSP;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported DAI format: 0x%x\n",
			pcm512x->fmt);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_I2S_1,
				 PCM512x_AFMT, afmt);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set data format: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_I2S_2,
				 0xFF, offset);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set data offset: %d\n", ret);
		वापस ret;
	पूर्ण

	pcm512x->fmt = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	अगर (ratio > 256)
		वापस -EINVAL;

	pcm512x->bclk_ratio = ratio;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	अचिन्हित पूर्णांक mute_det;

	mutex_lock(&pcm512x->mutex);

	अगर (mute) अणु
		pcm512x->mute |= 0x1;
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_MUTE,
					 PCM512x_RQML | PCM512x_RQMR,
					 PCM512x_RQML | PCM512x_RQMR);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to set digital mute: %d\n", ret);
			जाओ unlock;
		पूर्ण

		regmap_पढ़ो_poll_समयout(pcm512x->regmap,
					 PCM512x_ANALOG_MUTE_DET,
					 mute_det, (mute_det & 0x3) == 0,
					 200, 10000);
	पूर्ण अन्यथा अणु
		pcm512x->mute &= ~0x1;
		ret = pcm512x_update_mute(pcm512x);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to update digital mute: %d\n", ret);
			जाओ unlock;
		पूर्ण

		regmap_पढ़ो_poll_समयout(pcm512x->regmap,
					 PCM512x_ANALOG_MUTE_DET,
					 mute_det,
					 (mute_det & 0x3)
					 == ((~pcm512x->mute >> 1) & 0x3),
					 200, 10000);
	पूर्ण

unlock:
	mutex_unlock(&pcm512x->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm512x_dai_ops = अणु
	.startup = pcm512x_dai_startup,
	.hw_params = pcm512x_hw_params,
	.set_fmt = pcm512x_set_fmt,
	.mute_stream = pcm512x_mute,
	.set_bclk_ratio = pcm512x_set_bclk_ratio,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm512x_dai = अणु
	.name = "pcm512x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 8000,
		.rate_max = 384000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE
	पूर्ण,
	.ops = &pcm512x_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver pcm512x_component_driver = अणु
	.set_bias_level		= pcm512x_set_bias_level,
	.controls		= pcm512x_controls,
	.num_controls		= ARRAY_SIZE(pcm512x_controls),
	.dapm_widमाला_लो		= pcm512x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm512x_dapm_widमाला_लो),
	.dapm_routes		= pcm512x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm512x_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg pcm512x_range = अणु
	.name = "Pages", .range_min = PCM512x_VIRT_BASE,
	.range_max = PCM512x_MAX_REGISTER,
	.selector_reg = PCM512x_PAGE,
	.selector_mask = 0xff,
	.winकरोw_start = 0, .winकरोw_len = 0x100,
पूर्ण;

स्थिर काष्ठा regmap_config pcm512x_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ोable_reg = pcm512x_पढ़ोable,
	.अस्थिर_reg = pcm512x_अस्थिर,

	.ranges = &pcm512x_range,
	.num_ranges = 1,

	.max_रेजिस्टर = PCM512x_MAX_REGISTER,
	.reg_शेषs = pcm512x_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(pcm512x_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(pcm512x_regmap);

पूर्णांक pcm512x_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा pcm512x_priv *pcm512x;
	पूर्णांक i, ret;

	pcm512x = devm_kzalloc(dev, माप(काष्ठा pcm512x_priv), GFP_KERNEL);
	अगर (!pcm512x)
		वापस -ENOMEM;

	mutex_init(&pcm512x->mutex);

	dev_set_drvdata(dev, pcm512x);
	pcm512x->regmap = regmap;

	क्रम (i = 0; i < ARRAY_SIZE(pcm512x->supplies); i++)
		pcm512x->supplies[i].supply = pcm512x_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(pcm512x->supplies),
				      pcm512x->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	pcm512x->supply_nb[0].notअगरier_call = pcm512x_regulator_event_0;
	pcm512x->supply_nb[1].notअगरier_call = pcm512x_regulator_event_1;
	pcm512x->supply_nb[2].notअगरier_call = pcm512x_regulator_event_2;

	क्रम (i = 0; i < ARRAY_SIZE(pcm512x->supplies); i++) अणु
		ret = devm_regulator_रेजिस्टर_notअगरier(
						pcm512x->supplies[i].consumer,
						&pcm512x->supply_nb[i]);
		अगर (ret != 0) अणु
			dev_err(dev,
				"Failed to register regulator notifier: %d\n",
				ret);
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(pcm512x->supplies),
				    pcm512x->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset the device, verअगरying I/O in the process क्रम I2C */
	ret = regmap_ग_लिखो(regmap, PCM512x_RESET,
			   PCM512x_RSTM | PCM512x_RSTR);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to reset device: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, PCM512x_RESET, 0);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to reset device: %d\n", ret);
		जाओ err;
	पूर्ण

	pcm512x->sclk = devm_clk_get(dev, शून्य);
	अगर (PTR_ERR(pcm512x->sclk) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ err;
	पूर्ण
	अगर (!IS_ERR(pcm512x->sclk)) अणु
		ret = clk_prepare_enable(pcm512x->sclk);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to enable SCLK: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	/* Default to standby mode */
	ret = regmap_update_bits(pcm512x->regmap, PCM512x_POWER,
				 PCM512x_RQST, PCM512x_RQST);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request standby: %d\n",
			ret);
		जाओ err_clk;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

#अगर_घोषित CONFIG_OF
	अगर (dev->of_node) अणु
		स्थिर काष्ठा device_node *np = dev->of_node;
		u32 val;

		अगर (of_property_पढ़ो_u32(np, "pll-in", &val) >= 0) अणु
			अगर (val > 6) अणु
				dev_err(dev, "Invalid pll-in\n");
				ret = -EINVAL;
				जाओ err_clk;
			पूर्ण
			pcm512x->pll_in = val;
		पूर्ण

		अगर (of_property_पढ़ो_u32(np, "pll-out", &val) >= 0) अणु
			अगर (val > 6) अणु
				dev_err(dev, "Invalid pll-out\n");
				ret = -EINVAL;
				जाओ err_clk;
			पूर्ण
			pcm512x->pll_out = val;
		पूर्ण

		अगर (!pcm512x->pll_in != !pcm512x->pll_out) अणु
			dev_err(dev,
				"Error: both pll-in and pll-out, or none\n");
			ret = -EINVAL;
			जाओ err_clk;
		पूर्ण
		अगर (pcm512x->pll_in && pcm512x->pll_in == pcm512x->pll_out) अणु
			dev_err(dev, "Error: pll-in == pll-out\n");
			ret = -EINVAL;
			जाओ err_clk;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	ret = devm_snd_soc_रेजिस्टर_component(dev, &pcm512x_component_driver,
				    &pcm512x_dai, 1);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to register CODEC: %d\n", ret);
		जाओ err_pm;
	पूर्ण

	वापस 0;

err_pm:
	pm_runसमय_disable(dev);
err_clk:
	अगर (!IS_ERR(pcm512x->sclk))
		clk_disable_unprepare(pcm512x->sclk);
err:
	regulator_bulk_disable(ARRAY_SIZE(pcm512x->supplies),
				     pcm512x->supplies);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pcm512x_probe);

व्योम pcm512x_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा pcm512x_priv *pcm512x = dev_get_drvdata(dev);

	pm_runसमय_disable(dev);
	अगर (!IS_ERR(pcm512x->sclk))
		clk_disable_unprepare(pcm512x->sclk);
	regulator_bulk_disable(ARRAY_SIZE(pcm512x->supplies),
			       pcm512x->supplies);
पूर्ण
EXPORT_SYMBOL_GPL(pcm512x_हटाओ);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pcm512x_suspend(काष्ठा device *dev)
अणु
	काष्ठा pcm512x_priv *pcm512x = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_POWER,
				 PCM512x_RQPD, PCM512x_RQPD);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request power down: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_disable(ARRAY_SIZE(pcm512x->supplies),
				     pcm512x->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to disable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!IS_ERR(pcm512x->sclk))
		clk_disable_unprepare(pcm512x->sclk);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm512x_resume(काष्ठा device *dev)
अणु
	काष्ठा pcm512x_priv *pcm512x = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!IS_ERR(pcm512x->sclk)) अणु
		ret = clk_prepare_enable(pcm512x->sclk);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to enable SCLK: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(pcm512x->supplies),
				    pcm512x->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(pcm512x->regmap, false);
	ret = regcache_sync(pcm512x->regmap);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to sync cache: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_POWER,
				 PCM512x_RQPD, 0);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to remove power down: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops pcm512x_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pcm512x_suspend, pcm512x_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(pcm512x_pm_ops);

MODULE_DESCRIPTION("ASoC PCM512x codec driver");
MODULE_AUTHOR("Mark Brown <broonie@kernel.org>");
MODULE_LICENSE("GPL v2");
