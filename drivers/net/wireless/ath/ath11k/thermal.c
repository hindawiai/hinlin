<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश "core.h"
#समावेश "debug.h"

अटल पूर्णांक
ath11k_thermal_get_max_throttle_state(काष्ठा thermal_cooling_device *cdev,
				      अचिन्हित दीर्घ *state)
अणु
	*state = ATH11K_THERMAL_THROTTLE_MAX;

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_thermal_get_cur_throttle_state(काष्ठा thermal_cooling_device *cdev,
				      अचिन्हित दीर्घ *state)
अणु
	काष्ठा ath11k *ar = cdev->devdata;

	mutex_lock(&ar->conf_mutex);
	*state = ar->thermal.throttle_state;
	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_thermal_set_cur_throttle_state(काष्ठा thermal_cooling_device *cdev,
				      अचिन्हित दीर्घ throttle_state)
अणु
	काष्ठा ath11k *ar = cdev->devdata;
	पूर्णांक ret;

	अगर (throttle_state > ATH11K_THERMAL_THROTTLE_MAX) अणु
		ath11k_warn(ar->ab, "throttle state %ld is exceeding the limit %d\n",
			    throttle_state, ATH11K_THERMAL_THROTTLE_MAX);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&ar->conf_mutex);
	ret = ath11k_thermal_set_throttling(ar, throttle_state);
	अगर (ret == 0)
		ar->thermal.throttle_state = throttle_state;
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops ath11k_thermal_ops = अणु
	.get_max_state = ath11k_thermal_get_max_throttle_state,
	.get_cur_state = ath11k_thermal_get_cur_throttle_state,
	.set_cur_state = ath11k_thermal_set_cur_throttle_state,
पूर्ण;

अटल sमाप_प्रकार ath11k_thermal_show_temp(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा ath11k *ar = dev_get_drvdata(dev);
	पूर्णांक ret, temperature;
	अचिन्हित दीर्घ समय_left;

	mutex_lock(&ar->conf_mutex);

	/* Can't get temperature when the card is off */
	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	reinit_completion(&ar->thermal.wmi_sync);
	ret = ath11k_wmi_send_pdev_temperature_cmd(ar);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to read temperature %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags)) अणु
		ret = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->thermal.wmi_sync,
						ATH11K_THERMAL_SYNC_TIMEOUT_HZ);
	अगर (!समय_left) अणु
		ath11k_warn(ar->ab, "failed to synchronize thermal read\n");
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

व्योम ath11k_thermal_event_temperature(काष्ठा ath11k *ar, पूर्णांक temperature)
अणु
	spin_lock_bh(&ar->data_lock);
	ar->thermal.temperature = temperature;
	spin_unlock_bh(&ar->data_lock);
	complete(&ar->thermal.wmi_sync);
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, ath11k_thermal_show_temp,
			  शून्य, 0);

अटल काष्ठा attribute *ath11k_hwmon_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ath11k_hwmon);

पूर्णांक ath11k_thermal_set_throttling(काष्ठा ath11k *ar, u32 throttle_state)
अणु
	काष्ठा ath11k_base *sc = ar->ab;
	काष्ठा thermal_mitigation_params param;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON)
		वापस 0;

	स_रखो(&param, 0, माप(param));
	param.pdev_id = ar->pdev->pdev_id;
	param.enable = throttle_state ? 1 : 0;
	param.dc = ATH11K_THERMAL_DEFAULT_DUTY_CYCLE;
	param.dc_per_event = 0xFFFFFFFF;

	param.levelconf[0].पंचांगplwm = ATH11K_THERMAL_TEMP_LOW_MARK;
	param.levelconf[0].पंचांगphwm = ATH11K_THERMAL_TEMP_HIGH_MARK;
	param.levelconf[0].dcoffpercent = throttle_state;
	param.levelconf[0].priority = 0; /* disable all data tx queues */

	ret = ath11k_wmi_send_thermal_mitigation_param_cmd(ar, &param);
	अगर (ret) अणु
		ath11k_warn(sc, "failed to send thermal mitigation duty cycle %u ret %d\n",
			    throttle_state, ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_thermal_रेजिस्टर(काष्ठा ath11k_base *sc)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *hwmon_dev;
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < sc->num_radios; i++) अणु
		pdev = &sc->pdevs[i];
		ar = pdev->ar;
		अगर (!ar)
			जारी;

		cdev = thermal_cooling_device_रेजिस्टर("ath11k_thermal", ar,
						       &ath11k_thermal_ops);

		अगर (IS_ERR(cdev)) अणु
			ath11k_err(sc, "failed to setup thermal device result: %ld\n",
				   PTR_ERR(cdev));
			ret = -EINVAL;
			जाओ err_thermal_destroy;
		पूर्ण

		ar->thermal.cdev = cdev;

		ret = sysfs_create_link(&ar->hw->wiphy->dev.kobj, &cdev->device.kobj,
					"cooling_device");
		अगर (ret) अणु
			ath11k_err(sc, "failed to create cooling device symlink\n");
			जाओ err_thermal_destroy;
		पूर्ण

		अगर (!IS_REACHABLE(CONFIG_HWMON))
			वापस 0;

		hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&ar->hw->wiphy->dev,
								   "ath11k_hwmon", ar,
								   ath11k_hwmon_groups);
		अगर (IS_ERR(hwmon_dev)) अणु
			ath11k_err(ar->ab, "failed to register hwmon device: %ld\n",
				   PTR_ERR(hwmon_dev));
			ret = -EINVAL;
			जाओ err_thermal_destroy;
		पूर्ण
	पूर्ण

	वापस 0;

err_thermal_destroy:
	ath11k_thermal_unरेजिस्टर(sc);
	वापस ret;
पूर्ण

व्योम ath11k_thermal_unरेजिस्टर(काष्ठा ath11k_base *sc)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक i;

	क्रम (i = 0; i < sc->num_radios; i++) अणु
		pdev = &sc->pdevs[i];
		ar = pdev->ar;
		अगर (!ar)
			जारी;

		sysfs_हटाओ_link(&ar->hw->wiphy->dev.kobj, "cooling_device");
		thermal_cooling_device_unरेजिस्टर(ar->thermal.cdev);
	पूर्ण
पूर्ण
