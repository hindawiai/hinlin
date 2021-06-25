<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP7xx SPI 100k controller driver
 * Author: Fabrice Crohas <fcrohas@gmail.com>
 * from original omap1_mcspi driver
 *
 * Copyright (C) 2005, 2006 Nokia Corporation
 * Author:      Samuel Ortiz <samuel.ortiz@nokia.com> and
 *              Juha Yrjoडटloडट <juha.yrjola@nokia.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <linux/spi/spi.h>

#घोषणा OMAP1_SPI100K_MAX_FREQ          48000000

#घोषणा ICR_SPITAS      (OMAP7XX_ICR_BASE + 0x12)

#घोषणा SPI_SETUP1      0x00
#घोषणा SPI_SETUP2      0x02
#घोषणा SPI_CTRL        0x04
#घोषणा SPI_STATUS      0x06
#घोषणा SPI_TX_LSB      0x08
#घोषणा SPI_TX_MSB      0x0a
#घोषणा SPI_RX_LSB      0x0c
#घोषणा SPI_RX_MSB      0x0e

#घोषणा SPI_SETUP1_INT_READ_ENABLE      (1UL << 5)
#घोषणा SPI_SETUP1_INT_WRITE_ENABLE     (1UL << 4)
#घोषणा SPI_SETUP1_CLOCK_DIVISOR(x)     ((x) << 1)
#घोषणा SPI_SETUP1_CLOCK_ENABLE         (1UL << 0)

#घोषणा SPI_SETUP2_ACTIVE_EDGE_FALLING  (0UL << 0)
#घोषणा SPI_SETUP2_ACTIVE_EDGE_RISING   (1UL << 0)
#घोषणा SPI_SETUP2_NEGATIVE_LEVEL       (0UL << 5)
#घोषणा SPI_SETUP2_POSITIVE_LEVEL       (1UL << 5)
#घोषणा SPI_SETUP2_LEVEL_TRIGGER        (0UL << 10)
#घोषणा SPI_SETUP2_EDGE_TRIGGER         (1UL << 10)

#घोषणा SPI_CTRL_SEN(x)                 ((x) << 7)
#घोषणा SPI_CTRL_WORD_SIZE(x)           (((x) - 1) << 2)
#घोषणा SPI_CTRL_WR                     (1UL << 1)
#घोषणा SPI_CTRL_RD                     (1UL << 0)

#घोषणा SPI_STATUS_WE                   (1UL << 1)
#घोषणा SPI_STATUS_RD                   (1UL << 0)

/* use PIO क्रम small transfers, aव्योमing DMA setup/tearकरोwn overhead and
 * cache operations; better heuristics consider wordsize and bitrate.
 */
#घोषणा DMA_MIN_BYTES                   8

#घोषणा SPI_RUNNING	0
#घोषणा SPI_SHUTDOWN	1

काष्ठा omap1_spi100k अणु
	काष्ठा clk              *ick;
	काष्ठा clk              *fck;

	/* Virtual base address of the controller */
	व्योम __iomem            *base;
पूर्ण;

काष्ठा omap1_spi100k_cs अणु
	व्योम __iomem            *base;
	पूर्णांक                     word_len;
पूर्ण;

अटल व्योम spi100k_enable_घड़ी(काष्ठा spi_master *master)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	/* enable SPI */
	val = पढ़ोw(spi100k->base + SPI_SETUP1);
	val |= SPI_SETUP1_CLOCK_ENABLE;
	ग_लिखोw(val, spi100k->base + SPI_SETUP1);
पूर्ण

अटल व्योम spi100k_disable_घड़ी(काष्ठा spi_master *master)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	/* disable SPI */
	val = पढ़ोw(spi100k->base + SPI_SETUP1);
	val &= ~SPI_SETUP1_CLOCK_ENABLE;
	ग_लिखोw(val, spi100k->base + SPI_SETUP1);
पूर्ण

अटल व्योम spi100k_ग_लिखो_data(काष्ठा spi_master *master, पूर्णांक len, पूर्णांक data)
अणु
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	/* ग_लिखो 16-bit word, shअगरting 8-bit data अगर necessary */
	अगर (len <= 8) अणु
		data <<= 8;
		len = 16;
	पूर्ण

	spi100k_enable_घड़ी(master);
	ग_लिखोw(data, spi100k->base + SPI_TX_MSB);

	ग_लिखोw(SPI_CTRL_SEN(0) |
	       SPI_CTRL_WORD_SIZE(len) |
	       SPI_CTRL_WR,
	       spi100k->base + SPI_CTRL);

	/* Wait क्रम bit ack send change */
	जबतक ((पढ़ोw(spi100k->base + SPI_STATUS) & SPI_STATUS_WE) != SPI_STATUS_WE)
		;
	udelay(1000);

	spi100k_disable_घड़ी(master);
पूर्ण

अटल पूर्णांक spi100k_पढ़ो_data(काष्ठा spi_master *master, पूर्णांक len)
अणु
	पूर्णांक dataL;
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	/* Always करो at least 16 bits */
	अगर (len <= 8)
		len = 16;

	spi100k_enable_घड़ी(master);
	ग_लिखोw(SPI_CTRL_SEN(0) |
	       SPI_CTRL_WORD_SIZE(len) |
	       SPI_CTRL_RD,
	       spi100k->base + SPI_CTRL);

	जबतक ((पढ़ोw(spi100k->base + SPI_STATUS) & SPI_STATUS_RD) != SPI_STATUS_RD)
		;
	udelay(1000);

	dataL = पढ़ोw(spi100k->base + SPI_RX_LSB);
	पढ़ोw(spi100k->base + SPI_RX_MSB);
	spi100k_disable_घड़ी(master);

	वापस dataL;
पूर्ण

अटल व्योम spi100k_खोलो(काष्ठा spi_master *master)
अणु
	/* get control of SPI */
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	ग_लिखोw(SPI_SETUP1_INT_READ_ENABLE |
	       SPI_SETUP1_INT_WRITE_ENABLE |
	       SPI_SETUP1_CLOCK_DIVISOR(0), spi100k->base + SPI_SETUP1);

	/* configure घड़ी and पूर्णांकerrupts */
	ग_लिखोw(SPI_SETUP2_ACTIVE_EDGE_FALLING |
	       SPI_SETUP2_NEGATIVE_LEVEL |
	       SPI_SETUP2_LEVEL_TRIGGER, spi100k->base + SPI_SETUP2);
पूर्ण

अटल व्योम omap1_spi100k_क्रमce_cs(काष्ठा omap1_spi100k *spi100k, पूर्णांक enable)
अणु
	अगर (enable)
		ग_लिखोw(0x05fc, spi100k->base + SPI_CTRL);
	अन्यथा
		ग_लिखोw(0x05fd, spi100k->base + SPI_CTRL);
पूर्ण

अटल अचिन्हित
omap1_spi100k_txrx_pio(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा omap1_spi100k_cs *cs = spi->controller_state;
	अचिन्हित पूर्णांक            count, c;
	पूर्णांक                     word_len;

	count = xfer->len;
	c = count;
	word_len = cs->word_len;

	अगर (word_len <= 8) अणु
		u8              *rx;
		स्थिर u8        *tx;

		rx = xfer->rx_buf;
		tx = xfer->tx_buf;
		करो अणु
			c -= 1;
			अगर (xfer->tx_buf != शून्य)
				spi100k_ग_लिखो_data(spi->master, word_len, *tx++);
			अगर (xfer->rx_buf != शून्य)
				*rx++ = spi100k_पढ़ो_data(spi->master, word_len);
		पूर्ण जबतक (c);
	पूर्ण अन्यथा अगर (word_len <= 16) अणु
		u16             *rx;
		स्थिर u16       *tx;

		rx = xfer->rx_buf;
		tx = xfer->tx_buf;
		करो अणु
			c -= 2;
			अगर (xfer->tx_buf != शून्य)
				spi100k_ग_लिखो_data(spi->master, word_len, *tx++);
			अगर (xfer->rx_buf != शून्य)
				*rx++ = spi100k_पढ़ो_data(spi->master, word_len);
		पूर्ण जबतक (c);
	पूर्ण अन्यथा अगर (word_len <= 32) अणु
		u32             *rx;
		स्थिर u32       *tx;

		rx = xfer->rx_buf;
		tx = xfer->tx_buf;
		करो अणु
			c -= 4;
			अगर (xfer->tx_buf != शून्य)
				spi100k_ग_लिखो_data(spi->master, word_len, *tx);
			अगर (xfer->rx_buf != शून्य)
				*rx = spi100k_पढ़ो_data(spi->master, word_len);
		पूर्ण जबतक (c);
	पूर्ण
	वापस count - c;
पूर्ण

/* called only when no transfer is active to this device */
अटल पूर्णांक omap1_spi100k_setup_transfer(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t)
अणु
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(spi->master);
	काष्ठा omap1_spi100k_cs *cs = spi->controller_state;
	u8 word_len;

	अगर (t != शून्य)
		word_len = t->bits_per_word;
	अन्यथा
		word_len = spi->bits_per_word;

	अगर (spi->bits_per_word > 32)
		वापस -EINVAL;
	cs->word_len = word_len;

	/* SPI init beक्रमe transfer */
	ग_लिखोw(0x3e, spi100k->base + SPI_SETUP1);
	ग_लिखोw(0x00, spi100k->base + SPI_STATUS);
	ग_लिखोw(0x3e, spi100k->base + SPI_CTRL);

	वापस 0;
पूर्ण

/* the spi->mode bits understood by this driver: */
#घोषणा MODEBITS (SPI_CPOL | SPI_CPHA | SPI_CS_HIGH)

अटल पूर्णांक omap1_spi100k_setup(काष्ठा spi_device *spi)
अणु
	पूर्णांक                     ret;
	काष्ठा omap1_spi100k    *spi100k;
	काष्ठा omap1_spi100k_cs *cs = spi->controller_state;

	spi100k = spi_master_get_devdata(spi->master);

	अगर (!cs) अणु
		cs = devm_kzalloc(&spi->dev, माप(*cs), GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		cs->base = spi100k->base + spi->chip_select * 0x14;
		spi->controller_state = cs;
	पूर्ण

	spi100k_खोलो(spi->master);

	clk_prepare_enable(spi100k->ick);
	clk_prepare_enable(spi100k->fck);

	ret = omap1_spi100k_setup_transfer(spi, शून्य);

	clk_disable_unprepare(spi100k->ick);
	clk_disable_unprepare(spi100k->fck);

	वापस ret;
पूर्ण

अटल पूर्णांक omap1_spi100k_transfer_one_message(काष्ठा spi_master *master,
					      काष्ठा spi_message *m)
अणु
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = m->spi;
	काष्ठा spi_transfer *t = शून्य;
	पूर्णांक cs_active = 0;
	पूर्णांक status = 0;

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (t->tx_buf == शून्य && t->rx_buf == शून्य && t->len) अणु
			status = -EINVAL;
			अवरोध;
		पूर्ण
		status = omap1_spi100k_setup_transfer(spi, t);
		अगर (status < 0)
			अवरोध;

		अगर (!cs_active) अणु
			omap1_spi100k_क्रमce_cs(spi100k, 1);
			cs_active = 1;
		पूर्ण

		अगर (t->len) अणु
			अचिन्हित count;

			count = omap1_spi100k_txrx_pio(spi, t);
			m->actual_length += count;

			अगर (count != t->len) अणु
				status = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण

		spi_transfer_delay_exec(t);

		/* ignore the "leave it on after last xfer" hपूर्णांक */

		अगर (t->cs_change) अणु
			omap1_spi100k_क्रमce_cs(spi100k, 0);
			cs_active = 0;
		पूर्ण
	पूर्ण

	status = omap1_spi100k_setup_transfer(spi, शून्य);

	अगर (cs_active)
		omap1_spi100k_क्रमce_cs(spi100k, 0);

	m->status = status;

	spi_finalize_current_message(master);

	वापस status;
पूर्ण

अटल पूर्णांक omap1_spi100k_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master       *master;
	काष्ठा omap1_spi100k    *spi100k;
	पूर्णांक                     status = 0;

	अगर (!pdev->id)
		वापस -EINVAL;

	master = spi_alloc_master(&pdev->dev, माप(*spi100k));
	अगर (master == शून्य) अणु
		dev_dbg(&pdev->dev, "master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (pdev->id != -1)
		master->bus_num = pdev->id;

	master->setup = omap1_spi100k_setup;
	master->transfer_one_message = omap1_spi100k_transfer_one_message;
	master->num_chipselect = 2;
	master->mode_bits = MODEBITS;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	master->min_speed_hz = OMAP1_SPI100K_MAX_FREQ/(1<<16);
	master->max_speed_hz = OMAP1_SPI100K_MAX_FREQ;
	master->स्वतः_runसमय_pm = true;

	spi100k = spi_master_get_devdata(master);

	/*
	 * The memory region base address is taken as the platक्रमm_data.
	 * You should allocate this with ioremap() beक्रमe initializing
	 * the SPI.
	 */
	spi100k->base = (व्योम __iomem *)dev_get_platdata(&pdev->dev);

	spi100k->ick = devm_clk_get(&pdev->dev, "ick");
	अगर (IS_ERR(spi100k->ick)) अणु
		dev_dbg(&pdev->dev, "can't get spi100k_ick\n");
		status = PTR_ERR(spi100k->ick);
		जाओ err;
	पूर्ण

	spi100k->fck = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(spi100k->fck)) अणु
		dev_dbg(&pdev->dev, "can't get spi100k_fck\n");
		status = PTR_ERR(spi100k->fck);
		जाओ err;
	पूर्ण

	status = clk_prepare_enable(spi100k->ick);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "failed to enable ick: %d\n", status);
		जाओ err;
	पूर्ण

	status = clk_prepare_enable(spi100k->fck);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "failed to enable fck: %d\n", status);
		जाओ err_ick;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);

	status = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (status < 0)
		जाओ err_fck;

	वापस status;

err_fck:
	clk_disable_unprepare(spi100k->fck);
err_ick:
	clk_disable_unprepare(spi100k->ick);
err:
	spi_master_put(master);
	वापस status;
पूर्ण

अटल पूर्णांक omap1_spi100k_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(spi100k->fck);
	clk_disable_unprepare(spi100k->ick);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक omap1_spi100k_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);

	clk_disable_unprepare(spi100k->ick);
	clk_disable_unprepare(spi100k->fck);

	वापस 0;
पूर्ण

अटल पूर्णांक omap1_spi100k_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा omap1_spi100k *spi100k = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(spi100k->ick);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable ick: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(spi100k->fck);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable fck: %d\n", ret);
		clk_disable_unprepare(spi100k->ick);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops omap1_spi100k_pm = अणु
	SET_RUNTIME_PM_OPS(omap1_spi100k_runसमय_suspend,
			   omap1_spi100k_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver omap1_spi100k_driver = अणु
	.driver = अणु
		.name		= "omap1_spi100k",
		.pm		= &omap1_spi100k_pm,
	पूर्ण,
	.probe		= omap1_spi100k_probe,
	.हटाओ		= omap1_spi100k_हटाओ,
पूर्ण;

module_platक्रमm_driver(omap1_spi100k_driver);

MODULE_DESCRIPTION("OMAP7xx SPI 100k controller driver");
MODULE_AUTHOR("Fabrice Crohas <fcrohas@gmail.com>");
MODULE_LICENSE("GPL");
