<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Turris Mox module configuration bus driver
 *
 * Copyright (C) 2019 Marek Behथजn <kabel@kernel.org>
 */

#अगर_अघोषित __LINUX_MOXTET_H
#घोषणा __LINUX_MOXTET_H

#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mutex.h>

#घोषणा TURRIS_MOX_MAX_MODULES	10

क्रमागत turris_mox_cpu_module_id अणु
	TURRIS_MOX_CPU_ID_EMMC	= 0x00,
	TURRIS_MOX_CPU_ID_SD	= 0x10,
पूर्ण;

क्रमागत turris_mox_module_id अणु
	TURRIS_MOX_MODULE_FIRST		= 0x01,

	TURRIS_MOX_MODULE_SFP		= 0x01,
	TURRIS_MOX_MODULE_PCI		= 0x02,
	TURRIS_MOX_MODULE_TOPAZ		= 0x03,
	TURRIS_MOX_MODULE_PERIDOT	= 0x04,
	TURRIS_MOX_MODULE_USB3		= 0x05,
	TURRIS_MOX_MODULE_PCI_BRIDGE	= 0x06,

	TURRIS_MOX_MODULE_LAST		= 0x06,
पूर्ण;

#घोषणा MOXTET_NIRQS	16

बाह्य काष्ठा bus_type moxtet_type;

काष्ठा moxtet अणु
	काष्ठा device			*dev;
	काष्ठा mutex			lock;
	u8				modules[TURRIS_MOX_MAX_MODULES];
	पूर्णांक				count;
	u8				tx[TURRIS_MOX_MAX_MODULES];
	पूर्णांक				dev_irq;
	काष्ठा अणु
		काष्ठा irq_करोमुख्य	*करोमुख्य;
		काष्ठा irq_chip		chip;
		अचिन्हित दीर्घ		masked, exists;
		काष्ठा moxtet_irqpos अणु
					u8 idx;
					u8 bit;
		पूर्ण position[MOXTET_NIRQS];
	पूर्ण irq;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry			*debugfs_root;
#पूर्ण_अगर
पूर्ण;

काष्ठा moxtet_driver अणु
	स्थिर क्रमागत turris_mox_module_id	*id_table;
	काष्ठा device_driver		driver;
पूर्ण;

अटल अंतरभूत काष्ठा moxtet_driver *
to_moxtet_driver(काष्ठा device_driver *drv)
अणु
	अगर (!drv)
		वापस शून्य;
	वापस container_of(drv, काष्ठा moxtet_driver, driver);
पूर्ण

बाह्य पूर्णांक __moxtet_रेजिस्टर_driver(काष्ठा module *owner,
				    काष्ठा moxtet_driver *mdrv);

अटल अंतरभूत व्योम moxtet_unरेजिस्टर_driver(काष्ठा moxtet_driver *mdrv)
अणु
	अगर (mdrv)
		driver_unरेजिस्टर(&mdrv->driver);
पूर्ण

#घोषणा moxtet_रेजिस्टर_driver(driver) \
	__moxtet_रेजिस्टर_driver(THIS_MODULE, driver)

#घोषणा module_moxtet_driver(__moxtet_driver) \
	module_driver(__moxtet_driver, moxtet_रेजिस्टर_driver, \
			moxtet_unरेजिस्टर_driver)

काष्ठा moxtet_device अणु
	काष्ठा device			dev;
	काष्ठा moxtet			*moxtet;
	क्रमागत turris_mox_module_id	id;
	अचिन्हित पूर्णांक			idx;
पूर्ण;

बाह्य पूर्णांक moxtet_device_पढ़ो(काष्ठा device *dev);
बाह्य पूर्णांक moxtet_device_ग_लिखो(काष्ठा device *dev, u8 val);
बाह्य पूर्णांक moxtet_device_written(काष्ठा device *dev);

अटल अंतरभूत काष्ठा moxtet_device *
to_moxtet_device(काष्ठा device *dev)
अणु
	अगर (!dev)
		वापस शून्य;
	वापस container_of(dev, काष्ठा moxtet_device, dev);
पूर्ण

#पूर्ण_अगर /* __LINUX_MOXTET_H */
