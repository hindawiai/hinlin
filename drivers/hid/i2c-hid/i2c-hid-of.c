<शैली गुरु>
/*
 * HID over I2C Open Firmware Subclass
 *
 * Copyright (c) 2012 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 * Copyright (c) 2012 Ecole Nationale de l'Aviation Civile, France
 * Copyright (c) 2012 Red Hat, Inc
 *
 * This code was विभाजनed out of the core code, which was partly based on
 * "USB HID support for Linux":
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2007-2008 Oliver Neukum
 *  Copyright (c) 2006-2010 Jiri Kosina
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "i2c-hid.h"

काष्ठा i2c_hid_of अणु
	काष्ठा i2chid_ops ops;

	काष्ठा i2c_client *client;
	काष्ठा regulator_bulk_data supplies[2];
	पूर्णांक post_घातer_delay_ms;
पूर्ण;

अटल पूर्णांक i2c_hid_of_घातer_up(काष्ठा i2chid_ops *ops)
अणु
	काष्ठा i2c_hid_of *ihid_of = container_of(ops, काष्ठा i2c_hid_of, ops);
	काष्ठा device *dev = &ihid_of->client->dev;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ihid_of->supplies),
				    ihid_of->supplies);
	अगर (ret) अणु
		dev_warn(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ihid_of->post_घातer_delay_ms)
		msleep(ihid_of->post_घातer_delay_ms);

	वापस 0;
पूर्ण

अटल व्योम i2c_hid_of_घातer_करोwn(काष्ठा i2chid_ops *ops)
अणु
	काष्ठा i2c_hid_of *ihid_of = container_of(ops, काष्ठा i2c_hid_of, ops);

	regulator_bulk_disable(ARRAY_SIZE(ihid_of->supplies),
			       ihid_of->supplies);
पूर्ण

अटल पूर्णांक i2c_hid_of_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *dev_id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_hid_of *ihid_of;
	u16 hid_descriptor_address;
	पूर्णांक ret;
	u32 val;

	ihid_of = devm_kzalloc(&client->dev, माप(*ihid_of), GFP_KERNEL);
	अगर (!ihid_of)
		वापस -ENOMEM;

	ihid_of->ops.घातer_up = i2c_hid_of_घातer_up;
	ihid_of->ops.घातer_करोwn = i2c_hid_of_घातer_करोwn;

	ret = of_property_पढ़ो_u32(dev->of_node, "hid-descr-addr", &val);
	अगर (ret) अणु
		dev_err(&client->dev, "HID register address not provided\n");
		वापस -ENODEV;
	पूर्ण
	अगर (val >> 16) अणु
		dev_err(&client->dev, "Bad HID register address: 0x%08x\n",
			val);
		वापस -EINVAL;
	पूर्ण
	hid_descriptor_address = val;

	अगर (!device_property_पढ़ो_u32(&client->dev, "post-power-on-delay-ms",
				      &val))
		ihid_of->post_घातer_delay_ms = val;

	ihid_of->supplies[0].supply = "vdd";
	ihid_of->supplies[1].supply = "vddl";
	ret = devm_regulator_bulk_get(&client->dev,
				      ARRAY_SIZE(ihid_of->supplies),
				      ihid_of->supplies);
	अगर (ret)
		वापस ret;

	वापस i2c_hid_core_probe(client, &ihid_of->ops,
				  hid_descriptor_address);
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_hid_of_match[] = अणु
	अणु .compatible = "hid-over-i2c" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_hid_of_match);

अटल स्थिर काष्ठा i2c_device_id i2c_hid_of_id_table[] = अणु
	अणु "hid", 0 पूर्ण,
	अणु "hid-over-i2c", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, i2c_hid_of_id_table);

अटल काष्ठा i2c_driver i2c_hid_of_driver = अणु
	.driver = अणु
		.name	= "i2c_hid_of",
		.pm	= &i2c_hid_core_pm,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(i2c_hid_of_match),
	पूर्ण,

	.probe		= i2c_hid_of_probe,
	.हटाओ		= i2c_hid_core_हटाओ,
	.shutकरोwn	= i2c_hid_core_shutकरोwn,
	.id_table	= i2c_hid_of_id_table,
पूर्ण;

module_i2c_driver(i2c_hid_of_driver);

MODULE_DESCRIPTION("HID over I2C OF driver");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_LICENSE("GPL");
