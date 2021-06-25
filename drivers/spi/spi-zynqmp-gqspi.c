<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Xilinx Zynq UltraScale+ MPSoC Quad-SPI (QSPI) controller driver
 * (master mode only)
 *
 * Copyright (C) 2009 - 2015 Xilinx, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/firmware/xlnx-zynqmp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spi/spi-स्मृति.स>

/* Generic QSPI रेजिस्टर offsets */
#घोषणा GQSPI_CONFIG_OFST		0x00000100
#घोषणा GQSPI_ISR_OFST			0x00000104
#घोषणा GQSPI_IDR_OFST			0x0000010C
#घोषणा GQSPI_IER_OFST			0x00000108
#घोषणा GQSPI_IMASK_OFST		0x00000110
#घोषणा GQSPI_EN_OFST			0x00000114
#घोषणा GQSPI_TXD_OFST			0x0000011C
#घोषणा GQSPI_RXD_OFST			0x00000120
#घोषणा GQSPI_TX_THRESHOLD_OFST		0x00000128
#घोषणा GQSPI_RX_THRESHOLD_OFST		0x0000012C
#घोषणा GQSPI_LPBK_DLY_ADJ_OFST		0x00000138
#घोषणा GQSPI_GEN_FIFO_OFST		0x00000140
#घोषणा GQSPI_SEL_OFST			0x00000144
#घोषणा GQSPI_GF_THRESHOLD_OFST		0x00000150
#घोषणा GQSPI_FIFO_CTRL_OFST		0x0000014C
#घोषणा GQSPI_QSPIDMA_DST_CTRL_OFST	0x0000080C
#घोषणा GQSPI_QSPIDMA_DST_SIZE_OFST	0x00000804
#घोषणा GQSPI_QSPIDMA_DST_STS_OFST	0x00000808
#घोषणा GQSPI_QSPIDMA_DST_I_STS_OFST	0x00000814
#घोषणा GQSPI_QSPIDMA_DST_I_EN_OFST	0x00000818
#घोषणा GQSPI_QSPIDMA_DST_I_DIS_OFST	0x0000081C
#घोषणा GQSPI_QSPIDMA_DST_I_MASK_OFST	0x00000820
#घोषणा GQSPI_QSPIDMA_DST_ADDR_OFST	0x00000800
#घोषणा GQSPI_QSPIDMA_DST_ADDR_MSB_OFST 0x00000828

/* GQSPI रेजिस्टर bit masks */
#घोषणा GQSPI_SEL_MASK				0x00000001
#घोषणा GQSPI_EN_MASK				0x00000001
#घोषणा GQSPI_LPBK_DLY_ADJ_USE_LPBK_MASK	0x00000020
#घोषणा GQSPI_ISR_WR_TO_CLR_MASK		0x00000002
#घोषणा GQSPI_IDR_ALL_MASK			0x00000FBE
#घोषणा GQSPI_CFG_MODE_EN_MASK			0xC0000000
#घोषणा GQSPI_CFG_GEN_FIFO_START_MODE_MASK	0x20000000
#घोषणा GQSPI_CFG_ENDIAN_MASK			0x04000000
#घोषणा GQSPI_CFG_EN_POLL_TO_MASK		0x00100000
#घोषणा GQSPI_CFG_WP_HOLD_MASK			0x00080000
#घोषणा GQSPI_CFG_BAUD_RATE_DIV_MASK		0x00000038
#घोषणा GQSPI_CFG_CLK_PHA_MASK			0x00000004
#घोषणा GQSPI_CFG_CLK_POL_MASK			0x00000002
#घोषणा GQSPI_CFG_START_GEN_FIFO_MASK		0x10000000
#घोषणा GQSPI_GENFIFO_IMM_DATA_MASK		0x000000FF
#घोषणा GQSPI_GENFIFO_DATA_XFER			0x00000100
#घोषणा GQSPI_GENFIFO_EXP			0x00000200
#घोषणा GQSPI_GENFIFO_MODE_SPI			0x00000400
#घोषणा GQSPI_GENFIFO_MODE_DUALSPI		0x00000800
#घोषणा GQSPI_GENFIFO_MODE_QUADSPI		0x00000C00
#घोषणा GQSPI_GENFIFO_MODE_MASK			0x00000C00
#घोषणा GQSPI_GENFIFO_CS_LOWER			0x00001000
#घोषणा GQSPI_GENFIFO_CS_UPPER			0x00002000
#घोषणा GQSPI_GENFIFO_BUS_LOWER			0x00004000
#घोषणा GQSPI_GENFIFO_BUS_UPPER			0x00008000
#घोषणा GQSPI_GENFIFO_BUS_BOTH			0x0000C000
#घोषणा GQSPI_GENFIFO_BUS_MASK			0x0000C000
#घोषणा GQSPI_GENFIFO_TX			0x00010000
#घोषणा GQSPI_GENFIFO_RX			0x00020000
#घोषणा GQSPI_GENFIFO_STRIPE			0x00040000
#घोषणा GQSPI_GENFIFO_POLL			0x00080000
#घोषणा GQSPI_GENFIFO_EXP_START			0x00000100
#घोषणा GQSPI_FIFO_CTRL_RST_RX_FIFO_MASK	0x00000004
#घोषणा GQSPI_FIFO_CTRL_RST_TX_FIFO_MASK	0x00000002
#घोषणा GQSPI_FIFO_CTRL_RST_GEN_FIFO_MASK	0x00000001
#घोषणा GQSPI_ISR_RXEMPTY_MASK			0x00000800
#घोषणा GQSPI_ISR_GENFIFOFULL_MASK		0x00000400
#घोषणा GQSPI_ISR_GENFIFONOT_FULL_MASK		0x00000200
#घोषणा GQSPI_ISR_TXEMPTY_MASK			0x00000100
#घोषणा GQSPI_ISR_GENFIFOEMPTY_MASK		0x00000080
#घोषणा GQSPI_ISR_RXFULL_MASK			0x00000020
#घोषणा GQSPI_ISR_RXNEMPTY_MASK			0x00000010
#घोषणा GQSPI_ISR_TXFULL_MASK			0x00000008
#घोषणा GQSPI_ISR_TXNOT_FULL_MASK		0x00000004
#घोषणा GQSPI_ISR_POLL_TIME_EXPIRE_MASK		0x00000002
#घोषणा GQSPI_IER_TXNOT_FULL_MASK		0x00000004
#घोषणा GQSPI_IER_RXEMPTY_MASK			0x00000800
#घोषणा GQSPI_IER_POLL_TIME_EXPIRE_MASK		0x00000002
#घोषणा GQSPI_IER_RXNEMPTY_MASK			0x00000010
#घोषणा GQSPI_IER_GENFIFOEMPTY_MASK		0x00000080
#घोषणा GQSPI_IER_TXEMPTY_MASK			0x00000100
#घोषणा GQSPI_QSPIDMA_DST_INTR_ALL_MASK		0x000000FE
#घोषणा GQSPI_QSPIDMA_DST_STS_WTC		0x0000E000
#घोषणा GQSPI_CFG_MODE_EN_DMA_MASK		0x80000000
#घोषणा GQSPI_ISR_IDR_MASK			0x00000994
#घोषणा GQSPI_QSPIDMA_DST_I_EN_DONE_MASK	0x00000002
#घोषणा GQSPI_QSPIDMA_DST_I_STS_DONE_MASK	0x00000002
#घोषणा GQSPI_IRQ_MASK				0x00000980

#घोषणा GQSPI_CFG_BAUD_RATE_DIV_SHIFT		3
#घोषणा GQSPI_GENFIFO_CS_SETUP			0x4
#घोषणा GQSPI_GENFIFO_CS_HOLD			0x3
#घोषणा GQSPI_TXD_DEPTH				64
#घोषणा GQSPI_RX_FIFO_THRESHOLD			32
#घोषणा GQSPI_RX_FIFO_FILL	(GQSPI_RX_FIFO_THRESHOLD * 4)
#घोषणा GQSPI_TX_FIFO_THRESHOLD_RESET_VAL	32
#घोषणा GQSPI_TX_FIFO_FILL	(GQSPI_TXD_DEPTH -\
				GQSPI_TX_FIFO_THRESHOLD_RESET_VAL)
#घोषणा GQSPI_GEN_FIFO_THRESHOLD_RESET_VAL	0X10
#घोषणा GQSPI_QSPIDMA_DST_CTRL_RESET_VAL	0x803FFA00
#घोषणा GQSPI_SELECT_FLASH_CS_LOWER		0x1
#घोषणा GQSPI_SELECT_FLASH_CS_UPPER		0x2
#घोषणा GQSPI_SELECT_FLASH_CS_BOTH		0x3
#घोषणा GQSPI_SELECT_FLASH_BUS_LOWER		0x1
#घोषणा GQSPI_SELECT_FLASH_BUS_UPPER		0x2
#घोषणा GQSPI_SELECT_FLASH_BUS_BOTH		0x3
#घोषणा GQSPI_BAUD_DIV_MAX	7	/* Baud rate भागisor maximum */
#घोषणा GQSPI_BAUD_DIV_SHIFT	2	/* Baud rate भागisor shअगरt */
#घोषणा GQSPI_SELECT_MODE_SPI		0x1
#घोषणा GQSPI_SELECT_MODE_DUALSPI	0x2
#घोषणा GQSPI_SELECT_MODE_QUADSPI	0x4
#घोषणा GQSPI_DMA_UNALIGN		0x3
#घोषणा GQSPI_DEFAULT_NUM_CS	1	/* Default number of chip selects */

#घोषणा SPI_AUTOSUSPEND_TIMEOUT		3000
क्रमागत mode_type अणुGQSPI_MODE_IO, GQSPI_MODE_DMAपूर्ण;

/**
 * काष्ठा zynqmp_qspi - Defines qspi driver instance
 * @regs:		Virtual address of the QSPI controller रेजिस्टरs
 * @refclk:		Poपूर्णांकer to the peripheral घड़ी
 * @pclk:		Poपूर्णांकer to the APB घड़ी
 * @irq:		IRQ number
 * @dev:		Poपूर्णांकer to काष्ठा device
 * @txbuf:		Poपूर्णांकer to the TX buffer
 * @rxbuf:		Poपूर्णांकer to the RX buffer
 * @bytes_to_transfer:	Number of bytes left to transfer
 * @bytes_to_receive:	Number of bytes left to receive
 * @genfअगरocs:		Used क्रम chip select
 * @genfअगरobus:		Used to select the upper or lower bus
 * @dma_rx_bytes:	Reमुख्यing bytes to receive by DMA mode
 * @dma_addr:		DMA address after mapping the kernel buffer
 * @genfअगरoentry:	Used क्रम storing the genfअगरoentry inकाष्ठाion.
 * @mode:		Defines the mode in which QSPI is operating
 * @data_completion:	completion काष्ठाure
 */
काष्ठा zynqmp_qspi अणु
	काष्ठा spi_controller *ctlr;
	व्योम __iomem *regs;
	काष्ठा clk *refclk;
	काष्ठा clk *pclk;
	पूर्णांक irq;
	काष्ठा device *dev;
	स्थिर व्योम *txbuf;
	व्योम *rxbuf;
	पूर्णांक bytes_to_transfer;
	पूर्णांक bytes_to_receive;
	u32 genfअगरocs;
	u32 genfअगरobus;
	u32 dma_rx_bytes;
	dma_addr_t dma_addr;
	u32 genfअगरoentry;
	क्रमागत mode_type mode;
	काष्ठा completion data_completion;
	काष्ठा mutex op_lock;
पूर्ण;

/**
 * zynqmp_gqspi_पढ़ो - For GQSPI controller पढ़ो operation
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @offset:	Offset from where to पढ़ो
 * Return:      Value at the offset
 */
अटल u32 zynqmp_gqspi_पढ़ो(काष्ठा zynqmp_qspi *xqspi, u32 offset)
अणु
	वापस पढ़ोl_relaxed(xqspi->regs + offset);
पूर्ण

/**
 * zynqmp_gqspi_ग_लिखो - For GQSPI controller ग_लिखो operation
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @offset:	Offset where to ग_लिखो
 * @val:	Value to be written
 */
अटल अंतरभूत व्योम zynqmp_gqspi_ग_लिखो(काष्ठा zynqmp_qspi *xqspi, u32 offset,
				      u32 val)
अणु
	ग_लिखोl_relaxed(val, (xqspi->regs + offset));
पूर्ण

/**
 * zynqmp_gqspi_selectslave - For selection of slave device
 * @instanceptr:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @slavecs:	For chip select
 * @slavebus:	To check which bus is selected- upper or lower
 */
अटल व्योम zynqmp_gqspi_selectslave(काष्ठा zynqmp_qspi *instanceptr,
				     u8 slavecs, u8 slavebus)
अणु
	/*
	 * Bus and CS lines selected here will be updated in the instance and
	 * used क्रम subsequent GENFIFO entries during transfer.
	 */

	/* Choose slave select line */
	चयन (slavecs) अणु
	हाल GQSPI_SELECT_FLASH_CS_BOTH:
		instanceptr->genfअगरocs = GQSPI_GENFIFO_CS_LOWER |
			GQSPI_GENFIFO_CS_UPPER;
		अवरोध;
	हाल GQSPI_SELECT_FLASH_CS_UPPER:
		instanceptr->genfअगरocs = GQSPI_GENFIFO_CS_UPPER;
		अवरोध;
	हाल GQSPI_SELECT_FLASH_CS_LOWER:
		instanceptr->genfअगरocs = GQSPI_GENFIFO_CS_LOWER;
		अवरोध;
	शेष:
		dev_warn(instanceptr->dev, "Invalid slave select\n");
	पूर्ण

	/* Choose the bus */
	चयन (slavebus) अणु
	हाल GQSPI_SELECT_FLASH_BUS_BOTH:
		instanceptr->genfअगरobus = GQSPI_GENFIFO_BUS_LOWER |
			GQSPI_GENFIFO_BUS_UPPER;
		अवरोध;
	हाल GQSPI_SELECT_FLASH_BUS_UPPER:
		instanceptr->genfअगरobus = GQSPI_GENFIFO_BUS_UPPER;
		अवरोध;
	हाल GQSPI_SELECT_FLASH_BUS_LOWER:
		instanceptr->genfअगरobus = GQSPI_GENFIFO_BUS_LOWER;
		अवरोध;
	शेष:
		dev_warn(instanceptr->dev, "Invalid slave bus\n");
	पूर्ण
पूर्ण

/**
 * zynqmp_qspi_init_hw - Initialize the hardware
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 *
 * The शेष settings of the QSPI controller's configurable parameters on
 * reset are
 *	- Master mode
 *	- TX threshold set to 1
 *	- RX threshold set to 1
 *	- Flash memory पूर्णांकerface mode enabled
 * This function perक्रमms the following actions
 *	- Disable and clear all the पूर्णांकerrupts
 *	- Enable manual slave select
 *	- Enable manual start
 *	- Deselect all the chip select lines
 *	- Set the little endian mode of TX FIFO and
 *	- Enable the QSPI controller
 */
अटल व्योम zynqmp_qspi_init_hw(काष्ठा zynqmp_qspi *xqspi)
अणु
	u32 config_reg;

	/* Select the GQSPI mode */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_SEL_OFST, GQSPI_SEL_MASK);
	/* Clear and disable पूर्णांकerrupts */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_ISR_OFST,
			   zynqmp_gqspi_पढ़ो(xqspi, GQSPI_ISR_OFST) |
			   GQSPI_ISR_WR_TO_CLR_MASK);
	/* Clear the DMA STS */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_I_STS_OFST,
			   zynqmp_gqspi_पढ़ो(xqspi,
					     GQSPI_QSPIDMA_DST_I_STS_OFST));
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_STS_OFST,
			   zynqmp_gqspi_पढ़ो(xqspi,
					     GQSPI_QSPIDMA_DST_STS_OFST) |
					     GQSPI_QSPIDMA_DST_STS_WTC);
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IDR_OFST, GQSPI_IDR_ALL_MASK);
	zynqmp_gqspi_ग_लिखो(xqspi,
			   GQSPI_QSPIDMA_DST_I_DIS_OFST,
			   GQSPI_QSPIDMA_DST_INTR_ALL_MASK);
	/* Disable the GQSPI */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_EN_OFST, 0x0);
	config_reg = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST);
	config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
	/* Manual start */
	config_reg |= GQSPI_CFG_GEN_FIFO_START_MODE_MASK;
	/* Little endian by शेष */
	config_reg &= ~GQSPI_CFG_ENDIAN_MASK;
	/* Disable poll समय out */
	config_reg &= ~GQSPI_CFG_EN_POLL_TO_MASK;
	/* Set hold bit */
	config_reg |= GQSPI_CFG_WP_HOLD_MASK;
	/* Clear pre-scalar by शेष */
	config_reg &= ~GQSPI_CFG_BAUD_RATE_DIV_MASK;
	/* CPHA 0 */
	config_reg &= ~GQSPI_CFG_CLK_PHA_MASK;
	/* CPOL 0 */
	config_reg &= ~GQSPI_CFG_CLK_POL_MASK;
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST, config_reg);

	/* Clear the TX and RX FIFO */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_FIFO_CTRL_OFST,
			   GQSPI_FIFO_CTRL_RST_RX_FIFO_MASK |
			   GQSPI_FIFO_CTRL_RST_TX_FIFO_MASK |
			   GQSPI_FIFO_CTRL_RST_GEN_FIFO_MASK);
	/* Set by शेष to allow क्रम high frequencies */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_LPBK_DLY_ADJ_OFST,
			   zynqmp_gqspi_पढ़ो(xqspi, GQSPI_LPBK_DLY_ADJ_OFST) |
			   GQSPI_LPBK_DLY_ADJ_USE_LPBK_MASK);
	/* Reset thresholds */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_TX_THRESHOLD_OFST,
			   GQSPI_TX_FIFO_THRESHOLD_RESET_VAL);
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_RX_THRESHOLD_OFST,
			   GQSPI_RX_FIFO_THRESHOLD);
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GF_THRESHOLD_OFST,
			   GQSPI_GEN_FIFO_THRESHOLD_RESET_VAL);
	zynqmp_gqspi_selectslave(xqspi,
				 GQSPI_SELECT_FLASH_CS_LOWER,
				 GQSPI_SELECT_FLASH_BUS_LOWER);
	/* Initialize DMA */
	zynqmp_gqspi_ग_लिखो(xqspi,
			   GQSPI_QSPIDMA_DST_CTRL_OFST,
			   GQSPI_QSPIDMA_DST_CTRL_RESET_VAL);

	/* Enable the GQSPI */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_EN_OFST, GQSPI_EN_MASK);
पूर्ण

/**
 * zynqmp_qspi_copy_पढ़ो_data - Copy data to RX buffer
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @data:	The variable where data is stored
 * @size:	Number of bytes to be copied from data to RX buffer
 */
अटल व्योम zynqmp_qspi_copy_पढ़ो_data(काष्ठा zynqmp_qspi *xqspi,
				       uदीर्घ data, u8 size)
अणु
	स_नकल(xqspi->rxbuf, &data, size);
	xqspi->rxbuf += size;
	xqspi->bytes_to_receive -= size;
पूर्ण

/**
 * zynqmp_qspi_chipselect - Select or deselect the chip select line
 * @qspi:	Poपूर्णांकer to the spi_device काष्ठाure
 * @is_high:	Select(0) or deselect (1) the chip select line
 */
अटल व्योम zynqmp_qspi_chipselect(काष्ठा spi_device *qspi, bool is_high)
अणु
	काष्ठा zynqmp_qspi *xqspi = spi_master_get_devdata(qspi->master);
	uदीर्घ समयout;
	u32 genfअगरoentry = 0, statusreg;

	genfअगरoentry |= GQSPI_GENFIFO_MODE_SPI;

	अगर (!is_high) अणु
		xqspi->genfअगरobus = GQSPI_GENFIFO_BUS_LOWER;
		xqspi->genfअगरocs = GQSPI_GENFIFO_CS_LOWER;
		genfअगरoentry |= xqspi->genfअगरobus;
		genfअगरoentry |= xqspi->genfअगरocs;
		genfअगरoentry |= GQSPI_GENFIFO_CS_SETUP;
	पूर्ण अन्यथा अणु
		genfअगरoentry |= GQSPI_GENFIFO_CS_HOLD;
	पूर्ण

	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GEN_FIFO_OFST, genfअगरoentry);

	/* Manually start the generic FIFO command */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
			   zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST) |
			   GQSPI_CFG_START_GEN_FIFO_MASK);

	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	/* Wait until the generic FIFO command is empty */
	करो अणु
		statusreg = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_ISR_OFST);

		अगर ((statusreg & GQSPI_ISR_GENFIFOEMPTY_MASK) &&
		    (statusreg & GQSPI_ISR_TXEMPTY_MASK))
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (!समय_after_eq(jअगरfies, समयout));

	अगर (समय_after_eq(jअगरfies, समयout))
		dev_err(xqspi->dev, "Chip select timed out\n");
पूर्ण

/**
 * zynqmp_qspi_selectspimode - Selects SPI mode - x1 or x2 or x4.
 * @xqspi:	xqspi is a poपूर्णांकer to the GQSPI instance
 * @spimode:	spimode - SPI or DUAL or QUAD.
 * Return:	Mask to set desired SPI mode in GENFIFO entry.
 */
अटल अंतरभूत u32 zynqmp_qspi_selectspimode(काष्ठा zynqmp_qspi *xqspi,
					    u8 spimode)
अणु
	u32 mask = 0;

	चयन (spimode) अणु
	हाल GQSPI_SELECT_MODE_DUALSPI:
		mask = GQSPI_GENFIFO_MODE_DUALSPI;
		अवरोध;
	हाल GQSPI_SELECT_MODE_QUADSPI:
		mask = GQSPI_GENFIFO_MODE_QUADSPI;
		अवरोध;
	हाल GQSPI_SELECT_MODE_SPI:
		mask = GQSPI_GENFIFO_MODE_SPI;
		अवरोध;
	शेष:
		dev_warn(xqspi->dev, "Invalid SPI mode\n");
	पूर्ण

	वापस mask;
पूर्ण

/**
 * zynqmp_qspi_config_op - Configure QSPI controller क्रम specअगरied
 *				transfer
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @qspi:	Poपूर्णांकer to the spi_device काष्ठाure
 *
 * Sets the operational mode of QSPI controller क्रम the next QSPI transfer and
 * sets the requested घड़ी frequency.
 *
 * Return:	Always 0
 *
 * Note:
 *	If the requested frequency is not an exact match with what can be
 *	obtained using the pre-scalar value, the driver sets the घड़ी
 *	frequency which is lower than the requested frequency (maximum lower)
 *	क्रम the transfer.
 *
 *	If the requested frequency is higher or lower than that is supported
 *	by the QSPI controller the driver will set the highest or lowest
 *	frequency supported by controller.
 */
अटल पूर्णांक zynqmp_qspi_config_op(काष्ठा zynqmp_qspi *xqspi,
				 काष्ठा spi_device *qspi)
अणु
	uदीर्घ clk_rate;
	u32 config_reg, baud_rate_val = 0;

	/* Set the घड़ी frequency */
	/* If req_hz == 0, शेष to lowest speed */
	clk_rate = clk_get_rate(xqspi->refclk);

	जबतक ((baud_rate_val < GQSPI_BAUD_DIV_MAX) &&
	       (clk_rate /
		(GQSPI_BAUD_DIV_SHIFT << baud_rate_val)) > qspi->max_speed_hz)
		baud_rate_val++;

	config_reg = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST);

	/* Set the QSPI घड़ी phase and घड़ी polarity */
	config_reg &= (~GQSPI_CFG_CLK_PHA_MASK) & (~GQSPI_CFG_CLK_POL_MASK);

	अगर (qspi->mode & SPI_CPHA)
		config_reg |= GQSPI_CFG_CLK_PHA_MASK;
	अगर (qspi->mode & SPI_CPOL)
		config_reg |= GQSPI_CFG_CLK_POL_MASK;

	config_reg &= ~GQSPI_CFG_BAUD_RATE_DIV_MASK;
	config_reg |= (baud_rate_val << GQSPI_CFG_BAUD_RATE_DIV_SHIFT);
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST, config_reg);
	वापस 0;
पूर्ण

/**
 * zynqmp_qspi_setup_op - Configure the QSPI controller
 * @qspi:	Poपूर्णांकer to the spi_device काष्ठाure
 *
 * Sets the operational mode of QSPI controller क्रम the next QSPI transfer,
 * baud rate and भागisor value to setup the requested qspi घड़ी.
 *
 * Return:	0 on success; error value otherwise.
 */
अटल पूर्णांक zynqmp_qspi_setup_op(काष्ठा spi_device *qspi)
अणु
	काष्ठा spi_controller *ctlr = qspi->master;
	काष्ठा zynqmp_qspi *xqspi = spi_controller_get_devdata(ctlr);

	अगर (ctlr->busy)
		वापस -EBUSY;

	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_EN_OFST, GQSPI_EN_MASK);

	वापस 0;
पूर्ण

/**
 * zynqmp_qspi_filltxfअगरo - Fills the TX FIFO as दीर्घ as there is room in
 *				the FIFO or the bytes required to be
 *				transmitted.
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @size:	Number of bytes to be copied from TX buffer to TX FIFO
 */
अटल व्योम zynqmp_qspi_filltxfअगरo(काष्ठा zynqmp_qspi *xqspi, पूर्णांक size)
अणु
	u32 count = 0, पूर्णांकermediate;

	जबतक ((xqspi->bytes_to_transfer > 0) && (count < size) && (xqspi->txbuf)) अणु
		अगर (xqspi->bytes_to_transfer >= 4) अणु
			स_नकल(&पूर्णांकermediate, xqspi->txbuf, 4);
			xqspi->txbuf += 4;
			xqspi->bytes_to_transfer -= 4;
			count += 4;
		पूर्ण अन्यथा अणु
			स_नकल(&पूर्णांकermediate, xqspi->txbuf,
			       xqspi->bytes_to_transfer);
			xqspi->txbuf += xqspi->bytes_to_transfer;
			xqspi->bytes_to_transfer = 0;
			count += xqspi->bytes_to_transfer;
		पूर्ण
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_TXD_OFST, पूर्णांकermediate);
	पूर्ण
पूर्ण

/**
 * zynqmp_qspi_पढ़ोrxfअगरo - Fills the RX FIFO as दीर्घ as there is room in
 *				the FIFO.
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @size:	Number of bytes to be copied from RX buffer to RX FIFO
 */
अटल व्योम zynqmp_qspi_पढ़ोrxfअगरo(काष्ठा zynqmp_qspi *xqspi, u32 size)
अणु
	uदीर्घ data;
	पूर्णांक count = 0;

	जबतक ((count < size) && (xqspi->bytes_to_receive > 0)) अणु
		अगर (xqspi->bytes_to_receive >= 4) अणु
			(*(u32 *)xqspi->rxbuf) =
			zynqmp_gqspi_पढ़ो(xqspi, GQSPI_RXD_OFST);
			xqspi->rxbuf += 4;
			xqspi->bytes_to_receive -= 4;
			count += 4;
		पूर्ण अन्यथा अणु
			data = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_RXD_OFST);
			count += xqspi->bytes_to_receive;
			zynqmp_qspi_copy_पढ़ो_data(xqspi, data,
						   xqspi->bytes_to_receive);
			xqspi->bytes_to_receive = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * zynqmp_qspi_fillgenfअगरo - Fills the GENFIFO.
 * @xqspi:	Poपूर्णांकer to the zynqmp_qspi काष्ठाure
 * @nbits:	Transfer/Receive buswidth.
 * @genfअगरoentry:       Variable in which GENFIFO mask is saved
 */
अटल व्योम zynqmp_qspi_fillgenfअगरo(काष्ठा zynqmp_qspi *xqspi, u8 nbits,
				    u32 genfअगरoentry)
अणु
	u32 transfer_len = 0;

	अगर (xqspi->txbuf) अणु
		genfअगरoentry &= ~GQSPI_GENFIFO_RX;
		genfअगरoentry |= GQSPI_GENFIFO_DATA_XFER;
		genfअगरoentry |= GQSPI_GENFIFO_TX;
		transfer_len = xqspi->bytes_to_transfer;
	पूर्ण अन्यथा अगर (xqspi->rxbuf) अणु
		genfअगरoentry &= ~GQSPI_GENFIFO_TX;
		genfअगरoentry |= GQSPI_GENFIFO_DATA_XFER;
		genfअगरoentry |= GQSPI_GENFIFO_RX;
		अगर (xqspi->mode == GQSPI_MODE_DMA)
			transfer_len = xqspi->dma_rx_bytes;
		अन्यथा
			transfer_len = xqspi->bytes_to_receive;
	पूर्ण अन्यथा अणु
		/* Sending dummy circles here */
		genfअगरoentry &= ~(GQSPI_GENFIFO_TX | GQSPI_GENFIFO_RX);
		genfअगरoentry |= GQSPI_GENFIFO_DATA_XFER;
		transfer_len = xqspi->bytes_to_transfer;
	पूर्ण
	genfअगरoentry |= zynqmp_qspi_selectspimode(xqspi, nbits);
	xqspi->genfअगरoentry = genfअगरoentry;

	अगर ((transfer_len) < GQSPI_GENFIFO_IMM_DATA_MASK) अणु
		genfअगरoentry &= ~GQSPI_GENFIFO_IMM_DATA_MASK;
		genfअगरoentry |= transfer_len;
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GEN_FIFO_OFST, genfअगरoentry);
	पूर्ण अन्यथा अणु
		पूर्णांक tempcount = transfer_len;
		u32 exponent = 8;	/* 2^8 = 256 */
		u8 imm_data = tempcount & 0xFF;

		tempcount &= ~(tempcount & 0xFF);
		/* Immediate entry */
		अगर (tempcount != 0) अणु
			/* Exponent entries */
			genfअगरoentry |= GQSPI_GENFIFO_EXP;
			जबतक (tempcount != 0) अणु
				अगर (tempcount & GQSPI_GENFIFO_EXP_START) अणु
					genfअगरoentry &=
						~GQSPI_GENFIFO_IMM_DATA_MASK;
					genfअगरoentry |= exponent;
					zynqmp_gqspi_ग_लिखो(xqspi,
							   GQSPI_GEN_FIFO_OFST,
							   genfअगरoentry);
				पूर्ण
				tempcount = tempcount >> 1;
				exponent++;
			पूर्ण
		पूर्ण
		अगर (imm_data != 0) अणु
			genfअगरoentry &= ~GQSPI_GENFIFO_EXP;
			genfअगरoentry &= ~GQSPI_GENFIFO_IMM_DATA_MASK;
			genfअगरoentry |= (u8)(imm_data & 0xFF);
			zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GEN_FIFO_OFST,
					   genfअगरoentry);
		पूर्ण
	पूर्ण
	अगर (xqspi->mode == GQSPI_MODE_IO && xqspi->rxbuf) अणु
		/* Dummy generic FIFO entry */
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GEN_FIFO_OFST, 0x0);
	पूर्ण
पूर्ण

/**
 * zynqmp_process_dma_irq - Handler क्रम DMA करोne पूर्णांकerrupt of QSPI
 *				controller
 * @xqspi:	zynqmp_qspi instance poपूर्णांकer
 *
 * This function handles DMA पूर्णांकerrupt only.
 */
अटल व्योम zynqmp_process_dma_irq(काष्ठा zynqmp_qspi *xqspi)
अणु
	u32 config_reg, genfअगरoentry;

	dma_unmap_single(xqspi->dev, xqspi->dma_addr,
			 xqspi->dma_rx_bytes, DMA_FROM_DEVICE);
	xqspi->rxbuf += xqspi->dma_rx_bytes;
	xqspi->bytes_to_receive -= xqspi->dma_rx_bytes;
	xqspi->dma_rx_bytes = 0;

	/* Disabling the DMA पूर्णांकerrupts */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_I_DIS_OFST,
			   GQSPI_QSPIDMA_DST_I_EN_DONE_MASK);

	अगर (xqspi->bytes_to_receive > 0) अणु
		/* Switch to IO mode,क्रम reमुख्यing bytes to receive */
		config_reg = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST);
		config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST, config_reg);

		/* Initiate the transfer of reमुख्यing bytes */
		genfअगरoentry = xqspi->genfअगरoentry;
		genfअगरoentry |= xqspi->bytes_to_receive;
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GEN_FIFO_OFST, genfअगरoentry);

		/* Dummy generic FIFO entry */
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_GEN_FIFO_OFST, 0x0);

		/* Manual start */
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
				   (zynqmp_gqspi_पढ़ो(xqspi,
						      GQSPI_CONFIG_OFST) |
				   GQSPI_CFG_START_GEN_FIFO_MASK));

		/* Enable the RX पूर्णांकerrupts क्रम IO mode */
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IER_OFST,
				   GQSPI_IER_GENFIFOEMPTY_MASK |
				   GQSPI_IER_RXNEMPTY_MASK |
				   GQSPI_IER_RXEMPTY_MASK);
	पूर्ण
पूर्ण

/**
 * zynqmp_qspi_irq - Interrupt service routine of the QSPI controller
 * @irq:	IRQ number
 * @dev_id:	Poपूर्णांकer to the xqspi काष्ठाure
 *
 * This function handles TX empty only.
 * On TX empty पूर्णांकerrupt this function पढ़ोs the received data from RX FIFO
 * and fills the TX FIFO अगर there is any data reमुख्यing to be transferred.
 *
 * Return:	IRQ_HANDLED when पूर्णांकerrupt is handled
 *		IRQ_NONE otherwise.
 */
अटल irqवापस_t zynqmp_qspi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zynqmp_qspi *xqspi = (काष्ठा zynqmp_qspi *)dev_id;
	irqवापस_t ret = IRQ_NONE;
	u32 status, mask, dma_status = 0;

	status = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_ISR_OFST);
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_ISR_OFST, status);
	mask = (status & ~(zynqmp_gqspi_पढ़ो(xqspi, GQSPI_IMASK_OFST)));

	/* Read and clear DMA status */
	अगर (xqspi->mode == GQSPI_MODE_DMA) अणु
		dma_status =
			zynqmp_gqspi_पढ़ो(xqspi, GQSPI_QSPIDMA_DST_I_STS_OFST);
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_I_STS_OFST,
				   dma_status);
	पूर्ण

	अगर (mask & GQSPI_ISR_TXNOT_FULL_MASK) अणु
		zynqmp_qspi_filltxfअगरo(xqspi, GQSPI_TX_FIFO_FILL);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (dma_status & GQSPI_QSPIDMA_DST_I_STS_DONE_MASK) अणु
		zynqmp_process_dma_irq(xqspi);
		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (!(mask & GQSPI_IER_RXEMPTY_MASK) &&
			(mask & GQSPI_IER_GENFIFOEMPTY_MASK)) अणु
		zynqmp_qspi_पढ़ोrxfअगरo(xqspi, GQSPI_RX_FIFO_FILL);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (xqspi->bytes_to_receive == 0 && xqspi->bytes_to_transfer == 0 &&
	    ((status & GQSPI_IRQ_MASK) == GQSPI_IRQ_MASK)) अणु
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IDR_OFST, GQSPI_ISR_IDR_MASK);
		complete(&xqspi->data_completion);
		ret = IRQ_HANDLED;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * zynqmp_qspi_setuprxdma - This function sets up the RX DMA operation
 * @xqspi:	xqspi is a poपूर्णांकer to the GQSPI instance.
 */
अटल पूर्णांक zynqmp_qspi_setuprxdma(काष्ठा zynqmp_qspi *xqspi)
अणु
	u32 rx_bytes, rx_rem, config_reg;
	dma_addr_t addr;
	u64 dma_align =  (u64)(uपूर्णांकptr_t)xqspi->rxbuf;

	अगर (xqspi->bytes_to_receive < 8 ||
	    ((dma_align & GQSPI_DMA_UNALIGN) != 0x0)) अणु
		/* Setting to IO mode */
		config_reg = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST);
		config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST, config_reg);
		xqspi->mode = GQSPI_MODE_IO;
		xqspi->dma_rx_bytes = 0;
		वापस 0;
	पूर्ण

	rx_rem = xqspi->bytes_to_receive % 4;
	rx_bytes = (xqspi->bytes_to_receive - rx_rem);

	addr = dma_map_single(xqspi->dev, (व्योम *)xqspi->rxbuf,
			      rx_bytes, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(xqspi->dev, addr)) अणु
		dev_err(xqspi->dev, "ERR:rxdma:memory not mapped\n");
		वापस -ENOMEM;
	पूर्ण

	xqspi->dma_rx_bytes = rx_bytes;
	xqspi->dma_addr = addr;
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_ADDR_OFST,
			   (u32)(addr & 0xffffffff));
	addr = ((addr >> 16) >> 16);
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_ADDR_MSB_OFST,
			   ((u32)addr) & 0xfff);

	/* Enabling the DMA mode */
	config_reg = zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST);
	config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
	config_reg |= GQSPI_CFG_MODE_EN_DMA_MASK;
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST, config_reg);

	/* Switch to DMA mode */
	xqspi->mode = GQSPI_MODE_DMA;

	/* Write the number of bytes to transfer */
	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_QSPIDMA_DST_SIZE_OFST, rx_bytes);

	वापस 0;
पूर्ण

/**
 * zynqmp_qspi_ग_लिखो_op - This function sets up the GENFIFO entries,
 *			TX FIFO, and fills the TX FIFO with as many
 *			bytes as possible.
 * @xqspi:	Poपूर्णांकer to the GQSPI instance.
 * @tx_nbits:	Transfer buswidth.
 * @genfअगरoentry:	Variable in which GENFIFO mask is वापसed
 *			to calling function
 */
अटल व्योम zynqmp_qspi_ग_लिखो_op(काष्ठा zynqmp_qspi *xqspi, u8 tx_nbits,
				 u32 genfअगरoentry)
अणु
	u32 config_reg;

	zynqmp_qspi_fillgenfअगरo(xqspi, tx_nbits, genfअगरoentry);
	zynqmp_qspi_filltxfअगरo(xqspi, GQSPI_TXD_DEPTH);
	अगर (xqspi->mode == GQSPI_MODE_DMA) अणु
		config_reg = zynqmp_gqspi_पढ़ो(xqspi,
					       GQSPI_CONFIG_OFST);
		config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
				   config_reg);
		xqspi->mode = GQSPI_MODE_IO;
	पूर्ण
पूर्ण

/**
 * zynqmp_qspi_पढ़ो_op - This function sets up the GENFIFO entries and
 *				RX DMA operation.
 * @xqspi:	xqspi is a poपूर्णांकer to the GQSPI instance.
 * @rx_nbits:	Receive buswidth.
 * @genfअगरoentry:	genfअगरoentry is poपूर्णांकer to the variable in which
 *			GENFIFO	mask is वापसed to calling function
 */
अटल पूर्णांक zynqmp_qspi_पढ़ो_op(काष्ठा zynqmp_qspi *xqspi, u8 rx_nbits,
				u32 genfअगरoentry)
अणु
	पूर्णांक ret;

	ret = zynqmp_qspi_setuprxdma(xqspi);
	अगर (ret)
		वापस ret;
	zynqmp_qspi_fillgenfअगरo(xqspi, rx_nbits, genfअगरoentry);

	वापस 0;
पूर्ण

/**
 * zynqmp_qspi_suspend - Suspend method क्रम the QSPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function stops the QSPI driver queue and disables the QSPI controller
 *
 * Return:	Always 0
 */
अटल पूर्णांक __maybe_unused zynqmp_qspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_qspi *xqspi = dev_get_drvdata(dev);
	काष्ठा spi_controller *ctlr = xqspi->ctlr;
	पूर्णांक ret;

	ret = spi_controller_suspend(ctlr);
	अगर (ret)
		वापस ret;

	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_EN_OFST, 0x0);

	वापस 0;
पूर्ण

/**
 * zynqmp_qspi_resume - Resume method क्रम the QSPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * The function starts the QSPI driver queue and initializes the QSPI
 * controller
 *
 * Return:	0 on success; error value otherwise
 */
अटल पूर्णांक __maybe_unused zynqmp_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_qspi *xqspi = dev_get_drvdata(dev);
	काष्ठा spi_controller *ctlr = xqspi->ctlr;

	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_EN_OFST, GQSPI_EN_MASK);

	spi_controller_resume(ctlr);

	वापस 0;
पूर्ण

/**
 * zynqmp_runसमय_suspend - Runसमय suspend method क्रम the SPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function disables the घड़ीs
 *
 * Return:	Always 0
 */
अटल पूर्णांक __maybe_unused zynqmp_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_qspi *xqspi = dev_get_drvdata(dev);

	clk_disable_unprepare(xqspi->refclk);
	clk_disable_unprepare(xqspi->pclk);

	वापस 0;
पूर्ण

/**
 * zynqmp_runसमय_resume - Runसमय resume method क्रम the SPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function enables the घड़ीs
 *
 * Return:	0 on success and error value on error
 */
अटल पूर्णांक __maybe_unused zynqmp_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_qspi *xqspi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(xqspi->pclk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable APB clock.\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(xqspi->refclk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable device clock.\n");
		clk_disable_unprepare(xqspi->pclk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_qspi_exec_op() - Initiates the QSPI transfer
 * @mem: The SPI memory
 * @op: The memory operation to execute
 *
 * Executes a memory operation.
 *
 * This function first selects the chip and starts the memory operation.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
अटल पूर्णांक zynqmp_qspi_exec_op(काष्ठा spi_mem *mem,
			       स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा zynqmp_qspi *xqspi = spi_controller_get_devdata
				    (mem->spi->master);
	पूर्णांक err = 0, i;
	u32 genfअगरoentry = 0;
	u16 opcode = op->cmd.opcode;
	u64 opaddr;

	dev_dbg(xqspi->dev, "cmd:%#x mode:%d.%d.%d.%d\n",
		op->cmd.opcode, op->cmd.buswidth, op->addr.buswidth,
		op->dummy.buswidth, op->data.buswidth);

	mutex_lock(&xqspi->op_lock);
	zynqmp_qspi_config_op(xqspi, mem->spi);
	zynqmp_qspi_chipselect(mem->spi, false);
	genfअगरoentry |= xqspi->genfअगरocs;
	genfअगरoentry |= xqspi->genfअगरobus;

	अगर (op->cmd.opcode) अणु
		reinit_completion(&xqspi->data_completion);
		xqspi->txbuf = &opcode;
		xqspi->rxbuf = शून्य;
		xqspi->bytes_to_transfer = op->cmd.nbytes;
		xqspi->bytes_to_receive = 0;
		zynqmp_qspi_ग_लिखो_op(xqspi, op->cmd.buswidth, genfअगरoentry);
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
				   zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST) |
				   GQSPI_CFG_START_GEN_FIFO_MASK);
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IER_OFST,
				   GQSPI_IER_GENFIFOEMPTY_MASK |
				   GQSPI_IER_TXNOT_FULL_MASK);
		अगर (!रुको_क्रम_completion_समयout
		    (&xqspi->data_completion, msecs_to_jअगरfies(1000))) अणु
			err = -ETIMEDOUT;
			जाओ वापस_err;
		पूर्ण
	पूर्ण

	अगर (op->addr.nbytes) अणु
		xqspi->txbuf = &opaddr;
		क्रम (i = 0; i < op->addr.nbytes; i++) अणु
			*(((u8 *)xqspi->txbuf) + i) = op->addr.val >>
					(8 * (op->addr.nbytes - i - 1));
		पूर्ण

		reinit_completion(&xqspi->data_completion);
		xqspi->rxbuf = शून्य;
		xqspi->bytes_to_transfer = op->addr.nbytes;
		xqspi->bytes_to_receive = 0;
		zynqmp_qspi_ग_लिखो_op(xqspi, op->addr.buswidth, genfअगरoentry);
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
				   zynqmp_gqspi_पढ़ो(xqspi,
						     GQSPI_CONFIG_OFST) |
				   GQSPI_CFG_START_GEN_FIFO_MASK);
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IER_OFST,
				   GQSPI_IER_TXEMPTY_MASK |
				   GQSPI_IER_GENFIFOEMPTY_MASK |
				   GQSPI_IER_TXNOT_FULL_MASK);
		अगर (!रुको_क्रम_completion_समयout
		    (&xqspi->data_completion, msecs_to_jअगरfies(1000))) अणु
			err = -ETIMEDOUT;
			जाओ वापस_err;
		पूर्ण
	पूर्ण

	अगर (op->dummy.nbytes) अणु
		xqspi->txbuf = शून्य;
		xqspi->rxbuf = शून्य;
		/*
		 * xqspi->bytes_to_transfer here represents the dummy circles
		 * which need to be sent.
		 */
		xqspi->bytes_to_transfer = op->dummy.nbytes * 8 / op->dummy.buswidth;
		xqspi->bytes_to_receive = 0;
		/*
		 * Using op->data.buswidth instead of op->dummy.buswidth here because
		 * we need to use it to configure the correct SPI mode.
		 */
		zynqmp_qspi_ग_लिखो_op(xqspi, op->data.buswidth,
				     genfअगरoentry);
		zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
				   zynqmp_gqspi_पढ़ो(xqspi, GQSPI_CONFIG_OFST) |
				   GQSPI_CFG_START_GEN_FIFO_MASK);
	पूर्ण

	अगर (op->data.nbytes) अणु
		reinit_completion(&xqspi->data_completion);
		अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
			xqspi->txbuf = (u8 *)op->data.buf.out;
			xqspi->rxbuf = शून्य;
			xqspi->bytes_to_transfer = op->data.nbytes;
			xqspi->bytes_to_receive = 0;
			zynqmp_qspi_ग_लिखो_op(xqspi, op->data.buswidth,
					     genfअगरoentry);
			zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
					   zynqmp_gqspi_पढ़ो
					   (xqspi, GQSPI_CONFIG_OFST) |
					   GQSPI_CFG_START_GEN_FIFO_MASK);
			zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IER_OFST,
					   GQSPI_IER_TXEMPTY_MASK |
					   GQSPI_IER_GENFIFOEMPTY_MASK |
					   GQSPI_IER_TXNOT_FULL_MASK);
		पूर्ण अन्यथा अणु
			xqspi->txbuf = शून्य;
			xqspi->rxbuf = (u8 *)op->data.buf.in;
			xqspi->bytes_to_receive = op->data.nbytes;
			xqspi->bytes_to_transfer = 0;
			err = zynqmp_qspi_पढ़ो_op(xqspi, op->data.buswidth,
					    genfअगरoentry);
			अगर (err)
				जाओ वापस_err;

			zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_CONFIG_OFST,
					   zynqmp_gqspi_पढ़ो
					   (xqspi, GQSPI_CONFIG_OFST) |
					   GQSPI_CFG_START_GEN_FIFO_MASK);
			अगर (xqspi->mode == GQSPI_MODE_DMA) अणु
				zynqmp_gqspi_ग_लिखो
					(xqspi, GQSPI_QSPIDMA_DST_I_EN_OFST,
					 GQSPI_QSPIDMA_DST_I_EN_DONE_MASK);
			पूर्ण अन्यथा अणु
				zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_IER_OFST,
						   GQSPI_IER_GENFIFOEMPTY_MASK |
						   GQSPI_IER_RXNEMPTY_MASK |
						   GQSPI_IER_RXEMPTY_MASK);
			पूर्ण
		पूर्ण
		अगर (!रुको_क्रम_completion_समयout
		    (&xqspi->data_completion, msecs_to_jअगरfies(1000)))
			err = -ETIMEDOUT;
	पूर्ण

वापस_err:

	zynqmp_qspi_chipselect(mem->spi, true);
	mutex_unlock(&xqspi->op_lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops zynqmp_qspi_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(zynqmp_runसमय_suspend,
			   zynqmp_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(zynqmp_qspi_suspend, zynqmp_qspi_resume)
पूर्ण;

अटल स्थिर काष्ठा spi_controller_mem_ops zynqmp_qspi_mem_ops = अणु
	.exec_op = zynqmp_qspi_exec_op,
पूर्ण;

/**
 * zynqmp_qspi_probe - Probe method क्रम the QSPI driver
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * This function initializes the driver data काष्ठाures and the hardware.
 *
 * Return:	0 on success; error value otherwise
 */
अटल पूर्णांक zynqmp_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा spi_controller *ctlr;
	काष्ठा zynqmp_qspi *xqspi;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;

	ctlr = spi_alloc_master(&pdev->dev, माप(*xqspi));
	अगर (!ctlr)
		वापस -ENOMEM;

	xqspi = spi_controller_get_devdata(ctlr);
	xqspi->dev = dev;
	xqspi->ctlr = ctlr;
	platक्रमm_set_drvdata(pdev, xqspi);

	xqspi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xqspi->regs)) अणु
		ret = PTR_ERR(xqspi->regs);
		जाओ हटाओ_master;
	पूर्ण

	xqspi->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(xqspi->pclk)) अणु
		dev_err(dev, "pclk clock not found.\n");
		ret = PTR_ERR(xqspi->pclk);
		जाओ हटाओ_master;
	पूर्ण

	xqspi->refclk = devm_clk_get(&pdev->dev, "ref_clk");
	अगर (IS_ERR(xqspi->refclk)) अणु
		dev_err(dev, "ref_clk clock not found.\n");
		ret = PTR_ERR(xqspi->refclk);
		जाओ हटाओ_master;
	पूर्ण

	ret = clk_prepare_enable(xqspi->pclk);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable APB clock.\n");
		जाओ हटाओ_master;
	पूर्ण

	ret = clk_prepare_enable(xqspi->refclk);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable device clock.\n");
		जाओ clk_dis_pclk;
	पूर्ण

	init_completion(&xqspi->data_completion);

	mutex_init(&xqspi->op_lock);

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, SPI_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to pm_runtime_get_sync: %d\n", ret);
		जाओ clk_dis_all;
	पूर्ण

	/* QSPI controller initializations */
	zynqmp_qspi_init_hw(xqspi);

	xqspi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (xqspi->irq <= 0) अणु
		ret = -ENXIO;
		जाओ clk_dis_all;
	पूर्ण
	ret = devm_request_irq(&pdev->dev, xqspi->irq, zynqmp_qspi_irq,
			       0, pdev->name, xqspi);
	अगर (ret != 0) अणु
		ret = -ENXIO;
		dev_err(dev, "request_irq failed\n");
		जाओ clk_dis_all;
	पूर्ण

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(44));
	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
	ctlr->num_chipselect = GQSPI_DEFAULT_NUM_CS;
	ctlr->mem_ops = &zynqmp_qspi_mem_ops;
	ctlr->setup = zynqmp_qspi_setup_op;
	ctlr->max_speed_hz = clk_get_rate(xqspi->refclk) / 2;
	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_RX_DUAL | SPI_RX_QUAD |
			    SPI_TX_DUAL | SPI_TX_QUAD;
	ctlr->dev.of_node = np;
	ctlr->स्वतः_runसमय_pm = true;

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi_register_controller failed\n");
		जाओ clk_dis_all;
	पूर्ण

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

clk_dis_all:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(xqspi->refclk);
clk_dis_pclk:
	clk_disable_unprepare(xqspi->pclk);
हटाओ_master:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

/**
 * zynqmp_qspi_हटाओ - Remove method क्रम the QSPI driver
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * This function is called अगर a device is physically हटाओd from the प्रणाली or
 * अगर the driver module is being unloaded. It मुक्तs all resources allocated to
 * the device.
 *
 * Return:	0 Always
 */
अटल पूर्णांक zynqmp_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_qspi *xqspi = platक्रमm_get_drvdata(pdev);

	zynqmp_gqspi_ग_लिखो(xqspi, GQSPI_EN_OFST, 0x0);
	clk_disable_unprepare(xqspi->refclk);
	clk_disable_unprepare(xqspi->pclk);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_qspi_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-qspi-1.0", पूर्ण,
	अणु /* End of table */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, zynqmp_qspi_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_qspi_driver = अणु
	.probe = zynqmp_qspi_probe,
	.हटाओ = zynqmp_qspi_हटाओ,
	.driver = अणु
		.name = "zynqmp-qspi",
		.of_match_table = zynqmp_qspi_of_match,
		.pm = &zynqmp_qspi_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynqmp_qspi_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx Zynqmp QSPI driver");
MODULE_LICENSE("GPL");
