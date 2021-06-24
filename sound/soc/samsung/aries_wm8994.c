<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/extcon.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/input-event-codes.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "i2s.h"
#समावेश "../codecs/wm8994.h"

#घोषणा ARIES_MCLK1_FREQ 24000000

काष्ठा aries_wm8994_variant अणु
	अचिन्हित पूर्णांक modem_dai_fmt;
	bool has_fm_radio;
पूर्ण;

काष्ठा aries_wm8994_data अणु
	काष्ठा extcon_dev *usb_extcon;
	काष्ठा regulator *reg_मुख्य_micbias;
	काष्ठा regulator *reg_headset_micbias;
	काष्ठा gpio_desc *gpio_headset_detect;
	काष्ठा gpio_desc *gpio_headset_key;
	काष्ठा gpio_desc *gpio_earpath_sel;
	काष्ठा iio_channel *adc;
	स्थिर काष्ठा aries_wm8994_variant *variant;
पूर्ण;

/* USB करोck */
अटल काष्ठा snd_soc_jack aries_करोck;

अटल काष्ठा snd_soc_jack_pin करोck_pins[] = अणु
	अणु
		.pin = "LINE",
		.mask = SND_JACK_LINEOUT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक aries_extcon_notअगरier(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ connected, व्योम *_cmd)
अणु
	अगर (connected)
		snd_soc_jack_report(&aries_करोck, SND_JACK_LINEOUT,
				SND_JACK_LINEOUT);
	अन्यथा
		snd_soc_jack_report(&aries_करोck, 0, SND_JACK_LINEOUT);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block aries_extcon_notअगरier_block = अणु
	.notअगरier_call = aries_extcon_notअगरier,
पूर्ण;

/* Headset jack */
अटल काष्ठा snd_soc_jack aries_headset;

अटल काष्ठा snd_soc_jack_pin jack_pins[] = अणु
	अणु
		.pin = "HP",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण, अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_zone headset_zones[] = अणु
	अणु
		.min_mv = 0,
		.max_mv = 241,
		.jack_type = SND_JACK_HEADPHONE,
	पूर्ण, अणु
		.min_mv = 242,
		.max_mv = 2980,
		.jack_type = SND_JACK_HEADSET,
	पूर्ण, अणु
		.min_mv = 2981,
		.max_mv = अच_पूर्णांक_उच्च,
		.jack_type = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल irqवापस_t headset_det_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा aries_wm8994_data *priv = (काष्ठा aries_wm8994_data *) data;
	पूर्णांक ret = 0;
	पूर्णांक समय_left_ms = 300;
	पूर्णांक adc;

	जबतक (समय_left_ms > 0) अणु
		अगर (!gpiod_get_value(priv->gpio_headset_detect)) अणु
			snd_soc_jack_report(&aries_headset, 0,
					SND_JACK_HEADSET);
			gpiod_set_value(priv->gpio_earpath_sel, 0);
			वापस IRQ_HANDLED;
		पूर्ण
		msleep(20);
		समय_left_ms -= 20;
	पूर्ण

	/* Temporarily enable micbias and earpath selector */
	ret = regulator_enable(priv->reg_headset_micbias);
	अगर (ret)
		pr_err("%s failed to enable micbias: %d", __func__, ret);

	gpiod_set_value(priv->gpio_earpath_sel, 1);

	ret = iio_पढ़ो_channel_processed(priv->adc, &adc);
	अगर (ret < 0) अणु
		/* failed to पढ़ो ADC, so assume headphone */
		pr_err("%s failed to read ADC, assuming headphones", __func__);
		snd_soc_jack_report(&aries_headset, SND_JACK_HEADPHONE,
				SND_JACK_HEADSET);
	पूर्ण अन्यथा अणु
		snd_soc_jack_report(&aries_headset,
				snd_soc_jack_get_type(&aries_headset, adc),
				SND_JACK_HEADSET);
	पूर्ण

	ret = regulator_disable(priv->reg_headset_micbias);
	अगर (ret)
		pr_err("%s failed disable micbias: %d", __func__, ret);

	/* Disable earpath selector when no mic connected */
	अगर (!(aries_headset.status & SND_JACK_MICROPHONE))
		gpiod_set_value(priv->gpio_earpath_sel, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक headset_button_check(व्योम *data)
अणु
	काष्ठा aries_wm8994_data *priv = (काष्ठा aries_wm8994_data *) data;

	/* Filter out keypresses when 4 pole jack not detected */
	अगर (gpiod_get_value_cansleep(priv->gpio_headset_key) &&
			aries_headset.status & SND_JACK_MICROPHONE)
		वापस SND_JACK_BTN_0;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_jack_gpio headset_button_gpio[] = अणु
	अणु
		.name = "Media Button",
		.report = SND_JACK_BTN_0,
		.debounce_समय  = 30,
		.jack_status_check = headset_button_check,
	पूर्ण,
पूर्ण;

अटल पूर्णांक aries_spk_cfg(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *component;
	पूर्णांक ret = 0;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	component = asoc_rtd_to_codec(rtd, 0)->component;

	/**
	 * We have an odd setup - the SPKMODE pin is pulled up so
	 * we only have access to the left side SPK configs,
	 * but SPKOUTR isn't bridged so when playing back in
	 * stereo, we only get the left hand channel.  The only
	 * option we're left with is to क्रमce the AIF पूर्णांकo mono
	 * mode.
	 */
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		ret = snd_soc_component_update_bits(component,
				WM8994_AIF1_DAC1_FILTERS_1,
				WM8994_AIF1DAC1_MONO, WM8994_AIF1DAC1_MONO);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		ret = snd_soc_component_update_bits(component,
				WM8994_AIF1_DAC1_FILTERS_1,
				WM8994_AIF1DAC1_MONO, 0);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aries_मुख्य_bias(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा aries_wm8994_data *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = regulator_enable(priv->reg_मुख्य_micbias);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		ret = regulator_disable(priv->reg_मुख्य_micbias);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aries_headset_bias(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा aries_wm8994_data *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = regulator_enable(priv->reg_headset_micbias);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		ret = regulator_disable(priv->reg_headset_micbias);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new aries_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Modem In"),
	SOC_DAPM_PIN_SWITCH("Modem Out"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aries_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("HP", शून्य),

	SND_SOC_DAPM_SPK("SPK", aries_spk_cfg),
	SND_SOC_DAPM_SPK("RCV", शून्य),

	SND_SOC_DAPM_LINE("LINE", शून्य),

	SND_SOC_DAPM_MIC("Main Mic", aries_मुख्य_bias),
	SND_SOC_DAPM_MIC("Headset Mic", aries_headset_bias),

	SND_SOC_DAPM_MIC("Bluetooth Mic", शून्य),
	SND_SOC_DAPM_SPK("Bluetooth SPK", शून्य),

	SND_SOC_DAPM_LINE("Modem In", शून्य),
	SND_SOC_DAPM_LINE("Modem Out", शून्य),

	/* This must be last as it is conditionally not used */
	SND_SOC_DAPM_LINE("FM In", शून्य),
पूर्ण;

अटल पूर्णांक aries_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक pll_out;
	पूर्णांक ret;

	/* AIF1CLK should be >=3MHz क्रम optimal perक्रमmance */
	अगर (params_width(params) == 24)
		pll_out = params_rate(params) * 384;
	अन्यथा अगर (params_rate(params) == 8000 || params_rate(params) == 11025)
		pll_out = params_rate(params) * 512;
	अन्यथा
		pll_out = params_rate(params) * 256;

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1, WM8994_FLL_SRC_MCLK1,
				ARIES_MCLK1_FREQ, pll_out);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL1,
				pll_out, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक aries_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	/* Switch sysclk to MCLK1 */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_MCLK1,
				ARIES_MCLK1_FREQ, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* Stop PLL */
	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1, WM8994_FLL_SRC_MCLK1,
				ARIES_MCLK1_FREQ, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Main DAI operations
 */
अटल काष्ठा snd_soc_ops aries_ops = अणु
	.hw_params = aries_hw_params,
	.hw_मुक्त = aries_hw_मुक्त,
पूर्ण;

अटल पूर्णांक aries_baseband_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक pll_out;
	पूर्णांक ret;

	pll_out = 8000 * 512;

	/* Set the codec FLL */
	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL2, WM8994_FLL_SRC_MCLK1,
			ARIES_MCLK1_FREQ, pll_out);
	अगर (ret < 0)
		वापस ret;

	/* Set the codec प्रणाली घड़ी */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL2,
			pll_out, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक aries_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा aries_wm8994_data *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret, irq;

	ret = snd_soc_card_jack_new(card, "Dock", SND_JACK_LINEOUT,
			&aries_करोck, करोck_pins, ARRAY_SIZE(करोck_pins));
	अगर (ret)
		वापस ret;

	ret = devm_extcon_रेजिस्टर_notअगरier(card->dev,
			priv->usb_extcon, EXTCON_JACK_LINE_OUT,
			&aries_extcon_notअगरier_block);
	अगर (ret)
		वापस ret;

	अगर (extcon_get_state(priv->usb_extcon,
			EXTCON_JACK_LINE_OUT) > 0)
		snd_soc_jack_report(&aries_करोck, SND_JACK_LINEOUT,
				SND_JACK_LINEOUT);
	अन्यथा
		snd_soc_jack_report(&aries_करोck, 0, SND_JACK_LINEOUT);

	ret = snd_soc_card_jack_new(card, "Headset",
			SND_JACK_HEADSET | SND_JACK_BTN_0,
			&aries_headset,
			jack_pins, ARRAY_SIZE(jack_pins));
	अगर (ret)
		वापस ret;

	ret = snd_soc_jack_add_zones(&aries_headset, ARRAY_SIZE(headset_zones),
			headset_zones);
	अगर (ret)
		वापस ret;

	irq = gpiod_to_irq(priv->gpio_headset_detect);
	अगर (irq < 0) अणु
		dev_err(card->dev, "Failed to map headset detect gpio to irq");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(card->dev, irq, शून्य,
			headset_det_irq_thपढ़ो,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			IRQF_ONESHOT, "headset_detect", priv);
	अगर (ret) अणु
		dev_err(card->dev, "Failed to request headset detect irq");
		वापस ret;
	पूर्ण

	headset_button_gpio[0].data = priv;
	headset_button_gpio[0].desc = priv->gpio_headset_key;

	snd_jack_set_key(aries_headset.jack, SND_JACK_BTN_0, KEY_MEDIA);

	वापस snd_soc_jack_add_gpios(&aries_headset,
			ARRAY_SIZE(headset_button_gpio), headset_button_gpio);
पूर्ण

अटल स्थिर काष्ठा snd_soc_pcm_stream baseband_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rate_min = 8000,
	.rate_max = 8000,
	.channels_min = 1,
	.channels_max = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_pcm_stream bluetooth_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rate_min = 8000,
	.rate_max = 8000,
	.channels_min = 1,
	.channels_max = 2,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aries_modem_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("Modem RX"),
	SND_SOC_DAPM_OUTPUT("Modem TX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route aries_modem_routes[] = अणु
	अणु "Modem Capture", शून्य, "Modem RX" पूर्ण,
	अणु "Modem TX", शून्य, "Modem Playback" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver aries_component = अणु
	.name			= "aries-audio",
	.dapm_widमाला_लो		= aries_modem_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(aries_modem_widमाला_लो),
	.dapm_routes		= aries_modem_routes,
	.num_dapm_routes	= ARRAY_SIZE(aries_modem_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aries_ext_dai[] = अणु
	अणु
		.name = "Voice call",
		.playback = अणु
			.stream_name = "Modem Playback",
			.channels_min = 1,
			.channels_max = 1,
			.rate_min = 8000,
			.rate_max = 8000,
			.rates = SNDRV_PCM_RATE_8000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "Modem Capture",
			.channels_min = 1,
			.channels_max = 1,
			.rate_min = 8000,
			.rate_max = 8000,
			.rates = SNDRV_PCM_RATE_8000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
	पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(aअगर1,
	DAILINK_COMP_ARRAY(COMP_CPU(SAMSUNG_I2S_DAI)),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(baseband,
	DAILINK_COMP_ARRAY(COMP_CPU("Voice call")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif2")));

SND_SOC_DAILINK_DEFS(bluetooth,
	DAILINK_COMP_ARRAY(COMP_CPU("bt-sco-pcm")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif3")));

अटल काष्ठा snd_soc_dai_link aries_dai[] = अणु
	अणु
		.name = "WM8994 AIF1",
		.stream_name = "HiFi",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		.ops = &aries_ops,
		SND_SOC_DAILINK_REG(aअगर1),
	पूर्ण,
	अणु
		.name = "WM8994 AIF2",
		.stream_name = "Baseband",
		.init = &aries_baseband_init,
		.params = &baseband_params,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(baseband),
	पूर्ण,
	अणु
		.name = "WM8994 AIF3",
		.stream_name = "Bluetooth",
		.params = &bluetooth_params,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(bluetooth),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card aries_card = अणु
	.name = "ARIES",
	.owner = THIS_MODULE,
	.dai_link = aries_dai,
	.num_links = ARRAY_SIZE(aries_dai),
	.controls = aries_controls,
	.num_controls = ARRAY_SIZE(aries_controls),
	.dapm_widमाला_लो = aries_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(aries_dapm_widमाला_लो),
	.late_probe = aries_late_probe,
पूर्ण;

अटल स्थिर काष्ठा aries_wm8994_variant fascinate4g_variant = अणु
	.modem_dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBS_CFS
		| SND_SOC_DAIFMT_IB_NF,
	.has_fm_radio = false,
पूर्ण;

अटल स्थिर काष्ठा aries_wm8994_variant aries_variant = अणु
	.modem_dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBM_CFM
		| SND_SOC_DAIFMT_IB_NF,
	.has_fm_radio = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id samsung_wm8994_of_match[] = अणु
	अणु
		.compatible = "samsung,fascinate4g-wm8994",
		.data = &fascinate4g_variant,
	पूर्ण,
	अणु
		.compatible = "samsung,aries-wm8994",
		.data = &aries_variant,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, samsung_wm8994_of_match);

अटल पूर्णांक aries_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *cpu, *codec, *extcon_np;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_card *card = &aries_card;
	काष्ठा aries_wm8994_data *priv;
	काष्ठा snd_soc_dai_link *dai_link;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret, i;

	अगर (!np)
		वापस -EINVAL;

	card->dev = dev;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(card, priv);

	match = of_match_node(samsung_wm8994_of_match, np);
	priv->variant = match->data;

	/* Remove FM widget अगर not present */
	अगर (!priv->variant->has_fm_radio)
		card->num_dapm_widमाला_लो--;

	priv->reg_मुख्य_micbias = devm_regulator_get(dev, "main-micbias");
	अगर (IS_ERR(priv->reg_मुख्य_micbias)) अणु
		dev_err(dev, "Failed to get main micbias regulator\n");
		वापस PTR_ERR(priv->reg_मुख्य_micbias);
	पूर्ण

	priv->reg_headset_micbias = devm_regulator_get(dev, "headset-micbias");
	अगर (IS_ERR(priv->reg_headset_micbias)) अणु
		dev_err(dev, "Failed to get headset micbias regulator\n");
		वापस PTR_ERR(priv->reg_headset_micbias);
	पूर्ण

	priv->gpio_earpath_sel = devm_gpiod_get(dev, "earpath-sel",
			GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpio_earpath_sel)) अणु
		dev_err(dev, "Failed to get earpath selector gpio");
		वापस PTR_ERR(priv->gpio_earpath_sel);
	पूर्ण

	extcon_np = of_parse_phandle(np, "extcon", 0);
	priv->usb_extcon = extcon_find_edev_by_node(extcon_np);
	अगर (IS_ERR(priv->usb_extcon)) अणु
		अगर (PTR_ERR(priv->usb_extcon) != -EPROBE_DEFER)
			dev_err(dev, "Failed to get extcon device");
		वापस PTR_ERR(priv->usb_extcon);
	पूर्ण
	of_node_put(extcon_np);

	priv->adc = devm_iio_channel_get(dev, "headset-detect");
	अगर (IS_ERR(priv->adc)) अणु
		अगर (PTR_ERR(priv->adc) != -EPROBE_DEFER)
			dev_err(dev, "Failed to get ADC channel");
		वापस PTR_ERR(priv->adc);
	पूर्ण
	अगर (priv->adc->channel->type != IIO_VOLTAGE)
		वापस -EINVAL;

	priv->gpio_headset_key = devm_gpiod_get(dev, "headset-key",
			GPIOD_IN);
	अगर (IS_ERR(priv->gpio_headset_key)) अणु
		dev_err(dev, "Failed to get headset key gpio");
		वापस PTR_ERR(priv->gpio_headset_key);
	पूर्ण

	priv->gpio_headset_detect = devm_gpiod_get(dev,
			"headset-detect", GPIOD_IN);
	अगर (IS_ERR(priv->gpio_headset_detect)) अणु
		dev_err(dev, "Failed to get headset detect gpio");
		वापस PTR_ERR(priv->gpio_headset_detect);
	पूर्ण

	/* Update card-name अगर provided through DT, अन्यथा use शेष name */
	snd_soc_of_parse_card_name(card, "model");

	ret = snd_soc_of_parse_audio_routing(card, "samsung,audio-routing");
	अगर (ret < 0) अणु
		dev_err(dev, "Audio routing invalid/unspecified\n");
		वापस ret;
	पूर्ण

	aries_dai[1].dai_fmt = priv->variant->modem_dai_fmt;

	cpu = of_get_child_by_name(dev->of_node, "cpu");
	अगर (!cpu)
		वापस -EINVAL;

	codec = of_get_child_by_name(dev->of_node, "codec");
	अगर (!codec)
		वापस -EINVAL;

	क्रम_each_card_prelinks(card, i, dai_link) अणु
		dai_link->codecs->of_node = of_parse_phandle(codec,
				"sound-dai", 0);
		अगर (!dai_link->codecs->of_node) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Set CPU and platक्रमm of_node क्रम मुख्य DAI */
	aries_dai[0].cpus->of_node = of_parse_phandle(cpu,
			"sound-dai", 0);
	अगर (!aries_dai[0].cpus->of_node) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	aries_dai[0].platक्रमms->of_node = aries_dai[0].cpus->of_node;

	/* Set CPU of_node क्रम BT DAI */
	aries_dai[2].cpus->of_node = of_parse_phandle(cpu,
			"sound-dai", 1);
	अगर (!aries_dai[2].cpus->of_node) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &aries_component,
				aries_ext_dai, ARRAY_SIZE(aries_ext_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register component: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret)
		dev_err(dev, "snd_soc_register_card() failed:%d\n", ret);

out:
	of_node_put(cpu);
	of_node_put(codec);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver aries_audio_driver = अणु
	.driver		= अणु
		.name	= "aries-audio-wm8994",
		.of_match_table = of_match_ptr(samsung_wm8994_of_match),
		.pm	= &snd_soc_pm_ops,
	पूर्ण,
	.probe		= aries_audio_probe,
पूर्ण;

module_platक्रमm_driver(aries_audio_driver);

MODULE_DESCRIPTION("ALSA SoC ARIES WM8994");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:aries-audio-wm8994");
