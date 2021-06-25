<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "axg-tdm.h"

क्रमागत अणु
	TDM_IFACE_PAD,
	TDM_IFACE_LOOPBACK,
पूर्ण;

अटल अचिन्हित पूर्णांक axg_tdm_slots_total(u32 *mask)
अणु
	अचिन्हित पूर्णांक slots = 0;
	पूर्णांक i;

	अगर (!mask)
		वापस 0;

	/* Count the total number of slots provided by all 4 lanes */
	क्रम (i = 0; i < AXG_TDM_NUM_LANES; i++)
		slots += hweight32(mask[i]);

	वापस slots;
पूर्ण

पूर्णांक axg_tdm_set_tdm_slots(काष्ठा snd_soc_dai *dai, u32 *tx_mask,
			  u32 *rx_mask, अचिन्हित पूर्णांक slots,
			  अचिन्हित पूर्णांक slot_width)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	काष्ठा axg_tdm_stream *tx = (काष्ठा axg_tdm_stream *)
		dai->playback_dma_data;
	काष्ठा axg_tdm_stream *rx = (काष्ठा axg_tdm_stream *)
		dai->capture_dma_data;
	अचिन्हित पूर्णांक tx_slots, rx_slots;
	अचिन्हित पूर्णांक fmt = 0;

	tx_slots = axg_tdm_slots_total(tx_mask);
	rx_slots = axg_tdm_slots_total(rx_mask);

	/* We should at least have a slot क्रम a valid पूर्णांकerface */
	अगर (!tx_slots && !rx_slots) अणु
		dev_err(dai->dev, "interface has no slot\n");
		वापस -EINVAL;
	पूर्ण

	अगरace->slots = slots;

	चयन (slot_width) अणु
	हाल 0:
		slot_width = 32;
		fallthrough;
	हाल 32:
		fmt |= SNDRV_PCM_FMTBIT_S32_LE;
		fallthrough;
	हाल 24:
		fmt |= SNDRV_PCM_FMTBIT_S24_LE;
		fmt |= SNDRV_PCM_FMTBIT_S20_LE;
		fallthrough;
	हाल 16:
		fmt |= SNDRV_PCM_FMTBIT_S16_LE;
		fallthrough;
	हाल 8:
		fmt |= SNDRV_PCM_FMTBIT_S8;
		अवरोध;
	शेष:
		dev_err(dai->dev, "unsupported slot width: %d\n", slot_width);
		वापस -EINVAL;
	पूर्ण

	अगरace->slot_width = slot_width;

	/* Amend the dai driver and let dpcm merge करो its job */
	अगर (tx) अणु
		tx->mask = tx_mask;
		dai->driver->playback.channels_max = tx_slots;
		dai->driver->playback.क्रमmats = fmt;
	पूर्ण

	अगर (rx) अणु
		rx->mask = rx_mask;
		dai->driver->capture.channels_max = rx_slots;
		dai->driver->capture.क्रमmats = fmt;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_set_tdm_slots);

अटल पूर्णांक axg_tdm_अगरace_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				    अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret = -ENOTSUPP;

	अगर (dir == SND_SOC_CLOCK_OUT && clk_id == 0) अणु
		अगर (!अगरace->mclk) अणु
			dev_warn(dai->dev, "master clock not provided\n");
		पूर्ण अन्यथा अणु
			ret = clk_set_rate(अगरace->mclk, freq);
			अगर (!ret)
				अगरace->mclk_rate = freq;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगर (!अगरace->mclk) अणु
			dev_err(dai->dev, "cpu clock master: mclk missing\n");
			वापस -ENODEV;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;

	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
		dev_err(dai->dev, "only CBS_CFS and CBM_CFM are supported\n");
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगरace->fmt = fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	काष्ठा axg_tdm_stream *ts =
		snd_soc_dai_get_dma_data(dai, substream);
	पूर्णांक ret;

	अगर (!axg_tdm_slots_total(ts->mask)) अणु
		dev_err(dai->dev, "interface has not slots\n");
		वापस -EINVAL;
	पूर्ण

	/* Apply component wide rate symmetry */
	अगर (snd_soc_component_active(dai->component)) अणु
		ret = snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
						   SNDRV_PCM_HW_PARAM_RATE,
						   अगरace->rate);
		अगर (ret < 0) अणु
			dev_err(dai->dev,
				"can't set iface rate constraint\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_set_stream(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	काष्ठा axg_tdm_stream *ts = snd_soc_dai_get_dma_data(dai, substream);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक width = params_width(params);

	/* Save rate and sample_bits क्रम component symmetry */
	अगरace->rate = params_rate(params);

	/* Make sure this पूर्णांकerface can cope with the stream */
	अगर (axg_tdm_slots_total(ts->mask) < channels) अणु
		dev_err(dai->dev, "not enough slots for channels\n");
		वापस -EINVAL;
	पूर्ण

	अगर (अगरace->slot_width < width) अणु
		dev_err(dai->dev, "incompatible slots width for stream\n");
		वापस -EINVAL;
	पूर्ण

	/* Save the parameter क्रम tdmout/tdmin widमाला_लो */
	ts->physical_width = params_physical_width(params);
	ts->width = params_width(params);
	ts->channels = params_channels(params);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_set_lrclk(काष्ठा snd_soc_dai *dai,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक ratio_num;
	पूर्णांक ret;

	ret = clk_set_rate(अगरace->lrclk, params_rate(params));
	अगर (ret) अणु
		dev_err(dai->dev, "setting sample clock failed: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		/* 50% duty cycle ratio */
		ratio_num = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/*
		 * A zero duty cycle ratio will result in setting the mininum
		 * ratio possible which, क्रम this घड़ी, is 1 cycle of the
		 * parent bclk घड़ी high and the rest low, This is exactly
		 * what we want here.
		 */
		ratio_num = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_duty_cycle(अगरace->lrclk, ratio_num, 2);
	अगर (ret) अणु
		dev_err(dai->dev,
			"setting sample clock duty cycle failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set sample घड़ी inversion */
	ret = clk_set_phase(अगरace->lrclk,
			    axg_tdm_lrclk_invert(अगरace->fmt) ? 180 : 0);
	अगर (ret) अणु
		dev_err(dai->dev,
			"setting sample clock phase failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_set_sclk(काष्ठा snd_soc_dai *dai,
				  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	अचिन्हित दीर्घ srate;
	पूर्णांक ret;

	srate = अगरace->slots * अगरace->slot_width * params_rate(params);

	अगर (!अगरace->mclk_rate) अणु
		/* If no specअगरic mclk is requested, शेष to bit घड़ी * 4 */
		clk_set_rate(अगरace->mclk, 4 * srate);
	पूर्ण अन्यथा अणु
		/* Check अगर we can actually get the bit घड़ी from mclk */
		अगर (अगरace->mclk_rate % srate) अणु
			dev_err(dai->dev,
				"can't derive sclk %lu from mclk %lu\n",
				srate, अगरace->mclk_rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = clk_set_rate(अगरace->sclk, srate);
	अगर (ret) अणु
		dev_err(dai->dev, "setting bit clock failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set the bit घड़ी inversion */
	ret = clk_set_phase(अगरace->sclk,
			    axg_tdm_sclk_invert(अगरace->fmt) ? 0 : 180);
	अगर (ret) अणु
		dev_err(dai->dev, "setting bit clock phase failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	चयन (अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगर (अगरace->slots > 2) अणु
			dev_err(dai->dev, "bad slot number for format: %d\n",
				अगरace->slots);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		अवरोध;

	शेष:
		dev_err(dai->dev, "unsupported dai format\n");
		वापस -EINVAL;
	पूर्ण

	ret = axg_tdm_अगरace_set_stream(substream, params, dai);
	अगर (ret)
		वापस ret;

	अगर ((अगरace->fmt & SND_SOC_DAIFMT_MASTER_MASK) ==
	    SND_SOC_DAIFMT_CBS_CFS) अणु
		ret = axg_tdm_अगरace_set_sclk(dai, params);
		अगर (ret)
			वापस ret;

		ret = axg_tdm_अगरace_set_lrclk(dai, params);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_tdm_stream *ts = snd_soc_dai_get_dma_data(dai, substream);

	/* Stop all attached क्रमmatters */
	axg_tdm_stream_stop(ts);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_prepare(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_tdm_stream *ts = snd_soc_dai_get_dma_data(dai, substream);

	/* Force all attached क्रमmatters to update */
	वापस axg_tdm_stream_reset(ts);
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_हटाओ_dai(काष्ठा snd_soc_dai *dai)
अणु
	अगर (dai->capture_dma_data)
		axg_tdm_stream_मुक्त(dai->capture_dma_data);

	अगर (dai->playback_dma_data)
		axg_tdm_stream_मुक्त(dai->playback_dma_data);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_tdm_अगरace_probe_dai(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_dai_get_drvdata(dai);

	अगर (dai->capture_widget) अणु
		dai->capture_dma_data = axg_tdm_stream_alloc(अगरace);
		अगर (!dai->capture_dma_data)
			वापस -ENOMEM;
	पूर्ण

	अगर (dai->playback_widget) अणु
		dai->playback_dma_data = axg_tdm_stream_alloc(अगरace);
		अगर (!dai->playback_dma_data) अणु
			axg_tdm_अगरace_हटाओ_dai(dai);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axg_tdm_अगरace_ops = अणु
	.set_sysclk	= axg_tdm_अगरace_set_sysclk,
	.set_fmt	= axg_tdm_अगरace_set_fmt,
	.startup	= axg_tdm_अगरace_startup,
	.hw_params	= axg_tdm_अगरace_hw_params,
	.prepare	= axg_tdm_अगरace_prepare,
	.hw_मुक्त	= axg_tdm_अगरace_hw_मुक्त,
पूर्ण;

/* TDM Backend DAIs */
अटल स्थिर काष्ठा snd_soc_dai_driver axg_tdm_अगरace_dai_drv[] = अणु
	[TDM_IFACE_PAD] = अणु
		.name = "TDM Pad",
		.playback = अणु
			.stream_name	= "Playback",
			.channels_min	= 1,
			.channels_max	= AXG_TDM_CHANNEL_MAX,
			.rates		= AXG_TDM_RATES,
			.क्रमmats	= AXG_TDM_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name	= "Capture",
			.channels_min	= 1,
			.channels_max	= AXG_TDM_CHANNEL_MAX,
			.rates		= AXG_TDM_RATES,
			.क्रमmats	= AXG_TDM_FORMATS,
		पूर्ण,
		.id = TDM_IFACE_PAD,
		.ops = &axg_tdm_अगरace_ops,
		.probe = axg_tdm_अगरace_probe_dai,
		.हटाओ = axg_tdm_अगरace_हटाओ_dai,
	पूर्ण,
	[TDM_IFACE_LOOPBACK] = अणु
		.name = "TDM Loopback",
		.capture = अणु
			.stream_name	= "Loopback",
			.channels_min	= 1,
			.channels_max	= AXG_TDM_CHANNEL_MAX,
			.rates		= AXG_TDM_RATES,
			.क्रमmats	= AXG_TDM_FORMATS,
		पूर्ण,
		.id = TDM_IFACE_LOOPBACK,
		.ops = &axg_tdm_अगरace_ops,
		.probe = axg_tdm_अगरace_probe_dai,
		.हटाओ = axg_tdm_अगरace_हटाओ_dai,
	पूर्ण,
पूर्ण;

अटल पूर्णांक axg_tdm_अगरace_set_bias_level(काष्ठा snd_soc_component *component,
					क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा axg_tdm_अगरace *अगरace = snd_soc_component_get_drvdata(component);
	क्रमागत snd_soc_bias_level now =
		snd_soc_component_get_bias_level(component);
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (now == SND_SOC_BIAS_STANDBY)
			ret = clk_prepare_enable(अगरace->mclk);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (now == SND_SOC_BIAS_PREPARE)
			clk_disable_unprepare(अगरace->mclk);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget axg_tdm_अगरace_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SIGGEN("Playback Signal"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route axg_tdm_अगरace_dapm_routes[] = अणु
	अणु "Loopback", शून्य, "Playback Signal" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_tdm_अगरace_component_drv = अणु
	.dapm_widमाला_लो		= axg_tdm_अगरace_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_tdm_अगरace_dapm_widमाला_लो),
	.dapm_routes		= axg_tdm_अगरace_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_tdm_अगरace_dapm_routes),
	.set_bias_level		= axg_tdm_अगरace_set_bias_level,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_tdm_अगरace_of_match[] = अणु
	अणु .compatible = "amlogic,axg-tdm-iface", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_tdm_अगरace_of_match);

अटल पूर्णांक axg_tdm_अगरace_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा axg_tdm_अगरace *अगरace;
	पूर्णांक ret, i;

	अगरace = devm_kzalloc(dev, माप(*अगरace), GFP_KERNEL);
	अगर (!अगरace)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, अगरace);

	/*
	 * Duplicate dai driver: depending on the slot masks configuration
	 * We'll change the number of channel provided by DAI stream, so dpcm
	 * channel merge can be करोne properly
	 */
	dai_drv = devm_kसुस्मृति(dev, ARRAY_SIZE(axg_tdm_अगरace_dai_drv),
			       माप(*dai_drv), GFP_KERNEL);
	अगर (!dai_drv)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(axg_tdm_अगरace_dai_drv); i++)
		स_नकल(&dai_drv[i], &axg_tdm_अगरace_dai_drv[i],
		       माप(*dai_drv));

	/* Bit घड़ी provided on the pad */
	अगरace->sclk = devm_clk_get(dev, "sclk");
	अगर (IS_ERR(अगरace->sclk)) अणु
		ret = PTR_ERR(अगरace->sclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get sclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Sample घड़ी provided on the pad */
	अगरace->lrclk = devm_clk_get(dev, "lrclk");
	अगर (IS_ERR(अगरace->lrclk)) अणु
		ret = PTR_ERR(अगरace->lrclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get lrclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * mclk maybe be missing when the cpu dai is in slave mode and
	 * the codec करोes not require it to provide a master घड़ी.
	 * At this poपूर्णांक, ignore the error अगर mclk is missing. We'll
	 * throw an error अगर the cpu dai is master and mclk is missing
	 */
	अगरace->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(अगरace->mclk)) अणु
		ret = PTR_ERR(अगरace->mclk);
		अगर (ret == -ENOENT) अणु
			अगरace->mclk = शून्य;
		पूर्ण अन्यथा अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to get mclk: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev,
					&axg_tdm_अगरace_component_drv, dai_drv,
					ARRAY_SIZE(axg_tdm_अगरace_dai_drv));
पूर्ण

अटल काष्ठा platक्रमm_driver axg_tdm_अगरace_pdrv = अणु
	.probe = axg_tdm_अगरace_probe,
	.driver = अणु
		.name = "axg-tdm-iface",
		.of_match_table = axg_tdm_अगरace_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_tdm_अगरace_pdrv);

MODULE_DESCRIPTION("Amlogic AXG TDM interface driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
