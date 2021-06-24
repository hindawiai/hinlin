<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/hwmon/wm831x-hwmon.c - Wolfson Microelectronics WM831x PMIC
 *                                hardware monitoring features.
 *
 * Copyright (C) 2009 Wolfson Microelectronics plc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/auxadc.h>

अटल स्थिर अक्षर * स्थिर input_names[] = अणु
	[WM831X_AUX_SYSVDD]    = "SYSVDD",
	[WM831X_AUX_USB]       = "USB",
	[WM831X_AUX_BKUP_BATT] = "Backup battery",
	[WM831X_AUX_BATT]      = "Battery",
	[WM831X_AUX_WALL]      = "WALL",
	[WM831X_AUX_CHIP_TEMP] = "PMIC",
	[WM831X_AUX_BATT_TEMP] = "Battery",
पूर्ण;

अटल sमाप_प्रकार show_voltage(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret;

	ret = wm831x_auxadc_पढ़ो_uv(wm831x, channel);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", DIV_ROUND_CLOSEST(ret, 1000));
पूर्ण

अटल sमाप_प्रकार show_chip_temp(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret;

	ret = wm831x_auxadc_पढ़ो(wm831x, channel);
	अगर (ret < 0)
		वापस ret;

	/* Degrees celsius = (512.18-ret) / 1.0983 */
	ret = 512180 - (ret * 1000);
	ret = DIV_ROUND_CLOSEST(ret * 10000, 10983);

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार show_label(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%s\n", input_names[channel]);
पूर्ण

#घोषणा WM831X_VOLTAGE(id, name) \
	अटल SENSOR_DEVICE_ATTR(in##id##_input, S_IRUGO, show_voltage, \
				  शून्य, name)

#घोषणा WM831X_NAMED_VOLTAGE(id, name) \
	WM831X_VOLTAGE(id, name); \
	अटल SENSOR_DEVICE_ATTR(in##id##_label, S_IRUGO, show_label,	\
				  शून्य, name)

WM831X_VOLTAGE(0, WM831X_AUX_AUX1);
WM831X_VOLTAGE(1, WM831X_AUX_AUX2);
WM831X_VOLTAGE(2, WM831X_AUX_AUX3);
WM831X_VOLTAGE(3, WM831X_AUX_AUX4);

WM831X_NAMED_VOLTAGE(4, WM831X_AUX_SYSVDD);
WM831X_NAMED_VOLTAGE(5, WM831X_AUX_USB);
WM831X_NAMED_VOLTAGE(6, WM831X_AUX_BATT);
WM831X_NAMED_VOLTAGE(7, WM831X_AUX_WALL);
WM831X_NAMED_VOLTAGE(8, WM831X_AUX_BKUP_BATT);

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, show_chip_temp, शून्य,
			  WM831X_AUX_CHIP_TEMP);
अटल SENSOR_DEVICE_ATTR(temp1_label, S_IRUGO, show_label, शून्य,
			  WM831X_AUX_CHIP_TEMP);
/*
 * Report as a voltage since conversion depends on बाह्यal components
 * and that's what the ABI wants.
 */
अटल SENSOR_DEVICE_ATTR(temp2_input, S_IRUGO, show_voltage, शून्य,
			  WM831X_AUX_BATT_TEMP);
अटल SENSOR_DEVICE_ATTR(temp2_label, S_IRUGO, show_label, शून्य,
			  WM831X_AUX_BATT_TEMP);

अटल काष्ठा attribute *wm831x_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,

	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_label.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_label.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_label.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_label.dev_attr.attr,
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in8_label.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_label.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_label.dev_attr.attr,

	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(wm831x);

अटल पूर्णांक wm831x_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev, "wm831x",
							   wm831x,
							   wm831x_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_hwmon_driver = अणु
	.probe = wm831x_hwmon_probe,
	.driver = अणु
		.name = "wm831x-hwmon",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm831x_hwmon_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM831x Hardware Monitoring");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-hwmon");
