<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Goodix touchscreens that use the i2c-hid protocol.
 *
 * Copyright 2020 Google LLC
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "i2c-hid.h"

काष्ठा goodix_i2c_hid_timing_data अणु
	अचिन्हित पूर्णांक post_gpio_reset_delay_ms;
	अचिन्हित पूर्णांक post_घातer_delay_ms;
पूर्ण;

काष्ठा i2c_hid_of_goodix अणु
	काष्ठा i2chid_ops ops;

	काष्ठा regulator *vdd;
	काष्ठा gpio_desc *reset_gpio;
	स्थिर काष्ठा goodix_i2c_hid_timing_data *timings;
पूर्ण;

अटल पूर्णांक goodix_i2c_hid_घातer_up(काष्ठा i2chid_ops *ops)
अणु
	काष्ठा i2c_hid_of_goodix *ihid_goodix =
		container_of(ops, काष्ठा i2c_hid_of_goodix, ops);
	पूर्णांक ret;

	ret = regulator_enable(ihid_goodix->vdd);
	अगर (ret)
		वापस ret;

	अगर (ihid_goodix->timings->post_घातer_delay_ms)
		msleep(ihid_goodix->timings->post_घातer_delay_ms);

	gpiod_set_value_cansleep(ihid_goodix->reset_gpio, 0);
	अगर (ihid_goodix->timings->post_gpio_reset_delay_ms)
		msleep(ihid_goodix->timings->post_gpio_reset_delay_ms);

	वापस 0;
पूर्ण

अटल व्योम goodix_i2c_hid_घातer_करोwn(काष्ठा i2chid_ops *ops)
अणु
	काष्ठा i2c_hid_of_goodix *ihid_goodix =
		container_of(ops, काष्ठा i2c_hid_of_goodix, ops);

	gpiod_set_value_cansleep(ihid_goodix->reset_gpio, 1);
	regulator_disable(ihid_goodix->vdd);
पूर्ण

अटल पूर्णांक i2c_hid_of_goodix_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_hid_of_goodix *ihid_goodix;

	ihid_goodix = devm_kzalloc(&client->dev, माप(*ihid_goodix),
				   GFP_KERNEL);
	अगर (!ihid_goodix)
		वापस -ENOMEM;

	ihid_goodix->ops.घातer_up = goodix_i2c_hid_घातer_up;
	ihid_goodix->ops.घातer_करोwn = goodix_i2c_hid_घातer_करोwn;

	/* Start out with reset निश्चितed */
	ihid_goodix->reset_gpio =
		devm_gpiod_get_optional(&client->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ihid_goodix->reset_gpio))
		वापस PTR_ERR(ihid_goodix->reset_gpio);

	ihid_goodix->vdd = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(ihid_goodix->vdd))
		वापस PTR_ERR(ihid_goodix->vdd);

	ihid_goodix->timings = device_get_match_data(&client->dev);

	वापस i2c_hid_core_probe(client, &ihid_goodix->ops, 0x0001);
पूर्ण

अटल स्थिर काष्ठा goodix_i2c_hid_timing_data goodix_gt7375p_timing_data = अणु
	.post_घातer_delay_ms = 10,
	.post_gpio_reset_delay_ms = 180,
पूर्ण;

अटल स्थिर काष्ठा of_device_id goodix_i2c_hid_of_match[] = अणु
	अणु .compatible = "goodix,gt7375p", .data = &goodix_gt7375p_timing_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, goodix_i2c_hid_of_match);

अटल काष्ठा i2c_driver goodix_i2c_hid_ts_driver = अणु
	.driver = अणु
		.name	= "i2c_hid_of_goodix",
		.pm	= &i2c_hid_core_pm,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(goodix_i2c_hid_of_match),
	पूर्ण,
	.probe		= i2c_hid_of_goodix_probe,
	.हटाओ		= i2c_hid_core_हटाओ,
	.shutकरोwn	= i2c_hid_core_shutकरोwn,
पूर्ण;
module_i2c_driver(goodix_i2c_hid_ts_driver);

MODULE_AUTHOR("Douglas Anderson <dianders@chromium.org>");
MODULE_DESCRIPTION("Goodix i2c-hid touchscreen driver");
MODULE_LICENSE("GPL v2");
