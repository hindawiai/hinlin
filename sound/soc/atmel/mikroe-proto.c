<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ASoC driver क्रम PROTO AudioCODEC (with a WM8731)
 *
 * Author:      Florian Meier, <koalo@koalo.de>
 *	      Copyright 2013
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "../codecs/wm8731.h"

#घोषणा XTAL_RATE 12288000	/* This is fixed on this board */

अटल पूर्णांक snd_proto_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	/* Set proto sysclk */
	पूर्णांक ret = snd_soc_dai_set_sysclk(codec_dai, WM8731_SYSCLK_XTAL,
					 XTAL_RATE, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(card->dev, "Failed to set WM8731 SYSCLK: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget snd_proto_widget[] = अणु
	SND_SOC_DAPM_MIC("Microphone Jack", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route snd_proto_route[] = अणु
	/* speaker connected to LHPOUT/RHPOUT */
	अणु"Headphone Jack", शून्य, "LHPOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "RHPOUT"पूर्ण,

	/* mic is connected to Mic Jack, with WM8731 Mic Bias */
	अणु"MICIN", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Microphone Jack"पूर्ण,
पूर्ण;

/* audio machine driver */
अटल काष्ठा snd_soc_card snd_proto = अणु
	.name		= "snd_mikroe_proto",
	.owner		= THIS_MODULE,
	.dapm_widमाला_लो	= snd_proto_widget,
	.num_dapm_widमाला_लो = ARRAY_SIZE(snd_proto_widget),
	.dapm_routes	= snd_proto_route,
	.num_dapm_routes = ARRAY_SIZE(snd_proto_route),
पूर्ण;

अटल पूर्णांक snd_proto_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_dai_link *dai;
	काष्ठा snd_soc_dai_link_component *comp;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *codec_np, *cpu_np;
	काष्ठा device_node *bitclkmaster = शून्य;
	काष्ठा device_node *framemaster = शून्य;
	अचिन्हित पूर्णांक dai_fmt;
	पूर्णांक ret = 0;

	अगर (!np) अणु
		dev_err(&pdev->dev, "No device node supplied\n");
		वापस -EINVAL;
	पूर्ण

	snd_proto.dev = &pdev->dev;
	ret = snd_soc_of_parse_card_name(&snd_proto, "model");
	अगर (ret)
		वापस ret;

	dai = devm_kzalloc(&pdev->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	/* क्रम cpus/codecs/platक्रमms */
	comp = devm_kzalloc(&pdev->dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!comp)
		वापस -ENOMEM;

	snd_proto.dai_link = dai;
	snd_proto.num_links = 1;

	dai->cpus = &comp[0];
	dai->num_cpus = 1;
	dai->codecs = &comp[1];
	dai->num_codecs = 1;
	dai->platक्रमms = &comp[2];
	dai->num_platक्रमms = 1;

	dai->name = "WM8731";
	dai->stream_name = "WM8731 HiFi";
	dai->codecs->dai_name = "wm8731-hifi";
	dai->init = &snd_proto_init;

	codec_np = of_parse_phandle(np, "audio-codec", 0);
	अगर (!codec_np) अणु
		dev_err(&pdev->dev, "audio-codec node missing\n");
		वापस -EINVAL;
	पूर्ण
	dai->codecs->of_node = codec_np;

	cpu_np = of_parse_phandle(np, "i2s-controller", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "i2s-controller missing\n");
		वापस -EINVAL;
	पूर्ण
	dai->cpus->of_node = cpu_np;
	dai->platक्रमms->of_node = cpu_np;

	dai_fmt = snd_soc_of_parse_daअगरmt(np, शून्य,
					  &bitclkmaster, &framemaster);
	अगर (bitclkmaster != framemaster) अणु
		dev_err(&pdev->dev, "Must be the same bitclock and frame master\n");
		वापस -EINVAL;
	पूर्ण
	अगर (bitclkmaster) अणु
		dai_fmt &= ~SND_SOC_DAIFMT_MASTER_MASK;
		अगर (codec_np == bitclkmaster)
			dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
		अन्यथा
			dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
	पूर्ण
	of_node_put(bitclkmaster);
	of_node_put(framemaster);
	dai->dai_fmt = dai_fmt;

	of_node_put(codec_np);
	of_node_put(cpu_np);

	ret = snd_soc_रेजिस्टर_card(&snd_proto);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev,
			"snd_soc_register_card() failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_proto_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस snd_soc_unरेजिस्टर_card(&snd_proto);
पूर्ण

अटल स्थिर काष्ठा of_device_id snd_proto_of_match[] = अणु
	अणु .compatible = "mikroe,mikroe-proto", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, snd_proto_of_match);

अटल काष्ठा platक्रमm_driver snd_proto_driver = अणु
	.driver = अणु
		.name   = "snd-mikroe-proto",
		.of_match_table = snd_proto_of_match,
	पूर्ण,
	.probe	  = snd_proto_probe,
	.हटाओ	 = snd_proto_हटाओ,
पूर्ण;

module_platक्रमm_driver(snd_proto_driver);

MODULE_AUTHOR("Florian Meier");
MODULE_DESCRIPTION("ASoC Driver for PROTO board (WM8731)");
MODULE_LICENSE("GPL");
