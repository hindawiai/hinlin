<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt5682.c  --  RT5682 ALSA SoC audio component driver
//
// Copyright 2018 Realtek Semiconductor Corp.
// Author: Bard Liao <bardliao@realtek.com>
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/rt5682.h>

#समावेश "rl6231.h"
#समावेश "rt5682.h"

अटल स्थिर काष्ठा rt5682_platक्रमm_data i2s_शेष_platक्रमm_data = अणु
	.dmic1_data_pin = RT5682_DMIC1_DATA_GPIO2,
	.dmic1_clk_pin = RT5682_DMIC1_CLK_GPIO3,
	.jd_src = RT5682_JD1,
	.btndet_delay = 16,
	.dai_clk_names[RT5682_DAI_WCLK_IDX] = "rt5682-dai-wclk",
	.dai_clk_names[RT5682_DAI_BCLK_IDX] = "rt5682-dai-bclk",
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5682_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = RT5682_I2C_MODE,
	.अस्थिर_reg = rt5682_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5682_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5682_reg,
	.num_reg_शेषs = RT5682_REG_NUM,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल व्योम rt5682_jd_check_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5682_priv *rt5682 = container_of(work, काष्ठा rt5682_priv,
		jd_check_work.work);

	अगर (snd_soc_component_पढ़ो(rt5682->component, RT5682_AJD1_CTRL)
		& RT5682_JDH_RS_MASK) अणु
		/* jack out */
		rt5682->jack_type = rt5682_headset_detect(rt5682->component, 0);

		snd_soc_jack_report(rt5682->hs_jack, rt5682->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&rt5682->jd_check_work, 500);
	पूर्ण
पूर्ण

अटल irqवापस_t rt5682_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5682_priv *rt5682 = data;

	mod_delayed_work(प्रणाली_घातer_efficient_wq,
		&rt5682->jack_detect_work, msecs_to_jअगरfies(rt5682->irq_work_delay_समय));

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा snd_soc_dai_driver rt5682_dai[] = अणु
	अणु
		.name = "rt5682-aif1",
		.id = RT5682_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.ops = &rt5682_aअगर1_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5682-aif2",
		.id = RT5682_AIF2,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5682_STEREO_RATES,
			.क्रमmats = RT5682_FORMATS,
		पूर्ण,
		.ops = &rt5682_aअगर2_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt5682_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5682_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt5682_priv *rt5682;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;

	rt5682 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5682_priv),
		GFP_KERNEL);
	अगर (!rt5682)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5682);

	rt5682->pdata = i2s_शेष_platक्रमm_data;

	अगर (pdata)
		rt5682->pdata = *pdata;
	अन्यथा
		rt5682_parse_dt(rt5682, &i2c->dev);

	rt5682->regmap = devm_regmap_init_i2c(i2c, &rt5682_regmap);
	अगर (IS_ERR(rt5682->regmap)) अणु
		ret = PTR_ERR(rt5682->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rt5682->supplies); i++)
		rt5682->supplies[i].supply = rt5682_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(rt5682->supplies),
				      rt5682->supplies);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(rt5682->supplies),
				    rt5682->supplies);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (gpio_is_valid(rt5682->pdata.lकरो1_en)) अणु
		अगर (devm_gpio_request_one(&i2c->dev, rt5682->pdata.lकरो1_en,
					  GPIOF_OUT_INIT_HIGH, "rt5682"))
			dev_err(&i2c->dev, "Fail gpio_request gpio_ldo\n");
	पूर्ण

	/* Sleep क्रम 300 ms miniumum */
	usleep_range(300000, 350000);

	regmap_ग_लिखो(rt5682->regmap, RT5682_I2C_MODE, 0x1);
	usleep_range(10000, 15000);

	regmap_पढ़ो(rt5682->regmap, RT5682_DEVICE_ID, &val);
	अगर (val != DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt5682\n", val);
		वापस -ENODEV;
	पूर्ण

	mutex_init(&rt5682->calibrate_mutex);
	rt5682_calibrate(rt5682);

	rt5682_apply_patch_list(rt5682, &i2c->dev);

	regmap_ग_लिखो(rt5682->regmap, RT5682_DEPOP_1, 0x0000);

	/* DMIC pin*/
	अगर (rt5682->pdata.dmic1_data_pin != RT5682_DMIC1_शून्य) अणु
		चयन (rt5682->pdata.dmic1_data_pin) अणु
		हाल RT5682_DMIC1_DATA_GPIO2: /* share with LRCK2 */
			regmap_update_bits(rt5682->regmap, RT5682_DMIC_CTRL_1,
				RT5682_DMIC_1_DP_MASK, RT5682_DMIC_1_DP_GPIO2);
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP2_PIN_MASK, RT5682_GP2_PIN_DMIC_SDA);
			अवरोध;

		हाल RT5682_DMIC1_DATA_GPIO5: /* share with DACDAT1 */
			regmap_update_bits(rt5682->regmap, RT5682_DMIC_CTRL_1,
				RT5682_DMIC_1_DP_MASK, RT5682_DMIC_1_DP_GPIO5);
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP5_PIN_MASK, RT5682_GP5_PIN_DMIC_SDA);
			अवरोध;

		शेष:
			dev_warn(&i2c->dev, "invalid DMIC_DAT pin\n");
			अवरोध;
		पूर्ण

		चयन (rt5682->pdata.dmic1_clk_pin) अणु
		हाल RT5682_DMIC1_CLK_GPIO1: /* share with IRQ */
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP1_PIN_MASK, RT5682_GP1_PIN_DMIC_CLK);
			अवरोध;

		हाल RT5682_DMIC1_CLK_GPIO3: /* share with BCLK2 */
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP3_PIN_MASK, RT5682_GP3_PIN_DMIC_CLK);
			अगर (rt5682->pdata.dmic_clk_driving_high)
				regmap_update_bits(rt5682->regmap,
					RT5682_PAD_DRIVING_CTRL,
					RT5682_PAD_DRV_GP3_MASK,
					2 << RT5682_PAD_DRV_GP3_SFT);
			अवरोध;

		शेष:
			dev_warn(&i2c->dev, "invalid DMIC_CLK pin\n");
			अवरोध;
		पूर्ण
	पूर्ण

	regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
		RT5682_LDO1_DVO_MASK | RT5682_HP_DRIVER_MASK,
		RT5682_LDO1_DVO_12 | RT5682_HP_DRIVER_5X);
	regmap_ग_लिखो(rt5682->regmap, RT5682_MICBIAS_2, 0x0080);
	regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
		RT5682_GP4_PIN_MASK | RT5682_GP5_PIN_MASK,
		RT5682_GP4_PIN_ADCDAT1 | RT5682_GP5_PIN_DACDAT1);
	regmap_ग_लिखो(rt5682->regmap, RT5682_TEST_MODE_CTRL_1, 0x0000);
	regmap_update_bits(rt5682->regmap, RT5682_BIAS_CUR_CTRL_8,
		RT5682_HPA_CP_BIAS_CTRL_MASK, RT5682_HPA_CP_BIAS_3UA);
	regmap_update_bits(rt5682->regmap, RT5682_CHARGE_PUMP_1,
		RT5682_CP_CLK_HP_MASK, RT5682_CP_CLK_HP_300KHZ);
	regmap_update_bits(rt5682->regmap, RT5682_HP_CHARGE_PUMP_1,
		RT5682_PM_HP_MASK, RT5682_PM_HP_HV);
	regmap_update_bits(rt5682->regmap, RT5682_DMIC_CTRL_1,
		RT5682_FIFO_CLK_DIV_MASK, RT5682_FIFO_CLK_DIV_2);

	INIT_DELAYED_WORK(&rt5682->jack_detect_work,
		rt5682_jack_detect_handler);
	INIT_DELAYED_WORK(&rt5682->jd_check_work,
		rt5682_jd_check_handler);

	अगर (i2c->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
			rt5682_irq, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5682", rt5682);
		अगर (ret)
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
					       &rt5682_soc_component_dev,
					       rt5682_dai, ARRAY_SIZE(rt5682_dai));
पूर्ण

अटल व्योम rt5682_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5682_priv *rt5682 = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&rt5682->jack_detect_work);
	cancel_delayed_work_sync(&rt5682->jd_check_work);

	rt5682_reset(rt5682);
पूर्ण

अटल स्थिर काष्ठा of_device_id rt5682_of_match[] = अणु
	अणु.compatible = "realtek,rt5682i"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5682_of_match);

अटल स्थिर काष्ठा acpi_device_id rt5682_acpi_match[] = अणु
	अणु"10EC5682", 0,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5682_acpi_match);

अटल स्थिर काष्ठा i2c_device_id rt5682_i2c_id[] = अणु
	अणु"rt5682", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5682_i2c_id);

अटल काष्ठा i2c_driver rt5682_i2c_driver = अणु
	.driver = अणु
		.name = "rt5682",
		.of_match_table = rt5682_of_match,
		.acpi_match_table = rt5682_acpi_match,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe = rt5682_i2c_probe,
	.shutकरोwn = rt5682_i2c_shutकरोwn,
	.id_table = rt5682_i2c_id,
पूर्ण;
module_i2c_driver(rt5682_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5682 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
