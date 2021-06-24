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

#समावेश "rtsx.h"
#समावेश "sd.h"

#घोषणा SD_MAX_RETRY_COUNT	3

अटल u16 REG_SD_CFG1;
अटल u16 REG_SD_CFG2;
अटल u16 REG_SD_CFG3;
अटल u16 REG_SD_STAT1;
अटल u16 REG_SD_STAT2;
अटल u16 REG_SD_BUS_STAT;
अटल u16 REG_SD_PAD_CTL;
अटल u16 REG_SD_SAMPLE_POINT_CTL;
अटल u16 REG_SD_PUSH_POINT_CTL;
अटल u16 REG_SD_CMD0;
अटल u16 REG_SD_CMD1;
अटल u16 REG_SD_CMD2;
अटल u16 REG_SD_CMD3;
अटल u16 REG_SD_CMD4;
अटल u16 REG_SD_CMD5;
अटल u16 REG_SD_BYTE_CNT_L;
अटल u16 REG_SD_BYTE_CNT_H;
अटल u16 REG_SD_BLOCK_CNT_L;
अटल u16 REG_SD_BLOCK_CNT_H;
अटल u16 REG_SD_TRANSFER;
अटल u16 REG_SD_VPCLK0_CTL;
अटल u16 REG_SD_VPCLK1_CTL;
अटल u16 REG_SD_DCMPS0_CTL;
अटल u16 REG_SD_DCMPS1_CTL;

अटल अंतरभूत व्योम sd_set_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;

	sd_card->err_code |= err_code;
पूर्ण

अटल अंतरभूत व्योम sd_clr_err_code(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;

	sd_card->err_code = 0;
पूर्ण

अटल अंतरभूत पूर्णांक sd_check_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;

	वापस sd_card->err_code & err_code;
पूर्ण

अटल व्योम sd_init_reg_addr(काष्ठा rtsx_chip *chip)
अणु
	REG_SD_CFG1 = 0xFD31;
	REG_SD_CFG2 = 0xFD33;
	REG_SD_CFG3 = 0xFD3E;
	REG_SD_STAT1 = 0xFD30;
	REG_SD_STAT2 = 0;
	REG_SD_BUS_STAT = 0;
	REG_SD_PAD_CTL = 0;
	REG_SD_SAMPLE_POINT_CTL = 0;
	REG_SD_PUSH_POINT_CTL = 0;
	REG_SD_CMD0 = 0xFD34;
	REG_SD_CMD1 = 0xFD35;
	REG_SD_CMD2 = 0xFD36;
	REG_SD_CMD3 = 0xFD37;
	REG_SD_CMD4 = 0xFD38;
	REG_SD_CMD5 = 0xFD5A;
	REG_SD_BYTE_CNT_L = 0xFD39;
	REG_SD_BYTE_CNT_H = 0xFD3A;
	REG_SD_BLOCK_CNT_L = 0xFD3B;
	REG_SD_BLOCK_CNT_H = 0xFD3C;
	REG_SD_TRANSFER = 0xFD32;
	REG_SD_VPCLK0_CTL = 0;
	REG_SD_VPCLK1_CTL = 0;
	REG_SD_DCMPS0_CTL = 0;
	REG_SD_DCMPS1_CTL = 0;
पूर्ण

अटल पूर्णांक sd_check_data0_status(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 stat;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, REG_SD_STAT1, &stat);
	अगर (retval)
		वापस retval;

	अगर (!(stat & SD_DAT0_STATUS)) अणु
		sd_set_err_code(chip, SD_BUSY);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_send_cmd_get_rsp(काष्ठा rtsx_chip *chip, u8 cmd_idx,
			       u32 arg, u8 rsp_type, u8 *rsp, पूर्णांक rsp_len)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक समयout = 100;
	u16 reg_addr;
	u8 *ptr;
	पूर्णांक stat_idx = 0;
	पूर्णांक rty_cnt = 0;

	sd_clr_err_code(chip);

	dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d, arg = 0x%08x\n", cmd_idx, arg);

	अगर (rsp_type == SD_RSP_TYPE_R1b)
		समयout = 3000;

RTY_SEND_CMD:

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF, 0x40 | cmd_idx);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD1, 0xFF, (u8)(arg >> 24));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD2, 0xFF, (u8)(arg >> 16));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD3, 0xFF, (u8)(arg >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD4, 0xFF, (u8)arg);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, rsp_type);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER,
		     0xFF, SD_TM_CMD_RSP | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
		     SD_TRANSFER_END | SD_STAT_IDLE, SD_TRANSFER_END |
		     SD_STAT_IDLE);

	अगर (rsp_type == SD_RSP_TYPE_R2) अणु
		क्रम (reg_addr = PPBUF_BASE2; reg_addr < PPBUF_BASE2 + 16;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

		stat_idx = 16;
	पूर्ण अन्यथा अगर (rsp_type != SD_RSP_TYPE_R0) अणु
		क्रम (reg_addr = REG_SD_CMD0; reg_addr <= REG_SD_CMD4;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

		stat_idx = 5;
	पूर्ण

	rtsx_add_cmd(chip, READ_REG_CMD, REG_SD_STAT1, 0, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, समयout);
	अगर (retval < 0) अणु
		u8 val;

		rtsx_पढ़ो_रेजिस्टर(chip, REG_SD_STAT1, &val);
		dev_dbg(rtsx_dev(chip), "SD_STAT1: 0x%x\n", val);

		rtsx_पढ़ो_रेजिस्टर(chip, REG_SD_CFG3, &val);
		dev_dbg(rtsx_dev(chip), "SD_CFG3: 0x%x\n", val);

		अगर (retval == -ETIMEDOUT) अणु
			अगर (rsp_type & SD_WAIT_BUSY_END) अणु
				retval = sd_check_data0_status(chip);
				अगर (retval != STATUS_SUCCESS) अणु
					rtsx_clear_sd_error(chip);
					वापस retval;
				पूर्ण
			पूर्ण अन्यथा अणु
				sd_set_err_code(chip, SD_TO_ERR);
			पूर्ण
			retval = STATUS_TIMEDOUT;
		पूर्ण अन्यथा अणु
			retval = STATUS_FAIL;
		पूर्ण
		rtsx_clear_sd_error(chip);

		वापस retval;
	पूर्ण

	अगर (rsp_type == SD_RSP_TYPE_R0)
		वापस STATUS_SUCCESS;

	ptr = rtsx_get_cmd_data(chip) + 1;

	अगर ((ptr[0] & 0xC0) != 0) अणु
		sd_set_err_code(chip, SD_STS_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (!(rsp_type & SD_NO_CHECK_CRC7)) अणु
		अगर (ptr[stat_idx] & SD_CRC7_ERR) अणु
			अगर (cmd_idx == WRITE_MULTIPLE_BLOCK) अणु
				sd_set_err_code(chip, SD_CRC_ERR);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (rty_cnt < SD_MAX_RETRY_COUNT) अणु
				रुको_समयout(20);
				rty_cnt++;
				जाओ RTY_SEND_CMD;
			पूर्ण अन्यथा अणु
				sd_set_err_code(chip, SD_CRC_ERR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((rsp_type == SD_RSP_TYPE_R1) || (rsp_type == SD_RSP_TYPE_R1b)) अणु
		अगर ((cmd_idx != SEND_RELATIVE_ADDR) &&
		    (cmd_idx != SEND_IF_COND)) अणु
			अगर (cmd_idx != STOP_TRANSMISSION) अणु
				अगर (ptr[1] & 0x80)
					वापस STATUS_FAIL;
			पूर्ण
#अगर_घोषित SUPPORT_SD_LOCK
			अगर (ptr[1] & 0x7D) अणु
#अन्यथा
			अगर (ptr[1] & 0x7F) अणु
#पूर्ण_अगर
				dev_dbg(rtsx_dev(chip), "ptr[1]: 0x%02x\n",
					ptr[1]);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (ptr[2] & 0xFF) अणु
				dev_dbg(rtsx_dev(chip), "ptr[2]: 0x%02x\n",
					ptr[2]);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (ptr[3] & 0x80) अणु
				dev_dbg(rtsx_dev(chip), "ptr[3]: 0x%02x\n",
					ptr[3]);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (ptr[3] & 0x01)
				sd_card->sd_data_buf_पढ़ोy = 1;
			अन्यथा
				sd_card->sd_data_buf_पढ़ोy = 0;
		पूर्ण
	पूर्ण

	अगर (rsp && rsp_len)
		स_नकल(rsp, ptr, rsp_len);

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_पढ़ो_data(काष्ठा rtsx_chip *chip,
			u8 trans_mode, u8 *cmd, पूर्णांक cmd_len, u16 byte_cnt,
			u16 blk_cnt, u8 bus_width, u8 *buf, पूर्णांक buf_len,
			पूर्णांक समयout)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i;

	sd_clr_err_code(chip);

	अगर (!buf)
		buf_len = 0;

	अगर (buf_len > 512)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	अगर (cmd_len) अणु
		dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", cmd[0] - 0x40);
		क्रम (i = 0; i < (min(cmd_len, 6)); i++)
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0 + i,
				     0xFF, cmd[i]);
	पूर्ण
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
		     (u8)byte_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
		     (u8)(byte_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
		     (u8)blk_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
		     (u8)(blk_cnt >> 8));

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1, 0x03, bus_width);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
		     SD_CALCULATE_CRC7 | SD_CHECK_CRC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CRC7 | SD_RSP_LEN_6);
	अगर (trans_mode != SD_TM_AUTO_TUNING)
		rtsx_add_cmd(chip, WRITE_REG_CMD,
			     CARD_DATA_SOURCE, 0x01, PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		     trans_mode | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, SD_CARD, समयout);
	अगर (retval < 0) अणु
		अगर (retval == -ETIMEDOUT) अणु
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, शून्य, 0);
		पूर्ण

		वापस STATUS_FAIL;
	पूर्ण

	अगर (buf && buf_len) अणु
		retval = rtsx_पढ़ो_ppbuf(chip, buf, buf_len);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_ग_लिखो_data(काष्ठा rtsx_chip *chip, u8 trans_mode,
			 u8 *cmd, पूर्णांक cmd_len, u16 byte_cnt, u16 blk_cnt,
			 u8 bus_width, u8 *buf, पूर्णांक buf_len, पूर्णांक समयout)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i;

	sd_clr_err_code(chip);

	अगर (!buf)
		buf_len = 0;

	अगर (buf_len > 512) अणु
		/* This function can't ग_लिखो data more than one page */
		वापस STATUS_FAIL;
	पूर्ण

	अगर (buf && buf_len) अणु
		retval = rtsx_ग_लिखो_ppbuf(chip, buf, buf_len);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	rtsx_init_cmd(chip);

	अगर (cmd_len) अणु
		dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", cmd[0] - 0x40);
		क्रम (i = 0; i < (min(cmd_len, 6)); i++) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     REG_SD_CMD0 + i, 0xFF, cmd[i]);
		पूर्ण
	पूर्ण
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
		     (u8)byte_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
		     (u8)(byte_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
		     (u8)blk_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
		     (u8)(blk_cnt >> 8));

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1, 0x03, bus_width);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
		     SD_CALCULATE_CRC7 | SD_CHECK_CRC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CRC7 | SD_RSP_LEN_6);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		     trans_mode | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, SD_CARD, समयout);
	अगर (retval < 0) अणु
		अगर (retval == -ETIMEDOUT) अणु
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, शून्य, 0);
		पूर्ण

		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_check_csd(काष्ठा rtsx_chip *chip, अक्षर check_wp)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i;
	u8 csd_ver, trans_speed;
	u8 rsp[16];

	क्रम (i = 0; i < 6; i++) अणु
		अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = sd_send_cmd_get_rsp(chip, SEND_CSD, sd_card->sd_addr,
					     SD_RSP_TYPE_R2, rsp, 16);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण

	अगर (i == 6)
		वापस STATUS_FAIL;

	स_नकल(sd_card->raw_csd, rsp + 1, 15);

	dev_dbg(rtsx_dev(chip), "CSD Response:\n");
	dev_dbg(rtsx_dev(chip), "%*ph\n", 16, sd_card->raw_csd);

	csd_ver = (rsp[1] & 0xc0) >> 6;
	dev_dbg(rtsx_dev(chip), "csd_ver = %d\n", csd_ver);

	trans_speed = rsp[4];
	अगर ((trans_speed & 0x07) == 0x02) अणु
		अगर ((trans_speed & 0xf8) >= 0x30) अणु
			अगर (chip->asic_code)
				sd_card->sd_घड़ी = 47;
			अन्यथा
				sd_card->sd_घड़ी = CLK_50;

		पूर्ण अन्यथा अगर ((trans_speed & 0xf8) == 0x28) अणु
			अगर (chip->asic_code)
				sd_card->sd_घड़ी = 39;
			अन्यथा
				sd_card->sd_घड़ी = CLK_40;

		पूर्ण अन्यथा अगर ((trans_speed & 0xf8) == 0x20) अणु
			अगर (chip->asic_code)
				sd_card->sd_घड़ी = 29;
			अन्यथा
				sd_card->sd_घड़ी = CLK_30;

		पूर्ण अन्यथा अगर ((trans_speed & 0xf8) >= 0x10) अणु
			अगर (chip->asic_code)
				sd_card->sd_घड़ी = 23;
			अन्यथा
				sd_card->sd_घड़ी = CLK_20;

		पूर्ण अन्यथा अगर ((trans_speed & 0x08) >= 0x08) अणु
			अगर (chip->asic_code)
				sd_card->sd_घड़ी = 19;
			अन्यथा
				sd_card->sd_घड़ी = CLK_20;
		पूर्ण अन्यथा अणु
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	अगर (CHK_MMC_SECTOR_MODE(sd_card)) अणु
		sd_card->capacity = 0;
	पूर्ण अन्यथा अणु
		अगर ((!CHK_SD_HCXC(sd_card)) || (csd_ver == 0)) अणु
			u8 blk_size, c_size_mult;
			u16 c_size;

			blk_size = rsp[6] & 0x0F;
			c_size =  ((u16)(rsp[7] & 0x03) << 10)
					+ ((u16)rsp[8] << 2)
					+ ((u16)(rsp[9] & 0xC0) >> 6);
			c_size_mult = (u8)((rsp[10] & 0x03) << 1);
			c_size_mult += (rsp[11] & 0x80) >> 7;
			sd_card->capacity = (((u32)(c_size + 1)) *
					(1 << (c_size_mult + 2)))
				<< (blk_size - 9);
		पूर्ण अन्यथा अणु
			u32 total_sector = 0;

			total_sector = (((u32)rsp[8] & 0x3f) << 16) |
				((u32)rsp[9] << 8) | (u32)rsp[10];
			sd_card->capacity = (total_sector + 1) << 10;
		पूर्ण
	पूर्ण

	अगर (check_wp) अणु
		अगर (rsp[15] & 0x30)
			chip->card_wp |= SD_CARD;

		dev_dbg(rtsx_dev(chip), "CSD WP Status: 0x%x\n", rsp[15]);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_set_sample_push_timing(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	काष्ठा sd_info *sd_card = &chip->sd_card;
	u8 val = 0;

	अगर ((chip->sd_ctl & SD_PUSH_POINT_CTL_MASK) == SD_PUSH_POINT_DELAY)
		val |= 0x10;

	अगर ((chip->sd_ctl & SD_SAMPLE_POINT_CTL_MASK) == SD_SAMPLE_POINT_AUTO) अणु
		अगर (chip->asic_code) अणु
			अगर (CHK_SD_HS(sd_card) || CHK_MMC_52M(sd_card)) अणु
				अगर (val & 0x10)
					val |= 0x04;
				अन्यथा
					val |= 0x08;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (val & 0x10)
				val |= 0x04;
			अन्यथा
				val |= 0x08;
		पूर्ण
	पूर्ण अन्यथा अगर ((chip->sd_ctl & SD_SAMPLE_POINT_CTL_MASK) ==
		SD_SAMPLE_POINT_DELAY) अणु
		अगर (val & 0x10)
			val |= 0x04;
		अन्यथा
			val |= 0x08;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x1C, val);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल व्योम sd_choose_proper_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;

	अगर (CHK_SD_SDR104(sd_card)) अणु
		अगर (chip->asic_code)
			sd_card->sd_घड़ी = chip->asic_sd_sdr104_clk;
		अन्यथा
			sd_card->sd_घड़ी = chip->fpga_sd_sdr104_clk;

	पूर्ण अन्यथा अगर (CHK_SD_DDR50(sd_card)) अणु
		अगर (chip->asic_code)
			sd_card->sd_घड़ी = chip->asic_sd_ddr50_clk;
		अन्यथा
			sd_card->sd_घड़ी = chip->fpga_sd_ddr50_clk;

	पूर्ण अन्यथा अगर (CHK_SD_SDR50(sd_card)) अणु
		अगर (chip->asic_code)
			sd_card->sd_घड़ी = chip->asic_sd_sdr50_clk;
		अन्यथा
			sd_card->sd_घड़ी = chip->fpga_sd_sdr50_clk;

	पूर्ण अन्यथा अगर (CHK_SD_HS(sd_card)) अणु
		अगर (chip->asic_code)
			sd_card->sd_घड़ी = chip->asic_sd_hs_clk;
		अन्यथा
			sd_card->sd_घड़ी = chip->fpga_sd_hs_clk;

	पूर्ण अन्यथा अगर (CHK_MMC_52M(sd_card) || CHK_MMC_DDR52(sd_card)) अणु
		अगर (chip->asic_code)
			sd_card->sd_घड़ी = chip->asic_mmc_52m_clk;
		अन्यथा
			sd_card->sd_घड़ी = chip->fpga_mmc_52m_clk;

	पूर्ण अन्यथा अगर (CHK_MMC_26M(sd_card)) अणु
		अगर (chip->asic_code)
			sd_card->sd_घड़ी = 48;
		अन्यथा
			sd_card->sd_घड़ी = CLK_50;
	पूर्ण
पूर्ण

अटल पूर्णांक sd_set_घड़ी_भागider(काष्ठा rtsx_chip *chip, u8 clk_भाग)
अणु
	पूर्णांक retval;
	u8 mask = 0, val = 0;

	mask = 0x60;
	अगर (clk_भाग == SD_CLK_DIVIDE_0)
		val = 0x00;
	अन्यथा अगर (clk_भाग == SD_CLK_DIVIDE_128)
		val = 0x40;
	अन्यथा अगर (clk_भाग == SD_CLK_DIVIDE_256)
		val = 0x20;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, mask, val);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_set_init_para(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	retval = sd_set_sample_push_timing(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	sd_choose_proper_घड़ी(chip);

	retval = चयन_घड़ी(chip, sd_card->sd_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक sd_select_card(काष्ठा rtsx_chip *chip, पूर्णांक select)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd_idx, cmd_type;
	u32 addr;

	अगर (select) अणु
		cmd_idx = SELECT_CARD;
		cmd_type = SD_RSP_TYPE_R1;
		addr = sd_card->sd_addr;
	पूर्ण अन्यथा अणु
		cmd_idx = DESELECT_CARD;
		cmd_type = SD_RSP_TYPE_R0;
		addr = 0;
	पूर्ण

	retval = sd_send_cmd_get_rsp(chip, cmd_idx, addr, cmd_type, शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
अटल पूर्णांक sd_update_lock_status(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 rsp[5];

	retval = sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, rsp, 5);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (rsp[1] & 0x02)
		sd_card->sd_lock_status |= SD_LOCKED;
	अन्यथा
		sd_card->sd_lock_status &= ~SD_LOCKED;

	dev_dbg(rtsx_dev(chip), "sd_card->sd_lock_status = 0x%x\n",
		sd_card->sd_lock_status);

	अगर (rsp[1] & 0x01)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sd_रुको_state_data_पढ़ोy(काष्ठा rtsx_chip *chip, u8 state,
				    u8 data_पढ़ोy, पूर्णांक polling_cnt)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval, i;
	u8 rsp[5];

	क्रम (i = 0; i < polling_cnt; i++) अणु
		retval = sd_send_cmd_get_rsp(chip, SEND_STATUS,
					     sd_card->sd_addr, SD_RSP_TYPE_R1,
					     rsp, 5);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (((rsp[3] & 0x1E) == state) &&
		    ((rsp[3] & 0x01) == data_पढ़ोy))
			वापस STATUS_SUCCESS;
	पूर्ण

	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक sd_change_bank_voltage(काष्ठा rtsx_chip *chip, u8 voltage)
अणु
	पूर्णांक retval;

	अगर (voltage == SD_IO_3V3) अणु
		अगर (chip->asic_code) अणु
			retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x08,
							 0x4FC0 |
							 chip->phy_voltage);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण अन्यथा अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_PAD_CTL,
						     SD_IO_USING_1V8, 0);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण अन्यथा अगर (voltage == SD_IO_1V8) अणु
		अगर (chip->asic_code) अणु
			retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x08,
							 0x4C40 |
							 chip->phy_voltage);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण अन्यथा अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_PAD_CTL,
						     SD_IO_USING_1V8,
						     SD_IO_USING_1V8);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_voltage_चयन(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 stat;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BUS_STAT,
				     SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP,
				     SD_CLK_TOGGLE_EN);
	अगर (retval)
		वापस retval;

	retval = sd_send_cmd_get_rsp(chip, VOLTAGE_SWITCH, 0, SD_RSP_TYPE_R1,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	udelay(chip->sd_voltage_चयन_delay);

	retval = rtsx_पढ़ो_रेजिस्टर(chip, SD_BUS_STAT, &stat);
	अगर (retval)
		वापस retval;
	अगर (stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) अणु
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BUS_STAT, 0xFF,
				     SD_CLK_FORCE_STOP);
	अगर (retval)
		वापस retval;
	retval = sd_change_bank_voltage(chip, SD_IO_1V8);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	रुको_समयout(50);

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BUS_STAT, 0xFF,
				     SD_CLK_TOGGLE_EN);
	अगर (retval)
		वापस retval;
	रुको_समयout(10);

	retval = rtsx_पढ़ो_रेजिस्टर(chip, SD_BUS_STAT, &stat);
	अगर (retval)
		वापस retval;
	अगर ((stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) !=
			(SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) अणु
		dev_dbg(rtsx_dev(chip), "SD_BUS_STAT: 0x%x\n", stat);
		rtsx_ग_लिखो_रेजिस्टर(chip, SD_BUS_STAT, SD_CLK_TOGGLE_EN |
				    SD_CLK_FORCE_STOP, 0);
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_CLK_EN, 0xFF, 0);
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BUS_STAT,
				     SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_reset_dcm(काष्ठा rtsx_chip *chip, u8 tune_dir)
अणु
	पूर्णांक retval;

	अगर (tune_dir == TUNE_RX) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, DCM_DRP_CTL, 0xFF,
					     DCM_RESET | DCM_RX);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, DCM_DRP_CTL, 0xFF, DCM_RX);
		अगर (retval)
			वापस retval;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, DCM_DRP_CTL, 0xFF,
					     DCM_RESET | DCM_TX);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, DCM_DRP_CTL, 0xFF, DCM_TX);
		अगर (retval)
			वापस retval;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_change_phase(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक, u8 tune_dir)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	u16 SD_VP_CTL, SD_DCMPS_CTL;
	u8 val;
	पूर्णांक retval;
	bool ddr_rx = false;

	dev_dbg(rtsx_dev(chip), "%s (sample_point = %d, tune_dir = %d)\n",
		__func__, sample_poपूर्णांक, tune_dir);

	अगर (tune_dir == TUNE_RX) अणु
		SD_VP_CTL = SD_VPRX_CTL;
		SD_DCMPS_CTL = SD_DCMPS_RX_CTL;
		अगर (CHK_SD_DDR50(sd_card))
			ddr_rx = true;
	पूर्ण अन्यथा अणु
		SD_VP_CTL = SD_VPTX_CTL;
		SD_DCMPS_CTL = SD_DCMPS_TX_CTL;
	पूर्ण

	अगर (chip->asic_code) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL, CHANGE_CLK,
					     CHANGE_CLK);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VP_CTL, 0x1F,
					     sample_poपूर्णांक);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VPCLK0_CTL,
					     PHASE_NOT_RESET, 0);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VPCLK0_CTL,
					     PHASE_NOT_RESET, PHASE_NOT_RESET);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL, CHANGE_CLK, 0);
		अगर (retval)
			वापस retval;
	पूर्ण अन्यथा अणु
		rtsx_पढ़ो_रेजिस्टर(chip, SD_VP_CTL, &val);
		dev_dbg(rtsx_dev(chip), "SD_VP_CTL: 0x%x\n", val);
		rtsx_पढ़ो_रेजिस्टर(chip, SD_DCMPS_CTL, &val);
		dev_dbg(rtsx_dev(chip), "SD_DCMPS_CTL: 0x%x\n", val);

		अगर (ddr_rx) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VP_CTL,
						     PHASE_CHANGE,
						     PHASE_CHANGE);
			अगर (retval)
				वापस retval;
			udelay(50);
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VP_CTL, 0xFF,
						     PHASE_CHANGE |
						     PHASE_NOT_RESET |
						     sample_poपूर्णांक);
			अगर (retval)
				वापस retval;
		पूर्ण अन्यथा अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL,
						     CHANGE_CLK, CHANGE_CLK);
			अगर (retval)
				वापस retval;
			udelay(50);
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VP_CTL, 0xFF,
						     PHASE_NOT_RESET |
						     sample_poपूर्णांक);
			अगर (retval)
				वापस retval;
		पूर्ण
		udelay(100);

		rtsx_init_cmd(chip);
		rtsx_add_cmd(chip, WRITE_REG_CMD, SD_DCMPS_CTL, DCMPS_CHANGE,
			     DCMPS_CHANGE);
		rtsx_add_cmd(chip, CHECK_REG_CMD, SD_DCMPS_CTL,
			     DCMPS_CHANGE_DONE, DCMPS_CHANGE_DONE);
		retval = rtsx_send_cmd(chip, SD_CARD, 100);
		अगर (retval != STATUS_SUCCESS)
			जाओ fail;

		val = *rtsx_get_cmd_data(chip);
		अगर (val & DCMPS_ERROR)
			जाओ fail;

		अगर ((val & DCMPS_CURRENT_PHASE) != sample_poपूर्णांक)
			जाओ fail;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_DCMPS_CTL,
					     DCMPS_CHANGE, 0);
		अगर (retval)
			वापस retval;
		अगर (ddr_rx) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VP_CTL,
						     PHASE_CHANGE, 0);
			अगर (retval)
				वापस retval;
		पूर्ण अन्यथा अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL,
						     CHANGE_CLK, 0);
			अगर (retval)
				वापस retval;
		पूर्ण

		udelay(50);
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG1, SD_ASYNC_FIFO_NOT_RST, 0);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;

fail:
	rtsx_पढ़ो_रेजिस्टर(chip, SD_VP_CTL, &val);
	dev_dbg(rtsx_dev(chip), "SD_VP_CTL: 0x%x\n", val);
	rtsx_पढ़ो_रेजिस्टर(chip, SD_DCMPS_CTL, &val);
	dev_dbg(rtsx_dev(chip), "SD_DCMPS_CTL: 0x%x\n", val);

	rtsx_ग_लिखो_रेजिस्टर(chip, SD_DCMPS_CTL, DCMPS_CHANGE, 0);
	rtsx_ग_लिखो_रेजिस्टर(chip, SD_VP_CTL, PHASE_CHANGE, 0);
	mdelay(10);
	sd_reset_dcm(chip, tune_dir);
	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक sd_check_spec(काष्ठा rtsx_chip *chip, u8 bus_width)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd[5], buf[8];

	retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	cmd[0] = 0x40 | SEND_SCR;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, 8, 1, bus_width,
			      buf, 8, 250);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_sd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	स_नकल(sd_card->raw_scr, buf, 8);

	अगर ((buf[0] & 0x0F) == 0)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_query_चयन_result(काष्ठा rtsx_chip *chip, u8 func_group,
				  u8 func_to_चयन, u8 *buf, पूर्णांक buf_len)
अणु
	u8 support_mask = 0, query_चयन = 0, चयन_busy = 0;
	पूर्णांक support_offset = 0, query_चयन_offset = 0, check_busy_offset = 0;

	अगर (func_group == SD_FUNC_GROUP_1) अणु
		support_offset = FUNCTION_GROUP1_SUPPORT_OFFSET;
		query_चयन_offset = FUNCTION_GROUP1_QUERY_SWITCH_OFFSET;
		check_busy_offset = FUNCTION_GROUP1_CHECK_BUSY_OFFSET;

		चयन (func_to_चयन) अणु
		हाल HS_SUPPORT:
			support_mask = HS_SUPPORT_MASK;
			query_चयन = HS_QUERY_SWITCH_OK;
			चयन_busy = HS_SWITCH_BUSY;
			अवरोध;

		हाल SDR50_SUPPORT:
			support_mask = SDR50_SUPPORT_MASK;
			query_चयन = SDR50_QUERY_SWITCH_OK;
			चयन_busy = SDR50_SWITCH_BUSY;
			अवरोध;

		हाल SDR104_SUPPORT:
			support_mask = SDR104_SUPPORT_MASK;
			query_चयन = SDR104_QUERY_SWITCH_OK;
			चयन_busy = SDR104_SWITCH_BUSY;
			अवरोध;

		हाल DDR50_SUPPORT:
			support_mask = DDR50_SUPPORT_MASK;
			query_चयन = DDR50_QUERY_SWITCH_OK;
			चयन_busy = DDR50_SWITCH_BUSY;
			अवरोध;

		शेष:
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अगर (func_group == SD_FUNC_GROUP_3) अणु
		support_offset = FUNCTION_GROUP3_SUPPORT_OFFSET;
		query_चयन_offset = FUNCTION_GROUP3_QUERY_SWITCH_OFFSET;
		check_busy_offset = FUNCTION_GROUP3_CHECK_BUSY_OFFSET;

		चयन (func_to_चयन) अणु
		हाल DRIVING_TYPE_A:
			support_mask = DRIVING_TYPE_A_MASK;
			query_चयन = TYPE_A_QUERY_SWITCH_OK;
			चयन_busy = TYPE_A_SWITCH_BUSY;
			अवरोध;

		हाल DRIVING_TYPE_C:
			support_mask = DRIVING_TYPE_C_MASK;
			query_चयन = TYPE_C_QUERY_SWITCH_OK;
			चयन_busy = TYPE_C_SWITCH_BUSY;
			अवरोध;

		हाल DRIVING_TYPE_D:
			support_mask = DRIVING_TYPE_D_MASK;
			query_चयन = TYPE_D_QUERY_SWITCH_OK;
			चयन_busy = TYPE_D_SWITCH_BUSY;
			अवरोध;

		शेष:
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अगर (func_group == SD_FUNC_GROUP_4) अणु
		support_offset = FUNCTION_GROUP4_SUPPORT_OFFSET;
		query_चयन_offset = FUNCTION_GROUP4_QUERY_SWITCH_OFFSET;
		check_busy_offset = FUNCTION_GROUP4_CHECK_BUSY_OFFSET;

		चयन (func_to_चयन) अणु
		हाल CURRENT_LIMIT_400:
			support_mask = CURRENT_LIMIT_400_MASK;
			query_चयन = CURRENT_LIMIT_400_QUERY_SWITCH_OK;
			चयन_busy = CURRENT_LIMIT_400_SWITCH_BUSY;
			अवरोध;

		हाल CURRENT_LIMIT_600:
			support_mask = CURRENT_LIMIT_600_MASK;
			query_चयन = CURRENT_LIMIT_600_QUERY_SWITCH_OK;
			चयन_busy = CURRENT_LIMIT_600_SWITCH_BUSY;
			अवरोध;

		हाल CURRENT_LIMIT_800:
			support_mask = CURRENT_LIMIT_800_MASK;
			query_चयन = CURRENT_LIMIT_800_QUERY_SWITCH_OK;
			चयन_busy = CURRENT_LIMIT_800_SWITCH_BUSY;
			अवरोध;

		शेष:
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	अगर (func_group == SD_FUNC_GROUP_1) अणु
		अगर (!(buf[support_offset] & support_mask) ||
		    ((buf[query_चयन_offset] & 0x0F) != query_चयन)) अणु
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	/* Check 'Busy Status' */
	अगर ((buf[DATA_STRUCTURE_VER_OFFSET] == 0x01) &&
	    ((buf[check_busy_offset] & चयन_busy) == चयन_busy)) अणु
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_check_चयन_mode(काष्ठा rtsx_chip *chip, u8 mode, u8 func_group,
				u8 func_to_चयन, u8 bus_width)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd[5], buf[64];

	dev_dbg(rtsx_dev(chip), "%s (mode = %d, func_group = %d, func_to_switch = %d)\n",
		__func__, mode, func_group, func_to_चयन);

	cmd[0] = 0x40 | SWITCH;
	cmd[1] = mode;

	अगर (func_group == SD_FUNC_GROUP_1) अणु
		cmd[2] = 0xFF;
		cmd[3] = 0xFF;
		cmd[4] = 0xF0 + func_to_चयन;
	पूर्ण अन्यथा अगर (func_group == SD_FUNC_GROUP_3) अणु
		cmd[2] = 0xFF;
		cmd[3] = 0xF0 + func_to_चयन;
		cmd[4] = 0xFF;
	पूर्ण अन्यथा अगर (func_group == SD_FUNC_GROUP_4) अणु
		cmd[2] = 0xFF;
		cmd[3] = 0x0F + (func_to_चयन << 4);
		cmd[4] = 0xFF;
	पूर्ण अन्यथा अणु
		cmd[1] = SD_CHECK_MODE;
		cmd[2] = 0xFF;
		cmd[3] = 0xFF;
		cmd[4] = 0xFF;
	पूर्ण

	retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, 64, 1, bus_width,
			      buf, 64, 250);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_sd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "%*ph\n", 64, buf);

	अगर (func_group == NO_ARGUMENT) अणु
		sd_card->func_group1_mask = buf[0x0D];
		sd_card->func_group2_mask = buf[0x0B];
		sd_card->func_group3_mask = buf[0x09];
		sd_card->func_group4_mask = buf[0x07];

		dev_dbg(rtsx_dev(chip), "func_group1_mask = 0x%02x\n",
			buf[0x0D]);
		dev_dbg(rtsx_dev(chip), "func_group2_mask = 0x%02x\n",
			buf[0x0B]);
		dev_dbg(rtsx_dev(chip), "func_group3_mask = 0x%02x\n",
			buf[0x09]);
		dev_dbg(rtsx_dev(chip), "func_group4_mask = 0x%02x\n",
			buf[0x07]);
	पूर्ण अन्यथा अणु
		/* Maximum current consumption, check whether current is
		 * acceptable; bit[511:496] = 0x0000 means some error happened.
		 */
		u16 cc = ((u16)buf[0] << 8) | buf[1];

		dev_dbg(rtsx_dev(chip), "Maximum current consumption: %dmA\n",
			cc);
		अगर ((cc == 0) || (cc > 800))
			वापस STATUS_FAIL;

		retval = sd_query_चयन_result(chip, func_group,
						func_to_चयन, buf, 64);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर ((cc > 400) || (func_to_चयन > CURRENT_LIMIT_400)) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, OCPPARA2,
						     SD_OCP_THD_MASK,
						     chip->sd_800mA_ocp_thd);
			अगर (retval)
				वापस retval;
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PWR_CTL,
						     PMOS_STRG_MASK,
						     PMOS_STRG_800mA);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल u8 करोwngrade_चयन_mode(u8 func_group, u8 func_to_चयन)
अणु
	अगर (func_group == SD_FUNC_GROUP_1) अणु
		अगर (func_to_चयन > HS_SUPPORT)
			func_to_चयन--;

	पूर्ण अन्यथा अगर (func_group == SD_FUNC_GROUP_4) अणु
		अगर (func_to_चयन > CURRENT_LIMIT_200)
			func_to_चयन--;
	पूर्ण

	वापस func_to_चयन;
पूर्ण

अटल पूर्णांक sd_check_चयन(काष्ठा rtsx_chip *chip,
			   u8 func_group, u8 func_to_चयन, u8 bus_width)
अणु
	पूर्णांक retval;
	पूर्णांक i;
	bool चयन_good = false;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = sd_check_चयन_mode(chip, SD_CHECK_MODE, func_group,
					      func_to_चयन, bus_width);
		अगर (retval == STATUS_SUCCESS) अणु
			u8 stat;

			retval = sd_check_चयन_mode(chip, SD_SWITCH_MODE,
						      func_group,
						      func_to_चयन,
						      bus_width);
			अगर (retval == STATUS_SUCCESS) अणु
				चयन_good = true;
				अवरोध;
			पूर्ण

			retval = rtsx_पढ़ो_रेजिस्टर(chip, SD_STAT1, &stat);
			अगर (retval)
				वापस retval;
			अगर (stat & SD_CRC16_ERR) अणु
				dev_dbg(rtsx_dev(chip), "SD CRC16 error when switching mode\n");
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		func_to_चयन = करोwngrade_चयन_mode(func_group,
						       func_to_चयन);

		रुको_समयout(20);
	पूर्ण

	अगर (!चयन_good)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_चयन_function(काष्ठा rtsx_chip *chip, u8 bus_width)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i;
	u8 func_to_चयन = 0;

	/* Get supported functions */
	retval = sd_check_चयन_mode(chip, SD_CHECK_MODE, NO_ARGUMENT,
				      NO_ARGUMENT, bus_width);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	sd_card->func_group1_mask &= ~(sd_card->sd_चयन_fail);

	/* Function Group 1: Access Mode */
	क्रम (i = 0; i < 4; i++) अणु
		चयन ((u8)(chip->sd_speed_prior >> (i * 8))) अणु
		हाल SDR104_SUPPORT:
			अगर ((sd_card->func_group1_mask & SDR104_SUPPORT_MASK) &&
			    chip->sdr104_en) अणु
				func_to_चयन = SDR104_SUPPORT;
			पूर्ण
			अवरोध;

		हाल DDR50_SUPPORT:
			अगर ((sd_card->func_group1_mask & DDR50_SUPPORT_MASK) &&
			    chip->ddr50_en) अणु
				func_to_चयन = DDR50_SUPPORT;
			पूर्ण
			अवरोध;

		हाल SDR50_SUPPORT:
			अगर ((sd_card->func_group1_mask & SDR50_SUPPORT_MASK) &&
			    chip->sdr50_en) अणु
				func_to_चयन = SDR50_SUPPORT;
			पूर्ण
			अवरोध;

		हाल HS_SUPPORT:
			अगर (sd_card->func_group1_mask & HS_SUPPORT_MASK)
				func_to_चयन = HS_SUPPORT;

			अवरोध;

		शेष:
			जारी;
		पूर्ण

		अगर (func_to_चयन)
			अवरोध;
	पूर्ण
	dev_dbg(rtsx_dev(chip), "SD_FUNC_GROUP_1: func_to_switch = 0x%02x",
		func_to_चयन);

#अगर_घोषित SUPPORT_SD_LOCK
	अगर ((sd_card->sd_lock_status & SD_SDR_RST) &&
	    (func_to_चयन == DDR50_SUPPORT) &&
	    (sd_card->func_group1_mask & SDR50_SUPPORT_MASK)) अणु
		func_to_चयन = SDR50_SUPPORT;
		dev_dbg(rtsx_dev(chip), "Using SDR50 instead of DDR50 for SD Lock\n");
	पूर्ण
#पूर्ण_अगर

	अगर (func_to_चयन) अणु
		retval = sd_check_चयन(chip, SD_FUNC_GROUP_1, func_to_चयन,
					 bus_width);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (func_to_चयन == SDR104_SUPPORT) अणु
				sd_card->sd_चयन_fail = SDR104_SUPPORT_MASK;
			पूर्ण अन्यथा अगर (func_to_चयन == DDR50_SUPPORT) अणु
				sd_card->sd_चयन_fail = SDR104_SUPPORT_MASK |
					DDR50_SUPPORT_MASK;
			पूर्ण अन्यथा अगर (func_to_चयन == SDR50_SUPPORT) अणु
				sd_card->sd_चयन_fail = SDR104_SUPPORT_MASK |
					DDR50_SUPPORT_MASK | SDR50_SUPPORT_MASK;
			पूर्ण
			वापस STATUS_FAIL;
		पूर्ण

		अगर (func_to_चयन == SDR104_SUPPORT)
			SET_SD_SDR104(sd_card);
		अन्यथा अगर (func_to_चयन == DDR50_SUPPORT)
			SET_SD_DDR50(sd_card);
		अन्यथा अगर (func_to_चयन == SDR50_SUPPORT)
			SET_SD_SDR50(sd_card);
		अन्यथा
			SET_SD_HS(sd_card);
	पूर्ण

	अगर (CHK_SD_DDR50(sd_card)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_PUSH_POINT_CTL, 0x06,
					     0x04);
		अगर (retval)
			वापस retval;
		retval = sd_set_sample_push_timing(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	अगर (!func_to_चयन || (func_to_चयन == HS_SUPPORT)) अणु
		/* Do not try to चयन current limit अगर the card करोesn't
		 * support UHS mode or we करोn't want it to support UHS mode
		 */
		वापस STATUS_SUCCESS;
	पूर्ण

	/* Function Group 4: Current Limit */
	func_to_चयन = 0xFF;

	क्रम (i = 0; i < 4; i++) अणु
		चयन ((u8)(chip->sd_current_prior >> (i * 8))) अणु
		हाल CURRENT_LIMIT_800:
			अगर (sd_card->func_group4_mask & CURRENT_LIMIT_800_MASK)
				func_to_चयन = CURRENT_LIMIT_800;

			अवरोध;

		हाल CURRENT_LIMIT_600:
			अगर (sd_card->func_group4_mask & CURRENT_LIMIT_600_MASK)
				func_to_चयन = CURRENT_LIMIT_600;

			अवरोध;

		हाल CURRENT_LIMIT_400:
			अगर (sd_card->func_group4_mask & CURRENT_LIMIT_400_MASK)
				func_to_चयन = CURRENT_LIMIT_400;

			अवरोध;

		हाल CURRENT_LIMIT_200:
			अगर (sd_card->func_group4_mask & CURRENT_LIMIT_200_MASK)
				func_to_चयन = CURRENT_LIMIT_200;

			अवरोध;

		शेष:
			जारी;
		पूर्ण

		अगर (func_to_चयन != 0xFF)
			अवरोध;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "SD_FUNC_GROUP_4: func_to_switch = 0x%02x",
		func_to_चयन);

	अगर (func_to_चयन <= CURRENT_LIMIT_800) अणु
		retval = sd_check_चयन(chip, SD_FUNC_GROUP_4, func_to_चयन,
					 bus_width);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (sd_check_err_code(chip, SD_NO_CARD))
				वापस STATUS_FAIL;
		पूर्ण
		dev_dbg(rtsx_dev(chip), "Switch current limit finished! (%d)\n",
			retval);
	पूर्ण

	अगर (CHK_SD_DDR50(sd_card)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_PUSH_POINT_CTL, 0x06, 0);
		अगर (retval)
			वापस retval;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_रुको_data_idle(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval = STATUS_TIMEDOUT;
	पूर्णांक i;
	u8 val = 0;

	क्रम (i = 0; i < 100; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, SD_DATA_STATE, &val);
		अगर (retval)
			वापस retval;
		अगर (val & SD_DATA_IDLE) अणु
			retval = STATUS_SUCCESS;
			अवरोध;
		पूर्ण
		udelay(100);
	पूर्ण
	dev_dbg(rtsx_dev(chip), "SD_DATA_STATE: 0x%02x\n", val);

	वापस retval;
पूर्ण

अटल पूर्णांक sd_sdr_tuning_rx_cmd(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक)
अणु
	पूर्णांक retval;
	u8 cmd[5];

	retval = sd_change_phase(chip, sample_poपूर्णांक, TUNE_RX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	cmd[0] = 0x40 | SEND_TUNING_PATTERN;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_पढ़ो_data(chip, SD_TM_AUTO_TUNING, cmd, 5, 0x40, 1,
			      SD_BUS_WIDTH_4, शून्य, 0, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		(व्योम)sd_रुको_data_idle(chip);

		rtsx_clear_sd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_ddr_tuning_rx_cmd(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd[5];

	retval = sd_change_phase(chip, sample_poपूर्णांक, TUNE_RX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "sd ddr tuning rx\n");

	retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	cmd[0] = 0x40 | SD_STATUS;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, 64, 1,
			      SD_BUS_WIDTH_4, शून्य, 0, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		(व्योम)sd_रुको_data_idle(chip);

		rtsx_clear_sd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक mmc_ddr_tuning_rx_cmd(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd[5], bus_width;

	अगर (CHK_MMC_8BIT(sd_card))
		bus_width = SD_BUS_WIDTH_8;
	अन्यथा अगर (CHK_MMC_4BIT(sd_card))
		bus_width = SD_BUS_WIDTH_4;
	अन्यथा
		bus_width = SD_BUS_WIDTH_1;

	retval = sd_change_phase(chip, sample_poपूर्णांक, TUNE_RX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "mmc ddr tuning rx\n");

	cmd[0] = 0x40 | SEND_EXT_CSD;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, 0x200, 1,
			      bus_width, शून्य, 0, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		(व्योम)sd_रुको_data_idle(chip);

		rtsx_clear_sd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_sdr_tuning_tx_cmd(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	retval = sd_change_phase(chip, sample_poपूर्णांक, TUNE_TX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     SD_RSP_80CLK_TIMEOUT_EN);
	अगर (retval)
		वापस retval;

	retval = sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, शून्य, 0);
	अगर (retval != STATUS_SUCCESS) अणु
		अगर (sd_check_err_code(chip, SD_RSP_TIMEOUT)) अणु
			rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3,
					    SD_RSP_80CLK_TIMEOUT_EN, 0);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     0);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_ddr_tuning_tx_cmd(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd[5], bus_width;

	retval = sd_change_phase(chip, sample_poपूर्णांक, TUNE_TX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_SD(sd_card)) अणु
		bus_width = SD_BUS_WIDTH_4;
	पूर्ण अन्यथा अणु
		अगर (CHK_MMC_8BIT(sd_card))
			bus_width = SD_BUS_WIDTH_8;
		अन्यथा अगर (CHK_MMC_4BIT(sd_card))
			bus_width = SD_BUS_WIDTH_4;
		अन्यथा
			bus_width = SD_BUS_WIDTH_1;
	पूर्ण

	retval = sd_रुको_state_data_पढ़ोy(chip, 0x08, 1, 1000);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     SD_RSP_80CLK_TIMEOUT_EN);
	अगर (retval)
		वापस retval;

	cmd[0] = 0x40 | PROGRAM_CSD;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_ग_लिखो_data(chip, SD_TM_AUTO_WRITE_2, cmd, 5, 16, 1,
			       bus_width, sd_card->raw_csd, 16, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_sd_error(chip);
		rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN, 0);
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     0);
	अगर (retval)
		वापस retval;

	sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr, SD_RSP_TYPE_R1,
			    शून्य, 0);

	वापस STATUS_SUCCESS;
पूर्ण

अटल u8 sd_search_final_phase(काष्ठा rtsx_chip *chip, u32 phase_map,
				u8 tune_dir)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	काष्ठा timing_phase_path path[MAX_PHASE + 1];
	पूर्णांक i, j, cont_path_cnt;
	bool new_block;
	पूर्णांक max_len, final_path_idx;
	u8 final_phase = 0xFF;

	अगर (phase_map == 0xFFFFFFFF) अणु
		अगर (tune_dir == TUNE_RX)
			final_phase = (u8)chip->sd_शेष_rx_phase;
		अन्यथा
			final_phase = (u8)chip->sd_शेष_tx_phase;

		जाओ search_finish;
	पूर्ण

	cont_path_cnt = 0;
	new_block = true;
	j = 0;
	क्रम (i = 0; i < MAX_PHASE + 1; i++) अणु
		अगर (phase_map & (1 << i)) अणु
			अगर (new_block) अणु
				new_block = false;
				j = cont_path_cnt++;
				path[j].start = i;
				path[j].end = i;
			पूर्ण अन्यथा अणु
				path[j].end = i;
			पूर्ण
		पूर्ण अन्यथा अणु
			new_block = true;
			अगर (cont_path_cnt) अणु
				पूर्णांक idx = cont_path_cnt - 1;

				path[idx].len = path[idx].end -
					path[idx].start + 1;
				path[idx].mid = path[idx].start +
					path[idx].len / 2;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cont_path_cnt == 0) अणु
		dev_dbg(rtsx_dev(chip), "No continuous phase path\n");
		जाओ search_finish;
	पूर्ण अन्यथा अणु
		पूर्णांक idx = cont_path_cnt - 1;

		path[idx].len = path[idx].end - path[idx].start + 1;
		path[idx].mid = path[idx].start + path[idx].len / 2;
	पूर्ण

	अगर ((path[0].start == 0) &&
	    (path[cont_path_cnt - 1].end == MAX_PHASE)) अणु
		path[0].start = path[cont_path_cnt - 1].start - MAX_PHASE - 1;
		path[0].len += path[cont_path_cnt - 1].len;
		path[0].mid = path[0].start + path[0].len / 2;
		अगर (path[0].mid < 0)
			path[0].mid += MAX_PHASE + 1;

		cont_path_cnt--;
	पूर्ण

	max_len = 0;
	final_phase = 0;
	final_path_idx = 0;
	क्रम (i = 0; i < cont_path_cnt; i++) अणु
		अगर (path[i].len > max_len) अणु
			max_len = path[i].len;
			final_phase = (u8)path[i].mid;
			final_path_idx = i;
		पूर्ण

		dev_dbg(rtsx_dev(chip), "path[%d].start = %d\n",
			i, path[i].start);
		dev_dbg(rtsx_dev(chip), "path[%d].end = %d\n", i, path[i].end);
		dev_dbg(rtsx_dev(chip), "path[%d].len = %d\n", i, path[i].len);
		dev_dbg(rtsx_dev(chip), "path[%d].mid = %d\n", i, path[i].mid);
		dev_dbg(rtsx_dev(chip), "\n");
	पूर्ण

	अगर (tune_dir == TUNE_TX) अणु
		अगर (CHK_SD_SDR104(sd_card)) अणु
			अगर (max_len > 15) अणु
				पूर्णांक temp_mid = (max_len - 16) / 2;
				पूर्णांक temp_final_phase =
					path[final_path_idx].end -
					(max_len - (6 + temp_mid));

				अगर (temp_final_phase < 0)
					final_phase = (u8)(temp_final_phase +
							MAX_PHASE + 1);
				अन्यथा
					final_phase = (u8)temp_final_phase;
			पूर्ण
		पूर्ण अन्यथा अगर (CHK_SD_SDR50(sd_card)) अणु
			अगर (max_len > 12) अणु
				पूर्णांक temp_mid = (max_len - 13) / 2;
				पूर्णांक temp_final_phase =
					path[final_path_idx].end -
					(max_len - (3 + temp_mid));

				अगर (temp_final_phase < 0)
					final_phase = (u8)(temp_final_phase +
							MAX_PHASE + 1);
				अन्यथा
					final_phase = (u8)temp_final_phase;
			पूर्ण
		पूर्ण
	पूर्ण

search_finish:
	dev_dbg(rtsx_dev(chip), "Final chosen phase: %d\n", final_phase);
	वापस final_phase;
पूर्ण

अटल पूर्णांक sd_tuning_rx(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i, j;
	u32 raw_phase_map[3], phase_map;
	u8 final_phase;
	पूर्णांक (*tuning_cmd)(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक);

	अगर (CHK_SD(sd_card)) अणु
		अगर (CHK_SD_DDR50(sd_card))
			tuning_cmd = sd_ddr_tuning_rx_cmd;
		अन्यथा
			tuning_cmd = sd_sdr_tuning_rx_cmd;

	पूर्ण अन्यथा अणु
		अगर (CHK_MMC_DDR52(sd_card))
			tuning_cmd = mmc_ddr_tuning_rx_cmd;
		अन्यथा
			वापस STATUS_FAIL;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		raw_phase_map[i] = 0;
		क्रम (j = MAX_PHASE; j >= 0; j--) अणु
			अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
				sd_set_err_code(chip, SD_NO_CARD);
				वापस STATUS_FAIL;
			पूर्ण

			retval = tuning_cmd(chip, (u8)j);
			अगर (retval == STATUS_SUCCESS)
				raw_phase_map[i] |= 1 << j;
		पूर्ण
	पूर्ण

	phase_map = raw_phase_map[0] & raw_phase_map[1] & raw_phase_map[2];
	क्रम (i = 0; i < 3; i++)
		dev_dbg(rtsx_dev(chip), "RX raw_phase_map[%d] = 0x%08x\n",
			i, raw_phase_map[i]);

	dev_dbg(rtsx_dev(chip), "RX phase_map = 0x%08x\n", phase_map);

	final_phase = sd_search_final_phase(chip, phase_map, TUNE_RX);
	अगर (final_phase == 0xFF)
		वापस STATUS_FAIL;

	retval = sd_change_phase(chip, final_phase, TUNE_RX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_ddr_pre_tuning_tx(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i;
	u32 phase_map;
	u8 final_phase;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     SD_RSP_80CLK_TIMEOUT_EN);
	अगर (retval)
		वापस retval;

	phase_map = 0;
	क्रम (i = MAX_PHASE; i >= 0; i--) अणु
		अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_NO_CARD);
			rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3,
					    SD_RSP_80CLK_TIMEOUT_EN, 0);
			वापस STATUS_FAIL;
		पूर्ण

		retval = sd_change_phase(chip, (u8)i, TUNE_TX);
		अगर (retval != STATUS_SUCCESS)
			जारी;

		retval = sd_send_cmd_get_rsp(chip, SEND_STATUS,
					     sd_card->sd_addr, SD_RSP_TYPE_R1,
					     शून्य, 0);
		अगर ((retval == STATUS_SUCCESS) ||
		    !sd_check_err_code(chip, SD_RSP_TIMEOUT))
			phase_map |= 1 << i;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     0);
	अगर (retval)
		वापस retval;

	dev_dbg(rtsx_dev(chip), "DDR TX pre tune phase_map = 0x%08x\n",
		phase_map);

	final_phase = sd_search_final_phase(chip, phase_map, TUNE_TX);
	अगर (final_phase == 0xFF)
		वापस STATUS_FAIL;

	retval = sd_change_phase(chip, final_phase, TUNE_TX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "DDR TX pre tune phase: %d\n",
		(पूर्णांक)final_phase);

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_tuning_tx(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक i, j;
	u32 raw_phase_map[3], phase_map;
	u8 final_phase;
	पूर्णांक (*tuning_cmd)(काष्ठा rtsx_chip *chip, u8 sample_poपूर्णांक);

	अगर (CHK_SD(sd_card)) अणु
		अगर (CHK_SD_DDR50(sd_card))
			tuning_cmd = sd_ddr_tuning_tx_cmd;
		अन्यथा
			tuning_cmd = sd_sdr_tuning_tx_cmd;

	पूर्ण अन्यथा अणु
		अगर (CHK_MMC_DDR52(sd_card))
			tuning_cmd = sd_ddr_tuning_tx_cmd;
		अन्यथा
			वापस STATUS_FAIL;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		raw_phase_map[i] = 0;
		क्रम (j = MAX_PHASE; j >= 0; j--) अणु
			अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
				sd_set_err_code(chip, SD_NO_CARD);
				rtsx_ग_लिखो_रेजिस्टर(chip, SD_CFG3,
						    SD_RSP_80CLK_TIMEOUT_EN, 0);
				वापस STATUS_FAIL;
			पूर्ण

			retval = tuning_cmd(chip, (u8)j);
			अगर (retval == STATUS_SUCCESS)
				raw_phase_map[i] |= 1 << j;
		पूर्ण
	पूर्ण

	phase_map = raw_phase_map[0] & raw_phase_map[1] & raw_phase_map[2];
	क्रम (i = 0; i < 3; i++)
		dev_dbg(rtsx_dev(chip), "TX raw_phase_map[%d] = 0x%08x\n",
			i, raw_phase_map[i]);

	dev_dbg(rtsx_dev(chip), "TX phase_map = 0x%08x\n", phase_map);

	final_phase = sd_search_final_phase(chip, phase_map, TUNE_TX);
	अगर (final_phase == 0xFF)
		वापस STATUS_FAIL;

	retval = sd_change_phase(chip, final_phase, TUNE_TX);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_sdr_tuning(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = sd_tuning_tx(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = sd_tuning_rx(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_ddr_tuning(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	अगर (!(chip->sd_ctl & SD_DDR_TX_PHASE_SET_BY_USER)) अणु
		retval = sd_ddr_pre_tuning_tx(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = sd_change_phase(chip, (u8)chip->sd_ddr_tx_phase,
					 TUNE_TX);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	retval = sd_tuning_rx(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (!(chip->sd_ctl & SD_DDR_TX_PHASE_SET_BY_USER)) अणु
		retval = sd_tuning_tx(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक mmc_ddr_tuning(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	अगर (!(chip->sd_ctl & MMC_DDR_TX_PHASE_SET_BY_USER)) अणु
		retval = sd_ddr_pre_tuning_tx(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = sd_change_phase(chip, (u8)chip->mmc_ddr_tx_phase,
					 TUNE_TX);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	retval = sd_tuning_rx(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (!(chip->sd_ctl & MMC_DDR_TX_PHASE_SET_BY_USER)) अणु
		retval = sd_tuning_tx(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक sd_चयन_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	पूर्णांक re_tuning = 0;

	retval = select_card(chip, SD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = चयन_घड़ी(chip, sd_card->sd_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (re_tuning) अणु
		अगर (CHK_SD(sd_card)) अणु
			अगर (CHK_SD_DDR50(sd_card))
				retval = sd_ddr_tuning(chip);
			अन्यथा
				retval = sd_sdr_tuning(chip);
		पूर्ण अन्यथा अणु
			अगर (CHK_MMC_DDR52(sd_card))
				retval = mmc_ddr_tuning(chip);
		पूर्ण

		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_prepare_reset(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	अगर (chip->asic_code)
		sd_card->sd_घड़ी = 29;
	अन्यथा
		sd_card->sd_घड़ी = CLK_30;

	sd_card->sd_type = 0;
	sd_card->seq_mode = 0;
	sd_card->sd_data_buf_पढ़ोy = 0;
	sd_card->capacity = 0;

#अगर_घोषित SUPPORT_SD_LOCK
	sd_card->sd_lock_status = 0;
	sd_card->sd_erase_status = 0;
#पूर्ण_अगर

	chip->capacity[chip->card2lun[SD_CARD]] = 0;
	chip->sd_io = 0;

	retval = sd_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0xFF, 0x40);
	अगर (retval)
		वापस retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, SD_STOP | SD_CLR_ERR,
				     SD_STOP | SD_CLR_ERR);
	अगर (retval)
		वापस retval;

	retval = select_card(chip, SD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_pull_ctl_disable(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	अगर (CHECK_PID(chip, 0x5208)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL1, 0xFF,
					     XD_D3_PD | SD_D7_PD | SD_CLK_PD |
					     SD_D5_PD);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL2, 0xFF,
					     SD_D6_PD | SD_D0_PD | SD_D1_PD |
					     XD_D5_PD);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL3, 0xFF,
					     SD_D4_PD | XD_CE_PD | XD_CLE_PD |
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

पूर्णांक sd_pull_ctl_enable(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	rtsx_init_cmd(chip);

	अगर (CHECK_PID(chip, 0x5208)) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF,
			     XD_D3_PD | SD_DAT7_PU | SD_CLK_NP | SD_D5_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF,
			     SD_D6_PU | SD_D0_PU | SD_D1_PU | XD_D5_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF,
			     SD_D4_PU | XD_CE_PD | XD_CLE_PD | XD_CD_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF,
			     XD_RDY_PD | SD_D3_PU | SD_D2_PU | XD_ALE_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF,
			     MS_INS_PU | SD_WP_PU | SD_CD_PU | SD_CMD_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		अगर (CHECK_BARO_PKG(chip, QFN)) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF,
				     0xA8);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF,
				     0x5A);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF,
				     0x95);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF,
				     0xAA);
		पूर्ण
	पूर्ण

	retval = rtsx_send_cmd(chip, SD_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_init_घातer(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = sd_घातer_off_card3v3(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (!chip->ft2_fast_mode)
		रुको_समयout(250);

	retval = enable_card_घड़ी(chip, SD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (chip->asic_code) अणु
		retval = sd_pull_ctl_enable(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL,
					     FPGA_SD_PULL_CTL_BIT | 0x20, 0);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (!chip->ft2_fast_mode) अणु
		retval = card_घातer_on(chip, SD_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		रुको_समयout(260);

#अगर_घोषित SUPPORT_OCP
		अगर (chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) अणु
			dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			वापस STATUS_FAIL;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SD_OUTPUT_EN,
				     SD_OUTPUT_EN);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_dummy_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG3, 0x01, 0x01);
	अगर (retval)
		वापस retval;
	रुको_समयout(5);
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG3, 0x01, 0);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_पढ़ो_lba0(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 cmd[5], bus_width;

	cmd[0] = 0x40 | READ_SINGLE_BLOCK;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	अगर (CHK_SD(sd_card)) अणु
		bus_width = SD_BUS_WIDTH_4;
	पूर्ण अन्यथा अणु
		अगर (CHK_MMC_8BIT(sd_card))
			bus_width = SD_BUS_WIDTH_8;
		अन्यथा अगर (CHK_MMC_4BIT(sd_card))
			bus_width = SD_BUS_WIDTH_4;
		अन्यथा
			bus_width = SD_BUS_WIDTH_1;
	पूर्ण

	retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, 512, 1,
			      bus_width, शून्य, 0, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_sd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sd_check_wp_state(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u32 val;
	u16 sd_card_type;
	u8 cmd[5], buf[64];

	retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	cmd[0] = 0x40 | SD_STATUS;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, 64, 1,
			      SD_BUS_WIDTH_4, buf, 64, 250);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_sd_error(chip);

		sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				    SD_RSP_TYPE_R1, शून्य, 0);
		वापस STATUS_FAIL;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "ACMD13:\n");
	dev_dbg(rtsx_dev(chip), "%*ph\n", 64, buf);

	sd_card_type = ((u16)buf[2] << 8) | buf[3];
	dev_dbg(rtsx_dev(chip), "sd_card_type = 0x%04x\n", sd_card_type);
	अगर ((sd_card_type == 0x0001) || (sd_card_type == 0x0002)) अणु
		/* ROM card or OTP */
		chip->card_wp |= SD_CARD;
	पूर्ण

	/* Check SD Machanical Write-Protect Switch */
	val = rtsx_पढ़ोl(chip, RTSX_BIPR);
	अगर (val & SD_WRITE_PROTECT)
		chip->card_wp |= SD_CARD;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक reset_sd(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	bool hi_cap_flow = false;
	पूर्णांक retval, i = 0, j = 0, k = 0;
	bool sd_करोnt_चयन = false;
	bool support_1v8 = false;
	bool try_sdio = true;
	u8 rsp[16];
	u8 चयन_bus_width;
	u32 voltage = 0;
	bool sd20_mode = false;

	SET_SD(sd_card);

चयन_fail:

	i = 0;
	j = 0;
	k = 0;
	hi_cap_flow = false;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (sd_card->sd_lock_status & SD_UNLOCK_POW_ON)
		जाओ SD_UNLOCK_ENTRY;
#पूर्ण_अगर

	retval = sd_prepare_reset(chip);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	retval = sd_dummy_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	अगर (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNORED(chip) && try_sdio) अणु
		पूर्णांक rty_cnt = 0;

		क्रम (; rty_cnt < chip->sdio_retry_cnt; rty_cnt++) अणु
			अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
				sd_set_err_code(chip, SD_NO_CARD);
				जाओ status_fail;
			पूर्ण

			retval = sd_send_cmd_get_rsp(chip, IO_SEND_OP_COND, 0,
						     SD_RSP_TYPE_R4, rsp, 5);
			अगर (retval == STATUS_SUCCESS) अणु
				पूर्णांक func_num = (rsp[1] >> 4) & 0x07;

				अगर (func_num) अणु
					dev_dbg(rtsx_dev(chip), "SD_IO card (Function number: %d)!\n",
						func_num);
					chip->sd_io = 1;
					जाओ status_fail;
				पूर्ण

				अवरोध;
			पूर्ण

			sd_init_घातer(chip);

			sd_dummy_घड़ी(chip);
		पूर्ण

		dev_dbg(rtsx_dev(chip), "Normal card!\n");
	पूर्ण

	/* Start Initialization Process of SD Card */
RTY_SD_RST:
	retval = sd_send_cmd_get_rsp(chip, GO_IDLE_STATE, 0, SD_RSP_TYPE_R0,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	रुको_समयout(20);

	retval = sd_send_cmd_get_rsp(chip, SEND_IF_COND, 0x000001AA,
				     SD_RSP_TYPE_R7, rsp, 5);
	अगर (retval == STATUS_SUCCESS) अणु
		अगर ((rsp[4] == 0xAA) && ((rsp[3] & 0x0f) == 0x01)) अणु
			hi_cap_flow = true;
			voltage = SUPPORT_VOLTAGE | 0x40000000;
		पूर्ण
	पूर्ण

	अगर (!hi_cap_flow) अणु
		voltage = SUPPORT_VOLTAGE;

		retval = sd_send_cmd_get_rsp(chip, GO_IDLE_STATE, 0,
					     SD_RSP_TYPE_R0, शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;

		रुको_समयout(20);
	पूर्ण

	करो अणु
		retval = sd_send_cmd_get_rsp(chip, APP_CMD, 0, SD_RSP_TYPE_R1,
					     शून्य, 0);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
				sd_set_err_code(chip, SD_NO_CARD);
				जाओ status_fail;
			पूर्ण

			j++;
			अगर (j < 3)
				जाओ RTY_SD_RST;
			अन्यथा
				जाओ status_fail;
		पूर्ण

		retval = sd_send_cmd_get_rsp(chip, SD_APP_OP_COND, voltage,
					     SD_RSP_TYPE_R3, rsp, 5);
		अगर (retval != STATUS_SUCCESS) अणु
			k++;
			अगर (k < 3)
				जाओ RTY_SD_RST;
			अन्यथा
				जाओ status_fail;
		पूर्ण

		i++;
		रुको_समयout(20);
	पूर्ण जबतक (!(rsp[1] & 0x80) && (i < 255));

	अगर (i == 255)
		जाओ status_fail;

	अगर (hi_cap_flow) अणु
		अगर (rsp[1] & 0x40)
			SET_SD_HCXC(sd_card);
		अन्यथा
			CLR_SD_HCXC(sd_card);

		support_1v8 = false;
	पूर्ण अन्यथा अणु
		CLR_SD_HCXC(sd_card);
		support_1v8 = false;
	पूर्ण
	dev_dbg(rtsx_dev(chip), "support_1v8 = %d\n", support_1v8);

	अगर (support_1v8) अणु
		retval = sd_voltage_चयन(chip);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;
	पूर्ण

	retval = sd_send_cmd_get_rsp(chip, ALL_SEND_CID, 0, SD_RSP_TYPE_R2,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	क्रम (i = 0; i < 3; i++) अणु
		retval = sd_send_cmd_get_rsp(chip, SEND_RELATIVE_ADDR, 0,
					     SD_RSP_TYPE_R6, rsp, 5);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;

		sd_card->sd_addr = (u32)rsp[1] << 24;
		sd_card->sd_addr += (u32)rsp[2] << 16;

		अगर (sd_card->sd_addr)
			अवरोध;
	पूर्ण

	retval = sd_check_csd(chip, 1);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	retval = sd_select_card(chip, 1);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

#अगर_घोषित SUPPORT_SD_LOCK
SD_UNLOCK_ENTRY:
	retval = sd_update_lock_status(chip);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	अगर (sd_card->sd_lock_status & SD_LOCKED) अणु
		sd_card->sd_lock_status |= (SD_LOCK_1BIT_MODE | SD_PWD_EXIST);
		वापस STATUS_SUCCESS;
	पूर्ण अन्यथा अगर (!(sd_card->sd_lock_status & SD_UNLOCK_POW_ON)) अणु
		sd_card->sd_lock_status &= ~SD_PWD_EXIST;
	पूर्ण
#पूर्ण_अगर

	retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	retval = sd_send_cmd_get_rsp(chip, SET_CLR_CARD_DETECT, 0,
				     SD_RSP_TYPE_R1, शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	अगर (support_1v8) अणु
		retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
					     SD_RSP_TYPE_R1, शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;

		retval = sd_send_cmd_get_rsp(chip, SET_BUS_WIDTH, 2,
					     SD_RSP_TYPE_R1, शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;

		चयन_bus_width = SD_BUS_WIDTH_4;
	पूर्ण अन्यथा अणु
		चयन_bus_width = SD_BUS_WIDTH_1;
	पूर्ण

	retval = sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, 0x200, SD_RSP_TYPE_R1,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	retval = sd_set_घड़ी_भागider(chip, SD_CLK_DIVIDE_0);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	अगर (!(sd_card->raw_csd[4] & 0x40))
		sd_करोnt_चयन = true;

	अगर (!sd_करोnt_चयन) अणु
		अगर (sd20_mode) अणु
			/* Set sd_चयन_fail here, because we needn't
			 * चयन to UHS mode
			 */
			sd_card->sd_चयन_fail = SDR104_SUPPORT_MASK |
				DDR50_SUPPORT_MASK | SDR50_SUPPORT_MASK;
		पूर्ण

		/* Check the card whether follow SD1.1 spec or higher */
		retval = sd_check_spec(chip, चयन_bus_width);
		अगर (retval == STATUS_SUCCESS) अणु
			retval = sd_चयन_function(chip, चयन_bus_width);
			अगर (retval != STATUS_SUCCESS) अणु
				sd_init_घातer(chip);
				sd_करोnt_चयन = true;
				try_sdio = false;

				जाओ चयन_fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (support_1v8) अणु
				sd_init_घातer(chip);
				sd_करोnt_चयन = true;
				try_sdio = false;

				जाओ चयन_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!support_1v8) अणु
		retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
					     SD_RSP_TYPE_R1, शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;

		retval = sd_send_cmd_get_rsp(chip, SET_BUS_WIDTH, 2,
					     SD_RSP_TYPE_R1, शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	sd_card->sd_lock_status &= ~SD_LOCK_1BIT_MODE;
#पूर्ण_अगर

	अगर (!sd20_mode && CHK_SD30_SPEED(sd_card)) अणु
		पूर्णांक पढ़ो_lba0 = 1;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD30_DRIVE_SEL, 0x07,
					     chip->sd30_drive_sel_1v8);
		अगर (retval)
			वापस retval;

		retval = sd_set_init_para(chip);
		अगर (retval != STATUS_SUCCESS)
			जाओ status_fail;

		अगर (CHK_SD_DDR50(sd_card))
			retval = sd_ddr_tuning(chip);
		अन्यथा
			retval = sd_sdr_tuning(chip);

		अगर (retval != STATUS_SUCCESS) अणु
			retval = sd_init_घातer(chip);
			अगर (retval != STATUS_SUCCESS)
				जाओ status_fail;

			try_sdio = false;
			sd20_mode = true;
			जाओ चयन_fail;
		पूर्ण

		sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				    SD_RSP_TYPE_R1, शून्य, 0);

		अगर (CHK_SD_DDR50(sd_card)) अणु
			retval = sd_रुको_state_data_पढ़ोy(chip, 0x08, 1, 1000);
			अगर (retval != STATUS_SUCCESS)
				पढ़ो_lba0 = 0;
		पूर्ण

		अगर (पढ़ो_lba0) अणु
			retval = sd_पढ़ो_lba0(chip);
			अगर (retval != STATUS_SUCCESS) अणु
				retval = sd_init_घातer(chip);
				अगर (retval != STATUS_SUCCESS)
					जाओ status_fail;

				try_sdio = false;
				sd20_mode = true;
				जाओ चयन_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	retval = sd_check_wp_state(chip);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	chip->card_bus_width[chip->card2lun[SD_CARD]] = 4;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (sd_card->sd_lock_status & SD_UNLOCK_POW_ON) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BLOCK_CNT_H, 0xFF,
					     0x02);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BLOCK_CNT_L, 0xFF,
					     0x00);
		अगर (retval)
			वापस retval;
	पूर्ण
#पूर्ण_अगर

	वापस STATUS_SUCCESS;

status_fail:
	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक mmc_test_चयन_bus(काष्ठा rtsx_chip *chip, u8 width)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 buf[8] = अणु0पूर्ण, bus_width, *ptr;
	u16 byte_cnt;
	पूर्णांक len;

	retval = sd_send_cmd_get_rsp(chip, BUSTEST_W, 0, SD_RSP_TYPE_R1, शून्य,
				     0);
	अगर (retval != STATUS_SUCCESS)
		वापस SWITCH_FAIL;

	अगर (width == MMC_8BIT_BUS) अणु
		buf[0] = 0x55;
		buf[1] = 0xAA;
		len = 8;
		byte_cnt = 8;
		bus_width = SD_BUS_WIDTH_8;
	पूर्ण अन्यथा अणु
		buf[0] = 0x5A;
		len = 4;
		byte_cnt = 4;
		bus_width = SD_BUS_WIDTH_4;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG3, 0x02, 0x02);
	अगर (retval != STATUS_SUCCESS)
		वापस SWITCH_ERR;

	retval = sd_ग_लिखो_data(chip, SD_TM_AUTO_WRITE_3, शून्य, 0, byte_cnt, 1,
			       bus_width, buf, len, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_sd_error(chip);
		rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG3, 0x02, 0);
		वापस SWITCH_ERR;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG3, 0x02, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस SWITCH_ERR;

	dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", BUSTEST_R);

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF, 0x40 | BUSTEST_R);

	अगर (width == MMC_8BIT_BUS)
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L,
			     0xFF, 0x08);
	अन्यथा
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L,
			     0xFF, 0x04);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF, 0);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, SD_CALCULATE_CRC7 |
		     SD_NO_CHECK_CRC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CRC7 | SD_RSP_LEN_6);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		     PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		     SD_TM_NORMAL_READ | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2, 0, 0);
	अगर (width == MMC_8BIT_BUS)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 1, 0, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, 100);
	अगर (retval < 0) अणु
		rtsx_clear_sd_error(chip);
		वापस SWITCH_ERR;
	पूर्ण

	ptr = rtsx_get_cmd_data(chip) + 1;

	अगर (width == MMC_8BIT_BUS) अणु
		dev_dbg(rtsx_dev(chip), "BUSTEST_R [8bits]: 0x%02x 0x%02x\n",
			ptr[0], ptr[1]);
		अगर ((ptr[0] == 0xAA) && (ptr[1] == 0x55)) अणु
			u8 rsp[5];
			u32 arg;

			अगर (CHK_MMC_DDR52(sd_card))
				arg = 0x03B70600;
			अन्यथा
				arg = 0x03B70200;

			retval = sd_send_cmd_get_rsp(chip, SWITCH, arg,
						     SD_RSP_TYPE_R1b, rsp, 5);
			अगर ((retval == STATUS_SUCCESS) &&
			    !(rsp[4] & MMC_SWITCH_ERR))
				वापस SWITCH_SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(rtsx_dev(chip), "BUSTEST_R [4bits]: 0x%02x\n", ptr[0]);
		अगर (ptr[0] == 0xA5) अणु
			u8 rsp[5];
			u32 arg;

			अगर (CHK_MMC_DDR52(sd_card))
				arg = 0x03B70500;
			अन्यथा
				arg = 0x03B70100;

			retval = sd_send_cmd_get_rsp(chip, SWITCH, arg,
						     SD_RSP_TYPE_R1b, rsp, 5);
			अगर ((retval == STATUS_SUCCESS) &&
			    !(rsp[4] & MMC_SWITCH_ERR))
				वापस SWITCH_SUCCESS;
		पूर्ण
	पूर्ण

	वापस SWITCH_FAIL;
पूर्ण

अटल पूर्णांक mmc_चयन_timing_bus(काष्ठा rtsx_chip *chip, bool चयन_ddr)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;
	u8 *ptr, card_type, card_type_mask = 0;

	CLR_MMC_HS(sd_card);

	dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", SEND_EXT_CSD);

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF,
		     0x40 | SEND_EXT_CSD);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD1, 0xFF, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD2, 0xFF, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD3, 0xFF, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD4, 0xFF, 0);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF, 2);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF, 0);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
		     SD_CALCULATE_CRC7 | SD_CHECK_CRC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CRC7 | SD_RSP_LEN_6);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		     PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		     SD_TM_NORMAL_READ | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 196, 0xFF, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 212, 0xFF, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 213, 0xFF, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 214, 0xFF, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 215, 0xFF, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, 1000);
	अगर (retval < 0) अणु
		अगर (retval == -ETIMEDOUT) अणु
			rtsx_clear_sd_error(chip);
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, शून्य, 0);
		पूर्ण
		वापस STATUS_FAIL;
	पूर्ण

	ptr = rtsx_get_cmd_data(chip);
	अगर (ptr[0] & SD_TRANSFER_ERR) अणु
		sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				    SD_RSP_TYPE_R1, शून्य, 0);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (CHK_MMC_SECTOR_MODE(sd_card)) अणु
		sd_card->capacity = ((u32)ptr[5] << 24) | ((u32)ptr[4] << 16) |
			((u32)ptr[3] << 8) | ((u32)ptr[2]);
	पूर्ण

	card_type_mask = 0x03;
	card_type = ptr[1] & card_type_mask;
	अगर (card_type) अणु
		u8 rsp[5];

		अगर (card_type & 0x04) अणु
			अगर (चयन_ddr)
				SET_MMC_DDR52(sd_card);
			अन्यथा
				SET_MMC_52M(sd_card);
		पूर्ण अन्यथा अगर (card_type & 0x02) अणु
			SET_MMC_52M(sd_card);
		पूर्ण अन्यथा अणु
			SET_MMC_26M(sd_card);
		पूर्ण

		retval = sd_send_cmd_get_rsp(chip, SWITCH, 0x03B90100,
					     SD_RSP_TYPE_R1b, rsp, 5);
		अगर ((retval != STATUS_SUCCESS) || (rsp[4] & MMC_SWITCH_ERR))
			CLR_MMC_HS(sd_card);
	पूर्ण

	sd_choose_proper_घड़ी(chip);
	retval = चयन_घड़ी(chip, sd_card->sd_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	/* Test Bus Procedure */
	retval = mmc_test_चयन_bus(chip, MMC_8BIT_BUS);
	अगर (retval == SWITCH_SUCCESS) अणु
		SET_MMC_8BIT(sd_card);
		chip->card_bus_width[chip->card2lun[SD_CARD]] = 8;
#अगर_घोषित SUPPORT_SD_LOCK
		sd_card->sd_lock_status &= ~SD_LOCK_1BIT_MODE;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (retval == SWITCH_FAIL) अणु
		retval = mmc_test_चयन_bus(chip, MMC_4BIT_BUS);
		अगर (retval == SWITCH_SUCCESS) अणु
			SET_MMC_4BIT(sd_card);
			chip->card_bus_width[chip->card2lun[SD_CARD]] = 4;
#अगर_घोषित SUPPORT_SD_LOCK
			sd_card->sd_lock_status &= ~SD_LOCK_1BIT_MODE;
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (retval == SWITCH_FAIL) अणु
			CLR_MMC_8BIT(sd_card);
			CLR_MMC_4BIT(sd_card);
		पूर्ण अन्यथा अणु
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक reset_mmc(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval, i = 0, j = 0, k = 0;
	bool चयन_ddr = true;
	u8 rsp[16];
	u8 spec_ver = 0;
	u32 temp;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (sd_card->sd_lock_status & SD_UNLOCK_POW_ON)
		जाओ MMC_UNLOCK_ENTRY;
#पूर्ण_अगर

चयन_fail:
	retval = sd_prepare_reset(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस retval;

	SET_MMC(sd_card);

RTY_MMC_RST:
	retval = sd_send_cmd_get_rsp(chip, GO_IDLE_STATE, 0, SD_RSP_TYPE_R0,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	करो अणु
		अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		retval = sd_send_cmd_get_rsp(chip, SEND_OP_COND,
					     (SUPPORT_VOLTAGE | 0x40000000),
					     SD_RSP_TYPE_R3, rsp, 5);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (sd_check_err_code(chip, SD_BUSY) ||
			    sd_check_err_code(chip, SD_TO_ERR)) अणु
				k++;
				अगर (k < 20) अणु
					sd_clr_err_code(chip);
					जाओ RTY_MMC_RST;
				पूर्ण अन्यथा अणु
					वापस STATUS_FAIL;
				पूर्ण
			पूर्ण अन्यथा अणु
				j++;
				अगर (j < 100) अणु
					sd_clr_err_code(chip);
					जाओ RTY_MMC_RST;
				पूर्ण अन्यथा अणु
					वापस STATUS_FAIL;
				पूर्ण
			पूर्ण
		पूर्ण

		रुको_समयout(20);
		i++;
	पूर्ण जबतक (!(rsp[1] & 0x80) && (i < 255));

	अगर (i == 255)
		वापस STATUS_FAIL;

	अगर ((rsp[1] & 0x60) == 0x40)
		SET_MMC_SECTOR_MODE(sd_card);
	अन्यथा
		CLR_MMC_SECTOR_MODE(sd_card);

	retval = sd_send_cmd_get_rsp(chip, ALL_SEND_CID, 0, SD_RSP_TYPE_R2,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	sd_card->sd_addr = 0x00100000;
	retval = sd_send_cmd_get_rsp(chip, SET_RELATIVE_ADDR, sd_card->sd_addr,
				     SD_RSP_TYPE_R6, rsp, 5);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = sd_check_csd(chip, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	spec_ver = (sd_card->raw_csd[0] & 0x3C) >> 2;

	retval = sd_select_card(chip, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, 0x200, SD_RSP_TYPE_R1,
				     शून्य, 0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

#अगर_घोषित SUPPORT_SD_LOCK
MMC_UNLOCK_ENTRY:
	retval = sd_update_lock_status(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;
#पूर्ण_अगर

	retval = sd_set_घड़ी_भागider(chip, SD_CLK_DIVIDE_0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	chip->card_bus_width[chip->card2lun[SD_CARD]] = 1;

	अगर (!sd_card->mmc_करोnt_चयन_bus) अणु
		अगर (spec_ver == 4) अणु
			/* MMC 4.x Cards */
			retval = mmc_चयन_timing_bus(chip, चयन_ddr);
			अगर (retval != STATUS_SUCCESS) अणु
				retval = sd_init_घातer(chip);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;
				sd_card->mmc_करोnt_चयन_bus = 1;
				जाओ चयन_fail;
			पूर्ण
		पूर्ण

		अगर (CHK_MMC_SECTOR_MODE(sd_card) && (sd_card->capacity == 0))
			वापस STATUS_FAIL;

		अगर (चयन_ddr && CHK_MMC_DDR52(sd_card)) अणु
			retval = sd_set_init_para(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			retval = mmc_ddr_tuning(chip);
			अगर (retval != STATUS_SUCCESS) अणु
				retval = sd_init_घातer(chip);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;

				चयन_ddr = false;
				जाओ चयन_fail;
			पूर्ण

			retval = sd_रुको_state_data_पढ़ोy(chip, 0x08, 1, 1000);
			अगर (retval == STATUS_SUCCESS) अणु
				retval = sd_पढ़ो_lba0(chip);
				अगर (retval != STATUS_SUCCESS) अणु
					retval = sd_init_घातer(chip);
					अगर (retval != STATUS_SUCCESS)
						वापस STATUS_FAIL;

					चयन_ddr = false;
					जाओ चयन_fail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (sd_card->sd_lock_status & SD_UNLOCK_POW_ON) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BLOCK_CNT_H, 0xFF,
					     0x02);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BLOCK_CNT_L, 0xFF,
					     0x00);
		अगर (retval)
			वापस retval;
	पूर्ण
#पूर्ण_अगर

	temp = rtsx_पढ़ोl(chip, RTSX_BIPR);
	अगर (temp & SD_WRITE_PROTECT)
		chip->card_wp |= SD_CARD;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक reset_sd_card(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	sd_init_reg_addr(chip);

	स_रखो(sd_card, 0, माप(काष्ठा sd_info));
	chip->capacity[chip->card2lun[SD_CARD]] = 0;

	retval = enable_card_घड़ी(chip, SD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (chip->ignore_sd && CHK_SDIO_EXIST(chip) &&
	    !CHK_SDIO_IGNORED(chip)) अणु
		अगर (chip->asic_code) अणु
			retval = sd_pull_ctl_enable(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण अन्यथा अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL,
						     FPGA_SD_PULL_CTL_BIT |
						     0x20, 0);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण
		retval = card_share_mode(chip, SD_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		chip->sd_io = 1;
		वापस STATUS_FAIL;
	पूर्ण

	retval = sd_init_घातer(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (chip->sd_ctl & RESET_MMC_FIRST) अणु
		retval = reset_mmc(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (sd_check_err_code(chip, SD_NO_CARD))
				वापस STATUS_FAIL;

			retval = reset_sd(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = reset_sd(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (sd_check_err_code(chip, SD_NO_CARD))
				वापस STATUS_FAIL;

			अगर (chip->sd_io)
				वापस STATUS_FAIL;
			retval = reset_mmc(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	retval = sd_set_घड़ी_भागider(chip, SD_CLK_DIVIDE_0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BYTE_CNT_L, 0xFF, 0);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BYTE_CNT_H, 0xFF, 2);
	अगर (retval)
		वापस retval;

	chip->capacity[chip->card2lun[SD_CARD]] = sd_card->capacity;

	retval = sd_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "sd_card->sd_type = 0x%x\n", sd_card->sd_type);

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक reset_mmc_only(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	sd_card->sd_type = 0;
	sd_card->seq_mode = 0;
	sd_card->sd_data_buf_पढ़ोy = 0;
	sd_card->capacity = 0;
	sd_card->sd_चयन_fail = 0;

#अगर_घोषित SUPPORT_SD_LOCK
	sd_card->sd_lock_status = 0;
	sd_card->sd_erase_status = 0;
#पूर्ण_अगर

	chip->capacity[chip->card2lun[SD_CARD]] = sd_card->capacity = 0;

	retval = enable_card_घड़ी(chip, SD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = sd_init_घातer(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = reset_mmc(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = sd_set_घड़ी_भागider(chip, SD_CLK_DIVIDE_0);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BYTE_CNT_L, 0xFF, 0);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_BYTE_CNT_H, 0xFF, 2);
	अगर (retval)
		वापस retval;

	chip->capacity[chip->card2lun[SD_CARD]] = sd_card->capacity;

	retval = sd_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "In %s, sd_card->sd_type = 0x%x\n",
		__func__, sd_card->sd_type);

	वापस STATUS_SUCCESS;
पूर्ण

#घोषणा WAIT_DATA_READY_RTY_CNT		255

अटल पूर्णांक रुको_data_buf_पढ़ोy(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक i, retval;

	क्रम (i = 0; i < WAIT_DATA_READY_RTY_CNT; i++) अणु
		अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		sd_card->sd_data_buf_पढ़ोy = 0;

		retval = sd_send_cmd_get_rsp(chip, SEND_STATUS,
					     sd_card->sd_addr, SD_RSP_TYPE_R1,
					     शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (sd_card->sd_data_buf_पढ़ोy) अणु
			वापस sd_send_cmd_get_rsp(chip, SEND_STATUS,
				sd_card->sd_addr, SD_RSP_TYPE_R1, शून्य, 0);
		पूर्ण
	पूर्ण

	sd_set_err_code(chip, SD_TO_ERR);

	वापस STATUS_FAIL;
पूर्ण

व्योम sd_stop_seq_mode(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	अगर (sd_card->seq_mode) अणु
		retval = sd_चयन_घड़ी(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस;

		retval = sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
					     SD_RSP_TYPE_R1b, शून्य, 0);
		अगर (retval != STATUS_SUCCESS)
			sd_set_err_code(chip, SD_STS_ERR);

		retval = sd_रुको_state_data_पढ़ोy(chip, 0x08, 1, 1000);
		अगर (retval != STATUS_SUCCESS)
			sd_set_err_code(chip, SD_STS_ERR);

		sd_card->seq_mode = 0;

		rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, RB_FLUSH, RB_FLUSH);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक sd_स्वतः_tune_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	अगर (chip->asic_code) अणु
		अगर (sd_card->sd_घड़ी > 30)
			sd_card->sd_घड़ी -= 20;
	पूर्ण अन्यथा अणु
		चयन (sd_card->sd_घड़ी) अणु
		हाल CLK_200:
			sd_card->sd_घड़ी = CLK_150;
			अवरोध;

		हाल CLK_150:
			sd_card->sd_घड़ी = CLK_120;
			अवरोध;

		हाल CLK_120:
			sd_card->sd_घड़ी = CLK_100;
			अवरोध;

		हाल CLK_100:
			sd_card->sd_घड़ी = CLK_80;
			अवरोध;

		हाल CLK_80:
			sd_card->sd_घड़ी = CLK_60;
			अवरोध;

		हाल CLK_60:
			sd_card->sd_घड़ी = CLK_50;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक sd_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip, u32 start_sector,
	  u16 sector_cnt)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	u32 data_addr;
	u8 cfg2;
	पूर्णांक retval;

	अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
		dev_dbg(rtsx_dev(chip), "%s: Read %d %s from 0x%x\n", __func__,
			sector_cnt, (sector_cnt > 1) ? "sectors" : "sector",
			start_sector);
	पूर्ण अन्यथा अणु
		dev_dbg(rtsx_dev(chip), "%s: Write %d %s to 0x%x\n", __func__,
			sector_cnt, (sector_cnt > 1) ? "sectors" : "sector",
			start_sector);
	पूर्ण

	sd_card->cleanup_counter = 0;

	अगर (!(chip->card_पढ़ोy & SD_CARD)) अणु
		sd_card->seq_mode = 0;

		retval = reset_sd_card(chip);
		अगर (retval == STATUS_SUCCESS) अणु
			chip->card_पढ़ोy |= SD_CARD;
			chip->card_fail &= ~SD_CARD;
		पूर्ण अन्यथा अणु
			chip->card_पढ़ोy &= ~SD_CARD;
			chip->card_fail |= SD_CARD;
			chip->capacity[chip->card2lun[SD_CARD]] = 0;
			chip->rw_need_retry = 1;
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	अगर (!CHK_SD_HCXC(sd_card) && !CHK_MMC_SECTOR_MODE(sd_card))
		data_addr = start_sector << 9;
	अन्यथा
		data_addr = start_sector;

	sd_clr_err_code(chip);

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		sd_set_err_code(chip, SD_IO_ERR);
		जाओ RW_FAIL;
	पूर्ण

	अगर (sd_card->seq_mode &&
	    ((sd_card->pre_dir != srb->sc_data_direction) ||
	    ((sd_card->pre_sec_addr + sd_card->pre_sec_cnt) !=
	    start_sector))) अणु
		अगर ((sd_card->pre_sec_cnt < 0x80) &&
		    (sd_card->pre_dir == DMA_FROM_DEVICE) &&
		    !CHK_SD30_SPEED(sd_card) &&
		    !CHK_SD_HS(sd_card) &&
		    !CHK_MMC_HS(sd_card)) अणु
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, शून्य, 0);
		पूर्ण

		retval = sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
					     SD_RSP_TYPE_R1b, शून्य, 0);
		अगर (retval != STATUS_SUCCESS) अणु
			chip->rw_need_retry = 1;
			sd_set_err_code(chip, SD_STS_ERR);
			जाओ RW_FAIL;
		पूर्ण

		sd_card->seq_mode = 0;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, RB_FLUSH, RB_FLUSH);
		अगर (retval != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_IO_ERR);
			जाओ RW_FAIL;
		पूर्ण

		अगर ((sd_card->pre_sec_cnt < 0x80) &&
		    !CHK_SD30_SPEED(sd_card) &&
		    !CHK_SD_HS(sd_card) &&
		    !CHK_MMC_HS(sd_card)) अणु
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, शून्य, 0);
		पूर्ण
	पूर्ण

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF, 0x00);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF, 0x02);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
		     (u8)sector_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
		     (u8)(sector_cnt >> 8));

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);

	अगर (CHK_MMC_8BIT(sd_card))
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1,
			     0x03, SD_BUS_WIDTH_8);
	अन्यथा अगर (CHK_MMC_4BIT(sd_card) || CHK_SD(sd_card))
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1,
			     0x03, SD_BUS_WIDTH_4);
	अन्यथा
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1,
			     0x03, SD_BUS_WIDTH_1);

	अगर (sd_card->seq_mode) अणु
		cfg2 = SD_NO_CALCULATE_CRC7 | SD_CHECK_CRC16 |
			SD_NO_WAIT_BUSY_END | SD_NO_CHECK_CRC7 |
			SD_RSP_LEN_0;
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, cfg2);

		trans_dma_enable(srb->sc_data_direction, chip, sector_cnt * 512,
				 DMA_512);

		अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
				     SD_TM_AUTO_READ_3 | SD_TRANSFER_START);
		पूर्ण अन्यथा अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
				     SD_TM_AUTO_WRITE_3 | SD_TRANSFER_START);
		पूर्ण

		rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
			     SD_TRANSFER_END, SD_TRANSFER_END);

		rtsx_send_cmd_no_रुको(chip);
	पूर्ण अन्यथा अणु
		अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
			dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n",
				READ_MULTIPLE_BLOCK);
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF,
				     0x40 | READ_MULTIPLE_BLOCK);
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD1, 0xFF,
				     (u8)(data_addr >> 24));
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD2, 0xFF,
				     (u8)(data_addr >> 16));
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD3, 0xFF,
				     (u8)(data_addr >> 8));
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD4, 0xFF,
				     (u8)data_addr);

			cfg2 = SD_CALCULATE_CRC7 | SD_CHECK_CRC16 |
				SD_NO_WAIT_BUSY_END | SD_CHECK_CRC7 |
				SD_RSP_LEN_6;
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
				     cfg2);

			trans_dma_enable(srb->sc_data_direction, chip,
					 sector_cnt * 512, DMA_512);

			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
				     SD_TM_AUTO_READ_2 | SD_TRANSFER_START);
			rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
				     SD_TRANSFER_END, SD_TRANSFER_END);

			rtsx_send_cmd_no_रुको(chip);
		पूर्ण अन्यथा अणु
			retval = rtsx_send_cmd(chip, SD_CARD, 50);
			अगर (retval < 0) अणु
				rtsx_clear_sd_error(chip);

				chip->rw_need_retry = 1;
				sd_set_err_code(chip, SD_TO_ERR);
				जाओ RW_FAIL;
			पूर्ण

			retval = रुको_data_buf_पढ़ोy(chip);
			अगर (retval != STATUS_SUCCESS) अणु
				chip->rw_need_retry = 1;
				sd_set_err_code(chip, SD_TO_ERR);
				जाओ RW_FAIL;
			पूर्ण

			retval = sd_send_cmd_get_rsp(chip, WRITE_MULTIPLE_BLOCK,
						     data_addr, SD_RSP_TYPE_R1,
						     शून्य, 0);
			अगर (retval != STATUS_SUCCESS) अणु
				chip->rw_need_retry = 1;
				जाओ RW_FAIL;
			पूर्ण

			rtsx_init_cmd(chip);

			cfg2 = SD_NO_CALCULATE_CRC7 | SD_CHECK_CRC16 |
				SD_NO_WAIT_BUSY_END |
				SD_NO_CHECK_CRC7 | SD_RSP_LEN_0;
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
				     cfg2);

			trans_dma_enable(srb->sc_data_direction, chip,
					 sector_cnt * 512, DMA_512);

			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
				     SD_TM_AUTO_WRITE_3 | SD_TRANSFER_START);
			rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
				     SD_TRANSFER_END, SD_TRANSFER_END);

			rtsx_send_cmd_no_रुको(chip);
		पूर्ण

		sd_card->seq_mode = 1;
	पूर्ण

	retval = rtsx_transfer_data(chip, SD_CARD, scsi_sglist(srb),
				    scsi_bufflen(srb), scsi_sg_count(srb),
				srb->sc_data_direction, chip->sd_समयout);
	अगर (retval < 0) अणु
		u8 stat = 0;
		पूर्णांक err;

		sd_card->seq_mode = 0;

		अगर (retval == -ETIMEDOUT)
			err = STATUS_TIMEDOUT;
		अन्यथा
			err = STATUS_FAIL;

		rtsx_पढ़ो_रेजिस्टर(chip, REG_SD_STAT1, &stat);
		rtsx_clear_sd_error(chip);
		अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
			chip->rw_need_retry = 0;
			dev_dbg(rtsx_dev(chip), "No card exist, exit %s\n",
				__func__);
			वापस STATUS_FAIL;
		पूर्ण

		chip->rw_need_retry = 1;

		retval = sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
					     SD_RSP_TYPE_R1b, शून्य, 0);
		अगर (retval != STATUS_SUCCESS) अणु
			sd_set_err_code(chip, SD_STS_ERR);
			जाओ RW_FAIL;
		पूर्ण

		अगर (stat & (SD_CRC7_ERR | SD_CRC16_ERR | SD_CRC_WRITE_ERR)) अणु
			dev_dbg(rtsx_dev(chip), "SD CRC error, tune clock!\n");
			sd_set_err_code(chip, SD_CRC_ERR);
			जाओ RW_FAIL;
		पूर्ण

		अगर (err == STATUS_TIMEDOUT) अणु
			sd_set_err_code(chip, SD_TO_ERR);
			जाओ RW_FAIL;
		पूर्ण

		वापस err;
	पूर्ण

	sd_card->pre_sec_addr = start_sector;
	sd_card->pre_sec_cnt = sector_cnt;
	sd_card->pre_dir = srb->sc_data_direction;

	वापस STATUS_SUCCESS;

RW_FAIL:
	sd_card->seq_mode = 0;

	अगर (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) अणु
		chip->rw_need_retry = 0;
		dev_dbg(rtsx_dev(chip), "No card exist, exit %s\n", __func__);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (sd_check_err_code(chip, SD_CRC_ERR)) अणु
		अगर (CHK_MMC_4BIT(sd_card) || CHK_MMC_8BIT(sd_card)) अणु
			sd_card->mmc_करोnt_चयन_bus = 1;
			reset_mmc_only(chip);
			sd_card->mmc_करोnt_चयन_bus = 0;
		पूर्ण अन्यथा अणु
			sd_card->need_retune = 1;
			sd_स्वतः_tune_घड़ी(chip);
		पूर्ण
	पूर्ण अन्यथा अगर (sd_check_err_code(chip, SD_TO_ERR | SD_STS_ERR)) अणु
		retval = reset_sd_card(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			chip->card_पढ़ोy &= ~SD_CARD;
			chip->card_fail |= SD_CARD;
			chip->capacity[chip->card2lun[SD_CARD]] = 0;
		पूर्ण
	पूर्ण

	वापस STATUS_FAIL;
पूर्ण

#अगर_घोषित SUPPORT_CPRM
पूर्णांक ext_sd_send_cmd_get_rsp(काष्ठा rtsx_chip *chip, u8 cmd_idx, u32 arg,
			    u8 rsp_type, u8 *rsp, पूर्णांक rsp_len,
			    bool special_check)
अणु
	पूर्णांक retval;
	पूर्णांक समयout = 100;
	u16 reg_addr;
	u8 *ptr;
	पूर्णांक stat_idx = 0;
	पूर्णांक rty_cnt = 0;

	dev_dbg(rtsx_dev(chip), "EXT SD/MMC CMD %d\n", cmd_idx);

	अगर (rsp_type == SD_RSP_TYPE_R1b)
		समयout = 3000;

RTY_SEND_CMD:

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF, 0x40 | cmd_idx);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD1, 0xFF, (u8)(arg >> 24));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD2, 0xFF, (u8)(arg >> 16));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD3, 0xFF, (u8)(arg >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD4, 0xFF, (u8)arg);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, rsp_type);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER,
		     0xFF, SD_TM_CMD_RSP | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	अगर (rsp_type == SD_RSP_TYPE_R2) अणु
		क्रम (reg_addr = PPBUF_BASE2; reg_addr < PPBUF_BASE2 + 16;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

		stat_idx = 17;
	पूर्ण अन्यथा अगर (rsp_type != SD_RSP_TYPE_R0) अणु
		क्रम (reg_addr = REG_SD_CMD0; reg_addr <= REG_SD_CMD4;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

		stat_idx = 6;
	पूर्ण
	rtsx_add_cmd(chip, READ_REG_CMD, REG_SD_CMD5, 0, 0);

	rtsx_add_cmd(chip, READ_REG_CMD, REG_SD_STAT1, 0, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, समयout);
	अगर (retval < 0) अणु
		अगर (retval == -ETIMEDOUT) अणु
			rtsx_clear_sd_error(chip);

			अगर (rsp_type & SD_WAIT_BUSY_END) अणु
				retval = sd_check_data0_status(chip);
				अगर (retval != STATUS_SUCCESS)
					वापस retval;
			पूर्ण अन्यथा अणु
				sd_set_err_code(chip, SD_TO_ERR);
			पूर्ण
		पूर्ण
		वापस STATUS_FAIL;
	पूर्ण

	अगर (rsp_type == SD_RSP_TYPE_R0)
		वापस STATUS_SUCCESS;

	ptr = rtsx_get_cmd_data(chip) + 1;

	अगर ((ptr[0] & 0xC0) != 0) अणु
		sd_set_err_code(chip, SD_STS_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (!(rsp_type & SD_NO_CHECK_CRC7)) अणु
		अगर (ptr[stat_idx] & SD_CRC7_ERR) अणु
			अगर (cmd_idx == WRITE_MULTIPLE_BLOCK) अणु
				sd_set_err_code(chip, SD_CRC_ERR);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (rty_cnt < SD_MAX_RETRY_COUNT) अणु
				रुको_समयout(20);
				rty_cnt++;
				जाओ RTY_SEND_CMD;
			पूर्ण अन्यथा अणु
				sd_set_err_code(chip, SD_CRC_ERR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((cmd_idx == SELECT_CARD) || (cmd_idx == APP_CMD) ||
	    (cmd_idx == SEND_STATUS) || (cmd_idx == STOP_TRANSMISSION)) अणु
		अगर ((cmd_idx != STOP_TRANSMISSION) && !special_check) अणु
			अगर (ptr[1] & 0x80)
				वापस STATUS_FAIL;
		पूर्ण
#अगर_घोषित SUPPORT_SD_LOCK
		अगर (ptr[1] & 0x7D) अणु
#अन्यथा
		अगर (ptr[1] & 0x7F) अणु
#पूर्ण_अगर
			वापस STATUS_FAIL;
		पूर्ण
		अगर (ptr[2] & 0xF8)
			वापस STATUS_FAIL;

		अगर (cmd_idx == SELECT_CARD) अणु
			अगर (rsp_type == SD_RSP_TYPE_R2) अणु
				अगर ((ptr[3] & 0x1E) != 0x04)
					वापस STATUS_FAIL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rsp && rsp_len)
		स_नकल(rsp, ptr, rsp_len);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक ext_sd_get_rsp(काष्ठा rtsx_chip *chip, पूर्णांक len, u8 *rsp, u8 rsp_type)
अणु
	पूर्णांक retval, rsp_len;
	u16 reg_addr;

	अगर (rsp_type == SD_RSP_TYPE_R0)
		वापस STATUS_SUCCESS;

	rtsx_init_cmd(chip);

	अगर (rsp_type == SD_RSP_TYPE_R2) अणु
		क्रम (reg_addr = PPBUF_BASE2; reg_addr < PPBUF_BASE2 + 16;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0xFF, 0);

		rsp_len = 17;
	पूर्ण अन्यथा अगर (rsp_type != SD_RSP_TYPE_R0) अणु
		क्रम (reg_addr = REG_SD_CMD0; reg_addr <= REG_SD_CMD4;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0xFF, 0);

		rsp_len = 6;
	पूर्ण
	rtsx_add_cmd(chip, READ_REG_CMD, REG_SD_CMD5, 0xFF, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, 100);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (rsp) अणु
		पूर्णांक min_len = (rsp_len < len) ? rsp_len : len;

		स_नकल(rsp, rtsx_get_cmd_data(chip), min_len);

		dev_dbg(rtsx_dev(chip), "min_len = %d\n", min_len);
		dev_dbg(rtsx_dev(chip), "Response in cmd buf: 0x%x 0x%x 0x%x 0x%x\n",
			rsp[0], rsp[1], rsp[2], rsp[3]);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक sd_pass_thru_mode(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक len;
	u8 buf[18] = अणु
		0x00,
		0x00,
		0x00,
		0x0E,
		0x00,
		0x00,
		0x00,
		0x00,
		0x53,
		0x44,
		0x20,
		0x43,
		0x61,
		0x72,
		0x64,
		0x00,
		0x00,
		0x00,
	पूर्ण;

	sd_card->pre_cmd_err = 0;

	अगर (!(CHK_BIT(chip->lun_mc, lun))) अणु
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर ((srb->cmnd[2] != 0x53) || (srb->cmnd[3] != 0x44) ||
	    (srb->cmnd[4] != 0x20) || (srb->cmnd[5] != 0x43) ||
	    (srb->cmnd[6] != 0x61) || (srb->cmnd[7] != 0x72) ||
	    (srb->cmnd[8] != 0x64)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	चयन (srb->cmnd[1] & 0x0F) अणु
	हाल 0:
		sd_card->sd_pass_thru_en = 0;
		अवरोध;

	हाल 1:
		sd_card->sd_pass_thru_en = 1;
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	buf[5] = (CHK_SD(sd_card) == 1) ? 0x01 : 0x02;
	अगर (chip->card_wp & SD_CARD)
		buf[5] |= 0x80;

	buf[6] = (u8)(sd_card->sd_addr >> 16);
	buf[7] = (u8)(sd_card->sd_addr >> 24);

	buf[15] = chip->max_lun;

	len = min_t(पूर्णांक, 18, scsi_bufflen(srb));
	rtsx_stor_set_xfer_buf(buf, len, srb);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल अंतरभूत पूर्णांक get_rsp_type(काष्ठा scsi_cmnd *srb, u8 *rsp_type,
			       पूर्णांक *rsp_len)
अणु
	अगर (!rsp_type || !rsp_len)
		वापस STATUS_FAIL;

	चयन (srb->cmnd[10]) अणु
	हाल 0x03:
		*rsp_type = SD_RSP_TYPE_R0;
		*rsp_len = 0;
		अवरोध;

	हाल 0x04:
		*rsp_type = SD_RSP_TYPE_R1;
		*rsp_len = 6;
		अवरोध;

	हाल 0x05:
		*rsp_type = SD_RSP_TYPE_R1b;
		*rsp_len = 6;
		अवरोध;

	हाल 0x06:
		*rsp_type = SD_RSP_TYPE_R2;
		*rsp_len = 17;
		अवरोध;

	हाल 0x07:
		*rsp_type = SD_RSP_TYPE_R3;
		*rsp_len = 6;
		अवरोध;

	शेष:
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक sd_execute_no_data(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval, rsp_len;
	u8 cmd_idx, rsp_type;
	bool standby = false, acmd = false;
	u32 arg;

	अगर (!sd_card->sd_pass_thru_en) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

	अगर (sd_card->pre_cmd_err) अणु
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	cmd_idx = srb->cmnd[2] & 0x3F;
	अगर (srb->cmnd[1] & 0x02)
		standby = true;

	अगर (srb->cmnd[1] & 0x01)
		acmd = true;

	arg = ((u32)srb->cmnd[3] << 24) | ((u32)srb->cmnd[4] << 16) |
		((u32)srb->cmnd[5] << 8) | srb->cmnd[6];

	retval = get_rsp_type(srb, &rsp_type, &rsp_len);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण
	sd_card->last_rsp_type = rsp_type;

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर ((sd_card->sd_lock_status & SD_LOCK_1BIT_MODE) == 0) अणु
		अगर (CHK_MMC_8BIT(sd_card)) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_8);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अगर (CHK_SD(sd_card) || CHK_MMC_4BIT(sd_card)) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_4);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण
#अन्यथा
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x03, SD_BUS_WIDTH_4);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;
#पूर्ण_अगर

	अगर (standby) अणु
		retval = sd_select_card(chip, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_cmd_failed;
	पूर्ण

	अगर (acmd) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, APP_CMD,
						 sd_card->sd_addr,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_cmd_failed;
	पूर्ण

	retval = ext_sd_send_cmd_get_rsp(chip, cmd_idx, arg, rsp_type,
					 sd_card->rsp, rsp_len, false);
	अगर (retval != STATUS_SUCCESS)
		जाओ sd_execute_cmd_failed;

	अगर (standby) अणु
		retval = sd_select_card(chip, 1);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_cmd_failed;
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	retval = sd_update_lock_status(chip);
	अगर (retval != STATUS_SUCCESS)
		जाओ sd_execute_cmd_failed;
#पूर्ण_अगर

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;

sd_execute_cmd_failed:
	sd_card->pre_cmd_err = 1;
	set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
	release_sd_card(chip);
	करो_reset_sd_card(chip);
	अगर (!(chip->card_पढ़ोy & SD_CARD))
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);

	वापस TRANSPORT_FAILED;
पूर्ण

पूर्णांक sd_execute_पढ़ो_data(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval, rsp_len, i;
	bool पढ़ो_err = false, cmd13_checkbit = false;
	u8 cmd_idx, rsp_type, bus_width;
	bool standby = false, send_cmd12 = false, acmd = false;
	u32 data_len;

	अगर (!sd_card->sd_pass_thru_en) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (sd_card->pre_cmd_err) अणु
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

	cmd_idx = srb->cmnd[2] & 0x3F;
	अगर (srb->cmnd[1] & 0x04)
		send_cmd12 = true;

	अगर (srb->cmnd[1] & 0x02)
		standby = true;

	अगर (srb->cmnd[1] & 0x01)
		acmd = true;

	data_len = ((u32)srb->cmnd[7] << 16) | ((u32)srb->cmnd[8]
						<< 8) | srb->cmnd[9];

	retval = get_rsp_type(srb, &rsp_type, &rsp_len);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण
	sd_card->last_rsp_type = rsp_type;

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर ((sd_card->sd_lock_status & SD_LOCK_1BIT_MODE) == 0) अणु
		अगर (CHK_MMC_8BIT(sd_card))
			bus_width = SD_BUS_WIDTH_8;
		अन्यथा अगर (CHK_SD(sd_card) || CHK_MMC_4BIT(sd_card))
			bus_width = SD_BUS_WIDTH_4;
		अन्यथा
			bus_width = SD_BUS_WIDTH_1;
	पूर्ण अन्यथा अणु
		bus_width = SD_BUS_WIDTH_4;
	पूर्ण
	dev_dbg(rtsx_dev(chip), "bus_width = %d\n", bus_width);
#अन्यथा
	bus_width = SD_BUS_WIDTH_4;
#पूर्ण_अगर

	अगर (data_len < 512) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, data_len,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	अगर (standby) अणु
		retval = sd_select_card(chip, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	अगर (acmd) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, APP_CMD,
						 sd_card->sd_addr,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	अगर (data_len <= 512) अणु
		पूर्णांक min_len;
		u8 *buf;
		u16 byte_cnt, blk_cnt;
		u8 cmd[5];

		byte_cnt = ((u16)(srb->cmnd[8] & 0x03) << 8) | srb->cmnd[9];
		blk_cnt = 1;

		cmd[0] = 0x40 | cmd_idx;
		cmd[1] = srb->cmnd[3];
		cmd[2] = srb->cmnd[4];
		cmd[3] = srb->cmnd[5];
		cmd[4] = srb->cmnd[6];

		buf = kदो_स्मृति(data_len, GFP_KERNEL);
		अगर (!buf)
			वापस TRANSPORT_ERROR;

		retval = sd_पढ़ो_data(chip, SD_TM_NORMAL_READ, cmd, 5, byte_cnt,
				      blk_cnt, bus_width, buf, data_len, 2000);
		अगर (retval != STATUS_SUCCESS) अणु
			पढ़ो_err = true;
			kमुक्त(buf);
			rtsx_clear_sd_error(chip);
			जाओ sd_execute_पढ़ो_cmd_failed;
		पूर्ण

		min_len = min(data_len, scsi_bufflen(srb));
		rtsx_stor_set_xfer_buf(buf, min_len, srb);

		kमुक्त(buf);
	पूर्ण अन्यथा अगर (!(data_len & 0x1FF)) अणु
		rtsx_init_cmd(chip);

		trans_dma_enable(DMA_FROM_DEVICE, chip, data_len, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
			     0x02);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
			     0x00);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H,
			     0xFF, (srb->cmnd[7] & 0xFE) >> 1);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L,
			     0xFF, (u8)((data_len & 0x0001FE00) >> 9));

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF,
			     0x40 | cmd_idx);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD1, 0xFF,
			     srb->cmnd[3]);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD2, 0xFF,
			     srb->cmnd[4]);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD3, 0xFF,
			     srb->cmnd[5]);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD4, 0xFF,
			     srb->cmnd[6]);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1, 0x03, bus_width);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, rsp_type);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER,
			     0xFF, SD_TM_AUTO_READ_2 | SD_TRANSFER_START);
		rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
			     SD_TRANSFER_END, SD_TRANSFER_END);

		rtsx_send_cmd_no_रुको(chip);

		retval = rtsx_transfer_data(chip, SD_CARD, scsi_sglist(srb),
					    scsi_bufflen(srb),
					    scsi_sg_count(srb),
					    DMA_FROM_DEVICE, 10000);
		अगर (retval < 0) अणु
			पढ़ो_err = true;
			rtsx_clear_sd_error(chip);
			जाओ sd_execute_पढ़ो_cmd_failed;
		पूर्ण

	पूर्ण अन्यथा अणु
		जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	retval = ext_sd_get_rsp(chip, rsp_len, sd_card->rsp, rsp_type);
	अगर (retval != STATUS_SUCCESS)
		जाओ sd_execute_पढ़ो_cmd_failed;

	अगर (standby) अणु
		retval = sd_select_card(chip, 1);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	अगर (send_cmd12) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
						 SD_RSP_TYPE_R1b, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	अगर (data_len < 512) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, 0x200,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BYTE_CNT_H, 0xFF, 0x02);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BYTE_CNT_L, 0xFF, 0x00);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_पढ़ो_cmd_failed;
	पूर्ण

	अगर ((srb->cmnd[1] & 0x02) || (srb->cmnd[1] & 0x04))
		cmd13_checkbit = true;

	क्रम (i = 0; i < 3; i++) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, SEND_STATUS,
						 sd_card->sd_addr,
						SD_RSP_TYPE_R1, शून्य, 0,
						cmd13_checkbit);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (retval != STATUS_SUCCESS)
		जाओ sd_execute_पढ़ो_cmd_failed;

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;

sd_execute_पढ़ो_cmd_failed:
	sd_card->pre_cmd_err = 1;
	set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
	अगर (पढ़ो_err)
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);

	release_sd_card(chip);
	करो_reset_sd_card(chip);
	अगर (!(chip->card_पढ़ोy & SD_CARD))
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);

	वापस TRANSPORT_FAILED;
पूर्ण

पूर्णांक sd_execute_ग_लिखो_data(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval, rsp_len, i;
	bool ग_लिखो_err = false, cmd13_checkbit = false;
	u8 cmd_idx, rsp_type;
	bool standby = false, send_cmd12 = false, acmd = false;
	u32 data_len, arg;
#अगर_घोषित SUPPORT_SD_LOCK
	पूर्णांक lock_cmd_fail = 0;
	u8 sd_lock_state = 0;
	u8 lock_cmd_type = 0;
#पूर्ण_अगर

	अगर (!sd_card->sd_pass_thru_en) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (sd_card->pre_cmd_err) अणु
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

	cmd_idx = srb->cmnd[2] & 0x3F;
	अगर (srb->cmnd[1] & 0x04)
		send_cmd12 = true;

	अगर (srb->cmnd[1] & 0x02)
		standby = true;

	अगर (srb->cmnd[1] & 0x01)
		acmd = true;

	data_len = ((u32)srb->cmnd[7] << 16) | ((u32)srb->cmnd[8]
						<< 8) | srb->cmnd[9];
	arg = ((u32)srb->cmnd[3] << 24) | ((u32)srb->cmnd[4] << 16) |
		((u32)srb->cmnd[5] << 8) | srb->cmnd[6];

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (cmd_idx == LOCK_UNLOCK) अणु
		sd_lock_state = sd_card->sd_lock_status;
		sd_lock_state &= SD_LOCKED;
	पूर्ण
#पूर्ण_अगर

	retval = get_rsp_type(srb, &rsp_type, &rsp_len);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण
	sd_card->last_rsp_type = rsp_type;

	retval = sd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर ((sd_card->sd_lock_status & SD_LOCK_1BIT_MODE) == 0) अणु
		अगर (CHK_MMC_8BIT(sd_card)) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_8);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अगर (CHK_SD(sd_card) || CHK_MMC_4BIT(sd_card)) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_4);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण
#अन्यथा
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, REG_SD_CFG1, 0x03, SD_BUS_WIDTH_4);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;
#पूर्ण_अगर

	अगर (data_len < 512) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, data_len,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	अगर (standby) अणु
		retval = sd_select_card(chip, 0);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	अगर (acmd) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, APP_CMD,
						 sd_card->sd_addr,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	retval = ext_sd_send_cmd_get_rsp(chip, cmd_idx, arg, rsp_type,
					 sd_card->rsp, rsp_len, false);
	अगर (retval != STATUS_SUCCESS)
		जाओ sd_execute_ग_लिखो_cmd_failed;

	अगर (data_len <= 512) अणु
		u16 i;
		u8 *buf;

		buf = kदो_स्मृति(data_len, GFP_KERNEL);
		अगर (!buf)
			वापस TRANSPORT_ERROR;

		rtsx_stor_get_xfer_buf(buf, data_len, srb);

#अगर_घोषित SUPPORT_SD_LOCK
		अगर (cmd_idx == LOCK_UNLOCK)
			lock_cmd_type = buf[0] & 0x0F;
#पूर्ण_अगर

		अगर (data_len > 256) अणु
			rtsx_init_cmd(chip);
			क्रम (i = 0; i < 256; i++) अणु
				rtsx_add_cmd(chip, WRITE_REG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			पूर्ण
			retval = rtsx_send_cmd(chip, 0, 250);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				जाओ sd_execute_ग_लिखो_cmd_failed;
			पूर्ण

			rtsx_init_cmd(chip);
			क्रम (i = 256; i < data_len; i++) अणु
				rtsx_add_cmd(chip, WRITE_REG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			पूर्ण
			retval = rtsx_send_cmd(chip, 0, 250);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				जाओ sd_execute_ग_लिखो_cmd_failed;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtsx_init_cmd(chip);
			क्रम (i = 0; i < data_len; i++) अणु
				rtsx_add_cmd(chip, WRITE_REG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			पूर्ण
			retval = rtsx_send_cmd(chip, 0, 250);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				जाओ sd_execute_ग_लिखो_cmd_failed;
			पूर्ण
		पूर्ण

		kमुक्त(buf);

		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
			     srb->cmnd[8] & 0x03);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
			     srb->cmnd[9]);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
			     0x00);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
			     0x01);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
			     PINGPONG_BUFFER);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
			     SD_TM_AUTO_WRITE_3 | SD_TRANSFER_START);
		rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
			     SD_TRANSFER_END, SD_TRANSFER_END);

		retval = rtsx_send_cmd(chip, SD_CARD, 250);
	पूर्ण अन्यथा अगर (!(data_len & 0x1FF)) अणु
		rtsx_init_cmd(chip);

		trans_dma_enable(DMA_TO_DEVICE, chip, data_len, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
			     0x02);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
			     0x00);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H,
			     0xFF, (srb->cmnd[7] & 0xFE) >> 1);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L,
			     0xFF, (u8)((data_len & 0x0001FE00) >> 9));

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
			     SD_TM_AUTO_WRITE_3 | SD_TRANSFER_START);
		rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
			     SD_TRANSFER_END, SD_TRANSFER_END);

		rtsx_send_cmd_no_रुको(chip);

		retval = rtsx_transfer_data(chip, SD_CARD, scsi_sglist(srb),
					    scsi_bufflen(srb),
					    scsi_sg_count(srb),
					    DMA_TO_DEVICE, 10000);

	पूर्ण अन्यथा अणु
		जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	अगर (retval < 0) अणु
		ग_लिखो_err = true;
		rtsx_clear_sd_error(chip);
		जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (cmd_idx == LOCK_UNLOCK) अणु
		अगर (lock_cmd_type == SD_ERASE) अणु
			sd_card->sd_erase_status = SD_UNDER_ERASING;
			scsi_set_resid(srb, 0);
			वापस TRANSPORT_GOOD;
		पूर्ण

		rtsx_init_cmd(chip);
		rtsx_add_cmd(chip, CHECK_REG_CMD, 0xFD30, 0x02, 0x02);

		retval = rtsx_send_cmd(chip, SD_CARD, 250);
		अगर (retval < 0) अणु
			ग_लिखो_err = true;
			rtsx_clear_sd_error(chip);
			जाओ sd_execute_ग_लिखो_cmd_failed;
		पूर्ण

		retval = sd_update_lock_status(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			dev_dbg(rtsx_dev(chip), "Lock command fail!\n");
			lock_cmd_fail = 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* SUPPORT_SD_LOCK */

	अगर (standby) अणु
		retval = sd_select_card(chip, 1);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	अगर (send_cmd12) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
						 SD_RSP_TYPE_R1b, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	अगर (data_len < 512) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, 0x200,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 false);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BYTE_CNT_H, 0xFF, 0x02);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_BYTE_CNT_L, 0xFF, 0x00);
		अगर (retval != STATUS_SUCCESS)
			जाओ sd_execute_ग_लिखो_cmd_failed;
	पूर्ण

	अगर ((srb->cmnd[1] & 0x02) || (srb->cmnd[1] & 0x04))
		cmd13_checkbit = true;

	क्रम (i = 0; i < 3; i++) अणु
		retval = ext_sd_send_cmd_get_rsp(chip, SEND_STATUS,
						 sd_card->sd_addr,
						 SD_RSP_TYPE_R1, शून्य, 0,
						 cmd13_checkbit);
		अगर (retval == STATUS_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (retval != STATUS_SUCCESS)
		जाओ sd_execute_ग_लिखो_cmd_failed;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (cmd_idx == LOCK_UNLOCK) अणु
		अगर (!lock_cmd_fail) अणु
			dev_dbg(rtsx_dev(chip), "lock_cmd_type = 0x%x\n",
				lock_cmd_type);
			अगर (lock_cmd_type & SD_CLR_PWD)
				sd_card->sd_lock_status &= ~SD_PWD_EXIST;

			अगर (lock_cmd_type & SD_SET_PWD)
				sd_card->sd_lock_status |= SD_PWD_EXIST;
		पूर्ण

		dev_dbg(rtsx_dev(chip), "sd_lock_state = 0x%x, sd_card->sd_lock_status = 0x%x\n",
			sd_lock_state, sd_card->sd_lock_status);
		अगर (sd_lock_state ^ (sd_card->sd_lock_status & SD_LOCKED)) अणु
			sd_card->sd_lock_notअगरy = 1;
			अगर (sd_lock_state &&
			    (sd_card->sd_lock_status & SD_LOCK_1BIT_MODE)) अणु
				sd_card->sd_lock_status |= (
					SD_UNLOCK_POW_ON | SD_SDR_RST);
				अगर (CHK_SD(sd_card)) अणु
					retval = reset_sd(chip);
					अगर (retval != STATUS_SUCCESS) अणु
						sd_card->sd_lock_status &= ~(SD_UNLOCK_POW_ON | SD_SDR_RST);
						जाओ sd_execute_ग_लिखो_cmd_failed;
					पूर्ण
				पूर्ण

				sd_card->sd_lock_status &= ~(SD_UNLOCK_POW_ON | SD_SDR_RST);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (lock_cmd_fail) अणु
		scsi_set_resid(srb, 0);
		set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
		वापस TRANSPORT_FAILED;
	पूर्ण
#पूर्ण_अगर  /* SUPPORT_SD_LOCK */

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;

sd_execute_ग_लिखो_cmd_failed:
	sd_card->pre_cmd_err = 1;
	set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
	अगर (ग_लिखो_err)
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_ERR);

	release_sd_card(chip);
	करो_reset_sd_card(chip);
	अगर (!(chip->card_पढ़ोy & SD_CARD))
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);

	वापस TRANSPORT_FAILED;
पूर्ण

पूर्णांक sd_get_cmd_rsp(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक count;
	u16 data_len;

	अगर (!sd_card->sd_pass_thru_en) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (sd_card->pre_cmd_err) अणु
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	data_len = ((u16)srb->cmnd[7] << 8) | srb->cmnd[8];

	अगर (sd_card->last_rsp_type == SD_RSP_TYPE_R0) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण अन्यथा अगर (sd_card->last_rsp_type == SD_RSP_TYPE_R2) अणु
		count = (data_len < 17) ? data_len : 17;
	पूर्ण अन्यथा अणु
		count = (data_len < 6) ? data_len : 6;
	पूर्ण
	rtsx_stor_set_xfer_buf(sd_card->rsp, count, srb);

	dev_dbg(rtsx_dev(chip), "Response length: %d\n", data_len);
	dev_dbg(rtsx_dev(chip), "Response: 0x%x 0x%x 0x%x 0x%x\n",
		sd_card->rsp[0], sd_card->rsp[1],
		sd_card->rsp[2], sd_card->rsp[3]);

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;
पूर्ण

पूर्णांक sd_hw_rst(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval;

	अगर (!sd_card->sd_pass_thru_en) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (sd_card->pre_cmd_err) अणु
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर ((srb->cmnd[2] != 0x53) || (srb->cmnd[3] != 0x44) ||
	    (srb->cmnd[4] != 0x20) || (srb->cmnd[5] != 0x43) ||
	    (srb->cmnd[6] != 0x61) || (srb->cmnd[7] != 0x72) ||
	    (srb->cmnd[8] != 0x64)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	चयन (srb->cmnd[1] & 0x0F) अणु
	हाल 0:
#अगर_घोषित SUPPORT_SD_LOCK
		अगर (srb->cmnd[9] == 0x64)
			sd_card->sd_lock_status |= SD_SDR_RST;
#पूर्ण_अगर
		retval = reset_sd_card(chip);
		अगर (retval != STATUS_SUCCESS) अणु
#अगर_घोषित SUPPORT_SD_LOCK
			sd_card->sd_lock_status &= ~SD_SDR_RST;
#पूर्ण_अगर
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			sd_card->pre_cmd_err = 1;
			वापस TRANSPORT_FAILED;
		पूर्ण
#अगर_घोषित SUPPORT_SD_LOCK
		sd_card->sd_lock_status &= ~SD_SDR_RST;
#पूर्ण_अगर
		अवरोध;

	हाल 1:
		retval = reset_sd(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			sd_card->pre_cmd_err = 1;
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;
पूर्ण
#पूर्ण_अगर

व्योम sd_cleanup_work(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;

	अगर (sd_card->seq_mode) अणु
		dev_dbg(rtsx_dev(chip), "SD: stop transmission\n");
		sd_stop_seq_mode(chip);
		sd_card->cleanup_counter = 0;
	पूर्ण
पूर्ण

पूर्णांक sd_घातer_off_card3v3(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = disable_card_घड़ी(chip, SD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SD_OUTPUT_EN, 0);
	अगर (retval)
		वापस retval;

	अगर (!chip->ft2_fast_mode) अणु
		retval = card_घातer_off(chip, SD_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		mdelay(50);
	पूर्ण

	अगर (chip->asic_code) अणु
		retval = sd_pull_ctl_disable(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL,
					     FPGA_SD_PULL_CTL_BIT | 0x20,
					     FPGA_SD_PULL_CTL_BIT);
		अगर (retval)
			वापस retval;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक release_sd_card(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	पूर्णांक retval;

	chip->card_पढ़ोy &= ~SD_CARD;
	chip->card_fail &= ~SD_CARD;
	chip->card_wp &= ~SD_CARD;

	chip->sd_io = 0;
	chip->sd_पूर्णांक = 0;

#अगर_घोषित SUPPORT_SD_LOCK
	sd_card->sd_lock_status = 0;
	sd_card->sd_erase_status = 0;
#पूर्ण_अगर

	स_रखो(sd_card->raw_csd, 0, 16);
	स_रखो(sd_card->raw_scr, 0, 8);

	retval = sd_घातer_off_card3v3(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण
