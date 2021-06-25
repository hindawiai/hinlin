<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2012 Freescale Semiconductor, Inc.
// Copyright 2012 Linaro Ltd.

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <sound/soc.h>

#समावेश "../codecs/sgtl5000.h"
#समावेश "imx-audmux.h"

#घोषणा DAI_NAME_SIZE	32

काष्ठा imx_sgtl5000_data अणु
	काष्ठा snd_soc_dai_link dai;
	काष्ठा snd_soc_card card;
	अक्षर codec_dai_name[DAI_NAME_SIZE];
	अक्षर platक्रमm_name[DAI_NAME_SIZE];
	काष्ठा clk *codec_clk;
	अचिन्हित पूर्णांक clk_frequency;
पूर्ण;

अटल पूर्णांक imx_sgtl5000_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा imx_sgtl5000_data *data = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा device *dev = rtd->card->dev;
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_codec(rtd, 0), SGTL5000_SYSCLK,
				     data->clk_frequency, SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(dev, "could not set codec driver clock params\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget imx_sgtl5000_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In Jack", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Line Out Jack", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
पूर्ण;

अटल पूर्णांक imx_sgtl5000_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *ssi_np, *codec_np;
	काष्ठा platक्रमm_device *ssi_pdev;
	काष्ठा i2c_client *codec_dev;
	काष्ठा imx_sgtl5000_data *data = शून्य;
	काष्ठा snd_soc_dai_link_component *comp;
	पूर्णांक पूर्णांक_port, ext_port;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "mux-int-port", &पूर्णांक_port);
	अगर (ret) अणु
		dev_err(&pdev->dev, "mux-int-port missing or invalid\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "mux-ext-port", &ext_port);
	अगर (ret) अणु
		dev_err(&pdev->dev, "mux-ext-port missing or invalid\n");
		वापस ret;
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
		dev_err(&pdev->dev, "audmux internal port setup failed\n");
		वापस ret;
	पूर्ण
	ret = imx_audmux_v2_configure_port(ext_port,
			IMX_AUDMUX_V2_PTCR_SYN,
			IMX_AUDMUX_V2_PDCR_RXDSEL(पूर्णांक_port));
	अगर (ret) अणु
		dev_err(&pdev->dev, "audmux external port setup failed\n");
		वापस ret;
	पूर्ण

	ssi_np = of_parse_phandle(pdev->dev.of_node, "ssi-controller", 0);
	codec_np = of_parse_phandle(pdev->dev.of_node, "audio-codec", 0);
	अगर (!ssi_np || !codec_np) अणु
		dev_err(&pdev->dev, "phandle missing or invalid\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	ssi_pdev = of_find_device_by_node(ssi_np);
	अगर (!ssi_pdev) अणु
		dev_dbg(&pdev->dev, "failed to find SSI platform device\n");
		ret = -EPROBE_DEFER;
		जाओ fail;
	पूर्ण
	put_device(&ssi_pdev->dev);
	codec_dev = of_find_i2c_device_by_node(codec_np);
	अगर (!codec_dev) अणु
		dev_dbg(&pdev->dev, "failed to find codec platform device\n");
		ret = -EPROBE_DEFER;
		जाओ fail;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	comp = devm_kzalloc(&pdev->dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!comp) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	data->codec_clk = clk_get(&codec_dev->dev, शून्य);
	अगर (IS_ERR(data->codec_clk)) अणु
		ret = PTR_ERR(data->codec_clk);
		जाओ fail;
	पूर्ण

	data->clk_frequency = clk_get_rate(data->codec_clk);

	data->dai.cpus		= &comp[0];
	data->dai.codecs	= &comp[1];
	data->dai.platक्रमms	= &comp[2];

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_platक्रमms	= 1;

	data->dai.name = "HiFi";
	data->dai.stream_name = "HiFi";
	data->dai.codecs->dai_name = "sgtl5000";
	data->dai.codecs->of_node = codec_np;
	data->dai.cpus->of_node = ssi_np;
	data->dai.platक्रमms->of_node = ssi_np;
	data->dai.init = &imx_sgtl5000_dai_init;
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBM_CFM;

	data->card.dev = &pdev->dev;
	ret = snd_soc_of_parse_card_name(&data->card, "model");
	अगर (ret)
		जाओ fail;
	ret = snd_soc_of_parse_audio_routing(&data->card, "audio-routing");
	अगर (ret)
		जाओ fail;
	data->card.num_links = 1;
	data->card.owner = THIS_MODULE;
	data->card.dai_link = &data->dai;
	data->card.dapm_widमाला_लो = imx_sgtl5000_dapm_widमाला_लो;
	data->card.num_dapm_widमाला_लो = ARRAY_SIZE(imx_sgtl5000_dapm_widमाला_लो);

	platक्रमm_set_drvdata(pdev, &data->card);
	snd_soc_card_set_drvdata(&data->card, data);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &data->card);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
				ret);
		जाओ fail;
	पूर्ण

	of_node_put(ssi_np);
	of_node_put(codec_np);

	वापस 0;

fail:
	अगर (data && !IS_ERR(data->codec_clk))
		clk_put(data->codec_clk);
	of_node_put(ssi_np);
	of_node_put(codec_np);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_sgtl5000_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा imx_sgtl5000_data *data = snd_soc_card_get_drvdata(card);

	clk_put(data->codec_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_sgtl5000_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-audio-sgtl5000", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_sgtl5000_dt_ids);

अटल काष्ठा platक्रमm_driver imx_sgtl5000_driver = अणु
	.driver = अणु
		.name = "imx-sgtl5000",
		.pm = &snd_soc_pm_ops,
		.of_match_table = imx_sgtl5000_dt_ids,
	पूर्ण,
	.probe = imx_sgtl5000_probe,
	.हटाओ = imx_sgtl5000_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx_sgtl5000_driver);

MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("Freescale i.MX SGTL5000 ASoC machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-sgtl5000");
