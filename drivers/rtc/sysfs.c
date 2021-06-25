<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC subप्रणाली, sysfs पूर्णांकerface
 *
 * Copyright (C) 2005 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>

#समावेश "rtc-core.h"

/* device attributes */

/*
 * NOTE:  RTC बार displayed in sysfs use the RTC's timezone.  That's
 * ideally UTC.  However, PCs that also boot to MS-Winकरोws normally use
 * the local समय and change to match daylight savings समय.  That affects
 * attributes including date, समय, since_epoch, and wakealarm.
 */

अटल sमाप_प्रकार
name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s %s\n", dev_driver_string(dev->parent),
		       dev_name(dev->parent));
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार
date_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार retval;
	काष्ठा rtc_समय पंचांग;

	retval = rtc_पढ़ो_समय(to_rtc_device(dev), &पंचांग);
	अगर (retval)
		वापस retval;

	वापस प्र_लिखो(buf, "%ptRd\n", &पंचांग);
पूर्ण
अटल DEVICE_ATTR_RO(date);

अटल sमाप_प्रकार
समय_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार retval;
	काष्ठा rtc_समय पंचांग;

	retval = rtc_पढ़ो_समय(to_rtc_device(dev), &पंचांग);
	अगर (retval)
		वापस retval;

	वापस प्र_लिखो(buf, "%ptRt\n", &पंचांग);
पूर्ण
अटल DEVICE_ATTR_RO(समय);

अटल sमाप_प्रकार
since_epoch_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार retval;
	काष्ठा rtc_समय पंचांग;

	retval = rtc_पढ़ो_समय(to_rtc_device(dev), &पंचांग);
	अगर (retval == 0) अणु
		समय64_t समय;

		समय = rtc_पंचांग_to_समय64(&पंचांग);
		retval = प्र_लिखो(buf, "%lld\n", समय);
	पूर्ण

	वापस retval;
पूर्ण
अटल DEVICE_ATTR_RO(since_epoch);

अटल sमाप_प्रकार
max_user_freq_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", to_rtc_device(dev)->max_user_freq);
पूर्ण

अटल sमाप_प्रकार
max_user_freq_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा rtc_device *rtc = to_rtc_device(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 0, &val);
	अगर (err)
		वापस err;

	अगर (val >= 4096 || val == 0)
		वापस -EINVAL;

	rtc->max_user_freq = (पूर्णांक)val;

	वापस n;
पूर्ण
अटल DEVICE_ATTR_RW(max_user_freq);

/**
 * rtc_sysfs_show_hctosys - indicate अगर the given RTC set the प्रणाली समय
 * @dev: The device that the attribute beदीर्घs to.
 * @attr: The attribute being पढ़ो.
 * @buf: The result buffer.
 *
 * buf is "1" अगर the प्रणाली घड़ी was set by this RTC at the last
 * boot or resume event.
 */
अटल sमाप_प्रकार
hctosys_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
#अगर_घोषित CONFIG_RTC_HCTOSYS_DEVICE
	अगर (rtc_hctosys_ret == 0 &&
	    म_भेद(dev_name(&to_rtc_device(dev)->dev),
		   CONFIG_RTC_HCTOSYS_DEVICE) == 0)
		वापस प्र_लिखो(buf, "1\n");
#पूर्ण_अगर
	वापस प्र_लिखो(buf, "0\n");
पूर्ण
अटल DEVICE_ATTR_RO(hctosys);

अटल sमाप_प्रकार
wakealarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार retval;
	समय64_t alarm;
	काष्ठा rtc_wkalrm alm;

	/* Don't show disabled alarms.  For unअगरormity, RTC alarms are
	 * conceptually one-shot, even though some common RTCs (on PCs)
	 * करोn't actually work that way.
	 *
	 * NOTE: RTC implementations where the alarm करोesn't match an
	 * exact YYYY-MM-DD HH:MM[:SS] date *must* disable their RTC
	 * alarms after they trigger, to ensure one-shot semantics.
	 */
	retval = rtc_पढ़ो_alarm(to_rtc_device(dev), &alm);
	अगर (retval == 0 && alm.enabled) अणु
		alarm = rtc_पंचांग_to_समय64(&alm.समय);
		retval = प्र_लिखो(buf, "%lld\n", alarm);
	पूर्ण

	वापस retval;
पूर्ण

अटल sमाप_प्रकार
wakealarm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	sमाप_प्रकार retval;
	समय64_t now, alarm;
	समय64_t push = 0;
	काष्ठा rtc_wkalrm alm;
	काष्ठा rtc_device *rtc = to_rtc_device(dev);
	स्थिर अक्षर *buf_ptr;
	पूर्णांक adjust = 0;

	/* Only request alarms that trigger in the future.  Disable them
	 * by writing another समय, e.g. 0 meaning Jan 1 1970 UTC.
	 */
	retval = rtc_पढ़ो_समय(rtc, &alm.समय);
	अगर (retval < 0)
		वापस retval;
	now = rtc_पंचांग_to_समय64(&alm.समय);

	buf_ptr = buf;
	अगर (*buf_ptr == '+') अणु
		buf_ptr++;
		अगर (*buf_ptr == '=') अणु
			buf_ptr++;
			push = 1;
		पूर्ण अन्यथा अणु
			adjust = 1;
		पूर्ण
	पूर्ण
	retval = kstrtos64(buf_ptr, 0, &alarm);
	अगर (retval)
		वापस retval;
	अगर (adjust)
		alarm += now;
	अगर (alarm > now || push) अणु
		/* Aव्योम accidentally clobbering active alarms; we can't
		 * entirely prevent that here, without even the minimal
		 * locking from the /dev/rtcN api.
		 */
		retval = rtc_पढ़ो_alarm(rtc, &alm);
		अगर (retval < 0)
			वापस retval;
		अगर (alm.enabled) अणु
			अगर (push) अणु
				push = rtc_पंचांग_to_समय64(&alm.समय);
				alarm += push;
			पूर्ण अन्यथा
				वापस -EBUSY;
		पूर्ण अन्यथा अगर (push)
			वापस -EINVAL;
		alm.enabled = 1;
	पूर्ण अन्यथा अणु
		alm.enabled = 0;

		/* Provide a valid future alarm समय.  Linux isn't EFI,
		 * this समय won't be ignored when disabling the alarm.
		 */
		alarm = now + 300;
	पूर्ण
	rtc_समय64_to_पंचांग(alarm, &alm.समय);

	retval = rtc_set_alarm(rtc, &alm);
	वापस (retval < 0) ? retval : n;
पूर्ण
अटल DEVICE_ATTR_RW(wakealarm);

अटल sमाप_प्रकार
offset_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार retval;
	दीर्घ offset;

	retval = rtc_पढ़ो_offset(to_rtc_device(dev), &offset);
	अगर (retval == 0)
		retval = प्र_लिखो(buf, "%ld\n", offset);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार
offset_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	     स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	sमाप_प्रकार retval;
	दीर्घ offset;

	retval = kम_से_दीर्घ(buf, 10, &offset);
	अगर (retval == 0)
		retval = rtc_set_offset(to_rtc_device(dev), offset);

	वापस (retval < 0) ? retval : n;
पूर्ण
अटल DEVICE_ATTR_RW(offset);

अटल sमाप_प्रकार
range_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "[%lld,%llu]\n", to_rtc_device(dev)->range_min,
		       to_rtc_device(dev)->range_max);
पूर्ण
अटल DEVICE_ATTR_RO(range);

अटल काष्ठा attribute *rtc_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_date.attr,
	&dev_attr_समय.attr,
	&dev_attr_since_epoch.attr,
	&dev_attr_max_user_freq.attr,
	&dev_attr_hctosys.attr,
	&dev_attr_wakealarm.attr,
	&dev_attr_offset.attr,
	&dev_attr_range.attr,
	शून्य,
पूर्ण;

/* The reason to trigger an alarm with no process watching it (via sysfs)
 * is its side effect:  waking from a प्रणाली state like suspend-to-RAM or
 * suspend-to-disk.  So: no attribute unless that side effect is possible.
 * (Userspace may disable that mechanism later.)
 */
अटल bool rtc_करोes_wakealarm(काष्ठा rtc_device *rtc)
अणु
	अगर (!device_can_wakeup(rtc->dev.parent))
		वापस false;

	वापस !!test_bit(RTC_FEATURE_ALARM, rtc->features);
पूर्ण

अटल umode_t rtc_attr_is_visible(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा rtc_device *rtc = to_rtc_device(dev);
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_wakealarm.attr) अणु
		अगर (!rtc_करोes_wakealarm(rtc))
			mode = 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_offset.attr) अणु
		अगर (!rtc->ops->set_offset)
			mode = 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_range.attr) अणु
		अगर (!(rtc->range_max - rtc->range_min))
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल काष्ठा attribute_group rtc_attr_group = अणु
	.is_visible	= rtc_attr_is_visible,
	.attrs		= rtc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *rtc_attr_groups[] = अणु
	&rtc_attr_group,
	शून्य
पूर्ण;

स्थिर काष्ठा attribute_group **rtc_get_dev_attribute_groups(व्योम)
अणु
	वापस rtc_attr_groups;
पूर्ण

पूर्णांक rtc_add_groups(काष्ठा rtc_device *rtc, स्थिर काष्ठा attribute_group **grps)
अणु
	माप_प्रकार old_cnt = 0, add_cnt = 0, new_cnt;
	स्थिर काष्ठा attribute_group **groups, **old;

	अगर (!grps)
		वापस -EINVAL;

	groups = rtc->dev.groups;
	अगर (groups)
		क्रम (; *groups; groups++)
			old_cnt++;

	क्रम (groups = grps; *groups; groups++)
		add_cnt++;

	new_cnt = old_cnt + add_cnt + 1;
	groups = devm_kसुस्मृति(&rtc->dev, new_cnt, माप(*groups), GFP_KERNEL);
	अगर (!groups)
		वापस -ENOMEM;
	स_नकल(groups, rtc->dev.groups, old_cnt * माप(*groups));
	स_नकल(groups + old_cnt, grps, add_cnt * माप(*groups));
	groups[old_cnt + add_cnt] = शून्य;

	old = rtc->dev.groups;
	rtc->dev.groups = groups;
	अगर (old && old != rtc_attr_groups)
		devm_kमुक्त(&rtc->dev, old);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtc_add_groups);

पूर्णांक rtc_add_group(काष्ठा rtc_device *rtc, स्थिर काष्ठा attribute_group *grp)
अणु
	स्थिर काष्ठा attribute_group *groups[] = अणु grp, शून्य पूर्ण;

	वापस rtc_add_groups(rtc, groups);
पूर्ण
EXPORT_SYMBOL(rtc_add_group);
