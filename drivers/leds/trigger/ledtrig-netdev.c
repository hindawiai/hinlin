<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2017 Ben Whitten <ben.whitten@gmail.com>
// Copyright 2007 Oliver Jowett <oliver@खोलोcloud.com>
//
// LED Kernel Netdev Trigger
//
// Toggles the LED to reflect the link and traffic state of a named net device
//
// Derived from ledtrig-समयr.c which is:
//  Copyright 2005-2006 Openedhand Ltd.
//  Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>

#समावेश <linux/atomic.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश "../leds.h"

/*
 * Configurable sysfs attributes:
 *
 * device_name - network device name to monitor
 * पूर्णांकerval - duration of LED blink, in milliseconds
 * link -  LED's normal state reflects whether the link is up
 *         (has carrier) or not
 * tx -  LED blinks on transmitted data
 * rx -  LED blinks on receive data
 *
 */

काष्ठा led_netdev_data अणु
	spinlock_t lock;

	काष्ठा delayed_work work;
	काष्ठा notअगरier_block notअगरier;

	काष्ठा led_classdev *led_cdev;
	काष्ठा net_device *net_dev;

	अक्षर device_name[IFNAMSIZ];
	atomic_t पूर्णांकerval;
	अचिन्हित पूर्णांक last_activity;

	अचिन्हित दीर्घ mode;
#घोषणा NETDEV_LED_LINK	0
#घोषणा NETDEV_LED_TX	1
#घोषणा NETDEV_LED_RX	2
#घोषणा NETDEV_LED_MODE_LINKUP	3
पूर्ण;

क्रमागत netdev_led_attr अणु
	NETDEV_ATTR_LINK,
	NETDEV_ATTR_TX,
	NETDEV_ATTR_RX
पूर्ण;

अटल व्योम set_baseline_state(काष्ठा led_netdev_data *trigger_data)
अणु
	पूर्णांक current_brightness;
	काष्ठा led_classdev *led_cdev = trigger_data->led_cdev;

	current_brightness = led_cdev->brightness;
	अगर (current_brightness)
		led_cdev->blink_brightness = current_brightness;
	अगर (!led_cdev->blink_brightness)
		led_cdev->blink_brightness = led_cdev->max_brightness;

	अगर (!test_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode))
		led_set_brightness(led_cdev, LED_OFF);
	अन्यथा अणु
		अगर (test_bit(NETDEV_LED_LINK, &trigger_data->mode))
			led_set_brightness(led_cdev,
					   led_cdev->blink_brightness);
		अन्यथा
			led_set_brightness(led_cdev, LED_OFF);

		/* If we are looking क्रम RX/TX start periodically
		 * checking stats
		 */
		अगर (test_bit(NETDEV_LED_TX, &trigger_data->mode) ||
		    test_bit(NETDEV_LED_RX, &trigger_data->mode))
			schedule_delayed_work(&trigger_data->work, 0);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार device_name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);
	sमाप_प्रकार len;

	spin_lock_bh(&trigger_data->lock);
	len = प्र_लिखो(buf, "%s\n", trigger_data->device_name);
	spin_unlock_bh(&trigger_data->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार device_name_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार size)
अणु
	काष्ठा led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);

	अगर (size >= IFNAMSIZ)
		वापस -EINVAL;

	cancel_delayed_work_sync(&trigger_data->work);

	spin_lock_bh(&trigger_data->lock);

	अगर (trigger_data->net_dev) अणु
		dev_put(trigger_data->net_dev);
		trigger_data->net_dev = शून्य;
	पूर्ण

	स_नकल(trigger_data->device_name, buf, size);
	trigger_data->device_name[size] = 0;
	अगर (size > 0 && trigger_data->device_name[size - 1] == '\n')
		trigger_data->device_name[size - 1] = 0;

	अगर (trigger_data->device_name[0] != 0)
		trigger_data->net_dev =
		    dev_get_by_name(&init_net, trigger_data->device_name);

	clear_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode);
	अगर (trigger_data->net_dev != शून्य)
		अगर (netअगर_carrier_ok(trigger_data->net_dev))
			set_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode);

	trigger_data->last_activity = 0;

	set_baseline_state(trigger_data);
	spin_unlock_bh(&trigger_data->lock);

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(device_name);

अटल sमाप_प्रकार netdev_led_attr_show(काष्ठा device *dev, अक्षर *buf,
	क्रमागत netdev_led_attr attr)
अणु
	काष्ठा led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);
	पूर्णांक bit;

	चयन (attr) अणु
	हाल NETDEV_ATTR_LINK:
		bit = NETDEV_LED_LINK;
		अवरोध;
	हाल NETDEV_ATTR_TX:
		bit = NETDEV_LED_TX;
		अवरोध;
	हाल NETDEV_ATTR_RX:
		bit = NETDEV_LED_RX;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", test_bit(bit, &trigger_data->mode));
पूर्ण

अटल sमाप_प्रकार netdev_led_attr_store(काष्ठा device *dev, स्थिर अक्षर *buf,
	माप_प्रकार size, क्रमागत netdev_led_attr attr)
अणु
	काष्ठा led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;
	पूर्णांक bit;

	ret = kम_से_अदीर्घ(buf, 0, &state);
	अगर (ret)
		वापस ret;

	चयन (attr) अणु
	हाल NETDEV_ATTR_LINK:
		bit = NETDEV_LED_LINK;
		अवरोध;
	हाल NETDEV_ATTR_TX:
		bit = NETDEV_LED_TX;
		अवरोध;
	हाल NETDEV_ATTR_RX:
		bit = NETDEV_LED_RX;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cancel_delayed_work_sync(&trigger_data->work);

	अगर (state)
		set_bit(bit, &trigger_data->mode);
	अन्यथा
		clear_bit(bit, &trigger_data->mode);

	set_baseline_state(trigger_data);

	वापस size;
पूर्ण

अटल sमाप_प्रकार link_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस netdev_led_attr_show(dev, buf, NETDEV_ATTR_LINK);
पूर्ण

अटल sमाप_प्रकार link_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस netdev_led_attr_store(dev, buf, size, NETDEV_ATTR_LINK);
पूर्ण

अटल DEVICE_ATTR_RW(link);

अटल sमाप_प्रकार tx_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस netdev_led_attr_show(dev, buf, NETDEV_ATTR_TX);
पूर्ण

अटल sमाप_प्रकार tx_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस netdev_led_attr_store(dev, buf, size, NETDEV_ATTR_TX);
पूर्ण

अटल DEVICE_ATTR_RW(tx);

अटल sमाप_प्रकार rx_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस netdev_led_attr_show(dev, buf, NETDEV_ATTR_RX);
पूर्ण

अटल sमाप_प्रकार rx_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस netdev_led_attr_store(dev, buf, size, NETDEV_ATTR_RX);
पूर्ण

अटल DEVICE_ATTR_RW(rx);

अटल sमाप_प्रकार पूर्णांकerval_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n",
		       jअगरfies_to_msecs(atomic_पढ़ो(&trigger_data->पूर्णांकerval)));
पूर्ण

अटल sमाप_प्रकार पूर्णांकerval_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार size)
अणु
	काष्ठा led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	/* impose some basic bounds on the समयr पूर्णांकerval */
	अगर (value >= 5 && value <= 10000) अणु
		cancel_delayed_work_sync(&trigger_data->work);

		atomic_set(&trigger_data->पूर्णांकerval, msecs_to_jअगरfies(value));
		set_baseline_state(trigger_data);	/* resets समयr */
	पूर्ण

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(पूर्णांकerval);

अटल काष्ठा attribute *netdev_trig_attrs[] = अणु
	&dev_attr_device_name.attr,
	&dev_attr_link.attr,
	&dev_attr_rx.attr,
	&dev_attr_tx.attr,
	&dev_attr_पूर्णांकerval.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(netdev_trig);

अटल पूर्णांक netdev_trig_notअगरy(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ evt, व्योम *dv)
अणु
	काष्ठा net_device *dev =
		netdev_notअगरier_info_to_dev((काष्ठा netdev_notअगरier_info *)dv);
	काष्ठा led_netdev_data *trigger_data =
		container_of(nb, काष्ठा led_netdev_data, notअगरier);

	अगर (evt != NETDEV_UP && evt != NETDEV_DOWN && evt != NETDEV_CHANGE
	    && evt != NETDEV_REGISTER && evt != NETDEV_UNREGISTER
	    && evt != NETDEV_CHANGENAME)
		वापस NOTIFY_DONE;

	अगर (!(dev == trigger_data->net_dev ||
	      (evt == NETDEV_CHANGENAME && !म_भेद(dev->name, trigger_data->device_name)) ||
	      (evt == NETDEV_REGISTER && !म_भेद(dev->name, trigger_data->device_name))))
		वापस NOTIFY_DONE;

	cancel_delayed_work_sync(&trigger_data->work);

	spin_lock_bh(&trigger_data->lock);

	clear_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode);
	चयन (evt) अणु
	हाल NETDEV_CHANGENAME:
	हाल NETDEV_REGISTER:
		अगर (trigger_data->net_dev)
			dev_put(trigger_data->net_dev);
		dev_hold(dev);
		trigger_data->net_dev = dev;
		अवरोध;
	हाल NETDEV_UNREGISTER:
		dev_put(trigger_data->net_dev);
		trigger_data->net_dev = शून्य;
		अवरोध;
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE:
		अगर (netअगर_carrier_ok(dev))
			set_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode);
		अवरोध;
	पूर्ण

	set_baseline_state(trigger_data);

	spin_unlock_bh(&trigger_data->lock);

	वापस NOTIFY_DONE;
पूर्ण

/* here's the real work! */
अटल व्योम netdev_trig_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा led_netdev_data *trigger_data =
		container_of(work, काष्ठा led_netdev_data, work.work);
	काष्ठा rtnl_link_stats64 *dev_stats;
	अचिन्हित पूर्णांक new_activity;
	काष्ठा rtnl_link_stats64 temp;
	अचिन्हित दीर्घ पूर्णांकerval;
	पूर्णांक invert;

	/* If we करोnt have a device, insure we are off */
	अगर (!trigger_data->net_dev) अणु
		led_set_brightness(trigger_data->led_cdev, LED_OFF);
		वापस;
	पूर्ण

	/* If we are not looking क्रम RX/TX then वापस  */
	अगर (!test_bit(NETDEV_LED_TX, &trigger_data->mode) &&
	    !test_bit(NETDEV_LED_RX, &trigger_data->mode))
		वापस;

	dev_stats = dev_get_stats(trigger_data->net_dev, &temp);
	new_activity =
	    (test_bit(NETDEV_LED_TX, &trigger_data->mode) ?
		dev_stats->tx_packets : 0) +
	    (test_bit(NETDEV_LED_RX, &trigger_data->mode) ?
		dev_stats->rx_packets : 0);

	अगर (trigger_data->last_activity != new_activity) अणु
		led_stop_software_blink(trigger_data->led_cdev);

		invert = test_bit(NETDEV_LED_LINK, &trigger_data->mode);
		पूर्णांकerval = jअगरfies_to_msecs(
				atomic_पढ़ो(&trigger_data->पूर्णांकerval));
		/* base state is ON (link present) */
		led_blink_set_oneshot(trigger_data->led_cdev,
				      &पूर्णांकerval,
				      &पूर्णांकerval,
				      invert);
		trigger_data->last_activity = new_activity;
	पूर्ण

	schedule_delayed_work(&trigger_data->work,
			(atomic_पढ़ो(&trigger_data->पूर्णांकerval)*2));
पूर्ण

अटल पूर्णांक netdev_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा led_netdev_data *trigger_data;
	पूर्णांक rc;

	trigger_data = kzalloc(माप(काष्ठा led_netdev_data), GFP_KERNEL);
	अगर (!trigger_data)
		वापस -ENOMEM;

	spin_lock_init(&trigger_data->lock);

	trigger_data->notअगरier.notअगरier_call = netdev_trig_notअगरy;
	trigger_data->notअगरier.priority = 10;

	INIT_DELAYED_WORK(&trigger_data->work, netdev_trig_work);

	trigger_data->led_cdev = led_cdev;
	trigger_data->net_dev = शून्य;
	trigger_data->device_name[0] = 0;

	trigger_data->mode = 0;
	atomic_set(&trigger_data->पूर्णांकerval, msecs_to_jअगरfies(50));
	trigger_data->last_activity = 0;

	led_set_trigger_data(led_cdev, trigger_data);

	rc = रेजिस्टर_netdevice_notअगरier(&trigger_data->notअगरier);
	अगर (rc)
		kमुक्त(trigger_data);

	वापस rc;
पूर्ण

अटल व्योम netdev_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा led_netdev_data *trigger_data = led_get_trigger_data(led_cdev);

	unरेजिस्टर_netdevice_notअगरier(&trigger_data->notअगरier);

	cancel_delayed_work_sync(&trigger_data->work);

	अगर (trigger_data->net_dev)
		dev_put(trigger_data->net_dev);

	kमुक्त(trigger_data);
पूर्ण

अटल काष्ठा led_trigger netdev_led_trigger = अणु
	.name = "netdev",
	.activate = netdev_trig_activate,
	.deactivate = netdev_trig_deactivate,
	.groups = netdev_trig_groups,
पूर्ण;

अटल पूर्णांक __init netdev_trig_init(व्योम)
अणु
	वापस led_trigger_रेजिस्टर(&netdev_led_trigger);
पूर्ण

अटल व्योम __निकास netdev_trig_निकास(व्योम)
अणु
	led_trigger_unरेजिस्टर(&netdev_led_trigger);
पूर्ण

module_init(netdev_trig_init);
module_निकास(netdev_trig_निकास);

MODULE_AUTHOR("Ben Whitten <ben.whitten@gmail.com>");
MODULE_AUTHOR("Oliver Jowett <oliver@opencloud.com>");
MODULE_DESCRIPTION("Netdev LED trigger");
MODULE_LICENSE("GPL v2");
