<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/dt2817.c
 * Hardware driver क्रम Data Translation DT2817
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: dt2817
 * Description: Data Translation DT2817
 * Author: ds
 * Status: complete
 * Devices: [Data Translation] DT2817 (dt2817)
 *
 * A very simple digital I/O card.  Four banks of 8 lines, each bank
 * is configurable क्रम input or output.  One wonders why it takes a
 * 50 page manual to describe this thing.
 *
 * The driver (which, btw, is much less than 50 pages) has 1 subdevice
 * with 32 channels, configurable in groups of 8.
 *
 * Configuration options:
 * [0] - I/O port base base address
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#घोषणा DT2817_CR 0
#घोषणा DT2817_DATA 1

अटल पूर्णांक dt2817_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक oe = 0;
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x000000ff;
	अन्यथा अगर (chan < 16)
		mask = 0x0000ff00;
	अन्यथा अगर (chan < 24)
		mask = 0x00ff0000;
	अन्यथा
		mask = 0xff000000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	अगर (s->io_bits & 0x000000ff)
		oe |= 0x1;
	अगर (s->io_bits & 0x0000ff00)
		oe |= 0x2;
	अगर (s->io_bits & 0x00ff0000)
		oe |= 0x4;
	अगर (s->io_bits & 0xff000000)
		oe |= 0x8;

	outb(oe, dev->iobase + DT2817_CR);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt2817_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ iobase = dev->iobase + DT2817_DATA;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0x000000ff)
			outb(s->state & 0xff, iobase + 0);
		अगर (mask & 0x0000ff00)
			outb((s->state >> 8) & 0xff, iobase + 1);
		अगर (mask & 0x00ff0000)
			outb((s->state >> 16) & 0xff, iobase + 2);
		अगर (mask & 0xff000000)
			outb((s->state >> 24) & 0xff, iobase + 3);
	पूर्ण

	val = inb(iobase + 0);
	val |= (inb(iobase + 1) << 8);
	val |= (inb(iobase + 2) << 16);
	val |= (inb(iobase + 3) << 24);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt2817_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	पूर्णांक ret;
	काष्ठा comedi_subdevice *s;

	ret = comedi_request_region(dev, it->options[0], 0x5);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];

	s->n_chan = 32;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_bits = dt2817_dio_insn_bits;
	s->insn_config = dt2817_dio_insn_config;

	s->state = 0;
	outb(0, dev->iobase + DT2817_CR);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver dt2817_driver = अणु
	.driver_name	= "dt2817",
	.module		= THIS_MODULE,
	.attach		= dt2817_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(dt2817_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
