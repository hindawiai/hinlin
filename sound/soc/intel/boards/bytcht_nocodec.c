<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  bytcht_nocodec.c - ASoc Machine driver क्रम MinnowBoard Max and Up
 *  to make I2S संकेतs observable on the Low-Speed connector. Audio codec
 *  is not managed by ASoC/DAPM
 *
 *  Copyright (C) 2015-2017 Intel Corp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "../atom/sst-atom-controls.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Mic", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Mic"),
	SOC_DAPM_PIN_SWITCH("Speaker"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,

	अणु"ssp2 Rx", शून्य, "Mic"पूर्ण,
	अणु"Speaker", शून्य, "ssp2 Tx"पूर्ण,
पूर्ण;

अटल पूर्णांक codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret;

	/* The DSP will convert the FE rate to 48k, stereo, 24bits */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	/* set SSP2 to 24-bit */
	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);

	/*
	 * Default mode क्रम SSP configuration is TDM 4 slot, override config
	 * with explicit setting to I2S 2ch 24-bit. The word length is set with
	 * dai_set_tdm_slot() since there is no other API exposed
	 */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0),
				  SND_SOC_DAIFMT_I2S     |
				  SND_SOC_DAIFMT_NB_NF   |
				  SND_SOC_DAIFMT_CBS_CFS);

	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set format to I2S, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2, 24);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set I2S config, err %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक rates_48000[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_48000 = अणु
	.count = ARRAY_SIZE(rates_48000),
	.list  = rates_48000,
पूर्ण;

अटल पूर्णांक aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE,
			&स्थिरraपूर्णांकs_48000);
पूर्ण

अटल काष्ठा snd_soc_ops aअगर1_ops = अणु
	.startup = aअगर1_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp2_port,
	DAILINK_COMP_ARRAY(COMP_CPU("ssp2-port")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link dais[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.ignore_suspend = 1,
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.ignore_suspend = 1,
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* CODEC<->CODEC link */
	/* back ends */
	अणु
		.name = "SSP2-LowSpeed Connector",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBS_CFS,
		.be_hw_params_fixup = codec_fixup,
		.ignore_suspend = 1,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp2_port, dummy, platक्रमm),
	पूर्ण,
पूर्ण;

/* SoC card */
अटल काष्ठा snd_soc_card bytcht_nocodec_card = अणु
	.name = "bytcht-nocodec",
	.owner = THIS_MODULE,
	.dai_link = dais,
	.num_links = ARRAY_SIZE(dais),
	.dapm_widमाला_लो = widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक snd_bytcht_nocodec_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret_val = 0;

	/* रेजिस्टर the soc card */
	bytcht_nocodec_card.dev = &pdev->dev;

	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &bytcht_nocodec_card);

	अगर (ret_val) अणु
		dev_err(&pdev->dev, "devm_snd_soc_register_card failed %d\n",
			ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &bytcht_nocodec_card);
	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_bytcht_nocodec_mc_driver = अणु
	.driver = अणु
		.name = "bytcht_nocodec",
	पूर्ण,
	.probe = snd_bytcht_nocodec_mc_probe,
पूर्ण;
module_platक्रमm_driver(snd_bytcht_nocodec_mc_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail/Cherrytrail Nocodec Machine driver");
MODULE_AUTHOR("Pierre-Louis Bossart <pierre-louis.bossart at linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcht_nocodec");
