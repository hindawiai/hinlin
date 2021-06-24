<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * quatech_daqp_cs.c
 * Quatech DAQP PCMCIA data capture cards COMEDI client driver
 * Copyright (C) 2000, 2003 Brent Baccala <baccala@मुक्तsoft.org>
 * The DAQP पूर्णांकerface code in this file is released पूर्णांकo the खुला करोमुख्य.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 * https://www.comedi.org/
 *
 * Documentation क्रम the DAQP PCMCIA cards can be found on Quatech's site:
 *	ftp://ftp.quatech.com/Manuals/daqp-208.pdf
 *
 * This manual is क्रम both the DAQP-208 and the DAQP-308.
 *
 * What works:
 * - A/D conversion
 *	- 8 channels
 *	- 4 gain ranges
 *	- ground ref or dअगरferential
 *	- single-shot and समयd both supported
 * - D/A conversion, single-shot
 * - digital I/O
 *
 * What करोesn't:
 * - any kind of triggering - बाह्यal or D/A channel 1
 * - the card's optional expansion board
 * - the card's समयr (क्रम anything other than A/D conversion)
 * - D/A update modes other than immediate (i.e, समयd)
 * - fancier timing modes
 * - setting card's FIFO buffer thresholds to anything but शेष
 */

/*
 * Driver: quatech_daqp_cs
 * Description: Quatech DAQP PCMCIA data capture cards
 * Devices: [Quatech] DAQP-208 (daqp), DAQP-308
 * Author: Brent Baccala <baccala@मुक्तsoft.org>
 * Status: works
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pcmcia.h"

/*
 * Register I/O map
 *
 * The D/A and समयr रेजिस्टरs can be accessed with 16-bit or 8-bit I/O
 * inकाष्ठाions. All other रेजिस्टरs can only use 8-bit inकाष्ठाions.
 *
 * The FIFO and scanlist रेजिस्टरs require two 8-bit inकाष्ठाions to
 * access the 16-bit data. Data is transferred LSB then MSB.
 */
#घोषणा DAQP_AI_FIFO_REG		0x00

#घोषणा DAQP_SCANLIST_REG		0x01
#घोषणा DAQP_SCANLIST_DIFFERENTIAL	BIT(14)
#घोषणा DAQP_SCANLIST_GAIN(x)		(((x) & 0x3) << 12)
#घोषणा DAQP_SCANLIST_CHANNEL(x)	(((x) & 0xf) << 8)
#घोषणा DAQP_SCANLIST_START		BIT(7)
#घोषणा DAQP_SCANLIST_EXT_GAIN(x)	(((x) & 0x3) << 4)
#घोषणा DAQP_SCANLIST_EXT_CHANNEL(x)	(((x) & 0xf) << 0)

#घोषणा DAQP_CTRL_REG			0x02
#घोषणा DAQP_CTRL_PACER_CLK(x)		(((x) & 0x3) << 6)
#घोषणा DAQP_CTRL_PACER_CLK_EXT		DAQP_CTRL_PACER_CLK(0)
#घोषणा DAQP_CTRL_PACER_CLK_5MHZ	DAQP_CTRL_PACER_CLK(1)
#घोषणा DAQP_CTRL_PACER_CLK_1MHZ	DAQP_CTRL_PACER_CLK(2)
#घोषणा DAQP_CTRL_PACER_CLK_100KHZ	DAQP_CTRL_PACER_CLK(3)
#घोषणा DAQP_CTRL_EXPANSION		BIT(5)
#घोषणा DAQP_CTRL_EOS_INT_ENA		BIT(4)
#घोषणा DAQP_CTRL_FIFO_INT_ENA		BIT(3)
#घोषणा DAQP_CTRL_TRIG_MODE		BIT(2)	/* 0=one-shot; 1=continuous */
#घोषणा DAQP_CTRL_TRIG_SRC		BIT(1)	/* 0=पूर्णांकernal; 1=बाह्यal */
#घोषणा DAQP_CTRL_TRIG_EDGE		BIT(0)	/* 0=rising; 1=falling */

#घोषणा DAQP_STATUS_REG			0x02
#घोषणा DAQP_STATUS_IDLE		BIT(7)
#घोषणा DAQP_STATUS_RUNNING		BIT(6)
#घोषणा DAQP_STATUS_DATA_LOST		BIT(5)
#घोषणा DAQP_STATUS_END_OF_SCAN		BIT(4)
#घोषणा DAQP_STATUS_FIFO_THRESHOLD	BIT(3)
#घोषणा DAQP_STATUS_FIFO_FULL		BIT(2)
#घोषणा DAQP_STATUS_FIFO_NEARFULL	BIT(1)
#घोषणा DAQP_STATUS_FIFO_EMPTY		BIT(0)
/* these bits clear when the status रेजिस्टर is पढ़ो */
#घोषणा DAQP_STATUS_EVENTS		(DAQP_STATUS_DATA_LOST |	\
					 DAQP_STATUS_END_OF_SCAN |	\
					 DAQP_STATUS_FIFO_THRESHOLD)

#घोषणा DAQP_DI_REG			0x03
#घोषणा DAQP_DO_REG			0x03

#घोषणा DAQP_PACER_LOW_REG		0x04
#घोषणा DAQP_PACER_MID_REG		0x05
#घोषणा DAQP_PACER_HIGH_REG		0x06

#घोषणा DAQP_CMD_REG			0x07
/* the monostable bits are self-clearing after the function is complete */
#घोषणा DAQP_CMD_ARM			BIT(7)	/* monostable */
#घोषणा DAQP_CMD_RSTF			BIT(6)	/* monostable */
#घोषणा DAQP_CMD_RSTQ			BIT(5)	/* monostable */
#घोषणा DAQP_CMD_STOP			BIT(4)	/* monostable */
#घोषणा DAQP_CMD_LATCH			BIT(3)	/* monostable */
#घोषणा DAQP_CMD_SCANRATE(x)		(((x) & 0x3) << 1)
#घोषणा DAQP_CMD_SCANRATE_100KHZ	DAQP_CMD_SCANRATE(0)
#घोषणा DAQP_CMD_SCANRATE_50KHZ		DAQP_CMD_SCANRATE(1)
#घोषणा DAQP_CMD_SCANRATE_25KHZ		DAQP_CMD_SCANRATE(2)
#घोषणा DAQP_CMD_FIFO_DATA		BIT(0)

#घोषणा DAQP_AO_REG			0x08	/* and 0x09 (16-bit) */

#घोषणा DAQP_TIMER_REG			0x0a	/* and 0x0b (16-bit) */

#घोषणा DAQP_AUX_REG			0x0f
/* Auxiliary Control रेजिस्टर bits (ग_लिखो) */
#घोषणा DAQP_AUX_EXT_ANALOG_TRIG	BIT(7)
#घोषणा DAQP_AUX_PRETRIG		BIT(6)
#घोषणा DAQP_AUX_TIMER_INT_ENA		BIT(5)
#घोषणा DAQP_AUX_TIMER_MODE(x)		(((x) & 0x3) << 3)
#घोषणा DAQP_AUX_TIMER_MODE_RELOAD	DAQP_AUX_TIMER_MODE(0)
#घोषणा DAQP_AUX_TIMER_MODE_PAUSE	DAQP_AUX_TIMER_MODE(1)
#घोषणा DAQP_AUX_TIMER_MODE_GO		DAQP_AUX_TIMER_MODE(2)
#घोषणा DAQP_AUX_TIMER_MODE_EXT		DAQP_AUX_TIMER_MODE(3)
#घोषणा DAQP_AUX_TIMER_CLK_SRC_EXT	BIT(2)
#घोषणा DAQP_AUX_DA_UPDATE(x)		(((x) & 0x3) << 0)
#घोषणा DAQP_AUX_DA_UPDATE_सूचीECT	DAQP_AUX_DA_UPDATE(0)
#घोषणा DAQP_AUX_DA_UPDATE_OVERFLOW	DAQP_AUX_DA_UPDATE(1)
#घोषणा DAQP_AUX_DA_UPDATE_EXTERNAL	DAQP_AUX_DA_UPDATE(2)
#घोषणा DAQP_AUX_DA_UPDATE_PACER	DAQP_AUX_DA_UPDATE(3)
/* Auxiliary Status रेजिस्टर bits (पढ़ो) */
#घोषणा DAQP_AUX_RUNNING		BIT(7)
#घोषणा DAQP_AUX_TRIGGERED		BIT(6)
#घोषणा DAQP_AUX_DA_BUFFER		BIT(5)
#घोषणा DAQP_AUX_TIMER_OVERFLOW		BIT(4)
#घोषणा DAQP_AUX_CONVERSION		BIT(3)
#घोषणा DAQP_AUX_DATA_LOST		BIT(2)
#घोषणा DAQP_AUX_FIFO_NEARFULL		BIT(1)
#घोषणा DAQP_AUX_FIFO_EMPTY		BIT(0)

#घोषणा DAQP_FIFO_SIZE			4096

#घोषणा DAQP_MAX_TIMER_SPEED		10000	/* 100 kHz in nanoseconds */

काष्ठा daqp_निजी अणु
	अचिन्हित पूर्णांक pacer_भाग;
	पूर्णांक stop;
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_daqp_ai = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल पूर्णांक daqp_clear_events(काष्ठा comedi_device *dev, पूर्णांक loops)
अणु
	अचिन्हित पूर्णांक status;

	/*
	 * Reset any pending पूर्णांकerrupts (my card has a tendency to require
	 * multiple पढ़ोs on the status रेजिस्टर to achieve this).
	 */
	जबतक (--loops) अणु
		status = inb(dev->iobase + DAQP_STATUS_REG);
		अगर ((status & DAQP_STATUS_EVENTS) == 0)
			वापस 0;
	पूर्ण
	dev_err(dev->class_dev, "couldn't clear events in status register\n");
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक daqp_ai_cancel(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;

	अगर (devpriv->stop)
		वापस -EIO;

	/*
	 * Stop any conversions, disable पूर्णांकerrupts, and clear
	 * the status event flags.
	 */
	outb(DAQP_CMD_STOP, dev->iobase + DAQP_CMD_REG);
	outb(0, dev->iobase + DAQP_CTRL_REG);
	inb(dev->iobase + DAQP_STATUS_REG);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक daqp_ai_get_sample(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	/*
	 * Get a two's complement sample from the FIFO and
	 * वापस the munged offset binary value.
	 */
	val = inb(dev->iobase + DAQP_AI_FIFO_REG);
	val |= inb(dev->iobase + DAQP_AI_FIFO_REG) << 8;
	वापस comedi_offset_munge(s, val);
पूर्ण

अटल irqवापस_t daqp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा comedi_device *dev = dev_id;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक loop_limit = 10000;
	पूर्णांक status;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	status = inb(dev->iobase + DAQP_STATUS_REG);
	अगर (!(status & DAQP_STATUS_EVENTS))
		वापस IRQ_NONE;

	जबतक (!(status & DAQP_STATUS_FIFO_EMPTY)) अणु
		अचिन्हित लघु data;

		अगर (status & DAQP_STATUS_DATA_LOST) अणु
			s->async->events |= COMEDI_CB_OVERFLOW;
			dev_warn(dev->class_dev, "data lost\n");
			अवरोध;
		पूर्ण

		data = daqp_ai_get_sample(dev, s);
		comedi_buf_ग_लिखो_samples(s, &data, 1);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_करोne >= cmd->stop_arg) अणु
			s->async->events |= COMEDI_CB_EOA;
			अवरोध;
		पूर्ण

		अगर ((loop_limit--) <= 0)
			अवरोध;

		status = inb(dev->iobase + DAQP_STATUS_REG);
	पूर्ण

	अगर (loop_limit <= 0) अणु
		dev_warn(dev->class_dev,
			 "loop_limit reached in %s()\n", __func__);
		s->async->events |= COMEDI_CB_ERROR;
	पूर्ण

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम daqp_ai_set_one_scanlist_entry(काष्ठा comedi_device *dev,
					   अचिन्हित पूर्णांक chanspec,
					   पूर्णांक start)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
	अचिन्हित पूर्णांक val;

	val = DAQP_SCANLIST_CHANNEL(chan) | DAQP_SCANLIST_GAIN(range);

	अगर (aref == AREF_DIFF)
		val |= DAQP_SCANLIST_DIFFERENTIAL;

	अगर (start)
		val |= DAQP_SCANLIST_START;

	outb(val & 0xff, dev->iobase + DAQP_SCANLIST_REG);
	outb((val >> 8) & 0xff, dev->iobase + DAQP_SCANLIST_REG);
पूर्ण

अटल पूर्णांक daqp_ai_eos(काष्ठा comedi_device *dev,
		       काष्ठा comedi_subdevice *s,
		       काष्ठा comedi_insn *insn,
		       अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAQP_AUX_REG);
	अगर (status & DAQP_AUX_CONVERSION)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक daqp_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (devpriv->stop)
		वापस -EIO;

	outb(0, dev->iobase + DAQP_AUX_REG);

	/* Reset scan list queue */
	outb(DAQP_CMD_RSTQ, dev->iobase + DAQP_CMD_REG);

	/* Program one scan list entry */
	daqp_ai_set_one_scanlist_entry(dev, insn->chanspec, 1);

	/* Reset data FIFO (see page 28 of DAQP User's Manual) */
	outb(DAQP_CMD_RSTF, dev->iobase + DAQP_CMD_REG);

	/* Set trigger - one-shot, पूर्णांकernal, no पूर्णांकerrupts */
	outb(DAQP_CTRL_PACER_CLK_100KHZ, dev->iobase + DAQP_CTRL_REG);

	ret = daqp_clear_events(dev, 10000);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < insn->n; i++) अणु
		/* Start conversion */
		outb(DAQP_CMD_ARM | DAQP_CMD_FIFO_DATA,
		     dev->iobase + DAQP_CMD_REG);

		ret = comedi_समयout(dev, s, insn, daqp_ai_eos, 0);
		अगर (ret)
			अवरोध;

		/* clear the status event flags */
		inb(dev->iobase + DAQP_STATUS_REG);

		data[i] = daqp_ai_get_sample(dev, s);
	पूर्ण

	/* stop any conversions and clear the status event flags */
	outb(DAQP_CMD_STOP, dev->iobase + DAQP_CMD_REG);
	inb(dev->iobase + DAQP_STATUS_REG);

	वापस ret ? ret : insn->n;
पूर्ण

/* This function converts ns nanoseconds to a counter value suitable
 * क्रम programming the device.  We always use the DAQP's 5 MHz घड़ी,
 * which with its 24-bit counter, allows values up to 84 seconds.
 * Also, the function adjusts ns so that it cooresponds to the actual
 * समय that the device will use.
 */

अटल पूर्णांक daqp_ns_to_समयr(अचिन्हित पूर्णांक *ns, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक समयr;

	समयr = *ns / 200;
	*ns = समयr * 200;

	वापस समयr;
पूर्ण

अटल व्योम daqp_set_pacer(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक val)
अणु
	outb(val & 0xff, dev->iobase + DAQP_PACER_LOW_REG);
	outb((val >> 8) & 0xff, dev->iobase + DAQP_PACER_MID_REG);
	outb((val >> 16) & 0xff, dev->iobase + DAQP_PACER_HIGH_REG);
पूर्ण

अटल पूर्णांक daqp_ai_cmdtest(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/* the async command requires a pacer */
	अगर (cmd->scan_begin_src != TRIG_TIMER && cmd->convert_src != TRIG_TIMER)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->scan_begin_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    DAQP_MAX_TIMER_SPEED);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    DAQP_MAX_TIMER_SPEED);

		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			/*
			 * If both scan_begin and convert are both समयr
			 * values, the only way that can make sense is अगर
			 * the scan समय is the number of conversions बार
			 * the convert समय.
			 */
			arg = cmd->convert_arg * cmd->scan_end_arg;
			err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg,
							   arg);
		पूर्ण
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg, 0x00ffffff);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		devpriv->pacer_भाग = daqp_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण अन्यथा अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		devpriv->pacer_भाग = daqp_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक daqp_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक scanlist_start_on_every_entry;
	पूर्णांक threshold;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (devpriv->stop)
		वापस -EIO;

	outb(0, dev->iobase + DAQP_AUX_REG);

	/* Reset scan list queue */
	outb(DAQP_CMD_RSTQ, dev->iobase + DAQP_CMD_REG);

	/* Program pacer घड़ी
	 *
	 * There's two modes we can operate in.  If convert_src is
	 * TRIG_TIMER, then convert_arg specअगरies the समय between
	 * each conversion, so we program the pacer घड़ी to that
	 * frequency and set the SCANLIST_START bit on every scanlist
	 * entry.  Otherwise, convert_src is TRIG_NOW, which means
	 * we want the fastest possible conversions, scan_begin_src
	 * is TRIG_TIMER, and scan_begin_arg specअगरies the समय between
	 * each scan, so we program the pacer घड़ी to this frequency
	 * and only set the SCANLIST_START bit on the first entry.
	 */
	daqp_set_pacer(dev, devpriv->pacer_भाग);

	अगर (cmd->convert_src == TRIG_TIMER)
		scanlist_start_on_every_entry = 1;
	अन्यथा
		scanlist_start_on_every_entry = 0;

	/* Program scan list */
	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		पूर्णांक start = (i == 0 || scanlist_start_on_every_entry);

		daqp_ai_set_one_scanlist_entry(dev, cmd->chanlist[i], start);
	पूर्ण

	/* Now it's समय to program the FIFO threshold, basically the
	 * number of samples the card will buffer beक्रमe it पूर्णांकerrupts
	 * the CPU.
	 *
	 * If we करोn't have a stop count, then use half the size of
	 * the FIFO (the manufacturer's recommendation).  Consider
	 * that the FIFO can hold 2K samples (4K bytes).  With the
	 * threshold set at half the FIFO size, we have a margin of
	 * error of 1024 samples.  At the chip's maximum sample rate
	 * of 100,000 Hz, the CPU would have to delay पूर्णांकerrupt
	 * service क्रम a full 10 milliseconds in order to lose data
	 * here (as opposed to higher up in the kernel).  I've never
	 * seen it happen.  However, क्रम slow sample rates it may
	 * buffer too much data and पूर्णांकroduce too much delay क्रम the
	 * user application.
	 *
	 * If we have a stop count, then things get more पूर्णांकeresting.
	 * If the stop count is less than the FIFO size (actually
	 * three-quarters of the FIFO size - see below), we just use
	 * the stop count itself as the threshold, the card पूर्णांकerrupts
	 * us when that many samples have been taken, and we समाप्त the
	 * acquisition at that poपूर्णांक and are करोne.  If the stop count
	 * is larger than that, then we भागide it by 2 until it's less
	 * than three quarters of the FIFO size (we always leave the
	 * top quarter of the FIFO as protection against sluggish CPU
	 * पूर्णांकerrupt response) and use that as the threshold.  So, अगर
	 * the stop count is 4000 samples, we भागide by two twice to
	 * get 1000 samples, use that as the threshold, take four
	 * पूर्णांकerrupts to get our 4000 samples and are करोne.
	 *
	 * The algorithm could be more clever.  For example, अगर 81000
	 * samples are requested, we could set the threshold to 1500
	 * samples and take 54 पूर्णांकerrupts to get 81000.  But 54 isn't
	 * a घातer of two, so this algorithm won't find that option.
	 * Instead, it'll set the threshold at 1266 and take 64
	 * पूर्णांकerrupts to get 81024 samples, of which the last 24 will
	 * be discarded... but we won't get the last पूर्णांकerrupt until
	 * they've been collected.  To find the first option, the
	 * computer could look at the prime decomposition of the
	 * sample count (81000 = 3^4 * 5^3 * 2^3) and factor it पूर्णांकo a
	 * threshold (1500 = 3 * 5^3 * 2^2) and an पूर्णांकerrupt count (54
	 * = 3^3 * 2).  Hmmm... a one-line जबतक loop or prime
	 * decomposition of पूर्णांकegers... I'll leave it the way it is.
	 *
	 * I'll also note a mini-race condition beक्रमe ignoring it in
	 * the code.  Let's say we're taking 4000 samples, as beक्रमe.
	 * After 1000 samples, we get an पूर्णांकerrupt.  But beक्रमe that
	 * पूर्णांकerrupt is completely serviced, another sample is taken
	 * and loaded पूर्णांकo the FIFO.  Since the पूर्णांकerrupt handler
	 * empties the FIFO beक्रमe वापसing, it will पढ़ो 1001 samples.
	 * If that happens four बार, we'll end up taking 4004 samples,
	 * not 4000.  The पूर्णांकerrupt handler will discard the extra four
	 * samples (by halting the acquisition with four samples still
	 * in the FIFO), but we will have to रुको क्रम them.
	 *
	 * In लघु, this code works pretty well, but क्रम either of
	 * the two reasons noted, might end up रुकोing क्रम a few more
	 * samples than actually requested.  Shouldn't make too much
	 * of a dअगरference.
	 */

	/* Save away the number of conversions we should perक्रमm, and
	 * compute the FIFO threshold (in bytes, not samples - that's
	 * why we multiple devpriv->count by 2 = माप(sample))
	 */

	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अचिन्हित दीर्घ दीर्घ nsamples;
		अचिन्हित दीर्घ दीर्घ nbytes;

		nsamples = (अचिन्हित दीर्घ दीर्घ)cmd->stop_arg *
			   cmd->scan_end_arg;
		nbytes = nsamples * comedi_bytes_per_sample(s);
		जबतक (nbytes > DAQP_FIFO_SIZE * 3 / 4)
			nbytes /= 2;
		threshold = nbytes;
	पूर्ण अन्यथा अणु
		threshold = DAQP_FIFO_SIZE / 2;
	पूर्ण

	/* Reset data FIFO (see page 28 of DAQP User's Manual) */

	outb(DAQP_CMD_RSTF, dev->iobase + DAQP_CMD_REG);

	/* Set FIFO threshold.  First two bytes are near-empty
	 * threshold, which is unused; next two bytes are near-full
	 * threshold.  We computed the number of bytes we want in the
	 * FIFO when the पूर्णांकerrupt is generated, what the card wants
	 * is actually the number of available bytes left in the FIFO
	 * when the पूर्णांकerrupt is to happen.
	 */

	outb(0x00, dev->iobase + DAQP_AI_FIFO_REG);
	outb(0x00, dev->iobase + DAQP_AI_FIFO_REG);

	outb((DAQP_FIFO_SIZE - threshold) & 0xff,
	     dev->iobase + DAQP_AI_FIFO_REG);
	outb((DAQP_FIFO_SIZE - threshold) >> 8, dev->iobase + DAQP_AI_FIFO_REG);

	/* Set trigger - continuous, पूर्णांकernal */
	outb(DAQP_CTRL_TRIG_MODE | DAQP_CTRL_PACER_CLK_5MHZ |
	     DAQP_CTRL_FIFO_INT_ENA, dev->iobase + DAQP_CTRL_REG);

	ret = daqp_clear_events(dev, 100);
	अगर (ret)
		वापस ret;

	/* Start conversion */
	outb(DAQP_CMD_ARM | DAQP_CMD_FIFO_DATA, dev->iobase + DAQP_CMD_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक daqp_ao_empty(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAQP_AUX_REG);
	अगर ((status & DAQP_AUX_DA_BUFFER) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक daqp_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	अगर (devpriv->stop)
		वापस -EIO;

	/* Make sure D/A update mode is direct update */
	outb(0, dev->iobase + DAQP_AUX_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];
		पूर्णांक ret;

		/* D/A transfer rate is about 8ms */
		ret = comedi_समयout(dev, s, insn, daqp_ao_empty, 0);
		अगर (ret)
			वापस ret;

		/* ग_लिखो the two's complement value to the channel */
		outw((chan << 12) | comedi_offset_munge(s, val),
		     dev->iobase + DAQP_AO_REG);

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक daqp_di_insn_bits(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;

	अगर (devpriv->stop)
		वापस -EIO;

	data[0] = inb(dev->iobase + DAQP_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक daqp_करो_insn_bits(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा daqp_निजी *devpriv = dev->निजी;

	अगर (devpriv->stop)
		वापस -EIO;

	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAQP_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक daqp_स्वतः_attach(काष्ठा comedi_device *dev,
			    अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	काष्ठा daqp_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	link->config_flags |= CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	ret = comedi_pcmcia_enable(dev, शून्य);
	अगर (ret)
		वापस ret;
	dev->iobase = link->resource[0]->start;

	link->priv = dev;
	ret = pcmcia_request_irq(link, daqp_पूर्णांकerrupt);
	अगर (ret == 0)
		dev->irq = link->irq;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 8;
	s->maxdata	= 0xffff;
	s->range_table	= &range_daqp_ai;
	s->insn_पढ़ो	= daqp_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 2048;
		s->करो_cmdtest	= daqp_ai_cmdtest;
		s->करो_cmd	= daqp_ai_cmd;
		s->cancel	= daqp_ai_cancel;
	पूर्ण

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= &range_bipolar5;
	s->insn_ग_लिखो	= daqp_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/*
	 * Digital Input subdevice
	 * NOTE: The digital input lines are shared:
	 *
	 * Chan  Normal Mode        Expansion Mode
	 * ----  -----------------  ----------------------------
	 *  0    DI0, ext. trigger  Same as normal mode
	 *  1    DI1                External gain select, lo bit
	 *  2    DI2, ext. घड़ी    Same as normal mode
	 *  3    DI3                External gain select, hi bit
	 */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->insn_bits	= daqp_di_insn_bits;

	/*
	 * Digital Output subdevice
	 * NOTE: The digital output lines share the same pins on the
	 * पूर्णांकerface connector as the four बाह्यal channel selection
	 * bits. If expansion mode is used the digital outमाला_दो करो not
	 * work.
	 */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->insn_bits	= daqp_करो_insn_bits;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver driver_daqp = अणु
	.driver_name	= "quatech_daqp_cs",
	.module		= THIS_MODULE,
	.स्वतः_attach	= daqp_स्वतः_attach,
	.detach		= comedi_pcmcia_disable,
पूर्ण;

अटल पूर्णांक daqp_cs_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा comedi_device *dev = link->priv;
	काष्ठा daqp_निजी *devpriv = dev ? dev->निजी : शून्य;

	/* Mark the device as stopped, to block IO until later */
	अगर (devpriv)
		devpriv->stop = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक daqp_cs_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा comedi_device *dev = link->priv;
	काष्ठा daqp_निजी *devpriv = dev ? dev->निजी : शून्य;

	अगर (devpriv)
		devpriv->stop = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक daqp_cs_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &driver_daqp);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id daqp_cs_id_table[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x0137, 0x0027),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, daqp_cs_id_table);

अटल काष्ठा pcmcia_driver daqp_cs_driver = अणु
	.name		= "quatech_daqp_cs",
	.owner		= THIS_MODULE,
	.id_table	= daqp_cs_id_table,
	.probe		= daqp_cs_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
	.suspend	= daqp_cs_suspend,
	.resume		= daqp_cs_resume,
पूर्ण;
module_comedi_pcmcia_driver(driver_daqp, daqp_cs_driver);

MODULE_DESCRIPTION("Comedi driver for Quatech DAQP PCMCIA data capture cards");
MODULE_AUTHOR("Brent Baccala <baccala@freesoft.org>");
MODULE_LICENSE("GPL");
