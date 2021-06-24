<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Ingenic JZ4760 CODEC driver
//
// Copyright (C) 2021, Christophe Branchereau <cbranchereau@gmail.com>
// Copyright (C) 2021, Paul Cercueil <paul@crapouillou.net>

#समावेश <linux/bitfield.h>
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
#घोषणा	ICDC_RGADW_RGADDR_MASK		GENMASK(14, 8)
#घोषणा	ICDC_RGADW_RGDIN_MASK		GENMASK(7, 0)

/* ICDC पूर्णांकernal रेजिस्टर data output रेजिस्टर (RGDATA)*/
#घोषणा ICDC_RGDATA_IRQ			BIT(8)
#घोषणा ICDC_RGDATA_RGDOUT_MASK		GENMASK(7, 0)

/* Internal रेजिस्टर space, accessed through regmap */
क्रमागत अणु
	JZ4760_CODEC_REG_SR,
	JZ4760_CODEC_REG_AICR,
	JZ4760_CODEC_REG_CR1,
	JZ4760_CODEC_REG_CR2,
	JZ4760_CODEC_REG_CR3,
	JZ4760_CODEC_REG_CR4,
	JZ4760_CODEC_REG_CCR1,
	JZ4760_CODEC_REG_CCR2,
	JZ4760_CODEC_REG_PMR1,
	JZ4760_CODEC_REG_PMR2,
	JZ4760_CODEC_REG_ICR,
	JZ4760_CODEC_REG_IFR,
	JZ4760_CODEC_REG_GCR1,
	JZ4760_CODEC_REG_GCR2,
	JZ4760_CODEC_REG_GCR3,
	JZ4760_CODEC_REG_GCR4,
	JZ4760_CODEC_REG_GCR5,
	JZ4760_CODEC_REG_GCR6,
	JZ4760_CODEC_REG_GCR7,
	JZ4760_CODEC_REG_GCR8,
	JZ4760_CODEC_REG_GCR9,
	JZ4760_CODEC_REG_AGC1,
	JZ4760_CODEC_REG_AGC2,
	JZ4760_CODEC_REG_AGC3,
	JZ4760_CODEC_REG_AGC4,
	JZ4760_CODEC_REG_AGC5,
	JZ4760_CODEC_REG_MIX1,
	JZ4760_CODEC_REG_MIX2,
पूर्ण;

#घोषणा REG_AICR_DAC_ADWL_MASK		GENMASK(7, 6)
#घोषणा REG_AICR_DAC_SERIAL		BIT(3)
#घोषणा REG_AICR_DAC_I2S		BIT(1)

#घोषणा REG_AICR_ADC_ADWL_MASK		GENMASK(5, 4)

#घोषणा REG_AICR_ADC_SERIAL		BIT(2)
#घोषणा REG_AICR_ADC_I2S		BIT(0)

#घोषणा REG_CR1_HP_LOAD			BIT(7)
#घोषणा REG_CR1_HP_MUTE			BIT(5)
#घोषणा REG_CR1_LO_MUTE_OFFSET		4
#घोषणा REG_CR1_BTL_MUTE_OFFSET		3
#घोषणा REG_CR1_OUTSEL_OFFSET		0
#घोषणा REG_CR1_OUTSEL_MASK		GENMASK(1, REG_CR1_OUTSEL_OFFSET)

#घोषणा REG_CR2_DAC_MONO		BIT(7)
#घोषणा REG_CR2_DAC_MUTE		BIT(5)
#घोषणा REG_CR2_DAC_NOMAD		BIT(1)
#घोषणा REG_CR2_DAC_RIGHT_ONLY		BIT(0)

#घोषणा REG_CR3_ADC_INSEL_OFFSET	2
#घोषणा REG_CR3_ADC_INSEL_MASK		GENMASK(3, REG_CR3_ADC_INSEL_OFFSET)
#घोषणा REG_CR3_MICSTEREO_OFFSET	1
#घोषणा REG_CR3_MICDIFF_OFFSET		0

#घोषणा REG_CR4_ADC_HPF_OFFSET		7
#घोषणा REG_CR4_ADC_RIGHT_ONLY		BIT(0)

#घोषणा REG_CCR1_CRYSTAL_MASK		GENMASK(3, 0)

#घोषणा REG_CCR2_DAC_FREQ_MASK		GENMASK(7, 4)
#घोषणा REG_CCR2_ADC_FREQ_MASK		GENMASK(3, 0)

#घोषणा REG_PMR1_SB			BIT(7)
#घोषणा REG_PMR1_SB_SLEEP		BIT(6)
#घोषणा REG_PMR1_SB_AIP_OFFSET		5
#घोषणा REG_PMR1_SB_LINE_OFFSET		4
#घोषणा REG_PMR1_SB_MIC1_OFFSET		3
#घोषणा REG_PMR1_SB_MIC2_OFFSET		2
#घोषणा REG_PMR1_SB_BYPASS_OFFSET	1
#घोषणा REG_PMR1_SB_MICBIAS_OFFSET	0

#घोषणा REG_PMR2_SB_ADC_OFFSET		4
#घोषणा REG_PMR2_SB_HP_OFFSET		3
#घोषणा REG_PMR2_SB_BTL_OFFSET		2
#घोषणा REG_PMR2_SB_LOUT_OFFSET		1
#घोषणा REG_PMR2_SB_DAC_OFFSET		0

#घोषणा REG_ICR_INT_FORM_MASK		GENMASK(7, 6)
#घोषणा REG_ICR_ALL_MASK		GENMASK(5, 0)
#घोषणा REG_ICR_JACK_MASK		BIT(5)
#घोषणा REG_ICR_SCMC_MASK		BIT(4)
#घोषणा REG_ICR_RUP_MASK		BIT(3)
#घोषणा REG_ICR_RDO_MASK		BIT(2)
#घोषणा REG_ICR_GUP_MASK		BIT(1)
#घोषणा REG_ICR_GDO_MASK		BIT(0)

#घोषणा REG_IFR_ALL_MASK		GENMASK(5, 0)
#घोषणा REG_IFR_JACK			BIT(6)
#घोषणा REG_IFR_JACK_EVENT		BIT(5)
#घोषणा REG_IFR_SCMC			BIT(4)
#घोषणा REG_IFR_RUP			BIT(3)
#घोषणा REG_IFR_RDO			BIT(2)
#घोषणा REG_IFR_GUP			BIT(1)
#घोषणा REG_IFR_GDO			BIT(0)

#घोषणा REG_GCR_GAIN_OFFSET		0
#घोषणा REG_GCR_GAIN_MAX		0x1f

#घोषणा REG_GCR_RL			BIT(7)

#घोषणा REG_GCR_GIM1_MASK		GENMASK(5, 3)
#घोषणा REG_GCR_GIM2_MASK		GENMASK(2, 0)
#घोषणा REG_GCR_GIM_GAIN_MAX		7

#घोषणा REG_AGC1_EN			BIT(7)
#घोषणा REG_AGC1_TARGET_MASK		GENMASK(5, 2)

#घोषणा REG_AGC2_NG_THR_MASK		GENMASK(6, 4)
#घोषणा REG_AGC2_HOLD_MASK		GENMASK(3, 0)

#घोषणा REG_AGC3_ATK_MASK		GENMASK(7, 4)
#घोषणा REG_AGC3_DCY_MASK		GENMASK(3, 0)

#घोषणा REG_AGC4_AGC_MAX_MASK		GENMASK(4, 0)

#घोषणा REG_AGC5_AGC_MIN_MASK		GENMASK(4, 0)

#घोषणा REG_MIX1_MIX_REC_MASK		GENMASK(7, 6)
#घोषणा REG_MIX1_GIMIX_MASK		GENMASK(4, 0)

#घोषणा REG_MIX2_DAC_MIX_MASK		GENMASK(7, 6)
#घोषणा REG_MIX2_GOMIX_MASK		GENMASK(4, 0)

/* codec निजी data */
काष्ठा jz_codec अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक jz4760_codec_set_bias_level(काष्ठा snd_soc_component *codec,
				       क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	काष्ठा regmap *regmap = jz_codec->regmap;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		/* Reset all पूर्णांकerrupt flags. */
		regmap_ग_लिखो(regmap, JZ4760_CODEC_REG_IFR, REG_IFR_ALL_MASK);

		regmap_clear_bits(regmap, JZ4760_CODEC_REG_PMR1, REG_PMR1_SB);
		msleep(250);
		regmap_clear_bits(regmap, JZ4760_CODEC_REG_PMR1, REG_PMR1_SB_SLEEP);
		msleep(400);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_set_bits(regmap, JZ4760_CODEC_REG_PMR1, REG_PMR1_SB_SLEEP);
		regmap_set_bits(regmap, JZ4760_CODEC_REG_PMR1, REG_PMR1_SB);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jz4760_codec_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);
	पूर्णांक ret = 0;

	/*
	 * SYSCLK output from the codec to the AIC is required to keep the
	 * DMA transfer going during playback when all audible outमाला_दो have
	 * been disabled.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ret = snd_soc_dapm_क्रमce_enable_pin(dapm, "SYSCLK");
	वापस ret;
पूर्ण

अटल व्योम jz4760_codec_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dapm_disable_pin(dapm, "SYSCLK");
पूर्ण


अटल पूर्णांक jz4760_codec_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
			snd_soc_component_क्रमce_bias_level(codec, SND_SOC_BIAS_ON);
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

अटल पूर्णांक jz4760_codec_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *codec = dai->component;
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	अचिन्हित पूर्णांक gain_bit = mute ? REG_IFR_GDO : REG_IFR_GUP;
	अचिन्हित पूर्णांक val, reg;
	पूर्णांक change, err;

	change = snd_soc_component_update_bits(codec, JZ4760_CODEC_REG_CR2,
					       REG_CR2_DAC_MUTE,
					       mute ? REG_CR2_DAC_MUTE : 0);
	अगर (change == 1) अणु
		regmap_पढ़ो(jz_codec->regmap, JZ4760_CODEC_REG_PMR2, &val);

		अगर (val & BIT(REG_PMR2_SB_DAC_OFFSET))
			वापस 1;

		err = regmap_पढ़ो_poll_समयout(jz_codec->regmap,
					       JZ4760_CODEC_REG_IFR,
					       val, val & gain_bit,
					       1000, 1 * USEC_PER_SEC);
		अगर (err) अणु
			dev_err(jz_codec->dev,
				"Timeout while setting digital mute: %d", err);
			वापस err;
		पूर्ण

		/* clear GUP/GDO flag */
		regmap_ग_लिखो(jz_codec->regmap, JZ4760_CODEC_REG_IFR, gain_bit);
	पूर्ण

	regmap_पढ़ो(jz_codec->regmap, JZ4760_CODEC_REG_CR2, &reg);

	वापस 0;
पूर्ण

/* unit: 0.01dB */
अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(dac_tlv, -3100, 100);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(out_tlv, -2500, 100);
अटल स्थिर DECLARE_TLV_DB_SCALE(linein_tlv, -2500, 100, 0);

/* Unconditional controls. */
अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_snd_controls[] = अणु
	/* record gain control */
	SOC_DOUBLE_R_TLV("PCM Capture Volume",
			 JZ4760_CODEC_REG_GCR9, JZ4760_CODEC_REG_GCR8,
			 REG_GCR_GAIN_OFFSET, REG_GCR_GAIN_MAX, 0, adc_tlv),

	SOC_DOUBLE_R_TLV("Line In Bypass Playback Volume",
			 JZ4760_CODEC_REG_GCR4, JZ4760_CODEC_REG_GCR3,
			 REG_GCR_GAIN_OFFSET, REG_GCR_GAIN_MAX, 1, linein_tlv),

	SOC_SINGLE("High-Pass Filter Capture Switch",
		   JZ4760_CODEC_REG_CR4,
		   REG_CR4_ADC_HPF_OFFSET, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_pcm_playback_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Volume",
		.info = snd_soc_info_volsw,
		.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ
			| SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.tlv.p = dac_tlv,
		.get = snd_soc_dapm_get_volsw,
		.put = snd_soc_dapm_put_volsw,
		.निजी_value = SOC_DOUBLE_R_VALUE(JZ4760_CODEC_REG_GCR6,
						    JZ4760_CODEC_REG_GCR5,
						    REG_GCR_GAIN_OFFSET,
						    REG_GCR_GAIN_MAX, 1),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_hp_playback_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Volume",
		.info = snd_soc_info_volsw,
		.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ
			| SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.tlv.p = out_tlv,
		.get = snd_soc_dapm_get_volsw,
		.put = snd_soc_dapm_put_volsw,
		.निजी_value = SOC_DOUBLE_R_VALUE(JZ4760_CODEC_REG_GCR2,
						    JZ4760_CODEC_REG_GCR1,
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
		regmap_clear_bits(jz_codec->regmap, JZ4760_CODEC_REG_CR1,
				  REG_CR1_HP_MUTE);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		/* रुको क्रम ramp-up complete (RUP) */
		err = regmap_पढ़ो_poll_समयout(jz_codec->regmap,
					       JZ4760_CODEC_REG_IFR,
					       val, val & REG_IFR_RUP,
					       1000, 1 * USEC_PER_SEC);
		अगर (err) अणु
			dev_err(jz_codec->dev, "RUP timeout: %d", err);
			वापस err;
		पूर्ण

		/* clear RUP flag */
		regmap_set_bits(jz_codec->regmap, JZ4760_CODEC_REG_IFR,
				REG_IFR_RUP);

		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		/* mute HP */
		regmap_set_bits(jz_codec->regmap, JZ4760_CODEC_REG_CR1,
				REG_CR1_HP_MUTE);

		err = regmap_पढ़ो_poll_समयout(jz_codec->regmap,
					       JZ4760_CODEC_REG_IFR,
					       val, val & REG_IFR_RDO,
					       1000, 1 * USEC_PER_SEC);
		अगर (err) अणु
			dev_err(jz_codec->dev, "RDO timeout: %d", err);
			वापस err;
		पूर्ण

		/* clear RDO flag */
		regmap_set_bits(jz_codec->regmap, JZ4760_CODEC_REG_IFR,
				REG_IFR_RDO);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर jz4760_codec_hp_texts[] = अणु
	"PCM", "Line In", "Mic 1", "Mic 2"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक jz4760_codec_hp_values[] = अणु 3, 2, 0, 1 पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(jz4760_codec_hp_क्रमागत,
				  JZ4760_CODEC_REG_CR1,
				  REG_CR1_OUTSEL_OFFSET,
				  REG_CR1_OUTSEL_MASK >> REG_CR1_OUTSEL_OFFSET,
				  jz4760_codec_hp_texts,
				  jz4760_codec_hp_values);
अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_hp_source =
			SOC_DAPM_ENUM("Route", jz4760_codec_hp_क्रमागत);

अटल स्थिर अक्षर * स्थिर jz4760_codec_cap_texts[] = अणु
	"Line In", "Mic 1", "Mic 2"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक jz4760_codec_cap_values[] = अणु 2, 0, 1 पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(jz4760_codec_cap_क्रमागत,
				  JZ4760_CODEC_REG_CR3,
				  REG_CR3_ADC_INSEL_OFFSET,
				  REG_CR3_ADC_INSEL_MASK >> REG_CR3_ADC_INSEL_OFFSET,
				  jz4760_codec_cap_texts,
				  jz4760_codec_cap_values);
अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_cap_source =
			SOC_DAPM_ENUM("Route", jz4760_codec_cap_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_mic_controls[] = अणु
	SOC_DAPM_SINGLE("Stereo Capture Switch", JZ4760_CODEC_REG_CR3,
			REG_CR3_MICSTEREO_OFFSET, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_line_out_चयन =
	SOC_DAPM_SINGLE("Switch", JZ4760_CODEC_REG_CR1,
			REG_CR1_LO_MUTE_OFFSET, 0, 0);
अटल स्थिर काष्ठा snd_kcontrol_new jz4760_codec_btl_out_चयन =
	SOC_DAPM_SINGLE("Switch", JZ4760_CODEC_REG_CR1,
			REG_CR1_BTL_MUTE_OFFSET, 0, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget jz4760_codec_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_PGA_E("HP Out", JZ4760_CODEC_REG_PMR2,
			   REG_PMR2_SB_HP_OFFSET, 1, शून्य, 0, hpout_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SWITCH("Line Out", JZ4760_CODEC_REG_PMR2,
			    REG_PMR2_SB_LOUT_OFFSET, 1,
			    &jz4760_codec_line_out_चयन),

	SND_SOC_DAPM_SWITCH("BTL Out", JZ4760_CODEC_REG_PMR2,
			    REG_PMR2_SB_BTL_OFFSET, 1,
			    &jz4760_codec_btl_out_चयन),

	SND_SOC_DAPM_PGA("Line In", JZ4760_CODEC_REG_PMR1,
			 REG_PMR1_SB_LINE_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_MUX("Headphones Source", SND_SOC_NOPM, 0, 0,
			 &jz4760_codec_hp_source),

	SND_SOC_DAPM_MUX("Capture Source", SND_SOC_NOPM, 0, 0,
			 &jz4760_codec_cap_source),

	SND_SOC_DAPM_PGA("Mic 1", JZ4760_CODEC_REG_PMR1,
			 REG_PMR1_SB_MIC1_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Mic 2", JZ4760_CODEC_REG_PMR1,
			 REG_PMR1_SB_MIC2_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Mic Diff", JZ4760_CODEC_REG_CR3,
			 REG_CR3_MICDIFF_OFFSET, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Mic", SND_SOC_NOPM, 0, 0,
			   jz4760_codec_mic_controls,
			   ARRAY_SIZE(jz4760_codec_mic_controls)),

	SND_SOC_DAPM_PGA("Line In Bypass", JZ4760_CODEC_REG_PMR1,
			 REG_PMR1_SB_BYPASS_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_ADC("ADC", "Capture", JZ4760_CODEC_REG_PMR2,
			 REG_PMR2_SB_ADC_OFFSET, 1),

	SND_SOC_DAPM_DAC("DAC", "Playback", JZ4760_CODEC_REG_PMR2,
			 REG_PMR2_SB_DAC_OFFSET, 1),

	SND_SOC_DAPM_MIXER("PCM Playback", SND_SOC_NOPM, 0, 0,
			   jz4760_codec_pcm_playback_controls,
			   ARRAY_SIZE(jz4760_codec_pcm_playback_controls)),

	SND_SOC_DAPM_MIXER("Headphones Playback", SND_SOC_NOPM, 0, 0,
			   jz4760_codec_hp_playback_controls,
			   ARRAY_SIZE(jz4760_codec_hp_playback_controls)),

	SND_SOC_DAPM_SUPPLY("MICBIAS", JZ4760_CODEC_REG_PMR1,
			    REG_PMR1_SB_MICBIAS_OFFSET, 1, शून्य, 0),

	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),

	SND_SOC_DAPM_INPUT("LLINEIN"),
	SND_SOC_DAPM_INPUT("RLINEIN"),

	SND_SOC_DAPM_OUTPUT("LHPOUT"),
	SND_SOC_DAPM_OUTPUT("RHPOUT"),

	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),

	SND_SOC_DAPM_OUTPUT("BTLP"),
	SND_SOC_DAPM_OUTPUT("BTLN"),

	SND_SOC_DAPM_OUTPUT("SYSCLK"),
पूर्ण;

/* Unconditional routes. */
अटल स्थिर काष्ठा snd_soc_dapm_route jz4760_codec_dapm_routes[] = अणु
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

	अणु "Capture Source", "Line In", "Line In" पूर्ण,
	अणु "Capture Source", "Mic 1", "Mic 1" पूर्ण,
	अणु "Capture Source", "Mic 2", "Mic 2" पूर्ण,
	अणु "ADC", शून्य, "Capture Source" पूर्ण,

	अणु "Line In Bypass", शून्य, "Line In" पूर्ण,

	अणु "Headphones Source", "Mic 1", "Mic 1" पूर्ण,
	अणु "Headphones Source", "Mic 2", "Mic 2" पूर्ण,
	अणु "Headphones Source", "Line In", "Line In Bypass" पूर्ण,
	अणु "Headphones Source", "PCM", "Headphones Playback" पूर्ण,
	अणु "HP Out", शून्य, "Headphones Source" पूर्ण,

	अणु "LHPOUT", शून्य, "HP Out" पूर्ण,
	अणु "RHPOUT", शून्य, "HP Out" पूर्ण,
	अणु "Line Out", "Switch", "HP Out" पूर्ण,

	अणु "LOUT", शून्य, "Line Out" पूर्ण,
	अणु "ROUT", शून्य, "Line Out" पूर्ण,
	अणु "BTL Out", "Switch", "Line Out" पूर्ण,

	अणु "BTLP", शून्य, "BTL Out"पूर्ण,
	अणु "BTLN", शून्य, "BTL Out"पूर्ण,

	अणु "PCM Playback", "Volume", "DAC" पूर्ण,
	अणु "Headphones Playback", "Volume", "PCM Playback" पूर्ण,

	अणु "SYSCLK", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल व्योम jz4760_codec_codec_init_regs(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);
	काष्ठा regmap *regmap = jz_codec->regmap;

	/* Collect updates क्रम later sending. */
	regcache_cache_only(regmap, true);

	/* शेष Amp output to PCM */
	regmap_set_bits(regmap, JZ4760_CODEC_REG_CR1, REG_CR1_OUTSEL_MASK);

	/* Disable stereo mic */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_CR3,
			  BIT(REG_CR3_MICSTEREO_OFFSET));

	/* Set mic 1 as शेष source क्रम ADC */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_CR3,
			  REG_CR3_ADC_INSEL_MASK);

	/* ADC/DAC: serial + i2s */
	regmap_set_bits(regmap, JZ4760_CODEC_REG_AICR,
			REG_AICR_ADC_SERIAL | REG_AICR_ADC_I2S |
			REG_AICR_DAC_SERIAL | REG_AICR_DAC_I2S);

	/* The generated IRQ is a high level */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_ICR, REG_ICR_INT_FORM_MASK);
	regmap_update_bits(regmap, JZ4760_CODEC_REG_ICR, REG_ICR_ALL_MASK,
			   REG_ICR_JACK_MASK | REG_ICR_RUP_MASK |
			   REG_ICR_RDO_MASK  | REG_ICR_GUP_MASK |
			   REG_ICR_GDO_MASK);

	/* 12M oscillator */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_CCR1, REG_CCR1_CRYSTAL_MASK);

	/* 0: 16ohm/220uF, 1: 10kohm/1uF */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_CR1, REG_CR1_HP_LOAD);

	/* शेष to NOMAD */
	regmap_set_bits(jz_codec->regmap, JZ4760_CODEC_REG_CR2,
			REG_CR2_DAC_NOMAD);

	/* disable स्वतःmatic gain */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_AGC1, REG_AGC1_EN);

	/* Independent L/R DAC gain control */
	regmap_clear_bits(regmap, JZ4760_CODEC_REG_GCR5,
			  REG_GCR_RL);

	/* Send collected updates. */
	regcache_cache_only(regmap, false);
	regcache_sync(regmap);
पूर्ण

अटल पूर्णांक jz4760_codec_codec_probe(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);

	clk_prepare_enable(jz_codec->clk);

	jz4760_codec_codec_init_regs(codec);

	वापस 0;
पूर्ण

अटल व्योम jz4760_codec_codec_हटाओ(काष्ठा snd_soc_component *codec)
अणु
	काष्ठा jz_codec *jz_codec = snd_soc_component_get_drvdata(codec);

	clk_disable_unprepare(jz_codec->clk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver jz4760_codec_soc_codec_dev = अणु
	.probe			= jz4760_codec_codec_probe,
	.हटाओ			= jz4760_codec_codec_हटाओ,
	.set_bias_level		= jz4760_codec_set_bias_level,
	.controls		= jz4760_codec_snd_controls,
	.num_controls		= ARRAY_SIZE(jz4760_codec_snd_controls),
	.dapm_widमाला_लो		= jz4760_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(jz4760_codec_dapm_widमाला_लो),
	.dapm_routes		= jz4760_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(jz4760_codec_dapm_routes),
	.suspend_bias_off	= 1,
	.use_pmकरोwn_समय	= 1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक jz4760_codec_sample_rates[] = अणु
	96000, 48000, 44100, 32000,
	24000, 22050, 16000, 12000,
	11025, 9600, 8000,
पूर्ण;

अटल पूर्णांक jz4760_codec_hw_params(काष्ठा snd_pcm_substream *substream,
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

	क्रम (rate = 0; rate < ARRAY_SIZE(jz4760_codec_sample_rates); rate++) अणु
		अगर (jz4760_codec_sample_rates[rate] == params_rate(params))
			अवरोध;
	पूर्ण

	अगर (rate == ARRAY_SIZE(jz4760_codec_sample_rates))
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(codec->regmap, JZ4760_CODEC_REG_AICR,
				   REG_AICR_DAC_ADWL_MASK,
				   FIELD_PREP(REG_AICR_DAC_ADWL_MASK, bit_width));
		regmap_update_bits(codec->regmap, JZ4760_CODEC_REG_CCR2,
				   REG_CCR2_DAC_FREQ_MASK,
				   FIELD_PREP(REG_CCR2_DAC_FREQ_MASK, rate));
	पूर्ण अन्यथा अणु
		regmap_update_bits(codec->regmap, JZ4760_CODEC_REG_AICR,
				   REG_AICR_ADC_ADWL_MASK,
				   FIELD_PREP(REG_AICR_ADC_ADWL_MASK, bit_width));
		regmap_update_bits(codec->regmap, JZ4760_CODEC_REG_CCR2,
				   REG_CCR2_ADC_FREQ_MASK,
				   FIELD_PREP(REG_CCR2_ADC_FREQ_MASK, rate));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops jz4760_codec_dai_ops = अणु
	.startup	= jz4760_codec_startup,
	.shutकरोwn	= jz4760_codec_shutकरोwn,
	.hw_params	= jz4760_codec_hw_params,
	.trigger	= jz4760_codec_pcm_trigger,
	.mute_stream	= jz4760_codec_mute_stream,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा JZ_CODEC_FORMATS (SNDRV_PCM_FMTBIT_S16_LE  | \
			  SNDRV_PCM_FMTBIT_S18_3LE | \
			  SNDRV_PCM_FMTBIT_S20_3LE | \
			  SNDRV_PCM_FMTBIT_S24_3LE)

अटल काष्ठा snd_soc_dai_driver jz4760_codec_dai = अणु
	.name = "jz4760-hifi",
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
	.ops = &jz4760_codec_dai_ops,
पूर्ण;

अटल bool jz4760_codec_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == JZ4760_CODEC_REG_SR || reg == JZ4760_CODEC_REG_IFR;
पूर्ण

अटल bool jz4760_codec_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल JZ4760_CODEC_REG_SR:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक jz4760_codec_io_रुको(काष्ठा jz_codec *codec)
अणु
	u32 reg;

	वापस पढ़ोl_poll_समयout(codec->base + ICDC_RGADW_OFFSET, reg,
				  !(reg & ICDC_RGADW_RGWR),
				  1000, 1 * USEC_PER_SEC);
पूर्ण

अटल पूर्णांक jz4760_codec_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक *val)
अणु
	काष्ठा jz_codec *codec = context;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;
	पूर्णांक ret;

	ret = jz4760_codec_io_रुको(codec);
	अगर (ret)
		वापस ret;

	पंचांगp = पढ़ोl(codec->base + ICDC_RGADW_OFFSET);
	पंचांगp &= ~ICDC_RGADW_RGADDR_MASK;
	पंचांगp |= FIELD_PREP(ICDC_RGADW_RGADDR_MASK, reg);
	ग_लिखोl(पंचांगp, codec->base + ICDC_RGADW_OFFSET);

	/* रुको 6+ cycles */
	क्रम (i = 0; i < 6; i++)
		*val = पढ़ोl(codec->base + ICDC_RGDATA_OFFSET) &
			ICDC_RGDATA_RGDOUT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक jz4760_codec_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	काष्ठा jz_codec *codec = context;
	पूर्णांक ret;

	ret = jz4760_codec_io_रुको(codec);
	अगर (ret)
		वापस ret;

	ग_लिखोl(ICDC_RGADW_RGWR | FIELD_PREP(ICDC_RGADW_RGADDR_MASK, reg) | val,
	       codec->base + ICDC_RGADW_OFFSET);

	ret = jz4760_codec_io_रुको(codec);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर u8 jz4760_codec_reg_शेषs[] = अणु
	0x00, 0xFC, 0x1B, 0x20, 0x00, 0x80, 0x00, 0x00,
	0xFF, 0x1F, 0x3F, 0x00, 0x06, 0x06, 0x06, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x07, 0x44,
	0x1F, 0x00, 0x00, 0x00
पूर्ण;

अटल काष्ठा regmap_config jz4760_codec_regmap_config = अणु
	.reg_bits = 7,
	.val_bits = 8,

	.max_रेजिस्टर = JZ4760_CODEC_REG_MIX2,
	.अस्थिर_reg = jz4760_codec_अस्थिर,
	.ग_लिखोable_reg = jz4760_codec_ग_लिखोable,

	.reg_पढ़ो = jz4760_codec_reg_पढ़ो,
	.reg_ग_लिखो = jz4760_codec_reg_ग_लिखो,

	.reg_शेषs_raw = jz4760_codec_reg_शेषs,
	.num_reg_शेषs_raw = ARRAY_SIZE(jz4760_codec_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक jz4760_codec_probe(काष्ठा platक्रमm_device *pdev)
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
					&jz4760_codec_regmap_config);
	अगर (IS_ERR(codec->regmap))
		वापस PTR_ERR(codec->regmap);

	codec->clk = devm_clk_get(dev, "aic");
	अगर (IS_ERR(codec->clk))
		वापस PTR_ERR(codec->clk);

	platक्रमm_set_drvdata(pdev, codec);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &jz4760_codec_soc_codec_dev,
					      &jz4760_codec_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to register codec: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4760_codec_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4760-codec", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4760_codec_of_matches);

अटल काष्ठा platक्रमm_driver jz4760_codec_driver = अणु
	.probe			= jz4760_codec_probe,
	.driver			= अणु
		.name		= "jz4760-codec",
		.of_match_table = jz4760_codec_of_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4760_codec_driver);

MODULE_DESCRIPTION("JZ4760 SoC internal codec driver");
MODULE_AUTHOR("Christophe Branchereau <cbranchereau@gmail.com>");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_LICENSE("GPL v2");
