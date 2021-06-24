<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc-dapm.h>

#समावेश "../codecs/sgtl5000.h"
#समावेश "mxs-saif.h"

अटल पूर्णांक mxs_sgtl5000_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक rate = params_rate(params);
	u32 mclk;
	पूर्णांक ret;

	/* sgtl5000 करोes not support 512*rate when in 96000 fs */
	चयन (rate) अणु
	हाल 96000:
		mclk = 256 * rate;
		अवरोध;
	शेष:
		mclk = 512 * rate;
		अवरोध;
	पूर्ण

	/* Set SGTL5000's SYSCLK (provided by SAIF MCLK) */
	ret = snd_soc_dai_set_sysclk(codec_dai, SGTL5000_SYSCLK, mclk, 0);
	अगर (ret) अणु
		dev_err(codec_dai->dev, "Failed to set sysclk to %u.%03uMHz\n",
			mclk / 1000000, mclk / 1000 % 1000);
		वापस ret;
	पूर्ण

	/* The SAIF MCLK should be the same as SGTL5000_SYSCLK */
	ret = snd_soc_dai_set_sysclk(cpu_dai, MXS_SAIF_MCLK, mclk, 0);
	अगर (ret) अणु
		dev_err(cpu_dai->dev, "Failed to set sysclk to %u.%03uMHz\n",
			mclk / 1000000, mclk / 1000 % 1000);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mxs_sgtl5000_hअगरi_ops = अणु
	.hw_params = mxs_sgtl5000_hw_params,
पूर्ण;

#घोषणा MXS_SGTL5000_DAI_FMT (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | \
	SND_SOC_DAIFMT_CBS_CFS)


SND_SOC_DAILINK_DEFS(hअगरi_tx,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "sgtl5000")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hअगरi_rx,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "sgtl5000")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link mxs_sgtl5000_dai[] = अणु
	अणु
		.name		= "HiFi Tx",
		.stream_name	= "HiFi Playback",
		.dai_fmt	= MXS_SGTL5000_DAI_FMT,
		.ops		= &mxs_sgtl5000_hअगरi_ops,
		.playback_only	= true,
		SND_SOC_DAILINK_REG(hअगरi_tx),
	पूर्ण, अणु
		.name		= "HiFi Rx",
		.stream_name	= "HiFi Capture",
		.dai_fmt	= MXS_SGTL5000_DAI_FMT,
		.ops		= &mxs_sgtl5000_hअगरi_ops,
		.capture_only	= true,
		SND_SOC_DAILINK_REG(hअगरi_rx),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mxs_sgtl5000_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In Jack", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Line Out Jack", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
पूर्ण;

अटल काष्ठा snd_soc_card mxs_sgtl5000 = अणु
	.name		= "mxs_sgtl5000",
	.owner		= THIS_MODULE,
	.dai_link	= mxs_sgtl5000_dai,
	.num_links	= ARRAY_SIZE(mxs_sgtl5000_dai),
पूर्ण;

अटल पूर्णांक mxs_sgtl5000_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mxs_sgtl5000;
	पूर्णांक ret, i;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *saअगर_np[2], *codec_np;

	saअगर_np[0] = of_parse_phandle(np, "saif-controllers", 0);
	saअगर_np[1] = of_parse_phandle(np, "saif-controllers", 1);
	codec_np = of_parse_phandle(np, "audio-codec", 0);
	अगर (!saअगर_np[0] || !saअगर_np[1] || !codec_np) अणु
		dev_err(&pdev->dev, "phandle missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		mxs_sgtl5000_dai[i].codecs->name = शून्य;
		mxs_sgtl5000_dai[i].codecs->of_node = codec_np;
		mxs_sgtl5000_dai[i].cpus->dai_name = शून्य;
		mxs_sgtl5000_dai[i].cpus->of_node = saअगर_np[i];
		mxs_sgtl5000_dai[i].platक्रमms->name = शून्य;
		mxs_sgtl5000_dai[i].platक्रमms->of_node = saअगर_np[i];
	पूर्ण

	of_node_put(codec_np);
	of_node_put(saअगर_np[0]);
	of_node_put(saअगर_np[1]);

	/*
	 * Set an init घड़ी(11.28Mhz) क्रम sgtl5000 initialization(i2c r/w).
	 * The Sgtl5000 sysclk is derived from saअगर0 mclk and it's range
	 * should be >= 8MHz and <= 27M.
	 */
	ret = mxs_saअगर_get_mclk(0, 44100 * 256, 44100);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get mclk\n");
		वापस ret;
	पूर्ण

	card->dev = &pdev->dev;

	अगर (of_find_property(np, "audio-routing", शून्य)) अणु
		card->dapm_widमाला_लो = mxs_sgtl5000_dapm_widमाला_लो;
		card->num_dapm_widमाला_लो = ARRAY_SIZE(mxs_sgtl5000_dapm_widमाला_लो);

		ret = snd_soc_of_parse_audio_routing(card, "audio-routing");
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to parse audio-routing (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_sgtl5000_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	mxs_saअगर_put_mclk(0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxs_sgtl5000_dt_ids[] = अणु
	अणु .compatible = "fsl,mxs-audio-sgtl5000", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_sgtl5000_dt_ids);

अटल काष्ठा platक्रमm_driver mxs_sgtl5000_audio_driver = अणु
	.driver = अणु
		.name = "mxs-sgtl5000",
		.of_match_table = mxs_sgtl5000_dt_ids,
	पूर्ण,
	.probe = mxs_sgtl5000_probe,
	.हटाओ = mxs_sgtl5000_हटाओ,
पूर्ण;

module_platक्रमm_driver(mxs_sgtl5000_audio_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MXS ALSA SoC Machine driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-sgtl5000");
