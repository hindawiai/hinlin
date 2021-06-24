<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Heartbeat Trigger
 *
 * Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * Based on Riअक्षरd Purdie's ledtrig-timer.c and some arch's
 * CONFIG_HEARTBEAT code.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/leds.h>
#समावेश <linux/reboot.h>
#समावेश "../leds.h"

अटल पूर्णांक panic_heartbeats;

काष्ठा heartbeat_trig_data अणु
	काष्ठा led_classdev *led_cdev;
	अचिन्हित पूर्णांक phase;
	अचिन्हित पूर्णांक period;
	काष्ठा समयr_list समयr;
	अचिन्हित पूर्णांक invert;
पूर्ण;

अटल व्योम led_heartbeat_function(काष्ठा समयr_list *t)
अणु
	काष्ठा heartbeat_trig_data *heartbeat_data =
		from_समयr(heartbeat_data, t, समयr);
	काष्ठा led_classdev *led_cdev;
	अचिन्हित दीर्घ brightness = LED_OFF;
	अचिन्हित दीर्घ delay = 0;

	led_cdev = heartbeat_data->led_cdev;

	अगर (unlikely(panic_heartbeats)) अणु
		led_set_brightness_nosleep(led_cdev, LED_OFF);
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(LED_BLINK_BRIGHTNESS_CHANGE, &led_cdev->work_flags))
		led_cdev->blink_brightness = led_cdev->new_blink_brightness;

	/* acts like an actual heart beat -- ie thump-thump-छोड़ो... */
	चयन (heartbeat_data->phase) अणु
	हाल 0:
		/*
		 * The hyperbolic function below modअगरies the
		 * heartbeat period length in dependency of the
		 * current (1min) load. It goes through the poपूर्णांकs
		 * f(0)=1260, f(1)=860, f(5)=510, f(inf)->300.
		 */
		heartbeat_data->period = 300 +
			(6720 << FSHIFT) / (5 * avenrun[0] + (7 << FSHIFT));
		heartbeat_data->period =
			msecs_to_jअगरfies(heartbeat_data->period);
		delay = msecs_to_jअगरfies(70);
		heartbeat_data->phase++;
		अगर (!heartbeat_data->invert)
			brightness = led_cdev->blink_brightness;
		अवरोध;
	हाल 1:
		delay = heartbeat_data->period / 4 - msecs_to_jअगरfies(70);
		heartbeat_data->phase++;
		अगर (heartbeat_data->invert)
			brightness = led_cdev->blink_brightness;
		अवरोध;
	हाल 2:
		delay = msecs_to_jअगरfies(70);
		heartbeat_data->phase++;
		अगर (!heartbeat_data->invert)
			brightness = led_cdev->blink_brightness;
		अवरोध;
	शेष:
		delay = heartbeat_data->period - heartbeat_data->period / 4 -
			msecs_to_jअगरfies(70);
		heartbeat_data->phase = 0;
		अगर (heartbeat_data->invert)
			brightness = led_cdev->blink_brightness;
		अवरोध;
	पूर्ण

	led_set_brightness_nosleep(led_cdev, brightness);
	mod_समयr(&heartbeat_data->समयr, jअगरfies + delay);
पूर्ण

अटल sमाप_प्रकार led_invert_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा heartbeat_trig_data *heartbeat_data =
		led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", heartbeat_data->invert);
पूर्ण

अटल sमाप_प्रकार led_invert_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा heartbeat_trig_data *heartbeat_data =
		led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &state);
	अगर (ret)
		वापस ret;

	heartbeat_data->invert = !!state;

	वापस size;
पूर्ण

अटल DEVICE_ATTR(invert, 0644, led_invert_show, led_invert_store);

अटल काष्ठा attribute *heartbeat_trig_attrs[] = अणु
	&dev_attr_invert.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(heartbeat_trig);

अटल पूर्णांक heartbeat_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा heartbeat_trig_data *heartbeat_data;

	heartbeat_data = kzalloc(माप(*heartbeat_data), GFP_KERNEL);
	अगर (!heartbeat_data)
		वापस -ENOMEM;

	led_set_trigger_data(led_cdev, heartbeat_data);
	heartbeat_data->led_cdev = led_cdev;

	समयr_setup(&heartbeat_data->समयr, led_heartbeat_function, 0);
	heartbeat_data->phase = 0;
	अगर (!led_cdev->blink_brightness)
		led_cdev->blink_brightness = led_cdev->max_brightness;
	led_heartbeat_function(&heartbeat_data->समयr);
	set_bit(LED_BLINK_SW, &led_cdev->work_flags);

	वापस 0;
पूर्ण

अटल व्योम heartbeat_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा heartbeat_trig_data *heartbeat_data =
		led_get_trigger_data(led_cdev);

	del_समयr_sync(&heartbeat_data->समयr);
	kमुक्त(heartbeat_data);
	clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
पूर्ण

अटल काष्ठा led_trigger heartbeat_led_trigger = अणु
	.name     = "heartbeat",
	.activate = heartbeat_trig_activate,
	.deactivate = heartbeat_trig_deactivate,
	.groups = heartbeat_trig_groups,
पूर्ण;

अटल पूर्णांक heartbeat_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ code, व्योम *unused)
अणु
	led_trigger_unरेजिस्टर(&heartbeat_led_trigger);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक heartbeat_panic_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ code, व्योम *unused)
अणु
	panic_heartbeats = 1;
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block heartbeat_reboot_nb = अणु
	.notअगरier_call = heartbeat_reboot_notअगरier,
पूर्ण;

अटल काष्ठा notअगरier_block heartbeat_panic_nb = अणु
	.notअगरier_call = heartbeat_panic_notअगरier,
पूर्ण;

अटल पूर्णांक __init heartbeat_trig_init(व्योम)
अणु
	पूर्णांक rc = led_trigger_रेजिस्टर(&heartbeat_led_trigger);

	अगर (!rc) अणु
		atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					       &heartbeat_panic_nb);
		रेजिस्टर_reboot_notअगरier(&heartbeat_reboot_nb);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम __निकास heartbeat_trig_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&heartbeat_reboot_nb);
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &heartbeat_panic_nb);
	led_trigger_unरेजिस्टर(&heartbeat_led_trigger);
पूर्ण

module_init(heartbeat_trig_init);
module_निकास(heartbeat_trig_निकास);

MODULE_AUTHOR("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODULE_DESCRIPTION("Heartbeat LED trigger");
MODULE_LICENSE("GPL v2");
