<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MPC52xx SPI bus driver.
 *
 * Copyright (C) 2008 Secret Lab Technologies Ltd.
 *
 * This is the driver क्रम the MPC5200's dedicated SPI controller.
 *
 * Note: this driver करोes not support the MPC5200 PSC in SPI mode.  For
 * that driver see drivers/spi/mpc52xx_psc_spi.c
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpc52xx.h>

MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_DESCRIPTION("MPC52xx SPI (non-PSC) Driver");
MODULE_LICENSE("GPL");

/* Register offsets */
#घोषणा SPI_CTRL1	0x00
#घोषणा SPI_CTRL1_SPIE		(1 << 7)
#घोषणा SPI_CTRL1_SPE		(1 << 6)
#घोषणा SPI_CTRL1_MSTR		(1 << 4)
#घोषणा SPI_CTRL1_CPOL		(1 << 3)
#घोषणा SPI_CTRL1_CPHA		(1 << 2)
#घोषणा SPI_CTRL1_SSOE		(1 << 1)
#घोषणा SPI_CTRL1_LSBFE		(1 << 0)

#घोषणा SPI_CTRL2	0x01
#घोषणा SPI_BRR		0x04

#घोषणा SPI_STATUS	0x05
#घोषणा SPI_STATUS_SPIF		(1 << 7)
#घोषणा SPI_STATUS_WCOL		(1 << 6)
#घोषणा SPI_STATUS_MODF		(1 << 4)

#घोषणा SPI_DATA	0x09
#घोषणा SPI_PORTDATA	0x0d
#घोषणा SPI_DATAसूची	0x10

/* FSM state वापस values */
#घोषणा FSM_STOP	0	/* Nothing more क्रम the state machine to */
				/* करो.  If something पूर्णांकeresting happens */
				/* then an IRQ will be received */
#घोषणा FSM_POLL	1	/* need to poll क्रम completion, an IRQ is */
				/* not expected */
#घोषणा FSM_CONTINUE	2	/* Keep iterating the state machine */

/* Driver पूर्णांकernal data */
काष्ठा mpc52xx_spi अणु
	काष्ठा spi_master *master;
	व्योम __iomem *regs;
	पूर्णांक irq0;	/* MODF irq */
	पूर्णांक irq1;	/* SPIF irq */
	अचिन्हित पूर्णांक ipb_freq;

	/* Statistics; not used now, but will be reपूर्णांकroduced क्रम debugfs */
	पूर्णांक msg_count;
	पूर्णांक wcol_count;
	पूर्णांक wcol_ticks;
	u32 wcol_tx_बारtamp;
	पूर्णांक modf_count;
	पूर्णांक byte_count;

	काष्ठा list_head queue;		/* queue of pending messages */
	spinlock_t lock;
	काष्ठा work_काष्ठा work;

	/* Details of current transfer (length, and buffer poपूर्णांकers) */
	काष्ठा spi_message *message;	/* current message */
	काष्ठा spi_transfer *transfer;	/* current transfer */
	पूर्णांक (*state)(पूर्णांक irq, काष्ठा mpc52xx_spi *ms, u8 status, u8 data);
	पूर्णांक len;
	पूर्णांक बारtamp;
	u8 *rx_buf;
	स्थिर u8 *tx_buf;
	पूर्णांक cs_change;
	पूर्णांक gpio_cs_count;
	अचिन्हित पूर्णांक *gpio_cs;
पूर्ण;

/*
 * CS control function
 */
अटल व्योम mpc52xx_spi_chipsel(काष्ठा mpc52xx_spi *ms, पूर्णांक value)
अणु
	पूर्णांक cs;

	अगर (ms->gpio_cs_count > 0) अणु
		cs = ms->message->spi->chip_select;
		gpio_set_value(ms->gpio_cs[cs], value ? 0 : 1);
	पूर्ण अन्यथा
		out_8(ms->regs + SPI_PORTDATA, value ? 0 : 0x08);
पूर्ण

/*
 * Start a new transfer.  This is called both by the idle state
 * क्रम the first transfer in a message, and by the रुको state when the
 * previous transfer in a message is complete.
 */
अटल व्योम mpc52xx_spi_start_transfer(काष्ठा mpc52xx_spi *ms)
अणु
	ms->rx_buf = ms->transfer->rx_buf;
	ms->tx_buf = ms->transfer->tx_buf;
	ms->len = ms->transfer->len;

	/* Activate the chip select */
	अगर (ms->cs_change)
		mpc52xx_spi_chipsel(ms, 1);
	ms->cs_change = ms->transfer->cs_change;

	/* Write out the first byte */
	ms->wcol_tx_बारtamp = mftb();
	अगर (ms->tx_buf)
		out_8(ms->regs + SPI_DATA, *ms->tx_buf++);
	अन्यथा
		out_8(ms->regs + SPI_DATA, 0);
पूर्ण

/* Forward declaration of state handlers */
अटल पूर्णांक mpc52xx_spi_fsmstate_transfer(पूर्णांक irq, काष्ठा mpc52xx_spi *ms,
					 u8 status, u8 data);
अटल पूर्णांक mpc52xx_spi_fsmstate_रुको(पूर्णांक irq, काष्ठा mpc52xx_spi *ms,
				     u8 status, u8 data);

/*
 * IDLE state
 *
 * No transfers are in progress; अगर another transfer is pending then retrieve
 * it and kick it off.  Otherwise, stop processing the state machine
 */
अटल पूर्णांक
mpc52xx_spi_fsmstate_idle(पूर्णांक irq, काष्ठा mpc52xx_spi *ms, u8 status, u8 data)
अणु
	काष्ठा spi_device *spi;
	पूर्णांक spr, sppr;
	u8 ctrl1;

	अगर (status && (irq != NO_IRQ))
		dev_err(&ms->master->dev, "spurious irq, status=0x%.2x\n",
			status);

	/* Check अगर there is another transfer रुकोing. */
	अगर (list_empty(&ms->queue))
		वापस FSM_STOP;

	/* get the head of the queue */
	ms->message = list_first_entry(&ms->queue, काष्ठा spi_message, queue);
	list_del_init(&ms->message->queue);

	/* Setup the controller parameters */
	ctrl1 = SPI_CTRL1_SPIE | SPI_CTRL1_SPE | SPI_CTRL1_MSTR;
	spi = ms->message->spi;
	अगर (spi->mode & SPI_CPHA)
		ctrl1 |= SPI_CTRL1_CPHA;
	अगर (spi->mode & SPI_CPOL)
		ctrl1 |= SPI_CTRL1_CPOL;
	अगर (spi->mode & SPI_LSB_FIRST)
		ctrl1 |= SPI_CTRL1_LSBFE;
	out_8(ms->regs + SPI_CTRL1, ctrl1);

	/* Setup the controller speed */
	/* minimum भागider is '2'.  Also, add '1' to क्रमce rounding the
	 * भागider up. */
	sppr = ((ms->ipb_freq / ms->message->spi->max_speed_hz) + 1) >> 1;
	spr = 0;
	अगर (sppr < 1)
		sppr = 1;
	जबतक (((sppr - 1) & ~0x7) != 0) अणु
		sppr = (sppr + 1) >> 1; /* add '1' to क्रमce rounding up */
		spr++;
	पूर्ण
	sppr--;		/* sppr quantity in रेजिस्टर is offset by 1 */
	अगर (spr > 7) अणु
		/* Don't overrun limits of SPI baudrate रेजिस्टर */
		spr = 7;
		sppr = 7;
	पूर्ण
	out_8(ms->regs + SPI_BRR, sppr << 4 | spr); /* Set speed */

	ms->cs_change = 1;
	ms->transfer = container_of(ms->message->transfers.next,
				    काष्ठा spi_transfer, transfer_list);

	mpc52xx_spi_start_transfer(ms);
	ms->state = mpc52xx_spi_fsmstate_transfer;

	वापस FSM_CONTINUE;
पूर्ण

/*
 * TRANSFER state
 *
 * In the middle of a transfer.  If the SPI core has completed processing
 * a byte, then पढ़ो out the received data and ग_लिखो out the next byte
 * (unless this transfer is finished; in which हाल go on to the रुको
 * state)
 */
अटल पूर्णांक mpc52xx_spi_fsmstate_transfer(पूर्णांक irq, काष्ठा mpc52xx_spi *ms,
					 u8 status, u8 data)
अणु
	अगर (!status)
		वापस ms->irq0 ? FSM_STOP : FSM_POLL;

	अगर (status & SPI_STATUS_WCOL) अणु
		/* The SPI controller is stoopid.  At slower speeds, it may
		 * उठाओ the SPIF flag beक्रमe the state machine is actually
		 * finished, which causes a collision (पूर्णांकernal to the state
		 * machine only).  The manual recommends inserting a delay
		 * between receiving the पूर्णांकerrupt and sending the next byte,
		 * but it can also be worked around simply by retrying the
		 * transfer which is what we करो here. */
		ms->wcol_count++;
		ms->wcol_ticks += mftb() - ms->wcol_tx_बारtamp;
		ms->wcol_tx_बारtamp = mftb();
		data = 0;
		अगर (ms->tx_buf)
			data = *(ms->tx_buf - 1);
		out_8(ms->regs + SPI_DATA, data); /* try again */
		वापस FSM_CONTINUE;
	पूर्ण अन्यथा अगर (status & SPI_STATUS_MODF) अणु
		ms->modf_count++;
		dev_err(&ms->master->dev, "mode fault\n");
		mpc52xx_spi_chipsel(ms, 0);
		ms->message->status = -EIO;
		अगर (ms->message->complete)
			ms->message->complete(ms->message->context);
		ms->state = mpc52xx_spi_fsmstate_idle;
		वापस FSM_CONTINUE;
	पूर्ण

	/* Read data out of the spi device */
	ms->byte_count++;
	अगर (ms->rx_buf)
		*ms->rx_buf++ = data;

	/* Is the transfer complete? */
	ms->len--;
	अगर (ms->len == 0) अणु
		ms->बारtamp = mftb();
		अगर (ms->transfer->delay.unit == SPI_DELAY_UNIT_USECS)
			ms->बारtamp += ms->transfer->delay.value *
					 tb_ticks_per_usec;
		ms->state = mpc52xx_spi_fsmstate_रुको;
		वापस FSM_CONTINUE;
	पूर्ण

	/* Write out the next byte */
	ms->wcol_tx_बारtamp = mftb();
	अगर (ms->tx_buf)
		out_8(ms->regs + SPI_DATA, *ms->tx_buf++);
	अन्यथा
		out_8(ms->regs + SPI_DATA, 0);

	वापस FSM_CONTINUE;
पूर्ण

/*
 * WAIT state
 *
 * A transfer has completed; need to रुको क्रम the delay period to complete
 * beक्रमe starting the next transfer
 */
अटल पूर्णांक
mpc52xx_spi_fsmstate_रुको(पूर्णांक irq, काष्ठा mpc52xx_spi *ms, u8 status, u8 data)
अणु
	अगर (status && irq)
		dev_err(&ms->master->dev, "spurious irq, status=0x%.2x\n",
			status);

	अगर (((पूर्णांक)mftb()) - ms->बारtamp < 0)
		वापस FSM_POLL;

	ms->message->actual_length += ms->transfer->len;

	/* Check अगर there is another transfer in this message.  If there
	 * aren't then deactivate CS, notअगरy sender, and drop back to idle
	 * to start the next message. */
	अगर (ms->transfer->transfer_list.next == &ms->message->transfers) अणु
		ms->msg_count++;
		mpc52xx_spi_chipsel(ms, 0);
		ms->message->status = 0;
		अगर (ms->message->complete)
			ms->message->complete(ms->message->context);
		ms->state = mpc52xx_spi_fsmstate_idle;
		वापस FSM_CONTINUE;
	पूर्ण

	/* There is another transfer; kick it off */

	अगर (ms->cs_change)
		mpc52xx_spi_chipsel(ms, 0);

	ms->transfer = container_of(ms->transfer->transfer_list.next,
				    काष्ठा spi_transfer, transfer_list);
	mpc52xx_spi_start_transfer(ms);
	ms->state = mpc52xx_spi_fsmstate_transfer;
	वापस FSM_CONTINUE;
पूर्ण

/**
 * mpc52xx_spi_fsm_process - Finite State Machine iteration function
 * @irq: irq number that triggered the FSM or 0 क्रम polling
 * @ms: poपूर्णांकer to mpc52xx_spi driver data
 */
अटल व्योम mpc52xx_spi_fsm_process(पूर्णांक irq, काष्ठा mpc52xx_spi *ms)
अणु
	पूर्णांक rc = FSM_CONTINUE;
	u8 status, data;

	जबतक (rc == FSM_CONTINUE) अणु
		/* Interrupt cleared by पढ़ो of STATUS followed by
		 * पढ़ो of DATA रेजिस्टरs */
		status = in_8(ms->regs + SPI_STATUS);
		data = in_8(ms->regs + SPI_DATA);
		rc = ms->state(irq, ms, status, data);
	पूर्ण

	अगर (rc == FSM_POLL)
		schedule_work(&ms->work);
पूर्ण

/**
 * mpc52xx_spi_irq - IRQ handler
 */
अटल irqवापस_t mpc52xx_spi_irq(पूर्णांक irq, व्योम *_ms)
अणु
	काष्ठा mpc52xx_spi *ms = _ms;
	spin_lock(&ms->lock);
	mpc52xx_spi_fsm_process(irq, ms);
	spin_unlock(&ms->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * mpc52xx_spi_wq - Workqueue function क्रम polling the state machine
 */
अटल व्योम mpc52xx_spi_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mpc52xx_spi *ms = container_of(work, काष्ठा mpc52xx_spi, work);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ms->lock, flags);
	mpc52xx_spi_fsm_process(0, ms);
	spin_unlock_irqrestore(&ms->lock, flags);
पूर्ण

/*
 * spi_master ops
 */

अटल पूर्णांक mpc52xx_spi_transfer(काष्ठा spi_device *spi, काष्ठा spi_message *m)
अणु
	काष्ठा mpc52xx_spi *ms = spi_master_get_devdata(spi->master);
	अचिन्हित दीर्घ flags;

	m->actual_length = 0;
	m->status = -EINPROGRESS;

	spin_lock_irqsave(&ms->lock, flags);
	list_add_tail(&m->queue, &ms->queue);
	spin_unlock_irqrestore(&ms->lock, flags);
	schedule_work(&ms->work);

	वापस 0;
पूर्ण

/*
 * OF Platक्रमm Bus Binding
 */
अटल पूर्णांक mpc52xx_spi_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा spi_master *master;
	काष्ठा mpc52xx_spi *ms;
	व्योम __iomem *regs;
	u8 ctrl1;
	पूर्णांक rc, i = 0;
	पूर्णांक gpio_cs;

	/* MMIO रेजिस्टरs */
	dev_dbg(&op->dev, "probing mpc5200 SPI device\n");
	regs = of_iomap(op->dev.of_node, 0);
	अगर (!regs)
		वापस -ENODEV;

	/* initialize the device */
	ctrl1 = SPI_CTRL1_SPIE | SPI_CTRL1_SPE | SPI_CTRL1_MSTR;
	out_8(regs + SPI_CTRL1, ctrl1);
	out_8(regs + SPI_CTRL2, 0x0);
	out_8(regs + SPI_DATAसूची, 0xe);	/* Set output pins */
	out_8(regs + SPI_PORTDATA, 0x8);	/* Deनिश्चित /SS संकेत */

	/* Clear the status रेजिस्टर and re-पढ़ो it to check क्रम a MODF
	 * failure.  This driver cannot currently handle multiple masters
	 * on the SPI bus.  This fault will also occur अगर the SPI संकेतs
	 * are not connected to any pins (port_config setting) */
	in_8(regs + SPI_STATUS);
	out_8(regs + SPI_CTRL1, ctrl1);

	in_8(regs + SPI_DATA);
	अगर (in_8(regs + SPI_STATUS) & SPI_STATUS_MODF) अणु
		dev_err(&op->dev, "mode fault; is port_config correct?\n");
		rc = -EIO;
		जाओ err_init;
	पूर्ण

	dev_dbg(&op->dev, "allocating spi_master struct\n");
	master = spi_alloc_master(&op->dev, माप *ms);
	अगर (!master) अणु
		rc = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	master->transfer = mpc52xx_spi_transfer;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->dev.of_node = op->dev.of_node;

	platक्रमm_set_drvdata(op, master);

	ms = spi_master_get_devdata(master);
	ms->master = master;
	ms->regs = regs;
	ms->irq0 = irq_of_parse_and_map(op->dev.of_node, 0);
	ms->irq1 = irq_of_parse_and_map(op->dev.of_node, 1);
	ms->state = mpc52xx_spi_fsmstate_idle;
	ms->ipb_freq = mpc5xxx_get_bus_frequency(op->dev.of_node);
	ms->gpio_cs_count = of_gpio_count(op->dev.of_node);
	अगर (ms->gpio_cs_count > 0) अणु
		master->num_chipselect = ms->gpio_cs_count;
		ms->gpio_cs = kदो_स्मृति_array(ms->gpio_cs_count,
					    माप(*ms->gpio_cs),
					    GFP_KERNEL);
		अगर (!ms->gpio_cs) अणु
			rc = -ENOMEM;
			जाओ err_alloc_gpio;
		पूर्ण

		क्रम (i = 0; i < ms->gpio_cs_count; i++) अणु
			gpio_cs = of_get_gpio(op->dev.of_node, i);
			अगर (!gpio_is_valid(gpio_cs)) अणु
				dev_err(&op->dev,
					"could not parse the gpio field in oftree\n");
				rc = -ENODEV;
				जाओ err_gpio;
			पूर्ण

			rc = gpio_request(gpio_cs, dev_name(&op->dev));
			अगर (rc) अणु
				dev_err(&op->dev,
					"can't request spi cs gpio #%d on gpio line %d\n",
					i, gpio_cs);
				जाओ err_gpio;
			पूर्ण

			gpio_direction_output(gpio_cs, 1);
			ms->gpio_cs[i] = gpio_cs;
		पूर्ण
	पूर्ण

	spin_lock_init(&ms->lock);
	INIT_LIST_HEAD(&ms->queue);
	INIT_WORK(&ms->work, mpc52xx_spi_wq);

	/* Decide अगर पूर्णांकerrupts can be used */
	अगर (ms->irq0 && ms->irq1) अणु
		rc = request_irq(ms->irq0, mpc52xx_spi_irq, 0,
				  "mpc5200-spi-modf", ms);
		rc |= request_irq(ms->irq1, mpc52xx_spi_irq, 0,
				  "mpc5200-spi-spif", ms);
		अगर (rc) अणु
			मुक्त_irq(ms->irq0, ms);
			मुक्त_irq(ms->irq1, ms);
			ms->irq0 = ms->irq1 = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* operate in polled mode */
		ms->irq0 = ms->irq1 = 0;
	पूर्ण

	अगर (!ms->irq0)
		dev_info(&op->dev, "using polled mode\n");

	dev_dbg(&op->dev, "registering spi_master struct\n");
	rc = spi_रेजिस्टर_master(master);
	अगर (rc)
		जाओ err_रेजिस्टर;

	dev_info(&ms->master->dev, "registered MPC5200 SPI bus\n");

	वापस rc;

 err_रेजिस्टर:
	dev_err(&ms->master->dev, "initialization failed\n");
 err_gpio:
	जबतक (i-- > 0)
		gpio_मुक्त(ms->gpio_cs[i]);

	kमुक्त(ms->gpio_cs);
 err_alloc_gpio:
	spi_master_put(master);
 err_alloc:
 err_init:
	iounmap(regs);
	वापस rc;
पूर्ण

अटल पूर्णांक mpc52xx_spi_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा spi_master *master = spi_master_get(platक्रमm_get_drvdata(op));
	काष्ठा mpc52xx_spi *ms = spi_master_get_devdata(master);
	पूर्णांक i;

	मुक्त_irq(ms->irq0, ms);
	मुक्त_irq(ms->irq1, ms);

	क्रम (i = 0; i < ms->gpio_cs_count; i++)
		gpio_मुक्त(ms->gpio_cs[i]);

	kमुक्त(ms->gpio_cs);
	spi_unरेजिस्टर_master(master);
	iounmap(ms->regs);
	spi_master_put(master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_spi_match[] = अणु
	अणु .compatible = "fsl,mpc5200-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc52xx_spi_match);

अटल काष्ठा platक्रमm_driver mpc52xx_spi_of_driver = अणु
	.driver = अणु
		.name = "mpc52xx-spi",
		.of_match_table = mpc52xx_spi_match,
	पूर्ण,
	.probe = mpc52xx_spi_probe,
	.हटाओ = mpc52xx_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(mpc52xx_spi_of_driver);
