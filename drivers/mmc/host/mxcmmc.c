<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/host/mxcmmc.c - Freescale i.MX MMCI driver
 *
 *  This is a driver क्रम the SDHC controller found in Freescale MX2/MX3
 *  SoCs. It is basically the same hardware as found on MX1 (imxmmc.c).
 *  Unlike the hardware found on MX1, this hardware just works and करोes
 *  not need all the quirks found in imxmmc.c, hence the separate driver.
 *
 *  Copyright (C) 2008 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 *  Copyright (C) 2006 Pavel Pisa, PiKRON <ppisa@pikron.com>
 *
 *  derived from pxamci.c by Russell King
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/platक्रमm_data/mmc-mxcmmc.h>

#समावेश <linux/platक्रमm_data/dma-imx.h>

#घोषणा DRIVER_NAME "mxc-mmc"
#घोषणा MXCMCI_TIMEOUT_MS 10000

#घोषणा MMC_REG_STR_STP_CLK		0x00
#घोषणा MMC_REG_STATUS			0x04
#घोषणा MMC_REG_CLK_RATE		0x08
#घोषणा MMC_REG_CMD_DAT_CONT		0x0C
#घोषणा MMC_REG_RES_TO			0x10
#घोषणा MMC_REG_READ_TO			0x14
#घोषणा MMC_REG_BLK_LEN			0x18
#घोषणा MMC_REG_NOB			0x1C
#घोषणा MMC_REG_REV_NO			0x20
#घोषणा MMC_REG_INT_CNTR		0x24
#घोषणा MMC_REG_CMD			0x28
#घोषणा MMC_REG_ARG			0x2C
#घोषणा MMC_REG_RES_FIFO		0x34
#घोषणा MMC_REG_BUFFER_ACCESS		0x38

#घोषणा STR_STP_CLK_RESET               (1 << 3)
#घोषणा STR_STP_CLK_START_CLK           (1 << 1)
#घोषणा STR_STP_CLK_STOP_CLK            (1 << 0)

#घोषणा STATUS_CARD_INSERTION		(1 << 31)
#घोषणा STATUS_CARD_REMOVAL		(1 << 30)
#घोषणा STATUS_YBUF_EMPTY		(1 << 29)
#घोषणा STATUS_XBUF_EMPTY		(1 << 28)
#घोषणा STATUS_YBUF_FULL		(1 << 27)
#घोषणा STATUS_XBUF_FULL		(1 << 26)
#घोषणा STATUS_BUF_UND_RUN		(1 << 25)
#घोषणा STATUS_BUF_OVFL			(1 << 24)
#घोषणा STATUS_SDIO_INT_ACTIVE		(1 << 14)
#घोषणा STATUS_END_CMD_RESP		(1 << 13)
#घोषणा STATUS_WRITE_OP_DONE		(1 << 12)
#घोषणा STATUS_DATA_TRANS_DONE		(1 << 11)
#घोषणा STATUS_READ_OP_DONE		(1 << 11)
#घोषणा STATUS_WR_CRC_ERROR_CODE_MASK	(3 << 10)
#घोषणा STATUS_CARD_BUS_CLK_RUN		(1 << 8)
#घोषणा STATUS_BUF_READ_RDY		(1 << 7)
#घोषणा STATUS_BUF_WRITE_RDY		(1 << 6)
#घोषणा STATUS_RESP_CRC_ERR		(1 << 5)
#घोषणा STATUS_CRC_READ_ERR		(1 << 3)
#घोषणा STATUS_CRC_WRITE_ERR		(1 << 2)
#घोषणा STATUS_TIME_OUT_RESP		(1 << 1)
#घोषणा STATUS_TIME_OUT_READ		(1 << 0)
#घोषणा STATUS_ERR_MASK			0x2f

#घोषणा CMD_DAT_CONT_CMD_RESP_LONG_OFF	(1 << 12)
#घोषणा CMD_DAT_CONT_STOP_READWAIT	(1 << 11)
#घोषणा CMD_DAT_CONT_START_READWAIT	(1 << 10)
#घोषणा CMD_DAT_CONT_BUS_WIDTH_4	(2 << 8)
#घोषणा CMD_DAT_CONT_INIT		(1 << 7)
#घोषणा CMD_DAT_CONT_WRITE		(1 << 4)
#घोषणा CMD_DAT_CONT_DATA_ENABLE	(1 << 3)
#घोषणा CMD_DAT_CONT_RESPONSE_48BIT_CRC	(1 << 0)
#घोषणा CMD_DAT_CONT_RESPONSE_136BIT	(2 << 0)
#घोषणा CMD_DAT_CONT_RESPONSE_48BIT	(3 << 0)

#घोषणा INT_SDIO_INT_WKP_EN		(1 << 18)
#घोषणा INT_CARD_INSERTION_WKP_EN	(1 << 17)
#घोषणा INT_CARD_REMOVAL_WKP_EN		(1 << 16)
#घोषणा INT_CARD_INSERTION_EN		(1 << 15)
#घोषणा INT_CARD_REMOVAL_EN		(1 << 14)
#घोषणा INT_SDIO_IRQ_EN			(1 << 13)
#घोषणा INT_DAT0_EN			(1 << 12)
#घोषणा INT_BUF_READ_EN			(1 << 4)
#घोषणा INT_BUF_WRITE_EN		(1 << 3)
#घोषणा INT_END_CMD_RES_EN		(1 << 2)
#घोषणा INT_WRITE_OP_DONE_EN		(1 << 1)
#घोषणा INT_READ_OP_EN			(1 << 0)

क्रमागत mxcmci_type अणु
	IMX21_MMC,
	IMX31_MMC,
	MPC512X_MMC,
पूर्ण;

काष्ठा mxcmci_host अणु
	काष्ठा mmc_host		*mmc;
	व्योम __iomem		*base;
	dma_addr_t		phys_base;
	पूर्णांक			detect_irq;
	काष्ठा dma_chan		*dma;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक			करो_dma;
	पूर्णांक			शेष_irq_mask;
	पूर्णांक			use_sdio;
	अचिन्हित पूर्णांक		घातer_mode;
	काष्ठा imxmmc_platक्रमm_data *pdata;

	काष्ठा mmc_request	*req;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_data		*data;

	अचिन्हित पूर्णांक		datasize;
	अचिन्हित पूर्णांक		dma_dir;

	u16			rev_no;
	अचिन्हित पूर्णांक		cmdat;

	काष्ठा clk		*clk_ipg;
	काष्ठा clk		*clk_per;

	पूर्णांक			घड़ी;

	काष्ठा work_काष्ठा	datawork;
	spinlock_t		lock;

	पूर्णांक			burstlen;
	पूर्णांक			dmareq;
	काष्ठा dma_slave_config dma_slave_config;
	काष्ठा imx_dma_data	dma_data;

	काष्ठा समयr_list	watchकरोg;
	क्रमागत mxcmci_type	devtype;
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxcmci_of_match[] = अणु
	अणु
		.compatible = "fsl,imx21-mmc",
		.data = (व्योम *) IMX21_MMC,
	पूर्ण, अणु
		.compatible = "fsl,imx31-mmc",
		.data = (व्योम *) IMX31_MMC,
	पूर्ण, अणु
		.compatible = "fsl,mpc5121-sdhc",
		.data = (व्योम *) MPC512X_MMC,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxcmci_of_match);

अटल अंतरभूत पूर्णांक is_imx31_mmc(काष्ठा mxcmci_host *host)
अणु
	वापस host->devtype == IMX31_MMC;
पूर्ण

अटल अंतरभूत पूर्णांक is_mpc512x_mmc(काष्ठा mxcmci_host *host)
अणु
	वापस host->devtype == MPC512X_MMC;
पूर्ण

अटल अंतरभूत u32 mxcmci_पढ़ोl(काष्ठा mxcmci_host *host, पूर्णांक reg)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_MPC512x))
		वापस ioपढ़ो32be(host->base + reg);
	अन्यथा
		वापस पढ़ोl(host->base + reg);
पूर्ण

अटल अंतरभूत व्योम mxcmci_ग_लिखोl(काष्ठा mxcmci_host *host, u32 val, पूर्णांक reg)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_MPC512x))
		ioग_लिखो32be(val, host->base + reg);
	अन्यथा
		ग_लिखोl(val, host->base + reg);
पूर्ण

अटल अंतरभूत u16 mxcmci_पढ़ोw(काष्ठा mxcmci_host *host, पूर्णांक reg)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_MPC512x))
		वापस ioपढ़ो32be(host->base + reg);
	अन्यथा
		वापस पढ़ोw(host->base + reg);
पूर्ण

अटल अंतरभूत व्योम mxcmci_ग_लिखोw(काष्ठा mxcmci_host *host, u16 val, पूर्णांक reg)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_MPC512x))
		ioग_लिखो32be(val, host->base + reg);
	अन्यथा
		ग_लिखोw(val, host->base + reg);
पूर्ण

अटल व्योम mxcmci_set_clk_rate(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक clk_ios);

अटल व्योम mxcmci_set_घातer(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक vdd)
अणु
	अगर (!IS_ERR(host->mmc->supply.vmmc)) अणु
		अगर (host->घातer_mode == MMC_POWER_UP)
			mmc_regulator_set_ocr(host->mmc,
					      host->mmc->supply.vmmc, vdd);
		अन्यथा अगर (host->घातer_mode == MMC_POWER_OFF)
			mmc_regulator_set_ocr(host->mmc,
					      host->mmc->supply.vmmc, 0);
	पूर्ण

	अगर (host->pdata && host->pdata->setघातer)
		host->pdata->setघातer(mmc_dev(host->mmc), vdd);
पूर्ण

अटल अंतरभूत पूर्णांक mxcmci_use_dma(काष्ठा mxcmci_host *host)
अणु
	वापस host->करो_dma;
पूर्ण

अटल व्योम mxcmci_softreset(काष्ठा mxcmci_host *host)
अणु
	पूर्णांक i;

	dev_dbg(mmc_dev(host->mmc), "mxcmci_softreset\n");

	/* reset sequence */
	mxcmci_ग_लिखोw(host, STR_STP_CLK_RESET, MMC_REG_STR_STP_CLK);
	mxcmci_ग_लिखोw(host, STR_STP_CLK_RESET | STR_STP_CLK_START_CLK,
			MMC_REG_STR_STP_CLK);

	क्रम (i = 0; i < 8; i++)
		mxcmci_ग_लिखोw(host, STR_STP_CLK_START_CLK, MMC_REG_STR_STP_CLK);

	mxcmci_ग_लिखोw(host, 0xff, MMC_REG_RES_TO);
पूर्ण

#अगर IS_ENABLED(CONFIG_PPC_MPC512x)
अटल अंतरभूत व्योम buffer_swap32(u32 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ((len + 3) / 4); i++) अणु
		*buf = swab32(*buf);
		buf++;
	पूर्ण
पूर्ण

अटल व्योम mxcmci_swap_buffers(काष्ठा mmc_data *data)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(data->sg, sg, data->sg_len, i)
		buffer_swap32(sg_virt(sg), sg->length);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mxcmci_swap_buffers(काष्ठा mmc_data *data) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक mxcmci_setup_data(काष्ठा mxcmci_host *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक nob = data->blocks;
	अचिन्हित पूर्णांक blksz = data->blksz;
	अचिन्हित पूर्णांक datasize = nob * blksz;
	काष्ठा scatterlist *sg;
	क्रमागत dma_transfer_direction slave_dirn;
	पूर्णांक i, nents;

	host->data = data;
	data->bytes_xfered = 0;

	mxcmci_ग_लिखोw(host, nob, MMC_REG_NOB);
	mxcmci_ग_लिखोw(host, blksz, MMC_REG_BLK_LEN);
	host->datasize = datasize;

	अगर (!mxcmci_use_dma(host))
		वापस 0;

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		अगर (sg->offset & 3 || sg->length & 3 || sg->length < 512) अणु
			host->करो_dma = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (data->flags & MMC_DATA_READ) अणु
		host->dma_dir = DMA_FROM_DEVICE;
		slave_dirn = DMA_DEV_TO_MEM;
	पूर्ण अन्यथा अणु
		host->dma_dir = DMA_TO_DEVICE;
		slave_dirn = DMA_MEM_TO_DEV;

		mxcmci_swap_buffers(data);
	पूर्ण

	nents = dma_map_sg(host->dma->device->dev, data->sg,
				     data->sg_len,  host->dma_dir);
	अगर (nents != data->sg_len)
		वापस -EINVAL;

	host->desc = dmaengine_prep_slave_sg(host->dma,
		data->sg, data->sg_len, slave_dirn,
		DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!host->desc) अणु
		dma_unmap_sg(host->dma->device->dev, data->sg, data->sg_len,
				host->dma_dir);
		host->करो_dma = 0;
		वापस 0; /* Fall back to PIO */
	पूर्ण
	wmb();

	dmaengine_submit(host->desc);
	dma_async_issue_pending(host->dma);

	mod_समयr(&host->watchकरोg, jअगरfies + msecs_to_jअगरfies(MXCMCI_TIMEOUT_MS));

	वापस 0;
पूर्ण

अटल व्योम mxcmci_cmd_करोne(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक stat);
अटल व्योम mxcmci_data_करोne(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक stat);

अटल व्योम mxcmci_dma_callback(व्योम *data)
अणु
	काष्ठा mxcmci_host *host = data;
	u32 stat;

	del_समयr(&host->watchकरोg);

	stat = mxcmci_पढ़ोl(host, MMC_REG_STATUS);

	dev_dbg(mmc_dev(host->mmc), "%s: 0x%08x\n", __func__, stat);

	mxcmci_data_करोne(host, stat);
पूर्ण

अटल पूर्णांक mxcmci_start_cmd(काष्ठा mxcmci_host *host, काष्ठा mmc_command *cmd,
		अचिन्हित पूर्णांक cmdat)
अणु
	u32 पूर्णांक_cntr = host->शेष_irq_mask;
	अचिन्हित दीर्घ flags;

	WARN_ON(host->cmd != शून्य);
	host->cmd = cmd;

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_R1: /* लघु CRC, OPCODE */
	हाल MMC_RSP_R1B:/* लघु CRC, OPCODE, BUSY */
		cmdat |= CMD_DAT_CONT_RESPONSE_48BIT_CRC;
		अवरोध;
	हाल MMC_RSP_R2: /* दीर्घ 136 bit + CRC */
		cmdat |= CMD_DAT_CONT_RESPONSE_136BIT;
		अवरोध;
	हाल MMC_RSP_R3: /* लघु */
		cmdat |= CMD_DAT_CONT_RESPONSE_48BIT;
		अवरोध;
	हाल MMC_RSP_NONE:
		अवरोध;
	शेष:
		dev_err(mmc_dev(host->mmc), "unhandled response type 0x%x\n",
				mmc_resp_type(cmd));
		cmd->error = -EINVAL;
		वापस -EINVAL;
	पूर्ण

	पूर्णांक_cntr = INT_END_CMD_RES_EN;

	अगर (mxcmci_use_dma(host)) अणु
		अगर (host->dma_dir == DMA_FROM_DEVICE) अणु
			host->desc->callback = mxcmci_dma_callback;
			host->desc->callback_param = host;
		पूर्ण अन्यथा अणु
			पूर्णांक_cntr |= INT_WRITE_OP_DONE_EN;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);
	अगर (host->use_sdio)
		पूर्णांक_cntr |= INT_SDIO_IRQ_EN;
	mxcmci_ग_लिखोl(host, पूर्णांक_cntr, MMC_REG_INT_CNTR);
	spin_unlock_irqrestore(&host->lock, flags);

	mxcmci_ग_लिखोw(host, cmd->opcode, MMC_REG_CMD);
	mxcmci_ग_लिखोl(host, cmd->arg, MMC_REG_ARG);
	mxcmci_ग_लिखोw(host, cmdat, MMC_REG_CMD_DAT_CONT);

	वापस 0;
पूर्ण

अटल व्योम mxcmci_finish_request(काष्ठा mxcmci_host *host,
		काष्ठा mmc_request *req)
अणु
	u32 पूर्णांक_cntr = host->शेष_irq_mask;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	अगर (host->use_sdio)
		पूर्णांक_cntr |= INT_SDIO_IRQ_EN;
	mxcmci_ग_लिखोl(host, पूर्णांक_cntr, MMC_REG_INT_CNTR);
	spin_unlock_irqrestore(&host->lock, flags);

	host->req = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;

	mmc_request_करोne(host->mmc, req);
पूर्ण

अटल पूर्णांक mxcmci_finish_data(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक data_error;

	अगर (mxcmci_use_dma(host)) अणु
		dma_unmap_sg(host->dma->device->dev, data->sg, data->sg_len,
				host->dma_dir);
		mxcmci_swap_buffers(data);
	पूर्ण

	अगर (stat & STATUS_ERR_MASK) अणु
		dev_dbg(mmc_dev(host->mmc), "request failed. status: 0x%08x\n",
				stat);
		अगर (stat & STATUS_CRC_READ_ERR) अणु
			dev_err(mmc_dev(host->mmc), "%s: -EILSEQ\n", __func__);
			data->error = -EILSEQ;
		पूर्ण अन्यथा अगर (stat & STATUS_CRC_WRITE_ERR) अणु
			u32 err_code = (stat >> 9) & 0x3;
			अगर (err_code == 2) अणु /* No CRC response */
				dev_err(mmc_dev(host->mmc),
					"%s: No CRC -ETIMEDOUT\n", __func__);
				data->error = -ETIMEDOUT;
			पूर्ण अन्यथा अणु
				dev_err(mmc_dev(host->mmc),
					"%s: -EILSEQ\n", __func__);
				data->error = -EILSEQ;
			पूर्ण
		पूर्ण अन्यथा अगर (stat & STATUS_TIME_OUT_READ) अणु
			dev_err(mmc_dev(host->mmc),
				"%s: read -ETIMEDOUT\n", __func__);
			data->error = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			dev_err(mmc_dev(host->mmc), "%s: -EIO\n", __func__);
			data->error = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		data->bytes_xfered = host->datasize;
	पूर्ण

	data_error = data->error;

	host->data = शून्य;

	वापस data_error;
पूर्ण

अटल व्योम mxcmci_पढ़ो_response(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_command *cmd = host->cmd;
	पूर्णांक i;
	u32 a, b, c;

	अगर (!cmd)
		वापस;

	अगर (stat & STATUS_TIME_OUT_RESP) अणु
		dev_dbg(mmc_dev(host->mmc), "CMD TIMEOUT\n");
		cmd->error = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (stat & STATUS_RESP_CRC_ERR && cmd->flags & MMC_RSP_CRC) अणु
		dev_dbg(mmc_dev(host->mmc), "cmd crc error\n");
		cmd->error = -EILSEQ;
	पूर्ण

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			क्रम (i = 0; i < 4; i++) अणु
				a = mxcmci_पढ़ोw(host, MMC_REG_RES_FIFO);
				b = mxcmci_पढ़ोw(host, MMC_REG_RES_FIFO);
				cmd->resp[i] = a << 16 | b;
			पूर्ण
		पूर्ण अन्यथा अणु
			a = mxcmci_पढ़ोw(host, MMC_REG_RES_FIFO);
			b = mxcmci_पढ़ोw(host, MMC_REG_RES_FIFO);
			c = mxcmci_पढ़ोw(host, MMC_REG_RES_FIFO);
			cmd->resp[0] = a << 24 | b << 8 | c >> 8;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mxcmci_poll_status(काष्ठा mxcmci_host *host, u32 mask)
अणु
	u32 stat;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;

	करो अणु
		stat = mxcmci_पढ़ोl(host, MMC_REG_STATUS);
		अगर (stat & STATUS_ERR_MASK)
			वापस stat;
		अगर (समय_after(jअगरfies, समयout)) अणु
			mxcmci_softreset(host);
			mxcmci_set_clk_rate(host, host->घड़ी);
			वापस STATUS_TIME_OUT_READ;
		पूर्ण
		अगर (stat & mask)
			वापस 0;
		cpu_relax();
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक mxcmci_pull(काष्ठा mxcmci_host *host, व्योम *_buf, पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक stat;
	u32 *buf = _buf;

	जबतक (bytes > 3) अणु
		stat = mxcmci_poll_status(host,
				STATUS_BUF_READ_RDY | STATUS_READ_OP_DONE);
		अगर (stat)
			वापस stat;
		*buf++ = cpu_to_le32(mxcmci_पढ़ोl(host, MMC_REG_BUFFER_ACCESS));
		bytes -= 4;
	पूर्ण

	अगर (bytes) अणु
		u8 *b = (u8 *)buf;
		u32 पंचांगp;

		stat = mxcmci_poll_status(host,
				STATUS_BUF_READ_RDY | STATUS_READ_OP_DONE);
		अगर (stat)
			वापस stat;
		पंचांगp = cpu_to_le32(mxcmci_पढ़ोl(host, MMC_REG_BUFFER_ACCESS));
		स_नकल(b, &पंचांगp, bytes);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxcmci_push(काष्ठा mxcmci_host *host, व्योम *_buf, पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक stat;
	u32 *buf = _buf;

	जबतक (bytes > 3) अणु
		stat = mxcmci_poll_status(host, STATUS_BUF_WRITE_RDY);
		अगर (stat)
			वापस stat;
		mxcmci_ग_लिखोl(host, cpu_to_le32(*buf++), MMC_REG_BUFFER_ACCESS);
		bytes -= 4;
	पूर्ण

	अगर (bytes) अणु
		u8 *b = (u8 *)buf;
		u32 पंचांगp;

		stat = mxcmci_poll_status(host, STATUS_BUF_WRITE_RDY);
		अगर (stat)
			वापस stat;

		स_नकल(&पंचांगp, b, bytes);
		mxcmci_ग_लिखोl(host, cpu_to_le32(पंचांगp), MMC_REG_BUFFER_ACCESS);
	पूर्ण

	वापस mxcmci_poll_status(host, STATUS_BUF_WRITE_RDY);
पूर्ण

अटल पूर्णांक mxcmci_transfer_data(काष्ठा mxcmci_host *host)
अणु
	काष्ठा mmc_data *data = host->req->data;
	काष्ठा scatterlist *sg;
	पूर्णांक stat, i;

	host->data = data;
	host->datasize = 0;

	अगर (data->flags & MMC_DATA_READ) अणु
		क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
			stat = mxcmci_pull(host, sg_virt(sg), sg->length);
			अगर (stat)
				वापस stat;
			host->datasize += sg->length;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
			stat = mxcmci_push(host, sg_virt(sg), sg->length);
			अगर (stat)
				वापस stat;
			host->datasize += sg->length;
		पूर्ण
		stat = mxcmci_poll_status(host, STATUS_WRITE_OP_DONE);
		अगर (stat)
			वापस stat;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mxcmci_datawork(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mxcmci_host *host = container_of(work, काष्ठा mxcmci_host,
						  datawork);
	पूर्णांक datastat = mxcmci_transfer_data(host);

	mxcmci_ग_लिखोl(host, STATUS_READ_OP_DONE | STATUS_WRITE_OP_DONE,
		MMC_REG_STATUS);
	mxcmci_finish_data(host, datastat);

	अगर (host->req->stop) अणु
		अगर (mxcmci_start_cmd(host, host->req->stop, 0)) अणु
			mxcmci_finish_request(host, host->req);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		mxcmci_finish_request(host, host->req);
	पूर्ण
पूर्ण

अटल व्योम mxcmci_data_करोne(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_request *req;
	पूर्णांक data_error;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	अगर (!host->data) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		वापस;
	पूर्ण

	अगर (!host->req) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		वापस;
	पूर्ण

	req = host->req;
	अगर (!req->stop)
		host->req = शून्य; /* we will handle finish req below */

	data_error = mxcmci_finish_data(host, stat);

	spin_unlock_irqrestore(&host->lock, flags);

	अगर (data_error)
		वापस;

	mxcmci_पढ़ो_response(host, stat);
	host->cmd = शून्य;

	अगर (req->stop) अणु
		अगर (mxcmci_start_cmd(host, req->stop, 0)) अणु
			mxcmci_finish_request(host, req);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		mxcmci_finish_request(host, req);
	पूर्ण
पूर्ण

अटल व्योम mxcmci_cmd_करोne(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक stat)
अणु
	mxcmci_पढ़ो_response(host, stat);
	host->cmd = शून्य;

	अगर (!host->data && host->req) अणु
		mxcmci_finish_request(host, host->req);
		वापस;
	पूर्ण

	/* For the DMA हाल the DMA engine handles the data transfer
	 * स्वतःmatically. For non DMA we have to करो it ourselves.
	 * Don't करो it in पूर्णांकerrupt context though.
	 */
	अगर (!mxcmci_use_dma(host) && host->data)
		schedule_work(&host->datawork);

पूर्ण

अटल irqवापस_t mxcmci_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा mxcmci_host *host = devid;
	bool sdio_irq;
	u32 stat;

	stat = mxcmci_पढ़ोl(host, MMC_REG_STATUS);
	mxcmci_ग_लिखोl(host,
		stat & ~(STATUS_SDIO_INT_ACTIVE | STATUS_DATA_TRANS_DONE |
			 STATUS_WRITE_OP_DONE),
		MMC_REG_STATUS);

	dev_dbg(mmc_dev(host->mmc), "%s: 0x%08x\n", __func__, stat);

	spin_lock(&host->lock);
	sdio_irq = (stat & STATUS_SDIO_INT_ACTIVE) && host->use_sdio;
	spin_unlock(&host->lock);

	अगर (mxcmci_use_dma(host) && (stat & (STATUS_WRITE_OP_DONE)))
		mxcmci_ग_लिखोl(host, STATUS_WRITE_OP_DONE, MMC_REG_STATUS);

	अगर (sdio_irq) अणु
		mxcmci_ग_लिखोl(host, STATUS_SDIO_INT_ACTIVE, MMC_REG_STATUS);
		mmc_संकेत_sdio_irq(host->mmc);
	पूर्ण

	अगर (stat & STATUS_END_CMD_RESP)
		mxcmci_cmd_करोne(host, stat);

	अगर (mxcmci_use_dma(host) && (stat & STATUS_WRITE_OP_DONE)) अणु
		del_समयr(&host->watchकरोg);
		mxcmci_data_करोne(host, stat);
	पूर्ण

	अगर (host->शेष_irq_mask &&
		  (stat & (STATUS_CARD_INSERTION | STATUS_CARD_REMOVAL)))
		mmc_detect_change(host->mmc, msecs_to_jअगरfies(200));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mxcmci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा mxcmci_host *host = mmc_priv(mmc);
	अचिन्हित पूर्णांक cmdat = host->cmdat;
	पूर्णांक error;

	WARN_ON(host->req != शून्य);

	host->req = req;
	host->cmdat &= ~CMD_DAT_CONT_INIT;

	अगर (host->dma)
		host->करो_dma = 1;

	अगर (req->data) अणु
		error = mxcmci_setup_data(host, req->data);
		अगर (error) अणु
			req->cmd->error = error;
			जाओ out;
		पूर्ण


		cmdat |= CMD_DAT_CONT_DATA_ENABLE;

		अगर (req->data->flags & MMC_DATA_WRITE)
			cmdat |= CMD_DAT_CONT_WRITE;
	पूर्ण

	error = mxcmci_start_cmd(host, req->cmd, cmdat);

out:
	अगर (error)
		mxcmci_finish_request(host, req);
पूर्ण

अटल व्योम mxcmci_set_clk_rate(काष्ठा mxcmci_host *host, अचिन्हित पूर्णांक clk_ios)
अणु
	अचिन्हित पूर्णांक भागider;
	पूर्णांक prescaler = 0;
	अचिन्हित पूर्णांक clk_in = clk_get_rate(host->clk_per);

	जबतक (prescaler <= 0x800) अणु
		क्रम (भागider = 1; भागider <= 0xF; भागider++) अणु
			पूर्णांक x;

			x = (clk_in / (भागider + 1));

			अगर (prescaler)
				x /= (prescaler * 2);

			अगर (x <= clk_ios)
				अवरोध;
		पूर्ण
		अगर (भागider < 0x10)
			अवरोध;

		अगर (prescaler == 0)
			prescaler = 1;
		अन्यथा
			prescaler <<= 1;
	पूर्ण

	mxcmci_ग_लिखोw(host, (prescaler << 4) | भागider, MMC_REG_CLK_RATE);

	dev_dbg(mmc_dev(host->mmc), "scaler: %d divider: %d in: %d out: %d\n",
			prescaler, भागider, clk_in, clk_ios);
पूर्ण

अटल पूर्णांक mxcmci_setup_dma(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mxcmci_host *host = mmc_priv(mmc);
	काष्ठा dma_slave_config *config = &host->dma_slave_config;

	config->dst_addr = host->phys_base + MMC_REG_BUFFER_ACCESS;
	config->src_addr = host->phys_base + MMC_REG_BUFFER_ACCESS;
	config->dst_addr_width = 4;
	config->src_addr_width = 4;
	config->dst_maxburst = host->burstlen;
	config->src_maxburst = host->burstlen;
	config->device_fc = false;

	वापस dmaengine_slave_config(host->dma, config);
पूर्ण

अटल व्योम mxcmci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mxcmci_host *host = mmc_priv(mmc);
	पूर्णांक burstlen, ret;

	/*
	 * use burstlen of 64 (16 words) in 4 bit mode (--> reg value  0)
	 * use burstlen of 16 (4 words) in 1 bit mode (--> reg value 16)
	 */
	अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		burstlen = 16;
	अन्यथा
		burstlen = 4;

	अगर (mxcmci_use_dma(host) && burstlen != host->burstlen) अणु
		host->burstlen = burstlen;
		ret = mxcmci_setup_dma(mmc);
		अगर (ret) अणु
			dev_err(mmc_dev(host->mmc),
				"failed to config DMA channel. Falling back to PIO\n");
			dma_release_channel(host->dma);
			host->करो_dma = 0;
			host->dma = शून्य;
		पूर्ण
	पूर्ण

	अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		host->cmdat |= CMD_DAT_CONT_BUS_WIDTH_4;
	अन्यथा
		host->cmdat &= ~CMD_DAT_CONT_BUS_WIDTH_4;

	अगर (host->घातer_mode != ios->घातer_mode) अणु
		host->घातer_mode = ios->घातer_mode;
		mxcmci_set_घातer(host, ios->vdd);

		अगर (ios->घातer_mode == MMC_POWER_ON)
			host->cmdat |= CMD_DAT_CONT_INIT;
	पूर्ण

	अगर (ios->घड़ी) अणु
		mxcmci_set_clk_rate(host, ios->घड़ी);
		mxcmci_ग_लिखोw(host, STR_STP_CLK_START_CLK, MMC_REG_STR_STP_CLK);
	पूर्ण अन्यथा अणु
		mxcmci_ग_लिखोw(host, STR_STP_CLK_STOP_CLK, MMC_REG_STR_STP_CLK);
	पूर्ण

	host->घड़ी = ios->घड़ी;
पूर्ण

अटल irqवापस_t mxcmci_detect_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mmc_host *mmc = data;

	dev_dbg(mmc_dev(mmc), "%s\n", __func__);

	mmc_detect_change(mmc, msecs_to_jअगरfies(250));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxcmci_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mxcmci_host *host = mmc_priv(mmc);

	अगर (host->pdata && host->pdata->get_ro)
		वापस !!host->pdata->get_ro(mmc_dev(mmc));
	/*
	 * If board करोesn't support पढ़ो only detection (no mmc_gpio
	 * context or gpio is invalid), then let the mmc core decide
	 * what to करो.
	 */
	वापस mmc_gpio_get_ro(mmc);
पूर्ण

अटल व्योम mxcmci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा mxcmci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u32 पूर्णांक_cntr;

	spin_lock_irqsave(&host->lock, flags);
	host->use_sdio = enable;
	पूर्णांक_cntr = mxcmci_पढ़ोl(host, MMC_REG_INT_CNTR);

	अगर (enable)
		पूर्णांक_cntr |= INT_SDIO_IRQ_EN;
	अन्यथा
		पूर्णांक_cntr &= ~INT_SDIO_IRQ_EN;

	mxcmci_ग_लिखोl(host, पूर्णांक_cntr, MMC_REG_INT_CNTR);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम mxcmci_init_card(काष्ठा mmc_host *host, काष्ठा mmc_card *card)
अणु
	काष्ठा mxcmci_host *mxcmci = mmc_priv(host);

	/*
	 * MX3 SoCs have a silicon bug which corrupts CRC calculation of
	 * multi-block transfers when connected SDIO peripheral करोesn't
	 * drive the BUSY line as required by the specs.
	 * One way to prevent this is to only allow 1-bit transfers.
	 */

	अगर (is_imx31_mmc(mxcmci) && card->type == MMC_TYPE_SDIO)
		host->caps &= ~MMC_CAP_4_BIT_DATA;
	अन्यथा
		host->caps |= MMC_CAP_4_BIT_DATA;
पूर्ण

अटल bool filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा mxcmci_host *host = param;

	अगर (!imx_dma_is_general_purpose(chan))
		वापस false;

	chan->निजी = &host->dma_data;

	वापस true;
पूर्ण

अटल व्योम mxcmci_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा mxcmci_host *host = from_समयr(host, t, watchकरोg);
	काष्ठा mmc_request *req = host->req;
	अचिन्हित पूर्णांक stat = mxcmci_पढ़ोl(host, MMC_REG_STATUS);

	अगर (host->dma_dir == DMA_FROM_DEVICE) अणु
		dmaengine_terminate_all(host->dma);
		dev_err(mmc_dev(host->mmc),
			"%s: read time out (status = 0x%08x)\n",
			__func__, stat);
	पूर्ण अन्यथा अणु
		dev_err(mmc_dev(host->mmc),
			"%s: write time out (status = 0x%08x)\n",
			__func__, stat);
		mxcmci_softreset(host);
	पूर्ण

	/* Mark transfer as erroneus and inक्रमm the upper layers */

	अगर (host->data)
		host->data->error = -ETIMEDOUT;
	host->req = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;
	mmc_request_करोne(host->mmc, req);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mxcmci_ops = अणु
	.request		= mxcmci_request,
	.set_ios		= mxcmci_set_ios,
	.get_ro			= mxcmci_get_ro,
	.enable_sdio_irq	= mxcmci_enable_sdio_irq,
	.init_card		= mxcmci_init_card,
पूर्ण;

अटल पूर्णांक mxcmci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा mxcmci_host *host;
	काष्ठा resource *res;
	पूर्णांक ret = 0, irq;
	bool dat3_card_detect = false;
	dma_cap_mask_t mask;
	काष्ठा imxmmc_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;

	pr_info("i.MX/MPC512x SDHC driver\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mmc = mmc_alloc_host(माप(*host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);

	host->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ out_मुक्त;
	पूर्ण

	host->phys_base = res->start;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ out_मुक्त;
	mmc->ops = &mxcmci_ops;

	/* For devicetree parsing, the bus width is पढ़ो from devicetree */
	अगर (pdata)
		mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
	अन्यथा
		mmc->caps |= MMC_CAP_SDIO_IRQ;

	/* MMC core transfer sizes tunable parameters */
	mmc->max_blk_size = 2048;
	mmc->max_blk_count = 65535;
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_seg_size = mmc->max_req_size;

	host->devtype = (क्रमागत mxcmci_type)of_device_get_match_data(&pdev->dev);

	/* adjust max_segs after devtype detection */
	अगर (!is_mpc512x_mmc(host))
		mmc->max_segs = 64;

	host->mmc = mmc;
	host->pdata = pdata;
	spin_lock_init(&host->lock);

	अगर (pdata)
		dat3_card_detect = pdata->dat3_card_detect;
	अन्यथा अगर (mmc_card_is_removable(mmc)
			&& !of_property_पढ़ो_bool(pdev->dev.of_node, "cd-gpios"))
		dat3_card_detect = true;

	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (!mmc->ocr_avail) अणु
		अगर (pdata && pdata->ocr_avail)
			mmc->ocr_avail = pdata->ocr_avail;
		अन्यथा
			mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;
	पूर्ण

	अगर (dat3_card_detect)
		host->शेष_irq_mask =
			INT_CARD_INSERTION_EN | INT_CARD_REMOVAL_EN;
	अन्यथा
		host->शेष_irq_mask = 0;

	host->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(host->clk_ipg)) अणु
		ret = PTR_ERR(host->clk_ipg);
		जाओ out_मुक्त;
	पूर्ण

	host->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(host->clk_per)) अणु
		ret = PTR_ERR(host->clk_per);
		जाओ out_मुक्त;
	पूर्ण

	ret = clk_prepare_enable(host->clk_per);
	अगर (ret)
		जाओ out_मुक्त;

	ret = clk_prepare_enable(host->clk_ipg);
	अगर (ret)
		जाओ out_clk_per_put;

	mxcmci_softreset(host);

	host->rev_no = mxcmci_पढ़ोw(host, MMC_REG_REV_NO);
	अगर (host->rev_no != 0x400) अणु
		ret = -ENODEV;
		dev_err(mmc_dev(host->mmc), "wrong rev.no. 0x%08x. aborting.\n",
			host->rev_no);
		जाओ out_clk_put;
	पूर्ण

	mmc->f_min = clk_get_rate(host->clk_per) >> 16;
	mmc->f_max = clk_get_rate(host->clk_per) >> 1;

	/* recommended in data sheet */
	mxcmci_ग_लिखोw(host, 0x2db4, MMC_REG_READ_TO);

	mxcmci_ग_लिखोl(host, host->शेष_irq_mask, MMC_REG_INT_CNTR);

	अगर (!host->pdata) अणु
		host->dma = dma_request_chan(&pdev->dev, "rx-tx");
		अगर (IS_ERR(host->dma)) अणु
			अगर (PTR_ERR(host->dma) == -EPROBE_DEFER) अणु
				ret = -EPROBE_DEFER;
				जाओ out_clk_put;
			पूर्ण

			/* Ignore errors to fall back to PIO mode */
			host->dma = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
		अगर (res) अणु
			host->dmareq = res->start;
			host->dma_data.peripheral_type = IMX_DMATYPE_SDHC;
			host->dma_data.priority = DMA_PRIO_LOW;
			host->dma_data.dma_request = host->dmareq;
			dma_cap_zero(mask);
			dma_cap_set(DMA_SLAVE, mask);
			host->dma = dma_request_channel(mask, filter, host);
		पूर्ण
	पूर्ण
	अगर (host->dma)
		mmc->max_seg_size = dma_get_max_seg_size(
				host->dma->device->dev);
	अन्यथा
		dev_info(mmc_dev(host->mmc), "dma not available. Using PIO\n");

	INIT_WORK(&host->datawork, mxcmci_datawork);

	ret = devm_request_irq(&pdev->dev, irq, mxcmci_irq, 0,
			       dev_name(&pdev->dev), host);
	अगर (ret)
		जाओ out_मुक्त_dma;

	platक्रमm_set_drvdata(pdev, mmc);

	अगर (host->pdata && host->pdata->init) अणु
		ret = host->pdata->init(&pdev->dev, mxcmci_detect_irq,
				host->mmc);
		अगर (ret)
			जाओ out_मुक्त_dma;
	पूर्ण

	समयr_setup(&host->watchकरोg, mxcmci_watchकरोg, 0);

	mmc_add_host(mmc);

	वापस 0;

out_मुक्त_dma:
	अगर (host->dma)
		dma_release_channel(host->dma);

out_clk_put:
	clk_disable_unprepare(host->clk_ipg);
out_clk_per_put:
	clk_disable_unprepare(host->clk_per);

out_मुक्त:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक mxcmci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc = platक्रमm_get_drvdata(pdev);
	काष्ठा mxcmci_host *host = mmc_priv(mmc);

	mmc_हटाओ_host(mmc);

	अगर (host->pdata && host->pdata->निकास)
		host->pdata->निकास(&pdev->dev, mmc);

	अगर (host->dma)
		dma_release_channel(host->dma);

	clk_disable_unprepare(host->clk_per);
	clk_disable_unprepare(host->clk_ipg);

	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mxcmci_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा mxcmci_host *host = mmc_priv(mmc);

	clk_disable_unprepare(host->clk_per);
	clk_disable_unprepare(host->clk_ipg);
	वापस 0;
पूर्ण

अटल पूर्णांक mxcmci_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा mxcmci_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	ret = clk_prepare_enable(host->clk_per);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(host->clk_ipg);
	अगर (ret)
		clk_disable_unprepare(host->clk_per);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mxcmci_pm_ops, mxcmci_suspend, mxcmci_resume);

अटल काष्ठा platक्रमm_driver mxcmci_driver = अणु
	.probe		= mxcmci_probe,
	.हटाओ		= mxcmci_हटाओ,
	.driver		= अणु
		.name		= DRIVER_NAME,
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &mxcmci_pm_ops,
		.of_match_table	= mxcmci_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(mxcmci_driver);

MODULE_DESCRIPTION("i.MX Multimedia Card Interface Driver");
MODULE_AUTHOR("Sascha Hauer, Pengutronix");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxc-mmc");
