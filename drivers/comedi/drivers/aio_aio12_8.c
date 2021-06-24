<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aio_aio12_8.c
 * Driver क्रम Access I/O Products PC-104 AIO12-8 Analog I/O Board
 * Copyright (C) 2006 C&C Technologies, Inc.
 */

/*
 * Driver: aio_aio12_8
 * Description: Access I/O Products PC-104 AIO12-8 Analog I/O Board
 * Author: Pablo Mejia <pablo.mejia@cctechnol.com>
 * Devices: [Access I/O] PC-104 AIO12-8 (aio_aio12_8),
 *   [Access I/O] PC-104 AI12-8 (aio_ai12_8),
 *   [Access I/O] PC-104 AO12-4 (aio_ao12_4)
 * Status: experimental
 *
 * Configuration Options:
 *   [0] - I/O port base address
 *
 * Notes:
 * Only synchronous operations are supported.
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"
#समावेश "8255.h"

/*
 * Register map
 */
#घोषणा AIO12_8_STATUS_REG		0x00
#घोषणा AIO12_8_STATUS_ADC_EOC		BIT(7)
#घोषणा AIO12_8_STATUS_PORT_C_COS	BIT(6)
#घोषणा AIO12_8_STATUS_IRQ_ENA		BIT(2)
#घोषणा AIO12_8_INTERRUPT_REG		0x01
#घोषणा AIO12_8_INTERRUPT_ADC		BIT(7)
#घोषणा AIO12_8_INTERRUPT_COS		BIT(6)
#घोषणा AIO12_8_INTERRUPT_COUNTER1	BIT(5)
#घोषणा AIO12_8_INTERRUPT_PORT_C3	BIT(4)
#घोषणा AIO12_8_INTERRUPT_PORT_C0	BIT(3)
#घोषणा AIO12_8_INTERRUPT_ENA		BIT(2)
#घोषणा AIO12_8_ADC_REG			0x02
#घोषणा AIO12_8_ADC_MODE(x)		(((x) & 0x3) << 6)
#घोषणा AIO12_8_ADC_MODE_NORMAL		AIO12_8_ADC_MODE(0)
#घोषणा AIO12_8_ADC_MODE_INT_CLK	AIO12_8_ADC_MODE(1)
#घोषणा AIO12_8_ADC_MODE_STANDBY	AIO12_8_ADC_MODE(2)
#घोषणा AIO12_8_ADC_MODE_POWERDOWN	AIO12_8_ADC_MODE(3)
#घोषणा AIO12_8_ADC_ACQ(x)		(((x) & 0x1) << 5)
#घोषणा AIO12_8_ADC_ACQ_3USEC		AIO12_8_ADC_ACQ(0)
#घोषणा AIO12_8_ADC_ACQ_PROGRAM		AIO12_8_ADC_ACQ(1)
#घोषणा AIO12_8_ADC_RANGE(x)		((x) << 3)
#घोषणा AIO12_8_ADC_CHAN(x)		((x) << 0)
#घोषणा AIO12_8_DAC_REG(x)		(0x04 + (x) * 2)
#घोषणा AIO12_8_8254_BASE_REG		0x0c
#घोषणा AIO12_8_8255_BASE_REG		0x10
#घोषणा AIO12_8_DIO_CONTROL_REG		0x14
#घोषणा AIO12_8_DIO_CONTROL_TST		BIT(0)
#घोषणा AIO12_8_ADC_TRIGGER_REG		0x15
#घोषणा AIO12_8_ADC_TRIGGER_RANGE(x)	((x) << 3)
#घोषणा AIO12_8_ADC_TRIGGER_CHAN(x)	((x) << 0)
#घोषणा AIO12_8_TRIGGER_REG		0x16
#घोषणा AIO12_8_TRIGGER_ADTRIG		BIT(1)
#घोषणा AIO12_8_TRIGGER_DACTRIG		BIT(0)
#घोषणा AIO12_8_COS_REG			0x17
#घोषणा AIO12_8_DAC_ENABLE_REG		0x18
#घोषणा AIO12_8_DAC_ENABLE_REF_ENA	BIT(0)

अटल स्थिर काष्ठा comedi_lrange aio_aio12_8_range = अणु
	4, अणु
		UNI_RANGE(5),
		BIP_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

काष्ठा aio12_8_boardtype अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक has_ai:1;
	अचिन्हित पूर्णांक has_ao:1;
पूर्ण;

अटल स्थिर काष्ठा aio12_8_boardtype board_types[] = अणु
	अणु
		.name		= "aio_aio12_8",
		.has_ai		= 1,
		.has_ao		= 1,
	पूर्ण, अणु
		.name		= "aio_ai12_8",
		.has_ai		= 1,
	पूर्ण, अणु
		.name		= "aio_ao12_4",
		.has_ao		= 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक aio_aio12_8_ai_eoc(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + AIO12_8_STATUS_REG);
	अगर (status & AIO12_8_STATUS_ADC_EOC)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक aio_aio12_8_ai_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	अचिन्हित अक्षर control;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Setup the control byte क्रम पूर्णांकernal 2MHz घड़ी, 3uS conversion,
	 * at the desired range of the requested channel.
	 */
	control = AIO12_8_ADC_MODE_NORMAL | AIO12_8_ADC_ACQ_3USEC |
		  AIO12_8_ADC_RANGE(range) | AIO12_8_ADC_CHAN(chan);

	/* Read status to clear EOC latch */
	inb(dev->iobase + AIO12_8_STATUS_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		/*  Setup and start conversion */
		outb(control, dev->iobase + AIO12_8_ADC_REG);

		/*  Wait क्रम conversion to complete */
		ret = comedi_समयout(dev, s, insn, aio_aio12_8_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inw(dev->iobase + AIO12_8_ADC_REG) & s->maxdata;

		/* munge bipolar 2's complement data to offset binary */
		अगर (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक aio_aio12_8_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	/* enable DACs */
	outb(AIO12_8_DAC_ENABLE_REF_ENA, dev->iobase + AIO12_8_DAC_ENABLE_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, dev->iobase + AIO12_8_DAC_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक aio_aio12_8_counter_insn_config(काष्ठा comedi_device *dev,
					   काष्ठा comedi_subdevice *s,
					   काष्ठा comedi_insn *insn,
					   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	चयन (data[0]) अणु
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		/*
		 * Channels 0 and 2 have बाह्यal घड़ी sources.
		 * Channel 1 has a fixed 1 MHz घड़ी source.
		 */
		data[0] = 0;
		data[1] = (chan == 1) ? I8254_OSC_BASE_1MHZ : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक aio_aio12_8_attach(काष्ठा comedi_device *dev,
			      काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा aio12_8_boardtype *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 32);
	अगर (ret)
		वापस ret;

	dev->pacer = comedi_8254_init(dev->iobase + AIO12_8_8254_BASE_REG,
				      0, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	अगर (board->has_ai) अणु
		s->type		= COMEDI_SUBD_AI;
		s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
		s->n_chan	= 8;
		s->maxdata	= 0x0fff;
		s->range_table	= &aio_aio12_8_range;
		s->insn_पढ़ो	= aio_aio12_8_ai_पढ़ो;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
		s->n_chan	= 4;
		s->maxdata	= 0x0fff;
		s->range_table	= &aio_aio12_8_range;
		s->insn_ग_लिखो	= aio_aio12_8_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital I/O subdevice (8255) */
	s = &dev->subdevices[2];
	ret = subdev_8255_init(dev, s, शून्य, AIO12_8_8255_BASE_REG);
	अगर (ret)
		वापस ret;

	/* Counter subdevice (8254) */
	s = &dev->subdevices[3];
	comedi_8254_subdevice_init(s, dev->pacer);

	dev->pacer->insn_config = aio_aio12_8_counter_insn_config;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver aio_aio12_8_driver = अणु
	.driver_name	= "aio_aio12_8",
	.module		= THIS_MODULE,
	.attach		= aio_aio12_8_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &board_types[0].name,
	.num_names	= ARRAY_SIZE(board_types),
	.offset		= माप(काष्ठा aio12_8_boardtype),
पूर्ण;
module_comedi_driver(aio_aio12_8_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Access I/O AIO12-8 Analog I/O Board");
MODULE_LICENSE("GPL");
