<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pcl816.c
 * Comedi driver क्रम Advantech PCL-816 cards
 *
 * Author:  Juan Grigera <juan@grigera.com.ar>
 * based on pcl818 by Michal Dobes <करोbes@tesnet.cz> and bits of pcl812
 */

/*
 * Driver: pcl816
 * Description: Advantech PCL-816 cards, PCL-814
 * Devices: [Advantech] PCL-816 (pcl816), PCL-814B (pcl814b)
 * Author: Juan Grigera <juan@grigera.com.ar>
 * Status: works
 * Updated: Tue,  2 Apr 2002 23:15:21 -0800
 *
 * PCL 816 and 814B have 16 SE/DIFF ADCs, 16 DACs, 16 DI and 16 DO.
 * Dअगरferences are at resolution (16 vs 12 bits).
 *
 * The driver support AI command mode, other subdevices not written.
 *
 * Analog output and digital input and output are not supported.
 *
 * Configuration Options:
 *   [0] - IO Base
 *   [1] - IRQ	(0=disable, 2, 3, 4, 5, 6, 7)
 *   [2] - DMA	(0=disable, 1, 3)
 *   [3] - 0, 10=10MHz घड़ी क्रम 8254
 *	       1= 1MHz घड़ी क्रम 8254
 */

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "comedi_8254.h"

/*
 * Register I/O map
 */
#घोषणा PCL816_DO_DI_LSB_REG			0x00
#घोषणा PCL816_DO_DI_MSB_REG			0x01
#घोषणा PCL816_TIMER_BASE			0x04
#घोषणा PCL816_AI_LSB_REG			0x08
#घोषणा PCL816_AI_MSB_REG			0x09
#घोषणा PCL816_RANGE_REG			0x09
#घोषणा PCL816_CLRINT_REG			0x0a
#घोषणा PCL816_MUX_REG				0x0b
#घोषणा PCL816_MUX_SCAN(_first, _last)		(((_last) << 4) | (_first))
#घोषणा PCL816_CTRL_REG				0x0c
#घोषणा PCL816_CTRL_SOFT_TRIG			BIT(0)
#घोषणा PCL816_CTRL_PACER_TRIG			BIT(1)
#घोषणा PCL816_CTRL_EXT_TRIG			BIT(2)
#घोषणा PCL816_CTRL_POE				BIT(3)
#घोषणा PCL816_CTRL_DMAEN			BIT(4)
#घोषणा PCL816_CTRL_INTEN			BIT(5)
#घोषणा PCL816_CTRL_DMASRC_SLOT(x)		(((x) & 0x3) << 6)
#घोषणा PCL816_STATUS_REG			0x0d
#घोषणा PCL816_STATUS_NEXT_CHAN_MASK		(0xf << 0)
#घोषणा PCL816_STATUS_INTSRC_SLOT(x)		(((x) & 0x3) << 4)
#घोषणा PCL816_STATUS_INTSRC_DMA		PCL816_STATUS_INTSRC_SLOT(3)
#घोषणा PCL816_STATUS_INTSRC_MASK		PCL816_STATUS_INTSRC_SLOT(3)
#घोषणा PCL816_STATUS_INTACT			BIT(6)
#घोषणा PCL816_STATUS_DRDY			BIT(7)

#घोषणा MAGIC_DMA_WORD 0x5a5a

अटल स्थिर काष्ठा comedi_lrange range_pcl816 = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

काष्ठा pcl816_board अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_maxdata;
	पूर्णांक ai_chanlist;
पूर्ण;

अटल स्थिर काष्ठा pcl816_board boardtypes[] = अणु
	अणु
		.name		= "pcl816",
		.ai_maxdata	= 0xffff,
		.ai_chanlist	= 1024,
	पूर्ण, अणु
		.name		= "pcl814b",
		.ai_maxdata	= 0x3fff,
		.ai_chanlist	= 1024,
	पूर्ण,
पूर्ण;

काष्ठा pcl816_निजी अणु
	काष्ठा comedi_isadma *dma;
	अचिन्हित पूर्णांक ai_poll_ptr;	/*  how many sampes transfer poll */
	अचिन्हित पूर्णांक ai_cmd_running:1;
	अचिन्हित पूर्णांक ai_cmd_canceled:1;
पूर्ण;

अटल व्योम pcl816_ai_setup_dma(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक unपढ़ो_samples)
अणु
	काष्ठा pcl816_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक max_samples = comedi_bytes_to_samples(s, desc->maxsize);
	अचिन्हित पूर्णांक nsamples;

	comedi_isadma_disable(dma->chan);

	/*
	 * Determine dma size based on the buffer maxsize plus the number of
	 * unपढ़ो samples and the number of samples reमुख्यing in the command.
	 */
	nsamples = comedi_nsamples_left(s, max_samples + unपढ़ो_samples);
	अगर (nsamples > unपढ़ो_samples) अणु
		nsamples -= unपढ़ो_samples;
		desc->size = comedi_samples_to_bytes(s, nsamples);
		comedi_isadma_program(desc);
	पूर्ण
पूर्ण

अटल व्योम pcl816_ai_set_chan_range(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक chan,
				     अचिन्हित पूर्णांक range)
अणु
	outb(chan, dev->iobase + PCL816_MUX_REG);
	outb(range, dev->iobase + PCL816_RANGE_REG);
पूर्ण

अटल व्योम pcl816_ai_set_chan_scan(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक first_chan,
				    अचिन्हित पूर्णांक last_chan)
अणु
	outb(PCL816_MUX_SCAN(first_chan, last_chan),
	     dev->iobase + PCL816_MUX_REG);
पूर्ण

अटल व्योम pcl816_ai_setup_chanlist(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक *chanlist,
				     अचिन्हित पूर्णांक seglen)
अणु
	अचिन्हित पूर्णांक first_chan = CR_CHAN(chanlist[0]);
	अचिन्हित पूर्णांक last_chan;
	अचिन्हित पूर्णांक range;
	अचिन्हित पूर्णांक i;

	/* store range list to card */
	क्रम (i = 0; i < seglen; i++) अणु
		last_chan = CR_CHAN(chanlist[i]);
		range = CR_RANGE(chanlist[i]);

		pcl816_ai_set_chan_range(dev, last_chan, range);
	पूर्ण

	udelay(1);

	pcl816_ai_set_chan_scan(dev, first_chan, last_chan);
पूर्ण

अटल व्योम pcl816_ai_clear_eoc(काष्ठा comedi_device *dev)
अणु
	/* writing any value clears the पूर्णांकerrupt request */
	outb(0, dev->iobase + PCL816_CLRINT_REG);
पूर्ण

अटल व्योम pcl816_ai_soft_trig(काष्ठा comedi_device *dev)
अणु
	/* writing any value triggers a software conversion */
	outb(0, dev->iobase + PCL816_AI_LSB_REG);
पूर्ण

अटल अचिन्हित पूर्णांक pcl816_ai_get_sample(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + PCL816_AI_MSB_REG) << 8;
	val |= inb(dev->iobase + PCL816_AI_LSB_REG);

	वापस val & s->maxdata;
पूर्ण

अटल पूर्णांक pcl816_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + PCL816_STATUS_REG);
	अगर ((status & PCL816_STATUS_DRDY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल bool pcl816_ai_next_chan(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg) अणु
		s->async->events |= COMEDI_CB_EOA;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम transfer_from_dma_buf(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित लघु *ptr,
				  अचिन्हित पूर्णांक bufptr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित लघु val;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		val = ptr[bufptr++];
		comedi_buf_ग_लिखो_samples(s, &val, 1);

		अगर (!pcl816_ai_next_chan(dev, s))
			वापस;
	पूर्ण
पूर्ण

अटल irqवापस_t pcl816_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा pcl816_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक bufptr;

	अगर (!dev->attached || !devpriv->ai_cmd_running) अणु
		pcl816_ai_clear_eoc(dev);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (devpriv->ai_cmd_canceled) अणु
		devpriv->ai_cmd_canceled = 0;
		pcl816_ai_clear_eoc(dev);
		वापस IRQ_HANDLED;
	पूर्ण

	nsamples = comedi_bytes_to_samples(s, desc->size) -
		   devpriv->ai_poll_ptr;
	bufptr = devpriv->ai_poll_ptr;
	devpriv->ai_poll_ptr = 0;

	/* restart dma with the next buffer */
	dma->cur_dma = 1 - dma->cur_dma;
	pcl816_ai_setup_dma(dev, s, nsamples);

	transfer_from_dma_buf(dev, s, desc->virt_addr, bufptr, nsamples);

	pcl816_ai_clear_eoc(dev);

	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक check_channel_list(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      अचिन्हित पूर्णांक *chanlist,
			      अचिन्हित पूर्णांक chanlen)
अणु
	अचिन्हित पूर्णांक chansegment[16];
	अचिन्हित पूर्णांक i, nowmustbechan, seglen;

	/*  correct channel and range number check itself comedi/range.c */
	अगर (chanlen < 1) अणु
		dev_err(dev->class_dev, "range/channel list is empty!\n");
		वापस 0;
	पूर्ण

	अगर (chanlen > 1) अणु
		/*  first channel is every समय ok */
		chansegment[0] = chanlist[0];
		क्रम (i = 1, seglen = 1; i < chanlen; i++, seglen++) अणु
			/*  we detect loop, this must by finish */
			अगर (chanlist[0] == chanlist[i])
				अवरोध;
			nowmustbechan =
			    (CR_CHAN(chansegment[i - 1]) + 1) % chanlen;
			अगर (nowmustbechan != CR_CHAN(chanlist[i])) अणु
				/*  channel list isn't continuous :-( */
				dev_dbg(dev->class_dev,
					"channel list must be continuous! chanlist[%i]=%d but must be %d or %d!\n",
					i, CR_CHAN(chanlist[i]), nowmustbechan,
					CR_CHAN(chanlist[0]));
				वापस 0;
			पूर्ण
			/*  well, this is next correct channel in list */
			chansegment[i] = chanlist[i];
		पूर्ण

		/*  check whole chanlist */
		क्रम (i = 0; i < chanlen; i++) अणु
			अगर (chanlist[i] != chansegment[i % seglen]) अणु
				dev_dbg(dev->class_dev,
					"bad channel or range number! chanlist[%i]=%d,%d,%d and not %d,%d,%d!\n",
					i, CR_CHAN(chansegment[i]),
					CR_RANGE(chansegment[i]),
					CR_AREF(chansegment[i]),
					CR_CHAN(chanlist[i % seglen]),
					CR_RANGE(chanlist[i % seglen]),
					CR_AREF(chansegment[i % seglen]));
				वापस 0;	/*  chan/gain list is strange */
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		seglen = 1;
	पूर्ण

	वापस seglen;	/*  we can serve this with MUX logic */
पूर्ण

अटल पूर्णांक pcl816_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_EXT | TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 10000);
	अन्यथा	/* TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक arg = cmd->convert_arg;

		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* step 5: complain about special chanlist considerations */

	अगर (cmd->chanlist) अणु
		अगर (!check_channel_list(dev, s, cmd->chanlist,
					cmd->chanlist_len))
			वापस 5;	/*  incorrect channels list */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcl816_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl816_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक seglen;

	अगर (devpriv->ai_cmd_running)
		वापस -EBUSY;

	seglen = check_channel_list(dev, s, cmd->chanlist, cmd->chanlist_len);
	अगर (seglen < 1)
		वापस -EINVAL;
	pcl816_ai_setup_chanlist(dev, cmd->chanlist, seglen);
	udelay(1);

	devpriv->ai_cmd_running = 1;
	devpriv->ai_poll_ptr = 0;
	devpriv->ai_cmd_canceled = 0;

	/* setup and enable dma क्रम the first buffer */
	dma->cur_dma = 0;
	pcl816_ai_setup_dma(dev, s, 0);

	comedi_8254_set_mode(dev->pacer, 0, I8254_MODE1 | I8254_BINARY);
	comedi_8254_ग_लिखो(dev->pacer, 0, 0x0ff);
	udelay(1);
	comedi_8254_update_भागisors(dev->pacer);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, true);

	ctrl = PCL816_CTRL_INTEN | PCL816_CTRL_DMAEN |
	       PCL816_CTRL_DMASRC_SLOT(0);
	अगर (cmd->convert_src == TRIG_TIMER)
		ctrl |= PCL816_CTRL_PACER_TRIG;
	अन्यथा	/* TRIG_EXT */
		ctrl |= PCL816_CTRL_EXT_TRIG;

	outb(ctrl, dev->iobase + PCL816_CTRL_REG);
	outb((dma->chan << 4) | dev->irq,
	     dev->iobase + PCL816_STATUS_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक pcl816_ai_poll(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl816_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक poll;
	पूर्णांक ret;

	spin_lock_irqsave(&dev->spinlock, flags);

	poll = comedi_isadma_poll(dma);
	poll = comedi_bytes_to_samples(s, poll);
	अगर (poll > devpriv->ai_poll_ptr) अणु
		desc = &dma->desc[dma->cur_dma];
		transfer_from_dma_buf(dev, s, desc->virt_addr,
				      devpriv->ai_poll_ptr,
				      poll - devpriv->ai_poll_ptr);
		/* new buffer position */
		devpriv->ai_poll_ptr = poll;

		comedi_handle_events(dev, s);

		ret = comedi_buf_n_bytes_पढ़ोy(s);
	पूर्ण अन्यथा अणु
		/* no new samples */
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक pcl816_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl816_निजी *devpriv = dev->निजी;

	अगर (!devpriv->ai_cmd_running)
		वापस 0;

	outb(0, dev->iobase + PCL816_CTRL_REG);
	pcl816_ai_clear_eoc(dev);

	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);

	devpriv->ai_cmd_running = 0;
	devpriv->ai_cmd_canceled = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pcl816_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक ret = 0;
	पूर्णांक i;

	outb(PCL816_CTRL_SOFT_TRIG, dev->iobase + PCL816_CTRL_REG);

	pcl816_ai_set_chan_range(dev, chan, range);
	pcl816_ai_set_chan_scan(dev, chan, chan);

	क्रम (i = 0; i < insn->n; i++) अणु
		pcl816_ai_clear_eoc(dev);
		pcl816_ai_soft_trig(dev);

		ret = comedi_समयout(dev, s, insn, pcl816_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		data[i] = pcl816_ai_get_sample(dev, s);
	पूर्ण
	outb(0, dev->iobase + PCL816_CTRL_REG);
	pcl816_ai_clear_eoc(dev);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक pcl816_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + PCL816_DO_DI_LSB_REG) |
		  (inb(dev->iobase + PCL816_DO_DI_MSB_REG) << 8);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl816_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, dev->iobase + PCL816_DO_DI_LSB_REG);
		outb((s->state >> 8), dev->iobase + PCL816_DO_DI_MSB_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम pcl816_reset(काष्ठा comedi_device *dev)
अणु
	outb(0, dev->iobase + PCL816_CTRL_REG);
	pcl816_ai_set_chan_range(dev, 0, 0);
	pcl816_ai_clear_eoc(dev);

	/* set all digital outमाला_दो low */
	outb(0, dev->iobase + PCL816_DO_DI_LSB_REG);
	outb(0, dev->iobase + PCL816_DO_DI_MSB_REG);
पूर्ण

अटल व्योम pcl816_alloc_irq_and_dma(काष्ठा comedi_device *dev,
				     काष्ठा comedi_devconfig *it)
अणु
	काष्ठा pcl816_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक irq_num = it->options[1];
	अचिन्हित पूर्णांक dma_chan = it->options[2];

	/* only IRQs 2-7 and DMA channels 3 and 1 are valid */
	अगर (!(irq_num >= 2 && irq_num <= 7) ||
	    !(dma_chan == 3 || dma_chan == 1))
		वापस;

	अगर (request_irq(irq_num, pcl816_पूर्णांकerrupt, 0, dev->board_name, dev))
		वापस;

	/* DMA uses two 16K buffers */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 4, COMEDI_ISADMA_READ);
	अगर (!devpriv->dma)
		मुक्त_irq(irq_num, dev);
	अन्यथा
		dev->irq = irq_num;
पूर्ण

अटल व्योम pcl816_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcl816_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण

अटल पूर्णांक pcl816_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl816_board *board = dev->board_ptr;
	काष्ठा pcl816_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	/* an IRQ and DMA are required to support async commands */
	pcl816_alloc_irq_and_dma(dev, it);

	dev->pacer = comedi_8254_init(dev->iobase + PCL816_TIMER_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_CMD_READ | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= board->ai_maxdata;
	s->range_table	= &range_pcl816;
	s->insn_पढ़ो	= pcl816_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= board->ai_chanlist;
		s->करो_cmdtest	= pcl816_ai_cmdtest;
		s->करो_cmd	= pcl816_ai_cmd;
		s->poll		= pcl816_ai_poll;
		s->cancel	= pcl816_ai_cancel;
	पूर्ण

	/* Piggyback Slot1 subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_UNUSED;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl816_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl816_करो_insn_bits;

	pcl816_reset(dev);

	वापस 0;
पूर्ण

अटल व्योम pcl816_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->निजी) अणु
		pcl816_ai_cancel(dev, dev->पढ़ो_subdev);
		pcl816_reset(dev);
	पूर्ण
	pcl816_मुक्त_dma(dev);
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver pcl816_driver = अणु
	.driver_name	= "pcl816",
	.module		= THIS_MODULE,
	.attach		= pcl816_attach,
	.detach		= pcl816_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= माप(काष्ठा pcl816_board),
पूर्ण;
module_comedi_driver(pcl816_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
