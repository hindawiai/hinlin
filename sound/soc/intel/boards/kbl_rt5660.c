<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2018-19 Canonical Corporation.

/*
 * Intel Kabylake I2S Machine Driver with RT5660 Codec
 *
 * Modअगरied from:
 *   Intel Kabylake I2S Machine driver supporting MAXIM98357a and
 *   DA7219 codecs
 * Also referred to:
 *   Intel Broadwell I2S Machine driver supporting RT5677 codec
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "../../codecs/rt5660.h"

#घोषणा KBL_RT5660_CODEC_DAI "rt5660-aif1"
#घोषणा DUAL_CHANNEL 2

अटल काष्ठा snd_soc_card *kabylake_audio_card;
अटल काष्ठा snd_soc_jack skylake_hdmi[3];
अटल काष्ठा snd_soc_jack lineout_jack;
अटल काष्ठा snd_soc_jack mic_jack;

काष्ठा kbl_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा kbl_codec_निजी अणु
	काष्ठा gpio_desc *gpio_lo_mute;
	काष्ठा list_head hdmi_pcm_list;
पूर्ण;

क्रमागत अणु
	KBL_DPCM_AUDIO_PB = 0,
	KBL_DPCM_AUDIO_CP,
	KBL_DPCM_AUDIO_HDMI1_PB,
	KBL_DPCM_AUDIO_HDMI2_PB,
	KBL_DPCM_AUDIO_HDMI3_PB,
पूर्ण;

#घोषणा GPIO_LINEOUT_MUTE_INDEX 0
#घोषणा GPIO_LINEOUT_DET_INDEX 3
#घोषणा GPIO_LINEIN_DET_INDEX 4

अटल स्थिर काष्ठा acpi_gpio_params lineout_mute_gpio = अणु GPIO_LINEOUT_MUTE_INDEX, 0, true पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params lineout_det_gpio = अणु GPIO_LINEOUT_DET_INDEX, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params mic_det_gpio = अणु GPIO_LINEIN_DET_INDEX, 0, false पूर्ण;


अटल स्थिर काष्ठा acpi_gpio_mapping acpi_rt5660_gpios[] = अणु
	अणु "lineout-mute-gpios", &lineout_mute_gpio, 1 पूर्ण,
	अणु "lineout-det-gpios", &lineout_det_gpio, 1 पूर्ण,
	अणु "mic-det-gpios", &mic_det_gpio, 1 पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_pin lineout_jack_pin = अणु
	.pin	= "Line Out",
	.mask	= SND_JACK_LINEOUT,
पूर्ण;

अटल काष्ठा snd_soc_jack_pin mic_jack_pin = अणु
	.pin	= "Line In",
	.mask	= SND_JACK_MICROPHONE,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio lineout_jack_gpio = अणु
	.name			= "lineout-det",
	.report			= SND_JACK_LINEOUT,
	.debounce_समय		= 200,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio mic_jack_gpio = अणु
	.name			= "mic-det",
	.report			= SND_JACK_MICROPHONE,
	.debounce_समय		= 200,
पूर्ण;

अटल पूर्णांक kabylake_5660_event_lineout(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा kbl_codec_निजी *priv = snd_soc_card_get_drvdata(dapm->card);

	gpiod_set_value_cansleep(priv->gpio_lo_mute,
			!(SND_SOC_DAPM_EVENT_ON(event)));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new kabylake_rt5660_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Line In"),
	SOC_DAPM_PIN_SWITCH("Line Out"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget kabylake_rt5660_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("Line In", शून्य),
	SND_SOC_DAPM_LINE("Line Out", kabylake_5660_event_lineout),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route kabylake_rt5660_map[] = अणु
	/* other jacks */
	अणु"IN1P", शून्य, "Line In"पूर्ण,
	अणु"IN2P", शून्य, "Line In"पूर्ण,
	अणु"Line Out", शून्य, "LOUTR"पूर्ण,
	अणु"Line Out", शून्य, "LOUTL"पूर्ण,

	/* CODEC BE connections */
	अणु "AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु "ssp0 Tx", शून्य, "codec0_out"पूर्ण,

	अणु "codec0_in", शून्य, "ssp0 Rx" पूर्ण,
	अणु "ssp0 Rx", शून्य, "AIF1 Capture" पूर्ण,

	अणु "hifi1", शून्य, "iDisp1 Tx"पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out"पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx"पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out"पूर्ण,
	अणु "hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
पूर्ण;

अटल पूर्णांक kabylake_ssp0_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	/* The ADSP will convert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	chan->min = chan->max = DUAL_CHANNEL;

	/* set SSP0 to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_rt5660_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	ret = devm_acpi_dev_add_driver_gpios(component->dev, acpi_rt5660_gpios);
	अगर (ret)
		dev_warn(component->dev, "Failed to add driver gpios\n");

	/* Request rt5660 GPIO क्रम lineout mute control, वापस अगर fails */
	ctx->gpio_lo_mute = gpiod_get(component->dev, "lineout-mute",
				      GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->gpio_lo_mute)) अणु
		dev_err(component->dev, "Can't find GPIO_MUTE# gpio\n");
		वापस PTR_ERR(ctx->gpio_lo_mute);
	पूर्ण

	/* Create and initialize headphone jack, this jack is not mandatory, करोn't वापस अगर fails */
	ret = snd_soc_card_jack_new(rtd->card, "Lineout Jack",
				    SND_JACK_LINEOUT, &lineout_jack,
				    &lineout_jack_pin, 1);
	अगर (ret)
		dev_warn(component->dev, "Can't create Lineout jack\n");
	अन्यथा अणु
		lineout_jack_gpio.gpiod_dev = component->dev;
		ret = snd_soc_jack_add_gpios(&lineout_jack, 1,
					     &lineout_jack_gpio);
		अगर (ret)
			dev_warn(component->dev, "Can't add Lineout jack gpio\n");
	पूर्ण

	/* Create and initialize mic jack, this jack is not mandatory, करोn't वापस अगर fails */
	ret = snd_soc_card_jack_new(rtd->card, "Mic Jack",
				    SND_JACK_MICROPHONE, &mic_jack,
				    &mic_jack_pin, 1);
	अगर (ret)
		dev_warn(component->dev, "Can't create mic jack\n");
	अन्यथा अणु
		mic_jack_gpio.gpiod_dev = component->dev;
		ret = snd_soc_jack_add_gpios(&mic_jack, 1, &mic_jack_gpio);
		अगर (ret)
			dev_warn(component->dev, "Can't add mic jack gpio\n");
	पूर्ण

	/* Here we enable some dapms in advance to reduce the pop noise क्रम recording via line-in */
	snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
	snd_soc_dapm_क्रमce_enable_pin(dapm, "BST1");
	snd_soc_dapm_क्रमce_enable_pin(dapm, "BST2");

	वापस 0;
पूर्ण

अटल व्योम kabylake_rt5660_codec_निकास(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);

	/*
	 * The .निकास() can be reached without going through the .init()
	 * so explicitly test अगर the gpiod is valid
	 */
	अगर (!IS_ERR_OR_शून्य(ctx->gpio_lo_mute))
		gpiod_put(ctx->gpio_lo_mute);
पूर्ण

अटल पूर्णांक kabylake_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक device)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा kbl_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = device;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_hdmi1_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस kabylake_hdmi_init(rtd, KBL_DPCM_AUDIO_HDMI1_PB);
पूर्ण

अटल पूर्णांक kabylake_hdmi2_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस kabylake_hdmi_init(rtd, KBL_DPCM_AUDIO_HDMI2_PB);
पूर्ण

अटल पूर्णांक kabylake_hdmi3_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस kabylake_hdmi_init(rtd, KBL_DPCM_AUDIO_HDMI3_PB);
पूर्ण

अटल पूर्णांक kabylake_rt5660_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai,
				     RT5660_SCLK_S_PLL1, params_rate(params) * 512,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(codec_dai, 0,
				  RT5660_PLL1_S_BCLK,
				  params_rate(params) * 50,
				  params_rate(params) * 512);
	अगर (ret < 0)
		dev_err(codec_dai->dev, "can't set codec pll: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops kabylake_rt5660_ops = अणु
	.hw_params = kabylake_rt5660_hw_params,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list  = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	DUAL_CHANNEL,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक kbl_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/*
	 * On this platक्रमm क्रम PCM device we support,
	 * 48Khz
	 * stereo
	 * 16 bit audio
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &स्थिरraपूर्णांकs_channels);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops kabylake_rt5660_fe_ops = अणु
	.startup = kbl_fe_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(hdmi1,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI1 Pin")));

SND_SOC_DAILINK_DEF(hdmi2,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI2 Pin")));

SND_SOC_DAILINK_DEF(hdmi3,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI3 Pin")));

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC3277:00", KBL_RT5660_CODEC_DAI)));

SND_SOC_DAILINK_DEF(idisp1_pin,
		    DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(idisp3_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAILINK_DEF(idisp3_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi3")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

/* kabylake digital audio पूर्णांकerface glue - connects rt5660 codec <--> CPU */
अटल काष्ठा snd_soc_dai_link kabylake_rt5660_dais[] = अणु
	/* Front End DAI links */
	[KBL_DPCM_AUDIO_PB] = अणु
		.name = "Kbl Audio Port",
		.stream_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &kabylake_rt5660_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_CP] = अणु
		.name = "Kbl Audio Capture Port",
		.stream_name = "Audio Record",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		.ops = &kabylake_rt5660_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HDMI1_PB] = अणु
		.name = "Kbl HDMI Port1",
		.stream_name = "Hdmi1",
		.dpcm_playback = 1,
		.init = शून्य,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi1, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HDMI2_PB] = अणु
		.name = "Kbl HDMI Port2",
		.stream_name = "Hdmi2",
		.dpcm_playback = 1,
		.init = शून्य,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi2, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HDMI3_PB] = अणु
		.name = "Kbl HDMI Port3",
		.stream_name = "Hdmi3",
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi3, dummy, platक्रमm),
	पूर्ण,

	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.init = kabylake_rt5660_codec_init,
		.निकास = kabylake_rt5660_codec_निकास,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
		SND_SOC_DAIFMT_NB_NF |
		SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = kabylake_ssp0_fixup,
		.ops = &kabylake_rt5660_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 1,
		.dpcm_playback = 1,
		.init = kabylake_hdmi1_init,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 2,
		.init = kabylake_hdmi2_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 3,
		.init = kabylake_hdmi3_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
पूर्ण;


#घोषणा NAME_SIZE	32
अटल पूर्णांक kabylake_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा kbl_hdmi_pcm *pcm;
	काष्ठा snd_soc_component *component = शून्य;
	पूर्णांक err, i = 0;
	अक्षर jack_name[NAME_SIZE];

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					SND_JACK_AVOUT, &skylake_hdmi[i],
					शून्य, 0);

		अगर (err)
			वापस err;

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
				&skylake_hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;

	पूर्ण

	अगर (!component)
		वापस -EINVAL;

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

/* kabylake audio machine driver क्रम rt5660 */
अटल काष्ठा snd_soc_card kabylake_audio_card_rt5660 = अणु
	.name = "kblrt5660",
	.owner = THIS_MODULE,
	.dai_link = kabylake_rt5660_dais,
	.num_links = ARRAY_SIZE(kabylake_rt5660_dais),
	.controls = kabylake_rt5660_controls,
	.num_controls = ARRAY_SIZE(kabylake_rt5660_controls),
	.dapm_widमाला_लो = kabylake_rt5660_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(kabylake_rt5660_widमाला_लो),
	.dapm_routes = kabylake_rt5660_map,
	.num_dapm_routes = ARRAY_SIZE(kabylake_rt5660_map),
	.fully_routed = true,
	.late_probe = kabylake_card_late_probe,
पूर्ण;

अटल पूर्णांक kabylake_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kbl_codec_निजी *ctx;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	kabylake_audio_card =
		(काष्ठा snd_soc_card *)pdev->id_entry->driver_data;

	kabylake_audio_card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(kabylake_audio_card, ctx);
	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, kabylake_audio_card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id kbl_board_ids[] = अणु
	अणु
		.name = "kbl_rt5660",
		.driver_data =
			(kernel_uदीर्घ_t)&kabylake_audio_card_rt5660,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver kabylake_audio = अणु
	.probe = kabylake_audio_probe,
	.driver = अणु
		.name = "kbl_rt5660",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = kbl_board_ids,
पूर्ण;

module_platक्रमm_driver(kabylake_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("Audio Machine driver-RT5660 in I2S mode");
MODULE_AUTHOR("Hui Wang <hui.wang@canonical.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:kbl_rt5660");
