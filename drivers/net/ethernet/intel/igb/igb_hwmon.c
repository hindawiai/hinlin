<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#समावेश "igb.h"
#समावेश "e1000_82575.h"
#समावेश "e1000_hw.h"

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/pci.h>

#अगर_घोषित CONFIG_IGB_HWMON
अटल काष्ठा i2c_board_info i350_sensor_info = अणु
	I2C_BOARD_INFO("i350bb", (0Xf8 >> 1)),
पूर्ण;

/* hwmon callback functions */
अटल sमाप_प्रकार igb_hwmon_show_location(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा hwmon_attr *igb_attr = container_of(attr, काष्ठा hwmon_attr,
						   dev_attr);
	वापस प्र_लिखो(buf, "loc%u\n",
		       igb_attr->sensor->location);
पूर्ण

अटल sमाप_प्रकार igb_hwmon_show_temp(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा hwmon_attr *igb_attr = container_of(attr, काष्ठा hwmon_attr,
						   dev_attr);
	अचिन्हित पूर्णांक value;

	/* reset the temp field */
	igb_attr->hw->mac.ops.get_thermal_sensor_data(igb_attr->hw);

	value = igb_attr->sensor->temp;

	/* display millidegree */
	value *= 1000;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार igb_hwmon_show_cautionthresh(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा hwmon_attr *igb_attr = container_of(attr, काष्ठा hwmon_attr,
						   dev_attr);
	अचिन्हित पूर्णांक value = igb_attr->sensor->caution_thresh;

	/* display millidegree */
	value *= 1000;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार igb_hwmon_show_maxopthresh(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा hwmon_attr *igb_attr = container_of(attr, काष्ठा hwmon_attr,
						   dev_attr);
	अचिन्हित पूर्णांक value = igb_attr->sensor->max_op_thresh;

	/* display millidegree */
	value *= 1000;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

/* igb_add_hwmon_attr - Create hwmon attr table क्रम a hwmon sysfs file.
 * @ adapter: poपूर्णांकer to the adapter काष्ठाure
 * @ offset: offset in the eeprom sensor data table
 * @ type: type of sensor data to display
 *
 * For each file we want in hwmon's sysfs पूर्णांकerface we need a device_attribute
 * This is included in our hwmon_attr काष्ठा that contains the references to
 * the data काष्ठाures we need to get the data to display.
 */
अटल पूर्णांक igb_add_hwmon_attr(काष्ठा igb_adapter *adapter,
			      अचिन्हित पूर्णांक offset, पूर्णांक type)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक n_attr;
	काष्ठा hwmon_attr *igb_attr;

	n_attr = adapter->igb_hwmon_buff->n_hwmon;
	igb_attr = &adapter->igb_hwmon_buff->hwmon_list[n_attr];

	चयन (type) अणु
	हाल IGB_HWMON_TYPE_LOC:
		igb_attr->dev_attr.show = igb_hwmon_show_location;
		snम_लिखो(igb_attr->name, माप(igb_attr->name),
			 "temp%u_label", offset + 1);
		अवरोध;
	हाल IGB_HWMON_TYPE_TEMP:
		igb_attr->dev_attr.show = igb_hwmon_show_temp;
		snम_लिखो(igb_attr->name, माप(igb_attr->name),
			 "temp%u_input", offset + 1);
		अवरोध;
	हाल IGB_HWMON_TYPE_CAUTION:
		igb_attr->dev_attr.show = igb_hwmon_show_cautionthresh;
		snम_लिखो(igb_attr->name, माप(igb_attr->name),
			 "temp%u_max", offset + 1);
		अवरोध;
	हाल IGB_HWMON_TYPE_MAX:
		igb_attr->dev_attr.show = igb_hwmon_show_maxopthresh;
		snम_लिखो(igb_attr->name, माप(igb_attr->name),
			 "temp%u_crit", offset + 1);
		अवरोध;
	शेष:
		rc = -EPERM;
		वापस rc;
	पूर्ण

	/* These always the same regardless of type */
	igb_attr->sensor =
		&adapter->hw.mac.thermal_sensor_data.sensor[offset];
	igb_attr->hw = &adapter->hw;
	igb_attr->dev_attr.store = शून्य;
	igb_attr->dev_attr.attr.mode = 0444;
	igb_attr->dev_attr.attr.name = igb_attr->name;
	sysfs_attr_init(&igb_attr->dev_attr.attr);

	adapter->igb_hwmon_buff->attrs[n_attr] = &igb_attr->dev_attr.attr;

	++adapter->igb_hwmon_buff->n_hwmon;

	वापस 0;
पूर्ण

अटल व्योम igb_sysfs_del_adapter(काष्ठा igb_adapter *adapter)
अणु
पूर्ण

/* called from igb_मुख्य.c */
व्योम igb_sysfs_निकास(काष्ठा igb_adapter *adapter)
अणु
	igb_sysfs_del_adapter(adapter);
पूर्ण

/* called from igb_मुख्य.c */
पूर्णांक igb_sysfs_init(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा hwmon_buff *igb_hwmon;
	काष्ठा i2c_client *client;
	काष्ठा device *hwmon_dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	/* If this method isn't defined we don't support thermals */
	अगर (adapter->hw.mac.ops.init_thermal_sensor_thresh == शून्य)
		जाओ निकास;

	/* Don't create thermal hwmon पूर्णांकerface अगर no sensors present */
	rc = (adapter->hw.mac.ops.init_thermal_sensor_thresh(&adapter->hw));
	अगर (rc)
		जाओ निकास;

	igb_hwmon = devm_kzalloc(&adapter->pdev->dev, माप(*igb_hwmon),
				 GFP_KERNEL);
	अगर (!igb_hwmon) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण
	adapter->igb_hwmon_buff = igb_hwmon;

	क्रम (i = 0; i < E1000_MAX_SENSORS; i++) अणु

		/* Only create hwmon sysfs entries क्रम sensors that have
		 * meaningful data.
		 */
		अगर (adapter->hw.mac.thermal_sensor_data.sensor[i].location == 0)
			जारी;

		/* Bail अगर any hwmon attr काष्ठा fails to initialize */
		rc = igb_add_hwmon_attr(adapter, i, IGB_HWMON_TYPE_CAUTION);
		अगर (rc)
			जाओ निकास;
		rc = igb_add_hwmon_attr(adapter, i, IGB_HWMON_TYPE_LOC);
		अगर (rc)
			जाओ निकास;
		rc = igb_add_hwmon_attr(adapter, i, IGB_HWMON_TYPE_TEMP);
		अगर (rc)
			जाओ निकास;
		rc = igb_add_hwmon_attr(adapter, i, IGB_HWMON_TYPE_MAX);
		अगर (rc)
			जाओ निकास;
	पूर्ण

	/* init i2c_client */
	client = i2c_new_client_device(&adapter->i2c_adap, &i350_sensor_info);
	अगर (IS_ERR(client)) अणु
		dev_info(&adapter->pdev->dev,
			 "Failed to create new i2c device.\n");
		rc = PTR_ERR(client);
		जाओ निकास;
	पूर्ण
	adapter->i2c_client = client;

	igb_hwmon->groups[0] = &igb_hwmon->group;
	igb_hwmon->group.attrs = igb_hwmon->attrs;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&adapter->pdev->dev,
							   client->name,
							   igb_hwmon,
							   igb_hwmon->groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		rc = PTR_ERR(hwmon_dev);
		जाओ err;
	पूर्ण

	जाओ निकास;

err:
	igb_sysfs_del_adapter(adapter);
निकास:
	वापस rc;
पूर्ण
#पूर्ण_अगर
