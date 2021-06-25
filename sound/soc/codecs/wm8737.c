<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8737.c  --  WM8737 ALSA SoC Audio driver
 *
 * Copyright 2010 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
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
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8737.h"

#घोषणा WM8737_NUM_SUPPLIES 4
अटल स्थिर अक्षर *wm8737_supply_names[WM8737_NUM_SUPPLIES] = अणु
	"DCVDD",
	"DBVDD",
	"AVDD",
	"MVDD",
पूर्ण;

/* codec निजी data */
काष्ठा wm8737_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8737_NUM_SUPPLIES];
	अचिन्हित पूर्णांक mclk;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8737_reg_शेषs[] = अणु
	अणु  0, 0x00C3 पूर्ण,     /* R0  - Left PGA volume */
	अणु  1, 0x00C3 पूर्ण,     /* R1  - Right PGA volume */
	अणु  2, 0x0007 पूर्ण,     /* R2  - AUDIO path L */
	अणु  3, 0x0007 पूर्ण,     /* R3  - AUDIO path R */
	अणु  4, 0x0000 पूर्ण,     /* R4  - 3D Enhance */
	अणु  5, 0x0000 पूर्ण,     /* R5  - ADC Control */
	अणु  6, 0x0000 पूर्ण,     /* R6  - Power Management */
	अणु  7, 0x000A पूर्ण,     /* R7  - Audio Format */
	अणु  8, 0x0000 पूर्ण,     /* R8  - Clocking */
	अणु  9, 0x000F पूर्ण,     /* R9  - MIC Preamp Control */
	अणु 10, 0x0003 पूर्ण,     /* R10 - Misc Bias Control */
	अणु 11, 0x0000 पूर्ण,     /* R11 - Noise Gate */
	अणु 12, 0x007C पूर्ण,     /* R12 - ALC1 */
	अणु 13, 0x0000 पूर्ण,     /* R13 - ALC2 */
	अणु 14, 0x0032 पूर्ण,     /* R14 - ALC3 */
पूर्ण;

अटल bool wm8737_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8737_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8737_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, WM8737_RESET, 0);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(micboost_tlv,
	0, 0, TLV_DB_SCALE_ITEM(1300, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(1800, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(2800, 0, 0),
	3, 3, TLV_DB_SCALE_ITEM(3300, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, -9750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ng_tlv, -7800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_max_tlv, -1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_target_tlv, -1800, 100, 0);

अटल स्थिर अक्षर *micbias_क्रमागत_text[] = अणु
	"25%",
	"50%",
	"75%",
	"100%",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(micbias_क्रमागत,
			    WM8737_MIC_PREAMP_CONTROL, 0, micbias_क्रमागत_text);

अटल स्थिर अक्षर *low_cutoff_text[] = अणु
	"Low", "High"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(low_3d,
			    WM8737_3D_ENHANCE, 6, low_cutoff_text);

अटल स्थिर अक्षर *high_cutoff_text[] = अणु
	"High", "Low"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(high_3d,
			    WM8737_3D_ENHANCE, 5, high_cutoff_text);

अटल स्थिर अक्षर *alc_fn_text[] = अणु
	"Disabled", "Right", "Left", "Stereo"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(alc_fn,
			    WM8737_ALC1, 7, alc_fn_text);

अटल स्थिर अक्षर *alc_hold_text[] = अणु
	"0", "2.67ms", "5.33ms", "10.66ms", "21.32ms", "42.64ms", "85.28ms",
	"170.56ms", "341.12ms", "682.24ms", "1.364s", "2.728s", "5.458s",
	"10.916s", "21.832s", "43.691s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(alc_hold,
			    WM8737_ALC2, 0, alc_hold_text);

अटल स्थिर अक्षर *alc_atk_text[] = अणु
	"8.4ms", "16.8ms", "33.6ms", "67.2ms", "134.4ms", "268.8ms", "537.6ms",
	"1.075s", "2.15s", "4.3s", "8.6s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(alc_atk,
			    WM8737_ALC3, 0, alc_atk_text);

अटल स्थिर अक्षर *alc_dcy_text[] = अणु
	"33.6ms", "67.2ms", "134.4ms", "268.8ms", "537.6ms", "1.075s", "2.15s",
	"4.3s", "8.6s", "17.2s", "34.41s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(alc_dcy,
			    WM8737_ALC3, 4, alc_dcy_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8737_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Mic Boost Volume", WM8737_AUDIO_PATH_L, WM8737_AUDIO_PATH_R,
		 6, 3, 0, micboost_tlv),
SOC_DOUBLE_R("Mic Boost Switch", WM8737_AUDIO_PATH_L, WM8737_AUDIO_PATH_R,
	     4, 1, 0),
SOC_DOUBLE("Mic ZC Switch", WM8737_AUDIO_PATH_L, WM8737_AUDIO_PATH_R,
	   3, 1, 0),

SOC_DOUBLE_R_TLV("Capture Volume", WM8737_LEFT_PGA_VOLUME,
		 WM8737_RIGHT_PGA_VOLUME, 0, 255, 0, pga_tlv),
SOC_DOUBLE("Capture ZC Switch", WM8737_AUDIO_PATH_L, WM8737_AUDIO_PATH_R,
	   2, 1, 0),

SOC_DOUBLE("INPUT1 DC Bias Switch", WM8737_MISC_BIAS_CONTROL, 0, 1, 1, 0),

SOC_ENUM("Mic PGA Bias", micbias_क्रमागत),
SOC_SINGLE("ADC Low Power Switch", WM8737_ADC_CONTROL, 2, 1, 0),
SOC_SINGLE("High Pass Filter Switch", WM8737_ADC_CONTROL, 0, 1, 1),
SOC_DOUBLE("Polarity Invert Switch", WM8737_ADC_CONTROL, 5, 6, 1, 0),

SOC_SINGLE("3D Switch", WM8737_3D_ENHANCE, 0, 1, 0),
SOC_SINGLE("3D Depth", WM8737_3D_ENHANCE, 1, 15, 0),
SOC_ENUM("3D Low Cut-off", low_3d),
SOC_ENUM("3D High Cut-off", high_3d),
SOC_SINGLE_TLV("3D ADC Volume", WM8737_3D_ENHANCE, 7, 1, 1, adc_tlv),

SOC_SINGLE("Noise Gate Switch", WM8737_NOISE_GATE, 0, 1, 0),
SOC_SINGLE_TLV("Noise Gate Threshold Volume", WM8737_NOISE_GATE, 2, 7, 0,
	       ng_tlv),

SOC_ENUM("ALC", alc_fn),
SOC_SINGLE_TLV("ALC Max Gain Volume", WM8737_ALC1, 4, 7, 0, alc_max_tlv),
SOC_SINGLE_TLV("ALC Target Volume", WM8737_ALC1, 0, 15, 0, alc_target_tlv),
SOC_ENUM("ALC Hold Time", alc_hold),
SOC_SINGLE("ALC ZC Switch", WM8737_ALC2, 4, 1, 0),
SOC_ENUM("ALC Attack Time", alc_atk),
SOC_ENUM("ALC Decay Time", alc_dcy),
पूर्ण;

अटल स्थिर अक्षर *linsel_text[] = अणु
	"LINPUT1", "LINPUT2", "LINPUT3", "LINPUT1 DC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(linsel_क्रमागत,
			    WM8737_AUDIO_PATH_L, 7, linsel_text);

अटल स्थिर काष्ठा snd_kcontrol_new linsel_mux =
	SOC_DAPM_ENUM("LINSEL", linsel_क्रमागत);


अटल स्थिर अक्षर *rinsel_text[] = अणु
	"RINPUT1", "RINPUT2", "RINPUT3", "RINPUT1 DC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rinsel_क्रमागत,
			    WM8737_AUDIO_PATH_R, 7, rinsel_text);

अटल स्थिर काष्ठा snd_kcontrol_new rinsel_mux =
	SOC_DAPM_ENUM("RINSEL", rinsel_क्रमागत);

अटल स्थिर अक्षर *bypass_text[] = अणु
	"Direct", "Preamp"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lbypass_क्रमागत,
			    WM8737_MIC_PREAMP_CONTROL, 2, bypass_text);

अटल स्थिर काष्ठा snd_kcontrol_new lbypass_mux =
	SOC_DAPM_ENUM("Left Bypass", lbypass_क्रमागत);


अटल SOC_ENUM_SINGLE_DECL(rbypass_क्रमागत,
			    WM8737_MIC_PREAMP_CONTROL, 3, bypass_text);

अटल स्थिर काष्ठा snd_kcontrol_new rbypass_mux =
	SOC_DAPM_ENUM("Left Bypass", rbypass_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8737_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("LINPUT1"),
SND_SOC_DAPM_INPUT("LINPUT2"),
SND_SOC_DAPM_INPUT("LINPUT3"),
SND_SOC_DAPM_INPUT("RINPUT1"),
SND_SOC_DAPM_INPUT("RINPUT2"),
SND_SOC_DAPM_INPUT("RINPUT3"),
SND_SOC_DAPM_INPUT("LACIN"),
SND_SOC_DAPM_INPUT("RACIN"),

SND_SOC_DAPM_MUX("LINSEL", SND_SOC_NOPM, 0, 0, &linsel_mux),
SND_SOC_DAPM_MUX("RINSEL", SND_SOC_NOPM, 0, 0, &rinsel_mux),

SND_SOC_DAPM_MUX("Left Preamp Mux", SND_SOC_NOPM, 0, 0, &lbypass_mux),
SND_SOC_DAPM_MUX("Right Preamp Mux", SND_SOC_NOPM, 0, 0, &rbypass_mux),

SND_SOC_DAPM_PGA("PGAL", WM8737_POWER_MANAGEMENT, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("PGAR", WM8737_POWER_MANAGEMENT, 4, 0, शून्य, 0),

SND_SOC_DAPM_DAC("ADCL", शून्य, WM8737_POWER_MANAGEMENT, 3, 0),
SND_SOC_DAPM_DAC("ADCR", शून्य, WM8737_POWER_MANAGEMENT, 2, 0),

SND_SOC_DAPM_AIF_OUT("AIF", "Capture", 0, WM8737_POWER_MANAGEMENT, 6, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	अणु "LINSEL", "LINPUT1", "LINPUT1" पूर्ण,
	अणु "LINSEL", "LINPUT2", "LINPUT2" पूर्ण,
	अणु "LINSEL", "LINPUT3", "LINPUT3" पूर्ण,
	अणु "LINSEL", "LINPUT1 DC", "LINPUT1" पूर्ण,

	अणु "RINSEL", "RINPUT1", "RINPUT1" पूर्ण,
	अणु "RINSEL", "RINPUT2", "RINPUT2" पूर्ण,
	अणु "RINSEL", "RINPUT3", "RINPUT3" पूर्ण,
	अणु "RINSEL", "RINPUT1 DC", "RINPUT1" पूर्ण,

	अणु "Left Preamp Mux", "Preamp", "LINSEL" पूर्ण,
	अणु "Left Preamp Mux", "Direct", "LACIN" पूर्ण,

	अणु "Right Preamp Mux", "Preamp", "RINSEL" पूर्ण,
	अणु "Right Preamp Mux", "Direct", "RACIN" पूर्ण,

	अणु "PGAL", शून्य, "Left Preamp Mux" पूर्ण,
	अणु "PGAR", शून्य, "Right Preamp Mux" पूर्ण,

	अणु "ADCL", शून्य, "PGAL" पूर्ण,
	अणु "ADCR", शून्य, "PGAR" पूर्ण,

	अणु "AIF", शून्य, "ADCL" पूर्ण,
	अणु "AIF", शून्य, "ADCR" पूर्ण,
पूर्ण;

/* codec mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा अणु
	u32 mclk;
	u32 rate;
	u8 usb;
	u8 sr;
पूर्ण coeff_भाग[] = अणु
	अणु 12288000,  8000, 0,  0x4 पूर्ण,
	अणु 12288000, 12000, 0,  0x8 पूर्ण,
	अणु 12288000, 16000, 0,  0xa पूर्ण,
	अणु 12288000, 24000, 0, 0x1c पूर्ण,
	अणु 12288000, 32000, 0,  0xc पूर्ण,
	अणु 12288000, 48000, 0,    0 पूर्ण,
	अणु 12288000, 96000, 0,  0xe पूर्ण,

	अणु 11289600,  8000, 0, 0x14 पूर्ण,
	अणु 11289600, 11025, 0, 0x18 पूर्ण,
	अणु 11289600, 22050, 0, 0x1a पूर्ण,
	अणु 11289600, 44100, 0, 0x10 पूर्ण,
	अणु 11289600, 88200, 0, 0x1e पूर्ण,

	अणु 18432000,  8000, 0,  0x5 पूर्ण,
	अणु 18432000, 12000, 0,  0x9 पूर्ण,
	अणु 18432000, 16000, 0,  0xb पूर्ण,
	अणु 18432000, 24000, 0, 0x1b पूर्ण,
	अणु 18432000, 32000, 0,  0xd पूर्ण,
	अणु 18432000, 48000, 0,  0x1 पूर्ण,
	अणु 18432000, 96000, 0, 0x1f पूर्ण,

	अणु 16934400,  8000, 0, 0x15 पूर्ण,
	अणु 16934400, 11025, 0, 0x19 पूर्ण,
	अणु 16934400, 22050, 0, 0x1b पूर्ण,
	अणु 16934400, 44100, 0, 0x11 पूर्ण,
	अणु 16934400, 88200, 0, 0x1f पूर्ण,

	अणु 12000000,  8000, 1,  0x4 पूर्ण,
	अणु 12000000, 11025, 1, 0x19 पूर्ण,
	अणु 12000000, 12000, 1,  0x8 पूर्ण,
	अणु 12000000, 16000, 1,  0xa पूर्ण,
	अणु 12000000, 22050, 1, 0x1b पूर्ण,
	अणु 12000000, 24000, 1, 0x1c पूर्ण,
	अणु 12000000, 32000, 1,  0xc पूर्ण,
	अणु 12000000, 44100, 1, 0x11 पूर्ण,
	अणु 12000000, 48000, 1,  0x0 पूर्ण,
	अणु 12000000, 88200, 1, 0x1f पूर्ण,
	अणु 12000000, 96000, 1,  0xe पूर्ण,
पूर्ण;

अटल पूर्णांक wm8737_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8737_priv *wm8737 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;
	u16 घड़ीing = 0;
	u16 af = 0;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate != params_rate(params))
			जारी;

		अगर (coeff_भाग[i].mclk == wm8737->mclk)
			अवरोध;

		अगर (coeff_भाग[i].mclk == wm8737->mclk * 2) अणु
			घड़ीing |= WM8737_CLKDIV2;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(coeff_भाग)) अणु
		dev_err(component->dev, "%dHz MCLK can't support %dHz\n",
			wm8737->mclk, params_rate(params));
		वापस -EINVAL;
	पूर्ण

	घड़ीing |= coeff_भाग[i].usb | (coeff_भाग[i].sr << WM8737_SR_SHIFT);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		af |= 0x8;
		अवरोध;
	हाल 24:
		af |= 0x10;
		अवरोध;
	हाल 32:
		af |= 0x18;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8737_AUDIO_FORMAT, WM8737_WL_MASK, af);
	snd_soc_component_update_bits(component, WM8737_CLOCKING,
			    WM8737_USB_MODE | WM8737_CLKDIV2 | WM8737_SR_MASK,
			    घड़ीing);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8737_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8737_priv *wm8737 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (freq == coeff_भाग[i].mclk ||
		    freq == coeff_भाग[i].mclk * 2) अणु
			wm8737->mclk = freq;
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(component->dev, "MCLK rate %dHz not supported\n", freq);

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक wm8737_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 af = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		af |= WM8737_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		af |= 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		af |= 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		af |= 0x3;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		af |= 0x13;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		af |= WM8737_LRP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8737_AUDIO_FORMAT,
			    WM8737_FORMAT_MASK | WM8737_LRP | WM8737_MS, af);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8737_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8737_priv *wm8737 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VMID at 2*75k */
		snd_soc_component_update_bits(component, WM8737_MISC_BIAS_CONTROL,
				    WM8737_VMIDSEL_MASK, 0);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8737->supplies),
						    wm8737->supplies);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			regcache_sync(wm8737->regmap);

			/* Fast VMID ramp at 2*2.5k */
			snd_soc_component_update_bits(component, WM8737_MISC_BIAS_CONTROL,
					    WM8737_VMIDSEL_MASK,
					    2 << WM8737_VMIDSEL_SHIFT);

			/* Bring VMID up */
			snd_soc_component_update_bits(component, WM8737_POWER_MANAGEMENT,
					    WM8737_VMID_MASK |
					    WM8737_VREF_MASK,
					    WM8737_VMID_MASK |
					    WM8737_VREF_MASK);

			msleep(500);
		पूर्ण

		/* VMID at 2*300k */
		snd_soc_component_update_bits(component, WM8737_MISC_BIAS_CONTROL,
				    WM8737_VMIDSEL_MASK,
				    1 << WM8737_VMIDSEL_SHIFT);

		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8737_POWER_MANAGEMENT,
				    WM8737_VMID_MASK | WM8737_VREF_MASK, 0);

		regulator_bulk_disable(ARRAY_SIZE(wm8737->supplies),
				       wm8737->supplies);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8737_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8737_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8737_dai_ops = अणु
	.hw_params	= wm8737_hw_params,
	.set_sysclk	= wm8737_set_dai_sysclk,
	.set_fmt	= wm8737_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8737_dai = अणु
	.name = "wm8737",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,  /* Mono modes not yet supported */
		.channels_max = 2,
		.rates = WM8737_RATES,
		.क्रमmats = WM8737_FORMATS,
	पूर्ण,
	.ops = &wm8737_dai_ops,
पूर्ण;

अटल पूर्णांक wm8737_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8737_priv *wm8737 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8737->supplies),
				    wm8737->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_get;
	पूर्ण

	ret = wm8737_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset\n");
		जाओ err_enable;
	पूर्ण

	snd_soc_component_update_bits(component, WM8737_LEFT_PGA_VOLUME, WM8737_LVU,
			    WM8737_LVU);
	snd_soc_component_update_bits(component, WM8737_RIGHT_PGA_VOLUME, WM8737_RVU,
			    WM8737_RVU);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Bias level configuration will have करोne an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(wm8737->supplies), wm8737->supplies);

	वापस 0;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8737->supplies), wm8737->supplies);
err_get:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8737 = अणु
	.probe			= wm8737_probe,
	.set_bias_level		= wm8737_set_bias_level,
	.controls		= wm8737_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8737_snd_controls),
	.dapm_widमाला_लो		= wm8737_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8737_dapm_widमाला_लो),
	.dapm_routes		= पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8737_of_match[] = अणु
	अणु .compatible = "wlf,wm8737", पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, wm8737_of_match);

अटल स्थिर काष्ठा regmap_config wm8737_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8737_MAX_REGISTER,

	.reg_शेषs = wm8737_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8737_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8737_अस्थिर,
पूर्ण;

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8737_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8737_priv *wm8737;
	पूर्णांक ret, i;

	wm8737 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8737_priv),
			      GFP_KERNEL);
	अगर (wm8737 == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(wm8737->supplies); i++)
		wm8737->supplies[i].supply = wm8737_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8737->supplies),
				      wm8737->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8737->regmap = devm_regmap_init_i2c(i2c, &wm8737_regmap);
	अगर (IS_ERR(wm8737->regmap))
		वापस PTR_ERR(wm8737->regmap);

	i2c_set_clientdata(i2c, wm8737);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_component_dev_wm8737, &wm8737_dai, 1);

	वापस ret;

पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8737_i2c_id[] = अणु
	अणु "wm8737", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8737_i2c_id);

अटल काष्ठा i2c_driver wm8737_i2c_driver = अणु
	.driver = अणु
		.name = "wm8737",
		.of_match_table = wm8737_of_match,
	पूर्ण,
	.probe =    wm8737_i2c_probe,
	.id_table = wm8737_i2c_id,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8737_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8737_priv *wm8737;
	पूर्णांक ret, i;

	wm8737 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8737_priv),
			      GFP_KERNEL);
	अगर (wm8737 == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(wm8737->supplies); i++)
		wm8737->supplies[i].supply = wm8737_supply_names[i];

	ret = devm_regulator_bulk_get(&spi->dev, ARRAY_SIZE(wm8737->supplies),
				      wm8737->supplies);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8737->regmap = devm_regmap_init_spi(spi, &wm8737_regmap);
	अगर (IS_ERR(wm8737->regmap))
		वापस PTR_ERR(wm8737->regmap);

	spi_set_drvdata(spi, wm8737);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
				&soc_component_dev_wm8737, &wm8737_dai, 1);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8737_spi_driver = अणु
	.driver = अणु
		.name	= "wm8737",
		.of_match_table = wm8737_of_match,
	पूर्ण,
	.probe		= wm8737_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

अटल पूर्णांक __init wm8737_modinit(व्योम)
अणु
	पूर्णांक ret;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8737_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8737 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8737_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8737 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
module_init(wm8737_modinit);

अटल व्योम __निकास wm8737_निकास(व्योम)
अणु
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8737_spi_driver);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8737_i2c_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8737_निकास);

MODULE_DESCRIPTION("ASoC WM8737 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
