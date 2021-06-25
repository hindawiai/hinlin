<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c-xiic.c
 * Copyright (c) 2002-2007 Xilinx Inc.
 * Copyright (c) 2009-2010 Intel Corporation
 *
 * This code was implemented by Mocean Laboratories AB when porting linux
 * to the स्वतःmotive development board Russellville. The copyright holder
 * as seen in the header is Intel corporation.
 * Mocean Laboratories विभाजनed off the GNU/Linux platक्रमm work पूर्णांकo a
 * separate company called Pelagicore AB, which committed the code to the
 * kernel.
 */

/* Supports:
 * Xilinx IIC
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/platक्रमm_data/i2c-xiic.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा DRIVER_NAME "xiic-i2c"

क्रमागत xilinx_i2c_state अणु
	STATE_DONE,
	STATE_ERROR,
	STATE_START
पूर्ण;

क्रमागत xiic_endian अणु
	LITTLE,
	BIG
पूर्ण;

/**
 * काष्ठा xiic_i2c - Internal representation of the XIIC I2C bus
 * @dev: Poपूर्णांकer to device काष्ठाure
 * @base: Memory base of the HW रेजिस्टरs
 * @रुको: Wait queue क्रम callers
 * @adap: Kernel adapter representation
 * @tx_msg: Messages from above to be sent
 * @lock: Mutual exclusion
 * @tx_pos: Current pos in TX message
 * @nmsgs: Number of messages in tx_msg
 * @rx_msg: Current RX message
 * @rx_pos: Position within current RX message
 * @endianness: big/little-endian byte order
 * @clk: Poपूर्णांकer to AXI4-lite input घड़ी
 * @state: See STATE_
 * @singlemaster: Indicates bus is single master
 */
काष्ठा xiic_i2c अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	रुको_queue_head_t रुको;
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_msg *tx_msg;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक tx_pos;
	अचिन्हित पूर्णांक nmsgs;
	काष्ठा i2c_msg *rx_msg;
	पूर्णांक rx_pos;
	क्रमागत xiic_endian endianness;
	काष्ठा clk *clk;
	क्रमागत xilinx_i2c_state state;
	bool singlemaster;
पूर्ण;


#घोषणा XIIC_MSB_OFFSET 0
#घोषणा XIIC_REG_OFFSET (0x100+XIIC_MSB_OFFSET)

/*
 * Register offsets in bytes from RegisterBase. Three is added to the
 * base offset to access LSB (IBM style) of the word
 */
#घोषणा XIIC_CR_REG_OFFSET   (0x00+XIIC_REG_OFFSET)	/* Control Register   */
#घोषणा XIIC_SR_REG_OFFSET   (0x04+XIIC_REG_OFFSET)	/* Status Register    */
#घोषणा XIIC_DTR_REG_OFFSET  (0x08+XIIC_REG_OFFSET)	/* Data Tx Register   */
#घोषणा XIIC_DRR_REG_OFFSET  (0x0C+XIIC_REG_OFFSET)	/* Data Rx Register   */
#घोषणा XIIC_ADR_REG_OFFSET  (0x10+XIIC_REG_OFFSET)	/* Address Register   */
#घोषणा XIIC_TFO_REG_OFFSET  (0x14+XIIC_REG_OFFSET)	/* Tx FIFO Occupancy  */
#घोषणा XIIC_RFO_REG_OFFSET  (0x18+XIIC_REG_OFFSET)	/* Rx FIFO Occupancy  */
#घोषणा XIIC_TBA_REG_OFFSET  (0x1C+XIIC_REG_OFFSET)	/* 10 Bit Address reg */
#घोषणा XIIC_RFD_REG_OFFSET  (0x20+XIIC_REG_OFFSET)	/* Rx FIFO Depth reg  */
#घोषणा XIIC_GPO_REG_OFFSET  (0x24+XIIC_REG_OFFSET)	/* Output Register    */

/* Control Register masks */
#घोषणा XIIC_CR_ENABLE_DEVICE_MASK        0x01	/* Device enable = 1      */
#घोषणा XIIC_CR_TX_FIFO_RESET_MASK        0x02	/* Transmit FIFO reset=1  */
#घोषणा XIIC_CR_MSMS_MASK                 0x04	/* Master starts Txing=1  */
#घोषणा XIIC_CR_सूची_IS_TX_MASK            0x08	/* Dir of tx. Txing=1     */
#घोषणा XIIC_CR_NO_ACK_MASK               0x10	/* Tx Ack. NO ack = 1     */
#घोषणा XIIC_CR_REPEATED_START_MASK       0x20	/* Repeated start = 1     */
#घोषणा XIIC_CR_GENERAL_CALL_MASK         0x40	/* Gen Call enabled = 1   */

/* Status Register masks */
#घोषणा XIIC_SR_GEN_CALL_MASK             0x01	/* 1=a mstr issued a GC   */
#घोषणा XIIC_SR_ADDR_AS_SLAVE_MASK        0x02	/* 1=when addr as slave   */
#घोषणा XIIC_SR_BUS_BUSY_MASK             0x04	/* 1 = bus is busy        */
#घोषणा XIIC_SR_MSTR_RDING_SLAVE_MASK     0x08	/* 1=Dir: mstr <-- slave  */
#घोषणा XIIC_SR_TX_FIFO_FULL_MASK         0x10	/* 1 = Tx FIFO full       */
#घोषणा XIIC_SR_RX_FIFO_FULL_MASK         0x20	/* 1 = Rx FIFO full       */
#घोषणा XIIC_SR_RX_FIFO_EMPTY_MASK        0x40	/* 1 = Rx FIFO empty      */
#घोषणा XIIC_SR_TX_FIFO_EMPTY_MASK        0x80	/* 1 = Tx FIFO empty      */

/* Interrupt Status Register masks    Interrupt occurs when...       */
#घोषणा XIIC_INTR_ARB_LOST_MASK           0x01	/* 1 = arbitration lost   */
#घोषणा XIIC_INTR_TX_ERROR_MASK           0x02	/* 1=Tx error/msg complete */
#घोषणा XIIC_INTR_TX_EMPTY_MASK           0x04	/* 1 = Tx FIFO/reg empty  */
#घोषणा XIIC_INTR_RX_FULL_MASK            0x08	/* 1=Rx FIFO/reg=OCY level */
#घोषणा XIIC_INTR_BNB_MASK                0x10	/* 1 = Bus not busy       */
#घोषणा XIIC_INTR_AAS_MASK                0x20	/* 1 = when addr as slave */
#घोषणा XIIC_INTR_NAAS_MASK               0x40	/* 1 = not addr as slave  */
#घोषणा XIIC_INTR_TX_HALF_MASK            0x80	/* 1 = TX FIFO half empty */

/* The following स्थिरants specअगरy the depth of the FIFOs */
#घोषणा IIC_RX_FIFO_DEPTH         16	/* Rx fअगरo capacity               */
#घोषणा IIC_TX_FIFO_DEPTH         16	/* Tx fअगरo capacity               */

/* The following स्थिरants specअगरy groups of पूर्णांकerrupts that are typically
 * enabled or disables at the same समय
 */
#घोषणा XIIC_TX_INTERRUPTS                           \
(XIIC_INTR_TX_ERROR_MASK | XIIC_INTR_TX_EMPTY_MASK | XIIC_INTR_TX_HALF_MASK)

#घोषणा XIIC_TX_RX_INTERRUPTS (XIIC_INTR_RX_FULL_MASK | XIIC_TX_INTERRUPTS)

/*
 * Tx Fअगरo upper bit masks.
 */
#घोषणा XIIC_TX_DYN_START_MASK            0x0100 /* 1 = Set dynamic start */
#घोषणा XIIC_TX_DYN_STOP_MASK             0x0200 /* 1 = Set dynamic stop */

/*
 * The following स्थिरants define the रेजिस्टर offsets क्रम the Interrupt
 * रेजिस्टरs. There are some holes in the memory map क्रम reserved addresses
 * to allow other रेजिस्टरs to be added and still match the memory map of the
 * पूर्णांकerrupt controller रेजिस्टरs
 */
#घोषणा XIIC_DGIER_OFFSET    0x1C /* Device Global Interrupt Enable Register */
#घोषणा XIIC_IISR_OFFSET     0x20 /* Interrupt Status Register */
#घोषणा XIIC_IIER_OFFSET     0x28 /* Interrupt Enable Register */
#घोषणा XIIC_RESETR_OFFSET   0x40 /* Reset Register */

#घोषणा XIIC_RESET_MASK             0xAUL

#घोषणा XIIC_PM_TIMEOUT		1000	/* ms */
/* समयout रुकोing क्रम the controller to respond */
#घोषणा XIIC_I2C_TIMEOUT	(msecs_to_jअगरfies(1000))
/*
 * The following स्थिरant is used क्रम the device global पूर्णांकerrupt enable
 * रेजिस्टर, to enable all पूर्णांकerrupts क्रम the device, this is the only bit
 * in the रेजिस्टर
 */
#घोषणा XIIC_GINTR_ENABLE_MASK      0x80000000UL

#घोषणा xiic_tx_space(i2c) ((i2c)->tx_msg->len - (i2c)->tx_pos)
#घोषणा xiic_rx_space(i2c) ((i2c)->rx_msg->len - (i2c)->rx_pos)

अटल पूर्णांक xiic_start_xfer(काष्ठा xiic_i2c *i2c);
अटल व्योम __xiic_start_xfer(काष्ठा xiic_i2c *i2c);

/*
 * For the रेजिस्टर पढ़ो and ग_लिखो functions, a little-endian and big-endian
 * version are necessary. Endianness is detected during the probe function.
 * Only the least signअगरicant byte [द्विगुनt] of the रेजिस्टर are ever
 * accessed. This requires an offset of 3 [2] from the base address क्रम
 * big-endian प्रणालीs.
 */

अटल अंतरभूत व्योम xiic_setreg8(काष्ठा xiic_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	अगर (i2c->endianness == LITTLE)
		ioग_लिखो8(value, i2c->base + reg);
	अन्यथा
		ioग_लिखो8(value, i2c->base + reg + 3);
पूर्ण

अटल अंतरभूत u8 xiic_getreg8(काष्ठा xiic_i2c *i2c, पूर्णांक reg)
अणु
	u8 ret;

	अगर (i2c->endianness == LITTLE)
		ret = ioपढ़ो8(i2c->base + reg);
	अन्यथा
		ret = ioपढ़ो8(i2c->base + reg + 3);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम xiic_setreg16(काष्ठा xiic_i2c *i2c, पूर्णांक reg, u16 value)
अणु
	अगर (i2c->endianness == LITTLE)
		ioग_लिखो16(value, i2c->base + reg);
	अन्यथा
		ioग_लिखो16be(value, i2c->base + reg + 2);
पूर्ण

अटल अंतरभूत व्योम xiic_setreg32(काष्ठा xiic_i2c *i2c, पूर्णांक reg, पूर्णांक value)
अणु
	अगर (i2c->endianness == LITTLE)
		ioग_लिखो32(value, i2c->base + reg);
	अन्यथा
		ioग_लिखो32be(value, i2c->base + reg);
पूर्ण

अटल अंतरभूत पूर्णांक xiic_getreg32(काष्ठा xiic_i2c *i2c, पूर्णांक reg)
अणु
	u32 ret;

	अगर (i2c->endianness == LITTLE)
		ret = ioपढ़ो32(i2c->base + reg);
	अन्यथा
		ret = ioपढ़ो32be(i2c->base + reg);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम xiic_irq_dis(काष्ठा xiic_i2c *i2c, u32 mask)
अणु
	u32 ier = xiic_getreg32(i2c, XIIC_IIER_OFFSET);
	xiic_setreg32(i2c, XIIC_IIER_OFFSET, ier & ~mask);
पूर्ण

अटल अंतरभूत व्योम xiic_irq_en(काष्ठा xiic_i2c *i2c, u32 mask)
अणु
	u32 ier = xiic_getreg32(i2c, XIIC_IIER_OFFSET);
	xiic_setreg32(i2c, XIIC_IIER_OFFSET, ier | mask);
पूर्ण

अटल अंतरभूत व्योम xiic_irq_clr(काष्ठा xiic_i2c *i2c, u32 mask)
अणु
	u32 isr = xiic_getreg32(i2c, XIIC_IISR_OFFSET);
	xiic_setreg32(i2c, XIIC_IISR_OFFSET, isr & mask);
पूर्ण

अटल अंतरभूत व्योम xiic_irq_clr_en(काष्ठा xiic_i2c *i2c, u32 mask)
अणु
	xiic_irq_clr(i2c, mask);
	xiic_irq_en(i2c, mask);
पूर्ण

अटल पूर्णांक xiic_clear_rx_fअगरo(काष्ठा xiic_i2c *i2c)
अणु
	u8 sr;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + XIIC_I2C_TIMEOUT;
	क्रम (sr = xiic_getreg8(i2c, XIIC_SR_REG_OFFSET);
		!(sr & XIIC_SR_RX_FIFO_EMPTY_MASK);
		sr = xiic_getreg8(i2c, XIIC_SR_REG_OFFSET)) अणु
		xiic_getreg8(i2c, XIIC_DRR_REG_OFFSET);
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(i2c->dev, "Failed to clear rx fifo\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xiic_reinit(काष्ठा xiic_i2c *i2c)
अणु
	पूर्णांक ret;

	xiic_setreg32(i2c, XIIC_RESETR_OFFSET, XIIC_RESET_MASK);

	/* Set receive Fअगरo depth to maximum (zero based). */
	xiic_setreg8(i2c, XIIC_RFD_REG_OFFSET, IIC_RX_FIFO_DEPTH - 1);

	/* Reset Tx Fअगरo. */
	xiic_setreg8(i2c, XIIC_CR_REG_OFFSET, XIIC_CR_TX_FIFO_RESET_MASK);

	/* Enable IIC Device, हटाओ Tx Fअगरo reset & disable general call. */
	xiic_setreg8(i2c, XIIC_CR_REG_OFFSET, XIIC_CR_ENABLE_DEVICE_MASK);

	/* make sure RX fअगरo is empty */
	ret = xiic_clear_rx_fअगरo(i2c);
	अगर (ret)
		वापस ret;

	/* Enable पूर्णांकerrupts */
	xiic_setreg32(i2c, XIIC_DGIER_OFFSET, XIIC_GINTR_ENABLE_MASK);

	xiic_irq_clr_en(i2c, XIIC_INTR_ARB_LOST_MASK);

	वापस 0;
पूर्ण

अटल व्योम xiic_deinit(काष्ठा xiic_i2c *i2c)
अणु
	u8 cr;

	xiic_setreg32(i2c, XIIC_RESETR_OFFSET, XIIC_RESET_MASK);

	/* Disable IIC Device. */
	cr = xiic_getreg8(i2c, XIIC_CR_REG_OFFSET);
	xiic_setreg8(i2c, XIIC_CR_REG_OFFSET, cr & ~XIIC_CR_ENABLE_DEVICE_MASK);
पूर्ण

अटल व्योम xiic_पढ़ो_rx(काष्ठा xiic_i2c *i2c)
अणु
	u8 bytes_in_fअगरo;
	पूर्णांक i;

	bytes_in_fअगरo = xiic_getreg8(i2c, XIIC_RFO_REG_OFFSET) + 1;

	dev_dbg(i2c->adap.dev.parent,
		"%s entry, bytes in fifo: %d, msg: %d, SR: 0x%x, CR: 0x%x\n",
		__func__, bytes_in_fअगरo, xiic_rx_space(i2c),
		xiic_getreg8(i2c, XIIC_SR_REG_OFFSET),
		xiic_getreg8(i2c, XIIC_CR_REG_OFFSET));

	अगर (bytes_in_fअगरo > xiic_rx_space(i2c))
		bytes_in_fअगरo = xiic_rx_space(i2c);

	क्रम (i = 0; i < bytes_in_fअगरo; i++)
		i2c->rx_msg->buf[i2c->rx_pos++] =
			xiic_getreg8(i2c, XIIC_DRR_REG_OFFSET);

	xiic_setreg8(i2c, XIIC_RFD_REG_OFFSET,
		(xiic_rx_space(i2c) > IIC_RX_FIFO_DEPTH) ?
		IIC_RX_FIFO_DEPTH - 1 :  xiic_rx_space(i2c) - 1);
पूर्ण

अटल पूर्णांक xiic_tx_fअगरo_space(काष्ठा xiic_i2c *i2c)
अणु
	/* वापस the actual space left in the FIFO */
	वापस IIC_TX_FIFO_DEPTH - xiic_getreg8(i2c, XIIC_TFO_REG_OFFSET) - 1;
पूर्ण

अटल व्योम xiic_fill_tx_fअगरo(काष्ठा xiic_i2c *i2c)
अणु
	u8 fअगरo_space = xiic_tx_fअगरo_space(i2c);
	पूर्णांक len = xiic_tx_space(i2c);

	len = (len > fअगरo_space) ? fअगरo_space : len;

	dev_dbg(i2c->adap.dev.parent, "%s entry, len: %d, fifo space: %d\n",
		__func__, len, fअगरo_space);

	जबतक (len--) अणु
		u16 data = i2c->tx_msg->buf[i2c->tx_pos++];
		अगर ((xiic_tx_space(i2c) == 0) && (i2c->nmsgs == 1)) अणु
			/* last message in transfer -> STOP */
			data |= XIIC_TX_DYN_STOP_MASK;
			dev_dbg(i2c->adap.dev.parent, "%s TX STOP\n", __func__);
		पूर्ण
		xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET, data);
	पूर्ण
पूर्ण

अटल व्योम xiic_wakeup(काष्ठा xiic_i2c *i2c, पूर्णांक code)
अणु
	i2c->tx_msg = शून्य;
	i2c->rx_msg = शून्य;
	i2c->nmsgs = 0;
	i2c->state = code;
	wake_up(&i2c->रुको);
पूर्ण

अटल irqवापस_t xiic_process(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xiic_i2c *i2c = dev_id;
	u32 pend, isr, ier;
	u32 clr = 0;

	/* Get the पूर्णांकerrupt Status from the IPIF. There is no clearing of
	 * पूर्णांकerrupts in the IPIF. Interrupts must be cleared at the source.
	 * To find which पूर्णांकerrupts are pending; AND पूर्णांकerrupts pending with
	 * पूर्णांकerrupts masked.
	 */
	mutex_lock(&i2c->lock);
	isr = xiic_getreg32(i2c, XIIC_IISR_OFFSET);
	ier = xiic_getreg32(i2c, XIIC_IIER_OFFSET);
	pend = isr & ier;

	dev_dbg(i2c->adap.dev.parent, "%s: IER: 0x%x, ISR: 0x%x, pend: 0x%x\n",
		__func__, ier, isr, pend);
	dev_dbg(i2c->adap.dev.parent, "%s: SR: 0x%x, msg: %p, nmsgs: %d\n",
		__func__, xiic_getreg8(i2c, XIIC_SR_REG_OFFSET),
		i2c->tx_msg, i2c->nmsgs);


	/* Service requesting पूर्णांकerrupt */
	अगर ((pend & XIIC_INTR_ARB_LOST_MASK) ||
		((pend & XIIC_INTR_TX_ERROR_MASK) &&
		!(pend & XIIC_INTR_RX_FULL_MASK))) अणु
		/* bus arbritration lost, or...
		 * Transmit error _OR_ RX completed
		 * अगर this happens when RX_FULL is not set
		 * this is probably a TX error
		 */

		dev_dbg(i2c->adap.dev.parent, "%s error\n", __func__);

		/* dynamic mode seem to suffer from problems अगर we just flushes
		 * fअगरos and the next message is a TX with len 0 (only addr)
		 * reset the IP instead of just flush fअगरos
		 */
		xiic_reinit(i2c);

		अगर (i2c->rx_msg)
			xiic_wakeup(i2c, STATE_ERROR);
		अगर (i2c->tx_msg)
			xiic_wakeup(i2c, STATE_ERROR);
	पूर्ण
	अगर (pend & XIIC_INTR_RX_FULL_MASK) अणु
		/* Receive रेजिस्टर/FIFO is full */

		clr |= XIIC_INTR_RX_FULL_MASK;
		अगर (!i2c->rx_msg) अणु
			dev_dbg(i2c->adap.dev.parent,
				"%s unexpected RX IRQ\n", __func__);
			xiic_clear_rx_fअगरo(i2c);
			जाओ out;
		पूर्ण

		xiic_पढ़ो_rx(i2c);
		अगर (xiic_rx_space(i2c) == 0) अणु
			/* this is the last part of the message */
			i2c->rx_msg = शून्य;

			/* also clear TX error अगर there (RX complete) */
			clr |= (isr & XIIC_INTR_TX_ERROR_MASK);

			dev_dbg(i2c->adap.dev.parent,
				"%s end of message, nmsgs: %d\n",
				__func__, i2c->nmsgs);

			/* send next message अगर this wasn't the last,
			 * otherwise the transfer will be finialise when
			 * receiving the bus not busy पूर्णांकerrupt
			 */
			अगर (i2c->nmsgs > 1) अणु
				i2c->nmsgs--;
				i2c->tx_msg++;
				dev_dbg(i2c->adap.dev.parent,
					"%s will start next...\n", __func__);

				__xiic_start_xfer(i2c);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (pend & XIIC_INTR_BNB_MASK) अणु
		/* IIC bus has transitioned to not busy */
		clr |= XIIC_INTR_BNB_MASK;

		/* The bus is not busy, disable BusNotBusy पूर्णांकerrupt */
		xiic_irq_dis(i2c, XIIC_INTR_BNB_MASK);

		अगर (!i2c->tx_msg)
			जाओ out;

		अगर ((i2c->nmsgs == 1) && !i2c->rx_msg &&
			xiic_tx_space(i2c) == 0)
			xiic_wakeup(i2c, STATE_DONE);
		अन्यथा
			xiic_wakeup(i2c, STATE_ERROR);
	पूर्ण
	अगर (pend & (XIIC_INTR_TX_EMPTY_MASK | XIIC_INTR_TX_HALF_MASK)) अणु
		/* Transmit रेजिस्टर/FIFO is empty or तट empty */

		clr |= (pend &
			(XIIC_INTR_TX_EMPTY_MASK | XIIC_INTR_TX_HALF_MASK));

		अगर (!i2c->tx_msg) अणु
			dev_dbg(i2c->adap.dev.parent,
				"%s unexpected TX IRQ\n", __func__);
			जाओ out;
		पूर्ण

		xiic_fill_tx_fअगरo(i2c);

		/* current message sent and there is space in the fअगरo */
		अगर (!xiic_tx_space(i2c) && xiic_tx_fअगरo_space(i2c) >= 2) अणु
			dev_dbg(i2c->adap.dev.parent,
				"%s end of message sent, nmsgs: %d\n",
				__func__, i2c->nmsgs);
			अगर (i2c->nmsgs > 1) अणु
				i2c->nmsgs--;
				i2c->tx_msg++;
				__xiic_start_xfer(i2c);
			पूर्ण अन्यथा अणु
				xiic_irq_dis(i2c, XIIC_INTR_TX_HALF_MASK);

				dev_dbg(i2c->adap.dev.parent,
					"%s Got TX IRQ but no more to do...\n",
					__func__);
			पूर्ण
		पूर्ण अन्यथा अगर (!xiic_tx_space(i2c) && (i2c->nmsgs == 1))
			/* current frame is sent and is last,
			 * make sure to disable tx half
			 */
			xiic_irq_dis(i2c, XIIC_INTR_TX_HALF_MASK);
	पूर्ण
out:
	dev_dbg(i2c->adap.dev.parent, "%s clr: 0x%x\n", __func__, clr);

	xiic_setreg32(i2c, XIIC_IISR_OFFSET, clr);
	mutex_unlock(&i2c->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xiic_bus_busy(काष्ठा xiic_i2c *i2c)
अणु
	u8 sr = xiic_getreg8(i2c, XIIC_SR_REG_OFFSET);

	वापस (sr & XIIC_SR_BUS_BUSY_MASK) ? -EBUSY : 0;
पूर्ण

अटल पूर्णांक xiic_busy(काष्ठा xiic_i2c *i2c)
अणु
	पूर्णांक tries = 3;
	पूर्णांक err;

	अगर (i2c->tx_msg)
		वापस -EBUSY;

	/* In single master mode bus can only be busy, when in use by this
	 * driver. If the रेजिस्टर indicates bus being busy क्रम some reason we
	 * should ignore it, since bus will never be released and i2c will be
	 * stuck क्रमever.
	 */
	अगर (i2c->singlemaster) अणु
		वापस 0;
	पूर्ण

	/* क्रम instance अगर previous transfer was terminated due to TX error
	 * it might be that the bus is on it's way to become available
	 * give it at most 3 ms to wake
	 */
	err = xiic_bus_busy(i2c);
	जबतक (err && tries--) अणु
		msleep(1);
		err = xiic_bus_busy(i2c);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम xiic_start_recv(काष्ठा xiic_i2c *i2c)
अणु
	u8 rx_watermark;
	काष्ठा i2c_msg *msg = i2c->rx_msg = i2c->tx_msg;
	अचिन्हित दीर्घ flags;

	/* Clear and enable Rx full पूर्णांकerrupt. */
	xiic_irq_clr_en(i2c, XIIC_INTR_RX_FULL_MASK | XIIC_INTR_TX_ERROR_MASK);

	/* we want to get all but last byte, because the TX_ERROR IRQ is used
	 * to inidicate error ACK on the address, and negative ack on the last
	 * received byte, so to not mix them receive all but last.
	 * In the हाल where there is only one byte to receive
	 * we can check अगर ERROR and RX full is set at the same समय
	 */
	rx_watermark = msg->len;
	अगर (rx_watermark > IIC_RX_FIFO_DEPTH)
		rx_watermark = IIC_RX_FIFO_DEPTH;
	xiic_setreg8(i2c, XIIC_RFD_REG_OFFSET, rx_watermark - 1);

	local_irq_save(flags);
	अगर (!(msg->flags & I2C_M_NOSTART))
		/* ग_लिखो the address */
		xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET,
			i2c_8bit_addr_from_msg(msg) | XIIC_TX_DYN_START_MASK);

	xiic_irq_clr_en(i2c, XIIC_INTR_BNB_MASK);

	xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET,
		msg->len | ((i2c->nmsgs == 1) ? XIIC_TX_DYN_STOP_MASK : 0));
	local_irq_restore(flags);

	अगर (i2c->nmsgs == 1)
		/* very last, enable bus not busy as well */
		xiic_irq_clr_en(i2c, XIIC_INTR_BNB_MASK);

	/* the message is tx:ed */
	i2c->tx_pos = msg->len;
पूर्ण

अटल व्योम xiic_start_send(काष्ठा xiic_i2c *i2c)
अणु
	काष्ठा i2c_msg *msg = i2c->tx_msg;

	xiic_irq_clr(i2c, XIIC_INTR_TX_ERROR_MASK);

	dev_dbg(i2c->adap.dev.parent, "%s entry, msg: %p, len: %d",
		__func__, msg, msg->len);
	dev_dbg(i2c->adap.dev.parent, "%s entry, ISR: 0x%x, CR: 0x%x\n",
		__func__, xiic_getreg32(i2c, XIIC_IISR_OFFSET),
		xiic_getreg8(i2c, XIIC_CR_REG_OFFSET));

	अगर (!(msg->flags & I2C_M_NOSTART)) अणु
		/* ग_लिखो the address */
		u16 data = i2c_8bit_addr_from_msg(msg) |
			XIIC_TX_DYN_START_MASK;
		अगर ((i2c->nmsgs == 1) && msg->len == 0)
			/* no data and last message -> add STOP */
			data |= XIIC_TX_DYN_STOP_MASK;

		xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET, data);
	पूर्ण

	xiic_fill_tx_fअगरo(i2c);

	/* Clear any pending Tx empty, Tx Error and then enable them. */
	xiic_irq_clr_en(i2c, XIIC_INTR_TX_EMPTY_MASK | XIIC_INTR_TX_ERROR_MASK |
		XIIC_INTR_BNB_MASK);
पूर्ण

अटल irqवापस_t xiic_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xiic_i2c *i2c = dev_id;
	u32 pend, isr, ier;
	irqवापस_t ret = IRQ_NONE;
	/* Do not processes a devices पूर्णांकerrupts अगर the device has no
	 * पूर्णांकerrupts pending
	 */

	dev_dbg(i2c->adap.dev.parent, "%s entry\n", __func__);

	isr = xiic_getreg32(i2c, XIIC_IISR_OFFSET);
	ier = xiic_getreg32(i2c, XIIC_IIER_OFFSET);
	pend = isr & ier;
	अगर (pend)
		ret = IRQ_WAKE_THREAD;

	वापस ret;
पूर्ण

अटल व्योम __xiic_start_xfer(काष्ठा xiic_i2c *i2c)
अणु
	पूर्णांक first = 1;
	पूर्णांक fअगरo_space = xiic_tx_fअगरo_space(i2c);
	dev_dbg(i2c->adap.dev.parent, "%s entry, msg: %p, fifos space: %d\n",
		__func__, i2c->tx_msg, fअगरo_space);

	अगर (!i2c->tx_msg)
		वापस;

	i2c->rx_pos = 0;
	i2c->tx_pos = 0;
	i2c->state = STATE_START;
	जबतक ((fअगरo_space >= 2) && (first || (i2c->nmsgs > 1))) अणु
		अगर (!first) अणु
			i2c->nmsgs--;
			i2c->tx_msg++;
			i2c->tx_pos = 0;
		पूर्ण अन्यथा
			first = 0;

		अगर (i2c->tx_msg->flags & I2C_M_RD) अणु
			/* we करोnt date putting several पढ़ोs in the FIFO */
			xiic_start_recv(i2c);
			वापस;
		पूर्ण अन्यथा अणु
			xiic_start_send(i2c);
			अगर (xiic_tx_space(i2c) != 0) अणु
				/* the message could not be completely sent */
				अवरोध;
			पूर्ण
		पूर्ण

		fअगरo_space = xiic_tx_fअगरo_space(i2c);
	पूर्ण

	/* there are more messages or the current one could not be completely
	 * put पूर्णांकo the FIFO, also enable the half empty पूर्णांकerrupt
	 */
	अगर (i2c->nmsgs > 1 || xiic_tx_space(i2c))
		xiic_irq_clr_en(i2c, XIIC_INTR_TX_HALF_MASK);

पूर्ण

अटल पूर्णांक xiic_start_xfer(काष्ठा xiic_i2c *i2c)
अणु
	पूर्णांक ret;
	mutex_lock(&i2c->lock);

	ret = xiic_reinit(i2c);
	अगर (!ret)
		__xiic_start_xfer(i2c);

	mutex_unlock(&i2c->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक xiic_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा xiic_i2c *i2c = i2c_get_adapdata(adap);
	पूर्णांक err;

	dev_dbg(adap->dev.parent, "%s entry SR: 0x%x\n", __func__,
		xiic_getreg8(i2c, XIIC_SR_REG_OFFSET));

	err = pm_runसमय_resume_and_get(i2c->dev);
	अगर (err < 0)
		वापस err;

	err = xiic_busy(i2c);
	अगर (err)
		जाओ out;

	i2c->tx_msg = msgs;
	i2c->nmsgs = num;

	err = xiic_start_xfer(i2c);
	अगर (err < 0) अणु
		dev_err(adap->dev.parent, "Error xiic_start_xfer\n");
		जाओ out;
	पूर्ण

	अगर (रुको_event_समयout(i2c->रुको, (i2c->state == STATE_ERROR) ||
		(i2c->state == STATE_DONE), HZ)) अणु
		err = (i2c->state == STATE_DONE) ? num : -EIO;
		जाओ out;
	पूर्ण अन्यथा अणु
		i2c->tx_msg = शून्य;
		i2c->rx_msg = शून्य;
		i2c->nmsgs = 0;
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण
out:
	pm_runसमय_mark_last_busy(i2c->dev);
	pm_runसमय_put_स्वतःsuspend(i2c->dev);
	वापस err;
पूर्ण

अटल u32 xiic_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm xiic_algorithm = अणु
	.master_xfer = xiic_xfer,
	.functionality = xiic_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks xiic_quirks = अणु
	.max_पढ़ो_len = 255,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter xiic_adapter = अणु
	.owner = THIS_MODULE,
	.name = DRIVER_NAME,
	.class = I2C_CLASS_DEPRECATED,
	.algo = &xiic_algorithm,
	.quirks = &xiic_quirks,
पूर्ण;


अटल पूर्णांक xiic_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xiic_i2c *i2c;
	काष्ठा xiic_i2c_platक्रमm_data *pdata;
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	u8 i;
	u32 sr;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	pdata = dev_get_platdata(&pdev->dev);

	/* hook up driver to tree */
	platक्रमm_set_drvdata(pdev, i2c);
	i2c->adap = xiic_adapter;
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	mutex_init(&i2c->lock);
	init_रुकोqueue_head(&i2c->रुको);

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c->clk)) अणु
		अगर (PTR_ERR(i2c->clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "input clock not found.\n");
		वापस PTR_ERR(i2c->clk);
	पूर्ण
	ret = clk_prepare_enable(i2c->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		वापस ret;
	पूर्ण
	i2c->dev = &pdev->dev;
	pm_runसमय_set_स्वतःsuspend_delay(i2c->dev, XIIC_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(i2c->dev);
	pm_runसमय_set_active(i2c->dev);
	pm_runसमय_enable(i2c->dev);
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, xiic_isr,
					xiic_process, IRQF_ONESHOT,
					pdev->name, i2c);

	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		जाओ err_clk_dis;
	पूर्ण

	i2c->singlemaster =
		of_property_पढ़ो_bool(pdev->dev.of_node, "single-master");

	/*
	 * Detect endianness
	 * Try to reset the TX FIFO. Then check the EMPTY flag. If it is not
	 * set, assume that the endianness was wrong and swap.
	 */
	i2c->endianness = LITTLE;
	xiic_setreg32(i2c, XIIC_CR_REG_OFFSET, XIIC_CR_TX_FIFO_RESET_MASK);
	/* Reset is cleared in xiic_reinit */
	sr = xiic_getreg32(i2c, XIIC_SR_REG_OFFSET);
	अगर (!(sr & XIIC_SR_TX_FIFO_EMPTY_MASK))
		i2c->endianness = BIG;

	ret = xiic_reinit(i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot xiic_reinit\n");
		जाओ err_clk_dis;
	पूर्ण

	/* add i2c adapter to i2c tree */
	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret) अणु
		xiic_deinit(i2c);
		जाओ err_clk_dis;
	पूर्ण

	अगर (pdata) अणु
		/* add in known devices to the bus */
		क्रम (i = 0; i < pdata->num_devices; i++)
			i2c_new_client_device(&i2c->adap, pdata->devices + i);
	पूर्ण

	वापस 0;

err_clk_dis:
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक xiic_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xiic_i2c *i2c = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	/* हटाओ adapter & data */
	i2c_del_adapter(&i2c->adap);

	ret = pm_runसमय_resume_and_get(i2c->dev);
	अगर (ret < 0)
		वापस ret;

	xiic_deinit(i2c);
	pm_runसमय_put_sync(i2c->dev);
	clk_disable_unprepare(i2c->clk);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id xiic_of_match[] = अणु
	अणु .compatible = "xlnx,xps-iic-2.00.a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xiic_of_match);
#पूर्ण_अगर

अटल पूर्णांक __maybe_unused xiic_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा xiic_i2c *i2c = dev_get_drvdata(dev);

	clk_disable(i2c->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xiic_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा xiic_i2c *i2c = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(i2c->clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable clock.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xiic_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(xiic_i2c_runसमय_suspend,
			   xiic_i2c_runसमय_resume, शून्य)
पूर्ण;
अटल काष्ठा platक्रमm_driver xiic_i2c_driver = अणु
	.probe   = xiic_i2c_probe,
	.हटाओ  = xiic_i2c_हटाओ,
	.driver  = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(xiic_of_match),
		.pm = &xiic_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xiic_i2c_driver);

MODULE_AUTHOR("info@mocean-labs.com");
MODULE_DESCRIPTION("Xilinx I2C bus driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:"DRIVER_NAME);
