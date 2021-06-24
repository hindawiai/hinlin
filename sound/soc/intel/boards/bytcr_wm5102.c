<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  bytcr_wm5102.c - ASoc Machine driver क्रम Intel Baytrail platक्रमms with a
 *                   Wolfson Microelectronics WM5102 codec
 *
 *  Copyright (C) 2020 Hans de Goede <hdegoede@redhat.com>
 *  Loosely based on bytcr_rt5640.c which is:
 *  Copyright (C) 2014-2020 Intel Corp
 *  Author: Subhransu S. Prusty <subhransu.s.prusty@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/wm5102.h"
#समावेश "../atom/sst-atom-controls.h"

#घोषणा MCLK_FREQ		25000000

#घोषणा WM5102_MAX_SYSCLK_4K	49152000 /* max sysclk क्रम 4K family */
#घोषणा WM5102_MAX_SYSCLK_11025	45158400 /* max sysclk क्रम 11.025K family */

काष्ठा byt_wm5102_निजी अणु
	काष्ठा snd_soc_jack jack;
	काष्ठा clk *mclk;
	काष्ठा gpio_desc *spkvdd_en_gpio;
पूर्ण;

अटल पूर्णांक byt_wm5102_spkvdd_घातer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा byt_wm5102_निजी *priv = snd_soc_card_get_drvdata(card);

	gpiod_set_value_cansleep(priv->spkvdd_en_gpio,
				 !!SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल पूर्णांक byt_wm5102_prepare_and_enable_pll1(काष्ठा snd_soc_dai *codec_dai, पूर्णांक rate)
अणु
	काष्ठा snd_soc_component *codec_component = codec_dai->component;
	पूर्णांक sr_mult = ((rate % 4000) == 0) ?
		(WM5102_MAX_SYSCLK_4K / rate) :
		(WM5102_MAX_SYSCLK_11025 / rate);
	पूर्णांक ret;

	/* Reset FLL1 */
	snd_soc_dai_set_pll(codec_dai, WM5102_FLL1_REFCLK, ARIZONA_FLL_SRC_NONE, 0, 0);
	snd_soc_dai_set_pll(codec_dai, WM5102_FLL1, ARIZONA_FLL_SRC_NONE, 0, 0);

	/* Configure the FLL1 PLL beक्रमe selecting it */
	ret = snd_soc_dai_set_pll(codec_dai, WM5102_FLL1, ARIZONA_CLK_SRC_MCLK1,
				  MCLK_FREQ, rate * sr_mult);
	अगर (ret) अणु
		dev_err(codec_component->dev, "Error setting PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_sysclk(codec_component, ARIZONA_CLK_SYSCLK,
					   ARIZONA_CLK_SRC_FLL1, rate * sr_mult,
					   SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(codec_component->dev, "Error setting SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, ARIZONA_CLK_SYSCLK,
				     rate * 512, SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(codec_component->dev, "Error setting clock: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा byt_wm5102_निजी *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	codec_dai = snd_soc_card_get_codec_dai(card, "wm5102-aif1");
	अगर (!codec_dai) अणु
		dev_err(card->dev, "Error codec DAI not found\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = clk_prepare_enable(priv->mclk);
		अगर (ret) अणु
			dev_err(card->dev, "Error enabling MCLK: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = byt_wm5102_prepare_and_enable_pll1(codec_dai, 48000);
		अगर (ret) अणु
			dev_err(card->dev, "Error setting codec sysclk: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The WM5102 has a separate 32KHz घड़ी क्रम jack-detect
		 * so we can disable the PLL, followed by disabling the
		 * platक्रमm घड़ी which is the source-घड़ी क्रम the PLL.
		 */
		snd_soc_dai_set_pll(codec_dai, WM5102_FLL1, ARIZONA_FLL_SRC_NONE, 0, 0);
		clk_disable_unprepare(priv->mclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget byt_wm5102_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			    platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU |
			    SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("Speaker VDD", SND_SOC_NOPM, 0, 0,
			    byt_wm5102_spkvdd_घातer_event,
			    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_wm5102_audio_map[] = अणु
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Internal Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Speaker", शून्य, "Platform Clock"पूर्ण,

	अणु"Speaker", शून्य, "SPKOUTLP"पूर्ण,
	अणु"Speaker", शून्य, "SPKOUTLN"पूर्ण,
	अणु"Speaker", शून्य, "SPKOUTRP"पूर्ण,
	अणु"Speaker", शून्य, "SPKOUTRN"पूर्ण,
	अणु"Speaker", शून्य, "Speaker VDD"पूर्ण,

	अणु"Headphone", शून्य, "HPOUT1L"पूर्ण,
	अणु"Headphone", शून्य, "HPOUT1R"पूर्ण,

	अणु"Internal Mic", शून्य, "MICBIAS3"पूर्ण,
	अणु"IN3L", शून्य, "Internal Mic"पूर्ण,

	/*
	 * The Headset Mix uses MICBIAS1 or 2 depending on अगर a CTIA/OMTP Headset
	 * is connected, as the MICBIAS is applied after the CTIA/OMTP cross-चयन.
	 */
	अणु"Headset Mic", शून्य, "MICBIAS1"पूर्ण,
	अणु"Headset Mic", शून्य, "MICBIAS2"पूर्ण,
	अणु"IN1L", शून्य, "Headset Mic"पूर्ण,

	अणु"AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,

	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new byt_wm5102_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Internal Mic"),
	SOC_DAPM_PIN_SWITCH("Speaker"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin byt_wm5102_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक byt_wm5102_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा byt_wm5102_निजी *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;
	पूर्णांक ret, jack_type;

	card->dapm.idle_bias_off = true;

	ret = snd_soc_add_card_controls(card, byt_wm5102_controls,
					ARRAY_SIZE(byt_wm5102_controls));
	अगर (ret) अणु
		dev_err(card->dev, "Error adding card controls: %d\n", ret);
		वापस ret;
	पूर्ण

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

	ret = clk_set_rate(priv->mclk, MCLK_FREQ);
	अगर (ret) अणु
		dev_err(card->dev, "Error setting MCLK rate: %d\n", ret);
		वापस ret;
	पूर्ण

	jack_type = ARIZONA_JACK_MASK | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		    SND_JACK_BTN_2 | SND_JACK_BTN_3;
	ret = snd_soc_card_jack_new(card, "Headset", jack_type,
				    &priv->jack, byt_wm5102_pins,
				    ARRAY_SIZE(byt_wm5102_pins));
	अगर (ret) अणु
		dev_err(card->dev, "Error creating jack: %d\n", ret);
		वापस ret;
	पूर्ण

	snd_soc_component_set_jack(component, &priv->jack, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक byt_wm5102_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
						      SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
							  SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret;

	/* The DSP will covert the FE rate to 48k, stereo */
	rate->min = 48000;
	rate->max = 48000;
	channels->min = 2;
	channels->max = 2;

	/* set SSP0 to 16-bit */
	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);

	/*
	 * Default mode क्रम SSP configuration is TDM 4 slot, override config
	 * with explicit setting to I2S 2ch 16-bit. The word length is set with
	 * dai_set_tdm_slot() since there is no other API exposed
	 */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0),
				  SND_SOC_DAIFMT_I2S     |
				  SND_SOC_DAIFMT_NB_NF   |
				  SND_SOC_DAIFMT_CBS_CFS);
	अगर (ret) अणु
		dev_err(rtd->dev, "Error setting format to I2S: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2, 16);
	अगर (ret) अणु
		dev_err(rtd->dev, "Error setting I2S config: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_wm5102_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					    SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops byt_wm5102_aअगर1_ops = अणु
	.startup = byt_wm5102_aअगर1_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp0_port,
	DAILINK_COMP_ARRAY(COMP_CPU("ssp0-port")));

SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC(
	/*
	 * Note there is no need to overग_लिखो the codec-name as is करोne in
	 * other bytcr machine drivers, because the codec is a MFD child-dev.
	 */
	"wm5102-codec",
	"wm5102-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link byt_wm5102_dais[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Baytrail Audio Port",
		.stream_name = "Baytrail Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &byt_wm5102_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),

	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &byt_wm5102_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
		/* back ends */
	अणु
		/*
		 * This must be named SSP2-Codec even though this machine driver
		 * always uses SSP0. Most machine drivers support both and dynamically
		 * update the dailink to poपूर्णांक to SSP0 or SSP2, जबतक keeping the name
		 * as "SSP2-Codec". The SOF tplg files hardcode the "SSP2-Codec" even
		 * in the byt-foo-ssp0.tplg versions because the other machine-drivers
		 * use "SSP2-Codec" even when SSP0 is used.
		 */
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBS_CFS,
		.be_hw_params_fixup = byt_wm5102_codec_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.init = byt_wm5102_init,
		SND_SOC_DAILINK_REG(ssp0_port, ssp0_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht wm5102" /* card name will be 'sof-bytcht wm5102' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bytcr-wm5102"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card byt_wm5102_card = अणु
	.owner = THIS_MODULE,
	.dai_link = byt_wm5102_dais,
	.num_links = ARRAY_SIZE(byt_wm5102_dais),
	.dapm_widमाला_लो = byt_wm5102_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(byt_wm5102_widमाला_लो),
	.dapm_routes = byt_wm5102_audio_map,
	.num_dapm_routes = ARRAY_SIZE(byt_wm5102_audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक snd_byt_wm5102_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अक्षर codec_name[SND_ACPI_I2C_ID_LEN];
	काष्ठा device *dev = &pdev->dev;
	काष्ठा byt_wm5102_निजी *priv;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा acpi_device *adev;
	काष्ठा device *codec_dev;
	bool sof_parent;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_ATOMIC);
	अगर (!priv)
		वापस -ENOMEM;

	/* Get MCLK */
	priv->mclk = devm_clk_get(dev, "pmc_plt_clk_3");
	अगर (IS_ERR(priv->mclk))
		वापस dev_err_probe(dev, PTR_ERR(priv->mclk), "getting pmc_plt_clk_3\n");

	/*
	 * Get speaker VDD enable GPIO:
	 * 1. Get codec-device-name
	 * 2. Get codec-device
	 * 3. Get GPIO from codec-device
	 */
	mach = dev->platक्रमm_data;
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (!adev) अणु
		dev_err(dev, "Error cannot find acpi-dev for codec\n");
		वापस -ENOENT;
	पूर्ण
	snम_लिखो(codec_name, माप(codec_name), "spi-%s", acpi_dev_name(adev));
	put_device(&adev->dev);

	codec_dev = bus_find_device_by_name(&spi_bus_type, शून्य, codec_name);
	अगर (!codec_dev)
		वापस -EPROBE_DEFER;

	/* Note no devm_ here since we call gpiod_get on codec_dev rather then dev */
	priv->spkvdd_en_gpio = gpiod_get(codec_dev, "wlf,spkvdd-ena", GPIOD_OUT_LOW);
	put_device(codec_dev);

	अगर (IS_ERR(priv->spkvdd_en_gpio))
		वापस dev_err_probe(dev, PTR_ERR(priv->spkvdd_en_gpio), "getting spkvdd-GPIO\n");

	/* override platक्रमm name, अगर required */
	byt_wm5102_card.dev = dev;
	platक्रमm_name = mach->mach_params.platक्रमm;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&byt_wm5102_card, platक्रमm_name);
	अगर (ret)
		जाओ out_put_gpio;

	/* set card and driver name and pm-ops */
	sof_parent = snd_soc_acpi_sof_parent(dev);
	अगर (sof_parent) अणु
		byt_wm5102_card.name = SOF_CARD_NAME;
		byt_wm5102_card.driver_name = SOF_DRIVER_NAME;
		dev->driver->pm = &snd_soc_pm_ops;
	पूर्ण अन्यथा अणु
		byt_wm5102_card.name = CARD_NAME;
		byt_wm5102_card.driver_name = DRIVER_NAME;
	पूर्ण

	snd_soc_card_set_drvdata(&byt_wm5102_card, priv);
	ret = devm_snd_soc_रेजिस्टर_card(dev, &byt_wm5102_card);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "registering card\n");
		जाओ out_put_gpio;
	पूर्ण

	platक्रमm_set_drvdata(pdev, &byt_wm5102_card);
	वापस 0;

out_put_gpio:
	gpiod_put(priv->spkvdd_en_gpio);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_byt_wm5102_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा byt_wm5102_निजी *priv = snd_soc_card_get_drvdata(card);

	gpiod_put(priv->spkvdd_en_gpio);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_byt_wm5102_mc_driver = अणु
	.driver = अणु
		.name = "bytcr_wm5102",
	पूर्ण,
	.probe = snd_byt_wm5102_mc_probe,
	.हटाओ = snd_byt_wm5102_mc_हटाओ,
पूर्ण;

module_platक्रमm_driver(snd_byt_wm5102_mc_driver);

MODULE_DESCRIPTION("ASoC Baytrail with WM5102 codec machine driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcr_wm5102");
