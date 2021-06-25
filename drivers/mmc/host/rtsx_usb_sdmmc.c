<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Realtek USB SD/MMC Card Interface driver
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Roger Tseng <rogerable@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/rtsx_usb.h>
#समावेश <यंत्र/unaligned.h>

#अगर defined(CONFIG_LEDS_CLASS) || (defined(CONFIG_LEDS_CLASS_MODULE) && \
		defined(CONFIG_MMC_REALTEK_USB_MODULE))
#समावेश <linux/leds.h>
#समावेश <linux/workqueue.h>
#घोषणा RTSX_USB_USE_LEDS_CLASS
#पूर्ण_अगर

काष्ठा rtsx_usb_sdmmc अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा rtsx_ucr	*ucr;
	काष्ठा mmc_host		*mmc;
	काष्ठा mmc_request	*mrq;

	काष्ठा mutex		host_mutex;

	u8			ssc_depth;
	अचिन्हित पूर्णांक		घड़ी;
	bool			vpclk;
	bool			द्विगुन_clk;
	bool			host_removal;
	bool			card_exist;
	bool			initial_mode;
	bool			ddr_mode;

	अचिन्हित अक्षर		घातer_mode;

#अगर_घोषित RTSX_USB_USE_LEDS_CLASS
	काष्ठा led_classdev	led;
	अक्षर			led_name[32];
	काष्ठा work_काष्ठा	led_work;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा device *sdmmc_dev(काष्ठा rtsx_usb_sdmmc *host)
अणु
	वापस &(host->pdev->dev);
पूर्ण

अटल अंतरभूत व्योम sd_clear_error(काष्ठा rtsx_usb_sdmmc *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, CARD_STOP,
				  SD_STOP | SD_CLR_ERR,
				  SD_STOP | SD_CLR_ERR);

	rtsx_usb_clear_dma_err(ucr);
	rtsx_usb_clear_fsm_err(ucr);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम sd_prपूर्णांक_debug_regs(काष्ठा rtsx_usb_sdmmc *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	u8 val = 0;

	rtsx_usb_ep0_पढ़ो_रेजिस्टर(ucr, SD_STAT1, &val);
	dev_dbg(sdmmc_dev(host), "SD_STAT1: 0x%x\n", val);
	rtsx_usb_ep0_पढ़ो_रेजिस्टर(ucr, SD_STAT2, &val);
	dev_dbg(sdmmc_dev(host), "SD_STAT2: 0x%x\n", val);
	rtsx_usb_ep0_पढ़ो_रेजिस्टर(ucr, SD_BUS_STAT, &val);
	dev_dbg(sdmmc_dev(host), "SD_BUS_STAT: 0x%x\n", val);
पूर्ण
#अन्यथा
#घोषणा sd_prपूर्णांक_debug_regs(host)
#पूर्ण_अगर /* DEBUG */

अटल पूर्णांक sd_पढ़ो_data(काष्ठा rtsx_usb_sdmmc *host, काष्ठा mmc_command *cmd,
	       u16 byte_cnt, u8 *buf, पूर्णांक buf_len, पूर्णांक समयout)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	u8 trans_mode;

	अगर (!buf)
		buf_len = 0;

	rtsx_usb_init_cmd(ucr);
	अगर (cmd != शून्य) अणु
		dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD%d\n", __func__
				, cmd->opcode);
		अगर (cmd->opcode == MMC_SEND_TUNING_BLOCK)
			trans_mode = SD_TM_AUTO_TUNING;
		अन्यथा
			trans_mode = SD_TM_NORMAL_READ;

		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD0, 0xFF, (u8)(cmd->opcode) | 0x40);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD1, 0xFF, (u8)(cmd->arg >> 24));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD2, 0xFF, (u8)(cmd->arg >> 16));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD3, 0xFF, (u8)(cmd->arg >> 8));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD4, 0xFF, (u8)cmd->arg);
	पूर्ण अन्यथा अणु
		trans_mode = SD_TM_AUTO_READ_3;
	पूर्ण

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BYTE_CNT_L, 0xFF, (u8)byte_cnt);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BYTE_CNT_H,
			0xFF, (u8)(byte_cnt >> 8));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BLOCK_CNT_L, 0xFF, 1);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BLOCK_CNT_H, 0xFF, 0);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG2, 0xFF,
			SD_CALCULATE_CRC7 | SD_CHECK_CRC16 |
			SD_NO_WAIT_BUSY_END | SD_CHECK_CRC7 | SD_RSP_LEN_6);
	अगर (trans_mode != SD_TM_AUTO_TUNING)
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				CARD_DATA_SOURCE, 0x01, PINGPONG_BUFFER);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_TRANSFER,
			0xFF, trans_mode | SD_TRANSFER_START);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);

	अगर (cmd != शून्य) अणु
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD1, 0, 0);
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD2, 0, 0);
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD3, 0, 0);
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD4, 0, 0);
	पूर्ण

	err = rtsx_usb_send_cmd(ucr, MODE_CR, समयout);
	अगर (err) अणु
		dev_dbg(sdmmc_dev(host),
			"rtsx_usb_send_cmd failed (err = %d)\n", err);
		वापस err;
	पूर्ण

	err = rtsx_usb_get_rsp(ucr, !cmd ? 1 : 5, समयout);
	अगर (err || (ucr->rsp_buf[0] & SD_TRANSFER_ERR)) अणु
		sd_prपूर्णांक_debug_regs(host);

		अगर (!err) अणु
			dev_dbg(sdmmc_dev(host),
				"Transfer failed (SD_TRANSFER = %02x)\n",
				ucr->rsp_buf[0]);
			err = -EIO;
		पूर्ण अन्यथा अणु
			dev_dbg(sdmmc_dev(host),
				"rtsx_usb_get_rsp failed (err = %d)\n", err);
		पूर्ण

		वापस err;
	पूर्ण

	अगर (cmd != शून्य) अणु
		cmd->resp[0] = get_unaligned_be32(ucr->rsp_buf + 1);
		dev_dbg(sdmmc_dev(host), "cmd->resp[0] = 0x%08x\n",
				cmd->resp[0]);
	पूर्ण

	अगर (buf && buf_len) अणु
		/* 2-byte aligned part */
		err = rtsx_usb_पढ़ो_ppbuf(ucr, buf, byte_cnt - (byte_cnt % 2));
		अगर (err) अणु
			dev_dbg(sdmmc_dev(host),
				"rtsx_usb_read_ppbuf failed (err = %d)\n", err);
			वापस err;
		पूर्ण

		/* unaligned byte */
		अगर (byte_cnt % 2)
			वापस rtsx_usb_पढ़ो_रेजिस्टर(ucr,
					PPBUF_BASE2 + byte_cnt,
					buf + byte_cnt - 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sd_ग_लिखो_data(काष्ठा rtsx_usb_sdmmc *host, काष्ठा mmc_command *cmd,
		u16 byte_cnt, u8 *buf, पूर्णांक buf_len, पूर्णांक समयout)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	u8 trans_mode;

	अगर (!buf)
		buf_len = 0;

	अगर (buf && buf_len) अणु
		err = rtsx_usb_ग_लिखो_ppbuf(ucr, buf, buf_len);
		अगर (err) अणु
			dev_dbg(sdmmc_dev(host),
				"rtsx_usb_write_ppbuf failed (err = %d)\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	trans_mode = (cmd != शून्य) ? SD_TM_AUTO_WRITE_2 : SD_TM_AUTO_WRITE_3;
	rtsx_usb_init_cmd(ucr);

	अगर (cmd != शून्य) अणु
		dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD%d\n", __func__,
				cmd->opcode);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD0, 0xFF, (u8)(cmd->opcode) | 0x40);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD1, 0xFF, (u8)(cmd->arg >> 24));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD2, 0xFF, (u8)(cmd->arg >> 16));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD3, 0xFF, (u8)(cmd->arg >> 8));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CMD4, 0xFF, (u8)cmd->arg);
	पूर्ण

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BYTE_CNT_L, 0xFF, (u8)byte_cnt);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BYTE_CNT_H,
			0xFF, (u8)(byte_cnt >> 8));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BLOCK_CNT_L, 0xFF, 1);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BLOCK_CNT_H, 0xFF, 0);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG2, 0xFF,
		SD_CALCULATE_CRC7 | SD_CHECK_CRC16 |
		SD_NO_WAIT_BUSY_END | SD_CHECK_CRC7 | SD_RSP_LEN_6);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
			CARD_DATA_SOURCE, 0x01, PINGPONG_BUFFER);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_TRANSFER, 0xFF,
			trans_mode | SD_TRANSFER_START);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);

	अगर (cmd != शून्य) अणु
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD1, 0, 0);
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD2, 0, 0);
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD3, 0, 0);
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_CMD4, 0, 0);
	पूर्ण

	err = rtsx_usb_send_cmd(ucr, MODE_CR, समयout);
	अगर (err) अणु
		dev_dbg(sdmmc_dev(host),
			"rtsx_usb_send_cmd failed (err = %d)\n", err);
		वापस err;
	पूर्ण

	err = rtsx_usb_get_rsp(ucr, !cmd ? 1 : 5, समयout);
	अगर (err) अणु
		sd_prपूर्णांक_debug_regs(host);
		dev_dbg(sdmmc_dev(host),
			"rtsx_usb_get_rsp failed (err = %d)\n", err);
		वापस err;
	पूर्ण

	अगर (cmd != शून्य) अणु
		cmd->resp[0] = get_unaligned_be32(ucr->rsp_buf + 1);
		dev_dbg(sdmmc_dev(host), "cmd->resp[0] = 0x%08x\n",
				cmd->resp[0]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sd_send_cmd_get_rsp(काष्ठा rtsx_usb_sdmmc *host,
		काष्ठा mmc_command *cmd)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	u8 cmd_idx = (u8)cmd->opcode;
	u32 arg = cmd->arg;
	पूर्णांक err = 0;
	पूर्णांक समयout = 100;
	पूर्णांक i;
	u8 *ptr;
	पूर्णांक stat_idx = 0;
	पूर्णांक len = 2;
	u8 rsp_type;

	dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD %d, arg = 0x%08x\n",
			__func__, cmd_idx, arg);

	/* Response type:
	 * R0
	 * R1, R5, R6, R7
	 * R1b
	 * R2
	 * R3, R4
	 */
	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		rsp_type = SD_RSP_TYPE_R0;
		अवरोध;
	हाल MMC_RSP_R1:
		rsp_type = SD_RSP_TYPE_R1;
		अवरोध;
	हाल MMC_RSP_R1_NO_CRC:
		rsp_type = SD_RSP_TYPE_R1 | SD_NO_CHECK_CRC7;
		अवरोध;
	हाल MMC_RSP_R1B:
		rsp_type = SD_RSP_TYPE_R1b;
		अवरोध;
	हाल MMC_RSP_R2:
		rsp_type = SD_RSP_TYPE_R2;
		अवरोध;
	हाल MMC_RSP_R3:
		rsp_type = SD_RSP_TYPE_R3;
		अवरोध;
	शेष:
		dev_dbg(sdmmc_dev(host), "cmd->flag is not valid\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (rsp_type == SD_RSP_TYPE_R1b)
		समयout = cmd->busy_समयout ? cmd->busy_समयout : 3000;

	अगर (cmd->opcode == SD_SWITCH_VOLTAGE) अणु
		err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, SD_BUS_STAT,
				SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP,
				SD_CLK_TOGGLE_EN);
		अगर (err)
			जाओ out;
	पूर्ण

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CMD0, 0xFF, 0x40 | cmd_idx);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CMD1, 0xFF, (u8)(arg >> 24));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CMD2, 0xFF, (u8)(arg >> 16));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CMD3, 0xFF, (u8)(arg >> 8));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CMD4, 0xFF, (u8)arg);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG2, 0xFF, rsp_type);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, PINGPONG_BUFFER);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_TRANSFER,
			0xFF, SD_TM_CMD_RSP | SD_TRANSFER_START);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, SD_TRANSFER,
		     SD_TRANSFER_END | SD_STAT_IDLE,
		     SD_TRANSFER_END | SD_STAT_IDLE);

	अगर (rsp_type == SD_RSP_TYPE_R2) अणु
		/* Read data from ping-pong buffer */
		क्रम (i = PPBUF_BASE2; i < PPBUF_BASE2 + 16; i++)
			rtsx_usb_add_cmd(ucr, READ_REG_CMD, (u16)i, 0, 0);
		stat_idx = 16;
	पूर्ण अन्यथा अगर (rsp_type != SD_RSP_TYPE_R0) अणु
		/* Read data from SD_CMDx रेजिस्टरs */
		क्रम (i = SD_CMD0; i <= SD_CMD4; i++)
			rtsx_usb_add_cmd(ucr, READ_REG_CMD, (u16)i, 0, 0);
		stat_idx = 5;
	पूर्ण
	len += stat_idx;

	rtsx_usb_add_cmd(ucr, READ_REG_CMD, SD_STAT1, 0, 0);

	err = rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	अगर (err) अणु
		dev_dbg(sdmmc_dev(host),
			"rtsx_usb_send_cmd error (err = %d)\n", err);
		जाओ out;
	पूर्ण

	err = rtsx_usb_get_rsp(ucr, len, समयout);
	अगर (err || (ucr->rsp_buf[0] & SD_TRANSFER_ERR)) अणु
		sd_prपूर्णांक_debug_regs(host);
		sd_clear_error(host);

		अगर (!err) अणु
			dev_dbg(sdmmc_dev(host),
				"Transfer failed (SD_TRANSFER = %02x)\n",
					ucr->rsp_buf[0]);
			err = -EIO;
		पूर्ण अन्यथा अणु
			dev_dbg(sdmmc_dev(host),
				"rtsx_usb_get_rsp failed (err = %d)\n", err);
		पूर्ण

		जाओ out;
	पूर्ण

	अगर (rsp_type == SD_RSP_TYPE_R0) अणु
		err = 0;
		जाओ out;
	पूर्ण

	/* Skip result of CHECK_REG_CMD */
	ptr = ucr->rsp_buf + 1;

	/* Check (Start,Transmission) bit of Response */
	अगर ((ptr[0] & 0xC0) != 0) अणु
		err = -EILSEQ;
		dev_dbg(sdmmc_dev(host), "Invalid response bit\n");
		जाओ out;
	पूर्ण

	/* Check CRC7 */
	अगर (!(rsp_type & SD_NO_CHECK_CRC7)) अणु
		अगर (ptr[stat_idx] & SD_CRC7_ERR) अणु
			err = -EILSEQ;
			dev_dbg(sdmmc_dev(host), "CRC7 error\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rsp_type == SD_RSP_TYPE_R2) अणु
		/*
		 * The controller offloads the last byte अणुCRC-7, end bit 1'b1पूर्ण
		 * of response type R2. Assign dummy CRC, 0, and end bit to the
		 * byte(ptr[16], goes पूर्णांकo the LSB of resp[3] later).
		 */
		ptr[16] = 1;

		क्रम (i = 0; i < 4; i++) अणु
			cmd->resp[i] = get_unaligned_be32(ptr + 1 + i * 4);
			dev_dbg(sdmmc_dev(host), "cmd->resp[%d] = 0x%08x\n",
					i, cmd->resp[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->resp[0] = get_unaligned_be32(ptr + 1);
		dev_dbg(sdmmc_dev(host), "cmd->resp[0] = 0x%08x\n",
				cmd->resp[0]);
	पूर्ण

out:
	cmd->error = err;
पूर्ण

अटल पूर्णांक sd_rw_multi(काष्ठा rtsx_usb_sdmmc *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक पढ़ो = (data->flags & MMC_DATA_READ) ? 1 : 0;
	u8 cfg2, trans_mode;
	पूर्णांक err;
	u8 flag;
	माप_प्रकार data_len = data->blksz * data->blocks;
	अचिन्हित पूर्णांक pipe;

	अगर (पढ़ो) अणु
		dev_dbg(sdmmc_dev(host), "%s: read %zu bytes\n",
				__func__, data_len);
		cfg2 = SD_CALCULATE_CRC7 | SD_CHECK_CRC16 |
			SD_NO_WAIT_BUSY_END | SD_CHECK_CRC7 | SD_RSP_LEN_0;
		trans_mode = SD_TM_AUTO_READ_3;
	पूर्ण अन्यथा अणु
		dev_dbg(sdmmc_dev(host), "%s: write %zu bytes\n",
				__func__, data_len);
		cfg2 = SD_NO_CALCULATE_CRC7 | SD_CHECK_CRC16 |
			SD_NO_WAIT_BUSY_END | SD_NO_CHECK_CRC7 | SD_RSP_LEN_0;
		trans_mode = SD_TM_AUTO_WRITE_3;
	पूर्ण

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BYTE_CNT_L, 0xFF, 0x00);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BYTE_CNT_H, 0xFF, 0x02);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BLOCK_CNT_L,
			0xFF, (u8)data->blocks);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BLOCK_CNT_H,
			0xFF, (u8)(data->blocks >> 8));

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, RING_BUFFER);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC3,
			0xFF, (u8)(data_len >> 24));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC2,
			0xFF, (u8)(data_len >> 16));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC1,
			0xFF, (u8)(data_len >> 8));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC0,
			0xFF, (u8)data_len);
	अगर (पढ़ो) अणु
		flag = MODE_Cसूची;
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_CTL,
				0x03 | DMA_PACK_SIZE_MASK,
				DMA_सूची_FROM_CARD | DMA_EN | DMA_512);
	पूर्ण अन्यथा अणु
		flag = MODE_CDOR;
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_CTL,
				0x03 | DMA_PACK_SIZE_MASK,
				DMA_सूची_TO_CARD | DMA_EN | DMA_512);
	पूर्ण

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG2, 0xFF, cfg2);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_TRANSFER, 0xFF,
			trans_mode | SD_TRANSFER_START);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);

	err = rtsx_usb_send_cmd(ucr, flag, 100);
	अगर (err)
		वापस err;

	अगर (पढ़ो)
		pipe = usb_rcvbulkpipe(ucr->pusb_dev, EP_BULK_IN);
	अन्यथा
		pipe = usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT);

	err = rtsx_usb_transfer_data(ucr, pipe, data->sg, data_len,
			data->sg_len,  शून्य, 10000);
	अगर (err) अणु
		dev_dbg(sdmmc_dev(host), "rtsx_usb_transfer_data error %d\n"
				, err);
		sd_clear_error(host);
		वापस err;
	पूर्ण

	वापस rtsx_usb_get_rsp(ucr, 1, 2000);
पूर्ण

अटल अंतरभूत व्योम sd_enable_initial_mode(काष्ठा rtsx_usb_sdmmc *host)
अणु
	rtsx_usb_ग_लिखो_रेजिस्टर(host->ucr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, SD_CLK_DIVIDE_128);
पूर्ण

अटल अंतरभूत व्योम sd_disable_initial_mode(काष्ठा rtsx_usb_sdmmc *host)
अणु
	rtsx_usb_ग_लिखो_रेजिस्टर(host->ucr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, SD_CLK_DIVIDE_0);
पूर्ण

अटल व्योम sd_normal_rw(काष्ठा rtsx_usb_sdmmc *host,
		काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	u8 *buf;

	buf = kzalloc(data->blksz, GFP_NOIO);
	अगर (!buf) अणु
		cmd->error = -ENOMEM;
		वापस;
	पूर्ण

	अगर (data->flags & MMC_DATA_READ) अणु
		अगर (host->initial_mode)
			sd_disable_initial_mode(host);

		cmd->error = sd_पढ़ो_data(host, cmd, (u16)data->blksz, buf,
				data->blksz, 200);

		अगर (host->initial_mode)
			sd_enable_initial_mode(host);

		sg_copy_from_buffer(data->sg, data->sg_len, buf, data->blksz);
	पूर्ण अन्यथा अणु
		sg_copy_to_buffer(data->sg, data->sg_len, buf, data->blksz);

		cmd->error = sd_ग_लिखो_data(host, cmd, (u16)data->blksz, buf,
				data->blksz, 200);
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल पूर्णांक sd_change_phase(काष्ठा rtsx_usb_sdmmc *host, u8 sample_poपूर्णांक, पूर्णांक tx)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;

	dev_dbg(sdmmc_dev(host), "%s: %s sample_point = %d\n",
			__func__, tx ? "TX" : "RX", sample_poपूर्णांक);

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CLK_DIV, CLK_CHANGE, CLK_CHANGE);

	अगर (tx)
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				0x0F, sample_poपूर्णांक);
	अन्यथा
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK1_CTL,
				0x0F, sample_poपूर्णांक);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL, PHASE_NOT_RESET, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL,
			PHASE_NOT_RESET, PHASE_NOT_RESET);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CLK_DIV, CLK_CHANGE, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG1, SD_ASYNC_FIFO_RST, 0);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल अंतरभूत u32 get_phase_poपूर्णांक(u32 phase_map, अचिन्हित पूर्णांक idx)
अणु
	idx &= MAX_PHASE;
	वापस phase_map & (1 << idx);
पूर्ण

अटल पूर्णांक get_phase_len(u32 phase_map, अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PHASE + 1; i++) अणु
		अगर (get_phase_poपूर्णांक(phase_map, idx + i) == 0)
			वापस i;
	पूर्ण
	वापस MAX_PHASE + 1;
पूर्ण

अटल u8 sd_search_final_phase(काष्ठा rtsx_usb_sdmmc *host, u32 phase_map)
अणु
	पूर्णांक start = 0, len = 0;
	पूर्णांक start_final = 0, len_final = 0;
	u8 final_phase = 0xFF;

	अगर (phase_map == 0) अणु
		dev_dbg(sdmmc_dev(host), "Phase: [map:%x]\n", phase_map);
		वापस final_phase;
	पूर्ण

	जबतक (start < MAX_PHASE + 1) अणु
		len = get_phase_len(phase_map, start);
		अगर (len_final < len) अणु
			start_final = start;
			len_final = len;
		पूर्ण
		start += len ? len : 1;
	पूर्ण

	final_phase = (start_final + len_final / 2) & MAX_PHASE;
	dev_dbg(sdmmc_dev(host), "Phase: [map:%x] [maxlen:%d] [final:%d]\n",
		phase_map, len_final, final_phase);

	वापस final_phase;
पूर्ण

अटल व्योम sd_रुको_data_idle(काष्ठा rtsx_usb_sdmmc *host)
अणु
	पूर्णांक i;
	u8 val = 0;

	क्रम (i = 0; i < 100; i++) अणु
		rtsx_usb_ep0_पढ़ो_रेजिस्टर(host->ucr, SD_DATA_STATE, &val);
		अगर (val & SD_DATA_IDLE)
			वापस;

		usleep_range(100, 1000);
	पूर्ण
पूर्ण

अटल पूर्णांक sd_tuning_rx_cmd(काष्ठा rtsx_usb_sdmmc *host,
		u8 opcode, u8 sample_poपूर्णांक)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	err = sd_change_phase(host, sample_poपूर्णांक, 0);
	अगर (err)
		वापस err;

	cmd.opcode = MMC_SEND_TUNING_BLOCK;
	err = sd_पढ़ो_data(host, &cmd, 0x40, शून्य, 0, 100);
	अगर (err) अणु
		/* Wait till SD DATA IDLE */
		sd_रुको_data_idle(host);
		sd_clear_error(host);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sd_tuning_phase(काष्ठा rtsx_usb_sdmmc *host,
		u8 opcode, u16 *phase_map)
अणु
	पूर्णांक err, i;
	u16 raw_phase_map = 0;

	क्रम (i = MAX_PHASE; i >= 0; i--) अणु
		err = sd_tuning_rx_cmd(host, opcode, (u8)i);
		अगर (!err)
			raw_phase_map |= 1 << i;
	पूर्ण

	अगर (phase_map)
		*phase_map = raw_phase_map;
पूर्ण

अटल पूर्णांक sd_tuning_rx(काष्ठा rtsx_usb_sdmmc *host, u8 opcode)
अणु
	पूर्णांक err, i;
	u16 raw_phase_map[RX_TUNING_CNT] = अणु0पूर्ण, phase_map;
	u8 final_phase;

	/* setting fixed शेष TX phase */
	err = sd_change_phase(host, 0x01, 1);
	अगर (err) अणु
		dev_dbg(sdmmc_dev(host), "TX phase setting failed\n");
		वापस err;
	पूर्ण

	/* tuning RX phase */
	क्रम (i = 0; i < RX_TUNING_CNT; i++) अणु
		sd_tuning_phase(host, opcode, &(raw_phase_map[i]));

		अगर (raw_phase_map[i] == 0)
			अवरोध;
	पूर्ण

	phase_map = 0xFFFF;
	क्रम (i = 0; i < RX_TUNING_CNT; i++) अणु
		dev_dbg(sdmmc_dev(host), "RX raw_phase_map[%d] = 0x%04x\n",
				i, raw_phase_map[i]);
		phase_map &= raw_phase_map[i];
	पूर्ण
	dev_dbg(sdmmc_dev(host), "RX phase_map = 0x%04x\n", phase_map);

	अगर (phase_map) अणु
		final_phase = sd_search_final_phase(host, phase_map);
		अगर (final_phase == 0xFF)
			वापस -EINVAL;

		err = sd_change_phase(host, final_phase, 0);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	u16 val;

	अगर (host->host_removal)
		वापस -ENOMEDIUM;

	mutex_lock(&ucr->dev_mutex);

	/* Check SD card detect */
	err = rtsx_usb_get_card_status(ucr, &val);

	mutex_unlock(&ucr->dev_mutex);


	/* Treat failed detection as non-ro */
	अगर (err)
		वापस 0;

	अगर (val & SD_WP)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	u16 val;

	अगर (host->host_removal)
		वापस -ENOMEDIUM;

	mutex_lock(&ucr->dev_mutex);

	/* Check SD card detect */
	err = rtsx_usb_get_card_status(ucr, &val);

	mutex_unlock(&ucr->dev_mutex);

	/* Treat failed detection as non-exist */
	अगर (err)
		जाओ no_card;

	अगर (val & SD_CD) अणु
		host->card_exist = true;
		वापस 1;
	पूर्ण

no_card:
	host->card_exist = false;
	वापस 0;
पूर्ण

अटल व्योम sdmmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	अचिन्हित पूर्णांक data_size = 0;

	dev_dbg(sdmmc_dev(host), "%s\n", __func__);

	अगर (host->host_removal) अणु
		cmd->error = -ENOMEDIUM;
		जाओ finish;
	पूर्ण

	अगर ((!host->card_exist)) अणु
		cmd->error = -ENOMEDIUM;
		जाओ finish_detect_card;
	पूर्ण

	mutex_lock(&ucr->dev_mutex);

	mutex_lock(&host->host_mutex);
	host->mrq = mrq;
	mutex_unlock(&host->host_mutex);

	अगर (mrq->data)
		data_size = data->blocks * data->blksz;

	अगर (!data_size) अणु
		sd_send_cmd_get_rsp(host, cmd);
	पूर्ण अन्यथा अगर ((!(data_size % 512) && cmd->opcode != MMC_SEND_EXT_CSD) ||
		   mmc_op_multi(cmd->opcode)) अणु
		sd_send_cmd_get_rsp(host, cmd);

		अगर (!cmd->error) अणु
			sd_rw_multi(host, mrq);

			अगर (mmc_op_multi(cmd->opcode) && mrq->stop) अणु
				sd_send_cmd_get_rsp(host, mrq->stop);
				rtsx_usb_ग_लिखो_रेजिस्टर(ucr, MC_FIFO_CTL,
						FIFO_FLUSH, FIFO_FLUSH);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		sd_normal_rw(host, mrq);
	पूर्ण

	अगर (mrq->data) अणु
		अगर (cmd->error || data->error)
			data->bytes_xfered = 0;
		अन्यथा
			data->bytes_xfered = data->blocks * data->blksz;
	पूर्ण

	mutex_unlock(&ucr->dev_mutex);

finish_detect_card:
	अगर (cmd->error) अणु
		/*
		 * detect card when fail to update card existence state and
		 * speed up card removal when retry
		 */
		sdmmc_get_cd(mmc);
		dev_dbg(sdmmc_dev(host), "cmd->error = %d\n", cmd->error);
	पूर्ण

finish:
	mutex_lock(&host->host_mutex);
	host->mrq = शून्य;
	mutex_unlock(&host->host_mutex);

	mmc_request_करोne(mmc, mrq);
पूर्ण

अटल पूर्णांक sd_set_bus_width(काष्ठा rtsx_usb_sdmmc *host,
		अचिन्हित अक्षर bus_width)
अणु
	पूर्णांक err = 0;
	अटल स्थिर u8 width[] = अणु
		[MMC_BUS_WIDTH_1] = SD_BUS_WIDTH_1BIT,
		[MMC_BUS_WIDTH_4] = SD_BUS_WIDTH_4BIT,
		[MMC_BUS_WIDTH_8] = SD_BUS_WIDTH_8BIT,
	पूर्ण;

	अगर (bus_width <= MMC_BUS_WIDTH_8)
		err = rtsx_usb_ग_लिखो_रेजिस्टर(host->ucr, SD_CFG1,
				0x03, width[bus_width]);

	वापस err;
पूर्ण

अटल पूर्णांक sd_pull_ctl_disable_lqfp48(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0x95);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF, 0xA5);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक sd_pull_ctl_disable_qfn24(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0x65);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0x95);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF, 0x56);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF, 0x59);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक sd_pull_ctl_enable_lqfp48(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0xAA);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0xAA);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0xA9);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF, 0xA5);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक sd_pull_ctl_enable_qfn24(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0xA5);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0x9A);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0xA5);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x9A);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF, 0x65);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF, 0x5A);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक sd_घातer_on(काष्ठा rtsx_usb_sdmmc *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;

	dev_dbg(sdmmc_dev(host), "%s\n", __func__);
	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_SELECT, 0x07, SD_MOD_SEL);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_SHARE_MODE,
			CARD_SHARE_MASK, CARD_SHARE_SD);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_EN,
			SD_CLK_EN, SD_CLK_EN);
	err = rtsx_usb_send_cmd(ucr, MODE_C, 100);
	अगर (err)
		वापस err;

	अगर (CHECK_PKG(ucr, LQFP48))
		err = sd_pull_ctl_enable_lqfp48(ucr);
	अन्यथा
		err = sd_pull_ctl_enable_qfn24(ucr);
	अगर (err)
		वापस err;

	err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, CARD_PWR_CTL,
			POWER_MASK, PARTIAL_POWER_ON);
	अगर (err)
		वापस err;

	usleep_range(800, 1000);

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PWR_CTL,
			POWER_MASK|LDO3318_PWR_MASK, POWER_ON|LDO_ON);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_OE,
			SD_OUTPUT_EN, SD_OUTPUT_EN);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक sd_घातer_off(काष्ठा rtsx_usb_sdmmc *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;

	dev_dbg(sdmmc_dev(host), "%s\n", __func__);
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_EN, SD_CLK_EN, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_OE, SD_OUTPUT_EN, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PWR_CTL,
			POWER_MASK, POWER_OFF);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PWR_CTL,
			POWER_MASK|LDO3318_PWR_MASK, POWER_OFF|LDO_SUSPEND);

	err = rtsx_usb_send_cmd(ucr, MODE_C, 100);
	अगर (err)
		वापस err;

	अगर (CHECK_PKG(ucr, LQFP48))
			वापस sd_pull_ctl_disable_lqfp48(ucr);
	वापस sd_pull_ctl_disable_qfn24(ucr);
पूर्ण

अटल पूर्णांक sd_set_घातer_mode(काष्ठा rtsx_usb_sdmmc *host,
		अचिन्हित अक्षर घातer_mode)
अणु
	पूर्णांक err;

	अगर (घातer_mode != MMC_POWER_OFF)
		घातer_mode = MMC_POWER_ON;

	अगर (घातer_mode == host->घातer_mode)
		वापस 0;

	अगर (घातer_mode == MMC_POWER_OFF) अणु
		err = sd_घातer_off(host);
		pm_runसमय_put_noidle(sdmmc_dev(host));
	पूर्ण अन्यथा अणु
		pm_runसमय_get_noresume(sdmmc_dev(host));
		err = sd_घातer_on(host);
	पूर्ण

	अगर (!err)
		host->घातer_mode = घातer_mode;

	वापस err;
पूर्ण

अटल पूर्णांक sd_set_timing(काष्ठा rtsx_usb_sdmmc *host,
		अचिन्हित अक्षर timing, bool *ddr_mode)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;

	*ddr_mode = false;

	rtsx_usb_init_cmd(ucr);

	चयन (timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_UHS_SDR50:
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG1,
				0x0C | SD_ASYNC_FIFO_RST,
				SD_30_MODE | SD_ASYNC_FIFO_RST);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_VAR_CLK0 | SD30_FIX_CLK | SAMPLE_VAR_CLK1);
		अवरोध;

	हाल MMC_TIMING_UHS_DDR50:
		*ddr_mode = true;

		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG1,
				0x0C | SD_ASYNC_FIFO_RST,
				SD_DDR_MODE | SD_ASYNC_FIFO_RST);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_VAR_CLK0 | SD30_FIX_CLK | SAMPLE_VAR_CLK1);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_PUSH_POINT_CTL,
				DDR_VAR_TX_CMD_DAT, DDR_VAR_TX_CMD_DAT);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_SAMPLE_POINT_CTL,
				DDR_VAR_RX_DAT | DDR_VAR_RX_CMD,
				DDR_VAR_RX_DAT | DDR_VAR_RX_CMD);
		अवरोध;

	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_CFG1,
				0x0C, SD_20_MODE);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_FIX_CLK | SD30_VAR_CLK0 | SAMPLE_VAR_CLK1);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_PUSH_POINT_CTL,
				SD20_TX_SEL_MASK, SD20_TX_14_AHEAD);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_SAMPLE_POINT_CTL,
				SD20_RX_SEL_MASK, SD20_RX_14_DELAY);
		अवरोध;

	शेष:
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_CFG1, 0x0C, SD_20_MODE);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_FIX_CLK | SD30_VAR_CLK0 | SAMPLE_VAR_CLK1);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				SD_PUSH_POINT_CTL, 0xFF, 0);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_SAMPLE_POINT_CTL,
				SD20_RX_SEL_MASK, SD20_RX_POS_EDGE);
		अवरोध;
	पूर्ण

	err = rtsx_usb_send_cmd(ucr, MODE_C, 100);

	वापस err;
पूर्ण

अटल व्योम sdmmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;

	dev_dbg(sdmmc_dev(host), "%s\n", __func__);
	mutex_lock(&ucr->dev_mutex);

	sd_set_घातer_mode(host, ios->घातer_mode);
	sd_set_bus_width(host, ios->bus_width);
	sd_set_timing(host, ios->timing, &host->ddr_mode);

	host->vpclk = false;
	host->द्विगुन_clk = true;

	चयन (ios->timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_UHS_SDR50:
		host->ssc_depth = SSC_DEPTH_2M;
		host->vpclk = true;
		host->द्विगुन_clk = false;
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_UHS_SDR25:
		host->ssc_depth = SSC_DEPTH_1M;
		अवरोध;
	शेष:
		host->ssc_depth = SSC_DEPTH_512K;
		अवरोध;
	पूर्ण

	host->initial_mode = (ios->घड़ी <= 1000000) ? true : false;
	host->घड़ी = ios->घड़ी;

	rtsx_usb_चयन_घड़ी(host->ucr, host->घड़ी, host->ssc_depth,
			host->initial_mode, host->द्विगुन_clk, host->vpclk);

	mutex_unlock(&ucr->dev_mutex);
	dev_dbg(sdmmc_dev(host), "%s end\n", __func__);
पूर्ण

अटल पूर्णांक sdmmc_चयन_voltage(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err = 0;

	dev_dbg(sdmmc_dev(host), "%s: signal_voltage = %d\n",
			__func__, ios->संकेत_voltage);

	अगर (host->host_removal)
		वापस -ENOMEDIUM;

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_120)
		वापस -EPERM;

	mutex_lock(&ucr->dev_mutex);

	err = rtsx_usb_card_exclusive_check(ucr, RTSX_USB_SD_CARD);
	अगर (err) अणु
		mutex_unlock(&ucr->dev_mutex);
		वापस err;
	पूर्ण

	/* Let mmc core करो the busy checking, simply stop the क्रमced-toggle
	 * घड़ी(जबतक issuing CMD11) and चयन voltage.
	 */
	rtsx_usb_init_cmd(ucr);

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_PAD_CTL,
				SD_IO_USING_1V8, SD_IO_USING_3V3);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, LDO_POWER_CFG,
				TUNE_SD18_MASK, TUNE_SD18_3V3);
	पूर्ण अन्यथा अणु
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_BUS_STAT,
				SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP,
				SD_CLK_FORCE_STOP);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_PAD_CTL,
				SD_IO_USING_1V8, SD_IO_USING_1V8);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, LDO_POWER_CFG,
				TUNE_SD18_MASK, TUNE_SD18_1V8);
	पूर्ण

	err = rtsx_usb_send_cmd(ucr, MODE_C, 100);
	mutex_unlock(&ucr->dev_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक sdmmc_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	u8 stat;
	u8 mask = SD_DAT3_STATUS | SD_DAT2_STATUS | SD_DAT1_STATUS
		| SD_DAT0_STATUS;

	dev_dbg(sdmmc_dev(host), "%s\n", __func__);

	mutex_lock(&ucr->dev_mutex);

	err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, SD_BUS_STAT,
			SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP,
			SD_CLK_TOGGLE_EN);
	अगर (err)
		जाओ out;

	mdelay(1);

	err = rtsx_usb_पढ़ो_रेजिस्टर(ucr, SD_BUS_STAT, &stat);
	अगर (err)
		जाओ out;

	err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, SD_BUS_STAT,
			SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);
out:
	mutex_unlock(&ucr->dev_mutex);

	अगर (err)
		वापस err;

	/* check अगर any pin between dat[0:3] is low */
	अगर ((stat & mask) != mask)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा rtsx_usb_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err = 0;

	अगर (host->host_removal)
		वापस -ENOMEDIUM;

	mutex_lock(&ucr->dev_mutex);

	अगर (!host->ddr_mode)
		err = sd_tuning_rx(host, MMC_SEND_TUNING_BLOCK);

	mutex_unlock(&ucr->dev_mutex);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops rtsx_usb_sdmmc_ops = अणु
	.request = sdmmc_request,
	.set_ios = sdmmc_set_ios,
	.get_ro = sdmmc_get_ro,
	.get_cd = sdmmc_get_cd,
	.start_संकेत_voltage_चयन = sdmmc_चयन_voltage,
	.card_busy = sdmmc_card_busy,
	.execute_tuning = sdmmc_execute_tuning,
पूर्ण;

#अगर_घोषित RTSX_USB_USE_LEDS_CLASS
अटल व्योम rtsx_usb_led_control(काष्ठा led_classdev *led,
	क्रमागत led_brightness brightness)
अणु
	काष्ठा rtsx_usb_sdmmc *host = container_of(led,
			काष्ठा rtsx_usb_sdmmc, led);

	अगर (host->host_removal)
		वापस;

	host->led.brightness = brightness;
	schedule_work(&host->led_work);
पूर्ण

अटल व्योम rtsx_usb_update_led(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtsx_usb_sdmmc *host =
		container_of(work, काष्ठा rtsx_usb_sdmmc, led_work);
	काष्ठा rtsx_ucr *ucr = host->ucr;

	pm_runसमय_get_noresume(sdmmc_dev(host));
	mutex_lock(&ucr->dev_mutex);

	अगर (host->घातer_mode == MMC_POWER_OFF)
		जाओ out;

	अगर (host->led.brightness == LED_OFF)
		rtsx_usb_turn_off_led(ucr);
	अन्यथा
		rtsx_usb_turn_on_led(ucr);

out:
	mutex_unlock(&ucr->dev_mutex);
	pm_runसमय_put_sync_suspend(sdmmc_dev(host));
पूर्ण
#पूर्ण_अगर

अटल व्योम rtsx_usb_init_host(काष्ठा rtsx_usb_sdmmc *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	mmc->f_min = 250000;
	mmc->f_max = 208000000;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED |
		MMC_CAP_MMC_HIGHSPEED | MMC_CAP_BUS_WIDTH_TEST |
		MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50 |
		MMC_CAP_SYNC_RUNTIME_PM;
	mmc->caps2 = MMC_CAP2_NO_PRESCAN_POWERUP | MMC_CAP2_FULL_PWR_CYCLE |
		MMC_CAP2_NO_SDIO;

	mmc->max_current_330 = 400;
	mmc->max_current_180 = 800;
	mmc->ops = &rtsx_usb_sdmmc_ops;
	mmc->max_segs = 256;
	mmc->max_seg_size = 65536;
	mmc->max_blk_size = 512;
	mmc->max_blk_count = 65535;
	mmc->max_req_size = 524288;

	host->घातer_mode = MMC_POWER_OFF;
पूर्ण

अटल पूर्णांक rtsx_usb_sdmmc_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा rtsx_usb_sdmmc *host;
	काष्ठा rtsx_ucr *ucr;
#अगर_घोषित RTSX_USB_USE_LEDS_CLASS
	पूर्णांक err;
#पूर्ण_अगर

	ucr = usb_get_पूर्णांकfdata(to_usb_पूर्णांकerface(pdev->dev.parent));
	अगर (!ucr)
		वापस -ENXIO;

	dev_dbg(&(pdev->dev), ": Realtek USB SD/MMC controller found\n");

	mmc = mmc_alloc_host(माप(*host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	host->ucr = ucr;
	host->mmc = mmc;
	host->pdev = pdev;
	platक्रमm_set_drvdata(pdev, host);

	mutex_init(&host->host_mutex);
	rtsx_usb_init_host(host);
	pm_runसमय_enable(&pdev->dev);

#अगर_घोषित RTSX_USB_USE_LEDS_CLASS
	snम_लिखो(host->led_name, माप(host->led_name),
		"%s::", mmc_hostname(mmc));
	host->led.name = host->led_name;
	host->led.brightness = LED_OFF;
	host->led.शेष_trigger = mmc_hostname(mmc);
	host->led.brightness_set = rtsx_usb_led_control;

	err = led_classdev_रेजिस्टर(mmc_dev(mmc), &host->led);
	अगर (err)
		dev_err(&(pdev->dev),
				"Failed to register LED device: %d\n", err);
	INIT_WORK(&host->led_work, rtsx_usb_update_led);

#पूर्ण_अगर
	mmc_add_host(mmc);

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_sdmmc_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtsx_usb_sdmmc *host = platक्रमm_get_drvdata(pdev);
	काष्ठा mmc_host *mmc;

	अगर (!host)
		वापस 0;

	mmc = host->mmc;
	host->host_removal = true;

	mutex_lock(&host->host_mutex);
	अगर (host->mrq) अणु
		dev_dbg(&(pdev->dev),
			"%s: Controller removed during transfer\n",
			mmc_hostname(mmc));
		host->mrq->cmd->error = -ENOMEDIUM;
		अगर (host->mrq->stop)
			host->mrq->stop->error = -ENOMEDIUM;
		mmc_request_करोne(mmc, host->mrq);
	पूर्ण
	mutex_unlock(&host->host_mutex);

	mmc_हटाओ_host(mmc);

#अगर_घोषित RTSX_USB_USE_LEDS_CLASS
	cancel_work_sync(&host->led_work);
	led_classdev_unरेजिस्टर(&host->led);
#पूर्ण_अगर

	mmc_मुक्त_host(mmc);
	pm_runसमय_disable(&pdev->dev);
	platक्रमm_set_drvdata(pdev, शून्य);

	dev_dbg(&(pdev->dev),
		": Realtek USB SD/MMC module has been removed\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rtsx_usb_sdmmc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rtsx_usb_sdmmc *host = dev_get_drvdata(dev);

	host->mmc->caps &= ~MMC_CAP_NEEDS_POLL;
	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_sdmmc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rtsx_usb_sdmmc *host = dev_get_drvdata(dev);

	host->mmc->caps |= MMC_CAP_NEEDS_POLL;
	अगर (sdmmc_get_cd(host->mmc) == 1)
		mmc_detect_change(host->mmc, 0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rtsx_usb_sdmmc_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(rtsx_usb_sdmmc_runसमय_suspend,
			   rtsx_usb_sdmmc_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id rtsx_usb_sdmmc_ids[] = अणु
	अणु
		.name = "rtsx_usb_sdmmc",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rtsx_usb_sdmmc_ids);

अटल काष्ठा platक्रमm_driver rtsx_usb_sdmmc_driver = अणु
	.probe		= rtsx_usb_sdmmc_drv_probe,
	.हटाओ		= rtsx_usb_sdmmc_drv_हटाओ,
	.id_table       = rtsx_usb_sdmmc_ids,
	.driver		= अणु
		.name	= "rtsx_usb_sdmmc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &rtsx_usb_sdmmc_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rtsx_usb_sdmmc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Roger Tseng <rogerable@realtek.com>");
MODULE_DESCRIPTION("Realtek USB SD/MMC Card Host Driver");
