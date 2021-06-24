<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2015 Qualcomm Atheros, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "wmi-ops.h"

अटल पूर्णांक
ath10k_thermal_get_max_throttle_state(काष्ठा thermal_cooling_device *cdev,
				      अचिन्हित दीर्घ *state)
अणु
	*state = ATH10K_THERMAL_THROTTLE_MAX;

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_thermal_get_cur_throttle_state(काष्ठा thermal_cooling_device *cdev,
				      अचिन्हित दीर्घ *state)
अणु
	काष्ठा ath10k *ar = cdev->devdata;

	mutex_lock(&ar->conf_mutex);
	*state = ar->thermal.throttle_state;
	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_thermal_set_cur_throttle_state(काष्ठा thermal_cooling_device *cdev,
				      अचिन्हित दीर्घ throttle_state)
अणु
	काष्ठा ath10k *ar = cdev->devdata;

	अगर (throttle_state > ATH10K_THERMAL_THROTTLE_MAX) अणु
		ath10k_warn(ar, "throttle state %ld is exceeding the limit %d\n",
			    throttle_state, ATH10K_THERMAL_THROTTLE_MAX);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&ar->conf_mutex);
	ar->thermal.throttle_state = throttle_state;
	ath10k_thermal_set_throttling(ar);
	mutex_unlock(&ar->conf_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops ath10k_thermal_ops = अणु
	.get_max_state = ath10k_thermal_get_max_throttle_state,
	.get_cur_state = ath10k_thermal_get_cur_throttle_state,
	.set_cur_state = ath10k_thermal_set_cur_throttle_state,
पूर्ण;

अटल sमाप_प्रकार ath10k_thermal_show_temp(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा ath10k *ar = dev_get_drvdata(dev);
	पूर्णांक ret, temperature;
	अचिन्हित दीर्घ समय_left;

	mutex_lock(&ar->conf_mutex);

	/* Can't get temperature when the card is off */
	अगर (ar->state != ATH10K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	reinit_completion(&ar->thermal.wmi_sync);
	ret = ath10k_wmi_pdev_get_temperature(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read temperature %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags)) अणु
		ret = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->thermal.wmi_sync,
						ATH10K_THERMAL_SYNC_TIMEOUT_HZ);
	अगर (!समय_left) अणु
		ath10k_warn(ar, "failed to synchronize thermal read\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	temperature = ar->thermal.temperature;
	spin_unlock_bh(&ar->data_lock);

	/* display in millidegree celcius */
	ret = snम_लिखो(buf, PAGE_SIZE, "%d\n", temperature * 1000);
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

व्योम ath10k_thermal_event_temperature(काष्ठा ath10k *ar, पूर्णांक temperature)
अणु
	spin_lock_bh(&ar->data_lock);
	ar->thermal.temperature = temperature;
	spin_unlock_bh(&ar->data_lock);
	complete(&ar->thermal.wmi_sync);
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, ath10k_thermal_show_temp,
			  शून्य, 0);

अटल काष्ठा attribute *ath10k_hwmon_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ath10k_hwmon);

व्योम ath10k_thermal_set_throttling(काष्ठा ath10k *ar)
अणु
	u32 period, duration, enabled;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!test_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map))
		वापस;

	अगर (!ar->wmi.ops->gen_pdev_set_quiet_mode)
		वापस;

	अगर (ar->state != ATH10K_STATE_ON)
		वापस;

	period = ar->thermal.quiet_period;
	duration = (period * ar->thermal.throttle_state) / 100;
	enabled = duration ? 1 : 0;

	ret = ath10k_wmi_pdev_set_quiet_mode(ar, period, duration,
					     ATH10K_QUIET_START_OFFSET,
					     enabled);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set quiet mode period %u duarion %u enabled %u ret %d\n",
			    period, duration, enabled, ret);
	पूर्ण
पूर्ण

पूर्णांक ath10k_thermal_रेजिस्टर(काष्ठा ath10k *ar)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	अगर (!test_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map))
		वापस 0;

	cdev = thermal_cooling_device_रेजिस्टर("ath10k_thermal", ar,
					       &ath10k_thermal_ops);

	अगर (IS_ERR(cdev)) अणु
		ath10k_err(ar, "failed to setup thermal device result: %ld\n",
			   PTR_ERR(cdev));
		वापस -EINVAL;
	पूर्ण

	ret = sysfs_create_link(&ar->dev->kobj, &cdev->device.kobj,
				"cooling_device");
	अगर (ret) अणु
		ath10k_err(ar, "failed to create cooling device symlink\n");
		जाओ err_cooling_destroy;
	पूर्ण

	ar->thermal.cdev = cdev;
	ar->thermal.quiet_period = ATH10K_QUIET_PERIOD_DEFAULT;

	/* Do not रेजिस्टर hwmon device when temperature पढ़ोing is not
	 * supported by firmware
	 */
	अगर (!(ar->wmi.ops->gen_pdev_get_temperature))
		वापस 0;

	/* Aव्योम linking error on devm_hwmon_device_रेजिस्टर_with_groups, I
	 * guess linux/hwmon.h is missing proper stubs.
	 */
	अगर (!IS_REACHABLE(CONFIG_HWMON))
		वापस 0;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(ar->dev,
							   "ath10k_hwmon", ar,
							   ath10k_hwmon_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		ath10k_err(ar, "failed to register hwmon device: %ld\n",
			   PTR_ERR(hwmon_dev));
		ret = -EINVAL;
		जाओ err_हटाओ_link;
	पूर्ण
	वापस 0;

err_हटाओ_link:
	sysfs_हटाओ_link(&ar->dev->kobj, "cooling_device");
err_cooling_destroy:
	thermal_cooling_device_unरेजिस्टर(cdev);
	वापस ret;
पूर्ण

व्योम ath10k_thermal_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
	अगर (!test_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map))
		वापस;

	sysfs_हटाओ_link(&ar->dev->kobj, "cooling_device");
	thermal_cooling_device_unरेजिस्टर(ar->thermal.cdev);
पूर्ण
