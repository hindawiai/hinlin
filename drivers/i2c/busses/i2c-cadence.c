<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * I2C bus driver क्रम the Cadence I2C controller.
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>

/* Register offsets क्रम the I2C device. */
#घोषणा CDNS_I2C_CR_OFFSET		0x00 /* Control Register, RW */
#घोषणा CDNS_I2C_SR_OFFSET		0x04 /* Status Register, RO */
#घोषणा CDNS_I2C_ADDR_OFFSET		0x08 /* I2C Address Register, RW */
#घोषणा CDNS_I2C_DATA_OFFSET		0x0C /* I2C Data Register, RW */
#घोषणा CDNS_I2C_ISR_OFFSET		0x10 /* IRQ Status Register, RW */
#घोषणा CDNS_I2C_XFER_SIZE_OFFSET	0x14 /* Transfer Size Register, RW */
#घोषणा CDNS_I2C_TIME_OUT_OFFSET	0x1C /* Time Out Register, RW */
#घोषणा CDNS_I2C_IMR_OFFSET		0x20 /* IRQ Mask Register, RO */
#घोषणा CDNS_I2C_IER_OFFSET		0x24 /* IRQ Enable Register, WO */
#घोषणा CDNS_I2C_IDR_OFFSET		0x28 /* IRQ Disable Register, WO */

/* Control Register Bit mask definitions */
#घोषणा CDNS_I2C_CR_HOLD		BIT(4) /* Hold Bus bit */
#घोषणा CDNS_I2C_CR_ACK_EN		BIT(3)
#घोषणा CDNS_I2C_CR_NEA			BIT(2)
#घोषणा CDNS_I2C_CR_MS			BIT(1)
/* Read or Write Master transfer 0 = Transmitter, 1 = Receiver */
#घोषणा CDNS_I2C_CR_RW			BIT(0)
/* 1 = Auto init FIFO to zeroes */
#घोषणा CDNS_I2C_CR_CLR_FIFO		BIT(6)
#घोषणा CDNS_I2C_CR_DIVA_SHIFT		14
#घोषणा CDNS_I2C_CR_DIVA_MASK		(3 << CDNS_I2C_CR_DIVA_SHIFT)
#घोषणा CDNS_I2C_CR_DIVB_SHIFT		8
#घोषणा CDNS_I2C_CR_DIVB_MASK		(0x3f << CDNS_I2C_CR_DIVB_SHIFT)

#घोषणा CDNS_I2C_CR_MASTER_EN_MASK	(CDNS_I2C_CR_NEA | \
					 CDNS_I2C_CR_ACK_EN | \
					 CDNS_I2C_CR_MS)

#घोषणा CDNS_I2C_CR_SLAVE_EN_MASK	~CDNS_I2C_CR_MASTER_EN_MASK

/* Status Register Bit mask definitions */
#घोषणा CDNS_I2C_SR_BA		BIT(8)
#घोषणा CDNS_I2C_SR_TXDV	BIT(6)
#घोषणा CDNS_I2C_SR_RXDV	BIT(5)
#घोषणा CDNS_I2C_SR_RXRW	BIT(3)

/*
 * I2C Address Register Bit mask definitions
 * Normal addressing mode uses [6:0] bits. Extended addressing mode uses [9:0]
 * bits. A ग_लिखो access to this रेजिस्टर always initiates a transfer अगर the I2C
 * is in master mode.
 */
#घोषणा CDNS_I2C_ADDR_MASK	0x000003FF /* I2C Address Mask */

/*
 * I2C Interrupt Registers Bit mask definitions
 * All the four पूर्णांकerrupt रेजिस्टरs (Status/Mask/Enable/Disable) have the same
 * bit definitions.
 */
#घोषणा CDNS_I2C_IXR_ARB_LOST		BIT(9)
#घोषणा CDNS_I2C_IXR_RX_UNF		BIT(7)
#घोषणा CDNS_I2C_IXR_TX_OVF		BIT(6)
#घोषणा CDNS_I2C_IXR_RX_OVF		BIT(5)
#घोषणा CDNS_I2C_IXR_SLV_RDY		BIT(4)
#घोषणा CDNS_I2C_IXR_TO			BIT(3)
#घोषणा CDNS_I2C_IXR_NACK		BIT(2)
#घोषणा CDNS_I2C_IXR_DATA		BIT(1)
#घोषणा CDNS_I2C_IXR_COMP		BIT(0)

#घोषणा CDNS_I2C_IXR_ALL_INTR_MASK	(CDNS_I2C_IXR_ARB_LOST | \
					 CDNS_I2C_IXR_RX_UNF | \
					 CDNS_I2C_IXR_TX_OVF | \
					 CDNS_I2C_IXR_RX_OVF | \
					 CDNS_I2C_IXR_SLV_RDY | \
					 CDNS_I2C_IXR_TO | \
					 CDNS_I2C_IXR_NACK | \
					 CDNS_I2C_IXR_DATA | \
					 CDNS_I2C_IXR_COMP)

#घोषणा CDNS_I2C_IXR_ERR_INTR_MASK	(CDNS_I2C_IXR_ARB_LOST | \
					 CDNS_I2C_IXR_RX_UNF | \
					 CDNS_I2C_IXR_TX_OVF | \
					 CDNS_I2C_IXR_RX_OVF | \
					 CDNS_I2C_IXR_NACK)

#घोषणा CDNS_I2C_ENABLED_INTR_MASK	(CDNS_I2C_IXR_ARB_LOST | \
					 CDNS_I2C_IXR_RX_UNF | \
					 CDNS_I2C_IXR_TX_OVF | \
					 CDNS_I2C_IXR_RX_OVF | \
					 CDNS_I2C_IXR_NACK | \
					 CDNS_I2C_IXR_DATA | \
					 CDNS_I2C_IXR_COMP)

#घोषणा CDNS_I2C_IXR_SLAVE_INTR_MASK	(CDNS_I2C_IXR_RX_UNF | \
					 CDNS_I2C_IXR_TX_OVF | \
					 CDNS_I2C_IXR_RX_OVF | \
					 CDNS_I2C_IXR_TO | \
					 CDNS_I2C_IXR_NACK | \
					 CDNS_I2C_IXR_DATA | \
					 CDNS_I2C_IXR_COMP)

#घोषणा CDNS_I2C_TIMEOUT		msecs_to_jअगरfies(1000)
/* समयout क्रम pm runसमय स्वतःsuspend */
#घोषणा CNDS_I2C_PM_TIMEOUT		1000	/* ms */

#घोषणा CDNS_I2C_FIFO_DEPTH		16
/* FIFO depth at which the DATA पूर्णांकerrupt occurs */
#घोषणा CDNS_I2C_DATA_INTR_DEPTH	(CDNS_I2C_FIFO_DEPTH - 2)
#घोषणा CDNS_I2C_MAX_TRANSFER_SIZE	255
/* Transfer size in multiples of data पूर्णांकerrupt depth */
#घोषणा CDNS_I2C_TRANSFER_SIZE	(CDNS_I2C_MAX_TRANSFER_SIZE - 3)

#घोषणा DRIVER_NAME		"cdns-i2c"

#घोषणा CDNS_I2C_DIVA_MAX	4
#घोषणा CDNS_I2C_DIVB_MAX	64

#घोषणा CDNS_I2C_TIMEOUT_MAX	0xFF

#घोषणा CDNS_I2C_BROKEN_HOLD_BIT	BIT(0)

#घोषणा cdns_i2c_पढ़ोreg(offset)       पढ़ोl_relaxed(id->membase + offset)
#घोषणा cdns_i2c_ग_लिखोreg(val, offset) ग_लिखोl_relaxed(val, id->membase + offset)

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
/**
 * क्रमागत cdns_i2c_mode - I2C Controller current operating mode
 *
 * @CDNS_I2C_MODE_SLAVE:       I2C controller operating in slave mode
 * @CDNS_I2C_MODE_MASTER:      I2C Controller operating in master mode
 */
क्रमागत cdns_i2c_mode अणु
	CDNS_I2C_MODE_SLAVE,
	CDNS_I2C_MODE_MASTER,
पूर्ण;

/**
 * क्रमागत cdns_i2c_slave_state - Slave state when I2C is operating in slave mode
 *
 * @CDNS_I2C_SLAVE_STATE_IDLE: I2C slave idle
 * @CDNS_I2C_SLAVE_STATE_SEND: I2C slave sending data to master
 * @CDNS_I2C_SLAVE_STATE_RECV: I2C slave receiving data from master
 */
क्रमागत cdns_i2c_slave_state अणु
	CDNS_I2C_SLAVE_STATE_IDLE,
	CDNS_I2C_SLAVE_STATE_SEND,
	CDNS_I2C_SLAVE_STATE_RECV,
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा cdns_i2c - I2C device निजी data काष्ठाure
 *
 * @dev:		Poपूर्णांकer to device काष्ठाure
 * @membase:		Base address of the I2C device
 * @adap:		I2C adapter instance
 * @p_msg:		Message poपूर्णांकer
 * @err_status:		Error status in Interrupt Status Register
 * @xfer_करोne:		Transfer complete status
 * @p_send_buf:		Poपूर्णांकer to transmit buffer
 * @p_recv_buf:		Poपूर्णांकer to receive buffer
 * @send_count:		Number of bytes still expected to send
 * @recv_count:		Number of bytes still expected to receive
 * @curr_recv_count:	Number of bytes to be received in current transfer
 * @irq:		IRQ number
 * @input_clk:		Input घड़ी to I2C controller
 * @i2c_clk:		Maximum I2C घड़ी speed
 * @bus_hold_flag:	Flag used in repeated start क्रम clearing HOLD bit
 * @clk:		Poपूर्णांकer to काष्ठा clk
 * @clk_rate_change_nb:	Notअगरier block क्रम घड़ी rate changes
 * @quirks:		flag क्रम broken hold bit usage in r1p10
 * @ctrl_reg_भागa_भागb: value of fields DIV_A and DIV_B from CR रेजिस्टर
 * @slave:		Registered slave instance.
 * @dev_mode:		I2C operating role(master/slave).
 * @slave_state:	I2C Slave state(idle/पढ़ो/ग_लिखो).
 */
काष्ठा cdns_i2c अणु
	काष्ठा device		*dev;
	व्योम __iomem *membase;
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_msg *p_msg;
	पूर्णांक err_status;
	काष्ठा completion xfer_करोne;
	अचिन्हित अक्षर *p_send_buf;
	अचिन्हित अक्षर *p_recv_buf;
	अचिन्हित पूर्णांक send_count;
	अचिन्हित पूर्णांक recv_count;
	अचिन्हित पूर्णांक curr_recv_count;
	पूर्णांक irq;
	अचिन्हित दीर्घ input_clk;
	अचिन्हित पूर्णांक i2c_clk;
	अचिन्हित पूर्णांक bus_hold_flag;
	काष्ठा clk *clk;
	काष्ठा notअगरier_block clk_rate_change_nb;
	u32 quirks;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	u16 ctrl_reg_भागa_भागb;
	काष्ठा i2c_client *slave;
	क्रमागत cdns_i2c_mode dev_mode;
	क्रमागत cdns_i2c_slave_state slave_state;
#पूर्ण_अगर
पूर्ण;

काष्ठा cdns_platक्रमm_data अणु
	u32 quirks;
पूर्ण;

#घोषणा to_cdns_i2c(_nb)	container_of(_nb, काष्ठा cdns_i2c, \
					     clk_rate_change_nb)

/**
 * cdns_i2c_clear_bus_hold - Clear bus hold bit
 * @id:	Poपूर्णांकer to driver data काष्ठा
 *
 * Helper to clear the controller's bus hold bit.
 */
अटल व्योम cdns_i2c_clear_bus_hold(काष्ठा cdns_i2c *id)
अणु
	u32 reg = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
	अगर (reg & CDNS_I2C_CR_HOLD)
		cdns_i2c_ग_लिखोreg(reg & ~CDNS_I2C_CR_HOLD, CDNS_I2C_CR_OFFSET);
पूर्ण

अटल अंतरभूत bool cdns_is_holdquirk(काष्ठा cdns_i2c *id, bool hold_wrkaround)
अणु
	वापस (hold_wrkaround &&
		(id->curr_recv_count == CDNS_I2C_FIFO_DEPTH + 1));
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
अटल व्योम cdns_i2c_set_mode(क्रमागत cdns_i2c_mode mode, काष्ठा cdns_i2c *id)
अणु
	/* Disable all पूर्णांकerrupts */
	cdns_i2c_ग_लिखोreg(CDNS_I2C_IXR_ALL_INTR_MASK, CDNS_I2C_IDR_OFFSET);

	/* Clear FIFO and transfer size */
	cdns_i2c_ग_लिखोreg(CDNS_I2C_CR_CLR_FIFO, CDNS_I2C_CR_OFFSET);

	/* Update device mode and state */
	id->dev_mode = mode;
	id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;

	चयन (mode) अणु
	हाल CDNS_I2C_MODE_MASTER:
		/* Enable i2c master */
		cdns_i2c_ग_लिखोreg(id->ctrl_reg_भागa_भागb |
				  CDNS_I2C_CR_MASTER_EN_MASK,
				  CDNS_I2C_CR_OFFSET);
		/*
		 * This delay is needed to give the IP some समय to चयन to
		 * the master mode. With lower values(like 110 us) i2cdetect
		 * will not detect any slave and without this delay, the IP will
		 * trigger a समयout पूर्णांकerrupt.
		 */
		usleep_range(115, 125);
		अवरोध;
	हाल CDNS_I2C_MODE_SLAVE:
		/* Enable i2c slave */
		cdns_i2c_ग_लिखोreg(id->ctrl_reg_भागa_भागb &
				  CDNS_I2C_CR_SLAVE_EN_MASK,
				  CDNS_I2C_CR_OFFSET);

		/* Setting slave address */
		cdns_i2c_ग_लिखोreg(id->slave->addr & CDNS_I2C_ADDR_MASK,
				  CDNS_I2C_ADDR_OFFSET);

		/* Enable slave send/receive पूर्णांकerrupts */
		cdns_i2c_ग_लिखोreg(CDNS_I2C_IXR_SLAVE_INTR_MASK,
				  CDNS_I2C_IER_OFFSET);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cdns_i2c_slave_rcv_data(काष्ठा cdns_i2c *id)
अणु
	u8 bytes;
	अचिन्हित अक्षर data;

	/* Prepare backend क्रम data reception */
	अगर (id->slave_state == CDNS_I2C_SLAVE_STATE_IDLE) अणु
		id->slave_state = CDNS_I2C_SLAVE_STATE_RECV;
		i2c_slave_event(id->slave, I2C_SLAVE_WRITE_REQUESTED, शून्य);
	पूर्ण

	/* Fetch number of bytes to receive */
	bytes = cdns_i2c_पढ़ोreg(CDNS_I2C_XFER_SIZE_OFFSET);

	/* Read data and send to backend */
	जबतक (bytes--) अणु
		data = cdns_i2c_पढ़ोreg(CDNS_I2C_DATA_OFFSET);
		i2c_slave_event(id->slave, I2C_SLAVE_WRITE_RECEIVED, &data);
	पूर्ण
पूर्ण

अटल व्योम cdns_i2c_slave_send_data(काष्ठा cdns_i2c *id)
अणु
	u8 data;

	/* Prepare backend क्रम data transmission */
	अगर (id->slave_state == CDNS_I2C_SLAVE_STATE_IDLE) अणु
		id->slave_state = CDNS_I2C_SLAVE_STATE_SEND;
		i2c_slave_event(id->slave, I2C_SLAVE_READ_REQUESTED, &data);
	पूर्ण अन्यथा अणु
		i2c_slave_event(id->slave, I2C_SLAVE_READ_PROCESSED, &data);
	पूर्ण

	/* Send data over bus */
	cdns_i2c_ग_लिखोreg(data, CDNS_I2C_DATA_OFFSET);
पूर्ण

/**
 * cdns_i2c_slave_isr - Interrupt handler क्रम the I2C device in slave role
 * @ptr:       Poपूर्णांकer to I2C device निजी data
 *
 * This function handles the data पूर्णांकerrupt and transfer complete पूर्णांकerrupt of
 * the I2C device in slave role.
 *
 * Return: IRQ_HANDLED always
 */
अटल irqवापस_t cdns_i2c_slave_isr(व्योम *ptr)
अणु
	काष्ठा cdns_i2c *id = ptr;
	अचिन्हित पूर्णांक isr_status, i2c_status;

	/* Fetch the पूर्णांकerrupt status */
	isr_status = cdns_i2c_पढ़ोreg(CDNS_I2C_ISR_OFFSET);
	cdns_i2c_ग_लिखोreg(isr_status, CDNS_I2C_ISR_OFFSET);

	/* Ignore masked पूर्णांकerrupts */
	isr_status &= ~cdns_i2c_पढ़ोreg(CDNS_I2C_IMR_OFFSET);

	/* Fetch transfer mode (send/receive) */
	i2c_status = cdns_i2c_पढ़ोreg(CDNS_I2C_SR_OFFSET);

	/* Handle data send/receive */
	अगर (i2c_status & CDNS_I2C_SR_RXRW) अणु
		/* Send data to master */
		अगर (isr_status & CDNS_I2C_IXR_DATA)
			cdns_i2c_slave_send_data(id);

		अगर (isr_status & CDNS_I2C_IXR_COMP) अणु
			id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
			i2c_slave_event(id->slave, I2C_SLAVE_STOP, शून्य);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Receive data from master */
		अगर (isr_status & CDNS_I2C_IXR_DATA)
			cdns_i2c_slave_rcv_data(id);

		अगर (isr_status & CDNS_I2C_IXR_COMP) अणु
			cdns_i2c_slave_rcv_data(id);
			id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
			i2c_slave_event(id->slave, I2C_SLAVE_STOP, शून्य);
		पूर्ण
	पूर्ण

	/* Master indicated xfer stop or fअगरo underflow/overflow */
	अगर (isr_status & (CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_RX_OVF |
			  CDNS_I2C_IXR_RX_UNF | CDNS_I2C_IXR_TX_OVF)) अणु
		id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
		i2c_slave_event(id->slave, I2C_SLAVE_STOP, शून्य);
		cdns_i2c_ग_लिखोreg(CDNS_I2C_CR_CLR_FIFO, CDNS_I2C_CR_OFFSET);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

/**
 * cdns_i2c_master_isr - Interrupt handler क्रम the I2C device in master role
 * @ptr:       Poपूर्णांकer to I2C device निजी data
 *
 * This function handles the data पूर्णांकerrupt, transfer complete पूर्णांकerrupt and
 * the error पूर्णांकerrupts of the I2C device in master role.
 *
 * Return: IRQ_HANDLED always
 */
अटल irqवापस_t cdns_i2c_master_isr(व्योम *ptr)
अणु
	अचिन्हित पूर्णांक isr_status, avail_bytes, updatetx;
	अचिन्हित पूर्णांक bytes_to_send;
	bool hold_quirk;
	काष्ठा cdns_i2c *id = ptr;
	/* Signal completion only after everything is updated */
	पूर्णांक करोne_flag = 0;
	irqवापस_t status = IRQ_NONE;

	isr_status = cdns_i2c_पढ़ोreg(CDNS_I2C_ISR_OFFSET);
	cdns_i2c_ग_लिखोreg(isr_status, CDNS_I2C_ISR_OFFSET);
	id->err_status = 0;

	/* Handling nack and arbitration lost पूर्णांकerrupt */
	अगर (isr_status & (CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_ARB_LOST)) अणु
		करोne_flag = 1;
		status = IRQ_HANDLED;
	पूर्ण

	/*
	 * Check अगर transfer size रेजिस्टर needs to be updated again क्रम a
	 * large data receive operation.
	 */
	updatetx = 0;
	अगर (id->recv_count > id->curr_recv_count)
		updatetx = 1;

	hold_quirk = (id->quirks & CDNS_I2C_BROKEN_HOLD_BIT) && updatetx;

	/* When receiving, handle data पूर्णांकerrupt and completion पूर्णांकerrupt */
	अगर (id->p_recv_buf &&
	    ((isr_status & CDNS_I2C_IXR_COMP) ||
	     (isr_status & CDNS_I2C_IXR_DATA))) अणु
		/* Read data अगर receive data valid is set */
		जबतक (cdns_i2c_पढ़ोreg(CDNS_I2C_SR_OFFSET) &
		       CDNS_I2C_SR_RXDV) अणु
			अगर (id->recv_count > 0) अणु
				*(id->p_recv_buf)++ =
					cdns_i2c_पढ़ोreg(CDNS_I2C_DATA_OFFSET);
				id->recv_count--;
				id->curr_recv_count--;

				/*
				 * Clear hold bit that was set क्रम FIFO control
				 * अगर RX data left is less than or equal to
				 * FIFO DEPTH unless repeated start is selected
				 */
				अगर (id->recv_count <= CDNS_I2C_FIFO_DEPTH &&
				    !id->bus_hold_flag)
					cdns_i2c_clear_bus_hold(id);

			पूर्ण अन्यथा अणु
				dev_err(id->adap.dev.parent,
					"xfer_size reg rollover. xfer aborted!\n");
				id->err_status |= CDNS_I2C_IXR_TO;
				अवरोध;
			पूर्ण

			अगर (cdns_is_holdquirk(id, hold_quirk))
				अवरोध;
		पूर्ण

		/*
		 * The controller sends NACK to the slave when transfer size
		 * रेजिस्टर reaches zero without considering the HOLD bit.
		 * This workaround is implemented क्रम large data transfers to
		 * मुख्यtain transfer size non-zero जबतक perक्रमming a large
		 * receive operation.
		 */
		अगर (cdns_is_holdquirk(id, hold_quirk)) अणु
			/* रुको जबतक fअगरo is full */
			जबतक (cdns_i2c_पढ़ोreg(CDNS_I2C_XFER_SIZE_OFFSET) !=
			       (id->curr_recv_count - CDNS_I2C_FIFO_DEPTH))
				;

			/*
			 * Check number of bytes to be received against maximum
			 * transfer size and update रेजिस्टर accordingly.
			 */
			अगर (((पूर्णांक)(id->recv_count) - CDNS_I2C_FIFO_DEPTH) >
			    CDNS_I2C_TRANSFER_SIZE) अणु
				cdns_i2c_ग_लिखोreg(CDNS_I2C_TRANSFER_SIZE,
						  CDNS_I2C_XFER_SIZE_OFFSET);
				id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE +
						      CDNS_I2C_FIFO_DEPTH;
			पूर्ण अन्यथा अणु
				cdns_i2c_ग_लिखोreg(id->recv_count -
						  CDNS_I2C_FIFO_DEPTH,
						  CDNS_I2C_XFER_SIZE_OFFSET);
				id->curr_recv_count = id->recv_count;
			पूर्ण
		पूर्ण अन्यथा अगर (id->recv_count && !hold_quirk &&
						!id->curr_recv_count) अणु

			/* Set the slave address in address रेजिस्टर*/
			cdns_i2c_ग_लिखोreg(id->p_msg->addr & CDNS_I2C_ADDR_MASK,
						CDNS_I2C_ADDR_OFFSET);

			अगर (id->recv_count > CDNS_I2C_TRANSFER_SIZE) अणु
				cdns_i2c_ग_लिखोreg(CDNS_I2C_TRANSFER_SIZE,
						CDNS_I2C_XFER_SIZE_OFFSET);
				id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE;
			पूर्ण अन्यथा अणु
				cdns_i2c_ग_लिखोreg(id->recv_count,
						CDNS_I2C_XFER_SIZE_OFFSET);
				id->curr_recv_count = id->recv_count;
			पूर्ण
		पूर्ण

		/* Clear hold (अगर not repeated start) and संकेत completion */
		अगर ((isr_status & CDNS_I2C_IXR_COMP) && !id->recv_count) अणु
			अगर (!id->bus_hold_flag)
				cdns_i2c_clear_bus_hold(id);
			करोne_flag = 1;
		पूर्ण

		status = IRQ_HANDLED;
	पूर्ण

	/* When sending, handle transfer complete पूर्णांकerrupt */
	अगर ((isr_status & CDNS_I2C_IXR_COMP) && !id->p_recv_buf) अणु
		/*
		 * If there is more data to be sent, calculate the
		 * space available in FIFO and fill with that many bytes.
		 */
		अगर (id->send_count) अणु
			avail_bytes = CDNS_I2C_FIFO_DEPTH -
			    cdns_i2c_पढ़ोreg(CDNS_I2C_XFER_SIZE_OFFSET);
			अगर (id->send_count > avail_bytes)
				bytes_to_send = avail_bytes;
			अन्यथा
				bytes_to_send = id->send_count;

			जबतक (bytes_to_send--) अणु
				cdns_i2c_ग_लिखोreg(
					(*(id->p_send_buf)++),
					 CDNS_I2C_DATA_OFFSET);
				id->send_count--;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Signal the completion of transaction and
			 * clear the hold bus bit अगर there are no
			 * further messages to be processed.
			 */
			करोne_flag = 1;
		पूर्ण
		अगर (!id->send_count && !id->bus_hold_flag)
			cdns_i2c_clear_bus_hold(id);

		status = IRQ_HANDLED;
	पूर्ण

	/* Update the status क्रम errors */
	id->err_status |= isr_status & CDNS_I2C_IXR_ERR_INTR_MASK;
	अगर (id->err_status)
		status = IRQ_HANDLED;

	अगर (करोne_flag)
		complete(&id->xfer_करोne);

	वापस status;
पूर्ण

/**
 * cdns_i2c_isr - Interrupt handler क्रम the I2C device
 * @irq:	irq number क्रम the I2C device
 * @ptr:	व्योम poपूर्णांकer to cdns_i2c काष्ठाure
 *
 * This function passes the control to slave/master based on current role of
 * i2c controller.
 *
 * Return: IRQ_HANDLED always
 */
अटल irqवापस_t cdns_i2c_isr(पूर्णांक irq, व्योम *ptr)
अणु
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	काष्ठा cdns_i2c *id = ptr;

	अगर (id->dev_mode == CDNS_I2C_MODE_SLAVE)
		वापस cdns_i2c_slave_isr(ptr);
#पूर्ण_अगर
	वापस cdns_i2c_master_isr(ptr);
पूर्ण

/**
 * cdns_i2c_mrecv - Prepare and start a master receive operation
 * @id:		poपूर्णांकer to the i2c device काष्ठाure
 */
अटल व्योम cdns_i2c_mrecv(काष्ठा cdns_i2c *id)
अणु
	अचिन्हित पूर्णांक ctrl_reg;
	अचिन्हित पूर्णांक isr_status;

	id->p_recv_buf = id->p_msg->buf;
	id->recv_count = id->p_msg->len;

	/* Put the controller in master receive mode and clear the FIFO */
	ctrl_reg = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
	ctrl_reg |= CDNS_I2C_CR_RW | CDNS_I2C_CR_CLR_FIFO;

	अगर (id->p_msg->flags & I2C_M_RECV_LEN)
		id->recv_count = I2C_SMBUS_BLOCK_MAX + 1;

	id->curr_recv_count = id->recv_count;

	/*
	 * Check क्रम the message size against FIFO depth and set the
	 * 'hold bus' bit अगर it is greater than FIFO depth.
	 */
	अगर (id->recv_count > CDNS_I2C_FIFO_DEPTH)
		ctrl_reg |= CDNS_I2C_CR_HOLD;

	cdns_i2c_ग_लिखोreg(ctrl_reg, CDNS_I2C_CR_OFFSET);

	/* Clear the पूर्णांकerrupts in पूर्णांकerrupt status रेजिस्टर */
	isr_status = cdns_i2c_पढ़ोreg(CDNS_I2C_ISR_OFFSET);
	cdns_i2c_ग_लिखोreg(isr_status, CDNS_I2C_ISR_OFFSET);

	/*
	 * The no. of bytes to receive is checked against the limit of
	 * max transfer size. Set transfer size रेजिस्टर with no of bytes
	 * receive अगर it is less than transfer size and transfer size अगर
	 * it is more. Enable the पूर्णांकerrupts.
	 */
	अगर (id->recv_count > CDNS_I2C_TRANSFER_SIZE) अणु
		cdns_i2c_ग_लिखोreg(CDNS_I2C_TRANSFER_SIZE,
				  CDNS_I2C_XFER_SIZE_OFFSET);
		id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE;
	पूर्ण अन्यथा अणु
		cdns_i2c_ग_लिखोreg(id->recv_count, CDNS_I2C_XFER_SIZE_OFFSET);
	पूर्ण

	/* Set the slave address in address रेजिस्टर - triggers operation */
	cdns_i2c_ग_लिखोreg(id->p_msg->addr & CDNS_I2C_ADDR_MASK,
						CDNS_I2C_ADDR_OFFSET);
	/* Clear the bus hold flag अगर bytes to receive is less than FIFO size */
	अगर (!id->bus_hold_flag &&
		((id->p_msg->flags & I2C_M_RECV_LEN) != I2C_M_RECV_LEN) &&
		(id->recv_count <= CDNS_I2C_FIFO_DEPTH))
			cdns_i2c_clear_bus_hold(id);
	cdns_i2c_ग_लिखोreg(CDNS_I2C_ENABLED_INTR_MASK, CDNS_I2C_IER_OFFSET);
पूर्ण

/**
 * cdns_i2c_msend - Prepare and start a master send operation
 * @id:		poपूर्णांकer to the i2c device
 */
अटल व्योम cdns_i2c_msend(काष्ठा cdns_i2c *id)
अणु
	अचिन्हित पूर्णांक avail_bytes;
	अचिन्हित पूर्णांक bytes_to_send;
	अचिन्हित पूर्णांक ctrl_reg;
	अचिन्हित पूर्णांक isr_status;

	id->p_recv_buf = शून्य;
	id->p_send_buf = id->p_msg->buf;
	id->send_count = id->p_msg->len;

	/* Set the controller in Master transmit mode and clear the FIFO. */
	ctrl_reg = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
	ctrl_reg &= ~CDNS_I2C_CR_RW;
	ctrl_reg |= CDNS_I2C_CR_CLR_FIFO;

	/*
	 * Check क्रम the message size against FIFO depth and set the
	 * 'hold bus' bit अगर it is greater than FIFO depth.
	 */
	अगर (id->send_count > CDNS_I2C_FIFO_DEPTH)
		ctrl_reg |= CDNS_I2C_CR_HOLD;
	cdns_i2c_ग_लिखोreg(ctrl_reg, CDNS_I2C_CR_OFFSET);

	/* Clear the पूर्णांकerrupts in पूर्णांकerrupt status रेजिस्टर. */
	isr_status = cdns_i2c_पढ़ोreg(CDNS_I2C_ISR_OFFSET);
	cdns_i2c_ग_लिखोreg(isr_status, CDNS_I2C_ISR_OFFSET);

	/*
	 * Calculate the space available in FIFO. Check the message length
	 * against the space available, and fill the FIFO accordingly.
	 * Enable the पूर्णांकerrupts.
	 */
	avail_bytes = CDNS_I2C_FIFO_DEPTH -
				cdns_i2c_पढ़ोreg(CDNS_I2C_XFER_SIZE_OFFSET);

	अगर (id->send_count > avail_bytes)
		bytes_to_send = avail_bytes;
	अन्यथा
		bytes_to_send = id->send_count;

	जबतक (bytes_to_send--) अणु
		cdns_i2c_ग_लिखोreg((*(id->p_send_buf)++), CDNS_I2C_DATA_OFFSET);
		id->send_count--;
	पूर्ण

	/*
	 * Clear the bus hold flag अगर there is no more data
	 * and अगर it is the last message.
	 */
	अगर (!id->bus_hold_flag && !id->send_count)
		cdns_i2c_clear_bus_hold(id);
	/* Set the slave address in address रेजिस्टर - triggers operation. */
	cdns_i2c_ग_लिखोreg(id->p_msg->addr & CDNS_I2C_ADDR_MASK,
						CDNS_I2C_ADDR_OFFSET);

	cdns_i2c_ग_लिखोreg(CDNS_I2C_ENABLED_INTR_MASK, CDNS_I2C_IER_OFFSET);
पूर्ण

/**
 * cdns_i2c_master_reset - Reset the पूर्णांकerface
 * @adap:	poपूर्णांकer to the i2c adapter driver instance
 *
 * This function cleanup the fअगरos, clear the hold bit and status
 * and disable the पूर्णांकerrupts.
 */
अटल व्योम cdns_i2c_master_reset(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा cdns_i2c *id = adap->algo_data;
	u32 regval;

	/* Disable the पूर्णांकerrupts */
	cdns_i2c_ग_लिखोreg(CDNS_I2C_IXR_ALL_INTR_MASK, CDNS_I2C_IDR_OFFSET);
	/* Clear the hold bit and fअगरos */
	regval = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
	regval &= ~CDNS_I2C_CR_HOLD;
	regval |= CDNS_I2C_CR_CLR_FIFO;
	cdns_i2c_ग_लिखोreg(regval, CDNS_I2C_CR_OFFSET);
	/* Update the transfercount रेजिस्टर to zero */
	cdns_i2c_ग_लिखोreg(0, CDNS_I2C_XFER_SIZE_OFFSET);
	/* Clear the पूर्णांकerrupt status रेजिस्टर */
	regval = cdns_i2c_पढ़ोreg(CDNS_I2C_ISR_OFFSET);
	cdns_i2c_ग_लिखोreg(regval, CDNS_I2C_ISR_OFFSET);
	/* Clear the status रेजिस्टर */
	regval = cdns_i2c_पढ़ोreg(CDNS_I2C_SR_OFFSET);
	cdns_i2c_ग_लिखोreg(regval, CDNS_I2C_SR_OFFSET);
पूर्ण

अटल पूर्णांक cdns_i2c_process_msg(काष्ठा cdns_i2c *id, काष्ठा i2c_msg *msg,
		काष्ठा i2c_adapter *adap)
अणु
	अचिन्हित दीर्घ समय_left;
	u32 reg;

	id->p_msg = msg;
	id->err_status = 0;
	reinit_completion(&id->xfer_करोne);

	/* Check क्रम the TEN Bit mode on each msg */
	reg = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
	अगर (msg->flags & I2C_M_TEN) अणु
		अगर (reg & CDNS_I2C_CR_NEA)
			cdns_i2c_ग_लिखोreg(reg & ~CDNS_I2C_CR_NEA,
					CDNS_I2C_CR_OFFSET);
	पूर्ण अन्यथा अणु
		अगर (!(reg & CDNS_I2C_CR_NEA))
			cdns_i2c_ग_लिखोreg(reg | CDNS_I2C_CR_NEA,
					CDNS_I2C_CR_OFFSET);
	पूर्ण

	/* Check क्रम the R/W flag on each msg */
	अगर (msg->flags & I2C_M_RD)
		cdns_i2c_mrecv(id);
	अन्यथा
		cdns_i2c_msend(id);

	/* Wait क्रम the संकेत of completion */
	समय_left = रुको_क्रम_completion_समयout(&id->xfer_करोne, adap->समयout);
	अगर (समय_left == 0) अणु
		cdns_i2c_master_reset(adap);
		dev_err(id->adap.dev.parent,
				"timeout waiting on completion\n");
		वापस -ETIMEDOUT;
	पूर्ण

	cdns_i2c_ग_लिखोreg(CDNS_I2C_IXR_ALL_INTR_MASK,
			  CDNS_I2C_IDR_OFFSET);

	/* If it is bus arbitration error, try again */
	अगर (id->err_status & CDNS_I2C_IXR_ARB_LOST)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

/**
 * cdns_i2c_master_xfer - The मुख्य i2c transfer function
 * @adap:	poपूर्णांकer to the i2c adapter driver instance
 * @msgs:	poपूर्णांकer to the i2c message काष्ठाure
 * @num:	the number of messages to transfer
 *
 * Initiates the send/recv activity based on the transfer message received.
 *
 * Return: number of msgs processed on success, negative error otherwise
 */
अटल पूर्णांक cdns_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	पूर्णांक ret, count;
	u32 reg;
	काष्ठा cdns_i2c *id = adap->algo_data;
	bool hold_quirk;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	bool change_role = false;
#पूर्ण_अगर

	ret = pm_runसमय_resume_and_get(id->dev);
	अगर (ret < 0)
		वापस ret;

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/* Check i2c operating mode and चयन अगर possible */
	अगर (id->dev_mode == CDNS_I2C_MODE_SLAVE) अणु
		अगर (id->slave_state != CDNS_I2C_SLAVE_STATE_IDLE)
			वापस -EAGAIN;

		/* Set mode to master */
		cdns_i2c_set_mode(CDNS_I2C_MODE_MASTER, id);

		/* Mark flag to change role once xfer is completed */
		change_role = true;
	पूर्ण
#पूर्ण_अगर

	/* Check अगर the bus is मुक्त */
	अगर (cdns_i2c_पढ़ोreg(CDNS_I2C_SR_OFFSET) & CDNS_I2C_SR_BA) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	hold_quirk = !!(id->quirks & CDNS_I2C_BROKEN_HOLD_BIT);
	/*
	 * Set the flag to one when multiple messages are to be
	 * processed with a repeated start.
	 */
	अगर (num > 1) अणु
		/*
		 * This controller करोes not give completion पूर्णांकerrupt after a
		 * master receive message अगर HOLD bit is set (repeated start),
		 * resulting in SW समयout. Hence, अगर a receive message is
		 * followed by any other message, an error is वापसed
		 * indicating that this sequence is not supported.
		 */
		क्रम (count = 0; (count < num - 1 && hold_quirk); count++) अणु
			अगर (msgs[count].flags & I2C_M_RD) अणु
				dev_warn(adap->dev.parent,
					 "Can't do repeated start after a receive message\n");
				ret = -EOPNOTSUPP;
				जाओ out;
			पूर्ण
		पूर्ण
		id->bus_hold_flag = 1;
		reg = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
		reg |= CDNS_I2C_CR_HOLD;
		cdns_i2c_ग_लिखोreg(reg, CDNS_I2C_CR_OFFSET);
	पूर्ण अन्यथा अणु
		id->bus_hold_flag = 0;
	पूर्ण

	/* Process the msg one by one */
	क्रम (count = 0; count < num; count++, msgs++) अणु
		अगर (count == (num - 1))
			id->bus_hold_flag = 0;

		ret = cdns_i2c_process_msg(id, msgs, adap);
		अगर (ret)
			जाओ out;

		/* Report the other error पूर्णांकerrupts to application */
		अगर (id->err_status) अणु
			cdns_i2c_master_reset(adap);

			अगर (id->err_status & CDNS_I2C_IXR_NACK) अणु
				ret = -ENXIO;
				जाओ out;
			पूर्ण
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = num;

out:

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/* Switch i2c mode to slave */
	अगर (change_role)
		cdns_i2c_set_mode(CDNS_I2C_MODE_SLAVE, id);
#पूर्ण_अगर

	pm_runसमय_mark_last_busy(id->dev);
	pm_runसमय_put_स्वतःsuspend(id->dev);
	वापस ret;
पूर्ण

/**
 * cdns_i2c_func - Returns the supported features of the I2C driver
 * @adap:	poपूर्णांकer to the i2c adapter काष्ठाure
 *
 * Return: 32 bit value, each bit corresponding to a feature
 */
अटल u32 cdns_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	u32 func = I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR |
			(I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) |
			I2C_FUNC_SMBUS_BLOCK_DATA;

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	func |= I2C_FUNC_SLAVE;
#पूर्ण_अगर

	वापस func;
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
अटल पूर्णांक cdns_reg_slave(काष्ठा i2c_client *slave)
अणु
	पूर्णांक ret;
	काष्ठा cdns_i2c *id = container_of(slave->adapter, काष्ठा cdns_i2c,
									adap);

	अगर (id->slave)
		वापस -EBUSY;

	अगर (slave->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;

	ret = pm_runसमय_resume_and_get(id->dev);
	अगर (ret < 0)
		वापस ret;

	/* Store slave inक्रमmation */
	id->slave = slave;

	/* Enable I2C slave */
	cdns_i2c_set_mode(CDNS_I2C_MODE_SLAVE, id);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा cdns_i2c *id = container_of(slave->adapter, काष्ठा cdns_i2c,
									adap);

	pm_runसमय_put(id->dev);

	/* Remove slave inक्रमmation */
	id->slave = शून्य;

	/* Enable I2C master */
	cdns_i2c_set_mode(CDNS_I2C_MODE_MASTER, id);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_algorithm cdns_i2c_algo = अणु
	.master_xfer	= cdns_i2c_master_xfer,
	.functionality	= cdns_i2c_func,
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	.reg_slave	= cdns_reg_slave,
	.unreg_slave	= cdns_unreg_slave,
#पूर्ण_अगर
पूर्ण;

/**
 * cdns_i2c_calc_भागs - Calculate घड़ी भागiders
 * @f:		I2C घड़ी frequency
 * @input_clk:	Input घड़ी frequency
 * @a:		First भागider (वापस value)
 * @b:		Second भागider (वापस value)
 *
 * f is used as input and output variable. As input it is used as target I2C
 * frequency. On function निकास f holds the actually resulting I2C frequency.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक cdns_i2c_calc_भागs(अचिन्हित दीर्घ *f, अचिन्हित दीर्घ input_clk,
		अचिन्हित पूर्णांक *a, अचिन्हित पूर्णांक *b)
अणु
	अचिन्हित दीर्घ fscl = *f, best_fscl = *f, actual_fscl, temp;
	अचिन्हित पूर्णांक भाग_a, भाग_b, calc_भाग_a = 0, calc_भाग_b = 0;
	अचिन्हित पूर्णांक last_error, current_error;

	/* calculate (भागisor_a+1) x (भागisor_b+1) */
	temp = input_clk / (22 * fscl);

	/*
	 * If the calculated value is negative or 0, the fscl input is out of
	 * range. Return error.
	 */
	अगर (!temp || (temp > (CDNS_I2C_DIVA_MAX * CDNS_I2C_DIVB_MAX)))
		वापस -EINVAL;

	last_error = -1;
	क्रम (भाग_a = 0; भाग_a < CDNS_I2C_DIVA_MAX; भाग_a++) अणु
		भाग_b = DIV_ROUND_UP(input_clk, 22 * fscl * (भाग_a + 1));

		अगर ((भाग_b < 1) || (भाग_b > CDNS_I2C_DIVB_MAX))
			जारी;
		भाग_b--;

		actual_fscl = input_clk / (22 * (भाग_a + 1) * (भाग_b + 1));

		अगर (actual_fscl > fscl)
			जारी;

		current_error = ((actual_fscl > fscl) ? (actual_fscl - fscl) :
							(fscl - actual_fscl));

		अगर (last_error > current_error) अणु
			calc_भाग_a = भाग_a;
			calc_भाग_b = भाग_b;
			best_fscl = actual_fscl;
			last_error = current_error;
		पूर्ण
	पूर्ण

	*a = calc_भाग_a;
	*b = calc_भाग_b;
	*f = best_fscl;

	वापस 0;
पूर्ण

/**
 * cdns_i2c_setclk - This function sets the serial घड़ी rate क्रम the I2C device
 * @clk_in:	I2C घड़ी input frequency in Hz
 * @id:		Poपूर्णांकer to the I2C device काष्ठाure
 *
 * The device must be idle rather than busy transferring data beक्रमe setting
 * these device options.
 * The data rate is set by values in the control रेजिस्टर.
 * The क्रमmula क्रम determining the correct रेजिस्टर values is
 *	Fscl = Fpclk/(22 x (भागisor_a+1) x (भागisor_b+1))
 * See the hardware data sheet क्रम a full explanation of setting the serial
 * घड़ी rate. The घड़ी can not be faster than the input घड़ी भागide by 22.
 * The two most common घड़ी rates are 100KHz and 400KHz.
 *
 * Return: 0 on success, negative error otherwise
 */
अटल पूर्णांक cdns_i2c_setclk(अचिन्हित दीर्घ clk_in, काष्ठा cdns_i2c *id)
अणु
	अचिन्हित पूर्णांक भाग_a, भाग_b;
	अचिन्हित पूर्णांक ctrl_reg;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ fscl = id->i2c_clk;

	ret = cdns_i2c_calc_भागs(&fscl, clk_in, &भाग_a, &भाग_b);
	अगर (ret)
		वापस ret;

	ctrl_reg = cdns_i2c_पढ़ोreg(CDNS_I2C_CR_OFFSET);
	ctrl_reg &= ~(CDNS_I2C_CR_DIVA_MASK | CDNS_I2C_CR_DIVB_MASK);
	ctrl_reg |= ((भाग_a << CDNS_I2C_CR_DIVA_SHIFT) |
			(भाग_b << CDNS_I2C_CR_DIVB_SHIFT));
	cdns_i2c_ग_लिखोreg(ctrl_reg, CDNS_I2C_CR_OFFSET);
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	id->ctrl_reg_भागa_भागb = ctrl_reg & (CDNS_I2C_CR_DIVA_MASK |
				 CDNS_I2C_CR_DIVB_MASK);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * cdns_i2c_clk_notअगरier_cb - Clock rate change callback
 * @nb:		Poपूर्णांकer to notअगरier block
 * @event:	Notअगरication reason
 * @data:	Poपूर्णांकer to notअगरication data object
 *
 * This function is called when the cdns_i2c input घड़ी frequency changes.
 * The callback checks whether a valid bus frequency can be generated after the
 * change. If so, the change is acknowledged, otherwise the change is पातed.
 * New भागiders are written to the HW in the pre- or post change notअगरication
 * depending on the scaling direction.
 *
 * Return:	NOTIFY_STOP अगर the rate change should be पातed, NOTIFY_OK
 *		to acknowledge the change, NOTIFY_DONE अगर the notअगरication is
 *		considered irrelevant.
 */
अटल पूर्णांक cdns_i2c_clk_notअगरier_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ
		event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा cdns_i2c *id = to_cdns_i2c(nb);

	अगर (pm_runसमय_suspended(id->dev))
		वापस NOTIFY_OK;

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
	अणु
		अचिन्हित दीर्घ input_clk = ndata->new_rate;
		अचिन्हित दीर्घ fscl = id->i2c_clk;
		अचिन्हित पूर्णांक भाग_a, भाग_b;
		पूर्णांक ret;

		ret = cdns_i2c_calc_भागs(&fscl, input_clk, &भाग_a, &भाग_b);
		अगर (ret) अणु
			dev_warn(id->adap.dev.parent,
					"clock rate change rejected\n");
			वापस NOTIFY_STOP;
		पूर्ण

		/* scale up */
		अगर (ndata->new_rate > ndata->old_rate)
			cdns_i2c_setclk(ndata->new_rate, id);

		वापस NOTIFY_OK;
	पूर्ण
	हाल POST_RATE_CHANGE:
		id->input_clk = ndata->new_rate;
		/* scale करोwn */
		अगर (ndata->new_rate < ndata->old_rate)
			cdns_i2c_setclk(ndata->new_rate, id);
		वापस NOTIFY_OK;
	हाल ABORT_RATE_CHANGE:
		/* scale up */
		अगर (ndata->new_rate > ndata->old_rate)
			cdns_i2c_setclk(ndata->old_rate, id);
		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

/**
 * cdns_i2c_runसमय_suspend -  Runसमय suspend method क्रम the driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * Put the driver पूर्णांकo low घातer mode.
 *
 * Return: 0 always
 */
अटल पूर्णांक __maybe_unused cdns_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns_i2c *xi2c = dev_get_drvdata(dev);

	clk_disable(xi2c->clk);

	वापस 0;
पूर्ण

/**
 * cdns_i2c_runसमय_resume - Runसमय resume
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * Runसमय resume callback.
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक __maybe_unused cdns_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cdns_i2c *xi2c = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(xi2c->clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable clock.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cdns_i2c_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(cdns_i2c_runसमय_suspend,
			   cdns_i2c_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा cdns_platक्रमm_data r1p10_i2c_def = अणु
	.quirks = CDNS_I2C_BROKEN_HOLD_BIT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_i2c_of_match[] = अणु
	अणु .compatible = "cdns,i2c-r1p10", .data = &r1p10_i2c_def पूर्ण,
	अणु .compatible = "cdns,i2c-r1p14",पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_i2c_of_match);

/**
 * cdns_i2c_probe - Platक्रमm registration call
 * @pdev:	Handle to the platक्रमm device काष्ठाure
 *
 * This function करोes all the memory allocation and registration क्रम the i2c
 * device. User can modअगरy the address mode to 10 bit address mode using the
 * ioctl call with option I2C_TENBIT.
 *
 * Return: 0 on success, negative error otherwise
 */
अटल पूर्णांक cdns_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r_mem;
	काष्ठा cdns_i2c *id;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;

	id = devm_kzalloc(&pdev->dev, माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस -ENOMEM;

	id->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, id);

	match = of_match_node(cdns_i2c_of_match, pdev->dev.of_node);
	अगर (match && match->data) अणु
		स्थिर काष्ठा cdns_platक्रमm_data *data = match->data;
		id->quirks = data->quirks;
	पूर्ण

	id->membase = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &r_mem);
	अगर (IS_ERR(id->membase))
		वापस PTR_ERR(id->membase);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	id->irq = ret;

	id->adap.owner = THIS_MODULE;
	id->adap.dev.of_node = pdev->dev.of_node;
	id->adap.algo = &cdns_i2c_algo;
	id->adap.समयout = CDNS_I2C_TIMEOUT;
	id->adap.retries = 3;		/* Default retry value. */
	id->adap.algo_data = id;
	id->adap.dev.parent = &pdev->dev;
	init_completion(&id->xfer_करोne);
	snम_लिखो(id->adap.name, माप(id->adap.name),
		 "Cadence I2C at %08lx", (अचिन्हित दीर्घ)r_mem->start);

	id->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(id->clk)) अणु
		अगर (PTR_ERR(id->clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "input clock not found.\n");
		वापस PTR_ERR(id->clk);
	पूर्ण
	ret = clk_prepare_enable(id->clk);
	अगर (ret)
		dev_err(&pdev->dev, "Unable to enable clock.\n");

	pm_runसमय_set_स्वतःsuspend_delay(id->dev, CNDS_I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(id->dev);
	pm_runसमय_set_active(id->dev);
	pm_runसमय_enable(id->dev);

	id->clk_rate_change_nb.notअगरier_call = cdns_i2c_clk_notअगरier_cb;
	अगर (clk_notअगरier_रेजिस्टर(id->clk, &id->clk_rate_change_nb))
		dev_warn(&pdev->dev, "Unable to register clock notifier.\n");
	id->input_clk = clk_get_rate(id->clk);

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
			&id->i2c_clk);
	अगर (ret || (id->i2c_clk > I2C_MAX_FAST_MODE_FREQ))
		id->i2c_clk = I2C_MAX_STANDARD_MODE_FREQ;

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/* Set initial mode to master */
	id->dev_mode = CDNS_I2C_MODE_MASTER;
	id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
#पूर्ण_अगर
	cdns_i2c_ग_लिखोreg(CDNS_I2C_CR_MASTER_EN_MASK, CDNS_I2C_CR_OFFSET);

	ret = cdns_i2c_setclk(id->input_clk, id);
	अगर (ret) अणु
		dev_err(&pdev->dev, "invalid SCL clock: %u Hz\n", id->i2c_clk);
		ret = -EINVAL;
		जाओ err_clk_dis;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, id->irq, cdns_i2c_isr, 0,
				 DRIVER_NAME, id);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot get irq %d\n", id->irq);
		जाओ err_clk_dis;
	पूर्ण

	/*
	 * Cadence I2C controller has a bug wherein it generates
	 * invalid पढ़ो transaction after HW समयout in master receiver mode.
	 * HW समयout is not used by this driver and the पूर्णांकerrupt is disabled.
	 * But the feature itself cannot be disabled. Hence maximum value
	 * is written to this रेजिस्टर to reduce the chances of error.
	 */
	cdns_i2c_ग_लिखोreg(CDNS_I2C_TIMEOUT_MAX, CDNS_I2C_TIME_OUT_OFFSET);

	ret = i2c_add_adapter(&id->adap);
	अगर (ret < 0)
		जाओ err_clk_dis;

	dev_info(&pdev->dev, "%u kHz mmio %08lx irq %d\n",
		 id->i2c_clk / 1000, (अचिन्हित दीर्घ)r_mem->start, id->irq);

	वापस 0;

err_clk_dis:
	clk_disable_unprepare(id->clk);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	वापस ret;
पूर्ण

/**
 * cdns_i2c_हटाओ - Unरेजिस्टर the device after releasing the resources
 * @pdev:	Handle to the platक्रमm device काष्ठाure
 *
 * This function मुक्तs all the resources allocated to the device.
 *
 * Return: 0 always
 */
अटल पूर्णांक cdns_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_i2c *id = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);

	i2c_del_adapter(&id->adap);
	clk_notअगरier_unरेजिस्टर(id->clk, &id->clk_rate_change_nb);
	clk_disable_unprepare(id->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cdns_i2c_drv = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
		.of_match_table = cdns_i2c_of_match,
		.pm = &cdns_i2c_dev_pm_ops,
	पूर्ण,
	.probe  = cdns_i2c_probe,
	.हटाओ = cdns_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(cdns_i2c_drv);

MODULE_AUTHOR("Xilinx Inc.");
MODULE_DESCRIPTION("Cadence I2C bus driver");
MODULE_LICENSE("GPL");
