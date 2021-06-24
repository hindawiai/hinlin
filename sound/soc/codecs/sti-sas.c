<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Arnaud Pouliquen <arnaud.pouliquen@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>

/* DAC definitions */

/* stih407 DAC रेजिस्टरs */
/* sysconf 5041: Audio-Gue-Control */
#घोषणा STIH407_AUDIO_GLUE_CTRL 0x000000A4
/* sysconf 5042: Audio-DAC-Control */
#घोषणा STIH407_AUDIO_DAC_CTRL 0x000000A8

/* DAC definitions */
#घोषणा STIH407_DAC_SOFTMUTE		0x0
#घोषणा STIH407_DAC_STANDBY_ANA		0x1
#घोषणा STIH407_DAC_STANDBY		0x2

#घोषणा STIH407_DAC_SOFTMUTE_MASK	BIT(STIH407_DAC_SOFTMUTE)
#घोषणा STIH407_DAC_STANDBY_ANA_MASK    BIT(STIH407_DAC_STANDBY_ANA)
#घोषणा STIH407_DAC_STANDBY_MASK        BIT(STIH407_DAC_STANDBY)

/* SPDIF definitions */
#घोषणा SPDIF_BIPHASE_ENABLE		0x6
#घोषणा SPDIF_BIPHASE_IDLE		0x7

#घोषणा SPDIF_BIPHASE_ENABLE_MASK	BIT(SPDIF_BIPHASE_ENABLE)
#घोषणा SPDIF_BIPHASE_IDLE_MASK		BIT(SPDIF_BIPHASE_IDLE)

क्रमागत अणु
	STI_SAS_DAI_SPDIF_OUT,
	STI_SAS_DAI_ANALOG_OUT,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष stih407_sas_reg_शेषs[] = अणु
	अणु STIH407_AUDIO_DAC_CTRL, 0x000000000 पूर्ण,
	अणु STIH407_AUDIO_GLUE_CTRL, 0x00000040 पूर्ण,
पूर्ण;

काष्ठा sti_dac_audio अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap *virt_regmap;
	पूर्णांक mclk;
पूर्ण;

काष्ठा sti_spdअगर_audio अणु
	काष्ठा regmap *regmap;
	पूर्णांक mclk;
पूर्ण;

/* device data काष्ठाure */
काष्ठा sti_sas_dev_data अणु
	स्थिर काष्ठा regmap_config *regmap;
	स्थिर काष्ठा snd_soc_dai_ops *dac_ops;  /* DAC function callbacks */
	स्थिर काष्ठा snd_soc_dapm_widget *dapm_widमाला_लो; /* dapms declaration */
	स्थिर पूर्णांक num_dapm_widमाला_लो; /* dapms declaration */
	स्थिर काष्ठा snd_soc_dapm_route *dapm_routes; /* route declaration */
	स्थिर पूर्णांक num_dapm_routes; /* route declaration */
पूर्ण;

/* driver data काष्ठाure */
काष्ठा sti_sas_data अणु
	काष्ठा device *dev;
	स्थिर काष्ठा sti_sas_dev_data *dev_data;
	काष्ठा sti_dac_audio dac;
	काष्ठा sti_spdअगर_audio spdअगर;
पूर्ण;

/* Read a रेजिस्टर from the sysconf reg bank */
अटल पूर्णांक sti_sas_पढ़ो_reg(व्योम *context, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक *value)
अणु
	काष्ठा sti_sas_data *drvdata = context;
	पूर्णांक status;
	u32 val;

	status = regmap_पढ़ो(drvdata->dac.regmap, reg, &val);
	*value = (अचिन्हित पूर्णांक)val;

	वापस status;
पूर्ण

/* Read a रेजिस्टर from the sysconf reg bank */
अटल पूर्णांक sti_sas_ग_लिखो_reg(व्योम *context, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक value)
अणु
	काष्ठा sti_sas_data *drvdata = context;
	पूर्णांक status;

	status = regmap_ग_लिखो(drvdata->dac.regmap, reg, value);

	वापस status;
पूर्ण

अटल पूर्णांक  sti_sas_init_sas_रेजिस्टरs(काष्ठा snd_soc_component *component,
				       काष्ठा sti_sas_data *data)
अणु
	पूर्णांक ret;
	/*
	 * DAC and SPDIF are activated by शेष
	 * put them in IDLE to save घातer
	 */

	/* Initialise bi-phase क्रमmatter to disabled */
	ret = snd_soc_component_update_bits(component, STIH407_AUDIO_GLUE_CTRL,
				  SPDIF_BIPHASE_ENABLE_MASK, 0);

	अगर (!ret)
		/* Initialise bi-phase क्रमmatter idle value to 0 */
		ret = snd_soc_component_update_bits(component, STIH407_AUDIO_GLUE_CTRL,
					  SPDIF_BIPHASE_IDLE_MASK, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to update SPDIF registers\n");
		वापस ret;
	पूर्ण

	/* Init DAC configuration */
	/* init configuration */
	ret =  snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
				   STIH407_DAC_STANDBY_MASK,
				   STIH407_DAC_STANDBY_MASK);

	अगर (!ret)
		ret = snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					  STIH407_DAC_STANDBY_ANA_MASK,
					  STIH407_DAC_STANDBY_ANA_MASK);
	अगर (!ret)
		ret = snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					  STIH407_DAC_SOFTMUTE_MASK,
					  STIH407_DAC_SOFTMUTE_MASK);

	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to update DAC registers\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * DAC
 */
अटल पूर्णांक sti_sas_dac_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	/* Sanity check only */
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupporter master mask 0x%x\n",
			__func__, fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget stih407_sas_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUT_DRV("DAC standby ana", STIH407_AUDIO_DAC_CTRL,
			     STIH407_DAC_STANDBY_ANA, 1, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC standby",  "dac_p", STIH407_AUDIO_DAC_CTRL,
			 STIH407_DAC_STANDBY, 1),
	SND_SOC_DAPM_OUTPUT("DAC Output"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route stih407_sas_route[] = अणु
	अणु"DAC Output", शून्य, "DAC standby ana"पूर्ण,
	अणु"DAC standby ana", शून्य, "DAC standby"पूर्ण,
पूर्ण;


अटल पूर्णांक stih407_sas_dac_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute) अणु
		वापस snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					    STIH407_DAC_SOFTMUTE_MASK,
					    STIH407_DAC_SOFTMUTE_MASK);
	पूर्ण अन्यथा अणु
		वापस snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					    STIH407_DAC_SOFTMUTE_MASK,
					    0);
	पूर्ण
पूर्ण

/*
 * SPDIF
 */
अटल पूर्णांक sti_sas_spdअगर_set_fmt(काष्ठा snd_soc_dai *dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupporter master mask 0x%x\n",
			__func__, fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * sti_sas_spdअगर_trigger:
 * Trigger function is used to ensure that BiPhase Formater is disabled
 * beक्रमe CPU dai is stopped.
 * This is mandatory to aव्योम that BPF is stalled
 */
अटल पूर्णांक sti_sas_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		वापस snd_soc_component_update_bits(component, STIH407_AUDIO_GLUE_CTRL,
					    SPDIF_BIPHASE_ENABLE_MASK,
					    SPDIF_BIPHASE_ENABLE_MASK);
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		वापस snd_soc_component_update_bits(component, STIH407_AUDIO_GLUE_CTRL,
					    SPDIF_BIPHASE_ENABLE_MASK,
					    0);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool sti_sas_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == STIH407_AUDIO_GLUE_CTRL)
		वापस true;

	वापस false;
पूर्ण

/*
 * CODEC DAIS
 */

/*
 * sti_sas_set_sysclk:
 * get MCLK input frequency to check that MCLK-FS ratio is coherent
 */
अटल पूर्णांक sti_sas_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			      अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा sti_sas_data *drvdata = dev_get_drvdata(component->dev);

	अगर (dir == SND_SOC_CLOCK_OUT)
		वापस 0;

	अगर (clk_id != 0)
		वापस -EINVAL;

	चयन (dai->id) अणु
	हाल STI_SAS_DAI_SPDIF_OUT:
		drvdata->spdअगर.mclk = freq;
		अवरोध;

	हाल STI_SAS_DAI_ANALOG_OUT:
		drvdata->dac.mclk = freq;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sti_sas_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा sti_sas_data *drvdata = dev_get_drvdata(component->dev);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	चयन (dai->id) अणु
	हाल STI_SAS_DAI_SPDIF_OUT:
		अगर ((drvdata->spdअगर.mclk / runसमय->rate) != 128) अणु
			dev_err(component->dev, "unexpected mclk-fs ratio\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल STI_SAS_DAI_ANALOG_OUT:
		अगर ((drvdata->dac.mclk / runसमय->rate) != 256) अणु
			dev_err(component->dev, "unexpected mclk-fs ratio\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops stih407_dac_ops = अणु
	.set_fmt = sti_sas_dac_set_fmt,
	.mute_stream = stih407_sas_dac_mute,
	.prepare = sti_sas_prepare,
	.set_sysclk = sti_sas_set_sysclk,
पूर्ण;

अटल स्थिर काष्ठा regmap_config stih407_sas_regmap = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.fast_io = true,
	.max_रेजिस्टर = STIH407_AUDIO_DAC_CTRL,
	.reg_शेषs = stih407_sas_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(stih407_sas_reg_शेषs),
	.अस्थिर_reg = sti_sas_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_पढ़ो = sti_sas_पढ़ो_reg,
	.reg_ग_लिखो = sti_sas_ग_लिखो_reg,
पूर्ण;

अटल स्थिर काष्ठा sti_sas_dev_data stih407_data = अणु
	.regmap = &stih407_sas_regmap,
	.dac_ops = &stih407_dac_ops,
	.dapm_widमाला_लो = stih407_sas_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(stih407_sas_dapm_widमाला_लो),
	.dapm_routes =	stih407_sas_route,
	.num_dapm_routes = ARRAY_SIZE(stih407_sas_route),
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sti_sas_dai[] = अणु
	अणु
		.name = "sas-dai-spdif-out",
		.id = STI_SAS_DAI_SPDIF_OUT,
		.playback = अणु
			.stream_name = "spdif_p",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 |
				 SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = (काष्ठा snd_soc_dai_ops[]) अणु
			अणु
				.set_fmt = sti_sas_spdअगर_set_fmt,
				.trigger = sti_sas_spdअगर_trigger,
				.set_sysclk = sti_sas_set_sysclk,
				.prepare = sti_sas_prepare,
			पूर्ण
		पूर्ण,
	पूर्ण,
	अणु
		.name = "sas-dai-dac",
		.id = STI_SAS_DAI_ANALOG_OUT,
		.playback = अणु
			.stream_name = "dac_p",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sti_sas_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sti_sas_data *drvdata = dev_get_drvdata(component->dev);

	वापस sti_sas_init_sas_रेजिस्टरs(component, drvdata);
पूर्ण
#अन्यथा
#घोषणा sti_sas_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक sti_sas_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sti_sas_data *drvdata = dev_get_drvdata(component->dev);
	पूर्णांक ret;

	ret = sti_sas_init_sas_रेजिस्टरs(component, drvdata);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_component_driver sti_sas_driver = अणु
	.probe			= sti_sas_component_probe,
	.resume			= sti_sas_resume,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sti_sas_dev_match[] = अणु
	अणु
		.compatible = "st,stih407-sas-codec",
		.data = &stih407_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sti_sas_dev_match);

अटल पूर्णांक sti_sas_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *pnode = pdev->dev.of_node;
	काष्ठा sti_sas_data *drvdata;
	स्थिर काष्ठा of_device_id *of_id;

	/* Allocate device काष्ठाure */
	drvdata = devm_kzalloc(&pdev->dev, माप(काष्ठा sti_sas_data),
			       GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	/* Populate data काष्ठाure depending on compatibility */
	of_id = of_match_node(sti_sas_dev_match, pnode);
	अगर (!of_id->data) अणु
		dev_err(&pdev->dev, "data associated to device is missing\n");
		वापस -EINVAL;
	पूर्ण

	drvdata->dev_data = (काष्ठा sti_sas_dev_data *)of_id->data;

	/* Initialise device काष्ठाure */
	drvdata->dev = &pdev->dev;

	/* Request the DAC & SPDIF रेजिस्टरs memory region */
	drvdata->dac.virt_regmap = devm_regmap_init(&pdev->dev, शून्य, drvdata,
						    drvdata->dev_data->regmap);
	अगर (IS_ERR(drvdata->dac.virt_regmap)) अणु
		dev_err(&pdev->dev, "audio registers not enabled\n");
		वापस PTR_ERR(drvdata->dac.virt_regmap);
	पूर्ण

	/* Request the syscon region */
	drvdata->dac.regmap =
		syscon_regmap_lookup_by_phandle(pnode, "st,syscfg");
	अगर (IS_ERR(drvdata->dac.regmap)) अणु
		dev_err(&pdev->dev, "syscon registers not available\n");
		वापस PTR_ERR(drvdata->dac.regmap);
	पूर्ण
	drvdata->spdअगर.regmap = drvdata->dac.regmap;

	sti_sas_dai[STI_SAS_DAI_ANALOG_OUT].ops = drvdata->dev_data->dac_ops;

	/* Set dapms*/
	sti_sas_driver.dapm_widमाला_लो = drvdata->dev_data->dapm_widमाला_लो;
	sti_sas_driver.num_dapm_widमाला_लो = drvdata->dev_data->num_dapm_widमाला_लो;

	sti_sas_driver.dapm_routes = drvdata->dev_data->dapm_routes;
	sti_sas_driver.num_dapm_routes = drvdata->dev_data->num_dapm_routes;

	/* Store context */
	dev_set_drvdata(&pdev->dev, drvdata);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sti_sas_driver,
					sti_sas_dai,
					ARRAY_SIZE(sti_sas_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver sti_sas_platक्रमm_driver = अणु
	.driver = अणु
		.name = "sti-sas-codec",
		.of_match_table = sti_sas_dev_match,
	पूर्ण,
	.probe = sti_sas_driver_probe,
पूर्ण;

module_platक्रमm_driver(sti_sas_platक्रमm_driver);

MODULE_DESCRIPTION("audio codec for STMicroelectronics sti platforms");
MODULE_AUTHOR("Arnaud.pouliquen@st.com");
MODULE_LICENSE("GPL v2");
