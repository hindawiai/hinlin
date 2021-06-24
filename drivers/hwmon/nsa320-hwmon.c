<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/hwmon/nsa320-hwmon.c
 *
 * ZyXEL NSA320 Media Servers
 * hardware monitoring
 *
 * Copyright (C) 2016 Adam Baker <linux@baker-net.org.uk>
 * based on a board file driver
 * Copyright (C) 2012 Peter Schildmann <linux@schildmann.info>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

/* Tests क्रम error वापस values rely upon this value being < 0x80 */
#घोषणा MAGIC_NUMBER 0x55

/*
 * The Zyxel hwmon MCU is a Holtek HT46R065 that is factory programmed
 * to perक्रमm temperature and fan speed monitoring. It is पढ़ो by taking
 * the active pin low. The 32 bit output word is then घड़ीed onto the
 * data line. The MSB of the data word is a magic nuber to indicate it
 * has been पढ़ो correctly, the next byte is the fan speed (in hundreds
 * of RPM) and the last two bytes are the temperature (in tenths of a
 * degree)
 */

काष्ठा nsa320_hwmon अणु
	काष्ठा mutex		update_lock;	/* lock GPIO operations */
	अचिन्हित दीर्घ		last_updated;	/* jअगरfies */
	अचिन्हित दीर्घ		mcu_data;
	काष्ठा gpio_desc	*act;
	काष्ठा gpio_desc	*clk;
	काष्ठा gpio_desc	*data;
पूर्ण;

क्रमागत nsa320_inमाला_दो अणु
	NSA320_TEMP = 0,
	NSA320_FAN = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर nsa320_input_names[] = अणु
	[NSA320_TEMP] = "System Temperature",
	[NSA320_FAN] = "Chassis Fan",
पूर्ण;

/*
 * Although this protocol looks similar to SPI the दीर्घ delay
 * between the active (aka chip select) संकेत and the लघुer
 * delay between घड़ी pulses are needed क्रम reliable operation.
 * The delays provided are taken from the manufacturer kernel,
 * testing suggest they probably incorporate a reasonable safety
 * margin. (The single device tested became unreliable अगर the
 * delay was reduced to 1/10th of this value.)
 */
अटल s32 nsa320_hwmon_update(काष्ठा device *dev)
अणु
	u32 mcu_data;
	u32 mask;
	काष्ठा nsa320_hwmon *hwmon = dev_get_drvdata(dev);

	mutex_lock(&hwmon->update_lock);

	mcu_data = hwmon->mcu_data;

	अगर (समय_after(jअगरfies, hwmon->last_updated + HZ) || mcu_data == 0) अणु
		gpiod_set_value(hwmon->act, 1);
		msleep(100);

		mcu_data = 0;
		क्रम (mask = BIT(31); mask; mask >>= 1) अणु
			gpiod_set_value(hwmon->clk, 0);
			usleep_range(100, 200);
			gpiod_set_value(hwmon->clk, 1);
			usleep_range(100, 200);
			अगर (gpiod_get_value(hwmon->data))
				mcu_data |= mask;
		पूर्ण

		gpiod_set_value(hwmon->act, 0);
		dev_dbg(dev, "Read raw MCU data %08x\n", mcu_data);

		अगर ((mcu_data >> 24) != MAGIC_NUMBER) अणु
			dev_dbg(dev, "Read invalid MCU data %08x\n", mcu_data);
			mcu_data = -EIO;
		पूर्ण अन्यथा अणु
			hwmon->mcu_data = mcu_data;
			hwmon->last_updated = jअगरfies;
		पूर्ण
	पूर्ण

	mutex_unlock(&hwmon->update_lock);

	वापस mcu_data;
पूर्ण

अटल sमाप_प्रकार label_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%s\n", nsa320_input_names[channel]);
पूर्ण

अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	s32 mcu_data = nsa320_hwmon_update(dev);

	अगर (mcu_data < 0)
		वापस mcu_data;

	वापस प्र_लिखो(buf, "%d\n", (mcu_data & 0xffff) * 100);
पूर्ण

अटल sमाप_प्रकार fan1_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	s32 mcu_data = nsa320_hwmon_update(dev);

	अगर (mcu_data < 0)
		वापस mcu_data;

	वापस प्र_लिखो(buf, "%d\n", ((mcu_data & 0xff0000) >> 16) * 100);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_label, label, NSA320_TEMP);
अटल DEVICE_ATTR_RO(temp1_input);
अटल SENSOR_DEVICE_ATTR_RO(fan1_label, label, NSA320_FAN);
अटल DEVICE_ATTR_RO(fan1_input);

अटल काष्ठा attribute *nsa320_attrs[] = अणु
	&sensor_dev_attr_temp1_label.dev_attr.attr,
	&dev_attr_temp1_input.attr,
	&sensor_dev_attr_fan1_label.dev_attr.attr,
	&dev_attr_fan1_input.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(nsa320);

अटल स्थिर काष्ठा of_device_id of_nsa320_hwmon_match[] = अणु
	अणु .compatible = "zyxel,nsa320-mcu", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक nsa320_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nsa320_hwmon	*hwmon;
	काष्ठा device		*classdev;

	hwmon = devm_kzalloc(&pdev->dev, माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	/* Look up the GPIO pins to use */
	hwmon->act = devm_gpiod_get(&pdev->dev, "act", GPIOD_OUT_LOW);
	अगर (IS_ERR(hwmon->act))
		वापस PTR_ERR(hwmon->act);

	hwmon->clk = devm_gpiod_get(&pdev->dev, "clk", GPIOD_OUT_HIGH);
	अगर (IS_ERR(hwmon->clk))
		वापस PTR_ERR(hwmon->clk);

	hwmon->data = devm_gpiod_get(&pdev->dev, "data", GPIOD_IN);
	अगर (IS_ERR(hwmon->data))
		वापस PTR_ERR(hwmon->data);

	mutex_init(&hwmon->update_lock);

	classdev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
					"nsa320", hwmon, nsa320_groups);

	वापस PTR_ERR_OR_ZERO(classdev);

पूर्ण

/* All allocations use devres so हटाओ() is not needed. */

अटल काष्ठा platक्रमm_driver nsa320_hwmon_driver = अणु
	.probe = nsa320_hwmon_probe,
	.driver = अणु
		.name = "nsa320-hwmon",
		.of_match_table = of_match_ptr(of_nsa320_hwmon_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(nsa320_hwmon_driver);

MODULE_DEVICE_TABLE(of, of_nsa320_hwmon_match);
MODULE_AUTHOR("Peter Schildmann <linux@schildmann.info>");
MODULE_AUTHOR("Adam Baker <linux@baker-net.org.uk>");
MODULE_DESCRIPTION("NSA320 Hardware Monitoring");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:nsa320-hwmon");
