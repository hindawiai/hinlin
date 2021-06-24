<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/adl_pci8164.c
 *
 * Hardware comedi driver क्रम PCI-8164 Adlink card
 * Copyright (C) 2004 Michel Lachine <mike@mikelachaine.ca>
 */

/*
 * Driver: adl_pci8164
 * Description: Driver क्रम the Adlink PCI-8164 4 Axes Motion Control board
 * Devices: [ADLink] PCI-8164 (adl_pci8164)
 * Author: Michel Lachaine <mike@mikelachaine.ca>
 * Status: experimental
 * Updated: Mon, 14 Apr 2008 15:10:32 +0100
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

#घोषणा PCI8164_AXIS(x)		((x) * 0x08)
#घोषणा PCI8164_CMD_MSTS_REG	0x00
#घोषणा PCI8164_OTP_SSTS_REG	0x02
#घोषणा PCI8164_BUF0_REG	0x04
#घोषणा PCI8164_BUF1_REG	0x06

अटल पूर्णांक adl_pci8164_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = inw(dev->iobase + PCI8164_AXIS(chan) + offset);

	वापस insn->n;
पूर्ण

अटल पूर्णांक adl_pci8164_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		outw(data[i], dev->iobase + PCI8164_AXIS(chan) + offset);

	वापस insn->n;
पूर्ण

अटल पूर्णांक adl_pci8164_स्वतः_attach(काष्ठा comedi_device *dev,
				   अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 2);

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* पढ़ो MSTS रेजिस्टर / ग_लिखो CMD रेजिस्टर क्रम each axis (channel) */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_PROC;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->len_chanlist	= 4;
	s->insn_पढ़ो	= adl_pci8164_insn_पढ़ो;
	s->insn_ग_लिखो	= adl_pci8164_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI8164_CMD_MSTS_REG;

	/* पढ़ो SSTS रेजिस्टर / ग_लिखो OTP रेजिस्टर क्रम each axis (channel) */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_PROC;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->len_chanlist	= 4;
	s->insn_पढ़ो	= adl_pci8164_insn_पढ़ो;
	s->insn_ग_लिखो	= adl_pci8164_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI8164_OTP_SSTS_REG;

	/* पढ़ो/ग_लिखो BUF0 रेजिस्टर क्रम each axis (channel) */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_PROC;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->len_chanlist	= 4;
	s->insn_पढ़ो	= adl_pci8164_insn_पढ़ो;
	s->insn_ग_लिखो	= adl_pci8164_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI8164_BUF0_REG;

	/* पढ़ो/ग_लिखो BUF1 रेजिस्टर क्रम each axis (channel) */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_PROC;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->len_chanlist	= 4;
	s->insn_पढ़ो	= adl_pci8164_insn_पढ़ो;
	s->insn_ग_लिखो	= adl_pci8164_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI8164_BUF1_REG;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver adl_pci8164_driver = अणु
	.driver_name	= "adl_pci8164",
	.module		= THIS_MODULE,
	.स्वतः_attach	= adl_pci8164_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक adl_pci8164_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adl_pci8164_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adl_pci8164_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADLINK, 0x8164) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adl_pci8164_pci_table);

अटल काष्ठा pci_driver adl_pci8164_pci_driver = अणु
	.name		= "adl_pci8164",
	.id_table	= adl_pci8164_pci_table,
	.probe		= adl_pci8164_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adl_pci8164_driver, adl_pci8164_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
