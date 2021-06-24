<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8985.c  --  WM8985 / WM8758 ALSA SoC Audio driver
 *
 * Copyright 2010 Wolfson Microelectronics plc
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 *
 * WM8758 support:
 * Copyright: 2016 Barix AG
 * Author: Petr Kulhavy <petr@barix.com>
 *
 * TODO:
 *  o Add OUT3/OUT4 mixer controls.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8985.h"

#घोषणा WM8985_NUM_SUPPLIES 4
अटल स्थिर अक्षर *wm8985_supply_names[WM8985_NUM_SUPPLIES] = अणु
	"DCVDD",
	"DBVDD",
	"AVDD1",
	"AVDD2"
पूर्ण;

क्रमागत wm8985_type अणु
	WM8985,
	WM8758,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8985_reg_शेषs[] = अणु
	अणु 1,  0x0000 पूर्ण,     /* R1  - Power management 1 */
	अणु 2,  0x0000 पूर्ण,     /* R2  - Power management 2 */
	अणु 3,  0x0000 पूर्ण,     /* R3  - Power management 3 */
	अणु 4,  0x0050 पूर्ण,     /* R4  - Audio Interface */
	अणु 5,  0x0000 पूर्ण,     /* R5  - Companding control */
	अणु 6,  0x0140 पूर्ण,     /* R6  - Clock Gen control */
	अणु 7,  0x0000 पूर्ण,     /* R7  - Additional control */
	अणु 8,  0x0000 पूर्ण,     /* R8  - GPIO Control */
	अणु 9,  0x0000 पूर्ण,     /* R9  - Jack Detect Control 1 */
	अणु 10, 0x0000 पूर्ण,     /* R10 - DAC Control */
	अणु 11, 0x00FF पूर्ण,     /* R11 - Left DAC digital Vol */
	अणु 12, 0x00FF पूर्ण,     /* R12 - Right DAC digital vol */
	अणु 13, 0x0000 पूर्ण,     /* R13 - Jack Detect Control 2 */
	अणु 14, 0x0100 पूर्ण,     /* R14 - ADC Control */
	अणु 15, 0x00FF पूर्ण,     /* R15 - Left ADC Digital Vol */
	अणु 16, 0x00FF पूर्ण,     /* R16 - Right ADC Digital Vol */
	अणु 18, 0x012C पूर्ण,     /* R18 - EQ1 - low shelf */
	अणु 19, 0x002C पूर्ण,     /* R19 - EQ2 - peak 1 */
	अणु 20, 0x002C पूर्ण,     /* R20 - EQ3 - peak 2 */
	अणु 21, 0x002C पूर्ण,     /* R21 - EQ4 - peak 3 */
	अणु 22, 0x002C पूर्ण,     /* R22 - EQ5 - high shelf */
	अणु 24, 0x0032 पूर्ण,     /* R24 - DAC Limiter 1 */
	अणु 25, 0x0000 पूर्ण,     /* R25 - DAC Limiter 2 */
	अणु 27, 0x0000 पूर्ण,     /* R27 - Notch Filter 1 */
	अणु 28, 0x0000 पूर्ण,     /* R28 - Notch Filter 2 */
	अणु 29, 0x0000 पूर्ण,     /* R29 - Notch Filter 3 */
	अणु 30, 0x0000 पूर्ण,     /* R30 - Notch Filter 4 */
	अणु 32, 0x0038 पूर्ण,     /* R32 - ALC control 1 */
	अणु 33, 0x000B पूर्ण,     /* R33 - ALC control 2 */
	अणु 34, 0x0032 पूर्ण,     /* R34 - ALC control 3 */
	अणु 35, 0x0000 पूर्ण,     /* R35 - Noise Gate */
	अणु 36, 0x0008 पूर्ण,     /* R36 - PLL N */
	अणु 37, 0x000C पूर्ण,     /* R37 - PLL K 1 */
	अणु 38, 0x0093 पूर्ण,     /* R38 - PLL K 2 */
	अणु 39, 0x00E9 पूर्ण,     /* R39 - PLL K 3 */
	अणु 41, 0x0000 पूर्ण,     /* R41 - 3D control */
	अणु 42, 0x0000 पूर्ण,     /* R42 - OUT4 to ADC */
	अणु 43, 0x0000 पूर्ण,     /* R43 - Beep control */
	अणु 44, 0x0033 पूर्ण,     /* R44 - Input ctrl */
	अणु 45, 0x0010 पूर्ण,     /* R45 - Left INP PGA gain ctrl */
	अणु 46, 0x0010 पूर्ण,     /* R46 - Right INP PGA gain ctrl */
	अणु 47, 0x0100 पूर्ण,     /* R47 - Left ADC BOOST ctrl */
	अणु 48, 0x0100 पूर्ण,     /* R48 - Right ADC BOOST ctrl */
	अणु 49, 0x0002 पूर्ण,     /* R49 - Output ctrl */
	अणु 50, 0x0001 पूर्ण,     /* R50 - Left mixer ctrl */
	अणु 51, 0x0001 पूर्ण,     /* R51 - Right mixer ctrl */
	अणु 52, 0x0039 पूर्ण,     /* R52 - LOUT1 (HP) volume ctrl */
	अणु 53, 0x0039 पूर्ण,     /* R53 - ROUT1 (HP) volume ctrl */
	अणु 54, 0x0039 पूर्ण,     /* R54 - LOUT2 (SPK) volume ctrl */
	अणु 55, 0x0039 पूर्ण,     /* R55 - ROUT2 (SPK) volume ctrl */
	अणु 56, 0x0001 पूर्ण,     /* R56 - OUT3 mixer ctrl */
	अणु 57, 0x0001 पूर्ण,     /* R57 - OUT4 (MONO) mix ctrl */
	अणु 60, 0x0004 पूर्ण,     /* R60 - OUTPUT ctrl */
	अणु 61, 0x0000 पूर्ण,     /* R61 - BIAS CTRL */
पूर्ण;

अटल bool wm8985_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8985_SOFTWARE_RESET:
	हाल WM8985_POWER_MANAGEMENT_1:
	हाल WM8985_POWER_MANAGEMENT_2:
	हाल WM8985_POWER_MANAGEMENT_3:
	हाल WM8985_AUDIO_INTERFACE:
	हाल WM8985_COMPANDING_CONTROL:
	हाल WM8985_CLOCK_GEN_CONTROL:
	हाल WM8985_ADDITIONAL_CONTROL:
	हाल WM8985_GPIO_CONTROL:
	हाल WM8985_JACK_DETECT_CONTROL_1:
	हाल WM8985_DAC_CONTROL:
	हाल WM8985_LEFT_DAC_DIGITAL_VOL:
	हाल WM8985_RIGHT_DAC_DIGITAL_VOL:
	हाल WM8985_JACK_DETECT_CONTROL_2:
	हाल WM8985_ADC_CONTROL:
	हाल WM8985_LEFT_ADC_DIGITAL_VOL:
	हाल WM8985_RIGHT_ADC_DIGITAL_VOL:
	हाल WM8985_EQ1_LOW_SHELF:
	हाल WM8985_EQ2_PEAK_1:
	हाल WM8985_EQ3_PEAK_2:
	हाल WM8985_EQ4_PEAK_3:
	हाल WM8985_EQ5_HIGH_SHELF:
	हाल WM8985_DAC_LIMITER_1:
	हाल WM8985_DAC_LIMITER_2:
	हाल WM8985_NOTCH_FILTER_1:
	हाल WM8985_NOTCH_FILTER_2:
	हाल WM8985_NOTCH_FILTER_3:
	हाल WM8985_NOTCH_FILTER_4:
	हाल WM8985_ALC_CONTROL_1:
	हाल WM8985_ALC_CONTROL_2:
	हाल WM8985_ALC_CONTROL_3:
	हाल WM8985_NOISE_GATE:
	हाल WM8985_PLL_N:
	हाल WM8985_PLL_K_1:
	हाल WM8985_PLL_K_2:
	हाल WM8985_PLL_K_3:
	हाल WM8985_3D_CONTROL:
	हाल WM8985_OUT4_TO_ADC:
	हाल WM8985_BEEP_CONTROL:
	हाल WM8985_INPUT_CTRL:
	हाल WM8985_LEFT_INP_PGA_GAIN_CTRL:
	हाल WM8985_RIGHT_INP_PGA_GAIN_CTRL:
	हाल WM8985_LEFT_ADC_BOOST_CTRL:
	हाल WM8985_RIGHT_ADC_BOOST_CTRL:
	हाल WM8985_OUTPUT_CTRL0:
	हाल WM8985_LEFT_MIXER_CTRL:
	हाल WM8985_RIGHT_MIXER_CTRL:
	हाल WM8985_LOUT1_HP_VOLUME_CTRL:
	हाल WM8985_ROUT1_HP_VOLUME_CTRL:
	हाल WM8985_LOUT2_SPK_VOLUME_CTRL:
	हाल WM8985_ROUT2_SPK_VOLUME_CTRL:
	हाल WM8985_OUT3_MIXER_CTRL:
	हाल WM8985_OUT4_MONO_MIX_CTRL:
	हाल WM8985_OUTPUT_CTRL1:
	हाल WM8985_BIAS_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * latch bit 8 of these रेजिस्टरs to ensure instant
 * volume updates
 */
अटल स्थिर पूर्णांक volume_update_regs[] = अणु
	WM8985_LEFT_DAC_DIGITAL_VOL,
	WM8985_RIGHT_DAC_DIGITAL_VOL,
	WM8985_LEFT_ADC_DIGITAL_VOL,
	WM8985_RIGHT_ADC_DIGITAL_VOL,
	WM8985_LOUT2_SPK_VOLUME_CTRL,
	WM8985_ROUT2_SPK_VOLUME_CTRL,
	WM8985_LOUT1_HP_VOLUME_CTRL,
	WM8985_ROUT1_HP_VOLUME_CTRL,
	WM8985_LEFT_INP_PGA_GAIN_CTRL,
	WM8985_RIGHT_INP_PGA_GAIN_CTRL
पूर्ण;

काष्ठा wm8985_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8985_NUM_SUPPLIES];
	क्रमागत wm8985_type dev_type;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक bclk;
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक भाग;
	पूर्णांक ratio;
पूर्ण fs_ratios[] = अणु
	अणु 10, 128 पूर्ण,
	अणु 15, 192 पूर्ण,
	अणु 20, 256 पूर्ण,
	अणु 30, 384 पूर्ण,
	अणु 40, 512 पूर्ण,
	अणु 60, 768 पूर्ण,
	अणु 80, 1024 पूर्ण,
	अणु 120, 1536 पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक srates[] = अणु 48000, 32000, 24000, 16000, 12000, 8000 पूर्ण;

अटल स्थिर पूर्णांक bclk_भागs[] = अणु
	1, 2, 4, 8, 16, 32
पूर्ण;

अटल पूर्णांक eqmode_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol);
अटल पूर्णांक eqmode_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12700, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -12700, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(lim_thresh_tlv, -600, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(lim_boost_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_min_tlv, -1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_max_tlv, -675, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_tar_tlv, -2250, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_vol_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, -1200, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(aux_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(bypass_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_boost_tlv, 0, 2000, 0);

अटल स्थिर अक्षर *alc_sel_text[] = अणु "Off", "Right", "Left", "Stereo" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(alc_sel, WM8985_ALC_CONTROL_1, 7, alc_sel_text);

अटल स्थिर अक्षर *alc_mode_text[] = अणु "ALC", "Limiter" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(alc_mode, WM8985_ALC_CONTROL_3, 8, alc_mode_text);

अटल स्थिर अक्षर *filter_mode_text[] = अणु "Audio", "Application" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(filter_mode, WM8985_ADC_CONTROL, 7,
			    filter_mode_text);

अटल स्थिर अक्षर *eq_bw_text[] = अणु "Narrow", "Wide" पूर्ण;
अटल स्थिर अक्षर *eqmode_text[] = अणु "Capture", "Playback" पूर्ण;
अटल SOC_ENUM_SINGLE_EXT_DECL(eqmode, eqmode_text);

अटल स्थिर अक्षर *eq1_cutoff_text[] = अणु
	"80Hz", "105Hz", "135Hz", "175Hz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq1_cutoff, WM8985_EQ1_LOW_SHELF, 5,
			    eq1_cutoff_text);
अटल स्थिर अक्षर *eq2_cutoff_text[] = अणु
	"230Hz", "300Hz", "385Hz", "500Hz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq2_bw, WM8985_EQ2_PEAK_1, 8, eq_bw_text);
अटल SOC_ENUM_SINGLE_DECL(eq2_cutoff, WM8985_EQ2_PEAK_1, 5, eq2_cutoff_text);
अटल स्थिर अक्षर *eq3_cutoff_text[] = अणु
	"650Hz", "850Hz", "1.1kHz", "1.4kHz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq3_bw, WM8985_EQ3_PEAK_2, 8, eq_bw_text);
अटल SOC_ENUM_SINGLE_DECL(eq3_cutoff, WM8985_EQ3_PEAK_2, 5,
			    eq3_cutoff_text);
अटल स्थिर अक्षर *eq4_cutoff_text[] = अणु
	"1.8kHz", "2.4kHz", "3.2kHz", "4.1kHz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq4_bw, WM8985_EQ4_PEAK_3, 8, eq_bw_text);
अटल SOC_ENUM_SINGLE_DECL(eq4_cutoff, WM8985_EQ4_PEAK_3, 5, eq4_cutoff_text);
अटल स्थिर अक्षर *eq5_cutoff_text[] = अणु
	"5.3kHz", "6.9kHz", "9kHz", "11.7kHz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq5_cutoff, WM8985_EQ5_HIGH_SHELF, 5,
				  eq5_cutoff_text);

अटल स्थिर अक्षर *speaker_mode_text[] = अणु "Class A/B", "Class D" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(speaker_mode, 0x17, 8, speaker_mode_text);

अटल स्थिर अक्षर *depth_3d_text[] = अणु
	"Off",
	"6.67%",
	"13.3%",
	"20%",
	"26.7%",
	"33.3%",
	"40%",
	"46.6%",
	"53.3%",
	"60%",
	"66.7%",
	"73.3%",
	"80%",
	"86.7%",
	"93.3%",
	"100%"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(depth_3d, WM8985_3D_CONTROL, 0, depth_3d_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8985_common_snd_controls[] = अणु
	SOC_SINGLE("Digital Loopback Switch", WM8985_COMPANDING_CONTROL,
		0, 1, 0),

	SOC_ENUM("ALC Capture Function", alc_sel),
	SOC_SINGLE_TLV("ALC Capture Max Volume", WM8985_ALC_CONTROL_1,
		3, 7, 0, alc_max_tlv),
	SOC_SINGLE_TLV("ALC Capture Min Volume", WM8985_ALC_CONTROL_1,
		0, 7, 0, alc_min_tlv),
	SOC_SINGLE_TLV("ALC Capture Target Volume", WM8985_ALC_CONTROL_2,
		0, 15, 0, alc_tar_tlv),
	SOC_SINGLE("ALC Capture Attack", WM8985_ALC_CONTROL_3, 0, 10, 0),
	SOC_SINGLE("ALC Capture Hold", WM8985_ALC_CONTROL_2, 4, 10, 0),
	SOC_SINGLE("ALC Capture Decay", WM8985_ALC_CONTROL_3, 4, 10, 0),
	SOC_ENUM("ALC Mode", alc_mode),
	SOC_SINGLE("ALC Capture NG Switch", WM8985_NOISE_GATE,
		3, 1, 0),
	SOC_SINGLE("ALC Capture NG Threshold", WM8985_NOISE_GATE,
		0, 7, 1),

	SOC_DOUBLE_R_TLV("Capture Volume", WM8985_LEFT_ADC_DIGITAL_VOL,
		WM8985_RIGHT_ADC_DIGITAL_VOL, 0, 255, 0, adc_tlv),
	SOC_DOUBLE_R("Capture PGA ZC Switch", WM8985_LEFT_INP_PGA_GAIN_CTRL,
		WM8985_RIGHT_INP_PGA_GAIN_CTRL, 7, 1, 0),
	SOC_DOUBLE_R_TLV("Capture PGA Volume", WM8985_LEFT_INP_PGA_GAIN_CTRL,
		WM8985_RIGHT_INP_PGA_GAIN_CTRL, 0, 63, 0, pga_vol_tlv),

	SOC_DOUBLE_R_TLV("Capture PGA Boost Volume",
		WM8985_LEFT_ADC_BOOST_CTRL, WM8985_RIGHT_ADC_BOOST_CTRL,
		8, 1, 0, pga_boost_tlv),

	SOC_DOUBLE("ADC Inversion Switch", WM8985_ADC_CONTROL, 0, 1, 1, 0),
	SOC_SINGLE("ADC 128x Oversampling Switch", WM8985_ADC_CONTROL, 8, 1, 0),

	SOC_DOUBLE_R_TLV("Playback Volume", WM8985_LEFT_DAC_DIGITAL_VOL,
		WM8985_RIGHT_DAC_DIGITAL_VOL, 0, 255, 0, dac_tlv),

	SOC_SINGLE("DAC Playback Limiter Switch", WM8985_DAC_LIMITER_1, 8, 1, 0),
	SOC_SINGLE("DAC Playback Limiter Decay", WM8985_DAC_LIMITER_1, 4, 10, 0),
	SOC_SINGLE("DAC Playback Limiter Attack", WM8985_DAC_LIMITER_1, 0, 11, 0),
	SOC_SINGLE_TLV("DAC Playback Limiter Threshold", WM8985_DAC_LIMITER_2,
		4, 7, 1, lim_thresh_tlv),
	SOC_SINGLE_TLV("DAC Playback Limiter Boost Volume", WM8985_DAC_LIMITER_2,
		0, 12, 0, lim_boost_tlv),
	SOC_DOUBLE("DAC Inversion Switch", WM8985_DAC_CONTROL, 0, 1, 1, 0),
	SOC_SINGLE("DAC Auto Mute Switch", WM8985_DAC_CONTROL, 2, 1, 0),
	SOC_SINGLE("DAC 128x Oversampling Switch", WM8985_DAC_CONTROL, 3, 1, 0),

	SOC_DOUBLE_R_TLV("Headphone Playback Volume", WM8985_LOUT1_HP_VOLUME_CTRL,
		WM8985_ROUT1_HP_VOLUME_CTRL, 0, 63, 0, out_tlv),
	SOC_DOUBLE_R("Headphone Playback ZC Switch", WM8985_LOUT1_HP_VOLUME_CTRL,
		WM8985_ROUT1_HP_VOLUME_CTRL, 7, 1, 0),
	SOC_DOUBLE_R("Headphone Switch", WM8985_LOUT1_HP_VOLUME_CTRL,
		WM8985_ROUT1_HP_VOLUME_CTRL, 6, 1, 1),

	SOC_DOUBLE_R_TLV("Speaker Playback Volume", WM8985_LOUT2_SPK_VOLUME_CTRL,
		WM8985_ROUT2_SPK_VOLUME_CTRL, 0, 63, 0, out_tlv),
	SOC_DOUBLE_R("Speaker Playback ZC Switch", WM8985_LOUT2_SPK_VOLUME_CTRL,
		WM8985_ROUT2_SPK_VOLUME_CTRL, 7, 1, 0),
	SOC_DOUBLE_R("Speaker Switch", WM8985_LOUT2_SPK_VOLUME_CTRL,
		WM8985_ROUT2_SPK_VOLUME_CTRL, 6, 1, 1),

	SOC_SINGLE("High Pass Filter Switch", WM8985_ADC_CONTROL, 8, 1, 0),
	SOC_ENUM("High Pass Filter Mode", filter_mode),
	SOC_SINGLE("High Pass Filter Cutoff", WM8985_ADC_CONTROL, 4, 7, 0),

	SOC_DOUBLE_R_TLV("Input PGA Bypass Volume",
		WM8985_LEFT_MIXER_CTRL, WM8985_RIGHT_MIXER_CTRL, 2, 7, 0,
		bypass_tlv),

	SOC_ENUM_EXT("Equalizer Function", eqmode, eqmode_get, eqmode_put),
	SOC_ENUM("EQ1 Cutoff", eq1_cutoff),
	SOC_SINGLE_TLV("EQ1 Volume", WM8985_EQ1_LOW_SHELF,  0, 24, 1, eq_tlv),
	SOC_ENUM("EQ2 Bandwidth", eq2_bw),
	SOC_ENUM("EQ2 Cutoff", eq2_cutoff),
	SOC_SINGLE_TLV("EQ2 Volume", WM8985_EQ2_PEAK_1, 0, 24, 1, eq_tlv),
	SOC_ENUM("EQ3 Bandwidth", eq3_bw),
	SOC_ENUM("EQ3 Cutoff", eq3_cutoff),
	SOC_SINGLE_TLV("EQ3 Volume", WM8985_EQ3_PEAK_2, 0, 24, 1, eq_tlv),
	SOC_ENUM("EQ4 Bandwidth", eq4_bw),
	SOC_ENUM("EQ4 Cutoff", eq4_cutoff),
	SOC_SINGLE_TLV("EQ4 Volume", WM8985_EQ4_PEAK_3, 0, 24, 1, eq_tlv),
	SOC_ENUM("EQ5 Cutoff", eq5_cutoff),
	SOC_SINGLE_TLV("EQ5 Volume", WM8985_EQ5_HIGH_SHELF, 0, 24, 1, eq_tlv),

	SOC_ENUM("3D Depth", depth_3d),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8985_specअगरic_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Aux Bypass Volume",
		WM8985_LEFT_MIXER_CTRL, WM8985_RIGHT_MIXER_CTRL, 6, 7, 0,
		aux_tlv),

	SOC_ENUM("Speaker Mode", speaker_mode)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_out_mixer[] = अणु
	SOC_DAPM_SINGLE("Line Switch", WM8985_LEFT_MIXER_CTRL, 1, 1, 0),
	SOC_DAPM_SINGLE("PCM Switch", WM8985_LEFT_MIXER_CTRL, 0, 1, 0),

	/* --- WM8985 only --- */
	SOC_DAPM_SINGLE("Aux Switch", WM8985_LEFT_MIXER_CTRL, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_out_mixer[] = अणु
	SOC_DAPM_SINGLE("Line Switch", WM8985_RIGHT_MIXER_CTRL, 1, 1, 0),
	SOC_DAPM_SINGLE("PCM Switch", WM8985_RIGHT_MIXER_CTRL, 0, 1, 0),

	/* --- WM8985 only --- */
	SOC_DAPM_SINGLE("Aux Switch", WM8985_RIGHT_MIXER_CTRL, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_input_mixer[] = अणु
	SOC_DAPM_SINGLE("L2 Switch", WM8985_INPUT_CTRL, 2, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", WM8985_INPUT_CTRL, 1, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", WM8985_INPUT_CTRL, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_input_mixer[] = अणु
	SOC_DAPM_SINGLE("R2 Switch", WM8985_INPUT_CTRL, 6, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", WM8985_INPUT_CTRL, 5, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", WM8985_INPUT_CTRL, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_boost_mixer[] = अणु
	SOC_DAPM_SINGLE_TLV("L2 Volume", WM8985_LEFT_ADC_BOOST_CTRL,
		4, 7, 0, boost_tlv),

	/* --- WM8985 only --- */
	SOC_DAPM_SINGLE_TLV("AUXL Volume", WM8985_LEFT_ADC_BOOST_CTRL,
		0, 7, 0, boost_tlv)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_boost_mixer[] = अणु
	SOC_DAPM_SINGLE_TLV("R2 Volume", WM8985_RIGHT_ADC_BOOST_CTRL,
		4, 7, 0, boost_tlv),

	/* --- WM8985 only --- */
	SOC_DAPM_SINGLE_TLV("AUXR Volume", WM8985_RIGHT_ADC_BOOST_CTRL,
		0, 7, 0, boost_tlv)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8985_common_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", WM8985_POWER_MANAGEMENT_3,
		0, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", WM8985_POWER_MANAGEMENT_3,
		1, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8985_POWER_MANAGEMENT_2,
		0, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8985_POWER_MANAGEMENT_2,
		1, 0),

	SND_SOC_DAPM_MIXER("Left Input Mixer", WM8985_POWER_MANAGEMENT_2,
		2, 0, left_input_mixer, ARRAY_SIZE(left_input_mixer)),
	SND_SOC_DAPM_MIXER("Right Input Mixer", WM8985_POWER_MANAGEMENT_2,
		3, 0, right_input_mixer, ARRAY_SIZE(right_input_mixer)),

	SND_SOC_DAPM_PGA("Left Capture PGA", WM8985_LEFT_INP_PGA_GAIN_CTRL,
		6, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Capture PGA", WM8985_RIGHT_INP_PGA_GAIN_CTRL,
		6, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Headphone Out", WM8985_POWER_MANAGEMENT_2,
		7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Headphone Out", WM8985_POWER_MANAGEMENT_2,
		8, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Speaker Out", WM8985_POWER_MANAGEMENT_3,
		5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Speaker Out", WM8985_POWER_MANAGEMENT_3,
		6, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", WM8985_POWER_MANAGEMENT_1, 4, 0,
			    शून्य, 0),

	SND_SOC_DAPM_INPUT("LIN"),
	SND_SOC_DAPM_INPUT("LIP"),
	SND_SOC_DAPM_INPUT("RIN"),
	SND_SOC_DAPM_INPUT("RIP"),
	SND_SOC_DAPM_INPUT("L2"),
	SND_SOC_DAPM_INPUT("R2"),
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPKL"),
	SND_SOC_DAPM_OUTPUT("SPKR")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8985_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Left Output Mixer", WM8985_POWER_MANAGEMENT_3,
		2, 0, left_out_mixer, ARRAY_SIZE(left_out_mixer)),
	SND_SOC_DAPM_MIXER("Right Output Mixer", WM8985_POWER_MANAGEMENT_3,
		3, 0, right_out_mixer, ARRAY_SIZE(right_out_mixer)),

	SND_SOC_DAPM_MIXER("Left Boost Mixer", WM8985_POWER_MANAGEMENT_2,
		4, 0, left_boost_mixer, ARRAY_SIZE(left_boost_mixer)),
	SND_SOC_DAPM_MIXER("Right Boost Mixer", WM8985_POWER_MANAGEMENT_2,
		5, 0, right_boost_mixer, ARRAY_SIZE(right_boost_mixer)),

	SND_SOC_DAPM_INPUT("AUXL"),
	SND_SOC_DAPM_INPUT("AUXR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8758_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Left Output Mixer", WM8985_POWER_MANAGEMENT_3,
		2, 0, left_out_mixer,
		ARRAY_SIZE(left_out_mixer) - 1),
	SND_SOC_DAPM_MIXER("Right Output Mixer", WM8985_POWER_MANAGEMENT_3,
		3, 0, right_out_mixer,
		ARRAY_SIZE(right_out_mixer) - 1),

	SND_SOC_DAPM_MIXER("Left Boost Mixer", WM8985_POWER_MANAGEMENT_2,
		4, 0, left_boost_mixer,
		ARRAY_SIZE(left_boost_mixer) - 1),
	SND_SOC_DAPM_MIXER("Right Boost Mixer", WM8985_POWER_MANAGEMENT_2,
		5, 0, right_boost_mixer,
		ARRAY_SIZE(right_boost_mixer) - 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8985_common_dapm_routes[] = अणु
	अणु "Right Output Mixer", "PCM Switch", "Right DAC" पूर्ण,
	अणु "Right Output Mixer", "Line Switch", "Right Boost Mixer" पूर्ण,

	अणु "Left Output Mixer", "PCM Switch", "Left DAC" पूर्ण,
	अणु "Left Output Mixer", "Line Switch", "Left Boost Mixer" पूर्ण,

	अणु "Right Headphone Out", शून्य, "Right Output Mixer" पूर्ण,
	अणु "HPR", शून्य, "Right Headphone Out" पूर्ण,

	अणु "Left Headphone Out", शून्य, "Left Output Mixer" पूर्ण,
	अणु "HPL", शून्य, "Left Headphone Out" पूर्ण,

	अणु "Right Speaker Out", शून्य, "Right Output Mixer" पूर्ण,
	अणु "SPKR", शून्य, "Right Speaker Out" पूर्ण,

	अणु "Left Speaker Out", शून्य, "Left Output Mixer" पूर्ण,
	अणु "SPKL", शून्य, "Left Speaker Out" पूर्ण,

	अणु "Right ADC", शून्य, "Right Boost Mixer" पूर्ण,

	अणु "Right Boost Mixer", शून्य, "Right Capture PGA" पूर्ण,
	अणु "Right Boost Mixer", "R2 Volume", "R2" पूर्ण,

	अणु "Left ADC", शून्य, "Left Boost Mixer" पूर्ण,

	अणु "Left Boost Mixer", शून्य, "Left Capture PGA" पूर्ण,
	अणु "Left Boost Mixer", "L2 Volume", "L2" पूर्ण,

	अणु "Right Capture PGA", शून्य, "Right Input Mixer" पूर्ण,
	अणु "Left Capture PGA", शून्य, "Left Input Mixer" पूर्ण,

	अणु "Right Input Mixer", "R2 Switch", "R2" पूर्ण,
	अणु "Right Input Mixer", "MicN Switch", "RIN" पूर्ण,
	अणु "Right Input Mixer", "MicP Switch", "RIP" पूर्ण,

	अणु "Left Input Mixer", "L2 Switch", "L2" पूर्ण,
	अणु "Left Input Mixer", "MicN Switch", "LIN" पूर्ण,
	अणु "Left Input Mixer", "MicP Switch", "LIP" पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा snd_soc_dapm_route wm8985_aux_dapm_routes[] = अणु
	अणु "Right Output Mixer", "Aux Switch", "AUXR" पूर्ण,
	अणु "Left Output Mixer", "Aux Switch", "AUXL" पूर्ण,

	अणु "Right Boost Mixer", "AUXR Volume", "AUXR" पूर्ण,
	अणु "Left Boost Mixer", "AUXL Volume", "AUXL" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8985_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8985_priv *wm8985 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	चयन (wm8985->dev_type) अणु
	हाल WM8758:
		snd_soc_dapm_new_controls(dapm, wm8758_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8758_dapm_widमाला_लो));
		अवरोध;

	हाल WM8985:
		snd_soc_add_component_controls(component, wm8985_specअगरic_snd_controls,
			ARRAY_SIZE(wm8985_specअगरic_snd_controls));

		snd_soc_dapm_new_controls(dapm, wm8985_dapm_widमाला_लो,
			ARRAY_SIZE(wm8985_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, wm8985_aux_dapm_routes,
			ARRAY_SIZE(wm8985_aux_dapm_routes));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eqmode_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM8985_EQ1_LOW_SHELF);
	अगर (reg & WM8985_EQ3DMODE)
		ucontrol->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक eqmode_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक regpwr2, regpwr3;
	अचिन्हित पूर्णांक reg_eq;

	अगर (ucontrol->value.क्रमागतerated.item[0] != 0
			&& ucontrol->value.क्रमागतerated.item[0] != 1)
		वापस -EINVAL;

	reg_eq = snd_soc_component_पढ़ो(component, WM8985_EQ1_LOW_SHELF);
	चयन ((reg_eq & WM8985_EQ3DMODE) >> WM8985_EQ3DMODE_SHIFT) अणु
	हाल 0:
		अगर (!ucontrol->value.क्रमागतerated.item[0])
			वापस 0;
		अवरोध;
	हाल 1:
		अगर (ucontrol->value.क्रमागतerated.item[0])
			वापस 0;
		अवरोध;
	पूर्ण

	regpwr2 = snd_soc_component_पढ़ो(component, WM8985_POWER_MANAGEMENT_2);
	regpwr3 = snd_soc_component_पढ़ो(component, WM8985_POWER_MANAGEMENT_3);
	/* disable the DACs and ADCs */
	snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_2,
			    WM8985_ADCENR_MASK | WM8985_ADCENL_MASK, 0);
	snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_3,
			    WM8985_DACENR_MASK | WM8985_DACENL_MASK, 0);
	snd_soc_component_update_bits(component, WM8985_ADDITIONAL_CONTROL,
			    WM8985_M128ENB_MASK, WM8985_M128ENB);
	/* set the desired eqmode */
	snd_soc_component_update_bits(component, WM8985_EQ1_LOW_SHELF,
			    WM8985_EQ3DMODE_MASK,
			    ucontrol->value.क्रमागतerated.item[0]
			    << WM8985_EQ3DMODE_SHIFT);
	/* restore DAC/ADC configuration */
	snd_soc_component_ग_लिखो(component, WM8985_POWER_MANAGEMENT_2, regpwr2);
	snd_soc_component_ग_लिखो(component, WM8985_POWER_MANAGEMENT_3, regpwr3);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8985_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, WM8985_SOFTWARE_RESET, 0x0);
पूर्ण

अटल पूर्णांक wm8985_dac_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	वापस snd_soc_component_update_bits(component, WM8985_DAC_CONTROL,
				   WM8985_SOFTMUTE_MASK,
				   !!mute << WM8985_SOFTMUTE_SHIFT);
पूर्ण

अटल पूर्णांक wm8985_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component;
	u16 क्रमmat, master, bcp, lrp;

	component = dai->component;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat = 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		क्रमmat = 0x0;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat = 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat = 0x3;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown dai format\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8985_AUDIO_INTERFACE,
			    WM8985_FMT_MASK, क्रमmat << WM8985_FMT_SHIFT);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown master/slave configuration\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
			    WM8985_MS_MASK, master << WM8985_MS_SHIFT);

	/* frame inversion is not valid क्रम dsp modes */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_IB_IF:
		हाल SND_SOC_DAIFMT_NB_IF:
			वापस -EINVAL;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	bcp = lrp = 0;
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bcp = lrp = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bcp = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrp = 1;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown polarity configuration\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8985_AUDIO_INTERFACE,
			    WM8985_LRP_MASK, lrp << WM8985_LRP_SHIFT);
	snd_soc_component_update_bits(component, WM8985_AUDIO_INTERFACE,
			    WM8985_BCP_MASK, bcp << WM8985_BCP_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8985_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक i;
	काष्ठा snd_soc_component *component;
	काष्ठा wm8985_priv *wm8985;
	u16 blen, srate_idx;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक srate_best;

	component = dai->component;
	wm8985 = snd_soc_component_get_drvdata(component);

	wm8985->bclk = snd_soc_params_to_bclk(params);
	अगर ((पूर्णांक)wm8985->bclk < 0)
		वापस wm8985->bclk;

	चयन (params_width(params)) अणु
	हाल 16:
		blen = 0x0;
		अवरोध;
	हाल 20:
		blen = 0x1;
		अवरोध;
	हाल 24:
		blen = 0x2;
		अवरोध;
	हाल 32:
		blen = 0x3;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported word length %u\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8985_AUDIO_INTERFACE,
			    WM8985_WL_MASK, blen << WM8985_WL_SHIFT);

	/*
	 * match to the nearest possible sample rate and rely
	 * on the array index to configure the SR रेजिस्टर
	 */
	srate_idx = 0;
	srate_best = असल(srates[0] - params_rate(params));
	क्रम (i = 1; i < ARRAY_SIZE(srates); ++i) अणु
		अगर (असल(srates[i] - params_rate(params)) >= srate_best)
			जारी;
		srate_idx = i;
		srate_best = असल(srates[i] - params_rate(params));
	पूर्ण

	dev_dbg(dai->dev, "Selected SRATE = %d\n", srates[srate_idx]);
	snd_soc_component_update_bits(component, WM8985_ADDITIONAL_CONTROL,
			    WM8985_SR_MASK, srate_idx << WM8985_SR_SHIFT);

	dev_dbg(dai->dev, "Target BCLK = %uHz\n", wm8985->bclk);
	dev_dbg(dai->dev, "SYSCLK = %uHz\n", wm8985->sysclk);

	क्रम (i = 0; i < ARRAY_SIZE(fs_ratios); ++i) अणु
		अगर (wm8985->sysclk / params_rate(params)
				== fs_ratios[i].ratio)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(fs_ratios)) अणु
		dev_err(dai->dev, "Unable to configure MCLK ratio %u/%u\n",
			wm8985->sysclk, params_rate(params));
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "MCLK ratio = %dfs\n", fs_ratios[i].ratio);
	snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
			    WM8985_MCLKDIV_MASK, i << WM8985_MCLKDIV_SHIFT);

	/* select the appropriate bclk भागider */
	पंचांगp = (wm8985->sysclk / fs_ratios[i].भाग) * 10;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); ++i) अणु
		अगर (wm8985->bclk == पंचांगp / bclk_भागs[i])
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(bclk_भागs)) अणु
		dev_err(dai->dev, "No matching BCLK divider found\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "BCLK div = %d\n", i);
	snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
			    WM8985_BCLKDIV_MASK, i << WM8985_BCLKDIV_SHIFT);
	वापस 0;
पूर्ण

काष्ठा pll_भाग अणु
	u32 भाग2:1;
	u32 n:4;
	u32 k:24;
पूर्ण;

#घोषणा FIXED_PLL_SIZE ((1ULL << 24) * 10)
अटल पूर्णांक pll_factors(काष्ठा pll_भाग *pll_भाग, अचिन्हित पूर्णांक target,
		       अचिन्हित पूर्णांक source)
अणु
	u64 Kpart;
	अचिन्हित दीर्घ पूर्णांक K, Nभाग, Nmod;

	pll_भाग->भाग2 = 0;
	Nभाग = target / source;
	अगर (Nभाग < 6) अणु
		source >>= 1;
		pll_भाग->भाग2 = 1;
		Nभाग = target / source;
	पूर्ण

	अगर (Nभाग < 6 || Nभाग > 12) अणु
		prपूर्णांकk(KERN_ERR "%s: WM8985 N value is not within"
		       " the recommended range: %lu\n", __func__, Nभाग);
		वापस -EINVAL;
	पूर्ण
	pll_भाग->n = Nभाग;

	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (u64)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xffffffff;
	अगर ((K % 10) >= 5)
		K += 5;
	K /= 10;
	pll_भाग->k = K;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8985_set_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id,
			  पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			  अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_component *component;
	काष्ठा pll_भाग pll_भाग;

	component = dai->component;
	अगर (!freq_in || !freq_out) अणु
		/* disable the PLL */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_PLLEN_MASK, 0);
	पूर्ण अन्यथा अणु
		ret = pll_factors(&pll_भाग, freq_out * 4 * 2, freq_in);
		अगर (ret)
			वापस ret;

		/* set PLLN and PRESCALE */
		snd_soc_component_ग_लिखो(component, WM8985_PLL_N,
			      (pll_भाग.भाग2 << WM8985_PLL_PRESCALE_SHIFT)
			      | pll_भाग.n);
		/* set PLLK */
		snd_soc_component_ग_लिखो(component, WM8985_PLL_K_3, pll_भाग.k & 0x1ff);
		snd_soc_component_ग_लिखो(component, WM8985_PLL_K_2, (pll_भाग.k >> 9) & 0x1ff);
		snd_soc_component_ग_लिखो(component, WM8985_PLL_K_1, (pll_भाग.k >> 18));
		/* set the source of the घड़ी to be the PLL */
		snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
				    WM8985_CLKSEL_MASK, WM8985_CLKSEL);
		/* enable the PLL */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_PLLEN_MASK, WM8985_PLLEN);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8985_set_sysclk(काष्ठा snd_soc_dai *dai,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8985_priv *wm8985;

	component = dai->component;
	wm8985 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल WM8985_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
				    WM8985_CLKSEL_MASK, 0);
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_PLLEN_MASK, 0);
		अवरोध;
	हाल WM8985_CLKSRC_PLL:
		snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
				    WM8985_CLKSEL_MASK, WM8985_CLKSEL);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown clock source %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	wm8985->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8985_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret;
	काष्ठा wm8985_priv *wm8985;

	wm8985 = snd_soc_component_get_drvdata(component);
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		/* VMID at 75k */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_VMIDSEL_MASK,
				    1 << WM8985_VMIDSEL_SHIFT);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8985->supplies),
						    wm8985->supplies);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			regcache_sync(wm8985->regmap);

			/* enable anti-pop features */
			snd_soc_component_update_bits(component, WM8985_OUT4_TO_ADC,
					    WM8985_POBCTRL_MASK,
					    WM8985_POBCTRL);
			/* enable thermal shutकरोwn */
			snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
					    WM8985_TSDEN_MASK, WM8985_TSDEN);
			snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
					    WM8985_TSOPCTRL_MASK,
					    WM8985_TSOPCTRL);
			/* enable BIASEN */
			snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
					    WM8985_BIASEN_MASK, WM8985_BIASEN);
			/* VMID at 75k */
			snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
					    WM8985_VMIDSEL_MASK,
					    1 << WM8985_VMIDSEL_SHIFT);
			msleep(500);
			/* disable anti-pop features */
			snd_soc_component_update_bits(component, WM8985_OUT4_TO_ADC,
					    WM8985_POBCTRL_MASK, 0);
		पूर्ण
		/* VMID at 300k */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_VMIDSEL_MASK,
				    2 << WM8985_VMIDSEL_SHIFT);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* disable thermal shutकरोwn */
		snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
				    WM8985_TSOPCTRL_MASK, 0);
		snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
				    WM8985_TSDEN_MASK, 0);
		/* disable VMIDSEL and BIASEN */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_VMIDSEL_MASK | WM8985_BIASEN_MASK,
				    0);
		snd_soc_component_ग_लिखो(component, WM8985_POWER_MANAGEMENT_1, 0);
		snd_soc_component_ग_लिखो(component, WM8985_POWER_MANAGEMENT_2, 0);
		snd_soc_component_ग_लिखो(component, WM8985_POWER_MANAGEMENT_3, 0);

		regcache_mark_dirty(wm8985->regmap);

		regulator_bulk_disable(ARRAY_SIZE(wm8985->supplies),
				       wm8985->supplies);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8985_probe(काष्ठा snd_soc_component *component)
अणु
	माप_प्रकार i;
	काष्ठा wm8985_priv *wm8985;
	पूर्णांक ret;

	wm8985 = snd_soc_component_get_drvdata(component);

	क्रम (i = 0; i < ARRAY_SIZE(wm8985->supplies); i++)
		wm8985->supplies[i].supply = wm8985_supply_names[i];

	ret = devm_regulator_bulk_get(component->dev, ARRAY_SIZE(wm8985->supplies),
				 wm8985->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8985->supplies),
				    wm8985->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm8985_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	/* latch volume update bits */
	क्रम (i = 0; i < ARRAY_SIZE(volume_update_regs); ++i)
		snd_soc_component_update_bits(component, volume_update_regs[i],
				    0x100, 0x100);
	/* enable BIASCUT */
	snd_soc_component_update_bits(component, WM8985_BIAS_CTRL, WM8985_BIASCUT,
			    WM8985_BIASCUT);

	wm8985_add_widमाला_लो(component);

	वापस 0;

err_reg_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8985->supplies), wm8985->supplies);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm8985_dai_ops = अणु
	.mute_stream = wm8985_dac_mute,
	.hw_params = wm8985_hw_params,
	.set_fmt = wm8985_set_fmt,
	.set_sysclk = wm8985_set_sysclk,
	.set_pll = wm8985_set_pll,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा WM8985_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm8985_dai = अणु
	.name = "wm8985-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = WM8985_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = WM8985_FORMATS,
	पूर्ण,
	.ops = &wm8985_dai_ops,
	.symmetric_rate = 1
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8985 = अणु
	.probe			= wm8985_probe,
	.set_bias_level		= wm8985_set_bias_level,
	.controls		= wm8985_common_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8985_common_snd_controls),
	.dapm_widमाला_लो		= wm8985_common_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8985_common_dapm_widमाला_लो),
	.dapm_routes		= wm8985_common_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8985_common_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8985_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8985_MAX_REGISTER,
	.ग_लिखोable_reg = wm8985_ग_लिखोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8985_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8985_reg_शेषs),
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8985_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8985_priv *wm8985;
	पूर्णांक ret;

	wm8985 = devm_kzalloc(&spi->dev, माप *wm8985, GFP_KERNEL);
	अगर (!wm8985)
		वापस -ENOMEM;

	spi_set_drvdata(spi, wm8985);

	wm8985->dev_type = WM8985;

	wm8985->regmap = devm_regmap_init_spi(spi, &wm8985_regmap);
	अगर (IS_ERR(wm8985->regmap)) अणु
		ret = PTR_ERR(wm8985->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
				     &soc_component_dev_wm8985, &wm8985_dai, 1);
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8985_spi_driver = अणु
	.driver = अणु
		.name = "wm8985",
	पूर्ण,
	.probe = wm8985_spi_probe,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8985_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8985_priv *wm8985;
	पूर्णांक ret;

	wm8985 = devm_kzalloc(&i2c->dev, माप *wm8985, GFP_KERNEL);
	अगर (!wm8985)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8985);

	wm8985->dev_type = id->driver_data;

	wm8985->regmap = devm_regmap_init_i2c(i2c, &wm8985_regmap);
	अगर (IS_ERR(wm8985->regmap)) अणु
		ret = PTR_ERR(wm8985->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_wm8985, &wm8985_dai, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8985_i2c_id[] = अणु
	अणु "wm8985", WM8985 पूर्ण,
	अणु "wm8758", WM8758 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8985_i2c_id);

अटल काष्ठा i2c_driver wm8985_i2c_driver = अणु
	.driver = अणु
		.name = "wm8985",
	पूर्ण,
	.probe = wm8985_i2c_probe,
	.id_table = wm8985_i2c_id
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8985_modinit(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8985_i2c_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8985 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8985_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8985 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8985_modinit);

अटल व्योम __निकास wm8985_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8985_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8985_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8985_निकास);

MODULE_DESCRIPTION("ASoC WM8985 / WM8758 driver");
MODULE_AUTHOR("Dimitris Papastamos <dp@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
