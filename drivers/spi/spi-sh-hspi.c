<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH HSPI bus driver
 *
 * Copyright (C) 2011  Kuninori Morimoto
 *
 * Based on spi-sh.c:
 * Based on pxa2xx_spi.c:
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2005 Stephen Street / StreetFire Sound Lअसल
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/sh_hspi.h>

#घोषणा SPCR	0x00
#घोषणा SPSR	0x04
#घोषणा SPSCR	0x08
#घोषणा SPTBR	0x0C
#घोषणा SPRBR	0x10
#घोषणा SPCR2	0x14

/* SPSR */
#घोषणा RXFL	(1 << 2)

काष्ठा hspi_priv अणु
	व्योम __iomem *addr;
	काष्ठा spi_controller *ctlr;
	काष्ठा device *dev;
	काष्ठा clk *clk;
पूर्ण;

/*
 *		basic function
 */
अटल व्योम hspi_ग_लिखो(काष्ठा hspi_priv *hspi, पूर्णांक reg, u32 val)
अणु
	ioग_लिखो32(val, hspi->addr + reg);
पूर्ण

अटल u32 hspi_पढ़ो(काष्ठा hspi_priv *hspi, पूर्णांक reg)
अणु
	वापस ioपढ़ो32(hspi->addr + reg);
पूर्ण

अटल व्योम hspi_bit_set(काष्ठा hspi_priv *hspi, पूर्णांक reg, u32 mask, u32 set)
अणु
	u32 val = hspi_पढ़ो(hspi, reg);

	val &= ~mask;
	val |= set & mask;

	hspi_ग_लिखो(hspi, reg, val);
पूर्ण

/*
 *		transfer function
 */
अटल पूर्णांक hspi_status_check_समयout(काष्ठा hspi_priv *hspi, u32 mask, u32 val)
अणु
	पूर्णांक t = 256;

	जबतक (t--) अणु
		अगर ((mask & hspi_पढ़ो(hspi, SPSR)) == val)
			वापस 0;

		udelay(10);
	पूर्ण

	dev_err(hspi->dev, "timeout\n");
	वापस -ETIMEDOUT;
पूर्ण

/*
 *		spi master function
 */

#घोषणा hspi_hw_cs_enable(hspi)		hspi_hw_cs_ctrl(hspi, 0)
#घोषणा hspi_hw_cs_disable(hspi)	hspi_hw_cs_ctrl(hspi, 1)
अटल व्योम hspi_hw_cs_ctrl(काष्ठा hspi_priv *hspi, पूर्णांक hi)
अणु
	hspi_bit_set(hspi, SPSCR, (1 << 6), (hi) << 6);
पूर्ण

अटल व्योम hspi_hw_setup(काष्ठा hspi_priv *hspi,
			  काष्ठा spi_message *msg,
			  काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा device *dev = hspi->dev;
	u32 spcr, iभाग_clk;
	u32 rate, best_rate, min, पंचांगp;

	/*
	 * find best IDIV/CLKCx settings
	 */
	min = ~0;
	best_rate = 0;
	spcr = 0;
	क्रम (iभाग_clk = 0x00; iभाग_clk <= 0x3F; iभाग_clk++) अणु
		rate = clk_get_rate(hspi->clk);

		/* IDIV calculation */
		अगर (iभाग_clk & (1 << 5))
			rate /= 128;
		अन्यथा
			rate /= 16;

		/* CLKCx calculation */
		rate /= (((iभाग_clk & 0x1F) + 1) * 2);

		/* save best settings */
		पंचांगp = असल(t->speed_hz - rate);
		अगर (पंचांगp < min) अणु
			min = पंचांगp;
			spcr = iभाग_clk;
			best_rate = rate;
		पूर्ण
	पूर्ण

	अगर (spi->mode & SPI_CPHA)
		spcr |= 1 << 7;
	अगर (spi->mode & SPI_CPOL)
		spcr |= 1 << 6;

	dev_dbg(dev, "speed %d/%d\n", t->speed_hz, best_rate);

	hspi_ग_लिखो(hspi, SPCR, spcr);
	hspi_ग_लिखो(hspi, SPSR, 0x0);
	hspi_ग_लिखो(hspi, SPSCR, 0x21);	/* master mode / CS control */
पूर्ण

अटल पूर्णांक hspi_transfer_one_message(काष्ठा spi_controller *ctlr,
				     काष्ठा spi_message *msg)
अणु
	काष्ठा hspi_priv *hspi = spi_controller_get_devdata(ctlr);
	काष्ठा spi_transfer *t;
	u32 tx;
	u32 rx;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक cs_change;
	स्थिर पूर्णांक nsecs = 50;

	dev_dbg(hspi->dev, "%s\n", __func__);

	cs_change = 1;
	ret = 0;
	list_क्रम_each_entry(t, &msg->transfers, transfer_list) अणु

		अगर (cs_change) अणु
			hspi_hw_setup(hspi, msg, t);
			hspi_hw_cs_enable(hspi);
			ndelay(nsecs);
		पूर्ण
		cs_change = t->cs_change;

		क्रम (i = 0; i < t->len; i++) अणु

			/* रुको reमुख्यs */
			ret = hspi_status_check_समयout(hspi, 0x1, 0);
			अगर (ret < 0)
				अवरोध;

			tx = 0;
			अगर (t->tx_buf)
				tx = (u32)((u8 *)t->tx_buf)[i];

			hspi_ग_लिखो(hspi, SPTBR, tx);

			/* रुको receive */
			ret = hspi_status_check_समयout(hspi, 0x4, 0x4);
			अगर (ret < 0)
				अवरोध;

			rx = hspi_पढ़ो(hspi, SPRBR);
			अगर (t->rx_buf)
				((u8 *)t->rx_buf)[i] = (u8)rx;

		पूर्ण

		msg->actual_length += t->len;

		spi_transfer_delay_exec(t);

		अगर (cs_change) अणु
			ndelay(nsecs);
			hspi_hw_cs_disable(hspi);
			ndelay(nsecs);
		पूर्ण
	पूर्ण

	msg->status = ret;
	अगर (!cs_change) अणु
		ndelay(nsecs);
		hspi_hw_cs_disable(hspi);
	पूर्ण
	spi_finalize_current_message(ctlr);

	वापस ret;
पूर्ण

अटल पूर्णांक hspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा spi_controller *ctlr;
	काष्ठा hspi_priv *hspi;
	काष्ठा clk *clk;
	पूर्णांक ret;

	/* get base addr */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "invalid resource\n");
		वापस -EINVAL;
	पूर्ण

	ctlr = spi_alloc_master(&pdev->dev, माप(*hspi));
	अगर (!ctlr)
		वापस -ENOMEM;

	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "couldn't get clock\n");
		ret = -EINVAL;
		जाओ error0;
	पूर्ण

	hspi = spi_controller_get_devdata(ctlr);
	platक्रमm_set_drvdata(pdev, hspi);

	/* init hspi */
	hspi->ctlr	= ctlr;
	hspi->dev	= &pdev->dev;
	hspi->clk	= clk;
	hspi->addr	= devm_ioremap(hspi->dev,
				       res->start, resource_size(res));
	अगर (!hspi->addr) अणु
		ret = -ENOMEM;
		जाओ error1;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	ctlr->bus_num = pdev->id;
	ctlr->mode_bits	= SPI_CPOL | SPI_CPHA;
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->स्वतः_runसमय_pm = true;
	ctlr->transfer_one_message = hspi_transfer_one_message;
	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "devm_spi_register_controller error.\n");
		जाओ error2;
	पूर्ण

	वापस 0;

 error2:
	pm_runसमय_disable(&pdev->dev);
 error1:
	clk_put(clk);
 error0:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

अटल पूर्णांक hspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hspi_priv *hspi = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	clk_put(hspi->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hspi_of_match[] = अणु
	अणु .compatible = "renesas,hspi", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hspi_of_match);

अटल काष्ठा platक्रमm_driver hspi_driver = अणु
	.probe = hspi_probe,
	.हटाओ = hspi_हटाओ,
	.driver = अणु
		.name = "sh-hspi",
		.of_match_table = hspi_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hspi_driver);

MODULE_DESCRIPTION("SuperH HSPI bus driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
MODULE_ALIAS("platform:sh-hspi");
