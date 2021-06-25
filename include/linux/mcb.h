<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MEN Chameleon Bus.
 *
 * Copyright (C) 2014 MEN Mikroelektronik GmbH (www.men.de)
 * Author: Johannes Thumshirn <johannes.thumshirn@men.de>
 */
#अगर_अघोषित _LINUX_MCB_H
#घोषणा _LINUX_MCB_H

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/device.h>
#समावेश <linux/irqवापस.h>

#घोषणा CHAMELEON_खाताNAME_LEN 12

काष्ठा mcb_driver;
काष्ठा mcb_device;

/**
 * काष्ठा mcb_bus - MEN Chameleon Bus
 *
 * @dev: bus device
 * @carrier: poपूर्णांकer to carrier device
 * @bus_nr: mcb bus number
 * @get_irq: callback to get IRQ number
 * @revision: the FPGA's revision number
 * @model: the FPGA's model number
 * @filename: the FPGA's name
 */
काष्ठा mcb_bus अणु
	काष्ठा device dev;
	काष्ठा device *carrier;
	पूर्णांक bus_nr;
	u8 revision;
	अक्षर model;
	u8 minor;
	अक्षर name[CHAMELEON_खाताNAME_LEN + 1];
	पूर्णांक (*get_irq)(काष्ठा mcb_device *dev);
पूर्ण;

अटल अंतरभूत काष्ठा mcb_bus *to_mcb_bus(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा mcb_bus, dev);
पूर्ण

/**
 * काष्ठा mcb_device - MEN Chameleon Bus device
 *
 * @dev: device in kernel representation
 * @bus: mcb bus the device is plugged to
 * @is_added: flag to check अगर device is added to bus
 * @driver: associated mcb_driver
 * @id: mcb device id
 * @inst: instance in Chameleon table
 * @group: group in Chameleon table
 * @var: variant in Chameleon table
 * @bar: BAR in Chameleon table
 * @rev: revision in Chameleon table
 * @irq: IRQ resource
 * @memory: memory resource
 */
काष्ठा mcb_device अणु
	काष्ठा device dev;
	काष्ठा mcb_bus *bus;
	bool is_added;
	काष्ठा mcb_driver *driver;
	u16 id;
	पूर्णांक inst;
	पूर्णांक group;
	पूर्णांक var;
	पूर्णांक bar;
	पूर्णांक rev;
	काष्ठा resource irq;
	काष्ठा resource mem;
	काष्ठा device *dma_dev;
पूर्ण;

अटल अंतरभूत काष्ठा mcb_device *to_mcb_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा mcb_device, dev);
पूर्ण

/**
 * काष्ठा mcb_driver - MEN Chameleon Bus device driver
 *
 * @driver: device_driver
 * @id_table: mcb id table
 * @probe: probe callback
 * @हटाओ: हटाओ callback
 * @shutकरोwn: shutकरोwn callback
 */
काष्ठा mcb_driver अणु
	काष्ठा device_driver driver;
	स्थिर काष्ठा mcb_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा mcb_device *mdev, स्थिर काष्ठा mcb_device_id *id);
	व्योम (*हटाओ)(काष्ठा mcb_device *mdev);
	व्योम (*shutकरोwn)(काष्ठा mcb_device *mdev);
पूर्ण;

अटल अंतरभूत काष्ठा mcb_driver *to_mcb_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा mcb_driver, driver);
पूर्ण

अटल अंतरभूत व्योम *mcb_get_drvdata(काष्ठा mcb_device *dev)
अणु
	वापस dev_get_drvdata(&dev->dev);
पूर्ण

अटल अंतरभूत व्योम mcb_set_drvdata(काष्ठा mcb_device *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->dev, data);
पूर्ण

बाह्य पूर्णांक __must_check __mcb_रेजिस्टर_driver(काष्ठा mcb_driver *drv,
					काष्ठा module *owner,
					स्थिर अक्षर *mod_name);
#घोषणा mcb_रेजिस्टर_driver(driver)		\
	__mcb_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)
बाह्य व्योम mcb_unरेजिस्टर_driver(काष्ठा mcb_driver *driver);
#घोषणा module_mcb_driver(__mcb_driver)		\
	module_driver(__mcb_driver, mcb_रेजिस्टर_driver, mcb_unरेजिस्टर_driver);
बाह्य व्योम mcb_bus_add_devices(स्थिर काष्ठा mcb_bus *bus);
बाह्य पूर्णांक mcb_device_रेजिस्टर(काष्ठा mcb_bus *bus, काष्ठा mcb_device *dev);
बाह्य काष्ठा mcb_bus *mcb_alloc_bus(काष्ठा device *carrier);
बाह्य काष्ठा mcb_bus *mcb_bus_get(काष्ठा mcb_bus *bus);
बाह्य व्योम mcb_bus_put(काष्ठा mcb_bus *bus);
बाह्य काष्ठा mcb_device *mcb_alloc_dev(काष्ठा mcb_bus *bus);
बाह्य व्योम mcb_मुक्त_dev(काष्ठा mcb_device *dev);
बाह्य व्योम mcb_release_bus(काष्ठा mcb_bus *bus);
बाह्य काष्ठा resource *mcb_request_mem(काष्ठा mcb_device *dev,
					स्थिर अक्षर *name);
बाह्य व्योम mcb_release_mem(काष्ठा resource *mem);
बाह्य पूर्णांक mcb_get_irq(काष्ठा mcb_device *dev);
बाह्य काष्ठा resource *mcb_get_resource(काष्ठा mcb_device *dev,
					 अचिन्हित पूर्णांक type);

#पूर्ण_अगर /* _LINUX_MCB_H */
