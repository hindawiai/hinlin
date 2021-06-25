<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt2701-cs42448.c  --  MT2701 CS42448 ALSA SoC machine driver
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ir Lian <ir.lian@mediatek.com>
 *	   Garlic Tseng <garlic.tseng@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/of_gpपन.स>

#समावेश "mt2701-afe-common.h"

काष्ठा mt2701_cs42448_निजी अणु
	पूर्णांक i2s1_in_mux;
	पूर्णांक i2s1_in_mux_gpio_sel_1;
	पूर्णांक i2s1_in_mux_gpio_sel_2;
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2sin_mux_चयन_text[] = अणु
	"ADC_SDOUT2",
	"ADC_SDOUT3",
	"I2S_IN_1",
	"I2S_IN_2",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत i2sin_mux_क्रमागत =
	SOC_ENUM_SINGLE_EXT(4, i2sin_mux_चयन_text);

अटल पूर्णांक mt2701_cs42448_i2sin1_mux_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	काष्ठा mt2701_cs42448_निजी *priv = snd_soc_card_get_drvdata(card);

	ucontrol->value.पूर्णांकeger.value[0] = priv->i2s1_in_mux;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2701_cs42448_i2sin1_mux_set(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	काष्ठा mt2701_cs42448_निजी *priv = snd_soc_card_get_drvdata(card);

	अगर (ucontrol->value.पूर्णांकeger.value[0] == priv->i2s1_in_mux)
		वापस 0;

	चयन (ucontrol->value.पूर्णांकeger.value[0]) अणु
	हाल 0:
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_1, 0);
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_2, 0);
		अवरोध;
	हाल 1:
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_1, 1);
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_2, 0);
		अवरोध;
	हाल 2:
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_1, 0);
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_2, 1);
		अवरोध;
	हाल 3:
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_1, 1);
		gpio_set_value(priv->i2s1_in_mux_gpio_sel_2, 1);
		अवरोध;
	शेष:
		dev_warn(card->dev, "%s invalid setting\n", __func__);
	पूर्ण

	priv->i2s1_in_mux = ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget
			mt2701_cs42448_asoc_card_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("Line Out Jack", शून्य),
	SND_SOC_DAPM_MIC("AMIC", शून्य),
	SND_SOC_DAPM_LINE("Tuner In", शून्य),
	SND_SOC_DAPM_LINE("Satellite Tuner In", शून्य),
	SND_SOC_DAPM_LINE("AUX In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_cs42448_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Line Out Jack"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
	SOC_DAPM_PIN_SWITCH("Tuner In"),
	SOC_DAPM_PIN_SWITCH("Satellite Tuner In"),
	SOC_DAPM_PIN_SWITCH("AUX In"),
	SOC_ENUM_EXT("I2SIN1_MUX_Switch", i2sin_mux_क्रमागत,
		     mt2701_cs42448_i2sin1_mux_get,
		     mt2701_cs42448_i2sin1_mux_set),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt2701_cs42448_sampling_rates[] = अणु48000पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list mt2701_cs42448_स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(mt2701_cs42448_sampling_rates),
		.list = mt2701_cs42448_sampling_rates,
		.mask = 0,
पूर्ण;

अटल पूर्णांक mt2701_cs42448_fe_ops_startup(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &mt2701_cs42448_स्थिरraपूर्णांकs_rates);
	अगर (err < 0) अणु
		dev_err(substream->pcm->card->dev,
			"%s snd_pcm_hw_constraint_list failed: 0x%x\n",
			__func__, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt2701_cs42448_48k_fe_ops = अणु
	.startup = mt2701_cs42448_fe_ops_startup,
पूर्ण;

अटल पूर्णांक mt2701_cs42448_be_ops_hw_params(काष्ठा snd_pcm_substream *substream,
					   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक mclk_rate;
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक भाग_mclk_over_bck = rate > 192000 ? 2 : 4;
	अचिन्हित पूर्णांक भाग_bck_over_lrck = 64;

	mclk_rate = rate * भाग_bck_over_lrck * भाग_mclk_over_bck;

	/* mt2701 mclk */
	snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_rate, SND_SOC_CLOCK_OUT);

	/* codec mclk */
	snd_soc_dai_set_sysclk(codec_dai, 0, mclk_rate, SND_SOC_CLOCK_IN);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops mt2701_cs42448_be_ops = अणु
	.hw_params = mt2701_cs42448_be_ops_hw_params
पूर्ण;

क्रमागत अणु
	DAI_LINK_FE_MULTI_CH_OUT,
	DAI_LINK_FE_PCM0_IN,
	DAI_LINK_FE_PCM1_IN,
	DAI_LINK_FE_BT_OUT,
	DAI_LINK_FE_BT_IN,
	DAI_LINK_BE_I2S0,
	DAI_LINK_BE_I2S1,
	DAI_LINK_BE_I2S2,
	DAI_LINK_BE_I2S3,
	DAI_LINK_BE_MRG_BT,
पूर्ण;

SND_SOC_DAILINK_DEFS(fe_multi_ch_out,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM_multi")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(fe_pcm0_in,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM0")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(fe_pcm1_in,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(fe_bt_out,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM_BT_DL")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(fe_bt_in,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM_BT_UL")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(be_i2s0,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S0")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "cs42448")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(be_i2s1,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S1")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "cs42448")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(be_i2s2,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S2")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "cs42448")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(be_i2s3,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S3")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "cs42448")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(be_mrg_bt,
	DAILINK_COMP_ARRAY(COMP_CPU("MRG BT")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "bt-sco-pcm-wb")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link mt2701_cs42448_dai_links[] = अणु
	/* FE */
	[DAI_LINK_FE_MULTI_CH_OUT] = अणु
		.name = "mt2701-cs42448-multi-ch-out",
		.stream_name = "mt2701-cs42448-multi-ch-out",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.ops = &mt2701_cs42448_48k_fe_ops,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(fe_multi_ch_out),
	पूर्ण,
	[DAI_LINK_FE_PCM0_IN] = अणु
		.name = "mt2701-cs42448-pcm0",
		.stream_name = "mt2701-cs42448-pcm0-data-UL",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.ops = &mt2701_cs42448_48k_fe_ops,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(fe_pcm0_in),
	पूर्ण,
	[DAI_LINK_FE_PCM1_IN] = अणु
		.name = "mt2701-cs42448-pcm1-data-UL",
		.stream_name = "mt2701-cs42448-pcm1-data-UL",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.ops = &mt2701_cs42448_48k_fe_ops,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(fe_pcm1_in),
	पूर्ण,
	[DAI_LINK_FE_BT_OUT] = अणु
		.name = "mt2701-cs42448-pcm-BT-out",
		.stream_name = "mt2701-cs42448-pcm-BT",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(fe_bt_out),
	पूर्ण,
	[DAI_LINK_FE_BT_IN] = अणु
		.name = "mt2701-cs42448-pcm-BT-in",
		.stream_name = "mt2701-cs42448-pcm-BT",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(fe_bt_in),
	पूर्ण,
	/* BE */
	[DAI_LINK_BE_I2S0] = अणु
		.name = "mt2701-cs42448-I2S0",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(be_i2s0),
	पूर्ण,
	[DAI_LINK_BE_I2S1] = अणु
		.name = "mt2701-cs42448-I2S1",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(be_i2s1),
	पूर्ण,
	[DAI_LINK_BE_I2S2] = अणु
		.name = "mt2701-cs42448-I2S2",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(be_i2s2),
	पूर्ण,
	[DAI_LINK_BE_I2S3] = अणु
		.name = "mt2701-cs42448-I2S3",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(be_i2s3),
	पूर्ण,
	[DAI_LINK_BE_MRG_BT] = अणु
		.name = "mt2701-cs42448-MRG-BT",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(be_mrg_bt),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt2701_cs42448_soc_card = अणु
	.name = "mt2701-cs42448",
	.owner = THIS_MODULE,
	.dai_link = mt2701_cs42448_dai_links,
	.num_links = ARRAY_SIZE(mt2701_cs42448_dai_links),
	.controls = mt2701_cs42448_controls,
	.num_controls = ARRAY_SIZE(mt2701_cs42448_controls),
	.dapm_widमाला_लो = mt2701_cs42448_asoc_card_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt2701_cs42448_asoc_card_dapm_widमाला_लो),
पूर्ण;

अटल पूर्णांक mt2701_cs42448_machine_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mt2701_cs42448_soc_card;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा device_node *platक्रमm_node, *codec_node, *codec_node_bt_mrg;
	काष्ठा mt2701_cs42448_निजी *priv =
		devm_kzalloc(&pdev->dev, माप(काष्ठा mt2701_cs42448_निजी),
			     GFP_KERNEL);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_dai_link *dai_link;

	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_node = of_parse_phandle(pdev->dev.of_node,
					 "mediatek,platform", 0);
	अगर (!platक्रमm_node) अणु
		dev_err(&pdev->dev, "Property 'platform' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अगर (dai_link->platक्रमms->name)
			जारी;
		dai_link->platक्रमms->of_node = platक्रमm_node;
	पूर्ण

	card->dev = dev;

	codec_node = of_parse_phandle(pdev->dev.of_node,
				      "mediatek,audio-codec", 0);
	अगर (!codec_node) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अगर (dai_link->codecs->name)
			जारी;
		dai_link->codecs->of_node = codec_node;
	पूर्ण

	codec_node_bt_mrg = of_parse_phandle(pdev->dev.of_node,
					     "mediatek,audio-codec-bt-mrg", 0);
	अगर (!codec_node_bt_mrg) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec-bt-mrg' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	mt2701_cs42448_dai_links[DAI_LINK_BE_MRG_BT].codecs->of_node
							= codec_node_bt_mrg;

	ret = snd_soc_of_parse_audio_routing(card, "audio-routing");
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse audio-routing: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->i2s1_in_mux_gpio_sel_1 =
		of_get_named_gpio(dev->of_node, "i2s1-in-sel-gpio1", 0);
	अगर (gpio_is_valid(priv->i2s1_in_mux_gpio_sel_1)) अणु
		ret = devm_gpio_request(dev, priv->i2s1_in_mux_gpio_sel_1,
					"i2s1_in_mux_gpio_sel_1");
		अगर (ret)
			dev_warn(&pdev->dev, "%s devm_gpio_request fail %d\n",
				 __func__, ret);
		gpio_direction_output(priv->i2s1_in_mux_gpio_sel_1, 0);
	पूर्ण

	priv->i2s1_in_mux_gpio_sel_2 =
		of_get_named_gpio(dev->of_node, "i2s1-in-sel-gpio2", 0);
	अगर (gpio_is_valid(priv->i2s1_in_mux_gpio_sel_2)) अणु
		ret = devm_gpio_request(dev, priv->i2s1_in_mux_gpio_sel_2,
					"i2s1_in_mux_gpio_sel_2");
		अगर (ret)
			dev_warn(&pdev->dev, "%s devm_gpio_request fail2 %d\n",
				 __func__, ret);
		gpio_direction_output(priv->i2s1_in_mux_gpio_sel_2, 0);
	पूर्ण
	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);

	अगर (ret)
		dev_err(&pdev->dev, "%s snd_soc_register_card fail %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mt2701_cs42448_machine_dt_match[] = अणु
	अणु.compatible = "mediatek,mt2701-cs42448-machine",पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mt2701_cs42448_machine = अणु
	.driver = अणु
		.name = "mt2701-cs42448",
		   #अगर_घोषित CONFIG_OF
		   .of_match_table = mt2701_cs42448_machine_dt_match,
		   #पूर्ण_अगर
	पूर्ण,
	.probe = mt2701_cs42448_machine_probe,
पूर्ण;

module_platक्रमm_driver(mt2701_cs42448_machine);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT2701 CS42448 ALSA SoC machine driver");
MODULE_AUTHOR("Ir Lian <ir.lian@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mt2701 cs42448 soc card");
