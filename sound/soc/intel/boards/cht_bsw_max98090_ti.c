<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cht-bsw-max98090.c - ASoc Machine driver क्रम Intel Cherryview-based
 *  platक्रमms Cherrytrail and Braswell, with max98090 & TI codec.
 *
 *  Copyright (C) 2015 Intel Corp
 *  Author: Fang, Yang A <yang.a.fang@पूर्णांकel.com>
 *  This file is modअगरied from cht_bsw_rt5645.c
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/dmi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/jack.h>
#समावेश "../../codecs/max98090.h"
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../../codecs/ts3a227e.h"

#घोषणा CHT_PLAT_CLK_3_HZ	19200000
#घोषणा CHT_CODEC_DAI	"HiFi"

#घोषणा QUIRK_PMC_PLT_CLK_0				0x01

काष्ठा cht_mc_निजी अणु
	काष्ठा clk *mclk;
	काष्ठा snd_soc_jack jack;
	bool ts3a227e_present;
	पूर्णांक quirks;
पूर्ण;

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
					  काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	/* See the comment in snd_cht_mc_probe() */
	अगर (ctx->quirks & QUIRK_PMC_PLT_CLK_0)
		वापस 0;

	codec_dai = snd_soc_card_get_codec_dai(card, CHT_CODEC_DAI);
	अगर (!codec_dai) अणु
		dev_err(card->dev, "Codec dai not found; Unable to set platform clock\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = clk_prepare_enable(ctx->mclk);
		अगर (ret < 0) अणु
			dev_err(card->dev,
				"could not configure MCLK state");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(ctx->mclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cht_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			    platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU |
			    SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_audio_map[] = अणु
	अणु"IN34", शून्य, "Headset Mic"पूर्ण,
	अणु"Headset Mic", शून्य, "MICBIAS"पूर्ण,
	अणु"DMICL", शून्य, "Int Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPL"पूर्ण,
	अणु"Headphone", शून्य, "HPR"पूर्ण,
	अणु"Ext Spk", शून्य, "SPKL"पूर्ण,
	अणु"Ext Spk", शून्य, "SPKR"पूर्ण,
	अणु"HiFi Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx" पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx" पूर्ण,
	अणु"ssp2 Rx", शून्य, "HiFi Capture"पूर्ण,
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Int Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Ext Spk", शून्य, "Platform Clock"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cht_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
पूर्ण;

अटल पूर्णांक cht_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, M98090_REG_SYSTEM_CLOCK,
				     CHT_PLAT_CLK_3_HZ, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cht_ti_jack_event(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा snd_soc_jack *jack = (काष्ठा snd_soc_jack *)data;
	काष्ठा snd_soc_dapm_context *dapm = &jack->card->dapm;

	अगर (event & SND_JACK_MICROPHONE) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "SHDN");
		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS");
		snd_soc_dapm_sync(dapm);
	पूर्ण अन्यथा अणु
		snd_soc_dapm_disable_pin(dapm, "MICBIAS");
		snd_soc_dapm_disable_pin(dapm, "SHDN");
		snd_soc_dapm_sync(dapm);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block cht_jack_nb = अणु
	.notअगरier_call = cht_ti_jack_event,
पूर्ण;

अटल काष्ठा snd_soc_jack_pin hs_jack_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio hs_jack_gpios[] = अणु
	अणु
		.name		= "hp",
		.report		= SND_JACK_HEADPHONE | SND_JACK_LINEOUT,
		.debounce_समय	= 200,
	पूर्ण,
	अणु
		.name		= "mic",
		.invert		= 1,
		.report		= SND_JACK_MICROPHONE,
		.debounce_समय	= 200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params hp_gpios = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params mic_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_max98090_gpios[] = अणु
	अणु "hp-gpios", &hp_gpios, 1 पूर्ण,
	अणु "mic-gpios", &mic_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक cht_codec_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	पूर्णांक ret;
	पूर्णांक jack_type;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(runसमय->card);
	काष्ठा snd_soc_jack *jack = &ctx->jack;

	अगर (ctx->ts3a227e_present) अणु
		/*
		 * The jack has alपढ़ोy been created in the
		 * cht_max98090_headset_init() function.
		 */
		snd_soc_jack_notअगरier_रेजिस्टर(jack, &cht_jack_nb);
		वापस 0;
	पूर्ण

	jack_type = SND_JACK_HEADPHONE | SND_JACK_MICROPHONE;

	ret = snd_soc_card_jack_new(runसमय->card, "Headset Jack",
				    jack_type, jack,
				    hs_jack_pins, ARRAY_SIZE(hs_jack_pins));
	अगर (ret) अणु
		dev_err(runसमय->dev, "Headset Jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_jack_add_gpiods(runसमय->card->dev->parent, jack,
				      ARRAY_SIZE(hs_jack_gpios),
				      hs_jack_gpios);
	अगर (ret) अणु
		/*
		 * flag error but करोn't bail अगर jack detect is broken
		 * due to platक्रमm issues or bad BIOS/configuration
		 */
		dev_err(runसमय->dev,
			"jack detection gpios not added, error %d\n", ret);
	पूर्ण

	/* See the comment in snd_cht_mc_probe() */
	अगर (ctx->quirks & QUIRK_PMC_PLT_CLK_0)
		वापस 0;

	/*
	 * The firmware might enable the घड़ी at
	 * boot (this inक्रमmation may or may not
	 * be reflected in the enable घड़ी रेजिस्टर).
	 * To change the rate we must disable the घड़ी
	 * first to cover these हालs. Due to common
	 * घड़ी framework restrictions that करो not allow
	 * to disable a घड़ी that has not been enabled,
	 * we need to enable the घड़ी first.
	 */
	ret = clk_prepare_enable(ctx->mclk);
	अगर (!ret)
		clk_disable_unprepare(ctx->mclk);

	ret = clk_set_rate(ctx->mclk, CHT_PLAT_CLK_3_HZ);

	अगर (ret)
		dev_err(runसमय->dev, "unable to set MCLK rate\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cht_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक fmt = 0;

	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2, 16);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set cpu_dai slot fmt: %d\n", ret);
		वापस ret;
	पूर्ण

	fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBS_CFS;

	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0), fmt);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set cpu_dai set fmt: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The DSP will covert the FE rate to 48k, stereo, 24bits */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	/* set SSP2 to 16-bit */
	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);
	वापस 0;
पूर्ण

अटल पूर्णांक cht_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल पूर्णांक cht_max98090_headset_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_card *card = component->card;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_jack *jack = &ctx->jack;
	पूर्णांक jack_type;
	पूर्णांक ret;

	/*
	 * TI supports 4 butons headset detection
	 * KEY_MEDIA
	 * KEY_VOICECOMMAND
	 * KEY_VOLUMEUP
	 * KEY_VOLUMEDOWN
	 */
	jack_type = SND_JACK_HEADPHONE | SND_JACK_MICROPHONE |
		    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		    SND_JACK_BTN_2 | SND_JACK_BTN_3;

	ret = snd_soc_card_jack_new(card, "Headset Jack", jack_type,
				    jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "Headset Jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ts3a227e_enable_jack_detect(component, jack);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops cht_aअगर1_ops = अणु
	.startup = cht_aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cht_be_ssp2_ops = अणु
	.hw_params = cht_aअगर1_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_aux_dev cht_max98090_headset_dev = अणु
	.dlc = COMP_AUX("i2c-104C227E:00"),
	.init = cht_max98090_headset_init,
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
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-193C9890:00", "HiFi")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link cht_dailink[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &cht_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBS_CFS,
		.init = cht_codec_init,
		.be_hw_params_fixup = cht_codec_fixup,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_be_ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht max98090" /* card name will be 'sof-bytcht max98090 */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "chtmax98090"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card snd_soc_card_cht = अणु
	.owner = THIS_MODULE,
	.dai_link = cht_dailink,
	.num_links = ARRAY_SIZE(cht_dailink),
	.aux_dev = &cht_max98090_headset_dev,
	.num_aux_devs = 1,
	.dapm_widमाला_लो = cht_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cht_dapm_widमाला_लो),
	.dapm_routes = cht_audio_map,
	.num_dapm_routes = ARRAY_SIZE(cht_audio_map),
	.controls = cht_mc_controls,
	.num_controls = ARRAY_SIZE(cht_mc_controls),
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id cht_max98090_quirk_table[] = अणु
	अणु
		/* Banjo model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Banjo"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Candy model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Candy"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Clapper model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Clapper"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Cyan model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Cyan"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Enguarde model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Enguarde"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Glimmer model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Glimmer"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Gnawty model Chromebook (Acer Chromebook CB3-111) */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Gnawty"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Heli model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Heli"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Kip model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Kip"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Ninja model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Ninja"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Orco model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Orco"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Quawks model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Quawks"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Rambi model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Rambi"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Squawks model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Squawks"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Sumo model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Sumo"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Swanky model Chromebook (Toshiba Chromebook 2) */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Swanky"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
		/* Winky model Chromebook */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Winky"),
		पूर्ण,
		.driver_data = (व्योम *)QUIRK_PMC_PLT_CLK_0,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक snd_cht_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret_val = 0;
	काष्ठा cht_mc_निजी *drv;
	स्थिर अक्षर *mclk_name;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	bool sof_parent;

	drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	dmi_id = dmi_first_match(cht_max98090_quirk_table);
	अगर (dmi_id)
		drv->quirks = (अचिन्हित दीर्घ)dmi_id->driver_data;

	drv->ts3a227e_present = acpi_dev_found("104C227E");
	अगर (!drv->ts3a227e_present) अणु
		/* no need probe TI jack detection chip */
		snd_soc_card_cht.aux_dev = शून्य;
		snd_soc_card_cht.num_aux_devs = 0;

		ret_val = devm_acpi_dev_add_driver_gpios(dev->parent,
							 acpi_max98090_gpios);
		अगर (ret_val)
			dev_dbg(dev, "Unable to add GPIO mapping table\n");
	पूर्ण

	/* override plaक्रमm name, अगर required */
	snd_soc_card_cht.dev = &pdev->dev;
	mach = pdev->dev.platक्रमm_data;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(&snd_soc_card_cht,
							platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	/* रेजिस्टर the soc card */
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	अगर (drv->quirks & QUIRK_PMC_PLT_CLK_0)
		mclk_name = "pmc_plt_clk_0";
	अन्यथा
		mclk_name = "pmc_plt_clk_3";

	drv->mclk = devm_clk_get(&pdev->dev, mclk_name);
	अगर (IS_ERR(drv->mclk)) अणु
		dev_err(&pdev->dev,
			"Failed to get MCLK from %s: %ld\n",
			mclk_name, PTR_ERR(drv->mclk));
		वापस PTR_ERR(drv->mclk);
	पूर्ण

	/*
	 * Boards which have the MAX98090's clk connected to clk_0 करो not seem
	 * to like it अगर we muck with the घड़ी. If we disable the घड़ी when
	 * it is unused we get "max98090 i2c-193C9890:00: PLL unlocked" errors
	 * and the PLL never seems to lock again.
	 * So क्रम these boards we enable it here once and leave it at that.
	 */
	अगर (drv->quirks & QUIRK_PMC_PLT_CLK_0) अणु
		ret_val = clk_prepare_enable(drv->mclk);
		अगर (ret_val < 0) अणु
			dev_err(&pdev->dev, "MCLK enable error: %d\n", ret_val);
			वापस ret_val;
		पूर्ण
	पूर्ण

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		snd_soc_card_cht.name = SOF_CARD_NAME;
		snd_soc_card_cht.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		snd_soc_card_cht.name = CARD_NAME;
		snd_soc_card_cht.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		dev->driver->pm = &snd_soc_pm_ops;

	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &snd_soc_card_cht);
	अगर (ret_val) अणु
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &snd_soc_card_cht);
	वापस ret_val;
पूर्ण

अटल पूर्णांक snd_cht_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);

	अगर (ctx->quirks & QUIRK_PMC_PLT_CLK_0)
		clk_disable_unprepare(ctx->mclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_cht_mc_driver = अणु
	.driver = अणु
		.name = "cht-bsw-max98090",
	पूर्ण,
	.probe = snd_cht_mc_probe,
	.हटाओ = snd_cht_mc_हटाओ,
पूर्ण;

module_platक्रमm_driver(snd_cht_mc_driver)

MODULE_DESCRIPTION("ASoC Intel(R) Braswell Machine driver");
MODULE_AUTHOR("Fang, Yang A <yang.a.fang@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cht-bsw-max98090");
