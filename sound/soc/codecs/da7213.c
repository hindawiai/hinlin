<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA7213 ALSA SoC Codec Driver
 *
 * Copyright (c) 2013 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 * Based on DA9055 ALSA SoC codec driver.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश <sound/da7213.h>
#समावेश "da7213.h"


/* Gain and Volume */
अटल स्थिर DECLARE_TLV_DB_RANGE(aux_vol_tlv,
	/* -54dB */
	0x0, 0x11, TLV_DB_SCALE_ITEM(-5400, 0, 0),
	/* -52.5dB to 15dB */
	0x12, 0x3f, TLV_DB_SCALE_ITEM(-5250, 150, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(digital_gain_tlv,
	0x0, 0x07, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* -78dB to 12dB */
	0x08, 0x7f, TLV_DB_SCALE_ITEM(-7800, 75, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(alc_analog_gain_tlv,
	0x0, 0x0, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* 0dB to 36dB */
	0x01, 0x07, TLV_DB_SCALE_ITEM(0, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mixin_gain_tlv, -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_gain_tlv, -1050, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_vol_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(lineout_vol_tlv, -4800, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_threshold_tlv, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_gain_tlv, 0, 600, 0);

/* ADC and DAC voice mode (8kHz) high pass cutoff value */
अटल स्थिर अक्षर * स्थिर da7213_voice_hpf_corner_txt[] = अणु
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_voice_hpf_corner,
			    DA7213_DAC_FILTERS1,
			    DA7213_VOICE_HPF_CORNER_SHIFT,
			    da7213_voice_hpf_corner_txt);

अटल SOC_ENUM_SINGLE_DECL(da7213_adc_voice_hpf_corner,
			    DA7213_ADC_FILTERS1,
			    DA7213_VOICE_HPF_CORNER_SHIFT,
			    da7213_voice_hpf_corner_txt);

/* ADC and DAC high pass filter cutoff value */
अटल स्थिर अक्षर * स्थिर da7213_audio_hpf_corner_txt[] = अणु
	"Fs/24000", "Fs/12000", "Fs/6000", "Fs/3000"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_audio_hpf_corner,
			    DA7213_DAC_FILTERS1
			    , DA7213_AUDIO_HPF_CORNER_SHIFT,
			    da7213_audio_hpf_corner_txt);

अटल SOC_ENUM_SINGLE_DECL(da7213_adc_audio_hpf_corner,
			    DA7213_ADC_FILTERS1,
			    DA7213_AUDIO_HPF_CORNER_SHIFT,
			    da7213_audio_hpf_corner_txt);

/* Gain ramping rate value */
अटल स्थिर अक्षर * स्थिर da7213_gain_ramp_rate_txt[] = अणु
	"nominal rate * 8", "nominal rate * 16", "nominal rate / 16",
	"nominal rate / 32"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_gain_ramp_rate,
			    DA7213_GAIN_RAMP_CTRL,
			    DA7213_GAIN_RAMP_RATE_SHIFT,
			    da7213_gain_ramp_rate_txt);

/* DAC noise gate setup समय value */
अटल स्थिर अक्षर * स्थिर da7213_dac_ng_setup_समय_प्रकारxt[] = अणु
	"256 samples", "512 samples", "1024 samples", "2048 samples"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_ng_setup_समय,
			    DA7213_DAC_NG_SETUP_TIME,
			    DA7213_DAC_NG_SETUP_TIME_SHIFT,
			    da7213_dac_ng_setup_समय_प्रकारxt);

/* DAC noise gate rampup rate value */
अटल स्थिर अक्षर * स्थिर da7213_dac_ng_rampup_txt[] = अणु
	"0.02 ms/dB", "0.16 ms/dB"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_ng_rampup_rate,
			    DA7213_DAC_NG_SETUP_TIME,
			    DA7213_DAC_NG_RAMPUP_RATE_SHIFT,
			    da7213_dac_ng_rampup_txt);

/* DAC noise gate rampकरोwn rate value */
अटल स्थिर अक्षर * स्थिर da7213_dac_ng_rampकरोwn_txt[] = अणु
	"0.64 ms/dB", "20.48 ms/dB"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_ng_rampकरोwn_rate,
			    DA7213_DAC_NG_SETUP_TIME,
			    DA7213_DAC_NG_RAMPDN_RATE_SHIFT,
			    da7213_dac_ng_rampकरोwn_txt);

/* DAC soft mute rate value */
अटल स्थिर अक्षर * स्थिर da7213_dac_soft_mute_rate_txt[] = अणु
	"1", "2", "4", "8", "16", "32", "64"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_soft_mute_rate,
			    DA7213_DAC_FILTERS5,
			    DA7213_DAC_SOFTMUTE_RATE_SHIFT,
			    da7213_dac_soft_mute_rate_txt);

/* ALC Attack Rate select */
अटल स्थिर अक्षर * स्थिर da7213_alc_attack_rate_txt[] = अणु
	"44/fs", "88/fs", "176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs",
	"5632/fs", "11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_alc_attack_rate,
			    DA7213_ALC_CTRL2,
			    DA7213_ALC_ATTACK_SHIFT,
			    da7213_alc_attack_rate_txt);

/* ALC Release Rate select */
अटल स्थिर अक्षर * स्थिर da7213_alc_release_rate_txt[] = अणु
	"176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs", "5632/fs",
	"11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_alc_release_rate,
			    DA7213_ALC_CTRL2,
			    DA7213_ALC_RELEASE_SHIFT,
			    da7213_alc_release_rate_txt);

/* ALC Hold Time select */
अटल स्थिर अक्षर * स्थिर da7213_alc_hold_समय_प्रकारxt[] = अणु
	"62/fs", "124/fs", "248/fs", "496/fs", "992/fs", "1984/fs", "3968/fs",
	"7936/fs", "15872/fs", "31744/fs", "63488/fs", "126976/fs",
	"253952/fs", "507904/fs", "1015808/fs", "2031616/fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_alc_hold_समय,
			    DA7213_ALC_CTRL3,
			    DA7213_ALC_HOLD_SHIFT,
			    da7213_alc_hold_समय_प्रकारxt);

/* ALC Input Signal Tracking rate select */
अटल स्थिर अक्षर * स्थिर da7213_alc_पूर्णांकeg_rate_txt[] = अणु
	"1/4", "1/16", "1/256", "1/65536"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_alc_पूर्णांकeg_attack_rate,
			    DA7213_ALC_CTRL3,
			    DA7213_ALC_INTEG_ATTACK_SHIFT,
			    da7213_alc_पूर्णांकeg_rate_txt);

अटल SOC_ENUM_SINGLE_DECL(da7213_alc_पूर्णांकeg_release_rate,
			    DA7213_ALC_CTRL3,
			    DA7213_ALC_INTEG_RELEASE_SHIFT,
			    da7213_alc_पूर्णांकeg_rate_txt);


/*
 * Control Functions
 */

अटल पूर्णांक da7213_get_alc_data(काष्ठा snd_soc_component *component, u8 reg_val)
अणु
	पूर्णांक mid_data, top_data;
	पूर्णांक sum = 0;
	u8 iteration;

	क्रम (iteration = 0; iteration < DA7213_ALC_AVG_ITERATIONS;
	     iteration++) अणु
		/* Select the left or right channel and capture data */
		snd_soc_component_ग_लिखो(component, DA7213_ALC_CIC_OP_LVL_CTRL, reg_val);

		/* Select middle 8 bits क्रम पढ़ो back from data रेजिस्टर */
		snd_soc_component_ग_लिखो(component, DA7213_ALC_CIC_OP_LVL_CTRL,
			      reg_val | DA7213_ALC_DATA_MIDDLE);
		mid_data = snd_soc_component_पढ़ो(component, DA7213_ALC_CIC_OP_LVL_DATA);

		/* Select top 8 bits क्रम पढ़ो back from data रेजिस्टर */
		snd_soc_component_ग_लिखो(component, DA7213_ALC_CIC_OP_LVL_CTRL,
			      reg_val | DA7213_ALC_DATA_TOP);
		top_data = snd_soc_component_पढ़ो(component, DA7213_ALC_CIC_OP_LVL_DATA);

		sum += ((mid_data << 8) | (top_data << 16));
	पूर्ण

	वापस sum / DA7213_ALC_AVG_ITERATIONS;
पूर्ण

अटल व्योम da7213_alc_calib_man(काष्ठा snd_soc_component *component)
अणु
	u8 reg_val;
	पूर्णांक avg_left_data, avg_right_data, offset_l, offset_r;

	/* Calculate average क्रम Left and Right data */
	/* Left Data */
	avg_left_data = da7213_get_alc_data(component,
			DA7213_ALC_CIC_OP_CHANNEL_LEFT);
	/* Right Data */
	avg_right_data = da7213_get_alc_data(component,
			 DA7213_ALC_CIC_OP_CHANNEL_RIGHT);

	/* Calculate DC offset */
	offset_l = -avg_left_data;
	offset_r = -avg_right_data;

	reg_val = (offset_l & DA7213_ALC_OFFSET_15_8) >> 8;
	snd_soc_component_ग_लिखो(component, DA7213_ALC_OFFSET_MAN_M_L, reg_val);
	reg_val = (offset_l & DA7213_ALC_OFFSET_19_16) >> 16;
	snd_soc_component_ग_लिखो(component, DA7213_ALC_OFFSET_MAN_U_L, reg_val);

	reg_val = (offset_r & DA7213_ALC_OFFSET_15_8) >> 8;
	snd_soc_component_ग_लिखो(component, DA7213_ALC_OFFSET_MAN_M_R, reg_val);
	reg_val = (offset_r & DA7213_ALC_OFFSET_19_16) >> 16;
	snd_soc_component_ग_लिखो(component, DA7213_ALC_OFFSET_MAN_U_R, reg_val);

	/* Enable analog/digital gain mode & offset cancellation */
	snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
			    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE,
			    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE);
पूर्ण

अटल व्योम da7213_alc_calib_स्वतः(काष्ठा snd_soc_component *component)
अणु
	u8 alc_ctrl1;

	/* Begin स्वतः calibration and रुको क्रम completion */
	snd_soc_component_update_bits(component, DA7213_ALC_CTRL1, DA7213_ALC_AUTO_CALIB_EN,
			    DA7213_ALC_AUTO_CALIB_EN);
	करो अणु
		alc_ctrl1 = snd_soc_component_पढ़ो(component, DA7213_ALC_CTRL1);
	पूर्ण जबतक (alc_ctrl1 & DA7213_ALC_AUTO_CALIB_EN);

	/* If स्वतः calibration fails, fall back to digital gain only mode */
	अगर (alc_ctrl1 & DA7213_ALC_CALIB_OVERFLOW) अणु
		dev_warn(component->dev,
			 "ALC auto calibration failed with overflow\n");
		snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
				    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE,
				    0);
	पूर्ण अन्यथा अणु
		/* Enable analog/digital gain mode & offset cancellation */
		snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
				    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE,
				    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE);
	पूर्ण

पूर्ण

अटल व्योम da7213_alc_calib(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 adc_l_ctrl, adc_r_ctrl;
	u8 mixin_l_sel, mixin_r_sel;
	u8 mic_1_ctrl, mic_2_ctrl;

	/* Save current values from ADC control रेजिस्टरs */
	adc_l_ctrl = snd_soc_component_पढ़ो(component, DA7213_ADC_L_CTRL);
	adc_r_ctrl = snd_soc_component_पढ़ो(component, DA7213_ADC_R_CTRL);

	/* Save current values from MIXIN_L/R_SELECT रेजिस्टरs */
	mixin_l_sel = snd_soc_component_पढ़ो(component, DA7213_MIXIN_L_SELECT);
	mixin_r_sel = snd_soc_component_पढ़ो(component, DA7213_MIXIN_R_SELECT);

	/* Save current values from MIC control रेजिस्टरs */
	mic_1_ctrl = snd_soc_component_पढ़ो(component, DA7213_MIC_1_CTRL);
	mic_2_ctrl = snd_soc_component_पढ़ो(component, DA7213_MIC_2_CTRL);

	/* Enable ADC Left and Right */
	snd_soc_component_update_bits(component, DA7213_ADC_L_CTRL, DA7213_ADC_EN,
			    DA7213_ADC_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_R_CTRL, DA7213_ADC_EN,
			    DA7213_ADC_EN);

	/* Enable MIC paths */
	snd_soc_component_update_bits(component, DA7213_MIXIN_L_SELECT,
			    DA7213_MIXIN_L_MIX_SELECT_MIC_1 |
			    DA7213_MIXIN_L_MIX_SELECT_MIC_2,
			    DA7213_MIXIN_L_MIX_SELECT_MIC_1 |
			    DA7213_MIXIN_L_MIX_SELECT_MIC_2);
	snd_soc_component_update_bits(component, DA7213_MIXIN_R_SELECT,
			    DA7213_MIXIN_R_MIX_SELECT_MIC_2 |
			    DA7213_MIXIN_R_MIX_SELECT_MIC_1,
			    DA7213_MIXIN_R_MIX_SELECT_MIC_2 |
			    DA7213_MIXIN_R_MIX_SELECT_MIC_1);

	/* Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7213_MIC_1_CTRL, DA7213_MUTE_EN,
			    DA7213_MUTE_EN);
	snd_soc_component_update_bits(component, DA7213_MIC_2_CTRL, DA7213_MUTE_EN,
			    DA7213_MUTE_EN);

	/* Perक्रमm calibration */
	अगर (da7213->alc_calib_स्वतः)
		da7213_alc_calib_स्वतः(component);
	अन्यथा
		da7213_alc_calib_man(component);

	/* Restore MIXIN_L/R_SELECT रेजिस्टरs to their original states */
	snd_soc_component_ग_लिखो(component, DA7213_MIXIN_L_SELECT, mixin_l_sel);
	snd_soc_component_ग_लिखो(component, DA7213_MIXIN_R_SELECT, mixin_r_sel);

	/* Restore ADC control रेजिस्टरs to their original states */
	snd_soc_component_ग_लिखो(component, DA7213_ADC_L_CTRL, adc_l_ctrl);
	snd_soc_component_ग_लिखो(component, DA7213_ADC_R_CTRL, adc_r_ctrl);

	/* Restore original values of MIC control रेजिस्टरs */
	snd_soc_component_ग_लिखो(component, DA7213_MIC_1_CTRL, mic_1_ctrl);
	snd_soc_component_ग_लिखो(component, DA7213_MIC_2_CTRL, mic_2_ctrl);
पूर्ण

अटल पूर्णांक da7213_put_mixin_gain(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_put_volsw_2r(kcontrol, ucontrol);

	/* If ALC in operation, make sure calibrated offsets are updated */
	अगर ((!ret) && (da7213->alc_en))
		da7213_alc_calib(component);

	वापस ret;
पूर्ण

अटल पूर्णांक da7213_put_alc_sw(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);

	/* Force ALC offset calibration अगर enabling ALC */
	अगर (ucontrol->value.पूर्णांकeger.value[0] ||
	    ucontrol->value.पूर्णांकeger.value[1]) अणु
		अगर (!da7213->alc_en) अणु
			da7213_alc_calib(component);
			da7213->alc_en = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		da7213->alc_en = false;
	पूर्ण

	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण


/*
 * KControls
 */

अटल स्थिर काष्ठा snd_kcontrol_new da7213_snd_controls[] = अणु

	/* Volume controls */
	SOC_SINGLE_TLV("Mic 1 Volume", DA7213_MIC_1_GAIN,
		       DA7213_MIC_AMP_GAIN_SHIFT, DA7213_MIC_AMP_GAIN_MAX,
		       DA7213_NO_INVERT, mic_vol_tlv),
	SOC_SINGLE_TLV("Mic 2 Volume", DA7213_MIC_2_GAIN,
		       DA7213_MIC_AMP_GAIN_SHIFT, DA7213_MIC_AMP_GAIN_MAX,
		       DA7213_NO_INVERT, mic_vol_tlv),
	SOC_DOUBLE_R_TLV("Aux Volume", DA7213_AUX_L_GAIN, DA7213_AUX_R_GAIN,
			 DA7213_AUX_AMP_GAIN_SHIFT, DA7213_AUX_AMP_GAIN_MAX,
			 DA7213_NO_INVERT, aux_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("Mixin PGA Volume", DA7213_MIXIN_L_GAIN,
			     DA7213_MIXIN_R_GAIN, DA7213_MIXIN_AMP_GAIN_SHIFT,
			     DA7213_MIXIN_AMP_GAIN_MAX, DA7213_NO_INVERT,
			     snd_soc_get_volsw_2r, da7213_put_mixin_gain,
			     mixin_gain_tlv),
	SOC_DOUBLE_R_TLV("ADC Volume", DA7213_ADC_L_GAIN, DA7213_ADC_R_GAIN,
			 DA7213_ADC_AMP_GAIN_SHIFT, DA7213_ADC_AMP_GAIN_MAX,
			 DA7213_NO_INVERT, digital_gain_tlv),
	SOC_DOUBLE_R_TLV("DAC Volume", DA7213_DAC_L_GAIN, DA7213_DAC_R_GAIN,
			 DA7213_DAC_AMP_GAIN_SHIFT, DA7213_DAC_AMP_GAIN_MAX,
			 DA7213_NO_INVERT, digital_gain_tlv),
	SOC_DOUBLE_R_TLV("Headphone Volume", DA7213_HP_L_GAIN, DA7213_HP_R_GAIN,
			 DA7213_HP_AMP_GAIN_SHIFT, DA7213_HP_AMP_GAIN_MAX,
			 DA7213_NO_INVERT, hp_vol_tlv),
	SOC_SINGLE_TLV("Lineout Volume", DA7213_LINE_GAIN,
		       DA7213_LINE_AMP_GAIN_SHIFT, DA7213_LINE_AMP_GAIN_MAX,
		       DA7213_NO_INVERT, lineout_vol_tlv),

	/* DAC Equalizer controls */
	SOC_SINGLE("DAC EQ Switch", DA7213_DAC_FILTERS4, DA7213_DAC_EQ_EN_SHIFT,
		   DA7213_DAC_EQ_EN_MAX, DA7213_NO_INVERT),
	SOC_SINGLE_TLV("DAC EQ1 Volume", DA7213_DAC_FILTERS2,
		       DA7213_DAC_EQ_BAND1_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVERT, eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ2 Volume", DA7213_DAC_FILTERS2,
		       DA7213_DAC_EQ_BAND2_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVERT, eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ3 Volume", DA7213_DAC_FILTERS3,
		       DA7213_DAC_EQ_BAND3_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVERT, eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ4 Volume", DA7213_DAC_FILTERS3,
		       DA7213_DAC_EQ_BAND4_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVERT, eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ5 Volume", DA7213_DAC_FILTERS4,
		       DA7213_DAC_EQ_BAND5_SHIFT, DA7213_DAC_EQ_BAND_MAX,
		       DA7213_NO_INVERT, eq_gain_tlv),

	/* High Pass Filter and Voice Mode controls */
	SOC_SINGLE("ADC HPF Switch", DA7213_ADC_FILTERS1, DA7213_HPF_EN_SHIFT,
		   DA7213_HPF_EN_MAX, DA7213_NO_INVERT),
	SOC_ENUM("ADC HPF Cutoff", da7213_adc_audio_hpf_corner),
	SOC_SINGLE("ADC Voice Mode Switch", DA7213_ADC_FILTERS1,
		   DA7213_VOICE_EN_SHIFT, DA7213_VOICE_EN_MAX,
		   DA7213_NO_INVERT),
	SOC_ENUM("ADC Voice Cutoff", da7213_adc_voice_hpf_corner),

	SOC_SINGLE("DAC HPF Switch", DA7213_DAC_FILTERS1, DA7213_HPF_EN_SHIFT,
		   DA7213_HPF_EN_MAX, DA7213_NO_INVERT),
	SOC_ENUM("DAC HPF Cutoff", da7213_dac_audio_hpf_corner),
	SOC_SINGLE("DAC Voice Mode Switch", DA7213_DAC_FILTERS1,
		   DA7213_VOICE_EN_SHIFT, DA7213_VOICE_EN_MAX,
		   DA7213_NO_INVERT),
	SOC_ENUM("DAC Voice Cutoff", da7213_dac_voice_hpf_corner),

	/* Mute controls */
	SOC_SINGLE("Mic 1 Switch", DA7213_MIC_1_CTRL, DA7213_MUTE_EN_SHIFT,
		   DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_SINGLE("Mic 2 Switch", DA7213_MIC_2_CTRL, DA7213_MUTE_EN_SHIFT,
		   DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_DOUBLE_R("Aux Switch", DA7213_AUX_L_CTRL, DA7213_AUX_R_CTRL,
		     DA7213_MUTE_EN_SHIFT, DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_DOUBLE_R("Mixin PGA Switch", DA7213_MIXIN_L_CTRL,
		     DA7213_MIXIN_R_CTRL, DA7213_MUTE_EN_SHIFT,
		     DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_DOUBLE_R("ADC Switch", DA7213_ADC_L_CTRL, DA7213_ADC_R_CTRL,
		     DA7213_MUTE_EN_SHIFT, DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_DOUBLE_R("Headphone Switch", DA7213_HP_L_CTRL, DA7213_HP_R_CTRL,
		     DA7213_MUTE_EN_SHIFT, DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_SINGLE("Lineout Switch", DA7213_LINE_CTRL, DA7213_MUTE_EN_SHIFT,
		   DA7213_MUTE_EN_MAX, DA7213_INVERT),
	SOC_SINGLE("DAC Soft Mute Switch", DA7213_DAC_FILTERS5,
		   DA7213_DAC_SOFTMUTE_EN_SHIFT, DA7213_DAC_SOFTMUTE_EN_MAX,
		   DA7213_NO_INVERT),
	SOC_ENUM("DAC Soft Mute Rate", da7213_dac_soft_mute_rate),

	/* Zero Cross controls */
	SOC_DOUBLE_R("Aux ZC Switch", DA7213_AUX_L_CTRL, DA7213_AUX_R_CTRL,
		     DA7213_ZC_EN_SHIFT, DA7213_ZC_EN_MAX, DA7213_NO_INVERT),
	SOC_DOUBLE_R("Mixin PGA ZC Switch", DA7213_MIXIN_L_CTRL,
		     DA7213_MIXIN_R_CTRL, DA7213_ZC_EN_SHIFT, DA7213_ZC_EN_MAX,
		     DA7213_NO_INVERT),
	SOC_DOUBLE_R("Headphone ZC Switch", DA7213_HP_L_CTRL, DA7213_HP_R_CTRL,
		     DA7213_ZC_EN_SHIFT, DA7213_ZC_EN_MAX, DA7213_NO_INVERT),

	/* Gain Ramping controls */
	SOC_DOUBLE_R("Aux Gain Ramping Switch", DA7213_AUX_L_CTRL,
		     DA7213_AUX_R_CTRL, DA7213_GAIN_RAMP_EN_SHIFT,
		     DA7213_GAIN_RAMP_EN_MAX, DA7213_NO_INVERT),
	SOC_DOUBLE_R("Mixin Gain Ramping Switch", DA7213_MIXIN_L_CTRL,
		     DA7213_MIXIN_R_CTRL, DA7213_GAIN_RAMP_EN_SHIFT,
		     DA7213_GAIN_RAMP_EN_MAX, DA7213_NO_INVERT),
	SOC_DOUBLE_R("ADC Gain Ramping Switch", DA7213_ADC_L_CTRL,
		     DA7213_ADC_R_CTRL, DA7213_GAIN_RAMP_EN_SHIFT,
		     DA7213_GAIN_RAMP_EN_MAX, DA7213_NO_INVERT),
	SOC_DOUBLE_R("DAC Gain Ramping Switch", DA7213_DAC_L_CTRL,
		     DA7213_DAC_R_CTRL, DA7213_GAIN_RAMP_EN_SHIFT,
		     DA7213_GAIN_RAMP_EN_MAX, DA7213_NO_INVERT),
	SOC_DOUBLE_R("Headphone Gain Ramping Switch", DA7213_HP_L_CTRL,
		     DA7213_HP_R_CTRL, DA7213_GAIN_RAMP_EN_SHIFT,
		     DA7213_GAIN_RAMP_EN_MAX, DA7213_NO_INVERT),
	SOC_SINGLE("Lineout Gain Ramping Switch", DA7213_LINE_CTRL,
		   DA7213_GAIN_RAMP_EN_SHIFT, DA7213_GAIN_RAMP_EN_MAX,
		   DA7213_NO_INVERT),
	SOC_ENUM("Gain Ramping Rate", da7213_gain_ramp_rate),

	/* DAC Noise Gate controls */
	SOC_SINGLE("DAC NG Switch", DA7213_DAC_NG_CTRL, DA7213_DAC_NG_EN_SHIFT,
		   DA7213_DAC_NG_EN_MAX, DA7213_NO_INVERT),
	SOC_ENUM("DAC NG Setup Time", da7213_dac_ng_setup_समय),
	SOC_ENUM("DAC NG Rampup Rate", da7213_dac_ng_rampup_rate),
	SOC_ENUM("DAC NG Rampdown Rate", da7213_dac_ng_rampकरोwn_rate),
	SOC_SINGLE("DAC NG OFF Threshold", DA7213_DAC_NG_OFF_THRESHOLD,
		   DA7213_DAC_NG_THRESHOLD_SHIFT, DA7213_DAC_NG_THRESHOLD_MAX,
		   DA7213_NO_INVERT),
	SOC_SINGLE("DAC NG ON Threshold", DA7213_DAC_NG_ON_THRESHOLD,
		   DA7213_DAC_NG_THRESHOLD_SHIFT, DA7213_DAC_NG_THRESHOLD_MAX,
		   DA7213_NO_INVERT),

	/* DAC Routing & Inversion */
	SOC_DOUBLE("DAC Mono Switch", DA7213_DIG_ROUTING_DAC,
		   DA7213_DAC_L_MONO_SHIFT, DA7213_DAC_R_MONO_SHIFT,
		   DA7213_DAC_MONO_MAX, DA7213_NO_INVERT),
	SOC_DOUBLE("DAC Invert Switch", DA7213_DIG_CTRL, DA7213_DAC_L_INV_SHIFT,
		   DA7213_DAC_R_INV_SHIFT, DA7213_DAC_INV_MAX,
		   DA7213_NO_INVERT),

	/* DMIC controls */
	SOC_DOUBLE_R("DMIC Switch", DA7213_MIXIN_L_SELECT,
		     DA7213_MIXIN_R_SELECT, DA7213_DMIC_EN_SHIFT,
		     DA7213_DMIC_EN_MAX, DA7213_NO_INVERT),

	/* ALC Controls */
	SOC_DOUBLE_EXT("ALC Switch", DA7213_ALC_CTRL1, DA7213_ALC_L_EN_SHIFT,
		       DA7213_ALC_R_EN_SHIFT, DA7213_ALC_EN_MAX,
		       DA7213_NO_INVERT, snd_soc_get_volsw, da7213_put_alc_sw),
	SOC_ENUM("ALC Attack Rate", da7213_alc_attack_rate),
	SOC_ENUM("ALC Release Rate", da7213_alc_release_rate),
	SOC_ENUM("ALC Hold Time", da7213_alc_hold_समय),
	/*
	 * Rate at which input संकेत envelope is tracked as the संकेत माला_लो
	 * larger
	 */
	SOC_ENUM("ALC Integ Attack Rate", da7213_alc_पूर्णांकeg_attack_rate),
	/*
	 * Rate at which input संकेत envelope is tracked as the संकेत माला_लो
	 * smaller
	 */
	SOC_ENUM("ALC Integ Release Rate", da7213_alc_पूर्णांकeg_release_rate),
	SOC_SINGLE_TLV("ALC Noise Threshold Volume", DA7213_ALC_NOISE,
		       DA7213_ALC_THRESHOLD_SHIFT, DA7213_ALC_THRESHOLD_MAX,
		       DA7213_INVERT, alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Min Threshold Volume", DA7213_ALC_TARGET_MIN,
		       DA7213_ALC_THRESHOLD_SHIFT, DA7213_ALC_THRESHOLD_MAX,
		       DA7213_INVERT, alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Threshold Volume", DA7213_ALC_TARGET_MAX,
		       DA7213_ALC_THRESHOLD_SHIFT, DA7213_ALC_THRESHOLD_MAX,
		       DA7213_INVERT, alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Attenuation Volume", DA7213_ALC_GAIN_LIMITS,
		       DA7213_ALC_ATTEN_MAX_SHIFT,
		       DA7213_ALC_ATTEN_GAIN_MAX_MAX, DA7213_NO_INVERT,
		       alc_gain_tlv),
	SOC_SINGLE_TLV("ALC Max Gain Volume", DA7213_ALC_GAIN_LIMITS,
		       DA7213_ALC_GAIN_MAX_SHIFT, DA7213_ALC_ATTEN_GAIN_MAX_MAX,
		       DA7213_NO_INVERT, alc_gain_tlv),
	SOC_SINGLE_TLV("ALC Min Analog Gain Volume", DA7213_ALC_ANA_GAIN_LIMITS,
		       DA7213_ALC_ANA_GAIN_MIN_SHIFT, DA7213_ALC_ANA_GAIN_MAX,
		       DA7213_NO_INVERT, alc_analog_gain_tlv),
	SOC_SINGLE_TLV("ALC Max Analog Gain Volume", DA7213_ALC_ANA_GAIN_LIMITS,
		       DA7213_ALC_ANA_GAIN_MAX_SHIFT, DA7213_ALC_ANA_GAIN_MAX,
		       DA7213_NO_INVERT, alc_analog_gain_tlv),
	SOC_SINGLE("ALC Anticlip Mode Switch", DA7213_ALC_ANTICLIP_CTRL,
		   DA7213_ALC_ANTICLIP_EN_SHIFT, DA7213_ALC_ANTICLIP_EN_MAX,
		   DA7213_NO_INVERT),
	SOC_SINGLE("ALC Anticlip Level", DA7213_ALC_ANTICLIP_LEVEL,
		   DA7213_ALC_ANTICLIP_LEVEL_SHIFT,
		   DA7213_ALC_ANTICLIP_LEVEL_MAX, DA7213_NO_INVERT),
पूर्ण;


/*
 * DAPM
 */

/*
 * Enums
 */

/* MIC PGA source select */
अटल स्थिर अक्षर * स्थिर da7213_mic_amp_in_sel_txt[] = अणु
	"Differential", "MIC_P", "MIC_N"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_mic_1_amp_in_sel,
			    DA7213_MIC_1_CTRL,
			    DA7213_MIC_AMP_IN_SEL_SHIFT,
			    da7213_mic_amp_in_sel_txt);
अटल स्थिर काष्ठा snd_kcontrol_new da7213_mic_1_amp_in_sel_mux =
	SOC_DAPM_ENUM("Mic 1 Amp Source MUX", da7213_mic_1_amp_in_sel);

अटल SOC_ENUM_SINGLE_DECL(da7213_mic_2_amp_in_sel,
			    DA7213_MIC_2_CTRL,
			    DA7213_MIC_AMP_IN_SEL_SHIFT,
			    da7213_mic_amp_in_sel_txt);
अटल स्थिर काष्ठा snd_kcontrol_new da7213_mic_2_amp_in_sel_mux =
	SOC_DAPM_ENUM("Mic 2 Amp Source MUX", da7213_mic_2_amp_in_sel);

/* DAI routing select */
अटल स्थिर अक्षर * स्थिर da7213_dai_src_txt[] = अणु
	"ADC Left", "ADC Right", "DAI Input Left", "DAI Input Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dai_l_src,
			    DA7213_DIG_ROUTING_DAI,
			    DA7213_DAI_L_SRC_SHIFT,
			    da7213_dai_src_txt);
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dai_l_src_mux =
	SOC_DAPM_ENUM("DAI Left Source MUX", da7213_dai_l_src);

अटल SOC_ENUM_SINGLE_DECL(da7213_dai_r_src,
			    DA7213_DIG_ROUTING_DAI,
			    DA7213_DAI_R_SRC_SHIFT,
			    da7213_dai_src_txt);
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dai_r_src_mux =
	SOC_DAPM_ENUM("DAI Right Source MUX", da7213_dai_r_src);

/* DAC routing select */
अटल स्थिर अक्षर * स्थिर da7213_dac_src_txt[] = अणु
	"ADC Output Left", "ADC Output Right", "DAI Input Left",
	"DAI Input Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_l_src,
			    DA7213_DIG_ROUTING_DAC,
			    DA7213_DAC_L_SRC_SHIFT,
			    da7213_dac_src_txt);
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dac_l_src_mux =
	SOC_DAPM_ENUM("DAC Left Source MUX", da7213_dac_l_src);

अटल SOC_ENUM_SINGLE_DECL(da7213_dac_r_src,
			    DA7213_DIG_ROUTING_DAC,
			    DA7213_DAC_R_SRC_SHIFT,
			    da7213_dac_src_txt);
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dac_r_src_mux =
	SOC_DAPM_ENUM("DAC Right Source MUX", da7213_dac_r_src);

/*
 * Mixer Controls
 */

/* Mixin Left */
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dapm_mixinl_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Left Switch", DA7213_MIXIN_L_SELECT,
			DA7213_MIXIN_L_MIX_SELECT_AUX_L_SHIFT,
			DA7213_MIXIN_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mic 1 Switch", DA7213_MIXIN_L_SELECT,
			DA7213_MIXIN_L_MIX_SELECT_MIC_1_SHIFT,
			DA7213_MIXIN_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mic 2 Switch", DA7213_MIXIN_L_SELECT,
			DA7213_MIXIN_L_MIX_SELECT_MIC_2_SHIFT,
			DA7213_MIXIN_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Right Switch", DA7213_MIXIN_L_SELECT,
			DA7213_MIXIN_L_MIX_SELECT_MIXIN_R_SHIFT,
			DA7213_MIXIN_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
पूर्ण;

/* Mixin Right */
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dapm_mixinr_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Right Switch", DA7213_MIXIN_R_SELECT,
			DA7213_MIXIN_R_MIX_SELECT_AUX_R_SHIFT,
			DA7213_MIXIN_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mic 2 Switch", DA7213_MIXIN_R_SELECT,
			DA7213_MIXIN_R_MIX_SELECT_MIC_2_SHIFT,
			DA7213_MIXIN_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mic 1 Switch", DA7213_MIXIN_R_SELECT,
			DA7213_MIXIN_R_MIX_SELECT_MIC_1_SHIFT,
			DA7213_MIXIN_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Left Switch", DA7213_MIXIN_R_SELECT,
			DA7213_MIXIN_R_MIX_SELECT_MIXIN_L_SHIFT,
			DA7213_MIXIN_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
पूर्ण;

/* Mixout Left */
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dapm_mixoutl_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Left Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_AUX_L_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Left Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_MIXIN_L_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Right Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_MIXIN_R_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("DAC Left Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_DAC_L_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Aux Left Invert Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_AUX_L_INVERTED_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Left Invert Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_MIXIN_L_INVERTED_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Right Invert Switch", DA7213_MIXOUT_L_SELECT,
			DA7213_MIXOUT_L_MIX_SELECT_MIXIN_R_INVERTED_SHIFT,
			DA7213_MIXOUT_L_MIX_SELECT_MAX, DA7213_NO_INVERT),
पूर्ण;

/* Mixout Right */
अटल स्थिर काष्ठा snd_kcontrol_new da7213_dapm_mixoutr_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Right Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_AUX_R_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Right Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_MIXIN_R_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Left Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_MIXIN_L_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("DAC Right Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_DAC_R_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Aux Right Invert Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_AUX_R_INVERTED_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Right Invert Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_MIXIN_R_INVERTED_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
	SOC_DAPM_SINGLE("Mixin Left Invert Switch", DA7213_MIXOUT_R_SELECT,
			DA7213_MIXOUT_R_MIX_SELECT_MIXIN_L_INVERTED_SHIFT,
			DA7213_MIXOUT_R_MIX_SELECT_MAX, DA7213_NO_INVERT),
पूर्ण;


/*
 * DAPM Events
 */

अटल पूर्णांक da7213_dai_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 pll_ctrl, pll_status;
	पूर्णांक i = 0;
	bool srm_lock = false;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable DAI clks क्रम master mode */
		अगर (da7213->master)
			snd_soc_component_update_bits(component, DA7213_DAI_CLK_MODE,
					    DA7213_DAI_CLK_EN_MASK,
					    DA7213_DAI_CLK_EN_MASK);

		/* PC synchronised to DAI */
		snd_soc_component_update_bits(component, DA7213_PC_COUNT,
				    DA7213_PC_FREERUN_MASK, 0);

		/* If SRM not enabled then nothing more to करो */
		pll_ctrl = snd_soc_component_पढ़ो(component, DA7213_PLL_CTRL);
		अगर (!(pll_ctrl & DA7213_PLL_SRM_EN))
			वापस 0;

		/* Assist 32KHz mode PLL lock */
		अगर (pll_ctrl & DA7213_PLL_32K_MODE) अणु
			snd_soc_component_ग_लिखो(component, 0xF0, 0x8B);
			snd_soc_component_ग_लिखो(component, 0xF2, 0x03);
			snd_soc_component_ग_लिखो(component, 0xF0, 0x00);
		पूर्ण

		/* Check SRM has locked */
		करो अणु
			pll_status = snd_soc_component_पढ़ो(component, DA7213_PLL_STATUS);
			अगर (pll_status & DA7219_PLL_SRM_LOCK) अणु
				srm_lock = true;
			पूर्ण अन्यथा अणु
				++i;
				msleep(50);
			पूर्ण
		पूर्ण जबतक ((i < DA7213_SRM_CHECK_RETRIES) && (!srm_lock));

		अगर (!srm_lock)
			dev_warn(component->dev, "SRM failed to lock\n");

		वापस 0;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Revert 32KHz PLL lock udpates अगर applied previously */
		pll_ctrl = snd_soc_component_पढ़ो(component, DA7213_PLL_CTRL);
		अगर (pll_ctrl & DA7213_PLL_32K_MODE) अणु
			snd_soc_component_ग_लिखो(component, 0xF0, 0x8B);
			snd_soc_component_ग_लिखो(component, 0xF2, 0x01);
			snd_soc_component_ग_लिखो(component, 0xF0, 0x00);
		पूर्ण

		/* PC मुक्त-running */
		snd_soc_component_update_bits(component, DA7213_PC_COUNT,
				    DA7213_PC_FREERUN_MASK,
				    DA7213_PC_FREERUN_MASK);

		/* Disable DAI clks अगर in master mode */
		अगर (da7213->master)
			snd_soc_component_update_bits(component, DA7213_DAI_CLK_MODE,
					    DA7213_DAI_CLK_EN_MASK, 0);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


/*
 * DAPM widमाला_लो
 */

अटल स्थिर काष्ठा snd_soc_dapm_widget da7213_dapm_widमाला_लो[] = अणु
	/*
	 * Power Supply
	 */
	SND_SOC_DAPM_REGULATOR_SUPPLY("VDDMIC", 0, 0),

	/*
	 * Input & Output
	 */

	/* Use a supply here as this controls both input & output DAIs */
	SND_SOC_DAPM_SUPPLY("DAI", DA7213_DAI_CTRL, DA7213_DAI_EN_SHIFT,
			    DA7213_NO_INVERT, da7213_dai_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/*
	 * Input
	 */

	/* Input Lines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("AUXL"),
	SND_SOC_DAPM_INPUT("AUXR"),

	/* MUXs क्रम Mic PGA source selection */
	SND_SOC_DAPM_MUX("Mic 1 Amp Source MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_mic_1_amp_in_sel_mux),
	SND_SOC_DAPM_MUX("Mic 2 Amp Source MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_mic_2_amp_in_sel_mux),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic 1 PGA", DA7213_MIC_1_CTRL, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic 2 PGA", DA7213_MIC_2_CTRL, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux Left PGA", DA7213_AUX_L_CTRL, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux Right PGA", DA7213_AUX_R_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Mixin Left PGA", DA7213_MIXIN_L_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Mixin Right PGA", DA7213_MIXIN_R_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),

	/* Mic Biases */
	SND_SOC_DAPM_SUPPLY("Mic Bias 1", DA7213_MICBIAS_CTRL,
			    DA7213_MICBIAS1_EN_SHIFT, DA7213_NO_INVERT,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Bias 2", DA7213_MICBIAS_CTRL,
			    DA7213_MICBIAS2_EN_SHIFT, DA7213_NO_INVERT,
			    शून्य, 0),

	/* Input Mixers */
	SND_SOC_DAPM_MIXER("Mixin Left", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixinl_controls[0],
			   ARRAY_SIZE(da7213_dapm_mixinl_controls)),
	SND_SOC_DAPM_MIXER("Mixin Right", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixinr_controls[0],
			   ARRAY_SIZE(da7213_dapm_mixinr_controls)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Left", शून्य, DA7213_ADC_L_CTRL,
			 DA7213_ADC_EN_SHIFT, DA7213_NO_INVERT),
	SND_SOC_DAPM_ADC("ADC Right", शून्य, DA7213_ADC_R_CTRL,
			 DA7213_ADC_EN_SHIFT, DA7213_NO_INVERT),

	/* DAI */
	SND_SOC_DAPM_MUX("DAI Left Source MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dai_l_src_mux),
	SND_SOC_DAPM_MUX("DAI Right Source MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dai_r_src_mux),
	SND_SOC_DAPM_AIF_OUT("DAIOUTL", "Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DAIOUTR", "Capture", 1, SND_SOC_NOPM, 0, 0),

	/*
	 * Output
	 */

	/* DAI */
	SND_SOC_DAPM_AIF_IN("DAIINL", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DAIINR", "Playback", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("DAC Left Source MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dac_l_src_mux),
	SND_SOC_DAPM_MUX("DAC Right Source MUX", SND_SOC_NOPM, 0, 0,
			 &da7213_dac_r_src_mux),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC Left", शून्य, DA7213_DAC_L_CTRL,
			 DA7213_DAC_EN_SHIFT, DA7213_NO_INVERT),
	SND_SOC_DAPM_DAC("DAC Right", शून्य, DA7213_DAC_R_CTRL,
			 DA7213_DAC_EN_SHIFT, DA7213_NO_INVERT),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Mixout Left", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixoutl_controls[0],
			   ARRAY_SIZE(da7213_dapm_mixoutl_controls)),
	SND_SOC_DAPM_MIXER("Mixout Right", SND_SOC_NOPM, 0, 0,
			   &da7213_dapm_mixoutr_controls[0],
			   ARRAY_SIZE(da7213_dapm_mixoutr_controls)),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("Mixout Left PGA", DA7213_MIXOUT_L_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Mixout Right PGA", DA7213_MIXOUT_R_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Lineout PGA", DA7213_LINE_CTRL, DA7213_AMP_EN_SHIFT,
			 DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Headphone Left PGA", DA7213_HP_L_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),
	SND_SOC_DAPM_PGA("Headphone Right PGA", DA7213_HP_R_CTRL,
			 DA7213_AMP_EN_SHIFT, DA7213_NO_INVERT, शून्य, 0),

	/* Charge Pump */
	SND_SOC_DAPM_SUPPLY("Charge Pump", DA7213_CP_CTRL, DA7213_CP_EN_SHIFT,
			    DA7213_NO_INVERT, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("LINE"),
पूर्ण;


/*
 * DAPM audio route definition
 */

अटल स्थिर काष्ठा snd_soc_dapm_route da7213_audio_map[] = अणु
	/* Dest       Connecting Widget    source */

	/* Input path */
	अणु"Mic Bias 1", शून्य, "VDDMIC"पूर्ण,
	अणु"Mic Bias 2", शून्य, "VDDMIC"पूर्ण,

	अणु"MIC1", शून्य, "Mic Bias 1"पूर्ण,
	अणु"MIC2", शून्य, "Mic Bias 2"पूर्ण,

	अणु"Mic 1 Amp Source MUX", "Differential", "MIC1"पूर्ण,
	अणु"Mic 1 Amp Source MUX", "MIC_P", "MIC1"पूर्ण,
	अणु"Mic 1 Amp Source MUX", "MIC_N", "MIC1"पूर्ण,

	अणु"Mic 2 Amp Source MUX", "Differential", "MIC2"पूर्ण,
	अणु"Mic 2 Amp Source MUX", "MIC_P", "MIC2"पूर्ण,
	अणु"Mic 2 Amp Source MUX", "MIC_N", "MIC2"पूर्ण,

	अणु"Mic 1 PGA", शून्य, "Mic 1 Amp Source MUX"पूर्ण,
	अणु"Mic 2 PGA", शून्य, "Mic 2 Amp Source MUX"पूर्ण,

	अणु"Aux Left PGA", शून्य, "AUXL"पूर्ण,
	अणु"Aux Right PGA", शून्य, "AUXR"पूर्ण,

	अणु"Mixin Left", "Aux Left Switch", "Aux Left PGA"पूर्ण,
	अणु"Mixin Left", "Mic 1 Switch", "Mic 1 PGA"पूर्ण,
	अणु"Mixin Left", "Mic 2 Switch", "Mic 2 PGA"पूर्ण,
	अणु"Mixin Left", "Mixin Right Switch", "Mixin Right PGA"पूर्ण,

	अणु"Mixin Right", "Aux Right Switch", "Aux Right PGA"पूर्ण,
	अणु"Mixin Right", "Mic 2 Switch", "Mic 2 PGA"पूर्ण,
	अणु"Mixin Right", "Mic 1 Switch", "Mic 1 PGA"पूर्ण,
	अणु"Mixin Right", "Mixin Left Switch", "Mixin Left PGA"पूर्ण,

	अणु"Mixin Left PGA", शून्य, "Mixin Left"पूर्ण,
	अणु"ADC Left", शून्य, "Mixin Left PGA"पूर्ण,

	अणु"Mixin Right PGA", शून्य, "Mixin Right"पूर्ण,
	अणु"ADC Right", शून्य, "Mixin Right PGA"पूर्ण,

	अणु"DAI Left Source MUX", "ADC Left", "ADC Left"पूर्ण,
	अणु"DAI Left Source MUX", "ADC Right", "ADC Right"पूर्ण,
	अणु"DAI Left Source MUX", "DAI Input Left", "DAIINL"पूर्ण,
	अणु"DAI Left Source MUX", "DAI Input Right", "DAIINR"पूर्ण,

	अणु"DAI Right Source MUX", "ADC Left", "ADC Left"पूर्ण,
	अणु"DAI Right Source MUX", "ADC Right", "ADC Right"पूर्ण,
	अणु"DAI Right Source MUX", "DAI Input Left", "DAIINL"पूर्ण,
	अणु"DAI Right Source MUX", "DAI Input Right", "DAIINR"पूर्ण,

	अणु"DAIOUTL", शून्य, "DAI Left Source MUX"पूर्ण,
	अणु"DAIOUTR", शून्य, "DAI Right Source MUX"पूर्ण,

	अणु"DAIOUTL", शून्य, "DAI"पूर्ण,
	अणु"DAIOUTR", शून्य, "DAI"पूर्ण,

	/* Output path */
	अणु"DAIINL", शून्य, "DAI"पूर्ण,
	अणु"DAIINR", शून्य, "DAI"पूर्ण,

	अणु"DAC Left Source MUX", "ADC Output Left", "ADC Left"पूर्ण,
	अणु"DAC Left Source MUX", "ADC Output Right", "ADC Right"पूर्ण,
	अणु"DAC Left Source MUX", "DAI Input Left", "DAIINL"पूर्ण,
	अणु"DAC Left Source MUX", "DAI Input Right", "DAIINR"पूर्ण,

	अणु"DAC Right Source MUX", "ADC Output Left", "ADC Left"पूर्ण,
	अणु"DAC Right Source MUX", "ADC Output Right", "ADC Right"पूर्ण,
	अणु"DAC Right Source MUX", "DAI Input Left", "DAIINL"पूर्ण,
	अणु"DAC Right Source MUX", "DAI Input Right", "DAIINR"पूर्ण,

	अणु"DAC Left", शून्य, "DAC Left Source MUX"पूर्ण,
	अणु"DAC Right", शून्य, "DAC Right Source MUX"पूर्ण,

	अणु"Mixout Left", "Aux Left Switch", "Aux Left PGA"पूर्ण,
	अणु"Mixout Left", "Mixin Left Switch", "Mixin Left PGA"पूर्ण,
	अणु"Mixout Left", "Mixin Right Switch", "Mixin Right PGA"पूर्ण,
	अणु"Mixout Left", "DAC Left Switch", "DAC Left"पूर्ण,
	अणु"Mixout Left", "Aux Left Invert Switch", "Aux Left PGA"पूर्ण,
	अणु"Mixout Left", "Mixin Left Invert Switch", "Mixin Left PGA"पूर्ण,
	अणु"Mixout Left", "Mixin Right Invert Switch", "Mixin Right PGA"पूर्ण,

	अणु"Mixout Right", "Aux Right Switch", "Aux Right PGA"पूर्ण,
	अणु"Mixout Right", "Mixin Right Switch", "Mixin Right PGA"पूर्ण,
	अणु"Mixout Right", "Mixin Left Switch", "Mixin Left PGA"पूर्ण,
	अणु"Mixout Right", "DAC Right Switch", "DAC Right"पूर्ण,
	अणु"Mixout Right", "Aux Right Invert Switch", "Aux Right PGA"पूर्ण,
	अणु"Mixout Right", "Mixin Right Invert Switch", "Mixin Right PGA"पूर्ण,
	अणु"Mixout Right", "Mixin Left Invert Switch", "Mixin Left PGA"पूर्ण,

	अणु"Mixout Left PGA", शून्य, "Mixout Left"पूर्ण,
	अणु"Mixout Right PGA", शून्य, "Mixout Right"पूर्ण,

	अणु"Headphone Left PGA", शून्य, "Mixout Left PGA"पूर्ण,
	अणु"Headphone Left PGA", शून्य, "Charge Pump"पूर्ण,
	अणु"HPL", शून्य, "Headphone Left PGA"पूर्ण,

	अणु"Headphone Right PGA", शून्य, "Mixout Right PGA"पूर्ण,
	अणु"Headphone Right PGA", शून्य, "Charge Pump"पूर्ण,
	अणु"HPR", शून्य, "Headphone Right PGA"पूर्ण,

	अणु"Lineout PGA", शून्य, "Mixout Right PGA"पूर्ण,
	अणु"LINE", शून्य, "Lineout PGA"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष da7213_reg_शेषs[] = अणु
	अणु DA7213_DIG_ROUTING_DAI, 0x10 पूर्ण,
	अणु DA7213_SR, 0x0A पूर्ण,
	अणु DA7213_REFERENCES, 0x80 पूर्ण,
	अणु DA7213_PLL_FRAC_TOP, 0x00 पूर्ण,
	अणु DA7213_PLL_FRAC_BOT, 0x00 पूर्ण,
	अणु DA7213_PLL_INTEGER, 0x20 पूर्ण,
	अणु DA7213_PLL_CTRL, 0x0C पूर्ण,
	अणु DA7213_DAI_CLK_MODE, 0x01 पूर्ण,
	अणु DA7213_DAI_CTRL, 0x08 पूर्ण,
	अणु DA7213_DIG_ROUTING_DAC, 0x32 पूर्ण,
	अणु DA7213_AUX_L_GAIN, 0x35 पूर्ण,
	अणु DA7213_AUX_R_GAIN, 0x35 पूर्ण,
	अणु DA7213_MIXIN_L_SELECT, 0x00 पूर्ण,
	अणु DA7213_MIXIN_R_SELECT, 0x00 पूर्ण,
	अणु DA7213_MIXIN_L_GAIN, 0x03 पूर्ण,
	अणु DA7213_MIXIN_R_GAIN, 0x03 पूर्ण,
	अणु DA7213_ADC_L_GAIN, 0x6F पूर्ण,
	अणु DA7213_ADC_R_GAIN, 0x6F पूर्ण,
	अणु DA7213_ADC_FILTERS1, 0x80 पूर्ण,
	अणु DA7213_MIC_1_GAIN, 0x01 पूर्ण,
	अणु DA7213_MIC_2_GAIN, 0x01 पूर्ण,
	अणु DA7213_DAC_FILTERS5, 0x00 पूर्ण,
	अणु DA7213_DAC_FILTERS2, 0x88 पूर्ण,
	अणु DA7213_DAC_FILTERS3, 0x88 पूर्ण,
	अणु DA7213_DAC_FILTERS4, 0x08 पूर्ण,
	अणु DA7213_DAC_FILTERS1, 0x80 पूर्ण,
	अणु DA7213_DAC_L_GAIN, 0x6F पूर्ण,
	अणु DA7213_DAC_R_GAIN, 0x6F पूर्ण,
	अणु DA7213_CP_CTRL, 0x61 पूर्ण,
	अणु DA7213_HP_L_GAIN, 0x39 पूर्ण,
	अणु DA7213_HP_R_GAIN, 0x39 पूर्ण,
	अणु DA7213_LINE_GAIN, 0x30 पूर्ण,
	अणु DA7213_MIXOUT_L_SELECT, 0x00 पूर्ण,
	अणु DA7213_MIXOUT_R_SELECT, 0x00 पूर्ण,
	अणु DA7213_SYSTEM_MODES_INPUT, 0x00 पूर्ण,
	अणु DA7213_SYSTEM_MODES_OUTPUT, 0x00 पूर्ण,
	अणु DA7213_AUX_L_CTRL, 0x44 पूर्ण,
	अणु DA7213_AUX_R_CTRL, 0x44 पूर्ण,
	अणु DA7213_MICBIAS_CTRL, 0x11 पूर्ण,
	अणु DA7213_MIC_1_CTRL, 0x40 पूर्ण,
	अणु DA7213_MIC_2_CTRL, 0x40 पूर्ण,
	अणु DA7213_MIXIN_L_CTRL, 0x40 पूर्ण,
	अणु DA7213_MIXIN_R_CTRL, 0x40 पूर्ण,
	अणु DA7213_ADC_L_CTRL, 0x40 पूर्ण,
	अणु DA7213_ADC_R_CTRL, 0x40 पूर्ण,
	अणु DA7213_DAC_L_CTRL, 0x48 पूर्ण,
	अणु DA7213_DAC_R_CTRL, 0x40 पूर्ण,
	अणु DA7213_HP_L_CTRL, 0x41 पूर्ण,
	अणु DA7213_HP_R_CTRL, 0x40 पूर्ण,
	अणु DA7213_LINE_CTRL, 0x40 पूर्ण,
	अणु DA7213_MIXOUT_L_CTRL, 0x10 पूर्ण,
	अणु DA7213_MIXOUT_R_CTRL, 0x10 पूर्ण,
	अणु DA7213_LDO_CTRL, 0x00 पूर्ण,
	अणु DA7213_IO_CTRL, 0x00 पूर्ण,
	अणु DA7213_GAIN_RAMP_CTRL, 0x00पूर्ण,
	अणु DA7213_MIC_CONFIG, 0x00 पूर्ण,
	अणु DA7213_PC_COUNT, 0x00 पूर्ण,
	अणु DA7213_CP_VOL_THRESHOLD1, 0x32 पूर्ण,
	अणु DA7213_CP_DELAY, 0x95 पूर्ण,
	अणु DA7213_CP_DETECTOR, 0x00 पूर्ण,
	अणु DA7213_DAI_OFFSET, 0x00 पूर्ण,
	अणु DA7213_DIG_CTRL, 0x00 पूर्ण,
	अणु DA7213_ALC_CTRL2, 0x00 पूर्ण,
	अणु DA7213_ALC_CTRL3, 0x00 पूर्ण,
	अणु DA7213_ALC_NOISE, 0x3F पूर्ण,
	अणु DA7213_ALC_TARGET_MIN, 0x3F पूर्ण,
	अणु DA7213_ALC_TARGET_MAX, 0x00 पूर्ण,
	अणु DA7213_ALC_GAIN_LIMITS, 0xFF पूर्ण,
	अणु DA7213_ALC_ANA_GAIN_LIMITS, 0x71 पूर्ण,
	अणु DA7213_ALC_ANTICLIP_CTRL, 0x00 पूर्ण,
	अणु DA7213_ALC_ANTICLIP_LEVEL, 0x00 पूर्ण,
	अणु DA7213_ALC_OFFSET_MAN_M_L, 0x00 पूर्ण,
	अणु DA7213_ALC_OFFSET_MAN_U_L, 0x00 पूर्ण,
	अणु DA7213_ALC_OFFSET_MAN_M_R, 0x00 पूर्ण,
	अणु DA7213_ALC_OFFSET_MAN_U_R, 0x00 पूर्ण,
	अणु DA7213_ALC_CIC_OP_LVL_CTRL, 0x00 पूर्ण,
	अणु DA7213_DAC_NG_SETUP_TIME, 0x00 पूर्ण,
	अणु DA7213_DAC_NG_OFF_THRESHOLD, 0x00 पूर्ण,
	अणु DA7213_DAC_NG_ON_THRESHOLD, 0x00 पूर्ण,
	अणु DA7213_DAC_NG_CTRL, 0x00 पूर्ण,
पूर्ण;

अटल bool da7213_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA7213_STATUS1:
	हाल DA7213_PLL_STATUS:
	हाल DA7213_AUX_L_GAIN_STATUS:
	हाल DA7213_AUX_R_GAIN_STATUS:
	हाल DA7213_MIC_1_GAIN_STATUS:
	हाल DA7213_MIC_2_GAIN_STATUS:
	हाल DA7213_MIXIN_L_GAIN_STATUS:
	हाल DA7213_MIXIN_R_GAIN_STATUS:
	हाल DA7213_ADC_L_GAIN_STATUS:
	हाल DA7213_ADC_R_GAIN_STATUS:
	हाल DA7213_DAC_L_GAIN_STATUS:
	हाल DA7213_DAC_R_GAIN_STATUS:
	हाल DA7213_HP_L_GAIN_STATUS:
	हाल DA7213_HP_R_GAIN_STATUS:
	हाल DA7213_LINE_GAIN_STATUS:
	हाल DA7213_ALC_CTRL1:
	हाल DA7213_ALC_OFFSET_AUTO_M_L:
	हाल DA7213_ALC_OFFSET_AUTO_U_L:
	हाल DA7213_ALC_OFFSET_AUTO_M_R:
	हाल DA7213_ALC_OFFSET_AUTO_U_R:
	हाल DA7213_ALC_CIC_OP_LVL_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक da7213_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 dai_ctrl = 0;
	u8 fs;

	/* Set DAI क्रमmat */
	चयन (params_width(params)) अणु
	हाल 16:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S16_LE;
		अवरोध;
	हाल 20:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S20_LE;
		अवरोध;
	हाल 24:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S24_LE;
		अवरोध;
	हाल 32:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S32_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set sampling rate */
	चयन (params_rate(params)) अणु
	हाल 8000:
		fs = DA7213_SR_8000;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_98304000;
		अवरोध;
	हाल 11025:
		fs = DA7213_SR_11025;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_90316800;
		अवरोध;
	हाल 12000:
		fs = DA7213_SR_12000;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_98304000;
		अवरोध;
	हाल 16000:
		fs = DA7213_SR_16000;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_98304000;
		अवरोध;
	हाल 22050:
		fs = DA7213_SR_22050;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_90316800;
		अवरोध;
	हाल 32000:
		fs = DA7213_SR_32000;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_98304000;
		अवरोध;
	हाल 44100:
		fs = DA7213_SR_44100;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_90316800;
		अवरोध;
	हाल 48000:
		fs = DA7213_SR_48000;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_98304000;
		अवरोध;
	हाल 88200:
		fs = DA7213_SR_88200;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_90316800;
		अवरोध;
	हाल 96000:
		fs = DA7213_SR_96000;
		da7213->out_rate = DA7213_PLL_FREQ_OUT_98304000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, DA7213_DAI_CTRL, DA7213_DAI_WORD_LENGTH_MASK,
			    dai_ctrl);
	snd_soc_component_ग_लिखो(component, DA7213_SR, fs);

	वापस 0;
पूर्ण

अटल पूर्णांक da7213_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 dai_clk_mode = 0, dai_ctrl = 0;
	u8 dai_offset = 0;

	/* Set master/slave mode */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		da7213->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		da7213->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set घड़ी normal/inverted */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			dai_clk_mode |= DA7213_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV |
					DA7213_DAI_CLK_POL_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAI_FORMAT_DSP_A:
	हाल SND_SOC_DAI_FORMAT_DSP_B:
		/* The bclk is inverted wrt ASoC conventions */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			dai_clk_mode |= DA7213_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV |
					DA7213_DAI_CLK_POL_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Only I2S is supported */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		dai_ctrl |= DA7213_DAI_FORMAT_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dai_ctrl |= DA7213_DAI_FORMAT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		dai_ctrl |= DA7213_DAI_FORMAT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAI_FORMAT_DSP_A: /* L data MSB after FRM LRC */
		dai_ctrl |= DA7213_DAI_FORMAT_DSP;
		dai_offset = 1;
		अवरोध;
	हाल SND_SOC_DAI_FORMAT_DSP_B: /* L data MSB during FRM LRC */
		dai_ctrl |= DA7213_DAI_FORMAT_DSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* By शेष only 64 BCLK per WCLK is supported */
	dai_clk_mode |= DA7213_DAI_BCLKS_PER_WCLK_64;

	snd_soc_component_update_bits(component, DA7213_DAI_CLK_MODE,
			    DA7213_DAI_BCLKS_PER_WCLK_MASK |
			    DA7213_DAI_CLK_POL_MASK | DA7213_DAI_WCLK_POL_MASK,
			    dai_clk_mode);
	snd_soc_component_update_bits(component, DA7213_DAI_CTRL, DA7213_DAI_FORMAT_MASK,
			    dai_ctrl);
	snd_soc_component_ग_लिखो(component, DA7213_DAI_OFFSET, dai_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक da7213_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute) अणु
		snd_soc_component_update_bits(component, DA7213_DAC_L_CTRL,
				    DA7213_MUTE_EN, DA7213_MUTE_EN);
		snd_soc_component_update_bits(component, DA7213_DAC_R_CTRL,
				    DA7213_MUTE_EN, DA7213_MUTE_EN);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, DA7213_DAC_L_CTRL,
				    DA7213_MUTE_EN, 0);
		snd_soc_component_update_bits(component, DA7213_DAC_R_CTRL,
				    DA7213_MUTE_EN, 0);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DA7213_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक da7213_set_component_sysclk(काष्ठा snd_soc_component *component,
				       पूर्णांक clk_id, पूर्णांक source,
				       अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर ((da7213->clk_src == clk_id) && (da7213->mclk_rate == freq))
		वापस 0;

	अगर (((freq < 5000000) && (freq != 32768)) || (freq > 54000000)) अणु
		dev_err(component->dev, "Unsupported MCLK value %d\n",
			freq);
		वापस -EINVAL;
	पूर्ण

	चयन (clk_id) अणु
	हाल DA7213_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, DA7213_PLL_CTRL,
				    DA7213_PLL_MCLK_SQR_EN, 0);
		अवरोध;
	हाल DA7213_CLKSRC_MCLK_SQR:
		snd_soc_component_update_bits(component, DA7213_PLL_CTRL,
				    DA7213_PLL_MCLK_SQR_EN,
				    DA7213_PLL_MCLK_SQR_EN);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown clock source %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	da7213->clk_src = clk_id;

	अगर (da7213->mclk) अणु
		freq = clk_round_rate(da7213->mclk, freq);
		ret = clk_set_rate(da7213->mclk, freq);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to set clock rate %d\n",
				freq);
			वापस ret;
		पूर्ण
	पूर्ण

	da7213->mclk_rate = freq;

	वापस 0;
पूर्ण

/* Supported PLL input frequencies are 32KHz, 5MHz - 54MHz. */
अटल पूर्णांक _da7213_set_component_pll(काष्ठा snd_soc_component *component,
				     पूर्णांक pll_id, पूर्णांक source,
				     अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);

	u8 pll_ctrl, inभाग_bits, inभाग;
	u8 pll_frac_top, pll_frac_bot, pll_पूर्णांकeger;
	u32 freq_ref;
	u64 frac_भाग;

	/* Workout input भागider based on MCLK rate */
	अगर (da7213->mclk_rate == 32768) अणु
		अगर (!da7213->master) अणु
			dev_err(component->dev,
				"32KHz only valid if codec is clock master\n");
			वापस -EINVAL;
		पूर्ण

		/* 32KHz PLL Mode */
		inभाग_bits = DA7213_PLL_INDIV_9_TO_18_MHZ;
		inभाग = DA7213_PLL_INDIV_9_TO_18_MHZ_VAL;
		source = DA7213_SYSCLK_PLL_32KHZ;
		freq_ref = 3750000;

	पूर्ण अन्यथा अणु
		अगर (da7213->mclk_rate < 5000000) अणु
			dev_err(component->dev,
				"PLL input clock %d below valid range\n",
				da7213->mclk_rate);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (da7213->mclk_rate <= 9000000) अणु
			inभाग_bits = DA7213_PLL_INDIV_5_TO_9_MHZ;
			inभाग = DA7213_PLL_INDIV_5_TO_9_MHZ_VAL;
		पूर्ण अन्यथा अगर (da7213->mclk_rate <= 18000000) अणु
			inभाग_bits = DA7213_PLL_INDIV_9_TO_18_MHZ;
			inभाग = DA7213_PLL_INDIV_9_TO_18_MHZ_VAL;
		पूर्ण अन्यथा अगर (da7213->mclk_rate <= 36000000) अणु
			inभाग_bits = DA7213_PLL_INDIV_18_TO_36_MHZ;
			inभाग = DA7213_PLL_INDIV_18_TO_36_MHZ_VAL;
		पूर्ण अन्यथा अगर (da7213->mclk_rate <= 54000000) अणु
			inभाग_bits = DA7213_PLL_INDIV_36_TO_54_MHZ;
			inभाग = DA7213_PLL_INDIV_36_TO_54_MHZ_VAL;
		पूर्ण अन्यथा अणु
			dev_err(component->dev,
				"PLL input clock %d above valid range\n",
				da7213->mclk_rate);
			वापस -EINVAL;
		पूर्ण
		freq_ref = (da7213->mclk_rate / inभाग);
	पूर्ण

	pll_ctrl = inभाग_bits;

	/* Configure PLL */
	चयन (source) अणु
	हाल DA7213_SYSCLK_MCLK:
		snd_soc_component_update_bits(component, DA7213_PLL_CTRL,
				    DA7213_PLL_INDIV_MASK |
				    DA7213_PLL_MODE_MASK, pll_ctrl);
		वापस 0;
	हाल DA7213_SYSCLK_PLL:
		अवरोध;
	हाल DA7213_SYSCLK_PLL_SRM:
		pll_ctrl |= DA7213_PLL_SRM_EN;
		fout = DA7213_PLL_FREQ_OUT_94310400;
		अवरोध;
	हाल DA7213_SYSCLK_PLL_32KHZ:
		अगर (da7213->mclk_rate != 32768) अणु
			dev_err(component->dev,
				"32KHz mode only valid with 32KHz MCLK\n");
			वापस -EINVAL;
		पूर्ण

		pll_ctrl |= DA7213_PLL_32K_MODE | DA7213_PLL_SRM_EN;
		fout = DA7213_PLL_FREQ_OUT_94310400;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid PLL config\n");
		वापस -EINVAL;
	पूर्ण

	/* Calculate भागiders क्रम PLL */
	pll_पूर्णांकeger = fout / freq_ref;
	frac_भाग = (u64)(fout % freq_ref) * 8192ULL;
	करो_भाग(frac_भाग, freq_ref);
	pll_frac_top = (frac_भाग >> DA7213_BYTE_SHIFT) & DA7213_BYTE_MASK;
	pll_frac_bot = (frac_भाग) & DA7213_BYTE_MASK;

	/* Write PLL भागiders */
	snd_soc_component_ग_लिखो(component, DA7213_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_ग_लिखो(component, DA7213_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_ग_लिखो(component, DA7213_PLL_INTEGER, pll_पूर्णांकeger);

	/* Enable PLL */
	pll_ctrl |= DA7213_PLL_EN;
	snd_soc_component_update_bits(component, DA7213_PLL_CTRL,
			    DA7213_PLL_INDIV_MASK | DA7213_PLL_MODE_MASK,
			    pll_ctrl);

	/* Assist 32KHz mode PLL lock */
	अगर (source == DA7213_SYSCLK_PLL_32KHZ) अणु
		snd_soc_component_ग_लिखो(component, 0xF0, 0x8B);
		snd_soc_component_ग_लिखो(component, 0xF1, 0x03);
		snd_soc_component_ग_लिखो(component, 0xF1, 0x01);
		snd_soc_component_ग_लिखो(component, 0xF0, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7213_set_component_pll(काष्ठा snd_soc_component *component,
				    पूर्णांक pll_id, पूर्णांक source,
				    अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	da7213->fixed_clk_स्वतः_pll = false;

	वापस _da7213_set_component_pll(component, pll_id, source, fref, fout);
पूर्ण

/* DAI operations */
अटल स्थिर काष्ठा snd_soc_dai_ops da7213_dai_ops = अणु
	.hw_params	= da7213_hw_params,
	.set_fmt	= da7213_set_dai_fmt,
	.mute_stream	= da7213_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver da7213_dai = अणु
	.name = "da7213-hifi",
	/* Playback Capabilities */
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA7213_FORMATS,
	पूर्ण,
	/* Capture Capabilities */
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA7213_FORMATS,
	पूर्ण,
	.ops = &da7213_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक da7213_set_स्वतः_pll(काष्ठा snd_soc_component *component, bool enable)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	पूर्णांक mode;

	अगर (!da7213->fixed_clk_स्वतः_pll)
		वापस 0;

	da7213->mclk_rate = clk_get_rate(da7213->mclk);

	अगर (enable) अणु
		/* Slave mode needs SRM क्रम non-harmonic frequencies */
		अगर (da7213->master)
			mode = DA7213_SYSCLK_PLL;
		अन्यथा
			mode = DA7213_SYSCLK_PLL_SRM;

		/* PLL is not required क्रम harmonic frequencies */
		चयन (da7213->out_rate) अणु
		हाल DA7213_PLL_FREQ_OUT_90316800:
			अगर (da7213->mclk_rate == 11289600 ||
			    da7213->mclk_rate == 22579200 ||
			    da7213->mclk_rate == 45158400)
				mode = DA7213_SYSCLK_MCLK;
			अवरोध;
		हाल DA7213_PLL_FREQ_OUT_98304000:
			अगर (da7213->mclk_rate == 12288000 ||
			    da7213->mclk_rate == 24576000 ||
			    da7213->mclk_rate == 49152000)
				mode = DA7213_SYSCLK_MCLK;

			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Disable PLL in standby */
		mode = DA7213_SYSCLK_MCLK;
	पूर्ण

	वापस _da7213_set_component_pll(component, 0, mode,
					 da7213->mclk_rate, da7213->out_rate);
पूर्ण

अटल पूर्णांक da7213_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Enable MCLK क्रम transition to ON state */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY) अणु
			अगर (da7213->mclk) अणु
				ret = clk_prepare_enable(da7213->mclk);
				अगर (ret) अणु
					dev_err(component->dev,
						"Failed to enable mclk\n");
					वापस ret;
				पूर्ण

				da7213_set_स्वतः_pll(component, true);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Enable VMID reference & master bias */
			snd_soc_component_update_bits(component, DA7213_REFERENCES,
					    DA7213_VMID_EN | DA7213_BIAS_EN,
					    DA7213_VMID_EN | DA7213_BIAS_EN);
		पूर्ण अन्यथा अणु
			/* Remove MCLK */
			अगर (da7213->mclk) अणु
				da7213_set_स्वतः_pll(component, false);
				clk_disable_unprepare(da7213->mclk);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Disable VMID reference & master bias */
		snd_soc_component_update_bits(component, DA7213_REFERENCES,
				    DA7213_VMID_EN | DA7213_BIAS_EN, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
/* DT */
अटल स्थिर काष्ठा of_device_id da7213_of_match[] = अणु
	अणु .compatible = "dlg,da7212", पूर्ण,
	अणु .compatible = "dlg,da7213", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da7213_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id da7213_acpi_match[] = अणु
	अणु "DLGS7212", 0पूर्ण,
	अणु "DLGS7213", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, da7213_acpi_match);
#पूर्ण_अगर

अटल क्रमागत da7213_micbias_voltage
	da7213_of_micbias_lvl(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 1600:
		वापस DA7213_MICBIAS_1_6V;
	हाल 2200:
		वापस DA7213_MICBIAS_2_2V;
	हाल 2500:
		वापस DA7213_MICBIAS_2_5V;
	हाल 3000:
		वापस DA7213_MICBIAS_3_0V;
	शेष:
		dev_warn(component->dev, "Invalid micbias level\n");
		वापस DA7213_MICBIAS_2_2V;
	पूर्ण
पूर्ण

अटल क्रमागत da7213_dmic_data_sel
	da7213_of_dmic_data_sel(काष्ठा snd_soc_component *component, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "lrise_rfall")) अणु
		वापस DA7213_DMIC_DATA_LRISE_RFALL;
	पूर्ण अन्यथा अगर (!म_भेद(str, "lfall_rrise")) अणु
		वापस DA7213_DMIC_DATA_LFALL_RRISE;
	पूर्ण अन्यथा अणु
		dev_warn(component->dev, "Invalid DMIC data select type\n");
		वापस DA7213_DMIC_DATA_LRISE_RFALL;
	पूर्ण
पूर्ण

अटल क्रमागत da7213_dmic_samplephase
	da7213_of_dmic_samplephase(काष्ठा snd_soc_component *component, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "on_clkedge")) अणु
		वापस DA7213_DMIC_SAMPLE_ON_CLKEDGE;
	पूर्ण अन्यथा अगर (!म_भेद(str, "between_clkedge")) अणु
		वापस DA7213_DMIC_SAMPLE_BETWEEN_CLKEDGE;
	पूर्ण अन्यथा अणु
		dev_warn(component->dev, "Invalid DMIC sample phase\n");
		वापस DA7213_DMIC_SAMPLE_ON_CLKEDGE;
	पूर्ण
पूर्ण

अटल क्रमागत da7213_dmic_clk_rate
	da7213_of_dmic_clkrate(काष्ठा snd_soc_component *component, u32 val)
अणु
	चयन (val) अणु
	हाल 1500000:
		वापस DA7213_DMIC_CLK_1_5MHZ;
	हाल 3000000:
		वापस DA7213_DMIC_CLK_3_0MHZ;
	शेष:
		dev_warn(component->dev, "Invalid DMIC clock rate\n");
		वापस DA7213_DMIC_CLK_1_5MHZ;
	पूर्ण
पूर्ण

अटल काष्ठा da7213_platक्रमm_data
	*da7213_fw_to_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा device *dev = component->dev;
	काष्ठा da7213_platक्रमm_data *pdata;
	स्थिर अक्षर *fw_str;
	u32 fw_val32;

	pdata = devm_kzalloc(component->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	अगर (device_property_पढ़ो_u32(dev, "dlg,micbias1-lvl", &fw_val32) >= 0)
		pdata->micbias1_lvl = da7213_of_micbias_lvl(component, fw_val32);
	अन्यथा
		pdata->micbias1_lvl = DA7213_MICBIAS_2_2V;

	अगर (device_property_पढ़ो_u32(dev, "dlg,micbias2-lvl", &fw_val32) >= 0)
		pdata->micbias2_lvl = da7213_of_micbias_lvl(component, fw_val32);
	अन्यथा
		pdata->micbias2_lvl = DA7213_MICBIAS_2_2V;

	अगर (!device_property_पढ़ो_string(dev, "dlg,dmic-data-sel", &fw_str))
		pdata->dmic_data_sel = da7213_of_dmic_data_sel(component, fw_str);
	अन्यथा
		pdata->dmic_data_sel = DA7213_DMIC_DATA_LRISE_RFALL;

	अगर (!device_property_पढ़ो_string(dev, "dlg,dmic-samplephase", &fw_str))
		pdata->dmic_samplephase =
			da7213_of_dmic_samplephase(component, fw_str);
	अन्यथा
		pdata->dmic_samplephase = DA7213_DMIC_SAMPLE_ON_CLKEDGE;

	अगर (device_property_पढ़ो_u32(dev, "dlg,dmic-clkrate", &fw_val32) >= 0)
		pdata->dmic_clk_rate = da7213_of_dmic_clkrate(component, fw_val32);
	अन्यथा
		pdata->dmic_clk_rate = DA7213_DMIC_CLK_3_0MHZ;

	वापस pdata;
पूर्ण

अटल पूर्णांक da7213_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7213_priv *da7213 = snd_soc_component_get_drvdata(component);

	pm_runसमय_get_sync(component->dev);

	/* Default to using ALC स्वतः offset calibration mode. */
	snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
			    DA7213_ALC_CALIB_MODE_MAN, 0);
	da7213->alc_calib_स्वतः = true;

	/* Default PC counter to मुक्त-running */
	snd_soc_component_update_bits(component, DA7213_PC_COUNT, DA7213_PC_FREERUN_MASK,
			    DA7213_PC_FREERUN_MASK);

	/* Enable all Gain Ramps */
	snd_soc_component_update_bits(component, DA7213_AUX_L_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_AUX_R_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_MIXIN_L_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_MIXIN_R_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_L_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_R_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_DAC_L_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_DAC_R_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_HP_L_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_HP_R_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);
	snd_soc_component_update_bits(component, DA7213_LINE_CTRL,
			    DA7213_GAIN_RAMP_EN, DA7213_GAIN_RAMP_EN);

	/*
	 * There are two separate control bits क्रम input and output mixers as
	 * well as headphone and line outs.
	 * One to enable corresponding amplअगरier and other to enable its
	 * output. As amplअगरier bits are related to घातer control, they are
	 * being managed by DAPM जबतक other (non घातer related) bits are
	 * enabled here
	 */
	snd_soc_component_update_bits(component, DA7213_MIXIN_L_CTRL,
			    DA7213_MIXIN_MIX_EN, DA7213_MIXIN_MIX_EN);
	snd_soc_component_update_bits(component, DA7213_MIXIN_R_CTRL,
			    DA7213_MIXIN_MIX_EN, DA7213_MIXIN_MIX_EN);

	snd_soc_component_update_bits(component, DA7213_MIXOUT_L_CTRL,
			    DA7213_MIXOUT_MIX_EN, DA7213_MIXOUT_MIX_EN);
	snd_soc_component_update_bits(component, DA7213_MIXOUT_R_CTRL,
			    DA7213_MIXOUT_MIX_EN, DA7213_MIXOUT_MIX_EN);

	snd_soc_component_update_bits(component, DA7213_HP_L_CTRL,
			    DA7213_HP_AMP_OE, DA7213_HP_AMP_OE);
	snd_soc_component_update_bits(component, DA7213_HP_R_CTRL,
			    DA7213_HP_AMP_OE, DA7213_HP_AMP_OE);

	snd_soc_component_update_bits(component, DA7213_LINE_CTRL,
			    DA7213_LINE_AMP_OE, DA7213_LINE_AMP_OE);

	/* Handle DT/Platक्रमm data */
	da7213->pdata = dev_get_platdata(component->dev);
	अगर (!da7213->pdata)
		da7213->pdata = da7213_fw_to_pdata(component);

	/* Set platक्रमm data values */
	अगर (da7213->pdata) अणु
		काष्ठा da7213_platक्रमm_data *pdata = da7213->pdata;
		u8 micbias_lvl = 0, dmic_cfg = 0;

		/* Set Mic Bias voltages */
		चयन (pdata->micbias1_lvl) अणु
		हाल DA7213_MICBIAS_1_6V:
		हाल DA7213_MICBIAS_2_2V:
		हाल DA7213_MICBIAS_2_5V:
		हाल DA7213_MICBIAS_3_0V:
			micbias_lvl |= (pdata->micbias1_lvl <<
					DA7213_MICBIAS1_LEVEL_SHIFT);
			अवरोध;
		पूर्ण
		चयन (pdata->micbias2_lvl) अणु
		हाल DA7213_MICBIAS_1_6V:
		हाल DA7213_MICBIAS_2_2V:
		हाल DA7213_MICBIAS_2_5V:
		हाल DA7213_MICBIAS_3_0V:
			micbias_lvl |= (pdata->micbias2_lvl <<
					 DA7213_MICBIAS2_LEVEL_SHIFT);
			अवरोध;
		पूर्ण
		snd_soc_component_update_bits(component, DA7213_MICBIAS_CTRL,
				    DA7213_MICBIAS1_LEVEL_MASK |
				    DA7213_MICBIAS2_LEVEL_MASK, micbias_lvl);

		/* Set DMIC configuration */
		चयन (pdata->dmic_data_sel) अणु
		हाल DA7213_DMIC_DATA_LFALL_RRISE:
		हाल DA7213_DMIC_DATA_LRISE_RFALL:
			dmic_cfg |= (pdata->dmic_data_sel <<
				     DA7213_DMIC_DATA_SEL_SHIFT);
			अवरोध;
		पूर्ण
		चयन (pdata->dmic_samplephase) अणु
		हाल DA7213_DMIC_SAMPLE_ON_CLKEDGE:
		हाल DA7213_DMIC_SAMPLE_BETWEEN_CLKEDGE:
			dmic_cfg |= (pdata->dmic_samplephase <<
				     DA7213_DMIC_SAMPLEPHASE_SHIFT);
			अवरोध;
		पूर्ण
		चयन (pdata->dmic_clk_rate) अणु
		हाल DA7213_DMIC_CLK_3_0MHZ:
		हाल DA7213_DMIC_CLK_1_5MHZ:
			dmic_cfg |= (pdata->dmic_clk_rate <<
				     DA7213_DMIC_CLK_RATE_SHIFT);
			अवरोध;
		पूर्ण
		snd_soc_component_update_bits(component, DA7213_MIC_CONFIG,
				    DA7213_DMIC_DATA_SEL_MASK |
				    DA7213_DMIC_SAMPLEPHASE_MASK |
				    DA7213_DMIC_CLK_RATE_MASK, dmic_cfg);
	पूर्ण

	pm_runसमय_put_sync(component->dev);

	/* Check अगर MCLK provided */
	da7213->mclk = devm_clk_get(component->dev, "mclk");
	अगर (IS_ERR(da7213->mclk)) अणु
		अगर (PTR_ERR(da7213->mclk) != -ENOENT)
			वापस PTR_ERR(da7213->mclk);
		अन्यथा
			da7213->mclk = शून्य;
	पूर्ण अन्यथा अणु
		/* Do स्वतःmatic PLL handling assuming fixed घड़ी until
		 * set_pll() has been called. This makes the codec usable
		 * with the simple-audio-card driver. */
		da7213->fixed_clk_स्वतः_pll = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_da7213 = अणु
	.probe			= da7213_probe,
	.set_bias_level		= da7213_set_bias_level,
	.controls		= da7213_snd_controls,
	.num_controls		= ARRAY_SIZE(da7213_snd_controls),
	.dapm_widमाला_लो		= da7213_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(da7213_dapm_widमाला_लो),
	.dapm_routes		= da7213_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(da7213_audio_map),
	.set_sysclk		= da7213_set_component_sysclk,
	.set_pll		= da7213_set_component_pll,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config da7213_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = da7213_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(da7213_reg_शेषs),
	.अस्थिर_reg = da7213_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल व्योम da7213_घातer_off(व्योम *data)
अणु
	काष्ठा da7213_priv *da7213 = data;
	regulator_bulk_disable(DA7213_NUM_SUPPLIES, da7213->supplies);
पूर्ण

अटल स्थिर अक्षर *da7213_supply_names[DA7213_NUM_SUPPLIES] = अणु
	[DA7213_SUPPLY_VDDA] = "VDDA",
	[DA7213_SUPPLY_VDDIO] = "VDDIO",
पूर्ण;

अटल पूर्णांक da7213_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da7213_priv *da7213;
	पूर्णांक i, ret;

	da7213 = devm_kzalloc(&i2c->dev, माप(*da7213), GFP_KERNEL);
	अगर (!da7213)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, da7213);

	/* Get required supplies */
	क्रम (i = 0; i < DA7213_NUM_SUPPLIES; ++i)
		da7213->supplies[i].supply = da7213_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, DA7213_NUM_SUPPLIES,
				      da7213->supplies);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(DA7213_NUM_SUPPLIES, da7213->supplies);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&i2c->dev, da7213_घातer_off, da7213);
	अगर (ret < 0)
		वापस ret;

	da7213->regmap = devm_regmap_init_i2c(i2c, &da7213_regmap_config);
	अगर (IS_ERR(da7213->regmap)) अणु
		ret = PTR_ERR(da7213->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&i2c->dev, 100);
	pm_runसमय_use_स्वतःsuspend(&i2c->dev);
	pm_runसमय_set_active(&i2c->dev);
	pm_runसमय_enable(&i2c->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_da7213, &da7213_dai, 1);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to register da7213 component: %d\n",
			ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused da7213_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा da7213_priv *da7213 = dev_get_drvdata(dev);

	regcache_cache_only(da7213->regmap, true);
	regcache_mark_dirty(da7213->regmap);
	regulator_bulk_disable(DA7213_NUM_SUPPLIES, da7213->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused da7213_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा da7213_priv *da7213 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(DA7213_NUM_SUPPLIES, da7213->supplies);
	अगर (ret < 0)
		वापस ret;
	regcache_cache_only(da7213->regmap, false);
	regcache_sync(da7213->regmap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops da7213_pm = अणु
	SET_RUNTIME_PM_OPS(da7213_runसमय_suspend, da7213_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id da7213_i2c_id[] = अणु
	अणु "da7213", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da7213_i2c_id);

/* I2C codec control layer */
अटल काष्ठा i2c_driver da7213_i2c_driver = अणु
	.driver = अणु
		.name = "da7213",
		.of_match_table = of_match_ptr(da7213_of_match),
		.acpi_match_table = ACPI_PTR(da7213_acpi_match),
		.pm = &da7213_pm,
	पूर्ण,
	.probe		= da7213_i2c_probe,
	.id_table	= da7213_i2c_id,
पूर्ण;

module_i2c_driver(da7213_i2c_driver);

MODULE_DESCRIPTION("ASoC DA7213 Codec driver");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
