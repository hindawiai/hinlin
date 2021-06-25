<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// ASoC DPCM Machine driver क्रम Baytrail / Cherrytrail platक्रमms with
// CX2072X codec
//

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/cx2072x.h"
#समावेश "../atom/sst-atom-controls.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget byt_cht_cx2072x_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_cht_cx2072x_audio_map[] = अणु
	/* External Speakers: HFL, HFR */
	अणु"Headphone", शून्य, "PORTA"पूर्ण,
	अणु"Ext Spk", शून्य, "PORTG"पूर्ण,
	अणु"PORTC", शून्य, "Int Mic"पूर्ण,
	अणु"PORTD", शून्य, "Headset Mic"पूर्ण,

	अणु"Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new byt_cht_cx2072x_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
पूर्ण;

अटल काष्ठा snd_soc_jack byt_cht_cx2072x_headset;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin byt_cht_cx2072x_headset_pins[] = अणु
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params byt_cht_cx2072x_headset_gpios;
अटल स्थिर काष्ठा acpi_gpio_mapping byt_cht_cx2072x_acpi_gpios[] = अणु
	अणु "headset-gpios", &byt_cht_cx2072x_headset_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक byt_cht_cx2072x_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_component *codec = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक ret;

	अगर (devm_acpi_dev_add_driver_gpios(codec->dev,
					   byt_cht_cx2072x_acpi_gpios))
		dev_warn(rtd->dev, "Unable to add GPIO mapping table\n");

	card->dapm.idle_bias_off = true;

	/* set the शेष PLL rate, the घड़ी is handled by the codec driver */
	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_codec(rtd, 0), CX2072X_MCLK_EXTERNAL_PLL,
				     19200000, SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(rtd->dev, "Could not set sysclk\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_card_jack_new(card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &byt_cht_cx2072x_headset,
				    byt_cht_cx2072x_headset_pins,
				    ARRAY_SIZE(byt_cht_cx2072x_headset_pins));
	अगर (ret)
		वापस ret;

	snd_soc_component_set_jack(codec, &byt_cht_cx2072x_headset, शून्य);

	snd_soc_dai_set_bclk_ratio(asoc_rtd_to_codec(rtd, 0), 50);

	वापस 0;
पूर्ण

अटल पूर्णांक byt_cht_cx2072x_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret;

	/* The DSP will covert the FE rate to 48k, stereo, 24bits */
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

अटल पूर्णांक byt_cht_cx2072x_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					    SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल काष्ठा snd_soc_ops byt_cht_cx2072x_aअगर1_ops = अणु
	.startup = byt_cht_cx2072x_aअगर1_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp2,
	DAILINK_COMP_ARRAY(COMP_CPU("ssp2-port")));

SND_SOC_DAILINK_DEF(cx2072x,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-14F10720:00", "cx2072x-hifi")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link byt_cht_cx2072x_dais[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &byt_cht_cx2072x_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &byt_cht_cx2072x_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
					      | SND_SOC_DAIFMT_CBS_CFS,
		.init = byt_cht_cx2072x_init,
		.be_hw_params_fixup = byt_cht_cx2072x_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp2, cx2072x, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht cx2072x" /* card name will be 'sof-bytcht cx2072x' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bytcht-cx2072x"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card byt_cht_cx2072x_card = अणु
	.name = CARD_NAME,
	.driver_name = DRIVER_NAME,
	.owner = THIS_MODULE,
	.dai_link = byt_cht_cx2072x_dais,
	.num_links = ARRAY_SIZE(byt_cht_cx2072x_dais),
	.dapm_widमाला_लो = byt_cht_cx2072x_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(byt_cht_cx2072x_widमाला_लो),
	.dapm_routes = byt_cht_cx2072x_audio_map,
	.num_dapm_routes = ARRAY_SIZE(byt_cht_cx2072x_audio_map),
	.controls = byt_cht_cx2072x_controls,
	.num_controls = ARRAY_SIZE(byt_cht_cx2072x_controls),
पूर्ण;

अटल अक्षर codec_name[SND_ACPI_I2C_ID_LEN];

अटल पूर्णांक snd_byt_cht_cx2072x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा acpi_device *adev;
	पूर्णांक dai_index = 0;
	bool sof_parent;
	पूर्णांक i, ret;

	byt_cht_cx2072x_card.dev = &pdev->dev;
	mach = dev_get_platdata(&pdev->dev);

	/* fix index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(byt_cht_cx2072x_dais); i++) अणु
		अगर (!म_भेद(byt_cht_cx2072x_dais[i].codecs->name,
			    "i2c-14F10720:00")) अणु
			dai_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(codec_name, माप(codec_name), "i2c-%s",
			 acpi_dev_name(adev));
		put_device(&adev->dev);
		byt_cht_cx2072x_dais[dai_index].codecs->name = codec_name;
	पूर्ण

	/* override plaक्रमm name, अगर required */
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&byt_cht_cx2072x_card,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		byt_cht_cx2072x_card.name = SOF_CARD_NAME;
		byt_cht_cx2072x_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		byt_cht_cx2072x_card.name = CARD_NAME;
		byt_cht_cx2072x_card.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		pdev->dev.driver->pm = &snd_soc_pm_ops;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &byt_cht_cx2072x_card);
पूर्ण

अटल काष्ठा platक्रमm_driver snd_byt_cht_cx2072x_driver = अणु
	.driver = अणु
		.name = "bytcht_cx2072x",
	पूर्ण,
	.probe = snd_byt_cht_cx2072x_probe,
पूर्ण;
module_platक्रमm_driver(snd_byt_cht_cx2072x_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail/Cherrytrail Machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcht_cx2072x");
