<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Nuvoton Technology corporation.

#समावेश <linux/kernel.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/reset.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

काष्ठा npcm_pspi अणु
	काष्ठा completion xfer_करोne;
	काष्ठा reset_control *reset;
	काष्ठा spi_master *master;
	अचिन्हित पूर्णांक tx_bytes;
	अचिन्हित पूर्णांक rx_bytes;
	व्योम __iomem *base;
	bool is_save_param;
	u8 bits_per_word;
	स्थिर u8 *tx_buf;
	काष्ठा clk *clk;
	u32 speed_hz;
	u8 *rx_buf;
	u16 mode;
	u32 id;
पूर्ण;

#घोषणा DRIVER_NAME "npcm-pspi"

#घोषणा NPCM_PSPI_DATA		0x00
#घोषणा NPCM_PSPI_CTL1		0x02
#घोषणा NPCM_PSPI_STAT		0x04

/* definitions क्रम control and status रेजिस्टर */
#घोषणा NPCM_PSPI_CTL1_SPIEN	BIT(0)
#घोषणा NPCM_PSPI_CTL1_MOD	BIT(2)
#घोषणा NPCM_PSPI_CTL1_EIR	BIT(5)
#घोषणा NPCM_PSPI_CTL1_EIW	BIT(6)
#घोषणा NPCM_PSPI_CTL1_SCM	BIT(7)
#घोषणा NPCM_PSPI_CTL1_SCIDL	BIT(8)
#घोषणा NPCM_PSPI_CTL1_SCDV6_0	GENMASK(15, 9)

#घोषणा NPCM_PSPI_STAT_BSY	BIT(0)
#घोषणा NPCM_PSPI_STAT_RBF	BIT(1)

/* general definitions */
#घोषणा NPCM_PSPI_TIMEOUT_MS		2000
#घोषणा NPCM_PSPI_MAX_CLK_DIVIDER	256
#घोषणा NPCM_PSPI_MIN_CLK_DIVIDER	4
#घोषणा NPCM_PSPI_DEFAULT_CLK		25000000

अटल अंतरभूत अचिन्हित पूर्णांक bytes_per_word(अचिन्हित पूर्णांक bits)
अणु
	वापस bits <= 8 ? 1 : 2;
पूर्ण

अटल अंतरभूत व्योम npcm_pspi_irq_enable(काष्ठा npcm_pspi *priv, u16 mask)
अणु
	u16 val;

	val = ioपढ़ो16(priv->base + NPCM_PSPI_CTL1);
	val |= mask;
	ioग_लिखो16(val, priv->base + NPCM_PSPI_CTL1);
पूर्ण

अटल अंतरभूत व्योम npcm_pspi_irq_disable(काष्ठा npcm_pspi *priv, u16 mask)
अणु
	u16 val;

	val = ioपढ़ो16(priv->base + NPCM_PSPI_CTL1);
	val &= ~mask;
	ioग_लिखो16(val, priv->base + NPCM_PSPI_CTL1);
पूर्ण

अटल अंतरभूत व्योम npcm_pspi_enable(काष्ठा npcm_pspi *priv)
अणु
	u16 val;

	val = ioपढ़ो16(priv->base + NPCM_PSPI_CTL1);
	val |= NPCM_PSPI_CTL1_SPIEN;
	ioग_लिखो16(val, priv->base + NPCM_PSPI_CTL1);
पूर्ण

अटल अंतरभूत व्योम npcm_pspi_disable(काष्ठा npcm_pspi *priv)
अणु
	u16 val;

	val = ioपढ़ो16(priv->base + NPCM_PSPI_CTL1);
	val &= ~NPCM_PSPI_CTL1_SPIEN;
	ioग_लिखो16(val, priv->base + NPCM_PSPI_CTL1);
पूर्ण

अटल व्योम npcm_pspi_set_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा npcm_pspi *priv = spi_master_get_devdata(spi->master);
	u16 regtemp;
	u16 mode_val;

	चयन (spi->mode & (SPI_CPOL | SPI_CPHA)) अणु
	हाल SPI_MODE_0:
		mode_val = 0;
		अवरोध;
	हाल SPI_MODE_1:
		mode_val = NPCM_PSPI_CTL1_SCIDL;
		अवरोध;
	हाल SPI_MODE_2:
		mode_val = NPCM_PSPI_CTL1_SCM;
		अवरोध;
	हाल SPI_MODE_3:
		mode_val = NPCM_PSPI_CTL1_SCIDL | NPCM_PSPI_CTL1_SCM;
		अवरोध;
	पूर्ण

	regtemp = ioपढ़ो16(priv->base + NPCM_PSPI_CTL1);
	regtemp &= ~(NPCM_PSPI_CTL1_SCM | NPCM_PSPI_CTL1_SCIDL);
	ioग_लिखो16(regtemp | mode_val, priv->base + NPCM_PSPI_CTL1);
पूर्ण

अटल व्योम npcm_pspi_set_transfer_size(काष्ठा npcm_pspi *priv, पूर्णांक size)
अणु
	u16 regtemp;

	regtemp = ioपढ़ो16(NPCM_PSPI_CTL1 + priv->base);

	चयन (size) अणु
	हाल 8:
		regtemp &= ~NPCM_PSPI_CTL1_MOD;
		अवरोध;
	हाल 16:
		regtemp |= NPCM_PSPI_CTL1_MOD;
		अवरोध;
	पूर्ण

	ioग_लिखो16(regtemp, NPCM_PSPI_CTL1 + priv->base);
पूर्ण

अटल व्योम npcm_pspi_set_baudrate(काष्ठा npcm_pspi *priv, अचिन्हित पूर्णांक speed)
अणु
	u32 ckभाग;
	u16 regtemp;

	/* the supported rates are numbers from 4 to 256. */
	ckभाग = DIV_ROUND_CLOSEST(clk_get_rate(priv->clk), (2 * speed)) - 1;

	regtemp = ioपढ़ो16(NPCM_PSPI_CTL1 + priv->base);
	regtemp &= ~NPCM_PSPI_CTL1_SCDV6_0;
	ioग_लिखो16(regtemp | (ckभाग << 9), NPCM_PSPI_CTL1 + priv->base);
पूर्ण

अटल व्योम npcm_pspi_setup_transfer(काष्ठा spi_device *spi,
				     काष्ठा spi_transfer *t)
अणु
	काष्ठा npcm_pspi *priv = spi_master_get_devdata(spi->master);

	priv->tx_buf = t->tx_buf;
	priv->rx_buf = t->rx_buf;
	priv->tx_bytes = t->len;
	priv->rx_bytes = t->len;

	अगर (!priv->is_save_param || priv->mode != spi->mode) अणु
		npcm_pspi_set_mode(spi);
		priv->mode = spi->mode;
	पूर्ण

	/*
	 * If transfer is even length, and 8 bits per word transfer,
	 * then implement 16 bits-per-word transfer.
	 */
	अगर (priv->bits_per_word == 8 && !(t->len & 0x1))
		t->bits_per_word = 16;

	अगर (!priv->is_save_param || priv->bits_per_word != t->bits_per_word) अणु
		npcm_pspi_set_transfer_size(priv, t->bits_per_word);
		priv->bits_per_word = t->bits_per_word;
	पूर्ण

	अगर (!priv->is_save_param || priv->speed_hz != t->speed_hz) अणु
		npcm_pspi_set_baudrate(priv, t->speed_hz);
		priv->speed_hz = t->speed_hz;
	पूर्ण

	अगर (!priv->is_save_param)
		priv->is_save_param = true;
पूर्ण

अटल व्योम npcm_pspi_send(काष्ठा npcm_pspi *priv)
अणु
	पूर्णांक wsize;
	u16 val;

	wsize = min(bytes_per_word(priv->bits_per_word), priv->tx_bytes);
	priv->tx_bytes -= wsize;

	अगर (!priv->tx_buf)
		वापस;

	चयन (wsize) अणु
	हाल 1:
		val = *priv->tx_buf++;
		ioग_लिखो8(val, NPCM_PSPI_DATA + priv->base);
		अवरोध;
	हाल 2:
		val = *priv->tx_buf++;
		val = *priv->tx_buf++ | (val << 8);
		ioग_लिखो16(val, NPCM_PSPI_DATA + priv->base);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम npcm_pspi_recv(काष्ठा npcm_pspi *priv)
अणु
	पूर्णांक rsize;
	u16 val;

	rsize = min(bytes_per_word(priv->bits_per_word), priv->rx_bytes);
	priv->rx_bytes -= rsize;

	अगर (!priv->rx_buf)
		वापस;

	चयन (rsize) अणु
	हाल 1:
		*priv->rx_buf++ = ioपढ़ो8(priv->base + NPCM_PSPI_DATA);
		अवरोध;
	हाल 2:
		val = ioपढ़ो16(priv->base + NPCM_PSPI_DATA);
		*priv->rx_buf++ = (val >> 8);
		*priv->rx_buf++ = val & 0xff;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक npcm_pspi_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *t)
अणु
	काष्ठा npcm_pspi *priv = spi_master_get_devdata(master);
	पूर्णांक status;

	npcm_pspi_setup_transfer(spi, t);
	reinit_completion(&priv->xfer_करोne);
	npcm_pspi_enable(priv);
	status = रुको_क्रम_completion_समयout(&priv->xfer_करोne,
					     msecs_to_jअगरfies
					     (NPCM_PSPI_TIMEOUT_MS));
	अगर (status == 0) अणु
		npcm_pspi_disable(priv);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_pspi_prepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा npcm_pspi *priv = spi_master_get_devdata(master);

	npcm_pspi_irq_enable(priv, NPCM_PSPI_CTL1_EIR | NPCM_PSPI_CTL1_EIW);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_pspi_unprepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा npcm_pspi *priv = spi_master_get_devdata(master);

	npcm_pspi_irq_disable(priv, NPCM_PSPI_CTL1_EIR | NPCM_PSPI_CTL1_EIW);

	वापस 0;
पूर्ण

अटल व्योम npcm_pspi_reset_hw(काष्ठा npcm_pspi *priv)
अणु
	reset_control_निश्चित(priv->reset);
	udelay(5);
	reset_control_deनिश्चित(priv->reset);
पूर्ण

अटल irqवापस_t npcm_pspi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा npcm_pspi *priv = dev_id;
	u8 stat;

	stat = ioपढ़ो8(priv->base + NPCM_PSPI_STAT);

	अगर (!priv->tx_buf && !priv->rx_buf)
		वापस IRQ_NONE;

	अगर (priv->tx_buf) अणु
		अगर (stat & NPCM_PSPI_STAT_RBF) अणु
			ioपढ़ो8(NPCM_PSPI_DATA + priv->base);
			अगर (priv->tx_bytes == 0) अणु
				npcm_pspi_disable(priv);
				complete(&priv->xfer_करोne);
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण

		अगर ((stat & NPCM_PSPI_STAT_BSY) == 0)
			अगर (priv->tx_bytes)
				npcm_pspi_send(priv);
	पूर्ण

	अगर (priv->rx_buf) अणु
		अगर (stat & NPCM_PSPI_STAT_RBF) अणु
			अगर (!priv->rx_bytes)
				वापस IRQ_NONE;

			npcm_pspi_recv(priv);

			अगर (!priv->rx_bytes) अणु
				npcm_pspi_disable(priv);
				complete(&priv->xfer_करोne);
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण

		अगर (((stat & NPCM_PSPI_STAT_BSY) == 0) && !priv->tx_buf)
			ioग_लिखो8(0x0, NPCM_PSPI_DATA + priv->base);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक npcm_pspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm_pspi *priv;
	काष्ठा spi_master *master;
	अचिन्हित दीर्घ clk_hz;
	पूर्णांक irq;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*priv));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	priv = spi_master_get_devdata(master);
	priv->master = master;
	priv->is_save_param = false;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ out_master_put;
	पूर्ण

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(priv->clk);
		जाओ out_master_put;
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		जाओ out_master_put;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out_disable_clk;
	पूर्ण

	priv->reset = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->reset)) अणु
		ret = PTR_ERR(priv->reset);
		जाओ out_disable_clk;
	पूर्ण

	/* reset SPI-HW block */
	npcm_pspi_reset_hw(priv);

	ret = devm_request_irq(&pdev->dev, irq, npcm_pspi_handler, 0,
			       "npcm-pspi", priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		जाओ out_disable_clk;
	पूर्ण

	init_completion(&priv->xfer_करोne);

	clk_hz = clk_get_rate(priv->clk);

	master->max_speed_hz = DIV_ROUND_UP(clk_hz, NPCM_PSPI_MIN_CLK_DIVIDER);
	master->min_speed_hz = DIV_ROUND_UP(clk_hz, NPCM_PSPI_MAX_CLK_DIVIDER);
	master->mode_bits = SPI_CPHA | SPI_CPOL;
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = -1;
	master->bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	master->transfer_one = npcm_pspi_transfer_one;
	master->prepare_transfer_hardware =
		npcm_pspi_prepare_transfer_hardware;
	master->unprepare_transfer_hardware =
		npcm_pspi_unprepare_transfer_hardware;
	master->use_gpio_descriptors = true;

	/* set to शेष घड़ी rate */
	npcm_pspi_set_baudrate(priv, NPCM_PSPI_DEFAULT_CLK);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret)
		जाओ out_disable_clk;

	pr_info("NPCM Peripheral SPI %d probed\n", master->bus_num);

	वापस 0;

out_disable_clk:
	clk_disable_unprepare(priv->clk);

out_master_put:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक npcm_pspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा npcm_pspi *priv = spi_master_get_devdata(master);

	npcm_pspi_reset_hw(priv);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id npcm_pspi_match[] = अणु
	अणु .compatible = "nuvoton,npcm750-pspi", .data = शून्य पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm_pspi_match);

अटल काष्ठा platक्रमm_driver npcm_pspi_driver = अणु
	.driver		= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= npcm_pspi_match,
	पूर्ण,
	.probe		= npcm_pspi_probe,
	.हटाओ		= npcm_pspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(npcm_pspi_driver);

MODULE_DESCRIPTION("NPCM peripheral SPI Controller driver");
MODULE_AUTHOR("Tomer Maimon <tomer.maimon@nuvoton.com>");
MODULE_LICENSE("GPL v2");

