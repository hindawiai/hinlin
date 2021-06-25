<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_2200.c
 * Copyright (C) 2004,2005  ADDI-DATA GmbH क्रम the source code of this module.
 * Project manager: Eric Stolz
 *
 *	ADDI-DATA GmbH
 *	Dieselstrasse 3
 *	D-77833 Ottersweier
 *	Tel: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"
#समावेश "addi_watchdog.h"

/*
 * I/O Register Map
 */
#घोषणा APCI2200_DI_REG			0x00
#घोषणा APCI2200_DO_REG			0x04
#घोषणा APCI2200_WDOG_REG		0x08

अटल पूर्णांक apci2200_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = inw(dev->iobase + APCI2200_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci2200_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	s->state = inw(dev->iobase + APCI2200_DO_REG);

	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + APCI2200_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci2200_reset(काष्ठा comedi_device *dev)
अणु
	outw(0x0, dev->iobase + APCI2200_DO_REG);

	addi_watchकरोg_reset(dev->iobase + APCI2200_WDOG_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci2200_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pcidev, 1);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Initialize the digital input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci2200_di_insn_bits;

	/* Initialize the digital output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci2200_करो_insn_bits;

	/* Initialize the watchकरोg subdevice */
	s = &dev->subdevices[2];
	ret = addi_watchकरोg_init(s, dev->iobase + APCI2200_WDOG_REG);
	अगर (ret)
		वापस ret;

	apci2200_reset(dev);
	वापस 0;
पूर्ण

अटल व्योम apci2200_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci2200_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci2200_driver = अणु
	.driver_name	= "addi_apci_2200",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci2200_स्वतः_attach,
	.detach		= apci2200_detach,
पूर्ण;

अटल पूर्णांक apci2200_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci2200_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci2200_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADDIDATA, 0x1005) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci2200_pci_table);

अटल काष्ठा pci_driver apci2200_pci_driver = अणु
	.name		= "addi_apci_2200",
	.id_table	= apci2200_pci_table,
	.probe		= apci2200_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci2200_driver, apci2200_pci_driver);

MODULE_DESCRIPTION("ADDI-DATA APCI-2200 Relay board, optically isolated");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
