<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the MMC / SD / SDIO IP found in:
 *
 * TC6393XB, TC6391XB, TC6387XB, T7L66XB, ASIC3, SH-Mobile SoCs
 *
 * Copyright (C) 2015-19 Renesas Electronics Corporation
 * Copyright (C) 2016-19 Sang Engineering, Wolfram Sang
 * Copyright (C) 2017 Horms Solutions, Simon Horman
 * Copyright (C) 2011 Guennadi Liakhovetski
 * Copyright (C) 2007 Ian Molton
 * Copyright (C) 2004 Ian Molton
 *
 * This driver draws मुख्यly on scattered spec sheets, Reverse engineering
 * of the toshiba e800  SD driver and some parts of the 2.4 ASIC3 driver (4 bit
 * support). (Further 4 bit support from a later datasheet).
 *
 * TODO:
 *   Investigate using a workqueue क्रम PIO transfers
 *   Eliminate FIXMEs
 *   Better Power management
 *   Handle MMC errors better
 *   द्विगुन buffer support
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "tmio_mmc.h"

अटल अंतरभूत व्योम पंचांगio_mmc_start_dma(काष्ठा पंचांगio_mmc_host *host,
				      काष्ठा mmc_data *data)
अणु
	अगर (host->dma_ops)
		host->dma_ops->start(host, data);
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_end_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->dma_ops && host->dma_ops->end)
		host->dma_ops->end(host);
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_enable_dma(काष्ठा पंचांगio_mmc_host *host, bool enable)
अणु
	अगर (host->dma_ops)
		host->dma_ops->enable(host, enable);
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_request_dma(काष्ठा पंचांगio_mmc_host *host,
					काष्ठा पंचांगio_mmc_data *pdata)
अणु
	अगर (host->dma_ops) अणु
		host->dma_ops->request(host, pdata);
	पूर्ण अन्यथा अणु
		host->chan_tx = शून्य;
		host->chan_rx = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_release_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->dma_ops)
		host->dma_ops->release(host);
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_पात_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->dma_ops)
		host->dma_ops->पात(host);
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_dataend_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->dma_ops)
		host->dma_ops->dataend(host);
पूर्ण

व्योम पंचांगio_mmc_enable_mmc_irqs(काष्ठा पंचांगio_mmc_host *host, u32 i)
अणु
	host->sdcard_irq_mask &= ~(i & TMIO_MASK_IRQ);
	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_IRQ_MASK, host->sdcard_irq_mask);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_enable_mmc_irqs);

व्योम पंचांगio_mmc_disable_mmc_irqs(काष्ठा पंचांगio_mmc_host *host, u32 i)
अणु
	host->sdcard_irq_mask |= (i & TMIO_MASK_IRQ);
	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_IRQ_MASK, host->sdcard_irq_mask);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_disable_mmc_irqs);

अटल व्योम पंचांगio_mmc_ack_mmc_irqs(काष्ठा पंचांगio_mmc_host *host, u32 i)
अणु
	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_STATUS, ~i);
पूर्ण

अटल व्योम पंचांगio_mmc_init_sg(काष्ठा पंचांगio_mmc_host *host, काष्ठा mmc_data *data)
अणु
	host->sg_len = data->sg_len;
	host->sg_ptr = data->sg;
	host->sg_orig = data->sg;
	host->sg_off = 0;
पूर्ण

अटल पूर्णांक पंचांगio_mmc_next_sg(काष्ठा पंचांगio_mmc_host *host)
अणु
	host->sg_ptr = sg_next(host->sg_ptr);
	host->sg_off = 0;
	वापस --host->sg_len;
पूर्ण

#घोषणा CMDREQ_TIMEOUT	5000

अटल व्योम पंचांगio_mmc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);

	अगर (enable && !host->sdio_irq_enabled) अणु
		u16 sdio_status;

		/* Keep device active जबतक SDIO irq is enabled */
		pm_runसमय_get_sync(mmc_dev(mmc));

		host->sdio_irq_enabled = true;
		host->sdio_irq_mask = TMIO_SDIO_MASK_ALL & ~TMIO_SDIO_STAT_IOIRQ;

		/* Clear obsolete पूर्णांकerrupts beक्रमe enabling */
		sdio_status = sd_ctrl_पढ़ो16(host, CTL_SDIO_STATUS) & ~TMIO_SDIO_MASK_ALL;
		अगर (host->pdata->flags & TMIO_MMC_SDIO_STATUS_SETBITS)
			sdio_status |= TMIO_SDIO_SETBITS_MASK;
		sd_ctrl_ग_लिखो16(host, CTL_SDIO_STATUS, sdio_status);

		sd_ctrl_ग_लिखो16(host, CTL_SDIO_IRQ_MASK, host->sdio_irq_mask);
	पूर्ण अन्यथा अगर (!enable && host->sdio_irq_enabled) अणु
		host->sdio_irq_mask = TMIO_SDIO_MASK_ALL;
		sd_ctrl_ग_लिखो16(host, CTL_SDIO_IRQ_MASK, host->sdio_irq_mask);

		host->sdio_irq_enabled = false;
		pm_runसमय_mark_last_busy(mmc_dev(mmc));
		pm_runसमय_put_स्वतःsuspend(mmc_dev(mmc));
	पूर्ण
पूर्ण

अटल व्योम पंचांगio_mmc_set_bus_width(काष्ठा पंचांगio_mmc_host *host,
				   अचिन्हित अक्षर bus_width)
अणु
	u16 reg = sd_ctrl_पढ़ो16(host, CTL_SD_MEM_CARD_OPT)
				& ~(CARD_OPT_WIDTH | CARD_OPT_WIDTH8);

	/* reg now applies to MMC_BUS_WIDTH_4 */
	अगर (bus_width == MMC_BUS_WIDTH_1)
		reg |= CARD_OPT_WIDTH;
	अन्यथा अगर (bus_width == MMC_BUS_WIDTH_8)
		reg |= CARD_OPT_WIDTH8;

	sd_ctrl_ग_लिखो16(host, CTL_SD_MEM_CARD_OPT, reg);
पूर्ण

अटल व्योम पंचांगio_mmc_reset(काष्ठा पंचांगio_mmc_host *host)
अणु
	/* FIXME - should we set stop घड़ी reg here */
	sd_ctrl_ग_लिखो16(host, CTL_RESET_SD, 0x0000);
	usleep_range(10000, 11000);
	sd_ctrl_ग_लिखो16(host, CTL_RESET_SD, 0x0001);
	usleep_range(10000, 11000);

	पंचांगio_mmc_पात_dma(host);

	अगर (host->reset)
		host->reset(host);

	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_IRQ_MASK, host->sdcard_irq_mask_all);
	host->sdcard_irq_mask = host->sdcard_irq_mask_all;

	पंचांगio_mmc_set_bus_width(host, host->mmc->ios.bus_width);

	अगर (host->pdata->flags & TMIO_MMC_SDIO_IRQ) अणु
		sd_ctrl_ग_लिखो16(host, CTL_SDIO_IRQ_MASK, host->sdio_irq_mask);
		sd_ctrl_ग_लिखो16(host, CTL_TRANSACTION_CTL, 0x0001);
	पूर्ण

	अगर (host->mmc->card)
		mmc_retune_needed(host->mmc);
पूर्ण

अटल व्योम पंचांगio_mmc_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पंचांगio_mmc_host *host = container_of(work, काष्ठा पंचांगio_mmc_host,
						  delayed_reset_work.work);
	काष्ठा mmc_request *mrq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	mrq = host->mrq;

	/*
	 * is request alपढ़ोy finished? Since we use a non-blocking
	 * cancel_delayed_work(), it can happen, that a .set_ios() call preempts
	 * us, so, have to check क्रम IS_ERR(host->mrq)
	 */
	अगर (IS_ERR_OR_शून्य(mrq) ||
	    समय_is_after_jअगरfies(host->last_req_ts +
				  msecs_to_jअगरfies(CMDREQ_TIMEOUT))) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		वापस;
	पूर्ण

	dev_warn(&host->pdev->dev,
		 "timeout waiting for hardware interrupt (CMD%u)\n",
		 mrq->cmd->opcode);

	अगर (host->data)
		host->data->error = -ETIMEDOUT;
	अन्यथा अगर (host->cmd)
		host->cmd->error = -ETIMEDOUT;
	अन्यथा
		mrq->cmd->error = -ETIMEDOUT;

	host->cmd = शून्य;
	host->data = शून्य;

	spin_unlock_irqrestore(&host->lock, flags);

	पंचांगio_mmc_reset(host);

	/* Ready क्रम new calls */
	host->mrq = शून्य;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

/* These are the biपंचांगasks the पंचांगio chip requires to implement the MMC response
 * types. Note that R1 and R6 are the same in this scheme. */
#घोषणा APP_CMD        0x0040
#घोषणा RESP_NONE      0x0300
#घोषणा RESP_R1        0x0400
#घोषणा RESP_R1B       0x0500
#घोषणा RESP_R2        0x0600
#घोषणा RESP_R3        0x0700
#घोषणा DATA_PRESENT   0x0800
#घोषणा TRANSFER_READ  0x1000
#घोषणा TRANSFER_MULTI 0x2000
#घोषणा SECURITY_CMD   0x4000
#घोषणा NO_CMD12_ISSUE 0x4000 /* TMIO_MMC_HAVE_CMD12_CTRL */

अटल पूर्णांक पंचांगio_mmc_start_command(काष्ठा पंचांगio_mmc_host *host,
				  काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक c = cmd->opcode;

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE: c |= RESP_NONE; अवरोध;
	हाल MMC_RSP_R1:
	हाल MMC_RSP_R1_NO_CRC:
			   c |= RESP_R1;   अवरोध;
	हाल MMC_RSP_R1B:  c |= RESP_R1B;  अवरोध;
	हाल MMC_RSP_R2:   c |= RESP_R2;   अवरोध;
	हाल MMC_RSP_R3:   c |= RESP_R3;   अवरोध;
	शेष:
		pr_debug("Unknown response type %d\n", mmc_resp_type(cmd));
		वापस -EINVAL;
	पूर्ण

	host->cmd = cmd;

/* FIXME - this seems to be ok commented out but the spec suggest this bit
 *         should be set when issuing app commands.
 *	अगर(cmd->flags & MMC_FLAG_ACMD)
 *		c |= APP_CMD;
 */
	अगर (data) अणु
		c |= DATA_PRESENT;
		अगर (data->blocks > 1) अणु
			sd_ctrl_ग_लिखो16(host, CTL_STOP_INTERNAL_ACTION, TMIO_STOP_SEC);
			c |= TRANSFER_MULTI;

			/*
			 * Disable स्वतः CMD12 at IO_RW_EXTENDED and
			 * SET_BLOCK_COUNT when करोing multiple block transfer
			 */
			अगर ((host->pdata->flags & TMIO_MMC_HAVE_CMD12_CTRL) &&
			    (cmd->opcode == SD_IO_RW_EXTENDED || host->mrq->sbc))
				c |= NO_CMD12_ISSUE;
		पूर्ण
		अगर (data->flags & MMC_DATA_READ)
			c |= TRANSFER_READ;
	पूर्ण

	पंचांगio_mmc_enable_mmc_irqs(host, TMIO_MASK_CMD);

	/* Fire off the command */
	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_ARG_REG, cmd->arg);
	sd_ctrl_ग_लिखो16(host, CTL_SD_CMD, c);

	वापस 0;
पूर्ण

अटल व्योम पंचांगio_mmc_transfer_data(काष्ठा पंचांगio_mmc_host *host,
				   अचिन्हित लघु *buf,
				   अचिन्हित पूर्णांक count)
अणु
	पूर्णांक is_पढ़ो = host->data->flags & MMC_DATA_READ;
	u8  *buf8;

	/*
	 * Transfer the data
	 */
	अगर (host->pdata->flags & TMIO_MMC_32BIT_DATA_PORT) अणु
		u32 data = 0;
		u32 *buf32 = (u32 *)buf;

		अगर (is_पढ़ो)
			sd_ctrl_पढ़ो32_rep(host, CTL_SD_DATA_PORT, buf32,
					   count >> 2);
		अन्यथा
			sd_ctrl_ग_लिखो32_rep(host, CTL_SD_DATA_PORT, buf32,
					    count >> 2);

		/* अगर count was multiple of 4 */
		अगर (!(count & 0x3))
			वापस;

		buf32 += count >> 2;
		count %= 4;

		अगर (is_पढ़ो) अणु
			sd_ctrl_पढ़ो32_rep(host, CTL_SD_DATA_PORT, &data, 1);
			स_नकल(buf32, &data, count);
		पूर्ण अन्यथा अणु
			स_नकल(&data, buf32, count);
			sd_ctrl_ग_लिखो32_rep(host, CTL_SD_DATA_PORT, &data, 1);
		पूर्ण

		वापस;
	पूर्ण

	अगर (is_पढ़ो)
		sd_ctrl_पढ़ो16_rep(host, CTL_SD_DATA_PORT, buf, count >> 1);
	अन्यथा
		sd_ctrl_ग_लिखो16_rep(host, CTL_SD_DATA_PORT, buf, count >> 1);

	/* अगर count was even number */
	अगर (!(count & 0x1))
		वापस;

	/* अगर count was odd number */
	buf8 = (u8 *)(buf + (count >> 1));

	/*
	 * FIXME
	 *
	 * driver and this function are assuming that
	 * it is used as little endian
	 */
	अगर (is_पढ़ो)
		*buf8 = sd_ctrl_पढ़ो16(host, CTL_SD_DATA_PORT) & 0xff;
	अन्यथा
		sd_ctrl_ग_लिखो16(host, CTL_SD_DATA_PORT, *buf8);
पूर्ण

/*
 * This chip always वापसs (at least?) as much data as you ask क्रम.
 * I'm unsure what happens अगर you ask क्रम less than a block. This should be
 * looked पूर्णांकo to ensure that a funny length पढ़ो करोesn't hose the controller.
 */
अटल व्योम पंचांगio_mmc_pio_irq(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा mmc_data *data = host->data;
	व्योम *sg_virt;
	अचिन्हित लघु *buf;
	अचिन्हित पूर्णांक count;
	अचिन्हित दीर्घ flags;

	अगर (host->dma_on) अणु
		pr_err("PIO IRQ in DMA mode!\n");
		वापस;
	पूर्ण अन्यथा अगर (!data) अणु
		pr_debug("Spurious PIO IRQ\n");
		वापस;
	पूर्ण

	sg_virt = पंचांगio_mmc_kmap_atomic(host->sg_ptr, &flags);
	buf = (अचिन्हित लघु *)(sg_virt + host->sg_off);

	count = host->sg_ptr->length - host->sg_off;
	अगर (count > data->blksz)
		count = data->blksz;

	pr_debug("count: %08x offset: %08x flags %08x\n",
		 count, host->sg_off, data->flags);

	/* Transfer the data */
	पंचांगio_mmc_transfer_data(host, buf, count);

	host->sg_off += count;

	पंचांगio_mmc_kunmap_atomic(host->sg_ptr, &flags, sg_virt);

	अगर (host->sg_off == host->sg_ptr->length)
		पंचांगio_mmc_next_sg(host);
पूर्ण

अटल व्योम पंचांगio_mmc_check_bounce_buffer(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->sg_ptr == &host->bounce_sg) अणु
		अचिन्हित दीर्घ flags;
		व्योम *sg_vaddr = पंचांगio_mmc_kmap_atomic(host->sg_orig, &flags);

		स_नकल(sg_vaddr, host->bounce_buf, host->bounce_sg.length);
		पंचांगio_mmc_kunmap_atomic(host->sg_orig, &flags, sg_vaddr);
	पूर्ण
पूर्ण

/* needs to be called with host->lock held */
व्योम पंचांगio_mmc_करो_data_irq(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा mmc_data *data = host->data;
	काष्ठा mmc_command *stop;

	host->data = शून्य;

	अगर (!data) अणु
		dev_warn(&host->pdev->dev, "Spurious data end IRQ\n");
		वापस;
	पूर्ण
	stop = data->stop;

	/* FIXME - वापस correct transfer count on errors */
	अगर (!data->error)
		data->bytes_xfered = data->blocks * data->blksz;
	अन्यथा
		data->bytes_xfered = 0;

	pr_debug("Completed data request\n");

	/*
	 * FIXME: other drivers allow an optional stop command of any given type
	 *        which we करोnt करो, as the chip can स्वतः generate them.
	 *        Perhaps we can be smarter about when to use स्वतः CMD12 and
	 *        only issue the स्वतः request when we know this is the desired
	 *        stop command, allowing fallback to the stop command the
	 *        upper layers expect. For now, we करो what works.
	 */

	अगर (data->flags & MMC_DATA_READ) अणु
		अगर (host->dma_on)
			पंचांगio_mmc_check_bounce_buffer(host);
		dev_dbg(&host->pdev->dev, "Complete Rx request %p\n",
			host->mrq);
	पूर्ण अन्यथा अणु
		dev_dbg(&host->pdev->dev, "Complete Tx request %p\n",
			host->mrq);
	पूर्ण

	अगर (stop && !host->mrq->sbc) अणु
		अगर (stop->opcode != MMC_STOP_TRANSMISSION || stop->arg)
			dev_err(&host->pdev->dev, "unsupported stop: CMD%u,0x%x. We did CMD12,0\n",
				stop->opcode, stop->arg);

		/* fill in response from स्वतः CMD12 */
		stop->resp[0] = sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_RESPONSE);

		sd_ctrl_ग_लिखो16(host, CTL_STOP_INTERNAL_ACTION, 0);
	पूर्ण

	schedule_work(&host->करोne);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_करो_data_irq);

अटल व्योम पंचांगio_mmc_data_irq(काष्ठा पंचांगio_mmc_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_data *data;

	spin_lock(&host->lock);
	data = host->data;

	अगर (!data)
		जाओ out;

	अगर (stat & TMIO_STAT_DATATIMEOUT)
		data->error = -ETIMEDOUT;
	अन्यथा अगर (stat & TMIO_STAT_CRCFAIL || stat & TMIO_STAT_STOPBIT_ERR ||
		 stat & TMIO_STAT_TXUNDERRUN)
		data->error = -EILSEQ;
	अगर (host->dma_on && (data->flags & MMC_DATA_WRITE)) अणु
		u32 status = sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_STATUS);
		bool करोne = false;

		/*
		 * Has all data been written out yet? Testing on SuperH showed,
		 * that in most हालs the first पूर्णांकerrupt comes alपढ़ोy with the
		 * BUSY status bit clear, but on some operations, like mount or
		 * in the beginning of a ग_लिखो / sync / umount, there is one
		 * DATAEND पूर्णांकerrupt with the BUSY bit set, in this हालs
		 * रुकोing क्रम one more पूर्णांकerrupt fixes the problem.
		 */
		अगर (host->pdata->flags & TMIO_MMC_HAS_IDLE_WAIT) अणु
			अगर (status & TMIO_STAT_SCLKDIVEN)
				करोne = true;
		पूर्ण अन्यथा अणु
			अगर (!(status & TMIO_STAT_CMD_BUSY))
				करोne = true;
		पूर्ण

		अगर (करोne) अणु
			पंचांगio_mmc_disable_mmc_irqs(host, TMIO_STAT_DATAEND);
			पंचांगio_mmc_dataend_dma(host);
		पूर्ण
	पूर्ण अन्यथा अगर (host->dma_on && (data->flags & MMC_DATA_READ)) अणु
		पंचांगio_mmc_disable_mmc_irqs(host, TMIO_STAT_DATAEND);
		पंचांगio_mmc_dataend_dma(host);
	पूर्ण अन्यथा अणु
		पंचांगio_mmc_करो_data_irq(host);
		पंचांगio_mmc_disable_mmc_irqs(host, TMIO_MASK_READOP | TMIO_MASK_WRITEOP);
	पूर्ण
out:
	spin_unlock(&host->lock);
पूर्ण

अटल व्योम पंचांगio_mmc_cmd_irq(काष्ठा पंचांगio_mmc_host *host, अचिन्हित पूर्णांक stat)
अणु
	काष्ठा mmc_command *cmd = host->cmd;
	पूर्णांक i, addr;

	spin_lock(&host->lock);

	अगर (!host->cmd) अणु
		pr_debug("Spurious CMD irq\n");
		जाओ out;
	पूर्ण

	/* This controller is sicker than the PXA one. Not only करो we need to
	 * drop the top 8 bits of the first response word, we also need to
	 * modअगरy the order of the response क्रम लघु response command types.
	 */

	क्रम (i = 3, addr = CTL_RESPONSE ; i >= 0 ; i--, addr += 4)
		cmd->resp[i] = sd_ctrl_पढ़ो16_and_16_as_32(host, addr);

	अगर (cmd->flags &  MMC_RSP_136) अणु
		cmd->resp[0] = (cmd->resp[0] << 8) | (cmd->resp[1] >> 24);
		cmd->resp[1] = (cmd->resp[1] << 8) | (cmd->resp[2] >> 24);
		cmd->resp[2] = (cmd->resp[2] << 8) | (cmd->resp[3] >> 24);
		cmd->resp[3] <<= 8;
	पूर्ण अन्यथा अगर (cmd->flags & MMC_RSP_R3) अणु
		cmd->resp[0] = cmd->resp[3];
	पूर्ण

	अगर (stat & TMIO_STAT_CMDTIMEOUT)
		cmd->error = -ETIMEDOUT;
	अन्यथा अगर ((stat & TMIO_STAT_CRCFAIL && cmd->flags & MMC_RSP_CRC) ||
		 stat & TMIO_STAT_STOPBIT_ERR ||
		 stat & TMIO_STAT_CMD_IDX_ERR)
		cmd->error = -EILSEQ;

	/* If there is data to handle we enable data IRQs here, and
	 * we will ultimatley finish the request in the data_end handler.
	 * If theres no data or we encountered an error, finish now.
	 */
	अगर (host->data && (!cmd->error || cmd->error == -EILSEQ)) अणु
		अगर (host->data->flags & MMC_DATA_READ) अणु
			अगर (!host->dma_on) अणु
				पंचांगio_mmc_enable_mmc_irqs(host, TMIO_MASK_READOP);
			पूर्ण अन्यथा अणु
				पंचांगio_mmc_disable_mmc_irqs(host,
							  TMIO_MASK_READOP);
				tasklet_schedule(&host->dma_issue);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!host->dma_on) अणु
				पंचांगio_mmc_enable_mmc_irqs(host, TMIO_MASK_WRITEOP);
			पूर्ण अन्यथा अणु
				पंचांगio_mmc_disable_mmc_irqs(host,
							  TMIO_MASK_WRITEOP);
				tasklet_schedule(&host->dma_issue);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		schedule_work(&host->करोne);
	पूर्ण

out:
	spin_unlock(&host->lock);
पूर्ण

अटल bool __पंचांगio_mmc_card_detect_irq(काष्ठा पंचांगio_mmc_host *host,
				       पूर्णांक ireg, पूर्णांक status)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	/* Card insert / हटाओ attempts */
	अगर (ireg & (TMIO_STAT_CARD_INSERT | TMIO_STAT_CARD_REMOVE)) अणु
		पंचांगio_mmc_ack_mmc_irqs(host, TMIO_STAT_CARD_INSERT |
			TMIO_STAT_CARD_REMOVE);
		अगर ((((ireg & TMIO_STAT_CARD_REMOVE) && mmc->card) ||
		     ((ireg & TMIO_STAT_CARD_INSERT) && !mmc->card)) &&
		    !work_pending(&mmc->detect.work))
			mmc_detect_change(host->mmc, msecs_to_jअगरfies(100));
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __पंचांगio_mmc_sdcard_irq(काष्ठा पंचांगio_mmc_host *host, पूर्णांक ireg,
				  पूर्णांक status)
अणु
	/* Command completion */
	अगर (ireg & (TMIO_STAT_CMDRESPEND | TMIO_STAT_CMDTIMEOUT)) अणु
		पंचांगio_mmc_ack_mmc_irqs(host, TMIO_STAT_CMDRESPEND |
				      TMIO_STAT_CMDTIMEOUT);
		पंचांगio_mmc_cmd_irq(host, status);
		वापस true;
	पूर्ण

	/* Data transfer */
	अगर (ireg & (TMIO_STAT_RXRDY | TMIO_STAT_TXRQ)) अणु
		पंचांगio_mmc_ack_mmc_irqs(host, TMIO_STAT_RXRDY | TMIO_STAT_TXRQ);
		पंचांगio_mmc_pio_irq(host);
		वापस true;
	पूर्ण

	/* Data transfer completion */
	अगर (ireg & TMIO_STAT_DATAEND) अणु
		पंचांगio_mmc_ack_mmc_irqs(host, TMIO_STAT_DATAEND);
		पंचांगio_mmc_data_irq(host, status);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __पंचांगio_mmc_sdio_irq(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा पंचांगio_mmc_data *pdata = host->pdata;
	अचिन्हित पूर्णांक ireg, status;
	अचिन्हित पूर्णांक sdio_status;

	अगर (!(pdata->flags & TMIO_MMC_SDIO_IRQ))
		वापस false;

	status = sd_ctrl_पढ़ो16(host, CTL_SDIO_STATUS);
	ireg = status & TMIO_SDIO_MASK_ALL & ~host->sdio_irq_mask;

	sdio_status = status & ~TMIO_SDIO_MASK_ALL;
	अगर (pdata->flags & TMIO_MMC_SDIO_STATUS_SETBITS)
		sdio_status |= TMIO_SDIO_SETBITS_MASK;

	sd_ctrl_ग_लिखो16(host, CTL_SDIO_STATUS, sdio_status);

	अगर (mmc->caps & MMC_CAP_SDIO_IRQ && ireg & TMIO_SDIO_STAT_IOIRQ)
		mmc_संकेत_sdio_irq(mmc);

	वापस ireg;
पूर्ण

irqवापस_t पंचांगio_mmc_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा पंचांगio_mmc_host *host = devid;
	अचिन्हित पूर्णांक ireg, status;

	status = sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_STATUS);
	ireg = status & TMIO_MASK_IRQ & ~host->sdcard_irq_mask;

	/* Clear the status except the पूर्णांकerrupt status */
	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_STATUS, TMIO_MASK_IRQ);

	अगर (__पंचांगio_mmc_card_detect_irq(host, ireg, status))
		वापस IRQ_HANDLED;
	अगर (__पंचांगio_mmc_sdcard_irq(host, ireg, status))
		वापस IRQ_HANDLED;

	अगर (__पंचांगio_mmc_sdio_irq(host))
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_irq);

अटल पूर्णांक पंचांगio_mmc_start_data(काष्ठा पंचांगio_mmc_host *host,
			       काष्ठा mmc_data *data)
अणु
	काष्ठा पंचांगio_mmc_data *pdata = host->pdata;

	pr_debug("setup data transfer: blocksize %08x  nr_blocks %d\n",
		 data->blksz, data->blocks);

	/* Some hardware cannot perक्रमm 2 byte requests in 4/8 bit mode */
	अगर (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4 ||
	    host->mmc->ios.bus_width == MMC_BUS_WIDTH_8) अणु
		पूर्णांक blksz_2bytes = pdata->flags & TMIO_MMC_BLKSZ_2BYTES;

		अगर (data->blksz < 2 || (data->blksz < 4 && !blksz_2bytes)) अणु
			pr_err("%s: %d byte block unsupported in 4/8 bit mode\n",
			       mmc_hostname(host->mmc), data->blksz);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	पंचांगio_mmc_init_sg(host, data);
	host->data = data;
	host->dma_on = false;

	/* Set transfer length / blocksize */
	sd_ctrl_ग_लिखो16(host, CTL_SD_XFER_LEN, data->blksz);
	अगर (host->mmc->max_blk_count >= SZ_64K)
		sd_ctrl_ग_लिखो32(host, CTL_XFER_BLK_COUNT, data->blocks);
	अन्यथा
		sd_ctrl_ग_लिखो16(host, CTL_XFER_BLK_COUNT, data->blocks);

	पंचांगio_mmc_start_dma(host, data);

	वापस 0;
पूर्ण

अटल व्योम पंचांगio_process_mrq(काष्ठा पंचांगio_mmc_host *host,
			     काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_command *cmd;
	पूर्णांक ret;

	अगर (mrq->sbc && host->cmd != mrq->sbc) अणु
		cmd = mrq->sbc;
	पूर्ण अन्यथा अणु
		cmd = mrq->cmd;
		अगर (mrq->data) अणु
			ret = पंचांगio_mmc_start_data(host, mrq->data);
			अगर (ret)
				जाओ fail;
		पूर्ण
	पूर्ण

	ret = पंचांगio_mmc_start_command(host, cmd);
	अगर (ret)
		जाओ fail;

	schedule_delayed_work(&host->delayed_reset_work,
			      msecs_to_jअगरfies(CMDREQ_TIMEOUT));
	वापस;

fail:
	host->mrq = शून्य;
	mrq->cmd->error = ret;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

/* Process requests from the MMC layer */
अटल व्योम पंचांगio_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->mrq) अणु
		pr_debug("request not null\n");
		अगर (IS_ERR(host->mrq)) अणु
			spin_unlock_irqrestore(&host->lock, flags);
			mrq->cmd->error = -EAGAIN;
			mmc_request_करोne(mmc, mrq);
			वापस;
		पूर्ण
	पूर्ण

	host->last_req_ts = jअगरfies;
	wmb();
	host->mrq = mrq;

	spin_unlock_irqrestore(&host->lock, flags);

	पंचांगio_process_mrq(host, mrq);
पूर्ण

अटल व्योम पंचांगio_mmc_finish_request(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा mmc_request *mrq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	पंचांगio_mmc_end_dma(host);

	mrq = host->mrq;
	अगर (IS_ERR_OR_शून्य(mrq)) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		वापस;
	पूर्ण

	/* If not SET_BLOCK_COUNT, clear old data */
	अगर (host->cmd != mrq->sbc) अणु
		host->cmd = शून्य;
		host->data = शून्य;
		host->mrq = शून्य;
	पूर्ण

	cancel_delayed_work(&host->delayed_reset_work);

	spin_unlock_irqrestore(&host->lock, flags);

	अगर (mrq->cmd->error || (mrq->data && mrq->data->error)) अणु
		पंचांगio_mmc_ack_mmc_irqs(host, TMIO_MASK_IRQ); /* Clear all */
		पंचांगio_mmc_पात_dma(host);
	पूर्ण

	/* Error means retune, but executed command was still successful */
	अगर (host->check_retune && host->check_retune(host, mrq))
		mmc_retune_needed(host->mmc);

	/* If SET_BLOCK_COUNT, जारी with मुख्य command */
	अगर (host->mrq && !mrq->cmd->error) अणु
		पंचांगio_process_mrq(host, mrq);
		वापस;
	पूर्ण

	अगर (host->fixup_request)
		host->fixup_request(host, mrq);

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम पंचांगio_mmc_करोne_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पंचांगio_mmc_host *host = container_of(work, काष्ठा पंचांगio_mmc_host,
						  करोne);
	पंचांगio_mmc_finish_request(host);
पूर्ण

अटल व्योम पंचांगio_mmc_घातer_on(काष्ठा पंचांगio_mmc_host *host, अचिन्हित लघु vdd)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret = 0;

	/* .set_ios() is वापसing व्योम, so, no chance to report an error */

	अगर (host->set_pwr)
		host->set_pwr(host->pdev, 1);

	अगर (!IS_ERR(mmc->supply.vmmc)) अणु
		ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
		/*
		 * Attention: empiric value. With a b43 WiFi SDIO card this
		 * delay proved necessary क्रम reliable card-insertion probing.
		 * 100us were not enough. Is this the same 140us delay, as in
		 * पंचांगio_mmc_set_ios()?
		 */
		usleep_range(200, 300);
	पूर्ण
	/*
	 * It seems, VccQ should be चयनed on after Vcc, this is also what the
	 * omap_hsmmc.c driver करोes.
	 */
	अगर (!IS_ERR(mmc->supply.vqmmc) && !ret) अणु
		ret = regulator_enable(mmc->supply.vqmmc);
		usleep_range(200, 300);
	पूर्ण

	अगर (ret < 0)
		dev_dbg(&host->pdev->dev, "Regulators failed to power up: %d\n",
			ret);
पूर्ण

अटल व्योम पंचांगio_mmc_घातer_off(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	अगर (!IS_ERR(mmc->supply.vqmmc))
		regulator_disable(mmc->supply.vqmmc);

	अगर (!IS_ERR(mmc->supply.vmmc))
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

	अगर (host->set_pwr)
		host->set_pwr(host->pdev, 0);
पूर्ण

अटल अचिन्हित पूर्णांक पंचांगio_mmc_get_समयout_cycles(काष्ठा पंचांगio_mmc_host *host)
अणु
	u16 val = sd_ctrl_पढ़ो16(host, CTL_SD_MEM_CARD_OPT);

	val = (val & CARD_OPT_TOP_MASK) >> CARD_OPT_TOP_SHIFT;
	वापस 1 << (13 + val);
पूर्ण

अटल व्योम पंचांगio_mmc_max_busy_समयout(काष्ठा पंचांगio_mmc_host *host)
अणु
	अचिन्हित पूर्णांक clk_rate = host->mmc->actual_घड़ी ?: host->mmc->f_max;

	host->mmc->max_busy_समयout = host->get_समयout_cycles(host) /
				      (clk_rate / MSEC_PER_SEC);
पूर्ण

/* Set MMC घड़ी / घातer.
 * Note: This controller uses a simple भागider scheme thereक्रमe it cannot
 * run a MMC card at full speed (20MHz). The max घड़ी is 24MHz on SD, but as
 * MMC wont run that fast, it has to be घड़ीed at 12MHz which is the next
 * slowest setting.
 */
अटल व्योम पंचांगio_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा device *dev = &host->pdev->dev;
	अचिन्हित दीर्घ flags;

	mutex_lock(&host->ios_lock);

	spin_lock_irqsave(&host->lock, flags);
	अगर (host->mrq) अणु
		अगर (IS_ERR(host->mrq)) अणु
			dev_dbg(dev,
				"%s.%d: concurrent .set_ios(), clk %u, mode %u\n",
				current->comm, task_pid_nr(current),
				ios->घड़ी, ios->घातer_mode);
			host->mrq = ERR_PTR(-EINTR);
		पूर्ण अन्यथा अणु
			dev_dbg(dev,
				"%s.%d: CMD%u active since %lu, now %lu!\n",
				current->comm, task_pid_nr(current),
				host->mrq->cmd->opcode, host->last_req_ts,
				jअगरfies);
		पूर्ण
		spin_unlock_irqrestore(&host->lock, flags);

		mutex_unlock(&host->ios_lock);
		वापस;
	पूर्ण

	host->mrq = ERR_PTR(-EBUSY);

	spin_unlock_irqrestore(&host->lock, flags);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		पंचांगio_mmc_घातer_off(host);
		/* For R-Car Gen2+, we need to reset SDHI specअगरic SCC */
		अगर (host->pdata->flags & TMIO_MMC_MIN_RCAR2)
			host->reset(host);
		host->set_घड़ी(host, 0);
		अवरोध;
	हाल MMC_POWER_UP:
		पंचांगio_mmc_घातer_on(host, ios->vdd);
		host->set_घड़ी(host, ios->घड़ी);
		पंचांगio_mmc_set_bus_width(host, ios->bus_width);
		अवरोध;
	हाल MMC_POWER_ON:
		host->set_घड़ी(host, ios->घड़ी);
		पंचांगio_mmc_set_bus_width(host, ios->bus_width);
		अवरोध;
	पूर्ण

	अगर (host->pdata->flags & TMIO_MMC_USE_BUSY_TIMEOUT)
		पंचांगio_mmc_max_busy_समयout(host);

	/* Let things settle. delay taken from winCE driver */
	usleep_range(140, 200);
	अगर (PTR_ERR(host->mrq) == -EINTR)
		dev_dbg(&host->pdev->dev,
			"%s.%d: IOS interrupted: clk %u, mode %u",
			current->comm, task_pid_nr(current),
			ios->घड़ी, ios->घातer_mode);
	host->mrq = शून्य;

	host->clk_cache = ios->घड़ी;

	mutex_unlock(&host->ios_lock);
पूर्ण

अटल पूर्णांक पंचांगio_mmc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);

	वापस !(sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_STATUS) &
		 TMIO_STAT_WRPROTECT);
पूर्ण

अटल पूर्णांक पंचांगio_mmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);

	वापस !!(sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_STATUS) &
		  TMIO_STAT_SIGSTATE);
पूर्ण

अटल पूर्णांक पंचांगio_multi_io_quirk(काष्ठा mmc_card *card,
			       अचिन्हित पूर्णांक direction, पूर्णांक blk_size)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(card->host);

	अगर (host->multi_io_quirk)
		वापस host->multi_io_quirk(card, direction, blk_size);

	वापस blk_size;
पूर्ण

अटल काष्ठा mmc_host_ops पंचांगio_mmc_ops = अणु
	.request	= पंचांगio_mmc_request,
	.set_ios	= पंचांगio_mmc_set_ios,
	.get_ro         = पंचांगio_mmc_get_ro,
	.get_cd		= पंचांगio_mmc_get_cd,
	.enable_sdio_irq = पंचांगio_mmc_enable_sdio_irq,
	.multi_io_quirk	= पंचांगio_multi_io_quirk,
पूर्ण;

अटल पूर्णांक पंचांगio_mmc_init_ocr(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा पंचांगio_mmc_data *pdata = host->pdata;
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक err;

	err = mmc_regulator_get_supply(mmc);
	अगर (err)
		वापस err;

	/* use ocr_mask अगर no regulator */
	अगर (!mmc->ocr_avail)
		mmc->ocr_avail = pdata->ocr_mask;

	/*
	 * try again.
	 * There is possibility that regulator has not been probed
	 */
	अगर (!mmc->ocr_avail)
		वापस -EPROBE_DEFER;

	वापस 0;
पूर्ण

अटल व्योम पंचांगio_mmc_of_parse(काष्ठा platक्रमm_device *pdev,
			      काष्ठा mmc_host *mmc)
अणु
	स्थिर काष्ठा device_node *np = pdev->dev.of_node;

	अगर (!np)
		वापस;

	/*
	 * DEPRECATED:
	 * For new platक्रमms, please use "disable-wp" instead of
	 * "toshiba,mmc-wrprotect-disable"
	 */
	अगर (of_get_property(np, "toshiba,mmc-wrprotect-disable", शून्य))
		mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;
पूर्ण

काष्ठा पंचांगio_mmc_host *पंचांगio_mmc_host_alloc(काष्ठा platक्रमm_device *pdev,
					  काष्ठा पंचांगio_mmc_data *pdata)
अणु
	काष्ठा पंचांगio_mmc_host *host;
	काष्ठा mmc_host *mmc;
	व्योम __iomem *ctl;
	पूर्णांक ret;

	ctl = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctl))
		वापस ERR_CAST(ctl);

	mmc = mmc_alloc_host(माप(काष्ठा पंचांगio_mmc_host), &pdev->dev);
	अगर (!mmc)
		वापस ERR_PTR(-ENOMEM);

	host = mmc_priv(mmc);
	host->ctl = ctl;
	host->mmc = mmc;
	host->pdev = pdev;
	host->pdata = pdata;
	host->ops = पंचांगio_mmc_ops;
	mmc->ops = &host->ops;

	ret = mmc_of_parse(host->mmc);
	अगर (ret) अणु
		host = ERR_PTR(ret);
		जाओ मुक्त;
	पूर्ण

	पंचांगio_mmc_of_parse(pdev, mmc);

	platक्रमm_set_drvdata(pdev, host);

	वापस host;
मुक्त:
	mmc_मुक्त_host(mmc);

	वापस host;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_host_alloc);

व्योम पंचांगio_mmc_host_मुक्त(काष्ठा पंचांगio_mmc_host *host)
अणु
	mmc_मुक्त_host(host->mmc);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_host_मुक्त);

पूर्णांक पंचांगio_mmc_host_probe(काष्ठा पंचांगio_mmc_host *_host)
अणु
	काष्ठा platक्रमm_device *pdev = _host->pdev;
	काष्ठा पंचांगio_mmc_data *pdata = _host->pdata;
	काष्ठा mmc_host *mmc = _host->mmc;
	पूर्णांक ret;

	/*
	 * Check the sanity of mmc->f_min to prevent host->set_घड़ी() from
	 * looping क्रमever...
	 */
	अगर (mmc->f_min == 0)
		वापस -EINVAL;

	अगर (!(pdata->flags & TMIO_MMC_HAS_IDLE_WAIT))
		_host->ग_लिखो16_hook = शून्य;

	अगर (pdata->flags & TMIO_MMC_USE_BUSY_TIMEOUT && !_host->get_समयout_cycles)
		_host->get_समयout_cycles = पंचांगio_mmc_get_समयout_cycles;

	_host->set_pwr = pdata->set_pwr;

	ret = पंचांगio_mmc_init_ocr(_host);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Look क्रम a card detect GPIO, अगर it fails with anything
	 * अन्यथा than a probe deferral, just live without it.
	 */
	ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0);
	अगर (ret == -EPROBE_DEFER)
		वापस ret;

	mmc->caps |= MMC_CAP_4_BIT_DATA | pdata->capabilities;
	mmc->caps2 |= pdata->capabilities2;
	mmc->max_segs = pdata->max_segs ? : 32;
	mmc->max_blk_size = TMIO_MAX_BLK_SIZE;
	mmc->max_blk_count = pdata->max_blk_count ? :
		(PAGE_SIZE / mmc->max_blk_size) * mmc->max_segs;
	mmc->max_req_size = min_t(माप_प्रकार,
				  mmc->max_blk_size * mmc->max_blk_count,
				  dma_max_mapping_size(&pdev->dev));
	mmc->max_seg_size = mmc->max_req_size;

	अगर (mmc_can_gpio_ro(mmc))
		_host->ops.get_ro = mmc_gpio_get_ro;

	अगर (mmc_can_gpio_cd(mmc))
		_host->ops.get_cd = mmc_gpio_get_cd;

	_host->native_hotplug = !(mmc_can_gpio_cd(mmc) ||
				  mmc->caps & MMC_CAP_NEEDS_POLL ||
				  !mmc_card_is_removable(mmc));

	/*
	 * While using पूर्णांकernal पंचांगio hardware logic क्रम card detection, we need
	 * to ensure it stays घातered क्रम it to work.
	 */
	अगर (_host->native_hotplug)
		pm_runसमय_get_noresume(&pdev->dev);

	_host->sdio_irq_enabled = false;
	अगर (pdata->flags & TMIO_MMC_SDIO_IRQ)
		_host->sdio_irq_mask = TMIO_SDIO_MASK_ALL;

	अगर (!_host->sdcard_irq_mask_all)
		_host->sdcard_irq_mask_all = TMIO_MASK_ALL;

	_host->set_घड़ी(_host, 0);
	पंचांगio_mmc_reset(_host);

	अगर (_host->native_hotplug)
		पंचांगio_mmc_enable_mmc_irqs(_host,
				TMIO_STAT_CARD_REMOVE | TMIO_STAT_CARD_INSERT);

	spin_lock_init(&_host->lock);
	mutex_init(&_host->ios_lock);

	/* Init delayed work क्रम request समयouts */
	INIT_DELAYED_WORK(&_host->delayed_reset_work, पंचांगio_mmc_reset_work);
	INIT_WORK(&_host->करोne, पंचांगio_mmc_करोne_work);

	/* See अगर we also get DMA */
	पंचांगio_mmc_request_dma(_host, pdata);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ हटाओ_host;

	dev_pm_qos_expose_latency_limit(&pdev->dev, 100);
	pm_runसमय_put(&pdev->dev);

	वापस 0;

हटाओ_host:
	pm_runसमय_put_noidle(&pdev->dev);
	पंचांगio_mmc_host_हटाओ(_host);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_host_probe);

व्योम पंचांगio_mmc_host_हटाओ(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा platक्रमm_device *pdev = host->pdev;
	काष्ठा mmc_host *mmc = host->mmc;

	pm_runसमय_get_sync(&pdev->dev);

	अगर (host->pdata->flags & TMIO_MMC_SDIO_IRQ)
		sd_ctrl_ग_लिखो16(host, CTL_TRANSACTION_CTL, 0x0000);

	dev_pm_qos_hide_latency_limit(&pdev->dev);

	mmc_हटाओ_host(mmc);
	cancel_work_sync(&host->करोne);
	cancel_delayed_work_sync(&host->delayed_reset_work);
	पंचांगio_mmc_release_dma(host);
	पंचांगio_mmc_disable_mmc_irqs(host, host->sdcard_irq_mask_all);

	अगर (host->native_hotplug)
		pm_runसमय_put_noidle(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_host_हटाओ);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक पंचांगio_mmc_clk_enable(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (!host->clk_enable)
		वापस -ENOTSUPP;

	वापस host->clk_enable(host);
पूर्ण

अटल व्योम पंचांगio_mmc_clk_disable(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->clk_disable)
		host->clk_disable(host);
पूर्ण

पूर्णांक पंचांगio_mmc_host_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा पंचांगio_mmc_host *host = dev_get_drvdata(dev);

	पंचांगio_mmc_disable_mmc_irqs(host, host->sdcard_irq_mask_all);

	अगर (host->clk_cache)
		host->set_घड़ी(host, 0);

	पंचांगio_mmc_clk_disable(host);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_host_runसमय_suspend);

पूर्णांक पंचांगio_mmc_host_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा पंचांगio_mmc_host *host = dev_get_drvdata(dev);

	पंचांगio_mmc_clk_enable(host);
	पंचांगio_mmc_reset(host);

	अगर (host->clk_cache)
		host->set_घड़ी(host, host->clk_cache);

	अगर (host->native_hotplug)
		पंचांगio_mmc_enable_mmc_irqs(host,
				TMIO_STAT_CARD_REMOVE | TMIO_STAT_CARD_INSERT);

	पंचांगio_mmc_enable_dma(host, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगio_mmc_host_runसमय_resume);
#पूर्ण_अगर

MODULE_LICENSE("GPL v2");
