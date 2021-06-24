<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"

#समावेश <linux/pci.h>
#समावेश <linux/hwmon.h>

#घोषणा HWMON_NR_SENSOR_TYPES		(hwmon_pwm + 1)

पूर्णांक hl_build_hwmon_channel_info(काष्ठा hl_device *hdev,
				काष्ठा cpucp_sensor *sensors_arr)
अणु
	u32 counts[HWMON_NR_SENSOR_TYPES] = अणु0पूर्ण;
	u32 *sensors_by_type[HWMON_NR_SENSOR_TYPES] = अणुशून्यपूर्ण;
	u32 sensors_by_type_next_index[HWMON_NR_SENSOR_TYPES] = अणु0पूर्ण;
	काष्ठा hwmon_channel_info **channels_info;
	u32 num_sensors_क्रम_type, num_active_sensor_types = 0,
			arr_size = 0, *curr_arr;
	क्रमागत hwmon_sensor_types type;
	पूर्णांक rc, i, j;

	क्रम (i = 0 ; i < CPUCP_MAX_SENSORS ; i++) अणु
		type = le32_to_cpu(sensors_arr[i].type);

		अगर ((type == 0) && (sensors_arr[i].flags == 0))
			अवरोध;

		अगर (type >= HWMON_NR_SENSOR_TYPES) अणु
			dev_err(hdev->dev,
				"Got wrong sensor type %d from device\n", type);
			वापस -EINVAL;
		पूर्ण

		counts[type]++;
		arr_size++;
	पूर्ण

	क्रम (i = 0 ; i < HWMON_NR_SENSOR_TYPES ; i++) अणु
		अगर (counts[i] == 0)
			जारी;

		num_sensors_क्रम_type = counts[i] + 1;
		curr_arr = kसुस्मृति(num_sensors_क्रम_type, माप(*curr_arr),
				GFP_KERNEL);
		अगर (!curr_arr) अणु
			rc = -ENOMEM;
			जाओ sensors_type_err;
		पूर्ण

		num_active_sensor_types++;
		sensors_by_type[i] = curr_arr;
	पूर्ण

	क्रम (i = 0 ; i < arr_size ; i++) अणु
		type = le32_to_cpu(sensors_arr[i].type);
		curr_arr = sensors_by_type[type];
		curr_arr[sensors_by_type_next_index[type]++] =
				le32_to_cpu(sensors_arr[i].flags);
	पूर्ण

	channels_info = kसुस्मृति(num_active_sensor_types + 1,
			माप(*channels_info), GFP_KERNEL);
	अगर (!channels_info) अणु
		rc = -ENOMEM;
		जाओ channels_info_array_err;
	पूर्ण

	क्रम (i = 0 ; i < num_active_sensor_types ; i++) अणु
		channels_info[i] = kzalloc(माप(*channels_info[i]),
				GFP_KERNEL);
		अगर (!channels_info[i]) अणु
			rc = -ENOMEM;
			जाओ channel_info_err;
		पूर्ण
	पूर्ण

	क्रम (i = 0, j = 0 ; i < HWMON_NR_SENSOR_TYPES ; i++) अणु
		अगर (!sensors_by_type[i])
			जारी;

		channels_info[j]->type = i;
		channels_info[j]->config = sensors_by_type[i];
		j++;
	पूर्ण

	hdev->hl_chip_info->info =
			(स्थिर काष्ठा hwmon_channel_info **)channels_info;

	वापस 0;

channel_info_err:
	क्रम (i = 0 ; i < num_active_sensor_types ; i++)
		अगर (channels_info[i]) अणु
			kमुक्त(channels_info[i]->config);
			kमुक्त(channels_info[i]);
		पूर्ण
	kमुक्त(channels_info);
channels_info_array_err:
sensors_type_err:
	क्रम (i = 0 ; i < HWMON_NR_SENSOR_TYPES ; i++)
		kमुक्त(sensors_by_type[i]);

	वापस rc;
पूर्ण

अटल पूर्णांक hl_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_max:
		हाल hwmon_temp_crit:
		हाल hwmon_temp_max_hyst:
		हाल hwmon_temp_crit_hyst:
		हाल hwmon_temp_offset:
		हाल hwmon_temp_highest:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		rc = hl_get_temperature(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_min:
		हाल hwmon_in_max:
		हाल hwmon_in_highest:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		rc = hl_get_voltage(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_min:
		हाल hwmon_curr_max:
		हाल hwmon_curr_highest:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		rc = hl_get_current(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_input:
		हाल hwmon_fan_min:
		हाल hwmon_fan_max:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		rc = hl_get_fan_speed(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
		हाल hwmon_pwm_enable:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		rc = hl_get_pwm_info(hdev, channel, attr, val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक hl_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_offset:
		हाल hwmon_temp_reset_history:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		hl_set_temperature(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
		हाल hwmon_pwm_enable:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		hl_set_pwm_info(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_reset_history:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		hl_set_voltage(hdev, channel, attr, val);
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_reset_history:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		hl_set_current(hdev, channel, attr, val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल umode_t hl_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_max:
		हाल hwmon_temp_max_hyst:
		हाल hwmon_temp_crit:
		हाल hwmon_temp_crit_hyst:
		हाल hwmon_temp_highest:
			वापस 0444;
		हाल hwmon_temp_offset:
			वापस 0644;
		हाल hwmon_temp_reset_history:
			वापस 0200;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_min:
		हाल hwmon_in_max:
		हाल hwmon_in_highest:
			वापस 0444;
		हाल hwmon_in_reset_history:
			वापस 0200;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_min:
		हाल hwmon_curr_max:
		हाल hwmon_curr_highest:
			वापस 0444;
		हाल hwmon_curr_reset_history:
			वापस 0200;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_input:
		हाल hwmon_fan_min:
		हाल hwmon_fan_max:
			वापस 0444;
		पूर्ण
		अवरोध;
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
		हाल hwmon_pwm_enable:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops hl_hwmon_ops = अणु
	.is_visible = hl_is_visible,
	.पढ़ो = hl_पढ़ो,
	.ग_लिखो = hl_ग_लिखो
पूर्ण;

पूर्णांक hl_get_temperature(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ *value)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_TEMPERATURE_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	*value = (दीर्घ) result;

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to get temperature from sensor %d, error %d\n",
			sensor_index, rc);
		*value = 0;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक hl_set_temperature(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ value)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_TEMPERATURE_SET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);
	pkt.value = __cpu_to_le64(value);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev,
			"Failed to set temperature of sensor %d, error %d\n",
			sensor_index, rc);

	वापस rc;
पूर्ण

पूर्णांक hl_get_voltage(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ *value)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_VOLTAGE_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	*value = (दीर्घ) result;

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to get voltage from sensor %d, error %d\n",
			sensor_index, rc);
		*value = 0;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक hl_get_current(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ *value)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_CURRENT_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	*value = (दीर्घ) result;

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to get current from sensor %d, error %d\n",
			sensor_index, rc);
		*value = 0;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक hl_get_fan_speed(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ *value)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_FAN_SPEED_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	*value = (दीर्घ) result;

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to get fan speed from sensor %d, error %d\n",
			sensor_index, rc);
		*value = 0;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक hl_get_pwm_info(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ *value)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_PWM_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	*value = (दीर्घ) result;

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to get pwm info from sensor %d, error %d\n",
			sensor_index, rc);
		*value = 0;
	पूर्ण

	वापस rc;
पूर्ण

व्योम hl_set_pwm_info(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr,
			दीर्घ value)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_PWM_SET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);
	pkt.value = cpu_to_le64(value);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev,
			"Failed to set pwm info to sensor %d, error %d\n",
			sensor_index, rc);
पूर्ण

पूर्णांक hl_set_voltage(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ value)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_VOLTAGE_SET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);
	pkt.value = __cpu_to_le64(value);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev,
			"Failed to set voltage of sensor %d, error %d\n",
			sensor_index, rc);

	वापस rc;
पूर्ण

पूर्णांक hl_set_current(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ value)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_CURRENT_SET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);
	pkt.value = __cpu_to_le64(value);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev,
			"Failed to set current of sensor %d, error %d\n",
			sensor_index, rc);

	वापस rc;
पूर्ण

पूर्णांक hl_hwmon_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा device *dev = hdev->pdev ? &hdev->pdev->dev : hdev->dev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक rc;

	अगर ((hdev->hwmon_initialized) || !(hdev->cpu_queues_enable))
		वापस 0;

	अगर (hdev->hl_chip_info->info) अणु
		hdev->hl_chip_info->ops = &hl_hwmon_ops;

		hdev->hwmon_dev = hwmon_device_रेजिस्टर_with_info(dev,
					prop->cpucp_info.card_name, hdev,
					hdev->hl_chip_info, शून्य);
		अगर (IS_ERR(hdev->hwmon_dev)) अणु
			rc = PTR_ERR(hdev->hwmon_dev);
			dev_err(hdev->dev,
				"Unable to register hwmon device: %d\n", rc);
			वापस rc;
		पूर्ण

		dev_info(hdev->dev, "%s: add sensors information\n",
			dev_name(hdev->hwmon_dev));

		hdev->hwmon_initialized = true;
	पूर्ण अन्यथा अणु
		dev_info(hdev->dev, "no available sensors\n");
	पूर्ण

	वापस 0;
पूर्ण

व्योम hl_hwmon_fini(काष्ठा hl_device *hdev)
अणु
	अगर (!hdev->hwmon_initialized)
		वापस;

	hwmon_device_unरेजिस्टर(hdev->hwmon_dev);
पूर्ण
