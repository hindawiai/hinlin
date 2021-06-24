<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * zylonite.c  --  SoC audio क्रम Zylonite
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "../codecs/wm9713.h"
#समावेश "pxa-ssp.h"

/*
 * There is a physical चयन SW15 on the board which changes the MCLK
 * क्रम the WM9713 between the standard AC97 master घड़ी and the
 * output of the CLK_POUT संकेत from the PXA.
 */
अटल पूर्णांक clk_pout;
module_param(clk_pout, पूर्णांक, 0);
MODULE_PARM_DESC(clk_pout, "Use CLK_POUT as WM9713 MCLK (SW15 on board).");

अटल काष्ठा clk *pout;

अटल काष्ठा snd_soc_card zylonite;

अटल स्थिर काष्ठा snd_soc_dapm_widget zylonite_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Microphone", शून्य),
	SND_SOC_DAPM_MIC("Handset Microphone", शून्य),
	SND_SOC_DAPM_SPK("Multiactor", शून्य),
	SND_SOC_DAPM_SPK("Headset Earpiece", शून्य),
पूर्ण;

/* Currently supported audio map */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु

	/* Headphone output connected to HPL/HPR */
	अणु "Headphone", शून्य,  "HPL" पूर्ण,
	अणु "Headphone", शून्य,  "HPR" पूर्ण,

	/* On-board earpiece */
	अणु "Headset Earpiece", शून्य, "OUT3" पूर्ण,

	/* Headphone mic */
	अणु "MIC2A", शून्य, "Mic Bias" पूर्ण,
	अणु "Mic Bias", शून्य, "Headset Microphone" पूर्ण,

	/* On-board mic */
	अणु "MIC1", शून्य, "Mic Bias" पूर्ण,
	अणु "Mic Bias", शून्य, "Handset Microphone" पूर्ण,

	/* Multiactor dअगरferentially connected over SPKL/SPKR */
	अणु "Multiactor", शून्य, "SPKL" पूर्ण,
	अणु "Multiactor", शून्य, "SPKR" पूर्ण,
पूर्ण;

अटल पूर्णांक zylonite_wm9713_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	अगर (clk_pout)
		snd_soc_dai_set_pll(asoc_rtd_to_codec(rtd, 0), 0, 0,
				    clk_get_rate(pout), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक zylonite_voice_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक wm9713_भाग = 0;
	पूर्णांक ret = 0;
	पूर्णांक rate = params_rate(params);

	/* Only support ratios that we can generate neatly from the AC97
	 * based master घड़ी - in particular, this excludes 44.1kHz.
	 * In most applications the voice DAC will be used क्रम telephony
	 * data so multiples of 8kHz will be the common हाल.
	 */
	चयन (rate) अणु
	हाल 8000:
		wm9713_भाग = 12;
		अवरोध;
	हाल 16000:
		wm9713_भाग = 6;
		अवरोध;
	हाल 48000:
		wm9713_भाग = 2;
		अवरोध;
	शेष:
		/* Don't support OSS emulation */
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA_SSP_CLK_AUDIO, 0, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (clk_pout)
		ret = snd_soc_dai_set_clkभाग(codec_dai, WM9713_PCMCLK_PLL_DIV,
					     WM9713_PCMDIV(wm9713_भाग));
	अन्यथा
		ret = snd_soc_dai_set_clkभाग(codec_dai, WM9713_PCMCLK_DIV,
					     WM9713_PCMDIV(wm9713_भाग));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops zylonite_voice_ops = अणु
	.hw_params = zylonite_voice_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9713-codec", "wm9713-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(ac97_aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9713-codec", "wm9713-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(voice,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa-ssp-dai.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9713-codec", "wm9713-voice")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link zylonite_dai[] = अणु
अणु
	.name = "AC97",
	.stream_name = "AC97 HiFi",
	.init = zylonite_wm9713_init,
	SND_SOC_DAILINK_REG(ac97),
पूर्ण,
अणु
	.name = "AC97 Aux",
	.stream_name = "AC97 Aux",
	SND_SOC_DAILINK_REG(ac97_aux),
पूर्ण,
अणु
	.name = "WM9713 Voice",
	.stream_name = "WM9713 Voice",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &zylonite_voice_ops,
	SND_SOC_DAILINK_REG(voice),
पूर्ण,
पूर्ण;

अटल पूर्णांक zylonite_probe(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret;

	अगर (clk_pout) अणु
		pout = clk_get(शून्य, "CLK_POUT");
		अगर (IS_ERR(pout)) अणु
			dev_err(card->dev, "Unable to obtain CLK_POUT: %ld\n",
				PTR_ERR(pout));
			वापस PTR_ERR(pout);
		पूर्ण

		ret = clk_enable(pout);
		अगर (ret != 0) अणु
			dev_err(card->dev, "Unable to enable CLK_POUT: %d\n",
				ret);
			clk_put(pout);
			वापस ret;
		पूर्ण

		dev_dbg(card->dev, "MCLK enabled at %luHz\n",
			clk_get_rate(pout));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zylonite_हटाओ(काष्ठा snd_soc_card *card)
अणु
	अगर (clk_pout) अणु
		clk_disable(pout);
		clk_put(pout);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zylonite_suspend_post(काष्ठा snd_soc_card *card)
अणु
	अगर (clk_pout)
		clk_disable(pout);

	वापस 0;
पूर्ण

अटल पूर्णांक zylonite_resume_pre(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret = 0;

	अगर (clk_pout) अणु
		ret = clk_enable(pout);
		अगर (ret != 0)
			dev_err(card->dev, "Unable to enable CLK_POUT: %d\n",
				ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_card zylonite = अणु
	.name = "Zylonite",
	.owner = THIS_MODULE,
	.probe = &zylonite_probe,
	.हटाओ = &zylonite_हटाओ,
	.suspend_post = &zylonite_suspend_post,
	.resume_pre = &zylonite_resume_pre,
	.dai_link = zylonite_dai,
	.num_links = ARRAY_SIZE(zylonite_dai),

	.dapm_widमाला_लो = zylonite_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(zylonite_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल काष्ठा platक्रमm_device *zylonite_snd_ac97_device;

अटल पूर्णांक __init zylonite_init(व्योम)
अणु
	पूर्णांक ret;

	zylonite_snd_ac97_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!zylonite_snd_ac97_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(zylonite_snd_ac97_device, &zylonite);

	ret = platक्रमm_device_add(zylonite_snd_ac97_device);
	अगर (ret != 0)
		platक्रमm_device_put(zylonite_snd_ac97_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास zylonite_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(zylonite_snd_ac97_device);
पूर्ण

module_init(zylonite_init);
module_निकास(zylonite_निकास);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("ALSA SoC WM9713 Zylonite");
MODULE_LICENSE("GPL");
