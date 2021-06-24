<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *     comedi/drivers/ni_daq_700.c
 *     Driver क्रम DAQCard-700 DIO/AI
 *     copied from 8255
 *
 *     COMEDI - Linux Control and Measurement Device Interface
 *     Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_daq_700
 * Description: National Instruments PCMCIA DAQCard-700
 * Author: Fred Brooks <nsaspook@nsaspook.com>,
 *   based on ni_daq_dio24 by Daniel Vecino Castel <dvecino@able.es>
 * Devices: [National Instruments] PCMCIA DAQ-Card-700 (ni_daq_700)
 * Status: works
 * Updated: Wed, 21 May 2014 12:07:20 +0000
 *
 * The daqcard-700 appears in Comedi as a  digital I/O subdevice (0) with
 * 16 channels and a analog input subdevice (1) with 16 single-ended channels
 * or 8 dअगरferential channels, and three input ranges.
 *
 * Digital:  The channel 0 corresponds to the daqcard-700's output
 * port, bit 0; channel 8 corresponds to the input port, bit 0.
 *
 * Digital direction configuration: channels 0-7 output, 8-15 input.
 *
 * Analog: The input  range is 0 to 4095 with a शेष of -10 to +10 volts.
 * Valid ranges:
 *       0 क्रम -10 to 10V bipolar
 *       1 क्रम -5 to 5V bipolar
 *       2 क्रम -2.5 to 2.5V bipolar
 *
 * IRQ is asचिन्हित but not used.
 *
 * Manuals:	Register level:	https://www.ni.com/pdf/manuals/340698.pdf
 *		User Manual:	https://www.ni.com/pdf/manuals/320676d.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pcmcia.h"

/* daqcard700 रेजिस्टरs */
#घोषणा DIO_W		0x04	/* WO 8bit */
#घोषणा DIO_R		0x05	/* RO 8bit */
#घोषणा CMD_R1		0x00	/* WO 8bit */
#घोषणा CMD_R2		0x07	/* RW 8bit */
#घोषणा CMD_R3		0x05	/* W0 8bit */
#घोषणा STA_R1		0x00	/* RO 8bit */
#घोषणा STA_R2		0x01	/* RO 8bit */
#घोषणा ADFIFO_R	0x02	/* RO 16bit */
#घोषणा ADCLEAR_R	0x01	/* WO 8bit */
#घोषणा CDA_R0		0x08	/* RW 8bit */
#घोषणा CDA_R1		0x09	/* RW 8bit */
#घोषणा CDA_R2		0x0A	/* RW 8bit */
#घोषणा CMO_R		0x0B	/* RO 8bit */
#घोषणा TIC_R		0x06	/* WO 8bit */
/* daqcard700 modes */
#घोषणा CMD_R3_DIFF     0x04    /* dअगरf mode */

अटल स्थिर काष्ठा comedi_lrange range_daq700_ai = अणु
	3,
	अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5)
	पूर्ण
पूर्ण;

अटल पूर्णांक daq700_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0xff)
			outb(s->state & 0xff, dev->iobase + DIO_W);
	पूर्ण

	val = s->state & 0xff;
	val |= inb(dev->iobase + DIO_R) << 8;

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक daq700_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	/* The DIO channels are not configurable, fix the io_bits */
	s->io_bits = 0x00ff;

	वापस insn->n;
पूर्ण

अटल पूर्णांक daq700_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + STA_R2);
	अगर ((status & 0x03))
		वापस -EOVERFLOW;
	status = inb(dev->iobase + STA_R1);
	अगर ((status & 0x02))
		वापस -ENODATA;
	अगर ((status & 0x11) == 0x01)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक daq700_ai_rinsn(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक n;
	पूर्णांक d;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chan	= CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक aref	= CR_AREF(insn->chanspec);
	अचिन्हित पूर्णांक range	= CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक r3_bits	= 0;

	/* set channel input modes */
	अगर (aref == AREF_DIFF)
		r3_bits |= CMD_R3_DIFF;
	/* ग_लिखो channel mode/range */
	अगर (range >= 1)
		range++;        /* convert range to hardware value */
	outb(r3_bits | (range & 0x03), dev->iobase + CMD_R3);

	/* ग_लिखो channel to multiplexer */
	/* set mask scan bit high to disable scanning */
	outb(chan | 0x80, dev->iobase + CMD_R1);
	/* mux needs 2us to really settle [Fred Brooks]. */
	udelay(2);

	/* convert n samples */
	क्रम (n = 0; n < insn->n; n++) अणु
		/* trigger conversion with out0 L to H */
		outb(0x00, dev->iobase + CMD_R2); /* enable ADC conversions */
		outb(0x30, dev->iobase + CMO_R); /* mode 0 out0 L, from H */
		outb(0x00, dev->iobase + ADCLEAR_R);	/* clear the ADC FIFO */
		/* पढ़ो 16bit junk from FIFO to clear */
		inw(dev->iobase + ADFIFO_R);
		/* mode 1 out0 H, L to H, start conversion */
		outb(0x32, dev->iobase + CMO_R);

		/* रुको क्रम conversion to end */
		ret = comedi_समयout(dev, s, insn, daq700_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* पढ़ो data */
		d = inw(dev->iobase + ADFIFO_R);
		/* mangle the data as necessary */
		/* Bipolar Offset Binary: 0 to 4095 क्रम -10 to +10 */
		d &= 0x0fff;
		d ^= 0x0800;
		data[n] = d;
	पूर्ण
	वापस n;
पूर्ण

/*
 * Data acquisition is enabled.
 * The counter 0 output is high.
 * The I/O connector pin CLK1 drives counter 1 source.
 * Multiple-channel scanning is disabled.
 * All पूर्णांकerrupts are disabled.
 * The analog input range is set to +-10 V
 * The analog input mode is single-ended.
 * The analog input circuitry is initialized to channel 0.
 * The A/D FIFO is cleared.
 */
अटल व्योम daq700_ai_config(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित दीर्घ iobase = dev->iobase;

	outb(0x80, iobase + CMD_R1);	/* disable scanning, ADC to chan 0 */
	outb(0x00, iobase + CMD_R2);	/* clear all bits */
	outb(0x00, iobase + CMD_R3);	/* set +-10 range */
	outb(0x32, iobase + CMO_R);	/* config counter mode1, out0 to H */
	outb(0x00, iobase + TIC_R);	/* clear counter पूर्णांकerrupt */
	outb(0x00, iobase + ADCLEAR_R);	/* clear the ADC FIFO */
	inw(iobase + ADFIFO_R);		/* पढ़ो 16bit junk from FIFO to clear */
पूर्ण

अटल पूर्णांक daq700_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	link->config_flags |= CONF_AUTO_SET_IO;
	ret = comedi_pcmcia_enable(dev, शून्य);
	अगर (ret)
		वापस ret;
	dev->iobase = link->resource[0]->start;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/* DAQCard-700 dio */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 16;
	s->range_table	= &range_digital;
	s->maxdata	= 1;
	s->insn_bits	= daq700_dio_insn_bits;
	s->insn_config	= daq700_dio_insn_config;
	s->io_bits	= 0x00ff;

	/* DAQCard-700 ai */
	s = &dev->subdevices[1];
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan = 16;
	s->maxdata = BIT(12) - 1;
	s->range_table = &range_daq700_ai;
	s->insn_पढ़ो = daq700_ai_rinsn;
	daq700_ai_config(dev, s);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver daq700_driver = अणु
	.driver_name	= "ni_daq_700",
	.module		= THIS_MODULE,
	.स्वतः_attach	= daq700_स्वतः_attach,
	.detach		= comedi_pcmcia_disable,
पूर्ण;

अटल पूर्णांक daq700_cs_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &daq700_driver);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id daq700_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x4743),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, daq700_cs_ids);

अटल काष्ठा pcmcia_driver daq700_cs_driver = अणु
	.name		= "ni_daq_700",
	.owner		= THIS_MODULE,
	.id_table	= daq700_cs_ids,
	.probe		= daq700_cs_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
पूर्ण;
module_comedi_pcmcia_driver(daq700_driver, daq700_cs_driver);

MODULE_AUTHOR("Fred Brooks <nsaspook@nsaspook.com>");
MODULE_DESCRIPTION(
	"Comedi driver for National Instruments PCMCIA DAQCard-700 DIO/AI");
MODULE_LICENSE("GPL");
