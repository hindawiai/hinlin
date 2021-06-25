<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC subप्रणाली, पूर्णांकerface functions
 *
 * Copyright (C) 2005 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * based on arch/arm/common/rtस_समय.c
 */

#समावेश <linux/rtc.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/log2.h>
#समावेश <linux/workqueue.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/rtc.h>

अटल पूर्णांक rtc_समयr_enqueue(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr);
अटल व्योम rtc_समयr_हटाओ(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr);

अटल व्योम rtc_add_offset(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t secs;

	अगर (!rtc->offset_secs)
		वापस;

	secs = rtc_पंचांग_to_समय64(पंचांग);

	/*
	 * Since the पढ़ोing समय values from RTC device are always in the RTC
	 * original valid range, but we need to skip the overlapped region
	 * between expanded range and original range, which is no need to add
	 * the offset.
	 */
	अगर ((rtc->start_secs > rtc->range_min && secs >= rtc->start_secs) ||
	    (rtc->start_secs < rtc->range_min &&
	     secs <= (rtc->start_secs + rtc->range_max - rtc->range_min)))
		वापस;

	rtc_समय64_to_पंचांग(secs + rtc->offset_secs, पंचांग);
पूर्ण

अटल व्योम rtc_subtract_offset(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t secs;

	अगर (!rtc->offset_secs)
		वापस;

	secs = rtc_पंचांग_to_समय64(पंचांग);

	/*
	 * If the setting समय values are in the valid range of RTC hardware
	 * device, then no need to subtract the offset when setting समय to RTC
	 * device. Otherwise we need to subtract the offset to make the समय
	 * values are valid क्रम RTC hardware device.
	 */
	अगर (secs >= rtc->range_min && secs <= rtc->range_max)
		वापस;

	rtc_समय64_to_पंचांग(secs - rtc->offset_secs, पंचांग);
पूर्ण

अटल पूर्णांक rtc_valid_range(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	अगर (rtc->range_min != rtc->range_max) अणु
		समय64_t समय = rtc_पंचांग_to_समय64(पंचांग);
		समय64_t range_min = rtc->set_start_समय ? rtc->start_secs :
			rtc->range_min;
		समयu64_t range_max = rtc->set_start_समय ?
			(rtc->start_secs + rtc->range_max - rtc->range_min) :
			rtc->range_max;

		अगर (समय < range_min || समय > range_max)
			वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __rtc_पढ़ो_समय(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक err;

	अगर (!rtc->ops) अणु
		err = -ENODEV;
	पूर्ण अन्यथा अगर (!rtc->ops->पढ़ो_समय) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		स_रखो(पंचांग, 0, माप(काष्ठा rtc_समय));
		err = rtc->ops->पढ़ो_समय(rtc->dev.parent, पंचांग);
		अगर (err < 0) अणु
			dev_dbg(&rtc->dev, "read_time: fail to read: %d\n",
				err);
			वापस err;
		पूर्ण

		rtc_add_offset(rtc, पंचांग);

		err = rtc_valid_पंचांग(पंचांग);
		अगर (err < 0)
			dev_dbg(&rtc->dev, "read_time: rtc_time isn't valid\n");
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक rtc_पढ़ो_समय(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

	err = __rtc_पढ़ो_समय(rtc, पंचांग);
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_पढ़ो_समय(rtc_पंचांग_to_समय64(पंचांग), err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_पढ़ो_समय);

पूर्णांक rtc_set_समय(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक err, uie;

	err = rtc_valid_पंचांग(पंचांग);
	अगर (err != 0)
		वापस err;

	err = rtc_valid_range(rtc, पंचांग);
	अगर (err)
		वापस err;

	rtc_subtract_offset(rtc, पंचांग);

#अगर_घोषित CONFIG_RTC_INTF_DEV_UIE_EMUL
	uie = rtc->uie_rtस_समयr.enabled || rtc->uie_irq_active;
#अन्यथा
	uie = rtc->uie_rtस_समयr.enabled;
#पूर्ण_अगर
	अगर (uie) अणु
		err = rtc_update_irq_enable(rtc, 0);
		अगर (err)
			वापस err;
	पूर्ण

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

	अगर (!rtc->ops)
		err = -ENODEV;
	अन्यथा अगर (rtc->ops->set_समय)
		err = rtc->ops->set_समय(rtc->dev.parent, पंचांग);
	अन्यथा
		err = -EINVAL;

	pm_stay_awake(rtc->dev.parent);
	mutex_unlock(&rtc->ops_lock);
	/* A समयr might have just expired */
	schedule_work(&rtc->irqwork);

	अगर (uie) अणु
		err = rtc_update_irq_enable(rtc, 1);
		अगर (err)
			वापस err;
	पूर्ण

	trace_rtc_set_समय(rtc_पंचांग_to_समय64(पंचांग), err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_set_समय);

अटल पूर्णांक rtc_पढ़ो_alarm_पूर्णांकernal(काष्ठा rtc_device *rtc,
				   काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

	अगर (!rtc->ops) अणु
		err = -ENODEV;
	पूर्ण अन्यथा अगर (!test_bit(RTC_FEATURE_ALARM, rtc->features) || !rtc->ops->पढ़ो_alarm) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		alarm->enabled = 0;
		alarm->pending = 0;
		alarm->समय.पंचांग_sec = -1;
		alarm->समय.पंचांग_min = -1;
		alarm->समय.पंचांग_hour = -1;
		alarm->समय.पंचांग_mday = -1;
		alarm->समय.पंचांग_mon = -1;
		alarm->समय.पंचांग_year = -1;
		alarm->समय.पंचांग_wday = -1;
		alarm->समय.पंचांग_yday = -1;
		alarm->समय.पंचांग_isdst = -1;
		err = rtc->ops->पढ़ो_alarm(rtc->dev.parent, alarm);
	पूर्ण

	mutex_unlock(&rtc->ops_lock);

	trace_rtc_पढ़ो_alarm(rtc_पंचांग_to_समय64(&alarm->समय), err);
	वापस err;
पूर्ण

पूर्णांक __rtc_पढ़ो_alarm(काष्ठा rtc_device *rtc, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक err;
	काष्ठा rtc_समय beक्रमe, now;
	पूर्णांक first_समय = 1;
	समय64_t t_now, t_alm;
	क्रमागत अणु none, day, month, year पूर्ण missing = none;
	अचिन्हित पूर्णांक days;

	/* The lower level RTC driver may वापस -1 in some fields,
	 * creating invalid alarm->समय values, क्रम reasons like:
	 *
	 *   - The hardware may not be capable of filling them in;
	 *     many alarms match only on समय-of-day fields, not
	 *     day/month/year calendar data.
	 *
	 *   - Some hardware uses illegal values as "wildcard" match
	 *     values, which non-Linux firmware (like a BIOS) may try
	 *     to set up as e.g. "alarm 15 minutes after each hour".
	 *     Linux uses only oneshot alarms.
	 *
	 * When we see that here, we deal with it by using values from
	 * a current RTC बारtamp क्रम any missing (-1) values.  The
	 * RTC driver prevents "periodic alarm" modes.
	 *
	 * But this can be racey, because some fields of the RTC बारtamp
	 * may have wrapped in the पूर्णांकerval since we पढ़ो the RTC alarm,
	 * which would lead to us inserting inconsistent values in place
	 * of the -1 fields.
	 *
	 * Reading the alarm and बारtamp in the reverse sequence
	 * would have the same race condition, and not solve the issue.
	 *
	 * So, we must first पढ़ो the RTC बारtamp,
	 * then पढ़ो the RTC alarm value,
	 * and then पढ़ो a second RTC बारtamp.
	 *
	 * If any fields of the second बारtamp have changed
	 * when compared with the first बारtamp, then we know
	 * our बारtamp may be inconsistent with that used by
	 * the low-level rtc_पढ़ो_alarm_पूर्णांकernal() function.
	 *
	 * So, when the two बारtamps disagree, we just loop and करो
	 * the process again to get a fully consistent set of values.
	 *
	 * This could all instead be करोne in the lower level driver,
	 * but since more than one lower level RTC implementation needs it,
	 * then it's probably best best to करो it here instead of there..
	 */

	/* Get the "before" बारtamp */
	err = rtc_पढ़ो_समय(rtc, &beक्रमe);
	अगर (err < 0)
		वापस err;
	करो अणु
		अगर (!first_समय)
			स_नकल(&beक्रमe, &now, माप(काष्ठा rtc_समय));
		first_समय = 0;

		/* get the RTC alarm values, which may be incomplete */
		err = rtc_पढ़ो_alarm_पूर्णांकernal(rtc, alarm);
		अगर (err)
			वापस err;

		/* full-function RTCs won't have such missing fields */
		अगर (rtc_valid_पंचांग(&alarm->समय) == 0) अणु
			rtc_add_offset(rtc, &alarm->समय);
			वापस 0;
		पूर्ण

		/* get the "after" बारtamp, to detect wrapped fields */
		err = rtc_पढ़ो_समय(rtc, &now);
		अगर (err < 0)
			वापस err;

		/* note that पंचांग_sec is a "don't care" value here: */
	पूर्ण जबतक (beक्रमe.पंचांग_min  != now.पंचांग_min ||
		 beक्रमe.पंचांग_hour != now.पंचांग_hour ||
		 beक्रमe.पंचांग_mon  != now.पंचांग_mon ||
		 beक्रमe.पंचांग_year != now.पंचांग_year);

	/* Fill in the missing alarm fields using the बारtamp; we
	 * know there's at least one since alarm->समय is invalid.
	 */
	अगर (alarm->समय.पंचांग_sec == -1)
		alarm->समय.पंचांग_sec = now.पंचांग_sec;
	अगर (alarm->समय.पंचांग_min == -1)
		alarm->समय.पंचांग_min = now.पंचांग_min;
	अगर (alarm->समय.पंचांग_hour == -1)
		alarm->समय.पंचांग_hour = now.पंचांग_hour;

	/* For simplicity, only support date rollover क्रम now */
	अगर (alarm->समय.पंचांग_mday < 1 || alarm->समय.पंचांग_mday > 31) अणु
		alarm->समय.पंचांग_mday = now.पंचांग_mday;
		missing = day;
	पूर्ण
	अगर ((अचिन्हित पूर्णांक)alarm->समय.पंचांग_mon >= 12) अणु
		alarm->समय.पंचांग_mon = now.पंचांग_mon;
		अगर (missing == none)
			missing = month;
	पूर्ण
	अगर (alarm->समय.पंचांग_year == -1) अणु
		alarm->समय.पंचांग_year = now.पंचांग_year;
		अगर (missing == none)
			missing = year;
	पूर्ण

	/* Can't proceed अगर alarm is still invalid after replacing
	 * missing fields.
	 */
	err = rtc_valid_पंचांग(&alarm->समय);
	अगर (err)
		जाओ करोne;

	/* with luck, no rollover is needed */
	t_now = rtc_पंचांग_to_समय64(&now);
	t_alm = rtc_पंचांग_to_समय64(&alarm->समय);
	अगर (t_now < t_alm)
		जाओ करोne;

	चयन (missing) अणु
	/* 24 hour rollover ... अगर it's now 10am Monday, an alarm that
	 * that will trigger at 5am will करो so at 5am Tuesday, which
	 * could also be in the next month or year.  This is a common
	 * हाल, especially क्रम PCs.
	 */
	हाल day:
		dev_dbg(&rtc->dev, "alarm rollover: %s\n", "day");
		t_alm += 24 * 60 * 60;
		rtc_समय64_to_पंचांग(t_alm, &alarm->समय);
		अवरोध;

	/* Month rollover ... अगर it's the 31th, an alarm on the 3rd will
	 * be next month.  An alarm matching on the 30th, 29th, or 28th
	 * may end up in the month after that!  Many newer PCs support
	 * this type of alarm.
	 */
	हाल month:
		dev_dbg(&rtc->dev, "alarm rollover: %s\n", "month");
		करो अणु
			अगर (alarm->समय.पंचांग_mon < 11) अणु
				alarm->समय.पंचांग_mon++;
			पूर्ण अन्यथा अणु
				alarm->समय.पंचांग_mon = 0;
				alarm->समय.पंचांग_year++;
			पूर्ण
			days = rtc_month_days(alarm->समय.पंचांग_mon,
					      alarm->समय.पंचांग_year);
		पूर्ण जबतक (days < alarm->समय.पंचांग_mday);
		अवरोध;

	/* Year rollover ... easy except क्रम leap years! */
	हाल year:
		dev_dbg(&rtc->dev, "alarm rollover: %s\n", "year");
		करो अणु
			alarm->समय.पंचांग_year++;
		पूर्ण जबतक (!is_leap_year(alarm->समय.पंचांग_year + 1900) &&
			 rtc_valid_पंचांग(&alarm->समय) != 0);
		अवरोध;

	शेष:
		dev_warn(&rtc->dev, "alarm rollover not handled\n");
	पूर्ण

	err = rtc_valid_पंचांग(&alarm->समय);

करोne:
	अगर (err)
		dev_warn(&rtc->dev, "invalid alarm value: %ptR\n",
			 &alarm->समय);

	वापस err;
पूर्ण

पूर्णांक rtc_पढ़ो_alarm(काष्ठा rtc_device *rtc, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;
	अगर (!rtc->ops) अणु
		err = -ENODEV;
	पूर्ण अन्यथा अगर (!test_bit(RTC_FEATURE_ALARM, rtc->features) || !rtc->ops->पढ़ो_alarm) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		स_रखो(alarm, 0, माप(काष्ठा rtc_wkalrm));
		alarm->enabled = rtc->aie_समयr.enabled;
		alarm->समय = rtc_kसमय_प्रकारo_पंचांग(rtc->aie_समयr.node.expires);
	पूर्ण
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_पढ़ो_alarm(rtc_पंचांग_to_समय64(&alarm->समय), err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_पढ़ो_alarm);

अटल पूर्णांक __rtc_set_alarm(काष्ठा rtc_device *rtc, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rtc_समय पंचांग;
	समय64_t now, scheduled;
	पूर्णांक err;

	err = rtc_valid_पंचांग(&alarm->समय);
	अगर (err)
		वापस err;

	scheduled = rtc_पंचांग_to_समय64(&alarm->समय);

	/* Make sure we're not setting alarms in the past */
	err = __rtc_पढ़ो_समय(rtc, &पंचांग);
	अगर (err)
		वापस err;
	now = rtc_पंचांग_to_समय64(&पंचांग);
	अगर (scheduled <= now)
		वापस -ETIME;
	/*
	 * XXX - We just checked to make sure the alarm समय is not
	 * in the past, but there is still a race winकरोw where अगर
	 * the is alarm set क्रम the next second and the second ticks
	 * over right here, beक्रमe we set the alarm.
	 */

	rtc_subtract_offset(rtc, &alarm->समय);

	अगर (!rtc->ops)
		err = -ENODEV;
	अन्यथा अगर (!test_bit(RTC_FEATURE_ALARM, rtc->features))
		err = -EINVAL;
	अन्यथा
		err = rtc->ops->set_alarm(rtc->dev.parent, alarm);

	trace_rtc_set_alarm(rtc_पंचांग_to_समय64(&alarm->समय), err);
	वापस err;
पूर्ण

पूर्णांक rtc_set_alarm(काष्ठा rtc_device *rtc, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक err;

	अगर (!rtc->ops)
		वापस -ENODEV;
	अन्यथा अगर (!test_bit(RTC_FEATURE_ALARM, rtc->features))
		वापस -EINVAL;

	err = rtc_valid_पंचांग(&alarm->समय);
	अगर (err != 0)
		वापस err;

	err = rtc_valid_range(rtc, &alarm->समय);
	अगर (err)
		वापस err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;
	अगर (rtc->aie_समयr.enabled)
		rtc_समयr_हटाओ(rtc, &rtc->aie_समयr);

	rtc->aie_समयr.node.expires = rtc_पंचांग_to_kसमय(alarm->समय);
	rtc->aie_समयr.period = 0;
	अगर (alarm->enabled)
		err = rtc_समयr_enqueue(rtc, &rtc->aie_समयr);

	mutex_unlock(&rtc->ops_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_set_alarm);

/* Called once per device from rtc_device_रेजिस्टर */
पूर्णांक rtc_initialize_alarm(काष्ठा rtc_device *rtc, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक err;
	काष्ठा rtc_समय now;

	err = rtc_valid_पंचांग(&alarm->समय);
	अगर (err != 0)
		वापस err;

	err = rtc_पढ़ो_समय(rtc, &now);
	अगर (err)
		वापस err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

	rtc->aie_समयr.node.expires = rtc_पंचांग_to_kसमय(alarm->समय);
	rtc->aie_समयr.period = 0;

	/* Alarm has to be enabled & in the future क्रम us to enqueue it */
	अगर (alarm->enabled && (rtc_पंचांग_to_kसमय(now) <
			 rtc->aie_समयr.node.expires)) अणु
		rtc->aie_समयr.enabled = 1;
		समयrqueue_add(&rtc->समयrqueue, &rtc->aie_समयr.node);
		trace_rtc_समयr_enqueue(&rtc->aie_समयr);
	पूर्ण
	mutex_unlock(&rtc->ops_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_initialize_alarm);

पूर्णांक rtc_alarm_irq_enable(काष्ठा rtc_device *rtc, अचिन्हित पूर्णांक enabled)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

	अगर (rtc->aie_समयr.enabled != enabled) अणु
		अगर (enabled)
			err = rtc_समयr_enqueue(rtc, &rtc->aie_समयr);
		अन्यथा
			rtc_समयr_हटाओ(rtc, &rtc->aie_समयr);
	पूर्ण

	अगर (err)
		/* nothing */;
	अन्यथा अगर (!rtc->ops)
		err = -ENODEV;
	अन्यथा अगर (!test_bit(RTC_FEATURE_ALARM, rtc->features) || !rtc->ops->alarm_irq_enable)
		err = -EINVAL;
	अन्यथा
		err = rtc->ops->alarm_irq_enable(rtc->dev.parent, enabled);

	mutex_unlock(&rtc->ops_lock);

	trace_rtc_alarm_irq_enable(enabled, err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_alarm_irq_enable);

पूर्णांक rtc_update_irq_enable(काष्ठा rtc_device *rtc, अचिन्हित पूर्णांक enabled)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

#अगर_घोषित CONFIG_RTC_INTF_DEV_UIE_EMUL
	अगर (enabled == 0 && rtc->uie_irq_active) अणु
		mutex_unlock(&rtc->ops_lock);
		वापस rtc_dev_update_irq_enable_emul(rtc, 0);
	पूर्ण
#पूर्ण_अगर
	/* make sure we're changing state */
	अगर (rtc->uie_rtस_समयr.enabled == enabled)
		जाओ out;

	अगर (rtc->uie_unsupported || !test_bit(RTC_FEATURE_ALARM, rtc->features)) अणु
		mutex_unlock(&rtc->ops_lock);
#अगर_घोषित CONFIG_RTC_INTF_DEV_UIE_EMUL
		वापस rtc_dev_update_irq_enable_emul(rtc, enabled);
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण

	अगर (enabled) अणु
		काष्ठा rtc_समय पंचांग;
		kसमय_प्रकार now, onesec;

		err = __rtc_पढ़ो_समय(rtc, &पंचांग);
		अगर (err)
			जाओ out;
		onesec = kसमय_set(1, 0);
		now = rtc_पंचांग_to_kसमय(पंचांग);
		rtc->uie_rtस_समयr.node.expires = kसमय_add(now, onesec);
		rtc->uie_rtस_समयr.period = kसमय_set(1, 0);
		err = rtc_समयr_enqueue(rtc, &rtc->uie_rtस_समयr);
	पूर्ण अन्यथा अणु
		rtc_समयr_हटाओ(rtc, &rtc->uie_rtस_समयr);
	पूर्ण

out:
	mutex_unlock(&rtc->ops_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_update_irq_enable);

/**
 * rtc_handle_legacy_irq - AIE, UIE and PIE event hook
 * @rtc: poपूर्णांकer to the rtc device
 * @num: number of occurence of the event
 * @mode: type of the event, RTC_AF, RTC_UF of RTC_PF
 *
 * This function is called when an AIE, UIE or PIE mode पूर्णांकerrupt
 * has occurred (or been emulated).
 *
 */
व्योम rtc_handle_legacy_irq(काष्ठा rtc_device *rtc, पूर्णांक num, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	/* mark one irq of the appropriate mode */
	spin_lock_irqsave(&rtc->irq_lock, flags);
	rtc->irq_data = (rtc->irq_data + (num << 8)) | (RTC_IRQF | mode);
	spin_unlock_irqrestore(&rtc->irq_lock, flags);

	wake_up_पूर्णांकerruptible(&rtc->irq_queue);
	समाप्त_fasync(&rtc->async_queue, SIGIO, POLL_IN);
पूर्ण

/**
 * rtc_aie_update_irq - AIE mode rtस_समयr hook
 * @rtc: poपूर्णांकer to the rtc_device
 *
 * This functions is called when the aie_समयr expires.
 */
व्योम rtc_aie_update_irq(काष्ठा rtc_device *rtc)
अणु
	rtc_handle_legacy_irq(rtc, 1, RTC_AF);
पूर्ण

/**
 * rtc_uie_update_irq - UIE mode rtस_समयr hook
 * @rtc: poपूर्णांकer to the rtc_device
 *
 * This functions is called when the uie_समयr expires.
 */
व्योम rtc_uie_update_irq(काष्ठा rtc_device *rtc)
अणु
	rtc_handle_legacy_irq(rtc, 1,  RTC_UF);
पूर्ण

/**
 * rtc_pie_update_irq - PIE mode hrसमयr hook
 * @समयr: poपूर्णांकer to the pie mode hrसमयr
 *
 * This function is used to emulate PIE mode पूर्णांकerrupts
 * using an hrसमयr. This function is called when the periodic
 * hrसमयr expires.
 */
क्रमागत hrसमयr_restart rtc_pie_update_irq(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा rtc_device *rtc;
	kसमय_प्रकार period;
	u64 count;

	rtc = container_of(समयr, काष्ठा rtc_device, pie_समयr);

	period = NSEC_PER_SEC / rtc->irq_freq;
	count = hrसमयr_क्रमward_now(समयr, period);

	rtc_handle_legacy_irq(rtc, count, RTC_PF);

	वापस HRTIMER_RESTART;
पूर्ण

/**
 * rtc_update_irq - Triggered when a RTC पूर्णांकerrupt occurs.
 * @rtc: the rtc device
 * @num: how many irqs are being reported (usually one)
 * @events: mask of RTC_IRQF with one or more of RTC_PF, RTC_AF, RTC_UF
 * Context: any
 */
व्योम rtc_update_irq(काष्ठा rtc_device *rtc,
		    अचिन्हित दीर्घ num, अचिन्हित दीर्घ events)
अणु
	अगर (IS_ERR_OR_शून्य(rtc))
		वापस;

	pm_stay_awake(rtc->dev.parent);
	schedule_work(&rtc->irqwork);
पूर्ण
EXPORT_SYMBOL_GPL(rtc_update_irq);

काष्ठा rtc_device *rtc_class_खोलो(स्थिर अक्षर *name)
अणु
	काष्ठा device *dev;
	काष्ठा rtc_device *rtc = शून्य;

	dev = class_find_device_by_name(rtc_class, name);
	अगर (dev)
		rtc = to_rtc_device(dev);

	अगर (rtc) अणु
		अगर (!try_module_get(rtc->owner)) अणु
			put_device(dev);
			rtc = शून्य;
		पूर्ण
	पूर्ण

	वापस rtc;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_class_खोलो);

व्योम rtc_class_बंद(काष्ठा rtc_device *rtc)
अणु
	module_put(rtc->owner);
	put_device(&rtc->dev);
पूर्ण
EXPORT_SYMBOL_GPL(rtc_class_बंद);

अटल पूर्णांक rtc_update_hrसमयr(काष्ठा rtc_device *rtc, पूर्णांक enabled)
अणु
	/*
	 * We always cancel the समयr here first, because otherwise
	 * we could run पूर्णांकo BUG_ON(समयr->state != HRTIMER_STATE_CALLBACK);
	 * when we manage to start the समयr beक्रमe the callback
	 * वापसs HRTIMER_RESTART.
	 *
	 * We cannot use hrसमयr_cancel() here as a running callback
	 * could be blocked on rtc->irq_task_lock and hrसमयr_cancel()
	 * would spin क्रमever.
	 */
	अगर (hrसमयr_try_to_cancel(&rtc->pie_समयr) < 0)
		वापस -1;

	अगर (enabled) अणु
		kसमय_प्रकार period = NSEC_PER_SEC / rtc->irq_freq;

		hrसमयr_start(&rtc->pie_समयr, period, HRTIMER_MODE_REL);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * rtc_irq_set_state - enable/disable 2^N Hz periodic IRQs
 * @rtc: the rtc device
 * @enabled: true to enable periodic IRQs
 * Context: any
 *
 * Note that rtc_irq_set_freq() should previously have been used to
 * specअगरy the desired frequency of periodic IRQ.
 */
पूर्णांक rtc_irq_set_state(काष्ठा rtc_device *rtc, पूर्णांक enabled)
अणु
	पूर्णांक err = 0;

	जबतक (rtc_update_hrसमयr(rtc, enabled) < 0)
		cpu_relax();

	rtc->pie_enabled = enabled;

	trace_rtc_irq_set_state(enabled, err);
	वापस err;
पूर्ण

/**
 * rtc_irq_set_freq - set 2^N Hz periodic IRQ frequency क्रम IRQ
 * @rtc: the rtc device
 * @freq: positive frequency
 * Context: any
 *
 * Note that rtc_irq_set_state() is used to enable or disable the
 * periodic IRQs.
 */
पूर्णांक rtc_irq_set_freq(काष्ठा rtc_device *rtc, पूर्णांक freq)
अणु
	पूर्णांक err = 0;

	अगर (freq <= 0 || freq > RTC_MAX_FREQ)
		वापस -EINVAL;

	rtc->irq_freq = freq;
	जबतक (rtc->pie_enabled && rtc_update_hrसमयr(rtc, 1) < 0)
		cpu_relax();

	trace_rtc_irq_set_freq(freq, err);
	वापस err;
पूर्ण

/**
 * rtc_समयr_enqueue - Adds a rtc_समयr to the rtc_device समयrqueue
 * @rtc: rtc device
 * @समयr: समयr being added.
 *
 * Enqueues a समयr onto the rtc devices समयrqueue and sets
 * the next alarm event appropriately.
 *
 * Sets the enabled bit on the added समयr.
 *
 * Must hold ops_lock क्रम proper serialization of समयrqueue
 */
अटल पूर्णांक rtc_समयr_enqueue(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr)
अणु
	काष्ठा समयrqueue_node *next = समयrqueue_getnext(&rtc->समयrqueue);
	काष्ठा rtc_समय पंचांग;
	kसमय_प्रकार now;

	समयr->enabled = 1;
	__rtc_पढ़ो_समय(rtc, &पंचांग);
	now = rtc_पंचांग_to_kसमय(पंचांग);

	/* Skip over expired समयrs */
	जबतक (next) अणु
		अगर (next->expires >= now)
			अवरोध;
		next = समयrqueue_iterate_next(next);
	पूर्ण

	समयrqueue_add(&rtc->समयrqueue, &समयr->node);
	trace_rtc_समयr_enqueue(समयr);
	अगर (!next || kसमय_beक्रमe(समयr->node.expires, next->expires)) अणु
		काष्ठा rtc_wkalrm alarm;
		पूर्णांक err;

		alarm.समय = rtc_kसमय_प्रकारo_पंचांग(समयr->node.expires);
		alarm.enabled = 1;
		err = __rtc_set_alarm(rtc, &alarm);
		अगर (err == -ETIME) अणु
			pm_stay_awake(rtc->dev.parent);
			schedule_work(&rtc->irqwork);
		पूर्ण अन्यथा अगर (err) अणु
			समयrqueue_del(&rtc->समयrqueue, &समयr->node);
			trace_rtc_समयr_dequeue(समयr);
			समयr->enabled = 0;
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rtc_alarm_disable(काष्ठा rtc_device *rtc)
अणु
	अगर (!rtc->ops || !test_bit(RTC_FEATURE_ALARM, rtc->features) || !rtc->ops->alarm_irq_enable)
		वापस;

	rtc->ops->alarm_irq_enable(rtc->dev.parent, false);
	trace_rtc_alarm_irq_enable(0, 0);
पूर्ण

/**
 * rtc_समयr_हटाओ - Removes a rtc_समयr from the rtc_device समयrqueue
 * @rtc: rtc device
 * @समयr: समयr being हटाओd.
 *
 * Removes a समयr onto the rtc devices समयrqueue and sets
 * the next alarm event appropriately.
 *
 * Clears the enabled bit on the हटाओd समयr.
 *
 * Must hold ops_lock क्रम proper serialization of समयrqueue
 */
अटल व्योम rtc_समयr_हटाओ(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr)
अणु
	काष्ठा समयrqueue_node *next = समयrqueue_getnext(&rtc->समयrqueue);

	समयrqueue_del(&rtc->समयrqueue, &समयr->node);
	trace_rtc_समयr_dequeue(समयr);
	समयr->enabled = 0;
	अगर (next == &समयr->node) अणु
		काष्ठा rtc_wkalrm alarm;
		पूर्णांक err;

		next = समयrqueue_getnext(&rtc->समयrqueue);
		अगर (!next) अणु
			rtc_alarm_disable(rtc);
			वापस;
		पूर्ण
		alarm.समय = rtc_kसमय_प्रकारo_पंचांग(next->expires);
		alarm.enabled = 1;
		err = __rtc_set_alarm(rtc, &alarm);
		अगर (err == -ETIME) अणु
			pm_stay_awake(rtc->dev.parent);
			schedule_work(&rtc->irqwork);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * rtc_समयr_करो_work - Expires rtc समयrs
 * @work: work item
 *
 * Expires rtc समयrs. Reprograms next alarm event अगर needed.
 * Called via worktask.
 *
 * Serializes access to समयrqueue via ops_lock mutex
 */
व्योम rtc_समयr_करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtc_समयr *समयr;
	काष्ठा समयrqueue_node *next;
	kसमय_प्रकार now;
	काष्ठा rtc_समय पंचांग;

	काष्ठा rtc_device *rtc =
		container_of(work, काष्ठा rtc_device, irqwork);

	mutex_lock(&rtc->ops_lock);
again:
	__rtc_पढ़ो_समय(rtc, &पंचांग);
	now = rtc_पंचांग_to_kसमय(पंचांग);
	जबतक ((next = समयrqueue_getnext(&rtc->समयrqueue))) अणु
		अगर (next->expires > now)
			अवरोध;

		/* expire समयr */
		समयr = container_of(next, काष्ठा rtc_समयr, node);
		समयrqueue_del(&rtc->समयrqueue, &समयr->node);
		trace_rtc_समयr_dequeue(समयr);
		समयr->enabled = 0;
		अगर (समयr->func)
			समयr->func(समयr->rtc);

		trace_rtc_समयr_fired(समयr);
		/* Re-add/fwd periodic समयrs */
		अगर (kसमय_प्रकारo_ns(समयr->period)) अणु
			समयr->node.expires = kसमय_add(समयr->node.expires,
							समयr->period);
			समयr->enabled = 1;
			समयrqueue_add(&rtc->समयrqueue, &समयr->node);
			trace_rtc_समयr_enqueue(समयr);
		पूर्ण
	पूर्ण

	/* Set next alarm */
	अगर (next) अणु
		काष्ठा rtc_wkalrm alarm;
		पूर्णांक err;
		पूर्णांक retry = 3;

		alarm.समय = rtc_kसमय_प्रकारo_पंचांग(next->expires);
		alarm.enabled = 1;
reprogram:
		err = __rtc_set_alarm(rtc, &alarm);
		अगर (err == -ETIME) अणु
			जाओ again;
		पूर्ण अन्यथा अगर (err) अणु
			अगर (retry-- > 0)
				जाओ reprogram;

			समयr = container_of(next, काष्ठा rtc_समयr, node);
			समयrqueue_del(&rtc->समयrqueue, &समयr->node);
			trace_rtc_समयr_dequeue(समयr);
			समयr->enabled = 0;
			dev_err(&rtc->dev, "__rtc_set_alarm: err=%d\n", err);
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtc_alarm_disable(rtc);
	पूर्ण

	pm_relax(rtc->dev.parent);
	mutex_unlock(&rtc->ops_lock);
पूर्ण

/* rtc_समयr_init - Initializes an rtc_समयr
 * @समयr: समयr to be पूर्णांकiialized
 * @f: function poपूर्णांकer to be called when समयr fires
 * @rtc: poपूर्णांकer to the rtc_device
 *
 * Kernel पूर्णांकerface to initializing an rtc_समयr.
 */
व्योम rtc_समयr_init(काष्ठा rtc_समयr *समयr, व्योम (*f)(काष्ठा rtc_device *r),
		    काष्ठा rtc_device *rtc)
अणु
	समयrqueue_init(&समयr->node);
	समयr->enabled = 0;
	समयr->func = f;
	समयr->rtc = rtc;
पूर्ण

/* rtc_समयr_start - Sets an rtc_समयr to fire in the future
 * @ rtc: rtc device to be used
 * @ समयr: समयr being set
 * @ expires: समय at which to expire the समयr
 * @ period: period that the समयr will recur
 *
 * Kernel पूर्णांकerface to set an rtc_समयr
 */
पूर्णांक rtc_समयr_start(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr,
		    kसमय_प्रकार expires, kसमय_प्रकार period)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&rtc->ops_lock);
	अगर (समयr->enabled)
		rtc_समयr_हटाओ(rtc, समयr);

	समयr->node.expires = expires;
	समयr->period = period;

	ret = rtc_समयr_enqueue(rtc, समयr);

	mutex_unlock(&rtc->ops_lock);
	वापस ret;
पूर्ण

/* rtc_समयr_cancel - Stops an rtc_समयr
 * @ rtc: rtc device to be used
 * @ समयr: समयr being set
 *
 * Kernel पूर्णांकerface to cancel an rtc_समयr
 */
व्योम rtc_समयr_cancel(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr)
अणु
	mutex_lock(&rtc->ops_lock);
	अगर (समयr->enabled)
		rtc_समयr_हटाओ(rtc, समयr);
	mutex_unlock(&rtc->ops_lock);
पूर्ण

/**
 * rtc_पढ़ो_offset - Read the amount of rtc offset in parts per billion
 * @rtc: rtc device to be used
 * @offset: the offset in parts per billion
 *
 * see below क्रम details.
 *
 * Kernel पूर्णांकerface to पढ़ो rtc घड़ी offset
 * Returns 0 on success, or a negative number on error.
 * If पढ़ो_offset() is not implemented क्रम the rtc, वापस -EINVAL
 */
पूर्णांक rtc_पढ़ो_offset(काष्ठा rtc_device *rtc, दीर्घ *offset)
अणु
	पूर्णांक ret;

	अगर (!rtc->ops)
		वापस -ENODEV;

	अगर (!rtc->ops->पढ़ो_offset)
		वापस -EINVAL;

	mutex_lock(&rtc->ops_lock);
	ret = rtc->ops->पढ़ो_offset(rtc->dev.parent, offset);
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_पढ़ो_offset(*offset, ret);
	वापस ret;
पूर्ण

/**
 * rtc_set_offset - Adjusts the duration of the average second
 * @rtc: rtc device to be used
 * @offset: the offset in parts per billion
 *
 * Some rtc's allow an adjusपंचांगent to the average duration of a second
 * to compensate क्रम dअगरferences in the actual घड़ी rate due to temperature,
 * the crystal, capacitor, etc.
 *
 * The adjusपंचांगent applied is as follows:
 *   t = t0 * (1 + offset * 1e-9)
 * where t0 is the measured length of 1 RTC second with offset = 0
 *
 * Kernel पूर्णांकerface to adjust an rtc घड़ी offset.
 * Return 0 on success, or a negative number on error.
 * If the rtc offset is not setable (or not implemented), वापस -EINVAL
 */
पूर्णांक rtc_set_offset(काष्ठा rtc_device *rtc, दीर्घ offset)
अणु
	पूर्णांक ret;

	अगर (!rtc->ops)
		वापस -ENODEV;

	अगर (!rtc->ops->set_offset)
		वापस -EINVAL;

	mutex_lock(&rtc->ops_lock);
	ret = rtc->ops->set_offset(rtc->dev.parent, offset);
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_set_offset(offset, ret);
	वापस ret;
पूर्ण
