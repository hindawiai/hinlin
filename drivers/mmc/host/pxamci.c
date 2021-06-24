<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/host/pxa.c - PXA MMCI driver
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *
 *  This hardware is really sick:
 *   - No way to clear पूर्णांकerrupts.
 *   - Have to turn off the घड़ी whenever we touch the device.
 *   - Doesn't tell you how many data blocks were transferred.
 *  Yuck!
 *
 *	1 and 3 byte data transfers not supported
 *	max block length up to 1023
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gfp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/sizes.h>

#समावेश <mach/hardware.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>

#समावेश "pxamci.h"

#घोषणा DRIVER_NAME	"pxa2xx-mci"

#घोषणा NR_SG	1
#घोषणा CLKRT_OFF	(~0)

#घोषणा mmc_has_26MHz()		(cpu_is_pxa300() || cpu_is_pxa310() \
				|| cpu_is_pxa935())

काष्ठा pxamci_host अणु
	काष्ठा mmc_host		*mmc;
	spinlock_t		lock;
	काष्ठा resource		*res;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	अचिन्हित दीर्घ		clkrate;
	अचिन्हित पूर्णांक		clkrt;
	अचिन्हित पूर्णांक		cmdat;
	अचिन्हित पूर्णांक		imask;
	अचिन्हित पूर्णांक		घातer_mode;
	अचिन्हित दीर्घ		detect_delay_ms;
	bool			use_ro_gpio;
	काष्ठा gpio_desc	*घातer;
	काष्ठा pxamci_platक्रमm_data *pdata;

	काष्ठा mmc_request	*mrq;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_data		*data;

	काष्ठा dma_chan		*dma_chan_rx;
	काष्ठा dma_chan		*dma_chan_tx;
	dma_cookie_t		dma_cookie;
	अचिन्हित पूर्णांक		dma_len;
	अचिन्हित पूर्णांक		dma_dir;
पूर्ण;

अटल पूर्णांक pxamci_init_ocr(काष्ठा pxamci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;

	ret = mmc_regulator_get_supply(mmc);
	अगर (ret < 0)
		वापस ret;

	अगर (IS_ERR(mmc->supply.vmmc)) अणु
		/* fall-back to platक्रमm data */
		mmc->ocr_avail = host->pdata ?
			host->pdata->ocr_mask :
			MMC_VDD_32_33 | MMC_VDD_33_34;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pxamci_set_घातer(काष्ठा pxamci_host *host,
				    अचिन्हित अक्षर घातer_mode,
				    अचिन्हित पूर्णांक vdd)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा regulator *supply = mmc->supply.vmmc;

	अगर (!IS_ERR(supply))
		वापस mmc_regulator_set_ocr(mmc, supply, vdd);

	अगर (host->घातer) अणु
		bool on = !!((1 << vdd) & host->pdata->ocr_mask);
		gpiod_set_value(host->घातer, on);
	पूर्ण

	अगर (host->pdata && host->pdata->setघातer)
		वापस host->pdata->setघातer(mmc_dev(host->mmc), vdd);

	वापस 0;
पूर्ण

अटल व्योम pxamci_stop_घड़ी(काष्ठा pxamci_host *host)
अणु
	अगर (पढ़ोl(host->base + MMC_STAT) & STAT_CLK_EN) अणु
		अचिन्हित दीर्घ समयout = 10000;
		अचिन्हित पूर्णांक v;

		ग_लिखोl(STOP_CLOCK, host->base + MMC_STRPCL);

		करो अणु
			v = पढ़ोl(host->base + MMC_STAT);
			अगर (!(v & STAT_CLK_EN))
				अवरोध;
			udelay(1);
		पूर्ण जबतक (समयout--);

		अगर (v & STAT_CLK_EN)
			dev_err(mmc_dev(host->mmc), "unable to stop clock\n");
	पूर्ण
पूर्ण

अटल व्योम pxamci_enable_irq(काष्ठा pxamci_host *host, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	host->imask &= ~mask;
	ग_लिखोl(host->imask, host->base + MMC_I_MASK);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम pxamci_disable_irq(काष्ठा pxamci_host *host, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	host->imask |= mask;
	ग_लिखोl(host->imask, host->base + MMC_I_MASK);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम pxamci_dma_irq(व्योम *param);

अटल व्योम pxamci_setup_data(काष्ठा pxamci_host *host, काष्ठा mmc_data *data)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	क्रमागत dma_transfer_direction direction;
	काष्ठा dma_slave_config	config;
	काष्ठा dma_chan *chan;
	अचिन्हित पूर्णांक nob = data->blocks;
	अचिन्हित दीर्घ दीर्घ clks;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक ret;

	host->data = data;

	ग_लिखोl(nob, host->base + MMC_NOB);
	ग_लिखोl(data->blksz, host->base + MMC_BLKLEN);

	clks = (अचिन्हित दीर्घ दीर्घ)data->समयout_ns * host->clkrate;
	करो_भाग(clks, 1000000000UL);
	समयout = (अचिन्हित पूर्णांक)clks + (data->समयout_clks << host->clkrt);
	ग_लिखोl((समयout + 255) / 256, host->base + MMC_RDTO);

	स_रखो(&config, 0, माप(config));
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	config.src_addr = host->res->start + MMC_RXFIFO;
	config.dst_addr = host->res->start + MMC_TXFIFO;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;

	अगर (data->flags & MMC_DATA_READ) अणु
		host->dma_dir = DMA_FROM_DEVICE;
		direction = DMA_DEV_TO_MEM;
		chan = host->dma_chan_rx;
	पूर्ण अन्यथा अणु
		host->dma_dir = DMA_TO_DEVICE;
		direction = DMA_MEM_TO_DEV;
		chan = host->dma_chan_tx;
	पूर्ण

	config.direction = direction;

	ret = dmaengine_slave_config(chan, &config);
	अगर (ret < 0) अणु
		dev_err(mmc_dev(host->mmc), "dma slave config failed\n");
		वापस;
	पूर्ण

	host->dma_len = dma_map_sg(chan->device->dev, data->sg, data->sg_len,
				   host->dma_dir);

	tx = dmaengine_prep_slave_sg(chan, data->sg, host->dma_len, direction,
				     DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(mmc_dev(host->mmc), "prep_slave_sg() failed\n");
		वापस;
	पूर्ण

	अगर (!(data->flags & MMC_DATA_READ)) अणु
		tx->callback = pxamci_dma_irq;
		tx->callback_param = host;
	पूर्ण

	host->dma_cookie = dmaengine_submit(tx);

	/*
	 * workaround क्रम erratum #91:
	 * only start DMA now अगर we are करोing a पढ़ो,
	 * otherwise we रुको until CMD/RESP has finished
	 * beक्रमe starting DMA.
	 */
	अगर (!cpu_is_pxa27x() || data->flags & MMC_DATA_READ)
		dma_async_issue_pending(chan);
पूर्ण

अटल व्योम pxamci_start_cmd(काष्ठा pxamci_host *host, काष्ठा mmc_command *cmd, अचिन्हित पूर्णांक cmdat)
अणु
	WARN_ON(host->cmd != शून्य);
	host->cmd = cmd;

	अगर (cmd->flags & MMC_RSP_BUSY)
		cmdat |= CMDAT_BUSY;

#घोषणा RSP_TYPE(x)	((x) & ~(MMC_RSP_BUSY|MMC_RSP_OPCODE))
	चयन (RSP_TYPE(mmc_resp_type(cmd))) अणु
	हाल RSP_TYPE(MMC_RSP_R1): /* r1, r1b, r6, r7 */
		cmdat |= CMDAT_RESP_SHORT;
		अवरोध;
	हाल RSP_TYPE(MMC_RSP_R3):
		cmdat |= CMDAT_RESP_R3;
		अवरोध;
	हाल RSP_TYPE(MMC_RSP_R2):
		cmdat |= CMDAT_RESP_R2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(cmd->opcode, host->base + MMC_CMD);
	ग_लिखोl(cmd->arg >> 16, host->base + MMC_ARGH);
	ग_लिखोl(cmd->arg & 0xffff, host->base + MMC_ARGL);
	ग_लिखोl(cmdat, host->base + MMC_CMDAT);
	ग_लिखोl(host->clkrt, host->base + MMC_CLKRT);

	ग_लिखोl(START_CLOCK, host->base + MMC_STRPCL);

	pxamci_enable_irq(host, END_CMD_RES);
पूर्ण

अटल व्योम pxamci_finish_request(काष्ठा pxamci_host *host, काष्ठा mmc_request *mrq)
अणु
	host->mrq = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल पूर्णांक pxamci_cmd_करोne(काष्ठा pxamci_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_command *cmd = host->cmd;
	पूर्णांक i;
	u32 v;

	अगर (!cmd)
		वापस 0;

	host->cmd = शून्य;

	/*
	 * Did I mention this is Sick.  We always need to
	 * discard the upper 8 bits of the first 16-bit word.
	 */
	v = पढ़ोl(host->base + MMC_RES) & 0xffff;
	क्रम (i = 0; i < 4; i++) अणु
		u32 w1 = पढ़ोl(host->base + MMC_RES) & 0xffff;
		u32 w2 = पढ़ोl(host->base + MMC_RES) & 0xffff;
		cmd->resp[i] = v << 24 | w1 << 8 | w2 >> 8;
		v = w2;
	पूर्ण

	अगर (stat & STAT_TIME_OUT_RESPONSE) अणु
		cmd->error = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (stat & STAT_RES_CRC_ERR && cmd->flags & MMC_RSP_CRC) अणु
		/*
		 * workaround क्रम erratum #42:
		 * Intel PXA27x Family Processor Specअगरication Update Rev 001
		 * A bogus CRC error can appear अगर the msb of a 136 bit
		 * response is a one.
		 */
		अगर (cpu_is_pxa27x() &&
		    (cmd->flags & MMC_RSP_136 && cmd->resp[0] & 0x80000000))
			pr_debug("ignoring CRC from command %d - *risky*\n", cmd->opcode);
		अन्यथा
			cmd->error = -EILSEQ;
	पूर्ण

	pxamci_disable_irq(host, END_CMD_RES);
	अगर (host->data && !cmd->error) अणु
		pxamci_enable_irq(host, DATA_TRAN_DONE);
		/*
		 * workaround क्रम erratum #91, अगर करोing ग_लिखो
		 * enable DMA late
		 */
		अगर (cpu_is_pxa27x() && host->data->flags & MMC_DATA_WRITE)
			dma_async_issue_pending(host->dma_chan_tx);
	पूर्ण अन्यथा अणु
		pxamci_finish_request(host, host->mrq);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक pxamci_data_करोne(काष्ठा pxamci_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_data *data = host->data;
	काष्ठा dma_chan *chan;

	अगर (!data)
		वापस 0;

	अगर (data->flags & MMC_DATA_READ)
		chan = host->dma_chan_rx;
	अन्यथा
		chan = host->dma_chan_tx;
	dma_unmap_sg(chan->device->dev,
		     data->sg, data->sg_len, host->dma_dir);

	अगर (stat & STAT_READ_TIME_OUT)
		data->error = -ETIMEDOUT;
	अन्यथा अगर (stat & (STAT_CRC_READ_ERROR|STAT_CRC_WRITE_ERROR))
		data->error = -EILSEQ;

	/*
	 * There appears to be a hardware design bug here.  There seems to
	 * be no way to find out how much data was transferred to the card.
	 * This means that अगर there was an error on any block, we mark all
	 * data blocks as being in error.
	 */
	अगर (!data->error)
		data->bytes_xfered = data->blocks * data->blksz;
	अन्यथा
		data->bytes_xfered = 0;

	pxamci_disable_irq(host, DATA_TRAN_DONE);

	host->data = शून्य;
	अगर (host->mrq->stop) अणु
		pxamci_stop_घड़ी(host);
		pxamci_start_cmd(host, host->mrq->stop, host->cmdat);
	पूर्ण अन्यथा अणु
		pxamci_finish_request(host, host->mrq);
	पूर्ण

	वापस 1;
पूर्ण

अटल irqवापस_t pxamci_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा pxamci_host *host = devid;
	अचिन्हित पूर्णांक ireg;
	पूर्णांक handled = 0;

	ireg = पढ़ोl(host->base + MMC_I_REG) & ~पढ़ोl(host->base + MMC_I_MASK);

	अगर (ireg) अणु
		अचिन्हित stat = पढ़ोl(host->base + MMC_STAT);

		pr_debug("PXAMCI: irq %08x stat %08x\n", ireg, stat);

		अगर (ireg & END_CMD_RES)
			handled |= pxamci_cmd_करोne(host, stat);
		अगर (ireg & DATA_TRAN_DONE)
			handled |= pxamci_data_करोne(host, stat);
		अगर (ireg & SDIO_INT) अणु
			mmc_संकेत_sdio_irq(host->mmc);
			handled = 1;
		पूर्ण
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम pxamci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा pxamci_host *host = mmc_priv(mmc);
	अचिन्हित पूर्णांक cmdat;

	WARN_ON(host->mrq != शून्य);

	host->mrq = mrq;

	pxamci_stop_घड़ी(host);

	cmdat = host->cmdat;
	host->cmdat &= ~CMDAT_INIT;

	अगर (mrq->data) अणु
		pxamci_setup_data(host, mrq->data);

		cmdat &= ~CMDAT_BUSY;
		cmdat |= CMDAT_DATAEN | CMDAT_DMAEN;
		अगर (mrq->data->flags & MMC_DATA_WRITE)
			cmdat |= CMDAT_WRITE;
	पूर्ण

	pxamci_start_cmd(host, mrq->cmd, cmdat);
पूर्ण

अटल पूर्णांक pxamci_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा pxamci_host *host = mmc_priv(mmc);

	अगर (host->use_ro_gpio)
		वापस mmc_gpio_get_ro(mmc);
	अगर (host->pdata && host->pdata->get_ro)
		वापस !!host->pdata->get_ro(mmc_dev(mmc));
	/*
	 * Board करोesn't support पढ़ो only detection; let the mmc core
	 * decide what to करो.
	 */
	वापस -ENOSYS;
पूर्ण

अटल व्योम pxamci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा pxamci_host *host = mmc_priv(mmc);

	अगर (ios->घड़ी) अणु
		अचिन्हित दीर्घ rate = host->clkrate;
		अचिन्हित पूर्णांक clk = rate / ios->घड़ी;

		अगर (host->clkrt == CLKRT_OFF)
			clk_prepare_enable(host->clk);

		अगर (ios->घड़ी == 26000000) अणु
			/* to support 26MHz */
			host->clkrt = 7;
		पूर्ण अन्यथा अणु
			/* to handle (19.5MHz, 26MHz) */
			अगर (!clk)
				clk = 1;

			/*
			 * clk might result in a lower भागisor than we
			 * desire.  check क्रम that condition and adjust
			 * as appropriate.
			 */
			अगर (rate / clk > ios->घड़ी)
				clk <<= 1;
			host->clkrt = fls(clk) - 1;
		पूर्ण

		/*
		 * we ग_लिखो clkrt on the next command
		 */
	पूर्ण अन्यथा अणु
		pxamci_stop_घड़ी(host);
		अगर (host->clkrt != CLKRT_OFF) अणु
			host->clkrt = CLKRT_OFF;
			clk_disable_unprepare(host->clk);
		पूर्ण
	पूर्ण

	अगर (host->घातer_mode != ios->घातer_mode) अणु
		पूर्णांक ret;

		host->घातer_mode = ios->घातer_mode;

		ret = pxamci_set_घातer(host, ios->घातer_mode, ios->vdd);
		अगर (ret) अणु
			dev_err(mmc_dev(mmc), "unable to set power\n");
			/*
			 * The .set_ios() function in the mmc_host_ops
			 * काष्ठा वापस व्योम, and failing to set the
			 * घातer should be rare so we prपूर्णांक an error and
			 * वापस here.
			 */
			वापस;
		पूर्ण

		अगर (ios->घातer_mode == MMC_POWER_ON)
			host->cmdat |= CMDAT_INIT;
	पूर्ण

	अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		host->cmdat |= CMDAT_SD_4DAT;
	अन्यथा
		host->cmdat &= ~CMDAT_SD_4DAT;

	dev_dbg(mmc_dev(mmc), "PXAMCI: clkrt = %x cmdat = %x\n",
		host->clkrt, host->cmdat);
पूर्ण

अटल व्योम pxamci_enable_sdio_irq(काष्ठा mmc_host *host, पूर्णांक enable)
अणु
	काष्ठा pxamci_host *pxa_host = mmc_priv(host);

	अगर (enable)
		pxamci_enable_irq(pxa_host, SDIO_INT);
	अन्यथा
		pxamci_disable_irq(pxa_host, SDIO_INT);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops pxamci_ops = अणु
	.request		= pxamci_request,
	.get_cd			= mmc_gpio_get_cd,
	.get_ro			= pxamci_get_ro,
	.set_ios		= pxamci_set_ios,
	.enable_sdio_irq	= pxamci_enable_sdio_irq,
पूर्ण;

अटल व्योम pxamci_dma_irq(व्योम *param)
अणु
	काष्ठा pxamci_host *host = param;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	काष्ठा dma_chan *chan;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	अगर (!host->data)
		जाओ out_unlock;

	अगर (host->data->flags & MMC_DATA_READ)
		chan = host->dma_chan_rx;
	अन्यथा
		chan = host->dma_chan_tx;

	status = dmaengine_tx_status(chan, host->dma_cookie, &state);

	अगर (likely(status == DMA_COMPLETE)) अणु
		ग_लिखोl(BUF_PART_FULL, host->base + MMC_PRTBUF);
	पूर्ण अन्यथा अणु
		pr_err("%s: DMA error on %s channel\n", mmc_hostname(host->mmc),
			host->data->flags & MMC_DATA_READ ? "rx" : "tx");
		host->data->error = -EIO;
		pxamci_data_करोne(host, 0);
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल irqवापस_t pxamci_detect_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा pxamci_host *host = mmc_priv(devid);

	mmc_detect_change(devid, msecs_to_jअगरfies(host->detect_delay_ms));
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa_mmc_dt_ids[] = अणु
        अणु .compatible = "marvell,pxa-mmc" पूर्ण,
        अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, pxa_mmc_dt_ids);

अटल पूर्णांक pxamci_of_init(काष्ठा platक्रमm_device *pdev,
			  काष्ठा mmc_host *mmc)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pxamci_host *host = mmc_priv(mmc);
	u32 पंचांगp;
	पूर्णांक ret;

	अगर (!np)
		वापस 0;

	/* pxa-mmc specअगरic */
	अगर (of_property_पढ़ो_u32(np, "pxa-mmc,detect-delay-ms", &पंचांगp) == 0)
		host->detect_delay_ms = पंचांगp;

	ret = mmc_of_parse(mmc);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक pxamci_of_init(काष्ठा platक्रमm_device *pdev,
			  काष्ठा mmc_host *mmc)
अणु
        वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pxamci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा pxamci_host *host = शून्य;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *r;
	पूर्णांक ret, irq;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mmc = mmc_alloc_host(माप(काष्ठा pxamci_host), dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mmc->ops = &pxamci_ops;

	/*
	 * We can करो SG-DMA, but we करोn't because we never know how much
	 * data we successfully wrote to the card.
	 */
	mmc->max_segs = NR_SG;

	/*
	 * Our hardware DMA can handle a maximum of one page per SG entry.
	 */
	mmc->max_seg_size = PAGE_SIZE;

	/*
	 * Block length रेजिस्टर is only 10 bits beक्रमe PXA27x.
	 */
	mmc->max_blk_size = cpu_is_pxa25x() ? 1023 : 2048;

	/*
	 * Block count रेजिस्टर is 16 bits.
	 */
	mmc->max_blk_count = 65535;

	ret = pxamci_of_init(pdev, mmc);
	अगर (ret)
		वापस ret;

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->pdata = pdev->dev.platक्रमm_data;
	host->clkrt = CLKRT_OFF;

	host->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		host->clk = शून्य;
		जाओ out;
	पूर्ण

	host->clkrate = clk_get_rate(host->clk);

	/*
	 * Calculate minimum घड़ी rate, rounding up.
	 */
	mmc->f_min = (host->clkrate + 63) / 64;
	mmc->f_max = (mmc_has_26MHz()) ? 26000000 : host->clkrate;

	ret = pxamci_init_ocr(host);
	अगर (ret < 0)
		वापस ret;

	mmc->caps = 0;
	host->cmdat = 0;
	अगर (!cpu_is_pxa25x()) अणु
		mmc->caps |= MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
		host->cmdat |= CMDAT_SDIO_INT_EN;
		अगर (mmc_has_26MHz())
			mmc->caps |= MMC_CAP_MMC_HIGHSPEED |
				     MMC_CAP_SD_HIGHSPEED;
	पूर्ण

	spin_lock_init(&host->lock);
	host->res = r;
	host->imask = MMC_I_MASK_ALL;

	host->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ out;
	पूर्ण

	/*
	 * Ensure that the host controller is shut करोwn, and setup
	 * with our शेषs.
	 */
	pxamci_stop_घड़ी(host);
	ग_लिखोl(0, host->base + MMC_SPI);
	ग_लिखोl(64, host->base + MMC_RESTO);
	ग_लिखोl(host->imask, host->base + MMC_I_MASK);

	ret = devm_request_irq(dev, irq, pxamci_irq, 0,
			       DRIVER_NAME, host);
	अगर (ret)
		जाओ out;

	platक्रमm_set_drvdata(pdev, mmc);

	host->dma_chan_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(host->dma_chan_rx)) अणु
		dev_err(dev, "unable to request rx dma channel\n");
		ret = PTR_ERR(host->dma_chan_rx);
		host->dma_chan_rx = शून्य;
		जाओ out;
	पूर्ण

	host->dma_chan_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(host->dma_chan_tx)) अणु
		dev_err(dev, "unable to request tx dma channel\n");
		ret = PTR_ERR(host->dma_chan_tx);
		host->dma_chan_tx = शून्य;
		जाओ out;
	पूर्ण

	अगर (host->pdata) अणु
		host->detect_delay_ms = host->pdata->detect_delay_ms;

		host->घातer = devm_gpiod_get_optional(dev, "power", GPIOD_OUT_LOW);
		अगर (IS_ERR(host->घातer)) अणु
			ret = PTR_ERR(host->घातer);
			dev_err(dev, "Failed requesting gpio_power\n");
			जाओ out;
		पूर्ण

		/* FIXME: should we pass detection delay to debounce? */
		ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0);
		अगर (ret && ret != -ENOENT) अणु
			dev_err(dev, "Failed requesting gpio_cd\n");
			जाओ out;
		पूर्ण

		अगर (!host->pdata->gpio_card_ro_invert)
			mmc->caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;

		ret = mmc_gpiod_request_ro(mmc, "wp", 0, 0);
		अगर (ret && ret != -ENOENT) अणु
			dev_err(dev, "Failed requesting gpio_ro\n");
			जाओ out;
		पूर्ण
		अगर (!ret)
			host->use_ro_gpio = true;

		अगर (host->pdata->init)
			host->pdata->init(dev, pxamci_detect_irq, mmc);

		अगर (host->घातer && host->pdata->setघातer)
			dev_warn(dev, "gpio_power and setpower() both defined\n");
		अगर (host->use_ro_gpio && host->pdata->get_ro)
			dev_warn(dev, "gpio_ro and get_ro() both defined\n");
	पूर्ण

	mmc_add_host(mmc);

	वापस 0;

out:
	अगर (host) अणु
		अगर (host->dma_chan_rx)
			dma_release_channel(host->dma_chan_rx);
		अगर (host->dma_chan_tx)
			dma_release_channel(host->dma_chan_tx);
	पूर्ण
	अगर (mmc)
		mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक pxamci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc = platक्रमm_get_drvdata(pdev);

	अगर (mmc) अणु
		काष्ठा pxamci_host *host = mmc_priv(mmc);

		mmc_हटाओ_host(mmc);

		अगर (host->pdata && host->pdata->निकास)
			host->pdata->निकास(&pdev->dev, mmc);

		pxamci_stop_घड़ी(host);
		ग_लिखोl(TXFIFO_WR_REQ|RXFIFO_RD_REQ|CLK_IS_OFF|STOP_CMD|
		       END_CMD_RES|PRG_DONE|DATA_TRAN_DONE,
		       host->base + MMC_I_MASK);

		dmaengine_terminate_all(host->dma_chan_rx);
		dmaengine_terminate_all(host->dma_chan_tx);
		dma_release_channel(host->dma_chan_rx);
		dma_release_channel(host->dma_chan_tx);

		mmc_मुक्त_host(mmc);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxamci_driver = अणु
	.probe		= pxamci_probe,
	.हटाओ		= pxamci_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(pxa_mmc_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxamci_driver);

MODULE_DESCRIPTION("PXA Multimedia Card Interface Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-mci");
