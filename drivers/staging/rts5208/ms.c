<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "rtsx.h"
#समावेश "ms.h"

अटल अंतरभूत व्योम ms_set_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;

	ms_card->err_code = err_code;
पूर्ण

अटल अंतरभूत पूर्णांक ms_check_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;

	वापस (ms_card->err_code == err_code);
पूर्ण

अटल पूर्णांक ms_parse_err_code(काष्ठा rtsx_chip *chip)
अणु
	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक ms_transfer_tpc(काष्ठा rtsx_chip *chip, u8 trans_mode,
			   u8 tpc, u8 cnt, u8 cfg)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	u8 *ptr;

	dev_dbg(rtsx_dev(chip), "%s: tpc = 0x%x\n", __func__, tpc);

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANSFER,
		     0xFF, MS_TRANSFER_START | trans_mode);
	rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANSFER,
		     MS_TRANSFER_END, MS_TRANSFER_END);

	rtsx_add_cmd(chip, READ_REG_CMD, MS_TRANS_CFG, 0, 0);

	retval = rtsx_send_cmd(chip, MS_CARD, 5000);
	अगर (retval < 0) अणु
		rtsx_clear_ms_error(chip);
		ms_set_err_code(chip, MS_TO_ERROR);
		वापस ms_parse_err_code(chip);
	पूर्ण

	ptr = rtsx_get_cmd_data(chip) + 1;

	अगर (!(tpc & 0x08)) अणु		/* Read Packet */
		अगर (*ptr & MS_CRC16_ERR) अणु
			ms_set_err_code(chip, MS_CRC16_ERROR);
			वापस ms_parse_err_code(chip);
		पूर्ण
	पूर्ण अन्यथा अणु			/* Write Packet */
		अगर (CHK_MSPRO(ms_card) && !(*ptr & 0x80)) अणु
			अगर (*ptr & (MS_INT_ERR | MS_INT_CMDNK)) अणु
				ms_set_err_code(chip, MS_CMD_NK);
				वापस ms_parse_err_code(chip);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (*ptr & MS_RDY_TIMEOUT) अणु
		rtsx_clear_ms_error(chip);
		ms_set_err_code(chip, MS_TO_ERROR);
		वापस ms_parse_err_code(chip);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_transfer_data(काष्ठा rtsx_chip *chip, u8 trans_mode,
			    u8 tpc, u16 sec_cnt, u8 cfg, bool mode_2k,
			    पूर्णांक use_sg, व्योम *buf, पूर्णांक buf_len)
अणु
	पूर्णांक retval;
	u8 val, err_code = 0;
	क्रमागत dma_data_direction dir;

	अगर (!buf || !buf_len)
		वापस STATUS_FAIL;

	अगर (trans_mode == MS_TM_AUTO_READ) अणु
		dir = DMA_FROM_DEVICE;
		err_code = MS_FLASH_READ_ERROR;
	पूर्ण अन्यथा अगर (trans_mode == MS_TM_AUTO_WRITE) अणु
		dir = DMA_TO_DEVICE;
		err_code = MS_FLASH_WRITE_ERROR;
	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_add_cmd(chip, WRITE_REG_CMD,
		     MS_SECTOR_CNT_H, 0xFF, (u8)(sec_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_SECTOR_CNT_L, 0xFF, (u8)sec_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);

	अगर (mode_2k) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD,
			     MS_CFG, MS_2K_SECTOR_MODE, MS_2K_SECTOR_MODE);
	पूर्ण अन्यथा अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_CFG, MS_2K_SECTOR_MODE, 0);
	पूर्ण

	trans_dma_enable(dir, chip, sec_cnt * 512, DMA_512);

	rtsx_add_cmd(chip, WRITE_REG_CMD,
		     MS_TRANSFER, 0xFF, MS_TRANSFER_START | trans_mode);
	rtsx_add_cmd(chip, CHECK_REG_CMD,
		     MS_TRANSFER, MS_TRANSFER_END, MS_TRANSFER_END);

	rtsx_send_cmd_no_रुको(chip);

	retval = rtsx_transfer_data(chip, MS_CARD, buf, buf_len,
				    use_sg, dir, chip->mspro_समयout);
	अगर (retval < 0) अणु
		ms_set_err_code(chip, err_code);
		अगर (retval == -ETIMEDOUT)
			retval = STATUS_TIMEDOUT;
		अन्यथा
			retval = STATUS_FAIL;

		वापस retval;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
	अगर (retval)
		वापस retval;

	अगर (val & (MS_INT_CMDNK | MS_INT_ERR | MS_CRC16_ERR | MS_RDY_TIMEOUT))
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_ग_लिखो_bytes(काष्ठा rtsx_chip *chip,
			  u8 tpc, u8 cnt, u8 cfg, u8 *data, पूर्णांक data_len)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;

	अगर (!data || (data_len < cnt))
		वापस STATUS_ERROR;

	rtsx_init_cmd(chip);

	क्रम (i = 0; i < cnt; i++) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD,
			     PPBUF_BASE2 + i, 0xFF, data[i]);
	पूर्ण
	अगर (cnt % 2)
		rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2 + i, 0xFF, 0xFF);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD,
		     MS_TRANSFER, 0xFF, MS_TRANSFER_START | MS_TM_WRITE_BYTES);
	rtsx_add_cmd(chip, CHECK_REG_CMD,
		     MS_TRANSFER, MS_TRANSFER_END, MS_TRANSFER_END);

	retval = rtsx_send_cmd(chip, MS_CARD, 5000);
	अगर (retval < 0) अणु
		u8 val = 0;

		rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
		dev_dbg(rtsx_dev(chip), "MS_TRANS_CFG: 0x%02x\n", val);

		rtsx_clear_ms_error(chip);

		अगर (!(tpc & 0x08)) अणु
			अगर (val & MS_CRC16_ERR) अणु
				ms_set_err_code(chip, MS_CRC16_ERROR);
				वापस ms_parse_err_code(chip);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (CHK_MSPRO(ms_card) && !(val & 0x80)) अणु
				अगर (val & (MS_INT_ERR | MS_INT_CMDNK)) अणु
					ms_set_err_code(chip, MS_CMD_NK);
					वापस ms_parse_err_code(chip);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (val & MS_RDY_TIMEOUT) अणु
			ms_set_err_code(chip, MS_TO_ERROR);
			वापस ms_parse_err_code(chip);
		पूर्ण

		ms_set_err_code(chip, MS_TO_ERROR);
		वापस ms_parse_err_code(chip);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_पढ़ो_bytes(काष्ठा rtsx_chip *chip,
			 u8 tpc, u8 cnt, u8 cfg, u8 *data, पूर्णांक data_len)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 *ptr;

	अगर (!data)
		वापस STATUS_ERROR;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANSFER, 0xFF,
		     MS_TRANSFER_START | MS_TM_READ_BYTES);
	rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANSFER,
		     MS_TRANSFER_END, MS_TRANSFER_END);

	क्रम (i = 0; i < data_len - 1; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + i, 0, 0);

	अगर (data_len % 2)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + data_len, 0, 0);
	अन्यथा
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + data_len - 1,
			     0, 0);

	retval = rtsx_send_cmd(chip, MS_CARD, 5000);
	अगर (retval < 0) अणु
		u8 val = 0;

		rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
		rtsx_clear_ms_error(chip);

		अगर (!(tpc & 0x08)) अणु
			अगर (val & MS_CRC16_ERR) अणु
				ms_set_err_code(chip, MS_CRC16_ERROR);
				वापस ms_parse_err_code(chip);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (CHK_MSPRO(ms_card) && !(val & 0x80)) अणु
				अगर (val & (MS_INT_ERR | MS_INT_CMDNK)) अणु
					ms_set_err_code(chip, MS_CMD_NK);
					वापस ms_parse_err_code(chip);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (val & MS_RDY_TIMEOUT) अणु
			ms_set_err_code(chip, MS_TO_ERROR);
			वापस ms_parse_err_code(chip);
		पूर्ण

		ms_set_err_code(chip, MS_TO_ERROR);
		वापस ms_parse_err_code(chip);
	पूर्ण

	ptr = rtsx_get_cmd_data(chip) + 1;

	क्रम (i = 0; i < data_len; i++)
		data[i] = ptr[i];

	अगर ((tpc == PRO_READ_SHORT_DATA) && (data_len == 8)) अणु
		dev_dbg(rtsx_dev(chip), "Read format progress:\n");
		prपूर्णांक_hex_dump_bytes(KBUILD_MODNAME ": ", DUMP_PREFIX_NONE, ptr,
				     cnt);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_set_rw_reg_addr(काष्ठा rtsx_chip *chip, u8 पढ़ो_start,
			      u8 पढ़ो_cnt, u8 ग_लिखो_start, u8 ग_लिखो_cnt)
अणु
	पूर्णांक retval, i;
	u8 data[4];

	data[0] = पढ़ो_start;
	data[1] = पढ़ो_cnt;
	data[2] = ग_लिखो_start;
	data[3] = ग_लिखो_cnt;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, SET_RW_REG_ADRS, 4,
					NO_WAIT_INT, data, 4);
		अगर (retval == STATUS_SUCCESS)
			वापस STATUS_SUCCESS;
		rtsx_clear_ms_error(chip);
	पूर्ण

	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक ms_send_cmd(काष्ठा rtsx_chip *chip, u8 cmd, u8 cfg)
अणु
	u8 data[2];

	data[0] = cmd;
	data[1] = 0;

	वापस ms_ग_लिखो_bytes(chip, PRO_SET_CMD, 1, cfg, data, 1);
पूर्ण

अटल पूर्णांक ms_set_init_para(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;

	अगर (CHK_HG8BIT(ms_card)) अणु
		अगर (chip->asic_code)
			ms_card->ms_घड़ी = chip->asic_ms_hg_clk;
		अन्यथा
			ms_card->ms_घड़ी = chip->fpga_ms_hg_clk;

	पूर्ण अन्यथा अगर (CHK_MSPRO(ms_card) || CHK_MS4BIT(ms_card)) अणु
		अगर (chip->asic_code)
			ms_card->ms_घड़ी = chip->asic_ms_4bit_clk;
		अन्यथा
			ms_card->ms_घड़ी = chip->fpga_ms_4bit_clk;

	पूर्ण अन्यथा अणु
		अगर (chip->asic_code)
			ms_card->ms_घड़ी = chip->asic_ms_1bit_clk;
		अन्यथा
			ms_card->ms_घड़ी = chip->fpga_ms_1bit_clk;
	पूर्ण

	retval = चयन_घड़ी(chip, ms_card->ms_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = select_card(chip, MS_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_चयन_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;

	retval = select_card(chip, MS_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = चयन_घड़ी(chip, ms_card->ms_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_pull_ctl_disable(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	अगर (CHECK_PID(chip, 0x5208)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL1, 0xFF,
					     MS_D1_PD | MS_D2_PD | MS_CLK_PD |
					     MS_D6_PD);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL2, 0xFF,
					     MS_D3_PD | MS_D0_PD | MS_BS_PD |
					     XD_D4_PD);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL3, 0xFF,
					     MS_D7_PD | XD_CE_PD | XD_CLE_PD |
					     XD_CD_PU);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL4, 0xFF,
					     XD_RDY_PD | SD_D3_PD | SD_D2_PD |
					     XD_ALE_PD);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL5, 0xFF,
					     MS_INS_PU | SD_WP_PD | SD_CD_PU |
					     SD_CMD_PD);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL6, 0xFF,
					     MS_D5_PD | MS_D4_PD);
		अगर (retval)
			वापस retval;

	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		अगर (CHECK_BARO_PKG(chip, QFN)) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL1,
						     0xFF, 0x55);
			अगर (retval)
				वापस retval;

			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL2,
						     0xFF, 0x55);
			अगर (retval)
				वापस retval;

			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL3,
						     0xFF, 0x4B);
			अगर (retval)
				वापस retval;

			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL4,
						     0xFF, 0x69);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_pull_ctl_enable(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	rtsx_init_cmd(chip);

	अगर (CHECK_PID(chip, 0x5208)) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF,
			     MS_D1_PD | MS_D2_PD | MS_CLK_NP | MS_D6_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF,
			     MS_D3_PD | MS_D0_PD | MS_BS_NP | XD_D4_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF,
			     MS_D7_PD | XD_CE_PD | XD_CLE_PD | XD_CD_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF,
			     XD_RDY_PD | SD_D3_PD | SD_D2_PD | XD_ALE_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF,
			     MS_INS_PU | SD_WP_PD | SD_CD_PU | SD_CMD_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		अगर (CHECK_BARO_PKG(chip, QFN)) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL1, 0xFF, 0x55);
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL2, 0xFF, 0x45);
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL3, 0xFF, 0x4B);
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL4, 0xFF, 0x29);
		पूर्ण
	पूर्ण

	retval = rtsx_send_cmd(chip, MS_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_prepare_reset(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	u8 oc_mask = 0;

	ms_card->ms_type = 0;
	ms_card->check_ms_flow = 0;
	ms_card->चयन_8bit_fail = 0;
	ms_card->delay_ग_लिखो.delay_ग_लिखो_flag = 0;

	ms_card->pro_under_क्रमmatting = 0;

	retval = ms_घातer_off_card3v3(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (!chip->ft2_fast_mode)
		रुको_समयout(250);

	retval = enable_card_घड़ी(chip, MS_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (chip->asic_code) अणु
		retval = ms_pull_ctl_enable(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL,
					     FPGA_MS_PULL_CTL_BIT | 0x20, 0);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (!chip->ft2_fast_mode) अणु
		retval = card_घातer_on(chip, MS_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		रुको_समयout(150);

#अगर_घोषित SUPPORT_OCP
		अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN))
			oc_mask = MS_OC_NOW | MS_OC_EVER;
		अन्यथा
			oc_mask = SD_OC_NOW | SD_OC_EVER;

		अगर (chip->ocp_stat & oc_mask) अणु
			dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			वापस STATUS_FAIL;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, MS_OUTPUT_EN,
				     MS_OUTPUT_EN);
	अगर (retval)
		वापस retval;

	अगर (chip->asic_code) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, 0xFF,
					     SAMPLE_TIME_RISING |
					     PUSH_TIME_DEFAULT |
					     NO_EXTEND_TOGGLE |
					     MS_BUS_WIDTH_1);
		अगर (retval)
			वापस retval;

	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, 0xFF,
					     SAMPLE_TIME_FALLING |
					     PUSH_TIME_DEFAULT |
					     NO_EXTEND_TOGGLE |
					     MS_BUS_WIDTH_1);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_TRANS_CFG, 0xFF,
				     NO_WAIT_INT | NO_AUTO_READ_INT_REG);
	अगर (retval)
		वापस retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, MS_STOP | MS_CLR_ERR,
				     MS_STOP | MS_CLR_ERR);
	अगर (retval)
		वापस retval;

	retval = ms_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_identअगरy_media_type(काष्ठा rtsx_chip *chip, पूर्णांक चयन_8bit_bus)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 val;

	retval = ms_set_rw_reg_addr(chip, PRO_STATUS_REG, 6, SYSTEM_PARAM, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_transfer_tpc(chip, MS_TM_READ_BYTES, READ_REG,
					 6, NO_WAIT_INT);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2 + 2, &val);
	अगर (retval)
		वापस retval;

	dev_dbg(rtsx_dev(chip), "Type register: 0x%x\n", val);
	अगर (val != 0x01) अणु
		अगर (val != 0x02)
			ms_card->check_ms_flow = 1;

		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2 + 4, &val);
	अगर (retval)
		वापस retval;

	dev_dbg(rtsx_dev(chip), "Category register: 0x%x\n", val);
	अगर (val != 0) अणु
		ms_card->check_ms_flow = 1;
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2 + 5, &val);
	अगर (retval)
		वापस retval;

	dev_dbg(rtsx_dev(chip), "Class register: 0x%x\n", val);
	अगर (val == 0) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2, &val);
		अगर (retval)
			वापस retval;

		अगर (val & WRT_PRTCT)
			chip->card_wp |= MS_CARD;
		अन्यथा
			chip->card_wp &= ~MS_CARD;

	पूर्ण अन्यथा अगर ((val == 0x01) || (val == 0x02) || (val == 0x03)) अणु
		chip->card_wp |= MS_CARD;
	पूर्ण अन्यथा अणु
		ms_card->check_ms_flow = 1;
		वापस STATUS_FAIL;
	पूर्ण

	ms_card->ms_type |= TYPE_MSPRO;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2 + 3, &val);
	अगर (retval)
		वापस retval;

	dev_dbg(rtsx_dev(chip), "IF Mode register: 0x%x\n", val);
	अगर (val == 0) अणु
		ms_card->ms_type &= 0x0F;
	पूर्ण अन्यथा अगर (val == 7) अणु
		अगर (चयन_8bit_bus)
			ms_card->ms_type |= MS_HG;
		अन्यथा
			ms_card->ms_type &= 0x0F;

	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_confirm_cpu_startup(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval, i, k;
	u8 val;

	/* Confirm CPU StartUp */
	k = 0;
	करो अणु
		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			ms_set_err_code(chip, MS_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
			retval = ms_पढ़ो_bytes(chip, GET_INT, 1,
					       NO_WAIT_INT, &val, 1);
			अगर (retval == STATUS_SUCCESS)
				अवरोध;
		पूर्ण
		अगर (i == MS_MAX_RETRY_COUNT)
			वापस STATUS_FAIL;

		अगर (k > 100)
			वापस STATUS_FAIL;

		k++;
		रुको_समयout(100);
	पूर्ण जबतक (!(val & INT_REG_CED));

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	अगर (val & INT_REG_ERR) अणु
		अगर (val & INT_REG_CMDNK)
			chip->card_wp |= (MS_CARD);
		अन्यथा
			वापस STATUS_FAIL;
	पूर्ण
	/* --  end confirm CPU startup */

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_चयन_parallel_bus(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval, i;
	u8 data[2];

	data[0] = PARALLEL_4BIT_IF;
	data[1] = 0;
	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 1, NO_WAIT_INT,
					data, 2);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_चयन_8bit_bus(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 data[2];

	data[0] = PARALLEL_8BIT_IF;
	data[1] = 0;
	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 1,
					NO_WAIT_INT, data, 2);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, 0x98,
				     MS_BUS_WIDTH_8 | SAMPLE_TIME_FALLING);
	अगर (retval)
		वापस retval;

	ms_card->ms_type |= MS_8BIT;
	retval = ms_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_transfer_tpc(chip, MS_TM_READ_BYTES, GET_INT,
					 1, NO_WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_pro_reset_flow(काष्ठा rtsx_chip *chip, पूर्णांक चयन_8bit_bus)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;

	क्रम (i = 0; i < 3; i++) अणु
		retval = ms_prepare_reset(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_identअगरy_media_type(chip, चयन_8bit_bus);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_confirm_cpu_startup(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_चयन_parallel_bus(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
				ms_set_err_code(chip, MS_NO_CARD);
				वापस STATUS_FAIL;
			पूर्ण
			जारी;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	/* Switch MS-PRO पूर्णांकo Parallel mode */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, 0x18, MS_BUS_WIDTH_4);
	अगर (retval)
		वापस retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, PUSH_TIME_ODD,
				     PUSH_TIME_ODD);
	अगर (retval)
		वापस retval;

	retval = ms_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	/* If MSPro HG Card, We shall try to चयन to 8-bit bus */
	अगर (CHK_MSHG(ms_card) && chip->support_ms_8bit && चयन_8bit_bus) अणु
		retval = ms_चयन_8bit_bus(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			ms_card->चयन_8bit_fail = 1;
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

#अगर_घोषित XC_POWERCLASS
अटल पूर्णांक msxc_change_घातer(काष्ठा rtsx_chip *chip, u8 mode)
अणु
	पूर्णांक retval;
	u8 buf[6];

	ms_cleanup_work(chip);

	retval = ms_set_rw_reg_addr(chip, 0, 0, PRO_DATA_COUNT1, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	buf[0] = 0;
	buf[1] = mode;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	buf[5] = 0;

	retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_REG, 6, NO_WAIT_INT, buf, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_send_cmd(chip, XC_CHG_POWER, WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, buf);
	अगर (retval)
		वापस retval;

	अगर (buf[0] & (MS_INT_CMDNK | MS_INT_ERR))
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ms_पढ़ो_attribute_info(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 val, *buf, class_code, device_type, sub_class, data[16];
	u16 total_blk = 0, blk_size = 0;
#अगर_घोषित SUPPORT_MSXC
	u32 xc_total_blk = 0, xc_blk_size = 0;
#पूर्ण_अगर
	u32 sys_info_addr = 0, sys_info_size;
#अगर_घोषित SUPPORT_PCGL_1P18
	u32 model_name_addr = 0, model_name_size;
	पूर्णांक found_sys_info = 0, found_model_name = 0;
#पूर्ण_अगर

	retval = ms_set_rw_reg_addr(chip, PRO_INT_REG, 2, PRO_SYSTEM_PARAM, 7);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_MS8BIT(ms_card))
		data[0] = PARALLEL_8BIT_IF;
	अन्यथा
		data[0] = PARALLEL_4BIT_IF;

	data[1] = 0;

	data[2] = 0x40;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_REG, 7, NO_WAIT_INT,
					data, 8);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	buf = kदो_स्मृति(64 * 512, GFP_KERNEL);
	अगर (!buf)
		वापस STATUS_ERROR;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_send_cmd(chip, PRO_READ_ATRB, WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			जारी;

		retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
		अगर (retval != STATUS_SUCCESS) अणु
			kमुक्त(buf);
			वापस STATUS_FAIL;
		पूर्ण
		अगर (!(val & MS_INT_BREQ)) अणु
			kमुक्त(buf);
			वापस STATUS_FAIL;
		पूर्ण
		retval = ms_transfer_data(chip, MS_TM_AUTO_READ,
					  PRO_READ_LONG_DATA, 0x40, WAIT_INT,
					  0, 0, buf, 64 * 512);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;

		rtsx_clear_ms_error(chip);
	पूर्ण
	अगर (retval != STATUS_SUCCESS) अणु
		kमुक्त(buf);
		वापस STATUS_FAIL;
	पूर्ण

	i = 0;
	करो अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
		अगर (retval != STATUS_SUCCESS) अणु
			kमुक्त(buf);
			वापस STATUS_FAIL;
		पूर्ण

		अगर ((val & MS_INT_CED) || !(val & MS_INT_BREQ))
			अवरोध;

		retval = ms_transfer_tpc(chip, MS_TM_NORMAL_READ,
					 PRO_READ_LONG_DATA, 0, WAIT_INT);
		अगर (retval != STATUS_SUCCESS) अणु
			kमुक्त(buf);
			वापस STATUS_FAIL;
		पूर्ण

		i++;
	पूर्ण जबतक (i < 1024);

	अगर ((buf[0] != 0xa5) && (buf[1] != 0xc3)) अणु
		/* Signature code is wrong */
		kमुक्त(buf);
		वापस STATUS_FAIL;
	पूर्ण

	अगर ((buf[4] < 1) || (buf[4] > 12)) अणु
		kमुक्त(buf);
		वापस STATUS_FAIL;
	पूर्ण

	क्रम (i = 0; i < buf[4]; i++) अणु
		पूर्णांक cur_addr_off = 16 + i * 12;

#अगर_घोषित SUPPORT_MSXC
		अगर ((buf[cur_addr_off + 8] == 0x10) ||
		    (buf[cur_addr_off + 8] == 0x13)) अणु
#अन्यथा
		अगर (buf[cur_addr_off + 8] == 0x10) अणु
#पूर्ण_अगर
			sys_info_addr = ((u32)buf[cur_addr_off + 0] << 24) |
				((u32)buf[cur_addr_off + 1] << 16) |
				((u32)buf[cur_addr_off + 2] << 8) |
				buf[cur_addr_off + 3];
			sys_info_size = ((u32)buf[cur_addr_off + 4] << 24) |
				((u32)buf[cur_addr_off + 5] << 16) |
				((u32)buf[cur_addr_off + 6] << 8) |
				buf[cur_addr_off + 7];
			dev_dbg(rtsx_dev(chip), "sys_info_addr = 0x%x, sys_info_size = 0x%x\n",
				sys_info_addr, sys_info_size);
			अगर (sys_info_size != 96)  अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (sys_info_addr < 0x1A0) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण
			अगर ((sys_info_size + sys_info_addr) > 0x8000) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

#अगर_घोषित SUPPORT_MSXC
			अगर (buf[cur_addr_off + 8] == 0x13)
				ms_card->ms_type |= MS_XC;
#पूर्ण_अगर
#अगर_घोषित SUPPORT_PCGL_1P18
			found_sys_info = 1;
#अन्यथा
			अवरोध;
#पूर्ण_अगर
		पूर्ण
#अगर_घोषित SUPPORT_PCGL_1P18
		अगर (buf[cur_addr_off + 8] == 0x15) अणु
			model_name_addr = ((u32)buf[cur_addr_off + 0] << 24) |
				((u32)buf[cur_addr_off + 1] << 16) |
				((u32)buf[cur_addr_off + 2] << 8) |
				buf[cur_addr_off + 3];
			model_name_size = ((u32)buf[cur_addr_off + 4] << 24) |
				((u32)buf[cur_addr_off + 5] << 16) |
				((u32)buf[cur_addr_off + 6] << 8) |
				buf[cur_addr_off + 7];
			dev_dbg(rtsx_dev(chip), "model_name_addr = 0x%x, model_name_size = 0x%x\n",
				model_name_addr, model_name_size);
			अगर (model_name_size != 48)  अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (model_name_addr < 0x1A0) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण
			अगर ((model_name_size + model_name_addr) > 0x8000) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

			found_model_name = 1;
		पूर्ण

		अगर (found_sys_info && found_model_name)
			अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (i == buf[4]) अणु
		kमुक्त(buf);
		वापस STATUS_FAIL;
	पूर्ण

	class_code =  buf[sys_info_addr + 0];
	device_type = buf[sys_info_addr + 56];
	sub_class = buf[sys_info_addr + 46];
#अगर_घोषित SUPPORT_MSXC
	अगर (CHK_MSXC(ms_card)) अणु
		xc_total_blk = ((u32)buf[sys_info_addr + 6] << 24) |
				((u32)buf[sys_info_addr + 7] << 16) |
				((u32)buf[sys_info_addr + 8] << 8) |
				buf[sys_info_addr + 9];
		xc_blk_size = ((u32)buf[sys_info_addr + 32] << 24) |
				((u32)buf[sys_info_addr + 33] << 16) |
				((u32)buf[sys_info_addr + 34] << 8) |
				buf[sys_info_addr + 35];
		dev_dbg(rtsx_dev(chip), "xc_total_blk = 0x%x, xc_blk_size = 0x%x\n",
			xc_total_blk, xc_blk_size);
	पूर्ण अन्यथा अणु
		total_blk = ((u16)buf[sys_info_addr + 6] << 8) |
			buf[sys_info_addr + 7];
		blk_size = ((u16)buf[sys_info_addr + 2] << 8) |
			buf[sys_info_addr + 3];
		dev_dbg(rtsx_dev(chip), "total_blk = 0x%x, blk_size = 0x%x\n",
			total_blk, blk_size);
	पूर्ण
#अन्यथा
	total_blk = ((u16)buf[sys_info_addr + 6] << 8) | buf[sys_info_addr + 7];
	blk_size = ((u16)buf[sys_info_addr + 2] << 8) | buf[sys_info_addr + 3];
	dev_dbg(rtsx_dev(chip), "total_blk = 0x%x, blk_size = 0x%x\n",
		total_blk, blk_size);
#पूर्ण_अगर

	dev_dbg(rtsx_dev(chip), "class_code = 0x%x, device_type = 0x%x, sub_class = 0x%x\n",
		class_code, device_type, sub_class);

	स_नकल(ms_card->raw_sys_info, buf + sys_info_addr, 96);
#अगर_घोषित SUPPORT_PCGL_1P18
	स_नकल(ms_card->raw_model_name, buf + model_name_addr, 48);
#पूर्ण_अगर

	kमुक्त(buf);

#अगर_घोषित SUPPORT_MSXC
	अगर (CHK_MSXC(ms_card)) अणु
		अगर (class_code != 0x03)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		अगर (class_code != 0x02)
			वापस STATUS_FAIL;
	पूर्ण
#अन्यथा
	अगर (class_code != 0x02)
		वापस STATUS_FAIL;
#पूर्ण_अगर

	अगर (device_type != 0x00) अणु
		अगर ((device_type == 0x01) || (device_type == 0x02) ||
		    (device_type == 0x03)) अणु
			chip->card_wp |= MS_CARD;
		पूर्ण अन्यथा अणु
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	अगर (sub_class & 0xC0)
		वापस STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "class_code: 0x%x, device_type: 0x%x, sub_class: 0x%x\n",
		class_code, device_type, sub_class);

#अगर_घोषित SUPPORT_MSXC
	अगर (CHK_MSXC(ms_card)) अणु
		chip->capacity[chip->card2lun[MS_CARD]] =
			ms_card->capacity = xc_total_blk * xc_blk_size;
	पूर्ण अन्यथा अणु
		chip->capacity[chip->card2lun[MS_CARD]] =
			ms_card->capacity = total_blk * blk_size;
	पूर्ण
#अन्यथा
	ms_card->capacity = total_blk * blk_size;
	chip->capacity[chip->card2lun[MS_CARD]] = ms_card->capacity;
#पूर्ण_अगर

	वापस STATUS_SUCCESS;
पूर्ण

#अगर_घोषित SUPPORT_MAGIC_GATE
अटल पूर्णांक mg_set_tpc_para_sub(काष्ठा rtsx_chip *chip,
			       पूर्णांक type, u8 mg_entry_num);
#पूर्ण_अगर

अटल पूर्णांक reset_ms_pro(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
#अगर_घोषित XC_POWERCLASS
	u8 change_घातer_class;

	अगर (chip->ms_घातer_class_en & 0x02)
		change_घातer_class = 2;
	अन्यथा अगर (chip->ms_घातer_class_en & 0x01)
		change_घातer_class = 1;
	अन्यथा
		change_घातer_class = 0;
#पूर्ण_अगर

#अगर_घोषित XC_POWERCLASS
retry:
#पूर्ण_अगर
	retval = ms_pro_reset_flow(chip, 1);
	अगर (retval != STATUS_SUCCESS) अणु
		अगर (ms_card->चयन_8bit_fail) अणु
			retval = ms_pro_reset_flow(chip, 0);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण अन्यथा अणु
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = ms_पढ़ो_attribute_info(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

#अगर_घोषित XC_POWERCLASS
	अगर (CHK_HG8BIT(ms_card))
		change_घातer_class = 0;

	अगर (change_घातer_class && CHK_MSXC(ms_card)) अणु
		u8 घातer_class_en = chip->ms_घातer_class_en;

		dev_dbg(rtsx_dev(chip), "power_class_en = 0x%x\n",
			घातer_class_en);
		dev_dbg(rtsx_dev(chip), "change_power_class = %d\n",
			change_घातer_class);

		अगर (change_घातer_class)
			घातer_class_en &= (1 << (change_घातer_class - 1));
		अन्यथा
			घातer_class_en = 0;

		अगर (घातer_class_en) अणु
			u8 घातer_class_mode =
				(ms_card->raw_sys_info[46] & 0x18) >> 3;
			dev_dbg(rtsx_dev(chip), "power_class_mode = 0x%x",
				घातer_class_mode);
			अगर (change_घातer_class > घातer_class_mode)
				change_घातer_class = घातer_class_mode;
			अगर (change_घातer_class) अणु
				retval = msxc_change_घातer(chip,
							   change_घातer_class);
				अगर (retval != STATUS_SUCCESS) अणु
					change_घातer_class--;
					जाओ retry;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित SUPPORT_MAGIC_GATE
	retval = mg_set_tpc_para_sub(chip, 0, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;
#पूर्ण_अगर

	अगर (CHK_HG8BIT(ms_card))
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 8;
	अन्यथा
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 4;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_पढ़ो_status_reg(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 val[2];

	retval = ms_set_rw_reg_addr(chip, STATUS_REG0, 2, 0, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_पढ़ो_bytes(chip, READ_REG, 2, NO_WAIT_INT, val, 2);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (val[1] & (STS_UCDT | STS_UCEX | STS_UCFG)) अणु
		ms_set_err_code(chip, MS_FLASH_READ_ERROR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_पढ़ो_extra_data(काष्ठा rtsx_chip *chip,
			      u16 block_addr, u8 page_num, u8 *buf, पूर्णांक buf_len)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 val, data[10];

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_MS4BIT(ms_card)) अणु
		/* Parallel पूर्णांकerface */
		data[0] = 0x88;
	पूर्ण अन्यथा अणु
		/* Serial पूर्णांकerface */
		data[0] = 0x80;
	पूर्ण
	data[1] = 0;
	data[2] = (u8)(block_addr >> 8);
	data[3] = (u8)block_addr;
	data[4] = 0x40;
	data[5] = page_num;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 6, NO_WAIT_INT,
					data, 6);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_send_cmd(chip, BLOCK_READ, WAIT_INT);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);
	retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (val & INT_REG_CMDNK) अणु
		ms_set_err_code(chip, MS_CMD_NK);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (val & INT_REG_CED) अणु
		अगर (val & INT_REG_ERR) अणु
			retval = ms_पढ़ो_status_reg(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG,
						    MS_EXTRA_SIZE, SYSTEM_PARAM,
						    6);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = ms_पढ़ो_bytes(chip, READ_REG, MS_EXTRA_SIZE, NO_WAIT_INT,
			       data, MS_EXTRA_SIZE);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (buf && buf_len) अणु
		अगर (buf_len > MS_EXTRA_SIZE)
			buf_len = MS_EXTRA_SIZE;
		स_नकल(buf, data, buf_len);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_ग_लिखो_extra_data(काष्ठा rtsx_chip *chip, u16 block_addr,
			       u8 page_num, u8 *buf, पूर्णांक buf_len)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 val, data[16];

	अगर (!buf || (buf_len < MS_EXTRA_SIZE))
		वापस STATUS_FAIL;

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, 6 + MS_EXTRA_SIZE);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	अन्यथा
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(block_addr >> 8);
	data[3] = (u8)block_addr;
	data[4] = 0x40;
	data[5] = page_num;

	क्रम (i = 6; i < MS_EXTRA_SIZE + 6; i++)
		data[i] = buf[i - 6];

	retval = ms_ग_लिखो_bytes(chip, WRITE_REG, (6 + MS_EXTRA_SIZE),
				NO_WAIT_INT, data, 16);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_send_cmd(chip, BLOCK_WRITE, WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);
	retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (val & INT_REG_CMDNK) अणु
		ms_set_err_code(chip, MS_CMD_NK);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (val & INT_REG_CED) अणु
		अगर (val & INT_REG_ERR) अणु
			ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_पढ़ो_page(काष्ठा rtsx_chip *chip, u16 block_addr, u8 page_num)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	u8 val, data[6];

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	अन्यथा
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(block_addr >> 8);
	data[3] = (u8)block_addr;
	data[4] = 0x20;
	data[5] = page_num;

	retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 6, NO_WAIT_INT, data, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_send_cmd(chip, BLOCK_READ, WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);
	retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (val & INT_REG_CMDNK) अणु
		ms_set_err_code(chip, MS_CMD_NK);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (val & INT_REG_CED) अणु
		अगर (val & INT_REG_ERR) अणु
			अगर (!(val & INT_REG_BREQ)) अणु
				ms_set_err_code(chip,  MS_FLASH_READ_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
			retval = ms_पढ़ो_status_reg(chip);
			अगर (retval != STATUS_SUCCESS)
				ms_set_err_code(chip,  MS_FLASH_WRITE_ERROR);

		पूर्ण अन्यथा अणु
			अगर (!(val & INT_REG_BREQ)) अणु
				ms_set_err_code(chip, MS_BREQ_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण
	पूर्ण

	retval = ms_transfer_tpc(chip, MS_TM_NORMAL_READ, READ_PAGE_DATA,
				 0, NO_WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (ms_check_err_code(chip, MS_FLASH_WRITE_ERROR))
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_set_bad_block(काष्ठा rtsx_chip *chip, u16 phy_blk)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	u8 val, data[8], extra[MS_EXTRA_SIZE];

	retval = ms_पढ़ो_extra_data(chip, phy_blk, 0, extra, MS_EXTRA_SIZE);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, 7);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);

	अगर (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	अन्यथा
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(phy_blk >> 8);
	data[3] = (u8)phy_blk;
	data[4] = 0x80;
	data[5] = 0;
	data[6] = extra[0] & 0x7F;
	data[7] = 0xFF;

	retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 7, NO_WAIT_INT, data, 7);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_send_cmd(chip, BLOCK_WRITE, WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);
	retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (val & INT_REG_CMDNK) अणु
		ms_set_err_code(chip, MS_CMD_NK);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (val & INT_REG_CED) अणु
		अगर (val & INT_REG_ERR) अणु
			ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_erase_block(काष्ठा rtsx_chip *chip, u16 phy_blk)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i = 0;
	u8 val, data[6];

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);

	अगर (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	अन्यथा
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(phy_blk >> 8);
	data[3] = (u8)phy_blk;
	data[4] = 0;
	data[5] = 0;

	retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 6, NO_WAIT_INT, data, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

ERASE_RTY:
	retval = ms_send_cmd(chip, BLOCK_ERASE, WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);
	retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (val & INT_REG_CMDNK) अणु
		अगर (i < 3) अणु
			i++;
			जाओ ERASE_RTY;
		पूर्ण

		ms_set_err_code(chip, MS_CMD_NK);
		ms_set_bad_block(chip, phy_blk);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (val & INT_REG_CED) अणु
		अगर (val & INT_REG_ERR) अणु
			ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल व्योम ms_set_page_status(u16 log_blk, u8 type, u8 *extra, पूर्णांक extra_len)
अणु
	अगर (!extra || (extra_len < MS_EXTRA_SIZE))
		वापस;

	स_रखो(extra, 0xFF, MS_EXTRA_SIZE);

	अगर (type == set_PS_NG) अणु
		/* set page status as 1:NG,and block status keep 1:OK */
		extra[0] = 0xB8;
	पूर्ण अन्यथा अणु
		/* set page status as 0:Data Error,and block status keep 1:OK */
		extra[0] = 0x98;
	पूर्ण

	extra[2] = (u8)(log_blk >> 8);
	extra[3] = (u8)log_blk;
पूर्ण

अटल पूर्णांक ms_init_page(काष्ठा rtsx_chip *chip, u16 phy_blk, u16 log_blk,
			u8 start_page, u8 end_page)
अणु
	पूर्णांक retval;
	u8 extra[MS_EXTRA_SIZE], i;

	स_रखो(extra, 0xff, MS_EXTRA_SIZE);

	extra[0] = 0xf8;	/* Block, page OK, data erased */
	extra[1] = 0xff;
	extra[2] = (u8)(log_blk >> 8);
	extra[3] = (u8)log_blk;

	क्रम (i = start_page; i < end_page; i++) अणु
		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			ms_set_err_code(chip, MS_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = ms_ग_लिखो_extra_data(chip, phy_blk, i,
					     extra, MS_EXTRA_SIZE);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_copy_page(काष्ठा rtsx_chip *chip, u16 old_blk, u16 new_blk,
			u16 log_blk, u8 start_page, u8 end_page)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	bool uncorrect_flag = false;
	पूर्णांक retval, rty_cnt;
	u8 extra[MS_EXTRA_SIZE], val, i, j, data[16];

	dev_dbg(rtsx_dev(chip), "Copy page from 0x%x to 0x%x, logical block is 0x%x\n",
		old_blk, new_blk, log_blk);
	dev_dbg(rtsx_dev(chip), "start_page = %d, end_page = %d\n",
		start_page, end_page);

	retval = ms_पढ़ो_extra_data(chip, new_blk, 0, extra, MS_EXTRA_SIZE);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_पढ़ो_status_reg(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2, &val);
	अगर (retval)
		वापस retval;

	अगर (val & BUF_FULL) अणु
		retval = ms_send_cmd(chip, CLEAR_BUF, WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (!(val & INT_REG_CED)) अणु
			ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	क्रम (i = start_page; i < end_page; i++) अणु
		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			ms_set_err_code(chip, MS_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = ms_पढ़ो_extra_data(chip, old_blk, i, extra,
					    MS_EXTRA_SIZE);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG,
					    MS_EXTRA_SIZE, SYSTEM_PARAM, 6);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		ms_set_err_code(chip, MS_NO_ERROR);

		अगर (CHK_MS4BIT(ms_card))
			data[0] = 0x88;
		अन्यथा
			data[0] = 0x80;

		data[1] = 0;
		data[2] = (u8)(old_blk >> 8);
		data[3] = (u8)old_blk;
		data[4] = 0x20;
		data[5] = i;

		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 6, NO_WAIT_INT,
					data, 6);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_send_cmd(chip, BLOCK_READ, WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		ms_set_err_code(chip, MS_NO_ERROR);
		retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (val & INT_REG_CMDNK) अणु
			ms_set_err_code(chip, MS_CMD_NK);
			वापस STATUS_FAIL;
		पूर्ण

		अगर (val & INT_REG_CED) अणु
			अगर (val & INT_REG_ERR) अणु
				retval = ms_पढ़ो_status_reg(chip);
				अगर (retval != STATUS_SUCCESS) अणु
					uncorrect_flag = true;
					dev_dbg(rtsx_dev(chip), "Uncorrectable error\n");
				पूर्ण अन्यथा अणु
					uncorrect_flag = false;
				पूर्ण

				retval = ms_transfer_tpc(chip,
							 MS_TM_NORMAL_READ,
							 READ_PAGE_DATA,
							 0, NO_WAIT_INT);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;

				अगर (uncorrect_flag) अणु
					ms_set_page_status(log_blk, set_PS_NG,
							   extra,
							   MS_EXTRA_SIZE);
					अगर (i == 0)
						extra[0] &= 0xEF;

					ms_ग_लिखो_extra_data(chip, old_blk, i,
							    extra,
							    MS_EXTRA_SIZE);
					dev_dbg(rtsx_dev(chip), "page %d : extra[0] = 0x%x\n",
						i, extra[0]);
					MS_SET_BAD_BLOCK_FLG(ms_card);

					ms_set_page_status(log_blk,
							   set_PS_error, extra,
							   MS_EXTRA_SIZE);
					ms_ग_लिखो_extra_data(chip, new_blk, i,
							    extra,
							    MS_EXTRA_SIZE);
					जारी;
				पूर्ण

				क्रम (rty_cnt = 0; rty_cnt < MS_MAX_RETRY_COUNT;
				     rty_cnt++) अणु
					retval = ms_transfer_tpc(
						chip,
						MS_TM_NORMAL_WRITE,
						WRITE_PAGE_DATA,
						0, NO_WAIT_INT);
					अगर (retval == STATUS_SUCCESS)
						अवरोध;
				पूर्ण
				अगर (rty_cnt == MS_MAX_RETRY_COUNT)
					वापस STATUS_FAIL;
			पूर्ण

			अगर (!(val & INT_REG_BREQ)) अणु
				ms_set_err_code(chip, MS_BREQ_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
					    SYSTEM_PARAM, (6 + MS_EXTRA_SIZE));

		ms_set_err_code(chip, MS_NO_ERROR);

		अगर (CHK_MS4BIT(ms_card))
			data[0] = 0x88;
		अन्यथा
			data[0] = 0x80;

		data[1] = 0;
		data[2] = (u8)(new_blk >> 8);
		data[3] = (u8)new_blk;
		data[4] = 0x20;
		data[5] = i;

		अगर ((extra[0] & 0x60) != 0x60)
			data[6] = extra[0];
		अन्यथा
			data[6] = 0xF8;

		data[6 + 1] = 0xFF;
		data[6 + 2] = (u8)(log_blk >> 8);
		data[6 + 3] = (u8)log_blk;

		क्रम (j = 4; j <= MS_EXTRA_SIZE; j++)
			data[6 + j] = 0xFF;

		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, (6 + MS_EXTRA_SIZE),
					NO_WAIT_INT, data, 16);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_send_cmd(chip, BLOCK_WRITE, WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		ms_set_err_code(chip, MS_NO_ERROR);
		retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (val & INT_REG_CMDNK) अणु
			ms_set_err_code(chip, MS_CMD_NK);
			वापस STATUS_FAIL;
		पूर्ण

		अगर (val & INT_REG_CED) अणु
			अगर (val & INT_REG_ERR) अणु
				ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		अगर (i == 0) अणु
			retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG,
						    MS_EXTRA_SIZE, SYSTEM_PARAM,
						    7);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			ms_set_err_code(chip, MS_NO_ERROR);

			अगर (CHK_MS4BIT(ms_card))
				data[0] = 0x88;
			अन्यथा
				data[0] = 0x80;

			data[1] = 0;
			data[2] = (u8)(old_blk >> 8);
			data[3] = (u8)old_blk;
			data[4] = 0x80;
			data[5] = 0;
			data[6] = 0xEF;
			data[7] = 0xFF;

			retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 7,
						NO_WAIT_INT, data, 8);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			retval = ms_send_cmd(chip, BLOCK_WRITE, WAIT_INT);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			ms_set_err_code(chip, MS_NO_ERROR);
			retval = ms_पढ़ो_bytes(chip, GET_INT, 1,
					       NO_WAIT_INT, &val, 1);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			अगर (val & INT_REG_CMDNK) अणु
				ms_set_err_code(chip, MS_CMD_NK);
				वापस STATUS_FAIL;
			पूर्ण

			अगर (val & INT_REG_CED) अणु
				अगर (val & INT_REG_ERR) अणु
					ms_set_err_code(chip,
							MS_FLASH_WRITE_ERROR);
					वापस STATUS_FAIL;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक reset_ms(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	u16 i, reg_addr, block_size;
	u8 val, extra[MS_EXTRA_SIZE], j, *ptr;
#अगर_अघोषित SUPPORT_MAGIC_GATE
	u16 eblock_cnt;
#पूर्ण_अगर

	retval = ms_prepare_reset(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_card->ms_type |= TYPE_MS;

	retval = ms_send_cmd(chip, MS_RESET, NO_WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_पढ़ो_status_reg(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PPBUF_BASE2, &val);
	अगर (retval)
		वापस retval;

	अगर (val & WRT_PRTCT)
		chip->card_wp |= MS_CARD;
	अन्यथा
		chip->card_wp &= ~MS_CARD;

	i = 0;

RE_SEARCH:
	/* Search Boot Block */
	जबतक (i < (MAX_DEFECTIVE_BLOCK + 2)) अणु
		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			ms_set_err_code(chip, MS_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = ms_पढ़ो_extra_data(chip, i, 0, extra, MS_EXTRA_SIZE);
		अगर (retval != STATUS_SUCCESS) अणु
			i++;
			जारी;
		पूर्ण

		अगर (extra[0] & BLOCK_OK) अणु
			अगर (!(extra[1] & NOT_BOOT_BLOCK)) अणु
				ms_card->boot_block = i;
				अवरोध;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण

	अगर (i == (MAX_DEFECTIVE_BLOCK + 2)) अणु
		dev_dbg(rtsx_dev(chip), "No boot block found!");
		वापस STATUS_FAIL;
	पूर्ण

	क्रम (j = 0; j < 3; j++) अणु
		retval = ms_पढ़ो_page(chip, ms_card->boot_block, j);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (ms_check_err_code(chip, MS_FLASH_WRITE_ERROR)) अणु
				i = ms_card->boot_block + 1;
				ms_set_err_code(chip, MS_NO_ERROR);
				जाओ RE_SEARCH;
			पूर्ण
		पूर्ण
	पूर्ण

	retval = ms_पढ़ो_page(chip, ms_card->boot_block, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	/* Read MS प्रणाली inक्रमmation as sys_info */
	rtsx_init_cmd(chip);

	क्रम (i = 0; i < 96; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 0x1A0 + i, 0, 0);

	retval = rtsx_send_cmd(chip, MS_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	ptr = rtsx_get_cmd_data(chip);
	स_नकल(ms_card->raw_sys_info, ptr, 96);

	/* Read useful block contents */
	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, READ_REG_CMD, HEADER_ID0, 0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, HEADER_ID1, 0, 0);

	क्रम (reg_addr = DISABLED_BLOCK0; reg_addr <= DISABLED_BLOCK3;
	     reg_addr++)
		rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

	क्रम (reg_addr = BLOCK_SIZE_0; reg_addr <= PAGE_SIZE_1; reg_addr++)
		rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

	rtsx_add_cmd(chip, READ_REG_CMD, MS_device_type, 0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, MS_4bit_support, 0, 0);

	retval = rtsx_send_cmd(chip, MS_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	ptr = rtsx_get_cmd_data(chip);

	dev_dbg(rtsx_dev(chip), "Boot block data:\n");
	dev_dbg(rtsx_dev(chip), "%*ph\n", 16, ptr);

	/* Block ID error
	 * HEADER_ID0, HEADER_ID1
	 */
	अगर (ptr[0] != 0x00 || ptr[1] != 0x01) अणु
		i = ms_card->boot_block + 1;
		जाओ RE_SEARCH;
	पूर्ण

	/* Page size error
	 * PAGE_SIZE_0, PAGE_SIZE_1
	 */
	अगर (ptr[12] != 0x02 || ptr[13] != 0x00) अणु
		i = ms_card->boot_block + 1;
		जाओ RE_SEARCH;
	पूर्ण

	अगर ((ptr[14] == 1) || (ptr[14] == 3))
		chip->card_wp |= MS_CARD;

	/* BLOCK_SIZE_0, BLOCK_SIZE_1 */
	block_size = ((u16)ptr[6] << 8) | ptr[7];
	अगर (block_size == 0x0010) अणु
		/* Block size 16KB */
		ms_card->block_shअगरt = 5;
		ms_card->page_off = 0x1F;
	पूर्ण अन्यथा अगर (block_size == 0x0008) अणु
		/* Block size 8KB */
		ms_card->block_shअगरt = 4;
		ms_card->page_off = 0x0F;
	पूर्ण

	/* BLOCK_COUNT_0, BLOCK_COUNT_1 */
	ms_card->total_block = ((u16)ptr[8] << 8) | ptr[9];

#अगर_घोषित SUPPORT_MAGIC_GATE
	j = ptr[10];

	अगर (ms_card->block_shअगरt == 4)  अणु /* 4MB or 8MB */
		अगर (j < 2)  अणु /* Effective block क्रम 4MB: 0x1F0 */
			ms_card->capacity = 0x1EE0;
		पूर्ण अन्यथा अणु /* Effective block क्रम 8MB: 0x3E0 */
			ms_card->capacity = 0x3DE0;
		पूर्ण
	पूर्ण अन्यथा  अणु /* 16MB, 32MB, 64MB or 128MB */
		अगर (j < 5)  अणु /* Effective block क्रम 16MB: 0x3E0 */
			ms_card->capacity = 0x7BC0;
		पूर्ण अन्यथा अगर (j < 0xA) अणु /* Effective block क्रम 32MB: 0x7C0 */
			ms_card->capacity = 0xF7C0;
		पूर्ण अन्यथा अगर (j < 0x11) अणु /* Effective block क्रम 64MB: 0xF80 */
			ms_card->capacity = 0x1EF80;
		पूर्ण अन्यथा अणु /* Effective block क्रम 128MB: 0x1F00 */
			ms_card->capacity = 0x3DF00;
		पूर्ण
	पूर्ण
#अन्यथा
	/* EBLOCK_COUNT_0, EBLOCK_COUNT_1 */
	eblock_cnt = ((u16)ptr[10] << 8) | ptr[11];

	ms_card->capacity = ((u32)eblock_cnt - 2) << ms_card->block_shअगरt;
#पूर्ण_अगर

	chip->capacity[chip->card2lun[MS_CARD]] = ms_card->capacity;

	/* Switch I/F Mode */
	अगर (ptr[15]) अणु
		retval = ms_set_rw_reg_addr(chip, 0, 0, SYSTEM_PARAM, 1);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PPBUF_BASE2, 0xFF, 0x88);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PPBUF_BASE2 + 1, 0xFF, 0);
		अगर (retval)
			वापस retval;

		retval = ms_transfer_tpc(chip, MS_TM_WRITE_BYTES, WRITE_REG, 1,
					 NO_WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG,
					     0x58 | MS_NO_CHECK_INT,
					     MS_BUS_WIDTH_4 |
					     PUSH_TIME_ODD |
					     MS_NO_CHECK_INT);
		अगर (retval)
			वापस retval;

		ms_card->ms_type |= MS_4BIT;
	पूर्ण

	अगर (CHK_MS4BIT(ms_card))
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 4;
	अन्यथा
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 1;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_init_l2p_tbl(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक size, i, seg_no, retval;
	u16 defect_block, reg_addr;
	u8 val1, val2;

	ms_card->segment_cnt = ms_card->total_block >> 9;
	dev_dbg(rtsx_dev(chip), "ms_card->segment_cnt = %d\n",
		ms_card->segment_cnt);

	size = ms_card->segment_cnt * माप(काष्ठा zone_entry);
	ms_card->segment = vzalloc(size);
	अगर (!ms_card->segment)
		वापस STATUS_FAIL;

	retval = ms_पढ़ो_page(chip, ms_card->boot_block, 1);
	अगर (retval != STATUS_SUCCESS)
		जाओ INIT_FAIL;

	reg_addr = PPBUF_BASE2;
	क्रम (i = 0; i < (((ms_card->total_block >> 9) * 10) + 1); i++) अणु
		पूर्णांक block_no;

		retval = rtsx_पढ़ो_रेजिस्टर(chip, reg_addr++, &val1);
		अगर (retval != STATUS_SUCCESS)
			जाओ INIT_FAIL;

		retval = rtsx_पढ़ो_रेजिस्टर(chip, reg_addr++, &val2);
		अगर (retval != STATUS_SUCCESS)
			जाओ INIT_FAIL;

		defect_block = ((u16)val1 << 8) | val2;
		अगर (defect_block == 0xFFFF)
			अवरोध;

		seg_no = defect_block / 512;

		block_no = ms_card->segment[seg_no].disable_count++;
		ms_card->segment[seg_no].defect_list[block_no] = defect_block;
	पूर्ण

	क्रम (i = 0; i < ms_card->segment_cnt; i++) अणु
		ms_card->segment[i].build_flag = 0;
		ms_card->segment[i].l2p_table = शून्य;
		ms_card->segment[i].मुक्त_table = शून्य;
		ms_card->segment[i].get_index = 0;
		ms_card->segment[i].set_index = 0;
		ms_card->segment[i].unused_blk_cnt = 0;

		dev_dbg(rtsx_dev(chip), "defective block count of segment %d is %d\n",
			i, ms_card->segment[i].disable_count);
	पूर्ण

	वापस STATUS_SUCCESS;

INIT_FAIL:
	vमुक्त(ms_card->segment);
	ms_card->segment = शून्य;

	वापस STATUS_FAIL;
पूर्ण

अटल u16 ms_get_l2p_tbl(काष्ठा rtsx_chip *chip, पूर्णांक seg_no, u16 log_off)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा zone_entry *segment;

	अगर (!ms_card->segment)
		वापस 0xFFFF;

	segment = &ms_card->segment[seg_no];

	अगर (segment->l2p_table)
		वापस segment->l2p_table[log_off];

	वापस 0xFFFF;
पूर्ण

अटल व्योम ms_set_l2p_tbl(काष्ठा rtsx_chip *chip,
			   पूर्णांक seg_no, u16 log_off, u16 phy_blk)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा zone_entry *segment;

	अगर (!ms_card->segment)
		वापस;

	segment = &ms_card->segment[seg_no];
	अगर (segment->l2p_table)
		segment->l2p_table[log_off] = phy_blk;
पूर्ण

अटल व्योम ms_set_unused_block(काष्ठा rtsx_chip *chip, u16 phy_blk)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा zone_entry *segment;
	पूर्णांक seg_no;

	seg_no = (पूर्णांक)phy_blk >> 9;
	segment = &ms_card->segment[seg_no];

	segment->मुक्त_table[segment->set_index++] = phy_blk;
	अगर (segment->set_index >= MS_FREE_TABLE_CNT)
		segment->set_index = 0;

	segment->unused_blk_cnt++;
पूर्ण

अटल u16 ms_get_unused_block(काष्ठा rtsx_chip *chip, पूर्णांक seg_no)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा zone_entry *segment;
	u16 phy_blk;

	segment = &ms_card->segment[seg_no];

	अगर (segment->unused_blk_cnt <= 0)
		वापस 0xFFFF;

	phy_blk = segment->मुक्त_table[segment->get_index];
	segment->मुक्त_table[segment->get_index++] = 0xFFFF;
	अगर (segment->get_index >= MS_FREE_TABLE_CNT)
		segment->get_index = 0;

	segment->unused_blk_cnt--;

	वापस phy_blk;
पूर्ण

अटल स्थिर अचिन्हित लघु ms_start_idx[] = अणु0, 494, 990, 1486, 1982, 2478,
					      2974, 3470, 3966, 4462, 4958,
					      5454, 5950, 6446, 6942, 7438,
					      7934पूर्ण;

अटल पूर्णांक ms_arbitrate_l2p(काष्ठा rtsx_chip *chip, u16 phy_blk,
			    u16 log_off, u8 us1, u8 us2)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा zone_entry *segment;
	पूर्णांक seg_no;
	u16 पंचांगp_blk;

	seg_no = (पूर्णांक)phy_blk >> 9;
	segment = &ms_card->segment[seg_no];
	पंचांगp_blk = segment->l2p_table[log_off];

	अगर (us1 != us2) अणु
		अगर (us1 == 0) अणु
			अगर (!(chip->card_wp & MS_CARD))
				ms_erase_block(chip, पंचांगp_blk);

			ms_set_unused_block(chip, पंचांगp_blk);
			segment->l2p_table[log_off] = phy_blk;
		पूर्ण अन्यथा अणु
			अगर (!(chip->card_wp & MS_CARD))
				ms_erase_block(chip, phy_blk);

			ms_set_unused_block(chip, phy_blk);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy_blk < पंचांगp_blk) अणु
			अगर (!(chip->card_wp & MS_CARD))
				ms_erase_block(chip, phy_blk);

			ms_set_unused_block(chip, phy_blk);
		पूर्ण अन्यथा अणु
			अगर (!(chip->card_wp & MS_CARD))
				ms_erase_block(chip, पंचांगp_blk);

			ms_set_unused_block(chip, पंचांगp_blk);
			segment->l2p_table[log_off] = phy_blk;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_build_l2p_tbl(काष्ठा rtsx_chip *chip, पूर्णांक seg_no)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा zone_entry *segment;
	bool defect_flag;
	पूर्णांक retval, table_size, disable_cnt, i;
	u16 start, end, phy_blk, log_blk, पंचांगp_blk, idx;
	u8 extra[MS_EXTRA_SIZE], us1, us2;

	dev_dbg(rtsx_dev(chip), "%s: %d\n", __func__, seg_no);

	अगर (!ms_card->segment) अणु
		retval = ms_init_l2p_tbl(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस retval;
	पूर्ण

	अगर (ms_card->segment[seg_no].build_flag) अणु
		dev_dbg(rtsx_dev(chip), "l2p table of segment %d has been built\n",
			seg_no);
		वापस STATUS_SUCCESS;
	पूर्ण

	अगर (seg_no == 0)
		table_size = 494;
	अन्यथा
		table_size = 496;

	segment = &ms_card->segment[seg_no];

	अगर (!segment->l2p_table) अणु
		segment->l2p_table = vदो_स्मृति(array_size(table_size, 2));
		अगर (!segment->l2p_table)
			जाओ BUILD_FAIL;
	पूर्ण
	स_रखो((u8 *)(segment->l2p_table), 0xff, array_size(table_size, 2));

	अगर (!segment->मुक्त_table) अणु
		segment->मुक्त_table = vदो_स्मृति(array_size(MS_FREE_TABLE_CNT, 2));
		अगर (!segment->मुक्त_table)
			जाओ BUILD_FAIL;
	पूर्ण
	स_रखो((u8 *)(segment->मुक्त_table), 0xff, array_size(MS_FREE_TABLE_CNT, 2));

	start = (u16)seg_no << 9;
	end = (u16)(seg_no + 1) << 9;

	disable_cnt = segment->disable_count;

	segment->get_index = 0;
	segment->set_index = 0;
	segment->unused_blk_cnt = 0;

	क्रम (phy_blk = start; phy_blk < end; phy_blk++) अणु
		अगर (disable_cnt) अणु
			defect_flag = false;
			क्रम (i = 0; i < segment->disable_count; i++) अणु
				अगर (phy_blk == segment->defect_list[i]) अणु
					defect_flag = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (defect_flag) अणु
				disable_cnt--;
				जारी;
			पूर्ण
		पूर्ण

		retval = ms_पढ़ो_extra_data(chip, phy_blk, 0,
					    extra, MS_EXTRA_SIZE);
		अगर (retval != STATUS_SUCCESS) अणु
			dev_dbg(rtsx_dev(chip), "read extra data fail\n");
			ms_set_bad_block(chip, phy_blk);
			जारी;
		पूर्ण

		अगर (seg_no == ms_card->segment_cnt - 1) अणु
			अगर (!(extra[1] & NOT_TRANSLATION_TABLE)) अणु
				अगर (!(chip->card_wp & MS_CARD)) अणु
					retval = ms_erase_block(chip, phy_blk);
					अगर (retval != STATUS_SUCCESS)
						जारी;
					extra[2] = 0xff;
					extra[3] = 0xff;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!(extra[0] & BLOCK_OK))
			जारी;
		अगर (!(extra[1] & NOT_BOOT_BLOCK))
			जारी;
		अगर ((extra[0] & PAGE_OK) != PAGE_OK)
			जारी;

		log_blk = ((u16)extra[2] << 8) | extra[3];

		अगर (log_blk == 0xFFFF) अणु
			अगर (!(chip->card_wp & MS_CARD)) अणु
				retval = ms_erase_block(chip, phy_blk);
				अगर (retval != STATUS_SUCCESS)
					जारी;
			पूर्ण
			ms_set_unused_block(chip, phy_blk);
			जारी;
		पूर्ण

		अगर ((log_blk < ms_start_idx[seg_no]) ||
		    (log_blk >= ms_start_idx[seg_no + 1])) अणु
			अगर (!(chip->card_wp & MS_CARD)) अणु
				retval = ms_erase_block(chip, phy_blk);
				अगर (retval != STATUS_SUCCESS)
					जारी;
			पूर्ण
			ms_set_unused_block(chip, phy_blk);
			जारी;
		पूर्ण

		idx = log_blk - ms_start_idx[seg_no];

		अगर (segment->l2p_table[idx] == 0xFFFF) अणु
			segment->l2p_table[idx] = phy_blk;
			जारी;
		पूर्ण

		us1 = extra[0] & 0x10;
		पंचांगp_blk = segment->l2p_table[idx];
		retval = ms_पढ़ो_extra_data(chip, पंचांगp_blk, 0,
					    extra, MS_EXTRA_SIZE);
		अगर (retval != STATUS_SUCCESS)
			जारी;
		us2 = extra[0] & 0x10;

		(व्योम)ms_arbitrate_l2p(chip, phy_blk,
				log_blk - ms_start_idx[seg_no], us1, us2);
		जारी;
	पूर्ण

	segment->build_flag = 1;

	dev_dbg(rtsx_dev(chip), "unused block count: %d\n",
		segment->unused_blk_cnt);

	/* Logical Address Confirmation Process */
	अगर (seg_no == ms_card->segment_cnt - 1) अणु
		अगर (segment->unused_blk_cnt < 2)
			chip->card_wp |= MS_CARD;
	पूर्ण अन्यथा अणु
		अगर (segment->unused_blk_cnt < 1)
			chip->card_wp |= MS_CARD;
	पूर्ण

	अगर (chip->card_wp & MS_CARD)
		वापस STATUS_SUCCESS;

	क्रम (log_blk = ms_start_idx[seg_no];
	     log_blk < ms_start_idx[seg_no + 1]; log_blk++) अणु
		idx = log_blk - ms_start_idx[seg_no];
		अगर (segment->l2p_table[idx] == 0xFFFF) अणु
			phy_blk = ms_get_unused_block(chip, seg_no);
			अगर (phy_blk == 0xFFFF) अणु
				chip->card_wp |= MS_CARD;
				वापस STATUS_SUCCESS;
			पूर्ण
			retval = ms_init_page(chip, phy_blk, log_blk, 0, 1);
			अगर (retval != STATUS_SUCCESS)
				जाओ BUILD_FAIL;

			segment->l2p_table[idx] = phy_blk;
			अगर (seg_no == ms_card->segment_cnt - 1) अणु
				अगर (segment->unused_blk_cnt < 2) अणु
					chip->card_wp |= MS_CARD;
					वापस STATUS_SUCCESS;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (segment->unused_blk_cnt < 1) अणु
					chip->card_wp |= MS_CARD;
					वापस STATUS_SUCCESS;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Make boot block be the first normal block */
	अगर (seg_no == 0) अणु
		क्रम (log_blk = 0; log_blk < 494; log_blk++) अणु
			पंचांगp_blk = segment->l2p_table[log_blk];
			अगर (पंचांगp_blk < ms_card->boot_block) अणु
				dev_dbg(rtsx_dev(chip), "Boot block is not the first normal block.\n");

				अगर (chip->card_wp & MS_CARD)
					अवरोध;

				phy_blk = ms_get_unused_block(chip, 0);
				retval = ms_copy_page(chip, पंचांगp_blk, phy_blk,
						      log_blk, 0,
						      ms_card->page_off + 1);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;

				segment->l2p_table[log_blk] = phy_blk;

				retval = ms_set_bad_block(chip, पंचांगp_blk);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;

BUILD_FAIL:
	segment->build_flag = 0;
	vमुक्त(segment->l2p_table);
	segment->l2p_table = शून्य;
	vमुक्त(segment->मुक्त_table);
	segment->मुक्त_table = शून्य;

	वापस STATUS_FAIL;
पूर्ण

पूर्णांक reset_ms_card(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक seg_no = ms_card->total_block / 512 - 1;
	पूर्णांक retval;

	स_रखो(ms_card, 0, माप(काष्ठा ms_info));

	retval = enable_card_घड़ी(chip, MS_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = select_card(chip, MS_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_card->ms_type = 0;

	retval = reset_ms_pro(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		अगर (ms_card->check_ms_flow) अणु
			retval = reset_ms(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण अन्यथा अणु
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = ms_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (!CHK_MSPRO(ms_card)) अणु
		/* Build table क्रम the last segment,
		 * to check अगर L2P table block exists, erasing it
		 */
		retval = ms_build_l2p_tbl(chip, seg_no);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "ms_card->ms_type = 0x%x\n", ms_card->ms_type);

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक mspro_set_rw_cmd(काष्ठा rtsx_chip *chip,
			    u32 start_sec, u16 sec_cnt, u8 cmd)
अणु
	पूर्णांक retval, i;
	u8 data[8];

	data[0] = cmd;
	data[1] = (u8)(sec_cnt >> 8);
	data[2] = (u8)sec_cnt;
	data[3] = (u8)(start_sec >> 24);
	data[4] = (u8)(start_sec >> 16);
	data[5] = (u8)(start_sec >> 8);
	data[6] = (u8)start_sec;
	data[7] = 0;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, PRO_EX_SET_CMD, 7,
					WAIT_INT, data, 8);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

व्योम mspro_stop_seq_mode(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;

	अगर (ms_card->seq_mode) अणु
		retval = ms_चयन_घड़ी(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस;

		ms_card->seq_mode = 0;
		ms_card->total_sec_cnt = 0;
		ms_send_cmd(chip, PRO_STOP, WAIT_INT);

		rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, RB_FLUSH, RB_FLUSH);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ms_स्वतः_tune_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;

	अगर (chip->asic_code) अणु
		अगर (ms_card->ms_घड़ी > 30)
			ms_card->ms_घड़ी -= 20;
	पूर्ण अन्यथा अणु
		अगर (ms_card->ms_घड़ी == CLK_80)
			ms_card->ms_घड़ी = CLK_60;
		अन्यथा अगर (ms_card->ms_घड़ी == CLK_60)
			ms_card->ms_घड़ी = CLK_40;
	पूर्ण

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक mspro_rw_multi_sector(काष्ठा scsi_cmnd *srb,
				 काष्ठा rtsx_chip *chip, u32 start_sector,
				 u16 sector_cnt)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	bool mode_2k = false;
	पूर्णांक retval;
	u16 count;
	u8 val, trans_mode, rw_tpc, rw_cmd;

	ms_set_err_code(chip, MS_NO_ERROR);

	ms_card->cleanup_counter = 0;

	अगर (CHK_MSHG(ms_card)) अणु
		अगर ((start_sector % 4) || (sector_cnt % 4)) अणु
			अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
				rw_tpc = PRO_READ_LONG_DATA;
				rw_cmd = PRO_READ_DATA;
			पूर्ण अन्यथा अणु
				rw_tpc = PRO_WRITE_LONG_DATA;
				rw_cmd = PRO_WRITE_DATA;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
				rw_tpc = PRO_READ_QUAD_DATA;
				rw_cmd = PRO_READ_2K_DATA;
			पूर्ण अन्यथा अणु
				rw_tpc = PRO_WRITE_QUAD_DATA;
				rw_cmd = PRO_WRITE_2K_DATA;
			पूर्ण
			mode_2k = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
			rw_tpc = PRO_READ_LONG_DATA;
			rw_cmd = PRO_READ_DATA;
		पूर्ण अन्यथा अणु
			rw_tpc = PRO_WRITE_LONG_DATA;
			rw_cmd = PRO_WRITE_DATA;
		पूर्ण
	पूर्ण

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
		trans_mode = MS_TM_AUTO_READ;
	अन्यथा
		trans_mode = MS_TM_AUTO_WRITE;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
	अगर (retval)
		वापस retval;

	अगर (ms_card->seq_mode) अणु
		अगर ((ms_card->pre_dir != srb->sc_data_direction) ||
		    ((ms_card->pre_sec_addr + ms_card->pre_sec_cnt) !=
		     start_sector) ||
		    (mode_2k && (ms_card->seq_mode & MODE_512_SEQ)) ||
		    (!mode_2k && (ms_card->seq_mode & MODE_2K_SEQ)) ||
		    !(val & MS_INT_BREQ) ||
		    ((ms_card->total_sec_cnt + sector_cnt) > 0xFE00)) अणु
			ms_card->seq_mode = 0;
			ms_card->total_sec_cnt = 0;
			अगर (val & MS_INT_BREQ) अणु
				retval = ms_send_cmd(chip, PRO_STOP, WAIT_INT);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;

				rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, RB_FLUSH,
						    RB_FLUSH);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ms_card->seq_mode) अणु
		ms_card->total_sec_cnt = 0;
		अगर (sector_cnt >= SEQ_START_CRITERIA) अणु
			अगर ((ms_card->capacity - start_sector) > 0xFE00)
				count = 0xFE00;
			अन्यथा
				count = (u16)(ms_card->capacity - start_sector);

			अगर (count > sector_cnt) अणु
				अगर (mode_2k)
					ms_card->seq_mode = MODE_2K_SEQ;
				अन्यथा
					ms_card->seq_mode = MODE_512_SEQ;
			पूर्ण
		पूर्ण अन्यथा अणु
			count = sector_cnt;
		पूर्ण
		retval = mspro_set_rw_cmd(chip, start_sector, count, rw_cmd);
		अगर (retval != STATUS_SUCCESS) अणु
			ms_card->seq_mode = 0;
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = ms_transfer_data(chip, trans_mode, rw_tpc, sector_cnt,
				  WAIT_INT, mode_2k, scsi_sg_count(srb),
				  scsi_sglist(srb), scsi_bufflen(srb));
	अगर (retval != STATUS_SUCCESS) अणु
		ms_card->seq_mode = 0;
		rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
		rtsx_clear_ms_error(chip);

		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			chip->rw_need_retry = 0;
			dev_dbg(rtsx_dev(chip), "No card exist, exit %s\n",
				__func__);
			वापस STATUS_FAIL;
		पूर्ण

		अगर (val & MS_INT_BREQ)
			ms_send_cmd(chip, PRO_STOP, WAIT_INT);

		अगर (val & (MS_CRC16_ERR | MS_RDY_TIMEOUT)) अणु
			dev_dbg(rtsx_dev(chip), "MSPro CRC error, tune clock!\n");
			chip->rw_need_retry = 1;
			ms_स्वतः_tune_घड़ी(chip);
		पूर्ण

		वापस retval;
	पूर्ण

	अगर (ms_card->seq_mode) अणु
		ms_card->pre_sec_addr = start_sector;
		ms_card->pre_sec_cnt = sector_cnt;
		ms_card->pre_dir = srb->sc_data_direction;
		ms_card->total_sec_cnt += sector_cnt;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक mspro_पढ़ो_क्रमmat_progress(काष्ठा rtsx_chip *chip,
				      स्थिर पूर्णांक लघु_data_len)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u32 total_progress, cur_progress;
	u8 cnt, पंचांगp;
	u8 data[8];

	dev_dbg(rtsx_dev(chip), "%s, short_data_len = %d\n", __func__,
		लघु_data_len);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &पंचांगp);
	अगर (retval != STATUS_SUCCESS) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	अगर (!(पंचांगp & MS_INT_BREQ)) अणु
		अगर ((पंचांगp & (MS_INT_CED | MS_INT_BREQ | MS_INT_CMDNK |
			    MS_INT_ERR)) == MS_INT_CED) अणु
			ms_card->क्रमmat_status = FORMAT_SUCCESS;
			वापस STATUS_SUCCESS;
		पूर्ण
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	अगर (लघु_data_len >= 256)
		cnt = 0;
	अन्यथा
		cnt = (u8)लघु_data_len;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, MS_NO_CHECK_INT,
				     MS_NO_CHECK_INT);
	अगर (retval != STATUS_SUCCESS) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	retval = ms_पढ़ो_bytes(chip, PRO_READ_SHORT_DATA, cnt, WAIT_INT,
			       data, 8);
	अगर (retval != STATUS_SUCCESS) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	total_progress = (data[0] << 24) | (data[1] << 16) |
		(data[2] << 8) | data[3];
	cur_progress = (data[4] << 24) | (data[5] << 16) |
		(data[6] << 8) | data[7];

	dev_dbg(rtsx_dev(chip), "total_progress = %d, cur_progress = %d\n",
		total_progress, cur_progress);

	अगर (total_progress == 0) अणु
		ms_card->progress = 0;
	पूर्ण अन्यथा अणु
		u64 ullपंचांगp = (u64)cur_progress * (u64)65535;

		करो_भाग(ullपंचांगp, total_progress);
		ms_card->progress = (u16)ullपंचांगp;
	पूर्ण
	dev_dbg(rtsx_dev(chip), "progress = %d\n", ms_card->progress);

	क्रम (i = 0; i < 5000; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &पंचांगp);
		अगर (retval != STATUS_SUCCESS) अणु
			ms_card->क्रमmat_status = FORMAT_FAIL;
			वापस STATUS_FAIL;
		पूर्ण
		अगर (पंचांगp & (MS_INT_CED | MS_INT_CMDNK |
				MS_INT_BREQ | MS_INT_ERR))
			अवरोध;

		रुको_समयout(1);
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG, MS_NO_CHECK_INT, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	अगर (i == 5000) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	अगर (पंचांगp & (MS_INT_CMDNK | MS_INT_ERR)) अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		वापस STATUS_FAIL;
	पूर्ण

	अगर (पंचांगp & MS_INT_CED) अणु
		ms_card->क्रमmat_status = FORMAT_SUCCESS;
		ms_card->pro_under_क्रमmatting = 0;
	पूर्ण अन्यथा अगर (पंचांगp & MS_INT_BREQ) अणु
		ms_card->क्रमmat_status = FORMAT_IN_PROGRESS;
	पूर्ण अन्यथा अणु
		ms_card->क्रमmat_status = FORMAT_FAIL;
		ms_card->pro_under_क्रमmatting = 0;
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

व्योम mspro_polling_क्रमmat_status(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक i;

	अगर (ms_card->pro_under_क्रमmatting &&
	    (rtsx_get_stat(chip) != RTSX_STAT_SS)) अणु
		rtsx_set_stat(chip, RTSX_STAT_RUN);

		क्रम (i = 0; i < 65535; i++) अणु
			mspro_पढ़ो_क्रमmat_progress(chip, MS_SHORT_DATA_LEN);
			अगर (ms_card->क्रमmat_status != FORMAT_IN_PROGRESS)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक mspro_क्रमmat(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
		 पूर्णांक लघु_data_len, bool quick_क्रमmat)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 buf[8], पंचांगp;
	u16 para;

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = ms_set_rw_reg_addr(chip, 0x00, 0x00, PRO_TPC_PARM, 0x01);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	स_रखो(buf, 0, 2);
	चयन (लघु_data_len) अणु
	हाल 32:
		buf[0] = 0;
		अवरोध;
	हाल 64:
		buf[0] = 1;
		अवरोध;
	हाल 128:
		buf[0] = 2;
		अवरोध;
	हाल 256:
	शेष:
		buf[0] = 3;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_REG, 1,
					NO_WAIT_INT, buf, 2);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	अगर (quick_क्रमmat)
		para = 0x0000;
	अन्यथा
		para = 0x0001;

	retval = mspro_set_rw_cmd(chip, 0, para, PRO_FORMAT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &पंचांगp);
	अगर (retval)
		वापस retval;

	अगर (पंचांगp & (MS_INT_CMDNK | MS_INT_ERR))
		वापस STATUS_FAIL;

	अगर ((पंचांगp & (MS_INT_BREQ | MS_INT_CED)) == MS_INT_BREQ) अणु
		ms_card->pro_under_क्रमmatting = 1;
		ms_card->progress = 0;
		ms_card->क्रमmat_status = FORMAT_IN_PROGRESS;
		वापस STATUS_SUCCESS;
	पूर्ण

	अगर (पंचांगp & MS_INT_CED) अणु
		ms_card->pro_under_क्रमmatting = 0;
		ms_card->progress = 0;
		ms_card->क्रमmat_status = FORMAT_SUCCESS;
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_NO_SENSE);
		वापस STATUS_SUCCESS;
	पूर्ण

	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक ms_पढ़ो_multiple_pages(काष्ठा rtsx_chip *chip, u16 phy_blk,
				  u16 log_blk, u8 start_page, u8 end_page,
				  u8 *buf, अचिन्हित पूर्णांक *index,
				  अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 extra[MS_EXTRA_SIZE], page_addr, val, trans_cfg, data[6];
	u8 *ptr;

	retval = ms_पढ़ो_extra_data(chip, phy_blk, start_page,
				    extra, MS_EXTRA_SIZE);
	अगर (retval == STATUS_SUCCESS) अणु
		अगर ((extra[1] & 0x30) != 0x30) अणु
			ms_set_err_code(chip, MS_FLASH_READ_ERROR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	अन्यथा
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(phy_blk >> 8);
	data[3] = (u8)phy_blk;
	data[4] = 0;
	data[5] = start_page;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 6, NO_WAIT_INT,
					data, 6);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);

	retval = ms_send_cmd(chip, BLOCK_READ, WAIT_INT);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ptr = buf;

	क्रम (page_addr = start_page; page_addr < end_page; page_addr++) अणु
		ms_set_err_code(chip, MS_NO_ERROR);

		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			ms_set_err_code(chip, MS_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (val & INT_REG_CMDNK) अणु
			ms_set_err_code(chip, MS_CMD_NK);
			वापस STATUS_FAIL;
		पूर्ण
		अगर (val & INT_REG_ERR) अणु
			अगर (val & INT_REG_BREQ) अणु
				retval = ms_पढ़ो_status_reg(chip);
				अगर (retval != STATUS_SUCCESS) अणु
					अगर (!(chip->card_wp & MS_CARD)) अणु
						reset_ms(chip);
						ms_set_page_status
							(log_blk, set_PS_NG,
							 extra,
							 MS_EXTRA_SIZE);
						ms_ग_लिखो_extra_data
							(chip, phy_blk,
							 page_addr, extra,
							 MS_EXTRA_SIZE);
					पूर्ण
					ms_set_err_code(chip,
							MS_FLASH_READ_ERROR);
					वापस STATUS_FAIL;
				पूर्ण
			पूर्ण अन्यथा अणु
				ms_set_err_code(chip, MS_FLASH_READ_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(val & INT_REG_BREQ)) अणु
				ms_set_err_code(chip, MS_BREQ_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		अगर (page_addr == (end_page - 1)) अणु
			अगर (!(val & INT_REG_CED)) अणु
				retval = ms_send_cmd(chip, BLOCK_END, WAIT_INT);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;
			पूर्ण

			retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT,
					       &val, 1);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			अगर (!(val & INT_REG_CED)) अणु
				ms_set_err_code(chip, MS_FLASH_READ_ERROR);
				वापस STATUS_FAIL;
			पूर्ण

			trans_cfg = NO_WAIT_INT;
		पूर्ण अन्यथा अणु
			trans_cfg = WAIT_INT;
		पूर्ण

		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, READ_PAGE_DATA);
		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG,
			     0xFF, trans_cfg);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
			     0x01, RING_BUFFER);

		trans_dma_enable(DMA_FROM_DEVICE, chip, 512, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANSFER, 0xFF,
			     MS_TRANSFER_START |  MS_TM_NORMAL_READ);
		rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANSFER,
			     MS_TRANSFER_END, MS_TRANSFER_END);

		rtsx_send_cmd_no_रुको(chip);

		retval = rtsx_transfer_data_partial(chip, MS_CARD, ptr, 512,
						    scsi_sg_count(chip->srb),
						    index, offset,
						    DMA_FROM_DEVICE,
						    chip->ms_समयout);
		अगर (retval < 0) अणु
			अगर (retval == -ETIMEDOUT) अणु
				ms_set_err_code(chip, MS_TO_ERROR);
				rtsx_clear_ms_error(chip);
				वापस STATUS_TIMEDOUT;
			पूर्ण

			retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
			अगर (retval != STATUS_SUCCESS) अणु
				ms_set_err_code(chip, MS_TO_ERROR);
				rtsx_clear_ms_error(chip);
				वापस STATUS_TIMEDOUT;
			पूर्ण
			अगर (val & (MS_CRC16_ERR | MS_RDY_TIMEOUT)) अणु
				ms_set_err_code(chip, MS_CRC16_ERROR);
				rtsx_clear_ms_error(chip);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		अगर (scsi_sg_count(chip->srb) == 0)
			ptr += 512;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_ग_लिखो_multiple_pages(काष्ठा rtsx_chip *chip, u16 old_blk,
				   u16 new_blk, u16 log_blk, u8 start_page,
				u8 end_page, u8 *buf, अचिन्हित पूर्णांक *index,
				अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, i;
	u8 page_addr, val, data[16];
	u8 *ptr;

	अगर (!start_page) अणु
		retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
					    SYSTEM_PARAM, 7);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (CHK_MS4BIT(ms_card))
			data[0] = 0x88;
		अन्यथा
			data[0] = 0x80;

		data[1] = 0;
		data[2] = (u8)(old_blk >> 8);
		data[3] = (u8)old_blk;
		data[4] = 0x80;
		data[5] = 0;
		data[6] = 0xEF;
		data[7] = 0xFF;

		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 7, NO_WAIT_INT,
					data, 8);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = ms_send_cmd(chip, BLOCK_WRITE, WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		ms_set_err_code(chip, MS_NO_ERROR);
		retval = ms_transfer_tpc(chip, MS_TM_READ_BYTES, GET_INT, 1,
					 NO_WAIT_INT);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	retval = ms_set_rw_reg_addr(chip, OVERWRITE_FLAG, MS_EXTRA_SIZE,
				    SYSTEM_PARAM, (6 + MS_EXTRA_SIZE));
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);

	अगर (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	अन्यथा
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(new_blk >> 8);
	data[3] = (u8)new_blk;
	अगर ((end_page - start_page) == 1)
		data[4] = 0x20;
	अन्यथा
		data[4] = 0;

	data[5] = start_page;
	data[6] = 0xF8;
	data[7] = 0xFF;
	data[8] = (u8)(log_blk >> 8);
	data[9] = (u8)log_blk;

	क्रम (i = 0x0A; i < 0x10; i++)
		data[i] = 0xFF;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, WRITE_REG, 6 + MS_EXTRA_SIZE,
					NO_WAIT_INT, data, 16);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_send_cmd(chip, BLOCK_WRITE, WAIT_INT);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	ptr = buf;
	क्रम (page_addr = start_page; page_addr < end_page; page_addr++) अणु
		ms_set_err_code(chip, MS_NO_ERROR);

		अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
			ms_set_err_code(chip, MS_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		अगर (val & INT_REG_CMDNK) अणु
			ms_set_err_code(chip, MS_CMD_NK);
			वापस STATUS_FAIL;
		पूर्ण
		अगर (val & INT_REG_ERR) अणु
			ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
			वापस STATUS_FAIL;
		पूर्ण
		अगर (!(val & INT_REG_BREQ)) अणु
			ms_set_err_code(chip, MS_BREQ_ERROR);
			वापस STATUS_FAIL;
		पूर्ण

		udelay(30);

		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC,
			     0xFF, WRITE_PAGE_DATA);
		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG,
			     0xFF, WAIT_INT);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
			     0x01, RING_BUFFER);

		trans_dma_enable(DMA_TO_DEVICE, chip, 512, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANSFER, 0xFF,
			     MS_TRANSFER_START |  MS_TM_NORMAL_WRITE);
		rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANSFER,
			     MS_TRANSFER_END, MS_TRANSFER_END);

		rtsx_send_cmd_no_रुको(chip);

		retval = rtsx_transfer_data_partial(chip, MS_CARD, ptr,	512,
						    scsi_sg_count(chip->srb),
						    index, offset,
						    DMA_TO_DEVICE,
						    chip->ms_समयout);
		अगर (retval < 0) अणु
			ms_set_err_code(chip, MS_TO_ERROR);
			rtsx_clear_ms_error(chip);

			अगर (retval == -ETIMEDOUT)
				वापस STATUS_TIMEDOUT;
			वापस STATUS_FAIL;
		पूर्ण

		retval = ms_पढ़ो_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर ((end_page - start_page) == 1) अणु
			अगर (!(val & INT_REG_CED)) अणु
				ms_set_err_code(chip, MS_FLASH_WRITE_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (page_addr == (end_page - 1)) अणु
				अगर (!(val & INT_REG_CED)) अणु
					retval = ms_send_cmd(chip, BLOCK_END,
							     WAIT_INT);
					अगर (retval != STATUS_SUCCESS)
						वापस STATUS_FAIL;
				पूर्ण

				retval = ms_पढ़ो_bytes(chip, GET_INT, 1,
						       NO_WAIT_INT, &val, 1);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;
			पूर्ण

			अगर ((page_addr == (end_page - 1)) ||
			    (page_addr == ms_card->page_off)) अणु
				अगर (!(val & INT_REG_CED)) अणु
					ms_set_err_code(chip,
							MS_FLASH_WRITE_ERROR);
					वापस STATUS_FAIL;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (scsi_sg_count(chip->srb) == 0)
			ptr += 512;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_finish_ग_लिखो(काष्ठा rtsx_chip *chip, u16 old_blk, u16 new_blk,
			   u16 log_blk, u8 page_off)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval, seg_no;

	retval = ms_copy_page(chip, old_blk, new_blk, log_blk,
			      page_off, ms_card->page_off + 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	seg_no = old_blk >> 9;

	अगर (MS_TST_BAD_BLOCK_FLG(ms_card)) अणु
		MS_CLR_BAD_BLOCK_FLG(ms_card);
		ms_set_bad_block(chip, old_blk);
	पूर्ण अन्यथा अणु
		retval = ms_erase_block(chip, old_blk);
		अगर (retval == STATUS_SUCCESS)
			ms_set_unused_block(chip, old_blk);
	पूर्ण

	ms_set_l2p_tbl(chip, seg_no, log_blk - ms_start_idx[seg_no], new_blk);

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_prepare_ग_लिखो(काष्ठा rtsx_chip *chip, u16 old_blk, u16 new_blk,
			    u16 log_blk, u8 start_page)
अणु
	पूर्णांक retval;

	अगर (start_page) अणु
		retval = ms_copy_page(chip, old_blk, new_blk, log_blk,
				      0, start_page);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

#अगर_घोषित MS_DELAY_WRITE
पूर्णांक ms_delay_ग_लिखो(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	काष्ठा ms_delay_ग_लिखो_tag *delay_ग_लिखो = &ms_card->delay_ग_लिखो;
	पूर्णांक retval;

	अगर (delay_ग_लिखो->delay_ग_लिखो_flag) अणु
		retval = ms_set_init_para(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		delay_ग_लिखो->delay_ग_लिखो_flag = 0;
		retval = ms_finish_ग_लिखो(chip,
					 delay_ग_लिखो->old_phyblock,
					delay_ग_लिखो->new_phyblock,
					delay_ग_लिखो->logblock,
					delay_ग_लिखो->pageoff);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ms_rw_fail(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
	अन्यथा
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
पूर्ण

अटल पूर्णांक ms_rw_multi_sector(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
			      u32 start_sector, u16 sector_cnt)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval, seg_no;
	अचिन्हित पूर्णांक index = 0, offset = 0;
	u16 old_blk = 0, new_blk = 0, log_blk, total_sec_cnt = sector_cnt;
	u8 start_page, end_page = 0, page_cnt;
	u8 *ptr;
#अगर_घोषित MS_DELAY_WRITE
	काष्ठा ms_delay_ग_लिखो_tag *delay_ग_लिखो = &ms_card->delay_ग_लिखो;
#पूर्ण_अगर

	ms_set_err_code(chip, MS_NO_ERROR);

	ms_card->cleanup_counter = 0;

	ptr = (u8 *)scsi_sglist(srb);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		ms_rw_fail(srb, chip);
		वापस STATUS_FAIL;
	पूर्ण

	log_blk = (u16)(start_sector >> ms_card->block_shअगरt);
	start_page = (u8)(start_sector & ms_card->page_off);

	क्रम (seg_no = 0; seg_no < ARRAY_SIZE(ms_start_idx) - 1; seg_no++) अणु
		अगर (log_blk < ms_start_idx[seg_no + 1])
			अवरोध;
	पूर्ण

	अगर (ms_card->segment[seg_no].build_flag == 0) अणु
		retval = ms_build_l2p_tbl(chip, seg_no);
		अगर (retval != STATUS_SUCCESS) अणु
			chip->card_fail |= MS_CARD;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
#अगर_घोषित MS_DELAY_WRITE
		अगर (delay_ग_लिखो->delay_ग_लिखो_flag &&
		    (delay_ग_लिखो->logblock == log_blk) &&
		    (start_page > delay_ग_लिखो->pageoff)) अणु
			delay_ग_लिखो->delay_ग_लिखो_flag = 0;
			retval = ms_copy_page(chip,
					      delay_ग_लिखो->old_phyblock,
					      delay_ग_लिखो->new_phyblock,
					      log_blk,
					      delay_ग_लिखो->pageoff, start_page);
			अगर (retval != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
			old_blk = delay_ग_लिखो->old_phyblock;
			new_blk = delay_ग_लिखो->new_phyblock;
		पूर्ण अन्यथा अगर (delay_ग_लिखो->delay_ग_लिखो_flag &&
				(delay_ग_लिखो->logblock == log_blk) &&
				(start_page == delay_ग_लिखो->pageoff)) अणु
			delay_ग_लिखो->delay_ग_लिखो_flag = 0;
			old_blk = delay_ग_लिखो->old_phyblock;
			new_blk = delay_ग_लिखो->new_phyblock;
		पूर्ण अन्यथा अणु
			retval = ms_delay_ग_लिखो(chip);
			अगर (retval != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
#पूर्ण_अगर
			old_blk = ms_get_l2p_tbl
					(chip, seg_no,
					 log_blk - ms_start_idx[seg_no]);
			new_blk  = ms_get_unused_block(chip, seg_no);
			अगर ((old_blk == 0xFFFF) || (new_blk == 0xFFFF)) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण

			retval = ms_prepare_ग_लिखो(chip, old_blk, new_blk,
						  log_blk, start_page);
			अगर (retval != STATUS_SUCCESS) अणु
				अगर (detect_card_cd(chip, MS_CARD) !=
				    STATUS_SUCCESS) अणु
					set_sense_type
						(chip, lun,
						SENSE_TYPE_MEDIA_NOT_PRESENT);
					वापस STATUS_FAIL;
				पूर्ण
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
#अगर_घोषित MS_DELAY_WRITE
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित MS_DELAY_WRITE
		retval = ms_delay_ग_लिखो(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				वापस STATUS_FAIL;
			पूर्ण
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस STATUS_FAIL;
		पूर्ण
#पूर्ण_अगर
		old_blk = ms_get_l2p_tbl(chip, seg_no,
					 log_blk - ms_start_idx[seg_no]);
		अगर (old_blk == 0xFFFF) अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	dev_dbg(rtsx_dev(chip), "seg_no = %d, old_blk = 0x%x, new_blk = 0x%x\n",
		seg_no, old_blk, new_blk);

	जबतक (total_sec_cnt) अणु
		अगर ((start_page + total_sec_cnt) > (ms_card->page_off + 1))
			end_page = ms_card->page_off + 1;
		अन्यथा
			end_page = start_page + (u8)total_sec_cnt;

		page_cnt = end_page - start_page;

		dev_dbg(rtsx_dev(chip), "start_page = %d, end_page = %d, page_cnt = %d\n",
			start_page, end_page, page_cnt);

		अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
			retval = ms_पढ़ो_multiple_pages(chip,
							old_blk, log_blk,
							start_page, end_page,
							ptr, &index, &offset);
		पूर्ण अन्यथा अणु
			retval = ms_ग_लिखो_multiple_pages(chip, old_blk, new_blk,
							 log_blk, start_page,
							 end_page, ptr, &index,
							 &offset);
		पूर्ण

		अगर (retval != STATUS_SUCCESS) अणु
			toggle_gpio(chip, 1);
			अगर (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				वापस STATUS_FAIL;
			पूर्ण
			ms_rw_fail(srb, chip);
			वापस STATUS_FAIL;
		पूर्ण

		अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
			अगर (end_page == (ms_card->page_off + 1)) अणु
				retval = ms_erase_block(chip, old_blk);
				अगर (retval == STATUS_SUCCESS)
					ms_set_unused_block(chip, old_blk);

				ms_set_l2p_tbl(chip, seg_no,
					       log_blk - ms_start_idx[seg_no],
					       new_blk);
			पूर्ण
		पूर्ण

		total_sec_cnt -= page_cnt;
		अगर (scsi_sg_count(srb) == 0)
			ptr += page_cnt * 512;

		अगर (total_sec_cnt == 0)
			अवरोध;

		log_blk++;

		क्रम (seg_no = 0; seg_no < ARRAY_SIZE(ms_start_idx) - 1;
				seg_no++) अणु
			अगर (log_blk < ms_start_idx[seg_no + 1])
				अवरोध;
		पूर्ण

		अगर (ms_card->segment[seg_no].build_flag == 0) अणु
			retval = ms_build_l2p_tbl(chip, seg_no);
			अगर (retval != STATUS_SUCCESS) अणु
				chip->card_fail |= MS_CARD;
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		old_blk = ms_get_l2p_tbl(chip, seg_no,
					 log_blk - ms_start_idx[seg_no]);
		अगर (old_blk == 0xFFFF) अणु
			ms_rw_fail(srb, chip);
			वापस STATUS_FAIL;
		पूर्ण

		अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
			new_blk = ms_get_unused_block(chip, seg_no);
			अगर (new_blk == 0xFFFF) अणु
				ms_rw_fail(srb, chip);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		dev_dbg(rtsx_dev(chip), "seg_no = %d, old_blk = 0x%x, new_blk = 0x%x\n",
			seg_no, old_blk, new_blk);

		start_page = 0;
	पूर्ण

	अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
		अगर (end_page < (ms_card->page_off + 1)) अणु
#अगर_घोषित MS_DELAY_WRITE
			delay_ग_लिखो->delay_ग_लिखो_flag = 1;
			delay_ग_लिखो->old_phyblock = old_blk;
			delay_ग_लिखो->new_phyblock = new_blk;
			delay_ग_लिखो->logblock = log_blk;
			delay_ग_लिखो->pageoff = end_page;
#अन्यथा
			retval = ms_finish_ग_लिखो(chip, old_blk, new_blk,
						 log_blk, end_page);
			अगर (retval != STATUS_SUCCESS) अणु
				अगर (detect_card_cd(chip, MS_CARD) !=
				    STATUS_SUCCESS) अणु
					set_sense_type
						(chip, lun,
						SENSE_TYPE_MEDIA_NOT_PRESENT);
					वापस STATUS_FAIL;
				पूर्ण

				ms_rw_fail(srb, chip);
				वापस STATUS_FAIL;
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	scsi_set_resid(srb, 0);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक ms_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	  u32 start_sector, u16 sector_cnt)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;

	अगर (CHK_MSPRO(ms_card))
		retval = mspro_rw_multi_sector(srb, chip, start_sector,
					       sector_cnt);
	अन्यथा
		retval = ms_rw_multi_sector(srb, chip, start_sector,
					    sector_cnt);

	वापस retval;
पूर्ण

व्योम ms_मुक्त_l2p_tbl(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक i = 0;

	अगर (ms_card->segment) अणु
		क्रम (i = 0; i < ms_card->segment_cnt; i++) अणु
			vमुक्त(ms_card->segment[i].l2p_table);
			ms_card->segment[i].l2p_table = शून्य;
			vमुक्त(ms_card->segment[i].मुक्त_table);
			ms_card->segment[i].मुक्त_table = शून्य;
		पूर्ण
		vमुक्त(ms_card->segment);
		ms_card->segment = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित SUPPORT_MAGIC_GATE

#अगर_घोषित READ_BYTES_WAIT_INT
अटल पूर्णांक ms_poll_पूर्णांक(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 val;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANS_CFG, MS_INT_CED, MS_INT_CED);

	retval = rtsx_send_cmd(chip, MS_CARD, 5000);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	val = *rtsx_get_cmd_data(chip);
	अगर (val & MS_INT_ERR)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित MS_SAMPLE_INT_ERR
अटल पूर्णांक check_ms_err(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 val;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANSFER, &val);
	अगर (retval != STATUS_SUCCESS)
		वापस 1;
	अगर (val & MS_TRANSFER_ERR)
		वापस 1;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANS_CFG, &val);
	अगर (retval != STATUS_SUCCESS)
		वापस 1;

	अगर (val & (MS_INT_ERR | MS_INT_CMDNK))
		वापस 1;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक check_ms_err(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 val;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, MS_TRANSFER, &val);
	अगर (retval != STATUS_SUCCESS)
		वापस 1;
	अगर (val & MS_TRANSFER_ERR)
		वापस 1;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mg_send_ex_cmd(काष्ठा rtsx_chip *chip, u8 cmd, u8 entry_num)
अणु
	पूर्णांक retval, i;
	u8 data[8];

	data[0] = cmd;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = entry_num;
	data[7] = 0;

	क्रम (i = 0; i < MS_MAX_RETRY_COUNT; i++) अणु
		retval = ms_ग_लिखो_bytes(chip, PRO_EX_SET_CMD, 7, WAIT_INT,
					data, 8);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (i == MS_MAX_RETRY_COUNT)
		वापस STATUS_FAIL;

	अगर (check_ms_err(chip)) अणु
		rtsx_clear_ms_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक mg_set_tpc_para_sub(काष्ठा rtsx_chip *chip, पूर्णांक type,
			       u8 mg_entry_num)
अणु
	पूर्णांक retval;
	u8 buf[6];

	अगर (type == 0)
		retval = ms_set_rw_reg_addr(chip, 0, 0, PRO_TPC_PARM, 1);
	अन्यथा
		retval = ms_set_rw_reg_addr(chip, 0, 0, PRO_DATA_COUNT1, 6);

	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	buf[0] = 0;
	buf[1] = 0;
	अगर (type == 1) अणु
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = mg_entry_num;
	पूर्ण
	retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_REG, (type == 0) ? 1 : 6,
				NO_WAIT_INT, buf, 6);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक mg_set_leaf_id(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	पूर्णांक i;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 buf1[32], buf2[12];

	अगर (scsi_bufflen(srb) < 12) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस STATUS_FAIL;
	पूर्ण

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = mg_send_ex_cmd(chip, MG_SET_LID, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB);
		वापस STATUS_FAIL;
	पूर्ण

	स_रखो(buf1, 0, 32);
	rtsx_stor_get_xfer_buf(buf2, min_t(पूर्णांक, 12, scsi_bufflen(srb)), srb);
	क्रम (i = 0; i < 8; i++)
		buf1[8 + i] = buf2[4 + i];

	retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_SHORT_DATA, 32, WAIT_INT,
				buf1, 32);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB);
		rtsx_clear_ms_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक mg_get_local_EKB(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	पूर्णांक bufflen;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 *buf = शून्य;

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	buf = kदो_स्मृति(1540, GFP_KERNEL);
	अगर (!buf)
		वापस STATUS_ERROR;

	buf[0] = 0x04;
	buf[1] = 0x1A;
	buf[2] = 0x00;
	buf[3] = 0x00;

	retval = mg_send_ex_cmd(chip, MG_GET_LEKB, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		जाओ मुक्त_buffer;
	पूर्ण

	retval = ms_transfer_data(chip, MS_TM_AUTO_READ, PRO_READ_LONG_DATA,
				  3, WAIT_INT, 0, 0, buf + 4, 1536);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		rtsx_clear_ms_error(chip);
		जाओ मुक्त_buffer;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		rtsx_clear_ms_error(chip);
		retval = STATUS_FAIL;
		जाओ मुक्त_buffer;
	पूर्ण

	bufflen = min_t(पूर्णांक, 1052, scsi_bufflen(srb));
	rtsx_stor_set_xfer_buf(buf, bufflen, srb);

मुक्त_buffer:
	kमुक्त(buf);
	वापस retval;
पूर्ण

पूर्णांक mg_chg(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	पूर्णांक bufflen;
	पूर्णांक i;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 buf[32];

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = mg_send_ex_cmd(chip, MG_GET_ID, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस STATUS_FAIL;
	पूर्ण

	retval = ms_पढ़ो_bytes(chip, PRO_READ_SHORT_DATA, 32, WAIT_INT,
			       buf, 32);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_clear_ms_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	स_नकल(ms_card->magic_gate_id, buf, 16);

#अगर_घोषित READ_BYTES_WAIT_INT
	retval = ms_poll_पूर्णांक(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस STATUS_FAIL;
	पूर्ण
#पूर्ण_अगर

	retval = mg_send_ex_cmd(chip, MG_SET_RD, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस STATUS_FAIL;
	पूर्ण

	bufflen = min_t(पूर्णांक, 12, scsi_bufflen(srb));
	rtsx_stor_get_xfer_buf(buf, bufflen, srb);

	क्रम (i = 0; i < 8; i++)
		buf[i] = buf[4 + i];

	क्रम (i = 0; i < 24; i++)
		buf[8 + i] = 0;

	retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_SHORT_DATA,
				32, WAIT_INT, buf, 32);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_clear_ms_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	ms_card->mg_auth = 0;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक mg_get_rsp_chg(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	पूर्णांक bufflen;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 buf1[32], buf2[36];

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = mg_send_ex_cmd(chip, MG_MAKE_RMS, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		वापस STATUS_FAIL;
	पूर्ण

	retval = ms_पढ़ो_bytes(chip, PRO_READ_SHORT_DATA, 32, WAIT_INT,
			       buf1, 32);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		rtsx_clear_ms_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	buf2[0] = 0x00;
	buf2[1] = 0x22;
	buf2[2] = 0x00;
	buf2[3] = 0x00;

	स_नकल(buf2 + 4, ms_card->magic_gate_id, 16);
	स_नकल(buf2 + 20, buf1, 16);

	bufflen = min_t(पूर्णांक, 36, scsi_bufflen(srb));
	rtsx_stor_set_xfer_buf(buf2, bufflen, srb);

#अगर_घोषित READ_BYTES_WAIT_INT
	retval = ms_poll_पूर्णांक(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		वापस STATUS_FAIL;
	पूर्ण
#पूर्ण_अगर

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक mg_rsp(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	पूर्णांक i;
	पूर्णांक bufflen;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 buf[32];

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = mg_send_ex_cmd(chip, MG_MAKE_KSE, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		वापस STATUS_FAIL;
	पूर्ण

	bufflen = min_t(पूर्णांक, 12, scsi_bufflen(srb));
	rtsx_stor_get_xfer_buf(buf, bufflen, srb);

	क्रम (i = 0; i < 8; i++)
		buf[i] = buf[4 + i];

	क्रम (i = 0; i < 24; i++)
		buf[8 + i] = 0;

	retval = ms_ग_लिखो_bytes(chip, PRO_WRITE_SHORT_DATA, 32, WAIT_INT,
				buf, 32);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		वापस STATUS_FAIL;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN);
		rtsx_clear_ms_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	ms_card->mg_auth = 1;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक mg_get_ICV(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	पूर्णांक bufflen;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 *buf = शून्य;

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	buf = kदो_स्मृति(1028, GFP_KERNEL);
	अगर (!buf)
		वापस STATUS_ERROR;

	buf[0] = 0x04;
	buf[1] = 0x02;
	buf[2] = 0x00;
	buf[3] = 0x00;

	retval = mg_send_ex_cmd(chip, MG_GET_IBD, ms_card->mg_entry_num);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		जाओ मुक्त_buffer;
	पूर्ण

	retval = ms_transfer_data(chip, MS_TM_AUTO_READ, PRO_READ_LONG_DATA,
				  2, WAIT_INT, 0, 0, buf + 4, 1024);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		rtsx_clear_ms_error(chip);
		जाओ मुक्त_buffer;
	पूर्ण
	अगर (check_ms_err(chip)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		rtsx_clear_ms_error(chip);
		retval = STATUS_FAIL;
		जाओ मुक्त_buffer;
	पूर्ण

	bufflen = min_t(पूर्णांक, 1028, scsi_bufflen(srb));
	rtsx_stor_set_xfer_buf(buf, bufflen, srb);

मुक्त_buffer:
	kमुक्त(buf);
	वापस retval;
पूर्ण

पूर्णांक mg_set_ICV(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	पूर्णांक bufflen;
#अगर_घोषित MG_SET_ICV_SLOW
	पूर्णांक i;
#पूर्ण_अगर
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 *buf = शून्य;

	ms_cleanup_work(chip);

	retval = ms_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	buf = kदो_स्मृति(1028, GFP_KERNEL);
	अगर (!buf)
		वापस STATUS_ERROR;

	bufflen = min_t(पूर्णांक, 1028, scsi_bufflen(srb));
	rtsx_stor_get_xfer_buf(buf, bufflen, srb);

	retval = mg_send_ex_cmd(chip, MG_SET_IBD, ms_card->mg_entry_num);
	अगर (retval != STATUS_SUCCESS) अणु
		अगर (ms_card->mg_auth == 0) अणु
			अगर ((buf[5] & 0xC0) != 0)
				set_sense_type
					(chip, lun,
					SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB);
			अन्यथा
				set_sense_type(chip, lun,
					       SENSE_TYPE_MG_WRITE_ERR);
		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun, SENSE_TYPE_MG_WRITE_ERR);
		पूर्ण
		जाओ set_ICV_finish;
	पूर्ण

#अगर_घोषित MG_SET_ICV_SLOW
	क्रम (i = 0; i < 2; i++) अणु
		udelay(50);

		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC,
			     0xFF, PRO_WRITE_LONG_DATA);
		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, WAIT_INT);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
			     0x01, RING_BUFFER);

		trans_dma_enable(DMA_TO_DEVICE, chip, 512, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANSFER, 0xFF,
			     MS_TRANSFER_START |  MS_TM_NORMAL_WRITE);
		rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANSFER,
			     MS_TRANSFER_END, MS_TRANSFER_END);

		rtsx_send_cmd_no_रुको(chip);

		retval = rtsx_transfer_data(chip, MS_CARD, buf + 4 + i * 512,
					    512, 0, DMA_TO_DEVICE, 3000);
		अगर ((retval < 0) || check_ms_err(chip)) अणु
			rtsx_clear_ms_error(chip);
			अगर (ms_card->mg_auth == 0) अणु
				अगर ((buf[5] & 0xC0) != 0)
					set_sense_type
					    (chip, lun,
					     SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB);
				अन्यथा
					set_sense_type(chip, lun,
						       SENSE_TYPE_MG_WRITE_ERR);
			पूर्ण अन्यथा अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MG_WRITE_ERR);
			पूर्ण
			retval = STATUS_FAIL;
			जाओ set_ICV_finish;
		पूर्ण
	पूर्ण
#अन्यथा
	retval = ms_transfer_data(chip, MS_TM_AUTO_WRITE, PRO_WRITE_LONG_DATA,
				  2, WAIT_INT, 0, 0, buf + 4, 1024);
	अगर ((retval != STATUS_SUCCESS) || check_ms_err(chip)) अणु
		rtsx_clear_ms_error(chip);
		अगर (ms_card->mg_auth == 0) अणु
			अगर ((buf[5] & 0xC0) != 0)
				set_sense_type
				    (chip, lun,
				     SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB);
			अन्यथा
				set_sense_type(chip, lun,
					       SENSE_TYPE_MG_WRITE_ERR);
		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun, SENSE_TYPE_MG_WRITE_ERR);
		पूर्ण
		जाओ set_ICV_finish;
	पूर्ण
#पूर्ण_अगर

set_ICV_finish:
	kमुक्त(buf);
	वापस retval;
पूर्ण

#पूर्ण_अगर /* SUPPORT_MAGIC_GATE */

व्योम ms_cleanup_work(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;

	अगर (CHK_MSPRO(ms_card)) अणु
		अगर (ms_card->seq_mode) अणु
			dev_dbg(rtsx_dev(chip), "MS Pro: stop transmission\n");
			mspro_stop_seq_mode(chip);
			ms_card->cleanup_counter = 0;
		पूर्ण
		अगर (CHK_MSHG(ms_card)) अणु
			rtsx_ग_लिखो_रेजिस्टर(chip, MS_CFG,
					    MS_2K_SECTOR_MODE, 0x00);
		पूर्ण
	पूर्ण
#अगर_घोषित MS_DELAY_WRITE
	अन्यथा अगर ((!CHK_MSPRO(ms_card)) &&
		 ms_card->delay_ग_लिखो.delay_ग_लिखो_flag) अणु
		dev_dbg(rtsx_dev(chip), "MS: delay write\n");
		ms_delay_ग_लिखो(chip);
		ms_card->cleanup_counter = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक ms_घातer_off_card3v3(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = disable_card_घड़ी(chip, MS_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (chip->asic_code) अणु
		retval = ms_pull_ctl_disable(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL,
					     FPGA_MS_PULL_CTL_BIT | 0x20,
					     FPGA_MS_PULL_CTL_BIT);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, MS_OUTPUT_EN, 0);
	अगर (retval)
		वापस retval;

	अगर (!chip->ft2_fast_mode) अणु
		retval = card_घातer_off(chip, MS_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक release_ms_card(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;

#अगर_घोषित MS_DELAY_WRITE
	ms_card->delay_ग_लिखो.delay_ग_लिखो_flag = 0;
#पूर्ण_अगर
	ms_card->pro_under_क्रमmatting = 0;

	chip->card_पढ़ोy &= ~MS_CARD;
	chip->card_fail &= ~MS_CARD;
	chip->card_wp &= ~MS_CARD;

	ms_मुक्त_l2p_tbl(chip);

	स_रखो(ms_card->raw_sys_info, 0, 96);
#अगर_घोषित SUPPORT_PCGL_1P18
	स_रखो(ms_card->raw_model_name, 0, 48);
#पूर्ण_अगर

	retval = ms_घातer_off_card3v3(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण
