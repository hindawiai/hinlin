<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVM Express hardware monitoring support
 * Copyright (c) 2019, Guenter Roeck
 */

#समावेश <linux/hwmon.h>
#समावेश <linux/units.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "nvme.h"

काष्ठा nvme_hwmon_data अणु
	काष्ठा nvme_ctrl *ctrl;
	काष्ठा nvme_smart_log log;
	काष्ठा mutex पढ़ो_lock;
पूर्ण;

अटल पूर्णांक nvme_get_temp_thresh(काष्ठा nvme_ctrl *ctrl, पूर्णांक sensor, bool under,
				दीर्घ *temp)
अणु
	अचिन्हित पूर्णांक threshold = sensor << NVME_TEMP_THRESH_SELECT_SHIFT;
	u32 status;
	पूर्णांक ret;

	अगर (under)
		threshold |= NVME_TEMP_THRESH_TYPE_UNDER;

	ret = nvme_get_features(ctrl, NVME_FEAT_TEMP_THRESH, threshold, शून्य, 0,
				&status);
	अगर (ret > 0)
		वापस -EIO;
	अगर (ret < 0)
		वापस ret;
	*temp = kelvin_to_millicelsius(status & NVME_TEMP_THRESH_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_set_temp_thresh(काष्ठा nvme_ctrl *ctrl, पूर्णांक sensor, bool under,
				दीर्घ temp)
अणु
	अचिन्हित पूर्णांक threshold = sensor << NVME_TEMP_THRESH_SELECT_SHIFT;
	पूर्णांक ret;

	temp = millicelsius_to_kelvin(temp);
	threshold |= clamp_val(temp, 0, NVME_TEMP_THRESH_MASK);

	अगर (under)
		threshold |= NVME_TEMP_THRESH_TYPE_UNDER;

	ret = nvme_set_features(ctrl, NVME_FEAT_TEMP_THRESH, threshold, शून्य, 0,
				शून्य);
	अगर (ret > 0)
		वापस -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक nvme_hwmon_get_smart_log(काष्ठा nvme_hwmon_data *data)
अणु
	वापस nvme_get_log(data->ctrl, NVME_NSID_ALL, NVME_LOG_SMART, 0,
			   NVME_CSI_NVM, &data->log, माप(data->log), 0);
पूर्ण

अटल पूर्णांक nvme_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			   u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा nvme_hwmon_data *data = dev_get_drvdata(dev);
	काष्ठा nvme_smart_log *log = &data->log;
	पूर्णांक temp;
	पूर्णांक err;

	/*
	 * First handle attributes which करोn't require us to पढ़ो
	 * the smart log.
	 */
	चयन (attr) अणु
	हाल hwmon_temp_max:
		वापस nvme_get_temp_thresh(data->ctrl, channel, false, val);
	हाल hwmon_temp_min:
		वापस nvme_get_temp_thresh(data->ctrl, channel, true, val);
	हाल hwmon_temp_crit:
		*val = kelvin_to_millicelsius(data->ctrl->cctemp);
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	mutex_lock(&data->पढ़ो_lock);
	err = nvme_hwmon_get_smart_log(data);
	अगर (err)
		जाओ unlock;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (!channel)
			temp = get_unaligned_le16(log->temperature);
		अन्यथा
			temp = le16_to_cpu(log->temp_sensor[channel - 1]);
		*val = kelvin_to_millicelsius(temp);
		अवरोध;
	हाल hwmon_temp_alarm:
		*val = !!(log->critical_warning & NVME_SMART_CRIT_TEMPERATURE);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
unlock:
	mutex_unlock(&data->पढ़ो_lock);
	वापस err;
पूर्ण

अटल पूर्णांक nvme_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			    u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा nvme_hwmon_data *data = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_temp_max:
		वापस nvme_set_temp_thresh(data->ctrl, channel, false, val);
	हाल hwmon_temp_min:
		वापस nvme_set_temp_thresh(data->ctrl, channel, true, val);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर अक्षर * स्थिर nvme_hwmon_sensor_names[] = अणु
	"Composite",
	"Sensor 1",
	"Sensor 2",
	"Sensor 3",
	"Sensor 4",
	"Sensor 5",
	"Sensor 6",
	"Sensor 7",
	"Sensor 8",
पूर्ण;

अटल पूर्णांक nvme_hwmon_पढ़ो_string(काष्ठा device *dev,
				  क्रमागत hwmon_sensor_types type, u32 attr,
				  पूर्णांक channel, स्थिर अक्षर **str)
अणु
	*str = nvme_hwmon_sensor_names[channel];
	वापस 0;
पूर्ण

अटल umode_t nvme_hwmon_is_visible(स्थिर व्योम *_data,
				     क्रमागत hwmon_sensor_types type,
				     u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा nvme_hwmon_data *data = _data;

	चयन (attr) अणु
	हाल hwmon_temp_crit:
		अगर (!channel && data->ctrl->cctemp)
			वापस 0444;
		अवरोध;
	हाल hwmon_temp_max:
	हाल hwmon_temp_min:
		अगर ((!channel && data->ctrl->wctemp) ||
		    (channel && data->log.temp_sensor[channel - 1])) अणु
			अगर (data->ctrl->quirks &
			    NVME_QUIRK_NO_TEMP_THRESH_CHANGE)
				वापस 0444;
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_temp_alarm:
		अगर (!channel)
			वापस 0444;
		अवरोध;
	हाल hwmon_temp_input:
	हाल hwmon_temp_label:
		अगर (!channel || data->log.temp_sensor[channel - 1])
			वापस 0444;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *nvme_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_CRIT | HWMON_T_LABEL | HWMON_T_ALARM,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops nvme_hwmon_ops = अणु
	.is_visible	= nvme_hwmon_is_visible,
	.पढ़ो		= nvme_hwmon_पढ़ो,
	.पढ़ो_string	= nvme_hwmon_पढ़ो_string,
	.ग_लिखो		= nvme_hwmon_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info nvme_hwmon_chip_info = अणु
	.ops	= &nvme_hwmon_ops,
	.info	= nvme_hwmon_info,
पूर्ण;

पूर्णांक nvme_hwmon_init(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा device *dev = ctrl->device;
	काष्ठा nvme_hwmon_data *data;
	काष्ठा device *hwmon;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस 0;

	data->ctrl = ctrl;
	mutex_init(&data->पढ़ो_lock);

	err = nvme_hwmon_get_smart_log(data);
	अगर (err) अणु
		dev_warn(dev, "Failed to read smart log (error %d)\n", err);
		kमुक्त(data);
		वापस err;
	पूर्ण

	hwmon = hwmon_device_रेजिस्टर_with_info(dev, "nvme",
						data, &nvme_hwmon_chip_info,
						शून्य);
	अगर (IS_ERR(hwmon)) अणु
		dev_warn(dev, "Failed to instantiate hwmon device\n");
		kमुक्त(data);
		वापस PTR_ERR(hwmon);
	पूर्ण
	ctrl->hwmon_device = hwmon;
	वापस 0;
पूर्ण

व्योम nvme_hwmon_निकास(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (ctrl->hwmon_device) अणु
		काष्ठा nvme_hwmon_data *data =
			dev_get_drvdata(ctrl->hwmon_device);

		hwmon_device_unरेजिस्टर(ctrl->hwmon_device);
		ctrl->hwmon_device = शून्य;
		kमुक्त(data);
	पूर्ण
पूर्ण
