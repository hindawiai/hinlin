<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Realtek USB Memstick Card Interface driver
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Roger Tseng <rogerable@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/memstick.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/rtsx_usb.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <यंत्र/unaligned.h>

काष्ठा rtsx_usb_ms अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा rtsx_ucr	*ucr;
	काष्ठा memstick_host	*msh;
	काष्ठा memstick_request	*req;

	काष्ठा mutex		host_mutex;
	काष्ठा work_काष्ठा	handle_req;
	काष्ठा delayed_work	poll_card;

	u8			ssc_depth;
	अचिन्हित पूर्णांक		घड़ी;
	पूर्णांक			घातer_mode;
	अचिन्हित अक्षर           अगरmode;
	bool			eject;
	bool			प्रणाली_suspending;
पूर्ण;

अटल अंतरभूत काष्ठा device *ms_dev(काष्ठा rtsx_usb_ms *host)
अणु
	वापस &(host->pdev->dev);
पूर्ण

अटल अंतरभूत व्योम ms_clear_error(काष्ठा rtsx_usb_ms *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, CARD_STOP,
				  MS_STOP | MS_CLR_ERR,
				  MS_STOP | MS_CLR_ERR);

	rtsx_usb_clear_dma_err(ucr);
	rtsx_usb_clear_fsm_err(ucr);
पूर्ण

#अगर_घोषित DEBUG

अटल व्योम ms_prपूर्णांक_debug_regs(काष्ठा rtsx_usb_ms *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	u16 i;
	u8 *ptr;

	/* Prपूर्णांक MS host पूर्णांकernal रेजिस्टरs */
	rtsx_usb_init_cmd(ucr);

	/* MS_CFG to MS_INT_REG */
	क्रम (i = 0xFD40; i <= 0xFD44; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, i, 0, 0);

	/* CARD_SHARE_MODE to CARD_GPIO */
	क्रम (i = 0xFD51; i <= 0xFD56; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, i, 0, 0);

	/* CARD_PULL_CTLx */
	क्रम (i = 0xFD60; i <= 0xFD65; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, i, 0, 0);

	/* CARD_DATA_SOURCE, CARD_SELECT, CARD_CLK_EN, CARD_PWR_CTL */
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_DATA_SOURCE, 0, 0);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_SELECT, 0, 0);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_CLK_EN, 0, 0);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_PWR_CTL, 0, 0);

	rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	rtsx_usb_get_rsp(ucr, 21, 100);

	ptr = ucr->rsp_buf;
	क्रम (i = 0xFD40; i <= 0xFD44; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptr++));
	क्रम (i = 0xFD51; i <= 0xFD56; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptr++));
	क्रम (i = 0xFD60; i <= 0xFD65; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptr++));

	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CARD_DATA_SOURCE, *(ptr++));
	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CARD_SELECT, *(ptr++));
	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CARD_CLK_EN, *(ptr++));
	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CARD_PWR_CTL, *(ptr++));
पूर्ण

#अन्यथा

अटल व्योम ms_prपूर्णांक_debug_regs(काष्ठा rtsx_usb_ms *host)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक ms_pull_ctl_disable_lqfp48(काष्ठा rtsx_ucr *ucr)
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

अटल पूर्णांक ms_pull_ctl_disable_qfn24(काष्ठा rtsx_ucr *ucr)
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

अटल पूर्णांक ms_pull_ctl_enable_lqfp48(काष्ठा rtsx_ucr *ucr)
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

अटल पूर्णांक ms_pull_ctl_enable_qfn24(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0x65);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0x95);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF, 0x59);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक ms_घातer_on(काष्ठा rtsx_usb_ms *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;

	dev_dbg(ms_dev(host), "%s\n", __func__);

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_SELECT, 0x07, MS_MOD_SEL);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_SHARE_MODE,
			CARD_SHARE_MASK, CARD_SHARE_MS);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_EN,
			MS_CLK_EN, MS_CLK_EN);
	err = rtsx_usb_send_cmd(ucr, MODE_C, 100);
	अगर (err < 0)
		वापस err;

	अगर (CHECK_PKG(ucr, LQFP48))
		err = ms_pull_ctl_enable_lqfp48(ucr);
	अन्यथा
		err = ms_pull_ctl_enable_qfn24(ucr);
	अगर (err < 0)
		वापस err;

	err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, CARD_PWR_CTL,
			POWER_MASK, PARTIAL_POWER_ON);
	अगर (err)
		वापस err;

	usleep_range(800, 1000);

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PWR_CTL,
			POWER_MASK, POWER_ON);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

अटल पूर्णांक ms_घातer_off(काष्ठा rtsx_usb_ms *host)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;

	dev_dbg(ms_dev(host), "%s\n", __func__);

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_CLK_EN, MS_CLK_EN, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_OE, MS_OUTPUT_EN, 0);

	err = rtsx_usb_send_cmd(ucr, MODE_C, 100);
	अगर (err < 0)
		वापस err;

	अगर (CHECK_PKG(ucr, LQFP48))
		वापस ms_pull_ctl_disable_lqfp48(ucr);

	वापस ms_pull_ctl_disable_qfn24(ucr);
पूर्ण

अटल पूर्णांक ms_transfer_data(काष्ठा rtsx_usb_ms *host, अचिन्हित अक्षर data_dir,
		u8 tpc, u8 cfg, काष्ठा scatterlist *sg)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	अचिन्हित पूर्णांक length = sg->length;
	u16 sec_cnt = (u16)(length / 512);
	u8 trans_mode, dma_dir, flag;
	अचिन्हित पूर्णांक pipe;
	काष्ठा memstick_dev *card = host->msh->card;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x, data_dir = %s, length = %d\n",
			__func__, tpc, (data_dir == READ) ? "READ" : "WRITE",
			length);

	अगर (data_dir == READ) अणु
		flag = MODE_Cसूची;
		dma_dir = DMA_सूची_FROM_CARD;
		अगर (card->id.type != MEMSTICK_TYPE_PRO)
			trans_mode = MS_TM_NORMAL_READ;
		अन्यथा
			trans_mode = MS_TM_AUTO_READ;
		pipe = usb_rcvbulkpipe(ucr->pusb_dev, EP_BULK_IN);
	पूर्ण अन्यथा अणु
		flag = MODE_CDOR;
		dma_dir = DMA_सूची_TO_CARD;
		अगर (card->id.type != MEMSTICK_TYPE_PRO)
			trans_mode = MS_TM_NORMAL_WRITE;
		अन्यथा
			trans_mode = MS_TM_AUTO_WRITE;
		pipe = usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT);
	पूर्ण

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	अगर (card->id.type == MEMSTICK_TYPE_PRO) अणु
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_SECTOR_CNT_H,
				0xFF, (u8)(sec_cnt >> 8));
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_SECTOR_CNT_L,
				0xFF, (u8)sec_cnt);
	पूर्ण
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC3,
			0xFF, (u8)(length >> 24));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC2,
			0xFF, (u8)(length >> 16));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC1,
			0xFF, (u8)(length >> 8));
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_TC0, 0xFF,
			(u8)length);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MC_DMA_CTL,
			0x03 | DMA_PACK_SIZE_MASK, dma_dir | DMA_EN | DMA_512);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, RING_BUFFER);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TRANSFER,
			0xFF, MS_TRANSFER_START | trans_mode);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, MS_TRANSFER,
			MS_TRANSFER_END, MS_TRANSFER_END);

	err = rtsx_usb_send_cmd(ucr, flag | STAGE_MS_STATUS, 100);
	अगर (err)
		वापस err;

	err = rtsx_usb_transfer_data(ucr, pipe, sg, length,
			1, शून्य, 10000);
	अगर (err)
		जाओ err_out;

	err = rtsx_usb_get_rsp(ucr, 3, 15000);
	अगर (err)
		जाओ err_out;

	अगर (ucr->rsp_buf[0] & MS_TRANSFER_ERR ||
	    ucr->rsp_buf[1] & (MS_CRC16_ERR | MS_RDY_TIMEOUT)) अणु
		err = -EIO;
		जाओ err_out;
	पूर्ण
	वापस 0;
err_out:
	ms_clear_error(host);
	वापस err;
पूर्ण

अटल पूर्णांक ms_ग_लिखो_bytes(काष्ठा rtsx_usb_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *पूर्णांक_reg)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err, i;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	rtsx_usb_init_cmd(ucr);

	क्रम (i = 0; i < cnt; i++)
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				PPBUF_BASE2 + i, 0xFF, data[i]);

	अगर (cnt % 2)
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				PPBUF_BASE2 + i, 0xFF, 0xFF);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, PINGPONG_BUFFER);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TRANSFER,
			0xFF, MS_TRANSFER_START | MS_TM_WRITE_BYTES);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, MS_TRANSFER,
			MS_TRANSFER_END, MS_TRANSFER_END);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, MS_TRANS_CFG, 0, 0);

	err = rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	अगर (err)
		वापस err;

	err = rtsx_usb_get_rsp(ucr, 2, 5000);
	अगर (err || (ucr->rsp_buf[0] & MS_TRANSFER_ERR)) अणु
		u8 val;

		rtsx_usb_ep0_पढ़ो_रेजिस्टर(ucr, MS_TRANS_CFG, &val);
		dev_dbg(ms_dev(host), "MS_TRANS_CFG: 0x%02x\n", val);

		अगर (पूर्णांक_reg)
			*पूर्णांक_reg = val & 0x0F;

		ms_prपूर्णांक_debug_regs(host);

		ms_clear_error(host);

		अगर (!(tpc & 0x08)) अणु
			अगर (val & MS_CRC16_ERR)
				वापस -EIO;
		पूर्ण अन्यथा अणु
			अगर (!(val & 0x80)) अणु
				अगर (val & (MS_INT_ERR | MS_INT_CMDNK))
					वापस -EIO;
			पूर्ण
		पूर्ण

		वापस -ETIMEDOUT;
	पूर्ण

	अगर (पूर्णांक_reg)
		*पूर्णांक_reg = ucr->rsp_buf[1] & 0x0F;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_पढ़ो_bytes(काष्ठा rtsx_usb_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *पूर्णांक_reg)
अणु
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err, i;
	u8 *ptr;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, PINGPONG_BUFFER);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, MS_TRANSFER,
			0xFF, MS_TRANSFER_START | MS_TM_READ_BYTES);
	rtsx_usb_add_cmd(ucr, CHECK_REG_CMD, MS_TRANSFER,
			MS_TRANSFER_END, MS_TRANSFER_END);
	क्रम (i = 0; i < cnt - 1; i++)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, PPBUF_BASE2 + i, 0, 0);
	अगर (cnt % 2)
		rtsx_usb_add_cmd(ucr, READ_REG_CMD, PPBUF_BASE2 + cnt, 0, 0);
	अन्यथा
		rtsx_usb_add_cmd(ucr, READ_REG_CMD,
				PPBUF_BASE2 + cnt - 1, 0, 0);

	rtsx_usb_add_cmd(ucr, READ_REG_CMD, MS_TRANS_CFG, 0, 0);

	err = rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	अगर (err)
		वापस err;

	err = rtsx_usb_get_rsp(ucr, cnt + 2, 5000);
	अगर (err || (ucr->rsp_buf[0] & MS_TRANSFER_ERR)) अणु
		u8 val;

		rtsx_usb_ep0_पढ़ो_रेजिस्टर(ucr, MS_TRANS_CFG, &val);
		dev_dbg(ms_dev(host), "MS_TRANS_CFG: 0x%02x\n", val);

		अगर (पूर्णांक_reg && (host->अगरmode != MEMSTICK_SERIAL))
			*पूर्णांक_reg = val & 0x0F;

		ms_prपूर्णांक_debug_regs(host);

		ms_clear_error(host);

		अगर (!(tpc & 0x08)) अणु
			अगर (val & MS_CRC16_ERR)
				वापस -EIO;
		पूर्ण अन्यथा अणु
			अगर (!(val & 0x80)) अणु
				अगर (val & (MS_INT_ERR | MS_INT_CMDNK))
					वापस -EIO;
			पूर्ण
		पूर्ण

		वापस -ETIMEDOUT;
	पूर्ण

	ptr = ucr->rsp_buf + 1;
	क्रम (i = 0; i < cnt; i++)
		data[i] = *ptr++;


	अगर (पूर्णांक_reg && (host->अगरmode != MEMSTICK_SERIAL))
		*पूर्णांक_reg = *ptr & 0x0F;

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_ms_issue_cmd(काष्ठा rtsx_usb_ms *host)
अणु
	काष्ठा memstick_request *req = host->req;
	पूर्णांक err = 0;
	u8 cfg = 0, पूर्णांक_reg;

	dev_dbg(ms_dev(host), "%s\n", __func__);

	अगर (req->need_card_पूर्णांक) अणु
		अगर (host->अगरmode != MEMSTICK_SERIAL)
			cfg = WAIT_INT;
	पूर्ण

	अगर (req->दीर्घ_data) अणु
		err = ms_transfer_data(host, req->data_dir,
				req->tpc, cfg, &(req->sg));
	पूर्ण अन्यथा अणु
		अगर (req->data_dir == READ)
			err = ms_पढ़ो_bytes(host, req->tpc, cfg,
					req->data_len, req->data, &पूर्णांक_reg);
		अन्यथा
			err = ms_ग_लिखो_bytes(host, req->tpc, cfg,
					req->data_len, req->data, &पूर्णांक_reg);
	पूर्ण
	अगर (err < 0)
		वापस err;

	अगर (req->need_card_पूर्णांक) अणु
		अगर (host->अगरmode == MEMSTICK_SERIAL) अणु
			err = ms_पढ़ो_bytes(host, MS_TPC_GET_INT,
					NO_WAIT_INT, 1, &req->पूर्णांक_reg, शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु

			अगर (पूर्णांक_reg & MS_INT_CMDNK)
				req->पूर्णांक_reg |= MEMSTICK_INT_CMDNAK;
			अगर (पूर्णांक_reg & MS_INT_BREQ)
				req->पूर्णांक_reg |= MEMSTICK_INT_BREQ;
			अगर (पूर्णांक_reg & MS_INT_ERR)
				req->पूर्णांक_reg |= MEMSTICK_INT_ERR;
			अगर (पूर्णांक_reg & MS_INT_CED)
				req->पूर्णांक_reg |= MEMSTICK_INT_CED;
		पूर्ण
		dev_dbg(ms_dev(host), "int_reg: 0x%02x\n", req->पूर्णांक_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtsx_usb_ms_handle_req(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtsx_usb_ms *host = container_of(work,
			काष्ठा rtsx_usb_ms, handle_req);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	काष्ठा memstick_host *msh = host->msh;
	पूर्णांक rc;

	अगर (!host->req) अणु
		pm_runसमय_get_sync(ms_dev(host));
		करो अणु
			rc = memstick_next_req(msh, &host->req);
			dev_dbg(ms_dev(host), "next req %d\n", rc);

			अगर (!rc) अणु
				mutex_lock(&ucr->dev_mutex);

				अगर (rtsx_usb_card_exclusive_check(ucr,
							RTSX_USB_MS_CARD))
					host->req->error = -EIO;
				अन्यथा
					host->req->error =
						rtsx_usb_ms_issue_cmd(host);

				mutex_unlock(&ucr->dev_mutex);

				dev_dbg(ms_dev(host), "req result %d\n",
						host->req->error);
			पूर्ण
		पूर्ण जबतक (!rc);
		pm_runसमय_put_sync(ms_dev(host));
	पूर्ण

पूर्ण

अटल व्योम rtsx_usb_ms_request(काष्ठा memstick_host *msh)
अणु
	काष्ठा rtsx_usb_ms *host = memstick_priv(msh);

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	अगर (!host->eject)
		schedule_work(&host->handle_req);
पूर्ण

अटल पूर्णांक rtsx_usb_ms_set_param(काष्ठा memstick_host *msh,
		क्रमागत memstick_param param, पूर्णांक value)
अणु
	काष्ठा rtsx_usb_ms *host = memstick_priv(msh);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	अचिन्हित पूर्णांक घड़ी = 0;
	u8 ssc_depth = 0;
	पूर्णांक err;

	dev_dbg(ms_dev(host), "%s: param = %d, value = %d\n",
			__func__, param, value);

	pm_runसमय_get_sync(ms_dev(host));
	mutex_lock(&ucr->dev_mutex);

	err = rtsx_usb_card_exclusive_check(ucr, RTSX_USB_MS_CARD);
	अगर (err)
		जाओ out;

	चयन (param) अणु
	हाल MEMSTICK_POWER:
		अगर (value == host->घातer_mode)
			अवरोध;

		अगर (value == MEMSTICK_POWER_ON) अणु
			pm_runसमय_get_noresume(ms_dev(host));
			err = ms_घातer_on(host);
			अगर (err)
				pm_runसमय_put_noidle(ms_dev(host));
		पूर्ण अन्यथा अगर (value == MEMSTICK_POWER_OFF) अणु
			err = ms_घातer_off(host);
			अगर (!err)
				pm_runसमय_put_noidle(ms_dev(host));
		पूर्ण अन्यथा
			err = -EINVAL;
		अगर (!err)
			host->घातer_mode = value;
		अवरोध;

	हाल MEMSTICK_INTERFACE:
		अगर (value == MEMSTICK_SERIAL) अणु
			घड़ी = 19000000;
			ssc_depth = SSC_DEPTH_512K;
			err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, MS_CFG, 0x5A,
				       MS_BUS_WIDTH_1 | PUSH_TIME_DEFAULT);
			अगर (err < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (value == MEMSTICK_PAR4) अणु
			घड़ी = 39000000;
			ssc_depth = SSC_DEPTH_1M;

			err = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, MS_CFG, 0x5A,
					MS_BUS_WIDTH_4 | PUSH_TIME_ODD |
					MS_NO_CHECK_INT);
			अगर (err < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = rtsx_usb_चयन_घड़ी(ucr, घड़ी,
				ssc_depth, false, true, false);
		अगर (err < 0) अणु
			dev_dbg(ms_dev(host), "switch clock failed\n");
			अवरोध;
		पूर्ण

		host->ssc_depth = ssc_depth;
		host->घड़ी = घड़ी;
		host->अगरmode = value;
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
out:
	mutex_unlock(&ucr->dev_mutex);
	pm_runसमय_put_sync(ms_dev(host));

	/* घातer-on delay */
	अगर (param == MEMSTICK_POWER && value == MEMSTICK_POWER_ON) अणु
		usleep_range(10000, 12000);

		अगर (!host->eject)
			schedule_delayed_work(&host->poll_card, 100);
	पूर्ण

	dev_dbg(ms_dev(host), "%s: return = %d\n", __func__, err);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rtsx_usb_ms_suspend(काष्ठा device *dev)
अणु
	काष्ठा rtsx_usb_ms *host = dev_get_drvdata(dev);
	काष्ठा memstick_host *msh = host->msh;

	/* Since we use rtsx_usb's resume callback to runसमय resume its
	 * children to implement remote wakeup संकेतing, this causes
	 * rtsx_usb_ms' runसमय resume callback runs after its suspend
	 * callback:
	 * rtsx_usb_ms_suspend()
	 * rtsx_usb_resume()
	 *   -> rtsx_usb_ms_runसमय_resume()
	 *     -> memstick_detect_change()
	 *
	 * rtsx_usb_suspend()
	 *
	 * To aव्योम this, skip runसमय resume/suspend अगर प्रणाली suspend is
	 * underway.
	 */

	host->प्रणाली_suspending = true;
	memstick_suspend_host(msh);

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_ms_resume(काष्ठा device *dev)
अणु
	काष्ठा rtsx_usb_ms *host = dev_get_drvdata(dev);
	काष्ठा memstick_host *msh = host->msh;

	memstick_resume_host(msh);
	host->प्रणाली_suspending = false;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rtsx_usb_ms_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rtsx_usb_ms *host = dev_get_drvdata(dev);

	अगर (host->प्रणाली_suspending)
		वापस 0;

	अगर (host->msh->card || host->घातer_mode != MEMSTICK_POWER_OFF)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_ms_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rtsx_usb_ms *host = dev_get_drvdata(dev);


	अगर (host->प्रणाली_suspending)
		वापस 0;

	memstick_detect_change(host->msh);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops rtsx_usb_ms_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rtsx_usb_ms_suspend, rtsx_usb_ms_resume)
	SET_RUNTIME_PM_OPS(rtsx_usb_ms_runसमय_suspend, rtsx_usb_ms_runसमय_resume, शून्य)
पूर्ण;


अटल व्योम rtsx_usb_ms_poll_card(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtsx_usb_ms *host = container_of(work, काष्ठा rtsx_usb_ms,
			poll_card.work);
	काष्ठा rtsx_ucr *ucr = host->ucr;
	पूर्णांक err;
	u8 val;

	अगर (host->eject || host->घातer_mode != MEMSTICK_POWER_ON)
		वापस;

	pm_runसमय_get_sync(ms_dev(host));
	mutex_lock(&ucr->dev_mutex);

	/* Check pending MS card changes */
	err = rtsx_usb_पढ़ो_रेजिस्टर(ucr, CARD_INT_PEND, &val);
	अगर (err) अणु
		mutex_unlock(&ucr->dev_mutex);
		जाओ poll_again;
	पूर्ण

	/* Clear the pending */
	rtsx_usb_ग_लिखो_रेजिस्टर(ucr, CARD_INT_PEND,
			XD_INT | MS_INT | SD_INT,
			XD_INT | MS_INT | SD_INT);

	mutex_unlock(&ucr->dev_mutex);

	अगर (val & MS_INT) अणु
		dev_dbg(ms_dev(host), "MS slot change detected\n");
		memstick_detect_change(host->msh);
	पूर्ण

poll_again:
	pm_runसमय_put_sync(ms_dev(host));

	अगर (!host->eject && host->घातer_mode == MEMSTICK_POWER_ON)
		schedule_delayed_work(&host->poll_card, 100);
पूर्ण

अटल पूर्णांक rtsx_usb_ms_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा memstick_host *msh;
	काष्ठा rtsx_usb_ms *host;
	काष्ठा rtsx_ucr *ucr;
	पूर्णांक err;

	ucr = usb_get_पूर्णांकfdata(to_usb_पूर्णांकerface(pdev->dev.parent));
	अगर (!ucr)
		वापस -ENXIO;

	dev_dbg(&(pdev->dev),
			"Realtek USB Memstick controller found\n");

	msh = memstick_alloc_host(माप(*host), &pdev->dev);
	अगर (!msh)
		वापस -ENOMEM;

	host = memstick_priv(msh);
	host->ucr = ucr;
	host->msh = msh;
	host->pdev = pdev;
	host->घातer_mode = MEMSTICK_POWER_OFF;
	platक्रमm_set_drvdata(pdev, host);

	mutex_init(&host->host_mutex);
	INIT_WORK(&host->handle_req, rtsx_usb_ms_handle_req);

	INIT_DELAYED_WORK(&host->poll_card, rtsx_usb_ms_poll_card);

	msh->request = rtsx_usb_ms_request;
	msh->set_param = rtsx_usb_ms_set_param;
	msh->caps = MEMSTICK_CAP_PAR4;

	pm_runसमय_get_noresume(ms_dev(host));
	pm_runसमय_set_active(ms_dev(host));
	pm_runसमय_enable(ms_dev(host));

	err = memstick_add_host(msh);
	अगर (err)
		जाओ err_out;

	pm_runसमय_put(ms_dev(host));

	वापस 0;
err_out:
	memstick_मुक्त_host(msh);
	pm_runसमय_disable(ms_dev(host));
	pm_runसमय_put_noidle(ms_dev(host));
	वापस err;
पूर्ण

अटल पूर्णांक rtsx_usb_ms_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtsx_usb_ms *host = platक्रमm_get_drvdata(pdev);
	काष्ठा memstick_host *msh = host->msh;
	पूर्णांक err;

	host->eject = true;
	cancel_work_sync(&host->handle_req);

	mutex_lock(&host->host_mutex);
	अगर (host->req) अणु
		dev_dbg(ms_dev(host),
			"%s: Controller removed during transfer\n",
			dev_name(&msh->dev));
		host->req->error = -ENOMEDIUM;
		करो अणु
			err = memstick_next_req(msh, &host->req);
			अगर (!err)
				host->req->error = -ENOMEDIUM;
		पूर्ण जबतक (!err);
	पूर्ण
	mutex_unlock(&host->host_mutex);

	memstick_हटाओ_host(msh);
	memstick_मुक्त_host(msh);

	/* Balance possible unbalanced usage count
	 * e.g. unconditional module removal
	 */
	अगर (pm_runसमय_active(ms_dev(host)))
		pm_runसमय_put(ms_dev(host));

	pm_runसमय_disable(ms_dev(host));
	platक्रमm_set_drvdata(pdev, शून्य);

	dev_dbg(ms_dev(host),
		": Realtek USB Memstick controller has been removed\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device_id rtsx_usb_ms_ids[] = अणु
	अणु
		.name = "rtsx_usb_ms",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rtsx_usb_ms_ids);

अटल काष्ठा platक्रमm_driver rtsx_usb_ms_driver = अणु
	.probe		= rtsx_usb_ms_drv_probe,
	.हटाओ		= rtsx_usb_ms_drv_हटाओ,
	.id_table       = rtsx_usb_ms_ids,
	.driver		= अणु
		.name	= "rtsx_usb_ms",
		.pm	= &rtsx_usb_ms_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rtsx_usb_ms_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Roger Tseng <rogerable@realtek.com>");
MODULE_DESCRIPTION("Realtek USB Memstick Card Host Driver");
