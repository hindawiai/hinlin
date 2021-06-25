<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xilinx SPI controller driver (master mode only)
 *
 * Author: MontaVista Software, Inc.
 *	source@mvista.com
 *
 * Copyright (c) 2010 Secret Lab Technologies, Ltd.
 * Copyright (c) 2009 Intel Corporation
 * 2002-2007 (c) MontaVista Software, Inc.

 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/spi/xilinx_spi.h>
#समावेश <linux/पन.स>

#घोषणा XILINX_SPI_MAX_CS	32

#घोषणा XILINX_SPI_NAME "xilinx_spi"

/* Register definitions as per "OPB Serial Peripheral Interface (SPI) (v1.00e)
 * Product Specअगरication", DS464
 */
#घोषणा XSPI_CR_OFFSET		0x60	/* Control Register */

#घोषणा XSPI_CR_LOOP		0x01
#घोषणा XSPI_CR_ENABLE		0x02
#घोषणा XSPI_CR_MASTER_MODE	0x04
#घोषणा XSPI_CR_CPOL		0x08
#घोषणा XSPI_CR_CPHA		0x10
#घोषणा XSPI_CR_MODE_MASK	(XSPI_CR_CPHA | XSPI_CR_CPOL | \
				 XSPI_CR_LSB_FIRST | XSPI_CR_LOOP)
#घोषणा XSPI_CR_TXFIFO_RESET	0x20
#घोषणा XSPI_CR_RXFIFO_RESET	0x40
#घोषणा XSPI_CR_MANUAL_SSELECT	0x80
#घोषणा XSPI_CR_TRANS_INHIBIT	0x100
#घोषणा XSPI_CR_LSB_FIRST	0x200

#घोषणा XSPI_SR_OFFSET		0x64	/* Status Register */

#घोषणा XSPI_SR_RX_EMPTY_MASK	0x01	/* Receive FIFO is empty */
#घोषणा XSPI_SR_RX_FULL_MASK	0x02	/* Receive FIFO is full */
#घोषणा XSPI_SR_TX_EMPTY_MASK	0x04	/* Transmit FIFO is empty */
#घोषणा XSPI_SR_TX_FULL_MASK	0x08	/* Transmit FIFO is full */
#घोषणा XSPI_SR_MODE_FAULT_MASK	0x10	/* Mode fault error */

#घोषणा XSPI_TXD_OFFSET		0x68	/* Data Transmit Register */
#घोषणा XSPI_RXD_OFFSET		0x6c	/* Data Receive Register */

#घोषणा XSPI_SSR_OFFSET		0x70	/* 32-bit Slave Select Register */

/* Register definitions as per "OPB IPIF (v3.01c) Product Specification", DS414
 * IPIF रेजिस्टरs are 32 bit
 */
#घोषणा XIPIF_V123B_DGIER_OFFSET	0x1c	/* IPIF global पूर्णांक enable reg */
#घोषणा XIPIF_V123B_GINTR_ENABLE	0x80000000

#घोषणा XIPIF_V123B_IISR_OFFSET		0x20	/* IPIF पूर्णांकerrupt status reg */
#घोषणा XIPIF_V123B_IIER_OFFSET		0x28	/* IPIF पूर्णांकerrupt enable reg */

#घोषणा XSPI_INTR_MODE_FAULT		0x01	/* Mode fault error */
#घोषणा XSPI_INTR_SLAVE_MODE_FAULT	0x02	/* Selected as slave जबतक
						 * disabled */
#घोषणा XSPI_INTR_TX_EMPTY		0x04	/* TxFIFO is empty */
#घोषणा XSPI_INTR_TX_UNDERRUN		0x08	/* TxFIFO was underrun */
#घोषणा XSPI_INTR_RX_FULL		0x10	/* RxFIFO is full */
#घोषणा XSPI_INTR_RX_OVERRUN		0x20	/* RxFIFO was overrun */
#घोषणा XSPI_INTR_TX_HALF_EMPTY		0x40	/* TxFIFO is half empty */

#घोषणा XIPIF_V123B_RESETR_OFFSET	0x40	/* IPIF reset रेजिस्टर */
#घोषणा XIPIF_V123B_RESET_MASK		0x0a	/* the value to ग_लिखो */

काष्ठा xilinx_spi अणु
	/* bitbang has to be first */
	काष्ठा spi_bitbang bitbang;
	काष्ठा completion करोne;
	व्योम __iomem	*regs;	/* virt. address of the control रेजिस्टरs */

	पूर्णांक		irq;

	u8 *rx_ptr;		/* poपूर्णांकer in the Tx buffer */
	स्थिर u8 *tx_ptr;	/* poपूर्णांकer in the Rx buffer */
	u8 bytes_per_word;
	पूर्णांक buffer_size;	/* buffer size in words */
	u32 cs_inactive;	/* Level of the CS pins when inactive*/
	अचिन्हित पूर्णांक (*पढ़ो_fn)(व्योम __iomem *);
	व्योम (*ग_लिखो_fn)(u32, व्योम __iomem *);
पूर्ण;

अटल व्योम xspi_ग_लिखो32(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32(val, addr);
पूर्ण

अटल अचिन्हित पूर्णांक xspi_पढ़ो32(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल व्योम xspi_ग_लिखो32_be(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

अटल अचिन्हित पूर्णांक xspi_पढ़ो32_be(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

अटल व्योम xilinx_spi_tx(काष्ठा xilinx_spi *xspi)
अणु
	u32 data = 0;

	अगर (!xspi->tx_ptr) अणु
		xspi->ग_लिखो_fn(0, xspi->regs + XSPI_TXD_OFFSET);
		वापस;
	पूर्ण

	चयन (xspi->bytes_per_word) अणु
	हाल 1:
		data = *(u8 *)(xspi->tx_ptr);
		अवरोध;
	हाल 2:
		data = *(u16 *)(xspi->tx_ptr);
		अवरोध;
	हाल 4:
		data = *(u32 *)(xspi->tx_ptr);
		अवरोध;
	पूर्ण

	xspi->ग_लिखो_fn(data, xspi->regs + XSPI_TXD_OFFSET);
	xspi->tx_ptr += xspi->bytes_per_word;
पूर्ण

अटल व्योम xilinx_spi_rx(काष्ठा xilinx_spi *xspi)
अणु
	u32 data = xspi->पढ़ो_fn(xspi->regs + XSPI_RXD_OFFSET);

	अगर (!xspi->rx_ptr)
		वापस;

	चयन (xspi->bytes_per_word) अणु
	हाल 1:
		*(u8 *)(xspi->rx_ptr) = data;
		अवरोध;
	हाल 2:
		*(u16 *)(xspi->rx_ptr) = data;
		अवरोध;
	हाल 4:
		*(u32 *)(xspi->rx_ptr) = data;
		अवरोध;
	पूर्ण

	xspi->rx_ptr += xspi->bytes_per_word;
पूर्ण

अटल व्योम xspi_init_hw(काष्ठा xilinx_spi *xspi)
अणु
	व्योम __iomem *regs_base = xspi->regs;

	/* Reset the SPI device */
	xspi->ग_लिखो_fn(XIPIF_V123B_RESET_MASK,
		regs_base + XIPIF_V123B_RESETR_OFFSET);
	/* Enable the transmit empty पूर्णांकerrupt, which we use to determine
	 * progress on the transmission.
	 */
	xspi->ग_लिखो_fn(XSPI_INTR_TX_EMPTY,
			regs_base + XIPIF_V123B_IIER_OFFSET);
	/* Disable the global IPIF पूर्णांकerrupt */
	xspi->ग_लिखो_fn(0, regs_base + XIPIF_V123B_DGIER_OFFSET);
	/* Deselect the slave on the SPI bus */
	xspi->ग_लिखो_fn(0xffff, regs_base + XSPI_SSR_OFFSET);
	/* Disable the transmitter, enable Manual Slave Select Assertion,
	 * put SPI controller पूर्णांकo master mode, and enable it */
	xspi->ग_लिखो_fn(XSPI_CR_MANUAL_SSELECT |	XSPI_CR_MASTER_MODE |
		XSPI_CR_ENABLE | XSPI_CR_TXFIFO_RESET |	XSPI_CR_RXFIFO_RESET,
		regs_base + XSPI_CR_OFFSET);
पूर्ण

अटल व्योम xilinx_spi_chipselect(काष्ठा spi_device *spi, पूर्णांक is_on)
अणु
	काष्ठा xilinx_spi *xspi = spi_master_get_devdata(spi->master);
	u16 cr;
	u32 cs;

	अगर (is_on == BITBANG_CS_INACTIVE) अणु
		/* Deselect the slave on the SPI bus */
		xspi->ग_लिखो_fn(xspi->cs_inactive, xspi->regs + XSPI_SSR_OFFSET);
		वापस;
	पूर्ण

	/* Set the SPI घड़ी phase and polarity */
	cr = xspi->पढ़ो_fn(xspi->regs + XSPI_CR_OFFSET)	& ~XSPI_CR_MODE_MASK;
	अगर (spi->mode & SPI_CPHA)
		cr |= XSPI_CR_CPHA;
	अगर (spi->mode & SPI_CPOL)
		cr |= XSPI_CR_CPOL;
	अगर (spi->mode & SPI_LSB_FIRST)
		cr |= XSPI_CR_LSB_FIRST;
	अगर (spi->mode & SPI_LOOP)
		cr |= XSPI_CR_LOOP;
	xspi->ग_लिखो_fn(cr, xspi->regs + XSPI_CR_OFFSET);

	/* We करो not check spi->max_speed_hz here as the SPI घड़ी
	 * frequency is not software programmable (the IP block design
	 * parameter)
	 */

	cs = xspi->cs_inactive;
	cs ^= BIT(spi->chip_select);

	/* Activate the chip select */
	xspi->ग_लिखो_fn(cs, xspi->regs + XSPI_SSR_OFFSET);
पूर्ण

/* spi_bitbang requires custom setup_transfer() to be defined अगर there is a
 * custom txrx_bufs().
 */
अटल पूर्णांक xilinx_spi_setup_transfer(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t)
अणु
	काष्ठा xilinx_spi *xspi = spi_master_get_devdata(spi->master);

	अगर (spi->mode & SPI_CS_HIGH)
		xspi->cs_inactive &= ~BIT(spi->chip_select);
	अन्यथा
		xspi->cs_inactive |= BIT(spi->chip_select);

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_spi_txrx_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा xilinx_spi *xspi = spi_master_get_devdata(spi->master);
	पूर्णांक reमुख्यing_words;	/* the number of words left to transfer */
	bool use_irq = false;
	u16 cr = 0;

	/* We get here with transmitter inhibited */

	xspi->tx_ptr = t->tx_buf;
	xspi->rx_ptr = t->rx_buf;
	reमुख्यing_words = t->len / xspi->bytes_per_word;

	अगर (xspi->irq >= 0 &&  reमुख्यing_words > xspi->buffer_size) अणु
		u32 isr;
		use_irq = true;
		/* Inhibit irq to aव्योम spurious irqs on tx_empty*/
		cr = xspi->पढ़ो_fn(xspi->regs + XSPI_CR_OFFSET);
		xspi->ग_लिखो_fn(cr | XSPI_CR_TRANS_INHIBIT,
			       xspi->regs + XSPI_CR_OFFSET);
		/* ACK old irqs (अगर any) */
		isr = xspi->पढ़ो_fn(xspi->regs + XIPIF_V123B_IISR_OFFSET);
		अगर (isr)
			xspi->ग_लिखो_fn(isr,
				       xspi->regs + XIPIF_V123B_IISR_OFFSET);
		/* Enable the global IPIF पूर्णांकerrupt */
		xspi->ग_लिखो_fn(XIPIF_V123B_GINTR_ENABLE,
				xspi->regs + XIPIF_V123B_DGIER_OFFSET);
		reinit_completion(&xspi->करोne);
	पूर्ण

	जबतक (reमुख्यing_words) अणु
		पूर्णांक n_words, tx_words, rx_words;
		u32 sr;
		पूर्णांक stalled;

		n_words = min(reमुख्यing_words, xspi->buffer_size);

		tx_words = n_words;
		जबतक (tx_words--)
			xilinx_spi_tx(xspi);

		/* Start the transfer by not inhibiting the transmitter any
		 * दीर्घer
		 */

		अगर (use_irq) अणु
			xspi->ग_लिखो_fn(cr, xspi->regs + XSPI_CR_OFFSET);
			रुको_क्रम_completion(&xspi->करोne);
			/* A transmit has just completed. Process received data
			 * and check क्रम more data to transmit. Always inhibit
			 * the transmitter जबतक the Isr refills the transmit
			 * रेजिस्टर/FIFO, or make sure it is stopped अगर we're
			 * करोne.
			 */
			xspi->ग_लिखो_fn(cr | XSPI_CR_TRANS_INHIBIT,
				       xspi->regs + XSPI_CR_OFFSET);
			sr = XSPI_SR_TX_EMPTY_MASK;
		पूर्ण अन्यथा
			sr = xspi->पढ़ो_fn(xspi->regs + XSPI_SR_OFFSET);

		/* Read out all the data from the Rx FIFO */
		rx_words = n_words;
		stalled = 10;
		जबतक (rx_words) अणु
			अगर (rx_words == n_words && !(stalled--) &&
			    !(sr & XSPI_SR_TX_EMPTY_MASK) &&
			    (sr & XSPI_SR_RX_EMPTY_MASK)) अणु
				dev_err(&spi->dev,
					"Detected stall. Check C_SPI_MODE and C_SPI_MEMORY\n");
				xspi_init_hw(xspi);
				वापस -EIO;
			पूर्ण

			अगर ((sr & XSPI_SR_TX_EMPTY_MASK) && (rx_words > 1)) अणु
				xilinx_spi_rx(xspi);
				rx_words--;
				जारी;
			पूर्ण

			sr = xspi->पढ़ो_fn(xspi->regs + XSPI_SR_OFFSET);
			अगर (!(sr & XSPI_SR_RX_EMPTY_MASK)) अणु
				xilinx_spi_rx(xspi);
				rx_words--;
			पूर्ण
		पूर्ण

		reमुख्यing_words -= n_words;
	पूर्ण

	अगर (use_irq) अणु
		xspi->ग_लिखो_fn(0, xspi->regs + XIPIF_V123B_DGIER_OFFSET);
		xspi->ग_लिखो_fn(cr, xspi->regs + XSPI_CR_OFFSET);
	पूर्ण

	वापस t->len;
पूर्ण


/* This driver supports single master mode only. Hence Tx FIFO Empty
 * is the only पूर्णांकerrupt we care about.
 * Receive FIFO Overrun, Transmit FIFO Underrun, Mode Fault, and Slave Mode
 * Fault are not to happen.
 */
अटल irqवापस_t xilinx_spi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xilinx_spi *xspi = dev_id;
	u32 ipअगर_isr;

	/* Get the IPIF पूर्णांकerrupts, and clear them immediately */
	ipअगर_isr = xspi->पढ़ो_fn(xspi->regs + XIPIF_V123B_IISR_OFFSET);
	xspi->ग_लिखो_fn(ipअगर_isr, xspi->regs + XIPIF_V123B_IISR_OFFSET);

	अगर (ipअगर_isr & XSPI_INTR_TX_EMPTY) अणु	/* Transmission completed */
		complete(&xspi->करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक xilinx_spi_find_buffer_size(काष्ठा xilinx_spi *xspi)
अणु
	u8 sr;
	पूर्णांक n_words = 0;

	/*
	 * Beक्रमe the buffer_size detection we reset the core
	 * to make sure we start with a clean state.
	 */
	xspi->ग_लिखो_fn(XIPIF_V123B_RESET_MASK,
		xspi->regs + XIPIF_V123B_RESETR_OFFSET);

	/* Fill the Tx FIFO with as many words as possible */
	करो अणु
		xspi->ग_लिखो_fn(0, xspi->regs + XSPI_TXD_OFFSET);
		sr = xspi->पढ़ो_fn(xspi->regs + XSPI_SR_OFFSET);
		n_words++;
	पूर्ण जबतक (!(sr & XSPI_SR_TX_FULL_MASK));

	वापस n_words;
पूर्ण

अटल स्थिर काष्ठा of_device_id xilinx_spi_of_match[] = अणु
	अणु .compatible = "xlnx,axi-quad-spi-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-spi-2.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-spi-2.00.b", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xilinx_spi_of_match);

अटल पूर्णांक xilinx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xilinx_spi *xspi;
	काष्ठा xspi_platक्रमm_data *pdata;
	काष्ठा resource *res;
	पूर्णांक ret, num_cs = 0, bits_per_word;
	काष्ठा spi_master *master;
	u32 पंचांगp;
	u8 i;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata) अणु
		num_cs = pdata->num_chipselect;
		bits_per_word = pdata->bits_per_word;
	पूर्ण अन्यथा अणु
		of_property_पढ़ो_u32(pdev->dev.of_node, "xlnx,num-ss-bits",
					  &num_cs);
		ret = of_property_पढ़ो_u32(pdev->dev.of_node,
					   "xlnx,num-transfer-bits",
					   &bits_per_word);
		अगर (ret)
			bits_per_word = 8;
	पूर्ण

	अगर (!num_cs) अणु
		dev_err(&pdev->dev,
			"Missing slave select configuration data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_cs > XILINX_SPI_MAX_CS) अणु
		dev_err(&pdev->dev, "Invalid number of spi slaves\n");
		वापस -EINVAL;
	पूर्ण

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा xilinx_spi));
	अगर (!master)
		वापस -ENODEV;

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST | SPI_LOOP |
			    SPI_CS_HIGH;

	xspi = spi_master_get_devdata(master);
	xspi->cs_inactive = 0xffffffff;
	xspi->bitbang.master = master;
	xspi->bitbang.chipselect = xilinx_spi_chipselect;
	xspi->bitbang.setup_transfer = xilinx_spi_setup_transfer;
	xspi->bitbang.txrx_bufs = xilinx_spi_txrx_bufs;
	init_completion(&xspi->करोne);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	xspi->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(xspi->regs)) अणु
		ret = PTR_ERR(xspi->regs);
		जाओ put_master;
	पूर्ण

	master->bus_num = pdev->id;
	master->num_chipselect = num_cs;
	master->dev.of_node = pdev->dev.of_node;

	/*
	 * Detect endianess on the IP via loop bit in CR. Detection
	 * must be करोne beक्रमe reset is sent because incorrect reset
	 * value generates error पूर्णांकerrupt.
	 * Setup little endian helper functions first and try to use them
	 * and check अगर bit was correctly setup or not.
	 */
	xspi->पढ़ो_fn = xspi_पढ़ो32;
	xspi->ग_लिखो_fn = xspi_ग_लिखो32;

	xspi->ग_लिखो_fn(XSPI_CR_LOOP, xspi->regs + XSPI_CR_OFFSET);
	पंचांगp = xspi->पढ़ो_fn(xspi->regs + XSPI_CR_OFFSET);
	पंचांगp &= XSPI_CR_LOOP;
	अगर (पंचांगp != XSPI_CR_LOOP) अणु
		xspi->पढ़ो_fn = xspi_पढ़ो32_be;
		xspi->ग_लिखो_fn = xspi_ग_लिखो32_be;
	पूर्ण

	master->bits_per_word_mask = SPI_BPW_MASK(bits_per_word);
	xspi->bytes_per_word = bits_per_word / 8;
	xspi->buffer_size = xilinx_spi_find_buffer_size(xspi);

	xspi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (xspi->irq < 0 && xspi->irq != -ENXIO) अणु
		ret = xspi->irq;
		जाओ put_master;
	पूर्ण अन्यथा अगर (xspi->irq >= 0) अणु
		/* Register क्रम SPI Interrupt */
		ret = devm_request_irq(&pdev->dev, xspi->irq, xilinx_spi_irq, 0,
				dev_name(&pdev->dev), xspi);
		अगर (ret)
			जाओ put_master;
	पूर्ण

	/* SPI controller initializations */
	xspi_init_hw(xspi);

	ret = spi_bitbang_start(&xspi->bitbang);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi_bitbang_start FAILED\n");
		जाओ put_master;
	पूर्ण

	dev_info(&pdev->dev, "at %pR, irq=%d\n", res, xspi->irq);

	अगर (pdata) अणु
		क्रम (i = 0; i < pdata->num_devices; i++)
			spi_new_device(master, pdata->devices + i);
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);
	वापस 0;

put_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक xilinx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा xilinx_spi *xspi = spi_master_get_devdata(master);
	व्योम __iomem *regs_base = xspi->regs;

	spi_bitbang_stop(&xspi->bitbang);

	/* Disable all the पूर्णांकerrupts just in हाल */
	xspi->ग_लिखो_fn(0, regs_base + XIPIF_V123B_IIER_OFFSET);
	/* Disable the global IPIF पूर्णांकerrupt */
	xspi->ग_लिखो_fn(0, regs_base + XIPIF_V123B_DGIER_OFFSET);

	spi_master_put(xspi->bitbang.master);

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:" XILINX_SPI_NAME);

अटल काष्ठा platक्रमm_driver xilinx_spi_driver = अणु
	.probe = xilinx_spi_probe,
	.हटाओ = xilinx_spi_हटाओ,
	.driver = अणु
		.name = XILINX_SPI_NAME,
		.of_match_table = xilinx_spi_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(xilinx_spi_driver);

MODULE_AUTHOR("MontaVista Software, Inc. <source@mvista.com>");
MODULE_DESCRIPTION("Xilinx SPI driver");
MODULE_LICENSE("GPL");
