<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2013 Freescale Semiconductor, Inc.

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/soc.h>

काष्ठा imx_spdअगर_data अणु
	काष्ठा snd_soc_dai_link dai;
	काष्ठा snd_soc_card card;
पूर्ण;

अटल पूर्णांक imx_spdअगर_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *spdअगर_np, *np = pdev->dev.of_node;
	काष्ठा imx_spdअगर_data *data;
	काष्ठा snd_soc_dai_link_component *comp;
	पूर्णांक ret = 0;

	spdअगर_np = of_parse_phandle(np, "spdif-controller", 0);
	अगर (!spdअगर_np) अणु
		dev_err(&pdev->dev, "failed to find spdif-controller\n");
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	comp = devm_kzalloc(&pdev->dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!data || !comp) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	data->dai.cpus		= &comp[0];
	data->dai.codecs	= &comp[1];
	data->dai.platक्रमms	= &comp[2];

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_platक्रमms	= 1;

	data->dai.name = "S/PDIF PCM";
	data->dai.stream_name = "S/PDIF PCM";
	data->dai.codecs->dai_name = "snd-soc-dummy-dai";
	data->dai.codecs->name = "snd-soc-dummy";
	data->dai.cpus->of_node = spdअगर_np;
	data->dai.platक्रमms->of_node = spdअगर_np;
	data->dai.playback_only = true;
	data->dai.capture_only = true;

	अगर (of_property_पढ़ो_bool(np, "spdif-out"))
		data->dai.capture_only = false;

	अगर (of_property_पढ़ो_bool(np, "spdif-in"))
		data->dai.playback_only = false;

	अगर (data->dai.playback_only && data->dai.capture_only) अणु
		dev_err(&pdev->dev, "no enabled S/PDIF DAI link\n");
		जाओ end;
	पूर्ण

	data->card.dev = &pdev->dev;
	data->card.dai_link = &data->dai;
	data->card.num_links = 1;
	data->card.owner = THIS_MODULE;

	ret = snd_soc_of_parse_card_name(&data->card, "model");
	अगर (ret)
		जाओ end;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &data->card);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card failed: %d\n", ret);

end:
	of_node_put(spdअगर_np);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_spdअगर_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-audio-spdif", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_spdअगर_dt_ids);

अटल काष्ठा platक्रमm_driver imx_spdअगर_driver = अणु
	.driver = अणु
		.name = "imx-spdif",
		.pm = &snd_soc_pm_ops,
		.of_match_table = imx_spdअगर_dt_ids,
	पूर्ण,
	.probe = imx_spdअगर_audio_probe,
पूर्ण;

module_platक्रमm_driver(imx_spdअगर_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Freescale i.MX S/PDIF machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-spdif");
