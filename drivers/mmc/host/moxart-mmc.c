<शैली गुरु>
/*
 * MOXA ART MMC host driver.
 *
 * Copyright (C) 2014 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * Based on code from
 * Moxa Technologies Co., Ltd. <www.moxa.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/sched.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/spinlock.h>

#घोषणा REG_COMMAND		0
#घोषणा REG_ARGUMENT		4
#घोषणा REG_RESPONSE0		8
#घोषणा REG_RESPONSE1		12
#घोषणा REG_RESPONSE2		16
#घोषणा REG_RESPONSE3		20
#घोषणा REG_RESPONSE_COMMAND	24
#घोषणा REG_DATA_CONTROL	28
#घोषणा REG_DATA_TIMER		32
#घोषणा REG_DATA_LENGTH		36
#घोषणा REG_STATUS		40
#घोषणा REG_CLEAR		44
#घोषणा REG_INTERRUPT_MASK	48
#घोषणा REG_POWER_CONTROL	52
#घोषणा REG_CLOCK_CONTROL	56
#घोषणा REG_BUS_WIDTH		60
#घोषणा REG_DATA_WINDOW		64
#घोषणा REG_FEATURE		68
#घोषणा REG_REVISION		72

/* REG_COMMAND */
#घोषणा CMD_SDC_RESET		BIT(10)
#घोषणा CMD_EN			BIT(9)
#घोषणा CMD_APP_CMD		BIT(8)
#घोषणा CMD_LONG_RSP		BIT(7)
#घोषणा CMD_NEED_RSP		BIT(6)
#घोषणा CMD_IDX_MASK		0x3f

/* REG_RESPONSE_COMMAND */
#घोषणा RSP_CMD_APP		BIT(6)
#घोषणा RSP_CMD_IDX_MASK	0x3f

/* REG_DATA_CONTROL */
#घोषणा DCR_DATA_FIFO_RESET     BIT(8)
#घोषणा DCR_DATA_THRES          BIT(7)
#घोषणा DCR_DATA_EN		BIT(6)
#घोषणा DCR_DMA_EN		BIT(5)
#घोषणा DCR_DATA_WRITE		BIT(4)
#घोषणा DCR_BLK_SIZE		0x0f

/* REG_DATA_LENGTH */
#घोषणा DATA_LEN_MASK		0xffffff

/* REG_STATUS */
#घोषणा WRITE_PROT		BIT(12)
#घोषणा CARD_DETECT		BIT(11)
/* 1-10 below can be sent to either रेजिस्टरs, पूर्णांकerrupt or clear. */
#घोषणा CARD_CHANGE		BIT(10)
#घोषणा FIFO_ORUN		BIT(9)
#घोषणा FIFO_URUN		BIT(8)
#घोषणा DATA_END		BIT(7)
#घोषणा CMD_SENT		BIT(6)
#घोषणा DATA_CRC_OK		BIT(5)
#घोषणा RSP_CRC_OK		BIT(4)
#घोषणा DATA_TIMEOUT		BIT(3)
#घोषणा RSP_TIMEOUT		BIT(2)
#घोषणा DATA_CRC_FAIL		BIT(1)
#घोषणा RSP_CRC_FAIL		BIT(0)

#घोषणा MASK_RSP		(RSP_TIMEOUT | RSP_CRC_FAIL | \
				 RSP_CRC_OK  | CARD_DETECT  | CMD_SENT)

#घोषणा MASK_DATA		(DATA_CRC_OK   | DATA_END | \
				 DATA_CRC_FAIL | DATA_TIMEOUT)

#घोषणा MASK_INTR_PIO		(FIFO_URUN | FIFO_ORUN | CARD_CHANGE)

/* REG_POWER_CONTROL */
#घोषणा SD_POWER_ON		BIT(4)
#घोषणा SD_POWER_MASK		0x0f

/* REG_CLOCK_CONTROL */
#घोषणा CLK_HISPD		BIT(9)
#घोषणा CLK_OFF			BIT(8)
#घोषणा CLK_SD			BIT(7)
#घोषणा CLK_DIV_MASK		0x7f

/* REG_BUS_WIDTH */
#घोषणा BUS_WIDTH_8		BIT(2)
#घोषणा BUS_WIDTH_4		BIT(1)
#घोषणा BUS_WIDTH_1		BIT(0)

#घोषणा MMC_VDD_360		23
#घोषणा MIN_POWER		(MMC_VDD_360 - SD_POWER_MASK)
#घोषणा MAX_RETRIES		500000

काष्ठा moxart_host अणु
	spinlock_t			lock;

	व्योम __iomem			*base;

	phys_addr_t			reg_phys;

	काष्ठा dma_chan			*dma_chan_tx;
	काष्ठा dma_chan                 *dma_chan_rx;
	काष्ठा dma_async_tx_descriptor	*tx_desc;
	काष्ठा mmc_host			*mmc;
	काष्ठा mmc_request		*mrq;
	काष्ठा scatterlist		*cur_sg;
	काष्ठा completion		dma_complete;
	काष्ठा completion		pio_complete;

	u32				num_sg;
	u32				data_reमुख्य;
	u32				data_len;
	u32				fअगरo_width;
	u32				समयout;
	u32				rate;

	दीर्घ				sysclk;

	bool				have_dma;
	bool				is_हटाओd;
पूर्ण;

अटल अंतरभूत व्योम moxart_init_sg(काष्ठा moxart_host *host,
				  काष्ठा mmc_data *data)
अणु
	host->cur_sg = data->sg;
	host->num_sg = data->sg_len;
	host->data_reमुख्य = host->cur_sg->length;

	अगर (host->data_reमुख्य > host->data_len)
		host->data_reमुख्य = host->data_len;
पूर्ण

अटल अंतरभूत पूर्णांक moxart_next_sg(काष्ठा moxart_host *host)
अणु
	पूर्णांक reमुख्य;
	काष्ठा mmc_data *data = host->mrq->cmd->data;

	host->cur_sg++;
	host->num_sg--;

	अगर (host->num_sg > 0) अणु
		host->data_reमुख्य = host->cur_sg->length;
		reमुख्य = host->data_len - data->bytes_xfered;
		अगर (reमुख्य > 0 && reमुख्य < host->data_reमुख्य)
			host->data_reमुख्य = reमुख्य;
	पूर्ण

	वापस host->num_sg;
पूर्ण

अटल पूर्णांक moxart_रुको_क्रम_status(काष्ठा moxart_host *host,
				  u32 mask, u32 *status)
अणु
	पूर्णांक ret = -ETIMEDOUT;
	u32 i;

	क्रम (i = 0; i < MAX_RETRIES; i++) अणु
		*status = पढ़ोl(host->base + REG_STATUS);
		अगर (!(*status & mask)) अणु
			udelay(5);
			जारी;
		पूर्ण
		ग_लिखोl(*status & mask, host->base + REG_CLEAR);
		ret = 0;
		अवरोध;
	पूर्ण

	अगर (ret)
		dev_err(mmc_dev(host->mmc), "timed out waiting for status\n");

	वापस ret;
पूर्ण


अटल व्योम moxart_send_command(काष्ठा moxart_host *host,
	काष्ठा mmc_command *cmd)
अणु
	u32 status, cmdctrl;

	ग_लिखोl(RSP_TIMEOUT  | RSP_CRC_OK |
	       RSP_CRC_FAIL | CMD_SENT, host->base + REG_CLEAR);
	ग_लिखोl(cmd->arg, host->base + REG_ARGUMENT);

	cmdctrl = cmd->opcode & CMD_IDX_MASK;
	अगर (cmdctrl == SD_APP_SET_BUS_WIDTH    || cmdctrl == SD_APP_OP_COND   ||
	    cmdctrl == SD_APP_SEND_SCR         || cmdctrl == SD_APP_SD_STATUS ||
	    cmdctrl == SD_APP_SEND_NUM_WR_BLKS)
		cmdctrl |= CMD_APP_CMD;

	अगर (cmd->flags & MMC_RSP_PRESENT)
		cmdctrl |= CMD_NEED_RSP;

	अगर (cmd->flags & MMC_RSP_136)
		cmdctrl |= CMD_LONG_RSP;

	ग_लिखोl(cmdctrl | CMD_EN, host->base + REG_COMMAND);

	अगर (moxart_रुको_क्रम_status(host, MASK_RSP, &status) == -ETIMEDOUT)
		cmd->error = -ETIMEDOUT;

	अगर (status & RSP_TIMEOUT) अणु
		cmd->error = -ETIMEDOUT;
		वापस;
	पूर्ण
	अगर (status & RSP_CRC_FAIL) अणु
		cmd->error = -EIO;
		वापस;
	पूर्ण
	अगर (status & RSP_CRC_OK) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			cmd->resp[3] = पढ़ोl(host->base + REG_RESPONSE0);
			cmd->resp[2] = पढ़ोl(host->base + REG_RESPONSE1);
			cmd->resp[1] = पढ़ोl(host->base + REG_RESPONSE2);
			cmd->resp[0] = पढ़ोl(host->base + REG_RESPONSE3);
		पूर्ण अन्यथा अणु
			cmd->resp[0] = पढ़ोl(host->base + REG_RESPONSE0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम moxart_dma_complete(व्योम *param)
अणु
	काष्ठा moxart_host *host = param;

	complete(&host->dma_complete);
पूर्ण

अटल व्योम moxart_transfer_dma(काष्ठा mmc_data *data, काष्ठा moxart_host *host)
अणु
	u32 len, dir_slave;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *dma_chan;

	अगर (host->data_len == data->bytes_xfered)
		वापस;

	अगर (data->flags & MMC_DATA_WRITE) अणु
		dma_chan = host->dma_chan_tx;
		dir_slave = DMA_MEM_TO_DEV;
	पूर्ण अन्यथा अणु
		dma_chan = host->dma_chan_rx;
		dir_slave = DMA_DEV_TO_MEM;
	पूर्ण

	len = dma_map_sg(dma_chan->device->dev, data->sg,
			 data->sg_len, mmc_get_dma_dir(data));

	अगर (len > 0) अणु
		desc = dmaengine_prep_slave_sg(dma_chan, data->sg,
					       len, dir_slave,
					       DMA_PREP_INTERRUPT |
					       DMA_CTRL_ACK);
	पूर्ण अन्यथा अणु
		dev_err(mmc_dev(host->mmc), "dma_map_sg returned zero length\n");
	पूर्ण

	अगर (desc) अणु
		host->tx_desc = desc;
		desc->callback = moxart_dma_complete;
		desc->callback_param = host;
		dmaengine_submit(desc);
		dma_async_issue_pending(dma_chan);
	पूर्ण

	data->bytes_xfered += host->data_reमुख्य;

	रुको_क्रम_completion_पूर्णांकerruptible_समयout(&host->dma_complete,
						  host->समयout);

	dma_unmap_sg(dma_chan->device->dev,
		     data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
पूर्ण


अटल व्योम moxart_transfer_pio(काष्ठा moxart_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->cmd->data;
	u32 *sgp, len = 0, reमुख्य, status;

	अगर (host->data_len == data->bytes_xfered)
		वापस;

	sgp = sg_virt(host->cur_sg);
	reमुख्य = host->data_reमुख्य;

	अगर (data->flags & MMC_DATA_WRITE) अणु
		जबतक (reमुख्य > 0) अणु
			अगर (moxart_रुको_क्रम_status(host, FIFO_URUN, &status)
			     == -ETIMEDOUT) अणु
				data->error = -ETIMEDOUT;
				complete(&host->pio_complete);
				वापस;
			पूर्ण
			क्रम (len = 0; len < reमुख्य && len < host->fअगरo_width;) अणु
				ioग_लिखो32(*sgp, host->base + REG_DATA_WINDOW);
				sgp++;
				len += 4;
			पूर्ण
			reमुख्य -= len;
		पूर्ण

	पूर्ण अन्यथा अणु
		जबतक (reमुख्य > 0) अणु
			अगर (moxart_रुको_क्रम_status(host, FIFO_ORUN, &status)
			    == -ETIMEDOUT) अणु
				data->error = -ETIMEDOUT;
				complete(&host->pio_complete);
				वापस;
			पूर्ण
			क्रम (len = 0; len < reमुख्य && len < host->fअगरo_width;) अणु
				/* SCR data must be पढ़ो in big endian. */
				अगर (data->mrq->cmd->opcode == SD_APP_SEND_SCR)
					*sgp = ioपढ़ो32be(host->base +
							  REG_DATA_WINDOW);
				अन्यथा
					*sgp = ioपढ़ो32(host->base +
							REG_DATA_WINDOW);
				sgp++;
				len += 4;
			पूर्ण
			reमुख्य -= len;
		पूर्ण
	पूर्ण

	data->bytes_xfered += host->data_reमुख्य - reमुख्य;
	host->data_reमुख्य = reमुख्य;

	अगर (host->data_len != data->bytes_xfered)
		moxart_next_sg(host);
	अन्यथा
		complete(&host->pio_complete);
पूर्ण

अटल व्योम moxart_prepare_data(काष्ठा moxart_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->cmd->data;
	u32 datactrl;
	पूर्णांक blksz_bits;

	अगर (!data)
		वापस;

	host->data_len = data->blocks * data->blksz;
	blksz_bits = ffs(data->blksz) - 1;
	BUG_ON(1 << blksz_bits != data->blksz);

	moxart_init_sg(host, data);

	datactrl = DCR_DATA_EN | (blksz_bits & DCR_BLK_SIZE);

	अगर (data->flags & MMC_DATA_WRITE)
		datactrl |= DCR_DATA_WRITE;

	अगर ((host->data_len > host->fअगरo_width) && host->have_dma)
		datactrl |= DCR_DMA_EN;

	ग_लिखोl(DCR_DATA_FIFO_RESET, host->base + REG_DATA_CONTROL);
	ग_लिखोl(MASK_DATA | FIFO_URUN | FIFO_ORUN, host->base + REG_CLEAR);
	ग_लिखोl(host->rate, host->base + REG_DATA_TIMER);
	ग_लिखोl(host->data_len, host->base + REG_DATA_LENGTH);
	ग_लिखोl(datactrl, host->base + REG_DATA_CONTROL);
पूर्ण

अटल व्योम moxart_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा moxart_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u32 status;

	spin_lock_irqsave(&host->lock, flags);

	init_completion(&host->dma_complete);
	init_completion(&host->pio_complete);

	host->mrq = mrq;

	अगर (पढ़ोl(host->base + REG_STATUS) & CARD_DETECT) अणु
		mrq->cmd->error = -ETIMEDOUT;
		जाओ request_करोne;
	पूर्ण

	moxart_prepare_data(host);
	moxart_send_command(host, host->mrq->cmd);

	अगर (mrq->cmd->data) अणु
		अगर ((host->data_len > host->fअगरo_width) && host->have_dma) अणु

			ग_लिखोl(CARD_CHANGE, host->base + REG_INTERRUPT_MASK);

			spin_unlock_irqrestore(&host->lock, flags);

			moxart_transfer_dma(mrq->cmd->data, host);

			spin_lock_irqsave(&host->lock, flags);
		पूर्ण अन्यथा अणु

			ग_लिखोl(MASK_INTR_PIO, host->base + REG_INTERRUPT_MASK);

			spin_unlock_irqrestore(&host->lock, flags);

			/* PIO transfers start from पूर्णांकerrupt. */
			रुको_क्रम_completion_पूर्णांकerruptible_समयout(&host->pio_complete,
								  host->समयout);

			spin_lock_irqsave(&host->lock, flags);
		पूर्ण

		अगर (host->is_हटाओd) अणु
			dev_err(mmc_dev(host->mmc), "card removed\n");
			mrq->cmd->error = -ETIMEDOUT;
			जाओ request_करोne;
		पूर्ण

		अगर (moxart_रुको_क्रम_status(host, MASK_DATA, &status)
		    == -ETIMEDOUT) अणु
			mrq->cmd->data->error = -ETIMEDOUT;
			जाओ request_करोne;
		पूर्ण

		अगर (status & DATA_CRC_FAIL)
			mrq->cmd->data->error = -ETIMEDOUT;

		अगर (mrq->cmd->data->stop)
			moxart_send_command(host, mrq->cmd->data->stop);
	पूर्ण

request_करोne:
	spin_unlock_irqrestore(&host->lock, flags);
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल irqवापस_t moxart_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा moxart_host *host = (काष्ठा moxart_host *)devid;
	u32 status;

	spin_lock(&host->lock);

	status = पढ़ोl(host->base + REG_STATUS);
	अगर (status & CARD_CHANGE) अणु
		host->is_हटाओd = status & CARD_DETECT;
		अगर (host->is_हटाओd && host->have_dma) अणु
			dmaengine_terminate_all(host->dma_chan_tx);
			dmaengine_terminate_all(host->dma_chan_rx);
		पूर्ण
		host->mrq = शून्य;
		ग_लिखोl(MASK_INTR_PIO, host->base + REG_CLEAR);
		ग_लिखोl(CARD_CHANGE, host->base + REG_INTERRUPT_MASK);
		mmc_detect_change(host->mmc, 0);
	पूर्ण
	अगर (status & (FIFO_ORUN | FIFO_URUN) && host->mrq)
		moxart_transfer_pio(host);

	spin_unlock(&host->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम moxart_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा moxart_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u8 घातer, भाग;
	u32 ctrl;

	spin_lock_irqsave(&host->lock, flags);

	अगर (ios->घड़ी) अणु
		क्रम (भाग = 0; भाग < CLK_DIV_MASK; ++भाग) अणु
			अगर (ios->घड़ी >= host->sysclk / (2 * (भाग + 1)))
				अवरोध;
		पूर्ण
		ctrl = CLK_SD | भाग;
		host->rate = host->sysclk / (2 * (भाग + 1));
		अगर (host->rate > host->sysclk)
			ctrl |= CLK_HISPD;
		ग_लिखोl(ctrl, host->base + REG_CLOCK_CONTROL);
	पूर्ण

	अगर (ios->घातer_mode == MMC_POWER_OFF) अणु
		ग_लिखोl(पढ़ोl(host->base + REG_POWER_CONTROL) & ~SD_POWER_ON,
		       host->base + REG_POWER_CONTROL);
	पूर्ण अन्यथा अणु
		अगर (ios->vdd < MIN_POWER)
			घातer = 0;
		अन्यथा
			घातer = ios->vdd - MIN_POWER;

		ग_लिखोl(SD_POWER_ON | (u32) घातer,
		       host->base + REG_POWER_CONTROL);
	पूर्ण

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_4:
		ग_लिखोl(BUS_WIDTH_4, host->base + REG_BUS_WIDTH);
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		ग_लिखोl(BUS_WIDTH_8, host->base + REG_BUS_WIDTH);
		अवरोध;
	शेष:
		ग_लिखोl(BUS_WIDTH_1, host->base + REG_BUS_WIDTH);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण


अटल पूर्णांक moxart_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा moxart_host *host = mmc_priv(mmc);

	वापस !!(पढ़ोl(host->base + REG_STATUS) & WRITE_PROT);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops moxart_ops = अणु
	.request = moxart_request,
	.set_ios = moxart_set_ios,
	.get_ro = moxart_get_ro,
पूर्ण;

अटल पूर्णांक moxart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource res_mmc;
	काष्ठा mmc_host *mmc;
	काष्ठा moxart_host *host = शून्य;
	काष्ठा dma_slave_config cfg;
	काष्ठा clk *clk;
	व्योम __iomem *reg_mmc;
	पूर्णांक irq, ret;
	u32 i;

	mmc = mmc_alloc_host(माप(काष्ठा moxart_host), dev);
	अगर (!mmc) अणु
		dev_err(dev, "mmc_alloc_host failed\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = of_address_to_resource(node, 0, &res_mmc);
	अगर (ret) अणु
		dev_err(dev, "of_address_to_resource failed\n");
		जाओ out;
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		dev_err(dev, "irq_of_parse_and_map failed\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ out;
	पूर्ण

	reg_mmc = devm_ioremap_resource(dev, &res_mmc);
	अगर (IS_ERR(reg_mmc)) अणु
		ret = PTR_ERR(reg_mmc);
		जाओ out;
	पूर्ण

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ out;

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->base = reg_mmc;
	host->reg_phys = res_mmc.start;
	host->समयout = msecs_to_jअगरfies(1000);
	host->sysclk = clk_get_rate(clk);
	host->fअगरo_width = पढ़ोl(host->base + REG_FEATURE) << 2;
	host->dma_chan_tx = dma_request_chan(dev, "tx");
	host->dma_chan_rx = dma_request_chan(dev, "rx");

	spin_lock_init(&host->lock);

	mmc->ops = &moxart_ops;
	mmc->f_max = DIV_ROUND_CLOSEST(host->sysclk, 2);
	mmc->f_min = DIV_ROUND_CLOSEST(host->sysclk, CLK_DIV_MASK * 2);
	mmc->ocr_avail = 0xffff00;	/* Support 2.0v - 3.6v घातer. */

	अगर (IS_ERR(host->dma_chan_tx) || IS_ERR(host->dma_chan_rx)) अणु
		अगर (PTR_ERR(host->dma_chan_tx) == -EPROBE_DEFER ||
		    PTR_ERR(host->dma_chan_rx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ out;
		पूर्ण
		dev_dbg(dev, "PIO mode transfer enabled\n");
		host->have_dma = false;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "DMA channels found (%p,%p)\n",
			 host->dma_chan_tx, host->dma_chan_rx);
		host->have_dma = true;

		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

		cfg.direction = DMA_MEM_TO_DEV;
		cfg.src_addr = 0;
		cfg.dst_addr = host->reg_phys + REG_DATA_WINDOW;
		dmaengine_slave_config(host->dma_chan_tx, &cfg);

		cfg.direction = DMA_DEV_TO_MEM;
		cfg.src_addr = host->reg_phys + REG_DATA_WINDOW;
		cfg.dst_addr = 0;
		dmaengine_slave_config(host->dma_chan_rx, &cfg);
	पूर्ण

	चयन ((पढ़ोl(host->base + REG_BUS_WIDTH) >> 3) & 3) अणु
	हाल 1:
		mmc->caps |= MMC_CAP_4_BIT_DATA;
		अवरोध;
	हाल 2:
		mmc->caps |= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(0, host->base + REG_INTERRUPT_MASK);

	ग_लिखोl(CMD_SDC_RESET, host->base + REG_COMMAND);
	क्रम (i = 0; i < MAX_RETRIES; i++) अणु
		अगर (!(पढ़ोl(host->base + REG_COMMAND) & CMD_SDC_RESET))
			अवरोध;
		udelay(5);
	पूर्ण

	ret = devm_request_irq(dev, irq, moxart_irq, 0, "moxart-mmc", host);
	अगर (ret)
		जाओ out;

	dev_set_drvdata(dev, mmc);
	mmc_add_host(mmc);

	dev_dbg(dev, "IRQ=%d, FIFO is %d bytes\n", irq, host->fअगरo_width);

	वापस 0;

out:
	अगर (mmc)
		mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक moxart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(&pdev->dev);
	काष्ठा moxart_host *host = mmc_priv(mmc);

	dev_set_drvdata(&pdev->dev, शून्य);

	अगर (!IS_ERR(host->dma_chan_tx))
		dma_release_channel(host->dma_chan_tx);
	अगर (!IS_ERR(host->dma_chan_rx))
		dma_release_channel(host->dma_chan_rx);
	mmc_हटाओ_host(mmc);
	mmc_मुक्त_host(mmc);

	ग_लिखोl(0, host->base + REG_INTERRUPT_MASK);
	ग_लिखोl(0, host->base + REG_POWER_CONTROL);
	ग_लिखोl(पढ़ोl(host->base + REG_CLOCK_CONTROL) | CLK_OFF,
	       host->base + REG_CLOCK_CONTROL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxart_mmc_match[] = अणु
	अणु .compatible = "moxa,moxart-mmc" पूर्ण,
	अणु .compatible = "faraday,ftsdc010" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, moxart_mmc_match);

अटल काष्ठा platक्रमm_driver moxart_mmc_driver = अणु
	.probe      = moxart_probe,
	.हटाओ     = moxart_हटाओ,
	.driver     = अणु
		.name		= "mmc-moxart",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= moxart_mmc_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(moxart_mmc_driver);

MODULE_ALIAS("platform:mmc-moxart");
MODULE_DESCRIPTION("MOXA ART MMC driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jonas Jensen <jonas.jensen@gmail.com>");
