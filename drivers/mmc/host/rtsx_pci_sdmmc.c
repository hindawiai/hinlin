<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Realtek PCI-Express SD/MMC Card Interface driver
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/card.h>
#समावेश <linux/rtsx_pci.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/pm_runसमय.स>

काष्ठा realtek_pci_sdmmc अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा rtsx_pcr		*pcr;
	काष्ठा mmc_host		*mmc;
	काष्ठा mmc_request	*mrq;
#घोषणा SDMMC_WORKQ_NAME	"rtsx_pci_sdmmc_workq"

	काष्ठा work_काष्ठा	work;
	काष्ठा mutex		host_mutex;

	u8			ssc_depth;
	अचिन्हित पूर्णांक		घड़ी;
	bool			vpclk;
	bool			द्विगुन_clk;
	bool			eject;
	bool			initial_mode;
	पूर्णांक			घातer_state;
#घोषणा SDMMC_POWER_ON		1
#घोषणा SDMMC_POWER_OFF		0

	पूर्णांक			sg_count;
	s32			cookie;
	पूर्णांक			cookie_sg_count;
	bool			using_cookie;
पूर्ण;

अटल पूर्णांक sdmmc_init_sd_express(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios);

अटल अंतरभूत काष्ठा device *sdmmc_dev(काष्ठा realtek_pci_sdmmc *host)
अणु
	वापस &(host->pdev->dev);
पूर्ण

अटल अंतरभूत व्योम sd_clear_error(काष्ठा realtek_pci_sdmmc *host)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(host->pcr, CARD_STOP,
			SD_STOP | SD_CLR_ERR, SD_STOP | SD_CLR_ERR);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम dump_reg_range(काष्ठा realtek_pci_sdmmc *host, u16 start, u16 end)
अणु
	u16 len = end - start + 1;
	पूर्णांक i;
	u8 data[8];

	क्रम (i = 0; i < len; i += 8) अणु
		पूर्णांक j;
		पूर्णांक n = min(8, len - i);

		स_रखो(&data, 0, माप(data));
		क्रम (j = 0; j < n; j++)
			rtsx_pci_पढ़ो_रेजिस्टर(host->pcr, start + i + j,
				data + j);
		dev_dbg(sdmmc_dev(host), "0x%04X(%d): %8ph\n",
			start + i, n, data);
	पूर्ण
पूर्ण

अटल व्योम sd_prपूर्णांक_debug_regs(काष्ठा realtek_pci_sdmmc *host)
अणु
	dump_reg_range(host, 0xFDA0, 0xFDB3);
	dump_reg_range(host, 0xFD52, 0xFD69);
पूर्ण
#अन्यथा
#घोषणा sd_prपूर्णांक_debug_regs(host)
#पूर्ण_अगर /* DEBUG */

अटल अंतरभूत पूर्णांक sd_get_cd_पूर्णांक(काष्ठा realtek_pci_sdmmc *host)
अणु
	वापस rtsx_pci_पढ़ोl(host->pcr, RTSX_BIPR) & SD_EXIST;
पूर्ण

अटल व्योम sd_cmd_set_sd_cmd(काष्ठा rtsx_pcr *pcr, काष्ठा mmc_command *cmd)
अणु
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CMD0, 0xFF,
		SD_CMD_START | cmd->opcode);
	rtsx_pci_ग_लिखो_be32(pcr, SD_CMD1, cmd->arg);
पूर्ण

अटल व्योम sd_cmd_set_data_len(काष्ठा rtsx_pcr *pcr, u16 blocks, u16 blksz)
अणु
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BLOCK_CNT_L, 0xFF, blocks);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BLOCK_CNT_H, 0xFF, blocks >> 8);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BYTE_CNT_L, 0xFF, blksz);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BYTE_CNT_H, 0xFF, blksz >> 8);
पूर्ण

अटल पूर्णांक sd_response_type(काष्ठा mmc_command *cmd)
अणु
	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		वापस SD_RSP_TYPE_R0;
	हाल MMC_RSP_R1:
		वापस SD_RSP_TYPE_R1;
	हाल MMC_RSP_R1_NO_CRC:
		वापस SD_RSP_TYPE_R1 | SD_NO_CHECK_CRC7;
	हाल MMC_RSP_R1B:
		वापस SD_RSP_TYPE_R1b;
	हाल MMC_RSP_R2:
		वापस SD_RSP_TYPE_R2;
	हाल MMC_RSP_R3:
		वापस SD_RSP_TYPE_R3;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sd_status_index(पूर्णांक resp_type)
अणु
	अगर (resp_type == SD_RSP_TYPE_R0)
		वापस 0;
	अन्यथा अगर (resp_type == SD_RSP_TYPE_R2)
		वापस 16;

	वापस 5;
पूर्ण
/*
 * sd_pre_dma_transfer - करो dma_map_sg() or using cookie
 *
 * @pre: अगर called in pre_req()
 * वापस:
 *	0 - करो dma_map_sg()
 *	1 - using cookie
 */
अटल पूर्णांक sd_pre_dma_transfer(काष्ठा realtek_pci_sdmmc *host,
		काष्ठा mmc_data *data, bool pre)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक पढ़ो = data->flags & MMC_DATA_READ;
	पूर्णांक count = 0;
	पूर्णांक using_cookie = 0;

	अगर (!pre && data->host_cookie && data->host_cookie != host->cookie) अणु
		dev_err(sdmmc_dev(host),
			"error: data->host_cookie = %d, host->cookie = %d\n",
			data->host_cookie, host->cookie);
		data->host_cookie = 0;
	पूर्ण

	अगर (pre || data->host_cookie != host->cookie) अणु
		count = rtsx_pci_dma_map_sg(pcr, data->sg, data->sg_len, पढ़ो);
	पूर्ण अन्यथा अणु
		count = host->cookie_sg_count;
		using_cookie = 1;
	पूर्ण

	अगर (pre) अणु
		host->cookie_sg_count = count;
		अगर (++host->cookie < 0)
			host->cookie = 1;
		data->host_cookie = host->cookie;
	पूर्ण अन्यथा अणु
		host->sg_count = count;
	पूर्ण

	वापस using_cookie;
पूर्ण

अटल व्योम sdmmc_pre_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (data->host_cookie) अणु
		dev_err(sdmmc_dev(host),
			"error: reset data->host_cookie = %d\n",
			data->host_cookie);
		data->host_cookie = 0;
	पूर्ण

	sd_pre_dma_transfer(host, data, true);
	dev_dbg(sdmmc_dev(host), "pre dma sg: %d\n", host->cookie_sg_count);
पूर्ण

अटल व्योम sdmmc_post_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
		पूर्णांक err)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक पढ़ो = data->flags & MMC_DATA_READ;

	rtsx_pci_dma_unmap_sg(pcr, data->sg, data->sg_len, पढ़ो);
	data->host_cookie = 0;
पूर्ण

अटल व्योम sd_send_cmd_get_rsp(काष्ठा realtek_pci_sdmmc *host,
		काष्ठा mmc_command *cmd)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	u8 cmd_idx = (u8)cmd->opcode;
	u32 arg = cmd->arg;
	पूर्णांक err = 0;
	पूर्णांक समयout = 100;
	पूर्णांक i;
	u8 *ptr;
	पूर्णांक rsp_type;
	पूर्णांक stat_idx;
	bool घड़ी_प्रकारoggled = false;

	dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD %d, arg = 0x%08x\n",
			__func__, cmd_idx, arg);

	rsp_type = sd_response_type(cmd);
	अगर (rsp_type < 0)
		जाओ out;

	stat_idx = sd_status_index(rsp_type);

	अगर (rsp_type == SD_RSP_TYPE_R1b)
		समयout = cmd->busy_समयout ? cmd->busy_समयout : 3000;

	अगर (cmd->opcode == SD_SWITCH_VOLTAGE) अणु
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_BUS_STAT,
				0xFF, SD_CLK_TOGGLE_EN);
		अगर (err < 0)
			जाओ out;

		घड़ी_प्रकारoggled = true;
	पूर्ण

	rtsx_pci_init_cmd(pcr);
	sd_cmd_set_sd_cmd(pcr, cmd);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG2, 0xFF, rsp_type);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, PINGPONG_BUFFER);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_TRANSFER,
			0xFF, SD_TM_CMD_RSP | SD_TRANSFER_START);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, SD_TRANSFER,
		     SD_TRANSFER_END | SD_STAT_IDLE,
		     SD_TRANSFER_END | SD_STAT_IDLE);

	अगर (rsp_type == SD_RSP_TYPE_R2) अणु
		/* Read data from ping-pong buffer */
		क्रम (i = PPBUF_BASE2; i < PPBUF_BASE2 + 16; i++)
			rtsx_pci_add_cmd(pcr, READ_REG_CMD, (u16)i, 0, 0);
	पूर्ण अन्यथा अगर (rsp_type != SD_RSP_TYPE_R0) अणु
		/* Read data from SD_CMDx रेजिस्टरs */
		क्रम (i = SD_CMD0; i <= SD_CMD4; i++)
			rtsx_pci_add_cmd(pcr, READ_REG_CMD, (u16)i, 0, 0);
	पूर्ण

	rtsx_pci_add_cmd(pcr, READ_REG_CMD, SD_STAT1, 0, 0);

	err = rtsx_pci_send_cmd(pcr, समयout);
	अगर (err < 0) अणु
		sd_prपूर्णांक_debug_regs(host);
		sd_clear_error(host);
		dev_dbg(sdmmc_dev(host),
			"rtsx_pci_send_cmd error (err = %d)\n", err);
		जाओ out;
	पूर्ण

	अगर (rsp_type == SD_RSP_TYPE_R0) अणु
		err = 0;
		जाओ out;
	पूर्ण

	/* Eliminate वापसed value of CHECK_REG_CMD */
	ptr = rtsx_pci_get_cmd_data(pcr) + 1;

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

	अगर (err && घड़ी_प्रकारoggled)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_BUS_STAT,
				SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);
पूर्ण

अटल पूर्णांक sd_पढ़ो_data(काष्ठा realtek_pci_sdmmc *host, काष्ठा mmc_command *cmd,
	u16 byte_cnt, u8 *buf, पूर्णांक buf_len, पूर्णांक समयout)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;
	u8 trans_mode;

	dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD %d, arg = 0x%08x\n",
		__func__, cmd->opcode, cmd->arg);

	अगर (!buf)
		buf_len = 0;

	अगर (cmd->opcode == MMC_SEND_TUNING_BLOCK)
		trans_mode = SD_TM_AUTO_TUNING;
	अन्यथा
		trans_mode = SD_TM_NORMAL_READ;

	rtsx_pci_init_cmd(pcr);
	sd_cmd_set_sd_cmd(pcr, cmd);
	sd_cmd_set_data_len(pcr, 1, byte_cnt);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG2, 0xFF,
			SD_CALCULATE_CRC7 | SD_CHECK_CRC16 |
			SD_NO_WAIT_BUSY_END | SD_CHECK_CRC7 | SD_RSP_LEN_6);
	अगर (trans_mode != SD_TM_AUTO_TUNING)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				CARD_DATA_SOURCE, 0x01, PINGPONG_BUFFER);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_TRANSFER,
			0xFF, trans_mode | SD_TRANSFER_START);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);

	err = rtsx_pci_send_cmd(pcr, समयout);
	अगर (err < 0) अणु
		sd_prपूर्णांक_debug_regs(host);
		dev_dbg(sdmmc_dev(host),
			"rtsx_pci_send_cmd fail (err = %d)\n", err);
		वापस err;
	पूर्ण

	अगर (buf && buf_len) अणु
		err = rtsx_pci_पढ़ो_ppbuf(pcr, buf, buf_len);
		अगर (err < 0) अणु
			dev_dbg(sdmmc_dev(host),
				"rtsx_pci_read_ppbuf fail (err = %d)\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sd_ग_लिखो_data(काष्ठा realtek_pci_sdmmc *host,
	काष्ठा mmc_command *cmd, u16 byte_cnt, u8 *buf, पूर्णांक buf_len,
	पूर्णांक समयout)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;

	dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD %d, arg = 0x%08x\n",
		__func__, cmd->opcode, cmd->arg);

	अगर (!buf)
		buf_len = 0;

	sd_send_cmd_get_rsp(host, cmd);
	अगर (cmd->error)
		वापस cmd->error;

	अगर (buf && buf_len) अणु
		err = rtsx_pci_ग_लिखो_ppbuf(pcr, buf, buf_len);
		अगर (err < 0) अणु
			dev_dbg(sdmmc_dev(host),
				"rtsx_pci_write_ppbuf fail (err = %d)\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	rtsx_pci_init_cmd(pcr);
	sd_cmd_set_data_len(pcr, 1, byte_cnt);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG2, 0xFF,
		SD_CALCULATE_CRC7 | SD_CHECK_CRC16 |
		SD_NO_WAIT_BUSY_END | SD_CHECK_CRC7 | SD_RSP_LEN_0);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_TRANSFER, 0xFF,
			SD_TRANSFER_START | SD_TM_AUTO_WRITE_3);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);

	err = rtsx_pci_send_cmd(pcr, समयout);
	अगर (err < 0) अणु
		sd_prपूर्णांक_debug_regs(host);
		dev_dbg(sdmmc_dev(host),
			"rtsx_pci_send_cmd fail (err = %d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sd_पढ़ो_दीर्घ_data(काष्ठा realtek_pci_sdmmc *host,
	काष्ठा mmc_request *mrq)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा mmc_card *card = mmc->card;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक uhs = mmc_card_uhs(card);
	u8 cfg2 = 0;
	पूर्णांक err;
	पूर्णांक resp_type;
	माप_प्रकार data_len = data->blksz * data->blocks;

	dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD %d, arg = 0x%08x\n",
		__func__, cmd->opcode, cmd->arg);

	resp_type = sd_response_type(cmd);
	अगर (resp_type < 0)
		वापस resp_type;

	अगर (!uhs)
		cfg2 |= SD_NO_CHECK_WAIT_CRC_TO;

	rtsx_pci_init_cmd(pcr);
	sd_cmd_set_sd_cmd(pcr, cmd);
	sd_cmd_set_data_len(pcr, data->blocks, data->blksz);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, IRQSTAT0,
			DMA_DONE_INT, DMA_DONE_INT);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC3,
		0xFF, (u8)(data_len >> 24));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC2,
		0xFF, (u8)(data_len >> 16));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC1,
		0xFF, (u8)(data_len >> 8));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC0, 0xFF, (u8)data_len);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMACTL,
		0x03 | DMA_PACK_SIZE_MASK,
		DMA_सूची_FROM_CARD | DMA_EN | DMA_512);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, RING_BUFFER);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG2, 0xFF, cfg2 | resp_type);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_TRANSFER, 0xFF,
			SD_TRANSFER_START | SD_TM_AUTO_READ_2);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);
	rtsx_pci_send_cmd_no_रुको(pcr);

	err = rtsx_pci_dma_transfer(pcr, data->sg, host->sg_count, 1, 10000);
	अगर (err < 0) अणु
		sd_prपूर्णांक_debug_regs(host);
		sd_clear_error(host);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sd_ग_लिखो_दीर्घ_data(काष्ठा realtek_pci_sdmmc *host,
	काष्ठा mmc_request *mrq)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा mmc_card *card = mmc->card;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक uhs = mmc_card_uhs(card);
	u8 cfg2;
	पूर्णांक err;
	माप_प्रकार data_len = data->blksz * data->blocks;

	sd_send_cmd_get_rsp(host, cmd);
	अगर (cmd->error)
		वापस cmd->error;

	dev_dbg(sdmmc_dev(host), "%s: SD/MMC CMD %d, arg = 0x%08x\n",
		__func__, cmd->opcode, cmd->arg);

	cfg2 = SD_NO_CALCULATE_CRC7 | SD_CHECK_CRC16 |
		SD_NO_WAIT_BUSY_END | SD_NO_CHECK_CRC7 | SD_RSP_LEN_0;

	अगर (!uhs)
		cfg2 |= SD_NO_CHECK_WAIT_CRC_TO;

	rtsx_pci_init_cmd(pcr);
	sd_cmd_set_data_len(pcr, data->blocks, data->blksz);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, IRQSTAT0,
			DMA_DONE_INT, DMA_DONE_INT);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC3,
		0xFF, (u8)(data_len >> 24));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC2,
		0xFF, (u8)(data_len >> 16));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC1,
		0xFF, (u8)(data_len >> 8));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC0, 0xFF, (u8)data_len);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMACTL,
		0x03 | DMA_PACK_SIZE_MASK,
		DMA_सूची_TO_CARD | DMA_EN | DMA_512);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, RING_BUFFER);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG2, 0xFF, cfg2);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_TRANSFER, 0xFF,
			SD_TRANSFER_START | SD_TM_AUTO_WRITE_3);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, SD_TRANSFER,
			SD_TRANSFER_END, SD_TRANSFER_END);
	rtsx_pci_send_cmd_no_रुको(pcr);
	err = rtsx_pci_dma_transfer(pcr, data->sg, host->sg_count, 0, 10000);
	अगर (err < 0) अणु
		sd_clear_error(host);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sd_rw_multi(काष्ठा realtek_pci_sdmmc *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (host->sg_count < 0) अणु
		data->error = host->sg_count;
		dev_dbg(sdmmc_dev(host), "%s: sg_count = %d is invalid\n",
			__func__, host->sg_count);
		वापस data->error;
	पूर्ण

	अगर (data->flags & MMC_DATA_READ)
		वापस sd_पढ़ो_दीर्घ_data(host, mrq);

	वापस sd_ग_लिखो_दीर्घ_data(host, mrq);
पूर्ण

अटल अंतरभूत व्योम sd_enable_initial_mode(काष्ठा realtek_pci_sdmmc *host)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(host->pcr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, SD_CLK_DIVIDE_128);
पूर्ण

अटल अंतरभूत व्योम sd_disable_initial_mode(काष्ठा realtek_pci_sdmmc *host)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(host->pcr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, SD_CLK_DIVIDE_0);
पूर्ण

अटल व्योम sd_normal_rw(काष्ठा realtek_pci_sdmmc *host,
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

अटल पूर्णांक sd_change_phase(काष्ठा realtek_pci_sdmmc *host,
		u8 sample_poपूर्णांक, bool rx)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	u16 SD_VP_CTL = 0;
	dev_dbg(sdmmc_dev(host), "%s(%s): sample_point = %d\n",
			__func__, rx ? "RX" : "TX", sample_poपूर्णांक);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CHANGE_CLK, CHANGE_CLK);
	अगर (rx) अणु
		SD_VP_CTL = SD_VPRX_CTL;
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_VPRX_CTL,
			PHASE_SELECT_MASK, sample_poपूर्णांक);
	पूर्ण अन्यथा अणु
		SD_VP_CTL = SD_VPTX_CTL;
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_VPTX_CTL,
			PHASE_SELECT_MASK, sample_poपूर्णांक);
	पूर्ण
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_VP_CTL, PHASE_NOT_RESET, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_VP_CTL, PHASE_NOT_RESET,
				PHASE_NOT_RESET);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CHANGE_CLK, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1, SD_ASYNC_FIFO_NOT_RST, 0);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 test_phase_bit(u32 phase_map, अचिन्हित पूर्णांक bit)
अणु
	bit %= RTSX_PHASE_MAX;
	वापस phase_map & (1 << bit);
पूर्ण

अटल पूर्णांक sd_get_phase_len(u32 phase_map, अचिन्हित पूर्णांक start_bit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RTSX_PHASE_MAX; i++) अणु
		अगर (test_phase_bit(phase_map, start_bit + i) == 0)
			वापस i;
	पूर्ण
	वापस RTSX_PHASE_MAX;
पूर्ण

अटल u8 sd_search_final_phase(काष्ठा realtek_pci_sdmmc *host, u32 phase_map)
अणु
	पूर्णांक start = 0, len = 0;
	पूर्णांक start_final = 0, len_final = 0;
	u8 final_phase = 0xFF;

	अगर (phase_map == 0) अणु
		dev_err(sdmmc_dev(host), "phase error: [map:%x]\n", phase_map);
		वापस final_phase;
	पूर्ण

	जबतक (start < RTSX_PHASE_MAX) अणु
		len = sd_get_phase_len(phase_map, start);
		अगर (len_final < len) अणु
			start_final = start;
			len_final = len;
		पूर्ण
		start += len ? len : 1;
	पूर्ण

	final_phase = (start_final + len_final / 2) % RTSX_PHASE_MAX;
	dev_dbg(sdmmc_dev(host), "phase: [map:%x] [maxlen:%d] [final:%d]\n",
		phase_map, len_final, final_phase);

	वापस final_phase;
पूर्ण

अटल व्योम sd_रुको_data_idle(काष्ठा realtek_pci_sdmmc *host)
अणु
	पूर्णांक i;
	u8 val = 0;

	क्रम (i = 0; i < 100; i++) अणु
		rtsx_pci_पढ़ो_रेजिस्टर(host->pcr, SD_DATA_STATE, &val);
		अगर (val & SD_DATA_IDLE)
			वापस;

		udelay(100);
	पूर्ण
पूर्ण

अटल पूर्णांक sd_tuning_rx_cmd(काष्ठा realtek_pci_sdmmc *host,
		u8 opcode, u8 sample_poपूर्णांक)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा rtsx_pcr *pcr = host->pcr;

	sd_change_phase(host, sample_poपूर्णांक, true);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
		SD_RSP_80CLK_TIMEOUT_EN);

	cmd.opcode = opcode;
	err = sd_पढ़ो_data(host, &cmd, 0x40, शून्य, 0, 100);
	अगर (err < 0) अणु
		/* Wait till SD DATA IDLE */
		sd_रुको_data_idle(host);
		sd_clear_error(host);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG3,
			SD_RSP_80CLK_TIMEOUT_EN, 0);
		वापस err;
	पूर्ण

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक sd_tuning_phase(काष्ठा realtek_pci_sdmmc *host,
		u8 opcode, u32 *phase_map)
अणु
	पूर्णांक err, i;
	u32 raw_phase_map = 0;

	क्रम (i = 0; i < RTSX_PHASE_MAX; i++) अणु
		err = sd_tuning_rx_cmd(host, opcode, (u8)i);
		अगर (err == 0)
			raw_phase_map |= 1 << i;
	पूर्ण

	अगर (phase_map)
		*phase_map = raw_phase_map;

	वापस 0;
पूर्ण

अटल पूर्णांक sd_tuning_rx(काष्ठा realtek_pci_sdmmc *host, u8 opcode)
अणु
	पूर्णांक err, i;
	u32 raw_phase_map[RX_TUNING_CNT] = अणु0पूर्ण, phase_map;
	u8 final_phase;

	क्रम (i = 0; i < RX_TUNING_CNT; i++) अणु
		err = sd_tuning_phase(host, opcode, &(raw_phase_map[i]));
		अगर (err < 0)
			वापस err;

		अगर (raw_phase_map[i] == 0)
			अवरोध;
	पूर्ण

	phase_map = 0xFFFFFFFF;
	क्रम (i = 0; i < RX_TUNING_CNT; i++) अणु
		dev_dbg(sdmmc_dev(host), "RX raw_phase_map[%d] = 0x%08x\n",
				i, raw_phase_map[i]);
		phase_map &= raw_phase_map[i];
	पूर्ण
	dev_dbg(sdmmc_dev(host), "RX phase_map = 0x%08x\n", phase_map);

	अगर (phase_map) अणु
		final_phase = sd_search_final_phase(host, phase_map);
		अगर (final_phase == 0xFF)
			वापस -EINVAL;

		err = sd_change_phase(host, final_phase, true);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sdio_extblock_cmd(काष्ठा mmc_command *cmd,
	काष्ठा mmc_data *data)
अणु
	वापस (cmd->opcode == SD_IO_RW_EXTENDED) && (data->blksz == 512);
पूर्ण

अटल अंतरभूत पूर्णांक sd_rw_cmd(काष्ठा mmc_command *cmd)
अणु
	वापस mmc_op_multi(cmd->opcode) ||
		(cmd->opcode == MMC_READ_SINGLE_BLOCK) ||
		(cmd->opcode == MMC_WRITE_BLOCK);
पूर्ण

अटल व्योम sd_request(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा realtek_pci_sdmmc *host = container_of(work,
			काष्ठा realtek_pci_sdmmc, work);
	काष्ठा rtsx_pcr *pcr = host->pcr;

	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;

	अचिन्हित पूर्णांक data_size = 0;
	पूर्णांक err;

	अगर (host->eject || !sd_get_cd_पूर्णांक(host)) अणु
		cmd->error = -ENOMEDIUM;
		जाओ finish;
	पूर्ण

	err = rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD);
	अगर (err) अणु
		cmd->error = err;
		जाओ finish;
	पूर्ण

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	rtsx_pci_चयन_घड़ी(pcr, host->घड़ी, host->ssc_depth,
			host->initial_mode, host->द्विगुन_clk, host->vpclk);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_SELECT, 0x07, SD_MOD_SEL);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_SHARE_MODE,
			CARD_SHARE_MASK, CARD_SHARE_48_SD);

	mutex_lock(&host->host_mutex);
	host->mrq = mrq;
	mutex_unlock(&host->host_mutex);

	अगर (mrq->data)
		data_size = data->blocks * data->blksz;

	अगर (!data_size) अणु
		sd_send_cmd_get_rsp(host, cmd);
	पूर्ण अन्यथा अगर (sd_rw_cmd(cmd) || sdio_extblock_cmd(cmd, data)) अणु
		cmd->error = sd_rw_multi(host, mrq);
		अगर (!host->using_cookie)
			sdmmc_post_req(host->mmc, host->mrq, 0);

		अगर (mmc_op_multi(cmd->opcode) && mrq->stop)
			sd_send_cmd_get_rsp(host, mrq->stop);
	पूर्ण अन्यथा अणु
		sd_normal_rw(host, mrq);
	पूर्ण

	अगर (mrq->data) अणु
		अगर (cmd->error || data->error)
			data->bytes_xfered = 0;
		अन्यथा
			data->bytes_xfered = data->blocks * data->blksz;
	पूर्ण

	mutex_unlock(&pcr->pcr_mutex);

finish:
	अगर (cmd->error) अणु
		dev_dbg(sdmmc_dev(host), "CMD %d 0x%08x error(%d)\n",
			cmd->opcode, cmd->arg, cmd->error);
	पूर्ण

	mutex_lock(&host->host_mutex);
	host->mrq = शून्य;
	mutex_unlock(&host->host_mutex);

	mmc_request_करोne(mmc, mrq);
पूर्ण

अटल व्योम sdmmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	mutex_lock(&host->host_mutex);
	host->mrq = mrq;
	mutex_unlock(&host->host_mutex);

	अगर (sd_rw_cmd(mrq->cmd) || sdio_extblock_cmd(mrq->cmd, data))
		host->using_cookie = sd_pre_dma_transfer(host, data, false);

	schedule_work(&host->work);
पूर्ण

अटल पूर्णांक sd_set_bus_width(काष्ठा realtek_pci_sdmmc *host,
		अचिन्हित अक्षर bus_width)
अणु
	पूर्णांक err = 0;
	u8 width[] = अणु
		[MMC_BUS_WIDTH_1] = SD_BUS_WIDTH_1BIT,
		[MMC_BUS_WIDTH_4] = SD_BUS_WIDTH_4BIT,
		[MMC_BUS_WIDTH_8] = SD_BUS_WIDTH_8BIT,
	पूर्ण;

	अगर (bus_width <= MMC_BUS_WIDTH_8)
		err = rtsx_pci_ग_लिखो_रेजिस्टर(host->pcr, SD_CFG1,
				0x03, width[bus_width]);

	वापस err;
पूर्ण

अटल पूर्णांक sd_घातer_on(काष्ठा realtek_pci_sdmmc *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक err;
	u32 val;
	u8 test_mode;

	अगर (host->घातer_state == SDMMC_POWER_ON)
		वापस 0;

	msleep(100);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_SELECT, 0x07, SD_MOD_SEL);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_SHARE_MODE,
			CARD_SHARE_MASK, CARD_SHARE_48_SD);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN,
			SD_CLK_EN, SD_CLK_EN);
	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_card_pull_ctl_enable(pcr, RTSX_SD_CARD);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_card_घातer_on(pcr, RTSX_SD_CARD);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, SD_OUTPUT_EN, SD_OUTPUT_EN);
	अगर (err < 0)
		वापस err;

	अगर (PCI_PID(pcr) == PID_5261) अणु
		/*
		 * If test mode is set चयन to SD Express mandatorily,
		 * this is only क्रम factory testing.
		 */
		rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS5261_FW_CFG_INFO0, &test_mode);
		अगर (test_mode & RTS5261_FW_EXPRESS_TEST_MASK) अणु
			sdmmc_init_sd_express(mmc, शून्य);
			वापस 0;
		पूर्ण
		अगर (pcr->extra_caps & EXTRA_CAPS_SD_EXPRESS)
			mmc->caps2 |= MMC_CAP2_SD_EXP | MMC_CAP2_SD_EXP_1_2V;
		/*
		 * HW पढ़ो wp status when resuming from S3/S4,
		 * and then picks SD legacy पूर्णांकerface अगर it's set
		 * in पढ़ो-only mode.
		 */
		val = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
		अगर (val & SD_WRITE_PROTECT) अणु
			pcr->extra_caps &= ~EXTRA_CAPS_SD_EXPRESS;
			mmc->caps2 &= ~(MMC_CAP2_SD_EXP | MMC_CAP2_SD_EXP_1_2V);
		पूर्ण
	पूर्ण

	host->घातer_state = SDMMC_POWER_ON;
	वापस 0;
पूर्ण

अटल पूर्णांक sd_घातer_off(काष्ठा realtek_pci_sdmmc *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;

	host->घातer_state = SDMMC_POWER_OFF;

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN, SD_CLK_EN, 0);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE, SD_OUTPUT_EN, 0);

	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_card_घातer_off(pcr, RTSX_SD_CARD);
	अगर (err < 0)
		वापस err;

	वापस rtsx_pci_card_pull_ctl_disable(pcr, RTSX_SD_CARD);
पूर्ण

अटल पूर्णांक sd_set_घातer_mode(काष्ठा realtek_pci_sdmmc *host,
		अचिन्हित अक्षर घातer_mode)
अणु
	पूर्णांक err;

	अगर (घातer_mode == MMC_POWER_OFF)
		err = sd_घातer_off(host);
	अन्यथा
		err = sd_घातer_on(host);

	वापस err;
पूर्ण

अटल पूर्णांक sd_set_timing(काष्ठा realtek_pci_sdmmc *host, अचिन्हित अक्षर timing)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err = 0;

	rtsx_pci_init_cmd(pcr);

	चयन (timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_UHS_SDR50:
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG1,
				0x0C | SD_ASYNC_FIFO_NOT_RST,
				SD_30_MODE | SD_ASYNC_FIFO_NOT_RST);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL,
				CLK_LOW_FREQ, CLK_LOW_FREQ);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_VAR_CLK0 | SD30_FIX_CLK | SAMPLE_VAR_CLK1);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL, CLK_LOW_FREQ, 0);
		अवरोध;

	हाल MMC_TIMING_MMC_DDR52:
	हाल MMC_TIMING_UHS_DDR50:
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG1,
				0x0C | SD_ASYNC_FIFO_NOT_RST,
				SD_DDR_MODE | SD_ASYNC_FIFO_NOT_RST);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL,
				CLK_LOW_FREQ, CLK_LOW_FREQ);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_VAR_CLK0 | SD30_FIX_CLK | SAMPLE_VAR_CLK1);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL, CLK_LOW_FREQ, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_PUSH_POINT_CTL,
				DDR_VAR_TX_CMD_DAT, DDR_VAR_TX_CMD_DAT);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_SAMPLE_POINT_CTL,
				DDR_VAR_RX_DAT | DDR_VAR_RX_CMD,
				DDR_VAR_RX_DAT | DDR_VAR_RX_CMD);
		अवरोध;

	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CFG1,
				0x0C, SD_20_MODE);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL,
				CLK_LOW_FREQ, CLK_LOW_FREQ);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_FIX_CLK | SD30_VAR_CLK0 | SAMPLE_VAR_CLK1);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL, CLK_LOW_FREQ, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_PUSH_POINT_CTL,
				SD20_TX_SEL_MASK, SD20_TX_14_AHEAD);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_SAMPLE_POINT_CTL,
				SD20_RX_SEL_MASK, SD20_RX_14_DELAY);
		अवरोध;

	शेष:
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				SD_CFG1, 0x0C, SD_20_MODE);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL,
				CLK_LOW_FREQ, CLK_LOW_FREQ);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_SOURCE, 0xFF,
				CRC_FIX_CLK | SD30_VAR_CLK0 | SAMPLE_VAR_CLK1);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL, CLK_LOW_FREQ, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				SD_PUSH_POINT_CTL, 0xFF, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_SAMPLE_POINT_CTL,
				SD20_RX_SEL_MASK, SD20_RX_POS_EDGE);
		अवरोध;
	पूर्ण

	err = rtsx_pci_send_cmd(pcr, 100);

	वापस err;
पूर्ण

अटल व्योम sdmmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;

	अगर (host->eject)
		वापस;

	अगर (rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD))
		वापस;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	sd_set_bus_width(host, ios->bus_width);
	sd_set_घातer_mode(host, ios->घातer_mode);
	sd_set_timing(host, ios->timing);

	host->vpclk = false;
	host->द्विगुन_clk = true;

	चयन (ios->timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_UHS_SDR50:
		host->ssc_depth = RTSX_SSC_DEPTH_2M;
		host->vpclk = true;
		host->द्विगुन_clk = false;
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_UHS_SDR25:
		host->ssc_depth = RTSX_SSC_DEPTH_1M;
		अवरोध;
	शेष:
		host->ssc_depth = RTSX_SSC_DEPTH_500K;
		अवरोध;
	पूर्ण

	host->initial_mode = (ios->घड़ी <= 1000000) ? true : false;

	host->घड़ी = ios->घड़ी;
	rtsx_pci_चयन_घड़ी(pcr, ios->घड़ी, host->ssc_depth,
			host->initial_mode, host->द्विगुन_clk, host->vpclk);

	mutex_unlock(&pcr->pcr_mutex);
पूर्ण

अटल पूर्णांक sdmmc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक ro = 0;
	u32 val;

	अगर (host->eject)
		वापस -ENOMEDIUM;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	/* Check SD mechanical ग_लिखो-protect चयन */
	val = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	dev_dbg(sdmmc_dev(host), "%s: RTSX_BIPR = 0x%08x\n", __func__, val);
	अगर (val & SD_WRITE_PROTECT)
		ro = 1;

	mutex_unlock(&pcr->pcr_mutex);

	वापस ro;
पूर्ण

अटल पूर्णांक sdmmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक cd = 0;
	u32 val;

	अगर (host->eject)
		वापस cd;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	/* Check SD card detect */
	val = rtsx_pci_card_exist(pcr);
	dev_dbg(sdmmc_dev(host), "%s: RTSX_BIPR = 0x%08x\n", __func__, val);
	अगर (val & SD_EXIST)
		cd = 1;

	mutex_unlock(&pcr->pcr_mutex);

	वापस cd;
पूर्ण

अटल पूर्णांक sd_रुको_voltage_stable_1(काष्ठा realtek_pci_sdmmc *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;
	u8 stat;

	/* Reference to Signal Voltage Switch Sequence in SD spec.
	 * Wait क्रम a period of समय so that the card can drive SD_CMD and
	 * SD_DAT[3:0] to low after sending back CMD11 response.
	 */
	mdelay(1);

	/* SD_CMD, SD_DAT[3:0] should be driven to low by card;
	 * If either one of SD_CMD,SD_DAT[3:0] is not low,
	 * पात the voltage चयन sequence;
	 */
	err = rtsx_pci_पढ़ो_रेजिस्टर(pcr, SD_BUS_STAT, &stat);
	अगर (err < 0)
		वापस err;

	अगर (stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS))
		वापस -EINVAL;

	/* Stop toggle SD घड़ी */
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_BUS_STAT,
			0xFF, SD_CLK_FORCE_STOP);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक sd_रुको_voltage_stable_2(काष्ठा realtek_pci_sdmmc *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;
	u8 stat, mask, val;

	/* Wait 1.8V output of voltage regulator in card stable */
	msleep(50);

	/* Toggle SD घड़ी again */
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_BUS_STAT, 0xFF, SD_CLK_TOGGLE_EN);
	अगर (err < 0)
		वापस err;

	/* Wait क्रम a period of समय so that the card can drive
	 * SD_DAT[3:0] to high at 1.8V
	 */
	msleep(20);

	/* SD_CMD, SD_DAT[3:0] should be pulled high by host */
	err = rtsx_pci_पढ़ो_रेजिस्टर(pcr, SD_BUS_STAT, &stat);
	अगर (err < 0)
		वापस err;

	mask = SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
		SD_DAT1_STATUS | SD_DAT0_STATUS;
	val = SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
		SD_DAT1_STATUS | SD_DAT0_STATUS;
	अगर ((stat & mask) != val) अणु
		dev_dbg(sdmmc_dev(host),
			"%s: SD_BUS_STAT = 0x%x\n", __func__, stat);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_BUS_STAT,
				SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_CLK_EN, 0xFF, 0);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_चयन_voltage(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err = 0;
	u8 voltage;

	dev_dbg(sdmmc_dev(host), "%s: signal_voltage = %d\n",
			__func__, ios->संकेत_voltage);

	अगर (host->eject)
		वापस -ENOMEDIUM;

	err = rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD);
	अगर (err)
		वापस err;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
		voltage = OUTPUT_3V3;
	अन्यथा
		voltage = OUTPUT_1V8;

	अगर (voltage == OUTPUT_1V8) अणु
		err = sd_रुको_voltage_stable_1(host);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	err = rtsx_pci_चयन_output_voltage(pcr, voltage);
	अगर (err < 0)
		जाओ out;

	अगर (voltage == OUTPUT_1V8) अणु
		err = sd_रुको_voltage_stable_2(host);
		अगर (err < 0)
			जाओ out;
	पूर्ण

out:
	/* Stop toggle SD घड़ी in idle */
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_BUS_STAT,
			SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);

	mutex_unlock(&pcr->pcr_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक sdmmc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err = 0;

	अगर (host->eject)
		वापस -ENOMEDIUM;

	err = rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD);
	अगर (err)
		वापस err;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	/* Set initial TX phase */
	चयन (mmc->ios.timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
		err = sd_change_phase(host, SDR104_TX_PHASE(pcr), false);
		अवरोध;

	हाल MMC_TIMING_UHS_SDR50:
		err = sd_change_phase(host, SDR50_TX_PHASE(pcr), false);
		अवरोध;

	हाल MMC_TIMING_UHS_DDR50:
		err = sd_change_phase(host, DDR50_TX_PHASE(pcr), false);
		अवरोध;

	शेष:
		err = 0;
	पूर्ण

	अगर (err)
		जाओ out;

	/* Tuning RX phase */
	अगर ((mmc->ios.timing == MMC_TIMING_UHS_SDR104) ||
			(mmc->ios.timing == MMC_TIMING_UHS_SDR50))
		err = sd_tuning_rx(host, opcode);
	अन्यथा अगर (mmc->ios.timing == MMC_TIMING_UHS_DDR50)
		err = sd_change_phase(host, DDR50_RX_PHASE(pcr), true);

out:
	mutex_unlock(&pcr->pcr_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक sdmmc_init_sd_express(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	u32 relink_समय;
	काष्ठा realtek_pci_sdmmc *host = mmc_priv(mmc);
	काष्ठा rtsx_pcr *pcr = host->pcr;

	/* Set relink_समय क्रम changing to PCIe card */
	relink_समय = 0x8FFF;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF01, 0xFF, relink_समय);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF02, 0xFF, relink_समय >> 8);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF03, 0x01, relink_समय >> 16);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PETXCFG, 0x80, 0x80);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG0,
		RTS5261_LDO1_OCP_THD_MASK,
		pcr->option.sd_800mA_ocp_thd);

	अगर (pcr->ops->disable_स्वतः_blink)
		pcr->ops->disable_स्वतः_blink(pcr);

	/* For PCIe/NVMe mode can't enter delink issue */
	pcr->hw_param.पूर्णांकerrupt_en &= ~(SD_INT_EN);
	rtsx_pci_ग_लिखोl(pcr, RTSX_BIER, pcr->hw_param.पूर्णांकerrupt_en);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_AUTOLOAD_CFG4,
		RTS5261_AUX_CLK_16M_EN, RTS5261_AUX_CLK_16M_EN);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_FW_CFG0,
		RTS5261_FW_ENTER_EXPRESS, RTS5261_FW_ENTER_EXPRESS);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_FW_CFG1,
		RTS5261_MCU_CLOCK_GATING, RTS5261_MCU_CLOCK_GATING);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_FW_CFG1,
		RTS5261_MCU_BUS_SEL_MASK | RTS5261_MCU_CLOCK_SEL_MASK
		| RTS5261_DRIVER_ENABLE_FW,
		RTS5261_MCU_CLOCK_SEL_16M | RTS5261_DRIVER_ENABLE_FW);
	host->eject = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops realtek_pci_sdmmc_ops = अणु
	.pre_req = sdmmc_pre_req,
	.post_req = sdmmc_post_req,
	.request = sdmmc_request,
	.set_ios = sdmmc_set_ios,
	.get_ro = sdmmc_get_ro,
	.get_cd = sdmmc_get_cd,
	.start_संकेत_voltage_चयन = sdmmc_चयन_voltage,
	.execute_tuning = sdmmc_execute_tuning,
	.init_sd_express = sdmmc_init_sd_express,
पूर्ण;

अटल व्योम init_extra_caps(काष्ठा realtek_pci_sdmmc *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा rtsx_pcr *pcr = host->pcr;

	dev_dbg(sdmmc_dev(host), "pcr->extra_caps = 0x%x\n", pcr->extra_caps);

	अगर (pcr->extra_caps & EXTRA_CAPS_SD_SDR50)
		mmc->caps |= MMC_CAP_UHS_SDR50;
	अगर (pcr->extra_caps & EXTRA_CAPS_SD_SDR104)
		mmc->caps |= MMC_CAP_UHS_SDR104;
	अगर (pcr->extra_caps & EXTRA_CAPS_SD_DDR50)
		mmc->caps |= MMC_CAP_UHS_DDR50;
	अगर (pcr->extra_caps & EXTRA_CAPS_MMC_HSDDR)
		mmc->caps |= MMC_CAP_1_8V_DDR;
	अगर (pcr->extra_caps & EXTRA_CAPS_MMC_8BIT)
		mmc->caps |= MMC_CAP_8_BIT_DATA;
	अगर (pcr->extra_caps & EXTRA_CAPS_NO_MMC)
		mmc->caps2 |= MMC_CAP2_NO_MMC;
	अगर (pcr->extra_caps & EXTRA_CAPS_SD_EXPRESS)
		mmc->caps2 |= MMC_CAP2_SD_EXP | MMC_CAP2_SD_EXP_1_2V;
पूर्ण

अटल व्योम realtek_init_host(काष्ठा realtek_pci_sdmmc *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा rtsx_pcr *pcr = host->pcr;

	mmc->f_min = 250000;
	mmc->f_max = 208000000;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED |
		MMC_CAP_MMC_HIGHSPEED | MMC_CAP_BUS_WIDTH_TEST |
		MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25;
	अगर (pcr->rtd3_en)
		mmc->caps = mmc->caps | MMC_CAP_AGGRESSIVE_PM;
	mmc->caps2 = MMC_CAP2_NO_PRESCAN_POWERUP | MMC_CAP2_FULL_PWR_CYCLE |
		MMC_CAP2_NO_SDIO;
	mmc->max_current_330 = 400;
	mmc->max_current_180 = 800;
	mmc->ops = &realtek_pci_sdmmc_ops;

	init_extra_caps(host);

	mmc->max_segs = 256;
	mmc->max_seg_size = 65536;
	mmc->max_blk_size = 512;
	mmc->max_blk_count = 65535;
	mmc->max_req_size = 524288;
पूर्ण

अटल व्योम rtsx_pci_sdmmc_card_event(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा realtek_pci_sdmmc *host = platक्रमm_get_drvdata(pdev);

	host->cookie = -1;
	mmc_detect_change(host->mmc, 0);
पूर्ण

अटल पूर्णांक rtsx_pci_sdmmc_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा realtek_pci_sdmmc *host;
	काष्ठा rtsx_pcr *pcr;
	काष्ठा pcr_handle *handle = pdev->dev.platक्रमm_data;

	अगर (!handle)
		वापस -ENXIO;

	pcr = handle->pcr;
	अगर (!pcr)
		वापस -ENXIO;

	dev_dbg(&(pdev->dev), ": Realtek PCI-E SDMMC controller found\n");

	mmc = mmc_alloc_host(माप(*host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	host->pcr = pcr;
	host->mmc = mmc;
	host->pdev = pdev;
	host->cookie = -1;
	host->घातer_state = SDMMC_POWER_OFF;
	INIT_WORK(&host->work, sd_request);
	platक्रमm_set_drvdata(pdev, host);
	pcr->slots[RTSX_SD_CARD].p_dev = pdev;
	pcr->slots[RTSX_SD_CARD].card_event = rtsx_pci_sdmmc_card_event;

	mutex_init(&host->host_mutex);

	realtek_init_host(host);

	अगर (pcr->rtd3_en) अणु
		pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 5000);
		pm_runसमय_use_स्वतःsuspend(&pdev->dev);
		pm_runसमय_enable(&pdev->dev);
	पूर्ण


	mmc_add_host(mmc);

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_sdmmc_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा realtek_pci_sdmmc *host = platक्रमm_get_drvdata(pdev);
	काष्ठा rtsx_pcr *pcr;
	काष्ठा mmc_host *mmc;

	अगर (!host)
		वापस 0;

	pcr = host->pcr;
	pcr->slots[RTSX_SD_CARD].p_dev = शून्य;
	pcr->slots[RTSX_SD_CARD].card_event = शून्य;
	mmc = host->mmc;

	अगर (pcr->rtd3_en) अणु
		pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
		pm_runसमय_disable(&pdev->dev);
	पूर्ण

	cancel_work_sync(&host->work);

	mutex_lock(&host->host_mutex);
	अगर (host->mrq) अणु
		dev_dbg(&(pdev->dev),
			"%s: Controller removed during transfer\n",
			mmc_hostname(mmc));

		rtsx_pci_complete_unfinished_transfer(pcr);

		host->mrq->cmd->error = -ENOMEDIUM;
		अगर (host->mrq->stop)
			host->mrq->stop->error = -ENOMEDIUM;
		mmc_request_करोne(mmc, host->mrq);
	पूर्ण
	mutex_unlock(&host->host_mutex);

	mmc_हटाओ_host(mmc);
	host->eject = true;

	flush_work(&host->work);

	mmc_मुक्त_host(mmc);

	dev_dbg(&(pdev->dev),
		": Realtek PCI-E SDMMC controller has been removed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id rtsx_pci_sdmmc_ids[] = अणु
	अणु
		.name = DRV_NAME_RTSX_PCI_SDMMC,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rtsx_pci_sdmmc_ids);

अटल काष्ठा platक्रमm_driver rtsx_pci_sdmmc_driver = अणु
	.probe		= rtsx_pci_sdmmc_drv_probe,
	.हटाओ		= rtsx_pci_sdmmc_drv_हटाओ,
	.id_table       = rtsx_pci_sdmmc_ids,
	.driver		= अणु
		.name	= DRV_NAME_RTSX_PCI_SDMMC,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rtsx_pci_sdmmc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wei WANG <wei_wang@realsil.com.cn>");
MODULE_DESCRIPTION("Realtek PCI-E SD/MMC Card Host Driver");
