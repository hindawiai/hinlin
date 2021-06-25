<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aio_iiro_16.c
 * Comedi driver क्रम Access I/O Products 104-IIRO-16 board
 * Copyright (C) 2006 C&C Technologies, Inc.
 */

/*
 * Driver: aio_iiro_16
 * Description: Access I/O Products PC/104 Isolated Input/Relay Output Board
 * Author: Zaअक्षरy Ware <zach.ware@cctechnol.com>
 * Devices: [Access I/O] 104-IIRO-16 (aio_iiro_16)
 * Status: experimental
 *
 * Configuration Options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional)
 *
 * The board supports पूर्णांकerrupts on change of state of the digital inमाला_दो.
 * The sample data वापसed by the async command indicates which inमाला_दो
 * changed state and the current state of the inमाला_दो:
 *
 *	Bit 23 - IRQ Enable (1) / Disable (0)
 *	Bit 17 - Input 8-15 Changed State (1 = Changed, 0 = No Change)
 *	Bit 16 - Input 0-7 Changed State (1 = Changed, 0 = No Change)
 *	Bit 15 - Digital input 15
 *	...
 *	Bit 0  - Digital input 0
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#घोषणा AIO_IIRO_16_RELAY_0_7		0x00
#घोषणा AIO_IIRO_16_INPUT_0_7		0x01
#घोषणा AIO_IIRO_16_IRQ			0x02
#घोषणा AIO_IIRO_16_RELAY_8_15		0x04
#घोषणा AIO_IIRO_16_INPUT_8_15		0x05
#घोषणा AIO_IIRO_16_STATUS		0x07
#घोषणा AIO_IIRO_16_STATUS_IRQE		BIT(7)
#घोषणा AIO_IIRO_16_STATUS_INPUT_8_15	BIT(1)
#घोषणा AIO_IIRO_16_STATUS_INPUT_0_7	BIT(0)

अटल अचिन्हित पूर्णांक aio_iiro_16_पढ़ो_inमाला_दो(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + AIO_IIRO_16_INPUT_0_7);
	val |= inb(dev->iobase + AIO_IIRO_16_INPUT_8_15) << 8;

	वापस val;
पूर्ण

अटल irqवापस_t aio_iiro_16_cos(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक val;

	status = inb(dev->iobase + AIO_IIRO_16_STATUS);
	अगर (!(status & AIO_IIRO_16_STATUS_IRQE))
		वापस IRQ_NONE;

	val = aio_iiro_16_पढ़ो_inमाला_दो(dev);
	val |= (status << 16);

	comedi_buf_ग_लिखो_samples(s, &val, 1);
	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम aio_iiro_enable_irq(काष्ठा comedi_device *dev, bool enable)
अणु
	अगर (enable)
		inb(dev->iobase + AIO_IIRO_16_IRQ);
	अन्यथा
		outb(0, dev->iobase + AIO_IIRO_16_IRQ);
पूर्ण

अटल पूर्णांक aio_iiro_16_cos_cancel(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	aio_iiro_enable_irq(dev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक aio_iiro_16_cos_cmd(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	aio_iiro_enable_irq(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक aio_iiro_16_cos_cmdtest(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक aio_iiro_16_करो_insn_bits(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, dev->iobase + AIO_IIRO_16_RELAY_0_7);
		outb((s->state >> 8) & 0xff,
		     dev->iobase + AIO_IIRO_16_RELAY_8_15);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक aio_iiro_16_di_insn_bits(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	data[1] = aio_iiro_16_पढ़ो_inमाला_दो(dev);

	वापस insn->n;
पूर्ण

अटल पूर्णांक aio_iiro_16_attach(काष्ठा comedi_device *dev,
			      काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x8);
	अगर (ret)
		वापस ret;

	aio_iiro_enable_irq(dev, false);

	/*
	 * Digital input change of state पूर्णांकerrupts are optionally supported
	 * using IRQ 2-7, 10-12, 14, or 15.
	 */
	अगर ((1 << it->options[1]) & 0xdcfc) अणु
		ret = request_irq(it->options[1], aio_iiro_16_cos, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/* Digital Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= aio_iiro_16_करो_insn_bits;

	/* get the initial state of the relays */
	s->state = inb(dev->iobase + AIO_IIRO_16_RELAY_0_7) |
		   (inb(dev->iobase + AIO_IIRO_16_RELAY_8_15) << 8);

	/* Digital Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= aio_iiro_16_di_insn_bits;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ | SDF_LSAMPL;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= aio_iiro_16_cos_cmdtest;
		s->करो_cmd	= aio_iiro_16_cos_cmd;
		s->cancel	= aio_iiro_16_cos_cancel;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver aio_iiro_16_driver = अणु
	.driver_name	= "aio_iiro_16",
	.module		= THIS_MODULE,
	.attach		= aio_iiro_16_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(aio_iiro_16_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Access I/O Products 104-IIRO-16 board");
MODULE_LICENSE("GPL");
