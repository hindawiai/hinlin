<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * alc5623.c  --  alc562[123] ALSA Soc Audio driver
 *
 * Copyright 2008 Realtek Microelectronics
 * Author: flove <flove@realtek.com> Ethan <eku@marvell.com>
 *
 * Copyright 2010 Arnaud Patard <arnaud.patard@rtp-net.org>
 *
 * Based on WM8753.c
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/alc5623.h>

#समावेश "alc5623.h"

अटल पूर्णांक caps_अक्षरge = 2000;
module_param(caps_अक्षरge, पूर्णांक, 0);
MODULE_PARM_DESC(caps_अक्षरge, "ALC5623 cap charge time (msecs)");

/* codec निजी data */
काष्ठा alc5623_priv अणु
	काष्ठा regmap *regmap;
	u8 id;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक add_ctrl;
	अचिन्हित पूर्णांक jack_det_ctrl;
पूर्ण;

अटल अंतरभूत पूर्णांक alc5623_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, ALC5623_RESET, 0);
पूर्ण

अटल पूर्णांक amp_mixer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	/* to घातer-on/off class-d amp generators/speaker */
	/* need to ग_लिखो to 'index-46h' रेजिस्टर :        */
	/* so ग_लिखो index num (here 0x46) to reg 0x6a     */
	/* and then 0xffff/0 to reg 0x6c                  */
	snd_soc_component_ग_लिखो(component, ALC5623_HID_CTRL_INDEX, 0x46);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_ग_लिखो(component, ALC5623_HID_CTRL_DATA, 0xFFFF);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, ALC5623_HID_CTRL_DATA, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ALC5623 Controls
 */

अटल स्थिर DECLARE_TLV_DB_SCALE(vol_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_rec_tlv, -1650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(boost_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(2000, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(3000, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(dig_tlv, 0, 600, 0);

अटल स्थिर काष्ठा snd_kcontrol_new alc5621_vol_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Speaker Playback Volume",
			ALC5623_SPK_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Speaker Playback Switch",
			ALC5623_SPK_OUT_VOL, 15, 7, 1, 1),
	SOC_DOUBLE_TLV("Headphone Playback Volume",
			ALC5623_HP_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Headphone Playback Switch",
			ALC5623_HP_OUT_VOL, 15, 7, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5622_vol_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Speaker Playback Volume",
			ALC5623_SPK_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Speaker Playback Switch",
			ALC5623_SPK_OUT_VOL, 15, 7, 1, 1),
	SOC_DOUBLE_TLV("Line Playback Volume",
			ALC5623_HP_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Line Playback Switch",
			ALC5623_HP_OUT_VOL, 15, 7, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5623_vol_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Line Playback Volume",
			ALC5623_SPK_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Line Playback Switch",
			ALC5623_SPK_OUT_VOL, 15, 7, 1, 1),
	SOC_DOUBLE_TLV("Headphone Playback Volume",
			ALC5623_HP_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Headphone Playback Switch",
			ALC5623_HP_OUT_VOL, 15, 7, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5623_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Auxout Playback Volume",
			ALC5623_MONO_AUX_OUT_VOL, 8, 0, 31, 1, hp_tlv),
	SOC_DOUBLE("Auxout Playback Switch",
			ALC5623_MONO_AUX_OUT_VOL, 15, 7, 1, 1),
	SOC_DOUBLE_TLV("PCM Playback Volume",
			ALC5623_STEREO_DAC_VOL, 8, 0, 31, 1, vol_tlv),
	SOC_DOUBLE_TLV("AuxI Capture Volume",
			ALC5623_AUXIN_VOL, 8, 0, 31, 1, vol_tlv),
	SOC_DOUBLE_TLV("LineIn Capture Volume",
			ALC5623_LINE_IN_VOL, 8, 0, 31, 1, vol_tlv),
	SOC_SINGLE_TLV("Mic1 Capture Volume",
			ALC5623_MIC_VOL, 8, 31, 1, vol_tlv),
	SOC_SINGLE_TLV("Mic2 Capture Volume",
			ALC5623_MIC_VOL, 0, 31, 1, vol_tlv),
	SOC_DOUBLE_TLV("Rec Capture Volume",
			ALC5623_ADC_REC_GAIN, 7, 0, 31, 0, adc_rec_tlv),
	SOC_SINGLE_TLV("Mic 1 Boost Volume",
			ALC5623_MIC_CTRL, 10, 2, 0, boost_tlv),
	SOC_SINGLE_TLV("Mic 2 Boost Volume",
			ALC5623_MIC_CTRL, 8, 2, 0, boost_tlv),
	SOC_SINGLE_TLV("Digital Boost Volume",
			ALC5623_ADD_CTRL_REG, 4, 3, 0, dig_tlv),
पूर्ण;

/*
 * DAPM Controls
 */
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_hp_mixer_controls[] = अणु
SOC_DAPM_SINGLE("LI2HP Playback Switch", ALC5623_LINE_IN_VOL, 15, 1, 1),
SOC_DAPM_SINGLE("AUXI2HP Playback Switch", ALC5623_AUXIN_VOL, 15, 1, 1),
SOC_DAPM_SINGLE("MIC12HP Playback Switch", ALC5623_MIC_ROUTING_CTRL, 15, 1, 1),
SOC_DAPM_SINGLE("MIC22HP Playback Switch", ALC5623_MIC_ROUTING_CTRL, 7, 1, 1),
SOC_DAPM_SINGLE("DAC2HP Playback Switch", ALC5623_STEREO_DAC_VOL, 15, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5623_hpl_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ADC2HP_L Playback Switch", ALC5623_ADC_REC_GAIN, 15, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5623_hpr_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ADC2HP_R Playback Switch", ALC5623_ADC_REC_GAIN, 14, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5623_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ADC2MONO_L Playback Switch", ALC5623_ADC_REC_GAIN, 13, 1, 1),
SOC_DAPM_SINGLE("ADC2MONO_R Playback Switch", ALC5623_ADC_REC_GAIN, 12, 1, 1),
SOC_DAPM_SINGLE("LI2MONO Playback Switch", ALC5623_LINE_IN_VOL, 13, 1, 1),
SOC_DAPM_SINGLE("AUXI2MONO Playback Switch", ALC5623_AUXIN_VOL, 13, 1, 1),
SOC_DAPM_SINGLE("MIC12MONO Playback Switch", ALC5623_MIC_ROUTING_CTRL, 13, 1, 1),
SOC_DAPM_SINGLE("MIC22MONO Playback Switch", ALC5623_MIC_ROUTING_CTRL, 5, 1, 1),
SOC_DAPM_SINGLE("DAC2MONO Playback Switch", ALC5623_STEREO_DAC_VOL, 13, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new alc5623_speaker_mixer_controls[] = अणु
SOC_DAPM_SINGLE("LI2SPK Playback Switch", ALC5623_LINE_IN_VOL, 14, 1, 1),
SOC_DAPM_SINGLE("AUXI2SPK Playback Switch", ALC5623_AUXIN_VOL, 14, 1, 1),
SOC_DAPM_SINGLE("MIC12SPK Playback Switch", ALC5623_MIC_ROUTING_CTRL, 14, 1, 1),
SOC_DAPM_SINGLE("MIC22SPK Playback Switch", ALC5623_MIC_ROUTING_CTRL, 6, 1, 1),
SOC_DAPM_SINGLE("DAC2SPK Playback Switch", ALC5623_STEREO_DAC_VOL, 14, 1, 1),
पूर्ण;

/* Left Record Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_captureL_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Mic1 Capture Switch", ALC5623_ADC_REC_MIXER, 14, 1, 1),
SOC_DAPM_SINGLE("Mic2 Capture Switch", ALC5623_ADC_REC_MIXER, 13, 1, 1),
SOC_DAPM_SINGLE("LineInL Capture Switch", ALC5623_ADC_REC_MIXER, 12, 1, 1),
SOC_DAPM_SINGLE("Left AuxI Capture Switch", ALC5623_ADC_REC_MIXER, 11, 1, 1),
SOC_DAPM_SINGLE("HPMixerL Capture Switch", ALC5623_ADC_REC_MIXER, 10, 1, 1),
SOC_DAPM_SINGLE("SPKMixer Capture Switch", ALC5623_ADC_REC_MIXER, 9, 1, 1),
SOC_DAPM_SINGLE("MonoMixer Capture Switch", ALC5623_ADC_REC_MIXER, 8, 1, 1),
पूर्ण;

/* Right Record Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_captureR_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Mic1 Capture Switch", ALC5623_ADC_REC_MIXER, 6, 1, 1),
SOC_DAPM_SINGLE("Mic2 Capture Switch", ALC5623_ADC_REC_MIXER, 5, 1, 1),
SOC_DAPM_SINGLE("LineInR Capture Switch", ALC5623_ADC_REC_MIXER, 4, 1, 1),
SOC_DAPM_SINGLE("Right AuxI Capture Switch", ALC5623_ADC_REC_MIXER, 3, 1, 1),
SOC_DAPM_SINGLE("HPMixerR Capture Switch", ALC5623_ADC_REC_MIXER, 2, 1, 1),
SOC_DAPM_SINGLE("SPKMixer Capture Switch", ALC5623_ADC_REC_MIXER, 1, 1, 1),
SOC_DAPM_SINGLE("MonoMixer Capture Switch", ALC5623_ADC_REC_MIXER, 0, 1, 1),
पूर्ण;

अटल स्थिर अक्षर *alc5623_spk_n_sour_sel[] = अणु
		"RN/-R", "RP/+R", "LN/-R", "Vmid" पूर्ण;
अटल स्थिर अक्षर *alc5623_hpl_out_input_sel[] = अणु
		"Vmid", "HP Left Mix"पूर्ण;
अटल स्थिर अक्षर *alc5623_hpr_out_input_sel[] = अणु
		"Vmid", "HP Right Mix"पूर्ण;
अटल स्थिर अक्षर *alc5623_spkout_input_sel[] = अणु
		"Vmid", "HPOut Mix", "Speaker Mix", "Mono Mix"पूर्ण;
अटल स्थिर अक्षर *alc5623_aux_out_input_sel[] = अणु
		"Vmid", "HPOut Mix", "Speaker Mix", "Mono Mix"पूर्ण;

/* auxout output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5623_aux_out_input_क्रमागत,
			    ALC5623_OUTPUT_MIXER_CTRL, 6,
			    alc5623_aux_out_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_auxout_mux_controls =
SOC_DAPM_ENUM("Route", alc5623_aux_out_input_क्रमागत);

/* speaker output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5623_spkout_input_क्रमागत,
			    ALC5623_OUTPUT_MIXER_CTRL, 10,
			    alc5623_spkout_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_spkout_mux_controls =
SOC_DAPM_ENUM("Route", alc5623_spkout_input_क्रमागत);

/* headphone left output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5623_hpl_out_input_क्रमागत,
			    ALC5623_OUTPUT_MIXER_CTRL, 9,
			    alc5623_hpl_out_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_hpl_out_mux_controls =
SOC_DAPM_ENUM("Route", alc5623_hpl_out_input_क्रमागत);

/* headphone right output mux */
अटल SOC_ENUM_SINGLE_DECL(alc5623_hpr_out_input_क्रमागत,
			    ALC5623_OUTPUT_MIXER_CTRL, 8,
			    alc5623_hpr_out_input_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_hpr_out_mux_controls =
SOC_DAPM_ENUM("Route", alc5623_hpr_out_input_क्रमागत);

/* speaker output N select */
अटल SOC_ENUM_SINGLE_DECL(alc5623_spk_n_sour_क्रमागत,
			    ALC5623_OUTPUT_MIXER_CTRL, 14,
			    alc5623_spk_n_sour_sel);
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_spkoutn_mux_controls =
SOC_DAPM_ENUM("Route", alc5623_spk_n_sour_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget alc5623_dapm_widमाला_लो[] = अणु
/* Muxes */
SND_SOC_DAPM_MUX("AuxOut Mux", SND_SOC_NOPM, 0, 0,
	&alc5623_auxout_mux_controls),
SND_SOC_DAPM_MUX("SpeakerOut Mux", SND_SOC_NOPM, 0, 0,
	&alc5623_spkout_mux_controls),
SND_SOC_DAPM_MUX("Left Headphone Mux", SND_SOC_NOPM, 0, 0,
	&alc5623_hpl_out_mux_controls),
SND_SOC_DAPM_MUX("Right Headphone Mux", SND_SOC_NOPM, 0, 0,
	&alc5623_hpr_out_mux_controls),
SND_SOC_DAPM_MUX("SpeakerOut N Mux", SND_SOC_NOPM, 0, 0,
	&alc5623_spkoutn_mux_controls),

/* output mixers */
SND_SOC_DAPM_MIXER("HP Mix", SND_SOC_NOPM, 0, 0,
	&alc5623_hp_mixer_controls[0],
	ARRAY_SIZE(alc5623_hp_mixer_controls)),
SND_SOC_DAPM_MIXER("HPR Mix", ALC5623_PWR_MANAG_ADD2, 4, 0,
	&alc5623_hpr_mixer_controls[0],
	ARRAY_SIZE(alc5623_hpr_mixer_controls)),
SND_SOC_DAPM_MIXER("HPL Mix", ALC5623_PWR_MANAG_ADD2, 5, 0,
	&alc5623_hpl_mixer_controls[0],
	ARRAY_SIZE(alc5623_hpl_mixer_controls)),
SND_SOC_DAPM_MIXER("HPOut Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Mono Mix", ALC5623_PWR_MANAG_ADD2, 2, 0,
	&alc5623_mono_mixer_controls[0],
	ARRAY_SIZE(alc5623_mono_mixer_controls)),
SND_SOC_DAPM_MIXER("Speaker Mix", ALC5623_PWR_MANAG_ADD2, 3, 0,
	&alc5623_speaker_mixer_controls[0],
	ARRAY_SIZE(alc5623_speaker_mixer_controls)),

/* input mixers */
SND_SOC_DAPM_MIXER("Left Capture Mix", ALC5623_PWR_MANAG_ADD2, 1, 0,
	&alc5623_captureL_mixer_controls[0],
	ARRAY_SIZE(alc5623_captureL_mixer_controls)),
SND_SOC_DAPM_MIXER("Right Capture Mix", ALC5623_PWR_MANAG_ADD2, 0, 0,
	&alc5623_captureR_mixer_controls[0],
	ARRAY_SIZE(alc5623_captureR_mixer_controls)),

SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback",
	ALC5623_PWR_MANAG_ADD2, 9, 0),
SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback",
	ALC5623_PWR_MANAG_ADD2, 8, 0),
SND_SOC_DAPM_MIXER("I2S Mix", ALC5623_PWR_MANAG_ADD1, 15, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("AuxI Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Line Mix", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_ADC("Left ADC", "Left HiFi Capture",
	ALC5623_PWR_MANAG_ADD2, 7, 0),
SND_SOC_DAPM_ADC("Right ADC", "Right HiFi Capture",
	ALC5623_PWR_MANAG_ADD2, 6, 0),
SND_SOC_DAPM_PGA("Left Headphone", ALC5623_PWR_MANAG_ADD3, 10, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Headphone", ALC5623_PWR_MANAG_ADD3, 9, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SpeakerOut", ALC5623_PWR_MANAG_ADD3, 12, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left AuxOut", ALC5623_PWR_MANAG_ADD3, 14, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right AuxOut", ALC5623_PWR_MANAG_ADD3, 13, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left LineIn", ALC5623_PWR_MANAG_ADD3, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right LineIn", ALC5623_PWR_MANAG_ADD3, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left AuxI", ALC5623_PWR_MANAG_ADD3, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right AuxI", ALC5623_PWR_MANAG_ADD3, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC1 PGA", ALC5623_PWR_MANAG_ADD3, 3, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC2 PGA", ALC5623_PWR_MANAG_ADD3, 2, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC1 Pre Amp", ALC5623_PWR_MANAG_ADD3, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MIC2 Pre Amp", ALC5623_PWR_MANAG_ADD3, 0, 0, शून्य, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias1", ALC5623_PWR_MANAG_ADD1, 11, 0),

SND_SOC_DAPM_OUTPUT("AUXOUTL"),
SND_SOC_DAPM_OUTPUT("AUXOUTR"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("HPR"),
SND_SOC_DAPM_OUTPUT("SPKOUT"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
SND_SOC_DAPM_INPUT("LINEINL"),
SND_SOC_DAPM_INPUT("LINEINR"),
SND_SOC_DAPM_INPUT("AUXINL"),
SND_SOC_DAPM_INPUT("AUXINR"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2"),
SND_SOC_DAPM_VMID("Vmid"),
पूर्ण;

अटल स्थिर अक्षर *alc5623_amp_names[] = अणु"AB Amp", "D Amp"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(alc5623_amp_क्रमागत,
			    ALC5623_OUTPUT_MIXER_CTRL, 13,
			    alc5623_amp_names);
अटल स्थिर काष्ठा snd_kcontrol_new alc5623_amp_mux_controls =
	SOC_DAPM_ENUM("Route", alc5623_amp_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget alc5623_dapm_amp_widमाला_लो[] = अणु
SND_SOC_DAPM_PGA_E("D Amp", ALC5623_PWR_MANAG_ADD2, 14, 0, शून्य, 0,
	amp_mixer_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_PGA("AB Amp", ALC5623_PWR_MANAG_ADD2, 15, 0, शून्य, 0),
SND_SOC_DAPM_MUX("AB-D Amp Mux", SND_SOC_NOPM, 0, 0,
	&alc5623_amp_mux_controls),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	/* भव mixer - mixes left & right channels */
	अणु"I2S Mix", शून्य,				"Left DAC"पूर्ण,
	अणु"I2S Mix", शून्य,				"Right DAC"पूर्ण,
	अणु"Line Mix", शून्य,				"Right LineIn"पूर्ण,
	अणु"Line Mix", शून्य,				"Left LineIn"पूर्ण,
	अणु"AuxI Mix", शून्य,				"Left AuxI"पूर्ण,
	अणु"AuxI Mix", शून्य,				"Right AuxI"पूर्ण,
	अणु"AUXOUTL", शून्य,				"Left AuxOut"पूर्ण,
	अणु"AUXOUTR", शून्य,				"Right AuxOut"पूर्ण,

	/* HP mixer */
	अणु"HPL Mix", "ADC2HP_L Playback Switch",		"Left Capture Mix"पूर्ण,
	अणु"HPL Mix", शून्य,				"HP Mix"पूर्ण,
	अणु"HPR Mix", "ADC2HP_R Playback Switch",		"Right Capture Mix"पूर्ण,
	अणु"HPR Mix", शून्य,				"HP Mix"पूर्ण,
	अणु"HP Mix", "LI2HP Playback Switch",		"Line Mix"पूर्ण,
	अणु"HP Mix", "AUXI2HP Playback Switch",		"AuxI Mix"पूर्ण,
	अणु"HP Mix", "MIC12HP Playback Switch",		"MIC1 PGA"पूर्ण,
	अणु"HP Mix", "MIC22HP Playback Switch",		"MIC2 PGA"पूर्ण,
	अणु"HP Mix", "DAC2HP Playback Switch",		"I2S Mix"पूर्ण,

	/* speaker mixer */
	अणु"Speaker Mix", "LI2SPK Playback Switch",	"Line Mix"पूर्ण,
	अणु"Speaker Mix", "AUXI2SPK Playback Switch",	"AuxI Mix"पूर्ण,
	अणु"Speaker Mix", "MIC12SPK Playback Switch",	"MIC1 PGA"पूर्ण,
	अणु"Speaker Mix", "MIC22SPK Playback Switch",	"MIC2 PGA"पूर्ण,
	अणु"Speaker Mix", "DAC2SPK Playback Switch",	"I2S Mix"पूर्ण,

	/* mono mixer */
	अणु"Mono Mix", "ADC2MONO_L Playback Switch",	"Left Capture Mix"पूर्ण,
	अणु"Mono Mix", "ADC2MONO_R Playback Switch",	"Right Capture Mix"पूर्ण,
	अणु"Mono Mix", "LI2MONO Playback Switch",		"Line Mix"पूर्ण,
	अणु"Mono Mix", "AUXI2MONO Playback Switch",	"AuxI Mix"पूर्ण,
	अणु"Mono Mix", "MIC12MONO Playback Switch",	"MIC1 PGA"पूर्ण,
	अणु"Mono Mix", "MIC22MONO Playback Switch",	"MIC2 PGA"पूर्ण,
	अणु"Mono Mix", "DAC2MONO Playback Switch",	"I2S Mix"पूर्ण,

	/* Left record mixer */
	अणु"Left Capture Mix", "LineInL Capture Switch",	"LINEINL"पूर्ण,
	अणु"Left Capture Mix", "Left AuxI Capture Switch", "AUXINL"पूर्ण,
	अणु"Left Capture Mix", "Mic1 Capture Switch",	"MIC1 Pre Amp"पूर्ण,
	अणु"Left Capture Mix", "Mic2 Capture Switch",	"MIC2 Pre Amp"पूर्ण,
	अणु"Left Capture Mix", "HPMixerL Capture Switch", "HPL Mix"पूर्ण,
	अणु"Left Capture Mix", "SPKMixer Capture Switch", "Speaker Mix"पूर्ण,
	अणु"Left Capture Mix", "MonoMixer Capture Switch", "Mono Mix"पूर्ण,

	/*Right record mixer */
	अणु"Right Capture Mix", "LineInR Capture Switch",	"LINEINR"पूर्ण,
	अणु"Right Capture Mix", "Right AuxI Capture Switch",	"AUXINR"पूर्ण,
	अणु"Right Capture Mix", "Mic1 Capture Switch",	"MIC1 Pre Amp"पूर्ण,
	अणु"Right Capture Mix", "Mic2 Capture Switch",	"MIC2 Pre Amp"पूर्ण,
	अणु"Right Capture Mix", "HPMixerR Capture Switch", "HPR Mix"पूर्ण,
	अणु"Right Capture Mix", "SPKMixer Capture Switch", "Speaker Mix"पूर्ण,
	अणु"Right Capture Mix", "MonoMixer Capture Switch", "Mono Mix"पूर्ण,

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
	अणु"Left AuxOut", शून्य,				"AuxOut Mux"पूर्ण,
	अणु"Right AuxOut", शून्य,				"AuxOut Mux"पूर्ण,

	/* input pga */
	अणु"Left LineIn", शून्य,				"LINEINL"पूर्ण,
	अणु"Right LineIn", शून्य,				"LINEINR"पूर्ण,
	अणु"Left AuxI", शून्य,				"AUXINL"पूर्ण,
	अणु"Right AuxI", शून्य,				"AUXINR"पूर्ण,
	अणु"MIC1 Pre Amp", शून्य,				"MIC1"पूर्ण,
	अणु"MIC2 Pre Amp", शून्य,				"MIC2"पूर्ण,
	अणु"MIC1 PGA", शून्य,				"MIC1 Pre Amp"पूर्ण,
	अणु"MIC2 PGA", शून्य,				"MIC2 Pre Amp"पूर्ण,

	/* left ADC */
	अणु"Left ADC", शून्य,				"Left Capture Mix"पूर्ण,

	/* right ADC */
	अणु"Right ADC", शून्य,				"Right Capture Mix"पूर्ण,

	अणु"SpeakerOut N Mux", "RN/-R",			"SpeakerOut"पूर्ण,
	अणु"SpeakerOut N Mux", "RP/+R",			"SpeakerOut"पूर्ण,
	अणु"SpeakerOut N Mux", "LN/-R",			"SpeakerOut"पूर्ण,
	अणु"SpeakerOut N Mux", "Vmid",			"Vmid"पूर्ण,

	अणु"SPKOUT", शून्य,				"SpeakerOut"पूर्ण,
	अणु"SPKOUTN", शून्य,				"SpeakerOut N Mux"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon_spk[] = अणु
	अणु"SpeakerOut", शून्य,				"SpeakerOut Mux"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon_amp_spk[] = अणु
	अणु"AB Amp", शून्य,				"SpeakerOut Mux"पूर्ण,
	अणु"D Amp", शून्य,					"SpeakerOut Mux"पूर्ण,
	अणु"AB-D Amp Mux", "AB Amp",			"AB Amp"पूर्ण,
	अणु"AB-D Amp Mux", "D Amp",			"D Amp"पूर्ण,
	अणु"SpeakerOut", शून्य,				"AB-D Amp Mux"पूर्ण,
पूर्ण;

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 pll_in;
	u32 pll_out;
	u16 regvalue;
पूर्ण;

/* Note : pll code from original alc5623 driver. Not sure of how good it is */
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

अटल स्थिर काष्ठा _pll_भाग codec_slave_pll_भाग[] = अणु

	अणु  1024000,  16384000,  0x3ea0पूर्ण,
	अणु  1411200,  22579200,	0x3ea0पूर्ण,
	अणु  1536000,  24576000,	0x3ea0पूर्ण,
	अणु  2048000,  16384000,  0x1ea0पूर्ण,
	अणु  2822400,  22579200,	0x1ea0पूर्ण,
	अणु  3072000,  24576000,	0x1ea0पूर्ण,

पूर्ण;

अटल पूर्णांक alc5623_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक i;
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक gbl_clk = 0, pll_भाग = 0;
	u16 reg;

	अगर (pll_id < ALC5623_PLL_FR_MCLK || pll_id > ALC5623_PLL_FR_BCK)
		वापस -ENODEV;

	/* Disable PLL घातer */
	snd_soc_component_update_bits(component, ALC5623_PWR_MANAG_ADD2,
				ALC5623_PWR_ADD2_PLL,
				0);

	/* pll is not used in slave mode */
	reg = snd_soc_component_पढ़ो(component, ALC5623_DAI_CONTROL);
	अगर (reg & ALC5623_DAI_SDP_SLAVE_MODE)
		वापस 0;

	अगर (!freq_in || !freq_out)
		वापस 0;

	चयन (pll_id) अणु
	हाल ALC5623_PLL_FR_MCLK:
		क्रम (i = 0; i < ARRAY_SIZE(codec_master_pll_भाग); i++) अणु
			अगर (codec_master_pll_भाग[i].pll_in == freq_in
			   && codec_master_pll_भाग[i].pll_out == freq_out) अणु
				/* PLL source from MCLK */
				pll_भाग  = codec_master_pll_भाग[i].regvalue;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ALC5623_PLL_FR_BCK:
		क्रम (i = 0; i < ARRAY_SIZE(codec_slave_pll_भाग); i++) अणु
			अगर (codec_slave_pll_भाग[i].pll_in == freq_in
			   && codec_slave_pll_भाग[i].pll_out == freq_out) अणु
				/* PLL source from Bitclk */
				gbl_clk = ALC5623_GBL_CLK_PLL_SOUR_SEL_BITCLK;
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

	snd_soc_component_ग_लिखो(component, ALC5623_GLOBAL_CLK_CTRL_REG, gbl_clk);
	snd_soc_component_ग_लिखो(component, ALC5623_PLL_CTRL, pll_भाग);
	snd_soc_component_update_bits(component, ALC5623_PWR_MANAG_ADD2,
				ALC5623_PWR_ADD2_PLL,
				ALC5623_PWR_ADD2_PLL);
	gbl_clk |= ALC5623_GBL_CLK_SYS_SOUR_SEL_PLL;
	snd_soc_component_ग_लिखो(component, ALC5623_GLOBAL_CLK_CTRL_REG, gbl_clk);

	वापस 0;
पूर्ण

काष्ठा _coeff_भाग अणु
	u16 fs;
	u16 regvalue;
पूर्ण;

/* codec hअगरi mclk (after PLL) घड़ी भागider coefficients */
/* values inspired from column BCLK=32Fs of Appendix A table */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	अणु256*8, 0x3a69पूर्ण,
	अणु384*8, 0x3c6bपूर्ण,
	अणु256*4, 0x2a69पूर्ण,
	अणु384*4, 0x2c6bपूर्ण,
	अणु256*2, 0x1a69पूर्ण,
	अणु384*2, 0x1c6bपूर्ण,
	अणु256*1, 0x0a69पूर्ण,
	अणु384*1, 0x0c6bपूर्ण,
पूर्ण;

अटल पूर्णांक get_coeff(काष्ठा snd_soc_component *component, पूर्णांक rate)
अणु
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].fs * rate == alc5623->sysclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Clock after PLL and भागiders
 */
अटल पूर्णांक alc5623_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल  8192000:
	हाल 11289600:
	हाल 12288000:
	हाल 16384000:
	हाल 16934400:
	हाल 18432000:
	हाल 22579200:
	हाल 24576000:
		alc5623->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक alc5623_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace = ALC5623_DAI_SDP_MASTER_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगरace = ALC5623_DAI_SDP_SLAVE_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= ALC5623_DAI_I2S_DF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगरace |= ALC5623_DAI_I2S_DF_RIGHT;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= ALC5623_DAI_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= ALC5623_DAI_I2S_DF_PCM;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= ALC5623_DAI_I2S_DF_PCM | ALC5623_DAI_I2S_PCM_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= ALC5623_DAI_MAIN_I2S_BCLK_POL_CTRL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= ALC5623_DAI_MAIN_I2S_BCLK_POL_CTRL;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_ग_लिखो(component, ALC5623_DAI_CONTROL, अगरace);
पूर्ण

अटल पूर्णांक alc5623_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);
	पूर्णांक coeff, rate;
	u16 अगरace;

	अगरace = snd_soc_component_पढ़ो(component, ALC5623_DAI_CONTROL);
	अगरace &= ~ALC5623_DAI_I2S_DL_MASK;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अगरace |= ALC5623_DAI_I2S_DL_16;
		अवरोध;
	हाल 20:
		अगरace |= ALC5623_DAI_I2S_DL_20;
		अवरोध;
	हाल 24:
		अगरace |= ALC5623_DAI_I2S_DL_24;
		अवरोध;
	हाल 32:
		अगरace |= ALC5623_DAI_I2S_DL_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set अगरace & srate */
	snd_soc_component_ग_लिखो(component, ALC5623_DAI_CONTROL, अगरace);
	rate = params_rate(params);
	coeff = get_coeff(component, rate);
	अगर (coeff < 0)
		वापस -EINVAL;

	coeff = coeff_भाग[coeff].regvalue;
	dev_dbg(component->dev, "%s: sysclk=%d,rate=%d,coeff=0x%04x\n",
		__func__, alc5623->sysclk, rate, coeff);
	snd_soc_component_ग_लिखो(component, ALC5623_STEREO_AD_DA_CLK_CTRL, coeff);

	वापस 0;
पूर्ण

अटल पूर्णांक alc5623_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 hp_mute = ALC5623_MISC_M_DAC_L_INPUT | ALC5623_MISC_M_DAC_R_INPUT;
	u16 mute_reg = snd_soc_component_पढ़ो(component, ALC5623_MISC_CTRL) & ~hp_mute;

	अगर (mute)
		mute_reg |= hp_mute;

	वापस snd_soc_component_ग_लिखो(component, ALC5623_MISC_CTRL, mute_reg);
पूर्ण

#घोषणा ALC5623_ADD2_POWER_EN (ALC5623_PWR_ADD2_VREF \
	| ALC5623_PWR_ADD2_DAC_REF_CIR)

#घोषणा ALC5623_ADD3_POWER_EN (ALC5623_PWR_ADD3_MAIN_BIAS \
	| ALC5623_PWR_ADD3_MIC1_BOOST_AD)

#घोषणा ALC5623_ADD1_POWER_EN \
	(ALC5623_PWR_ADD1_SHORT_CURR_DET_EN | ALC5623_PWR_ADD1_SOFTGEN_EN \
	| ALC5623_PWR_ADD1_DEPOP_BUF_HP | ALC5623_PWR_ADD1_HP_OUT_AMP \
	| ALC5623_PWR_ADD1_HP_OUT_ENH_AMP)

#घोषणा ALC5623_ADD1_POWER_EN_5622 \
	(ALC5623_PWR_ADD1_SHORT_CURR_DET_EN \
	| ALC5623_PWR_ADD1_HP_OUT_AMP)

अटल व्योम enable_घातer_depop(काष्ठा snd_soc_component *component)
अणु
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, ALC5623_PWR_MANAG_ADD1,
				ALC5623_PWR_ADD1_SOFTGEN_EN,
				ALC5623_PWR_ADD1_SOFTGEN_EN);

	snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD3, ALC5623_ADD3_POWER_EN);

	snd_soc_component_update_bits(component, ALC5623_MISC_CTRL,
				ALC5623_MISC_HP_DEPOP_MODE2_EN,
				ALC5623_MISC_HP_DEPOP_MODE2_EN);

	msleep(500);

	snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD2, ALC5623_ADD2_POWER_EN);

	/* aव्योम writing '1' पूर्णांकo 5622 reserved bits */
	अगर (alc5623->id == 0x22)
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD1,
			ALC5623_ADD1_POWER_EN_5622);
	अन्यथा
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD1,
			ALC5623_ADD1_POWER_EN);

	/* disable HP Depop2 */
	snd_soc_component_update_bits(component, ALC5623_MISC_CTRL,
				ALC5623_MISC_HP_DEPOP_MODE2_EN,
				0);

पूर्ण

अटल पूर्णांक alc5623_set_bias_level(काष्ठा snd_soc_component *component,
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
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD2,
				ALC5623_PWR_ADD2_VREF);
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD3,
				ALC5623_PWR_ADD3_MAIN_BIAS);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD2, 0);
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD3, 0);
		snd_soc_component_ग_लिखो(component, ALC5623_PWR_MANAG_ADD1, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ALC5623_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE \
			| SNDRV_PCM_FMTBIT_S24_LE \
			| SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops alc5623_dai_ops = अणु
		.hw_params = alc5623_pcm_hw_params,
		.mute_stream = alc5623_mute,
		.set_fmt = alc5623_set_dai_fmt,
		.set_sysclk = alc5623_set_dai_sysclk,
		.set_pll = alc5623_set_dai_pll,
		.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver alc5623_dai = अणु
	.name = "alc5623-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rate_min =	8000,
		.rate_max =	48000,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = ALC5623_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rate_min =	8000,
		.rate_max =	48000,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = ALC5623_FORMATS,पूर्ण,

	.ops = &alc5623_dai_ops,
पूर्ण;

अटल पूर्णांक alc5623_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(alc5623->regmap, true);

	वापस 0;
पूर्ण

अटल पूर्णांक alc5623_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	/* Sync reg_cache with the hardware */
	regcache_cache_only(alc5623->regmap, false);
	ret = regcache_sync(alc5623->regmap);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to sync register cache: %d\n",
			ret);
		regcache_cache_only(alc5623->regmap, true);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alc5623_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	alc5623_reset(component);

	अगर (alc5623->add_ctrl) अणु
		snd_soc_component_ग_लिखो(component, ALC5623_ADD_CTRL_REG,
				alc5623->add_ctrl);
	पूर्ण

	अगर (alc5623->jack_det_ctrl) अणु
		snd_soc_component_ग_लिखो(component, ALC5623_JACK_DET_CTRL,
				alc5623->jack_det_ctrl);
	पूर्ण

	चयन (alc5623->id) अणु
	हाल 0x21:
		snd_soc_add_component_controls(component, alc5621_vol_snd_controls,
			ARRAY_SIZE(alc5621_vol_snd_controls));
		अवरोध;
	हाल 0x22:
		snd_soc_add_component_controls(component, alc5622_vol_snd_controls,
			ARRAY_SIZE(alc5622_vol_snd_controls));
		अवरोध;
	हाल 0x23:
		snd_soc_add_component_controls(component, alc5623_vol_snd_controls,
			ARRAY_SIZE(alc5623_vol_snd_controls));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_add_component_controls(component, alc5623_snd_controls,
			ARRAY_SIZE(alc5623_snd_controls));

	snd_soc_dapm_new_controls(dapm, alc5623_dapm_widमाला_लो,
					ARRAY_SIZE(alc5623_dapm_widमाला_लो));

	/* set up audio path पूर्णांकerconnects */
	snd_soc_dapm_add_routes(dapm, पूर्णांकercon, ARRAY_SIZE(पूर्णांकercon));

	चयन (alc5623->id) अणु
	हाल 0x21:
	हाल 0x22:
		snd_soc_dapm_new_controls(dapm, alc5623_dapm_amp_widमाला_लो,
					ARRAY_SIZE(alc5623_dapm_amp_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_amp_spk,
					ARRAY_SIZE(पूर्णांकercon_amp_spk));
		अवरोध;
	हाल 0x23:
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_spk,
					ARRAY_SIZE(पूर्णांकercon_spk));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_device_alc5623 = अणु
	.probe			= alc5623_probe,
	.suspend		= alc5623_suspend,
	.resume			= alc5623_resume,
	.set_bias_level		= alc5623_set_bias_level,
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config alc5623_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.reg_stride = 2,

	.max_रेजिस्टर = ALC5623_VENDOR_ID2,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * ALC5623 2 wire address is determined by A1 pin
 * state during घातerup.
 *    low  = 0x1a
 *    high = 0x1b
 */
अटल पूर्णांक alc5623_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा alc5623_platक्रमm_data *pdata;
	काष्ठा alc5623_priv *alc5623;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक vid1, vid2;
	पूर्णांक ret;
	u32 val32;

	alc5623 = devm_kzalloc(&client->dev, माप(काष्ठा alc5623_priv),
			       GFP_KERNEL);
	अगर (alc5623 == शून्य)
		वापस -ENOMEM;

	alc5623->regmap = devm_regmap_init_i2c(client, &alc5623_regmap);
	अगर (IS_ERR(alc5623->regmap)) अणु
		ret = PTR_ERR(alc5623->regmap);
		dev_err(&client->dev, "Failed to initialise I/O: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(alc5623->regmap, ALC5623_VENDOR_ID1, &vid1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to read vendor ID1: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(alc5623->regmap, ALC5623_VENDOR_ID2, &vid2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to read vendor ID2: %d\n", ret);
		वापस ret;
	पूर्ण
	vid2 >>= 8;

	अगर ((vid1 != 0x10ec) || (vid2 != id->driver_data)) अणु
		dev_err(&client->dev, "unknown or wrong codec\n");
		dev_err(&client->dev, "Expected %x:%lx, got %x:%x\n",
				0x10ec, id->driver_data,
				vid1, vid2);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&client->dev, "Found codec id : alc56%02x\n", vid2);

	pdata = client->dev.platक्रमm_data;
	अगर (pdata) अणु
		alc5623->add_ctrl = pdata->add_ctrl;
		alc5623->jack_det_ctrl = pdata->jack_det_ctrl;
	पूर्ण अन्यथा अणु
		अगर (client->dev.of_node) अणु
			np = client->dev.of_node;
			ret = of_property_पढ़ो_u32(np, "add-ctrl", &val32);
			अगर (!ret)
				alc5623->add_ctrl = val32;
			ret = of_property_पढ़ो_u32(np, "jack-det-ctrl", &val32);
			अगर (!ret)
				alc5623->jack_det_ctrl = val32;
		पूर्ण
	पूर्ण

	alc5623->id = vid2;
	चयन (alc5623->id) अणु
	हाल 0x21:
		alc5623_dai.name = "alc5621-hifi";
		अवरोध;
	हाल 0x22:
		alc5623_dai.name = "alc5622-hifi";
		अवरोध;
	हाल 0x23:
		alc5623_dai.name = "alc5623-hifi";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	i2c_set_clientdata(client, alc5623);

	ret =  devm_snd_soc_रेजिस्टर_component(&client->dev,
		&soc_component_device_alc5623, &alc5623_dai, 1);
	अगर (ret != 0)
		dev_err(&client->dev, "Failed to register codec: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id alc5623_i2c_table[] = अणु
	अणु"alc5621", 0x21पूर्ण,
	अणु"alc5622", 0x22पूर्ण,
	अणु"alc5623", 0x23पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, alc5623_i2c_table);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id alc5623_of_match[] = अणु
	अणु .compatible = "realtek,alc5623", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, alc5623_of_match);
#पूर्ण_अगर

/*  i2c codec control layer */
अटल काष्ठा i2c_driver alc5623_i2c_driver = अणु
	.driver = अणु
		.name = "alc562x-codec",
		.of_match_table = of_match_ptr(alc5623_of_match),
	पूर्ण,
	.probe = alc5623_i2c_probe,
	.id_table = alc5623_i2c_table,
पूर्ण;

module_i2c_driver(alc5623_i2c_driver);

MODULE_DESCRIPTION("ASoC alc5621/2/3 driver");
MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>");
MODULE_LICENSE("GPL");
