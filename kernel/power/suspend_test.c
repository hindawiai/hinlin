<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/घातer/suspend_test.c - Suspend to RAM and standby test facility.
 *
 * Copyright (c) 2009 Pavel Machek <pavel@ucw.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/rtc.h>

#समावेश "power.h"

/*
 * We test the प्रणाली suspend code by setting an RTC wakealarm a लघु
 * समय in the future, then suspending.  Suspending the devices won't
 * normally take दीर्घ ... some प्रणालीs only need a few milliseconds.
 *
 * The समय it takes is प्रणाली-specअगरic though, so when we test this
 * during प्रणाली bootup we allow a LOT of समय.
 */
#घोषणा TEST_SUSPEND_SECONDS	10

अटल अचिन्हित दीर्घ suspend_test_start_समय;
अटल u32 test_repeat_count_max = 1;
अटल u32 test_repeat_count_current;

व्योम suspend_test_start(व्योम)
अणु
	/* FIXME Use better समयbase than "jiffies", ideally a घड़ीsource.
	 * What we want is a hardware counter that will work correctly even
	 * during the irqs-are-off stages of the suspend/resume cycle...
	 */
	suspend_test_start_समय = jअगरfies;
पूर्ण

व्योम suspend_test_finish(स्थिर अक्षर *label)
अणु
	दीर्घ nj = jअगरfies - suspend_test_start_समय;
	अचिन्हित msec;

	msec = jअगरfies_to_msecs(असल(nj));
	pr_info("PM: %s took %d.%03d seconds\n", label,
			msec / 1000, msec % 1000);

	/* Warning on suspend means the RTC alarm period needs to be
	 * larger -- the प्रणाली was sooo slooowwww to suspend that the
	 * alarm (should have) fired beक्रमe the प्रणाली went to sleep!
	 *
	 * Warning on either suspend or resume also means the प्रणाली
	 * has some perक्रमmance issues.  The stack dump of a WARN_ON
	 * is more likely to get the right attention than a prपूर्णांकk...
	 */
	WARN(msec > (TEST_SUSPEND_SECONDS * 1000),
	     "Component: %s, time: %u\n", label, msec);
पूर्ण

/*
 * To test प्रणाली suspend, we need a hands-off mechanism to resume the
 * प्रणाली.  RTCs wake alarms are a common self-contained mechanism.
 */

अटल व्योम __init test_wakealarm(काष्ठा rtc_device *rtc, suspend_state_t state)
अणु
	अटल अक्षर err_पढ़ोसमय[] __initdata =
		KERN_ERR "PM: can't read %s time, err %d\n";
	अटल अक्षर err_wakealarm [] __initdata =
		KERN_ERR "PM: can't set %s wakealarm, err %d\n";
	अटल अक्षर err_suspend[] __initdata =
		KERN_ERR "PM: suspend test failed, error %d\n";
	अटल अक्षर info_test[] __initdata =
		KERN_INFO "PM: test RTC wakeup from '%s' suspend\n";

	समय64_t		now;
	काष्ठा rtc_wkalrm	alm;
	पूर्णांक			status;

	/* this may fail अगर the RTC hasn't been initialized */
repeat:
	status = rtc_पढ़ो_समय(rtc, &alm.समय);
	अगर (status < 0) अणु
		prपूर्णांकk(err_पढ़ोसमय, dev_name(&rtc->dev), status);
		वापस;
	पूर्ण
	now = rtc_पंचांग_to_समय64(&alm.समय);

	स_रखो(&alm, 0, माप alm);
	rtc_समय64_to_पंचांग(now + TEST_SUSPEND_SECONDS, &alm.समय);
	alm.enabled = true;

	status = rtc_set_alarm(rtc, &alm);
	अगर (status < 0) अणु
		prपूर्णांकk(err_wakealarm, dev_name(&rtc->dev), status);
		वापस;
	पूर्ण

	अगर (state == PM_SUSPEND_MEM) अणु
		prपूर्णांकk(info_test, pm_states[state]);
		status = pm_suspend(state);
		अगर (status == -ENODEV)
			state = PM_SUSPEND_STANDBY;
	पूर्ण
	अगर (state == PM_SUSPEND_STANDBY) अणु
		prपूर्णांकk(info_test, pm_states[state]);
		status = pm_suspend(state);
		अगर (status < 0)
			state = PM_SUSPEND_TO_IDLE;
	पूर्ण
	अगर (state == PM_SUSPEND_TO_IDLE) अणु
		prपूर्णांकk(info_test, pm_states[state]);
		status = pm_suspend(state);
	पूर्ण

	अगर (status < 0)
		prपूर्णांकk(err_suspend, status);

	test_repeat_count_current++;
	अगर (test_repeat_count_current < test_repeat_count_max)
		जाओ repeat;

	/* Some platक्रमms can't detect that the alarm triggered the
	 * wakeup, or (accordingly) disable it after it afterwards.
	 * It's supposed to give oneshot behavior; cope.
	 */
	alm.enabled = false;
	rtc_set_alarm(rtc, &alm);
पूर्ण

अटल पूर्णांक __init has_wakealarm(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा rtc_device *candidate = to_rtc_device(dev);

	अगर (!candidate->ops->set_alarm)
		वापस 0;
	अगर (!device_may_wakeup(candidate->dev.parent))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Kernel options like "test_suspend=mem" क्रमce suspend/resume sanity tests
 * at startup समय.  They're normally disabled, क्रम faster boot and because
 * we can't know which states really work on this particular प्रणाली.
 */
अटल स्थिर अक्षर *test_state_label __initdata;

अटल अक्षर warn_bad_state[] __initdata =
	KERN_WARNING "PM: can't test '%s' suspend state\n";

अटल पूर्णांक __init setup_test_suspend(अक्षर *value)
अणु
	पूर्णांक i;
	अक्षर *repeat;
	अक्षर *suspend_type;

	/* example : "=mem[,N]" ==> "mem[,N]" */
	value++;
	suspend_type = strsep(&value, ",");
	अगर (!suspend_type)
		वापस 0;

	repeat = strsep(&value, ",");
	अगर (repeat) अणु
		अगर (kstrtou32(repeat, 0, &test_repeat_count_max))
			वापस 0;
	पूर्ण

	क्रम (i = PM_SUSPEND_MIN; i < PM_SUSPEND_MAX; i++)
		अगर (!म_भेद(pm_labels[i], suspend_type)) अणु
			test_state_label = pm_labels[i];
			वापस 0;
		पूर्ण

	prपूर्णांकk(warn_bad_state, suspend_type);
	वापस 0;
पूर्ण
__setup("test_suspend", setup_test_suspend);

अटल पूर्णांक __init test_suspend(व्योम)
अणु
	अटल अक्षर		warn_no_rtc[] __initdata =
		KERN_WARNING "PM: no wakealarm-capable RTC driver is ready\n";

	काष्ठा rtc_device	*rtc = शून्य;
	काष्ठा device		*dev;
	suspend_state_t test_state;

	/* PM is initialized by now; is that state testable? */
	अगर (!test_state_label)
		वापस 0;

	क्रम (test_state = PM_SUSPEND_MIN; test_state < PM_SUSPEND_MAX; test_state++) अणु
		स्थिर अक्षर *state_label = pm_states[test_state];

		अगर (state_label && !म_भेद(test_state_label, state_label))
			अवरोध;
	पूर्ण
	अगर (test_state == PM_SUSPEND_MAX) अणु
		prपूर्णांकk(warn_bad_state, test_state_label);
		वापस 0;
	पूर्ण

	/* RTCs have initialized by now too ... can we use one? */
	dev = class_find_device(rtc_class, शून्य, शून्य, has_wakealarm);
	अगर (dev) अणु
		rtc = rtc_class_खोलो(dev_name(dev));
		put_device(dev);
	पूर्ण
	अगर (!rtc) अणु
		prपूर्णांकk(warn_no_rtc);
		वापस 0;
	पूर्ण

	/* go क्रम it */
	test_wakealarm(rtc, test_state);
	rtc_class_बंद(rtc);
	वापस 0;
पूर्ण
late_initcall(test_suspend);
