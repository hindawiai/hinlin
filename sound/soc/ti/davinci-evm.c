<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ASoC driver क्रम TI DAVINCI EVM platक्रमm
 *
 * Author:      Vladimir Barinov, <vbarinov@embeddedalley.com>
 * Copyright:   (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/mach-types.h>

काष्ठा snd_soc_card_drvdata_davinci अणु
	काष्ठा clk *mclk;
	अचिन्हित sysclk;
पूर्ण;

अटल पूर्णांक evm_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *soc_card = rtd->card;
	काष्ठा snd_soc_card_drvdata_davinci *drvdata =
		snd_soc_card_get_drvdata(soc_card);

	अगर (drvdata->mclk)
		वापस clk_prepare_enable(drvdata->mclk);

	वापस 0;
पूर्ण

अटल व्योम evm_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *soc_card = rtd->card;
	काष्ठा snd_soc_card_drvdata_davinci *drvdata =
		snd_soc_card_get_drvdata(soc_card);

	clk_disable_unprepare(drvdata->mclk);
पूर्ण

अटल पूर्णांक evm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_card *soc_card = rtd->card;
	पूर्णांक ret = 0;
	अचिन्हित sysclk = ((काष्ठा snd_soc_card_drvdata_davinci *)
			   snd_soc_card_get_drvdata(soc_card))->sysclk;

	/* set the codec प्रणाली घड़ी */
	ret = snd_soc_dai_set_sysclk(codec_dai, 0, sysclk, SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	/* set the CPU प्रणाली घड़ी */
	ret = snd_soc_dai_set_sysclk(cpu_dai, 0, sysclk, SND_SOC_CLOCK_OUT);
	अगर (ret < 0 && ret != -ENOTSUPP)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops evm_ops = अणु
	.startup = evm_startup,
	.shutकरोwn = evm_shutकरोwn,
	.hw_params = evm_hw_params,
पूर्ण;

/* davinci-evm machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget aic3x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
पूर्ण;

/* davinci-evm machine audio_mapnections to the codec pins */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* Headphone connected to HPLOUT, HPROUT */
	अणु"Headphone Jack", शून्य, "HPLOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPROUT"पूर्ण,

	/* Line Out connected to LLOUT, RLOUT */
	अणु"Line Out", शून्य, "LLOUT"पूर्ण,
	अणु"Line Out", शून्य, "RLOUT"पूर्ण,

	/* Mic connected to (MIC3L | MIC3R) */
	अणु"MIC3L", शून्य, "Mic Bias"पूर्ण,
	अणु"MIC3R", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Mic Jack"पूर्ण,

	/* Line In connected to (LINE1L | LINE2L), (LINE1R | LINE2R) */
	अणु"LINE1L", शून्य, "Line In"पूर्ण,
	अणु"LINE2L", शून्य, "Line In"पूर्ण,
	अणु"LINE1R", शून्य, "Line In"पूर्ण,
	अणु"LINE2R", शून्य, "Line In"पूर्ण,
पूर्ण;

/* Logic क्रम a aic3x as connected on a davinci-evm */
अटल पूर्णांक evm_aic3x_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा device_node *np = card->dev->of_node;
	पूर्णांक ret;

	/* Add davinci-evm specअगरic widमाला_लो */
	snd_soc_dapm_new_controls(&card->dapm, aic3x_dapm_widमाला_लो,
				  ARRAY_SIZE(aic3x_dapm_widमाला_लो));

	अगर (np) अणु
		ret = snd_soc_of_parse_audio_routing(card, "ti,audio-routing");
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Set up davinci-evm specअगरic audio path audio_map */
		snd_soc_dapm_add_routes(&card->dapm, audio_map,
					ARRAY_SIZE(audio_map));
	पूर्ण

	/* not connected */
	snd_soc_dapm_nc_pin(&card->dapm, "MONO_LOUT");
	snd_soc_dapm_nc_pin(&card->dapm, "HPLCOM");
	snd_soc_dapm_nc_pin(&card->dapm, "HPRCOM");

	वापस 0;
पूर्ण

/* davinci-evm digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(dm6446,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcbsp")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.1-001b",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcbsp")));

अटल काष्ठा snd_soc_dai_link dm6446_evm_dai = अणु
	.name = "TLV320AIC3X",
	.stream_name = "AIC3X",
	.init = evm_aic3x_init,
	.ops = &evm_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAILINK_REG(dm6446),
पूर्ण;

SND_SOC_DAILINK_DEFS(dm355,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcbsp.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.1-001b",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcbsp.1")));

अटल काष्ठा snd_soc_dai_link dm355_evm_dai = अणु
	.name = "TLV320AIC3X",
	.stream_name = "AIC3X",
	.init = evm_aic3x_init,
	.ops = &evm_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAILINK_REG(dm355),
पूर्ण;

#अगर_घोषित CONFIG_SND_SOC_DM365_AIC3X_CODEC
SND_SOC_DAILINK_DEFS(dm365,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcbsp")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.1-0018",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcbsp")));
#या_अगर defined(CONFIG_SND_SOC_DM365_VOICE_CODEC)
SND_SOC_DAILINK_DEFS(dm365,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-vcif")),
	DAILINK_COMP_ARRAY(COMP_CODEC("cq93vc-codec", "cq93vc-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-vcif")));
#पूर्ण_अगर

अटल काष्ठा snd_soc_dai_link dm365_evm_dai = अणु
#अगर_घोषित CONFIG_SND_SOC_DM365_AIC3X_CODEC
	.name = "TLV320AIC3X",
	.stream_name = "AIC3X",
	.init = evm_aic3x_init,
	.ops = &evm_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAILINK_REG(dm365),
#या_अगर defined(CONFIG_SND_SOC_DM365_VOICE_CODEC)
	.name = "Voice Codec - CQ93VC",
	.stream_name = "CQ93",
	SND_SOC_DAILINK_REG(dm365),
#पूर्ण_अगर
पूर्ण;

SND_SOC_DAILINK_DEFS(dm6467_aic3x,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcasp.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.0-001a",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcasp.0")));

SND_SOC_DAILINK_DEFS(dm6467_spdअगर,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcasp.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spdif_dit", "dit-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcasp.1")));

अटल काष्ठा snd_soc_dai_link dm6467_evm_dai[] = अणु
	अणु
		.name = "TLV320AIC3X",
		.stream_name = "AIC3X",
		.init = evm_aic3x_init,
		.ops = &evm_ops,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
			   SND_SOC_DAIFMT_IB_NF,
		SND_SOC_DAILINK_REG(dm6467_aic3x),
	पूर्ण,
	अणु
		.name = "McASP",
		.stream_name = "spdif",
		.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
			   SND_SOC_DAIFMT_IB_NF,
		SND_SOC_DAILINK_REG(dm6467_spdअगर),
	पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(da830,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcasp.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.1-0018",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcasp.1")));

अटल काष्ठा snd_soc_dai_link da830_evm_dai = अणु
	.name = "TLV320AIC3X",
	.stream_name = "AIC3X",
	.init = evm_aic3x_init,
	.ops = &evm_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAILINK_REG(da830),
पूर्ण;

SND_SOC_DAILINK_DEFS(da850,
	DAILINK_COMP_ARRAY(COMP_CPU("davinci-mcasp.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.1-0018",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("davinci-mcasp.0")));

अटल काष्ठा snd_soc_dai_link da850_evm_dai = अणु
	.name = "TLV320AIC3X",
	.stream_name = "AIC3X",
	.init = evm_aic3x_init,
	.ops = &evm_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAILINK_REG(da850),
पूर्ण;

/* davinci dm6446 evm audio machine driver */
/*
 * ASP0 in DM6446 EVM is घड़ीed by U55, as configured by
 * board-dm644x-evm.c using GPIOs from U18.  There are six
 * options; here we "know" we use a 48 KHz sample rate.
 */
अटल काष्ठा snd_soc_card_drvdata_davinci dm6446_snd_soc_card_drvdata = अणु
	.sysclk = 12288000,
पूर्ण;

अटल काष्ठा snd_soc_card dm6446_snd_soc_card_evm = अणु
	.name = "DaVinci DM6446 EVM",
	.owner = THIS_MODULE,
	.dai_link = &dm6446_evm_dai,
	.num_links = 1,
	.drvdata = &dm6446_snd_soc_card_drvdata,
पूर्ण;

/* davinci dm355 evm audio machine driver */
/* ASP1 on DM355 EVM is घड़ीed by an बाह्यal oscillator */
अटल काष्ठा snd_soc_card_drvdata_davinci dm355_snd_soc_card_drvdata = अणु
	.sysclk = 27000000,
पूर्ण;

अटल काष्ठा snd_soc_card dm355_snd_soc_card_evm = अणु
	.name = "DaVinci DM355 EVM",
	.owner = THIS_MODULE,
	.dai_link = &dm355_evm_dai,
	.num_links = 1,
	.drvdata = &dm355_snd_soc_card_drvdata,
पूर्ण;

/* davinci dm365 evm audio machine driver */
अटल काष्ठा snd_soc_card_drvdata_davinci dm365_snd_soc_card_drvdata = अणु
	.sysclk = 27000000,
पूर्ण;

अटल काष्ठा snd_soc_card dm365_snd_soc_card_evm = अणु
	.name = "DaVinci DM365 EVM",
	.owner = THIS_MODULE,
	.dai_link = &dm365_evm_dai,
	.num_links = 1,
	.drvdata = &dm365_snd_soc_card_drvdata,
पूर्ण;

/* davinci dm6467 evm audio machine driver */
अटल काष्ठा snd_soc_card_drvdata_davinci dm6467_snd_soc_card_drvdata = अणु
	.sysclk = 27000000,
पूर्ण;

अटल काष्ठा snd_soc_card dm6467_snd_soc_card_evm = अणु
	.name = "DaVinci DM6467 EVM",
	.owner = THIS_MODULE,
	.dai_link = dm6467_evm_dai,
	.num_links = ARRAY_SIZE(dm6467_evm_dai),
	.drvdata = &dm6467_snd_soc_card_drvdata,
पूर्ण;

अटल काष्ठा snd_soc_card_drvdata_davinci da830_snd_soc_card_drvdata = अणु
	.sysclk = 24576000,
पूर्ण;

अटल काष्ठा snd_soc_card da830_snd_soc_card = अणु
	.name = "DA830/OMAP-L137 EVM",
	.owner = THIS_MODULE,
	.dai_link = &da830_evm_dai,
	.num_links = 1,
	.drvdata = &da830_snd_soc_card_drvdata,
पूर्ण;

अटल काष्ठा snd_soc_card_drvdata_davinci da850_snd_soc_card_drvdata = अणु
	.sysclk = 24576000,
पूर्ण;

अटल काष्ठा snd_soc_card da850_snd_soc_card = अणु
	.name = "DA850/OMAP-L138 EVM",
	.owner = THIS_MODULE,
	.dai_link = &da850_evm_dai,
	.num_links = 1,
	.drvdata = &da850_snd_soc_card_drvdata,
पूर्ण;

#अगर defined(CONFIG_OF)

/*
 * The काष्ठा is used as place holder. It will be completely
 * filled with data from dt node.
 */
SND_SOC_DAILINK_DEFS(evm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link evm_dai_tlv320aic3x = अणु
	.name		= "TLV320AIC3X",
	.stream_name	= "AIC3X",
	.ops            = &evm_ops,
	.init           = evm_aic3x_init,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAILINK_REG(evm),
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_evm_dt_ids[] = अणु
	अणु
		.compatible = "ti,da830-evm-audio",
		.data = (व्योम *) &evm_dai_tlv320aic3x,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_evm_dt_ids);

/* davinci evm audio machine driver */
अटल काष्ठा snd_soc_card evm_soc_card = अणु
	.owner = THIS_MODULE,
	.num_links = 1,
पूर्ण;

अटल पूर्णांक davinci_evm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा snd_soc_dai_link *dai;
	काष्ठा snd_soc_card_drvdata_davinci *drvdata = शून्य;
	काष्ठा clk *mclk;
	पूर्णांक ret = 0;

	match = of_match_device(of_match_ptr(davinci_evm_dt_ids), &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण

	dai = (काष्ठा snd_soc_dai_link *) match->data;

	evm_soc_card.dai_link = dai;

	dai->codecs->of_node = of_parse_phandle(np, "ti,audio-codec", 0);
	अगर (!dai->codecs->of_node)
		वापस -EINVAL;

	dai->cpus->of_node = of_parse_phandle(np, "ti,mcasp-controller", 0);
	अगर (!dai->cpus->of_node)
		वापस -EINVAL;

	dai->platक्रमms->of_node = dai->cpus->of_node;

	evm_soc_card.dev = &pdev->dev;
	ret = snd_soc_of_parse_card_name(&evm_soc_card, "ti,model");
	अगर (ret)
		वापस ret;

	mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (PTR_ERR(mclk) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (IS_ERR(mclk)) अणु
		dev_dbg(&pdev->dev, "mclk not found.\n");
		mclk = शून्य;
	पूर्ण

	drvdata = devm_kzalloc(&pdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->mclk = mclk;

	ret = of_property_पढ़ो_u32(np, "ti,codec-clock-rate", &drvdata->sysclk);

	अगर (ret < 0) अणु
		अगर (!drvdata->mclk) अणु
			dev_err(&pdev->dev,
				"No clock or clock rate defined.\n");
			वापस -EINVAL;
		पूर्ण
		drvdata->sysclk = clk_get_rate(drvdata->mclk);
	पूर्ण अन्यथा अगर (drvdata->mclk) अणु
		अचिन्हित पूर्णांक requestd_rate = drvdata->sysclk;
		clk_set_rate(drvdata->mclk, drvdata->sysclk);
		drvdata->sysclk = clk_get_rate(drvdata->mclk);
		अगर (drvdata->sysclk != requestd_rate)
			dev_warn(&pdev->dev,
				 "Could not get requested rate %u using %u.\n",
				 requestd_rate, drvdata->sysclk);
	पूर्ण

	snd_soc_card_set_drvdata(&evm_soc_card, drvdata);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &evm_soc_card);

	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_evm_driver = अणु
	.probe		= davinci_evm_probe,
	.driver		= अणु
		.name	= "davinci_evm",
		.pm	= &snd_soc_pm_ops,
		.of_match_table = of_match_ptr(davinci_evm_dt_ids),
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device *evm_snd_device;

अटल पूर्णांक __init evm_init(व्योम)
अणु
	काष्ठा snd_soc_card *evm_snd_dev_data;
	पूर्णांक index;
	पूर्णांक ret;

	/*
	 * If dtb is there, the devices will be created dynamically.
	 * Only रेजिस्टर platfrom driver काष्ठाure.
	 */
#अगर defined(CONFIG_OF)
	अगर (of_have_populated_dt())
		वापस platक्रमm_driver_रेजिस्टर(&davinci_evm_driver);
#पूर्ण_अगर

	अगर (machine_is_davinci_evm()) अणु
		evm_snd_dev_data = &dm6446_snd_soc_card_evm;
		index = 0;
	पूर्ण अन्यथा अगर (machine_is_davinci_dm355_evm()) अणु
		evm_snd_dev_data = &dm355_snd_soc_card_evm;
		index = 1;
	पूर्ण अन्यथा अगर (machine_is_davinci_dm365_evm()) अणु
		evm_snd_dev_data = &dm365_snd_soc_card_evm;
		index = 0;
	पूर्ण अन्यथा अगर (machine_is_davinci_dm6467_evm()) अणु
		evm_snd_dev_data = &dm6467_snd_soc_card_evm;
		index = 0;
	पूर्ण अन्यथा अगर (machine_is_davinci_da830_evm()) अणु
		evm_snd_dev_data = &da830_snd_soc_card;
		index = 1;
	पूर्ण अन्यथा अगर (machine_is_davinci_da850_evm()) अणु
		evm_snd_dev_data = &da850_snd_soc_card;
		index = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;

	evm_snd_device = platक्रमm_device_alloc("soc-audio", index);
	अगर (!evm_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(evm_snd_device, evm_snd_dev_data);
	ret = platक्रमm_device_add(evm_snd_device);
	अगर (ret)
		platक्रमm_device_put(evm_snd_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास evm_निकास(व्योम)
अणु
#अगर defined(CONFIG_OF)
	अगर (of_have_populated_dt()) अणु
		platक्रमm_driver_unरेजिस्टर(&davinci_evm_driver);
		वापस;
	पूर्ण
#पूर्ण_अगर

	platक्रमm_device_unरेजिस्टर(evm_snd_device);
पूर्ण

module_init(evm_init);
module_निकास(evm_निकास);

MODULE_AUTHOR("Vladimir Barinov");
MODULE_DESCRIPTION("TI DAVINCI EVM ASoC driver");
MODULE_LICENSE("GPL");
