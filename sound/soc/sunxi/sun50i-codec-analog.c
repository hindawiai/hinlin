<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * This driver supports the analog controls क्रम the पूर्णांकernal codec
 * found in Allwinner's A64 SoC.
 *
 * Copyright (C) 2016 Chen-Yu Tsai <wens@csie.org>
 * Copyright (C) 2017 Marcus Cooper <codekipper@gmail.com>
 * Copyright (C) 2018 Vasily Khoruzhick <anarsoul@gmail.com>
 *
 * Based on sun8i-codec-analog.c
 *
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "sun8i-adda-pr-regmap.h"

/* Codec analog control रेजिस्टर offsets and bit fields */
#घोषणा SUN50I_ADDA_HP_CTRL		0x00
#घोषणा SUN50I_ADDA_HP_CTRL_PA_CLK_GATE		7
#घोषणा SUN50I_ADDA_HP_CTRL_HPPA_EN		6
#घोषणा SUN50I_ADDA_HP_CTRL_HPVOL		0

#घोषणा SUN50I_ADDA_OL_MIX_CTRL		0x01
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_MIC1		6
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_MIC2		5
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_PHONE		4
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_PHONEN		3
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_LINEINL		2
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_DACL		1
#घोषणा SUN50I_ADDA_OL_MIX_CTRL_DACR		0

#घोषणा SUN50I_ADDA_OR_MIX_CTRL		0x02
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_MIC1		6
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_MIC2		5
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_PHONE		4
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_PHONEP		3
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_LINEINR		2
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_DACR		1
#घोषणा SUN50I_ADDA_OR_MIX_CTRL_DACL		0

#घोषणा SUN50I_ADDA_EARPIECE_CTRL0	0x03
#घोषणा SUN50I_ADDA_EARPIECE_CTRL0_EAR_RAMP_TIME	4
#घोषणा SUN50I_ADDA_EARPIECE_CTRL0_ESPSR		0

#घोषणा SUN50I_ADDA_EARPIECE_CTRL1	0x04
#घोषणा SUN50I_ADDA_EARPIECE_CTRL1_ESPPA_EN	7
#घोषणा SUN50I_ADDA_EARPIECE_CTRL1_ESPPA_MUTE	6
#घोषणा SUN50I_ADDA_EARPIECE_CTRL1_ESP_VOL	0

#घोषणा SUN50I_ADDA_LINEOUT_CTRL0	0x05
#घोषणा SUN50I_ADDA_LINEOUT_CTRL0_LEN		7
#घोषणा SUN50I_ADDA_LINEOUT_CTRL0_REN		6
#घोषणा SUN50I_ADDA_LINEOUT_CTRL0_LSRC_SEL	5
#घोषणा SUN50I_ADDA_LINEOUT_CTRL0_RSRC_SEL	4

#घोषणा SUN50I_ADDA_LINEOUT_CTRL1	0x06
#घोषणा SUN50I_ADDA_LINEOUT_CTRL1_VOL		0

#घोषणा SUN50I_ADDA_MIC1_CTRL		0x07
#घोषणा SUN50I_ADDA_MIC1_CTRL_MIC1G		4
#घोषणा SUN50I_ADDA_MIC1_CTRL_MIC1AMPEN		3
#घोषणा SUN50I_ADDA_MIC1_CTRL_MIC1BOOST		0

#घोषणा SUN50I_ADDA_MIC2_CTRL		0x08
#घोषणा SUN50I_ADDA_MIC2_CTRL_MIC2G		4
#घोषणा SUN50I_ADDA_MIC2_CTRL_MIC2AMPEN		3
#घोषणा SUN50I_ADDA_MIC2_CTRL_MIC2BOOST		0

#घोषणा SUN50I_ADDA_LINEIN_CTRL		0x09
#घोषणा SUN50I_ADDA_LINEIN_CTRL_LINEING		0

#घोषणा SUN50I_ADDA_MIX_DAC_CTRL	0x0a
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_DACAREN	7
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_DACALEN	6
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_RMIXEN		5
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_LMIXEN		4
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_RHPPAMUTE	3
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_LHPPAMUTE	2
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_RHPIS		1
#घोषणा SUN50I_ADDA_MIX_DAC_CTRL_LHPIS		0

#घोषणा SUN50I_ADDA_L_ADCMIX_SRC	0x0b
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_MIC1		6
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_MIC2		5
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_PHONE		4
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_PHONEN		3
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_LINEINL	2
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_OMIXRL		1
#घोषणा SUN50I_ADDA_L_ADCMIX_SRC_OMIXRR		0

#घोषणा SUN50I_ADDA_R_ADCMIX_SRC	0x0c
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_MIC1		6
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_MIC2		5
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_PHONE		4
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_PHONEP		3
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_LINEINR	2
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_OMIXR		1
#घोषणा SUN50I_ADDA_R_ADCMIX_SRC_OMIXL		0

#घोषणा SUN50I_ADDA_ADC_CTRL		0x0d
#घोषणा SUN50I_ADDA_ADC_CTRL_ADCREN		7
#घोषणा SUN50I_ADDA_ADC_CTRL_ADCLEN		6
#घोषणा SUN50I_ADDA_ADC_CTRL_ADCG		0

#घोषणा SUN50I_ADDA_HS_MBIAS_CTRL	0x0e
#घोषणा SUN50I_ADDA_HS_MBIAS_CTRL_MMICBIASEN	7

#घोषणा SUN50I_ADDA_JACK_MIC_CTRL	0x1d
#घोषणा SUN50I_ADDA_JACK_MIC_CTRL_HMICBIASEN	5

/* mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun50i_a64_codec_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("Mic1 Playback Switch",
			  SUN50I_ADDA_OL_MIX_CTRL,
			  SUN50I_ADDA_OR_MIX_CTRL,
			  SUN50I_ADDA_OL_MIX_CTRL_MIC1, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic2 Playback Switch",
			  SUN50I_ADDA_OL_MIX_CTRL,
			  SUN50I_ADDA_OR_MIX_CTRL,
			  SUN50I_ADDA_OL_MIX_CTRL_MIC2, 1, 0),
	SOC_DAPM_DOUBLE_R("Line In Playback Switch",
			  SUN50I_ADDA_OL_MIX_CTRL,
			  SUN50I_ADDA_OR_MIX_CTRL,
			  SUN50I_ADDA_OL_MIX_CTRL_LINEINL, 1, 0),
	SOC_DAPM_DOUBLE_R("DAC Playback Switch",
			  SUN50I_ADDA_OL_MIX_CTRL,
			  SUN50I_ADDA_OR_MIX_CTRL,
			  SUN50I_ADDA_OL_MIX_CTRL_DACL, 1, 0),
	SOC_DAPM_DOUBLE_R("DAC Reversed Playback Switch",
			  SUN50I_ADDA_OL_MIX_CTRL,
			  SUN50I_ADDA_OR_MIX_CTRL,
			  SUN50I_ADDA_OL_MIX_CTRL_DACR, 1, 0),
पूर्ण;

/* ADC mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_adc_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("Mic1 Capture Switch",
			  SUN50I_ADDA_L_ADCMIX_SRC,
			  SUN50I_ADDA_R_ADCMIX_SRC,
			  SUN50I_ADDA_L_ADCMIX_SRC_MIC1, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic2 Capture Switch",
			  SUN50I_ADDA_L_ADCMIX_SRC,
			  SUN50I_ADDA_R_ADCMIX_SRC,
			  SUN50I_ADDA_L_ADCMIX_SRC_MIC2, 1, 0),
	SOC_DAPM_DOUBLE_R("Line In Capture Switch",
			  SUN50I_ADDA_L_ADCMIX_SRC,
			  SUN50I_ADDA_R_ADCMIX_SRC,
			  SUN50I_ADDA_L_ADCMIX_SRC_LINEINL, 1, 0),
	SOC_DAPM_DOUBLE_R("Mixer Capture Switch",
			  SUN50I_ADDA_L_ADCMIX_SRC,
			  SUN50I_ADDA_R_ADCMIX_SRC,
			  SUN50I_ADDA_L_ADCMIX_SRC_OMIXRL, 1, 0),
	SOC_DAPM_DOUBLE_R("Mixer Reversed Capture Switch",
			  SUN50I_ADDA_L_ADCMIX_SRC,
			  SUN50I_ADDA_R_ADCMIX_SRC,
			  SUN50I_ADDA_L_ADCMIX_SRC_OMIXRR, 1, 0),
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(sun50i_codec_out_mixer_pregain_scale,
				  -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(sun50i_codec_mic_gain_scale,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 7, TLV_DB_SCALE_ITEM(2400, 300, 0),
);

अटल स्थिर DECLARE_TLV_DB_SCALE(sun50i_codec_hp_vol_scale, -6300, 100, 1);

अटल स्थिर DECLARE_TLV_DB_RANGE(sun50i_codec_lineout_vol_scale,
	0, 1, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	2, 31, TLV_DB_SCALE_ITEM(-4350, 150, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(sun50i_codec_earpiece_vol_scale,
	0, 1, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	2, 31, TLV_DB_SCALE_ITEM(-4350, 150, 0),
);

/* volume / mute controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun50i_a64_codec_controls[] = अणु
	SOC_SINGLE_TLV("Headphone Playback Volume",
		       SUN50I_ADDA_HP_CTRL,
		       SUN50I_ADDA_HP_CTRL_HPVOL, 0x3f, 0,
		       sun50i_codec_hp_vol_scale),

	/* Mixer pre-gain */
	SOC_SINGLE_TLV("Mic1 Playback Volume", SUN50I_ADDA_MIC1_CTRL,
		       SUN50I_ADDA_MIC1_CTRL_MIC1G,
		       0x7, 0, sun50i_codec_out_mixer_pregain_scale),

	/* Microphone Amp boost gain */
	SOC_SINGLE_TLV("Mic1 Boost Volume", SUN50I_ADDA_MIC1_CTRL,
		       SUN50I_ADDA_MIC1_CTRL_MIC1BOOST, 0x7, 0,
		       sun50i_codec_mic_gain_scale),

	/* Mixer pre-gain */
	SOC_SINGLE_TLV("Mic2 Playback Volume",
		       SUN50I_ADDA_MIC2_CTRL, SUN50I_ADDA_MIC2_CTRL_MIC2G,
		       0x7, 0, sun50i_codec_out_mixer_pregain_scale),

	/* Microphone Amp boost gain */
	SOC_SINGLE_TLV("Mic2 Boost Volume", SUN50I_ADDA_MIC2_CTRL,
		       SUN50I_ADDA_MIC2_CTRL_MIC2BOOST, 0x7, 0,
		       sun50i_codec_mic_gain_scale),

	/* ADC */
	SOC_SINGLE_TLV("ADC Gain Capture Volume", SUN50I_ADDA_ADC_CTRL,
		       SUN50I_ADDA_ADC_CTRL_ADCG, 0x7, 0,
		       sun50i_codec_out_mixer_pregain_scale),

	/* Mixer pre-gain */
	SOC_SINGLE_TLV("Line In Playback Volume", SUN50I_ADDA_LINEIN_CTRL,
		       SUN50I_ADDA_LINEIN_CTRL_LINEING,
		       0x7, 0, sun50i_codec_out_mixer_pregain_scale),

	SOC_SINGLE_TLV("Line Out Playback Volume",
		       SUN50I_ADDA_LINEOUT_CTRL1,
		       SUN50I_ADDA_LINEOUT_CTRL1_VOL, 0x1f, 0,
		       sun50i_codec_lineout_vol_scale),

	SOC_SINGLE_TLV("Earpiece Playback Volume",
		       SUN50I_ADDA_EARPIECE_CTRL1,
		       SUN50I_ADDA_EARPIECE_CTRL1_ESP_VOL, 0x1f, 0,
		       sun50i_codec_earpiece_vol_scale),
पूर्ण;

अटल स्थिर अक्षर * स्थिर sun50i_codec_hp_src_क्रमागत_text[] = अणु
	"DAC", "Mixer",
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun50i_codec_hp_src_क्रमागत,
			    SUN50I_ADDA_MIX_DAC_CTRL,
			    SUN50I_ADDA_MIX_DAC_CTRL_LHPIS,
			    SUN50I_ADDA_MIX_DAC_CTRL_RHPIS,
			    sun50i_codec_hp_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_hp_src[] = अणु
	SOC_DAPM_ENUM("Headphone Source Playback Route",
		      sun50i_codec_hp_src_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_hp_चयन =
	SOC_DAPM_DOUBLE("Headphone Playback Switch",
			SUN50I_ADDA_MIX_DAC_CTRL,
			SUN50I_ADDA_MIX_DAC_CTRL_LHPPAMUTE,
			SUN50I_ADDA_MIX_DAC_CTRL_RHPPAMUTE, 1, 0);

अटल स्थिर अक्षर * स्थिर sun50i_codec_lineout_src_क्रमागत_text[] = अणु
	"Stereo", "Mono Differential",
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun50i_codec_lineout_src_क्रमागत,
			    SUN50I_ADDA_LINEOUT_CTRL0,
			    SUN50I_ADDA_LINEOUT_CTRL0_LSRC_SEL,
			    SUN50I_ADDA_LINEOUT_CTRL0_RSRC_SEL,
			    sun50i_codec_lineout_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_lineout_src[] = अणु
	SOC_DAPM_ENUM("Line Out Source Playback Route",
		      sun50i_codec_lineout_src_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_lineout_चयन =
	SOC_DAPM_DOUBLE("Line Out Playback Switch",
			SUN50I_ADDA_LINEOUT_CTRL0,
			SUN50I_ADDA_LINEOUT_CTRL0_LEN,
			SUN50I_ADDA_LINEOUT_CTRL0_REN, 1, 0);

अटल स्थिर अक्षर * स्थिर sun50i_codec_earpiece_src_क्रमागत_text[] = अणु
	"DACR", "DACL", "Right Mixer", "Left Mixer",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sun50i_codec_earpiece_src_क्रमागत,
			    SUN50I_ADDA_EARPIECE_CTRL0,
			    SUN50I_ADDA_EARPIECE_CTRL0_ESPSR,
			    sun50i_codec_earpiece_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_earpiece_src[] = अणु
	SOC_DAPM_ENUM("Earpiece Source Playback Route",
		      sun50i_codec_earpiece_src_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun50i_codec_earpiece_चयन[] = अणु
	SOC_DAPM_SINGLE("Earpiece Playback Switch",
			SUN50I_ADDA_EARPIECE_CTRL1,
			SUN50I_ADDA_EARPIECE_CTRL1_ESPPA_MUTE, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun50i_a64_codec_widमाला_लो[] = अणु
	/* DAC */
	SND_SOC_DAPM_DAC("Left DAC", शून्य, SUN50I_ADDA_MIX_DAC_CTRL,
			 SUN50I_ADDA_MIX_DAC_CTRL_DACALEN, 0),
	SND_SOC_DAPM_DAC("Right DAC", शून्य, SUN50I_ADDA_MIX_DAC_CTRL,
			 SUN50I_ADDA_MIX_DAC_CTRL_DACAREN, 0),
	/* ADC */
	SND_SOC_DAPM_ADC("Left ADC", शून्य, SUN50I_ADDA_ADC_CTRL,
			 SUN50I_ADDA_ADC_CTRL_ADCLEN, 0),
	SND_SOC_DAPM_ADC("Right ADC", शून्य, SUN50I_ADDA_ADC_CTRL,
			 SUN50I_ADDA_ADC_CTRL_ADCREN, 0),
	/*
	 * Due to this component and the codec beदीर्घing to separate DAPM
	 * contexts, we need to manually link the above widमाला_लो to their
	 * stream widमाला_लो at the card level.
	 */

	SND_SOC_DAPM_REGULATOR_SUPPLY("cpvdd", 0, 0),
	SND_SOC_DAPM_MUX("Left Headphone Source",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_hp_src),
	SND_SOC_DAPM_MUX("Right Headphone Source",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_hp_src),
	SND_SOC_DAPM_SWITCH("Left Headphone Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_hp_चयन),
	SND_SOC_DAPM_SWITCH("Right Headphone Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_hp_चयन),
	SND_SOC_DAPM_OUT_DRV("Left Headphone Amp",
			     SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Right Headphone Amp",
			     SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Headphone Amp", SUN50I_ADDA_HP_CTRL,
			     SUN50I_ADDA_HP_CTRL_HPPA_EN, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("HP"),

	SND_SOC_DAPM_MUX("Left Line Out Source",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_lineout_src),
	SND_SOC_DAPM_MUX("Right Line Out Source",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_lineout_src),
	SND_SOC_DAPM_SWITCH("Left Line Out Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_lineout_चयन),
	SND_SOC_DAPM_SWITCH("Right Line Out Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_lineout_चयन),
	SND_SOC_DAPM_OUTPUT("LINEOUT"),

	SND_SOC_DAPM_MUX("Earpiece Source Playback Route",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_earpiece_src),
	SOC_MIXER_NAMED_CTL_ARRAY("Earpiece Switch",
				  SND_SOC_NOPM, 0, 0,
				  sun50i_codec_earpiece_चयन),
	SND_SOC_DAPM_OUT_DRV("Earpiece Amp", SUN50I_ADDA_EARPIECE_CTRL1,
			     SUN50I_ADDA_EARPIECE_CTRL1_ESPPA_EN, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("EARPIECE"),

	/* Microphone inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC1"),

	/* Microphone Bias */
	SND_SOC_DAPM_SUPPLY("MBIAS", SUN50I_ADDA_HS_MBIAS_CTRL,
			    SUN50I_ADDA_HS_MBIAS_CTRL_MMICBIASEN,
			    0, शून्य, 0),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic1 Amplifier", SUN50I_ADDA_MIC1_CTRL,
			 SUN50I_ADDA_MIC1_CTRL_MIC1AMPEN, 0, शून्य, 0),

	/* Microphone input */
	SND_SOC_DAPM_INPUT("MIC2"),

	/* Microphone Bias */
	SND_SOC_DAPM_SUPPLY("HBIAS", SUN50I_ADDA_JACK_MIC_CTRL,
			    SUN50I_ADDA_JACK_MIC_CTRL_HMICBIASEN,
			    0, शून्य, 0),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic2 Amplifier", SUN50I_ADDA_MIC2_CTRL,
			 SUN50I_ADDA_MIC2_CTRL_MIC2AMPEN, 0, शून्य, 0),

	/* Line input */
	SND_SOC_DAPM_INPUT("LINEIN"),

	/* Mixers */
	SND_SOC_DAPM_MIXER("Left Mixer", SUN50I_ADDA_MIX_DAC_CTRL,
			   SUN50I_ADDA_MIX_DAC_CTRL_LMIXEN, 0,
			   sun50i_a64_codec_mixer_controls,
			   ARRAY_SIZE(sun50i_a64_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SUN50I_ADDA_MIX_DAC_CTRL,
			   SUN50I_ADDA_MIX_DAC_CTRL_RMIXEN, 0,
			   sun50i_a64_codec_mixer_controls,
			   ARRAY_SIZE(sun50i_a64_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Left ADC Mixer", SND_SOC_NOPM, 0, 0,
			   sun50i_codec_adc_mixer_controls,
			   ARRAY_SIZE(sun50i_codec_adc_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right ADC Mixer", SND_SOC_NOPM, 0, 0,
			   sun50i_codec_adc_mixer_controls,
			   ARRAY_SIZE(sun50i_codec_adc_mixer_controls)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun50i_a64_codec_routes[] = अणु
	/* Left Mixer Routes */
	अणु "Left Mixer", "Mic1 Playback Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Left Mixer", "Mic2 Playback Switch", "Mic2 Amplifier" पूर्ण,
	अणु "Left Mixer", "Line In Playback Switch", "LINEIN" पूर्ण,
	अणु "Left Mixer", "DAC Playback Switch", "Left DAC" पूर्ण,
	अणु "Left Mixer", "DAC Reversed Playback Switch", "Right DAC" पूर्ण,

	/* Right Mixer Routes */
	अणु "Right Mixer", "Mic1 Playback Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Right Mixer", "Mic2 Playback Switch", "Mic2 Amplifier" पूर्ण,
	अणु "Right Mixer", "Line In Playback Switch", "LINEIN" पूर्ण,
	अणु "Right Mixer", "DAC Playback Switch", "Right DAC" पूर्ण,
	अणु "Right Mixer", "DAC Reversed Playback Switch", "Left DAC" पूर्ण,

	/* Left ADC Mixer Routes */
	अणु "Left ADC Mixer", "Mic1 Capture Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Left ADC Mixer", "Mic2 Capture Switch", "Mic2 Amplifier" पूर्ण,
	अणु "Left ADC Mixer", "Line In Capture Switch", "LINEIN" पूर्ण,
	अणु "Left ADC Mixer", "Mixer Capture Switch", "Left Mixer" पूर्ण,
	अणु "Left ADC Mixer", "Mixer Reversed Capture Switch", "Right Mixer" पूर्ण,

	/* Right ADC Mixer Routes */
	अणु "Right ADC Mixer", "Mic1 Capture Switch", "Mic1 Amplifier" पूर्ण,
	अणु "Right ADC Mixer", "Mic2 Capture Switch", "Mic2 Amplifier" पूर्ण,
	अणु "Right ADC Mixer", "Line In Capture Switch", "LINEIN" पूर्ण,
	अणु "Right ADC Mixer", "Mixer Capture Switch", "Right Mixer" पूर्ण,
	अणु "Right ADC Mixer", "Mixer Reversed Capture Switch", "Left Mixer" पूर्ण,

	/* ADC Routes */
	अणु "Left ADC", शून्य, "Left ADC Mixer" पूर्ण,
	अणु "Right ADC", शून्य, "Right ADC Mixer" पूर्ण,

	/* Headphone Routes */
	अणु "Left Headphone Source", "DAC", "Left DAC" पूर्ण,
	अणु "Left Headphone Source", "Mixer", "Left Mixer" पूर्ण,
	अणु "Left Headphone Switch", "Headphone Playback Switch", "Left Headphone Source" पूर्ण,
	अणु "Left Headphone Amp", शून्य, "Left Headphone Switch" पूर्ण,
	अणु "Left Headphone Amp", शून्य, "Headphone Amp" पूर्ण,
	अणु "HP", शून्य, "Left Headphone Amp" पूर्ण,

	अणु "Right Headphone Source", "DAC", "Right DAC" पूर्ण,
	अणु "Right Headphone Source", "Mixer", "Right Mixer" पूर्ण,
	अणु "Right Headphone Switch", "Headphone Playback Switch", "Right Headphone Source" पूर्ण,
	अणु "Right Headphone Amp", शून्य, "Right Headphone Switch" पूर्ण,
	अणु "Right Headphone Amp", शून्य, "Headphone Amp" पूर्ण,
	अणु "HP", शून्य, "Right Headphone Amp" पूर्ण,

	अणु "Headphone Amp", शून्य, "cpvdd" पूर्ण,

	/* Microphone Routes */
	अणु "Mic1 Amplifier", शून्य, "MIC1"पूर्ण,

	/* Microphone Routes */
	अणु "Mic2 Amplifier", शून्य, "MIC2"पूर्ण,

	/* Line-out Routes */
	अणु "Left Line Out Source", "Stereo", "Left Mixer" पूर्ण,
	अणु "Left Line Out Source", "Mono Differential", "Left Mixer" पूर्ण,
	अणु "Left Line Out Source", "Mono Differential", "Right Mixer" पूर्ण,
	अणु "Left Line Out Switch", "Line Out Playback Switch", "Left Line Out Source" पूर्ण,
	अणु "LINEOUT", शून्य, "Left Line Out Switch" पूर्ण,

	अणु "Right Line Out Switch", "Line Out Playback Switch", "Right Mixer" पूर्ण,
	अणु "Right Line Out Source", "Stereo", "Right Line Out Switch" पूर्ण,
	अणु "Right Line Out Source", "Mono Differential", "Left Line Out Switch" पूर्ण,
	अणु "LINEOUT", शून्य, "Right Line Out Source" पूर्ण,

	/* Earpiece Routes */
	अणु "Earpiece Source Playback Route", "DACL", "Left DAC" पूर्ण,
	अणु "Earpiece Source Playback Route", "DACR", "Right DAC" पूर्ण,
	अणु "Earpiece Source Playback Route", "Left Mixer", "Left Mixer" पूर्ण,
	अणु "Earpiece Source Playback Route", "Right Mixer", "Right Mixer" पूर्ण,
	अणु "Earpiece Switch", "Earpiece Playback Switch", "Earpiece Source Playback Route" पूर्ण,
	अणु "Earpiece Amp", शून्य, "Earpiece Switch" पूर्ण,
	अणु "EARPIECE", शून्य, "Earpiece Amp" पूर्ण,
पूर्ण;

अटल पूर्णांक sun50i_a64_codec_suspend(काष्ठा snd_soc_component *component)
अणु
	वापस regmap_update_bits(component->regmap, SUN50I_ADDA_HP_CTRL,
				  BIT(SUN50I_ADDA_HP_CTRL_PA_CLK_GATE),
				  BIT(SUN50I_ADDA_HP_CTRL_PA_CLK_GATE));
पूर्ण

अटल पूर्णांक sun50i_a64_codec_resume(काष्ठा snd_soc_component *component)
अणु
	वापस regmap_update_bits(component->regmap, SUN50I_ADDA_HP_CTRL,
				  BIT(SUN50I_ADDA_HP_CTRL_PA_CLK_GATE), 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sun50i_codec_analog_cmpnt_drv = अणु
	.controls		= sun50i_a64_codec_controls,
	.num_controls		= ARRAY_SIZE(sun50i_a64_codec_controls),
	.dapm_widमाला_लो		= sun50i_a64_codec_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun50i_a64_codec_widमाला_लो),
	.dapm_routes		= sun50i_a64_codec_routes,
	.num_dapm_routes	= ARRAY_SIZE(sun50i_a64_codec_routes),
	.suspend		= sun50i_a64_codec_suspend,
	.resume			= sun50i_a64_codec_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun50i_codec_analog_of_match[] = अणु
	अणु
		.compatible = "allwinner,sun50i-a64-codec-analog",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun50i_codec_analog_of_match);

अटल पूर्णांक sun50i_codec_analog_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	व्योम __iomem *base;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		dev_err(&pdev->dev, "Failed to map the registers\n");
		वापस PTR_ERR(base);
	पूर्ण

	regmap = sun8i_adda_pr_regmap_init(&pdev->dev, base);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&pdev->dev, "Failed to create regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					       &sun50i_codec_analog_cmpnt_drv,
					       शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver sun50i_codec_analog_driver = अणु
	.driver = अणु
		.name = "sun50i-codec-analog",
		.of_match_table = sun50i_codec_analog_of_match,
	पूर्ण,
	.probe = sun50i_codec_analog_probe,
पूर्ण;
module_platक्रमm_driver(sun50i_codec_analog_driver);

MODULE_DESCRIPTION("Allwinner internal codec analog controls driver for A64");
MODULE_AUTHOR("Vasily Khoruzhick <anarsoul@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sun50i-codec-analog");
