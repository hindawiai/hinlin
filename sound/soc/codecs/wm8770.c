<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8770.c  --  WM8770 ALSA SoC Audio driver
 *
 * Copyright 2010 Wolfson Microelectronics plc
 *
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8770.h"

#घोषणा WM8770_NUM_SUPPLIES 3
अटल स्थिर अक्षर *wm8770_supply_names[WM8770_NUM_SUPPLIES] = अणु
	"AVDD1",
	"AVDD2",
	"DVDD"
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8770_reg_शेषs[] = अणु
	अणु  0, 0x7f पूर्ण,
	अणु  1, 0x7f पूर्ण,
	अणु  2, 0x7f पूर्ण,
	अणु  3, 0x7f पूर्ण,
	अणु  4, 0x7f पूर्ण,
	अणु  5, 0x7f पूर्ण,
	अणु  6, 0x7f पूर्ण,
	अणु  7, 0x7f पूर्ण,
	अणु  8, 0x7f पूर्ण,
	अणु  9, 0xff पूर्ण,
	अणु 10, 0xff पूर्ण,
	अणु 11, 0xff पूर्ण,
	अणु 12, 0xff पूर्ण,
	अणु 13, 0xff पूर्ण,
	अणु 14, 0xff पूर्ण,
	अणु 15, 0xff पूर्ण,
	अणु 16, 0xff पूर्ण,
	अणु 17, 0xff पूर्ण,
	अणु 18, 0    पूर्ण,
	अणु 19, 0x90 पूर्ण,
	अणु 20, 0    पूर्ण,
	अणु 21, 0    पूर्ण,
	अणु 22, 0x22 पूर्ण,
	अणु 23, 0x22 पूर्ण,
	अणु 24, 0x3e पूर्ण,
	अणु 25, 0xc  पूर्ण,
	अणु 26, 0xc  पूर्ण,
	अणु 27, 0x100 पूर्ण,
	अणु 28, 0x189 पूर्ण,
	अणु 29, 0x189 पूर्ण,
	अणु 30, 0x8770 पूर्ण,
पूर्ण;

अटल bool wm8770_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8770_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

काष्ठा wm8770_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8770_NUM_SUPPLIES];
	काष्ठा notअगरier_block disable_nb[WM8770_NUM_SUPPLIES];
	काष्ठा snd_soc_component *component;
	पूर्णांक sysclk;
पूर्ण;

अटल पूर्णांक vout12supply_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
अटल पूर्णांक vout34supply_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

/*
 * We can't use the same notअगरier block क्रम more than one supply and
 * there's no way I can see to get from a callback to the caller
 * except container_of().
 */
#घोषणा WM8770_REGULATOR_EVENT(n) \
अटल पूर्णांक wm8770_regulator_event_##n(काष्ठा notअगरier_block *nb, \
				      अचिन्हित दीर्घ event, व्योम *data)    \
अणु \
	काष्ठा wm8770_priv *wm8770 = container_of(nb, काष्ठा wm8770_priv, \
				     disable_nb[n]); \
	अगर (event & REGULATOR_EVENT_DISABLE) अणु \
		regcache_mark_dirty(wm8770->regmap);	\
	पूर्ण \
	वापस 0; \
पूर्ण

WM8770_REGULATOR_EVENT(0)
WM8770_REGULATOR_EVENT(1)
WM8770_REGULATOR_EVENT(2)

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_dig_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_alg_tlv, -12700, 100, 1);

अटल स्थिर अक्षर *dac_phase_text[][2] = अणु
	अणु "DAC1 Normal", "DAC1 Inverted" पूर्ण,
	अणु "DAC2 Normal", "DAC2 Inverted" पूर्ण,
	अणु "DAC3 Normal", "DAC3 Inverted" पूर्ण,
	अणु "DAC4 Normal", "DAC4 Inverted" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत dac_phase[] = अणु
	SOC_ENUM_DOUBLE(WM8770_DACPHASE, 0, 1, 2, dac_phase_text[0]),
	SOC_ENUM_DOUBLE(WM8770_DACPHASE, 2, 3, 2, dac_phase_text[1]),
	SOC_ENUM_DOUBLE(WM8770_DACPHASE, 4, 5, 2, dac_phase_text[2]),
	SOC_ENUM_DOUBLE(WM8770_DACPHASE, 6, 7, 2, dac_phase_text[3]),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8770_snd_controls[] = अणु
	/* global DAC playback controls */
	SOC_SINGLE_TLV("DAC Playback Volume", WM8770_MSDIGVOL, 0, 255, 0,
		dac_dig_tlv),
	SOC_SINGLE("DAC Playback Switch", WM8770_DACMUTE, 4, 1, 1),
	SOC_SINGLE("DAC Playback ZC Switch", WM8770_DACCTRL1, 0, 1, 0),

	/* global VOUT playback controls */
	SOC_SINGLE_TLV("VOUT Playback Volume", WM8770_MSALGVOL, 0, 127, 0,
		dac_alg_tlv),
	SOC_SINGLE("VOUT Playback ZC Switch", WM8770_MSALGVOL, 7, 1, 0),

	/* VOUT1/2/3/4 specअगरic controls */
	SOC_DOUBLE_R_TLV("VOUT1 Playback Volume", WM8770_VOUT1LVOL,
		WM8770_VOUT1RVOL, 0, 127, 0, dac_alg_tlv),
	SOC_DOUBLE_R("VOUT1 Playback ZC Switch", WM8770_VOUT1LVOL,
		WM8770_VOUT1RVOL, 7, 1, 0),
	SOC_DOUBLE_R_TLV("VOUT2 Playback Volume", WM8770_VOUT2LVOL,
		WM8770_VOUT2RVOL, 0, 127, 0, dac_alg_tlv),
	SOC_DOUBLE_R("VOUT2 Playback ZC Switch", WM8770_VOUT2LVOL,
		WM8770_VOUT2RVOL, 7, 1, 0),
	SOC_DOUBLE_R_TLV("VOUT3 Playback Volume", WM8770_VOUT3LVOL,
		WM8770_VOUT3RVOL, 0, 127, 0, dac_alg_tlv),
	SOC_DOUBLE_R("VOUT3 Playback ZC Switch", WM8770_VOUT3LVOL,
		WM8770_VOUT3RVOL, 7, 1, 0),
	SOC_DOUBLE_R_TLV("VOUT4 Playback Volume", WM8770_VOUT4LVOL,
		WM8770_VOUT4RVOL, 0, 127, 0, dac_alg_tlv),
	SOC_DOUBLE_R("VOUT4 Playback ZC Switch", WM8770_VOUT4LVOL,
		WM8770_VOUT4RVOL, 7, 1, 0),

	/* DAC1/2/3/4 specअगरic controls */
	SOC_DOUBLE_R_TLV("DAC1 Playback Volume", WM8770_DAC1LVOL,
		WM8770_DAC1RVOL, 0, 255, 0, dac_dig_tlv),
	SOC_SINGLE("DAC1 Deemphasis Switch", WM8770_DACCTRL2, 0, 1, 0),
	SOC_ENUM("DAC1 Phase", dac_phase[0]),
	SOC_DOUBLE_R_TLV("DAC2 Playback Volume", WM8770_DAC2LVOL,
		WM8770_DAC2RVOL, 0, 255, 0, dac_dig_tlv),
	SOC_SINGLE("DAC2 Deemphasis Switch", WM8770_DACCTRL2, 1, 1, 0),
	SOC_ENUM("DAC2 Phase", dac_phase[1]),
	SOC_DOUBLE_R_TLV("DAC3 Playback Volume", WM8770_DAC3LVOL,
		WM8770_DAC3RVOL, 0, 255, 0, dac_dig_tlv),
	SOC_SINGLE("DAC3 Deemphasis Switch", WM8770_DACCTRL2, 2, 1, 0),
	SOC_ENUM("DAC3 Phase", dac_phase[2]),
	SOC_DOUBLE_R_TLV("DAC4 Playback Volume", WM8770_DAC4LVOL,
		WM8770_DAC4RVOL, 0, 255, 0, dac_dig_tlv),
	SOC_SINGLE("DAC4 Deemphasis Switch", WM8770_DACCTRL2, 3, 1, 0),
	SOC_ENUM("DAC4 Phase", dac_phase[3]),

	/* ADC specअगरic controls */
	SOC_DOUBLE_R_TLV("Capture Volume", WM8770_ADCLCTRL, WM8770_ADCRCTRL,
		0, 31, 0, adc_tlv),
	SOC_DOUBLE_R("Capture Switch", WM8770_ADCLCTRL, WM8770_ADCRCTRL,
		5, 1, 1),

	/* other controls */
	SOC_SINGLE("ADC 128x Oversampling Switch", WM8770_MSTRCTRL, 3, 1, 0),
	SOC_SINGLE("ADC Highpass Filter Switch", WM8770_IFACECTRL, 8, 1, 1)
पूर्ण;

अटल स्थिर अक्षर *ain_text[] = अणु
	"AIN1", "AIN2", "AIN3", "AIN4",
	"AIN5", "AIN6", "AIN7", "AIN8"
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(ain_क्रमागत,
			    WM8770_ADCMUX, 0, 4, ain_text);

अटल स्थिर काष्ठा snd_kcontrol_new ain_mux =
	SOC_DAPM_ENUM("Capture Mux", ain_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new vout1_mix_controls[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", WM8770_OUTMUX1, 0, 1, 0),
	SOC_DAPM_SINGLE("AUX1 Switch", WM8770_OUTMUX1, 1, 1, 0),
	SOC_DAPM_SINGLE("Bypass Switch", WM8770_OUTMUX1, 2, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vout2_mix_controls[] = अणु
	SOC_DAPM_SINGLE("DAC2 Switch", WM8770_OUTMUX1, 3, 1, 0),
	SOC_DAPM_SINGLE("AUX2 Switch", WM8770_OUTMUX1, 4, 1, 0),
	SOC_DAPM_SINGLE("Bypass Switch", WM8770_OUTMUX1, 5, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vout3_mix_controls[] = अणु
	SOC_DAPM_SINGLE("DAC3 Switch", WM8770_OUTMUX2, 0, 1, 0),
	SOC_DAPM_SINGLE("AUX3 Switch", WM8770_OUTMUX2, 1, 1, 0),
	SOC_DAPM_SINGLE("Bypass Switch", WM8770_OUTMUX2, 2, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vout4_mix_controls[] = अणु
	SOC_DAPM_SINGLE("DAC4 Switch", WM8770_OUTMUX2, 3, 1, 0),
	SOC_DAPM_SINGLE("Bypass Switch", WM8770_OUTMUX2, 4, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8770_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("AUX1"),
	SND_SOC_DAPM_INPUT("AUX2"),
	SND_SOC_DAPM_INPUT("AUX3"),

	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),
	SND_SOC_DAPM_INPUT("AIN5"),
	SND_SOC_DAPM_INPUT("AIN6"),
	SND_SOC_DAPM_INPUT("AIN7"),
	SND_SOC_DAPM_INPUT("AIN8"),

	SND_SOC_DAPM_MUX("Capture Mux", WM8770_ADCMUX, 8, 1, &ain_mux),

	SND_SOC_DAPM_ADC("ADC", "Capture", WM8770_PWDNCTRL, 1, 1),

	SND_SOC_DAPM_DAC("DAC1", "Playback", WM8770_PWDNCTRL, 2, 1),
	SND_SOC_DAPM_DAC("DAC2", "Playback", WM8770_PWDNCTRL, 3, 1),
	SND_SOC_DAPM_DAC("DAC3", "Playback", WM8770_PWDNCTRL, 4, 1),
	SND_SOC_DAPM_DAC("DAC4", "Playback", WM8770_PWDNCTRL, 5, 1),

	SND_SOC_DAPM_SUPPLY("VOUT12 Supply", SND_SOC_NOPM, 0, 0,
		vout12supply_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("VOUT34 Supply", SND_SOC_NOPM, 0, 0,
		vout34supply_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER("VOUT1 Mixer", SND_SOC_NOPM, 0, 0,
		vout1_mix_controls, ARRAY_SIZE(vout1_mix_controls)),
	SND_SOC_DAPM_MIXER("VOUT2 Mixer", SND_SOC_NOPM, 0, 0,
		vout2_mix_controls, ARRAY_SIZE(vout2_mix_controls)),
	SND_SOC_DAPM_MIXER("VOUT3 Mixer", SND_SOC_NOPM, 0, 0,
		vout3_mix_controls, ARRAY_SIZE(vout3_mix_controls)),
	SND_SOC_DAPM_MIXER("VOUT4 Mixer", SND_SOC_NOPM, 0, 0,
		vout4_mix_controls, ARRAY_SIZE(vout4_mix_controls)),

	SND_SOC_DAPM_OUTPUT("VOUT1"),
	SND_SOC_DAPM_OUTPUT("VOUT2"),
	SND_SOC_DAPM_OUTPUT("VOUT3"),
	SND_SOC_DAPM_OUTPUT("VOUT4")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8770_पूर्णांकercon[] = अणु
	अणु "Capture Mux", "AIN1", "AIN1" पूर्ण,
	अणु "Capture Mux", "AIN2", "AIN2" पूर्ण,
	अणु "Capture Mux", "AIN3", "AIN3" पूर्ण,
	अणु "Capture Mux", "AIN4", "AIN4" पूर्ण,
	अणु "Capture Mux", "AIN5", "AIN5" पूर्ण,
	अणु "Capture Mux", "AIN6", "AIN6" पूर्ण,
	अणु "Capture Mux", "AIN7", "AIN7" पूर्ण,
	अणु "Capture Mux", "AIN8", "AIN8" पूर्ण,

	अणु "ADC", शून्य, "Capture Mux" पूर्ण,

	अणु "VOUT1 Mixer", शून्य, "VOUT12 Supply" पूर्ण,
	अणु "VOUT1 Mixer", "DAC1 Switch", "DAC1" पूर्ण,
	अणु "VOUT1 Mixer", "AUX1 Switch", "AUX1" पूर्ण,
	अणु "VOUT1 Mixer", "Bypass Switch", "Capture Mux" पूर्ण,

	अणु "VOUT2 Mixer", शून्य, "VOUT12 Supply" पूर्ण,
	अणु "VOUT2 Mixer", "DAC2 Switch", "DAC2" पूर्ण,
	अणु "VOUT2 Mixer", "AUX2 Switch", "AUX2" पूर्ण,
	अणु "VOUT2 Mixer", "Bypass Switch", "Capture Mux" पूर्ण,

	अणु "VOUT3 Mixer", शून्य, "VOUT34 Supply" पूर्ण,
	अणु "VOUT3 Mixer", "DAC3 Switch", "DAC3" पूर्ण,
	अणु "VOUT3 Mixer", "AUX3 Switch", "AUX3" पूर्ण,
	अणु "VOUT3 Mixer", "Bypass Switch", "Capture Mux" पूर्ण,

	अणु "VOUT4 Mixer", शून्य, "VOUT34 Supply" पूर्ण,
	अणु "VOUT4 Mixer", "DAC4 Switch", "DAC4" पूर्ण,
	अणु "VOUT4 Mixer", "Bypass Switch", "Capture Mux" पूर्ण,

	अणु "VOUT1", शून्य, "VOUT1 Mixer" पूर्ण,
	अणु "VOUT2", शून्य, "VOUT2 Mixer" पूर्ण,
	अणु "VOUT3", शून्य, "VOUT3 Mixer" पूर्ण,
	अणु "VOUT4", शून्य, "VOUT4 Mixer" पूर्ण
पूर्ण;

अटल पूर्णांक vout12supply_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, WM8770_OUTMUX1, 0x180, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8770_OUTMUX1, 0x180, 0x180);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vout34supply_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, WM8770_OUTMUX2, 0x180, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8770_OUTMUX2, 0x180, 0x180);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8770_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, WM8770_RESET, 0);
पूर्ण

अटल पूर्णांक wm8770_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक अगरace, master;

	component = dai->component;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master = 0x100;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगरace = 0;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0xc;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x8;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8770_IFACECTRL, 0xf, अगरace);
	snd_soc_component_update_bits(component, WM8770_MSTRCTRL, 0x100, master);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक mclk_ratios[] = अणु
	128,
	192,
	256,
	384,
	512,
	768
पूर्ण;

अटल पूर्णांक wm8770_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8770_priv *wm8770;
	पूर्णांक i;
	पूर्णांक अगरace;
	पूर्णांक shअगरt;
	पूर्णांक ratio;

	component = dai->component;
	wm8770 = snd_soc_component_get_drvdata(component);

	अगरace = 0;
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x10;
		अवरोध;
	हाल 24:
		अगरace |= 0x20;
		अवरोध;
	हाल 32:
		अगरace |= 0x30;
		अवरोध;
	पूर्ण

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		i = 0;
		shअगरt = 4;
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		i = 2;
		shअगरt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Only need to set MCLK/LRCLK ratio अगर we're master */
	अगर (snd_soc_component_पढ़ो(component, WM8770_MSTRCTRL) & 0x100) अणु
		क्रम (; i < ARRAY_SIZE(mclk_ratios); ++i) अणु
			ratio = wm8770->sysclk / params_rate(params);
			अगर (ratio == mclk_ratios[i])
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(mclk_ratios)) अणु
			dev_err(component->dev,
				"Unable to configure MCLK ratio %d/%d\n",
				wm8770->sysclk, params_rate(params));
			वापस -EINVAL;
		पूर्ण

		dev_dbg(component->dev, "MCLK is %dfs\n", mclk_ratios[i]);

		snd_soc_component_update_bits(component, WM8770_MSTRCTRL, 0x7 << shअगरt,
				    i << shअगरt);
	पूर्ण

	snd_soc_component_update_bits(component, WM8770_IFACECTRL, 0x30, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8770_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component;

	component = dai->component;
	वापस snd_soc_component_update_bits(component, WM8770_DACMUTE, 0x10,
				   !!mute << 4);
पूर्ण

अटल पूर्णांक wm8770_set_sysclk(काष्ठा snd_soc_dai *dai,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8770_priv *wm8770;

	component = dai->component;
	wm8770 = snd_soc_component_get_drvdata(component);
	wm8770->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8770_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret;
	काष्ठा wm8770_priv *wm8770;

	wm8770 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8770->supplies),
						    wm8770->supplies);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			regcache_sync(wm8770->regmap);

			/* global घातerup */
			snd_soc_component_ग_लिखो(component, WM8770_PWDNCTRL, 0);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* global घातerकरोwn */
		snd_soc_component_ग_लिखो(component, WM8770_PWDNCTRL, 1);
		regulator_bulk_disable(ARRAY_SIZE(wm8770->supplies),
				       wm8770->supplies);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8770_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8770_dai_ops = अणु
	.mute_stream = wm8770_mute,
	.hw_params = wm8770_hw_params,
	.set_fmt = wm8770_set_fmt,
	.set_sysclk = wm8770_set_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8770_dai = अणु
	.name = "wm8770-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = WM8770_FORMATS
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = WM8770_FORMATS
	पूर्ण,
	.ops = &wm8770_dai_ops,
	.symmetric_rate = 1
पूर्ण;

अटल पूर्णांक wm8770_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8770_priv *wm8770;
	पूर्णांक ret;

	wm8770 = snd_soc_component_get_drvdata(component);
	wm8770->component = component;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8770->supplies),
				    wm8770->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm8770_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	/* latch the volume update bits */
	snd_soc_component_update_bits(component, WM8770_MSDIGVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_MSALGVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT1RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT2RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT3RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT4RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC1RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC2RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC3RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC4RVOL, 0x100, 0x100);

	/* mute all DACs */
	snd_soc_component_update_bits(component, WM8770_DACMUTE, 0x10, 0x10);

err_reg_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8770->supplies), wm8770->supplies);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8770 = अणु
	.probe			= wm8770_probe,
	.set_bias_level		= wm8770_set_bias_level,
	.controls		= wm8770_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8770_snd_controls),
	.dapm_widमाला_लो		= wm8770_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8770_dapm_widमाला_लो),
	.dapm_routes		= wm8770_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(wm8770_पूर्णांकercon),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8770_of_match[] = अणु
	अणु .compatible = "wlf,wm8770", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8770_of_match);

अटल स्थिर काष्ठा regmap_config wm8770_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8770_RESET,

	.reg_शेषs = wm8770_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8770_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8770_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक wm8770_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8770_priv *wm8770;
	पूर्णांक ret, i;

	wm8770 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8770_priv),
			      GFP_KERNEL);
	अगर (!wm8770)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(wm8770->supplies); i++)
		wm8770->supplies[i].supply = wm8770_supply_names[i];

	ret = devm_regulator_bulk_get(&spi->dev, ARRAY_SIZE(wm8770->supplies),
				      wm8770->supplies);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8770->disable_nb[0].notअगरier_call = wm8770_regulator_event_0;
	wm8770->disable_nb[1].notअगरier_call = wm8770_regulator_event_1;
	wm8770->disable_nb[2].notअगरier_call = wm8770_regulator_event_2;

	/* This should really be moved पूर्णांकo the regulator core */
	क्रम (i = 0; i < ARRAY_SIZE(wm8770->supplies); i++) अणु
		ret = devm_regulator_रेजिस्टर_notअगरier(
						wm8770->supplies[i].consumer,
						&wm8770->disable_nb[i]);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"Failed to register regulator notifier: %d\n",
				ret);
		पूर्ण
	पूर्ण

	wm8770->regmap = devm_regmap_init_spi(spi, &wm8770_regmap);
	अगर (IS_ERR(wm8770->regmap))
		वापस PTR_ERR(wm8770->regmap);

	spi_set_drvdata(spi, wm8770);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
				     &soc_component_dev_wm8770, &wm8770_dai, 1);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8770_spi_driver = अणु
	.driver = अणु
		.name = "wm8770",
		.of_match_table = wm8770_of_match,
	पूर्ण,
	.probe = wm8770_spi_probe,
पूर्ण;

module_spi_driver(wm8770_spi_driver);

MODULE_DESCRIPTION("ASoC WM8770 driver");
MODULE_AUTHOR("Dimitris Papastamos <dp@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
