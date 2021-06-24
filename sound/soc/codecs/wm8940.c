<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8940.c  --  WM8940 ALSA Soc Audio driver
 *
 * Author: Jonathan Cameron <jic23@cam.ac.uk>
 *
 * Based on wm8510.c
 *    Copyright  2006 Wolfson Microelectronics PLC.
 *    Author:  Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * Not currently handled:
 * Notch filter control
 * AUXMode (inverting vs mixer)
 * No means to obtain current gain अगर alc enabled.
 * No use made of gpio
 * Fast VMID disअक्षरge क्रम घातer करोwn
 * Soft Start
 * DLR and ALR Swaps not enabled
 * Digital Sidetone not supported
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8940.h"

काष्ठा wm8940_priv अणु
	अचिन्हित पूर्णांक sysclk;
	काष्ठा regmap *regmap;
पूर्ण;

अटल bool wm8940_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8940_SOFTRESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8940_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8940_SOFTRESET:
	हाल WM8940_POWER1:
	हाल WM8940_POWER2:
	हाल WM8940_POWER3:
	हाल WM8940_IFACE:
	हाल WM8940_COMPANDINGCTL:
	हाल WM8940_CLOCK:
	हाल WM8940_ADDCNTRL:
	हाल WM8940_GPIO:
	हाल WM8940_CTLINT:
	हाल WM8940_DAC:
	हाल WM8940_DACVOL:
	हाल WM8940_ADC:
	हाल WM8940_ADCVOL:
	हाल WM8940_NOTCH1:
	हाल WM8940_NOTCH2:
	हाल WM8940_NOTCH3:
	हाल WM8940_NOTCH4:
	हाल WM8940_NOTCH5:
	हाल WM8940_NOTCH6:
	हाल WM8940_NOTCH7:
	हाल WM8940_NOTCH8:
	हाल WM8940_DACLIM1:
	हाल WM8940_DACLIM2:
	हाल WM8940_ALC1:
	हाल WM8940_ALC2:
	हाल WM8940_ALC3:
	हाल WM8940_NOISEGATE:
	हाल WM8940_PLLN:
	हाल WM8940_PLLK1:
	हाल WM8940_PLLK2:
	हाल WM8940_PLLK3:
	हाल WM8940_ALC4:
	हाल WM8940_INPUTCTL:
	हाल WM8940_PGAGAIN:
	हाल WM8940_ADCBOOST:
	हाल WM8940_OUTPUTCTL:
	हाल WM8940_SPKMIX:
	हाल WM8940_SPKVOL:
	हाल WM8940_MONOMIX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष wm8940_reg_शेषs[] = अणु
	अणु  0x1, 0x0000 पूर्ण, /* Power 1 */
	अणु  0x2, 0x0000 पूर्ण, /* Power 2 */
	अणु  0x3, 0x0000 पूर्ण, /* Power 3 */
	अणु  0x4, 0x0010 पूर्ण, /* Interface Control */
	अणु  0x5, 0x0000 पूर्ण, /* Companding Control */
	अणु  0x6, 0x0140 पूर्ण, /* Clock Control */
	अणु  0x7, 0x0000 पूर्ण, /* Additional Controls */
	अणु  0x8, 0x0000 पूर्ण, /* GPIO Control */
	अणु  0x9, 0x0002 पूर्ण, /* Auto Increment Control */
	अणु  0xa, 0x0000 पूर्ण, /* DAC Control */
	अणु  0xb, 0x00FF पूर्ण, /* DAC Volume */

	अणु  0xe, 0x0100 पूर्ण, /* ADC Control */
	अणु  0xf, 0x00FF पूर्ण, /* ADC Volume */
	अणु 0x10, 0x0000 पूर्ण, /* Notch Filter 1 Control 1 */
	अणु 0x11, 0x0000 पूर्ण, /* Notch Filter 1 Control 2 */
	अणु 0x12, 0x0000 पूर्ण, /* Notch Filter 2 Control 1 */
	अणु 0x13, 0x0000 पूर्ण, /* Notch Filter 2 Control 2 */
	अणु 0x14, 0x0000 पूर्ण, /* Notch Filter 3 Control 1 */
	अणु 0x15, 0x0000 पूर्ण, /* Notch Filter 3 Control 2 */
	अणु 0x16, 0x0000 पूर्ण, /* Notch Filter 4 Control 1 */
	अणु 0x17, 0x0000 पूर्ण, /* Notch Filter 4 Control 2 */
	अणु 0x18, 0x0032 पूर्ण, /* DAC Limit Control 1 */
	अणु 0x19, 0x0000 पूर्ण, /* DAC Limit Control 2 */

	अणु 0x20, 0x0038 पूर्ण, /* ALC Control 1 */
	अणु 0x21, 0x000B पूर्ण, /* ALC Control 2 */
	अणु 0x22, 0x0032 पूर्ण, /* ALC Control 3 */
	अणु 0x23, 0x0000 पूर्ण, /* Noise Gate */
	अणु 0x24, 0x0041 पूर्ण, /* PLLN */
	अणु 0x25, 0x000C पूर्ण, /* PLLK1 */
	अणु 0x26, 0x0093 पूर्ण, /* PLLK2 */
	अणु 0x27, 0x00E9 पूर्ण, /* PLLK3 */

	अणु 0x2a, 0x0030 पूर्ण, /* ALC Control 4 */

	अणु 0x2c, 0x0002 पूर्ण, /* Input Control */
	अणु 0x2d, 0x0050 पूर्ण, /* PGA Gain */

	अणु 0x2f, 0x0002 पूर्ण, /* ADC Boost Control */

	अणु 0x31, 0x0002 पूर्ण, /* Output Control */
	अणु 0x32, 0x0000 पूर्ण, /* Speaker Mixer Control */

	अणु 0x36, 0x0079 पूर्ण, /* Speaker Volume */

	अणु 0x38, 0x0000 पूर्ण, /* Mono Mixer Control */
पूर्ण;

अटल स्थिर अक्षर *wm8940_companding[] = अणु "Off", "NC", "u-law", "A-law" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(wm8940_adc_companding_क्रमागत,
			    WM8940_COMPANDINGCTL, 1, wm8940_companding);
अटल SOC_ENUM_SINGLE_DECL(wm8940_dac_companding_क्रमागत,
			    WM8940_COMPANDINGCTL, 3, wm8940_companding);

अटल स्थिर अक्षर *wm8940_alc_mode_text[] = अणु"ALC", "Limiter"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(wm8940_alc_mode_क्रमागत,
			    WM8940_ALC3, 8, wm8940_alc_mode_text);

अटल स्थिर अक्षर *wm8940_mic_bias_level_text[] = अणु"0.9", "0.65"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(wm8940_mic_bias_level_क्रमागत,
			    WM8940_INPUTCTL, 8, wm8940_mic_bias_level_text);

अटल स्थिर अक्षर *wm8940_filter_mode_text[] = अणु"Audio", "Application"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(wm8940_filter_mode_क्रमागत,
			    WM8940_ADC, 7, wm8940_filter_mode_text);

अटल DECLARE_TLV_DB_SCALE(wm8940_spk_vol_tlv, -5700, 100, 1);
अटल DECLARE_TLV_DB_SCALE(wm8940_att_tlv, -1000, 1000, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_pga_vol_tlv, -1200, 75, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_alc_min_tlv, -1200, 600, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_alc_max_tlv, 675, 600, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_alc_tar_tlv, -2250, 50, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_lim_boost_tlv, 0, 100, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_lim_thresh_tlv, -600, 100, 0);
अटल DECLARE_TLV_DB_SCALE(wm8940_adc_tlv, -12750, 50, 1);
अटल DECLARE_TLV_DB_SCALE(wm8940_capture_boost_vol_tlv, 0, 2000, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8940_snd_controls[] = अणु
	SOC_SINGLE("Digital Loopback Switch", WM8940_COMPANDINGCTL,
		   6, 1, 0),
	SOC_ENUM("DAC Companding", wm8940_dac_companding_क्रमागत),
	SOC_ENUM("ADC Companding", wm8940_adc_companding_क्रमागत),

	SOC_ENUM("ALC Mode", wm8940_alc_mode_क्रमागत),
	SOC_SINGLE("ALC Switch", WM8940_ALC1, 8, 1, 0),
	SOC_SINGLE_TLV("ALC Capture Max Gain", WM8940_ALC1,
		       3, 7, 1, wm8940_alc_max_tlv),
	SOC_SINGLE_TLV("ALC Capture Min Gain", WM8940_ALC1,
		       0, 7, 0, wm8940_alc_min_tlv),
	SOC_SINGLE_TLV("ALC Capture Target", WM8940_ALC2,
		       0, 14, 0, wm8940_alc_tar_tlv),
	SOC_SINGLE("ALC Capture Hold", WM8940_ALC2, 4, 10, 0),
	SOC_SINGLE("ALC Capture Decay", WM8940_ALC3, 4, 10, 0),
	SOC_SINGLE("ALC Capture Attach", WM8940_ALC3, 0, 10, 0),
	SOC_SINGLE("ALC ZC Switch", WM8940_ALC4, 1, 1, 0),
	SOC_SINGLE("ALC Capture Noise Gate Switch", WM8940_NOISEGATE,
		   3, 1, 0),
	SOC_SINGLE("ALC Capture Noise Gate Threshold", WM8940_NOISEGATE,
		   0, 7, 0),

	SOC_SINGLE("DAC Playback Limiter Switch", WM8940_DACLIM1, 8, 1, 0),
	SOC_SINGLE("DAC Playback Limiter Attack", WM8940_DACLIM1, 0, 9, 0),
	SOC_SINGLE("DAC Playback Limiter Decay", WM8940_DACLIM1, 4, 11, 0),
	SOC_SINGLE_TLV("DAC Playback Limiter Threshold", WM8940_DACLIM2,
		       4, 9, 1, wm8940_lim_thresh_tlv),
	SOC_SINGLE_TLV("DAC Playback Limiter Boost", WM8940_DACLIM2,
		       0, 12, 0, wm8940_lim_boost_tlv),

	SOC_SINGLE("Capture PGA ZC Switch", WM8940_PGAGAIN, 7, 1, 0),
	SOC_SINGLE_TLV("Capture PGA Volume", WM8940_PGAGAIN,
		       0, 63, 0, wm8940_pga_vol_tlv),
	SOC_SINGLE_TLV("Digital Playback Volume", WM8940_DACVOL,
		       0, 255, 0, wm8940_adc_tlv),
	SOC_SINGLE_TLV("Digital Capture Volume", WM8940_ADCVOL,
		       0, 255, 0, wm8940_adc_tlv),
	SOC_ENUM("Mic Bias Level", wm8940_mic_bias_level_क्रमागत),
	SOC_SINGLE_TLV("Capture Boost Volue", WM8940_ADCBOOST,
		       8, 1, 0, wm8940_capture_boost_vol_tlv),
	SOC_SINGLE_TLV("Speaker Playback Volume", WM8940_SPKVOL,
		       0, 63, 0, wm8940_spk_vol_tlv),
	SOC_SINGLE("Speaker Playback Switch", WM8940_SPKVOL,  6, 1, 1),

	SOC_SINGLE_TLV("Speaker Mixer Line Bypass Volume", WM8940_SPKVOL,
		       8, 1, 1, wm8940_att_tlv),
	SOC_SINGLE("Speaker Playback ZC Switch", WM8940_SPKVOL, 7, 1, 0),

	SOC_SINGLE("Mono Out Switch", WM8940_MONOMIX, 6, 1, 1),
	SOC_SINGLE_TLV("Mono Mixer Line Bypass Volume", WM8940_MONOMIX,
		       7, 1, 1, wm8940_att_tlv),

	SOC_SINGLE("High Pass Filter Switch", WM8940_ADC, 8, 1, 0),
	SOC_ENUM("High Pass Filter Mode", wm8940_filter_mode_क्रमागत),
	SOC_SINGLE("High Pass Filter Cut Off", WM8940_ADC, 4, 7, 0),
	SOC_SINGLE("ADC Inversion Switch", WM8940_ADC, 0, 1, 0),
	SOC_SINGLE("DAC Inversion Switch", WM8940_DAC, 0, 1, 0),
	SOC_SINGLE("DAC Auto Mute Switch", WM8940_DAC, 2, 1, 0),
	SOC_SINGLE("ZC Timeout Clock Switch", WM8940_ADDCNTRL, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8940_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Line Bypass Switch", WM8940_SPKMIX, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux Playback Switch", WM8940_SPKMIX, 5, 1, 0),
	SOC_DAPM_SINGLE("PCM Playback Switch", WM8940_SPKMIX, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8940_mono_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Line Bypass Switch", WM8940_MONOMIX, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux Playback Switch", WM8940_MONOMIX, 2, 1, 0),
	SOC_DAPM_SINGLE("PCM Playback Switch", WM8940_MONOMIX, 0, 1, 0),
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(wm8940_boost_vol_tlv, -1500, 300, 1);
अटल स्थिर काष्ठा snd_kcontrol_new wm8940_input_boost_controls[] = अणु
	SOC_DAPM_SINGLE("Mic PGA Switch", WM8940_PGAGAIN, 6, 1, 1),
	SOC_DAPM_SINGLE_TLV("Aux Volume", WM8940_ADCBOOST,
			    0, 7, 0, wm8940_boost_vol_tlv),
	SOC_DAPM_SINGLE_TLV("Mic Volume", WM8940_ADCBOOST,
			    4, 7, 0, wm8940_boost_vol_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8940_micpga_controls[] = अणु
	SOC_DAPM_SINGLE("AUX Switch", WM8940_INPUTCTL, 2, 1, 0),
	SOC_DAPM_SINGLE("MICP Switch", WM8940_INPUTCTL, 0, 1, 0),
	SOC_DAPM_SINGLE("MICN Switch", WM8940_INPUTCTL, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8940_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Speaker Mixer", WM8940_POWER3, 2, 0,
			   &wm8940_speaker_mixer_controls[0],
			   ARRAY_SIZE(wm8940_speaker_mixer_controls)),
	SND_SOC_DAPM_MIXER("Mono Mixer", WM8940_POWER3, 3, 0,
			   &wm8940_mono_mixer_controls[0],
			   ARRAY_SIZE(wm8940_mono_mixer_controls)),
	SND_SOC_DAPM_DAC("DAC", "HiFi Playback", WM8940_POWER3, 0, 0),

	SND_SOC_DAPM_PGA("SpkN Out", WM8940_POWER3, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SpkP Out", WM8940_POWER3, 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono Out", WM8940_POWER3, 7, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUTP"),
	SND_SOC_DAPM_OUTPUT("SPKOUTN"),

	SND_SOC_DAPM_PGA("Aux Input", WM8940_POWER1, 6, 0, शून्य, 0),
	SND_SOC_DAPM_ADC("ADC", "HiFi Capture", WM8940_POWER2, 0, 0),
	SND_SOC_DAPM_MIXER("Mic PGA", WM8940_POWER2, 2, 0,
			   &wm8940_micpga_controls[0],
			   ARRAY_SIZE(wm8940_micpga_controls)),
	SND_SOC_DAPM_MIXER("Boost Mixer", WM8940_POWER2, 4, 0,
			   &wm8940_input_boost_controls[0],
			   ARRAY_SIZE(wm8940_input_boost_controls)),
	SND_SOC_DAPM_MICBIAS("Mic Bias", WM8940_POWER1, 4, 0),

	SND_SOC_DAPM_INPUT("MICN"),
	SND_SOC_DAPM_INPUT("MICP"),
	SND_SOC_DAPM_INPUT("AUX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8940_dapm_routes[] = अणु
	/* Mono output mixer */
	अणु"Mono Mixer", "PCM Playback Switch", "DAC"पूर्ण,
	अणु"Mono Mixer", "Aux Playback Switch", "Aux Input"पूर्ण,
	अणु"Mono Mixer", "Line Bypass Switch", "Boost Mixer"पूर्ण,

	/* Speaker output mixer */
	अणु"Speaker Mixer", "PCM Playback Switch", "DAC"पूर्ण,
	अणु"Speaker Mixer", "Aux Playback Switch", "Aux Input"पूर्ण,
	अणु"Speaker Mixer", "Line Bypass Switch", "Boost Mixer"पूर्ण,

	/* Outमाला_दो */
	अणु"Mono Out", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONOOUT", शून्य, "Mono Out"पूर्ण,
	अणु"SpkN Out", शून्य, "Speaker Mixer"पूर्ण,
	अणु"SpkP Out", शून्य, "Speaker Mixer"पूर्ण,
	अणु"SPKOUTN", शून्य, "SpkN Out"पूर्ण,
	अणु"SPKOUTP", शून्य, "SpkP Out"पूर्ण,

	/*  Microphone PGA */
	अणु"Mic PGA", "MICN Switch", "MICN"पूर्ण,
	अणु"Mic PGA", "MICP Switch", "MICP"पूर्ण,
	अणु"Mic PGA", "AUX Switch", "AUX"पूर्ण,

	/* Boost Mixer */
	अणु"Boost Mixer", "Mic PGA Switch", "Mic PGA"पूर्ण,
	अणु"Boost Mixer", "Mic Volume",  "MICP"पूर्ण,
	अणु"Boost Mixer", "Aux Volume", "Aux Input"पूर्ण,

	अणु"ADC", शून्य, "Boost Mixer"पूर्ण,
पूर्ण;

#घोषणा wm8940_reset(c) snd_soc_component_ग_लिखो(c, WM8940_SOFTRESET, 0);

अटल पूर्णांक wm8940_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8940_IFACE) & 0xFE67;
	u16 clk = snd_soc_component_पढ़ो(component, WM8940_CLOCK) & 0x1fe;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		clk |= 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_ग_लिखो(component, WM8940_CLOCK, clk);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= (2 << 3);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= (1 << 3);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= (3 << 3);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= (3 << 3) | (1 << 7);
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= (1 << 7);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= (1 << 8);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= (1 << 8) | (1 << 7);
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8940_IFACE, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8940_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8940_IFACE) & 0xFD9F;
	u16 addcntrl = snd_soc_component_पढ़ो(component, WM8940_ADDCNTRL) & 0xFFF1;
	u16 companding =  snd_soc_component_पढ़ो(component,
						WM8940_COMPANDINGCTL) & 0xFFDF;
	पूर्णांक ret;

	/* LoutR control */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE
	    && params_channels(params) == 2)
		अगरace |= (1 << 9);

	चयन (params_rate(params)) अणु
	हाल 8000:
		addcntrl |= (0x5 << 1);
		अवरोध;
	हाल 11025:
		addcntrl |= (0x4 << 1);
		अवरोध;
	हाल 16000:
		addcntrl |= (0x3 << 1);
		अवरोध;
	हाल 22050:
		addcntrl |= (0x2 << 1);
		अवरोध;
	हाल 32000:
		addcntrl |= (0x1 << 1);
		अवरोध;
	हाल 44100:
	हाल 48000:
		अवरोध;
	पूर्ण
	ret = snd_soc_component_ग_लिखो(component, WM8940_ADDCNTRL, addcntrl);
	अगर (ret)
		जाओ error_ret;

	चयन (params_width(params)) अणु
	हाल 8:
		companding = companding | (1 << 5);
		अवरोध;
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= (1 << 5);
		अवरोध;
	हाल 24:
		अगरace |= (2 << 5);
		अवरोध;
	हाल 32:
		अगरace |= (3 << 5);
		अवरोध;
	पूर्ण
	ret = snd_soc_component_ग_लिखो(component, WM8940_COMPANDINGCTL, companding);
	अगर (ret)
		जाओ error_ret;
	ret = snd_soc_component_ग_लिखो(component, WM8940_IFACE, अगरace);

error_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक wm8940_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8940_DAC) & 0xffbf;

	अगर (mute)
		mute_reg |= 0x40;

	वापस snd_soc_component_ग_लिखो(component, WM8940_DAC, mute_reg);
पूर्ण

अटल पूर्णांक wm8940_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8940_priv *wm8940 = snd_soc_component_get_drvdata(component);
	u16 val;
	u16 pwr_reg = snd_soc_component_पढ़ो(component, WM8940_POWER1) & 0x1F0;
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* ensure bufioen and biasen */
		pwr_reg |= (1 << 2) | (1 << 3);
		/* Enable thermal shutकरोwn */
		val = snd_soc_component_पढ़ो(component, WM8940_OUTPUTCTL);
		ret = snd_soc_component_ग_लिखो(component, WM8940_OUTPUTCTL, val | 0x2);
		अगर (ret)
			अवरोध;
		/* set vmid to 75k */
		ret = snd_soc_component_ग_लिखो(component, WM8940_POWER1, pwr_reg | 0x1);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* ensure bufioen and biasen */
		pwr_reg |= (1 << 2) | (1 << 3);
		ret = snd_soc_component_ग_लिखो(component, WM8940_POWER1, pwr_reg | 0x1);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regcache_sync(wm8940->regmap);
			अगर (ret < 0) अणु
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		/* ensure bufioen and biasen */
		pwr_reg |= (1 << 2) | (1 << 3);
		/* set vmid to 300k क्रम standby */
		ret = snd_soc_component_ग_लिखो(component, WM8940_POWER1, pwr_reg | 0x2);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		ret = snd_soc_component_ग_लिखो(component, WM8940_POWER1, pwr_reg);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा pll_ अणु
	अचिन्हित पूर्णांक pre_scale:2;
	अचिन्हित पूर्णांक n:4;
	अचिन्हित पूर्णांक k;
पूर्ण;

अटल काष्ठा pll_ pll_भाग;

/* The size in bits of the pll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 24) * 10)
अटल व्योम pll_factors(अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक source)
अणु
	अचिन्हित दीर्घ दीर्घ Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;
	/* The left shअगरt ist to aव्योम accuracy loss when right shअगरting */
	Nभाग = target / source;

	अगर (Nभाग > 12) अणु
		source <<= 1;
		/* Multiply by 2 */
		pll_भाग.pre_scale = 0;
		Nभाग = target / source;
	पूर्ण अन्यथा अगर (Nभाग < 3) अणु
		source >>= 2;
		/* Divide by 4 */
		pll_भाग.pre_scale = 3;
		Nभाग = target / source;
	पूर्ण अन्यथा अगर (Nभाग < 6) अणु
		source >>= 1;
		/* भागide by 2 */
		pll_भाग.pre_scale = 2;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग.pre_scale = 1;

	अगर ((Nभाग < 6) || (Nभाग > 12))
		prपूर्णांकk(KERN_WARNING
			"WM8940 N value %d outwith recommended range!d\n",
			Nभाग);

	pll_भाग.n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check अगर we need to round */
	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	K /= 10;

	pll_भाग.k = K;
पूर्ण

/* Untested at the moment */
अटल पूर्णांक wm8940_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	/* Turn off PLL */
	reg = snd_soc_component_पढ़ो(component, WM8940_POWER1);
	snd_soc_component_ग_लिखो(component, WM8940_POWER1, reg & 0x1df);

	अगर (freq_in == 0 || freq_out == 0) अणु
		/* Clock CODEC directly from MCLK */
		reg = snd_soc_component_पढ़ो(component, WM8940_CLOCK);
		snd_soc_component_ग_लिखो(component, WM8940_CLOCK, reg & 0x0ff);
		/* Pll घातer करोwn */
		snd_soc_component_ग_लिखो(component, WM8940_PLLN, (1 << 7));
		वापस 0;
	पूर्ण

	/* Pll is followed by a frequency भागide by 4 */
	pll_factors(freq_out*4, freq_in);
	अगर (pll_भाग.k)
		snd_soc_component_ग_लिखो(component, WM8940_PLLN,
			     (pll_भाग.pre_scale << 4) | pll_भाग.n | (1 << 6));
	अन्यथा /* No factional component */
		snd_soc_component_ग_लिखो(component, WM8940_PLLN,
			     (pll_भाग.pre_scale << 4) | pll_भाग.n);
	snd_soc_component_ग_लिखो(component, WM8940_PLLK1, pll_भाग.k >> 18);
	snd_soc_component_ग_लिखो(component, WM8940_PLLK2, (pll_भाग.k >> 9) & 0x1ff);
	snd_soc_component_ग_लिखो(component, WM8940_PLLK3, pll_भाग.k & 0x1ff);
	/* Enable the PLL */
	reg = snd_soc_component_पढ़ो(component, WM8940_POWER1);
	snd_soc_component_ग_लिखो(component, WM8940_POWER1, reg | 0x020);

	/* Run CODEC from PLL instead of MCLK */
	reg = snd_soc_component_पढ़ो(component, WM8940_CLOCK);
	snd_soc_component_ग_लिखो(component, WM8940_CLOCK, reg | 0x100);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8940_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8940_priv *wm8940 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल 11289600:
	हाल 12000000:
	हाल 12288000:
	हाल 16934400:
	हाल 18432000:
		wm8940->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8940_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;
	पूर्णांक ret = 0;

	चयन (भाग_id) अणु
	हाल WM8940_BCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8940_CLOCK) & 0xFFE3;
		ret = snd_soc_component_ग_लिखो(component, WM8940_CLOCK, reg | (भाग << 2));
		अवरोध;
	हाल WM8940_MCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8940_CLOCK) & 0xFF1F;
		ret = snd_soc_component_ग_लिखो(component, WM8940_CLOCK, reg | (भाग << 5));
		अवरोध;
	हाल WM8940_OPCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8940_GPIO) & 0xFFCF;
		ret = snd_soc_component_ग_लिखो(component, WM8940_GPIO, reg | (भाग << 4));
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा WM8940_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा WM8940_FORMATS (SNDRV_PCM_FMTBIT_S8 |				\
			SNDRV_PCM_FMTBIT_S16_LE |			\
			SNDRV_PCM_FMTBIT_S20_3LE |			\
			SNDRV_PCM_FMTBIT_S24_LE |			\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8940_dai_ops = अणु
	.hw_params = wm8940_i2s_hw_params,
	.set_sysclk = wm8940_set_dai_sysclk,
	.mute_stream = wm8940_mute,
	.set_fmt = wm8940_set_dai_fmt,
	.set_clkभाग = wm8940_set_dai_clkभाग,
	.set_pll = wm8940_set_dai_pll,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8940_dai = अणु
	.name = "wm8940-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8940_RATES,
		.क्रमmats = WM8940_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8940_RATES,
		.क्रमmats = WM8940_FORMATS,
	पूर्ण,
	.ops = &wm8940_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8940_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8940_setup_data *pdata = component->dev->platक्रमm_data;
	पूर्णांक ret;
	u16 reg;

	ret = wm8940_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	ret = snd_soc_component_ग_लिखो(component, WM8940_POWER1, 0x180);
	अगर (ret < 0)
		वापस ret;

	अगर (!pdata)
		dev_warn(component->dev, "No platform data supplied\n");
	अन्यथा अणु
		reg = snd_soc_component_पढ़ो(component, WM8940_OUTPUTCTL);
		ret = snd_soc_component_ग_लिखो(component, WM8940_OUTPUTCTL, reg | pdata->vroi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8940 = अणु
	.probe			= wm8940_probe,
	.set_bias_level		= wm8940_set_bias_level,
	.controls		= wm8940_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8940_snd_controls),
	.dapm_widमाला_लो		= wm8940_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8940_dapm_widमाला_लो),
	.dapm_routes		= wm8940_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8940_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8940_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = WM8940_MONOMIX,
	.reg_शेषs = wm8940_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8940_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.पढ़ोable_reg = wm8940_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = wm8940_अस्थिर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक wm8940_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8940_priv *wm8940;
	पूर्णांक ret;

	wm8940 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8940_priv),
			      GFP_KERNEL);
	अगर (wm8940 == शून्य)
		वापस -ENOMEM;

	wm8940->regmap = devm_regmap_init_i2c(i2c, &wm8940_regmap);
	अगर (IS_ERR(wm8940->regmap))
		वापस PTR_ERR(wm8940->regmap);

	i2c_set_clientdata(i2c, wm8940);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8940, &wm8940_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8940_i2c_id[] = अणु
	अणु "wm8940", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8940_i2c_id);

अटल काष्ठा i2c_driver wm8940_i2c_driver = अणु
	.driver = अणु
		.name = "wm8940",
	पूर्ण,
	.probe =    wm8940_i2c_probe,
	.id_table = wm8940_i2c_id,
पूर्ण;

module_i2c_driver(wm8940_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8940 driver");
MODULE_AUTHOR("Jonathan Cameron");
MODULE_LICENSE("GPL");
