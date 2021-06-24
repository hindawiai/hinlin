<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap-twl4030.c  --  SoC audio क्रम TI SoC based boards with twl4030 codec
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com
 * All rights reserved.
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * This driver replaces the following machine drivers:
 * omap3beagle (Author: Steve Sakoman <steve@sakoman.com>)
 * omap3evm (Author: Anuj Aggarwal <anuj.aggarwal@ti.com>)
 * overo (Author: Steve Sakoman <steve@sakoman.com>)
 * igep0020 (Author: Enric Balletbo i Serra <eballetbo@iseebcn.com>)
 * zoom2 (Author: Misael Lopez Cruz <misael.lopez@ti.com>)
 * sdp3430 (Author: Misael Lopez Cruz <misael.lopez@ti.com>)
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/omap-twl4030.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "omap-mcbsp.h"

काष्ठा omap_twl4030 अणु
	पूर्णांक jack_detect;	/* board can detect jack events */
	काष्ठा snd_soc_jack hs_jack;
पूर्ण;

अटल पूर्णांक omap_twl4030_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक fmt;

	चयन (params_channels(params)) अणु
	हाल 2: /* Stereo I2S mode */
		fmt =	SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM;
		अवरोध;
	हाल 4: /* Four channel TDM mode */
		fmt =	SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_IB_NF |
			SND_SOC_DAIFMT_CBM_CFM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_runसमय_set_dai_fmt(rtd, fmt);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops omap_twl4030_ops = अणु
	.hw_params = omap_twl4030_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Earpiece Spk", शून्य),
	SND_SOC_DAPM_SPK("Handsfree Spk", शून्य),
	SND_SOC_DAPM_HP("Headset Stereophone", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_SPK("Carkit Spk", शून्य),

	SND_SOC_DAPM_MIC("Main Mic", शून्य),
	SND_SOC_DAPM_MIC("Sub Mic", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Carkit Mic", शून्य),
	SND_SOC_DAPM_MIC("Digital0 Mic", शून्य),
	SND_SOC_DAPM_MIC("Digital1 Mic", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* Headset Stereophone:  HSOL, HSOR */
	अणु"Headset Stereophone", शून्य, "HSOL"पूर्ण,
	अणु"Headset Stereophone", शून्य, "HSOR"पूर्ण,
	/* External Speakers: HFL, HFR */
	अणु"Handsfree Spk", शून्य, "HFL"पूर्ण,
	अणु"Handsfree Spk", शून्य, "HFR"पूर्ण,
	/* External Speakers: PredrivL, PredrivR */
	अणु"Ext Spk", शून्य, "PREDRIVEL"पूर्ण,
	अणु"Ext Spk", शून्य, "PREDRIVER"पूर्ण,
	/* Carkit speakers:  CARKITL, CARKITR */
	अणु"Carkit Spk", शून्य, "CARKITL"पूर्ण,
	अणु"Carkit Spk", शून्य, "CARKITR"पूर्ण,
	/* Earpiece */
	अणु"Earpiece Spk", शून्य, "EARPIECE"पूर्ण,

	/* External Mics: MAINMIC, SUBMIC with bias */
	अणु"MAINMIC", शून्य, "Main Mic"पूर्ण,
	अणु"Main Mic", शून्य, "Mic Bias 1"पूर्ण,
	अणु"SUBMIC", शून्य, "Sub Mic"पूर्ण,
	अणु"Sub Mic", शून्य, "Mic Bias 2"पूर्ण,
	/* Headset Mic: HSMIC with bias */
	अणु"HSMIC", शून्य, "Headset Mic"पूर्ण,
	अणु"Headset Mic", शून्य, "Headset Mic Bias"पूर्ण,
	/* Digital Mics: DIGIMIC0, DIGIMIC1 with bias */
	अणु"DIGIMIC0", शून्य, "Digital0 Mic"पूर्ण,
	अणु"Digital0 Mic", शून्य, "Mic Bias 1"पूर्ण,
	अणु"DIGIMIC1", शून्य, "Digital1 Mic"पूर्ण,
	अणु"Digital1 Mic", शून्य, "Mic Bias 2"पूर्ण,
	/* Carkit In: CARKITMIC */
	अणु"CARKITMIC", शून्य, "Carkit Mic"पूर्ण,
	/* Aux In: AUXL, AUXR */
	अणु"AUXL", शून्य, "Line In"पूर्ण,
	अणु"AUXR", शून्य, "Line In"पूर्ण,
पूर्ण;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin hs_jack_pins[] = अणु
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headset Stereophone",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

/* Headset jack detection gpios */
अटल काष्ठा snd_soc_jack_gpio hs_jack_gpios[] = अणु
	अणु
		.name = "hsdet-gpio",
		.report = SND_JACK_HEADSET,
		.debounce_समय = 200,
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम twl4030_disconnect_pin(काष्ठा snd_soc_dapm_context *dapm,
					  पूर्णांक connected, अक्षर *pin)
अणु
	अगर (!connected)
		snd_soc_dapm_disable_pin(dapm, pin);
पूर्ण

अटल पूर्णांक omap_twl4030_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;
	काष्ठा omap_tw4030_pdata *pdata = dev_get_platdata(card->dev);
	काष्ठा omap_twl4030 *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret = 0;

	/* Headset jack detection only अगर it is supported */
	अगर (priv->jack_detect > 0) अणु
		hs_jack_gpios[0].gpio = priv->jack_detect;

		ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
					    SND_JACK_HEADSET, &priv->hs_jack,
					    hs_jack_pins,
					    ARRAY_SIZE(hs_jack_pins));
		अगर (ret)
			वापस ret;

		ret = snd_soc_jack_add_gpios(&priv->hs_jack,
					     ARRAY_SIZE(hs_jack_gpios),
					     hs_jack_gpios);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * शून्य pdata means we booted with DT. In this हाल the routing is
	 * provided and the card is fully routed, no need to mark pins.
	 */
	अगर (!pdata || !pdata->custom_routing)
		वापस ret;

	/* Disable not connected paths अगर not used */
	twl4030_disconnect_pin(dapm, pdata->has_ear, "Earpiece Spk");
	twl4030_disconnect_pin(dapm, pdata->has_hf, "Handsfree Spk");
	twl4030_disconnect_pin(dapm, pdata->has_hs, "Headset Stereophone");
	twl4030_disconnect_pin(dapm, pdata->has_predriv, "Ext Spk");
	twl4030_disconnect_pin(dapm, pdata->has_carkit, "Carkit Spk");

	twl4030_disconnect_pin(dapm, pdata->has_मुख्यmic, "Main Mic");
	twl4030_disconnect_pin(dapm, pdata->has_submic, "Sub Mic");
	twl4030_disconnect_pin(dapm, pdata->has_hsmic, "Headset Mic");
	twl4030_disconnect_pin(dapm, pdata->has_carkiपंचांगic, "Carkit Mic");
	twl4030_disconnect_pin(dapm, pdata->has_digimic0, "Digital0 Mic");
	twl4030_disconnect_pin(dapm, pdata->has_digimic1, "Digital1 Mic");
	twl4030_disconnect_pin(dapm, pdata->has_linein, "Line In");

	वापस ret;
पूर्ण

/* Digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("twl4030-codec", "twl4030-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.2")));

SND_SOC_DAILINK_DEFS(voice,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("twl4030-codec", "twl4030-voice")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.3")));

अटल काष्ठा snd_soc_dai_link omap_twl4030_dai_links[] = अणु
	अणु
		.name = "TWL4030 HiFi",
		.stream_name = "TWL4030 HiFi",
		.init = omap_twl4030_init,
		.ops = &omap_twl4030_ops,
		SND_SOC_DAILINK_REG(hअगरi),
	पूर्ण,
	अणु
		.name = "TWL4030 Voice",
		.stream_name = "TWL4030 Voice",
		.dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF |
			   SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(voice),
	पूर्ण,
पूर्ण;

/* Audio machine driver */
अटल काष्ठा snd_soc_card omap_twl4030_card = अणु
	.owner = THIS_MODULE,
	.dai_link = omap_twl4030_dai_links,
	.num_links = ARRAY_SIZE(omap_twl4030_dai_links),

	.dapm_widमाला_लो = dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल पूर्णांक omap_twl4030_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_tw4030_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &omap_twl4030_card;
	काष्ठा omap_twl4030 *priv;
	पूर्णांक ret = 0;

	card->dev = &pdev->dev;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_twl4030), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	अगर (node) अणु
		काष्ठा device_node *dai_node;
		काष्ठा property *prop;

		अगर (snd_soc_of_parse_card_name(card, "ti,model")) अणु
			dev_err(&pdev->dev, "Card name is not provided\n");
			वापस -ENODEV;
		पूर्ण

		dai_node = of_parse_phandle(node, "ti,mcbsp", 0);
		अगर (!dai_node) अणु
			dev_err(&pdev->dev, "McBSP node is not provided\n");
			वापस -EINVAL;
		पूर्ण
		omap_twl4030_dai_links[0].cpus->dai_name  = शून्य;
		omap_twl4030_dai_links[0].cpus->of_node = dai_node;

		omap_twl4030_dai_links[0].platक्रमms->name  = शून्य;
		omap_twl4030_dai_links[0].platक्रमms->of_node = dai_node;

		dai_node = of_parse_phandle(node, "ti,mcbsp-voice", 0);
		अगर (!dai_node) अणु
			card->num_links = 1;
		पूर्ण अन्यथा अणु
			omap_twl4030_dai_links[1].cpus->dai_name  = शून्य;
			omap_twl4030_dai_links[1].cpus->of_node = dai_node;

			omap_twl4030_dai_links[1].platक्रमms->name  = शून्य;
			omap_twl4030_dai_links[1].platक्रमms->of_node = dai_node;
		पूर्ण

		priv->jack_detect = of_get_named_gpio(node,
						      "ti,jack-det-gpio", 0);

		/* Optional: audio routing can be provided */
		prop = of_find_property(node, "ti,audio-routing", शून्य);
		अगर (prop) अणु
			ret = snd_soc_of_parse_audio_routing(card,
							    "ti,audio-routing");
			अगर (ret)
				वापस ret;

			card->fully_routed = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (pdata) अणु
		अगर (pdata->card_name) अणु
			card->name = pdata->card_name;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "Card name is not provided\n");
			वापस -ENODEV;
		पूर्ण

		अगर (!pdata->voice_connected)
			card->num_links = 1;

		priv->jack_detect = pdata->jack_detect;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Missing pdata\n");
		वापस -ENODEV;
	पूर्ण

	snd_soc_card_set_drvdata(card, priv);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "devm_snd_soc_register_card() failed: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_twl4030_of_match[] = अणु
	अणु.compatible = "ti,omap-twl4030", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_twl4030_of_match);

अटल काष्ठा platक्रमm_driver omap_twl4030_driver = अणु
	.driver = अणु
		.name = "omap-twl4030",
		.pm = &snd_soc_pm_ops,
		.of_match_table = omap_twl4030_of_match,
	पूर्ण,
	.probe = omap_twl4030_probe,
पूर्ण;

module_platक्रमm_driver(omap_twl4030_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("ALSA SoC for TI SoC based boards with twl4030 codec");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap-twl4030");
