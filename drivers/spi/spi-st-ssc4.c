<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2008-2014 STMicroelectronics Limited
 *
 *  Author: Angus Clark <Angus.Clark@st.com>
 *          Patrice Chotard <patrice.chotard@st.com>
 *          Lee Jones <lee.jones@linaro.org>
 *
 *  SPI master mode controller driver, used in STMicroelectronics devices.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>

/* SSC रेजिस्टरs */
#घोषणा SSC_BRG				0x000
#घोषणा SSC_TBUF			0x004
#घोषणा SSC_RBUF			0x008
#घोषणा SSC_CTL				0x00C
#घोषणा SSC_IEN				0x010
#घोषणा SSC_I2C				0x018

/* SSC Control */
#घोषणा SSC_CTL_DATA_WIDTH_9		0x8
#घोषणा SSC_CTL_DATA_WIDTH_MSK		0xf
#घोषणा SSC_CTL_BM			0xf
#घोषणा SSC_CTL_HB			BIT(4)
#घोषणा SSC_CTL_PH			BIT(5)
#घोषणा SSC_CTL_PO			BIT(6)
#घोषणा SSC_CTL_SR			BIT(7)
#घोषणा SSC_CTL_MS			BIT(8)
#घोषणा SSC_CTL_EN			BIT(9)
#घोषणा SSC_CTL_LPB			BIT(10)
#घोषणा SSC_CTL_EN_TX_FIFO		BIT(11)
#घोषणा SSC_CTL_EN_RX_FIFO		BIT(12)
#घोषणा SSC_CTL_EN_CLST_RX		BIT(13)

/* SSC Interrupt Enable */
#घोषणा SSC_IEN_TEEN			BIT(2)

#घोषणा FIFO_SIZE			8

काष्ठा spi_st अणु
	/* SSC SPI Controller */
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा device		*dev;

	/* SSC SPI current transaction */
	स्थिर u8		*tx_ptr;
	u8			*rx_ptr;
	u16			bytes_per_word;
	अचिन्हित पूर्णांक		words_reमुख्यing;
	अचिन्हित पूर्णांक		baud;
	काष्ठा completion	करोne;
पूर्ण;

/* Load the TX FIFO */
अटल व्योम ssc_ग_लिखो_tx_fअगरo(काष्ठा spi_st *spi_st)
अणु
	अचिन्हित पूर्णांक count, i;
	uपूर्णांक32_t word = 0;

	अगर (spi_st->words_reमुख्यing > FIFO_SIZE)
		count = FIFO_SIZE;
	अन्यथा
		count = spi_st->words_reमुख्यing;

	क्रम (i = 0; i < count; i++) अणु
		अगर (spi_st->tx_ptr) अणु
			अगर (spi_st->bytes_per_word == 1) अणु
				word = *spi_st->tx_ptr++;
			पूर्ण अन्यथा अणु
				word = *spi_st->tx_ptr++;
				word = *spi_st->tx_ptr++ | (word << 8);
			पूर्ण
		पूर्ण
		ग_लिखोl_relaxed(word, spi_st->base + SSC_TBUF);
	पूर्ण
पूर्ण

/* Read the RX FIFO */
अटल व्योम ssc_पढ़ो_rx_fअगरo(काष्ठा spi_st *spi_st)
अणु
	अचिन्हित पूर्णांक count, i;
	uपूर्णांक32_t word = 0;

	अगर (spi_st->words_reमुख्यing > FIFO_SIZE)
		count = FIFO_SIZE;
	अन्यथा
		count = spi_st->words_reमुख्यing;

	क्रम (i = 0; i < count; i++) अणु
		word = पढ़ोl_relaxed(spi_st->base + SSC_RBUF);

		अगर (spi_st->rx_ptr) अणु
			अगर (spi_st->bytes_per_word == 1) अणु
				*spi_st->rx_ptr++ = (uपूर्णांक8_t)word;
			पूर्ण अन्यथा अणु
				*spi_st->rx_ptr++ = (word >> 8);
				*spi_st->rx_ptr++ = word & 0xff;
			पूर्ण
		पूर्ण
	पूर्ण
	spi_st->words_reमुख्यing -= count;
पूर्ण

अटल पूर्णांक spi_st_transfer_one(काष्ठा spi_master *master,
			       काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_st *spi_st = spi_master_get_devdata(master);
	uपूर्णांक32_t ctl = 0;

	/* Setup transfer */
	spi_st->tx_ptr = t->tx_buf;
	spi_st->rx_ptr = t->rx_buf;

	अगर (spi->bits_per_word > 8) अणु
		/*
		 * Anything greater than 8 bits-per-word requires 2
		 * bytes-per-word in the RX/TX buffers
		 */
		spi_st->bytes_per_word = 2;
		spi_st->words_reमुख्यing = t->len / 2;

	पूर्ण अन्यथा अगर (spi->bits_per_word == 8 && !(t->len & 0x1)) अणु
		/*
		 * If transfer is even-length, and 8 bits-per-word, then
		 * implement as half-length 16 bits-per-word transfer
		 */
		spi_st->bytes_per_word = 2;
		spi_st->words_reमुख्यing = t->len / 2;

		/* Set SSC_CTL to 16 bits-per-word */
		ctl = पढ़ोl_relaxed(spi_st->base + SSC_CTL);
		ग_लिखोl_relaxed((ctl | 0xf), spi_st->base + SSC_CTL);

		पढ़ोl_relaxed(spi_st->base + SSC_RBUF);

	पूर्ण अन्यथा अणु
		spi_st->bytes_per_word = 1;
		spi_st->words_reमुख्यing = t->len;
	पूर्ण

	reinit_completion(&spi_st->करोne);

	/* Start transfer by writing to the TX FIFO */
	ssc_ग_लिखो_tx_fअगरo(spi_st);
	ग_लिखोl_relaxed(SSC_IEN_TEEN, spi_st->base + SSC_IEN);

	/* Wait क्रम transfer to complete */
	रुको_क्रम_completion(&spi_st->करोne);

	/* Restore SSC_CTL अगर necessary */
	अगर (ctl)
		ग_लिखोl_relaxed(ctl, spi_st->base + SSC_CTL);

	spi_finalize_current_transfer(spi->master);

	वापस t->len;
पूर्ण

अटल व्योम spi_st_cleanup(काष्ठा spi_device *spi)
अणु
	gpio_मुक्त(spi->cs_gpio);
पूर्ण

/* the spi->mode bits understood by this driver: */
#घोषणा MODEBITS  (SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST | SPI_LOOP | SPI_CS_HIGH)
अटल पूर्णांक spi_st_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_st *spi_st = spi_master_get_devdata(spi->master);
	u32 spi_st_clk, sscbrg, var;
	u32 hz = spi->max_speed_hz;
	पूर्णांक cs = spi->cs_gpio;
	पूर्णांक ret;

	अगर (!hz)  अणु
		dev_err(&spi->dev, "max_speed_hz unspecified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!gpio_is_valid(cs)) अणु
		dev_err(&spi->dev, "%d is not a valid gpio\n", cs);
		वापस -EINVAL;
	पूर्ण

	ret = gpio_request(cs, dev_name(&spi->dev));
	अगर (ret) अणु
		dev_err(&spi->dev, "could not request gpio:%d\n", cs);
		वापस ret;
	पूर्ण

	ret = gpio_direction_output(cs, spi->mode & SPI_CS_HIGH);
	अगर (ret)
		जाओ out_मुक्त_gpio;

	spi_st_clk = clk_get_rate(spi_st->clk);

	/* Set SSC_BRF */
	sscbrg = spi_st_clk / (2 * hz);
	अगर (sscbrg < 0x07 || sscbrg > BIT(16)) अणु
		dev_err(&spi->dev,
			"baudrate %d outside valid range %d\n", sscbrg, hz);
		ret = -EINVAL;
		जाओ out_मुक्त_gpio;
	पूर्ण

	spi_st->baud = spi_st_clk / (2 * sscbrg);
	अगर (sscbrg == BIT(16)) /* 16-bit counter wraps */
		sscbrg = 0x0;

	ग_लिखोl_relaxed(sscbrg, spi_st->base + SSC_BRG);

	dev_dbg(&spi->dev,
		"setting baudrate:target= %u hz, actual= %u hz, sscbrg= %u\n",
		hz, spi_st->baud, sscbrg);

	/* Set SSC_CTL and enable SSC */
	var = पढ़ोl_relaxed(spi_st->base + SSC_CTL);
	var |= SSC_CTL_MS;

	अगर (spi->mode & SPI_CPOL)
		var |= SSC_CTL_PO;
	अन्यथा
		var &= ~SSC_CTL_PO;

	अगर (spi->mode & SPI_CPHA)
		var |= SSC_CTL_PH;
	अन्यथा
		var &= ~SSC_CTL_PH;

	अगर ((spi->mode & SPI_LSB_FIRST) == 0)
		var |= SSC_CTL_HB;
	अन्यथा
		var &= ~SSC_CTL_HB;

	अगर (spi->mode & SPI_LOOP)
		var |= SSC_CTL_LPB;
	अन्यथा
		var &= ~SSC_CTL_LPB;

	var &= ~SSC_CTL_DATA_WIDTH_MSK;
	var |= (spi->bits_per_word - 1);

	var |= SSC_CTL_EN_TX_FIFO | SSC_CTL_EN_RX_FIFO;
	var |= SSC_CTL_EN;

	ग_लिखोl_relaxed(var, spi_st->base + SSC_CTL);

	/* Clear the status रेजिस्टर */
	पढ़ोl_relaxed(spi_st->base + SSC_RBUF);

	वापस 0;

out_मुक्त_gpio:
	gpio_मुक्त(cs);
	वापस ret;
पूर्ण

/* Interrupt fired when TX shअगरt रेजिस्टर becomes empty */
अटल irqवापस_t spi_st_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_st *spi_st = (काष्ठा spi_st *)dev_id;

	/* Read RX FIFO */
	ssc_पढ़ो_rx_fअगरo(spi_st);

	/* Fill TX FIFO */
	अगर (spi_st->words_reमुख्यing) अणु
		ssc_ग_लिखो_tx_fअगरo(spi_st);
	पूर्ण अन्यथा अणु
		/* TX/RX complete */
		ग_लिखोl_relaxed(0x0, spi_st->base + SSC_IEN);
		/*
		 * पढ़ो SSC_IEN to ensure that this bit is set
		 * beक्रमe re-enabling पूर्णांकerrupt
		 */
		पढ़ोl(spi_st->base + SSC_IEN);
		complete(&spi_st->करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spi_st_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spi_master *master;
	काष्ठा spi_st *spi_st;
	पूर्णांक irq, ret = 0;
	u32 var;

	master = spi_alloc_master(&pdev->dev, माप(*spi_st));
	अगर (!master)
		वापस -ENOMEM;

	master->dev.of_node		= np;
	master->mode_bits		= MODEBITS;
	master->setup			= spi_st_setup;
	master->cleanup			= spi_st_cleanup;
	master->transfer_one		= spi_st_transfer_one;
	master->bits_per_word_mask	= SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	master->स्वतः_runसमय_pm		= true;
	master->bus_num			= pdev->id;
	spi_st				= spi_master_get_devdata(master);

	spi_st->clk = devm_clk_get(&pdev->dev, "ssc");
	अगर (IS_ERR(spi_st->clk)) अणु
		dev_err(&pdev->dev, "Unable to request clock\n");
		ret = PTR_ERR(spi_st->clk);
		जाओ put_master;
	पूर्ण

	ret = clk_prepare_enable(spi_st->clk);
	अगर (ret)
		जाओ put_master;

	init_completion(&spi_st->करोne);

	/* Get resources */
	spi_st->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spi_st->base)) अणु
		ret = PTR_ERR(spi_st->base);
		जाओ clk_disable;
	पूर्ण

	/* Disable I2C and Reset SSC */
	ग_लिखोl_relaxed(0x0, spi_st->base + SSC_I2C);
	var = पढ़ोw_relaxed(spi_st->base + SSC_CTL);
	var |= SSC_CTL_SR;
	ग_लिखोl_relaxed(var, spi_st->base + SSC_CTL);

	udelay(1);
	var = पढ़ोl_relaxed(spi_st->base + SSC_CTL);
	var &= ~SSC_CTL_SR;
	ग_लिखोl_relaxed(var, spi_st->base + SSC_CTL);

	/* Set SSC पूर्णांकo slave mode beक्रमe reconfiguring PIO pins */
	var = पढ़ोl_relaxed(spi_st->base + SSC_CTL);
	var &= ~SSC_CTL_MS;
	ग_लिखोl_relaxed(var, spi_st->base + SSC_CTL);

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "IRQ missing or invalid\n");
		ret = -EINVAL;
		जाओ clk_disable;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, spi_st_irq, 0,
			       pdev->name, spi_st);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq %d\n", irq);
		जाओ clk_disable;
	पूर्ण

	/* by शेष the device is on */
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	platक्रमm_set_drvdata(pdev, master);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register master\n");
		जाओ rpm_disable;
	पूर्ण

	वापस 0;

rpm_disable:
	pm_runसमय_disable(&pdev->dev);
clk_disable:
	clk_disable_unprepare(spi_st->clk);
put_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_st_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा spi_st *spi_st = spi_master_get_devdata(master);

	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(spi_st->clk);

	pinctrl_pm_select_sleep_state(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक spi_st_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा spi_st *spi_st = spi_master_get_devdata(master);

	ग_लिखोl_relaxed(0, spi_st->base + SSC_IEN);
	pinctrl_pm_select_sleep_state(dev);

	clk_disable_unprepare(spi_st->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_st_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा spi_st *spi_st = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(spi_st->clk);
	pinctrl_pm_select_शेष_state(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक spi_st_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक spi_st_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_resume(master);
	अगर (ret)
		वापस ret;

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops spi_st_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(spi_st_suspend, spi_st_resume)
	SET_RUNTIME_PM_OPS(spi_st_runसमय_suspend, spi_st_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग_spi_match[] = अणु
	अणु .compatible = "st,comms-ssc4-spi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग_spi_match);

अटल काष्ठा platक्रमm_driver spi_st_driver = अणु
	.driver = अणु
		.name = "spi-st",
		.pm = &spi_st_pm,
		.of_match_table = of_match_ptr(sपंचांग_spi_match),
	पूर्ण,
	.probe = spi_st_probe,
	.हटाओ = spi_st_हटाओ,
पूर्ण;
module_platक्रमm_driver(spi_st_driver);

MODULE_AUTHOR("Patrice Chotard <patrice.chotard@st.com>");
MODULE_DESCRIPTION("STM SSC SPI driver");
MODULE_LICENSE("GPL v2");
