<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8983.c  --  WM8983 ALSA SoC Audio driver
 *
 * Copyright 2011 Wolfson Microelectronics plc
 *
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8983.h"

अटल स्थिर काष्ठा reg_शेष wm8983_शेषs[] = अणु
	अणु 0x01, 0x0000 पूर्ण,     /* R1  - Power management 1 */
	अणु 0x02, 0x0000 पूर्ण,     /* R2  - Power management 2 */
	अणु 0x03, 0x0000 पूर्ण,     /* R3  - Power management 3 */
	अणु 0x04, 0x0050 पूर्ण,     /* R4  - Audio Interface */
	अणु 0x05, 0x0000 पूर्ण,     /* R5  - Companding control */
	अणु 0x06, 0x0140 पूर्ण,     /* R6  - Clock Gen control */
	अणु 0x07, 0x0000 पूर्ण,     /* R7  - Additional control */
	अणु 0x08, 0x0000 पूर्ण,     /* R8  - GPIO Control */
	अणु 0x09, 0x0000 पूर्ण,     /* R9  - Jack Detect Control 1 */
	अणु 0x0A, 0x0000 पूर्ण,     /* R10 - DAC Control */
	अणु 0x0B, 0x00FF पूर्ण,     /* R11 - Left DAC digital Vol */
	अणु 0x0C, 0x00FF पूर्ण,     /* R12 - Right DAC digital vol */
	अणु 0x0D, 0x0000 पूर्ण,     /* R13 - Jack Detect Control 2 */
	अणु 0x0E, 0x0100 पूर्ण,     /* R14 - ADC Control */
	अणु 0x0F, 0x00FF पूर्ण,     /* R15 - Left ADC Digital Vol */
	अणु 0x10, 0x00FF पूर्ण,     /* R16 - Right ADC Digital Vol */
	अणु 0x12, 0x012C पूर्ण,     /* R18 - EQ1 - low shelf */
	अणु 0x13, 0x002C पूर्ण,     /* R19 - EQ2 - peak 1 */
	अणु 0x14, 0x002C पूर्ण,     /* R20 - EQ3 - peak 2 */
	अणु 0x15, 0x002C पूर्ण,     /* R21 - EQ4 - peak 3 */
	अणु 0x16, 0x002C पूर्ण,     /* R22 - EQ5 - high shelf */
	अणु 0x18, 0x0032 पूर्ण,     /* R24 - DAC Limiter 1 */
	अणु 0x19, 0x0000 पूर्ण,     /* R25 - DAC Limiter 2 */
	अणु 0x1B, 0x0000 पूर्ण,     /* R27 - Notch Filter 1 */
	अणु 0x1C, 0x0000 पूर्ण,     /* R28 - Notch Filter 2 */
	अणु 0x1D, 0x0000 पूर्ण,     /* R29 - Notch Filter 3 */
	अणु 0x1E, 0x0000 पूर्ण,     /* R30 - Notch Filter 4 */
	अणु 0x20, 0x0038 पूर्ण,     /* R32 - ALC control 1 */
	अणु 0x21, 0x000B पूर्ण,     /* R33 - ALC control 2 */
	अणु 0x22, 0x0032 पूर्ण,     /* R34 - ALC control 3 */
	अणु 0x23, 0x0000 पूर्ण,     /* R35 - Noise Gate */
	अणु 0x24, 0x0008 पूर्ण,     /* R36 - PLL N */
	अणु 0x25, 0x000C पूर्ण,     /* R37 - PLL K 1 */
	अणु 0x26, 0x0093 पूर्ण,     /* R38 - PLL K 2 */
	अणु 0x27, 0x00E9 पूर्ण,     /* R39 - PLL K 3 */
	अणु 0x29, 0x0000 पूर्ण,     /* R41 - 3D control */
	अणु 0x2A, 0x0000 पूर्ण,     /* R42 - OUT4 to ADC */
	अणु 0x2B, 0x0000 पूर्ण,     /* R43 - Beep control */
	अणु 0x2C, 0x0033 पूर्ण,     /* R44 - Input ctrl */
	अणु 0x2D, 0x0010 पूर्ण,     /* R45 - Left INP PGA gain ctrl */
	अणु 0x2E, 0x0010 पूर्ण,     /* R46 - Right INP PGA gain ctrl */
	अणु 0x2F, 0x0100 पूर्ण,     /* R47 - Left ADC BOOST ctrl */
	अणु 0x30, 0x0100 पूर्ण,     /* R48 - Right ADC BOOST ctrl */
	अणु 0x31, 0x0002 पूर्ण,     /* R49 - Output ctrl */
	अणु 0x32, 0x0001 पूर्ण,     /* R50 - Left mixer ctrl */
	अणु 0x33, 0x0001 पूर्ण,     /* R51 - Right mixer ctrl */
	अणु 0x34, 0x0039 पूर्ण,     /* R52 - LOUT1 (HP) volume ctrl */
	अणु 0x35, 0x0039 पूर्ण,     /* R53 - ROUT1 (HP) volume ctrl */
	अणु 0x36, 0x0039 पूर्ण,     /* R54 - LOUT2 (SPK) volume ctrl */
	अणु 0x37, 0x0039 पूर्ण,     /* R55 - ROUT2 (SPK) volume ctrl */
	अणु 0x38, 0x0001 पूर्ण,     /* R56 - OUT3 mixer ctrl */
	अणु 0x39, 0x0001 पूर्ण,     /* R57 - OUT4 (MONO) mix ctrl */
	अणु 0x3D, 0x0000 पूर्ण,      /* R61 - BIAS CTRL */
पूर्ण;

/* vol/gain update regs */
अटल स्थिर पूर्णांक vol_update_regs[] = अणु
	WM8983_LEFT_DAC_DIGITAL_VOL,
	WM8983_RIGHT_DAC_DIGITAL_VOL,
	WM8983_LEFT_ADC_DIGITAL_VOL,
	WM8983_RIGHT_ADC_DIGITAL_VOL,
	WM8983_LOUT1_HP_VOLUME_CTRL,
	WM8983_ROUT1_HP_VOLUME_CTRL,
	WM8983_LOUT2_SPK_VOLUME_CTRL,
	WM8983_ROUT2_SPK_VOLUME_CTRL,
	WM8983_LEFT_INP_PGA_GAIN_CTRL,
	WM8983_RIGHT_INP_PGA_GAIN_CTRL
पूर्ण;

काष्ठा wm8983_priv अणु
	काष्ठा regmap *regmap;
	u32 sysclk;
	u32 bclk;
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
अटल SOC_ENUM_SINGLE_DECL(alc_sel, WM8983_ALC_CONTROL_1, 7, alc_sel_text);

अटल स्थिर अक्षर *alc_mode_text[] = अणु "ALC", "Limiter" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(alc_mode, WM8983_ALC_CONTROL_3, 8, alc_mode_text);

अटल स्थिर अक्षर *filter_mode_text[] = अणु "Audio", "Application" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(filter_mode, WM8983_ADC_CONTROL, 7,
			    filter_mode_text);

अटल स्थिर अक्षर *eq_bw_text[] = अणु "Narrow", "Wide" पूर्ण;
अटल स्थिर अक्षर *eqmode_text[] = अणु "Capture", "Playback" पूर्ण;
अटल SOC_ENUM_SINGLE_EXT_DECL(eqmode, eqmode_text);

अटल स्थिर अक्षर *eq1_cutoff_text[] = अणु
	"80Hz", "105Hz", "135Hz", "175Hz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq1_cutoff, WM8983_EQ1_LOW_SHELF, 5,
			    eq1_cutoff_text);
अटल स्थिर अक्षर *eq2_cutoff_text[] = अणु
	"230Hz", "300Hz", "385Hz", "500Hz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq2_bw, WM8983_EQ2_PEAK_1, 8, eq_bw_text);
अटल SOC_ENUM_SINGLE_DECL(eq2_cutoff, WM8983_EQ2_PEAK_1, 5, eq2_cutoff_text);
अटल स्थिर अक्षर *eq3_cutoff_text[] = अणु
	"650Hz", "850Hz", "1.1kHz", "1.4kHz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq3_bw, WM8983_EQ3_PEAK_2, 8, eq_bw_text);
अटल SOC_ENUM_SINGLE_DECL(eq3_cutoff, WM8983_EQ3_PEAK_2, 5, eq3_cutoff_text);
अटल स्थिर अक्षर *eq4_cutoff_text[] = अणु
	"1.8kHz", "2.4kHz", "3.2kHz", "4.1kHz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq4_bw, WM8983_EQ4_PEAK_3, 8, eq_bw_text);
अटल SOC_ENUM_SINGLE_DECL(eq4_cutoff, WM8983_EQ4_PEAK_3, 5, eq4_cutoff_text);
अटल स्थिर अक्षर *eq5_cutoff_text[] = अणु
	"5.3kHz", "6.9kHz", "9kHz", "11.7kHz"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(eq5_cutoff, WM8983_EQ5_HIGH_SHELF, 5,
			    eq5_cutoff_text);

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
अटल SOC_ENUM_SINGLE_DECL(depth_3d, WM8983_3D_CONTROL, 0,
			    depth_3d_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8983_snd_controls[] = अणु
	SOC_SINGLE("Digital Loopback Switch", WM8983_COMPANDING_CONTROL,
		   0, 1, 0),

	SOC_ENUM("ALC Capture Function", alc_sel),
	SOC_SINGLE_TLV("ALC Capture Max Volume", WM8983_ALC_CONTROL_1,
		       3, 7, 0, alc_max_tlv),
	SOC_SINGLE_TLV("ALC Capture Min Volume", WM8983_ALC_CONTROL_1,
		       0, 7, 0, alc_min_tlv),
	SOC_SINGLE_TLV("ALC Capture Target Volume", WM8983_ALC_CONTROL_2,
		       0, 15, 0, alc_tar_tlv),
	SOC_SINGLE("ALC Capture Attack", WM8983_ALC_CONTROL_3, 0, 10, 0),
	SOC_SINGLE("ALC Capture Hold", WM8983_ALC_CONTROL_2, 4, 10, 0),
	SOC_SINGLE("ALC Capture Decay", WM8983_ALC_CONTROL_3, 4, 10, 0),
	SOC_ENUM("ALC Mode", alc_mode),
	SOC_SINGLE("ALC Capture NG Switch", WM8983_NOISE_GATE,
		   3, 1, 0),
	SOC_SINGLE("ALC Capture NG Threshold", WM8983_NOISE_GATE,
		   0, 7, 1),

	SOC_DOUBLE_R_TLV("Capture Volume", WM8983_LEFT_ADC_DIGITAL_VOL,
			 WM8983_RIGHT_ADC_DIGITAL_VOL, 0, 255, 0, adc_tlv),
	SOC_DOUBLE_R("Capture PGA ZC Switch", WM8983_LEFT_INP_PGA_GAIN_CTRL,
		     WM8983_RIGHT_INP_PGA_GAIN_CTRL, 7, 1, 0),
	SOC_DOUBLE_R_TLV("Capture PGA Volume", WM8983_LEFT_INP_PGA_GAIN_CTRL,
			 WM8983_RIGHT_INP_PGA_GAIN_CTRL, 0, 63, 0, pga_vol_tlv),

	SOC_DOUBLE_R_TLV("Capture PGA Boost Volume",
			 WM8983_LEFT_ADC_BOOST_CTRL, WM8983_RIGHT_ADC_BOOST_CTRL,
			 8, 1, 0, pga_boost_tlv),

	SOC_DOUBLE("ADC Inversion Switch", WM8983_ADC_CONTROL, 0, 1, 1, 0),
	SOC_SINGLE("ADC 128x Oversampling Switch", WM8983_ADC_CONTROL, 8, 1, 0),

	SOC_DOUBLE_R_TLV("Playback Volume", WM8983_LEFT_DAC_DIGITAL_VOL,
			 WM8983_RIGHT_DAC_DIGITAL_VOL, 0, 255, 0, dac_tlv),

	SOC_SINGLE("DAC Playback Limiter Switch", WM8983_DAC_LIMITER_1, 8, 1, 0),
	SOC_SINGLE("DAC Playback Limiter Decay", WM8983_DAC_LIMITER_1, 4, 10, 0),
	SOC_SINGLE("DAC Playback Limiter Attack", WM8983_DAC_LIMITER_1, 0, 11, 0),
	SOC_SINGLE_TLV("DAC Playback Limiter Threshold", WM8983_DAC_LIMITER_2,
		       4, 7, 1, lim_thresh_tlv),
	SOC_SINGLE_TLV("DAC Playback Limiter Boost Volume", WM8983_DAC_LIMITER_2,
		       0, 12, 0, lim_boost_tlv),
	SOC_DOUBLE("DAC Inversion Switch", WM8983_DAC_CONTROL, 0, 1, 1, 0),
	SOC_SINGLE("DAC Auto Mute Switch", WM8983_DAC_CONTROL, 2, 1, 0),
	SOC_SINGLE("DAC 128x Oversampling Switch", WM8983_DAC_CONTROL, 3, 1, 0),

	SOC_DOUBLE_R_TLV("Headphone Playback Volume", WM8983_LOUT1_HP_VOLUME_CTRL,
			 WM8983_ROUT1_HP_VOLUME_CTRL, 0, 63, 0, out_tlv),
	SOC_DOUBLE_R("Headphone Playback ZC Switch", WM8983_LOUT1_HP_VOLUME_CTRL,
		     WM8983_ROUT1_HP_VOLUME_CTRL, 7, 1, 0),
	SOC_DOUBLE_R("Headphone Switch", WM8983_LOUT1_HP_VOLUME_CTRL,
		     WM8983_ROUT1_HP_VOLUME_CTRL, 6, 1, 1),

	SOC_DOUBLE_R_TLV("Speaker Playback Volume", WM8983_LOUT2_SPK_VOLUME_CTRL,
			 WM8983_ROUT2_SPK_VOLUME_CTRL, 0, 63, 0, out_tlv),
	SOC_DOUBLE_R("Speaker Playback ZC Switch", WM8983_LOUT2_SPK_VOLUME_CTRL,
		     WM8983_ROUT2_SPK_VOLUME_CTRL, 7, 1, 0),
	SOC_DOUBLE_R("Speaker Switch", WM8983_LOUT2_SPK_VOLUME_CTRL,
		     WM8983_ROUT2_SPK_VOLUME_CTRL, 6, 1, 1),

	SOC_SINGLE("OUT3 Switch", WM8983_OUT3_MIXER_CTRL,
		   6, 1, 1),

	SOC_SINGLE("OUT4 Switch", WM8983_OUT4_MONO_MIX_CTRL,
		   6, 1, 1),

	SOC_SINGLE("High Pass Filter Switch", WM8983_ADC_CONTROL, 8, 1, 0),
	SOC_ENUM("High Pass Filter Mode", filter_mode),
	SOC_SINGLE("High Pass Filter Cutoff", WM8983_ADC_CONTROL, 4, 7, 0),

	SOC_DOUBLE_R_TLV("Aux Bypass Volume",
			 WM8983_LEFT_MIXER_CTRL, WM8983_RIGHT_MIXER_CTRL, 6, 7, 0,
			 aux_tlv),

	SOC_DOUBLE_R_TLV("Input PGA Bypass Volume",
			 WM8983_LEFT_MIXER_CTRL, WM8983_RIGHT_MIXER_CTRL, 2, 7, 0,
			 bypass_tlv),

	SOC_ENUM_EXT("Equalizer Function", eqmode, eqmode_get, eqmode_put),
	SOC_ENUM("EQ1 Cutoff", eq1_cutoff),
	SOC_SINGLE_TLV("EQ1 Volume", WM8983_EQ1_LOW_SHELF,  0, 24, 1, eq_tlv),
	SOC_ENUM("EQ2 Bandwidth", eq2_bw),
	SOC_ENUM("EQ2 Cutoff", eq2_cutoff),
	SOC_SINGLE_TLV("EQ2 Volume", WM8983_EQ2_PEAK_1, 0, 24, 1, eq_tlv),
	SOC_ENUM("EQ3 Bandwidth", eq3_bw),
	SOC_ENUM("EQ3 Cutoff", eq3_cutoff),
	SOC_SINGLE_TLV("EQ3 Volume", WM8983_EQ3_PEAK_2, 0, 24, 1, eq_tlv),
	SOC_ENUM("EQ4 Bandwidth", eq4_bw),
	SOC_ENUM("EQ4 Cutoff", eq4_cutoff),
	SOC_SINGLE_TLV("EQ4 Volume", WM8983_EQ4_PEAK_3, 0, 24, 1, eq_tlv),
	SOC_ENUM("EQ5 Cutoff", eq5_cutoff),
	SOC_SINGLE_TLV("EQ5 Volume", WM8983_EQ5_HIGH_SHELF, 0, 24, 1, eq_tlv),

	SOC_ENUM("3D Depth", depth_3d),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_out_mixer[] = अणु
	SOC_DAPM_SINGLE("Line Switch", WM8983_LEFT_MIXER_CTRL, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux Switch", WM8983_LEFT_MIXER_CTRL, 5, 1, 0),
	SOC_DAPM_SINGLE("PCM Switch", WM8983_LEFT_MIXER_CTRL, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_out_mixer[] = अणु
	SOC_DAPM_SINGLE("Line Switch", WM8983_RIGHT_MIXER_CTRL, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux Switch", WM8983_RIGHT_MIXER_CTRL, 5, 1, 0),
	SOC_DAPM_SINGLE("PCM Switch", WM8983_RIGHT_MIXER_CTRL, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_input_mixer[] = अणु
	SOC_DAPM_SINGLE("L2 Switch", WM8983_INPUT_CTRL, 2, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", WM8983_INPUT_CTRL, 1, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", WM8983_INPUT_CTRL, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_input_mixer[] = अणु
	SOC_DAPM_SINGLE("R2 Switch", WM8983_INPUT_CTRL, 6, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", WM8983_INPUT_CTRL, 5, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", WM8983_INPUT_CTRL, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_boost_mixer[] = अणु
	SOC_DAPM_SINGLE_TLV("L2 Volume", WM8983_LEFT_ADC_BOOST_CTRL,
			    4, 7, 0, boost_tlv),
	SOC_DAPM_SINGLE_TLV("AUXL Volume", WM8983_LEFT_ADC_BOOST_CTRL,
			    0, 7, 0, boost_tlv)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new out3_mixer[] = अणु
	SOC_DAPM_SINGLE("LMIX2OUT3 Switch", WM8983_OUT3_MIXER_CTRL,
			1, 1, 0),
	SOC_DAPM_SINGLE("LDAC2OUT3 Switch", WM8983_OUT3_MIXER_CTRL,
			0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new out4_mixer[] = अणु
	SOC_DAPM_SINGLE("LMIX2OUT4 Switch", WM8983_OUT4_MONO_MIX_CTRL,
			4, 1, 0),
	SOC_DAPM_SINGLE("RMIX2OUT4 Switch", WM8983_OUT4_MONO_MIX_CTRL,
			1, 1, 0),
	SOC_DAPM_SINGLE("LDAC2OUT4 Switch", WM8983_OUT4_MONO_MIX_CTRL,
			3, 1, 0),
	SOC_DAPM_SINGLE("RDAC2OUT4 Switch", WM8983_OUT4_MONO_MIX_CTRL,
			0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_boost_mixer[] = अणु
	SOC_DAPM_SINGLE_TLV("R2 Volume", WM8983_RIGHT_ADC_BOOST_CTRL,
			    4, 7, 0, boost_tlv),
	SOC_DAPM_SINGLE_TLV("AUXR Volume", WM8983_RIGHT_ADC_BOOST_CTRL,
			    0, 7, 0, boost_tlv)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8983_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", WM8983_POWER_MANAGEMENT_3,
			 0, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", WM8983_POWER_MANAGEMENT_3,
			 1, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8983_POWER_MANAGEMENT_2,
			 0, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8983_POWER_MANAGEMENT_2,
			 1, 0),

	SND_SOC_DAPM_MIXER("Left Output Mixer", WM8983_POWER_MANAGEMENT_3,
			   2, 0, left_out_mixer, ARRAY_SIZE(left_out_mixer)),
	SND_SOC_DAPM_MIXER("Right Output Mixer", WM8983_POWER_MANAGEMENT_3,
			   3, 0, right_out_mixer, ARRAY_SIZE(right_out_mixer)),

	SND_SOC_DAPM_MIXER("Left Input Mixer", WM8983_POWER_MANAGEMENT_2,
			   2, 0, left_input_mixer, ARRAY_SIZE(left_input_mixer)),
	SND_SOC_DAPM_MIXER("Right Input Mixer", WM8983_POWER_MANAGEMENT_2,
			   3, 0, right_input_mixer, ARRAY_SIZE(right_input_mixer)),

	SND_SOC_DAPM_MIXER("Left Boost Mixer", WM8983_POWER_MANAGEMENT_2,
			   4, 0, left_boost_mixer, ARRAY_SIZE(left_boost_mixer)),
	SND_SOC_DAPM_MIXER("Right Boost Mixer", WM8983_POWER_MANAGEMENT_2,
			   5, 0, right_boost_mixer, ARRAY_SIZE(right_boost_mixer)),

	SND_SOC_DAPM_MIXER("OUT3 Mixer", WM8983_POWER_MANAGEMENT_1,
			   6, 0, out3_mixer, ARRAY_SIZE(out3_mixer)),

	SND_SOC_DAPM_MIXER("OUT4 Mixer", WM8983_POWER_MANAGEMENT_1,
			   7, 0, out4_mixer, ARRAY_SIZE(out4_mixer)),

	SND_SOC_DAPM_PGA("Left Capture PGA", WM8983_LEFT_INP_PGA_GAIN_CTRL,
			 6, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Capture PGA", WM8983_RIGHT_INP_PGA_GAIN_CTRL,
			 6, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Headphone Out", WM8983_POWER_MANAGEMENT_2,
			 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Headphone Out", WM8983_POWER_MANAGEMENT_2,
			 8, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Speaker Out", WM8983_POWER_MANAGEMENT_3,
			 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Speaker Out", WM8983_POWER_MANAGEMENT_3,
			 6, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("OUT3 Out", WM8983_POWER_MANAGEMENT_3,
			 7, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("OUT4 Out", WM8983_POWER_MANAGEMENT_3,
			 8, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", WM8983_POWER_MANAGEMENT_1, 4, 0,
			    शून्य, 0),

	SND_SOC_DAPM_INPUT("LIN"),
	SND_SOC_DAPM_INPUT("LIP"),
	SND_SOC_DAPM_INPUT("RIN"),
	SND_SOC_DAPM_INPUT("RIP"),
	SND_SOC_DAPM_INPUT("AUXL"),
	SND_SOC_DAPM_INPUT("AUXR"),
	SND_SOC_DAPM_INPUT("L2"),
	SND_SOC_DAPM_INPUT("R2"),
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPKL"),
	SND_SOC_DAPM_OUTPUT("SPKR"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_OUTPUT("OUT4")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8983_audio_map[] = अणु
	अणु "OUT3 Mixer", "LMIX2OUT3 Switch", "Left Output Mixer" पूर्ण,
	अणु "OUT3 Mixer", "LDAC2OUT3 Switch", "Left DAC" पूर्ण,

	अणु "OUT3 Out", शून्य, "OUT3 Mixer" पूर्ण,
	अणु "OUT3", शून्य, "OUT3 Out" पूर्ण,

	अणु "OUT4 Mixer", "LMIX2OUT4 Switch", "Left Output Mixer" पूर्ण,
	अणु "OUT4 Mixer", "RMIX2OUT4 Switch", "Right Output Mixer" पूर्ण,
	अणु "OUT4 Mixer", "LDAC2OUT4 Switch", "Left DAC" पूर्ण,
	अणु "OUT4 Mixer", "RDAC2OUT4 Switch", "Right DAC" पूर्ण,

	अणु "OUT4 Out", शून्य, "OUT4 Mixer" पूर्ण,
	अणु "OUT4", शून्य, "OUT4 Out" पूर्ण,

	अणु "Right Output Mixer", "PCM Switch", "Right DAC" पूर्ण,
	अणु "Right Output Mixer", "Aux Switch", "AUXR" पूर्ण,
	अणु "Right Output Mixer", "Line Switch", "Right Boost Mixer" पूर्ण,

	अणु "Left Output Mixer", "PCM Switch", "Left DAC" पूर्ण,
	अणु "Left Output Mixer", "Aux Switch", "AUXL" पूर्ण,
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

	अणु "Right Boost Mixer", "AUXR Volume", "AUXR" पूर्ण,
	अणु "Right Boost Mixer", शून्य, "Right Capture PGA" पूर्ण,
	अणु "Right Boost Mixer", "R2 Volume", "R2" पूर्ण,

	अणु "Left ADC", शून्य, "Left Boost Mixer" पूर्ण,

	अणु "Left Boost Mixer", "AUXL Volume", "AUXL" पूर्ण,
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

अटल पूर्णांक eqmode_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM8983_EQ1_LOW_SHELF);
	अगर (reg & WM8983_EQ3DMODE)
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

	reg_eq = snd_soc_component_पढ़ो(component, WM8983_EQ1_LOW_SHELF);
	चयन ((reg_eq & WM8983_EQ3DMODE) >> WM8983_EQ3DMODE_SHIFT) अणु
	हाल 0:
		अगर (!ucontrol->value.क्रमागतerated.item[0])
			वापस 0;
		अवरोध;
	हाल 1:
		अगर (ucontrol->value.क्रमागतerated.item[0])
			वापस 0;
		अवरोध;
	पूर्ण

	regpwr2 = snd_soc_component_पढ़ो(component, WM8983_POWER_MANAGEMENT_2);
	regpwr3 = snd_soc_component_पढ़ो(component, WM8983_POWER_MANAGEMENT_3);
	/* disable the DACs and ADCs */
	snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_2,
			    WM8983_ADCENR_MASK | WM8983_ADCENL_MASK, 0);
	snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_3,
			    WM8983_DACENR_MASK | WM8983_DACENL_MASK, 0);
	/* set the desired eqmode */
	snd_soc_component_update_bits(component, WM8983_EQ1_LOW_SHELF,
			    WM8983_EQ3DMODE_MASK,
			    ucontrol->value.क्रमागतerated.item[0]
			    << WM8983_EQ3DMODE_SHIFT);
	/* restore DAC/ADC configuration */
	snd_soc_component_ग_लिखो(component, WM8983_POWER_MANAGEMENT_2, regpwr2);
	snd_soc_component_ग_लिखो(component, WM8983_POWER_MANAGEMENT_3, regpwr3);
	वापस 0;
पूर्ण

अटल bool wm8983_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8983_SOFTWARE_RESET ... WM8983_RIGHT_ADC_DIGITAL_VOL:
	हाल WM8983_EQ1_LOW_SHELF ... WM8983_DAC_LIMITER_2:
	हाल WM8983_NOTCH_FILTER_1 ... WM8983_NOTCH_FILTER_4:
	हाल WM8983_ALC_CONTROL_1 ... WM8983_PLL_K_3:
	हाल WM8983_3D_CONTROL ... WM8983_OUT4_MONO_MIX_CTRL:
	हाल WM8983_BIAS_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8983_dac_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	वापस snd_soc_component_update_bits(component, WM8983_DAC_CONTROL,
				   WM8983_SOFTMUTE_MASK,
				   !!mute << WM8983_SOFTMUTE_SHIFT);
पूर्ण

अटल पूर्णांक wm8983_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 क्रमmat, master, bcp, lrp;

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

	snd_soc_component_update_bits(component, WM8983_AUDIO_INTERFACE,
			    WM8983_FMT_MASK, क्रमmat << WM8983_FMT_SHIFT);

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

	snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
			    WM8983_MS_MASK, master << WM8983_MS_SHIFT);

	/* FIXME: We करोn't currently support DSP A/B modes */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		dev_err(dai->dev, "DSP A/B modes are not supported\n");
		वापस -EINVAL;
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

	snd_soc_component_update_bits(component, WM8983_AUDIO_INTERFACE,
			    WM8983_LRCP_MASK, lrp << WM8983_LRCP_SHIFT);
	snd_soc_component_update_bits(component, WM8983_AUDIO_INTERFACE,
			    WM8983_BCP_MASK, bcp << WM8983_BCP_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8983_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक i;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8983_priv *wm8983 = snd_soc_component_get_drvdata(component);
	u16 blen, srate_idx;
	u32 पंचांगp;
	पूर्णांक srate_best;
	पूर्णांक ret;

	ret = snd_soc_params_to_bclk(params);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to convert params to bclk: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8983->bclk = ret;

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

	snd_soc_component_update_bits(component, WM8983_AUDIO_INTERFACE,
			    WM8983_WL_MASK, blen << WM8983_WL_SHIFT);

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
	snd_soc_component_update_bits(component, WM8983_ADDITIONAL_CONTROL,
			    WM8983_SR_MASK, srate_idx << WM8983_SR_SHIFT);

	dev_dbg(dai->dev, "Target BCLK = %uHz\n", wm8983->bclk);
	dev_dbg(dai->dev, "SYSCLK = %uHz\n", wm8983->sysclk);

	क्रम (i = 0; i < ARRAY_SIZE(fs_ratios); ++i) अणु
		अगर (wm8983->sysclk / params_rate(params)
		    == fs_ratios[i].ratio)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(fs_ratios)) अणु
		dev_err(dai->dev, "Unable to configure MCLK ratio %u/%u\n",
			wm8983->sysclk, params_rate(params));
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "MCLK ratio = %dfs\n", fs_ratios[i].ratio);
	snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
			    WM8983_MCLKDIV_MASK, i << WM8983_MCLKDIV_SHIFT);

	/* select the appropriate bclk भागider */
	पंचांगp = (wm8983->sysclk / fs_ratios[i].भाग) * 10;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); ++i) अणु
		अगर (wm8983->bclk == पंचांगp / bclk_भागs[i])
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(bclk_भागs)) अणु
		dev_err(dai->dev, "No matching BCLK divider found\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "BCLK div = %d\n", i);
	snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
			    WM8983_BCLKDIV_MASK, i << WM8983_BCLKDIV_SHIFT);

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
		prपूर्णांकk(KERN_ERR "%s: WM8983 N value is not within"
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

अटल पूर्णांक wm8983_set_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id,
			  पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			  अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_component *component;
	काष्ठा pll_भाग pll_भाग;

	component = dai->component;
	अगर (!freq_in || !freq_out) अणु
		/* disable the PLL */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_PLLEN_MASK, 0);
		वापस 0;
	पूर्ण अन्यथा अणु
		ret = pll_factors(&pll_भाग, freq_out * 4 * 2, freq_in);
		अगर (ret)
			वापस ret;

		/* disable the PLL beक्रमe re-programming it */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_PLLEN_MASK, 0);

		/* set PLLN and PRESCALE */
		snd_soc_component_ग_लिखो(component, WM8983_PLL_N,
			(pll_भाग.भाग2 << WM8983_PLL_PRESCALE_SHIFT)
			| pll_भाग.n);
		/* set PLLK */
		snd_soc_component_ग_लिखो(component, WM8983_PLL_K_3, pll_भाग.k & 0x1ff);
		snd_soc_component_ग_लिखो(component, WM8983_PLL_K_2, (pll_भाग.k >> 9) & 0x1ff);
		snd_soc_component_ग_लिखो(component, WM8983_PLL_K_1, (pll_भाग.k >> 18));
		/* enable the PLL */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
					WM8983_PLLEN_MASK, WM8983_PLLEN);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8983_set_sysclk(काष्ठा snd_soc_dai *dai,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8983_priv *wm8983 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल WM8983_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
				    WM8983_CLKSEL_MASK, 0);
		अवरोध;
	हाल WM8983_CLKSRC_PLL:
		snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
				    WM8983_CLKSEL_MASK, WM8983_CLKSEL);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown clock source: %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	wm8983->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8983_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8983_priv *wm8983 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		/* VMID at 100k */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_VMIDSEL_MASK,
				    1 << WM8983_VMIDSEL_SHIFT);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regcache_sync(wm8983->regmap);
			अगर (ret < 0) अणु
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण
			/* enable anti-pop features */
			snd_soc_component_update_bits(component, WM8983_OUT4_TO_ADC,
					    WM8983_POBCTRL_MASK | WM8983_DELEN_MASK,
					    WM8983_POBCTRL | WM8983_DELEN);
			/* enable thermal shutकरोwn */
			snd_soc_component_update_bits(component, WM8983_OUTPUT_CTRL,
					    WM8983_TSDEN_MASK, WM8983_TSDEN);
			/* enable BIASEN */
			snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
					    WM8983_BIASEN_MASK, WM8983_BIASEN);
			/* VMID at 100k */
			snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
					    WM8983_VMIDSEL_MASK,
					    1 << WM8983_VMIDSEL_SHIFT);
			msleep(250);
			/* disable anti-pop features */
			snd_soc_component_update_bits(component, WM8983_OUT4_TO_ADC,
					    WM8983_POBCTRL_MASK |
					    WM8983_DELEN_MASK, 0);
		पूर्ण

		/* VMID at 500k */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_VMIDSEL_MASK,
				    2 << WM8983_VMIDSEL_SHIFT);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* disable thermal shutकरोwn */
		snd_soc_component_update_bits(component, WM8983_OUTPUT_CTRL,
				    WM8983_TSDEN_MASK, 0);
		/* disable VMIDSEL and BIASEN */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_VMIDSEL_MASK | WM8983_BIASEN_MASK,
				    0);
		/* रुको क्रम VMID to disअक्षरge */
		msleep(100);
		snd_soc_component_ग_लिखो(component, WM8983_POWER_MANAGEMENT_1, 0);
		snd_soc_component_ग_लिखो(component, WM8983_POWER_MANAGEMENT_2, 0);
		snd_soc_component_ग_लिखो(component, WM8983_POWER_MANAGEMENT_3, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8983_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = snd_soc_component_ग_लिखो(component, WM8983_SOFTWARE_RESET, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	/* set the vol/gain update bits */
	क्रम (i = 0; i < ARRAY_SIZE(vol_update_regs); ++i)
		snd_soc_component_update_bits(component, vol_update_regs[i],
				    0x100, 0x100);

	/* mute all outमाला_दो and set PGAs to minimum gain */
	क्रम (i = WM8983_LOUT1_HP_VOLUME_CTRL;
	     i <= WM8983_OUT4_MONO_MIX_CTRL; ++i)
		snd_soc_component_update_bits(component, i, 0x40, 0x40);

	/* enable soft mute */
	snd_soc_component_update_bits(component, WM8983_DAC_CONTROL,
			    WM8983_SOFTMUTE_MASK,
			    WM8983_SOFTMUTE);

	/* enable BIASCUT */
	snd_soc_component_update_bits(component, WM8983_BIAS_CTRL,
			    WM8983_BIASCUT, WM8983_BIASCUT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm8983_dai_ops = अणु
	.mute_stream = wm8983_dac_mute,
	.hw_params = wm8983_hw_params,
	.set_fmt = wm8983_set_fmt,
	.set_sysclk = wm8983_set_sysclk,
	.set_pll = wm8983_set_pll,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा WM8983_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm8983_dai = अणु
	.name = "wm8983-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = WM8983_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = WM8983_FORMATS,
	पूर्ण,
	.ops = &wm8983_dai_ops,
	.symmetric_rate = 1
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8983 = अणु
	.probe			= wm8983_probe,
	.set_bias_level		= wm8983_set_bias_level,
	.controls		= wm8983_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8983_snd_controls),
	.dapm_widमाला_लो		= wm8983_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8983_dapm_widमाला_लो),
	.dapm_routes		= wm8983_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(wm8983_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8983_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.reg_शेषs = wm8983_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8983_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = WM8983_MAX_REGISTER,

	.ग_लिखोable_reg = wm8983_ग_लिखोable,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8983_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8983_priv *wm8983;
	पूर्णांक ret;

	wm8983 = devm_kzalloc(&spi->dev, माप *wm8983, GFP_KERNEL);
	अगर (!wm8983)
		वापस -ENOMEM;

	wm8983->regmap = devm_regmap_init_spi(spi, &wm8983_regmap);
	अगर (IS_ERR(wm8983->regmap)) अणु
		ret = PTR_ERR(wm8983->regmap);
		dev_err(&spi->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, wm8983);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
				&soc_component_dev_wm8983, &wm8983_dai, 1);
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8983_spi_driver = अणु
	.driver = अणु
		.name = "wm8983",
	पूर्ण,
	.probe = wm8983_spi_probe,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8983_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8983_priv *wm8983;
	पूर्णांक ret;

	wm8983 = devm_kzalloc(&i2c->dev, माप *wm8983, GFP_KERNEL);
	अगर (!wm8983)
		वापस -ENOMEM;

	wm8983->regmap = devm_regmap_init_i2c(i2c, &wm8983_regmap);
	अगर (IS_ERR(wm8983->regmap)) अणु
		ret = PTR_ERR(wm8983->regmap);
		dev_err(&i2c->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8983);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_component_dev_wm8983, &wm8983_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8983_i2c_id[] = अणु
	अणु "wm8983", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8983_i2c_id);

अटल काष्ठा i2c_driver wm8983_i2c_driver = अणु
	.driver = अणु
		.name = "wm8983",
	पूर्ण,
	.probe = wm8983_i2c_probe,
	.id_table = wm8983_i2c_id
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8983_modinit(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8983_i2c_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8983 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8983_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8983 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8983_modinit);

अटल व्योम __निकास wm8983_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8983_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8983_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8983_निकास);

MODULE_DESCRIPTION("ASoC WM8983 driver");
MODULE_AUTHOR("Dimitris Papastamos <dp@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
