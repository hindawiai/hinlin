<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sam9x5_wm8731   --	SoC audio क्रम AT91SAM9X5-based boards
 *			that are using WM8731 as codec.
 *
 *  Copyright (C) 2011 Aपंचांगel,
 *		  Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 *
 *  Copyright (C) 2013 Paratronic,
 *		  Riअक्षरd Genoud <riअक्षरd.genoud@gmail.com>
 *
 * Based on sam9g20_wm8731.c by:
 * Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 */
#समावेश <linux/of.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-dapm.h>

#समावेश "../codecs/wm8731.h"
#समावेश "atmel_ssc_dai.h"


#घोषणा MCLK_RATE 12288000

#घोषणा DRV_NAME "sam9x5-snd-wm8731"

काष्ठा sam9x5_drvdata अणु
	पूर्णांक ssc_id;
पूर्ण;

/*
 * Logic क्रम a wm8731 as connected on a at91sam9x5ek based board.
 */
अटल पूर्णांक sam9x5_wm8731_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा device *dev = rtd->dev;
	पूर्णांक ret;

	dev_dbg(dev, "%s called\n", __func__);

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8731_SYSCLK_XTAL,
				     MCLK_RATE, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set WM8731 SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Audio paths on at91sam9x5ek board:
 *
 *  |A| ------------> |      | ---R----> Headphone Jack
 *  |T| <----\        |  WM  | ---L--/
 *  |9| ---> CLK <--> | 8731 | <--R----- Line In Jack
 *  |1| <------------ |      | <--L--/
 */
अटल स्थिर काष्ठा snd_soc_dapm_widget sam9x5_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In Jack", शून्य),
पूर्ण;

अटल पूर्णांक sam9x5_wm8731_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *codec_np, *cpu_np;
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_dai_link *dai;
	काष्ठा sam9x5_drvdata *priv;
	काष्ठा snd_soc_dai_link_component *comp;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "No device node supplied\n");
		वापस -EINVAL;
	पूर्ण

	card = devm_kzalloc(&pdev->dev, माप(*card), GFP_KERNEL);
	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	dai = devm_kzalloc(&pdev->dev, माप(*dai), GFP_KERNEL);
	comp = devm_kzalloc(&pdev->dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!dai || !card || !priv || !comp) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	snd_soc_card_set_drvdata(card, priv);

	card->dev = &pdev->dev;
	card->owner = THIS_MODULE;
	card->dai_link = dai;
	card->num_links = 1;
	card->dapm_widमाला_लो = sam9x5_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो = ARRAY_SIZE(sam9x5_dapm_widमाला_लो);

	dai->cpus = &comp[0];
	dai->num_cpus = 1;
	dai->codecs = &comp[1];
	dai->num_codecs = 1;
	dai->platक्रमms = &comp[2];
	dai->num_platक्रमms = 1;

	dai->name = "WM8731";
	dai->stream_name = "WM8731 PCM";
	dai->codecs->dai_name = "wm8731-hifi";
	dai->init = sam9x5_wm8731_init;
	dai->dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF
		| SND_SOC_DAIFMT_CBM_CFM;

	ret = snd_soc_of_parse_card_name(card, "atmel,model");
	अगर (ret) अणु
		dev_err(&pdev->dev, "atmel,model node missing\n");
		जाओ out;
	पूर्ण

	ret = snd_soc_of_parse_audio_routing(card, "atmel,audio-routing");
	अगर (ret) अणु
		dev_err(&pdev->dev, "atmel,audio-routing node missing\n");
		जाओ out;
	पूर्ण

	codec_np = of_parse_phandle(np, "atmel,audio-codec", 0);
	अगर (!codec_np) अणु
		dev_err(&pdev->dev, "atmel,audio-codec node missing\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	dai->codecs->of_node = codec_np;

	cpu_np = of_parse_phandle(np, "atmel,ssc-controller", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "atmel,ssc-controller node missing\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	dai->cpus->of_node = cpu_np;
	dai->platक्रमms->of_node = cpu_np;

	priv->ssc_id = of_alias_get_id(cpu_np, "ssc");

	ret = aपंचांगel_ssc_set_audio(priv->ssc_id);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to set SSC %d for audio: %d\n",
			ret, priv->ssc_id);
		जाओ out;
	पूर्ण

	of_node_put(codec_np);
	of_node_put(cpu_np);

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Platform device allocation failed\n");
		जाओ out_put_audio;
	पूर्ण

	dev_dbg(&pdev->dev, "%s ok\n", __func__);

	वापस ret;

out_put_audio:
	aपंचांगel_ssc_put_audio(priv->ssc_id);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sam9x5_wm8731_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा sam9x5_drvdata *priv = card->drvdata;

	snd_soc_unरेजिस्टर_card(card);
	aपंचांगel_ssc_put_audio(priv->ssc_id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sam9x5_wm8731_of_match[] = अणु
	अणु .compatible = "atmel,sam9x5-wm8731-audio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sam9x5_wm8731_of_match);

अटल काष्ठा platक्रमm_driver sam9x5_wm8731_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(sam9x5_wm8731_of_match),
	पूर्ण,
	.probe = sam9x5_wm8731_driver_probe,
	.हटाओ = sam9x5_wm8731_driver_हटाओ,
पूर्ण;
module_platक्रमm_driver(sam9x5_wm8731_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Nicolas Ferre <nicolas.ferre@atmel.com>");
MODULE_AUTHOR("Richard Genoud <richard.genoud@gmail.com>");
MODULE_DESCRIPTION("ALSA SoC machine driver for AT91SAM9x5 - WM8731");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
