<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pcmmio.c
 * Driver क्रम Winप्रणालीs PC-104 based multअगरunction IO board.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2007 Calin A. Culianu <calin@ajvar.org>
 */

/*
 * Driver: pcmmio
 * Description: A driver क्रम the PCM-MIO multअगरunction board
 * Devices: [Winप्रणालीs] PCM-MIO (pcmmio)
 * Author: Calin Culianu <calin@ajvar.org>
 * Updated: Wed, May 16 2007 16:21:10 -0500
 * Status: works
 *
 * A driver क्रम the PCM-MIO multअगरunction board from Winप्रणालीs. This
 * is a PC-104 based I/O board. It contains four subdevices:
 *
 *	subdevice 0 - 16 channels of 16-bit AI
 *	subdevice 1 - 8 channels of 16-bit AO
 *	subdevice 2 - first 24 channels of the 48 channel of DIO
 *			(with edge-triggered पूर्णांकerrupt support)
 *	subdevice 3 - last 24 channels of the 48 channel DIO
 *			(no पूर्णांकerrupt support क्रम this bank of channels)
 *
 * Some notes:
 *
 * Synchronous पढ़ोs and ग_लिखोs are the only things implemented क्रम analog
 * input and output. The hardware itself can करो streaming acquisition, etc.
 *
 * Asynchronous I/O क्रम the DIO subdevices *is* implemented, however! They
 * are basically edge-triggered पूर्णांकerrupts क्रम any configuration of the
 * channels in subdevice 2.
 *
 * Also note that this पूर्णांकerrupt support is untested.
 *
 * A few words about edge-detection IRQ support (commands on DIO):
 *
 * To use edge-detection IRQ support क्रम the DIO subdevice, pass the IRQ
 * of the board to the comedi_config command. The board IRQ is not jumpered
 * but rather configured through software, so any IRQ from 1-15 is OK.
 *
 * Due to the genericity of the comedi API, you need to create a special
 * comedi_command in order to use edge-triggered पूर्णांकerrupts क्रम DIO.
 *
 * Use comedi_commands with TRIG_NOW.  Your callback will be called each
 * समय an edge is detected on the specअगरied DIO line(s), and the data
 * values will be two sample_t's, which should be concatenated to क्रमm
 * one 32-bit अचिन्हित पूर्णांक. This value is the mask of channels that had
 * edges detected from your channel list. Note that the bits positions
 * in the mask correspond to positions in your chanlist when you
 * specअगरied the command and *not* channel id's!
 *
 * To set the polarity of the edge-detection पूर्णांकerrupts pass a nonzero value
 * क्रम either CR_RANGE or CR_AREF क्रम edge-up polarity, or a zero
 * value क्रम both CR_RANGE and CR_AREF अगर you want edge-करोwn polarity.
 *
 * Configuration Options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional -- क्रम edge-detect पूर्णांकerrupt support only,
 *		leave out अगर you करोn't need this feature)
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश "../comedidev.h"

/*
 * Register I/O map
 */
#घोषणा PCMMIO_AI_LSB_REG			0x00
#घोषणा PCMMIO_AI_MSB_REG			0x01
#घोषणा PCMMIO_AI_CMD_REG			0x02
#घोषणा PCMMIO_AI_CMD_SE			BIT(7)
#घोषणा PCMMIO_AI_CMD_ODD_CHAN			BIT(6)
#घोषणा PCMMIO_AI_CMD_CHAN_SEL(x)		(((x) & 0x3) << 4)
#घोषणा PCMMIO_AI_CMD_RANGE(x)			(((x) & 0x3) << 2)
#घोषणा PCMMIO_RESOURCE_REG			0x02
#घोषणा PCMMIO_RESOURCE_IRQ(x)			(((x) & 0xf) << 0)
#घोषणा PCMMIO_AI_STATUS_REG			0x03
#घोषणा PCMMIO_AI_STATUS_DATA_READY		BIT(7)
#घोषणा PCMMIO_AI_STATUS_DATA_DMA_PEND		BIT(6)
#घोषणा PCMMIO_AI_STATUS_CMD_DMA_PEND		BIT(5)
#घोषणा PCMMIO_AI_STATUS_IRQ_PEND		BIT(4)
#घोषणा PCMMIO_AI_STATUS_DATA_DRQ_ENA		BIT(2)
#घोषणा PCMMIO_AI_STATUS_REG_SEL		BIT(3)
#घोषणा PCMMIO_AI_STATUS_CMD_DRQ_ENA		BIT(1)
#घोषणा PCMMIO_AI_STATUS_IRQ_ENA		BIT(0)
#घोषणा PCMMIO_AI_RES_ENA_REG			0x03
#घोषणा PCMMIO_AI_RES_ENA_CMD_REG_ACCESS	(0 << 3)
#घोषणा PCMMIO_AI_RES_ENA_AI_RES_ACCESS		BIT(3)
#घोषणा PCMMIO_AI_RES_ENA_DIO_RES_ACCESS	BIT(4)
#घोषणा PCMMIO_AI_2ND_ADC_OFFSET		0x04

#घोषणा PCMMIO_AO_LSB_REG			0x08
#घोषणा PCMMIO_AO_LSB_SPAN(x)			(((x) & 0xf) << 0)
#घोषणा PCMMIO_AO_MSB_REG			0x09
#घोषणा PCMMIO_AO_CMD_REG			0x0a
#घोषणा PCMMIO_AO_CMD_WR_SPAN			(0x2 << 4)
#घोषणा PCMMIO_AO_CMD_WR_CODE			(0x3 << 4)
#घोषणा PCMMIO_AO_CMD_UPDATE			(0x4 << 4)
#घोषणा PCMMIO_AO_CMD_UPDATE_ALL		(0x5 << 4)
#घोषणा PCMMIO_AO_CMD_WR_SPAN_UPDATE		(0x6 << 4)
#घोषणा PCMMIO_AO_CMD_WR_CODE_UPDATE		(0x7 << 4)
#घोषणा PCMMIO_AO_CMD_WR_SPAN_UPDATE_ALL	(0x8 << 4)
#घोषणा PCMMIO_AO_CMD_WR_CODE_UPDATE_ALL	(0x9 << 4)
#घोषणा PCMMIO_AO_CMD_RD_B1_SPAN		(0xa << 4)
#घोषणा PCMMIO_AO_CMD_RD_B1_CODE		(0xb << 4)
#घोषणा PCMMIO_AO_CMD_RD_B2_SPAN		(0xc << 4)
#घोषणा PCMMIO_AO_CMD_RD_B2_CODE		(0xd << 4)
#घोषणा PCMMIO_AO_CMD_NOP			(0xf << 4)
#घोषणा PCMMIO_AO_CMD_CHAN_SEL(x)		(((x) & 0x03) << 1)
#घोषणा PCMMIO_AO_CMD_CHAN_SEL_ALL		(0x0f << 0)
#घोषणा PCMMIO_AO_STATUS_REG			0x0b
#घोषणा PCMMIO_AO_STATUS_DATA_READY		BIT(7)
#घोषणा PCMMIO_AO_STATUS_DATA_DMA_PEND		BIT(6)
#घोषणा PCMMIO_AO_STATUS_CMD_DMA_PEND		BIT(5)
#घोषणा PCMMIO_AO_STATUS_IRQ_PEND		BIT(4)
#घोषणा PCMMIO_AO_STATUS_DATA_DRQ_ENA		BIT(2)
#घोषणा PCMMIO_AO_STATUS_REG_SEL		BIT(3)
#घोषणा PCMMIO_AO_STATUS_CMD_DRQ_ENA		BIT(1)
#घोषणा PCMMIO_AO_STATUS_IRQ_ENA		BIT(0)
#घोषणा PCMMIO_AO_RESOURCE_ENA_REG		0x0b
#घोषणा PCMMIO_AO_2ND_DAC_OFFSET		0x04

/*
 * WinSystems WS16C48
 *
 * Offset    Page 0       Page 1       Page 2       Page 3
 * ------  -----------  -----------  -----------  -----------
 *  0x10   Port 0 I/O   Port 0 I/O   Port 0 I/O   Port 0 I/O
 *  0x11   Port 1 I/O   Port 1 I/O   Port 1 I/O   Port 1 I/O
 *  0x12   Port 2 I/O   Port 2 I/O   Port 2 I/O   Port 2 I/O
 *  0x13   Port 3 I/O   Port 3 I/O   Port 3 I/O   Port 3 I/O
 *  0x14   Port 4 I/O   Port 4 I/O   Port 4 I/O   Port 4 I/O
 *  0x15   Port 5 I/O   Port 5 I/O   Port 5 I/O   Port 5 I/O
 *  0x16   INT_PENDING  INT_PENDING  INT_PENDING  INT_PENDING
 *  0x17    Page/Lock    Page/Lock    Page/Lock    Page/Lock
 *  0x18       N/A         POL_0       ENAB_0       INT_ID0
 *  0x19       N/A         POL_1       ENAB_1       INT_ID1
 *  0x1a       N/A         POL_2       ENAB_2       INT_ID2
 */
#घोषणा PCMMIO_PORT_REG(x)			(0x10 + (x))
#घोषणा PCMMIO_INT_PENDING_REG			0x16
#घोषणा PCMMIO_PAGE_LOCK_REG			0x17
#घोषणा PCMMIO_LOCK_PORT(x)			((1 << (x)) & 0x3f)
#घोषणा PCMMIO_PAGE(x)				(((x) & 0x3) << 6)
#घोषणा PCMMIO_PAGE_MASK			PCMUIO_PAGE(3)
#घोषणा PCMMIO_PAGE_POL				1
#घोषणा PCMMIO_PAGE_ENAB			2
#घोषणा PCMMIO_PAGE_INT_ID			3
#घोषणा PCMMIO_PAGE_REG(x)			(0x18 + (x))

अटल स्थिर काष्ठा comedi_lrange pcmmio_ai_ranges = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange pcmmio_ao_ranges = अणु
	6, अणु
		UNI_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(10),
		BIP_RANGE(2.5),
		RANGE(-2.5, 7.5)
	पूर्ण
पूर्ण;

काष्ठा pcmmio_निजी अणु
	spinlock_t pagelock;	/* protects the page रेजिस्टरs */
	spinlock_t spinlock;	/* protects the member variables */
	अचिन्हित पूर्णांक enabled_mask;
	अचिन्हित पूर्णांक active:1;
पूर्ण;

अटल व्योम pcmmio_dio_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक val,
			     पूर्णांक page, पूर्णांक port)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ iobase = dev->iobase;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->pagelock, flags);
	अगर (page == 0) अणु
		/* Port रेजिस्टरs are valid क्रम any page */
		outb(val & 0xff, iobase + PCMMIO_PORT_REG(port + 0));
		outb((val >> 8) & 0xff, iobase + PCMMIO_PORT_REG(port + 1));
		outb((val >> 16) & 0xff, iobase + PCMMIO_PORT_REG(port + 2));
	पूर्ण अन्यथा अणु
		outb(PCMMIO_PAGE(page), iobase + PCMMIO_PAGE_LOCK_REG);
		outb(val & 0xff, iobase + PCMMIO_PAGE_REG(0));
		outb((val >> 8) & 0xff, iobase + PCMMIO_PAGE_REG(1));
		outb((val >> 16) & 0xff, iobase + PCMMIO_PAGE_REG(2));
	पूर्ण
	spin_unlock_irqrestore(&devpriv->pagelock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक pcmmio_dio_पढ़ो(काष्ठा comedi_device *dev,
				    पूर्णांक page, पूर्णांक port)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ iobase = dev->iobase;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&devpriv->pagelock, flags);
	अगर (page == 0) अणु
		/* Port रेजिस्टरs are valid क्रम any page */
		val = inb(iobase + PCMMIO_PORT_REG(port + 0));
		val |= (inb(iobase + PCMMIO_PORT_REG(port + 1)) << 8);
		val |= (inb(iobase + PCMMIO_PORT_REG(port + 2)) << 16);
	पूर्ण अन्यथा अणु
		outb(PCMMIO_PAGE(page), iobase + PCMMIO_PAGE_LOCK_REG);
		val = inb(iobase + PCMMIO_PAGE_REG(0));
		val |= (inb(iobase + PCMMIO_PAGE_REG(1)) << 8);
		val |= (inb(iobase + PCMMIO_PAGE_REG(2)) << 16);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->pagelock, flags);

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
अटल पूर्णांक pcmmio_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	/* subdevice 2 uses ports 0-2, subdevice 3 uses ports 3-5 */
	पूर्णांक port = s->index == 2 ? 0 : 3;
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
		pcmmio_dio_ग_लिखो(dev, val, 0, port);
	पूर्ण

	/* get inverted state of the channels from the port */
	val = pcmmio_dio_पढ़ो(dev, 0, port);

	/* वापस the true state of the channels */
	data[1] = ~val & chanmask;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcmmio_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	/* subdevice 2 uses ports 0-2, subdevice 3 uses ports 3-5 */
	पूर्णांक port = s->index == 2 ? 0 : 3;
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	अगर (data[0] == INSN_CONFIG_DIO_INPUT)
		pcmmio_dio_ग_लिखो(dev, s->io_bits, 0, port);

	वापस insn->n;
पूर्ण

अटल व्योम pcmmio_reset(काष्ठा comedi_device *dev)
अणु
	/* Clear all the DIO port bits */
	pcmmio_dio_ग_लिखो(dev, 0, 0, 0);
	pcmmio_dio_ग_लिखो(dev, 0, 0, 3);

	/* Clear all the paged रेजिस्टरs */
	pcmmio_dio_ग_लिखो(dev, 0, PCMMIO_PAGE_POL, 0);
	pcmmio_dio_ग_लिखो(dev, 0, PCMMIO_PAGE_ENAB, 0);
	pcmmio_dio_ग_लिखो(dev, 0, PCMMIO_PAGE_INT_ID, 0);
पूर्ण

/* devpriv->spinlock is alपढ़ोy locked */
अटल व्योम pcmmio_stop_पूर्णांकr(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;

	devpriv->enabled_mask = 0;
	devpriv->active = 0;
	s->async->पूर्णांकtrig = शून्य;

	/* disable all dio पूर्णांकerrupts */
	pcmmio_dio_ग_लिखो(dev, 0, PCMMIO_PAGE_ENAB, 0);
पूर्ण

अटल व्योम pcmmio_handle_dio_पूर्णांकr(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक triggered)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&devpriv->spinlock, flags);

	अगर (!devpriv->active)
		जाओ करोne;

	अगर (!(triggered & devpriv->enabled_mask))
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
	spin_unlock_irqrestore(&devpriv->spinlock, flags);

	comedi_handle_events(dev, s);
पूर्ण

अटल irqवापस_t पूर्णांकerrupt_pcmmio(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक triggered;
	अचिन्हित अक्षर पूर्णांक_pend;

	/* are there any पूर्णांकerrupts pending */
	पूर्णांक_pend = inb(dev->iobase + PCMMIO_INT_PENDING_REG) & 0x07;
	अगर (!पूर्णांक_pend)
		वापस IRQ_NONE;

	/* get, and clear, the pending पूर्णांकerrupts */
	triggered = pcmmio_dio_पढ़ो(dev, PCMMIO_PAGE_INT_ID, 0);
	pcmmio_dio_ग_लिखो(dev, 0, PCMMIO_PAGE_INT_ID, 0);

	pcmmio_handle_dio_पूर्णांकr(dev, s, triggered);

	वापस IRQ_HANDLED;
पूर्ण

/* devpriv->spinlock is alपढ़ोy locked */
अटल व्योम pcmmio_start_पूर्णांकr(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक bits = 0;
	अचिन्हित पूर्णांक pol_bits = 0;
	पूर्णांक i;

	devpriv->enabled_mask = 0;
	devpriv->active = 1;
	अगर (cmd->chanlist) अणु
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक chanspec = cmd->chanlist[i];
			अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
			अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
			अचिन्हित पूर्णांक aref = CR_AREF(chanspec);

			bits |= (1 << chan);
			pol_bits |= (((aref || range) ? 1 : 0) << chan);
		पूर्ण
	पूर्ण
	bits &= ((1 << s->n_chan) - 1);
	devpriv->enabled_mask = bits;

	/* set polarity and enable पूर्णांकerrupts */
	pcmmio_dio_ग_लिखो(dev, pol_bits, PCMMIO_PAGE_POL, 0);
	pcmmio_dio_ग_लिखो(dev, bits, PCMMIO_PAGE_ENAB, 0);
पूर्ण

अटल पूर्णांक pcmmio_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->spinlock, flags);
	अगर (devpriv->active)
		pcmmio_stop_पूर्णांकr(dev, s);
	spin_unlock_irqrestore(&devpriv->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmmio_पूर्णांकtrig_start_पूर्णांकr(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित दीर्घ flags;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	spin_lock_irqsave(&devpriv->spinlock, flags);
	s->async->पूर्णांकtrig = शून्य;
	अगर (devpriv->active)
		pcmmio_start_पूर्णांकr(dev, s);
	spin_unlock_irqrestore(&devpriv->spinlock, flags);

	वापस 1;
पूर्ण

/*
 * 'do_cmd' function for an 'INTERRUPT' subdevice.
 */
अटल पूर्णांक pcmmio_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcmmio_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->spinlock, flags);
	devpriv->active = 1;

	/* Set up start of acquisition. */
	अगर (cmd->start_src == TRIG_INT)
		s->async->पूर्णांकtrig = pcmmio_पूर्णांकtrig_start_पूर्णांकr;
	अन्यथा	/* TRIG_NOW */
		pcmmio_start_पूर्णांकr(dev, s);

	spin_unlock_irqrestore(&devpriv->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmmio_cmdtest(काष्ठा comedi_device *dev,
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

अटल पूर्णांक pcmmio_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + PCMMIO_AI_STATUS_REG);
	अगर (status & PCMMIO_AI_STATUS_DATA_READY)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pcmmio_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ iobase = dev->iobase;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	अचिन्हित अक्षर cmd = 0;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * The PCM-MIO uses two Linear Tech LTC1859CG 8-channel A/D converters.
	 * The devices use a full duplex serial पूर्णांकerface which transmits and
	 * receives data simultaneously. An 8-bit command is shअगरted पूर्णांकo the
	 * ADC पूर्णांकerface to configure it क्रम the next conversion. At the same
	 * समय, the data from the previous conversion is shअगरted out of the
	 * device. Consequently, the conversion result is delayed by one
	 * conversion from the command word.
	 *
	 * Setup the cmd क्रम the conversions then करो a dummy conversion to
	 * flush the junk data. Then करो each conversion requested by the
	 * comedi_insn. Note that the last conversion will leave junk data
	 * in ADC which will get flushed on the next comedi_insn.
	 */

	अगर (chan > 7) अणु
		chan -= 8;
		iobase += PCMMIO_AI_2ND_ADC_OFFSET;
	पूर्ण

	अगर (aref == AREF_GROUND)
		cmd |= PCMMIO_AI_CMD_SE;
	अगर (chan % 2)
		cmd |= PCMMIO_AI_CMD_ODD_CHAN;
	cmd |= PCMMIO_AI_CMD_CHAN_SEL(chan / 2);
	cmd |= PCMMIO_AI_CMD_RANGE(range);

	outb(cmd, iobase + PCMMIO_AI_CMD_REG);

	ret = comedi_समयout(dev, s, insn, pcmmio_ai_eoc, 0);
	अगर (ret)
		वापस ret;

	val = inb(iobase + PCMMIO_AI_LSB_REG);
	val |= inb(iobase + PCMMIO_AI_MSB_REG) << 8;

	क्रम (i = 0; i < insn->n; i++) अणु
		outb(cmd, iobase + PCMMIO_AI_CMD_REG);

		ret = comedi_समयout(dev, s, insn, pcmmio_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inb(iobase + PCMMIO_AI_LSB_REG);
		val |= inb(iobase + PCMMIO_AI_MSB_REG) << 8;

		/* bipolar data is two's complement */
		अगर (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcmmio_ao_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + PCMMIO_AO_STATUS_REG);
	अगर (status & PCMMIO_AO_STATUS_DATA_READY)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pcmmio_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ iobase = dev->iobase;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित अक्षर cmd = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * The PCM-MIO has two Linear Tech LTC2704 DAC devices. Each device
	 * is a 4-channel converter with software-selectable output range.
	 */

	अगर (chan > 3) अणु
		cmd |= PCMMIO_AO_CMD_CHAN_SEL(chan - 4);
		iobase += PCMMIO_AO_2ND_DAC_OFFSET;
	पूर्ण अन्यथा अणु
		cmd |= PCMMIO_AO_CMD_CHAN_SEL(chan);
	पूर्ण

	/* set the range क्रम the channel */
	outb(PCMMIO_AO_LSB_SPAN(range), iobase + PCMMIO_AO_LSB_REG);
	outb(0, iobase + PCMMIO_AO_MSB_REG);
	outb(cmd | PCMMIO_AO_CMD_WR_SPAN_UPDATE, iobase + PCMMIO_AO_CMD_REG);

	ret = comedi_समयout(dev, s, insn, pcmmio_ao_eoc, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		/* ग_लिखो the data to the channel */
		outb(val & 0xff, iobase + PCMMIO_AO_LSB_REG);
		outb((val >> 8) & 0xff, iobase + PCMMIO_AO_MSB_REG);
		outb(cmd | PCMMIO_AO_CMD_WR_CODE_UPDATE,
		     iobase + PCMMIO_AO_CMD_REG);

		ret = comedi_समयout(dev, s, insn, pcmmio_ao_eoc, 0);
		अगर (ret)
			वापस ret;

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcmmio_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा pcmmio_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 32);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	spin_lock_init(&devpriv->pagelock);
	spin_lock_init(&devpriv->spinlock);

	pcmmio_reset(dev);

	अगर (it->options[1]) अणु
		ret = request_irq(it->options[1], पूर्णांकerrupt_pcmmio, 0,
				  dev->board_name, dev);
		अगर (ret == 0) अणु
			dev->irq = it->options[1];

			/* configure the पूर्णांकerrupt routing on the board */
			outb(PCMMIO_AI_RES_ENA_DIO_RES_ACCESS,
			     dev->iobase + PCMMIO_AI_RES_ENA_REG);
			outb(PCMMIO_RESOURCE_IRQ(dev->irq),
			     dev->iobase + PCMMIO_RESOURCE_REG);
		पूर्ण
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0xffff;
	s->range_table	= &pcmmio_ai_ranges;
	s->insn_पढ़ो	= pcmmio_ai_insn_पढ़ो;

	/* initialize the resource enable रेजिस्टर by clearing it */
	outb(PCMMIO_AI_RES_ENA_CMD_REG_ACCESS,
	     dev->iobase + PCMMIO_AI_RES_ENA_REG);
	outb(PCMMIO_AI_RES_ENA_CMD_REG_ACCESS,
	     dev->iobase + PCMMIO_AI_RES_ENA_REG + PCMMIO_AI_2ND_ADC_OFFSET);

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 0xffff;
	s->range_table	= &pcmmio_ao_ranges;
	s->insn_ग_लिखो	= pcmmio_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* initialize the resource enable रेजिस्टर by clearing it */
	outb(0, dev->iobase + PCMMIO_AO_RESOURCE_ENA_REG);
	outb(0, dev->iobase + PCMMIO_AO_2ND_DAC_OFFSET +
		PCMMIO_AO_RESOURCE_ENA_REG);

	/* Digital I/O subdevice with पूर्णांकerrupt support */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->len_chanlist	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcmmio_dio_insn_bits;
	s->insn_config	= pcmmio_dio_insn_config;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ | SDF_LSAMPL | SDF_PACKED;
		s->len_chanlist	= s->n_chan;
		s->cancel	= pcmmio_cancel;
		s->करो_cmd	= pcmmio_cmd;
		s->करो_cmdtest	= pcmmio_cmdtest;
	पूर्ण

	/* Digital I/O subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcmmio_dio_insn_bits;
	s->insn_config	= pcmmio_dio_insn_config;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcmmio_driver = अणु
	.driver_name	= "pcmmio",
	.module		= THIS_MODULE,
	.attach		= pcmmio_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(pcmmio_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Winsystems PCM-MIO PC/104 board");
MODULE_LICENSE("GPL");
