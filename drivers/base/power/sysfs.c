<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sysfs entries क्रम device PM */
#समावेश <linux/device.h>
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/atomic.h>
#समावेश <linux/jअगरfies.h>
#समावेश "power.h"

/*
 *	control - Report/change current runसमय PM setting of the device
 *
 *	Runसमय घातer management of a device can be blocked with the help of
 *	this attribute.  All devices have one of the following two values क्रम
 *	the घातer/control file:
 *
 *	 + "auto\n" to allow the device to be घातer managed at run समय;
 *	 + "on\n" to prevent the device from being घातer managed at run समय;
 *
 *	The शेष क्रम all devices is "auto", which means that devices may be
 *	subject to स्वतःmatic घातer management, depending on their drivers.
 *	Changing this attribute to "on" prevents the driver from घातer managing
 *	the device at run समय.  Doing that जबतक the device is suspended causes
 *	it to be woken up.
 *
 *	wakeup - Report/change current wakeup option क्रम device
 *
 *	Some devices support "wakeup" events, which are hardware संकेतs
 *	used to activate devices from suspended or low घातer states.  Such
 *	devices have one of three values क्रम the sysfs घातer/wakeup file:
 *
 *	 + "enabled\n" to issue the events;
 *	 + "disabled\n" not to करो so; or
 *	 + "\n" क्रम temporary or permanent inability to issue wakeup.
 *
 *	(For example, unconfigured USB devices can't issue wakeups.)
 *
 *	Familiar examples of devices that can issue wakeup events include
 *	keyboards and mice (both PS2 and USB styles), घातer buttons, modems,
 *	"Wake-On-LAN" Ethernet links, GPIO lines, and more.  Some events
 *	will wake the entire प्रणाली from a suspend state; others may just
 *	wake up the device (अगर the प्रणाली as a whole is alपढ़ोy active).
 *	Some wakeup events use normal IRQ lines; other use special out
 *	of band संकेतing.
 *
 *	It is the responsibility of device drivers to enable (or disable)
 *	wakeup संकेतing as part of changing device घातer states, respecting
 *	the policy choices provided through the driver model.
 *
 *	Devices may not be able to generate wakeup events from all घातer
 *	states.  Also, the events may be ignored in some configurations;
 *	क्रम example, they might need help from other devices that aren't
 *	active, or which may have wakeup disabled.  Some drivers rely on
 *	wakeup events पूर्णांकernally (unless they are disabled), keeping
 *	their hardware in low घातer modes whenever they're unused.  This
 *	saves runसमय घातer, without requiring प्रणाली-wide sleep states.
 *
 *	async - Report/change current async suspend setting क्रम the device
 *
 *	Asynchronous suspend and resume of the device during प्रणाली-wide घातer
 *	state transitions can be enabled by writing "enabled" to this file.
 *	Analogously, अगर "disabled" is written to this file, the device will be
 *	suspended and resumed synchronously.
 *
 *	All devices have one of the following two values क्रम घातer/async:
 *
 *	 + "enabled\n" to permit the asynchronous suspend/resume of the device;
 *	 + "disabled\n" to क्रमbid it;
 *
 *	NOTE: It generally is unsafe to permit the asynchronous suspend/resume
 *	of a device unless it is certain that all of the PM dependencies of the
 *	device are known to the PM core.  However, क्रम some devices this
 *	attribute is set to "enabled" by bus type code or device drivers and in
 *	that हालs it should be safe to leave the शेष value.
 *
 *	स्वतःsuspend_delay_ms - Report/change a device's स्वतःsuspend_delay value
 *
 *	Some drivers करोn't want to carry out a runसमय suspend as soon as a
 *	device becomes idle; they want it always to reमुख्य idle क्रम some period
 *	of समय beक्रमe suspending it.  This period is the स्वतःsuspend_delay
 *	value (expressed in milliseconds) and it can be controlled by the user.
 *	If the value is negative then the device will never be runसमय
 *	suspended.
 *
 *	NOTE: The स्वतःsuspend_delay_ms attribute and the स्वतःsuspend_delay
 *	value are used only अगर the driver calls pm_runसमय_use_स्वतःsuspend().
 *
 *	wakeup_count - Report the number of wakeup events related to the device
 */

स्थिर अक्षर घातer_group_name[] = "power";
EXPORT_SYMBOL_GPL(घातer_group_name);

अटल स्थिर अक्षर ctrl_स्वतः[] = "auto";
अटल स्थिर अक्षर ctrl_on[] = "on";

अटल sमाप_प्रकार control_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n",
			  dev->घातer.runसमय_स्वतः ? ctrl_स्वतः : ctrl_on);
पूर्ण

अटल sमाप_प्रकार control_store(काष्ठा device * dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर * buf, माप_प्रकार n)
अणु
	device_lock(dev);
	अगर (sysfs_streq(buf, ctrl_स्वतः))
		pm_runसमय_allow(dev);
	अन्यथा अगर (sysfs_streq(buf, ctrl_on))
		pm_runसमय_क्रमbid(dev);
	अन्यथा
		n = -EINVAL;
	device_unlock(dev);
	वापस n;
पूर्ण

अटल DEVICE_ATTR_RW(control);

अटल sमाप_प्रकार runसमय_active_समय_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	u64 पंचांगp = pm_runसमय_active_समय(dev);

	करो_भाग(पंचांगp, NSEC_PER_MSEC);

	वापस sysfs_emit(buf, "%llu\n", पंचांगp);
पूर्ण

अटल DEVICE_ATTR_RO(runसमय_active_समय);

अटल sमाप_प्रकार runसमय_suspended_समय_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	u64 पंचांगp = pm_runसमय_suspended_समय(dev);

	करो_भाग(पंचांगp, NSEC_PER_MSEC);

	वापस sysfs_emit(buf, "%llu\n", पंचांगp);
पूर्ण

अटल DEVICE_ATTR_RO(runसमय_suspended_समय);

अटल sमाप_प्रकार runसमय_status_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *output;

	अगर (dev->घातer.runसमय_error) अणु
		output = "error";
	पूर्ण अन्यथा अगर (dev->घातer.disable_depth) अणु
		output = "unsupported";
	पूर्ण अन्यथा अणु
		चयन (dev->घातer.runसमय_status) अणु
		हाल RPM_SUSPENDED:
			output = "suspended";
			अवरोध;
		हाल RPM_SUSPENDING:
			output = "suspending";
			अवरोध;
		हाल RPM_RESUMING:
			output = "resuming";
			अवरोध;
		हाल RPM_ACTIVE:
			output = "active";
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल DEVICE_ATTR_RO(runसमय_status);

अटल sमाप_प्रकार स्वतःsuspend_delay_ms_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	अगर (!dev->घातer.use_स्वतःsuspend)
		वापस -EIO;

	वापस sysfs_emit(buf, "%d\n", dev->घातer.स्वतःsuspend_delay);
पूर्ण

अटल sमाप_प्रकार स्वतःsuspend_delay_ms_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	दीर्घ delay;

	अगर (!dev->घातer.use_स्वतःsuspend)
		वापस -EIO;

	अगर (kम_से_दीर्घ(buf, 10, &delay) != 0 || delay != (पूर्णांक) delay)
		वापस -EINVAL;

	device_lock(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, delay);
	device_unlock(dev);
	वापस n;
पूर्ण

अटल DEVICE_ATTR_RW(स्वतःsuspend_delay_ms);

अटल sमाप_प्रकार pm_qos_resume_latency_us_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	s32 value = dev_pm_qos_requested_resume_latency(dev);

	अगर (value == 0)
		वापस sysfs_emit(buf, "n/a\n");
	अगर (value == PM_QOS_RESUME_LATENCY_NO_CONSTRAINT)
		value = 0;

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार pm_qos_resume_latency_us_store(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	s32 value;
	पूर्णांक ret;

	अगर (!kstrtos32(buf, 0, &value)) अणु
		/*
		 * Prevent users from writing negative or "no constraint" values
		 * directly.
		 */
		अगर (value < 0 || value == PM_QOS_RESUME_LATENCY_NO_CONSTRAINT)
			वापस -EINVAL;

		अगर (value == 0)
			value = PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "n/a")) अणु
		value = 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = dev_pm_qos_update_request(dev->घातer.qos->resume_latency_req,
					value);
	वापस ret < 0 ? ret : n;
पूर्ण

अटल DEVICE_ATTR_RW(pm_qos_resume_latency_us);

अटल sमाप_प्रकार pm_qos_latency_tolerance_us_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	s32 value = dev_pm_qos_get_user_latency_tolerance(dev);

	अगर (value < 0)
		वापस sysfs_emit(buf, "%s\n", "auto");
	अगर (value == PM_QOS_LATENCY_ANY)
		वापस sysfs_emit(buf, "%s\n", "any");

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार pm_qos_latency_tolerance_us_store(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	s32 value;
	पूर्णांक ret;

	अगर (kstrtos32(buf, 0, &value) == 0) अणु
		/* Users can't ग_लिखो negative values directly */
		अगर (value < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (sysfs_streq(buf, "auto"))
			value = PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT;
		अन्यथा अगर (sysfs_streq(buf, "any"))
			value = PM_QOS_LATENCY_ANY;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	ret = dev_pm_qos_update_user_latency_tolerance(dev, value);
	वापस ret < 0 ? ret : n;
पूर्ण

अटल DEVICE_ATTR_RW(pm_qos_latency_tolerance_us);

अटल sमाप_प्रकार pm_qos_no_घातer_off_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(dev_pm_qos_requested_flags(dev)
					  & PM_QOS_FLAG_NO_POWER_OFF));
पूर्ण

अटल sमाप_प्रकार pm_qos_no_घातer_off_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक ret;

	अगर (kstrtoपूर्णांक(buf, 0, &ret))
		वापस -EINVAL;

	अगर (ret != 0 && ret != 1)
		वापस -EINVAL;

	ret = dev_pm_qos_update_flags(dev, PM_QOS_FLAG_NO_POWER_OFF, ret);
	वापस ret < 0 ? ret : n;
पूर्ण

अटल DEVICE_ATTR_RW(pm_qos_no_घातer_off);

#अगर_घोषित CONFIG_PM_SLEEP
अटल स्थिर अक्षर _enabled[] = "enabled";
अटल स्थिर अक्षर _disabled[] = "disabled";

अटल sमाप_प्रकार wakeup_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n", device_can_wakeup(dev)
			  ? (device_may_wakeup(dev) ? _enabled : _disabled)
			  : "");
पूर्ण

अटल sमाप_प्रकार wakeup_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अगर (!device_can_wakeup(dev))
		वापस -EINVAL;

	अगर (sysfs_streq(buf, _enabled))
		device_set_wakeup_enable(dev, 1);
	अन्यथा अगर (sysfs_streq(buf, _disabled))
		device_set_wakeup_enable(dev, 0);
	अन्यथा
		वापस -EINVAL;
	वापस n;
पूर्ण

अटल DEVICE_ATTR_RW(wakeup);

अटल sमाप_प्रकार wakeup_count_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ count;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		count = dev->घातer.wakeup->wakeup_count;
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lu\n", count);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_count);

अटल sमाप_प्रकार wakeup_active_count_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	अचिन्हित दीर्घ count;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		count = dev->घातer.wakeup->active_count;
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lu\n", count);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_active_count);

अटल sमाप_प्रकार wakeup_पात_count_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	अचिन्हित दीर्घ count;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		count = dev->घातer.wakeup->wakeup_count;
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lu\n", count);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_पात_count);

अटल sमाप_प्रकार wakeup_expire_count_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	अचिन्हित दीर्घ count;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		count = dev->घातer.wakeup->expire_count;
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lu\n", count);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_expire_count);

अटल sमाप_प्रकार wakeup_active_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक active;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		active = dev->घातer.wakeup->active;
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%u\n", active);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_active);

अटल sमाप_प्रकार wakeup_total_समय_ms_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	s64 msec;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		msec = kसमय_प्रकारo_ms(dev->घातer.wakeup->total_समय);
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lld\n", msec);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_total_समय_ms);

अटल sमाप_प्रकार wakeup_max_समय_ms_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	s64 msec;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		msec = kसमय_प्रकारo_ms(dev->घातer.wakeup->max_समय);
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lld\n", msec);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_max_समय_ms);

अटल sमाप_प्रकार wakeup_last_समय_ms_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	s64 msec;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		msec = kसमय_प्रकारo_ms(dev->घातer.wakeup->last_समय);
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lld\n", msec);
पूर्ण

अटल अंतरभूत पूर्णांक dpm_sysfs_wakeup_change_owner(काष्ठा device *dev, kuid_t kuid,
						kgid_t kgid)
अणु
	अगर (dev->घातer.wakeup && dev->घातer.wakeup->dev)
		वापस device_change_owner(dev->घातer.wakeup->dev, kuid, kgid);
	वापस 0;
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_last_समय_ms);

#अगर_घोषित CONFIG_PM_AUTOSLEEP
अटल sमाप_प्रकार wakeup_prevent_sleep_समय_ms_show(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	s64 msec;
	bool enabled = false;

	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		msec = kसमय_प्रकारo_ms(dev->घातer.wakeup->prevent_sleep_समय);
		enabled = true;
	पूर्ण
	spin_unlock_irq(&dev->घातer.lock);

	अगर (!enabled)
		वापस sysfs_emit(buf, "\n");
	वापस sysfs_emit(buf, "%lld\n", msec);
पूर्ण

अटल DEVICE_ATTR_RO(wakeup_prevent_sleep_समय_ms);
#पूर्ण_अगर /* CONFIG_PM_AUTOSLEEP */
#अन्यथा /* CONFIG_PM_SLEEP */
अटल अंतरभूत पूर्णांक dpm_sysfs_wakeup_change_owner(काष्ठा device *dev, kuid_t kuid,
						kgid_t kgid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_ADVANCED_DEBUG
अटल sमाप_प्रकार runसमय_usage_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", atomic_पढ़ो(&dev->घातer.usage_count));
पूर्ण
अटल DEVICE_ATTR_RO(runसमय_usage);

अटल sमाप_प्रकार runसमय_active_kids_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", dev->घातer.ignore_children ?
			  0 : atomic_पढ़ो(&dev->घातer.child_count));
पूर्ण
अटल DEVICE_ATTR_RO(runसमय_active_kids);

अटल sमाप_प्रकार runसमय_enabled_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *output;

	अगर (dev->घातer.disable_depth && !dev->घातer.runसमय_स्वतः)
		output = "disabled & forbidden";
	अन्यथा अगर (dev->घातer.disable_depth)
		output = "disabled";
	अन्यथा अगर (!dev->घातer.runसमय_स्वतः)
		output = "forbidden";
	अन्यथा
		output = "enabled";

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण
अटल DEVICE_ATTR_RO(runसमय_enabled);

#अगर_घोषित CONFIG_PM_SLEEP
अटल sमाप_प्रकार async_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n",
			  device_async_suspend_enabled(dev) ?
			  _enabled : _disabled);
पूर्ण

अटल sमाप_प्रकार async_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अगर (sysfs_streq(buf, _enabled))
		device_enable_async_suspend(dev);
	अन्यथा अगर (sysfs_streq(buf, _disabled))
		device_disable_async_suspend(dev);
	अन्यथा
		वापस -EINVAL;
	वापस n;
पूर्ण

अटल DEVICE_ATTR_RW(async);

#पूर्ण_अगर /* CONFIG_PM_SLEEP */
#पूर्ण_अगर /* CONFIG_PM_ADVANCED_DEBUG */

अटल काष्ठा attribute *घातer_attrs[] = अणु
#अगर_घोषित CONFIG_PM_ADVANCED_DEBUG
#अगर_घोषित CONFIG_PM_SLEEP
	&dev_attr_async.attr,
#पूर्ण_अगर
	&dev_attr_runसमय_status.attr,
	&dev_attr_runसमय_usage.attr,
	&dev_attr_runसमय_active_kids.attr,
	&dev_attr_runसमय_enabled.attr,
#पूर्ण_अगर /* CONFIG_PM_ADVANCED_DEBUG */
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group pm_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= घातer_attrs,
पूर्ण;

अटल काष्ठा attribute *wakeup_attrs[] = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	&dev_attr_wakeup.attr,
	&dev_attr_wakeup_count.attr,
	&dev_attr_wakeup_active_count.attr,
	&dev_attr_wakeup_पात_count.attr,
	&dev_attr_wakeup_expire_count.attr,
	&dev_attr_wakeup_active.attr,
	&dev_attr_wakeup_total_समय_ms.attr,
	&dev_attr_wakeup_max_समय_ms.attr,
	&dev_attr_wakeup_last_समय_ms.attr,
#अगर_घोषित CONFIG_PM_AUTOSLEEP
	&dev_attr_wakeup_prevent_sleep_समय_ms.attr,
#पूर्ण_अगर
#पूर्ण_अगर
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group pm_wakeup_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= wakeup_attrs,
पूर्ण;

अटल काष्ठा attribute *runसमय_attrs[] = अणु
#अगर_अघोषित CONFIG_PM_ADVANCED_DEBUG
	&dev_attr_runसमय_status.attr,
#पूर्ण_अगर
	&dev_attr_control.attr,
	&dev_attr_runसमय_suspended_समय.attr,
	&dev_attr_runसमय_active_समय.attr,
	&dev_attr_स्वतःsuspend_delay_ms.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group pm_runसमय_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= runसमय_attrs,
पूर्ण;

अटल काष्ठा attribute *pm_qos_resume_latency_attrs[] = अणु
	&dev_attr_pm_qos_resume_latency_us.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group pm_qos_resume_latency_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= pm_qos_resume_latency_attrs,
पूर्ण;

अटल काष्ठा attribute *pm_qos_latency_tolerance_attrs[] = अणु
	&dev_attr_pm_qos_latency_tolerance_us.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group pm_qos_latency_tolerance_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= pm_qos_latency_tolerance_attrs,
पूर्ण;

अटल काष्ठा attribute *pm_qos_flags_attrs[] = अणु
	&dev_attr_pm_qos_no_घातer_off.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group pm_qos_flags_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= pm_qos_flags_attrs,
पूर्ण;

पूर्णांक dpm_sysfs_add(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	/* No need to create PM sysfs अगर explicitly disabled. */
	अगर (device_pm_not_required(dev))
		वापस 0;

	rc = sysfs_create_group(&dev->kobj, &pm_attr_group);
	अगर (rc)
		वापस rc;

	अगर (!pm_runसमय_has_no_callbacks(dev)) अणु
		rc = sysfs_merge_group(&dev->kobj, &pm_runसमय_attr_group);
		अगर (rc)
			जाओ err_out;
	पूर्ण
	अगर (device_can_wakeup(dev)) अणु
		rc = sysfs_merge_group(&dev->kobj, &pm_wakeup_attr_group);
		अगर (rc)
			जाओ err_runसमय;
	पूर्ण
	अगर (dev->घातer.set_latency_tolerance) अणु
		rc = sysfs_merge_group(&dev->kobj,
				       &pm_qos_latency_tolerance_attr_group);
		अगर (rc)
			जाओ err_wakeup;
	पूर्ण
	rc = pm_wakeup_source_sysfs_add(dev);
	अगर (rc)
		जाओ err_latency;
	वापस 0;

 err_latency:
	sysfs_unmerge_group(&dev->kobj, &pm_qos_latency_tolerance_attr_group);
 err_wakeup:
	sysfs_unmerge_group(&dev->kobj, &pm_wakeup_attr_group);
 err_runसमय:
	sysfs_unmerge_group(&dev->kobj, &pm_runसमय_attr_group);
 err_out:
	sysfs_हटाओ_group(&dev->kobj, &pm_attr_group);
	वापस rc;
पूर्ण

पूर्णांक dpm_sysfs_change_owner(काष्ठा device *dev, kuid_t kuid, kgid_t kgid)
अणु
	पूर्णांक rc;

	अगर (device_pm_not_required(dev))
		वापस 0;

	rc = sysfs_group_change_owner(&dev->kobj, &pm_attr_group, kuid, kgid);
	अगर (rc)
		वापस rc;

	अगर (!pm_runसमय_has_no_callbacks(dev)) अणु
		rc = sysfs_group_change_owner(
			&dev->kobj, &pm_runसमय_attr_group, kuid, kgid);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (device_can_wakeup(dev)) अणु
		rc = sysfs_group_change_owner(&dev->kobj, &pm_wakeup_attr_group,
					      kuid, kgid);
		अगर (rc)
			वापस rc;

		rc = dpm_sysfs_wakeup_change_owner(dev, kuid, kgid);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (dev->घातer.set_latency_tolerance) अणु
		rc = sysfs_group_change_owner(
			&dev->kobj, &pm_qos_latency_tolerance_attr_group, kuid,
			kgid);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक wakeup_sysfs_add(काष्ठा device *dev)
अणु
	पूर्णांक ret = sysfs_merge_group(&dev->kobj, &pm_wakeup_attr_group);

	अगर (!ret)
		kobject_uevent(&dev->kobj, KOBJ_CHANGE);

	वापस ret;
पूर्ण

व्योम wakeup_sysfs_हटाओ(काष्ठा device *dev)
अणु
	sysfs_unmerge_group(&dev->kobj, &pm_wakeup_attr_group);
	kobject_uevent(&dev->kobj, KOBJ_CHANGE);
पूर्ण

पूर्णांक pm_qos_sysfs_add_resume_latency(काष्ठा device *dev)
अणु
	वापस sysfs_merge_group(&dev->kobj, &pm_qos_resume_latency_attr_group);
पूर्ण

व्योम pm_qos_sysfs_हटाओ_resume_latency(काष्ठा device *dev)
अणु
	sysfs_unmerge_group(&dev->kobj, &pm_qos_resume_latency_attr_group);
पूर्ण

पूर्णांक pm_qos_sysfs_add_flags(काष्ठा device *dev)
अणु
	वापस sysfs_merge_group(&dev->kobj, &pm_qos_flags_attr_group);
पूर्ण

व्योम pm_qos_sysfs_हटाओ_flags(काष्ठा device *dev)
अणु
	sysfs_unmerge_group(&dev->kobj, &pm_qos_flags_attr_group);
पूर्ण

पूर्णांक pm_qos_sysfs_add_latency_tolerance(काष्ठा device *dev)
अणु
	वापस sysfs_merge_group(&dev->kobj,
				 &pm_qos_latency_tolerance_attr_group);
पूर्ण

व्योम pm_qos_sysfs_हटाओ_latency_tolerance(काष्ठा device *dev)
अणु
	sysfs_unmerge_group(&dev->kobj, &pm_qos_latency_tolerance_attr_group);
पूर्ण

व्योम rpm_sysfs_हटाओ(काष्ठा device *dev)
अणु
	sysfs_unmerge_group(&dev->kobj, &pm_runसमय_attr_group);
पूर्ण

व्योम dpm_sysfs_हटाओ(काष्ठा device *dev)
अणु
	अगर (device_pm_not_required(dev))
		वापस;
	sysfs_unmerge_group(&dev->kobj, &pm_qos_latency_tolerance_attr_group);
	dev_pm_qos_स्थिरraपूर्णांकs_destroy(dev);
	rpm_sysfs_हटाओ(dev);
	sysfs_unmerge_group(&dev->kobj, &pm_wakeup_attr_group);
	sysfs_हटाओ_group(&dev->kobj, &pm_attr_group);
पूर्ण
