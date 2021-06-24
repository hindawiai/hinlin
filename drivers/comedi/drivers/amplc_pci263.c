<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Amplicon PCI263 relay board.
 *
 * Copyright (C) 2002 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: amplc_pci263
 * Description: Amplicon PCI263
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PCI263 (amplc_pci263)
 * Updated: Fri, 12 Apr 2013 15:19:36 +0100
 * Status: works
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * The board appears as one subdevice, with 16 digital outमाला_दो, each
 * connected to a reed-relay. Relay contacts are बंदd when output is 1.
 * The state of the outमाला_दो can be पढ़ो.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

/* PCI263 रेजिस्टरs */
#घोषणा PCI263_DO_0_7_REG	0x00
#घोषणा PCI263_DO_8_15_REG	0x01

अटल पूर्णांक pci263_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, dev->iobase + PCI263_DO_0_7_REG);
		outb((s->state >> 8) & 0xff, dev->iobase + PCI263_DO_8_15_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci263_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pci_dev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pci_dev, 2);
	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* Digital Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci263_करो_insn_bits;

	/* पढ़ो initial relay state */
	s->state = inb(dev->iobase + PCI263_DO_0_7_REG) |
		   (inb(dev->iobase + PCI263_DO_8_15_REG) << 8);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver amplc_pci263_driver = अणु
	.driver_name	= "amplc_pci263",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci263_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci263_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMPLICON, 0x000c) पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci263_pci_table);

अटल पूर्णांक amplc_pci263_pci_probe(काष्ठा pci_dev *dev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &amplc_pci263_driver,
				      id->driver_data);
पूर्ण

अटल काष्ठा pci_driver amplc_pci263_pci_driver = अणु
	.name		= "amplc_pci263",
	.id_table	= pci263_pci_table,
	.probe		= &amplc_pci263_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(amplc_pci263_driver, amplc_pci263_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon PCI263 relay board");
MODULE_LICENSE("GPL");
