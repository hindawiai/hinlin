<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * userspace-consumer.c
 *
 * Copyright 2009 CompuLab, Ltd.
 *
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Based of भव consumer driver:
 *   Copyright 2008 Wolfson Microelectronics PLC.
 *   Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/userspace-consumer.h>
#समावेश <linux/slab.h>

काष्ठा userspace_consumer_data अणु
	स्थिर अक्षर *name;

	काष्ठा mutex lock;
	bool enabled;

	पूर्णांक num_supplies;
	काष्ठा regulator_bulk_data *supplies;
पूर्ण;

अटल sमाप_प्रकार reg_show_name(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा userspace_consumer_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण

अटल sमाप_प्रकार reg_show_state(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा userspace_consumer_data *data = dev_get_drvdata(dev);

	अगर (data->enabled)
		वापस प्र_लिखो(buf, "enabled\n");

	वापस प्र_लिखो(buf, "disabled\n");
पूर्ण

अटल sमाप_प्रकार reg_set_state(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा userspace_consumer_data *data = dev_get_drvdata(dev);
	bool enabled;
	पूर्णांक ret;

	/*
	 * sysfs_streq() करोesn't need the \n's, but we add them so the strings
	 * will be shared with show_state(), above.
	 */
	अगर (sysfs_streq(buf, "enabled\n") || sysfs_streq(buf, "1"))
		enabled = true;
	अन्यथा अगर (sysfs_streq(buf, "disabled\n") || sysfs_streq(buf, "0"))
		enabled = false;
	अन्यथा अणु
		dev_err(dev, "Configuring invalid mode\n");
		वापस count;
	पूर्ण

	mutex_lock(&data->lock);
	अगर (enabled != data->enabled) अणु
		अगर (enabled)
			ret = regulator_bulk_enable(data->num_supplies,
						    data->supplies);
		अन्यथा
			ret = regulator_bulk_disable(data->num_supplies,
						     data->supplies);

		अगर (ret == 0)
			data->enabled = enabled;
		अन्यथा
			dev_err(dev, "Failed to configure state: %d\n", ret);
	पूर्ण
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(name, 0444, reg_show_name, शून्य);
अटल DEVICE_ATTR(state, 0644, reg_show_state, reg_set_state);

अटल काष्ठा attribute *attributes[] = अणु
	&dev_attr_name.attr,
	&dev_attr_state.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group attr_group = अणु
	.attrs	= attributes,
पूर्ण;

अटल पूर्णांक regulator_userspace_consumer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_userspace_consumer_data *pdata;
	काष्ठा userspace_consumer_data *drvdata;
	पूर्णांक ret;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata)
		वापस -EINVAL;

	drvdata = devm_kzalloc(&pdev->dev,
			       माप(काष्ठा userspace_consumer_data),
			       GFP_KERNEL);
	अगर (drvdata == शून्य)
		वापस -ENOMEM;

	drvdata->name = pdata->name;
	drvdata->num_supplies = pdata->num_supplies;
	drvdata->supplies = pdata->supplies;

	mutex_init(&drvdata->lock);

	ret = devm_regulator_bulk_get(&pdev->dev, drvdata->num_supplies,
				      drvdata->supplies);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = sysfs_create_group(&pdev->dev.kobj, &attr_group);
	अगर (ret != 0)
		वापस ret;

	अगर (pdata->init_on) अणु
		ret = regulator_bulk_enable(drvdata->num_supplies,
					    drvdata->supplies);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to set initial state: %d\n", ret);
			जाओ err_enable;
		पूर्ण
	पूर्ण

	drvdata->enabled = pdata->init_on;
	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;

err_enable:
	sysfs_हटाओ_group(&pdev->dev.kobj, &attr_group);

	वापस ret;
पूर्ण

अटल पूर्णांक regulator_userspace_consumer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा userspace_consumer_data *data = platक्रमm_get_drvdata(pdev);

	sysfs_हटाओ_group(&pdev->dev.kobj, &attr_group);

	अगर (data->enabled)
		regulator_bulk_disable(data->num_supplies, data->supplies);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver regulator_userspace_consumer_driver = अणु
	.probe		= regulator_userspace_consumer_probe,
	.हटाओ		= regulator_userspace_consumer_हटाओ,
	.driver		= अणु
		.name		= "reg-userspace-consumer",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(regulator_userspace_consumer_driver);

MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("Userspace consumer for voltage and current regulators");
MODULE_LICENSE("GPL");
