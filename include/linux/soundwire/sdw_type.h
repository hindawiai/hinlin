<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2015-17 Intel Corporation. */

#अगर_अघोषित __SOUNDWIRE_TYPES_H
#घोषणा __SOUNDWIRE_TYPES_H

बाह्य काष्ठा bus_type sdw_bus_type;
बाह्य काष्ठा device_type sdw_slave_type;
बाह्य काष्ठा device_type sdw_master_type;

अटल अंतरभूत पूर्णांक is_sdw_slave(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &sdw_slave_type;
पूर्ण

#घोषणा drv_to_sdw_driver(_drv) container_of(_drv, काष्ठा sdw_driver, driver)

#घोषणा sdw_रेजिस्टर_driver(drv) \
	__sdw_रेजिस्टर_driver(drv, THIS_MODULE)

पूर्णांक __sdw_रेजिस्टर_driver(काष्ठा sdw_driver *drv, काष्ठा module *owner);
व्योम sdw_unरेजिस्टर_driver(काष्ठा sdw_driver *drv);

पूर्णांक sdw_slave_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);

/**
 * module_sdw_driver() - Helper macro क्रम रेजिस्टरing a Soundwire driver
 * @__sdw_driver: soundwire slave driver काष्ठा
 *
 * Helper macro क्रम Soundwire drivers which करो not करो anything special in
 * module init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_sdw_driver(__sdw_driver) \
	module_driver(__sdw_driver, sdw_रेजिस्टर_driver, \
			sdw_unरेजिस्टर_driver)
#पूर्ण_अगर /* __SOUNDWIRE_TYPES_H */
