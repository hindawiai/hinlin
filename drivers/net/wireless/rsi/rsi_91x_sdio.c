<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#समावेश <linux/module.h>
#समावेश "rsi_sdio.h"
#समावेश "rsi_common.h"
#समावेश "rsi_coex.h"
#समावेश "rsi_hal.h"

/* Default operating mode is wlan STA + BT */
अटल u16 dev_oper_mode = DEV_OPMODE_STA_BT_DUAL;
module_param(dev_oper_mode, uलघु, 0444);
MODULE_PARM_DESC(dev_oper_mode,
		 "1[Wi-Fi], 4[BT], 8[BT LE], 5[Wi-Fi STA + BT classic]\n"
		 "9[Wi-Fi STA + BT LE], 13[Wi-Fi STA + BT classic + BT LE]\n"
		 "6[AP + BT classic], 14[AP + BT classic + BT LE]");

/**
 * rsi_sdio_set_cmd52_arg() - This function prepares cmd 52 पढ़ो/ग_लिखो arg.
 * @rw: Read/ग_लिखो
 * @func: function number
 * @raw: indicates whether to perक्रमm पढ़ो after ग_लिखो
 * @address: address to which to पढ़ो/ग_लिखो
 * @ग_लिखोdata: data to ग_लिखो
 *
 * Return: argument
 */
अटल u32 rsi_sdio_set_cmd52_arg(bool rw,
				  u8 func,
				  u8 raw,
				  u32 address,
				  u8 ग_लिखोdata)
अणु
	वापस ((rw & 1) << 31) | ((func & 0x7) << 28) |
		((raw & 1) << 27) | (1 << 26) |
		((address & 0x1FFFF) << 9) | (1 << 8) |
		(ग_लिखोdata & 0xFF);
पूर्ण

/**
 * rsi_cmd52ग_लिखोbyte() - This function issues cmd52 byte ग_लिखो onto the card.
 * @card: Poपूर्णांकer to the mmc_card.
 * @address: Address to ग_लिखो.
 * @byte: Data to ग_लिखो.
 *
 * Return: Write status.
 */
अटल पूर्णांक rsi_cmd52ग_लिखोbyte(काष्ठा mmc_card *card,
			      u32 address,
			      u8 byte)
अणु
	काष्ठा mmc_command io_cmd;
	u32 arg;

	स_रखो(&io_cmd, 0, माप(io_cmd));
	arg = rsi_sdio_set_cmd52_arg(1, 0, 0, address, byte);
	io_cmd.opcode = SD_IO_RW_सूचीECT;
	io_cmd.arg = arg;
	io_cmd.flags = MMC_RSP_R5 | MMC_CMD_AC;

	वापस mmc_रुको_क्रम_cmd(card->host, &io_cmd, 0);
पूर्ण

/**
 * rsi_cmd52पढ़ोbyte() - This function issues cmd52 byte पढ़ो onto the card.
 * @card: Poपूर्णांकer to the mmc_card.
 * @address: Address to पढ़ो from.
 * @byte: Variable to store पढ़ो value.
 *
 * Return: Read status.
 */
अटल पूर्णांक rsi_cmd52पढ़ोbyte(काष्ठा mmc_card *card,
			     u32 address,
			     u8 *byte)
अणु
	काष्ठा mmc_command io_cmd;
	u32 arg;
	पूर्णांक err;

	स_रखो(&io_cmd, 0, माप(io_cmd));
	arg = rsi_sdio_set_cmd52_arg(0, 0, 0, address, 0);
	io_cmd.opcode = SD_IO_RW_सूचीECT;
	io_cmd.arg = arg;
	io_cmd.flags = MMC_RSP_R5 | MMC_CMD_AC;

	err = mmc_रुको_क्रम_cmd(card->host, &io_cmd, 0);
	अगर ((!err) && (byte))
		*byte =  io_cmd.resp[0] & 0xFF;
	वापस err;
पूर्ण

/**
 * rsi_issue_sdiocommand() - This function issues sdio commands.
 * @func: Poपूर्णांकer to the sdio_func काष्ठाure.
 * @opcode: Opcode value.
 * @arg: Arguments to pass.
 * @flags: Flags which are set.
 * @resp: Poपूर्णांकer to store response.
 *
 * Return: err: command status as 0 or -1.
 */
अटल पूर्णांक rsi_issue_sdiocommand(काष्ठा sdio_func *func,
				 u32 opcode,
				 u32 arg,
				 u32 flags,
				 u32 *resp)
अणु
	काष्ठा mmc_command cmd;
	काष्ठा mmc_host *host;
	पूर्णांक err;

	host = func->card->host;

	स_रखो(&cmd, 0, माप(काष्ठा mmc_command));
	cmd.opcode = opcode;
	cmd.arg = arg;
	cmd.flags = flags;
	err = mmc_रुको_क्रम_cmd(host, &cmd, 3);

	अगर ((!err) && (resp))
		*resp = cmd.resp[0];

	वापस err;
पूर्ण

/**
 * rsi_handle_पूर्णांकerrupt() - This function is called upon the occurrence
 *			    of an पूर्णांकerrupt.
 * @function: Poपूर्णांकer to the sdio_func काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_handle_पूर्णांकerrupt(काष्ठा sdio_func *function)
अणु
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(function);
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;

	अगर (adapter->priv->fsm_state == FSM_FW_NOT_LOADED)
		वापस;

	rsi_set_event(&dev->rx_thपढ़ो.event);
पूर्ण

/**
 * rsi_reset_card() - This function resets and re-initializes the card.
 * @pfunction: Poपूर्णांकer to the sdio_func काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_reset_card(काष्ठा sdio_func *pfunction)
अणु
	पूर्णांक ret = 0;
	पूर्णांक err;
	काष्ठा mmc_card *card = pfunction->card;
	काष्ठा mmc_host *host = card->host;
	u8 cmd52_resp;
	u32 घड़ी, resp, i;
	u16 rca;

	/* Reset 9110 chip */
	ret = rsi_cmd52ग_लिखोbyte(pfunction->card,
				 SDIO_CCCR_ABORT,
				 (1 << 3));

	/* Card will not send any response as it is getting reset immediately
	 * Hence expect a समयout status from host controller
	 */
	अगर (ret != -ETIMEDOUT)
		rsi_dbg(ERR_ZONE, "%s: Reset failed : %d\n", __func__, ret);

	/* Wait क्रम few milli seconds to get rid of residue अक्षरges अगर any */
	msleep(20);

	/* Initialize the SDIO card */
	host->ios.chip_select = MMC_CS_DONTCARE;
	host->ios.bus_mode = MMC_BUSMODE_OPENDRAIN;
	host->ios.घातer_mode = MMC_POWER_UP;
	host->ios.bus_width = MMC_BUS_WIDTH_1;
	host->ios.timing = MMC_TIMING_LEGACY;
	host->ops->set_ios(host, &host->ios);

	/*
	 * This delay should be sufficient to allow the घातer supply
	 * to reach the minimum voltage.
	 */
	msleep(20);

	host->ios.घड़ी = host->f_min;
	host->ios.घातer_mode = MMC_POWER_ON;
	host->ops->set_ios(host, &host->ios);

	/*
	 * This delay must be at least 74 घड़ी sizes, or 1 ms, or the
	 * समय required to reach a stable voltage.
	 */
	msleep(20);

	/* Issue CMD0. Goto idle state */
	host->ios.chip_select = MMC_CS_HIGH;
	host->ops->set_ios(host, &host->ios);
	msleep(20);
	err = rsi_issue_sdiocommand(pfunction,
				    MMC_GO_IDLE_STATE,
				    0,
				    (MMC_RSP_NONE | MMC_CMD_BC),
				    शून्य);
	host->ios.chip_select = MMC_CS_DONTCARE;
	host->ops->set_ios(host, &host->ios);
	msleep(20);
	host->use_spi_crc = 0;

	अगर (err)
		rsi_dbg(ERR_ZONE, "%s: CMD0 failed : %d\n", __func__, err);

	/* Issue CMD5, arg = 0 */
	err = rsi_issue_sdiocommand(pfunction,	SD_IO_SEND_OP_COND, 0,
				    (MMC_RSP_R4 | MMC_CMD_BCR), &resp);
	अगर (err)
		rsi_dbg(ERR_ZONE, "%s: CMD5 failed : %d\n",
			__func__, err);
	card->ocr = resp;
	/* Issue CMD5, arg = ocr. Wait till card is पढ़ोy  */
	क्रम (i = 0; i < 100; i++) अणु
		err = rsi_issue_sdiocommand(pfunction, SD_IO_SEND_OP_COND,
					    card->ocr,
					    (MMC_RSP_R4 | MMC_CMD_BCR), &resp);
		अगर (err) अणु
			rsi_dbg(ERR_ZONE, "%s: CMD5 failed : %d\n",
				__func__, err);
			अवरोध;
		पूर्ण

		अगर (resp & MMC_CARD_BUSY)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर ((i == 100) || (err)) अणु
		rsi_dbg(ERR_ZONE, "%s: card in not ready : %d %d\n",
			__func__, i, err);
		वापस;
	पूर्ण

	/* Issue CMD3, get RCA */
	err = rsi_issue_sdiocommand(pfunction,
				    SD_SEND_RELATIVE_ADDR,
				    0,
				    (MMC_RSP_R6 | MMC_CMD_BCR),
				    &resp);
	अगर (err) अणु
		rsi_dbg(ERR_ZONE, "%s: CMD3 failed : %d\n", __func__, err);
		वापस;
	पूर्ण
	rca = resp >> 16;
	host->ios.bus_mode = MMC_BUSMODE_PUSHPULL;
	host->ops->set_ios(host, &host->ios);

	/* Issue CMD7, select card  */
	err = rsi_issue_sdiocommand(pfunction,
				    MMC_SELECT_CARD,
				    (rca << 16),
				    (MMC_RSP_R1 | MMC_CMD_AC),
				    शून्य);
	अगर (err) अणु
		rsi_dbg(ERR_ZONE, "%s: CMD7 failed : %d\n", __func__, err);
		वापस;
	पूर्ण

	/* Enable high speed */
	अगर (card->host->caps & MMC_CAP_SD_HIGHSPEED) अणु
		rsi_dbg(ERR_ZONE, "%s: Set high speed mode\n", __func__);
		err = rsi_cmd52पढ़ोbyte(card, SDIO_CCCR_SPEED, &cmd52_resp);
		अगर (err) अणु
			rsi_dbg(ERR_ZONE, "%s: CCCR speed reg read failed: %d\n",
				__func__, err);
		पूर्ण अन्यथा अणु
			err = rsi_cmd52ग_लिखोbyte(card,
						 SDIO_CCCR_SPEED,
						 (cmd52_resp | SDIO_SPEED_EHS));
			अगर (err) अणु
				rsi_dbg(ERR_ZONE,
					"%s: CCR speed regwrite failed %d\n",
					__func__, err);
				वापस;
			पूर्ण
			host->ios.timing = MMC_TIMING_SD_HS;
			host->ops->set_ios(host, &host->ios);
		पूर्ण
	पूर्ण

	/* Set घड़ी */
	अगर (mmc_card_hs(card))
		घड़ी = 50000000;
	अन्यथा
		घड़ी = card->cis.max_dtr;

	अगर (घड़ी > host->f_max)
		घड़ी = host->f_max;

	host->ios.घड़ी = घड़ी;
	host->ops->set_ios(host, &host->ios);

	अगर (card->host->caps & MMC_CAP_4_BIT_DATA) अणु
		/* CMD52: Set bus width & disable card detect resistor */
		err = rsi_cmd52ग_लिखोbyte(card,
					 SDIO_CCCR_IF,
					 (SDIO_BUS_CD_DISABLE |
					  SDIO_BUS_WIDTH_4BIT));
		अगर (err) अणु
			rsi_dbg(ERR_ZONE, "%s: Set bus mode failed : %d\n",
				__func__, err);
			वापस;
		पूर्ण
		host->ios.bus_width = MMC_BUS_WIDTH_4;
		host->ops->set_ios(host, &host->ios);
	पूर्ण
पूर्ण

/**
 * rsi_setघड़ी() - This function sets the घड़ी frequency.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @freq: Clock frequency.
 *
 * Return: None.
 */
अटल व्योम rsi_setघड़ी(काष्ठा rsi_hw *adapter, u32 freq)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	काष्ठा mmc_host *host = dev->pfunction->card->host;
	u32 घड़ी;

	घड़ी = freq * 1000;
	अगर (घड़ी > host->f_max)
		घड़ी = host->f_max;
	host->ios.घड़ी = घड़ी;
	host->ops->set_ios(host, &host->ios);
पूर्ण

/**
 * rsi_setblocklength() - This function sets the host block length.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @length: Block length to be set.
 *
 * Return: status: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_setblocklength(काष्ठा rsi_hw *adapter, u32 length)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	पूर्णांक status;
	rsi_dbg(INIT_ZONE, "%s: Setting the block length\n", __func__);

	status = sdio_set_block_size(dev->pfunction, length);
	dev->pfunction->max_blksize = 256;
	adapter->block_size = dev->pfunction->max_blksize;

	rsi_dbg(INFO_ZONE,
		"%s: Operational blk length is %d\n", __func__, length);
	वापस status;
पूर्ण

/**
 * rsi_setupcard() - This function queries and sets the card's features.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: status: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_setupcard(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	पूर्णांक status = 0;

	rsi_setघड़ी(adapter, 50000);

	dev->tx_blk_size = 256;
	status = rsi_setblocklength(adapter, dev->tx_blk_size);
	अगर (status)
		rsi_dbg(ERR_ZONE,
			"%s: Unable to set block length\n", __func__);
	वापस status;
पूर्ण

/**
 * rsi_sdio_पढ़ो_रेजिस्टर() - This function पढ़ोs one byte of inक्रमmation
 *			      from a रेजिस्टर.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @addr: Address of the रेजिस्टर.
 * @data: Poपूर्णांकer to the data that stores the data पढ़ो.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_sdio_पढ़ो_रेजिस्टर(काष्ठा rsi_hw *adapter,
			   u32 addr,
			   u8 *data)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	u8 fun_num = 0;
	पूर्णांक status;

	अगर (likely(dev->sdio_irq_task != current))
		sdio_claim_host(dev->pfunction);

	अगर (fun_num == 0)
		*data = sdio_f0_पढ़ोb(dev->pfunction, addr, &status);
	अन्यथा
		*data = sdio_पढ़ोb(dev->pfunction, addr, &status);

	अगर (likely(dev->sdio_irq_task != current))
		sdio_release_host(dev->pfunction);

	वापस status;
पूर्ण

/**
 * rsi_sdio_ग_लिखो_रेजिस्टर() - This function ग_लिखोs one byte of inक्रमmation
 *			       पूर्णांकo a रेजिस्टर.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @function: Function Number.
 * @addr: Address of the रेजिस्टर.
 * @data: Poपूर्णांकer to the data tha has to be written.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_sdio_ग_लिखो_रेजिस्टर(काष्ठा rsi_hw *adapter,
			    u8 function,
			    u32 addr,
			    u8 *data)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	पूर्णांक status = 0;

	अगर (likely(dev->sdio_irq_task != current))
		sdio_claim_host(dev->pfunction);

	अगर (function == 0)
		sdio_f0_ग_लिखोb(dev->pfunction, *data, addr, &status);
	अन्यथा
		sdio_ग_लिखोb(dev->pfunction, *data, addr, &status);

	अगर (likely(dev->sdio_irq_task != current))
		sdio_release_host(dev->pfunction);

	वापस status;
पूर्ण

/**
 * rsi_sdio_ack_पूर्णांकr() - This function acks the पूर्णांकerrupt received.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @पूर्णांक_bit: Interrupt bit to ग_लिखो पूर्णांकo रेजिस्टर.
 *
 * Return: None.
 */
व्योम rsi_sdio_ack_पूर्णांकr(काष्ठा rsi_hw *adapter, u8 पूर्णांक_bit)
अणु
	पूर्णांक status;
	status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
					 1,
					 (SDIO_FUN1_INTR_CLR_REG |
					  RSI_SD_REQUEST_MASTER),
					 &पूर्णांक_bit);
	अगर (status)
		rsi_dbg(ERR_ZONE, "%s: unable to send ack\n", __func__);
पूर्ण



/**
 * rsi_sdio_पढ़ो_रेजिस्टर_multiple() - This function पढ़ो multiple bytes of
 *				       inक्रमmation from the SD card.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @addr: Address of the रेजिस्टर.
 * @count: Number of multiple bytes to be पढ़ो.
 * @data: Poपूर्णांकer to the पढ़ो data.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_sdio_पढ़ो_रेजिस्टर_multiple(काष्ठा rsi_hw *adapter,
					   u32 addr,
					   u8 *data,
					   u16 count)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	u32 status;

	अगर (likely(dev->sdio_irq_task != current))
		sdio_claim_host(dev->pfunction);

	status =  sdio_पढ़ोsb(dev->pfunction, data, addr, count);

	अगर (likely(dev->sdio_irq_task != current))
		sdio_release_host(dev->pfunction);

	अगर (status != 0)
		rsi_dbg(ERR_ZONE, "%s: Synch Cmd53 read failed\n", __func__);
	वापस status;
पूर्ण

/**
 * rsi_sdio_ग_लिखो_रेजिस्टर_multiple() - This function ग_लिखोs multiple bytes of
 *					inक्रमmation to the SD card.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @addr: Address of the रेजिस्टर.
 * @data: Poपूर्णांकer to the data that has to be written.
 * @count: Number of multiple bytes to be written.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_sdio_ग_लिखो_रेजिस्टर_multiple(काष्ठा rsi_hw *adapter,
				     u32 addr,
				     u8 *data,
				     u16 count)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	पूर्णांक status;

	अगर (dev->ग_लिखो_fail > 1) अणु
		rsi_dbg(ERR_ZONE, "%s: Stopping card writes\n", __func__);
		वापस 0;
	पूर्ण अन्यथा अगर (dev->ग_लिखो_fail == 1) अणु
		/**
		 * Assuming it is a CRC failure, we want to allow another
		 *  card ग_लिखो
		 */
		rsi_dbg(ERR_ZONE, "%s: Continue card writes\n", __func__);
		dev->ग_लिखो_fail++;
	पूर्ण

	अगर (likely(dev->sdio_irq_task != current))
		sdio_claim_host(dev->pfunction);

	status = sdio_ग_लिखोsb(dev->pfunction, addr, data, count);

	अगर (likely(dev->sdio_irq_task != current))
		sdio_release_host(dev->pfunction);

	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Synch Cmd53 write failed %d\n",
			__func__, status);
		dev->ग_लिखो_fail = 2;
	पूर्ण अन्यथा अणु
		स_नकल(dev->prev_desc, data, FRAME_DESC_SZ);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक rsi_sdio_load_data_master_ग_लिखो(काष्ठा rsi_hw *adapter,
					   u32 base_address,
					   u32 inकाष्ठाions_sz,
					   u16 block_size,
					   u8 *ta_firmware)
अणु
	u32 num_blocks, offset, i;
	u16 msb_address, lsb_address;
	u8 *temp_buf;
	पूर्णांक status;

	num_blocks = inकाष्ठाions_sz / block_size;
	msb_address = base_address >> 16;

	rsi_dbg(INFO_ZONE, "ins_size: %d, num_blocks: %d\n",
		inकाष्ठाions_sz, num_blocks);

	temp_buf = kदो_स्मृति(block_size, GFP_KERNEL);
	अगर (!temp_buf)
		वापस -ENOMEM;

	/* Loading DM ms word in the sdio slave */
	status = rsi_sdio_master_access_msword(adapter, msb_address);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to set ms word reg\n", __func__);
		जाओ out_मुक्त;
	पूर्ण

	क्रम (offset = 0, i = 0; i < num_blocks; i++, offset += block_size) अणु
		स_नकल(temp_buf, ta_firmware + offset, block_size);
		lsb_address = (u16)base_address;
		status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple
					(adapter,
					 lsb_address | RSI_SD_REQUEST_MASTER,
					 temp_buf, block_size);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE, "%s: failed to write\n", __func__);
			जाओ out_मुक्त;
		पूर्ण
		rsi_dbg(INFO_ZONE, "%s: loading block: %d\n", __func__, i);
		base_address += block_size;

		अगर ((base_address >> 16) != msb_address) अणु
			msb_address += 1;

			/* Loading DM ms word in the sdio slave */
			status = rsi_sdio_master_access_msword(adapter,
							       msb_address);
			अगर (status < 0) अणु
				rsi_dbg(ERR_ZONE,
					"%s: Unable to set ms word reg\n",
					__func__);
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (inकाष्ठाions_sz % block_size) अणु
		स_रखो(temp_buf, 0, block_size);
		स_नकल(temp_buf, ta_firmware + offset,
		       inकाष्ठाions_sz % block_size);
		lsb_address = (u16)base_address;
		status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple
					(adapter,
					 lsb_address | RSI_SD_REQUEST_MASTER,
					 temp_buf,
					 inकाष्ठाions_sz % block_size);
		अगर (status < 0)
			जाओ out_मुक्त;
		rsi_dbg(INFO_ZONE,
			"Written Last Block in Address 0x%x Successfully\n",
			offset | RSI_SD_REQUEST_MASTER);
	पूर्ण

	status = 0;
out_मुक्त:
	kमुक्त(temp_buf);
	वापस status;
पूर्ण

#घोषणा FLASH_SIZE_ADDR                 0x04000016
अटल पूर्णांक rsi_sdio_master_reg_पढ़ो(काष्ठा rsi_hw *adapter, u32 addr,
				    u32 *पढ़ो_buf, u16 size)
अणु
	u32 addr_on_bus, *data;
	u16 ms_addr;
	पूर्णांक status;

	data = kzalloc(RSI_MASTER_REG_BUF_SIZE, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ms_addr = (addr >> 16);
	status = rsi_sdio_master_access_msword(adapter, ms_addr);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unable to set ms word to common reg\n",
			__func__);
		जाओ err;
	पूर्ण
	addr &= 0xFFFF;

	addr_on_bus = (addr & 0xFF000000);
	अगर ((addr_on_bus == (FLASH_SIZE_ADDR & 0xFF000000)) ||
	    (addr_on_bus == 0x0))
		addr_on_bus = (addr & ~(0x3));
	अन्यथा
		addr_on_bus = addr;

	/* Bring TA out of reset */
	status = rsi_sdio_पढ़ो_रेजिस्टर_multiple
					(adapter,
					 (addr_on_bus | RSI_SD_REQUEST_MASTER),
					 (u8 *)data, 4);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "%s: AHB register read failed\n", __func__);
		जाओ err;
	पूर्ण
	अगर (size == 2) अणु
		अगर ((addr & 0x3) == 0)
			*पढ़ो_buf = *data;
		अन्यथा
			*पढ़ो_buf  = (*data >> 16);
		*पढ़ो_buf = (*पढ़ो_buf & 0xFFFF);
	पूर्ण अन्यथा अगर (size == 1) अणु
		अगर ((addr & 0x3) == 0)
			*पढ़ो_buf = *data;
		अन्यथा अगर ((addr & 0x3) == 1)
			*पढ़ो_buf = (*data >> 8);
		अन्यथा अगर ((addr & 0x3) == 2)
			*पढ़ो_buf = (*data >> 16);
		अन्यथा
			*पढ़ो_buf = (*data >> 24);
		*पढ़ो_buf = (*पढ़ो_buf & 0xFF);
	पूर्ण अन्यथा अणु
		*पढ़ो_buf = *data;
	पूर्ण

err:
	kमुक्त(data);
	वापस status;
पूर्ण

अटल पूर्णांक rsi_sdio_master_reg_ग_लिखो(काष्ठा rsi_hw *adapter,
				     अचिन्हित दीर्घ addr,
				     अचिन्हित दीर्घ data, u16 size)
अणु
	अचिन्हित दीर्घ *data_aligned;
	पूर्णांक status;

	data_aligned = kzalloc(RSI_MASTER_REG_BUF_SIZE, GFP_KERNEL);
	अगर (!data_aligned)
		वापस -ENOMEM;

	अगर (size == 2) अणु
		*data_aligned = ((data << 16) | (data & 0xFFFF));
	पूर्ण अन्यथा अगर (size == 1) अणु
		u32 temp_data = data & 0xFF;

		*data_aligned = ((temp_data << 24) | (temp_data << 16) |
				 (temp_data << 8) | temp_data);
	पूर्ण अन्यथा अणु
		*data_aligned = data;
	पूर्ण
	size = 4;

	status = rsi_sdio_master_access_msword(adapter, (addr >> 16));
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unable to set ms word to common reg\n",
			__func__);
		kमुक्त(data_aligned);
		वापस -EIO;
	पूर्ण
	addr = addr & 0xFFFF;

	/* Bring TA out of reset */
	status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple
					(adapter,
					 (addr | RSI_SD_REQUEST_MASTER),
					 (u8 *)data_aligned, size);
	अगर (status < 0)
		rsi_dbg(ERR_ZONE,
			"%s: Unable to do AHB reg write\n", __func__);

	kमुक्त(data_aligned);
	वापस status;
पूर्ण

/**
 * rsi_sdio_host_पूर्णांकf_ग_लिखो_pkt() - This function ग_लिखोs the packet to device.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @pkt: Poपूर्णांकer to the data to be written on to the device.
 * @len: length of the data to be written on to the device.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_sdio_host_पूर्णांकf_ग_लिखो_pkt(काष्ठा rsi_hw *adapter,
					u8 *pkt,
					u32 len)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	u32 block_size = dev->tx_blk_size;
	u32 num_blocks, address, length;
	u32 queueno;
	पूर्णांक status;

	queueno = ((pkt[1] >> 4) & 0xf);
	अगर (queueno == RSI_BT_MGMT_Q || queueno == RSI_BT_DATA_Q)
		queueno = RSI_BT_Q;

	num_blocks = len / block_size;

	अगर (len % block_size)
		num_blocks++;

	address = (num_blocks * block_size | (queueno << 12));
	length  = num_blocks * block_size;

	status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple(adapter,
						  address,
						  (u8 *)pkt,
						  length);
	अगर (status)
		rsi_dbg(ERR_ZONE, "%s: Unable to write onto the card: %d\n",
			__func__, status);
	rsi_dbg(DATA_TX_ZONE, "%s: Successfully written onto card\n", __func__);
	वापस status;
पूर्ण

/**
 * rsi_sdio_host_पूर्णांकf_पढ़ो_pkt() - This function पढ़ोs the packet
 *				   from the device.
 * @adapter: Poपूर्णांकer to the adapter data काष्ठाure.
 * @pkt: Poपूर्णांकer to the packet data to be पढ़ो from the the device.
 * @length: Length of the data to be पढ़ो from the device.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_sdio_host_पूर्णांकf_पढ़ो_pkt(काष्ठा rsi_hw *adapter,
				u8 *pkt,
				u32 length)
अणु
	पूर्णांक status = -EINVAL;

	अगर (!length) अणु
		rsi_dbg(ERR_ZONE, "%s: Pkt size is zero\n", __func__);
		वापस status;
	पूर्ण

	status = rsi_sdio_पढ़ो_रेजिस्टर_multiple(adapter,
						 length,
						 (u8 *)pkt,
						 length); /*num of bytes*/

	अगर (status)
		rsi_dbg(ERR_ZONE, "%s: Failed to read frame: %d\n", __func__,
			status);
	वापस status;
पूर्ण

/**
 * rsi_init_sdio_पूर्णांकerface() - This function करोes init specअगरic to SDIO.
 *
 * @adapter: Poपूर्णांकer to the adapter data काष्ठाure.
 * @pfunction: Poपूर्णांकer to the sdio_func काष्ठाure.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_init_sdio_पूर्णांकerface(काष्ठा rsi_hw *adapter,
				   काष्ठा sdio_func *pfunction)
अणु
	काष्ठा rsi_91x_sdiodev *rsi_91x_dev;
	पूर्णांक status;

	rsi_91x_dev = kzalloc(माप(*rsi_91x_dev), GFP_KERNEL);
	अगर (!rsi_91x_dev)
		वापस -ENOMEM;

	adapter->rsi_dev = rsi_91x_dev;

	sdio_claim_host(pfunction);

	pfunction->enable_समयout = 100;
	status = sdio_enable_func(pfunction);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to enable interface\n", __func__);
		sdio_release_host(pfunction);
		वापस status;
	पूर्ण

	rsi_dbg(INIT_ZONE, "%s: Enabled the interface\n", __func__);

	rsi_91x_dev->pfunction = pfunction;
	adapter->device = &pfunction->dev;

	sdio_set_drvdata(pfunction, adapter);

	status = rsi_setupcard(adapter);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to setup card\n", __func__);
		जाओ fail;
	पूर्ण

	rsi_dbg(INIT_ZONE, "%s: Setup card successfully\n", __func__);

	status = rsi_init_sdio_slave_regs(adapter);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to init slave regs\n", __func__);
		जाओ fail;
	पूर्ण
	sdio_release_host(pfunction);

	adapter->determine_event_समयout = rsi_sdio_determine_event_समयout;
	adapter->check_hw_queue_status = rsi_sdio_check_buffer_status;

#अगर_घोषित CONFIG_RSI_DEBUGFS
	adapter->num_debugfs_entries = MAX_DEBUGFS_ENTRIES;
#पूर्ण_अगर
	वापस 0;
fail:
	sdio_disable_func(pfunction);
	sdio_release_host(pfunction);
	वापस status;
पूर्ण

अटल पूर्णांक rsi_sdio_reinit_device(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_sdiodev *sdev = adapter->rsi_dev;
	काष्ठा sdio_func *pfunction = sdev->pfunction;
	पूर्णांक ii;

	क्रम (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_purge(&adapter->priv->tx_queue[ii]);

	/* Initialize device again */
	sdio_claim_host(pfunction);

	sdio_release_irq(pfunction);
	rsi_reset_card(pfunction);

	sdio_enable_func(pfunction);
	rsi_setupcard(adapter);
	rsi_init_sdio_slave_regs(adapter);
	sdio_claim_irq(pfunction, rsi_handle_पूर्णांकerrupt);
	rsi_hal_device_init(adapter);

	sdio_release_host(pfunction);

	वापस 0;
पूर्ण

अटल पूर्णांक rsi_sdio_ta_reset(काष्ठा rsi_hw *adapter)
अणु
	पूर्णांक status;
	u32 addr;
	u8 *data;

	data = kzalloc(RSI_9116_REG_SIZE, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	status = rsi_sdio_master_access_msword(adapter, TA_BASE_ADDR);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"Unable to set ms word to common reg\n");
		जाओ err;
	पूर्ण

	rsi_dbg(INIT_ZONE, "%s: Bring TA out of reset\n", __func__);
	put_unaligned_le32(TA_HOLD_THREAD_VALUE, data);
	addr = TA_HOLD_THREAD_REG | RSI_SD_REQUEST_MASTER;
	status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple(adapter, addr,
						  (u8 *)data,
						  RSI_9116_REG_SIZE);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "Unable to hold TA threads\n");
		जाओ err;
	पूर्ण

	put_unaligned_le32(TA_SOFT_RST_CLR, data);
	addr = TA_SOFT_RESET_REG | RSI_SD_REQUEST_MASTER;
	status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple(adapter, addr,
						  (u8 *)data,
						  RSI_9116_REG_SIZE);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "Unable to get TA out of reset\n");
		जाओ err;
	पूर्ण

	put_unaligned_le32(TA_PC_ZERO, data);
	addr = TA_TH0_PC_REG | RSI_SD_REQUEST_MASTER;
	status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple(adapter, addr,
						  (u8 *)data,
						  RSI_9116_REG_SIZE);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "Unable to Reset TA PC value\n");
		status = -EINVAL;
		जाओ err;
	पूर्ण

	put_unaligned_le32(TA_RELEASE_THREAD_VALUE, data);
	addr = TA_RELEASE_THREAD_REG | RSI_SD_REQUEST_MASTER;
	status = rsi_sdio_ग_लिखो_रेजिस्टर_multiple(adapter, addr,
						  (u8 *)data,
						  RSI_9116_REG_SIZE);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "Unable to release TA threads\n");
		जाओ err;
	पूर्ण

	status = rsi_sdio_master_access_msword(adapter, MISC_CFG_BASE_ADDR);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "Unable to set ms word to common reg\n");
		जाओ err;
	पूर्ण
	rsi_dbg(INIT_ZONE, "***** TA Reset done *****\n");

err:
	kमुक्त(data);
	वापस status;
पूर्ण

अटल काष्ठा rsi_host_पूर्णांकf_ops sdio_host_पूर्णांकf_ops = अणु
	.ग_लिखो_pkt		= rsi_sdio_host_पूर्णांकf_ग_लिखो_pkt,
	.पढ़ो_pkt		= rsi_sdio_host_पूर्णांकf_पढ़ो_pkt,
	.master_access_msword	= rsi_sdio_master_access_msword,
	.पढ़ो_reg_multiple	= rsi_sdio_पढ़ो_रेजिस्टर_multiple,
	.ग_लिखो_reg_multiple	= rsi_sdio_ग_लिखो_रेजिस्टर_multiple,
	.master_reg_पढ़ो	= rsi_sdio_master_reg_पढ़ो,
	.master_reg_ग_लिखो	= rsi_sdio_master_reg_ग_लिखो,
	.load_data_master_ग_लिखो	= rsi_sdio_load_data_master_ग_लिखो,
	.reinit_device          = rsi_sdio_reinit_device,
	.ta_reset		= rsi_sdio_ta_reset,
पूर्ण;

/**
 * rsi_probe() - This function is called by kernel when the driver provided
 *		 Venकरोr and device IDs are matched. All the initialization
 *		 work is करोne here.
 * @pfunction: Poपूर्णांकer to the sdio_func काष्ठाure.
 * @id: Poपूर्णांकer to sdio_device_id काष्ठाure.
 *
 * Return: 0 on success, 1 on failure.
 */
अटल पूर्णांक rsi_probe(काष्ठा sdio_func *pfunction,
		     स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा rsi_hw *adapter;
	काष्ठा rsi_91x_sdiodev *sdev;
	पूर्णांक status = -EINVAL;

	rsi_dbg(INIT_ZONE, "%s: Init function called\n", __func__);

	adapter = rsi_91x_init(dev_oper_mode);
	अगर (!adapter) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to init os intf ops\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	adapter->rsi_host_पूर्णांकf = RSI_HOST_INTF_SDIO;
	adapter->host_पूर्णांकf_ops = &sdio_host_पूर्णांकf_ops;

	अगर (rsi_init_sdio_पूर्णांकerface(adapter, pfunction)) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to init sdio interface\n",
			__func__);
		status = -EIO;
		जाओ fail_मुक्त_adapter;
	पूर्ण

	अगर (pfunction->device == SDIO_DEVICE_ID_RSI_9113) अणु
		rsi_dbg(ERR_ZONE, "%s: 9113 module detected\n", __func__);
		adapter->device_model = RSI_DEV_9113;
	पूर्ण अन्यथा  अगर (pfunction->device == SDIO_DEVICE_ID_RSI_9116) अणु
		rsi_dbg(ERR_ZONE, "%s: 9116 module detected\n", __func__);
		adapter->device_model = RSI_DEV_9116;
	पूर्ण अन्यथा अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unsupported RSI device id 0x%x\n", __func__,
			pfunction->device);
		जाओ fail_मुक्त_adapter;
	पूर्ण

	sdev = (काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	rsi_init_event(&sdev->rx_thपढ़ो.event);
	status = rsi_create_kthपढ़ो(adapter->priv, &sdev->rx_thपढ़ो,
				    rsi_sdio_rx_thपढ़ो, "SDIO-RX-Thread");
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to init rx thrd\n", __func__);
		जाओ fail_समाप्त_thपढ़ो;
	पूर्ण

	sdio_claim_host(pfunction);
	अगर (sdio_claim_irq(pfunction, rsi_handle_पूर्णांकerrupt)) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to request IRQ\n", __func__);
		sdio_release_host(pfunction);
		status = -EIO;
		जाओ fail_claim_irq;
	पूर्ण
	sdio_release_host(pfunction);
	rsi_dbg(INIT_ZONE, "%s: Registered Interrupt handler\n", __func__);

	अगर (rsi_hal_device_init(adapter)) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in device init\n", __func__);
		status = -EINVAL;
		जाओ fail_dev_init;
	पूर्ण
	rsi_dbg(INFO_ZONE, "===> RSI Device Init Done <===\n");

	अगर (rsi_sdio_master_access_msword(adapter, MISC_CFG_BASE_ADDR)) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to set ms word reg\n", __func__);
		status = -EIO;
		जाओ fail_dev_init;
	पूर्ण

	adapter->priv->hibernate_resume = false;
	adapter->priv->reinit_hw = false;
	वापस 0;

fail_dev_init:
	sdio_claim_host(pfunction);
	sdio_release_irq(pfunction);
	sdio_release_host(pfunction);
fail_claim_irq:
	rsi_समाप्त_thपढ़ो(&sdev->rx_thपढ़ो);
fail_समाप्त_thपढ़ो:
	sdio_claim_host(pfunction);
	sdio_disable_func(pfunction);
	sdio_release_host(pfunction);
fail_मुक्त_adapter:
	rsi_91x_deinit(adapter);
	rsi_dbg(ERR_ZONE, "%s: Failed in probe...Exiting\n", __func__);
	वापस status;
पूर्ण

अटल व्योम ulp_पढ़ो_ग_लिखो(काष्ठा rsi_hw *adapter, u16 addr, u32 data,
			   u16 len_in_bits)
अणु
	rsi_sdio_master_reg_ग_लिखो(adapter, RSI_GSPI_DATA_REG1,
				  ((addr << 6) | ((data >> 16) & 0xffff)), 2);
	rsi_sdio_master_reg_ग_लिखो(adapter, RSI_GSPI_DATA_REG0,
				  (data & 0xffff), 2);
	rsi_sdio_master_reg_ग_लिखो(adapter, RSI_GSPI_CTRL_REG0,
				  RSI_GSPI_CTRL_REG0_VALUE, 2);
	rsi_sdio_master_reg_ग_लिखो(adapter, RSI_GSPI_CTRL_REG1,
				  ((len_in_bits - 1) | RSI_GSPI_TRIG), 2);
	msleep(20);
पूर्ण

/*This function resets and re-initializes the chip.*/
अटल व्योम rsi_reset_chip(काष्ठा rsi_hw *adapter)
अणु
	u8 *data;
	u8 sdio_पूर्णांकerrupt_status = 0;
	u8 request = 1;
	पूर्णांक ret;

	data = kzalloc(माप(u32), GFP_KERNEL);
	अगर (!data)
		वापस;

	rsi_dbg(INFO_ZONE, "Writing disable to wakeup register\n");
	ret =  rsi_sdio_ग_लिखो_रेजिस्टर(adapter, 0, SDIO_WAKEUP_REG, &request);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to write SDIO wakeup register\n", __func__);
		जाओ err;
	पूर्ण
	msleep(20);
	ret =  rsi_sdio_पढ़ो_रेजिस्टर(adapter, RSI_FN1_INT_REGISTER,
				      &sdio_पूर्णांकerrupt_status);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to Read Intr Status Register\n",
			__func__);
		जाओ err;
	पूर्ण
	rsi_dbg(INFO_ZONE, "%s: Intr Status Register value = %d\n",
		__func__, sdio_पूर्णांकerrupt_status);

	/* Put Thपढ़ो-Arch processor on hold */
	अगर (rsi_sdio_master_access_msword(adapter, TA_BASE_ADDR)) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unable to set ms word to common reg\n",
			__func__);
		जाओ err;
	पूर्ण

	put_unaligned_le32(TA_HOLD_THREAD_VALUE, data);
	अगर (rsi_sdio_ग_लिखो_रेजिस्टर_multiple(adapter, TA_HOLD_THREAD_REG |
					     RSI_SD_REQUEST_MASTER,
					     data, 4)) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unable to hold Thread-Arch processor threads\n",
			__func__);
		जाओ err;
	पूर्ण

	/* This msleep will ensure Thपढ़ो-Arch processor to go to hold
	 * and any pending dma transfers to rf spi in device to finish.
	 */
	msleep(100);
	अगर (adapter->device_model != RSI_DEV_9116) अणु
		ulp_पढ़ो_ग_लिखो(adapter, RSI_ULP_RESET_REG, RSI_ULP_WRITE_0, 32);
		ulp_पढ़ो_ग_लिखो(adapter,
			       RSI_WATCH_DOG_TIMER_1, RSI_ULP_WRITE_2, 32);
		ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_TIMER_2, RSI_ULP_WRITE_0,
			       32);
		ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_DELAY_TIMER_1,
			       RSI_ULP_WRITE_50, 32);
		ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_DELAY_TIMER_2,
			       RSI_ULP_WRITE_0, 32);
		ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_TIMER_ENABLE,
			       RSI_ULP_TIMER_ENABLE, 32);
	पूर्ण अन्यथा अणु
		अगर ((rsi_sdio_master_reg_ग_लिखो(adapter,
					       NWP_WWD_INTERRUPT_TIMER,
					       NWP_WWD_INT_TIMER_CLKS,
					       RSI_9116_REG_SIZE)) < 0) अणु
			rsi_dbg(ERR_ZONE, "Failed to write to intr timer\n");
		पूर्ण
		अगर ((rsi_sdio_master_reg_ग_लिखो(adapter,
					       NWP_WWD_SYSTEM_RESET_TIMER,
					       NWP_WWD_SYS_RESET_TIMER_CLKS,
					       RSI_9116_REG_SIZE)) < 0) अणु
			rsi_dbg(ERR_ZONE,
				"Failed to write to system reset timer\n");
		पूर्ण
		अगर ((rsi_sdio_master_reg_ग_लिखो(adapter,
					       NWP_WWD_MODE_AND_RSTART,
					       NWP_WWD_TIMER_DISABLE,
					       RSI_9116_REG_SIZE)) < 0) अणु
			rsi_dbg(ERR_ZONE,
				"Failed to write to mode and restart\n");
		पूर्ण
		rsi_dbg(ERR_ZONE, "***** Watch Dog Reset Successful *****\n");
	पूर्ण
	/* This msleep will be sufficient क्रम the ulp
	 * पढ़ो ग_लिखो operations to complete क्रम chip reset.
	 */
	msleep(500);
err:
	kमुक्त(data);
	वापस;
पूर्ण

/**
 * rsi_disconnect() - This function perक्रमms the reverse of the probe function.
 * @pfunction: Poपूर्णांकer to the sdio_func काष्ठाure.
 *
 * Return: व्योम.
 */
अटल व्योम rsi_disconnect(काष्ठा sdio_func *pfunction)
अणु
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_91x_sdiodev *dev;

	अगर (!adapter)
		वापस;

	dev = (काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;

	rsi_समाप्त_thपढ़ो(&dev->rx_thपढ़ो);
	sdio_claim_host(pfunction);
	sdio_release_irq(pfunction);
	sdio_release_host(pfunction);
	mdelay(10);

	rsi_mac80211_detach(adapter);
	mdelay(10);

	अगर (IS_ENABLED(CONFIG_RSI_COEX) && adapter->priv->coex_mode > 1 &&
	    adapter->priv->bt_adapter) अणु
		rsi_bt_ops.detach(adapter->priv->bt_adapter);
		adapter->priv->bt_adapter = शून्य;
	पूर्ण

	/* Reset Chip */
	rsi_reset_chip(adapter);

	/* Resetting to take care of the हाल, where-in driver is re-loaded */
	sdio_claim_host(pfunction);
	rsi_reset_card(pfunction);
	sdio_disable_func(pfunction);
	sdio_release_host(pfunction);
	dev->ग_लिखो_fail = 2;
	rsi_91x_deinit(adapter);
	rsi_dbg(ERR_ZONE, "##### RSI SDIO device disconnected #####\n");

पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rsi_set_sdio_pm_caps(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	काष्ठा sdio_func *func = dev->pfunction;
	पूर्णांक ret;

	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	अगर (ret)
		rsi_dbg(ERR_ZONE, "Set sdio keep pwr flag failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rsi_sdio_disable_पूर्णांकerrupts(काष्ठा sdio_func *pfunc)
अणु
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunc);
	u8 isr_status = 0, data = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ t1;

	rsi_dbg(INFO_ZONE, "Waiting for interrupts to be cleared..");
	t1 = jअगरfies;
	करो अणु
		rsi_sdio_पढ़ो_रेजिस्टर(adapter, RSI_FN1_INT_REGISTER,
				       &isr_status);
		rsi_dbg(INFO_ZONE, ".");
	पूर्ण जबतक ((isr_status) && (jअगरfies_to_msecs(jअगरfies - t1) < 20));
	rsi_dbg(INFO_ZONE, "Interrupts cleared\n");

	sdio_claim_host(pfunc);
	ret = rsi_cmd52पढ़ोbyte(pfunc->card, RSI_INT_ENABLE_REGISTER, &data);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to read int enable register\n",
			__func__);
		जाओ करोne;
	पूर्ण

	data &= RSI_INT_ENABLE_MASK;
	ret = rsi_cmd52ग_लिखोbyte(pfunc->card, RSI_INT_ENABLE_REGISTER, data);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to write to int enable register\n",
			__func__);
		जाओ करोne;
	पूर्ण
	ret = rsi_cmd52पढ़ोbyte(pfunc->card, RSI_INT_ENABLE_REGISTER, &data);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to read int enable register\n",
			__func__);
		जाओ करोne;
	पूर्ण
	rsi_dbg(INFO_ZONE, "int enable reg content = %x\n", data);

करोne:
	sdio_release_host(pfunc);
	वापस ret;
पूर्ण

अटल पूर्णांक rsi_sdio_enable_पूर्णांकerrupts(काष्ठा sdio_func *pfunc)
अणु
	u8 data;
	पूर्णांक ret;
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunc);
	काष्ठा rsi_common *common = adapter->priv;

	sdio_claim_host(pfunc);
	ret = rsi_cmd52पढ़ोbyte(pfunc->card, RSI_INT_ENABLE_REGISTER, &data);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to read int enable register\n", __func__);
		जाओ करोne;
	पूर्ण

	data |= ~RSI_INT_ENABLE_MASK & 0xff;

	ret = rsi_cmd52ग_लिखोbyte(pfunc->card, RSI_INT_ENABLE_REGISTER, data);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to write to int enable register\n",
			__func__);
		जाओ करोne;
	पूर्ण

	अगर ((common->wow_flags & RSI_WOW_ENABLED) &&
	    (common->wow_flags & RSI_WOW_NO_CONNECTION))
		rsi_dbg(ERR_ZONE,
			"##### Device can not wake up through WLAN\n");

	ret = rsi_cmd52पढ़ोbyte(pfunc->card, RSI_INT_ENABLE_REGISTER, &data);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to read int enable register\n", __func__);
		जाओ करोne;
	पूर्ण
	rsi_dbg(INFO_ZONE, "int enable reg content = %x\n", data);

करोne:
	sdio_release_host(pfunc);
	वापस ret;
पूर्ण

अटल पूर्णांक rsi_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *pfunction = dev_to_sdio_func(dev);
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_common *common;

	अगर (!adapter) अणु
		rsi_dbg(ERR_ZONE, "Device is not ready\n");
		वापस -ENODEV;
	पूर्ण
	common = adapter->priv;
	rsi_sdio_disable_पूर्णांकerrupts(pfunction);

	ret = rsi_set_sdio_pm_caps(adapter);
	अगर (ret)
		rsi_dbg(INFO_ZONE,
			"Setting power management caps failed\n");
	common->fsm_state = FSM_CARD_NOT_READY;

	वापस 0;
पूर्ण

अटल पूर्णांक rsi_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *pfunction = dev_to_sdio_func(dev);
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_common *common = adapter->priv;

	common->fsm_state = FSM_MAC_INIT_DONE;
	rsi_sdio_enable_पूर्णांकerrupts(pfunction);

	वापस 0;
पूर्ण

अटल पूर्णांक rsi_मुक्तze(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *pfunction = dev_to_sdio_func(dev);
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_common *common;
	काष्ठा rsi_91x_sdiodev *sdev;

	rsi_dbg(INFO_ZONE, "SDIO Bus freeze ===>\n");

	अगर (!adapter) अणु
		rsi_dbg(ERR_ZONE, "Device is not ready\n");
		वापस -ENODEV;
	पूर्ण
	common = adapter->priv;
	sdev = (काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;

	अगर ((common->wow_flags & RSI_WOW_ENABLED) &&
	    (common->wow_flags & RSI_WOW_NO_CONNECTION))
		rsi_dbg(ERR_ZONE,
			"##### Device can not wake up through WLAN\n");

	अगर (IS_ENABLED(CONFIG_RSI_COEX) && common->coex_mode > 1 &&
	    common->bt_adapter) अणु
		rsi_bt_ops.detach(common->bt_adapter);
		common->bt_adapter = शून्य;
	पूर्ण

	ret = rsi_sdio_disable_पूर्णांकerrupts(pfunction);

	अगर (sdev->ग_लिखो_fail)
		rsi_dbg(INFO_ZONE, "###### Device is not ready #######\n");

	ret = rsi_set_sdio_pm_caps(adapter);
	अगर (ret)
		rsi_dbg(INFO_ZONE, "Setting power management caps failed\n");

	rsi_dbg(INFO_ZONE, "***** RSI module freezed *****\n");

	वापस 0;
पूर्ण

अटल पूर्णांक rsi_thaw(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *pfunction = dev_to_sdio_func(dev);
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_common *common = adapter->priv;

	rsi_dbg(ERR_ZONE, "SDIO Bus thaw =====>\n");

	common->hibernate_resume = true;
	common->fsm_state = FSM_CARD_NOT_READY;
	common->अगरace_करोwn = true;

	rsi_sdio_enable_पूर्णांकerrupts(pfunction);

	rsi_dbg(INFO_ZONE, "***** RSI module thaw done *****\n");

	वापस 0;
पूर्ण

अटल व्योम rsi_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *pfunction = dev_to_sdio_func(dev);
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_91x_sdiodev *sdev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	काष्ठा ieee80211_hw *hw = adapter->hw;

	rsi_dbg(ERR_ZONE, "SDIO Bus shutdown =====>\n");

	अगर (hw) अणु
		काष्ठा cfg80211_wowlan *wowlan = hw->wiphy->wowlan_config;

		अगर (rsi_config_wowlan(adapter, wowlan))
			rsi_dbg(ERR_ZONE, "Failed to configure WoWLAN\n");
	पूर्ण

	अगर (IS_ENABLED(CONFIG_RSI_COEX) && adapter->priv->coex_mode > 1 &&
	    adapter->priv->bt_adapter) अणु
		rsi_bt_ops.detach(adapter->priv->bt_adapter);
		adapter->priv->bt_adapter = शून्य;
	पूर्ण

	rsi_sdio_disable_पूर्णांकerrupts(sdev->pfunction);

	अगर (sdev->ग_लिखो_fail)
		rsi_dbg(INFO_ZONE, "###### Device is not ready #######\n");

	अगर (rsi_set_sdio_pm_caps(adapter))
		rsi_dbg(INFO_ZONE, "Setting power management caps failed\n");

	rsi_dbg(INFO_ZONE, "***** RSI module shut down *****\n");
पूर्ण

अटल पूर्णांक rsi_restore(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *pfunction = dev_to_sdio_func(dev);
	काष्ठा rsi_hw *adapter = sdio_get_drvdata(pfunction);
	काष्ठा rsi_common *common = adapter->priv;

	rsi_dbg(INFO_ZONE, "SDIO Bus restore ======>\n");
	common->hibernate_resume = true;
	common->fsm_state = FSM_FW_NOT_LOADED;
	common->अगरace_करोwn = true;

	adapter->sc_nvअगरs = 0;
	adapter->ps_state = PS_NONE;

	common->wow_flags = 0;
	common->अगरace_करोwn = false;

	rsi_dbg(INFO_ZONE, "RSI module restored\n");

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा dev_pm_ops rsi_pm_ops = अणु
	.suspend = rsi_suspend,
	.resume_noirq = rsi_resume,
	.मुक्तze = rsi_मुक्तze,
	.thaw = rsi_thaw,
	.restore = rsi_restore,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा sdio_device_id rsi_dev_table[] =  अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_RSI, SDIO_DEVICE_ID_RSI_9113) पूर्ण,
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_RSI, SDIO_DEVICE_ID_RSI_9116) पूर्ण,
	अणु /* Blank */पूर्ण,
पूर्ण;

अटल काष्ठा sdio_driver rsi_driver = अणु
	.name       = "RSI-SDIO WLAN",
	.probe      = rsi_probe,
	.हटाओ     = rsi_disconnect,
	.id_table   = rsi_dev_table,
#अगर_घोषित CONFIG_PM
	.drv = अणु
		.pm = &rsi_pm_ops,
		.shutकरोwn   = rsi_shutकरोwn,
	पूर्ण
#पूर्ण_अगर
पूर्ण;

/**
 * rsi_module_init() - This function रेजिस्टरs the sdio module.
 * @व्योम: Void.
 *
 * Return: 0 on success.
 */
अटल पूर्णांक rsi_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = sdio_रेजिस्टर_driver(&rsi_driver);
	rsi_dbg(INIT_ZONE, "%s: Registering driver\n", __func__);
	वापस ret;
पूर्ण

/**
 * rsi_module_निकास() - This function unरेजिस्टरs the sdio module.
 * @व्योम: Void.
 *
 * Return: None.
 */
अटल व्योम rsi_module_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&rsi_driver);
	rsi_dbg(INFO_ZONE, "%s: Unregistering driver\n", __func__);
पूर्ण

module_init(rsi_module_init);
module_निकास(rsi_module_निकास);

MODULE_AUTHOR("Redpine Signals Inc");
MODULE_DESCRIPTION("Common SDIO layer for RSI drivers");
MODULE_DEVICE_TABLE(sdio, rsi_dev_table);
MODULE_FIRMWARE(FIRMWARE_RSI9113);
MODULE_VERSION("0.1");
MODULE_LICENSE("Dual BSD/GPL");
