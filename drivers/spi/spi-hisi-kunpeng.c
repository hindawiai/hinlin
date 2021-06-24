<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// HiSilicon SPI Controller Driver क्रम Kunpeng SoCs
//
// Copyright (c) 2021 HiSilicon Technologies Co., Ltd.
// Author: Jay Fang <f.fangjian@huawei.com>
//
// This code is based on spi-dw-core.c.

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

/* Register offsets */
#घोषणा HISI_SPI_CSCR		0x00	/* cs control रेजिस्टर */
#घोषणा HISI_SPI_CR		0x04	/* spi common control रेजिस्टर */
#घोषणा HISI_SPI_ENR		0x08	/* spi enable रेजिस्टर */
#घोषणा HISI_SPI_FIFOC		0x0c	/* fअगरo level control रेजिस्टर */
#घोषणा HISI_SPI_IMR		0x10	/* पूर्णांकerrupt mask रेजिस्टर */
#घोषणा HISI_SPI_DIN		0x14	/* data in रेजिस्टर */
#घोषणा HISI_SPI_DOUT		0x18	/* data out रेजिस्टर */
#घोषणा HISI_SPI_SR		0x1c	/* status रेजिस्टर */
#घोषणा HISI_SPI_RISR		0x20	/* raw पूर्णांकerrupt status रेजिस्टर */
#घोषणा HISI_SPI_ISR		0x24	/* पूर्णांकerrupt status रेजिस्टर */
#घोषणा HISI_SPI_ICR		0x28	/* पूर्णांकerrupt clear रेजिस्टर */
#घोषणा HISI_SPI_VERSION	0xe0	/* version रेजिस्टर */

/* Bit fields in HISI_SPI_CR */
#घोषणा CR_LOOP_MASK		GENMASK(1, 1)
#घोषणा CR_CPOL_MASK		GENMASK(2, 2)
#घोषणा CR_CPHA_MASK		GENMASK(3, 3)
#घोषणा CR_DIV_PRE_MASK		GENMASK(11, 4)
#घोषणा CR_DIV_POST_MASK	GENMASK(19, 12)
#घोषणा CR_BPW_MASK		GENMASK(24, 20)
#घोषणा CR_SPD_MODE_MASK	GENMASK(25, 25)

/* Bit fields in HISI_SPI_FIFOC */
#घोषणा FIFOC_TX_MASK		GENMASK(5, 3)
#घोषणा FIFOC_RX_MASK		GENMASK(11, 9)

/* Bit fields in HISI_SPI_IMR, 4 bits */
#घोषणा IMR_RXOF		BIT(0)		/* Receive Overflow */
#घोषणा IMR_RXTO		BIT(1)		/* Receive Timeout */
#घोषणा IMR_RX			BIT(2)		/* Receive */
#घोषणा IMR_TX			BIT(3)		/* Transmit */
#घोषणा IMR_MASK		(IMR_RXOF | IMR_RXTO | IMR_RX | IMR_TX)

/* Bit fields in HISI_SPI_SR, 5 bits */
#घोषणा SR_TXE			BIT(0)		/* Transmit FIFO empty */
#घोषणा SR_TXNF			BIT(1)		/* Transmit FIFO not full */
#घोषणा SR_RXNE			BIT(2)		/* Receive FIFO not empty */
#घोषणा SR_RXF			BIT(3)		/* Receive FIFO full */
#घोषणा SR_BUSY			BIT(4)		/* Busy Flag */

/* Bit fields in HISI_SPI_ISR, 4 bits */
#घोषणा ISR_RXOF		BIT(0)		/* Receive Overflow */
#घोषणा ISR_RXTO		BIT(1)		/* Receive Timeout */
#घोषणा ISR_RX			BIT(2)		/* Receive */
#घोषणा ISR_TX			BIT(3)		/* Transmit */
#घोषणा ISR_MASK		(ISR_RXOF | ISR_RXTO | ISR_RX | ISR_TX)

/* Bit fields in HISI_SPI_ICR, 2 bits */
#घोषणा ICR_RXOF		BIT(0)		/* Receive Overflow */
#घोषणा ICR_RXTO		BIT(1)		/* Receive Timeout */
#घोषणा ICR_MASK		(ICR_RXOF | ICR_RXTO)

#घोषणा DIV_POST_MAX		0xFF
#घोषणा DIV_POST_MIN		0x00
#घोषणा DIV_PRE_MAX		0xFE
#घोषणा DIV_PRE_MIN		0x02
#घोषणा CLK_DIV_MAX		((1 + DIV_POST_MAX) * DIV_PRE_MAX)
#घोषणा CLK_DIV_MIN		((1 + DIV_POST_MIN) * DIV_PRE_MIN)

#घोषणा DEFAULT_NUM_CS		1

#घोषणा HISI_SPI_WAIT_TIMEOUT_MS	10UL

क्रमागत hisi_spi_rx_level_trig अणु
	HISI_SPI_RX_1,
	HISI_SPI_RX_4,
	HISI_SPI_RX_8,
	HISI_SPI_RX_16,
	HISI_SPI_RX_32,
	HISI_SPI_RX_64,
	HISI_SPI_RX_128
पूर्ण;

क्रमागत hisi_spi_tx_level_trig अणु
	HISI_SPI_TX_1_OR_LESS,
	HISI_SPI_TX_4_OR_LESS,
	HISI_SPI_TX_8_OR_LESS,
	HISI_SPI_TX_16_OR_LESS,
	HISI_SPI_TX_32_OR_LESS,
	HISI_SPI_TX_64_OR_LESS,
	HISI_SPI_TX_128_OR_LESS
पूर्ण;

क्रमागत hisi_spi_frame_n_bytes अणु
	HISI_SPI_N_BYTES_शून्य,
	HISI_SPI_N_BYTES_U8,
	HISI_SPI_N_BYTES_U16,
	HISI_SPI_N_BYTES_U32 = 4
पूर्ण;

/* Slave spi_dev related */
काष्ठा hisi_chip_data अणु
	u32 cr;
	u32 speed_hz;	/* baud rate */
	u16 clk_भाग;	/* baud rate भागider */

	/* clk_भाग = (1 + भाग_post) * भाग_pre */
	u8 भाग_post;	/* value from 0 to 255 */
	u8 भाग_pre;	/* value from 2 to 254 (even only!) */
पूर्ण;

काष्ठा hisi_spi अणु
	काष्ठा device		*dev;

	व्योम __iomem		*regs;
	पूर्णांक			irq;
	u32			fअगरo_len; /* depth of the FIFO buffer */

	/* Current message transfer state info */
	स्थिर व्योम		*tx;
	अचिन्हित पूर्णांक		tx_len;
	व्योम			*rx;
	अचिन्हित पूर्णांक		rx_len;
	u8			n_bytes; /* current is a 1/2/4 bytes op */
पूर्ण;

अटल u32 hisi_spi_busy(काष्ठा hisi_spi *hs)
अणु
	वापस पढ़ोl(hs->regs + HISI_SPI_SR) & SR_BUSY;
पूर्ण

अटल u32 hisi_spi_rx_not_empty(काष्ठा hisi_spi *hs)
अणु
	वापस पढ़ोl(hs->regs + HISI_SPI_SR) & SR_RXNE;
पूर्ण

अटल u32 hisi_spi_tx_not_full(काष्ठा hisi_spi *hs)
अणु
	वापस पढ़ोl(hs->regs + HISI_SPI_SR) & SR_TXNF;
पूर्ण

अटल व्योम hisi_spi_flush_fअगरo(काष्ठा hisi_spi *hs)
अणु
	अचिन्हित दीर्घ limit = loops_per_jअगरfy << 1;

	करो अणु
		जबतक (hisi_spi_rx_not_empty(hs))
			पढ़ोl(hs->regs + HISI_SPI_DOUT);
	पूर्ण जबतक (hisi_spi_busy(hs) && limit--);
पूर्ण

/* Disable the controller and all पूर्णांकerrupts */
अटल व्योम hisi_spi_disable(काष्ठा hisi_spi *hs)
अणु
	ग_लिखोl(0, hs->regs + HISI_SPI_ENR);
	ग_लिखोl(IMR_MASK, hs->regs + HISI_SPI_IMR);
	ग_लिखोl(ICR_MASK, hs->regs + HISI_SPI_ICR);
पूर्ण

अटल u8 hisi_spi_n_bytes(काष्ठा spi_transfer *transfer)
अणु
	अगर (transfer->bits_per_word <= 8)
		वापस HISI_SPI_N_BYTES_U8;
	अन्यथा अगर (transfer->bits_per_word <= 16)
		वापस HISI_SPI_N_BYTES_U16;
	अन्यथा
		वापस HISI_SPI_N_BYTES_U32;
पूर्ण

अटल व्योम hisi_spi_पढ़ोer(काष्ठा hisi_spi *hs)
अणु
	u32 max = min_t(u32, hs->rx_len, hs->fअगरo_len);
	u32 rxw;

	जबतक (hisi_spi_rx_not_empty(hs) && max--) अणु
		rxw = पढ़ोl(hs->regs + HISI_SPI_DOUT);
		/* Check the transfer's original "rx" is not null */
		अगर (hs->rx) अणु
			चयन (hs->n_bytes) अणु
			हाल HISI_SPI_N_BYTES_U8:
				*(u8 *)(hs->rx) = rxw;
				अवरोध;
			हाल HISI_SPI_N_BYTES_U16:
				*(u16 *)(hs->rx) = rxw;
				अवरोध;
			हाल HISI_SPI_N_BYTES_U32:
				*(u32 *)(hs->rx) = rxw;
				अवरोध;
			पूर्ण
			hs->rx += hs->n_bytes;
		पूर्ण
		--hs->rx_len;
	पूर्ण
पूर्ण

अटल व्योम hisi_spi_ग_लिखोr(काष्ठा hisi_spi *hs)
अणु
	u32 max = min_t(u32, hs->tx_len, hs->fअगरo_len);
	u32 txw = 0;

	जबतक (hisi_spi_tx_not_full(hs) && max--) अणु
		/* Check the transfer's original "tx" is not null */
		अगर (hs->tx) अणु
			चयन (hs->n_bytes) अणु
			हाल HISI_SPI_N_BYTES_U8:
				txw = *(u8 *)(hs->tx);
				अवरोध;
			हाल HISI_SPI_N_BYTES_U16:
				txw = *(u16 *)(hs->tx);
				अवरोध;
			हाल HISI_SPI_N_BYTES_U32:
				txw = *(u32 *)(hs->tx);
				अवरोध;
			पूर्ण
			hs->tx += hs->n_bytes;
		पूर्ण
		ग_लिखोl(txw, hs->regs + HISI_SPI_DIN);
		--hs->tx_len;
	पूर्ण
पूर्ण

अटल व्योम __hisi_calc_भाग_reg(काष्ठा hisi_chip_data *chip)
अणु
	chip->भाग_pre = DIV_PRE_MAX;
	जबतक (chip->भाग_pre >= DIV_PRE_MIN) अणु
		अगर (chip->clk_भाग % chip->भाग_pre == 0)
			अवरोध;

		chip->भाग_pre -= 2;
	पूर्ण

	अगर (chip->भाग_pre > chip->clk_भाग)
		chip->भाग_pre = chip->clk_भाग;

	chip->भाग_post = (chip->clk_भाग / chip->भाग_pre) - 1;
पूर्ण

अटल u32 hisi_calc_effective_speed(काष्ठा spi_controller *master,
			काष्ठा hisi_chip_data *chip, u32 speed_hz)
अणु
	u32 effective_speed;

	/* Note घड़ी भागider करोesn't support odd numbers */
	chip->clk_भाग = DIV_ROUND_UP(master->max_speed_hz, speed_hz) + 1;
	chip->clk_भाग &= 0xfffe;
	अगर (chip->clk_भाग > CLK_DIV_MAX)
		chip->clk_भाग = CLK_DIV_MAX;

	effective_speed = master->max_speed_hz / chip->clk_भाग;
	अगर (chip->speed_hz != effective_speed) अणु
		__hisi_calc_भाग_reg(chip);
		chip->speed_hz = effective_speed;
	पूर्ण

	वापस effective_speed;
पूर्ण

अटल u32 hisi_spi_prepare_cr(काष्ठा spi_device *spi)
अणु
	u32 cr = FIELD_PREP(CR_SPD_MODE_MASK, 1);

	cr |= FIELD_PREP(CR_CPHA_MASK, (spi->mode & SPI_CPHA) ? 1 : 0);
	cr |= FIELD_PREP(CR_CPOL_MASK, (spi->mode & SPI_CPOL) ? 1 : 0);
	cr |= FIELD_PREP(CR_LOOP_MASK, (spi->mode & SPI_LOOP) ? 1 : 0);

	वापस cr;
पूर्ण

अटल व्योम hisi_spi_hw_init(काष्ठा hisi_spi *hs)
अणु
	hisi_spi_disable(hs);

	/* FIFO शेष config */
	ग_लिखोl(FIELD_PREP(FIFOC_TX_MASK, HISI_SPI_TX_64_OR_LESS) |
		FIELD_PREP(FIFOC_RX_MASK, HISI_SPI_RX_16),
		hs->regs + HISI_SPI_FIFOC);

	hs->fअगरo_len = 256;
पूर्ण

अटल irqवापस_t hisi_spi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_controller *master = dev_id;
	काष्ठा hisi_spi *hs = spi_controller_get_devdata(master);
	u32 irq_status = पढ़ोl(hs->regs + HISI_SPI_ISR) & ISR_MASK;

	अगर (!irq_status)
		वापस IRQ_NONE;

	अगर (!master->cur_msg)
		वापस IRQ_HANDLED;

	/* Error handling */
	अगर (irq_status & ISR_RXOF) अणु
		dev_err(hs->dev, "interrupt_transfer: fifo overflow\n");
		master->cur_msg->status = -EIO;
		जाओ finalize_transfer;
	पूर्ण

	/*
	 * Read data from the Rx FIFO every समय. If there is
	 * nothing left to receive, finalize the transfer.
	 */
	hisi_spi_पढ़ोer(hs);
	अगर (!hs->rx_len)
		जाओ finalize_transfer;

	/* Send data out when Tx FIFO IRQ triggered */
	अगर (irq_status & ISR_TX)
		hisi_spi_ग_लिखोr(hs);

	वापस IRQ_HANDLED;

finalize_transfer:
	hisi_spi_disable(hs);
	spi_finalize_current_transfer(master);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hisi_spi_transfer_one(काष्ठा spi_controller *master,
		काष्ठा spi_device *spi, काष्ठा spi_transfer *transfer)
अणु
	काष्ठा hisi_spi *hs = spi_controller_get_devdata(master);
	काष्ठा hisi_chip_data *chip = spi_get_ctldata(spi);
	u32 cr = chip->cr;

	/* Update per transfer options क्रम speed and bpw */
	transfer->effective_speed_hz =
		hisi_calc_effective_speed(master, chip, transfer->speed_hz);
	cr |= FIELD_PREP(CR_DIV_PRE_MASK, chip->भाग_pre);
	cr |= FIELD_PREP(CR_DIV_POST_MASK, chip->भाग_post);
	cr |= FIELD_PREP(CR_BPW_MASK, transfer->bits_per_word - 1);
	ग_लिखोl(cr, hs->regs + HISI_SPI_CR);

	hisi_spi_flush_fअगरo(hs);

	hs->n_bytes = hisi_spi_n_bytes(transfer);
	hs->tx = transfer->tx_buf;
	hs->tx_len = transfer->len / hs->n_bytes;
	hs->rx = transfer->rx_buf;
	hs->rx_len = hs->tx_len;

	/*
	 * Ensure that the transfer data above has been updated
	 * beक्रमe the पूर्णांकerrupt to start.
	 */
	smp_mb();

	/* Enable all पूर्णांकerrupts and the controller */
	ग_लिखोl(~(u32)IMR_MASK, hs->regs + HISI_SPI_IMR);
	ग_लिखोl(1, hs->regs + HISI_SPI_ENR);

	वापस 1;
पूर्ण

अटल व्योम hisi_spi_handle_err(काष्ठा spi_controller *master,
		काष्ठा spi_message *msg)
अणु
	काष्ठा hisi_spi *hs = spi_controller_get_devdata(master);

	hisi_spi_disable(hs);

	/*
	 * Wait क्रम पूर्णांकerrupt handler that is
	 * alपढ़ोy in समयout to complete.
	 */
	msleep(HISI_SPI_WAIT_TIMEOUT_MS);
पूर्ण

अटल पूर्णांक hisi_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा hisi_chip_data *chip;

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	अगर (!chip) अणु
		chip = kzalloc(माप(*chip), GFP_KERNEL);
		अगर (!chip)
			वापस -ENOMEM;
		spi_set_ctldata(spi, chip);
	पूर्ण

	chip->cr = hisi_spi_prepare_cr(spi);

	वापस 0;
पूर्ण

अटल व्योम hisi_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा hisi_chip_data *chip = spi_get_ctldata(spi);

	kमुक्त(chip);
	spi_set_ctldata(spi, शून्य);
पूर्ण

अटल पूर्णांक hisi_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_controller *master;
	काष्ठा hisi_spi *hs;
	पूर्णांक ret, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	master = devm_spi_alloc_master(dev, माप(*hs));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	hs = spi_controller_get_devdata(master);
	hs->dev = dev;
	hs->irq = irq;

	hs->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hs->regs))
		वापस PTR_ERR(hs->regs);

	/* Specअगरy maximum SPI घड़ीing speed (master only) by firmware */
	ret = device_property_पढ़ो_u32(dev, "spi-max-frequency",
					&master->max_speed_hz);
	अगर (ret) अणु
		dev_err(dev, "failed to get max SPI clocking speed, ret=%d\n",
			ret);
		वापस -EINVAL;
	पूर्ण

	ret = device_property_पढ़ो_u16(dev, "num-cs",
					&master->num_chipselect);
	अगर (ret)
		master->num_chipselect = DEFAULT_NUM_CS;

	master->use_gpio_descriptors = true;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LOOP;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	master->bus_num = pdev->id;
	master->setup = hisi_spi_setup;
	master->cleanup = hisi_spi_cleanup;
	master->transfer_one = hisi_spi_transfer_one;
	master->handle_err = hisi_spi_handle_err;
	master->dev.fwnode = dev->fwnode;

	hisi_spi_hw_init(hs);

	ret = devm_request_irq(dev, hs->irq, hisi_spi_irq, 0, dev_name(dev),
			master);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get IRQ=%d, ret=%d\n", hs->irq, ret);
		वापस ret;
	पूर्ण

	ret = spi_रेजिस्टर_controller(master);
	अगर (ret) अणु
		dev_err(dev, "failed to register spi master, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "hw version:0x%x max-freq:%u kHz\n",
		पढ़ोl(hs->regs + HISI_SPI_VERSION),
		master->max_speed_hz / 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *master = platक्रमm_get_drvdata(pdev);

	spi_unरेजिस्टर_controller(master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_spi_acpi_match[] = अणु
	अणु"HISI03E1", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_spi_acpi_match);

अटल काष्ठा platक्रमm_driver hisi_spi_driver = अणु
	.probe		= hisi_spi_probe,
	.हटाओ		= hisi_spi_हटाओ,
	.driver		= अणु
		.name	= "hisi-kunpeng-spi",
		.acpi_match_table = hisi_spi_acpi_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hisi_spi_driver);

MODULE_AUTHOR("Jay Fang <f.fangjian@huawei.com>");
MODULE_DESCRIPTION("HiSilicon SPI Controller Driver for Kunpeng SoCs");
MODULE_LICENSE("GPL v2");
