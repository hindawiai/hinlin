<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-2021 Intel Corporation.

/*
 * SDW Intel ACPI scan helpers
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/module.h>
#समावेश <linux/soundwire/sdw_पूर्णांकel.h>
#समावेश <linux/माला.स>

#घोषणा SDW_LINK_TYPE		4 /* from Intel ACPI करोcumentation */
#घोषणा SDW_MAX_LINKS		4

अटल पूर्णांक ctrl_link_mask;
module_param_named(sdw_link_mask, ctrl_link_mask, पूर्णांक, 0444);
MODULE_PARM_DESC(sdw_link_mask, "Intel link mask (one bit per link)");

अटल bool is_link_enabled(काष्ठा fwnode_handle *fw_node, पूर्णांक i)
अणु
	काष्ठा fwnode_handle *link;
	अक्षर name[32];
	u32 quirk_mask = 0;

	/* Find master handle */
	snम_लिखो(name, माप(name),
		 "mipi-sdw-link-%d-subproperties", i);

	link = fwnode_get_named_child_node(fw_node, name);
	अगर (!link)
		वापस false;

	fwnode_property_पढ़ो_u32(link,
				 "intel-quirk-mask",
				 &quirk_mask);

	अगर (quirk_mask & SDW_INTEL_QUIRK_MASK_BUS_DISABLE)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
sdw_पूर्णांकel_scan_controller(काष्ठा sdw_पूर्णांकel_acpi_info *info)
अणु
	काष्ठा acpi_device *adev;
	पूर्णांक ret, i;
	u8 count;

	अगर (acpi_bus_get_device(info->handle, &adev))
		वापस -EINVAL;

	/* Found controller, find links supported */
	count = 0;
	ret = fwnode_property_पढ़ो_u8_array(acpi_fwnode_handle(adev),
					    "mipi-sdw-master-count", &count, 1);

	/*
	 * In theory we could check the number of links supported in
	 * hardware, but in that step we cannot assume SoundWire IP is
	 * घातered.
	 *
	 * In addition, अगर the BIOS करोesn't even provide this
	 * 'master-count' property then all the inits based on link
	 * masks will fail as well.
	 *
	 * We will check the hardware capabilities in the startup() step
	 */

	अगर (ret) अणु
		dev_err(&adev->dev,
			"Failed to read mipi-sdw-master-count: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	/* Check count is within bounds */
	अगर (count > SDW_MAX_LINKS) अणु
		dev_err(&adev->dev, "Link count %d exceeds max %d\n",
			count, SDW_MAX_LINKS);
		वापस -EINVAL;
	पूर्ण

	अगर (!count) अणु
		dev_warn(&adev->dev, "No SoundWire links detected\n");
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&adev->dev, "ACPI reports %d SDW Link devices\n", count);

	info->count = count;
	info->link_mask = 0;

	क्रम (i = 0; i < count; i++) अणु
		अगर (ctrl_link_mask && !(ctrl_link_mask & BIT(i))) अणु
			dev_dbg(&adev->dev,
				"Link %d masked, will not be enabled\n", i);
			जारी;
		पूर्ण

		अगर (!is_link_enabled(acpi_fwnode_handle(adev), i)) अणु
			dev_dbg(&adev->dev,
				"Link %d not selected in firmware\n", i);
			जारी;
		पूर्ण

		info->link_mask |= BIT(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल acpi_status sdw_पूर्णांकel_acpi_cb(acpi_handle handle, u32 level,
				     व्योम *cdata, व्योम **वापस_value)
अणु
	काष्ठा sdw_पूर्णांकel_acpi_info *info = cdata;
	काष्ठा acpi_device *adev;
	acpi_status status;
	u64 adr;

	status = acpi_evaluate_पूर्णांकeger(handle, METHOD_NAME__ADR, शून्य, &adr);
	अगर (ACPI_FAILURE(status))
		वापस AE_OK; /* keep going */

	अगर (acpi_bus_get_device(handle, &adev)) अणु
		pr_err("%s: Couldn't find ACPI handle\n", __func__);
		वापस AE_NOT_FOUND;
	पूर्ण

	info->handle = handle;

	/*
	 * On some Intel platक्रमms, multiple children of the HDAS
	 * device can be found, but only one of them is the SoundWire
	 * controller. The SNDW device is always exposed with
	 * Name(_ADR, 0x40000000), with bits 31..28 representing the
	 * SoundWire link so filter accordingly
	 */
	अगर (FIELD_GET(GENMASK(31, 28), adr) != SDW_LINK_TYPE)
		वापस AE_OK; /* keep going */

	/* device found, stop namespace walk */
	वापस AE_CTRL_TERMINATE;
पूर्ण

/**
 * sdw_पूर्णांकel_acpi_scan() - SoundWire Intel init routine
 * @parent_handle: ACPI parent handle
 * @info: description of what firmware/DSDT tables expose
 *
 * This scans the namespace and queries firmware to figure out which
 * links to enable. A follow-up use of sdw_पूर्णांकel_probe() and
 * sdw_पूर्णांकel_startup() is required क्रम creation of devices and bus
 * startup
 */
पूर्णांक sdw_पूर्णांकel_acpi_scan(acpi_handle *parent_handle,
			काष्ठा sdw_पूर्णांकel_acpi_info *info)
अणु
	acpi_status status;

	info->handle = शून्य;
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE,
				     parent_handle, 1,
				     sdw_पूर्णांकel_acpi_cb,
				     शून्य, info, शून्य);
	अगर (ACPI_FAILURE(status) || info->handle == शून्य)
		वापस -ENODEV;

	वापस sdw_पूर्णांकel_scan_controller(info);
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_acpi_scan, SND_INTEL_SOUNDWIRE_ACPI);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Intel Soundwire ACPI helpers");
