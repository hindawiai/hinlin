<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8988.c -- WM8988 ALSA SoC audio driver
 *
 * Copyright 2009 Wolfson Microelectronics plc
 * Copyright 2005 Openedhand Ltd.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश "wm8988.h"

/*
 * wm8988 रेजिस्टर cache
 * We can't पढ़ो the WM8988 रेजिस्टर space when we
 * are using 2 wire क्रम device control, so we cache them instead.
 */
अटल स्थिर काष्ठा reg_शेष wm8988_reg_शेषs[] = अणु
	अणु 0, 0x0097 पूर्ण,
	अणु 1, 0x0097 पूर्ण,
	अणु 2, 0x0079 पूर्ण,
	अणु 3, 0x0079 पूर्ण,
	अणु 5, 0x0008 पूर्ण,
	अणु 7, 0x000a पूर्ण,
	अणु 8, 0x0000 पूर्ण,
	अणु 10, 0x00ff पूर्ण,
	अणु 11, 0x00ff पूर्ण,
	अणु 12, 0x000f पूर्ण,
	अणु 13, 0x000f पूर्ण,
	अणु 16, 0x0000 पूर्ण,
	अणु 17, 0x007b पूर्ण,
	अणु 18, 0x0000 पूर्ण,
	अणु 19, 0x0032 पूर्ण,
	अणु 20, 0x0000 पूर्ण,
	अणु 21, 0x00c3 पूर्ण,
	अणु 22, 0x00c3 पूर्ण,
	अणु 23, 0x00c0 पूर्ण,
	अणु 24, 0x0000 पूर्ण,
	अणु 25, 0x0000 पूर्ण,
	अणु 26, 0x0000 पूर्ण,
	अणु 27, 0x0000 पूर्ण,
	अणु 31, 0x0000 पूर्ण,
	अणु 32, 0x0000 पूर्ण,
	अणु 33, 0x0000 पूर्ण,
	अणु 34, 0x0050 पूर्ण,
	अणु 35, 0x0050 पूर्ण,
	अणु 36, 0x0050 पूर्ण,
	अणु 37, 0x0050 पूर्ण,
	अणु 40, 0x0079 पूर्ण,
	अणु 41, 0x0079 पूर्ण,
	अणु 42, 0x0079 पूर्ण,
पूर्ण;

अटल bool wm8988_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8988_LINVOL:
	हाल WM8988_RINVOL:
	हाल WM8988_LOUT1V:
	हाल WM8988_ROUT1V:
	हाल WM8988_ADCDAC:
	हाल WM8988_IFACE:
	हाल WM8988_SRATE:
	हाल WM8988_LDAC:
	हाल WM8988_RDAC:
	हाल WM8988_BASS:
	हाल WM8988_TREBLE:
	हाल WM8988_RESET:
	हाल WM8988_3D:
	हाल WM8988_ALC1:
	हाल WM8988_ALC2:
	हाल WM8988_ALC3:
	हाल WM8988_NGATE:
	हाल WM8988_LADC:
	हाल WM8988_RADC:
	हाल WM8988_ADCTL1:
	हाल WM8988_ADCTL2:
	हाल WM8988_PWR1:
	हाल WM8988_PWR2:
	हाल WM8988_ADCTL3:
	हाल WM8988_ADCIN:
	हाल WM8988_LADCIN:
	हाल WM8988_RADCIN:
	हाल WM8988_LOUTM1:
	हाल WM8988_LOUTM2:
	हाल WM8988_ROUTM1:
	हाल WM8988_ROUTM2:
	हाल WM8988_LOUT2V:
	हाल WM8988_ROUT2V:
	हाल WM8988_LPPB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* codec निजी data */
काष्ठा wm8988_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *sysclk_स्थिरraपूर्णांकs;
पूर्ण;

#घोषणा wm8988_reset(c)	snd_soc_component_ग_लिखो(c, WM8988_RESET, 0)

/*
 * WM8988 Controls
 */

अटल स्थिर अक्षर *bass_boost_txt[] = अणु"Linear Control", "Adaptive Boost"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(bass_boost,
			    WM8988_BASS, 7, bass_boost_txt);

अटल स्थिर अक्षर *bass_filter_txt[] = अणु "130Hz @ 48kHz", "200Hz @ 48kHz" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(bass_filter,
			    WM8988_BASS, 6, bass_filter_txt);

अटल स्थिर अक्षर *treble_txt[] = अणु"8kHz", "4kHz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(treble,
			    WM8988_TREBLE, 6, treble_txt);

अटल स्थिर अक्षर *stereo_3d_lc_txt[] = अणु"200Hz", "500Hz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(stereo_3d_lc,
			    WM8988_3D, 5, stereo_3d_lc_txt);

अटल स्थिर अक्षर *stereo_3d_uc_txt[] = अणु"2.2kHz", "1.5kHz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(stereo_3d_uc,
			    WM8988_3D, 6, stereo_3d_uc_txt);

अटल स्थिर अक्षर *stereo_3d_func_txt[] = अणु"Capture", "Playback"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(stereo_3d_func,
			    WM8988_3D, 7, stereo_3d_func_txt);

अटल स्थिर अक्षर *alc_func_txt[] = अणु"Off", "Right", "Left", "Stereo"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(alc_func,
			    WM8988_ALC1, 7, alc_func_txt);

अटल स्थिर अक्षर *ng_type_txt[] = अणु"Constant PGA Gain",
				    "Mute ADC Output"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(ng_type,
			    WM8988_NGATE, 1, ng_type_txt);

अटल स्थिर अक्षर *deemph_txt[] = अणु"None", "32Khz", "44.1Khz", "48Khz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(deemph,
			    WM8988_ADCDAC, 1, deemph_txt);

अटल स्थिर अक्षर *adcpol_txt[] = अणु"Normal", "L Invert", "R Invert",
				   "L + R Invert"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(adcpol,
			    WM8988_ADCDAC, 5, adcpol_txt);

अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -9750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(bypass_tlv, -1500, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8988_snd_controls[] = अणु

SOC_ENUM("Bass Boost", bass_boost),
SOC_ENUM("Bass Filter", bass_filter),
SOC_SINGLE("Bass Volume", WM8988_BASS, 0, 15, 1),

SOC_SINGLE("Treble Volume", WM8988_TREBLE, 0, 15, 0),
SOC_ENUM("Treble Cut-off", treble),

SOC_SINGLE("3D Switch", WM8988_3D, 0, 1, 0),
SOC_SINGLE("3D Volume", WM8988_3D, 1, 15, 0),
SOC_ENUM("3D Lower Cut-off", stereo_3d_lc),
SOC_ENUM("3D Upper Cut-off", stereo_3d_uc),
SOC_ENUM("3D Mode", stereo_3d_func),

SOC_SINGLE("ALC Capture Target Volume", WM8988_ALC1, 0, 7, 0),
SOC_SINGLE("ALC Capture Max Volume", WM8988_ALC1, 4, 7, 0),
SOC_ENUM("ALC Capture Function", alc_func),
SOC_SINGLE("ALC Capture ZC Switch", WM8988_ALC2, 7, 1, 0),
SOC_SINGLE("ALC Capture Hold Time", WM8988_ALC2, 0, 15, 0),
SOC_SINGLE("ALC Capture Decay Time", WM8988_ALC3, 4, 15, 0),
SOC_SINGLE("ALC Capture Attack Time", WM8988_ALC3, 0, 15, 0),
SOC_SINGLE("ALC Capture NG Threshold", WM8988_NGATE, 3, 31, 0),
SOC_ENUM("ALC Capture NG Type", ng_type),
SOC_SINGLE("ALC Capture NG Switch", WM8988_NGATE, 0, 1, 0),

SOC_SINGLE("ZC Timeout Switch", WM8988_ADCTL1, 0, 1, 0),

SOC_DOUBLE_R_TLV("Capture Digital Volume", WM8988_LADC, WM8988_RADC,
		 0, 255, 0, adc_tlv),
SOC_DOUBLE_R_TLV("Capture Volume", WM8988_LINVOL, WM8988_RINVOL,
		 0, 63, 0, pga_tlv),
SOC_DOUBLE_R("Capture ZC Switch", WM8988_LINVOL, WM8988_RINVOL, 6, 1, 0),
SOC_DOUBLE_R("Capture Switch", WM8988_LINVOL, WM8988_RINVOL, 7, 1, 1),

SOC_ENUM("Playback De-emphasis", deemph),

SOC_ENUM("Capture Polarity", adcpol),
SOC_SINGLE("Playback 6dB Attenuate", WM8988_ADCDAC, 7, 1, 0),
SOC_SINGLE("Capture 6dB Attenuate", WM8988_ADCDAC, 8, 1, 0),

SOC_DOUBLE_R_TLV("PCM Volume", WM8988_LDAC, WM8988_RDAC, 0, 255, 0, dac_tlv),

SOC_SINGLE_TLV("Left Mixer Left Bypass Volume", WM8988_LOUTM1, 4, 7, 1,
	       bypass_tlv),
SOC_SINGLE_TLV("Left Mixer Right Bypass Volume", WM8988_LOUTM2, 4, 7, 1,
	       bypass_tlv),
SOC_SINGLE_TLV("Right Mixer Left Bypass Volume", WM8988_ROUTM1, 4, 7, 1,
	       bypass_tlv),
SOC_SINGLE_TLV("Right Mixer Right Bypass Volume", WM8988_ROUTM2, 4, 7, 1,
	       bypass_tlv),

SOC_DOUBLE_R("Output 1 Playback ZC Switch", WM8988_LOUT1V,
	     WM8988_ROUT1V, 7, 1, 0),
SOC_DOUBLE_R_TLV("Output 1 Playback Volume", WM8988_LOUT1V, WM8988_ROUT1V,
		 0, 127, 0, out_tlv),

SOC_DOUBLE_R("Output 2 Playback ZC Switch", WM8988_LOUT2V,
	     WM8988_ROUT2V, 7, 1, 0),
SOC_DOUBLE_R_TLV("Output 2 Playback Volume", WM8988_LOUT2V, WM8988_ROUT2V,
		 0, 127, 0, out_tlv),

पूर्ण;

/*
 * DAPM Controls
 */

अटल पूर्णांक wm8988_lrc_control(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 adctl2 = snd_soc_component_पढ़ो(component, WM8988_ADCTL2);

	/* Use the DAC to gate LRC अगर active, otherwise use ADC */
	अगर (snd_soc_component_पढ़ो(component, WM8988_PWR2) & 0x180)
		adctl2 &= ~0x4;
	अन्यथा
		adctl2 |= 0x4;

	वापस snd_soc_component_ग_लिखो(component, WM8988_ADCTL2, adctl2);
पूर्ण

अटल स्थिर अक्षर *wm8988_line_texts[] = अणु
	"Line 1", "Line 2", "PGA", "Differential"पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm8988_line_values[] = अणु
	0, 1, 3, 4पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8988_lline_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(WM8988_LOUTM1, 0, 7,
			      ARRAY_SIZE(wm8988_line_texts),
			      wm8988_line_texts,
			      wm8988_line_values);
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_left_line_controls =
	SOC_DAPM_ENUM("Route", wm8988_lline_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत wm8988_rline_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(WM8988_ROUTM1, 0, 7,
			      ARRAY_SIZE(wm8988_line_texts),
			      wm8988_line_texts,
			      wm8988_line_values);
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_right_line_controls =
	SOC_DAPM_ENUM("Route", wm8988_rline_क्रमागत);

/* Left Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_left_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Playback Switch", WM8988_LOUTM1, 8, 1, 0),
	SOC_DAPM_SINGLE("Left Bypass Switch", WM8988_LOUTM1, 7, 1, 0),
	SOC_DAPM_SINGLE("Right Playback Switch", WM8988_LOUTM2, 8, 1, 0),
	SOC_DAPM_SINGLE("Right Bypass Switch", WM8988_LOUTM2, 7, 1, 0),
पूर्ण;

/* Right Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_right_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left Playback Switch", WM8988_ROUTM1, 8, 1, 0),
	SOC_DAPM_SINGLE("Left Bypass Switch", WM8988_ROUTM1, 7, 1, 0),
	SOC_DAPM_SINGLE("Playback Switch", WM8988_ROUTM2, 8, 1, 0),
	SOC_DAPM_SINGLE("Right Bypass Switch", WM8988_ROUTM2, 7, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *wm8988_pga_sel[] = अणु"Line 1", "Line 2", "Differential"पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक wm8988_pga_val[] = अणु 0, 1, 3 पूर्ण;

/* Left PGA Mux */
अटल स्थिर काष्ठा soc_क्रमागत wm8988_lpga_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(WM8988_LADCIN, 6, 3,
			      ARRAY_SIZE(wm8988_pga_sel),
			      wm8988_pga_sel,
			      wm8988_pga_val);
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_left_pga_controls =
	SOC_DAPM_ENUM("Route", wm8988_lpga_क्रमागत);

/* Right PGA Mux */
अटल स्थिर काष्ठा soc_क्रमागत wm8988_rpga_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(WM8988_RADCIN, 6, 3,
			      ARRAY_SIZE(wm8988_pga_sel),
			      wm8988_pga_sel,
			      wm8988_pga_val);
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_right_pga_controls =
	SOC_DAPM_ENUM("Route", wm8988_rpga_क्रमागत);

/* Dअगरferential Mux */
अटल स्थिर अक्षर *wm8988_dअगरf_sel[] = अणु"Line 1", "Line 2"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dअगरfmux,
			    WM8988_ADCIN, 8, wm8988_dअगरf_sel);
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_dअगरfmux_controls =
	SOC_DAPM_ENUM("Route", dअगरfmux);

/* Mono ADC Mux */
अटल स्थिर अक्षर *wm8988_mono_mux[] = अणु"Stereo", "Mono (Left)",
	"Mono (Right)", "Digital Mono"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(monomux,
			    WM8988_ADCIN, 6, wm8988_mono_mux);
अटल स्थिर काष्ठा snd_kcontrol_new wm8988_monomux_controls =
	SOC_DAPM_ENUM("Route", monomux);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8988_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("Mic Bias", WM8988_PWR1, 1, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("Differential Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_dअगरfmux_controls),
	SND_SOC_DAPM_MUX("Left ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_monomux_controls),
	SND_SOC_DAPM_MUX("Right ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_monomux_controls),

	SND_SOC_DAPM_MUX("Left PGA Mux", WM8988_PWR1, 5, 0,
		&wm8988_left_pga_controls),
	SND_SOC_DAPM_MUX("Right PGA Mux", WM8988_PWR1, 4, 0,
		&wm8988_right_pga_controls),

	SND_SOC_DAPM_MUX("Left Line Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_left_line_controls),
	SND_SOC_DAPM_MUX("Right Line Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_right_line_controls),

	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8988_PWR1, 2, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8988_PWR1, 3, 0),

	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", WM8988_PWR2, 7, 0),
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", WM8988_PWR2, 8, 0),

	SND_SOC_DAPM_MIXER("Left Mixer", SND_SOC_NOPM, 0, 0,
		&wm8988_left_mixer_controls[0],
		ARRAY_SIZE(wm8988_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SND_SOC_NOPM, 0, 0,
		&wm8988_right_mixer_controls[0],
		ARRAY_SIZE(wm8988_right_mixer_controls)),

	SND_SOC_DAPM_PGA("Right Out 2", WM8988_PWR2, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left Out 2", WM8988_PWR2, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Out 1", WM8988_PWR2, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left Out 1", WM8988_PWR2, 6, 0, शून्य, 0),

	SND_SOC_DAPM_POST("LRC control", wm8988_lrc_control),

	SND_SOC_DAPM_OUTPUT("LOUT1"),
	SND_SOC_DAPM_OUTPUT("ROUT1"),
	SND_SOC_DAPM_OUTPUT("LOUT2"),
	SND_SOC_DAPM_OUTPUT("ROUT2"),
	SND_SOC_DAPM_OUTPUT("VREF"),

	SND_SOC_DAPM_INPUT("LINPUT1"),
	SND_SOC_DAPM_INPUT("LINPUT2"),
	SND_SOC_DAPM_INPUT("RINPUT1"),
	SND_SOC_DAPM_INPUT("RINPUT2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8988_dapm_routes[] = अणु

	अणु "Left Line Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Left Line Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Left Line Mux", "PGA", "Left PGA Mux" पूर्ण,
	अणु "Left Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Right Line Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Right Line Mux", "Line 2", "RINPUT2" पूर्ण,
	अणु "Right Line Mux", "PGA", "Right PGA Mux" पूर्ण,
	अणु "Right Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Left PGA Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Left PGA Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Left PGA Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Right PGA Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Right PGA Mux", "Line 2", "RINPUT2" पूर्ण,
	अणु "Right PGA Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Differential Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Differential Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Differential Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Differential Mux", "Line 2", "RINPUT2" पूर्ण,

	अणु "Left ADC Mux", "Stereo", "Left PGA Mux" पूर्ण,
	अणु "Left ADC Mux", "Mono (Left)", "Left PGA Mux" पूर्ण,
	अणु "Left ADC Mux", "Digital Mono", "Left PGA Mux" पूर्ण,

	अणु "Right ADC Mux", "Stereo", "Right PGA Mux" पूर्ण,
	अणु "Right ADC Mux", "Mono (Right)", "Right PGA Mux" पूर्ण,
	अणु "Right ADC Mux", "Digital Mono", "Right PGA Mux" पूर्ण,

	अणु "Left ADC", शून्य, "Left ADC Mux" पूर्ण,
	अणु "Right ADC", शून्य, "Right ADC Mux" पूर्ण,

	अणु "Left Line Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Left Line Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Left Line Mux", "PGA", "Left PGA Mux" पूर्ण,
	अणु "Left Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Right Line Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Right Line Mux", "Line 2", "RINPUT2" पूर्ण,
	अणु "Right Line Mux", "PGA", "Right PGA Mux" पूर्ण,
	अणु "Right Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Left Mixer", "Playback Switch", "Left DAC" पूर्ण,
	अणु "Left Mixer", "Left Bypass Switch", "Left Line Mux" पूर्ण,
	अणु "Left Mixer", "Right Playback Switch", "Right DAC" पूर्ण,
	अणु "Left Mixer", "Right Bypass Switch", "Right Line Mux" पूर्ण,

	अणु "Right Mixer", "Left Playback Switch", "Left DAC" पूर्ण,
	अणु "Right Mixer", "Left Bypass Switch", "Left Line Mux" पूर्ण,
	अणु "Right Mixer", "Playback Switch", "Right DAC" पूर्ण,
	अणु "Right Mixer", "Right Bypass Switch", "Right Line Mux" पूर्ण,

	अणु "Left Out 1", शून्य, "Left Mixer" पूर्ण,
	अणु "LOUT1", शून्य, "Left Out 1" पूर्ण,
	अणु "Right Out 1", शून्य, "Right Mixer" पूर्ण,
	अणु "ROUT1", शून्य, "Right Out 1" पूर्ण,

	अणु "Left Out 2", शून्य, "Left Mixer" पूर्ण,
	अणु "LOUT2", शून्य, "Left Out 2" पूर्ण,
	अणु "Right Out 2", शून्य, "Right Mixer" पूर्ण,
	अणु "ROUT2", शून्य, "Right Out 2" पूर्ण,
पूर्ण;

काष्ठा _coeff_भाग अणु
	u32 mclk;
	u32 rate;
	u16 fs;
	u8 sr:5;
	u8 usb:1;
पूर्ण;

/* codec hअगरi mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	/* 8k */
	अणु12288000, 8000, 1536, 0x6, 0x0पूर्ण,
	अणु11289600, 8000, 1408, 0x16, 0x0पूर्ण,
	अणु18432000, 8000, 2304, 0x7, 0x0पूर्ण,
	अणु16934400, 8000, 2112, 0x17, 0x0पूर्ण,
	अणु12000000, 8000, 1500, 0x6, 0x1पूर्ण,

	/* 11.025k */
	अणु11289600, 11025, 1024, 0x18, 0x0पूर्ण,
	अणु16934400, 11025, 1536, 0x19, 0x0पूर्ण,
	अणु12000000, 11025, 1088, 0x19, 0x1पूर्ण,

	/* 16k */
	अणु12288000, 16000, 768, 0xa, 0x0पूर्ण,
	अणु18432000, 16000, 1152, 0xb, 0x0पूर्ण,
	अणु12000000, 16000, 750, 0xa, 0x1पूर्ण,

	/* 22.05k */
	अणु11289600, 22050, 512, 0x1a, 0x0पूर्ण,
	अणु16934400, 22050, 768, 0x1b, 0x0पूर्ण,
	अणु12000000, 22050, 544, 0x1b, 0x1पूर्ण,

	/* 32k */
	अणु12288000, 32000, 384, 0xc, 0x0पूर्ण,
	अणु18432000, 32000, 576, 0xd, 0x0पूर्ण,
	अणु12000000, 32000, 375, 0xa, 0x1पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, 256, 0x10, 0x0पूर्ण,
	अणु16934400, 44100, 384, 0x11, 0x0पूर्ण,
	अणु12000000, 44100, 272, 0x11, 0x1पूर्ण,

	/* 48k */
	अणु12288000, 48000, 256, 0x0, 0x0पूर्ण,
	अणु18432000, 48000, 384, 0x1, 0x0पूर्ण,
	अणु12000000, 48000, 250, 0x0, 0x1पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, 128, 0x1e, 0x0पूर्ण,
	अणु16934400, 88200, 192, 0x1f, 0x0पूर्ण,
	अणु12000000, 88200, 136, 0x1f, 0x1पूर्ण,

	/* 96k */
	अणु12288000, 96000, 128, 0xe, 0x0पूर्ण,
	अणु18432000, 96000, 192, 0xf, 0x0पूर्ण,
	अणु12000000, 96000, 125, 0xe, 0x1पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate == rate && coeff_भाग[i].mclk == mclk)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* The set of rates we can generate from the above क्रम each SYSCLK */

अटल स्थिर अचिन्हित पूर्णांक rates_12288[] = अणु
	8000, 12000, 16000, 24000, 32000, 48000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_12288 = अणु
	.count	= ARRAY_SIZE(rates_12288),
	.list	= rates_12288,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_112896[] = अणु
	8000, 11025, 22050, 44100,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_112896 = अणु
	.count	= ARRAY_SIZE(rates_112896),
	.list	= rates_112896,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_12[] = अणु
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 41100, 48000,
	48000, 88235, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_12 = अणु
	.count	= ARRAY_SIZE(rates_12),
	.list	= rates_12,
पूर्ण;

/*
 * Note that this should be called from init rather than from hw_params.
 */
अटल पूर्णांक wm8988_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8988_priv *wm8988 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल 11289600:
	हाल 18432000:
	हाल 22579200:
	हाल 36864000:
		wm8988->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_112896;
		wm8988->sysclk = freq;
		वापस 0;

	हाल 12288000:
	हाल 16934400:
	हाल 24576000:
	हाल 33868800:
		wm8988->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_12288;
		wm8988->sysclk = freq;
		वापस 0;

	हाल 12000000:
	हाल 24000000:
		wm8988->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_12;
		wm8988->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8988_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace = 0x0040;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= 0x0013;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x0090;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x0080;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x0010;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8988_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8988_pcm_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8988_priv *wm8988 = snd_soc_component_get_drvdata(component);

	/* The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC - enक्रमce this.
	 */
	अगर (!wm8988->sysclk) अणु
		dev_err(component->dev,
			"No MCLK configured, call set_sysclk() on init\n");
		वापस -EINVAL;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   wm8988->sysclk_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8988_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8988_priv *wm8988 = snd_soc_component_get_drvdata(component);
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8988_IFACE) & 0x1f3;
	u16 srate = snd_soc_component_पढ़ो(component, WM8988_SRATE) & 0x180;
	पूर्णांक coeff;

	coeff = get_coeff(wm8988->sysclk, params_rate(params));
	अगर (coeff < 0) अणु
		coeff = get_coeff(wm8988->sysclk / 2, params_rate(params));
		srate |= 0x40;
	पूर्ण
	अगर (coeff < 0) अणु
		dev_err(component->dev,
			"Unable to configure sample rate %dHz with %dHz MCLK\n",
			params_rate(params), wm8988->sysclk);
		वापस coeff;
	पूर्ण

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x0004;
		अवरोध;
	हाल 24:
		अगरace |= 0x0008;
		अवरोध;
	हाल 32:
		अगरace |= 0x000c;
		अवरोध;
	पूर्ण

	/* set अगरace & srate */
	snd_soc_component_ग_लिखो(component, WM8988_IFACE, अगरace);
	अगर (coeff >= 0)
		snd_soc_component_ग_लिखो(component, WM8988_SRATE, srate |
			(coeff_भाग[coeff].sr << 1) | coeff_भाग[coeff].usb);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8988_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8988_ADCDAC) & 0xfff7;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8988_ADCDAC, mute_reg | 0x8);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8988_ADCDAC, mute_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8988_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8988_priv *wm8988 = snd_soc_component_get_drvdata(component);
	u16 pwr_reg = snd_soc_component_पढ़ो(component, WM8988_PWR1) & ~0x1c1;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VREF, VMID=2x50k, digital enabled */
		snd_soc_component_ग_लिखो(component, WM8988_PWR1, pwr_reg | 0x00c0);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_sync(wm8988->regmap);

			/* VREF, VMID=2x5k */
			snd_soc_component_ग_लिखो(component, WM8988_PWR1, pwr_reg | 0x1c1);

			/* Charge caps */
			msleep(100);
		पूर्ण

		/* VREF, VMID=2*500k, digital stopped */
		snd_soc_component_ग_लिखो(component, WM8988_PWR1, pwr_reg | 0x0141);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, WM8988_PWR1, 0x0000);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8988_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8988_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8988_ops = अणु
	.startup = wm8988_pcm_startup,
	.hw_params = wm8988_pcm_hw_params,
	.set_fmt = wm8988_set_dai_fmt,
	.set_sysclk = wm8988_set_dai_sysclk,
	.mute_stream = wm8988_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8988_dai = अणु
	.name = "wm8988-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8988_RATES,
		.क्रमmats = WM8988_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8988_RATES,
		.क्रमmats = WM8988_FORMATS,
	 पूर्ण,
	.ops = &wm8988_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8988_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;

	ret = wm8988_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	/* set the update bits (we always update left then right) */
	snd_soc_component_update_bits(component, WM8988_RADC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_RDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_ROUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_ROUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_RINVOL, 0x0100, 0x0100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8988 = अणु
	.probe			= wm8988_probe,
	.set_bias_level		= wm8988_set_bias_level,
	.controls		= wm8988_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8988_snd_controls),
	.dapm_widमाला_लो		= wm8988_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8988_dapm_widमाला_लो),
	.dapm_routes		= wm8988_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8988_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8988_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8988_LPPB,
	.ग_लिखोable_reg = wm8988_ग_लिखोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8988_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8988_reg_शेषs),
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8988_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8988_priv *wm8988;
	पूर्णांक ret;

	wm8988 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8988_priv),
			      GFP_KERNEL);
	अगर (wm8988 == शून्य)
		वापस -ENOMEM;

	wm8988->regmap = devm_regmap_init_spi(spi, &wm8988_regmap);
	अगर (IS_ERR(wm8988->regmap)) अणु
		ret = PTR_ERR(wm8988->regmap);
		dev_err(&spi->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, wm8988);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8988, &wm8988_dai, 1);
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8988_spi_driver = अणु
	.driver = अणु
		.name	= "wm8988",
	पूर्ण,
	.probe		= wm8988_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8988_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8988_priv *wm8988;
	पूर्णांक ret;

	wm8988 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8988_priv),
			      GFP_KERNEL);
	अगर (wm8988 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8988);

	wm8988->regmap = devm_regmap_init_i2c(i2c, &wm8988_regmap);
	अगर (IS_ERR(wm8988->regmap)) अणु
		ret = PTR_ERR(wm8988->regmap);
		dev_err(&i2c->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8988, &wm8988_dai, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8988_i2c_id[] = अणु
	अणु "wm8988", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8988_i2c_id);

अटल काष्ठा i2c_driver wm8988_i2c_driver = अणु
	.driver = अणु
		.name = "wm8988",
	पूर्ण,
	.probe =    wm8988_i2c_probe,
	.id_table = wm8988_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8988_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8988_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8988 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8988_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8988 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8988_modinit);

अटल व्योम __निकास wm8988_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8988_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8988_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8988_निकास);


MODULE_DESCRIPTION("ASoC WM8988 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
