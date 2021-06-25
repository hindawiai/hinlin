<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm.h>
#समावेश "common.h"

#घोषणा SLIM_MAX_TX_PORTS 16
#घोषणा SLIM_MAX_RX_PORTS 16
#घोषणा WCD9335_DEFAULT_MCLK_RATE	9600000

अटल पूर्णांक apq8096_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
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

अटल पूर्णांक msm_snd_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	u32 rx_ch[SLIM_MAX_RX_PORTS], tx_ch[SLIM_MAX_TX_PORTS];
	u32 rx_ch_cnt = 0, tx_ch_cnt = 0;
	पूर्णांक ret = 0;

	ret = snd_soc_dai_get_channel_map(codec_dai,
				&tx_ch_cnt, tx_ch, &rx_ch_cnt, rx_ch);
	अगर (ret != 0 && ret != -ENOTSUPP) अणु
		pr_err("failed to get codec chan map, err:%d\n", ret);
		जाओ end;
	पूर्ण अन्यथा अगर (ret == -ENOTSUPP) अणु
		वापस 0;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ret = snd_soc_dai_set_channel_map(cpu_dai, 0, शून्य,
						  rx_ch_cnt, rx_ch);
	अन्यथा
		ret = snd_soc_dai_set_channel_map(cpu_dai, tx_ch_cnt, tx_ch,
						  0, शून्य);
	अगर (ret != 0 && ret != -ENOTSUPP)
		pr_err("Failed to set cpu chan map, err:%d\n", ret);
	अन्यथा अगर (ret == -ENOTSUPP)
		ret = 0;
end:
	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops apq8096_ops = अणु
	.hw_params = msm_snd_hw_params,
पूर्ण;

अटल पूर्णांक apq8096_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	/*
	 * Codec SLIMBUS configuration
	 * RX1, RX2, RX3, RX4, RX5, RX6, RX7, RX8, RX9, RX10, RX11, RX12, RX13
	 * TX1, TX2, TX3, TX4, TX5, TX6, TX7, TX8, TX9, TX10, TX11, TX12, TX13
	 * TX14, TX15, TX16
	 */
	अचिन्हित पूर्णांक rx_ch[SLIM_MAX_RX_PORTS] = अणु144, 145, 146, 147, 148, 149,
					150, 151, 152, 153, 154, 155, 156पूर्ण;
	अचिन्हित पूर्णांक tx_ch[SLIM_MAX_TX_PORTS] = अणु128, 129, 130, 131, 132, 133,
					    134, 135, 136, 137, 138, 139,
					    140, 141, 142, 143पूर्ण;

	snd_soc_dai_set_channel_map(codec_dai, ARRAY_SIZE(tx_ch),
					tx_ch, ARRAY_SIZE(rx_ch), rx_ch);

	snd_soc_dai_set_sysclk(codec_dai, 0, WCD9335_DEFAULT_MCLK_RATE,
				SNDRV_PCM_STREAM_PLAYBACK);

	वापस 0;
पूर्ण

अटल व्योम apq8096_add_be_ops(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक i;

	क्रम_each_card_prelinks(card, i, link) अणु
		अगर (link->no_pcm == 1) अणु
			link->be_hw_params_fixup = apq8096_be_hw_params_fixup;
			link->init = apq8096_init;
			link->ops = &apq8096_ops;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक apq8096_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->dev = dev;
	card->owner = THIS_MODULE;
	dev_set_drvdata(dev, card);
	ret = qcom_snd_parse_of(card);
	अगर (ret)
		वापस ret;

	apq8096_add_be_ops(card);
	वापस devm_snd_soc_रेजिस्टर_card(dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id msm_snd_apq8096_dt_match[] = अणु
	अणु.compatible = "qcom,apq8096-sndcard"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, msm_snd_apq8096_dt_match);

अटल काष्ठा platक्रमm_driver msm_snd_apq8096_driver = अणु
	.probe  = apq8096_platक्रमm_probe,
	.driver = अणु
		.name = "msm-snd-apq8096",
		.of_match_table = msm_snd_apq8096_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(msm_snd_apq8096_driver);
MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org");
MODULE_DESCRIPTION("APQ8096 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
