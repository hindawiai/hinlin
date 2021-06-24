<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ke_counter.c
 * Comedi driver क्रम Kolter-Electronic PCI Counter 1 Card
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ke_counter
 * Description: Driver क्रम Kolter Electronic Counter Card
 * Devices: [Kolter Electronic] PCI Counter Card (ke_counter)
 * Author: Michael Hillmann
 * Updated: Mon, 14 Apr 2008 15:42:42 +0100
 * Status: tested
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

/*
 * PCI BAR 0 Register I/O map
 */
#घोषणा KE_RESET_REG(x)			(0x00 + ((x) * 0x20))
#घोषणा KE_LATCH_REG(x)			(0x00 + ((x) * 0x20))
#घोषणा KE_LSB_REG(x)			(0x04 + ((x) * 0x20))
#घोषणा KE_MID_REG(x)			(0x08 + ((x) * 0x20))
#घोषणा KE_MSB_REG(x)			(0x0c + ((x) * 0x20))
#घोषणा KE_SIGN_REG(x)			(0x10 + ((x) * 0x20))
#घोषणा KE_OSC_SEL_REG			0xf8
#घोषणा KE_OSC_SEL_CLK(x)		(((x) & 0x3) << 0)
#घोषणा KE_OSC_SEL_EXT			KE_OSC_SEL_CLK(1)
#घोषणा KE_OSC_SEL_4MHZ			KE_OSC_SEL_CLK(2)
#घोषणा KE_OSC_SEL_20MHZ		KE_OSC_SEL_CLK(3)
#घोषणा KE_DO_REG			0xfc

अटल पूर्णांक ke_counter_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[0];

		/* Order matters */
		outb((val >> 24) & 0xff, dev->iobase + KE_SIGN_REG(chan));
		outb((val >> 16) & 0xff, dev->iobase + KE_MSB_REG(chan));
		outb((val >> 8) & 0xff, dev->iobase + KE_MID_REG(chan));
		outb((val >> 0) & 0xff, dev->iobase + KE_LSB_REG(chan));
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ke_counter_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		/* Order matters */
		inb(dev->iobase + KE_LATCH_REG(chan));

		val = inb(dev->iobase + KE_LSB_REG(chan));
		val |= (inb(dev->iobase + KE_MID_REG(chan)) << 8);
		val |= (inb(dev->iobase + KE_MSB_REG(chan)) << 16);
		val |= (inb(dev->iobase + KE_SIGN_REG(chan)) << 24);

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम ke_counter_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक chan;

	क्रम (chan = 0; chan < 3; chan++)
		outb(0, dev->iobase + KE_RESET_REG(chan));
पूर्ण

अटल पूर्णांक ke_counter_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित अक्षर src;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		चयन (data[1]) अणु
		हाल KE_CLK_20MHZ:	/* शेष */
			src = KE_OSC_SEL_20MHZ;
			अवरोध;
		हाल KE_CLK_4MHZ:	/* option */
			src = KE_OSC_SEL_4MHZ;
			अवरोध;
		हाल KE_CLK_EXT:	/* Pin 21 on D-sub */
			src = KE_OSC_SEL_EXT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		outb(src, dev->iobase + KE_OSC_SEL_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		src = inb(dev->iobase + KE_OSC_SEL_REG);
		चयन (src) अणु
		हाल KE_OSC_SEL_20MHZ:
			data[1] = KE_CLK_20MHZ;
			data[2] = 50;	/* 50ns */
			अवरोध;
		हाल KE_OSC_SEL_4MHZ:
			data[1] = KE_CLK_4MHZ;
			data[2] = 250;	/* 250ns */
			अवरोध;
		हाल KE_OSC_SEL_EXT:
			data[1] = KE_CLK_EXT;
			data[2] = 0;	/* Unknown */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल INSN_CONFIG_RESET:
		ke_counter_reset(dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ke_counter_करो_insn_bits(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + KE_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक ke_counter_स्वतः_attach(काष्ठा comedi_device *dev,
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
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 3;
	s->maxdata	= 0x01ffffff;
	s->range_table	= &range_unknown;
	s->insn_पढ़ो	= ke_counter_insn_पढ़ो;
	s->insn_ग_लिखो	= ke_counter_insn_ग_लिखो;
	s->insn_config	= ke_counter_insn_config;

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 3;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= ke_counter_करो_insn_bits;

	outb(KE_OSC_SEL_20MHZ, dev->iobase + KE_OSC_SEL_REG);

	ke_counter_reset(dev);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver ke_counter_driver = अणु
	.driver_name	= "ke_counter",
	.module		= THIS_MODULE,
	.स्वतः_attach	= ke_counter_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक ke_counter_pci_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ke_counter_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ke_counter_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_KOLTER, 0x0014) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ke_counter_pci_table);

अटल काष्ठा pci_driver ke_counter_pci_driver = अणु
	.name		= "ke_counter",
	.id_table	= ke_counter_pci_table,
	.probe		= ke_counter_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ke_counter_driver, ke_counter_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Kolter Electronic Counter Card");
MODULE_LICENSE("GPL");
