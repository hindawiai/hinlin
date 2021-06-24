<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Amplicon PC263 relay board.
 *
 * Copyright (C) 2002 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: amplc_pc263
 * Description: Amplicon PC263
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PC263 (pc263)
 * Updated: Fri, 12 Apr 2013 15:19:36 +0100
 * Status: works
 *
 * Configuration options:
 *   [0] - I/O port base address
 *
 * The board appears as one subdevice, with 16 digital outमाला_दो, each
 * connected to a reed-relay. Relay contacts are बंदd when output is 1.
 * The state of the outमाला_दो can be पढ़ो.
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

/* PC263 रेजिस्टरs */
#घोषणा PC263_DO_0_7_REG	0x00
#घोषणा PC263_DO_8_15_REG	0x01

काष्ठा pc263_board अणु
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा pc263_board pc263_boards[] = अणु
	अणु
		.name = "pc263",
	पूर्ण,
पूर्ण;

अटल पूर्णांक pc263_करो_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, dev->iobase + PC263_DO_0_7_REG);
		outb((s->state >> 8) & 0xff, dev->iobase + PC263_DO_8_15_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pc263_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x2);
	अगर (ret)
		वापस ret;

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
	s->insn_bits	= pc263_करो_insn_bits;

	/* पढ़ो initial relay state */
	s->state = inb(dev->iobase + PC263_DO_0_7_REG) |
		   (inb(dev->iobase + PC263_DO_8_15_REG) << 8);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver amplc_pc263_driver = अणु
	.driver_name	= "amplc_pc263",
	.module		= THIS_MODULE,
	.attach		= pc263_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &pc263_boards[0].name,
	.offset		= माप(काष्ठा pc263_board),
	.num_names	= ARRAY_SIZE(pc263_boards),
पूर्ण;

module_comedi_driver(amplc_pc263_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon PC263 relay board");
MODULE_LICENSE("GPL");
