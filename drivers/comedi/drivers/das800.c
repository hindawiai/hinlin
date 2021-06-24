<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/das800.c
 * Driver क्रम Keitley das800 series boards and compatibles
 * Copyright (C) 2000 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: das800
 * Description: Keithley Metrabyte DAS800 (& compatibles)
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Devices: [Keithley Metrabyte] DAS-800 (das-800), DAS-801 (das-801),
 * DAS-802 (das-802),
 * [Measurement Computing] CIO-DAS800 (cio-das800),
 * CIO-DAS801 (cio-das801), CIO-DAS802 (cio-das802),
 * CIO-DAS802/16 (cio-das802/16)
 * Status: works, cio-das802/16 untested - email me अगर you have tested it
 *
 * Configuration options:
 * [0] - I/O port base address
 * [1] - IRQ (optional, required क्रम समयd or बाह्यally triggered conversions)
 *
 * Notes:
 *	IRQ can be omitted, although the cmd पूर्णांकerface will not work without it.
 *
 *	All entries in the channel/gain list must use the same gain and be
 *	consecutive channels counting upwards in channel number (these are
 *	hardware limitations.)
 *
 *	I've never tested the gain setting stuff since I only have a
 *	DAS-800 board with fixed gain.
 *
 *	The cio-das802/16 करोes not have a fअगरo-empty status bit!  Thereक्रमe
 *	only fअगरo-half-full transfers are possible with this card.
 *
 * cmd triggers supported:
 *	start_src:      TRIG_NOW | TRIG_EXT
 *	scan_begin_src: TRIG_FOLLOW
 *	scan_end_src:   TRIG_COUNT
 *	convert_src:    TRIG_TIMER | TRIG_EXT
 *	stop_src:       TRIG_NONE | TRIG_COUNT
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"

#घोषणा N_CHAN_AI             8	/*  number of analog input channels */

/* Registers क्रम the das800 */

#घोषणा DAS800_LSB            0
#घोषणा   FIFO_EMPTY            0x1
#घोषणा   FIFO_OVF              0x2
#घोषणा DAS800_MSB            1
#घोषणा DAS800_CONTROL1       2
#घोषणा   CONTROL1_INTE         0x8
#घोषणा DAS800_CONV_CONTROL   2
#घोषणा   ITE                   0x1
#घोषणा   CASC                  0x2
#घोषणा   DTEN                  0x4
#घोषणा   IEOC                  0x8
#घोषणा   EACS                  0x10
#घोषणा   CONV_HCEN             0x80
#घोषणा DAS800_SCAN_LIMITS    2
#घोषणा DAS800_STATUS         2
#घोषणा   IRQ                   0x8
#घोषणा   BUSY                  0x80
#घोषणा DAS800_GAIN           3
#घोषणा   CIO_FFOV              0x8   /* cio-das802/16 fअगरo overflow */
#घोषणा   CIO_ENHF              0x90  /* cio-das802/16 fअगरo half full पूर्णांक ena */
#घोषणा   CONTROL1              0x80
#घोषणा   CONV_CONTROL          0xa0
#घोषणा   SCAN_LIMITS           0xc0
#घोषणा   ID                    0xe0
#घोषणा DAS800_8254           4
#घोषणा DAS800_STATUS2        7
#घोषणा   STATUS2_HCEN          0x80
#घोषणा   STATUS2_INTE          0X20
#घोषणा DAS800_ID             7

#घोषणा DAS802_16_HALF_FIFO_SZ	128

काष्ठा das800_board अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_speed;
	स्थिर काष्ठा comedi_lrange *ai_range;
	पूर्णांक resolution;
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das801_ai = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(10),
		BIP_RANGE(0.5),
		UNI_RANGE(1),
		BIP_RANGE(0.05),
		UNI_RANGE(0.1),
		BIP_RANGE(0.01),
		UNI_RANGE(0.02)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_cio_das801_ai = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(10),
		BIP_RANGE(0.5),
		UNI_RANGE(1),
		BIP_RANGE(0.05),
		UNI_RANGE(0.1),
		BIP_RANGE(0.005),
		UNI_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das802_ai = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(10),
		BIP_RANGE(2.5),
		UNI_RANGE(5),
		BIP_RANGE(1.25),
		UNI_RANGE(2.5),
		BIP_RANGE(0.625),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das80216_ai = अणु
	8, अणु
		BIP_RANGE(10),
		UNI_RANGE(10),
		BIP_RANGE(5),
		UNI_RANGE(5),
		BIP_RANGE(2.5),
		UNI_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

क्रमागत das800_boardinfo अणु
	BOARD_DAS800,
	BOARD_CIODAS800,
	BOARD_DAS801,
	BOARD_CIODAS801,
	BOARD_DAS802,
	BOARD_CIODAS802,
	BOARD_CIODAS80216,
पूर्ण;

अटल स्थिर काष्ठा das800_board das800_boards[] = अणु
	[BOARD_DAS800] = अणु
		.name		= "das-800",
		.ai_speed	= 25000,
		.ai_range	= &range_bipolar5,
		.resolution	= 12,
	पूर्ण,
	[BOARD_CIODAS800] = अणु
		.name		= "cio-das800",
		.ai_speed	= 20000,
		.ai_range	= &range_bipolar5,
		.resolution	= 12,
	पूर्ण,
	[BOARD_DAS801] = अणु
		.name		= "das-801",
		.ai_speed	= 25000,
		.ai_range	= &range_das801_ai,
		.resolution	= 12,
	पूर्ण,
	[BOARD_CIODAS801] = अणु
		.name		= "cio-das801",
		.ai_speed	= 20000,
		.ai_range	= &range_cio_das801_ai,
		.resolution	= 12,
	पूर्ण,
	[BOARD_DAS802] = अणु
		.name		= "das-802",
		.ai_speed	= 25000,
		.ai_range	= &range_das802_ai,
		.resolution	= 12,
	पूर्ण,
	[BOARD_CIODAS802] = अणु
		.name		= "cio-das802",
		.ai_speed	= 20000,
		.ai_range	= &range_das802_ai,
		.resolution	= 12,
	पूर्ण,
	[BOARD_CIODAS80216] = अणु
		.name		= "cio-das802/16",
		.ai_speed	= 10000,
		.ai_range	= &range_das80216_ai,
		.resolution	= 16,
	पूर्ण,
पूर्ण;

काष्ठा das800_निजी अणु
	अचिन्हित पूर्णांक करो_bits;	/* digital output bits */
पूर्ण;

अटल व्योम das800_ind_ग_लिखो(काष्ठा comedi_device *dev,
			     अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक reg)
अणु
	/*
	 * Select dev->iobase + 2 to be desired रेजिस्टर
	 * then ग_लिखो to that रेजिस्टर.
	 */
	outb(reg, dev->iobase + DAS800_GAIN);
	outb(val, dev->iobase + 2);
पूर्ण

अटल अचिन्हित पूर्णांक das800_ind_पढ़ो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक reg)
अणु
	/*
	 * Select dev->iobase + 7 to be desired रेजिस्टर
	 * then पढ़ो from that रेजिस्टर.
	 */
	outb(reg, dev->iobase + DAS800_GAIN);
	वापस inb(dev->iobase + 7);
पूर्ण

अटल व्योम das800_enable(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा das800_board *board = dev->board_ptr;
	काष्ठा das800_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	/*  enable fअगरo-half full पूर्णांकerrupts क्रम cio-das802/16 */
	अगर (board->resolution == 16)
		outb(CIO_ENHF, dev->iobase + DAS800_GAIN);
	/* enable hardware triggering */
	das800_ind_ग_लिखो(dev, CONV_HCEN, CONV_CONTROL);
	/* enable card's पूर्णांकerrupt */
	das800_ind_ग_लिखो(dev, CONTROL1_INTE | devpriv->करो_bits, CONTROL1);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);
पूर्ण

अटल व्योम das800_disable(काष्ठा comedi_device *dev)
अणु
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	/* disable hardware triggering of conversions */
	das800_ind_ग_लिखो(dev, 0x0, CONV_CONTROL);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);
पूर्ण

अटल पूर्णांक das800_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	das800_disable(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक das800_ai_check_chanlist(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		अगर (chan != (chan0 + i) % s->n_chan) अणु
			dev_dbg(dev->class_dev,
				"chanlist must be consecutive, counting upwards\n");
			वापस -EINVAL;
		पूर्ण

		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"chanlist must all have the same gain\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक das800_ai_करो_cmdtest(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा das800_board *board = dev->board_ptr;
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

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
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

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= das800_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक das800_ai_करो_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा das800_board *board = dev->board_ptr;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक gain = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक start_chan = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक end_chan = (start_chan + cmd->chanlist_len - 1) % 8;
	अचिन्हित पूर्णांक scan_chans = (end_chan << 3) | start_chan;
	पूर्णांक conv_bits;
	अचिन्हित दीर्घ irq_flags;

	das800_disable(dev);

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	/* set scan limits */
	das800_ind_ग_लिखो(dev, scan_chans, SCAN_LIMITS);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	/* set gain */
	अगर (board->resolution == 12 && gain > 0)
		gain += 0x7;
	gain &= 0xf;
	outb(gain, dev->iobase + DAS800_GAIN);

	/* enable स्वतः channel scan, send पूर्णांकerrupts on end of conversion
	 * and set घड़ी source to पूर्णांकernal or बाह्यal
	 */
	conv_bits = 0;
	conv_bits |= EACS | IEOC;
	अगर (cmd->start_src == TRIG_EXT)
		conv_bits |= DTEN;
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		conv_bits |= CASC | ITE;
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	पूर्ण

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	das800_ind_ग_लिखो(dev, conv_bits, CONV_CONTROL);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	das800_enable(dev);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक das800_ai_get_sample(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक lsb = inb(dev->iobase + DAS800_LSB);
	अचिन्हित पूर्णांक msb = inb(dev->iobase + DAS800_MSB);

	वापस (msb << 8) | lsb;
पूर्ण

अटल irqवापस_t das800_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा das800_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async;
	काष्ठा comedi_cmd *cmd;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक status;
	अचिन्हित लघु val;
	bool fअगरo_empty;
	bool fअगरo_overflow;
	पूर्णांक i;

	status = inb(dev->iobase + DAS800_STATUS);
	अगर (!(status & IRQ))
		वापस IRQ_NONE;
	अगर (!dev->attached)
		वापस IRQ_HANDLED;

	async = s->async;
	cmd = &async->cmd;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	status = das800_ind_पढ़ो(dev, CONTROL1) & STATUS2_HCEN;
	/*
	 * Don't release spinlock yet since we want to make sure
	 * no one अन्यथा disables hardware conversions.
	 */

	/* अगर hardware conversions are not enabled, then quit */
	अगर (status == 0) अणु
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
		वापस IRQ_HANDLED;
	पूर्ण

	क्रम (i = 0; i < DAS802_16_HALF_FIFO_SZ; i++) अणु
		val = das800_ai_get_sample(dev);
		अगर (s->maxdata == 0x0fff) अणु
			fअगरo_empty = !!(val & FIFO_EMPTY);
			fअगरo_overflow = !!(val & FIFO_OVF);
		पूर्ण अन्यथा अणु
			/* cio-das802/16 has no fअगरo empty status bit */
			fअगरo_empty = false;
			fअगरo_overflow = !!(inb(dev->iobase + DAS800_GAIN) &
						CIO_FFOV);
		पूर्ण
		अगर (fअगरo_empty || fअगरo_overflow)
			अवरोध;

		अगर (s->maxdata == 0x0fff)
			val >>= 4;	/* 12-bit sample */

		val &= s->maxdata;
		comedi_buf_ग_लिखो_samples(s, &val, 1);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg) अणु
			async->events |= COMEDI_CB_EOA;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fअगरo_overflow) अणु
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!(async->events & COMEDI_CB_CANCEL_MASK)) अणु
		/*
		 * Re-enable card's पूर्णांकerrupt.
		 * We alपढ़ोy have spinlock, so indirect addressing is safe
		 */
		das800_ind_ग_लिखो(dev, CONTROL1_INTE | devpriv->करो_bits,
				 CONTROL1);
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
	पूर्ण अन्यथा अणु
		/* otherwise, stop taking data */
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
		das800_disable(dev);
	पूर्ण
	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक das800_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAS800_STATUS);
	अगर ((status & BUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das800_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das800_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	das800_disable(dev);

	/* set multiplexer */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	das800_ind_ग_लिखो(dev, chan | devpriv->करो_bits, CONTROL1);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	/* set gain / range */
	अगर (s->maxdata == 0x0fff && range)
		range += 0x7;
	range &= 0xf;
	outb(range, dev->iobase + DAS800_GAIN);

	udelay(5);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* trigger conversion */
		outb_p(0, dev->iobase + DAS800_MSB);

		ret = comedi_समयout(dev, s, insn, das800_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = das800_ai_get_sample(dev);
		अगर (s->maxdata == 0x0fff)
			val >>= 4;	/* 12-bit sample */
		data[i] = val & s->maxdata;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक das800_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = (inb(dev->iobase + DAS800_STATUS) >> 4) & 0x7;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das800_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das800_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irq_flags;

	अगर (comedi_dio_update_state(s, data)) अणु
		devpriv->करो_bits = s->state << 4;

		spin_lock_irqsave(&dev->spinlock, irq_flags);
		das800_ind_ग_लिखो(dev, CONTROL1_INTE | devpriv->करो_bits,
				 CONTROL1);
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल स्थिर काष्ठा das800_board *das800_probe(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा das800_board *board = dev->board_ptr;
	पूर्णांक index = board ? board - das800_boards : -EINVAL;
	पूर्णांक id_bits;
	अचिन्हित दीर्घ irq_flags;

	/*
	 * The dev->board_ptr will be set by comedi_device_attach() अगर the
	 * board name provided by the user matches a board->name in this
	 * driver. If so, this function sanity checks the id_bits to verअगरy
	 * that the board is correct.
	 *
	 * If the dev->board_ptr is not set, the user is trying to attach
	 * an unspecअगरied board to this driver. In this हाल the id_bits
	 * are used to 'probe' क्रम the correct dev->board_ptr.
	 */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	id_bits = das800_ind_पढ़ो(dev, ID) & 0x3;
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	चयन (id_bits) अणु
	हाल 0x0:
		अगर (index == BOARD_DAS800 || index == BOARD_CIODAS800)
			वापस board;
		index = BOARD_DAS800;
		अवरोध;
	हाल 0x2:
		अगर (index == BOARD_DAS801 || index == BOARD_CIODAS801)
			वापस board;
		index = BOARD_DAS801;
		अवरोध;
	हाल 0x3:
		अगर (index == BOARD_DAS802 || index == BOARD_CIODAS802 ||
		    index == BOARD_CIODAS80216)
			वापस board;
		index = BOARD_DAS802;
		अवरोध;
	शेष:
		dev_dbg(dev->class_dev, "Board model: 0x%x (unknown)\n",
			id_bits);
		वापस शून्य;
	पूर्ण
	dev_dbg(dev->class_dev, "Board model (probed): %s series\n",
		das800_boards[index].name);

	वापस &das800_boards[index];
पूर्ण

अटल पूर्णांक das800_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा das800_board *board;
	काष्ठा das800_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक irq = it->options[1];
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x8);
	अगर (ret)
		वापस ret;

	board = das800_probe(dev);
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	अगर (irq > 1 && irq <= 7) अणु
		ret = request_irq(irq, das800_पूर्णांकerrupt, 0, "das800",
				  dev);
		अगर (ret == 0)
			dev->irq = irq;
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + DAS800_8254,
				      I8254_OSC_BASE_1MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	dev->पढ़ो_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	s->n_chan	= 8;
	s->maxdata	= (1 << board->resolution) - 1;
	s->range_table	= board->ai_range;
	s->insn_पढ़ो	= das800_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 8;
		s->करो_cmdtest	= das800_ai_करो_cmdtest;
		s->करो_cmd	= das800_ai_करो_cmd;
		s->cancel	= das800_cancel;
	पूर्ण

	/* Digital Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 3;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das800_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das800_करो_insn_bits;

	das800_disable(dev);

	/* initialize digital out channels */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	das800_ind_ग_लिखो(dev, CONTROL1_INTE | devpriv->करो_bits, CONTROL1);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	वापस 0;
पूर्ण;

अटल काष्ठा comedi_driver driver_das800 = अणु
	.driver_name	= "das800",
	.module		= THIS_MODULE,
	.attach		= das800_attach,
	.detach		= comedi_legacy_detach,
	.num_names	= ARRAY_SIZE(das800_boards),
	.board_name	= &das800_boards[0].name,
	.offset		= माप(काष्ठा das800_board),
पूर्ण;
module_comedi_driver(driver_das800);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
