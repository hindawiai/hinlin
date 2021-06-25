<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedi_pci.h
 * header file क्रम Comedi PCI drivers
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _COMEDI_PCI_H
#घोषणा _COMEDI_PCI_H

#समावेश <linux/pci.h>

#समावेश "comedidev.h"

/*
 * PCI Venकरोr IDs not in <linux/pci_ids.h>
 */
#घोषणा PCI_VENDOR_ID_KOLTER		0x1001
#घोषणा PCI_VENDOR_ID_ICP		0x104c
#घोषणा PCI_VENDOR_ID_DT		0x1116
#घोषणा PCI_VENDOR_ID_IOTECH		0x1616
#घोषणा PCI_VENDOR_ID_CONTEC		0x1221
#घोषणा PCI_VENDOR_ID_RTD		0x1435
#घोषणा PCI_VENDOR_ID_HUMUSOFT		0x186c

काष्ठा pci_dev *comedi_to_pci_dev(काष्ठा comedi_device *dev);

पूर्णांक comedi_pci_enable(काष्ठा comedi_device *dev);
व्योम comedi_pci_disable(काष्ठा comedi_device *dev);
व्योम comedi_pci_detach(काष्ठा comedi_device *dev);

पूर्णांक comedi_pci_स्वतः_config(काष्ठा pci_dev *pcidev, काष्ठा comedi_driver *driver,
			   अचिन्हित दीर्घ context);
व्योम comedi_pci_स्वतः_unconfig(काष्ठा pci_dev *pcidev);

पूर्णांक comedi_pci_driver_रेजिस्टर(काष्ठा comedi_driver *comedi_driver,
			       काष्ठा pci_driver *pci_driver);
व्योम comedi_pci_driver_unरेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				  काष्ठा pci_driver *pci_driver);

/**
 * module_comedi_pci_driver() - Helper macro क्रम रेजिस्टरing a comedi PCI driver
 * @__comedi_driver: comedi_driver काष्ठा
 * @__pci_driver: pci_driver काष्ठा
 *
 * Helper macro क्रम comedi PCI drivers which करो not करो anything special
 * in module init/निकास. This eliminates a lot of boilerplate. Each
 * module may only use this macro once, and calling it replaces
 * module_init() and module_निकास()
 */
#घोषणा module_comedi_pci_driver(__comedi_driver, __pci_driver) \
	module_driver(__comedi_driver, comedi_pci_driver_रेजिस्टर, \
			comedi_pci_driver_unरेजिस्टर, &(__pci_driver))

#पूर्ण_अगर /* _COMEDI_PCI_H */
