<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/contec_pci_dio.c
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: contec_pci_dio
 * Description: Contec PIO1616L digital I/O board
 * Devices: [Contec] PIO1616L (contec_pci_dio)
 * Author: Stefano Rivoir <s.rivoir@gts.it>
 * Updated: Wed, 27 Jun 2007 13:00:06 +0100
 * Status: works
 *
 * Configuration Options: not applicable, uses comedi PCI स्वतः config
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

/*
 * Register map
 */
#घोषणा PIO1616L_DI_REG		0x00
#घोषणा PIO1616L_DO_REG		0x02

अटल पूर्णांक contec_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PIO1616L_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक contec_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	data[1] = inw(dev->iobase + PIO1616L_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक contec_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 0);

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= contec_di_insn_bits;

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= contec_करो_insn_bits;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver contec_pci_dio_driver = अणु
	.driver_name	= "contec_pci_dio",
	.module		= THIS_MODULE,
	.स्वतः_attach	= contec_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक contec_pci_dio_pci_probe(काष्ठा pci_dev *dev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &contec_pci_dio_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id contec_pci_dio_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CONTEC, 0x8172) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, contec_pci_dio_pci_table);

अटल काष्ठा pci_driver contec_pci_dio_pci_driver = अणु
	.name		= "contec_pci_dio",
	.id_table	= contec_pci_dio_pci_table,
	.probe		= contec_pci_dio_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(contec_pci_dio_driver, contec_pci_dio_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
