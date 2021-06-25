<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020, Linaro Limited

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश "qdsp6/q6afe.h"
#समावेश "common.h"

#घोषणा DRIVER_NAME		"sm8250"
#घोषणा MI2S_BCLK_RATE		1536000

काष्ठा sm8250_snd_data अणु
	bool stream_prepared[AFE_PORT_MAX];
	काष्ठा snd_soc_card *card;
	काष्ठा sdw_stream_runसमय *srunसमय[AFE_PORT_MAX];
पूर्ण;

अटल पूर्णांक sm8250_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_CHANNELS);

	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक sm8250_snd_startup(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक fmt = SND_SOC_DAIFMT_CBS_CFS;
	अचिन्हित पूर्णांक codec_dai_fmt = SND_SOC_DAIFMT_CBS_CFS;
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	चयन (cpu_dai->id) अणु
	हाल TERTIARY_MI2S_RX:
		codec_dai_fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_I2S;
		snd_soc_dai_set_sysclk(cpu_dai,
			Q6AFE_LPASS_CLK_ID_TER_MI2S_IBIT,
			MI2S_BCLK_RATE, SNDRV_PCM_STREAM_PLAYBACK);
		snd_soc_dai_set_fmt(cpu_dai, fmt);
		snd_soc_dai_set_fmt(codec_dai, codec_dai_fmt);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sm8250_snd_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sm8250_snd_data *pdata = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा sdw_stream_runसमय *srunसमय;
	पूर्णांक i;

	चयन (cpu_dai->id) अणु
	हाल WSA_CODEC_DMA_RX_0:
		क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
			srunसमय = snd_soc_dai_get_sdw_stream(codec_dai,
						      substream->stream);
			अगर (srunसमय != ERR_PTR(-ENOTSUPP))
				pdata->srunसमय[cpu_dai->id] = srunसमय;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक sm8250_snd_wsa_dma_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sm8250_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा sdw_stream_runसमय *srunसमय = data->srunसमय[cpu_dai->id];
	पूर्णांक ret;

	अगर (!srunसमय)
		वापस 0;

	अगर (data->stream_prepared[cpu_dai->id]) अणु
		sdw_disable_stream(srunसमय);
		sdw_deprepare_stream(srunसमय);
		data->stream_prepared[cpu_dai->id] = false;
	पूर्ण

	ret = sdw_prepare_stream(srunसमय);
	अगर (ret)
		वापस ret;

	/**
	 * NOTE: there is a strict hw requirement about the ordering of port
	 * enables and actual WSA881x PA enable. PA enable should only happen
	 * after soundwire ports are enabled अगर not DC on the line is
	 * accumulated resulting in Click/Pop Noise
	 * PA enable/mute are handled as part of codec DAPM and digital mute.
	 */

	ret = sdw_enable_stream(srunसमय);
	अगर (ret) अणु
		sdw_deprepare_stream(srunसमय);
		वापस ret;
	पूर्ण
	data->stream_prepared[cpu_dai->id]  = true;

	वापस ret;
पूर्ण

अटल पूर्णांक sm8250_snd_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	चयन (cpu_dai->id) अणु
	हाल WSA_CODEC_DMA_RX_0:
	हाल WSA_CODEC_DMA_RX_1:
		वापस sm8250_snd_wsa_dma_prepare(substream);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sm8250_snd_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा sm8250_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sdw_stream_runसमय *srunसमय = data->srunसमय[cpu_dai->id];

	चयन (cpu_dai->id) अणु
	हाल WSA_CODEC_DMA_RX_0:
	हाल WSA_CODEC_DMA_RX_1:
		अगर (srunसमय && data->stream_prepared[cpu_dai->id]) अणु
			sdw_disable_stream(srunसमय);
			sdw_deprepare_stream(srunसमय);
			data->stream_prepared[cpu_dai->id] = false;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops sm8250_be_ops = अणु
	.startup = sm8250_snd_startup,
	.hw_params = sm8250_snd_hw_params,
	.hw_मुक्त = sm8250_snd_hw_मुक्त,
	.prepare = sm8250_snd_prepare,
पूर्ण;

अटल व्योम sm8250_add_be_ops(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक i;

	क्रम_each_card_prelinks(card, i, link) अणु
		अगर (link->no_pcm == 1) अणु
			link->be_hw_params_fixup = sm8250_be_hw_params_fixup;
			link->ops = &sm8250_be_ops;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sm8250_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा sm8250_snd_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	/* Allocate the निजी data */
	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	card->dev = dev;
	dev_set_drvdata(dev, card);
	snd_soc_card_set_drvdata(card, data);
	ret = qcom_snd_parse_of(card);
	अगर (ret)
		वापस ret;

	card->driver_name = DRIVER_NAME;
	sm8250_add_be_ops(card);
	वापस devm_snd_soc_रेजिस्टर_card(dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id snd_sm8250_dt_match[] = अणु
	अणु.compatible = "qcom,sm8250-sndcard"पूर्ण,
	अणु.compatible = "qcom,qrb5165-rb5-sndcard"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, snd_sm8250_dt_match);

अटल काष्ठा platक्रमm_driver snd_sm8250_driver = अणु
	.probe  = sm8250_platक्रमm_probe,
	.driver = अणु
		.name = "snd-sm8250",
		.of_match_table = snd_sm8250_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snd_sm8250_driver);
MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org");
MODULE_DESCRIPTION("SM8250 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
