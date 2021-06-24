<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006, 2007 Eugene Konev <ejka@खोलोwrt.org>
 */

#अगर_अघोषित __VLYNQ_H__
#घोषणा __VLYNQ_H__

#समावेश <linux/device.h>
#समावेश <linux/types.h>

काष्ठा module;

#घोषणा VLYNQ_NUM_IRQS 32

काष्ठा vlynq_mapping अणु
	u32 size;
	u32 offset;
पूर्ण;

क्रमागत vlynq_भागisor अणु
	vlynq_भाग_स्वतः = 0,
	vlynq_द_भाग1,
	vlynq_द_भाग2,
	vlynq_द_भाग3,
	vlynq_द_भाग4,
	vlynq_द_भाग5,
	vlynq_द_भाग6,
	vlynq_द_भाग7,
	vlynq_द_भाग8,
	vlynq_rभाग1,
	vlynq_rभाग2,
	vlynq_rभाग3,
	vlynq_rभाग4,
	vlynq_rभाग5,
	vlynq_rभाग6,
	vlynq_rभाग7,
	vlynq_rभाग8,
	vlynq_भाग_बाह्यal
पूर्ण;

काष्ठा vlynq_device_id अणु
	u32 id;
	क्रमागत vlynq_भागisor भागisor;
	अचिन्हित दीर्घ driver_data;
पूर्ण;

काष्ठा vlynq_regs;
काष्ठा vlynq_device अणु
	u32 id, dev_id;
	पूर्णांक local_irq;
	पूर्णांक remote_irq;
	क्रमागत vlynq_भागisor भागisor;
	u32 regs_start, regs_end;
	u32 mem_start, mem_end;
	u32 irq_start, irq_end;
	पूर्णांक irq;
	पूर्णांक enabled;
	काष्ठा vlynq_regs *local;
	काष्ठा vlynq_regs *remote;
	काष्ठा device dev;
पूर्ण;

काष्ठा vlynq_driver अणु
	अक्षर *name;
	काष्ठा vlynq_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा vlynq_device *dev, काष्ठा vlynq_device_id *id);
	व्योम (*हटाओ)(काष्ठा vlynq_device *dev);
	काष्ठा device_driver driver;
पूर्ण;

काष्ठा plat_vlynq_ops अणु
	पूर्णांक (*on)(काष्ठा vlynq_device *dev);
	व्योम (*off)(काष्ठा vlynq_device *dev);
पूर्ण;

अटल अंतरभूत काष्ठा vlynq_driver *to_vlynq_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा vlynq_driver, driver);
पूर्ण

अटल अंतरभूत काष्ठा vlynq_device *to_vlynq_device(काष्ठा device *device)
अणु
	वापस container_of(device, काष्ठा vlynq_device, dev);
पूर्ण

बाह्य काष्ठा bus_type vlynq_bus_type;

बाह्य पूर्णांक __vlynq_रेजिस्टर_driver(काष्ठा vlynq_driver *driver,
				   काष्ठा module *owner);

अटल अंतरभूत पूर्णांक vlynq_रेजिस्टर_driver(काष्ठा vlynq_driver *driver)
अणु
	वापस __vlynq_रेजिस्टर_driver(driver, THIS_MODULE);
पूर्ण

अटल अंतरभूत व्योम *vlynq_get_drvdata(काष्ठा vlynq_device *dev)
अणु
	वापस dev_get_drvdata(&dev->dev);
पूर्ण

अटल अंतरभूत व्योम vlynq_set_drvdata(काष्ठा vlynq_device *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->dev, data);
पूर्ण

अटल अंतरभूत u32 vlynq_mem_start(काष्ठा vlynq_device *dev)
अणु
	वापस dev->mem_start;
पूर्ण

अटल अंतरभूत u32 vlynq_mem_end(काष्ठा vlynq_device *dev)
अणु
	वापस dev->mem_end;
पूर्ण

अटल अंतरभूत u32 vlynq_mem_len(काष्ठा vlynq_device *dev)
अणु
	वापस dev->mem_end - dev->mem_start + 1;
पूर्ण

अटल अंतरभूत पूर्णांक vlynq_virq_to_irq(काष्ठा vlynq_device *dev, पूर्णांक virq)
अणु
	पूर्णांक irq = dev->irq_start + virq;
	अगर ((irq < dev->irq_start) || (irq > dev->irq_end))
		वापस -EINVAL;

	वापस irq;
पूर्ण

अटल अंतरभूत पूर्णांक vlynq_irq_to_virq(काष्ठा vlynq_device *dev, पूर्णांक irq)
अणु
	अगर ((irq < dev->irq_start) || (irq > dev->irq_end))
		वापस -EINVAL;

	वापस irq - dev->irq_start;
पूर्ण

बाह्य व्योम vlynq_unरेजिस्टर_driver(काष्ठा vlynq_driver *driver);
बाह्य पूर्णांक vlynq_enable_device(काष्ठा vlynq_device *dev);
बाह्य व्योम vlynq_disable_device(काष्ठा vlynq_device *dev);
बाह्य पूर्णांक vlynq_set_local_mapping(काष्ठा vlynq_device *dev, u32 tx_offset,
				   काष्ठा vlynq_mapping *mapping);
बाह्य पूर्णांक vlynq_set_remote_mapping(काष्ठा vlynq_device *dev, u32 tx_offset,
				    काष्ठा vlynq_mapping *mapping);
बाह्य पूर्णांक vlynq_set_local_irq(काष्ठा vlynq_device *dev, पूर्णांक virq);
बाह्य पूर्णांक vlynq_set_remote_irq(काष्ठा vlynq_device *dev, पूर्णांक virq);

#पूर्ण_अगर /* __VLYNQ_H__ */
