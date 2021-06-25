<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * ipoctal.c
 *
 * driver क्रम the GE IP-OCTAL boards
 *
 * Copyright (C) 2009-2012 CERN (www.cern.ch)
 * Author: Nicolas Serafini, EIC2 SA
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/ipack.h>
#समावेश "ipoctal.h"
#समावेश "scc2698.h"

#घोषणा IP_OCTAL_ID_SPACE_VECTOR    0x41
#घोषणा IP_OCTAL_NB_BLOCKS          4

अटल स्थिर काष्ठा tty_operations ipoctal_fops;

काष्ठा ipoctal_channel अणु
	काष्ठा ipoctal_stats		stats;
	अचिन्हित पूर्णांक			nb_bytes;
	रुको_queue_head_t		queue;
	spinlock_t			lock;
	अचिन्हित पूर्णांक			poपूर्णांकer_पढ़ो;
	अचिन्हित पूर्णांक			poपूर्णांकer_ग_लिखो;
	काष्ठा tty_port			tty_port;
	जोड़ scc2698_channel __iomem	*regs;
	जोड़ scc2698_block __iomem	*block_regs;
	अचिन्हित पूर्णांक			board_id;
	u8				isr_rx_rdy_mask;
	u8				isr_tx_rdy_mask;
	अचिन्हित पूर्णांक			rx_enable;
पूर्ण;

काष्ठा ipoctal अणु
	काष्ठा ipack_device		*dev;
	अचिन्हित पूर्णांक			board_id;
	काष्ठा ipoctal_channel		channel[NR_CHANNELS];
	काष्ठा tty_driver		*tty_drv;
	u8 __iomem			*mem8_space;
	u8 __iomem			*पूर्णांक_space;
पूर्ण;

अटल अंतरभूत काष्ठा ipoctal *chan_to_ipoctal(काष्ठा ipoctal_channel *chan,
					      अचिन्हित पूर्णांक index)
अणु
	वापस container_of(chan, काष्ठा ipoctal, channel[index]);
पूर्ण

अटल व्योम ipoctal_reset_channel(काष्ठा ipoctal_channel *channel)
अणु
	ioग_लिखो8(CR_DISABLE_RX | CR_DISABLE_TX, &channel->regs->w.cr);
	channel->rx_enable = 0;
	ioग_लिखो8(CR_CMD_RESET_RX, &channel->regs->w.cr);
	ioग_लिखो8(CR_CMD_RESET_TX, &channel->regs->w.cr);
	ioग_लिखो8(CR_CMD_RESET_ERR_STATUS, &channel->regs->w.cr);
	ioग_लिखो8(CR_CMD_RESET_MR, &channel->regs->w.cr);
पूर्ण

अटल पूर्णांक ipoctal_port_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ipoctal_channel *channel;

	channel = dev_get_drvdata(tty->dev);

	/*
	 * Enable RX. TX will be enabled when
	 * there is something to send
	 */
	ioग_लिखो8(CR_ENABLE_RX, &channel->regs->w.cr);
	channel->rx_enable = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ipoctal_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा ipoctal_channel *channel = dev_get_drvdata(tty->dev);
	काष्ठा ipoctal *ipoctal = chan_to_ipoctal(channel, tty->index);
	पूर्णांक err;

	tty->driver_data = channel;

	अगर (!ipack_get_carrier(ipoctal->dev))
		वापस -EBUSY;

	err = tty_port_खोलो(&channel->tty_port, tty, file);
	अगर (err)
		ipack_put_carrier(ipoctal->dev);

	वापस err;
पूर्ण

अटल व्योम ipoctal_reset_stats(काष्ठा ipoctal_stats *stats)
अणु
	stats->tx = 0;
	stats->rx = 0;
	stats->rcv_अवरोध = 0;
	stats->framing_err = 0;
	stats->overrun_err = 0;
	stats->parity_err = 0;
पूर्ण

अटल व्योम ipoctal_मुक्त_channel(काष्ठा ipoctal_channel *channel)
अणु
	ipoctal_reset_stats(&channel->stats);
	channel->poपूर्णांकer_पढ़ो = 0;
	channel->poपूर्णांकer_ग_लिखो = 0;
	channel->nb_bytes = 0;
पूर्ण

अटल व्योम ipoctal_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;

	tty_port_बंद(&channel->tty_port, tty, filp);
	ipoctal_मुक्त_channel(channel);
पूर्ण

अटल पूर्णांक ipoctal_get_icount(काष्ठा tty_काष्ठा *tty,
			      काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;

	icount->cts = 0;
	icount->dsr = 0;
	icount->rng = 0;
	icount->dcd = 0;
	icount->rx = channel->stats.rx;
	icount->tx = channel->stats.tx;
	icount->frame = channel->stats.framing_err;
	icount->parity = channel->stats.parity_err;
	icount->brk = channel->stats.rcv_अवरोध;
	वापस 0;
पूर्ण

अटल व्योम ipoctal_irq_rx(काष्ठा ipoctal_channel *channel, u8 sr)
अणु
	काष्ठा tty_port *port = &channel->tty_port;
	अचिन्हित अक्षर value;
	अचिन्हित अक्षर flag;
	u8 isr;

	करो अणु
		value = ioपढ़ो8(&channel->regs->r.rhr);
		flag = TTY_NORMAL;
		/* Error: count statistics */
		अगर (sr & SR_ERROR) अणु
			ioग_लिखो8(CR_CMD_RESET_ERR_STATUS, &channel->regs->w.cr);

			अगर (sr & SR_OVERRUN_ERROR) अणु
				channel->stats.overrun_err++;
				/* Overrun करोesn't affect the current अक्षरacter*/
				tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
			पूर्ण
			अगर (sr & SR_PARITY_ERROR) अणु
				channel->stats.parity_err++;
				flag = TTY_PARITY;
			पूर्ण
			अगर (sr & SR_FRAMING_ERROR) अणु
				channel->stats.framing_err++;
				flag = TTY_FRAME;
			पूर्ण
			अगर (sr & SR_RECEIVED_BREAK) अणु
				channel->stats.rcv_अवरोध++;
				flag = TTY_BREAK;
			पूर्ण
		पूर्ण
		tty_insert_flip_अक्षर(port, value, flag);

		/* Check अगर there are more अक्षरacters in RX FIFO
		 * If there are more, the isr रेजिस्टर क्रम this channel
		 * has enabled the RxRDY|FFULL bit.
		 */
		isr = ioपढ़ो8(&channel->block_regs->r.isr);
		sr = ioपढ़ो8(&channel->regs->r.sr);
	पूर्ण जबतक (isr & channel->isr_rx_rdy_mask);

	tty_flip_buffer_push(port);
पूर्ण

अटल व्योम ipoctal_irq_tx(काष्ठा ipoctal_channel *channel)
अणु
	अचिन्हित अक्षर value;
	अचिन्हित पूर्णांक *poपूर्णांकer_ग_लिखो = &channel->poपूर्णांकer_ग_लिखो;

	अगर (channel->nb_bytes == 0)
		वापस;

	spin_lock(&channel->lock);
	value = channel->tty_port.xmit_buf[*poपूर्णांकer_ग_लिखो];
	ioग_लिखो8(value, &channel->regs->w.thr);
	channel->stats.tx++;
	(*poपूर्णांकer_ग_लिखो)++;
	*poपूर्णांकer_ग_लिखो = *poपूर्णांकer_ग_लिखो % PAGE_SIZE;
	channel->nb_bytes--;
	spin_unlock(&channel->lock);
पूर्ण

अटल व्योम ipoctal_irq_channel(काष्ठा ipoctal_channel *channel)
अणु
	u8 isr, sr;

	/* The HW is organized in pair of channels.  See which रेजिस्टर we need
	 * to पढ़ो from */
	isr = ioपढ़ो8(&channel->block_regs->r.isr);
	sr = ioपढ़ो8(&channel->regs->r.sr);

	अगर (isr & (IMR_DELTA_BREAK_A | IMR_DELTA_BREAK_B))
		ioग_लिखो8(CR_CMD_RESET_BREAK_CHANGE, &channel->regs->w.cr);

	अगर ((sr & SR_TX_EMPTY) && (channel->nb_bytes == 0)) अणु
		ioग_लिखो8(CR_DISABLE_TX, &channel->regs->w.cr);
		/* In हाल of RS-485, change from TX to RX when finishing TX.
		 * Half-duplex. */
		अगर (channel->board_id == IPACK1_DEVICE_ID_SBS_OCTAL_485) अणु
			ioग_लिखो8(CR_CMD_NEGATE_RTSN, &channel->regs->w.cr);
			ioग_लिखो8(CR_ENABLE_RX, &channel->regs->w.cr);
			channel->rx_enable = 1;
		पूर्ण
	पूर्ण

	/* RX data */
	अगर ((isr & channel->isr_rx_rdy_mask) && (sr & SR_RX_READY))
		ipoctal_irq_rx(channel, sr);

	/* TX of each अक्षरacter */
	अगर ((isr & channel->isr_tx_rdy_mask) && (sr & SR_TX_READY))
		ipoctal_irq_tx(channel);
पूर्ण

अटल irqवापस_t ipoctal_irq_handler(व्योम *arg)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ipoctal *ipoctal = (काष्ठा ipoctal *) arg;

	/* Clear the IPack device पूर्णांकerrupt */
	पढ़ोw(ipoctal->पूर्णांक_space + ACK_INT_REQ0);
	पढ़ोw(ipoctal->पूर्णांक_space + ACK_INT_REQ1);

	/* Check all channels */
	क्रम (i = 0; i < NR_CHANNELS; i++)
		ipoctal_irq_channel(&ipoctal->channel[i]);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा tty_port_operations ipoctal_tty_port_ops = अणु
	.dtr_rts = शून्य,
	.activate = ipoctal_port_activate,
पूर्ण;

अटल पूर्णांक ipoctal_inst_slot(काष्ठा ipoctal *ipoctal, अचिन्हित पूर्णांक bus_nr,
			     अचिन्हित पूर्णांक slot)
अणु
	पूर्णांक res;
	पूर्णांक i;
	काष्ठा tty_driver *tty;
	अक्षर name[20];
	काष्ठा ipoctal_channel *channel;
	काष्ठा ipack_region *region;
	व्योम __iomem *addr;
	जोड़ scc2698_channel __iomem *chan_regs;
	जोड़ scc2698_block __iomem *block_regs;

	ipoctal->board_id = ipoctal->dev->id_device;

	region = &ipoctal->dev->region[IPACK_IO_SPACE];
	addr = devm_ioremap(&ipoctal->dev->dev,
				    region->start, region->size);
	अगर (!addr) अणु
		dev_err(&ipoctal->dev->dev,
			"Unable to map slot [%d:%d] IO space!\n",
			bus_nr, slot);
		वापस -EADDRNOTAVAIL;
	पूर्ण
	/* Save the भव address to access the रेजिस्टरs easily */
	chan_regs =
		(जोड़ scc2698_channel __iomem *) addr;
	block_regs =
		(जोड़ scc2698_block __iomem *) addr;

	region = &ipoctal->dev->region[IPACK_INT_SPACE];
	ipoctal->पूर्णांक_space =
		devm_ioremap(&ipoctal->dev->dev,
				     region->start, region->size);
	अगर (!ipoctal->पूर्णांक_space) अणु
		dev_err(&ipoctal->dev->dev,
			"Unable to map slot [%d:%d] INT space!\n",
			bus_nr, slot);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	region = &ipoctal->dev->region[IPACK_MEM8_SPACE];
	ipoctal->mem8_space =
		devm_ioremap(&ipoctal->dev->dev,
				     region->start, 0x8000);
	अगर (!ipoctal->mem8_space) अणु
		dev_err(&ipoctal->dev->dev,
			"Unable to map slot [%d:%d] MEM8 space!\n",
			bus_nr, slot);
		वापस -EADDRNOTAVAIL;
	पूर्ण


	/* Disable RX and TX beक्रमe touching anything */
	क्रम (i = 0; i < NR_CHANNELS ; i++) अणु
		काष्ठा ipoctal_channel *channel = &ipoctal->channel[i];
		channel->regs = chan_regs + i;
		channel->block_regs = block_regs + (i >> 1);
		channel->board_id = ipoctal->board_id;
		अगर (i & 1) अणु
			channel->isr_tx_rdy_mask = ISR_TxRDY_B;
			channel->isr_rx_rdy_mask = ISR_RxRDY_FFULL_B;
		पूर्ण अन्यथा अणु
			channel->isr_tx_rdy_mask = ISR_TxRDY_A;
			channel->isr_rx_rdy_mask = ISR_RxRDY_FFULL_A;
		पूर्ण

		ipoctal_reset_channel(channel);
		ioग_लिखो8(MR1_CHRL_8_BITS | MR1_ERROR_CHAR | MR1_RxINT_RxRDY,
			 &channel->regs->w.mr); /* mr1 */
		ioग_लिखो8(0, &channel->regs->w.mr); /* mr2 */
		ioग_लिखो8(TX_CLK_9600  | RX_CLK_9600, &channel->regs->w.csr);
	पूर्ण

	क्रम (i = 0; i < IP_OCTAL_NB_BLOCKS; i++) अणु
		ioग_लिखो8(ACR_BRG_SET2, &block_regs[i].w.acr);
		ioग_लिखो8(OPCR_MPP_OUTPUT | OPCR_MPOa_RTSN | OPCR_MPOb_RTSN,
			 &block_regs[i].w.opcr);
		ioग_लिखो8(IMR_TxRDY_A | IMR_RxRDY_FFULL_A | IMR_DELTA_BREAK_A |
			 IMR_TxRDY_B | IMR_RxRDY_FFULL_B | IMR_DELTA_BREAK_B,
			 &block_regs[i].w.imr);
	पूर्ण

	/* Dummy ग_लिखो */
	ioग_लिखो8(1, ipoctal->mem8_space + 1);

	/* Register the TTY device */

	/* Each IP-OCTAL channel is a TTY port */
	tty = alloc_tty_driver(NR_CHANNELS);

	अगर (!tty)
		वापस -ENOMEM;

	/* Fill काष्ठा tty_driver with ipoctal data */
	tty->owner = THIS_MODULE;
	tty->driver_name = KBUILD_MODNAME;
	प्र_लिखो(name, KBUILD_MODNAME ".%d.%d.", bus_nr, slot);
	tty->name = name;
	tty->major = 0;

	tty->minor_start = 0;
	tty->type = TTY_DRIVER_TYPE_SERIAL;
	tty->subtype = SERIAL_TYPE_NORMAL;
	tty->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty->init_termios = tty_std_termios;
	tty->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	tty->init_termios.c_ispeed = 9600;
	tty->init_termios.c_ospeed = 9600;

	tty_set_operations(tty, &ipoctal_fops);
	res = tty_रेजिस्टर_driver(tty);
	अगर (res) अणु
		dev_err(&ipoctal->dev->dev, "Can't register tty driver.\n");
		put_tty_driver(tty);
		वापस res;
	पूर्ण

	/* Save काष्ठा tty_driver क्रम use it when uninstalling the device */
	ipoctal->tty_drv = tty;

	क्रम (i = 0; i < NR_CHANNELS; i++) अणु
		काष्ठा device *tty_dev;

		channel = &ipoctal->channel[i];
		tty_port_init(&channel->tty_port);
		tty_port_alloc_xmit_buf(&channel->tty_port);
		channel->tty_port.ops = &ipoctal_tty_port_ops;

		ipoctal_reset_stats(&channel->stats);
		channel->nb_bytes = 0;
		spin_lock_init(&channel->lock);
		channel->poपूर्णांकer_पढ़ो = 0;
		channel->poपूर्णांकer_ग_लिखो = 0;
		tty_dev = tty_port_रेजिस्टर_device(&channel->tty_port, tty, i, शून्य);
		अगर (IS_ERR(tty_dev)) अणु
			dev_err(&ipoctal->dev->dev, "Failed to register tty device.\n");
			tty_port_destroy(&channel->tty_port);
			जारी;
		पूर्ण
		dev_set_drvdata(tty_dev, channel);
	पूर्ण

	/*
	 * IP-OCTAL has dअगरferent addresses to copy its IRQ vector.
	 * Depending of the carrier these addresses are accesible or not.
	 * More info in the datasheet.
	 */
	ipoctal->dev->bus->ops->request_irq(ipoctal->dev,
				       ipoctal_irq_handler, ipoctal);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ipoctal_copy_ग_लिखो_buffer(काष्ठा ipoctal_channel *channel,
					    स्थिर अचिन्हित अक्षर *buf,
					    पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	अचिन्हित पूर्णांक *poपूर्णांकer_पढ़ो = &channel->poपूर्णांकer_पढ़ो;

	/* Copy the bytes from the user buffer to the पूर्णांकernal one */
	क्रम (i = 0; i < count; i++) अणु
		अगर (i <= (PAGE_SIZE - channel->nb_bytes)) अणु
			spin_lock_irqsave(&channel->lock, flags);
			channel->tty_port.xmit_buf[*poपूर्णांकer_पढ़ो] = buf[i];
			*poपूर्णांकer_पढ़ो = (*poपूर्णांकer_पढ़ो + 1) % PAGE_SIZE;
			channel->nb_bytes++;
			spin_unlock_irqrestore(&channel->lock, flags);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक ipoctal_ग_लिखो_tty(काष्ठा tty_काष्ठा *tty,
			     स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;
	अचिन्हित पूर्णांक अक्षर_copied;

	अक्षर_copied = ipoctal_copy_ग_लिखो_buffer(channel, buf, count);

	/* As the IP-OCTAL 485 only supports half duplex, करो it manually */
	अगर (channel->board_id == IPACK1_DEVICE_ID_SBS_OCTAL_485) अणु
		ioग_लिखो8(CR_DISABLE_RX, &channel->regs->w.cr);
		channel->rx_enable = 0;
		ioग_लिखो8(CR_CMD_ASSERT_RTSN, &channel->regs->w.cr);
	पूर्ण

	/*
	 * Send a packet and then disable TX to aव्योम failure after several send
	 * operations
	 */
	ioग_लिखो8(CR_ENABLE_TX, &channel->regs->w.cr);
	वापस अक्षर_copied;
पूर्ण

अटल पूर्णांक ipoctal_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;

	वापस PAGE_SIZE - channel->nb_bytes;
पूर्ण

अटल पूर्णांक ipoctal_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;

	वापस channel->nb_bytes;
पूर्ण

अटल व्योम ipoctal_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा ktermios *old_termios)
अणु
	अचिन्हित पूर्णांक cflag;
	अचिन्हित अक्षर mr1 = 0;
	अचिन्हित अक्षर mr2 = 0;
	अचिन्हित अक्षर csr = 0;
	काष्ठा ipoctal_channel *channel = tty->driver_data;
	speed_t baud;

	cflag = tty->termios.c_cflag;

	/* Disable and reset everything beक्रमe change the setup */
	ipoctal_reset_channel(channel);

	/* Set Bits per अक्षरs */
	चयन (cflag & CSIZE) अणु
	हाल CS6:
		mr1 |= MR1_CHRL_6_BITS;
		अवरोध;
	हाल CS7:
		mr1 |= MR1_CHRL_7_BITS;
		अवरोध;
	हाल CS8:
	शेष:
		mr1 |= MR1_CHRL_8_BITS;
		/* By शेष, select CS8 */
		tty->termios.c_cflag = (cflag & ~CSIZE) | CS8;
		अवरोध;
	पूर्ण

	/* Set Parity */
	अगर (cflag & PARENB)
		अगर (cflag & PARODD)
			mr1 |= MR1_PARITY_ON | MR1_PARITY_ODD;
		अन्यथा
			mr1 |= MR1_PARITY_ON | MR1_PARITY_EVEN;
	अन्यथा
		mr1 |= MR1_PARITY_OFF;

	/* Mark or space parity is not supported */
	tty->termios.c_cflag &= ~CMSPAR;

	/* Set stop bits */
	अगर (cflag & CSTOPB)
		mr2 |= MR2_STOP_BITS_LENGTH_2;
	अन्यथा
		mr2 |= MR2_STOP_BITS_LENGTH_1;

	/* Set the flow control */
	चयन (channel->board_id) अणु
	हाल IPACK1_DEVICE_ID_SBS_OCTAL_232:
		अगर (cflag & CRTSCTS) अणु
			mr1 |= MR1_RxRTS_CONTROL_ON;
			mr2 |= MR2_TxRTS_CONTROL_OFF | MR2_CTS_ENABLE_TX_ON;
		पूर्ण अन्यथा अणु
			mr1 |= MR1_RxRTS_CONTROL_OFF;
			mr2 |= MR2_TxRTS_CONTROL_OFF | MR2_CTS_ENABLE_TX_OFF;
		पूर्ण
		अवरोध;
	हाल IPACK1_DEVICE_ID_SBS_OCTAL_422:
		mr1 |= MR1_RxRTS_CONTROL_OFF;
		mr2 |= MR2_TxRTS_CONTROL_OFF | MR2_CTS_ENABLE_TX_OFF;
		अवरोध;
	हाल IPACK1_DEVICE_ID_SBS_OCTAL_485:
		mr1 |= MR1_RxRTS_CONTROL_OFF;
		mr2 |= MR2_TxRTS_CONTROL_ON | MR2_CTS_ENABLE_TX_OFF;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	baud = tty_get_baud_rate(tty);
	tty_termios_encode_baud_rate(&tty->termios, baud, baud);

	/* Set baud rate */
	चयन (baud) अणु
	हाल 75:
		csr |= TX_CLK_75 | RX_CLK_75;
		अवरोध;
	हाल 110:
		csr |= TX_CLK_110 | RX_CLK_110;
		अवरोध;
	हाल 150:
		csr |= TX_CLK_150 | RX_CLK_150;
		अवरोध;
	हाल 300:
		csr |= TX_CLK_300 | RX_CLK_300;
		अवरोध;
	हाल 600:
		csr |= TX_CLK_600 | RX_CLK_600;
		अवरोध;
	हाल 1200:
		csr |= TX_CLK_1200 | RX_CLK_1200;
		अवरोध;
	हाल 1800:
		csr |= TX_CLK_1800 | RX_CLK_1800;
		अवरोध;
	हाल 2000:
		csr |= TX_CLK_2000 | RX_CLK_2000;
		अवरोध;
	हाल 2400:
		csr |= TX_CLK_2400 | RX_CLK_2400;
		अवरोध;
	हाल 4800:
		csr |= TX_CLK_4800  | RX_CLK_4800;
		अवरोध;
	हाल 9600:
		csr |= TX_CLK_9600  | RX_CLK_9600;
		अवरोध;
	हाल 19200:
		csr |= TX_CLK_19200 | RX_CLK_19200;
		अवरोध;
	हाल 38400:
	शेष:
		csr |= TX_CLK_38400 | RX_CLK_38400;
		/* In हाल of शेष, we establish 38400 bps */
		tty_termios_encode_baud_rate(&tty->termios, 38400, 38400);
		अवरोध;
	पूर्ण

	mr1 |= MR1_ERROR_CHAR;
	mr1 |= MR1_RxINT_RxRDY;

	/* Write the control रेजिस्टरs */
	ioग_लिखो8(mr1, &channel->regs->w.mr);
	ioग_लिखो8(mr2, &channel->regs->w.mr);
	ioग_लिखो8(csr, &channel->regs->w.csr);

	/* Enable again the RX, अगर it was beक्रमe */
	अगर (channel->rx_enable)
		ioग_लिखो8(CR_ENABLE_RX, &channel->regs->w.cr);
पूर्ण

अटल व्योम ipoctal_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ipoctal_channel *channel = tty->driver_data;

	अगर (channel == शून्य)
		वापस;

	spin_lock_irqsave(&channel->lock, flags);
	channel->nb_bytes = 0;
	channel->poपूर्णांकer_पढ़ो = 0;
	channel->poपूर्णांकer_ग_लिखो = 0;
	spin_unlock_irqrestore(&channel->lock, flags);

	tty_port_hangup(&channel->tty_port);

	ipoctal_reset_channel(channel);
	tty_port_set_initialized(&channel->tty_port, 0);
	wake_up_पूर्णांकerruptible(&channel->tty_port.खोलो_रुको);
पूर्ण

अटल व्योम ipoctal_shutकरोwn(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;

	अगर (channel == शून्य)
		वापस;

	ipoctal_reset_channel(channel);
	tty_port_set_initialized(&channel->tty_port, 0);
पूर्ण

अटल व्योम ipoctal_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ipoctal_channel *channel = tty->driver_data;
	काष्ठा ipoctal *ipoctal = chan_to_ipoctal(channel, tty->index);

	/* release the carrier driver */
	ipack_put_carrier(ipoctal->dev);
पूर्ण

अटल स्थिर काष्ठा tty_operations ipoctal_fops = अणु
	.ioctl =		शून्य,
	.खोलो =			ipoctal_खोलो,
	.बंद =		ipoctal_बंद,
	.ग_लिखो =		ipoctal_ग_लिखो_tty,
	.set_termios =		ipoctal_set_termios,
	.ग_लिखो_room =		ipoctal_ग_लिखो_room,
	.अक्षरs_in_buffer =	ipoctal_अक्षरs_in_buffer,
	.get_icount =		ipoctal_get_icount,
	.hangup =		ipoctal_hangup,
	.shutकरोwn =		ipoctal_shutकरोwn,
	.cleanup =              ipoctal_cleanup,
पूर्ण;

अटल पूर्णांक ipoctal_probe(काष्ठा ipack_device *dev)
अणु
	पूर्णांक res;
	काष्ठा ipoctal *ipoctal;

	ipoctal = kzalloc(माप(काष्ठा ipoctal), GFP_KERNEL);
	अगर (ipoctal == शून्य)
		वापस -ENOMEM;

	ipoctal->dev = dev;
	res = ipoctal_inst_slot(ipoctal, dev->bus->bus_nr, dev->slot);
	अगर (res)
		जाओ out_uninst;

	dev_set_drvdata(&dev->dev, ipoctal);
	वापस 0;

out_uninst:
	kमुक्त(ipoctal);
	वापस res;
पूर्ण

अटल व्योम __ipoctal_हटाओ(काष्ठा ipoctal *ipoctal)
अणु
	पूर्णांक i;

	ipoctal->dev->bus->ops->मुक्त_irq(ipoctal->dev);

	क्रम (i = 0; i < NR_CHANNELS; i++) अणु
		काष्ठा ipoctal_channel *channel = &ipoctal->channel[i];
		tty_unरेजिस्टर_device(ipoctal->tty_drv, i);
		tty_port_मुक्त_xmit_buf(&channel->tty_port);
		tty_port_destroy(&channel->tty_port);
	पूर्ण

	tty_unरेजिस्टर_driver(ipoctal->tty_drv);
	put_tty_driver(ipoctal->tty_drv);
	kमुक्त(ipoctal);
पूर्ण

अटल व्योम ipoctal_हटाओ(काष्ठा ipack_device *idev)
अणु
	__ipoctal_हटाओ(dev_get_drvdata(&idev->dev));
पूर्ण

अटल DEFINE_IPACK_DEVICE_TABLE(ipoctal_ids) = अणु
	अणु IPACK_DEVICE(IPACK_ID_VERSION_1, IPACK1_VENDOR_ID_SBS,
			IPACK1_DEVICE_ID_SBS_OCTAL_232) पूर्ण,
	अणु IPACK_DEVICE(IPACK_ID_VERSION_1, IPACK1_VENDOR_ID_SBS,
			IPACK1_DEVICE_ID_SBS_OCTAL_422) पूर्ण,
	अणु IPACK_DEVICE(IPACK_ID_VERSION_1, IPACK1_VENDOR_ID_SBS,
			IPACK1_DEVICE_ID_SBS_OCTAL_485) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ipack, ipoctal_ids);

अटल स्थिर काष्ठा ipack_driver_ops ipoctal_drv_ops = अणु
	.probe  = ipoctal_probe,
	.हटाओ = ipoctal_हटाओ,
पूर्ण;

अटल काष्ठा ipack_driver driver = अणु
	.ops      = &ipoctal_drv_ops,
	.id_table = ipoctal_ids,
पूर्ण;

अटल पूर्णांक __init ipoctal_init(व्योम)
अणु
	वापस ipack_driver_रेजिस्टर(&driver, THIS_MODULE, KBUILD_MODNAME);
पूर्ण

अटल व्योम __निकास ipoctal_निकास(व्योम)
अणु
	ipack_driver_unरेजिस्टर(&driver);
पूर्ण

MODULE_DESCRIPTION("IP-Octal 232, 422 and 485 device driver");
MODULE_LICENSE("GPL");

module_init(ipoctal_init);
module_निकास(ipoctal_निकास);
