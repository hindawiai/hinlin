<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * gpio-fan.c - Hwmon driver क्रम fans connected to GPIO lines.
 *
 * Copyright (C) 2010 LaCie
 *
 * Author: Simon Guinot <sguinot@lacie.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/thermal.h>

काष्ठा gpio_fan_speed अणु
	पूर्णांक rpm;
	पूर्णांक ctrl_val;
पूर्ण;

काष्ठा gpio_fan_data अणु
	काष्ठा device		*dev;
	काष्ठा device		*hwmon_dev;
	/* Cooling device अगर any */
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा mutex		lock; /* lock GPIOs operations. */
	पूर्णांक			num_gpios;
	काष्ठा gpio_desc	**gpios;
	पूर्णांक			num_speed;
	काष्ठा gpio_fan_speed	*speed;
	पूर्णांक			speed_index;
#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक			resume_speed;
#पूर्ण_अगर
	bool			pwm_enable;
	काष्ठा gpio_desc	*alarm_gpio;
	काष्ठा work_काष्ठा	alarm_work;
पूर्ण;

/*
 * Alarm GPIO.
 */

अटल व्योम fan_alarm_notअगरy(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा gpio_fan_data *fan_data =
		container_of(ws, काष्ठा gpio_fan_data, alarm_work);

	sysfs_notअगरy(&fan_data->hwmon_dev->kobj, शून्य, "fan1_alarm");
	kobject_uevent(&fan_data->hwmon_dev->kobj, KOBJ_CHANGE);
पूर्ण

अटल irqवापस_t fan_alarm_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_id;

	schedule_work(&fan_data->alarm_work);

	वापस IRQ_NONE;
पूर्ण

अटल sमाप_प्रकार fan1_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       gpiod_get_value_cansleep(fan_data->alarm_gpio));
पूर्ण

अटल DEVICE_ATTR_RO(fan1_alarm);

अटल पूर्णांक fan_alarm_init(काष्ठा gpio_fan_data *fan_data)
अणु
	पूर्णांक alarm_irq;
	काष्ठा device *dev = fan_data->dev;

	/*
	 * If the alarm GPIO करोn't support पूर्णांकerrupts, just leave
	 * without initializing the fail notअगरication support.
	 */
	alarm_irq = gpiod_to_irq(fan_data->alarm_gpio);
	अगर (alarm_irq <= 0)
		वापस 0;

	INIT_WORK(&fan_data->alarm_work, fan_alarm_notअगरy);
	irq_set_irq_type(alarm_irq, IRQ_TYPE_EDGE_BOTH);
	वापस devm_request_irq(dev, alarm_irq, fan_alarm_irq_handler,
				IRQF_SHARED, "GPIO fan alarm", fan_data);
पूर्ण

/*
 * Control GPIOs.
 */

/* Must be called with fan_data->lock held, except during initialization. */
अटल व्योम __set_fan_ctrl(काष्ठा gpio_fan_data *fan_data, पूर्णांक ctrl_val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fan_data->num_gpios; i++)
		gpiod_set_value_cansleep(fan_data->gpios[i],
					 (ctrl_val >> i) & 1);
पूर्ण

अटल पूर्णांक __get_fan_ctrl(काष्ठा gpio_fan_data *fan_data)
अणु
	पूर्णांक i;
	पूर्णांक ctrl_val = 0;

	क्रम (i = 0; i < fan_data->num_gpios; i++) अणु
		पूर्णांक value;

		value = gpiod_get_value_cansleep(fan_data->gpios[i]);
		ctrl_val |= (value << i);
	पूर्ण
	वापस ctrl_val;
पूर्ण

/* Must be called with fan_data->lock held, except during initialization. */
अटल व्योम set_fan_speed(काष्ठा gpio_fan_data *fan_data, पूर्णांक speed_index)
अणु
	अगर (fan_data->speed_index == speed_index)
		वापस;

	__set_fan_ctrl(fan_data, fan_data->speed[speed_index].ctrl_val);
	fan_data->speed_index = speed_index;
पूर्ण

अटल पूर्णांक get_fan_speed_index(काष्ठा gpio_fan_data *fan_data)
अणु
	पूर्णांक ctrl_val = __get_fan_ctrl(fan_data);
	पूर्णांक i;

	क्रम (i = 0; i < fan_data->num_speed; i++)
		अगर (fan_data->speed[i].ctrl_val == ctrl_val)
			वापस i;

	dev_warn(fan_data->dev,
		 "missing speed array entry for GPIO value 0x%x\n", ctrl_val);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक rpm_to_speed_index(काष्ठा gpio_fan_data *fan_data, अचिन्हित दीर्घ rpm)
अणु
	काष्ठा gpio_fan_speed *speed = fan_data->speed;
	पूर्णांक i;

	क्रम (i = 0; i < fan_data->num_speed; i++)
		अगर (speed[i].rpm >= rpm)
			वापस i;

	वापस fan_data->num_speed - 1;
पूर्ण

अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);
	u8 pwm = fan_data->speed_index * 255 / (fan_data->num_speed - 1);

	वापस प्र_लिखो(buf, "%d\n", pwm);
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ pwm;
	पूर्णांक speed_index;
	पूर्णांक ret = count;

	अगर (kम_से_अदीर्घ(buf, 10, &pwm) || pwm > 255)
		वापस -EINVAL;

	mutex_lock(&fan_data->lock);

	अगर (!fan_data->pwm_enable) अणु
		ret = -EPERM;
		जाओ निकास_unlock;
	पूर्ण

	speed_index = DIV_ROUND_UP(pwm * (fan_data->num_speed - 1), 255);
	set_fan_speed(fan_data, speed_index);

निकास_unlock:
	mutex_unlock(&fan_data->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", fan_data->pwm_enable);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) || val > 1)
		वापस -EINVAL;

	अगर (fan_data->pwm_enable == val)
		वापस count;

	mutex_lock(&fan_data->lock);

	fan_data->pwm_enable = val;

	/* Disable manual control mode: set fan at full speed. */
	अगर (val == 0)
		set_fan_speed(fan_data, fan_data->num_speed - 1);

	mutex_unlock(&fan_data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm1_mode_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार fan1_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", fan_data->speed[0].rpm);
पूर्ण

अटल sमाप_प्रकार fan1_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       fan_data->speed[fan_data->num_speed - 1].rpm);
पूर्ण

अटल sमाप_प्रकार fan1_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", fan_data->speed[fan_data->speed_index].rpm);
पूर्ण

अटल sमाप_प्रकार set_rpm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ rpm;
	पूर्णांक ret = count;

	अगर (kम_से_अदीर्घ(buf, 10, &rpm))
		वापस -EINVAL;

	mutex_lock(&fan_data->lock);

	अगर (!fan_data->pwm_enable) अणु
		ret = -EPERM;
		जाओ निकास_unlock;
	पूर्ण

	set_fan_speed(fan_data, rpm_to_speed_index(fan_data, rpm));

निकास_unlock:
	mutex_unlock(&fan_data->lock);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RW(pwm1);
अटल DEVICE_ATTR_RW(pwm1_enable);
अटल DEVICE_ATTR_RO(pwm1_mode);
अटल DEVICE_ATTR_RO(fan1_min);
अटल DEVICE_ATTR_RO(fan1_max);
अटल DEVICE_ATTR_RO(fan1_input);
अटल DEVICE_ATTR(fan1_target, 0644, fan1_input_show, set_rpm);

अटल umode_t gpio_fan_is_visible(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gpio_fan_data *data = dev_get_drvdata(dev);

	अगर (index == 0 && !data->alarm_gpio)
		वापस 0;
	अगर (index > 0 && !data->gpios)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *gpio_fan_attributes[] = अणु
	&dev_attr_fan1_alarm.attr,		/* 0 */
	&dev_attr_pwm1.attr,			/* 1 */
	&dev_attr_pwm1_enable.attr,
	&dev_attr_pwm1_mode.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_fan1_target.attr,
	&dev_attr_fan1_min.attr,
	&dev_attr_fan1_max.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gpio_fan_group = अणु
	.attrs = gpio_fan_attributes,
	.is_visible = gpio_fan_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *gpio_fan_groups[] = अणु
	&gpio_fan_group,
	शून्य
पूर्ण;

अटल पूर्णांक fan_ctrl_init(काष्ठा gpio_fan_data *fan_data)
अणु
	पूर्णांक num_gpios = fan_data->num_gpios;
	काष्ठा gpio_desc **gpios = fan_data->gpios;
	पूर्णांक i, err;

	क्रम (i = 0; i < num_gpios; i++) अणु
		/*
		 * The GPIO descriptors were retrieved with GPIOD_ASIS so here
		 * we set the GPIO पूर्णांकo output mode, carefully preserving the
		 * current value by setting it to whatever it is alपढ़ोy set
		 * (no surprise changes in शेष fan speed).
		 */
		err = gpiod_direction_output(gpios[i],
					gpiod_get_value_cansleep(gpios[i]));
		अगर (err)
			वापस err;
	पूर्ण

	fan_data->pwm_enable = true; /* Enable manual fan speed control. */
	fan_data->speed_index = get_fan_speed_index(fan_data);
	अगर (fan_data->speed_index < 0)
		वापस fan_data->speed_index;

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_fan_get_max_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ *state)
अणु
	काष्ठा gpio_fan_data *fan_data = cdev->devdata;

	अगर (!fan_data)
		वापस -EINVAL;

	*state = fan_data->num_speed - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_fan_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ *state)
अणु
	काष्ठा gpio_fan_data *fan_data = cdev->devdata;

	अगर (!fan_data)
		वापस -EINVAL;

	*state = fan_data->speed_index;
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_fan_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ state)
अणु
	काष्ठा gpio_fan_data *fan_data = cdev->devdata;

	अगर (!fan_data)
		वापस -EINVAL;

	set_fan_speed(fan_data, state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops gpio_fan_cool_ops = अणु
	.get_max_state = gpio_fan_get_max_state,
	.get_cur_state = gpio_fan_get_cur_state,
	.set_cur_state = gpio_fan_set_cur_state,
पूर्ण;

/*
 * Translate OpenFirmware node properties पूर्णांकo platक्रमm_data
 */
अटल पूर्णांक gpio_fan_get_of_data(काष्ठा gpio_fan_data *fan_data)
अणु
	काष्ठा gpio_fan_speed *speed;
	काष्ठा device *dev = fan_data->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_desc **gpios;
	अचिन्हित i;
	u32 u;
	काष्ठा property *prop;
	स्थिर __be32 *p;

	/* Alarm GPIO अगर one exists */
	fan_data->alarm_gpio = devm_gpiod_get_optional(dev, "alarm", GPIOD_IN);
	अगर (IS_ERR(fan_data->alarm_gpio))
		वापस PTR_ERR(fan_data->alarm_gpio);

	/* Fill GPIO pin array */
	fan_data->num_gpios = gpiod_count(dev, शून्य);
	अगर (fan_data->num_gpios <= 0) अणु
		अगर (fan_data->alarm_gpio)
			वापस 0;
		dev_err(dev, "DT properties empty / missing");
		वापस -ENODEV;
	पूर्ण
	gpios = devm_kसुस्मृति(dev,
			     fan_data->num_gpios, माप(काष्ठा gpio_desc *),
			     GFP_KERNEL);
	अगर (!gpios)
		वापस -ENOMEM;
	क्रम (i = 0; i < fan_data->num_gpios; i++) अणु
		gpios[i] = devm_gpiod_get_index(dev, शून्य, i, GPIOD_ASIS);
		अगर (IS_ERR(gpios[i]))
			वापस PTR_ERR(gpios[i]);
	पूर्ण
	fan_data->gpios = gpios;

	/* Get number of RPM/ctrl_val pairs in speed map */
	prop = of_find_property(np, "gpio-fan,speed-map", &i);
	अगर (!prop) अणु
		dev_err(dev, "gpio-fan,speed-map DT property missing");
		वापस -ENODEV;
	पूर्ण
	i = i / माप(u32);
	अगर (i == 0 || i & 1) अणु
		dev_err(dev, "gpio-fan,speed-map contains zero/odd number of entries");
		वापस -ENODEV;
	पूर्ण
	fan_data->num_speed = i / 2;

	/*
	 * Populate speed map
	 * Speed map is in the क्रमm <RPM ctrl_val RPM ctrl_val ...>
	 * this needs splitting पूर्णांकo pairs to create gpio_fan_speed काष्ठाs
	 */
	speed = devm_kसुस्मृति(dev,
			fan_data->num_speed, माप(काष्ठा gpio_fan_speed),
			GFP_KERNEL);
	अगर (!speed)
		वापस -ENOMEM;
	p = शून्य;
	क्रम (i = 0; i < fan_data->num_speed; i++) अणु
		p = of_prop_next_u32(prop, p, &u);
		अगर (!p)
			वापस -ENODEV;
		speed[i].rpm = u;
		p = of_prop_next_u32(prop, p, &u);
		अगर (!p)
			वापस -ENODEV;
		speed[i].ctrl_val = u;
	पूर्ण
	fan_data->speed = speed;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_gpio_fan_match[] = अणु
	अणु .compatible = "gpio-fan", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_gpio_fan_match);

अटल व्योम gpio_fan_stop(व्योम *data)
अणु
	set_fan_speed(data, 0);
पूर्ण

अटल पूर्णांक gpio_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा gpio_fan_data *fan_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;

	fan_data = devm_kzalloc(dev, माप(काष्ठा gpio_fan_data),
				GFP_KERNEL);
	अगर (!fan_data)
		वापस -ENOMEM;

	fan_data->dev = dev;
	err = gpio_fan_get_of_data(fan_data);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, fan_data);
	mutex_init(&fan_data->lock);

	/* Configure control GPIOs अगर available. */
	अगर (fan_data->gpios && fan_data->num_gpios > 0) अणु
		अगर (!fan_data->speed || fan_data->num_speed <= 1)
			वापस -EINVAL;
		err = fan_ctrl_init(fan_data);
		अगर (err)
			वापस err;
		err = devm_add_action_or_reset(dev, gpio_fan_stop, fan_data);
		अगर (err)
			वापस err;
	पूर्ण

	/* Make this driver part of hwmon class. */
	fan_data->hwmon_dev =
		devm_hwmon_device_रेजिस्टर_with_groups(dev,
						       "gpio_fan", fan_data,
						       gpio_fan_groups);
	अगर (IS_ERR(fan_data->hwmon_dev))
		वापस PTR_ERR(fan_data->hwmon_dev);

	/* Configure alarm GPIO अगर available. */
	अगर (fan_data->alarm_gpio) अणु
		err = fan_alarm_init(fan_data);
		अगर (err)
			वापस err;
	पूर्ण

	/* Optional cooling device रेजिस्टर क्रम Device tree platक्रमms */
	fan_data->cdev = devm_thermal_of_cooling_device_रेजिस्टर(dev, np,
				"gpio-fan", fan_data, &gpio_fan_cool_ops);

	dev_info(dev, "GPIO fan initialized\n");

	वापस 0;
पूर्ण

अटल व्योम gpio_fan_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_fan_data *fan_data = platक्रमm_get_drvdata(pdev);

	अगर (fan_data->gpios)
		set_fan_speed(fan_data, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpio_fan_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	अगर (fan_data->gpios) अणु
		fan_data->resume_speed = fan_data->speed_index;
		set_fan_speed(fan_data, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_fan_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_fan_data *fan_data = dev_get_drvdata(dev);

	अगर (fan_data->gpios)
		set_fan_speed(fan_data, fan_data->resume_speed);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(gpio_fan_pm, gpio_fan_suspend, gpio_fan_resume);
#घोषणा GPIO_FAN_PM	(&gpio_fan_pm)
#अन्यथा
#घोषणा GPIO_FAN_PM	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver gpio_fan_driver = अणु
	.probe		= gpio_fan_probe,
	.shutकरोwn	= gpio_fan_shutकरोwn,
	.driver	= अणु
		.name	= "gpio-fan",
		.pm	= GPIO_FAN_PM,
		.of_match_table = of_match_ptr(of_gpio_fan_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_fan_driver);

MODULE_AUTHOR("Simon Guinot <sguinot@lacie.com>");
MODULE_DESCRIPTION("GPIO FAN driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-fan");
