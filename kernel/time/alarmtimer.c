<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alarmसमयr पूर्णांकerface
 *
 * This पूर्णांकerface provides a समयr which is similar to hrसमयrs,
 * but triggers a RTC alarm अगर the box is suspend.
 *
 * This पूर्णांकerface is influenced by the Android RTC Alarm समयr
 * पूर्णांकerface.
 *
 * Copyright (C) 2010 IBM Corporation
 *
 * Author: John Stultz <john.stultz@linaro.org>
 */
#समावेश <linux/समय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/समयrqueue.h>
#समावेश <linux/rtc.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/alarmसमयr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/समय_namespace.h>

#समावेश "posix-timers.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/alarmसमयr.h>

/**
 * काष्ठा alarm_base - Alarm समयr bases
 * @lock:		Lock क्रम syncrhonized access to the base
 * @समयrqueue:		Timerqueue head managing the list of events
 * @get_kसमय:		Function to पढ़ो the समय correlating to the base
 * @get_बारpec:	Function to पढ़ो the namespace समय correlating to the base
 * @base_घड़ीid:	घड़ीid क्रम the base
 */
अटल काष्ठा alarm_base अणु
	spinlock_t		lock;
	काष्ठा समयrqueue_head	समयrqueue;
	kसमय_प्रकार			(*get_kसमय)(व्योम);
	व्योम			(*get_बारpec)(काष्ठा बारpec64 *tp);
	घड़ीid_t		base_घड़ीid;
पूर्ण alarm_bases[ALARM_NUMTYPE];

#अगर defined(CONFIG_POSIX_TIMERS) || defined(CONFIG_RTC_CLASS)
/* मुक्तzer inक्रमmation to handle घड़ी_nanosleep triggered wakeups */
अटल क्रमागत alarmसमयr_type मुक्तzer_alarmtype;
अटल kसमय_प्रकार मुक्तzer_expires;
अटल kसमय_प्रकार मुक्तzer_delta;
अटल DEFINE_SPINLOCK(मुक्तzer_delta_lock);
#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_CLASS
/* rtc समयr and device क्रम setting alarm wakeups at suspend */
अटल काष्ठा rtc_समयr		rtस_समयr;
अटल काष्ठा rtc_device	*rtcdev;
अटल DEFINE_SPINLOCK(rtcdev_lock);

/**
 * alarmसमयr_get_rtcdev - Return selected rtcdevice
 *
 * This function वापसs the rtc device to use क्रम wakealarms.
 */
काष्ठा rtc_device *alarmसमयr_get_rtcdev(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rtc_device *ret;

	spin_lock_irqsave(&rtcdev_lock, flags);
	ret = rtcdev;
	spin_unlock_irqrestore(&rtcdev_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(alarmसमयr_get_rtcdev);

अटल पूर्णांक alarmसमयr_rtc_add_device(काष्ठा device *dev,
				काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rtc_device *rtc = to_rtc_device(dev);
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret = 0;

	अगर (rtcdev)
		वापस -EBUSY;

	अगर (!test_bit(RTC_FEATURE_ALARM, rtc->features))
		वापस -1;
	अगर (!device_may_wakeup(rtc->dev.parent))
		वापस -1;

	pdev = platक्रमm_device_रेजिस्टर_data(dev, "alarmtimer",
					     PLATFORM_DEVID_AUTO, शून्य, 0);
	अगर (!IS_ERR(pdev))
		device_init_wakeup(&pdev->dev, true);

	spin_lock_irqsave(&rtcdev_lock, flags);
	अगर (!IS_ERR(pdev) && !rtcdev) अणु
		अगर (!try_module_get(rtc->owner)) अणु
			ret = -1;
			जाओ unlock;
		पूर्ण

		rtcdev = rtc;
		/* hold a reference so it करोesn't go away */
		get_device(dev);
		pdev = शून्य;
	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण
unlock:
	spin_unlock_irqrestore(&rtcdev_lock, flags);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम alarmसमयr_rtc_समयr_init(व्योम)
अणु
	rtc_समयr_init(&rtस_समयr, शून्य, शून्य);
पूर्ण

अटल काष्ठा class_पूर्णांकerface alarmसमयr_rtc_पूर्णांकerface = अणु
	.add_dev = &alarmसमयr_rtc_add_device,
पूर्ण;

अटल पूर्णांक alarmसमयr_rtc_पूर्णांकerface_setup(व्योम)
अणु
	alarmसमयr_rtc_पूर्णांकerface.class = rtc_class;
	वापस class_पूर्णांकerface_रेजिस्टर(&alarmसमयr_rtc_पूर्णांकerface);
पूर्ण
अटल व्योम alarmसमयr_rtc_पूर्णांकerface_हटाओ(व्योम)
अणु
	class_पूर्णांकerface_unरेजिस्टर(&alarmसमयr_rtc_पूर्णांकerface);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक alarmसमयr_rtc_पूर्णांकerface_setup(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम alarmसमयr_rtc_पूर्णांकerface_हटाओ(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम alarmसमयr_rtc_समयr_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/**
 * alarmसमयr_enqueue - Adds an alarm समयr to an alarm_base समयrqueue
 * @base: poपूर्णांकer to the base where the समयr is being run
 * @alarm: poपूर्णांकer to alarm being enqueued.
 *
 * Adds alarm to a alarm_base समयrqueue
 *
 * Must hold base->lock when calling.
 */
अटल व्योम alarmसमयr_enqueue(काष्ठा alarm_base *base, काष्ठा alarm *alarm)
अणु
	अगर (alarm->state & ALARMTIMER_STATE_ENQUEUED)
		समयrqueue_del(&base->समयrqueue, &alarm->node);

	समयrqueue_add(&base->समयrqueue, &alarm->node);
	alarm->state |= ALARMTIMER_STATE_ENQUEUED;
पूर्ण

/**
 * alarmसमयr_dequeue - Removes an alarm समयr from an alarm_base समयrqueue
 * @base: poपूर्णांकer to the base where the समयr is running
 * @alarm: poपूर्णांकer to alarm being हटाओd
 *
 * Removes alarm to a alarm_base समयrqueue
 *
 * Must hold base->lock when calling.
 */
अटल व्योम alarmसमयr_dequeue(काष्ठा alarm_base *base, काष्ठा alarm *alarm)
अणु
	अगर (!(alarm->state & ALARMTIMER_STATE_ENQUEUED))
		वापस;

	समयrqueue_del(&base->समयrqueue, &alarm->node);
	alarm->state &= ~ALARMTIMER_STATE_ENQUEUED;
पूर्ण


/**
 * alarmसमयr_fired - Handles alarm hrसमयr being fired.
 * @समयr: poपूर्णांकer to hrसमयr being run
 *
 * When a alarm समयr fires, this runs through the समयrqueue to
 * see which alarms expired, and runs those. If there are more alarm
 * समयrs queued क्रम the future, we set the hrसमयr to fire when
 * the next future alarm समयr expires.
 */
अटल क्रमागत hrसमयr_restart alarmसमयr_fired(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा alarm *alarm = container_of(समयr, काष्ठा alarm, समयr);
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = HRTIMER_NORESTART;
	पूर्णांक restart = ALARMTIMER_NORESTART;

	spin_lock_irqsave(&base->lock, flags);
	alarmसमयr_dequeue(base, alarm);
	spin_unlock_irqrestore(&base->lock, flags);

	अगर (alarm->function)
		restart = alarm->function(alarm, base->get_kसमय());

	spin_lock_irqsave(&base->lock, flags);
	अगर (restart != ALARMTIMER_NORESTART) अणु
		hrसमयr_set_expires(&alarm->समयr, alarm->node.expires);
		alarmसमयr_enqueue(base, alarm);
		ret = HRTIMER_RESTART;
	पूर्ण
	spin_unlock_irqrestore(&base->lock, flags);

	trace_alarmसमयr_fired(alarm, base->get_kसमय());
	वापस ret;

पूर्ण

kसमय_प्रकार alarm_expires_reमुख्यing(स्थिर काष्ठा alarm *alarm)
अणु
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];
	वापस kसमय_sub(alarm->node.expires, base->get_kसमय());
पूर्ण
EXPORT_SYMBOL_GPL(alarm_expires_reमुख्यing);

#अगर_घोषित CONFIG_RTC_CLASS
/**
 * alarmसमयr_suspend - Suspend समय callback
 * @dev: unused
 *
 * When we are going पूर्णांकo suspend, we look through the bases
 * to see which is the soonest समयr to expire. We then
 * set an rtc समयr to fire that far पूर्णांकo the future, which
 * will wake us from suspend.
 */
अटल पूर्णांक alarmसमयr_suspend(काष्ठा device *dev)
अणु
	kसमय_प्रकार min, now, expires;
	पूर्णांक i, ret, type;
	काष्ठा rtc_device *rtc;
	अचिन्हित दीर्घ flags;
	काष्ठा rtc_समय पंचांग;

	spin_lock_irqsave(&मुक्तzer_delta_lock, flags);
	min = मुक्तzer_delta;
	expires = मुक्तzer_expires;
	type = मुक्तzer_alarmtype;
	मुक्तzer_delta = 0;
	spin_unlock_irqrestore(&मुक्तzer_delta_lock, flags);

	rtc = alarmसमयr_get_rtcdev();
	/* If we have no rtcdev, just वापस */
	अगर (!rtc)
		वापस 0;

	/* Find the soonest समयr to expire*/
	क्रम (i = 0; i < ALARM_NUMTYPE; i++) अणु
		काष्ठा alarm_base *base = &alarm_bases[i];
		काष्ठा समयrqueue_node *next;
		kसमय_प्रकार delta;

		spin_lock_irqsave(&base->lock, flags);
		next = समयrqueue_getnext(&base->समयrqueue);
		spin_unlock_irqrestore(&base->lock, flags);
		अगर (!next)
			जारी;
		delta = kसमय_sub(next->expires, base->get_kसमय());
		अगर (!min || (delta < min)) अणु
			expires = next->expires;
			min = delta;
			type = i;
		पूर्ण
	पूर्ण
	अगर (min == 0)
		वापस 0;

	अगर (kसमय_प्रकारo_ns(min) < 2 * NSEC_PER_SEC) अणु
		pm_wakeup_event(dev, 2 * MSEC_PER_SEC);
		वापस -EBUSY;
	पूर्ण

	trace_alarmसमयr_suspend(expires, type);

	/* Setup an rtc समयr to fire that far in the future */
	rtc_समयr_cancel(rtc, &rtस_समयr);
	rtc_पढ़ो_समय(rtc, &पंचांग);
	now = rtc_पंचांग_to_kसमय(पंचांग);
	now = kसमय_add(now, min);

	/* Set alarm, अगर in the past reject suspend briefly to handle */
	ret = rtc_समयr_start(rtc, &rtस_समयr, now, 0);
	अगर (ret < 0)
		pm_wakeup_event(dev, MSEC_PER_SEC);
	वापस ret;
पूर्ण

अटल पूर्णांक alarmसमयr_resume(काष्ठा device *dev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = alarmसमयr_get_rtcdev();
	अगर (rtc)
		rtc_समयr_cancel(rtc, &rtस_समयr);
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक alarmसमयr_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक alarmसमयr_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम
__alarm_init(काष्ठा alarm *alarm, क्रमागत alarmसमयr_type type,
	     क्रमागत alarmसमयr_restart (*function)(काष्ठा alarm *, kसमय_प्रकार))
अणु
	समयrqueue_init(&alarm->node);
	alarm->समयr.function = alarmसमयr_fired;
	alarm->function = function;
	alarm->type = type;
	alarm->state = ALARMTIMER_STATE_INACTIVE;
पूर्ण

/**
 * alarm_init - Initialize an alarm काष्ठाure
 * @alarm: ptr to alarm to be initialized
 * @type: the type of the alarm
 * @function: callback that is run when the alarm fires
 */
व्योम alarm_init(काष्ठा alarm *alarm, क्रमागत alarmसमयr_type type,
		क्रमागत alarmसमयr_restart (*function)(काष्ठा alarm *, kसमय_प्रकार))
अणु
	hrसमयr_init(&alarm->समयr, alarm_bases[type].base_घड़ीid,
		     HRTIMER_MODE_ABS);
	__alarm_init(alarm, type, function);
पूर्ण
EXPORT_SYMBOL_GPL(alarm_init);

/**
 * alarm_start - Sets an असलolute alarm to fire
 * @alarm: ptr to alarm to set
 * @start: समय to run the alarm
 */
व्योम alarm_start(काष्ठा alarm *alarm, kसमय_प्रकार start)
अणु
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&base->lock, flags);
	alarm->node.expires = start;
	alarmसमयr_enqueue(base, alarm);
	hrसमयr_start(&alarm->समयr, alarm->node.expires, HRTIMER_MODE_ABS);
	spin_unlock_irqrestore(&base->lock, flags);

	trace_alarmसमयr_start(alarm, base->get_kसमय());
पूर्ण
EXPORT_SYMBOL_GPL(alarm_start);

/**
 * alarm_start_relative - Sets a relative alarm to fire
 * @alarm: ptr to alarm to set
 * @start: समय relative to now to run the alarm
 */
व्योम alarm_start_relative(काष्ठा alarm *alarm, kसमय_प्रकार start)
अणु
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];

	start = kसमय_add_safe(start, base->get_kसमय());
	alarm_start(alarm, start);
पूर्ण
EXPORT_SYMBOL_GPL(alarm_start_relative);

व्योम alarm_restart(काष्ठा alarm *alarm)
अणु
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&base->lock, flags);
	hrसमयr_set_expires(&alarm->समयr, alarm->node.expires);
	hrसमयr_restart(&alarm->समयr);
	alarmसमयr_enqueue(base, alarm);
	spin_unlock_irqrestore(&base->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(alarm_restart);

/**
 * alarm_try_to_cancel - Tries to cancel an alarm समयr
 * @alarm: ptr to alarm to be canceled
 *
 * Returns 1 अगर the समयr was canceled, 0 अगर it was not running,
 * and -1 अगर the callback was running
 */
पूर्णांक alarm_try_to_cancel(काष्ठा alarm *alarm)
अणु
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&base->lock, flags);
	ret = hrसमयr_try_to_cancel(&alarm->समयr);
	अगर (ret >= 0)
		alarmसमयr_dequeue(base, alarm);
	spin_unlock_irqrestore(&base->lock, flags);

	trace_alarmसमयr_cancel(alarm, base->get_kसमय());
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(alarm_try_to_cancel);


/**
 * alarm_cancel - Spins trying to cancel an alarm समयr until it is करोne
 * @alarm: ptr to alarm to be canceled
 *
 * Returns 1 अगर the समयr was canceled, 0 अगर it was not active.
 */
पूर्णांक alarm_cancel(काष्ठा alarm *alarm)
अणु
	क्रम (;;) अणु
		पूर्णांक ret = alarm_try_to_cancel(alarm);
		अगर (ret >= 0)
			वापस ret;
		hrसमयr_cancel_रुको_running(&alarm->समयr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(alarm_cancel);


u64 alarm_क्रमward(काष्ठा alarm *alarm, kसमय_प्रकार now, kसमय_प्रकार पूर्णांकerval)
अणु
	u64 overrun = 1;
	kसमय_प्रकार delta;

	delta = kसमय_sub(now, alarm->node.expires);

	अगर (delta < 0)
		वापस 0;

	अगर (unlikely(delta >= पूर्णांकerval)) अणु
		s64 incr = kसमय_प्रकारo_ns(पूर्णांकerval);

		overrun = kसमय_भागns(delta, incr);

		alarm->node.expires = kसमय_add_ns(alarm->node.expires,
							incr*overrun);

		अगर (alarm->node.expires > now)
			वापस overrun;
		/*
		 * This (and the kसमय_add() below) is the
		 * correction क्रम exact:
		 */
		overrun++;
	पूर्ण

	alarm->node.expires = kसमय_add_safe(alarm->node.expires, पूर्णांकerval);
	वापस overrun;
पूर्ण
EXPORT_SYMBOL_GPL(alarm_क्रमward);

u64 alarm_क्रमward_now(काष्ठा alarm *alarm, kसमय_प्रकार पूर्णांकerval)
अणु
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];

	वापस alarm_क्रमward(alarm, base->get_kसमय(), पूर्णांकerval);
पूर्ण
EXPORT_SYMBOL_GPL(alarm_क्रमward_now);

#अगर_घोषित CONFIG_POSIX_TIMERS

अटल व्योम alarmसमयr_मुक्तzerset(kसमय_प्रकार असलexp, क्रमागत alarmसमयr_type type)
अणु
	काष्ठा alarm_base *base;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार delta;

	चयन(type) अणु
	हाल ALARM_REALTIME:
		base = &alarm_bases[ALARM_REALTIME];
		type = ALARM_REALTIME_FREEZER;
		अवरोध;
	हाल ALARM_BOOTTIME:
		base = &alarm_bases[ALARM_BOOTTIME];
		type = ALARM_BOOTTIME_FREEZER;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid alarm type: %d\n", type);
		वापस;
	पूर्ण

	delta = kसमय_sub(असलexp, base->get_kसमय());

	spin_lock_irqsave(&मुक्तzer_delta_lock, flags);
	अगर (!मुक्तzer_delta || (delta < मुक्तzer_delta)) अणु
		मुक्तzer_delta = delta;
		मुक्तzer_expires = असलexp;
		मुक्तzer_alarmtype = type;
	पूर्ण
	spin_unlock_irqrestore(&मुक्तzer_delta_lock, flags);
पूर्ण

/**
 * घड़ी2alarm - helper that converts from घड़ीid to alarmtypes
 * @घड़ीid: घड़ीid.
 */
अटल क्रमागत alarmसमयr_type घड़ी2alarm(घड़ीid_t घड़ीid)
अणु
	अगर (घड़ीid == CLOCK_REALTIME_ALARM)
		वापस ALARM_REALTIME;
	अगर (घड़ीid == CLOCK_BOOTTIME_ALARM)
		वापस ALARM_BOOTTIME;
	वापस -1;
पूर्ण

/**
 * alarm_handle_समयr - Callback क्रम posix समयrs
 * @alarm: alarm that fired
 * @now: समय at the समयr expiration
 *
 * Posix समयr callback क्रम expired alarm समयrs.
 *
 * Return: whether the समयr is to be restarted
 */
अटल क्रमागत alarmसमयr_restart alarm_handle_समयr(काष्ठा alarm *alarm,
							kसमय_प्रकार now)
अणु
	काष्ठा k_iसमयr *ptr = container_of(alarm, काष्ठा k_iसमयr,
					    it.alarm.alarmसमयr);
	क्रमागत alarmसमयr_restart result = ALARMTIMER_NORESTART;
	अचिन्हित दीर्घ flags;
	पूर्णांक si_निजी = 0;

	spin_lock_irqsave(&ptr->it_lock, flags);

	ptr->it_active = 0;
	अगर (ptr->it_पूर्णांकerval)
		si_निजी = ++ptr->it_requeue_pending;

	अगर (posix_समयr_event(ptr, si_निजी) && ptr->it_पूर्णांकerval) अणु
		/*
		 * Handle ignored संकेतs and rearm the समयr. This will go
		 * away once we handle ignored संकेतs proper.
		 */
		ptr->it_overrun += alarm_क्रमward_now(alarm, ptr->it_पूर्णांकerval);
		++ptr->it_requeue_pending;
		ptr->it_active = 1;
		result = ALARMTIMER_RESTART;
	पूर्ण
	spin_unlock_irqrestore(&ptr->it_lock, flags);

	वापस result;
पूर्ण

/**
 * alarm_समयr_rearm - Posix समयr callback क्रम rearming समयr
 * @timr:	Poपूर्णांकer to the posixसमयr data काष्ठा
 */
अटल व्योम alarm_समयr_rearm(काष्ठा k_iसमयr *timr)
अणु
	काष्ठा alarm *alarm = &timr->it.alarm.alarmसमयr;

	timr->it_overrun += alarm_क्रमward_now(alarm, timr->it_पूर्णांकerval);
	alarm_start(alarm, alarm->node.expires);
पूर्ण

/**
 * alarm_समयr_क्रमward - Posix समयr callback क्रम क्रमwarding समयr
 * @timr:	Poपूर्णांकer to the posixसमयr data काष्ठा
 * @now:	Current समय to क्रमward the समयr against
 */
अटल s64 alarm_समयr_क्रमward(काष्ठा k_iसमयr *timr, kसमय_प्रकार now)
अणु
	काष्ठा alarm *alarm = &timr->it.alarm.alarmसमयr;

	वापस alarm_क्रमward(alarm, timr->it_पूर्णांकerval, now);
पूर्ण

/**
 * alarm_समयr_reमुख्यing - Posix समयr callback to retrieve reमुख्यing समय
 * @timr:	Poपूर्णांकer to the posixसमयr data काष्ठा
 * @now:	Current समय to calculate against
 */
अटल kसमय_प्रकार alarm_समयr_reमुख्यing(काष्ठा k_iसमयr *timr, kसमय_प्रकार now)
अणु
	काष्ठा alarm *alarm = &timr->it.alarm.alarmसमयr;

	वापस kसमय_sub(alarm->node.expires, now);
पूर्ण

/**
 * alarm_समयr_try_to_cancel - Posix समयr callback to cancel a समयr
 * @timr:	Poपूर्णांकer to the posixसमयr data काष्ठा
 */
अटल पूर्णांक alarm_समयr_try_to_cancel(काष्ठा k_iसमयr *timr)
अणु
	वापस alarm_try_to_cancel(&timr->it.alarm.alarmसमयr);
पूर्ण

/**
 * alarm_समयr_रुको_running - Posix समयr callback to रुको क्रम a समयr
 * @timr:	Poपूर्णांकer to the posixसमयr data काष्ठा
 *
 * Called from the core code when समयr cancel detected that the callback
 * is running. @timr is unlocked and rcu पढ़ो lock is held to prevent it
 * from being मुक्तd.
 */
अटल व्योम alarm_समयr_रुको_running(काष्ठा k_iसमयr *timr)
अणु
	hrसमयr_cancel_रुको_running(&timr->it.alarm.alarmसमयr.समयr);
पूर्ण

/**
 * alarm_समयr_arm - Posix समयr callback to arm a समयr
 * @timr:	Poपूर्णांकer to the posixसमयr data काष्ठा
 * @expires:	The new expiry समय
 * @असलolute:	Expiry value is असलolute समय
 * @sigev_none:	Posix समयr करोes not deliver संकेतs
 */
अटल व्योम alarm_समयr_arm(काष्ठा k_iसमयr *timr, kसमय_प्रकार expires,
			    bool असलolute, bool sigev_none)
अणु
	काष्ठा alarm *alarm = &timr->it.alarm.alarmसमयr;
	काष्ठा alarm_base *base = &alarm_bases[alarm->type];

	अगर (!असलolute)
		expires = kसमय_add_safe(expires, base->get_kसमय());
	अगर (sigev_none)
		alarm->node.expires = expires;
	अन्यथा
		alarm_start(&timr->it.alarm.alarmसमयr, expires);
पूर्ण

/**
 * alarm_घड़ी_getres - posix getres पूर्णांकerface
 * @which_घड़ी: घड़ीid
 * @tp: बारpec to fill
 *
 * Returns the granularity of underlying alarm base घड़ी
 */
अटल पूर्णांक alarm_घड़ी_getres(स्थिर घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	अगर (!alarmसमयr_get_rtcdev())
		वापस -EINVAL;

	tp->tv_sec = 0;
	tp->tv_nsec = hrसमयr_resolution;
	वापस 0;
पूर्ण

/**
 * alarm_घड़ी_get_बारpec - posix घड़ी_get_बारpec पूर्णांकerface
 * @which_घड़ी: घड़ीid
 * @tp: बारpec to fill.
 *
 * Provides the underlying alarm base समय in a tasks समय namespace.
 */
अटल पूर्णांक alarm_घड़ी_get_बारpec(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	काष्ठा alarm_base *base = &alarm_bases[घड़ी2alarm(which_घड़ी)];

	अगर (!alarmसमयr_get_rtcdev())
		वापस -EINVAL;

	base->get_बारpec(tp);

	वापस 0;
पूर्ण

/**
 * alarm_घड़ी_get_kसमय - posix घड़ी_get_kसमय पूर्णांकerface
 * @which_घड़ी: घड़ीid
 *
 * Provides the underlying alarm base समय in the root namespace.
 */
अटल kसमय_प्रकार alarm_घड़ी_get_kसमय(घड़ीid_t which_घड़ी)
अणु
	काष्ठा alarm_base *base = &alarm_bases[घड़ी2alarm(which_घड़ी)];

	अगर (!alarmसमयr_get_rtcdev())
		वापस -EINVAL;

	वापस base->get_kसमय();
पूर्ण

/**
 * alarm_समयr_create - posix समयr_create पूर्णांकerface
 * @new_समयr: k_iसमयr poपूर्णांकer to manage
 *
 * Initializes the k_iसमयr काष्ठाure.
 */
अटल पूर्णांक alarm_समयr_create(काष्ठा k_iसमयr *new_समयr)
अणु
	क्रमागत  alarmसमयr_type type;

	अगर (!alarmसमयr_get_rtcdev())
		वापस -EOPNOTSUPP;

	अगर (!capable(CAP_WAKE_ALARM))
		वापस -EPERM;

	type = घड़ी2alarm(new_समयr->it_घड़ी);
	alarm_init(&new_समयr->it.alarm.alarmसमयr, type, alarm_handle_समयr);
	वापस 0;
पूर्ण

/**
 * alarmसमयr_nsleep_wakeup - Wakeup function क्रम alarm_समयr_nsleep
 * @alarm: ptr to alarm that fired
 * @now: समय at the समयr expiration
 *
 * Wakes up the task that set the alarmसमयr
 *
 * Return: ALARMTIMER_NORESTART
 */
अटल क्रमागत alarmसमयr_restart alarmसमयr_nsleep_wakeup(काष्ठा alarm *alarm,
								kसमय_प्रकार now)
अणु
	काष्ठा task_काष्ठा *task = (काष्ठा task_काष्ठा *)alarm->data;

	alarm->data = शून्य;
	अगर (task)
		wake_up_process(task);
	वापस ALARMTIMER_NORESTART;
पूर्ण

/**
 * alarmसमयr_करो_nsleep - Internal alarmसमयr nsleep implementation
 * @alarm: ptr to alarmसमयr
 * @असलexp: असलolute expiration समय
 * @type: alarm type (BOOTTIME/REALTIME).
 *
 * Sets the alarm समयr and sleeps until it is fired or पूर्णांकerrupted.
 */
अटल पूर्णांक alarmसमयr_करो_nsleep(काष्ठा alarm *alarm, kसमय_प्रकार असलexp,
				क्रमागत alarmसमयr_type type)
अणु
	काष्ठा restart_block *restart;
	alarm->data = (व्योम *)current;
	करो अणु
		set_current_state(TASK_INTERRUPTIBLE);
		alarm_start(alarm, असलexp);
		अगर (likely(alarm->data))
			schedule();

		alarm_cancel(alarm);
	पूर्ण जबतक (alarm->data && !संकेत_pending(current));

	__set_current_state(TASK_RUNNING);

	destroy_hrसमयr_on_stack(&alarm->समयr);

	अगर (!alarm->data)
		वापस 0;

	अगर (मुक्तzing(current))
		alarmसमयr_मुक्तzerset(असलexp, type);
	restart = &current->restart_block;
	अगर (restart->nanosleep.type != TT_NONE) अणु
		काष्ठा बारpec64 rmt;
		kसमय_प्रकार rem;

		rem = kसमय_sub(असलexp, alarm_bases[type].get_kसमय());

		अगर (rem <= 0)
			वापस 0;
		rmt = kसमय_प्रकारo_बारpec64(rem);

		वापस nanosleep_copyout(restart, &rmt);
	पूर्ण
	वापस -ERESTART_RESTARTBLOCK;
पूर्ण

अटल व्योम
alarm_init_on_stack(काष्ठा alarm *alarm, क्रमागत alarmसमयr_type type,
		    क्रमागत alarmसमयr_restart (*function)(काष्ठा alarm *, kसमय_प्रकार))
अणु
	hrसमयr_init_on_stack(&alarm->समयr, alarm_bases[type].base_घड़ीid,
			      HRTIMER_MODE_ABS);
	__alarm_init(alarm, type, function);
पूर्ण

/**
 * alarm_समयr_nsleep_restart - restartblock alarmसमयr nsleep
 * @restart: ptr to restart block
 *
 * Handles restarted घड़ी_nanosleep calls
 */
अटल दीर्घ __sched alarm_समयr_nsleep_restart(काष्ठा restart_block *restart)
अणु
	क्रमागत  alarmसमयr_type type = restart->nanosleep.घड़ीid;
	kसमय_प्रकार exp = restart->nanosleep.expires;
	काष्ठा alarm alarm;

	alarm_init_on_stack(&alarm, type, alarmसमयr_nsleep_wakeup);

	वापस alarmसमयr_करो_nsleep(&alarm, exp, type);
पूर्ण

/**
 * alarm_समयr_nsleep - alarmसमयr nanosleep
 * @which_घड़ी: घड़ीid
 * @flags: determines असलसमय or relative
 * @tsreq: requested sleep समय (असल or rel)
 *
 * Handles घड़ी_nanosleep calls against _ALARM घड़ीids
 */
अटल पूर्णांक alarm_समयr_nsleep(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			      स्थिर काष्ठा बारpec64 *tsreq)
अणु
	क्रमागत  alarmसमयr_type type = घड़ी2alarm(which_घड़ी);
	काष्ठा restart_block *restart = &current->restart_block;
	काष्ठा alarm alarm;
	kसमय_प्रकार exp;
	पूर्णांक ret = 0;

	अगर (!alarmसमयr_get_rtcdev())
		वापस -EOPNOTSUPP;

	अगर (flags & ~TIMER_ABSTIME)
		वापस -EINVAL;

	अगर (!capable(CAP_WAKE_ALARM))
		वापस -EPERM;

	alarm_init_on_stack(&alarm, type, alarmसमयr_nsleep_wakeup);

	exp = बारpec64_to_kसमय(*tsreq);
	/* Convert (अगर necessary) to असलolute समय */
	अगर (flags != TIMER_ABSTIME) अणु
		kसमय_प्रकार now = alarm_bases[type].get_kसमय();

		exp = kसमय_add_safe(now, exp);
	पूर्ण अन्यथा अणु
		exp = समयns_kसमय_प्रकारo_host(which_घड़ी, exp);
	पूर्ण

	ret = alarmसमयr_करो_nsleep(&alarm, exp, type);
	अगर (ret != -ERESTART_RESTARTBLOCK)
		वापस ret;

	/* असल समयrs करोn't set reमुख्यing समय or restart */
	अगर (flags == TIMER_ABSTIME)
		वापस -ERESTARTNOHAND;

	restart->nanosleep.घड़ीid = type;
	restart->nanosleep.expires = exp;
	set_restart_fn(restart, alarm_समयr_nsleep_restart);
	वापस ret;
पूर्ण

स्थिर काष्ठा k_घड़ी alarm_घड़ी = अणु
	.घड़ी_getres		= alarm_घड़ी_getres,
	.घड़ी_get_kसमय	= alarm_घड़ी_get_kसमय,
	.घड़ी_get_बारpec	= alarm_घड़ी_get_बारpec,
	.समयr_create		= alarm_समयr_create,
	.समयr_set		= common_समयr_set,
	.समयr_del		= common_समयr_del,
	.समयr_get		= common_समयr_get,
	.समयr_arm		= alarm_समयr_arm,
	.समयr_rearm		= alarm_समयr_rearm,
	.समयr_क्रमward		= alarm_समयr_क्रमward,
	.समयr_reमुख्यing	= alarm_समयr_reमुख्यing,
	.समयr_try_to_cancel	= alarm_समयr_try_to_cancel,
	.समयr_रुको_running	= alarm_समयr_रुको_running,
	.nsleep			= alarm_समयr_nsleep,
पूर्ण;
#पूर्ण_अगर /* CONFIG_POSIX_TIMERS */


/* Suspend hook काष्ठाures */
अटल स्थिर काष्ठा dev_pm_ops alarmसमयr_pm_ops = अणु
	.suspend = alarmसमयr_suspend,
	.resume = alarmसमयr_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver alarmसमयr_driver = अणु
	.driver = अणु
		.name = "alarmtimer",
		.pm = &alarmसमयr_pm_ops,
	पूर्ण
पूर्ण;

अटल व्योम get_bootसमय_प्रकारimespec(काष्ठा बारpec64 *tp)
अणु
	kसमय_get_bootसमय_प्रकारs64(tp);
	समयns_add_bootसमय(tp);
पूर्ण

/**
 * alarmसमयr_init - Initialize alarm समयr code
 *
 * This function initializes the alarm bases and रेजिस्टरs
 * the posix घड़ी ids.
 */
अटल पूर्णांक __init alarmसमयr_init(व्योम)
अणु
	पूर्णांक error;
	पूर्णांक i;

	alarmसमयr_rtc_समयr_init();

	/* Initialize alarm bases */
	alarm_bases[ALARM_REALTIME].base_घड़ीid = CLOCK_REALTIME;
	alarm_bases[ALARM_REALTIME].get_kसमय = &kसमय_get_real;
	alarm_bases[ALARM_REALTIME].get_बारpec = kसमय_get_real_ts64;
	alarm_bases[ALARM_BOOTTIME].base_घड़ीid = CLOCK_BOOTTIME;
	alarm_bases[ALARM_BOOTTIME].get_kसमय = &kसमय_get_bootसमय;
	alarm_bases[ALARM_BOOTTIME].get_बारpec = get_bootसमय_प्रकारimespec;
	क्रम (i = 0; i < ALARM_NUMTYPE; i++) अणु
		समयrqueue_init_head(&alarm_bases[i].समयrqueue);
		spin_lock_init(&alarm_bases[i].lock);
	पूर्ण

	error = alarmसमयr_rtc_पूर्णांकerface_setup();
	अगर (error)
		वापस error;

	error = platक्रमm_driver_रेजिस्टर(&alarmसमयr_driver);
	अगर (error)
		जाओ out_अगर;

	वापस 0;
out_अगर:
	alarmसमयr_rtc_पूर्णांकerface_हटाओ();
	वापस error;
पूर्ण
device_initcall(alarmसमयr_init);
