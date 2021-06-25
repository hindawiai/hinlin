<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Driver क्रम Amlogic Meson SPI flash controller (SPIFC)
//
// Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
//

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>

/* रेजिस्टर map */
#घोषणा REG_CMD			0x00
#घोषणा REG_ADDR		0x04
#घोषणा REG_CTRL		0x08
#घोषणा REG_CTRL1		0x0c
#घोषणा REG_STATUS		0x10
#घोषणा REG_CTRL2		0x14
#घोषणा REG_CLOCK		0x18
#घोषणा REG_USER		0x1c
#घोषणा REG_USER1		0x20
#घोषणा REG_USER2		0x24
#घोषणा REG_USER3		0x28
#घोषणा REG_USER4		0x2c
#घोषणा REG_SLAVE		0x30
#घोषणा REG_SLAVE1		0x34
#घोषणा REG_SLAVE2		0x38
#घोषणा REG_SLAVE3		0x3c
#घोषणा REG_C0			0x40
#घोषणा REG_B8			0x60
#घोषणा REG_MAX			0x7c

/* रेजिस्टर fields */
#घोषणा CMD_USER		BIT(18)
#घोषणा CTRL_ENABLE_AHB		BIT(17)
#घोषणा CLOCK_SOURCE		BIT(31)
#घोषणा CLOCK_DIV_SHIFT		12
#घोषणा CLOCK_DIV_MASK		(0x3f << CLOCK_DIV_SHIFT)
#घोषणा CLOCK_CNT_HIGH_SHIFT	6
#घोषणा CLOCK_CNT_HIGH_MASK	(0x3f << CLOCK_CNT_HIGH_SHIFT)
#घोषणा CLOCK_CNT_LOW_SHIFT	0
#घोषणा CLOCK_CNT_LOW_MASK	(0x3f << CLOCK_CNT_LOW_SHIFT)
#घोषणा USER_DIN_EN_MS		BIT(0)
#घोषणा USER_CMP_MODE		BIT(2)
#घोषणा USER_UC_DOUT_SEL	BIT(27)
#घोषणा USER_UC_DIN_SEL		BIT(28)
#घोषणा USER_UC_MASK		((BIT(5) - 1) << 27)
#घोषणा USER1_BN_UC_DOUT_SHIFT	17
#घोषणा USER1_BN_UC_DOUT_MASK	(0xff << 16)
#घोषणा USER1_BN_UC_DIN_SHIFT	8
#घोषणा USER1_BN_UC_DIN_MASK	(0xff << 8)
#घोषणा USER4_CS_ACT		BIT(30)
#घोषणा SLAVE_TRST_DONE		BIT(4)
#घोषणा SLAVE_OP_MODE		BIT(30)
#घोषणा SLAVE_SW_RST		BIT(31)

#घोषणा SPIFC_BUFFER_SIZE	64

/**
 * काष्ठा meson_spअगरc
 * @master:	the SPI master
 * @regmap:	regmap क्रम device रेजिस्टरs
 * @clk:	input घड़ी of the built-in baud rate generator
 * @dev:	the device काष्ठाure
 */
काष्ठा meson_spअगरc अणु
	काष्ठा spi_master *master;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	काष्ठा device *dev;
पूर्ण;

अटल स्थिर काष्ठा regmap_config spअगरc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = REG_MAX,
पूर्ण;

/**
 * meson_spअगरc_रुको_पढ़ोy() - रुको क्रम the current operation to terminate
 * @spअगरc:	the Meson SPI device
 * Return:	0 on success, a negative value on error
 */
अटल पूर्णांक meson_spअगरc_रुको_पढ़ोy(काष्ठा meson_spअगरc *spअगरc)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + msecs_to_jअगरfies(5);
	u32 data;

	करो अणु
		regmap_पढ़ो(spअगरc->regmap, REG_SLAVE, &data);
		अगर (data & SLAVE_TRST_DONE)
			वापस 0;
		cond_resched();
	पूर्ण जबतक (!समय_after(jअगरfies, deadline));

	वापस -ETIMEDOUT;
पूर्ण

/**
 * meson_spअगरc_drain_buffer() - copy data from device buffer to memory
 * @spअगरc:	the Meson SPI device
 * @buf:	the destination buffer
 * @len:	number of bytes to copy
 */
अटल व्योम meson_spअगरc_drain_buffer(काष्ठा meson_spअगरc *spअगरc, u8 *buf,
				     पूर्णांक len)
अणु
	u32 data;
	पूर्णांक i = 0;

	जबतक (i < len) अणु
		regmap_पढ़ो(spअगरc->regmap, REG_C0 + i, &data);

		अगर (len - i >= 4) अणु
			*((u32 *)buf) = data;
			buf += 4;
		पूर्ण अन्यथा अणु
			स_नकल(buf, &data, len - i);
			अवरोध;
		पूर्ण
		i += 4;
	पूर्ण
पूर्ण

/**
 * meson_spअगरc_fill_buffer() - copy data from memory to device buffer
 * @spअगरc:	the Meson SPI device
 * @buf:	the source buffer
 * @len:	number of bytes to copy
 */
अटल व्योम meson_spअगरc_fill_buffer(काष्ठा meson_spअगरc *spअगरc, स्थिर u8 *buf,
				    पूर्णांक len)
अणु
	u32 data;
	पूर्णांक i = 0;

	जबतक (i < len) अणु
		अगर (len - i >= 4)
			data = *(u32 *)buf;
		अन्यथा
			स_नकल(&data, buf, len - i);

		regmap_ग_लिखो(spअगरc->regmap, REG_C0 + i, data);

		buf += 4;
		i += 4;
	पूर्ण
पूर्ण

/**
 * meson_spअगरc_setup_speed() - program the घड़ी भागider
 * @spअगरc:	the Meson SPI device
 * @speed:	desired speed in Hz
 */
अटल व्योम meson_spअगरc_setup_speed(काष्ठा meson_spअगरc *spअगरc, u32 speed)
अणु
	अचिन्हित दीर्घ parent, value;
	पूर्णांक n;

	parent = clk_get_rate(spअगरc->clk);
	n = max_t(पूर्णांक, parent / speed - 1, 1);

	dev_dbg(spअगरc->dev, "parent %lu, speed %u, n %d\n", parent,
		speed, n);

	value = (n << CLOCK_DIV_SHIFT) & CLOCK_DIV_MASK;
	value |= (n << CLOCK_CNT_LOW_SHIFT) & CLOCK_CNT_LOW_MASK;
	value |= (((n + 1) / 2 - 1) << CLOCK_CNT_HIGH_SHIFT) &
		CLOCK_CNT_HIGH_MASK;

	regmap_ग_लिखो(spअगरc->regmap, REG_CLOCK, value);
पूर्ण

/**
 * meson_spअगरc_txrx() - transfer a chunk of data
 * @spअगरc:	the Meson SPI device
 * @xfer:	the current SPI transfer
 * @offset:	offset of the data to transfer
 * @len:	length of the data to transfer
 * @last_xfer:	whether this is the last transfer of the message
 * @last_chunk:	whether this is the last chunk of the transfer
 * Return:	0 on success, a negative value on error
 */
अटल पूर्णांक meson_spअगरc_txrx(काष्ठा meson_spअगरc *spअगरc,
			    काष्ठा spi_transfer *xfer,
			    पूर्णांक offset, पूर्णांक len, bool last_xfer,
			    bool last_chunk)
अणु
	bool keep_cs = true;
	पूर्णांक ret;

	अगर (xfer->tx_buf)
		meson_spअगरc_fill_buffer(spअगरc, xfer->tx_buf + offset, len);

	/* enable DOUT stage */
	regmap_update_bits(spअगरc->regmap, REG_USER, USER_UC_MASK,
			   USER_UC_DOUT_SEL);
	regmap_ग_लिखो(spअगरc->regmap, REG_USER1,
		     (8 * len - 1) << USER1_BN_UC_DOUT_SHIFT);

	/* enable data input during DOUT */
	regmap_update_bits(spअगरc->regmap, REG_USER, USER_DIN_EN_MS,
			   USER_DIN_EN_MS);

	अगर (last_chunk) अणु
		अगर (last_xfer)
			keep_cs = xfer->cs_change;
		अन्यथा
			keep_cs = !xfer->cs_change;
	पूर्ण

	regmap_update_bits(spअगरc->regmap, REG_USER4, USER4_CS_ACT,
			   keep_cs ? USER4_CS_ACT : 0);

	/* clear transition करोne bit */
	regmap_update_bits(spअगरc->regmap, REG_SLAVE, SLAVE_TRST_DONE, 0);
	/* start transfer */
	regmap_update_bits(spअगरc->regmap, REG_CMD, CMD_USER, CMD_USER);

	ret = meson_spअगरc_रुको_पढ़ोy(spअगरc);

	अगर (!ret && xfer->rx_buf)
		meson_spअगरc_drain_buffer(spअगरc, xfer->rx_buf + offset, len);

	वापस ret;
पूर्ण

/**
 * meson_spअगरc_transfer_one() - perक्रमm a single transfer
 * @master:	the SPI master
 * @spi:	the SPI device
 * @xfer:	the current SPI transfer
 * Return:	0 on success, a negative value on error
 */
अटल पूर्णांक meson_spअगरc_transfer_one(काष्ठा spi_master *master,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा meson_spअगरc *spअगरc = spi_master_get_devdata(master);
	पूर्णांक len, करोne = 0, ret = 0;

	meson_spअगरc_setup_speed(spअगरc, xfer->speed_hz);

	regmap_update_bits(spअगरc->regmap, REG_CTRL, CTRL_ENABLE_AHB, 0);

	जबतक (करोne < xfer->len && !ret) अणु
		len = min_t(पूर्णांक, xfer->len - करोne, SPIFC_BUFFER_SIZE);
		ret = meson_spअगरc_txrx(spअगरc, xfer, करोne, len,
				       spi_transfer_is_last(master, xfer),
				       करोne + len >= xfer->len);
		करोne += len;
	पूर्ण

	regmap_update_bits(spअगरc->regmap, REG_CTRL, CTRL_ENABLE_AHB,
			   CTRL_ENABLE_AHB);

	वापस ret;
पूर्ण

/**
 * meson_spअगरc_hw_init() - reset and initialize the SPI controller
 * @spअगरc:	the Meson SPI device
 */
अटल व्योम meson_spअगरc_hw_init(काष्ठा meson_spअगरc *spअगरc)
अणु
	/* reset device */
	regmap_update_bits(spअगरc->regmap, REG_SLAVE, SLAVE_SW_RST,
			   SLAVE_SW_RST);
	/* disable compatible mode */
	regmap_update_bits(spअगरc->regmap, REG_USER, USER_CMP_MODE, 0);
	/* set master mode */
	regmap_update_bits(spअगरc->regmap, REG_SLAVE, SLAVE_OP_MODE, 0);
पूर्ण

अटल पूर्णांक meson_spअगरc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा meson_spअगरc *spअगरc;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक rate;
	पूर्णांक ret = 0;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा meson_spअगरc));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	spअगरc = spi_master_get_devdata(master);
	spअगरc->dev = &pdev->dev;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ out_err;
	पूर्ण

	spअगरc->regmap = devm_regmap_init_mmio(spअगरc->dev, base,
					      &spअगरc_regmap_config);
	अगर (IS_ERR(spअगरc->regmap)) अणु
		ret = PTR_ERR(spअगरc->regmap);
		जाओ out_err;
	पूर्ण

	spअगरc->clk = devm_clk_get(spअगरc->dev, शून्य);
	अगर (IS_ERR(spअगरc->clk)) अणु
		dev_err(spअगरc->dev, "missing clock\n");
		ret = PTR_ERR(spअगरc->clk);
		जाओ out_err;
	पूर्ण

	ret = clk_prepare_enable(spअगरc->clk);
	अगर (ret) अणु
		dev_err(spअगरc->dev, "can't prepare clock\n");
		जाओ out_err;
	पूर्ण

	rate = clk_get_rate(spअगरc->clk);

	master->num_chipselect = 1;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->स्वतः_runसमय_pm = true;
	master->transfer_one = meson_spअगरc_transfer_one;
	master->min_speed_hz = rate >> 6;
	master->max_speed_hz = rate >> 1;

	meson_spअगरc_hw_init(spअगरc);

	pm_runसमय_set_active(spअगरc->dev);
	pm_runसमय_enable(spअगरc->dev);

	ret = devm_spi_रेजिस्टर_master(spअगरc->dev, master);
	अगर (ret) अणु
		dev_err(spअगरc->dev, "failed to register spi master\n");
		जाओ out_clk;
	पूर्ण

	वापस 0;
out_clk:
	clk_disable_unprepare(spअगरc->clk);
out_err:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_spअगरc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा meson_spअगरc *spअगरc = spi_master_get_devdata(master);

	pm_runसमय_get_sync(&pdev->dev);
	clk_disable_unprepare(spअगरc->clk);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक meson_spअगरc_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा meson_spअगरc *spअगरc = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		clk_disable_unprepare(spअगरc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_spअगरc_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा meson_spअगरc *spअगरc = spi_master_get_devdata(master);
	पूर्णांक ret;

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = clk_prepare_enable(spअगरc->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	meson_spअगरc_hw_init(spअगरc);

	ret = spi_master_resume(master);
	अगर (ret)
		clk_disable_unprepare(spअगरc->clk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक meson_spअगरc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा meson_spअगरc *spअगरc = spi_master_get_devdata(master);

	clk_disable_unprepare(spअगरc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_spअगरc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा meson_spअगरc *spअगरc = spi_master_get_devdata(master);

	वापस clk_prepare_enable(spअगरc->clk);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops meson_spअगरc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(meson_spअगरc_suspend, meson_spअगरc_resume)
	SET_RUNTIME_PM_OPS(meson_spअगरc_runसमय_suspend,
			   meson_spअगरc_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_spअगरc_dt_match[] = अणु
	अणु .compatible = "amlogic,meson6-spifc", पूर्ण,
	अणु .compatible = "amlogic,meson-gxbb-spifc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_spअगरc_dt_match);

अटल काष्ठा platक्रमm_driver meson_spअगरc_driver = अणु
	.probe	= meson_spअगरc_probe,
	.हटाओ	= meson_spअगरc_हटाओ,
	.driver	= अणु
		.name		= "meson-spifc",
		.of_match_table	= of_match_ptr(meson_spअगरc_dt_match),
		.pm		= &meson_spअगरc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_spअगरc_driver);

MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_DESCRIPTION("Amlogic Meson SPIFC driver");
MODULE_LICENSE("GPL v2");
