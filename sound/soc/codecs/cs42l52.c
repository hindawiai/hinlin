<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs42l52.c -- CS42L52 ALSA SoC audio driver
 *
 * Copyright 2012 CirrusLogic, Inc.
 *
 * Author: Georgi Vlaev <joe@nucleusys.com>
 * Author: Brian Austin <brian.austin@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/cs42l52.h>
#समावेश "cs42l52.h"

काष्ठा sp_config अणु
	u8 spc, क्रमmat, spfs;
	u32 srate;
पूर्ण;

काष्ठा  cs42l52_निजी अणु
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;
	काष्ठा device *dev;
	काष्ठा sp_config config;
	काष्ठा cs42l52_platक्रमm_data pdata;
	u32 sysclk;
	u8 mclksel;
	u32 mclk;
	u8 flags;
	काष्ठा input_dev *beep;
	काष्ठा work_काष्ठा beep_work;
	पूर्णांक beep_rate;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs42l52_reg_शेषs[] = अणु
	अणु CS42L52_PWRCTL1, 0x9F पूर्ण,	/* r02 PWRCTL 1 */
	अणु CS42L52_PWRCTL2, 0x07 पूर्ण,	/* r03 PWRCTL 2 */
	अणु CS42L52_PWRCTL3, 0xFF पूर्ण,	/* r04 PWRCTL 3 */
	अणु CS42L52_CLK_CTL, 0xA0 पूर्ण,	/* r05 Clocking Ctl */
	अणु CS42L52_IFACE_CTL1, 0x00 पूर्ण,	/* r06 Interface Ctl 1 */
	अणु CS42L52_ADC_PGA_A, 0x80 पूर्ण,	/* r08 Input A Select */
	अणु CS42L52_ADC_PGA_B, 0x80 पूर्ण,	/* r09 Input B Select */
	अणु CS42L52_ANALOG_HPF_CTL, 0xA5 पूर्ण,	/* r0A Analog HPF Ctl */
	अणु CS42L52_ADC_HPF_FREQ, 0x00 पूर्ण,	/* r0B ADC HPF Corner Freq */
	अणु CS42L52_ADC_MISC_CTL, 0x00 पूर्ण,	/* r0C Misc. ADC Ctl */
	अणु CS42L52_PB_CTL1, 0x60 पूर्ण,	/* r0D Playback Ctl 1 */
	अणु CS42L52_MISC_CTL, 0x02 पूर्ण,	/* r0E Misc. Ctl */
	अणु CS42L52_PB_CTL2, 0x00 पूर्ण,	/* r0F Playback Ctl 2 */
	अणु CS42L52_MICA_CTL, 0x00 पूर्ण,	/* r10 MICA Amp Ctl */
	अणु CS42L52_MICB_CTL, 0x00 पूर्ण,	/* r11 MICB Amp Ctl */
	अणु CS42L52_PGAA_CTL, 0x00 पूर्ण,	/* r12 PGAA Vol, Misc. */
	अणु CS42L52_PGAB_CTL, 0x00 पूर्ण,	/* r13 PGAB Vol, Misc. */
	अणु CS42L52_PASSTHRUA_VOL, 0x00 पूर्ण,	/* r14 Bypass A Vol */
	अणु CS42L52_PASSTHRUB_VOL, 0x00 पूर्ण,	/* r15 Bypass B Vol */
	अणु CS42L52_ADCA_VOL, 0x00 पूर्ण,	/* r16 ADCA Volume */
	अणु CS42L52_ADCB_VOL, 0x00 पूर्ण,	/* r17 ADCB Volume */
	अणु CS42L52_ADCA_MIXER_VOL, 0x80 पूर्ण,	/* r18 ADCA Mixer Volume */
	अणु CS42L52_ADCB_MIXER_VOL, 0x80 पूर्ण,	/* r19 ADCB Mixer Volume */
	अणु CS42L52_PCMA_MIXER_VOL, 0x00 पूर्ण,	/* r1A PCMA Mixer Volume */
	अणु CS42L52_PCMB_MIXER_VOL, 0x00 पूर्ण,	/* r1B PCMB Mixer Volume */
	अणु CS42L52_BEEP_FREQ, 0x00 पूर्ण,	/* r1C Beep Freq on Time */
	अणु CS42L52_BEEP_VOL, 0x00 पूर्ण,	/* r1D Beep Volume off Time */
	अणु CS42L52_BEEP_TONE_CTL, 0x00 पूर्ण,	/* r1E Beep Tone Cfg. */
	अणु CS42L52_TONE_CTL, 0x00 पूर्ण,	/* r1F Tone Ctl */
	अणु CS42L52_MASTERA_VOL, 0x00 पूर्ण,	/* r20 Master A Volume */
	अणु CS42L52_MASTERB_VOL, 0x00 पूर्ण,	/* r21 Master B Volume */
	अणु CS42L52_HPA_VOL, 0x00 पूर्ण,	/* r22 Headphone A Volume */
	अणु CS42L52_HPB_VOL, 0x00 पूर्ण,	/* r23 Headphone B Volume */
	अणु CS42L52_SPKA_VOL, 0x00 पूर्ण,	/* r24 Speaker A Volume */
	अणु CS42L52_SPKB_VOL, 0x00 पूर्ण,	/* r25 Speaker B Volume */
	अणु CS42L52_ADC_PCM_MIXER, 0x00 पूर्ण,	/* r26 Channel Mixer and Swap */
	अणु CS42L52_LIMITER_CTL1, 0x00 पूर्ण,	/* r27 Limit Ctl 1 Thresholds */
	अणु CS42L52_LIMITER_CTL2, 0x7F पूर्ण,	/* r28 Limit Ctl 2 Release Rate */
	अणु CS42L52_LIMITER_AT_RATE, 0xC0 पूर्ण,	/* r29 Limiter Attack Rate */
	अणु CS42L52_ALC_CTL, 0x00 पूर्ण,	/* r2A ALC Ctl 1 Attack Rate */
	अणु CS42L52_ALC_RATE, 0x3F पूर्ण,	/* r2B ALC Release Rate */
	अणु CS42L52_ALC_THRESHOLD, 0x3f पूर्ण,	/* r2C ALC Thresholds */
	अणु CS42L52_NOISE_GATE_CTL, 0x00 पूर्ण,	/* r2D Noise Gate Ctl */
	अणु CS42L52_CLK_STATUS, 0x00 पूर्ण,	/* r2E Overflow and Clock Status */
	अणु CS42L52_BATT_COMPEN, 0x00 पूर्ण,	/* r2F battery Compensation */
	अणु CS42L52_BATT_LEVEL, 0x00 पूर्ण,	/* r30 VP Battery Level */
	अणु CS42L52_SPK_STATUS, 0x00 पूर्ण,	/* r31 Speaker Status */
	अणु CS42L52_TEM_CTL, 0x3B पूर्ण,	/* r32 Temp Ctl */
	अणु CS42L52_THE_FOLDBACK, 0x00 पूर्ण,	/* r33 Foldback */
पूर्ण;

अटल bool cs42l52_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L52_CHIP ... CS42L52_CHARGE_PUMP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs42l52_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L52_IFACE_CTL2:
	हाल CS42L52_CLK_STATUS:
	हाल CS42L52_BATT_LEVEL:
	हाल CS42L52_SPK_STATUS:
	हाल CS42L52_CHARGE_PUMP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(hl_tlv, -10200, 50, 0);

अटल DECLARE_TLV_DB_SCALE(hpd_tlv, -9600, 50, 1);

अटल DECLARE_TLV_DB_SCALE(ipd_tlv, -9600, 100, 0);

अटल DECLARE_TLV_DB_SCALE(mic_tlv, 1600, 100, 0);

अटल DECLARE_TLV_DB_SCALE(pga_tlv, -600, 50, 0);

अटल DECLARE_TLV_DB_SCALE(mix_tlv, -50, 50, 0);

अटल DECLARE_TLV_DB_SCALE(beep_tlv, -56, 200, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(limiter_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-3000, 600, 0),
	3, 7, TLV_DB_SCALE_ITEM(-1200, 300, 0)
);

अटल स्थिर अक्षर * स्थिर cs42l52_adca_text[] = अणु
	"Input1A", "Input2A", "Input3A", "Input4A", "PGA Input Left"पूर्ण;

अटल स्थिर अक्षर * स्थिर cs42l52_adcb_text[] = अणु
	"Input1B", "Input2B", "Input3B", "Input4B", "PGA Input Right"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adca_क्रमागत,
			    CS42L52_ADC_PGA_A, 5, cs42l52_adca_text);

अटल SOC_ENUM_SINGLE_DECL(adcb_क्रमागत,
			    CS42L52_ADC_PGA_B, 5, cs42l52_adcb_text);

अटल स्थिर काष्ठा snd_kcontrol_new adca_mux =
	SOC_DAPM_ENUM("Left ADC Input Capture Mux", adca_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adcb_mux =
	SOC_DAPM_ENUM("Right ADC Input Capture Mux", adcb_क्रमागत);

अटल स्थिर अक्षर * स्थिर mic_bias_level_text[] = अणु
	"0.5 +VA", "0.6 +VA", "0.7 +VA",
	"0.8 +VA", "0.83 +VA", "0.91 +VA"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic_bias_level_क्रमागत,
			    CS42L52_IFACE_CTL2, 0, mic_bias_level_text);

अटल स्थिर अक्षर * स्थिर cs42l52_mic_text[] = अणु "MIC1", "MIC2" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mica_क्रमागत,
			    CS42L52_MICA_CTL, 5, cs42l52_mic_text);

अटल SOC_ENUM_SINGLE_DECL(micb_क्रमागत,
			    CS42L52_MICB_CTL, 5, cs42l52_mic_text);

अटल स्थिर अक्षर * स्थिर digital_output_mux_text[] = अणु"ADC", "DSP"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(digital_output_mux_क्रमागत,
			    CS42L52_ADC_MISC_CTL, 6,
			    digital_output_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new digital_output_mux =
	SOC_DAPM_ENUM("Digital Output Mux", digital_output_mux_क्रमागत);

अटल स्थिर अक्षर * स्थिर hp_gain_num_text[] = अणु
	"0.3959", "0.4571", "0.5111", "0.6047",
	"0.7099", "0.8399", "1.000", "1.1430"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hp_gain_क्रमागत,
			    CS42L52_PB_CTL1, 5,
			    hp_gain_num_text);

अटल स्थिर अक्षर * स्थिर beep_pitch_text[] = अणु
	"C4", "C5", "D5", "E5", "F5", "G5", "A5", "B5",
	"C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(beep_pitch_क्रमागत,
			    CS42L52_BEEP_FREQ, 4,
			    beep_pitch_text);

अटल स्थिर अक्षर * स्थिर beep_onसमय_प्रकारext[] = अणु
	"86 ms", "430 ms", "780 ms", "1.20 s", "1.50 s",
	"1.80 s", "2.20 s", "2.50 s", "2.80 s", "3.20 s",
	"3.50 s", "3.80 s", "4.20 s", "4.50 s", "4.80 s", "5.20 s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(beep_onसमय_क्रमागत,
			    CS42L52_BEEP_FREQ, 0,
			    beep_onसमय_प्रकारext);

अटल स्थिर अक्षर * स्थिर beep_offसमय_प्रकारext[] = अणु
	"1.23 s", "2.58 s", "3.90 s", "5.20 s",
	"6.60 s", "8.05 s", "9.35 s", "10.80 s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(beep_offसमय_क्रमागत,
			    CS42L52_BEEP_VOL, 5,
			    beep_offसमय_प्रकारext);

अटल स्थिर अक्षर * स्थिर beep_config_text[] = अणु
	"Off", "Single", "Multiple", "Continuous"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(beep_config_क्रमागत,
			    CS42L52_BEEP_TONE_CTL, 6,
			    beep_config_text);

अटल स्थिर अक्षर * स्थिर beep_bass_text[] = अणु
	"50 Hz", "100 Hz", "200 Hz", "250 Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(beep_bass_क्रमागत,
			    CS42L52_BEEP_TONE_CTL, 1,
			    beep_bass_text);

अटल स्थिर अक्षर * स्थिर beep_treble_text[] = अणु
	"5 kHz", "7 kHz", "10 kHz", " 15 kHz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(beep_treble_क्रमागत,
			    CS42L52_BEEP_TONE_CTL, 3,
			    beep_treble_text);

अटल स्थिर अक्षर * स्थिर ng_threshold_text[] = अणु
	"-34dB", "-37dB", "-40dB", "-43dB",
	"-46dB", "-52dB", "-58dB", "-64dB"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ng_threshold_क्रमागत,
			    CS42L52_NOISE_GATE_CTL, 2,
			    ng_threshold_text);

अटल स्थिर अक्षर * स्थिर cs42l52_ng_delay_text[] = अणु
	"50ms", "100ms", "150ms", "200ms"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ng_delay_क्रमागत,
			    CS42L52_NOISE_GATE_CTL, 0,
			    cs42l52_ng_delay_text);

अटल स्थिर अक्षर * स्थिर cs42l52_ng_type_text[] = अणु
	"Apply Specific", "Apply All"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ng_type_क्रमागत,
			    CS42L52_NOISE_GATE_CTL, 6,
			    cs42l52_ng_type_text);

अटल स्थिर अक्षर * स्थिर left_swap_text[] = अणु
	"Left", "LR 2", "Right"पूर्ण;

अटल स्थिर अक्षर * स्थिर right_swap_text[] = अणु
	"Right", "LR 2", "Left"पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक swap_values[] = अणु 0, 1, 3 पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adca_swap_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L52_ADC_PCM_MIXER, 2, 3,
			      ARRAY_SIZE(left_swap_text),
			      left_swap_text,
			      swap_values);

अटल स्थिर काष्ठा snd_kcontrol_new adca_mixer =
	SOC_DAPM_ENUM("Route", adca_swap_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत pcma_swap_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L52_ADC_PCM_MIXER, 6, 3,
			      ARRAY_SIZE(left_swap_text),
			      left_swap_text,
			      swap_values);

अटल स्थिर काष्ठा snd_kcontrol_new pcma_mixer =
	SOC_DAPM_ENUM("Route", pcma_swap_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत adcb_swap_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L52_ADC_PCM_MIXER, 0, 3,
			      ARRAY_SIZE(right_swap_text),
			      right_swap_text,
			      swap_values);

अटल स्थिर काष्ठा snd_kcontrol_new adcb_mixer =
	SOC_DAPM_ENUM("Route", adcb_swap_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत pcmb_swap_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L52_ADC_PCM_MIXER, 4, 3,
			      ARRAY_SIZE(right_swap_text),
			      right_swap_text,
			      swap_values);

अटल स्थिर काष्ठा snd_kcontrol_new pcmb_mixer =
	SOC_DAPM_ENUM("Route", pcmb_swap_क्रमागत);


अटल स्थिर काष्ठा snd_kcontrol_new passthrul_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L52_MISC_CTL, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new passthrur_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L52_MISC_CTL, 7, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new spkl_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L52_PWRCTL3, 0, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new spkr_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L52_PWRCTL3, 2, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpl_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L52_PWRCTL3, 4, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpr_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L52_PWRCTL3, 6, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new cs42l52_snd_controls[] = अणु

	SOC_DOUBLE_R_SX_TLV("Master Volume", CS42L52_MASTERA_VOL,
			      CS42L52_MASTERB_VOL, 0, 0x34, 0xE4, hl_tlv),

	SOC_DOUBLE_R_SX_TLV("Headphone Volume", CS42L52_HPA_VOL,
			      CS42L52_HPB_VOL, 0, 0x34, 0xC0, hpd_tlv),

	SOC_ENUM("Headphone Analog Gain", hp_gain_क्रमागत),

	SOC_DOUBLE_R_SX_TLV("Speaker Volume", CS42L52_SPKA_VOL,
			      CS42L52_SPKB_VOL, 0, 0x40, 0xC0, hl_tlv),

	SOC_DOUBLE_R_SX_TLV("Bypass Volume", CS42L52_PASSTHRUA_VOL,
			      CS42L52_PASSTHRUB_VOL, 0, 0x88, 0x90, pga_tlv),

	SOC_DOUBLE("Bypass Mute", CS42L52_MISC_CTL, 4, 5, 1, 0),

	SOC_DOUBLE_R_TLV("MIC Gain Volume", CS42L52_MICA_CTL,
			      CS42L52_MICB_CTL, 0, 0x10, 0, mic_tlv),

	SOC_ENUM("MIC Bias Level", mic_bias_level_क्रमागत),

	SOC_DOUBLE_R_SX_TLV("ADC Volume", CS42L52_ADCA_VOL,
			      CS42L52_ADCB_VOL, 0, 0xA0, 0x78, ipd_tlv),
	SOC_DOUBLE_R_SX_TLV("ADC Mixer Volume",
			     CS42L52_ADCA_MIXER_VOL, CS42L52_ADCB_MIXER_VOL,
				0, 0x19, 0x7F, ipd_tlv),

	SOC_DOUBLE("ADC Switch", CS42L52_ADC_MISC_CTL, 0, 1, 1, 0),

	SOC_DOUBLE_R("ADC Mixer Switch", CS42L52_ADCA_MIXER_VOL,
		     CS42L52_ADCB_MIXER_VOL, 7, 1, 1),

	SOC_DOUBLE_R_SX_TLV("PGA Volume", CS42L52_PGAA_CTL,
			    CS42L52_PGAB_CTL, 0, 0x28, 0x24, pga_tlv),

	SOC_DOUBLE_R_SX_TLV("PCM Mixer Volume",
			    CS42L52_PCMA_MIXER_VOL, CS42L52_PCMB_MIXER_VOL,
				0, 0x19, 0x7f, mix_tlv),
	SOC_DOUBLE_R("PCM Mixer Switch",
		     CS42L52_PCMA_MIXER_VOL, CS42L52_PCMB_MIXER_VOL, 7, 1, 1),

	SOC_ENUM("Beep Config", beep_config_क्रमागत),
	SOC_ENUM("Beep Pitch", beep_pitch_क्रमागत),
	SOC_ENUM("Beep on Time", beep_onसमय_क्रमागत),
	SOC_ENUM("Beep off Time", beep_offसमय_क्रमागत),
	SOC_SINGLE_SX_TLV("Beep Volume", CS42L52_BEEP_VOL,
			0, 0x07, 0x1f, beep_tlv),
	SOC_SINGLE("Beep Mixer Switch", CS42L52_BEEP_TONE_CTL, 5, 1, 1),
	SOC_ENUM("Beep Treble Corner Freq", beep_treble_क्रमागत),
	SOC_ENUM("Beep Bass Corner Freq", beep_bass_क्रमागत),

	SOC_SINGLE("Tone Control Switch", CS42L52_BEEP_TONE_CTL, 0, 1, 1),
	SOC_SINGLE_TLV("Treble Gain Volume",
			    CS42L52_TONE_CTL, 4, 15, 1, hl_tlv),
	SOC_SINGLE_TLV("Bass Gain Volume",
			    CS42L52_TONE_CTL, 0, 15, 1, hl_tlv),

	/* Limiter */
	SOC_SINGLE_TLV("Limiter Max Threshold Volume",
		       CS42L52_LIMITER_CTL1, 5, 7, 0, limiter_tlv),
	SOC_SINGLE_TLV("Limiter Cushion Threshold Volume",
		       CS42L52_LIMITER_CTL1, 2, 7, 0, limiter_tlv),
	SOC_SINGLE_TLV("Limiter Release Rate Volume",
		       CS42L52_LIMITER_CTL2, 0, 63, 0, limiter_tlv),
	SOC_SINGLE_TLV("Limiter Attack Rate Volume",
		       CS42L52_LIMITER_AT_RATE, 0, 63, 0, limiter_tlv),

	SOC_SINGLE("Limiter SR Switch", CS42L52_LIMITER_CTL1, 1, 1, 0),
	SOC_SINGLE("Limiter ZC Switch", CS42L52_LIMITER_CTL1, 0, 1, 0),
	SOC_SINGLE("Limiter Switch", CS42L52_LIMITER_CTL2, 7, 1, 0),

	/* ALC */
	SOC_SINGLE_TLV("ALC Attack Rate Volume", CS42L52_ALC_CTL,
		       0, 63, 0, limiter_tlv),
	SOC_SINGLE_TLV("ALC Release Rate Volume", CS42L52_ALC_RATE,
		       0, 63, 0, limiter_tlv),
	SOC_SINGLE_TLV("ALC Max Threshold Volume", CS42L52_ALC_THRESHOLD,
		       5, 7, 0, limiter_tlv),
	SOC_SINGLE_TLV("ALC Min Threshold Volume", CS42L52_ALC_THRESHOLD,
		       2, 7, 0, limiter_tlv),

	SOC_DOUBLE_R("ALC SR Capture Switch", CS42L52_PGAA_CTL,
		     CS42L52_PGAB_CTL, 7, 1, 1),
	SOC_DOUBLE_R("ALC ZC Capture Switch", CS42L52_PGAA_CTL,
		     CS42L52_PGAB_CTL, 6, 1, 1),
	SOC_DOUBLE("ALC Capture Switch", CS42L52_ALC_CTL, 6, 7, 1, 0),

	/* Noise gate */
	SOC_ENUM("NG Type Switch", ng_type_क्रमागत),
	SOC_SINGLE("NG Enable Switch", CS42L52_NOISE_GATE_CTL, 6, 1, 0),
	SOC_SINGLE("NG Boost Switch", CS42L52_NOISE_GATE_CTL, 5, 1, 1),
	SOC_ENUM("NG Threshold", ng_threshold_क्रमागत),
	SOC_ENUM("NG Delay", ng_delay_क्रमागत),

	SOC_DOUBLE("HPF Switch", CS42L52_ANALOG_HPF_CTL, 5, 7, 1, 0),

	SOC_DOUBLE("Analog SR Switch", CS42L52_ANALOG_HPF_CTL, 1, 3, 1, 1),
	SOC_DOUBLE("Analog ZC Switch", CS42L52_ANALOG_HPF_CTL, 0, 2, 1, 1),
	SOC_SINGLE("Digital SR Switch", CS42L52_MISC_CTL, 1, 1, 0),
	SOC_SINGLE("Digital ZC Switch", CS42L52_MISC_CTL, 0, 1, 0),
	SOC_SINGLE("Deemphasis Switch", CS42L52_MISC_CTL, 2, 1, 0),

	SOC_SINGLE("Batt Compensation Switch", CS42L52_BATT_COMPEN, 7, 1, 0),
	SOC_SINGLE("Batt VP Monitor Switch", CS42L52_BATT_COMPEN, 6, 1, 0),
	SOC_SINGLE("Batt VP ref", CS42L52_BATT_COMPEN, 0, 0x0f, 0),

	SOC_SINGLE("PGA AIN1L Switch", CS42L52_ADC_PGA_A, 0, 1, 0),
	SOC_SINGLE("PGA AIN1R Switch", CS42L52_ADC_PGA_B, 0, 1, 0),
	SOC_SINGLE("PGA AIN2L Switch", CS42L52_ADC_PGA_A, 1, 1, 0),
	SOC_SINGLE("PGA AIN2R Switch", CS42L52_ADC_PGA_B, 1, 1, 0),

	SOC_SINGLE("PGA AIN3L Switch", CS42L52_ADC_PGA_A, 2, 1, 0),
	SOC_SINGLE("PGA AIN3R Switch", CS42L52_ADC_PGA_B, 2, 1, 0),

	SOC_SINGLE("PGA AIN4L Switch", CS42L52_ADC_PGA_A, 3, 1, 0),
	SOC_SINGLE("PGA AIN4R Switch", CS42L52_ADC_PGA_B, 3, 1, 0),

	SOC_SINGLE("PGA MICA Switch", CS42L52_ADC_PGA_A, 4, 1, 0),
	SOC_SINGLE("PGA MICB Switch", CS42L52_ADC_PGA_B, 4, 1, 0),

पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs42l52_mica_controls[] = अणु
	SOC_ENUM("MICA Select", mica_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs42l52_micb_controls[] = अणु
	SOC_ENUM("MICB Select", micb_क्रमागत),
पूर्ण;

अटल पूर्णांक cs42l52_add_mic_controls(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);
	काष्ठा cs42l52_platक्रमm_data *pdata = &cs42l52->pdata;

	अगर (!pdata->mica_dअगरf_cfg)
		snd_soc_add_component_controls(component, cs42l52_mica_controls,
				     ARRAY_SIZE(cs42l52_mica_controls));

	अगर (!pdata->micb_dअगरf_cfg)
		snd_soc_add_component_controls(component, cs42l52_micb_controls,
				     ARRAY_SIZE(cs42l52_micb_controls));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42l52_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_INPUT("AIN1L"),
	SND_SOC_DAPM_INPUT("AIN1R"),
	SND_SOC_DAPM_INPUT("AIN2L"),
	SND_SOC_DAPM_INPUT("AIN2R"),
	SND_SOC_DAPM_INPUT("AIN3L"),
	SND_SOC_DAPM_INPUT("AIN3R"),
	SND_SOC_DAPM_INPUT("AIN4L"),
	SND_SOC_DAPM_INPUT("AIN4R"),
	SND_SOC_DAPM_INPUT("MICA"),
	SND_SOC_DAPM_INPUT("MICB"),
	SND_SOC_DAPM_SIGGEN("Beep"),

	SND_SOC_DAPM_AIF_OUT("AIFOUTL", शून्य,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIFOUTR", शून्य,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_ADC("ADC Left", शून्य, CS42L52_PWRCTL1, 1, 1),
	SND_SOC_DAPM_ADC("ADC Right", शून्य, CS42L52_PWRCTL1, 2, 1),
	SND_SOC_DAPM_PGA("PGA Left", CS42L52_PWRCTL1, 3, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA Right", CS42L52_PWRCTL1, 4, 1, शून्य, 0),

	SND_SOC_DAPM_MUX("ADC Left Mux", SND_SOC_NOPM, 0, 0, &adca_mux),
	SND_SOC_DAPM_MUX("ADC Right Mux", SND_SOC_NOPM, 0, 0, &adcb_mux),

	SND_SOC_DAPM_MUX("ADC Left Swap", SND_SOC_NOPM,
			 0, 0, &adca_mixer),
	SND_SOC_DAPM_MUX("ADC Right Swap", SND_SOC_NOPM,
			 0, 0, &adcb_mixer),

	SND_SOC_DAPM_MUX("Output Mux", SND_SOC_NOPM,
			 0, 0, &digital_output_mux),

	SND_SOC_DAPM_PGA("PGA MICA", CS42L52_PWRCTL2, 1, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA MICB", CS42L52_PWRCTL2, 2, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", CS42L52_PWRCTL2, 0, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Charge Pump", CS42L52_PWRCTL1, 7, 1, शून्य, 0),

	SND_SOC_DAPM_AIF_IN("AIFINL", शून्य,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINR", शून्य,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DAC Left", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Right", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SWITCH("Bypass Left", CS42L52_MISC_CTL,
			    6, 0, &passthrul_ctl),
	SND_SOC_DAPM_SWITCH("Bypass Right", CS42L52_MISC_CTL,
			    7, 0, &passthrur_ctl),

	SND_SOC_DAPM_MUX("PCM Left Swap", SND_SOC_NOPM,
			 0, 0, &pcma_mixer),
	SND_SOC_DAPM_MUX("PCM Right Swap", SND_SOC_NOPM,
			 0, 0, &pcmb_mixer),

	SND_SOC_DAPM_SWITCH("HP Left Amp", SND_SOC_NOPM, 0, 0, &hpl_ctl),
	SND_SOC_DAPM_SWITCH("HP Right Amp", SND_SOC_NOPM, 0, 0, &hpr_ctl),

	SND_SOC_DAPM_SWITCH("SPK Left Amp", SND_SOC_NOPM, 0, 0, &spkl_ctl),
	SND_SOC_DAPM_SWITCH("SPK Right Amp", SND_SOC_NOPM, 0, 0, &spkr_ctl),

	SND_SOC_DAPM_OUTPUT("HPOUTA"),
	SND_SOC_DAPM_OUTPUT("HPOUTB"),
	SND_SOC_DAPM_OUTPUT("SPKOUTA"),
	SND_SOC_DAPM_OUTPUT("SPKOUTB"),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs42l52_audio_map[] = अणु

	अणु"Capture", शून्य, "AIFOUTL"पूर्ण,
	अणु"Capture", शून्य, "AIFOUTL"पूर्ण,

	अणु"AIFOUTL", शून्य, "Output Mux"पूर्ण,
	अणु"AIFOUTR", शून्य, "Output Mux"पूर्ण,

	अणु"Output Mux", "ADC", "ADC Left"पूर्ण,
	अणु"Output Mux", "ADC", "ADC Right"पूर्ण,

	अणु"ADC Left", शून्य, "Charge Pump"पूर्ण,
	अणु"ADC Right", शून्य, "Charge Pump"पूर्ण,

	अणु"Charge Pump", शून्य, "ADC Left Mux"पूर्ण,
	अणु"Charge Pump", शून्य, "ADC Right Mux"पूर्ण,

	अणु"ADC Left Mux", "Input1A", "AIN1L"पूर्ण,
	अणु"ADC Right Mux", "Input1B", "AIN1R"पूर्ण,
	अणु"ADC Left Mux", "Input2A", "AIN2L"पूर्ण,
	अणु"ADC Right Mux", "Input2B", "AIN2R"पूर्ण,
	अणु"ADC Left Mux", "Input3A", "AIN3L"पूर्ण,
	अणु"ADC Right Mux", "Input3B", "AIN3R"पूर्ण,
	अणु"ADC Left Mux", "Input4A", "AIN4L"पूर्ण,
	अणु"ADC Right Mux", "Input4B", "AIN4R"पूर्ण,
	अणु"ADC Left Mux", "PGA Input Left", "PGA Left"पूर्ण,
	अणु"ADC Right Mux", "PGA Input Right" , "PGA Right"पूर्ण,

	अणु"PGA Left", "Switch", "AIN1L"पूर्ण,
	अणु"PGA Right", "Switch", "AIN1R"पूर्ण,
	अणु"PGA Left", "Switch", "AIN2L"पूर्ण,
	अणु"PGA Right", "Switch", "AIN2R"पूर्ण,
	अणु"PGA Left", "Switch", "AIN3L"पूर्ण,
	अणु"PGA Right", "Switch", "AIN3R"पूर्ण,
	अणु"PGA Left", "Switch", "AIN4L"पूर्ण,
	अणु"PGA Right", "Switch", "AIN4R"पूर्ण,

	अणु"PGA Left", "Switch", "PGA MICA"पूर्ण,
	अणु"PGA MICA", शून्य, "MICA"पूर्ण,

	अणु"PGA Right", "Switch", "PGA MICB"पूर्ण,
	अणु"PGA MICB", शून्य, "MICB"पूर्ण,

	अणु"HPOUTA", शून्य, "HP Left Amp"पूर्ण,
	अणु"HPOUTB", शून्य, "HP Right Amp"पूर्ण,
	अणु"HP Left Amp", शून्य, "Bypass Left"पूर्ण,
	अणु"HP Right Amp", शून्य, "Bypass Right"पूर्ण,
	अणु"Bypass Left", "Switch", "PGA Left"पूर्ण,
	अणु"Bypass Right", "Switch", "PGA Right"पूर्ण,
	अणु"HP Left Amp", "Switch", "DAC Left"पूर्ण,
	अणु"HP Right Amp", "Switch", "DAC Right"पूर्ण,

	अणु"SPKOUTA", शून्य, "SPK Left Amp"पूर्ण,
	अणु"SPKOUTB", शून्य, "SPK Right Amp"पूर्ण,

	अणु"SPK Left Amp", शून्य, "Beep"पूर्ण,
	अणु"SPK Right Amp", शून्य, "Beep"पूर्ण,
	अणु"SPK Left Amp", "Switch", "Playback"पूर्ण,
	अणु"SPK Right Amp", "Switch", "Playback"पूर्ण,

	अणु"DAC Left", शून्य, "Beep"पूर्ण,
	अणु"DAC Right", शून्य, "Beep"पूर्ण,
	अणु"DAC Left", शून्य, "Playback"पूर्ण,
	अणु"DAC Right", शून्य, "Playback"पूर्ण,

	अणु"Output Mux", "DSP", "Playback"पूर्ण,
	अणु"Output Mux", "DSP", "Playback"पूर्ण,

	अणु"AIFINL", शून्य, "Playback"पूर्ण,
	अणु"AIFINR", शून्य, "Playback"पूर्ण,

पूर्ण;

काष्ठा cs42l52_clk_para अणु
	u32 mclk;
	u32 rate;
	u8 speed;
	u8 group;
	u8 videoclk;
	u8 ratio;
	u8 mclkभाग2;
पूर्ण;

अटल स्थिर काष्ठा cs42l52_clk_para clk_map_table[] = अणु
	/*8k*/
	अणु12288000, 8000, CLK_QS_MODE, CLK_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु18432000, 8000, CLK_QS_MODE, CLK_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु12000000, 8000, CLK_QS_MODE, CLK_32K, CLK_NO_27M, CLK_R_125, 0पूर्ण,
	अणु24000000, 8000, CLK_QS_MODE, CLK_32K, CLK_NO_27M, CLK_R_125, 1पूर्ण,
	अणु27000000, 8000, CLK_QS_MODE, CLK_32K, CLK_27M_MCLK, CLK_R_125, 0पूर्ण,

	/*11.025k*/
	अणु11289600, 11025, CLK_QS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु16934400, 11025, CLK_QS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,

	/*16k*/
	अणु12288000, 16000, CLK_HS_MODE, CLK_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु18432000, 16000, CLK_HS_MODE, CLK_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु12000000, 16000, CLK_HS_MODE, CLK_32K, CLK_NO_27M, CLK_R_125, 0पूर्ण,
	अणु24000000, 16000, CLK_HS_MODE, CLK_32K, CLK_NO_27M, CLK_R_125, 1पूर्ण,
	अणु27000000, 16000, CLK_HS_MODE, CLK_32K, CLK_27M_MCLK, CLK_R_125, 1पूर्ण,

	/*22.05k*/
	अणु11289600, 22050, CLK_HS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु16934400, 22050, CLK_HS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,

	/* 32k */
	अणु12288000, 32000, CLK_SS_MODE, CLK_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु18432000, 32000, CLK_SS_MODE, CLK_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु12000000, 32000, CLK_SS_MODE, CLK_32K, CLK_NO_27M, CLK_R_125, 0पूर्ण,
	अणु24000000, 32000, CLK_SS_MODE, CLK_32K, CLK_NO_27M, CLK_R_125, 1पूर्ण,
	अणु27000000, 32000, CLK_SS_MODE, CLK_32K, CLK_27M_MCLK, CLK_R_125, 0पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, CLK_SS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु16934400, 44100, CLK_SS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,

	/* 48k */
	अणु12288000, 48000, CLK_SS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु18432000, 48000, CLK_SS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु12000000, 48000, CLK_SS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_125, 0पूर्ण,
	अणु24000000, 48000, CLK_SS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_125, 1पूर्ण,
	अणु27000000, 48000, CLK_SS_MODE, CLK_NO_32K, CLK_27M_MCLK, CLK_R_125, 1पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, CLK_DS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु16934400, 88200, CLK_DS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,

	/* 96k */
	अणु12288000, 96000, CLK_DS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु18432000, 96000, CLK_DS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_128, 0पूर्ण,
	अणु12000000, 96000, CLK_DS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_125, 0पूर्ण,
	अणु24000000, 96000, CLK_DS_MODE, CLK_NO_32K, CLK_NO_27M, CLK_R_125, 1पूर्ण,
पूर्ण;

अटल पूर्णांक cs42l52_get_clk(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i, ret = -EINVAL;
	u_पूर्णांक mclk1, mclk2 = 0;

	क्रम (i = 0; i < ARRAY_SIZE(clk_map_table); i++) अणु
		अगर (clk_map_table[i].rate == rate) अणु
			mclk1 = clk_map_table[i].mclk;
			अगर (असल(mclk - mclk1) < असल(mclk - mclk2)) अणु
				mclk2 = mclk1;
				ret = i;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cs42l52_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
			पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);

	अगर ((freq >= CS42L52_MIN_CLK) && (freq <= CS42L52_MAX_CLK)) अणु
		cs42l52->sysclk = freq;
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Invalid freq parameter\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs42l52_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);
	u8 अगरace = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace = CS42L52_IFACE_CTL1_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगरace = CS42L52_IFACE_CTL1_SLAVE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	 /* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= CS42L52_IFACE_CTL1_ADC_FMT_I2S |
				CS42L52_IFACE_CTL1_DAC_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगरace |= CS42L52_IFACE_CTL1_DAC_FMT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= CS42L52_IFACE_CTL1_ADC_FMT_LEFT_J |
				CS42L52_IFACE_CTL1_DAC_FMT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= CS42L52_IFACE_CTL1_DSP_MODE_EN;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= CS42L52_IFACE_CTL1_INV_SCLK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= CS42L52_IFACE_CTL1_INV_SCLK;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	cs42l52->config.क्रमmat = अगरace;
	snd_soc_component_ग_लिखो(component, CS42L52_IFACE_CTL1, cs42l52->config.क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l52_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute)
		snd_soc_component_update_bits(component, CS42L52_PB_CTL1,
				    CS42L52_PB_CTL1_MUTE_MASK,
				CS42L52_PB_CTL1_MUTE);
	अन्यथा
		snd_soc_component_update_bits(component, CS42L52_PB_CTL1,
				    CS42L52_PB_CTL1_MUTE_MASK,
				CS42L52_PB_CTL1_UNMUTE);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l52_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);
	u32 clk = 0;
	पूर्णांक index;

	index = cs42l52_get_clk(cs42l52->sysclk, params_rate(params));
	अगर (index >= 0) अणु
		cs42l52->sysclk = clk_map_table[index].mclk;

		clk |= (clk_map_table[index].speed << CLK_SPEED_SHIFT) |
		(clk_map_table[index].group << CLK_32K_SR_SHIFT) |
		(clk_map_table[index].videoclk << CLK_27M_MCLK_SHIFT) |
		(clk_map_table[index].ratio << CLK_RATIO_SHIFT) |
		clk_map_table[index].mclkभाग2;

		snd_soc_component_ग_लिखो(component, CS42L52_CLK_CTL, clk);
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "can't get correct mclk\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l52_set_bias_level(काष्ठा snd_soc_component *component,
					क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, CS42L52_PWRCTL1,
				    CS42L52_PWRCTL1_PDN_CODEC, 0);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_cache_only(cs42l52->regmap, false);
			regcache_sync(cs42l52->regmap);
		पूर्ण
		snd_soc_component_ग_लिखो(component, CS42L52_PWRCTL1, CS42L52_PWRCTL1_PDN_ALL);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, CS42L52_PWRCTL1, CS42L52_PWRCTL1_PDN_ALL);
		regcache_cache_only(cs42l52->regmap, true);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CS42L52_RATES (SNDRV_PCM_RATE_8000_96000)

#घोषणा CS42L52_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE | \
			SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_U18_3LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_U20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_U24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops cs42l52_ops = अणु
	.hw_params	= cs42l52_pcm_hw_params,
	.mute_stream	= cs42l52_mute,
	.set_fmt	= cs42l52_set_fmt,
	.set_sysclk	= cs42l52_set_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs42l52_dai = अणु
		.name = "cs42l52",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CS42L52_RATES,
			.क्रमmats = CS42L52_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CS42L52_RATES,
			.क्रमmats = CS42L52_FORMATS,
		पूर्ण,
		.ops = &cs42l52_ops,
पूर्ण;

अटल पूर्णांक beep_rates[] = अणु
	261, 522, 585, 667, 706, 774, 889, 1000,
	1043, 1200, 1333, 1412, 1600, 1714, 2000, 2182
पूर्ण;

अटल व्योम cs42l52_beep_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cs42l52_निजी *cs42l52 =
		container_of(work, काष्ठा cs42l52_निजी, beep_work);
	काष्ठा snd_soc_component *component = cs42l52->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक i;
	पूर्णांक val = 0;
	पूर्णांक best = 0;

	अगर (cs42l52->beep_rate) अणु
		क्रम (i = 0; i < ARRAY_SIZE(beep_rates); i++) अणु
			अगर (असल(cs42l52->beep_rate - beep_rates[i]) <
			    असल(cs42l52->beep_rate - beep_rates[best]))
				best = i;
		पूर्ण

		dev_dbg(component->dev, "Set beep rate %dHz for requested %dHz\n",
			beep_rates[best], cs42l52->beep_rate);

		val = (best << CS42L52_BEEP_RATE_SHIFT);

		snd_soc_dapm_enable_pin(dapm, "Beep");
	पूर्ण अन्यथा अणु
		dev_dbg(component->dev, "Disabling beep\n");
		snd_soc_dapm_disable_pin(dapm, "Beep");
	पूर्ण

	snd_soc_component_update_bits(component, CS42L52_BEEP_FREQ,
			    CS42L52_BEEP_RATE_MASK, val);

	snd_soc_dapm_sync(dapm);
पूर्ण

/* For usability define a way of injecting beep events क्रम the device -
 * many प्रणालीs will not have a keyboard.
 */
अटल पूर्णांक cs42l52_beep_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			     अचिन्हित पूर्णांक code, पूर्णांक hz)
अणु
	काष्ठा snd_soc_component *component = input_get_drvdata(dev);
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "Beep event %x %x\n", code, hz);

	चयन (code) अणु
	हाल SND_BELL:
		अगर (hz)
			hz = 261;
		अवरोध;
	हाल SND_TONE:
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	/* Kick the beep from a workqueue */
	cs42l52->beep_rate = hz;
	schedule_work(&cs42l52->beep_work);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cs42l52_beep_set(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cs42l52_निजी *cs42l52 = dev_get_drvdata(dev);
	दीर्घ पूर्णांक समय;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &समय);
	अगर (ret != 0)
		वापस ret;

	input_event(cs42l52->beep, EV_SND, SND_TONE, समय);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(beep, 0200, शून्य, cs42l52_beep_set);

अटल व्योम cs42l52_init_beep(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	cs42l52->beep = devm_input_allocate_device(component->dev);
	अगर (!cs42l52->beep) अणु
		dev_err(component->dev, "Failed to allocate beep device\n");
		वापस;
	पूर्ण

	INIT_WORK(&cs42l52->beep_work, cs42l52_beep_work);
	cs42l52->beep_rate = 0;

	cs42l52->beep->name = "CS42L52 Beep Generator";
	cs42l52->beep->phys = dev_name(component->dev);
	cs42l52->beep->id.bustype = BUS_I2C;

	cs42l52->beep->evbit[0] = BIT_MASK(EV_SND);
	cs42l52->beep->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
	cs42l52->beep->event = cs42l52_beep_event;
	cs42l52->beep->dev.parent = component->dev;
	input_set_drvdata(cs42l52->beep, component);

	ret = input_रेजिस्टर_device(cs42l52->beep);
	अगर (ret != 0) अणु
		cs42l52->beep = शून्य;
		dev_err(component->dev, "Failed to register beep device\n");
	पूर्ण

	ret = device_create_file(component->dev, &dev_attr_beep);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to create keyclick file: %d\n",
			ret);
	पूर्ण
पूर्ण

अटल व्योम cs42l52_मुक्त_beep(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);

	device_हटाओ_file(component->dev, &dev_attr_beep);
	cancel_work_sync(&cs42l52->beep_work);
	cs42l52->beep = शून्य;

	snd_soc_component_update_bits(component, CS42L52_BEEP_TONE_CTL,
			    CS42L52_BEEP_EN_MASK, 0);
पूर्ण

अटल पूर्णांक cs42l52_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l52_निजी *cs42l52 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(cs42l52->regmap, true);

	cs42l52_add_mic_controls(component);

	cs42l52_init_beep(component);

	cs42l52->sysclk = CS42L52_DEFAULT_CLK;
	cs42l52->config.क्रमmat = CS42L52_DEFAULT_FORMAT;

	वापस 0;
पूर्ण

अटल व्योम cs42l52_हटाओ(काष्ठा snd_soc_component *component)
अणु
	cs42l52_मुक्त_beep(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs42l52 = अणु
	.probe			= cs42l52_probe,
	.हटाओ			= cs42l52_हटाओ,
	.set_bias_level		= cs42l52_set_bias_level,
	.controls		= cs42l52_snd_controls,
	.num_controls		= ARRAY_SIZE(cs42l52_snd_controls),
	.dapm_widमाला_लो		= cs42l52_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs42l52_dapm_widमाला_लो),
	.dapm_routes		= cs42l52_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs42l52_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/* Current and threshold घातerup sequence Pg37 */
अटल स्थिर काष्ठा reg_sequence cs42l52_threshold_patch[] = अणु

	अणु 0x00, 0x99 पूर्ण,
	अणु 0x3E, 0xBA पूर्ण,
	अणु 0x47, 0x80 पूर्ण,
	अणु 0x32, 0xBB पूर्ण,
	अणु 0x32, 0x3B पूर्ण,
	अणु 0x00, 0x00 पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा regmap_config cs42l52_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS42L52_MAX_REGISTER,
	.reg_शेषs = cs42l52_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs42l52_reg_शेषs),
	.पढ़ोable_reg = cs42l52_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs42l52_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक cs42l52_i2c_probe(काष्ठा i2c_client *i2c_client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs42l52_निजी *cs42l52;
	काष्ठा cs42l52_platक्रमm_data *pdata = dev_get_platdata(&i2c_client->dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;
	u32 val32;

	cs42l52 = devm_kzalloc(&i2c_client->dev, माप(*cs42l52), GFP_KERNEL);
	अगर (cs42l52 == शून्य)
		वापस -ENOMEM;
	cs42l52->dev = &i2c_client->dev;

	cs42l52->regmap = devm_regmap_init_i2c(i2c_client, &cs42l52_regmap);
	अगर (IS_ERR(cs42l52->regmap)) अणु
		ret = PTR_ERR(cs42l52->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (pdata) अणु
		cs42l52->pdata = *pdata;
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(&i2c_client->dev, माप(*pdata),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		अगर (i2c_client->dev.of_node) अणु
			अगर (of_property_पढ़ो_bool(i2c_client->dev.of_node,
				"cirrus,mica-differential-cfg"))
				pdata->mica_dअगरf_cfg = true;

			अगर (of_property_पढ़ो_bool(i2c_client->dev.of_node,
				"cirrus,micb-differential-cfg"))
				pdata->micb_dअगरf_cfg = true;

			अगर (of_property_पढ़ो_u32(i2c_client->dev.of_node,
				"cirrus,micbias-lvl", &val32) >= 0)
				pdata->micbias_lvl = val32;

			अगर (of_property_पढ़ो_u32(i2c_client->dev.of_node,
				"cirrus,chgfreq-divisor", &val32) >= 0)
				pdata->chgfreq = val32;

			pdata->reset_gpio =
				of_get_named_gpio(i2c_client->dev.of_node,
						"cirrus,reset-gpio", 0);
		पूर्ण
		cs42l52->pdata = *pdata;
	पूर्ण

	अगर (cs42l52->pdata.reset_gpio) अणु
		ret = devm_gpio_request_one(&i2c_client->dev,
					    cs42l52->pdata.reset_gpio,
					    GPIOF_OUT_INIT_HIGH,
					    "CS42L52 /RST");
		अगर (ret < 0) अणु
			dev_err(&i2c_client->dev, "Failed to request /RST %d: %d\n",
				cs42l52->pdata.reset_gpio, ret);
			वापस ret;
		पूर्ण
		gpio_set_value_cansleep(cs42l52->pdata.reset_gpio, 0);
		gpio_set_value_cansleep(cs42l52->pdata.reset_gpio, 1);
	पूर्ण

	i2c_set_clientdata(i2c_client, cs42l52);

	ret = regmap_रेजिस्टर_patch(cs42l52->regmap, cs42l52_threshold_patch,
				    ARRAY_SIZE(cs42l52_threshold_patch));
	अगर (ret != 0)
		dev_warn(cs42l52->dev, "Failed to apply regmap patch: %d\n",
			 ret);

	ret = regmap_पढ़ो(cs42l52->regmap, CS42L52_CHIP, &reg);
	devid = reg & CS42L52_CHIP_ID_MASK;
	अगर (devid != CS42L52_CHIP_ID) अणु
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS42L52 Device ID (%X). Expected %X\n",
			devid, CS42L52_CHIP_ID);
		वापस ret;
	पूर्ण

	dev_info(&i2c_client->dev, "Cirrus Logic CS42L52, Revision: %02X\n",
		 reg & CS42L52_CHIP_REV_MASK);

	/* Set Platक्रमm Data */
	अगर (cs42l52->pdata.mica_dअगरf_cfg)
		regmap_update_bits(cs42l52->regmap, CS42L52_MICA_CTL,
				   CS42L52_MIC_CTL_TYPE_MASK,
				cs42l52->pdata.mica_dअगरf_cfg <<
				CS42L52_MIC_CTL_TYPE_SHIFT);

	अगर (cs42l52->pdata.micb_dअगरf_cfg)
		regmap_update_bits(cs42l52->regmap, CS42L52_MICB_CTL,
				   CS42L52_MIC_CTL_TYPE_MASK,
				cs42l52->pdata.micb_dअगरf_cfg <<
				CS42L52_MIC_CTL_TYPE_SHIFT);

	अगर (cs42l52->pdata.chgfreq)
		regmap_update_bits(cs42l52->regmap, CS42L52_CHARGE_PUMP,
				   CS42L52_CHARGE_PUMP_MASK,
				cs42l52->pdata.chgfreq <<
				CS42L52_CHARGE_PUMP_SHIFT);

	अगर (cs42l52->pdata.micbias_lvl)
		regmap_update_bits(cs42l52->regmap, CS42L52_IFACE_CTL2,
				   CS42L52_IFACE_CTL2_BIAS_LVL,
				cs42l52->pdata.micbias_lvl);

	ret =  devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_dev_cs42l52, &cs42l52_dai, 1);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cs42l52_of_match[] = अणु
	अणु .compatible = "cirrus,cs42l52", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs42l52_of_match);


अटल स्थिर काष्ठा i2c_device_id cs42l52_id[] = अणु
	अणु "cs42l52", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs42l52_id);

अटल काष्ठा i2c_driver cs42l52_i2c_driver = अणु
	.driver = अणु
		.name = "cs42l52",
		.of_match_table = cs42l52_of_match,
	पूर्ण,
	.id_table = cs42l52_id,
	.probe =    cs42l52_i2c_probe,
पूर्ण;

module_i2c_driver(cs42l52_i2c_driver);

MODULE_DESCRIPTION("ASoC CS42L52 driver");
MODULE_AUTHOR("Georgi Vlaev, Nucleus Systems Ltd, <joe@nucleusys.com>");
MODULE_AUTHOR("Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>");
MODULE_LICENSE("GPL");
