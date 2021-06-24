<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  bytcht-da7213.c - ASoc Machine driver क्रम Intel Baytrail and
 *             Cherrytrail-based platक्रमms, with Dialog DA7213 codec
 *
 *  Copyright (C) 2017 Intel Corporation
 *  Author: Pierre-Louis Bossart <pierre-louis.bossart@linux.पूर्णांकel.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/da7213.h"
#समावेश "../atom/sst-atom-controls.h"

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Mic"),
	SOC_DAPM_PIN_SWITCH("Aux In"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Mic", शून्य),
	SND_SOC_DAPM_LINE("Aux In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Headphone Jack", शून्य, "HPL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPR"पूर्ण,

	अणु"AUXL", शून्य, "Aux In"पूर्ण,
	अणु"AUXR", शून्य, "Aux In"पूर्ण,

	/* Assume Mic1 is linked to Headset and Mic2 to on-board mic */
	अणु"MIC1", शून्य, "Headset Mic"पूर्ण,
	अणु"MIC2", शून्य, "Mic"पूर्ण,

	/* SOC-codec link */
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,

	अणु"Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल पूर्णांक codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
		       काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret;
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);

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

अटल पूर्णांक aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल पूर्णांक aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, DA7213_CLKSRC_MCLK,
				     19200000, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		dev_err(codec_dai->dev, "can't set codec sysclk configuration\n");

	ret = snd_soc_dai_set_pll(codec_dai, 0,
			DA7213_SYSCLK_PLL_SRM, 0, DA7213_PLL_FREQ_OUT_98304000);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "failed to start PLL: %d\n", ret);
		वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aअगर1_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_pll(codec_dai, 0,
				  DA7213_SYSCLK_MCLK, 0, 0);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "failed to stop PLL: %d\n", ret);
		वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops aअगर1_ops = अणु
	.startup = aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops ssp2_ops = अणु
	.hw_params = aअगर1_hw_params,
	.hw_मुक्त = aअगर1_hw_मुक्त,

पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp2_port,
	DAILINK_COMP_ARRAY(COMP_CPU("ssp2-port")));
SND_SOC_DAILINK_DEF(ssp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-DLGS7213:00",
				      "da7213-hifi")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link dailink[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
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
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* CODEC<->CODEC link */
	/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBS_CFS,
		.be_hw_params_fixup = codec_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht da7213" /* card name will be 'sof-bytcht da7213' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bytcht-da7213"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card bytcht_da7213_card = अणु
	.name = CARD_NAME,
	.driver_name = DRIVER_NAME,
	.owner = THIS_MODULE,
	.dai_link = dailink,
	.num_links = ARRAY_SIZE(dailink),
	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.dapm_widमाला_लो = dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल अक्षर codec_name[SND_ACPI_I2C_ID_LEN];

अटल पूर्णांक bytcht_da7213_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा acpi_device *adev;
	bool sof_parent;
	पूर्णांक dai_index = 0;
	पूर्णांक ret_val = 0;
	पूर्णांक i;

	mach = pdev->dev.platक्रमm_data;
	card = &bytcht_da7213_card;
	card->dev = &pdev->dev;

	/* fix index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(dailink); i++) अणु
		अगर (!म_भेद(dailink[i].codecs->name, "i2c-DLGS7213:00")) अणु
			dai_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(codec_name, माप(codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		put_device(&adev->dev);
		dailink[dai_index].codecs->name = codec_name;
	पूर्ण

	/* override plaक्रमm name, अगर required */
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(card, platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		bytcht_da7213_card.name = SOF_CARD_NAME;
		bytcht_da7213_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		bytcht_da7213_card.name = CARD_NAME;
		bytcht_da7213_card.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		pdev->dev.driver->pm = &snd_soc_pm_ops;

	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret_val) अणु
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, card);
	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver bytcht_da7213_driver = अणु
	.driver = अणु
		.name = "bytcht_da7213",
	पूर्ण,
	.probe = bytcht_da7213_probe,
पूर्ण;
module_platक्रमm_driver(bytcht_da7213_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail/Cherrytrail+DA7213 Machine driver");
MODULE_AUTHOR("Pierre-Louis Bossart");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcht_da7213");
