<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This driver supports the analog controls क्रम the पूर्णांकernal codec
 * found in Allwinner's A31s, A23, A33 and H3 SoCs.
 *
 * Copyright 2016 Chen-Yu Tsai <wens@csie.org>
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
#घोषणा SUN8I_ADDA_HP_VOLC		0x00
#घोषणा SUN8I_ADDA_HP_VOLC_PA_CLK_GATE		7
#घोषणा SUN8I_ADDA_HP_VOLC_HP_VOL		0
#घोषणा SUN8I_ADDA_LOMIXSC		0x01
#घोषणा SUN8I_ADDA_LOMIXSC_MIC1			6
#घोषणा SUN8I_ADDA_LOMIXSC_MIC2			5
#घोषणा SUN8I_ADDA_LOMIXSC_PHONE		4
#घोषणा SUN8I_ADDA_LOMIXSC_PHONEN		3
#घोषणा SUN8I_ADDA_LOMIXSC_LINEINL		2
#घोषणा SUN8I_ADDA_LOMIXSC_DACL			1
#घोषणा SUN8I_ADDA_LOMIXSC_DACR			0
#घोषणा SUN8I_ADDA_ROMIXSC		0x02
#घोषणा SUN8I_ADDA_ROMIXSC_MIC1			6
#घोषणा SUN8I_ADDA_ROMIXSC_MIC2			5
#घोषणा SUN8I_ADDA_ROMIXSC_PHONE		4
#घोषणा SUN8I_ADDA_ROMIXSC_PHONEP		3
#घोषणा SUN8I_ADDA_ROMIXSC_LINEINR		2
#घोषणा SUN8I_ADDA_ROMIXSC_DACR			1
#घोषणा SUN8I_ADDA_ROMIXSC_DACL			0
#घोषणा SUN8I_ADDA_DAC_PA_SRC		0x03
#घोषणा SUN8I_ADDA_DAC_PA_SRC_DACAREN		7
#घोषणा SUN8I_ADDA_DAC_PA_SRC_DACALEN		6
#घोषणा SUN8I_ADDA_DAC_PA_SRC_RMIXEN		5
#घोषणा SUN8I_ADDA_DAC_PA_SRC_LMIXEN		4
#घोषणा SUN8I_ADDA_DAC_PA_SRC_RHPPAMUTE		3
#घोषणा SUN8I_ADDA_DAC_PA_SRC_LHPPAMUTE		2
#घोषणा SUN8I_ADDA_DAC_PA_SRC_RHPIS		1
#घोषणा SUN8I_ADDA_DAC_PA_SRC_LHPIS		0
#घोषणा SUN8I_ADDA_PHONEIN_GCTRL	0x04
#घोषणा SUN8I_ADDA_PHONEIN_GCTRL_PHONEPG	4
#घोषणा SUN8I_ADDA_PHONEIN_GCTRL_PHONENG	0
#घोषणा SUN8I_ADDA_LINEIN_GCTRL		0x05
#घोषणा SUN8I_ADDA_LINEIN_GCTRL_LINEING		4
#घोषणा SUN8I_ADDA_LINEIN_GCTRL_PHONEG		0
#घोषणा SUN8I_ADDA_MICIN_GCTRL		0x06
#घोषणा SUN8I_ADDA_MICIN_GCTRL_MIC1G		4
#घोषणा SUN8I_ADDA_MICIN_GCTRL_MIC2G		0
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL		0x07
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN		7
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_LINEOUTEN	7	/* H3 specअगरic */
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_HPCOM_FC	5
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_COMPTEN		4
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_PA_ANTI_POP_CTRL	2
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_LTRNMUTE	1
#घोषणा SUN8I_ADDA_PAEN_HP_CTRL_RTLNMUTE	0
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL	0x08
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL_PHONEOUTG	5
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL_PHONEOUTEN	4
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL_PHONEOUT_MIC1	3
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL_PHONEOUT_MIC2	2
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL_PHONEOUT_RMIX	1
#घोषणा SUN8I_ADDA_PHONEOUT_CTRL_PHONEOUT_LMIX	0
#घोषणा SUN8I_ADDA_PHONE_GAIN_CTRL	0x09
#घोषणा SUN8I_ADDA_PHONE_GAIN_CTRL_LINEOUT_VOL	3
#घोषणा SUN8I_ADDA_PHONE_GAIN_CTRL_PHONEPREG	0
#घोषणा SUN8I_ADDA_MIC2G_CTRL		0x0a
#घोषणा SUN8I_ADDA_MIC2G_CTRL_MIC2AMPEN		7
#घोषणा SUN8I_ADDA_MIC2G_CTRL_MIC2BOOST		4
#घोषणा SUN8I_ADDA_MIC2G_CTRL_LINEOUTLEN	3
#घोषणा SUN8I_ADDA_MIC2G_CTRL_LINEOUTREN	2
#घोषणा SUN8I_ADDA_MIC2G_CTRL_LINEOUTLSRC	1
#घोषणा SUN8I_ADDA_MIC2G_CTRL_LINEOUTRSRC	0
#घोषणा SUN8I_ADDA_MIC1G_MICBIAS_CTRL	0x0b
#घोषणा SUN8I_ADDA_MIC1G_MICBIAS_CTRL_HMICBIASEN	7
#घोषणा SUN8I_ADDA_MIC1G_MICBIAS_CTRL_MMICBIASEN	6
#घोषणा SUN8I_ADDA_MIC1G_MICBIAS_CTRL_HMICBIAS_MODE	5
#घोषणा SUN8I_ADDA_MIC1G_MICBIAS_CTRL_MIC1AMPEN		3
#घोषणा SUN8I_ADDA_MIC1G_MICBIAS_CTRL_MIC1BOOST		0
#घोषणा SUN8I_ADDA_LADCMIXSC		0x0c
#घोषणा SUN8I_ADDA_LADCMIXSC_MIC1		6
#घोषणा SUN8I_ADDA_LADCMIXSC_MIC2		5
#घोषणा SUN8I_ADDA_LADCMIXSC_PHONE		4
#घोषणा SUN8I_ADDA_LADCMIXSC_PHONEN		3
#घोषणा SUN8I_ADDA_LADCMIXSC_LINEINL		2
#घोषणा SUN8I_ADDA_LADCMIXSC_OMIXRL		1
#घोषणा SUN8I_ADDA_LADCMIXSC_OMIXRR		0
#घोषणा SUN8I_ADDA_RADCMIXSC		0x0d
#घोषणा SUN8I_ADDA_RADCMIXSC_MIC1		6
#घोषणा SUN8I_ADDA_RADCMIXSC_MIC2		5
#घोषणा SUN8I_ADDA_RADCMIXSC_PHONE		4
#घोषणा SUN8I_ADDA_RADCMIXSC_PHONEP		3
#घोषणा SUN8I_ADDA_RADCMIXSC_LINEINR		2
#घोषणा SUN8I_ADDA_RADCMIXSC_OMIXR		1
#घोषणा SUN8I_ADDA_RADCMIXSC_OMIXL		0
#घोषणा SUN8I_ADDA_RES			0x0e
#घोषणा SUN8I_ADDA_RES_MMICBIAS_SEL		4
#घोषणा SUN8I_ADDA_RES_PA_ANTI_POP_CTRL		0
#घोषणा SUN8I_ADDA_ADC_AP_EN		0x0f
#घोषणा SUN8I_ADDA_ADC_AP_EN_ADCREN		7
#घोषणा SUN8I_ADDA_ADC_AP_EN_ADCLEN		6
#घोषणा SUN8I_ADDA_ADC_AP_EN_ADCG		0

/* mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("DAC Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_DACL, 1, 0),
	SOC_DAPM_DOUBLE_R("DAC Reversed Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_DACR, 1, 0),
	SOC_DAPM_DOUBLE_R("Line In Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_LINEINL, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic1 Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_MIC1, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic2 Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_MIC2, 1, 0),
पूर्ण;

/* mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_v3s_codec_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("DAC Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_DACL, 1, 0),
	SOC_DAPM_DOUBLE_R("DAC Reversed Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_DACR, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic1 Playback Switch",
			  SUN8I_ADDA_LOMIXSC,
			  SUN8I_ADDA_ROMIXSC,
			  SUN8I_ADDA_LOMIXSC_MIC1, 1, 0),
पूर्ण;

/* ADC mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_adc_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("Mixer Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_OMIXRL, 1, 0),
	SOC_DAPM_DOUBLE_R("Mixer Reversed Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_OMIXRR, 1, 0),
	SOC_DAPM_DOUBLE_R("Line In Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_LINEINL, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic1 Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_MIC1, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic2 Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_MIC2, 1, 0),
पूर्ण;

/* ADC mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_v3s_codec_adc_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("Mixer Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_OMIXRL, 1, 0),
	SOC_DAPM_DOUBLE_R("Mixer Reversed Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_OMIXRR, 1, 0),
	SOC_DAPM_DOUBLE_R("Mic1 Capture Switch",
			  SUN8I_ADDA_LADCMIXSC,
			  SUN8I_ADDA_RADCMIXSC,
			  SUN8I_ADDA_LADCMIXSC_MIC1, 1, 0),
पूर्ण;

/* volume / mute controls */
अटल स्थिर DECLARE_TLV_DB_SCALE(sun8i_codec_out_mixer_pregain_scale,
				  -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(sun8i_codec_mic_gain_scale,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 7, TLV_DB_SCALE_ITEM(2400, 300, 0),
);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_common_controls[] = अणु
	/* Mixer pre-gain */
	SOC_SINGLE_TLV("Mic1 Playback Volume", SUN8I_ADDA_MICIN_GCTRL,
		       SUN8I_ADDA_MICIN_GCTRL_MIC1G,
		       0x7, 0, sun8i_codec_out_mixer_pregain_scale),

	/* Microphone Amp boost gain */
	SOC_SINGLE_TLV("Mic1 Boost Volume", SUN8I_ADDA_MIC1G_MICBIAS_CTRL,
		       SUN8I_ADDA_MIC1G_MICBIAS_CTRL_MIC1BOOST, 0x7, 0,
		       sun8i_codec_mic_gain_scale),

	/* ADC */
	SOC_SINGLE_TLV("ADC Gain Capture Volume", SUN8I_ADDA_ADC_AP_EN,
		       SUN8I_ADDA_ADC_AP_EN_ADCG, 0x7, 0,
		       sun8i_codec_out_mixer_pregain_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_common_widमाला_लो[] = अणु
	/* ADC */
	SND_SOC_DAPM_ADC("Left ADC", शून्य, SUN8I_ADDA_ADC_AP_EN,
			 SUN8I_ADDA_ADC_AP_EN_ADCLEN, 0),
	SND_SOC_DAPM_ADC("Right ADC", शून्य, SUN8I_ADDA_ADC_AP_EN,
			 SUN8I_ADDA_ADC_AP_EN_ADCREN, 0),

	/* DAC */
	SND_SOC_DAPM_DAC("Left DAC", शून्य, SUN8I_ADDA_DAC_PA_SRC,
			 SUN8I_ADDA_DAC_PA_SRC_DACALEN, 0),
	SND_SOC_DAPM_DAC("Right DAC", शून्य, SUN8I_ADDA_DAC_PA_SRC,
			 SUN8I_ADDA_DAC_PA_SRC_DACAREN, 0),
	/*
	 * Due to this component and the codec beदीर्घing to separate DAPM
	 * contexts, we need to manually link the above widमाला_लो to their
	 * stream widमाला_लो at the card level.
	 */

	/* Microphone input */
	SND_SOC_DAPM_INPUT("MIC1"),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic1 Amplifier", SUN8I_ADDA_MIC1G_MICBIAS_CTRL,
			 SUN8I_ADDA_MIC1G_MICBIAS_CTRL_MIC1AMPEN, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_mixer_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Left Mixer", SUN8I_ADDA_DAC_PA_SRC,
			   SUN8I_ADDA_DAC_PA_SRC_LMIXEN, 0,
			   sun8i_codec_mixer_controls,
			   ARRAY_SIZE(sun8i_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SUN8I_ADDA_DAC_PA_SRC,
			   SUN8I_ADDA_DAC_PA_SRC_RMIXEN, 0,
			   sun8i_codec_mixer_controls,
			   ARRAY_SIZE(sun8i_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Left ADC Mixer", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCLEN, 0,
			   sun8i_codec_adc_mixer_controls,
			   ARRAY_SIZE(sun8i_codec_adc_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right ADC Mixer", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCREN, 0,
			   sun8i_codec_adc_mixer_controls,
			   ARRAY_SIZE(sun8i_codec_adc_mixer_controls)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_v3s_codec_mixer_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Left Mixer", SUN8I_ADDA_DAC_PA_SRC,
			   SUN8I_ADDA_DAC_PA_SRC_LMIXEN, 0,
			   sun8i_v3s_codec_mixer_controls,
			   ARRAY_SIZE(sun8i_v3s_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SUN8I_ADDA_DAC_PA_SRC,
			   SUN8I_ADDA_DAC_PA_SRC_RMIXEN, 0,
			   sun8i_v3s_codec_mixer_controls,
			   ARRAY_SIZE(sun8i_v3s_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("Left ADC Mixer", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCLEN, 0,
			   sun8i_v3s_codec_adc_mixer_controls,
			   ARRAY_SIZE(sun8i_v3s_codec_adc_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right ADC Mixer", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCREN, 0,
			   sun8i_v3s_codec_adc_mixer_controls,
			   ARRAY_SIZE(sun8i_v3s_codec_adc_mixer_controls)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_common_routes[] = अणु
	/* Microphone Routes */
	अणु "Mic1 Amplifier", शून्य, "MIC1"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_mixer_routes[] = अणु
	/* Left Mixer Routes */
	अणु "Left Mixer", "DAC Playback Switch", "Left DAC" पूर्ण,
	अणु "Left Mixer", "DAC Reversed Playback Switch", "Right DAC" पूर्ण,
	अणु "Left Mixer", "Mic1 Playback Switch", "Mic1 Amplifier" पूर्ण,

	/* Right Mixer Routes */
	अणु "Right Mixer", "DAC Playback Switch", "Right DAC" पूर्ण,
	अणु "Right Mixer", "DAC Reversed Playback Switch", "Left DAC" पूर्ण,
	अणु "Right Mixer", "Mic1 Playback Switch", "Mic1 Amplifier" पूर्ण,

	/* Left ADC Mixer Routes */
	अणु "Left ADC Mixer", "Mixer Capture Switch", "Left Mixer" पूर्ण,
	अणु "Left ADC Mixer", "Mixer Reversed Capture Switch", "Right Mixer" पूर्ण,
	अणु "Left ADC Mixer", "Mic1 Capture Switch", "Mic1 Amplifier" पूर्ण,

	/* Right ADC Mixer Routes */
	अणु "Right ADC Mixer", "Mixer Capture Switch", "Right Mixer" पूर्ण,
	अणु "Right ADC Mixer", "Mixer Reversed Capture Switch", "Left Mixer" पूर्ण,
	अणु "Right ADC Mixer", "Mic1 Capture Switch", "Mic1 Amplifier" पूर्ण,

	/* ADC Routes */
	अणु "Left ADC", शून्य, "Left ADC Mixer" पूर्ण,
	अणु "Right ADC", शून्य, "Right ADC Mixer" पूर्ण,
पूर्ण;

/* headphone specअगरic controls, widमाला_लो, and routes */
अटल स्थिर DECLARE_TLV_DB_SCALE(sun8i_codec_hp_vol_scale, -6300, 100, 1);
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_headphone_controls[] = अणु
	SOC_SINGLE_TLV("Headphone Playback Volume",
		       SUN8I_ADDA_HP_VOLC,
		       SUN8I_ADDA_HP_VOLC_HP_VOL, 0x3f, 0,
		       sun8i_codec_hp_vol_scale),
	SOC_DOUBLE("Headphone Playback Switch",
		   SUN8I_ADDA_DAC_PA_SRC,
		   SUN8I_ADDA_DAC_PA_SRC_LHPPAMUTE,
		   SUN8I_ADDA_DAC_PA_SRC_RHPPAMUTE, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर sun8i_codec_hp_src_क्रमागत_text[] = अणु
	"DAC", "Mixer",
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun8i_codec_hp_src_क्रमागत,
			    SUN8I_ADDA_DAC_PA_SRC,
			    SUN8I_ADDA_DAC_PA_SRC_LHPIS,
			    SUN8I_ADDA_DAC_PA_SRC_RHPIS,
			    sun8i_codec_hp_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_hp_src[] = अणु
	SOC_DAPM_ENUM("Headphone Source Playback Route",
		      sun8i_codec_hp_src_क्रमागत),
पूर्ण;

अटल पूर्णांक sun8i_headphone_amp_event(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		snd_soc_component_update_bits(component, SUN8I_ADDA_PAEN_HP_CTRL,
					      BIT(SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN),
					      BIT(SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN));
		/*
		 * Need a delay to have the amplअगरier up. 700ms seems the best
		 * compromise between the समय to let the amplअगरier up and the
		 * समय not to feel this delay जबतक playing a sound.
		 */
		msleep(700);
	पूर्ण अन्यथा अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		snd_soc_component_update_bits(component, SUN8I_ADDA_PAEN_HP_CTRL,
					      BIT(SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN),
					      0x0);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_headphone_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Headphone Source Playback Route",
			 SND_SOC_NOPM, 0, 0, sun8i_codec_hp_src),
	SND_SOC_DAPM_OUT_DRV_E("Headphone Amp", SUN8I_ADDA_PAEN_HP_CTRL,
			       SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN, 0, शून्य, 0,
			       sun8i_headphone_amp_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("HPCOM Protection", SUN8I_ADDA_PAEN_HP_CTRL,
			    SUN8I_ADDA_PAEN_HP_CTRL_COMPTEN, 0, शून्य, 0),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "HPCOM", SUN8I_ADDA_PAEN_HP_CTRL,
			 SUN8I_ADDA_PAEN_HP_CTRL_HPCOM_FC, 0x3, 0x3, 0),
	SND_SOC_DAPM_OUTPUT("HP"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_headphone_routes[] = अणु
	अणु "Headphone Source Playback Route", "DAC", "Left DAC" पूर्ण,
	अणु "Headphone Source Playback Route", "DAC", "Right DAC" पूर्ण,
	अणु "Headphone Source Playback Route", "Mixer", "Left Mixer" पूर्ण,
	अणु "Headphone Source Playback Route", "Mixer", "Right Mixer" पूर्ण,
	अणु "Headphone Amp", शून्य, "Headphone Source Playback Route" पूर्ण,
	अणु "HPCOM", शून्य, "HPCOM Protection" पूर्ण,
	अणु "HP", शून्य, "Headphone Amp" पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_add_headphone(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	ret = snd_soc_add_component_controls(cmpnt,
					     sun8i_codec_headphone_controls,
					     ARRAY_SIZE(sun8i_codec_headphone_controls));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Headphone controls: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_headphone_widमाला_लो,
					ARRAY_SIZE(sun8i_codec_headphone_widमाला_लो));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Headphone DAPM widgets: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_headphone_routes,
				      ARRAY_SIZE(sun8i_codec_headphone_routes));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Headphone DAPM routes: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* mbias specअगरic widget */
अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_mbias_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("MBIAS", SUN8I_ADDA_MIC1G_MICBIAS_CTRL,
			    SUN8I_ADDA_MIC1G_MICBIAS_CTRL_MMICBIASEN,
			    0, शून्य, 0),
पूर्ण;

अटल पूर्णांक sun8i_codec_add_mbias(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_mbias_widमाला_लो,
					ARRAY_SIZE(sun8i_codec_mbias_widमाला_लो));
	अगर (ret)
		dev_err(dev, "Failed to add MBIAS DAPM widgets: %d\n", ret);

	वापस ret;
पूर्ण

/* hmic specअगरic widget */
अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_hmic_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("HBIAS", SUN8I_ADDA_MIC1G_MICBIAS_CTRL,
			    SUN8I_ADDA_MIC1G_MICBIAS_CTRL_HMICBIASEN,
			    0, शून्य, 0),
पूर्ण;

अटल पूर्णांक sun8i_codec_add_hmic(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_hmic_widमाला_लो,
					ARRAY_SIZE(sun8i_codec_hmic_widमाला_लो));
	अगर (ret)
		dev_err(dev, "Failed to add Mic3 DAPM widgets: %d\n", ret);

	वापस ret;
पूर्ण

/* line in specअगरic controls, widमाला_लो and rines */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_linein_controls[] = अणु
	/* Mixer pre-gain */
	SOC_SINGLE_TLV("Line In Playback Volume", SUN8I_ADDA_LINEIN_GCTRL,
		       SUN8I_ADDA_LINEIN_GCTRL_LINEING,
		       0x7, 0, sun8i_codec_out_mixer_pregain_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_linein_widमाला_लो[] = अणु
	/* Line input */
	SND_SOC_DAPM_INPUT("LINEIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_linein_routes[] = अणु
	अणु "Left Mixer", "Line In Playback Switch", "LINEIN" पूर्ण,

	अणु "Right Mixer", "Line In Playback Switch", "LINEIN" पूर्ण,

	अणु "Left ADC Mixer", "Line In Capture Switch", "LINEIN" पूर्ण,

	अणु "Right ADC Mixer", "Line In Capture Switch", "LINEIN" पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_add_linein(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	ret = snd_soc_add_component_controls(cmpnt,
					     sun8i_codec_linein_controls,
					     ARRAY_SIZE(sun8i_codec_linein_controls));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Line In controls: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_linein_widमाला_लो,
					ARRAY_SIZE(sun8i_codec_linein_widमाला_लो));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Line In DAPM widgets: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_linein_routes,
				      ARRAY_SIZE(sun8i_codec_linein_routes));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Line In DAPM routes: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


/* line out specअगरic controls, widमाला_लो and routes */
अटल स्थिर DECLARE_TLV_DB_RANGE(sun8i_codec_lineout_vol_scale,
	0, 1, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	2, 31, TLV_DB_SCALE_ITEM(-4350, 150, 0),
);
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_lineout_controls[] = अणु
	SOC_SINGLE_TLV("Line Out Playback Volume",
		       SUN8I_ADDA_PHONE_GAIN_CTRL,
		       SUN8I_ADDA_PHONE_GAIN_CTRL_LINEOUT_VOL, 0x1f, 0,
		       sun8i_codec_lineout_vol_scale),
	SOC_DOUBLE("Line Out Playback Switch",
		   SUN8I_ADDA_MIC2G_CTRL,
		   SUN8I_ADDA_MIC2G_CTRL_LINEOUTLEN,
		   SUN8I_ADDA_MIC2G_CTRL_LINEOUTREN, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर sun8i_codec_lineout_src_क्रमागत_text[] = अणु
	"Stereo", "Mono Differential",
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun8i_codec_lineout_src_क्रमागत,
			    SUN8I_ADDA_MIC2G_CTRL,
			    SUN8I_ADDA_MIC2G_CTRL_LINEOUTLSRC,
			    SUN8I_ADDA_MIC2G_CTRL_LINEOUTRSRC,
			    sun8i_codec_lineout_src_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_lineout_src[] = अणु
	SOC_DAPM_ENUM("Line Out Source Playback Route",
		      sun8i_codec_lineout_src_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_lineout_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Line Out Source Playback Route",
			 SND_SOC_NOPM, 0, 0, sun8i_codec_lineout_src),
	/* It is unclear अगर this is a buffer or gate, model it as a supply */
	SND_SOC_DAPM_SUPPLY("Line Out Enable", SUN8I_ADDA_PAEN_HP_CTRL,
			    SUN8I_ADDA_PAEN_HP_CTRL_LINEOUTEN, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("LINEOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_lineout_routes[] = अणु
	अणु "Line Out Source Playback Route", "Stereo", "Left Mixer" पूर्ण,
	अणु "Line Out Source Playback Route", "Stereo", "Right Mixer" पूर्ण,
	अणु "Line Out Source Playback Route", "Mono Differential", "Left Mixer" पूर्ण,
	अणु "Line Out Source Playback Route", "Mono Differential", "Right Mixer" पूर्ण,
	अणु "LINEOUT", शून्य, "Line Out Source Playback Route" पूर्ण,
	अणु "LINEOUT", शून्य, "Line Out Enable", पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_add_lineout(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	ret = snd_soc_add_component_controls(cmpnt,
					     sun8i_codec_lineout_controls,
					     ARRAY_SIZE(sun8i_codec_lineout_controls));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Line Out controls: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_lineout_widमाला_लो,
					ARRAY_SIZE(sun8i_codec_lineout_widमाला_लो));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Line Out DAPM widgets: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_lineout_routes,
				      ARRAY_SIZE(sun8i_codec_lineout_routes));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Line Out DAPM routes: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* mic2 specअगरic controls, widमाला_लो and routes */
अटल स्थिर काष्ठा snd_kcontrol_new sun8i_codec_mic2_controls[] = अणु
	/* Mixer pre-gain */
	SOC_SINGLE_TLV("Mic2 Playback Volume",
		       SUN8I_ADDA_MICIN_GCTRL, SUN8I_ADDA_MICIN_GCTRL_MIC2G,
		       0x7, 0, sun8i_codec_out_mixer_pregain_scale),

	/* Microphone Amp boost gain */
	SOC_SINGLE_TLV("Mic2 Boost Volume", SUN8I_ADDA_MIC2G_CTRL,
		       SUN8I_ADDA_MIC2G_CTRL_MIC2BOOST, 0x7, 0,
		       sun8i_codec_mic_gain_scale),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_mic2_widमाला_लो[] = अणु
	/* Microphone input */
	SND_SOC_DAPM_INPUT("MIC2"),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic2 Amplifier", SUN8I_ADDA_MIC2G_CTRL,
			 SUN8I_ADDA_MIC2G_CTRL_MIC2AMPEN, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_mic2_routes[] = अणु
	अणु "Mic2 Amplifier", शून्य, "MIC2"पूर्ण,

	अणु "Left Mixer", "Mic2 Playback Switch", "Mic2 Amplifier" पूर्ण,

	अणु "Right Mixer", "Mic2 Playback Switch", "Mic2 Amplifier" पूर्ण,

	अणु "Left ADC Mixer", "Mic2 Capture Switch", "Mic2 Amplifier" पूर्ण,

	अणु "Right ADC Mixer", "Mic2 Capture Switch", "Mic2 Amplifier" पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_add_mic2(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	ret = snd_soc_add_component_controls(cmpnt,
					     sun8i_codec_mic2_controls,
					     ARRAY_SIZE(sun8i_codec_mic2_controls));
	अगर (ret) अणु
		dev_err(dev, "Failed to add MIC2 controls: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_mic2_widमाला_लो,
					ARRAY_SIZE(sun8i_codec_mic2_widमाला_लो));
	अगर (ret) अणु
		dev_err(dev, "Failed to add MIC2 DAPM widgets: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_mic2_routes,
				      ARRAY_SIZE(sun8i_codec_mic2_routes));
	अगर (ret) अणु
		dev_err(dev, "Failed to add MIC2 DAPM routes: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा sun8i_codec_analog_quirks अणु
	bool has_headphone;
	bool has_hmic;
	bool has_linein;
	bool has_lineout;
	bool has_mbias;
	bool has_mic2;
पूर्ण;

अटल स्थिर काष्ठा sun8i_codec_analog_quirks sun8i_a23_quirks = अणु
	.has_headphone	= true,
	.has_hmic	= true,
	.has_linein	= true,
	.has_mbias	= true,
	.has_mic2	= true,
पूर्ण;

अटल स्थिर काष्ठा sun8i_codec_analog_quirks sun8i_h3_quirks = अणु
	.has_linein	= true,
	.has_lineout	= true,
	.has_mbias	= true,
	.has_mic2	= true,
पूर्ण;

अटल पूर्णांक sun8i_codec_analog_add_mixer(काष्ठा snd_soc_component *cmpnt,
					स्थिर काष्ठा sun8i_codec_analog_quirks *quirks)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा device *dev = cmpnt->dev;
	पूर्णांक ret;

	अगर (!quirks->has_mic2 && !quirks->has_linein) अणु
		/*
		 * Apply the special widget set which has uses a control
		 * without MIC2 and Line In, क्रम SoCs without these.
		 * TODO: not all special हालs are supported now, this हाल
		 * is present because it's the हाल of V3s.
		 */
		ret = snd_soc_dapm_new_controls(dapm,
						sun8i_v3s_codec_mixer_widमाला_लो,
						ARRAY_SIZE(sun8i_v3s_codec_mixer_widमाला_लो));
		अगर (ret) अणु
			dev_err(dev, "Failed to add V3s Mixer DAPM widgets: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Apply the generic mixer widget set. */
		ret = snd_soc_dapm_new_controls(dapm,
						sun8i_codec_mixer_widमाला_लो,
						ARRAY_SIZE(sun8i_codec_mixer_widमाला_लो));
		अगर (ret) अणु
			dev_err(dev, "Failed to add Mixer DAPM widgets: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_mixer_routes,
				      ARRAY_SIZE(sun8i_codec_mixer_routes));
	अगर (ret) अणु
		dev_err(dev, "Failed to add Mixer DAPM routes: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun8i_codec_analog_quirks sun8i_v3s_quirks = अणु
	.has_headphone	= true,
	.has_hmic	= true,
पूर्ण;

अटल पूर्णांक sun8i_codec_analog_cmpnt_probe(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा device *dev = cmpnt->dev;
	स्थिर काष्ठा sun8i_codec_analog_quirks *quirks;
	पूर्णांक ret;

	/*
	 * This would never वापस शून्य unless someone directly रेजिस्टरs a
	 * platक्रमm device matching this driver's name, without specअगरying a
	 * device tree node.
	 */
	quirks = of_device_get_match_data(dev);

	/* Add controls, widमाला_लो, and routes क्रम inभागidual features */
	ret = sun8i_codec_analog_add_mixer(cmpnt, quirks);
	अगर (ret)
		वापस ret;

	अगर (quirks->has_headphone) अणु
		ret = sun8i_codec_add_headphone(cmpnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (quirks->has_hmic) अणु
		ret = sun8i_codec_add_hmic(cmpnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (quirks->has_linein) अणु
		ret = sun8i_codec_add_linein(cmpnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (quirks->has_lineout) अणु
		ret = sun8i_codec_add_lineout(cmpnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (quirks->has_mbias) अणु
		ret = sun8i_codec_add_mbias(cmpnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (quirks->has_mic2) अणु
		ret = sun8i_codec_add_mic2(cmpnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sun8i_codec_analog_cmpnt_drv = अणु
	.controls		= sun8i_codec_common_controls,
	.num_controls		= ARRAY_SIZE(sun8i_codec_common_controls),
	.dapm_widमाला_लो		= sun8i_codec_common_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun8i_codec_common_widमाला_लो),
	.dapm_routes		= sun8i_codec_common_routes,
	.num_dapm_routes	= ARRAY_SIZE(sun8i_codec_common_routes),
	.probe			= sun8i_codec_analog_cmpnt_probe,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun8i_codec_analog_of_match[] = अणु
	अणु
		.compatible = "allwinner,sun8i-a23-codec-analog",
		.data = &sun8i_a23_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-codec-analog",
		.data = &sun8i_h3_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-v3s-codec-analog",
		.data = &sun8i_v3s_quirks,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_codec_analog_of_match);

अटल पूर्णांक sun8i_codec_analog_probe(काष्ठा platक्रमm_device *pdev)
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
					       &sun8i_codec_analog_cmpnt_drv,
					       शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver sun8i_codec_analog_driver = अणु
	.driver = अणु
		.name = "sun8i-codec-analog",
		.of_match_table = sun8i_codec_analog_of_match,
	पूर्ण,
	.probe = sun8i_codec_analog_probe,
पूर्ण;
module_platक्रमm_driver(sun8i_codec_analog_driver);

MODULE_DESCRIPTION("Allwinner internal codec analog controls driver");
MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sun8i-codec-analog");
