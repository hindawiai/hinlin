<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC WL1273 codec driver
 *
 * Author:      Matti Aaltonen, <matti.j.aaltonen@nokia.com>
 *
 * Copyright:   (C) 2010, 2011 Nokia Corporation
 */

#समावेश <linux/mfd/wl1273-core.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश "wl1273.h"

क्रमागत wl1273_mode अणु WL1273_MODE_BT, WL1273_MODE_FM_RX, WL1273_MODE_FM_TX पूर्ण;

/* codec निजी data */
काष्ठा wl1273_priv अणु
	क्रमागत wl1273_mode mode;
	काष्ठा wl1273_core *core;
	अचिन्हित पूर्णांक channels;
पूर्ण;

अटल पूर्णांक snd_wl1273_fm_set_i2s_mode(काष्ठा wl1273_core *core,
				      पूर्णांक rate, पूर्णांक width)
अणु
	काष्ठा device *dev = &core->client->dev;
	पूर्णांक r = 0;
	u16 mode;

	dev_dbg(dev, "rate: %d\n", rate);
	dev_dbg(dev, "width: %d\n", width);

	mutex_lock(&core->lock);

	mode = core->i2s_mode & ~WL1273_IS2_WIDTH & ~WL1273_IS2_RATE;

	चयन (rate) अणु
	हाल 48000:
		mode |= WL1273_IS2_RATE_48K;
		अवरोध;
	हाल 44100:
		mode |= WL1273_IS2_RATE_44_1K;
		अवरोध;
	हाल 32000:
		mode |= WL1273_IS2_RATE_32K;
		अवरोध;
	हाल 22050:
		mode |= WL1273_IS2_RATE_22_05K;
		अवरोध;
	हाल 16000:
		mode |= WL1273_IS2_RATE_16K;
		अवरोध;
	हाल 12000:
		mode |= WL1273_IS2_RATE_12K;
		अवरोध;
	हाल 11025:
		mode |= WL1273_IS2_RATE_11_025;
		अवरोध;
	हाल 8000:
		mode |= WL1273_IS2_RATE_8K;
		अवरोध;
	शेष:
		dev_err(dev, "Sampling rate: %d not supported\n", rate);
		r = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (width) अणु
	हाल 16:
		mode |= WL1273_IS2_WIDTH_32;
		अवरोध;
	हाल 20:
		mode |= WL1273_IS2_WIDTH_40;
		अवरोध;
	हाल 24:
		mode |= WL1273_IS2_WIDTH_48;
		अवरोध;
	हाल 25:
		mode |= WL1273_IS2_WIDTH_50;
		अवरोध;
	हाल 30:
		mode |= WL1273_IS2_WIDTH_60;
		अवरोध;
	हाल 32:
		mode |= WL1273_IS2_WIDTH_64;
		अवरोध;
	हाल 40:
		mode |= WL1273_IS2_WIDTH_80;
		अवरोध;
	हाल 48:
		mode |= WL1273_IS2_WIDTH_96;
		अवरोध;
	हाल 64:
		mode |= WL1273_IS2_WIDTH_128;
		अवरोध;
	शेष:
		dev_err(dev, "Data width: %d not supported\n", width);
		r = -EINVAL;
		जाओ out;
	पूर्ण

	dev_dbg(dev, "WL1273_I2S_DEF_MODE: 0x%04x\n",  WL1273_I2S_DEF_MODE);
	dev_dbg(dev, "core->i2s_mode: 0x%04x\n", core->i2s_mode);
	dev_dbg(dev, "mode: 0x%04x\n", mode);

	अगर (core->i2s_mode != mode) अणु
		r = core->ग_लिखो(core, WL1273_I2S_MODE_CONFIG_SET, mode);
		अगर (r)
			जाओ out;

		core->i2s_mode = mode;
		r = core->ग_लिखो(core, WL1273_AUDIO_ENABLE,
				WL1273_AUDIO_ENABLE_I2S);
		अगर (r)
			जाओ out;
	पूर्ण
out:
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल पूर्णांक snd_wl1273_fm_set_channel_number(काष्ठा wl1273_core *core,
					    पूर्णांक channel_number)
अणु
	काष्ठा device *dev = &core->client->dev;
	पूर्णांक r = 0;

	dev_dbg(dev, "%s\n", __func__);

	mutex_lock(&core->lock);

	अगर (core->channel_number == channel_number)
		जाओ out;

	अगर (channel_number == 1 && core->mode == WL1273_MODE_RX)
		r = core->ग_लिखो(core, WL1273_MOST_MODE_SET, WL1273_RX_MONO);
	अन्यथा अगर (channel_number == 1 && core->mode == WL1273_MODE_TX)
		r = core->ग_लिखो(core, WL1273_MONO_SET, WL1273_TX_MONO);
	अन्यथा अगर (channel_number == 2 && core->mode == WL1273_MODE_RX)
		r = core->ग_लिखो(core, WL1273_MOST_MODE_SET, WL1273_RX_STEREO);
	अन्यथा अगर (channel_number == 2 && core->mode == WL1273_MODE_TX)
		r = core->ग_लिखो(core, WL1273_MONO_SET, WL1273_TX_STEREO);
	अन्यथा
		r = -EINVAL;
out:
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल पूर्णांक snd_wl1273_get_audio_route(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wl1273->mode;

	वापस 0;
पूर्ण

/*
 * TODO: Implement the audio routing in the driver. Now this control
 * only indicates the setting that has been करोne अन्यथाwhere (in the user
 * space).
 */
अटल स्थिर अक्षर * स्थिर wl1273_audio_route[] = अणु "Bt", "FmRx", "FmTx" पूर्ण;

अटल पूर्णांक snd_wl1273_set_audio_route(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	अगर (wl1273->mode == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	/* Do not allow changes जबतक stream is running */
	अगर (snd_soc_component_active(component))
		वापस -EPERM;

	अगर (ucontrol->value.क्रमागतerated.item[0] >=  ARRAY_SIZE(wl1273_audio_route))
		वापस -EINVAL;

	wl1273->mode = ucontrol->value.क्रमागतerated.item[0];

	वापस 1;
पूर्ण

अटल SOC_ENUM_SINGLE_EXT_DECL(wl1273_क्रमागत, wl1273_audio_route);

अटल पूर्णांक snd_wl1273_fm_audio_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s: enter.\n", __func__);

	ucontrol->value.क्रमागतerated.item[0] = wl1273->core->audio_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wl1273_fm_audio_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, r = 0;

	dev_dbg(component->dev, "%s: enter.\n", __func__);

	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (wl1273->core->audio_mode == val)
		वापस 0;

	r = wl1273->core->set_audio(wl1273->core, val);
	अगर (r < 0)
		वापस r;

	वापस 1;
पूर्ण

अटल स्थिर अक्षर * स्थिर wl1273_audio_strings[] = अणु "Digital", "Analog" पूर्ण;

अटल SOC_ENUM_SINGLE_EXT_DECL(wl1273_audio_क्रमागत, wl1273_audio_strings);

अटल पूर्णांक snd_wl1273_fm_volume_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s: enter.\n", __func__);

	ucontrol->value.पूर्णांकeger.value[0] = wl1273->core->volume;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wl1273_fm_volume_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);
	पूर्णांक r;

	dev_dbg(component->dev, "%s: enter.\n", __func__);

	r = wl1273->core->set_volume(wl1273->core,
				     ucontrol->value.पूर्णांकeger.value[0]);
	अगर (r)
		वापस r;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wl1273_controls[] = अणु
	SOC_ENUM_EXT("Codec Mode", wl1273_क्रमागत,
		     snd_wl1273_get_audio_route, snd_wl1273_set_audio_route),
	SOC_ENUM_EXT("Audio Switch", wl1273_audio_क्रमागत,
		     snd_wl1273_fm_audio_get,  snd_wl1273_fm_audio_put),
	SOC_SINGLE_EXT("Volume", 0, 0, WL1273_MAX_VOLUME, 0,
		       snd_wl1273_fm_volume_get, snd_wl1273_fm_volume_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wl1273_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("RX"),

	SND_SOC_DAPM_OUTPUT("TX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wl1273_dapm_routes[] = अणु
	अणु "Capture", शून्य, "RX" पूर्ण,

	अणु "TX", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल पूर्णांक wl1273_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	चयन (wl1273->mode) अणु
	हाल WL1273_MODE_BT:
		snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_RATE, 8000);
		snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_CHANNELS, 1);
		अवरोध;
	हाल WL1273_MODE_FM_RX:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			pr_err("Cannot play in RX mode.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल WL1273_MODE_FM_TX:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
			pr_err("Cannot capture in TX mode.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(dai->component);
	काष्ठा wl1273_core *core = wl1273->core;
	अचिन्हित पूर्णांक rate, width, r;

	अगर (params_width(params) != 16) अणु
		dev_err(dai->dev, "%d bits/sample not supported\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	rate = params_rate(params);
	width =  hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS)->min;

	अगर (wl1273->mode == WL1273_MODE_BT) अणु
		अगर (rate != 8000) अणु
			pr_err("Rate %d not supported.\n", params_rate(params));
			वापस -EINVAL;
		पूर्ण

		अगर (params_channels(params) != 1) अणु
			pr_err("Only mono supported.\n");
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (wl1273->mode == WL1273_MODE_FM_TX &&
	    substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		pr_err("Only playback supported with TX.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wl1273->mode == WL1273_MODE_FM_RX  &&
	    substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		pr_err("Only capture supported with RX.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wl1273->mode != WL1273_MODE_FM_RX  &&
	    wl1273->mode != WL1273_MODE_FM_TX) अणु
		pr_err("Unexpected mode: %d.\n", wl1273->mode);
		वापस -EINVAL;
	पूर्ण

	r = snd_wl1273_fm_set_i2s_mode(core, rate, width);
	अगर (r)
		वापस r;

	wl1273->channels = params_channels(params);
	r = snd_wl1273_fm_set_channel_number(core, wl1273->channels);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wl1273_dai_ops = अणु
	.startup	= wl1273_startup,
	.hw_params	= wl1273_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wl1273_dai = अणु
	.name = "wl1273-fm",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LEपूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LEपूर्ण,
	.ops = &wl1273_dai_ops,
पूर्ण;

/* Audio पूर्णांकerface क्रमmat क्रम the soc_card driver */
पूर्णांक wl1273_get_क्रमmat(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक *fmt)
अणु
	काष्ठा wl1273_priv *wl1273;

	अगर (component == शून्य || fmt == शून्य)
		वापस -EINVAL;

	wl1273 = snd_soc_component_get_drvdata(component);

	चयन (wl1273->mode) अणु
	हाल WL1273_MODE_FM_RX:
	हाल WL1273_MODE_FM_TX:
		*fmt =	SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM;

		अवरोध;
	हाल WL1273_MODE_BT:
		*fmt =	SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_IB_NF |
			SND_SOC_DAIFMT_CBM_CFM;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wl1273_get_क्रमmat);

अटल पूर्णांक wl1273_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wl1273_core **core = component->dev->platक्रमm_data;
	काष्ठा wl1273_priv *wl1273;

	dev_dbg(component->dev, "%s.\n", __func__);

	अगर (!core) अणु
		dev_err(component->dev, "Platform data is missing.\n");
		वापस -EINVAL;
	पूर्ण

	wl1273 = kzalloc(माप(काष्ठा wl1273_priv), GFP_KERNEL);
	अगर (!wl1273)
		वापस -ENOMEM;

	wl1273->mode = WL1273_MODE_BT;
	wl1273->core = *core;

	snd_soc_component_set_drvdata(component, wl1273);

	वापस 0;
पूर्ण

अटल व्योम wl1273_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s\n", __func__);
	kमुक्त(wl1273);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wl1273 = अणु
	.probe			= wl1273_probe,
	.हटाओ			= wl1273_हटाओ,
	.controls		= wl1273_controls,
	.num_controls		= ARRAY_SIZE(wl1273_controls),
	.dapm_widमाला_लो		= wl1273_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wl1273_dapm_widमाला_लो),
	.dapm_routes		= wl1273_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wl1273_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wl1273_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &soc_component_dev_wl1273,
				      &wl1273_dai, 1);
पूर्ण

अटल पूर्णांक wl1273_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

MODULE_ALIAS("platform:wl1273-codec");

अटल काष्ठा platक्रमm_driver wl1273_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "wl1273-codec",
	पूर्ण,
	.probe		= wl1273_platक्रमm_probe,
	.हटाओ		= wl1273_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(wl1273_platक्रमm_driver);

MODULE_AUTHOR("Matti Aaltonen <matti.j.aaltonen@nokia.com>");
MODULE_DESCRIPTION("ASoC WL1273 codec driver");
MODULE_LICENSE("GPL");
