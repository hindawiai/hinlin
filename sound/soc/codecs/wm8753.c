<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8753.c  --  WM8753 ALSA Soc Audio driver
 *
 * Copyright 2003-11 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * Notes:
 *  The WM8753 is a low घातer, high quality stereo codec with पूर्णांकegrated PCM
 *  codec deचिन्हित क्रम portable digital telephony applications.
 *
 * Dual DAI:-
 *
 * This driver support 2 DAI PCM's. This makes the शेष PCM available क्रम
 * HiFi audio (e.g. MP3, ogg) playback/capture and the other PCM available क्रम
 * voice.
 *
 * Please note that the voice PCM can be connected directly to a Bluetooth
 * codec or GSM modem and thus cannot be पढ़ो or written to, although it is
 * available to be configured with snd_hw_params(), etc and kcontrols in the
 * normal alsa manner.
 *
 * Fast DAI चयनing:-
 *
 * The driver can now fast चयन between the DAI configurations via a
 * an alsa kcontrol. This allows the PCM to reमुख्य खोलो.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "wm8753.h"

अटल पूर्णांक caps_अक्षरge = 2000;
module_param(caps_अक्षरge, पूर्णांक, 0);
MODULE_PARM_DESC(caps_अक्षरge, "WM8753 cap charge time (msecs)");

अटल पूर्णांक wm8753_hअगरi_ग_लिखो_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt);
अटल पूर्णांक wm8753_voice_ग_लिखो_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt);

/*
 * wm8753 रेजिस्टर cache
 * We can't पढ़ो the WM8753 रेजिस्टर space when we
 * are using 2 wire क्रम device control, so we cache them instead.
 */
अटल स्थिर काष्ठा reg_शेष wm8753_reg_शेषs[] = अणु
	अणु 0x00, 0x0000 पूर्ण,
	अणु 0x01, 0x0008 पूर्ण,
	अणु 0x02, 0x0000 पूर्ण,
	अणु 0x03, 0x000a पूर्ण,
	अणु 0x04, 0x000a पूर्ण,
	अणु 0x05, 0x0033 पूर्ण,
	अणु 0x06, 0x0000 पूर्ण,
	अणु 0x07, 0x0007 पूर्ण,
	अणु 0x08, 0x00ff पूर्ण,
	अणु 0x09, 0x00ff पूर्ण,
	अणु 0x0a, 0x000f पूर्ण,
	अणु 0x0b, 0x000f पूर्ण,
	अणु 0x0c, 0x007b पूर्ण,
	अणु 0x0d, 0x0000 पूर्ण,
	अणु 0x0e, 0x0032 पूर्ण,
	अणु 0x0f, 0x0000 पूर्ण,
	अणु 0x10, 0x00c3 पूर्ण,
	अणु 0x11, 0x00c3 पूर्ण,
	अणु 0x12, 0x00c0 पूर्ण,
	अणु 0x13, 0x0000 पूर्ण,
	अणु 0x14, 0x0000 पूर्ण,
	अणु 0x15, 0x0000 पूर्ण,
	अणु 0x16, 0x0000 पूर्ण,
	अणु 0x17, 0x0000 पूर्ण,
	अणु 0x18, 0x0000 पूर्ण,
	अणु 0x19, 0x0000 पूर्ण,
	अणु 0x1a, 0x0000 पूर्ण,
	अणु 0x1b, 0x0000 पूर्ण,
	अणु 0x1c, 0x0000 पूर्ण,
	अणु 0x1d, 0x0000 पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x1f, 0x0000 पूर्ण,
	अणु 0x20, 0x0055 पूर्ण,
	अणु 0x21, 0x0005 पूर्ण,
	अणु 0x22, 0x0050 पूर्ण,
	अणु 0x23, 0x0055 पूर्ण,
	अणु 0x24, 0x0050 पूर्ण,
	अणु 0x25, 0x0055 पूर्ण,
	अणु 0x26, 0x0050 पूर्ण,
	अणु 0x27, 0x0055 पूर्ण,
	अणु 0x28, 0x0079 पूर्ण,
	अणु 0x29, 0x0079 पूर्ण,
	अणु 0x2a, 0x0079 पूर्ण,
	अणु 0x2b, 0x0079 पूर्ण,
	अणु 0x2c, 0x0079 पूर्ण,
	अणु 0x2d, 0x0000 पूर्ण,
	अणु 0x2e, 0x0000 पूर्ण,
	अणु 0x2f, 0x0000 पूर्ण,
	अणु 0x30, 0x0000 पूर्ण,
	अणु 0x31, 0x0097 पूर्ण,
	अणु 0x32, 0x0097 पूर्ण,
	अणु 0x33, 0x0000 पूर्ण,
	अणु 0x34, 0x0004 पूर्ण,
	अणु 0x35, 0x0000 पूर्ण,
	अणु 0x36, 0x0083 पूर्ण,
	अणु 0x37, 0x0024 पूर्ण,
	अणु 0x38, 0x01ba पूर्ण,
	अणु 0x39, 0x0000 पूर्ण,
	अणु 0x3a, 0x0083 पूर्ण,
	अणु 0x3b, 0x0024 पूर्ण,
	अणु 0x3c, 0x01ba पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x0000 पूर्ण,
	अणु 0x3f, 0x0000 पूर्ण,
पूर्ण;

अटल bool wm8753_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == WM8753_RESET;
पूर्ण

/* codec निजी data */
काष्ठा wm8753_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक pcmclk;

	अचिन्हित पूर्णांक voice_fmt;
	अचिन्हित पूर्णांक hअगरi_fmt;

	पूर्णांक dai_func;
	काष्ठा delayed_work अक्षरge_work;
पूर्ण;

#घोषणा wm8753_reset(c) snd_soc_component_ग_लिखो(c, WM8753_RESET, 0)

/*
 * WM8753 Controls
 */
अटल स्थिर अक्षर *wm8753_base[] = अणु"Linear Control", "Adaptive Boost"पूर्ण;
अटल स्थिर अक्षर *wm8753_base_filter[] =
	अणु"130Hz @ 48kHz", "200Hz @ 48kHz", "100Hz @ 16kHz", "400Hz @ 48kHz",
	"100Hz @ 8kHz", "200Hz @ 8kHz"पूर्ण;
अटल स्थिर अक्षर *wm8753_treble[] = अणु"8kHz", "4kHz"पूर्ण;
अटल स्थिर अक्षर *wm8753_alc_func[] = अणु"Off", "Right", "Left", "Stereo"पूर्ण;
अटल स्थिर अक्षर *wm8753_ng_type[] = अणु"Constant PGA Gain", "Mute ADC Output"पूर्ण;
अटल स्थिर अक्षर *wm8753_3d_func[] = अणु"Capture", "Playback"पूर्ण;
अटल स्थिर अक्षर *wm8753_3d_uc[] = अणु"2.2kHz", "1.5kHz"पूर्ण;
अटल स्थिर अक्षर *wm8753_3d_lc[] = अणु"200Hz", "500Hz"पूर्ण;
अटल स्थिर अक्षर *wm8753_deemp[] = अणु"None", "32kHz", "44.1kHz", "48kHz"पूर्ण;
अटल स्थिर अक्षर *wm8753_mono_mix[] = अणु"Stereo", "Left", "Right", "Mono"पूर्ण;
अटल स्थिर अक्षर *wm8753_dac_phase[] = अणु"Non Inverted", "Inverted"पूर्ण;
अटल स्थिर अक्षर *wm8753_line_mix[] = अणु"Line 1 + 2", "Line 1 - 2",
	"Line 1", "Line 2"पूर्ण;
अटल स्थिर अक्षर *wm8753_mono_mux[] = अणु"Line Mix", "Rx Mix"पूर्ण;
अटल स्थिर अक्षर *wm8753_right_mux[] = अणु"Line 2", "Rx Mix"पूर्ण;
अटल स्थिर अक्षर *wm8753_left_mux[] = अणु"Line 1", "Rx Mix"पूर्ण;
अटल स्थिर अक्षर *wm8753_rxmsel[] = अणु"RXP - RXN", "RXP + RXN", "RXP", "RXN"पूर्ण;
अटल स्थिर अक्षर *wm8753_sidetone_mux[] = अणु"Left PGA", "Mic 1", "Mic 2",
	"Right PGA"पूर्ण;
अटल स्थिर अक्षर *wm8753_mono2_src[] = अणु"Inverted Mono 1", "Left", "Right",
	"Left + Right"पूर्ण;
अटल स्थिर अक्षर *wm8753_out3[] = अणु"VREF", "ROUT2", "Left + Right"पूर्ण;
अटल स्थिर अक्षर *wm8753_out4[] = अणु"VREF", "Capture ST", "LOUT2"पूर्ण;
अटल स्थिर अक्षर *wm8753_radcsel[] = अणु"PGA", "Line or RXP-RXN", "Sidetone"पूर्ण;
अटल स्थिर अक्षर *wm8753_ladcsel[] = अणु"PGA", "Line or RXP-RXN", "Line"पूर्ण;
अटल स्थिर अक्षर *wm8753_mono_adc[] = अणु"Stereo", "Analogue Mix Left",
	"Analogue Mix Right", "Digital Mono Mix"पूर्ण;
अटल स्थिर अक्षर *wm8753_adc_hp[] = अणु"3.4Hz @ 48kHz", "82Hz @ 16k",
	"82Hz @ 8kHz", "170Hz @ 8kHz"पूर्ण;
अटल स्थिर अक्षर *wm8753_adc_filter[] = अणु"HiFi", "Voice"पूर्ण;
अटल स्थिर अक्षर *wm8753_mic_sel[] = अणु"Mic 1", "Mic 2", "Mic 3"पूर्ण;
अटल स्थिर अक्षर *wm8753_dai_mode[] = अणु"DAI 0", "DAI 1", "DAI 2", "DAI 3"पूर्ण;
अटल स्थिर अक्षर *wm8753_dat_sel[] = अणु"Stereo", "Left ADC", "Right ADC",
	"Channel Swap"पूर्ण;
अटल स्थिर अक्षर *wm8753_rout2_phase[] = अणु"Non Inverted", "Inverted"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8753_क्रमागत[] = अणु
SOC_ENUM_SINGLE(WM8753_BASS, 7, 2, wm8753_base),
SOC_ENUM_SINGLE(WM8753_BASS, 4, 6, wm8753_base_filter),
SOC_ENUM_SINGLE(WM8753_TREBLE, 6, 2, wm8753_treble),
SOC_ENUM_SINGLE(WM8753_ALC1, 7, 4, wm8753_alc_func),
SOC_ENUM_SINGLE(WM8753_NGATE, 1, 2, wm8753_ng_type),
SOC_ENUM_SINGLE(WM8753_3D, 7, 2, wm8753_3d_func),
SOC_ENUM_SINGLE(WM8753_3D, 6, 2, wm8753_3d_uc),
SOC_ENUM_SINGLE(WM8753_3D, 5, 2, wm8753_3d_lc),
SOC_ENUM_SINGLE(WM8753_DAC, 1, 4, wm8753_deemp),
SOC_ENUM_SINGLE(WM8753_DAC, 4, 4, wm8753_mono_mix),
SOC_ENUM_SINGLE(WM8753_DAC, 6, 2, wm8753_dac_phase),
SOC_ENUM_SINGLE(WM8753_INCTL1, 3, 4, wm8753_line_mix),
SOC_ENUM_SINGLE(WM8753_INCTL1, 2, 2, wm8753_mono_mux),
SOC_ENUM_SINGLE(WM8753_INCTL1, 1, 2, wm8753_right_mux),
SOC_ENUM_SINGLE(WM8753_INCTL1, 0, 2, wm8753_left_mux),
SOC_ENUM_SINGLE(WM8753_INCTL2, 6, 4, wm8753_rxmsel),
SOC_ENUM_SINGLE(WM8753_INCTL2, 4, 4, wm8753_sidetone_mux),
SOC_ENUM_SINGLE(WM8753_OUTCTL, 7, 4, wm8753_mono2_src),
SOC_ENUM_SINGLE(WM8753_OUTCTL, 0, 3, wm8753_out3),
SOC_ENUM_SINGLE(WM8753_ADCTL2, 7, 3, wm8753_out4),
SOC_ENUM_SINGLE(WM8753_ADCIN, 2, 3, wm8753_radcsel),
SOC_ENUM_SINGLE(WM8753_ADCIN, 0, 3, wm8753_ladcsel),
SOC_ENUM_SINGLE(WM8753_ADCIN, 4, 4, wm8753_mono_adc),
SOC_ENUM_SINGLE(WM8753_ADC, 2, 4, wm8753_adc_hp),
SOC_ENUM_SINGLE(WM8753_ADC, 4, 2, wm8753_adc_filter),
SOC_ENUM_SINGLE(WM8753_MICBIAS, 6, 3, wm8753_mic_sel),
SOC_ENUM_SINGLE(WM8753_IOCTL, 2, 4, wm8753_dai_mode),
SOC_ENUM_SINGLE(WM8753_ADC, 7, 4, wm8753_dat_sel),
SOC_ENUM_SINGLE(WM8753_OUTCTL, 2, 2, wm8753_rout2_phase),
पूर्ण;


अटल पूर्णांक wm8753_get_dai(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8753->dai_func;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8753_set_dai(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	u16 ioctl;

	अगर (wm8753->dai_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	अगर (snd_soc_component_active(component))
		वापस -EBUSY;

	ioctl = snd_soc_component_पढ़ो(component, WM8753_IOCTL);

	wm8753->dai_func = ucontrol->value.क्रमागतerated.item[0];

	अगर (((ioctl >> 2) & 0x3) == wm8753->dai_func)
		वापस 1;

	ioctl = (ioctl & 0x1f3) | (wm8753->dai_func << 2);
	snd_soc_component_ग_लिखो(component, WM8753_IOCTL, ioctl);


	wm8753_hअगरi_ग_लिखो_dai_fmt(component, wm8753->hअगरi_fmt);
	wm8753_voice_ग_लिखो_dai_fmt(component, wm8753->voice_fmt);

	वापस 1;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(rec_mix_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_preamp_tlv, 1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -9750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_RANGE(out_tlv,
	/* 0000000 - 0101111 = "Analogue mute" */
	0, 48, TLV_DB_SCALE_ITEM(-25500, 0, 0),
	48, 127, TLV_DB_SCALE_ITEM(-7300, 100, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(mix_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(voice_mix_tlv, -1200, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, -1725, 75, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8753_snd_controls[] = अणु
SOC_SINGLE("Hi-Fi DAC Left/Right channel Swap", WM8753_HIFI, 5, 1, 0),
SOC_DOUBLE_R_TLV("PCM Volume", WM8753_LDAC, WM8753_RDAC, 0, 255, 0, dac_tlv),

SOC_DOUBLE_R_TLV("ADC Capture Volume", WM8753_LADC, WM8753_RADC, 0, 255, 0,
		 adc_tlv),

SOC_DOUBLE_R_TLV("Headphone Playback Volume", WM8753_LOUT1V, WM8753_ROUT1V,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_R_TLV("Speaker Playback Volume", WM8753_LOUT2V, WM8753_ROUT2V, 0,
		 127, 0, out_tlv),

SOC_SINGLE_TLV("Mono Playback Volume", WM8753_MOUTV, 0, 127, 0, out_tlv),

SOC_DOUBLE_R_TLV("Bypass Playback Volume", WM8753_LOUTM1, WM8753_ROUTM1, 4, 7,
		 1, mix_tlv),
SOC_DOUBLE_R_TLV("Sidetone Playback Volume", WM8753_LOUTM2, WM8753_ROUTM2, 4,
		 7, 1, mix_tlv),
SOC_DOUBLE_R_TLV("Voice Playback Volume", WM8753_LOUTM2, WM8753_ROUTM2, 0, 7,
		 1, voice_mix_tlv),

SOC_DOUBLE_R("Headphone Playback ZC Switch", WM8753_LOUT1V, WM8753_ROUT1V, 7,
	     1, 0),
SOC_DOUBLE_R("Speaker Playback ZC Switch", WM8753_LOUT2V, WM8753_ROUT2V, 7,
	     1, 0),

SOC_SINGLE_TLV("Mono Bypass Playback Volume", WM8753_MOUTM1, 4, 7, 1, mix_tlv),
SOC_SINGLE_TLV("Mono Sidetone Playback Volume", WM8753_MOUTM2, 4, 7, 1,
	       mix_tlv),
SOC_SINGLE_TLV("Mono Voice Playback Volume", WM8753_MOUTM2, 0, 7, 1,
	       voice_mix_tlv),
SOC_SINGLE("Mono Playback ZC Switch", WM8753_MOUTV, 7, 1, 0),

SOC_ENUM("Bass Boost", wm8753_क्रमागत[0]),
SOC_ENUM("Bass Filter", wm8753_क्रमागत[1]),
SOC_SINGLE("Bass Volume", WM8753_BASS, 0, 15, 1),

SOC_SINGLE("Treble Volume", WM8753_TREBLE, 0, 15, 1),
SOC_ENUM("Treble Cut-off", wm8753_क्रमागत[2]),

SOC_DOUBLE_TLV("Sidetone Capture Volume", WM8753_RECMIX1, 0, 4, 7, 1,
	       rec_mix_tlv),
SOC_SINGLE_TLV("Voice Sidetone Capture Volume", WM8753_RECMIX2, 0, 7, 1,
	       rec_mix_tlv),

SOC_DOUBLE_R_TLV("Capture Volume", WM8753_LINVOL, WM8753_RINVOL, 0, 63, 0,
		 pga_tlv),
SOC_DOUBLE_R("Capture ZC Switch", WM8753_LINVOL, WM8753_RINVOL, 6, 1, 0),
SOC_DOUBLE_R("Capture Switch", WM8753_LINVOL, WM8753_RINVOL, 7, 1, 1),

SOC_ENUM("Capture Filter Select", wm8753_क्रमागत[23]),
SOC_ENUM("Capture Filter Cut-off", wm8753_क्रमागत[24]),
SOC_SINGLE("Capture Filter Switch", WM8753_ADC, 0, 1, 1),

SOC_SINGLE("ALC Capture Target Volume", WM8753_ALC1, 0, 7, 0),
SOC_SINGLE("ALC Capture Max Volume", WM8753_ALC1, 4, 7, 0),
SOC_ENUM("ALC Capture Function", wm8753_क्रमागत[3]),
SOC_SINGLE("ALC Capture ZC Switch", WM8753_ALC2, 8, 1, 0),
SOC_SINGLE("ALC Capture Hold Time", WM8753_ALC2, 0, 15, 1),
SOC_SINGLE("ALC Capture Decay Time", WM8753_ALC3, 4, 15, 1),
SOC_SINGLE("ALC Capture Attack Time", WM8753_ALC3, 0, 15, 0),
SOC_SINGLE("ALC Capture NG Threshold", WM8753_NGATE, 3, 31, 0),
SOC_ENUM("ALC Capture NG Type", wm8753_क्रमागत[4]),
SOC_SINGLE("ALC Capture NG Switch", WM8753_NGATE, 0, 1, 0),

SOC_ENUM("3D Function", wm8753_क्रमागत[5]),
SOC_ENUM("3D Upper Cut-off", wm8753_क्रमागत[6]),
SOC_ENUM("3D Lower Cut-off", wm8753_क्रमागत[7]),
SOC_SINGLE("3D Volume", WM8753_3D, 1, 15, 0),
SOC_SINGLE("3D Switch", WM8753_3D, 0, 1, 0),

SOC_SINGLE("Capture 6dB Attenuate", WM8753_ADCTL1, 2, 1, 0),
SOC_SINGLE("Playback 6dB Attenuate", WM8753_ADCTL1, 1, 1, 0),

SOC_ENUM("De-emphasis", wm8753_क्रमागत[8]),
SOC_ENUM("Playback Mono Mix", wm8753_क्रमागत[9]),
SOC_ENUM("Playback Phase", wm8753_क्रमागत[10]),

SOC_SINGLE_TLV("Mic2 Capture Volume", WM8753_INCTL1, 7, 3, 0, mic_preamp_tlv),
SOC_SINGLE_TLV("Mic1 Capture Volume", WM8753_INCTL1, 5, 3, 0, mic_preamp_tlv),

SOC_ENUM_EXT("DAI Mode", wm8753_क्रमागत[26], wm8753_get_dai, wm8753_set_dai),

SOC_ENUM("ADC Data Select", wm8753_क्रमागत[27]),
SOC_ENUM("ROUT2 Phase", wm8753_क्रमागत[28]),
पूर्ण;

/*
 * _DAPM_ Controls
 */

/* Left Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Voice Playback Switch", WM8753_LOUTM2, 8, 1, 0),
SOC_DAPM_SINGLE("Sidetone Playback Switch", WM8753_LOUTM2, 7, 1, 0),
SOC_DAPM_SINGLE("Left Playback Switch", WM8753_LOUTM1, 8, 1, 0),
SOC_DAPM_SINGLE("Bypass Playback Switch", WM8753_LOUTM1, 7, 1, 0),
पूर्ण;

/* Right mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Voice Playback Switch", WM8753_ROUTM2, 8, 1, 0),
SOC_DAPM_SINGLE("Sidetone Playback Switch", WM8753_ROUTM2, 7, 1, 0),
SOC_DAPM_SINGLE("Right Playback Switch", WM8753_ROUTM1, 8, 1, 0),
SOC_DAPM_SINGLE("Bypass Playback Switch", WM8753_ROUTM1, 7, 1, 0),
पूर्ण;

/* Mono mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Left Playback Switch", WM8753_MOUTM1, 8, 1, 0),
SOC_DAPM_SINGLE("Right Playback Switch", WM8753_MOUTM2, 8, 1, 0),
SOC_DAPM_SINGLE("Voice Playback Switch", WM8753_MOUTM2, 3, 1, 0),
SOC_DAPM_SINGLE("Sidetone Playback Switch", WM8753_MOUTM2, 7, 1, 0),
SOC_DAPM_SINGLE("Bypass Playback Switch", WM8753_MOUTM1, 7, 1, 0),
पूर्ण;

/* Mono 2 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_mono2_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[17]);

/* Out 3 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_out3_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[18]);

/* Out 4 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_out4_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[19]);

/* ADC Mono Mix */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_adc_mono_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[22]);

/* Record mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_record_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Voice Capture Switch", WM8753_RECMIX2, 3, 1, 0),
SOC_DAPM_SINGLE("Left Capture Switch", WM8753_RECMIX1, 3, 1, 0),
SOC_DAPM_SINGLE("Right Capture Switch", WM8753_RECMIX1, 7, 1, 0),
पूर्ण;

/* Left ADC mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_adc_left_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[21]);

/* Right ADC mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_adc_right_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[20]);

/* MIC mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_mic_mux_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[16]);

/* ALC mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_alc_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Capture Switch", WM8753_INCTL2, 3, 1, 0),
SOC_DAPM_SINGLE("Mic2 Capture Switch", WM8753_INCTL2, 2, 1, 0),
SOC_DAPM_SINGLE("Mic1 Capture Switch", WM8753_INCTL2, 1, 1, 0),
SOC_DAPM_SINGLE("Rx Capture Switch", WM8753_INCTL2, 0, 1, 0),
पूर्ण;

/* Left Line mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_line_left_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[14]);

/* Right Line mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_line_right_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[13]);

/* Mono Line mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_line_mono_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[12]);

/* Line mux and mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_line_mux_mix_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[11]);

/* Rx mux and mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_rx_mux_mix_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[15]);

/* Mic Selector Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8753_mic_sel_mux_controls =
SOC_DAPM_ENUM("Route", wm8753_क्रमागत[25]);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8753_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MICBIAS("Mic Bias", WM8753_PWR1, 5, 0),
SND_SOC_DAPM_MIXER("Left Mixer", WM8753_PWR4, 0, 0,
	&wm8753_left_mixer_controls[0], ARRAY_SIZE(wm8753_left_mixer_controls)),
SND_SOC_DAPM_PGA("Left Out 1", WM8753_PWR3, 8, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left Out 2", WM8753_PWR3, 6, 0, शून्य, 0),
SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback", WM8753_PWR1, 3, 0),
SND_SOC_DAPM_OUTPUT("LOUT1"),
SND_SOC_DAPM_OUTPUT("LOUT2"),
SND_SOC_DAPM_MIXER("Right Mixer", WM8753_PWR4, 1, 0,
	&wm8753_right_mixer_controls[0], ARRAY_SIZE(wm8753_right_mixer_controls)),
SND_SOC_DAPM_PGA("Right Out 1", WM8753_PWR3, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Out 2", WM8753_PWR3, 5, 0, शून्य, 0),
SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback", WM8753_PWR1, 2, 0),
SND_SOC_DAPM_OUTPUT("ROUT1"),
SND_SOC_DAPM_OUTPUT("ROUT2"),
SND_SOC_DAPM_MIXER("Mono Mixer", WM8753_PWR4, 2, 0,
	&wm8753_mono_mixer_controls[0], ARRAY_SIZE(wm8753_mono_mixer_controls)),
SND_SOC_DAPM_PGA("Mono Out 1", WM8753_PWR3, 2, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Mono Out 2", WM8753_PWR3, 1, 0, शून्य, 0),
SND_SOC_DAPM_DAC("Voice DAC", "Voice Playback", WM8753_PWR1, 4, 0),
SND_SOC_DAPM_OUTPUT("MONO1"),
SND_SOC_DAPM_MUX("Mono 2 Mux", SND_SOC_NOPM, 0, 0, &wm8753_mono2_controls),
SND_SOC_DAPM_OUTPUT("MONO2"),
SND_SOC_DAPM_MIXER("Out3 Left + Right", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MUX("Out3 Mux", SND_SOC_NOPM, 0, 0, &wm8753_out3_controls),
SND_SOC_DAPM_PGA("Out 3", WM8753_PWR3, 4, 0, शून्य, 0),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_MUX("Out4 Mux", SND_SOC_NOPM, 0, 0, &wm8753_out4_controls),
SND_SOC_DAPM_PGA("Out 4", WM8753_PWR3, 3, 0, शून्य, 0),
SND_SOC_DAPM_OUTPUT("OUT4"),
SND_SOC_DAPM_MIXER("Playback Mixer", WM8753_PWR4, 3, 0,
	&wm8753_record_mixer_controls[0],
	ARRAY_SIZE(wm8753_record_mixer_controls)),
SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8753_PWR2, 3, 0),
SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8753_PWR2, 2, 0),
SND_SOC_DAPM_MUX("Capture Left Mixer", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_mono_controls),
SND_SOC_DAPM_MUX("Capture Right Mixer", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_mono_controls),
SND_SOC_DAPM_MUX("Capture Left Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_left_controls),
SND_SOC_DAPM_MUX("Capture Right Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_right_controls),
SND_SOC_DAPM_MUX("Mic Sidetone Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_mic_mux_controls),
SND_SOC_DAPM_PGA("Left Capture Volume", WM8753_PWR2, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Capture Volume", WM8753_PWR2, 4, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("ALC Mixer", WM8753_PWR2, 6, 0,
	&wm8753_alc_mixer_controls[0], ARRAY_SIZE(wm8753_alc_mixer_controls)),
SND_SOC_DAPM_MUX("Line Left Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_line_left_controls),
SND_SOC_DAPM_MUX("Line Right Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_line_right_controls),
SND_SOC_DAPM_MUX("Line Mono Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_line_mono_controls),
SND_SOC_DAPM_MUX("Line Mixer", WM8753_PWR2, 0, 0,
	&wm8753_line_mux_mix_controls),
SND_SOC_DAPM_MUX("Rx Mixer", WM8753_PWR2, 1, 0,
	&wm8753_rx_mux_mix_controls),
SND_SOC_DAPM_PGA("Mic 1 Volume", WM8753_PWR2, 8, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Mic 2 Volume", WM8753_PWR2, 7, 0, शून्य, 0),
SND_SOC_DAPM_MUX("Mic Selection Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_mic_sel_mux_controls),
SND_SOC_DAPM_INPUT("LINE1"),
SND_SOC_DAPM_INPUT("LINE2"),
SND_SOC_DAPM_INPUT("RXP"),
SND_SOC_DAPM_INPUT("RXN"),
SND_SOC_DAPM_INPUT("ACIN"),
SND_SOC_DAPM_OUTPUT("ACOP"),
SND_SOC_DAPM_INPUT("MIC1N"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2N"),
SND_SOC_DAPM_INPUT("MIC2"),
SND_SOC_DAPM_VMID("VREF"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8753_dapm_routes[] = अणु
	/* left mixer */
	अणु"Left Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Left Mixer", "Voice Playback Switch", "Voice DAC"पूर्ण,
	अणु"Left Mixer", "Sidetone Playback Switch", "Mic Sidetone Mux"पूर्ण,
	अणु"Left Mixer", "Bypass Playback Switch", "Line Left Mux"पूर्ण,

	/* right mixer */
	अणु"Right Mixer", "Right Playback Switch", "Right DAC"पूर्ण,
	अणु"Right Mixer", "Voice Playback Switch", "Voice DAC"पूर्ण,
	अणु"Right Mixer", "Sidetone Playback Switch", "Mic Sidetone Mux"पूर्ण,
	अणु"Right Mixer", "Bypass Playback Switch", "Line Right Mux"पूर्ण,

	/* mono mixer */
	अणु"Mono Mixer", "Voice Playback Switch", "Voice DAC"पूर्ण,
	अणु"Mono Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Mono Mixer", "Right Playback Switch", "Right DAC"पूर्ण,
	अणु"Mono Mixer", "Sidetone Playback Switch", "Mic Sidetone Mux"पूर्ण,
	अणु"Mono Mixer", "Bypass Playback Switch", "Line Mono Mux"पूर्ण,

	/* left out */
	अणु"Left Out 1", शून्य, "Left Mixer"पूर्ण,
	अणु"Left Out 2", शून्य, "Left Mixer"पूर्ण,
	अणु"LOUT1", शून्य, "Left Out 1"पूर्ण,
	अणु"LOUT2", शून्य, "Left Out 2"पूर्ण,

	/* right out */
	अणु"Right Out 1", शून्य, "Right Mixer"पूर्ण,
	अणु"Right Out 2", शून्य, "Right Mixer"पूर्ण,
	अणु"ROUT1", शून्य, "Right Out 1"पूर्ण,
	अणु"ROUT2", शून्य, "Right Out 2"पूर्ण,

	/* mono 1 out */
	अणु"Mono Out 1", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONO1", शून्य, "Mono Out 1"पूर्ण,

	/* mono 2 out */
	अणु"Mono 2 Mux", "Left + Right", "Out3 Left + Right"पूर्ण,
	अणु"Mono 2 Mux", "Inverted Mono 1", "MONO1"पूर्ण,
	अणु"Mono 2 Mux", "Left", "Left Mixer"पूर्ण,
	अणु"Mono 2 Mux", "Right", "Right Mixer"पूर्ण,
	अणु"Mono Out 2", शून्य, "Mono 2 Mux"पूर्ण,
	अणु"MONO2", शून्य, "Mono Out 2"पूर्ण,

	/* out 3 */
	अणु"Out3 Left + Right", शून्य, "Left Mixer"पूर्ण,
	अणु"Out3 Left + Right", शून्य, "Right Mixer"पूर्ण,
	अणु"Out3 Mux", "VREF", "VREF"पूर्ण,
	अणु"Out3 Mux", "Left + Right", "Out3 Left + Right"पूर्ण,
	अणु"Out3 Mux", "ROUT2", "ROUT2"पूर्ण,
	अणु"Out 3", शून्य, "Out3 Mux"पूर्ण,
	अणु"OUT3", शून्य, "Out 3"पूर्ण,

	/* out 4 */
	अणु"Out4 Mux", "VREF", "VREF"पूर्ण,
	अणु"Out4 Mux", "Capture ST", "Playback Mixer"पूर्ण,
	अणु"Out4 Mux", "LOUT2", "LOUT2"पूर्ण,
	अणु"Out 4", शून्य, "Out4 Mux"पूर्ण,
	अणु"OUT4", शून्य, "Out 4"पूर्ण,

	/* record mixer  */
	अणु"Playback Mixer", "Left Capture Switch", "Left Mixer"पूर्ण,
	अणु"Playback Mixer", "Voice Capture Switch", "Mono Mixer"पूर्ण,
	अणु"Playback Mixer", "Right Capture Switch", "Right Mixer"पूर्ण,

	/* Mic/SideTone Mux */
	अणु"Mic Sidetone Mux", "Left PGA", "Left Capture Volume"पूर्ण,
	अणु"Mic Sidetone Mux", "Right PGA", "Right Capture Volume"पूर्ण,
	अणु"Mic Sidetone Mux", "Mic 1", "Mic 1 Volume"पूर्ण,
	अणु"Mic Sidetone Mux", "Mic 2", "Mic 2 Volume"पूर्ण,

	/* Capture Left Mux */
	अणु"Capture Left Mux", "PGA", "Left Capture Volume"पूर्ण,
	अणु"Capture Left Mux", "Line or RXP-RXN", "Line Left Mux"पूर्ण,
	अणु"Capture Left Mux", "Line", "LINE1"पूर्ण,

	/* Capture Right Mux */
	अणु"Capture Right Mux", "PGA", "Right Capture Volume"पूर्ण,
	अणु"Capture Right Mux", "Line or RXP-RXN", "Line Right Mux"पूर्ण,
	अणु"Capture Right Mux", "Sidetone", "Playback Mixer"पूर्ण,

	/* Mono Capture mixer-mux */
	अणु"Capture Right Mixer", "Stereo", "Capture Right Mux"पूर्ण,
	अणु"Capture Left Mixer", "Stereo", "Capture Left Mux"पूर्ण,
	अणु"Capture Left Mixer", "Analogue Mix Left", "Capture Left Mux"पूर्ण,
	अणु"Capture Left Mixer", "Analogue Mix Left", "Capture Right Mux"पूर्ण,
	अणु"Capture Right Mixer", "Analogue Mix Right", "Capture Left Mux"पूर्ण,
	अणु"Capture Right Mixer", "Analogue Mix Right", "Capture Right Mux"पूर्ण,
	अणु"Capture Left Mixer", "Digital Mono Mix", "Capture Left Mux"पूर्ण,
	अणु"Capture Left Mixer", "Digital Mono Mix", "Capture Right Mux"पूर्ण,
	अणु"Capture Right Mixer", "Digital Mono Mix", "Capture Left Mux"पूर्ण,
	अणु"Capture Right Mixer", "Digital Mono Mix", "Capture Right Mux"पूर्ण,

	/* ADC */
	अणु"Left ADC", शून्य, "Capture Left Mixer"पूर्ण,
	अणु"Right ADC", शून्य, "Capture Right Mixer"पूर्ण,

	/* Left Capture Volume */
	अणु"Left Capture Volume", शून्य, "ACIN"पूर्ण,

	/* Right Capture Volume */
	अणु"Right Capture Volume", शून्य, "Mic 2 Volume"पूर्ण,

	/* ALC Mixer */
	अणु"ALC Mixer", "Line Capture Switch", "Line Mixer"पूर्ण,
	अणु"ALC Mixer", "Mic2 Capture Switch", "Mic 2 Volume"पूर्ण,
	अणु"ALC Mixer", "Mic1 Capture Switch", "Mic 1 Volume"पूर्ण,
	अणु"ALC Mixer", "Rx Capture Switch", "Rx Mixer"पूर्ण,

	/* Line Left Mux */
	अणु"Line Left Mux", "Line 1", "LINE1"पूर्ण,
	अणु"Line Left Mux", "Rx Mix", "Rx Mixer"पूर्ण,

	/* Line Right Mux */
	अणु"Line Right Mux", "Line 2", "LINE2"पूर्ण,
	अणु"Line Right Mux", "Rx Mix", "Rx Mixer"पूर्ण,

	/* Line Mono Mux */
	अणु"Line Mono Mux", "Line Mix", "Line Mixer"पूर्ण,
	अणु"Line Mono Mux", "Rx Mix", "Rx Mixer"पूर्ण,

	/* Line Mixer/Mux */
	अणु"Line Mixer", "Line 1 + 2", "LINE1"पूर्ण,
	अणु"Line Mixer", "Line 1 - 2", "LINE1"पूर्ण,
	अणु"Line Mixer", "Line 1 + 2", "LINE2"पूर्ण,
	अणु"Line Mixer", "Line 1 - 2", "LINE2"पूर्ण,
	अणु"Line Mixer", "Line 1", "LINE1"पूर्ण,
	अणु"Line Mixer", "Line 2", "LINE2"पूर्ण,

	/* Rx Mixer/Mux */
	अणु"Rx Mixer", "RXP - RXN", "RXP"पूर्ण,
	अणु"Rx Mixer", "RXP + RXN", "RXP"पूर्ण,
	अणु"Rx Mixer", "RXP - RXN", "RXN"पूर्ण,
	अणु"Rx Mixer", "RXP + RXN", "RXN"पूर्ण,
	अणु"Rx Mixer", "RXP", "RXP"पूर्ण,
	अणु"Rx Mixer", "RXN", "RXN"पूर्ण,

	/* Mic 1 Volume */
	अणु"Mic 1 Volume", शून्य, "MIC1N"पूर्ण,
	अणु"Mic 1 Volume", शून्य, "Mic Selection Mux"पूर्ण,

	/* Mic 2 Volume */
	अणु"Mic 2 Volume", शून्य, "MIC2N"पूर्ण,
	अणु"Mic 2 Volume", शून्य, "MIC2"पूर्ण,

	/* Mic Selector Mux */
	अणु"Mic Selection Mux", "Mic 1", "MIC1"पूर्ण,
	अणु"Mic Selection Mux", "Mic 2", "MIC2N"पूर्ण,
	अणु"Mic Selection Mux", "Mic 3", "MIC2"पूर्ण,

	/* ACOP */
	अणु"ACOP", शून्य, "ALC Mixer"पूर्ण,
पूर्ण;

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 भाग2:1;
	u32 n:4;
	u32 k:24;
पूर्ण;

/* The size in bits of the pll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 22) * 10)

अटल व्योम pll_factors(काष्ठा _pll_भाग *pll_भाग, अचिन्हित पूर्णांक target,
	अचिन्हित पूर्णांक source)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;

	Nभाग = target / source;
	अगर (Nभाग < 6) अणु
		source >>= 1;
		pll_भाग->भाग2 = 1;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग->भाग2 = 0;

	अगर ((Nभाग < 6) || (Nभाग > 12))
		prपूर्णांकk(KERN_WARNING
			"wm8753: unsupported N = %u\n", Nभाग);

	pll_भाग->n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check अगर we need to round */
	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	K /= 10;

	pll_भाग->k = K;
पूर्ण

अटल पूर्णांक wm8753_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	u16 reg, enable;
	पूर्णांक offset;
	काष्ठा snd_soc_component *component = codec_dai->component;

	अगर (pll_id < WM8753_PLL1 || pll_id > WM8753_PLL2)
		वापस -ENODEV;

	अगर (pll_id == WM8753_PLL1) अणु
		offset = 0;
		enable = 0x10;
		reg = snd_soc_component_पढ़ो(component, WM8753_CLOCK) & 0xffef;
	पूर्ण अन्यथा अणु
		offset = 4;
		enable = 0x8;
		reg = snd_soc_component_पढ़ो(component, WM8753_CLOCK) & 0xfff7;
	पूर्ण

	अगर (!freq_in || !freq_out) अणु
		/* disable PLL  */
		snd_soc_component_ग_लिखो(component, WM8753_PLL1CTL1 + offset, 0x0026);
		snd_soc_component_ग_लिखो(component, WM8753_CLOCK, reg);
		वापस 0;
	पूर्ण अन्यथा अणु
		u16 value = 0;
		काष्ठा _pll_भाग pll_भाग;

		pll_factors(&pll_भाग, freq_out * 8, freq_in);

		/* set up N and K PLL भागisor ratios */
		/* bits 8:5 = PLL_N, bits 3:0 = PLL_K[21:18] */
		value = (pll_भाग.n << 5) + ((pll_भाग.k & 0x3c0000) >> 18);
		snd_soc_component_ग_लिखो(component, WM8753_PLL1CTL2 + offset, value);

		/* bits 8:0 = PLL_K[17:9] */
		value = (pll_भाग.k & 0x03fe00) >> 9;
		snd_soc_component_ग_लिखो(component, WM8753_PLL1CTL3 + offset, value);

		/* bits 8:0 = PLL_K[8:0] */
		value = pll_भाग.k & 0x0001ff;
		snd_soc_component_ग_लिखो(component, WM8753_PLL1CTL4 + offset, value);

		/* set PLL as input and enable */
		snd_soc_component_ग_लिखो(component, WM8753_PLL1CTL1 + offset, 0x0027 |
			(pll_भाग.भाग2 << 3));
		snd_soc_component_ग_लिखो(component, WM8753_CLOCK, reg | enable);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा _coeff_भाग अणु
	u32 mclk;
	u32 rate;
	u8 sr:5;
	u8 usb:1;
पूर्ण;

/* codec hअगरi mclk (after PLL) घड़ी भागider coefficients */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	/* 8k */
	अणु12288000, 8000, 0x6, 0x0पूर्ण,
	अणु11289600, 8000, 0x16, 0x0पूर्ण,
	अणु18432000, 8000, 0x7, 0x0पूर्ण,
	अणु16934400, 8000, 0x17, 0x0पूर्ण,
	अणु12000000, 8000, 0x6, 0x1पूर्ण,

	/* 11.025k */
	अणु11289600, 11025, 0x18, 0x0पूर्ण,
	अणु16934400, 11025, 0x19, 0x0पूर्ण,
	अणु12000000, 11025, 0x19, 0x1पूर्ण,

	/* 16k */
	अणु12288000, 16000, 0xa, 0x0पूर्ण,
	अणु18432000, 16000, 0xb, 0x0पूर्ण,
	अणु12000000, 16000, 0xa, 0x1पूर्ण,

	/* 22.05k */
	अणु11289600, 22050, 0x1a, 0x0पूर्ण,
	अणु16934400, 22050, 0x1b, 0x0पूर्ण,
	अणु12000000, 22050, 0x1b, 0x1पूर्ण,

	/* 32k */
	अणु12288000, 32000, 0xc, 0x0पूर्ण,
	अणु18432000, 32000, 0xd, 0x0पूर्ण,
	अणु12000000, 32000, 0xa, 0x1पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, 0x10, 0x0पूर्ण,
	अणु16934400, 44100, 0x11, 0x0पूर्ण,
	अणु12000000, 44100, 0x11, 0x1पूर्ण,

	/* 48k */
	अणु12288000, 48000, 0x0, 0x0पूर्ण,
	अणु18432000, 48000, 0x1, 0x0पूर्ण,
	अणु12000000, 48000, 0x0, 0x1पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, 0x1e, 0x0पूर्ण,
	अणु16934400, 88200, 0x1f, 0x0पूर्ण,
	अणु12000000, 88200, 0x1f, 0x1पूर्ण,

	/* 96k */
	अणु12288000, 96000, 0xe, 0x0पूर्ण,
	अणु18432000, 96000, 0xf, 0x0पूर्ण,
	अणु12000000, 96000, 0xe, 0x1पूर्ण,
पूर्ण;

अटल पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate == rate && coeff_भाग[i].mclk == mclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Clock after PLL and भागiders
 */
अटल पूर्णांक wm8753_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल 11289600:
	हाल 12000000:
	हाल 12288000:
	हाल 16934400:
	हाल 18432000:
		अगर (clk_id == WM8753_MCLK) अणु
			wm8753->sysclk = freq;
			वापस 0;
		पूर्ण अन्यथा अगर (clk_id == WM8753_PCMCLK) अणु
			wm8753->pcmclk = freq;
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Set's ADC and Voice DAC क्रमmat.
 */
अटल पूर्णांक wm8753_vdac_adc_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 voice = snd_soc_component_पढ़ो(component, WM8753_PCM) & 0x01ec;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		voice |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		voice |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		voice |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		voice |= 0x0013;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8753_PCM, voice);
	वापस 0;
पूर्ण

/*
 * Set PCM DAI bit size and sample rate.
 */
अटल पूर्णांक wm8753_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	u16 voice = snd_soc_component_पढ़ो(component, WM8753_PCM) & 0x01f3;
	u16 srate = snd_soc_component_पढ़ो(component, WM8753_SRATE1) & 0x017f;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		voice |= 0x0004;
		अवरोध;
	हाल 24:
		voice |= 0x0008;
		अवरोध;
	हाल 32:
		voice |= 0x000c;
		अवरोध;
	पूर्ण

	/* sample rate */
	अगर (params_rate(params) * 384 == wm8753->pcmclk)
		srate |= 0x80;
	snd_soc_component_ग_लिखो(component, WM8753_SRATE1, srate);

	snd_soc_component_ग_लिखो(component, WM8753_PCM, voice);
	वापस 0;
पूर्ण

/*
 * Set's PCM dai fmt and BCLK.
 */
अटल पूर्णांक wm8753_pcm_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 voice, ioctl;

	voice = snd_soc_component_पढ़ो(component, WM8753_PCM) & 0x011f;
	ioctl = snd_soc_component_पढ़ो(component, WM8753_IOCTL) & 0x015d;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ioctl |= 0x2;
		fallthrough;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		voice |= 0x0040;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid क्रम DSP modes */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			voice |= 0x0080;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		voice &= ~0x0010;
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			voice |= 0x0090;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			voice |= 0x0080;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			voice |= 0x0010;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8753_PCM, voice);
	snd_soc_component_ग_लिखो(component, WM8753_IOCTL, ioctl);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8753_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	चयन (भाग_id) अणु
	हाल WM8753_PCMDIV:
		reg = snd_soc_component_पढ़ो(component, WM8753_CLOCK) & 0x003f;
		snd_soc_component_ग_लिखो(component, WM8753_CLOCK, reg | भाग);
		अवरोध;
	हाल WM8753_BCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8753_SRATE2) & 0x01c7;
		snd_soc_component_ग_लिखो(component, WM8753_SRATE2, reg | भाग);
		अवरोध;
	हाल WM8753_VXCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8753_SRATE2) & 0x003f;
		snd_soc_component_ग_लिखो(component, WM8753_SRATE2, reg | भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set's HiFi DAC क्रमmat.
 */
अटल पूर्णांक wm8753_hdac_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 hअगरi = snd_soc_component_पढ़ो(component, WM8753_HIFI) & 0x01e0;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		hअगरi |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		hअगरi |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		hअगरi |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		hअगरi |= 0x0013;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8753_HIFI, hअगरi);
	वापस 0;
पूर्ण

/*
 * Set's I2S DAI क्रमmat.
 */
अटल पूर्णांक wm8753_i2s_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 ioctl, hअगरi;

	hअगरi = snd_soc_component_पढ़ो(component, WM8753_HIFI) & 0x013f;
	ioctl = snd_soc_component_पढ़ो(component, WM8753_IOCTL) & 0x00ae;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ioctl |= 0x1;
		fallthrough;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		hअगरi |= 0x0040;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid क्रम DSP modes */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			hअगरi |= 0x0080;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		hअगरi &= ~0x0010;
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			hअगरi |= 0x0090;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			hअगरi |= 0x0080;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			hअगरi |= 0x0010;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8753_HIFI, hअगरi);
	snd_soc_component_ग_लिखो(component, WM8753_IOCTL, ioctl);
	वापस 0;
पूर्ण

/*
 * Set PCM DAI bit size and sample rate.
 */
अटल पूर्णांक wm8753_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	u16 srate = snd_soc_component_पढ़ो(component, WM8753_SRATE1) & 0x01c0;
	u16 hअगरi = snd_soc_component_पढ़ो(component, WM8753_HIFI) & 0x01f3;
	पूर्णांक coeff;

	/* is digital filter coefficient valid ? */
	coeff = get_coeff(wm8753->sysclk, params_rate(params));
	अगर (coeff < 0) अणु
		prपूर्णांकk(KERN_ERR "wm8753 invalid MCLK or rate\n");
		वापस coeff;
	पूर्ण
	snd_soc_component_ग_लिखो(component, WM8753_SRATE1, srate | (coeff_भाग[coeff].sr << 1) |
		coeff_भाग[coeff].usb);

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		hअगरi |= 0x0004;
		अवरोध;
	हाल 24:
		hअगरi |= 0x0008;
		अवरोध;
	हाल 32:
		hअगरi |= 0x000c;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8753_HIFI, hअगरi);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8753_mode1v_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 घड़ी;

	/* set clk source as pcmclk */
	घड़ी = snd_soc_component_पढ़ो(component, WM8753_CLOCK) & 0xfffb;
	snd_soc_component_ग_लिखो(component, WM8753_CLOCK, घड़ी);

	वापस wm8753_vdac_adc_set_dai_fmt(component, fmt);
पूर्ण

अटल पूर्णांक wm8753_mode1h_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	वापस wm8753_hdac_set_dai_fmt(component, fmt);
पूर्ण

अटल पूर्णांक wm8753_mode2_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 घड़ी;

	/* set clk source as pcmclk */
	घड़ी = snd_soc_component_पढ़ो(component, WM8753_CLOCK) & 0xfffb;
	snd_soc_component_ग_लिखो(component, WM8753_CLOCK, घड़ी);

	वापस wm8753_vdac_adc_set_dai_fmt(component, fmt);
पूर्ण

अटल पूर्णांक wm8753_mode3_4_set_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	u16 घड़ी;

	/* set clk source as mclk */
	घड़ी = snd_soc_component_पढ़ो(component, WM8753_CLOCK) & 0xfffb;
	snd_soc_component_ग_लिखो(component, WM8753_CLOCK, घड़ी | 0x4);

	अगर (wm8753_hdac_set_dai_fmt(component, fmt) < 0)
		वापस -EINVAL;
	वापस wm8753_vdac_adc_set_dai_fmt(component, fmt);
पूर्ण

अटल पूर्णांक wm8753_hअगरi_ग_लिखो_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (wm8753->dai_func) अणु
	हाल 0:
		ret = wm8753_mode1h_set_dai_fmt(component, fmt);
		अवरोध;
	हाल 1:
		ret = wm8753_mode2_set_dai_fmt(component, fmt);
		अवरोध;
	हाल 2:
	हाल 3:
		ret = wm8753_mode3_4_set_dai_fmt(component, fmt);
		अवरोध;
	शेष:
		 अवरोध;
	पूर्ण
	अगर (ret)
		वापस ret;

	वापस wm8753_i2s_set_dai_fmt(component, fmt);
पूर्ण

अटल पूर्णांक wm8753_hअगरi_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	wm8753->hअगरi_fmt = fmt;

	वापस wm8753_hअगरi_ग_लिखो_dai_fmt(component, fmt);
पूर्ण;

अटल पूर्णांक wm8753_voice_ग_लिखो_dai_fmt(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर (wm8753->dai_func != 0)
		वापस 0;

	ret = wm8753_mode1v_set_dai_fmt(component, fmt);
	अगर (ret)
		वापस ret;
	ret = wm8753_pcm_set_dai_fmt(component, fmt);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण;

अटल पूर्णांक wm8753_voice_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	wm8753->voice_fmt = fmt;

	वापस wm8753_voice_ग_लिखो_dai_fmt(component, fmt);
पूर्ण;

अटल पूर्णांक wm8753_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8753_DAC) & 0xfff7;
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	/* the digital mute covers the HiFi and Voice DAC's on the WM8753.
	 * make sure we check अगर they are not both active when we mute */
	अगर (mute && wm8753->dai_func == 1) अणु
		अगर (!snd_soc_component_active(component))
			snd_soc_component_ग_लिखो(component, WM8753_DAC, mute_reg | 0x8);
	पूर्ण अन्यथा अणु
		अगर (mute)
			snd_soc_component_ग_लिखो(component, WM8753_DAC, mute_reg | 0x8);
		अन्यथा
			snd_soc_component_ग_लिखो(component, WM8753_DAC, mute_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wm8753_अक्षरge_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8753_priv *wm8753 =
		container_of(work, काष्ठा wm8753_priv, अक्षरge_work.work);

	/* Set to 500k */
	regmap_update_bits(wm8753->regmap, WM8753_PWR1, 0x0180, 0x0100);
पूर्ण

अटल पूर्णांक wm8753_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	u16 pwr_reg = snd_soc_component_पढ़ो(component, WM8753_PWR1) & 0xfe3e;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_ग_लिखो(component, WM8753_PWR1, pwr_reg | 0x00c0);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Wait until fully अक्षरged */
		flush_delayed_work(&wm8753->अक्षरge_work);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* set vmid to 5k क्रम quick घातer up */
			snd_soc_component_ग_लिखो(component, WM8753_PWR1, pwr_reg | 0x01c1);
			schedule_delayed_work(&wm8753->अक्षरge_work,
				msecs_to_jअगरfies(caps_अक्षरge));
		पूर्ण अन्यथा अणु
			/* mute dac and set vmid to 500k, enable VREF */
			snd_soc_component_ग_लिखो(component, WM8753_PWR1, pwr_reg | 0x0141);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		cancel_delayed_work_sync(&wm8753->अक्षरge_work);
		snd_soc_component_ग_लिखो(component, WM8753_PWR1, 0x0001);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8753_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |\
		SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

#घोषणा WM8753_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

/*
 * The WM8753 supports up to 4 dअगरferent and mutually exclusive DAI
 * configurations. This gives 2 PCM's available क्रम use, hअगरi and voice.
 * NOTE: The Voice PCM cannot play or capture audio to the CPU as it's DAI
 * is connected between the wm8753 and a BT codec or GSM modem.
 *
 * 1. Voice over PCM DAI - HIFI DAC over HIFI DAI
 * 2. Voice over HIFI DAI - HIFI disabled
 * 3. Voice disabled - HIFI over HIFI
 * 4. Voice disabled - HIFI over HIFI, uses voice DAI LRC क्रम capture
 */
अटल स्थिर काष्ठा snd_soc_dai_ops wm8753_dai_ops_hअगरi_mode = अणु
	.hw_params	= wm8753_i2s_hw_params,
	.mute_stream	= wm8753_mute,
	.set_fmt	= wm8753_hअगरi_set_dai_fmt,
	.set_clkभाग	= wm8753_set_dai_clkभाग,
	.set_pll	= wm8753_set_dai_pll,
	.set_sysclk	= wm8753_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8753_dai_ops_voice_mode = अणु
	.hw_params	= wm8753_pcm_hw_params,
	.mute_stream	= wm8753_mute,
	.set_fmt	= wm8753_voice_set_dai_fmt,
	.set_clkभाग	= wm8753_set_dai_clkभाग,
	.set_pll	= wm8753_set_dai_pll,
	.set_sysclk	= wm8753_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8753_dai[] = अणु
/* DAI HiFi mode 1 */
अणु	.name = "wm8753-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8753_RATES,
		.क्रमmats = WM8753_FORMATS
	पूर्ण,
	.capture = अणु /* dummy क्रम fast DAI चयनing */
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8753_RATES,
		.क्रमmats = WM8753_FORMATS
	पूर्ण,
	.ops = &wm8753_dai_ops_hअगरi_mode,
पूर्ण,
/* DAI Voice mode 1 */
अणु	.name = "wm8753-voice",
	.playback = अणु
		.stream_name = "Voice Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = WM8753_RATES,
		.क्रमmats = WM8753_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8753_RATES,
		.क्रमmats = WM8753_FORMATS,
	पूर्ण,
	.ops = &wm8753_dai_ops_voice_mode,
पूर्ण,
पूर्ण;

अटल पूर्णांक wm8753_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	regcache_sync(wm8753->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8753_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	INIT_DELAYED_WORK(&wm8753->अक्षरge_work, wm8753_अक्षरge_work);

	ret = wm8753_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8753->dai_func = 0;

	/* set the update bits */
	snd_soc_component_update_bits(component, WM8753_LDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_RDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_LADC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_RADC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_LOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_ROUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_LOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_ROUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_LINVOL, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_RINVOL, 0x0100, 0x0100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8753 = अणु
	.probe			= wm8753_probe,
	.resume			= wm8753_resume,
	.set_bias_level		= wm8753_set_bias_level,
	.controls		= wm8753_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8753_snd_controls),
	.dapm_widमाला_लो		= wm8753_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8753_dapm_widमाला_लो),
	.dapm_routes		= wm8753_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8753_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8753_of_match[] = अणु
	अणु .compatible = "wlf,wm8753", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8753_of_match);

अटल स्थिर काष्ठा regmap_config wm8753_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8753_ADCTL2,
	.अस्थिर_reg = wm8753_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8753_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8753_reg_शेषs),
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8753_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8753_priv *wm8753;
	पूर्णांक ret;

	wm8753 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8753_priv),
			      GFP_KERNEL);
	अगर (wm8753 == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, wm8753);

	wm8753->regmap = devm_regmap_init_spi(spi, &wm8753_regmap);
	अगर (IS_ERR(wm8753->regmap)) अणु
		ret = PTR_ERR(wm8753->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev, &soc_component_dev_wm8753,
				     wm8753_dai, ARRAY_SIZE(wm8753_dai));
	अगर (ret != 0)
		dev_err(&spi->dev, "Failed to register CODEC: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8753_spi_driver = अणु
	.driver = अणु
		.name	= "wm8753",
		.of_match_table = wm8753_of_match,
	पूर्ण,
	.probe		= wm8753_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8753_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8753_priv *wm8753;
	पूर्णांक ret;

	wm8753 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8753_priv),
			      GFP_KERNEL);
	अगर (wm8753 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8753);

	wm8753->regmap = devm_regmap_init_i2c(i2c, &wm8753_regmap);
	अगर (IS_ERR(wm8753->regmap)) अणु
		ret = PTR_ERR(wm8753->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &soc_component_dev_wm8753,
				     wm8753_dai, ARRAY_SIZE(wm8753_dai));
	अगर (ret != 0)
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8753_i2c_id[] = अणु
	अणु "wm8753", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8753_i2c_id);

अटल काष्ठा i2c_driver wm8753_i2c_driver = अणु
	.driver = अणु
		.name = "wm8753",
		.of_match_table = wm8753_of_match,
	पूर्ण,
	.probe =    wm8753_i2c_probe,
	.id_table = wm8753_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8753_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8753_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8753 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8753_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8753 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8753_modinit);

अटल व्योम __निकास wm8753_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8753_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8753_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8753_निकास);

MODULE_DESCRIPTION("ASoC WM8753 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
