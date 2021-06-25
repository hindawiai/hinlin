<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adv_pci1723.c
 * Comedi driver क्रम the Advantech PCI-1723 card.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adv_pci1723
 * Description: Advantech PCI-1723
 * Author: yonggang <rsmgnu@gmail.com>, Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Advantech] PCI-1723 (adv_pci1723)
 * Updated: Mon, 14 Apr 2008 15:12:56 +0100
 * Status: works
 *
 * Configuration Options: not applicable, uses comedi PCI स्वतः config
 *
 * Subdevice 0 is 8-channel AO, 16-bit, range +/- 10 V.
 *
 * Subdevice 1 is 16-channel DIO.  The channels are configurable as
 * input or output in 2 groups (0 to 7, 8 to 15). Configuring any
 * channel implicitly configures all channels in the same group.
 *
 * TODO:
 * 1. Add the two milliamp ranges to the AO subdevice (0 to 20 mA,
 *    4 to 20 mA).
 * 2. Read the initial ranges and values of the AO subdevice at
 *    start-up instead of reinitializing them.
 * 3. Implement calibration.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

/*
 * PCI Bar 2 I/O Register map (dev->iobase)
 */
#घोषणा PCI1723_AO_REG(x)		(0x00 + ((x) * 2))
#घोषणा PCI1723_BOARD_ID_REG		0x10
#घोषणा PCI1723_BOARD_ID_MASK		(0xf << 0)
#घोषणा PCI1723_SYNC_CTRL_REG		0x12
#घोषणा PCI1723_SYNC_CTRL(x)		(((x) & 0x1) << 0)
#घोषणा PCI1723_SYNC_CTRL_ASYNC		PCI1723_SYNC_CTRL(0)
#घोषणा PCI1723_SYNC_CTRL_SYNC		PCI1723_SYNC_CTRL(1)
#घोषणा PCI1723_CTRL_REG		0x14
#घोषणा PCI1723_CTRL_BUSY		BIT(15)
#घोषणा PCI1723_CTRL_INIT		BIT(14)
#घोषणा PCI1723_CTRL_SELF		BIT(8)
#घोषणा PCI1723_CTRL_IDX(x)		(((x) & 0x3) << 6)
#घोषणा PCI1723_CTRL_RANGE(x)		(((x) & 0x3) << 4)
#घोषणा PCI1723_CTRL_SEL(x)		(((x) & 0x1) << 3)
#घोषणा PCI1723_CTRL_GAIN		PCI1723_CTRL_SEL(0)
#घोषणा PCI1723_CTRL_OFFSET		PCI1723_CTRL_SEL(1)
#घोषणा PCI1723_CTRL_CHAN(x)		(((x) & 0x7) << 0)
#घोषणा PCI1723_CALIB_CTRL_REG		0x16
#घोषणा PCI1723_CALIB_CTRL_CS		BIT(2)
#घोषणा PCI1723_CALIB_CTRL_DAT		BIT(1)
#घोषणा PCI1723_CALIB_CTRL_CLK		BIT(0)
#घोषणा PCI1723_CALIB_STROBE_REG	0x18
#घोषणा PCI1723_DIO_CTRL_REG		0x1a
#घोषणा PCI1723_DIO_CTRL_HDIO		BIT(1)
#घोषणा PCI1723_DIO_CTRL_LDIO		BIT(0)
#घोषणा PCI1723_DIO_DATA_REG		0x1c
#घोषणा PCI1723_CALIB_DATA_REG		0x1e
#घोषणा PCI1723_SYNC_STROBE_REG		0x20
#घोषणा PCI1723_RESET_AO_STROBE_REG	0x22
#घोषणा PCI1723_RESET_CALIB_STROBE_REG	0x24
#घोषणा PCI1723_RANGE_STROBE_REG	0x26
#घोषणा PCI1723_VREF_REG		0x28
#घोषणा PCI1723_VREF(x)			(((x) & 0x3) << 0)
#घोषणा PCI1723_VREF_NEG10V		PCI1723_VREF(0)
#घोषणा PCI1723_VREF_0V			PCI1723_VREF(1)
#घोषणा PCI1723_VREF_POS10V		PCI1723_VREF(3)

अटल पूर्णांक pci1723_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		outw(val, dev->iobase + PCI1723_AO_REG(chan));
		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1723_dio_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask = (chan < 8) ? 0x00ff : 0xff00;
	अचिन्हित लघु mode = 0x0000;		/* assume output */
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	अगर (!(s->io_bits & 0x00ff))
		mode |= PCI1723_DIO_CTRL_LDIO;	/* low byte input */
	अगर (!(s->io_bits & 0xff00))
		mode |= PCI1723_DIO_CTRL_HDIO;	/* high byte input */
	outw(mode, dev->iobase + PCI1723_DIO_CTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1723_dio_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI1723_DIO_DATA_REG);

	data[1] = inw(dev->iobase + PCI1723_DIO_DATA_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1723_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 2);

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
	s->n_chan	= 8;
	s->maxdata	= 0xffff;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= pci1723_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* synchronously reset all analog outमाला_दो to 0V, +/-10V range */
	outw(PCI1723_SYNC_CTRL_SYNC, dev->iobase + PCI1723_SYNC_CTRL_REG);
	क्रम (i = 0; i < s->n_chan; i++) अणु
		outw(PCI1723_CTRL_RANGE(0) | PCI1723_CTRL_CHAN(i),
		     PCI1723_CTRL_REG);
		outw(0, dev->iobase + PCI1723_RANGE_STROBE_REG);

		outw(0x8000, dev->iobase + PCI1723_AO_REG(i));
		s->पढ़ोback[i] = 0x8000;
	पूर्ण
	outw(0, dev->iobase + PCI1723_SYNC_STROBE_REG);

	/* disable syncronous control */
	outw(PCI1723_SYNC_CTRL_ASYNC, dev->iobase + PCI1723_SYNC_CTRL_REG);

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_config	= pci1723_dio_insn_config;
	s->insn_bits	= pci1723_dio_insn_bits;

	/* get initial DIO direction and state */
	val = inw(dev->iobase + PCI1723_DIO_CTRL_REG);
	अगर (!(val & PCI1723_DIO_CTRL_LDIO))
		s->io_bits |= 0x00ff;	/* low byte output */
	अगर (!(val & PCI1723_DIO_CTRL_HDIO))
		s->io_bits |= 0xff00;	/* high byte output */
	s->state = inw(dev->iobase + PCI1723_DIO_DATA_REG);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver adv_pci1723_driver = अणु
	.driver_name	= "adv_pci1723",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci1723_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक adv_pci1723_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adv_pci1723_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adv_pci1723_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADVANTECH, 0x1723) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adv_pci1723_pci_table);

अटल काष्ठा pci_driver adv_pci1723_pci_driver = अणु
	.name		= "adv_pci1723",
	.id_table	= adv_pci1723_pci_table,
	.probe		= adv_pci1723_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adv_pci1723_driver, adv_pci1723_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Advantech PCI-1723 Comedi driver");
MODULE_LICENSE("GPL");
