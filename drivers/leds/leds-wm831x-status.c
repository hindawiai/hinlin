<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED driver क्रम WM831x status LEDs
 *
 * Copyright(C) 2009 Wolfson Microelectronics PLC.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/status.h>
#समावेश <linux/module.h>


काष्ठा wm831x_status अणु
	काष्ठा led_classdev cdev;
	काष्ठा wm831x *wm831x;
	काष्ठा mutex mutex;

	spinlock_t value_lock;
	पूर्णांक reg;     /* Control रेजिस्टर */
	पूर्णांक reg_val; /* Control रेजिस्टर value */

	पूर्णांक blink;
	पूर्णांक blink_समय;
	पूर्णांक blink_cyc;
	पूर्णांक src;
	क्रमागत led_brightness brightness;
पूर्ण;

#घोषणा to_wm831x_status(led_cdev) \
	container_of(led_cdev, काष्ठा wm831x_status, cdev)

अटल व्योम wm831x_status_set(काष्ठा wm831x_status *led)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&led->mutex);

	led->reg_val &= ~(WM831X_LED_SRC_MASK | WM831X_LED_MODE_MASK |
			  WM831X_LED_DUTY_CYC_MASK | WM831X_LED_DUR_MASK);

	spin_lock_irqsave(&led->value_lock, flags);

	led->reg_val |= led->src << WM831X_LED_SRC_SHIFT;
	अगर (led->blink) अणु
		led->reg_val |= 2 << WM831X_LED_MODE_SHIFT;
		led->reg_val |= led->blink_समय << WM831X_LED_DUR_SHIFT;
		led->reg_val |= led->blink_cyc;
	पूर्ण अन्यथा अणु
		अगर (led->brightness != LED_OFF)
			led->reg_val |= 1 << WM831X_LED_MODE_SHIFT;
	पूर्ण

	spin_unlock_irqrestore(&led->value_lock, flags);

	wm831x_reg_ग_लिखो(led->wm831x, led->reg, led->reg_val);

	mutex_unlock(&led->mutex);
पूर्ण

अटल पूर्णांक wm831x_status_brightness_set(काष्ठा led_classdev *led_cdev,
					 क्रमागत led_brightness value)
अणु
	काष्ठा wm831x_status *led = to_wm831x_status(led_cdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&led->value_lock, flags);
	led->brightness = value;
	अगर (value == LED_OFF)
		led->blink = 0;
	spin_unlock_irqrestore(&led->value_lock, flags);
	wm831x_status_set(led);

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_status_blink_set(काष्ठा led_classdev *led_cdev,
				   अचिन्हित दीर्घ *delay_on,
				   अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा wm831x_status *led = to_wm831x_status(led_cdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* Pick some शेषs अगर we've not been given बार */
	अगर (*delay_on == 0 && *delay_off == 0) अणु
		*delay_on = 250;
		*delay_off = 250;
	पूर्ण

	spin_lock_irqsave(&led->value_lock, flags);

	/* We only have a limited selection of settings, see अगर we can
	 * support the configuration we're being given */
	चयन (*delay_on) अणु
	हाल 1000:
		led->blink_समय = 0;
		अवरोध;
	हाल 250:
		led->blink_समय = 1;
		अवरोध;
	हाल 125:
		led->blink_समय = 2;
		अवरोध;
	हाल 62:
	हाल 63:
		/* Actually 62.5ms */
		led->blink_समय = 3;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret == 0) अणु
		चयन (*delay_off / *delay_on) अणु
		हाल 1:
			led->blink_cyc = 0;
			अवरोध;
		हाल 3:
			led->blink_cyc = 1;
			अवरोध;
		हाल 4:
			led->blink_cyc = 2;
			अवरोध;
		हाल 8:
			led->blink_cyc = 3;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == 0)
		led->blink = 1;
	अन्यथा
		led->blink = 0;

	spin_unlock_irqrestore(&led->value_lock, flags);
	wm831x_status_set(led);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर led_src_texts[] = अणु
	"otp",
	"power",
	"charger",
	"soft",
पूर्ण;

अटल sमाप_प्रकार src_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा wm831x_status *led = to_wm831x_status(led_cdev);
	पूर्णांक i;
	sमाप_प्रकार ret = 0;

	mutex_lock(&led->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(led_src_texts); i++)
		अगर (i == led->src)
			ret += प्र_लिखो(&buf[ret], "[%s] ", led_src_texts[i]);
		अन्यथा
			ret += प्र_लिखो(&buf[ret], "%s ", led_src_texts[i]);

	mutex_unlock(&led->mutex);

	ret += प्र_लिखो(&buf[ret], "\n");

	वापस ret;
पूर्ण

अटल sमाप_प्रकार src_store(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा wm831x_status *led = to_wm831x_status(led_cdev);
	पूर्णांक i;

	i = sysfs_match_string(led_src_texts, buf);
	अगर (i >= 0) अणु
		mutex_lock(&led->mutex);
		led->src = i;
		mutex_unlock(&led->mutex);
		wm831x_status_set(led);
	पूर्ण

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(src);

अटल काष्ठा attribute *wm831x_status_attrs[] = अणु
	&dev_attr_src.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(wm831x_status);

अटल पूर्णांक wm831x_status_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *chip_pdata;
	काष्ठा wm831x_status_pdata pdata;
	काष्ठा wm831x_status *drvdata;
	काष्ठा resource *res;
	पूर्णांक id = pdev->id % ARRAY_SIZE(chip_pdata->status);
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No register resource\n");
		वापस -EINVAL;
	पूर्ण

	drvdata = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_status),
			       GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->wm831x = wm831x;
	drvdata->reg = res->start;

	अगर (dev_get_platdata(wm831x->dev))
		chip_pdata = dev_get_platdata(wm831x->dev);
	अन्यथा
		chip_pdata = शून्य;

	स_रखो(&pdata, 0, माप(pdata));
	अगर (chip_pdata && chip_pdata->status[id])
		स_नकल(&pdata, chip_pdata->status[id], माप(pdata));
	अन्यथा
		pdata.name = dev_name(&pdev->dev);

	mutex_init(&drvdata->mutex);
	spin_lock_init(&drvdata->value_lock);

	/* We cache the configuration रेजिस्टर and पढ़ो startup values
	 * from it. */
	drvdata->reg_val = wm831x_reg_पढ़ो(wm831x, drvdata->reg);

	अगर (drvdata->reg_val & WM831X_LED_MODE_MASK)
		drvdata->brightness = LED_FULL;
	अन्यथा
		drvdata->brightness = LED_OFF;

	/* Set a शेष source अगर configured, otherwise leave the
	 * current hardware setting.
	 */
	अगर (pdata.शेष_src == WM831X_STATUS_PRESERVE) अणु
		drvdata->src = drvdata->reg_val;
		drvdata->src &= WM831X_LED_SRC_MASK;
		drvdata->src >>= WM831X_LED_SRC_SHIFT;
	पूर्ण अन्यथा अणु
		drvdata->src = pdata.शेष_src - 1;
	पूर्ण

	drvdata->cdev.name = pdata.name;
	drvdata->cdev.शेष_trigger = pdata.शेष_trigger;
	drvdata->cdev.brightness_set_blocking = wm831x_status_brightness_set;
	drvdata->cdev.blink_set = wm831x_status_blink_set;
	drvdata->cdev.groups = wm831x_status_groups;

	ret = led_classdev_रेजिस्टर(wm831x->dev, &drvdata->cdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register LED: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_status_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x_status *drvdata = platक्रमm_get_drvdata(pdev);

	led_classdev_unरेजिस्टर(&drvdata->cdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_status_driver = अणु
	.driver = अणु
		   .name = "wm831x-status",
		   पूर्ण,
	.probe = wm831x_status_probe,
	.हटाओ = wm831x_status_हटाओ,
पूर्ण;

module_platक्रमm_driver(wm831x_status_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM831x status LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-status");
