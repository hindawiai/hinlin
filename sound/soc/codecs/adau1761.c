<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ADAU1361/ADAU1461/ADAU1761/ADAU1961 codec
 *
 * Copyright 2011-2013 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/platक्रमm_data/adau17x1.h>

#समावेश "adau17x1.h"
#समावेश "adau1761.h"

#घोषणा ADAU1761_DIGMIC_JACKDETECT	0x4008
#घोषणा ADAU1761_REC_MIXER_LEFT0	0x400a
#घोषणा ADAU1761_REC_MIXER_LEFT1	0x400b
#घोषणा ADAU1761_REC_MIXER_RIGHT0	0x400c
#घोषणा ADAU1761_REC_MIXER_RIGHT1	0x400d
#घोषणा ADAU1761_LEFT_DIFF_INPUT_VOL	0x400e
#घोषणा ADAU1761_RIGHT_DIFF_INPUT_VOL	0x400f
#घोषणा ADAU1761_ALC_CTRL0		0x4011
#घोषणा ADAU1761_ALC_CTRL1		0x4012
#घोषणा ADAU1761_ALC_CTRL2		0x4013
#घोषणा ADAU1761_ALC_CTRL3		0x4014
#घोषणा ADAU1761_PLAY_LR_MIXER_LEFT	0x4020
#घोषणा ADAU1761_PLAY_MIXER_LEFT0	0x401c
#घोषणा ADAU1761_PLAY_MIXER_LEFT1	0x401d
#घोषणा ADAU1761_PLAY_MIXER_RIGHT0	0x401e
#घोषणा ADAU1761_PLAY_MIXER_RIGHT1	0x401f
#घोषणा ADAU1761_PLAY_LR_MIXER_RIGHT	0x4021
#घोषणा ADAU1761_PLAY_MIXER_MONO	0x4022
#घोषणा ADAU1761_PLAY_HP_LEFT_VOL	0x4023
#घोषणा ADAU1761_PLAY_HP_RIGHT_VOL	0x4024
#घोषणा ADAU1761_PLAY_LINE_LEFT_VOL	0x4025
#घोषणा ADAU1761_PLAY_LINE_RIGHT_VOL	0x4026
#घोषणा ADAU1761_PLAY_MONO_OUTPUT_VOL	0x4027
#घोषणा ADAU1761_POP_CLICK_SUPPRESS	0x4028
#घोषणा ADAU1761_JACK_DETECT_PIN	0x4031
#घोषणा ADAU1761_DEJITTER		0x4036
#घोषणा ADAU1761_CLK_ENABLE0		0x40f9
#घोषणा ADAU1761_CLK_ENABLE1		0x40fa

#घोषणा ADAU1761_DIGMIC_JACKDETECT_ACTIVE_LOW	BIT(0)
#घोषणा ADAU1761_DIGMIC_JACKDETECT_DIGMIC	BIT(5)

#घोषणा ADAU1761_DIFF_INPUT_VOL_LDEN		BIT(0)

#घोषणा ADAU1761_PLAY_MONO_OUTPUT_VOL_MODE_HP	BIT(0)
#घोषणा ADAU1761_PLAY_MONO_OUTPUT_VOL_UNMUTE	BIT(1)

#घोषणा ADAU1761_PLAY_HP_RIGHT_VOL_MODE_HP	BIT(0)

#घोषणा ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP	BIT(0)

#घोषणा ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP	BIT(0)


#घोषणा ADAU1761_FIRMWARE "adau1761.bin"

अटल स्थिर काष्ठा reg_शेष adau1761_reg_शेषs[] = अणु
	अणु ADAU1761_DEJITTER,			0x03 पूर्ण,
	अणु ADAU1761_DIGMIC_JACKDETECT,		0x00 पूर्ण,
	अणु ADAU1761_REC_MIXER_LEFT0,		0x00 पूर्ण,
	अणु ADAU1761_REC_MIXER_LEFT1,		0x00 पूर्ण,
	अणु ADAU1761_REC_MIXER_RIGHT0,		0x00 पूर्ण,
	अणु ADAU1761_REC_MIXER_RIGHT1,		0x00 पूर्ण,
	अणु ADAU1761_LEFT_DIFF_INPUT_VOL,		0x00 पूर्ण,
	अणु ADAU1761_ALC_CTRL0,			0x00 पूर्ण,
	अणु ADAU1761_ALC_CTRL1,			0x00 पूर्ण,
	अणु ADAU1761_ALC_CTRL2,			0x00 पूर्ण,
	अणु ADAU1761_ALC_CTRL3,			0x00 पूर्ण,
	अणु ADAU1761_RIGHT_DIFF_INPUT_VOL,	0x00 पूर्ण,
	अणु ADAU1761_PLAY_LR_MIXER_LEFT,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_MIXER_LEFT0,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_MIXER_LEFT1,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_MIXER_RIGHT0,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_MIXER_RIGHT1,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_LR_MIXER_RIGHT,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_MIXER_MONO,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_HP_LEFT_VOL,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_HP_RIGHT_VOL,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_LINE_LEFT_VOL,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_LINE_RIGHT_VOL,		0x00 पूर्ण,
	अणु ADAU1761_PLAY_MONO_OUTPUT_VOL,	0x00 पूर्ण,
	अणु ADAU1761_POP_CLICK_SUPPRESS,		0x00 पूर्ण,
	अणु ADAU1761_JACK_DETECT_PIN,		0x00 पूर्ण,
	अणु ADAU1761_CLK_ENABLE0,			0x00 पूर्ण,
	अणु ADAU1761_CLK_ENABLE1,			0x00 पूर्ण,
	अणु ADAU17X1_CLOCK_CONTROL,		0x00 पूर्ण,
	अणु ADAU17X1_PLL_CONTROL,			0x00 पूर्ण,
	अणु ADAU17X1_REC_POWER_MGMT,		0x00 पूर्ण,
	अणु ADAU17X1_MICBIAS,			0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_PORT0,		0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_PORT1,		0x00 पूर्ण,
	अणु ADAU17X1_CONVERTER0,			0x00 पूर्ण,
	अणु ADAU17X1_CONVERTER1,			0x00 पूर्ण,
	अणु ADAU17X1_LEFT_INPUT_DIGITAL_VOL,	0x00 पूर्ण,
	अणु ADAU17X1_RIGHT_INPUT_DIGITAL_VOL,	0x00 पूर्ण,
	अणु ADAU17X1_ADC_CONTROL,			0x00 पूर्ण,
	अणु ADAU17X1_PLAY_POWER_MGMT,		0x00 पूर्ण,
	अणु ADAU17X1_DAC_CONTROL0,		0x00 पूर्ण,
	अणु ADAU17X1_DAC_CONTROL1,		0x00 पूर्ण,
	अणु ADAU17X1_DAC_CONTROL2,		0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_PORT_PAD,		0xaa पूर्ण,
	अणु ADAU17X1_CONTROL_PORT_PAD0,		0xaa पूर्ण,
	अणु ADAU17X1_CONTROL_PORT_PAD1,		0x00 पूर्ण,
	अणु ADAU17X1_DSP_SAMPLING_RATE,		0x01 पूर्ण,
	अणु ADAU17X1_SERIAL_INPUT_ROUTE,		0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_OUTPUT_ROUTE,		0x00 पूर्ण,
	अणु ADAU17X1_DSP_ENABLE,			0x00 पूर्ण,
	अणु ADAU17X1_DSP_RUN,			0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_SAMPLING_RATE,	0x00 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_sing_in_tlv, -1500, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_dअगरf_in_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_out_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_sidetone_tlv, -1800, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_boost_tlv, -600, 600, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_pga_boost_tlv, -2000, 2000, 1);

अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_alc_max_gain_tlv, -1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_alc_target_tlv, -2850, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1761_alc_ng_threshold_tlv, -7650, 150, 0);

अटल स्थिर अचिन्हित पूर्णांक adau1761_bias_select_values[] = अणु
	0, 2, 3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_bias_select_text[] = अणु
	"Normal operation", "Enhanced performance", "Power saving",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_bias_select_extreme_text[] = अणु
	"Normal operation", "Extreme power saving", "Enhanced performance",
	"Power saving",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1761_adc_bias_क्रमागत,
		ADAU17X1_REC_POWER_MGMT, 3, adau1761_bias_select_extreme_text);
अटल SOC_ENUM_SINGLE_DECL(adau1761_hp_bias_क्रमागत,
		ADAU17X1_PLAY_POWER_MGMT, 6, adau1761_bias_select_extreme_text);
अटल SOC_ENUM_SINGLE_DECL(adau1761_dac_bias_क्रमागत,
		ADAU17X1_PLAY_POWER_MGMT, 4, adau1761_bias_select_extreme_text);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1761_playback_bias_क्रमागत,
		ADAU17X1_PLAY_POWER_MGMT, 2, 0x3, adau1761_bias_select_text,
		adau1761_bias_select_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1761_capture_bias_क्रमागत,
		ADAU17X1_REC_POWER_MGMT, 1, 0x3, adau1761_bias_select_text,
		adau1761_bias_select_values);

अटल स्थिर अचिन्हित पूर्णांक adau1761_pga_slew_समय_values[] = अणु
	3, 0, 1, 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_pga_slew_समय_प्रकारext[] = अणु
	"Off",
	"24 ms",
	"48 ms",
	"96 ms",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_alc_function_text[] = अणु
	"Off",
	"Right",
	"Left",
	"Stereo",
	"DSP control",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_alc_hold_समय_प्रकारext[] = अणु
	"2.67 ms",
	"5.34 ms",
	"10.68 ms",
	"21.36 ms",
	"42.72 ms",
	"85.44 ms",
	"170.88 ms",
	"341.76 ms",
	"683.52 ms",
	"1367 ms",
	"2734.1 ms",
	"5468.2 ms",
	"10936 ms",
	"21873 ms",
	"43745 ms",
	"87491 ms",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_alc_attack_समय_प्रकारext[] = अणु
	"6 ms",
	"12 ms",
	"24 ms",
	"48 ms",
	"96 ms",
	"192 ms",
	"384 ms",
	"768 ms",
	"1540 ms",
	"3070 ms",
	"6140 ms",
	"12290 ms",
	"24580 ms",
	"49150 ms",
	"98300 ms",
	"196610 ms",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_alc_decay_समय_प्रकारext[] = अणु
	"24 ms",
	"48 ms",
	"96 ms",
	"192 ms",
	"384 ms",
	"768 ms",
	"15400 ms",
	"30700 ms",
	"61400 ms",
	"12290 ms",
	"24580 ms",
	"49150 ms",
	"98300 ms",
	"196610 ms",
	"393220 ms",
	"786430 ms",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_alc_ng_type_text[] = अणु
	"Hold",
	"Mute",
	"Fade",
	"Fade + Mute",
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1761_pga_slew_समय_क्रमागत,
		ADAU1761_ALC_CTRL0, 6, 0x3, adau1761_pga_slew_समय_प्रकारext,
		adau1761_pga_slew_समय_values);
अटल SOC_ENUM_SINGLE_DECL(adau1761_alc_function_क्रमागत,
		ADAU1761_ALC_CTRL0, 0, adau1761_alc_function_text);
अटल SOC_ENUM_SINGLE_DECL(adau1761_alc_hold_समय_क्रमागत,
		ADAU1761_ALC_CTRL1, 4, adau1761_alc_hold_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(adau1761_alc_attack_समय_क्रमागत,
		ADAU1761_ALC_CTRL2, 4, adau1761_alc_attack_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(adau1761_alc_decay_समय_क्रमागत,
		ADAU1761_ALC_CTRL2, 0, adau1761_alc_decay_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(adau1761_alc_ng_type_क्रमागत,
		ADAU1761_ALC_CTRL3, 6, adau1761_alc_ng_type_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_jack_detect_controls[] = अणु
	SOC_SINGLE("Speaker Auto-mute Switch", ADAU1761_DIGMIC_JACKDETECT,
		4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_dअगरferential_mode_controls[] = अणु
	SOC_DOUBLE_R_TLV("Capture Volume", ADAU1761_LEFT_DIFF_INPUT_VOL,
		ADAU1761_RIGHT_DIFF_INPUT_VOL, 2, 0x3f, 0,
		adau1761_dअगरf_in_tlv),
	SOC_DOUBLE_R("Capture Switch", ADAU1761_LEFT_DIFF_INPUT_VOL,
		ADAU1761_RIGHT_DIFF_INPUT_VOL, 1, 1, 0),

	SOC_DOUBLE_R_TLV("PGA Boost Capture Volume", ADAU1761_REC_MIXER_LEFT1,
		ADAU1761_REC_MIXER_RIGHT1, 3, 2, 0, adau1761_pga_boost_tlv),

	SOC_ENUM("PGA Capture Slew Time", adau1761_pga_slew_समय_क्रमागत),

	SOC_SINGLE_TLV("ALC Capture Max Gain Volume", ADAU1761_ALC_CTRL0,
		3, 7, 0, adau1761_alc_max_gain_tlv),
	SOC_ENUM("ALC Capture Function", adau1761_alc_function_क्रमागत),
	SOC_ENUM("ALC Capture Hold Time", adau1761_alc_hold_समय_क्रमागत),
	SOC_SINGLE_TLV("ALC Capture Target Volume", ADAU1761_ALC_CTRL1,
		0, 15, 0, adau1761_alc_target_tlv),
	SOC_ENUM("ALC Capture Attack Time", adau1761_alc_decay_समय_क्रमागत),
	SOC_ENUM("ALC Capture Decay Time", adau1761_alc_attack_समय_क्रमागत),
	SOC_ENUM("ALC Capture Noise Gate Type", adau1761_alc_ng_type_क्रमागत),
	SOC_SINGLE("ALC Capture Noise Gate Switch",
		ADAU1761_ALC_CTRL3, 5, 1, 0),
	SOC_SINGLE_TLV("ALC Capture Noise Gate Threshold Volume",
		ADAU1761_ALC_CTRL3, 0, 31, 0, adau1761_alc_ng_threshold_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_single_mode_controls[] = अणु
	SOC_SINGLE_TLV("Input 1 Capture Volume", ADAU1761_REC_MIXER_LEFT0,
		4, 7, 0, adau1761_sing_in_tlv),
	SOC_SINGLE_TLV("Input 2 Capture Volume", ADAU1761_REC_MIXER_LEFT0,
		1, 7, 0, adau1761_sing_in_tlv),
	SOC_SINGLE_TLV("Input 3 Capture Volume", ADAU1761_REC_MIXER_RIGHT0,
		4, 7, 0, adau1761_sing_in_tlv),
	SOC_SINGLE_TLV("Input 4 Capture Volume", ADAU1761_REC_MIXER_RIGHT0,
		1, 7, 0, adau1761_sing_in_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_controls[] = अणु
	SOC_DOUBLE_R_TLV("Aux Capture Volume", ADAU1761_REC_MIXER_LEFT1,
		ADAU1761_REC_MIXER_RIGHT1, 0, 7, 0, adau1761_sing_in_tlv),

	SOC_DOUBLE_R_TLV("Headphone Playback Volume", ADAU1761_PLAY_HP_LEFT_VOL,
		ADAU1761_PLAY_HP_RIGHT_VOL, 2, 0x3f, 0, adau1761_out_tlv),
	SOC_DOUBLE_R("Headphone Playback Switch", ADAU1761_PLAY_HP_LEFT_VOL,
		ADAU1761_PLAY_HP_RIGHT_VOL, 1, 1, 0),
	SOC_DOUBLE_R_TLV("Lineout Playback Volume", ADAU1761_PLAY_LINE_LEFT_VOL,
		ADAU1761_PLAY_LINE_RIGHT_VOL, 2, 0x3f, 0, adau1761_out_tlv),
	SOC_DOUBLE_R("Lineout Playback Switch", ADAU1761_PLAY_LINE_LEFT_VOL,
		ADAU1761_PLAY_LINE_RIGHT_VOL, 1, 1, 0),

	SOC_ENUM("ADC Bias", adau1761_adc_bias_क्रमागत),
	SOC_ENUM("DAC Bias", adau1761_dac_bias_क्रमागत),
	SOC_ENUM("Capture Bias", adau1761_capture_bias_क्रमागत),
	SOC_ENUM("Playback Bias", adau1761_playback_bias_क्रमागत),
	SOC_ENUM("Headphone Bias", adau1761_hp_bias_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_mono_controls[] = अणु
	SOC_SINGLE_TLV("Mono Playback Volume", ADAU1761_PLAY_MONO_OUTPUT_VOL,
		2, 0x3f, 0, adau1761_out_tlv),
	SOC_SINGLE("Mono Playback Switch", ADAU1761_PLAY_MONO_OUTPUT_VOL,
		1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_left_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Left DAC Switch",
		ADAU1761_PLAY_MIXER_LEFT0, 5, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("Right DAC Switch",
		ADAU1761_PLAY_MIXER_LEFT0, 6, 1, 0),
	SOC_DAPM_SINGLE_TLV("Aux Bypass Volume",
		ADAU1761_PLAY_MIXER_LEFT0, 1, 8, 0, adau1761_sidetone_tlv),
	SOC_DAPM_SINGLE_TLV("Right Bypass Volume",
		ADAU1761_PLAY_MIXER_LEFT1, 4, 8, 0, adau1761_sidetone_tlv),
	SOC_DAPM_SINGLE_TLV("Left Bypass Volume",
		ADAU1761_PLAY_MIXER_LEFT1, 0, 8, 0, adau1761_sidetone_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_right_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Left DAC Switch",
		ADAU1761_PLAY_MIXER_RIGHT0, 5, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("Right DAC Switch",
		ADAU1761_PLAY_MIXER_RIGHT0, 6, 1, 0),
	SOC_DAPM_SINGLE_TLV("Aux Bypass Volume",
		ADAU1761_PLAY_MIXER_RIGHT0, 1, 8, 0, adau1761_sidetone_tlv),
	SOC_DAPM_SINGLE_TLV("Right Bypass Volume",
		ADAU1761_PLAY_MIXER_RIGHT1, 4, 8, 0, adau1761_sidetone_tlv),
	SOC_DAPM_SINGLE_TLV("Left Bypass Volume",
		ADAU1761_PLAY_MIXER_RIGHT1, 0, 8, 0, adau1761_sidetone_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_left_lr_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_TLV("Left Volume",
		ADAU1761_PLAY_LR_MIXER_LEFT, 1, 2, 0, adau1761_boost_tlv),
	SOC_DAPM_SINGLE_TLV("Right Volume",
		ADAU1761_PLAY_LR_MIXER_LEFT, 3, 2, 0, adau1761_boost_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_right_lr_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_TLV("Left Volume",
		ADAU1761_PLAY_LR_MIXER_RIGHT, 1, 2, 0, adau1761_boost_tlv),
	SOC_DAPM_SINGLE_TLV("Right Volume",
		ADAU1761_PLAY_LR_MIXER_RIGHT, 3, 2, 0, adau1761_boost_tlv),
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1761_input_mux_text[] = अणु
	"ADC", "DMIC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1761_input_mux_क्रमागत,
	ADAU17X1_ADC_CONTROL, 2, adau1761_input_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1761_input_mux_control =
	SOC_DAPM_ENUM("Input Select", adau1761_input_mux_क्रमागत);

अटल पूर्णांक adau1761_dejitter_fixup(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	/* After any घातer changes have been made the dejitter circuit
	 * has to be reinitialized. */
	regmap_ग_लिखो(adau->regmap, ADAU1761_DEJITTER, 0);
	अगर (!adau->master)
		regmap_ग_लिखो(adau->regmap, ADAU1761_DEJITTER, 3);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1x61_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Left Input Mixer", ADAU1761_REC_MIXER_LEFT0, 0, 0,
		शून्य, 0),
	SND_SOC_DAPM_MIXER("Right Input Mixer", ADAU1761_REC_MIXER_RIGHT0, 0, 0,
		शून्य, 0),

	SOC_MIXER_ARRAY("Left Playback Mixer", ADAU1761_PLAY_MIXER_LEFT0,
		0, 0, adau1761_left_mixer_controls),
	SOC_MIXER_ARRAY("Right Playback Mixer", ADAU1761_PLAY_MIXER_RIGHT0,
		0, 0, adau1761_right_mixer_controls),
	SOC_MIXER_ARRAY("Left LR Playback Mixer", ADAU1761_PLAY_LR_MIXER_LEFT,
		0, 0, adau1761_left_lr_mixer_controls),
	SOC_MIXER_ARRAY("Right LR Playback Mixer", ADAU1761_PLAY_LR_MIXER_RIGHT,
		0, 0, adau1761_right_lr_mixer_controls),

	SND_SOC_DAPM_SUPPLY("Headphone", ADAU1761_PLAY_HP_LEFT_VOL,
		0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("SYSCLK", 2, SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_POST("Dejitter fixup", adau1761_dejitter_fixup),

	SND_SOC_DAPM_INPUT("LAUX"),
	SND_SOC_DAPM_INPUT("RAUX"),
	SND_SOC_DAPM_INPUT("LINP"),
	SND_SOC_DAPM_INPUT("LINN"),
	SND_SOC_DAPM_INPUT("RINP"),
	SND_SOC_DAPM_INPUT("RINN"),

	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),
	SND_SOC_DAPM_OUTPUT("LHP"),
	SND_SOC_DAPM_OUTPUT("RHP"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1761_mono_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Mono Playback Mixer", ADAU1761_PLAY_MIXER_MONO,
		0, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("MONOOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1761_capless_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY_S("Headphone VGND", 1, ADAU1761_PLAY_MIXER_MONO,
		0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1x61_dapm_routes[] = अणु
	अणु "Left Input Mixer", शून्य, "LINP" पूर्ण,
	अणु "Left Input Mixer", शून्य, "LINN" पूर्ण,
	अणु "Left Input Mixer", शून्य, "LAUX" पूर्ण,

	अणु "Right Input Mixer", शून्य, "RINP" पूर्ण,
	अणु "Right Input Mixer", शून्य, "RINN" पूर्ण,
	अणु "Right Input Mixer", शून्य, "RAUX" पूर्ण,

	अणु "Left Playback Mixer", शून्य, "Left Playback Enable"पूर्ण,
	अणु "Right Playback Mixer", शून्य, "Right Playback Enable"पूर्ण,
	अणु "Left LR Playback Mixer", शून्य, "Left Playback Enable"पूर्ण,
	अणु "Right LR Playback Mixer", शून्य, "Right Playback Enable"पूर्ण,

	अणु "Left Playback Mixer", "Left DAC Switch", "Left DAC" पूर्ण,
	अणु "Left Playback Mixer", "Right DAC Switch", "Right DAC" पूर्ण,

	अणु "Right Playback Mixer", "Left DAC Switch", "Left DAC" पूर्ण,
	अणु "Right Playback Mixer", "Right DAC Switch", "Right DAC" पूर्ण,

	अणु "Left LR Playback Mixer", "Left Volume", "Left Playback Mixer" पूर्ण,
	अणु "Left LR Playback Mixer", "Right Volume", "Right Playback Mixer" पूर्ण,

	अणु "Right LR Playback Mixer", "Left Volume", "Left Playback Mixer" पूर्ण,
	अणु "Right LR Playback Mixer", "Right Volume", "Right Playback Mixer" पूर्ण,

	अणु "LHP", शून्य, "Left Playback Mixer" पूर्ण,
	अणु "RHP", शून्य, "Right Playback Mixer" पूर्ण,

	अणु "LHP", शून्य, "Headphone" पूर्ण,
	अणु "RHP", शून्य, "Headphone" पूर्ण,

	अणु "LOUT", शून्य, "Left LR Playback Mixer" पूर्ण,
	अणु "ROUT", शून्य, "Right LR Playback Mixer" पूर्ण,

	अणु "Left Playback Mixer", "Aux Bypass Volume", "LAUX" पूर्ण,
	अणु "Left Playback Mixer", "Left Bypass Volume", "Left Input Mixer" पूर्ण,
	अणु "Left Playback Mixer", "Right Bypass Volume", "Right Input Mixer" पूर्ण,
	अणु "Right Playback Mixer", "Aux Bypass Volume", "RAUX" पूर्ण,
	अणु "Right Playback Mixer", "Left Bypass Volume", "Left Input Mixer" पूर्ण,
	अणु "Right Playback Mixer", "Right Bypass Volume", "Right Input Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1761_mono_dapm_routes[] = अणु
	अणु "Mono Playback Mixer", शून्य, "Left Playback Mixer" पूर्ण,
	अणु "Mono Playback Mixer", शून्य, "Right Playback Mixer" पूर्ण,

	अणु "MONOOUT", शून्य, "Mono Playback Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1761_capless_dapm_routes[] = अणु
	अणु "Headphone", शून्य, "Headphone VGND" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1761_dmic_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Left Decimator Mux", SND_SOC_NOPM, 0, 0,
		&adau1761_input_mux_control),
	SND_SOC_DAPM_MUX("Right Decimator Mux", SND_SOC_NOPM, 0, 0,
		&adau1761_input_mux_control),

	SND_SOC_DAPM_INPUT("DMIC"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1761_dmic_routes[] = अणु
	अणु "Left Decimator Mux", "ADC", "Left Input Mixer" पूर्ण,
	अणु "Left Decimator Mux", "DMIC", "DMIC" पूर्ण,
	अणु "Right Decimator Mux", "ADC", "Right Input Mixer" पूर्ण,
	अणु "Right Decimator Mux", "DMIC", "DMIC" पूर्ण,

	अणु "Left Decimator", शून्य, "Left Decimator Mux" पूर्ण,
	अणु "Right Decimator", शून्य, "Right Decimator Mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1761_no_dmic_routes[] = अणु
	अणु "Left Decimator", शून्य, "Left Input Mixer" पूर्ण,
	अणु "Right Decimator", शून्य, "Right Input Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1761_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("Serial Port Clock", ADAU1761_CLK_ENABLE0,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Serial Input Routing Clock", ADAU1761_CLK_ENABLE0,
		1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Serial Output Routing Clock", ADAU1761_CLK_ENABLE0,
		3, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Decimator Resync Clock", ADAU1761_CLK_ENABLE0,
		4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Interpolator Resync Clock", ADAU1761_CLK_ENABLE0,
		2, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Slew Clock", ADAU1761_CLK_ENABLE0, 6, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ALC Clock", ADAU1761_CLK_ENABLE0, 5, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("Digital Clock 0", 1, ADAU1761_CLK_ENABLE1,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("Digital Clock 1", 1, ADAU1761_CLK_ENABLE1,
		1, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1761_dapm_routes[] = अणु
	अणु "Left Decimator", शून्य, "Digital Clock 0", पूर्ण,
	अणु "Right Decimator", शून्य, "Digital Clock 0", पूर्ण,
	अणु "Left DAC", शून्य, "Digital Clock 0", पूर्ण,
	अणु "Right DAC", शून्य, "Digital Clock 0", पूर्ण,

	अणु "AIFCLK", शून्य, "Digital Clock 1" पूर्ण,

	अणु "Playback", शून्य, "Serial Port Clock" पूर्ण,
	अणु "Capture", शून्य, "Serial Port Clock" पूर्ण,
	अणु "Playback", शून्य, "Serial Input Routing Clock" पूर्ण,
	अणु "Capture", शून्य, "Serial Output Routing Clock" पूर्ण,

	अणु "Left Decimator", शून्य, "Decimator Resync Clock" पूर्ण,
	अणु "Right Decimator", शून्य, "Decimator Resync Clock" पूर्ण,
	अणु "Left DAC", शून्य, "Interpolator Resync Clock" पूर्ण,
	अणु "Right DAC", शून्य, "Interpolator Resync Clock" पूर्ण,

	अणु "DSP", शून्य, "Digital Clock 0" पूर्ण,

	अणु "Slew Clock", शून्य, "Digital Clock 0" पूर्ण,
	अणु "Right Playback Mixer", शून्य, "Slew Clock" पूर्ण,
	अणु "Left Playback Mixer", शून्य, "Slew Clock" पूर्ण,

	अणु "Left Input Mixer", शून्य, "ALC Clock" पूर्ण,
	अणु "Right Input Mixer", शून्य, "ALC Clock" पूर्ण,

	अणु "Digital Clock 0", शून्य, "SYSCLK" पूर्ण,
	अणु "Digital Clock 1", शून्य, "SYSCLK" पूर्ण,
पूर्ण;

अटल पूर्णांक adau1761_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regcache_cache_only(adau->regmap, false);
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN);
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(adau->regmap);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN, 0);
		regcache_cache_only(adau->regmap, true);
		अवरोध;

	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत adau1761_output_mode adau1761_get_lineout_mode(
	काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau1761_platक्रमm_data *pdata = component->dev->platक्रमm_data;

	अगर (pdata)
		वापस pdata->lineout_mode;

	वापस ADAU1761_OUTPUT_MODE_LINE;
पूर्ण

अटल पूर्णांक adau1761_setup_digmic_jackdetect(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau1761_platक्रमm_data *pdata = component->dev->platक्रमm_data;
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	क्रमागत adau1761_digmic_jackdet_pin_mode mode;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	अगर (pdata)
		mode = pdata->digmic_jackdetect_pin_mode;
	अन्यथा
		mode = ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE;

	चयन (mode) अणु
	हाल ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT:
		चयन (pdata->jackdetect_debounce_समय) अणु
		हाल ADAU1761_JACKDETECT_DEBOUNCE_5MS:
		हाल ADAU1761_JACKDETECT_DEBOUNCE_10MS:
		हाल ADAU1761_JACKDETECT_DEBOUNCE_20MS:
		हाल ADAU1761_JACKDETECT_DEBOUNCE_40MS:
			val |= pdata->jackdetect_debounce_समय << 6;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (pdata->jackdetect_active_low)
			val |= ADAU1761_DIGMIC_JACKDETECT_ACTIVE_LOW;

		ret = snd_soc_add_component_controls(component,
			adau1761_jack_detect_controls,
			ARRAY_SIZE(adau1761_jack_detect_controls));
		अगर (ret)
			वापस ret;
		fallthrough;
	हाल ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE:
		ret = snd_soc_dapm_add_routes(dapm, adau1761_no_dmic_routes,
			ARRAY_SIZE(adau1761_no_dmic_routes));
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC:
		ret = snd_soc_dapm_new_controls(dapm, adau1761_dmic_widमाला_लो,
			ARRAY_SIZE(adau1761_dmic_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, adau1761_dmic_routes,
			ARRAY_SIZE(adau1761_dmic_routes));
		अगर (ret)
			वापस ret;

		val |= ADAU1761_DIGMIC_JACKDETECT_DIGMIC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(adau->regmap, ADAU1761_DIGMIC_JACKDETECT, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1761_setup_headphone_mode(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	काष्ठा adau1761_platक्रमm_data *pdata = component->dev->platक्रमm_data;
	क्रमागत adau1761_output_mode mode;
	पूर्णांक ret;

	अगर (pdata)
		mode = pdata->headphone_mode;
	अन्यथा
		mode = ADAU1761_OUTPUT_MODE_HEADPHONE;

	चयन (mode) अणु
	हाल ADAU1761_OUTPUT_MODE_LINE:
		अवरोध;
	हाल ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_MONO_OUTPUT_VOL,
			ADAU1761_PLAY_MONO_OUTPUT_VOL_MODE_HP |
			ADAU1761_PLAY_MONO_OUTPUT_VOL_UNMUTE,
			ADAU1761_PLAY_MONO_OUTPUT_VOL_MODE_HP |
			ADAU1761_PLAY_MONO_OUTPUT_VOL_UNMUTE);
		fallthrough;
	हाल ADAU1761_OUTPUT_MODE_HEADPHONE:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_HP_RIGHT_VOL,
			ADAU1761_PLAY_HP_RIGHT_VOL_MODE_HP,
			ADAU1761_PLAY_HP_RIGHT_VOL_MODE_HP);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (mode == ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS) अणु
		ret = snd_soc_dapm_new_controls(dapm,
			adau1761_capless_dapm_widमाला_लो,
			ARRAY_SIZE(adau1761_capless_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;
		ret = snd_soc_dapm_add_routes(dapm,
			adau1761_capless_dapm_routes,
			ARRAY_SIZE(adau1761_capless_dapm_routes));
	पूर्ण अन्यथा अणु
		ret = snd_soc_add_component_controls(component, adau1761_mono_controls,
			ARRAY_SIZE(adau1761_mono_controls));
		अगर (ret)
			वापस ret;
		ret = snd_soc_dapm_new_controls(dapm,
			adau1761_mono_dapm_widमाला_लो,
			ARRAY_SIZE(adau1761_mono_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;
		ret = snd_soc_dapm_add_routes(dapm,
			adau1761_mono_dapm_routes,
			ARRAY_SIZE(adau1761_mono_dapm_routes));
	पूर्ण

	वापस ret;
पूर्ण

अटल bool adau1761_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADAU1761_DIGMIC_JACKDETECT:
	हाल ADAU1761_REC_MIXER_LEFT0:
	हाल ADAU1761_REC_MIXER_LEFT1:
	हाल ADAU1761_REC_MIXER_RIGHT0:
	हाल ADAU1761_REC_MIXER_RIGHT1:
	हाल ADAU1761_LEFT_DIFF_INPUT_VOL:
	हाल ADAU1761_RIGHT_DIFF_INPUT_VOL:
	हाल ADAU1761_PLAY_LR_MIXER_LEFT:
	हाल ADAU1761_PLAY_MIXER_LEFT0:
	हाल ADAU1761_PLAY_MIXER_LEFT1:
	हाल ADAU1761_PLAY_MIXER_RIGHT0:
	हाल ADAU1761_PLAY_MIXER_RIGHT1:
	हाल ADAU1761_PLAY_LR_MIXER_RIGHT:
	हाल ADAU1761_PLAY_MIXER_MONO:
	हाल ADAU1761_PLAY_HP_LEFT_VOL:
	हाल ADAU1761_PLAY_HP_RIGHT_VOL:
	हाल ADAU1761_PLAY_LINE_LEFT_VOL:
	हाल ADAU1761_PLAY_LINE_RIGHT_VOL:
	हाल ADAU1761_PLAY_MONO_OUTPUT_VOL:
	हाल ADAU1761_POP_CLICK_SUPPRESS:
	हाल ADAU1761_JACK_DETECT_PIN:
	हाल ADAU1761_DEJITTER:
	हाल ADAU1761_CLK_ENABLE0:
	हाल ADAU1761_CLK_ENABLE1:
	हाल ADAU1761_ALC_CTRL0:
	हाल ADAU1761_ALC_CTRL1:
	हाल ADAU1761_ALC_CTRL2:
	हाल ADAU1761_ALC_CTRL3:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस adau17x1_पढ़ोable_रेजिस्टर(dev, reg);
पूर्ण

अटल पूर्णांक adau1761_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau1761_platक्रमm_data *pdata = component->dev->platक्रमm_data;
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = adau17x1_add_widमाला_लो(component);
	अगर (ret < 0)
		वापस ret;

	अगर (pdata && pdata->input_dअगरferential) अणु
		regmap_update_bits(adau->regmap, ADAU1761_LEFT_DIFF_INPUT_VOL,
			ADAU1761_DIFF_INPUT_VOL_LDEN,
			ADAU1761_DIFF_INPUT_VOL_LDEN);
		regmap_update_bits(adau->regmap, ADAU1761_RIGHT_DIFF_INPUT_VOL,
			ADAU1761_DIFF_INPUT_VOL_LDEN,
			ADAU1761_DIFF_INPUT_VOL_LDEN);
		ret = snd_soc_add_component_controls(component,
			adau1761_dअगरferential_mode_controls,
			ARRAY_SIZE(adau1761_dअगरferential_mode_controls));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = snd_soc_add_component_controls(component,
			adau1761_single_mode_controls,
			ARRAY_SIZE(adau1761_single_mode_controls));
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (adau1761_get_lineout_mode(component)) अणु
	हाल ADAU1761_OUTPUT_MODE_LINE:
		अवरोध;
	हाल ADAU1761_OUTPUT_MODE_HEADPHONE:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_LINE_LEFT_VOL,
			ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP,
			ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP);
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_LINE_RIGHT_VOL,
			ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP,
			ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = adau1761_setup_headphone_mode(component);
	अगर (ret)
		वापस ret;

	ret = adau1761_setup_digmic_jackdetect(component);
	अगर (ret)
		वापस ret;

	अगर (adau->type == ADAU1761) अणु
		ret = snd_soc_dapm_new_controls(dapm, adau1761_dapm_widमाला_लो,
			ARRAY_SIZE(adau1761_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, adau1761_dapm_routes,
			ARRAY_SIZE(adau1761_dapm_routes));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = adau17x1_add_routes(component);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver adau1761_component_driver = अणु
	.probe			= adau1761_component_probe,
	.resume			= adau17x1_resume,
	.set_bias_level		= adau1761_set_bias_level,
	.controls		= adau1761_controls,
	.num_controls		= ARRAY_SIZE(adau1761_controls),
	.dapm_widमाला_लो		= adau1x61_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau1x61_dapm_widमाला_लो),
	.dapm_routes		= adau1x61_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(adau1x61_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#घोषणा ADAU1761_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | \
	SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver adau1361_dai_driver = अणु
	.name = "adau-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = ADAU1761_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = ADAU1761_FORMATS,
	पूर्ण,
	.ops = &adau17x1_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver adau1761_dai_driver = अणु
	.name = "adau-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = ADAU1761_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = ADAU1761_FORMATS,
	पूर्ण,
	.ops = &adau17x1_dai_ops,
पूर्ण;

पूर्णांक adau1761_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau17x1_type type, व्योम (*चयन_mode)(काष्ठा device *dev))
अणु
	काष्ठा snd_soc_dai_driver *dai_drv;
	स्थिर अक्षर *firmware_name;
	पूर्णांक ret;

	अगर (type == ADAU1361) अणु
		dai_drv = &adau1361_dai_driver;
		firmware_name = शून्य;
	पूर्ण अन्यथा अणु
		dai_drv = &adau1761_dai_driver;
		firmware_name = ADAU1761_FIRMWARE;
	पूर्ण

	ret = adau17x1_probe(dev, regmap, type, चयन_mode, firmware_name);
	अगर (ret)
		वापस ret;

	/* Enable cache only mode as we could miss ग_लिखोs beक्रमe bias level
	 * reaches standby and the core घड़ी is enabled */
	regcache_cache_only(regmap, true);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &adau1761_component_driver,
					       dai_drv, 1);
पूर्ण
EXPORT_SYMBOL_GPL(adau1761_probe);

स्थिर काष्ठा regmap_config adau1761_regmap_config = अणु
	.val_bits = 8,
	.reg_bits = 16,
	.max_रेजिस्टर = 0x40fa,
	.reg_शेषs = adau1761_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adau1761_reg_शेषs),
	.पढ़ोable_reg = adau1761_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = adau17x1_अस्थिर_रेजिस्टर,
	.precious_reg = adau17x1_precious_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(adau1761_regmap_config);

MODULE_DESCRIPTION("ASoC ADAU1361/ADAU1461/ADAU1761/ADAU1961 CODEC driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
