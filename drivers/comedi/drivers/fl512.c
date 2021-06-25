<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * fl512.c
 * Anders Gnistrup <ex18@kalman.iau.dtu.dk>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: fl512
 * Description: unknown
 * Author: Anders Gnistrup <ex18@kalman.iau.dtu.dk>
 * Devices: [unknown] FL512 (fl512)
 * Status: unknown
 *
 * Digital I/O is not supported.
 *
 * Configuration options:
 *   [0] - I/O port base address
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश <linux/delay.h>

/*
 * Register I/O map
 */
#घोषणा FL512_AI_LSB_REG		0x02
#घोषणा FL512_AI_MSB_REG		0x03
#घोषणा FL512_AI_MUX_REG		0x02
#घोषणा FL512_AI_START_CONV_REG		0x03
#घोषणा FL512_AO_DATA_REG(x)		(0x04 + ((x) * 2))
#घोषणा FL512_AO_TRIG_REG(x)		(0x04 + ((x) * 2))

अटल स्थिर काष्ठा comedi_lrange range_fl512 = अणु
	4, अणु
		BIP_RANGE(0.5),
		BIP_RANGE(1),
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

अटल पूर्णांक fl512_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	outb(chan, dev->iobase + FL512_AI_MUX_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		outb(0, dev->iobase + FL512_AI_START_CONV_REG);

		/* XXX should test "done" flag instead of delay */
		usleep_range(30, 100);

		val = inb(dev->iobase + FL512_AI_LSB_REG);
		val |= (inb(dev->iobase + FL512_AI_MSB_REG) << 8);
		val &= s->maxdata;

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक fl512_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		/* ग_लिखो LSB, MSB then trigger conversion */
		outb(val & 0x0ff, dev->iobase + FL512_AO_DATA_REG(chan));
		outb((val >> 8) & 0xf, dev->iobase + FL512_AO_DATA_REG(chan));
		inb(dev->iobase + FL512_AO_TRIG_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक fl512_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->range_table	= &range_fl512;
	s->insn_पढ़ो	= fl512_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= &range_fl512;
	s->insn_ग_लिखो	= fl512_ao_insn_ग_लिखो;

	वापस comedi_alloc_subdev_पढ़ोback(s);
पूर्ण

अटल काष्ठा comedi_driver fl512_driver = अणु
	.driver_name	= "fl512",
	.module		= THIS_MODULE,
	.attach		= fl512_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(fl512_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
