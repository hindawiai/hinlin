<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/sound/soc/codecs/tlv320aic32x4.c
 *
 * Copyright 2011 Vista Silicon S.L.
 *
 * Author: Javier Martin <javier.martin@vista-silicon.com>
 *
 * Based on sound/soc/codecs/wm8974 and TI driver क्रम kernel 2.6.27.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/tlv320aic32x4.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "tlv320aic32x4.h"

काष्ठा aic32x4_priv अणु
	काष्ठा regmap *regmap;
	u32 घातer_cfg;
	u32 micpga_routing;
	bool swapdacs;
	पूर्णांक rstn_gpio;
	स्थिर अक्षर *mclk_name;

	काष्ठा regulator *supply_lकरो;
	काष्ठा regulator *supply_iov;
	काष्ठा regulator *supply_dv;
	काष्ठा regulator *supply_av;

	काष्ठा aic32x4_setup_data *setup;
	काष्ठा device *dev;
पूर्ण;

अटल पूर्णांक aic32x4_reset_adc(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u32 adc_reg;

	/*
	 * Workaround: the datasheet करोes not mention a required programming
	 * sequence but experiments show the ADC needs to be reset after each
	 * capture to aव्योम audible artअगरacts.
	 */
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		adc_reg = snd_soc_component_पढ़ो(component, AIC32X4_ADCSETUP);
		snd_soc_component_ग_लिखो(component, AIC32X4_ADCSETUP, adc_reg |
					AIC32X4_LADC_EN | AIC32X4_RADC_EN);
		snd_soc_component_ग_लिखो(component, AIC32X4_ADCSETUP, adc_reg);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण;

अटल पूर्णांक mic_bias_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Change Mic Bias Registor */
		snd_soc_component_update_bits(component, AIC32X4_MICBIAS,
				AIC32x4_MICBIAS_MASK,
				AIC32X4_MICBIAS_LDOIN |
				AIC32X4_MICBIAS_2075V);
		prपूर्णांकk(KERN_DEBUG "%s: Mic Bias will be turned ON\n", __func__);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, AIC32X4_MICBIAS,
				AIC32x4_MICBIAS_MASK, 0);
		prपूर्णांकk(KERN_DEBUG "%s: Mic Bias will be turned OFF\n",
				__func__);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक aic32x4_get_mfp1_gpio(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	u8 val;

	val = snd_soc_component_पढ़ो(component, AIC32X4_DINCTL);

	ucontrol->value.पूर्णांकeger.value[0] = (val & 0x01);

	वापस 0;
पूर्ण;

अटल पूर्णांक aic32x4_set_mfp2_gpio(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	u8 val;
	u8 gpio_check;

	val = snd_soc_component_पढ़ो(component, AIC32X4_DOUTCTL);
	gpio_check = (val & AIC32X4_MFP_GPIO_ENABLED);
	अगर (gpio_check != AIC32X4_MFP_GPIO_ENABLED) अणु
		prपूर्णांकk(KERN_ERR "%s: MFP2 is not configure as a GPIO output\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (ucontrol->value.पूर्णांकeger.value[0] == (val & AIC32X4_MFP2_GPIO_OUT_HIGH))
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा
		val &= ~AIC32X4_MFP2_GPIO_OUT_HIGH;

	snd_soc_component_ग_लिखो(component, AIC32X4_DOUTCTL, val);

	वापस 0;
पूर्ण;

अटल पूर्णांक aic32x4_get_mfp3_gpio(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	u8 val;

	val = snd_soc_component_पढ़ो(component, AIC32X4_SCLKCTL);

	ucontrol->value.पूर्णांकeger.value[0] = (val & 0x01);

	वापस 0;
पूर्ण;

अटल पूर्णांक aic32x4_set_mfp4_gpio(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	u8 val;
	u8 gpio_check;

	val = snd_soc_component_पढ़ो(component, AIC32X4_MISOCTL);
	gpio_check = (val & AIC32X4_MFP_GPIO_ENABLED);
	अगर (gpio_check != AIC32X4_MFP_GPIO_ENABLED) अणु
		prपूर्णांकk(KERN_ERR "%s: MFP4 is not configure as a GPIO output\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (ucontrol->value.पूर्णांकeger.value[0] == (val & AIC32X4_MFP5_GPIO_OUT_HIGH))
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा
		val &= ~AIC32X4_MFP5_GPIO_OUT_HIGH;

	snd_soc_component_ग_लिखो(component, AIC32X4_MISOCTL, val);

	वापस 0;
पूर्ण;

अटल पूर्णांक aic32x4_get_mfp5_gpio(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	u8 val;

	val = snd_soc_component_पढ़ो(component, AIC32X4_GPIOCTL);
	ucontrol->value.पूर्णांकeger.value[0] = ((val & 0x2) >> 1);

	वापस 0;
पूर्ण;

अटल पूर्णांक aic32x4_set_mfp5_gpio(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	u8 val;
	u8 gpio_check;

	val = snd_soc_component_पढ़ो(component, AIC32X4_GPIOCTL);
	gpio_check = (val & AIC32X4_MFP5_GPIO_OUTPUT);
	अगर (gpio_check != AIC32X4_MFP5_GPIO_OUTPUT) अणु
		prपूर्णांकk(KERN_ERR "%s: MFP5 is not configure as a GPIO output\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (ucontrol->value.पूर्णांकeger.value[0] == (val & 0x1))
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा
		val &= 0xfe;

	snd_soc_component_ग_लिखो(component, AIC32X4_GPIOCTL, val);

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic32x4_mfp1[] = अणु
	SOC_SINGLE_BOOL_EXT("MFP1 GPIO", 0, aic32x4_get_mfp1_gpio, शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic32x4_mfp2[] = अणु
	SOC_SINGLE_BOOL_EXT("MFP2 GPIO", 0, शून्य, aic32x4_set_mfp2_gpio),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic32x4_mfp3[] = अणु
	SOC_SINGLE_BOOL_EXT("MFP3 GPIO", 0, aic32x4_get_mfp3_gpio, शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic32x4_mfp4[] = अणु
	SOC_SINGLE_BOOL_EXT("MFP4 GPIO", 0, शून्य, aic32x4_set_mfp4_gpio),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic32x4_mfp5[] = अणु
	SOC_SINGLE_BOOL_EXT("MFP5 GPIO", 0, aic32x4_get_mfp5_gpio,
		aic32x4_set_mfp5_gpio),
पूर्ण;

/* 0dB min, 0.5dB steps */
अटल DECLARE_TLV_DB_SCALE(tlv_step_0_5, 0, 50, 0);
/* -63.5dB min, 0.5dB steps */
अटल DECLARE_TLV_DB_SCALE(tlv_pcm, -6350, 50, 0);
/* -6dB min, 1dB steps */
अटल DECLARE_TLV_DB_SCALE(tlv_driver_gain, -600, 100, 0);
/* -12dB min, 0.5dB steps */
अटल DECLARE_TLV_DB_SCALE(tlv_adc_vol, -1200, 50, 0);

अटल स्थिर अक्षर * स्थिर lo_cm_text[] = अणु
	"Full Chip", "1.65V",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lo_cm_क्रमागत, AIC32X4_CMMODE, 3, lo_cm_text);

अटल स्थिर अक्षर * स्थिर pपंचांग_text[] = अणु
	"P3", "P2", "P1",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(l_pपंचांग_क्रमागत, AIC32X4_LPLAYBACK, 2, pपंचांग_text);
अटल SOC_ENUM_SINGLE_DECL(r_pपंचांग_क्रमागत, AIC32X4_RPLAYBACK, 2, pपंचांग_text);

अटल स्थिर काष्ठा snd_kcontrol_new aic32x4_snd_controls[] = अणु
	SOC_DOUBLE_R_S_TLV("PCM Playback Volume", AIC32X4_LDACVOL,
			AIC32X4_RDACVOL, 0, -0x7f, 0x30, 7, 0, tlv_pcm),
	SOC_ENUM("DAC Left Playback PowerTune Switch", l_pपंचांग_क्रमागत),
	SOC_ENUM("DAC Right Playback PowerTune Switch", r_pपंचांग_क्रमागत),
	SOC_DOUBLE_R_S_TLV("HP Driver Gain Volume", AIC32X4_HPLGAIN,
			AIC32X4_HPRGAIN, 0, -0x6, 0x1d, 5, 0,
			tlv_driver_gain),
	SOC_DOUBLE_R_S_TLV("LO Driver Gain Volume", AIC32X4_LOLGAIN,
			AIC32X4_LORGAIN, 0, -0x6, 0x1d, 5, 0,
			tlv_driver_gain),
	SOC_DOUBLE_R("HP DAC Playback Switch", AIC32X4_HPLGAIN,
			AIC32X4_HPRGAIN, 6, 0x01, 1),
	SOC_DOUBLE_R("LO DAC Playback Switch", AIC32X4_LOLGAIN,
			AIC32X4_LORGAIN, 6, 0x01, 1),
	SOC_ENUM("LO Playback Common Mode Switch", lo_cm_क्रमागत),
	SOC_DOUBLE_R("Mic PGA Switch", AIC32X4_LMICPGAVOL,
			AIC32X4_RMICPGAVOL, 7, 0x01, 1),

	SOC_SINGLE("ADCFGA Left Mute Switch", AIC32X4_ADCFGA, 7, 1, 0),
	SOC_SINGLE("ADCFGA Right Mute Switch", AIC32X4_ADCFGA, 3, 1, 0),

	SOC_DOUBLE_R_S_TLV("ADC Level Volume", AIC32X4_LADCVOL,
			AIC32X4_RADCVOL, 0, -0x18, 0x28, 6, 0, tlv_adc_vol),
	SOC_DOUBLE_R_TLV("PGA Level Volume", AIC32X4_LMICPGAVOL,
			AIC32X4_RMICPGAVOL, 0, 0x5f, 0, tlv_step_0_5),

	SOC_SINGLE("Auto-mute Switch", AIC32X4_DACMUTE, 4, 7, 0),

	SOC_SINGLE("AGC Left Switch", AIC32X4_LAGC1, 7, 1, 0),
	SOC_SINGLE("AGC Right Switch", AIC32X4_RAGC1, 7, 1, 0),
	SOC_DOUBLE_R("AGC Target Level", AIC32X4_LAGC1, AIC32X4_RAGC1,
			4, 0x07, 0),
	SOC_DOUBLE_R("AGC Gain Hysteresis", AIC32X4_LAGC1, AIC32X4_RAGC1,
			0, 0x03, 0),
	SOC_DOUBLE_R("AGC Hysteresis", AIC32X4_LAGC2, AIC32X4_RAGC2,
			6, 0x03, 0),
	SOC_DOUBLE_R("AGC Noise Threshold", AIC32X4_LAGC2, AIC32X4_RAGC2,
			1, 0x1F, 0),
	SOC_DOUBLE_R("AGC Max PGA", AIC32X4_LAGC3, AIC32X4_RAGC3,
			0, 0x7F, 0),
	SOC_DOUBLE_R("AGC Attack Time", AIC32X4_LAGC4, AIC32X4_RAGC4,
			3, 0x1F, 0),
	SOC_DOUBLE_R("AGC Decay Time", AIC32X4_LAGC5, AIC32X4_RAGC5,
			3, 0x1F, 0),
	SOC_DOUBLE_R("AGC Noise Debounce", AIC32X4_LAGC6, AIC32X4_RAGC6,
			0, 0x1F, 0),
	SOC_DOUBLE_R("AGC Signal Debounce", AIC32X4_LAGC7, AIC32X4_RAGC7,
			0, 0x0F, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new hpl_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("L_DAC Switch", AIC32X4_HPLROUTE, 3, 1, 0),
	SOC_DAPM_SINGLE("IN1_L Switch", AIC32X4_HPLROUTE, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new hpr_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("R_DAC Switch", AIC32X4_HPRROUTE, 3, 1, 0),
	SOC_DAPM_SINGLE("IN1_R Switch", AIC32X4_HPRROUTE, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lol_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("L_DAC Switch", AIC32X4_LOLROUTE, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lor_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("R_DAC Switch", AIC32X4_LORROUTE, 3, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर resistor_text[] = अणु
	"Off", "10 kOhm", "20 kOhm", "40 kOhm",
पूर्ण;

/* Left mixer pins */
अटल SOC_ENUM_SINGLE_DECL(in1l_lpga_p_क्रमागत, AIC32X4_LMICPGAPIN, 6, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in2l_lpga_p_क्रमागत, AIC32X4_LMICPGAPIN, 4, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in3l_lpga_p_क्रमागत, AIC32X4_LMICPGAPIN, 2, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in1r_lpga_p_क्रमागत, AIC32X4_LMICPGAPIN, 0, resistor_text);

अटल SOC_ENUM_SINGLE_DECL(cml_lpga_n_क्रमागत, AIC32X4_LMICPGANIN, 6, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in2r_lpga_n_क्रमागत, AIC32X4_LMICPGANIN, 4, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in3r_lpga_n_क्रमागत, AIC32X4_LMICPGANIN, 2, resistor_text);

अटल स्थिर काष्ठा snd_kcontrol_new in1l_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN1_L L+ Switch", in1l_lpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in2l_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN2_L L+ Switch", in2l_lpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in3l_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN3_L L+ Switch", in3l_lpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in1r_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN1_R L+ Switch", in1r_lpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new cml_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("CM_L L- Switch", cml_lpga_n_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in2r_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN2_R L- Switch", in2r_lpga_n_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in3r_to_lmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN3_R L- Switch", in3r_lpga_n_क्रमागत),
पूर्ण;

/*	Right mixer pins */
अटल SOC_ENUM_SINGLE_DECL(in1r_rpga_p_क्रमागत, AIC32X4_RMICPGAPIN, 6, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in2r_rpga_p_क्रमागत, AIC32X4_RMICPGAPIN, 4, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in3r_rpga_p_क्रमागत, AIC32X4_RMICPGAPIN, 2, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in2l_rpga_p_क्रमागत, AIC32X4_RMICPGAPIN, 0, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(cmr_rpga_n_क्रमागत, AIC32X4_RMICPGANIN, 6, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in1l_rpga_n_क्रमागत, AIC32X4_RMICPGANIN, 4, resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in3l_rpga_n_क्रमागत, AIC32X4_RMICPGANIN, 2, resistor_text);

अटल स्थिर काष्ठा snd_kcontrol_new in1r_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN1_R R+ Switch", in1r_rpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in2r_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN2_R R+ Switch", in2r_rpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in3r_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN3_R R+ Switch", in3r_rpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in2l_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN2_L R+ Switch", in2l_rpga_p_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new cmr_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("CM_R R- Switch", cmr_rpga_n_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in1l_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN1_L R- Switch", in1l_rpga_n_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in3l_to_rmixer_controls[] = अणु
	SOC_DAPM_ENUM("IN3_L R- Switch", in3l_rpga_n_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aic32x4_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", AIC32X4_DACSETUP, 7, 0),
	SND_SOC_DAPM_MIXER("HPL Output Mixer", SND_SOC_NOPM, 0, 0,
			   &hpl_output_mixer_controls[0],
			   ARRAY_SIZE(hpl_output_mixer_controls)),
	SND_SOC_DAPM_PGA("HPL Power", AIC32X4_OUTPWRCTL, 5, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("LOL Output Mixer", SND_SOC_NOPM, 0, 0,
			   &lol_output_mixer_controls[0],
			   ARRAY_SIZE(lol_output_mixer_controls)),
	SND_SOC_DAPM_PGA("LOL Power", AIC32X4_OUTPWRCTL, 3, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", AIC32X4_DACSETUP, 6, 0),
	SND_SOC_DAPM_MIXER("HPR Output Mixer", SND_SOC_NOPM, 0, 0,
			   &hpr_output_mixer_controls[0],
			   ARRAY_SIZE(hpr_output_mixer_controls)),
	SND_SOC_DAPM_PGA("HPR Power", AIC32X4_OUTPWRCTL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("LOR Output Mixer", SND_SOC_NOPM, 0, 0,
			   &lor_output_mixer_controls[0],
			   ARRAY_SIZE(lor_output_mixer_controls)),
	SND_SOC_DAPM_PGA("LOR Power", AIC32X4_OUTPWRCTL, 2, 0, शून्य, 0),

	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", AIC32X4_ADCSETUP, 6, 0),
	SND_SOC_DAPM_MUX("IN1_R to Right Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in1r_to_rmixer_controls),
	SND_SOC_DAPM_MUX("IN2_R to Right Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in2r_to_rmixer_controls),
	SND_SOC_DAPM_MUX("IN3_R to Right Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in3r_to_rmixer_controls),
	SND_SOC_DAPM_MUX("IN2_L to Right Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in2l_to_rmixer_controls),
	SND_SOC_DAPM_MUX("CM_R to Right Mixer Negative Resistor", SND_SOC_NOPM, 0, 0,
			cmr_to_rmixer_controls),
	SND_SOC_DAPM_MUX("IN1_L to Right Mixer Negative Resistor", SND_SOC_NOPM, 0, 0,
			in1l_to_rmixer_controls),
	SND_SOC_DAPM_MUX("IN3_L to Right Mixer Negative Resistor", SND_SOC_NOPM, 0, 0,
			in3l_to_rmixer_controls),

	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", AIC32X4_ADCSETUP, 7, 0),
	SND_SOC_DAPM_MUX("IN1_L to Left Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in1l_to_lmixer_controls),
	SND_SOC_DAPM_MUX("IN2_L to Left Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in2l_to_lmixer_controls),
	SND_SOC_DAPM_MUX("IN3_L to Left Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in3l_to_lmixer_controls),
	SND_SOC_DAPM_MUX("IN1_R to Left Mixer Positive Resistor", SND_SOC_NOPM, 0, 0,
			in1r_to_lmixer_controls),
	SND_SOC_DAPM_MUX("CM_L to Left Mixer Negative Resistor", SND_SOC_NOPM, 0, 0,
			cml_to_lmixer_controls),
	SND_SOC_DAPM_MUX("IN2_R to Left Mixer Negative Resistor", SND_SOC_NOPM, 0, 0,
			in2r_to_lmixer_controls),
	SND_SOC_DAPM_MUX("IN3_R to Left Mixer Negative Resistor", SND_SOC_NOPM, 0, 0,
			in3r_to_lmixer_controls),

	SND_SOC_DAPM_SUPPLY("Mic Bias", AIC32X4_MICBIAS, 6, 0, mic_bias_event,
			SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_POST("ADC Reset", aic32x4_reset_adc),

	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("LOL"),
	SND_SOC_DAPM_OUTPUT("LOR"),
	SND_SOC_DAPM_INPUT("IN1_L"),
	SND_SOC_DAPM_INPUT("IN1_R"),
	SND_SOC_DAPM_INPUT("IN2_L"),
	SND_SOC_DAPM_INPUT("IN2_R"),
	SND_SOC_DAPM_INPUT("IN3_L"),
	SND_SOC_DAPM_INPUT("IN3_R"),
	SND_SOC_DAPM_INPUT("CM_L"),
	SND_SOC_DAPM_INPUT("CM_R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route aic32x4_dapm_routes[] = अणु
	/* Left Output */
	अणु"HPL Output Mixer", "L_DAC Switch", "Left DAC"पूर्ण,
	अणु"HPL Output Mixer", "IN1_L Switch", "IN1_L"पूर्ण,

	अणु"HPL Power", शून्य, "HPL Output Mixer"पूर्ण,
	अणु"HPL", शून्य, "HPL Power"पूर्ण,

	अणु"LOL Output Mixer", "L_DAC Switch", "Left DAC"पूर्ण,

	अणु"LOL Power", शून्य, "LOL Output Mixer"पूर्ण,
	अणु"LOL", शून्य, "LOL Power"पूर्ण,

	/* Right Output */
	अणु"HPR Output Mixer", "R_DAC Switch", "Right DAC"पूर्ण,
	अणु"HPR Output Mixer", "IN1_R Switch", "IN1_R"पूर्ण,

	अणु"HPR Power", शून्य, "HPR Output Mixer"पूर्ण,
	अणु"HPR", शून्य, "HPR Power"पूर्ण,

	अणु"LOR Output Mixer", "R_DAC Switch", "Right DAC"पूर्ण,

	अणु"LOR Power", शून्य, "LOR Output Mixer"पूर्ण,
	अणु"LOR", शून्य, "LOR Power"पूर्ण,

	/* Right Input */
	अणु"Right ADC", शून्य, "IN1_R to Right Mixer Positive Resistor"पूर्ण,
	अणु"IN1_R to Right Mixer Positive Resistor", "10 kOhm", "IN1_R"पूर्ण,
	अणु"IN1_R to Right Mixer Positive Resistor", "20 kOhm", "IN1_R"पूर्ण,
	अणु"IN1_R to Right Mixer Positive Resistor", "40 kOhm", "IN1_R"पूर्ण,

	अणु"Right ADC", शून्य, "IN2_R to Right Mixer Positive Resistor"पूर्ण,
	अणु"IN2_R to Right Mixer Positive Resistor", "10 kOhm", "IN2_R"पूर्ण,
	अणु"IN2_R to Right Mixer Positive Resistor", "20 kOhm", "IN2_R"पूर्ण,
	अणु"IN2_R to Right Mixer Positive Resistor", "40 kOhm", "IN2_R"पूर्ण,

	अणु"Right ADC", शून्य, "IN3_R to Right Mixer Positive Resistor"पूर्ण,
	अणु"IN3_R to Right Mixer Positive Resistor", "10 kOhm", "IN3_R"पूर्ण,
	अणु"IN3_R to Right Mixer Positive Resistor", "20 kOhm", "IN3_R"पूर्ण,
	अणु"IN3_R to Right Mixer Positive Resistor", "40 kOhm", "IN3_R"पूर्ण,

	अणु"Right ADC", शून्य, "IN2_L to Right Mixer Positive Resistor"पूर्ण,
	अणु"IN2_L to Right Mixer Positive Resistor", "10 kOhm", "IN2_L"पूर्ण,
	अणु"IN2_L to Right Mixer Positive Resistor", "20 kOhm", "IN2_L"पूर्ण,
	अणु"IN2_L to Right Mixer Positive Resistor", "40 kOhm", "IN2_L"पूर्ण,

	अणु"Right ADC", शून्य, "CM_R to Right Mixer Negative Resistor"पूर्ण,
	अणु"CM_R to Right Mixer Negative Resistor", "10 kOhm", "CM_R"पूर्ण,
	अणु"CM_R to Right Mixer Negative Resistor", "20 kOhm", "CM_R"पूर्ण,
	अणु"CM_R to Right Mixer Negative Resistor", "40 kOhm", "CM_R"पूर्ण,

	अणु"Right ADC", शून्य, "IN1_L to Right Mixer Negative Resistor"पूर्ण,
	अणु"IN1_L to Right Mixer Negative Resistor", "10 kOhm", "IN1_L"पूर्ण,
	अणु"IN1_L to Right Mixer Negative Resistor", "20 kOhm", "IN1_L"पूर्ण,
	अणु"IN1_L to Right Mixer Negative Resistor", "40 kOhm", "IN1_L"पूर्ण,

	अणु"Right ADC", शून्य, "IN3_L to Right Mixer Negative Resistor"पूर्ण,
	अणु"IN3_L to Right Mixer Negative Resistor", "10 kOhm", "IN3_L"पूर्ण,
	अणु"IN3_L to Right Mixer Negative Resistor", "20 kOhm", "IN3_L"पूर्ण,
	अणु"IN3_L to Right Mixer Negative Resistor", "40 kOhm", "IN3_L"पूर्ण,

	/* Left Input */
	अणु"Left ADC", शून्य, "IN1_L to Left Mixer Positive Resistor"पूर्ण,
	अणु"IN1_L to Left Mixer Positive Resistor", "10 kOhm", "IN1_L"पूर्ण,
	अणु"IN1_L to Left Mixer Positive Resistor", "20 kOhm", "IN1_L"पूर्ण,
	अणु"IN1_L to Left Mixer Positive Resistor", "40 kOhm", "IN1_L"पूर्ण,

	अणु"Left ADC", शून्य, "IN2_L to Left Mixer Positive Resistor"पूर्ण,
	अणु"IN2_L to Left Mixer Positive Resistor", "10 kOhm", "IN2_L"पूर्ण,
	अणु"IN2_L to Left Mixer Positive Resistor", "20 kOhm", "IN2_L"पूर्ण,
	अणु"IN2_L to Left Mixer Positive Resistor", "40 kOhm", "IN2_L"पूर्ण,

	अणु"Left ADC", शून्य, "IN3_L to Left Mixer Positive Resistor"पूर्ण,
	अणु"IN3_L to Left Mixer Positive Resistor", "10 kOhm", "IN3_L"पूर्ण,
	अणु"IN3_L to Left Mixer Positive Resistor", "20 kOhm", "IN3_L"पूर्ण,
	अणु"IN3_L to Left Mixer Positive Resistor", "40 kOhm", "IN3_L"पूर्ण,

	अणु"Left ADC", शून्य, "IN1_R to Left Mixer Positive Resistor"पूर्ण,
	अणु"IN1_R to Left Mixer Positive Resistor", "10 kOhm", "IN1_R"पूर्ण,
	अणु"IN1_R to Left Mixer Positive Resistor", "20 kOhm", "IN1_R"पूर्ण,
	अणु"IN1_R to Left Mixer Positive Resistor", "40 kOhm", "IN1_R"पूर्ण,

	अणु"Left ADC", शून्य, "CM_L to Left Mixer Negative Resistor"पूर्ण,
	अणु"CM_L to Left Mixer Negative Resistor", "10 kOhm", "CM_L"पूर्ण,
	अणु"CM_L to Left Mixer Negative Resistor", "20 kOhm", "CM_L"पूर्ण,
	अणु"CM_L to Left Mixer Negative Resistor", "40 kOhm", "CM_L"पूर्ण,

	अणु"Left ADC", शून्य, "IN2_R to Left Mixer Negative Resistor"पूर्ण,
	अणु"IN2_R to Left Mixer Negative Resistor", "10 kOhm", "IN2_R"पूर्ण,
	अणु"IN2_R to Left Mixer Negative Resistor", "20 kOhm", "IN2_R"पूर्ण,
	अणु"IN2_R to Left Mixer Negative Resistor", "40 kOhm", "IN2_R"पूर्ण,

	अणु"Left ADC", शून्य, "IN3_R to Left Mixer Negative Resistor"पूर्ण,
	अणु"IN3_R to Left Mixer Negative Resistor", "10 kOhm", "IN3_R"पूर्ण,
	अणु"IN3_R to Left Mixer Negative Resistor", "20 kOhm", "IN3_R"पूर्ण,
	अणु"IN3_R to Left Mixer Negative Resistor", "40 kOhm", "IN3_R"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg aic32x4_regmap_pages[] = अणु
	अणु
		.selector_reg = 0,
		.selector_mask	= 0xff,
		.winकरोw_start = 0,
		.winकरोw_len = 128,
		.range_min = 0,
		.range_max = AIC32X4_REFPOWERUP,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_config aic32x4_regmap_config = अणु
	.max_रेजिस्टर = AIC32X4_REFPOWERUP,
	.ranges = aic32x4_regmap_pages,
	.num_ranges = ARRAY_SIZE(aic32x4_regmap_pages),
पूर्ण;
EXPORT_SYMBOL(aic32x4_regmap_config);

अटल पूर्णांक aic32x4_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा clk *mclk;
	काष्ठा clk *pll;

	pll = devm_clk_get(component->dev, "pll");
	अगर (IS_ERR(pll))
		वापस PTR_ERR(pll);

	mclk = clk_get_parent(pll);

	वापस clk_set_rate(mclk, freq);
पूर्ण

अटल पूर्णांक aic32x4_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 अगरace_reg_1 = 0;
	u8 अगरace_reg_2 = 0;
	u8 अगरace_reg_3 = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace_reg_1 |= AIC32X4_BCLKMASTER | AIC32X4_WCLKMASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "aic32x4: invalid DAI master/slave interface\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace_reg_1 |= (AIC32X4_DSP_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		अगरace_reg_3 |= AIC32X4_BCLKINV_MASK; /* invert bit घड़ी */
		अगरace_reg_2 = 0x01; /* add offset 1 */
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace_reg_1 |= (AIC32X4_DSP_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		अगरace_reg_3 |= AIC32X4_BCLKINV_MASK; /* invert bit घड़ी */
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगरace_reg_1 |= (AIC32X4_RIGHT_JUSTIFIED_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace_reg_1 |= (AIC32X4_LEFT_JUSTIFIED_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "aic32x4: invalid DAI interface format\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIC32X4_IFACE1,
				AIC32X4_IFACE1_DATATYPE_MASK |
				AIC32X4_IFACE1_MASTER_MASK, अगरace_reg_1);
	snd_soc_component_update_bits(component, AIC32X4_IFACE2,
				AIC32X4_DATA_OFFSET_MASK, अगरace_reg_2);
	snd_soc_component_update_bits(component, AIC32X4_IFACE3,
				AIC32X4_BCLKINV_MASK, अगरace_reg_3);

	वापस 0;
पूर्ण

अटल पूर्णांक aic32x4_set_aosr(काष्ठा snd_soc_component *component, u8 aosr)
अणु
	वापस snd_soc_component_ग_लिखो(component, AIC32X4_AOSR, aosr);
पूर्ण

अटल पूर्णांक aic32x4_set_करोsr(काष्ठा snd_soc_component *component, u16 करोsr)
अणु
	snd_soc_component_ग_लिखो(component, AIC32X4_DOSRMSB, करोsr >> 8);
	snd_soc_component_ग_लिखो(component, AIC32X4_DOSRLSB,
		      (करोsr & 0xff));

	वापस 0;
पूर्ण

अटल पूर्णांक aic32x4_set_processing_blocks(काष्ठा snd_soc_component *component,
						u8 r_block, u8 p_block)
अणु
	अगर (r_block > 18 || p_block > 25)
		वापस -EINVAL;

	snd_soc_component_ग_लिखो(component, AIC32X4_ADCSPB, r_block);
	snd_soc_component_ग_लिखो(component, AIC32X4_DACSPB, p_block);

	वापस 0;
पूर्ण

अटल पूर्णांक aic32x4_setup_घड़ीs(काष्ठा snd_soc_component *component,
				अचिन्हित पूर्णांक sample_rate, अचिन्हित पूर्णांक channels,
				अचिन्हित पूर्णांक bit_depth)
अणु
	u8 aosr;
	u16 करोsr;
	u8 adc_resource_class, dac_resource_class;
	u8 madc, nadc, mdac, ndac, max_nadc, min_mdac, max_ndac;
	u8 करोsr_increment;
	u16 max_करोsr, min_करोsr;
	अचिन्हित दीर्घ adc_घड़ी_rate, dac_घड़ी_rate;
	पूर्णांक ret;

	काष्ठा clk_bulk_data घड़ीs[] = अणु
		अणु .id = "pll" पूर्ण,
		अणु .id = "nadc" पूर्ण,
		अणु .id = "madc" पूर्ण,
		अणु .id = "ndac" पूर्ण,
		अणु .id = "mdac" पूर्ण,
		अणु .id = "bdiv" पूर्ण,
	पूर्ण;
	ret = devm_clk_bulk_get(component->dev, ARRAY_SIZE(घड़ीs), घड़ीs);
	अगर (ret)
		वापस ret;

	अगर (sample_rate <= 48000) अणु
		aosr = 128;
		adc_resource_class = 6;
		dac_resource_class = 8;
		करोsr_increment = 8;
		aic32x4_set_processing_blocks(component, 1, 1);
	पूर्ण अन्यथा अगर (sample_rate <= 96000) अणु
		aosr = 64;
		adc_resource_class = 6;
		dac_resource_class = 8;
		करोsr_increment = 4;
		aic32x4_set_processing_blocks(component, 1, 9);
	पूर्ण अन्यथा अगर (sample_rate == 192000) अणु
		aosr = 32;
		adc_resource_class = 3;
		dac_resource_class = 4;
		करोsr_increment = 2;
		aic32x4_set_processing_blocks(component, 13, 19);
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Sampling rate not supported\n");
		वापस -EINVAL;
	पूर्ण

	madc = DIV_ROUND_UP((32 * adc_resource_class), aosr);
	max_करोsr = (AIC32X4_MAX_DOSR_FREQ / sample_rate / करोsr_increment) *
			करोsr_increment;
	min_करोsr = (AIC32X4_MIN_DOSR_FREQ / sample_rate / करोsr_increment) *
			करोsr_increment;
	max_nadc = AIC32X4_MAX_CODEC_CLKIN_FREQ / (madc * aosr * sample_rate);

	क्रम (nadc = max_nadc; nadc > 0; --nadc) अणु
		adc_घड़ी_rate = nadc * madc * aosr * sample_rate;
		क्रम (करोsr = max_करोsr; करोsr >= min_करोsr;
				करोsr -= करोsr_increment) अणु
			min_mdac = DIV_ROUND_UP((32 * dac_resource_class), करोsr);
			max_ndac = AIC32X4_MAX_CODEC_CLKIN_FREQ /
					(min_mdac * करोsr * sample_rate);
			क्रम (mdac = min_mdac; mdac <= 128; ++mdac) अणु
				क्रम (ndac = max_ndac; ndac > 0; --ndac) अणु
					dac_घड़ी_rate = ndac * mdac * करोsr *
							sample_rate;
					अगर (dac_घड़ी_rate == adc_घड़ी_rate) अणु
						अगर (clk_round_rate(घड़ीs[0].clk, dac_घड़ी_rate) == 0)
							जारी;

						clk_set_rate(घड़ीs[0].clk,
							dac_घड़ी_rate);

						clk_set_rate(घड़ीs[1].clk,
							sample_rate * aosr *
							madc);
						clk_set_rate(घड़ीs[2].clk,
							sample_rate * aosr);
						aic32x4_set_aosr(component,
							aosr);

						clk_set_rate(घड़ीs[3].clk,
							sample_rate * करोsr *
							mdac);
						clk_set_rate(घड़ीs[4].clk,
							sample_rate * करोsr);
						aic32x4_set_करोsr(component,
							करोsr);

						clk_set_rate(घड़ीs[5].clk,
							sample_rate * channels *
							bit_depth);

						वापस 0;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	dev_err(component->dev,
		"Could not set clocks to support sample rate.\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aic32x4_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aic32x4_priv *aic32x4 = snd_soc_component_get_drvdata(component);
	u8 अगरace1_reg = 0;
	u8 dacsetup_reg = 0;

	aic32x4_setup_घड़ीs(component, params_rate(params),
			     params_channels(params),
			     params_physical_width(params));

	चयन (params_physical_width(params)) अणु
	हाल 16:
		अगरace1_reg |= (AIC32X4_WORD_LEN_16BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		अवरोध;
	हाल 20:
		अगरace1_reg |= (AIC32X4_WORD_LEN_20BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		अवरोध;
	हाल 24:
		अगरace1_reg |= (AIC32X4_WORD_LEN_24BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		अवरोध;
	हाल 32:
		अगरace1_reg |= (AIC32X4_WORD_LEN_32BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		अवरोध;
	पूर्ण
	snd_soc_component_update_bits(component, AIC32X4_IFACE1,
				AIC32X4_IFACE1_DATALEN_MASK, अगरace1_reg);

	अगर (params_channels(params) == 1) अणु
		dacsetup_reg = AIC32X4_RDAC2LCHN | AIC32X4_LDAC2LCHN;
	पूर्ण अन्यथा अणु
		अगर (aic32x4->swapdacs)
			dacsetup_reg = AIC32X4_RDAC2LCHN | AIC32X4_LDAC2RCHN;
		अन्यथा
			dacsetup_reg = AIC32X4_LDAC2LCHN | AIC32X4_RDAC2RCHN;
	पूर्ण
	snd_soc_component_update_bits(component, AIC32X4_DACSETUP,
				AIC32X4_DAC_CHAN_MASK, dacsetup_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक aic32x4_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	snd_soc_component_update_bits(component, AIC32X4_DACMUTE,
				AIC32X4_MUTEON, mute ? AIC32X4_MUTEON : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक aic32x4_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret;

	काष्ठा clk_bulk_data घड़ीs[] = अणु
		अणु .id = "madc" पूर्ण,
		अणु .id = "mdac" पूर्ण,
		अणु .id = "bdiv" पूर्ण,
	पूर्ण;

	ret = devm_clk_bulk_get(component->dev, ARRAY_SIZE(घड़ीs), घड़ीs);
	अगर (ret)
		वापस ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		ret = clk_bulk_prepare_enable(ARRAY_SIZE(घड़ीs), घड़ीs);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to enable clocks\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* Initial cold start */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			अवरोध;

		clk_bulk_disable_unprepare(ARRAY_SIZE(घड़ीs), घड़ीs);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AIC32X4_RATES	SNDRV_PCM_RATE_8000_192000
#घोषणा AIC32X4_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE \
			 | SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_3LE \
			 | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops aic32x4_ops = अणु
	.hw_params = aic32x4_hw_params,
	.mute_stream = aic32x4_mute,
	.set_fmt = aic32x4_set_dai_fmt,
	.set_sysclk = aic32x4_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aic32x4_dai = अणु
	.name = "tlv320aic32x4-hifi",
	.playback = अणु
			 .stream_name = "Playback",
			 .channels_min = 1,
			 .channels_max = 2,
			 .rates = AIC32X4_RATES,
			 .क्रमmats = AIC32X4_FORMATS,पूर्ण,
	.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = AIC32X4_RATES,
			.क्रमmats = AIC32X4_FORMATS,पूर्ण,
	.ops = &aic32x4_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल व्योम aic32x4_setup_gpios(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic32x4_priv *aic32x4 = snd_soc_component_get_drvdata(component);

	/* setup GPIO functions */
	/* MFP1 */
	अगर (aic32x4->setup->gpio_func[0] != AIC32X4_MFPX_DEFAULT_VALUE) अणु
		snd_soc_component_ग_लिखो(component, AIC32X4_DINCTL,
			  aic32x4->setup->gpio_func[0]);
		snd_soc_add_component_controls(component, aic32x4_mfp1,
			ARRAY_SIZE(aic32x4_mfp1));
	पूर्ण

	/* MFP2 */
	अगर (aic32x4->setup->gpio_func[1] != AIC32X4_MFPX_DEFAULT_VALUE) अणु
		snd_soc_component_ग_लिखो(component, AIC32X4_DOUTCTL,
			  aic32x4->setup->gpio_func[1]);
		snd_soc_add_component_controls(component, aic32x4_mfp2,
			ARRAY_SIZE(aic32x4_mfp2));
	पूर्ण

	/* MFP3 */
	अगर (aic32x4->setup->gpio_func[2] != AIC32X4_MFPX_DEFAULT_VALUE) अणु
		snd_soc_component_ग_लिखो(component, AIC32X4_SCLKCTL,
			  aic32x4->setup->gpio_func[2]);
		snd_soc_add_component_controls(component, aic32x4_mfp3,
			ARRAY_SIZE(aic32x4_mfp3));
	पूर्ण

	/* MFP4 */
	अगर (aic32x4->setup->gpio_func[3] != AIC32X4_MFPX_DEFAULT_VALUE) अणु
		snd_soc_component_ग_लिखो(component, AIC32X4_MISOCTL,
			  aic32x4->setup->gpio_func[3]);
		snd_soc_add_component_controls(component, aic32x4_mfp4,
			ARRAY_SIZE(aic32x4_mfp4));
	पूर्ण

	/* MFP5 */
	अगर (aic32x4->setup->gpio_func[4] != AIC32X4_MFPX_DEFAULT_VALUE) अणु
		snd_soc_component_ग_लिखो(component, AIC32X4_GPIOCTL,
			  aic32x4->setup->gpio_func[4]);
		snd_soc_add_component_controls(component, aic32x4_mfp5,
			ARRAY_SIZE(aic32x4_mfp5));
	पूर्ण
पूर्ण

अटल पूर्णांक aic32x4_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic32x4_priv *aic32x4 = snd_soc_component_get_drvdata(component);
	u32 पंचांगp_reg;
	पूर्णांक ret;

	काष्ठा clk_bulk_data घड़ीs[] = अणु
		अणु .id = "codec_clkin" पूर्ण,
		अणु .id = "pll" पूर्ण,
		अणु .id = "bdiv" पूर्ण,
		अणु .id = "mdac" पूर्ण,
	पूर्ण;

	ret = devm_clk_bulk_get(component->dev, ARRAY_SIZE(घड़ीs), घड़ीs);
	अगर (ret)
		वापस ret;

	अगर (aic32x4->setup)
		aic32x4_setup_gpios(component);

	clk_set_parent(घड़ीs[0].clk, घड़ीs[1].clk);
	clk_set_parent(घड़ीs[2].clk, घड़ीs[3].clk);

	/* Power platक्रमm configuration */
	अगर (aic32x4->घातer_cfg & AIC32X4_PWR_MICBIAS_2075_LDOIN) अणु
		snd_soc_component_ग_लिखो(component, AIC32X4_MICBIAS,
				AIC32X4_MICBIAS_LDOIN | AIC32X4_MICBIAS_2075V);
	पूर्ण
	अगर (aic32x4->घातer_cfg & AIC32X4_PWR_AVDD_DVDD_WEAK_DISABLE)
		snd_soc_component_ग_लिखो(component, AIC32X4_PWRCFG, AIC32X4_AVDDWEAKDISABLE);

	पंचांगp_reg = (aic32x4->घातer_cfg & AIC32X4_PWR_AIC32X4_LDO_ENABLE) ?
			AIC32X4_LDOCTLEN : 0;
	snd_soc_component_ग_लिखो(component, AIC32X4_LDOCTL, पंचांगp_reg);

	पंचांगp_reg = snd_soc_component_पढ़ो(component, AIC32X4_CMMODE);
	अगर (aic32x4->घातer_cfg & AIC32X4_PWR_CMMODE_LDOIN_RANGE_18_36)
		पंचांगp_reg |= AIC32X4_LDOIN_18_36;
	अगर (aic32x4->घातer_cfg & AIC32X4_PWR_CMMODE_HP_LDOIN_POWERED)
		पंचांगp_reg |= AIC32X4_LDOIN2HP;
	snd_soc_component_ग_लिखो(component, AIC32X4_CMMODE, पंचांगp_reg);

	/* Mic PGA routing */
	अगर (aic32x4->micpga_routing & AIC32X4_MICPGA_ROUTE_LMIC_IN2R_10K)
		snd_soc_component_ग_लिखो(component, AIC32X4_LMICPGANIN,
				AIC32X4_LMICPGANIN_IN2R_10K);
	अन्यथा
		snd_soc_component_ग_लिखो(component, AIC32X4_LMICPGANIN,
				AIC32X4_LMICPGANIN_CM1L_10K);
	अगर (aic32x4->micpga_routing & AIC32X4_MICPGA_ROUTE_RMIC_IN1L_10K)
		snd_soc_component_ग_लिखो(component, AIC32X4_RMICPGANIN,
				AIC32X4_RMICPGANIN_IN1L_10K);
	अन्यथा
		snd_soc_component_ग_लिखो(component, AIC32X4_RMICPGANIN,
				AIC32X4_RMICPGANIN_CM1R_10K);

	/*
	 * Workaround: क्रम an unknown reason, the ADC needs to be घातered up
	 * and करोwn क्रम the first capture to work properly. It seems related to
	 * a HW BUG or some kind of behavior not करोcumented in the datasheet.
	 */
	पंचांगp_reg = snd_soc_component_पढ़ो(component, AIC32X4_ADCSETUP);
	snd_soc_component_ग_लिखो(component, AIC32X4_ADCSETUP, पंचांगp_reg |
				AIC32X4_LADC_EN | AIC32X4_RADC_EN);
	snd_soc_component_ग_लिखो(component, AIC32X4_ADCSETUP, पंचांगp_reg);

	/*
	 * Enable the fast अक्षरging feature and ensure the needed 40ms ellapsed
	 * beक्रमe using the analog circuits.
	 */
	snd_soc_component_ग_लिखो(component, AIC32X4_REFPOWERUP,
				AIC32X4_REFPOWERUP_40MS);
	msleep(40);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_aic32x4 = अणु
	.probe			= aic32x4_component_probe,
	.set_bias_level		= aic32x4_set_bias_level,
	.controls		= aic32x4_snd_controls,
	.num_controls		= ARRAY_SIZE(aic32x4_snd_controls),
	.dapm_widमाला_लो		= aic32x4_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(aic32x4_dapm_widमाला_लो),
	.dapm_routes		= aic32x4_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(aic32x4_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक aic32x4_parse_dt(काष्ठा aic32x4_priv *aic32x4,
		काष्ठा device_node *np)
अणु
	काष्ठा aic32x4_setup_data *aic32x4_setup;
	पूर्णांक ret;

	aic32x4_setup = devm_kzalloc(aic32x4->dev, माप(*aic32x4_setup),
							GFP_KERNEL);
	अगर (!aic32x4_setup)
		वापस -ENOMEM;

	ret = of_property_match_string(np, "clock-names", "mclk");
	अगर (ret < 0)
		वापस -EINVAL;
	aic32x4->mclk_name = of_clk_get_parent_name(np, ret);

	aic32x4->swapdacs = false;
	aic32x4->micpga_routing = 0;
	aic32x4->rstn_gpio = of_get_named_gpio(np, "reset-gpios", 0);

	अगर (of_property_पढ़ो_u32_array(np, "aic32x4-gpio-func",
				aic32x4_setup->gpio_func, 5) >= 0)
		aic32x4->setup = aic32x4_setup;
	वापस 0;
पूर्ण

अटल व्योम aic32x4_disable_regulators(काष्ठा aic32x4_priv *aic32x4)
अणु
	regulator_disable(aic32x4->supply_iov);

	अगर (!IS_ERR(aic32x4->supply_lकरो))
		regulator_disable(aic32x4->supply_lकरो);

	अगर (!IS_ERR(aic32x4->supply_dv))
		regulator_disable(aic32x4->supply_dv);

	अगर (!IS_ERR(aic32x4->supply_av))
		regulator_disable(aic32x4->supply_av);
पूर्ण

अटल पूर्णांक aic32x4_setup_regulators(काष्ठा device *dev,
		काष्ठा aic32x4_priv *aic32x4)
अणु
	पूर्णांक ret = 0;

	aic32x4->supply_lकरो = devm_regulator_get_optional(dev, "ldoin");
	aic32x4->supply_iov = devm_regulator_get(dev, "iov");
	aic32x4->supply_dv = devm_regulator_get_optional(dev, "dv");
	aic32x4->supply_av = devm_regulator_get_optional(dev, "av");

	/* Check अगर the regulator requirements are fulfilled */

	अगर (IS_ERR(aic32x4->supply_iov)) अणु
		dev_err(dev, "Missing supply 'iov'\n");
		वापस PTR_ERR(aic32x4->supply_iov);
	पूर्ण

	अगर (IS_ERR(aic32x4->supply_lकरो)) अणु
		अगर (PTR_ERR(aic32x4->supply_lकरो) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		अगर (IS_ERR(aic32x4->supply_dv)) अणु
			dev_err(dev, "Missing supply 'dv' or 'ldoin'\n");
			वापस PTR_ERR(aic32x4->supply_dv);
		पूर्ण
		अगर (IS_ERR(aic32x4->supply_av)) अणु
			dev_err(dev, "Missing supply 'av' or 'ldoin'\n");
			वापस PTR_ERR(aic32x4->supply_av);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (PTR_ERR(aic32x4->supply_dv) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		अगर (PTR_ERR(aic32x4->supply_av) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
	पूर्ण

	ret = regulator_enable(aic32x4->supply_iov);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable regulator iov\n");
		वापस ret;
	पूर्ण

	अगर (!IS_ERR(aic32x4->supply_lकरो)) अणु
		ret = regulator_enable(aic32x4->supply_lकरो);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator ldo\n");
			जाओ error_lकरो;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(aic32x4->supply_dv)) अणु
		ret = regulator_enable(aic32x4->supply_dv);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator dv\n");
			जाओ error_dv;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(aic32x4->supply_av)) अणु
		ret = regulator_enable(aic32x4->supply_av);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator av\n");
			जाओ error_av;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(aic32x4->supply_lकरो) && IS_ERR(aic32x4->supply_av))
		aic32x4->घातer_cfg |= AIC32X4_PWR_AIC32X4_LDO_ENABLE;

	वापस 0;

error_av:
	अगर (!IS_ERR(aic32x4->supply_dv))
		regulator_disable(aic32x4->supply_dv);

error_dv:
	अगर (!IS_ERR(aic32x4->supply_lकरो))
		regulator_disable(aic32x4->supply_lकरो);

error_lकरो:
	regulator_disable(aic32x4->supply_iov);
	वापस ret;
पूर्ण

पूर्णांक aic32x4_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा aic32x4_priv *aic32x4;
	काष्ठा aic32x4_pdata *pdata = dev->platक्रमm_data;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	aic32x4 = devm_kzalloc(dev, माप(काष्ठा aic32x4_priv),
				   GFP_KERNEL);
	अगर (aic32x4 == शून्य)
		वापस -ENOMEM;

	aic32x4->dev = dev;
	dev_set_drvdata(dev, aic32x4);

	अगर (pdata) अणु
		aic32x4->घातer_cfg = pdata->घातer_cfg;
		aic32x4->swapdacs = pdata->swapdacs;
		aic32x4->micpga_routing = pdata->micpga_routing;
		aic32x4->rstn_gpio = pdata->rstn_gpio;
		aic32x4->mclk_name = "mclk";
	पूर्ण अन्यथा अगर (np) अणु
		ret = aic32x4_parse_dt(aic32x4, np);
		अगर (ret) अणु
			dev_err(dev, "Failed to parse DT node\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		aic32x4->घातer_cfg = 0;
		aic32x4->swapdacs = false;
		aic32x4->micpga_routing = 0;
		aic32x4->rstn_gpio = -1;
		aic32x4->mclk_name = "mclk";
	पूर्ण

	अगर (gpio_is_valid(aic32x4->rstn_gpio)) अणु
		ret = devm_gpio_request_one(dev, aic32x4->rstn_gpio,
				GPIOF_OUT_INIT_LOW, "tlv320aic32x4 rstn");
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	ret = aic32x4_setup_regulators(dev, aic32x4);
	अगर (ret) अणु
		dev_err(dev, "Failed to setup regulators\n");
		वापस ret;
	पूर्ण

	अगर (gpio_is_valid(aic32x4->rstn_gpio)) अणु
		ndelay(10);
		gpio_set_value_cansleep(aic32x4->rstn_gpio, 1);
		mdelay(1);
	पूर्ण

	ret = regmap_ग_लिखो(regmap, AIC32X4_RESET, 0x01);
	अगर (ret)
		जाओ err_disable_regulators;

	ret = aic32x4_रेजिस्टर_घड़ीs(dev, aic32x4->mclk_name);
	अगर (ret)
		जाओ err_disable_regulators;

	ret = devm_snd_soc_रेजिस्टर_component(dev,
			&soc_component_dev_aic32x4, &aic32x4_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to register component\n");
		जाओ err_disable_regulators;
	पूर्ण

	वापस 0;

err_disable_regulators:
	aic32x4_disable_regulators(aic32x4);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(aic32x4_probe);

पूर्णांक aic32x4_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा aic32x4_priv *aic32x4 = dev_get_drvdata(dev);

	aic32x4_disable_regulators(aic32x4);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(aic32x4_हटाओ);

MODULE_DESCRIPTION("ASoC tlv320aic32x4 codec driver");
MODULE_AUTHOR("Javier Martin <javier.martin@vista-silicon.com>");
MODULE_LICENSE("GPL");
