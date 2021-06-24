<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Raspberry Pi voltage sensor driver
 *
 * Based on firmware/raspberrypi.c by Noralf Trथचnnes
 *
 * Copyright (C) 2018 Stefan Wahren <stefan.wahren@i2se.com>
 */
#समावेश <linux/device.h>
#समावेश <linux/devm-helpers.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

#घोषणा UNDERVOLTAGE_STICKY_BIT	BIT(16)

काष्ठा rpi_hwmon_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा rpi_firmware *fw;
	u32 last_throttled;
	काष्ठा delayed_work get_values_poll_work;
पूर्ण;

अटल व्योम rpi_firmware_get_throttled(काष्ठा rpi_hwmon_data *data)
अणु
	u32 new_uv, old_uv, value;
	पूर्णांक ret;

	/* Request firmware to clear sticky bits */
	value = 0xffff;

	ret = rpi_firmware_property(data->fw, RPI_FIRMWARE_GET_THROTTLED,
				    &value, माप(value));
	अगर (ret) अणु
		dev_err_once(data->hwmon_dev, "Failed to get throttled (%d)\n",
			     ret);
		वापस;
	पूर्ण

	new_uv = value & UNDERVOLTAGE_STICKY_BIT;
	old_uv = data->last_throttled & UNDERVOLTAGE_STICKY_BIT;
	data->last_throttled = value;

	अगर (new_uv == old_uv)
		वापस;

	अगर (new_uv)
		dev_crit(data->hwmon_dev, "Undervoltage detected!\n");
	अन्यथा
		dev_info(data->hwmon_dev, "Voltage normalised\n");

	sysfs_notअगरy(&data->hwmon_dev->kobj, शून्य, "in0_lcrit_alarm");
पूर्ण

अटल व्योम get_values_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpi_hwmon_data *data;

	data = container_of(work, काष्ठा rpi_hwmon_data,
			    get_values_poll_work.work);

	rpi_firmware_get_throttled(data);

	/*
	 * We can't run faster than the sticky shअगरt (100ms) since we get
	 * flipping in the sticky bits that are cleared.
	 */
	schedule_delayed_work(&data->get_values_poll_work, 2 * HZ);
पूर्ण

अटल पूर्णांक rpi_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा rpi_hwmon_data *data = dev_get_drvdata(dev);

	*val = !!(data->last_throttled & UNDERVOLTAGE_STICKY_BIT);
	वापस 0;
पूर्ण

अटल umode_t rpi_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel)
अणु
	वापस 0444;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *rpi_info[] = अणु
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_LCRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops rpi_hwmon_ops = अणु
	.is_visible = rpi_is_visible,
	.पढ़ो = rpi_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info rpi_chip_info = अणु
	.ops = &rpi_hwmon_ops,
	.info = rpi_info,
पूर्ण;

अटल पूर्णांक rpi_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpi_hwmon_data *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Parent driver assure that firmware is correct */
	data->fw = dev_get_drvdata(dev->parent);

	data->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, "rpi_volt",
							       data,
							       &rpi_chip_info,
							       शून्य);

	ret = devm_delayed_work_स्वतःcancel(dev, &data->get_values_poll_work,
					   get_values_poll);
	अगर (ret)
		वापस ret;
	platक्रमm_set_drvdata(pdev, data);

	अगर (!PTR_ERR_OR_ZERO(data->hwmon_dev))
		schedule_delayed_work(&data->get_values_poll_work, 2 * HZ);

	वापस PTR_ERR_OR_ZERO(data->hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver rpi_hwmon_driver = अणु
	.probe = rpi_hwmon_probe,
	.driver = अणु
		.name = "raspberrypi-hwmon",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rpi_hwmon_driver);

MODULE_AUTHOR("Stefan Wahren <wahrenst@gmx.net>");
MODULE_DESCRIPTION("Raspberry Pi voltage sensor driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:raspberrypi-hwmon");
