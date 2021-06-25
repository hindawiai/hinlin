<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ssv_dnp.c
 * generic comedi driver क्रम SSV Embedded Systems' DIL/Net-PCs
 * Copyright (C) 2001 Robert Schwebel <robert@schwebel.de>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ssv_dnp
 * Description: SSV Embedded Systems DIL/Net-PC
 * Author: Robert Schwebel <robert@schwebel.de>
 * Devices: [SSV Embedded Systems] DIL/Net-PC 1486 (dnp-1486)
 * Status: unknown
 */

/* include files ----------------------------------------------------------- */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

/* Some global definitions: the रेजिस्टरs of the DNP ----------------------- */
/*                                                                           */
/* For port A and B the mode रेजिस्टर has bits corresponding to the output   */
/* pins, where Bit-N = 0 -> input, Bit-N = 1 -> output. Note that bits       */
/* 4 to 7 correspond to pin 0..3 क्रम port C data रेजिस्टर. Ensure that bits  */
/* 0..3 reमुख्य unchanged! For details about Port C Mode Register see         */
/* the remarks in dnp_insn_config() below.                                   */

#घोषणा CSCIR 0x22		/* Chip Setup and Control Index Register     */
#घोषणा CSCDR 0x23		/* Chip Setup and Control Data Register      */
#घोषणा PAMR  0xa5		/* Port A Mode Register                      */
#घोषणा PADR  0xa9		/* Port A Data Register                      */
#घोषणा PBMR  0xa4		/* Port B Mode Register                      */
#घोषणा PBDR  0xa8		/* Port B Data Register                      */
#घोषणा PCMR  0xa3		/* Port C Mode Register                      */
#घोषणा PCDR  0xa7		/* Port C Data Register                      */

अटल पूर्णांक dnp_dio_insn_bits(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	/*
	 * Ports A and B are straight क्रमward: each bit corresponds to an
	 * output pin with the same order. Port C is dअगरferent: bits 0...3
	 * correspond to bits 4...7 of the output रेजिस्टर (PCDR).
	 */

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		outb(PADR, CSCIR);
		outb(s->state & 0xff, CSCDR);

		outb(PBDR, CSCIR);
		outb((s->state >> 8) & 0xff, CSCDR);

		outb(PCDR, CSCIR);
		val = inb(CSCDR) & 0x0f;
		outb(((s->state >> 12) & 0xf0) | val, CSCDR);
	पूर्ण

	outb(PADR, CSCIR);
	val = inb(CSCDR);
	outb(PBDR, CSCIR);
	val |= (inb(CSCDR) << 8);
	outb(PCDR, CSCIR);
	val |= ((inb(CSCDR) & 0xf0) << 12);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dnp_dio_insn_config(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	अगर (chan < 8) अणु			/* Port A */
		mask = 1 << chan;
		outb(PAMR, CSCIR);
	पूर्ण अन्यथा अगर (chan < 16) अणु		/* Port B */
		mask = 1 << (chan - 8);
		outb(PBMR, CSCIR);
	पूर्ण अन्यथा अणु			/* Port C */
		/*
		 * We have to pay attention with port C.
		 * This is the meaning of PCMR:
		 *   Bit in PCMR:              7 6 5 4 3 2 1 0
		 *   Corresponding port C pin: d 3 d 2 d 1 d 0   d= करोn't touch
		 *
		 * Multiplication by 2 brings bits पूर्णांकo correct position
		 * क्रम PCMR!
		 */
		mask = 1 << ((chan - 16) * 2);
		outb(PCMR, CSCIR);
	पूर्ण

	val = inb(CSCDR);
	अगर (data[0] == COMEDI_OUTPUT)
		val |= mask;
	अन्यथा
		val &= ~mask;
	outb(val, CSCDR);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dnp_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	/*
	 * We use I/O ports 0x22, 0x23 and 0xa3-0xa9, which are always
	 * allocated क्रम the primary 8259, so we करोn't need to allocate
	 * them ourselves.
	 */

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* digital i/o subdevice                                             */
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = 20;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = dnp_dio_insn_bits;
	s->insn_config = dnp_dio_insn_config;

	/* configure all ports as input (शेष)                            */
	outb(PAMR, CSCIR);
	outb(0x00, CSCDR);
	outb(PBMR, CSCIR);
	outb(0x00, CSCDR);
	outb(PCMR, CSCIR);
	outb((inb(CSCDR) & 0xAA), CSCDR);

	वापस 0;
पूर्ण

अटल व्योम dnp_detach(काष्ठा comedi_device *dev)
अणु
	outb(PAMR, CSCIR);
	outb(0x00, CSCDR);
	outb(PBMR, CSCIR);
	outb(0x00, CSCDR);
	outb(PCMR, CSCIR);
	outb((inb(CSCDR) & 0xAA), CSCDR);
पूर्ण

अटल काष्ठा comedi_driver dnp_driver = अणु
	.driver_name	= "dnp-1486",
	.module		= THIS_MODULE,
	.attach		= dnp_attach,
	.detach		= dnp_detach,
पूर्ण;
module_comedi_driver(dnp_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
