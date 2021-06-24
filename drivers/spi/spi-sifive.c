<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2018 SiFive, Inc.
//
// SiFive SPI controller driver (master mode only)
//
// Author: SiFive, Inc.
// sअगरive@sअगरive.com

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>

#घोषणा SIFIVE_SPI_DRIVER_NAME           "sifive_spi"

#घोषणा SIFIVE_SPI_MAX_CS                32
#घोषणा SIFIVE_SPI_DEFAULT_DEPTH         8
#घोषणा SIFIVE_SPI_DEFAULT_MAX_BITS      8

/* रेजिस्टर offsets */
#घोषणा SIFIVE_SPI_REG_SCKDIV            0x00 /* Serial घड़ी भागisor */
#घोषणा SIFIVE_SPI_REG_SCKMODE           0x04 /* Serial घड़ी mode */
#घोषणा SIFIVE_SPI_REG_CSID              0x10 /* Chip select ID */
#घोषणा SIFIVE_SPI_REG_CSDEF             0x14 /* Chip select शेष */
#घोषणा SIFIVE_SPI_REG_CSMODE            0x18 /* Chip select mode */
#घोषणा SIFIVE_SPI_REG_DELAY0            0x28 /* Delay control 0 */
#घोषणा SIFIVE_SPI_REG_DELAY1            0x2c /* Delay control 1 */
#घोषणा SIFIVE_SPI_REG_FMT               0x40 /* Frame क्रमmat */
#घोषणा SIFIVE_SPI_REG_TXDATA            0x48 /* Tx FIFO data */
#घोषणा SIFIVE_SPI_REG_RXDATA            0x4c /* Rx FIFO data */
#घोषणा SIFIVE_SPI_REG_TXMARK            0x50 /* Tx FIFO watermark */
#घोषणा SIFIVE_SPI_REG_RXMARK            0x54 /* Rx FIFO watermark */
#घोषणा SIFIVE_SPI_REG_FCTRL             0x60 /* SPI flash पूर्णांकerface control */
#घोषणा SIFIVE_SPI_REG_FFMT              0x64 /* SPI flash inकाष्ठाion क्रमmat */
#घोषणा SIFIVE_SPI_REG_IE                0x70 /* Interrupt Enable Register */
#घोषणा SIFIVE_SPI_REG_IP                0x74 /* Interrupt Pendings Register */

/* sckभाग bits */
#घोषणा SIFIVE_SPI_SCKDIV_DIV_MASK       0xfffU

/* sckmode bits */
#घोषणा SIFIVE_SPI_SCKMODE_PHA           BIT(0)
#घोषणा SIFIVE_SPI_SCKMODE_POL           BIT(1)
#घोषणा SIFIVE_SPI_SCKMODE_MODE_MASK     (SIFIVE_SPI_SCKMODE_PHA | \
					  SIFIVE_SPI_SCKMODE_POL)

/* csmode bits */
#घोषणा SIFIVE_SPI_CSMODE_MODE_AUTO      0U
#घोषणा SIFIVE_SPI_CSMODE_MODE_HOLD      2U
#घोषणा SIFIVE_SPI_CSMODE_MODE_OFF       3U

/* delay0 bits */
#घोषणा SIFIVE_SPI_DELAY0_CSSCK(x)       ((u32)(x))
#घोषणा SIFIVE_SPI_DELAY0_CSSCK_MASK     0xffU
#घोषणा SIFIVE_SPI_DELAY0_SCKCS(x)       ((u32)(x) << 16)
#घोषणा SIFIVE_SPI_DELAY0_SCKCS_MASK     (0xffU << 16)

/* delay1 bits */
#घोषणा SIFIVE_SPI_DELAY1_INTERCS(x)     ((u32)(x))
#घोषणा SIFIVE_SPI_DELAY1_INTERCS_MASK   0xffU
#घोषणा SIFIVE_SPI_DELAY1_INTERXFR(x)    ((u32)(x) << 16)
#घोषणा SIFIVE_SPI_DELAY1_INTERXFR_MASK  (0xffU << 16)

/* fmt bits */
#घोषणा SIFIVE_SPI_FMT_PROTO_SINGLE      0U
#घोषणा SIFIVE_SPI_FMT_PROTO_DUAL        1U
#घोषणा SIFIVE_SPI_FMT_PROTO_QUAD        2U
#घोषणा SIFIVE_SPI_FMT_PROTO_MASK        3U
#घोषणा SIFIVE_SPI_FMT_ENDIAN            BIT(2)
#घोषणा SIFIVE_SPI_FMT_सूची               BIT(3)
#घोषणा SIFIVE_SPI_FMT_LEN(x)            ((u32)(x) << 16)
#घोषणा SIFIVE_SPI_FMT_LEN_MASK          (0xfU << 16)

/* txdata bits */
#घोषणा SIFIVE_SPI_TXDATA_DATA_MASK      0xffU
#घोषणा SIFIVE_SPI_TXDATA_FULL           BIT(31)

/* rxdata bits */
#घोषणा SIFIVE_SPI_RXDATA_DATA_MASK      0xffU
#घोषणा SIFIVE_SPI_RXDATA_EMPTY          BIT(31)

/* ie and ip bits */
#घोषणा SIFIVE_SPI_IP_TXWM               BIT(0)
#घोषणा SIFIVE_SPI_IP_RXWM               BIT(1)

काष्ठा sअगरive_spi अणु
	व्योम __iomem      *regs;        /* virt. address of control रेजिस्टरs */
	काष्ठा clk        *clk;         /* bus घड़ी */
	अचिन्हित पूर्णांक      fअगरo_depth;   /* fअगरo depth in words */
	u32               cs_inactive;  /* level of the CS pins when inactive */
	काष्ठा completion करोne;         /* wake-up from पूर्णांकerrupt */
पूर्ण;

अटल व्योम sअगरive_spi_ग_लिखो(काष्ठा sअगरive_spi *spi, पूर्णांक offset, u32 value)
अणु
	ioग_लिखो32(value, spi->regs + offset);
पूर्ण

अटल u32 sअगरive_spi_पढ़ो(काष्ठा sअगरive_spi *spi, पूर्णांक offset)
अणु
	वापस ioपढ़ो32(spi->regs + offset);
पूर्ण

अटल व्योम sअगरive_spi_init(काष्ठा sअगरive_spi *spi)
अणु
	/* Watermark पूर्णांकerrupts are disabled by शेष */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_IE, 0);

	/* Default watermark FIFO threshold values */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_TXMARK, 1);
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_RXMARK, 0);

	/* Set CS/SCK Delays and Inactive Time to शेषs */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_DELAY0,
			 SIFIVE_SPI_DELAY0_CSSCK(1) |
			 SIFIVE_SPI_DELAY0_SCKCS(1));
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_DELAY1,
			 SIFIVE_SPI_DELAY1_INTERCS(1) |
			 SIFIVE_SPI_DELAY1_INTERXFR(0));

	/* Exit specialized memory-mapped SPI flash mode */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_FCTRL, 0);
पूर्ण

अटल पूर्णांक
sअगरive_spi_prepare_message(काष्ठा spi_master *master, काष्ठा spi_message *msg)
अणु
	काष्ठा sअगरive_spi *spi = spi_master_get_devdata(master);
	काष्ठा spi_device *device = msg->spi;

	/* Update the chip select polarity */
	अगर (device->mode & SPI_CS_HIGH)
		spi->cs_inactive &= ~BIT(device->chip_select);
	अन्यथा
		spi->cs_inactive |= BIT(device->chip_select);
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_CSDEF, spi->cs_inactive);

	/* Select the correct device */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_CSID, device->chip_select);

	/* Set घड़ी mode */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_SCKMODE,
			 device->mode & SIFIVE_SPI_SCKMODE_MODE_MASK);

	वापस 0;
पूर्ण

अटल व्योम sअगरive_spi_set_cs(काष्ठा spi_device *device, bool is_high)
अणु
	काष्ठा sअगरive_spi *spi = spi_master_get_devdata(device->master);

	/* Reverse polarity is handled by SCMR/CPOL. Not inverted CS. */
	अगर (device->mode & SPI_CS_HIGH)
		is_high = !is_high;

	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_CSMODE, is_high ?
			 SIFIVE_SPI_CSMODE_MODE_AUTO :
			 SIFIVE_SPI_CSMODE_MODE_HOLD);
पूर्ण

अटल पूर्णांक
sअगरive_spi_prep_transfer(काष्ठा sअगरive_spi *spi, काष्ठा spi_device *device,
			 काष्ठा spi_transfer *t)
अणु
	u32 cr;
	अचिन्हित पूर्णांक mode;

	/* Calculate and program the घड़ी rate */
	cr = DIV_ROUND_UP(clk_get_rate(spi->clk) >> 1, t->speed_hz) - 1;
	cr &= SIFIVE_SPI_SCKDIV_DIV_MASK;
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_SCKDIV, cr);

	mode = max_t(अचिन्हित पूर्णांक, t->rx_nbits, t->tx_nbits);

	/* Set frame क्रमmat */
	cr = SIFIVE_SPI_FMT_LEN(t->bits_per_word);
	चयन (mode) अणु
	हाल SPI_NBITS_QUAD:
		cr |= SIFIVE_SPI_FMT_PROTO_QUAD;
		अवरोध;
	हाल SPI_NBITS_DUAL:
		cr |= SIFIVE_SPI_FMT_PROTO_DUAL;
		अवरोध;
	शेष:
		cr |= SIFIVE_SPI_FMT_PROTO_SINGLE;
		अवरोध;
	पूर्ण
	अगर (device->mode & SPI_LSB_FIRST)
		cr |= SIFIVE_SPI_FMT_ENDIAN;
	अगर (!t->rx_buf)
		cr |= SIFIVE_SPI_FMT_सूची;
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_FMT, cr);

	/* We will want to poll अगर the समय we need to रुको is
	 * less than the context चयनing समय.
	 * Let's call that threshold 5us. The operation will take:
	 *    (8/mode) * fअगरo_depth / hz <= 5 * 10^-6
	 *    1600000 * fअगरo_depth <= hz * mode
	 */
	वापस 1600000 * spi->fअगरo_depth <= t->speed_hz * mode;
पूर्ण

अटल irqवापस_t sअगरive_spi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sअगरive_spi *spi = dev_id;
	u32 ip = sअगरive_spi_पढ़ो(spi, SIFIVE_SPI_REG_IP);

	अगर (ip & (SIFIVE_SPI_IP_TXWM | SIFIVE_SPI_IP_RXWM)) अणु
		/* Disable पूर्णांकerrupts until next transfer */
		sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_IE, 0);
		complete(&spi->करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम sअगरive_spi_रुको(काष्ठा sअगरive_spi *spi, u32 bit, पूर्णांक poll)
अणु
	अगर (poll) अणु
		u32 cr;

		करो अणु
			cr = sअगरive_spi_पढ़ो(spi, SIFIVE_SPI_REG_IP);
		पूर्ण जबतक (!(cr & bit));
	पूर्ण अन्यथा अणु
		reinit_completion(&spi->करोne);
		sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_IE, bit);
		रुको_क्रम_completion(&spi->करोne);
	पूर्ण
पूर्ण

अटल व्योम sअगरive_spi_tx(काष्ठा sअगरive_spi *spi, स्थिर u8 *tx_ptr)
अणु
	WARN_ON_ONCE((sअगरive_spi_पढ़ो(spi, SIFIVE_SPI_REG_TXDATA)
				& SIFIVE_SPI_TXDATA_FULL) != 0);
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_TXDATA,
			 *tx_ptr & SIFIVE_SPI_TXDATA_DATA_MASK);
पूर्ण

अटल व्योम sअगरive_spi_rx(काष्ठा sअगरive_spi *spi, u8 *rx_ptr)
अणु
	u32 data = sअगरive_spi_पढ़ो(spi, SIFIVE_SPI_REG_RXDATA);

	WARN_ON_ONCE((data & SIFIVE_SPI_RXDATA_EMPTY) != 0);
	*rx_ptr = data & SIFIVE_SPI_RXDATA_DATA_MASK;
पूर्ण

अटल पूर्णांक
sअगरive_spi_transfer_one(काष्ठा spi_master *master, काष्ठा spi_device *device,
			काष्ठा spi_transfer *t)
अणु
	काष्ठा sअगरive_spi *spi = spi_master_get_devdata(master);
	पूर्णांक poll = sअगरive_spi_prep_transfer(spi, device, t);
	स्थिर u8 *tx_ptr = t->tx_buf;
	u8 *rx_ptr = t->rx_buf;
	अचिन्हित पूर्णांक reमुख्यing_words = t->len;

	जबतक (reमुख्यing_words) अणु
		अचिन्हित पूर्णांक n_words = min(reमुख्यing_words, spi->fअगरo_depth);
		अचिन्हित पूर्णांक i;

		/* Enqueue n_words क्रम transmission */
		क्रम (i = 0; i < n_words; i++)
			sअगरive_spi_tx(spi, tx_ptr++);

		अगर (rx_ptr) अणु
			/* Wait क्रम transmission + reception to complete */
			sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_RXMARK,
					 n_words - 1);
			sअगरive_spi_रुको(spi, SIFIVE_SPI_IP_RXWM, poll);

			/* Read out all the data from the RX FIFO */
			क्रम (i = 0; i < n_words; i++)
				sअगरive_spi_rx(spi, rx_ptr++);
		पूर्ण अन्यथा अणु
			/* Wait क्रम transmission to complete */
			sअगरive_spi_रुको(spi, SIFIVE_SPI_IP_TXWM, poll);
		पूर्ण

		reमुख्यing_words -= n_words;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sअगरive_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sअगरive_spi *spi;
	पूर्णांक ret, irq, num_cs;
	u32 cs_bits, max_bits_per_word;
	काष्ठा spi_master *master;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा sअगरive_spi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	spi = spi_master_get_devdata(master);
	init_completion(&spi->करोne);
	platक्रमm_set_drvdata(pdev, master);

	spi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spi->regs)) अणु
		ret = PTR_ERR(spi->regs);
		जाओ put_master;
	पूर्ण

	spi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(spi->clk)) अणु
		dev_err(&pdev->dev, "Unable to find bus clock\n");
		ret = PTR_ERR(spi->clk);
		जाओ put_master;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ put_master;
	पूर्ण

	/* Optional parameters */
	ret =
	  of_property_पढ़ो_u32(pdev->dev.of_node, "sifive,fifo-depth",
			       &spi->fअगरo_depth);
	अगर (ret < 0)
		spi->fअगरo_depth = SIFIVE_SPI_DEFAULT_DEPTH;

	ret =
	  of_property_पढ़ो_u32(pdev->dev.of_node, "sifive,max-bits-per-word",
			       &max_bits_per_word);

	अगर (!ret && max_bits_per_word < 8) अणु
		dev_err(&pdev->dev, "Only 8bit SPI words supported by the driver\n");
		ret = -EINVAL;
		जाओ put_master;
	पूर्ण

	/* Spin up the bus घड़ी beक्रमe hitting रेजिस्टरs */
	ret = clk_prepare_enable(spi->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable bus clock\n");
		जाओ put_master;
	पूर्ण

	/* probe the number of CS lines */
	spi->cs_inactive = sअगरive_spi_पढ़ो(spi, SIFIVE_SPI_REG_CSDEF);
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_CSDEF, 0xffffffffU);
	cs_bits = sअगरive_spi_पढ़ो(spi, SIFIVE_SPI_REG_CSDEF);
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_CSDEF, spi->cs_inactive);
	अगर (!cs_bits) अणु
		dev_err(&pdev->dev, "Could not auto probe CS lines\n");
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	num_cs = ilog2(cs_bits) + 1;
	अगर (num_cs > SIFIVE_SPI_MAX_CS) अणु
		dev_err(&pdev->dev, "Invalid number of spi slaves\n");
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	/* Define our master */
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->num_chipselect = num_cs;
	master->mode_bits = SPI_CPHA | SPI_CPOL
			  | SPI_CS_HIGH | SPI_LSB_FIRST
			  | SPI_TX_DUAL | SPI_TX_QUAD
			  | SPI_RX_DUAL | SPI_RX_QUAD;
	/* TODO: add driver support क्रम bits_per_word < 8
	 * we need to "left-align" the bits (unless SPI_LSB_FIRST)
	 */
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->flags = SPI_CONTROLLER_MUST_TX | SPI_MASTER_GPIO_SS;
	master->prepare_message = sअगरive_spi_prepare_message;
	master->set_cs = sअगरive_spi_set_cs;
	master->transfer_one = sअगरive_spi_transfer_one;

	pdev->dev.dma_mask = शून्य;
	/* Configure the SPI master hardware */
	sअगरive_spi_init(spi);

	/* Register क्रम SPI Interrupt */
	ret = devm_request_irq(&pdev->dev, irq, sअगरive_spi_irq, 0,
			       dev_name(&pdev->dev), spi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to bind to interrupt\n");
		जाओ disable_clk;
	पूर्ण

	dev_info(&pdev->dev, "mapped; irq=%d, cs=%d\n",
		 irq, master->num_chipselect);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "spi_register_master failed\n");
		जाओ disable_clk;
	पूर्ण

	वापस 0;

disable_clk:
	clk_disable_unprepare(spi->clk);
put_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक sअगरive_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा sअगरive_spi *spi = spi_master_get_devdata(master);

	/* Disable all the पूर्णांकerrupts just in हाल */
	sअगरive_spi_ग_लिखो(spi, SIFIVE_SPI_REG_IE, 0);
	clk_disable_unprepare(spi->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sअगरive_spi_of_match[] = अणु
	अणु .compatible = "sifive,spi0", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sअगरive_spi_of_match);

अटल काष्ठा platक्रमm_driver sअगरive_spi_driver = अणु
	.probe = sअगरive_spi_probe,
	.हटाओ = sअगरive_spi_हटाओ,
	.driver = अणु
		.name = SIFIVE_SPI_DRIVER_NAME,
		.of_match_table = sअगरive_spi_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sअगरive_spi_driver);

MODULE_AUTHOR("SiFive, Inc. <sifive@sifive.com>");
MODULE_DESCRIPTION("SiFive SPI driver");
MODULE_LICENSE("GPL");
