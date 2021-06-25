<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Altera SPI driver
 *
 * Copyright (C) 2008 Thomas Chou <thomas@wytron.com.tw>
 *
 * Based on spi_s3c24xx.c, which is:
 * Copyright (c) 2006 Ben Dooks
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/altera.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#घोषणा DRV_NAME "spi_altera"

#घोषणा ALTERA_SPI_RXDATA	0
#घोषणा ALTERA_SPI_TXDATA	4
#घोषणा ALTERA_SPI_STATUS	8
#घोषणा ALTERA_SPI_CONTROL	12
#घोषणा ALTERA_SPI_SLAVE_SEL	20

#घोषणा ALTERA_SPI_STATUS_ROE_MSK	0x8
#घोषणा ALTERA_SPI_STATUS_TOE_MSK	0x10
#घोषणा ALTERA_SPI_STATUS_TMT_MSK	0x20
#घोषणा ALTERA_SPI_STATUS_TRDY_MSK	0x40
#घोषणा ALTERA_SPI_STATUS_RRDY_MSK	0x80
#घोषणा ALTERA_SPI_STATUS_E_MSK		0x100

#घोषणा ALTERA_SPI_CONTROL_IROE_MSK	0x8
#घोषणा ALTERA_SPI_CONTROL_ITOE_MSK	0x10
#घोषणा ALTERA_SPI_CONTROL_ITRDY_MSK	0x40
#घोषणा ALTERA_SPI_CONTROL_IRRDY_MSK	0x80
#घोषणा ALTERA_SPI_CONTROL_IE_MSK	0x100
#घोषणा ALTERA_SPI_CONTROL_SSO_MSK	0x400

अटल पूर्णांक altr_spi_ग_लिखोl(काष्ठा altera_spi *hw, अचिन्हित पूर्णांक reg,
			   अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(hw->regmap, hw->regoff + reg, val);
	अगर (ret)
		dev_err(hw->dev, "fail to write reg 0x%x val 0x%x: %d\n",
			reg, val, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक altr_spi_पढ़ोl(काष्ठा altera_spi *hw, अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = regmap_पढ़ो(hw->regmap, hw->regoff + reg, val);
	अगर (ret)
		dev_err(hw->dev, "fail to read reg 0x%x: %d\n", reg, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा altera_spi *altera_spi_to_hw(काष्ठा spi_device *sdev)
अणु
	वापस spi_master_get_devdata(sdev->master);
पूर्ण

अटल व्योम altera_spi_set_cs(काष्ठा spi_device *spi, bool is_high)
अणु
	काष्ठा altera_spi *hw = altera_spi_to_hw(spi);

	अगर (is_high) अणु
		hw->imr &= ~ALTERA_SPI_CONTROL_SSO_MSK;
		altr_spi_ग_लिखोl(hw, ALTERA_SPI_CONTROL, hw->imr);
		altr_spi_ग_लिखोl(hw, ALTERA_SPI_SLAVE_SEL, 0);
	पूर्ण अन्यथा अणु
		altr_spi_ग_लिखोl(hw, ALTERA_SPI_SLAVE_SEL,
				BIT(spi->chip_select));
		hw->imr |= ALTERA_SPI_CONTROL_SSO_MSK;
		altr_spi_ग_लिखोl(hw, ALTERA_SPI_CONTROL, hw->imr);
	पूर्ण
पूर्ण

अटल व्योम altera_spi_tx_word(काष्ठा altera_spi *hw)
अणु
	अचिन्हित पूर्णांक txd = 0;

	अगर (hw->tx) अणु
		चयन (hw->bytes_per_word) अणु
		हाल 1:
			txd = hw->tx[hw->count];
			अवरोध;
		हाल 2:
			txd = (hw->tx[hw->count * 2]
				| (hw->tx[hw->count * 2 + 1] << 8));
			अवरोध;
		हाल 4:
			txd = (hw->tx[hw->count * 4]
				| (hw->tx[hw->count * 4 + 1] << 8)
				| (hw->tx[hw->count * 4 + 2] << 16)
				| (hw->tx[hw->count * 4 + 3] << 24));
			अवरोध;

		पूर्ण
	पूर्ण

	altr_spi_ग_लिखोl(hw, ALTERA_SPI_TXDATA, txd);
पूर्ण

अटल व्योम altera_spi_rx_word(काष्ठा altera_spi *hw)
अणु
	अचिन्हित पूर्णांक rxd;

	altr_spi_पढ़ोl(hw, ALTERA_SPI_RXDATA, &rxd);
	अगर (hw->rx) अणु
		चयन (hw->bytes_per_word) अणु
		हाल 1:
			hw->rx[hw->count] = rxd;
			अवरोध;
		हाल 2:
			hw->rx[hw->count * 2] = rxd;
			hw->rx[hw->count * 2 + 1] = rxd >> 8;
			अवरोध;
		हाल 4:
			hw->rx[hw->count * 4] = rxd;
			hw->rx[hw->count * 4 + 1] = rxd >> 8;
			hw->rx[hw->count * 4 + 2] = rxd >> 16;
			hw->rx[hw->count * 4 + 3] = rxd >> 24;
			अवरोध;

		पूर्ण
	पूर्ण

	hw->count++;
पूर्ण

अटल पूर्णांक altera_spi_txrx(काष्ठा spi_master *master,
	काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा altera_spi *hw = spi_master_get_devdata(master);
	u32 val;

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->count = 0;
	hw->bytes_per_word = DIV_ROUND_UP(t->bits_per_word, 8);
	hw->len = t->len / hw->bytes_per_word;

	अगर (hw->irq >= 0) अणु
		/* enable receive पूर्णांकerrupt */
		hw->imr |= ALTERA_SPI_CONTROL_IRRDY_MSK;
		altr_spi_ग_लिखोl(hw, ALTERA_SPI_CONTROL, hw->imr);

		/* send the first byte */
		altera_spi_tx_word(hw);

		वापस 1;
	पूर्ण

	जबतक (hw->count < hw->len) अणु
		altera_spi_tx_word(hw);

		क्रम (;;) अणु
			altr_spi_पढ़ोl(hw, ALTERA_SPI_STATUS, &val);
			अगर (val & ALTERA_SPI_STATUS_RRDY_MSK)
				अवरोध;

			cpu_relax();
		पूर्ण

		altera_spi_rx_word(hw);
	पूर्ण
	spi_finalize_current_transfer(master);

	वापस 0;
पूर्ण

irqवापस_t altera_spi_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा spi_master *master = dev;
	काष्ठा altera_spi *hw = spi_master_get_devdata(master);

	altera_spi_rx_word(hw);

	अगर (hw->count < hw->len) अणु
		altera_spi_tx_word(hw);
	पूर्ण अन्यथा अणु
		/* disable receive पूर्णांकerrupt */
		hw->imr &= ~ALTERA_SPI_CONTROL_IRRDY_MSK;
		altr_spi_ग_लिखोl(hw, ALTERA_SPI_CONTROL, hw->imr);

		spi_finalize_current_transfer(master);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(altera_spi_irq);

व्योम altera_spi_init_master(काष्ठा spi_master *master)
अणु
	काष्ठा altera_spi *hw = spi_master_get_devdata(master);
	u32 val;

	master->transfer_one = altera_spi_txrx;
	master->set_cs = altera_spi_set_cs;

	/* program शेषs पूर्णांकo the रेजिस्टरs */
	hw->imr = 0;		/* disable spi पूर्णांकerrupts */
	altr_spi_ग_लिखोl(hw, ALTERA_SPI_CONTROL, hw->imr);
	altr_spi_ग_लिखोl(hw, ALTERA_SPI_STATUS, 0);	/* clear status reg */
	altr_spi_पढ़ोl(hw, ALTERA_SPI_STATUS, &val);
	अगर (val & ALTERA_SPI_STATUS_RRDY_MSK)
		altr_spi_पढ़ोl(hw, ALTERA_SPI_RXDATA, &val); /* flush rxdata */
पूर्ण
EXPORT_SYMBOL_GPL(altera_spi_init_master);

MODULE_LICENSE("GPL");
