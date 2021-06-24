<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2021 Thomas Weiथschuh <thomas@weissschuh.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/wmi.h>

#घोषणा GIGABYTE_WMI_GUID	"DEADBEEF-2001-0000-00A0-C90629100000"
#घोषणा NUM_TEMPERATURE_SENSORS	6

अटल bool क्रमce_load;
module_param(क्रमce_load, bool, 0444);
MODULE_PARM_DESC(क्रमce_load, "Force loading on unknown platform");

अटल u8 usable_sensors_mask;

क्रमागत gigabyte_wmi_commandtype अणु
	GIGABYTE_WMI_BUILD_DATE_QUERY       =   0x1,
	GIGABYTE_WMI_MAINBOARD_TYPE_QUERY   =   0x2,
	GIGABYTE_WMI_FIRMWARE_VERSION_QUERY =   0x4,
	GIGABYTE_WMI_MAINBOARD_NAME_QUERY   =   0x5,
	GIGABYTE_WMI_TEMPERATURE_QUERY      = 0x125,
पूर्ण;

काष्ठा gigabyte_wmi_args अणु
	u32 arg1;
पूर्ण;

अटल पूर्णांक gigabyte_wmi_perक्रमm_query(काष्ठा wmi_device *wdev,
				      क्रमागत gigabyte_wmi_commandtype command,
				      काष्ठा gigabyte_wmi_args *args, काष्ठा acpi_buffer *out)
अणु
	स्थिर काष्ठा acpi_buffer in = अणु
		.length = माप(*args),
		.poपूर्णांकer = args,
	पूर्ण;

	acpi_status ret = wmidev_evaluate_method(wdev, 0x0, command, &in, out);

	अगर (ACPI_FAILURE(ret))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक gigabyte_wmi_query_पूर्णांकeger(काष्ठा wmi_device *wdev,
				      क्रमागत gigabyte_wmi_commandtype command,
				      काष्ठा gigabyte_wmi_args *args, u64 *res)
अणु
	जोड़ acpi_object *obj;
	काष्ठा acpi_buffer result = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	पूर्णांक ret;

	ret = gigabyte_wmi_perक्रमm_query(wdev, command, args, &result);
	अगर (ret)
		वापस ret;
	obj = result.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_INTEGER)
		*res = obj->पूर्णांकeger.value;
	अन्यथा
		ret = -EIO;
	kमुक्त(result.poपूर्णांकer);
	वापस ret;
पूर्ण

अटल पूर्णांक gigabyte_wmi_temperature(काष्ठा wmi_device *wdev, u8 sensor, दीर्घ *res)
अणु
	काष्ठा gigabyte_wmi_args args = अणु
		.arg1 = sensor,
	पूर्ण;
	u64 temp;
	acpi_status ret;

	ret = gigabyte_wmi_query_पूर्णांकeger(wdev, GIGABYTE_WMI_TEMPERATURE_QUERY, &args, &temp);
	अगर (ret == 0) अणु
		अगर (temp == 0)
			वापस -ENODEV;
		*res = (s8)temp * 1000; // value is a चिन्हित 8-bit पूर्णांकeger
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gigabyte_wmi_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा wmi_device *wdev = dev_get_drvdata(dev);

	वापस gigabyte_wmi_temperature(wdev, channel, val);
पूर्ण

अटल umode_t gigabyte_wmi_hwmon_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
					     u32 attr, पूर्णांक channel)
अणु
	वापस usable_sensors_mask & BIT(channel) ? 0444  : 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *gigabyte_wmi_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops gigabyte_wmi_hwmon_ops = अणु
	.पढ़ो = gigabyte_wmi_hwmon_पढ़ो,
	.is_visible = gigabyte_wmi_hwmon_is_visible,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info gigabyte_wmi_hwmon_chip_info = अणु
	.ops = &gigabyte_wmi_hwmon_ops,
	.info = gigabyte_wmi_hwmon_info,
पूर्ण;

अटल u8 gigabyte_wmi_detect_sensor_usability(काष्ठा wmi_device *wdev)
अणु
	पूर्णांक i;
	दीर्घ temp;
	u8 r = 0;

	क्रम (i = 0; i < NUM_TEMPERATURE_SENSORS; i++) अणु
		अगर (!gigabyte_wmi_temperature(wdev, i, &temp))
			r |= BIT(i);
	पूर्ण
	वापस r;
पूर्ण

#घोषणा DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME(name) \
	अणु .matches = अणु \
		DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co., Ltd."), \
		DMI_EXACT_MATCH(DMI_BOARD_NAME, name), \
	पूर्णपूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id gigabyte_wmi_known_working_platक्रमms[] = अणु
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("B550 AORUS ELITE"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("B550 GAMING X V2"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("B550M AORUS PRO-P"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("B550M DS3H"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("Z390 I AORUS PRO WIFI-CF"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("X570 AORUS ELITE"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("X570 I AORUS PRO WIFI"),
	DMI_EXACT_MATCH_GIGABYTE_BOARD_NAME("X570 UD"),
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक gigabyte_wmi_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	काष्ठा device *hwmon_dev;

	अगर (!dmi_check_प्रणाली(gigabyte_wmi_known_working_platक्रमms)) अणु
		अगर (!क्रमce_load)
			वापस -ENODEV;
		dev_warn(&wdev->dev, "Forcing load on unknown platform");
	पूर्ण

	usable_sensors_mask = gigabyte_wmi_detect_sensor_usability(wdev);
	अगर (!usable_sensors_mask) अणु
		dev_info(&wdev->dev, "No temperature sensors usable");
		वापस -ENODEV;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&wdev->dev, "gigabyte_wmi", wdev,
							 &gigabyte_wmi_hwmon_chip_info, शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id gigabyte_wmi_id_table[] = अणु
	अणु GIGABYTE_WMI_GUID, शून्य पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा wmi_driver gigabyte_wmi_driver = अणु
	.driver = अणु
		.name = "gigabyte-wmi",
	पूर्ण,
	.id_table = gigabyte_wmi_id_table,
	.probe = gigabyte_wmi_probe,
पूर्ण;
module_wmi_driver(gigabyte_wmi_driver);

MODULE_DEVICE_TABLE(wmi, gigabyte_wmi_id_table);
MODULE_AUTHOR("Thomas Weiथschuh <thomas@weissschuh.net>");
MODULE_DESCRIPTION("Gigabyte WMI temperature driver");
MODULE_LICENSE("GPL");
