<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// tegra_audio_graph_card.c - Audio Graph based Tegra Machine Driver
//
// Copyright (c) 2020-2021 NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/graph_card.h>
#समावेश <sound/pcm_params.h>

#घोषणा MAX_PLLA_OUT0_DIV 128

#घोषणा simple_to_tegra_priv(simple) \
		container_of(simple, काष्ठा tegra_audio_priv, simple)

क्रमागत srate_type अणु
	/*
	 * Sample rates multiple of 8000 Hz and below are supported:
	 * ( 8000, 16000, 32000, 48000, 96000, 192000 Hz )
	 */
	x8_RATE,

	/*
	 * Sample rates multiple of 11025 Hz and below are supported:
	 * ( 11025, 22050, 44100, 88200, 176400 Hz )
	 */
	x11_RATE,

	NUM_RATE_TYPE,
पूर्ण;

काष्ठा tegra_audio_priv अणु
	काष्ठा asoc_simple_priv simple;
	काष्ठा clk *clk_plla_out0;
	काष्ठा clk *clk_plla;
पूर्ण;

/* Tegra audio chip data */
काष्ठा tegra_audio_cdata अणु
	अचिन्हित पूर्णांक plla_rates[NUM_RATE_TYPE];
	अचिन्हित पूर्णांक plla_out0_rates[NUM_RATE_TYPE];
पूर्ण;

/* Setup PLL घड़ी as per the given sample rate */
अटल पूर्णांक tegra_audio_graph_update_pll(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा asoc_simple_priv *simple = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा tegra_audio_priv *priv = simple_to_tegra_priv(simple);
	काष्ठा device *dev = rtd->card->dev;
	स्थिर काष्ठा tegra_audio_cdata *data = of_device_get_match_data(dev);
	अचिन्हित पूर्णांक plla_rate, plla_out0_rate, bclk;
	अचिन्हित पूर्णांक srate = params_rate(params);
	पूर्णांक err;

	चयन (srate) अणु
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
	हाल 176400:
		plla_out0_rate = data->plla_out0_rates[x11_RATE];
		plla_rate = data->plla_rates[x11_RATE];
		अवरोध;
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 48000:
	हाल 96000:
	हाल 192000:
		plla_out0_rate = data->plla_out0_rates[x8_RATE];
		plla_rate = data->plla_rates[x8_RATE];
		अवरोध;
	शेष:
		dev_err(rtd->card->dev, "Unsupported sample rate %u\n",
			srate);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Below is the घड़ी relation:
	 *
	 *	PLLA
	 *	  |
	 *	  |--> PLLA_OUT0
	 *		  |
	 *		  |---> I2S modules
	 *		  |
	 *		  |---> DMIC modules
	 *		  |
	 *		  |---> DSPK modules
	 *
	 *
	 * Default PLLA_OUT0 rate might be too high when I/O is running
	 * at minimum PCM configurations. This may result in incorrect
	 * घड़ी rates and glitchy audio. The maximum भागider is 128
	 * and any thing higher than that won't work. Thus reduce PLLA_OUT0
	 * to work क्रम lower configurations.
	 *
	 * This problem is seen क्रम I2S only, as DMIC and DSPK minimum
	 * घड़ी requirements are under allowed भागider limits.
	 */
	bclk = srate * params_channels(params) * params_width(params);
	अगर (भाग_u64(plla_out0_rate, bclk) > MAX_PLLA_OUT0_DIV)
		plla_out0_rate >>= 1;

	dev_dbg(rtd->card->dev,
		"Update clock rates: PLLA(= %u Hz) and PLLA_OUT0(= %u Hz)\n",
		plla_rate, plla_out0_rate);

	/* Set PLLA rate */
	err = clk_set_rate(priv->clk_plla, plla_rate);
	अगर (err) अणु
		dev_err(rtd->card->dev,
			"Can't set plla rate for %u, err: %d\n",
			plla_rate, err);
		वापस err;
	पूर्ण

	/* Set PLLA_OUT0 rate */
	err = clk_set_rate(priv->clk_plla_out0, plla_out0_rate);
	अगर (err) अणु
		dev_err(rtd->card->dev,
			"Can't set plla_out0 rate %u, err: %d\n",
			plla_out0_rate, err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tegra_audio_graph_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक err;

	/*
	 * This माला_लो called क्रम each DAI link (FE or BE) when DPCM is used.
	 * We may not want to update PLLA rate क्रम each call. So PLLA update
	 * must be restricted to बाह्यal I/O links (I2S, DMIC or DSPK) since
	 * they actually depend on it. I/O modules update their घड़ीs in
	 * hw_param() of their respective component driver and PLLA rate
	 * update here helps them to derive appropriate rates.
	 *
	 * TODO: When more HW accelerators get added (like sample rate
	 * converter, volume gain controller etc., which करोn't really
	 * depend on PLLA) we need a better way to filter here.
	 */
	अगर (cpu_dai->driver->ops && rtd->dai_link->no_pcm) अणु
		err = tegra_audio_graph_update_pll(substream, params);
		अगर (err)
			वापस err;
	पूर्ण

	वापस asoc_simple_hw_params(substream, params);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tegra_audio_graph_ops = अणु
	.startup	= asoc_simple_startup,
	.shutकरोwn	= asoc_simple_shutकरोwn,
	.hw_params	= tegra_audio_graph_hw_params,
पूर्ण;

अटल पूर्णांक tegra_audio_graph_card_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा asoc_simple_priv *simple = snd_soc_card_get_drvdata(card);
	काष्ठा tegra_audio_priv *priv = simple_to_tegra_priv(simple);

	priv->clk_plla = devm_clk_get(card->dev, "pll_a");
	अगर (IS_ERR(priv->clk_plla)) अणु
		dev_err(card->dev, "Can't retrieve clk pll_a\n");
		वापस PTR_ERR(priv->clk_plla);
	पूर्ण

	priv->clk_plla_out0 = devm_clk_get(card->dev, "plla_out0");
	अगर (IS_ERR(priv->clk_plla_out0)) अणु
		dev_err(card->dev, "Can't retrieve clk plla_out0\n");
		वापस PTR_ERR(priv->clk_plla_out0);
	पूर्ण

	वापस asoc_graph_card_probe(card);
पूर्ण

अटल पूर्णांक tegra_audio_graph_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_audio_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_card *card;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	card = simple_priv_to_card(&priv->simple);
	card->driver_name = "tegra-ape";

	card->probe = tegra_audio_graph_card_probe;

	/* audio_graph_parse_of() depends on below */
	card->component_chaining = 1;
	priv->simple.ops = &tegra_audio_graph_ops;
	priv->simple.क्रमce_dpcm = 1;

	वापस audio_graph_parse_of(&priv->simple, dev);
पूर्ण

अटल स्थिर काष्ठा tegra_audio_cdata tegra210_data = अणु
	/* PLLA */
	.plla_rates[x8_RATE] = 368640000,
	.plla_rates[x11_RATE] = 338688000,
	/* PLLA_OUT0 */
	.plla_out0_rates[x8_RATE] = 49152000,
	.plla_out0_rates[x11_RATE] = 45158400,
पूर्ण;

अटल स्थिर काष्ठा tegra_audio_cdata tegra186_data = अणु
	/* PLLA */
	.plla_rates[x8_RATE] = 245760000,
	.plla_rates[x11_RATE] = 270950400,
	/* PLLA_OUT0 */
	.plla_out0_rates[x8_RATE] = 49152000,
	.plla_out0_rates[x11_RATE] = 45158400,
पूर्ण;

अटल स्थिर काष्ठा of_device_id graph_of_tegra_match[] = अणु
	अणु .compatible = "nvidia,tegra210-audio-graph-card",
	  .data = &tegra210_data पूर्ण,
	अणु .compatible = "nvidia,tegra186-audio-graph-card",
	  .data = &tegra186_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, graph_of_tegra_match);

अटल काष्ठा platक्रमm_driver tegra_audio_graph_card = अणु
	.driver = अणु
		.name = "tegra-audio-graph-card",
		.pm = &snd_soc_pm_ops,
		.of_match_table = graph_of_tegra_match,
	पूर्ण,
	.probe = tegra_audio_graph_probe,
	.हटाओ = asoc_simple_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_audio_graph_card);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ASoC Tegra Audio Graph Sound Card");
MODULE_AUTHOR("Sameer Pujar <spujar@nvidia.com>");
