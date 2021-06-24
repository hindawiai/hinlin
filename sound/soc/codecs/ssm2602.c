<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// File:         sound/soc/codecs/ssm2602.c
// Author:       Clअगरf Cai <Clअगरf.Cai@analog.com>
//
// Created:      Tue June 06 2008
// Description:  Driver क्रम ssm2602 sound chip
//
// Modअगरied:
//               Copyright 2008 Analog Devices Inc.
//
// Bugs:         Enter bugs at http://blackfin.uclinux.org/

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "ssm2602.h"

/* codec निजी data */
काष्ठा ssm2602_priv अणु
	अचिन्हित पूर्णांक sysclk;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *sysclk_स्थिरraपूर्णांकs;

	काष्ठा regmap *regmap;

	क्रमागत ssm2602_type type;
	अचिन्हित पूर्णांक clk_out_pwr;
पूर्ण;

/*
 * ssm2602 रेजिस्टर cache
 * We can't पढ़ो the ssm2602 रेजिस्टर space when we are
 * using 2 wire क्रम device control, so we cache them instead.
 * There is no poपूर्णांक in caching the reset रेजिस्टर
 */
अटल स्थिर काष्ठा reg_शेष ssm2602_reg[SSM2602_CACHEREGNUM] = अणु
	अणु .reg = 0x00, .def = 0x0097 पूर्ण,
	अणु .reg = 0x01, .def = 0x0097 पूर्ण,
	अणु .reg = 0x02, .def = 0x0079 पूर्ण,
	अणु .reg = 0x03, .def = 0x0079 पूर्ण,
	अणु .reg = 0x04, .def = 0x000a पूर्ण,
	अणु .reg = 0x05, .def = 0x0008 पूर्ण,
	अणु .reg = 0x06, .def = 0x009f पूर्ण,
	अणु .reg = 0x07, .def = 0x000a पूर्ण,
	अणु .reg = 0x08, .def = 0x0000 पूर्ण,
	अणु .reg = 0x09, .def = 0x0000 पूर्ण
पूर्ण;


/*Appending several "None"s just क्रम OSS mixer use*/
अटल स्थिर अक्षर *ssm2602_input_select[] = अणु
	"Line", "Mic",
पूर्ण;

अटल स्थिर अक्षर *ssm2602_deemph[] = अणु"None", "32Khz", "44.1Khz", "48Khz"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ssm2602_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(SSM2602_APANA, 2, ARRAY_SIZE(ssm2602_input_select),
			ssm2602_input_select),
	SOC_ENUM_SINGLE(SSM2602_APDIGI, 1, ARRAY_SIZE(ssm2602_deemph),
			ssm2602_deemph),
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(ssm260x_ouपंचांगix_tlv,
	0, 47, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 0),
	48, 127, TLV_DB_SCALE_ITEM(-7400, 100, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(ssm260x_inpga_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ssm260x_sidetone_tlv, -1500, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new ssm260x_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Capture Volume", SSM2602_LINVOL, SSM2602_RINVOL, 0, 45, 0,
	ssm260x_inpga_tlv),
SOC_DOUBLE_R("Capture Switch", SSM2602_LINVOL, SSM2602_RINVOL, 7, 1, 1),

SOC_SINGLE("ADC High Pass Filter Switch", SSM2602_APDIGI, 0, 1, 1),
SOC_SINGLE("Store DC Offset Switch", SSM2602_APDIGI, 4, 1, 0),

SOC_ENUM("Playback De-emphasis", ssm2602_क्रमागत[1]),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ssm2602_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Master Playback Volume", SSM2602_LOUT1V, SSM2602_ROUT1V,
	0, 127, 0, ssm260x_ouपंचांगix_tlv),
SOC_DOUBLE_R("Master Playback ZC Switch", SSM2602_LOUT1V, SSM2602_ROUT1V,
	7, 1, 0),
SOC_SINGLE_TLV("Sidetone Playback Volume", SSM2602_APANA, 6, 3, 1,
	ssm260x_sidetone_tlv),

SOC_SINGLE("Mic Boost (+20dB)", SSM2602_APANA, 0, 1, 0),
SOC_SINGLE("Mic Boost2 (+20dB)", SSM2602_APANA, 8, 1, 0),
पूर्ण;

/* Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ssm260x_output_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", SSM2602_APANA, 3, 1, 0),
SOC_DAPM_SINGLE("HiFi Playback Switch", SSM2602_APANA, 4, 1, 0),
SOC_DAPM_SINGLE("Mic Sidetone Switch", SSM2602_APANA, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mic_ctl =
	SOC_DAPM_SINGLE("Switch", SSM2602_APANA, 1, 1, 1);

/* Input mux */
अटल स्थिर काष्ठा snd_kcontrol_new ssm2602_input_mux_controls =
SOC_DAPM_ENUM("Input Select", ssm2602_क्रमागत[0]);

अटल पूर्णांक ssm2602_mic_चयन_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	/*
	 * According to the ssm2603 data sheet (control रेजिस्टर sequencing),
	 * the digital core should be activated only after all necessary bits
	 * in the घातer रेजिस्टर are enabled, and a delay determined by the
	 * decoupling capacitor on the VMID pin has passed. If the digital core
	 * is activated too early, or even beक्रमe the ADC is घातered up, audible
	 * artअगरacts appear at the beginning and end of the recorded संकेत.
	 *
	 * In practice, audible artअगरacts disappear well over 500 ms.
	 */
	msleep(500);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget ssm260x_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", SSM2602_PWR, 3, 1),
SND_SOC_DAPM_ADC("ADC", "HiFi Capture", SSM2602_PWR, 2, 1),
SND_SOC_DAPM_PGA("Line Input", SSM2602_PWR, 0, 1, शून्य, 0),

SND_SOC_DAPM_SUPPLY("Digital Core Power", SSM2602_ACTIVE, 0, 0, शून्य, 0),

SND_SOC_DAPM_OUTPUT("LOUT"),
SND_SOC_DAPM_OUTPUT("ROUT"),
SND_SOC_DAPM_INPUT("RLINEIN"),
SND_SOC_DAPM_INPUT("LLINEIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ssm2602_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MIXER("Output Mixer", SSM2602_PWR, 4, 1,
	ssm260x_output_mixer_controls,
	ARRAY_SIZE(ssm260x_output_mixer_controls)),

SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0, &ssm2602_input_mux_controls),
SND_SOC_DAPM_MICBIAS("Mic Bias", SSM2602_PWR, 1, 1),

SND_SOC_DAPM_SWITCH_E("Mic Switch", SSM2602_APANA, 1, 1, &mic_ctl,
		ssm2602_mic_चयन_event, SND_SOC_DAPM_PRE_PMU),

SND_SOC_DAPM_OUTPUT("LHPOUT"),
SND_SOC_DAPM_OUTPUT("RHPOUT"),
SND_SOC_DAPM_INPUT("MICIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ssm2604_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MIXER("Output Mixer", SND_SOC_NOPM, 0, 0,
	ssm260x_output_mixer_controls,
	ARRAY_SIZE(ssm260x_output_mixer_controls) - 1), /* Last element is the mic */
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ssm260x_routes[] = अणु
	अणु"DAC", शून्य, "Digital Core Power"पूर्ण,
	अणु"ADC", शून्य, "Digital Core Power"पूर्ण,

	अणु"Output Mixer", "Line Bypass Switch", "Line Input"पूर्ण,
	अणु"Output Mixer", "HiFi Playback Switch", "DAC"पूर्ण,

	अणु"ROUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LOUT", शून्य, "Output Mixer"पूर्ण,

	अणु"Line Input", शून्य, "LLINEIN"पूर्ण,
	अणु"Line Input", शून्य, "RLINEIN"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ssm2602_routes[] = अणु
	अणु"Output Mixer", "Mic Sidetone Switch", "Mic Bias"पूर्ण,

	अणु"RHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LHPOUT", शून्य, "Output Mixer"पूर्ण,

	अणु"Input Mux", "Line", "Line Input"पूर्ण,
	अणु"Input Mux", "Mic", "Mic Switch"पूर्ण,
	अणु"ADC", शून्य, "Input Mux"पूर्ण,

	अणु"Mic Switch", शून्य, "Mic Bias"पूर्ण,

	अणु"Mic Bias", शून्य, "MICIN"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ssm2604_routes[] = अणु
	अणु"ADC", शून्य, "Line Input"पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2602_rates_12288000[] = अणु
	8000, 16000, 32000, 48000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ssm2602_स्थिरraपूर्णांकs_12288000 = अणु
	.list = ssm2602_rates_12288000,
	.count = ARRAY_SIZE(ssm2602_rates_12288000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2602_rates_11289600[] = अणु
	8000, 11025, 22050, 44100, 88200,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ssm2602_स्थिरraपूर्णांकs_11289600 = अणु
	.list = ssm2602_rates_11289600,
	.count = ARRAY_SIZE(ssm2602_rates_11289600),
पूर्ण;

काष्ठा ssm2602_coeff अणु
	u32 mclk;
	u32 rate;
	u8 srate;
पूर्ण;

#घोषणा SSM2602_COEFF_SRATE(sr, bosr, usb) (((sr) << 2) | ((bosr) << 1) | (usb))

/* codec mclk घड़ी coefficients */
अटल स्थिर काष्ठा ssm2602_coeff ssm2602_coeff_table[] = अणु
	/* 48k */
	अणु12288000, 48000, SSM2602_COEFF_SRATE(0x0, 0x0, 0x0)पूर्ण,
	अणु18432000, 48000, SSM2602_COEFF_SRATE(0x0, 0x1, 0x0)पूर्ण,
	अणु12000000, 48000, SSM2602_COEFF_SRATE(0x0, 0x0, 0x1)पूर्ण,

	/* 32k */
	अणु12288000, 32000, SSM2602_COEFF_SRATE(0x6, 0x0, 0x0)पूर्ण,
	अणु18432000, 32000, SSM2602_COEFF_SRATE(0x6, 0x1, 0x0)पूर्ण,
	अणु12000000, 32000, SSM2602_COEFF_SRATE(0x6, 0x0, 0x1)पूर्ण,

	/* 16k */
	अणु12288000, 16000, SSM2602_COEFF_SRATE(0x5, 0x0, 0x0)पूर्ण,
	अणु18432000, 16000, SSM2602_COEFF_SRATE(0x5, 0x1, 0x0)पूर्ण,
	अणु12000000, 16000, SSM2602_COEFF_SRATE(0xa, 0x0, 0x1)पूर्ण,

	/* 8k */
	अणु12288000, 8000, SSM2602_COEFF_SRATE(0x3, 0x0, 0x0)पूर्ण,
	अणु18432000, 8000, SSM2602_COEFF_SRATE(0x3, 0x1, 0x0)पूर्ण,
	अणु11289600, 8000, SSM2602_COEFF_SRATE(0xb, 0x0, 0x0)पूर्ण,
	अणु16934400, 8000, SSM2602_COEFF_SRATE(0xb, 0x1, 0x0)पूर्ण,
	अणु12000000, 8000, SSM2602_COEFF_SRATE(0x3, 0x0, 0x1)पूर्ण,

	/* 96k */
	अणु12288000, 96000, SSM2602_COEFF_SRATE(0x7, 0x0, 0x0)पूर्ण,
	अणु18432000, 96000, SSM2602_COEFF_SRATE(0x7, 0x1, 0x0)पूर्ण,
	अणु12000000, 96000, SSM2602_COEFF_SRATE(0x7, 0x0, 0x1)पूर्ण,

	/* 11.025k */
	अणु11289600, 11025, SSM2602_COEFF_SRATE(0xc, 0x0, 0x0)पूर्ण,
	अणु16934400, 11025, SSM2602_COEFF_SRATE(0xc, 0x1, 0x0)पूर्ण,
	अणु12000000, 11025, SSM2602_COEFF_SRATE(0xc, 0x1, 0x1)पूर्ण,

	/* 22.05k */
	अणु11289600, 22050, SSM2602_COEFF_SRATE(0xd, 0x0, 0x0)पूर्ण,
	अणु16934400, 22050, SSM2602_COEFF_SRATE(0xd, 0x1, 0x0)पूर्ण,
	अणु12000000, 22050, SSM2602_COEFF_SRATE(0xd, 0x1, 0x1)पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, SSM2602_COEFF_SRATE(0x8, 0x0, 0x0)पूर्ण,
	अणु16934400, 44100, SSM2602_COEFF_SRATE(0x8, 0x1, 0x0)पूर्ण,
	अणु12000000, 44100, SSM2602_COEFF_SRATE(0x8, 0x1, 0x1)पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, SSM2602_COEFF_SRATE(0xf, 0x0, 0x0)पूर्ण,
	अणु16934400, 88200, SSM2602_COEFF_SRATE(0xf, 0x1, 0x0)पूर्ण,
	अणु12000000, 88200, SSM2602_COEFF_SRATE(0xf, 0x1, 0x1)पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक ssm2602_get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ssm2602_coeff_table); i++) अणु
		अगर (ssm2602_coeff_table[i].rate == rate &&
			ssm2602_coeff_table[i].mclk == mclk)
			वापस ssm2602_coeff_table[i].srate;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ssm2602_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);
	पूर्णांक srate = ssm2602_get_coeff(ssm2602->sysclk, params_rate(params));
	अचिन्हित पूर्णांक अगरace;

	अगर (srate < 0)
		वापस srate;

	regmap_ग_लिखो(ssm2602->regmap, SSM2602_SRATE, srate);

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अगरace = 0x0;
		अवरोध;
	हाल 20:
		अगरace = 0x4;
		अवरोध;
	हाल 24:
		अगरace = 0x8;
		अवरोध;
	हाल 32:
		अगरace = 0xc;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(ssm2602->regmap, SSM2602_IFACE,
		IFACE_AUDIO_DATA_LEN, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक ssm2602_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	अगर (ssm2602->sysclk_स्थिरraपूर्णांकs) अणु
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   ssm2602->sysclk_स्थिरraपूर्णांकs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssm2602_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(dai->component);

	अगर (mute)
		regmap_update_bits(ssm2602->regmap, SSM2602_APDIGI,
				    APDIGI_ENABLE_DAC_MUTE,
				    APDIGI_ENABLE_DAC_MUTE);
	अन्यथा
		regmap_update_bits(ssm2602->regmap, SSM2602_APDIGI,
				    APDIGI_ENABLE_DAC_MUTE, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ssm2602_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	अगर (dir == SND_SOC_CLOCK_IN) अणु
		अगर (clk_id != SSM2602_SYSCLK)
			वापस -EINVAL;

		चयन (freq) अणु
		हाल 12288000:
		हाल 18432000:
			ssm2602->sysclk_स्थिरraपूर्णांकs = &ssm2602_स्थिरraपूर्णांकs_12288000;
			अवरोध;
		हाल 11289600:
		हाल 16934400:
			ssm2602->sysclk_स्थिरraपूर्णांकs = &ssm2602_स्थिरraपूर्णांकs_11289600;
			अवरोध;
		हाल 12000000:
			ssm2602->sysclk_स्थिरraपूर्णांकs = शून्य;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ssm2602->sysclk = freq;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक mask;

		चयन (clk_id) अणु
		हाल SSM2602_CLK_CLKOUT:
			mask = PWR_CLK_OUT_PDN;
			अवरोध;
		हाल SSM2602_CLK_XTO:
			mask = PWR_OSC_PDN;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (freq == 0)
			ssm2602->clk_out_pwr |= mask;
		अन्यथा
			ssm2602->clk_out_pwr &= ~mask;

		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_CLK_OUT_PDN | PWR_OSC_PDN, ssm2602->clk_out_pwr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssm2602_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(codec_dai->component);
	अचिन्हित पूर्णांक अगरace = 0;

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
		अगरace |= 0x0013;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= 0x0003;
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
	regmap_ग_लिखो(ssm2602->regmap, SSM2602_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक ssm2602_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* vref/mid on, osc and clkout on अगर enabled */
		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_POWER_OFF | PWR_CLK_OUT_PDN | PWR_OSC_PDN,
			ssm2602->clk_out_pwr);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_POWER_OFF | PWR_CLK_OUT_PDN | PWR_OSC_PDN,
			PWR_CLK_OUT_PDN | PWR_OSC_PDN);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* everything off */
		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_POWER_OFF, PWR_POWER_OFF);
		अवरोध;

	पूर्ण
	वापस 0;
पूर्ण

#घोषणा SSM2602_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
		SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |\
		SNDRV_PCM_RATE_96000)

#घोषणा SSM2602_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops ssm2602_dai_ops = अणु
	.startup	= ssm2602_startup,
	.hw_params	= ssm2602_hw_params,
	.mute_stream	= ssm2602_mute,
	.set_sysclk	= ssm2602_set_dai_sysclk,
	.set_fmt	= ssm2602_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ssm2602_dai = अणु
	.name = "ssm2602-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SSM2602_RATES,
		.क्रमmats = SSM2602_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SSM2602_RATES,
		.क्रमmats = SSM2602_FORMATS,पूर्ण,
	.ops = &ssm2602_dai_ops,
	.symmetric_rate = 1,
	.symmetric_sample_bits = 1,
पूर्ण;

अटल पूर्णांक ssm2602_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	regcache_sync(ssm2602->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक ssm2602_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	regmap_update_bits(ssm2602->regmap, SSM2602_LOUT1V,
			    LOUT1V_LRHP_BOTH, LOUT1V_LRHP_BOTH);
	regmap_update_bits(ssm2602->regmap, SSM2602_ROUT1V,
			    ROUT1V_RLHP_BOTH, ROUT1V_RLHP_BOTH);

	ret = snd_soc_add_component_controls(component, ssm2602_snd_controls,
			ARRAY_SIZE(ssm2602_snd_controls));
	अगर (ret)
		वापस ret;

	ret = snd_soc_dapm_new_controls(dapm, ssm2602_dapm_widमाला_लो,
			ARRAY_SIZE(ssm2602_dapm_widमाला_लो));
	अगर (ret)
		वापस ret;

	वापस snd_soc_dapm_add_routes(dapm, ssm2602_routes,
			ARRAY_SIZE(ssm2602_routes));
पूर्ण

अटल पूर्णांक ssm2604_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(dapm, ssm2604_dapm_widमाला_लो,
			ARRAY_SIZE(ssm2604_dapm_widमाला_लो));
	अगर (ret)
		वापस ret;

	वापस snd_soc_dapm_add_routes(dapm, ssm2604_routes,
			ARRAY_SIZE(ssm2604_routes));
पूर्ण

अटल पूर्णांक ssm260x_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ssm2602->regmap, SSM2602_RESET, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	/* set the update bits */
	regmap_update_bits(ssm2602->regmap, SSM2602_LINVOL,
			    LINVOL_LRIN_BOTH, LINVOL_LRIN_BOTH);
	regmap_update_bits(ssm2602->regmap, SSM2602_RINVOL,
			    RINVOL_RLIN_BOTH, RINVOL_RLIN_BOTH);
	/*select Line in as शेष input*/
	regmap_ग_लिखो(ssm2602->regmap, SSM2602_APANA, APANA_SELECT_DAC |
			APANA_ENABLE_MIC_BOOST);

	चयन (ssm2602->type) अणु
	हाल SSM2602:
		ret = ssm2602_component_probe(component);
		अवरोध;
	हाल SSM2604:
		ret = ssm2604_component_probe(component);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ssm2602 = अणु
	.probe			= ssm260x_component_probe,
	.resume			= ssm2602_resume,
	.set_bias_level		= ssm2602_set_bias_level,
	.controls		= ssm260x_snd_controls,
	.num_controls		= ARRAY_SIZE(ssm260x_snd_controls),
	.dapm_widमाला_लो		= ssm260x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ssm260x_dapm_widमाला_लो),
	.dapm_routes		= ssm260x_routes,
	.num_dapm_routes	= ARRAY_SIZE(ssm260x_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल bool ssm2602_रेजिस्टर_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == SSM2602_RESET;
पूर्ण

स्थिर काष्ठा regmap_config ssm2602_regmap_config = अणु
	.val_bits = 9,
	.reg_bits = 7,

	.max_रेजिस्टर = SSM2602_RESET,
	.अस्थिर_reg = ssm2602_रेजिस्टर_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = ssm2602_reg,
	.num_reg_शेषs = ARRAY_SIZE(ssm2602_reg),
पूर्ण;
EXPORT_SYMBOL_GPL(ssm2602_regmap_config);

पूर्णांक ssm2602_probe(काष्ठा device *dev, क्रमागत ssm2602_type type,
	काष्ठा regmap *regmap)
अणु
	काष्ठा ssm2602_priv *ssm2602;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ssm2602 = devm_kzalloc(dev, माप(*ssm2602), GFP_KERNEL);
	अगर (ssm2602 == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(dev, ssm2602);
	ssm2602->type = type;
	ssm2602->regmap = regmap;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_ssm2602,
		&ssm2602_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ssm2602_probe);

MODULE_DESCRIPTION("ASoC SSM2602/SSM2603/SSM2604 driver");
MODULE_AUTHOR("Cliff Cai");
MODULE_LICENSE("GPL");
