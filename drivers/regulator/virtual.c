<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * reg-भव-consumer.c
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

काष्ठा भव_consumer_data अणु
	काष्ठा mutex lock;
	काष्ठा regulator *regulator;
	bool enabled;
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	पूर्णांक min_uA;
	पूर्णांक max_uA;
	अचिन्हित पूर्णांक mode;
पूर्ण;

अटल व्योम update_voltage_स्थिरraपूर्णांकs(काष्ठा device *dev,
				       काष्ठा भव_consumer_data *data)
अणु
	पूर्णांक ret;

	अगर (data->min_uV && data->max_uV
	    && data->min_uV <= data->max_uV) अणु
		dev_dbg(dev, "Requesting %d-%duV\n",
			data->min_uV, data->max_uV);
		ret = regulator_set_voltage(data->regulator,
					data->min_uV, data->max_uV);
		अगर (ret != 0) अणु
			dev_err(dev,
				"regulator_set_voltage() failed: %d\n", ret);
			वापस;
		पूर्ण
	पूर्ण

	अगर (data->min_uV && data->max_uV && !data->enabled) अणु
		dev_dbg(dev, "Enabling regulator\n");
		ret = regulator_enable(data->regulator);
		अगर (ret == 0)
			data->enabled = true;
		अन्यथा
			dev_err(dev, "regulator_enable() failed: %d\n",
				ret);
	पूर्ण

	अगर (!(data->min_uV && data->max_uV) && data->enabled) अणु
		dev_dbg(dev, "Disabling regulator\n");
		ret = regulator_disable(data->regulator);
		अगर (ret == 0)
			data->enabled = false;
		अन्यथा
			dev_err(dev, "regulator_disable() failed: %d\n",
				ret);
	पूर्ण
पूर्ण

अटल व्योम update_current_limit_स्थिरraपूर्णांकs(काष्ठा device *dev,
					  काष्ठा भव_consumer_data *data)
अणु
	पूर्णांक ret;

	अगर (data->max_uA
	    && data->min_uA <= data->max_uA) अणु
		dev_dbg(dev, "Requesting %d-%duA\n",
			data->min_uA, data->max_uA);
		ret = regulator_set_current_limit(data->regulator,
					data->min_uA, data->max_uA);
		अगर (ret != 0) अणु
			dev_err(dev,
				"regulator_set_current_limit() failed: %d\n",
				ret);
			वापस;
		पूर्ण
	पूर्ण

	अगर (data->max_uA && !data->enabled) अणु
		dev_dbg(dev, "Enabling regulator\n");
		ret = regulator_enable(data->regulator);
		अगर (ret == 0)
			data->enabled = true;
		अन्यथा
			dev_err(dev, "regulator_enable() failed: %d\n",
				ret);
	पूर्ण

	अगर (!(data->min_uA && data->max_uA) && data->enabled) अणु
		dev_dbg(dev, "Disabling regulator\n");
		ret = regulator_disable(data->regulator);
		अगर (ret == 0)
			data->enabled = false;
		अन्यथा
			dev_err(dev, "regulator_disable() failed: %d\n",
				ret);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार show_min_uV(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->min_uV);
पूर्ण

अटल sमाप_प्रकार set_min_uV(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) != 0)
		वापस count;

	mutex_lock(&data->lock);

	data->min_uV = val;
	update_voltage_स्थिरraपूर्णांकs(dev, data);

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_max_uV(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->max_uV);
पूर्ण

अटल sमाप_प्रकार set_max_uV(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) != 0)
		वापस count;

	mutex_lock(&data->lock);

	data->max_uV = val;
	update_voltage_स्थिरraपूर्णांकs(dev, data);

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_min_uA(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->min_uA);
पूर्ण

अटल sमाप_प्रकार set_min_uA(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) != 0)
		वापस count;

	mutex_lock(&data->lock);

	data->min_uA = val;
	update_current_limit_स्थिरraपूर्णांकs(dev, data);

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_max_uA(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->max_uA);
पूर्ण

अटल sमाप_प्रकार set_max_uA(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) != 0)
		वापस count;

	mutex_lock(&data->lock);

	data->max_uA = val;
	update_current_limit_स्थिरraपूर्णांकs(dev, data);

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_mode(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);

	चयन (data->mode) अणु
	हाल REGULATOR_MODE_FAST:
		वापस प्र_लिखो(buf, "fast\n");
	हाल REGULATOR_MODE_NORMAL:
		वापस प्र_लिखो(buf, "normal\n");
	हाल REGULATOR_MODE_IDLE:
		वापस प्र_लिखो(buf, "idle\n");
	हाल REGULATOR_MODE_STANDBY:
		वापस प्र_लिखो(buf, "standby\n");
	शेष:
		वापस प्र_लिखो(buf, "unknown\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार set_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा भव_consumer_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	/*
	 * sysfs_streq() करोesn't need the \n's, but we add them so the strings
	 * will be shared with show_mode(), above.
	 */
	अगर (sysfs_streq(buf, "fast\n"))
		mode = REGULATOR_MODE_FAST;
	अन्यथा अगर (sysfs_streq(buf, "normal\n"))
		mode = REGULATOR_MODE_NORMAL;
	अन्यथा अगर (sysfs_streq(buf, "idle\n"))
		mode = REGULATOR_MODE_IDLE;
	अन्यथा अगर (sysfs_streq(buf, "standby\n"))
		mode = REGULATOR_MODE_STANDBY;
	अन्यथा अणु
		dev_err(dev, "Configuring invalid mode\n");
		वापस count;
	पूर्ण

	mutex_lock(&data->lock);
	ret = regulator_set_mode(data->regulator, mode);
	अगर (ret == 0)
		data->mode = mode;
	अन्यथा
		dev_err(dev, "Failed to configure mode: %d\n", ret);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(min_microvolts, 0664, show_min_uV, set_min_uV);
अटल DEVICE_ATTR(max_microvolts, 0664, show_max_uV, set_max_uV);
अटल DEVICE_ATTR(min_microamps, 0664, show_min_uA, set_min_uA);
अटल DEVICE_ATTR(max_microamps, 0664, show_max_uA, set_max_uA);
अटल DEVICE_ATTR(mode, 0664, show_mode, set_mode);

अटल काष्ठा attribute *regulator_भव_attributes[] = अणु
	&dev_attr_min_microvolts.attr,
	&dev_attr_max_microvolts.attr,
	&dev_attr_min_microamps.attr,
	&dev_attr_max_microamps.attr,
	&dev_attr_mode.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group regulator_भव_attr_group = अणु
	.attrs	= regulator_भव_attributes,
पूर्ण;

अटल पूर्णांक regulator_भव_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अक्षर *reg_id = dev_get_platdata(&pdev->dev);
	काष्ठा भव_consumer_data *drvdata;
	पूर्णांक ret;

	drvdata = devm_kzalloc(&pdev->dev, माप(काष्ठा भव_consumer_data),
			       GFP_KERNEL);
	अगर (drvdata == शून्य)
		वापस -ENOMEM;

	mutex_init(&drvdata->lock);

	drvdata->regulator = devm_regulator_get(&pdev->dev, reg_id);
	अगर (IS_ERR(drvdata->regulator)) अणु
		ret = PTR_ERR(drvdata->regulator);
		dev_err(&pdev->dev, "Failed to obtain supply '%s': %d\n",
			reg_id, ret);
		वापस ret;
	पूर्ण

	ret = sysfs_create_group(&pdev->dev.kobj,
				 &regulator_भव_attr_group);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev,
			"Failed to create attribute group: %d\n", ret);
		वापस ret;
	पूर्ण

	drvdata->mode = regulator_get_mode(drvdata->regulator);

	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_भव_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा भव_consumer_data *drvdata = platक्रमm_get_drvdata(pdev);

	sysfs_हटाओ_group(&pdev->dev.kobj, &regulator_भव_attr_group);

	अगर (drvdata->enabled)
		regulator_disable(drvdata->regulator);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver regulator_भव_consumer_driver = अणु
	.probe		= regulator_भव_probe,
	.हटाओ		= regulator_भव_हटाओ,
	.driver		= अणु
		.name		= "reg-virt-consumer",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(regulator_भव_consumer_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("Virtual regulator consumer");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:reg-virt-consumer");
