<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACPI Time and Alarm (TAD) Device Driver
 *
 * Copyright (C) 2018 Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * This driver is based on Section 9.18 of the ACPI 6.2 specअगरication revision.
 *
 * It only supports the प्रणाली wakeup capabilities of the TAD.
 *
 * Provided are sysfs attributes, available under the TAD platक्रमm device,
 * allowing user space to manage the AC and DC wakeup समयrs of the TAD:
 * set and पढ़ो their values, set and check their expire समयr wake policies,
 * check and clear their status and check the capabilities of the TAD reported
 * by AML.  The DC समयr attributes are only present अगर the TAD supports a
 * separate DC alarm समयr.
 *
 * The wakeup events handling and घातer management of the TAD is expected to
 * be taken care of by the ACPI PM करोमुख्य attached to its platक्रमm device.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/suspend.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Rafael J. Wysocki");

/* ACPI TAD capability flags (ACPI 6.2, Section 9.18.2) */
#घोषणा ACPI_TAD_AC_WAKE	BIT(0)
#घोषणा ACPI_TAD_DC_WAKE	BIT(1)
#घोषणा ACPI_TAD_RT		BIT(2)
#घोषणा ACPI_TAD_RT_IN_MS	BIT(3)
#घोषणा ACPI_TAD_S4_S5__GWS	BIT(4)
#घोषणा ACPI_TAD_AC_S4_WAKE	BIT(5)
#घोषणा ACPI_TAD_AC_S5_WAKE	BIT(6)
#घोषणा ACPI_TAD_DC_S4_WAKE	BIT(7)
#घोषणा ACPI_TAD_DC_S5_WAKE	BIT(8)

/* ACPI TAD alarm समयr selection */
#घोषणा ACPI_TAD_AC_TIMER	(u32)0
#घोषणा ACPI_TAD_DC_TIMER	(u32)1

/* Special value क्रम disabled समयr or expired समयr wake policy. */
#घोषणा ACPI_TAD_WAKE_DISABLED	(~(u32)0)

काष्ठा acpi_tad_driver_data अणु
	u32 capabilities;
पूर्ण;

काष्ठा acpi_tad_rt अणु
	u16 year;  /* 1900 - 9999 */
	u8 month;  /* 1 - 12 */
	u8 day;    /* 1 - 31 */
	u8 hour;   /* 0 - 23 */
	u8 minute; /* 0 - 59 */
	u8 second; /* 0 - 59 */
	u8 valid;  /* 0 (failed) or 1 (success) क्रम पढ़ोs, 0 क्रम ग_लिखोs */
	u16 msec;  /* 1 - 1000 */
	s16 tz;    /* -1440 to 1440 or 2047 (unspecअगरied) */
	u8 daylight;
	u8 padding[3]; /* must be 0 */
पूर्ण __packed;

अटल पूर्णांक acpi_tad_set_real_समय(काष्ठा device *dev, काष्ठा acpi_tad_rt *rt)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object args[] = अणु
		अणु .type = ACPI_TYPE_BUFFER, पूर्ण,
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु
		.poपूर्णांकer = args,
		.count = ARRAY_SIZE(args),
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ retval;
	acpi_status status;

	अगर (rt->year < 1900 || rt->year > 9999 ||
	    rt->month < 1 || rt->month > 12 ||
	    rt->hour > 23 || rt->minute > 59 || rt->second > 59 ||
	    rt->tz < -1440 || (rt->tz > 1440 && rt->tz != 2047) ||
	    rt->daylight > 3)
		वापस -दुस्फल;

	args[0].buffer.poपूर्णांकer = (u8 *)rt;
	args[0].buffer.length = माप(*rt);

	pm_runसमय_get_sync(dev);

	status = acpi_evaluate_पूर्णांकeger(handle, "_SRT", &arg_list, &retval);

	pm_runसमय_put_sync(dev);

	अगर (ACPI_FAILURE(status) || retval)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_tad_get_real_समय(काष्ठा device *dev, काष्ठा acpi_tad_rt *rt)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	जोड़ acpi_object *out_obj;
	काष्ठा acpi_tad_rt *data;
	acpi_status status;
	पूर्णांक ret = -EIO;

	pm_runसमय_get_sync(dev);

	status = acpi_evaluate_object(handle, "_GRT", शून्य, &output);

	pm_runसमय_put_sync(dev);

	अगर (ACPI_FAILURE(status))
		जाओ out_मुक्त;

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER)
		जाओ out_मुक्त;

	अगर (out_obj->buffer.length != माप(*rt))
		जाओ out_मुक्त;

	data = (काष्ठा acpi_tad_rt *)(out_obj->buffer.poपूर्णांकer);
	अगर (!data->valid)
		जाओ out_मुक्त;

	स_नकल(rt, data, माप(*rt));
	ret = 0;

out_मुक्त:
	ACPI_FREE(output.poपूर्णांकer);
	वापस ret;
पूर्ण

अटल अक्षर *acpi_tad_rt_next_field(अक्षर *s, पूर्णांक *val)
अणु
	अक्षर *p;

	p = म_अक्षर(s, ':');
	अगर (!p)
		वापस शून्य;

	*p = '\0';
	अगर (kstrtoपूर्णांक(s, 10, val))
		वापस शून्य;

	वापस p + 1;
पूर्ण

अटल sमाप_प्रकार समय_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_tad_rt rt;
	अक्षर *str, *s;
	पूर्णांक val, ret = -ENODATA;

	str = kmemdup_nul(buf, count, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	s = acpi_tad_rt_next_field(str, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.year = val;

	s = acpi_tad_rt_next_field(s, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.month = val;

	s = acpi_tad_rt_next_field(s, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.day = val;

	s = acpi_tad_rt_next_field(s, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.hour = val;

	s = acpi_tad_rt_next_field(s, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.minute = val;

	s = acpi_tad_rt_next_field(s, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.second = val;

	s = acpi_tad_rt_next_field(s, &val);
	अगर (!s)
		जाओ out_मुक्त;

	rt.tz = val;

	अगर (kstrtoपूर्णांक(s, 10, &val))
		जाओ out_मुक्त;

	rt.daylight = val;

	rt.valid = 0;
	rt.msec = 0;
	स_रखो(rt.padding, 0, 3);

	ret = acpi_tad_set_real_समय(dev, &rt);

out_मुक्त:
	kमुक्त(str);
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार समय_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा acpi_tad_rt rt;
	पूर्णांक ret;

	ret = acpi_tad_get_real_समय(dev, &rt);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u:%u:%u:%u:%u:%u:%d:%u\n",
		       rt.year, rt.month, rt.day, rt.hour, rt.minute, rt.second,
		       rt.tz, rt.daylight);
पूर्ण

अटल DEVICE_ATTR_RW(समय);

अटल काष्ठा attribute *acpi_tad_समय_attrs[] = अणु
	&dev_attr_समय.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group acpi_tad_समय_attr_group = अणु
	.attrs	= acpi_tad_समय_attrs,
पूर्ण;

अटल पूर्णांक acpi_tad_wake_set(काष्ठा device *dev, अक्षर *method, u32 समयr_id,
			     u32 value)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object args[] = अणु
		अणु .type = ACPI_TYPE_INTEGER, पूर्ण,
		अणु .type = ACPI_TYPE_INTEGER, पूर्ण,
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु
		.poपूर्णांकer = args,
		.count = ARRAY_SIZE(args),
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ retval;
	acpi_status status;

	args[0].पूर्णांकeger.value = समयr_id;
	args[1].पूर्णांकeger.value = value;

	pm_runसमय_get_sync(dev);

	status = acpi_evaluate_पूर्णांकeger(handle, method, &arg_list, &retval);

	pm_runसमय_put_sync(dev);

	अगर (ACPI_FAILURE(status) || retval)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_tad_wake_ग_लिखो(काष्ठा device *dev, स्थिर अक्षर *buf, अक्षर *method,
			       u32 समयr_id, स्थिर अक्षर *specval)
अणु
	u32 value;

	अगर (sysfs_streq(buf, specval)) अणु
		value = ACPI_TAD_WAKE_DISABLED;
	पूर्ण अन्यथा अणु
		पूर्णांक ret = kstrtou32(buf, 0, &value);

		अगर (ret)
			वापस ret;

		अगर (value == ACPI_TAD_WAKE_DISABLED)
			वापस -EINVAL;
	पूर्ण

	वापस acpi_tad_wake_set(dev, method, समयr_id, value);
पूर्ण

अटल sमाप_प्रकार acpi_tad_wake_पढ़ो(काष्ठा device *dev, अक्षर *buf, अक्षर *method,
				  u32 समयr_id, स्थिर अक्षर *specval)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object args[] = अणु
		अणु .type = ACPI_TYPE_INTEGER, पूर्ण,
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु
		.poपूर्णांकer = args,
		.count = ARRAY_SIZE(args),
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ retval;
	acpi_status status;

	args[0].पूर्णांकeger.value = समयr_id;

	pm_runसमय_get_sync(dev);

	status = acpi_evaluate_पूर्णांकeger(handle, method, &arg_list, &retval);

	pm_runसमय_put_sync(dev);

	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	अगर ((u32)retval == ACPI_TAD_WAKE_DISABLED)
		वापस प्र_लिखो(buf, "%s\n", specval);

	वापस प्र_लिखो(buf, "%u\n", (u32)retval);
पूर्ण

अटल स्थिर अक्षर *alarm_specval = "disabled";

अटल पूर्णांक acpi_tad_alarm_ग_लिखो(काष्ठा device *dev, स्थिर अक्षर *buf,
				u32 समयr_id)
अणु
	वापस acpi_tad_wake_ग_लिखो(dev, buf, "_STV", समयr_id, alarm_specval);
पूर्ण

अटल sमाप_प्रकार acpi_tad_alarm_पढ़ो(काष्ठा device *dev, अक्षर *buf, u32 समयr_id)
अणु
	वापस acpi_tad_wake_पढ़ो(dev, buf, "_TIV", समयr_id, alarm_specval);
पूर्ण

अटल स्थिर अक्षर *policy_specval = "never";

अटल पूर्णांक acpi_tad_policy_ग_लिखो(काष्ठा device *dev, स्थिर अक्षर *buf,
				 u32 समयr_id)
अणु
	वापस acpi_tad_wake_ग_लिखो(dev, buf, "_STP", समयr_id, policy_specval);
पूर्ण

अटल sमाप_प्रकार acpi_tad_policy_पढ़ो(काष्ठा device *dev, अक्षर *buf, u32 समयr_id)
अणु
	वापस acpi_tad_wake_पढ़ो(dev, buf, "_TIP", समयr_id, policy_specval);
पूर्ण

अटल पूर्णांक acpi_tad_clear_status(काष्ठा device *dev, u32 समयr_id)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object args[] = अणु
		अणु .type = ACPI_TYPE_INTEGER, पूर्ण,
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु
		.poपूर्णांकer = args,
		.count = ARRAY_SIZE(args),
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ retval;
	acpi_status status;

	args[0].पूर्णांकeger.value = समयr_id;

	pm_runसमय_get_sync(dev);

	status = acpi_evaluate_पूर्णांकeger(handle, "_CWS", &arg_list, &retval);

	pm_runसमय_put_sync(dev);

	अगर (ACPI_FAILURE(status) || retval)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_tad_status_ग_लिखो(काष्ठा device *dev, स्थिर अक्षर *buf, u32 समयr_id)
अणु
	पूर्णांक ret, value;

	ret = kstrtoपूर्णांक(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value)
		वापस -EINVAL;

	वापस acpi_tad_clear_status(dev, समयr_id);
पूर्ण

अटल sमाप_प्रकार acpi_tad_status_पढ़ो(काष्ठा device *dev, अक्षर *buf, u32 समयr_id)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object args[] = अणु
		अणु .type = ACPI_TYPE_INTEGER, पूर्ण,
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु
		.poपूर्णांकer = args,
		.count = ARRAY_SIZE(args),
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ retval;
	acpi_status status;

	args[0].पूर्णांकeger.value = समयr_id;

	pm_runसमय_get_sync(dev);

	status = acpi_evaluate_पूर्णांकeger(handle, "_GWS", &arg_list, &retval);

	pm_runसमय_put_sync(dev);

	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस प्र_लिखो(buf, "0x%02X\n", (u32)retval);
पूर्ण

अटल sमाप_प्रकार caps_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा acpi_tad_driver_data *dd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%02X\n", dd->capabilities);
पूर्ण

अटल DEVICE_ATTR_RO(caps);

अटल sमाप_प्रकार ac_alarm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = acpi_tad_alarm_ग_लिखो(dev, buf, ACPI_TAD_AC_TIMER);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार ac_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस acpi_tad_alarm_पढ़ो(dev, buf, ACPI_TAD_AC_TIMER);
पूर्ण

अटल DEVICE_ATTR_RW(ac_alarm);

अटल sमाप_प्रकार ac_policy_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = acpi_tad_policy_ग_लिखो(dev, buf, ACPI_TAD_AC_TIMER);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार ac_policy_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस acpi_tad_policy_पढ़ो(dev, buf, ACPI_TAD_AC_TIMER);
पूर्ण

अटल DEVICE_ATTR_RW(ac_policy);

अटल sमाप_प्रकार ac_status_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = acpi_tad_status_ग_लिखो(dev, buf, ACPI_TAD_AC_TIMER);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार ac_status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस acpi_tad_status_पढ़ो(dev, buf, ACPI_TAD_AC_TIMER);
पूर्ण

अटल DEVICE_ATTR_RW(ac_status);

अटल काष्ठा attribute *acpi_tad_attrs[] = अणु
	&dev_attr_caps.attr,
	&dev_attr_ac_alarm.attr,
	&dev_attr_ac_policy.attr,
	&dev_attr_ac_status.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group acpi_tad_attr_group = अणु
	.attrs	= acpi_tad_attrs,
पूर्ण;

अटल sमाप_प्रकार dc_alarm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = acpi_tad_alarm_ग_लिखो(dev, buf, ACPI_TAD_DC_TIMER);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार dc_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस acpi_tad_alarm_पढ़ो(dev, buf, ACPI_TAD_DC_TIMER);
पूर्ण

अटल DEVICE_ATTR_RW(dc_alarm);

अटल sमाप_प्रकार dc_policy_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = acpi_tad_policy_ग_लिखो(dev, buf, ACPI_TAD_DC_TIMER);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार dc_policy_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस acpi_tad_policy_पढ़ो(dev, buf, ACPI_TAD_DC_TIMER);
पूर्ण

अटल DEVICE_ATTR_RW(dc_policy);

अटल sमाप_प्रकार dc_status_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = acpi_tad_status_ग_लिखो(dev, buf, ACPI_TAD_DC_TIMER);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार dc_status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस acpi_tad_status_पढ़ो(dev, buf, ACPI_TAD_DC_TIMER);
पूर्ण

अटल DEVICE_ATTR_RW(dc_status);

अटल काष्ठा attribute *acpi_tad_dc_attrs[] = अणु
	&dev_attr_dc_alarm.attr,
	&dev_attr_dc_policy.attr,
	&dev_attr_dc_status.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group acpi_tad_dc_attr_group = अणु
	.attrs	= acpi_tad_dc_attrs,
पूर्ण;

अटल पूर्णांक acpi_tad_disable_समयr(काष्ठा device *dev, u32 समयr_id)
अणु
	वापस acpi_tad_wake_set(dev, "_STV", समयr_id, ACPI_TAD_WAKE_DISABLED);
पूर्ण

अटल पूर्णांक acpi_tad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_tad_driver_data *dd = dev_get_drvdata(dev);

	device_init_wakeup(dev, false);

	pm_runसमय_get_sync(dev);

	अगर (dd->capabilities & ACPI_TAD_DC_WAKE)
		sysfs_हटाओ_group(&dev->kobj, &acpi_tad_dc_attr_group);

	sysfs_हटाओ_group(&dev->kobj, &acpi_tad_attr_group);

	acpi_tad_disable_समयr(dev, ACPI_TAD_AC_TIMER);
	acpi_tad_clear_status(dev, ACPI_TAD_AC_TIMER);
	अगर (dd->capabilities & ACPI_TAD_DC_WAKE) अणु
		acpi_tad_disable_समयr(dev, ACPI_TAD_DC_TIMER);
		acpi_tad_clear_status(dev, ACPI_TAD_DC_TIMER);
	पूर्ण

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_tad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	acpi_handle handle = ACPI_HANDLE(dev);
	काष्ठा acpi_tad_driver_data *dd;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ caps;
	पूर्णांक ret;

	/*
	 * Initialization failure messages are mostly about firmware issues, so
	 * prपूर्णांक them at the "info" level.
	 */
	status = acpi_evaluate_पूर्णांकeger(handle, "_GCP", शून्य, &caps);
	अगर (ACPI_FAILURE(status)) अणु
		dev_info(dev, "Unable to get capabilities\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!(caps & ACPI_TAD_AC_WAKE)) अणु
		dev_info(dev, "Unsupported capabilities\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_has_method(handle, "_PRW")) अणु
		dev_info(dev, "Missing _PRW\n");
		वापस -ENODEV;
	पूर्ण

	dd = devm_kzalloc(dev, माप(*dd), GFP_KERNEL);
	अगर (!dd)
		वापस -ENOMEM;

	dd->capabilities = caps;
	dev_set_drvdata(dev, dd);

	/*
	 * Assume that the ACPI PM करोमुख्य has been attached to the device and
	 * simply enable प्रणाली wakeup and runसमय PM and put the device पूर्णांकo
	 * runसमय suspend.  Everything अन्यथा should be taken care of by the ACPI
	 * PM करोमुख्य callbacks.
	 */
	device_init_wakeup(dev, true);
	dev_pm_set_driver_flags(dev, DPM_FLAG_SMART_SUSPEND |
				     DPM_FLAG_MAY_SKIP_RESUME);
	/*
	 * The platक्रमm bus type layer tells the ACPI PM करोमुख्य घातers up the
	 * device, so set the runसमय PM status of it to "active".
	 */
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_suspend(dev);

	ret = sysfs_create_group(&dev->kobj, &acpi_tad_attr_group);
	अगर (ret)
		जाओ fail;

	अगर (caps & ACPI_TAD_DC_WAKE) अणु
		ret = sysfs_create_group(&dev->kobj, &acpi_tad_dc_attr_group);
		अगर (ret)
			जाओ fail;
	पूर्ण

	अगर (caps & ACPI_TAD_RT) अणु
		ret = sysfs_create_group(&dev->kobj, &acpi_tad_समय_attr_group);
		अगर (ret)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	acpi_tad_हटाओ(pdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id acpi_tad_ids[] = अणु
	अणु"ACPI000E", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver acpi_tad_driver = अणु
	.driver = अणु
		.name = "acpi-tad",
		.acpi_match_table = acpi_tad_ids,
	पूर्ण,
	.probe = acpi_tad_probe,
	.हटाओ = acpi_tad_हटाओ,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_tad_ids);

module_platक्रमm_driver(acpi_tad_driver);
