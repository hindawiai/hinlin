<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Ingenic JZ4770 CODEC driver
//
// Copyright (C) 2012, Maarten ter Huurne <maarten@treewalker.org>
// Copyright (C) 2019, Paul Cercueil <paul@crapouillou.net>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/समय64.h>

#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-dapm.h>
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

/* Internal रेजिस्टर space, accessed through regmap */
क्रमागत अणु
	JZ4770_CODEC_REG_SR,
	JZ4770_CODEC_REG_AICR_DAC,
	JZ4770_CODEC_REG_AICR_ADC,
	JZ4770_CODEC_REG_CR_LO,
	JZ4770_CODEC_REG_CR_HP,

	JZ4770_CODEC_REG_MISSING_REG1,

	JZ4770_CODEC_REG_CR_DAC,
	JZ4770_CODEC_REG_CR_MIC,
	JZ4770_CODEC_REG_CR_LI,
	JZ4770_CODEC_REG_CR_ADC,
	JZ4770_CODEC_REG_CR_MIX,
	JZ4770_CODEC_REG_CR_VIC,
	JZ4770_CODEC_REG_CCR,
	JZ4770_CODEC_REG_FCR_DAC,
	JZ4770_CODEC_REG_FCR_ADC,
	JZ4770_CODEC_REG_ICR,
	JZ4770_CODEC_REG_IMR,
	JZ4770_CODEC_REG_IFR,
	JZ4770_CODEC_REG_GCR_HPL,
	JZ4770_CODEC_REG_GCR_HPR,
	JZ4770_CODEC_REG_GCR_LIBYL,
	JZ4770_CODEC_REG_GCR_LIBYR,
	JZ4770_CODEC_REG_GCR_DACL,
	JZ4770_CODEC_REG_GCR_DACR,
	JZ4770_CODEC_REG_GCR_MIC1,
	JZ4770_CODEC_REG_GCR_MIC2,
	JZ4770_CODEC_REG_GCR_ADCL,
	JZ4770_CODEC_REG_GCR_ADCR,

	JZ4770_CODEC_REG_MISSING_REG2,

	JZ4770_CODEC_REG_GCR_MIXADC,
	JZ4770_CODEC_REG_GCR_MIXDAC,
	JZ4770_CODEC_REG_AGC1,
	JZ4770_CODEC_REG_AGC2,
	JZ4770_CODEC_REG_AGC3,
	JZ4770_CODEC_REG_AGC4,
	JZ4770_CODEC_REG_AGC5,
पूर्ण;

#घोषणा REG_AICR_DAC_ADWL_OFFSET	6
#घोषणा REG_AICR_DAC_ADWL_MASK		(0x3 << REG_AICR_DAC_ADWL_OFFSET)
#घोषणा REG_AICR_DAC_SERIAL		BIT(1)
#घोषणा REG_AICR_DAC_I2S		BIT(0)

#घोषणा REG_AICR_ADC_ADWL_OFFSET	6
#घोषणा REG_AICR_ADC_ADWL_MASK		(0x3 << REG_AICR_ADC_ADWL_OFFSET)
#घोषणा REG_AICR_ADC_SERIAL		BIT(1)
#घोषणा REG_AICR_ADC_I2S		BIT(0)

#घोषणा REG_CR_LO_MUTE_OFFSET		7
#घोषणा REG_CR_LO_SB_OFFSET		4
#घोषणा REG_CR_LO_SEL_OFFSET		0
#घोषणा REG_CR_LO_SEL_MASK		(0x3 << REG_CR_LO_SEL_OFFSET)

#घोषणा REG_CR_HP_MUTE			BIT(7)
#घोषणा REG_CR_HP_LOAD			BIT(6)
#घोषणा REG_CR_HP_SB_OFFSET		4
#घोषणा REG_CR_HP_SB_HPCM_OFFSET	3
#घोषणा REG_CR_HP_SEL_OFFSET		0
#घोषणा REG_CR_HP_SEL_MASK		(0x3 << REG_CR_HP_SEL_OFFSET)

#घोषणा REG_CR_DAC_MUTE			BIT(7)
#घोषणा REG_CR_DAC_MONO			BIT(6)
#घोषणा REG_CR_DAC_LEFT_ONLY		BIT(5)
#घोषणा REG_CR_DAC_SB_OFFSET		4
#घोषणा REG_CR_DAC_LRSWAP		BIT(3)

#घोषणा REG_CR_MIC_STEREO_OFFSET	7
#घोषणा REG_CR_MIC_IDIFF_OFFSET		6
#घोषणा REG_CR_MIC_SB_MIC2_OFFSET	5
#घोषणा REG_CR_MIC_SB_MIC1_OFFSET	4
#घोषणा REG_CR_MIC_BIAS_V0_OFFSET	1
#घोषणा REG_CR_MIC_BIAS_SB_OFFSET	0

#घोषणा REG_CR_LI_LIBY_OFFSET		4
#घोषणा REG_CR_LI_SB_OFFSET		0

#घोषणा REG_CR_ADC_DMIC_SEL		BIT(7)
#घोषणा REG_CR_ADC_MONO			BIT(6)
#घोषणा REG_CR_ADC_LEFT_ONLY		BIT(5)
#घोषणा REG_CR_ADC_SB_OFFSET		4
#घोषणा REG_CR_ADC_LRSWAP		BIT(3)
#घोषणा REG_CR_ADC_IN_SEL_OFFSET	0
#घोषणा REG_CR_ADC_IN_SEL_MASK		(0x3 << REG_CR_ADC_IN_SEL_OFFSET)

#घोषणा REG_CR_VIC_SB_SLEEP		BIT(1)
#घोषणा REG_CR_VIC_SB			BIT(0)

#घोषणा REG_CCR_CRYSTAL_OFFSET		0
#घोषणा REG_CCR_CRYSTAL_MASK		(0xf << REG_CCR_CRYSTAL_OFFSET)

#घोषणा REG_FCR_DAC_FREQ_OFFSET		0
#घोषणा REG_FCR_DAC_FREQ_MASK		(0xf << REG_FCR_DAC_FREQ_OFFSET)

#घोषणा REG_FCR_ADC_FREQ_OFFSET		0
#घोषणा REG_FCR_ADC_FREQ_MASK		(0xf << REG_FCR_ADC_FREQ_OFFSET)

#घोषणा REG_ICR_INT_FORM_OFFSET		6
#घोषणा REG_ICR_INT_FORM_MASK		(0x3 << REG_ICR_INT_FORM_OFFSET)

#घोषणा REG_IMR_ALL_MASK		(0x7f)
#घोषणा REG_IMR_SCLR_MASK		BIT(6)
#घोषणा REG_IMR_JACK_MASK		BIT(5)
#घोषणा REG_IMR_SCMC_MASK		BIT(4)
#घोषणा REG_IMR_RUP_MASK		BIT(3)
#घोषणा REG_IMR_RDO_MASK		BIT(2)
#घोषणा REG_IMR_GUP_MASK		BIT(1)
#घोषणा REG_IMR_GDO_MASK		BIT(0)

#घोषणा REG_IFR_ALL_MASK		(0x7f)
#घोषणा REG_IFR_SCLR			BIT(6)
#घोषणा REG_IFR_JACK			BIT(5)
#घोषणा REG_IFR_SCMC			BIT(4)
#घोषणा REG_IFR_RUP			BIT(3)
#घोषणा REG_IFR_RDO			BIT(2)
#घोषणा REG_IFR_GUP			BIT(1)
#घोषणा REG_IFR_GDO			BIT(0)

#घोषणा REG_GCR_HPL_LRGO		BIT(7)

#घोषणा REG_GCR_DACL_RLGOD		BIT(7)

#घोषणा REG_GCR_GAIN_OFFSET		0
#घोषणा REG_GCR_GAIN_MAX		0x1f

#घोषणा REG_GCR_MIC_GAIN_OFFSET		0
#घोषणा REG_GCR_MIC_GAIN_MAX		5

#घोषणा REG_GCR_ADC_GAIN_OFFSET		0
#घोषणा REG_GCR_ADC_GAIN_MAX		23

#घोषणा REG_AGC1_EN			BIT(7)

/* codec निजी data */
काष्ठा jz_codec अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक jz4770_codec_set_bias_level(काष्ठा snd_soc_component *codec,
				       क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	काष्ठा regmap *regmap = jz_codec->regmap;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		/* Reset all पूर्णांकerrupt flags. */
		regmap_ग_लिखो(regmap, JZ4770_CODEC_REG_IFR, REG_IFR_ALL_MASK);

		regmap_clear_bits(regmap, JZ4770_CODEC_REG_CR_VIC,
				  REG_CR_VIC_SB);
		msleep(250);
		regmap_clear_bits(regmap, JZ4770_CODEC_REG_CR_VIC,
				  REG_CR_VIC_SB_SLEEP);
		msleep(400);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_set_bits(regmap, JZ4770_CODEC_REG_CR_VIC,
				REG_CR_VIC_SB_SLEEP);
		regmap_set_bits(regmap, JZ4770_CODEC_REG_CR_VIC,
				REG_CR_VIC_SB);
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jz4770_codec_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	/*
	 * SYSCLK output from the codec to the AIC is required to keep the
	 * DMA transfer going during playback when all audible outमाला_दो have
	 * been disabled.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dapm_क्रमce_enable_pin(dapm, "SYSCLK");

	वापस 0;
पूर्ण

अटल व्योम jz4770_codec_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dapm_disable_pin(dapm, "SYSCLK");
पूर्ण


अटल पूर्णांक jz4770_codec_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
			snd_soc_component_क्रमce_bias_level(codec,
							   SND_SOC_BIAS_ON);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* करो nothing */
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक jz4770_codec_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	अचिन्हित पूर्णांक gain_bit = mute ? REG_IFR_GDO : REG_IFR_GUP;
	अचिन्हित पूर्णांक val;
	पूर्णांक change, err;

	change = snd_soc_component_update_bits(codec, JZ4770_CODEC_REG_CR_DAC,
					       REG_CR_DAC_MUTE,
					       mute ? REG_CR_DAC_MUTE : 0);
	अगर (change == 1) अणु
		regmap_पढ़ो(jz_codec->regmap, JZ4770_CODEC_REG_CR_DAC, &val);

		अगर (val & BIT(REG_CR_DAC_SB_OFFSET))
			वापस 1;

		err = regmap_पढ़ो_poll_समयout(jz_codec->regmap,
					       JZ4770_CODEC_REG_IFR,
					       val, val & gain_bit,
					       1000, 1 * USEC_PER_SEC);
		अगर (err) अणु
			dev_err(jz_codec->dev,
				"Timeout while setting digital mute: %d", err);
			वापस err;
		पूर्ण

		/* clear GUP/GDO flag */
		regmap_set_bits(jz_codec->regmap, JZ4770_CODEC_REG_IFR,
				gain_bit);
	पूर्ण

	वापस 0;
पूर्ण

/* unit: 0.01dB */
अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(dac_tlv, -3100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(out_tlv, -2500, 600);
अटल स्थिर DECLARE_TLV_DB_SCALE(linein_tlv, -2500, 100, 0);

/* Unconditional controls. */
अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_snd_controls[] = अणु
	/* record gain control */
	SOC_DOUBLE_R_TLV("PCM Capture Volume",
			 JZ4770_CODEC_REG_GCR_ADCL, JZ4770_CODEC_REG_GCR_ADCR,
			 REG_GCR_ADC_GAIN_OFFSET, REG_GCR_ADC_GAIN_MAX,
			 0, adc_tlv),

	SOC_DOUBLE_R_TLV("Line In Bypass Playback Volume",
			 JZ4770_CODEC_REG_GCR_LIBYL, JZ4770_CODEC_REG_GCR_LIBYR,
			 REG_GCR_GAIN_OFFSET, REG_GCR_GAIN_MAX, 1, linein_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_pcm_playback_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Volume",
		.info = snd_soc_info_volsw,
		.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ
			| SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.tlv.p = dac_tlv,
		.get = snd_soc_dapm_get_volsw,
		.put = snd_soc_dapm_put_volsw,
		/*
		 * NOTE: DACR/DACL are inversed; the gain value written to DACR
		 * seems to affect the left channel, and the gain value written
		 * to DACL seems to affect the right channel.
		 */
		.निजी_value = SOC_DOUBLE_R_VALUE(JZ4770_CODEC_REG_GCR_DACR,
						    JZ4770_CODEC_REG_GCR_DACL,
						    REG_GCR_GAIN_OFFSET,
						    REG_GCR_GAIN_MAX, 1),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_hp_playback_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Volume",
		.info = snd_soc_info_volsw,
		.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ
			| SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.tlv.p = out_tlv,
		.get = snd_soc_dapm_get_volsw,
		.put = snd_soc_dapm_put_volsw,
		/* HPR/HPL inversed क्रम the same reason as above */
		.निजी_value = SOC_DOUBLE_R_VALUE(JZ4770_CODEC_REG_GCR_HPR,
						    JZ4770_CODEC_REG_GCR_HPL,
						    REG_GCR_GAIN_OFFSET,
						    REG_GCR_GAIN_MAX, 1),
	पूर्ण,
पूर्ण;

अटल पूर्णांक hpout_event(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* unmute HP */
		regmap_clear_bits(jz_codec->regmap, JZ4770_CODEC_REG_CR_HP,
				  REG_CR_HP_MUTE);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		/* रुको क्रम ramp-up complete (RUP) */
		err = regmap_पढ़ो_poll_समयout(jz_codec->regmap,
					       JZ4770_CODEC_REG_IFR,
					       val, val & REG_IFR_RUP,
					       1000, 1 * USEC_PER_SEC);
		अगर (err) अणु
			dev_err(jz_codec->dev, "RUP timeout: %d", err);
			वापस err;
		पूर्ण

		/* clear RUP flag */
		regmap_set_bits(jz_codec->regmap, JZ4770_CODEC_REG_IFR,
				REG_IFR_RUP);

		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		/* mute HP */
		regmap_set_bits(jz_codec->regmap, JZ4770_CODEC_REG_CR_HP,
				REG_CR_HP_MUTE);

		err = regmap_पढ़ो_poll_समयout(jz_codec->regmap,
					       JZ4770_CODEC_REG_IFR,
					       val, val & REG_IFR_RDO,
					       1000, 1 * USEC_PER_SEC);
		अगर (err) अणु
			dev_err(jz_codec->dev, "RDO timeout: %d", err);
			वापस err;
		पूर्ण

		/* clear RDO flag */
		regmap_set_bits(jz_codec->regmap, JZ4770_CODEC_REG_IFR,
				REG_IFR_RDO);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adc_घातeron_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (event == SND_SOC_DAPM_POST_PMU)
		msleep(1000);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर jz4770_codec_hp_texts[] = अणु
	"PCM", "Line In", "Mic 1", "Mic 2"
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक jz4770_codec_hp_values[] = अणु 3, 2, 0, 1 पूर्ण;
अटल SOC_VALUE_ENUM_SINGLE_DECL(jz4770_codec_hp_क्रमागत,
				  JZ4770_CODEC_REG_CR_HP,
				  REG_CR_HP_SEL_OFFSET,
				  REG_CR_HP_SEL_MASK,
				  jz4770_codec_hp_texts,
				  jz4770_codec_hp_values);
अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_hp_source =
			SOC_DAPM_ENUM("Route", jz4770_codec_hp_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(jz4770_codec_lo_क्रमागत,
				  JZ4770_CODEC_REG_CR_LO,
				  REG_CR_LO_SEL_OFFSET,
				  REG_CR_LO_SEL_MASK,
				  jz4770_codec_hp_texts,
				  jz4770_codec_hp_values);
अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_lo_source =
			SOC_DAPM_ENUM("Route", jz4770_codec_lo_क्रमागत);

अटल स्थिर अक्षर * स्थिर jz4770_codec_cap_texts[] = अणु
	"Line In", "Mic 1", "Mic 2"
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक jz4770_codec_cap_values[] = अणु 2, 0, 1 पूर्ण;
अटल SOC_VALUE_ENUM_SINGLE_DECL(jz4770_codec_cap_क्रमागत,
				  JZ4770_CODEC_REG_CR_ADC,
				  REG_CR_ADC_IN_SEL_OFFSET,
				  REG_CR_ADC_IN_SEL_MASK,
				  jz4770_codec_cap_texts,
				  jz4770_codec_cap_values);
अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_cap_source =
			SOC_DAPM_ENUM("Route", jz4770_codec_cap_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new jz4770_codec_mic_controls[] = अणु
	SOC_DAPM_SINGLE("Stereo Capture Switch", JZ4770_CODEC_REG_CR_MIC,
			REG_CR_MIC_STEREO_OFFSET, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget jz4770_codec_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_PGA_E("HP Out", JZ4770_CODEC_REG_CR_HP,
			   REG_CR_HP_SB_OFFSET, 1, शून्य, 0, hpout_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA("Line Out", JZ4770_CODEC_REG_CR_LO,
			 REG_CR_LO_SB_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Line Out Switch 2", JZ4770_CODEC_REG_CR_LO,
			 REG_CR_LO_MUTE_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Line In", JZ4770_CODEC_REG_CR_LI,
			 REG_CR_LI_SB_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_MUX("Headphones Source", SND_SOC_NOPM, 0, 0,
			 &jz4770_codec_hp_source),
	SND_SOC_DAPM_MUX("Capture Source", SND_SOC_NOPM, 0, 0,
			 &jz4770_codec_cap_source),
	SND_SOC_DAPM_MUX("Line Out Source", SND_SOC_NOPM, 0, 0,
			 &jz4770_codec_lo_source),

	SND_SOC_DAPM_PGA("Mic 1", JZ4770_CODEC_REG_CR_MIC,
			 REG_CR_MIC_SB_MIC1_OFFSET, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic 2", JZ4770_CODEC_REG_CR_MIC,
			 REG_CR_MIC_SB_MIC2_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Mic Diff", JZ4770_CODEC_REG_CR_MIC,
			 REG_CR_MIC_IDIFF_OFFSET, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Mic", SND_SOC_NOPM, 0, 0,
			   jz4770_codec_mic_controls,
			   ARRAY_SIZE(jz4770_codec_mic_controls)),

	SND_SOC_DAPM_PGA("Line In Bypass", JZ4770_CODEC_REG_CR_LI,
			 REG_CR_LI_LIBY_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_ADC_E("ADC", "HiFi Capture", JZ4770_CODEC_REG_CR_ADC,
			   REG_CR_ADC_SB_OFFSET, 1, adc_घातeron_event,
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_DAC("DAC", "HiFi Playback", JZ4770_CODEC_REG_CR_DAC,
			 REG_CR_DAC_SB_OFFSET, 1),

	SND_SOC_DAPM_MIXER("PCM Playback", SND_SOC_NOPM, 0, 0,
			   jz4770_codec_pcm_playback_controls,
			   ARRAY_SIZE(jz4770_codec_pcm_playback_controls)),
	SND_SOC_DAPM_MIXER("Headphones Playback", SND_SOC_NOPM, 0, 0,
			   jz4770_codec_hp_playback_controls,
			   ARRAY_SIZE(jz4770_codec_hp_playback_controls)),

	SND_SOC_DAPM_SUPPLY("MICBIAS", JZ4770_CODEC_REG_CR_MIC,
			    REG_CR_MIC_BIAS_SB_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Cap-less", JZ4770_CODEC_REG_CR_HP,
			    REG_CR_HP_SB_HPCM_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),

	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),

	SND_SOC_DAPM_OUTPUT("LHPOUT"),
	SND_SOC_DAPM_OUTPUT("RHPOUT"),

	SND_SOC_DAPM_INPUT("LLINEIN"),
	SND_SOC_DAPM_INPUT("RLINEIN"),

	SND_SOC_DAPM_OUTPUT("SYSCLK"),
पूर्ण;

/* Unconditional routes. */
अटल स्थिर काष्ठा snd_soc_dapm_route jz4770_codec_dapm_routes[] = अणु
	अणु "Mic 1", शून्य, "MIC1P" पूर्ण,
	अणु "Mic Diff", शून्य, "MIC1N" पूर्ण,
	अणु "Mic 1", शून्य, "Mic Diff" पूर्ण,
	अणु "Mic 2", शून्य, "MIC2P" पूर्ण,
	अणु "Mic Diff", शून्य, "MIC2N" पूर्ण,
	अणु "Mic 2", शून्य, "Mic Diff" पूर्ण,

	अणु "Line In", शून्य, "LLINEIN" पूर्ण,
	अणु "Line In", शून्य, "RLINEIN" पूर्ण,

	अणु "Mic", "Stereo Capture Switch", "Mic 1" पूर्ण,
	अणु "Mic", "Stereo Capture Switch", "Mic 2" पूर्ण,
	अणु "Headphones Source", "Mic 1", "Mic" पूर्ण,
	अणु "Headphones Source", "Mic 2", "Mic" पूर्ण,
	अणु "Capture Source", "Mic 1", "Mic" पूर्ण,
	अणु "Capture Source", "Mic 2", "Mic" पूर्ण,

	अणु "Headphones Source", "Mic 1", "Mic 1" पूर्ण,
	अणु "Headphones Source", "Mic 2", "Mic 2" पूर्ण,
	अणु "Headphones Source", "Line In", "Line In Bypass" पूर्ण,
	अणु "Headphones Source", "PCM", "Headphones Playback" पूर्ण,
	अणु "HP Out", शून्य, "Headphones Source" पूर्ण,

	अणु "Capture Source", "Line In", "Line In" पूर्ण,
	अणु "Capture Source", "Mic 1", "Mic 1" पूर्ण,
	अणु "Capture Source", "Mic 2", "Mic 2" पूर्ण,
	अणु "ADC", शून्य, "Capture Source" पूर्ण,

	अणु "Line In Bypass", शून्य, "Line In" पूर्ण,
	अणु "Line Out Source", "Line In", "Line In Bypass" पूर्ण,
	अणु "Line Out Source", "PCM", "PCM Playback" पूर्ण,

	अणु "LHPOUT", शून्य, "HP Out"पूर्ण,
	अणु "RHPOUT", शून्य, "HP Out"पूर्ण,

	अणु "Line Out", शून्य, "Line Out Source" पूर्ण,
	अणु "Line Out Switch 2", शून्य, "Line Out" पूर्ण,

	अणु "LOUT", शून्य, "Line Out Switch 2"पूर्ण,
	अणु "ROUT", शून्य, "Line Out Switch 2"पूर्ण,

	अणु "PCM Playback", "Volume", "DAC" पूर्ण,
	अणु "Headphones Playback", "Volume", "PCM Playback" पूर्ण,

	अणु "SYSCLK", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल व्योम jz4770_codec_codec_init_regs(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	काष्ठा regmap *regmap = jz_codec->regmap;

	/* Collect updates क्रम later sending. */
	regcache_cache_only(regmap, true);

	/* शेष HP output to PCM */
	regmap_set_bits(regmap, JZ4770_CODEC_REG_CR_HP, REG_CR_HP_SEL_MASK);

	/* शेष line output to PCM */
	regmap_set_bits(regmap, JZ4770_CODEC_REG_CR_LO, REG_CR_LO_SEL_MASK);

	/* Disable stereo mic */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_CR_MIC,
			  BIT(REG_CR_MIC_STEREO_OFFSET));

	/* Set mic 1 as शेष source क्रम ADC */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_CR_ADC,
			  REG_CR_ADC_IN_SEL_MASK);

	/* ADC/DAC: serial + i2s */
	regmap_set_bits(regmap, JZ4770_CODEC_REG_AICR_ADC,
			REG_AICR_ADC_SERIAL | REG_AICR_ADC_I2S);
	regmap_set_bits(regmap, JZ4770_CODEC_REG_AICR_DAC,
			REG_AICR_DAC_SERIAL | REG_AICR_DAC_I2S);

	/* The generated IRQ is a high level */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_ICR, REG_ICR_INT_FORM_MASK);
	regmap_update_bits(regmap, JZ4770_CODEC_REG_IMR, REG_IMR_ALL_MASK,
			   REG_IMR_JACK_MASK | REG_IMR_RUP_MASK |
			   REG_IMR_RDO_MASK | REG_IMR_GUP_MASK |
			   REG_IMR_GDO_MASK);

	/* 12M oscillator */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_CCR, REG_CCR_CRYSTAL_MASK);

	/* 0: 16ohm/220uF, 1: 10kohm/1uF */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_CR_HP, REG_CR_HP_LOAD);

	/* disable स्वतःmatic gain */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_AGC1, REG_AGC1_EN);

	/* Disable DAC lrswap */
	regmap_set_bits(regmap, JZ4770_CODEC_REG_CR_DAC, REG_CR_DAC_LRSWAP);

	/* Independent L/R DAC gain control */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_GCR_DACL,
			  REG_GCR_DACL_RLGOD);

	/* Disable ADC lrswap */
	regmap_set_bits(regmap, JZ4770_CODEC_REG_CR_ADC, REG_CR_ADC_LRSWAP);

	/* शेष to cap-less mode(0) */
	regmap_clear_bits(regmap, JZ4770_CODEC_REG_CR_HP,
			  BIT(REG_CR_HP_SB_HPCM_OFFSET));

	/* Send collected updates. */
	regcache_cache_only(regmap, false);
	regcache_sync(regmap);
पूर्ण

अटल पूर्णांक jz4770_codec_codec_probe(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);

	clk_prepare_enable(jz_codec->clk);

	jz4770_codec_codec_init_regs(codec);

	वापस 0;
पूर्ण

अटल व्योम jz4770_codec_codec_हटाओ(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);

	clk_disable_unprepare(jz_codec->clk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver jz4770_codec_soc_codec_dev = अणु
	.probe			= jz4770_codec_codec_probe,
	.हटाओ			= jz4770_codec_codec_हटाओ,
	.set_bias_level		= jz4770_codec_set_bias_level,
	.controls		= jz4770_codec_snd_controls,
	.num_controls		= ARRAY_SIZE(jz4770_codec_snd_controls),
	.dapm_widमाला_लो		= jz4770_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(jz4770_codec_dapm_widमाला_लो),
	.dapm_routes		= jz4770_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(jz4770_codec_dapm_routes),
	.suspend_bias_off	= 1,
	.use_pmकरोwn_समय	= 1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक jz4770_codec_sample_rates[] = अणु
	96000, 48000, 44100, 32000,
	24000, 22050, 16000, 12000,
	11025, 9600, 8000,
पूर्ण;

अटल पूर्णांक jz4770_codec_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz_codec *codec = snd_soc_component_get_drvdata(dai->component);
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

	क्रम (rate = 0; rate < ARRAY_SIZE(jz4770_codec_sample_rates); rate++) अणु
		अगर (jz4770_codec_sample_rates[rate] == params_rate(params))
			अवरोध;
	पूर्ण

	अगर (rate == ARRAY_SIZE(jz4770_codec_sample_rates))
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(codec->regmap, JZ4770_CODEC_REG_AICR_DAC,
				   REG_AICR_DAC_ADWL_MASK,
				   bit_width << REG_AICR_DAC_ADWL_OFFSET);
		regmap_update_bits(codec->regmap, JZ4770_CODEC_REG_FCR_DAC,
				   REG_FCR_DAC_FREQ_MASK,
				   rate << REG_FCR_DAC_FREQ_OFFSET);
	पूर्ण अन्यथा अणु
		regmap_update_bits(codec->regmap, JZ4770_CODEC_REG_AICR_ADC,
				   REG_AICR_ADC_ADWL_MASK,
				   bit_width << REG_AICR_ADC_ADWL_OFFSET);
		regmap_update_bits(codec->regmap, JZ4770_CODEC_REG_FCR_ADC,
				   REG_FCR_ADC_FREQ_MASK,
				   rate << REG_FCR_ADC_FREQ_OFFSET);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops jz4770_codec_dai_ops = अणु
	.startup	= jz4770_codec_startup,
	.shutकरोwn	= jz4770_codec_shutकरोwn,
	.hw_params	= jz4770_codec_hw_params,
	.trigger	= jz4770_codec_pcm_trigger,
	.mute_stream	= jz4770_codec_mute_stream,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा JZ_CODEC_FORMATS (SNDRV_PCM_FMTBIT_S16_LE  | \
			  SNDRV_PCM_FMTBIT_S18_3LE | \
			  SNDRV_PCM_FMTBIT_S20_3LE | \
			  SNDRV_PCM_FMTBIT_S24_3LE)

अटल काष्ठा snd_soc_dai_driver jz4770_codec_dai = अणु
	.name = "jz4770-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = JZ_CODEC_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = JZ_CODEC_FORMATS,
	पूर्ण,
	.ops = &jz4770_codec_dai_ops,
पूर्ण;

अटल bool jz4770_codec_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == JZ4770_CODEC_REG_SR || reg == JZ4770_CODEC_REG_IFR;
पूर्ण

अटल bool jz4770_codec_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल JZ4770_CODEC_REG_MISSING_REG1:
	हाल JZ4770_CODEC_REG_MISSING_REG2:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool jz4770_codec_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल JZ4770_CODEC_REG_SR:
	हाल JZ4770_CODEC_REG_MISSING_REG1:
	हाल JZ4770_CODEC_REG_MISSING_REG2:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक jz4770_codec_io_रुको(काष्ठा jz_codec *codec)
अणु
	u32 reg;

	वापस पढ़ोl_poll_समयout(codec->base + ICDC_RGADW_OFFSET, reg,
				  !(reg & ICDC_RGADW_RGWR),
				  1000, 1 * USEC_PER_SEC);
पूर्ण

अटल पूर्णांक jz4770_codec_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक *val)
अणु
	काष्ठा jz_codec *codec = context;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;
	पूर्णांक ret;

	ret = jz4770_codec_io_रुको(codec);
	अगर (ret)
		वापस ret;

	पंचांगp = पढ़ोl(codec->base + ICDC_RGADW_OFFSET);
	पंचांगp = (पंचांगp & ~ICDC_RGADW_RGADDR_MASK)
	    | (reg << ICDC_RGADW_RGADDR_OFFSET);
	ग_लिखोl(पंचांगp, codec->base + ICDC_RGADW_OFFSET);

	/* रुको 6+ cycles */
	क्रम (i = 0; i < 6; i++)
		*val = पढ़ोl(codec->base + ICDC_RGDATA_OFFSET) &
			ICDC_RGDATA_RGDOUT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक jz4770_codec_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	काष्ठा jz_codec *codec = context;
	पूर्णांक ret;

	ret = jz4770_codec_io_रुको(codec);
	अगर (ret)
		वापस ret;

	ग_लिखोl(ICDC_RGADW_RGWR | (reg << ICDC_RGADW_RGADDR_OFFSET) | val,
	       codec->base + ICDC_RGADW_OFFSET);

	ret = jz4770_codec_io_रुको(codec);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर u8 jz4770_codec_reg_शेषs[] = अणु
	0x00, 0xC3, 0xC3, 0x90, 0x98, 0xFF, 0x90, 0xB1,
	0x11, 0x10, 0x00, 0x03, 0x00, 0x00, 0x40, 0x00,
	0xFF, 0x00, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x34,
	0x07, 0x44, 0x1F, 0x00
पूर्ण;

अटल काष्ठा regmap_config jz4770_codec_regmap_config = अणु
	.reg_bits = 7,
	.val_bits = 8,

	.max_रेजिस्टर = JZ4770_CODEC_REG_AGC5,
	.अस्थिर_reg = jz4770_codec_अस्थिर,
	.पढ़ोable_reg = jz4770_codec_पढ़ोable,
	.ग_लिखोable_reg = jz4770_codec_ग_लिखोable,

	.reg_पढ़ो = jz4770_codec_reg_पढ़ो,
	.reg_ग_लिखो = jz4770_codec_reg_ग_लिखो,

	.reg_शेषs_raw = jz4770_codec_reg_शेषs,
	.num_reg_शेषs_raw = ARRAY_SIZE(jz4770_codec_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक jz4770_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz_codec *codec;
	पूर्णांक ret;

	codec = devm_kzalloc(dev, माप(*codec), GFP_KERNEL);
	अगर (!codec)
		वापस -ENOMEM;

	codec->dev = dev;

	codec->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(codec->base))
		वापस PTR_ERR(codec->base);

	codec->regmap = devm_regmap_init(dev, शून्य, codec,
					&jz4770_codec_regmap_config);
	अगर (IS_ERR(codec->regmap))
		वापस PTR_ERR(codec->regmap);

	codec->clk = devm_clk_get(dev, "aic");
	अगर (IS_ERR(codec->clk))
		वापस PTR_ERR(codec->clk);

	platक्रमm_set_drvdata(pdev, codec);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &jz4770_codec_soc_codec_dev,
					      &jz4770_codec_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to register codec: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4770_codec_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4770-codec", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4770_codec_of_matches);

अटल काष्ठा platक्रमm_driver jz4770_codec_driver = अणु
	.probe			= jz4770_codec_probe,
	.driver			= अणु
		.name		= "jz4770-codec",
		.of_match_table = jz4770_codec_of_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4770_codec_driver);

MODULE_DESCRIPTION("JZ4770 SoC internal codec driver");
MODULE_AUTHOR("Maarten ter Huurne <maarten@treewalker.org>");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_LICENSE("GPL v2");
