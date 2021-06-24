<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * da7218.c - DA7218 ALSA SoC Codec Driver
 *
 * Copyright (c) 2015 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
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
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <sound/da7218.h>
#समावेश "da7218.h"


/*
 * TLVs and Enums
 */

/* Input TLVs */
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_mic_gain_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_mixin_gain_tlv, -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_in_dig_gain_tlv, -8325, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_ags_trigger_tlv, -9000, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_ags_att_max_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_alc_threshold_tlv, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_alc_gain_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_alc_ana_gain_tlv, 0, 600, 0);

/* Input/Output TLVs */
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_dmix_gain_tlv, -4200, 150, 0);

/* Output TLVs */
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_dgs_trigger_tlv, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_dgs_anticlip_tlv, -4200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_dgs_संकेत_tlv, -9000, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_out_eq_band_tlv, -1050, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_out_dig_gain_tlv, -8325, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_dac_ng_threshold_tlv, -10200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_mixout_gain_tlv, -100, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(da7218_hp_gain_tlv, -5700, 150, 0);

/* Input Enums */
अटल स्थिर अक्षर * स्थिर da7218_alc_attack_rate_txt[] = अणु
	"7.33/fs", "14.66/fs", "29.32/fs", "58.64/fs", "117.3/fs", "234.6/fs",
	"469.1/fs", "938.2/fs", "1876/fs", "3753/fs", "7506/fs", "15012/fs",
	"30024/fs",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_alc_attack_rate =
	SOC_ENUM_SINGLE(DA7218_ALC_CTRL2, DA7218_ALC_ATTACK_SHIFT,
			DA7218_ALC_ATTACK_MAX, da7218_alc_attack_rate_txt);

अटल स्थिर अक्षर * स्थिर da7218_alc_release_rate_txt[] = अणु
	"28.66/fs", "57.33/fs", "114.6/fs", "229.3/fs", "458.6/fs", "917.1/fs",
	"1834/fs", "3668/fs", "7337/fs", "14674/fs", "29348/fs",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_alc_release_rate =
	SOC_ENUM_SINGLE(DA7218_ALC_CTRL2, DA7218_ALC_RELEASE_SHIFT,
			DA7218_ALC_RELEASE_MAX, da7218_alc_release_rate_txt);

अटल स्थिर अक्षर * स्थिर da7218_alc_hold_समय_प्रकारxt[] = अणु
	"62/fs", "124/fs", "248/fs", "496/fs", "992/fs", "1984/fs", "3968/fs",
	"7936/fs", "15872/fs", "31744/fs", "63488/fs", "126976/fs",
	"253952/fs", "507904/fs", "1015808/fs", "2031616/fs"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_alc_hold_समय =
	SOC_ENUM_SINGLE(DA7218_ALC_CTRL3, DA7218_ALC_HOLD_SHIFT,
			DA7218_ALC_HOLD_MAX, da7218_alc_hold_समय_प्रकारxt);

अटल स्थिर अक्षर * स्थिर da7218_alc_anticlip_step_txt[] = अणु
	"0.034dB/fs", "0.068dB/fs", "0.136dB/fs", "0.272dB/fs",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_alc_anticlip_step =
	SOC_ENUM_SINGLE(DA7218_ALC_ANTICLIP_CTRL,
			DA7218_ALC_ANTICLIP_STEP_SHIFT,
			DA7218_ALC_ANTICLIP_STEP_MAX,
			da7218_alc_anticlip_step_txt);

अटल स्थिर अक्षर * स्थिर da7218_पूर्णांकeg_rate_txt[] = अणु
	"1/4", "1/16", "1/256", "1/65536"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_पूर्णांकeg_attack_rate =
	SOC_ENUM_SINGLE(DA7218_ENV_TRACK_CTRL, DA7218_INTEG_ATTACK_SHIFT,
			DA7218_INTEG_MAX, da7218_पूर्णांकeg_rate_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7218_पूर्णांकeg_release_rate =
	SOC_ENUM_SINGLE(DA7218_ENV_TRACK_CTRL, DA7218_INTEG_RELEASE_SHIFT,
			DA7218_INTEG_MAX, da7218_पूर्णांकeg_rate_txt);

/* Input/Output Enums */
अटल स्थिर अक्षर * स्थिर da7218_gain_ramp_rate_txt[] = अणु
	"Nominal Rate * 8", "Nominal Rate", "Nominal Rate / 8",
	"Nominal Rate / 16",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_gain_ramp_rate =
	SOC_ENUM_SINGLE(DA7218_GAIN_RAMP_CTRL, DA7218_GAIN_RAMP_RATE_SHIFT,
			DA7218_GAIN_RAMP_RATE_MAX, da7218_gain_ramp_rate_txt);

अटल स्थिर अक्षर * स्थिर da7218_hpf_mode_txt[] = अणु
	"Disabled", "Audio", "Voice",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक da7218_hpf_mode_val[] = अणु
	DA7218_HPF_DISABLED, DA7218_HPF_AUDIO_EN, DA7218_HPF_VOICE_EN,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_in1_hpf_mode =
	SOC_VALUE_ENUM_SINGLE(DA7218_IN_1_HPF_FILTER_CTRL,
			      DA7218_HPF_MODE_SHIFT, DA7218_HPF_MODE_MASK,
			      DA7218_HPF_MODE_MAX, da7218_hpf_mode_txt,
			      da7218_hpf_mode_val);

अटल स्थिर काष्ठा soc_क्रमागत da7218_in2_hpf_mode =
	SOC_VALUE_ENUM_SINGLE(DA7218_IN_2_HPF_FILTER_CTRL,
			      DA7218_HPF_MODE_SHIFT, DA7218_HPF_MODE_MASK,
			      DA7218_HPF_MODE_MAX, da7218_hpf_mode_txt,
			      da7218_hpf_mode_val);

अटल स्थिर काष्ठा soc_क्रमागत da7218_out1_hpf_mode =
	SOC_VALUE_ENUM_SINGLE(DA7218_OUT_1_HPF_FILTER_CTRL,
			      DA7218_HPF_MODE_SHIFT, DA7218_HPF_MODE_MASK,
			      DA7218_HPF_MODE_MAX, da7218_hpf_mode_txt,
			      da7218_hpf_mode_val);

अटल स्थिर अक्षर * स्थिर da7218_audio_hpf_corner_txt[] = अणु
	"2Hz", "4Hz", "8Hz", "16Hz",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_in1_audio_hpf_corner =
	SOC_ENUM_SINGLE(DA7218_IN_1_HPF_FILTER_CTRL,
			DA7218_IN_1_AUDIO_HPF_CORNER_SHIFT,
			DA7218_AUDIO_HPF_CORNER_MAX,
			da7218_audio_hpf_corner_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7218_in2_audio_hpf_corner =
	SOC_ENUM_SINGLE(DA7218_IN_2_HPF_FILTER_CTRL,
			DA7218_IN_2_AUDIO_HPF_CORNER_SHIFT,
			DA7218_AUDIO_HPF_CORNER_MAX,
			da7218_audio_hpf_corner_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7218_out1_audio_hpf_corner =
	SOC_ENUM_SINGLE(DA7218_OUT_1_HPF_FILTER_CTRL,
			DA7218_OUT_1_AUDIO_HPF_CORNER_SHIFT,
			DA7218_AUDIO_HPF_CORNER_MAX,
			da7218_audio_hpf_corner_txt);

अटल स्थिर अक्षर * स्थिर da7218_voice_hpf_corner_txt[] = अणु
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_in1_voice_hpf_corner =
	SOC_ENUM_SINGLE(DA7218_IN_1_HPF_FILTER_CTRL,
			DA7218_IN_1_VOICE_HPF_CORNER_SHIFT,
			DA7218_VOICE_HPF_CORNER_MAX,
			da7218_voice_hpf_corner_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7218_in2_voice_hpf_corner =
	SOC_ENUM_SINGLE(DA7218_IN_2_HPF_FILTER_CTRL,
			DA7218_IN_2_VOICE_HPF_CORNER_SHIFT,
			DA7218_VOICE_HPF_CORNER_MAX,
			da7218_voice_hpf_corner_txt);

अटल स्थिर काष्ठा soc_क्रमागत da7218_out1_voice_hpf_corner =
	SOC_ENUM_SINGLE(DA7218_OUT_1_HPF_FILTER_CTRL,
			DA7218_OUT_1_VOICE_HPF_CORNER_SHIFT,
			DA7218_VOICE_HPF_CORNER_MAX,
			da7218_voice_hpf_corner_txt);

अटल स्थिर अक्षर * स्थिर da7218_tonegen_dपंचांगf_key_txt[] = अणु
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D",
	"*", "#"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_tonegen_dपंचांगf_key =
	SOC_ENUM_SINGLE(DA7218_TONE_GEN_CFG1, DA7218_DTMF_REG_SHIFT,
			DA7218_DTMF_REG_MAX, da7218_tonegen_dपंचांगf_key_txt);

अटल स्थिर अक्षर * स्थिर da7218_tonegen_swg_sel_txt[] = अणु
	"Sum", "SWG1", "SWG2", "SWG1_1-Cos"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_tonegen_swg_sel =
	SOC_ENUM_SINGLE(DA7218_TONE_GEN_CFG2, DA7218_SWG_SEL_SHIFT,
			DA7218_SWG_SEL_MAX, da7218_tonegen_swg_sel_txt);

/* Output Enums */
अटल स्थिर अक्षर * स्थिर da7218_dgs_rise_coeff_txt[] = अणु
	"1/1", "1/16", "1/64", "1/256", "1/1024", "1/4096", "1/16384",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_dgs_rise_coeff =
	SOC_ENUM_SINGLE(DA7218_DGS_RISE_FALL, DA7218_DGS_RISE_COEFF_SHIFT,
			DA7218_DGS_RISE_COEFF_MAX, da7218_dgs_rise_coeff_txt);

अटल स्थिर अक्षर * स्थिर da7218_dgs_fall_coeff_txt[] = अणु
	"1/4", "1/16", "1/64", "1/256", "1/1024", "1/4096", "1/16384", "1/65536",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_dgs_fall_coeff =
	SOC_ENUM_SINGLE(DA7218_DGS_RISE_FALL, DA7218_DGS_FALL_COEFF_SHIFT,
			DA7218_DGS_FALL_COEFF_MAX, da7218_dgs_fall_coeff_txt);

अटल स्थिर अक्षर * स्थिर da7218_dac_ng_setup_समय_प्रकारxt[] = अणु
	"256 Samples", "512 Samples", "1024 Samples", "2048 Samples"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_dac_ng_setup_समय =
	SOC_ENUM_SINGLE(DA7218_DAC_NG_SETUP_TIME,
			DA7218_DAC_NG_SETUP_TIME_SHIFT,
			DA7218_DAC_NG_SETUP_TIME_MAX,
			da7218_dac_ng_setup_समय_प्रकारxt);

अटल स्थिर अक्षर * स्थिर da7218_dac_ng_rampup_txt[] = अणु
	"0.22ms/dB", "0.0138ms/dB"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_dac_ng_rampup_rate =
	SOC_ENUM_SINGLE(DA7218_DAC_NG_SETUP_TIME,
			DA7218_DAC_NG_RAMPUP_RATE_SHIFT,
			DA7218_DAC_NG_RAMPUP_RATE_MAX,
			da7218_dac_ng_rampup_txt);

अटल स्थिर अक्षर * स्थिर da7218_dac_ng_rampकरोwn_txt[] = अणु
	"0.88ms/dB", "14.08ms/dB"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_dac_ng_rampकरोwn_rate =
	SOC_ENUM_SINGLE(DA7218_DAC_NG_SETUP_TIME,
			DA7218_DAC_NG_RAMPDN_RATE_SHIFT,
			DA7218_DAC_NG_RAMPDN_RATE_MAX,
			da7218_dac_ng_rampकरोwn_txt);

अटल स्थिर अक्षर * स्थिर da7218_cp_mchange_txt[] = अणु
	"Largest Volume", "DAC Volume", "Signal Magnitude"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक da7218_cp_mchange_val[] = अणु
	DA7218_CP_MCHANGE_LARGEST_VOL, DA7218_CP_MCHANGE_DAC_VOL,
	DA7218_CP_MCHANGE_SIG_MAG
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_cp_mchange =
	SOC_VALUE_ENUM_SINGLE(DA7218_CP_CTRL, DA7218_CP_MCHANGE_SHIFT,
			      DA7218_CP_MCHANGE_REL_MASK, DA7218_CP_MCHANGE_MAX,
			      da7218_cp_mchange_txt, da7218_cp_mchange_val);

अटल स्थिर अक्षर * स्थिर da7218_cp_fcontrol_txt[] = अणु
	"1MHz", "500KHz", "250KHz", "125KHz", "63KHz", "0KHz"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_cp_fcontrol =
	SOC_ENUM_SINGLE(DA7218_CP_DELAY, DA7218_CP_FCONTROL_SHIFT,
			DA7218_CP_FCONTROL_MAX, da7218_cp_fcontrol_txt);

अटल स्थिर अक्षर * स्थिर da7218_cp_tau_delay_txt[] = अणु
	"0ms", "2ms", "4ms", "16ms", "64ms", "128ms", "256ms", "512ms"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_cp_tau_delay =
	SOC_ENUM_SINGLE(DA7218_CP_DELAY, DA7218_CP_TAU_DELAY_SHIFT,
			DA7218_CP_TAU_DELAY_MAX, da7218_cp_tau_delay_txt);

/*
 * Control Functions
 */

/* ALC */
अटल व्योम da7218_alc_calib(काष्ठा snd_soc_component *component)
अणु
	u8 mic_1_ctrl, mic_2_ctrl;
	u8 mixin_1_ctrl, mixin_2_ctrl;
	u8 in_1l_filt_ctrl, in_1r_filt_ctrl, in_2l_filt_ctrl, in_2r_filt_ctrl;
	u8 in_1_hpf_ctrl, in_2_hpf_ctrl;
	u8 calib_ctrl;
	पूर्णांक i = 0;
	bool calibrated = false;

	/* Save current state of MIC control रेजिस्टरs */
	mic_1_ctrl = snd_soc_component_पढ़ो(component, DA7218_MIC_1_CTRL);
	mic_2_ctrl = snd_soc_component_पढ़ो(component, DA7218_MIC_2_CTRL);

	/* Save current state of input mixer control रेजिस्टरs */
	mixin_1_ctrl = snd_soc_component_पढ़ो(component, DA7218_MIXIN_1_CTRL);
	mixin_2_ctrl = snd_soc_component_पढ़ो(component, DA7218_MIXIN_2_CTRL);

	/* Save current state of input filter control रेजिस्टरs */
	in_1l_filt_ctrl = snd_soc_component_पढ़ो(component, DA7218_IN_1L_FILTER_CTRL);
	in_1r_filt_ctrl = snd_soc_component_पढ़ो(component, DA7218_IN_1R_FILTER_CTRL);
	in_2l_filt_ctrl = snd_soc_component_पढ़ो(component, DA7218_IN_2L_FILTER_CTRL);
	in_2r_filt_ctrl = snd_soc_component_पढ़ो(component, DA7218_IN_2R_FILTER_CTRL);

	/* Save current state of input HPF control रेजिस्टरs */
	in_1_hpf_ctrl = snd_soc_component_पढ़ो(component, DA7218_IN_1_HPF_FILTER_CTRL);
	in_2_hpf_ctrl = snd_soc_component_पढ़ो(component, DA7218_IN_2_HPF_FILTER_CTRL);

	/* Enable then Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7218_MIC_1_CTRL, DA7218_MIC_1_AMP_EN_MASK,
			    DA7218_MIC_1_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIC_2_CTRL, DA7218_MIC_2_AMP_EN_MASK,
			    DA7218_MIC_2_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIC_1_CTRL,
			    DA7218_MIC_1_AMP_MUTE_EN_MASK,
			    DA7218_MIC_1_AMP_MUTE_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIC_2_CTRL,
			    DA7218_MIC_2_AMP_MUTE_EN_MASK,
			    DA7218_MIC_2_AMP_MUTE_EN_MASK);

	/* Enable input mixers unmuted */
	snd_soc_component_update_bits(component, DA7218_MIXIN_1_CTRL,
			    DA7218_MIXIN_1_AMP_EN_MASK |
			    DA7218_MIXIN_1_AMP_MUTE_EN_MASK,
			    DA7218_MIXIN_1_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIXIN_2_CTRL,
			    DA7218_MIXIN_2_AMP_EN_MASK |
			    DA7218_MIXIN_2_AMP_MUTE_EN_MASK,
			    DA7218_MIXIN_2_AMP_EN_MASK);

	/* Enable input filters unmuted */
	snd_soc_component_update_bits(component, DA7218_IN_1L_FILTER_CTRL,
			    DA7218_IN_1L_FILTER_EN_MASK |
			    DA7218_IN_1L_MUTE_EN_MASK,
			    DA7218_IN_1L_FILTER_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_1R_FILTER_CTRL,
			    DA7218_IN_1R_FILTER_EN_MASK |
			    DA7218_IN_1R_MUTE_EN_MASK,
			    DA7218_IN_1R_FILTER_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2L_FILTER_CTRL,
			    DA7218_IN_2L_FILTER_EN_MASK |
			    DA7218_IN_2L_MUTE_EN_MASK,
			    DA7218_IN_2L_FILTER_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2R_FILTER_CTRL,
			    DA7218_IN_2R_FILTER_EN_MASK |
			    DA7218_IN_2R_MUTE_EN_MASK,
			    DA7218_IN_2R_FILTER_EN_MASK);

	/*
	 * Make sure input HPFs voice mode is disabled, otherwise क्रम sampling
	 * rates above 32KHz the ADC संकेतs will be stopped and will cause
	 * calibration to lock up.
	 */
	snd_soc_component_update_bits(component, DA7218_IN_1_HPF_FILTER_CTRL,
			    DA7218_IN_1_VOICE_EN_MASK, 0);
	snd_soc_component_update_bits(component, DA7218_IN_2_HPF_FILTER_CTRL,
			    DA7218_IN_2_VOICE_EN_MASK, 0);

	/* Perक्रमm स्वतः calibration */
	snd_soc_component_update_bits(component, DA7218_CALIB_CTRL, DA7218_CALIB_AUTO_EN_MASK,
			    DA7218_CALIB_AUTO_EN_MASK);
	करो अणु
		calib_ctrl = snd_soc_component_पढ़ो(component, DA7218_CALIB_CTRL);
		अगर (calib_ctrl & DA7218_CALIB_AUTO_EN_MASK) अणु
			++i;
			usleep_range(DA7218_ALC_CALIB_DELAY_MIN,
				     DA7218_ALC_CALIB_DELAY_MAX);
		पूर्ण अन्यथा अणु
			calibrated = true;
		पूर्ण

	पूर्ण जबतक ((i < DA7218_ALC_CALIB_MAX_TRIES) && (!calibrated));

	/* If स्वतः calibration fails, disable DC offset, hybrid ALC */
	अगर ((!calibrated) || (calib_ctrl & DA7218_CALIB_OVERFLOW_MASK)) अणु
		dev_warn(component->dev,
			 "ALC auto calibration failed - %s\n",
			 (calibrated) ? "overflow" : "timeout");
		snd_soc_component_update_bits(component, DA7218_CALIB_CTRL,
				    DA7218_CALIB_OFFSET_EN_MASK, 0);
		snd_soc_component_update_bits(component, DA7218_ALC_CTRL1,
				    DA7218_ALC_SYNC_MODE_MASK, 0);

	पूर्ण अन्यथा अणु
		/* Enable DC offset cancellation */
		snd_soc_component_update_bits(component, DA7218_CALIB_CTRL,
				    DA7218_CALIB_OFFSET_EN_MASK,
				    DA7218_CALIB_OFFSET_EN_MASK);

		/* Enable ALC hybrid mode */
		snd_soc_component_update_bits(component, DA7218_ALC_CTRL1,
				    DA7218_ALC_SYNC_MODE_MASK,
				    DA7218_ALC_SYNC_MODE_CH1 |
				    DA7218_ALC_SYNC_MODE_CH2);
	पूर्ण

	/* Restore input HPF control रेजिस्टरs to original states */
	snd_soc_component_ग_लिखो(component, DA7218_IN_1_HPF_FILTER_CTRL, in_1_hpf_ctrl);
	snd_soc_component_ग_लिखो(component, DA7218_IN_2_HPF_FILTER_CTRL, in_2_hpf_ctrl);

	/* Restore input filter control रेजिस्टरs to original states */
	snd_soc_component_ग_लिखो(component, DA7218_IN_1L_FILTER_CTRL, in_1l_filt_ctrl);
	snd_soc_component_ग_लिखो(component, DA7218_IN_1R_FILTER_CTRL, in_1r_filt_ctrl);
	snd_soc_component_ग_लिखो(component, DA7218_IN_2L_FILTER_CTRL, in_2l_filt_ctrl);
	snd_soc_component_ग_लिखो(component, DA7218_IN_2R_FILTER_CTRL, in_2r_filt_ctrl);

	/* Restore input mixer control रेजिस्टरs to original state */
	snd_soc_component_ग_लिखो(component, DA7218_MIXIN_1_CTRL, mixin_1_ctrl);
	snd_soc_component_ग_लिखो(component, DA7218_MIXIN_2_CTRL, mixin_2_ctrl);

	/* Restore MIC control रेजिस्टरs to original states */
	snd_soc_component_ग_लिखो(component, DA7218_MIC_1_CTRL, mic_1_ctrl);
	snd_soc_component_ग_लिखो(component, DA7218_MIC_2_CTRL, mic_2_ctrl);
पूर्ण

अटल पूर्णांक da7218_mixin_gain_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);

	/*
	 * If ALC in operation and value of control has been updated,
	 * make sure calibrated offsets are updated.
	 */
	अगर ((ret == 1) && (da7218->alc_en))
		da7218_alc_calib(component);

	वापस ret;
पूर्ण

अटल पूर्णांक da7218_alc_sw_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक lvalue = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित पूर्णांक rvalue = ucontrol->value.पूर्णांकeger.value[1];
	अचिन्हित पूर्णांक lshअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	अचिन्हित पूर्णांक mask = (mc->max << lshअगरt) | (mc->max << rshअगरt);

	/* Force ALC offset calibration अगर enabling ALC */
	अगर ((lvalue || rvalue) && (!da7218->alc_en))
		da7218_alc_calib(component);

	/* Update bits to detail which channels are enabled/disabled */
	da7218->alc_en &= ~mask;
	da7218->alc_en |= (lvalue << lshअगरt) | (rvalue << rshअगरt);

	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण

/* ToneGen */
अटल पूर्णांक da7218_tonegen_freq_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mixer_ctrl =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mixer_ctrl->reg;
	u16 val;
	पूर्णांक ret;

	/*
	 * Frequency value spans two 8-bit रेजिस्टरs, lower then upper byte.
	 * Thereक्रमe we need to convert to host endianness here.
	 */
	ret = regmap_raw_पढ़ो(da7218->regmap, reg, &val, 2);
	अगर (ret)
		वापस ret;

	ucontrol->value.पूर्णांकeger.value[0] = le16_to_cpu(val);

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_tonegen_freq_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mixer_ctrl =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mixer_ctrl->reg;
	u16 val;

	/*
	 * Frequency value spans two 8-bit रेजिस्टरs, lower then upper byte.
	 * Thereक्रमe we need to convert to little endian here to align with
	 * HW रेजिस्टरs.
	 */
	val = cpu_to_le16(ucontrol->value.पूर्णांकeger.value[0]);

	वापस regmap_raw_ग_लिखो(da7218->regmap, reg, &val, 2);
पूर्ण

अटल पूर्णांक da7218_mic_lvl_det_sw_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mixer_ctrl =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	अचिन्हित पूर्णांक lvalue = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित पूर्णांक rvalue = ucontrol->value.पूर्णांकeger.value[1];
	अचिन्हित पूर्णांक lshअगरt = mixer_ctrl->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mixer_ctrl->rshअगरt;
	अचिन्हित पूर्णांक mask = (mixer_ctrl->max << lshअगरt) |
			    (mixer_ctrl->max << rshअगरt);
	da7218->mic_lvl_det_en &= ~mask;
	da7218->mic_lvl_det_en |= (lvalue << lshअगरt) | (rvalue << rshअगरt);

	/*
	 * Here we only enable the feature on paths which are alपढ़ोy
	 * घातered. If a channel is enabled here क्रम level detect, but that path
	 * isn't घातered, then the channel will actually be enabled when we करो
	 * घातer the path (IN_FILTER widget events). This handling aव्योमs
	 * unwanted level detect events.
	 */
	वापस snd_soc_component_ग_लिखो(component, mixer_ctrl->reg,
			     (da7218->in_filt_en & da7218->mic_lvl_det_en));
पूर्ण

अटल पूर्णांक da7218_mic_lvl_det_sw_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mixer_ctrl =
		(काष्ठा soc_mixer_control *) kcontrol->निजी_value;
	अचिन्हित पूर्णांक lshअगरt = mixer_ctrl->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mixer_ctrl->rshअगरt;
	अचिन्हित पूर्णांक lmask = (mixer_ctrl->max << lshअगरt);
	अचिन्हित पूर्णांक rmask = (mixer_ctrl->max << rshअगरt);

	ucontrol->value.पूर्णांकeger.value[0] =
		(da7218->mic_lvl_det_en & lmask) >> lshअगरt;
	ucontrol->value.पूर्णांकeger.value[1] =
		(da7218->mic_lvl_det_en & rmask) >> rshअगरt;

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_biquad_coeff_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *) kcontrol->निजी_value;

	/* Determine which BiQuads we're setting based on size of config data */
	चयन (bytes_ext->max) अणु
	हाल DA7218_OUT_1_BIQ_5STAGE_CFG_SIZE:
		स_नकल(ucontrol->value.bytes.data, da7218->biq_5stage_coeff,
		       bytes_ext->max);
		अवरोध;
	हाल DA7218_SIDETONE_BIQ_3STAGE_CFG_SIZE:
		स_नकल(ucontrol->value.bytes.data, da7218->stbiq_3stage_coeff,
		       bytes_ext->max);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_biquad_coeff_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *) kcontrol->निजी_value;
	u8 reg, out_filt1l;
	u8 cfg[DA7218_BIQ_CFG_SIZE];
	पूर्णांक i;

	/*
	 * Determine which BiQuads we're setting based on size of config data,
	 * and stored the data क्रम use by get function.
	 */
	चयन (bytes_ext->max) अणु
	हाल DA7218_OUT_1_BIQ_5STAGE_CFG_SIZE:
		reg = DA7218_OUT_1_BIQ_5STAGE_DATA;
		स_नकल(da7218->biq_5stage_coeff, ucontrol->value.bytes.data,
		       bytes_ext->max);
		अवरोध;
	हाल DA7218_SIDETONE_BIQ_3STAGE_CFG_SIZE:
		reg = DA7218_SIDETONE_BIQ_3STAGE_DATA;
		स_नकल(da7218->stbiq_3stage_coeff, ucontrol->value.bytes.data,
		       bytes_ext->max);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Make sure at least out filter1 enabled to allow programming */
	out_filt1l = snd_soc_component_पढ़ो(component, DA7218_OUT_1L_FILTER_CTRL);
	snd_soc_component_ग_लिखो(component, DA7218_OUT_1L_FILTER_CTRL,
		      out_filt1l | DA7218_OUT_1L_FILTER_EN_MASK);

	क्रम (i = 0; i < bytes_ext->max; ++i) अणु
		cfg[DA7218_BIQ_CFG_DATA] = ucontrol->value.bytes.data[i];
		cfg[DA7218_BIQ_CFG_ADDR] = i;
		regmap_raw_ग_लिखो(da7218->regmap, reg, cfg, DA7218_BIQ_CFG_SIZE);
	पूर्ण

	/* Restore filter to previous setting */
	snd_soc_component_ग_लिखो(component, DA7218_OUT_1L_FILTER_CTRL, out_filt1l);

	वापस 0;
पूर्ण


/*
 * KControls
 */

अटल स्थिर काष्ठा snd_kcontrol_new da7218_snd_controls[] = अणु
	/* Mics */
	SOC_SINGLE_TLV("Mic1 Volume", DA7218_MIC_1_GAIN,
		       DA7218_MIC_1_AMP_GAIN_SHIFT, DA7218_MIC_AMP_GAIN_MAX,
		       DA7218_NO_INVERT, da7218_mic_gain_tlv),
	SOC_SINGLE("Mic1 Switch", DA7218_MIC_1_CTRL,
		   DA7218_MIC_1_AMP_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE_TLV("Mic2 Volume", DA7218_MIC_2_GAIN,
		       DA7218_MIC_2_AMP_GAIN_SHIFT, DA7218_MIC_AMP_GAIN_MAX,
		       DA7218_NO_INVERT, da7218_mic_gain_tlv),
	SOC_SINGLE("Mic2 Switch", DA7218_MIC_2_CTRL,
		   DA7218_MIC_2_AMP_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),

	/* Mixer Input */
	SOC_SINGLE_EXT_TLV("Mixin1 Volume", DA7218_MIXIN_1_GAIN,
			   DA7218_MIXIN_1_AMP_GAIN_SHIFT,
			   DA7218_MIXIN_AMP_GAIN_MAX, DA7218_NO_INVERT,
			   snd_soc_get_volsw, da7218_mixin_gain_put,
			   da7218_mixin_gain_tlv),
	SOC_SINGLE("Mixin1 Switch", DA7218_MIXIN_1_CTRL,
		   DA7218_MIXIN_1_AMP_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE("Mixin1 Gain Ramp Switch", DA7218_MIXIN_1_CTRL,
		   DA7218_MIXIN_1_AMP_RAMP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("Mixin1 ZC Gain Switch", DA7218_MIXIN_1_CTRL,
		   DA7218_MIXIN_1_AMP_ZC_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE_EXT_TLV("Mixin2 Volume", DA7218_MIXIN_2_GAIN,
			   DA7218_MIXIN_2_AMP_GAIN_SHIFT,
			   DA7218_MIXIN_AMP_GAIN_MAX, DA7218_NO_INVERT,
			   snd_soc_get_volsw, da7218_mixin_gain_put,
			   da7218_mixin_gain_tlv),
	SOC_SINGLE("Mixin2 Switch", DA7218_MIXIN_2_CTRL,
		   DA7218_MIXIN_2_AMP_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE("Mixin2 Gain Ramp Switch", DA7218_MIXIN_2_CTRL,
		   DA7218_MIXIN_2_AMP_RAMP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("Mixin2 ZC Gain Switch", DA7218_MIXIN_2_CTRL,
		   DA7218_MIXIN_2_AMP_ZC_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),

	/* ADCs */
	SOC_SINGLE("ADC1 AAF Switch", DA7218_ADC_1_CTRL,
		   DA7218_ADC_1_AAF_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("ADC2 AAF Switch", DA7218_ADC_2_CTRL,
		   DA7218_ADC_2_AAF_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("ADC LP Mode Switch", DA7218_ADC_MODE,
		   DA7218_ADC_LP_MODE_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),

	/* Input Filters */
	SOC_SINGLE_TLV("In Filter1L Volume", DA7218_IN_1L_GAIN,
		       DA7218_IN_1L_DIGITAL_GAIN_SHIFT,
		       DA7218_IN_DIGITAL_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_in_dig_gain_tlv),
	SOC_SINGLE("In Filter1L Switch", DA7218_IN_1L_FILTER_CTRL,
		   DA7218_IN_1L_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE("In Filter1L Gain Ramp Switch", DA7218_IN_1L_FILTER_CTRL,
		   DA7218_IN_1L_RAMP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE_TLV("In Filter1R Volume", DA7218_IN_1R_GAIN,
		       DA7218_IN_1R_DIGITAL_GAIN_SHIFT,
		       DA7218_IN_DIGITAL_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_in_dig_gain_tlv),
	SOC_SINGLE("In Filter1R Switch", DA7218_IN_1R_FILTER_CTRL,
		   DA7218_IN_1R_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE("In Filter1R Gain Ramp Switch",
		   DA7218_IN_1R_FILTER_CTRL, DA7218_IN_1R_RAMP_EN_SHIFT,
		   DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),
	SOC_SINGLE_TLV("In Filter2L Volume", DA7218_IN_2L_GAIN,
		       DA7218_IN_2L_DIGITAL_GAIN_SHIFT,
		       DA7218_IN_DIGITAL_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_in_dig_gain_tlv),
	SOC_SINGLE("In Filter2L Switch", DA7218_IN_2L_FILTER_CTRL,
		   DA7218_IN_2L_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE("In Filter2L Gain Ramp Switch", DA7218_IN_2L_FILTER_CTRL,
		   DA7218_IN_2L_RAMP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE_TLV("In Filter2R Volume", DA7218_IN_2R_GAIN,
		       DA7218_IN_2R_DIGITAL_GAIN_SHIFT,
		       DA7218_IN_DIGITAL_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_in_dig_gain_tlv),
	SOC_SINGLE("In Filter2R Switch", DA7218_IN_2R_FILTER_CTRL,
		   DA7218_IN_2R_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),
	SOC_SINGLE("In Filter2R Gain Ramp Switch",
		   DA7218_IN_2R_FILTER_CTRL, DA7218_IN_2R_RAMP_EN_SHIFT,
		   DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),

	/* AGS */
	SOC_SINGLE_TLV("AGS Trigger", DA7218_AGS_TRIGGER,
		       DA7218_AGS_TRIGGER_SHIFT, DA7218_AGS_TRIGGER_MAX,
		       DA7218_INVERT, da7218_ags_trigger_tlv),
	SOC_SINGLE_TLV("AGS Max Attenuation", DA7218_AGS_ATT_MAX,
		       DA7218_AGS_ATT_MAX_SHIFT, DA7218_AGS_ATT_MAX_MAX,
		       DA7218_NO_INVERT, da7218_ags_att_max_tlv),
	SOC_SINGLE("AGS Anticlip Switch", DA7218_AGS_ANTICLIP_CTRL,
		   DA7218_AGS_ANTICLIP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("AGS Channel1 Switch", DA7218_AGS_ENABLE,
		   DA7218_AGS_ENABLE_CHAN1_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("AGS Channel2 Switch", DA7218_AGS_ENABLE,
		   DA7218_AGS_ENABLE_CHAN2_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),

	/* ALC */
	SOC_ENUM("ALC Attack Rate", da7218_alc_attack_rate),
	SOC_ENUM("ALC Release Rate", da7218_alc_release_rate),
	SOC_ENUM("ALC Hold Time", da7218_alc_hold_समय),
	SOC_SINGLE_TLV("ALC Noise Threshold", DA7218_ALC_NOISE,
		       DA7218_ALC_NOISE_SHIFT, DA7218_ALC_THRESHOLD_MAX,
		       DA7218_INVERT, da7218_alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Min Threshold", DA7218_ALC_TARGET_MIN,
		       DA7218_ALC_THRESHOLD_MIN_SHIFT, DA7218_ALC_THRESHOLD_MAX,
		       DA7218_INVERT, da7218_alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Threshold", DA7218_ALC_TARGET_MAX,
		       DA7218_ALC_THRESHOLD_MAX_SHIFT, DA7218_ALC_THRESHOLD_MAX,
		       DA7218_INVERT, da7218_alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Attenuation", DA7218_ALC_GAIN_LIMITS,
		       DA7218_ALC_ATTEN_MAX_SHIFT, DA7218_ALC_ATTEN_GAIN_MAX,
		       DA7218_NO_INVERT, da7218_alc_gain_tlv),
	SOC_SINGLE_TLV("ALC Max Gain", DA7218_ALC_GAIN_LIMITS,
		       DA7218_ALC_GAIN_MAX_SHIFT, DA7218_ALC_ATTEN_GAIN_MAX,
		       DA7218_NO_INVERT, da7218_alc_gain_tlv),
	SOC_SINGLE_RANGE_TLV("ALC Min Analog Gain", DA7218_ALC_ANA_GAIN_LIMITS,
			     DA7218_ALC_ANA_GAIN_MIN_SHIFT,
			     DA7218_ALC_ANA_GAIN_MIN, DA7218_ALC_ANA_GAIN_MAX,
			     DA7218_NO_INVERT, da7218_alc_ana_gain_tlv),
	SOC_SINGLE_RANGE_TLV("ALC Max Analog Gain", DA7218_ALC_ANA_GAIN_LIMITS,
			     DA7218_ALC_ANA_GAIN_MAX_SHIFT,
			     DA7218_ALC_ANA_GAIN_MIN, DA7218_ALC_ANA_GAIN_MAX,
			     DA7218_NO_INVERT, da7218_alc_ana_gain_tlv),
	SOC_ENUM("ALC Anticlip Step", da7218_alc_anticlip_step),
	SOC_SINGLE("ALC Anticlip Switch", DA7218_ALC_ANTICLIP_CTRL,
		   DA7218_ALC_ANTICLIP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_DOUBLE_EXT("ALC Channel1 Switch", DA7218_ALC_CTRL1,
		       DA7218_ALC_CHAN1_L_EN_SHIFT, DA7218_ALC_CHAN1_R_EN_SHIFT,
		       DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT,
		       snd_soc_get_volsw, da7218_alc_sw_put),
	SOC_DOUBLE_EXT("ALC Channel2 Switch", DA7218_ALC_CTRL1,
		       DA7218_ALC_CHAN2_L_EN_SHIFT, DA7218_ALC_CHAN2_R_EN_SHIFT,
		       DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT,
		       snd_soc_get_volsw, da7218_alc_sw_put),

	/* Envelope Tracking */
	SOC_ENUM("Envelope Tracking Attack Rate", da7218_पूर्णांकeg_attack_rate),
	SOC_ENUM("Envelope Tracking Release Rate", da7218_पूर्णांकeg_release_rate),

	/* Input High-Pass Filters */
	SOC_ENUM("In Filter1 HPF Mode", da7218_in1_hpf_mode),
	SOC_ENUM("In Filter1 HPF Corner Audio", da7218_in1_audio_hpf_corner),
	SOC_ENUM("In Filter1 HPF Corner Voice", da7218_in1_voice_hpf_corner),
	SOC_ENUM("In Filter2 HPF Mode", da7218_in2_hpf_mode),
	SOC_ENUM("In Filter2 HPF Corner Audio", da7218_in2_audio_hpf_corner),
	SOC_ENUM("In Filter2 HPF Corner Voice", da7218_in2_voice_hpf_corner),

	/* Mic Level Detect */
	SOC_DOUBLE_EXT("Mic Level Detect Channel1 Switch", DA7218_LVL_DET_CTRL,
		       DA7218_LVL_DET_EN_CHAN1L_SHIFT,
		       DA7218_LVL_DET_EN_CHAN1R_SHIFT, DA7218_SWITCH_EN_MAX,
		       DA7218_NO_INVERT, da7218_mic_lvl_det_sw_get,
		       da7218_mic_lvl_det_sw_put),
	SOC_DOUBLE_EXT("Mic Level Detect Channel2 Switch", DA7218_LVL_DET_CTRL,
		       DA7218_LVL_DET_EN_CHAN2L_SHIFT,
		       DA7218_LVL_DET_EN_CHAN2R_SHIFT, DA7218_SWITCH_EN_MAX,
		       DA7218_NO_INVERT, da7218_mic_lvl_det_sw_get,
		       da7218_mic_lvl_det_sw_put),
	SOC_SINGLE("Mic Level Detect Level", DA7218_LVL_DET_LEVEL,
		   DA7218_LVL_DET_LEVEL_SHIFT, DA7218_LVL_DET_LEVEL_MAX,
		   DA7218_NO_INVERT),

	/* Digital Mixer (Input) */
	SOC_SINGLE_TLV("DMix In Filter1L Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_INFILT_1L_GAIN,
		       DA7218_OUTDAI_1L_INFILT_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1L Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_INFILT_1L_GAIN,
		       DA7218_OUTDAI_1R_INFILT_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1L Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_INFILT_1L_GAIN,
		       DA7218_OUTDAI_2L_INFILT_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1L Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_INFILT_1L_GAIN,
		       DA7218_OUTDAI_2R_INFILT_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In Filter1R Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_INFILT_1R_GAIN,
		       DA7218_OUTDAI_1L_INFILT_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1R Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_INFILT_1R_GAIN,
		       DA7218_OUTDAI_1R_INFILT_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1R Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_INFILT_1R_GAIN,
		       DA7218_OUTDAI_2L_INFILT_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1R Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_INFILT_1R_GAIN,
		       DA7218_OUTDAI_2R_INFILT_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In Filter2L Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_INFILT_2L_GAIN,
		       DA7218_OUTDAI_1L_INFILT_2L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2L Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_INFILT_2L_GAIN,
		       DA7218_OUTDAI_1R_INFILT_2L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2L Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_INFILT_2L_GAIN,
		       DA7218_OUTDAI_2L_INFILT_2L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2L Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_INFILT_2L_GAIN,
		       DA7218_OUTDAI_2R_INFILT_2L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In Filter2R Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_INFILT_2R_GAIN,
		       DA7218_OUTDAI_1L_INFILT_2R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2R Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_INFILT_2R_GAIN,
		       DA7218_OUTDAI_1R_INFILT_2R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2R Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_INFILT_2R_GAIN,
		       DA7218_OUTDAI_2L_INFILT_2R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2R Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_INFILT_2R_GAIN,
		       DA7218_OUTDAI_2R_INFILT_2R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix ToneGen Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_TONEGEN_GAIN,
		       DA7218_OUTDAI_1L_TONEGEN_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix ToneGen Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_TONEGEN_GAIN,
		       DA7218_OUTDAI_1R_TONEGEN_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix ToneGen Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_TONEGEN_GAIN,
		       DA7218_OUTDAI_2L_TONEGEN_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix ToneGen Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_TONEGEN_GAIN,
		       DA7218_OUTDAI_2R_TONEGEN_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In DAIL Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_INDAI_1L_GAIN,
		       DA7218_OUTDAI_1L_INDAI_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIL Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_INDAI_1L_GAIN,
		       DA7218_OUTDAI_1R_INDAI_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIL Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_INDAI_1L_GAIN,
		       DA7218_OUTDAI_2L_INDAI_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIL Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_INDAI_1L_GAIN,
		       DA7218_OUTDAI_2R_INDAI_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In DAIR Out1 DAIL Volume",
		       DA7218_DMIX_OUTDAI_1L_INDAI_1R_GAIN,
		       DA7218_OUTDAI_1L_INDAI_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIR Out1 DAIR Volume",
		       DA7218_DMIX_OUTDAI_1R_INDAI_1R_GAIN,
		       DA7218_OUTDAI_1R_INDAI_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIR Out2 DAIL Volume",
		       DA7218_DMIX_OUTDAI_2L_INDAI_1R_GAIN,
		       DA7218_OUTDAI_2L_INDAI_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIR Out2 DAIR Volume",
		       DA7218_DMIX_OUTDAI_2R_INDAI_1R_GAIN,
		       DA7218_OUTDAI_2R_INDAI_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	/* Digital Mixer (Output) */
	SOC_SINGLE_TLV("DMix In Filter1L Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_INFILT_1L_GAIN,
		       DA7218_OUTFILT_1L_INFILT_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1L Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_INFILT_1L_GAIN,
		       DA7218_OUTFILT_1R_INFILT_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In Filter1R Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_INFILT_1R_GAIN,
		       DA7218_OUTFILT_1L_INFILT_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter1R Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_INFILT_1R_GAIN,
		       DA7218_OUTFILT_1R_INFILT_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In Filter2L Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_INFILT_2L_GAIN,
		       DA7218_OUTFILT_1L_INFILT_2L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2L Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_INFILT_2L_GAIN,
		       DA7218_OUTFILT_1R_INFILT_2L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In Filter2R Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_INFILT_2R_GAIN,
		       DA7218_OUTFILT_1L_INFILT_2R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In Filter2R Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_INFILT_2R_GAIN,
		       DA7218_OUTFILT_1R_INFILT_2R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix ToneGen Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_TONEGEN_GAIN,
		       DA7218_OUTFILT_1L_TONEGEN_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix ToneGen Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_TONEGEN_GAIN,
		       DA7218_OUTFILT_1R_TONEGEN_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In DAIL Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_INDAI_1L_GAIN,
		       DA7218_OUTFILT_1L_INDAI_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIL Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_INDAI_1L_GAIN,
		       DA7218_OUTFILT_1R_INDAI_1L_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	SOC_SINGLE_TLV("DMix In DAIR Out FilterL Volume",
		       DA7218_DMIX_OUTFILT_1L_INDAI_1R_GAIN,
		       DA7218_OUTFILT_1L_INDAI_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),
	SOC_SINGLE_TLV("DMix In DAIR Out FilterR Volume",
		       DA7218_DMIX_OUTFILT_1R_INDAI_1R_GAIN,
		       DA7218_OUTFILT_1R_INDAI_1R_GAIN_SHIFT,
		       DA7218_DMIX_GAIN_MAX, DA7218_NO_INVERT,
		       da7218_dmix_gain_tlv),

	/* Sidetone Filter */
	SND_SOC_BYTES_EXT("Sidetone BiQuad Coefficients",
			  DA7218_SIDETONE_BIQ_3STAGE_CFG_SIZE,
			  da7218_biquad_coeff_get, da7218_biquad_coeff_put),
	SOC_SINGLE_TLV("Sidetone Volume", DA7218_SIDETONE_GAIN,
		       DA7218_SIDETONE_GAIN_SHIFT, DA7218_DMIX_GAIN_MAX,
		       DA7218_NO_INVERT, da7218_dmix_gain_tlv),
	SOC_SINGLE("Sidetone Switch", DA7218_SIDETONE_CTRL,
		   DA7218_SIDETONE_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),

	/* Tone Generator */
	SOC_ENUM("ToneGen DTMF Key", da7218_tonegen_dपंचांगf_key),
	SOC_SINGLE("ToneGen DTMF Switch", DA7218_TONE_GEN_CFG1,
		   DA7218_DTMF_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_ENUM("ToneGen Sinewave Gen Type", da7218_tonegen_swg_sel),
	SOC_SINGLE_EXT("ToneGen Sinewave1 Freq", DA7218_TONE_GEN_FREQ1_L,
		       DA7218_FREQ1_L_SHIFT, DA7218_FREQ_MAX, DA7218_NO_INVERT,
		       da7218_tonegen_freq_get, da7218_tonegen_freq_put),
	SOC_SINGLE_EXT("ToneGen Sinewave2 Freq", DA7218_TONE_GEN_FREQ2_L,
		       DA7218_FREQ2_L_SHIFT, DA7218_FREQ_MAX, DA7218_NO_INVERT,
		       da7218_tonegen_freq_get, da7218_tonegen_freq_put),
	SOC_SINGLE("ToneGen On Time", DA7218_TONE_GEN_ON_PER,
		   DA7218_BEEP_ON_PER_SHIFT, DA7218_BEEP_ON_OFF_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("ToneGen Off Time", DA7218_TONE_GEN_OFF_PER,
		   DA7218_BEEP_OFF_PER_SHIFT, DA7218_BEEP_ON_OFF_MAX,
		   DA7218_NO_INVERT),

	/* Gain ramping */
	SOC_ENUM("Gain Ramp Rate", da7218_gain_ramp_rate),

	/* DGS */
	SOC_SINGLE_TLV("DGS Trigger", DA7218_DGS_TRIGGER,
		       DA7218_DGS_TRIGGER_LVL_SHIFT, DA7218_DGS_TRIGGER_MAX,
		       DA7218_INVERT, da7218_dgs_trigger_tlv),
	SOC_ENUM("DGS Rise Coefficient", da7218_dgs_rise_coeff),
	SOC_ENUM("DGS Fall Coefficient", da7218_dgs_fall_coeff),
	SOC_SINGLE("DGS Sync Delay", DA7218_DGS_SYNC_DELAY,
		   DA7218_DGS_SYNC_DELAY_SHIFT, DA7218_DGS_SYNC_DELAY_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("DGS Fast SR Sync Delay", DA7218_DGS_SYNC_DELAY2,
		   DA7218_DGS_SYNC_DELAY2_SHIFT, DA7218_DGS_SYNC_DELAY_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("DGS Voice Filter Sync Delay", DA7218_DGS_SYNC_DELAY3,
		   DA7218_DGS_SYNC_DELAY3_SHIFT, DA7218_DGS_SYNC_DELAY3_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE_TLV("DGS Anticlip Level", DA7218_DGS_LEVELS,
		       DA7218_DGS_ANTICLIP_LVL_SHIFT,
		       DA7218_DGS_ANTICLIP_LVL_MAX, DA7218_INVERT,
		       da7218_dgs_anticlip_tlv),
	SOC_SINGLE_TLV("DGS Signal Level", DA7218_DGS_LEVELS,
		       DA7218_DGS_SIGNAL_LVL_SHIFT, DA7218_DGS_SIGNAL_LVL_MAX,
		       DA7218_INVERT, da7218_dgs_संकेत_tlv),
	SOC_SINGLE("DGS Gain Subrange Switch", DA7218_DGS_GAIN_CTRL,
		   DA7218_DGS_SUBR_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("DGS Gain Ramp Switch", DA7218_DGS_GAIN_CTRL,
		   DA7218_DGS_RAMP_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),
	SOC_SINGLE("DGS Gain Steps", DA7218_DGS_GAIN_CTRL,
		   DA7218_DGS_STEPS_SHIFT, DA7218_DGS_STEPS_MAX,
		   DA7218_NO_INVERT),
	SOC_DOUBLE("DGS Switch", DA7218_DGS_ENABLE, DA7218_DGS_ENABLE_L_SHIFT,
		   DA7218_DGS_ENABLE_R_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),

	/* Output High-Pass Filter */
	SOC_ENUM("Out Filter HPF Mode", da7218_out1_hpf_mode),
	SOC_ENUM("Out Filter HPF Corner Audio", da7218_out1_audio_hpf_corner),
	SOC_ENUM("Out Filter HPF Corner Voice", da7218_out1_voice_hpf_corner),

	/* 5-Band Equaliser */
	SOC_SINGLE_TLV("Out EQ Band1 Volume", DA7218_OUT_1_EQ_12_FILTER_CTRL,
		       DA7218_OUT_1_EQ_BAND1_SHIFT, DA7218_OUT_EQ_BAND_MAX,
		       DA7218_NO_INVERT, da7218_out_eq_band_tlv),
	SOC_SINGLE_TLV("Out EQ Band2 Volume", DA7218_OUT_1_EQ_12_FILTER_CTRL,
		       DA7218_OUT_1_EQ_BAND2_SHIFT, DA7218_OUT_EQ_BAND_MAX,
		       DA7218_NO_INVERT, da7218_out_eq_band_tlv),
	SOC_SINGLE_TLV("Out EQ Band3 Volume", DA7218_OUT_1_EQ_34_FILTER_CTRL,
		       DA7218_OUT_1_EQ_BAND3_SHIFT, DA7218_OUT_EQ_BAND_MAX,
		       DA7218_NO_INVERT, da7218_out_eq_band_tlv),
	SOC_SINGLE_TLV("Out EQ Band4 Volume", DA7218_OUT_1_EQ_34_FILTER_CTRL,
		       DA7218_OUT_1_EQ_BAND4_SHIFT, DA7218_OUT_EQ_BAND_MAX,
		       DA7218_NO_INVERT, da7218_out_eq_band_tlv),
	SOC_SINGLE_TLV("Out EQ Band5 Volume", DA7218_OUT_1_EQ_5_FILTER_CTRL,
		       DA7218_OUT_1_EQ_BAND5_SHIFT, DA7218_OUT_EQ_BAND_MAX,
		       DA7218_NO_INVERT, da7218_out_eq_band_tlv),
	SOC_SINGLE("Out EQ Switch", DA7218_OUT_1_EQ_5_FILTER_CTRL,
		   DA7218_OUT_1_EQ_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_NO_INVERT),

	/* BiQuad Filters */
	SND_SOC_BYTES_EXT("BiQuad Coefficients",
			  DA7218_OUT_1_BIQ_5STAGE_CFG_SIZE,
			  da7218_biquad_coeff_get, da7218_biquad_coeff_put),
	SOC_SINGLE("BiQuad Filter Switch", DA7218_OUT_1_BIQ_5STAGE_CTRL,
		   DA7218_OUT_1_BIQ_5STAGE_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		   DA7218_INVERT),

	/* Output Filters */
	SOC_DOUBLE_R_RANGE_TLV("Out Filter Volume", DA7218_OUT_1L_GAIN,
			       DA7218_OUT_1R_GAIN,
			       DA7218_OUT_1L_DIGITAL_GAIN_SHIFT,
			       DA7218_OUT_DIGITAL_GAIN_MIN,
			       DA7218_OUT_DIGITAL_GAIN_MAX, DA7218_NO_INVERT,
			       da7218_out_dig_gain_tlv),
	SOC_DOUBLE_R("Out Filter Switch", DA7218_OUT_1L_FILTER_CTRL,
		     DA7218_OUT_1R_FILTER_CTRL, DA7218_OUT_1L_MUTE_EN_SHIFT,
		     DA7218_SWITCH_EN_MAX, DA7218_INVERT),
	SOC_DOUBLE_R("Out Filter Gain Subrange Switch",
		     DA7218_OUT_1L_FILTER_CTRL, DA7218_OUT_1R_FILTER_CTRL,
		     DA7218_OUT_1L_SUBRANGE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		     DA7218_NO_INVERT),
	SOC_DOUBLE_R("Out Filter Gain Ramp Switch", DA7218_OUT_1L_FILTER_CTRL,
		     DA7218_OUT_1R_FILTER_CTRL, DA7218_OUT_1L_RAMP_EN_SHIFT,
		     DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),

	/* Mixer Output */
	SOC_DOUBLE_R_RANGE_TLV("Mixout Volume", DA7218_MIXOUT_L_GAIN,
			       DA7218_MIXOUT_R_GAIN,
			       DA7218_MIXOUT_L_AMP_GAIN_SHIFT,
			       DA7218_MIXOUT_AMP_GAIN_MIN,
			       DA7218_MIXOUT_AMP_GAIN_MAX, DA7218_NO_INVERT,
			       da7218_mixout_gain_tlv),

	/* DAC Noise Gate */
	SOC_ENUM("DAC NG Setup Time", da7218_dac_ng_setup_समय),
	SOC_ENUM("DAC NG Rampup Rate", da7218_dac_ng_rampup_rate),
	SOC_ENUM("DAC NG Rampdown Rate", da7218_dac_ng_rampकरोwn_rate),
	SOC_SINGLE_TLV("DAC NG Off Threshold", DA7218_DAC_NG_OFF_THRESH,
		       DA7218_DAC_NG_OFF_THRESHOLD_SHIFT,
		       DA7218_DAC_NG_THRESHOLD_MAX, DA7218_NO_INVERT,
		       da7218_dac_ng_threshold_tlv),
	SOC_SINGLE_TLV("DAC NG On Threshold", DA7218_DAC_NG_ON_THRESH,
		       DA7218_DAC_NG_ON_THRESHOLD_SHIFT,
		       DA7218_DAC_NG_THRESHOLD_MAX, DA7218_NO_INVERT,
		       da7218_dac_ng_threshold_tlv),
	SOC_SINGLE("DAC NG Switch", DA7218_DAC_NG_CTRL, DA7218_DAC_NG_EN_SHIFT,
		   DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),

	/* CP */
	SOC_ENUM("Charge Pump Track Mode", da7218_cp_mchange),
	SOC_ENUM("Charge Pump Frequency", da7218_cp_fcontrol),
	SOC_ENUM("Charge Pump Decay Rate", da7218_cp_tau_delay),
	SOC_SINGLE("Charge Pump Threshold", DA7218_CP_VOL_THRESHOLD1,
		   DA7218_CP_THRESH_VDD2_SHIFT, DA7218_CP_THRESH_VDD2_MAX,
		   DA7218_NO_INVERT),

	/* Headphones */
	SOC_DOUBLE_R_RANGE_TLV("Headphone Volume", DA7218_HP_L_GAIN,
			       DA7218_HP_R_GAIN, DA7218_HP_L_AMP_GAIN_SHIFT,
			       DA7218_HP_AMP_GAIN_MIN, DA7218_HP_AMP_GAIN_MAX,
			       DA7218_NO_INVERT, da7218_hp_gain_tlv),
	SOC_DOUBLE_R("Headphone Switch", DA7218_HP_L_CTRL, DA7218_HP_R_CTRL,
		     DA7218_HP_L_AMP_MUTE_EN_SHIFT, DA7218_SWITCH_EN_MAX,
		     DA7218_INVERT),
	SOC_DOUBLE_R("Headphone Gain Ramp Switch", DA7218_HP_L_CTRL,
		     DA7218_HP_R_CTRL, DA7218_HP_L_AMP_RAMP_EN_SHIFT,
		     DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),
	SOC_DOUBLE_R("Headphone ZC Gain Switch", DA7218_HP_L_CTRL,
		     DA7218_HP_R_CTRL, DA7218_HP_L_AMP_ZC_EN_SHIFT,
		     DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),
पूर्ण;


/*
 * DAPM Mux Controls
 */

अटल स्थिर अक्षर * स्थिर da7218_mic_sel_text[] = अणु "Analog", "Digital" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_mic1_sel =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(da7218_mic_sel_text),
			    da7218_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new da7218_mic1_sel_mux =
	SOC_DAPM_ENUM("Mic1 Mux", da7218_mic1_sel);

अटल स्थिर काष्ठा soc_क्रमागत da7218_mic2_sel =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(da7218_mic_sel_text),
			    da7218_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new da7218_mic2_sel_mux =
	SOC_DAPM_ENUM("Mic2 Mux", da7218_mic2_sel);

अटल स्थिर अक्षर * स्थिर da7218_sidetone_in_sel_txt[] = अणु
	"In Filter1L", "In Filter1R", "In Filter2L", "In Filter2R"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_sidetone_in_sel =
	SOC_ENUM_SINGLE(DA7218_SIDETONE_IN_SELECT,
			DA7218_SIDETONE_IN_SELECT_SHIFT,
			DA7218_SIDETONE_IN_SELECT_MAX,
			da7218_sidetone_in_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7218_sidetone_in_sel_mux =
	SOC_DAPM_ENUM("Sidetone Mux", da7218_sidetone_in_sel);

अटल स्थिर अक्षर * स्थिर da7218_out_filt_biq_sel_txt[] = अणु
	"Bypass", "Enabled"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत da7218_out_filtl_biq_sel =
	SOC_ENUM_SINGLE(DA7218_OUT_1L_FILTER_CTRL,
			DA7218_OUT_1L_BIQ_5STAGE_SEL_SHIFT,
			DA7218_OUT_BIQ_5STAGE_SEL_MAX,
			da7218_out_filt_biq_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_filtl_biq_sel_mux =
	SOC_DAPM_ENUM("Out FilterL BiQuad Mux", da7218_out_filtl_biq_sel);

अटल स्थिर काष्ठा soc_क्रमागत da7218_out_filtr_biq_sel =
	SOC_ENUM_SINGLE(DA7218_OUT_1R_FILTER_CTRL,
			DA7218_OUT_1R_BIQ_5STAGE_SEL_SHIFT,
			DA7218_OUT_BIQ_5STAGE_SEL_MAX,
			da7218_out_filt_biq_sel_txt);

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_filtr_biq_sel_mux =
	SOC_DAPM_ENUM("Out FilterR BiQuad Mux", da7218_out_filtr_biq_sel);


/*
 * DAPM Mixer Controls
 */

#घोषणा DA7218_DMIX_CTRLS(reg)						\
	SOC_DAPM_SINGLE("In Filter1L Switch", reg,			\
			DA7218_DMIX_SRC_INFILT1L,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("In Filter1R Switch", reg,			\
			DA7218_DMIX_SRC_INFILT1R,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("In Filter2L Switch", reg,			\
			DA7218_DMIX_SRC_INFILT2L,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("In Filter2R Switch", reg,			\
			DA7218_DMIX_SRC_INFILT2R,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("ToneGen Switch", reg,				\
			DA7218_DMIX_SRC_TONEGEN,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("DAIL Switch", reg, DA7218_DMIX_SRC_DAIL,	\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("DAIR Switch", reg, DA7218_DMIX_SRC_DAIR,	\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT)

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_dai1l_mix_controls[] = अणु
	DA7218_DMIX_CTRLS(DA7218_DROUTING_OUTDAI_1L),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_dai1r_mix_controls[] = अणु
	DA7218_DMIX_CTRLS(DA7218_DROUTING_OUTDAI_1R),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_dai2l_mix_controls[] = अणु
	DA7218_DMIX_CTRLS(DA7218_DROUTING_OUTDAI_2L),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_dai2r_mix_controls[] = अणु
	DA7218_DMIX_CTRLS(DA7218_DROUTING_OUTDAI_2R),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_filtl_mix_controls[] = अणु
	DA7218_DMIX_CTRLS(DA7218_DROUTING_OUTFILT_1L),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7218_out_filtr_mix_controls[] = अणु
	DA7218_DMIX_CTRLS(DA7218_DROUTING_OUTFILT_1R),
पूर्ण;

#घोषणा DA7218_DMIX_ST_CTRLS(reg)					\
	SOC_DAPM_SINGLE("Out FilterL Switch", reg,			\
			DA7218_DMIX_ST_SRC_OUTFILT1L,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("Out FilterR Switch", reg,			\
			DA7218_DMIX_ST_SRC_OUTFILT1R,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT),	\
	SOC_DAPM_SINGLE("Sidetone Switch", reg,				\
			DA7218_DMIX_ST_SRC_SIDETONE,			\
			DA7218_SWITCH_EN_MAX, DA7218_NO_INVERT)		\

अटल स्थिर काष्ठा snd_kcontrol_new da7218_st_out_filtl_mix_controls[] = अणु
	DA7218_DMIX_ST_CTRLS(DA7218_DROUTING_ST_OUTFILT_1L),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new da7218_st_out_filtr_mix_controls[] = अणु
	DA7218_DMIX_ST_CTRLS(DA7218_DROUTING_ST_OUTFILT_1R),
पूर्ण;


/*
 * DAPM Events
 */

/*
 * We keep track of which input filters are enabled. This is used in the logic
 * क्रम controlling the mic level detect feature.
 */
अटल पूर्णांक da7218_in_filter_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	u8 mask;

	चयन (w->reg) अणु
	हाल DA7218_IN_1L_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN1L_SHIFT);
		अवरोध;
	हाल DA7218_IN_1R_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN1R_SHIFT);
		अवरोध;
	हाल DA7218_IN_2L_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN2L_SHIFT);
		अवरोध;
	हाल DA7218_IN_2R_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN2R_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		da7218->in_filt_en |= mask;
		/*
		 * If we're enabling path क्रम mic level detect, रुको क्रम path
		 * to settle beक्रमe enabling feature to aव्योम incorrect and
		 * unwanted detect events.
		 */
		अगर (mask & da7218->mic_lvl_det_en)
			msleep(DA7218_MIC_LVL_DET_DELAY);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		da7218->in_filt_en &= ~mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Enable configured level detection paths */
	snd_soc_component_ग_लिखो(component, DA7218_LVL_DET_CTRL,
		      (da7218->in_filt_en & da7218->mic_lvl_det_en));

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_dai_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	u8 pll_ctrl, pll_status, refosc_cal;
	पूर्णांक i;
	bool success;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (da7218->master)
			/* Enable DAI clks क्रम master mode */
			snd_soc_component_update_bits(component, DA7218_DAI_CLK_MODE,
					    DA7218_DAI_CLK_EN_MASK,
					    DA7218_DAI_CLK_EN_MASK);

		/* Tune reference oscillator */
		snd_soc_component_ग_लिखो(component, DA7218_PLL_REFOSC_CAL,
			      DA7218_PLL_REFOSC_CAL_START_MASK);
		snd_soc_component_ग_लिखो(component, DA7218_PLL_REFOSC_CAL,
			      DA7218_PLL_REFOSC_CAL_START_MASK |
			      DA7218_PLL_REFOSC_CAL_EN_MASK);

		/* Check tuning complete */
		i = 0;
		success = false;
		करो अणु
			refosc_cal = snd_soc_component_पढ़ो(component, DA7218_PLL_REFOSC_CAL);
			अगर (!(refosc_cal & DA7218_PLL_REFOSC_CAL_START_MASK)) अणु
				success = true;
			पूर्ण अन्यथा अणु
				++i;
				usleep_range(DA7218_REF_OSC_CHECK_DELAY_MIN,
					     DA7218_REF_OSC_CHECK_DELAY_MAX);
			पूर्ण
		पूर्ण जबतक ((i < DA7218_REF_OSC_CHECK_TRIES) && (!success));

		अगर (!success)
			dev_warn(component->dev,
				 "Reference oscillator failed calibration\n");

		/* PC synchronised to DAI */
		snd_soc_component_ग_लिखो(component, DA7218_PC_COUNT,
			      DA7218_PC_RESYNC_AUTO_MASK);

		/* If SRM not enabled, we करोn't need to check status */
		pll_ctrl = snd_soc_component_पढ़ो(component, DA7218_PLL_CTRL);
		अगर ((pll_ctrl & DA7218_PLL_MODE_MASK) != DA7218_PLL_MODE_SRM)
			वापस 0;

		/* Check SRM has locked */
		i = 0;
		success = false;
		करो अणु
			pll_status = snd_soc_component_पढ़ो(component, DA7218_PLL_STATUS);
			अगर (pll_status & DA7218_PLL_SRM_STATUS_SRM_LOCK) अणु
				success = true;
			पूर्ण अन्यथा अणु
				++i;
				msleep(DA7218_SRM_CHECK_DELAY);
			पूर्ण
		पूर्ण जबतक ((i < DA7218_SRM_CHECK_TRIES) && (!success));

		अगर (!success)
			dev_warn(component->dev, "SRM failed to lock\n");

		वापस 0;
	हाल SND_SOC_DAPM_POST_PMD:
		/* PC मुक्त-running */
		snd_soc_component_ग_लिखो(component, DA7218_PC_COUNT, DA7218_PC_FREERUN_MASK);

		अगर (da7218->master)
			/* Disable DAI clks क्रम master mode */
			snd_soc_component_update_bits(component, DA7218_DAI_CLK_MODE,
					    DA7218_DAI_CLK_EN_MASK, 0);

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक da7218_cp_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	/*
	 * If this is DA7217 and we're using single supply क्रम dअगरferential
	 * output, we really करोn't want to touch the अक्षरge pump.
	 */
	अगर (da7218->hp_single_supply)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, DA7218_CP_CTRL, DA7218_CP_EN_MASK,
				    DA7218_CP_EN_MASK);
		वापस 0;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, DA7218_CP_CTRL, DA7218_CP_EN_MASK,
				    0);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक da7218_hp_pga_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Enable headphone output */
		snd_soc_component_update_bits(component, w->reg, DA7218_HP_AMP_OE_MASK,
				    DA7218_HP_AMP_OE_MASK);
		वापस 0;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* Headphone output high impedance */
		snd_soc_component_update_bits(component, w->reg, DA7218_HP_AMP_OE_MASK, 0);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


/*
 * DAPM Widमाला_लो
 */

अटल स्थिर काष्ठा snd_soc_dapm_widget da7218_dapm_widमाला_लो[] = अणु
	/* Input Supplies */
	SND_SOC_DAPM_SUPPLY("Mic Bias1", DA7218_MICBIAS_EN,
			    DA7218_MICBIAS_1_EN_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Bias2", DA7218_MICBIAS_EN,
			    DA7218_MICBIAS_2_EN_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMic1 Left", DA7218_DMIC_1_CTRL,
			    DA7218_DMIC_1L_EN_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMic1 Right", DA7218_DMIC_1_CTRL,
			    DA7218_DMIC_1R_EN_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMic2 Left", DA7218_DMIC_2_CTRL,
			    DA7218_DMIC_2L_EN_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMic2 Right", DA7218_DMIC_2_CTRL,
			    DA7218_DMIC_2R_EN_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),

	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("DMIC1L"),
	SND_SOC_DAPM_INPUT("DMIC1R"),
	SND_SOC_DAPM_INPUT("DMIC2L"),
	SND_SOC_DAPM_INPUT("DMIC2R"),

	/* Input Mixer Supplies */
	SND_SOC_DAPM_SUPPLY("Mixin1 Supply", DA7218_MIXIN_1_CTRL,
			    DA7218_MIXIN_1_MIX_SEL_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mixin2 Supply", DA7218_MIXIN_2_CTRL,
			    DA7218_MIXIN_2_MIX_SEL_SHIFT, DA7218_NO_INVERT,
			    शून्य, 0),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic1 PGA", DA7218_MIC_1_CTRL,
			 DA7218_MIC_1_AMP_EN_SHIFT, DA7218_NO_INVERT,
			 शून्य, 0),
	SND_SOC_DAPM_PGA("Mic2 PGA", DA7218_MIC_2_CTRL,
			 DA7218_MIC_2_AMP_EN_SHIFT, DA7218_NO_INVERT,
			 शून्य, 0),
	SND_SOC_DAPM_PGA("Mixin1 PGA", DA7218_MIXIN_1_CTRL,
			 DA7218_MIXIN_1_AMP_EN_SHIFT, DA7218_NO_INVERT,
			 शून्य, 0),
	SND_SOC_DAPM_PGA("Mixin2 PGA", DA7218_MIXIN_2_CTRL,
			 DA7218_MIXIN_2_AMP_EN_SHIFT, DA7218_NO_INVERT,
			 शून्य, 0),

	/* Mic/DMic Muxes */
	SND_SOC_DAPM_MUX("Mic1 Mux", SND_SOC_NOPM, 0, 0, &da7218_mic1_sel_mux),
	SND_SOC_DAPM_MUX("Mic2 Mux", SND_SOC_NOPM, 0, 0, &da7218_mic2_sel_mux),

	/* Input Filters */
	SND_SOC_DAPM_ADC_E("In Filter1L", शून्य, DA7218_IN_1L_FILTER_CTRL,
			   DA7218_IN_1L_FILTER_EN_SHIFT, DA7218_NO_INVERT,
			   da7218_in_filter_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("In Filter1R", शून्य, DA7218_IN_1R_FILTER_CTRL,
			   DA7218_IN_1R_FILTER_EN_SHIFT, DA7218_NO_INVERT,
			   da7218_in_filter_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("In Filter2L", शून्य, DA7218_IN_2L_FILTER_CTRL,
			   DA7218_IN_2L_FILTER_EN_SHIFT, DA7218_NO_INVERT,
			   da7218_in_filter_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("In Filter2R", शून्य, DA7218_IN_2R_FILTER_CTRL,
			   DA7218_IN_2R_FILTER_EN_SHIFT, DA7218_NO_INVERT,
			   da7218_in_filter_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	/* Tone Generator */
	SND_SOC_DAPM_SIGGEN("TONE"),
	SND_SOC_DAPM_PGA("Tone Generator", DA7218_TONE_GEN_CFG1,
			 DA7218_START_STOPN_SHIFT, DA7218_NO_INVERT, शून्य, 0),

	/* Sidetone Input */
	SND_SOC_DAPM_MUX("Sidetone Mux", SND_SOC_NOPM, 0, 0,
			 &da7218_sidetone_in_sel_mux),
	SND_SOC_DAPM_ADC("Sidetone Filter", शून्य, DA7218_SIDETONE_CTRL,
			 DA7218_SIDETONE_FILTER_EN_SHIFT, DA7218_NO_INVERT),

	/* Input Mixers */
	SND_SOC_DAPM_MIXER("Mixer DAI1L", SND_SOC_NOPM, 0, 0,
			   da7218_out_dai1l_mix_controls,
			   ARRAY_SIZE(da7218_out_dai1l_mix_controls)),
	SND_SOC_DAPM_MIXER("Mixer DAI1R", SND_SOC_NOPM, 0, 0,
			   da7218_out_dai1r_mix_controls,
			   ARRAY_SIZE(da7218_out_dai1r_mix_controls)),
	SND_SOC_DAPM_MIXER("Mixer DAI2L", SND_SOC_NOPM, 0, 0,
			   da7218_out_dai2l_mix_controls,
			   ARRAY_SIZE(da7218_out_dai2l_mix_controls)),
	SND_SOC_DAPM_MIXER("Mixer DAI2R", SND_SOC_NOPM, 0, 0,
			   da7218_out_dai2r_mix_controls,
			   ARRAY_SIZE(da7218_out_dai2r_mix_controls)),

	/* DAI Supply */
	SND_SOC_DAPM_SUPPLY("DAI", DA7218_DAI_CTRL, DA7218_DAI_EN_SHIFT,
			    DA7218_NO_INVERT, da7218_dai_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* DAI */
	SND_SOC_DAPM_AIF_OUT("DAIOUT", "Capture", 0, DA7218_DAI_TDM_CTRL,
			     DA7218_DAI_OE_SHIFT, DA7218_NO_INVERT),
	SND_SOC_DAPM_AIF_IN("DAIIN", "Playback", 0, SND_SOC_NOPM, 0, 0),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Mixer Out FilterL", SND_SOC_NOPM, 0, 0,
			   da7218_out_filtl_mix_controls,
			   ARRAY_SIZE(da7218_out_filtl_mix_controls)),
	SND_SOC_DAPM_MIXER("Mixer Out FilterR", SND_SOC_NOPM, 0, 0,
			   da7218_out_filtr_mix_controls,
			   ARRAY_SIZE(da7218_out_filtr_mix_controls)),

	/* BiQuad Filters */
	SND_SOC_DAPM_MUX("Out FilterL BiQuad Mux", SND_SOC_NOPM, 0, 0,
			 &da7218_out_filtl_biq_sel_mux),
	SND_SOC_DAPM_MUX("Out FilterR BiQuad Mux", SND_SOC_NOPM, 0, 0,
			 &da7218_out_filtr_biq_sel_mux),
	SND_SOC_DAPM_DAC("BiQuad Filter", शून्य, DA7218_OUT_1_BIQ_5STAGE_CTRL,
			 DA7218_OUT_1_BIQ_5STAGE_FILTER_EN_SHIFT,
			 DA7218_NO_INVERT),

	/* Sidetone Mixers */
	SND_SOC_DAPM_MIXER("ST Mixer Out FilterL", SND_SOC_NOPM, 0, 0,
			   da7218_st_out_filtl_mix_controls,
			   ARRAY_SIZE(da7218_st_out_filtl_mix_controls)),
	SND_SOC_DAPM_MIXER("ST Mixer Out FilterR", SND_SOC_NOPM, 0, 0,
			   da7218_st_out_filtr_mix_controls,
			   ARRAY_SIZE(da7218_st_out_filtr_mix_controls)),

	/* Output Filters */
	SND_SOC_DAPM_DAC("Out FilterL", शून्य, DA7218_OUT_1L_FILTER_CTRL,
			 DA7218_OUT_1L_FILTER_EN_SHIFT, DA7218_NO_INVERT),
	SND_SOC_DAPM_DAC("Out FilterR", शून्य, DA7218_OUT_1R_FILTER_CTRL,
			 DA7218_IN_1R_FILTER_EN_SHIFT, DA7218_NO_INVERT),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("Mixout Left PGA", DA7218_MIXOUT_L_CTRL,
			 DA7218_MIXOUT_L_AMP_EN_SHIFT, DA7218_NO_INVERT,
			 शून्य, 0),
	SND_SOC_DAPM_PGA("Mixout Right PGA", DA7218_MIXOUT_R_CTRL,
			 DA7218_MIXOUT_R_AMP_EN_SHIFT, DA7218_NO_INVERT,
			 शून्य, 0),
	SND_SOC_DAPM_PGA_E("Headphone Left PGA", DA7218_HP_L_CTRL,
			   DA7218_HP_L_AMP_EN_SHIFT, DA7218_NO_INVERT, शून्य, 0,
			   da7218_hp_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("Headphone Right PGA", DA7218_HP_R_CTRL,
			   DA7218_HP_R_AMP_EN_SHIFT, DA7218_NO_INVERT, शून्य, 0,
			   da7218_hp_pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	/* Output Supplies */
	SND_SOC_DAPM_SUPPLY("Charge Pump", SND_SOC_NOPM, 0, 0, da7218_cp_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
पूर्ण;


/*
 * DAPM Mixer Routes
 */

#घोषणा DA7218_DMIX_ROUTES(name)				\
	अणुname, "In Filter1L Switch", "In Filter1L"पूर्ण,		\
	अणुname, "In Filter1R Switch", "In Filter1R"पूर्ण,		\
	अणुname, "In Filter2L Switch", "In Filter2L"पूर्ण,		\
	अणुname, "In Filter2R Switch", "In Filter2R"पूर्ण,		\
	अणुname, "ToneGen Switch", "Tone Generator"पूर्ण,		\
	अणुname, "DAIL Switch", "DAIIN"पूर्ण,				\
	अणुname, "DAIR Switch", "DAIIN"पूर्ण

#घोषणा DA7218_DMIX_ST_ROUTES(name)				\
	अणुname, "Out FilterL Switch", "Out FilterL BiQuad Mux"पूर्ण,	\
	अणुname, "Out FilterR Switch", "Out FilterR BiQuad Mux"पूर्ण,	\
	अणुname, "Sidetone Switch", "Sidetone Filter"पूर्ण


/*
 * DAPM audio route definition
 */

अटल स्थिर काष्ठा snd_soc_dapm_route da7218_audio_map[] = अणु
	/* Input paths */
	अणु"MIC1", शून्य, "Mic Bias1"पूर्ण,
	अणु"MIC2", शून्य, "Mic Bias2"पूर्ण,
	अणु"DMIC1L", शून्य, "Mic Bias1"पूर्ण,
	अणु"DMIC1L", शून्य, "DMic1 Left"पूर्ण,
	अणु"DMIC1R", शून्य, "Mic Bias1"पूर्ण,
	अणु"DMIC1R", शून्य, "DMic1 Right"पूर्ण,
	अणु"DMIC2L", शून्य, "Mic Bias2"पूर्ण,
	अणु"DMIC2L", शून्य, "DMic2 Left"पूर्ण,
	अणु"DMIC2R", शून्य, "Mic Bias2"पूर्ण,
	अणु"DMIC2R", शून्य, "DMic2 Right"पूर्ण,

	अणु"Mic1 PGA", शून्य, "MIC1"पूर्ण,
	अणु"Mic2 PGA", शून्य, "MIC2"पूर्ण,

	अणु"Mixin1 PGA", शून्य, "Mixin1 Supply"पूर्ण,
	अणु"Mixin2 PGA", शून्य, "Mixin2 Supply"पूर्ण,

	अणु"Mixin1 PGA", शून्य, "Mic1 PGA"पूर्ण,
	अणु"Mixin2 PGA", शून्य, "Mic2 PGA"पूर्ण,

	अणु"Mic1 Mux", "Analog", "Mixin1 PGA"पूर्ण,
	अणु"Mic1 Mux", "Digital", "DMIC1L"पूर्ण,
	अणु"Mic1 Mux", "Digital", "DMIC1R"पूर्ण,
	अणु"Mic2 Mux", "Analog", "Mixin2 PGA"पूर्ण,
	अणु"Mic2 Mux", "Digital", "DMIC2L"पूर्ण,
	अणु"Mic2 Mux", "Digital", "DMIC2R"पूर्ण,

	अणु"In Filter1L", शून्य, "Mic1 Mux"पूर्ण,
	अणु"In Filter1R", शून्य, "Mic1 Mux"पूर्ण,
	अणु"In Filter2L", शून्य, "Mic2 Mux"पूर्ण,
	अणु"In Filter2R", शून्य, "Mic2 Mux"पूर्ण,

	अणु"Tone Generator", शून्य, "TONE"पूर्ण,

	अणु"Sidetone Mux", "In Filter1L", "In Filter1L"पूर्ण,
	अणु"Sidetone Mux", "In Filter1R", "In Filter1R"पूर्ण,
	अणु"Sidetone Mux", "In Filter2L", "In Filter2L"पूर्ण,
	अणु"Sidetone Mux", "In Filter2R", "In Filter2R"पूर्ण,
	अणु"Sidetone Filter", शून्य, "Sidetone Mux"पूर्ण,

	DA7218_DMIX_ROUTES("Mixer DAI1L"),
	DA7218_DMIX_ROUTES("Mixer DAI1R"),
	DA7218_DMIX_ROUTES("Mixer DAI2L"),
	DA7218_DMIX_ROUTES("Mixer DAI2R"),

	अणु"DAIOUT", शून्य, "Mixer DAI1L"पूर्ण,
	अणु"DAIOUT", शून्य, "Mixer DAI1R"पूर्ण,
	अणु"DAIOUT", शून्य, "Mixer DAI2L"पूर्ण,
	अणु"DAIOUT", शून्य, "Mixer DAI2R"पूर्ण,

	अणु"DAIOUT", शून्य, "DAI"पूर्ण,

	/* Output paths */
	अणु"DAIIN", शून्य, "DAI"पूर्ण,

	DA7218_DMIX_ROUTES("Mixer Out FilterL"),
	DA7218_DMIX_ROUTES("Mixer Out FilterR"),

	अणु"BiQuad Filter", शून्य, "Mixer Out FilterL"पूर्ण,
	अणु"BiQuad Filter", शून्य, "Mixer Out FilterR"पूर्ण,

	अणु"Out FilterL BiQuad Mux", "Bypass", "Mixer Out FilterL"पूर्ण,
	अणु"Out FilterL BiQuad Mux", "Enabled", "BiQuad Filter"पूर्ण,
	अणु"Out FilterR BiQuad Mux", "Bypass", "Mixer Out FilterR"पूर्ण,
	अणु"Out FilterR BiQuad Mux", "Enabled", "BiQuad Filter"पूर्ण,

	DA7218_DMIX_ST_ROUTES("ST Mixer Out FilterL"),
	DA7218_DMIX_ST_ROUTES("ST Mixer Out FilterR"),

	अणु"Out FilterL", शून्य, "ST Mixer Out FilterL"पूर्ण,
	अणु"Out FilterR", शून्य, "ST Mixer Out FilterR"पूर्ण,

	अणु"Mixout Left PGA", शून्य, "Out FilterL"पूर्ण,
	अणु"Mixout Right PGA", शून्य, "Out FilterR"पूर्ण,

	अणु"Headphone Left PGA", शून्य, "Mixout Left PGA"पूर्ण,
	अणु"Headphone Right PGA", शून्य, "Mixout Right PGA"पूर्ण,

	अणु"HPL", शून्य, "Headphone Left PGA"पूर्ण,
	अणु"HPR", शून्य, "Headphone Right PGA"पूर्ण,

	अणु"HPL", शून्य, "Charge Pump"पूर्ण,
	अणु"HPR", शून्य, "Charge Pump"पूर्ण,
पूर्ण;


/*
 * DAI operations
 */

अटल पूर्णांक da7218_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (da7218->mclk_rate == freq)
		वापस 0;

	अगर ((freq < 2000000) || (freq > 54000000)) अणु
		dev_err(codec_dai->dev, "Unsupported MCLK value %d\n",
			freq);
		वापस -EINVAL;
	पूर्ण

	चयन (clk_id) अणु
	हाल DA7218_CLKSRC_MCLK_SQR:
		snd_soc_component_update_bits(component, DA7218_PLL_CTRL,
				    DA7218_PLL_MCLK_SQR_EN_MASK,
				    DA7218_PLL_MCLK_SQR_EN_MASK);
		अवरोध;
	हाल DA7218_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, DA7218_PLL_CTRL,
				    DA7218_PLL_MCLK_SQR_EN_MASK, 0);
		अवरोध;
	शेष:
		dev_err(codec_dai->dev, "Unknown clock source %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	अगर (da7218->mclk) अणु
		freq = clk_round_rate(da7218->mclk, freq);
		ret = clk_set_rate(da7218->mclk, freq);
		अगर (ret) अणु
			dev_err(codec_dai->dev, "Failed to set clock rate %d\n",
				freq);
			वापस ret;
		पूर्ण
	पूर्ण

	da7218->mclk_rate = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	u8 pll_ctrl, inभाग_bits, inभाग;
	u8 pll_frac_top, pll_frac_bot, pll_पूर्णांकeger;
	u32 freq_ref;
	u64 frac_भाग;

	/* Verअगरy 2MHz - 54MHz MCLK provided, and set input भागider */
	अगर (da7218->mclk_rate < 2000000) अणु
		dev_err(component->dev, "PLL input clock %d below valid range\n",
			da7218->mclk_rate);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (da7218->mclk_rate <= 4500000) अणु
		inभाग_bits = DA7218_PLL_INDIV_2_TO_4_5_MHZ;
		inभाग = DA7218_PLL_INDIV_2_TO_4_5_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7218->mclk_rate <= 9000000) अणु
		inभाग_bits = DA7218_PLL_INDIV_4_5_TO_9_MHZ;
		inभाग = DA7218_PLL_INDIV_4_5_TO_9_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7218->mclk_rate <= 18000000) अणु
		inभाग_bits = DA7218_PLL_INDIV_9_TO_18_MHZ;
		inभाग = DA7218_PLL_INDIV_9_TO_18_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7218->mclk_rate <= 36000000) अणु
		inभाग_bits = DA7218_PLL_INDIV_18_TO_36_MHZ;
		inभाग = DA7218_PLL_INDIV_18_TO_36_MHZ_VAL;
	पूर्ण अन्यथा अगर (da7218->mclk_rate <= 54000000) अणु
		inभाग_bits = DA7218_PLL_INDIV_36_TO_54_MHZ;
		inभाग = DA7218_PLL_INDIV_36_TO_54_MHZ_VAL;
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "PLL input clock %d above valid range\n",
			da7218->mclk_rate);
		वापस -EINVAL;
	पूर्ण
	freq_ref = (da7218->mclk_rate / inभाग);
	pll_ctrl = inभाग_bits;

	/* Configure PLL */
	चयन (source) अणु
	हाल DA7218_SYSCLK_MCLK:
		pll_ctrl |= DA7218_PLL_MODE_BYPASS;
		snd_soc_component_update_bits(component, DA7218_PLL_CTRL,
				    DA7218_PLL_INDIV_MASK |
				    DA7218_PLL_MODE_MASK, pll_ctrl);
		वापस 0;
	हाल DA7218_SYSCLK_PLL:
		pll_ctrl |= DA7218_PLL_MODE_NORMAL;
		अवरोध;
	हाल DA7218_SYSCLK_PLL_SRM:
		pll_ctrl |= DA7218_PLL_MODE_SRM;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid PLL config\n");
		वापस -EINVAL;
	पूर्ण

	/* Calculate भागiders क्रम PLL */
	pll_पूर्णांकeger = fout / freq_ref;
	frac_भाग = (u64)(fout % freq_ref) * 8192ULL;
	करो_भाग(frac_भाग, freq_ref);
	pll_frac_top = (frac_भाग >> DA7218_BYTE_SHIFT) & DA7218_BYTE_MASK;
	pll_frac_bot = (frac_भाग) & DA7218_BYTE_MASK;

	/* Write PLL config & भागiders */
	snd_soc_component_ग_लिखो(component, DA7218_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_ग_लिखो(component, DA7218_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_ग_लिखो(component, DA7218_PLL_INTEGER, pll_पूर्णांकeger);
	snd_soc_component_update_bits(component, DA7218_PLL_CTRL,
			    DA7218_PLL_MODE_MASK | DA7218_PLL_INDIV_MASK,
			    pll_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	u8 dai_clk_mode = 0, dai_ctrl = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		da7218->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		da7218->master = false;
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
			dai_clk_mode |= DA7218_DAI_WCLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			dai_clk_mode |= DA7218_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7218_DAI_WCLK_POL_INV |
					DA7218_DAI_CLK_POL_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			dai_clk_mode |= DA7218_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7218_DAI_WCLK_POL_INV |
					DA7218_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7218_DAI_WCLK_POL_INV;
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
		dai_ctrl |= DA7218_DAI_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dai_ctrl |= DA7218_DAI_FORMAT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		dai_ctrl |= DA7218_DAI_FORMAT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		dai_ctrl |= DA7218_DAI_FORMAT_DSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* By शेष 64 BCLKs per WCLK is supported */
	dai_clk_mode |= DA7218_DAI_BCLKS_PER_WCLK_64;

	snd_soc_component_ग_लिखो(component, DA7218_DAI_CLK_MODE, dai_clk_mode);
	snd_soc_component_update_bits(component, DA7218_DAI_CTRL, DA7218_DAI_FORMAT_MASK,
			    dai_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				   पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 dai_bclks_per_wclk;
	u32 frame_size;

	/* No channels enabled so disable TDM, revert to 64-bit frames */
	अगर (!tx_mask) अणु
		snd_soc_component_update_bits(component, DA7218_DAI_TDM_CTRL,
				    DA7218_DAI_TDM_CH_EN_MASK |
				    DA7218_DAI_TDM_MODE_EN_MASK, 0);
		snd_soc_component_update_bits(component, DA7218_DAI_CLK_MODE,
				    DA7218_DAI_BCLKS_PER_WCLK_MASK,
				    DA7218_DAI_BCLKS_PER_WCLK_64);
		वापस 0;
	पूर्ण

	/* Check we have valid slots */
	अगर (fls(tx_mask) > DA7218_DAI_TDM_MAX_SLOTS) अणु
		dev_err(component->dev, "Invalid number of slots, max = %d\n",
			DA7218_DAI_TDM_MAX_SLOTS);
		वापस -EINVAL;
	पूर्ण

	/* Check we have a valid offset given (first 2 bytes of rx_mask) */
	अगर (rx_mask >> DA7218_2BYTE_SHIFT) अणु
		dev_err(component->dev, "Invalid slot offset, max = %d\n",
			DA7218_2BYTE_MASK);
		वापस -EINVAL;
	पूर्ण

	/* Calculate & validate frame size based on slot info provided. */
	frame_size = slots * slot_width;
	चयन (frame_size) अणु
	हाल 32:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_32;
		अवरोध;
	हाल 64:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_64;
		अवरोध;
	हाल 128:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_128;
		अवरोध;
	हाल 256:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_256;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid frame size\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, DA7218_DAI_CLK_MODE,
			    DA7218_DAI_BCLKS_PER_WCLK_MASK,
			    dai_bclks_per_wclk);
	snd_soc_component_ग_लिखो(component, DA7218_DAI_OFFSET_LOWER,
		      (rx_mask & DA7218_BYTE_MASK));
	snd_soc_component_ग_लिखो(component, DA7218_DAI_OFFSET_UPPER,
		      ((rx_mask >> DA7218_BYTE_SHIFT) & DA7218_BYTE_MASK));
	snd_soc_component_update_bits(component, DA7218_DAI_TDM_CTRL,
			    DA7218_DAI_TDM_CH_EN_MASK |
			    DA7218_DAI_TDM_MODE_EN_MASK,
			    (tx_mask << DA7218_DAI_TDM_CH_EN_SHIFT) |
			    DA7218_DAI_TDM_MODE_EN_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 dai_ctrl = 0, fs;
	अचिन्हित पूर्णांक channels;

	चयन (params_width(params)) अणु
	हाल 16:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S16_LE;
		अवरोध;
	हाल 20:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S20_LE;
		अवरोध;
	हाल 24:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S24_LE;
		अवरोध;
	हाल 32:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S32_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	channels = params_channels(params);
	अगर ((channels < 1) || (channels > DA7218_DAI_CH_NUM_MAX)) अणु
		dev_err(component->dev,
			"Invalid number of channels, only 1 to %d supported\n",
			DA7218_DAI_CH_NUM_MAX);
		वापस -EINVAL;
	पूर्ण
	dai_ctrl |= channels << DA7218_DAI_CH_NUM_SHIFT;

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs = DA7218_SR_8000;
		अवरोध;
	हाल 11025:
		fs = DA7218_SR_11025;
		अवरोध;
	हाल 12000:
		fs = DA7218_SR_12000;
		अवरोध;
	हाल 16000:
		fs = DA7218_SR_16000;
		अवरोध;
	हाल 22050:
		fs = DA7218_SR_22050;
		अवरोध;
	हाल 24000:
		fs = DA7218_SR_24000;
		अवरोध;
	हाल 32000:
		fs = DA7218_SR_32000;
		अवरोध;
	हाल 44100:
		fs = DA7218_SR_44100;
		अवरोध;
	हाल 48000:
		fs = DA7218_SR_48000;
		अवरोध;
	हाल 88200:
		fs = DA7218_SR_88200;
		अवरोध;
	हाल 96000:
		fs = DA7218_SR_96000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, DA7218_DAI_CTRL,
			    DA7218_DAI_WORD_LENGTH_MASK | DA7218_DAI_CH_NUM_MASK,
			    dai_ctrl);
	/* SRs tied क्रम ADCs and DACs. */
	snd_soc_component_ग_लिखो(component, DA7218_SR,
		      (fs << DA7218_SR_DAC_SHIFT) | (fs << DA7218_SR_ADC_SHIFT));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops da7218_dai_ops = अणु
	.hw_params	= da7218_hw_params,
	.set_sysclk	= da7218_set_dai_sysclk,
	.set_pll	= da7218_set_dai_pll,
	.set_fmt	= da7218_set_dai_fmt,
	.set_tdm_slot	= da7218_set_dai_tdm_slot,
पूर्ण;

#घोषणा DA7218_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver da7218_dai = अणु
	.name = "da7218-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 4,	/* Only 2 channels of data */
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA7218_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA7218_FORMATS,
	पूर्ण,
	.ops = &da7218_dai_ops,
	.symmetric_rate = 1,
	.symmetric_channels = 1,
	.symmetric_sample_bits = 1,
पूर्ण;


/*
 * HP Detect
 */

पूर्णांक da7218_hpldet(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	अगर (da7218->dev_id == DA7217_DEV_ID)
		वापस -EINVAL;

	da7218->jack = jack;
	snd_soc_component_update_bits(component, DA7218_HPLDET_JACK,
			    DA7218_HPLDET_JACK_EN_MASK,
			    jack ? DA7218_HPLDET_JACK_EN_MASK : 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(da7218_hpldet);

अटल व्योम da7218_micldet_irq(काष्ठा snd_soc_component *component)
अणु
	अक्षर *envp[] = अणु
		"EVENT=MIC_LEVEL_DETECT",
		शून्य,
	पूर्ण;

	kobject_uevent_env(&component->dev->kobj, KOBJ_CHANGE, envp);
पूर्ण

अटल व्योम da7218_hpldet_irq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	u8 jack_status;
	पूर्णांक report;

	jack_status = snd_soc_component_पढ़ो(component, DA7218_EVENT_STATUS);

	अगर (jack_status & DA7218_HPLDET_JACK_STS_MASK)
		report = SND_JACK_HEADPHONE;
	अन्यथा
		report = 0;

	snd_soc_jack_report(da7218->jack, report, SND_JACK_HEADPHONE);
पूर्ण

/*
 * IRQ
 */

अटल irqवापस_t da7218_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;
	u8 status;

	/* Read IRQ status reg */
	status = snd_soc_component_पढ़ो(component, DA7218_EVENT);
	अगर (!status)
		वापस IRQ_NONE;

	/* Mic level detect */
	अगर (status & DA7218_LVL_DET_EVENT_MASK)
		da7218_micldet_irq(component);

	/* HP detect */
	अगर (status & DA7218_HPLDET_JACK_EVENT_MASK)
		da7218_hpldet_irq(component);

	/* Clear पूर्णांकerrupts */
	snd_soc_component_ग_लिखो(component, DA7218_EVENT, status);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * DT
 */

अटल स्थिर काष्ठा of_device_id da7218_of_match[] = अणु
	अणु .compatible = "dlg,da7217", .data = (व्योम *) DA7217_DEV_ID पूर्ण,
	अणु .compatible = "dlg,da7218", .data = (व्योम *) DA7218_DEV_ID पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da7218_of_match);

अटल अंतरभूत पूर्णांक da7218_of_get_id(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *id = of_match_device(da7218_of_match, dev);

	अगर (id)
		वापस (uपूर्णांकptr_t)id->data;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल क्रमागत da7218_micbias_voltage
	da7218_of_micbias_lvl(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 1200:
		वापस DA7218_MICBIAS_1_2V;
	हाल 1600:
		वापस DA7218_MICBIAS_1_6V;
	हाल 1800:
		वापस DA7218_MICBIAS_1_8V;
	हाल 2000:
		वापस DA7218_MICBIAS_2_0V;
	हाल 2200:
		वापस DA7218_MICBIAS_2_2V;
	हाल 2400:
		वापस DA7218_MICBIAS_2_4V;
	हाल 2600:
		वापस DA7218_MICBIAS_2_6V;
	हाल 2800:
		वापस DA7218_MICBIAS_2_8V;
	हाल 3000:
		वापस DA7218_MICBIAS_3_0V;
	शेष:
		dev_warn(component->dev, "Invalid micbias level");
		वापस DA7218_MICBIAS_1_6V;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_mic_amp_in_sel
	da7218_of_mic_amp_in_sel(काष्ठा snd_soc_component *component, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "diff")) अणु
		वापस DA7218_MIC_AMP_IN_SEL_DIFF;
	पूर्ण अन्यथा अगर (!म_भेद(str, "se_p")) अणु
		वापस DA7218_MIC_AMP_IN_SEL_SE_P;
	पूर्ण अन्यथा अगर (!म_भेद(str, "se_n")) अणु
		वापस DA7218_MIC_AMP_IN_SEL_SE_N;
	पूर्ण अन्यथा अणु
		dev_warn(component->dev, "Invalid mic input type selection");
		वापस DA7218_MIC_AMP_IN_SEL_DIFF;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_dmic_data_sel
	da7218_of_dmic_data_sel(काष्ठा snd_soc_component *component, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "lrise_rfall")) अणु
		वापस DA7218_DMIC_DATA_LRISE_RFALL;
	पूर्ण अन्यथा अगर (!म_भेद(str, "lfall_rrise")) अणु
		वापस DA7218_DMIC_DATA_LFALL_RRISE;
	पूर्ण अन्यथा अणु
		dev_warn(component->dev, "Invalid DMIC data type selection");
		वापस DA7218_DMIC_DATA_LRISE_RFALL;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_dmic_samplephase
	da7218_of_dmic_samplephase(काष्ठा snd_soc_component *component, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "on_clkedge")) अणु
		वापस DA7218_DMIC_SAMPLE_ON_CLKEDGE;
	पूर्ण अन्यथा अगर (!म_भेद(str, "between_clkedge")) अणु
		वापस DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE;
	पूर्ण अन्यथा अणु
		dev_warn(component->dev, "Invalid DMIC sample phase");
		वापस DA7218_DMIC_SAMPLE_ON_CLKEDGE;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_dmic_clk_rate
	da7218_of_dmic_clkrate(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 1500000:
		वापस DA7218_DMIC_CLK_1_5MHZ;
	हाल 3000000:
		वापस DA7218_DMIC_CLK_3_0MHZ;
	शेष:
		dev_warn(component->dev, "Invalid DMIC clock rate");
		वापस DA7218_DMIC_CLK_3_0MHZ;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_hpldet_jack_rate
	da7218_of_jack_rate(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 5:
		वापस DA7218_HPLDET_JACK_RATE_5US;
	हाल 10:
		वापस DA7218_HPLDET_JACK_RATE_10US;
	हाल 20:
		वापस DA7218_HPLDET_JACK_RATE_20US;
	हाल 40:
		वापस DA7218_HPLDET_JACK_RATE_40US;
	हाल 80:
		वापस DA7218_HPLDET_JACK_RATE_80US;
	हाल 160:
		वापस DA7218_HPLDET_JACK_RATE_160US;
	हाल 320:
		वापस DA7218_HPLDET_JACK_RATE_320US;
	हाल 640:
		वापस DA7218_HPLDET_JACK_RATE_640US;
	शेष:
		dev_warn(component->dev, "Invalid jack detect rate");
		वापस DA7218_HPLDET_JACK_RATE_40US;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_hpldet_jack_debounce
	da7218_of_jack_debounce(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 0:
		वापस DA7218_HPLDET_JACK_DEBOUNCE_OFF;
	हाल 2:
		वापस DA7218_HPLDET_JACK_DEBOUNCE_2;
	हाल 3:
		वापस DA7218_HPLDET_JACK_DEBOUNCE_3;
	हाल 4:
		वापस DA7218_HPLDET_JACK_DEBOUNCE_4;
	शेष:
		dev_warn(component->dev, "Invalid jack debounce");
		वापस DA7218_HPLDET_JACK_DEBOUNCE_2;
	पूर्ण
पूर्ण

अटल क्रमागत da7218_hpldet_jack_thr
	da7218_of_jack_thr(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 84:
		वापस DA7218_HPLDET_JACK_THR_84PCT;
	हाल 88:
		वापस DA7218_HPLDET_JACK_THR_88PCT;
	हाल 92:
		वापस DA7218_HPLDET_JACK_THR_92PCT;
	हाल 96:
		वापस DA7218_HPLDET_JACK_THR_96PCT;
	शेष:
		dev_warn(component->dev, "Invalid jack threshold level");
		वापस DA7218_HPLDET_JACK_THR_84PCT;
	पूर्ण
पूर्ण

अटल काष्ठा da7218_pdata *da7218_of_to_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा device_node *np = component->dev->of_node;
	काष्ठा device_node *hpldet_np;
	काष्ठा da7218_pdata *pdata;
	काष्ठा da7218_hpldet_pdata *hpldet_pdata;
	स्थिर अक्षर *of_str;
	u32 of_val32;

	pdata = devm_kzalloc(component->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	अगर (of_property_पढ़ो_u32(np, "dlg,micbias1-lvl-millivolt", &of_val32) >= 0)
		pdata->micbias1_lvl = da7218_of_micbias_lvl(component, of_val32);
	अन्यथा
		pdata->micbias1_lvl = DA7218_MICBIAS_1_6V;

	अगर (of_property_पढ़ो_u32(np, "dlg,micbias2-lvl-millivolt", &of_val32) >= 0)
		pdata->micbias2_lvl = da7218_of_micbias_lvl(component, of_val32);
	अन्यथा
		pdata->micbias2_lvl = DA7218_MICBIAS_1_6V;

	अगर (!of_property_पढ़ो_string(np, "dlg,mic1-amp-in-sel", &of_str))
		pdata->mic1_amp_in_sel =
			da7218_of_mic_amp_in_sel(component, of_str);
	अन्यथा
		pdata->mic1_amp_in_sel = DA7218_MIC_AMP_IN_SEL_DIFF;

	अगर (!of_property_पढ़ो_string(np, "dlg,mic2-amp-in-sel", &of_str))
		pdata->mic2_amp_in_sel =
			da7218_of_mic_amp_in_sel(component, of_str);
	अन्यथा
		pdata->mic2_amp_in_sel = DA7218_MIC_AMP_IN_SEL_DIFF;

	अगर (!of_property_पढ़ो_string(np, "dlg,dmic1-data-sel", &of_str))
		pdata->dmic1_data_sel =	da7218_of_dmic_data_sel(component, of_str);
	अन्यथा
		pdata->dmic1_data_sel =	DA7218_DMIC_DATA_LRISE_RFALL;

	अगर (!of_property_पढ़ो_string(np, "dlg,dmic1-samplephase", &of_str))
		pdata->dmic1_samplephase =
			da7218_of_dmic_samplephase(component, of_str);
	अन्यथा
		pdata->dmic1_samplephase = DA7218_DMIC_SAMPLE_ON_CLKEDGE;

	अगर (of_property_पढ़ो_u32(np, "dlg,dmic1-clkrate-hz", &of_val32) >= 0)
		pdata->dmic1_clk_rate = da7218_of_dmic_clkrate(component, of_val32);
	अन्यथा
		pdata->dmic1_clk_rate = DA7218_DMIC_CLK_3_0MHZ;

	अगर (!of_property_पढ़ो_string(np, "dlg,dmic2-data-sel", &of_str))
		pdata->dmic2_data_sel = da7218_of_dmic_data_sel(component, of_str);
	अन्यथा
		pdata->dmic2_data_sel =	DA7218_DMIC_DATA_LRISE_RFALL;

	अगर (!of_property_पढ़ो_string(np, "dlg,dmic2-samplephase", &of_str))
		pdata->dmic2_samplephase =
			da7218_of_dmic_samplephase(component, of_str);
	अन्यथा
		pdata->dmic2_samplephase = DA7218_DMIC_SAMPLE_ON_CLKEDGE;

	अगर (of_property_पढ़ो_u32(np, "dlg,dmic2-clkrate-hz", &of_val32) >= 0)
		pdata->dmic2_clk_rate = da7218_of_dmic_clkrate(component, of_val32);
	अन्यथा
		pdata->dmic2_clk_rate = DA7218_DMIC_CLK_3_0MHZ;

	अगर (da7218->dev_id == DA7217_DEV_ID) अणु
		अगर (of_property_पढ़ो_bool(np, "dlg,hp-diff-single-supply"))
			pdata->hp_dअगरf_single_supply = true;
	पूर्ण

	अगर (da7218->dev_id == DA7218_DEV_ID) अणु
		hpldet_np = of_get_child_by_name(np, "da7218_hpldet");
		अगर (!hpldet_np)
			वापस pdata;

		hpldet_pdata = devm_kzalloc(component->dev, माप(*hpldet_pdata),
					    GFP_KERNEL);
		अगर (!hpldet_pdata) अणु
			of_node_put(hpldet_np);
			वापस pdata;
		पूर्ण
		pdata->hpldet_pdata = hpldet_pdata;

		अगर (of_property_पढ़ो_u32(hpldet_np, "dlg,jack-rate-us",
					 &of_val32) >= 0)
			hpldet_pdata->jack_rate =
				da7218_of_jack_rate(component, of_val32);
		अन्यथा
			hpldet_pdata->jack_rate = DA7218_HPLDET_JACK_RATE_40US;

		अगर (of_property_पढ़ो_u32(hpldet_np, "dlg,jack-debounce",
					 &of_val32) >= 0)
			hpldet_pdata->jack_debounce =
				da7218_of_jack_debounce(component, of_val32);
		अन्यथा
			hpldet_pdata->jack_debounce =
				DA7218_HPLDET_JACK_DEBOUNCE_2;

		अगर (of_property_पढ़ो_u32(hpldet_np, "dlg,jack-threshold-pct",
					 &of_val32) >= 0)
			hpldet_pdata->jack_thr =
				da7218_of_jack_thr(component, of_val32);
		अन्यथा
			hpldet_pdata->jack_thr = DA7218_HPLDET_JACK_THR_84PCT;

		अगर (of_property_पढ़ो_bool(hpldet_np, "dlg,comp-inv"))
			hpldet_pdata->comp_inv = true;

		अगर (of_property_पढ़ो_bool(hpldet_np, "dlg,hyst"))
			hpldet_pdata->hyst = true;

		अगर (of_property_पढ़ो_bool(hpldet_np, "dlg,discharge"))
			hpldet_pdata->disअक्षरge = true;

		of_node_put(hpldet_np);
	पूर्ण

	वापस pdata;
पूर्ण


/*
 * Codec driver functions
 */

अटल पूर्णांक da7218_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Enable MCLK क्रम transition to ON state */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY) अणु
			अगर (da7218->mclk) अणु
				ret = clk_prepare_enable(da7218->mclk);
				अगर (ret) अणु
					dev_err(component->dev, "Failed to enable mclk\n");
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण

		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Master bias */
			snd_soc_component_update_bits(component, DA7218_REFERENCES,
					    DA7218_BIAS_EN_MASK,
					    DA7218_BIAS_EN_MASK);

			/* Internal LDO */
			snd_soc_component_update_bits(component, DA7218_LDO_CTRL,
					    DA7218_LDO_EN_MASK,
					    DA7218_LDO_EN_MASK);
		पूर्ण अन्यथा अणु
			/* Remove MCLK */
			अगर (da7218->mclk)
				clk_disable_unprepare(da7218->mclk);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Only disable अगर jack detection disabled */
		अगर (!da7218->jack) अणु
			/* Internal LDO */
			snd_soc_component_update_bits(component, DA7218_LDO_CTRL,
					    DA7218_LDO_EN_MASK, 0);

			/* Master bias */
			snd_soc_component_update_bits(component, DA7218_REFERENCES,
					    DA7218_BIAS_EN_MASK, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *da7218_supply_names[DA7218_NUM_SUPPLIES] = अणु
	[DA7218_SUPPLY_VDD] = "VDD",
	[DA7218_SUPPLY_VDDMIC] = "VDDMIC",
	[DA7218_SUPPLY_VDDIO] = "VDDIO",
पूर्ण;

अटल पूर्णांक da7218_handle_supplies(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा regulator *vddio;
	u8 io_voltage_lvl = DA7218_IO_VOLTAGE_LEVEL_2_5V_3_6V;
	पूर्णांक i, ret;

	/* Get required supplies */
	क्रम (i = 0; i < DA7218_NUM_SUPPLIES; ++i)
		da7218->supplies[i].supply = da7218_supply_names[i];

	ret = devm_regulator_bulk_get(component->dev, DA7218_NUM_SUPPLIES,
				      da7218->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to get supplies\n");
		वापस ret;
	पूर्ण

	/* Determine VDDIO voltage provided */
	vddio = da7218->supplies[DA7218_SUPPLY_VDDIO].consumer;
	ret = regulator_get_voltage(vddio);
	अगर (ret < 1500000)
		dev_warn(component->dev, "Invalid VDDIO voltage\n");
	अन्यथा अगर (ret < 2500000)
		io_voltage_lvl = DA7218_IO_VOLTAGE_LEVEL_1_5V_2_5V;

	/* Enable मुख्य supplies */
	ret = regulator_bulk_enable(DA7218_NUM_SUPPLIES, da7218->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to enable supplies\n");
		वापस ret;
	पूर्ण

	/* Ensure device in active mode */
	snd_soc_component_ग_लिखो(component, DA7218_SYSTEM_ACTIVE, DA7218_SYSTEM_ACTIVE_MASK);

	/* Update IO voltage level range */
	snd_soc_component_ग_लिखो(component, DA7218_IO_CTRL, io_voltage_lvl);

	वापस 0;
पूर्ण

अटल व्योम da7218_handle_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	काष्ठा da7218_pdata *pdata = da7218->pdata;

	अगर (pdata) अणु
		u8 micbias_lvl = 0, dmic_cfg = 0;

		/* Mic Bias voltages */
		चयन (pdata->micbias1_lvl) अणु
		हाल DA7218_MICBIAS_1_2V:
			micbias_lvl |= DA7218_MICBIAS_1_LP_MODE_MASK;
			अवरोध;
		हाल DA7218_MICBIAS_1_6V:
		हाल DA7218_MICBIAS_1_8V:
		हाल DA7218_MICBIAS_2_0V:
		हाल DA7218_MICBIAS_2_2V:
		हाल DA7218_MICBIAS_2_4V:
		हाल DA7218_MICBIAS_2_6V:
		हाल DA7218_MICBIAS_2_8V:
		हाल DA7218_MICBIAS_3_0V:
			micbias_lvl |= (pdata->micbias1_lvl <<
					DA7218_MICBIAS_1_LEVEL_SHIFT);
			अवरोध;
		पूर्ण

		चयन (pdata->micbias2_lvl) अणु
		हाल DA7218_MICBIAS_1_2V:
			micbias_lvl |= DA7218_MICBIAS_2_LP_MODE_MASK;
			अवरोध;
		हाल DA7218_MICBIAS_1_6V:
		हाल DA7218_MICBIAS_1_8V:
		हाल DA7218_MICBIAS_2_0V:
		हाल DA7218_MICBIAS_2_2V:
		हाल DA7218_MICBIAS_2_4V:
		हाल DA7218_MICBIAS_2_6V:
		हाल DA7218_MICBIAS_2_8V:
		हाल DA7218_MICBIAS_3_0V:
			micbias_lvl |= (pdata->micbias2_lvl <<
					 DA7218_MICBIAS_2_LEVEL_SHIFT);
			अवरोध;
		पूर्ण

		snd_soc_component_ग_लिखो(component, DA7218_MICBIAS_CTRL, micbias_lvl);

		/* Mic */
		चयन (pdata->mic1_amp_in_sel) अणु
		हाल DA7218_MIC_AMP_IN_SEL_DIFF:
		हाल DA7218_MIC_AMP_IN_SEL_SE_P:
		हाल DA7218_MIC_AMP_IN_SEL_SE_N:
			snd_soc_component_ग_लिखो(component, DA7218_MIC_1_SELECT,
				      pdata->mic1_amp_in_sel);
			अवरोध;
		पूर्ण

		चयन (pdata->mic2_amp_in_sel) अणु
		हाल DA7218_MIC_AMP_IN_SEL_DIFF:
		हाल DA7218_MIC_AMP_IN_SEL_SE_P:
		हाल DA7218_MIC_AMP_IN_SEL_SE_N:
			snd_soc_component_ग_लिखो(component, DA7218_MIC_2_SELECT,
				      pdata->mic2_amp_in_sel);
			अवरोध;
		पूर्ण

		/* DMic */
		चयन (pdata->dmic1_data_sel) अणु
		हाल DA7218_DMIC_DATA_LFALL_RRISE:
		हाल DA7218_DMIC_DATA_LRISE_RFALL:
			dmic_cfg |= (pdata->dmic1_data_sel <<
				     DA7218_DMIC_1_DATA_SEL_SHIFT);
			अवरोध;
		पूर्ण

		चयन (pdata->dmic1_samplephase) अणु
		हाल DA7218_DMIC_SAMPLE_ON_CLKEDGE:
		हाल DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE:
			dmic_cfg |= (pdata->dmic1_samplephase <<
				     DA7218_DMIC_1_SAMPLEPHASE_SHIFT);
			अवरोध;
		पूर्ण

		चयन (pdata->dmic1_clk_rate) अणु
		हाल DA7218_DMIC_CLK_3_0MHZ:
		हाल DA7218_DMIC_CLK_1_5MHZ:
			dmic_cfg |= (pdata->dmic1_clk_rate <<
				     DA7218_DMIC_1_CLK_RATE_SHIFT);
			अवरोध;
		पूर्ण

		snd_soc_component_update_bits(component, DA7218_DMIC_1_CTRL,
				    DA7218_DMIC_1_DATA_SEL_MASK |
				    DA7218_DMIC_1_SAMPLEPHASE_MASK |
				    DA7218_DMIC_1_CLK_RATE_MASK, dmic_cfg);

		dmic_cfg = 0;
		चयन (pdata->dmic2_data_sel) अणु
		हाल DA7218_DMIC_DATA_LFALL_RRISE:
		हाल DA7218_DMIC_DATA_LRISE_RFALL:
			dmic_cfg |= (pdata->dmic2_data_sel <<
				     DA7218_DMIC_2_DATA_SEL_SHIFT);
			अवरोध;
		पूर्ण

		चयन (pdata->dmic2_samplephase) अणु
		हाल DA7218_DMIC_SAMPLE_ON_CLKEDGE:
		हाल DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE:
			dmic_cfg |= (pdata->dmic2_samplephase <<
				     DA7218_DMIC_2_SAMPLEPHASE_SHIFT);
			अवरोध;
		पूर्ण

		चयन (pdata->dmic2_clk_rate) अणु
		हाल DA7218_DMIC_CLK_3_0MHZ:
		हाल DA7218_DMIC_CLK_1_5MHZ:
			dmic_cfg |= (pdata->dmic2_clk_rate <<
				     DA7218_DMIC_2_CLK_RATE_SHIFT);
			अवरोध;
		पूर्ण

		snd_soc_component_update_bits(component, DA7218_DMIC_2_CTRL,
				    DA7218_DMIC_2_DATA_SEL_MASK |
				    DA7218_DMIC_2_SAMPLEPHASE_MASK |
				    DA7218_DMIC_2_CLK_RATE_MASK, dmic_cfg);

		/* DA7217 Specअगरic */
		अगर (da7218->dev_id == DA7217_DEV_ID) अणु
			da7218->hp_single_supply =
				pdata->hp_dअगरf_single_supply;

			अगर (da7218->hp_single_supply) अणु
				snd_soc_component_ग_लिखो(component, DA7218_HP_DIFF_UNLOCK,
					      DA7218_HP_DIFF_UNLOCK_VAL);
				snd_soc_component_update_bits(component, DA7218_HP_DIFF_CTRL,
						    DA7218_HP_AMP_SINGLE_SUPPLY_EN_MASK,
						    DA7218_HP_AMP_SINGLE_SUPPLY_EN_MASK);
			पूर्ण
		पूर्ण

		/* DA7218 Specअगरic */
		अगर ((da7218->dev_id == DA7218_DEV_ID) &&
		    (pdata->hpldet_pdata)) अणु
			काष्ठा da7218_hpldet_pdata *hpldet_pdata =
				pdata->hpldet_pdata;
			u8 hpldet_cfg = 0;

			चयन (hpldet_pdata->jack_rate) अणु
			हाल DA7218_HPLDET_JACK_RATE_5US:
			हाल DA7218_HPLDET_JACK_RATE_10US:
			हाल DA7218_HPLDET_JACK_RATE_20US:
			हाल DA7218_HPLDET_JACK_RATE_40US:
			हाल DA7218_HPLDET_JACK_RATE_80US:
			हाल DA7218_HPLDET_JACK_RATE_160US:
			हाल DA7218_HPLDET_JACK_RATE_320US:
			हाल DA7218_HPLDET_JACK_RATE_640US:
				hpldet_cfg |=
					(hpldet_pdata->jack_rate <<
					 DA7218_HPLDET_JACK_RATE_SHIFT);
				अवरोध;
			पूर्ण

			चयन (hpldet_pdata->jack_debounce) अणु
			हाल DA7218_HPLDET_JACK_DEBOUNCE_OFF:
			हाल DA7218_HPLDET_JACK_DEBOUNCE_2:
			हाल DA7218_HPLDET_JACK_DEBOUNCE_3:
			हाल DA7218_HPLDET_JACK_DEBOUNCE_4:
				hpldet_cfg |=
					(hpldet_pdata->jack_debounce <<
					 DA7218_HPLDET_JACK_DEBOUNCE_SHIFT);
				अवरोध;
			पूर्ण

			चयन (hpldet_pdata->jack_thr) अणु
			हाल DA7218_HPLDET_JACK_THR_84PCT:
			हाल DA7218_HPLDET_JACK_THR_88PCT:
			हाल DA7218_HPLDET_JACK_THR_92PCT:
			हाल DA7218_HPLDET_JACK_THR_96PCT:
				hpldet_cfg |=
					(hpldet_pdata->jack_thr <<
					 DA7218_HPLDET_JACK_THR_SHIFT);
				अवरोध;
			पूर्ण
			snd_soc_component_update_bits(component, DA7218_HPLDET_JACK,
					    DA7218_HPLDET_JACK_RATE_MASK |
					    DA7218_HPLDET_JACK_DEBOUNCE_MASK |
					    DA7218_HPLDET_JACK_THR_MASK,
					    hpldet_cfg);

			hpldet_cfg = 0;
			अगर (hpldet_pdata->comp_inv)
				hpldet_cfg |= DA7218_HPLDET_COMP_INV_MASK;

			अगर (hpldet_pdata->hyst)
				hpldet_cfg |= DA7218_HPLDET_HYST_EN_MASK;

			अगर (hpldet_pdata->disअक्षरge)
				hpldet_cfg |= DA7218_HPLDET_DISCHARGE_EN_MASK;

			snd_soc_component_ग_लिखो(component, DA7218_HPLDET_CTRL, hpldet_cfg);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक da7218_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	/* Regulator configuration */
	ret = da7218_handle_supplies(component);
	अगर (ret)
		वापस ret;

	/* Handle DT/Platक्रमm data */
	अगर (component->dev->of_node)
		da7218->pdata = da7218_of_to_pdata(component);
	अन्यथा
		da7218->pdata = dev_get_platdata(component->dev);

	da7218_handle_pdata(component);

	/* Check अगर MCLK provided, अगर not the घड़ी is शून्य */
	da7218->mclk = devm_clk_get(component->dev, "mclk");
	अगर (IS_ERR(da7218->mclk)) अणु
		अगर (PTR_ERR(da7218->mclk) != -ENOENT) अणु
			ret = PTR_ERR(da7218->mclk);
			जाओ err_disable_reg;
		पूर्ण अन्यथा अणु
			da7218->mclk = शून्य;
		पूर्ण
	पूर्ण

	/* Default PC to मुक्त-running */
	snd_soc_component_ग_लिखो(component, DA7218_PC_COUNT, DA7218_PC_FREERUN_MASK);

	/*
	 * Default Output Filter mixers to off otherwise DAPM will घातer
	 * Mic to HP passthrough paths by शेष at startup.
	 */
	snd_soc_component_ग_लिखो(component, DA7218_DROUTING_OUTFILT_1L, 0);
	snd_soc_component_ग_लिखो(component, DA7218_DROUTING_OUTFILT_1R, 0);

	/* Default CP to normal load, घातer mode */
	snd_soc_component_update_bits(component, DA7218_CP_CTRL,
			    DA7218_CP_SMALL_SWITCH_FREQ_EN_MASK, 0);

	/* Default gain ramping */
	snd_soc_component_update_bits(component, DA7218_MIXIN_1_CTRL,
			    DA7218_MIXIN_1_AMP_RAMP_EN_MASK,
			    DA7218_MIXIN_1_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIXIN_2_CTRL,
			    DA7218_MIXIN_2_AMP_RAMP_EN_MASK,
			    DA7218_MIXIN_2_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_1L_FILTER_CTRL,
			    DA7218_IN_1L_RAMP_EN_MASK,
			    DA7218_IN_1L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_1R_FILTER_CTRL,
			    DA7218_IN_1R_RAMP_EN_MASK,
			    DA7218_IN_1R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2L_FILTER_CTRL,
			    DA7218_IN_2L_RAMP_EN_MASK,
			    DA7218_IN_2L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2R_FILTER_CTRL,
			    DA7218_IN_2R_RAMP_EN_MASK,
			    DA7218_IN_2R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_DGS_GAIN_CTRL,
			    DA7218_DGS_RAMP_EN_MASK, DA7218_DGS_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_OUT_1L_FILTER_CTRL,
			    DA7218_OUT_1L_RAMP_EN_MASK,
			    DA7218_OUT_1L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_OUT_1R_FILTER_CTRL,
			    DA7218_OUT_1R_RAMP_EN_MASK,
			    DA7218_OUT_1R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_HP_L_CTRL,
			    DA7218_HP_L_AMP_RAMP_EN_MASK,
			    DA7218_HP_L_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_HP_R_CTRL,
			    DA7218_HP_R_AMP_RAMP_EN_MASK,
			    DA7218_HP_R_AMP_RAMP_EN_MASK);

	/* Default infinite tone gen, start/stop by Kcontrol */
	snd_soc_component_ग_लिखो(component, DA7218_TONE_GEN_CYCLES, DA7218_BEEP_CYCLES_MASK);

	/* DA7217 specअगरic config */
	अगर (da7218->dev_id == DA7217_DEV_ID) अणु
		snd_soc_component_update_bits(component, DA7218_HP_DIFF_CTRL,
				    DA7218_HP_AMP_DIFF_MODE_EN_MASK,
				    DA7218_HP_AMP_DIFF_MODE_EN_MASK);

		/* Only DA7218 supports HP detect, mask off क्रम DA7217 */
		snd_soc_component_ग_लिखो(component, DA7218_EVENT_MASK,
			      DA7218_HPLDET_JACK_EVENT_IRQ_MSK_MASK);
	पूर्ण

	अगर (da7218->irq) अणु
		ret = devm_request_thपढ़ोed_irq(component->dev, da7218->irq, शून्य,
						da7218_irq_thपढ़ो,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"da7218", component);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to request IRQ %d: %d\n",
				da7218->irq, ret);
			जाओ err_disable_reg;
		पूर्ण

	पूर्ण

	वापस 0;

err_disable_reg:
	regulator_bulk_disable(DA7218_NUM_SUPPLIES, da7218->supplies);

	वापस ret;
पूर्ण

अटल व्योम da7218_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	regulator_bulk_disable(DA7218_NUM_SUPPLIES, da7218->supplies);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक da7218_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	da7218_set_bias_level(component, SND_SOC_BIAS_OFF);

	/* Put device पूर्णांकo standby mode अगर jack detection disabled */
	अगर (!da7218->jack)
		snd_soc_component_ग_लिखो(component, DA7218_SYSTEM_ACTIVE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक da7218_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	/* Put device पूर्णांकo active mode अगर previously moved to standby */
	अगर (!da7218->jack)
		snd_soc_component_ग_लिखो(component, DA7218_SYSTEM_ACTIVE,
			      DA7218_SYSTEM_ACTIVE_MASK);

	da7218_set_bias_level(component, SND_SOC_BIAS_STANDBY);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा da7218_suspend शून्य
#घोषणा da7218_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_da7218 = अणु
	.probe			= da7218_probe,
	.हटाओ			= da7218_हटाओ,
	.suspend		= da7218_suspend,
	.resume			= da7218_resume,
	.set_bias_level		= da7218_set_bias_level,
	.controls		= da7218_snd_controls,
	.num_controls		= ARRAY_SIZE(da7218_snd_controls),
	.dapm_widमाला_लो		= da7218_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(da7218_dapm_widमाला_लो),
	.dapm_routes		= da7218_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(da7218_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;


/*
 * Regmap configs
 */

अटल काष्ठा reg_शेष da7218_reg_शेषs[] = अणु
	अणु DA7218_SYSTEM_ACTIVE, 0x00 पूर्ण,
	अणु DA7218_CIF_CTRL, 0x00 पूर्ण,
	अणु DA7218_SPARE1, 0x00 पूर्ण,
	अणु DA7218_SR, 0xAA पूर्ण,
	अणु DA7218_PC_COUNT, 0x02 पूर्ण,
	अणु DA7218_GAIN_RAMP_CTRL, 0x00 पूर्ण,
	अणु DA7218_CIF_TIMEOUT_CTRL, 0x01 पूर्ण,
	अणु DA7218_SYSTEM_MODES_INPUT, 0x00 पूर्ण,
	अणु DA7218_SYSTEM_MODES_OUTPUT, 0x00 पूर्ण,
	अणु DA7218_IN_1L_FILTER_CTRL, 0x00 पूर्ण,
	अणु DA7218_IN_1R_FILTER_CTRL, 0x00 पूर्ण,
	अणु DA7218_IN_2L_FILTER_CTRL, 0x00 पूर्ण,
	अणु DA7218_IN_2R_FILTER_CTRL, 0x00 पूर्ण,
	अणु DA7218_OUT_1L_FILTER_CTRL, 0x40 पूर्ण,
	अणु DA7218_OUT_1R_FILTER_CTRL, 0x40 पूर्ण,
	अणु DA7218_OUT_1_HPF_FILTER_CTRL, 0x80 पूर्ण,
	अणु DA7218_OUT_1_EQ_12_FILTER_CTRL, 0x77 पूर्ण,
	अणु DA7218_OUT_1_EQ_34_FILTER_CTRL, 0x77 पूर्ण,
	अणु DA7218_OUT_1_EQ_5_FILTER_CTRL, 0x07 पूर्ण,
	अणु DA7218_OUT_1_BIQ_5STAGE_CTRL, 0x40 पूर्ण,
	अणु DA7218_OUT_1_BIQ_5STAGE_DATA, 0x00 पूर्ण,
	अणु DA7218_OUT_1_BIQ_5STAGE_ADDR, 0x00 पूर्ण,
	अणु DA7218_MIXIN_1_CTRL, 0x48 पूर्ण,
	अणु DA7218_MIXIN_1_GAIN, 0x03 पूर्ण,
	अणु DA7218_MIXIN_2_CTRL, 0x48 पूर्ण,
	अणु DA7218_MIXIN_2_GAIN, 0x03 पूर्ण,
	अणु DA7218_ALC_CTRL1, 0x00 पूर्ण,
	अणु DA7218_ALC_CTRL2, 0x00 पूर्ण,
	अणु DA7218_ALC_CTRL3, 0x00 पूर्ण,
	अणु DA7218_ALC_NOISE, 0x3F पूर्ण,
	अणु DA7218_ALC_TARGET_MIN, 0x3F पूर्ण,
	अणु DA7218_ALC_TARGET_MAX, 0x00 पूर्ण,
	अणु DA7218_ALC_GAIN_LIMITS, 0xFF पूर्ण,
	अणु DA7218_ALC_ANA_GAIN_LIMITS, 0x71 पूर्ण,
	अणु DA7218_ALC_ANTICLIP_CTRL, 0x00 पूर्ण,
	अणु DA7218_AGS_ENABLE, 0x00 पूर्ण,
	अणु DA7218_AGS_TRIGGER, 0x09 पूर्ण,
	अणु DA7218_AGS_ATT_MAX, 0x00 पूर्ण,
	अणु DA7218_AGS_TIMEOUT, 0x00 पूर्ण,
	अणु DA7218_AGS_ANTICLIP_CTRL, 0x00 पूर्ण,
	अणु DA7218_ENV_TRACK_CTRL, 0x00 पूर्ण,
	अणु DA7218_LVL_DET_CTRL, 0x00 पूर्ण,
	अणु DA7218_LVL_DET_LEVEL, 0x7F पूर्ण,
	अणु DA7218_DGS_TRIGGER, 0x24 पूर्ण,
	अणु DA7218_DGS_ENABLE, 0x00 पूर्ण,
	अणु DA7218_DGS_RISE_FALL, 0x50 पूर्ण,
	अणु DA7218_DGS_SYNC_DELAY, 0xA3 पूर्ण,
	अणु DA7218_DGS_SYNC_DELAY2, 0x31 पूर्ण,
	अणु DA7218_DGS_SYNC_DELAY3, 0x11 पूर्ण,
	अणु DA7218_DGS_LEVELS, 0x01 पूर्ण,
	अणु DA7218_DGS_GAIN_CTRL, 0x74 पूर्ण,
	अणु DA7218_DROUTING_OUTDAI_1L, 0x01 पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_INFILT_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_INFILT_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_INFILT_2L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_INFILT_2R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_TONEGEN_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_INDAI_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1L_INDAI_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DROUTING_OUTDAI_1R, 0x04 पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_INFILT_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_INFILT_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_INFILT_2L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_INFILT_2R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_TONEGEN_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_INDAI_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_1R_INDAI_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DROUTING_OUTFILT_1L, 0x01 पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_INFILT_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_INFILT_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_INFILT_2L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_INFILT_2R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_TONEGEN_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_INDAI_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1L_INDAI_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DROUTING_OUTFILT_1R, 0x04 पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_INFILT_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_INFILT_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_INFILT_2L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_INFILT_2R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_TONEGEN_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_INDAI_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTFILT_1R_INDAI_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DROUTING_OUTDAI_2L, 0x04 पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_INFILT_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_INFILT_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_INFILT_2L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_INFILT_2R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_TONEGEN_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_INDAI_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2L_INDAI_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DROUTING_OUTDAI_2R, 0x08 पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_INFILT_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_INFILT_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_INFILT_2L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_INFILT_2R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_TONEGEN_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_INDAI_1L_GAIN, 0x1C पूर्ण,
	अणु DA7218_DMIX_OUTDAI_2R_INDAI_1R_GAIN, 0x1C पूर्ण,
	अणु DA7218_DAI_CTRL, 0x28 पूर्ण,
	अणु DA7218_DAI_TDM_CTRL, 0x40 पूर्ण,
	अणु DA7218_DAI_OFFSET_LOWER, 0x00 पूर्ण,
	अणु DA7218_DAI_OFFSET_UPPER, 0x00 पूर्ण,
	अणु DA7218_DAI_CLK_MODE, 0x01 पूर्ण,
	अणु DA7218_PLL_CTRL, 0x04 पूर्ण,
	अणु DA7218_PLL_FRAC_TOP, 0x00 पूर्ण,
	अणु DA7218_PLL_FRAC_BOT, 0x00 पूर्ण,
	अणु DA7218_PLL_INTEGER, 0x20 पूर्ण,
	अणु DA7218_DAC_NG_CTRL, 0x00 पूर्ण,
	अणु DA7218_DAC_NG_SETUP_TIME, 0x00 पूर्ण,
	अणु DA7218_DAC_NG_OFF_THRESH, 0x00 पूर्ण,
	अणु DA7218_DAC_NG_ON_THRESH, 0x00 पूर्ण,
	अणु DA7218_TONE_GEN_CFG2, 0x00 पूर्ण,
	अणु DA7218_TONE_GEN_FREQ1_L, 0x55 पूर्ण,
	अणु DA7218_TONE_GEN_FREQ1_U, 0x15 पूर्ण,
	अणु DA7218_TONE_GEN_FREQ2_L, 0x00 पूर्ण,
	अणु DA7218_TONE_GEN_FREQ2_U, 0x40 पूर्ण,
	अणु DA7218_TONE_GEN_CYCLES, 0x00 पूर्ण,
	अणु DA7218_TONE_GEN_ON_PER, 0x02 पूर्ण,
	अणु DA7218_TONE_GEN_OFF_PER, 0x01 पूर्ण,
	अणु DA7218_CP_CTRL, 0x60 पूर्ण,
	अणु DA7218_CP_DELAY, 0x11 पूर्ण,
	अणु DA7218_CP_VOL_THRESHOLD1, 0x0E पूर्ण,
	अणु DA7218_MIC_1_CTRL, 0x40 पूर्ण,
	अणु DA7218_MIC_1_GAIN, 0x01 पूर्ण,
	अणु DA7218_MIC_1_SELECT, 0x00 पूर्ण,
	अणु DA7218_MIC_2_CTRL, 0x40 पूर्ण,
	अणु DA7218_MIC_2_GAIN, 0x01 पूर्ण,
	अणु DA7218_MIC_2_SELECT, 0x00 पूर्ण,
	अणु DA7218_IN_1_HPF_FILTER_CTRL, 0x80 पूर्ण,
	अणु DA7218_IN_2_HPF_FILTER_CTRL, 0x80 पूर्ण,
	अणु DA7218_ADC_1_CTRL, 0x07 पूर्ण,
	अणु DA7218_ADC_2_CTRL, 0x07 पूर्ण,
	अणु DA7218_MIXOUT_L_CTRL, 0x00 पूर्ण,
	अणु DA7218_MIXOUT_L_GAIN, 0x03 पूर्ण,
	अणु DA7218_MIXOUT_R_CTRL, 0x00 पूर्ण,
	अणु DA7218_MIXOUT_R_GAIN, 0x03 पूर्ण,
	अणु DA7218_HP_L_CTRL, 0x40 पूर्ण,
	अणु DA7218_HP_L_GAIN, 0x3B पूर्ण,
	अणु DA7218_HP_R_CTRL, 0x40 पूर्ण,
	अणु DA7218_HP_R_GAIN, 0x3B पूर्ण,
	अणु DA7218_HP_DIFF_CTRL, 0x00 पूर्ण,
	अणु DA7218_HP_DIFF_UNLOCK, 0xC3 पूर्ण,
	अणु DA7218_HPLDET_JACK, 0x0B पूर्ण,
	अणु DA7218_HPLDET_CTRL, 0x00 पूर्ण,
	अणु DA7218_REFERENCES, 0x08 पूर्ण,
	अणु DA7218_IO_CTRL, 0x00 पूर्ण,
	अणु DA7218_LDO_CTRL, 0x00 पूर्ण,
	अणु DA7218_SIDETONE_CTRL, 0x40 पूर्ण,
	अणु DA7218_SIDETONE_IN_SELECT, 0x00 पूर्ण,
	अणु DA7218_SIDETONE_GAIN, 0x1C पूर्ण,
	अणु DA7218_DROUTING_ST_OUTFILT_1L, 0x01 पूर्ण,
	अणु DA7218_DROUTING_ST_OUTFILT_1R, 0x02 पूर्ण,
	अणु DA7218_SIDETONE_BIQ_3STAGE_DATA, 0x00 पूर्ण,
	अणु DA7218_SIDETONE_BIQ_3STAGE_ADDR, 0x00 पूर्ण,
	अणु DA7218_EVENT_MASK, 0x00 पूर्ण,
	अणु DA7218_DMIC_1_CTRL, 0x00 पूर्ण,
	अणु DA7218_DMIC_2_CTRL, 0x00 पूर्ण,
	अणु DA7218_IN_1L_GAIN, 0x6F पूर्ण,
	अणु DA7218_IN_1R_GAIN, 0x6F पूर्ण,
	अणु DA7218_IN_2L_GAIN, 0x6F पूर्ण,
	अणु DA7218_IN_2R_GAIN, 0x6F पूर्ण,
	अणु DA7218_OUT_1L_GAIN, 0x6F पूर्ण,
	अणु DA7218_OUT_1R_GAIN, 0x6F पूर्ण,
	अणु DA7218_MICBIAS_CTRL, 0x00 पूर्ण,
	अणु DA7218_MICBIAS_EN, 0x00 पूर्ण,
पूर्ण;

अटल bool da7218_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA7218_STATUS1:
	हाल DA7218_SOFT_RESET:
	हाल DA7218_SYSTEM_STATUS:
	हाल DA7218_CALIB_CTRL:
	हाल DA7218_CALIB_OFFSET_AUTO_M_1:
	हाल DA7218_CALIB_OFFSET_AUTO_U_1:
	हाल DA7218_CALIB_OFFSET_AUTO_M_2:
	हाल DA7218_CALIB_OFFSET_AUTO_U_2:
	हाल DA7218_PLL_STATUS:
	हाल DA7218_PLL_REFOSC_CAL:
	हाल DA7218_TONE_GEN_CFG1:
	हाल DA7218_ADC_MODE:
	हाल DA7218_HP_SNGL_CTRL:
	हाल DA7218_HPLDET_TEST:
	हाल DA7218_EVENT_STATUS:
	हाल DA7218_EVENT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config da7218_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = DA7218_MICBIAS_EN,
	.reg_शेषs = da7218_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(da7218_reg_शेषs),
	.अस्थिर_reg = da7218_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;


/*
 * I2C layer
 */

अटल पूर्णांक da7218_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da7218_priv *da7218;
	पूर्णांक ret;

	da7218 = devm_kzalloc(&i2c->dev, माप(*da7218), GFP_KERNEL);
	अगर (!da7218)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, da7218);

	अगर (i2c->dev.of_node)
		da7218->dev_id = da7218_of_get_id(&i2c->dev);
	अन्यथा
		da7218->dev_id = id->driver_data;

	अगर ((da7218->dev_id != DA7217_DEV_ID) &&
	    (da7218->dev_id != DA7218_DEV_ID)) अणु
		dev_err(&i2c->dev, "Invalid device Id\n");
		वापस -EINVAL;
	पूर्ण

	da7218->irq = i2c->irq;

	da7218->regmap = devm_regmap_init_i2c(i2c, &da7218_regmap_config);
	अगर (IS_ERR(da7218->regmap)) अणु
		ret = PTR_ERR(da7218->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_da7218, &da7218_dai, 1);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to register da7218 component: %d\n",
			ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da7218_i2c_id[] = अणु
	अणु "da7217", DA7217_DEV_ID पूर्ण,
	अणु "da7218", DA7218_DEV_ID पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da7218_i2c_id);

अटल काष्ठा i2c_driver da7218_i2c_driver = अणु
	.driver = अणु
		.name = "da7218",
		.of_match_table = da7218_of_match,
	पूर्ण,
	.probe		= da7218_i2c_probe,
	.id_table	= da7218_i2c_id,
पूर्ण;

module_i2c_driver(da7218_i2c_driver);

MODULE_DESCRIPTION("ASoC DA7218 Codec driver");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
