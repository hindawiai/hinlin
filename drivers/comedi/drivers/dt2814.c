<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/dt2814.c
 * Hardware driver क्रम Data Translation DT2814
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: dt2814
 * Description: Data Translation DT2814
 * Author: ds
 * Status: complete
 * Devices: [Data Translation] DT2814 (dt2814)
 *
 * Configuration options:
 * [0] - I/O port base address
 * [1] - IRQ
 *
 * This card has 16 analog inमाला_दो multiplexed onto a 12 bit ADC.  There
 * is a minimally useful onboard घड़ी.  The base frequency क्रम the
 * घड़ी is selected by jumpers, and the घड़ी भागider can be selected
 * via programmed I/O.  Unक्रमtunately, the घड़ी भागider can only be
 * a घातer of 10, from 1 to 10^7, of which only 3 or 4 are useful.  In
 * addition, the घड़ी करोes not seem to be very accurate.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "../comedidev.h"

#समावेश <linux/delay.h>

#घोषणा DT2814_CSR 0
#घोषणा DT2814_DATA 1

/*
 * flags
 */

#घोषणा DT2814_FINISH 0x80
#घोषणा DT2814_ERR 0x40
#घोषणा DT2814_BUSY 0x20
#घोषणा DT2814_ENB 0x10
#घोषणा DT2814_CHANMASK 0x0f

#घोषणा DT2814_TIMEOUT 10
#घोषणा DT2814_MAX_SPEED 100000	/* Arbitrary 10 khz limit */

अटल पूर्णांक dt2814_ai_notbusy(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DT2814_CSR);
	अगर (context)
		*(अचिन्हित पूर्णांक *)context = status;
	अगर (status & DT2814_BUSY)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक dt2814_ai_clear(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक status = 0;
	पूर्णांक ret;

	/* Wait until not busy and get status रेजिस्टर value. */
	ret = comedi_समयout(dev, शून्य, शून्य, dt2814_ai_notbusy,
			     (अचिन्हित दीर्घ)&status);
	अगर (ret)
		वापस ret;

	अगर (status & (DT2814_FINISH | DT2814_ERR)) अणु
		/*
		 * There unपढ़ो data, or the error flag is set.
		 * Read the data रेजिस्टर twice to clear the condition.
		 */
		inb(dev->iobase + DT2814_DATA);
		inb(dev->iobase + DT2814_DATA);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dt2814_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DT2814_CSR);
	अगर (status & DT2814_FINISH)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dt2814_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक n, hi, lo;
	पूर्णांक chan;
	पूर्णांक ret;

	dt2814_ai_clear(dev);	/* clear stale data or error */
	क्रम (n = 0; n < insn->n; n++) अणु
		chan = CR_CHAN(insn->chanspec);

		outb(chan, dev->iobase + DT2814_CSR);

		ret = comedi_समयout(dev, s, insn, dt2814_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		hi = inb(dev->iobase + DT2814_DATA);
		lo = inb(dev->iobase + DT2814_DATA);

		data[n] = (hi << 4) | (lo >> 4);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक dt2814_ns_to_समयr(अचिन्हित पूर्णांक *ns, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक f;

	/* XXX ignores flags */

	f = 10000;		/* ns */
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((2 * (*ns)) < (f * 11))
			अवरोध;
		f *= 10;
	पूर्ण

	*ns = f;

	वापस i;
पूर्ण

अटल पूर्णांक dt2814_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg, 1000000000);
	err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
					    DT2814_MAX_SPEED);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 2);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	arg = cmd->scan_begin_arg;
	dt2814_ns_to_समयr(&arg, cmd->flags);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक dt2814_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक chan;
	पूर्णांक trigvar;

	dt2814_ai_clear(dev);	/* clear stale data or error */
	trigvar = dt2814_ns_to_समयr(&cmd->scan_begin_arg, cmd->flags);

	chan = CR_CHAN(cmd->chanlist[0]);

	outb(chan | DT2814_ENB | (trigvar << 5), dev->iobase + DT2814_CSR);

	वापस 0;
पूर्ण

अटल पूर्णांक dt2814_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	status = inb(dev->iobase + DT2814_CSR);
	अगर (status & DT2814_ENB) अणु
		/*
		 * Clear the समयd trigger enable bit.
		 *
		 * Note: turning off समयd mode triggers another
		 * sample.  This will be mopped up by the calls to
		 * dt2814_ai_clear().
		 */
		outb(status & DT2814_CHANMASK, dev->iobase + DT2814_CSR);
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);
	वापस 0;
पूर्ण

अटल irqवापस_t dt2814_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async;
	अचिन्हित पूर्णांक lo, hi;
	अचिन्हित लघु data;
	अचिन्हित पूर्णांक status;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "spurious interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	async = s->async;

	spin_lock(&dev->spinlock);

	status = inb(dev->iobase + DT2814_CSR);
	अगर (!(status & DT2814_ENB)) अणु
		/* Timed acquisition not enabled.  Nothing to करो. */
		spin_unlock(&dev->spinlock);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!(status & (DT2814_FINISH | DT2814_ERR))) अणु
		/* Spurious पूर्णांकerrupt? */
		spin_unlock(&dev->spinlock);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Read data or clear error. */
	hi = inb(dev->iobase + DT2814_DATA);
	lo = inb(dev->iobase + DT2814_DATA);

	data = (hi << 4) | (lo >> 4);

	अगर (status & DT2814_ERR) अणु
		async->events |= COMEDI_CB_ERROR;
	पूर्ण अन्यथा अणु
		comedi_buf_ग_लिखो_samples(s, &data, 1);
		अगर (async->cmd.stop_src == TRIG_COUNT &&
		    async->scans_करोne >=  async->cmd.stop_arg) अणु
			async->events |= COMEDI_CB_EOA;
		पूर्ण
	पूर्ण
	अगर (async->events & COMEDI_CB_CANCEL_MASK) अणु
		/*
		 * Disable समयd mode.
		 *
		 * Note: turning off समयd mode triggers another
		 * sample.  This will be mopped up by the calls to
		 * dt2814_ai_clear().
		 */
		outb(status & DT2814_CHANMASK, dev->iobase + DT2814_CSR);
	पूर्ण

	spin_unlock(&dev->spinlock);

	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dt2814_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x2);
	अगर (ret)
		वापस ret;

	outb(0, dev->iobase + DT2814_CSR);
	अगर (dt2814_ai_clear(dev)) अणु
		dev_err(dev->class_dev, "reset error (fatal)\n");
		वापस -EIO;
	पूर्ण

	अगर (it->options[1]) अणु
		ret = request_irq(it->options[1], dt2814_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND;
	s->n_chan = 16;		/* XXX */
	s->insn_पढ़ो = dt2814_ai_insn_पढ़ो;
	s->maxdata = 0xfff;
	s->range_table = &range_unknown;	/* XXX */
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags |= SDF_CMD_READ;
		s->len_chanlist = 1;
		s->करो_cmd = dt2814_ai_cmd;
		s->करो_cmdtest = dt2814_ai_cmdtest;
		s->cancel = dt2814_ai_cancel;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dt2814_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->irq) अणु
		/*
		 * An extra conversion triggered on termination of an
		 * asynchronous command may still be in progress.  Wait क्रम
		 * it to finish and clear the data or error status.
		 */
		dt2814_ai_clear(dev);
	पूर्ण
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver dt2814_driver = अणु
	.driver_name	= "dt2814",
	.module		= THIS_MODULE,
	.attach		= dt2814_attach,
	.detach		= dt2814_detach,
पूर्ण;
module_comedi_driver(dt2814_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
