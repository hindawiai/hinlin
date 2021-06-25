<शैली गुरु>
/*
 * Copyright 2010 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#अगर_घोषित CONFIG_ACPI
#समावेश <linux/acpi.h>
#पूर्ण_अगर
#समावेश <linux/घातer_supply.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_hwmon.h"

#समावेश <nvkm/subdev/iccsense.h>
#समावेश <nvkm/subdev/volt.h>

#अगर defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))

अटल sमाप_प्रकार
nouveau_hwmon_show_temp1_स्वतः_poपूर्णांक1_pwm(काष्ठा device *d,
					 काष्ठा device_attribute *a, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", 100);
पूर्ण
अटल SENSOR_DEVICE_ATTR(temp1_स्वतः_poपूर्णांक1_pwm, 0444,
			  nouveau_hwmon_show_temp1_स्वतः_poपूर्णांक1_pwm, शून्य, 0);

अटल sमाप_प्रकार
nouveau_hwmon_temp1_स्वतः_poपूर्णांक1_temp(काष्ठा device *d,
				     काष्ठा device_attribute *a, अक्षर *buf)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
	      therm->attr_get(therm, NVKM_THERM_ATTR_THRS_FAN_BOOST) * 1000);
पूर्ण
अटल sमाप_प्रकार
nouveau_hwmon_set_temp1_स्वतः_poपूर्णांक1_temp(काष्ठा device *d,
					 काष्ठा device_attribute *a,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	दीर्घ value;

	अगर (kम_से_दीर्घ(buf, 10, &value))
		वापस -EINVAL;

	therm->attr_set(therm, NVKM_THERM_ATTR_THRS_FAN_BOOST,
			value / 1000);

	वापस count;
पूर्ण
अटल SENSOR_DEVICE_ATTR(temp1_स्वतः_poपूर्णांक1_temp, 0644,
			  nouveau_hwmon_temp1_स्वतः_poपूर्णांक1_temp,
			  nouveau_hwmon_set_temp1_स्वतः_poपूर्णांक1_temp, 0);

अटल sमाप_प्रकार
nouveau_hwmon_temp1_स्वतः_poपूर्णांक1_temp_hyst(काष्ठा device *d,
					  काष्ठा device_attribute *a, अक्षर *buf)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
	 therm->attr_get(therm, NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST) * 1000);
पूर्ण
अटल sमाप_प्रकार
nouveau_hwmon_set_temp1_स्वतः_poपूर्णांक1_temp_hyst(काष्ठा device *d,
					      काष्ठा device_attribute *a,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	दीर्घ value;

	अगर (kम_से_दीर्घ(buf, 10, &value))
		वापस -EINVAL;

	therm->attr_set(therm, NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST,
			value / 1000);

	वापस count;
पूर्ण
अटल SENSOR_DEVICE_ATTR(temp1_स्वतः_poपूर्णांक1_temp_hyst, 0644,
			  nouveau_hwmon_temp1_स्वतः_poपूर्णांक1_temp_hyst,
			  nouveau_hwmon_set_temp1_स्वतः_poपूर्णांक1_temp_hyst, 0);

अटल sमाप_प्रकार
nouveau_hwmon_get_pwm1_max(काष्ठा device *d,
			   काष्ठा device_attribute *a, अक्षर *buf)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	पूर्णांक ret;

	ret = therm->attr_get(therm, NVKM_THERM_ATTR_FAN_MAX_DUTY);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", ret);
पूर्ण

अटल sमाप_प्रकार
nouveau_hwmon_get_pwm1_min(काष्ठा device *d,
			   काष्ठा device_attribute *a, अक्षर *buf)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	पूर्णांक ret;

	ret = therm->attr_get(therm, NVKM_THERM_ATTR_FAN_MIN_DUTY);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", ret);
पूर्ण

अटल sमाप_प्रकार
nouveau_hwmon_set_pwm1_min(काष्ठा device *d, काष्ठा device_attribute *a,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	दीर्घ value;
	पूर्णांक ret;

	अगर (kम_से_दीर्घ(buf, 10, &value))
		वापस -EINVAL;

	ret = therm->attr_set(therm, NVKM_THERM_ATTR_FAN_MIN_DUTY, value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल SENSOR_DEVICE_ATTR(pwm1_min, 0644,
			  nouveau_hwmon_get_pwm1_min,
			  nouveau_hwmon_set_pwm1_min, 0);

अटल sमाप_प्रकार
nouveau_hwmon_set_pwm1_max(काष्ठा device *d, काष्ठा device_attribute *a,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(d);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	दीर्घ value;
	पूर्णांक ret;

	अगर (kम_से_दीर्घ(buf, 10, &value))
		वापस -EINVAL;

	ret = therm->attr_set(therm, NVKM_THERM_ATTR_FAN_MAX_DUTY, value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल SENSOR_DEVICE_ATTR(pwm1_max, 0644,
			  nouveau_hwmon_get_pwm1_max,
			  nouveau_hwmon_set_pwm1_max, 0);

अटल काष्ठा attribute *pwm_fan_sensor_attrs[] = अणु
	&sensor_dev_attr_pwm1_min.dev_attr.attr,
	&sensor_dev_attr_pwm1_max.dev_attr.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group pwm_fan_sensor_group = अणु
	.attrs = pwm_fan_sensor_attrs,
पूर्ण;

अटल काष्ठा attribute *temp1_स्वतः_poपूर्णांक_sensor_attrs[] = अणु
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group temp1_स्वतः_poपूर्णांक_sensor_group = अणु
	.attrs = temp1_स्वतः_poपूर्णांक_sensor_attrs,
पूर्ण;

#घोषणा N_ATTR_GROUPS   3

अटल स्थिर u32 nouveau_config_chip[] = अणु
	HWMON_C_UPDATE_INTERVAL,
	0
पूर्ण;

अटल स्थिर u32 nouveau_config_in[] = अणु
	HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_LABEL,
	0
पूर्ण;

अटल स्थिर u32 nouveau_config_temp[] = अणु
	HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
	HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_EMERGENCY |
	HWMON_T_EMERGENCY_HYST,
	0
पूर्ण;

अटल स्थिर u32 nouveau_config_fan[] = अणु
	HWMON_F_INPUT,
	0
पूर्ण;

अटल स्थिर u32 nouveau_config_pwm[] = अणु
	HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
	0
पूर्ण;

अटल स्थिर u32 nouveau_config_घातer[] = अणु
	HWMON_P_INPUT | HWMON_P_CAP_MAX | HWMON_P_CRIT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nouveau_chip = अणु
	.type = hwmon_chip,
	.config = nouveau_config_chip,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nouveau_temp = अणु
	.type = hwmon_temp,
	.config = nouveau_config_temp,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nouveau_fan = अणु
	.type = hwmon_fan,
	.config = nouveau_config_fan,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nouveau_in = अणु
	.type = hwmon_in,
	.config = nouveau_config_in,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nouveau_pwm = अणु
	.type = hwmon_pwm,
	.config = nouveau_config_pwm,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nouveau_घातer = अणु
	.type = hwmon_घातer,
	.config = nouveau_config_घातer,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *nouveau_info[] = अणु
	&nouveau_chip,
	&nouveau_temp,
	&nouveau_fan,
	&nouveau_in,
	&nouveau_pwm,
	&nouveau_घातer,
	शून्य
पूर्ण;

अटल umode_t
nouveau_chip_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t
nouveau_घातer_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm((काष्ठा drm_device *)data);
	काष्ठा nvkm_iccsense *iccsense = nvxx_iccsense(&drm->client.device);

	अगर (!iccsense || !iccsense->data_valid || list_empty(&iccsense->rails))
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		वापस 0444;
	हाल hwmon_घातer_max:
		अगर (iccsense->घातer_w_max)
			वापस 0444;
		वापस 0;
	हाल hwmon_घातer_crit:
		अगर (iccsense->घातer_w_crit)
			वापस 0444;
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t
nouveau_temp_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm((काष्ठा drm_device *)data);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm || !therm->attr_get || nvkm_therm_temp_get(therm) < 0)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस 0444;
	हाल hwmon_temp_max:
	हाल hwmon_temp_max_hyst:
	हाल hwmon_temp_crit:
	हाल hwmon_temp_crit_hyst:
	हाल hwmon_temp_emergency:
	हाल hwmon_temp_emergency_hyst:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t
nouveau_pwm_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm((काष्ठा drm_device *)data);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm || !therm->attr_get || !therm->fan_get ||
	    therm->fan_get(therm) < 0)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_pwm_enable:
	हाल hwmon_pwm_input:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t
nouveau_input_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm((काष्ठा drm_device *)data);
	काष्ठा nvkm_volt *volt = nvxx_volt(&drm->client.device);

	अगर (!volt || nvkm_volt_get(volt) < 0)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_in_input:
	हाल hwmon_in_label:
	हाल hwmon_in_min:
	हाल hwmon_in_max:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t
nouveau_fan_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm((काष्ठा drm_device *)data);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm || !therm->attr_get || nvkm_therm_fan_sense(therm) < 0)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_fan_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
nouveau_chip_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		*val = 1000;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_temp_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	पूर्णांक ret;

	अगर (!therm || !therm->attr_get)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (drm_dev->चयन_घातer_state != DRM_SWITCH_POWER_ON)
			वापस -EINVAL;
		ret = nvkm_therm_temp_get(therm);
		*val = ret < 0 ? ret : (ret * 1000);
		अवरोध;
	हाल hwmon_temp_max:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_THRS_DOWN_CLK)
					* 1000;
		अवरोध;
	हाल hwmon_temp_max_hyst:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST)
					* 1000;
		अवरोध;
	हाल hwmon_temp_crit:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_THRS_CRITICAL)
					* 1000;
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_THRS_CRITICAL_HYST)
					* 1000;
		अवरोध;
	हाल hwmon_temp_emergency:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_THRS_SHUTDOWN)
					* 1000;
		अवरोध;
	हाल hwmon_temp_emergency_hyst:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST)
					* 1000;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_fan_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_fan_input:
		अगर (drm_dev->चयन_घातer_state != DRM_SWITCH_POWER_ON)
			वापस -EINVAL;
		*val = nvkm_therm_fan_sense(therm);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_in_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_volt *volt = nvxx_volt(&drm->client.device);
	पूर्णांक ret;

	अगर (!volt)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_in_input:
		अगर (drm_dev->चयन_घातer_state != DRM_SWITCH_POWER_ON)
			वापस -EINVAL;
		ret = nvkm_volt_get(volt);
		*val = ret < 0 ? ret : (ret / 1000);
		अवरोध;
	हाल hwmon_in_min:
		*val = volt->min_uv > 0 ? (volt->min_uv / 1000) : -ENODEV;
		अवरोध;
	हाल hwmon_in_max:
		*val = volt->max_uv > 0 ? (volt->max_uv / 1000) : -ENODEV;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_pwm_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm || !therm->attr_get || !therm->fan_get)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_pwm_enable:
		*val = therm->attr_get(therm, NVKM_THERM_ATTR_FAN_MODE);
		अवरोध;
	हाल hwmon_pwm_input:
		अगर (drm_dev->चयन_घातer_state != DRM_SWITCH_POWER_ON)
			वापस -EINVAL;
		*val = therm->fan_get(therm);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_घातer_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_iccsense *iccsense = nvxx_iccsense(&drm->client.device);

	अगर (!iccsense)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		अगर (drm_dev->चयन_घातer_state != DRM_SWITCH_POWER_ON)
			वापस -EINVAL;
		*val = nvkm_iccsense_पढ़ो_all(iccsense);
		अवरोध;
	हाल hwmon_घातer_max:
		*val = iccsense->घातer_w_max;
		अवरोध;
	हाल hwmon_घातer_crit:
		*val = iccsense->घातer_w_crit;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_temp_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm || !therm->attr_set)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_max:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_THRS_DOWN_CLK,
					val / 1000);
	हाल hwmon_temp_max_hyst:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST,
					val / 1000);
	हाल hwmon_temp_crit:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_THRS_CRITICAL,
					val / 1000);
	हाल hwmon_temp_crit_hyst:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_THRS_CRITICAL_HYST,
					val / 1000);
	हाल hwmon_temp_emergency:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_THRS_SHUTDOWN,
					val / 1000);
	हाल hwmon_temp_emergency_hyst:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST,
					val / 1000);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nouveau_pwm_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);

	अगर (!therm || !therm->attr_set)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		वापस therm->fan_set(therm, val);
	हाल hwmon_pwm_enable:
		वापस therm->attr_set(therm, NVKM_THERM_ATTR_FAN_MODE, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t
nouveau_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type, u32 attr,
			पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस nouveau_chip_is_visible(data, attr, channel);
	हाल hwmon_temp:
		वापस nouveau_temp_is_visible(data, attr, channel);
	हाल hwmon_fan:
		वापस nouveau_fan_is_visible(data, attr, channel);
	हाल hwmon_in:
		वापस nouveau_input_is_visible(data, attr, channel);
	हाल hwmon_pwm:
		वापस nouveau_pwm_is_visible(data, attr, channel);
	हाल hwmon_घातer:
		वापस nouveau_घातer_is_visible(data, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर input_label[] = "GPU core";

अटल पूर्णांक
nouveau_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
		    पूर्णांक channel, स्थिर अक्षर **buf)
अणु
	अगर (type == hwmon_in && attr == hwmon_in_label) अणु
		*buf = input_label;
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
nouveau_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
							पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस nouveau_chip_पढ़ो(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस nouveau_temp_पढ़ो(dev, attr, channel, val);
	हाल hwmon_fan:
		वापस nouveau_fan_पढ़ो(dev, attr, channel, val);
	हाल hwmon_in:
		वापस nouveau_in_पढ़ो(dev, attr, channel, val);
	हाल hwmon_pwm:
		वापस nouveau_pwm_पढ़ो(dev, attr, channel, val);
	हाल hwmon_घातer:
		वापस nouveau_घातer_पढ़ो(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nouveau_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
							पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		वापस nouveau_temp_ग_लिखो(dev, attr, channel, val);
	हाल hwmon_pwm:
		वापस nouveau_pwm_ग_लिखो(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_ops nouveau_hwmon_ops = अणु
	.is_visible = nouveau_is_visible,
	.पढ़ो = nouveau_पढ़ो,
	.पढ़ो_string = nouveau_पढ़ो_string,
	.ग_लिखो = nouveau_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info nouveau_chip_info = अणु
	.ops = &nouveau_hwmon_ops,
	.info = nouveau_info,
पूर्ण;
#पूर्ण_अगर

पूर्णांक
nouveau_hwmon_init(काष्ठा drm_device *dev)
अणु
#अगर defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_iccsense *iccsense = nvxx_iccsense(&drm->client.device);
	काष्ठा nvkm_therm *therm = nvxx_therm(&drm->client.device);
	काष्ठा nvkm_volt *volt = nvxx_volt(&drm->client.device);
	स्थिर काष्ठा attribute_group *special_groups[N_ATTR_GROUPS];
	काष्ठा nouveau_hwmon *hwmon;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret = 0;
	पूर्णांक i = 0;

	अगर (!iccsense && !therm && !volt) अणु
		NV_DEBUG(drm, "Skipping hwmon registration\n");
		वापस 0;
	पूर्ण

	hwmon = drm->hwmon = kzalloc(माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;
	hwmon->dev = dev;

	अगर (therm && therm->attr_get && therm->attr_set) अणु
		अगर (nvkm_therm_temp_get(therm) >= 0)
			special_groups[i++] = &temp1_स्वतः_poपूर्णांक_sensor_group;
		अगर (therm->fan_get && therm->fan_get(therm) >= 0)
			special_groups[i++] = &pwm_fan_sensor_group;
	पूर्ण

	special_groups[i] = शून्य;
	hwmon_dev = hwmon_device_रेजिस्टर_with_info(dev->dev, "nouveau", dev,
							&nouveau_chip_info,
							special_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		ret = PTR_ERR(hwmon_dev);
		NV_ERROR(drm, "Unable to register hwmon device: %d\n", ret);
		वापस ret;
	पूर्ण

	hwmon->hwmon = hwmon_dev;
	वापस 0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम
nouveau_hwmon_fini(काष्ठा drm_device *dev)
अणु
#अगर defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))
	काष्ठा nouveau_hwmon *hwmon = nouveau_hwmon(dev);

	अगर (!hwmon)
		वापस;

	अगर (hwmon->hwmon)
		hwmon_device_unरेजिस्टर(hwmon->hwmon);

	nouveau_drm(dev)->hwmon = शून्य;
	kमुक्त(hwmon);
#पूर्ण_अगर
पूर्ण
