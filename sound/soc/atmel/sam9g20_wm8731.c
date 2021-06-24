<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sam9g20_wm8731  --  SoC audio क्रम AT91SAM9G20-based
 * 			ATMEL AT91SAM9G20ek board.
 *
 *  Copyright (C) 2005 SAN People
 *  Copyright (C) 2008 Aपंचांगel
 *
 * Authors: Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 *
 * Based on ati_b1_wm8731.c by:
 * Frank Mandarino <fmandarino@endrelia.com>
 * Copyright 2006 Endrelia Technologies Inc.
 * Based on corgi.c by:
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Copyright 2005 Openedhand Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>

#समावेश <linux/aपंचांगel-ssc.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "../codecs/wm8731.h"
#समावेश "atmel-pcm.h"
#समावेश "atmel_ssc_dai.h"

#घोषणा MCLK_RATE 12000000

/*
 * As shipped the board करोes not have inमाला_दो.  However, it is relatively
 * straightक्रमward to modअगरy the board to hook them up so support is left
 * in the driver.
 */
#अघोषित ENABLE_MIC_INPUT

अटल काष्ठा clk *mclk;

अटल पूर्णांक at91sam9g20ek_set_bias_level(काष्ठा snd_soc_card *card,
					काष्ठा snd_soc_dapm_context *dapm,
					क्रमागत snd_soc_bias_level level)
अणु
	अटल पूर्णांक mclk_on;
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अगर (!mclk_on)
			ret = clk_enable(mclk);
		अगर (ret == 0)
			mclk_on = 1;
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
	हाल SND_SOC_BIAS_STANDBY:
		अगर (mclk_on)
			clk_disable(mclk);
		mclk_on = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget at91sam9g20ek_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु

	/* speaker connected to LHPOUT/RHPOUT */
	अणु"Ext Spk", शून्य, "LHPOUT"पूर्ण,
	अणु"Ext Spk", शून्य, "RHPOUT"पूर्ण,

	/* mic is connected to Mic Jack, with WM8731 Mic Bias */
	अणु"MICIN", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Int Mic"पूर्ण,
पूर्ण;

/*
 * Logic क्रम a wm8731 as connected on a at91sam9g20ek board.
 */
अटल पूर्णांक at91sam9g20ek_wm8731_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा device *dev = rtd->dev;
	पूर्णांक ret;

	dev_dbg(dev, "%s called\n", __func__);

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8731_SYSCLK_MCLK,
				     MCLK_RATE, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set WM8731 SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

#अगर_अघोषित ENABLE_MIC_INPUT
	snd_soc_dapm_nc_pin(&rtd->card->dapm, "Int Mic");
#पूर्ण_अगर

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_CPU("at91rm9200_ssc.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8731.0-001b", "wm8731-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("at91rm9200_ssc.0")));

अटल काष्ठा snd_soc_dai_link at91sam9g20ek_dai = अणु
	.name = "WM8731",
	.stream_name = "WM8731 PCM",
	.init = at91sam9g20ek_wm8731_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_at91sam9g20ek = अणु
	.name = "AT91SAMG20-EK",
	.owner = THIS_MODULE,
	.dai_link = &at91sam9g20ek_dai,
	.num_links = 1,
	.set_bias_level = at91sam9g20ek_set_bias_level,

	.dapm_widमाला_लो = at91sam9g20ek_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(at91sam9g20ek_dapm_widमाला_लो),
	.dapm_routes = पूर्णांकercon,
	.num_dapm_routes = ARRAY_SIZE(पूर्णांकercon),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक at91sam9g20ek_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *codec_np, *cpu_np;
	काष्ठा clk *pllb;
	काष्ठा snd_soc_card *card = &snd_soc_at91sam9g20ek;
	पूर्णांक ret;

	अगर (!np) अणु
		वापस -ENODEV;
	पूर्ण

	ret = aपंचांगel_ssc_set_audio(0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "ssc channel is not valid\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Codec MCLK is supplied by PCK0 - set it up.
	 */
	mclk = clk_get(शून्य, "pck0");
	अगर (IS_ERR(mclk)) अणु
		dev_err(&pdev->dev, "Failed to get MCLK\n");
		ret = PTR_ERR(mclk);
		जाओ err;
	पूर्ण

	pllb = clk_get(शून्य, "pllb");
	अगर (IS_ERR(pllb)) अणु
		dev_err(&pdev->dev, "Failed to get PLLB\n");
		ret = PTR_ERR(pllb);
		जाओ err_mclk;
	पूर्ण
	ret = clk_set_parent(mclk, pllb);
	clk_put(pllb);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to set MCLK parent\n");
		जाओ err_mclk;
	पूर्ण

	clk_set_rate(mclk, MCLK_RATE);

	card->dev = &pdev->dev;

	/* Parse device node info */
	ret = snd_soc_of_parse_card_name(card, "atmel,model");
	अगर (ret)
		जाओ err;

	ret = snd_soc_of_parse_audio_routing(card,
		"atmel,audio-routing");
	अगर (ret)
		जाओ err;

	/* Parse codec info */
	at91sam9g20ek_dai.codecs->name = शून्य;
	codec_np = of_parse_phandle(np, "atmel,audio-codec", 0);
	अगर (!codec_np) अणु
		dev_err(&pdev->dev, "codec info missing\n");
		वापस -EINVAL;
	पूर्ण
	at91sam9g20ek_dai.codecs->of_node = codec_np;

	/* Parse dai and platक्रमm info */
	at91sam9g20ek_dai.cpus->dai_name = शून्य;
	at91sam9g20ek_dai.platक्रमms->name = शून्य;
	cpu_np = of_parse_phandle(np, "atmel,ssc-controller", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "dai and pcm info missing\n");
		वापस -EINVAL;
	पूर्ण
	at91sam9g20ek_dai.cpus->of_node = cpu_np;
	at91sam9g20ek_dai.platक्रमms->of_node = cpu_np;

	of_node_put(codec_np);
	of_node_put(cpu_np);

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed\n");
	पूर्ण

	वापस ret;

err_mclk:
	clk_put(mclk);
	mclk = शून्य;
err:
	aपंचांगel_ssc_put_audio(0);
	वापस ret;
पूर्ण

अटल पूर्णांक at91sam9g20ek_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	clk_disable(mclk);
	mclk = शून्य;
	snd_soc_unरेजिस्टर_card(card);
	aपंचांगel_ssc_put_audio(0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id at91sam9g20ek_wm8731_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9g20ek-wm8731-audio", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91sam9g20ek_wm8731_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver at91sam9g20ek_audio_driver = अणु
	.driver = अणु
		.name	= "at91sam9g20ek-audio",
		.of_match_table = of_match_ptr(at91sam9g20ek_wm8731_dt_ids),
	पूर्ण,
	.probe	= at91sam9g20ek_audio_probe,
	.हटाओ	= at91sam9g20ek_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(at91sam9g20ek_audio_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Sedji Gaouaou <sedji.gaouaou@atmel.com>");
MODULE_DESCRIPTION("ALSA SoC AT91SAM9G20EK_WM8731");
MODULE_ALIAS("platform:at91sam9g20ek-audio");
MODULE_LICENSE("GPL");
