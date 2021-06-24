<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Portions copyright (C) 2003 Russell King, PXA MMCI Driver
 * Portions copyright (C) 2004-2005 Pierre Ossman, W83L51xD SD/MMC driver
 *
 * Copyright 2008 Embedded Alley Solutions, Inc.
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/mxs-dma.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/completion.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/spi/mxs-spi.h>

#घोषणा DRIVER_NAME	"mxs-mmc"

#घोषणा MXS_MMC_IRQ_BITS	(BM_SSP_CTRL1_SDIO_IRQ		| \
				 BM_SSP_CTRL1_RESP_ERR_IRQ	| \
				 BM_SSP_CTRL1_RESP_TIMEOUT_IRQ	| \
				 BM_SSP_CTRL1_DATA_TIMEOUT_IRQ	| \
				 BM_SSP_CTRL1_DATA_CRC_IRQ	| \
				 BM_SSP_CTRL1_FIFO_UNDERRUN_IRQ	| \
				 BM_SSP_CTRL1_RECV_TIMEOUT_IRQ  | \
				 BM_SSP_CTRL1_FIFO_OVERRUN_IRQ)

/* card detect polling समयout */
#घोषणा MXS_MMC_DETECT_TIMEOUT			(HZ/2)

काष्ठा mxs_mmc_host अणु
	काष्ठा mxs_ssp			ssp;

	काष्ठा mmc_host			*mmc;
	काष्ठा mmc_request		*mrq;
	काष्ठा mmc_command		*cmd;
	काष्ठा mmc_data			*data;

	अचिन्हित अक्षर			bus_width;
	spinlock_t			lock;
	पूर्णांक				sdio_irq_en;
	bool				broken_cd;
पूर्ण;

अटल पूर्णांक mxs_mmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);
	काष्ठा mxs_ssp *ssp = &host->ssp;
	पूर्णांक present, ret;

	अगर (host->broken_cd)
		वापस -ENOSYS;

	ret = mmc_gpio_get_cd(mmc);
	अगर (ret >= 0)
		वापस ret;

	present = mmc->caps & MMC_CAP_NEEDS_POLL ||
		!(पढ़ोl(ssp->base + HW_SSP_STATUS(ssp)) &
			BM_SSP_STATUS_CARD_DETECT);

	अगर (mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH)
		present = !present;

	वापस present;
पूर्ण

अटल पूर्णांक mxs_mmc_reset(काष्ठा mxs_mmc_host *host)
अणु
	काष्ठा mxs_ssp *ssp = &host->ssp;
	u32 ctrl0, ctrl1;
	पूर्णांक ret;

	ret = sपंचांगp_reset_block(ssp->base);
	अगर (ret)
		वापस ret;

	ctrl0 = BM_SSP_CTRL0_IGNORE_CRC;
	ctrl1 = BF_SSP(0x3, CTRL1_SSP_MODE) |
		BF_SSP(0x7, CTRL1_WORD_LENGTH) |
		BM_SSP_CTRL1_DMA_ENABLE |
		BM_SSP_CTRL1_POLARITY |
		BM_SSP_CTRL1_RECV_TIMEOUT_IRQ_EN |
		BM_SSP_CTRL1_DATA_CRC_IRQ_EN |
		BM_SSP_CTRL1_DATA_TIMEOUT_IRQ_EN |
		BM_SSP_CTRL1_RESP_TIMEOUT_IRQ_EN |
		BM_SSP_CTRL1_RESP_ERR_IRQ_EN;

	ग_लिखोl(BF_SSP(0xffff, TIMING_TIMEOUT) |
	       BF_SSP(2, TIMING_CLOCK_DIVIDE) |
	       BF_SSP(0, TIMING_CLOCK_RATE),
	       ssp->base + HW_SSP_TIMING(ssp));

	अगर (host->sdio_irq_en) अणु
		ctrl0 |= BM_SSP_CTRL0_SDIO_IRQ_CHECK;
		ctrl1 |= BM_SSP_CTRL1_SDIO_IRQ_EN;
	पूर्ण

	ग_लिखोl(ctrl0, ssp->base + HW_SSP_CTRL0);
	ग_लिखोl(ctrl1, ssp->base + HW_SSP_CTRL1(ssp));
	वापस 0;
पूर्ण

अटल व्योम mxs_mmc_start_cmd(काष्ठा mxs_mmc_host *host,
			      काष्ठा mmc_command *cmd);

अटल व्योम mxs_mmc_request_करोne(काष्ठा mxs_mmc_host *host)
अणु
	काष्ठा mmc_command *cmd = host->cmd;
	काष्ठा mmc_data *data = host->data;
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mxs_ssp *ssp = &host->ssp;

	अगर (mmc_resp_type(cmd) & MMC_RSP_PRESENT) अणु
		अगर (mmc_resp_type(cmd) & MMC_RSP_136) अणु
			cmd->resp[3] = पढ़ोl(ssp->base + HW_SSP_SDRESP0(ssp));
			cmd->resp[2] = पढ़ोl(ssp->base + HW_SSP_SDRESP1(ssp));
			cmd->resp[1] = पढ़ोl(ssp->base + HW_SSP_SDRESP2(ssp));
			cmd->resp[0] = पढ़ोl(ssp->base + HW_SSP_SDRESP3(ssp));
		पूर्ण अन्यथा अणु
			cmd->resp[0] = पढ़ोl(ssp->base + HW_SSP_SDRESP0(ssp));
		पूर्ण
	पूर्ण

	अगर (cmd == mrq->sbc) अणु
		/* Finished CMD23, now send actual command. */
		mxs_mmc_start_cmd(host, mrq->cmd);
		वापस;
	पूर्ण अन्यथा अगर (data) अणु
		dma_unmap_sg(mmc_dev(host->mmc), data->sg,
			     data->sg_len, ssp->dma_dir);
		/*
		 * If there was an error on any block, we mark all
		 * data blocks as being in error.
		 */
		अगर (!data->error)
			data->bytes_xfered = data->blocks * data->blksz;
		अन्यथा
			data->bytes_xfered = 0;

		host->data = शून्य;
		अगर (data->stop && (data->error || !mrq->sbc)) अणु
			mxs_mmc_start_cmd(host, mrq->stop);
			वापस;
		पूर्ण
	पूर्ण

	host->mrq = शून्य;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम mxs_mmc_dma_irq_callback(व्योम *param)
अणु
	काष्ठा mxs_mmc_host *host = param;

	mxs_mmc_request_करोne(host);
पूर्ण

अटल irqवापस_t mxs_mmc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxs_mmc_host *host = dev_id;
	काष्ठा mmc_command *cmd = host->cmd;
	काष्ठा mmc_data *data = host->data;
	काष्ठा mxs_ssp *ssp = &host->ssp;
	u32 stat;

	spin_lock(&host->lock);

	stat = पढ़ोl(ssp->base + HW_SSP_CTRL1(ssp));
	ग_लिखोl(stat & MXS_MMC_IRQ_BITS,
	       ssp->base + HW_SSP_CTRL1(ssp) + STMP_OFFSET_REG_CLR);

	spin_unlock(&host->lock);

	अगर ((stat & BM_SSP_CTRL1_SDIO_IRQ) && (stat & BM_SSP_CTRL1_SDIO_IRQ_EN))
		mmc_संकेत_sdio_irq(host->mmc);

	अगर (stat & BM_SSP_CTRL1_RESP_TIMEOUT_IRQ)
		cmd->error = -ETIMEDOUT;
	अन्यथा अगर (stat & BM_SSP_CTRL1_RESP_ERR_IRQ)
		cmd->error = -EIO;

	अगर (data) अणु
		अगर (stat & (BM_SSP_CTRL1_DATA_TIMEOUT_IRQ |
			    BM_SSP_CTRL1_RECV_TIMEOUT_IRQ))
			data->error = -ETIMEDOUT;
		अन्यथा अगर (stat & BM_SSP_CTRL1_DATA_CRC_IRQ)
			data->error = -EILSEQ;
		अन्यथा अगर (stat & (BM_SSP_CTRL1_FIFO_UNDERRUN_IRQ |
				 BM_SSP_CTRL1_FIFO_OVERRUN_IRQ))
			data->error = -EIO;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mxs_mmc_prep_dma(
	काष्ठा mxs_mmc_host *host, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mxs_ssp *ssp = &host->ssp;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा mmc_data *data = host->data;
	काष्ठा scatterlist * sgl;
	अचिन्हित पूर्णांक sg_len;

	अगर (data) अणु
		/* data */
		dma_map_sg(mmc_dev(host->mmc), data->sg,
			   data->sg_len, ssp->dma_dir);
		sgl = data->sg;
		sg_len = data->sg_len;
	पूर्ण अन्यथा अणु
		/* pio */
		sgl = (काष्ठा scatterlist *) ssp->ssp_pio_words;
		sg_len = SSP_PIO_NUM;
	पूर्ण

	desc = dmaengine_prep_slave_sg(ssp->dmach,
				sgl, sg_len, ssp->slave_dirn, flags);
	अगर (desc) अणु
		desc->callback = mxs_mmc_dma_irq_callback;
		desc->callback_param = host;
	पूर्ण अन्यथा अणु
		अगर (data)
			dma_unmap_sg(mmc_dev(host->mmc), data->sg,
				     data->sg_len, ssp->dma_dir);
	पूर्ण

	वापस desc;
पूर्ण

अटल व्योम mxs_mmc_bc(काष्ठा mxs_mmc_host *host)
अणु
	काष्ठा mxs_ssp *ssp = &host->ssp;
	काष्ठा mmc_command *cmd = host->cmd;
	काष्ठा dma_async_tx_descriptor *desc;
	u32 ctrl0, cmd0, cmd1;

	ctrl0 = BM_SSP_CTRL0_ENABLE | BM_SSP_CTRL0_IGNORE_CRC;
	cmd0 = BF_SSP(cmd->opcode, CMD0_CMD) | BM_SSP_CMD0_APPEND_8CYC;
	cmd1 = cmd->arg;

	अगर (host->sdio_irq_en) अणु
		ctrl0 |= BM_SSP_CTRL0_SDIO_IRQ_CHECK;
		cmd0 |= BM_SSP_CMD0_CONT_CLKING_EN | BM_SSP_CMD0_SLOW_CLKING_EN;
	पूर्ण

	ssp->ssp_pio_words[0] = ctrl0;
	ssp->ssp_pio_words[1] = cmd0;
	ssp->ssp_pio_words[2] = cmd1;
	ssp->dma_dir = DMA_NONE;
	ssp->slave_dirn = DMA_TRANS_NONE;
	desc = mxs_mmc_prep_dma(host, MXS_DMA_CTRL_WAIT4END);
	अगर (!desc)
		जाओ out;

	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);
	वापस;

out:
	dev_warn(mmc_dev(host->mmc),
		 "%s: failed to prep dma\n", __func__);
पूर्ण

अटल व्योम mxs_mmc_ac(काष्ठा mxs_mmc_host *host)
अणु
	काष्ठा mxs_ssp *ssp = &host->ssp;
	काष्ठा mmc_command *cmd = host->cmd;
	काष्ठा dma_async_tx_descriptor *desc;
	u32 ignore_crc, get_resp, दीर्घ_resp;
	u32 ctrl0, cmd0, cmd1;

	ignore_crc = (mmc_resp_type(cmd) & MMC_RSP_CRC) ?
			0 : BM_SSP_CTRL0_IGNORE_CRC;
	get_resp = (mmc_resp_type(cmd) & MMC_RSP_PRESENT) ?
			BM_SSP_CTRL0_GET_RESP : 0;
	दीर्घ_resp = (mmc_resp_type(cmd) & MMC_RSP_136) ?
			BM_SSP_CTRL0_LONG_RESP : 0;

	ctrl0 = BM_SSP_CTRL0_ENABLE | ignore_crc | get_resp | दीर्घ_resp;
	cmd0 = BF_SSP(cmd->opcode, CMD0_CMD);
	cmd1 = cmd->arg;

	अगर (cmd->opcode == MMC_STOP_TRANSMISSION)
		cmd0 |= BM_SSP_CMD0_APPEND_8CYC;

	अगर (host->sdio_irq_en) अणु
		ctrl0 |= BM_SSP_CTRL0_SDIO_IRQ_CHECK;
		cmd0 |= BM_SSP_CMD0_CONT_CLKING_EN | BM_SSP_CMD0_SLOW_CLKING_EN;
	पूर्ण

	ssp->ssp_pio_words[0] = ctrl0;
	ssp->ssp_pio_words[1] = cmd0;
	ssp->ssp_pio_words[2] = cmd1;
	ssp->dma_dir = DMA_NONE;
	ssp->slave_dirn = DMA_TRANS_NONE;
	desc = mxs_mmc_prep_dma(host, MXS_DMA_CTRL_WAIT4END);
	अगर (!desc)
		जाओ out;

	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);
	वापस;

out:
	dev_warn(mmc_dev(host->mmc),
		 "%s: failed to prep dma\n", __func__);
पूर्ण

अटल अचिन्हित लघु mxs_ns_to_ssp_ticks(अचिन्हित घड़ी_rate, अचिन्हित ns)
अणु
	स्थिर अचिन्हित पूर्णांक ssp_समयout_mul = 4096;
	/*
	 * Calculate ticks in ms since ns are large numbers
	 * and might overflow
	 */
	स्थिर अचिन्हित पूर्णांक घड़ी_per_ms = घड़ी_rate / 1000;
	स्थिर अचिन्हित पूर्णांक ms = ns / 1000;
	स्थिर अचिन्हित पूर्णांक ticks = ms * घड़ी_per_ms;
	स्थिर अचिन्हित पूर्णांक ssp_ticks = ticks / ssp_समयout_mul;

	WARN_ON(ssp_ticks == 0);
	वापस ssp_ticks;
पूर्ण

अटल व्योम mxs_mmc_adtc(काष्ठा mxs_mmc_host *host)
अणु
	काष्ठा mmc_command *cmd = host->cmd;
	काष्ठा mmc_data *data = cmd->data;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा scatterlist *sgl = data->sg, *sg;
	अचिन्हित पूर्णांक sg_len = data->sg_len;
	अचिन्हित पूर्णांक i;

	अचिन्हित लघु dma_data_dir, समयout;
	क्रमागत dma_transfer_direction slave_dirn;
	अचिन्हित पूर्णांक data_size = 0, log2_blksz;
	अचिन्हित पूर्णांक blocks = data->blocks;

	काष्ठा mxs_ssp *ssp = &host->ssp;

	u32 ignore_crc, get_resp, दीर्घ_resp, पढ़ो;
	u32 ctrl0, cmd0, cmd1, val;

	ignore_crc = (mmc_resp_type(cmd) & MMC_RSP_CRC) ?
			0 : BM_SSP_CTRL0_IGNORE_CRC;
	get_resp = (mmc_resp_type(cmd) & MMC_RSP_PRESENT) ?
			BM_SSP_CTRL0_GET_RESP : 0;
	दीर्घ_resp = (mmc_resp_type(cmd) & MMC_RSP_136) ?
			BM_SSP_CTRL0_LONG_RESP : 0;

	अगर (data->flags & MMC_DATA_WRITE) अणु
		dma_data_dir = DMA_TO_DEVICE;
		slave_dirn = DMA_MEM_TO_DEV;
		पढ़ो = 0;
	पूर्ण अन्यथा अणु
		dma_data_dir = DMA_FROM_DEVICE;
		slave_dirn = DMA_DEV_TO_MEM;
		पढ़ो = BM_SSP_CTRL0_READ;
	पूर्ण

	ctrl0 = BF_SSP(host->bus_width, CTRL0_BUS_WIDTH) |
		ignore_crc | get_resp | दीर्घ_resp |
		BM_SSP_CTRL0_DATA_XFER | पढ़ो |
		BM_SSP_CTRL0_WAIT_FOR_IRQ |
		BM_SSP_CTRL0_ENABLE;

	cmd0 = BF_SSP(cmd->opcode, CMD0_CMD);

	/* get logarithm to base 2 of block size क्रम setting रेजिस्टर */
	log2_blksz = ilog2(data->blksz);

	/*
	 * take special care of the हाल that data size from data->sg
	 * is not equal to blocks x blksz
	 */
	क्रम_each_sg(sgl, sg, sg_len, i)
		data_size += sg->length;

	अगर (data_size != data->blocks * data->blksz)
		blocks = 1;

	/* xfer count, block size and count need to be set dअगरferently */
	अगर (ssp_is_old(ssp)) अणु
		ctrl0 |= BF_SSP(data_size, CTRL0_XFER_COUNT);
		cmd0 |= BF_SSP(log2_blksz, CMD0_BLOCK_SIZE) |
			BF_SSP(blocks - 1, CMD0_BLOCK_COUNT);
	पूर्ण अन्यथा अणु
		ग_लिखोl(data_size, ssp->base + HW_SSP_XFER_SIZE);
		ग_लिखोl(BF_SSP(log2_blksz, BLOCK_SIZE_BLOCK_SIZE) |
		       BF_SSP(blocks - 1, BLOCK_SIZE_BLOCK_COUNT),
		       ssp->base + HW_SSP_BLOCK_SIZE);
	पूर्ण

	अगर (cmd->opcode == SD_IO_RW_EXTENDED)
		cmd0 |= BM_SSP_CMD0_APPEND_8CYC;

	cmd1 = cmd->arg;

	अगर (host->sdio_irq_en) अणु
		ctrl0 |= BM_SSP_CTRL0_SDIO_IRQ_CHECK;
		cmd0 |= BM_SSP_CMD0_CONT_CLKING_EN | BM_SSP_CMD0_SLOW_CLKING_EN;
	पूर्ण

	/* set the समयout count */
	समयout = mxs_ns_to_ssp_ticks(ssp->clk_rate, data->समयout_ns);
	val = पढ़ोl(ssp->base + HW_SSP_TIMING(ssp));
	val &= ~(BM_SSP_TIMING_TIMEOUT);
	val |= BF_SSP(समयout, TIMING_TIMEOUT);
	ग_लिखोl(val, ssp->base + HW_SSP_TIMING(ssp));

	/* pio */
	ssp->ssp_pio_words[0] = ctrl0;
	ssp->ssp_pio_words[1] = cmd0;
	ssp->ssp_pio_words[2] = cmd1;
	ssp->dma_dir = DMA_NONE;
	ssp->slave_dirn = DMA_TRANS_NONE;
	desc = mxs_mmc_prep_dma(host, 0);
	अगर (!desc)
		जाओ out;

	/* append data sg */
	WARN_ON(host->data != शून्य);
	host->data = data;
	ssp->dma_dir = dma_data_dir;
	ssp->slave_dirn = slave_dirn;
	desc = mxs_mmc_prep_dma(host, DMA_PREP_INTERRUPT | MXS_DMA_CTRL_WAIT4END);
	अगर (!desc)
		जाओ out;

	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);
	वापस;
out:
	dev_warn(mmc_dev(host->mmc),
		 "%s: failed to prep dma\n", __func__);
पूर्ण

अटल व्योम mxs_mmc_start_cmd(काष्ठा mxs_mmc_host *host,
			      काष्ठा mmc_command *cmd)
अणु
	host->cmd = cmd;

	चयन (mmc_cmd_type(cmd)) अणु
	हाल MMC_CMD_BC:
		mxs_mmc_bc(host);
		अवरोध;
	हाल MMC_CMD_BCR:
		mxs_mmc_ac(host);
		अवरोध;
	हाल MMC_CMD_AC:
		mxs_mmc_ac(host);
		अवरोध;
	हाल MMC_CMD_ADTC:
		mxs_mmc_adtc(host);
		अवरोध;
	शेष:
		dev_warn(mmc_dev(host->mmc),
			 "%s: unknown MMC command\n", __func__);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mxs_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);

	WARN_ON(host->mrq != शून्य);
	host->mrq = mrq;

	अगर (mrq->sbc)
		mxs_mmc_start_cmd(host, mrq->sbc);
	अन्यथा
		mxs_mmc_start_cmd(host, mrq->cmd);
पूर्ण

अटल व्योम mxs_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);

	अगर (ios->bus_width == MMC_BUS_WIDTH_8)
		host->bus_width = 2;
	अन्यथा अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		host->bus_width = 1;
	अन्यथा
		host->bus_width = 0;

	अगर (ios->घड़ी)
		mxs_ssp_set_clk_rate(&host->ssp, ios->घड़ी);
पूर्ण

अटल व्योम mxs_mmc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);
	काष्ठा mxs_ssp *ssp = &host->ssp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	host->sdio_irq_en = enable;

	अगर (enable) अणु
		ग_लिखोl(BM_SSP_CTRL0_SDIO_IRQ_CHECK,
		       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);
		ग_लिखोl(BM_SSP_CTRL1_SDIO_IRQ_EN,
		       ssp->base + HW_SSP_CTRL1(ssp) + STMP_OFFSET_REG_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(BM_SSP_CTRL0_SDIO_IRQ_CHECK,
		       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
		ग_लिखोl(BM_SSP_CTRL1_SDIO_IRQ_EN,
		       ssp->base + HW_SSP_CTRL1(ssp) + STMP_OFFSET_REG_CLR);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);

	अगर (enable && पढ़ोl(ssp->base + HW_SSP_STATUS(ssp)) &
			BM_SSP_STATUS_SDIO_IRQ)
		mmc_संकेत_sdio_irq(host->mmc);

पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mxs_mmc_ops = अणु
	.request = mxs_mmc_request,
	.get_ro = mmc_gpio_get_ro,
	.get_cd = mxs_mmc_get_cd,
	.set_ios = mxs_mmc_set_ios,
	.enable_sdio_irq = mxs_mmc_enable_sdio_irq,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_mmc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-mmc", .data = (व्योम *) IMX23_SSP, पूर्ण,
	अणु .compatible = "fsl,imx28-mmc", .data = (व्योम *) IMX28_SSP, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_mmc_dt_ids);

अटल पूर्णांक mxs_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mxs_mmc_host *host;
	काष्ठा mmc_host *mmc;
	पूर्णांक ret = 0, irq_err;
	काष्ठा regulator *reg_vmmc;
	काष्ठा mxs_ssp *ssp;

	irq_err = platक्रमm_get_irq(pdev, 0);
	अगर (irq_err < 0)
		वापस irq_err;

	mmc = mmc_alloc_host(माप(काष्ठा mxs_mmc_host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	ssp = &host->ssp;
	ssp->dev = &pdev->dev;
	ssp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ssp->base)) अणु
		ret = PTR_ERR(ssp->base);
		जाओ out_mmc_मुक्त;
	पूर्ण

	ssp->devid = (क्रमागत mxs_ssp_id)of_device_get_match_data(&pdev->dev);

	host->mmc = mmc;
	host->sdio_irq_en = 0;

	reg_vmmc = devm_regulator_get(&pdev->dev, "vmmc");
	अगर (!IS_ERR(reg_vmmc)) अणु
		ret = regulator_enable(reg_vmmc);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to enable vmmc regulator: %d\n", ret);
			जाओ out_mmc_मुक्त;
		पूर्ण
	पूर्ण

	ssp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ssp->clk)) अणु
		ret = PTR_ERR(ssp->clk);
		जाओ out_mmc_मुक्त;
	पूर्ण
	ret = clk_prepare_enable(ssp->clk);
	अगर (ret)
		जाओ out_mmc_मुक्त;

	ret = mxs_mmc_reset(host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to reset mmc: %d\n", ret);
		जाओ out_clk_disable;
	पूर्ण

	ssp->dmach = dma_request_chan(&pdev->dev, "rx-tx");
	अगर (IS_ERR(ssp->dmach)) अणु
		dev_err(mmc_dev(host->mmc),
			"%s: failed to request dma\n", __func__);
		ret = PTR_ERR(ssp->dmach);
		जाओ out_clk_disable;
	पूर्ण

	/* set mmc core parameters */
	mmc->ops = &mxs_mmc_ops;
	mmc->caps = MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		    MMC_CAP_SDIO_IRQ | MMC_CAP_NEEDS_POLL | MMC_CAP_CMD23;

	host->broken_cd = of_property_पढ़ो_bool(np, "broken-cd");

	mmc->f_min = 400000;
	mmc->f_max = 288000000;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ out_मुक्त_dma;

	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	mmc->max_segs = 52;
	mmc->max_blk_size = 1 << 0xf;
	mmc->max_blk_count = (ssp_is_old(ssp)) ? 0xff : 0xffffff;
	mmc->max_req_size = (ssp_is_old(ssp)) ? 0xffff : 0xffffffff;
	mmc->max_seg_size = dma_get_max_seg_size(ssp->dmach->device->dev);

	platक्रमm_set_drvdata(pdev, mmc);

	spin_lock_init(&host->lock);

	ret = devm_request_irq(&pdev->dev, irq_err, mxs_mmc_irq_handler, 0,
			       dev_name(&pdev->dev), host);
	अगर (ret)
		जाओ out_मुक्त_dma;

	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ out_मुक्त_dma;

	dev_info(mmc_dev(host->mmc), "initialized\n");

	वापस 0;

out_मुक्त_dma:
	dma_release_channel(ssp->dmach);
out_clk_disable:
	clk_disable_unprepare(ssp->clk);
out_mmc_मुक्त:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक mxs_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc = platक्रमm_get_drvdata(pdev);
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);
	काष्ठा mxs_ssp *ssp = &host->ssp;

	mmc_हटाओ_host(mmc);

	अगर (ssp->dmach)
		dma_release_channel(ssp->dmach);

	clk_disable_unprepare(ssp->clk);

	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mxs_mmc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);
	काष्ठा mxs_ssp *ssp = &host->ssp;

	clk_disable_unprepare(ssp->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक mxs_mmc_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा mxs_mmc_host *host = mmc_priv(mmc);
	काष्ठा mxs_ssp *ssp = &host->ssp;

	वापस clk_prepare_enable(ssp->clk);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mxs_mmc_pm_ops, mxs_mmc_suspend, mxs_mmc_resume);

अटल काष्ठा platक्रमm_driver mxs_mmc_driver = अणु
	.probe		= mxs_mmc_probe,
	.हटाओ		= mxs_mmc_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &mxs_mmc_pm_ops,
		.of_match_table = mxs_mmc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mxs_mmc_driver);

MODULE_DESCRIPTION("FREESCALE MXS MMC peripheral");
MODULE_AUTHOR("Freescale Semiconductor");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
