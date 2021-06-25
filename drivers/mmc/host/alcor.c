<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Oleksij Rempel <linux@rempel-privat.de>
 *
 * Driver क्रम Alcor Micro AU6601 and AU6621 controllers
 */

/* Note: this driver was created without any करोcumentation. Based
 * on snअगरfing, testing and in some हालs mimic of original driver.
 * As soon as some one with करोcumentation or more experience in SD/MMC, or
 * reverse engineering then me, please review this driver and question every
 * thing what I did. 2018 Oleksij Rempel <linux@rempel-privat.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>

#समावेश <linux/alcor_pci.h>

क्रमागत alcor_cookie अणु
	COOKIE_UNMAPPED,
	COOKIE_PRE_MAPPED,
	COOKIE_MAPPED,
पूर्ण;

काष्ठा alcor_pll_conf अणु
	अचिन्हित पूर्णांक clk_src_freq;
	अचिन्हित पूर्णांक clk_src_reg;
	अचिन्हित पूर्णांक min_भाग;
	अचिन्हित पूर्णांक max_भाग;
पूर्ण;

काष्ठा alcor_sdmmc_host अणु
	काष्ठा  device *dev;
	काष्ठा alcor_pci_priv *alcor_pci;

	काष्ठा mmc_request *mrq;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data *data;
	अचिन्हित पूर्णांक dma_on:1;

	काष्ठा mutex cmd_mutex;

	काष्ठा delayed_work समयout_work;

	काष्ठा sg_mapping_iter sg_miter;	/* SG state क्रम PIO */
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक blocks;		/* reमुख्यing PIO blocks */
	पूर्णांक sg_count;

	u32			irq_status_sd;
	अचिन्हित अक्षर		cur_घातer_mode;
पूर्ण;

अटल स्थिर काष्ठा alcor_pll_conf alcor_pll_cfg[] = अणु
	/* MHZ,		CLK src,		max भाग, min भाग */
	अणु 31250000,	AU6601_CLK_31_25_MHZ,	1,	511पूर्ण,
	अणु 48000000,	AU6601_CLK_48_MHZ,	1,	511पूर्ण,
	अणु125000000,	AU6601_CLK_125_MHZ,	1,	511पूर्ण,
	अणु384000000,	AU6601_CLK_384_MHZ,	1,	511पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम alcor_rmw8(काष्ठा alcor_sdmmc_host *host, अचिन्हित पूर्णांक addr,
			       u8 clear, u8 set)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	u32 var;

	var = alcor_पढ़ो8(priv, addr);
	var &= ~clear;
	var |= set;
	alcor_ग_लिखो8(priv, var, addr);
पूर्ण

/* As soon as irqs are masked, some status updates may be missed.
 * Use this with care.
 */
अटल अंतरभूत व्योम alcor_mask_sd_irqs(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;

	alcor_ग_लिखो32(priv, 0, AU6601_REG_INT_ENABLE);
पूर्ण

अटल अंतरभूत व्योम alcor_unmask_sd_irqs(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;

	alcor_ग_लिखो32(priv, AU6601_INT_CMD_MASK | AU6601_INT_DATA_MASK |
		  AU6601_INT_CARD_INSERT | AU6601_INT_CARD_REMOVE |
		  AU6601_INT_OVER_CURRENT_ERR,
		  AU6601_REG_INT_ENABLE);
पूर्ण

अटल व्योम alcor_reset(काष्ठा alcor_sdmmc_host *host, u8 val)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	पूर्णांक i;

	alcor_ग_लिखो8(priv, val | AU6601_BUF_CTRL_RESET,
		      AU6601_REG_SW_RESET);
	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(alcor_पढ़ो8(priv, AU6601_REG_SW_RESET) & val))
			वापस;
		udelay(50);
	पूर्ण
	dev_err(host->dev, "%s: timeout\n", __func__);
पूर्ण

/*
 * Perक्रमm DMA I/O of a single page.
 */
अटल व्योम alcor_data_set_dma(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	u32 addr;

	अगर (!host->sg_count)
		वापस;

	अगर (!host->sg) अणु
		dev_err(host->dev, "have blocks, but no SG\n");
		वापस;
	पूर्ण

	अगर (!sg_dma_len(host->sg)) अणु
		dev_err(host->dev, "DMA SG len == 0\n");
		वापस;
	पूर्ण


	addr = (u32)sg_dma_address(host->sg);

	alcor_ग_लिखो32(priv, addr, AU6601_REG_SDMA_ADDR);
	host->sg = sg_next(host->sg);
	host->sg_count--;
पूर्ण

अटल व्योम alcor_trigger_data_transfer(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	काष्ठा mmc_data *data = host->data;
	u8 ctrl = 0;

	अगर (data->flags & MMC_DATA_WRITE)
		ctrl |= AU6601_DATA_WRITE;

	अगर (data->host_cookie == COOKIE_MAPPED) अणु
		/*
		 * For DMA transfers, this function is called just once,
		 * at the start of the operation. The hardware can only
		 * perक्रमm DMA I/O on a single page at a समय, so here
		 * we kick off the transfer with the first page, and expect
		 * subsequent pages to be transferred upon IRQ events
		 * indicating that the single-page DMA was completed.
		 */
		alcor_data_set_dma(host);
		ctrl |= AU6601_DATA_DMA_MODE;
		host->dma_on = 1;
		alcor_ग_लिखो32(priv, data->sg_count * 0x1000,
			       AU6601_REG_BLOCK_SIZE);
	पूर्ण अन्यथा अणु
		/*
		 * For PIO transfers, we अवरोध करोwn each operation
		 * पूर्णांकo several sector-sized transfers. When one sector has
		 * complete, the IRQ handler will call this function again
		 * to kick off the transfer of the next sector.
		 */
		alcor_ग_लिखो32(priv, data->blksz, AU6601_REG_BLOCK_SIZE);
	पूर्ण

	alcor_ग_लिखो8(priv, ctrl | AU6601_DATA_START_XFER,
		      AU6601_DATA_XFER_CTRL);
पूर्ण

अटल व्योम alcor_trf_block_pio(काष्ठा alcor_sdmmc_host *host, bool पढ़ो)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	माप_प्रकार blksize, len;
	u8 *buf;

	अगर (!host->blocks)
		वापस;

	अगर (host->dma_on) अणु
		dev_err(host->dev, "configured DMA but got PIO request.\n");
		वापस;
	पूर्ण

	अगर (!!(host->data->flags & MMC_DATA_READ) != पढ़ो) अणु
		dev_err(host->dev, "got unexpected direction %i != %i\n",
			!!(host->data->flags & MMC_DATA_READ), पढ़ो);
	पूर्ण

	अगर (!sg_miter_next(&host->sg_miter))
		वापस;

	blksize = host->data->blksz;
	len = min(host->sg_miter.length, blksize);

	dev_dbg(host->dev, "PIO, %s block size: 0x%zx\n",
		पढ़ो ? "read" : "write", blksize);

	host->sg_miter.consumed = len;
	host->blocks--;

	buf = host->sg_miter.addr;

	अगर (पढ़ो)
		ioपढ़ो32_rep(priv->iobase + AU6601_REG_BUFFER, buf, len >> 2);
	अन्यथा
		ioग_लिखो32_rep(priv->iobase + AU6601_REG_BUFFER, buf, len >> 2);

	sg_miter_stop(&host->sg_miter);
पूर्ण

अटल व्योम alcor_prepare_sg_miter(काष्ठा alcor_sdmmc_host *host)
अणु
	अचिन्हित पूर्णांक flags = SG_MITER_ATOMIC;
	काष्ठा mmc_data *data = host->data;

	अगर (data->flags & MMC_DATA_READ)
		flags |= SG_MITER_TO_SG;
	अन्यथा
		flags |= SG_MITER_FROM_SG;
	sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
पूर्ण

अटल व्योम alcor_prepare_data(काष्ठा alcor_sdmmc_host *host,
			       काष्ठा mmc_command *cmd)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	काष्ठा mmc_data *data = cmd->data;

	अगर (!data)
		वापस;


	host->data = data;
	host->data->bytes_xfered = 0;
	host->blocks = data->blocks;
	host->sg = data->sg;
	host->sg_count = data->sg_count;
	dev_dbg(host->dev, "prepare DATA: sg %i, blocks: %i\n",
			host->sg_count, host->blocks);

	अगर (data->host_cookie != COOKIE_MAPPED)
		alcor_prepare_sg_miter(host);

	alcor_ग_लिखो8(priv, 0, AU6601_DATA_XFER_CTRL);
पूर्ण

अटल व्योम alcor_send_cmd(काष्ठा alcor_sdmmc_host *host,
			   काष्ठा mmc_command *cmd, bool set_समयout)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	अचिन्हित दीर्घ समयout = 0;
	u8 ctrl = 0;

	host->cmd = cmd;
	alcor_prepare_data(host, cmd);

	dev_dbg(host->dev, "send CMD. opcode: 0x%02x, arg; 0x%08x\n",
		cmd->opcode, cmd->arg);
	alcor_ग_लिखो8(priv, cmd->opcode | 0x40, AU6601_REG_CMD_OPCODE);
	alcor_ग_लिखो32be(priv, cmd->arg, AU6601_REG_CMD_ARG);

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		ctrl = AU6601_CMD_NO_RESP;
		अवरोध;
	हाल MMC_RSP_R1:
		ctrl = AU6601_CMD_6_BYTE_CRC;
		अवरोध;
	हाल MMC_RSP_R1B:
		ctrl = AU6601_CMD_6_BYTE_CRC | AU6601_CMD_STOP_WAIT_RDY;
		अवरोध;
	हाल MMC_RSP_R2:
		ctrl = AU6601_CMD_17_BYTE_CRC;
		अवरोध;
	हाल MMC_RSP_R3:
		ctrl = AU6601_CMD_6_BYTE_WO_CRC;
		अवरोध;
	शेष:
		dev_err(host->dev, "%s: cmd->flag (0x%02x) is not valid\n",
			mmc_hostname(mmc_from_priv(host)), mmc_resp_type(cmd));
		अवरोध;
	पूर्ण

	अगर (set_समयout) अणु
		अगर (!cmd->data && cmd->busy_समयout)
			समयout = cmd->busy_समयout;
		अन्यथा
			समयout = 10000;

		schedule_delayed_work(&host->समयout_work,
				      msecs_to_jअगरfies(समयout));
	पूर्ण

	dev_dbg(host->dev, "xfer ctrl: 0x%02x; timeout: %lu\n", ctrl, समयout);
	alcor_ग_लिखो8(priv, ctrl | AU6601_CMD_START_XFER,
				 AU6601_CMD_XFER_CTRL);
पूर्ण

अटल व्योम alcor_request_complete(काष्ठा alcor_sdmmc_host *host,
				   bool cancel_समयout)
अणु
	काष्ठा mmc_request *mrq;

	/*
	 * If this work माला_लो rescheduled जबतक running, it will
	 * be run again afterwards but without any active request.
	 */
	अगर (!host->mrq)
		वापस;

	अगर (cancel_समयout)
		cancel_delayed_work(&host->समयout_work);

	mrq = host->mrq;

	host->mrq = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;
	host->dma_on = 0;

	mmc_request_करोne(mmc_from_priv(host), mrq);
पूर्ण

अटल व्योम alcor_finish_data(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा mmc_data *data;

	data = host->data;
	host->data = शून्य;
	host->dma_on = 0;

	/*
	 * The specअगरication states that the block count रेजिस्टर must
	 * be updated, but it करोes not specअगरy at what poपूर्णांक in the
	 * data flow. That makes the रेजिस्टर entirely useless to पढ़ो
	 * back so we have to assume that nothing made it to the card
	 * in the event of an error.
	 */
	अगर (data->error)
		data->bytes_xfered = 0;
	अन्यथा
		data->bytes_xfered = data->blksz * data->blocks;

	/*
	 * Need to send CMD12 अगर -
	 * a) खोलो-ended multiblock transfer (no CMD23)
	 * b) error in multiblock transfer
	 */
	अगर (data->stop &&
	    (data->error ||
	     !host->mrq->sbc)) अणु

		/*
		 * The controller needs a reset of पूर्णांकernal state machines
		 * upon error conditions.
		 */
		अगर (data->error)
			alcor_reset(host, AU6601_RESET_CMD | AU6601_RESET_DATA);

		alcor_unmask_sd_irqs(host);
		alcor_send_cmd(host, data->stop, false);
		वापस;
	पूर्ण

	alcor_request_complete(host, 1);
पूर्ण

अटल व्योम alcor_err_irq(काष्ठा alcor_sdmmc_host *host, u32 पूर्णांकmask)
अणु
	dev_dbg(host->dev, "ERR IRQ %x\n", पूर्णांकmask);

	अगर (host->cmd) अणु
		अगर (पूर्णांकmask & AU6601_INT_CMD_TIMEOUT_ERR)
			host->cmd->error = -ETIMEDOUT;
		अन्यथा
			host->cmd->error = -EILSEQ;
	पूर्ण

	अगर (host->data) अणु
		अगर (पूर्णांकmask & AU6601_INT_DATA_TIMEOUT_ERR)
			host->data->error = -ETIMEDOUT;
		अन्यथा
			host->data->error = -EILSEQ;

		host->data->bytes_xfered = 0;
	पूर्ण

	alcor_reset(host, AU6601_RESET_CMD | AU6601_RESET_DATA);
	alcor_request_complete(host, 1);
पूर्ण

अटल पूर्णांक alcor_cmd_irq_करोne(काष्ठा alcor_sdmmc_host *host, u32 पूर्णांकmask)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;

	पूर्णांकmask &= AU6601_INT_CMD_END;

	अगर (!पूर्णांकmask)
		वापस true;

	/* got CMD_END but no CMD is in progress, wake thपढ़ो an process the
	 * error
	 */
	अगर (!host->cmd)
		वापस false;

	अगर (host->cmd->flags & MMC_RSP_PRESENT) अणु
		काष्ठा mmc_command *cmd = host->cmd;

		cmd->resp[0] = alcor_पढ़ो32be(priv, AU6601_REG_CMD_RSP0);
		dev_dbg(host->dev, "RSP0: 0x%04x\n", cmd->resp[0]);
		अगर (host->cmd->flags & MMC_RSP_136) अणु
			cmd->resp[1] =
				alcor_पढ़ो32be(priv, AU6601_REG_CMD_RSP1);
			cmd->resp[2] =
				alcor_पढ़ो32be(priv, AU6601_REG_CMD_RSP2);
			cmd->resp[3] =
				alcor_पढ़ो32be(priv, AU6601_REG_CMD_RSP3);
			dev_dbg(host->dev, "RSP1,2,3: 0x%04x 0x%04x 0x%04x\n",
				cmd->resp[1], cmd->resp[2], cmd->resp[3]);
		पूर्ण

	पूर्ण

	host->cmd->error = 0;

	/* Processed actual command. */
	अगर (!host->data)
		वापस false;

	alcor_trigger_data_transfer(host);
	host->cmd = शून्य;
	वापस true;
पूर्ण

अटल व्योम alcor_cmd_irq_thपढ़ो(काष्ठा alcor_sdmmc_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांकmask &= AU6601_INT_CMD_END;

	अगर (!पूर्णांकmask)
		वापस;

	अगर (!host->cmd && पूर्णांकmask & AU6601_INT_CMD_END) अणु
		dev_dbg(host->dev, "Got command interrupt 0x%08x even though no command operation was in progress.\n",
			पूर्णांकmask);
	पूर्ण

	/* Processed actual command. */
	अगर (!host->data)
		alcor_request_complete(host, 1);
	अन्यथा
		alcor_trigger_data_transfer(host);
	host->cmd = शून्य;
पूर्ण

अटल पूर्णांक alcor_data_irq_करोne(काष्ठा alcor_sdmmc_host *host, u32 पूर्णांकmask)
अणु
	u32 पंचांगp;

	पूर्णांकmask &= AU6601_INT_DATA_MASK;

	/* nothing here to करो */
	अगर (!पूर्णांकmask)
		वापस 1;

	/* we was too fast and got DATA_END after it was processed?
	 * lets ignore it क्रम now.
	 */
	अगर (!host->data && पूर्णांकmask == AU6601_INT_DATA_END)
		वापस 1;

	/* looks like an error, so lets handle it. */
	अगर (!host->data)
		वापस 0;

	पंचांगp = पूर्णांकmask & (AU6601_INT_READ_BUF_RDY | AU6601_INT_WRITE_BUF_RDY
			 | AU6601_INT_DMA_END);
	चयन (पंचांगp) अणु
	हाल 0:
		अवरोध;
	हाल AU6601_INT_READ_BUF_RDY:
		alcor_trf_block_pio(host, true);
		वापस 1;
	हाल AU6601_INT_WRITE_BUF_RDY:
		alcor_trf_block_pio(host, false);
		वापस 1;
	हाल AU6601_INT_DMA_END:
		अगर (!host->sg_count)
			अवरोध;

		alcor_data_set_dma(host);
		अवरोध;
	शेष:
		dev_err(host->dev, "Got READ_BUF_RDY and WRITE_BUF_RDY at same time\n");
		अवरोध;
	पूर्ण

	अगर (पूर्णांकmask & AU6601_INT_DATA_END) अणु
		अगर (!host->dma_on && host->blocks) अणु
			alcor_trigger_data_transfer(host);
			वापस 1;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम alcor_data_irq_thपढ़ो(काष्ठा alcor_sdmmc_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांकmask &= AU6601_INT_DATA_MASK;

	अगर (!पूर्णांकmask)
		वापस;

	अगर (!host->data) अणु
		dev_dbg(host->dev, "Got data interrupt 0x%08x even though no data operation was in progress.\n",
			पूर्णांकmask);
		alcor_reset(host, AU6601_RESET_DATA);
		वापस;
	पूर्ण

	अगर (alcor_data_irq_करोne(host, पूर्णांकmask))
		वापस;

	अगर ((पूर्णांकmask & AU6601_INT_DATA_END) || !host->blocks ||
	    (host->dma_on && !host->sg_count))
		alcor_finish_data(host);
पूर्ण

अटल व्योम alcor_cd_irq(काष्ठा alcor_sdmmc_host *host, u32 पूर्णांकmask)
अणु
	dev_dbg(host->dev, "card %s\n",
		पूर्णांकmask & AU6601_INT_CARD_REMOVE ? "removed" : "inserted");

	अगर (host->mrq) अणु
		dev_dbg(host->dev, "cancel all pending tasks.\n");

		अगर (host->data)
			host->data->error = -ENOMEDIUM;

		अगर (host->cmd)
			host->cmd->error = -ENOMEDIUM;
		अन्यथा
			host->mrq->cmd->error = -ENOMEDIUM;

		alcor_request_complete(host, 1);
	पूर्ण

	mmc_detect_change(mmc_from_priv(host), msecs_to_jअगरfies(1));
पूर्ण

अटल irqवापस_t alcor_irq_thपढ़ो(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा alcor_sdmmc_host *host = d;
	irqवापस_t ret = IRQ_HANDLED;
	u32 पूर्णांकmask, पंचांगp;

	mutex_lock(&host->cmd_mutex);

	पूर्णांकmask = host->irq_status_sd;

	/* some thing bad */
	अगर (unlikely(!पूर्णांकmask || AU6601_INT_ALL_MASK == पूर्णांकmask)) अणु
		dev_dbg(host->dev, "unexpected IRQ: 0x%04x\n", पूर्णांकmask);
		ret = IRQ_NONE;
		जाओ निकास;
	पूर्ण

	पंचांगp = पूर्णांकmask & (AU6601_INT_CMD_MASK | AU6601_INT_DATA_MASK);
	अगर (पंचांगp) अणु
		अगर (पंचांगp & AU6601_INT_ERROR_MASK)
			alcor_err_irq(host, पंचांगp);
		अन्यथा अणु
			alcor_cmd_irq_thपढ़ो(host, पंचांगp);
			alcor_data_irq_thपढ़ो(host, पंचांगp);
		पूर्ण
		पूर्णांकmask &= ~(AU6601_INT_CMD_MASK | AU6601_INT_DATA_MASK);
	पूर्ण

	अगर (पूर्णांकmask & (AU6601_INT_CARD_INSERT | AU6601_INT_CARD_REMOVE)) अणु
		alcor_cd_irq(host, पूर्णांकmask);
		पूर्णांकmask &= ~(AU6601_INT_CARD_INSERT | AU6601_INT_CARD_REMOVE);
	पूर्ण

	अगर (पूर्णांकmask & AU6601_INT_OVER_CURRENT_ERR) अणु
		dev_warn(host->dev,
			 "warning: over current detected!\n");
		पूर्णांकmask &= ~AU6601_INT_OVER_CURRENT_ERR;
	पूर्ण

	अगर (पूर्णांकmask)
		dev_dbg(host->dev, "got not handled IRQ: 0x%04x\n", पूर्णांकmask);

निकास:
	mutex_unlock(&host->cmd_mutex);
	alcor_unmask_sd_irqs(host);
	वापस ret;
पूर्ण


अटल irqवापस_t alcor_irq(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा alcor_sdmmc_host *host = d;
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	u32 status, पंचांगp;
	irqवापस_t ret;
	पूर्णांक cmd_करोne, data_करोne;

	status = alcor_पढ़ो32(priv, AU6601_REG_INT_STATUS);
	अगर (!status)
		वापस IRQ_NONE;

	alcor_ग_लिखो32(priv, status, AU6601_REG_INT_STATUS);

	पंचांगp = status & (AU6601_INT_READ_BUF_RDY | AU6601_INT_WRITE_BUF_RDY
			| AU6601_INT_DATA_END | AU6601_INT_DMA_END
			| AU6601_INT_CMD_END);
	अगर (पंचांगp == status) अणु
		cmd_करोne = alcor_cmd_irq_करोne(host, पंचांगp);
		data_करोne = alcor_data_irq_करोne(host, पंचांगp);
		/* use fast path क्रम simple tasks */
		अगर (cmd_करोne && data_करोne) अणु
			ret = IRQ_HANDLED;
			जाओ alcor_irq_करोne;
		पूर्ण
	पूर्ण

	host->irq_status_sd = status;
	ret = IRQ_WAKE_THREAD;
	alcor_mask_sd_irqs(host);
alcor_irq_करोne:
	वापस ret;
पूर्ण

अटल व्योम alcor_set_घड़ी(काष्ठा alcor_sdmmc_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	पूर्णांक i, dअगरf = 0x7fffffff, पंचांगp_घड़ी = 0;
	u16 clk_src = 0;
	u8 clk_भाग = 0;

	अगर (घड़ी == 0) अणु
		alcor_ग_लिखो16(priv, 0, AU6601_CLK_SELECT);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(alcor_pll_cfg); i++) अणु
		अचिन्हित पूर्णांक पंचांगp_भाग, पंचांगp_dअगरf;
		स्थिर काष्ठा alcor_pll_conf *cfg = &alcor_pll_cfg[i];

		पंचांगp_भाग = DIV_ROUND_UP(cfg->clk_src_freq, घड़ी);
		अगर (cfg->min_भाग > पंचांगp_भाग || पंचांगp_भाग > cfg->max_भाग)
			जारी;

		पंचांगp_घड़ी = DIV_ROUND_UP(cfg->clk_src_freq, पंचांगp_भाग);
		पंचांगp_dअगरf = असल(घड़ी - पंचांगp_घड़ी);

		अगर (पंचांगp_dअगरf < dअगरf) अणु
			dअगरf = पंचांगp_dअगरf;
			clk_src = cfg->clk_src_reg;
			clk_भाग = पंचांगp_भाग;
		पूर्ण
	पूर्ण

	clk_src |= ((clk_भाग - 1) << 8);
	clk_src |= AU6601_CLK_ENABLE;

	dev_dbg(host->dev, "set freq %d cal freq %d, use div %d, mod %x\n",
			घड़ी, पंचांगp_घड़ी, clk_भाग, clk_src);

	alcor_ग_लिखो16(priv, clk_src, AU6601_CLK_SELECT);

पूर्ण

अटल व्योम alcor_set_timing(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);

	अगर (ios->timing == MMC_TIMING_LEGACY) अणु
		alcor_rmw8(host, AU6601_CLK_DELAY,
			    AU6601_CLK_POSITIVE_EDGE_ALL, 0);
	पूर्ण अन्यथा अणु
		alcor_rmw8(host, AU6601_CLK_DELAY,
			    0, AU6601_CLK_POSITIVE_EDGE_ALL);
	पूर्ण
पूर्ण

अटल व्योम alcor_set_bus_width(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;

	अगर (ios->bus_width == MMC_BUS_WIDTH_1) अणु
		alcor_ग_लिखो8(priv, 0, AU6601_REG_BUS_CTRL);
	पूर्ण अन्यथा अगर (ios->bus_width == MMC_BUS_WIDTH_4) अणु
		alcor_ग_लिखो8(priv, AU6601_BUS_WIDTH_4BIT,
			      AU6601_REG_BUS_CTRL);
	पूर्ण अन्यथा
		dev_err(host->dev, "Unknown BUS mode\n");

पूर्ण

अटल पूर्णांक alcor_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	u8 status;

	/* Check whether dat[0:3] low */
	status = alcor_पढ़ो8(priv, AU6601_DATA_PIN_STATE);

	वापस !(status & AU6601_BUS_STAT_DAT_MASK);
पूर्ण

अटल पूर्णांक alcor_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	u8 detect;

	detect = alcor_पढ़ो8(priv, AU6601_DETECT_STATUS)
		& AU6601_DETECT_STATUS_M;
	/* check अगर card is present then send command and data */
	वापस (detect == AU6601_SD_DETECTED);
पूर्ण

अटल पूर्णांक alcor_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	u8 status;

	/* get ग_लिखो protect pin status */
	status = alcor_पढ़ो8(priv, AU6601_INTERFACE_MODE_CTRL);

	वापस !!(status & AU6601_SD_CARD_WP);
पूर्ण

अटल व्योम alcor_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);

	mutex_lock(&host->cmd_mutex);

	host->mrq = mrq;

	/* check अगर card is present then send command and data */
	अगर (alcor_get_cd(mmc))
		alcor_send_cmd(host, mrq->cmd, true);
	अन्यथा अणु
		mrq->cmd->error = -ENOMEDIUM;
		alcor_request_complete(host, 1);
	पूर्ण

	mutex_unlock(&host->cmd_mutex);
पूर्ण

अटल व्योम alcor_pre_req(काष्ठा mmc_host *mmc,
			   काष्ठा mmc_request *mrq)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, sg_len;

	अगर (!data || !cmd)
		वापस;

	data->host_cookie = COOKIE_UNMAPPED;

	/* FIXME: looks like the DMA engine works only with CMD18 */
	अगर (cmd->opcode != MMC_READ_MULTIPLE_BLOCK
			&& cmd->opcode != MMC_WRITE_MULTIPLE_BLOCK)
		वापस;
	/*
	 * We करोn't करो DMA on "complex" transfers, i.e. with
	 * non-word-aligned buffers or lengths. A future improvement
	 * could be made to use temporary DMA bounce-buffers when these
	 * requirements are not met.
	 *
	 * Also, we करोn't bother with all the DMA setup overhead क्रम
	 * लघु transfers.
	 */
	अगर (data->blocks * data->blksz < AU6601_MAX_DMA_BLOCK_SIZE)
		वापस;

	अगर (data->blksz & 3)
		वापस;

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		अगर (sg->length != AU6601_MAX_DMA_BLOCK_SIZE)
			वापस;
		अगर (sg->offset != 0)
			वापस;
	पूर्ण

	/* This data might be unmapped at this समय */

	sg_len = dma_map_sg(host->dev, data->sg, data->sg_len,
			    mmc_get_dma_dir(data));
	अगर (sg_len)
		data->host_cookie = COOKIE_MAPPED;

	data->sg_count = sg_len;
पूर्ण

अटल व्योम alcor_post_req(काष्ठा mmc_host *mmc,
			    काष्ठा mmc_request *mrq,
			    पूर्णांक err)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस;

	अगर (data->host_cookie == COOKIE_MAPPED) अणु
		dma_unmap_sg(host->dev,
			     data->sg,
			     data->sg_len,
			     mmc_get_dma_dir(data));
	पूर्ण

	data->host_cookie = COOKIE_UNMAPPED;
पूर्ण

अटल व्योम alcor_set_घातer_mode(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		alcor_set_घड़ी(host, ios->घड़ी);
		/* set all pins to input */
		alcor_ग_लिखो8(priv, 0, AU6601_OUTPUT_ENABLE);
		/* turn of VDD */
		alcor_ग_लिखो8(priv, 0, AU6601_POWER_CONTROL);
		अवरोध;
	हाल MMC_POWER_UP:
		अवरोध;
	हाल MMC_POWER_ON:
		/* This is most trickiest part. The order and timings of
		 * inकाष्ठाions seems to play important role. Any changes may
		 * confuse पूर्णांकernal state engine अगर this HW.
		 * FIXME: If we will ever get access to करोcumentation, then this
		 * part should be reviewed again.
		 */

		/* enable SD card mode */
		alcor_ग_लिखो8(priv, AU6601_SD_CARD,
			      AU6601_ACTIVE_CTRL);
		/* set संकेत voltage to 3.3V */
		alcor_ग_लिखो8(priv, 0, AU6601_OPT);
		/* no करोcumentation about clk delay, क्रम now just try to mimic
		 * original driver.
		 */
		alcor_ग_लिखो8(priv, 0x20, AU6601_CLK_DELAY);
		/* set BUS width to 1 bit */
		alcor_ग_लिखो8(priv, 0, AU6601_REG_BUS_CTRL);
		/* set CLK first समय */
		alcor_set_घड़ी(host, ios->घड़ी);
		/* घातer on VDD */
		alcor_ग_लिखो8(priv, AU6601_SD_CARD,
			      AU6601_POWER_CONTROL);
		/* रुको until the CLK will get stable */
		mdelay(20);
		/* set CLK again, mimic original driver. */
		alcor_set_घड़ी(host, ios->घड़ी);

		/* enable output */
		alcor_ग_लिखो8(priv, AU6601_SD_CARD,
			      AU6601_OUTPUT_ENABLE);
		/* The clk will not work on au6621. We need to trigger data
		 * transfer.
		 */
		alcor_ग_लिखो8(priv, AU6601_DATA_WRITE,
			      AU6601_DATA_XFER_CTRL);
		/* configure समयout. Not clear what exactly it means. */
		alcor_ग_लिखो8(priv, 0x7d, AU6601_TIME_OUT_CTRL);
		mdelay(100);
		अवरोध;
	शेष:
		dev_err(host->dev, "Unknown power parameter\n");
	पूर्ण
पूर्ण

अटल व्योम alcor_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);

	mutex_lock(&host->cmd_mutex);

	dev_dbg(host->dev, "set ios. bus width: %x, power mode: %x\n",
		ios->bus_width, ios->घातer_mode);

	अगर (ios->घातer_mode != host->cur_घातer_mode) अणु
		alcor_set_घातer_mode(mmc, ios);
		host->cur_घातer_mode = ios->घातer_mode;
	पूर्ण अन्यथा अणु
		alcor_set_timing(mmc, ios);
		alcor_set_bus_width(mmc, ios);
		alcor_set_घड़ी(host, ios->घड़ी);
	पूर्ण

	mutex_unlock(&host->cmd_mutex);
पूर्ण

अटल पूर्णांक alcor_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
				       काष्ठा mmc_ios *ios)
अणु
	काष्ठा alcor_sdmmc_host *host = mmc_priv(mmc);

	mutex_lock(&host->cmd_mutex);

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		alcor_rmw8(host, AU6601_OPT, AU6601_OPT_SD_18V, 0);
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		alcor_rmw8(host, AU6601_OPT, 0, AU6601_OPT_SD_18V);
		अवरोध;
	शेष:
		/* No संकेत voltage चयन required */
		अवरोध;
	पूर्ण

	mutex_unlock(&host->cmd_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops alcor_sdc_ops = अणु
	.card_busy	= alcor_card_busy,
	.get_cd		= alcor_get_cd,
	.get_ro		= alcor_get_ro,
	.post_req	= alcor_post_req,
	.pre_req	= alcor_pre_req,
	.request	= alcor_request,
	.set_ios	= alcor_set_ios,
	.start_संकेत_voltage_चयन = alcor_संकेत_voltage_चयन,
पूर्ण;

अटल व्योम alcor_समयout_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *d = to_delayed_work(work);
	काष्ठा alcor_sdmmc_host *host = container_of(d, काष्ठा alcor_sdmmc_host,
						समयout_work);
	mutex_lock(&host->cmd_mutex);

	dev_dbg(host->dev, "triggered timeout\n");
	अगर (host->mrq) अणु
		dev_err(host->dev, "Timeout waiting for hardware interrupt.\n");

		अगर (host->data) अणु
			host->data->error = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			अगर (host->cmd)
				host->cmd->error = -ETIMEDOUT;
			अन्यथा
				host->mrq->cmd->error = -ETIMEDOUT;
		पूर्ण

		alcor_reset(host, AU6601_RESET_CMD | AU6601_RESET_DATA);
		alcor_request_complete(host, 0);
	पूर्ण

	mutex_unlock(&host->cmd_mutex);
पूर्ण

अटल व्योम alcor_hw_init(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;
	काष्ठा alcor_dev_cfg *cfg = priv->cfg;

	/* FIXME: This part is a mimics HW init of original driver.
	 * If we will ever get access to करोcumentation, then this part
	 * should be reviewed again.
	 */

	/* reset command state engine */
	alcor_reset(host, AU6601_RESET_CMD);

	alcor_ग_लिखो8(priv, 0, AU6601_DMA_BOUNDARY);
	/* enable sd card mode */
	alcor_ग_लिखो8(priv, AU6601_SD_CARD, AU6601_ACTIVE_CTRL);

	/* set BUS width to 1 bit */
	alcor_ग_लिखो8(priv, 0, AU6601_REG_BUS_CTRL);

	/* reset data state engine */
	alcor_reset(host, AU6601_RESET_DATA);
	/* Not sure अगर a vooकरोo with AU6601_DMA_BOUNDARY is really needed */
	alcor_ग_लिखो8(priv, 0, AU6601_DMA_BOUNDARY);

	alcor_ग_लिखो8(priv, 0, AU6601_INTERFACE_MODE_CTRL);
	/* not clear what we are करोing here. */
	alcor_ग_लिखो8(priv, 0x44, AU6601_PAD_DRIVE0);
	alcor_ग_लिखो8(priv, 0x44, AU6601_PAD_DRIVE1);
	alcor_ग_लिखो8(priv, 0x00, AU6601_PAD_DRIVE2);

	/* क्रम 6601 - dma_boundary; क्रम 6621 - dma_page_cnt
	 * exact meaning of this रेजिस्टर is not clear.
	 */
	alcor_ग_लिखो8(priv, cfg->dma, AU6601_DMA_BOUNDARY);

	/* make sure all pins are set to input and VDD is off */
	alcor_ग_लिखो8(priv, 0, AU6601_OUTPUT_ENABLE);
	alcor_ग_लिखो8(priv, 0, AU6601_POWER_CONTROL);

	alcor_ग_लिखो8(priv, AU6601_DETECT_EN, AU6601_DETECT_STATUS);
	/* now we should be safe to enable IRQs */
	alcor_unmask_sd_irqs(host);
पूर्ण

अटल व्योम alcor_hw_uninit(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा alcor_pci_priv *priv = host->alcor_pci;

	alcor_mask_sd_irqs(host);
	alcor_reset(host, AU6601_RESET_CMD | AU6601_RESET_DATA);

	alcor_ग_लिखो8(priv, 0, AU6601_DETECT_STATUS);

	alcor_ग_लिखो8(priv, 0, AU6601_OUTPUT_ENABLE);
	alcor_ग_लिखो8(priv, 0, AU6601_POWER_CONTROL);

	alcor_ग_लिखो8(priv, 0, AU6601_OPT);
पूर्ण

अटल व्योम alcor_init_mmc(काष्ठा alcor_sdmmc_host *host)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);

	mmc->f_min = AU6601_MIN_CLOCK;
	mmc->f_max = AU6601_MAX_CLOCK;
	mmc->ocr_avail = MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED
		| MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50
		| MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_DDR50;
	mmc->caps2 = MMC_CAP2_NO_SDIO;
	mmc->ops = &alcor_sdc_ops;

	/* The hardware करोes DMA data transfer of 4096 bytes to/from a single
	 * buffer address. Scatterlists are not supported at the hardware
	 * level, however we can work with them at the driver level,
	 * provided that each segment is exactly 4096 bytes in size.
	 * Upon DMA completion of a single segment (संकेतled via IRQ), we
	 * immediately proceed to transfer the next segment from the
	 * scatterlist.
	 *
	 * The overall request is limited to 240 sectors, matching the
	 * original venकरोr driver.
	 */
	mmc->max_segs = AU6601_MAX_DMA_SEGMENTS;
	mmc->max_seg_size = AU6601_MAX_DMA_BLOCK_SIZE;
	mmc->max_blk_count = 240;
	mmc->max_req_size = mmc->max_blk_count * mmc->max_blk_size;
	dma_set_max_seg_size(host->dev, mmc->max_seg_size);
पूर्ण

अटल पूर्णांक alcor_pci_sdmmc_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा alcor_pci_priv *priv = pdev->dev.platक्रमm_data;
	काष्ठा mmc_host *mmc;
	काष्ठा alcor_sdmmc_host *host;
	पूर्णांक ret;

	mmc = mmc_alloc_host(माप(*host), &pdev->dev);
	अगर (!mmc) अणु
		dev_err(&pdev->dev, "Can't allocate MMC\n");
		वापस -ENOMEM;
	पूर्ण

	host = mmc_priv(mmc);
	host->dev = &pdev->dev;
	host->cur_घातer_mode = MMC_POWER_UNDEFINED;
	host->alcor_pci = priv;

	/* make sure irqs are disabled */
	alcor_ग_लिखो32(priv, 0, AU6601_REG_INT_ENABLE);
	alcor_ग_लिखो32(priv, 0, AU6601_MS_INT_ENABLE);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, priv->irq,
			alcor_irq, alcor_irq_thपढ़ो, IRQF_SHARED,
			DRV_NAME_ALCOR_PCI_SDMMC, host);

	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get irq for data line\n");
		जाओ मुक्त_host;
	पूर्ण

	mutex_init(&host->cmd_mutex);
	INIT_DELAYED_WORK(&host->समयout_work, alcor_समयout_समयr);

	alcor_init_mmc(host);
	alcor_hw_init(host);

	dev_set_drvdata(&pdev->dev, host);
	mmc_add_host(mmc);
	वापस 0;

मुक्त_host:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक alcor_pci_sdmmc_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा alcor_sdmmc_host *host = dev_get_drvdata(&pdev->dev);
	काष्ठा mmc_host *mmc = mmc_from_priv(host);

	अगर (cancel_delayed_work_sync(&host->समयout_work))
		alcor_request_complete(host, 0);

	alcor_hw_uninit(host);
	mmc_हटाओ_host(mmc);
	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक alcor_pci_sdmmc_suspend(काष्ठा device *dev)
अणु
	काष्ठा alcor_sdmmc_host *host = dev_get_drvdata(dev);

	अगर (cancel_delayed_work_sync(&host->समयout_work))
		alcor_request_complete(host, 0);

	alcor_hw_uninit(host);

	वापस 0;
पूर्ण

अटल पूर्णांक alcor_pci_sdmmc_resume(काष्ठा device *dev)
अणु
	काष्ठा alcor_sdmmc_host *host = dev_get_drvdata(dev);

	alcor_hw_init(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(alcor_mmc_pm_ops, alcor_pci_sdmmc_suspend,
			 alcor_pci_sdmmc_resume);

अटल स्थिर काष्ठा platक्रमm_device_id alcor_pci_sdmmc_ids[] = अणु
	अणु
		.name = DRV_NAME_ALCOR_PCI_SDMMC,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, alcor_pci_sdmmc_ids);

अटल काष्ठा platक्रमm_driver alcor_pci_sdmmc_driver = अणु
	.probe		= alcor_pci_sdmmc_drv_probe,
	.हटाओ		= alcor_pci_sdmmc_drv_हटाओ,
	.id_table	= alcor_pci_sdmmc_ids,
	.driver		= अणु
		.name	= DRV_NAME_ALCOR_PCI_SDMMC,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &alcor_mmc_pm_ops
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(alcor_pci_sdmmc_driver);

MODULE_AUTHOR("Oleksij Rempel <linux@rempel-privat.de>");
MODULE_DESCRIPTION("PCI driver for Alcor Micro AU6601 Secure Digital Host Controller Interface");
MODULE_LICENSE("GPL");
