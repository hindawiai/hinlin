<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>

काष्ठा rtspi अणु
	व्योम __iomem *base;
पूर्ण;

/* SPI Flash Configuration Register */
#घोषणा RTL_SPI_SFCR			0x00
#घोषणा RTL_SPI_SFCR_RBO		BIT(28)
#घोषणा RTL_SPI_SFCR_WBO		BIT(27)

/* SPI Flash Control and Status Register */
#घोषणा RTL_SPI_SFCSR			0x08
#घोषणा RTL_SPI_SFCSR_CSB0		BIT(31)
#घोषणा RTL_SPI_SFCSR_CSB1		BIT(30)
#घोषणा RTL_SPI_SFCSR_RDY		BIT(27)
#घोषणा RTL_SPI_SFCSR_CS		BIT(24)
#घोषणा RTL_SPI_SFCSR_LEN_MASK		~(0x03 << 28)
#घोषणा RTL_SPI_SFCSR_LEN1		(0x00 << 28)
#घोषणा RTL_SPI_SFCSR_LEN4		(0x03 << 28)

/* SPI Flash Data Register */
#घोषणा RTL_SPI_SFDR			0x0c

#घोषणा REG(x)		(rtspi->base + x)


अटल व्योम rt_set_cs(काष्ठा spi_device *spi, bool active)
अणु
	काष्ठा rtspi *rtspi = spi_controller_get_devdata(spi->controller);
	u32 value;

	/* CS0 bit is active low */
	value = पढ़ोl(REG(RTL_SPI_SFCSR));
	अगर (active)
		value |= RTL_SPI_SFCSR_CSB0;
	अन्यथा
		value &= ~RTL_SPI_SFCSR_CSB0;
	ग_लिखोl(value, REG(RTL_SPI_SFCSR));
पूर्ण

अटल व्योम set_size(काष्ठा rtspi *rtspi, पूर्णांक size)
अणु
	u32 value;

	value = पढ़ोl(REG(RTL_SPI_SFCSR));
	value &= RTL_SPI_SFCSR_LEN_MASK;
	अगर (size == 4)
		value |= RTL_SPI_SFCSR_LEN4;
	अन्यथा अगर (size == 1)
		value |= RTL_SPI_SFCSR_LEN1;
	ग_लिखोl(value, REG(RTL_SPI_SFCSR));
पूर्ण

अटल अंतरभूत व्योम रुको_पढ़ोy(काष्ठा rtspi *rtspi)
अणु
	जबतक (!(पढ़ोl(REG(RTL_SPI_SFCSR)) & RTL_SPI_SFCSR_RDY))
		cpu_relax();
पूर्ण
अटल व्योम send4(काष्ठा rtspi *rtspi, स्थिर u32 *buf)
अणु
	रुको_पढ़ोy(rtspi);
	set_size(rtspi, 4);
	ग_लिखोl(*buf, REG(RTL_SPI_SFDR));
पूर्ण

अटल व्योम send1(काष्ठा rtspi *rtspi, स्थिर u8 *buf)
अणु
	रुको_पढ़ोy(rtspi);
	set_size(rtspi, 1);
	ग_लिखोl(buf[0] << 24, REG(RTL_SPI_SFDR));
पूर्ण

अटल व्योम rcv4(काष्ठा rtspi *rtspi, u32 *buf)
अणु
	रुको_पढ़ोy(rtspi);
	set_size(rtspi, 4);
	*buf = पढ़ोl(REG(RTL_SPI_SFDR));
पूर्ण

अटल व्योम rcv1(काष्ठा rtspi *rtspi, u8 *buf)
अणु
	रुको_पढ़ोy(rtspi);
	set_size(rtspi, 1);
	*buf = पढ़ोl(REG(RTL_SPI_SFDR)) >> 24;
पूर्ण

अटल पूर्णांक transfer_one(काष्ठा spi_controller *ctrl, काष्ठा spi_device *spi,
			काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rtspi *rtspi = spi_controller_get_devdata(ctrl);
	व्योम *rx_buf;
	स्थिर व्योम *tx_buf;
	पूर्णांक cnt;

	tx_buf = xfer->tx_buf;
	rx_buf = xfer->rx_buf;
	cnt = xfer->len;
	अगर (tx_buf) अणु
		जबतक (cnt >= 4) अणु
			send4(rtspi, tx_buf);
			tx_buf += 4;
			cnt -= 4;
		पूर्ण
		जबतक (cnt) अणु
			send1(rtspi, tx_buf);
			tx_buf++;
			cnt--;
		पूर्ण
	पूर्ण अन्यथा अगर (rx_buf) अणु
		जबतक (cnt >= 4) अणु
			rcv4(rtspi, rx_buf);
			rx_buf += 4;
			cnt -= 4;
		पूर्ण
		जबतक (cnt) अणु
			rcv1(rtspi, rx_buf);
			rx_buf++;
			cnt--;
		पूर्ण
	पूर्ण

	spi_finalize_current_transfer(ctrl);

	वापस 0;
पूर्ण

अटल व्योम init_hw(काष्ठा rtspi *rtspi)
अणु
	u32 value;

	/* Turn on big-endian byte ordering */
	value = पढ़ोl(REG(RTL_SPI_SFCR));
	value |= RTL_SPI_SFCR_RBO | RTL_SPI_SFCR_WBO;
	ग_लिखोl(value, REG(RTL_SPI_SFCR));

	value = पढ़ोl(REG(RTL_SPI_SFCSR));
	/* Permanently disable CS1, since it's never used */
	value |= RTL_SPI_SFCSR_CSB1;
	/* Select CS0 क्रम use */
	value &= RTL_SPI_SFCSR_CS;
	ग_लिखोl(value, REG(RTL_SPI_SFCSR));
पूर्ण

अटल पूर्णांक realtek_rtl_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctrl;
	काष्ठा rtspi *rtspi;
	पूर्णांक err;

	ctrl = devm_spi_alloc_master(&pdev->dev, माप(*rtspi));
	अगर (!ctrl) अणु
		dev_err(&pdev->dev, "Error allocating SPI controller\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, ctrl);
	rtspi = spi_controller_get_devdata(ctrl);

	rtspi->base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, शून्य);
	अगर (IS_ERR(rtspi->base)) अणु
		dev_err(&pdev->dev, "Could not map SPI register address");
		वापस -ENOMEM;
	पूर्ण

	init_hw(rtspi);

	ctrl->dev.of_node = pdev->dev.of_node;
	ctrl->flags = SPI_CONTROLLER_HALF_DUPLEX;
	ctrl->set_cs = rt_set_cs;
	ctrl->transfer_one = transfer_one;

	err = devm_spi_रेजिस्टर_controller(&pdev->dev, ctrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "Could not register SPI controller\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id realtek_rtl_spi_of_ids[] = अणु
	अणु .compatible = "realtek,rtl8380-spi" पूर्ण,
	अणु .compatible = "realtek,rtl8382-spi" पूर्ण,
	अणु .compatible = "realtek,rtl8391-spi" पूर्ण,
	अणु .compatible = "realtek,rtl8392-spi" पूर्ण,
	अणु .compatible = "realtek,rtl8393-spi" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, realtek_rtl_spi_of_ids);

अटल काष्ठा platक्रमm_driver realtek_rtl_spi_driver = अणु
	.probe = realtek_rtl_spi_probe,
	.driver = अणु
		.name = "realtek-rtl-spi",
		.of_match_table = realtek_rtl_spi_of_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(realtek_rtl_spi_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Bert Vermeulen <bert@biot.com>");
MODULE_DESCRIPTION("Realtek RTL SPI driver");
