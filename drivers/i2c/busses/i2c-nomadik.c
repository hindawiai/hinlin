<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 ST-Ericsson SA
 * Copyright (C) 2009 STMicroelectronics
 *
 * I2C master mode controller driver, used in Nomadik 8815
 * and Ux500 platक्रमms.
 *
 * Author: Srinidhi Kasagar <srinidhi.kasagar@stericsson.com>
 * Author: Sachin Verma <sachin.verma@st.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>

#घोषणा DRIVER_NAME "nmk-i2c"

/* I2C Controller रेजिस्टर offsets */
#घोषणा I2C_CR		(0x000)
#घोषणा I2C_SCR		(0x004)
#घोषणा I2C_HSMCR	(0x008)
#घोषणा I2C_MCR		(0x00C)
#घोषणा I2C_TFR		(0x010)
#घोषणा I2C_SR		(0x014)
#घोषणा I2C_RFR		(0x018)
#घोषणा I2C_TFTR	(0x01C)
#घोषणा I2C_RFTR	(0x020)
#घोषणा I2C_DMAR	(0x024)
#घोषणा I2C_BRCR	(0x028)
#घोषणा I2C_IMSCR	(0x02C)
#घोषणा I2C_RISR	(0x030)
#घोषणा I2C_MISR	(0x034)
#घोषणा I2C_ICR		(0x038)

/* Control रेजिस्टरs */
#घोषणा I2C_CR_PE		(0x1 << 0)	/* Peripheral Enable */
#घोषणा I2C_CR_OM		(0x3 << 1)	/* Operating mode */
#घोषणा I2C_CR_SAM		(0x1 << 3)	/* Slave addressing mode */
#घोषणा I2C_CR_SM		(0x3 << 4)	/* Speed mode */
#घोषणा I2C_CR_SGCM		(0x1 << 6)	/* Slave general call mode */
#घोषणा I2C_CR_FTX		(0x1 << 7)	/* Flush Transmit */
#घोषणा I2C_CR_FRX		(0x1 << 8)	/* Flush Receive */
#घोषणा I2C_CR_DMA_TX_EN	(0x1 << 9)	/* DMA Tx enable */
#घोषणा I2C_CR_DMA_RX_EN	(0x1 << 10)	/* DMA Rx Enable */
#घोषणा I2C_CR_DMA_SLE		(0x1 << 11)	/* DMA sync. logic enable */
#घोषणा I2C_CR_LM		(0x1 << 12)	/* Loopback mode */
#घोषणा I2C_CR_FON		(0x3 << 13)	/* Filtering on */
#घोषणा I2C_CR_FS		(0x3 << 15)	/* Force stop enable */

/* Master controller (MCR) रेजिस्टर */
#घोषणा I2C_MCR_OP		(0x1 << 0)	/* Operation */
#घोषणा I2C_MCR_A7		(0x7f << 1)	/* 7-bit address */
#घोषणा I2C_MCR_EA10		(0x7 << 8)	/* 10-bit Extended address */
#घोषणा I2C_MCR_SB		(0x1 << 11)	/* Extended address */
#घोषणा I2C_MCR_AM		(0x3 << 12)	/* Address type */
#घोषणा I2C_MCR_STOP		(0x1 << 14)	/* Stop condition */
#घोषणा I2C_MCR_LENGTH		(0x7ff << 15)	/* Transaction length */

/* Status रेजिस्टर (SR) */
#घोषणा I2C_SR_OP		(0x3 << 0)	/* Operation */
#घोषणा I2C_SR_STATUS		(0x3 << 2)	/* controller status */
#घोषणा I2C_SR_CAUSE		(0x7 << 4)	/* Abort cause */
#घोषणा I2C_SR_TYPE		(0x3 << 7)	/* Receive type */
#घोषणा I2C_SR_LENGTH		(0x7ff << 9)	/* Transfer length */

/* Interrupt mask set/clear (IMSCR) bits */
#घोषणा I2C_IT_TXFE		(0x1 << 0)
#घोषणा I2C_IT_TXFNE		(0x1 << 1)
#घोषणा I2C_IT_TXFF		(0x1 << 2)
#घोषणा I2C_IT_TXFOVR		(0x1 << 3)
#घोषणा I2C_IT_RXFE		(0x1 << 4)
#घोषणा I2C_IT_RXFNF		(0x1 << 5)
#घोषणा I2C_IT_RXFF		(0x1 << 6)
#घोषणा I2C_IT_RFSR		(0x1 << 16)
#घोषणा I2C_IT_RFSE		(0x1 << 17)
#घोषणा I2C_IT_WTSR		(0x1 << 18)
#घोषणा I2C_IT_MTD		(0x1 << 19)
#घोषणा I2C_IT_STD		(0x1 << 20)
#घोषणा I2C_IT_MAL		(0x1 << 24)
#घोषणा I2C_IT_BERR		(0x1 << 25)
#घोषणा I2C_IT_MTDWS		(0x1 << 28)

#घोषणा GEN_MASK(val, mask, sb)  (((val) << (sb)) & (mask))

/* some bits in ICR are reserved */
#घोषणा I2C_CLEAR_ALL_INTS	0x131f007f

/* first three msb bits are reserved */
#घोषणा IRQ_MASK(mask)		(mask & 0x1fffffff)

/* maximum threshold value */
#घोषणा MAX_I2C_FIFO_THRESHOLD	15

क्रमागत i2c_freq_mode अणु
	I2C_FREQ_MODE_STANDARD,		/* up to 100 Kb/s */
	I2C_FREQ_MODE_FAST,		/* up to 400 Kb/s */
	I2C_FREQ_MODE_HIGH_SPEED,	/* up to 3.4 Mb/s */
	I2C_FREQ_MODE_FAST_PLUS,	/* up to 1 Mb/s */
पूर्ण;

/**
 * काष्ठा i2c_venकरोr_data - per-venकरोr variations
 * @has_mtdws: variant has the MTDWS bit
 * @fअगरodepth: variant FIFO depth
 */
काष्ठा i2c_venकरोr_data अणु
	bool has_mtdws;
	u32 fअगरodepth;
पूर्ण;

क्रमागत i2c_status अणु
	I2C_NOP,
	I2C_ON_GOING,
	I2C_OK,
	I2C_ABORT
पूर्ण;

/* operation */
क्रमागत i2c_operation अणु
	I2C_NO_OPERATION = 0xff,
	I2C_WRITE = 0x00,
	I2C_READ = 0x01
पूर्ण;

/**
 * काष्ठा i2c_nmk_client - client specअगरic data
 * @slave_adr: 7-bit slave address
 * @count: no. bytes to be transferred
 * @buffer: client data buffer
 * @xfer_bytes: bytes transferred till now
 * @operation: current I2C operation
 */
काष्ठा i2c_nmk_client अणु
	अचिन्हित लघु		slave_adr;
	अचिन्हित दीर्घ		count;
	अचिन्हित अक्षर		*buffer;
	अचिन्हित दीर्घ		xfer_bytes;
	क्रमागत i2c_operation	operation;
पूर्ण;

/**
 * काष्ठा nmk_i2c_dev - निजी data काष्ठाure of the controller.
 * @venकरोr: venकरोr data क्रम this variant.
 * @adev: parent amba device.
 * @adap: corresponding I2C adapter.
 * @irq: पूर्णांकerrupt line क्रम the controller.
 * @virtbase: भव io memory area.
 * @clk: hardware i2c block घड़ी.
 * @cli: holder of client specअगरic data.
 * @clk_freq: घड़ी frequency क्रम the operation mode
 * @tft: Tx FIFO Threshold in bytes
 * @rft: Rx FIFO Threshold in bytes
 * @समयout: Slave response समयout (ms)
 * @sm: speed mode
 * @stop: stop condition.
 * @xfer_complete: acknowledge completion क्रम a I2C message.
 * @result: controller propogated result.
 */
काष्ठा nmk_i2c_dev अणु
	काष्ठा i2c_venकरोr_data		*venकरोr;
	काष्ठा amba_device		*adev;
	काष्ठा i2c_adapter		adap;
	पूर्णांक				irq;
	व्योम __iomem			*virtbase;
	काष्ठा clk			*clk;
	काष्ठा i2c_nmk_client		cli;
	u32				clk_freq;
	अचिन्हित अक्षर			tft;
	अचिन्हित अक्षर			rft;
	पूर्णांक				समयout;
	क्रमागत i2c_freq_mode		sm;
	पूर्णांक				stop;
	काष्ठा completion		xfer_complete;
	पूर्णांक				result;
पूर्ण;

/* controller's पात causes */
अटल स्थिर अक्षर *पात_causes[] = अणु
	"no ack received after address transmission",
	"no ack received during data phase",
	"ack received after xmission of master code",
	"master lost arbitration",
	"slave restarts",
	"slave reset",
	"overflow, maxsize is 2047 bytes",
पूर्ण;

अटल अंतरभूत व्योम i2c_set_bit(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl(पढ़ोl(reg) | mask, reg);
पूर्ण

अटल अंतरभूत व्योम i2c_clr_bit(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl(पढ़ोl(reg) & ~mask, reg);
पूर्ण

/**
 * flush_i2c_fअगरo() - This function flushes the I2C FIFO
 * @dev: निजी data of I2C Driver
 *
 * This function flushes the I2C Tx and Rx FIFOs. It वापसs
 * 0 on successful flushing of FIFO
 */
अटल पूर्णांक flush_i2c_fअगरo(काष्ठा nmk_i2c_dev *dev)
अणु
#घोषणा LOOP_ATTEMPTS 10
	पूर्णांक i;
	अचिन्हित दीर्घ समयout;

	/*
	 * flush the transmit and receive FIFO. The flushing
	 * operation takes several cycles beक्रमe to be completed.
	 * On the completion, the I2C पूर्णांकernal logic clears these
	 * bits, until then no one must access Tx, Rx FIFO and
	 * should poll on these bits रुकोing क्रम the completion.
	 */
	ग_लिखोl((I2C_CR_FTX | I2C_CR_FRX), dev->virtbase + I2C_CR);

	क्रम (i = 0; i < LOOP_ATTEMPTS; i++) अणु
		समयout = jअगरfies + dev->adap.समयout;

		जबतक (!समय_after(jअगरfies, समयout)) अणु
			अगर ((पढ़ोl(dev->virtbase + I2C_CR) &
				(I2C_CR_FTX | I2C_CR_FRX)) == 0)
					वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&dev->adev->dev,
		"flushing operation timed out giving up after %d attempts",
		LOOP_ATTEMPTS);

	वापस -ETIMEDOUT;
पूर्ण

/**
 * disable_all_पूर्णांकerrupts() - Disable all पूर्णांकerrupts of this I2c Bus
 * @dev: निजी data of I2C Driver
 */
अटल व्योम disable_all_पूर्णांकerrupts(काष्ठा nmk_i2c_dev *dev)
अणु
	u32 mask = IRQ_MASK(0);
	ग_लिखोl(mask, dev->virtbase + I2C_IMSCR);
पूर्ण

/**
 * clear_all_पूर्णांकerrupts() - Clear all पूर्णांकerrupts of I2C Controller
 * @dev: निजी data of I2C Driver
 */
अटल व्योम clear_all_पूर्णांकerrupts(काष्ठा nmk_i2c_dev *dev)
अणु
	u32 mask;
	mask = IRQ_MASK(I2C_CLEAR_ALL_INTS);
	ग_लिखोl(mask, dev->virtbase + I2C_ICR);
पूर्ण

/**
 * init_hw() - initialize the I2C hardware
 * @dev: निजी data of I2C Driver
 */
अटल पूर्णांक init_hw(काष्ठा nmk_i2c_dev *dev)
अणु
	पूर्णांक stat;

	stat = flush_i2c_fअगरo(dev);
	अगर (stat)
		जाओ निकास;

	/* disable the controller */
	i2c_clr_bit(dev->virtbase + I2C_CR, I2C_CR_PE);

	disable_all_पूर्णांकerrupts(dev);

	clear_all_पूर्णांकerrupts(dev);

	dev->cli.operation = I2C_NO_OPERATION;

निकास:
	वापस stat;
पूर्ण

/* enable peripheral, master mode operation */
#घोषणा DEFAULT_I2C_REG_CR	((1 << 1) | I2C_CR_PE)

/**
 * load_i2c_mcr_reg() - load the MCR रेजिस्टर
 * @dev: निजी data of controller
 * @flags: message flags
 */
अटल u32 load_i2c_mcr_reg(काष्ठा nmk_i2c_dev *dev, u16 flags)
अणु
	u32 mcr = 0;
	अचिन्हित लघु slave_adr_3msb_bits;

	mcr |= GEN_MASK(dev->cli.slave_adr, I2C_MCR_A7, 1);

	अगर (unlikely(flags & I2C_M_TEN)) अणु
		/* 10-bit address transaction */
		mcr |= GEN_MASK(2, I2C_MCR_AM, 12);
		/*
		 * Get the top 3 bits.
		 * EA10 represents extended address in MCR. This includes
		 * the extension (MSB bits) of the 7 bit address loaded
		 * in A7
		 */
		slave_adr_3msb_bits = (dev->cli.slave_adr >> 7) & 0x7;

		mcr |= GEN_MASK(slave_adr_3msb_bits, I2C_MCR_EA10, 8);
	पूर्ण अन्यथा अणु
		/* 7-bit address transaction */
		mcr |= GEN_MASK(1, I2C_MCR_AM, 12);
	पूर्ण

	/* start byte procedure not applied */
	mcr |= GEN_MASK(0, I2C_MCR_SB, 11);

	/* check the operation, master पढ़ो/ग_लिखो? */
	अगर (dev->cli.operation == I2C_WRITE)
		mcr |= GEN_MASK(I2C_WRITE, I2C_MCR_OP, 0);
	अन्यथा
		mcr |= GEN_MASK(I2C_READ, I2C_MCR_OP, 0);

	/* stop or repeated start? */
	अगर (dev->stop)
		mcr |= GEN_MASK(1, I2C_MCR_STOP, 14);
	अन्यथा
		mcr &= ~(GEN_MASK(1, I2C_MCR_STOP, 14));

	mcr |= GEN_MASK(dev->cli.count, I2C_MCR_LENGTH, 15);

	वापस mcr;
पूर्ण

/**
 * setup_i2c_controller() - setup the controller
 * @dev: निजी data of controller
 */
अटल व्योम setup_i2c_controller(काष्ठा nmk_i2c_dev *dev)
अणु
	u32 brcr1, brcr2;
	u32 i2c_clk, भाग;
	u32 ns;
	u16 slsu;

	ग_लिखोl(0x0, dev->virtbase + I2C_CR);
	ग_लिखोl(0x0, dev->virtbase + I2C_HSMCR);
	ग_लिखोl(0x0, dev->virtbase + I2C_TFTR);
	ग_लिखोl(0x0, dev->virtbase + I2C_RFTR);
	ग_लिखोl(0x0, dev->virtbase + I2C_DMAR);

	i2c_clk = clk_get_rate(dev->clk);

	/*
	 * set the slsu:
	 *
	 * slsu defines the data setup समय after SCL घड़ी
	 * stretching in terms of i2c clk cycles + 1 (zero means
	 * "wait one cycle"), the needed setup समय क्रम the three
	 * modes are 250ns, 100ns, 10ns respectively.
	 *
	 * As the समय क्रम one cycle T in nanoseconds is
	 * T = (1/f) * 1000000000 =>
	 * slsu = cycles / (1000000000 / f) + 1
	 */
	ns = DIV_ROUND_UP_ULL(1000000000ULL, i2c_clk);
	चयन (dev->sm) अणु
	हाल I2C_FREQ_MODE_FAST:
	हाल I2C_FREQ_MODE_FAST_PLUS:
		slsu = DIV_ROUND_UP(100, ns); /* Fast */
		अवरोध;
	हाल I2C_FREQ_MODE_HIGH_SPEED:
		slsu = DIV_ROUND_UP(10, ns); /* High */
		अवरोध;
	हाल I2C_FREQ_MODE_STANDARD:
	शेष:
		slsu = DIV_ROUND_UP(250, ns); /* Standard */
		अवरोध;
	पूर्ण
	slsu += 1;

	dev_dbg(&dev->adev->dev, "calculated SLSU = %04x\n", slsu);
	ग_लिखोl(slsu << 16, dev->virtbase + I2C_SCR);

	/*
	 * The spec says, in हाल of std. mode the भागider is
	 * 2 whereas it is 3 क्रम fast and fastplus mode of
	 * operation. TODO - high speed support.
	 */
	भाग = (dev->clk_freq > I2C_MAX_STANDARD_MODE_FREQ) ? 3 : 2;

	/*
	 * generate the mask क्रम baud rate counters. The controller
	 * has two baud rate counters. One is used क्रम High speed
	 * operation, and the other is क्रम std, fast mode, fast mode
	 * plus operation. Currently we करो not supprt high speed mode
	 * so set brcr1 to 0.
	 */
	brcr1 = 0 << 16;
	brcr2 = (i2c_clk/(dev->clk_freq * भाग)) & 0xffff;

	/* set the baud rate counter रेजिस्टर */
	ग_लिखोl((brcr1 | brcr2), dev->virtbase + I2C_BRCR);

	/*
	 * set the speed mode. Currently we support
	 * only standard and fast mode of operation
	 * TODO - support क्रम fast mode plus (up to 1Mb/s)
	 * and high speed (up to 3.4 Mb/s)
	 */
	अगर (dev->sm > I2C_FREQ_MODE_FAST) अणु
		dev_err(&dev->adev->dev,
			"do not support this mode defaulting to std. mode\n");
		brcr2 = i2c_clk / (I2C_MAX_STANDARD_MODE_FREQ * 2) & 0xffff;
		ग_लिखोl((brcr1 | brcr2), dev->virtbase + I2C_BRCR);
		ग_लिखोl(I2C_FREQ_MODE_STANDARD << 4,
				dev->virtbase + I2C_CR);
	पूर्ण
	ग_लिखोl(dev->sm << 4, dev->virtbase + I2C_CR);

	/* set the Tx and Rx FIFO threshold */
	ग_लिखोl(dev->tft, dev->virtbase + I2C_TFTR);
	ग_लिखोl(dev->rft, dev->virtbase + I2C_RFTR);
पूर्ण

/**
 * पढ़ो_i2c() - Read from I2C client device
 * @dev: निजी data of I2C Driver
 * @flags: message flags
 *
 * This function पढ़ोs from i2c client device when controller is in
 * master mode. There is a completion समयout. If there is no transfer
 * beक्रमe समयout error is वापसed.
 */
अटल पूर्णांक पढ़ो_i2c(काष्ठा nmk_i2c_dev *dev, u16 flags)
अणु
	पूर्णांक status = 0;
	u32 mcr, irq_mask;
	अचिन्हित दीर्घ समयout;

	mcr = load_i2c_mcr_reg(dev, flags);
	ग_लिखोl(mcr, dev->virtbase + I2C_MCR);

	/* load the current CR value */
	ग_लिखोl(पढ़ोl(dev->virtbase + I2C_CR) | DEFAULT_I2C_REG_CR,
			dev->virtbase + I2C_CR);

	/* enable the controller */
	i2c_set_bit(dev->virtbase + I2C_CR, I2C_CR_PE);

	init_completion(&dev->xfer_complete);

	/* enable पूर्णांकerrupts by setting the mask */
	irq_mask = (I2C_IT_RXFNF | I2C_IT_RXFF |
			I2C_IT_MAL | I2C_IT_BERR);

	अगर (dev->stop || !dev->venकरोr->has_mtdws)
		irq_mask |= I2C_IT_MTD;
	अन्यथा
		irq_mask |= I2C_IT_MTDWS;

	irq_mask = I2C_CLEAR_ALL_INTS & IRQ_MASK(irq_mask);

	ग_लिखोl(पढ़ोl(dev->virtbase + I2C_IMSCR) | irq_mask,
			dev->virtbase + I2C_IMSCR);

	समयout = रुको_क्रम_completion_समयout(
		&dev->xfer_complete, dev->adap.समयout);

	अगर (समयout == 0) अणु
		/* Controller समयd out */
		dev_err(&dev->adev->dev, "read from slave 0x%x timed out\n",
				dev->cli.slave_adr);
		status = -ETIMEDOUT;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम fill_tx_fअगरo(काष्ठा nmk_i2c_dev *dev, पूर्णांक no_bytes)
अणु
	पूर्णांक count;

	क्रम (count = (no_bytes - 2);
			(count > 0) &&
			(dev->cli.count != 0);
			count--) अणु
		/* ग_लिखो to the Tx FIFO */
		ग_लिखोb(*dev->cli.buffer,
			dev->virtbase + I2C_TFR);
		dev->cli.buffer++;
		dev->cli.count--;
		dev->cli.xfer_bytes++;
	पूर्ण

पूर्ण

/**
 * ग_लिखो_i2c() - Write data to I2C client.
 * @dev: निजी data of I2C Driver
 * @flags: message flags
 *
 * This function ग_लिखोs data to I2C client
 */
अटल पूर्णांक ग_लिखो_i2c(काष्ठा nmk_i2c_dev *dev, u16 flags)
अणु
	u32 status = 0;
	u32 mcr, irq_mask;
	अचिन्हित दीर्घ समयout;

	mcr = load_i2c_mcr_reg(dev, flags);

	ग_लिखोl(mcr, dev->virtbase + I2C_MCR);

	/* load the current CR value */
	ग_लिखोl(पढ़ोl(dev->virtbase + I2C_CR) | DEFAULT_I2C_REG_CR,
			dev->virtbase + I2C_CR);

	/* enable the controller */
	i2c_set_bit(dev->virtbase + I2C_CR, I2C_CR_PE);

	init_completion(&dev->xfer_complete);

	/* enable पूर्णांकerrupts by settings the masks */
	irq_mask = (I2C_IT_TXFOVR | I2C_IT_MAL | I2C_IT_BERR);

	/* Fill the TX FIFO with transmit data */
	fill_tx_fअगरo(dev, MAX_I2C_FIFO_THRESHOLD);

	अगर (dev->cli.count != 0)
		irq_mask |= I2C_IT_TXFNE;

	/*
	 * check अगर we want to transfer a single or multiple bytes, अगर so
	 * set the MTDWS bit (Master Transaction Done Without Stop)
	 * to start repeated start operation
	 */
	अगर (dev->stop || !dev->venकरोr->has_mtdws)
		irq_mask |= I2C_IT_MTD;
	अन्यथा
		irq_mask |= I2C_IT_MTDWS;

	irq_mask = I2C_CLEAR_ALL_INTS & IRQ_MASK(irq_mask);

	ग_लिखोl(पढ़ोl(dev->virtbase + I2C_IMSCR) | irq_mask,
			dev->virtbase + I2C_IMSCR);

	समयout = रुको_क्रम_completion_समयout(
		&dev->xfer_complete, dev->adap.समयout);

	अगर (समयout == 0) अणु
		/* Controller समयd out */
		dev_err(&dev->adev->dev, "write to slave 0x%x timed out\n",
				dev->cli.slave_adr);
		status = -ETIMEDOUT;
	पूर्ण

	वापस status;
पूर्ण

/**
 * nmk_i2c_xfer_one() - transmit a single I2C message
 * @dev: device with a message encoded पूर्णांकo it
 * @flags: message flags
 */
अटल पूर्णांक nmk_i2c_xfer_one(काष्ठा nmk_i2c_dev *dev, u16 flags)
अणु
	पूर्णांक status;

	अगर (flags & I2C_M_RD) अणु
		/* पढ़ो operation */
		dev->cli.operation = I2C_READ;
		status = पढ़ो_i2c(dev, flags);
	पूर्ण अन्यथा अणु
		/* ग_लिखो operation */
		dev->cli.operation = I2C_WRITE;
		status = ग_लिखो_i2c(dev, flags);
	पूर्ण

	अगर (status || (dev->result)) अणु
		u32 i2c_sr;
		u32 cause;

		i2c_sr = पढ़ोl(dev->virtbase + I2C_SR);
		/*
		 * Check अगर the controller I2C operation status
		 * is set to ABORT(11b).
		 */
		अगर (((i2c_sr >> 2) & 0x3) == 0x3) अणु
			/* get the पात cause */
			cause =	(i2c_sr >> 4) & 0x7;
			dev_err(&dev->adev->dev, "%s\n",
				cause >= ARRAY_SIZE(पात_causes) ?
				"unknown reason" :
				पात_causes[cause]);
		पूर्ण

		(व्योम) init_hw(dev);

		status = status ? status : dev->result;
	पूर्ण

	वापस status;
पूर्ण

/**
 * nmk_i2c_xfer() - I2C transfer function used by kernel framework
 * @i2c_adap: Adapter poपूर्णांकer to the controller
 * @msgs: Poपूर्णांकer to data to be written.
 * @num_msgs: Number of messages to be executed
 *
 * This is the function called by the generic kernel i2c_transfer()
 * or i2c_smbus...() API calls. Note that this code is रक्षित by the
 * semaphore set in the kernel i2c_transfer() function.
 *
 * NOTE:
 * READ TRANSFER : We impose a restriction of the first message to be the
 *		index message क्रम any पढ़ो transaction.
 *		- a no index is coded as '0',
 *		- 2byte big endian index is coded as '3'
 *		!!! msg[0].buf holds the actual index.
 *		This is compatible with generic messages of smbus emulator
 *		that send a one byte index.
 *		eg. a I2C transation to पढ़ो 2 bytes from index 0
 *			idx = 0;
 *			msg[0].addr = client->addr;
 *			msg[0].flags = 0x0;
 *			msg[0].len = 1;
 *			msg[0].buf = &idx;
 *
 *			msg[1].addr = client->addr;
 *			msg[1].flags = I2C_M_RD;
 *			msg[1].len = 2;
 *			msg[1].buf = rd_buff
 *			i2c_transfer(adap, msg, 2);
 *
 * WRITE TRANSFER : The I2C standard पूर्णांकerface पूर्णांकerprets all data as payload.
 *		If you want to emulate an SMBUS ग_लिखो transaction put the
 *		index as first byte(or first and second) in the payload.
 *		eg. a I2C transation to ग_लिखो 2 bytes from index 1
 *			wr_buff[0] = 0x1;
 *			wr_buff[1] = 0x23;
 *			wr_buff[2] = 0x46;
 *			msg[0].flags = 0x0;
 *			msg[0].len = 3;
 *			msg[0].buf = wr_buff;
 *			i2c_transfer(adap, msg, 1);
 *
 * To पढ़ो or ग_लिखो a block of data (multiple bytes) using SMBUS emulation
 * please use the i2c_smbus_पढ़ो_i2c_block_data()
 * or i2c_smbus_ग_लिखो_i2c_block_data() API
 */
अटल पूर्णांक nmk_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msgs[], पूर्णांक num_msgs)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;
	काष्ठा nmk_i2c_dev *dev = i2c_get_adapdata(i2c_adap);
	पूर्णांक j;

	pm_runसमय_get_sync(&dev->adev->dev);

	/* Attempt three बार to send the message queue */
	क्रम (j = 0; j < 3; j++) अणु
		/* setup the i2c controller */
		setup_i2c_controller(dev);

		क्रम (i = 0; i < num_msgs; i++) अणु
			dev->cli.slave_adr	= msgs[i].addr;
			dev->cli.buffer		= msgs[i].buf;
			dev->cli.count		= msgs[i].len;
			dev->stop = (i < (num_msgs - 1)) ? 0 : 1;
			dev->result = 0;

			status = nmk_i2c_xfer_one(dev, msgs[i].flags);
			अगर (status != 0)
				अवरोध;
		पूर्ण
		अगर (status == 0)
			अवरोध;
	पूर्ण

	pm_runसमय_put_sync(&dev->adev->dev);

	/* वापस the no. messages processed */
	अगर (status)
		वापस status;
	अन्यथा
		वापस num_msgs;
पूर्ण

/**
 * disable_पूर्णांकerrupts() - disable the पूर्णांकerrupts
 * @dev: निजी data of controller
 * @irq: पूर्णांकerrupt number
 */
अटल पूर्णांक disable_पूर्णांकerrupts(काष्ठा nmk_i2c_dev *dev, u32 irq)
अणु
	irq = IRQ_MASK(irq);
	ग_लिखोl(पढ़ोl(dev->virtbase + I2C_IMSCR) & ~(I2C_CLEAR_ALL_INTS & irq),
			dev->virtbase + I2C_IMSCR);
	वापस 0;
पूर्ण

/**
 * i2c_irq_handler() - पूर्णांकerrupt routine
 * @irq: पूर्णांकerrupt number
 * @arg: data passed to the handler
 *
 * This is the पूर्णांकerrupt handler क्रम the i2c driver. Currently
 * it handles the major पूर्णांकerrupts like Rx & Tx FIFO management
 * पूर्णांकerrupts, master transaction पूर्णांकerrupts, arbitration and
 * bus error पूर्णांकerrupts. The rest of the पूर्णांकerrupts are treated as
 * unhandled.
 */
अटल irqवापस_t i2c_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा nmk_i2c_dev *dev = arg;
	u32 tft, rft;
	u32 count;
	u32 misr, src;

	/* load Tx FIFO and Rx FIFO threshold values */
	tft = पढ़ोl(dev->virtbase + I2C_TFTR);
	rft = पढ़ोl(dev->virtbase + I2C_RFTR);

	/* पढ़ो पूर्णांकerrupt status रेजिस्टर */
	misr = पढ़ोl(dev->virtbase + I2C_MISR);

	src = __ffs(misr);
	चयन ((1 << src)) अणु

	/* Transmit FIFO nearly empty पूर्णांकerrupt */
	हाल I2C_IT_TXFNE:
	अणु
		अगर (dev->cli.operation == I2C_READ) अणु
			/*
			 * in पढ़ो operation why करो we care क्रम writing?
			 * so disable the Transmit FIFO पूर्णांकerrupt
			 */
			disable_पूर्णांकerrupts(dev, I2C_IT_TXFNE);
		पूर्ण अन्यथा अणु
			fill_tx_fअगरo(dev, (MAX_I2C_FIFO_THRESHOLD - tft));
			/*
			 * अगर करोne, बंद the transfer by disabling the
			 * corresponding TXFNE पूर्णांकerrupt
			 */
			अगर (dev->cli.count == 0)
				disable_पूर्णांकerrupts(dev,	I2C_IT_TXFNE);
		पूर्ण
	पूर्ण
	अवरोध;

	/*
	 * Rx FIFO nearly full पूर्णांकerrupt.
	 * This is set when the numer of entries in Rx FIFO is
	 * greater or equal than the threshold value programmed
	 * in RFT
	 */
	हाल I2C_IT_RXFNF:
		क्रम (count = rft; count > 0; count--) अणु
			/* Read the Rx FIFO */
			*dev->cli.buffer = पढ़ोb(dev->virtbase + I2C_RFR);
			dev->cli.buffer++;
		पूर्ण
		dev->cli.count -= rft;
		dev->cli.xfer_bytes += rft;
		अवरोध;

	/* Rx FIFO full */
	हाल I2C_IT_RXFF:
		क्रम (count = MAX_I2C_FIFO_THRESHOLD; count > 0; count--) अणु
			*dev->cli.buffer = पढ़ोb(dev->virtbase + I2C_RFR);
			dev->cli.buffer++;
		पूर्ण
		dev->cli.count -= MAX_I2C_FIFO_THRESHOLD;
		dev->cli.xfer_bytes += MAX_I2C_FIFO_THRESHOLD;
		अवरोध;

	/* Master Transaction Done with/without stop */
	हाल I2C_IT_MTD:
	हाल I2C_IT_MTDWS:
		अगर (dev->cli.operation == I2C_READ) अणु
			जबतक (!(पढ़ोl(dev->virtbase + I2C_RISR)
				 & I2C_IT_RXFE)) अणु
				अगर (dev->cli.count == 0)
					अवरोध;
				*dev->cli.buffer =
					पढ़ोb(dev->virtbase + I2C_RFR);
				dev->cli.buffer++;
				dev->cli.count--;
				dev->cli.xfer_bytes++;
			पूर्ण
		पूर्ण

		disable_all_पूर्णांकerrupts(dev);
		clear_all_पूर्णांकerrupts(dev);

		अगर (dev->cli.count) अणु
			dev->result = -EIO;
			dev_err(&dev->adev->dev,
				"%lu bytes still remain to be xfered\n",
				dev->cli.count);
			(व्योम) init_hw(dev);
		पूर्ण
		complete(&dev->xfer_complete);

		अवरोध;

	/* Master Arbitration lost पूर्णांकerrupt */
	हाल I2C_IT_MAL:
		dev->result = -EIO;
		(व्योम) init_hw(dev);

		i2c_set_bit(dev->virtbase + I2C_ICR, I2C_IT_MAL);
		complete(&dev->xfer_complete);

		अवरोध;

	/*
	 * Bus Error पूर्णांकerrupt.
	 * This happens when an unexpected start/stop condition occurs
	 * during the transaction.
	 */
	हाल I2C_IT_BERR:
		dev->result = -EIO;
		/* get the status */
		अगर (((पढ़ोl(dev->virtbase + I2C_SR) >> 2) & 0x3) == I2C_ABORT)
			(व्योम) init_hw(dev);

		i2c_set_bit(dev->virtbase + I2C_ICR, I2C_IT_BERR);
		complete(&dev->xfer_complete);

		अवरोध;

	/*
	 * Tx FIFO overrun पूर्णांकerrupt.
	 * This is set when a ग_लिखो operation in Tx FIFO is perक्रमmed and
	 * the Tx FIFO is full.
	 */
	हाल I2C_IT_TXFOVR:
		dev->result = -EIO;
		(व्योम) init_hw(dev);

		dev_err(&dev->adev->dev, "Tx Fifo Over run\n");
		complete(&dev->xfer_complete);

		अवरोध;

	/* unhandled पूर्णांकerrupts by this driver - TODO*/
	हाल I2C_IT_TXFE:
	हाल I2C_IT_TXFF:
	हाल I2C_IT_RXFE:
	हाल I2C_IT_RFSR:
	हाल I2C_IT_RFSE:
	हाल I2C_IT_WTSR:
	हाल I2C_IT_STD:
		dev_err(&dev->adev->dev, "unhandled Interrupt\n");
		अवरोध;
	शेष:
		dev_err(&dev->adev->dev, "spurious Interrupt..\n");
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nmk_i2c_suspend_late(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		वापस ret;

	pinctrl_pm_select_sleep_state(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक nmk_i2c_resume_early(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nmk_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा amba_device *adev = to_amba_device(dev);
	काष्ठा nmk_i2c_dev *nmk_i2c = amba_get_drvdata(adev);

	clk_disable_unprepare(nmk_i2c->clk);
	pinctrl_pm_select_idle_state(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक nmk_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा amba_device *adev = to_amba_device(dev);
	काष्ठा nmk_i2c_dev *nmk_i2c = amba_get_drvdata(adev);
	पूर्णांक ret;

	ret = clk_prepare_enable(nmk_i2c->clk);
	अगर (ret) अणु
		dev_err(dev, "can't prepare_enable clock\n");
		वापस ret;
	पूर्ण

	pinctrl_pm_select_शेष_state(dev);

	ret = init_hw(nmk_i2c);
	अगर (ret) अणु
		clk_disable_unprepare(nmk_i2c->clk);
		pinctrl_pm_select_idle_state(dev);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops nmk_i2c_pm = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(nmk_i2c_suspend_late, nmk_i2c_resume_early)
	SET_RUNTIME_PM_OPS(nmk_i2c_runसमय_suspend,
			nmk_i2c_runसमय_resume,
			शून्य)
पूर्ण;

अटल अचिन्हित पूर्णांक nmk_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm nmk_i2c_algo = अणु
	.master_xfer	= nmk_i2c_xfer,
	.functionality	= nmk_i2c_functionality
पूर्ण;

अटल व्योम nmk_i2c_of_probe(काष्ठा device_node *np,
			     काष्ठा nmk_i2c_dev *nmk)
अणु
	/* Default to 100 kHz अगर no frequency is given in the node */
	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &nmk->clk_freq))
		nmk->clk_freq = I2C_MAX_STANDARD_MODE_FREQ;

	/* This driver only supports 'standard' and 'fast' modes of operation. */
	अगर (nmk->clk_freq <= I2C_MAX_STANDARD_MODE_FREQ)
		nmk->sm = I2C_FREQ_MODE_STANDARD;
	अन्यथा
		nmk->sm = I2C_FREQ_MODE_FAST;
	nmk->tft = 1; /* Tx FIFO threshold */
	nmk->rft = 8; /* Rx FIFO threshold */
	nmk->समयout = 200; /* Slave response समयout(ms) */
पूर्ण

अटल पूर्णांक nmk_i2c_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा device_node *np = adev->dev.of_node;
	काष्ठा nmk_i2c_dev	*dev;
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_venकरोr_data *venकरोr = id->data;
	u32 max_fअगरo_threshold = (venकरोr->fअगरodepth / 2) - 1;

	dev = devm_kzalloc(&adev->dev, माप(काष्ठा nmk_i2c_dev), GFP_KERNEL);
	अगर (!dev) अणु
		dev_err(&adev->dev, "cannot allocate memory\n");
		ret = -ENOMEM;
		जाओ err_no_mem;
	पूर्ण
	dev->venकरोr = venकरोr;
	dev->adev = adev;
	nmk_i2c_of_probe(np, dev);

	अगर (dev->tft > max_fअगरo_threshold) अणु
		dev_warn(&adev->dev, "requested TX FIFO threshold %u, adjusted down to %u\n",
			 dev->tft, max_fअगरo_threshold);
		dev->tft = max_fअगरo_threshold;
	पूर्ण

	अगर (dev->rft > max_fअगरo_threshold) अणु
		dev_warn(&adev->dev, "requested RX FIFO threshold %u, adjusted down to %u\n",
			dev->rft, max_fअगरo_threshold);
		dev->rft = max_fअगरo_threshold;
	पूर्ण

	amba_set_drvdata(adev, dev);

	dev->virtbase = devm_ioremap(&adev->dev, adev->res.start,
				resource_size(&adev->res));
	अगर (!dev->virtbase) अणु
		ret = -ENOMEM;
		जाओ err_no_mem;
	पूर्ण

	dev->irq = adev->irq[0];
	ret = devm_request_irq(&adev->dev, dev->irq, i2c_irq_handler, 0,
				DRIVER_NAME, dev);
	अगर (ret) अणु
		dev_err(&adev->dev, "cannot claim the irq %d\n", dev->irq);
		जाओ err_no_mem;
	पूर्ण

	dev->clk = devm_clk_get(&adev->dev, शून्य);
	अगर (IS_ERR(dev->clk)) अणु
		dev_err(&adev->dev, "could not get i2c clock\n");
		ret = PTR_ERR(dev->clk);
		जाओ err_no_mem;
	पूर्ण

	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		dev_err(&adev->dev, "can't prepare_enable clock\n");
		जाओ err_no_mem;
	पूर्ण

	init_hw(dev);

	adap = &dev->adap;
	adap->dev.of_node = np;
	adap->dev.parent = &adev->dev;
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	adap->algo = &nmk_i2c_algo;
	adap->समयout = msecs_to_jअगरfies(dev->समयout);
	snम_लिखो(adap->name, माप(adap->name),
		 "Nomadik I2C at %pR", &adev->res);

	i2c_set_adapdata(adap, dev);

	dev_info(&adev->dev,
		 "initialize %s on virtual base %p\n",
		 adap->name, dev->virtbase);

	ret = i2c_add_adapter(adap);
	अगर (ret)
		जाओ err_no_adap;

	pm_runसमय_put(&adev->dev);

	वापस 0;

 err_no_adap:
	clk_disable_unprepare(dev->clk);
 err_no_mem:

	वापस ret;
पूर्ण

अटल व्योम nmk_i2c_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा resource *res = &adev->res;
	काष्ठा nmk_i2c_dev *dev = amba_get_drvdata(adev);

	i2c_del_adapter(&dev->adap);
	flush_i2c_fअगरo(dev);
	disable_all_पूर्णांकerrupts(dev);
	clear_all_पूर्णांकerrupts(dev);
	/* disable the controller */
	i2c_clr_bit(dev->virtbase + I2C_CR, I2C_CR_PE);
	clk_disable_unprepare(dev->clk);
	release_mem_region(res->start, resource_size(res));
पूर्ण

अटल काष्ठा i2c_venकरोr_data venकरोr_stn8815 = अणु
	.has_mtdws = false,
	.fअगरodepth = 16, /* Guessed from TFTR/RFTR = 7 */
पूर्ण;

अटल काष्ठा i2c_venकरोr_data venकरोr_db8500 = अणु
	.has_mtdws = true,
	.fअगरodepth = 32, /* Guessed from TFTR/RFTR = 15 */
पूर्ण;

अटल स्थिर काष्ठा amba_id nmk_i2c_ids[] = अणु
	अणु
		.id	= 0x00180024,
		.mask	= 0x00ffffff,
		.data	= &venकरोr_stn8815,
	पूर्ण,
	अणु
		.id	= 0x00380024,
		.mask	= 0x00ffffff,
		.data	= &venकरोr_db8500,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, nmk_i2c_ids);

अटल काष्ठा amba_driver nmk_i2c_driver = अणु
	.drv = अणु
		.owner = THIS_MODULE,
		.name = DRIVER_NAME,
		.pm = &nmk_i2c_pm,
	पूर्ण,
	.id_table = nmk_i2c_ids,
	.probe = nmk_i2c_probe,
	.हटाओ = nmk_i2c_हटाओ,
पूर्ण;

अटल पूर्णांक __init nmk_i2c_init(व्योम)
अणु
	वापस amba_driver_रेजिस्टर(&nmk_i2c_driver);
पूर्ण

अटल व्योम __निकास nmk_i2c_निकास(व्योम)
अणु
	amba_driver_unरेजिस्टर(&nmk_i2c_driver);
पूर्ण

subsys_initcall(nmk_i2c_init);
module_निकास(nmk_i2c_निकास);

MODULE_AUTHOR("Sachin Verma");
MODULE_AUTHOR("Srinidhi KASAGAR");
MODULE_DESCRIPTION("Nomadik/Ux500 I2C driver");
MODULE_LICENSE("GPL");
