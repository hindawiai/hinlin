<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  bytcht_es8316.c - ASoc Machine driver क्रम Intel Baytrail/Cherrytrail
 *                    platक्रमms with Everest ES8316 SoC
 *
 *  Copyright (C) 2017 Endless Mobile, Inc.
 *  Authors: David Yang <yangxiaohua@everest-semi.com>,
 *           Daniel Drake <drake@endlessm.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../common/soc-intel-quirks.h"

/* jd-inv + terminating entry */
#घोषणा MAX_NO_PROPS 2

काष्ठा byt_cht_es8316_निजी अणु
	काष्ठा clk *mclk;
	काष्ठा snd_soc_jack jack;
	काष्ठा gpio_desc *speaker_en_gpio;
	bool speaker_en;
पूर्ण;

क्रमागत अणु
	BYT_CHT_ES8316_INTMIC_IN1_MAP,
	BYT_CHT_ES8316_INTMIC_IN2_MAP,
पूर्ण;

#घोषणा BYT_CHT_ES8316_MAP(quirk)		((quirk) & GENMASK(3, 0))
#घोषणा BYT_CHT_ES8316_SSP0			BIT(16)
#घोषणा BYT_CHT_ES8316_MONO_SPEAKER		BIT(17)
#घोषणा BYT_CHT_ES8316_JD_INVERTED		BIT(18)

अटल अचिन्हित दीर्घ quirk;

अटल पूर्णांक quirk_override = -1;
module_param_named(quirk, quirk_override, पूर्णांक, 0444);
MODULE_PARM_DESC(quirk, "Board-specific quirk override");

अटल व्योम log_quirks(काष्ठा device *dev)
अणु
	अगर (BYT_CHT_ES8316_MAP(quirk) == BYT_CHT_ES8316_INTMIC_IN1_MAP)
		dev_info(dev, "quirk IN1_MAP enabled");
	अगर (BYT_CHT_ES8316_MAP(quirk) == BYT_CHT_ES8316_INTMIC_IN2_MAP)
		dev_info(dev, "quirk IN2_MAP enabled");
	अगर (quirk & BYT_CHT_ES8316_SSP0)
		dev_info(dev, "quirk SSP0 enabled");
	अगर (quirk & BYT_CHT_ES8316_MONO_SPEAKER)
		dev_info(dev, "quirk MONO_SPEAKER enabled\n");
	अगर (quirk & BYT_CHT_ES8316_JD_INVERTED)
		dev_info(dev, "quirk JD_INVERTED enabled\n");
पूर्ण

अटल पूर्णांक byt_cht_es8316_speaker_घातer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा byt_cht_es8316_निजी *priv = snd_soc_card_get_drvdata(card);

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		priv->speaker_en = true;
	अन्यथा
		priv->speaker_en = false;

	gpiod_set_value_cansleep(priv->speaker_en_gpio, priv->speaker_en);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget byt_cht_es8316_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic", शून्य),

	SND_SOC_DAPM_SUPPLY("Speaker Power", SND_SOC_NOPM, 0, 0,
			    byt_cht_es8316_speaker_घातer_event,
			    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_cht_es8316_audio_map[] = अणु
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,

	/*
	 * There is no separate speaker output instead the speakers are muxed to
	 * the HP outमाला_दो. The mux is controlled by the "Speaker Power" supply.
	 */
	अणु"Speaker", शून्य, "HPOL"पूर्ण,
	अणु"Speaker", शून्य, "HPOR"पूर्ण,
	अणु"Speaker", शून्य, "Speaker Power"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_cht_es8316_पूर्णांकmic_in1_map[] = अणु
	अणु"MIC1", शून्य, "Internal Mic"पूर्ण,
	अणु"MIC2", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_cht_es8316_पूर्णांकmic_in2_map[] = अणु
	अणु"MIC2", शून्य, "Internal Mic"पूर्ण,
	अणु"MIC1", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_cht_es8316_ssp0_map[] = अणु
	अणु"Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_cht_es8316_ssp2_map[] = अणु
	अणु"Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx" पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx" पूर्ण,
	अणु"ssp2 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new byt_cht_es8316_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Internal Mic"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin byt_cht_es8316_jack_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक byt_cht_es8316_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_component *codec = asoc_rtd_to_codec(runसमय, 0)->component;
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा byt_cht_es8316_निजी *priv = snd_soc_card_get_drvdata(card);
	स्थिर काष्ठा snd_soc_dapm_route *custom_map;
	पूर्णांक num_routes;
	पूर्णांक ret;

	card->dapm.idle_bias_off = true;

	चयन (BYT_CHT_ES8316_MAP(quirk)) अणु
	हाल BYT_CHT_ES8316_INTMIC_IN1_MAP:
	शेष:
		custom_map = byt_cht_es8316_पूर्णांकmic_in1_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_पूर्णांकmic_in1_map);
		अवरोध;
	हाल BYT_CHT_ES8316_INTMIC_IN2_MAP:
		custom_map = byt_cht_es8316_पूर्णांकmic_in2_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_पूर्णांकmic_in2_map);
		अवरोध;
	पूर्ण
	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	अगर (ret)
		वापस ret;

	अगर (quirk & BYT_CHT_ES8316_SSP0) अणु
		custom_map = byt_cht_es8316_ssp0_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_ssp0_map);
	पूर्ण अन्यथा अणु
		custom_map = byt_cht_es8316_ssp2_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_ssp2_map);
	पूर्ण
	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	अगर (ret)
		वापस ret;

	/*
	 * The firmware might enable the घड़ी at boot (this inक्रमmation
	 * may or may not be reflected in the enable घड़ी रेजिस्टर).
	 * To change the rate we must disable the घड़ी first to cover these
	 * हालs. Due to common घड़ी framework restrictions that करो not allow
	 * to disable a घड़ी that has not been enabled, we need to enable
	 * the घड़ी first.
	 */
	ret = clk_prepare_enable(priv->mclk);
	अगर (!ret)
		clk_disable_unprepare(priv->mclk);

	ret = clk_set_rate(priv->mclk, 19200000);
	अगर (ret)
		dev_err(card->dev, "unable to set MCLK rate\n");

	ret = clk_prepare_enable(priv->mclk);
	अगर (ret)
		dev_err(card->dev, "unable to enable MCLK\n");

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_codec(runसमय, 0), 0, 19200000,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(card->dev, "can't set codec clock %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_card_jack_new(card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &priv->jack, byt_cht_es8316_jack_pins,
				    ARRAY_SIZE(byt_cht_es8316_jack_pins));
	अगर (ret) अणु
		dev_err(card->dev, "jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(priv->jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_soc_component_set_jack(codec, &priv->jack, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक byt_cht_es8316_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret, bits;

	/* The DSP will covert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	अगर (quirk & BYT_CHT_ES8316_SSP0) अणु
		/* set SSP0 to 16-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);
		bits = 16;
	पूर्ण अन्यथा अणु
		/* set SSP2 to 24-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);
		bits = 24;
	पूर्ण

	/*
	 * Default mode क्रम SSP configuration is TDM 4 slot, override config
	 * with explicit setting to I2S 2ch 24-bit. The word length is set with
	 * dai_set_tdm_slot() since there is no other API exposed
	 */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0),
				SND_SOC_DAIFMT_I2S     |
				SND_SOC_DAIFMT_NB_NF   |
				SND_SOC_DAIFMT_CBS_CFS
		);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set format to I2S, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2, bits);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set I2S config, err %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_cht_es8316_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops byt_cht_es8316_aअगर1_ops = अणु
	.startup = byt_cht_es8316_aअगर1_startup,
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
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-ESSX8316:00", "ES8316 HiFi")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link byt_cht_es8316_dais[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &byt_cht_es8316_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,

	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &byt_cht_es8316_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,

		/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBS_CFS,
		.be_hw_params_fixup = byt_cht_es8316_codec_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.init = byt_cht_es8316_init,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;


/* SoC card */
अटल अक्षर codec_name[SND_ACPI_I2C_ID_LEN];
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_USER_FRIENDLY_LONG_NAMES)
अटल अक्षर दीर्घ_name[50]; /* = "bytcht-es8316-*-spk-*-mic" */
#पूर्ण_अगर
अटल अक्षर components_string[32]; /* = "cfg-spk:* cfg-mic:* */

अटल पूर्णांक byt_cht_es8316_suspend(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, codec_name)) अणु
			dev_dbg(component->dev, "disabling jack detect before suspend\n");
			snd_soc_component_set_jack(component, शून्य, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_cht_es8316_resume(काष्ठा snd_soc_card *card)
अणु
	काष्ठा byt_cht_es8316_निजी *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, codec_name)) अणु
			dev_dbg(component->dev, "re-enabling jack detect after resume\n");
			snd_soc_component_set_jack(component, &priv->jack, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Some Cherry Trail boards with an ES8316 codec have a bug in their
	 * ACPI tables where the MSSL1680 touchscreen's _PS0 and _PS3 methods
	 * wrongly also set the speaker-enable GPIO to 1/0. Testing has shown
	 * that this really is a bug and the GPIO has no influence on the
	 * touchscreen at all.
	 *
	 * The silead.c touchscreen driver करोes not support runसमय suspend, so
	 * the GPIO can only be changed underneath us during a प्रणाली suspend.
	 * This resume() function runs from a pm complete() callback, and thus
	 * is guaranteed to run after the touchscreen driver/ACPI-subsys has
	 * brought the touchscreen back up again (and thus changed the GPIO).
	 *
	 * So to work around this we pass GPIOD_FLAGS_BIT_NONEXCLUSIVE when
	 * requesting the GPIO and we set its value here to unकरो any changes
	 * करोne by the touchscreen's broken _PS0 ACPI method.
	 */
	gpiod_set_value_cansleep(priv->speaker_en_gpio, priv->speaker_en);

	वापस 0;
पूर्ण

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht es8316" /* card name will be 'sof-bytcht es8316' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bytcht-es8316"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

अटल काष्ठा snd_soc_card byt_cht_es8316_card = अणु
	.owner = THIS_MODULE,
	.dai_link = byt_cht_es8316_dais,
	.num_links = ARRAY_SIZE(byt_cht_es8316_dais),
	.dapm_widमाला_लो = byt_cht_es8316_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(byt_cht_es8316_widमाला_लो),
	.dapm_routes = byt_cht_es8316_audio_map,
	.num_dapm_routes = ARRAY_SIZE(byt_cht_es8316_audio_map),
	.controls = byt_cht_es8316_controls,
	.num_controls = ARRAY_SIZE(byt_cht_es8316_controls),
	.fully_routed = true,
	.suspend_pre = byt_cht_es8316_suspend,
	.resume_post = byt_cht_es8316_resume,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params first_gpio = अणु 0, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping byt_cht_es8316_gpios[] = अणु
	अणु "speaker-enable-gpios", &first_gpio, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* Please keep this list alphabetically sorted */
अटल स्थिर काष्ठा dmi_प्रणाली_id byt_cht_es8316_quirk_table[] = अणु
	अणु	/* Irbis NB41 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IRBIS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "NB41"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_CHT_ES8316_SSP0
					| BYT_CHT_ES8316_INTMIC_IN2_MAP
					| BYT_CHT_ES8316_JD_INVERTED),
	पूर्ण,
	अणु	/* Teclast X98 Plus II */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X98 Plus II"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_CHT_ES8316_INTMIC_IN1_MAP
					| BYT_CHT_ES8316_JD_INVERTED),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक snd_byt_cht_es8316_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल स्थिर अक्षर * स्थिर mic_name[] = अणु "in1", "in2" पूर्ण;
	काष्ठा property_entry props[MAX_NO_PROPS] = अणुपूर्ण;
	काष्ठा byt_cht_es8316_निजी *priv;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा acpi_device *adev;
	काष्ठा device *codec_dev;
	bool sof_parent;
	अचिन्हित पूर्णांक cnt = 0;
	पूर्णांक dai_index = 0;
	पूर्णांक i;
	पूर्णांक ret = 0;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mach = dev->platक्रमm_data;
	/* fix index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(byt_cht_es8316_dais); i++) अणु
		अगर (!म_भेद(byt_cht_es8316_dais[i].codecs->name,
			    "i2c-ESSX8316:00")) अणु
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
		byt_cht_es8316_dais[dai_index].codecs->name = codec_name;
	पूर्ण

	/* override plaक्रमm name, अगर required */
	byt_cht_es8316_card.dev = dev;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret = snd_soc_fixup_dai_links_platक्रमm_name(&byt_cht_es8316_card,
						    platक्रमm_name);
	अगर (ret)
		वापस ret;

	/* Check क्रम BYTCR or other platक्रमm and setup quirks */
	dmi_id = dmi_first_match(byt_cht_es8316_quirk_table);
	अगर (dmi_id) अणु
		quirk = (अचिन्हित दीर्घ)dmi_id->driver_data;
	पूर्ण अन्यथा अगर (soc_पूर्णांकel_is_byt() &&
		   mach->mach_params.acpi_ipc_irq_index == 0) अणु
		/* On BYTCR शेष to SSP0, पूर्णांकernal-mic-in2-map, mono-spk */
		quirk = BYT_CHT_ES8316_SSP0 | BYT_CHT_ES8316_INTMIC_IN2_MAP |
			BYT_CHT_ES8316_MONO_SPEAKER;
	पूर्ण अन्यथा अणु
		/* Others शेष to पूर्णांकernal-mic-in1-map, mono-speaker */
		quirk = BYT_CHT_ES8316_INTMIC_IN1_MAP |
			BYT_CHT_ES8316_MONO_SPEAKER;
	पूर्ण
	अगर (quirk_override != -1) अणु
		dev_info(dev, "Overriding quirk 0x%lx => 0x%x\n",
			 quirk, quirk_override);
		quirk = quirk_override;
	पूर्ण
	log_quirks(dev);

	अगर (quirk & BYT_CHT_ES8316_SSP0)
		byt_cht_es8316_dais[dai_index].cpus->dai_name = "ssp0-port";

	/* get the घड़ी */
	priv->mclk = devm_clk_get(dev, "pmc_plt_clk_3");
	अगर (IS_ERR(priv->mclk)) अणु
		ret = PTR_ERR(priv->mclk);
		dev_err(dev, "clk_get pmc_plt_clk_3 failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* get speaker enable GPIO */
	codec_dev = bus_find_device_by_name(&i2c_bus_type, शून्य, codec_name);
	अगर (!codec_dev)
		वापस -EPROBE_DEFER;

	अगर (quirk & BYT_CHT_ES8316_JD_INVERTED)
		props[cnt++] = PROPERTY_ENTRY_BOOL("everest,jack-detect-inverted");

	अगर (cnt) अणु
		ret = device_add_properties(codec_dev, props);
		अगर (ret) अणु
			put_device(codec_dev);
			वापस ret;
		पूर्ण
	पूर्ण

	devm_acpi_dev_add_driver_gpios(codec_dev, byt_cht_es8316_gpios);
	priv->speaker_en_gpio =
		gpiod_get_index(codec_dev, "speaker-enable", 0,
				/* see comment in byt_cht_es8316_resume */
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	put_device(codec_dev);

	अगर (IS_ERR(priv->speaker_en_gpio)) अणु
		ret = PTR_ERR(priv->speaker_en_gpio);
		चयन (ret) अणु
		हाल -ENOENT:
			priv->speaker_en_gpio = शून्य;
			अवरोध;
		शेष:
			dev_err(dev, "get speaker GPIO failed: %d\n", ret);
			fallthrough;
		हाल -EPROBE_DEFER:
			वापस ret;
		पूर्ण
	पूर्ण

	snम_लिखो(components_string, माप(components_string),
		 "cfg-spk:%s cfg-mic:%s",
		 (quirk & BYT_CHT_ES8316_MONO_SPEAKER) ? "1" : "2",
		 mic_name[BYT_CHT_ES8316_MAP(quirk)]);
	byt_cht_es8316_card.components = components_string;
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_USER_FRIENDLY_LONG_NAMES)
	snम_लिखो(दीर्घ_name, माप(दीर्घ_name), "bytcht-es8316-%s-spk-%s-mic",
		 (quirk & BYT_CHT_ES8316_MONO_SPEAKER) ? "mono" : "stereo",
		 mic_name[BYT_CHT_ES8316_MAP(quirk)]);
	byt_cht_es8316_card.दीर्घ_name = दीर्घ_name;
#पूर्ण_अगर

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		byt_cht_es8316_card.name = SOF_CARD_NAME;
		byt_cht_es8316_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		byt_cht_es8316_card.name = CARD_NAME;
		byt_cht_es8316_card.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		dev->driver->pm = &snd_soc_pm_ops;

	/* रेजिस्टर the soc card */
	snd_soc_card_set_drvdata(&byt_cht_es8316_card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(dev, &byt_cht_es8316_card);
	अगर (ret) अणु
		gpiod_put(priv->speaker_en_gpio);
		dev_err(dev, "snd_soc_register_card failed: %d\n", ret);
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &byt_cht_es8316_card);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_byt_cht_es8316_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा byt_cht_es8316_निजी *priv = snd_soc_card_get_drvdata(card);

	gpiod_put(priv->speaker_en_gpio);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_byt_cht_es8316_mc_driver = अणु
	.driver = अणु
		.name = "bytcht_es8316",
	पूर्ण,
	.probe = snd_byt_cht_es8316_mc_probe,
	.हटाओ = snd_byt_cht_es8316_mc_हटाओ,
पूर्ण;

module_platक्रमm_driver(snd_byt_cht_es8316_mc_driver);
MODULE_DESCRIPTION("ASoC Intel(R) Baytrail/Cherrytrail Machine driver");
MODULE_AUTHOR("David Yang <yangxiaohua@everest-semi.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcht_es8316");
