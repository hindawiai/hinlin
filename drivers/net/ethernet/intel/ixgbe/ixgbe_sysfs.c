<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश "ixgbe_common.h"
#समावेश "ixgbe_type.h"

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hwmon.h>

/* hwmon callback functions */
अटल sमाप_प्रकार ixgbe_hwmon_show_location(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा hwmon_attr *ixgbe_attr = container_of(attr, काष्ठा hwmon_attr,
						     dev_attr);
	वापस प्र_लिखो(buf, "loc%u\n",
		       ixgbe_attr->sensor->location);
पूर्ण

अटल sमाप_प्रकार ixgbe_hwmon_show_temp(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hwmon_attr *ixgbe_attr = container_of(attr, काष्ठा hwmon_attr,
						     dev_attr);
	अचिन्हित पूर्णांक value;

	/* reset the temp field */
	ixgbe_attr->hw->mac.ops.get_thermal_sensor_data(ixgbe_attr->hw);

	value = ixgbe_attr->sensor->temp;

	/* display millidegree */
	value *= 1000;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार ixgbe_hwmon_show_cautionthresh(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hwmon_attr *ixgbe_attr = container_of(attr, काष्ठा hwmon_attr,
						     dev_attr);
	अचिन्हित पूर्णांक value = ixgbe_attr->sensor->caution_thresh;

	/* display millidegree */
	value *= 1000;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार ixgbe_hwmon_show_maxopthresh(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hwmon_attr *ixgbe_attr = container_of(attr, काष्ठा hwmon_attr,
						     dev_attr);
	अचिन्हित पूर्णांक value = ixgbe_attr->sensor->max_op_thresh;

	/* display millidegree */
	value *= 1000;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

/**
 * ixgbe_add_hwmon_attr - Create hwmon attr table क्रम a hwmon sysfs file.
 * @adapter: poपूर्णांकer to the adapter काष्ठाure
 * @offset: offset in the eeprom sensor data table
 * @type: type of sensor data to display
 *
 * For each file we want in hwmon's sysfs पूर्णांकerface we need a device_attribute
 * This is included in our hwmon_attr काष्ठा that contains the references to
 * the data काष्ठाures we need to get the data to display.
 */
अटल पूर्णांक ixgbe_add_hwmon_attr(काष्ठा ixgbe_adapter *adapter,
				अचिन्हित पूर्णांक offset, पूर्णांक type) अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक n_attr;
	काष्ठा hwmon_attr *ixgbe_attr;

	n_attr = adapter->ixgbe_hwmon_buff->n_hwmon;
	ixgbe_attr = &adapter->ixgbe_hwmon_buff->hwmon_list[n_attr];

	चयन (type) अणु
	हाल IXGBE_HWMON_TYPE_LOC:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_location;
		snम_लिखो(ixgbe_attr->name, माप(ixgbe_attr->name),
			 "temp%u_label", offset + 1);
		अवरोध;
	हाल IXGBE_HWMON_TYPE_TEMP:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_temp;
		snम_लिखो(ixgbe_attr->name, माप(ixgbe_attr->name),
			 "temp%u_input", offset + 1);
		अवरोध;
	हाल IXGBE_HWMON_TYPE_CAUTION:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_cautionthresh;
		snम_लिखो(ixgbe_attr->name, माप(ixgbe_attr->name),
			 "temp%u_max", offset + 1);
		अवरोध;
	हाल IXGBE_HWMON_TYPE_MAX:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_maxopthresh;
		snम_लिखो(ixgbe_attr->name, माप(ixgbe_attr->name),
			 "temp%u_crit", offset + 1);
		अवरोध;
	शेष:
		rc = -EPERM;
		वापस rc;
	पूर्ण

	/* These always the same regardless of type */
	ixgbe_attr->sensor =
		&adapter->hw.mac.thermal_sensor_data.sensor[offset];
	ixgbe_attr->hw = &adapter->hw;
	ixgbe_attr->dev_attr.store = शून्य;
	ixgbe_attr->dev_attr.attr.mode = 0444;
	ixgbe_attr->dev_attr.attr.name = ixgbe_attr->name;
	sysfs_attr_init(&ixgbe_attr->dev_attr.attr);

	adapter->ixgbe_hwmon_buff->attrs[n_attr] = &ixgbe_attr->dev_attr.attr;

	++adapter->ixgbe_hwmon_buff->n_hwmon;

	वापस 0;
पूर्ण

अटल व्योम ixgbe_sysfs_del_adapter(काष्ठा ixgbe_adapter *adapter)
अणु
पूर्ण

/* called from ixgbe_मुख्य.c */
व्योम ixgbe_sysfs_निकास(काष्ठा ixgbe_adapter *adapter)
अणु
	ixgbe_sysfs_del_adapter(adapter);
पूर्ण

/* called from ixgbe_मुख्य.c */
पूर्णांक ixgbe_sysfs_init(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा hwmon_buff *ixgbe_hwmon;
	काष्ठा device *hwmon_dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	/* If this method isn't defined we don't support thermals */
	अगर (adapter->hw.mac.ops.init_thermal_sensor_thresh == शून्य) अणु
		जाओ निकास;
	पूर्ण

	/* Don't create thermal hwmon पूर्णांकerface अगर no sensors present */
	अगर (adapter->hw.mac.ops.init_thermal_sensor_thresh(&adapter->hw))
		जाओ निकास;

	ixgbe_hwmon = devm_kzalloc(&adapter->pdev->dev, माप(*ixgbe_hwmon),
				   GFP_KERNEL);
	अगर (ixgbe_hwmon == शून्य) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण
	adapter->ixgbe_hwmon_buff = ixgbe_hwmon;

	क्रम (i = 0; i < IXGBE_MAX_SENSORS; i++) अणु
		/*
		 * Only create hwmon sysfs entries क्रम sensors that have
		 * meaningful data क्रम.
		 */
		अगर (adapter->hw.mac.thermal_sensor_data.sensor[i].location == 0)
			जारी;

		/* Bail अगर any hwmon attr काष्ठा fails to initialize */
		rc = ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_CAUTION);
		अगर (rc)
			जाओ निकास;
		rc = ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_LOC);
		अगर (rc)
			जाओ निकास;
		rc = ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_TEMP);
		अगर (rc)
			जाओ निकास;
		rc = ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_MAX);
		अगर (rc)
			जाओ निकास;
	पूर्ण

	ixgbe_hwmon->groups[0] = &ixgbe_hwmon->group;
	ixgbe_hwmon->group.attrs = ixgbe_hwmon->attrs;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&adapter->pdev->dev,
							   "ixgbe",
							   ixgbe_hwmon,
							   ixgbe_hwmon->groups);
	अगर (IS_ERR(hwmon_dev))
		rc = PTR_ERR(hwmon_dev);
निकास:
	वापस rc;
पूर्ण

