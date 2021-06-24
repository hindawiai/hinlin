<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Slim Bootloader(SBL) firmware update संकेतing driver
 *
 * Slim Bootloader is a small, खोलो-source, non UEFI compliant, boot firmware
 * optimized क्रम running on certain Intel platक्रमms.
 *
 * SBL exposes an ACPI-WMI device via /sys/bus/wmi/devices/<INTEL_WMI_SBL_GUID>.
 * This driver further adds "firmware_update_request" device attribute.
 * This attribute normally has a value of 0 and userspace can संकेत SBL
 * to update firmware, on next reboot, by writing a value of 1.
 *
 * More details of SBL firmware update process is available at:
 * https://slimbootloader.github.io/security/firmware-update.hपंचांगl
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/wmi.h>

#घोषणा INTEL_WMI_SBL_GUID  "44FADEB1-B204-40F2-8581-394BBDC1B651"

अटल पूर्णांक get_fwu_request(काष्ठा device *dev, u32 *out)
अणु
	काष्ठा acpi_buffer result = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_query_block(INTEL_WMI_SBL_GUID, 0, &result);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "wmi_query_block failed\n");
		वापस -ENODEV;
	पूर्ण

	obj = (जोड़ acpi_object *)result.poपूर्णांकer;
	अगर (!obj || obj->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "wmi_query_block returned invalid value\n");
		kमुक्त(obj);
		वापस -EINVAL;
	पूर्ण

	*out = obj->पूर्णांकeger.value;
	kमुक्त(obj);

	वापस 0;
पूर्ण

अटल पूर्णांक set_fwu_request(काष्ठा device *dev, u32 in)
अणु
	काष्ठा acpi_buffer input;
	acpi_status status;
	u32 value;

	value = in;
	input.length = माप(u32);
	input.poपूर्णांकer = &value;

	status = wmi_set_block(INTEL_WMI_SBL_GUID, 0, &input);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "wmi_set_block failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार firmware_update_request_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	u32 val;
	पूर्णांक ret;

	ret = get_fwu_request(dev, &val);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार firmware_update_request_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	/* May later be extended to support values other than 0 and 1 */
	अगर (val > 1)
		वापस -दुस्फल;

	ret = set_fwu_request(dev, val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(firmware_update_request);

अटल काष्ठा attribute *firmware_update_attrs[] = अणु
	&dev_attr_firmware_update_request.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(firmware_update);

अटल पूर्णांक पूर्णांकel_wmi_sbl_fw_update_probe(काष्ठा wmi_device *wdev,
					 स्थिर व्योम *context)
अणु
	dev_info(&wdev->dev, "Slim Bootloader signaling driver attached\n");
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_wmi_sbl_fw_update_हटाओ(काष्ठा wmi_device *wdev)
अणु
	dev_info(&wdev->dev, "Slim Bootloader signaling driver removed\n");
पूर्ण

अटल स्थिर काष्ठा wmi_device_id पूर्णांकel_wmi_sbl_id_table[] = अणु
	अणु .guid_string = INTEL_WMI_SBL_GUID पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(wmi, पूर्णांकel_wmi_sbl_id_table);

अटल काष्ठा wmi_driver पूर्णांकel_wmi_sbl_fw_update_driver = अणु
	.driver = अणु
		.name = "intel-wmi-sbl-fw-update",
		.dev_groups = firmware_update_groups,
	पूर्ण,
	.probe = पूर्णांकel_wmi_sbl_fw_update_probe,
	.हटाओ = पूर्णांकel_wmi_sbl_fw_update_हटाओ,
	.id_table = पूर्णांकel_wmi_sbl_id_table,
पूर्ण;
module_wmi_driver(पूर्णांकel_wmi_sbl_fw_update_driver);

MODULE_AUTHOR("Jithu Joseph <jithu.joseph@intel.com>");
MODULE_DESCRIPTION("Slim Bootloader firmware update signaling driver");
MODULE_LICENSE("GPL v2");
