<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम CIO-DAS16/M1
 * Author: Frank Mori Hess, based on code from the das16 driver.
 * Copyright (C) 2001 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: das16m1
 * Description: CIO-DAS16/M1
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Devices: [Measurement Computing] CIO-DAS16/M1 (das16m1)
 * Status: works
 *
 * This driver supports a single board - the CIO-DAS16/M1. As far as I know,
 * there are no other boards that have the same रेजिस्टर layout. Even the
 * CIO-DAS16/M1/16 is signअगरicantly dअगरferent.
 *
 * I was _barely_ able to reach the full 1 MHz capability of this board, using
 * a hard real-समय पूर्णांकerrupt (set the TRIG_RT flag in your काष्ठा comedi_cmd
 * and use rtlinux or RTAI). The board can't करो dma, so the bottleneck is
 * pulling the data across the ISA bus. I समयd the पूर्णांकerrupt handler, and it
 * took my computer ~470 microseconds to pull 512 samples from the board. So
 * at 1 Mhz sampling rate, expect your CPU to be spending almost all of its
 * समय in the पूर्णांकerrupt handler.
 *
 * This board has some unusual restrictions क्रम its channel/gain list.  If the
 * list has 2 or more channels in it, then two conditions must be satisfied:
 * (1) - even/odd channels must appear at even/odd indices in the list
 * (2) - the list must have an even number of entries.
 *
 * Configuration options:
 *   [0] - base io address
 *   [1] - irq (optional, but you probably want it)
 *
 * irq can be omitted, although the cmd पूर्णांकerface will not work without it.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "../comedidev.h"

#समावेश "8255.h"
#समावेश "comedi_8254.h"

/*
 * Register map (dev->iobase)
 */
#घोषणा DAS16M1_AI_REG			0x00	/* 16-bit रेजिस्टर */
#घोषणा DAS16M1_AI_TO_CHAN(x)		(((x) >> 0) & 0xf)
#घोषणा DAS16M1_AI_TO_SAMPLE(x)		(((x) >> 4) & 0xfff)
#घोषणा DAS16M1_CS_REG			0x02
#घोषणा DAS16M1_CS_EXT_TRIG		BIT(0)
#घोषणा DAS16M1_CS_OVRUN		BIT(5)
#घोषणा DAS16M1_CS_IRQDATA		BIT(7)
#घोषणा DAS16M1_DI_REG			0x03
#घोषणा DAS16M1_DO_REG			0x03
#घोषणा DAS16M1_CLR_INTR_REG		0x04
#घोषणा DAS16M1_INTR_CTRL_REG		0x05
#घोषणा DAS16M1_INTR_CTRL_PACER(x)	(((x) & 0x3) << 0)
#घोषणा DAS16M1_INTR_CTRL_PACER_EXT	DAS16M1_INTR_CTRL_PACER(2)
#घोषणा DAS16M1_INTR_CTRL_PACER_INT	DAS16M1_INTR_CTRL_PACER(3)
#घोषणा DAS16M1_INTR_CTRL_PACER_MASK	DAS16M1_INTR_CTRL_PACER(3)
#घोषणा DAS16M1_INTR_CTRL_IRQ(x)	(((x) & 0x7) << 4)
#घोषणा DAS16M1_INTR_CTRL_INTE		BIT(7)
#घोषणा DAS16M1_Q_ADDR_REG		0x06
#घोषणा DAS16M1_Q_REG			0x07
#घोषणा DAS16M1_Q_CHAN(x)              (((x) & 0x7) << 0)
#घोषणा DAS16M1_Q_RANGE(x)             (((x) & 0xf) << 4)
#घोषणा DAS16M1_8254_IOBASE1		0x08
#घोषणा DAS16M1_8254_IOBASE2		0x0c
#घोषणा DAS16M1_8255_IOBASE		0x400
#घोषणा DAS16M1_8254_IOBASE3		0x404

#घोषणा DAS16M1_SIZE2			0x08

#घोषणा DAS16M1_AI_FIFO_SZ		1024	/* # samples */

अटल स्थिर काष्ठा comedi_lrange range_das16m1 = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

काष्ठा das16m1_निजी अणु
	काष्ठा comedi_8254 *counter;
	अचिन्हित पूर्णांक पूर्णांकr_ctrl;
	अचिन्हित पूर्णांक adc_count;
	u16 initial_hw_count;
	अचिन्हित लघु ai_buffer[DAS16M1_AI_FIFO_SZ];
	अचिन्हित दीर्घ extra_iobase;
पूर्ण;

अटल व्योम das16m1_ai_set_queue(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक *chanspec, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(chanspec[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(chanspec[i]);

		outb(i, dev->iobase + DAS16M1_Q_ADDR_REG);
		outb(DAS16M1_Q_CHAN(chan) | DAS16M1_Q_RANGE(range),
		     dev->iobase + DAS16M1_Q_REG);
	पूर्ण
पूर्ण

अटल व्योम das16m1_ai_munge(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     व्योम *data, अचिन्हित पूर्णांक num_bytes,
			     अचिन्हित पूर्णांक start_chan_index)
अणु
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित पूर्णांक i;

	/*
	 * The fअगरo values have the channel number in the lower 4-bits and
	 * the sample in the upper 12-bits. This just shअगरts the values
	 * to हटाओ the channel numbers.
	 */
	क्रम (i = 0; i < nsamples; i++)
		array[i] = DAS16M1_AI_TO_SAMPLE(array[i]);
पूर्ण

अटल पूर्णांक das16m1_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक i;

	अगर (cmd->chanlist_len == 1)
		वापस 0;

	अगर ((cmd->chanlist_len % 2) != 0) अणु
		dev_dbg(dev->class_dev,
			"chanlist must be of even length or length 1\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर ((i % 2) != (chan % 2)) अणु
			dev_dbg(dev->class_dev,
				"even/odd channels must go have even/odd chanlist indices\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक das16m1_ai_cmdtest(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_FOLLOW)	/* पूर्णांकernal trigger */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 1000);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक arg = cmd->convert_arg;

		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= das16m1_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक das16m1_ai_cmd(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das16m1_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक byte;

	/*  set software count */
	devpriv->adc_count = 0;

	/*
	 * Initialize lower half of hardware counter, used to determine how
	 * many samples are in fअगरo.  Value करोesn't actually load पूर्णांकo counter
	 * until counter's next घड़ी (the next a/d conversion).
	 */
	comedi_8254_set_mode(devpriv->counter, 1, I8254_MODE2 | I8254_BINARY);
	comedi_8254_ग_लिखो(devpriv->counter, 1, 0);

	/*
	 * Remember current पढ़ोing of counter so we know when counter has
	 * actually been loaded.
	 */
	devpriv->initial_hw_count = comedi_8254_पढ़ो(devpriv->counter, 1);

	das16m1_ai_set_queue(dev, cmd->chanlist, cmd->chanlist_len);

	/* enable पूर्णांकerrupts and set पूर्णांकernal pacer counter mode and counts */
	devpriv->पूर्णांकr_ctrl &= ~DAS16M1_INTR_CTRL_PACER_MASK;
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		devpriv->पूर्णांकr_ctrl |= DAS16M1_INTR_CTRL_PACER_INT;
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		devpriv->पूर्णांकr_ctrl |= DAS16M1_INTR_CTRL_PACER_EXT;
	पूर्ण

	/*  set control & status रेजिस्टर */
	byte = 0;
	/*
	 * If we are using बाह्यal start trigger (also board dislikes having
	 * both start and conversion triggers बाह्यal simultaneously).
	 */
	अगर (cmd->start_src == TRIG_EXT && cmd->convert_src != TRIG_EXT)
		byte |= DAS16M1_CS_EXT_TRIG;

	outb(byte, dev->iobase + DAS16M1_CS_REG);

	/* clear पूर्णांकerrupt */
	outb(0, dev->iobase + DAS16M1_CLR_INTR_REG);

	devpriv->पूर्णांकr_ctrl |= DAS16M1_INTR_CTRL_INTE;
	outb(devpriv->पूर्णांकr_ctrl, dev->iobase + DAS16M1_INTR_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक das16m1_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das16m1_निजी *devpriv = dev->निजी;

	/* disable पूर्णांकerrupts and pacer */
	devpriv->पूर्णांकr_ctrl &= ~(DAS16M1_INTR_CTRL_INTE |
				DAS16M1_INTR_CTRL_PACER_MASK);
	outb(devpriv->पूर्णांकr_ctrl, dev->iobase + DAS16M1_INTR_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक das16m1_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAS16M1_CS_REG);
	अगर (status & DAS16M1_CS_IRQDATA)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das16m1_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	das16m1_ai_set_queue(dev, &insn->chanspec, 1);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित लघु val;

		/* clear पूर्णांकerrupt */
		outb(0, dev->iobase + DAS16M1_CLR_INTR_REG);
		/* trigger conversion */
		outb(0, dev->iobase + DAS16M1_AI_REG);

		ret = comedi_समयout(dev, s, insn, das16m1_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inw(dev->iobase + DAS16M1_AI_REG);
		data[i] = DAS16M1_AI_TO_SAMPLE(val);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16m1_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + DAS16M1_DI_REG) & 0xf;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16m1_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS16M1_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम das16m1_handler(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक status)
अणु
	काष्ठा das16m1_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u16 num_samples;
	u16 hw_counter;

	/* figure out how many samples are in fअगरo */
	hw_counter = comedi_8254_पढ़ो(devpriv->counter, 1);
	/*
	 * Make sure hardware counter पढ़ोing is not bogus due to initial
	 * value not having been loaded yet.
	 */
	अगर (devpriv->adc_count == 0 &&
	    hw_counter == devpriv->initial_hw_count) अणु
		num_samples = 0;
	पूर्ण अन्यथा अणु
		/*
		 * The calculation of num_samples looks odd, but it uses the
		 * following facts. 16 bit hardware counter is initialized with
		 * value of zero (which really means 0x1000).  The counter
		 * decrements by one on each conversion (when the counter
		 * decrements from zero it goes to 0xffff).  num_samples is a
		 * 16 bit variable, so it will roll over in a similar fashion
		 * to the hardware counter.  Work it out, and this is what you
		 * get.
		 */
		num_samples = -hw_counter - devpriv->adc_count;
	पूर्ण
	/*  check अगर we only need some of the poपूर्णांकs */
	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अगर (num_samples > cmd->stop_arg * cmd->chanlist_len)
			num_samples = cmd->stop_arg * cmd->chanlist_len;
	पूर्ण
	/*  make sure we करोn't try to get too many poपूर्णांकs अगर fअगरo has overrun */
	अगर (num_samples > DAS16M1_AI_FIFO_SZ)
		num_samples = DAS16M1_AI_FIFO_SZ;
	insw(dev->iobase, devpriv->ai_buffer, num_samples);
	comedi_buf_ग_लिखो_samples(s, devpriv->ai_buffer, num_samples);
	devpriv->adc_count += num_samples;

	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अगर (devpriv->adc_count >= cmd->stop_arg * cmd->chanlist_len) अणु
			/* end of acquisition */
			async->events |= COMEDI_CB_EOA;
		पूर्ण
	पूर्ण

	/*
	 * This probably won't catch overruns since the card doesn't generate
	 * overrun पूर्णांकerrupts, but we might as well try.
	 */
	अगर (status & DAS16M1_CS_OVRUN) अणु
		async->events |= COMEDI_CB_ERROR;
		dev_err(dev->class_dev, "fifo overflow\n");
	पूर्ण

	comedi_handle_events(dev, s);
पूर्ण

अटल पूर्णांक das16m1_ai_poll(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	/*  prevent race with पूर्णांकerrupt handler */
	spin_lock_irqsave(&dev->spinlock, flags);
	status = inb(dev->iobase + DAS16M1_CS_REG);
	das16m1_handler(dev, status);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस comedi_buf_n_bytes_पढ़ोy(s);
पूर्ण

अटल irqवापस_t das16m1_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	पूर्णांक status;
	काष्ठा comedi_device *dev = d;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "premature interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण
	/*  prevent race with comedi_poll() */
	spin_lock(&dev->spinlock);

	status = inb(dev->iobase + DAS16M1_CS_REG);

	अगर ((status & (DAS16M1_CS_IRQDATA | DAS16M1_CS_OVRUN)) == 0) अणु
		dev_err(dev->class_dev, "spurious interrupt\n");
		spin_unlock(&dev->spinlock);
		वापस IRQ_NONE;
	पूर्ण

	das16m1_handler(dev, status);

	/* clear पूर्णांकerrupt */
	outb(0, dev->iobase + DAS16M1_CLR_INTR_REG);

	spin_unlock(&dev->spinlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक das16m1_irq_bits(अचिन्हित पूर्णांक irq)
अणु
	चयन (irq) अणु
	हाल 10:
		वापस 0x0;
	हाल 11:
		वापस 0x1;
	हाल 12:
		वापस 0x2;
	हाल 15:
		वापस 0x3;
	हाल 2:
		वापस 0x4;
	हाल 3:
		वापस 0x5;
	हाल 5:
		वापस 0x6;
	हाल 7:
		वापस 0x7;
	शेष:
		वापस 0x0;
	पूर्ण
पूर्ण

अटल पूर्णांक das16m1_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा das16m1_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;
	/* Request an additional region क्रम the 8255 and 3rd 8254 */
	ret = __comedi_request_region(dev, dev->iobase + DAS16M1_8255_IOBASE,
				      DAS16M1_SIZE2);
	अगर (ret)
		वापस ret;
	devpriv->extra_iobase = dev->iobase + DAS16M1_8255_IOBASE;

	/* only irqs 2, 3, 4, 5, 6, 7, 10, 11, 12, 14, and 15 are valid */
	अगर ((1 << it->options[1]) & 0xdcfc) अणु
		ret = request_irq(it->options[1], das16m1_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + DAS16M1_8254_IOBASE2,
				      I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	devpriv->counter = comedi_8254_init(dev->iobase + DAS16M1_8254_IOBASE1,
					    0, I8254_IO8, 0);
	अगर (!devpriv->counter)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_DIFF;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->range_table	= &range_das16m1;
	s->insn_पढ़ो	= das16m1_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 256;
		s->करो_cmdtest	= das16m1_ai_cmdtest;
		s->करो_cmd	= das16m1_ai_cmd;
		s->cancel	= das16m1_ai_cancel;
		s->poll		= das16m1_ai_poll;
		s->munge	= das16m1_ai_munge;
	पूर्ण

	/* Digital Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das16m1_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das16m1_करो_insn_bits;

	/* Digital I/O subdevice (8255) */
	s = &dev->subdevices[3];
	ret = subdev_8255_init(dev, s, शून्य, DAS16M1_8255_IOBASE);
	अगर (ret)
		वापस ret;

	/*  initialize digital output lines */
	outb(0, dev->iobase + DAS16M1_DO_REG);

	/* set the पूर्णांकerrupt level */
	devpriv->पूर्णांकr_ctrl = DAS16M1_INTR_CTRL_IRQ(das16m1_irq_bits(dev->irq));
	outb(devpriv->पूर्णांकr_ctrl, dev->iobase + DAS16M1_INTR_CTRL_REG);

	वापस 0;
पूर्ण

अटल व्योम das16m1_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा das16m1_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		अगर (devpriv->extra_iobase)
			release_region(devpriv->extra_iobase, DAS16M1_SIZE2);
		kमुक्त(devpriv->counter);
	पूर्ण
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver das16m1_driver = अणु
	.driver_name	= "das16m1",
	.module		= THIS_MODULE,
	.attach		= das16m1_attach,
	.detach		= das16m1_detach,
पूर्ण;
module_comedi_driver(das16m1_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for CIO-DAS16/M1 ISA cards");
MODULE_LICENSE("GPL");
