<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_parport.c
 * Comedi driver क्रम standard parallel port
 *
 * For more inक्रमmation see:
 *	http://retired.beyondlogic.org/spp/parallel.hपंचांग
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998,2001 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: comedi_parport
 * Description: Standard PC parallel port
 * Author: ds
 * Status: works in immediate mode
 * Devices: [standard] parallel port (comedi_parport)
 * Updated: Tue, 30 Apr 2002 21:11:45 -0700
 *
 * A cheap and easy way to get a few more digital I/O lines. Steal
 * additional parallel ports from old computers or your neighbors'
 * computers.
 *
 * Option list:
 *   0: I/O port base क्रम the parallel port.
 *   1: IRQ (optional)
 *
 * Parallel Port Lines:
 *
 *	 pin   subdev  chan  type  name
 *	-----  ------  ----  ----  --------------
 *	  1      2       0    DO   strobe
 *	  2      0       0    DIO  data 0
 *	  3      0       1    DIO  data 1
 *	  4      0       2    DIO  data 2
 *	  5      0       3    DIO  data 3
 *	  6      0       4    DIO  data 4
 *	  7      0       5    DIO  data 5
 *	  8      0       6    DIO  data 6
 *	  9      0       7    DIO  data 7
 *	 10      1       3    DI   ack
 *	 11      1       4    DI   busy
 *	 12      1       2    DI   paper out
 *	 13      1       1    DI   select in
 *	 14      2       1    DO   स्वतः LF
 *	 15      1       0    DI   error
 *	 16      2       2    DO   init
 *	 17      2       3    DO   select prपूर्णांकer
 *	18-25                      ground
 *
 * When an IRQ is configured subdevice 3 pretends to be a digital
 * input subdevice, but it always वापसs 0 when पढ़ो. However, अगर
 * you run a command with scan_begin_src=TRIG_EXT, it uses pin 10
 * as a बाह्यal trigger, which can be used to wake up tasks.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

/*
 * Register map
 */
#घोषणा PARPORT_DATA_REG	0x00
#घोषणा PARPORT_STATUS_REG	0x01
#घोषणा PARPORT_CTRL_REG	0x02
#घोषणा PARPORT_CTRL_IRQ_ENA	BIT(4)
#घोषणा PARPORT_CTRL_BIसूची_ENA	BIT(5)

अटल पूर्णांक parport_data_reg_insn_bits(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + PARPORT_DATA_REG);

	data[1] = inb(dev->iobase + PARPORT_DATA_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक parport_data_reg_insn_config(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक ctrl;
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0xff);
	अगर (ret)
		वापस ret;

	ctrl = inb(dev->iobase + PARPORT_CTRL_REG);
	अगर (s->io_bits)
		ctrl &= ~PARPORT_CTRL_BIसूची_ENA;
	अन्यथा
		ctrl |= PARPORT_CTRL_BIसूची_ENA;
	outb(ctrl, dev->iobase + PARPORT_CTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक parport_status_reg_insn_bits(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + PARPORT_STATUS_REG) >> 3;

	वापस insn->n;
पूर्ण

अटल पूर्णांक parport_ctrl_reg_insn_bits(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक ctrl;

	अगर (comedi_dio_update_state(s, data)) अणु
		ctrl = inb(dev->iobase + PARPORT_CTRL_REG);
		ctrl &= (PARPORT_CTRL_IRQ_ENA | PARPORT_CTRL_BIसूची_ENA);
		ctrl |= s->state;
		outb(ctrl, dev->iobase + PARPORT_CTRL_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक parport_पूर्णांकr_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	data[1] = 0;
	वापस insn->n;
पूर्ण

अटल पूर्णांक parport_पूर्णांकr_cmdtest(काष्ठा comedi_device *dev,
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

अटल पूर्णांक parport_पूर्णांकr_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक ctrl;

	ctrl = inb(dev->iobase + PARPORT_CTRL_REG);
	ctrl |= PARPORT_CTRL_IRQ_ENA;
	outb(ctrl, dev->iobase + PARPORT_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक parport_पूर्णांकr_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक ctrl;

	ctrl = inb(dev->iobase + PARPORT_CTRL_REG);
	ctrl &= ~PARPORT_CTRL_IRQ_ENA;
	outb(ctrl, dev->iobase + PARPORT_CTRL_REG);

	वापस 0;
पूर्ण

अटल irqवापस_t parport_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित लघु val = 0;

	ctrl = inb(dev->iobase + PARPORT_CTRL_REG);
	अगर (!(ctrl & PARPORT_CTRL_IRQ_ENA))
		वापस IRQ_NONE;

	comedi_buf_ग_लिखो_samples(s, &val, 1);
	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक parport_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x03);
	अगर (ret)
		वापस ret;

	अगर (it->options[1]) अणु
		ret = request_irq(it->options[1], parport_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	ret = comedi_alloc_subdevices(dev, dev->irq ? 4 : 3);
	अगर (ret)
		वापस ret;

	/* Digial I/O subdevice - Parallel port DATA रेजिस्टर */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= parport_data_reg_insn_bits;
	s->insn_config	= parport_data_reg_insn_config;

	/* Digial Input subdevice - Parallel port STATUS रेजिस्टर */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 5;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= parport_status_reg_insn_bits;

	/* Digial Output subdevice - Parallel port CONTROL रेजिस्टर */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= parport_ctrl_reg_insn_bits;

	अगर (dev->irq) अणु
		/* Digial Input subdevice - Interrupt support */
		s = &dev->subdevices[3];
		dev->पढ़ो_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE | SDF_CMD_READ;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= parport_पूर्णांकr_insn_bits;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= parport_पूर्णांकr_cmdtest;
		s->करो_cmd	= parport_पूर्णांकr_cmd;
		s->cancel	= parport_पूर्णांकr_cancel;
	पूर्ण

	outb(0, dev->iobase + PARPORT_DATA_REG);
	outb(0, dev->iobase + PARPORT_CTRL_REG);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver parport_driver = अणु
	.driver_name	= "comedi_parport",
	.module		= THIS_MODULE,
	.attach		= parport_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(parport_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi: Standard parallel port driver");
MODULE_LICENSE("GPL");
