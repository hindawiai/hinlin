<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rti802.c
 * Comedi driver क्रम Analog Devices RTI-802 board
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999 Anders Blomdell <anders.blomdell@control.lth.se>
 */

/*
 * Driver: rti802
 * Description: Analog Devices RTI-802
 * Author: Anders Blomdell <anders.blomdell@control.lth.se>
 * Devices: [Analog Devices] RTI-802 (rti802)
 * Status: works
 *
 * Configuration Options:
 *   [0] - i/o base
 *   [1] - unused
 *   [2,4,6,8,10,12,14,16] - dac#[0-7]  0=two's comp, 1=straight
 *   [3,5,7,9,11,13,15,17] - dac#[0-7]  0=bipolar, 1=unipolar
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

/*
 * Register I/O map
 */
#घोषणा RTI802_SELECT		0x00
#घोषणा RTI802_DATALOW		0x01
#घोषणा RTI802_DATAHIGH		0x02

काष्ठा rti802_निजी अणु
	क्रमागत अणु
		dac_2comp, dac_straight
	पूर्ण dac_coding[8];
	स्थिर काष्ठा comedi_lrange *range_type_list[8];
पूर्ण;

अटल पूर्णांक rti802_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा rti802_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	outb(chan, dev->iobase + RTI802_SELECT);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		/* munge offset binary to two's complement अगर needed */
		अगर (devpriv->dac_coding[chan] == dac_2comp)
			val = comedi_offset_munge(s, val);

		outb(val & 0xff, dev->iobase + RTI802_DATALOW);
		outb((val >> 8) & 0xff, dev->iobase + RTI802_DATAHIGH);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक rti802_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा rti802_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x04);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* Analog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->maxdata	= 0xfff;
	s->n_chan	= 8;
	s->insn_ग_लिखो	= rti802_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s->range_table_list = devpriv->range_type_list;
	क्रम (i = 0; i < 8; i++) अणु
		devpriv->dac_coding[i] = (it->options[3 + 2 * i])
			? (dac_straight) : (dac_2comp);
		devpriv->range_type_list[i] = (it->options[2 + 2 * i])
			? &range_unipolar10 : &range_bipolar10;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver rti802_driver = अणु
	.driver_name	= "rti802",
	.module		= THIS_MODULE,
	.attach		= rti802_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(rti802_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Analog Devices RTI-802 board");
MODULE_LICENSE("GPL");
