<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (c) 2020, The Linux Foundation. All rights reserved.
//
// sc7180.c -- ALSA SoC Machine driver क्रम SC7180

#समावेश <dt-bindings/sound/sc7180-lpass.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <uapi/linux/input-event-codes.h>

#समावेश "../codecs/rt5682.h"
#समावेश "common.h"
#समावेश "lpass.h"

#घोषणा DEFAULT_MCLK_RATE		19200000
#घोषणा RT5682_PLL1_FREQ (48000 * 512)

#घोषणा DRIVER_NAME "SC7180"

काष्ठा sc7180_snd_data अणु
	काष्ठा snd_soc_card card;
	u32 pri_mi2s_clk_count;
	काष्ठा snd_soc_jack hs_jack;
	काष्ठा snd_soc_jack hdmi_jack;
	काष्ठा gpio_desc *dmic_sel;
	पूर्णांक dmic_चयन;
पूर्ण;

अटल व्योम sc7180_jack_मुक्त(काष्ठा snd_jack *jack)
अणु
	काष्ठा snd_soc_component *component = jack->निजी_data;

	snd_soc_component_set_jack(component, शून्य, शून्य);
पूर्ण

अटल पूर्णांक sc7180_headset_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा sc7180_snd_data *pdata = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_jack *jack;
	पूर्णांक rval;

	rval = snd_soc_card_jack_new(
			card, "Headset Jack",
			SND_JACK_HEADSET |
			SND_JACK_HEADPHONE |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3,
			&pdata->hs_jack, शून्य, 0);

	अगर (rval < 0) अणु
		dev_err(card->dev, "Unable to add Headset Jack\n");
		वापस rval;
	पूर्ण

	jack = pdata->hs_jack.jack;

	snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	jack->निजी_data = component;
	jack->निजी_मुक्त = sc7180_jack_मुक्त;

	वापस snd_soc_component_set_jack(component, &pdata->hs_jack, शून्य);
पूर्ण

अटल पूर्णांक sc7180_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा sc7180_snd_data *pdata = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_jack *jack;
	पूर्णांक rval;

	rval = snd_soc_card_jack_new(
			card, "HDMI Jack",
			SND_JACK_LINEOUT,
			&pdata->hdmi_jack, शून्य, 0);

	अगर (rval < 0) अणु
		dev_err(card->dev, "Unable to add HDMI Jack\n");
		वापस rval;
	पूर्ण

	jack = pdata->hdmi_jack.jack;
	jack->निजी_data = component;
	jack->निजी_मुक्त = sc7180_jack_मुक्त;

	वापस snd_soc_component_set_jack(component, &pdata->hdmi_jack, शून्य);
पूर्ण

अटल पूर्णांक sc7180_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	चयन (cpu_dai->id) अणु
	हाल MI2S_PRIMARY:
		वापस sc7180_headset_init(rtd);
	हाल MI2S_SECONDARY:
		वापस 0;
	हाल LPASS_DP_RX:
		वापस sc7180_hdmi_init(rtd);
	शेष:
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sc7180_snd_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा sc7180_snd_data *data = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	चयन (cpu_dai->id) अणु
	हाल MI2S_PRIMARY:
		अगर (++data->pri_mi2s_clk_count == 1) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
					       LPASS_MCLK0,
					       DEFAULT_MCLK_RATE,
					       SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण

		snd_soc_dai_set_fmt(codec_dai,
				    SND_SOC_DAIFMT_CBS_CFS |
				    SND_SOC_DAIFMT_NB_NF |
				    SND_SOC_DAIFMT_I2S);

		/* Configure PLL1 क्रम codec */
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT5682_PLL1_S_MCLK,
					  DEFAULT_MCLK_RATE, RT5682_PLL1_FREQ);
		अगर (ret) अणु
			dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
			वापस ret;
		पूर्ण

		/* Configure sysclk क्रम codec */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL1,
					     RT5682_PLL1_FREQ,
					     SND_SOC_CLOCK_IN);
		अगर (ret)
			dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n",
				ret);

		अवरोध;
	हाल MI2S_SECONDARY:
		अवरोध;
	हाल LPASS_DP_RX:
		अवरोध;
	शेष:
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dmic_get(काष्ठा snd_kcontrol *kcontrol,
		    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा sc7180_snd_data *data = snd_soc_card_get_drvdata(dapm->card);

	ucontrol->value.पूर्णांकeger.value[0] = data->dmic_चयन;
	वापस 0;
पूर्ण

अटल पूर्णांक dmic_set(काष्ठा snd_kcontrol *kcontrol,
		    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा sc7180_snd_data *data = snd_soc_card_get_drvdata(dapm->card);

	data->dmic_चयन = ucontrol->value.पूर्णांकeger.value[0];
	gpiod_set_value(data->dmic_sel, data->dmic_चयन);
	वापस 0;
पूर्ण

अटल व्योम sc7180_snd_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा sc7180_snd_data *data = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	चयन (cpu_dai->id) अणु
	हाल MI2S_PRIMARY:
		अगर (--data->pri_mi2s_clk_count == 0) अणु
			snd_soc_dai_set_sysclk(cpu_dai,
					       LPASS_MCLK0,
					       0,
					       SNDRV_PCM_STREAM_PLAYBACK);
		पूर्ण
		अवरोध;
	हाल MI2S_SECONDARY:
		अवरोध;
	हाल LPASS_DP_RX:
		अवरोध;
	शेष:
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sc7180_adau7002_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	चयन (cpu_dai->id) अणु
	हाल MI2S_PRIMARY:
		वापस 0;
	हाल MI2S_SECONDARY:
		वापस 0;
	हाल LPASS_DP_RX:
		वापस sc7180_hdmi_init(rtd);
	शेष:
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sc7180_adau7002_snd_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	चयन (cpu_dai->id) अणु
	हाल MI2S_PRIMARY:
		snd_soc_dai_set_fmt(codec_dai,
				    SND_SOC_DAIFMT_CBS_CFS |
				    SND_SOC_DAIFMT_NB_NF |
				    SND_SOC_DAIFMT_I2S);
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE;
		snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 32);

		अवरोध;
	हाल MI2S_SECONDARY:
		अवरोध;
	हाल LPASS_DP_RX:
		अवरोध;
	शेष:
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops sc7180_ops = अणु
	.startup = sc7180_snd_startup,
	.shutकरोwn = sc7180_snd_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops sc7180_adau7002_ops = अणु
	.startup = sc7180_adau7002_snd_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sc7180_snd_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sc7180_adau7002_snd_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("DMIC", शून्य),
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic_mux_text[] = अणु
	"Front Mic",
	"Rear Mic",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sc7180_dmic_क्रमागत,
			    SND_SOC_NOPM, 0, dmic_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new sc7180_dmic_mux_control =
	SOC_DAPM_ENUM_EXT("DMIC Select Mux", sc7180_dmic_क्रमागत,
			  dmic_get, dmic_set);

अटल स्थिर काष्ठा snd_soc_dapm_widget sc7180_snd_dual_mic_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("DMIC", शून्य),
	SND_SOC_DAPM_MUX("Dmic Mux", SND_SOC_NOPM, 0, 0, &sc7180_dmic_mux_control),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sc7180_snd_dual_mic_audio_route[] = अणु
	अणु"Dmic Mux", "Front Mic", "DMIC"पूर्ण,
	अणु"Dmic Mux", "Rear Mic", "DMIC"पूर्ण,
पूर्ण;

अटल पूर्णांक sc7180_snd_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा sc7180_snd_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक ret;
	पूर्णांक i;
	bool no_headphone = false;

	/* Allocate the निजी data */
	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	card = &data->card;
	snd_soc_card_set_drvdata(card, data);

	card->owner = THIS_MODULE;
	card->driver_name = DRIVER_NAME;
	card->dev = dev;
	card->dapm_widमाला_लो = sc7180_snd_widमाला_लो;
	card->num_dapm_widमाला_लो = ARRAY_SIZE(sc7180_snd_widमाला_लो);

	अगर (of_property_पढ़ो_bool(dev->of_node, "dmic-gpios")) अणु
		card->dapm_widमाला_लो = sc7180_snd_dual_mic_widमाला_लो,
		card->num_dapm_widमाला_लो = ARRAY_SIZE(sc7180_snd_dual_mic_widमाला_लो),
		card->dapm_routes = sc7180_snd_dual_mic_audio_route,
		card->num_dapm_routes = ARRAY_SIZE(sc7180_snd_dual_mic_audio_route),
		data->dmic_sel = devm_gpiod_get(&pdev->dev, "dmic", GPIOD_OUT_LOW);
		अगर (IS_ERR(data->dmic_sel)) अणु
			dev_err(&pdev->dev, "DMIC gpio failed err=%ld\n", PTR_ERR(data->dmic_sel));
			वापस PTR_ERR(data->dmic_sel);
		पूर्ण
	पूर्ण

	अगर (of_device_is_compatible(dev->of_node, "google,sc7180-coachz")) अणु
		no_headphone = true;
		card->dapm_widमाला_लो = sc7180_adau7002_snd_widमाला_लो;
		card->num_dapm_widमाला_लो = ARRAY_SIZE(sc7180_adau7002_snd_widमाला_लो);
	पूर्ण

	ret = qcom_snd_parse_of(card);
	अगर (ret)
		वापस ret;

	क्रम_each_card_prelinks(card, i, link) अणु
		अगर (no_headphone) अणु
			link->ops = &sc7180_adau7002_ops;
			link->init = sc7180_adau7002_init;
		पूर्ण अन्यथा अणु
			link->ops = &sc7180_ops;
			link->init = sc7180_init;
		पूर्ण
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_card(dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id sc7180_snd_device_id[]  = अणु
	अणु.compatible = "google,sc7180-trogdor"पूर्ण,
	अणु.compatible = "google,sc7180-coachz"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sc7180_snd_device_id);

अटल काष्ठा platक्रमm_driver sc7180_snd_driver = अणु
	.probe = sc7180_snd_platक्रमm_probe,
	.driver = अणु
		.name = "msm-snd-sc7180",
		.of_match_table = sc7180_snd_device_id,
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sc7180_snd_driver);

MODULE_DESCRIPTION("sc7180 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
