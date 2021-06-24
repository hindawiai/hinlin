<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cht_bsw_rt5672.c - ASoc Machine driver क्रम Intel Cherryview-based platक्रमms
 *                     Cherrytrail and Braswell, with RT5672 codec.
 *
 *  Copyright (C) 2014 Intel Corp
 *  Author: Subhransu S. Prusty <subhransu.s.prusty@पूर्णांकel.com>
 *          Mengकरोng Lin <mengकरोng.lin@पूर्णांकel.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/rt5670.h"
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../common/soc-intel-quirks.h"


/* The platक्रमm घड़ी #3 outमाला_दो 19.2Mhz घड़ी to codec as I2S MCLK */
#घोषणा CHT_PLAT_CLK_3_HZ	19200000
#घोषणा CHT_CODEC_DAI	"rt5670-aif1"

काष्ठा cht_mc_निजी अणु
	काष्ठा snd_soc_jack headset;
	अक्षर codec_name[SND_ACPI_I2C_ID_LEN];
	काष्ठा clk *mclk;
	bool use_ssp0;
पूर्ण;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin cht_bsw_headset_pins[] = अणु
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	codec_dai = snd_soc_card_get_codec_dai(card, CHT_CODEC_DAI);
	अगर (!codec_dai) अणु
		dev_err(card->dev, "Codec dai not found; Unable to set platform clock\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		अगर (ctx->mclk) अणु
			ret = clk_prepare_enable(ctx->mclk);
			अगर (ret < 0) अणु
				dev_err(card->dev,
					"could not configure MCLK state");
				वापस ret;
			पूर्ण
		पूर्ण

		/* set codec PLL source to the 19.2MHz platक्रमm घड़ी (MCLK) */
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT5670_PLL1_S_MCLK,
				CHT_PLAT_CLK_3_HZ, 48000 * 512);
		अगर (ret < 0) अणु
			dev_err(card->dev, "can't set codec pll: %d\n", ret);
			वापस ret;
		पूर्ण

		/* set codec sysclk source to PLL */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5670_SCLK_S_PLL1,
			48000 * 512, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(card->dev, "can't set codec sysclk: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Set codec sysclk source to its पूर्णांकernal घड़ी because codec
		 * PLL will be off when idle and MCLK will also be off by ACPI
		 * when codec is runसमय suspended. Codec needs घड़ी क्रम jack
		 * detection and button press.
		 */
		snd_soc_dai_set_sysclk(codec_dai, RT5670_SCLK_S_RCCLK,
				       48000 * 512, SND_SOC_CLOCK_IN);

		अगर (ctx->mclk)
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
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,
	अणु"DMIC L1", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC R1", शून्य, "Int Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"Ext Spk", शून्य, "SPOLP"पूर्ण,
	अणु"Ext Spk", शून्य, "SPOLN"पूर्ण,
	अणु"Ext Spk", शून्य, "SPORP"पूर्ण,
	अणु"Ext Spk", शून्य, "SPORN"पूर्ण,
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Int Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Ext Spk", शून्य, "Platform Clock"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_audio_ssp0_map[] = अणु
	अणु"AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_audio_ssp2_map[] = अणु
	अणु"AIF1 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF1 Capture"पूर्ण,
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

	/* set codec PLL source to the 19.2MHz platक्रमm घड़ी (MCLK) */
	ret = snd_soc_dai_set_pll(codec_dai, 0, RT5670_PLL1_S_MCLK,
				  CHT_PLAT_CLK_3_HZ, params_rate(params) * 512);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		वापस ret;
	पूर्ण

	/* set codec sysclk source to PLL */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5670_SCLK_S_PLL1,
				     params_rate(params) * 512,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params headset_gpios = अणु 0, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping cht_rt5672_gpios[] = अणु
	अणु "headset-gpios", &headset_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक cht_codec_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(runसमय, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(runसमय->card);

	अगर (devm_acpi_dev_add_driver_gpios(component->dev, cht_rt5672_gpios))
		dev_warn(runसमय->dev, "Unable to add GPIO mapping table\n");

	/* Select codec ASRC घड़ी source to track I2S1 घड़ी, because codec
	 * is in slave mode and 100fs I2S क्रमmat (BCLK = 100 * LRCLK) cannot
	 * be supported by RT5672. Otherwise, ASRC will be disabled and cause
	 * noise.
	 */
	rt5670_sel_asrc_clk_src(component,
				RT5670_DA_STEREO_FILTER
				| RT5670_DA_MONO_L_FILTER
				| RT5670_DA_MONO_R_FILTER
				| RT5670_AD_STEREO_FILTER
				| RT5670_AD_MONO_L_FILTER
				| RT5670_AD_MONO_R_FILTER,
				RT5670_CLK_SEL_I2S1_ASRC);

	अगर (ctx->use_ssp0) अणु
		ret = snd_soc_dapm_add_routes(&runसमय->card->dapm,
					      cht_audio_ssp0_map,
					      ARRAY_SIZE(cht_audio_ssp0_map));
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_add_routes(&runसमय->card->dapm,
					      cht_audio_ssp2_map,
					      ARRAY_SIZE(cht_audio_ssp2_map));
	पूर्ण
	अगर (ret)
		वापस ret;

        ret = snd_soc_card_jack_new(runसमय->card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2,
				    &ctx->headset,
				    cht_bsw_headset_pins,
				    ARRAY_SIZE(cht_bsw_headset_pins));
        अगर (ret)
                वापस ret;

	snd_jack_set_key(ctx->headset.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(ctx->headset.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(ctx->headset.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);

	rt5670_set_jack_detect(component, &ctx->headset);
	अगर (ctx->mclk) अणु
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

		अगर (ret) अणु
			dev_err(runसमय->dev, "unable to set MCLK rate\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cht_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret, bits;

	/* The DSP will covert the FE rate to 48k, stereo, 24bits */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	अगर (ctx->use_ssp0) अणु
		/* set SSP0 to 16-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);
		bits = 16;
	पूर्ण अन्यथा अणु
		/* set SSP2 to 24-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);
		bits = 24;
	पूर्ण

	/*
	 * The शेष mode क्रम the cpu-dai is TDM 4 slot. The शेष mode
	 * क्रम the codec-dai is I2S. So we need to either set the cpu-dai to
	 * I2S mode to match the codec-dai, or set the codec-dai to TDM 4 slot
	 * (or program both to yet another mode).
	 * One board, the Lenovo Miix 2 10, uses not 1 but 2 codecs connected
	 * to SSP2. The second piggy-backed, output-only codec is inside the
	 * keyboard-करोck (which has extra speakers). Unlike the मुख्य rt5672
	 * codec, we cannot configure this codec, it is hard coded to use
	 * 2 channel 24 bit I2S. For this to work we must use I2S mode on this
	 * board. Since we only support 2 channels anyways, there is no need
	 * क्रम TDM on any cht-bsw-rt5672 designs. So we use I2S 2ch everywhere.
	 */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0),
				  SND_SOC_DAIFMT_I2S     |
				  SND_SOC_DAIFMT_NB_NF   |
				  SND_SOC_DAIFMT_CBS_CFS);
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

अटल पूर्णांक cht_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops cht_aअगर1_ops = अणु
	.startup = cht_aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cht_be_ssp2_ops = अणु
	.hw_params = cht_aअगर1_hw_params,
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
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5670:00",
				      "rt5670-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link cht_dailink[] = अणु
	/* Front End DAI links */
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

	/* Back End DAI links */
	अणु
		/* SSP2 - Codec */
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.nonatomic = true,
		.init = cht_codec_init,
		.be_hw_params_fixup = cht_codec_fixup,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_be_ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल पूर्णांक cht_suspend_pre(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेदन(component->name,
			     ctx->codec_name, माप(ctx->codec_name))) अणु

			dev_dbg(component->dev, "disabling jack detect before going to suspend.\n");
			rt5670_jack_suspend(component);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cht_resume_post(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेदन(component->name,
			     ctx->codec_name, माप(ctx->codec_name))) अणु

			dev_dbg(component->dev, "enabling jack detect for resume.\n");
			rt5670_jack_resume(component);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht rt5672" /* card name will be 'sof-bytcht rt5672' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "cht-bsw-rt5672"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card snd_soc_card_cht = अणु
	.owner = THIS_MODULE,
	.dai_link = cht_dailink,
	.num_links = ARRAY_SIZE(cht_dailink),
	.dapm_widमाला_लो = cht_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cht_dapm_widमाला_लो),
	.dapm_routes = cht_audio_map,
	.num_dapm_routes = ARRAY_SIZE(cht_audio_map),
	.controls = cht_mc_controls,
	.num_controls = ARRAY_SIZE(cht_mc_controls),
	.suspend_pre = cht_suspend_pre,
	.resume_post = cht_resume_post,
पूर्ण;

#घोषणा RT5672_I2C_DEFAULT	"i2c-10EC5670:00"

अटल पूर्णांक snd_cht_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा cht_mc_निजी *drv;
	काष्ठा snd_soc_acpi_mach *mach = pdev->dev.platक्रमm_data;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा acpi_device *adev;
	bool sof_parent;
	पूर्णांक dai_index = 0;
	पूर्णांक i;

	drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	म_नकल(drv->codec_name, RT5672_I2C_DEFAULT);

	/* find index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(cht_dailink); i++) अणु
		अगर (!म_भेद(cht_dailink[i].codecs->name, RT5672_I2C_DEFAULT)) अणु
			dai_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(drv->codec_name, माप(drv->codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		put_device(&adev->dev);
		cht_dailink[dai_index].codecs->name = drv->codec_name;
	पूर्ण

	/* Use SSP0 on Bay Trail CR devices */
	अगर (soc_पूर्णांकel_is_byt() && mach->mach_params.acpi_ipc_irq_index == 0) अणु
		cht_dailink[dai_index].cpus->dai_name = "ssp0-port";
		drv->use_ssp0 = true;
	पूर्ण

	/* override plaक्रमm name, अगर required */
	snd_soc_card_cht.dev = &pdev->dev;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(&snd_soc_card_cht,
							platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	snd_soc_card_cht.components = rt5670_components();

	drv->mclk = devm_clk_get(&pdev->dev, "pmc_plt_clk_3");
	अगर (IS_ERR(drv->mclk)) अणु
		dev_err(&pdev->dev,
			"Failed to get MCLK from pmc_plt_clk_3: %ld\n",
			PTR_ERR(drv->mclk));
		वापस PTR_ERR(drv->mclk);
	पूर्ण
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

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
		pdev->dev.driver->pm = &snd_soc_pm_ops;

	/* रेजिस्टर the soc card */
	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &snd_soc_card_cht);
	अगर (ret_val) अणु
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &snd_soc_card_cht);
	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_cht_mc_driver = अणु
	.driver = अणु
		.name = "cht-bsw-rt5672",
	पूर्ण,
	.probe = snd_cht_mc_probe,
पूर्ण;

module_platक्रमm_driver(snd_cht_mc_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail CR Machine driver");
MODULE_AUTHOR("Subhransu S. Prusty, Mengdong Lin");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cht-bsw-rt5672");
