<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * aपंचांगel_wm8904 - Aपंचांगel ASoC driver क्रम boards with WM8904 codec.
 *
 * Copyright (C) 2012 Aपंचांगel
 *
 * Author: Bo Shen <voice.shen@aपंचांगel.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <sound/soc.h>

#समावेश "../codecs/wm8904.h"
#समावेश "atmel_ssc_dai.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget aपंचांगel_asoc_wm8904_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic", शून्य),
	SND_SOC_DAPM_LINE("Line In Jack", शून्य),
पूर्ण;

अटल पूर्णांक aपंचांगel_asoc_wm8904_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_pll(codec_dai, WM8904_FLL_MCLK, WM8904_FLL_MCLK,
		32768, params_rate(params) * 256);
	अगर (ret < 0) अणु
		pr_err("%s - failed to set wm8904 codec PLL.", __func__);
		वापस ret;
	पूर्ण

	/*
	 * As here wm8904 use FLL output as its प्रणाली घड़ी
	 * so calling set_sysclk won't care freq parameter
	 * then we pass 0
	 */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8904_CLK_FLL,
			0, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		pr_err("%s -failed to set wm8904 SYSCLK\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops aपंचांगel_asoc_wm8904_ops = अणु
	.hw_params = aपंचांगel_asoc_wm8904_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8904-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link aपंचांगel_asoc_wm8904_dailink = अणु
	.name = "WM8904",
	.stream_name = "WM8904 PCM",
	.dai_fmt = SND_SOC_DAIFMT_I2S
		| SND_SOC_DAIFMT_NB_NF
		| SND_SOC_DAIFMT_CBM_CFM,
	.ops = &aपंचांगel_asoc_wm8904_ops,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card aपंचांगel_asoc_wm8904_card = अणु
	.name = "atmel_asoc_wm8904",
	.owner = THIS_MODULE,
	.dai_link = &aपंचांगel_asoc_wm8904_dailink,
	.num_links = 1,
	.dapm_widमाला_लो = aपंचांगel_asoc_wm8904_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(aपंचांगel_asoc_wm8904_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक aपंचांगel_asoc_wm8904_dt_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *codec_np, *cpu_np;
	काष्ठा snd_soc_card *card = &aपंचांगel_asoc_wm8904_card;
	काष्ठा snd_soc_dai_link *dailink = &aपंचांगel_asoc_wm8904_dailink;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "only device tree supported\n");
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_of_parse_card_name(card, "atmel,model");
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse card name\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_of_parse_audio_routing(card, "atmel,audio-routing");
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse audio routing\n");
		वापस ret;
	पूर्ण

	cpu_np = of_parse_phandle(np, "atmel,ssc-controller", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "failed to get dai and pcm info\n");
		ret = -EINVAL;
		वापस ret;
	पूर्ण
	dailink->cpus->of_node = cpu_np;
	dailink->platक्रमms->of_node = cpu_np;
	of_node_put(cpu_np);

	codec_np = of_parse_phandle(np, "atmel,audio-codec", 0);
	अगर (!codec_np) अणु
		dev_err(&pdev->dev, "failed to get codec info\n");
		ret = -EINVAL;
		वापस ret;
	पूर्ण
	dailink->codecs->of_node = codec_np;
	of_node_put(codec_np);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_asoc_wm8904_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &aपंचांगel_asoc_wm8904_card;
	काष्ठा snd_soc_dai_link *dailink = &aपंचांगel_asoc_wm8904_dailink;
	पूर्णांक id, ret;

	card->dev = &pdev->dev;
	ret = aपंचांगel_asoc_wm8904_dt_init(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init dt info\n");
		वापस ret;
	पूर्ण

	id = of_alias_get_id((काष्ठा device_node *)dailink->cpus->of_node, "ssc");
	ret = aपंचांगel_ssc_set_audio(id);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "failed to set SSC %d for audio\n", id);
		वापस ret;
	पूर्ण

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card failed\n");
		जाओ err_set_audio;
	पूर्ण

	वापस 0;

err_set_audio:
	aपंचांगel_ssc_put_audio(id);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_asoc_wm8904_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा snd_soc_dai_link *dailink = &aपंचांगel_asoc_wm8904_dailink;
	पूर्णांक id;

	id = of_alias_get_id((काष्ठा device_node *)dailink->cpus->of_node, "ssc");

	snd_soc_unरेजिस्टर_card(card);
	aपंचांगel_ssc_put_audio(id);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id aपंचांगel_asoc_wm8904_dt_ids[] = अणु
	अणु .compatible = "atmel,asoc-wm8904", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_asoc_wm8904_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver aपंचांगel_asoc_wm8904_driver = अणु
	.driver = अणु
		.name = "atmel-wm8904-audio",
		.of_match_table = of_match_ptr(aपंचांगel_asoc_wm8904_dt_ids),
		.pm		= &snd_soc_pm_ops,
	पूर्ण,
	.probe = aपंचांगel_asoc_wm8904_probe,
	.हटाओ = aपंचांगel_asoc_wm8904_हटाओ,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_asoc_wm8904_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Bo Shen <voice.shen@atmel.com>");
MODULE_DESCRIPTION("ALSA SoC machine driver for Atmel EK with WM8904 codec");
MODULE_LICENSE("GPL");
