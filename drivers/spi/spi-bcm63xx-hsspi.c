<शैली गुरु>
/*
 * Broadcom BCM63XX High Speed SPI Controller driver
 *
 * Copyright 2000-2010 Broadcom Corporation
 * Copyright 2012-2013 Jonas Gorski <jogo@खोलोwrt.org>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/reset.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा HSSPI_GLOBAL_CTRL_REG			0x0
#घोषणा GLOBAL_CTRL_CS_POLARITY_SHIFT		0
#घोषणा GLOBAL_CTRL_CS_POLARITY_MASK		0x000000ff
#घोषणा GLOBAL_CTRL_PLL_CLK_CTRL_SHIFT		8
#घोषणा GLOBAL_CTRL_PLL_CLK_CTRL_MASK		0x0000ff00
#घोषणा GLOBAL_CTRL_CLK_GATE_SSOFF		BIT(16)
#घोषणा GLOBAL_CTRL_CLK_POLARITY		BIT(17)
#घोषणा GLOBAL_CTRL_MOSI_IDLE			BIT(18)

#घोषणा HSSPI_GLOBAL_EXT_TRIGGER_REG		0x4

#घोषणा HSSPI_INT_STATUS_REG			0x8
#घोषणा HSSPI_INT_STATUS_MASKED_REG		0xc
#घोषणा HSSPI_INT_MASK_REG			0x10

#घोषणा HSSPI_PINGx_CMD_DONE(i)			BIT((i * 8) + 0)
#घोषणा HSSPI_PINGx_RX_OVER(i)			BIT((i * 8) + 1)
#घोषणा HSSPI_PINGx_TX_UNDER(i)			BIT((i * 8) + 2)
#घोषणा HSSPI_PINGx_POLL_TIMEOUT(i)		BIT((i * 8) + 3)
#घोषणा HSSPI_PINGx_CTRL_INVAL(i)		BIT((i * 8) + 4)

#घोषणा HSSPI_INT_CLEAR_ALL			0xff001f1f

#घोषणा HSSPI_PINGPONG_COMMAND_REG(x)		(0x80 + (x) * 0x40)
#घोषणा PINGPONG_CMD_COMMAND_MASK		0xf
#घोषणा PINGPONG_COMMAND_NOOP			0
#घोषणा PINGPONG_COMMAND_START_NOW		1
#घोषणा PINGPONG_COMMAND_START_TRIGGER		2
#घोषणा PINGPONG_COMMAND_HALT			3
#घोषणा PINGPONG_COMMAND_FLUSH			4
#घोषणा PINGPONG_CMD_PROखाता_SHIFT		8
#घोषणा PINGPONG_CMD_SS_SHIFT			12

#घोषणा HSSPI_PINGPONG_STATUS_REG(x)		(0x84 + (x) * 0x40)

#घोषणा HSSPI_PROखाता_CLK_CTRL_REG(x)		(0x100 + (x) * 0x20)
#घोषणा CLK_CTRL_FREQ_CTRL_MASK			0x0000ffff
#घोषणा CLK_CTRL_SPI_CLK_2X_SEL			BIT(14)
#घोषणा CLK_CTRL_ACCUM_RST_ON_LOOP		BIT(15)

#घोषणा HSSPI_PROखाता_SIGNAL_CTRL_REG(x)	(0x104 + (x) * 0x20)
#घोषणा SIGNAL_CTRL_LATCH_RISING		BIT(12)
#घोषणा SIGNAL_CTRL_LAUNCH_RISING		BIT(13)
#घोषणा SIGNAL_CTRL_ASYNC_INPUT_PATH		BIT(16)

#घोषणा HSSPI_PROखाता_MODE_CTRL_REG(x)		(0x108 + (x) * 0x20)
#घोषणा MODE_CTRL_MULTIDATA_RD_STRT_SHIFT	8
#घोषणा MODE_CTRL_MULTIDATA_WR_STRT_SHIFT	12
#घोषणा MODE_CTRL_MULTIDATA_RD_SIZE_SHIFT	16
#घोषणा MODE_CTRL_MULTIDATA_WR_SIZE_SHIFT	18
#घोषणा MODE_CTRL_MODE_3WIRE			BIT(20)
#घोषणा MODE_CTRL_PREPENDBYTE_CNT_SHIFT		24

#घोषणा HSSPI_FIFO_REG(x)			(0x200 + (x) * 0x200)


#घोषणा HSSPI_OP_MULTIBIT			BIT(11)
#घोषणा HSSPI_OP_CODE_SHIFT			13
#घोषणा HSSPI_OP_SLEEP				(0 << HSSPI_OP_CODE_SHIFT)
#घोषणा HSSPI_OP_READ_WRITE			(1 << HSSPI_OP_CODE_SHIFT)
#घोषणा HSSPI_OP_WRITE				(2 << HSSPI_OP_CODE_SHIFT)
#घोषणा HSSPI_OP_READ				(3 << HSSPI_OP_CODE_SHIFT)
#घोषणा HSSPI_OP_SETIRQ				(4 << HSSPI_OP_CODE_SHIFT)

#घोषणा HSSPI_BUFFER_LEN			512
#घोषणा HSSPI_OPCODE_LEN			2

#घोषणा HSSPI_MAX_PREPEND_LEN			15

#घोषणा HSSPI_MAX_SYNC_CLOCK			30000000

#घोषणा HSSPI_SPI_MAX_CS			8
#घोषणा HSSPI_BUS_NUM				1 /* 0 is legacy SPI */

काष्ठा bcm63xx_hsspi अणु
	काष्ठा completion करोne;
	काष्ठा mutex bus_mutex;

	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *clk;
	काष्ठा clk *pll_clk;
	व्योम __iomem *regs;
	u8 __iomem *fअगरo;

	u32 speed_hz;
	u8 cs_polarity;
पूर्ण;

अटल व्योम bcm63xx_hsspi_set_cs(काष्ठा bcm63xx_hsspi *bs, अचिन्हित पूर्णांक cs,
				 bool active)
अणु
	u32 reg;

	mutex_lock(&bs->bus_mutex);
	reg = __raw_पढ़ोl(bs->regs + HSSPI_GLOBAL_CTRL_REG);

	reg &= ~BIT(cs);
	अगर (active == !(bs->cs_polarity & BIT(cs)))
		reg |= BIT(cs);

	__raw_ग_लिखोl(reg, bs->regs + HSSPI_GLOBAL_CTRL_REG);
	mutex_unlock(&bs->bus_mutex);
पूर्ण

अटल व्योम bcm63xx_hsspi_set_clk(काष्ठा bcm63xx_hsspi *bs,
				  काष्ठा spi_device *spi, पूर्णांक hz)
अणु
	अचिन्हित पूर्णांक profile = spi->chip_select;
	u32 reg;

	reg = DIV_ROUND_UP(2048, DIV_ROUND_UP(bs->speed_hz, hz));
	__raw_ग_लिखोl(CLK_CTRL_ACCUM_RST_ON_LOOP | reg,
		     bs->regs + HSSPI_PROखाता_CLK_CTRL_REG(profile));

	reg = __raw_पढ़ोl(bs->regs + HSSPI_PROखाता_SIGNAL_CTRL_REG(profile));
	अगर (hz > HSSPI_MAX_SYNC_CLOCK)
		reg |= SIGNAL_CTRL_ASYNC_INPUT_PATH;
	अन्यथा
		reg &= ~SIGNAL_CTRL_ASYNC_INPUT_PATH;
	__raw_ग_लिखोl(reg, bs->regs + HSSPI_PROखाता_SIGNAL_CTRL_REG(profile));

	mutex_lock(&bs->bus_mutex);
	/* setup घड़ी polarity */
	reg = __raw_पढ़ोl(bs->regs + HSSPI_GLOBAL_CTRL_REG);
	reg &= ~GLOBAL_CTRL_CLK_POLARITY;
	अगर (spi->mode & SPI_CPOL)
		reg |= GLOBAL_CTRL_CLK_POLARITY;
	__raw_ग_लिखोl(reg, bs->regs + HSSPI_GLOBAL_CTRL_REG);
	mutex_unlock(&bs->bus_mutex);
पूर्ण

अटल पूर्णांक bcm63xx_hsspi_करो_txrx(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा bcm63xx_hsspi *bs = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक chip_select = spi->chip_select;
	u16 opcode = 0;
	पूर्णांक pending = t->len;
	पूर्णांक step_size = HSSPI_BUFFER_LEN;
	स्थिर u8 *tx = t->tx_buf;
	u8 *rx = t->rx_buf;

	bcm63xx_hsspi_set_clk(bs, spi, t->speed_hz);
	bcm63xx_hsspi_set_cs(bs, spi->chip_select, true);

	अगर (tx && rx)
		opcode = HSSPI_OP_READ_WRITE;
	अन्यथा अगर (tx)
		opcode = HSSPI_OP_WRITE;
	अन्यथा अगर (rx)
		opcode = HSSPI_OP_READ;

	अगर (opcode != HSSPI_OP_READ)
		step_size -= HSSPI_OPCODE_LEN;

	अगर ((opcode == HSSPI_OP_READ && t->rx_nbits == SPI_NBITS_DUAL) ||
	    (opcode == HSSPI_OP_WRITE && t->tx_nbits == SPI_NBITS_DUAL))
		opcode |= HSSPI_OP_MULTIBIT;

	__raw_ग_लिखोl(1 << MODE_CTRL_MULTIDATA_WR_SIZE_SHIFT |
		     1 << MODE_CTRL_MULTIDATA_RD_SIZE_SHIFT | 0xff,
		     bs->regs + HSSPI_PROखाता_MODE_CTRL_REG(chip_select));

	जबतक (pending > 0) अणु
		पूर्णांक curr_step = min_t(पूर्णांक, step_size, pending);

		reinit_completion(&bs->करोne);
		अगर (tx) अणु
			स_नकल_toio(bs->fअगरo + HSSPI_OPCODE_LEN, tx, curr_step);
			tx += curr_step;
		पूर्ण

		__raw_ग_लिखोw(opcode | curr_step, bs->fअगरo);

		/* enable पूर्णांकerrupt */
		__raw_ग_लिखोl(HSSPI_PINGx_CMD_DONE(0),
			     bs->regs + HSSPI_INT_MASK_REG);

		/* start the transfer */
		__raw_ग_लिखोl(!chip_select << PINGPONG_CMD_SS_SHIFT |
			     chip_select << PINGPONG_CMD_PROखाता_SHIFT |
			     PINGPONG_COMMAND_START_NOW,
			     bs->regs + HSSPI_PINGPONG_COMMAND_REG(0));

		अगर (रुको_क्रम_completion_समयout(&bs->करोne, HZ) == 0) अणु
			dev_err(&bs->pdev->dev, "transfer timed out!\n");
			वापस -ETIMEDOUT;
		पूर्ण

		अगर (rx) अणु
			स_नकल_fromio(rx, bs->fअगरo, curr_step);
			rx += curr_step;
		पूर्ण

		pending -= curr_step;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_hsspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा bcm63xx_hsspi *bs = spi_master_get_devdata(spi->master);
	u32 reg;

	reg = __raw_पढ़ोl(bs->regs +
			  HSSPI_PROखाता_SIGNAL_CTRL_REG(spi->chip_select));
	reg &= ~(SIGNAL_CTRL_LAUNCH_RISING | SIGNAL_CTRL_LATCH_RISING);
	अगर (spi->mode & SPI_CPHA)
		reg |= SIGNAL_CTRL_LAUNCH_RISING;
	अन्यथा
		reg |= SIGNAL_CTRL_LATCH_RISING;
	__raw_ग_लिखोl(reg, bs->regs +
		     HSSPI_PROखाता_SIGNAL_CTRL_REG(spi->chip_select));

	mutex_lock(&bs->bus_mutex);
	reg = __raw_पढ़ोl(bs->regs + HSSPI_GLOBAL_CTRL_REG);

	/* only change actual polarities अगर there is no transfer */
	अगर ((reg & GLOBAL_CTRL_CS_POLARITY_MASK) == bs->cs_polarity) अणु
		अगर (spi->mode & SPI_CS_HIGH)
			reg |= BIT(spi->chip_select);
		अन्यथा
			reg &= ~BIT(spi->chip_select);
		__raw_ग_लिखोl(reg, bs->regs + HSSPI_GLOBAL_CTRL_REG);
	पूर्ण

	अगर (spi->mode & SPI_CS_HIGH)
		bs->cs_polarity |= BIT(spi->chip_select);
	अन्यथा
		bs->cs_polarity &= ~BIT(spi->chip_select);

	mutex_unlock(&bs->bus_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_hsspi_transfer_one(काष्ठा spi_master *master,
				      काष्ठा spi_message *msg)
अणु
	काष्ठा bcm63xx_hsspi *bs = spi_master_get_devdata(master);
	काष्ठा spi_transfer *t;
	काष्ठा spi_device *spi = msg->spi;
	पूर्णांक status = -EINVAL;
	पूर्णांक dummy_cs;
	u32 reg;

	/* This controller करोes not support keeping CS active during idle.
	 * To work around this, we use the following ugly hack:
	 *
	 * a. Invert the target chip select's polarity so it will be active.
	 * b. Select a "dummy" chip select to use as the hardware target.
	 * c. Invert the dummy chip select's polarity so it will be inactive
	 *    during the actual transfers.
	 * d. Tell the hardware to send to the dummy chip select. Thanks to
	 *    the multiplexed nature of SPI the actual target will receive
	 *    the transfer and we see its response.
	 *
	 * e. At the end restore the polarities again to their शेष values.
	 */

	dummy_cs = !spi->chip_select;
	bcm63xx_hsspi_set_cs(bs, dummy_cs, true);

	list_क्रम_each_entry(t, &msg->transfers, transfer_list) अणु
		status = bcm63xx_hsspi_करो_txrx(spi, t);
		अगर (status)
			अवरोध;

		msg->actual_length += t->len;

		spi_transfer_delay_exec(t);

		अगर (t->cs_change)
			bcm63xx_hsspi_set_cs(bs, spi->chip_select, false);
	पूर्ण

	mutex_lock(&bs->bus_mutex);
	reg = __raw_पढ़ोl(bs->regs + HSSPI_GLOBAL_CTRL_REG);
	reg &= ~GLOBAL_CTRL_CS_POLARITY_MASK;
	reg |= bs->cs_polarity;
	__raw_ग_लिखोl(reg, bs->regs + HSSPI_GLOBAL_CTRL_REG);
	mutex_unlock(&bs->bus_mutex);

	msg->status = status;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

अटल irqवापस_t bcm63xx_hsspi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm63xx_hsspi *bs = (काष्ठा bcm63xx_hsspi *)dev_id;

	अगर (__raw_पढ़ोl(bs->regs + HSSPI_INT_STATUS_MASKED_REG) == 0)
		वापस IRQ_NONE;

	__raw_ग_लिखोl(HSSPI_INT_CLEAR_ALL, bs->regs + HSSPI_INT_STATUS_REG);
	__raw_ग_लिखोl(0, bs->regs + HSSPI_INT_MASK_REG);

	complete(&bs->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm63xx_hsspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा bcm63xx_hsspi *bs;
	व्योम __iomem *regs;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk, *pll_clk = शून्य;
	पूर्णांक irq, ret;
	u32 reg, rate, num_cs = HSSPI_SPI_MAX_CS;
	काष्ठा reset_control *reset;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	clk = devm_clk_get(dev, "hsspi");

	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	reset = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(reset))
		वापस PTR_ERR(reset);

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_reset(reset);
	अगर (ret) अणु
		dev_err(dev, "unable to reset device: %d\n", ret);
		जाओ out_disable_clk;
	पूर्ण

	rate = clk_get_rate(clk);
	अगर (!rate) अणु
		pll_clk = devm_clk_get(dev, "pll");

		अगर (IS_ERR(pll_clk)) अणु
			ret = PTR_ERR(pll_clk);
			जाओ out_disable_clk;
		पूर्ण

		ret = clk_prepare_enable(pll_clk);
		अगर (ret)
			जाओ out_disable_clk;

		rate = clk_get_rate(pll_clk);
		अगर (!rate) अणु
			ret = -EINVAL;
			जाओ out_disable_pll_clk;
		पूर्ण
	पूर्ण

	master = spi_alloc_master(&pdev->dev, माप(*bs));
	अगर (!master) अणु
		ret = -ENOMEM;
		जाओ out_disable_pll_clk;
	पूर्ण

	bs = spi_master_get_devdata(master);
	bs->pdev = pdev;
	bs->clk = clk;
	bs->pll_clk = pll_clk;
	bs->regs = regs;
	bs->speed_hz = rate;
	bs->fअगरo = (u8 __iomem *)(bs->regs + HSSPI_FIFO_REG(0));

	mutex_init(&bs->bus_mutex);
	init_completion(&bs->करोne);

	master->dev.of_node = dev->of_node;
	अगर (!dev->of_node)
		master->bus_num = HSSPI_BUS_NUM;

	of_property_पढ़ो_u32(dev->of_node, "num-cs", &num_cs);
	अगर (num_cs > 8) अणु
		dev_warn(dev, "unsupported number of cs (%i), reducing to 8\n",
			 num_cs);
		num_cs = HSSPI_SPI_MAX_CS;
	पूर्ण
	master->num_chipselect = num_cs;
	master->setup = bcm63xx_hsspi_setup;
	master->transfer_one_message = bcm63xx_hsspi_transfer_one;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH |
			    SPI_RX_DUAL | SPI_TX_DUAL;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->स्वतः_runसमय_pm = true;

	platक्रमm_set_drvdata(pdev, master);

	/* Initialize the hardware */
	__raw_ग_लिखोl(0, bs->regs + HSSPI_INT_MASK_REG);

	/* clean up any pending पूर्णांकerrupts */
	__raw_ग_लिखोl(HSSPI_INT_CLEAR_ALL, bs->regs + HSSPI_INT_STATUS_REG);

	/* पढ़ो out शेष CS polarities */
	reg = __raw_पढ़ोl(bs->regs + HSSPI_GLOBAL_CTRL_REG);
	bs->cs_polarity = reg & GLOBAL_CTRL_CS_POLARITY_MASK;
	__raw_ग_लिखोl(reg | GLOBAL_CTRL_CLK_GATE_SSOFF,
		     bs->regs + HSSPI_GLOBAL_CTRL_REG);

	ret = devm_request_irq(dev, irq, bcm63xx_hsspi_पूर्णांकerrupt, IRQF_SHARED,
			       pdev->name, bs);

	अगर (ret)
		जाओ out_put_master;

	pm_runसमय_enable(&pdev->dev);

	/* रेजिस्टर and we are करोne */
	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret)
		जाओ out_pm_disable;

	वापस 0;

out_pm_disable:
	pm_runसमय_disable(&pdev->dev);
out_put_master:
	spi_master_put(master);
out_disable_pll_clk:
	clk_disable_unprepare(pll_clk);
out_disable_clk:
	clk_disable_unprepare(clk);
	वापस ret;
पूर्ण


अटल पूर्णांक bcm63xx_hsspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा bcm63xx_hsspi *bs = spi_master_get_devdata(master);

	/* reset the hardware and block queue progress */
	__raw_ग_लिखोl(0, bs->regs + HSSPI_INT_MASK_REG);
	clk_disable_unprepare(bs->pll_clk);
	clk_disable_unprepare(bs->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bcm63xx_hsspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा bcm63xx_hsspi *bs = spi_master_get_devdata(master);

	spi_master_suspend(master);
	clk_disable_unprepare(bs->pll_clk);
	clk_disable_unprepare(bs->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_hsspi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा bcm63xx_hsspi *bs = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(bs->clk);
	अगर (ret)
		वापस ret;

	अगर (bs->pll_clk) अणु
		ret = clk_prepare_enable(bs->pll_clk);
		अगर (ret) अणु
			clk_disable_unprepare(bs->clk);
			वापस ret;
		पूर्ण
	पूर्ण

	spi_master_resume(master);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(bcm63xx_hsspi_pm_ops, bcm63xx_hsspi_suspend,
			 bcm63xx_hsspi_resume);

अटल स्थिर काष्ठा of_device_id bcm63xx_hsspi_of_match[] = अणु
	अणु .compatible = "brcm,bcm6328-hsspi", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm63xx_hsspi_of_match);

अटल काष्ठा platक्रमm_driver bcm63xx_hsspi_driver = अणु
	.driver = अणु
		.name	= "bcm63xx-hsspi",
		.pm	= &bcm63xx_hsspi_pm_ops,
		.of_match_table = bcm63xx_hsspi_of_match,
	पूर्ण,
	.probe		= bcm63xx_hsspi_probe,
	.हटाओ		= bcm63xx_hsspi_हटाओ,
पूर्ण;

module_platक्रमm_driver(bcm63xx_hsspi_driver);

MODULE_ALIAS("platform:bcm63xx_hsspi");
MODULE_DESCRIPTION("Broadcom BCM63xx High Speed SPI Controller driver");
MODULE_AUTHOR("Jonas Gorski <jogo@openwrt.org>");
MODULE_LICENSE("GPL");
