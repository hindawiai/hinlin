<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Aपंचांगel ALSA SoC Audio Class D Amplअगरier (CLASSD) driver
 *
 * Copyright (C) 2015 Aपंचांगel
 *
 * Author: Songjun Wu <songjun.wu@aपंचांगel.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "atmel-classd.h"

काष्ठा aपंचांगel_classd_pdata अणु
	bool non_overlap_enable;
	पूर्णांक non_overlap_समय;
	पूर्णांक pwm_type;
	स्थिर अक्षर *card_name;
पूर्ण;

काष्ठा aपंचांगel_classd अणु
	dma_addr_t phy_base;
	काष्ठा regmap *regmap;
	काष्ठा clk *pclk;
	काष्ठा clk *gclk;
	काष्ठा device *dev;
	पूर्णांक irq;
	स्थिर काष्ठा aपंचांगel_classd_pdata *pdata;
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id aपंचांगel_classd_of_match[] = अणु
	अणु
		.compatible = "atmel,sama5d2-classd",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_classd_of_match);

अटल काष्ठा aपंचांगel_classd_pdata *aपंचांगel_classd_dt_init(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा aपंचांगel_classd_pdata *pdata;
	स्थिर अक्षर *pwm_type_s;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(dev, "device node not found\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	ret = of_property_पढ़ो_string(np, "atmel,pwm-type", &pwm_type_s);
	अगर ((ret == 0) && (म_भेद(pwm_type_s, "diff") == 0))
		pdata->pwm_type = CLASSD_MR_PWMTYP_DIFF;
	अन्यथा
		pdata->pwm_type = CLASSD_MR_PWMTYP_SINGLE;

	ret = of_property_पढ़ो_u32(np,
			"atmel,non-overlap-time", &pdata->non_overlap_समय);
	अगर (ret)
		pdata->non_overlap_enable = false;
	अन्यथा
		pdata->non_overlap_enable = true;

	ret = of_property_पढ़ो_string(np, "atmel,model", &pdata->card_name);
	अगर (ret)
		pdata->card_name = "CLASSD";

	वापस pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा aपंचांगel_classd_pdata *
aपंचांगel_classd_dt_init(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

#घोषणा ATMEL_CLASSD_RATES (SNDRV_PCM_RATE_8000 \
			| SNDRV_PCM_RATE_16000	| SNDRV_PCM_RATE_22050 \
			| SNDRV_PCM_RATE_32000	| SNDRV_PCM_RATE_44100 \
			| SNDRV_PCM_RATE_48000	| SNDRV_PCM_RATE_88200 \
			| SNDRV_PCM_RATE_96000)

अटल स्थिर काष्ठा snd_pcm_hardware aपंचांगel_classd_hw = अणु
	.info			= SNDRV_PCM_INFO_MMAP
				| SNDRV_PCM_INFO_MMAP_VALID
				| SNDRV_PCM_INFO_INTERLEAVED
				| SNDRV_PCM_INFO_RESUME
				| SNDRV_PCM_INFO_PAUSE,
	.क्रमmats		= (SNDRV_PCM_FMTBIT_S16_LE),
	.rates			= ATMEL_CLASSD_RATES,
	.rate_min		= 8000,
	.rate_max		= 96000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= 64 * 1024,
	.period_bytes_min	= 256,
	.period_bytes_max	= 32 * 1024,
	.periods_min		= 2,
	.periods_max		= 256,
पूर्ण;

#घोषणा ATMEL_CLASSD_PREALLOC_BUF_SIZE  (64 * 1024)

/* cpu dai component */
अटल पूर्णांक aपंचांगel_classd_cpu_dai_startup(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक err;

	regmap_ग_लिखो(dd->regmap, CLASSD_THR, 0x0);

	err = clk_prepare_enable(dd->pclk);
	अगर (err)
		वापस err;
	err = clk_prepare_enable(dd->gclk);
	अगर (err) अणु
		clk_disable_unprepare(dd->pclk);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* platक्रमm */
अटल पूर्णांक
aपंचांगel_classd_platक्रमm_configure_dma(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा dma_slave_config *slave_config)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(rtd->card);

	अगर (params_physical_width(params) != 16) अणु
		dev_err(dd->dev,
			"only supports 16-bit audio data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (params_channels(params) == 1)
		slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	अन्यथा
		slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	slave_config->direction		= DMA_MEM_TO_DEV;
	slave_config->dst_addr		= dd->phy_base + CLASSD_THR;
	slave_config->dst_maxburst	= 1;
	slave_config->src_maxburst	= 1;
	slave_config->device_fc		= false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config
aपंचांगel_classd_dmaengine_pcm_config = अणु
	.prepare_slave_config	= aपंचांगel_classd_platक्रमm_configure_dma,
	.pcm_hardware		= &aपंचांगel_classd_hw,
	.pपुनः_स्मृति_buffer_size	= ATMEL_CLASSD_PREALLOC_BUF_SIZE,
पूर्ण;

/* codec */
अटल स्थिर अक्षर * स्थिर mono_mode_text[] = अणु
	"mix", "sat", "left", "right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(classd_mono_mode_क्रमागत,
			CLASSD_INTPMR, CLASSD_INTPMR_MONO_MODE_SHIFT,
			mono_mode_text);

अटल स्थिर अक्षर * स्थिर eqcfg_text[] = अणु
	"Treble-12dB", "Treble-6dB",
	"Medium-8dB", "Medium-3dB",
	"Bass-12dB", "Bass-6dB",
	"0 dB",
	"Bass+6dB", "Bass+12dB",
	"Medium+3dB", "Medium+8dB",
	"Treble+6dB", "Treble+12dB",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक eqcfg_value[] = अणु
	CLASSD_INTPMR_EQCFG_T_CUT_12, CLASSD_INTPMR_EQCFG_T_CUT_6,
	CLASSD_INTPMR_EQCFG_M_CUT_8, CLASSD_INTPMR_EQCFG_M_CUT_3,
	CLASSD_INTPMR_EQCFG_B_CUT_12, CLASSD_INTPMR_EQCFG_B_CUT_6,
	CLASSD_INTPMR_EQCFG_FLAT,
	CLASSD_INTPMR_EQCFG_B_BOOST_6, CLASSD_INTPMR_EQCFG_B_BOOST_12,
	CLASSD_INTPMR_EQCFG_M_BOOST_3, CLASSD_INTPMR_EQCFG_M_BOOST_8,
	CLASSD_INTPMR_EQCFG_T_BOOST_6, CLASSD_INTPMR_EQCFG_T_BOOST_12,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(classd_eqcfg_क्रमागत,
		CLASSD_INTPMR, CLASSD_INTPMR_EQCFG_SHIFT, 0xf,
		eqcfg_text, eqcfg_value);

अटल स्थिर DECLARE_TLV_DB_SCALE(classd_digital_tlv, -7800, 100, 1);

अटल स्थिर काष्ठा snd_kcontrol_new aपंचांगel_classd_snd_controls[] = अणु
SOC_DOUBLE_TLV("Playback Volume", CLASSD_INTPMR,
		CLASSD_INTPMR_ATTL_SHIFT, CLASSD_INTPMR_ATTR_SHIFT,
		78, 1, classd_digital_tlv),

SOC_SINGLE("Deemphasis Switch", CLASSD_INTPMR,
		CLASSD_INTPMR_DEEMP_SHIFT, 1, 0),

SOC_SINGLE("Mono Switch", CLASSD_INTPMR, CLASSD_INTPMR_MONO_SHIFT, 1, 0),

SOC_SINGLE("Swap Switch", CLASSD_INTPMR, CLASSD_INTPMR_SWAP_SHIFT, 1, 0),

SOC_ENUM("Mono Mode", classd_mono_mode_क्रमागत),

SOC_ENUM("EQ", classd_eqcfg_क्रमागत),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_type[] = अणु
	"Single ended", "Differential"
पूर्ण;

अटल पूर्णांक aपंचांगel_classd_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_card *card = snd_soc_component_get_drvdata(component);
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(card);
	स्थिर काष्ठा aपंचांगel_classd_pdata *pdata = dd->pdata;
	u32 mask, val;

	mask = CLASSD_MR_PWMTYP_MASK;
	val = pdata->pwm_type << CLASSD_MR_PWMTYP_SHIFT;

	mask |= CLASSD_MR_NON_OVERLAP_MASK;
	अगर (pdata->non_overlap_enable) अणु
		val |= (CLASSD_MR_NON_OVERLAP_EN
			<< CLASSD_MR_NON_OVERLAP_SHIFT);

		mask |= CLASSD_MR_NOVR_VAL_MASK;
		चयन (pdata->non_overlap_समय) अणु
		हाल 5:
			val |= (CLASSD_MR_NOVR_VAL_5NS
				<< CLASSD_MR_NOVR_VAL_SHIFT);
			अवरोध;
		हाल 10:
			val |= (CLASSD_MR_NOVR_VAL_10NS
				<< CLASSD_MR_NOVR_VAL_SHIFT);
			अवरोध;
		हाल 15:
			val |= (CLASSD_MR_NOVR_VAL_15NS
				<< CLASSD_MR_NOVR_VAL_SHIFT);
			अवरोध;
		हाल 20:
			val |= (CLASSD_MR_NOVR_VAL_20NS
				<< CLASSD_MR_NOVR_VAL_SHIFT);
			अवरोध;
		शेष:
			val |= (CLASSD_MR_NOVR_VAL_10NS
				<< CLASSD_MR_NOVR_VAL_SHIFT);
			dev_warn(component->dev,
				"non-overlapping value %d is invalid, the default value 10 is specified\n",
				pdata->non_overlap_समय);
			अवरोध;
		पूर्ण
	पूर्ण

	snd_soc_component_update_bits(component, CLASSD_MR, mask, val);

	dev_info(component->dev,
		"PWM modulation type is %s, non-overlapping is %s\n",
		pwm_type[pdata->pwm_type],
		pdata->non_overlap_enable?"enabled":"disabled");

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_classd_component_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_card *card = snd_soc_component_get_drvdata(component);
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(card);

	वापस regcache_sync(dd->regmap);
पूर्ण

अटल पूर्णांक aपंचांगel_classd_cpu_dai_mute_stream(काष्ठा snd_soc_dai *cpu_dai,
					    पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = cpu_dai->component;
	u32 mask, val;

	mask = CLASSD_MR_LMUTE_MASK | CLASSD_MR_RMUTE_MASK;

	अगर (mute)
		val = mask;
	अन्यथा
		val = 0;

	snd_soc_component_update_bits(component, CLASSD_MR, mask, val);

	वापस 0;
पूर्ण

#घोषणा CLASSD_GCLK_RATE_11M2896_MPY_8 (112896 * 100 * 8)
#घोषणा CLASSD_GCLK_RATE_12M288_MPY_8  (12288 * 1000 * 8)

अटल काष्ठा अणु
	पूर्णांक rate;
	पूर्णांक sample_rate;
	पूर्णांक dsp_clk;
	अचिन्हित दीर्घ gclk_rate;
पूर्ण स्थिर sample_rates[] = अणु
	अणु 8000,  CLASSD_INTPMR_FRAME_8K,
	CLASSD_INTPMR_DSP_CLK_FREQ_12M288, CLASSD_GCLK_RATE_12M288_MPY_8 पूर्ण,
	अणु 16000, CLASSD_INTPMR_FRAME_16K,
	CLASSD_INTPMR_DSP_CLK_FREQ_12M288, CLASSD_GCLK_RATE_12M288_MPY_8 पूर्ण,
	अणु 32000, CLASSD_INTPMR_FRAME_32K,
	CLASSD_INTPMR_DSP_CLK_FREQ_12M288, CLASSD_GCLK_RATE_12M288_MPY_8 पूर्ण,
	अणु 48000, CLASSD_INTPMR_FRAME_48K,
	CLASSD_INTPMR_DSP_CLK_FREQ_12M288, CLASSD_GCLK_RATE_12M288_MPY_8 पूर्ण,
	अणु 96000, CLASSD_INTPMR_FRAME_96K,
	CLASSD_INTPMR_DSP_CLK_FREQ_12M288, CLASSD_GCLK_RATE_12M288_MPY_8 पूर्ण,
	अणु 22050, CLASSD_INTPMR_FRAME_22K,
	CLASSD_INTPMR_DSP_CLK_FREQ_11M2896, CLASSD_GCLK_RATE_11M2896_MPY_8 पूर्ण,
	अणु 44100, CLASSD_INTPMR_FRAME_44K,
	CLASSD_INTPMR_DSP_CLK_FREQ_11M2896, CLASSD_GCLK_RATE_11M2896_MPY_8 पूर्ण,
	अणु 88200, CLASSD_INTPMR_FRAME_88K,
	CLASSD_INTPMR_DSP_CLK_FREQ_11M2896, CLASSD_GCLK_RATE_11M2896_MPY_8 पूर्ण,
पूर्ण;

अटल पूर्णांक
aपंचांगel_classd_cpu_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = cpu_dai->component;
	पूर्णांक fs;
	पूर्णांक i, best, best_val, cur_val, ret;
	u32 mask, val;

	fs = params_rate(params);

	best = 0;
	best_val = असल(fs - sample_rates[0].rate);
	क्रम (i = 1; i < ARRAY_SIZE(sample_rates); i++) अणु
		/* Closest match */
		cur_val = असल(fs - sample_rates[i].rate);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण

	dev_dbg(component->dev,
		"Selected SAMPLE_RATE of %dHz, GCLK_RATE of %ldHz\n",
		sample_rates[best].rate, sample_rates[best].gclk_rate);

	clk_disable_unprepare(dd->gclk);

	ret = clk_set_rate(dd->gclk, sample_rates[best].gclk_rate);
	अगर (ret)
		वापस ret;

	mask = CLASSD_INTPMR_DSP_CLK_FREQ_MASK | CLASSD_INTPMR_FRAME_MASK;
	val = (sample_rates[best].dsp_clk << CLASSD_INTPMR_DSP_CLK_FREQ_SHIFT)
	| (sample_rates[best].sample_rate << CLASSD_INTPMR_FRAME_SHIFT);

	snd_soc_component_update_bits(component, CLASSD_INTPMR, mask, val);

	वापस clk_prepare_enable(dd->gclk);
पूर्ण

अटल व्योम
aपंचांगel_classd_cpu_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(rtd->card);

	clk_disable_unprepare(dd->gclk);
पूर्ण

अटल पूर्णांक aपंचांगel_classd_cpu_dai_prepare(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_component *component = cpu_dai->component;

	snd_soc_component_update_bits(component, CLASSD_MR,
				CLASSD_MR_LEN_MASK | CLASSD_MR_REN_MASK,
				(CLASSD_MR_LEN_DIS << CLASSD_MR_LEN_SHIFT)
				|(CLASSD_MR_REN_DIS << CLASSD_MR_REN_SHIFT));

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_classd_cpu_dai_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd, काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_component *component = cpu_dai->component;
	u32 mask, val;

	mask = CLASSD_MR_LEN_MASK | CLASSD_MR_REN_MASK;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = mask;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = (CLASSD_MR_LEN_DIS << CLASSD_MR_LEN_SHIFT)
			| (CLASSD_MR_REN_DIS << CLASSD_MR_REN_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, CLASSD_MR, mask, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops aपंचांगel_classd_cpu_dai_ops = अणु
	.startup        = aपंचांगel_classd_cpu_dai_startup,
	.shutकरोwn       = aपंचांगel_classd_cpu_dai_shutकरोwn,
	.mute_stream	= aपंचांगel_classd_cpu_dai_mute_stream,
	.hw_params	= aपंचांगel_classd_cpu_dai_hw_params,
	.prepare	= aपंचांगel_classd_cpu_dai_prepare,
	.trigger	= aपंचांगel_classd_cpu_dai_trigger,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aपंचांगel_classd_cpu_dai = अणु
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates		= ATMEL_CLASSD_RATES,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &aपंचांगel_classd_cpu_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver aपंचांगel_classd_cpu_dai_component = अणु
	.name			= "atmel-classd",
	.probe			= aपंचांगel_classd_component_probe,
	.resume			= aपंचांगel_classd_component_resume,
	.controls		= aपंचांगel_classd_snd_controls,
	.num_controls		= ARRAY_SIZE(aपंचांगel_classd_snd_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
पूर्ण;

/* ASoC sound card */
अटल पूर्णांक aपंचांगel_classd_asoc_card_init(काष्ठा device *dev,
					काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा aपंचांगel_classd *dd = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link_component *comp;

	dai_link = devm_kzalloc(dev, माप(*dai_link), GFP_KERNEL);
	अगर (!dai_link)
		वापस -ENOMEM;

	comp = devm_kzalloc(dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!comp)
		वापस -ENOMEM;

	dai_link->cpus		= &comp[0];
	dai_link->codecs	= &comp[1];
	dai_link->platक्रमms	= &comp[2];

	dai_link->num_cpus	= 1;
	dai_link->num_codecs	= 1;
	dai_link->num_platक्रमms	= 1;

	dai_link->name			= "CLASSD";
	dai_link->stream_name		= "CLASSD PCM";
	dai_link->codecs->dai_name	= "snd-soc-dummy-dai";
	dai_link->cpus->dai_name	= dev_name(dev);
	dai_link->codecs->name		= "snd-soc-dummy";
	dai_link->platक्रमms->name	= dev_name(dev);

	card->dai_link	= dai_link;
	card->num_links	= 1;
	card->name	= dd->pdata->card_name;
	card->dev	= dev;

	वापस 0;
पूर्ण;

/* regmap configuration */
अटल स्थिर काष्ठा reg_शेष aपंचांगel_classd_reg_शेषs[] = अणु
	अणु CLASSD_INTPMR,   0x00301212 पूर्ण,
पूर्ण;

#घोषणा ATMEL_CLASSD_REG_MAX    0xE4
अटल स्थिर काष्ठा regmap_config aपंचांगel_classd_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= ATMEL_CLASSD_REG_MAX,

	.cache_type		= REGCACHE_FLAT,
	.reg_शेषs		= aपंचांगel_classd_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(aपंचांगel_classd_reg_शेषs),
पूर्ण;

अटल पूर्णांक aपंचांगel_classd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_classd *dd;
	काष्ठा resource *res;
	व्योम __iomem *io_base;
	स्थिर काष्ठा aपंचांगel_classd_pdata *pdata;
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	pdata = dev_get_platdata(dev);
	अगर (!pdata) अणु
		pdata = aपंचांगel_classd_dt_init(dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	dd = devm_kzalloc(dev, माप(*dd), GFP_KERNEL);
	अगर (!dd)
		वापस -ENOMEM;

	dd->pdata = pdata;

	dd->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dd->irq < 0)
		वापस dd->irq;

	dd->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(dd->pclk)) अणु
		ret = PTR_ERR(dd->pclk);
		dev_err(dev, "failed to get peripheral clock: %d\n", ret);
		वापस ret;
	पूर्ण

	dd->gclk = devm_clk_get(dev, "gclk");
	अगर (IS_ERR(dd->gclk)) अणु
		ret = PTR_ERR(dd->gclk);
		dev_err(dev, "failed to get GCK clock: %d\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	dd->phy_base = res->start;
	dd->dev = dev;

	dd->regmap = devm_regmap_init_mmio(dev, io_base,
					&aपंचांगel_classd_regmap_config);
	अगर (IS_ERR(dd->regmap)) अणु
		ret = PTR_ERR(dd->regmap);
		dev_err(dev, "failed to init register map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev,
					&aपंचांगel_classd_cpu_dai_component,
					&aपंचांगel_classd_cpu_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "could not register CPU DAI: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(dev,
					&aपंचांगel_classd_dmaengine_pcm_config,
					0);
	अगर (ret) अणु
		dev_err(dev, "could not register platform: %d\n", ret);
		वापस ret;
	पूर्ण

	/* रेजिस्टर sound card */
	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card) अणु
		ret = -ENOMEM;
		जाओ unरेजिस्टर_codec;
	पूर्ण

	snd_soc_card_set_drvdata(card, dd);

	ret = aपंचांगel_classd_asoc_card_init(dev, card);
	अगर (ret) अणु
		dev_err(dev, "failed to init sound card\n");
		जाओ unरेजिस्टर_codec;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret) अणु
		dev_err(dev, "failed to register sound card: %d\n", ret);
		जाओ unरेजिस्टर_codec;
	पूर्ण

	वापस 0;

unरेजिस्टर_codec:
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_classd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_classd_driver = अणु
	.driver	= अणु
		.name		= "atmel-classd",
		.of_match_table	= of_match_ptr(aपंचांगel_classd_of_match),
		.pm		= &snd_soc_pm_ops,
	पूर्ण,
	.probe	= aपंचांगel_classd_probe,
	.हटाओ	= aपंचांगel_classd_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_classd_driver);

MODULE_DESCRIPTION("Atmel ClassD driver under ALSA SoC architecture");
MODULE_AUTHOR("Songjun Wu <songjun.wu@atmel.com>");
MODULE_LICENSE("GPL");
