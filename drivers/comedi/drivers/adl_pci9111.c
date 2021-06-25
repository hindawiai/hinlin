<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adl_pci9111.c
 * Hardware driver क्रम PCI9111 ADLink cards: PCI-9111HR
 * Copyright (C) 2002-2005 Emmanuel Pacaud <emmanuel.pacaud@univ-poitiers.fr>
 */

/*
 * Driver: adl_pci9111
 * Description: Adlink PCI-9111HR
 * Devices: [ADLink] PCI-9111HR (adl_pci9111)
 * Author: Emmanuel Pacaud <emmanuel.pacaud@univ-poitiers.fr>
 * Status: experimental
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * Supports:
 * - ai_insn पढ़ो
 * - ao_insn पढ़ो/ग_लिखो
 * - di_insn पढ़ो
 * - करो_insn पढ़ो/ग_लिखो
 * - ai_करो_cmd mode with the following sources:
 *	- start_src		TRIG_NOW
 *	- scan_begin_src	TRIG_FOLLOW	TRIG_TIMER	TRIG_EXT
 *	- convert_src				TRIG_TIMER	TRIG_EXT
 *	- scan_end_src		TRIG_COUNT
 *	- stop_src		TRIG_COUNT	TRIG_NONE
 *
 * The scanned channels must be consecutive and start from 0. They must
 * all have the same range and aref.
 */

/*
 * TODO:
 * - Really test implemented functionality.
 * - Add support क्रम the PCI-9111DG with a probe routine to identअगरy
 *   the card type (perhaps with the help of the channel number पढ़ोback
 *   of the A/D Data रेजिस्टर).
 * - Add बाह्यal multiplexer support.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "plx9052.h"
#समावेश "comedi_8254.h"

#घोषणा PCI9111_FIFO_HALF_SIZE	512

#घोषणा PCI9111_AI_ACQUISITION_PERIOD_MIN_NS	10000

#घोषणा PCI9111_RANGE_SETTING_DELAY		10
#घोषणा PCI9111_AI_INSTANT_READ_UDELAY_US	2

/*
 * IO address map and bit defines
 */
#घोषणा PCI9111_AI_FIFO_REG		0x00
#घोषणा PCI9111_AO_REG			0x00
#घोषणा PCI9111_DIO_REG			0x02
#घोषणा PCI9111_EDIO_REG		0x04
#घोषणा PCI9111_AI_CHANNEL_REG		0x06
#घोषणा PCI9111_AI_RANGE_STAT_REG	0x08
#घोषणा PCI9111_AI_STAT_AD_BUSY		BIT(7)
#घोषणा PCI9111_AI_STAT_FF_FF		BIT(6)
#घोषणा PCI9111_AI_STAT_FF_HF		BIT(5)
#घोषणा PCI9111_AI_STAT_FF_EF		BIT(4)
#घोषणा PCI9111_AI_RANGE(x)		(((x) & 0x7) << 0)
#घोषणा PCI9111_AI_RANGE_MASK		PCI9111_AI_RANGE(7)
#घोषणा PCI9111_AI_TRIG_CTRL_REG	0x0a
#घोषणा PCI9111_AI_TRIG_CTRL_TRGEVENT	BIT(5)
#घोषणा PCI9111_AI_TRIG_CTRL_POTRG	BIT(4)
#घोषणा PCI9111_AI_TRIG_CTRL_PTRG	BIT(3)
#घोषणा PCI9111_AI_TRIG_CTRL_ETIS	BIT(2)
#घोषणा PCI9111_AI_TRIG_CTRL_TPST	BIT(1)
#घोषणा PCI9111_AI_TRIG_CTRL_ASCAN	BIT(0)
#घोषणा PCI9111_INT_CTRL_REG		0x0c
#घोषणा PCI9111_INT_CTRL_ISC2		BIT(3)
#घोषणा PCI9111_INT_CTRL_FFEN		BIT(2)
#घोषणा PCI9111_INT_CTRL_ISC1		BIT(1)
#घोषणा PCI9111_INT_CTRL_ISC0		BIT(0)
#घोषणा PCI9111_SOFT_TRIG_REG		0x0e
#घोषणा PCI9111_8254_BASE_REG		0x40
#घोषणा PCI9111_INT_CLR_REG		0x48

/* PLX 9052 Local Interrupt 1 enabled and active */
#घोषणा PCI9111_LI1_ACTIVE	(PLX9052_INTCSR_LI1ENAB |	\
				 PLX9052_INTCSR_LI1STAT)

/* PLX 9052 Local Interrupt 2 enabled and active */
#घोषणा PCI9111_LI2_ACTIVE	(PLX9052_INTCSR_LI2ENAB |	\
				 PLX9052_INTCSR_LI2STAT)

अटल स्थिर काष्ठा comedi_lrange pci9111_ai_range = अणु
	5, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

काष्ठा pci9111_निजी_data अणु
	अचिन्हित दीर्घ lcr_io_base;

	अचिन्हित पूर्णांक scan_delay;
	अचिन्हित पूर्णांक chunk_counter;
	अचिन्हित पूर्णांक chunk_num_samples;

	अचिन्हित लघु ai_bounce_buffer[2 * PCI9111_FIFO_HALF_SIZE];
पूर्ण;

अटल व्योम plx9050_पूर्णांकerrupt_control(अचिन्हित दीर्घ io_base,
				      bool पूर्णांक1_enable,
				      bool पूर्णांक1_active_high,
				      bool पूर्णांक2_enable,
				      bool पूर्णांक2_active_high,
				      bool पूर्णांकerrupt_enable)
अणु
	पूर्णांक flags = 0;

	अगर (पूर्णांक1_enable)
		flags |= PLX9052_INTCSR_LI1ENAB;
	अगर (पूर्णांक1_active_high)
		flags |= PLX9052_INTCSR_LI1POL;
	अगर (पूर्णांक2_enable)
		flags |= PLX9052_INTCSR_LI2ENAB;
	अगर (पूर्णांक2_active_high)
		flags |= PLX9052_INTCSR_LI2POL;

	अगर (पूर्णांकerrupt_enable)
		flags |= PLX9052_INTCSR_PCIENAB;

	outb(flags, io_base + PLX9052_INTCSR);
पूर्ण

क्रमागत pci9111_ISC0_sources अणु
	irq_on_eoc,
	irq_on_fअगरo_half_full
पूर्ण;

क्रमागत pci9111_ISC1_sources अणु
	irq_on_समयr_tick,
	irq_on_बाह्यal_trigger
पूर्ण;

अटल व्योम pci9111_पूर्णांकerrupt_source_set(काष्ठा comedi_device *dev,
					 क्रमागत pci9111_ISC0_sources irq_0_source,
					 क्रमागत pci9111_ISC1_sources irq_1_source)
अणु
	पूर्णांक flags;

	/* Read the current पूर्णांकerrupt control bits */
	flags = inb(dev->iobase + PCI9111_AI_TRIG_CTRL_REG);
	/* Shअगरt the bits so they are compatible with the ग_लिखो रेजिस्टर */
	flags >>= 4;
	/* Mask off the ISCx bits */
	flags &= 0xc0;

	/* Now set the new ISCx bits */
	अगर (irq_0_source == irq_on_fअगरo_half_full)
		flags |= PCI9111_INT_CTRL_ISC0;

	अगर (irq_1_source == irq_on_बाह्यal_trigger)
		flags |= PCI9111_INT_CTRL_ISC1;

	outb(flags, dev->iobase + PCI9111_INT_CTRL_REG);
पूर्ण

अटल व्योम pci9111_fअगरo_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित दीर्घ पूर्णांक_ctrl_reg = dev->iobase + PCI9111_INT_CTRL_REG;

	/* To reset the FIFO, set FFEN sequence as 0 -> 1 -> 0 */
	outb(0, पूर्णांक_ctrl_reg);
	outb(PCI9111_INT_CTRL_FFEN, पूर्णांक_ctrl_reg);
	outb(0, पूर्णांक_ctrl_reg);
पूर्ण

अटल पूर्णांक pci9111_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9111_निजी_data *dev_निजी = dev->निजी;

	/*  Disable पूर्णांकerrupts */
	plx9050_पूर्णांकerrupt_control(dev_निजी->lcr_io_base, true, true, true,
				  true, false);

	/* disable A/D triggers (software trigger mode) and स्वतः scan off */
	outb(0, dev->iobase + PCI9111_AI_TRIG_CTRL_REG);

	pci9111_fअगरo_reset(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci9111_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (chan != i) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must be consecutive channels,counting upwards from 0\n");
			वापस -EINVAL;
		पूर्ण

		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same gain\n");
			वापस -EINVAL;
		पूर्ण

		अगर (aref != aref0) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same reference\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci9111_ai_करो_cmd_test(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_FOLLOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
		अगर (cmd->scan_begin_src != cmd->convert_src)
			err |= -EINVAL;
	पूर्ण

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
					PCI9111_AI_ACQUISITION_PERIOD_MIN_NS);
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
					PCI9111_AI_ACQUISITION_PERIOD_MIN_NS);
	पूर्ण अन्यथा अणु	/* TRIG_FOLLOW || TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	/*
	 * There's only one समयr on this card, so the scan_begin समयr
	 * must be a multiple of chanlist_len*convert_arg
	 */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->chanlist_len * cmd->convert_arg;

		अगर (arg < cmd->scan_begin_arg)
			arg *= (cmd->scan_begin_arg / arg);

		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci9111_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक pci9111_ai_करो_cmd(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9111_निजी_data *dev_निजी = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक last_chan = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक trig = 0;

	/*  Set channel scan limit */
	/*  PCI9111 allows only scanning from channel 0 to channel n */
	/*  TODO: handle the हाल of an बाह्यal multiplexer */

	अगर (cmd->chanlist_len > 1)
		trig |= PCI9111_AI_TRIG_CTRL_ASCAN;

	outb(last_chan, dev->iobase + PCI9111_AI_CHANNEL_REG);

	/*  Set gain - all channels use the same range */
	outb(PCI9111_AI_RANGE(range0), dev->iobase + PCI9111_AI_RANGE_STAT_REG);

	/*  Set समयr pacer */
	dev_निजी->scan_delay = 0;
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		trig |= PCI9111_AI_TRIG_CTRL_TPST;
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		pci9111_fअगरo_reset(dev);
		pci9111_पूर्णांकerrupt_source_set(dev, irq_on_fअगरo_half_full,
					     irq_on_समयr_tick);
		plx9050_पूर्णांकerrupt_control(dev_निजी->lcr_io_base, true, true,
					  false, true, true);

		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			dev_निजी->scan_delay = (cmd->scan_begin_arg /
				(cmd->convert_arg * cmd->chanlist_len)) - 1;
		पूर्ण
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		trig |= PCI9111_AI_TRIG_CTRL_ETIS;
		pci9111_fअगरo_reset(dev);
		pci9111_पूर्णांकerrupt_source_set(dev, irq_on_fअगरo_half_full,
					     irq_on_समयr_tick);
		plx9050_पूर्णांकerrupt_control(dev_निजी->lcr_io_base, true, true,
					  false, true, true);
	पूर्ण
	outb(trig, dev->iobase + PCI9111_AI_TRIG_CTRL_REG);

	dev_निजी->chunk_counter = 0;
	dev_निजी->chunk_num_samples = cmd->chanlist_len *
					 (1 + dev_निजी->scan_delay);

	वापस 0;
पूर्ण

अटल व्योम pci9111_ai_munge(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, व्योम *data,
			     अचिन्हित पूर्णांक num_bytes,
			     अचिन्हित पूर्णांक start_chan_index)
अणु
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक maxdata = s->maxdata;
	अचिन्हित पूर्णांक invert = (maxdata + 1) >> 1;
	अचिन्हित पूर्णांक shअगरt = (maxdata == 0xffff) ? 0 : 4;
	अचिन्हित पूर्णांक num_samples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_samples; i++)
		array[i] = ((array[i] >> shअगरt) & maxdata) ^ invert;
पूर्ण

अटल व्योम pci9111_handle_fअगरo_half_full(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9111_निजी_data *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित लघु *buf = devpriv->ai_bounce_buffer;
	अचिन्हित पूर्णांक samples;

	samples = comedi_nsamples_left(s, PCI9111_FIFO_HALF_SIZE);
	insw(dev->iobase + PCI9111_AI_FIFO_REG, buf, samples);

	अगर (devpriv->scan_delay < 1) अणु
		comedi_buf_ग_लिखो_samples(s, buf, samples);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक pos = 0;
		अचिन्हित पूर्णांक to_पढ़ो;

		जबतक (pos < samples) अणु
			अगर (devpriv->chunk_counter < cmd->chanlist_len) अणु
				to_पढ़ो = cmd->chanlist_len -
					  devpriv->chunk_counter;

				अगर (to_पढ़ो > samples - pos)
					to_पढ़ो = samples - pos;

				comedi_buf_ग_लिखो_samples(s, buf + pos, to_पढ़ो);
			पूर्ण अन्यथा अणु
				to_पढ़ो = devpriv->chunk_num_samples -
					  devpriv->chunk_counter;

				अगर (to_पढ़ो > samples - pos)
					to_पढ़ो = samples - pos;
			पूर्ण

			pos += to_पढ़ो;
			devpriv->chunk_counter += to_पढ़ो;

			अगर (devpriv->chunk_counter >=
			    devpriv->chunk_num_samples)
				devpriv->chunk_counter = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t pci9111_पूर्णांकerrupt(पूर्णांक irq, व्योम *p_device)
अणु
	काष्ठा comedi_device *dev = p_device;
	काष्ठा pci9111_निजी_data *dev_निजी = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async;
	काष्ठा comedi_cmd *cmd;
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित अक्षर पूर्णांकcsr;

	अगर (!dev->attached) अणु
		/*  Ignore पूर्णांकerrupt beक्रमe device fully attached. */
		/*  Might not even have allocated subdevices yet! */
		वापस IRQ_NONE;
	पूर्ण

	async = s->async;
	cmd = &async->cmd;

	spin_lock_irqsave(&dev->spinlock, irq_flags);

	/*  Check अगर we are source of पूर्णांकerrupt */
	पूर्णांकcsr = inb(dev_निजी->lcr_io_base + PLX9052_INTCSR);
	अगर (!(((पूर्णांकcsr & PLX9052_INTCSR_PCIENAB) != 0) &&
	      (((पूर्णांकcsr & PCI9111_LI1_ACTIVE) == PCI9111_LI1_ACTIVE) ||
	       ((पूर्णांकcsr & PCI9111_LI2_ACTIVE) == PCI9111_LI2_ACTIVE)))) अणु
		/*  Not the source of the पूर्णांकerrupt. */
		/*  (N.B. not using PLX9052_INTCSR_SOFTINT) */
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर ((पूर्णांकcsr & PCI9111_LI1_ACTIVE) == PCI9111_LI1_ACTIVE) अणु
		/*  Interrupt comes from fअगरo_half-full संकेत */

		status = inb(dev->iobase + PCI9111_AI_RANGE_STAT_REG);

		/* '0' means FIFO is full, data may have been lost */
		अगर (!(status & PCI9111_AI_STAT_FF_FF)) अणु
			spin_unlock_irqrestore(&dev->spinlock, irq_flags);
			dev_dbg(dev->class_dev, "fifo overflow\n");
			outb(0, dev->iobase + PCI9111_INT_CLR_REG);
			async->events |= COMEDI_CB_ERROR;
			comedi_handle_events(dev, s);

			वापस IRQ_HANDLED;
		पूर्ण

		/* '0' means FIFO is half-full */
		अगर (!(status & PCI9111_AI_STAT_FF_HF))
			pci9111_handle_fअगरo_half_full(dev, s);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	outb(0, dev->iobase + PCI9111_INT_CLR_REG);

	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pci9111_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + PCI9111_AI_RANGE_STAT_REG);
	अगर (status & PCI9111_AI_STAT_FF_EF)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pci9111_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक maxdata = s->maxdata;
	अचिन्हित पूर्णांक invert = (maxdata + 1) >> 1;
	अचिन्हित पूर्णांक shअगरt = (maxdata == 0xffff) ? 0 : 4;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;
	पूर्णांक i;

	outb(chan, dev->iobase + PCI9111_AI_CHANNEL_REG);

	status = inb(dev->iobase + PCI9111_AI_RANGE_STAT_REG);
	अगर ((status & PCI9111_AI_RANGE_MASK) != range) अणु
		outb(PCI9111_AI_RANGE(range),
		     dev->iobase + PCI9111_AI_RANGE_STAT_REG);
	पूर्ण

	pci9111_fअगरo_reset(dev);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* Generate a software trigger */
		outb(0, dev->iobase + PCI9111_SOFT_TRIG_REG);

		ret = comedi_समयout(dev, s, insn, pci9111_ai_eoc, 0);
		अगर (ret) अणु
			pci9111_fअगरo_reset(dev);
			वापस ret;
		पूर्ण

		data[i] = inw(dev->iobase + PCI9111_AI_FIFO_REG);
		data[i] = ((data[i] >> shअगरt) & maxdata) ^ invert;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक pci9111_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, dev->iobase + PCI9111_AO_REG);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci9111_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inw(dev->iobase + PCI9111_DIO_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci9111_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI9111_DIO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci9111_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci9111_निजी_data *dev_निजी = dev->निजी;

	/*  Set trigger source to software */
	plx9050_पूर्णांकerrupt_control(dev_निजी->lcr_io_base, true, true, true,
				  true, false);

	/* disable A/D triggers (software trigger mode) and स्वतः scan off */
	outb(0, dev->iobase + PCI9111_AI_TRIG_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक pci9111_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा pci9111_निजी_data *dev_निजी;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	dev_निजी = comedi_alloc_devpriv(dev, माप(*dev_निजी));
	अगर (!dev_निजी)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev_निजी->lcr_io_base = pci_resource_start(pcidev, 1);
	dev->iobase = pci_resource_start(pcidev, 2);

	pci9111_reset(dev);

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, pci9111_पूर्णांकerrupt,
				  IRQF_SHARED, dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + PCI9111_8254_BASE_REG,
				      I8254_OSC_BASE_2MHZ, I8254_IO16, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_COMMON;
	s->n_chan	= 16;
	s->maxdata	= 0xffff;
	s->range_table	= &pci9111_ai_range;
	s->insn_पढ़ो	= pci9111_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmdtest	= pci9111_ai_करो_cmd_test;
		s->करो_cmd	= pci9111_ai_करो_cmd;
		s->cancel	= pci9111_ai_cancel;
		s->munge	= pci9111_ai_munge;
	पूर्ण

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_COMMON;
	s->n_chan	= 1;
	s->maxdata	= 0x0fff;
	s->len_chanlist	= 1;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= pci9111_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci9111_di_insn_bits;

	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci9111_करो_insn_bits;

	वापस 0;
पूर्ण

अटल व्योम pci9111_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		pci9111_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver adl_pci9111_driver = अणु
	.driver_name	= "adl_pci9111",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci9111_स्वतः_attach,
	.detach		= pci9111_detach,
पूर्ण;

अटल पूर्णांक pci9111_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adl_pci9111_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pci9111_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADLINK, 0x9111) पूर्ण,
	/* अणु PCI_DEVICE(PCI_VENDOR_ID_ADLINK, PCI9111_HG_DEVICE_ID) पूर्ण, */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci9111_pci_table);

अटल काष्ठा pci_driver adl_pci9111_pci_driver = अणु
	.name		= "adl_pci9111",
	.id_table	= pci9111_pci_table,
	.probe		= pci9111_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adl_pci9111_driver, adl_pci9111_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
