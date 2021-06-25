<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2012 Freescale Semiconductor, Inc.
// Copyright 2012 Linaro Ltd.

#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_gpपन.स>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "imx-audmux.h"

#घोषणा DAI_NAME_SIZE	32
#घोषणा MUX_PORT_MAX	7

काष्ठा imx_es8328_data अणु
	काष्ठा device *dev;
	काष्ठा snd_soc_dai_link dai;
	काष्ठा snd_soc_card card;
	अक्षर codec_dai_name[DAI_NAME_SIZE];
	अक्षर platक्रमm_name[DAI_NAME_SIZE];
	पूर्णांक jack_gpio;
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio headset_jack_gpios[] = अणु
	अणु
		.gpio = -1,
		.name = "headset-gpio",
		.report = SND_JACK_HEADSET,
		.invert = 0,
		.debounce_समय = 200,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack headset_jack;

अटल पूर्णांक imx_es8328_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा imx_es8328_data *data = container_of(rtd->card,
					काष्ठा imx_es8328_data, card);
	पूर्णांक ret = 0;

	/* Headphone jack detection */
	अगर (gpio_is_valid(data->jack_gpio)) अणु
		ret = snd_soc_card_jack_new(rtd->card, "Headphone",
					    SND_JACK_HEADPHONE | SND_JACK_BTN_0,
					    &headset_jack, शून्य, 0);
		अगर (ret)
			वापस ret;

		headset_jack_gpios[0].gpio = data->jack_gpio;
		ret = snd_soc_jack_add_gpios(&headset_jack,
					     ARRAY_SIZE(headset_jack_gpios),
					     headset_jack_gpios);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget imx_es8328_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_REGULATOR_SUPPLY("audio-amp", 1, 0),
पूर्ण;

अटल पूर्णांक imx_es8328_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *ssi_np = शून्य, *codec_np = शून्य;
	काष्ठा platक्रमm_device *ssi_pdev;
	काष्ठा imx_es8328_data *data;
	काष्ठा snd_soc_dai_link_component *comp;
	u32 पूर्णांक_port, ext_port;
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	ret = of_property_पढ़ो_u32(np, "mux-int-port", &पूर्णांक_port);
	अगर (ret) अणु
		dev_err(dev, "mux-int-port missing or invalid\n");
		जाओ fail;
	पूर्ण
	अगर (पूर्णांक_port > MUX_PORT_MAX || पूर्णांक_port == 0) अणु
		dev_err(dev, "mux-int-port: hardware only has %d mux ports\n",
			MUX_PORT_MAX);
		जाओ fail;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "mux-ext-port", &ext_port);
	अगर (ret) अणु
		dev_err(dev, "mux-ext-port missing or invalid\n");
		जाओ fail;
	पूर्ण
	अगर (ext_port > MUX_PORT_MAX || ext_port == 0) अणु
		dev_err(dev, "mux-ext-port: hardware only has %d mux ports\n",
			MUX_PORT_MAX);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	/*
	 * The port numbering in the hardware manual starts at 1, जबतक
	 * the audmux API expects it starts at 0.
	 */
	पूर्णांक_port--;
	ext_port--;
	ret = imx_audmux_v2_configure_port(पूर्णांक_port,
			IMX_AUDMUX_V2_PTCR_SYN |
			IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			IMX_AUDMUX_V2_PTCR_TFSसूची |
			IMX_AUDMUX_V2_PTCR_TCLKसूची,
			IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port));
	अगर (ret) अणु
		dev_err(dev, "audmux internal port setup failed\n");
		वापस ret;
	पूर्ण
	ret = imx_audmux_v2_configure_port(ext_port,
			IMX_AUDMUX_V2_PTCR_SYN,
			IMX_AUDMUX_V2_PDCR_RXDSEL(पूर्णांक_port));
	अगर (ret) अणु
		dev_err(dev, "audmux external port setup failed\n");
		वापस ret;
	पूर्ण

	ssi_np = of_parse_phandle(pdev->dev.of_node, "ssi-controller", 0);
	codec_np = of_parse_phandle(pdev->dev.of_node, "audio-codec", 0);
	अगर (!ssi_np || !codec_np) अणु
		dev_err(dev, "phandle missing or invalid\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	ssi_pdev = of_find_device_by_node(ssi_np);
	अगर (!ssi_pdev) अणु
		dev_err(dev, "failed to find SSI platform device\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	comp = devm_kzalloc(dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!comp) अणु
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	data->dev = dev;

	data->jack_gpio = of_get_named_gpio(pdev->dev.of_node, "jack-gpio", 0);

	data->dai.cpus		= &comp[0];
	data->dai.codecs	= &comp[1];
	data->dai.platक्रमms	= &comp[2];

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_platक्रमms	= 1;

	data->dai.name = "hifi";
	data->dai.stream_name = "hifi";
	data->dai.codecs->dai_name = "es8328-hifi-analog";
	data->dai.codecs->of_node = codec_np;
	data->dai.cpus->of_node = ssi_np;
	data->dai.platक्रमms->of_node = ssi_np;
	data->dai.init = &imx_es8328_dai_init;
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBM_CFM;

	data->card.dev = dev;
	data->card.dapm_widमाला_लो = imx_es8328_dapm_widमाला_लो;
	data->card.num_dapm_widमाला_लो = ARRAY_SIZE(imx_es8328_dapm_widमाला_लो);
	ret = snd_soc_of_parse_card_name(&data->card, "model");
	अगर (ret) अणु
		dev_err(dev, "Unable to parse card name\n");
		जाओ put_device;
	पूर्ण
	ret = snd_soc_of_parse_audio_routing(&data->card, "audio-routing");
	अगर (ret) अणु
		dev_err(dev, "Unable to parse routing: %d\n", ret);
		जाओ put_device;
	पूर्ण
	data->card.num_links = 1;
	data->card.owner = THIS_MODULE;
	data->card.dai_link = &data->dai;

	ret = snd_soc_रेजिस्टर_card(&data->card);
	अगर (ret) अणु
		dev_err(dev, "Unable to register: %d\n", ret);
		जाओ put_device;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);
put_device:
	put_device(&ssi_pdev->dev);
fail:
	of_node_put(ssi_np);
	of_node_put(codec_np);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_es8328_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_es8328_data *data = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(&data->card);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_es8328_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-audio-es8328", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_es8328_dt_ids);

अटल काष्ठा platक्रमm_driver imx_es8328_driver = अणु
	.driver = अणु
		.name = "imx-es8328",
		.of_match_table = imx_es8328_dt_ids,
	पूर्ण,
	.probe = imx_es8328_probe,
	.हटाओ = imx_es8328_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx_es8328_driver);

MODULE_AUTHOR("Sean Cross <xobs@kosagi.com>");
MODULE_DESCRIPTION("Kosagi i.MX6 ES8328 ASoC machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-audio-es8328");
