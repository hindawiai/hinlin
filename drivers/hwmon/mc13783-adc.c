<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम the ADC on Freescale Semiconductor MC13783 and MC13892 PMICs.
 *
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2009 Sascha Hauer, Pengutronix
 */

#समावेश <linux/mfd/mc13xxx.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>

#घोषणा DRIVER_NAME	"mc13783-adc"

/* platक्रमm device id driver data */
#घोषणा MC13783_ADC_16CHANS	1
#घोषणा MC13783_ADC_BPDIV2	2

काष्ठा mc13783_adc_priv अणु
	काष्ठा mc13xxx *mc13xxx;
	काष्ठा device *hwmon_dev;
	अक्षर name[PLATFORM_NAME_SIZE];
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा mc13783_adc_priv *priv = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", priv->name);
पूर्ण

अटल पूर्णांक mc13783_adc_पढ़ो(काष्ठा device *dev,
		काष्ठा device_attribute *devattr, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा mc13783_adc_priv *priv = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	अचिन्हित पूर्णांक channel = attr->index;
	अचिन्हित पूर्णांक sample[4];
	पूर्णांक ret;

	ret = mc13xxx_adc_करो_conversion(priv->mc13xxx,
			MC13XXX_ADC_MODE_MULT_CHAN,
			channel, 0, 0, sample);
	अगर (ret)
		वापस ret;

	/* ADIN7 subchannels */
	अगर (channel >= 16)
		channel = 7;

	channel &= 0x7;

	*val = (sample[channel % 4] >> (channel > 3 ? 14 : 2)) & 0x3ff;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mc13783_adc_bp_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	अचिन्हित val;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	kernel_uदीर्घ_t driver_data = platक्रमm_get_device_id(pdev)->driver_data;
	पूर्णांक ret = mc13783_adc_पढ़ो(dev, devattr, &val);

	अगर (ret)
		वापस ret;

	अगर (driver_data & MC13783_ADC_BPDIV2)
		val = DIV_ROUND_CLOSEST(val * 9, 2);
	अन्यथा
		/*
		 * BP (channel 2) reports with offset 2.4V to the actual value
		 * to fit the input range of the ADC.  unit = 2.25mV = 9/4 mV.
		 */
		val = DIV_ROUND_CLOSEST(val * 9, 4) + 2400;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार mc13783_adc_gp_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	अचिन्हित val;
	पूर्णांक ret = mc13783_adc_पढ़ो(dev, devattr, &val);

	अगर (ret)
		वापस ret;

	/*
	 * input range is [0, 2.3V], val has 10 bits, so each bit
	 * is worth 9/4 mV.
	 */
	val = DIV_ROUND_CLOSEST(val * 9, 4);

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार mc13783_adc_uid_show(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    अक्षर *buf)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	kernel_uदीर्घ_t driver_data = platक्रमm_get_device_id(pdev)->driver_data;
	पूर्णांक ret = mc13783_adc_पढ़ो(dev, devattr, &val);

	अगर (ret)
		वापस ret;

	अगर (driver_data & MC13783_ADC_BPDIV2)
		/* MC13892 have 1/2 भागider, input range is [0, 4.800V] */
		val = DIV_ROUND_CLOSEST(val * 4800, 1024);
	अन्यथा
		/* MC13783 have 0.9 भागider, input range is [0, 2.555V] */
		val = DIV_ROUND_CLOSEST(val * 2555, 1024);

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार mc13783_adc_temp_show(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     अक्षर *buf)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	kernel_uदीर्घ_t driver_data = platक्रमm_get_device_id(pdev)->driver_data;
	पूर्णांक ret = mc13783_adc_पढ़ो(dev, devattr, &val);

	अगर (ret)
		वापस ret;

	अगर (driver_data & MC13783_ADC_BPDIV2) अणु
		/*
		 * MC13892:
		 * Die Temperature Read Out Code at 25C 680
		 * Temperature change per LSB +0.4244C
		 */
		ret = DIV_ROUND_CLOSEST(-2635920 + val * 4244, 10);
	पूर्ण अन्यथा अणु
		/*
		 * MC13783:
		 * Die Temperature Read Out Code at 25C 282
		 * Temperature change per LSB -1.14C
		 */
		ret = 346480 - 1140 * val;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल DEVICE_ATTR_RO(name);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, mc13783_adc_bp, 2);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, mc13783_adc_gp, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, mc13783_adc_gp, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, mc13783_adc_gp, 7);
अटल SENSOR_DEVICE_ATTR_RO(in8_input, mc13783_adc_gp, 8);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, mc13783_adc_gp, 9);
अटल SENSOR_DEVICE_ATTR_RO(in10_input, mc13783_adc_gp, 10);
अटल SENSOR_DEVICE_ATTR_RO(in11_input, mc13783_adc_gp, 11);
अटल SENSOR_DEVICE_ATTR_RO(in12_input, mc13783_adc_gp, 12);
अटल SENSOR_DEVICE_ATTR_RO(in13_input, mc13783_adc_gp, 13);
अटल SENSOR_DEVICE_ATTR_RO(in14_input, mc13783_adc_gp, 14);
अटल SENSOR_DEVICE_ATTR_RO(in15_input, mc13783_adc_gp, 15);
अटल SENSOR_DEVICE_ATTR_RO(in16_input, mc13783_adc_uid, 16);
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, mc13783_adc_temp, 17);

अटल काष्ठा attribute *mc13783_attr_base[] = अणु
	&dev_attr_name.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in16_input.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc13783_group_base = अणु
	.attrs = mc13783_attr_base,
पूर्ण;

/* these are only used अगर MC13783_ADC_16CHANS is provided in driver data */
अटल काष्ठा attribute *mc13783_attr_16chans[] = अणु
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in11_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc13783_group_16chans = अणु
	.attrs = mc13783_attr_16chans,
पूर्ण;

/* last four channels may be occupied by the touchscreen */
अटल काष्ठा attribute *mc13783_attr_ts[] = अणु
	&sensor_dev_attr_in12_input.dev_attr.attr,
	&sensor_dev_attr_in13_input.dev_attr.attr,
	&sensor_dev_attr_in14_input.dev_attr.attr,
	&sensor_dev_attr_in15_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc13783_group_ts = अणु
	.attrs = mc13783_attr_ts,
पूर्ण;

अटल पूर्णांक mc13783_adc_use_touchscreen(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_adc_priv *priv = platक्रमm_get_drvdata(pdev);
	अचिन्हित flags = mc13xxx_get_flags(priv->mc13xxx);

	वापस flags & MC13XXX_USE_TOUCHSCREEN;
पूर्ण

अटल पूर्णांक __init mc13783_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_adc_priv *priv;
	पूर्णांक ret;
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	अक्षर *dash;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->mc13xxx = dev_get_drvdata(pdev->dev.parent);
	snम_लिखो(priv->name, ARRAY_SIZE(priv->name), "%s", id->name);
	dash = म_अक्षर(priv->name, '-');
	अगर (dash)
		*dash = '\0';

	platक्रमm_set_drvdata(pdev, priv);

	/* Register sysfs hooks */
	ret = sysfs_create_group(&pdev->dev.kobj, &mc13783_group_base);
	अगर (ret)
		वापस ret;

	अगर (id->driver_data & MC13783_ADC_16CHANS) अणु
		ret = sysfs_create_group(&pdev->dev.kobj,
				&mc13783_group_16chans);
		अगर (ret)
			जाओ out_err_create_16chans;
	पूर्ण

	अगर (!mc13783_adc_use_touchscreen(pdev)) अणु
		ret = sysfs_create_group(&pdev->dev.kobj, &mc13783_group_ts);
		अगर (ret)
			जाओ out_err_create_ts;
	पूर्ण

	priv->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(priv->hwmon_dev)) अणु
		ret = PTR_ERR(priv->hwmon_dev);
		dev_err(&pdev->dev,
				"hwmon_device_register failed with %d.\n", ret);
		जाओ out_err_रेजिस्टर;
	पूर्ण

	वापस 0;

out_err_रेजिस्टर:

	अगर (!mc13783_adc_use_touchscreen(pdev))
		sysfs_हटाओ_group(&pdev->dev.kobj, &mc13783_group_ts);
out_err_create_ts:

	अगर (id->driver_data & MC13783_ADC_16CHANS)
		sysfs_हटाओ_group(&pdev->dev.kobj, &mc13783_group_16chans);
out_err_create_16chans:

	sysfs_हटाओ_group(&pdev->dev.kobj, &mc13783_group_base);
	वापस ret;
पूर्ण

अटल पूर्णांक mc13783_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_adc_priv *priv = platक्रमm_get_drvdata(pdev);
	kernel_uदीर्घ_t driver_data = platक्रमm_get_device_id(pdev)->driver_data;

	hwmon_device_unरेजिस्टर(priv->hwmon_dev);

	अगर (!mc13783_adc_use_touchscreen(pdev))
		sysfs_हटाओ_group(&pdev->dev.kobj, &mc13783_group_ts);

	अगर (driver_data & MC13783_ADC_16CHANS)
		sysfs_हटाओ_group(&pdev->dev.kobj, &mc13783_group_16chans);

	sysfs_हटाओ_group(&pdev->dev.kobj, &mc13783_group_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mc13783_adc_idtable[] = अणु
	अणु
		.name = "mc13783-adc",
		.driver_data = MC13783_ADC_16CHANS,
	पूर्ण, अणु
		.name = "mc13892-adc",
		.driver_data = MC13783_ADC_BPDIV2,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mc13783_adc_idtable);

अटल काष्ठा platक्रमm_driver mc13783_adc_driver = अणु
	.हटाओ		= mc13783_adc_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.id_table	= mc13783_adc_idtable,
पूर्ण;

module_platक्रमm_driver_probe(mc13783_adc_driver, mc13783_adc_probe);

MODULE_DESCRIPTION("MC13783 ADC driver");
MODULE_AUTHOR("Luotao Fu <l.fu@pengutronix.de>");
MODULE_LICENSE("GPL");
