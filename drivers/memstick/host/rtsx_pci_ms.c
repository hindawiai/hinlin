<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Realtek PCI-Express Memstick Card Interface driver
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memstick.h>
#समावेश <linux/rtsx_pci.h>
#समावेश <यंत्र/unaligned.h>

काष्ठा realtek_pci_ms अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा rtsx_pcr		*pcr;
	काष्ठा memstick_host	*msh;
	काष्ठा memstick_request	*req;

	काष्ठा mutex		host_mutex;
	काष्ठा work_काष्ठा	handle_req;

	u8			ssc_depth;
	अचिन्हित पूर्णांक		घड़ी;
	अचिन्हित अक्षर           अगरmode;
	bool			eject;
पूर्ण;

अटल अंतरभूत काष्ठा device *ms_dev(काष्ठा realtek_pci_ms *host)
अणु
	वापस &(host->pdev->dev);
पूर्ण

अटल अंतरभूत व्योम ms_clear_error(काष्ठा realtek_pci_ms *host)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(host->pcr, CARD_STOP,
			MS_STOP | MS_CLR_ERR, MS_STOP | MS_CLR_ERR);
पूर्ण

#अगर_घोषित DEBUG

अटल व्योम ms_prपूर्णांक_debug_regs(काष्ठा realtek_pci_ms *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	u16 i;
	u8 *ptr;

	/* Prपूर्णांक MS host पूर्णांकernal रेजिस्टरs */
	rtsx_pci_init_cmd(pcr);
	क्रम (i = 0xFD40; i <= 0xFD44; i++)
		rtsx_pci_add_cmd(pcr, READ_REG_CMD, i, 0, 0);
	क्रम (i = 0xFD52; i <= 0xFD69; i++)
		rtsx_pci_add_cmd(pcr, READ_REG_CMD, i, 0, 0);
	rtsx_pci_send_cmd(pcr, 100);

	ptr = rtsx_pci_get_cmd_data(pcr);
	क्रम (i = 0xFD40; i <= 0xFD44; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptr++));
	क्रम (i = 0xFD52; i <= 0xFD69; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptr++));
पूर्ण

#अन्यथा

#घोषणा ms_prपूर्णांक_debug_regs(host)

#पूर्ण_अगर

अटल पूर्णांक ms_घातer_on(काष्ठा realtek_pci_ms *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_SELECT, 0x07, MS_MOD_SEL);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_SHARE_MODE,
			CARD_SHARE_MASK, CARD_SHARE_48_MS);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN,
			MS_CLK_EN, MS_CLK_EN);
	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_card_pull_ctl_enable(pcr, RTSX_MS_CARD);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_card_घातer_on(pcr, RTSX_MS_CARD);
	अगर (err < 0)
		वापस err;

	/* Wait ms घातer stable */
	msleep(150);

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_घातer_off(काष्ठा realtek_pci_ms *host)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN, MS_CLK_EN, 0);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE, MS_OUTPUT_EN, 0);

	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_card_घातer_off(pcr, RTSX_MS_CARD);
	अगर (err < 0)
		वापस err;

	वापस rtsx_pci_card_pull_ctl_disable(pcr, RTSX_MS_CARD);
पूर्ण

अटल पूर्णांक ms_transfer_data(काष्ठा realtek_pci_ms *host, अचिन्हित अक्षर data_dir,
		u8 tpc, u8 cfg, काष्ठा scatterlist *sg)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err;
	अचिन्हित पूर्णांक length = sg->length;
	u16 sec_cnt = (u16)(length / 512);
	u8 val, trans_mode, dma_dir;
	काष्ठा memstick_dev *card = host->msh->card;
	bool pro_card = card->id.type == MEMSTICK_TYPE_PRO;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x, data_dir = %s, length = %d\n",
			__func__, tpc, (data_dir == READ) ? "READ" : "WRITE",
			length);

	अगर (data_dir == READ) अणु
		dma_dir = DMA_सूची_FROM_CARD;
		trans_mode = pro_card ? MS_TM_AUTO_READ : MS_TM_NORMAL_READ;
	पूर्ण अन्यथा अणु
		dma_dir = DMA_सूची_TO_CARD;
		trans_mode = pro_card ? MS_TM_AUTO_WRITE : MS_TM_NORMAL_WRITE;
	पूर्ण

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	अगर (pro_card) अणु
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_SECTOR_CNT_H,
				0xFF, (u8)(sec_cnt >> 8));
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_SECTOR_CNT_L,
				0xFF, (u8)sec_cnt);
	पूर्ण
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, IRQSTAT0,
			DMA_DONE_INT, DMA_DONE_INT);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC3, 0xFF, (u8)(length >> 24));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC2, 0xFF, (u8)(length >> 16));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC1, 0xFF, (u8)(length >> 8));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMATC0, 0xFF, (u8)length);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, DMACTL,
			0x03 | DMA_PACK_SIZE_MASK, dma_dir | DMA_EN | DMA_512);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, RING_BUFFER);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TRANSFER,
			0xFF, MS_TRANSFER_START | trans_mode);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, MS_TRANSFER,
			MS_TRANSFER_END, MS_TRANSFER_END);

	rtsx_pci_send_cmd_no_रुको(pcr);

	err = rtsx_pci_transfer_data(pcr, sg, 1, data_dir == READ, 10000);
	अगर (err < 0) अणु
		ms_clear_error(host);
		वापस err;
	पूर्ण

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, MS_TRANS_CFG, &val);
	अगर (pro_card) अणु
		अगर (val & (MS_INT_CMDNK | MS_INT_ERR |
				MS_CRC16_ERR | MS_RDY_TIMEOUT))
			वापस -EIO;
	पूर्ण अन्यथा अणु
		अगर (val & (MS_CRC16_ERR | MS_RDY_TIMEOUT))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ms_ग_लिखो_bytes(काष्ठा realtek_pci_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *पूर्णांक_reg)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err, i;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	अगर (!data)
		वापस -EINVAL;

	rtsx_pci_init_cmd(pcr);

	क्रम (i = 0; i < cnt; i++)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				PPBUF_BASE2 + i, 0xFF, data[i]);
	अगर (cnt % 2)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				PPBUF_BASE2 + i, 0xFF, 0xFF);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, PINGPONG_BUFFER);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TRANSFER,
			0xFF, MS_TRANSFER_START | MS_TM_WRITE_BYTES);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, MS_TRANSFER,
			MS_TRANSFER_END, MS_TRANSFER_END);
	अगर (पूर्णांक_reg)
		rtsx_pci_add_cmd(pcr, READ_REG_CMD, MS_TRANS_CFG, 0, 0);

	err = rtsx_pci_send_cmd(pcr, 5000);
	अगर (err < 0) अणु
		u8 val;

		rtsx_pci_पढ़ो_रेजिस्टर(pcr, MS_TRANS_CFG, &val);
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

	अगर (पूर्णांक_reg) अणु
		u8 *ptr = rtsx_pci_get_cmd_data(pcr) + 1;
		*पूर्णांक_reg = *ptr & 0x0F;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ms_पढ़ो_bytes(काष्ठा realtek_pci_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *पूर्णांक_reg)
अणु
	काष्ठा rtsx_pcr *pcr = host->pcr;
	पूर्णांक err, i;
	u8 *ptr;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	अगर (!data)
		वापस -EINVAL;

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DATA_SOURCE,
			0x01, PINGPONG_BUFFER);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, MS_TRANSFER,
			0xFF, MS_TRANSFER_START | MS_TM_READ_BYTES);
	rtsx_pci_add_cmd(pcr, CHECK_REG_CMD, MS_TRANSFER,
			MS_TRANSFER_END, MS_TRANSFER_END);
	क्रम (i = 0; i < cnt - 1; i++)
		rtsx_pci_add_cmd(pcr, READ_REG_CMD, PPBUF_BASE2 + i, 0, 0);
	अगर (cnt % 2)
		rtsx_pci_add_cmd(pcr, READ_REG_CMD, PPBUF_BASE2 + cnt, 0, 0);
	अन्यथा
		rtsx_pci_add_cmd(pcr, READ_REG_CMD,
				PPBUF_BASE2 + cnt - 1, 0, 0);
	अगर (पूर्णांक_reg)
		rtsx_pci_add_cmd(pcr, READ_REG_CMD, MS_TRANS_CFG, 0, 0);

	err = rtsx_pci_send_cmd(pcr, 5000);
	अगर (err < 0) अणु
		u8 val;

		rtsx_pci_पढ़ो_रेजिस्टर(pcr, MS_TRANS_CFG, &val);
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

	ptr = rtsx_pci_get_cmd_data(pcr) + 1;
	क्रम (i = 0; i < cnt; i++)
		data[i] = *ptr++;

	अगर (पूर्णांक_reg)
		*पूर्णांक_reg = *ptr & 0x0F;

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_ms_issue_cmd(काष्ठा realtek_pci_ms *host)
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
		अगर (req->data_dir == READ) अणु
			err = ms_पढ़ो_bytes(host, req->tpc, cfg,
					req->data_len, req->data, &पूर्णांक_reg);
		पूर्ण अन्यथा अणु
			err = ms_ग_लिखो_bytes(host, req->tpc, cfg,
					req->data_len, req->data, &पूर्णांक_reg);
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस err;

	अगर (req->need_card_पूर्णांक && (host->अगरmode == MEMSTICK_SERIAL)) अणु
		err = ms_पढ़ो_bytes(host, MS_TPC_GET_INT,
				NO_WAIT_INT, 1, &पूर्णांक_reg, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (req->need_card_पूर्णांक) अणु
		dev_dbg(ms_dev(host), "int_reg: 0x%02x\n", पूर्णांक_reg);

		अगर (पूर्णांक_reg & MS_INT_CMDNK)
			req->पूर्णांक_reg |= MEMSTICK_INT_CMDNAK;
		अगर (पूर्णांक_reg & MS_INT_BREQ)
			req->पूर्णांक_reg |= MEMSTICK_INT_BREQ;
		अगर (पूर्णांक_reg & MS_INT_ERR)
			req->पूर्णांक_reg |= MEMSTICK_INT_ERR;
		अगर (पूर्णांक_reg & MS_INT_CED)
			req->पूर्णांक_reg |= MEMSTICK_INT_CED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtsx_pci_ms_handle_req(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा realtek_pci_ms *host = container_of(work,
			काष्ठा realtek_pci_ms, handle_req);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	काष्ठा memstick_host *msh = host->msh;
	पूर्णांक rc;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	rtsx_pci_चयन_घड़ी(host->pcr, host->घड़ी, host->ssc_depth,
			false, true, false);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_SELECT, 0x07, MS_MOD_SEL);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_SHARE_MODE,
			CARD_SHARE_MASK, CARD_SHARE_48_MS);

	अगर (!host->req) अणु
		करो अणु
			rc = memstick_next_req(msh, &host->req);
			dev_dbg(ms_dev(host), "next req %d\n", rc);

			अगर (!rc)
				host->req->error = rtsx_pci_ms_issue_cmd(host);
		पूर्ण जबतक (!rc);
	पूर्ण

	mutex_unlock(&pcr->pcr_mutex);
पूर्ण

अटल व्योम rtsx_pci_ms_request(काष्ठा memstick_host *msh)
अणु
	काष्ठा realtek_pci_ms *host = memstick_priv(msh);

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	अगर (rtsx_pci_card_exclusive_check(host->pcr, RTSX_MS_CARD))
		वापस;

	schedule_work(&host->handle_req);
पूर्ण

अटल पूर्णांक rtsx_pci_ms_set_param(काष्ठा memstick_host *msh,
		क्रमागत memstick_param param, पूर्णांक value)
अणु
	काष्ठा realtek_pci_ms *host = memstick_priv(msh);
	काष्ठा rtsx_pcr *pcr = host->pcr;
	अचिन्हित पूर्णांक घड़ी = 0;
	u8 ssc_depth = 0;
	पूर्णांक err;

	dev_dbg(ms_dev(host), "%s: param = %d, value = %d\n",
			__func__, param, value);

	err = rtsx_pci_card_exclusive_check(host->pcr, RTSX_MS_CARD);
	अगर (err)
		वापस err;

	चयन (param) अणु
	हाल MEMSTICK_POWER:
		अगर (value == MEMSTICK_POWER_ON)
			err = ms_घातer_on(host);
		अन्यथा अगर (value == MEMSTICK_POWER_OFF)
			err = ms_घातer_off(host);
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल MEMSTICK_INTERFACE:
		अगर (value == MEMSTICK_SERIAL) अणु
			घड़ी = 19000000;
			ssc_depth = RTSX_SSC_DEPTH_500K;

			err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, MS_CFG, 0x58,
					MS_BUS_WIDTH_1 | PUSH_TIME_DEFAULT);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अगर (value == MEMSTICK_PAR4) अणु
			घड़ी = 39000000;
			ssc_depth = RTSX_SSC_DEPTH_1M;

			err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, MS_CFG,
					0x58, MS_BUS_WIDTH_4 | PUSH_TIME_ODD);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		err = rtsx_pci_चयन_घड़ी(pcr, घड़ी,
				ssc_depth, false, true, false);
		अगर (err < 0)
			वापस err;

		host->ssc_depth = ssc_depth;
		host->घड़ी = घड़ी;
		host->अगरmode = value;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक rtsx_pci_ms_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा realtek_pci_ms *host = platक्रमm_get_drvdata(pdev);
	काष्ठा memstick_host *msh = host->msh;

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	memstick_suspend_host(msh);
	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_ms_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा realtek_pci_ms *host = platक्रमm_get_drvdata(pdev);
	काष्ठा memstick_host *msh = host->msh;

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	memstick_resume_host(msh);
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_PM */

#घोषणा rtsx_pci_ms_suspend शून्य
#घोषणा rtsx_pci_ms_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम rtsx_pci_ms_card_event(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा realtek_pci_ms *host = platक्रमm_get_drvdata(pdev);

	memstick_detect_change(host->msh);
पूर्ण

अटल पूर्णांक rtsx_pci_ms_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा memstick_host *msh;
	काष्ठा realtek_pci_ms *host;
	काष्ठा rtsx_pcr *pcr;
	काष्ठा pcr_handle *handle = pdev->dev.platक्रमm_data;
	पूर्णांक rc;

	अगर (!handle)
		वापस -ENXIO;

	pcr = handle->pcr;
	अगर (!pcr)
		वापस -ENXIO;

	dev_dbg(&(pdev->dev),
			": Realtek PCI-E Memstick controller found\n");

	msh = memstick_alloc_host(माप(*host), &pdev->dev);
	अगर (!msh)
		वापस -ENOMEM;

	host = memstick_priv(msh);
	host->pcr = pcr;
	host->msh = msh;
	host->pdev = pdev;
	platक्रमm_set_drvdata(pdev, host);
	pcr->slots[RTSX_MS_CARD].p_dev = pdev;
	pcr->slots[RTSX_MS_CARD].card_event = rtsx_pci_ms_card_event;

	mutex_init(&host->host_mutex);

	INIT_WORK(&host->handle_req, rtsx_pci_ms_handle_req);
	msh->request = rtsx_pci_ms_request;
	msh->set_param = rtsx_pci_ms_set_param;
	msh->caps = MEMSTICK_CAP_PAR4;

	rc = memstick_add_host(msh);
	अगर (rc) अणु
		memstick_मुक्त_host(msh);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_ms_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा realtek_pci_ms *host = platक्रमm_get_drvdata(pdev);
	काष्ठा rtsx_pcr *pcr;
	काष्ठा memstick_host *msh;
	पूर्णांक rc;

	अगर (!host)
		वापस 0;

	pcr = host->pcr;
	pcr->slots[RTSX_MS_CARD].p_dev = शून्य;
	pcr->slots[RTSX_MS_CARD].card_event = शून्य;
	msh = host->msh;
	host->eject = true;
	cancel_work_sync(&host->handle_req);

	mutex_lock(&host->host_mutex);
	अगर (host->req) अणु
		dev_dbg(&(pdev->dev),
			"%s: Controller removed during transfer\n",
			dev_name(&msh->dev));

		rtsx_pci_complete_unfinished_transfer(pcr);

		host->req->error = -ENOMEDIUM;
		करो अणु
			rc = memstick_next_req(msh, &host->req);
			अगर (!rc)
				host->req->error = -ENOMEDIUM;
		पूर्ण जबतक (!rc);
	पूर्ण
	mutex_unlock(&host->host_mutex);

	memstick_हटाओ_host(msh);
	memstick_मुक्त_host(msh);

	dev_dbg(&(pdev->dev),
		": Realtek PCI-E Memstick controller has been removed\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device_id rtsx_pci_ms_ids[] = अणु
	अणु
		.name = DRV_NAME_RTSX_PCI_MS,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rtsx_pci_ms_ids);

अटल काष्ठा platक्रमm_driver rtsx_pci_ms_driver = अणु
	.probe		= rtsx_pci_ms_drv_probe,
	.हटाओ		= rtsx_pci_ms_drv_हटाओ,
	.id_table       = rtsx_pci_ms_ids,
	.suspend	= rtsx_pci_ms_suspend,
	.resume		= rtsx_pci_ms_resume,
	.driver		= अणु
		.name	= DRV_NAME_RTSX_PCI_MS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rtsx_pci_ms_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wei WANG <wei_wang@realsil.com.cn>");
MODULE_DESCRIPTION("Realtek PCI-E Memstick Card Host Driver");
