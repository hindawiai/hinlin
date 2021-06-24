<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* alc5632.c  --  ALC5632 ALSA SoC Audio Codec
*
* Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.lauchpad.net>
*
* Authors:  Leon Romanovsky <leon@leon.nu>
*           Andrey Danin <danindrey@mail.ru>
*           Ilya Petrov <ilya.muromec@gmail.com>
*           Marc Dietrich <marvin24@gmx.de>
*
* Based on alc5623.c by Arnaud Patard
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश "alc5632.h"

/*
 * ALC5632 रेजिस्टर cache
 */
अटल स्थिर काष्ठा reg_शेष alc5632_reg_शेषs[] = अणु
	अणु   2, 0x8080 पूर्ण,	/* R2   - Speaker Output Volume */
	अणु   4, 0x8080 पूर्ण,	/* R4   - Headphone Output Volume */
	अणु   6, 0x8080 पूर्ण,	/* R6   - AUXOUT Volume */
	अणु   8, 0xC800 पूर्ण,	/* R8   - Phone Input */
	अणु  10, 0xE808 पूर्ण,	/* R10  - LINE_IN Volume */
	अणु  12, 0x1010 पूर्ण,	/* R12  - STEREO DAC Input Volume */
	अणु  14, 0x0808 पूर्ण,	/* R14  - MIC Input Volume */
	अणु  16, 0xEE0F पूर्ण,	/* R16  - Stereo DAC and MIC Routing Control */
	अणु  18, 0xCBCB पूर्ण,	/* R18  - ADC Record Gain */
	अणु  20, 0x7F7F पूर्ण,	/* R20  - ADC Record Mixer Control */
	अणु  24, 0xE010 पूर्ण,	/* R24  - Voice DAC Volume */
	अणु  28, 0x8008 पूर्ण,	/* R28  - Output Mixer Control */
	अणु  34, 0x0000 पूर्ण,	/* R34  - Microphone Control */
	अणु  36, 0x00C0 पूर्ण,    /* R36  - Codec Digital MIC/Digital Boost
						   Control */
	अणु  46, 0x0000 पूर्ण,	/* R46  - Stereo DAC/Voice DAC/Stereo ADC
						   Function Select */
	अणु  52, 0x8000 पूर्ण,	/* R52  - Main Serial Data Port Control
						   (Stereo I2S) */
	अणु  54, 0x0000 पूर्ण,	/* R54  - Extend Serial Data Port Control
						   (VoDAC_I2S/PCM) */
	अणु  58, 0x0000 पूर्ण,	/* R58  - Power Management Addition 1 */
	अणु  60, 0x0000 पूर्ण,	/* R60  - Power Management Addition 2 */
	अणु  62, 0x8000 पूर्ण,	/* R62  - Power Management Addition 3 */
	अणु  64, 0x0C0A पूर्ण,	/* R64  - General Purpose Control Register 1 */
	अणु  66, 0x0000 पूर्ण,	/* R66  - General Purpose Control Register 2 */
	अणु  68, 0x0000 पूर्ण,	/* R68  - PLL1 Control */
	अणु  70, 0x0000 पूर्ण,	/* R70  - PLL2 Control */
	अणु  76, 0xBE3E पूर्ण,	/* R76  - GPIO Pin Configuration */
	अणु  78, 0xBE3E पूर्ण,	/* R78  - GPIO Pin Polarity */
	अणु  80, 0x0000 पूर्ण,	/* R80  - GPIO Pin Sticky */
	अणु  82, 0x0000 पूर्ण,	/* R82  - GPIO Pin Wake Up */
	अणु  86, 0x0000 पूर्ण,	/* R86  - Pin Sharing */
	अणु  90, 0x0009 पूर्ण,	/* R90  - Soft Volume Control Setting */
	अणु  92, 0x0000 पूर्ण,	/* R92  - GPIO_Output Pin Control */
	अणु  94, 0x3000 पूर्ण,	/* R94  - MISC Control */
	अणु  96, 0x3075 पूर्ण,	/* R96  - Stereo DAC Clock Control_1 */
	अणु  98, 0x1010 पूर्ण,	/* R98  - Stereo DAC Clock Control_2 */
	अणु 100, 0x3110 पूर्ण,	/* R100 - VoDAC_PCM Clock Control_1 */
	अणु 104, 0x0553 पूर्ण,	/* R104 - Pseuकरो Stereo and Spatial Effect
						   Block Control */
	अणु 106, 0x0000 पूर्ण,	/* R106 - Private Register Address */
पूर्ण;

/* codec निजी data */
काष्ठा alc5632_priv अणु
	काष्ठा regmap *regmap;
	u8 id;
	अचिन्हित पूर्णांक sysclk;
पूर्ण;

अटल bool alc5632_अस्थिर_रेजिस्टर(काष्ठा device *dev,
							अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ALC5632_RESET:
	हाल ALC5632_PWR_DOWN_CTRL_STATUS:
	हाल ALC5632_GPIO_PIN_STATUS:
	हाल ALC5632_OVER_CURR_STATUS:
	हाल ALC5632_HID_CTRL_DATA:
	हाल ALC5632_EQ_CTRL:
	हाल ALC5632_VENDOR_ID1:
	हाल ALC5632_VENDOR_ID2:
		वापस true;

	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक alc5632_reset(काष्ठा regmap *map)
अणु
	वापस regmap_ग_लिखो(map, ALC5632_RESET, 0x59B4);
पूर्ण

अटल पूर्णांक amp_mixer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	/* to घातer-on/off class-d amp generators/speaker */
	/* need to ग_लिखो to 'index-46h' रेजिस्टर :        */
	/* so ग_लिखो index num (here 0x46) to reg 0x6a     */
	/* and then 0xffff/0 to reg 0x6c                  */
	snd_soc_component_ग_लिखो(component, ALC5632_HID_CTRL_INDEX, 0x46);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_ग_लिखो(component, ALC5632_HID_CTRL_DATA, 0xFFFF);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, ALC5632_HID_CTRL_DATA, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ALC5632 Controls
 */

/* -34.5db min scale, 1.5db steps, no mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(vol_tlv, -3450, 150, 0);
/* -46.5db min scale, 1.5db steps, no mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_tlv, -4650, 150, 0);
/* -16.5db min scale, 1.5db steps, no mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_rec_tlv, -1650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(boost_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 2000, 0),
	1, 3, TLV_DB_SCALE_ITEM(2000, 1000, 0)
);
/* 0db min scale, 6 db steps, no mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(dig_tlv, 0, 600, 0);
/* 0db min scalem 0.75db steps, no mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(vdac_tlv, -3525, 75, 0);

अटल स्थिर काष्ठा snd_kcontrol_new alc5632_vol_snd_controls[] = अणु
	/* left starts at bit 8, right at bit 0 */
	/* 31 steps (5 bit), -46.5db scale */
	SOC_DOUBLE_TLV("Speaker Playback Volume",
			ALC5632_SPK_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	/* bit 15 mutes left, bit 7 right */
	SOC_DOUBLE("Speaker Playback Switch",
			ALC5632_SPK_OUT_VOL, 15, 7, 1, 1),
	SOC_DOUBLE_TLV("Headphone Playback Volume",
			ALC5632_HP_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Headphone Playback Switch",
			ALC5632_HP_OUT_VOL, 15, 7, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5632_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Auxout Playback Volume",
			ALC5632_AUX_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Auxout Playback Switch",
			ALC5632_AUX_OUT_VOL, 15, 7, 1, 1),
	SOC_SINGLE_TLV("Voice DAC Playback Volume",
			ALC5632_VOICE_DAC_VOL, 0, 63, 0, vdac_tlv),
	SOC_SINGLE("Voice DAC Playback Switch",
			ALC5632_VOICE_DAC_VOL, 12, 1, 1),
	SOC_SINGLE_TLV("Phone Playback Volume",
			ALC5632_PHONE_IN_VOL, 8, 31, 1, vol_tlv),
	SOC_DOUBLE_TLV("LineIn Playback Volume",
			ALC5632_LINE_IN_VOL, 8, 0, 31, 1, vol_tlv),
	SOC_DOUBLE_TLV("Master Playback Volume",
			ALC5632_STEREO_DAC_IN_VOL, 8, 0, 63, 1, vdac_tlv),
	SOC_DOUBLE("Master Playback Switch",
			ALC5632_STEREO_DAC_IN_VOL, 15, 7, 1, 1),
	SOC_SINGLE_TLV("Mic1 Playback Volume",
			ALC5632_MIC_VOL, 8, 31, 1, vol_tlv),
	SOC_SINGLE_TLV("Mic2 Playback Volume",
			ALC5632_MIC_VOL, 0, 31, 1, vol_tlv),
	SOC_DOUBLE_TLV("Rec Capture Volume",
			ALC5632_ADC_REC_GAIN, 8, 0, 31, 0, adc_rec_tlv),
	SOC_SINGLE_TLV("Mic 1 Boost Volume",
			ALC5632_MIC_CTRL, 10, 3, 0, boost_tlv),
	SOC_SINGLE_TLV("Mic 2 Boost Volume",
			ALC5632_MIC_CTRL, 8, 3, 0, boost_tlv),
	SOC_SINGLE_TLV("DMIC Boost Capture Volume",
			ALC5632_DIGI_BOOST_CTRL, 0, 7, 0, dig_tlv),
	SOC_SINGLE("DMIC En Capture Switch",
			ALC5632_DIGI_BOOST_CTRL, 15, 1, 0),
	SOC_SINGLE("DMIC PreFilter Capture Switch",
			ALC5632_DIGI_BOOST_CTRL, 12, 1, 0),
पूर्ण;

/*
 * DAPM Controls
 */
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_hp_mixer_controls[] = अणु
SOC_DAPM_SINGLE("LI2HP Playback Switch", ALC5632_LINE_IN_VOL, 15, 1, 1),
SOC_DAPM_SINGLE("PHONE2HP Playback Switch", ALC5632_PHONE_IN_VOL, 15, 1, 1),
SOC_DAPM_SINGLE("MIC12HP Playback Switch", ALC5632_MIC_ROUTING_CTRL, 15, 1, 1),
SOC_DAPM_SINGLE("MIC22HP Playback Switch", ALC5632_MIC_ROUTING_CTRL, 11, 1, 1),
SOC_DAPM_SINGLE("VOICE2HP Playback Switch", ALC5632_VOICE_DAC_VOL, 15, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5632_hpl_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ADC2HP_L Playback Switch", ALC5632_ADC_REC_GAIN, 15, 1, 1),
SOC_DAPM_SINGLE("DACL2HP Playback Switch", ALC5632_MIC_ROUTING_CTRL, 3, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5632_hpr_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ADC2HP_R Playback Switch", ALC5632_ADC_REC_GAIN, 7, 1, 1),
SOC_DAPM_SINGLE("DACR2HP Playback Switch", ALC5632_MIC_ROUTING_CTRL, 2, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5632_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ADC2MONO_L Playback Switch", ALC5632_ADC_REC_GAIN, 14, 1, 1),
SOC_DAPM_SINGLE("ADC2MONO_R Playback Switch", ALC5632_ADC_REC_GAIN, 6, 1, 1),
SOC_DAPM_SINGLE("LI2MONO Playback Switch", ALC5632_LINE_IN_VOL, 13, 1, 1),
SOC_DAPM_SINGLE("MIC12MONO Playback Switch",
					ALC5632_MIC_ROUTING_CTRL, 13, 1, 1),
SOC_DAPM_SINGLE("MIC22MONO Playback Switch",
					ALC5632_MIC_ROUTING_CTRL, 9, 1, 1),
SOC_DAPM_SINGLE("DAC2MONO Playback Switch", ALC5632_MIC_ROUTING_CTRL, 0, 1, 1),
SOC_DAPM_SINGLE("VOICE2MONO Playback Switch", ALC5632_VOICE_DAC_VOL, 13, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5632_speaker_mixer_controls[] = अणु
SOC_DAPM_SINGLE("LI2SPK Playback Switch", ALC5632_LINE_IN_VOL, 14, 1, 1),
SOC_DAPM_SINGLE("PHONE2SPK Playback Switch", ALC5632_PHONE_IN_VOL, 14, 1, 1),
SOC_DAPM_SINGLE("MIC12SPK Playback Switch",
					ALC5632_MIC_ROUTING_CTRL, 14, 1, 1),
SOC_DAPM_SINGLE("MIC22SPK Playback Switch",
					ALC5632_MIC_ROUTING_CTRL, 10, 1, 1),
SOC_DAPM_SINGLE("DAC2SPK Playback Switch", ALC5632_MIC_ROUTING_CTRL, 1, 1, 1),
SOC_DAPM_SINGLE("VOICE2SPK Playback Switch", ALC5632_VOICE_DAC_VOL, 14, 1, 1),
पूर्ण;

/* Left Record Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_captureL_mixer_controls[] = अणु
SOC_DAPM_SINGLE("MIC12REC_L Capture Switch", ALC5632_ADC_REC_MIXER, 14, 1, 1),
SOC_DAPM_SINGLE("MIC22REC_L Capture Switch", ALC5632_ADC_REC_MIXER, 13, 1, 1),
SOC_DAPM_SINGLE("LIL2REC Capture Switch", ALC5632_ADC_REC_MIXER, 12, 1, 1),
SOC_DAPM_SINGLE("PH2REC_L Capture Switch", ALC5632_ADC_REC_MIXER, 11, 1, 1),
SOC_DAPM_SINGLE("HPL2REC Capture Switch", ALC5632_ADC_REC_MIXER, 10, 1, 1),
SOC_DAPM_SINGLE("SPK2REC_L Capture Switch", ALC5632_ADC_REC_MIXER, 9, 1, 1),
SOC_DAPM_SINGLE("MONO2REC_L Capture Switch", ALC5632_ADC_REC_MIXER, 8, 1, 1),
पूर्ण;

/* Right Record Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_captureR_mixer_controls[] = अणु
SOC_DAPM_SINGLE("MIC12REC_R Capture Switch", ALC5632_ADC_REC_MIXER, 6, 1, 1),
SOC_DAPM_SINGLE("MIC22REC_R Capture Switch", ALC5632_ADC_REC_MIXER, 5, 1, 1),
SOC_DAPM_SINGLE("LIR2REC Capture Switch", ALC5632_ADC_REC_MIXER, 4, 1, 1),
SOC_DAPM_SINGLE("PH2REC_R Capture Switch", ALC5632_ADC_REC_MIXER, 3, 1, 1),
SOC_DAPM_SINGLE("HPR2REC Capture Switch", ALC5632_ADC_REC_MIXER, 2, 1, 1),
SOC_DAPM_SINGLE("SPK2REC_R Capture Switch", ALC5632_ADC_REC_MIXER, 1, 1, 1),
SOC_DAPM_SINGLE("MONO2REC_R Capture Switch", ALC5632_ADC_REC_MIXER, 0, 1, 1),
पूर्ण;

/* Dmic Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_dmicl_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DMICL2ADC Capture Switch", ALC5632_DIGI_BOOST_CTRL, 7, 1, 1),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_dmicr_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DMICR2ADC Capture Switch", ALC5632_DIGI_BOOST_CTRL, 6, 1, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर alc5632_spk_n_sour_sel[] = अणु
		"RN/-R", "RP/+R", "LN/-R", "Mute"पूर्ण;
अटल स्थिर अक्षर * स्थिर alc5632_hpl_out_input_sel[] = अणु
		"Vmid", "HP Left Mix"पूर्ण;
अटल स्थिर अक्षर * स्थिर alc5632_hpr_out_input_sel[] = अणु
		"Vmid", "HP Right Mix"पूर्ण;
अटल स्थिर अक्षर * स्थिर alc5632_spkout_input_sel[] = अणु
		"Vmid", "HPOut Mix", "Speaker Mix", "Mono Mix"पूर्ण;
अटल स्थिर अक्षर * स्थिर alc5632_aux_out_input_sel[] = अणु
		"Vmid", "HPOut Mix", "Speaker Mix", "Mono Mix"पूर्ण;
अटल स्थिर अक्षर * स्थिर alc5632_adcr_func_sel[] = अणु
		"Stereo ADC", "Voice ADC"पूर्ण;
अटल स्थिर अक्षर * स्थिर alc5632_i2s_out_sel[] = अणु
		"ADC LR", "Voice Stereo Digital"पूर्ण;

/* auxout output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5632_aux_out_input_क्रमागत,
			    ALC5632_OUTPUT_MIXER_CTRL, 6,
			    alc5632_aux_out_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_auxout_mux_controls =
SOC_DAPM_ENUM("AuxOut Mux", alc5632_aux_out_input_क्रमागत);

/* speaker output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5632_spkout_input_क्रमागत,
			    ALC5632_OUTPUT_MIXER_CTRL, 10,
			    alc5632_spkout_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_spkout_mux_controls =
SOC_DAPM_ENUM("SpeakerOut Mux", alc5632_spkout_input_क्रमागत);

/* headphone left output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5632_hpl_out_input_क्रमागत,
			    ALC5632_OUTPUT_MIXER_CTRL, 9,
			    alc5632_hpl_out_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_hpl_out_mux_controls =
SOC_DAPM_ENUM("Left Headphone Mux", alc5632_hpl_out_input_क्रमागत);

/* headphone right output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5632_hpr_out_input_क्रमागत,
			    ALC5632_OUTPUT_MIXER_CTRL, 8,
			    alc5632_hpr_out_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_hpr_out_mux_controls =
SOC_DAPM_ENUM("Right Headphone Mux", alc5632_hpr_out_input_क्रमागत);

/* speaker output N select */
अटल SOC_ENUM_SINGLE_DECL(alc5632_spk_n_sour_क्रमागत,
			    ALC5632_OUTPUT_MIXER_CTRL, 14,
			    alc5632_spk_n_sour_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_spkoutn_mux_controls =
SOC_DAPM_ENUM("SpeakerOut N Mux", alc5632_spk_n_sour_क्रमागत);

/* speaker amplअगरier */
अटल स्थिर अक्षर *alc5632_amp_names[] = अणु"AB Amp", "D Amp"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(alc5632_amp_क्रमागत,
			    ALC5632_OUTPUT_MIXER_CTRL, 13,
			    alc5632_amp_names);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_amp_mux_controls =
	SOC_DAPM_ENUM("AB-D Amp Mux", alc5632_amp_क्रमागत);

/* ADC output select */
अटल SOC_ENUM_SINGLE_DECL(alc5632_adcr_func_क्रमागत,
			    ALC5632_DAC_FUNC_SELECT, 5,
			    alc5632_adcr_func_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_adcr_func_controls =
	SOC_DAPM_ENUM("ADCR Mux", alc5632_adcr_func_क्रमागत);

/* I2S out select */
अटल SOC_ENUM_SINGLE_DECL(alc5632_i2s_out_क्रमागत,
			    ALC5632_I2S_OUT_CTL, 5,
			    alc5632_i2s_out_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5632_i2s_out_controls =
	SOC_DAPM_ENUM("I2SOut Mux", alc5632_i2s_out_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget alc5632_dapm_widमाला_लो[] = अणु
/* Muxes */
SND_SOC_DAPM_MUX("AuxOut Mux", SND_SOC_NOPM, 0, 0,
	&alc5632_auxout_mux_controls),
SND_SOC_DAPM_MUX("SpeakerOut Mux", SND_SOC_NOPM, 0, 0,
	&alc5632_spkout_mux_controls),
SND_SOC_DAPM_MUX("Left Headphone Mux", SND_SOC_NOPM, 0, 0,
	&alc5632_hpl_out_mux_controls),
SND_SOC_DAPM_MUX("Right Headphone Mux", SND_SOC_NOPM, 0, 0,
	&alc5632_hpr_out_mux_controls),
SND_SOC_DAPM_MUX("SpeakerOut N Mux", SND_SOC_NOPM, 0, 0,
	&alc5632_spkoutn_mux_controls),
SND_SOC_DAPM_MUX("ADCR Mux", SND_SOC_NOPM, 0, 0,
	&alc5632_adcr_func_controls),
SND_SOC_DAPM_MUX("I2SOut Mux", ALC5632_PWR_MANAG_ADD1, 11, 0,
	&alc5632_i2s_out_controls),

/* output mixers */
SND_SOC_DAPM_MIXER("HP Mix", SND_SOC_NOPM, 0, 0,
	&alc5632_hp_mixer_controls[0],
	ARRAY_SIZE(alc5632_hp_mixer_controls)),
SND_SOC_DAPM_MIXER("HPR Mix", ALC5632_PWR_MANAG_ADD2, 4, 0,
	&alc5632_hpr_mixer_controls[0],
	ARRAY_SIZE(alc5632_hpr_mixer_controls)),
SND_SOC_DAPM_MIXER("HPL Mix", ALC5632_PWR_MANAG_ADD2, 5, 0,
	&alc5632_hpl_mixer_controls[0],
	ARRAY_SIZE(alc5632_hpl_mixer_controls)),
SND_SOC_DAPM_MIXER("HPOut Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Mono Mix", ALC5632_PWR_MANAG_ADD2, 2, 0,
	&alc5632_mono_mixer_controls[0],
	ARRAY_SIZE(alc5632_mono_mixer_controls)),
SND_SOC_DAPM_MIXER("Speaker Mix", ALC5632_PWR_MANAG_ADD2, 3, 0,
	&alc5632_speaker_mixer_controls[0],
	ARRAY_SIZE(alc5632_speaker_mixer_controls)),
SND_SOC_DAPM_MIXER("DMICL Mix", SND_SOC_NOPM, 0, 0,
	&alc5632_dmicl_mixer_controls[0],
	ARRAY_SIZE(alc5632_dmicl_mixer_controls)),
SND_SOC_DAPM_MIXER("DMICR Mix", SND_SOC_NOPM, 0, 0,
	&alc5632_dmicr_mixer_controls[0],
	ARRAY_SIZE(alc5632_dmicr_mixer_controls)),

/* input mixers */
SND_SOC_DAPM_MIXER("Left Capture Mix", ALC5632_PWR_MANAG_ADD2, 1, 0,
	&alc5632_captureL_mixer_controls[0],
	ARRAY_SIZE(alc5632_captureL_mixer_controls)),
SND_SOC_DAPM_MIXER("Right Capture Mix", ALC5632_PWR_MANAG_ADD2, 0, 0,
	&alc5632_captureR_mixer_controls[0],
	ARRAY_SIZE(alc5632_captureR_mixer_controls)),

SND_SOC_DAPM_AIF_IN("AIFRXL", "Left HiFi Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIFRXR", "Right HiFi Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIFTXL", "Left HiFi Capture", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIFTXR", "Right HiFi Capture", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("VAIFRX", "Voice Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("VAIFTX", "Voice Capture", 0, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_DAC("Voice DAC", शून्य, ALC5632_PWR_MANAG_ADD2, 10, 0),
SND_SOC_DAPM_DAC("Left DAC", शून्य, ALC5632_PWR_MANAG_ADD2, 9, 0),
SND_SOC_DAPM_DAC("Right DAC", शून्य, ALC5632_PWR_MANAG_ADD2, 8, 0),
SND_SOC_DAPM_ADC("Left ADC", शून्य, ALC5632_PWR_MANAG_ADD2, 7, 0),
SND_SOC_DAPM_ADC("Right ADC", शून्य, ALC5632_PWR_MANAG_ADD2, 6, 0),

SND_SOC_DAPM_MIXER("DAC Left Channel", ALC5632_PWR_MANAG_ADD1, 15, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("DAC Right Channel",
	ALC5632_PWR_MANAG_ADD1, 14, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("I2S Mix", ALC5632_PWR_MANAG_ADD1, 11, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Phone Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Line Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Voice Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("ADCLR", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Left Headphone", ALC5632_PWR_MANAG_ADD3, 11, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Headphone", ALC5632_PWR_MANAG_ADD3, 10, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left Speaker", ALC5632_PWR_MANAG_ADD3, 13, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Speaker", ALC5632_PWR_MANAG_ADD3, 12, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Aux Out", ALC5632_PWR_MANAG_ADD3, 14, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left LineIn", ALC5632_PWR_MANAG_ADD3, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right LineIn", ALC5632_PWR_MANAG_ADD3, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Phone", ALC5632_PWR_MANAG_ADD3, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Phone ADMix", ALC5632_PWR_MANAG_ADD3, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC1 PGA", ALC5632_PWR_MANAG_ADD3, 3, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC2 PGA", ALC5632_PWR_MANAG_ADD3, 2, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC1 Pre Amp", ALC5632_PWR_MANAG_ADD3, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC2 Pre Amp", ALC5632_PWR_MANAG_ADD3, 0, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1", ALC5632_PWR_MANAG_ADD1, 3, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS2", ALC5632_PWR_MANAG_ADD1, 2, 0, शून्य, 0),

SND_SOC_DAPM_PGA_E("D Amp", ALC5632_PWR_MANAG_ADD2, 14, 0, शून्य, 0,
	amp_mixer_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_PGA("AB Amp", ALC5632_PWR_MANAG_ADD2, 15, 0, शून्य, 0),
SND_SOC_DAPM_MUX("AB-D Amp Mux", ALC5632_PWR_MANAG_ADD1, 10, 0,
	&alc5632_amp_mux_controls),

SND_SOC_DAPM_OUTPUT("AUXOUT"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("HPR"),
SND_SOC_DAPM_OUTPUT("SPKOUT"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),

SND_SOC_DAPM_INPUT("LINEINL"),
SND_SOC_DAPM_INPUT("LINEINR"),
SND_SOC_DAPM_INPUT("PHONEP"),
SND_SOC_DAPM_INPUT("PHONEN"),
SND_SOC_DAPM_INPUT("DMICDAT"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2"),
SND_SOC_DAPM_VMID("Vmid"),
पूर्ण;


अटल स्थिर काष्ठा snd_soc_dapm_route alc5632_dapm_routes[] = अणु
	/* Playback streams */
	अणु"Left DAC", शून्य, "AIFRXL"पूर्ण,
	अणु"Right DAC", शून्य, "AIFRXR"पूर्ण,

	/* भव mixer - mixes left & right channels */
	अणु"I2S Mix",	शून्य,	"Left DAC"पूर्ण,
	अणु"I2S Mix",	शून्य,	"Right DAC"पूर्ण,
	अणु"Line Mix",	शून्य,	"Right LineIn"पूर्ण,
	अणु"Line Mix",	शून्य,	"Left LineIn"पूर्ण,
	अणु"Phone Mix",	शून्य,	"Phone"पूर्ण,
	अणु"Phone Mix",	शून्य,	"Phone ADMix"पूर्ण,
	अणु"AUXOUT",		शून्य,	"Aux Out"पूर्ण,

	/* DAC */
	अणु"DAC Right Channel",	शून्य,	"I2S Mix"पूर्ण,
	अणु"DAC Left Channel",	शून्य,   "I2S Mix"पूर्ण,

	/* HP mixer */
	अणु"HPL Mix",	"ADC2HP_L Playback Switch",	"Left Capture Mix"पूर्ण,
	अणु"HPL Mix", शून्य,					"HP Mix"पूर्ण,
	अणु"HPR Mix", "ADC2HP_R Playback Switch",	"Right Capture Mix"पूर्ण,
	अणु"HPR Mix", शून्य,					"HP Mix"पूर्ण,
	अणु"HP Mix",	"LI2HP Playback Switch",	"Line Mix"पूर्ण,
	अणु"HP Mix",	"PHONE2HP Playback Switch",	"Phone Mix"पूर्ण,
	अणु"HP Mix",	"MIC12HP Playback Switch",	"MIC1 PGA"पूर्ण,
	अणु"HP Mix",	"MIC22HP Playback Switch",	"MIC2 PGA"पूर्ण,
	अणु"HP Mix", "VOICE2HP Playback Switch",	"Voice Mix"पूर्ण,
	अणु"HPR Mix", "DACR2HP Playback Switch",	"DAC Right Channel"पूर्ण,
	अणु"HPL Mix", "DACL2HP Playback Switch",	"DAC Left Channel"पूर्ण,
	अणु"HPOut Mix", शून्य, "HP Mix"पूर्ण,
	अणु"HPOut Mix", शून्य, "HPR Mix"पूर्ण,
	अणु"HPOut Mix", शून्य, "HPL Mix"पूर्ण,

	/* speaker mixer */
	अणु"Speaker Mix", "LI2SPK Playback Switch",	"Line Mix"पूर्ण,
	अणु"Speaker Mix", "PHONE2SPK Playback Switch", "Phone Mix"पूर्ण,
	अणु"Speaker Mix", "MIC12SPK Playback Switch",	"MIC1 PGA"पूर्ण,
	अणु"Speaker Mix", "MIC22SPK Playback Switch",	"MIC2 PGA"पूर्ण,
	अणु"Speaker Mix", "DAC2SPK Playback Switch",	"DAC Left Channel"पूर्ण,
	अणु"Speaker Mix", "VOICE2SPK Playback Switch",	"Voice Mix"पूर्ण,

	/* mono mixer */
	अणु"Mono Mix", "ADC2MONO_L Playback Switch",	"Left Capture Mix"पूर्ण,
	अणु"Mono Mix", "ADC2MONO_R Playback Switch",	"Right Capture Mix"पूर्ण,
	अणु"Mono Mix", "LI2MONO Playback Switch",		"Line Mix"पूर्ण,
	अणु"Mono Mix", "MIC12MONO Playback Switch",	"MIC1 PGA"पूर्ण,
	अणु"Mono Mix", "MIC22MONO Playback Switch",	"MIC2 PGA"पूर्ण,
	अणु"Mono Mix", "DAC2MONO Playback Switch",	"DAC Left Channel"पूर्ण,
	अणु"Mono Mix", "VOICE2MONO Playback Switch",	"Voice Mix"पूर्ण,

	/* Left record mixer */
	अणु"Left Capture Mix", "LIL2REC Capture Switch", "LINEINL"पूर्ण,
	अणु"Left Capture Mix", "PH2REC_L Capture Switch", "PHONEN"पूर्ण,
	अणु"Left Capture Mix", "MIC12REC_L Capture Switch", "MIC1 Pre Amp"पूर्ण,
	अणु"Left Capture Mix", "MIC22REC_L Capture Switch", "MIC2 Pre Amp"पूर्ण,
	अणु"Left Capture Mix", "HPL2REC Capture Switch", "HPL Mix"पूर्ण,
	अणु"Left Capture Mix", "SPK2REC_L Capture Switch", "Speaker Mix"पूर्ण,
	अणु"Left Capture Mix", "MONO2REC_L Capture Switch", "Mono Mix"पूर्ण,

	/*Right record mixer */
	अणु"Right Capture Mix", "LIR2REC Capture Switch", "LINEINR"पूर्ण,
	अणु"Right Capture Mix", "PH2REC_R Capture Switch", "PHONEP"पूर्ण,
	अणु"Right Capture Mix", "MIC12REC_R Capture Switch", "MIC1 Pre Amp"पूर्ण,
	अणु"Right Capture Mix", "MIC22REC_R Capture Switch", "MIC2 Pre Amp"पूर्ण,
	अणु"Right Capture Mix", "HPR2REC Capture Switch", "HPR Mix"पूर्ण,
	अणु"Right Capture Mix", "SPK2REC_R Capture Switch", "Speaker Mix"पूर्ण,
	अणु"Right Capture Mix", "MONO2REC_R Capture Switch", "Mono Mix"पूर्ण,

	/* headphone left mux */
	अणु"Left Headphone Mux", "HP Left Mix",		"HPL Mix"पूर्ण,
	अणु"Left Headphone Mux", "Vmid",			"Vmid"पूर्ण,

	/* headphone right mux */
	अणु"Right Headphone Mux", "HP Right Mix",		"HPR Mix"पूर्ण,
	अणु"Right Headphone Mux", "Vmid",			"Vmid"पूर्ण,

	/* speaker out mux */
	अणु"SpeakerOut Mux", "Vmid",			"Vmid"पूर्ण,
	अणु"SpeakerOut Mux", "HPOut Mix",			"HPOut Mix"पूर्ण,
	अणु"SpeakerOut Mux", "Speaker Mix",		"Speaker Mix"पूर्ण,
	अणु"SpeakerOut Mux", "Mono Mix",			"Mono Mix"पूर्ण,

	/* Mono/Aux Out mux */
	अणु"AuxOut Mux", "Vmid",				"Vmid"पूर्ण,
	अणु"AuxOut Mux", "HPOut Mix",			"HPOut Mix"पूर्ण,
	अणु"AuxOut Mux", "Speaker Mix",			"Speaker Mix"पूर्ण,
	अणु"AuxOut Mux", "Mono Mix",			"Mono Mix"पूर्ण,

	/* output pga */
	अणु"HPL", शून्य,					"Left Headphone"पूर्ण,
	अणु"Left Headphone", शून्य,			"Left Headphone Mux"पूर्ण,
	अणु"HPR", शून्य,					"Right Headphone"पूर्ण,
	अणु"Right Headphone", शून्य,			"Right Headphone Mux"पूर्ण,
	अणु"Aux Out", शून्य,				"AuxOut Mux"पूर्ण,

	/* input pga */
	अणु"Left LineIn", शून्य,				"LINEINL"पूर्ण,
	अणु"Right LineIn", शून्य,				"LINEINR"पूर्ण,
	अणु"Phone", शून्य,				"PHONEP"पूर्ण,
	अणु"MIC1 Pre Amp", शून्य,				"MIC1"पूर्ण,
	अणु"MIC2 Pre Amp", शून्य,				"MIC2"पूर्ण,
	अणु"MIC1 PGA", शून्य,				"MIC1 Pre Amp"पूर्ण,
	अणु"MIC2 PGA", शून्य,				"MIC2 Pre Amp"पूर्ण,

	/* left ADC */
	अणु"Left ADC", शून्य,				"Left Capture Mix"पूर्ण,
	अणु"DMICL Mix", "DMICL2ADC Capture Switch", "DMICDAT"पूर्ण,
	अणु"Left ADC", शून्य,				"DMICL Mix"पूर्ण,
	अणु"ADCLR", शून्य,					"Left ADC"पूर्ण,

	/* right ADC */
	अणु"Right ADC", शून्य, "Right Capture Mix"पूर्ण,
	अणु"DMICR Mix", "DMICR2ADC Capture Switch", "DMICDAT"पूर्ण,
	अणु"Right ADC", शून्य, "DMICR Mix"पूर्ण,
	अणु"ADCR Mux", "Stereo ADC", "Right ADC"पूर्ण,
	अणु"ADCR Mux", "Voice ADC", "Right ADC"पूर्ण,
	अणु"ADCLR", शून्य, "ADCR Mux"पूर्ण,
	अणु"VAIFTX", शून्य, "ADCR Mux"पूर्ण,

	/* Digital I2S out */
	अणु"I2SOut Mux", "ADC LR", "ADCLR"पूर्ण,
	अणु"I2SOut Mux", "Voice Stereo Digital", "VAIFRX"पूर्ण,
	अणु"AIFTXL", शून्य, "I2SOut Mux"पूर्ण,
	अणु"AIFTXR", शून्य, "I2SOut Mux"पूर्ण,

	/* Voice Mix */
	अणु"Voice DAC", शून्य, "VAIFRX"पूर्ण,
	अणु"Voice Mix", शून्य, "Voice DAC"पूर्ण,

	/* Speaker Output */
	अणु"SpeakerOut N Mux", "RN/-R",			"Left Speaker"पूर्ण,
	अणु"SpeakerOut N Mux", "RP/+R",			"Left Speaker"पूर्ण,
	अणु"SpeakerOut N Mux", "LN/-R",			"Left Speaker"पूर्ण,
	अणु"SpeakerOut N Mux", "Mute",			"Vmid"पूर्ण,

	अणु"SpeakerOut N Mux", "RN/-R",			"Right Speaker"पूर्ण,
	अणु"SpeakerOut N Mux", "RP/+R",			"Right Speaker"पूर्ण,
	अणु"SpeakerOut N Mux", "LN/-R",			"Right Speaker"पूर्ण,
	अणु"SpeakerOut N Mux", "Mute",			"Vmid"पूर्ण,

	अणु"AB Amp", शून्य,				"SpeakerOut Mux"पूर्ण,
	अणु"D Amp", शून्य,					"SpeakerOut Mux"पूर्ण,
	अणु"AB-D Amp Mux", "AB Amp",			"AB Amp"पूर्ण,
	अणु"AB-D Amp Mux", "D Amp",			"D Amp"पूर्ण,
	अणु"Left Speaker", शून्य,				"AB-D Amp Mux"पूर्ण,
	अणु"Right Speaker", शून्य,				"AB-D Amp Mux"पूर्ण,

	अणु"SPKOUT", शून्य,				"Left Speaker"पूर्ण,
	अणु"SPKOUT", शून्य,				"Right Speaker"पूर्ण,

	अणु"SPKOUTN", शून्य,				"SpeakerOut N Mux"पूर्ण,

पूर्ण;

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 pll_in;
	u32 pll_out;
	u16 regvalue;
पूर्ण;

/* Note : pll code from original alc5632 driver. Not sure of how good it is */
/* useful only क्रम master mode */
अटल स्थिर काष्ठा _pll_भाग codec_master_pll_भाग[] = अणु

	अणु  2048000,  8192000,	0x0ea0पूर्ण,
	अणु  3686400,  8192000,	0x4e27पूर्ण,
	अणु 12000000,  8192000,	0x456bपूर्ण,
	अणु 13000000,  8192000,	0x495fपूर्ण,
	अणु 13100000,  8192000,	0x0320पूर्ण,
	अणु  2048000,  11289600,	0xf637पूर्ण,
	अणु  3686400,  11289600,	0x2f22पूर्ण,
	अणु 12000000,  11289600,	0x3e2fपूर्ण,
	अणु 13000000,  11289600,	0x4d5bपूर्ण,
	अणु 13100000,  11289600,	0x363bपूर्ण,
	अणु  2048000,  16384000,	0x1ea0पूर्ण,
	अणु  3686400,  16384000,	0x9e27पूर्ण,
	अणु 12000000,  16384000,	0x452bपूर्ण,
	अणु 13000000,  16384000,	0x542fपूर्ण,
	अणु 13100000,  16384000,	0x03a0पूर्ण,
	अणु  2048000,  16934400,	0xe625पूर्ण,
	अणु  3686400,  16934400,	0x9126पूर्ण,
	अणु 12000000,  16934400,	0x4d2cपूर्ण,
	अणु 13000000,  16934400,	0x742fपूर्ण,
	अणु 13100000,  16934400,	0x3c27पूर्ण,
	अणु  2048000,  22579200,	0x2aa0पूर्ण,
	अणु  3686400,  22579200,	0x2f20पूर्ण,
	अणु 12000000,  22579200,	0x7e2fपूर्ण,
	अणु 13000000,  22579200,	0x742fपूर्ण,
	अणु 13100000,  22579200,	0x3c27पूर्ण,
	अणु  2048000,  24576000,	0x2ea0पूर्ण,
	अणु  3686400,  24576000,	0xee27पूर्ण,
	अणु 12000000,  24576000,	0x2915पूर्ण,
	अणु 13000000,  24576000,	0x772eपूर्ण,
	अणु 13100000,  24576000,	0x0d20पूर्ण,
पूर्ण;

/* FOUT = MCLK*(N+2)/((M+2)*(K+2))
   N: bit 15:8 (भाग 2 .. भाग 257)
   K: bit  6:4 typical 2
   M: bit  3:0 (भाग 2 .. भाग 17)

   same as क्रम 5623 - thanks!
*/

अटल स्थिर काष्ठा _pll_भाग codec_slave_pll_भाग[] = अणु

	अणु  1024000,  16384000,  0x3ea0पूर्ण,
	अणु  1411200,  22579200,	0x3ea0पूर्ण,
	अणु  1536000,  24576000,	0x3ea0पूर्ण,
	अणु  2048000,  16384000,  0x1ea0पूर्ण,
	अणु  2822400,  22579200,	0x1ea0पूर्ण,
	अणु  3072000,  24576000,	0x1ea0पूर्ण,

पूर्ण;

अटल पूर्णांक alc5632_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक i;
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक gbl_clk = 0, pll_भाग = 0;
	u16 reg;

	अगर (pll_id < ALC5632_PLL_FR_MCLK || pll_id > ALC5632_PLL_FR_VBCLK)
		वापस -EINVAL;

	/* Disable PLL घातer */
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL1,
				0);
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL2,
				0);

	/* pll is not used in slave mode */
	reg = snd_soc_component_पढ़ो(component, ALC5632_DAI_CONTROL);
	अगर (reg & ALC5632_DAI_SDP_SLAVE_MODE)
		वापस 0;

	अगर (!freq_in || !freq_out)
		वापस 0;

	चयन (pll_id) अणु
	हाल ALC5632_PLL_FR_MCLK:
		क्रम (i = 0; i < ARRAY_SIZE(codec_master_pll_भाग); i++) अणु
			अगर (codec_master_pll_भाग[i].pll_in == freq_in
			   && codec_master_pll_भाग[i].pll_out == freq_out) अणु
				/* PLL source from MCLK */
				pll_भाग  = codec_master_pll_भाग[i].regvalue;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ALC5632_PLL_FR_BCLK:
		क्रम (i = 0; i < ARRAY_SIZE(codec_slave_pll_भाग); i++) अणु
			अगर (codec_slave_pll_भाग[i].pll_in == freq_in
			   && codec_slave_pll_भाग[i].pll_out == freq_out) अणु
				/* PLL source from Bitclk */
				gbl_clk = ALC5632_PLL_FR_BCLK;
				pll_भाग = codec_slave_pll_भाग[i].regvalue;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ALC5632_PLL_FR_VBCLK:
		क्रम (i = 0; i < ARRAY_SIZE(codec_slave_pll_भाग); i++) अणु
			अगर (codec_slave_pll_भाग[i].pll_in == freq_in
			   && codec_slave_pll_भाग[i].pll_out == freq_out) अणु
				/* PLL source from voice घड़ी */
				gbl_clk = ALC5632_PLL_FR_VBCLK;
				pll_भाग = codec_slave_pll_भाग[i].regvalue;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!pll_भाग)
		वापस -EINVAL;

	/* choose MCLK/BCLK/VBCLK */
	snd_soc_component_ग_लिखो(component, ALC5632_GPCR2, gbl_clk);
	/* choose PLL1 घड़ी rate */
	snd_soc_component_ग_लिखो(component, ALC5632_PLL1_CTRL, pll_भाग);
	/* enable PLL1 */
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL1,
				ALC5632_PWR_ADD2_PLL1);
	/* enable PLL2 */
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL2,
				ALC5632_PWR_ADD2_PLL2);
	/* use PLL1 as मुख्य SYSCLK */
	snd_soc_component_update_bits(component, ALC5632_GPCR1,
			ALC5632_GPCR1_CLK_SYS_SRC_SEL_PLL1,
			ALC5632_GPCR1_CLK_SYS_SRC_SEL_PLL1);

	वापस 0;
पूर्ण

काष्ठा _coeff_भाग अणु
	u16 fs;
	u16 regvalue;
पूर्ण;

/* codec hअगरi mclk (after PLL) घड़ी भागider coefficients */
/* values inspired from column BCLK=32Fs of Appendix A table */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	अणु512*1, 0x3075पूर्ण,
पूर्ण;

अटल पूर्णांक get_coeff(काष्ठा snd_soc_component *component, पूर्णांक rate)
अणु
	काष्ठा alc5632_priv *alc5632 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].fs * rate == alc5632->sysclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Clock after PLL and भागiders
 */
अटल पूर्णांक alc5632_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा alc5632_priv *alc5632 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल  4096000:
	हाल  8192000:
	हाल 11289600:
	हाल 12288000:
	हाल 16384000:
	हाल 16934400:
	हाल 18432000:
	हाल 22579200:
	हाल 24576000:
		alc5632->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक alc5632_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace = ALC5632_DAI_SDP_MASTER_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगरace = ALC5632_DAI_SDP_SLAVE_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= ALC5632_DAI_I2S_DF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= ALC5632_DAI_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= ALC5632_DAI_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= ALC5632_DAI_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= ALC5632_DAI_MAIN_I2S_BCLK_POL_CTRL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= ALC5632_DAI_MAIN_I2S_BCLK_POL_CTRL;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_ग_लिखो(component, ALC5632_DAI_CONTROL, अगरace);
पूर्ण

अटल पूर्णांक alc5632_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक coeff, rate;
	u16 अगरace;

	अगरace = snd_soc_component_पढ़ो(component, ALC5632_DAI_CONTROL);
	अगरace &= ~ALC5632_DAI_I2S_DL_MASK;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अगरace |= ALC5632_DAI_I2S_DL_16;
		अवरोध;
	हाल 20:
		अगरace |= ALC5632_DAI_I2S_DL_20;
		अवरोध;
	हाल 24:
		अगरace |= ALC5632_DAI_I2S_DL_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set अगरace & srate */
	snd_soc_component_ग_लिखो(component, ALC5632_DAI_CONTROL, अगरace);
	rate = params_rate(params);
	coeff = get_coeff(component, rate);
	अगर (coeff < 0)
		वापस -EINVAL;

	coeff = coeff_भाग[coeff].regvalue;
	snd_soc_component_ग_लिखो(component, ALC5632_DAC_CLK_CTRL1, coeff);

	वापस 0;
पूर्ण

अटल पूर्णांक alc5632_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 hp_mute = ALC5632_MISC_HP_DEPOP_MUTE_L
						|ALC5632_MISC_HP_DEPOP_MUTE_R;
	u16 mute_reg = snd_soc_component_पढ़ो(component, ALC5632_MISC_CTRL) & ~hp_mute;

	अगर (mute)
		mute_reg |= hp_mute;

	वापस snd_soc_component_ग_लिखो(component, ALC5632_MISC_CTRL, mute_reg);
पूर्ण

#घोषणा ALC5632_ADD2_POWER_EN (ALC5632_PWR_ADD2_VREF)

#घोषणा ALC5632_ADD3_POWER_EN (ALC5632_PWR_ADD3_MIC1_BOOST_AD)

#घोषणा ALC5632_ADD1_POWER_EN \
		(ALC5632_PWR_ADD1_DAC_REF \
		| ALC5632_PWR_ADD1_SOFTGEN_EN \
		| ALC5632_PWR_ADD1_HP_OUT_AMP \
		| ALC5632_PWR_ADD1_HP_OUT_ENH_AMP \
		| ALC5632_PWR_ADD1_MAIN_BIAS)

अटल व्योम enable_घातer_depop(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_PWR_ADD1_SOFTGEN_EN,
				ALC5632_PWR_ADD1_SOFTGEN_EN);

	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD3,
				ALC5632_ADD3_POWER_EN,
				ALC5632_ADD3_POWER_EN);

	snd_soc_component_update_bits(component, ALC5632_MISC_CTRL,
				ALC5632_MISC_HP_DEPOP_MODE2_EN,
				ALC5632_MISC_HP_DEPOP_MODE2_EN);

	/* "normal" mode: 0 @ 26 */
	/* set all PR0-7 mixers to 0 */
	snd_soc_component_update_bits(component, ALC5632_PWR_DOWN_CTRL_STATUS,
				ALC5632_PWR_DOWN_CTRL_STATUS_MASK,
				0);

	msleep(500);

	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_ADD2_POWER_EN,
				ALC5632_ADD2_POWER_EN);

	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_ADD1_POWER_EN,
				ALC5632_ADD1_POWER_EN);

	/* disable HP Depop2 */
	snd_soc_component_update_bits(component, ALC5632_MISC_CTRL,
				ALC5632_MISC_HP_DEPOP_MODE2_EN,
				0);

पूर्ण

अटल पूर्णांक alc5632_set_bias_level(काष्ठा snd_soc_component *component,
				      क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		enable_घातer_depop(component);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_PWR_MANAG_ADD1_MASK,
				ALC5632_PWR_ADD1_MAIN_BIAS);
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_MANAG_ADD2_MASK,
				ALC5632_PWR_ADD2_VREF);
		/* "normal" mode: 0 @ 26 */
		snd_soc_component_update_bits(component, ALC5632_PWR_DOWN_CTRL_STATUS,
				ALC5632_PWR_DOWN_CTRL_STATUS_MASK,
				0xffff ^ (ALC5632_PWR_VREF_PR3
				| ALC5632_PWR_VREF_PR2));
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_MANAG_ADD2_MASK, 0);
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD3,
				ALC5632_PWR_MANAG_ADD3_MASK, 0);
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_PWR_MANAG_ADD1_MASK, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ALC5632_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE \
			| SNDRV_PCM_FMTBIT_S24_LE \
			| SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops alc5632_dai_ops = अणु
		.hw_params = alc5632_pcm_hw_params,
		.mute_stream = alc5632_mute,
		.set_fmt = alc5632_set_dai_fmt,
		.set_sysclk = alc5632_set_dai_sysclk,
		.set_pll = alc5632_set_dai_pll,
		.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver alc5632_dai = अणु
	.name = "alc5632-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rate_min =	8000,
		.rate_max =	48000,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = ALC5632_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rate_min =	8000,
		.rate_max =	48000,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = ALC5632_FORMATS,पूर्ण,

	.ops = &alc5632_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक alc5632_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा alc5632_priv *alc5632 = snd_soc_component_get_drvdata(component);

	regcache_sync(alc5632->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा	alc5632_resume	शून्य
#पूर्ण_अगर

अटल पूर्णांक alc5632_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा alc5632_priv *alc5632 = snd_soc_component_get_drvdata(component);

	चयन (alc5632->id) अणु
	हाल 0x5c:
		snd_soc_add_component_controls(component, alc5632_vol_snd_controls,
			ARRAY_SIZE(alc5632_vol_snd_controls));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_device_alc5632 = अणु
	.probe			= alc5632_probe,
	.resume			= alc5632_resume,
	.set_bias_level		= alc5632_set_bias_level,
	.controls		= alc5632_snd_controls,
	.num_controls		= ARRAY_SIZE(alc5632_snd_controls),
	.dapm_widमाला_लो		= alc5632_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(alc5632_dapm_widमाला_लो),
	.dapm_routes		= alc5632_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(alc5632_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config alc5632_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = ALC5632_MAX_REGISTER,
	.reg_शेषs = alc5632_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(alc5632_reg_शेषs),
	.अस्थिर_reg = alc5632_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * alc5632 2 wire address is determined by A1 pin
 * state during घातerup.
 *    low  = 0x1a
 *    high = 0x1b
 */
अटल पूर्णांक alc5632_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा alc5632_priv *alc5632;
	पूर्णांक ret, ret1, ret2;
	अचिन्हित पूर्णांक vid1, vid2;

	alc5632 = devm_kzalloc(&client->dev,
			 माप(काष्ठा alc5632_priv), GFP_KERNEL);
	अगर (alc5632 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(client, alc5632);

	alc5632->regmap = devm_regmap_init_i2c(client, &alc5632_regmap);
	अगर (IS_ERR(alc5632->regmap)) अणु
		ret = PTR_ERR(alc5632->regmap);
		dev_err(&client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret1 = regmap_पढ़ो(alc5632->regmap, ALC5632_VENDOR_ID1, &vid1);
	ret2 = regmap_पढ़ो(alc5632->regmap, ALC5632_VENDOR_ID2, &vid2);
	अगर (ret1 != 0 || ret2 != 0) अणु
		dev_err(&client->dev,
		"Failed to read chip ID: ret1=%d, ret2=%d\n", ret1, ret2);
		वापस -EIO;
	पूर्ण

	vid2 >>= 8;

	अगर ((vid1 != 0x10EC) || (vid2 != id->driver_data)) अणु
		dev_err(&client->dev,
		"Device is not a ALC5632: VID1=0x%x, VID2=0x%x\n", vid1, vid2);
		वापस -EINVAL;
	पूर्ण

	ret = alc5632_reset(alc5632->regmap);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	alc5632->id = vid2;
	चयन (alc5632->id) अणु
	हाल 0x5c:
		alc5632_dai.name = "alc5632-hifi";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
		&soc_component_device_alc5632, &alc5632_dai, 1);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to register component: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id alc5632_i2c_table[] = अणु
	अणु"alc5632", 0x5cपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, alc5632_i2c_table);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id alc5632_of_match[] = अणु
	अणु .compatible = "realtek,alc5632", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, alc5632_of_match);
#पूर्ण_अगर

/* i2c codec control layer */
अटल काष्ठा i2c_driver alc5632_i2c_driver = अणु
	.driver = अणु
		.name = "alc5632",
		.of_match_table = of_match_ptr(alc5632_of_match),
	पूर्ण,
	.probe = alc5632_i2c_probe,
	.id_table = alc5632_i2c_table,
पूर्ण;

module_i2c_driver(alc5632_i2c_driver);

MODULE_DESCRIPTION("ASoC ALC5632 driver");
MODULE_AUTHOR("Leon Romanovsky <leon@leon.nu>");
MODULE_LICENSE("GPL");
