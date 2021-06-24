<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPI master driver क्रम ICP DAS LP-8841 RTC
 *
 * Copyright (C) 2016 Sergei Ianovich
 *
 * based on
 *
 * Dallas DS1302 RTC Support
 * Copyright (C) 2002 David McCullough
 * Copyright (C) 2003 - 2007 Paul Mundt
 */
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRIVER_NAME	"spi_lp8841_rtc"

#घोषणा SPI_LP8841_RTC_CE	0x01
#घोषणा SPI_LP8841_RTC_CLK	0x02
#घोषणा SPI_LP8841_RTC_nWE	0x04
#घोषणा SPI_LP8841_RTC_MOSI	0x08
#घोषणा SPI_LP8841_RTC_MISO	0x01

/*
 * REVISIT If there is support क्रम SPI_3WIRE and SPI_LSB_FIRST in SPI
 * GPIO driver, this SPI driver can be replaced by a simple GPIO driver
 * providing 3 GPIO pins.
 */

काष्ठा spi_lp8841_rtc अणु
	व्योम		*iomem;
	अचिन्हित दीर्घ	state;
पूर्ण;

अटल अंतरभूत व्योम
setsck(काष्ठा spi_lp8841_rtc *data, पूर्णांक is_on)
अणु
	अगर (is_on)
		data->state |= SPI_LP8841_RTC_CLK;
	अन्यथा
		data->state &= ~SPI_LP8841_RTC_CLK;
	ग_लिखोb(data->state, data->iomem);
पूर्ण

अटल अंतरभूत व्योम
seपंचांगosi(काष्ठा spi_lp8841_rtc *data, पूर्णांक is_on)
अणु
	अगर (is_on)
		data->state |= SPI_LP8841_RTC_MOSI;
	अन्यथा
		data->state &= ~SPI_LP8841_RTC_MOSI;
	ग_लिखोb(data->state, data->iomem);
पूर्ण

अटल अंतरभूत पूर्णांक
geपंचांगiso(काष्ठा spi_lp8841_rtc *data)
अणु
	वापस ioपढ़ो8(data->iomem) & SPI_LP8841_RTC_MISO;
पूर्ण

अटल अंतरभूत u32
bitbang_txrx_be_cpha0_lsb(काष्ठा spi_lp8841_rtc *data,
		अचिन्हित usecs, अचिन्हित cpol, अचिन्हित flags,
		u32 word, u8 bits)
अणु
	/* अगर (cpol == 0) this is SPI_MODE_0; अन्यथा this is SPI_MODE_2 */

	u32 shअगरt = 32 - bits;
	/* घड़ी starts at inactive polarity */
	क्रम (; likely(bits); bits--) अणु

		/* setup LSB (to slave) on leading edge */
		अगर ((flags & SPI_MASTER_NO_TX) == 0)
			seपंचांगosi(data, (word & 1));

		usleep_range(usecs, usecs + 1);	/* T(setup) */

		/* sample LSB (from slave) on trailing edge */
		word >>= 1;
		अगर ((flags & SPI_MASTER_NO_RX) == 0)
			word |= (geपंचांगiso(data) << 31);

		setsck(data, !cpol);
		usleep_range(usecs, usecs + 1);

		setsck(data, cpol);
	पूर्ण

	word >>= shअगरt;
	वापस word;
पूर्ण

अटल पूर्णांक
spi_lp8841_rtc_transfer_one(काष्ठा spi_master *master,
			    काष्ठा spi_device *spi,
			    काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_lp8841_rtc	*data = spi_master_get_devdata(master);
	अचिन्हित		count = t->len;
	स्थिर u8		*tx = t->tx_buf;
	u8			*rx = t->rx_buf;
	u8			word = 0;
	पूर्णांक			ret = 0;

	अगर (tx) अणु
		data->state &= ~SPI_LP8841_RTC_nWE;
		ग_लिखोb(data->state, data->iomem);
		जबतक (likely(count > 0)) अणु
			word = *tx++;
			bitbang_txrx_be_cpha0_lsb(data, 1, 0,
					SPI_MASTER_NO_RX, word, 8);
			count--;
		पूर्ण
	पूर्ण अन्यथा अगर (rx) अणु
		data->state |= SPI_LP8841_RTC_nWE;
		ग_लिखोb(data->state, data->iomem);
		जबतक (likely(count > 0)) अणु
			word = bitbang_txrx_be_cpha0_lsb(data, 1, 0,
					SPI_MASTER_NO_TX, word, 8);
			*rx++ = word;
			count--;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	spi_finalize_current_transfer(master);

	वापस ret;
पूर्ण

अटल व्योम
spi_lp8841_rtc_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा spi_lp8841_rtc *data = spi_master_get_devdata(spi->master);

	data->state = 0;
	ग_लिखोb(data->state, data->iomem);
	अगर (enable) अणु
		usleep_range(4, 5);
		data->state |= SPI_LP8841_RTC_CE;
		ग_लिखोb(data->state, data->iomem);
		usleep_range(4, 5);
	पूर्ण
पूर्ण

अटल पूर्णांक
spi_lp8841_rtc_setup(काष्ठा spi_device *spi)
अणु
	अगर ((spi->mode & SPI_CS_HIGH) == 0) अणु
		dev_err(&spi->dev, "unsupported active low chip select\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((spi->mode & SPI_LSB_FIRST) == 0) अणु
		dev_err(&spi->dev, "unsupported MSB first mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((spi->mode & SPI_3WIRE) == 0) अणु
		dev_err(&spi->dev, "unsupported wiring. 3 wires required\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spi_lp8841_rtc_dt_ids[] = अणु
	अणु .compatible = "icpdas,lp8841-spi-rtc" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, spi_lp8841_rtc_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक
spi_lp8841_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक				ret;
	काष्ठा spi_master		*master;
	काष्ठा spi_lp8841_rtc		*data;

	master = spi_alloc_master(&pdev->dev, माप(*data));
	अगर (!master)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, master);

	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->mode_bits = SPI_CS_HIGH | SPI_3WIRE | SPI_LSB_FIRST;

	master->bus_num = pdev->id;
	master->num_chipselect = 1;
	master->setup = spi_lp8841_rtc_setup;
	master->set_cs = spi_lp8841_rtc_set_cs;
	master->transfer_one = spi_lp8841_rtc_transfer_one;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
#अगर_घोषित CONFIG_OF
	master->dev.of_node = pdev->dev.of_node;
#पूर्ण_अगर

	data = spi_master_get_devdata(master);

	data->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	ret = PTR_ERR_OR_ZERO(data->iomem);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get IO address\n");
		जाओ err_put_master;
	पूर्ण

	/* रेजिस्टर with the SPI framework */
	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot register spi master\n");
		जाओ err_put_master;
	पूर्ण

	वापस ret;


err_put_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

MODULE_ALIAS("platform:" DRIVER_NAME);

अटल काष्ठा platक्रमm_driver spi_lp8841_rtc_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(spi_lp8841_rtc_dt_ids),
	पूर्ण,
	.probe		= spi_lp8841_rtc_probe,
पूर्ण;
module_platक्रमm_driver(spi_lp8841_rtc_driver);

MODULE_DESCRIPTION("SPI master driver for ICP DAS LP-8841 RTC");
MODULE_AUTHOR("Sergei Ianovich");
MODULE_LICENSE("GPL");
