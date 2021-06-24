<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम the MAX9860 Mono Audio Voice Codec
//
// https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX9860.pdf
//
// The driver करोes not support sidetone since the DVST रेजिस्टर field is
// backwards with the mute near the maximum level instead of the minimum.
//
// Author: Peter Rosin <peda@axentia.s>
//         Copyright 2016 Axentia Technologies

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#समावेश "max9860.h"

काष्ठा max9860_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator *dvddio;
	काष्ठा notअगरier_block dvddio_nb;
	u8 psclk;
	अचिन्हित दीर्घ pclk_rate;
	पूर्णांक fmt;
पूर्ण;

अटल पूर्णांक max9860_dvddio_event(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा max9860_priv *max9860 = container_of(nb, काष्ठा max9860_priv,
						    dvddio_nb);
	अगर (event & REGULATOR_EVENT_DISABLE) अणु
		regcache_mark_dirty(max9860->regmap);
		regcache_cache_only(max9860->regmap, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_शेष max9860_reg_शेषs[] = अणु
	अणु MAX9860_PWRMAN,       0x00 पूर्ण,
	अणु MAX9860_INTEN,        0x00 पूर्ण,
	अणु MAX9860_SYSCLK,       0x00 पूर्ण,
	अणु MAX9860_AUDIOCLKHIGH, 0x00 पूर्ण,
	अणु MAX9860_AUDIOCLKLOW,  0x00 पूर्ण,
	अणु MAX9860_IFC1A,        0x00 पूर्ण,
	अणु MAX9860_IFC1B,        0x00 पूर्ण,
	अणु MAX9860_VOICEFLTR,    0x00 पूर्ण,
	अणु MAX9860_DACATTN,      0x00 पूर्ण,
	अणु MAX9860_ADCLEVEL,     0x00 पूर्ण,
	अणु MAX9860_DACGAIN,      0x00 पूर्ण,
	अणु MAX9860_MICGAIN,      0x00 पूर्ण,
	अणु MAX9860_MICADC,       0x00 पूर्ण,
	अणु MAX9860_NOISEGATE,    0x00 पूर्ण,
पूर्ण;

अटल bool max9860_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX9860_INTRSTATUS ... MAX9860_MICGAIN:
	हाल MAX9860_MICADC ... MAX9860_PWRMAN:
	हाल MAX9860_REVISION:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool max9860_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX9860_INTEN ... MAX9860_MICGAIN:
	हाल MAX9860_MICADC ... MAX9860_PWRMAN:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool max9860_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX9860_INTRSTATUS:
	हाल MAX9860_MICREADBACK:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool max9860_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX9860_INTRSTATUS:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config max9860_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ोable_reg = max9860_पढ़ोable,
	.ग_लिखोable_reg = max9860_ग_लिखोable,
	.अस्थिर_reg = max9860_अस्थिर,
	.precious_reg = max9860_precious,

	.max_रेजिस्टर = MAX9860_MAX_REGISTER,
	.reg_शेषs = max9860_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(max9860_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(dva_tlv, -9100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dvg_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(pam_tlv,
	0, MAX9860_PAM_MAX - 1,             TLV_DB_SCALE_ITEM(-2000, 2000, 1),
	MAX9860_PAM_MAX, MAX9860_PAM_MAX,   TLV_DB_SCALE_ITEM(3000, 0, 0));
अटल स्थिर DECLARE_TLV_DB_SCALE(pgam_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(anth_tlv, -7600, 400, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(agcth_tlv, -1800, 100, 0);

अटल स्थिर अक्षर * स्थिर agchld_text[] = अणु
	"AGC Disabled", "50ms", "100ms", "400ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(agchld_क्रमागत, MAX9860_MICADC,
			    MAX9860_AGCHLD_SHIFT, agchld_text);

अटल स्थिर अक्षर * स्थिर agcsrc_text[] = अणु
	"Left ADC", "Left/Right ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(agcsrc_क्रमागत, MAX9860_MICADC,
			    MAX9860_AGCSRC_SHIFT, agcsrc_text);

अटल स्थिर अक्षर * स्थिर agcatk_text[] = अणु
	"3ms", "12ms", "50ms", "200ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(agcatk_क्रमागत, MAX9860_MICADC,
			    MAX9860_AGCATK_SHIFT, agcatk_text);

अटल स्थिर अक्षर * स्थिर agcrls_text[] = अणु
	"78ms", "156ms", "312ms", "625ms",
	"1.25s", "2.5s", "5s", "10s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(agcrls_क्रमागत, MAX9860_MICADC,
			    MAX9860_AGCRLS_SHIFT, agcrls_text);

अटल स्थिर अक्षर * स्थिर filter_text[] = अणु
	"Disabled",
	"Elliptical HP 217Hz notch (16kHz)",
	"Butterworth HP 500Hz (16kHz)",
	"Elliptical HP 217Hz notch (8kHz)",
	"Butterworth HP 500Hz (8kHz)",
	"Butterworth HP 200Hz (48kHz)"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(avflt_क्रमागत, MAX9860_VOICEFLTR,
			    MAX9860_AVFLT_SHIFT, filter_text);

अटल SOC_ENUM_SINGLE_DECL(dvflt_क्रमागत, MAX9860_VOICEFLTR,
			    MAX9860_DVFLT_SHIFT, filter_text);

अटल स्थिर काष्ठा snd_kcontrol_new max9860_controls[] = अणु
SOC_SINGLE_TLV("Master Playback Volume", MAX9860_DACATTN,
	       MAX9860_DVA_SHIFT, MAX9860_DVA_MUTE, 1, dva_tlv),
SOC_SINGLE_TLV("DAC Gain Volume", MAX9860_DACGAIN,
	       MAX9860_DVG_SHIFT, MAX9860_DVG_MAX, 0, dvg_tlv),
SOC_DOUBLE_TLV("Line Capture Volume", MAX9860_ADCLEVEL,
	       MAX9860_ADCLL_SHIFT, MAX9860_ADCRL_SHIFT, MAX9860_ADCxL_MIN, 1,
	       adc_tlv),

SOC_ENUM("AGC Hold Time", agchld_क्रमागत),
SOC_ENUM("AGC/Noise Gate Source", agcsrc_क्रमागत),
SOC_ENUM("AGC Attack Time", agcatk_क्रमागत),
SOC_ENUM("AGC Release Time", agcrls_क्रमागत),

SOC_SINGLE_TLV("Noise Gate Threshold Volume", MAX9860_NOISEGATE,
	       MAX9860_ANTH_SHIFT, MAX9860_ANTH_MAX, 0, anth_tlv),
SOC_SINGLE_TLV("AGC Signal Threshold Volume", MAX9860_NOISEGATE,
	       MAX9860_AGCTH_SHIFT, MAX9860_AGCTH_MIN, 1, agcth_tlv),

SOC_SINGLE_TLV("Mic PGA Volume", MAX9860_MICGAIN,
	       MAX9860_PGAM_SHIFT, MAX9860_PGAM_MIN, 1, pgam_tlv),
SOC_SINGLE_TLV("Mic Preamp Volume", MAX9860_MICGAIN,
	       MAX9860_PAM_SHIFT, MAX9860_PAM_MAX, 0, pam_tlv),

SOC_ENUM("ADC Filter", avflt_क्रमागत),
SOC_ENUM("DAC Filter", dvflt_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max9860_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("MICL"),
SND_SOC_DAPM_INPUT("MICR"),

SND_SOC_DAPM_ADC("ADCL", शून्य, MAX9860_PWRMAN, MAX9860_ADCLEN_SHIFT, 0),
SND_SOC_DAPM_ADC("ADCR", शून्य, MAX9860_PWRMAN, MAX9860_ADCREN_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIFOUTL", "Capture", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIFOUTR", "Capture", 1, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_AIF_IN("AIFINL", "Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIFINR", "Playback", 1, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_DAC("DAC", शून्य, MAX9860_PWRMAN, MAX9860_DACEN_SHIFT, 0),

SND_SOC_DAPM_OUTPUT("OUT"),

SND_SOC_DAPM_SUPPLY("Supply", SND_SOC_NOPM, 0, 0,
		    शून्य, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_REGULATOR_SUPPLY("AVDD", 0, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("DVDD", 0, 0),
SND_SOC_DAPM_CLOCK_SUPPLY("mclk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max9860_dapm_routes[] = अणु
	अणु "ADCL", शून्य, "MICL" पूर्ण,
	अणु "ADCR", शून्य, "MICR" पूर्ण,
	अणु "AIFOUTL", शून्य, "ADCL" पूर्ण,
	अणु "AIFOUTR", शून्य, "ADCR" पूर्ण,

	अणु "DAC", शून्य, "AIFINL" पूर्ण,
	अणु "DAC", शून्य, "AIFINR" पूर्ण,
	अणु "OUT", शून्य, "DAC" पूर्ण,

	अणु "Supply", शून्य, "AVDD" पूर्ण,
	अणु "Supply", शून्य, "DVDD" पूर्ण,
	अणु "Supply", शून्य, "mclk" पूर्ण,

	अणु "DAC", शून्य, "Supply" पूर्ण,
	अणु "ADCL", शून्य, "Supply" पूर्ण,
	अणु "ADCR", शून्य, "Supply" पूर्ण,
पूर्ण;

अटल पूर्णांक max9860_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max9860_priv *max9860 = snd_soc_component_get_drvdata(component);
	u8 master;
	u8 अगरc1a = 0;
	u8 अगरc1b = 0;
	u8 sysclk = 0;
	अचिन्हित दीर्घ n;
	पूर्णांक ret;

	dev_dbg(component->dev, "hw_params %u Hz, %u channels\n",
		params_rate(params),
		params_channels(params));

	अगर (params_channels(params) == 2)
		अगरc1b |= MAX9860_ST;

	चयन (max9860->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master = MAX9860_MASTER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगरc1a |= master;

	अगर (master) अणु
		अगर (params_width(params) * params_channels(params) > 48)
			अगरc1b |= MAX9860_BSEL_64X;
		अन्यथा
			अगरc1b |= MAX9860_BSEL_48X;
	पूर्ण

	चयन (max9860->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरc1a |= MAX9860_DDLY;
		अगरc1b |= MAX9860_ADLY;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरc1a |= MAX9860_WCI;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगर (params_width(params) != 16) अणु
			dev_err(component->dev,
				"DSP_A works for 16 bits per sample only.\n");
			वापस -EINVAL;
		पूर्ण
		अगरc1a |= MAX9860_DDLY | MAX9860_WCI | MAX9860_HIZ | MAX9860_TDM;
		अगरc1b |= MAX9860_ADLY;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगर (params_width(params) != 16) अणु
			dev_err(component->dev,
				"DSP_B works for 16 bits per sample only.\n");
			वापस -EINVAL;
		पूर्ण
		अगरc1a |= MAX9860_WCI | MAX9860_HIZ | MAX9860_TDM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (max9860->fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		चयन (max9860->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
		हाल SND_SOC_DAIFMT_DSP_A:
		हाल SND_SOC_DAIFMT_DSP_B:
			वापस -EINVAL;
		पूर्ण
		अगरc1a ^= MAX9860_WCI;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		चयन (max9860->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
		हाल SND_SOC_DAIFMT_DSP_A:
		हाल SND_SOC_DAIFMT_DSP_B:
			वापस -EINVAL;
		पूर्ण
		अगरc1a ^= MAX9860_WCI;
		fallthrough;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरc1a ^= MAX9860_DBCI;
		अगरc1b ^= MAX9860_ABCI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "IFC1A  %02x\n", अगरc1a);
	ret = regmap_ग_लिखो(max9860->regmap, MAX9860_IFC1A, अगरc1a);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to set IFC1A: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(component->dev, "IFC1B  %02x\n", अगरc1b);
	ret = regmap_ग_लिखो(max9860->regmap, MAX9860_IFC1B, अगरc1b);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to set IFC1B: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Check अगर Integer Clock Mode is possible, but aव्योम it in slave mode
	 * since we then करो not know अगर lrclk is derived from pclk and the
	 * datasheet mentions that the frequencies have to match exactly in
	 * order क्रम this to work.
	 */
	अगर (params_rate(params) == 8000 || params_rate(params) == 16000) अणु
		अगर (master) अणु
			चयन (max9860->pclk_rate) अणु
			हाल 12000000:
				sysclk = MAX9860_FREQ_12MHZ;
				अवरोध;
			हाल 13000000:
				sysclk = MAX9860_FREQ_13MHZ;
				अवरोध;
			हाल 19200000:
				sysclk = MAX9860_FREQ_19_2MHZ;
				अवरोध;
			शेष:
				/*
				 * Integer Clock Mode not possible. Leave
				 * sysclk at zero and fall through to the
				 * code below क्रम PLL mode.
				 */
				अवरोध;
			पूर्ण

			अगर (sysclk && params_rate(params) == 16000)
				sysclk |= MAX9860_16KHZ;
		पूर्ण
	पूर्ण

	/*
	 * Largest possible n:
	 *    65536 * 96 * 48kHz / 10MHz -> 30199
	 * Smallest possible n:
	 *    65536 * 96 *  8kHz / 20MHz -> 2517
	 * Both fit nicely in the available 15 bits, no need to apply any mask.
	 */
	n = DIV_ROUND_CLOSEST_ULL(65536ULL * 96 * params_rate(params),
				  max9860->pclk_rate);

	अगर (!sysclk) अणु
		/* PLL mode */
		अगर (params_rate(params) > 24000)
			sysclk |= MAX9860_16KHZ;

		अगर (!master)
			n |= 1; /* trigger rapid pll lock mode */
	पूर्ण

	sysclk |= max9860->psclk;
	dev_dbg(component->dev, "SYSCLK %02x\n", sysclk);
	ret = regmap_ग_लिखो(max9860->regmap,
			   MAX9860_SYSCLK, sysclk);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to set SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(component->dev, "N %lu\n", n);
	ret = regmap_ग_लिखो(max9860->regmap,
			   MAX9860_AUDIOCLKHIGH, n >> 8);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to set NHI: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regmap_ग_लिखो(max9860->regmap,
			   MAX9860_AUDIOCLKLOW, n & 0xff);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to set NLO: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!master) अणु
		dev_dbg(component->dev, "Enable PLL\n");
		ret = regmap_update_bits(max9860->regmap, MAX9860_AUDIOCLKHIGH,
					 MAX9860_PLL, MAX9860_PLL);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to enable PLL: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max9860_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max9860_priv *max9860 = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		max9860->fmt = fmt;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops max9860_dai_ops = अणु
	.hw_params = max9860_hw_params,
	.set_fmt = max9860_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max9860_dai = अणु
	.name = "max9860-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 8000,
		.rate_max = 48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 8000,
		.rate_max = 48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.ops = &max9860_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक max9860_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा max9860_priv *max9860 = dev_get_drvdata(component->dev);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		ret = regmap_update_bits(max9860->regmap, MAX9860_PWRMAN,
					 MAX9860_SHDN, MAX9860_SHDN);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to remove SHDN: %d\n",
				ret);
			वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		ret = regmap_update_bits(max9860->regmap, MAX9860_PWRMAN,
					 MAX9860_SHDN, 0);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to request SHDN: %d\n",
				ret);
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver max9860_component_driver = अणु
	.set_bias_level		= max9860_set_bias_level,
	.controls		= max9860_controls,
	.num_controls		= ARRAY_SIZE(max9860_controls),
	.dapm_widमाला_लो		= max9860_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max9860_dapm_widमाला_लो),
	.dapm_routes		= max9860_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(max9860_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक max9860_suspend(काष्ठा device *dev)
अणु
	काष्ठा max9860_priv *max9860 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(max9860->regmap, MAX9860_SYSCLK,
				 MAX9860_PSCLK, MAX9860_PSCLK_OFF);
	अगर (ret) अणु
		dev_err(dev, "Failed to disable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	regulator_disable(max9860->dvddio);

	वापस 0;
पूर्ण

अटल पूर्णांक max9860_resume(काष्ठा device *dev)
अणु
	काष्ठा max9860_priv *max9860 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_enable(max9860->dvddio);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable DVDDIO: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(max9860->regmap, false);
	ret = regcache_sync(max9860->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to sync cache: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(max9860->regmap, MAX9860_SYSCLK,
				 MAX9860_PSCLK, max9860->psclk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops max9860_pm_ops = अणु
	SET_RUNTIME_PM_OPS(max9860_suspend, max9860_resume, शून्य)
पूर्ण;

अटल पूर्णांक max9860_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा max9860_priv *max9860;
	पूर्णांक ret;
	काष्ठा clk *mclk;
	अचिन्हित दीर्घ mclk_rate;
	पूर्णांक i;
	पूर्णांक पूर्णांकr;

	max9860 = devm_kzalloc(dev, माप(काष्ठा max9860_priv), GFP_KERNEL);
	अगर (!max9860)
		वापस -ENOMEM;

	max9860->dvddio = devm_regulator_get(dev, "DVDDIO");
	अगर (IS_ERR(max9860->dvddio)) अणु
		ret = PTR_ERR(max9860->dvddio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get DVDDIO supply: %d\n", ret);
		वापस ret;
	पूर्ण

	max9860->dvddio_nb.notअगरier_call = max9860_dvddio_event;

	ret = devm_regulator_रेजिस्टर_notअगरier(max9860->dvddio,
					       &max9860->dvddio_nb);
	अगर (ret)
		dev_err(dev, "Failed to register DVDDIO notifier: %d\n", ret);

	ret = regulator_enable(max9860->dvddio);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable DVDDIO: %d\n", ret);
		वापस ret;
	पूर्ण

	max9860->regmap = devm_regmap_init_i2c(i2c, &max9860_regmap);
	अगर (IS_ERR(max9860->regmap)) अणु
		ret = PTR_ERR(max9860->regmap);
		जाओ err_regulator;
	पूर्ण

	dev_set_drvdata(dev, max9860);

	/*
	 * mclk has to be in the 10MHz to 60MHz range.
	 * psclk is used to scale mclk पूर्णांकo pclk so that
	 * pclk is in the 10MHz to 20MHz range.
	 */
	mclk = clk_get(dev, "mclk");

	अगर (IS_ERR(mclk)) अणु
		ret = PTR_ERR(mclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get MCLK: %d\n", ret);
		जाओ err_regulator;
	पूर्ण

	mclk_rate = clk_get_rate(mclk);
	clk_put(mclk);

	अगर (mclk_rate > 60000000 || mclk_rate < 10000000) अणु
		dev_err(dev, "Bad mclk %luHz (needs 10MHz - 60MHz)\n",
			mclk_rate);
		ret = -EINVAL;
		जाओ err_regulator;
	पूर्ण
	अगर (mclk_rate >= 40000000)
		max9860->psclk = 3;
	अन्यथा अगर (mclk_rate >= 20000000)
		max9860->psclk = 2;
	अन्यथा
		max9860->psclk = 1;
	max9860->pclk_rate = mclk_rate >> (max9860->psclk - 1);
	max9860->psclk <<= MAX9860_PSCLK_SHIFT;
	dev_dbg(dev, "mclk %lu pclk %lu\n", mclk_rate, max9860->pclk_rate);

	regcache_cache_bypass(max9860->regmap, true);
	क्रम (i = 0; i < max9860_regmap.num_reg_शेषs; ++i) अणु
		ret = regmap_ग_लिखो(max9860->regmap,
				   max9860_regmap.reg_शेषs[i].reg,
				   max9860_regmap.reg_शेषs[i].def);
		अगर (ret) अणु
			dev_err(dev, "Failed to initialize register %u: %d\n",
				max9860_regmap.reg_शेषs[i].reg, ret);
			जाओ err_regulator;
		पूर्ण
	पूर्ण
	regcache_cache_bypass(max9860->regmap, false);

	ret = regmap_पढ़ो(max9860->regmap, MAX9860_INTRSTATUS, &पूर्णांकr);
	अगर (ret) अणु
		dev_err(dev, "Failed to clear INTRSTATUS: %d\n", ret);
		जाओ err_regulator;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &max9860_component_driver,
					      &max9860_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to register CODEC: %d\n", ret);
		जाओ err_pm;
	पूर्ण

	वापस 0;

err_pm:
	pm_runसमय_disable(dev);
err_regulator:
	regulator_disable(max9860->dvddio);
	वापस ret;
पूर्ण

अटल पूर्णांक max9860_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा max9860_priv *max9860 = dev_get_drvdata(dev);

	pm_runसमय_disable(dev);
	regulator_disable(max9860->dvddio);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max9860_i2c_id[] = अणु
	अणु "max9860", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max9860_i2c_id);

अटल स्थिर काष्ठा of_device_id max9860_of_match[] = अणु
	अणु .compatible = "maxim,max9860", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max9860_of_match);

अटल काष्ठा i2c_driver max9860_i2c_driver = अणु
	.probe_new      = max9860_probe,
	.हटाओ         = max9860_हटाओ,
	.id_table       = max9860_i2c_id,
	.driver         = अणु
		.name           = "max9860",
		.of_match_table = max9860_of_match,
		.pm             = &max9860_pm_ops,
	पूर्ण,
पूर्ण;

module_i2c_driver(max9860_i2c_driver);

MODULE_DESCRIPTION("ASoC MAX9860 Mono Audio Voice Codec driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
