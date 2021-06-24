<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// LED Kernel Transient Trigger
//
// Transient trigger allows one shot समयr activation. Please refer to
// Documentation/leds/ledtrig-transient.rst क्रम details
// Copyright (C) 2012 Shuah Khan <shuahkhan@gmail.com>
//
// Based on Riअक्षरd Purdie's ledtrig-timer.c and Atsushi Nemoto's
// ledtrig-heartbeat.c
// Design and use-हाल input from Jonas Bonn <jonas@southpole.se> and
// Neil Brown <neilb@suse.de>

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/leds.h>
#समावेश "../leds.h"

काष्ठा transient_trig_data अणु
	पूर्णांक activate;
	पूर्णांक state;
	पूर्णांक restore_state;
	अचिन्हित दीर्घ duration;
	काष्ठा समयr_list समयr;
	काष्ठा led_classdev *led_cdev;
पूर्ण;

अटल व्योम transient_समयr_function(काष्ठा समयr_list *t)
अणु
	काष्ठा transient_trig_data *transient_data =
		from_समयr(transient_data, t, समयr);
	काष्ठा led_classdev *led_cdev = transient_data->led_cdev;

	transient_data->activate = 0;
	led_set_brightness_nosleep(led_cdev, transient_data->restore_state);
पूर्ण

अटल sमाप_प्रकार transient_activate_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा transient_trig_data *transient_data =
		led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", transient_data->activate);
पूर्ण

अटल sमाप_प्रकार transient_activate_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);
	काष्ठा transient_trig_data *transient_data =
		led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		वापस ret;

	अगर (state != 1 && state != 0)
		वापस -EINVAL;

	/* cancel the running समयr */
	अगर (state == 0 && transient_data->activate == 1) अणु
		del_समयr(&transient_data->समयr);
		transient_data->activate = state;
		led_set_brightness_nosleep(led_cdev,
					transient_data->restore_state);
		वापस size;
	पूर्ण

	/* start समयr अगर there is no active समयr */
	अगर (state == 1 && transient_data->activate == 0 &&
	    transient_data->duration != 0) अणु
		transient_data->activate = state;
		led_set_brightness_nosleep(led_cdev, transient_data->state);
		transient_data->restore_state =
		    (transient_data->state == LED_FULL) ? LED_OFF : LED_FULL;
		mod_समयr(&transient_data->समयr,
			  jअगरfies + msecs_to_jअगरfies(transient_data->duration));
	पूर्ण

	/* state == 0 && transient_data->activate == 0
		समयr is not active - just वापस */
	/* state == 1 && transient_data->activate == 1
		समयr is alपढ़ोy active - just वापस */

	वापस size;
पूर्ण

अटल sमाप_प्रकार transient_duration_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा transient_trig_data *transient_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lu\n", transient_data->duration);
पूर्ण

अटल sमाप_प्रकार transient_duration_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा transient_trig_data *transient_data =
		led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		वापस ret;

	transient_data->duration = state;
	वापस size;
पूर्ण

अटल sमाप_प्रकार transient_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा transient_trig_data *transient_data =
		led_trigger_get_drvdata(dev);
	पूर्णांक state;

	state = (transient_data->state == LED_FULL) ? 1 : 0;
	वापस प्र_लिखो(buf, "%d\n", state);
पूर्ण

अटल sमाप_प्रकार transient_state_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा transient_trig_data *transient_data =
		led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		वापस ret;

	अगर (state != 1 && state != 0)
		वापस -EINVAL;

	transient_data->state = (state == 1) ? LED_FULL : LED_OFF;
	वापस size;
पूर्ण

अटल DEVICE_ATTR(activate, 0644, transient_activate_show,
		   transient_activate_store);
अटल DEVICE_ATTR(duration, 0644, transient_duration_show,
		   transient_duration_store);
अटल DEVICE_ATTR(state, 0644, transient_state_show, transient_state_store);

अटल काष्ठा attribute *transient_trig_attrs[] = अणु
	&dev_attr_activate.attr,
	&dev_attr_duration.attr,
	&dev_attr_state.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(transient_trig);

अटल पूर्णांक transient_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा transient_trig_data *tdata;

	tdata = kzalloc(माप(काष्ठा transient_trig_data), GFP_KERNEL);
	अगर (!tdata)
		वापस -ENOMEM;

	led_set_trigger_data(led_cdev, tdata);
	tdata->led_cdev = led_cdev;

	समयr_setup(&tdata->समयr, transient_समयr_function, 0);

	वापस 0;
पूर्ण

अटल व्योम transient_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा transient_trig_data *transient_data = led_get_trigger_data(led_cdev);

	del_समयr_sync(&transient_data->समयr);
	led_set_brightness_nosleep(led_cdev, transient_data->restore_state);
	kमुक्त(transient_data);
पूर्ण

अटल काष्ठा led_trigger transient_trigger = अणु
	.name     = "transient",
	.activate = transient_trig_activate,
	.deactivate = transient_trig_deactivate,
	.groups = transient_trig_groups,
पूर्ण;
module_led_trigger(transient_trigger);

MODULE_AUTHOR("Shuah Khan <shuahkhan@gmail.com>");
MODULE_DESCRIPTION("Transient LED trigger");
MODULE_LICENSE("GPL v2");
