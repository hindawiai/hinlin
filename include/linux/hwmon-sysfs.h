<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  hwmon-sysfs.h - hardware monitoring chip driver sysfs defines
 *
 *  Copyright (C) 2005 Yani Ioannou <yani.ioannou@gmail.com>
 */
#अगर_अघोषित _LINUX_HWMON_SYSFS_H
#घोषणा _LINUX_HWMON_SYSFS_H

#समावेश <linux/device.h>

काष्ठा sensor_device_attributeअणु
	काष्ठा device_attribute dev_attr;
	पूर्णांक index;
पूर्ण;
#घोषणा to_sensor_dev_attr(_dev_attr) \
	container_of(_dev_attr, काष्ठा sensor_device_attribute, dev_attr)

#घोषणा SENSOR_ATTR(_name, _mode, _show, _store, _index)	\
	अणु .dev_attr = __ATTR(_name, _mode, _show, _store),	\
	  .index = _index पूर्ण

#घोषणा SENSOR_ATTR_RO(_name, _func, _index)			\
	SENSOR_ATTR(_name, 0444, _func##_show, शून्य, _index)

#घोषणा SENSOR_ATTR_RW(_name, _func, _index)			\
	SENSOR_ATTR(_name, 0644, _func##_show, _func##_store, _index)

#घोषणा SENSOR_ATTR_WO(_name, _func, _index)			\
	SENSOR_ATTR(_name, 0200, शून्य, _func##_store, _index)

#घोषणा SENSOR_DEVICE_ATTR(_name, _mode, _show, _store, _index)	\
काष्ठा sensor_device_attribute sensor_dev_attr_##_name		\
	= SENSOR_ATTR(_name, _mode, _show, _store, _index)

#घोषणा SENSOR_DEVICE_ATTR_RO(_name, _func, _index)		\
	SENSOR_DEVICE_ATTR(_name, 0444, _func##_show, शून्य, _index)

#घोषणा SENSOR_DEVICE_ATTR_RW(_name, _func, _index)		\
	SENSOR_DEVICE_ATTR(_name, 0644, _func##_show, _func##_store, _index)

#घोषणा SENSOR_DEVICE_ATTR_WO(_name, _func, _index)		\
	SENSOR_DEVICE_ATTR(_name, 0200, शून्य, _func##_store, _index)

काष्ठा sensor_device_attribute_2 अणु
	काष्ठा device_attribute dev_attr;
	u8 index;
	u8 nr;
पूर्ण;
#घोषणा to_sensor_dev_attr_2(_dev_attr) \
	container_of(_dev_attr, काष्ठा sensor_device_attribute_2, dev_attr)

#घोषणा SENSOR_ATTR_2(_name, _mode, _show, _store, _nr, _index)	\
	अणु .dev_attr = __ATTR(_name, _mode, _show, _store),	\
	  .index = _index,					\
	  .nr = _nr पूर्ण

#घोषणा SENSOR_ATTR_2_RO(_name, _func, _nr, _index)		\
	SENSOR_ATTR_2(_name, 0444, _func##_show, शून्य, _nr, _index)

#घोषणा SENSOR_ATTR_2_RW(_name, _func, _nr, _index)		\
	SENSOR_ATTR_2(_name, 0644, _func##_show, _func##_store, _nr, _index)

#घोषणा SENSOR_ATTR_2_WO(_name, _func, _nr, _index)		\
	SENSOR_ATTR_2(_name, 0200, शून्य, _func##_store, _nr, _index)

#घोषणा SENSOR_DEVICE_ATTR_2(_name,_mode,_show,_store,_nr,_index)	\
काष्ठा sensor_device_attribute_2 sensor_dev_attr_##_name		\
	= SENSOR_ATTR_2(_name, _mode, _show, _store, _nr, _index)

#घोषणा SENSOR_DEVICE_ATTR_2_RO(_name, _func, _nr, _index)		\
	SENSOR_DEVICE_ATTR_2(_name, 0444, _func##_show, शून्य,		\
			     _nr, _index)

#घोषणा SENSOR_DEVICE_ATTR_2_RW(_name, _func, _nr, _index)		\
	SENSOR_DEVICE_ATTR_2(_name, 0644, _func##_show, _func##_store,	\
			     _nr, _index)

#घोषणा SENSOR_DEVICE_ATTR_2_WO(_name, _func, _nr, _index)		\
	SENSOR_DEVICE_ATTR_2(_name, 0200, शून्य, _func##_store,		\
			     _nr, _index)

#पूर्ण_अगर /* _LINUX_HWMON_SYSFS_H */
