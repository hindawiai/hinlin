<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale/Motorola Coldfire Queued SPI driver
 *
 * Copyright 2010 Steven King <sfking@fdwdc.com>
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfqspi.h>

#घोषणा	DRIVER_NAME "mcfqspi"

#घोषणा	MCFQSPI_BUSCLK			(MCF_BUSCLK / 2)

#घोषणा	MCFQSPI_QMR			0x00
#घोषणा		MCFQSPI_QMR_MSTR	0x8000
#घोषणा		MCFQSPI_QMR_CPOL	0x0200
#घोषणा		MCFQSPI_QMR_CPHA	0x0100
#घोषणा	MCFQSPI_QDLYR			0x04
#घोषणा		MCFQSPI_QDLYR_SPE	0x8000
#घोषणा	MCFQSPI_QWR			0x08
#घोषणा		MCFQSPI_QWR_HALT	0x8000
#घोषणा		MCFQSPI_QWR_WREN	0x4000
#घोषणा		MCFQSPI_QWR_CSIV	0x1000
#घोषणा	MCFQSPI_QIR			0x0C
#घोषणा		MCFQSPI_QIR_WCEFB	0x8000
#घोषणा		MCFQSPI_QIR_ABRTB	0x4000
#घोषणा		MCFQSPI_QIR_ABRTL	0x1000
#घोषणा		MCFQSPI_QIR_WCEFE	0x0800
#घोषणा		MCFQSPI_QIR_ABRTE	0x0400
#घोषणा		MCFQSPI_QIR_SPIFE	0x0100
#घोषणा		MCFQSPI_QIR_WCEF	0x0008
#घोषणा		MCFQSPI_QIR_ABRT	0x0004
#घोषणा		MCFQSPI_QIR_SPIF	0x0001
#घोषणा	MCFQSPI_QAR			0x010
#घोषणा		MCFQSPI_QAR_TXBUF	0x00
#घोषणा		MCFQSPI_QAR_RXBUF	0x10
#घोषणा		MCFQSPI_QAR_CMDBUF	0x20
#घोषणा	MCFQSPI_QDR			0x014
#घोषणा	MCFQSPI_QCR			0x014
#घोषणा		MCFQSPI_QCR_CONT	0x8000
#घोषणा		MCFQSPI_QCR_BITSE	0x4000
#घोषणा		MCFQSPI_QCR_DT		0x2000

काष्ठा mcfqspi अणु
	व्योम __iomem *iobase;
	पूर्णांक irq;
	काष्ठा clk *clk;
	काष्ठा mcfqspi_cs_control *cs_control;

	रुको_queue_head_t रुकोq;
पूर्ण;

अटल व्योम mcfqspi_wr_qmr(काष्ठा mcfqspi *mcfqspi, u16 val)
अणु
	ग_लिखोw(val, mcfqspi->iobase + MCFQSPI_QMR);
पूर्ण

अटल व्योम mcfqspi_wr_qdlyr(काष्ठा mcfqspi *mcfqspi, u16 val)
अणु
	ग_लिखोw(val, mcfqspi->iobase + MCFQSPI_QDLYR);
पूर्ण

अटल u16 mcfqspi_rd_qdlyr(काष्ठा mcfqspi *mcfqspi)
अणु
	वापस पढ़ोw(mcfqspi->iobase + MCFQSPI_QDLYR);
पूर्ण

अटल व्योम mcfqspi_wr_qwr(काष्ठा mcfqspi *mcfqspi, u16 val)
अणु
	ग_लिखोw(val, mcfqspi->iobase + MCFQSPI_QWR);
पूर्ण

अटल व्योम mcfqspi_wr_qir(काष्ठा mcfqspi *mcfqspi, u16 val)
अणु
	ग_लिखोw(val, mcfqspi->iobase + MCFQSPI_QIR);
पूर्ण

अटल व्योम mcfqspi_wr_qar(काष्ठा mcfqspi *mcfqspi, u16 val)
अणु
	ग_लिखोw(val, mcfqspi->iobase + MCFQSPI_QAR);
पूर्ण

अटल व्योम mcfqspi_wr_qdr(काष्ठा mcfqspi *mcfqspi, u16 val)
अणु
	ग_लिखोw(val, mcfqspi->iobase + MCFQSPI_QDR);
पूर्ण

अटल u16 mcfqspi_rd_qdr(काष्ठा mcfqspi *mcfqspi)
अणु
	वापस पढ़ोw(mcfqspi->iobase + MCFQSPI_QDR);
पूर्ण

अटल व्योम mcfqspi_cs_select(काष्ठा mcfqspi *mcfqspi, u8 chip_select,
			    bool cs_high)
अणु
	mcfqspi->cs_control->select(mcfqspi->cs_control, chip_select, cs_high);
पूर्ण

अटल व्योम mcfqspi_cs_deselect(काष्ठा mcfqspi *mcfqspi, u8 chip_select,
				bool cs_high)
अणु
	mcfqspi->cs_control->deselect(mcfqspi->cs_control, chip_select, cs_high);
पूर्ण

अटल पूर्णांक mcfqspi_cs_setup(काष्ठा mcfqspi *mcfqspi)
अणु
	वापस (mcfqspi->cs_control->setup) ?
		mcfqspi->cs_control->setup(mcfqspi->cs_control) : 0;
पूर्ण

अटल व्योम mcfqspi_cs_tearकरोwn(काष्ठा mcfqspi *mcfqspi)
अणु
	अगर (mcfqspi->cs_control->tearकरोwn)
		mcfqspi->cs_control->tearकरोwn(mcfqspi->cs_control);
पूर्ण

अटल u8 mcfqspi_qmr_baud(u32 speed_hz)
अणु
	वापस clamp((MCFQSPI_BUSCLK + speed_hz - 1) / speed_hz, 2u, 255u);
पूर्ण

अटल bool mcfqspi_qdlyr_spe(काष्ठा mcfqspi *mcfqspi)
अणु
	वापस mcfqspi_rd_qdlyr(mcfqspi) & MCFQSPI_QDLYR_SPE;
पूर्ण

अटल irqवापस_t mcfqspi_irq_handler(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा mcfqspi *mcfqspi = dev_id;

	/* clear पूर्णांकerrupt */
	mcfqspi_wr_qir(mcfqspi, MCFQSPI_QIR_SPIFE | MCFQSPI_QIR_SPIF);
	wake_up(&mcfqspi->रुकोq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mcfqspi_transfer_msg8(काष्ठा mcfqspi *mcfqspi, अचिन्हित count,
				  स्थिर u8 *txbuf, u8 *rxbuf)
अणु
	अचिन्हित i, n, offset = 0;

	n = min(count, 16u);

	mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_CMDBUF);
	क्रम (i = 0; i < n; ++i)
		mcfqspi_wr_qdr(mcfqspi, MCFQSPI_QCR_BITSE);

	mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_TXBUF);
	अगर (txbuf)
		क्रम (i = 0; i < n; ++i)
			mcfqspi_wr_qdr(mcfqspi, *txbuf++);
	अन्यथा
		क्रम (i = 0; i < count; ++i)
			mcfqspi_wr_qdr(mcfqspi, 0);

	count -= n;
	अगर (count) अणु
		u16 qwr = 0xf08;
		mcfqspi_wr_qwr(mcfqspi, 0x700);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);

		करो अणु
			रुको_event(mcfqspi->रुकोq, !mcfqspi_qdlyr_spe(mcfqspi));
			mcfqspi_wr_qwr(mcfqspi, qwr);
			mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
			अगर (rxbuf) अणु
				mcfqspi_wr_qar(mcfqspi,
					       MCFQSPI_QAR_RXBUF + offset);
				क्रम (i = 0; i < 8; ++i)
					*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
			पूर्ण
			n = min(count, 8u);
			अगर (txbuf) अणु
				mcfqspi_wr_qar(mcfqspi,
					       MCFQSPI_QAR_TXBUF + offset);
				क्रम (i = 0; i < n; ++i)
					mcfqspi_wr_qdr(mcfqspi, *txbuf++);
			पूर्ण
			qwr = (offset ? 0x808 : 0) + ((n - 1) << 8);
			offset ^= 8;
			count -= n;
		पूर्ण जबतक (count);
		रुको_event(mcfqspi->रुकोq, !mcfqspi_qdlyr_spe(mcfqspi));
		mcfqspi_wr_qwr(mcfqspi, qwr);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
		अगर (rxbuf) अणु
			mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_RXBUF + offset);
			क्रम (i = 0; i < 8; ++i)
				*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
			offset ^= 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		mcfqspi_wr_qwr(mcfqspi, (n - 1) << 8);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
	पूर्ण
	रुको_event(mcfqspi->रुकोq, !mcfqspi_qdlyr_spe(mcfqspi));
	अगर (rxbuf) अणु
		mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_RXBUF + offset);
		क्रम (i = 0; i < n; ++i)
			*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
	पूर्ण
पूर्ण

अटल व्योम mcfqspi_transfer_msg16(काष्ठा mcfqspi *mcfqspi, अचिन्हित count,
				   स्थिर u16 *txbuf, u16 *rxbuf)
अणु
	अचिन्हित i, n, offset = 0;

	n = min(count, 16u);

	mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_CMDBUF);
	क्रम (i = 0; i < n; ++i)
		mcfqspi_wr_qdr(mcfqspi, MCFQSPI_QCR_BITSE);

	mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_TXBUF);
	अगर (txbuf)
		क्रम (i = 0; i < n; ++i)
			mcfqspi_wr_qdr(mcfqspi, *txbuf++);
	अन्यथा
		क्रम (i = 0; i < count; ++i)
			mcfqspi_wr_qdr(mcfqspi, 0);

	count -= n;
	अगर (count) अणु
		u16 qwr = 0xf08;
		mcfqspi_wr_qwr(mcfqspi, 0x700);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);

		करो अणु
			रुको_event(mcfqspi->रुकोq, !mcfqspi_qdlyr_spe(mcfqspi));
			mcfqspi_wr_qwr(mcfqspi, qwr);
			mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
			अगर (rxbuf) अणु
				mcfqspi_wr_qar(mcfqspi,
					       MCFQSPI_QAR_RXBUF + offset);
				क्रम (i = 0; i < 8; ++i)
					*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
			पूर्ण
			n = min(count, 8u);
			अगर (txbuf) अणु
				mcfqspi_wr_qar(mcfqspi,
					       MCFQSPI_QAR_TXBUF + offset);
				क्रम (i = 0; i < n; ++i)
					mcfqspi_wr_qdr(mcfqspi, *txbuf++);
			पूर्ण
			qwr = (offset ? 0x808 : 0x000) + ((n - 1) << 8);
			offset ^= 8;
			count -= n;
		पूर्ण जबतक (count);
		रुको_event(mcfqspi->रुकोq, !mcfqspi_qdlyr_spe(mcfqspi));
		mcfqspi_wr_qwr(mcfqspi, qwr);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
		अगर (rxbuf) अणु
			mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_RXBUF + offset);
			क्रम (i = 0; i < 8; ++i)
				*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
			offset ^= 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		mcfqspi_wr_qwr(mcfqspi, (n - 1) << 8);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
	पूर्ण
	रुको_event(mcfqspi->रुकोq, !mcfqspi_qdlyr_spe(mcfqspi));
	अगर (rxbuf) अणु
		mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_RXBUF + offset);
		क्रम (i = 0; i < n; ++i)
			*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
	पूर्ण
पूर्ण

अटल व्योम mcfqspi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(spi->master);
	bool cs_high = spi->mode & SPI_CS_HIGH;

	अगर (enable)
		mcfqspi_cs_select(mcfqspi, spi->chip_select, cs_high);
	अन्यथा
		mcfqspi_cs_deselect(mcfqspi, spi->chip_select, cs_high);
पूर्ण

अटल पूर्णांक mcfqspi_transfer_one(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *t)
अणु
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(master);
	u16 qmr = MCFQSPI_QMR_MSTR;

	qmr |= t->bits_per_word << 10;
	अगर (spi->mode & SPI_CPHA)
		qmr |= MCFQSPI_QMR_CPHA;
	अगर (spi->mode & SPI_CPOL)
		qmr |= MCFQSPI_QMR_CPOL;
	qmr |= mcfqspi_qmr_baud(t->speed_hz);
	mcfqspi_wr_qmr(mcfqspi, qmr);

	mcfqspi_wr_qir(mcfqspi, MCFQSPI_QIR_SPIFE);
	अगर (t->bits_per_word == 8)
		mcfqspi_transfer_msg8(mcfqspi, t->len, t->tx_buf, t->rx_buf);
	अन्यथा
		mcfqspi_transfer_msg16(mcfqspi, t->len / 2, t->tx_buf,
				       t->rx_buf);
	mcfqspi_wr_qir(mcfqspi, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mcfqspi_setup(काष्ठा spi_device *spi)
अणु
	mcfqspi_cs_deselect(spi_master_get_devdata(spi->master),
			    spi->chip_select, spi->mode & SPI_CS_HIGH);

	dev_dbg(&spi->dev,
			"bits per word %d, chip select %d, speed %d KHz\n",
			spi->bits_per_word, spi->chip_select,
			(MCFQSPI_BUSCLK / mcfqspi_qmr_baud(spi->max_speed_hz))
			/ 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक mcfqspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा mcfqspi *mcfqspi;
	काष्ठा mcfqspi_platक्रमm_data *pdata;
	पूर्णांक status;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_dbg(&pdev->dev, "platform data is missing\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!pdata->cs_control) अणु
		dev_dbg(&pdev->dev, "pdata->cs_control is NULL\n");
		वापस -EINVAL;
	पूर्ण

	master = spi_alloc_master(&pdev->dev, माप(*mcfqspi));
	अगर (master == शून्य) अणु
		dev_dbg(&pdev->dev, "spi_alloc_master failed\n");
		वापस -ENOMEM;
	पूर्ण

	mcfqspi = spi_master_get_devdata(master);

	mcfqspi->iobase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mcfqspi->iobase)) अणु
		status = PTR_ERR(mcfqspi->iobase);
		जाओ fail0;
	पूर्ण

	mcfqspi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mcfqspi->irq < 0) अणु
		dev_dbg(&pdev->dev, "platform_get_irq failed\n");
		status = -ENXIO;
		जाओ fail0;
	पूर्ण

	status = devm_request_irq(&pdev->dev, mcfqspi->irq, mcfqspi_irq_handler,
				0, pdev->name, mcfqspi);
	अगर (status) अणु
		dev_dbg(&pdev->dev, "request_irq failed\n");
		जाओ fail0;
	पूर्ण

	mcfqspi->clk = devm_clk_get(&pdev->dev, "qspi_clk");
	अगर (IS_ERR(mcfqspi->clk)) अणु
		dev_dbg(&pdev->dev, "clk_get failed\n");
		status = PTR_ERR(mcfqspi->clk);
		जाओ fail0;
	पूर्ण
	clk_prepare_enable(mcfqspi->clk);

	master->bus_num = pdata->bus_num;
	master->num_chipselect = pdata->num_chipselect;

	mcfqspi->cs_control = pdata->cs_control;
	status = mcfqspi_cs_setup(mcfqspi);
	अगर (status) अणु
		dev_dbg(&pdev->dev, "error initializing cs_control\n");
		जाओ fail1;
	पूर्ण

	init_रुकोqueue_head(&mcfqspi->रुकोq);

	master->mode_bits = SPI_CS_HIGH | SPI_CPOL | SPI_CPHA;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 16);
	master->setup = mcfqspi_setup;
	master->set_cs = mcfqspi_set_cs;
	master->transfer_one = mcfqspi_transfer_one;
	master->स्वतः_runसमय_pm = true;

	platक्रमm_set_drvdata(pdev, master);
	pm_runसमय_enable(&pdev->dev);

	status = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (status) अणु
		dev_dbg(&pdev->dev, "spi_register_master failed\n");
		जाओ fail2;
	पूर्ण

	dev_info(&pdev->dev, "Coldfire QSPI bus driver\n");

	वापस 0;

fail2:
	pm_runसमय_disable(&pdev->dev);
	mcfqspi_cs_tearकरोwn(mcfqspi);
fail1:
	clk_disable_unprepare(mcfqspi->clk);
fail0:
	spi_master_put(master);

	dev_dbg(&pdev->dev, "Coldfire QSPI probe failed\n");

	वापस status;
पूर्ण

अटल पूर्णांक mcfqspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(master);

	pm_runसमय_disable(&pdev->dev);
	/* disable the hardware (set the baud rate to 0) */
	mcfqspi_wr_qmr(mcfqspi, MCFQSPI_QMR_MSTR);

	mcfqspi_cs_tearकरोwn(mcfqspi);
	clk_disable(mcfqspi->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mcfqspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	clk_disable(mcfqspi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mcfqspi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(master);

	clk_enable(mcfqspi->clk);

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mcfqspi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(master);

	clk_disable(mcfqspi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mcfqspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mcfqspi *mcfqspi = spi_master_get_devdata(master);

	clk_enable(mcfqspi->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mcfqspi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mcfqspi_suspend, mcfqspi_resume)
	SET_RUNTIME_PM_OPS(mcfqspi_runसमय_suspend, mcfqspi_runसमय_resume,
			शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mcfqspi_driver = अणु
	.driver.name	= DRIVER_NAME,
	.driver.owner	= THIS_MODULE,
	.driver.pm	= &mcfqspi_pm,
	.probe		= mcfqspi_probe,
	.हटाओ		= mcfqspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(mcfqspi_driver);

MODULE_AUTHOR("Steven King <sfking@fdwdc.com>");
MODULE_DESCRIPTION("Coldfire QSPI Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
