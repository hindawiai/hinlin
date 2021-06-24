<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2019-2020 Intel Corporation
 *
 * Please see Documentation/driver-api/auxiliary_bus.rst क्रम more inक्रमmation.
 */

#अगर_अघोषित _AUXILIARY_BUS_H_
#घोषणा _AUXILIARY_BUS_H_

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

काष्ठा auxiliary_device अणु
	काष्ठा device dev;
	स्थिर अक्षर *name;
	u32 id;
पूर्ण;

काष्ठा auxiliary_driver अणु
	पूर्णांक (*probe)(काष्ठा auxiliary_device *auxdev, स्थिर काष्ठा auxiliary_device_id *id);
	व्योम (*हटाओ)(काष्ठा auxiliary_device *auxdev);
	व्योम (*shutकरोwn)(काष्ठा auxiliary_device *auxdev);
	पूर्णांक (*suspend)(काष्ठा auxiliary_device *auxdev, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा auxiliary_device *auxdev);
	स्थिर अक्षर *name;
	काष्ठा device_driver driver;
	स्थिर काष्ठा auxiliary_device_id *id_table;
पूर्ण;

अटल अंतरभूत काष्ठा auxiliary_device *to_auxiliary_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा auxiliary_device, dev);
पूर्ण

अटल अंतरभूत काष्ठा auxiliary_driver *to_auxiliary_drv(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा auxiliary_driver, driver);
पूर्ण

पूर्णांक auxiliary_device_init(काष्ठा auxiliary_device *auxdev);
पूर्णांक __auxiliary_device_add(काष्ठा auxiliary_device *auxdev, स्थिर अक्षर *modname);
#घोषणा auxiliary_device_add(auxdev) __auxiliary_device_add(auxdev, KBUILD_MODNAME)

अटल अंतरभूत व्योम auxiliary_device_uninit(काष्ठा auxiliary_device *auxdev)
अणु
	put_device(&auxdev->dev);
पूर्ण

अटल अंतरभूत व्योम auxiliary_device_delete(काष्ठा auxiliary_device *auxdev)
अणु
	device_del(&auxdev->dev);
पूर्ण

पूर्णांक __auxiliary_driver_रेजिस्टर(काष्ठा auxiliary_driver *auxdrv, काष्ठा module *owner,
				स्थिर अक्षर *modname);
#घोषणा auxiliary_driver_रेजिस्टर(auxdrv) \
	__auxiliary_driver_रेजिस्टर(auxdrv, THIS_MODULE, KBUILD_MODNAME)

व्योम auxiliary_driver_unरेजिस्टर(काष्ठा auxiliary_driver *auxdrv);

/**
 * module_auxiliary_driver() - Helper macro क्रम रेजिस्टरing an auxiliary driver
 * @__auxiliary_driver: auxiliary driver काष्ठा
 *
 * Helper macro क्रम auxiliary drivers which करो not करो anything special in
 * module init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_auxiliary_driver(__auxiliary_driver) \
	module_driver(__auxiliary_driver, auxiliary_driver_रेजिस्टर, auxiliary_driver_unरेजिस्टर)

काष्ठा auxiliary_device *auxiliary_find_device(काष्ठा device *start,
					       स्थिर व्योम *data,
					       पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data));

#पूर्ण_अगर /* _AUXILIARY_BUS_H_ */
