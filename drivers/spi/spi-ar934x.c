<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// SPI controller driver क्रम Qualcomm Atheros AR934x/QCA95xx SoCs
//
// Copyright (C) 2020 Chuanhong Guo <gch981213@gmail.com>
//
// Based on spi-mt7621.c:
// Copyright (C) 2011 Sergiy <piratfm@gmail.com>
// Copyright (C) 2011-2013 Gabor Juhos <juhosg@खोलोwrt.org>
// Copyright (C) 2014-2015 Felix Fietkau <nbd@nbd.name>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRIVER_NAME "spi-ar934x"

#घोषणा AR934X_SPI_REG_FS		0x00
#घोषणा AR934X_SPI_ENABLE		BIT(0)

#घोषणा AR934X_SPI_REG_IOC		0x08
#घोषणा AR934X_SPI_IOC_INITVAL		0x70000

#घोषणा AR934X_SPI_REG_CTRL		0x04
#घोषणा AR934X_SPI_CLK_MASK		GENMASK(5, 0)

#घोषणा AR934X_SPI_DATAOUT		0x10

#घोषणा AR934X_SPI_REG_SHIFT_CTRL	0x14
#घोषणा AR934X_SPI_SHIFT_EN		BIT(31)
#घोषणा AR934X_SPI_SHIFT_CS(n)		BIT(28 + (n))
#घोषणा AR934X_SPI_SHIFT_TERM		26
#घोषणा AR934X_SPI_SHIFT_VAL(cs, term, count)			\
	(AR934X_SPI_SHIFT_EN | AR934X_SPI_SHIFT_CS(cs) |	\
	(term) << AR934X_SPI_SHIFT_TERM | (count))

#घोषणा AR934X_SPI_DATAIN 0x18

काष्ठा ar934x_spi अणु
	काष्ठा spi_controller *ctlr;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक clk_freq;
पूर्ण;

अटल अंतरभूत पूर्णांक ar934x_spi_clk_भाग(काष्ठा ar934x_spi *sp, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक भाग = DIV_ROUND_UP(sp->clk_freq, freq * 2) - 1;

	अगर (भाग < 0)
		वापस 0;
	अन्यथा अगर (भाग > AR934X_SPI_CLK_MASK)
		वापस -EINVAL;
	अन्यथा
		वापस भाग;
पूर्ण

अटल पूर्णांक ar934x_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा ar934x_spi *sp = spi_controller_get_devdata(spi->master);

	अगर ((spi->max_speed_hz == 0) ||
	    (spi->max_speed_hz > (sp->clk_freq / 2))) अणु
		spi->max_speed_hz = sp->clk_freq / 2;
	पूर्ण अन्यथा अगर (spi->max_speed_hz < (sp->clk_freq / 128)) अणु
		dev_err(&spi->dev, "spi clock is too low\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ar934x_spi_transfer_one_message(काष्ठा spi_controller *master,
					   काष्ठा spi_message *m)
अणु
	काष्ठा ar934x_spi *sp = spi_controller_get_devdata(master);
	काष्ठा spi_transfer *t = शून्य;
	काष्ठा spi_device *spi = m->spi;
	अचिन्हित दीर्घ trx_करोne, trx_cur;
	पूर्णांक stat = 0;
	u8 term = 0;
	पूर्णांक भाग, i;
	u32 reg;
	स्थिर u8 *tx_buf;
	u8 *buf;

	m->actual_length = 0;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (t->speed_hz)
			भाग = ar934x_spi_clk_भाग(sp, t->speed_hz);
		अन्यथा
			भाग = ar934x_spi_clk_भाग(sp, spi->max_speed_hz);
		अगर (भाग < 0) अणु
			stat = -EIO;
			जाओ msg_करोne;
		पूर्ण

		reg = ioपढ़ो32(sp->base + AR934X_SPI_REG_CTRL);
		reg &= ~AR934X_SPI_CLK_MASK;
		reg |= भाग;
		ioग_लिखो32(reg, sp->base + AR934X_SPI_REG_CTRL);
		ioग_लिखो32(0, sp->base + AR934X_SPI_DATAOUT);

		क्रम (trx_करोne = 0; trx_करोne < t->len; trx_करोne += 4) अणु
			trx_cur = t->len - trx_करोne;
			अगर (trx_cur > 4)
				trx_cur = 4;
			अन्यथा अगर (list_is_last(&t->transfer_list, &m->transfers))
				term = 1;

			अगर (t->tx_buf) अणु
				tx_buf = t->tx_buf + trx_करोne;
				reg = tx_buf[0];
				क्रम (i = 1; i < trx_cur; i++)
					reg = reg << 8 | tx_buf[i];
				ioग_लिखो32(reg, sp->base + AR934X_SPI_DATAOUT);
			पूर्ण

			reg = AR934X_SPI_SHIFT_VAL(spi->chip_select, term,
						   trx_cur * 8);
			ioग_लिखो32(reg, sp->base + AR934X_SPI_REG_SHIFT_CTRL);
			stat = पढ़ोl_poll_समयout(
				sp->base + AR934X_SPI_REG_SHIFT_CTRL, reg,
				!(reg & AR934X_SPI_SHIFT_EN), 0, 5);
			अगर (stat < 0)
				जाओ msg_करोne;

			अगर (t->rx_buf) अणु
				reg = ioपढ़ो32(sp->base + AR934X_SPI_DATAIN);
				buf = t->rx_buf + trx_करोne;
				क्रम (i = 0; i < trx_cur; i++) अणु
					buf[trx_cur - i - 1] = reg & 0xff;
					reg >>= 8;
				पूर्ण
			पूर्ण
		पूर्ण
		m->actual_length += t->len;
	पूर्ण

msg_करोne:
	m->status = stat;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ar934x_spi_match[] = अणु
	अणु .compatible = "qca,ar934x-spi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ar934x_spi_match);

अटल पूर्णांक ar934x_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा ar934x_spi *sp;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	पूर्णांक ret;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	ctlr = devm_spi_alloc_master(&pdev->dev, माप(*sp));
	अगर (!ctlr) अणु
		dev_info(&pdev->dev, "failed to allocate spi controller\n");
		ret = -ENOMEM;
		जाओ err_clk_disable;
	पूर्ण

	/* disable flash mapping and expose spi controller रेजिस्टरs */
	ioग_लिखो32(AR934X_SPI_ENABLE, base + AR934X_SPI_REG_FS);
	/* restore pins to शेष state: CSn=1 DO=CLK=0 */
	ioग_लिखो32(AR934X_SPI_IOC_INITVAL, base + AR934X_SPI_REG_IOC);

	ctlr->mode_bits = SPI_LSB_FIRST;
	ctlr->setup = ar934x_spi_setup;
	ctlr->transfer_one_message = ar934x_spi_transfer_one_message;
	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->num_chipselect = 3;

	dev_set_drvdata(&pdev->dev, ctlr);

	sp = spi_controller_get_devdata(ctlr);
	sp->base = base;
	sp->clk = clk;
	sp->clk_freq = clk_get_rate(clk);
	sp->ctlr = ctlr;

	ret = spi_रेजिस्टर_controller(ctlr);
	अगर (!ret)
		वापस 0;

err_clk_disable:
	clk_disable_unprepare(clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ar934x_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा ar934x_spi *sp;

	ctlr = dev_get_drvdata(&pdev->dev);
	sp = spi_controller_get_devdata(ctlr);

	spi_unरेजिस्टर_controller(ctlr);
	clk_disable_unprepare(sp->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ar934x_spi_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = ar934x_spi_match,
	पूर्ण,
	.probe = ar934x_spi_probe,
	.हटाओ = ar934x_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(ar934x_spi_driver);

MODULE_DESCRIPTION("SPI controller driver for Qualcomm Atheros AR934x/QCA95xx");
MODULE_AUTHOR("Chuanhong Guo <gch981213@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
