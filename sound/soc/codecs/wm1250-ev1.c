<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the 1250-EV1 audio I/O module
 *
 * Copyright 2011 Wolfson Microelectronics plc
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/wm1250-ev1.h>

अटल स्थिर अक्षर *wm1250_gpio_names[WM1250_EV1_NUM_GPIOS] = अणु
	"WM1250 CLK_ENA",
	"WM1250 CLK_SEL0",
	"WM1250 CLK_SEL1",
	"WM1250 OSR",
	"WM1250 MASTER",
पूर्ण;

काष्ठा wm1250_priv अणु
	काष्ठा gpio gpios[WM1250_EV1_NUM_GPIOS];
पूर्ण;

अटल पूर्णांक wm1250_ev1_set_bias_level(काष्ठा snd_soc_component *component,
				     क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm1250_priv *wm1250 = dev_get_drvdata(component->dev);
	पूर्णांक ena;

	अगर (wm1250)
		ena = wm1250->gpios[WM1250_EV1_GPIO_CLK_ENA].gpio;
	अन्यथा
		ena = -1;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (ena >= 0)
			gpio_set_value_cansleep(ena, 1);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		अगर (ena >= 0)
			gpio_set_value_cansleep(ena, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wm1250_ev1_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_ADC("ADC", "wm1250-ev1 Capture", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_DAC("DAC", "wm1250-ev1 Playback", SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_INPUT("WM1250 Input"),
SND_SOC_DAPM_OUTPUT("WM1250 Output"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm1250_ev1_dapm_routes[] = अणु
	अणु "ADC", शून्य, "WM1250 Input" पूर्ण,
	अणु "WM1250 Output", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक wm1250_ev1_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wm1250_priv *wm1250 = snd_soc_component_get_drvdata(dai->component);

	चयन (params_rate(params)) अणु
	हाल 8000:
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].gpio,
			       1);
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].gpio,
			       1);
		अवरोध;
	हाल 16000:
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].gpio,
			       0);
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].gpio,
			       1);
		अवरोध;
	हाल 32000:
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].gpio,
			       1);
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].gpio,
			       0);
		अवरोध;
	हाल 64000:
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].gpio,
			       0);
		gpio_set_value(wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].gpio,
			       0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm1250_ev1_ops = अणु
	.hw_params = wm1250_ev1_hw_params,
पूर्ण;

#घोषणा WM1250_EV1_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |\
			  SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_64000)

अटल काष्ठा snd_soc_dai_driver wm1250_ev1_dai = अणु
	.name = "wm1250-ev1",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM1250_EV1_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM1250_EV1_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &wm1250_ev1_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm1250_ev1 = अणु
	.dapm_widमाला_लो		= wm1250_ev1_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm1250_ev1_dapm_widमाला_लो),
	.dapm_routes		= wm1250_ev1_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm1250_ev1_dapm_routes),
	.set_bias_level		= wm1250_ev1_set_bias_level,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm1250_ev1_pdata(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm1250_ev1_pdata *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा wm1250_priv *wm1250;
	पूर्णांक i, ret;

	अगर (!pdata)
		वापस 0;

	wm1250 = devm_kzalloc(&i2c->dev, माप(*wm1250), GFP_KERNEL);
	अगर (!wm1250) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm1250->gpios); i++) अणु
		wm1250->gpios[i].gpio = pdata->gpios[i];
		wm1250->gpios[i].label = wm1250_gpio_names[i];
		wm1250->gpios[i].flags = GPIOF_OUT_INIT_LOW;
	पूर्ण
	wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].flags = GPIOF_OUT_INIT_HIGH;
	wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].flags = GPIOF_OUT_INIT_HIGH;

	ret = gpio_request_array(wm1250->gpios, ARRAY_SIZE(wm1250->gpios));
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to get GPIOs: %d\n", ret);
		जाओ err;
	पूर्ण

	dev_set_drvdata(&i2c->dev, wm1250);

	वापस ret;

err:
	वापस ret;
पूर्ण

अटल व्योम wm1250_ev1_मुक्त(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm1250_priv *wm1250 = dev_get_drvdata(&i2c->dev);

	अगर (wm1250)
		gpio_मुक्त_array(wm1250->gpios, ARRAY_SIZE(wm1250->gpios));
पूर्ण

अटल पूर्णांक wm1250_ev1_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	पूर्णांक id, board, rev, ret;

	dev_set_drvdata(&i2c->dev, शून्य);

	board = i2c_smbus_पढ़ो_byte_data(i2c, 0);
	अगर (board < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID: %d\n", board);
		वापस board;
	पूर्ण

	id = (board & 0xfe) >> 2;
	rev = board & 0x3;

	अगर (id != 1) अणु
		dev_err(&i2c->dev, "Unknown board ID %d\n", id);
		वापस -ENODEV;
	पूर्ण

	dev_info(&i2c->dev, "revision %d\n", rev + 1);

	ret = wm1250_ev1_pdata(i2c);
	अगर (ret != 0)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &soc_component_dev_wm1250_ev1,
				     &wm1250_ev1_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		wm1250_ev1_मुक्त(i2c);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm1250_ev1_हटाओ(काष्ठा i2c_client *i2c)
अणु
	wm1250_ev1_मुक्त(i2c);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm1250_ev1_i2c_id[] = अणु
	अणु "wm1250-ev1", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm1250_ev1_i2c_id);

अटल काष्ठा i2c_driver wm1250_ev1_i2c_driver = अणु
	.driver = अणु
		.name = "wm1250-ev1",
	पूर्ण,
	.probe =    wm1250_ev1_probe,
	.हटाओ =   wm1250_ev1_हटाओ,
	.id_table = wm1250_ev1_i2c_id,
पूर्ण;

module_i2c_driver(wm1250_ev1_i2c_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM1250-EV1 audio I/O module driver");
MODULE_LICENSE("GPL");
