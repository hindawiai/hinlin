<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017-2020 NXP

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/i2c.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश "imx-pcm-rpmsg.h"

काष्ठा imx_rpmsg अणु
	काष्ठा snd_soc_dai_link dai;
	काष्ठा snd_soc_card card;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget imx_rpmsg_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("Main MIC", शून्य),
पूर्ण;

अटल पूर्णांक imx_rpmsg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_dai_link_component *dlc;
	काष्ठा device *dev = pdev->dev.parent;
	/* rpmsg_pdev is the platक्रमm device क्रम the rpmsg node that probed us */
	काष्ठा platक्रमm_device *rpmsg_pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = rpmsg_pdev->dev.of_node;
	काष्ठा of_phandle_args args;
	काष्ठा imx_rpmsg *data;
	पूर्णांक ret = 0;

	dlc = devm_kzalloc(&pdev->dev, 3 * माप(*dlc), GFP_KERNEL);
	अगर (!dlc)
		वापस -ENOMEM;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ret = of_reserved_mem_device_init_by_idx(&pdev->dev, np, 0);
	अगर (ret)
		dev_warn(&pdev->dev, "no reserved DMA memory\n");

	data->dai.cpus = &dlc[0];
	data->dai.num_cpus = 1;
	data->dai.platक्रमms = &dlc[1];
	data->dai.num_platक्रमms = 1;
	data->dai.codecs = &dlc[2];
	data->dai.num_codecs = 1;

	data->dai.name = "rpmsg hifi";
	data->dai.stream_name = "rpmsg hifi";
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S |
			    SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBS_CFS;

	/* Optional codec node */
	ret = of_parse_phandle_with_fixed_args(np, "audio-codec", 0, 0, &args);
	अगर (ret) अणु
		data->dai.codecs->dai_name = "snd-soc-dummy-dai";
		data->dai.codecs->name = "snd-soc-dummy";
	पूर्ण अन्यथा अणु
		data->dai.codecs->of_node = args.np;
		ret = snd_soc_get_dai_name(&args, &data->dai.codecs->dai_name);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Unable to get codec_dai_name\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	data->dai.cpus->dai_name = dev_name(&rpmsg_pdev->dev);
	data->dai.platक्रमms->name = IMX_PCM_DRV_NAME;
	data->dai.playback_only = true;
	data->dai.capture_only = true;
	data->card.num_links = 1;
	data->card.dai_link = &data->dai;

	अगर (of_property_पढ़ो_bool(np, "fsl,rpmsg-out"))
		data->dai.capture_only = false;

	अगर (of_property_पढ़ो_bool(np, "fsl,rpmsg-in"))
		data->dai.playback_only = false;

	अगर (data->dai.playback_only && data->dai.capture_only) अणु
		dev_err(&pdev->dev, "no enabled rpmsg DAI link\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	data->card.dev = &pdev->dev;
	data->card.owner = THIS_MODULE;
	data->card.dapm_widमाला_लो = imx_rpmsg_dapm_widमाला_लो;
	data->card.num_dapm_widमाला_लो = ARRAY_SIZE(imx_rpmsg_dapm_widमाला_लो);
	/*
	 * Inoder to use common api to get card name and audio routing.
	 * Use parent of_node क्रम this device, revert it after finishing using
	 */
	data->card.dev->of_node = np;

	ret = snd_soc_of_parse_card_name(&data->card, "model");
	अगर (ret)
		जाओ fail;

	अगर (of_property_पढ़ो_bool(np, "audio-routing")) अणु
		ret = snd_soc_of_parse_audio_routing(&data->card, "audio-routing");
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to parse audio-routing: %d\n", ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, &data->card);
	snd_soc_card_set_drvdata(&data->card, data);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &data->card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		जाओ fail;
	पूर्ण

fail:
	pdev->dev.of_node = शून्य;
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_rpmsg_driver = अणु
	.driver = अणु
		.name = "imx-audio-rpmsg",
		.owner = THIS_MODULE,
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = imx_rpmsg_probe,
पूर्ण;
module_platक्रमm_driver(imx_rpmsg_driver);

MODULE_DESCRIPTION("Freescale SoC Audio RPMSG Machine Driver");
MODULE_AUTHOR("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODULE_ALIAS("platform:imx-audio-rpmsg");
MODULE_LICENSE("GPL v2");
