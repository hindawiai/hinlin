<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/delay.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <uapi/linux/serial.h>

काष्ठा ledtrig_tty_data अणु
	काष्ठा led_classdev *led_cdev;
	काष्ठा delayed_work dwork;
	काष्ठा mutex mutex;
	स्थिर अक्षर *ttyname;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक rx, tx;
पूर्ण;

अटल व्योम ledtrig_tty_restart(काष्ठा ledtrig_tty_data *trigger_data)
अणु
	schedule_delayed_work(&trigger_data->dwork, 0);
पूर्ण

अटल sमाप_प्रकार ttyname_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ledtrig_tty_data *trigger_data = led_trigger_get_drvdata(dev);
	sमाप_प्रकार len = 0;

	mutex_lock(&trigger_data->mutex);

	अगर (trigger_data->ttyname)
		len = प्र_लिखो(buf, "%s\n", trigger_data->ttyname);

	mutex_unlock(&trigger_data->mutex);

	वापस len;
पूर्ण

अटल sमाप_प्रकार ttyname_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार size)
अणु
	काष्ठा ledtrig_tty_data *trigger_data = led_trigger_get_drvdata(dev);
	अक्षर *ttyname;
	sमाप_प्रकार ret = size;
	bool running;

	अगर (size > 0 && buf[size - 1] == '\n')
		size -= 1;

	अगर (size) अणु
		ttyname = kmemdup_nul(buf, size, GFP_KERNEL);
		अगर (!ttyname)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		ttyname = शून्य;
	पूर्ण

	mutex_lock(&trigger_data->mutex);

	running = trigger_data->ttyname != शून्य;

	kमुक्त(trigger_data->ttyname);
	tty_kref_put(trigger_data->tty);
	trigger_data->tty = शून्य;

	trigger_data->ttyname = ttyname;

	mutex_unlock(&trigger_data->mutex);

	अगर (ttyname && !running)
		ledtrig_tty_restart(trigger_data);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(ttyname);

अटल व्योम ledtrig_tty_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ledtrig_tty_data *trigger_data =
		container_of(work, काष्ठा ledtrig_tty_data, dwork.work);
	काष्ठा serial_icounter_काष्ठा icount;
	पूर्णांक ret;

	mutex_lock(&trigger_data->mutex);

	अगर (!trigger_data->ttyname) अणु
		/* निकास without rescheduling */
		mutex_unlock(&trigger_data->mutex);
		वापस;
	पूर्ण

	/* try to get the tty corresponding to $ttyname */
	अगर (!trigger_data->tty) अणु
		dev_t devno;
		काष्ठा tty_काष्ठा *tty;
		पूर्णांक ret;

		ret = tty_dev_name_to_number(trigger_data->ttyname, &devno);
		अगर (ret < 0)
			/*
			 * A device with this name might appear later, so keep
			 * retrying.
			 */
			जाओ out;

		tty = tty_kखोलो_shared(devno);
		अगर (IS_ERR(tty) || !tty)
			/* What to करो? retry or पात */
			जाओ out;

		trigger_data->tty = tty;
	पूर्ण

	ret = tty_get_icount(trigger_data->tty, &icount);
	अगर (ret) अणु
		dev_info(trigger_data->tty->dev, "Failed to get icount, stopped polling\n");
		mutex_unlock(&trigger_data->mutex);
		वापस;
	पूर्ण

	अगर (icount.rx != trigger_data->rx ||
	    icount.tx != trigger_data->tx) अणु
		led_set_brightness_sync(trigger_data->led_cdev, LED_ON);

		trigger_data->rx = icount.rx;
		trigger_data->tx = icount.tx;
	पूर्ण अन्यथा अणु
		led_set_brightness_sync(trigger_data->led_cdev, LED_OFF);
	पूर्ण

out:
	mutex_unlock(&trigger_data->mutex);
	schedule_delayed_work(&trigger_data->dwork, msecs_to_jअगरfies(100));
पूर्ण

अटल काष्ठा attribute *ledtrig_tty_attrs[] = अणु
	&dev_attr_ttyname.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(ledtrig_tty);

अटल पूर्णांक ledtrig_tty_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ledtrig_tty_data *trigger_data;

	trigger_data = kzalloc(माप(*trigger_data), GFP_KERNEL);
	अगर (!trigger_data)
		वापस -ENOMEM;

	led_set_trigger_data(led_cdev, trigger_data);

	INIT_DELAYED_WORK(&trigger_data->dwork, ledtrig_tty_work);
	trigger_data->led_cdev = led_cdev;
	mutex_init(&trigger_data->mutex);

	वापस 0;
पूर्ण

अटल व्योम ledtrig_tty_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ledtrig_tty_data *trigger_data = led_get_trigger_data(led_cdev);

	cancel_delayed_work_sync(&trigger_data->dwork);

	kमुक्त(trigger_data);
पूर्ण

अटल काष्ठा led_trigger ledtrig_tty = अणु
	.name = "tty",
	.activate = ledtrig_tty_activate,
	.deactivate = ledtrig_tty_deactivate,
	.groups = ledtrig_tty_groups,
पूर्ण;
module_led_trigger(ledtrig_tty);

MODULE_AUTHOR("Uwe Kleine-Kथघnig <u.kleine-koenig@pengutronix.de>");
MODULE_DESCRIPTION("UART LED trigger");
MODULE_LICENSE("GPL v2");
