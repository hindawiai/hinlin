<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dac02.c
 * Comedi driver क्रम DAC02 compatible boards
 * Copyright (C) 2014 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on the poc driver
 * Copyright (C) 2000 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Copyright (C) 2001 David A. Schleef <ds@schleef.org>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: dac02
 * Description: Comedi driver क्रम DAC02 compatible boards
 * Devices: [Keithley Metrabyte] DAC-02 (dac02)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Tue, 11 Mar 2014 11:27:19 -0700
 * Status: unknown
 *
 * Configuration options:
 *	[0] - I/O port base
 */

#समावेश <linux/module.h>

#समावेश "../comedidev.h"

/*
 * The output range is selected by jumpering pins on the I/O connector.
 *
 *	    Range      Chan #   Jumper pins        Output
 *	-------------  ------  -------------  -----------------
 *	   0 to 5V       0        21 to 22      24
 *	                 1        15 to 16      18
 *	   0 to 10V      0        20 to 22      24
 *	                 1        14 to 16      18
 *	    +/-5V        0        21 to 22      23
 *	                 1        15 to 16      17
 *	    +/-10V       0        20 to 22      23
 *	                 1        14 to 16      17
 *	  4 to 20mA      0        21 to 22      25
 *	                 1        15 to 16      19
 *	AC reference     0      In on pin 22    24 (2-quadrant)
 *	                        In on pin 22    23 (4-quadrant)
 *	                 1      In on pin 16    18 (2-quadrant)
 *	                        In on pin 16    17 (4-quadrant)
 */
अटल स्थिर काष्ठा comedi_lrange das02_ao_ranges = अणु
	6, अणु
		UNI_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(10),
		RANGE_mA(4, 20),
		RANGE_ext(0, 1)
	पूर्ण
पूर्ण;

/*
 * Register I/O map
 */
#घोषणा DAC02_AO_LSB(x)		(0x00 + ((x) * 2))
#घोषणा DAC02_AO_MSB(x)		(0x01 + ((x) * 2))

अटल पूर्णांक dac02_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		s->पढ़ोback[chan] = val;

		/*
		 * Unipolar outमाला_दो are true binary encoding.
		 * Bipolar outमाला_दो are complementary offset binary
		 * (that is, 0 = +full scale, maxdata = -full scale).
		 */
		अगर (comedi_range_is_bipolar(s, range))
			val = s->maxdata - val;

		/*
		 * DACs are द्विगुन-buffered.
		 * Write LSB then MSB to latch output.
		 */
		outb((val << 4) & 0xf0, dev->iobase + DAC02_AO_LSB(chan));
		outb((val >> 4) & 0xff, dev->iobase + DAC02_AO_MSB(chan));
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dac02_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x08);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* Analog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= &das02_ao_ranges;
	s->insn_ग_लिखो	= dac02_ao_insn_ग_लिखो;

	वापस comedi_alloc_subdev_पढ़ोback(s);
पूर्ण

अटल काष्ठा comedi_driver dac02_driver = अणु
	.driver_name	= "dac02",
	.module		= THIS_MODULE,
	.attach		= dac02_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(dac02_driver);

MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("Comedi driver for DAC02 compatible boards");
MODULE_LICENSE("GPL");
