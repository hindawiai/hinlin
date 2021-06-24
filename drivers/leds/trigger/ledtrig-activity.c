<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Activity LED trigger
 *
 * Copyright (C) 2017 Willy Tarreau <w@1wt.eu>
 * Partially based on Atsushi Nemoto's ledtrig-heartbeat.c.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश "../leds.h"

अटल पूर्णांक panic_detected;

काष्ठा activity_data अणु
	काष्ठा समयr_list समयr;
	काष्ठा led_classdev *led_cdev;
	u64 last_used;
	u64 last_boot;
	पूर्णांक समय_left;
	पूर्णांक state;
	पूर्णांक invert;
पूर्ण;

अटल व्योम led_activity_function(काष्ठा समयr_list *t)
अणु
	काष्ठा activity_data *activity_data = from_समयr(activity_data, t,
							 समयr);
	काष्ठा led_classdev *led_cdev = activity_data->led_cdev;
	अचिन्हित पूर्णांक target;
	अचिन्हित पूर्णांक usage;
	पूर्णांक delay;
	u64 curr_used;
	u64 curr_boot;
	s32 dअगरf_used;
	s32 dअगरf_boot;
	पूर्णांक cpus;
	पूर्णांक i;

	अगर (test_and_clear_bit(LED_BLINK_BRIGHTNESS_CHANGE, &led_cdev->work_flags))
		led_cdev->blink_brightness = led_cdev->new_blink_brightness;

	अगर (unlikely(panic_detected)) अणु
		/* full brightness in हाल of panic */
		led_set_brightness_nosleep(led_cdev, led_cdev->blink_brightness);
		वापस;
	पूर्ण

	cpus = 0;
	curr_used = 0;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा kernel_cpustat kcpustat;

		kcpustat_cpu_fetch(&kcpustat, i);

		curr_used += kcpustat.cpustat[CPUTIME_USER]
			  +  kcpustat.cpustat[CPUTIME_NICE]
			  +  kcpustat.cpustat[CPUTIME_SYSTEM]
			  +  kcpustat.cpustat[CPUTIME_SOFTIRQ]
			  +  kcpustat.cpustat[CPUTIME_IRQ];
		cpus++;
	पूर्ण

	/* We come here every 100ms in the worst हाल, so that's 100M ns of
	 * cumulated समय. By भागiding by 2^16, we get the समय resolution
	 * करोwn to 16us, ensuring we won't overflow 32-bit computations below
	 * even up to 3k CPUs, जबतक keeping भागides cheap on smaller प्रणालीs.
	 */
	curr_boot = kसमय_get_bootसमय_ns() * cpus;
	dअगरf_boot = (curr_boot - activity_data->last_boot) >> 16;
	dअगरf_used = (curr_used - activity_data->last_used) >> 16;
	activity_data->last_boot = curr_boot;
	activity_data->last_used = curr_used;

	अगर (dअगरf_boot <= 0 || dअगरf_used < 0)
		usage = 0;
	अन्यथा अगर (dअगरf_used >= dअगरf_boot)
		usage = 100;
	अन्यथा
		usage = 100 * dअगरf_used / dअगरf_boot;

	/*
	 * Now we know the total boot_समय multiplied by the number of CPUs, and
	 * the total idle+रुको समय क्रम all CPUs. We'll compare how they evolved
	 * since last call. The % of overall CPU usage is :
	 *
	 *      1 - delta_idle / delta_boot
	 *
	 * What we want is that when the CPU usage is zero, the LED must blink
	 * slowly with very faपूर्णांक flashes that are detectable but not disturbing
	 * (typically 10ms every second, or 10ms ON, 990ms OFF). Then we want
	 * blinking frequency to increase up to the poपूर्णांक where the load is
	 * enough to saturate one core in multi-core प्रणालीs or 50% in single
	 * core प्रणालीs. At this poपूर्णांक it should reach 10 Hz with a 10/90 duty
	 * cycle (10ms ON, 90ms OFF). After this poपूर्णांक, the blinking frequency
	 * reमुख्यs stable (10 Hz) and only the duty cycle increases to report
	 * the activity, up to the poपूर्णांक where we have 90ms ON, 10ms OFF when
	 * all cores are saturated. It's important that the LED never stays in
	 * a steady state so that it's easy to distinguish an idle or saturated
	 * machine from a hung one.
	 *
	 * This gives us :
	 *   - a target CPU usage of min(50%, 100%/#CPU) क्रम a 10% duty cycle
	 *     (10ms ON, 90ms OFF)
	 *   - below target :
	 *      ON_ms  = 10
	 *      OFF_ms = 90 + (1 - usage/target) * 900
	 *   - above target :
	 *      ON_ms  = 10 + (usage-target)/(100%-target) * 80
	 *      OFF_ms = 90 - (usage-target)/(100%-target) * 80
	 *
	 * In order to keep a good responsiveness, we cap the sleep समय to
	 * 100 ms and keep track of the sleep समय left. This allows us to
	 * quickly change it अगर needed.
	 */

	activity_data->समय_left -= 100;
	अगर (activity_data->समय_left <= 0) अणु
		activity_data->समय_left = 0;
		activity_data->state = !activity_data->state;
		led_set_brightness_nosleep(led_cdev,
			(activity_data->state ^ activity_data->invert) ?
			led_cdev->blink_brightness : LED_OFF);
	पूर्ण

	target = (cpus > 1) ? (100 / cpus) : 50;

	अगर (usage < target)
		delay = activity_data->state ?
			10 :                        /* ON  */
			990 - 900 * usage / target; /* OFF */
	अन्यथा
		delay = activity_data->state ?
			10 + 80 * (usage - target) / (100 - target) : /* ON  */
			90 - 80 * (usage - target) / (100 - target);  /* OFF */


	अगर (!activity_data->समय_left || delay <= activity_data->समय_left)
		activity_data->समय_left = delay;

	delay = min_t(पूर्णांक, activity_data->समय_left, 100);
	mod_समयr(&activity_data->समयr, jअगरfies + msecs_to_jअगरfies(delay));
पूर्ण

अटल sमाप_प्रकार led_invert_show(काष्ठा device *dev,
                               काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा activity_data *activity_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", activity_data->invert);
पूर्ण

अटल sमाप_प्रकार led_invert_store(काष्ठा device *dev,
                                काष्ठा device_attribute *attr,
                                स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा activity_data *activity_data = led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &state);
	अगर (ret)
		वापस ret;

	activity_data->invert = !!state;

	वापस size;
पूर्ण

अटल DEVICE_ATTR(invert, 0644, led_invert_show, led_invert_store);

अटल काष्ठा attribute *activity_led_attrs[] = अणु
	&dev_attr_invert.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(activity_led);

अटल पूर्णांक activity_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा activity_data *activity_data;

	activity_data = kzalloc(माप(*activity_data), GFP_KERNEL);
	अगर (!activity_data)
		वापस -ENOMEM;

	led_set_trigger_data(led_cdev, activity_data);

	activity_data->led_cdev = led_cdev;
	समयr_setup(&activity_data->समयr, led_activity_function, 0);
	अगर (!led_cdev->blink_brightness)
		led_cdev->blink_brightness = led_cdev->max_brightness;
	led_activity_function(&activity_data->समयr);
	set_bit(LED_BLINK_SW, &led_cdev->work_flags);

	वापस 0;
पूर्ण

अटल व्योम activity_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा activity_data *activity_data = led_get_trigger_data(led_cdev);

	del_समयr_sync(&activity_data->समयr);
	kमुक्त(activity_data);
	clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
पूर्ण

अटल काष्ठा led_trigger activity_led_trigger = अणु
	.name       = "activity",
	.activate   = activity_activate,
	.deactivate = activity_deactivate,
	.groups     = activity_led_groups,
पूर्ण;

अटल पूर्णांक activity_reboot_notअगरier(काष्ठा notअगरier_block *nb,
                                    अचिन्हित दीर्घ code, व्योम *unused)
अणु
	led_trigger_unरेजिस्टर(&activity_led_trigger);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक activity_panic_notअगरier(काष्ठा notअगरier_block *nb,
                                   अचिन्हित दीर्घ code, व्योम *unused)
अणु
	panic_detected = 1;
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block activity_reboot_nb = अणु
	.notअगरier_call = activity_reboot_notअगरier,
पूर्ण;

अटल काष्ठा notअगरier_block activity_panic_nb = अणु
	.notअगरier_call = activity_panic_notअगरier,
पूर्ण;

अटल पूर्णांक __init activity_init(व्योम)
अणु
	पूर्णांक rc = led_trigger_रेजिस्टर(&activity_led_trigger);

	अगर (!rc) अणु
		atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					       &activity_panic_nb);
		रेजिस्टर_reboot_notअगरier(&activity_reboot_nb);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम __निकास activity_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&activity_reboot_nb);
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &activity_panic_nb);
	led_trigger_unरेजिस्टर(&activity_led_trigger);
पूर्ण

module_init(activity_init);
module_निकास(activity_निकास);

MODULE_AUTHOR("Willy Tarreau <w@1wt.eu>");
MODULE_DESCRIPTION("Activity LED trigger");
MODULE_LICENSE("GPL v2");
