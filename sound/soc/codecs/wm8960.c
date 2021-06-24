<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8960.c  --  WM8960 ALSA SoC Audio driver
 *
 * Copyright 2007-11 Wolfson Microelectronics, plc
 *
 * Author: Liam Girdwood
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wm8960.h>

#समावेश "wm8960.h"

/* R25 - Power 1 */
#घोषणा WM8960_VMID_MASK 0x180
#घोषणा WM8960_VREF      0x40

/* R26 - Power 2 */
#घोषणा WM8960_PWR2_LOUT1	0x40
#घोषणा WM8960_PWR2_ROUT1	0x20
#घोषणा WM8960_PWR2_OUT3	0x02

/* R28 - Anti-pop 1 */
#घोषणा WM8960_POBCTRL   0x80
#घोषणा WM8960_BUFDCOPEN 0x10
#घोषणा WM8960_BUFIOEN   0x08
#घोषणा WM8960_SOFT_ST   0x04
#घोषणा WM8960_HPSTBY    0x01

/* R29 - Anti-pop 2 */
#घोषणा WM8960_DISOP     0x40
#घोषणा WM8960_DRES_MASK 0x30

अटल bool is_pll_freq_available(अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक target);
अटल पूर्णांक wm8960_set_pll(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out);
/*
 * wm8960 रेजिस्टर cache
 * We can't पढ़ो the WM8960 रेजिस्टर space when we are
 * using 2 wire क्रम device control, so we cache them instead.
 */
अटल स्थिर काष्ठा reg_शेष wm8960_reg_शेषs[] = अणु
	अणु  0x0, 0x00a7 पूर्ण,
	अणु  0x1, 0x00a7 पूर्ण,
	अणु  0x2, 0x0000 पूर्ण,
	अणु  0x3, 0x0000 पूर्ण,
	अणु  0x4, 0x0000 पूर्ण,
	अणु  0x5, 0x0008 पूर्ण,
	अणु  0x6, 0x0000 पूर्ण,
	अणु  0x7, 0x000a पूर्ण,
	अणु  0x8, 0x01c0 पूर्ण,
	अणु  0x9, 0x0000 पूर्ण,
	अणु  0xa, 0x00ff पूर्ण,
	अणु  0xb, 0x00ff पूर्ण,

	अणु 0x10, 0x0000 पूर्ण,
	अणु 0x11, 0x007b पूर्ण,
	अणु 0x12, 0x0100 पूर्ण,
	अणु 0x13, 0x0032 पूर्ण,
	अणु 0x14, 0x0000 पूर्ण,
	अणु 0x15, 0x00c3 पूर्ण,
	अणु 0x16, 0x00c3 पूर्ण,
	अणु 0x17, 0x01c0 पूर्ण,
	अणु 0x18, 0x0000 पूर्ण,
	अणु 0x19, 0x0000 पूर्ण,
	अणु 0x1a, 0x0000 पूर्ण,
	अणु 0x1b, 0x0000 पूर्ण,
	अणु 0x1c, 0x0000 पूर्ण,
	अणु 0x1d, 0x0000 पूर्ण,

	अणु 0x20, 0x0100 पूर्ण,
	अणु 0x21, 0x0100 पूर्ण,
	अणु 0x22, 0x0050 पूर्ण,

	अणु 0x25, 0x0050 पूर्ण,
	अणु 0x26, 0x0000 पूर्ण,
	अणु 0x27, 0x0000 पूर्ण,
	अणु 0x28, 0x0000 पूर्ण,
	अणु 0x29, 0x0000 पूर्ण,
	अणु 0x2a, 0x0040 पूर्ण,
	अणु 0x2b, 0x0000 पूर्ण,
	अणु 0x2c, 0x0000 पूर्ण,
	अणु 0x2d, 0x0050 पूर्ण,
	अणु 0x2e, 0x0050 पूर्ण,
	अणु 0x2f, 0x0000 पूर्ण,
	अणु 0x30, 0x0002 पूर्ण,
	अणु 0x31, 0x0037 पूर्ण,

	अणु 0x33, 0x0080 पूर्ण,
	अणु 0x34, 0x0008 पूर्ण,
	अणु 0x35, 0x0031 पूर्ण,
	अणु 0x36, 0x0026 पूर्ण,
	अणु 0x37, 0x00e9 पूर्ण,
पूर्ण;

अटल bool wm8960_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8960_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

काष्ठा wm8960_priv अणु
	काष्ठा clk *mclk;
	काष्ठा regmap *regmap;
	पूर्णांक (*set_bias_level)(काष्ठा snd_soc_component *,
			      क्रमागत snd_soc_bias_level level);
	काष्ठा snd_soc_dapm_widget *lout1;
	काष्ठा snd_soc_dapm_widget *rout1;
	काष्ठा snd_soc_dapm_widget *out3;
	bool deemph;
	पूर्णांक lrclk;
	पूर्णांक bclk;
	पूर्णांक sysclk;
	पूर्णांक clk_id;
	पूर्णांक freq_in;
	bool is_stream_in_use[2];
	काष्ठा wm8960_data pdata;
पूर्ण;

#घोषणा wm8960_reset(c)	regmap_ग_लिखो(c, WM8960_RESET, 0)

/* क्रमागतerated controls */
अटल स्थिर अक्षर *wm8960_polarity[] = अणु"No Inversion", "Left Inverted",
	"Right Inverted", "Stereo Inversion"पूर्ण;
अटल स्थिर अक्षर *wm8960_3d_upper_cutoff[] = अणु"High", "Low"पूर्ण;
अटल स्थिर अक्षर *wm8960_3d_lower_cutoff[] = अणु"Low", "High"पूर्ण;
अटल स्थिर अक्षर *wm8960_alcfunc[] = अणु"Off", "Right", "Left", "Stereo"पूर्ण;
अटल स्थिर अक्षर *wm8960_alcmode[] = अणु"ALC", "Limiter"पूर्ण;
अटल स्थिर अक्षर *wm8960_adc_data_output_sel[] = अणु
	"Left Data = Left ADC;  Right Data = Right ADC",
	"Left Data = Left ADC;  Right Data = Left ADC",
	"Left Data = Right ADC; Right Data = Right ADC",
	"Left Data = Right ADC; Right Data = Left ADC",
पूर्ण;
अटल स्थिर अक्षर *wm8960_dmonomix[] = अणु"Stereo", "Mono"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8960_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(WM8960_DACCTL1, 5, 4, wm8960_polarity),
	SOC_ENUM_SINGLE(WM8960_DACCTL2, 5, 4, wm8960_polarity),
	SOC_ENUM_SINGLE(WM8960_3D, 6, 2, wm8960_3d_upper_cutoff),
	SOC_ENUM_SINGLE(WM8960_3D, 5, 2, wm8960_3d_lower_cutoff),
	SOC_ENUM_SINGLE(WM8960_ALC1, 7, 4, wm8960_alcfunc),
	SOC_ENUM_SINGLE(WM8960_ALC3, 8, 2, wm8960_alcmode),
	SOC_ENUM_SINGLE(WM8960_ADDCTL1, 2, 4, wm8960_adc_data_output_sel),
	SOC_ENUM_SINGLE(WM8960_ADDCTL1, 4, 2, wm8960_dmonomix),
पूर्ण;

अटल स्थिर पूर्णांक deemph_settings[] = अणु 0, 32000, 44100, 48000 पूर्ण;

अटल पूर्णांक wm8960_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, i, best;

	/* If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	अगर (wm8960->deemph) अणु
		best = 1;
		क्रम (i = 2; i < ARRAY_SIZE(deemph_settings); i++) अणु
			अगर (असल(deemph_settings[i] - wm8960->lrclk) <
			    असल(deemph_settings[best] - wm8960->lrclk))
				best = i;
		पूर्ण

		val = best << 1;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	वापस snd_soc_component_update_bits(component, WM8960_DACCTL1,
				   0x6, val);
पूर्ण

अटल पूर्णांक wm8960_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8960->deemph;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];

	अगर (deemph > 1)
		वापस -EINVAL;

	wm8960->deemph = deemph;

	वापस wm8960_set_deemph(component);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -9750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(bypass_tlv, -2100, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(lineinboost_tlv, -1500, 300, 1);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(micboost_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 1300, 0),
	2, 3, TLV_DB_SCALE_ITEM(2000, 900, 0),
);

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Capture Volume", WM8960_LINVOL, WM8960_RINVOL,
		 0, 63, 0, inpga_tlv),
SOC_DOUBLE_R("Capture Volume ZC Switch", WM8960_LINVOL, WM8960_RINVOL,
	6, 1, 0),
SOC_DOUBLE_R("Capture Switch", WM8960_LINVOL, WM8960_RINVOL,
	7, 1, 1),

SOC_SINGLE_TLV("Left Input Boost Mixer LINPUT3 Volume",
	       WM8960_INBMIX1, 4, 7, 0, lineinboost_tlv),
SOC_SINGLE_TLV("Left Input Boost Mixer LINPUT2 Volume",
	       WM8960_INBMIX1, 1, 7, 0, lineinboost_tlv),
SOC_SINGLE_TLV("Right Input Boost Mixer RINPUT3 Volume",
	       WM8960_INBMIX2, 4, 7, 0, lineinboost_tlv),
SOC_SINGLE_TLV("Right Input Boost Mixer RINPUT2 Volume",
	       WM8960_INBMIX2, 1, 7, 0, lineinboost_tlv),
SOC_SINGLE_TLV("Right Input Boost Mixer RINPUT1 Volume",
		WM8960_RINPATH, 4, 3, 0, micboost_tlv),
SOC_SINGLE_TLV("Left Input Boost Mixer LINPUT1 Volume",
		WM8960_LINPATH, 4, 3, 0, micboost_tlv),

SOC_DOUBLE_R_TLV("Playback Volume", WM8960_LDAC, WM8960_RDAC,
		 0, 255, 0, dac_tlv),

SOC_DOUBLE_R_TLV("Headphone Playback Volume", WM8960_LOUT1, WM8960_ROUT1,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Headphone Playback ZC Switch", WM8960_LOUT1, WM8960_ROUT1,
	7, 1, 0),

SOC_DOUBLE_R_TLV("Speaker Playback Volume", WM8960_LOUT2, WM8960_ROUT2,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Speaker Playback ZC Switch", WM8960_LOUT2, WM8960_ROUT2,
	7, 1, 0),
SOC_SINGLE("Speaker DC Volume", WM8960_CLASSD3, 3, 5, 0),
SOC_SINGLE("Speaker AC Volume", WM8960_CLASSD3, 0, 5, 0),

SOC_SINGLE("PCM Playback -6dB Switch", WM8960_DACCTL1, 7, 1, 0),
SOC_ENUM("ADC Polarity", wm8960_क्रमागत[0]),
SOC_SINGLE("ADC High Pass Filter Switch", WM8960_DACCTL1, 0, 1, 0),

SOC_ENUM("DAC Polarity", wm8960_क्रमागत[1]),
SOC_SINGLE_BOOL_EXT("DAC Deemphasis Switch", 0,
		    wm8960_get_deemph, wm8960_put_deemph),

SOC_ENUM("3D Filter Upper Cut-Off", wm8960_क्रमागत[2]),
SOC_ENUM("3D Filter Lower Cut-Off", wm8960_क्रमागत[3]),
SOC_SINGLE("3D Volume", WM8960_3D, 1, 15, 0),
SOC_SINGLE("3D Switch", WM8960_3D, 0, 1, 0),

SOC_ENUM("ALC Function", wm8960_क्रमागत[4]),
SOC_SINGLE("ALC Max Gain", WM8960_ALC1, 4, 7, 0),
SOC_SINGLE("ALC Target", WM8960_ALC1, 0, 15, 1),
SOC_SINGLE("ALC Min Gain", WM8960_ALC2, 4, 7, 0),
SOC_SINGLE("ALC Hold Time", WM8960_ALC2, 0, 15, 0),
SOC_ENUM("ALC Mode", wm8960_क्रमागत[5]),
SOC_SINGLE("ALC Decay", WM8960_ALC3, 4, 15, 0),
SOC_SINGLE("ALC Attack", WM8960_ALC3, 0, 15, 0),

SOC_SINGLE("Noise Gate Threshold", WM8960_NOISEG, 3, 31, 0),
SOC_SINGLE("Noise Gate Switch", WM8960_NOISEG, 0, 1, 0),

SOC_DOUBLE_R_TLV("ADC PCM Capture Volume", WM8960_LADC, WM8960_RADC,
	0, 255, 0, adc_tlv),

SOC_SINGLE_TLV("Left Output Mixer Boost Bypass Volume",
	       WM8960_BYPASS1, 4, 7, 1, bypass_tlv),
SOC_SINGLE_TLV("Left Output Mixer LINPUT3 Volume",
	       WM8960_LOUTMIX, 4, 7, 1, bypass_tlv),
SOC_SINGLE_TLV("Right Output Mixer Boost Bypass Volume",
	       WM8960_BYPASS2, 4, 7, 1, bypass_tlv),
SOC_SINGLE_TLV("Right Output Mixer RINPUT3 Volume",
	       WM8960_ROUTMIX, 4, 7, 1, bypass_tlv),

SOC_ENUM("ADC Data Output Select", wm8960_क्रमागत[6]),
SOC_ENUM("DAC Mono Mix", wm8960_क्रमागत[7]),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_lin_boost[] = अणु
SOC_DAPM_SINGLE("LINPUT2 Switch", WM8960_LINPATH, 6, 1, 0),
SOC_DAPM_SINGLE("LINPUT3 Switch", WM8960_LINPATH, 7, 1, 0),
SOC_DAPM_SINGLE("LINPUT1 Switch", WM8960_LINPATH, 8, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_lin[] = अणु
SOC_DAPM_SINGLE("Boost Switch", WM8960_LINPATH, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_rin_boost[] = अणु
SOC_DAPM_SINGLE("RINPUT2 Switch", WM8960_RINPATH, 6, 1, 0),
SOC_DAPM_SINGLE("RINPUT3 Switch", WM8960_RINPATH, 7, 1, 0),
SOC_DAPM_SINGLE("RINPUT1 Switch", WM8960_RINPATH, 8, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_rin[] = अणु
SOC_DAPM_SINGLE("Boost Switch", WM8960_RINPATH, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_loutput_mixer[] = अणु
SOC_DAPM_SINGLE("PCM Playback Switch", WM8960_LOUTMIX, 8, 1, 0),
SOC_DAPM_SINGLE("LINPUT3 Switch", WM8960_LOUTMIX, 7, 1, 0),
SOC_DAPM_SINGLE("Boost Bypass Switch", WM8960_BYPASS1, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_routput_mixer[] = अणु
SOC_DAPM_SINGLE("PCM Playback Switch", WM8960_ROUTMIX, 8, 1, 0),
SOC_DAPM_SINGLE("RINPUT3 Switch", WM8960_ROUTMIX, 7, 1, 0),
SOC_DAPM_SINGLE("Boost Bypass Switch", WM8960_BYPASS2, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8960_mono_out[] = अणु
SOC_DAPM_SINGLE("Left Switch", WM8960_MONOMIX1, 7, 1, 0),
SOC_DAPM_SINGLE("Right Switch", WM8960_MONOMIX2, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8960_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("LINPUT1"),
SND_SOC_DAPM_INPUT("RINPUT1"),
SND_SOC_DAPM_INPUT("LINPUT2"),
SND_SOC_DAPM_INPUT("RINPUT2"),
SND_SOC_DAPM_INPUT("LINPUT3"),
SND_SOC_DAPM_INPUT("RINPUT3"),

SND_SOC_DAPM_SUPPLY("MICB", WM8960_POWER1, 1, 0, शून्य, 0),

SND_SOC_DAPM_MIXER("Left Boost Mixer", WM8960_POWER1, 5, 0,
		   wm8960_lin_boost, ARRAY_SIZE(wm8960_lin_boost)),
SND_SOC_DAPM_MIXER("Right Boost Mixer", WM8960_POWER1, 4, 0,
		   wm8960_rin_boost, ARRAY_SIZE(wm8960_rin_boost)),

SND_SOC_DAPM_MIXER("Left Input Mixer", WM8960_POWER3, 5, 0,
		   wm8960_lin, ARRAY_SIZE(wm8960_lin)),
SND_SOC_DAPM_MIXER("Right Input Mixer", WM8960_POWER3, 4, 0,
		   wm8960_rin, ARRAY_SIZE(wm8960_rin)),

SND_SOC_DAPM_ADC("Left ADC", "Capture", WM8960_POWER1, 3, 0),
SND_SOC_DAPM_ADC("Right ADC", "Capture", WM8960_POWER1, 2, 0),

SND_SOC_DAPM_DAC("Left DAC", "Playback", WM8960_POWER2, 8, 0),
SND_SOC_DAPM_DAC("Right DAC", "Playback", WM8960_POWER2, 7, 0),

SND_SOC_DAPM_MIXER("Left Output Mixer", WM8960_POWER3, 3, 0,
	&wm8960_loutput_mixer[0],
	ARRAY_SIZE(wm8960_loutput_mixer)),
SND_SOC_DAPM_MIXER("Right Output Mixer", WM8960_POWER3, 2, 0,
	&wm8960_routput_mixer[0],
	ARRAY_SIZE(wm8960_routput_mixer)),

SND_SOC_DAPM_PGA("LOUT1 PGA", WM8960_POWER2, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ROUT1 PGA", WM8960_POWER2, 5, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Left Speaker PGA", WM8960_POWER2, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Speaker PGA", WM8960_POWER2, 3, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Right Speaker Output", WM8960_CLASSD1, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Left Speaker Output", WM8960_CLASSD1, 6, 0, शून्य, 0),

SND_SOC_DAPM_OUTPUT("SPK_LP"),
SND_SOC_DAPM_OUTPUT("SPK_LN"),
SND_SOC_DAPM_OUTPUT("HP_L"),
SND_SOC_DAPM_OUTPUT("HP_R"),
SND_SOC_DAPM_OUTPUT("SPK_RP"),
SND_SOC_DAPM_OUTPUT("SPK_RN"),
SND_SOC_DAPM_OUTPUT("OUT3"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8960_dapm_widमाला_लो_out3[] = अणु
SND_SOC_DAPM_MIXER("Mono Output Mixer", WM8960_POWER2, 1, 0,
	&wm8960_mono_out[0],
	ARRAY_SIZE(wm8960_mono_out)),
पूर्ण;

/* Represent OUT3 as a PGA so that it माला_लो turned on with LOUT1/ROUT1 */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm8960_dapm_widमाला_लो_capless[] = अणु
SND_SOC_DAPM_PGA("OUT3 VMID", WM8960_POWER2, 1, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "Left Boost Mixer", "LINPUT1 Switch", "LINPUT1" पूर्ण,
	अणु "Left Boost Mixer", "LINPUT2 Switch", "LINPUT2" पूर्ण,
	अणु "Left Boost Mixer", "LINPUT3 Switch", "LINPUT3" पूर्ण,

	अणु "Left Input Mixer", "Boost Switch", "Left Boost Mixer" पूर्ण,
	अणु "Left Input Mixer", "Boost Switch", "LINPUT1" पूर्ण,  /* Really Boost Switch */
	अणु "Left Input Mixer", शून्य, "LINPUT2" पूर्ण,
	अणु "Left Input Mixer", शून्य, "LINPUT3" पूर्ण,

	अणु "Right Boost Mixer", "RINPUT1 Switch", "RINPUT1" पूर्ण,
	अणु "Right Boost Mixer", "RINPUT2 Switch", "RINPUT2" पूर्ण,
	अणु "Right Boost Mixer", "RINPUT3 Switch", "RINPUT3" पूर्ण,

	अणु "Right Input Mixer", "Boost Switch", "Right Boost Mixer" पूर्ण,
	अणु "Right Input Mixer", "Boost Switch", "RINPUT1" पूर्ण,  /* Really Boost Switch */
	अणु "Right Input Mixer", शून्य, "RINPUT2" पूर्ण,
	अणु "Right Input Mixer", शून्य, "RINPUT3" पूर्ण,

	अणु "Left ADC", शून्य, "Left Input Mixer" पूर्ण,
	अणु "Right ADC", शून्य, "Right Input Mixer" पूर्ण,

	अणु "Left Output Mixer", "LINPUT3 Switch", "LINPUT3" पूर्ण,
	अणु "Left Output Mixer", "Boost Bypass Switch", "Left Boost Mixer" पूर्ण,
	अणु "Left Output Mixer", "PCM Playback Switch", "Left DAC" पूर्ण,

	अणु "Right Output Mixer", "RINPUT3 Switch", "RINPUT3" पूर्ण,
	अणु "Right Output Mixer", "Boost Bypass Switch", "Right Boost Mixer" पूर्ण,
	अणु "Right Output Mixer", "PCM Playback Switch", "Right DAC" पूर्ण,

	अणु "LOUT1 PGA", शून्य, "Left Output Mixer" पूर्ण,
	अणु "ROUT1 PGA", शून्य, "Right Output Mixer" पूर्ण,

	अणु "HP_L", शून्य, "LOUT1 PGA" पूर्ण,
	अणु "HP_R", शून्य, "ROUT1 PGA" पूर्ण,

	अणु "Left Speaker PGA", शून्य, "Left Output Mixer" पूर्ण,
	अणु "Right Speaker PGA", शून्य, "Right Output Mixer" पूर्ण,

	अणु "Left Speaker Output", शून्य, "Left Speaker PGA" पूर्ण,
	अणु "Right Speaker Output", शून्य, "Right Speaker PGA" पूर्ण,

	अणु "SPK_LN", शून्य, "Left Speaker Output" पूर्ण,
	अणु "SPK_LP", शून्य, "Left Speaker Output" पूर्ण,
	अणु "SPK_RN", शून्य, "Right Speaker Output" पूर्ण,
	अणु "SPK_RP", शून्य, "Right Speaker Output" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_paths_out3[] = अणु
	अणु "Mono Output Mixer", "Left Switch", "Left Output Mixer" पूर्ण,
	अणु "Mono Output Mixer", "Right Switch", "Right Output Mixer" पूर्ण,

	अणु "OUT3", शून्य, "Mono Output Mixer", पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_paths_capless[] = अणु
	अणु "HP_L", शून्य, "OUT3 VMID" पूर्ण,
	अणु "HP_R", शून्य, "OUT3 VMID" पूर्ण,

	अणु "OUT3 VMID", शून्य, "Left Output Mixer" पूर्ण,
	अणु "OUT3 VMID", शून्य, "Right Output Mixer" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8960_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8960_data *pdata = &wm8960->pdata;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा snd_soc_dapm_widget *w;

	snd_soc_dapm_new_controls(dapm, wm8960_dapm_widमाला_लो,
				  ARRAY_SIZE(wm8960_dapm_widमाला_लो));

	snd_soc_dapm_add_routes(dapm, audio_paths, ARRAY_SIZE(audio_paths));

	/* In capless mode OUT3 is used to provide VMID क्रम the
	 * headphone outमाला_दो, otherwise it is used as a mono mixer.
	 */
	अगर (pdata && pdata->capless) अणु
		snd_soc_dapm_new_controls(dapm, wm8960_dapm_widमाला_लो_capless,
					  ARRAY_SIZE(wm8960_dapm_widमाला_लो_capless));

		snd_soc_dapm_add_routes(dapm, audio_paths_capless,
					ARRAY_SIZE(audio_paths_capless));
	पूर्ण अन्यथा अणु
		snd_soc_dapm_new_controls(dapm, wm8960_dapm_widमाला_लो_out3,
					  ARRAY_SIZE(wm8960_dapm_widमाला_लो_out3));

		snd_soc_dapm_add_routes(dapm, audio_paths_out3,
					ARRAY_SIZE(audio_paths_out3));
	पूर्ण

	/* We need to घातer up the headphone output stage out of
	 * sequence क्रम capless mode.  To save scanning the widget
	 * list each समय to find the desired घातer state करो so now
	 * and save the result.
	 */
	list_क्रम_each_entry(w, &component->card->widमाला_लो, list) अणु
		अगर (w->dapm != dapm)
			जारी;
		अगर (म_भेद(w->name, "LOUT1 PGA") == 0)
			wm8960->lout1 = w;
		अगर (म_भेद(w->name, "ROUT1 PGA") == 0)
			wm8960->rout1 = w;
		अगर (म_भेद(w->name, "OUT3 VMID") == 0)
			wm8960->out3 = w;
	पूर्ण
	
	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace |= 0x0040;
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

	/* set अगरace */
	snd_soc_component_ग_लिखो(component, WM8960_IFACE1, अगरace);
	वापस 0;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक rate;
	अचिन्हित पूर्णांक val;
पूर्ण alc_rates[] = अणु
	अणु 48000, 0 पूर्ण,
	अणु 44100, 0 पूर्ण,
	अणु 32000, 1 पूर्ण,
	अणु 22050, 2 पूर्ण,
	अणु 24000, 2 पूर्ण,
	अणु 16000, 3 पूर्ण,
	अणु 11025, 4 पूर्ण,
	अणु 12000, 4 पूर्ण,
	अणु  8000, 5 पूर्ण,
पूर्ण;

/* -1 क्रम reserved value */
अटल स्थिर पूर्णांक sysclk_भागs[] = अणु 1, -1, 2, -1 पूर्ण;

/* Multiply 256 क्रम पूर्णांकernal 256 भाग */
अटल स्थिर पूर्णांक dac_भागs[] = अणु 256, 384, 512, 768, 1024, 1408, 1536 पूर्ण;

/* Multiply 10 to eliminate decimials */
अटल स्थिर पूर्णांक bclk_भागs[] = अणु
	10, 15, 20, 30, 40, 55, 60, 80, 110,
	120, 160, 220, 240, 320, 320, 320
पूर्ण;

/**
 * wm8960_configure_sysclk - checks अगर there is a sysclk frequency available
 *	The sysclk must be chosen such that:
 *		- sysclk     = MCLK / sysclk_भागs
 *		- lrclk      = sysclk / dac_भागs
 *		- 10 * bclk  = sysclk / bclk_भागs
 *
 * @wm8960: codec निजी data
 * @mclk: MCLK used to derive sysclk
 * @sysclk_idx: sysclk_भागs index क्रम found sysclk
 * @dac_idx: dac_भागs index क्रम found lrclk
 * @bclk_idx: bclk_भागs index क्रम found bclk
 *
 * Returns:
 *  -1, in हाल no sysclk frequency available found
 * >=0, in हाल we could derive bclk and lrclk from sysclk using
 *      (@sysclk_idx, @dac_idx, @bclk_idx) भागiders
 */
अटल
पूर्णांक wm8960_configure_sysclk(काष्ठा wm8960_priv *wm8960, पूर्णांक mclk,
			    पूर्णांक *sysclk_idx, पूर्णांक *dac_idx, पूर्णांक *bclk_idx)
अणु
	पूर्णांक sysclk, bclk, lrclk;
	पूर्णांक i, j, k;
	पूर्णांक dअगरf;

	/* marker क्रम no match */
	*bclk_idx = -1;

	bclk = wm8960->bclk;
	lrclk = wm8960->lrclk;

	/* check अगर the sysclk frequency is available. */
	क्रम (i = 0; i < ARRAY_SIZE(sysclk_भागs); ++i) अणु
		अगर (sysclk_भागs[i] == -1)
			जारी;
		sysclk = mclk / sysclk_भागs[i];
		क्रम (j = 0; j < ARRAY_SIZE(dac_भागs); ++j) अणु
			अगर (sysclk != dac_भागs[j] * lrclk)
				जारी;
			क्रम (k = 0; k < ARRAY_SIZE(bclk_भागs); ++k) अणु
				dअगरf = sysclk - bclk * bclk_भागs[k] / 10;
				अगर (dअगरf == 0) अणु
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (k != ARRAY_SIZE(bclk_भागs))
				अवरोध;
		पूर्ण
		अगर (j != ARRAY_SIZE(dac_भागs))
			अवरोध;
	पूर्ण
	वापस *bclk_idx;
पूर्ण

/**
 * wm8960_configure_pll - checks अगर there is a PLL out frequency available
 *	The PLL out frequency must be chosen such that:
 *		- sysclk      = lrclk * dac_भागs
 *		- freq_out    = sysclk * sysclk_भागs
 *		- 10 * sysclk = bclk * bclk_भागs
 *
 * 	If we cannot find an exact match क्रम (sysclk, lrclk, bclk)
 * 	triplet, we relax the bclk such that bclk is chosen as the
 * 	बंदst available frequency greater than expected bclk.
 *
 * @component: component काष्ठाure
 * @freq_in: input frequency used to derive freq out via PLL
 * @sysclk_idx: sysclk_भागs index क्रम found sysclk
 * @dac_idx: dac_भागs index क्रम found lrclk
 * @bclk_idx: bclk_भागs index क्रम found bclk
 *
 * Returns:
 * < 0, in हाल no PLL frequency out available was found
 * >=0, in हाल we could derive bclk, lrclk, sysclk from PLL out using
 *      (@sysclk_idx, @dac_idx, @bclk_idx) भागiders
 */
अटल
पूर्णांक wm8960_configure_pll(काष्ठा snd_soc_component *component, पूर्णांक freq_in,
			 पूर्णांक *sysclk_idx, पूर्णांक *dac_idx, पूर्णांक *bclk_idx)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	पूर्णांक sysclk, bclk, lrclk, freq_out;
	पूर्णांक dअगरf, बंदst, best_freq_out;
	पूर्णांक i, j, k;

	bclk = wm8960->bclk;
	lrclk = wm8960->lrclk;
	बंदst = freq_in;

	best_freq_out = -EINVAL;
	*sysclk_idx = *dac_idx = *bclk_idx = -1;

	/*
	 * From Datasheet, the PLL perक्रमms best when f2 is between
	 * 90MHz and 100MHz, the desired sysclk output is 11.2896MHz
	 * or 12.288MHz, then sysclkभाग = 2 is the best choice.
	 * So search sysclk_भागs from 2 to 1 other than from 1 to 2.
	 */
	क्रम (i = ARRAY_SIZE(sysclk_भागs) - 1; i >= 0; --i) अणु
		अगर (sysclk_भागs[i] == -1)
			जारी;
		क्रम (j = 0; j < ARRAY_SIZE(dac_भागs); ++j) अणु
			sysclk = lrclk * dac_भागs[j];
			freq_out = sysclk * sysclk_भागs[i];

			क्रम (k = 0; k < ARRAY_SIZE(bclk_भागs); ++k) अणु
				अगर (!is_pll_freq_available(freq_in, freq_out))
					जारी;

				dअगरf = sysclk - bclk * bclk_भागs[k] / 10;
				अगर (dअगरf == 0) अणु
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					वापस freq_out;
				पूर्ण
				अगर (dअगरf > 0 && बंदst > dअगरf) अणु
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					बंदst = dअगरf;
					best_freq_out = freq_out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस best_freq_out;
पूर्ण
अटल पूर्णांक wm8960_configure_घड़ीing(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	पूर्णांक freq_out, freq_in;
	u16 अगरace1 = snd_soc_component_पढ़ो(component, WM8960_IFACE1);
	पूर्णांक i, j, k;
	पूर्णांक ret;

	अगर (!(अगरace1 & (1<<6))) अणु
		dev_dbg(component->dev,
			"Codec is slave mode, no need to configure clock\n");
		वापस 0;
	पूर्ण

	अगर (wm8960->clk_id != WM8960_SYSCLK_MCLK && !wm8960->freq_in) अणु
		dev_err(component->dev, "No MCLK configured\n");
		वापस -EINVAL;
	पूर्ण

	freq_in = wm8960->freq_in;
	/*
	 * If it's sysclk स्वतः mode, check अगर the MCLK can provide sysclk or
	 * not. If MCLK can provide sysclk, using MCLK to provide sysclk
	 * directly. Otherwise, स्वतः select a available pll out frequency
	 * and set PLL.
	 */
	अगर (wm8960->clk_id == WM8960_SYSCLK_AUTO) अणु
		/* disable the PLL and using MCLK to provide sysclk */
		wm8960_set_pll(component, 0, 0);
		freq_out = freq_in;
	पूर्ण अन्यथा अगर (wm8960->sysclk) अणु
		freq_out = wm8960->sysclk;
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "No SYSCLK configured\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wm8960->clk_id != WM8960_SYSCLK_PLL) अणु
		ret = wm8960_configure_sysclk(wm8960, freq_out, &i, &j, &k);
		अगर (ret >= 0) अणु
			जाओ configure_घड़ी;
		पूर्ण अन्यथा अगर (wm8960->clk_id != WM8960_SYSCLK_AUTO) अणु
			dev_err(component->dev, "failed to configure clock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	freq_out = wm8960_configure_pll(component, freq_in, &i, &j, &k);
	अगर (freq_out < 0) अणु
		dev_err(component->dev, "failed to configure clock via PLL\n");
		वापस freq_out;
	पूर्ण
	wm8960_set_pll(component, freq_in, freq_out);

configure_घड़ी:
	/* configure sysclk घड़ी */
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 3 << 1, i << 1);

	/* configure frame घड़ी */
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 0x7 << 3, j << 3);
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 0x7 << 6, j << 6);

	/* configure bit घड़ी */
	snd_soc_component_update_bits(component, WM8960_CLOCK2, 0xf, k);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8960_IFACE1) & 0xfff3;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक i;

	wm8960->bclk = snd_soc_params_to_bclk(params);
	अगर (params_channels(params) == 1)
		wm8960->bclk *= 2;

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
		/* right justअगरy mode करोes not support 32 word length */
		अगर ((अगरace & 0x3) != 0) अणु
			अगरace |= 0x000c;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		dev_err(component->dev, "unsupported width %d\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	wm8960->lrclk = params_rate(params);
	/* Update filters क्रम the new rate */
	अगर (tx) अणु
		wm8960_set_deemph(component);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(alc_rates); i++)
			अगर (alc_rates[i].rate == params_rate(params))
				snd_soc_component_update_bits(component,
						    WM8960_ADDCTL3, 0x7,
						    alc_rates[i].val);
	पूर्ण

	/* set अगरace */
	snd_soc_component_ग_लिखो(component, WM8960_IFACE1, अगरace);

	wm8960->is_stream_in_use[tx] = true;

	अगर (!wm8960->is_stream_in_use[!tx])
		वापस wm8960_configure_घड़ीing(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	wm8960->is_stream_in_use[tx] = false;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute)
		snd_soc_component_update_bits(component, WM8960_DACCTL1, 0x8, 0x8);
	अन्यथा
		snd_soc_component_update_bits(component, WM8960_DACCTL1, 0x8, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_set_bias_level_out3(काष्ठा snd_soc_component *component,
				      क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	u16 pm2 = snd_soc_component_पढ़ो(component, WM8960_POWER2);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		चयन (snd_soc_component_get_bias_level(component)) अणु
		हाल SND_SOC_BIAS_STANDBY:
			अगर (!IS_ERR(wm8960->mclk)) अणु
				ret = clk_prepare_enable(wm8960->mclk);
				अगर (ret) अणु
					dev_err(component->dev,
						"Failed to enable MCLK: %d\n",
						ret);
					वापस ret;
				पूर्ण
			पूर्ण

			ret = wm8960_configure_घड़ीing(component);
			अगर (ret)
				वापस ret;

			/* Set VMID to 2x50k */
			snd_soc_component_update_bits(component, WM8960_POWER1, 0x180, 0x80);
			अवरोध;

		हाल SND_SOC_BIAS_ON:
			/*
			 * If it's sysclk स्वतः mode, and the pll is enabled,
			 * disable the pll
			 */
			अगर (wm8960->clk_id == WM8960_SYSCLK_AUTO && (pm2 & 0x1))
				wm8960_set_pll(component, 0, 0);

			अगर (!IS_ERR(wm8960->mclk))
				clk_disable_unprepare(wm8960->mclk);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_sync(wm8960->regmap);

			/* Enable anti-pop features */
			snd_soc_component_ग_लिखो(component, WM8960_APOP1,
				      WM8960_POBCTRL | WM8960_SOFT_ST |
				      WM8960_BUFDCOPEN | WM8960_BUFIOEN);

			/* Enable & ramp VMID at 2x50k */
			snd_soc_component_update_bits(component, WM8960_POWER1, 0x80, 0x80);
			msleep(100);

			/* Enable VREF */
			snd_soc_component_update_bits(component, WM8960_POWER1, WM8960_VREF,
					    WM8960_VREF);

			/* Disable anti-pop features */
			snd_soc_component_ग_लिखो(component, WM8960_APOP1, WM8960_BUFIOEN);
		पूर्ण

		/* Set VMID to 2x250k */
		snd_soc_component_update_bits(component, WM8960_POWER1, 0x180, 0x100);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Enable anti-pop features */
		snd_soc_component_ग_लिखो(component, WM8960_APOP1,
			     WM8960_POBCTRL | WM8960_SOFT_ST |
			     WM8960_BUFDCOPEN | WM8960_BUFIOEN);

		/* Disable VMID and VREF, let them disअक्षरge */
		snd_soc_component_ग_लिखो(component, WM8960_POWER1, 0);
		msleep(600);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_set_bias_level_capless(काष्ठा snd_soc_component *component,
					 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	u16 pm2 = snd_soc_component_पढ़ो(component, WM8960_POWER2);
	पूर्णांक reg, ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		चयन (snd_soc_component_get_bias_level(component)) अणु
		हाल SND_SOC_BIAS_STANDBY:
			/* Enable anti pop mode */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);

			/* Enable LOUT1, ROUT1 and OUT3 अगर they're enabled */
			reg = 0;
			अगर (wm8960->lout1 && wm8960->lout1->घातer)
				reg |= WM8960_PWR2_LOUT1;
			अगर (wm8960->rout1 && wm8960->rout1->घातer)
				reg |= WM8960_PWR2_ROUT1;
			अगर (wm8960->out3 && wm8960->out3->घातer)
				reg |= WM8960_PWR2_OUT3;
			snd_soc_component_update_bits(component, WM8960_POWER2,
					    WM8960_PWR2_LOUT1 |
					    WM8960_PWR2_ROUT1 |
					    WM8960_PWR2_OUT3, reg);

			/* Enable VMID at 2*50k */
			snd_soc_component_update_bits(component, WM8960_POWER1,
					    WM8960_VMID_MASK, 0x80);

			/* Ramp */
			msleep(100);

			/* Enable VREF */
			snd_soc_component_update_bits(component, WM8960_POWER1,
					    WM8960_VREF, WM8960_VREF);

			msleep(100);

			अगर (!IS_ERR(wm8960->mclk)) अणु
				ret = clk_prepare_enable(wm8960->mclk);
				अगर (ret) अणु
					dev_err(component->dev,
						"Failed to enable MCLK: %d\n",
						ret);
					वापस ret;
				पूर्ण
			पूर्ण

			ret = wm8960_configure_घड़ीing(component);
			अगर (ret)
				वापस ret;

			अवरोध;

		हाल SND_SOC_BIAS_ON:
			/*
			 * If it's sysclk स्वतः mode, and the pll is enabled,
			 * disable the pll
			 */
			अगर (wm8960->clk_id == WM8960_SYSCLK_AUTO && (pm2 & 0x1))
				wm8960_set_pll(component, 0, 0);

			अगर (!IS_ERR(wm8960->mclk))
				clk_disable_unprepare(wm8960->mclk);

			/* Enable anti-pop mode */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);

			/* Disable VMID and VREF */
			snd_soc_component_update_bits(component, WM8960_POWER1,
					    WM8960_VREF | WM8960_VMID_MASK, 0);
			अवरोध;

		हाल SND_SOC_BIAS_OFF:
			regcache_sync(wm8960->regmap);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		चयन (snd_soc_component_get_bias_level(component)) अणु
		हाल SND_SOC_BIAS_PREPARE:
			/* Disable HP disअक्षरge */
			snd_soc_component_update_bits(component, WM8960_APOP2,
					    WM8960_DISOP | WM8960_DRES_MASK,
					    0);

			/* Disable anti-pop features */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 pre_भाग:1;
	u32 n:4;
	u32 k:24;
पूर्ण;

अटल bool is_pll_freq_available(अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक target)
अणु
	अचिन्हित पूर्णांक Nभाग;

	अगर (source == 0 || target == 0)
		वापस false;

	/* Scale up target to PLL operating frequency */
	target *= 4;
	Nभाग = target / source;

	अगर (Nभाग < 6) अणु
		source >>= 1;
		Nभाग = target / source;
	पूर्ण

	अगर ((Nभाग < 6) || (Nभाग > 12))
		वापस false;

	वापस true;
पूर्ण

/* The size in bits of the pll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 24) * 10)

अटल पूर्णांक pll_factors(अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक target,
		       काष्ठा _pll_भाग *pll_भाग)
अणु
	अचिन्हित दीर्घ दीर्घ Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;

	pr_debug("WM8960 PLL: setting %dHz->%dHz\n", source, target);

	/* Scale up target to PLL operating frequency */
	target *= 4;

	Nभाग = target / source;
	अगर (Nभाग < 6) अणु
		source >>= 1;
		pll_भाग->pre_भाग = 1;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग->pre_भाग = 0;

	अगर ((Nभाग < 6) || (Nभाग > 12)) अणु
		pr_err("WM8960 PLL: Unsupported N=%d\n", Nभाग);
		वापस -EINVAL;
	पूर्ण

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

	pr_debug("WM8960 PLL: N=%x K=%x pre_div=%d\n",
		 pll_भाग->n, pll_भाग->k, pll_भाग->pre_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_set_pll(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	u16 reg;
	अटल काष्ठा _pll_भाग pll_भाग;
	पूर्णांक ret;

	अगर (freq_in && freq_out) अणु
		ret = pll_factors(freq_in, freq_out, &pll_भाग);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	/* Disable the PLL: even अगर we are changing the frequency the
	 * PLL needs to be disabled जबतक we करो so. */
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 0x1, 0);
	snd_soc_component_update_bits(component, WM8960_POWER2, 0x1, 0);

	अगर (!freq_in || !freq_out)
		वापस 0;

	reg = snd_soc_component_पढ़ो(component, WM8960_PLL1) & ~0x3f;
	reg |= pll_भाग.pre_भाग << 4;
	reg |= pll_भाग.n;

	अगर (pll_भाग.k) अणु
		reg |= 0x20;

		snd_soc_component_ग_लिखो(component, WM8960_PLL2, (pll_भाग.k >> 16) & 0xff);
		snd_soc_component_ग_लिखो(component, WM8960_PLL3, (pll_भाग.k >> 8) & 0xff);
		snd_soc_component_ग_लिखो(component, WM8960_PLL4, pll_भाग.k & 0xff);
	पूर्ण
	snd_soc_component_ग_लिखो(component, WM8960_PLL1, reg);

	/* Turn it on */
	snd_soc_component_update_bits(component, WM8960_POWER2, 0x1, 0x1);
	msleep(250);
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 0x1, 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);

	wm8960->freq_in = freq_in;

	अगर (pll_id == WM8960_SYSCLK_AUTO)
		वापस 0;

	वापस wm8960_set_pll(component, freq_in, freq_out);
पूर्ण

अटल पूर्णांक wm8960_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	चयन (भाग_id) अणु
	हाल WM8960_SYSCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8960_CLOCK1) & 0x1f9;
		snd_soc_component_ग_लिखो(component, WM8960_CLOCK1, reg | भाग);
		अवरोध;
	हाल WM8960_DACDIV:
		reg = snd_soc_component_पढ़ो(component, WM8960_CLOCK1) & 0x1c7;
		snd_soc_component_ग_लिखो(component, WM8960_CLOCK1, reg | भाग);
		अवरोध;
	हाल WM8960_OPCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8960_PLL1) & 0x03f;
		snd_soc_component_ग_लिखो(component, WM8960_PLL1, reg | भाग);
		अवरोध;
	हाल WM8960_DCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8960_CLOCK2) & 0x03f;
		snd_soc_component_ग_लिखो(component, WM8960_CLOCK2, reg | भाग);
		अवरोध;
	हाल WM8960_TOCLKSEL:
		reg = snd_soc_component_पढ़ो(component, WM8960_ADDCTL1) & 0x1fd;
		snd_soc_component_ग_लिखो(component, WM8960_ADDCTL1, reg | भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8960_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);

	वापस wm8960->set_bias_level(component, level);
पूर्ण

अटल पूर्णांक wm8960_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
					अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल WM8960_SYSCLK_MCLK:
		snd_soc_component_update_bits(component, WM8960_CLOCK1,
					0x1, WM8960_SYSCLK_MCLK);
		अवरोध;
	हाल WM8960_SYSCLK_PLL:
		snd_soc_component_update_bits(component, WM8960_CLOCK1,
					0x1, WM8960_SYSCLK_PLL);
		अवरोध;
	हाल WM8960_SYSCLK_AUTO:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wm8960->sysclk = freq;
	wm8960->clk_id = clk_id;

	वापस 0;
पूर्ण

#घोषणा WM8960_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा WM8960_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8960_dai_ops = अणु
	.hw_params = wm8960_hw_params,
	.hw_मुक्त = wm8960_hw_मुक्त,
	.mute_stream = wm8960_mute,
	.set_fmt = wm8960_set_dai_fmt,
	.set_clkभाग = wm8960_set_dai_clkभाग,
	.set_pll = wm8960_set_dai_pll,
	.set_sysclk = wm8960_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8960_dai = अणु
	.name = "wm8960-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8960_RATES,
		.क्रमmats = WM8960_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8960_RATES,
		.क्रमmats = WM8960_FORMATS,पूर्ण,
	.ops = &wm8960_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8960_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8960_data *pdata = &wm8960->pdata;

	अगर (pdata->capless)
		wm8960->set_bias_level = wm8960_set_bias_level_capless;
	अन्यथा
		wm8960->set_bias_level = wm8960_set_bias_level_out3;

	snd_soc_add_component_controls(component, wm8960_snd_controls,
				     ARRAY_SIZE(wm8960_snd_controls));
	wm8960_add_widमाला_लो(component);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8960 = अणु
	.probe			= wm8960_probe,
	.set_bias_level		= wm8960_set_bias_level,
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8960_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8960_PLL4,

	.reg_शेषs = wm8960_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8960_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8960_अस्थिर,
पूर्ण;

अटल व्योम wm8960_set_pdata_from_of(काष्ठा i2c_client *i2c,
				काष्ठा wm8960_data *pdata)
अणु
	स्थिर काष्ठा device_node *np = i2c->dev.of_node;

	अगर (of_property_पढ़ो_bool(np, "wlf,capless"))
		pdata->capless = true;

	अगर (of_property_पढ़ो_bool(np, "wlf,shared-lrclk"))
		pdata->shared_lrclk = true;

	of_property_पढ़ो_u32_array(np, "wlf,gpio-cfg", pdata->gpio_cfg,
				   ARRAY_SIZE(pdata->gpio_cfg));

	of_property_पढ़ो_u32_array(np, "wlf,hp-cfg", pdata->hp_cfg,
				   ARRAY_SIZE(pdata->hp_cfg));
पूर्ण

अटल पूर्णांक wm8960_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8960_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा wm8960_priv *wm8960;
	पूर्णांक ret;

	wm8960 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8960_priv),
			      GFP_KERNEL);
	अगर (wm8960 == शून्य)
		वापस -ENOMEM;

	wm8960->mclk = devm_clk_get(&i2c->dev, "mclk");
	अगर (IS_ERR(wm8960->mclk)) अणु
		अगर (PTR_ERR(wm8960->mclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
	पूर्ण

	wm8960->regmap = devm_regmap_init_i2c(i2c, &wm8960_regmap);
	अगर (IS_ERR(wm8960->regmap))
		वापस PTR_ERR(wm8960->regmap);

	अगर (pdata)
		स_नकल(&wm8960->pdata, pdata, माप(काष्ठा wm8960_data));
	अन्यथा अगर (i2c->dev.of_node)
		wm8960_set_pdata_from_of(i2c, &wm8960->pdata);

	ret = wm8960_reset(wm8960->regmap);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	अगर (wm8960->pdata.shared_lrclk) अणु
		ret = regmap_update_bits(wm8960->regmap, WM8960_ADDCTL2,
					 0x4, 0x4);
		अगर (ret != 0) अणु
			dev_err(&i2c->dev, "Failed to enable LRCM: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Latch the update bits */
	regmap_update_bits(wm8960->regmap, WM8960_LINVOL, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_RINVOL, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LADC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_RADC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LDAC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_RDAC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LOUT1, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_ROUT1, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LOUT2, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_ROUT2, 0x100, 0x100);

	/* ADCLRC pin configured as GPIO. */
	regmap_update_bits(wm8960->regmap, WM8960_IFACE2, 1 << 6,
			   wm8960->pdata.gpio_cfg[0] << 6);
	regmap_update_bits(wm8960->regmap, WM8960_ADDCTL4, 0xF << 4,
			   wm8960->pdata.gpio_cfg[1] << 4);

	/* Enable headphone jack detect */
	regmap_update_bits(wm8960->regmap, WM8960_ADDCTL4, 3 << 2,
			   wm8960->pdata.hp_cfg[0] << 2);
	regmap_update_bits(wm8960->regmap, WM8960_ADDCTL2, 3 << 5,
			   wm8960->pdata.hp_cfg[1] << 5);
	regmap_update_bits(wm8960->regmap, WM8960_ADDCTL1, 3,
			   wm8960->pdata.hp_cfg[2]);

	i2c_set_clientdata(i2c, wm8960);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8960, &wm8960_dai, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8960_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8960_i2c_id[] = अणु
	अणु "wm8960", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8960_i2c_id);

अटल स्थिर काष्ठा of_device_id wm8960_of_match[] = अणु
       अणु .compatible = "wlf,wm8960", पूर्ण,
       अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8960_of_match);

अटल काष्ठा i2c_driver wm8960_i2c_driver = अणु
	.driver = अणु
		.name = "wm8960",
		.of_match_table = wm8960_of_match,
	पूर्ण,
	.probe =    wm8960_i2c_probe,
	.हटाओ =   wm8960_i2c_हटाओ,
	.id_table = wm8960_i2c_id,
पूर्ण;

module_i2c_driver(wm8960_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8960 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
