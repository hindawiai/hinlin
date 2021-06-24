<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACIO_ASIC_H__
#घोषणा __MACIO_ASIC_H__
#अगर_घोषित __KERNEL__

#समावेश <linux/of_device.h>

बाह्य काष्ठा bus_type macio_bus_type;

/* MacIO device driver is defined later */
काष्ठा macio_driver;
काष्ठा macio_chip;

#घोषणा MACIO_DEV_COUNT_RESOURCES	8
#घोषणा MACIO_DEV_COUNT_IRQS		8

/*
 * the macio_bus काष्ठाure is used to describe a "virtual" bus
 * within a MacIO ASIC. It's typically provided by a macio_pci_asic
 * PCI device, but could be provided dअगरferently as well (nubus
 * machines using a fake OF tree).
 *
 * The pdev field can be शून्य on non-PCI machines
 */
काष्ठा macio_bus
अणु
	काष्ठा macio_chip	*chip;		/* macio_chip (निजी use) */
	पूर्णांक			index;		/* macio chip index in प्रणाली */
#अगर_घोषित CONFIG_PCI
	काष्ठा pci_dev		*pdev;		/* PCI device hosting this bus */
#पूर्ण_अगर
पूर्ण;

/*
 * the macio_dev काष्ठाure is used to describe a device
 * within an Apple MacIO ASIC.
 */
काष्ठा macio_dev
अणु
	काष्ठा macio_bus	*bus;		/* macio bus this device is on */
	काष्ठा macio_dev	*media_bay;	/* Device is part of a media bay */
	काष्ठा platक्रमm_device	ofdev;
	काष्ठा device_dma_parameters dma_parms; /* ide needs that */
	पूर्णांक			n_resources;
	काष्ठा resource		resource[MACIO_DEV_COUNT_RESOURCES];
	पूर्णांक			n_पूर्णांकerrupts;
	काष्ठा resource		पूर्णांकerrupt[MACIO_DEV_COUNT_IRQS];
पूर्ण;
#घोषणा	to_macio_device(d) container_of(d, काष्ठा macio_dev, ofdev.dev)
#घोषणा	of_to_macio_device(d) container_of(d, काष्ठा macio_dev, ofdev)

बाह्य काष्ठा macio_dev *macio_dev_get(काष्ठा macio_dev *dev);
बाह्य व्योम macio_dev_put(काष्ठा macio_dev *dev);

/*
 * Accessors to resources & पूर्णांकerrupts and other device
 * fields
 */

अटल अंतरभूत पूर्णांक macio_resource_count(काष्ठा macio_dev *dev)
अणु
	वापस dev->n_resources;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ macio_resource_start(काष्ठा macio_dev *dev, पूर्णांक resource_no)
अणु
	वापस dev->resource[resource_no].start;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ macio_resource_end(काष्ठा macio_dev *dev, पूर्णांक resource_no)
अणु
	वापस dev->resource[resource_no].end;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ macio_resource_len(काष्ठा macio_dev *dev, पूर्णांक resource_no)
अणु
	काष्ठा resource *res = &dev->resource[resource_no];
	अगर (res->start == 0 || res->end == 0 || res->end < res->start)
		वापस 0;
	वापस resource_size(res);
पूर्ण

बाह्य पूर्णांक macio_enable_devres(काष्ठा macio_dev *dev);

बाह्य पूर्णांक macio_request_resource(काष्ठा macio_dev *dev, पूर्णांक resource_no, स्थिर अक्षर *name);
बाह्य व्योम macio_release_resource(काष्ठा macio_dev *dev, पूर्णांक resource_no);
बाह्य पूर्णांक macio_request_resources(काष्ठा macio_dev *dev, स्थिर अक्षर *name);
बाह्य व्योम macio_release_resources(काष्ठा macio_dev *dev);

अटल अंतरभूत पूर्णांक macio_irq_count(काष्ठा macio_dev *dev)
अणु
	वापस dev->n_पूर्णांकerrupts;
पूर्ण

अटल अंतरभूत पूर्णांक macio_irq(काष्ठा macio_dev *dev, पूर्णांक irq_no)
अणु
	वापस dev->पूर्णांकerrupt[irq_no].start;
पूर्ण

अटल अंतरभूत व्योम macio_set_drvdata(काष्ठा macio_dev *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->ofdev.dev, data);
पूर्ण

अटल अंतरभूत व्योम* macio_get_drvdata(काष्ठा macio_dev *dev)
अणु
	वापस dev_get_drvdata(&dev->ofdev.dev);
पूर्ण

अटल अंतरभूत काष्ठा device_node *macio_get_of_node(काष्ठा macio_dev *mdev)
अणु
	वापस mdev->ofdev.dev.of_node;
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत काष्ठा pci_dev *macio_get_pci_dev(काष्ठा macio_dev *mdev)
अणु
	वापस mdev->bus->pdev;
पूर्ण
#पूर्ण_अगर

/*
 * A driver क्रम a mac-io chip based device
 */
काष्ठा macio_driver
अणु
	पूर्णांक	(*probe)(काष्ठा macio_dev* dev, स्थिर काष्ठा of_device_id *match);
	पूर्णांक	(*हटाओ)(काष्ठा macio_dev* dev);

	पूर्णांक	(*suspend)(काष्ठा macio_dev* dev, pm_message_t state);
	पूर्णांक	(*resume)(काष्ठा macio_dev* dev);
	पूर्णांक	(*shutकरोwn)(काष्ठा macio_dev* dev);

#अगर_घोषित CONFIG_PMAC_MEDIABAY
	व्योम	(*mediabay_event)(काष्ठा macio_dev* dev, पूर्णांक mb_state);
#पूर्ण_अगर
	काष्ठा device_driver	driver;
पूर्ण;
#घोषणा	to_macio_driver(drv) container_of(drv,काष्ठा macio_driver, driver)

बाह्य पूर्णांक macio_रेजिस्टर_driver(काष्ठा macio_driver *);
बाह्य व्योम macio_unरेजिस्टर_driver(काष्ठा macio_driver *);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __MACIO_ASIC_H__ */
