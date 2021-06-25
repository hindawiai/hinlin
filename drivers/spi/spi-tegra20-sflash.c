<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI driver क्रम Nvidia's Tegra20 Serial Flash Controller.
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/spi/spi.h>

#घोषणा SPI_COMMAND				0x000
#घोषणा SPI_GO					BIT(30)
#घोषणा SPI_M_S					BIT(28)
#घोषणा SPI_ACTIVE_SCLK_MASK			(0x3 << 26)
#घोषणा SPI_ACTIVE_SCLK_DRIVE_LOW		(0 << 26)
#घोषणा SPI_ACTIVE_SCLK_DRIVE_HIGH		(1 << 26)
#घोषणा SPI_ACTIVE_SCLK_PULL_LOW		(2 << 26)
#घोषणा SPI_ACTIVE_SCLK_PULL_HIGH		(3 << 26)

#घोषणा SPI_CK_SDA_FALLING			(1 << 21)
#घोषणा SPI_CK_SDA_RISING			(0 << 21)
#घोषणा SPI_CK_SDA_MASK				(1 << 21)
#घोषणा SPI_ACTIVE_SDA				(0x3 << 18)
#घोषणा SPI_ACTIVE_SDA_DRIVE_LOW		(0 << 18)
#घोषणा SPI_ACTIVE_SDA_DRIVE_HIGH		(1 << 18)
#घोषणा SPI_ACTIVE_SDA_PULL_LOW			(2 << 18)
#घोषणा SPI_ACTIVE_SDA_PULL_HIGH		(3 << 18)

#घोषणा SPI_CS_POL_INVERT			BIT(16)
#घोषणा SPI_TX_EN				BIT(15)
#घोषणा SPI_RX_EN				BIT(14)
#घोषणा SPI_CS_VAL_HIGH				BIT(13)
#घोषणा SPI_CS_VAL_LOW				0x0
#घोषणा SPI_CS_SW				BIT(12)
#घोषणा SPI_CS_HW				0x0
#घोषणा SPI_CS_DELAY_MASK			(7 << 9)
#घोषणा SPI_CS3_EN				BIT(8)
#घोषणा SPI_CS2_EN				BIT(7)
#घोषणा SPI_CS1_EN				BIT(6)
#घोषणा SPI_CS0_EN				BIT(5)

#घोषणा SPI_CS_MASK			(SPI_CS3_EN | SPI_CS2_EN |	\
					SPI_CS1_EN | SPI_CS0_EN)
#घोषणा SPI_BIT_LENGTH(x)		(((x) & 0x1f) << 0)

#घोषणा SPI_MODES			(SPI_ACTIVE_SCLK_MASK | SPI_CK_SDA_MASK)

#घोषणा SPI_STATUS			0x004
#घोषणा SPI_BSY				BIT(31)
#घोषणा SPI_RDY				BIT(30)
#घोषणा SPI_TXF_FLUSH			BIT(29)
#घोषणा SPI_RXF_FLUSH			BIT(28)
#घोषणा SPI_RX_UNF			BIT(27)
#घोषणा SPI_TX_OVF			BIT(26)
#घोषणा SPI_RXF_EMPTY			BIT(25)
#घोषणा SPI_RXF_FULL			BIT(24)
#घोषणा SPI_TXF_EMPTY			BIT(23)
#घोषणा SPI_TXF_FULL			BIT(22)
#घोषणा SPI_BLK_CNT(count)		(((count) & 0xffff) + 1)

#घोषणा SPI_FIFO_ERROR			(SPI_RX_UNF | SPI_TX_OVF)
#घोषणा SPI_FIFO_EMPTY			(SPI_TX_EMPTY | SPI_RX_EMPTY)

#घोषणा SPI_RX_CMP			0x8
#घोषणा SPI_DMA_CTL			0x0C
#घोषणा SPI_DMA_EN			BIT(31)
#घोषणा SPI_IE_RXC			BIT(27)
#घोषणा SPI_IE_TXC			BIT(26)
#घोषणा SPI_PACKED			BIT(20)
#घोषणा SPI_RX_TRIG_MASK		(0x3 << 18)
#घोषणा SPI_RX_TRIG_1W			(0x0 << 18)
#घोषणा SPI_RX_TRIG_4W			(0x1 << 18)
#घोषणा SPI_TX_TRIG_MASK		(0x3 << 16)
#घोषणा SPI_TX_TRIG_1W			(0x0 << 16)
#घोषणा SPI_TX_TRIG_4W			(0x1 << 16)
#घोषणा SPI_DMA_BLK_COUNT(count)	(((count) - 1) & 0xFFFF)

#घोषणा SPI_TX_FIFO			0x10
#घोषणा SPI_RX_FIFO			0x20

#घोषणा DATA_सूची_TX			(1 << 0)
#घोषणा DATA_सूची_RX			(1 << 1)

#घोषणा MAX_CHIP_SELECT			4
#घोषणा SPI_FIFO_DEPTH			4
#घोषणा SPI_DMA_TIMEOUT               (msecs_to_jअगरfies(1000))

काष्ठा tegra_sflash_data अणु
	काष्ठा device				*dev;
	काष्ठा spi_master			*master;
	spinlock_t				lock;

	काष्ठा clk				*clk;
	काष्ठा reset_control			*rst;
	व्योम __iomem				*base;
	अचिन्हित				irq;
	u32					cur_speed;

	काष्ठा spi_device			*cur_spi;
	अचिन्हित				cur_pos;
	अचिन्हित				cur_len;
	अचिन्हित				bytes_per_word;
	अचिन्हित				cur_direction;
	अचिन्हित				curr_xfer_words;

	अचिन्हित				cur_rx_pos;
	अचिन्हित				cur_tx_pos;

	u32					tx_status;
	u32					rx_status;
	u32					status_reg;

	u32					def_command_reg;
	u32					command_reg;
	u32					dma_control_reg;

	काष्ठा completion			xfer_completion;
	काष्ठा spi_transfer			*curr_xfer;
पूर्ण;

अटल पूर्णांक tegra_sflash_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक tegra_sflash_runसमय_resume(काष्ठा device *dev);

अटल अंतरभूत u32 tegra_sflash_पढ़ोl(काष्ठा tegra_sflash_data *tsd,
		अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(tsd->base + reg);
पूर्ण

अटल अंतरभूत व्योम tegra_sflash_ग_लिखोl(काष्ठा tegra_sflash_data *tsd,
		u32 val, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोl(val, tsd->base + reg);
पूर्ण

अटल व्योम tegra_sflash_clear_status(काष्ठा tegra_sflash_data *tsd)
अणु
	/* Write 1 to clear status रेजिस्टर */
	tegra_sflash_ग_लिखोl(tsd, SPI_RDY | SPI_FIFO_ERROR, SPI_STATUS);
पूर्ण

अटल अचिन्हित tegra_sflash_calculate_curr_xfer_param(
	काष्ठा spi_device *spi, काष्ठा tegra_sflash_data *tsd,
	काष्ठा spi_transfer *t)
अणु
	अचिन्हित reमुख्य_len = t->len - tsd->cur_pos;
	अचिन्हित max_word;

	tsd->bytes_per_word = DIV_ROUND_UP(t->bits_per_word, 8);
	max_word = reमुख्य_len / tsd->bytes_per_word;
	अगर (max_word > SPI_FIFO_DEPTH)
		max_word = SPI_FIFO_DEPTH;
	tsd->curr_xfer_words = max_word;
	वापस max_word;
पूर्ण

अटल अचिन्हित tegra_sflash_fill_tx_fअगरo_from_client_txbuf(
	काष्ठा tegra_sflash_data *tsd, काष्ठा spi_transfer *t)
अणु
	अचिन्हित nbytes;
	u32 status;
	अचिन्हित max_n_32bit = tsd->curr_xfer_words;
	u8 *tx_buf = (u8 *)t->tx_buf + tsd->cur_tx_pos;

	अगर (max_n_32bit > SPI_FIFO_DEPTH)
		max_n_32bit = SPI_FIFO_DEPTH;
	nbytes = max_n_32bit * tsd->bytes_per_word;

	status = tegra_sflash_पढ़ोl(tsd, SPI_STATUS);
	जबतक (!(status & SPI_TXF_FULL)) अणु
		पूर्णांक i;
		u32 x = 0;

		क्रम (i = 0; nbytes && (i < tsd->bytes_per_word);
							i++, nbytes--)
			x |= (u32)(*tx_buf++) << (i * 8);
		tegra_sflash_ग_लिखोl(tsd, x, SPI_TX_FIFO);
		अगर (!nbytes)
			अवरोध;

		status = tegra_sflash_पढ़ोl(tsd, SPI_STATUS);
	पूर्ण
	tsd->cur_tx_pos += max_n_32bit * tsd->bytes_per_word;
	वापस max_n_32bit;
पूर्ण

अटल पूर्णांक tegra_sflash_पढ़ो_rx_fअगरo_to_client_rxbuf(
		काष्ठा tegra_sflash_data *tsd, काष्ठा spi_transfer *t)
अणु
	u32 status;
	अचिन्हित पूर्णांक पढ़ो_words = 0;
	u8 *rx_buf = (u8 *)t->rx_buf + tsd->cur_rx_pos;

	status = tegra_sflash_पढ़ोl(tsd, SPI_STATUS);
	जबतक (!(status & SPI_RXF_EMPTY)) अणु
		पूर्णांक i;
		u32 x = tegra_sflash_पढ़ोl(tsd, SPI_RX_FIFO);

		क्रम (i = 0; (i < tsd->bytes_per_word); i++)
			*rx_buf++ = (x >> (i*8)) & 0xFF;
		पढ़ो_words++;
		status = tegra_sflash_पढ़ोl(tsd, SPI_STATUS);
	पूर्ण
	tsd->cur_rx_pos += पढ़ो_words * tsd->bytes_per_word;
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sflash_start_cpu_based_transfer(
		काष्ठा tegra_sflash_data *tsd, काष्ठा spi_transfer *t)
अणु
	u32 val = 0;
	अचिन्हित cur_words;

	अगर (tsd->cur_direction & DATA_सूची_TX)
		val |= SPI_IE_TXC;

	अगर (tsd->cur_direction & DATA_सूची_RX)
		val |= SPI_IE_RXC;

	tegra_sflash_ग_लिखोl(tsd, val, SPI_DMA_CTL);
	tsd->dma_control_reg = val;

	अगर (tsd->cur_direction & DATA_सूची_TX)
		cur_words = tegra_sflash_fill_tx_fअगरo_from_client_txbuf(tsd, t);
	अन्यथा
		cur_words = tsd->curr_xfer_words;
	val |= SPI_DMA_BLK_COUNT(cur_words);
	tegra_sflash_ग_लिखोl(tsd, val, SPI_DMA_CTL);
	tsd->dma_control_reg = val;
	val |= SPI_DMA_EN;
	tegra_sflash_ग_लिखोl(tsd, val, SPI_DMA_CTL);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sflash_start_transfer_one(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t, bool is_first_of_msg,
		bool is_single_xfer)
अणु
	काष्ठा tegra_sflash_data *tsd = spi_master_get_devdata(spi->master);
	u32 speed;
	u32 command;

	speed = t->speed_hz;
	अगर (speed != tsd->cur_speed) अणु
		clk_set_rate(tsd->clk, speed);
		tsd->cur_speed = speed;
	पूर्ण

	tsd->cur_spi = spi;
	tsd->cur_pos = 0;
	tsd->cur_rx_pos = 0;
	tsd->cur_tx_pos = 0;
	tsd->curr_xfer = t;
	tegra_sflash_calculate_curr_xfer_param(spi, tsd, t);
	अगर (is_first_of_msg) अणु
		command = tsd->def_command_reg;
		command |= SPI_BIT_LENGTH(t->bits_per_word - 1);
		command |= SPI_CS_VAL_HIGH;

		command &= ~SPI_MODES;
		अगर (spi->mode & SPI_CPHA)
			command |= SPI_CK_SDA_FALLING;

		अगर (spi->mode & SPI_CPOL)
			command |= SPI_ACTIVE_SCLK_DRIVE_HIGH;
		अन्यथा
			command |= SPI_ACTIVE_SCLK_DRIVE_LOW;
		command |= SPI_CS0_EN << spi->chip_select;
	पूर्ण अन्यथा अणु
		command = tsd->command_reg;
		command &= ~SPI_BIT_LENGTH(~0);
		command |= SPI_BIT_LENGTH(t->bits_per_word - 1);
		command &= ~(SPI_RX_EN | SPI_TX_EN);
	पूर्ण

	tsd->cur_direction = 0;
	अगर (t->rx_buf) अणु
		command |= SPI_RX_EN;
		tsd->cur_direction |= DATA_सूची_RX;
	पूर्ण
	अगर (t->tx_buf) अणु
		command |= SPI_TX_EN;
		tsd->cur_direction |= DATA_सूची_TX;
	पूर्ण
	tegra_sflash_ग_लिखोl(tsd, command, SPI_COMMAND);
	tsd->command_reg = command;

	वापस tegra_sflash_start_cpu_based_transfer(tsd, t);
पूर्ण

अटल पूर्णांक tegra_sflash_transfer_one_message(काष्ठा spi_master *master,
			काष्ठा spi_message *msg)
अणु
	bool is_first_msg = true;
	पूर्णांक single_xfer;
	काष्ठा tegra_sflash_data *tsd = spi_master_get_devdata(master);
	काष्ठा spi_transfer *xfer;
	काष्ठा spi_device *spi = msg->spi;
	पूर्णांक ret;

	msg->status = 0;
	msg->actual_length = 0;
	single_xfer = list_is_singular(&msg->transfers);
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		reinit_completion(&tsd->xfer_completion);
		ret = tegra_sflash_start_transfer_one(spi, xfer,
					is_first_msg, single_xfer);
		अगर (ret < 0) अणु
			dev_err(tsd->dev,
				"spi can not start transfer, err %d\n", ret);
			जाओ निकास;
		पूर्ण
		is_first_msg = false;
		ret = रुको_क्रम_completion_समयout(&tsd->xfer_completion,
						SPI_DMA_TIMEOUT);
		अगर (WARN_ON(ret == 0)) अणु
			dev_err(tsd->dev,
				"spi transfer timeout, err %d\n", ret);
			ret = -EIO;
			जाओ निकास;
		पूर्ण

		अगर (tsd->tx_status ||  tsd->rx_status) अणु
			dev_err(tsd->dev, "Error in Transfer\n");
			ret = -EIO;
			जाओ निकास;
		पूर्ण
		msg->actual_length += xfer->len;
		अगर (xfer->cs_change && xfer->delay.value) अणु
			tegra_sflash_ग_लिखोl(tsd, tsd->def_command_reg,
					SPI_COMMAND);
			spi_transfer_delay_exec(xfer);
		पूर्ण
	पूर्ण
	ret = 0;
निकास:
	tegra_sflash_ग_लिखोl(tsd, tsd->def_command_reg, SPI_COMMAND);
	msg->status = ret;
	spi_finalize_current_message(master);
	वापस ret;
पूर्ण

अटल irqवापस_t handle_cpu_based_xfer(काष्ठा tegra_sflash_data *tsd)
अणु
	काष्ठा spi_transfer *t = tsd->curr_xfer;

	spin_lock(&tsd->lock);
	अगर (tsd->tx_status || tsd->rx_status || (tsd->status_reg & SPI_BSY)) अणु
		dev_err(tsd->dev,
			"CpuXfer ERROR bit set 0x%x\n", tsd->status_reg);
		dev_err(tsd->dev,
			"CpuXfer 0x%08x:0x%08x\n", tsd->command_reg,
				tsd->dma_control_reg);
		reset_control_निश्चित(tsd->rst);
		udelay(2);
		reset_control_deनिश्चित(tsd->rst);
		complete(&tsd->xfer_completion);
		जाओ निकास;
	पूर्ण

	अगर (tsd->cur_direction & DATA_सूची_RX)
		tegra_sflash_पढ़ो_rx_fअगरo_to_client_rxbuf(tsd, t);

	अगर (tsd->cur_direction & DATA_सूची_TX)
		tsd->cur_pos = tsd->cur_tx_pos;
	अन्यथा
		tsd->cur_pos = tsd->cur_rx_pos;

	अगर (tsd->cur_pos == t->len) अणु
		complete(&tsd->xfer_completion);
		जाओ निकास;
	पूर्ण

	tegra_sflash_calculate_curr_xfer_param(tsd->cur_spi, tsd, t);
	tegra_sflash_start_cpu_based_transfer(tsd, t);
निकास:
	spin_unlock(&tsd->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_sflash_isr(पूर्णांक irq, व्योम *context_data)
अणु
	काष्ठा tegra_sflash_data *tsd = context_data;

	tsd->status_reg = tegra_sflash_पढ़ोl(tsd, SPI_STATUS);
	अगर (tsd->cur_direction & DATA_सूची_TX)
		tsd->tx_status = tsd->status_reg & SPI_TX_OVF;

	अगर (tsd->cur_direction & DATA_सूची_RX)
		tsd->rx_status = tsd->status_reg & SPI_RX_UNF;
	tegra_sflash_clear_status(tsd);

	वापस handle_cpu_based_xfer(tsd);
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_sflash_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-sflash", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_sflash_of_match);

अटल पूर्णांक tegra_sflash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master;
	काष्ठा tegra_sflash_data	*tsd;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(tegra_sflash_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण

	master = spi_alloc_master(&pdev->dev, माप(*tsd));
	अगर (!master) अणु
		dev_err(&pdev->dev, "master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA;
	master->transfer_one_message = tegra_sflash_transfer_one_message;
	master->स्वतः_runसमय_pm = true;
	master->num_chipselect = MAX_CHIP_SELECT;

	platक्रमm_set_drvdata(pdev, master);
	tsd = spi_master_get_devdata(master);
	tsd->master = master;
	tsd->dev = &pdev->dev;
	spin_lock_init(&tsd->lock);

	अगर (of_property_पढ़ो_u32(tsd->dev->of_node, "spi-max-frequency",
				 &master->max_speed_hz))
		master->max_speed_hz = 25000000; /* 25MHz */

	tsd->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tsd->base)) अणु
		ret = PTR_ERR(tsd->base);
		जाओ निकास_मुक्त_master;
	पूर्ण

	tsd->irq = platक्रमm_get_irq(pdev, 0);
	ret = request_irq(tsd->irq, tegra_sflash_isr, 0,
			dev_name(&pdev->dev), tsd);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register ISR for IRQ %d\n",
					tsd->irq);
		जाओ निकास_मुक्त_master;
	पूर्ण

	tsd->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tsd->clk)) अणु
		dev_err(&pdev->dev, "can not get clock\n");
		ret = PTR_ERR(tsd->clk);
		जाओ निकास_मुक्त_irq;
	पूर्ण

	tsd->rst = devm_reset_control_get_exclusive(&pdev->dev, "spi");
	अगर (IS_ERR(tsd->rst)) अणु
		dev_err(&pdev->dev, "can not get reset\n");
		ret = PTR_ERR(tsd->rst);
		जाओ निकास_मुक्त_irq;
	पूर्ण

	init_completion(&tsd->xfer_completion);
	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = tegra_sflash_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ निकास_pm_disable;
	पूर्ण

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pm runtime get failed, e = %d\n", ret);
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ निकास_pm_disable;
	पूर्ण

	/* Reset controller */
	reset_control_निश्चित(tsd->rst);
	udelay(2);
	reset_control_deनिश्चित(tsd->rst);

	tsd->def_command_reg  = SPI_M_S | SPI_CS_SW;
	tegra_sflash_ग_लिखोl(tsd, tsd->def_command_reg, SPI_COMMAND);
	pm_runसमय_put(&pdev->dev);

	master->dev.of_node = pdev->dev.of_node;
	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can not register to master err %d\n", ret);
		जाओ निकास_pm_disable;
	पूर्ण
	वापस ret;

निकास_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_sflash_runसमय_suspend(&pdev->dev);
निकास_मुक्त_irq:
	मुक्त_irq(tsd->irq, tsd);
निकास_मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_sflash_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा tegra_sflash_data	*tsd = spi_master_get_devdata(master);

	मुक्त_irq(tsd->irq, tsd);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_sflash_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_sflash_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);

	वापस spi_master_suspend(master);
पूर्ण

अटल पूर्णांक tegra_sflash_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_sflash_data *tsd = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		dev_err(dev, "pm runtime failed, e = %d\n", ret);
		वापस ret;
	पूर्ण
	tegra_sflash_ग_लिखोl(tsd, tsd->command_reg, SPI_COMMAND);
	pm_runसमय_put(dev);

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tegra_sflash_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_sflash_data *tsd = spi_master_get_devdata(master);

	/* Flush all ग_लिखो which are in PPSB queue by पढ़ोing back */
	tegra_sflash_पढ़ोl(tsd, SPI_COMMAND);

	clk_disable_unprepare(tsd->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sflash_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_sflash_data *tsd = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(tsd->clk);
	अगर (ret < 0) अणु
		dev_err(tsd->dev, "clk_prepare failed: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops slink_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_sflash_runसमय_suspend,
		tegra_sflash_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_sflash_suspend, tegra_sflash_resume)
पूर्ण;
अटल काष्ठा platक्रमm_driver tegra_sflash_driver = अणु
	.driver = अणु
		.name		= "spi-tegra-sflash",
		.pm		= &slink_pm_ops,
		.of_match_table	= tegra_sflash_of_match,
	पूर्ण,
	.probe =	tegra_sflash_probe,
	.हटाओ =	tegra_sflash_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_sflash_driver);

MODULE_ALIAS("platform:spi-tegra-sflash");
MODULE_DESCRIPTION("NVIDIA Tegra20 Serial Flash Controller Driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
