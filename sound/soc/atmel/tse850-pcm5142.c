<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// TSE-850 audio - ASoC driver क्रम the Axentia TSE-850 with a PCM5142 codec
//
// Copyright (C) 2016 Axentia Technologies AB
//
// Author: Peter Rosin <peda@axentia.se>
//
//               loop1 relays
//   IN1 +---o  +------------+  o---+ OUT1
//            \                /
//             +              +
//             |   /          |
//             +--o  +--.     |
//             |  add   |     |
//             |        V     |
//             |      .---.   |
//   DAC +----------->|Sum|---+
//             |      '---'   |
//             |              |
//             +              +
//
//   IN2 +---o--+------------+--o---+ OUT2
//               loop2 relays
//
// The 'loop1' gpio pin controlls two relays, which are either in loop
// position, meaning that input and output are directly connected, or
// they are in mixer position, meaning that the संकेत is passed through
// the 'Sum' mixer. Similarly for 'loop2'.
//
// In the above, the 'loop1' relays are inactive, thus feeding IN1 to the
// mixer (अगर 'add' is active) and feeding the mixer output to OUT1. The
// 'loop2' relays are active, लघु-cutting the TSE-850 from channel 2.
// IN1, IN2, OUT1 and OUT2 are TSE-850 connectors and DAC is the PCB name
// of the (filtered) output from the PCM5142 codec.

#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

काष्ठा tse850_priv अणु
	काष्ठा gpio_desc *add;
	काष्ठा gpio_desc *loop1;
	काष्ठा gpio_desc *loop2;

	काष्ठा regulator *ana;

	पूर्णांक add_cache;
	पूर्णांक loop1_cache;
	पूर्णांक loop2_cache;
पूर्ण;

अटल पूर्णांक tse850_get_mux1(काष्ठा snd_kcontrol *kctrl,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);

	ucontrol->value.क्रमागतerated.item[0] = tse850->loop1_cache;

	वापस 0;
पूर्ण

अटल पूर्णांक tse850_put_mux1(काष्ठा snd_kcontrol *kctrl,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kctrl->निजी_value;
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0];

	अगर (val >= e->items)
		वापस -EINVAL;

	gpiod_set_value_cansleep(tse850->loop1, val);
	tse850->loop1_cache = val;

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kctrl, ucontrol);
पूर्ण

अटल पूर्णांक tse850_get_mux2(काष्ठा snd_kcontrol *kctrl,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);

	ucontrol->value.क्रमागतerated.item[0] = tse850->loop2_cache;

	वापस 0;
पूर्ण

अटल पूर्णांक tse850_put_mux2(काष्ठा snd_kcontrol *kctrl,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kctrl->निजी_value;
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0];

	अगर (val >= e->items)
		वापस -EINVAL;

	gpiod_set_value_cansleep(tse850->loop2, val);
	tse850->loop2_cache = val;

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kctrl, ucontrol);
पूर्ण

अटल पूर्णांक tse850_get_mix(काष्ठा snd_kcontrol *kctrl,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);

	ucontrol->value.क्रमागतerated.item[0] = tse850->add_cache;

	वापस 0;
पूर्ण

अटल पूर्णांक tse850_put_mix(काष्ठा snd_kcontrol *kctrl,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);
	पूर्णांक connect = !!ucontrol->value.पूर्णांकeger.value[0];

	अगर (tse850->add_cache == connect)
		वापस 0;

	/*
	 * Hmmm, this gpiod_set_value_cansleep call should probably happen
	 * inside snd_soc_dapm_mixer_update_घातer in the loop.
	 */
	gpiod_set_value_cansleep(tse850->add, connect);
	tse850->add_cache = connect;

	snd_soc_dapm_mixer_update_घातer(dapm, kctrl, connect, शून्य);
	वापस 1;
पूर्ण

अटल पूर्णांक tse850_get_ana(काष्ठा snd_kcontrol *kctrl,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	ret = regulator_get_voltage(tse850->ana);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Map regulator output values like so:
	 *      -11.5V to "Low" (क्रमागत 0)
	 * 11.5V-12.5V to "12V" (क्रमागत 1)
	 * 12.5V-13.5V to "13V" (क्रमागत 2)
	 *     ...
	 * 18.5V-19.5V to "19V" (क्रमागत 8)
	 * 19.5V-      to "20V" (क्रमागत 9)
	 */
	अगर (ret < 11000000)
		ret = 11000000;
	अन्यथा अगर (ret > 20000000)
		ret = 20000000;
	ret -= 11000000;
	ret = (ret + 500000) / 1000000;

	ucontrol->value.क्रमागतerated.item[0] = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tse850_put_ana(काष्ठा snd_kcontrol *kctrl,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kctrl->निजी_value;
	अचिन्हित पूर्णांक uV = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक ret;

	अगर (uV >= e->items)
		वापस -EINVAL;

	/*
	 * Map क्रमागत zero (Low) to 2 volts on the regulator, करो this since
	 * the ana regulator is supplied by the प्रणाली 12V voltage and
	 * requesting anything below the प्रणाली voltage causes the प्रणाली
	 * voltage to be passed through the regulator. Also, the ana
	 * regulator induces noise when requesting voltages near the
	 * प्रणाली voltage. So, by mapping Low to 2V, that noise is
	 * eliminated when all that is needed is 12V (the प्रणाली voltage).
	 */
	अगर (uV)
		uV = 11000000 + (1000000 * uV);
	अन्यथा
		uV = 2000000;

	ret = regulator_set_voltage(tse850->ana, uV, uV);
	अगर (ret < 0)
		वापस ret;

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kctrl, ucontrol);
पूर्ण

अटल स्थिर अक्षर * स्थिर mux_text[] = अणु "Mixer", "Loop" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत mux_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, ARRAY_SIZE(mux_text), mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new mux1 =
	SOC_DAPM_ENUM_EXT("MUX1", mux_क्रमागत, tse850_get_mux1, tse850_put_mux1);

अटल स्थिर काष्ठा snd_kcontrol_new mux2 =
	SOC_DAPM_ENUM_EXT("MUX2", mux_क्रमागत, tse850_get_mux2, tse850_put_mux2);

#घोषणा TSE850_DAPM_SINGLE_EXT(xname, reg, shअगरt, max, invert, xget, xput) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = xget, \
	.put = xput, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 0) पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mix[] = अणु
	TSE850_DAPM_SINGLE_EXT("IN Switch", SND_SOC_NOPM, 0, 1, 0,
			       tse850_get_mix, tse850_put_mix),
पूर्ण;

अटल स्थिर अक्षर * स्थिर ana_text[] = अणु
	"Low", "12V", "13V", "14V", "15V", "16V", "17V", "18V", "19V", "20V"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ana_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, ARRAY_SIZE(ana_text), ana_text);

अटल स्थिर काष्ठा snd_kcontrol_new out =
	SOC_DAPM_ENUM_EXT("ANA", ana_क्रमागत, tse850_get_ana, tse850_put_ana);

अटल स्थिर काष्ठा snd_soc_dapm_widget tse850_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("OUT1", शून्य),
	SND_SOC_DAPM_LINE("OUT2", शून्य),
	SND_SOC_DAPM_LINE("IN1", शून्य),
	SND_SOC_DAPM_LINE("IN2", शून्य),
	SND_SOC_DAPM_INPUT("DAC"),
	SND_SOC_DAPM_AIF_IN("AIFINL", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINR", "Playback", 1, SND_SOC_NOPM, 0, 0),
	SOC_MIXER_ARRAY("MIX", SND_SOC_NOPM, 0, 0, mix),
	SND_SOC_DAPM_MUX("MUX1", SND_SOC_NOPM, 0, 0, &mux1),
	SND_SOC_DAPM_MUX("MUX2", SND_SOC_NOPM, 0, 0, &mux2),
	SND_SOC_DAPM_OUT_DRV("OUT", SND_SOC_NOPM, 0, 0, &out, 1),
पूर्ण;

/*
 * These connections are not entirely correct, since both IN1 and IN2
 * are always fed to MIX (अगर the "IN switch" is set so), i.e. without
 * regard to the loop1 and loop2 relays that according to this only
 * control MUX1 and MUX2 but in fact also control how the input संकेतs
 * are routed.
 * But, 1) I करोn't know how to do it right, and 2) it doesn't seem to
 * matter in practice since nothing is घातered in those sections anyway.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route tse850_पूर्णांकercon[] = अणु
	अणु "OUT1", शून्य, "MUX1" पूर्ण,
	अणु "OUT2", शून्य, "MUX2" पूर्ण,

	अणु "MUX1", "Loop",  "IN1" पूर्ण,
	अणु "MUX1", "Mixer", "OUT" पूर्ण,

	अणु "MUX2", "Loop",  "IN2" पूर्ण,
	अणु "MUX2", "Mixer", "OUT" पूर्ण,

	अणु "OUT", शून्य, "MIX" पूर्ण,

	अणु "MIX", शून्य, "DAC" पूर्ण,
	अणु "MIX", "IN Switch", "IN1" पूर्ण,
	अणु "MIX", "IN Switch", "IN2" पूर्ण,

	/* connect board input to the codec left channel output pin */
	अणु "DAC", शून्य, "OUTL" पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "pcm512x-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tse850_dailink = अणु
	.name = "TSE-850",
	.stream_name = "TSE-850-PCM",
	.dai_fmt = SND_SOC_DAIFMT_I2S
		 | SND_SOC_DAIFMT_NB_NF
		 | SND_SOC_DAIFMT_CBM_CFS,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card tse850_card = अणु
	.name = "TSE-850-ASoC",
	.owner = THIS_MODULE,
	.dai_link = &tse850_dailink,
	.num_links = 1,
	.dapm_widमाला_लो = tse850_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tse850_dapm_widमाला_लो),
	.dapm_routes = tse850_पूर्णांकercon,
	.num_dapm_routes = ARRAY_SIZE(tse850_पूर्णांकercon),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tse850_dt_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *codec_np, *cpu_np;
	काष्ठा snd_soc_dai_link *dailink = &tse850_dailink;

	अगर (!np) अणु
		dev_err(&pdev->dev, "only device tree supported\n");
		वापस -EINVAL;
	पूर्ण

	cpu_np = of_parse_phandle(np, "axentia,cpu-dai", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "failed to get cpu dai\n");
		वापस -EINVAL;
	पूर्ण
	dailink->cpus->of_node = cpu_np;
	dailink->platक्रमms->of_node = cpu_np;
	of_node_put(cpu_np);

	codec_np = of_parse_phandle(np, "axentia,audio-codec", 0);
	अगर (!codec_np) अणु
		dev_err(&pdev->dev, "failed to get codec info\n");
		वापस -EINVAL;
	पूर्ण
	dailink->codecs->of_node = codec_np;
	of_node_put(codec_np);

	वापस 0;
पूर्ण

अटल पूर्णांक tse850_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &tse850_card;
	काष्ठा device *dev = card->dev = &pdev->dev;
	काष्ठा tse850_priv *tse850;
	पूर्णांक ret;

	tse850 = devm_kzalloc(dev, माप(*tse850), GFP_KERNEL);
	अगर (!tse850)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(card, tse850);

	ret = tse850_dt_init(pdev);
	अगर (ret) अणु
		dev_err(dev, "failed to init dt info\n");
		वापस ret;
	पूर्ण

	tse850->add = devm_gpiod_get(dev, "axentia,add", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tse850->add)) अणु
		अगर (PTR_ERR(tse850->add) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'add' gpio\n");
		वापस PTR_ERR(tse850->add);
	पूर्ण
	tse850->add_cache = 1;

	tse850->loop1 = devm_gpiod_get(dev, "axentia,loop1", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tse850->loop1)) अणु
		अगर (PTR_ERR(tse850->loop1) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'loop1' gpio\n");
		वापस PTR_ERR(tse850->loop1);
	पूर्ण
	tse850->loop1_cache = 1;

	tse850->loop2 = devm_gpiod_get(dev, "axentia,loop2", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tse850->loop2)) अणु
		अगर (PTR_ERR(tse850->loop2) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'loop2' gpio\n");
		वापस PTR_ERR(tse850->loop2);
	पूर्ण
	tse850->loop2_cache = 1;

	tse850->ana = devm_regulator_get(dev, "axentia,ana");
	अगर (IS_ERR(tse850->ana)) अणु
		अगर (PTR_ERR(tse850->ana) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'ana' regulator\n");
		वापस PTR_ERR(tse850->ana);
	पूर्ण

	ret = regulator_enable(tse850->ana);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable the 'ana' regulator\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(dev, "snd_soc_register_card failed\n");
		जाओ err_disable_ana;
	पूर्ण

	वापस 0;

err_disable_ana:
	regulator_disable(tse850->ana);
	वापस ret;
पूर्ण

अटल पूर्णांक tse850_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा tse850_priv *tse850 = snd_soc_card_get_drvdata(card);

	snd_soc_unरेजिस्टर_card(card);
	regulator_disable(tse850->ana);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tse850_dt_ids[] = अणु
	अणु .compatible = "axentia,tse850-pcm5142", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tse850_dt_ids);

अटल काष्ठा platक्रमm_driver tse850_driver = अणु
	.driver = अणु
		.name = "axentia-tse850-pcm5142",
		.of_match_table = of_match_ptr(tse850_dt_ids),
	पूर्ण,
	.probe = tse850_probe,
	.हटाओ = tse850_हटाओ,
पूर्ण;

module_platक्रमm_driver(tse850_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_DESCRIPTION("ALSA SoC driver for TSE-850 with PCM5142 codec");
MODULE_LICENSE("GPL v2");
