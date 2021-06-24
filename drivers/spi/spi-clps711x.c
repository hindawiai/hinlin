<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  CLPS711X SPI bus driver
 *
 *  Copyright (C) 2012-2016 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/clps711x.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRIVER_NAME		"clps711x-spi"

#घोषणा SYNCIO_FRMLEN(x)	((x) << 8)
#घोषणा SYNCIO_TXFRMEN		(1 << 14)

काष्ठा spi_clps711x_data अणु
	व्योम __iomem		*syncio;
	काष्ठा regmap		*syscon;
	काष्ठा clk		*spi_clk;

	u8			*tx_buf;
	u8			*rx_buf;
	अचिन्हित पूर्णांक		bpw;
	पूर्णांक			len;
पूर्ण;

अटल पूर्णांक spi_clps711x_prepare_message(काष्ठा spi_master *master,
					काष्ठा spi_message *msg)
अणु
	काष्ठा spi_clps711x_data *hw = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = msg->spi;

	/* Setup mode क्रम transfer */
	वापस regmap_update_bits(hw->syscon, SYSCON_OFFSET, SYSCON3_ADCCKNSEN,
				  (spi->mode & SPI_CPHA) ?
				  SYSCON3_ADCCKNSEN : 0);
पूर्ण

अटल पूर्णांक spi_clps711x_transfer_one(काष्ठा spi_master *master,
				     काष्ठा spi_device *spi,
				     काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_clps711x_data *hw = spi_master_get_devdata(master);
	u8 data;

	clk_set_rate(hw->spi_clk, xfer->speed_hz ? : spi->max_speed_hz);

	hw->len = xfer->len;
	hw->bpw = xfer->bits_per_word;
	hw->tx_buf = (u8 *)xfer->tx_buf;
	hw->rx_buf = (u8 *)xfer->rx_buf;

	/* Initiate transfer */
	data = hw->tx_buf ? *hw->tx_buf++ : 0;
	ग_लिखोl(data | SYNCIO_FRMLEN(hw->bpw) | SYNCIO_TXFRMEN, hw->syncio);

	वापस 1;
पूर्ण

अटल irqवापस_t spi_clps711x_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा spi_clps711x_data *hw = spi_master_get_devdata(master);
	u8 data;

	/* Handle RX */
	data = पढ़ोb(hw->syncio);
	अगर (hw->rx_buf)
		*hw->rx_buf++ = data;

	/* Handle TX */
	अगर (--hw->len > 0) अणु
		data = hw->tx_buf ? *hw->tx_buf++ : 0;
		ग_लिखोl(data | SYNCIO_FRMLEN(hw->bpw) | SYNCIO_TXFRMEN,
		       hw->syncio);
	पूर्ण अन्यथा
		spi_finalize_current_transfer(master);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spi_clps711x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_clps711x_data *hw;
	काष्ठा spi_master *master;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	master = spi_alloc_master(&pdev->dev, माप(*hw));
	अगर (!master)
		वापस -ENOMEM;

	master->use_gpio_descriptors = true;
	master->bus_num = -1;
	master->mode_bits = SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 8);
	master->dev.of_node = pdev->dev.of_node;
	master->prepare_message = spi_clps711x_prepare_message;
	master->transfer_one = spi_clps711x_transfer_one;

	hw = spi_master_get_devdata(master);

	hw->spi_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(hw->spi_clk)) अणु
		ret = PTR_ERR(hw->spi_clk);
		जाओ err_out;
	पूर्ण

	hw->syscon =
		syscon_regmap_lookup_by_compatible("cirrus,ep7209-syscon3");
	अगर (IS_ERR(hw->syscon)) अणु
		ret = PTR_ERR(hw->syscon);
		जाओ err_out;
	पूर्ण

	hw->syncio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hw->syncio)) अणु
		ret = PTR_ERR(hw->syncio);
		जाओ err_out;
	पूर्ण

	/* Disable extended mode due hardware problems */
	regmap_update_bits(hw->syscon, SYSCON_OFFSET, SYSCON3_ADCCON, 0);

	/* Clear possible pending पूर्णांकerrupt */
	पढ़ोl(hw->syncio);

	ret = devm_request_irq(&pdev->dev, irq, spi_clps711x_isr, 0,
			       dev_name(&pdev->dev), master);
	अगर (ret)
		जाओ err_out;

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (!ret)
		वापस 0;

err_out:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id clps711x_spi_dt_ids[] = अणु
	अणु .compatible = "cirrus,ep7209-spi", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clps711x_spi_dt_ids);

अटल काष्ठा platक्रमm_driver clps711x_spi_driver = अणु
	.driver	= अणु
		.name	= DRIVER_NAME,
		.of_match_table = clps711x_spi_dt_ids,
	पूर्ण,
	.probe	= spi_clps711x_probe,
पूर्ण;
module_platक्रमm_driver(clps711x_spi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("CLPS711X SPI bus driver");
MODULE_ALIAS("platform:" DRIVER_NAME);
