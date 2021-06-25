<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adq12b.c
 * Driver क्रम MicroAxial ADQ12-B data acquisition and control card
 * written by jeremy theler <thelerg@ib.cnea.gov.ar>
 *	instituto balseiro
 *	commission nacional de energia atomica
 *	universidad nacional de cuyo
 *	argentina
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adq12b
 * Description: Driver क्रम MicroAxial ADQ12-B data acquisition and control card
 * Devices: [MicroAxial] ADQ12-B (adq12b)
 * Author: jeremy theler <thelerg@ib.cnea.gov.ar>
 * Updated: Thu, 21 Feb 2008 02:56:27 -0300
 * Status: works
 *
 * Configuration options:
 *   [0] - I/O base address (set with hardware jumpers)
 *		address		jumper JADR
 *		0x300		1 (factory शेष)
 *		0x320		2
 *		0x340		3
 *		0x360		4
 *		0x380		5
 *		0x3A0		6
 *   [1] - Analog Input unipolar/bipolar selection
 *		selection	option	JUB
 *		bipolar		0	2-3 (factory शेष)
 *		unipolar	1	1-2
 *   [2] - Analog Input single-ended/dअगरferential selection
 *		selection	option	JCHA	JCHB
 *		single-ended	0	1-2	1-2 (factory शेष)
 *		dअगरferential	1	2-3	2-3
 *
 * Driver क्रम the acquisition card ADQ12-B (without any add-on).
 *
 * - Analog input is subdevice 0 (16 channels single-ended or 8 dअगरferential)
 * - Digital input is subdevice 1 (5 channels)
 * - Digital output is subdevice 1 (8 channels)
 * - The PACER is not supported in this version
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedidev.h"

/* address scheme (page 2.17 of the manual) */
#घोषणा ADQ12B_CTREG		0x00
#घोषणा ADQ12B_CTREG_MSKP	BIT(7)	/* enable pacer पूर्णांकerrupt */
#घोषणा ADQ12B_CTREG_GTP	BIT(6)	/* enable pacer */
#घोषणा ADQ12B_CTREG_RANGE(x)	((x) << 4)
#घोषणा ADQ12B_CTREG_CHAN(x)	((x) << 0)
#घोषणा ADQ12B_STINR		0x00
#घोषणा ADQ12B_STINR_OUT2	BIT(7)	/* समयr 2 output state */
#घोषणा ADQ12B_STINR_OUTP	BIT(6)	/* pacer output state */
#घोषणा ADQ12B_STINR_EOC	BIT(5)	/* A/D end-of-conversion */
#घोषणा ADQ12B_STINR_IN_MASK	(0x1f << 0)
#घोषणा ADQ12B_OUTBR		0x04
#घोषणा ADQ12B_ADLOW		0x08
#घोषणा ADQ12B_ADHIG		0x09
#घोषणा ADQ12B_TIMER_BASE	0x0c

/* available ranges through the PGA gains */
अटल स्थिर काष्ठा comedi_lrange range_adq12b_ai_bipolar = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		BIP_RANGE(0.5)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_adq12b_ai_unipolar = अणु
	4, अणु
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5)
	पूर्ण
पूर्ण;

काष्ठा adq12b_निजी अणु
	अचिन्हित पूर्णांक last_ctreg;
पूर्ण;

अटल पूर्णांक adq12b_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + ADQ12B_STINR);
	अगर (status & ADQ12B_STINR_EOC)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक adq12b_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा adq12b_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	/* change channel and range only अगर it is dअगरferent from the previous */
	val = ADQ12B_CTREG_RANGE(range) | ADQ12B_CTREG_CHAN(chan);
	अगर (val != devpriv->last_ctreg) अणु
		outb(val, dev->iobase + ADQ12B_CTREG);
		devpriv->last_ctreg = val;
		usleep_range(50, 100);	/* रुको क्रम the mux to settle */
	पूर्ण

	val = inb(dev->iobase + ADQ12B_ADLOW);	/* trigger A/D */

	क्रम (i = 0; i < insn->n; i++) अणु
		ret = comedi_समयout(dev, s, insn, adq12b_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inb(dev->iobase + ADQ12B_ADHIG) << 8;
		val |= inb(dev->iobase + ADQ12B_ADLOW);	/* retriggers A/D */

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक adq12b_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	/* only bits 0-4 have inक्रमmation about digital inमाला_दो */
	data[1] = (inb(dev->iobase + ADQ12B_STINR) & ADQ12B_STINR_IN_MASK);

	वापस insn->n;
पूर्ण

अटल पूर्णांक adq12b_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		क्रम (chan = 0; chan < 8; chan++) अणु
			अगर ((mask >> chan) & 0x01) अणु
				val = (s->state >> chan) & 0x01;
				outb((val << 3) | chan,
				     dev->iobase + ADQ12B_OUTBR);
			पूर्ण
		पूर्ण
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक adq12b_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा adq12b_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	devpriv->last_ctreg = -1;	/* क्रमce ctreg update */

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	अगर (it->options[2]) अणु
		s->subdev_flags	= SDF_READABLE | SDF_DIFF;
		s->n_chan	= 8;
	पूर्ण अन्यथा अणु
		s->subdev_flags	= SDF_READABLE | SDF_GROUND;
		s->n_chan	= 16;
	पूर्ण
	s->maxdata	= 0xfff;
	s->range_table	= it->options[1] ? &range_adq12b_ai_unipolar
					 : &range_adq12b_ai_bipolar;
	s->insn_पढ़ो	= adq12b_ai_insn_पढ़ो;

	/* Digital Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 5;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= adq12b_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= adq12b_करो_insn_bits;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver adq12b_driver = अणु
	.driver_name	= "adq12b",
	.module		= THIS_MODULE,
	.attach		= adq12b_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(adq12b_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
