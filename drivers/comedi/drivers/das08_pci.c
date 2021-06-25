<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  das08_pci.c
 *  comedi driver क्रम DAS08 PCI boards
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 *  Copyright (C) 2001,2002,2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *  Copyright (C) 2004 Salvaकरोr E. Tropea <set@users.sf.net> <set@ieee.org>
 */

/*
 * Driver: das08_pci
 * Description: DAS-08 PCI compatible boards
 * Devices: [ComputerBoards] PCI-DAS08 (pci-das08)
 * Author: Warren Jasper, ds, Frank Hess
 * Updated: Fri, 31 Aug 2012 19:19:06 +0100
 * Status: works
 *
 * This is the PCI-specअगरic support split off from the das08 driver.
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

#समावेश "das08.h"

अटल स्थिर काष्ठा das08_board_काष्ठा das08_pci_boards[] = अणु
	अणु
		.name		= "pci-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_bipolar5,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8254_offset	= 4,
		.iosize		= 8,
	पूर्ण,
पूर्ण;

अटल पूर्णांक das08_pci_स्वतः_attach(काष्ठा comedi_device *dev,
				 अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pdev = comedi_to_pci_dev(dev);
	काष्ठा das08_निजी_काष्ठा *devpriv;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	/* The das08 driver needs the board_ptr */
	dev->board_ptr = &das08_pci_boards[0];

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pdev, 2);

	वापस das08_common_attach(dev, dev->iobase);
पूर्ण

अटल काष्ठा comedi_driver das08_pci_comedi_driver = अणु
	.driver_name	= "pci-das08",
	.module		= THIS_MODULE,
	.स्वतः_attach	= das08_pci_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक das08_pci_probe(काष्ठा pci_dev *dev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &das08_pci_comedi_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id das08_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CB, 0x0029) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, das08_pci_table);

अटल काष्ठा pci_driver das08_pci_driver = अणु
	.name		= "pci-das08",
	.id_table	= das08_pci_table,
	.probe		= das08_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(das08_pci_comedi_driver, das08_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
