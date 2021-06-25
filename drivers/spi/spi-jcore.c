<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * J-Core SPI controller driver
 *
 * Copyright (C) 2012-2016 Smart Energy Instruments, Inc.
 *
 * Current version by Rich Felker
 * Based loosely on initial version by Oleksandr G Zhadan
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>

#घोषणा DRV_NAME	"jcore_spi"

#घोषणा CTRL_REG	0x0
#घोषणा DATA_REG	0x4

#घोषणा JCORE_SPI_CTRL_XMIT		0x02
#घोषणा JCORE_SPI_STAT_BUSY		0x02
#घोषणा JCORE_SPI_CTRL_LOOP		0x08
#घोषणा JCORE_SPI_CTRL_CS_BITS		0x15

#घोषणा JCORE_SPI_WAIT_RDY_MAX_LOOP	2000000

काष्ठा jcore_spi अणु
	काष्ठा spi_master *master;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक cs_reg;
	अचिन्हित पूर्णांक speed_reg;
	अचिन्हित पूर्णांक speed_hz;
	अचिन्हित पूर्णांक घड़ी_freq;
पूर्ण;

अटल पूर्णांक jcore_spi_रुको(व्योम __iomem *ctrl_reg)
अणु
	अचिन्हित समयout = JCORE_SPI_WAIT_RDY_MAX_LOOP;

	करो अणु
		अगर (!(पढ़ोl(ctrl_reg) & JCORE_SPI_STAT_BUSY))
			वापस 0;
		cpu_relax();
	पूर्ण जबतक (--समयout);

	वापस -EBUSY;
पूर्ण

अटल व्योम jcore_spi_program(काष्ठा jcore_spi *hw)
अणु
	व्योम __iomem *ctrl_reg = hw->base + CTRL_REG;

	अगर (jcore_spi_रुको(ctrl_reg))
		dev_err(hw->master->dev.parent,
			"timeout waiting to program ctrl reg.\n");

	ग_लिखोl(hw->cs_reg | hw->speed_reg, ctrl_reg);
पूर्ण

अटल व्योम jcore_spi_chipsel(काष्ठा spi_device *spi, bool value)
अणु
	काष्ठा jcore_spi *hw = spi_master_get_devdata(spi->master);
	u32 csbit = 1U << (2 * spi->chip_select);

	dev_dbg(hw->master->dev.parent, "chipselect %d\n", spi->chip_select);

	अगर (value)
		hw->cs_reg |= csbit;
	अन्यथा
		hw->cs_reg &= ~csbit;

	jcore_spi_program(hw);
पूर्ण

अटल व्योम jcore_spi_baudrate(काष्ठा jcore_spi *hw, पूर्णांक speed)
अणु
	अगर (speed == hw->speed_hz)
		वापस;
	hw->speed_hz = speed;
	अगर (speed >= hw->घड़ी_freq / 2)
		hw->speed_reg = 0;
	अन्यथा
		hw->speed_reg = ((hw->घड़ी_freq / 2 / speed) - 1) << 27;
	jcore_spi_program(hw);
	dev_dbg(hw->master->dev.parent, "speed=%d reg=0x%x\n",
		speed, hw->speed_reg);
पूर्ण

अटल पूर्णांक jcore_spi_txrx(काष्ठा spi_master *master, काष्ठा spi_device *spi,
			  काष्ठा spi_transfer *t)
अणु
	काष्ठा jcore_spi *hw = spi_master_get_devdata(master);

	व्योम __iomem *ctrl_reg = hw->base + CTRL_REG;
	व्योम __iomem *data_reg = hw->base + DATA_REG;
	u32 xmit;

	/* data buffers */
	स्थिर अचिन्हित अक्षर *tx;
	अचिन्हित अक्षर *rx;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक count;

	jcore_spi_baudrate(hw, t->speed_hz);

	xmit = hw->cs_reg | hw->speed_reg | JCORE_SPI_CTRL_XMIT;
	tx = t->tx_buf;
	rx = t->rx_buf;
	len = t->len;

	क्रम (count = 0; count < len; count++) अणु
		अगर (jcore_spi_रुको(ctrl_reg))
			अवरोध;

		ग_लिखोl(tx ? *tx++ : 0, data_reg);
		ग_लिखोl(xmit, ctrl_reg);

		अगर (jcore_spi_रुको(ctrl_reg))
			अवरोध;

		अगर (rx)
			*rx++ = पढ़ोl(data_reg);
	पूर्ण

	spi_finalize_current_transfer(master);

	अगर (count < len)
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक jcore_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा jcore_spi *hw;
	काष्ठा spi_master *master;
	काष्ठा resource *res;
	u32 घड़ी_freq;
	काष्ठा clk *clk;
	पूर्णांक err = -ENODEV;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा jcore_spi));
	अगर (!master)
		वापस err;

	/* Setup the master state. */
	master->num_chipselect = 3;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->transfer_one = jcore_spi_txrx;
	master->set_cs = jcore_spi_chipsel;
	master->dev.of_node = node;
	master->bus_num = pdev->id;

	hw = spi_master_get_devdata(master);
	hw->master = master;
	platक्रमm_set_drvdata(pdev, hw);

	/* Find and map our resources */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		जाओ निकास_busy;
	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), pdev->name))
		जाओ निकास_busy;
	hw->base = devm_ioremap(&pdev->dev, res->start,
					resource_size(res));
	अगर (!hw->base)
		जाओ निकास_busy;

	/*
	 * The SPI घड़ी rate controlled via a configurable घड़ी भागider
	 * which is applied to the reference घड़ी. A 50 MHz reference is
	 * most suitable क्रम obtaining standard SPI घड़ी rates, but some
	 * designs may have a dअगरferent reference घड़ी, and the DT must
	 * make the driver aware so that it can properly program the
	 * requested rate. If the घड़ी is omitted, 50 MHz is assumed.
	 */
	घड़ी_freq = 50000000;
	clk = devm_clk_get(&pdev->dev, "ref_clk");
	अगर (!IS_ERR(clk)) अणु
		अगर (clk_prepare_enable(clk) == 0) अणु
			घड़ी_freq = clk_get_rate(clk);
			clk_disable_unprepare(clk);
		पूर्ण अन्यथा
			dev_warn(&pdev->dev, "could not enable ref_clk\n");
	पूर्ण
	hw->घड़ी_freq = घड़ी_freq;

	/* Initialize all CS bits to high. */
	hw->cs_reg = JCORE_SPI_CTRL_CS_BITS;
	jcore_spi_baudrate(hw, 400000);

	/* Register our spi controller */
	err = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (err)
		जाओ निकास;

	वापस 0;

निकास_busy:
	err = -EBUSY;
निकास:
	spi_master_put(master);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id jcore_spi_of_match[] = अणु
	अणु .compatible = "jcore,spi2" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jcore_spi_of_match);

अटल काष्ठा platक्रमm_driver jcore_spi_driver = अणु
	.probe = jcore_spi_probe,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = jcore_spi_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jcore_spi_driver);

MODULE_DESCRIPTION("J-Core SPI driver");
MODULE_AUTHOR("Rich Felker <dalias@libc.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
