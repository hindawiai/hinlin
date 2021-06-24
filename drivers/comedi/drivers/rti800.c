<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/rti800.c
 * Hardware driver क्रम Analog Devices RTI-800/815 board
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: rti800
 * Description: Analog Devices RTI-800/815
 * Devices: [Analog Devices] RTI-800 (rti800), RTI-815 (rti815)
 * Author: David A. Schleef <ds@schleef.org>
 * Status: unknown
 * Updated: Fri, 05 Sep 2008 14:50:44 +0100
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (not supported / unused)
 *   [2] - A/D mux/reference (number of channels)
 *	   0 = dअगरferential
 *	   1 = pseuकरोdअगरferential (common)
 *	   2 = single-ended
 *   [3] - A/D range
 *	   0 = [-10,10]
 *	   1 = [-5,5]
 *	   2 = [0,10]
 *   [4] - A/D encoding
 *	   0 = two's complement
 *	   1 = straight binary
 *   [5] - DAC 0 range
 *	   0 = [-10,10]
 *	   1 = [0,10]
 *   [6] - DAC 0 encoding
 *	   0 = two's complement
 *	   1 = straight binary
 *   [7] - DAC 1 range (same as DAC 0)
 *   [8] - DAC 1 encoding (same as DAC 0)
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "../comedidev.h"

/*
 * Register map
 */
#घोषणा RTI800_CSR		0x00
#घोषणा RTI800_CSR_BUSY		BIT(7)
#घोषणा RTI800_CSR_DONE		BIT(6)
#घोषणा RTI800_CSR_OVERRUN	BIT(5)
#घोषणा RTI800_CSR_TCR		BIT(4)
#घोषणा RTI800_CSR_DMA_ENAB	BIT(3)
#घोषणा RTI800_CSR_INTR_TC	BIT(2)
#घोषणा RTI800_CSR_INTR_EC	BIT(1)
#घोषणा RTI800_CSR_INTR_OVRN	BIT(0)
#घोषणा RTI800_MUXGAIN		0x01
#घोषणा RTI800_CONVERT		0x02
#घोषणा RTI800_ADCLO		0x03
#घोषणा RTI800_ADCHI		0x04
#घोषणा RTI800_DAC0LO		0x05
#घोषणा RTI800_DAC0HI		0x06
#घोषणा RTI800_DAC1LO		0x07
#घोषणा RTI800_DAC1HI		0x08
#घोषणा RTI800_CLRFLAGS		0x09
#घोषणा RTI800_DI		0x0a
#घोषणा RTI800_DO		0x0b
#घोषणा RTI800_9513A_DATA	0x0c
#घोषणा RTI800_9513A_CNTRL	0x0d
#घोषणा RTI800_9513A_STATUS	0x0d

अटल स्थिर काष्ठा comedi_lrange range_rti800_ai_10_bipolar = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.02)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_rti800_ai_5_bipolar = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_rti800_ai_unipolar = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.02)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर rti800_ai_ranges[] = अणु
	&range_rti800_ai_10_bipolar,
	&range_rti800_ai_5_bipolar,
	&range_rti800_ai_unipolar,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर rti800_ao_ranges[] = अणु
	&range_bipolar10,
	&range_unipolar10,
पूर्ण;

काष्ठा rti800_board अणु
	स्थिर अक्षर *name;
	पूर्णांक has_ao;
पूर्ण;

अटल स्थिर काष्ठा rti800_board rti800_boardtypes[] = अणु
	अणु
		.name		= "rti800",
	पूर्ण, अणु
		.name		= "rti815",
		.has_ao		= 1,
	पूर्ण,
पूर्ण;

काष्ठा rti800_निजी अणु
	bool adc_2comp;
	bool dac_2comp[2];
	स्थिर काष्ठा comedi_lrange *ao_range_type_list[2];
	अचिन्हित अक्षर muxgain_bits;
पूर्ण;

अटल पूर्णांक rti800_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + RTI800_CSR);
	अगर (status & RTI800_CSR_OVERRUN) अणु
		outb(0, dev->iobase + RTI800_CLRFLAGS);
		वापस -EOVERFLOW;
	पूर्ण
	अगर (status & RTI800_CSR_DONE)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rti800_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा rti800_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक gain = CR_RANGE(insn->chanspec);
	अचिन्हित अक्षर muxgain_bits;
	पूर्णांक ret;
	पूर्णांक i;

	inb(dev->iobase + RTI800_ADCHI);
	outb(0, dev->iobase + RTI800_CLRFLAGS);

	muxgain_bits = chan | (gain << 5);
	अगर (muxgain_bits != devpriv->muxgain_bits) अणु
		devpriv->muxgain_bits = muxgain_bits;
		outb(devpriv->muxgain_bits, dev->iobase + RTI800_MUXGAIN);
		/*
		 * Without a delay here, the RTI_CSR_OVERRUN bit
		 * माला_लो set, and you will have an error.
		 */
		अगर (insn->n > 0) अणु
			पूर्णांक delay = (gain == 0) ? 10 :
				    (gain == 1) ? 20 :
				    (gain == 2) ? 40 : 80;

			udelay(delay);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val;

		outb(0, dev->iobase + RTI800_CONVERT);

		ret = comedi_समयout(dev, s, insn, rti800_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inb(dev->iobase + RTI800_ADCLO);
		val |= (inb(dev->iobase + RTI800_ADCHI) & 0xf) << 8;

		अगर (devpriv->adc_2comp)
			val = comedi_offset_munge(s, val);

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक rti800_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा rti800_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक reg_lo = chan ? RTI800_DAC1LO : RTI800_DAC0LO;
	पूर्णांक reg_hi = chan ? RTI800_DAC1HI : RTI800_DAC0HI;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		अगर (devpriv->dac_2comp[chan])
			val = comedi_offset_munge(s, val);

		outb(val & 0xff, dev->iobase + reg_lo);
		outb((val >> 8) & 0xff, dev->iobase + reg_hi);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक rti800_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + RTI800_DI);
	वापस insn->n;
पूर्ण

अटल पूर्णांक rti800_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		/* Outमाला_दो are inverted... */
		outb(s->state ^ 0xff, dev->iobase + RTI800_DO);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक rti800_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा rti800_board *board = dev->board_ptr;
	काष्ठा rti800_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	outb(0, dev->iobase + RTI800_CSR);
	inb(dev->iobase + RTI800_ADCHI);
	outb(0, dev->iobase + RTI800_CLRFLAGS);

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	devpriv->adc_2comp = (it->options[4] == 0);
	devpriv->dac_2comp[0] = (it->options[6] == 0);
	devpriv->dac_2comp[1] = (it->options[8] == 0);
	/* invalid, क्रमces the MUXGAIN रेजिस्टर to be set when first used */
	devpriv->muxgain_bits = 0xff;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* ai subdevice */
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	s->n_chan	= (it->options[2] ? 16 : 8);
	s->insn_पढ़ो	= rti800_ai_insn_पढ़ो;
	s->maxdata	= 0x0fff;
	s->range_table	= (it->options[3] < ARRAY_SIZE(rti800_ai_ranges))
				? rti800_ai_ranges[it->options[3]]
				: &range_unknown;

	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		/* ao subdevice (only on rti815) */
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->range_table_list = devpriv->ao_range_type_list;
		devpriv->ao_range_type_list[0] =
			(it->options[5] < ARRAY_SIZE(rti800_ao_ranges))
				? rti800_ao_ranges[it->options[5]]
				: &range_unknown;
		devpriv->ao_range_type_list[1] =
			(it->options[7] < ARRAY_SIZE(rti800_ao_ranges))
				? rti800_ao_ranges[it->options[7]]
				: &range_unknown;
		s->insn_ग_लिखो	= rti800_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[2];
	/* di */
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->insn_bits	= rti800_di_insn_bits;
	s->maxdata	= 1;
	s->range_table	= &range_digital;

	s = &dev->subdevices[3];
	/* करो */
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->insn_bits	= rti800_करो_insn_bits;
	s->maxdata	= 1;
	s->range_table	= &range_digital;

	/*
	 * There is also an Am9513 समयr on these boards. This subdevice
	 * is not currently supported.
	 */

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver rti800_driver = अणु
	.driver_name	= "rti800",
	.module		= THIS_MODULE,
	.attach		= rti800_attach,
	.detach		= comedi_legacy_detach,
	.num_names	= ARRAY_SIZE(rti800_boardtypes),
	.board_name	= &rti800_boardtypes[0].name,
	.offset		= माप(काष्ठा rti800_board),
पूर्ण;
module_comedi_driver(rti800_driver);

MODULE_DESCRIPTION("Comedi: RTI-800 Multifunction Analog/Digital board");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
