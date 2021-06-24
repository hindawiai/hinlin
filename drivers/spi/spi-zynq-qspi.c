<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Xilinx, Inc.
 *
 * Author: Naga Sureshkumar Relli <nagasure@xilinx.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spi/spi-स्मृति.स>

/* Register offset definitions */
#घोषणा ZYNQ_QSPI_CONFIG_OFFSET		0x00 /* Configuration  Register, RW */
#घोषणा ZYNQ_QSPI_STATUS_OFFSET		0x04 /* Interrupt Status Register, RO */
#घोषणा ZYNQ_QSPI_IEN_OFFSET		0x08 /* Interrupt Enable Register, WO */
#घोषणा ZYNQ_QSPI_IDIS_OFFSET		0x0C /* Interrupt Disable Reg, WO */
#घोषणा ZYNQ_QSPI_IMASK_OFFSET		0x10 /* Interrupt Enabled Mask Reg,RO */
#घोषणा ZYNQ_QSPI_ENABLE_OFFSET		0x14 /* Enable/Disable Register, RW */
#घोषणा ZYNQ_QSPI_DELAY_OFFSET		0x18 /* Delay Register, RW */
#घोषणा ZYNQ_QSPI_TXD_00_00_OFFSET	0x1C /* Transmit 4-byte inst, WO */
#घोषणा ZYNQ_QSPI_TXD_00_01_OFFSET	0x80 /* Transmit 1-byte inst, WO */
#घोषणा ZYNQ_QSPI_TXD_00_10_OFFSET	0x84 /* Transmit 2-byte inst, WO */
#घोषणा ZYNQ_QSPI_TXD_00_11_OFFSET	0x88 /* Transmit 3-byte inst, WO */
#घोषणा ZYNQ_QSPI_RXD_OFFSET		0x20 /* Data Receive Register, RO */
#घोषणा ZYNQ_QSPI_SIC_OFFSET		0x24 /* Slave Idle Count Register, RW */
#घोषणा ZYNQ_QSPI_TX_THRESH_OFFSET	0x28 /* TX FIFO Watermark Reg, RW */
#घोषणा ZYNQ_QSPI_RX_THRESH_OFFSET	0x2C /* RX FIFO Watermark Reg, RW */
#घोषणा ZYNQ_QSPI_GPIO_OFFSET		0x30 /* GPIO Register, RW */
#घोषणा ZYNQ_QSPI_LINEAR_CFG_OFFSET	0xA0 /* Linear Adapter Config Ref, RW */
#घोषणा ZYNQ_QSPI_MOD_ID_OFFSET		0xFC /* Module ID Register, RO */

/*
 * QSPI Configuration Register bit Masks
 *
 * This रेजिस्टर contains various control bits that effect the operation
 * of the QSPI controller
 */
#घोषणा ZYNQ_QSPI_CONFIG_IFMODE_MASK	BIT(31) /* Flash Memory Interface */
#घोषणा ZYNQ_QSPI_CONFIG_MANSRT_MASK	BIT(16) /* Manual TX Start */
#घोषणा ZYNQ_QSPI_CONFIG_MANSRTEN_MASK	BIT(15) /* Enable Manual TX Mode */
#घोषणा ZYNQ_QSPI_CONFIG_SSFORCE_MASK	BIT(14) /* Manual Chip Select */
#घोषणा ZYNQ_QSPI_CONFIG_BDRATE_MASK	GENMASK(5, 3) /* Baud Rate Mask */
#घोषणा ZYNQ_QSPI_CONFIG_CPHA_MASK	BIT(2) /* Clock Phase Control */
#घोषणा ZYNQ_QSPI_CONFIG_CPOL_MASK	BIT(1) /* Clock Polarity Control */
#घोषणा ZYNQ_QSPI_CONFIG_FWIDTH_MASK	GENMASK(7, 6) /* FIFO width */
#घोषणा ZYNQ_QSPI_CONFIG_MSTREN_MASK	BIT(0) /* Master Mode */

/*
 * QSPI Configuration Register - Baud rate and slave select
 *
 * These are the values used in the calculation of baud rate भागisor and
 * setting the slave select.
 */
#घोषणा ZYNQ_QSPI_CONFIG_BAUD_DIV_MAX	GENMASK(2, 0) /* Baud rate maximum */
#घोषणा ZYNQ_QSPI_CONFIG_BAUD_DIV_SHIFT	3 /* Baud rate भागisor shअगरt */
#घोषणा ZYNQ_QSPI_CONFIG_PCS		BIT(10) /* Peripheral Chip Select */

/*
 * QSPI Interrupt Registers bit Masks
 *
 * All the four पूर्णांकerrupt रेजिस्टरs (Status/Mask/Enable/Disable) have the same
 * bit definitions.
 */
#घोषणा ZYNQ_QSPI_IXR_RX_OVERFLOW_MASK	BIT(0) /* QSPI RX FIFO Overflow */
#घोषणा ZYNQ_QSPI_IXR_TXNFULL_MASK	BIT(2) /* QSPI TX FIFO Overflow */
#घोषणा ZYNQ_QSPI_IXR_TXFULL_MASK	BIT(3) /* QSPI TX FIFO is full */
#घोषणा ZYNQ_QSPI_IXR_RXNEMTY_MASK	BIT(4) /* QSPI RX FIFO Not Empty */
#घोषणा ZYNQ_QSPI_IXR_RXF_FULL_MASK	BIT(5) /* QSPI RX FIFO is full */
#घोषणा ZYNQ_QSPI_IXR_TXF_UNDRFLOW_MASK	BIT(6) /* QSPI TX FIFO Underflow */
#घोषणा ZYNQ_QSPI_IXR_ALL_MASK		(ZYNQ_QSPI_IXR_RX_OVERFLOW_MASK | \
					ZYNQ_QSPI_IXR_TXNFULL_MASK | \
					ZYNQ_QSPI_IXR_TXFULL_MASK | \
					ZYNQ_QSPI_IXR_RXNEMTY_MASK | \
					ZYNQ_QSPI_IXR_RXF_FULL_MASK | \
					ZYNQ_QSPI_IXR_TXF_UNDRFLOW_MASK)
#घोषणा ZYNQ_QSPI_IXR_RXTX_MASK		(ZYNQ_QSPI_IXR_TXNFULL_MASK | \
					ZYNQ_QSPI_IXR_RXNEMTY_MASK)

/*
 * QSPI Enable Register bit Masks
 *
 * This रेजिस्टर is used to enable or disable the QSPI controller
 */
#घोषणा ZYNQ_QSPI_ENABLE_ENABLE_MASK	BIT(0) /* QSPI Enable Bit Mask */

/*
 * QSPI Linear Configuration Register
 *
 * It is named Linear Configuration but it controls other modes when not in
 * linear mode also.
 */
#घोषणा ZYNQ_QSPI_LCFG_TWO_MEM		BIT(30) /* LQSPI Two memories */
#घोषणा ZYNQ_QSPI_LCFG_SEP_BUS		BIT(29) /* LQSPI Separate bus */
#घोषणा ZYNQ_QSPI_LCFG_U_PAGE		BIT(28) /* LQSPI Upper Page */

#घोषणा ZYNQ_QSPI_LCFG_DUMMY_SHIFT	8

#घोषणा ZYNQ_QSPI_FAST_READ_QOUT_CODE	0x6B /* पढ़ो inकाष्ठाion code */
#घोषणा ZYNQ_QSPI_FIFO_DEPTH		63 /* FIFO depth in words */
#घोषणा ZYNQ_QSPI_RX_THRESHOLD		32 /* Rx FIFO threshold level */
#घोषणा ZYNQ_QSPI_TX_THRESHOLD		1 /* Tx FIFO threshold level */

/*
 * The modebits configurable by the driver to make the SPI support dअगरferent
 * data क्रमmats
 */
#घोषणा ZYNQ_QSPI_MODEBITS			(SPI_CPOL | SPI_CPHA)

/* Maximum number of chip selects */
#घोषणा ZYNQ_QSPI_MAX_NUM_CS		2

/**
 * काष्ठा zynq_qspi - Defines qspi driver instance
 * @dev:		Poपूर्णांकer to the this device's inक्रमmation
 * @regs:		Virtual address of the QSPI controller रेजिस्टरs
 * @refclk:		Poपूर्णांकer to the peripheral घड़ी
 * @pclk:		Poपूर्णांकer to the APB घड़ी
 * @irq:		IRQ number
 * @txbuf:		Poपूर्णांकer to the TX buffer
 * @rxbuf:		Poपूर्णांकer to the RX buffer
 * @tx_bytes:		Number of bytes left to transfer
 * @rx_bytes:		Number of bytes left to receive
 * @data_completion:	completion काष्ठाure
 */
काष्ठा zynq_qspi अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *refclk;
	काष्ठा clk *pclk;
	पूर्णांक irq;
	u8 *txbuf;
	u8 *rxbuf;
	पूर्णांक tx_bytes;
	पूर्णांक rx_bytes;
	काष्ठा completion data_completion;
पूर्ण;

/*
 * Inline functions क्रम the QSPI controller पढ़ो/ग_लिखो
 */
अटल अंतरभूत u32 zynq_qspi_पढ़ो(काष्ठा zynq_qspi *xqspi, u32 offset)
अणु
	वापस पढ़ोl_relaxed(xqspi->regs + offset);
पूर्ण

अटल अंतरभूत व्योम zynq_qspi_ग_लिखो(काष्ठा zynq_qspi *xqspi, u32 offset,
				   u32 val)
अणु
	ग_लिखोl_relaxed(val, xqspi->regs + offset);
पूर्ण

/**
 * zynq_qspi_init_hw - Initialize the hardware
 * @xqspi:	Poपूर्णांकer to the zynq_qspi काष्ठाure
 * @num_cs:	Number of connected CS (to enable dual memories अगर needed)
 *
 * The शेष settings of the QSPI controller's configurable parameters on
 * reset are
 *	- Master mode
 *	- Baud rate भागisor is set to 2
 *	- Tx threshold set to 1l Rx threshold set to 32
 *	- Flash memory पूर्णांकerface mode enabled
 *	- Size of the word to be transferred as 8 bit
 * This function perक्रमms the following actions
 *	- Disable and clear all the पूर्णांकerrupts
 *	- Enable manual slave select
 *	- Enable manual start
 *	- Deselect all the chip select lines
 *	- Set the size of the word to be transferred as 32 bit
 *	- Set the little endian mode of TX FIFO and
 *	- Enable the QSPI controller
 */
अटल व्योम zynq_qspi_init_hw(काष्ठा zynq_qspi *xqspi, अचिन्हित पूर्णांक num_cs)
अणु
	u32 config_reg;

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_ENABLE_OFFSET, 0);
	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_IDIS_OFFSET, ZYNQ_QSPI_IXR_ALL_MASK);

	/* Disable linear mode as the boot loader may have used it */
	config_reg = 0;
	/* At the same समय, enable dual mode अगर more than 1 CS is available */
	अगर (num_cs > 1)
		config_reg |= ZYNQ_QSPI_LCFG_TWO_MEM;

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_LINEAR_CFG_OFFSET, config_reg);

	/* Clear the RX FIFO */
	जबतक (zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_STATUS_OFFSET) &
			      ZYNQ_QSPI_IXR_RXNEMTY_MASK)
		zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_RXD_OFFSET);

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_STATUS_OFFSET, ZYNQ_QSPI_IXR_ALL_MASK);
	config_reg = zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_CONFIG_OFFSET);
	config_reg &= ~(ZYNQ_QSPI_CONFIG_MSTREN_MASK |
			ZYNQ_QSPI_CONFIG_CPOL_MASK |
			ZYNQ_QSPI_CONFIG_CPHA_MASK |
			ZYNQ_QSPI_CONFIG_BDRATE_MASK |
			ZYNQ_QSPI_CONFIG_SSFORCE_MASK |
			ZYNQ_QSPI_CONFIG_MANSRTEN_MASK |
			ZYNQ_QSPI_CONFIG_MANSRT_MASK);
	config_reg |= (ZYNQ_QSPI_CONFIG_MSTREN_MASK |
		       ZYNQ_QSPI_CONFIG_SSFORCE_MASK |
		       ZYNQ_QSPI_CONFIG_FWIDTH_MASK |
		       ZYNQ_QSPI_CONFIG_IFMODE_MASK);
	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_CONFIG_OFFSET, config_reg);

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_RX_THRESH_OFFSET,
			ZYNQ_QSPI_RX_THRESHOLD);
	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_TX_THRESH_OFFSET,
			ZYNQ_QSPI_TX_THRESHOLD);

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_ENABLE_OFFSET,
			ZYNQ_QSPI_ENABLE_ENABLE_MASK);
पूर्ण

अटल bool zynq_qspi_supports_op(काष्ठा spi_mem *mem,
				  स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (!spi_mem_शेष_supports_op(mem, op))
		वापस false;

	/*
	 * The number of address bytes should be equal to or less than 3 bytes.
	 */
	अगर (op->addr.nbytes > 3)
		वापस false;

	वापस true;
पूर्ण

/**
 * zynq_qspi_rxfअगरo_op - Read 1..4 bytes from RxFIFO to RX buffer
 * @xqspi:	Poपूर्णांकer to the zynq_qspi काष्ठाure
 * @size:	Number of bytes to be पढ़ो (1..4)
 */
अटल व्योम zynq_qspi_rxfअगरo_op(काष्ठा zynq_qspi *xqspi, अचिन्हित पूर्णांक size)
अणु
	u32 data;

	data = zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_RXD_OFFSET);

	अगर (xqspi->rxbuf) अणु
		स_नकल(xqspi->rxbuf, ((u8 *)&data) + 4 - size, size);
		xqspi->rxbuf += size;
	पूर्ण

	xqspi->rx_bytes -= size;
	अगर (xqspi->rx_bytes < 0)
		xqspi->rx_bytes = 0;
पूर्ण

/**
 * zynq_qspi_txfअगरo_op - Write 1..4 bytes from TX buffer to TxFIFO
 * @xqspi:	Poपूर्णांकer to the zynq_qspi काष्ठाure
 * @size:	Number of bytes to be written (1..4)
 */
अटल व्योम zynq_qspi_txfअगरo_op(काष्ठा zynq_qspi *xqspi, अचिन्हित पूर्णांक size)
अणु
	अटल स्थिर अचिन्हित पूर्णांक offset[4] = अणु
		ZYNQ_QSPI_TXD_00_01_OFFSET, ZYNQ_QSPI_TXD_00_10_OFFSET,
		ZYNQ_QSPI_TXD_00_11_OFFSET, ZYNQ_QSPI_TXD_00_00_OFFSET पूर्ण;
	u32 data;

	अगर (xqspi->txbuf) अणु
		data = 0xffffffff;
		स_नकल(&data, xqspi->txbuf, size);
		xqspi->txbuf += size;
	पूर्ण अन्यथा अणु
		data = 0;
	पूर्ण

	xqspi->tx_bytes -= size;
	zynq_qspi_ग_लिखो(xqspi, offset[size - 1], data);
पूर्ण

/**
 * zynq_qspi_chipselect - Select or deselect the chip select line
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 * @निश्चित:	1 क्रम select or 0 क्रम deselect the chip select line
 */
अटल व्योम zynq_qspi_chipselect(काष्ठा spi_device *spi, bool निश्चित)
अणु
	काष्ठा spi_controller *ctlr = spi->master;
	काष्ठा zynq_qspi *xqspi = spi_controller_get_devdata(ctlr);
	u32 config_reg;

	/* Select the lower (CS0) or upper (CS1) memory */
	अगर (ctlr->num_chipselect > 1) अणु
		config_reg = zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_LINEAR_CFG_OFFSET);
		अगर (!spi->chip_select)
			config_reg &= ~ZYNQ_QSPI_LCFG_U_PAGE;
		अन्यथा
			config_reg |= ZYNQ_QSPI_LCFG_U_PAGE;

		zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_LINEAR_CFG_OFFSET, config_reg);
	पूर्ण

	/* Ground the line to निश्चित the CS */
	config_reg = zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_CONFIG_OFFSET);
	अगर (निश्चित)
		config_reg &= ~ZYNQ_QSPI_CONFIG_PCS;
	अन्यथा
		config_reg |= ZYNQ_QSPI_CONFIG_PCS;

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_CONFIG_OFFSET, config_reg);
पूर्ण

/**
 * zynq_qspi_config_op - Configure QSPI controller क्रम specअगरied transfer
 * @xqspi:	Poपूर्णांकer to the zynq_qspi काष्ठाure
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 *
 * Sets the operational mode of QSPI controller क्रम the next QSPI transfer and
 * sets the requested घड़ी frequency.
 *
 * Return:	0 on success and -EINVAL on invalid input parameter
 *
 * Note: If the requested frequency is not an exact match with what can be
 * obtained using the prescalar value, the driver sets the घड़ी frequency which
 * is lower than the requested frequency (maximum lower) क्रम the transfer. If
 * the requested frequency is higher or lower than that is supported by the QSPI
 * controller the driver will set the highest or lowest frequency supported by
 * controller.
 */
अटल पूर्णांक zynq_qspi_config_op(काष्ठा zynq_qspi *xqspi, काष्ठा spi_device *spi)
अणु
	u32 config_reg, baud_rate_val = 0;

	/*
	 * Set the घड़ी frequency
	 * The baud rate भागisor is not a direct mapping to the value written
	 * पूर्णांकo the configuration रेजिस्टर (config_reg[5:3])
	 * i.e. 000 - भागide by 2
	 *      001 - भागide by 4
	 *      ----------------
	 *      111 - भागide by 256
	 */
	जबतक ((baud_rate_val < ZYNQ_QSPI_CONFIG_BAUD_DIV_MAX)  &&
	       (clk_get_rate(xqspi->refclk) / (2 << baud_rate_val)) >
		spi->max_speed_hz)
		baud_rate_val++;

	config_reg = zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_CONFIG_OFFSET);

	/* Set the QSPI घड़ी phase and घड़ी polarity */
	config_reg &= (~ZYNQ_QSPI_CONFIG_CPHA_MASK) &
		      (~ZYNQ_QSPI_CONFIG_CPOL_MASK);
	अगर (spi->mode & SPI_CPHA)
		config_reg |= ZYNQ_QSPI_CONFIG_CPHA_MASK;
	अगर (spi->mode & SPI_CPOL)
		config_reg |= ZYNQ_QSPI_CONFIG_CPOL_MASK;

	config_reg &= ~ZYNQ_QSPI_CONFIG_BDRATE_MASK;
	config_reg |= (baud_rate_val << ZYNQ_QSPI_CONFIG_BAUD_DIV_SHIFT);
	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_CONFIG_OFFSET, config_reg);

	वापस 0;
पूर्ण

/**
 * zynq_qspi_setup_op - Configure the QSPI controller
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 *
 * Sets the operational mode of QSPI controller क्रम the next QSPI transfer, baud
 * rate and भागisor value to setup the requested qspi घड़ी.
 *
 * Return:	0 on success and error value on failure
 */
अटल पूर्णांक zynq_qspi_setup_op(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr = spi->master;
	काष्ठा zynq_qspi *qspi = spi_controller_get_devdata(ctlr);

	अगर (ctlr->busy)
		वापस -EBUSY;

	clk_enable(qspi->refclk);
	clk_enable(qspi->pclk);
	zynq_qspi_ग_लिखो(qspi, ZYNQ_QSPI_ENABLE_OFFSET,
			ZYNQ_QSPI_ENABLE_ENABLE_MASK);

	वापस 0;
पूर्ण

/**
 * zynq_qspi_ग_लिखो_op - Fills the TX FIFO with as many bytes as possible
 * @xqspi:	Poपूर्णांकer to the zynq_qspi काष्ठाure
 * @txcount:	Maximum number of words to ग_लिखो
 * @txempty:	Indicates that TxFIFO is empty
 */
अटल व्योम zynq_qspi_ग_लिखो_op(काष्ठा zynq_qspi *xqspi, पूर्णांक txcount,
			       bool txempty)
अणु
	पूर्णांक count, len, k;

	len = xqspi->tx_bytes;
	अगर (len && len < 4) अणु
		/*
		 * We must empty the TxFIFO between accesses to TXD0,
		 * TXD1, TXD2, TXD3.
		 */
		अगर (txempty)
			zynq_qspi_txfअगरo_op(xqspi, len);

		वापस;
	पूर्ण

	count = len / 4;
	अगर (count > txcount)
		count = txcount;

	अगर (xqspi->txbuf) अणु
		ioग_लिखो32_rep(xqspi->regs + ZYNQ_QSPI_TXD_00_00_OFFSET,
			      xqspi->txbuf, count);
		xqspi->txbuf += count * 4;
	पूर्ण अन्यथा अणु
		क्रम (k = 0; k < count; k++)
			ग_लिखोl_relaxed(0, xqspi->regs +
					  ZYNQ_QSPI_TXD_00_00_OFFSET);
	पूर्ण

	xqspi->tx_bytes -= count * 4;
पूर्ण

/**
 * zynq_qspi_पढ़ो_op - Drains the RX FIFO by as many bytes as possible
 * @xqspi:	Poपूर्णांकer to the zynq_qspi काष्ठाure
 * @rxcount:	Maximum number of words to पढ़ो
 */
अटल व्योम zynq_qspi_पढ़ो_op(काष्ठा zynq_qspi *xqspi, पूर्णांक rxcount)
अणु
	पूर्णांक count, len, k;

	len = xqspi->rx_bytes - xqspi->tx_bytes;
	count = len / 4;
	अगर (count > rxcount)
		count = rxcount;
	अगर (xqspi->rxbuf) अणु
		ioपढ़ो32_rep(xqspi->regs + ZYNQ_QSPI_RXD_OFFSET,
			     xqspi->rxbuf, count);
		xqspi->rxbuf += count * 4;
	पूर्ण अन्यथा अणु
		क्रम (k = 0; k < count; k++)
			पढ़ोl_relaxed(xqspi->regs + ZYNQ_QSPI_RXD_OFFSET);
	पूर्ण
	xqspi->rx_bytes -= count * 4;
	len -= count * 4;

	अगर (len && len < 4 && count < rxcount)
		zynq_qspi_rxfअगरo_op(xqspi, len);
पूर्ण

/**
 * zynq_qspi_irq - Interrupt service routine of the QSPI controller
 * @irq:	IRQ number
 * @dev_id:	Poपूर्णांकer to the xqspi काष्ठाure
 *
 * This function handles TX empty only.
 * On TX empty पूर्णांकerrupt this function पढ़ोs the received data from RX FIFO and
 * fills the TX FIFO अगर there is any data reमुख्यing to be transferred.
 *
 * Return:	IRQ_HANDLED when पूर्णांकerrupt is handled; IRQ_NONE otherwise.
 */
अटल irqवापस_t zynq_qspi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पूर्णांकr_status;
	bool txempty;
	काष्ठा zynq_qspi *xqspi = (काष्ठा zynq_qspi *)dev_id;

	पूर्णांकr_status = zynq_qspi_पढ़ो(xqspi, ZYNQ_QSPI_STATUS_OFFSET);
	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_STATUS_OFFSET, पूर्णांकr_status);

	अगर ((पूर्णांकr_status & ZYNQ_QSPI_IXR_TXNFULL_MASK) ||
	    (पूर्णांकr_status & ZYNQ_QSPI_IXR_RXNEMTY_MASK)) अणु
		/*
		 * This bit is set when Tx FIFO has < THRESHOLD entries.
		 * We have the THRESHOLD value set to 1,
		 * so this bit indicates Tx FIFO is empty.
		 */
		txempty = !!(पूर्णांकr_status & ZYNQ_QSPI_IXR_TXNFULL_MASK);
		/* Read out the data from the RX FIFO */
		zynq_qspi_पढ़ो_op(xqspi, ZYNQ_QSPI_RX_THRESHOLD);
		अगर (xqspi->tx_bytes) अणु
			/* There is more data to send */
			zynq_qspi_ग_लिखो_op(xqspi, ZYNQ_QSPI_RX_THRESHOLD,
					   txempty);
		पूर्ण अन्यथा अणु
			/*
			 * If transfer and receive is completed then only send
			 * complete संकेत.
			 */
			अगर (!xqspi->rx_bytes) अणु
				zynq_qspi_ग_लिखो(xqspi,
						ZYNQ_QSPI_IDIS_OFFSET,
						ZYNQ_QSPI_IXR_RXTX_MASK);
				complete(&xqspi->data_completion);
			पूर्ण
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/**
 * zynq_qspi_exec_mem_op() - Initiates the QSPI transfer
 * @mem: the SPI memory
 * @op: the memory operation to execute
 *
 * Executes a memory operation.
 *
 * This function first selects the chip and starts the memory operation.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
अटल पूर्णांक zynq_qspi_exec_mem_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा zynq_qspi *xqspi = spi_controller_get_devdata(mem->spi->master);
	पूर्णांक err = 0, i;
	u8 *पंचांगpbuf;

	dev_dbg(xqspi->dev, "cmd:%#x mode:%d.%d.%d.%d\n",
		op->cmd.opcode, op->cmd.buswidth, op->addr.buswidth,
		op->dummy.buswidth, op->data.buswidth);

	zynq_qspi_chipselect(mem->spi, true);
	zynq_qspi_config_op(xqspi, mem->spi);

	अगर (op->cmd.opcode) अणु
		reinit_completion(&xqspi->data_completion);
		xqspi->txbuf = (u8 *)&op->cmd.opcode;
		xqspi->rxbuf = शून्य;
		xqspi->tx_bytes = op->cmd.nbytes;
		xqspi->rx_bytes = op->cmd.nbytes;
		zynq_qspi_ग_लिखो_op(xqspi, ZYNQ_QSPI_FIFO_DEPTH, true);
		zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_IEN_OFFSET,
				ZYNQ_QSPI_IXR_RXTX_MASK);
		अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout(&xqspi->data_completion,
							       msecs_to_jअगरfies(1000)))
			err = -ETIMEDOUT;
	पूर्ण

	अगर (op->addr.nbytes) अणु
		क्रम (i = 0; i < op->addr.nbytes; i++) अणु
			xqspi->txbuf[i] = op->addr.val >>
					(8 * (op->addr.nbytes - i - 1));
		पूर्ण

		reinit_completion(&xqspi->data_completion);
		xqspi->rxbuf = शून्य;
		xqspi->tx_bytes = op->addr.nbytes;
		xqspi->rx_bytes = op->addr.nbytes;
		zynq_qspi_ग_लिखो_op(xqspi, ZYNQ_QSPI_FIFO_DEPTH, true);
		zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_IEN_OFFSET,
				ZYNQ_QSPI_IXR_RXTX_MASK);
		अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout(&xqspi->data_completion,
							       msecs_to_jअगरfies(1000)))
			err = -ETIMEDOUT;
	पूर्ण

	अगर (op->dummy.nbytes) अणु
		पंचांगpbuf = kzalloc(op->dummy.nbytes, GFP_KERNEL);
		स_रखो(पंचांगpbuf, 0xff, op->dummy.nbytes);
		reinit_completion(&xqspi->data_completion);
		xqspi->txbuf = पंचांगpbuf;
		xqspi->rxbuf = शून्य;
		xqspi->tx_bytes = op->dummy.nbytes;
		xqspi->rx_bytes = op->dummy.nbytes;
		zynq_qspi_ग_लिखो_op(xqspi, ZYNQ_QSPI_FIFO_DEPTH, true);
		zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_IEN_OFFSET,
				ZYNQ_QSPI_IXR_RXTX_MASK);
		अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout(&xqspi->data_completion,
							       msecs_to_jअगरfies(1000)))
			err = -ETIMEDOUT;

		kमुक्त(पंचांगpbuf);
	पूर्ण

	अगर (op->data.nbytes) अणु
		reinit_completion(&xqspi->data_completion);
		अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
			xqspi->txbuf = (u8 *)op->data.buf.out;
			xqspi->tx_bytes = op->data.nbytes;
			xqspi->rxbuf = शून्य;
			xqspi->rx_bytes = op->data.nbytes;
		पूर्ण अन्यथा अणु
			xqspi->txbuf = शून्य;
			xqspi->rxbuf = (u8 *)op->data.buf.in;
			xqspi->rx_bytes = op->data.nbytes;
			xqspi->tx_bytes = op->data.nbytes;
		पूर्ण

		zynq_qspi_ग_लिखो_op(xqspi, ZYNQ_QSPI_FIFO_DEPTH, true);
		zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_IEN_OFFSET,
				ZYNQ_QSPI_IXR_RXTX_MASK);
		अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout(&xqspi->data_completion,
							       msecs_to_jअगरfies(1000)))
			err = -ETIMEDOUT;
	पूर्ण
	zynq_qspi_chipselect(mem->spi, false);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops zynq_qspi_mem_ops = अणु
	.supports_op = zynq_qspi_supports_op,
	.exec_op = zynq_qspi_exec_mem_op,
पूर्ण;

/**
 * zynq_qspi_probe - Probe method क्रम the QSPI driver
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * This function initializes the driver data काष्ठाures and the hardware.
 *
 * Return:	0 on success and error value on failure
 */
अटल पूर्णांक zynq_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा spi_controller *ctlr;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा zynq_qspi *xqspi;
	u32 num_cs;

	ctlr = spi_alloc_master(&pdev->dev, माप(*xqspi));
	अगर (!ctlr)
		वापस -ENOMEM;

	xqspi = spi_controller_get_devdata(ctlr);
	xqspi->dev = dev;
	platक्रमm_set_drvdata(pdev, xqspi);
	xqspi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xqspi->regs)) अणु
		ret = PTR_ERR(xqspi->regs);
		जाओ हटाओ_master;
	पूर्ण

	xqspi->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(xqspi->pclk)) अणु
		dev_err(&pdev->dev, "pclk clock not found.\n");
		ret = PTR_ERR(xqspi->pclk);
		जाओ हटाओ_master;
	पूर्ण

	init_completion(&xqspi->data_completion);

	xqspi->refclk = devm_clk_get(&pdev->dev, "ref_clk");
	अगर (IS_ERR(xqspi->refclk)) अणु
		dev_err(&pdev->dev, "ref_clk clock not found.\n");
		ret = PTR_ERR(xqspi->refclk);
		जाओ हटाओ_master;
	पूर्ण

	ret = clk_prepare_enable(xqspi->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable APB clock.\n");
		जाओ हटाओ_master;
	पूर्ण

	ret = clk_prepare_enable(xqspi->refclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable device clock.\n");
		जाओ clk_dis_pclk;
	पूर्ण

	xqspi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (xqspi->irq <= 0) अणु
		ret = -ENXIO;
		जाओ clk_dis_all;
	पूर्ण
	ret = devm_request_irq(&pdev->dev, xqspi->irq, zynq_qspi_irq,
			       0, pdev->name, xqspi);
	अगर (ret != 0) अणु
		ret = -ENXIO;
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ clk_dis_all;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "num-cs",
				   &num_cs);
	अगर (ret < 0) अणु
		ctlr->num_chipselect = 1;
	पूर्ण अन्यथा अगर (num_cs > ZYNQ_QSPI_MAX_NUM_CS) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "only 2 chip selects are available\n");
		जाओ clk_dis_all;
	पूर्ण अन्यथा अणु
		ctlr->num_chipselect = num_cs;
	पूर्ण

	ctlr->mode_bits =  SPI_RX_DUAL | SPI_RX_QUAD |
			    SPI_TX_DUAL | SPI_TX_QUAD;
	ctlr->mem_ops = &zynq_qspi_mem_ops;
	ctlr->setup = zynq_qspi_setup_op;
	ctlr->max_speed_hz = clk_get_rate(xqspi->refclk) / 2;
	ctlr->dev.of_node = np;

	/* QSPI controller initializations */
	zynq_qspi_init_hw(xqspi, ctlr->num_chipselect);

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi_register_master failed\n");
		जाओ clk_dis_all;
	पूर्ण

	वापस ret;

clk_dis_all:
	clk_disable_unprepare(xqspi->refclk);
clk_dis_pclk:
	clk_disable_unprepare(xqspi->pclk);
हटाओ_master:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

/**
 * zynq_qspi_हटाओ - Remove method क्रम the QSPI driver
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * This function is called अगर a device is physically हटाओd from the प्रणाली or
 * अगर the driver module is being unloaded. It मुक्तs all resources allocated to
 * the device.
 *
 * Return:	0 on success and error value on failure
 */
अटल पूर्णांक zynq_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynq_qspi *xqspi = platक्रमm_get_drvdata(pdev);

	zynq_qspi_ग_लिखो(xqspi, ZYNQ_QSPI_ENABLE_OFFSET, 0);

	clk_disable_unprepare(xqspi->refclk);
	clk_disable_unprepare(xqspi->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynq_qspi_of_match[] = अणु
	अणु .compatible = "xlnx,zynq-qspi-1.0", पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, zynq_qspi_of_match);

/*
 * zynq_qspi_driver - This काष्ठाure defines the QSPI platक्रमm driver
 */
अटल काष्ठा platक्रमm_driver zynq_qspi_driver = अणु
	.probe = zynq_qspi_probe,
	.हटाओ = zynq_qspi_हटाओ,
	.driver = अणु
		.name = "zynq-qspi",
		.of_match_table = zynq_qspi_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynq_qspi_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx Zynq QSPI driver");
MODULE_LICENSE("GPL");
