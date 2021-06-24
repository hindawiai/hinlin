<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Toshiba PCI Secure Digital Host Controller Interface driver
 *
 *  Copyright (C) 2014 Ondrej Zary
 *  Copyright (C) 2007 Riअक्षरd Betts, All Rights Reserved.
 *
 *	Based on asic3_mmc.c, copyright (c) 2005 SDG Systems, LLC and,
 *	sdhci.c, copyright (C) 2005-2006 Pierre Ossman
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>

#समावेश "toshsd.h"

#घोषणा DRIVER_NAME "toshsd"

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA, 0x0805) पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_ids);

अटल व्योम toshsd_init(काष्ठा toshsd_host *host)
अणु
	/* enable घड़ी */
	pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_CLKSTOP,
					SD_PCICFG_CLKSTOP_ENABLE_ALL);
	pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_CARDDETECT, 2);

	/* reset */
	ioग_लिखो16(0, host->ioaddr + SD_SOFTWARERESET); /* निश्चित */
	mdelay(2);
	ioग_लिखो16(1, host->ioaddr + SD_SOFTWARERESET); /* deनिश्चित */
	mdelay(2);

	/* Clear card रेजिस्टरs */
	ioग_लिखो16(0, host->ioaddr + SD_CARDCLOCKCTRL);
	ioग_लिखो32(0, host->ioaddr + SD_CARDSTATUS);
	ioग_लिखो32(0, host->ioaddr + SD_ERRORSTATUS0);
	ioग_लिखो16(0, host->ioaddr + SD_STOPINTERNAL);

	/* SDIO घड़ी? */
	ioग_लिखो16(0x100, host->ioaddr + SDIO_BASE + SDIO_CLOCKNWAITCTRL);

	/* enable LED */
	pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_SDLED_ENABLE1,
					SD_PCICFG_LED_ENABLE1_START);
	pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_SDLED_ENABLE2,
					SD_PCICFG_LED_ENABLE2_START);

	/* set पूर्णांकerrupt masks */
	ioग_लिखो32(~(u32)(SD_CARD_RESP_END | SD_CARD_RW_END
			| SD_CARD_CARD_REMOVED_0 | SD_CARD_CARD_INSERTED_0
			| SD_BUF_READ_ENABLE | SD_BUF_WRITE_ENABLE
			| SD_BUF_CMD_TIMEOUT),
			host->ioaddr + SD_INTMASKCARD);

	ioग_लिखो16(0x1000, host->ioaddr + SD_TRANSACTIONCTRL);
पूर्ण

/* Set MMC घड़ी / घातer.
 * Note: This controller uses a simple भागider scheme thereक्रमe it cannot run
 * SD/MMC cards at full speed (24/20MHz). HCLK (=33MHz PCI घड़ी?) is too high
 * and the next slowest is 16MHz (भाग=2).
 */
अटल व्योम __toshsd_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा toshsd_host *host = mmc_priv(mmc);

	अगर (ios->घड़ी) अणु
		u16 clk;
		पूर्णांक भाग = 1;

		जबतक (ios->घड़ी < HCLK / भाग)
			भाग *= 2;

		clk = भाग >> 2;

		अगर (भाग == 1) अणु /* disable the भागider */
			pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_CLKMODE,
					      SD_PCICFG_CLKMODE_DIV_DISABLE);
			clk |= SD_CARDCLK_DIV_DISABLE;
		पूर्ण अन्यथा
			pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_CLKMODE, 0);

		clk |= SD_CARDCLK_ENABLE_CLOCK;
		ioग_लिखो16(clk, host->ioaddr + SD_CARDCLOCKCTRL);

		mdelay(10);
	पूर्ण अन्यथा
		ioग_लिखो16(0, host->ioaddr + SD_CARDCLOCKCTRL);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_POWER1,
					SD_PCICFG_PWR1_OFF);
		mdelay(1);
		अवरोध;
	हाल MMC_POWER_UP:
		अवरोध;
	हाल MMC_POWER_ON:
		pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_POWER1,
					SD_PCICFG_PWR1_33V);
		pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_POWER2,
					SD_PCICFG_PWR2_AUTO);
		mdelay(20);
		अवरोध;
	पूर्ण

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		ioग_लिखो16(SD_CARDOPT_REQUIRED | SD_CARDOPT_DATA_RESP_TIMEOUT(14)
				| SD_CARDOPT_C2_MODULE_ABSENT
				| SD_CARDOPT_DATA_XFR_WIDTH_1,
				host->ioaddr + SD_CARDOPTIONSETUP);
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		ioग_लिखो16(SD_CARDOPT_REQUIRED | SD_CARDOPT_DATA_RESP_TIMEOUT(14)
				| SD_CARDOPT_C2_MODULE_ABSENT
				| SD_CARDOPT_DATA_XFR_WIDTH_4,
				host->ioaddr + SD_CARDOPTIONSETUP);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम toshsd_set_led(काष्ठा toshsd_host *host, अचिन्हित अक्षर state)
अणु
	ioग_लिखो16(state, host->ioaddr + SDIO_BASE + SDIO_LEDCTRL);
पूर्ण

अटल व्योम toshsd_finish_request(काष्ठा toshsd_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;

	/* Write something to end the command */
	host->mrq = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;

	toshsd_set_led(host, 0);
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल irqवापस_t toshsd_thपढ़ो_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा toshsd_host *host = dev_id;
	काष्ठा mmc_data *data = host->data;
	काष्ठा sg_mapping_iter *sg_miter = &host->sg_miter;
	अचिन्हित लघु *buf;
	पूर्णांक count;
	अचिन्हित दीर्घ flags;

	अगर (!data) अणु
		dev_warn(&host->pdev->dev, "Spurious Data IRQ\n");
		अगर (host->cmd) अणु
			host->cmd->error = -EIO;
			toshsd_finish_request(host);
		पूर्ण
		वापस IRQ_NONE;
	पूर्ण
	spin_lock_irqsave(&host->lock, flags);

	अगर (!sg_miter_next(sg_miter))
		जाओ करोne;

	buf = sg_miter->addr;

	/* Ensure we करोnt पढ़ो more than one block. The chip will पूर्णांकerrupt us
	 * When the next block is available.
	 */
	count = sg_miter->length;
	अगर (count > data->blksz)
		count = data->blksz;

	dev_dbg(&host->pdev->dev, "count: %08x, flags %08x\n", count,
		data->flags);

	/* Transfer the data */
	अगर (data->flags & MMC_DATA_READ)
		ioपढ़ो32_rep(host->ioaddr + SD_DATAPORT, buf, count >> 2);
	अन्यथा
		ioग_लिखो32_rep(host->ioaddr + SD_DATAPORT, buf, count >> 2);

	sg_miter->consumed = count;
	sg_miter_stop(sg_miter);

करोne:
	spin_unlock_irqrestore(&host->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम toshsd_cmd_irq(काष्ठा toshsd_host *host)
अणु
	काष्ठा mmc_command *cmd = host->cmd;
	u8 *buf;
	u16 data;

	अगर (!host->cmd) अणु
		dev_warn(&host->pdev->dev, "Spurious CMD irq\n");
		वापस;
	पूर्ण
	buf = (u8 *)cmd->resp;
	host->cmd = शून्य;

	अगर (cmd->flags & MMC_RSP_PRESENT && cmd->flags & MMC_RSP_136) अणु
		/* R2 */
		buf[12] = 0xff;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE0);
		buf[13] = data & 0xff;
		buf[14] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE1);
		buf[15] = data & 0xff;
		buf[8] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE2);
		buf[9] = data & 0xff;
		buf[10] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE3);
		buf[11] = data & 0xff;
		buf[4] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE4);
		buf[5] = data & 0xff;
		buf[6] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE5);
		buf[7] = data & 0xff;
		buf[0] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE6);
		buf[1] = data & 0xff;
		buf[2] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE7);
		buf[3] = data & 0xff;
	पूर्ण अन्यथा अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		/* R1, R1B, R3, R6, R7 */
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE0);
		buf[0] = data & 0xff;
		buf[1] = data >> 8;
		data = ioपढ़ो16(host->ioaddr + SD_RESPONSE1);
		buf[2] = data & 0xff;
		buf[3] = data >> 8;
	पूर्ण

	dev_dbg(&host->pdev->dev, "Command IRQ complete %d %d %x\n",
		cmd->opcode, cmd->error, cmd->flags);

	/* If there is data to handle we will
	 * finish the request in the mmc_data_end_irq handler.*/
	अगर (host->data)
		वापस;

	toshsd_finish_request(host);
पूर्ण

अटल व्योम toshsd_data_end_irq(काष्ठा toshsd_host *host)
अणु
	काष्ठा mmc_data *data = host->data;

	host->data = शून्य;

	अगर (!data) अणु
		dev_warn(&host->pdev->dev, "Spurious data end IRQ\n");
		वापस;
	पूर्ण

	अगर (data->error == 0)
		data->bytes_xfered = data->blocks * data->blksz;
	अन्यथा
		data->bytes_xfered = 0;

	dev_dbg(&host->pdev->dev, "Completed data request xfr=%d\n",
		data->bytes_xfered);

	ioग_लिखो16(0, host->ioaddr + SD_STOPINTERNAL);

	toshsd_finish_request(host);
पूर्ण

अटल irqवापस_t toshsd_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा toshsd_host *host = dev_id;
	u32 पूर्णांक_reg, पूर्णांक_mask, पूर्णांक_status, detail;
	पूर्णांक error = 0, ret = IRQ_HANDLED;

	spin_lock(&host->lock);
	पूर्णांक_status = ioपढ़ो32(host->ioaddr + SD_CARDSTATUS);
	पूर्णांक_mask = ioपढ़ो32(host->ioaddr + SD_INTMASKCARD);
	पूर्णांक_reg = पूर्णांक_status & ~पूर्णांक_mask & ~IRQ_DONT_CARE_BITS;

	dev_dbg(&host->pdev->dev, "IRQ status:%x mask:%x\n",
		पूर्णांक_status, पूर्णांक_mask);

	/* nothing to करो: it's not our IRQ */
	अगर (!पूर्णांक_reg) अणु
		ret = IRQ_NONE;
		जाओ irq_end;
	पूर्ण

	अगर (पूर्णांक_reg & SD_BUF_CMD_TIMEOUT) अणु
		error = -ETIMEDOUT;
		dev_dbg(&host->pdev->dev, "Timeout\n");
	पूर्ण अन्यथा अगर (पूर्णांक_reg & SD_BUF_CRC_ERR) अणु
		error = -EILSEQ;
		dev_err(&host->pdev->dev, "BadCRC\n");
	पूर्ण अन्यथा अगर (पूर्णांक_reg & (SD_BUF_ILLEGAL_ACCESS
				| SD_BUF_CMD_INDEX_ERR
				| SD_BUF_STOP_BIT_END_ERR
				| SD_BUF_OVERFLOW
				| SD_BUF_UNDERFLOW
				| SD_BUF_DATA_TIMEOUT)) अणु
		dev_err(&host->pdev->dev, "Buffer status error: { %s%s%s%s%s%s}\n",
			पूर्णांक_reg & SD_BUF_ILLEGAL_ACCESS ? "ILLEGAL_ACC " : "",
			पूर्णांक_reg & SD_BUF_CMD_INDEX_ERR ? "CMD_INDEX " : "",
			पूर्णांक_reg & SD_BUF_STOP_BIT_END_ERR ? "STOPBIT_END " : "",
			पूर्णांक_reg & SD_BUF_OVERFLOW ? "OVERFLOW " : "",
			पूर्णांक_reg & SD_BUF_UNDERFLOW ? "UNDERFLOW " : "",
			पूर्णांक_reg & SD_BUF_DATA_TIMEOUT ? "DATA_TIMEOUT " : "");

		detail = ioपढ़ो32(host->ioaddr + SD_ERRORSTATUS0);
		dev_err(&host->pdev->dev, "detail error status { %s%s%s%s%s%s%s%s%s%s%s%s%s}\n",
			detail & SD_ERR0_RESP_CMD_ERR ? "RESP_CMD " : "",
			detail & SD_ERR0_RESP_NON_CMD12_END_BIT_ERR ? "RESP_END_BIT " : "",
			detail & SD_ERR0_RESP_CMD12_END_BIT_ERR ? "RESP_END_BIT " : "",
			detail & SD_ERR0_READ_DATA_END_BIT_ERR ? "READ_DATA_END_BIT " : "",
			detail & SD_ERR0_WRITE_CRC_STATUS_END_BIT_ERR ? "WRITE_CMD_END_BIT " : "",
			detail & SD_ERR0_RESP_NON_CMD12_CRC_ERR ? "RESP_CRC " : "",
			detail & SD_ERR0_RESP_CMD12_CRC_ERR ? "RESP_CRC " : "",
			detail & SD_ERR0_READ_DATA_CRC_ERR ? "READ_DATA_CRC " : "",
			detail & SD_ERR0_WRITE_CMD_CRC_ERR ? "WRITE_CMD_CRC " : "",
			detail & SD_ERR1_NO_CMD_RESP ? "NO_CMD_RESP " : "",
			detail & SD_ERR1_TIMEOUT_READ_DATA ? "READ_DATA_TIMEOUT " : "",
			detail & SD_ERR1_TIMEOUT_CRS_STATUS ? "CRS_STATUS_TIMEOUT " : "",
			detail & SD_ERR1_TIMEOUT_CRC_BUSY ? "CRC_BUSY_TIMEOUT " : "");
		error = -EIO;
	पूर्ण

	अगर (error) अणु
		अगर (host->cmd)
			host->cmd->error = error;

		अगर (error == -ETIMEDOUT) अणु
			ioग_लिखो32(पूर्णांक_status &
				  ~(SD_BUF_CMD_TIMEOUT | SD_CARD_RESP_END),
				  host->ioaddr + SD_CARDSTATUS);
		पूर्ण अन्यथा अणु
			toshsd_init(host);
			__toshsd_set_ios(host->mmc, &host->mmc->ios);
			जाओ irq_end;
		पूर्ण
	पूर्ण

	/* Card insert/हटाओ. The mmc controlling code is stateless. */
	अगर (पूर्णांक_reg & (SD_CARD_CARD_INSERTED_0 | SD_CARD_CARD_REMOVED_0)) अणु
		ioग_लिखो32(पूर्णांक_status &
			  ~(SD_CARD_CARD_REMOVED_0 | SD_CARD_CARD_INSERTED_0),
			  host->ioaddr + SD_CARDSTATUS);

		अगर (पूर्णांक_reg & SD_CARD_CARD_INSERTED_0)
			toshsd_init(host);

		mmc_detect_change(host->mmc, 1);
	पूर्ण

	/* Data transfer */
	अगर (पूर्णांक_reg & (SD_BUF_READ_ENABLE | SD_BUF_WRITE_ENABLE)) अणु
		ioग_लिखो32(पूर्णांक_status &
			  ~(SD_BUF_WRITE_ENABLE | SD_BUF_READ_ENABLE),
			  host->ioaddr + SD_CARDSTATUS);

		ret = IRQ_WAKE_THREAD;
		जाओ irq_end;
	पूर्ण

	/* Command completion */
	अगर (पूर्णांक_reg & SD_CARD_RESP_END) अणु
		ioग_लिखो32(पूर्णांक_status & ~(SD_CARD_RESP_END),
			  host->ioaddr + SD_CARDSTATUS);
		toshsd_cmd_irq(host);
	पूर्ण

	/* Data transfer completion */
	अगर (पूर्णांक_reg & SD_CARD_RW_END) अणु
		ioग_लिखो32(पूर्णांक_status & ~(SD_CARD_RW_END),
			  host->ioaddr + SD_CARDSTATUS);
		toshsd_data_end_irq(host);
	पूर्ण
irq_end:
	spin_unlock(&host->lock);
	वापस ret;
पूर्ण

अटल व्योम toshsd_start_cmd(काष्ठा toshsd_host *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक c = cmd->opcode;

	dev_dbg(&host->pdev->dev, "Command opcode: %d\n", cmd->opcode);

	अगर (cmd->opcode == MMC_STOP_TRANSMISSION) अणु
		ioग_लिखो16(SD_STOPINT_ISSUE_CMD12,
			  host->ioaddr + SD_STOPINTERNAL);

		cmd->resp[0] = cmd->opcode;
		cmd->resp[1] = 0;
		cmd->resp[2] = 0;
		cmd->resp[3] = 0;

		toshsd_finish_request(host);
		वापस;
	पूर्ण

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		c |= SD_CMD_RESP_TYPE_NONE;
		अवरोध;

	हाल MMC_RSP_R1:
		c |= SD_CMD_RESP_TYPE_EXT_R1;
		अवरोध;
	हाल MMC_RSP_R1B:
		c |= SD_CMD_RESP_TYPE_EXT_R1B;
		अवरोध;
	हाल MMC_RSP_R2:
		c |= SD_CMD_RESP_TYPE_EXT_R2;
		अवरोध;
	हाल MMC_RSP_R3:
		c |= SD_CMD_RESP_TYPE_EXT_R3;
		अवरोध;

	शेष:
		dev_err(&host->pdev->dev, "Unknown response type %d\n",
			mmc_resp_type(cmd));
		अवरोध;
	पूर्ण

	host->cmd = cmd;

	अगर (cmd->opcode == MMC_APP_CMD)
		c |= SD_CMD_TYPE_ACMD;

	अगर (cmd->opcode == MMC_GO_IDLE_STATE)
		c |= (3 << 8);  /* हटाओd from ipaq-asic3.h क्रम some reason */

	अगर (data) अणु
		c |= SD_CMD_DATA_PRESENT;

		अगर (data->blocks > 1) अणु
			ioग_लिखो16(SD_STOPINT_AUTO_ISSUE_CMD12,
				  host->ioaddr + SD_STOPINTERNAL);
			c |= SD_CMD_MULTI_BLOCK;
		पूर्ण

		अगर (data->flags & MMC_DATA_READ)
			c |= SD_CMD_TRANSFER_READ;

		/* MMC_DATA_WRITE करोes not require a bit to be set */
	पूर्ण

	/* Send the command */
	ioग_लिखो32(cmd->arg, host->ioaddr + SD_ARG0);
	ioग_लिखो16(c, host->ioaddr + SD_CMD);
पूर्ण

अटल व्योम toshsd_start_data(काष्ठा toshsd_host *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक flags = SG_MITER_ATOMIC;

	dev_dbg(&host->pdev->dev, "setup data transfer: blocksize %08x  nr_blocks %d, offset: %08x\n",
		data->blksz, data->blocks, data->sg->offset);

	host->data = data;

	अगर (data->flags & MMC_DATA_READ)
		flags |= SG_MITER_TO_SG;
	अन्यथा
		flags |= SG_MITER_FROM_SG;

	sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);

	/* Set transfer length and blocksize */
	ioग_लिखो16(data->blocks, host->ioaddr + SD_BLOCKCOUNT);
	ioग_लिखो16(data->blksz, host->ioaddr + SD_CARDXFERDATALEN);
पूर्ण

/* Process requests from the MMC layer */
अटल व्योम toshsd_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा toshsd_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	/* पात अगर card not present */
	अगर (!(ioपढ़ो16(host->ioaddr + SD_CARDSTATUS) & SD_CARD_PRESENT_0)) अणु
		mrq->cmd->error = -ENOMEDIUM;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);

	WARN_ON(host->mrq != शून्य);

	host->mrq = mrq;

	अगर (mrq->data)
		toshsd_start_data(host, mrq->data);

	toshsd_set_led(host, 1);

	toshsd_start_cmd(host, mrq->cmd);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम toshsd_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा toshsd_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	__toshsd_set_ios(mmc, ios);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल पूर्णांक toshsd_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा toshsd_host *host = mmc_priv(mmc);

	/* active low */
	वापस !(ioपढ़ो16(host->ioaddr + SD_CARDSTATUS) & SD_CARD_WRITE_PROTECT);
पूर्ण

अटल पूर्णांक toshsd_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा toshsd_host *host = mmc_priv(mmc);

	वापस !!(ioपढ़ो16(host->ioaddr + SD_CARDSTATUS) & SD_CARD_PRESENT_0);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops toshsd_ops = अणु
	.request = toshsd_request,
	.set_ios = toshsd_set_ios,
	.get_ro = toshsd_get_ro,
	.get_cd = toshsd_get_cd,
पूर्ण;


अटल व्योम toshsd_घातerकरोwn(काष्ठा toshsd_host *host)
अणु
	/* mask all पूर्णांकerrupts */
	ioग_लिखो32(0xffffffff, host->ioaddr + SD_INTMASKCARD);
	/* disable card घड़ी */
	ioग_लिखो16(0x000, host->ioaddr + SDIO_BASE + SDIO_CLOCKNWAITCTRL);
	ioग_लिखो16(0, host->ioaddr + SD_CARDCLOCKCTRL);
	/* घातer करोwn card */
	pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_POWER1, SD_PCICFG_PWR1_OFF);
	/* disable घड़ी */
	pci_ग_लिखो_config_byte(host->pdev, SD_PCICFG_CLKSTOP, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक toshsd_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा toshsd_host *host = pci_get_drvdata(pdev);

	toshsd_घातerकरोwn(host);

	pci_save_state(pdev);
	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक toshsd_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा toshsd_host *host = pci_get_drvdata(pdev);
	पूर्णांक ret;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	toshsd_init(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक toshsd_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;
	काष्ठा toshsd_host *host;
	काष्ठा mmc_host *mmc;
	resource_माप_प्रकार base;

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	mmc = mmc_alloc_host(माप(काष्ठा toshsd_host), &pdev->dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc = mmc;

	host->pdev = pdev;
	pci_set_drvdata(pdev, host);

	ret = pci_request_regions(pdev, DRIVER_NAME);
	अगर (ret)
		जाओ मुक्त;

	host->ioaddr = pci_iomap(pdev, 0, 0);
	अगर (!host->ioaddr) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	/* Set MMC host parameters */
	mmc->ops = &toshsd_ops;
	mmc->caps = MMC_CAP_4_BIT_DATA;
	mmc->ocr_avail = MMC_VDD_32_33;

	mmc->f_min = HCLK / 512;
	mmc->f_max = HCLK;

	spin_lock_init(&host->lock);

	toshsd_init(host);

	ret = request_thपढ़ोed_irq(pdev->irq, toshsd_irq, toshsd_thपढ़ो_irq,
				   IRQF_SHARED, DRIVER_NAME, host);
	अगर (ret)
		जाओ unmap;

	mmc_add_host(mmc);

	base = pci_resource_start(pdev, 0);
	dev_dbg(&pdev->dev, "MMIO %pa, IRQ %d\n", &base, pdev->irq);

	pm_suspend_ignore_children(&pdev->dev, 1);

	वापस 0;

unmap:
	pci_iounmap(pdev, host->ioaddr);
release:
	pci_release_regions(pdev);
मुक्त:
	mmc_मुक्त_host(mmc);
	pci_set_drvdata(pdev, शून्य);
err:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम toshsd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा toshsd_host *host = pci_get_drvdata(pdev);

	mmc_हटाओ_host(host->mmc);
	toshsd_घातerकरोwn(host);
	मुक्त_irq(pdev->irq, host);
	pci_iounmap(pdev, host->ioaddr);
	pci_release_regions(pdev);
	mmc_मुक्त_host(host->mmc);
	pci_set_drvdata(pdev, शून्य);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops toshsd_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(toshsd_pm_suspend, toshsd_pm_resume)
पूर्ण;

अटल काष्ठा pci_driver toshsd_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pci_ids,
	.probe = toshsd_probe,
	.हटाओ = toshsd_हटाओ,
	.driver.pm = &toshsd_pm_ops,
पूर्ण;

module_pci_driver(toshsd_driver);

MODULE_AUTHOR("Ondrej Zary, Richard Betts");
MODULE_DESCRIPTION("Toshiba PCI Secure Digital Host Controller Interface driver");
MODULE_LICENSE("GPL");
