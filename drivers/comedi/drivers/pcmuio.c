<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pcmuio.c
 * Comedi driver क्रम Winप्रणालीs PC-104 based 48/96-channel DIO boards.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2006 Calin A. Culianu <calin@ajvar.org>
 */

/*
 * Driver: pcmuio
 * Description: Winप्रणालीs PC-104 based 48/96-channel DIO boards.
 * Devices: [Winप्रणालीs] PCM-UIO48A (pcmuio48), PCM-UIO96A (pcmuio96)
 * Author: Calin Culianu <calin@ajvar.org>
 * Updated: Fri, 13 Jan 2006 12:01:01 -0500
 * Status: works
 *
 * A driver क्रम the relatively straightक्रमward-to-program PCM-UIO48A and
 * PCM-UIO96A boards from Winप्रणालीs. These boards use either one or two
 * (in the 96-DIO version) WS16C48 ASIC HighDensity I/O Chips (HDIO). This
 * chip is पूर्णांकeresting in that each I/O line is inभागidually programmable
 * क्रम INPUT or OUTPUT (thus comedi_dio_config can be करोne on a per-channel
 * basis). Also, each chip supports edge-triggered पूर्णांकerrupts क्रम the first
 * 24 I/O lines. Of course, since the 96-channel version of the board has
 * two ASICs, it can detect polarity changes on up to 48 I/O lines. Since
 * this is essentially an (non-PnP) ISA board, I/O Address and IRQ selection
 * are करोne through jumpers on the board. You need to pass that inक्रमmation
 * to this driver as the first and second comedi_config option, respectively.
 * Note that the 48-channel version uses 16 bytes of IO memory and the 96-
 * channel version uses 32-bytes (in हाल you are worried about conflicts).
 * The 48-channel board is split पूर्णांकo two 24-channel comedi subdevices. The
 * 96-channel board is split पूर्णांकo 4 24-channel DIO subdevices.
 *
 * Note that IRQ support has been added, but it is untested.
 *
 * To use edge-detection IRQ support, pass the IRQs of both ASICS (क्रम the
 * 96 channel version) or just 1 ASIC (क्रम 48-channel version). Then, use
 * comedi_commands with TRIG_NOW. Your callback will be called each समय an
 * edge is triggered, and the data values will be two sample_t's, which
 * should be concatenated to क्रमm one 32-bit अचिन्हित पूर्णांक.  This value is
 * the mask of channels that had edges detected from your channel list. Note
 * that the bits positions in the mask correspond to positions in your
 * chanlist when you specअगरied the command and *not* channel id's!
 *
 * To set the polarity of the edge-detection पूर्णांकerrupts pass a nonzero value
 * क्रम either CR_RANGE or CR_AREF क्रम edge-up polarity, or a zero value क्रम
 * both CR_RANGE and CR_AREF अगर you want edge-करोwn polarity.
 *
 * In the 48-channel version:
 *
 * On subdev 0, the first 24 channels are edge-detect channels.
 *
 * In the 96-channel board you have the following channels that can करो edge
 * detection:
 *
 * subdev 0, channels 0-24  (first 24 channels of 1st ASIC)
 * subdev 2, channels 0-24  (first 24 channels of 2nd ASIC)
 *
 * Configuration Options:
 *  [0] - I/O port base address
 *  [1] - IRQ (क्रम first ASIC, or first 24 channels)
 *  [2] - IRQ (क्रम second ASIC, pcmuio96 only - IRQ क्रम chans 48-72
 *             can be the same as first irq!)
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

/*
 * Register I/O map
 *
 * Offset    Page 0       Page 1       Page 2       Page 3
 * ------  -----------  -----------  -----------  -----------
 *  0x00   Port 0 I/O   Port 0 I/O   Port 0 I/O   Port 0 I/O
 *  0x01   Port 1 I/O   Port 1 I/O   Port 1 I/O   Port 1 I/O
 *  0x02   Port 2 I/O   Port 2 I/O   Port 2 I/O   Port 2 I/O
 *  0x03   Port 3 I/O   Port 3 I/O   Port 3 I/O   Port 3 I/O
 *  0x04   Port 4 I/O   Port 4 I/O   Port 4 I/O   Port 4 I/O
 *  0x05   Port 5 I/O   Port 5 I/O   Port 5 I/O   Port 5 I/O
 *  0x06   INT_PENDING  INT_PENDING  INT_PENDING  INT_PENDING
 *  0x07    Page/Lock    Page/Lock    Page/Lock    Page/Lock
 *  0x08       N/A         POL_0       ENAB_0       INT_ID0
 *  0x09       N/A         POL_1       ENAB_1       INT_ID1
 *  0x0a       N/A         POL_2       ENAB_2       INT_ID2
 */
#घोषणा PCMUIO_PORT_REG(x)		(0x00 + (x))
#घोषणा PCMUIO_INT_PENDING_REG		0x06
#घोषणा PCMUIO_PAGE_LOCK_REG		0x07
#घोषणा PCMUIO_LOCK_PORT(x)		((1 << (x)) & 0x3f)
#घोषणा PCMUIO_PAGE(x)			(((x) & 0x3) << 6)
#घोषणा PCMUIO_PAGE_MASK		PCMUIO_PAGE(3)
#घोषणा PCMUIO_PAGE_POL			1
#घोषणा PCMUIO_PAGE_ENAB		2
#घोषणा PCMUIO_PAGE_INT_ID		3
#घोषणा PCMUIO_PAGE_REG(x)		(0x08 + (x))

#घोषणा PCMUIO_ASIC_IOSIZE		0x10
#घोषणा PCMUIO_MAX_ASICS		2

काष्ठा pcmuio_board अणु
	स्थिर अक्षर *name;
	स्थिर पूर्णांक num_asics;
पूर्ण;

अटल स्थिर काष्ठा pcmuio_board pcmuio_boards[] = अणु
	अणु
		.name		= "pcmuio48",
		.num_asics	= 1,
	पूर्ण, अणु
		.name		= "pcmuio96",
		.num_asics	= 2,
	पूर्ण,
पूर्ण;

काष्ठा pcmuio_asic अणु
	spinlock_t pagelock;	/* protects the page रेजिस्टरs */
	spinlock_t spinlock;	/* protects member variables */
	अचिन्हित पूर्णांक enabled_mask;
	अचिन्हित पूर्णांक active:1;
पूर्ण;

काष्ठा pcmuio_निजी अणु
	काष्ठा pcmuio_asic asics[PCMUIO_MAX_ASICS];
	अचिन्हित पूर्णांक irq2;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ pcmuio_asic_iobase(काष्ठा comedi_device *dev,
					       पूर्णांक asic)
अणु
	वापस dev->iobase + (asic * PCMUIO_ASIC_IOSIZE);
पूर्ण

अटल अंतरभूत पूर्णांक pcmuio_subdevice_to_asic(काष्ठा comedi_subdevice *s)
अणु
	/*
	 * subdevice 0 and 1 are handled by the first asic
	 * subdevice 2 and 3 are handled by the second asic
	 */
	वापस s->index / 2;
पूर्ण

अटल अंतरभूत पूर्णांक pcmuio_subdevice_to_port(काष्ठा comedi_subdevice *s)
अणु
	/*
	 * subdevice 0 and 2 use port रेजिस्टरs 0-2
	 * subdevice 1 and 3 use port रेजिस्टरs 3-5
	 */
	वापस (s->index % 2) ? 3 : 0;
पूर्ण

अटल व्योम pcmuio_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक val,
			 पूर्णांक asic, पूर्णांक page, पूर्णांक port)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	अचिन्हित दीर्घ iobase = pcmuio_asic_iobase(dev, asic);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->pagelock, flags);
	अगर (page == 0) अणु
		/* Port रेजिस्टरs are valid क्रम any page */
		outb(val & 0xff, iobase + PCMUIO_PORT_REG(port + 0));
		outb((val >> 8) & 0xff, iobase + PCMUIO_PORT_REG(port + 1));
		outb((val >> 16) & 0xff, iobase + PCMUIO_PORT_REG(port + 2));
	पूर्ण अन्यथा अणु
		outb(PCMUIO_PAGE(page), iobase + PCMUIO_PAGE_LOCK_REG);
		outb(val & 0xff, iobase + PCMUIO_PAGE_REG(0));
		outb((val >> 8) & 0xff, iobase + PCMUIO_PAGE_REG(1));
		outb((val >> 16) & 0xff, iobase + PCMUIO_PAGE_REG(2));
	पूर्ण
	spin_unlock_irqrestore(&chip->pagelock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक pcmuio_पढ़ो(काष्ठा comedi_device *dev,
				पूर्णांक asic, पूर्णांक page, पूर्णांक port)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	अचिन्हित दीर्घ iobase = pcmuio_asic_iobase(dev, asic);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&chip->pagelock, flags);
	अगर (page == 0) अणु
		/* Port रेजिस्टरs are valid क्रम any page */
		val = inb(iobase + PCMUIO_PORT_REG(port + 0));
		val |= (inb(iobase + PCMUIO_PORT_REG(port + 1)) << 8);
		val |= (inb(iobase + PCMUIO_PORT_REG(port + 2)) << 16);
	पूर्ण अन्यथा अणु
		outb(PCMUIO_PAGE(page), iobase + PCMUIO_PAGE_LOCK_REG);
		val = inb(iobase + PCMUIO_PAGE_REG(0));
		val |= (inb(iobase + PCMUIO_PAGE_REG(1)) << 8);
		val |= (inb(iobase + PCMUIO_PAGE_REG(2)) << 16);
	पूर्ण
	spin_unlock_irqrestore(&chip->pagelock, flags);

	वापस val;
पूर्ण

/*
 * Each channel can be inभागidually programmed क्रम input or output.
 * Writing a '0' to a channel causes the corresponding output pin
 * to go to a high-z state (pulled high by an बाह्यal 10K resistor).
 * This allows it to be used as an input. When used in the input mode,
 * a पढ़ो reflects the inverted state of the I/O pin, such that a
 * high on the pin will पढ़ो as a '0' in the register. Writing a '1'
 * to a bit position causes the pin to sink current (up to 12mA),
 * effectively pulling it low.
 */
अटल पूर्णांक pcmuio_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	पूर्णांक port = pcmuio_subdevice_to_port(s);
	अचिन्हित पूर्णांक chanmask = (1 << s->n_chan) - 1;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		/*
		 * Outमाला_दो are inverted, invert the state and
		 * update the channels.
		 *
		 * The s->io_bits mask makes sure the input channels
		 * are '0' so that the outमाला_दो pins stay in a high
		 * z-state.
		 */
		val = ~s->state & chanmask;
		val &= s->io_bits;
		pcmuio_ग_लिखो(dev, val, asic, 0, port);
	पूर्ण

	/* get inverted state of the channels from the port */
	val = pcmuio_पढ़ो(dev, asic, 0, port);

	/* वापस the true state of the channels */
	data[1] = ~val & chanmask;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcmuio_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	पूर्णांक port = pcmuio_subdevice_to_port(s);
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	अगर (data[0] == INSN_CONFIG_DIO_INPUT)
		pcmuio_ग_लिखो(dev, s->io_bits, asic, 0, port);

	वापस insn->n;
पूर्ण

अटल व्योम pcmuio_reset(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcmuio_board *board = dev->board_ptr;
	पूर्णांक asic;

	क्रम (asic = 0; asic < board->num_asics; ++asic) अणु
		/* first, clear all the DIO port bits */
		pcmuio_ग_लिखो(dev, 0, asic, 0, 0);
		pcmuio_ग_लिखो(dev, 0, asic, 0, 3);

		/* Next, clear all the paged रेजिस्टरs क्रम each page */
		pcmuio_ग_लिखो(dev, 0, asic, PCMUIO_PAGE_POL, 0);
		pcmuio_ग_लिखो(dev, 0, asic, PCMUIO_PAGE_ENAB, 0);
		pcmuio_ग_लिखो(dev, 0, asic, PCMUIO_PAGE_INT_ID, 0);
	पूर्ण
पूर्ण

/* chip->spinlock is alपढ़ोy locked */
अटल व्योम pcmuio_stop_पूर्णांकr(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];

	chip->enabled_mask = 0;
	chip->active = 0;
	s->async->पूर्णांकtrig = शून्य;

	/* disable all पूर्णांकrs क्रम this subdev.. */
	pcmuio_ग_लिखो(dev, 0, asic, PCMUIO_PAGE_ENAB, 0);
पूर्ण

अटल व्योम pcmuio_handle_पूर्णांकr_subdev(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      अचिन्हित पूर्णांक triggered)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&chip->spinlock, flags);

	अगर (!chip->active)
		जाओ करोne;

	अगर (!(triggered & chip->enabled_mask))
		जाओ करोne;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर (triggered & (1 << chan))
			val |= (1 << i);
	पूर्ण

	comedi_buf_ग_लिखो_samples(s, &val, 1);

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg)
		s->async->events |= COMEDI_CB_EOA;

करोne:
	spin_unlock_irqrestore(&chip->spinlock, flags);

	comedi_handle_events(dev, s);
पूर्ण

अटल पूर्णांक pcmuio_handle_asic_पूर्णांकerrupt(काष्ठा comedi_device *dev, पूर्णांक asic)
अणु
	/* there are could be two asics so we can't use dev->पढ़ो_subdev */
	काष्ठा comedi_subdevice *s = &dev->subdevices[asic * 2];
	अचिन्हित दीर्घ iobase = pcmuio_asic_iobase(dev, asic);
	अचिन्हित पूर्णांक val;

	/* are there any पूर्णांकerrupts pending */
	val = inb(iobase + PCMUIO_INT_PENDING_REG) & 0x07;
	अगर (!val)
		वापस 0;

	/* get, and clear, the pending पूर्णांकerrupts */
	val = pcmuio_पढ़ो(dev, asic, PCMUIO_PAGE_INT_ID, 0);
	pcmuio_ग_लिखो(dev, 0, asic, PCMUIO_PAGE_INT_ID, 0);

	/* handle the pending पूर्णांकerrupts */
	pcmuio_handle_पूर्णांकr_subdev(dev, s, val);

	वापस 1;
पूर्ण

अटल irqवापस_t pcmuio_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	पूर्णांक handled = 0;

	अगर (irq == dev->irq)
		handled += pcmuio_handle_asic_पूर्णांकerrupt(dev, 0);
	अगर (irq == devpriv->irq2)
		handled += pcmuio_handle_asic_पूर्णांकerrupt(dev, 1);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/* chip->spinlock is alपढ़ोy locked */
अटल व्योम pcmuio_start_पूर्णांकr(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक bits = 0;
	अचिन्हित पूर्णांक pol_bits = 0;
	पूर्णांक i;

	chip->enabled_mask = 0;
	chip->active = 1;
	अगर (cmd->chanlist) अणु
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक chanspec = cmd->chanlist[i];
			अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
			अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
			अचिन्हित पूर्णांक aref = CR_AREF(chanspec);

			bits |= (1 << chan);
			pol_bits |= ((aref || range) ? 1 : 0) << chan;
		पूर्ण
	पूर्ण
	bits &= ((1 << s->n_chan) - 1);
	chip->enabled_mask = bits;

	/* set pol and enab पूर्णांकrs क्रम this subdev.. */
	pcmuio_ग_लिखो(dev, pol_bits, asic, PCMUIO_PAGE_POL, 0);
	pcmuio_ग_लिखो(dev, bits, asic, PCMUIO_PAGE_ENAB, 0);
पूर्ण

अटल पूर्णांक pcmuio_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	अगर (chip->active)
		pcmuio_stop_पूर्णांकr(dev, s);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmuio_पूर्णांकtrig_start_पूर्णांकr(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	अचिन्हित दीर्घ flags;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	spin_lock_irqsave(&chip->spinlock, flags);
	s->async->पूर्णांकtrig = शून्य;
	अगर (chip->active)
		pcmuio_start_पूर्णांकr(dev, s);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 1;
पूर्ण

/*
 * 'do_cmd' function for an 'INTERRUPT' subdevice.
 */
अटल पूर्णांक pcmuio_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक asic = pcmuio_subdevice_to_asic(s);
	काष्ठा pcmuio_asic *chip = &devpriv->asics[asic];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	chip->active = 1;

	/* Set up start of acquisition. */
	अगर (cmd->start_src == TRIG_INT)
		s->async->पूर्णांकtrig = pcmuio_पूर्णांकtrig_start_पूर्णांकr;
	अन्यथा	/* TRIG_NOW */
		pcmuio_start_पूर्णांकr(dev, s);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmuio_cmdtest(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
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

	/* अगर (err) वापस 4; */

	वापस 0;
पूर्ण

अटल पूर्णांक pcmuio_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcmuio_board *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	काष्ठा pcmuio_निजी *devpriv;
	पूर्णांक ret;
	पूर्णांक i;

	ret = comedi_request_region(dev, it->options[0],
				    board->num_asics * PCMUIO_ASIC_IOSIZE);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	क्रम (i = 0; i < PCMUIO_MAX_ASICS; ++i) अणु
		काष्ठा pcmuio_asic *chip = &devpriv->asics[i];

		spin_lock_init(&chip->pagelock);
		spin_lock_init(&chip->spinlock);
	पूर्ण

	pcmuio_reset(dev);

	अगर (it->options[1]) अणु
		/* request the irq क्रम the 1st asic */
		ret = request_irq(it->options[1], pcmuio_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	अगर (board->num_asics == 2) अणु
		अगर (it->options[2] == dev->irq) अणु
			/* the same irq (or none) is used by both asics */
			devpriv->irq2 = it->options[2];
		पूर्ण अन्यथा अगर (it->options[2]) अणु
			/* request the irq क्रम the 2nd asic */
			ret = request_irq(it->options[2], pcmuio_पूर्णांकerrupt, 0,
					  dev->board_name, dev);
			अगर (ret == 0)
				devpriv->irq2 = it->options[2];
		पूर्ण
	पूर्ण

	ret = comedi_alloc_subdevices(dev, board->num_asics * 2);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dev->n_subdevices; ++i) अणु
		s = &dev->subdevices[i];
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
		s->n_chan	= 24;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcmuio_dio_insn_bits;
		s->insn_config	= pcmuio_dio_insn_config;

		/* subdevices 0 and 2 can support पूर्णांकerrupts */
		अगर ((i == 0 && dev->irq) || (i == 2 && devpriv->irq2)) अणु
			/* setup the पूर्णांकerrupt subdevice */
			dev->पढ़ो_subdev = s;
			s->subdev_flags	|= SDF_CMD_READ | SDF_LSAMPL |
					   SDF_PACKED;
			s->len_chanlist	= s->n_chan;
			s->cancel	= pcmuio_cancel;
			s->करो_cmd	= pcmuio_cmd;
			s->करो_cmdtest	= pcmuio_cmdtest;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcmuio_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcmuio_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		pcmuio_reset(dev);

		/* मुक्त the 2nd irq अगर used, the core will मुक्त the 1st one */
		अगर (devpriv->irq2 && devpriv->irq2 != dev->irq)
			मुक्त_irq(devpriv->irq2, dev);
	पूर्ण
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver pcmuio_driver = अणु
	.driver_name	= "pcmuio",
	.module		= THIS_MODULE,
	.attach		= pcmuio_attach,
	.detach		= pcmuio_detach,
	.board_name	= &pcmuio_boards[0].name,
	.offset		= माप(काष्ठा pcmuio_board),
	.num_names	= ARRAY_SIZE(pcmuio_boards),
पूर्ण;
module_comedi_driver(pcmuio_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
