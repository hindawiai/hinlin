<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_1516.c
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
 * PCI bar 1 I/O Register map - Digital input/output
 */
#घोषणा APCI1516_DI_REG			0x00
#घोषणा APCI1516_DO_REG			0x04

/*
 * PCI bar 2 I/O Register map - Watchकरोg (APCI-1516 and APCI-2016)
 */
#घोषणा APCI1516_WDOG_REG		0x00

क्रमागत apci1516_boardid अणु
	BOARD_APCI1016,
	BOARD_APCI1516,
	BOARD_APCI2016,
पूर्ण;

काष्ठा apci1516_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक di_nchan;
	पूर्णांक करो_nchan;
	पूर्णांक has_wकरोg;
पूर्ण;

अटल स्थिर काष्ठा apci1516_boardinfo apci1516_boardtypes[] = अणु
	[BOARD_APCI1016] = अणु
		.name		= "apci1016",
		.di_nchan	= 16,
	पूर्ण,
	[BOARD_APCI1516] = अणु
		.name		= "apci1516",
		.di_nchan	= 8,
		.करो_nchan	= 8,
		.has_wकरोg	= 1,
	पूर्ण,
	[BOARD_APCI2016] = अणु
		.name		= "apci2016",
		.करो_nchan	= 16,
		.has_wकरोg	= 1,
	पूर्ण,
पूर्ण;

काष्ठा apci1516_निजी अणु
	अचिन्हित दीर्घ wकरोg_iobase;
पूर्ण;

अटल पूर्णांक apci1516_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = inw(dev->iobase + APCI1516_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1516_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	s->state = inw(dev->iobase + APCI1516_DO_REG);

	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + APCI1516_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1516_reset(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा apci1516_boardinfo *board = dev->board_ptr;
	काष्ठा apci1516_निजी *devpriv = dev->निजी;

	अगर (!board->has_wकरोg)
		वापस 0;

	outw(0x0, dev->iobase + APCI1516_DO_REG);

	addi_watchकरोg_reset(devpriv->wकरोg_iobase);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1516_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा apci1516_boardinfo *board = शून्य;
	काष्ठा apci1516_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(apci1516_boardtypes))
		board = &apci1516_boardtypes[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pcidev, 1);
	devpriv->wकरोg_iobase = pci_resource_start(pcidev, 2);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Initialize the digital input subdevice */
	s = &dev->subdevices[0];
	अगर (board->di_nchan) अणु
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= board->di_nchan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= apci1516_di_insn_bits;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Initialize the digital output subdevice */
	s = &dev->subdevices[1];
	अगर (board->करो_nchan) अणु
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= board->करो_nchan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= apci1516_करो_insn_bits;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Initialize the watchकरोg subdevice */
	s = &dev->subdevices[2];
	अगर (board->has_wकरोg) अणु
		ret = addi_watchकरोg_init(s, devpriv->wकरोg_iobase);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	apci1516_reset(dev);
	वापस 0;
पूर्ण

अटल व्योम apci1516_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci1516_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci1516_driver = अणु
	.driver_name	= "addi_apci_1516",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci1516_स्वतः_attach,
	.detach		= apci1516_detach,
पूर्ण;

अटल पूर्णांक apci1516_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci1516_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci1516_pci_table[] = अणु
	अणु PCI_VDEVICE(ADDIDATA, 0x1000), BOARD_APCI1016 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x1001), BOARD_APCI1516 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x1002), BOARD_APCI2016 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci1516_pci_table);

अटल काष्ठा pci_driver apci1516_pci_driver = अणु
	.name		= "addi_apci_1516",
	.id_table	= apci1516_pci_table,
	.probe		= apci1516_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci1516_driver, apci1516_pci_driver);

MODULE_DESCRIPTION("ADDI-DATA APCI-1016/1516/2016, 16 channel DIO boards");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
