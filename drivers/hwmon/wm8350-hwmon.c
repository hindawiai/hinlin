<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/hwmon/wm8350-hwmon.c - Wolfson Microelectronics WM8350 PMIC
 *                                  hardware monitoring features.
 *
 * Copyright (C) 2009 Wolfson Microelectronics plc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/comparator.h>

अटल स्थिर अक्षर * स्थिर input_names[] = अणु
	[WM8350_AUXADC_USB]  = "USB",
	[WM8350_AUXADC_LINE] = "Line",
	[WM8350_AUXADC_BATT] = "Battery",
पूर्ण;

अटल sमाप_प्रकार show_voltage(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;
	पूर्णांक val;

	val = wm8350_पढ़ो_auxadc(wm8350, channel, 0, 0) * WM8350_AUX_COEFF;
	val = DIV_ROUND_CLOSEST(val, 1000);

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार show_label(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%s\n", input_names[channel]);
पूर्ण

#घोषणा WM8350_NAMED_VOLTAGE(id, name) \
	अटल SENSOR_DEVICE_ATTR(in##id##_input, S_IRUGO, show_voltage,\
				  शून्य, name);		\
	अटल SENSOR_DEVICE_ATTR(in##id##_label, S_IRUGO, show_label,	\
				  शून्य, name)

WM8350_NAMED_VOLTAGE(0, WM8350_AUXADC_USB);
WM8350_NAMED_VOLTAGE(1, WM8350_AUXADC_BATT);
WM8350_NAMED_VOLTAGE(2, WM8350_AUXADC_LINE);

अटल काष्ठा attribute *wm8350_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_label.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_label.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_label.dev_attr.attr,

	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(wm8350);

अटल पूर्णांक wm8350_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = platक्रमm_get_drvdata(pdev);
	काष्ठा device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev, "wm8350",
							   wm8350,
							   wm8350_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver wm8350_hwmon_driver = अणु
	.probe = wm8350_hwmon_probe,
	.driver = अणु
		.name = "wm8350-hwmon",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm8350_hwmon_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM8350 Hardware Monitoring");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-hwmon");
