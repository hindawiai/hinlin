<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pcmad.c
 * Hardware driver क्रम Winप्रणालीs PCM-A/D12 and PCM-A/D16
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000,2001 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: pcmad
 * Description: Winप्रणालीs PCM-A/D12, PCM-A/D16
 * Devices: [Winप्रणालीs] PCM-A/D12 (pcmad12), PCM-A/D16 (pcmad16)
 * Author: ds
 * Status: untested
 *
 * This driver was written on a bet that I couldn't ग_लिखो a driver
 * in less than 2 hours.  I won the bet, but never got paid.  =(
 *
 * Configuration options:
 *   [0] - I/O port base
 *   [1] - IRQ (unused)
 *   [2] - Analog input reference (must match jumpers)
 *	   0 = single-ended (16 channels)
 *	   1 = dअगरferential (8 channels)
 *   [3] - Analog input encoding (must match jumpers)
 *	   0 = straight binary (0-5V input range)
 *	   1 = two's complement (+-10V input range)
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#घोषणा PCMAD_STATUS		0
#घोषणा PCMAD_LSB		1
#घोषणा PCMAD_MSB		2
#घोषणा PCMAD_CONVERT		1

काष्ठा pcmad_board_काष्ठा अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ai_maxdata;
पूर्ण;

अटल स्थिर काष्ठा pcmad_board_काष्ठा pcmad_boards[] = अणु
	अणु
		.name		= "pcmad12",
		.ai_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "pcmad16",
		.ai_maxdata	= 0xffff,
	पूर्ण,
पूर्ण;

अटल पूर्णांक pcmad_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + PCMAD_STATUS);
	अगर ((status & 0x3) == 0x3)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pcmad_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		outb(chan, dev->iobase + PCMAD_CONVERT);

		ret = comedi_समयout(dev, s, insn, pcmad_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inb(dev->iobase + PCMAD_LSB) |
		      (inb(dev->iobase + PCMAD_MSB) << 8);

		/* data is shअगरted on the pcmad12, fix it */
		अगर (s->maxdata == 0x0fff)
			val >>= 4;

		अगर (comedi_range_is_bipolar(s, range)) अणु
			/* munge the two's complement value */
			val ^= ((s->maxdata + 1) >> 1);
		पूर्ण

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcmad_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcmad_board_काष्ठा *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x04);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	अगर (it->options[1]) अणु
		/* 8 dअगरferential channels */
		s->subdev_flags	= SDF_READABLE | AREF_DIFF;
		s->n_chan	= 8;
	पूर्ण अन्यथा अणु
		/* 16 single-ended channels */
		s->subdev_flags	= SDF_READABLE | AREF_GROUND;
		s->n_chan	= 16;
	पूर्ण
	s->len_chanlist	= 1;
	s->maxdata	= board->ai_maxdata;
	s->range_table	= it->options[2] ? &range_bipolar10 : &range_unipolar5;
	s->insn_पढ़ो	= pcmad_ai_insn_पढ़ो;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcmad_driver = अणु
	.driver_name	= "pcmad",
	.module		= THIS_MODULE,
	.attach		= pcmad_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &pcmad_boards[0].name,
	.num_names	= ARRAY_SIZE(pcmad_boards),
	.offset		= माप(pcmad_boards[0]),
पूर्ण;
module_comedi_driver(pcmad_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
