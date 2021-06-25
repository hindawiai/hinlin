<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * COMEDI driver क्रम Advantech PCI-1720U
 * Copyright (c) 2015 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Separated from the adv_pci1710 driver written by:
 * Michal Dobes <करोbes@tesnet.cz>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adv_pci1720
 * Description: 4-channel Isolated D/A Output board
 * Devices: [Advantech] PCI-7120U (adv_pci1720)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Fri, 29 Oct 2015 17:19:35 -0700
 * Status: untested
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * The PCI-1720 has 4 isolated 12-bit analog output channels with multiple
 * output ranges. It also has a BoardID चयन to allow dअगरferentiating
 * multiple boards in the प्रणाली.
 *
 * The analog outमाला_दो can operate in two modes, immediate and synchronized.
 * This driver currently करोes not support the synchronized output mode.
 *
 * Jumpers JP1 to JP4 are used to set the current sink ranges क्रम each
 * analog output channel. In order to use the current sink ranges, the
 * unipolar 5V range must be used. The voltage output and sink output क्रम
 * each channel is available on the connector as separate pins.
 *
 * Jumper JP5 controls the "hot" reset state of the analog outमाला_दो.
 * Depending on its setting, the analog outमाला_दो will either keep the
 * last settings and output values or reset to the शेष state after
 * a "hot" reset. The शेष state क्रम all channels is uniploar 5V range
 * and all the output values are 0V. To allow this feature to work, the
 * analog outमाला_दो are not "reset" when the driver attaches.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pci.h"

/*
 * PCI BAR2 Register map (dev->iobase)
 */
#घोषणा PCI1720_AO_LSB_REG(x)		(0x00 + ((x) * 2))
#घोषणा PCI1720_AO_MSB_REG(x)		(0x01 + ((x) * 2))
#घोषणा PCI1720_AO_RANGE_REG		0x08
#घोषणा PCI1720_AO_RANGE(c, r)		(((r) & 0x3) << ((c) * 2))
#घोषणा PCI1720_AO_RANGE_MASK(c)	PCI1720_AO_RANGE((c), 0x3)
#घोषणा PCI1720_SYNC_REG		0x09
#घोषणा PCI1720_SYNC_CTRL_REG		0x0f
#घोषणा PCI1720_SYNC_CTRL_SC0		BIT(0)
#घोषणा PCI1720_BOARDID_REG		0x14

अटल स्थिर काष्ठा comedi_lrange pci1720_ao_range = अणु
	4, अणु
		UNI_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल पूर्णांक pci1720_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	/* set the channel range and polarity */
	val = inb(dev->iobase + PCI1720_AO_RANGE_REG);
	val &= ~PCI1720_AO_RANGE_MASK(chan);
	val |= PCI1720_AO_RANGE(chan, range);
	outb(val, dev->iobase + PCI1720_AO_RANGE_REG);

	val = s->पढ़ोback[chan];
	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		outb(val & 0xff, dev->iobase + PCI1720_AO_LSB_REG(chan));
		outb((val >> 8) & 0xff, dev->iobase + PCI1720_AO_MSB_REG(chan));

		/* conversion समय is 2us (500 kHz throughput) */
		usleep_range(2, 100);
	पूर्ण

	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1720_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + PCI1720_BOARDID_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1720_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 2);

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/* Analog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->range_table	= &pci1720_ao_range;
	s->insn_ग_लिखो	= pci1720_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice (BoardID SW1) */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci1720_di_insn_bits;

	/* disable synchronized output, channels update when written */
	outb(0, dev->iobase + PCI1720_SYNC_CTRL_REG);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver adv_pci1720_driver = अणु
	.driver_name	= "adv_pci1720",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci1720_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक adv_pci1720_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adv_pci1720_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adv_pci1720_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADVANTECH, 0x1720) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adv_pci1720_pci_table);

अटल काष्ठा pci_driver adv_pci1720_pci_driver = अणु
	.name		= "adv_pci1720",
	.id_table	= adv_pci1720_pci_table,
	.probe		= adv_pci1720_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adv_pci1720_driver, adv_pci1720_pci_driver);

MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("Comedi driver for Advantech PCI-1720 Analog Output board");
MODULE_LICENSE("GPL");
