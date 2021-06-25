<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap-abe-twl6040.c  --  SoC audio क्रम TI OMAP based boards with ABE and
 *			   twl6040 codec
 *
 * Author: Misael Lopez Cruz <misael.lopez@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/twl6040.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "omap-dmic.h"
#समावेश "omap-mcpdm.h"
#समावेश "../codecs/twl6040.h"

SND_SOC_DAILINK_DEFS(link0,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC("twl6040-codec",
				      "twl6040-legacy")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(link1,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec",
				      "dmic-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

काष्ठा abe_twl6040 अणु
	काष्ठा snd_soc_card card;
	काष्ठा snd_soc_dai_link dai_links[2];
	पूर्णांक	jack_detection;	/* board can detect jack events */
	पूर्णांक	mclk_freq;	/* MCLK frequency speed क्रम twl6040 */
पूर्ण;

अटल काष्ठा platक्रमm_device *dmic_codec_dev;

अटल पूर्णांक omap_abe_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा abe_twl6040 *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक clk_id, freq;
	पूर्णांक ret;

	clk_id = twl6040_get_clk_id(codec_dai->component);
	अगर (clk_id == TWL6040_SYSCLK_SEL_HPPLL)
		freq = priv->mclk_freq;
	अन्यथा अगर (clk_id == TWL6040_SYSCLK_SEL_LPPLL)
		freq = 32768;
	अन्यथा
		वापस -EINVAL;

	/* set the codec mclk */
	ret = snd_soc_dai_set_sysclk(codec_dai, clk_id, freq,
				SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "can't set codec system clock\n");
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops omap_abe_ops = अणु
	.hw_params = omap_abe_hw_params,
पूर्ण;

अटल पूर्णांक omap_abe_dmic_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret = 0;

	ret = snd_soc_dai_set_sysclk(cpu_dai, OMAP_DMIC_SYSCLK_PAD_CLKS,
				     19200000, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "can't set DMIC cpu system clock\n");
		वापस ret;
	पूर्ण
	ret = snd_soc_dai_set_sysclk(cpu_dai, OMAP_DMIC_ABE_DMIC_CLK, 2400000,
				     SND_SOC_CLOCK_OUT);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "can't set DMIC output clock\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops omap_abe_dmic_ops = अणु
	.hw_params = omap_abe_dmic_hw_params,
पूर्ण;

/* Headset jack */
अटल काष्ठा snd_soc_jack hs_jack;

/*Headset jack detection DAPM pins */
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

/* SDP4430 machine DAPM */
अटल स्थिर काष्ठा snd_soc_dapm_widget twl6040_dapm_widमाला_लो[] = अणु
	/* Outमाला_दो */
	SND_SOC_DAPM_HP("Headset Stereophone", शून्य),
	SND_SOC_DAPM_SPK("Earphone Spk", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),
	SND_SOC_DAPM_SPK("Vibrator", शून्य),

	/* Inमाला_दो */
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Main Handset Mic", शून्य),
	SND_SOC_DAPM_MIC("Sub Handset Mic", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),

	/* Digital microphones */
	SND_SOC_DAPM_MIC("Digital Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* Routings क्रम outमाला_दो */
	अणु"Headset Stereophone", शून्य, "HSOL"पूर्ण,
	अणु"Headset Stereophone", शून्य, "HSOR"पूर्ण,

	अणु"Earphone Spk", शून्य, "EP"पूर्ण,

	अणु"Ext Spk", शून्य, "HFL"पूर्ण,
	अणु"Ext Spk", शून्य, "HFR"पूर्ण,

	अणु"Line Out", शून्य, "AUXL"पूर्ण,
	अणु"Line Out", शून्य, "AUXR"पूर्ण,

	अणु"Vibrator", शून्य, "VIBRAL"पूर्ण,
	अणु"Vibrator", शून्य, "VIBRAR"पूर्ण,

	/* Routings क्रम inमाला_दो */
	अणु"HSMIC", शून्य, "Headset Mic"पूर्ण,
	अणु"Headset Mic", शून्य, "Headset Mic Bias"पूर्ण,

	अणु"MAINMIC", शून्य, "Main Handset Mic"पूर्ण,
	अणु"Main Handset Mic", शून्य, "Main Mic Bias"पूर्ण,

	अणु"SUBMIC", शून्य, "Sub Handset Mic"पूर्ण,
	अणु"Sub Handset Mic", शून्य, "Main Mic Bias"पूर्ण,

	अणु"AFML", शून्य, "Line In"पूर्ण,
	अणु"AFMR", शून्य, "Line In"पूर्ण,
पूर्ण;

अटल पूर्णांक omap_abe_twl6040_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा abe_twl6040 *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक hs_trim;
	पूर्णांक ret;

	/*
	 * Configure McPDM offset cancellation based on the HSOTRIM value from
	 * twl6040.
	 */
	hs_trim = twl6040_get_trim_value(component, TWL6040_TRIM_HSOTRIM);
	omap_mcpdm_configure_dn_offsets(rtd, TWL6040_HSF_TRIM_LEFT(hs_trim),
					TWL6040_HSF_TRIM_RIGHT(hs_trim));

	/* Headset jack detection only अगर it is supported */
	अगर (priv->jack_detection) अणु
		ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
					    SND_JACK_HEADSET, &hs_jack,
					    hs_jack_pins,
					    ARRAY_SIZE(hs_jack_pins));
		अगर (ret)
			वापस ret;

		twl6040_hs_jack_detect(component, &hs_jack, SND_JACK_HEADSET);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route dmic_audio_map[] = अणु
	अणु"DMic", शून्य, "Digital Mic"पूर्ण,
	अणु"Digital Mic", शून्य, "Digital Mic1 Bias"पूर्ण,
पूर्ण;

अटल पूर्णांक omap_abe_dmic_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;

	वापस snd_soc_dapm_add_routes(dapm, dmic_audio_map,
				ARRAY_SIZE(dmic_audio_map));
पूर्ण

अटल पूर्णांक omap_abe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा snd_soc_card *card;
	काष्ठा device_node *dai_node;
	काष्ठा abe_twl6040 *priv;
	पूर्णांक num_links = 0;
	पूर्णांक ret = 0;

	अगर (!node) अणु
		dev_err(&pdev->dev, "of node is missing.\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा abe_twl6040), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	card = &priv->card;
	card->dev = &pdev->dev;
	card->owner = THIS_MODULE;
	card->dapm_widमाला_लो = twl6040_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो = ARRAY_SIZE(twl6040_dapm_widमाला_लो);
	card->dapm_routes = audio_map;
	card->num_dapm_routes = ARRAY_SIZE(audio_map);

	अगर (snd_soc_of_parse_card_name(card, "ti,model")) अणु
		dev_err(&pdev->dev, "Card name is not provided\n");
		वापस -ENODEV;
	पूर्ण

	ret = snd_soc_of_parse_audio_routing(card, "ti,audio-routing");
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error while parsing DAPM routing\n");
		वापस ret;
	पूर्ण

	dai_node = of_parse_phandle(node, "ti,mcpdm", 0);
	अगर (!dai_node) अणु
		dev_err(&pdev->dev, "McPDM node is not provided\n");
		वापस -EINVAL;
	पूर्ण

	priv->dai_links[0].name = "DMIC";
	priv->dai_links[0].stream_name = "TWL6040";
	priv->dai_links[0].cpus = link0_cpus;
	priv->dai_links[0].num_cpus = 1;
	priv->dai_links[0].cpus->of_node = dai_node;
	priv->dai_links[0].platक्रमms = link0_platक्रमms;
	priv->dai_links[0].num_platक्रमms = 1;
	priv->dai_links[0].platक्रमms->of_node = dai_node;
	priv->dai_links[0].codecs = link0_codecs;
	priv->dai_links[0].num_codecs = 1;
	priv->dai_links[0].init = omap_abe_twl6040_init;
	priv->dai_links[0].ops = &omap_abe_ops;

	dai_node = of_parse_phandle(node, "ti,dmic", 0);
	अगर (dai_node) अणु
		num_links = 2;
		priv->dai_links[1].name = "TWL6040";
		priv->dai_links[1].stream_name = "DMIC Capture";
		priv->dai_links[1].cpus = link1_cpus;
		priv->dai_links[1].num_cpus = 1;
		priv->dai_links[1].cpus->of_node = dai_node;
		priv->dai_links[1].platक्रमms = link1_platक्रमms;
		priv->dai_links[1].num_platक्रमms = 1;
		priv->dai_links[1].platक्रमms->of_node = dai_node;
		priv->dai_links[1].codecs = link1_codecs;
		priv->dai_links[1].num_codecs = 1;
		priv->dai_links[1].init = omap_abe_dmic_init;
		priv->dai_links[1].ops = &omap_abe_dmic_ops;
	पूर्ण अन्यथा अणु
		num_links = 1;
	पूर्ण

	priv->jack_detection = of_property_पढ़ो_bool(node, "ti,jack-detection");
	of_property_पढ़ो_u32(node, "ti,mclk-freq", &priv->mclk_freq);
	अगर (!priv->mclk_freq) अणु
		dev_err(&pdev->dev, "MCLK frequency not provided\n");
		वापस -EINVAL;
	पूर्ण

	card->fully_routed = 1;

	अगर (!priv->mclk_freq) अणु
		dev_err(&pdev->dev, "MCLK frequency missing\n");
		वापस -ENODEV;
	पूर्ण

	card->dai_link = priv->dai_links;
	card->num_links = num_links;

	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "devm_snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_abe_of_match[] = अणु
	अणु.compatible = "ti,abe-twl6040", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_abe_of_match);

अटल काष्ठा platक्रमm_driver omap_abe_driver = अणु
	.driver = अणु
		.name = "omap-abe-twl6040",
		.pm = &snd_soc_pm_ops,
		.of_match_table = omap_abe_of_match,
	पूर्ण,
	.probe = omap_abe_probe,
पूर्ण;

अटल पूर्णांक __init omap_abe_init(व्योम)
अणु
	पूर्णांक ret;

	dmic_codec_dev = platक्रमm_device_रेजिस्टर_simple("dmic-codec", -1, शून्य,
							 0);
	अगर (IS_ERR(dmic_codec_dev)) अणु
		pr_err("%s: dmic-codec device registration failed\n", __func__);
		वापस PTR_ERR(dmic_codec_dev);
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&omap_abe_driver);
	अगर (ret) अणु
		pr_err("%s: platform driver registration failed\n", __func__);
		platक्रमm_device_unरेजिस्टर(dmic_codec_dev);
	पूर्ण

	वापस ret;
पूर्ण
module_init(omap_abe_init);

अटल व्योम __निकास omap_abe_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_abe_driver);
	platक्रमm_device_unरेजिस्टर(dmic_codec_dev);
पूर्ण
module_निकास(omap_abe_निकास);

MODULE_AUTHOR("Misael Lopez Cruz <misael.lopez@ti.com>");
MODULE_DESCRIPTION("ALSA SoC for OMAP boards with ABE and twl6040 codec");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap-abe-twl6040");
