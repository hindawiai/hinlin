<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cadence SPI controller driver (master mode only)
 *
 * Copyright (C) 2008 - 2014 Xilinx, Inc.
 *
 * based on Blackfin On-Chip SPI Driver (spi_bfin5xx.c)
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>

/* Name of this driver */
#घोषणा CDNS_SPI_NAME		"cdns-spi"

/* Register offset definitions */
#घोषणा CDNS_SPI_CR	0x00 /* Configuration  Register, RW */
#घोषणा CDNS_SPI_ISR	0x04 /* Interrupt Status Register, RO */
#घोषणा CDNS_SPI_IER	0x08 /* Interrupt Enable Register, WO */
#घोषणा CDNS_SPI_IDR	0x0c /* Interrupt Disable Register, WO */
#घोषणा CDNS_SPI_IMR	0x10 /* Interrupt Enabled Mask Register, RO */
#घोषणा CDNS_SPI_ER	0x14 /* Enable/Disable Register, RW */
#घोषणा CDNS_SPI_DR	0x18 /* Delay Register, RW */
#घोषणा CDNS_SPI_TXD	0x1C /* Data Transmit Register, WO */
#घोषणा CDNS_SPI_RXD	0x20 /* Data Receive Register, RO */
#घोषणा CDNS_SPI_SICR	0x24 /* Slave Idle Count Register, RW */
#घोषणा CDNS_SPI_THLD	0x28 /* Transmit FIFO Watermark Register,RW */

#घोषणा SPI_AUTOSUSPEND_TIMEOUT		3000
/*
 * SPI Configuration Register bit Masks
 *
 * This रेजिस्टर contains various control bits that affect the operation
 * of the SPI controller
 */
#घोषणा CDNS_SPI_CR_MANSTRT	0x00010000 /* Manual TX Start */
#घोषणा CDNS_SPI_CR_CPHA		0x00000004 /* Clock Phase Control */
#घोषणा CDNS_SPI_CR_CPOL		0x00000002 /* Clock Polarity Control */
#घोषणा CDNS_SPI_CR_SSCTRL		0x00003C00 /* Slave Select Mask */
#घोषणा CDNS_SPI_CR_PERI_SEL	0x00000200 /* Peripheral Select Decode */
#घोषणा CDNS_SPI_CR_BAUD_DIV	0x00000038 /* Baud Rate Divisor Mask */
#घोषणा CDNS_SPI_CR_MSTREN		0x00000001 /* Master Enable Mask */
#घोषणा CDNS_SPI_CR_MANSTRTEN	0x00008000 /* Manual TX Enable Mask */
#घोषणा CDNS_SPI_CR_SSFORCE	0x00004000 /* Manual SS Enable Mask */
#घोषणा CDNS_SPI_CR_BAUD_DIV_4	0x00000008 /* Default Baud Div Mask */
#घोषणा CDNS_SPI_CR_DEFAULT	(CDNS_SPI_CR_MSTREN | \
					CDNS_SPI_CR_SSCTRL | \
					CDNS_SPI_CR_SSFORCE | \
					CDNS_SPI_CR_BAUD_DIV_4)

/*
 * SPI Configuration Register - Baud rate and slave select
 *
 * These are the values used in the calculation of baud rate भागisor and
 * setting the slave select.
 */

#घोषणा CDNS_SPI_BAUD_DIV_MAX		7 /* Baud rate भागisor maximum */
#घोषणा CDNS_SPI_BAUD_DIV_MIN		1 /* Baud rate भागisor minimum */
#घोषणा CDNS_SPI_BAUD_DIV_SHIFT		3 /* Baud rate भागisor shअगरt in CR */
#घोषणा CDNS_SPI_SS_SHIFT		10 /* Slave Select field shअगरt in CR */
#घोषणा CDNS_SPI_SS0			0x1 /* Slave Select zero */

/*
 * SPI Interrupt Registers bit Masks
 *
 * All the four पूर्णांकerrupt रेजिस्टरs (Status/Mask/Enable/Disable) have the same
 * bit definitions.
 */
#घोषणा CDNS_SPI_IXR_TXOW	0x00000004 /* SPI TX FIFO Overwater */
#घोषणा CDNS_SPI_IXR_MODF	0x00000002 /* SPI Mode Fault */
#घोषणा CDNS_SPI_IXR_RXNEMTY 0x00000010 /* SPI RX FIFO Not Empty */
#घोषणा CDNS_SPI_IXR_DEFAULT	(CDNS_SPI_IXR_TXOW | \
					CDNS_SPI_IXR_MODF)
#घोषणा CDNS_SPI_IXR_TXFULL	0x00000008 /* SPI TX Full */
#घोषणा CDNS_SPI_IXR_ALL	0x0000007F /* SPI all पूर्णांकerrupts */

/*
 * SPI Enable Register bit Masks
 *
 * This रेजिस्टर is used to enable or disable the SPI controller
 */
#घोषणा CDNS_SPI_ER_ENABLE	0x00000001 /* SPI Enable Bit Mask */
#घोषणा CDNS_SPI_ER_DISABLE	0x0 /* SPI Disable Bit Mask */

/* SPI FIFO depth in bytes */
#घोषणा CDNS_SPI_FIFO_DEPTH	128

/* Default number of chip select lines */
#घोषणा CDNS_SPI_DEFAULT_NUM_CS		4

/**
 * काष्ठा cdns_spi - This definition defines spi driver instance
 * @regs:		Virtual address of the SPI controller रेजिस्टरs
 * @ref_clk:		Poपूर्णांकer to the peripheral घड़ी
 * @pclk:		Poपूर्णांकer to the APB घड़ी
 * @speed_hz:		Current SPI bus घड़ी speed in Hz
 * @txbuf:		Poपूर्णांकer	to the TX buffer
 * @rxbuf:		Poपूर्णांकer to the RX buffer
 * @tx_bytes:		Number of bytes left to transfer
 * @rx_bytes:		Number of bytes requested
 * @dev_busy:		Device busy flag
 * @is_decoded_cs:	Flag क्रम decoder property set or not
 */
काष्ठा cdns_spi अणु
	व्योम __iomem *regs;
	काष्ठा clk *ref_clk;
	काष्ठा clk *pclk;
	अचिन्हित पूर्णांक clk_rate;
	u32 speed_hz;
	स्थिर u8 *txbuf;
	u8 *rxbuf;
	पूर्णांक tx_bytes;
	पूर्णांक rx_bytes;
	u8 dev_busy;
	u32 is_decoded_cs;
पूर्ण;

/* Macros क्रम the SPI controller पढ़ो/ग_लिखो */
अटल अंतरभूत u32 cdns_spi_पढ़ो(काष्ठा cdns_spi *xspi, u32 offset)
अणु
	वापस पढ़ोl_relaxed(xspi->regs + offset);
पूर्ण

अटल अंतरभूत व्योम cdns_spi_ग_लिखो(काष्ठा cdns_spi *xspi, u32 offset, u32 val)
अणु
	ग_लिखोl_relaxed(val, xspi->regs + offset);
पूर्ण

/**
 * cdns_spi_init_hw - Initialize the hardware and configure the SPI controller
 * @xspi:	Poपूर्णांकer to the cdns_spi काष्ठाure
 *
 * On reset the SPI controller is configured to be in master mode, baud rate
 * भागisor is set to 4, threshold value क्रम TX FIFO not full पूर्णांकerrupt is set
 * to 1 and size of the word to be transferred as 8 bit.
 * This function initializes the SPI controller to disable and clear all the
 * पूर्णांकerrupts, enable manual slave select and manual start, deselect all the
 * chip select lines, and enable the SPI controller.
 */
अटल व्योम cdns_spi_init_hw(काष्ठा cdns_spi *xspi)
अणु
	u32 ctrl_reg = CDNS_SPI_CR_DEFAULT;

	अगर (xspi->is_decoded_cs)
		ctrl_reg |= CDNS_SPI_CR_PERI_SEL;

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_DISABLE);
	cdns_spi_ग_लिखो(xspi, CDNS_SPI_IDR, CDNS_SPI_IXR_ALL);

	/* Clear the RX FIFO */
	जबतक (cdns_spi_पढ़ो(xspi, CDNS_SPI_ISR) & CDNS_SPI_IXR_RXNEMTY)
		cdns_spi_पढ़ो(xspi, CDNS_SPI_RXD);

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ISR, CDNS_SPI_IXR_ALL);
	cdns_spi_ग_लिखो(xspi, CDNS_SPI_CR, ctrl_reg);
	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_ENABLE);
पूर्ण

/**
 * cdns_spi_chipselect - Select or deselect the chip select line
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 * @is_high:	Select(0) or deselect (1) the chip select line
 */
अटल व्योम cdns_spi_chipselect(काष्ठा spi_device *spi, bool is_high)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(spi->master);
	u32 ctrl_reg;

	ctrl_reg = cdns_spi_पढ़ो(xspi, CDNS_SPI_CR);

	अगर (is_high) अणु
		/* Deselect the slave */
		ctrl_reg |= CDNS_SPI_CR_SSCTRL;
	पूर्ण अन्यथा अणु
		/* Select the slave */
		ctrl_reg &= ~CDNS_SPI_CR_SSCTRL;
		अगर (!(xspi->is_decoded_cs))
			ctrl_reg |= ((~(CDNS_SPI_SS0 << spi->chip_select)) <<
				     CDNS_SPI_SS_SHIFT) &
				     CDNS_SPI_CR_SSCTRL;
		अन्यथा
			ctrl_reg |= (spi->chip_select << CDNS_SPI_SS_SHIFT) &
				     CDNS_SPI_CR_SSCTRL;
	पूर्ण

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_CR, ctrl_reg);
पूर्ण

/**
 * cdns_spi_config_घड़ी_mode - Sets घड़ी polarity and phase
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 *
 * Sets the requested घड़ी polarity and phase.
 */
अटल व्योम cdns_spi_config_घड़ी_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(spi->master);
	u32 ctrl_reg, new_ctrl_reg;

	new_ctrl_reg = cdns_spi_पढ़ो(xspi, CDNS_SPI_CR);
	ctrl_reg = new_ctrl_reg;

	/* Set the SPI घड़ी phase and घड़ी polarity */
	new_ctrl_reg &= ~(CDNS_SPI_CR_CPHA | CDNS_SPI_CR_CPOL);
	अगर (spi->mode & SPI_CPHA)
		new_ctrl_reg |= CDNS_SPI_CR_CPHA;
	अगर (spi->mode & SPI_CPOL)
		new_ctrl_reg |= CDNS_SPI_CR_CPOL;

	अगर (new_ctrl_reg != ctrl_reg) अणु
		/*
		 * Just writing the CR रेजिस्टर करोes not seem to apply the घड़ी
		 * setting changes. This is problematic when changing the घड़ी
		 * polarity as it will cause the SPI slave to see spurious घड़ी
		 * transitions. To workaround the issue toggle the ER रेजिस्टर.
		 */
		cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_DISABLE);
		cdns_spi_ग_लिखो(xspi, CDNS_SPI_CR, new_ctrl_reg);
		cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_ENABLE);
	पूर्ण
पूर्ण

/**
 * cdns_spi_config_घड़ी_freq - Sets घड़ी frequency
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 * @transfer:	Poपूर्णांकer to the spi_transfer काष्ठाure which provides
 *		inक्रमmation about next transfer setup parameters
 *
 * Sets the requested घड़ी frequency.
 * Note: If the requested frequency is not an exact match with what can be
 * obtained using the prescalar value the driver sets the घड़ी frequency which
 * is lower than the requested frequency (maximum lower) क्रम the transfer. If
 * the requested frequency is higher or lower than that is supported by the SPI
 * controller the driver will set the highest or lowest frequency supported by
 * controller.
 */
अटल व्योम cdns_spi_config_घड़ी_freq(काष्ठा spi_device *spi,
				       काष्ठा spi_transfer *transfer)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(spi->master);
	u32 ctrl_reg, baud_rate_val;
	अचिन्हित दीर्घ frequency;

	frequency = xspi->clk_rate;

	ctrl_reg = cdns_spi_पढ़ो(xspi, CDNS_SPI_CR);

	/* Set the घड़ी frequency */
	अगर (xspi->speed_hz != transfer->speed_hz) अणु
		/* first valid value is 1 */
		baud_rate_val = CDNS_SPI_BAUD_DIV_MIN;
		जबतक ((baud_rate_val < CDNS_SPI_BAUD_DIV_MAX) &&
		       (frequency / (2 << baud_rate_val)) > transfer->speed_hz)
			baud_rate_val++;

		ctrl_reg &= ~CDNS_SPI_CR_BAUD_DIV;
		ctrl_reg |= baud_rate_val << CDNS_SPI_BAUD_DIV_SHIFT;

		xspi->speed_hz = frequency / (2 << baud_rate_val);
	पूर्ण
	cdns_spi_ग_लिखो(xspi, CDNS_SPI_CR, ctrl_reg);
पूर्ण

/**
 * cdns_spi_setup_transfer - Configure SPI controller क्रम specअगरied transfer
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 * @transfer:	Poपूर्णांकer to the spi_transfer काष्ठाure which provides
 *		inक्रमmation about next transfer setup parameters
 *
 * Sets the operational mode of SPI controller क्रम the next SPI transfer and
 * sets the requested घड़ी frequency.
 *
 * Return:	Always 0
 */
अटल पूर्णांक cdns_spi_setup_transfer(काष्ठा spi_device *spi,
				   काष्ठा spi_transfer *transfer)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(spi->master);

	cdns_spi_config_घड़ी_freq(spi, transfer);

	dev_dbg(&spi->dev, "%s, mode %d, %u bits/w, %u clock speed\n",
		__func__, spi->mode, spi->bits_per_word,
		xspi->speed_hz);

	वापस 0;
पूर्ण

/**
 * cdns_spi_fill_tx_fअगरo - Fills the TX FIFO with as many bytes as possible
 * @xspi:	Poपूर्णांकer to the cdns_spi काष्ठाure
 */
अटल व्योम cdns_spi_fill_tx_fअगरo(काष्ठा cdns_spi *xspi)
अणु
	अचिन्हित दीर्घ trans_cnt = 0;

	जबतक ((trans_cnt < CDNS_SPI_FIFO_DEPTH) &&
	       (xspi->tx_bytes > 0)) अणु

		/* When xspi in busy condition, bytes may send failed,
		 * then spi control did't work thoroughly, add one byte delay
		 */
		अगर (cdns_spi_पढ़ो(xspi, CDNS_SPI_ISR) &
		    CDNS_SPI_IXR_TXFULL)
			udelay(10);

		अगर (xspi->txbuf)
			cdns_spi_ग_लिखो(xspi, CDNS_SPI_TXD, *xspi->txbuf++);
		अन्यथा
			cdns_spi_ग_लिखो(xspi, CDNS_SPI_TXD, 0);

		xspi->tx_bytes--;
		trans_cnt++;
	पूर्ण
पूर्ण

/**
 * cdns_spi_irq - Interrupt service routine of the SPI controller
 * @irq:	IRQ number
 * @dev_id:	Poपूर्णांकer to the xspi काष्ठाure
 *
 * This function handles TX empty and Mode Fault पूर्णांकerrupts only.
 * On TX empty पूर्णांकerrupt this function पढ़ोs the received data from RX FIFO and
 * fills the TX FIFO अगर there is any data reमुख्यing to be transferred.
 * On Mode Fault पूर्णांकerrupt this function indicates that transfer is completed,
 * the SPI subप्रणाली will identअगरy the error as the reमुख्यing bytes to be
 * transferred is non-zero.
 *
 * Return:	IRQ_HANDLED when handled; IRQ_NONE otherwise.
 */
अटल irqवापस_t cdns_spi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);
	u32 पूर्णांकr_status, status;

	status = IRQ_NONE;
	पूर्णांकr_status = cdns_spi_पढ़ो(xspi, CDNS_SPI_ISR);
	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ISR, पूर्णांकr_status);

	अगर (पूर्णांकr_status & CDNS_SPI_IXR_MODF) अणु
		/* Indicate that transfer is completed, the SPI subप्रणाली will
		 * identअगरy the error as the reमुख्यing bytes to be
		 * transferred is non-zero
		 */
		cdns_spi_ग_लिखो(xspi, CDNS_SPI_IDR, CDNS_SPI_IXR_DEFAULT);
		spi_finalize_current_transfer(master);
		status = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (पूर्णांकr_status & CDNS_SPI_IXR_TXOW) अणु
		अचिन्हित दीर्घ trans_cnt;

		trans_cnt = xspi->rx_bytes - xspi->tx_bytes;

		/* Read out the data from the RX FIFO */
		जबतक (trans_cnt) अणु
			u8 data;

			data = cdns_spi_पढ़ो(xspi, CDNS_SPI_RXD);
			अगर (xspi->rxbuf)
				*xspi->rxbuf++ = data;

			xspi->rx_bytes--;
			trans_cnt--;
		पूर्ण

		अगर (xspi->tx_bytes) अणु
			/* There is more data to send */
			cdns_spi_fill_tx_fअगरo(xspi);
		पूर्ण अन्यथा अणु
			/* Transfer is completed */
			cdns_spi_ग_लिखो(xspi, CDNS_SPI_IDR,
				       CDNS_SPI_IXR_DEFAULT);
			spi_finalize_current_transfer(master);
		पूर्ण
		status = IRQ_HANDLED;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक cdns_prepare_message(काष्ठा spi_master *master,
				काष्ठा spi_message *msg)
अणु
	cdns_spi_config_घड़ी_mode(msg->spi);
	वापस 0;
पूर्ण

/**
 * cdns_transfer_one - Initiates the SPI transfer
 * @master:	Poपूर्णांकer to spi_master काष्ठाure
 * @spi:	Poपूर्णांकer to the spi_device काष्ठाure
 * @transfer:	Poपूर्णांकer to the spi_transfer काष्ठाure which provides
 *		inक्रमmation about next transfer parameters
 *
 * This function fills the TX FIFO, starts the SPI transfer and
 * वापसs a positive transfer count so that core will रुको क्रम completion.
 *
 * Return:	Number of bytes transferred in the last transfer
 */
अटल पूर्णांक cdns_transfer_one(काष्ठा spi_master *master,
			     काष्ठा spi_device *spi,
			     काष्ठा spi_transfer *transfer)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);

	xspi->txbuf = transfer->tx_buf;
	xspi->rxbuf = transfer->rx_buf;
	xspi->tx_bytes = transfer->len;
	xspi->rx_bytes = transfer->len;

	cdns_spi_setup_transfer(spi, transfer);
	cdns_spi_fill_tx_fअगरo(xspi);
	spi_transfer_delay_exec(transfer);

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_IER, CDNS_SPI_IXR_DEFAULT);
	वापस transfer->len;
पूर्ण

/**
 * cdns_prepare_transfer_hardware - Prepares hardware क्रम transfer.
 * @master:	Poपूर्णांकer to the spi_master काष्ठाure which provides
 *		inक्रमmation about the controller.
 *
 * This function enables SPI master controller.
 *
 * Return:	0 always
 */
अटल पूर्णांक cdns_prepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_ENABLE);

	वापस 0;
पूर्ण

/**
 * cdns_unprepare_transfer_hardware - Relaxes hardware after transfer
 * @master:	Poपूर्णांकer to the spi_master काष्ठाure which provides
 *		inक्रमmation about the controller.
 *
 * This function disables the SPI master controller.
 *
 * Return:	0 always
 */
अटल पूर्णांक cdns_unprepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_DISABLE);

	वापस 0;
पूर्ण

/**
 * cdns_spi_probe - Probe method क्रम the SPI driver
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * This function initializes the driver data काष्ठाures and the hardware.
 *
 * Return:	0 on success and error value on error
 */
अटल पूर्णांक cdns_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, irq;
	काष्ठा spi_master *master;
	काष्ठा cdns_spi *xspi;
	u32 num_cs;

	master = spi_alloc_master(&pdev->dev, माप(*xspi));
	अगर (!master)
		वापस -ENOMEM;

	xspi = spi_master_get_devdata(master);
	master->dev.of_node = pdev->dev.of_node;
	platक्रमm_set_drvdata(pdev, master);

	xspi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xspi->regs)) अणु
		ret = PTR_ERR(xspi->regs);
		जाओ हटाओ_master;
	पूर्ण

	xspi->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(xspi->pclk)) अणु
		dev_err(&pdev->dev, "pclk clock not found.\n");
		ret = PTR_ERR(xspi->pclk);
		जाओ हटाओ_master;
	पूर्ण

	xspi->ref_clk = devm_clk_get(&pdev->dev, "ref_clk");
	अगर (IS_ERR(xspi->ref_clk)) अणु
		dev_err(&pdev->dev, "ref_clk clock not found.\n");
		ret = PTR_ERR(xspi->ref_clk);
		जाओ हटाओ_master;
	पूर्ण

	ret = clk_prepare_enable(xspi->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable APB clock.\n");
		जाओ हटाओ_master;
	पूर्ण

	ret = clk_prepare_enable(xspi->ref_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable device clock.\n");
		जाओ clk_dis_apb;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "num-cs", &num_cs);
	अगर (ret < 0)
		master->num_chipselect = CDNS_SPI_DEFAULT_NUM_CS;
	अन्यथा
		master->num_chipselect = num_cs;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "is-decoded-cs",
				   &xspi->is_decoded_cs);
	अगर (ret < 0)
		xspi->is_decoded_cs = 0;

	/* SPI controller initializations */
	cdns_spi_init_hw(xspi);

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, SPI_AUTOSUSPEND_TIMEOUT);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		ret = -ENXIO;
		जाओ clk_dis_all;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, cdns_spi_irq,
			       0, pdev->name, master);
	अगर (ret != 0) अणु
		ret = -ENXIO;
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ clk_dis_all;
	पूर्ण

	master->use_gpio_descriptors = true;
	master->prepare_transfer_hardware = cdns_prepare_transfer_hardware;
	master->prepare_message = cdns_prepare_message;
	master->transfer_one = cdns_transfer_one;
	master->unprepare_transfer_hardware = cdns_unprepare_transfer_hardware;
	master->set_cs = cdns_spi_chipselect;
	master->स्वतः_runसमय_pm = true;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;

	xspi->clk_rate = clk_get_rate(xspi->ref_clk);
	/* Set to शेष valid value */
	master->max_speed_hz = xspi->clk_rate / 4;
	xspi->speed_hz = master->max_speed_hz;

	master->bits_per_word_mask = SPI_BPW_MASK(8);

	ret = spi_रेजिस्टर_master(master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi_register_master failed\n");
		जाओ clk_dis_all;
	पूर्ण

	वापस ret;

clk_dis_all:
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(xspi->ref_clk);
clk_dis_apb:
	clk_disable_unprepare(xspi->pclk);
हटाओ_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

/**
 * cdns_spi_हटाओ - Remove method क्रम the SPI driver
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * This function is called अगर a device is physically हटाओd from the प्रणाली or
 * अगर the driver module is being unloaded. It मुक्तs all resources allocated to
 * the device.
 *
 * Return:	0 on success and error value on error
 */
अटल पूर्णांक cdns_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);

	cdns_spi_ग_लिखो(xspi, CDNS_SPI_ER, CDNS_SPI_ER_DISABLE);

	clk_disable_unprepare(xspi->ref_clk);
	clk_disable_unprepare(xspi->pclk);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	spi_unरेजिस्टर_master(master);

	वापस 0;
पूर्ण

/**
 * cdns_spi_suspend - Suspend method क्रम the SPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function disables the SPI controller and
 * changes the driver state to "suspend"
 *
 * Return:	0 on success and error value on error
 */
अटल पूर्णांक __maybe_unused cdns_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);

	वापस spi_master_suspend(master);
पूर्ण

/**
 * cdns_spi_resume - Resume method क्रम the SPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function changes the driver state to "ready"
 *
 * Return:	0 on success and error value on error
 */
अटल पूर्णांक __maybe_unused cdns_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);

	cdns_spi_init_hw(xspi);
	वापस spi_master_resume(master);
पूर्ण

/**
 * cdns_spi_runसमय_resume - Runसमय resume method क्रम the SPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function enables the घड़ीs
 *
 * Return:	0 on success and error value on error
 */
अटल पूर्णांक __maybe_unused cnds_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(xspi->pclk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable APB clock.\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(xspi->ref_clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable device clock.\n");
		clk_disable_unprepare(xspi->pclk);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cdns_spi_runसमय_suspend - Runसमय suspend method क्रम the SPI driver
 * @dev:	Address of the platक्रमm_device काष्ठाure
 *
 * This function disables the घड़ीs
 *
 * Return:	Always 0
 */
अटल पूर्णांक __maybe_unused cnds_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा cdns_spi *xspi = spi_master_get_devdata(master);

	clk_disable_unprepare(xspi->ref_clk);
	clk_disable_unprepare(xspi->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cdns_spi_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(cnds_runसमय_suspend,
			   cnds_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(cdns_spi_suspend, cdns_spi_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_spi_of_match[] = अणु
	अणु .compatible = "xlnx,zynq-spi-r1p6" पूर्ण,
	अणु .compatible = "cdns,spi-r1p6" पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_spi_of_match);

/* cdns_spi_driver - This काष्ठाure defines the SPI subप्रणाली platक्रमm driver */
अटल काष्ठा platक्रमm_driver cdns_spi_driver = अणु
	.probe	= cdns_spi_probe,
	.हटाओ	= cdns_spi_हटाओ,
	.driver = अणु
		.name = CDNS_SPI_NAME,
		.of_match_table = cdns_spi_of_match,
		.pm = &cdns_spi_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cdns_spi_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Cadence SPI driver");
MODULE_LICENSE("GPL");
