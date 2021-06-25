<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2017-2020 NXP

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/hdmi-codec.h>
#समावेश "fsl_sai.h"

/**
 * काष्ठा cpu_priv - CPU निजी data
 * @sysclk_id: SYSCLK ids क्रम set_sysclk()
 * @slot_width: Slot width of each frame
 *
 * Note: [1] क्रम tx and [0] क्रम rx
 */
काष्ठा cpu_priv अणु
	u32 sysclk_id[2];
	u32 slot_width;
पूर्ण;

काष्ठा imx_hdmi_data अणु
	काष्ठा snd_soc_dai_link dai;
	काष्ठा snd_soc_card card;
	काष्ठा snd_soc_jack hdmi_jack;
	काष्ठा snd_soc_jack_pin hdmi_jack_pin;
	काष्ठा cpu_priv cpu_priv;
	u32 dai_fmt;
पूर्ण;

अटल पूर्णांक imx_hdmi_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा imx_hdmi_data *data = snd_soc_card_get_drvdata(rtd->card);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा device *dev = card->dev;
	u32 slot_width = data->cpu_priv.slot_width;
	पूर्णांक ret;

	/* MCLK always is (256 or 192) * rate. */
	ret = snd_soc_dai_set_sysclk(cpu_dai, data->cpu_priv.sysclk_id[tx],
				     8 * slot_width * params_rate(params),
				     tx ? SND_SOC_CLOCK_OUT : SND_SOC_CLOCK_IN);
	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(dev, "failed to set cpu sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_tdm_slot(cpu_dai, 0, 0, 2, slot_width);
	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(dev, "failed to set cpu dai tdm slot: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops imx_hdmi_ops = अणु
	.hw_params = imx_hdmi_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget imx_hdmi_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("HDMI Jack", शून्य),
पूर्ण;

अटल पूर्णांक imx_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा imx_hdmi_data *data = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	data->hdmi_jack_pin.pin = "HDMI Jack";
	data->hdmi_jack_pin.mask = SND_JACK_LINEOUT;
	/* enable jack detection */
	ret = snd_soc_card_jack_new(card, "HDMI Jack", SND_JACK_LINEOUT,
				    &data->hdmi_jack, &data->hdmi_jack_pin, 1);
	अगर (ret) अणु
		dev_err(card->dev, "Can't new HDMI Jack %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_jack(component, &data->hdmi_jack, शून्य);
	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(card->dev, "Can't set HDMI Jack %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक imx_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	bool hdmi_out = of_property_पढ़ो_bool(np, "hdmi-out");
	bool hdmi_in = of_property_पढ़ो_bool(np, "hdmi-in");
	काष्ठा snd_soc_dai_link_component *dlc;
	काष्ठा platक्रमm_device *cpu_pdev;
	काष्ठा device_node *cpu_np;
	काष्ठा imx_hdmi_data *data;
	पूर्णांक ret;

	dlc = devm_kzalloc(&pdev->dev, 3 * माप(*dlc), GFP_KERNEL);
	अगर (!dlc)
		वापस -ENOMEM;

	cpu_np = of_parse_phandle(np, "audio-cpu", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "cpu dai phandle missing or invalid\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	cpu_pdev = of_find_device_by_node(cpu_np);
	अगर (!cpu_pdev) अणु
		dev_err(&pdev->dev, "failed to find SAI platform device\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	data->dai.cpus = &dlc[0];
	data->dai.num_cpus = 1;
	data->dai.platक्रमms = &dlc[1];
	data->dai.num_platक्रमms = 1;
	data->dai.codecs = &dlc[2];
	data->dai.num_codecs = 1;

	data->dai.name = "i.MX HDMI";
	data->dai.stream_name = "i.MX HDMI";
	data->dai.cpus->dai_name = dev_name(&cpu_pdev->dev);
	data->dai.platक्रमms->of_node = cpu_np;
	data->dai.ops = &imx_hdmi_ops;
	data->dai.playback_only = true;
	data->dai.capture_only = false;
	data->dai.init = imx_hdmi_init;

	अगर (of_node_name_eq(cpu_np, "sai")) अणु
		data->cpu_priv.sysclk_id[1] = FSL_SAI_CLK_MAST1;
		data->cpu_priv.sysclk_id[0] = FSL_SAI_CLK_MAST1;
	पूर्ण

	अगर (of_device_is_compatible(np, "fsl,imx-audio-sii902x")) अणु
		data->dai_fmt = SND_SOC_DAIFMT_LEFT_J;
		data->cpu_priv.slot_width = 24;
	पूर्ण अन्यथा अणु
		data->dai_fmt = SND_SOC_DAIFMT_I2S;
		data->cpu_priv.slot_width = 32;
	पूर्ण

	अगर ((hdmi_out && hdmi_in) || (!hdmi_out && !hdmi_in)) अणु
		dev_err(&pdev->dev, "Invalid HDMI DAI link\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (hdmi_out) अणु
		data->dai.playback_only = true;
		data->dai.capture_only = false;
		data->dai.codecs->dai_name = "i2s-hifi";
		data->dai.codecs->name = "hdmi-audio-codec.1";
		data->dai.dai_fmt = data->dai_fmt |
				    SND_SOC_DAIFMT_NB_NF |
				    SND_SOC_DAIFMT_CBS_CFS;
	पूर्ण

	अगर (hdmi_in) अणु
		data->dai.playback_only = false;
		data->dai.capture_only = true;
		data->dai.codecs->dai_name = "i2s-hifi";
		data->dai.codecs->name = "hdmi-audio-codec.2";
		data->dai.dai_fmt = data->dai_fmt |
				    SND_SOC_DAIFMT_NB_NF |
				    SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण

	data->card.dapm_widमाला_लो = imx_hdmi_widमाला_लो;
	data->card.num_dapm_widमाला_लो = ARRAY_SIZE(imx_hdmi_widमाला_लो);
	data->card.dev = &pdev->dev;
	data->card.owner = THIS_MODULE;
	ret = snd_soc_of_parse_card_name(&data->card, "model");
	अगर (ret)
		जाओ fail;

	data->card.num_links = 1;
	data->card.dai_link = &data->dai;

	snd_soc_card_set_drvdata(&data->card, data);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &data->card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		जाओ fail;
	पूर्ण

fail:
	अगर (cpu_np)
		of_node_put(cpu_np);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_hdmi_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-audio-hdmi", पूर्ण,
	अणु .compatible = "fsl,imx-audio-sii902x", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_hdmi_dt_ids);

अटल काष्ठा platक्रमm_driver imx_hdmi_driver = अणु
	.driver = अणु
		.name = "imx-hdmi",
		.pm = &snd_soc_pm_ops,
		.of_match_table = imx_hdmi_dt_ids,
	पूर्ण,
	.probe = imx_hdmi_probe,
पूर्ण;
module_platक्रमm_driver(imx_hdmi_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Freescale i.MX hdmi audio ASoC machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-hdmi");
