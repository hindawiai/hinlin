<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// JZ4725B CODEC driver
//
// Copyright (C) 2019, Paul Cercueil <paul@crapouillou.net>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>

#समावेश <linux/delay.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा ICDC_RGADW_OFFSET		0x00
#घोषणा ICDC_RGDATA_OFFSET		0x04

/* ICDC पूर्णांकernal रेजिस्टर access control रेजिस्टर(RGADW) */
#घोषणा ICDC_RGADW_RGWR			BIT(16)

#घोषणा ICDC_RGADW_RGADDR_OFFSET	8
#घोषणा	ICDC_RGADW_RGADDR_MASK		GENMASK(14, ICDC_RGADW_RGADDR_OFFSET)

#घोषणा ICDC_RGADW_RGDIN_OFFSET		0
#घोषणा	ICDC_RGADW_RGDIN_MASK		GENMASK(7, ICDC_RGADW_RGDIN_OFFSET)

/* ICDC पूर्णांकernal रेजिस्टर data output रेजिस्टर (RGDATA)*/
#घोषणा ICDC_RGDATA_IRQ			BIT(8)

#घोषणा ICDC_RGDATA_RGDOUT_OFFSET	0
#घोषणा ICDC_RGDATA_RGDOUT_MASK		GENMASK(7, ICDC_RGDATA_RGDOUT_OFFSET)

/* JZ पूर्णांकernal रेजिस्टर space */
क्रमागत अणु
	JZ4725B_CODEC_REG_AICR,
	JZ4725B_CODEC_REG_CR1,
	JZ4725B_CODEC_REG_CR2,
	JZ4725B_CODEC_REG_CCR1,
	JZ4725B_CODEC_REG_CCR2,
	JZ4725B_CODEC_REG_PMR1,
	JZ4725B_CODEC_REG_PMR2,
	JZ4725B_CODEC_REG_CRR,
	JZ4725B_CODEC_REG_ICR,
	JZ4725B_CODEC_REG_IFR,
	JZ4725B_CODEC_REG_CGR1,
	JZ4725B_CODEC_REG_CGR2,
	JZ4725B_CODEC_REG_CGR3,
	JZ4725B_CODEC_REG_CGR4,
	JZ4725B_CODEC_REG_CGR5,
	JZ4725B_CODEC_REG_CGR6,
	JZ4725B_CODEC_REG_CGR7,
	JZ4725B_CODEC_REG_CGR8,
	JZ4725B_CODEC_REG_CGR9,
	JZ4725B_CODEC_REG_CGR10,
	JZ4725B_CODEC_REG_TR1,
	JZ4725B_CODEC_REG_TR2,
	JZ4725B_CODEC_REG_CR3,
	JZ4725B_CODEC_REG_AGC1,
	JZ4725B_CODEC_REG_AGC2,
	JZ4725B_CODEC_REG_AGC3,
	JZ4725B_CODEC_REG_AGC4,
	JZ4725B_CODEC_REG_AGC5,
पूर्ण;

#घोषणा REG_AICR_CONFIG1_OFFSET		0
#घोषणा REG_AICR_CONFIG1_MASK		(0xf << REG_AICR_CONFIG1_OFFSET)

#घोषणा REG_CR1_SB_MICBIAS_OFFSET	7
#घोषणा REG_CR1_MONO_OFFSET		6
#घोषणा REG_CR1_DAC_MUTE_OFFSET		5
#घोषणा REG_CR1_HP_DIS_OFFSET		4
#घोषणा REG_CR1_DACSEL_OFFSET		3
#घोषणा REG_CR1_BYPASS_OFFSET		2

#घोषणा REG_CR2_DAC_DEEMP_OFFSET	7
#घोषणा REG_CR2_DAC_ADWL_OFFSET		5
#घोषणा REG_CR2_DAC_ADWL_MASK		(0x3 << REG_CR2_DAC_ADWL_OFFSET)
#घोषणा REG_CR2_ADC_ADWL_OFFSET		3
#घोषणा REG_CR2_ADC_ADWL_MASK		(0x3 << REG_CR2_ADC_ADWL_OFFSET)
#घोषणा REG_CR2_ADC_HPF_OFFSET		2

#घोषणा REG_CR3_SB_MIC1_OFFSET		7
#घोषणा REG_CR3_SB_MIC2_OFFSET		6
#घोषणा REG_CR3_SIDETONE1_OFFSET	5
#घोषणा REG_CR3_SIDETONE2_OFFSET	4
#घोषणा REG_CR3_MICDIFF_OFFSET		3
#घोषणा REG_CR3_MICSTEREO_OFFSET	2
#घोषणा REG_CR3_INSEL_OFFSET		0
#घोषणा REG_CR3_INSEL_MASK		(0x3 << REG_CR3_INSEL_OFFSET)

#घोषणा REG_CCR1_CONFIG4_OFFSET		0
#घोषणा REG_CCR1_CONFIG4_MASK		(0xf << REG_CCR1_CONFIG4_OFFSET)

#घोषणा REG_CCR2_DFREQ_OFFSET		4
#घोषणा REG_CCR2_DFREQ_MASK		(0xf << REG_CCR2_DFREQ_OFFSET)
#घोषणा REG_CCR2_AFREQ_OFFSET		0
#घोषणा REG_CCR2_AFREQ_MASK		(0xf << REG_CCR2_AFREQ_OFFSET)

#घोषणा REG_PMR1_SB_DAC_OFFSET		7
#घोषणा REG_PMR1_SB_OUT_OFFSET		6
#घोषणा REG_PMR1_SB_MIX_OFFSET		5
#घोषणा REG_PMR1_SB_ADC_OFFSET		4
#घोषणा REG_PMR1_SB_LIN_OFFSET		3
#घोषणा REG_PMR1_SB_IND_OFFSET		0

#घोषणा REG_PMR2_LRGI_OFFSET		7
#घोषणा REG_PMR2_RLGI_OFFSET		6
#घोषणा REG_PMR2_LRGOD_OFFSET		5
#घोषणा REG_PMR2_RLGOD_OFFSET		4
#घोषणा REG_PMR2_GIM_OFFSET		3
#घोषणा REG_PMR2_SB_MC_OFFSET		2
#घोषणा REG_PMR2_SB_OFFSET		1
#घोषणा REG_PMR2_SB_SLEEP_OFFSET	0

#घोषणा REG_IFR_RAMP_UP_DONE_OFFSET	3
#घोषणा REG_IFR_RAMP_DOWN_DONE_OFFSET	2

#घोषणा REG_CGR1_GODL_OFFSET		4
#घोषणा REG_CGR1_GODL_MASK		(0xf << REG_CGR1_GODL_OFFSET)
#घोषणा REG_CGR1_GODR_OFFSET		0
#घोषणा REG_CGR1_GODR_MASK		(0xf << REG_CGR1_GODR_OFFSET)

#घोषणा REG_CGR2_GO1R_OFFSET		0
#घोषणा REG_CGR2_GO1R_MASK		(0x1f << REG_CGR2_GO1R_OFFSET)

#घोषणा REG_CGR3_GO1L_OFFSET		0
#घोषणा REG_CGR3_GO1L_MASK		(0x1f << REG_CGR3_GO1L_OFFSET)

काष्ठा jz_icdc अणु
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_LINEAR(jz4725b_dac_tlv, -2250, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_LINEAR(jz4725b_line_tlv, -1500, 600);

अटल स्थिर काष्ठा snd_kcontrol_new jz4725b_codec_controls[] = अणु
	SOC_DOUBLE_TLV("Master Playback Volume",
		       JZ4725B_CODEC_REG_CGR1,
		       REG_CGR1_GODL_OFFSET,
		       REG_CGR1_GODR_OFFSET,
		       0xf, 1, jz4725b_dac_tlv),
	SOC_DOUBLE_R_TLV("Master Capture Volume",
			 JZ4725B_CODEC_REG_CGR3,
			 JZ4725B_CODEC_REG_CGR2,
			 REG_CGR2_GO1R_OFFSET,
			 0x1f, 1, jz4725b_line_tlv),

	SOC_SINGLE("Master Playback Switch", JZ4725B_CODEC_REG_CR1,
		   REG_CR1_DAC_MUTE_OFFSET, 1, 1),

	SOC_SINGLE("Deemphasize Filter Playback Switch",
		   JZ4725B_CODEC_REG_CR2,
		   REG_CR2_DAC_DEEMP_OFFSET, 1, 0),

	SOC_SINGLE("High-Pass Filter Capture Switch",
		   JZ4725B_CODEC_REG_CR2,
		   REG_CR2_ADC_HPF_OFFSET, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर jz4725b_codec_adc_src_texts[] = अणु
	"Mic 1", "Mic 2", "Line In", "Mixer",
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक jz4725b_codec_adc_src_values[] = अणु 0, 1, 2, 3, पूर्ण;
अटल SOC_VALUE_ENUM_SINGLE_DECL(jz4725b_codec_adc_src_क्रमागत,
				  JZ4725B_CODEC_REG_CR3,
				  REG_CR3_INSEL_OFFSET,
				  REG_CR3_INSEL_MASK,
				  jz4725b_codec_adc_src_texts,
				  jz4725b_codec_adc_src_values);
अटल स्थिर काष्ठा snd_kcontrol_new jz4725b_codec_adc_src_ctrl =
			SOC_DAPM_ENUM("Route", jz4725b_codec_adc_src_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new jz4725b_codec_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Line In Bypass", JZ4725B_CODEC_REG_CR1,
			REG_CR1_BYPASS_OFFSET, 1, 0),
पूर्ण;

अटल पूर्णांक jz4725b_out_stage_enable(काष्ठा snd_soc_dapm_widget *w,
				    काष्ठा snd_kcontrol *kcontrol,
				    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	काष्ठा jz_icdc *icdc = snd_soc_component_get_drvdata(codec);
	काष्ठा regmap *map = icdc->regmap;
	अचिन्हित पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस regmap_clear_bits(map, JZ4725B_CODEC_REG_IFR,
					 BIT(REG_IFR_RAMP_UP_DONE_OFFSET));
	हाल SND_SOC_DAPM_POST_PMU:
		वापस regmap_पढ़ो_poll_समयout(map, JZ4725B_CODEC_REG_IFR,
			       val, val & BIT(REG_IFR_RAMP_UP_DONE_OFFSET),
			       100000, 500000);
	हाल SND_SOC_DAPM_PRE_PMD:
		वापस regmap_clear_bits(map, JZ4725B_CODEC_REG_IFR,
				BIT(REG_IFR_RAMP_DOWN_DONE_OFFSET));
	हाल SND_SOC_DAPM_POST_PMD:
		वापस regmap_पढ़ो_poll_समयout(map, JZ4725B_CODEC_REG_IFR,
			       val, val & BIT(REG_IFR_RAMP_DOWN_DONE_OFFSET),
			       100000, 500000);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget jz4725b_codec_dapm_widमाला_लो[] = अणु
	/* DAC */
	SND_SOC_DAPM_DAC("DAC", "Playback",
			 JZ4725B_CODEC_REG_PMR1, REG_PMR1_SB_DAC_OFFSET, 1),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC", "Capture",
			 JZ4725B_CODEC_REG_PMR1, REG_PMR1_SB_ADC_OFFSET, 1),

	SND_SOC_DAPM_MUX("ADC Source", SND_SOC_NOPM, 0, 0,
			 &jz4725b_codec_adc_src_ctrl),

	/* Mixer */
	SND_SOC_DAPM_MIXER("Mixer", JZ4725B_CODEC_REG_PMR1,
			   REG_PMR1_SB_MIX_OFFSET, 1,
			   jz4725b_codec_mixer_controls,
			   ARRAY_SIZE(jz4725b_codec_mixer_controls)),
	SND_SOC_DAPM_MIXER("DAC to Mixer", JZ4725B_CODEC_REG_CR1,
			   REG_CR1_DACSEL_OFFSET, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Line In", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("HP Out", JZ4725B_CODEC_REG_CR1,
			   REG_CR1_HP_DIS_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_MIXER("Mic 1", JZ4725B_CODEC_REG_CR3,
			   REG_CR3_SB_MIC1_OFFSET, 1, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mic 2", JZ4725B_CODEC_REG_CR3,
			   REG_CR3_SB_MIC2_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_MIXER_E("Out Stage", JZ4725B_CODEC_REG_PMR1,
			     REG_PMR1_SB_OUT_OFFSET, 1, शून्य, 0,
			     jz4725b_out_stage_enable,
			     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			     SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXER("Mixer to ADC", JZ4725B_CODEC_REG_PMR1,
			   REG_PMR1_SB_IND_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", JZ4725B_CODEC_REG_CR1,
			    REG_CR1_SB_MICBIAS_OFFSET, 1, शून्य, 0),

	/* Pins */
	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),

	SND_SOC_DAPM_INPUT("LLINEIN"),
	SND_SOC_DAPM_INPUT("RLINEIN"),

	SND_SOC_DAPM_OUTPUT("LHPOUT"),
	SND_SOC_DAPM_OUTPUT("RHPOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route jz4725b_codec_dapm_routes[] = अणु
	अणु"Mic 1", शून्य, "MIC1P"पूर्ण,
	अणु"Mic 1", शून्य, "MIC1N"पूर्ण,
	अणु"Mic 2", शून्य, "MIC2P"पूर्ण,
	अणु"Mic 2", शून्य, "MIC2N"पूर्ण,

	अणु"Line In", शून्य, "LLINEIN"पूर्ण,
	अणु"Line In", शून्य, "RLINEIN"पूर्ण,

	अणु"Mixer", "Line In Bypass", "Line In"पूर्ण,
	अणु"DAC to Mixer", शून्य, "DAC"पूर्ण,
	अणु"Mixer", शून्य, "DAC to Mixer"पूर्ण,

	अणु"Mixer to ADC", शून्य, "Mixer"पूर्ण,
	अणु"ADC Source", "Mixer", "Mixer to ADC"पूर्ण,
	अणु"ADC Source", "Line In", "Line In"पूर्ण,
	अणु"ADC Source", "Mic 1", "Mic 1"पूर्ण,
	अणु"ADC Source", "Mic 2", "Mic 2"पूर्ण,
	अणु"ADC", शून्य, "ADC Source"पूर्ण,

	अणु"Out Stage", शून्य, "Mixer"पूर्ण,
	अणु"HP Out", शून्य, "Out Stage"पूर्ण,
	अणु"LHPOUT", शून्य, "HP Out"पूर्ण,
	अणु"RHPOUT", शून्य, "HP Out"पूर्ण,
पूर्ण;

अटल पूर्णांक jz4725b_codec_set_bias_level(काष्ठा snd_soc_component *component,
					क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा jz_icdc *icdc = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *map = icdc->regmap;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		regmap_clear_bits(map, JZ4725B_CODEC_REG_PMR2,
				  BIT(REG_PMR2_SB_SLEEP_OFFSET));
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Enable sound hardware */
		regmap_clear_bits(map, JZ4725B_CODEC_REG_PMR2,
				  BIT(REG_PMR2_SB_OFFSET));
		msleep(224);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_set_bits(map, JZ4725B_CODEC_REG_PMR2,
				BIT(REG_PMR2_SB_SLEEP_OFFSET));
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_set_bits(map, JZ4725B_CODEC_REG_PMR2,
				BIT(REG_PMR2_SB_OFFSET));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jz4725b_codec_dev_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा jz_icdc *icdc = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *map = icdc->regmap;

	clk_prepare_enable(icdc->clk);

	/* Write CONFIGn (n=1 to 8) bits.
	 * The value 0x0f is specअगरied in the datasheet as a requirement.
	 */
	regmap_ग_लिखो(map, JZ4725B_CODEC_REG_AICR,
		     0xf << REG_AICR_CONFIG1_OFFSET);
	regmap_ग_लिखो(map, JZ4725B_CODEC_REG_CCR1,
		     0x0 << REG_CCR1_CONFIG4_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम jz4725b_codec_dev_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा jz_icdc *icdc = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(icdc->clk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver jz4725b_codec = अणु
	.probe			= jz4725b_codec_dev_probe,
	.हटाओ			= jz4725b_codec_dev_हटाओ,
	.set_bias_level		= jz4725b_codec_set_bias_level,
	.controls		= jz4725b_codec_controls,
	.num_controls		= ARRAY_SIZE(jz4725b_codec_controls),
	.dapm_widमाला_लो		= jz4725b_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(jz4725b_codec_dapm_widमाला_लो),
	.dapm_routes		= jz4725b_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(jz4725b_codec_dapm_routes),
	.suspend_bias_off	= 1,
	.use_pmकरोwn_समय	= 1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक jz4725b_codec_sample_rates[] = अणु
	96000, 48000, 44100, 32000,
	24000, 22050, 16000, 12000,
	11025, 9600, 8000,
पूर्ण;

अटल पूर्णांक jz4725b_codec_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz_icdc *icdc = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक rate, bit_width;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		bit_width = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S18_3LE:
		bit_width = 1;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		bit_width = 2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		bit_width = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (rate = 0; rate < ARRAY_SIZE(jz4725b_codec_sample_rates); rate++) अणु
		अगर (jz4725b_codec_sample_rates[rate] == params_rate(params))
			अवरोध;
	पूर्ण

	अगर (rate == ARRAY_SIZE(jz4725b_codec_sample_rates))
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(icdc->regmap,
				   JZ4725B_CODEC_REG_CR2,
				   REG_CR2_DAC_ADWL_MASK,
				   bit_width << REG_CR2_DAC_ADWL_OFFSET);

		regmap_update_bits(icdc->regmap,
				   JZ4725B_CODEC_REG_CCR2,
				   REG_CCR2_DFREQ_MASK,
				   rate << REG_CCR2_DFREQ_OFFSET);
	पूर्ण अन्यथा अणु
		regmap_update_bits(icdc->regmap,
				   JZ4725B_CODEC_REG_CR2,
				   REG_CR2_ADC_ADWL_MASK,
				   bit_width << REG_CR2_ADC_ADWL_OFFSET);

		regmap_update_bits(icdc->regmap,
				   JZ4725B_CODEC_REG_CCR2,
				   REG_CCR2_AFREQ_MASK,
				   rate << REG_CCR2_AFREQ_OFFSET);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops jz4725b_codec_dai_ops = अणु
	.hw_params = jz4725b_codec_hw_params,
पूर्ण;

#घोषणा JZ_ICDC_FORMATS (SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S18_3LE | \
			 SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_3LE)

अटल काष्ठा snd_soc_dai_driver jz4725b_codec_dai = अणु
	.name = "jz4725b-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = JZ_ICDC_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = JZ_ICDC_FORMATS,
	पूर्ण,
	.ops = &jz4725b_codec_dai_ops,
पूर्ण;

अटल bool jz4725b_codec_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == JZ4725B_CODEC_REG_IFR;
पूर्ण

अटल bool jz4725b_codec_can_access_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg != JZ4725B_CODEC_REG_TR1) && (reg != JZ4725B_CODEC_REG_TR2);
पूर्ण

अटल पूर्णांक jz4725b_codec_io_रुको(काष्ठा jz_icdc *icdc)
अणु
	u32 reg;

	वापस पढ़ोl_poll_समयout(icdc->base + ICDC_RGADW_OFFSET, reg,
				  !(reg & ICDC_RGADW_RGWR), 1000, 10000);
पूर्ण

अटल पूर्णांक jz4725b_codec_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक *val)
अणु
	काष्ठा jz_icdc *icdc = context;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;
	पूर्णांक ret;

	ret = jz4725b_codec_io_रुको(icdc);
	अगर (ret)
		वापस ret;

	पंचांगp = पढ़ोl(icdc->base + ICDC_RGADW_OFFSET);
	पंचांगp = (पंचांगp & ~ICDC_RGADW_RGADDR_MASK)
	    | (reg << ICDC_RGADW_RGADDR_OFFSET);
	ग_लिखोl(पंचांगp, icdc->base + ICDC_RGADW_OFFSET);

	/* रुको 6+ cycles */
	क्रम (i = 0; i < 6; i++)
		*val = पढ़ोl(icdc->base + ICDC_RGDATA_OFFSET) &
			ICDC_RGDATA_RGDOUT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक jz4725b_codec_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित पूर्णांक val)
अणु
	काष्ठा jz_icdc *icdc = context;
	पूर्णांक ret;

	ret = jz4725b_codec_io_रुको(icdc);
	अगर (ret)
		वापस ret;

	ग_लिखोl(ICDC_RGADW_RGWR | (reg << ICDC_RGADW_RGADDR_OFFSET) | val,
			icdc->base + ICDC_RGADW_OFFSET);

	ret = jz4725b_codec_io_रुको(icdc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर u8 jz4725b_codec_reg_शेषs[] = अणु
	0x0c, 0xaa, 0x78, 0x00, 0x00, 0xff, 0x03, 0x51,
	0x3f, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0xc0, 0x34,
	0x07, 0x44, 0x1f, 0x00,
पूर्ण;

अटल स्थिर काष्ठा regmap_config jz4725b_codec_regmap_config = अणु
	.reg_bits = 7,
	.val_bits = 8,

	.max_रेजिस्टर = JZ4725B_CODEC_REG_AGC5,
	.अस्थिर_reg = jz4725b_codec_अस्थिर,
	.पढ़ोable_reg = jz4725b_codec_can_access_reg,
	.ग_लिखोable_reg = jz4725b_codec_can_access_reg,

	.reg_पढ़ो = jz4725b_codec_reg_पढ़ो,
	.reg_ग_लिखो = jz4725b_codec_reg_ग_लिखो,

	.reg_शेषs_raw = jz4725b_codec_reg_शेषs,
	.num_reg_शेषs_raw = ARRAY_SIZE(jz4725b_codec_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक jz4725b_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz_icdc *icdc;
	पूर्णांक ret;

	icdc = devm_kzalloc(dev, माप(*icdc), GFP_KERNEL);
	अगर (!icdc)
		वापस -ENOMEM;

	icdc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(icdc->base))
		वापस PTR_ERR(icdc->base);

	icdc->regmap = devm_regmap_init(dev, शून्य, icdc,
					&jz4725b_codec_regmap_config);
	अगर (IS_ERR(icdc->regmap))
		वापस PTR_ERR(icdc->regmap);

	icdc->clk = devm_clk_get(&pdev->dev, "aic");
	अगर (IS_ERR(icdc->clk))
		वापस PTR_ERR(icdc->clk);

	platक्रमm_set_drvdata(pdev, icdc);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &jz4725b_codec,
					      &jz4725b_codec_dai, 1);
	अगर (ret)
		dev_err(dev, "Failed to register codec\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4725b_codec_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4725b-codec", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4725b_codec_of_matches);

अटल काष्ठा platक्रमm_driver jz4725b_codec_driver = अणु
	.probe = jz4725b_codec_probe,
	.driver = अणु
		.name = "jz4725b-codec",
		.of_match_table = jz4725b_codec_of_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4725b_codec_driver);

MODULE_DESCRIPTION("JZ4725B SoC internal codec driver");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_LICENSE("GPL v2");
