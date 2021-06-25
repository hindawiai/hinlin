<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * da7219.c - DA7219 ALSA SoC Codec Driver
 *
 * Copyright (c) 2015 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <sound/da7219.h>
#समावेश "da7219.h"
#समावेश "da7219-aad.h"


/*
 * TLVs and Enums
 */

/* Input TLVs */
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_mic_gain_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_mixin_gain_tlv, -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_adc_dig_gain_tlv, -8325, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_alc_threshold_tlv, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_alc_gain_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_alc_ana_gain_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_sidetone_gain_tlv, -4200, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_tonegen_gain_tlv, -4500, 300, 0);

/* Output TLVs */
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_dac_eq_band_tlv, -1050, 150, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(da7219_dac_dig_gain_tlv,
	0x0, 0x07, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* -77.25dB to 12dB */
	0x08, 0x7f, TLV_DB_SCALE_ITEM(-7725, 75, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_dac_ng_threshold_tlv, -10200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7219_hp_gain_tlv, -5700, 100, 0);

/* Input Enums */
अटल स्थिर अक्षर * स्थिर da7219_alc_attack_rate_txt[] = अणु
	"7.33/fs", "14.66/fs", "29.32/fs", "58.64/fs", "117.3/fs", "234.6/fs",
	"469.1/fs", "938.2/fs", "1876/fs", "3753/fs", "7506/fs", "15012/fs",
	"30024/fs"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_alc_attack_rate =
	SOC_ENUM_SINGLE(DA7219_ALC_CTRL2, DA7219_ALC_ATTACK_SHIFT,
			DA7219_ALC_ATTACK_MAX, da7219_alc_attack_rate_txt);

अटल स्थिर अक्षर * स्थिर da7219_alc_release_rate_txt[] = अणु
	"28.66/fs", "57.33/fs", "114.6/fs", "229.3/fs", "458.6/fs", "917.1/fs",
	"1834/fs", "3668/fs", "7337/fs", "14674/fs", "29348/fs"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_alc_release_rate =
	SOC_ENUM_SINGLE(DA7219_ALC_CTRL2, DA7219_ALC_RELEASE_SHIFT,
			DA7219_ALC_RELEASE_MAX, da7219_alc_release_rate_txt);

अटल स्थिर अक्षर * स्थिर da7219_alc_hold_समय_प्रकारxt[] = अणु
	"62/fs", "124/fs", "248/fs", "496/fs", "992/fs", "1984/fs", "3968/fs",
	"7936/fs", "15872/fs", "31744/fs", "63488/fs", "126976/fs",
	"253952/fs", "507904/fs", "1015808/fs", "2031616/fs"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_alc_hold_समय =
	SOC_ENUM_SINGLE(DA7219_ALC_CTRL3, DA7219_ALC_HOLD_SHIFT,
			DA7219_ALC_HOLD_MAX, da7219_alc_hold_समय_प्रकारxt);

अटल स्थिर अक्षर * स्थिर da7219_alc_env_rate_txt[] = अणु
	"1/4", "1/16", "1/256", "1/65536"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_alc_env_attack_rate =
	SOC_ENUM_SINGLE(DA7219_ALC_CTRL3, DA7219_ALC_INTEG_ATTACK_SHIFT,
			DA7219_ALC_INTEG_MAX, da7219_alc_env_rate_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7219_alc_env_release_rate =
	SOC_ENUM_SINGLE(DA7219_ALC_CTRL3, DA7219_ALC_INTEG_RELEASE_SHIFT,
			DA7219_ALC_INTEG_MAX, da7219_alc_env_rate_txt);

अटल स्थिर अक्षर * स्थिर da7219_alc_anticlip_step_txt[] = अणु
	"0.034dB/fs", "0.068dB/fs", "0.136dB/fs", "0.272dB/fs"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_alc_anticlip_step =
	SOC_ENUM_SINGLE(DA7219_ALC_ANTICLIP_CTRL,
			DA7219_ALC_ANTICLIP_STEP_SHIFT,
			DA7219_ALC_ANTICLIP_STEP_MAX,
			da7219_alc_anticlip_step_txt);

/* Input/Output Enums */
अटल स्थिर अक्षर * स्थिर da7219_gain_ramp_rate_txt[] = अणु
	"Nominal Rate * 8", "Nominal Rate", "Nominal Rate / 8",
	"Nominal Rate / 16"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_gain_ramp_rate =
	SOC_ENUM_SINGLE(DA7219_GAIN_RAMP_CTRL, DA7219_GAIN_RAMP_RATE_SHIFT,
			DA7219_GAIN_RAMP_RATE_MAX, da7219_gain_ramp_rate_txt);

अटल स्थिर अक्षर * स्थिर da7219_hpf_mode_txt[] = अणु
	"Disabled", "Audio", "Voice"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक da7219_hpf_mode_val[] = अणु
	DA7219_HPF_DISABLED, DA7219_HPF_AUDIO_EN, DA7219_HPF_VOICE_EN,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_adc_hpf_mode =
	SOC_VALUE_ENUM_SINGLE(DA7219_ADC_FILTERS1, DA7219_HPF_MODE_SHIFT,
			      DA7219_HPF_MODE_MASK, DA7219_HPF_MODE_MAX,
			      da7219_hpf_mode_txt, da7219_hpf_mode_val);

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_hpf_mode =
	SOC_VALUE_ENUM_SINGLE(DA7219_DAC_FILTERS1, DA7219_HPF_MODE_SHIFT,
			      DA7219_HPF_MODE_MASK, DA7219_HPF_MODE_MAX,
			      da7219_hpf_mode_txt, da7219_hpf_mode_val);

अटल स्थिर अक्षर * स्थिर da7219_audio_hpf_corner_txt[] = अणु
	"2Hz", "4Hz", "8Hz", "16Hz"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_adc_audio_hpf_corner =
	SOC_ENUM_SINGLE(DA7219_ADC_FILTERS1,
			DA7219_ADC_AUDIO_HPF_CORNER_SHIFT,
			DA7219_AUDIO_HPF_CORNER_MAX,
			da7219_audio_hpf_corner_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_audio_hpf_corner =
	SOC_ENUM_SINGLE(DA7219_DAC_FILTERS1,
			DA7219_DAC_AUDIO_HPF_CORNER_SHIFT,
			DA7219_AUDIO_HPF_CORNER_MAX,
			da7219_audio_hpf_corner_txt);

अटल स्थिर अक्षर * स्थिर da7219_voice_hpf_corner_txt[] = अणु
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_adc_voice_hpf_corner =
	SOC_ENUM_SINGLE(DA7219_ADC_FILTERS1,
			DA7219_ADC_VOICE_HPF_CORNER_SHIFT,
			DA7219_VOICE_HPF_CORNER_MAX,
			da7219_voice_hpf_corner_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_voice_hpf_corner =
	SOC_ENUM_SINGLE(DA7219_DAC_FILTERS1,
			DA7219_DAC_VOICE_HPF_CORNER_SHIFT,
			DA7219_VOICE_HPF_CORNER_MAX,
			da7219_voice_hpf_corner_txt);

अटल स्थिर अक्षर * स्थिर da7219_tonegen_dपंचांगf_key_txt[] = अणु
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D",
	"*", "#"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_tonegen_dपंचांगf_key =
	SOC_ENUM_SINGLE(DA7219_TONE_GEN_CFG1, DA7219_DTMF_REG_SHIFT,
			DA7219_DTMF_REG_MAX, da7219_tonegen_dपंचांगf_key_txt);

अटल स्थिर अक्षर * स्थिर da7219_tonegen_swg_sel_txt[] = अणु
	"Sum", "SWG1", "SWG2", "SWG1_1-Cos"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_tonegen_swg_sel =
	SOC_ENUM_SINGLE(DA7219_TONE_GEN_CFG2, DA7219_SWG_SEL_SHIFT,
			DA7219_SWG_SEL_MAX, da7219_tonegen_swg_sel_txt);

/* Output Enums */
अटल स्थिर अक्षर * स्थिर da7219_dac_sofपंचांगute_rate_txt[] = अणु
	"1 Sample", "2 Samples", "4 Samples", "8 Samples", "16 Samples",
	"32 Samples", "64 Samples"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_sofपंचांगute_rate =
	SOC_ENUM_SINGLE(DA7219_DAC_FILTERS5, DA7219_DAC_SOFTMUTE_RATE_SHIFT,
			DA7219_DAC_SOFTMUTE_RATE_MAX,
			da7219_dac_sofपंचांगute_rate_txt);

अटल स्थिर अक्षर * स्थिर da7219_dac_ng_setup_समय_प्रकारxt[] = अणु
	"256 Samples", "512 Samples", "1024 Samples", "2048 Samples"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_ng_setup_समय =
	SOC_ENUM_SINGLE(DA7219_DAC_NG_SETUP_TIME,
			DA7219_DAC_NG_SETUP_TIME_SHIFT,
			DA7219_DAC_NG_SETUP_TIME_MAX,
			da7219_dac_ng_setup_समय_प्रकारxt);

अटल स्थिर अक्षर * स्थिर da7219_dac_ng_rampup_txt[] = अणु
	"0.22ms/dB", "0.0138ms/dB"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_ng_rampup_rate =
	SOC_ENUM_SINGLE(DA7219_DAC_NG_SETUP_TIME,
			DA7219_DAC_NG_RAMPUP_RATE_SHIFT,
			DA7219_DAC_NG_RAMP_RATE_MAX,
			da7219_dac_ng_rampup_txt);

अटल स्थिर अक्षर * स्थिर da7219_dac_ng_rampकरोwn_txt[] = अणु
	"0.88ms/dB", "14.08ms/dB"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_dac_ng_rampकरोwn_rate =
	SOC_ENUM_SINGLE(DA7219_DAC_NG_SETUP_TIME,
			DA7219_DAC_NG_RAMPDN_RATE_SHIFT,
			DA7219_DAC_NG_RAMP_RATE_MAX,
			da7219_dac_ng_rampकरोwn_txt);


अटल स्थिर अक्षर * स्थिर da7219_cp_track_mode_txt[] = अणु
	"Largest Volume", "DAC Volume", "Signal Magnitude"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक da7219_cp_track_mode_val[] = अणु
	DA7219_CP_MCHANGE_LARGEST_VOL, DA7219_CP_MCHANGE_DAC_VOL,
	DA7219_CP_MCHANGE_SIG_MAG
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_cp_track_mode =
	SOC_VALUE_ENUM_SINGLE(DA7219_CP_CTRL, DA7219_CP_MCHANGE_SHIFT,
			      DA7219_CP_MCHANGE_REL_MASK, DA7219_CP_MCHANGE_MAX,
			      da7219_cp_track_mode_txt,
			      da7219_cp_track_mode_val);


/*
 * Control Functions
 */

/* Locked Kcontrol calls */
अटल पूर्णांक da7219_volsw_locked_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&da7219->ctrl_lock);
	ret = snd_soc_get_volsw(kcontrol, ucontrol);
	mutex_unlock(&da7219->ctrl_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक da7219_volsw_locked_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&da7219->ctrl_lock);
	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	mutex_unlock(&da7219->ctrl_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक da7219_क्रमागत_locked_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&da7219->ctrl_lock);
	ret = snd_soc_get_क्रमागत_द्विगुन(kcontrol, ucontrol);
	mutex_unlock(&da7219->ctrl_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक da7219_क्रमागत_locked_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&da7219->ctrl_lock);
	ret = snd_soc_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
	mutex_unlock(&da7219->ctrl_lock);

	वापस ret;
पूर्ण

/* ALC */
अटल व्योम da7219_alc_calib(काष्ठा snd_soc_component *component)
अणु
	u8 mic_ctrl, mixin_ctrl, adc_ctrl, calib_ctrl;

	/* Save current state of mic control रेजिस्टर */
	mic_ctrl = snd_soc_component_पढ़ो(component, DA7219_MIC_1_CTRL);

	/* Save current state of input mixer control रेजिस्टर */
	mixin_ctrl = snd_soc_component_पढ़ो(component, DA7219_MIXIN_L_CTRL);

	/* Save current state of input ADC control रेजिस्टर */
	adc_ctrl = snd_soc_component_पढ़ो(component, DA7219_ADC_L_CTRL);

	/* Enable then Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7219_MIC_1_CTRL, DA7219_MIC_1_AMP_EN_MASK,
			    DA7219_MIC_1_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_MIC_1_CTRL,
			    DA7219_MIC_1_AMP_MUTE_EN_MASK,
			    DA7219_MIC_1_AMP_MUTE_EN_MASK);

	/* Enable input mixers unmuted */
	snd_soc_component_update_bits(component, DA7219_MIXIN_L_CTRL,
			    DA7219_MIXIN_L_AMP_EN_MASK |
			    DA7219_MIXIN_L_AMP_MUTE_EN_MASK,
			    DA7219_MIXIN_L_AMP_EN_MASK);

	/* Enable input filters unmuted */
	snd_soc_component_update_bits(component, DA7219_ADC_L_CTRL,
			    DA7219_ADC_L_MUTE_EN_MASK | DA7219_ADC_L_EN_MASK,
			    DA7219_ADC_L_EN_MASK);

	/* Perक्रमm स्वतः calibration */
	snd_soc_component_update_bits(component, DA7219_ALC_CTRL1,
			    DA7219_ALC_AUTO_CALIB_EN_MASK,
			    DA7219_ALC_AUTO_CALIB_EN_MASK);
	करो अणु
		calib_ctrl = snd_soc_component_पढ़ो(component, DA7219_ALC_CTRL1);
	पूर्ण जबतक (calib_ctrl & DA7219_ALC_AUTO_CALIB_EN_MASK);

	/* If स्वतः calibration fails, disable DC offset, hybrid ALC */
	अगर (calib_ctrl & DA7219_ALC_CALIB_OVERFLOW_MASK) अणु
		dev_warn(component->dev,
			 "ALC auto calibration failed with overflow\n");
		snd_soc_component_update_bits(component, DA7219_ALC_CTRL1,
				    DA7219_ALC_OFFSET_EN_MASK |
				    DA7219_ALC_SYNC_MODE_MASK, 0);
	पूर्ण अन्यथा अणु
		/* Enable DC offset cancellation, hybrid mode */
		snd_soc_component_update_bits(component, DA7219_ALC_CTRL1,
				    DA7219_ALC_OFFSET_EN_MASK |
				    DA7219_ALC_SYNC_MODE_MASK,
				    DA7219_ALC_OFFSET_EN_MASK |
				    DA7219_ALC_SYNC_MODE_MASK);
	पूर्ण

	/* Restore input filter control रेजिस्टर to original state */
	snd_soc_component_ग_लिखो(component, DA7219_ADC_L_CTRL, adc_ctrl);

	/* Restore input mixer control रेजिस्टरs to original state */
	snd_soc_component_ग_लिखो(component, DA7219_MIXIN_L_CTRL, mixin_ctrl);

	/* Restore MIC control रेजिस्टरs to original states */
	snd_soc_component_ग_लिखो(component, DA7219_MIC_1_CTRL, mic_ctrl);
पूर्ण

अटल पूर्णांक da7219_mixin_gain_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);

	/*
	 * If ALC in operation and value of control has been updated,
	 * make sure calibrated offsets are updated.
	 */
	अगर ((ret == 1) && (da7219->alc_en))
		da7219_alc_calib(component);

	वापस ret;
पूर्ण

अटल पूर्णांक da7219_alc_sw_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);


	/* Force ALC offset calibration अगर enabling ALC */
	अगर ((ucontrol->value.पूर्णांकeger.value[0]) && (!da7219->alc_en)) अणु
		da7219_alc_calib(component);
		da7219->alc_en = true;
	पूर्ण अन्यथा अणु
		da7219->alc_en = false;
	पूर्ण

	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण

/* ToneGen */
अटल पूर्णांक da7219_tonegen_freq_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mixer_ctrl =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mixer_ctrl->reg;
	__le16 val;
	पूर्णांक ret;

	mutex_lock(&da7219->ctrl_lock);
	ret = regmap_raw_पढ़ो(da7219->regmap, reg, &val, माप(val));
	mutex_unlock(&da7219->ctrl_lock);

	अगर (ret)
		वापस ret;

	/*
	 * Frequency value spans two 8-bit रेजिस्टरs, lower then upper byte.
	 * Thereक्रमe we need to convert to host endianness here.
	 */
	ucontrol->value.पूर्णांकeger.value[0] = le16_to_cpu(val);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_tonegen_freq_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mixer_ctrl =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mixer_ctrl->reg;
	__le16 val;
	पूर्णांक ret;

	/*
	 * Frequency value spans two 8-bit रेजिस्टरs, lower then upper byte.
	 * Thereक्रमe we need to convert to little endian here to align with
	 * HW रेजिस्टरs.
	 */
	val = cpu_to_le16(ucontrol->value.पूर्णांकeger.value[0]);

	mutex_lock(&da7219->ctrl_lock);
	ret = regmap_raw_ग_लिखो(da7219->regmap, reg, &val, माप(val));
	mutex_unlock(&da7219->ctrl_lock);

	वापस ret;
पूर्ण


/*
 * KControls
 */

अटल स्थिर काष्ठा snd_kcontrol_new da7219_snd_controls[] = अणु
	/* Mics */
	SOC_SINGLE_TLV("Mic Volume", DA7219_MIC_1_GAIN,
		       DA7219_MIC_1_AMP_GAIN_SHIFT, DA7219_MIC_1_AMP_GAIN_MAX,
		       DA7219_NO_INVERT, da7219_mic_gain_tlv),
	SOC_SINGLE("Mic Switch", DA7219_MIC_1_CTRL,
		   DA7219_MIC_1_AMP_MUTE_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_INVERT),

	/* Mixer Input */
	SOC_SINGLE_EXT_TLV("Mixin Volume", DA7219_MIXIN_L_GAIN,
			   DA7219_MIXIN_L_AMP_GAIN_SHIFT,
			   DA7219_MIXIN_L_AMP_GAIN_MAX, DA7219_NO_INVERT,
			   snd_soc_get_volsw, da7219_mixin_gain_put,
			   da7219_mixin_gain_tlv),
	SOC_SINGLE("Mixin Switch", DA7219_MIXIN_L_CTRL,
		   DA7219_MIXIN_L_AMP_MUTE_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_INVERT),
	SOC_SINGLE("Mixin Gain Ramp Switch", DA7219_MIXIN_L_CTRL,
		   DA7219_MIXIN_L_AMP_RAMP_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_NO_INVERT),
	SOC_SINGLE("Mixin ZC Gain Switch", DA7219_MIXIN_L_CTRL,
		   DA7219_MIXIN_L_AMP_ZC_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_NO_INVERT),

	/* ADC */
	SOC_SINGLE_TLV("Capture Digital Volume", DA7219_ADC_L_GAIN,
		       DA7219_ADC_L_DIGITAL_GAIN_SHIFT,
		       DA7219_ADC_L_DIGITAL_GAIN_MAX, DA7219_NO_INVERT,
		       da7219_adc_dig_gain_tlv),
	SOC_SINGLE("Capture Digital Switch", DA7219_ADC_L_CTRL,
		   DA7219_ADC_L_MUTE_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_INVERT),
	SOC_SINGLE("Capture Digital Gain Ramp Switch", DA7219_ADC_L_CTRL,
		   DA7219_ADC_L_RAMP_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_NO_INVERT),

	/* ALC */
	SOC_ENUM("ALC Attack Rate", da7219_alc_attack_rate),
	SOC_ENUM("ALC Release Rate", da7219_alc_release_rate),
	SOC_ENUM("ALC Hold Time", da7219_alc_hold_समय),
	SOC_ENUM("ALC Envelope Attack Rate", da7219_alc_env_attack_rate),
	SOC_ENUM("ALC Envelope Release Rate", da7219_alc_env_release_rate),
	SOC_SINGLE_TLV("ALC Noise Threshold", DA7219_ALC_NOISE,
		       DA7219_ALC_NOISE_SHIFT, DA7219_ALC_THRESHOLD_MAX,
		       DA7219_INVERT, da7219_alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Min Threshold", DA7219_ALC_TARGET_MIN,
		       DA7219_ALC_THRESHOLD_MIN_SHIFT, DA7219_ALC_THRESHOLD_MAX,
		       DA7219_INVERT, da7219_alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Threshold", DA7219_ALC_TARGET_MAX,
		       DA7219_ALC_THRESHOLD_MAX_SHIFT, DA7219_ALC_THRESHOLD_MAX,
		       DA7219_INVERT, da7219_alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Attenuation", DA7219_ALC_GAIN_LIMITS,
		       DA7219_ALC_ATTEN_MAX_SHIFT, DA7219_ALC_ATTEN_GAIN_MAX,
		       DA7219_NO_INVERT, da7219_alc_gain_tlv),
	SOC_SINGLE_TLV("ALC Max Volume", DA7219_ALC_GAIN_LIMITS,
		       DA7219_ALC_GAIN_MAX_SHIFT, DA7219_ALC_ATTEN_GAIN_MAX,
		       DA7219_NO_INVERT, da7219_alc_gain_tlv),
	SOC_SINGLE_RANGE_TLV("ALC Min Analog Volume", DA7219_ALC_ANA_GAIN_LIMITS,
			     DA7219_ALC_ANA_GAIN_MIN_SHIFT,
			     DA7219_ALC_ANA_GAIN_MIN, DA7219_ALC_ANA_GAIN_MAX,
			     DA7219_NO_INVERT, da7219_alc_ana_gain_tlv),
	SOC_SINGLE_RANGE_TLV("ALC Max Analog Volume", DA7219_ALC_ANA_GAIN_LIMITS,
			     DA7219_ALC_ANA_GAIN_MAX_SHIFT,
			     DA7219_ALC_ANA_GAIN_MIN, DA7219_ALC_ANA_GAIN_MAX,
			     DA7219_NO_INVERT, da7219_alc_ana_gain_tlv),
	SOC_ENUM("ALC Anticlip Step", da7219_alc_anticlip_step),
	SOC_SINGLE("ALC Anticlip Switch", DA7219_ALC_ANTICLIP_CTRL,
		   DA7219_ALC_ANTIPCLIP_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_NO_INVERT),
	SOC_SINGLE_EXT("ALC Switch", DA7219_ALC_CTRL1, DA7219_ALC_EN_SHIFT,
		       DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT,
		       snd_soc_get_volsw, da7219_alc_sw_put),

	/* Input High-Pass Filters */
	SOC_ENUM("ADC HPF Mode", da7219_adc_hpf_mode),
	SOC_ENUM("ADC HPF Corner Audio", da7219_adc_audio_hpf_corner),
	SOC_ENUM("ADC HPF Corner Voice", da7219_adc_voice_hpf_corner),

	/* Sidetone Filter */
	SOC_SINGLE_TLV("Sidetone Volume", DA7219_SIDETONE_GAIN,
		       DA7219_SIDETONE_GAIN_SHIFT, DA7219_SIDETONE_GAIN_MAX,
		       DA7219_NO_INVERT, da7219_sidetone_gain_tlv),
	SOC_SINGLE("Sidetone Switch", DA7219_SIDETONE_CTRL,
		   DA7219_SIDETONE_MUTE_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		   DA7219_INVERT),

	/* Tone Generator */
	SOC_SINGLE_EXT_TLV("ToneGen Volume", DA7219_TONE_GEN_CFG2,
			   DA7219_TONE_GEN_GAIN_SHIFT, DA7219_TONE_GEN_GAIN_MAX,
			   DA7219_NO_INVERT, da7219_volsw_locked_get,
			   da7219_volsw_locked_put, da7219_tonegen_gain_tlv),
	SOC_ENUM_EXT("ToneGen DTMF Key", da7219_tonegen_dपंचांगf_key,
		     da7219_क्रमागत_locked_get, da7219_क्रमागत_locked_put),
	SOC_SINGLE_EXT("ToneGen DTMF Switch", DA7219_TONE_GEN_CFG1,
		       DA7219_DTMF_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		       DA7219_NO_INVERT, da7219_volsw_locked_get,
		       da7219_volsw_locked_put),
	SOC_ENUM_EXT("ToneGen Sinewave Gen Type", da7219_tonegen_swg_sel,
		     da7219_क्रमागत_locked_get, da7219_क्रमागत_locked_put),
	SOC_SINGLE_EXT("ToneGen Sinewave1 Freq", DA7219_TONE_GEN_FREQ1_L,
		       DA7219_FREQ1_L_SHIFT, DA7219_FREQ_MAX, DA7219_NO_INVERT,
		       da7219_tonegen_freq_get, da7219_tonegen_freq_put),
	SOC_SINGLE_EXT("ToneGen Sinewave2 Freq", DA7219_TONE_GEN_FREQ2_L,
		       DA7219_FREQ2_L_SHIFT, DA7219_FREQ_MAX, DA7219_NO_INVERT,
		       da7219_tonegen_freq_get, da7219_tonegen_freq_put),
	SOC_SINGLE_EXT("ToneGen On Time", DA7219_TONE_GEN_ON_PER,
		       DA7219_BEEP_ON_PER_SHIFT, DA7219_BEEP_ON_OFF_MAX,
		       DA7219_NO_INVERT, da7219_volsw_locked_get,
		       da7219_volsw_locked_put),
	SOC_SINGLE("ToneGen Off Time", DA7219_TONE_GEN_OFF_PER,
		   DA7219_BEEP_OFF_PER_SHIFT, DA7219_BEEP_ON_OFF_MAX,
		   DA7219_NO_INVERT),

	/* Gain ramping */
	SOC_ENUM("Gain Ramp Rate", da7219_gain_ramp_rate),

	/* DAC High-Pass Filter */
	SOC_ENUM_EXT("DAC HPF Mode", da7219_dac_hpf_mode,
		     da7219_क्रमागत_locked_get, da7219_क्रमागत_locked_put),
	SOC_ENUM("DAC HPF Corner Audio", da7219_dac_audio_hpf_corner),
	SOC_ENUM("DAC HPF Corner Voice", da7219_dac_voice_hpf_corner),

	/* DAC 5-Band Equaliser */
	SOC_SINGLE_TLV("DAC EQ Band1 Volume", DA7219_DAC_FILTERS2,
		       DA7219_DAC_EQ_BAND1_SHIFT, DA7219_DAC_EQ_BAND_MAX,
		       DA7219_NO_INVERT, da7219_dac_eq_band_tlv),
	SOC_SINGLE_TLV("DAC EQ Band2 Volume", DA7219_DAC_FILTERS2,
		       DA7219_DAC_EQ_BAND2_SHIFT, DA7219_DAC_EQ_BAND_MAX,
		       DA7219_NO_INVERT, da7219_dac_eq_band_tlv),
	SOC_SINGLE_TLV("DAC EQ Band3 Volume", DA7219_DAC_FILTERS3,
		       DA7219_DAC_EQ_BAND3_SHIFT, DA7219_DAC_EQ_BAND_MAX,
		       DA7219_NO_INVERT, da7219_dac_eq_band_tlv),
	SOC_SINGLE_TLV("DAC EQ Band4 Volume", DA7219_DAC_FILTERS3,
		       DA7219_DAC_EQ_BAND4_SHIFT, DA7219_DAC_EQ_BAND_MAX,
		       DA7219_NO_INVERT, da7219_dac_eq_band_tlv),
	SOC_SINGLE_TLV("DAC EQ Band5 Volume", DA7219_DAC_FILTERS4,
		       DA7219_DAC_EQ_BAND5_SHIFT, DA7219_DAC_EQ_BAND_MAX,
		       DA7219_NO_INVERT, da7219_dac_eq_band_tlv),
	SOC_SINGLE_EXT("DAC EQ Switch", DA7219_DAC_FILTERS4,
		       DA7219_DAC_EQ_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		       DA7219_NO_INVERT, da7219_volsw_locked_get,
		       da7219_volsw_locked_put),

	/* DAC Sofपंचांगute */
	SOC_ENUM("DAC Soft Mute Rate", da7219_dac_sofपंचांगute_rate),
	SOC_SINGLE_EXT("DAC Soft Mute Switch", DA7219_DAC_FILTERS5,
		       DA7219_DAC_SOFTMUTE_EN_SHIFT, DA7219_SWITCH_EN_MAX,
		       DA7219_NO_INVERT, da7219_volsw_locked_get,
		       da7219_volsw_locked_put),

	/* DAC Noise Gate */
	SOC_ENUM("DAC NG Setup Time", da7219_dac_ng_setup_समय),
	SOC_ENUM("DAC NG Rampup Rate", da7219_dac_ng_rampup_rate),
	SOC_ENUM("DAC NG Rampdown Rate", da7219_dac_ng_rampकरोwn_rate),
	SOC_SINGLE_TLV("DAC NG Off Threshold", DA7219_DAC_NG_OFF_THRESH,
		       DA7219_DAC_NG_OFF_THRESHOLD_SHIFT,
		       DA7219_DAC_NG_THRESHOLD_MAX, DA7219_NO_INVERT,
		       da7219_dac_ng_threshold_tlv),
	SOC_SINGLE_TLV("DAC NG On Threshold", DA7219_DAC_NG_ON_THRESH,
		       DA7219_DAC_NG_ON_THRESHOLD_SHIFT,
		       DA7219_DAC_NG_THRESHOLD_MAX, DA7219_NO_INVERT,
		       da7219_dac_ng_threshold_tlv),
	SOC_SINGLE("DAC NG Switch", DA7219_DAC_NG_CTRL, DA7219_DAC_NG_EN_SHIFT,
		   DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),

	/* DACs */
	SOC_DOUBLE_R_EXT_TLV("Playback Digital Volume", DA7219_DAC_L_GAIN,
			     DA7219_DAC_R_GAIN, DA7219_DAC_L_DIGITAL_GAIN_SHIFT,
			     DA7219_DAC_DIGITAL_GAIN_MAX, DA7219_NO_INVERT,
			     da7219_volsw_locked_get, da7219_volsw_locked_put,
			     da7219_dac_dig_gain_tlv),
	SOC_DOUBLE_R_EXT("Playback Digital Switch", DA7219_DAC_L_CTRL,
			 DA7219_DAC_R_CTRL, DA7219_DAC_L_MUTE_EN_SHIFT,
			 DA7219_SWITCH_EN_MAX, DA7219_INVERT,
			 da7219_volsw_locked_get, da7219_volsw_locked_put),
	SOC_DOUBLE_R("Playback Digital Gain Ramp Switch", DA7219_DAC_L_CTRL,
		     DA7219_DAC_R_CTRL, DA7219_DAC_L_RAMP_EN_SHIFT,
		     DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),

	/* CP */
	SOC_ENUM("Charge Pump Track Mode", da7219_cp_track_mode),
	SOC_SINGLE("Charge Pump Threshold", DA7219_CP_VOL_THRESHOLD1,
		   DA7219_CP_THRESH_VDD2_SHIFT, DA7219_CP_THRESH_VDD2_MAX,
		   DA7219_NO_INVERT),

	/* Headphones */
	SOC_DOUBLE_R_EXT_TLV("Headphone Volume", DA7219_HP_L_GAIN,
			     DA7219_HP_R_GAIN, DA7219_HP_L_AMP_GAIN_SHIFT,
			     DA7219_HP_AMP_GAIN_MAX, DA7219_NO_INVERT,
			     da7219_volsw_locked_get, da7219_volsw_locked_put,
			     da7219_hp_gain_tlv),
	SOC_DOUBLE_R_EXT("Headphone Switch", DA7219_HP_L_CTRL, DA7219_HP_R_CTRL,
			 DA7219_HP_L_AMP_MUTE_EN_SHIFT, DA7219_SWITCH_EN_MAX,
			 DA7219_INVERT, da7219_volsw_locked_get,
			 da7219_volsw_locked_put),
	SOC_DOUBLE_R("Headphone Gain Ramp Switch", DA7219_HP_L_CTRL,
		     DA7219_HP_R_CTRL, DA7219_HP_L_AMP_RAMP_EN_SHIFT,
		     DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),
	SOC_DOUBLE_R("Headphone ZC Gain Switch", DA7219_HP_L_CTRL,
		     DA7219_HP_R_CTRL, DA7219_HP_L_AMP_ZC_EN_SHIFT,
		     DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),
पूर्ण;


/*
 * DAPM Mux Controls
 */

अटल स्थिर अक्षर * स्थिर da7219_out_sel_txt[] = अणु
	"ADC", "Tone Generator", "DAIL", "DAIR"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7219_out_dail_sel =
	SOC_ENUM_SINGLE(DA7219_DIG_ROUTING_DAI,
			DA7219_DAI_L_SRC_SHIFT,
			DA7219_OUT_SRC_MAX,
			da7219_out_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7219_out_dail_sel_mux =
	SOC_DAPM_ENUM("Out DAIL Mux", da7219_out_dail_sel);

अटल स्थिर काष्ठा soc_क्रमागत da7219_out_dair_sel =
	SOC_ENUM_SINGLE(DA7219_DIG_ROUTING_DAI,
			DA7219_DAI_R_SRC_SHIFT,
			DA7219_OUT_SRC_MAX,
			da7219_out_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7219_out_dair_sel_mux =
	SOC_DAPM_ENUM("Out DAIR Mux", da7219_out_dair_sel);

अटल स्थिर काष्ठा soc_क्रमागत da7219_out_dacl_sel =
	SOC_ENUM_SINGLE(DA7219_DIG_ROUTING_DAC,
			DA7219_DAC_L_SRC_SHIFT,
			DA7219_OUT_SRC_MAX,
			da7219_out_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7219_out_dacl_sel_mux =
	SOC_DAPM_ENUM("Out DACL Mux", da7219_out_dacl_sel);

अटल स्थिर काष्ठा soc_क्रमागत da7219_out_dacr_sel =
	SOC_ENUM_SINGLE(DA7219_DIG_ROUTING_DAC,
			DA7219_DAC_R_SRC_SHIFT,
			DA7219_OUT_SRC_MAX,
			da7219_out_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7219_out_dacr_sel_mux =
	SOC_DAPM_ENUM("Out DACR Mux", da7219_out_dacr_sel);


/*
 * DAPM Mixer Controls
 */

अटल स्थिर काष्ठा snd_kcontrol_new da7219_mixin_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Switch", DA7219_MIXIN_L_SELECT,
			DA7219_MIXIN_L_MIX_SELECT_SHIFT,
			DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7219_mixout_l_controls[] = अणु
	SOC_DAPM_SINGLE("DACL Switch", DA7219_MIXOUT_L_SELECT,
			DA7219_MIXOUT_L_MIX_SELECT_SHIFT,
			DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7219_mixout_r_controls[] = अणु
	SOC_DAPM_SINGLE("DACR Switch", DA7219_MIXOUT_R_SELECT,
			DA7219_MIXOUT_R_MIX_SELECT_SHIFT,
			DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),
पूर्ण;

#घोषणा DA7219_DMIX_ST_CTRLS(reg)					\
	SOC_DAPM_SINGLE("Out FilterL Switch", reg,			\
			DA7219_DMIX_ST_SRC_OUTFILT1L_SHIFT,		\
			DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),	\
	SOC_DAPM_SINGLE("Out FilterR Switch", reg,			\
			DA7219_DMIX_ST_SRC_OUTFILT1R_SHIFT,		\
			DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT),	\
	SOC_DAPM_SINGLE("Sidetone Switch", reg,				\
			DA7219_DMIX_ST_SRC_SIDETONE_SHIFT,		\
			DA7219_SWITCH_EN_MAX, DA7219_NO_INVERT)		\

अटल स्थिर काष्ठा snd_kcontrol_new da7219_st_out_filtl_mix_controls[] = अणु
	DA7219_DMIX_ST_CTRLS(DA7219_DROUTING_ST_OUTFILT_1L),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7219_st_out_filtr_mix_controls[] = अणु
	DA7219_DMIX_ST_CTRLS(DA7219_DROUTING_ST_OUTFILT_1R),
पूर्ण;


/*
 * DAPM Events
 */

अटल पूर्णांक da7219_mic_pga_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (da7219->micbias_on_event) अणु
			/*
			 * Delay only क्रम first capture after bias enabled to
			 * aव्योम possible DC offset related noise.
			 */
			da7219->micbias_on_event = false;
			msleep(da7219->mic_pga_delay);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_dai_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा clk *bclk = da7219->dai_clks[DA7219_DAI_BCLK_IDX];
	u8 pll_ctrl, pll_status;
	पूर्णांक i = 0, ret;
	bool srm_lock = false;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (da7219->master) अणु
			/* Enable DAI clks क्रम master mode */
			अगर (bclk) अणु
				ret = clk_prepare_enable(bclk);
				अगर (ret) अणु
					dev_err(component->dev,
						"Failed to enable DAI clks\n");
					वापस ret;
				पूर्ण
			पूर्ण अन्यथा अणु
				snd_soc_component_update_bits(component,
							      DA7219_DAI_CLK_MODE,
							      DA7219_DAI_CLK_EN_MASK,
							      DA7219_DAI_CLK_EN_MASK);
			पूर्ण
		पूर्ण

		/* PC synchronised to DAI */
		snd_soc_component_update_bits(component, DA7219_PC_COUNT,
				    DA7219_PC_FREERUN_MASK, 0);

		/* Slave mode, अगर SRM not enabled no need क्रम status checks */
		pll_ctrl = snd_soc_component_पढ़ो(component, DA7219_PLL_CTRL);
		अगर ((pll_ctrl & DA7219_PLL_MODE_MASK) != DA7219_PLL_MODE_SRM)
			वापस 0;

		/* Check SRM has locked */
		करो अणु
			pll_status = snd_soc_component_पढ़ो(component, DA7219_PLL_SRM_STS);
			अगर (pll_status & DA7219_PLL_SRM_STS_SRM_LOCK) अणु
				srm_lock = true;
			पूर्ण अन्यथा अणु
				++i;
				msleep(50);
			पूर्ण
		पूर्ण जबतक ((i < DA7219_SRM_CHECK_RETRIES) && (!srm_lock));

		अगर (!srm_lock)
			dev_warn(component->dev, "SRM failed to lock\n");

		वापस 0;
	हाल SND_SOC_DAPM_POST_PMD:
		/* PC मुक्त-running */
		snd_soc_component_update_bits(component, DA7219_PC_COUNT,
				    DA7219_PC_FREERUN_MASK,
				    DA7219_PC_FREERUN_MASK);

		/* Disable DAI clks अगर in master mode */
		अगर (da7219->master) अणु
			अगर (bclk)
				clk_disable_unprepare(bclk);
			अन्यथा
				snd_soc_component_update_bits(component,
							      DA7219_DAI_CLK_MODE,
							      DA7219_DAI_CLK_EN_MASK,
							      0);
		पूर्ण

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक da7219_settling_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		msleep(DA7219_SETTLING_DELAY);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_mixout_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 hp_ctrl, min_gain_mask;

	चयन (w->reg) अणु
	हाल DA7219_MIXOUT_L_CTRL:
		hp_ctrl = DA7219_HP_L_CTRL;
		min_gain_mask = DA7219_HP_L_AMP_MIN_GAIN_EN_MASK;
		अवरोध;
	हाल DA7219_MIXOUT_R_CTRL:
		hp_ctrl = DA7219_HP_R_CTRL;
		min_gain_mask = DA7219_HP_R_AMP_MIN_GAIN_EN_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMD:
		/* Enable minimum gain on HP to aव्योम pops */
		snd_soc_component_update_bits(component, hp_ctrl, min_gain_mask,
				    min_gain_mask);

		msleep(DA7219_MIN_GAIN_DELAY);

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* Remove minimum gain on HP */
		snd_soc_component_update_bits(component, hp_ctrl, min_gain_mask, 0);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_gain_ramp_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
	हाल SND_SOC_DAPM_PRE_PMD:
		/* Ensure nominal gain ramping क्रम DAPM sequence */
		da7219->gain_ramp_ctrl =
			snd_soc_component_पढ़ो(component, DA7219_GAIN_RAMP_CTRL);
		snd_soc_component_ग_लिखो(component, DA7219_GAIN_RAMP_CTRL,
			      DA7219_GAIN_RAMP_RATE_NOMINAL);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		/* Restore previous gain ramp settings */
		snd_soc_component_ग_लिखो(component, DA7219_GAIN_RAMP_CTRL,
			      da7219->gain_ramp_ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * DAPM Widमाला_लो
 */

अटल स्थिर काष्ठा snd_soc_dapm_widget da7219_dapm_widमाला_लो[] = अणु
	/* Input Supplies */
	SND_SOC_DAPM_SUPPLY("Mic Bias", DA7219_MICBIAS_CTRL,
			    DA7219_MICBIAS1_EN_SHIFT, DA7219_NO_INVERT,
			    शून्य, 0),

	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC"),

	/* Input PGAs */
	SND_SOC_DAPM_PGA_E("Mic PGA", DA7219_MIC_1_CTRL,
			   DA7219_MIC_1_AMP_EN_SHIFT, DA7219_NO_INVERT,
			   शून्य, 0, da7219_mic_pga_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("Mixin PGA", DA7219_MIXIN_L_CTRL,
			   DA7219_MIXIN_L_AMP_EN_SHIFT, DA7219_NO_INVERT,
			   शून्य, 0, da7219_settling_event, SND_SOC_DAPM_POST_PMU),

	/* Input Filters */
	SND_SOC_DAPM_ADC("ADC", शून्य, DA7219_ADC_L_CTRL, DA7219_ADC_L_EN_SHIFT,
			 DA7219_NO_INVERT),

	/* Tone Generator */
	SND_SOC_DAPM_SIGGEN("TONE"),
	SND_SOC_DAPM_PGA("Tone Generator", DA7219_TONE_GEN_CFG1,
			 DA7219_START_STOPN_SHIFT, DA7219_NO_INVERT, शून्य, 0),

	/* Sidetone Input */
	SND_SOC_DAPM_ADC("Sidetone Filter", शून्य, DA7219_SIDETONE_CTRL,
			 DA7219_SIDETONE_EN_SHIFT, DA7219_NO_INVERT),

	/* Input Mixer Supply */
	SND_SOC_DAPM_SUPPLY("Mixer In Supply", DA7219_MIXIN_L_CTRL,
			    DA7219_MIXIN_L_MIX_EN_SHIFT, DA7219_NO_INVERT,
			    शून्य, 0),

	/* Input Mixer */
	SND_SOC_DAPM_MIXER("Mixer In", SND_SOC_NOPM, 0, 0,
			   da7219_mixin_controls,
			   ARRAY_SIZE(da7219_mixin_controls)),

	/* Input Muxes */
	SND_SOC_DAPM_MUX("Out DAIL Mux", SND_SOC_NOPM, 0, 0,
			 &da7219_out_dail_sel_mux),
	SND_SOC_DAPM_MUX("Out DAIR Mux", SND_SOC_NOPM, 0, 0,
			 &da7219_out_dair_sel_mux),

	/* DAI Supply */
	SND_SOC_DAPM_SUPPLY("DAI", DA7219_DAI_CTRL, DA7219_DAI_EN_SHIFT,
			    DA7219_NO_INVERT, da7219_dai_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* DAI */
	SND_SOC_DAPM_AIF_OUT("DAIOUT", "Capture", 0, DA7219_DAI_TDM_CTRL,
			     DA7219_DAI_OE_SHIFT, DA7219_NO_INVERT),
	SND_SOC_DAPM_AIF_IN("DAIIN", "Playback", 0, SND_SOC_NOPM, 0, 0),

	/* Output Muxes */
	SND_SOC_DAPM_MUX("Out DACL Mux", SND_SOC_NOPM, 0, 0,
			 &da7219_out_dacl_sel_mux),
	SND_SOC_DAPM_MUX("Out DACR Mux", SND_SOC_NOPM, 0, 0,
			 &da7219_out_dacr_sel_mux),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Mixer Out FilterL", SND_SOC_NOPM, 0, 0,
			   da7219_mixout_l_controls,
			   ARRAY_SIZE(da7219_mixout_l_controls)),
	SND_SOC_DAPM_MIXER("Mixer Out FilterR", SND_SOC_NOPM, 0, 0,
			   da7219_mixout_r_controls,
			   ARRAY_SIZE(da7219_mixout_r_controls)),

	/* Sidetone Mixers */
	SND_SOC_DAPM_MIXER("ST Mixer Out FilterL", SND_SOC_NOPM, 0, 0,
			   da7219_st_out_filtl_mix_controls,
			   ARRAY_SIZE(da7219_st_out_filtl_mix_controls)),
	SND_SOC_DAPM_MIXER("ST Mixer Out FilterR", SND_SOC_NOPM, 0,
			   0, da7219_st_out_filtr_mix_controls,
			   ARRAY_SIZE(da7219_st_out_filtr_mix_controls)),

	/* DACs */
	SND_SOC_DAPM_DAC_E("DACL", शून्य, DA7219_DAC_L_CTRL,
			   DA7219_DAC_L_EN_SHIFT, DA7219_NO_INVERT,
			   da7219_settling_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DACR", शून्य, DA7219_DAC_R_CTRL,
			   DA7219_DAC_R_EN_SHIFT, DA7219_NO_INVERT,
			   da7219_settling_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* Output PGAs */
	SND_SOC_DAPM_PGA_E("Mixout Left PGA", DA7219_MIXOUT_L_CTRL,
			   DA7219_MIXOUT_L_AMP_EN_SHIFT, DA7219_NO_INVERT,
			   शून्य, 0, da7219_mixout_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("Mixout Right PGA", DA7219_MIXOUT_R_CTRL,
			   DA7219_MIXOUT_R_AMP_EN_SHIFT, DA7219_NO_INVERT,
			   शून्य, 0, da7219_mixout_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY_S("Headphone Left PGA", 1, DA7219_HP_L_CTRL,
			      DA7219_HP_L_AMP_EN_SHIFT, DA7219_NO_INVERT,
			      da7219_settling_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("Headphone Right PGA", 1, DA7219_HP_R_CTRL,
			      DA7219_HP_R_AMP_EN_SHIFT, DA7219_NO_INVERT,
			      da7219_settling_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* Output Supplies */
	SND_SOC_DAPM_SUPPLY_S("Charge Pump", 0, DA7219_CP_CTRL,
			      DA7219_CP_EN_SHIFT, DA7219_NO_INVERT,
			      da7219_settling_event,
			      SND_SOC_DAPM_POST_PMU),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),

	/* Pre/Post Power */
	SND_SOC_DAPM_PRE("Pre Power Gain Ramp", da7219_gain_ramp_event),
	SND_SOC_DAPM_POST("Post Power Gain Ramp", da7219_gain_ramp_event),
पूर्ण;


/*
 * DAPM Mux Routes
 */

#घोषणा DA7219_OUT_DAI_MUX_ROUTES(name)			\
	अणुname, "ADC", "Mixer In"पूर्ण,			\
	अणुname, "Tone Generator", "Tone Generator"पूर्ण,	\
	अणुname, "DAIL", "DAIOUT"पूर्ण,			\
	अणुname, "DAIR", "DAIOUT"पूर्ण

#घोषणा DA7219_OUT_DAC_MUX_ROUTES(name)			\
	अणुname, "ADC", "Mixer In"पूर्ण,			\
	अणुname, "Tone Generator", "Tone Generator"पूर्ण,		\
	अणुname, "DAIL", "DAIIN"पूर्ण,			\
	अणुname, "DAIR", "DAIIN"पूर्ण

/*
 * DAPM Mixer Routes
 */

#घोषणा DA7219_DMIX_ST_ROUTES(name)				\
	अणुname, "Out FilterL Switch", "Mixer Out FilterL"पूर्ण,	\
	अणुname, "Out FilterR Switch", "Mixer Out FilterR"पूर्ण,	\
	अणुname, "Sidetone Switch", "Sidetone Filter"पूर्ण


/*
 * DAPM audio route definition
 */

अटल स्थिर काष्ठा snd_soc_dapm_route da7219_audio_map[] = अणु
	/* Input paths */
	अणु"MIC", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic PGA", शून्य, "MIC"पूर्ण,
	अणु"Mixin PGA", शून्य, "Mic PGA"पूर्ण,
	अणु"ADC", शून्य, "Mixin PGA"पूर्ण,

	अणु"Mixer In", शून्य, "Mixer In Supply"पूर्ण,
	अणु"Mixer In", "Mic Switch", "ADC"पूर्ण,

	अणु"Sidetone Filter", शून्य, "Mixer In"पूर्ण,

	अणु"Tone Generator", शून्य, "TONE"पूर्ण,

	DA7219_OUT_DAI_MUX_ROUTES("Out DAIL Mux"),
	DA7219_OUT_DAI_MUX_ROUTES("Out DAIR Mux"),

	अणु"DAIOUT", शून्य, "Out DAIL Mux"पूर्ण,
	अणु"DAIOUT", शून्य, "Out DAIR Mux"पूर्ण,
	अणु"DAIOUT", शून्य, "DAI"पूर्ण,

	/* Output paths */
	अणु"DAIIN", शून्य, "DAI"पूर्ण,

	DA7219_OUT_DAC_MUX_ROUTES("Out DACL Mux"),
	DA7219_OUT_DAC_MUX_ROUTES("Out DACR Mux"),

	अणु"Mixer Out FilterL", "DACL Switch", "Out DACL Mux"पूर्ण,
	अणु"Mixer Out FilterR", "DACR Switch", "Out DACR Mux"पूर्ण,

	DA7219_DMIX_ST_ROUTES("ST Mixer Out FilterL"),
	DA7219_DMIX_ST_ROUTES("ST Mixer Out FilterR"),

	अणु"DACL", शून्य, "ST Mixer Out FilterL"पूर्ण,
	अणु"DACR", शून्य, "ST Mixer Out FilterR"पूर्ण,

	अणु"Mixout Left PGA", शून्य, "DACL"पूर्ण,
	अणु"Mixout Right PGA", शून्य, "DACR"पूर्ण,

	अणु"HPL", शून्य, "Mixout Left PGA"पूर्ण,
	अणु"HPR", शून्य, "Mixout Right PGA"पूर्ण,

	अणु"HPL", शून्य, "Headphone Left PGA"पूर्ण,
	अणु"HPR", शून्य, "Headphone Right PGA"पूर्ण,

	अणु"HPL", शून्य, "Charge Pump"पूर्ण,
	अणु"HPR", शून्य, "Charge Pump"पूर्ण,
पूर्ण;


/*
 * DAI operations
 */

अटल पूर्णांक da7219_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर ((da7219->clk_src == clk_id) && (da7219->mclk_rate == freq))
		वापस 0;

	अगर ((freq < 2000000) || (freq > 54000000)) अणु
		dev_err(codec_dai->dev, "Unsupported MCLK value %d\n",
			freq);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&da7219->pll_lock);

	चयन (clk_id) अणु
	हाल DA7219_CLKSRC_MCLK_SQR:
		snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
				    DA7219_PLL_MCLK_SQR_EN_MASK,
				    DA7219_PLL_MCLK_SQR_EN_MASK);
		अवरोध;
	हाल DA7219_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
				    DA7219_PLL_MCLK_SQR_EN_MASK, 0);
		अवरोध;
	शेष:
		dev_err(codec_dai->dev, "Unknown clock source %d\n", clk_id);
		mutex_unlock(&da7219->pll_lock);
		वापस -EINVAL;
	पूर्ण

	da7219->clk_src = clk_id;

	अगर (da7219->mclk) अणु
		freq = clk_round_rate(da7219->mclk, freq);
		ret = clk_set_rate(da7219->mclk, freq);
		अगर (ret) अणु
			dev_err(codec_dai->dev, "Failed to set clock rate %d\n",
				freq);
			mutex_unlock(&da7219->pll_lock);
			वापस ret;
		पूर्ण
	पूर्ण

	da7219->mclk_rate = freq;

	mutex_unlock(&da7219->pll_lock);

	वापस 0;
पूर्ण

पूर्णांक da7219_set_pll(काष्ठा snd_soc_component *component, पूर्णांक source, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	u8 pll_ctrl, inभाग_bits, inभाग;
	u8 pll_frac_top, pll_frac_bot, pll_पूर्णांकeger;
	u32 freq_ref;
	u64 frac_भाग;

	/* Verअगरy 2MHz - 54MHz MCLK provided, and set input भागider */
	अगर (da7219->mclk_rate < 2000000) अणु
		dev_err(component->dev, "PLL input clock %d below valid range\n",
			da7219->mclk_rate);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (da7219->mclk_rate <= 4500000) अणु
		inभाग_bits = DA7219_PLL_INDIV_2_TO_4_5_MHZ;
		inभाग = DA7219_PLL_INDIV_2_TO_4_5_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7219->mclk_rate <= 9000000) अणु
		inभाग_bits = DA7219_PLL_INDIV_4_5_TO_9_MHZ;
		inभाग = DA7219_PLL_INDIV_4_5_TO_9_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7219->mclk_rate <= 18000000) अणु
		inभाग_bits = DA7219_PLL_INDIV_9_TO_18_MHZ;
		inभाग = DA7219_PLL_INDIV_9_TO_18_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7219->mclk_rate <= 36000000) अणु
		inभाग_bits = DA7219_PLL_INDIV_18_TO_36_MHZ;
		inभाग = DA7219_PLL_INDIV_18_TO_36_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7219->mclk_rate <= 54000000) अणु
		inभाग_bits = DA7219_PLL_INDIV_36_TO_54_MHZ;
		inभाग = DA7219_PLL_INDIV_36_TO_54_MHZ_VAL;
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "PLL input clock %d above valid range\n",
			da7219->mclk_rate);
		वापस -EINVAL;
	पूर्ण
	freq_ref = (da7219->mclk_rate / inभाग);
	pll_ctrl = inभाग_bits;

	/* Configure PLL */
	चयन (source) अणु
	हाल DA7219_SYSCLK_MCLK:
		pll_ctrl |= DA7219_PLL_MODE_BYPASS;
		snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
				    DA7219_PLL_INDIV_MASK |
				    DA7219_PLL_MODE_MASK, pll_ctrl);
		वापस 0;
	हाल DA7219_SYSCLK_PLL:
		pll_ctrl |= DA7219_PLL_MODE_NORMAL;
		अवरोध;
	हाल DA7219_SYSCLK_PLL_SRM:
		pll_ctrl |= DA7219_PLL_MODE_SRM;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid PLL config\n");
		वापस -EINVAL;
	पूर्ण

	/* Calculate भागiders क्रम PLL */
	pll_पूर्णांकeger = fout / freq_ref;
	frac_भाग = (u64)(fout % freq_ref) * 8192ULL;
	करो_भाग(frac_भाग, freq_ref);
	pll_frac_top = (frac_भाग >> DA7219_BYTE_SHIFT) & DA7219_BYTE_MASK;
	pll_frac_bot = (frac_भाग) & DA7219_BYTE_MASK;

	/* Write PLL config & भागiders */
	snd_soc_component_ग_लिखो(component, DA7219_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_ग_लिखो(component, DA7219_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_ग_लिखो(component, DA7219_PLL_INTEGER, pll_पूर्णांकeger);
	snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
			    DA7219_PLL_INDIV_MASK | DA7219_PLL_MODE_MASK,
			    pll_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&da7219->pll_lock);
	ret = da7219_set_pll(component, source, fout);
	mutex_unlock(&da7219->pll_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक da7219_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	u8 dai_clk_mode = 0, dai_ctrl = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		da7219->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		da7219->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7219_DAI_WCLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			dai_clk_mode |= DA7219_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7219_DAI_WCLK_POL_INV |
					DA7219_DAI_CLK_POL_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			dai_clk_mode |= DA7219_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7219_DAI_WCLK_POL_INV |
					DA7219_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7219_DAI_WCLK_POL_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		dai_ctrl |= DA7219_DAI_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dai_ctrl |= DA7219_DAI_FORMAT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		dai_ctrl |= DA7219_DAI_FORMAT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		dai_ctrl |= DA7219_DAI_FORMAT_DSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, DA7219_DAI_CLK_MODE,
			    DA7219_DAI_CLK_POL_MASK | DA7219_DAI_WCLK_POL_MASK,
			    dai_clk_mode);
	snd_soc_component_update_bits(component, DA7219_DAI_CTRL, DA7219_DAI_FORMAT_MASK,
			    dai_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_set_bclks_per_wclk(काष्ठा snd_soc_component *component,
				     अचिन्हित दीर्घ factor)
अणु
	u8 bclks_per_wclk;

	चयन (factor) अणु
	हाल 32:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_32;
		अवरोध;
	हाल 64:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_64;
		अवरोध;
	हाल 128:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_128;
		अवरोध;
	हाल 256:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, DA7219_DAI_CLK_MODE,
				      DA7219_DAI_BCLKS_PER_WCLK_MASK,
				      bclks_per_wclk);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				   पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा clk *wclk = da7219->dai_clks[DA7219_DAI_WCLK_IDX];
	काष्ठा clk *bclk = da7219->dai_clks[DA7219_DAI_BCLK_IDX];
	अचिन्हित पूर्णांक ch_mask;
	अचिन्हित दीर्घ sr, bclk_rate;
	u8 slot_offset;
	u16 offset;
	__le16 dai_offset;
	u32 frame_size;
	पूर्णांक ret;

	/* No channels enabled so disable TDM */
	अगर (!tx_mask) अणु
		snd_soc_component_update_bits(component, DA7219_DAI_TDM_CTRL,
				    DA7219_DAI_TDM_CH_EN_MASK |
				    DA7219_DAI_TDM_MODE_EN_MASK, 0);
		da7219->tdm_en = false;
		वापस 0;
	पूर्ण

	/* Check we have valid slots */
	slot_offset = ffs(tx_mask) - 1;
	ch_mask = (tx_mask >> slot_offset);
	अगर (fls(ch_mask) > DA7219_DAI_TDM_MAX_SLOTS) अणु
		dev_err(component->dev,
			"Invalid number of slots, max = %d\n",
			DA7219_DAI_TDM_MAX_SLOTS);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Ensure we have a valid offset पूर्णांकo the frame, based on slot width
	 * and slot offset of first slot we're पूर्णांकerested in.
	 */
	offset = slot_offset * slot_width;
	अगर (offset > DA7219_DAI_OFFSET_MAX) अणु
		dev_err(component->dev, "Invalid frame offset %d\n", offset);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If we're master, calculate & validate frame size based on slot info
	 * provided as we have a limited set of rates available.
	 */
	अगर (da7219->master) अणु
		frame_size = slots * slot_width;

		अगर (bclk) अणु
			sr = clk_get_rate(wclk);
			bclk_rate = sr * frame_size;
			ret = clk_set_rate(bclk, bclk_rate);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to set TDM BCLK rate %lu: %d\n",
					bclk_rate, ret);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = da7219_set_bclks_per_wclk(component, frame_size);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to set TDM BCLKs per WCLK %d: %d\n",
					frame_size, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	dai_offset = cpu_to_le16(offset);
	regmap_bulk_ग_लिखो(da7219->regmap, DA7219_DAI_OFFSET_LOWER,
			  &dai_offset, माप(dai_offset));

	snd_soc_component_update_bits(component, DA7219_DAI_TDM_CTRL,
			    DA7219_DAI_TDM_CH_EN_MASK |
			    DA7219_DAI_TDM_MODE_EN_MASK,
			    (ch_mask << DA7219_DAI_TDM_CH_EN_SHIFT) |
			    DA7219_DAI_TDM_MODE_EN_MASK);

	da7219->tdm_en = true;

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_set_sr(काष्ठा snd_soc_component *component,
			 अचिन्हित दीर्घ rate)
अणु
	u8 fs;

	चयन (rate) अणु
	हाल 8000:
		fs = DA7219_SR_8000;
		अवरोध;
	हाल 11025:
		fs = DA7219_SR_11025;
		अवरोध;
	हाल 12000:
		fs = DA7219_SR_12000;
		अवरोध;
	हाल 16000:
		fs = DA7219_SR_16000;
		अवरोध;
	हाल 22050:
		fs = DA7219_SR_22050;
		अवरोध;
	हाल 24000:
		fs = DA7219_SR_24000;
		अवरोध;
	हाल 32000:
		fs = DA7219_SR_32000;
		अवरोध;
	हाल 44100:
		fs = DA7219_SR_44100;
		अवरोध;
	हाल 48000:
		fs = DA7219_SR_48000;
		अवरोध;
	हाल 88200:
		fs = DA7219_SR_88200;
		अवरोध;
	हाल 96000:
		fs = DA7219_SR_96000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, DA7219_SR, fs);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा clk *wclk = da7219->dai_clks[DA7219_DAI_WCLK_IDX];
	काष्ठा clk *bclk = da7219->dai_clks[DA7219_DAI_BCLK_IDX];
	u8 dai_ctrl = 0;
	अचिन्हित पूर्णांक channels;
	अचिन्हित दीर्घ sr, bclk_rate;
	पूर्णांक word_len = params_width(params);
	पूर्णांक frame_size, ret;

	चयन (word_len) अणु
	हाल 16:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S16_LE;
		अवरोध;
	हाल 20:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S20_LE;
		अवरोध;
	हाल 24:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S24_LE;
		अवरोध;
	हाल 32:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S32_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	channels = params_channels(params);
	अगर ((channels < 1) || (channels > DA7219_DAI_CH_NUM_MAX)) अणु
		dev_err(component->dev,
			"Invalid number of channels, only 1 to %d supported\n",
			DA7219_DAI_CH_NUM_MAX);
		वापस -EINVAL;
	पूर्ण
	dai_ctrl |= channels << DA7219_DAI_CH_NUM_SHIFT;

	sr = params_rate(params);
	अगर (da7219->master && wclk) अणु
		ret = clk_set_rate(wclk, sr);
		अगर (ret) अणु
			dev_err(component->dev,
				"Failed to set WCLK SR %lu: %d\n", sr, ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = da7219_set_sr(component, sr);
		अगर (ret) अणु
			dev_err(component->dev,
				"Failed to set SR %lu: %d\n", sr, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * If we're master, then we have a limited set of BCLK rates we
	 * support. For slave mode this isn't the हाल and the codec can detect
	 * the BCLK rate स्वतःmatically.
	 */
	अगर (da7219->master && !da7219->tdm_en) अणु
		अगर ((word_len * DA7219_DAI_CH_NUM_MAX) <= 32)
			frame_size = 32;
		अन्यथा
			frame_size = 64;

		अगर (bclk) अणु
			bclk_rate = frame_size * sr;
			/*
			 * Rounding the rate here aव्योमs failure trying to set a
			 * new rate on an alपढ़ोy enabled bclk. In that
			 * instance this will just set the same rate as is
			 * currently in use, and so should जारी without
			 * problem, as दीर्घ as the BCLK rate is suitable क्रम the
			 * desired frame size.
			 */
			bclk_rate = clk_round_rate(bclk, bclk_rate);
			अगर ((bclk_rate / sr) < frame_size) अणु
				dev_err(component->dev,
					"BCLK rate mismatch against frame size");
				वापस -EINVAL;
			पूर्ण

			ret = clk_set_rate(bclk, bclk_rate);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to set BCLK rate %lu: %d\n",
					bclk_rate, ret);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = da7219_set_bclks_per_wclk(component, frame_size);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to set BCLKs per WCLK %d: %d\n",
					frame_size, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	snd_soc_component_update_bits(component, DA7219_DAI_CTRL,
			    DA7219_DAI_WORD_LENGTH_MASK |
			    DA7219_DAI_CH_NUM_MASK,
			    dai_ctrl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops da7219_dai_ops = अणु
	.hw_params	= da7219_hw_params,
	.set_sysclk	= da7219_set_dai_sysclk,
	.set_pll	= da7219_set_dai_pll,
	.set_fmt	= da7219_set_dai_fmt,
	.set_tdm_slot	= da7219_set_dai_tdm_slot,
पूर्ण;

#घोषणा DA7219_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा DA7219_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		      SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		      SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
		      SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |\
		      SNDRV_PCM_RATE_96000)

अटल काष्ठा snd_soc_dai_driver da7219_dai = अणु
	.name = "da7219-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = DA7219_DAI_CH_NUM_MAX,
		.rates = DA7219_RATES,
		.क्रमmats = DA7219_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = DA7219_DAI_CH_NUM_MAX,
		.rates = DA7219_RATES,
		.क्रमmats = DA7219_FORMATS,
	पूर्ण,
	.ops = &da7219_dai_ops,
	.symmetric_rate = 1,
	.symmetric_channels = 1,
	.symmetric_sample_bits = 1,
पूर्ण;


/*
 * DT/ACPI
 */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id da7219_of_match[] = अणु
	अणु .compatible = "dlg,da7219", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da7219_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id da7219_acpi_match[] = अणु
	अणु .id = "DLGS7219", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, da7219_acpi_match);
#पूर्ण_अगर

अटल क्रमागत da7219_micbias_voltage
	da7219_fw_micbias_lvl(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 1600:
		वापस DA7219_MICBIAS_1_6V;
	हाल 1800:
		वापस DA7219_MICBIAS_1_8V;
	हाल 2000:
		वापस DA7219_MICBIAS_2_0V;
	हाल 2200:
		वापस DA7219_MICBIAS_2_2V;
	हाल 2400:
		वापस DA7219_MICBIAS_2_4V;
	हाल 2600:
		वापस DA7219_MICBIAS_2_6V;
	शेष:
		dev_warn(dev, "Invalid micbias level");
		वापस DA7219_MICBIAS_2_2V;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_mic_amp_in_sel
	da7219_fw_mic_amp_in_sel(काष्ठा device *dev, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "diff")) अणु
		वापस DA7219_MIC_AMP_IN_SEL_DIFF;
	पूर्ण अन्यथा अगर (!म_भेद(str, "se_p")) अणु
		वापस DA7219_MIC_AMP_IN_SEL_SE_P;
	पूर्ण अन्यथा अगर (!म_भेद(str, "se_n")) अणु
		वापस DA7219_MIC_AMP_IN_SEL_SE_N;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Invalid mic input type selection");
		वापस DA7219_MIC_AMP_IN_SEL_DIFF;
	पूर्ण
पूर्ण

अटल काष्ठा da7219_pdata *da7219_fw_to_pdata(काष्ठा device *dev)
अणु
	काष्ठा da7219_pdata *pdata;
	स्थिर अक्षर *of_str;
	u32 of_val32;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->wakeup_source = device_property_पढ़ो_bool(dev, "wakeup-source");

	pdata->dai_clk_names[DA7219_DAI_WCLK_IDX] = "da7219-dai-wclk";
	pdata->dai_clk_names[DA7219_DAI_BCLK_IDX] = "da7219-dai-bclk";
	अगर (device_property_पढ़ो_string_array(dev, "clock-output-names",
					      pdata->dai_clk_names,
					      DA7219_DAI_NUM_CLKS) < 0)
		dev_warn(dev, "Using default DAI clk names: %s, %s\n",
			 pdata->dai_clk_names[DA7219_DAI_WCLK_IDX],
			 pdata->dai_clk_names[DA7219_DAI_BCLK_IDX]);

	अगर (device_property_पढ़ो_u32(dev, "dlg,micbias-lvl", &of_val32) >= 0)
		pdata->micbias_lvl = da7219_fw_micbias_lvl(dev, of_val32);
	अन्यथा
		pdata->micbias_lvl = DA7219_MICBIAS_2_2V;

	अगर (!device_property_पढ़ो_string(dev, "dlg,mic-amp-in-sel", &of_str))
		pdata->mic_amp_in_sel = da7219_fw_mic_amp_in_sel(dev, of_str);
	अन्यथा
		pdata->mic_amp_in_sel = DA7219_MIC_AMP_IN_SEL_DIFF;

	वापस pdata;
पूर्ण


/*
 * Codec driver functions
 */

अटल पूर्णांक da7219_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Enable MCLK क्रम transition to ON state */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY) अणु
			अगर (da7219->mclk) अणु
				ret = clk_prepare_enable(da7219->mclk);
				अगर (ret) अणु
					dev_err(component->dev,
						"Failed to enable mclk\n");
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण

		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			/* Master bias */
			snd_soc_component_update_bits(component, DA7219_REFERENCES,
					    DA7219_BIAS_EN_MASK,
					    DA7219_BIAS_EN_MASK);

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE) अणु
			/* Remove MCLK */
			अगर (da7219->mclk)
				clk_disable_unprepare(da7219->mclk);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Only disable master bias अगर we're not a wake-up source */
		अगर (!da7219->wakeup_source)
			snd_soc_component_update_bits(component, DA7219_REFERENCES,
					    DA7219_BIAS_EN_MASK, 0);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *da7219_supply_names[DA7219_NUM_SUPPLIES] = अणु
	[DA7219_SUPPLY_VDD] = "VDD",
	[DA7219_SUPPLY_VDDMIC] = "VDDMIC",
	[DA7219_SUPPLY_VDDIO] = "VDDIO",
पूर्ण;

अटल पूर्णांक da7219_handle_supplies(काष्ठा snd_soc_component *component,
				  u8 *io_voltage_lvl)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा regulator *vddio;
	पूर्णांक i, ret;

	/* Get required supplies */
	क्रम (i = 0; i < DA7219_NUM_SUPPLIES; ++i)
		da7219->supplies[i].supply = da7219_supply_names[i];

	ret = regulator_bulk_get(component->dev, DA7219_NUM_SUPPLIES,
				 da7219->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to get supplies");
		वापस ret;
	पूर्ण

	/* Default to upper range */
	*io_voltage_lvl = DA7219_IO_VOLTAGE_LEVEL_2_5V_3_6V;

	/* Determine VDDIO voltage provided */
	vddio = da7219->supplies[DA7219_SUPPLY_VDDIO].consumer;
	ret = regulator_get_voltage(vddio);
	अगर (ret < 1200000)
		dev_warn(component->dev, "Invalid VDDIO voltage\n");
	अन्यथा अगर (ret < 2800000)
		*io_voltage_lvl = DA7219_IO_VOLTAGE_LEVEL_1_2V_2_8V;

	/* Enable मुख्य supplies */
	ret = regulator_bulk_enable(DA7219_NUM_SUPPLIES, da7219->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to enable supplies");
		regulator_bulk_मुक्त(DA7219_NUM_SUPPLIES, da7219->supplies);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
अटल पूर्णांक da7219_wclk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;

	अगर (!da7219->master)
		वापस -EINVAL;

	snd_soc_component_update_bits(component, DA7219_DAI_CLK_MODE,
				      DA7219_DAI_CLK_EN_MASK,
				      DA7219_DAI_CLK_EN_MASK);

	वापस 0;
पूर्ण

अटल व्योम da7219_wclk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;

	अगर (!da7219->master)
		वापस;

	snd_soc_component_update_bits(component, DA7219_DAI_CLK_MODE,
				      DA7219_DAI_CLK_EN_MASK, 0);
पूर्ण

अटल पूर्णांक da7219_wclk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;
	u8 clk_reg;

	अगर (!da7219->master)
		वापस -EINVAL;

	clk_reg = snd_soc_component_पढ़ो(component, DA7219_DAI_CLK_MODE);

	वापस !!(clk_reg & DA7219_DAI_CLK_EN_MASK);
पूर्ण

अटल अचिन्हित दीर्घ da7219_wclk_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;
	u8 fs = snd_soc_component_पढ़ो(component, DA7219_SR);

	चयन (fs & DA7219_SR_MASK) अणु
	हाल DA7219_SR_8000:
		वापस 8000;
	हाल DA7219_SR_11025:
		वापस 11025;
	हाल DA7219_SR_12000:
		वापस 12000;
	हाल DA7219_SR_16000:
		वापस 16000;
	हाल DA7219_SR_22050:
		वापस 22050;
	हाल DA7219_SR_24000:
		वापस 24000;
	हाल DA7219_SR_32000:
		वापस 32000;
	हाल DA7219_SR_44100:
		वापस 44100;
	हाल DA7219_SR_48000:
		वापस 48000;
	हाल DA7219_SR_88200:
		वापस 88200;
	हाल DA7219_SR_96000:
		वापस 96000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल दीर्घ da7219_wclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_WCLK_IDX]);

	अगर (!da7219->master)
		वापस -EINVAL;

	अगर (rate < 11025)
		वापस 8000;
	अन्यथा अगर (rate < 12000)
		वापस 11025;
	अन्यथा अगर (rate < 16000)
		वापस 12000;
	अन्यथा अगर (rate < 22050)
		वापस 16000;
	अन्यथा अगर (rate < 24000)
		वापस 22050;
	अन्यथा अगर (rate < 32000)
		वापस 24000;
	अन्यथा अगर (rate < 44100)
		वापस 32000;
	अन्यथा अगर (rate < 48000)
		वापस 44100;
	अन्यथा अगर (rate < 88200)
		वापस 48000;
	अन्यथा अगर (rate < 96000)
		वापस 88200;
	अन्यथा
		वापस 96000;
पूर्ण

अटल पूर्णांक da7219_wclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_WCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;

	अगर (!da7219->master)
		वापस -EINVAL;

	वापस da7219_set_sr(component, rate);
पूर्ण

अटल अचिन्हित दीर्घ da7219_bclk_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_BCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;
	u8 bclks_per_wclk = snd_soc_component_पढ़ो(component,
						     DA7219_DAI_CLK_MODE);

	चयन (bclks_per_wclk & DA7219_DAI_BCLKS_PER_WCLK_MASK) अणु
	हाल DA7219_DAI_BCLKS_PER_WCLK_32:
		वापस parent_rate * 32;
	हाल DA7219_DAI_BCLKS_PER_WCLK_64:
		वापस parent_rate * 64;
	हाल DA7219_DAI_BCLKS_PER_WCLK_128:
		वापस parent_rate * 128;
	हाल DA7219_DAI_BCLKS_PER_WCLK_256:
		वापस parent_rate * 256;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ da7219_bclk_get_factor(अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ factor;

	factor = rate / parent_rate;
	अगर (factor < 64)
		वापस 32;
	अन्यथा अगर (factor < 128)
		वापस 64;
	अन्यथा अगर (factor < 256)
		वापस 128;
	अन्यथा
		वापस 256;
पूर्ण

अटल दीर्घ da7219_bclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_BCLK_IDX]);
	अचिन्हित दीर्घ factor;

	अगर (!*parent_rate || !da7219->master)
		वापस -EINVAL;

	/*
	 * We करोn't allow changing the parent rate as some BCLK rates can be
	 * derived from multiple parent WCLK rates (BCLK rates are set as a
	 * multiplier of WCLK in HW). We just करो some rounding करोwn based on the
	 * parent WCLK rate set and find the appropriate multiplier of BCLK to
	 * get the rounded करोwn BCLK value.
	 */
	factor = da7219_bclk_get_factor(rate, *parent_rate);

	वापस *parent_rate * factor;
पूर्ण

अटल पूर्णांक da7219_bclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा da7219_priv *da7219 =
		container_of(hw, काष्ठा da7219_priv,
			     dai_clks_hw[DA7219_DAI_BCLK_IDX]);
	काष्ठा snd_soc_component *component = da7219->component;
	अचिन्हित दीर्घ factor;

	अगर (!da7219->master)
		वापस -EINVAL;

	factor = da7219_bclk_get_factor(rate, parent_rate);

	वापस da7219_set_bclks_per_wclk(component, factor);
पूर्ण

अटल स्थिर काष्ठा clk_ops da7219_dai_clk_ops[DA7219_DAI_NUM_CLKS] = अणु
	[DA7219_DAI_WCLK_IDX] = अणु
		.prepare = da7219_wclk_prepare,
		.unprepare = da7219_wclk_unprepare,
		.is_prepared = da7219_wclk_is_prepared,
		.recalc_rate = da7219_wclk_recalc_rate,
		.round_rate = da7219_wclk_round_rate,
		.set_rate = da7219_wclk_set_rate,
	पूर्ण,
	[DA7219_DAI_BCLK_IDX] = अणु
		.recalc_rate = da7219_bclk_recalc_rate,
		.round_rate = da7219_bclk_round_rate,
		.set_rate = da7219_bclk_set_rate,
	पूर्ण,
पूर्ण;

अटल पूर्णांक da7219_रेजिस्टर_dai_clks(काष्ठा snd_soc_component *component)
अणु
	काष्ठा device *dev = component->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_pdata *pdata = da7219->pdata;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_hw_onecell_data *clk_data;
	पूर्णांक i, ret;

	/* For DT platक्रमms allocate onecell data क्रम घड़ी registration */
	अगर (np) अणु
		clk_data = kzalloc(काष्ठा_size(clk_data, hws, DA7219_DAI_NUM_CLKS),
				   GFP_KERNEL);
		अगर (!clk_data)
			वापस -ENOMEM;

		clk_data->num = DA7219_DAI_NUM_CLKS;
		da7219->clk_hw_data = clk_data;
	पूर्ण

	क्रम (i = 0; i < DA7219_DAI_NUM_CLKS; ++i) अणु
		काष्ठा clk_init_data init = अणुपूर्ण;
		काष्ठा clk_lookup *dai_clk_lookup;
		काष्ठा clk_hw *dai_clk_hw = &da7219->dai_clks_hw[i];

		चयन (i) अणु
		हाल DA7219_DAI_WCLK_IDX:
			/*
			 * If we can, make MCLK the parent of WCLK to ensure
			 * it's enabled as required.
			 */
			अगर (da7219->mclk) अणु
				parent_name = __clk_get_name(da7219->mclk);
				init.parent_names = &parent_name;
				init.num_parents = 1;
			पूर्ण अन्यथा अणु
				init.parent_names = शून्य;
				init.num_parents = 0;
			पूर्ण
			अवरोध;
		हाल DA7219_DAI_BCLK_IDX:
			/* Make WCLK the parent of BCLK */
			parent_name = __clk_get_name(da7219->dai_clks[DA7219_DAI_WCLK_IDX]);
			init.parent_names = &parent_name;
			init.num_parents = 1;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid clock index\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		init.name = pdata->dai_clk_names[i];
		init.ops = &da7219_dai_clk_ops[i];
		init.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_GATE;
		dai_clk_hw->init = &init;

		ret = clk_hw_रेजिस्टर(dev, dai_clk_hw);
		अगर (ret) अणु
			dev_warn(dev, "Failed to register %s: %d\n", init.name,
				 ret);
			जाओ err;
		पूर्ण
		da7219->dai_clks[i] = dai_clk_hw->clk;

		/* For DT setup onecell data, otherwise create lookup */
		अगर (np) अणु
			da7219->clk_hw_data->hws[i] = dai_clk_hw;
		पूर्ण अन्यथा अणु
			dai_clk_lookup = clkdev_hw_create(dai_clk_hw, init.name,
							  "%s", dev_name(dev));
			अगर (!dai_clk_lookup) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण अन्यथा अणु
				da7219->dai_clks_lookup[i] = dai_clk_lookup;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If we're using DT, then रेजिस्टर as provider accordingly */
	अगर (np) अणु
		ret = of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
					     da7219->clk_hw_data);
		अगर (ret) अणु
			dev_err(dev, "Failed to register clock provider\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	करो अणु
		अगर (da7219->dai_clks_lookup[i])
			clkdev_drop(da7219->dai_clks_lookup[i]);

		clk_hw_unरेजिस्टर(&da7219->dai_clks_hw[i]);
	पूर्ण जबतक (i-- > 0);

	अगर (np)
		kमुक्त(da7219->clk_hw_data);

	वापस ret;
पूर्ण

अटल व्योम da7219_मुक्त_dai_clks(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा device_node *np = component->dev->of_node;
	पूर्णांक i;

	अगर (np)
		of_clk_del_provider(np);

	क्रम (i = DA7219_DAI_NUM_CLKS - 1; i >= 0; --i) अणु
		अगर (da7219->dai_clks_lookup[i])
			clkdev_drop(da7219->dai_clks_lookup[i]);

		clk_hw_unरेजिस्टर(&da7219->dai_clks_hw[i]);
	पूर्ण

	अगर (np)
		kमुक्त(da7219->clk_hw_data);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक da7219_रेजिस्टर_dai_clks(काष्ठा snd_soc_component *component)
अणु
	वापस 0;
पूर्ण

अटल व्योम da7219_मुक्त_dai_clks(काष्ठा snd_soc_component *component) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_COMMON_CLK */

अटल व्योम da7219_handle_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_pdata *pdata = da7219->pdata;

	अगर (pdata) अणु
		u8 micbias_lvl = 0;

		da7219->wakeup_source = pdata->wakeup_source;

		/* Mic Bias voltages */
		चयन (pdata->micbias_lvl) अणु
		हाल DA7219_MICBIAS_1_6V:
		हाल DA7219_MICBIAS_1_8V:
		हाल DA7219_MICBIAS_2_0V:
		हाल DA7219_MICBIAS_2_2V:
		हाल DA7219_MICBIAS_2_4V:
		हाल DA7219_MICBIAS_2_6V:
			micbias_lvl |= (pdata->micbias_lvl <<
					DA7219_MICBIAS1_LEVEL_SHIFT);
			अवरोध;
		पूर्ण

		snd_soc_component_ग_लिखो(component, DA7219_MICBIAS_CTRL, micbias_lvl);

		/*
		 * Calculate delay required to compensate क्रम DC offset in
		 * Mic PGA, based on Mic Bias voltage.
		 */
		da7219->mic_pga_delay =  DA7219_MIC_PGA_BASE_DELAY +
					(pdata->micbias_lvl *
					 DA7219_MIC_PGA_OFFSET_DELAY);

		/* Mic */
		चयन (pdata->mic_amp_in_sel) अणु
		हाल DA7219_MIC_AMP_IN_SEL_DIFF:
		हाल DA7219_MIC_AMP_IN_SEL_SE_P:
		हाल DA7219_MIC_AMP_IN_SEL_SE_N:
			snd_soc_component_ग_लिखो(component, DA7219_MIC_1_SELECT,
				      pdata->mic_amp_in_sel);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Regmap configs
 */

अटल काष्ठा reg_शेष da7219_reg_शेषs[] = अणु
	अणु DA7219_MIC_1_SELECT, 0x00 पूर्ण,
	अणु DA7219_CIF_TIMEOUT_CTRL, 0x01 पूर्ण,
	अणु DA7219_SR_24_48, 0x00 पूर्ण,
	अणु DA7219_SR, 0x0A पूर्ण,
	अणु DA7219_CIF_I2C_ADDR_CFG, 0x02 पूर्ण,
	अणु DA7219_PLL_CTRL, 0x10 पूर्ण,
	अणु DA7219_PLL_FRAC_TOP, 0x00 पूर्ण,
	अणु DA7219_PLL_FRAC_BOT, 0x00 पूर्ण,
	अणु DA7219_PLL_INTEGER, 0x20 पूर्ण,
	अणु DA7219_DIG_ROUTING_DAI, 0x10 पूर्ण,
	अणु DA7219_DAI_CLK_MODE, 0x01 पूर्ण,
	अणु DA7219_DAI_CTRL, 0x28 पूर्ण,
	अणु DA7219_DAI_TDM_CTRL, 0x40 पूर्ण,
	अणु DA7219_DIG_ROUTING_DAC, 0x32 पूर्ण,
	अणु DA7219_DAI_OFFSET_LOWER, 0x00 पूर्ण,
	अणु DA7219_DAI_OFFSET_UPPER, 0x00 पूर्ण,
	अणु DA7219_REFERENCES, 0x08 पूर्ण,
	अणु DA7219_MIXIN_L_SELECT, 0x00 पूर्ण,
	अणु DA7219_MIXIN_L_GAIN, 0x03 पूर्ण,
	अणु DA7219_ADC_L_GAIN, 0x6F पूर्ण,
	अणु DA7219_ADC_FILTERS1, 0x80 पूर्ण,
	अणु DA7219_MIC_1_GAIN, 0x01 पूर्ण,
	अणु DA7219_SIDETONE_CTRL, 0x40 पूर्ण,
	अणु DA7219_SIDETONE_GAIN, 0x0E पूर्ण,
	अणु DA7219_DROUTING_ST_OUTFILT_1L, 0x01 पूर्ण,
	अणु DA7219_DROUTING_ST_OUTFILT_1R, 0x02 पूर्ण,
	अणु DA7219_DAC_FILTERS5, 0x00 पूर्ण,
	अणु DA7219_DAC_FILTERS2, 0x88 पूर्ण,
	अणु DA7219_DAC_FILTERS3, 0x88 पूर्ण,
	अणु DA7219_DAC_FILTERS4, 0x08 पूर्ण,
	अणु DA7219_DAC_FILTERS1, 0x80 पूर्ण,
	अणु DA7219_DAC_L_GAIN, 0x6F पूर्ण,
	अणु DA7219_DAC_R_GAIN, 0x6F पूर्ण,
	अणु DA7219_CP_CTRL, 0x20 पूर्ण,
	अणु DA7219_HP_L_GAIN, 0x39 पूर्ण,
	अणु DA7219_HP_R_GAIN, 0x39 पूर्ण,
	अणु DA7219_MIXOUT_L_SELECT, 0x00 पूर्ण,
	अणु DA7219_MIXOUT_R_SELECT, 0x00 पूर्ण,
	अणु DA7219_MICBIAS_CTRL, 0x03 पूर्ण,
	अणु DA7219_MIC_1_CTRL, 0x40 पूर्ण,
	अणु DA7219_MIXIN_L_CTRL, 0x40 पूर्ण,
	अणु DA7219_ADC_L_CTRL, 0x40 पूर्ण,
	अणु DA7219_DAC_L_CTRL, 0x40 पूर्ण,
	अणु DA7219_DAC_R_CTRL, 0x40 पूर्ण,
	अणु DA7219_HP_L_CTRL, 0x40 पूर्ण,
	अणु DA7219_HP_R_CTRL, 0x40 पूर्ण,
	अणु DA7219_MIXOUT_L_CTRL, 0x10 पूर्ण,
	अणु DA7219_MIXOUT_R_CTRL, 0x10 पूर्ण,
	अणु DA7219_CHIP_ID1, 0x23 पूर्ण,
	अणु DA7219_CHIP_ID2, 0x93 पूर्ण,
	अणु DA7219_IO_CTRL, 0x00 पूर्ण,
	अणु DA7219_GAIN_RAMP_CTRL, 0x00 पूर्ण,
	अणु DA7219_PC_COUNT, 0x02 पूर्ण,
	अणु DA7219_CP_VOL_THRESHOLD1, 0x0E पूर्ण,
	अणु DA7219_DIG_CTRL, 0x00 पूर्ण,
	अणु DA7219_ALC_CTRL2, 0x00 पूर्ण,
	अणु DA7219_ALC_CTRL3, 0x00 पूर्ण,
	अणु DA7219_ALC_NOISE, 0x3F पूर्ण,
	अणु DA7219_ALC_TARGET_MIN, 0x3F पूर्ण,
	अणु DA7219_ALC_TARGET_MAX, 0x00 पूर्ण,
	अणु DA7219_ALC_GAIN_LIMITS, 0xFF पूर्ण,
	अणु DA7219_ALC_ANA_GAIN_LIMITS, 0x71 पूर्ण,
	अणु DA7219_ALC_ANTICLIP_CTRL, 0x00 पूर्ण,
	अणु DA7219_ALC_ANTICLIP_LEVEL, 0x00 पूर्ण,
	अणु DA7219_DAC_NG_SETUP_TIME, 0x00 पूर्ण,
	अणु DA7219_DAC_NG_OFF_THRESH, 0x00 पूर्ण,
	अणु DA7219_DAC_NG_ON_THRESH, 0x00 पूर्ण,
	अणु DA7219_DAC_NG_CTRL, 0x00 पूर्ण,
	अणु DA7219_TONE_GEN_CFG1, 0x00 पूर्ण,
	अणु DA7219_TONE_GEN_CFG2, 0x00 पूर्ण,
	अणु DA7219_TONE_GEN_CYCLES, 0x00 पूर्ण,
	अणु DA7219_TONE_GEN_FREQ1_L, 0x55 पूर्ण,
	अणु DA7219_TONE_GEN_FREQ1_U, 0x15 पूर्ण,
	अणु DA7219_TONE_GEN_FREQ2_L, 0x00 पूर्ण,
	अणु DA7219_TONE_GEN_FREQ2_U, 0x40 पूर्ण,
	अणु DA7219_TONE_GEN_ON_PER, 0x02 पूर्ण,
	अणु DA7219_TONE_GEN_OFF_PER, 0x01 पूर्ण,
	अणु DA7219_ACCDET_IRQ_MASK_A, 0x00 पूर्ण,
	अणु DA7219_ACCDET_IRQ_MASK_B, 0x00 पूर्ण,
	अणु DA7219_ACCDET_CONFIG_1, 0xD6 पूर्ण,
	अणु DA7219_ACCDET_CONFIG_2, 0x34 पूर्ण,
	अणु DA7219_ACCDET_CONFIG_3, 0x0A पूर्ण,
	अणु DA7219_ACCDET_CONFIG_4, 0x16 पूर्ण,
	अणु DA7219_ACCDET_CONFIG_5, 0x21 पूर्ण,
	अणु DA7219_ACCDET_CONFIG_6, 0x3E पूर्ण,
	अणु DA7219_ACCDET_CONFIG_7, 0x01 पूर्ण,
	अणु DA7219_SYSTEM_ACTIVE, 0x00 पूर्ण,
पूर्ण;

अटल bool da7219_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA7219_MIC_1_GAIN_STATUS:
	हाल DA7219_MIXIN_L_GAIN_STATUS:
	हाल DA7219_ADC_L_GAIN_STATUS:
	हाल DA7219_DAC_L_GAIN_STATUS:
	हाल DA7219_DAC_R_GAIN_STATUS:
	हाल DA7219_HP_L_GAIN_STATUS:
	हाल DA7219_HP_R_GAIN_STATUS:
	हाल DA7219_CIF_CTRL:
	हाल DA7219_PLL_SRM_STS:
	हाल DA7219_ALC_CTRL1:
	हाल DA7219_SYSTEM_MODES_INPUT:
	हाल DA7219_SYSTEM_MODES_OUTPUT:
	हाल DA7219_ALC_OFFSET_AUTO_M_L:
	हाल DA7219_ALC_OFFSET_AUTO_U_L:
	हाल DA7219_TONE_GEN_CFG1:
	हाल DA7219_ACCDET_STATUS_A:
	हाल DA7219_ACCDET_STATUS_B:
	हाल DA7219_ACCDET_IRQ_EVENT_A:
	हाल DA7219_ACCDET_IRQ_EVENT_B:
	हाल DA7219_ACCDET_CONFIG_8:
	हाल DA7219_SYSTEM_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config da7219_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = DA7219_SYSTEM_ACTIVE,
	.reg_शेषs = da7219_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(da7219_reg_शेषs),
	.अस्थिर_reg = da7219_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा reg_sequence da7219_rev_aa_patch[] = अणु
	अणु DA7219_REFERENCES, 0x08 पूर्ण,
पूर्ण;

अटल पूर्णांक da7219_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक प्रणाली_active, प्रणाली_status, rev;
	u8 io_voltage_lvl;
	पूर्णांक i, ret;

	da7219->component = component;
	mutex_init(&da7219->ctrl_lock);
	mutex_init(&da7219->pll_lock);

	/* Regulator configuration */
	ret = da7219_handle_supplies(component, &io_voltage_lvl);
	अगर (ret)
		वापस ret;

	regcache_cache_bypass(da7219->regmap, true);

	/* Disable audio paths अगर still active from previous start */
	regmap_पढ़ो(da7219->regmap, DA7219_SYSTEM_ACTIVE, &प्रणाली_active);
	अगर (प्रणाली_active) अणु
		regmap_ग_लिखो(da7219->regmap, DA7219_GAIN_RAMP_CTRL,
			     DA7219_GAIN_RAMP_RATE_NOMINAL);
		regmap_ग_लिखो(da7219->regmap, DA7219_SYSTEM_MODES_INPUT, 0x00);
		regmap_ग_लिखो(da7219->regmap, DA7219_SYSTEM_MODES_OUTPUT, 0x01);

		क्रम (i = 0; i < DA7219_SYS_STAT_CHECK_RETRIES; ++i) अणु
			regmap_पढ़ो(da7219->regmap, DA7219_SYSTEM_STATUS,
				    &प्रणाली_status);
			अगर (!प्रणाली_status)
				अवरोध;

			msleep(DA7219_SYS_STAT_CHECK_DELAY);
		पूर्ण
	पूर्ण

	/* Soft reset component */
	regmap_ग_लिखो_bits(da7219->regmap, DA7219_ACCDET_CONFIG_1,
			  DA7219_ACCDET_EN_MASK, 0);
	regmap_ग_लिखो_bits(da7219->regmap, DA7219_CIF_CTRL,
			  DA7219_CIF_REG_SOFT_RESET_MASK,
			  DA7219_CIF_REG_SOFT_RESET_MASK);
	regmap_ग_लिखो_bits(da7219->regmap, DA7219_SYSTEM_ACTIVE,
			  DA7219_SYSTEM_ACTIVE_MASK, 0);
	regmap_ग_लिखो_bits(da7219->regmap, DA7219_SYSTEM_ACTIVE,
			  DA7219_SYSTEM_ACTIVE_MASK, 1);

	regcache_cache_bypass(da7219->regmap, false);
	regmap_reinit_cache(da7219->regmap, &da7219_regmap_config);

	/* Update IO voltage level range based on supply level */
	snd_soc_component_ग_लिखो(component, DA7219_IO_CTRL, io_voltage_lvl);

	ret = regmap_पढ़ो(da7219->regmap, DA7219_CHIP_REVISION, &rev);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to read chip revision: %d\n", ret);
		जाओ err_disable_reg;
	पूर्ण

	चयन (rev & DA7219_CHIP_MINOR_MASK) अणु
	हाल 0:
		ret = regmap_रेजिस्टर_patch(da7219->regmap, da7219_rev_aa_patch,
					    ARRAY_SIZE(da7219_rev_aa_patch));
		अगर (ret) अणु
			dev_err(component->dev, "Failed to register AA patch: %d\n",
				ret);
			जाओ err_disable_reg;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Handle DT/ACPI/Platक्रमm data */
	da7219_handle_pdata(component);

	/* Check अगर MCLK provided */
	da7219->mclk = clk_get(component->dev, "mclk");
	अगर (IS_ERR(da7219->mclk)) अणु
		अगर (PTR_ERR(da7219->mclk) != -ENOENT) अणु
			ret = PTR_ERR(da7219->mclk);
			जाओ err_disable_reg;
		पूर्ण अन्यथा अणु
			da7219->mclk = शून्य;
		पूर्ण
	पूर्ण

	/* Register CCF DAI घड़ी control */
	ret = da7219_रेजिस्टर_dai_clks(component);
	अगर (ret)
		जाओ err_put_clk;

	/* Default PC counter to मुक्त-running */
	snd_soc_component_update_bits(component, DA7219_PC_COUNT, DA7219_PC_FREERUN_MASK,
			    DA7219_PC_FREERUN_MASK);

	/* Default gain ramping */
	snd_soc_component_update_bits(component, DA7219_MIXIN_L_CTRL,
			    DA7219_MIXIN_L_AMP_RAMP_EN_MASK,
			    DA7219_MIXIN_L_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_ADC_L_CTRL, DA7219_ADC_L_RAMP_EN_MASK,
			    DA7219_ADC_L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_DAC_L_CTRL, DA7219_DAC_L_RAMP_EN_MASK,
			    DA7219_DAC_L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_DAC_R_CTRL, DA7219_DAC_R_RAMP_EN_MASK,
			    DA7219_DAC_R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
			    DA7219_HP_L_AMP_RAMP_EN_MASK,
			    DA7219_HP_L_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
			    DA7219_HP_R_AMP_RAMP_EN_MASK,
			    DA7219_HP_R_AMP_RAMP_EN_MASK);

	/* Default minimum gain on HP to aव्योम pops during DAPM sequencing */
	snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
			    DA7219_HP_L_AMP_MIN_GAIN_EN_MASK,
			    DA7219_HP_L_AMP_MIN_GAIN_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
			    DA7219_HP_R_AMP_MIN_GAIN_EN_MASK,
			    DA7219_HP_R_AMP_MIN_GAIN_EN_MASK);

	/* Default infinite tone gen, start/stop by Kcontrol */
	snd_soc_component_ग_लिखो(component, DA7219_TONE_GEN_CYCLES, DA7219_BEEP_CYCLES_MASK);

	/* Initialise AAD block */
	ret = da7219_aad_init(component);
	अगर (ret)
		जाओ err_मुक्त_dai_clks;

	वापस 0;

err_मुक्त_dai_clks:
	da7219_मुक्त_dai_clks(component);

err_put_clk:
	clk_put(da7219->mclk);

err_disable_reg:
	regulator_bulk_disable(DA7219_NUM_SUPPLIES, da7219->supplies);
	regulator_bulk_मुक्त(DA7219_NUM_SUPPLIES, da7219->supplies);

	वापस ret;
पूर्ण

अटल व्योम da7219_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	da7219_aad_निकास(component);

	da7219_मुक्त_dai_clks(component);
	clk_put(da7219->mclk);

	/* Supplies */
	regulator_bulk_disable(DA7219_NUM_SUPPLIES, da7219->supplies);
	regulator_bulk_मुक्त(DA7219_NUM_SUPPLIES, da7219->supplies);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक da7219_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	/* Suspend AAD अगर we're not a wake-up source */
	अगर (!da7219->wakeup_source)
		da7219_aad_suspend(component);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Resume AAD अगर previously suspended */
	अगर (!da7219->wakeup_source)
		da7219_aad_resume(component);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा da7219_suspend शून्य
#घोषणा da7219_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_da7219 = अणु
	.probe			= da7219_probe,
	.हटाओ			= da7219_हटाओ,
	.suspend		= da7219_suspend,
	.resume			= da7219_resume,
	.set_bias_level		= da7219_set_bias_level,
	.controls		= da7219_snd_controls,
	.num_controls		= ARRAY_SIZE(da7219_snd_controls),
	.dapm_widमाला_लो		= da7219_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(da7219_dapm_widमाला_लो),
	.dapm_routes		= da7219_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(da7219_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;


/*
 * I2C layer
 */

अटल पूर्णांक da7219_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा da7219_priv *da7219;
	पूर्णांक ret;

	da7219 = devm_kzalloc(dev, माप(काष्ठा da7219_priv),
			      GFP_KERNEL);
	अगर (!da7219)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, da7219);

	da7219->regmap = devm_regmap_init_i2c(i2c, &da7219_regmap_config);
	अगर (IS_ERR(da7219->regmap)) अणु
		ret = PTR_ERR(da7219->regmap);
		dev_err(dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Retrieve DT/ACPI/Platक्रमm data */
	da7219->pdata = dev_get_platdata(dev);
	अगर (!da7219->pdata)
		da7219->pdata = da7219_fw_to_pdata(dev);

	/* AAD */
	ret = da7219_aad_probe(i2c);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_da7219,
					      &da7219_dai, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register da7219 component: %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक da7219_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da7219_i2c_id[] = अणु
	अणु "da7219", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da7219_i2c_id);

अटल काष्ठा i2c_driver da7219_i2c_driver = अणु
	.driver = अणु
		.name = "da7219",
		.of_match_table = of_match_ptr(da7219_of_match),
		.acpi_match_table = ACPI_PTR(da7219_acpi_match),
	पूर्ण,
	.probe		= da7219_i2c_probe,
	.हटाओ		= da7219_i2c_हटाओ,
	.id_table	= da7219_i2c_id,
पूर्ण;

module_i2c_driver(da7219_i2c_driver);

MODULE_DESCRIPTION("ASoC DA7219 Codec Driver");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
