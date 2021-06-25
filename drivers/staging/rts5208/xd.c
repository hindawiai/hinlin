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
#समावेश "rtsx_transport.h"
#समावेश "rtsx_scsi.h"
#समावेश "rtsx_card.h"
#समावेश "xd.h"

अटल पूर्णांक xd_build_l2p_tbl(काष्ठा rtsx_chip *chip, पूर्णांक zone_no);
अटल पूर्णांक xd_init_page(काष्ठा rtsx_chip *chip, u32 phy_blk, u16 logoff,
			u8 start_page, u8 end_page);

अटल अंतरभूत व्योम xd_set_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;

	xd_card->err_code = err_code;
पूर्ण

अटल अंतरभूत पूर्णांक xd_check_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;

	वापस (xd_card->err_code == err_code);
पूर्ण

अटल पूर्णांक xd_set_init_para(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval;

	अगर (chip->asic_code)
		xd_card->xd_घड़ी = 47;
	अन्यथा
		xd_card->xd_घड़ी = CLK_50;

	retval = चयन_घड़ी(chip, xd_card->xd_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_चयन_घड़ी(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval;

	retval = select_card(chip, XD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = चयन_घड़ी(chip, xd_card->xd_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_पढ़ो_id(काष्ठा rtsx_chip *chip, u8 id_cmd, u8 *id_buf, u8 buf_len)
अणु
	पूर्णांक retval, i;
	u8 *ptr;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_DAT, 0xFF, id_cmd);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_READ_ID);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER, XD_TRANSFER_END,
		     XD_TRANSFER_END);

	क्रम (i = 0; i < 4; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, (u16)(XD_ADDRESS1 + i), 0, 0);

	retval = rtsx_send_cmd(chip, XD_CARD, 20);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	ptr = rtsx_get_cmd_data(chip) + 1;
	अगर (id_buf && buf_len) अणु
		अगर (buf_len > 4)
			buf_len = 4;
		स_नकल(id_buf, ptr, buf_len);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल व्योम xd_assign_phy_addr(काष्ठा rtsx_chip *chip, u32 addr, u8 mode)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;

	चयन (mode) अणु
	हाल XD_RW_ADDR:
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS0, 0xFF, 0);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS1, 0xFF, (u8)addr);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS2,
			     0xFF, (u8)(addr >> 8));
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS3,
			     0xFF, (u8)(addr >> 16));
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CFG, 0xFF,
			     xd_card->addr_cycle |
			     XD_CALC_ECC |
			     XD_BA_NO_TRANSFORM);
		अवरोध;

	हाल XD_ERASE_ADDR:
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS0, 0xFF, (u8)addr);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS1,
			     0xFF, (u8)(addr >> 8));
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_ADDRESS2,
			     0xFF, (u8)(addr >> 16));
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CFG, 0xFF,
			     (xd_card->addr_cycle - 1) | XD_CALC_ECC |
			XD_BA_NO_TRANSFORM);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xd_पढ़ो_redundant(काष्ठा rtsx_chip *chip, u32 page_addr,
			     u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक retval, i;

	rtsx_init_cmd(chip);

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER,
		     0xFF, XD_TRANSFER_START | XD_READ_REDUNDANT);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	क्रम (i = 0; i < 6; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, (u16)(XD_PAGE_STATUS + i),
			     0, 0);
	क्रम (i = 0; i < 4; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, (u16)(XD_RESERVED0 + i),
			     0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, XD_PARITY, 0, 0);

	retval = rtsx_send_cmd(chip, XD_CARD, 500);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	अगर (buf && buf_len) अणु
		u8 *ptr = rtsx_get_cmd_data(chip) + 1;

		अगर (buf_len > 11)
			buf_len = 11;
		स_नकल(buf, ptr, buf_len);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_पढ़ो_data_from_ppb(काष्ठा rtsx_chip *chip, पूर्णांक offset,
				 u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक retval, i;

	अगर (!buf || (buf_len < 0))
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	क्रम (i = 0; i < buf_len; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + offset + i,
			     0, 0);

	retval = rtsx_send_cmd(chip, 0, 250);
	अगर (retval < 0) अणु
		rtsx_clear_xd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	स_नकल(buf, rtsx_get_cmd_data(chip), buf_len);

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_पढ़ो_cis(काष्ठा rtsx_chip *chip, u32 page_addr, u8 *buf,
		       पूर्णांक buf_len)
अणु
	पूर्णांक retval;
	u8 reg;

	अगर (!buf || (buf_len < 10))
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CHK_DATA_STATUS,
		     XD_AUTO_CHK_DATA_STATUS, XD_AUTO_CHK_DATA_STATUS);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_READ_PAGES);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER, XD_TRANSFER_END,
		     XD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, XD_CARD, 250);
	अगर (retval == -ETIMEDOUT) अणु
		rtsx_clear_xd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_PAGE_STATUS, &reg);
	अगर (retval)
		वापस retval;
	अगर (reg != XD_GPG) अणु
		rtsx_clear_xd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_CTL, &reg);
	अगर (retval)
		वापस retval;
	अगर (!(reg & XD_ECC1_ERROR) || !(reg & XD_ECC1_UNCORRECTABLE)) अणु
		retval = xd_पढ़ो_data_from_ppb(chip, 0, buf, buf_len);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
		अगर (reg & XD_ECC1_ERROR) अणु
			u8 ecc_bit, ecc_byte;

			retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_ECC_BIT1,
						    &ecc_bit);
			अगर (retval)
				वापस retval;
			retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_ECC_BYTE1,
						    &ecc_byte);
			अगर (retval)
				वापस retval;

			dev_dbg(rtsx_dev(chip), "ECC_BIT1 = 0x%x, ECC_BYTE1 = 0x%x\n",
				ecc_bit, ecc_byte);
			अगर (ecc_byte < buf_len) अणु
				dev_dbg(rtsx_dev(chip), "Before correct: 0x%x\n",
					buf[ecc_byte]);
				buf[ecc_byte] ^= (1 << ecc_bit);
				dev_dbg(rtsx_dev(chip), "After correct: 0x%x\n",
					buf[ecc_byte]);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!(reg & XD_ECC2_ERROR) || !(reg & XD_ECC2_UNCORRECTABLE)) अणु
		rtsx_clear_xd_error(chip);

		retval = xd_पढ़ो_data_from_ppb(chip, 256, buf, buf_len);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
		अगर (reg & XD_ECC2_ERROR) अणु
			u8 ecc_bit, ecc_byte;

			retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_ECC_BIT2,
						    &ecc_bit);
			अगर (retval)
				वापस retval;
			retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_ECC_BYTE2,
						    &ecc_byte);
			अगर (retval)
				वापस retval;

			dev_dbg(rtsx_dev(chip), "ECC_BIT2 = 0x%x, ECC_BYTE2 = 0x%x\n",
				ecc_bit, ecc_byte);
			अगर (ecc_byte < buf_len) अणु
				dev_dbg(rtsx_dev(chip), "Before correct: 0x%x\n",
					buf[ecc_byte]);
				buf[ecc_byte] ^= (1 << ecc_bit);
				dev_dbg(rtsx_dev(chip), "After correct: 0x%x\n",
					buf[ecc_byte]);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rtsx_clear_xd_error(chip);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल व्योम xd_fill_pull_ctl_disable(काष्ठा rtsx_chip *chip)
अणु
	अगर (CHECK_PID(chip, 0x5208)) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF,
			     XD_D3_PD | XD_D2_PD | XD_D1_PD | XD_D0_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF,
			     XD_D7_PD | XD_D6_PD | XD_D5_PD | XD_D4_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF,
			     XD_WP_PD | XD_CE_PD | XD_CLE_PD | XD_CD_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF,
			     XD_RDY_PD | XD_WE_PD | XD_RE_PD | XD_ALE_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF,
			     MS_INS_PU | SD_WP_PD | SD_CD_PU | SD_CMD_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		अगर (CHECK_BARO_PKG(chip, QFN)) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1,
				     0xFF, 0x55);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2,
				     0xFF, 0x55);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3,
				     0xFF, 0x4B);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4,
				     0xFF, 0x69);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xd_fill_pull_ctl_stage1_barossa(काष्ठा rtsx_chip *chip)
अणु
	अगर (CHECK_BARO_PKG(chip, QFN)) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0x55);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0x55);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0x4B);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x55);
	पूर्ण
पूर्ण

अटल व्योम xd_fill_pull_ctl_enable(काष्ठा rtsx_chip *chip)
अणु
	अगर (CHECK_PID(chip, 0x5208)) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF,
			     XD_D3_PD | XD_D2_PD | XD_D1_PD | XD_D0_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF,
			     XD_D7_PD | XD_D6_PD | XD_D5_PD | XD_D4_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF,
			     XD_WP_PD | XD_CE_PU | XD_CLE_PD | XD_CD_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF,
			     XD_RDY_PU | XD_WE_PU | XD_RE_PU | XD_ALE_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF,
			     MS_INS_PU | SD_WP_PD | SD_CD_PU | SD_CMD_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		अगर (CHECK_BARO_PKG(chip, QFN)) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1,
				     0xFF, 0x55);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2,
				     0xFF, 0x55);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3,
				     0xFF, 0x53);
			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4,
				     0xFF, 0xA9);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xd_pull_ctl_disable(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	अगर (CHECK_PID(chip, 0x5208)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL1, 0xFF,
					     XD_D3_PD |
					     XD_D2_PD |
					     XD_D1_PD |
					     XD_D0_PD);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL2, 0xFF,
					     XD_D7_PD |
					     XD_D6_PD |
					     XD_D5_PD |
					     XD_D4_PD);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL3, 0xFF,
					     XD_WP_PD |
					     XD_CE_PD |
					     XD_CLE_PD |
					     XD_CD_PU);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL4, 0xFF,
					     XD_RDY_PD |
					     XD_WE_PD |
					     XD_RE_PD |
					     XD_ALE_PD);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL5, 0xFF,
					     MS_INS_PU |
					     SD_WP_PD |
					     SD_CD_PU |
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

अटल पूर्णांक reset_xd(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval, i, j;
	u8 *ptr, id_buf[4], redunt[11];

	retval = select_card(chip, XD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CHK_DATA_STATUS, 0xFF,
		     XD_PGSTS_NOT_FF);
	अगर (chip->asic_code) अणु
		अगर (!CHECK_PID(chip, 0x5288))
			xd_fill_pull_ctl_disable(chip);
		अन्यथा
			xd_fill_pull_ctl_stage1_barossa(chip);
	पूर्ण अन्यथा अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, FPGA_PULL_CTL, 0xFF,
			     (FPGA_XD_PULL_CTL_EN1 & FPGA_XD_PULL_CTL_EN3) |
			     0x20);
	पूर्ण

	अगर (!chip->ft2_fast_mode)
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_INIT,
			     XD_NO_AUTO_PWR_OFF, 0);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_OE, XD_OUTPUT_EN, 0);

	retval = rtsx_send_cmd(chip, XD_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	अगर (!chip->ft2_fast_mode) अणु
		retval = card_घातer_off(chip, XD_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		रुको_समयout(250);

		rtsx_init_cmd(chip);

		अगर (chip->asic_code) अणु
			xd_fill_pull_ctl_enable(chip);
		पूर्ण अन्यथा अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, FPGA_PULL_CTL, 0xFF,
				     (FPGA_XD_PULL_CTL_EN1 &
				      FPGA_XD_PULL_CTL_EN2) |
				     0x20);
		पूर्ण

		retval = rtsx_send_cmd(chip, XD_CARD, 100);
		अगर (retval < 0)
			वापस STATUS_FAIL;

		retval = card_घातer_on(chip, XD_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

#अगर_घोषित SUPPORT_OCP
		रुको_समयout(50);
		अगर (chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) अणु
			dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			वापस STATUS_FAIL;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	rtsx_init_cmd(chip);

	अगर (chip->ft2_fast_mode) अणु
		अगर (chip->asic_code) अणु
			xd_fill_pull_ctl_enable(chip);
		पूर्ण अन्यथा अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, FPGA_PULL_CTL, 0xFF,
				     (FPGA_XD_PULL_CTL_EN1 &
				      FPGA_XD_PULL_CTL_EN2) |
				     0x20);
		पूर्ण
	पूर्ण

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_OE, XD_OUTPUT_EN, XD_OUTPUT_EN);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CTL, XD_CE_DISEN, XD_CE_DISEN);

	retval = rtsx_send_cmd(chip, XD_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	अगर (!chip->ft2_fast_mode)
		रुको_समयout(200);

	retval = xd_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	/* Read ID to check अगर the timing setting is right */
	क्रम (i = 0; i < 4; i++) अणु
		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_DTCTL, 0xFF,
			     XD_TIME_SETUP_STEP * 3 +
			     XD_TIME_RW_STEP * (2 + i) + XD_TIME_RWN_STEP * i);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CATCTL, 0xFF,
			     XD_TIME_SETUP_STEP * 3 +
			     XD_TIME_RW_STEP * (4 + i) +
			     XD_TIME_RWN_STEP * (3 + i));

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
			     XD_TRANSFER_START | XD_RESET);
		rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
			     XD_TRANSFER_END, XD_TRANSFER_END);

		rtsx_add_cmd(chip, READ_REG_CMD, XD_DAT, 0, 0);
		rtsx_add_cmd(chip, READ_REG_CMD, XD_CTL, 0, 0);

		retval = rtsx_send_cmd(chip, XD_CARD, 100);
		अगर (retval < 0)
			वापस STATUS_FAIL;

		ptr = rtsx_get_cmd_data(chip) + 1;

		dev_dbg(rtsx_dev(chip), "XD_DAT: 0x%x, XD_CTL: 0x%x\n",
			ptr[0], ptr[1]);

		अगर (((ptr[0] & READY_FLAG) != READY_STATE) ||
		    !(ptr[1] & XD_RDY))
			जारी;

		retval = xd_पढ़ो_id(chip, READ_ID, id_buf, 4);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		dev_dbg(rtsx_dev(chip), "READ_ID: 0x%x 0x%x 0x%x 0x%x\n",
			id_buf[0], id_buf[1], id_buf[2], id_buf[3]);

		xd_card->device_code = id_buf[1];

		/* Check अगर the xD card is supported */
		चयन (xd_card->device_code) अणु
		हाल XD_4M_X8_512_1:
		हाल XD_4M_X8_512_2:
			xd_card->block_shअगरt = 4;
			xd_card->page_off = 0x0F;
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 1;
			xd_card->capacity = 8000;
			XD_SET_4MB(xd_card);
			अवरोध;
		हाल XD_8M_X8_512:
			xd_card->block_shअगरt = 4;
			xd_card->page_off = 0x0F;
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 1;
			xd_card->capacity = 16000;
			अवरोध;
		हाल XD_16M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 1;
			xd_card->capacity = 32000;
			अवरोध;
		हाल XD_32M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 2;
			xd_card->capacity = 64000;
			अवरोध;
		हाल XD_64M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 4;
			xd_card->capacity = 128000;
			अवरोध;
		हाल XD_128M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 8;
			xd_card->capacity = 256000;
			अवरोध;
		हाल XD_256M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 16;
			xd_card->capacity = 512000;
			अवरोध;
		हाल XD_512M_X8:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 32;
			xd_card->capacity = 1024000;
			अवरोध;
		हाल XD_1G_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 64;
			xd_card->capacity = 2048000;
			अवरोध;
		हाल XD_2G_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 128;
			xd_card->capacity = 4096000;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		/* Confirm timing setting */
		क्रम (j = 0; j < 10; j++) अणु
			retval = xd_पढ़ो_id(chip, READ_ID, id_buf, 4);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			अगर (id_buf[1] != xd_card->device_code)
				अवरोध;
		पूर्ण

		अगर (j == 10)
			अवरोध;
	पूर्ण

	अगर (i == 4) अणु
		xd_card->block_shअगरt = 0;
		xd_card->page_off = 0;
		xd_card->addr_cycle = 0;
		xd_card->capacity = 0;

		वापस STATUS_FAIL;
	पूर्ण

	retval = xd_पढ़ो_id(chip, READ_XD_ID, id_buf, 4);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;
	dev_dbg(rtsx_dev(chip), "READ_XD_ID: 0x%x 0x%x 0x%x 0x%x\n",
		id_buf[0], id_buf[1], id_buf[2], id_buf[3]);
	अगर (id_buf[2] != XD_ID_CODE)
		वापस STATUS_FAIL;

	/* Search CIS block */
	क्रम (i = 0; i < 24; i++) अणु
		u32 page_addr;

		अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		page_addr = (u32)i << xd_card->block_shअगरt;

		क्रम (j = 0; j < 3; j++) अणु
			retval = xd_पढ़ो_redundant(chip, page_addr, redunt, 11);
			अगर (retval == STATUS_SUCCESS)
				अवरोध;
		पूर्ण
		अगर (j == 3)
			जारी;

		अगर (redunt[BLOCK_STATUS] != XD_GBLK)
			जारी;

		j = 0;
		अगर (redunt[PAGE_STATUS] != XD_GPG) अणु
			क्रम (j = 1; j <= 8; j++) अणु
				retval = xd_पढ़ो_redundant(chip, page_addr + j,
							   redunt, 11);
				अगर (retval == STATUS_SUCCESS) अणु
					अगर (redunt[PAGE_STATUS] == XD_GPG)
						अवरोध;
				पूर्ण
			पूर्ण

			अगर (j == 9)
				अवरोध;
		पूर्ण

		/* Check CIS data */
		अगर ((redunt[BLOCK_STATUS] == XD_GBLK) &&
		    (redunt[PARITY] & XD_BA1_ALL0)) अणु
			u8 buf[10];

			page_addr += j;

			retval = xd_पढ़ो_cis(chip, page_addr, buf, 10);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			अगर ((buf[0] == 0x01) && (buf[1] == 0x03) &&
			    (buf[2] == 0xD9) &&
			    (buf[3] == 0x01) && (buf[4] == 0xFF) &&
			    (buf[5] == 0x18) && (buf[6] == 0x02) &&
			    (buf[7] == 0xDF) && (buf[8] == 0x01) &&
			    (buf[9] == 0x20)) अणु
				xd_card->cis_block = (u16)i;
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "CIS block: 0x%x\n", xd_card->cis_block);
	अगर (xd_card->cis_block == 0xFFFF)
		वापस STATUS_FAIL;

	chip->capacity[chip->card2lun[XD_CARD]] = xd_card->capacity;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_check_data_blank(u8 *redunt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		अगर (redunt[PAGE_STATUS + i] != 0xFF)
			वापस 0;
	पूर्ण

	अगर ((redunt[PARITY] & (XD_ECC1_ALL1 | XD_ECC2_ALL1))
		!= (XD_ECC1_ALL1 | XD_ECC2_ALL1))
		वापस 0;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (redunt[RESERVED0 + i] != 0xFF)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल u16 xd_load_log_block_addr(u8 *redunt)
अणु
	u16 addr = 0xFFFF;

	अगर (redunt[PARITY] & XD_BA1_BA2_EQL)
		addr = ((u16)redunt[BLOCK_ADDR1_H] << 8) |
			redunt[BLOCK_ADDR1_L];
	अन्यथा अगर (redunt[PARITY] & XD_BA1_VALID)
		addr = ((u16)redunt[BLOCK_ADDR1_H] << 8) |
			redunt[BLOCK_ADDR1_L];
	अन्यथा अगर (redunt[PARITY] & XD_BA2_VALID)
		addr = ((u16)redunt[BLOCK_ADDR2_H] << 8) |
			redunt[BLOCK_ADDR2_L];

	वापस addr;
पूर्ण

अटल पूर्णांक xd_init_l2p_tbl(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक size, i;

	dev_dbg(rtsx_dev(chip), "%s: zone_cnt = %d\n", __func__,
		xd_card->zone_cnt);

	अगर (xd_card->zone_cnt < 1)
		वापस STATUS_FAIL;

	size = xd_card->zone_cnt * माप(काष्ठा zone_entry);
	dev_dbg(rtsx_dev(chip), "Buffer size for l2p table is %d\n", size);

	xd_card->zone = vदो_स्मृति(size);
	अगर (!xd_card->zone)
		वापस STATUS_ERROR;

	क्रम (i = 0; i < xd_card->zone_cnt; i++) अणु
		xd_card->zone[i].build_flag = 0;
		xd_card->zone[i].l2p_table = शून्य;
		xd_card->zone[i].मुक्त_table = शून्य;
		xd_card->zone[i].get_index = 0;
		xd_card->zone[i].set_index = 0;
		xd_card->zone[i].unused_blk_cnt = 0;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल अंतरभूत व्योम मुक्त_zone(काष्ठा zone_entry *zone)
अणु
	अगर (!zone)
		वापस;

	zone->build_flag = 0;
	zone->set_index = 0;
	zone->get_index = 0;
	zone->unused_blk_cnt = 0;
	vमुक्त(zone->l2p_table);
	zone->l2p_table = शून्य;
	vमुक्त(zone->मुक्त_table);
	zone->मुक्त_table = शून्य;
पूर्ण

अटल व्योम xd_set_unused_block(काष्ठा rtsx_chip *chip, u32 phy_blk)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा zone_entry *zone;
	पूर्णांक zone_no;

	zone_no = (पूर्णांक)phy_blk >> 10;
	अगर (zone_no >= xd_card->zone_cnt) अणु
		dev_dbg(rtsx_dev(chip), "Set unused block to invalid zone (zone_no = %d, zone_cnt = %d)\n",
			zone_no, xd_card->zone_cnt);
		वापस;
	पूर्ण
	zone = &xd_card->zone[zone_no];

	अगर (!zone->मुक्त_table) अणु
		अगर (xd_build_l2p_tbl(chip, zone_no) != STATUS_SUCCESS)
			वापस;
	पूर्ण

	अगर ((zone->set_index >= XD_FREE_TABLE_CNT) ||
	    (zone->set_index < 0)) अणु
		मुक्त_zone(zone);
		dev_dbg(rtsx_dev(chip), "Set unused block fail, invalid set_index\n");
		वापस;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "Set unused block to index %d\n",
		zone->set_index);

	zone->मुक्त_table[zone->set_index++] = (u16)(phy_blk & 0x3ff);
	अगर (zone->set_index >= XD_FREE_TABLE_CNT)
		zone->set_index = 0;
	zone->unused_blk_cnt++;
पूर्ण

अटल u32 xd_get_unused_block(काष्ठा rtsx_chip *chip, पूर्णांक zone_no)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा zone_entry *zone;
	u32 phy_blk;

	अगर (zone_no >= xd_card->zone_cnt) अणु
		dev_dbg(rtsx_dev(chip), "Get unused block from invalid zone (zone_no = %d, zone_cnt = %d)\n",
			zone_no, xd_card->zone_cnt);
		वापस BLK_NOT_FOUND;
	पूर्ण
	zone = &xd_card->zone[zone_no];

	अगर ((zone->unused_blk_cnt == 0) ||
	    (zone->set_index == zone->get_index)) अणु
		मुक्त_zone(zone);
		dev_dbg(rtsx_dev(chip), "Get unused block fail, no unused block available\n");
		वापस BLK_NOT_FOUND;
	पूर्ण
	अगर ((zone->get_index >= XD_FREE_TABLE_CNT) || (zone->get_index < 0)) अणु
		मुक्त_zone(zone);
		dev_dbg(rtsx_dev(chip), "Get unused block fail, invalid get_index\n");
		वापस BLK_NOT_FOUND;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "Get unused block from index %d\n",
		zone->get_index);

	phy_blk = zone->मुक्त_table[zone->get_index];
	zone->मुक्त_table[zone->get_index++] = 0xFFFF;
	अगर (zone->get_index >= XD_FREE_TABLE_CNT)
		zone->get_index = 0;
	zone->unused_blk_cnt--;

	phy_blk += ((u32)(zone_no) << 10);
	वापस phy_blk;
पूर्ण

अटल व्योम xd_set_l2p_tbl(काष्ठा rtsx_chip *chip,
			   पूर्णांक zone_no, u16 log_off, u16 phy_off)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा zone_entry *zone;

	zone = &xd_card->zone[zone_no];
	zone->l2p_table[log_off] = phy_off;
पूर्ण

अटल u32 xd_get_l2p_tbl(काष्ठा rtsx_chip *chip, पूर्णांक zone_no, u16 log_off)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा zone_entry *zone;
	पूर्णांक retval;

	zone = &xd_card->zone[zone_no];
	अगर (zone->l2p_table[log_off] == 0xFFFF) अणु
		u32 phy_blk = 0;
		पूर्णांक i;

#अगर_घोषित XD_DELAY_WRITE
		retval = xd_delay_ग_लिखो(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			dev_dbg(rtsx_dev(chip), "In %s, delay write fail!\n",
				__func__);
			वापस BLK_NOT_FOUND;
		पूर्ण
#पूर्ण_अगर

		अगर (zone->unused_blk_cnt <= 0) अणु
			dev_dbg(rtsx_dev(chip), "No unused block!\n");
			वापस BLK_NOT_FOUND;
		पूर्ण

		क्रम (i = 0; i < zone->unused_blk_cnt; i++) अणु
			phy_blk = xd_get_unused_block(chip, zone_no);
			अगर (phy_blk == BLK_NOT_FOUND) अणु
				dev_dbg(rtsx_dev(chip), "No unused block available!\n");
				वापस BLK_NOT_FOUND;
			पूर्ण

			retval = xd_init_page(chip, phy_blk, log_off,
					      0, xd_card->page_off + 1);
			अगर (retval == STATUS_SUCCESS)
				अवरोध;
		पूर्ण
		अगर (i >= zone->unused_blk_cnt) अणु
			dev_dbg(rtsx_dev(chip), "No good unused block available!\n");
			वापस BLK_NOT_FOUND;
		पूर्ण

		xd_set_l2p_tbl(chip, zone_no, log_off, (u16)(phy_blk & 0x3FF));
		वापस phy_blk;
	पूर्ण

	वापस (u32)zone->l2p_table[log_off] + ((u32)(zone_no) << 10);
पूर्ण

पूर्णांक reset_xd_card(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval;

	स_रखो(xd_card, 0, माप(काष्ठा xd_info));

	xd_card->block_shअगरt = 0;
	xd_card->page_off = 0;
	xd_card->addr_cycle = 0;
	xd_card->capacity = 0;
	xd_card->zone_cnt = 0;
	xd_card->cis_block = 0xFFFF;
	xd_card->delay_ग_लिखो.delay_ग_लिखो_flag = 0;

	retval = enable_card_घड़ी(chip, XD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = reset_xd(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = xd_init_l2p_tbl(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_mark_bad_block(काष्ठा rtsx_chip *chip, u32 phy_blk)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval;
	u32 page_addr;
	u8 reg = 0;

	dev_dbg(rtsx_dev(chip), "mark block 0x%x as bad block\n", phy_blk);

	अगर (phy_blk == BLK_NOT_FOUND)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_STATUS, 0xFF, XD_GPG);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_STATUS, 0xFF, XD_LATER_BBLK);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_H, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_L, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR2_H, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR2_L, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED0, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED1, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED2, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED3, 0xFF, 0xFF);

	page_addr = phy_blk << xd_card->block_shअगरt;

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF,
		     xd_card->page_off + 1);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_WRITE_REDUNDANT);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, XD_CARD, 500);
	अगर (retval < 0) अणु
		rtsx_clear_xd_error(chip);
		rtsx_पढ़ो_रेजिस्टर(chip, XD_DAT, &reg);
		अगर (reg & PROGRAM_ERROR)
			xd_set_err_code(chip, XD_PRG_ERROR);
		अन्यथा
			xd_set_err_code(chip, XD_TO_ERROR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_init_page(काष्ठा rtsx_chip *chip, u32 phy_blk,
			u16 logoff, u8 start_page, u8 end_page)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval;
	u32 page_addr;
	u8 reg = 0;

	dev_dbg(rtsx_dev(chip), "Init block 0x%x\n", phy_blk);

	अगर (start_page > end_page)
		वापस STATUS_FAIL;
	अगर (phy_blk == BLK_NOT_FOUND)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_STATUS, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_STATUS, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_H,
		     0xFF, (u8)(logoff >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_L, 0xFF, (u8)logoff);

	page_addr = (phy_blk << xd_card->block_shअगरt) + start_page;

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CFG,
		     XD_BA_TRANSFORM, XD_BA_TRANSFORM);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT,
		     0xFF, (end_page - start_page));

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER,
		     0xFF, XD_TRANSFER_START | XD_WRITE_REDUNDANT);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, XD_CARD, 500);
	अगर (retval < 0) अणु
		rtsx_clear_xd_error(chip);
		rtsx_पढ़ो_रेजिस्टर(chip, XD_DAT, &reg);
		अगर (reg & PROGRAM_ERROR) अणु
			xd_mark_bad_block(chip, phy_blk);
			xd_set_err_code(chip, XD_PRG_ERROR);
		पूर्ण अन्यथा अणु
			xd_set_err_code(chip, XD_TO_ERROR);
		पूर्ण
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_copy_page(काष्ठा rtsx_chip *chip, u32 old_blk, u32 new_blk,
			u8 start_page, u8 end_page)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	u32 old_page, new_page;
	u8 i, reg = 0;
	पूर्णांक retval;

	dev_dbg(rtsx_dev(chip), "Copy page from block 0x%x to block 0x%x\n",
		old_blk, new_blk);

	अगर (start_page > end_page)
		वापस STATUS_FAIL;

	अगर ((old_blk == BLK_NOT_FOUND) || (new_blk == BLK_NOT_FOUND))
		वापस STATUS_FAIL;

	old_page = (old_blk << xd_card->block_shअगरt) + start_page;
	new_page = (new_blk << xd_card->block_shअगरt) + start_page;

	XD_CLR_BAD_NEWBLK(xd_card);

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_DATA_SOURCE, 0x01,
				     PINGPONG_BUFFER);
	अगर (retval)
		वापस retval;

	क्रम (i = start_page; i < end_page; i++) अणु
		अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
			rtsx_clear_xd_error(chip);
			xd_set_err_code(chip, XD_NO_CARD);
			वापस STATUS_FAIL;
		पूर्ण

		rtsx_init_cmd(chip);

		xd_assign_phy_addr(chip, old_page, XD_RW_ADDR);

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF, 1);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CHK_DATA_STATUS,
			     XD_AUTO_CHK_DATA_STATUS, 0);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
			     XD_TRANSFER_START | XD_READ_PAGES);
		rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
			     XD_TRANSFER_END, XD_TRANSFER_END);

		retval = rtsx_send_cmd(chip, XD_CARD, 500);
		अगर (retval < 0) अणु
			rtsx_clear_xd_error(chip);
			reg = 0;
			rtsx_पढ़ो_रेजिस्टर(chip, XD_CTL, &reg);
			अगर (reg & (XD_ECC1_ERROR | XD_ECC2_ERROR)) अणु
				mdelay(100);

				अगर (detect_card_cd(chip,
						   XD_CARD) != STATUS_SUCCESS) अणु
					xd_set_err_code(chip, XD_NO_CARD);
					वापस STATUS_FAIL;
				पूर्ण

				अगर (((reg & XD_ECC1_ERROR) &&
				     (reg & XD_ECC1_UNCORRECTABLE)) ||
				    ((reg & XD_ECC2_ERROR) &&
				     (reg & XD_ECC2_UNCORRECTABLE))) अणु
					rtsx_ग_लिखो_रेजिस्टर(chip,
							    XD_PAGE_STATUS,
							    0xFF,
							    XD_BPG);
					rtsx_ग_लिखो_रेजिस्टर(chip,
							    XD_BLOCK_STATUS,
							    0xFF,
							    XD_GBLK);
					XD_SET_BAD_OLDBLK(xd_card);
					dev_dbg(rtsx_dev(chip), "old block 0x%x ecc error\n",
						old_blk);
				पूर्ण
			पूर्ण अन्यथा अणु
				xd_set_err_code(chip, XD_TO_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		अगर (XD_CHK_BAD_OLDBLK(xd_card))
			rtsx_clear_xd_error(chip);

		rtsx_init_cmd(chip);

		xd_assign_phy_addr(chip, new_page, XD_RW_ADDR);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF, 1);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
			     XD_TRANSFER_START | XD_WRITE_PAGES);
		rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
			     XD_TRANSFER_END, XD_TRANSFER_END);

		retval = rtsx_send_cmd(chip, XD_CARD, 300);
		अगर (retval < 0) अणु
			rtsx_clear_xd_error(chip);
			reg = 0;
			rtsx_पढ़ो_रेजिस्टर(chip, XD_DAT, &reg);
			अगर (reg & PROGRAM_ERROR) अणु
				xd_mark_bad_block(chip, new_blk);
				xd_set_err_code(chip, XD_PRG_ERROR);
				XD_SET_BAD_NEWBLK(xd_card);
			पूर्ण अन्यथा अणु
				xd_set_err_code(chip, XD_TO_ERROR);
			पूर्ण
			वापस STATUS_FAIL;
		पूर्ण

		old_page++;
		new_page++;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_reset_cmd(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 *ptr;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER,
		     0xFF, XD_TRANSFER_START | XD_RESET);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);
	rtsx_add_cmd(chip, READ_REG_CMD, XD_DAT, 0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, XD_CTL, 0, 0);

	retval = rtsx_send_cmd(chip, XD_CARD, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	ptr = rtsx_get_cmd_data(chip) + 1;
	अगर (((ptr[0] & READY_FLAG) == READY_STATE) && (ptr[1] & XD_RDY))
		वापस STATUS_SUCCESS;

	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक xd_erase_block(काष्ठा rtsx_chip *chip, u32 phy_blk)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	u32 page_addr;
	u8 reg = 0, *ptr;
	पूर्णांक i, retval;

	अगर (phy_blk == BLK_NOT_FOUND)
		वापस STATUS_FAIL;

	page_addr = phy_blk << xd_card->block_shअगरt;

	क्रम (i = 0; i < 3; i++) अणु
		rtsx_init_cmd(chip);

		xd_assign_phy_addr(chip, page_addr, XD_ERASE_ADDR);

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
			     XD_TRANSFER_START | XD_ERASE);
		rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
			     XD_TRANSFER_END, XD_TRANSFER_END);
		rtsx_add_cmd(chip, READ_REG_CMD, XD_DAT, 0, 0);

		retval = rtsx_send_cmd(chip, XD_CARD, 250);
		अगर (retval < 0) अणु
			rtsx_clear_xd_error(chip);
			rtsx_पढ़ो_रेजिस्टर(chip, XD_DAT, &reg);
			अगर (reg & PROGRAM_ERROR) अणु
				xd_mark_bad_block(chip, phy_blk);
				xd_set_err_code(chip, XD_PRG_ERROR);
				वापस STATUS_FAIL;
			पूर्ण
			xd_set_err_code(chip, XD_ERASE_FAIL);
			retval = xd_reset_cmd(chip);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
			जारी;
		पूर्ण

		ptr = rtsx_get_cmd_data(chip) + 1;
		अगर (*ptr & PROGRAM_ERROR) अणु
			xd_mark_bad_block(chip, phy_blk);
			xd_set_err_code(chip, XD_PRG_ERROR);
			वापस STATUS_FAIL;
		पूर्ण

		वापस STATUS_SUCCESS;
	पूर्ण

	xd_mark_bad_block(chip, phy_blk);
	xd_set_err_code(chip, XD_ERASE_FAIL);
	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक xd_build_l2p_tbl(काष्ठा rtsx_chip *chip, पूर्णांक zone_no)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा zone_entry *zone;
	पूर्णांक retval;
	u32 start, end, i;
	u16 max_logoff, cur_fst_page_logoff;
	u16 cur_lst_page_logoff, ent_lst_page_logoff;
	u8 redunt[11];

	dev_dbg(rtsx_dev(chip), "%s: %d\n", __func__, zone_no);

	अगर (!xd_card->zone) अणु
		retval = xd_init_l2p_tbl(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस retval;
	पूर्ण

	अगर (xd_card->zone[zone_no].build_flag) अणु
		dev_dbg(rtsx_dev(chip), "l2p table of zone %d has been built\n",
			zone_no);
		वापस STATUS_SUCCESS;
	पूर्ण

	zone = &xd_card->zone[zone_no];

	अगर (!zone->l2p_table) अणु
		zone->l2p_table = vदो_स्मृति(2000);
		अगर (!zone->l2p_table)
			जाओ build_fail;
	पूर्ण
	स_रखो((u8 *)(zone->l2p_table), 0xff, 2000);

	अगर (!zone->मुक्त_table) अणु
		zone->मुक्त_table = vदो_स्मृति(XD_FREE_TABLE_CNT * 2);
		अगर (!zone->मुक्त_table)
			जाओ build_fail;
	पूर्ण
	स_रखो((u8 *)(zone->मुक्त_table), 0xff, XD_FREE_TABLE_CNT * 2);

	अगर (zone_no == 0) अणु
		अगर (xd_card->cis_block == 0xFFFF)
			start = 0;
		अन्यथा
			start = xd_card->cis_block + 1;
		अगर (XD_CHK_4MB(xd_card)) अणु
			end = 0x200;
			max_logoff = 499;
		पूर्ण अन्यथा अणु
			end = 0x400;
			max_logoff = 999;
		पूर्ण
	पूर्ण अन्यथा अणु
		start = (u32)(zone_no) << 10;
		end = (u32)(zone_no + 1) << 10;
		max_logoff = 999;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "start block 0x%x, end block 0x%x\n",
		start, end);

	zone->set_index = 0;
	zone->get_index = 0;
	zone->unused_blk_cnt = 0;

	क्रम (i = start; i < end; i++) अणु
		u32 page_addr = i << xd_card->block_shअगरt;
		u32 phy_block;

		retval = xd_पढ़ो_redundant(chip, page_addr, redunt, 11);
		अगर (retval != STATUS_SUCCESS)
			जारी;

		अगर (redunt[BLOCK_STATUS] != 0xFF) अणु
			dev_dbg(rtsx_dev(chip), "bad block\n");
			जारी;
		पूर्ण

		अगर (xd_check_data_blank(redunt)) अणु
			dev_dbg(rtsx_dev(chip), "blank block\n");
			xd_set_unused_block(chip, i);
			जारी;
		पूर्ण

		cur_fst_page_logoff = xd_load_log_block_addr(redunt);
		अगर ((cur_fst_page_logoff == 0xFFFF) ||
		    (cur_fst_page_logoff > max_logoff)) अणु
			retval = xd_erase_block(chip, i);
			अगर (retval == STATUS_SUCCESS)
				xd_set_unused_block(chip, i);
			जारी;
		पूर्ण

		अगर ((zone_no == 0) && (cur_fst_page_logoff == 0) &&
		    (redunt[PAGE_STATUS] != XD_GPG))
			XD_SET_MBR_FAIL(xd_card);

		अगर (zone->l2p_table[cur_fst_page_logoff] == 0xFFFF) अणु
			zone->l2p_table[cur_fst_page_logoff] = (u16)(i & 0x3FF);
			जारी;
		पूर्ण

		phy_block = zone->l2p_table[cur_fst_page_logoff] +
			((u32)((zone_no) << 10));

		page_addr = ((i + 1) << xd_card->block_shअगरt) - 1;

		retval = xd_पढ़ो_redundant(chip, page_addr, redunt, 11);
		अगर (retval != STATUS_SUCCESS)
			जारी;

		cur_lst_page_logoff = xd_load_log_block_addr(redunt);
		अगर (cur_lst_page_logoff == cur_fst_page_logoff) अणु
			पूर्णांक m;

			page_addr = ((phy_block + 1) <<
				xd_card->block_shअगरt) - 1;

			क्रम (m = 0; m < 3; m++) अणु
				retval = xd_पढ़ो_redundant(chip, page_addr,
							   redunt, 11);
				अगर (retval == STATUS_SUCCESS)
					अवरोध;
			पूर्ण

			अगर (m == 3) अणु
				zone->l2p_table[cur_fst_page_logoff] =
					(u16)(i & 0x3FF);
				retval = xd_erase_block(chip, phy_block);
				अगर (retval == STATUS_SUCCESS)
					xd_set_unused_block(chip, phy_block);
				जारी;
			पूर्ण

			ent_lst_page_logoff = xd_load_log_block_addr(redunt);
			अगर (ent_lst_page_logoff != cur_fst_page_logoff) अणु
				zone->l2p_table[cur_fst_page_logoff] =
					(u16)(i & 0x3FF);
				retval = xd_erase_block(chip, phy_block);
				अगर (retval == STATUS_SUCCESS)
					xd_set_unused_block(chip, phy_block);
				जारी;
			पूर्ण अन्यथा अणु
				retval = xd_erase_block(chip, i);
				अगर (retval == STATUS_SUCCESS)
					xd_set_unused_block(chip, i);
			पूर्ण
		पूर्ण अन्यथा अणु
			retval = xd_erase_block(chip, i);
			अगर (retval == STATUS_SUCCESS)
				xd_set_unused_block(chip, i);
		पूर्ण
	पूर्ण

	अगर (XD_CHK_4MB(xd_card))
		end = 500;
	अन्यथा
		end = 1000;

	i = 0;
	क्रम (start = 0; start < end; start++) अणु
		अगर (zone->l2p_table[start] == 0xFFFF)
			i++;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "Block count %d, invalid L2P entry %d\n",
		end, i);
	dev_dbg(rtsx_dev(chip), "Total unused block: %d\n",
		zone->unused_blk_cnt);

	अगर ((zone->unused_blk_cnt - i) < 1)
		chip->card_wp |= XD_CARD;

	zone->build_flag = 1;

	वापस STATUS_SUCCESS;

build_fail:
	vमुक्त(zone->l2p_table);
	zone->l2p_table = शून्य;
	vमुक्त(zone->मुक्त_table);
	zone->मुक्त_table = शून्य;

	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक xd_send_cmd(काष्ठा rtsx_chip *chip, u8 cmd)
अणु
	पूर्णांक retval;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_DAT, 0xFF, cmd);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_SET_CMD);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, XD_CARD, 200);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_पढ़ो_multiple_pages(काष्ठा rtsx_chip *chip, u32 phy_blk,
				  u32 log_blk, u8 start_page, u8 end_page,
				  u8 *buf, अचिन्हित पूर्णांक *index,
				  अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	u32 page_addr, new_blk;
	u16 log_off;
	u8 reg_val, page_cnt;
	पूर्णांक zone_no, retval, i;

	अगर (start_page > end_page)
		जाओ status_fail;

	page_cnt = end_page - start_page;
	zone_no = (पूर्णांक)(log_blk / 1000);
	log_off = (u16)(log_blk % 1000);

	अगर ((phy_blk & 0x3FF) == 0x3FF) अणु
		क्रम (i = 0; i < 256; i++) अणु
			page_addr = ((u32)i) << xd_card->block_shअगरt;

			retval = xd_पढ़ो_redundant(chip, page_addr, शून्य, 0);
			अगर (retval == STATUS_SUCCESS)
				अवरोध;

			अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
				xd_set_err_code(chip, XD_NO_CARD);
				जाओ status_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	page_addr = (phy_blk << xd_card->block_shअगरt) + start_page;

	rtsx_init_cmd(chip);

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CFG, XD_PPB_TO_SIE, XD_PPB_TO_SIE);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF, page_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CHK_DATA_STATUS,
		     XD_AUTO_CHK_DATA_STATUS, XD_AUTO_CHK_DATA_STATUS);

	trans_dma_enable(chip->srb->sc_data_direction, chip,
			 page_cnt * 512, DMA_512);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_READ_PAGES);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END | XD_PPB_EMPTY,
		     XD_TRANSFER_END | XD_PPB_EMPTY);

	rtsx_send_cmd_no_रुको(chip);

	retval = rtsx_transfer_data_partial(chip, XD_CARD, buf, page_cnt * 512,
					    scsi_sg_count(chip->srb),
					    index, offset, DMA_FROM_DEVICE,
					    chip->xd_समयout);
	अगर (retval < 0) अणु
		rtsx_clear_xd_error(chip);

		अगर (retval == -ETIMEDOUT) अणु
			xd_set_err_code(chip, XD_TO_ERROR);
			जाओ status_fail;
		पूर्ण अन्यथा अणु
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;

fail:
	retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_PAGE_STATUS, &reg_val);
	अगर (retval)
		वापस retval;

	अगर (reg_val !=  XD_GPG)
		xd_set_err_code(chip, XD_PRG_ERROR);

	retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_CTL, &reg_val);
	अगर (retval)
		वापस retval;

	अगर (((reg_val & (XD_ECC1_ERROR | XD_ECC1_UNCORRECTABLE)) ==
				(XD_ECC1_ERROR | XD_ECC1_UNCORRECTABLE)) ||
		((reg_val & (XD_ECC2_ERROR | XD_ECC2_UNCORRECTABLE)) ==
			(XD_ECC2_ERROR | XD_ECC2_UNCORRECTABLE))) अणु
		रुको_समयout(100);

		अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
			xd_set_err_code(chip, XD_NO_CARD);
			जाओ status_fail;
		पूर्ण

		xd_set_err_code(chip, XD_ECC_ERROR);

		new_blk = xd_get_unused_block(chip, zone_no);
		अगर (new_blk == NO_NEW_BLK) अणु
			XD_CLR_BAD_OLDBLK(xd_card);
			जाओ status_fail;
		पूर्ण

		retval = xd_copy_page(chip, phy_blk, new_blk, 0,
				      xd_card->page_off + 1);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (!XD_CHK_BAD_NEWBLK(xd_card)) अणु
				retval = xd_erase_block(chip, new_blk);
				अगर (retval == STATUS_SUCCESS)
					xd_set_unused_block(chip, new_blk);
			पूर्ण अन्यथा अणु
				XD_CLR_BAD_NEWBLK(xd_card);
			पूर्ण
			XD_CLR_BAD_OLDBLK(xd_card);
			जाओ status_fail;
		पूर्ण
		xd_set_l2p_tbl(chip, zone_no, log_off, (u16)(new_blk & 0x3FF));
		xd_erase_block(chip, phy_blk);
		xd_mark_bad_block(chip, phy_blk);
		XD_CLR_BAD_OLDBLK(xd_card);
	पूर्ण

status_fail:
	वापस STATUS_FAIL;
पूर्ण

अटल पूर्णांक xd_finish_ग_लिखो(काष्ठा rtsx_chip *chip,
			   u32 old_blk, u32 new_blk, u32 log_blk, u8 page_off)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval, zone_no;
	u16 log_off;

	dev_dbg(rtsx_dev(chip), "old_blk = 0x%x, ", old_blk);
	dev_dbg(rtsx_dev(chip),	"new_blk = 0x%x, ", new_blk);
	dev_dbg(rtsx_dev(chip), "log_blk = 0x%x\n", log_blk);

	अगर (page_off > xd_card->page_off)
		वापस STATUS_FAIL;

	zone_no = (पूर्णांक)(log_blk / 1000);
	log_off = (u16)(log_blk % 1000);

	अगर (old_blk == BLK_NOT_FOUND) अणु
		retval = xd_init_page(chip, new_blk, log_off,
				      page_off, xd_card->page_off + 1);
		अगर (retval != STATUS_SUCCESS) अणु
			retval = xd_erase_block(chip, new_blk);
			अगर (retval == STATUS_SUCCESS)
				xd_set_unused_block(chip, new_blk);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = xd_copy_page(chip, old_blk, new_blk,
				      page_off, xd_card->page_off + 1);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (!XD_CHK_BAD_NEWBLK(xd_card)) अणु
				retval = xd_erase_block(chip, new_blk);
				अगर (retval == STATUS_SUCCESS)
					xd_set_unused_block(chip, new_blk);
			पूर्ण
			XD_CLR_BAD_NEWBLK(xd_card);
			वापस STATUS_FAIL;
		पूर्ण

		retval = xd_erase_block(chip, old_blk);
		अगर (retval == STATUS_SUCCESS) अणु
			अगर (XD_CHK_BAD_OLDBLK(xd_card)) अणु
				xd_mark_bad_block(chip, old_blk);
				XD_CLR_BAD_OLDBLK(xd_card);
			पूर्ण अन्यथा अणु
				xd_set_unused_block(chip, old_blk);
			पूर्ण
		पूर्ण अन्यथा अणु
			xd_set_err_code(chip, XD_NO_ERROR);
			XD_CLR_BAD_OLDBLK(xd_card);
		पूर्ण
	पूर्ण

	xd_set_l2p_tbl(chip, zone_no, log_off, (u16)(new_blk & 0x3FF));

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_prepare_ग_लिखो(काष्ठा rtsx_chip *chip,
			    u32 old_blk, u32 new_blk, u32 log_blk, u8 page_off)
अणु
	पूर्णांक retval;

	dev_dbg(rtsx_dev(chip), "%s, old_blk = 0x%x, new_blk = 0x%x, log_blk = 0x%x, page_off = %d\n",
		__func__, old_blk, new_blk, log_blk, (पूर्णांक)page_off);

	अगर (page_off) अणु
		retval = xd_copy_page(chip, old_blk, new_blk, 0, page_off);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक xd_ग_लिखो_multiple_pages(काष्ठा rtsx_chip *chip, u32 old_blk,
				   u32 new_blk, u32 log_blk, u8 start_page,
				   u8 end_page, u8 *buf, अचिन्हित पूर्णांक *index,
				   अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	u32 page_addr;
	पूर्णांक zone_no, retval;
	u16 log_off;
	u8 page_cnt, reg_val;

	dev_dbg(rtsx_dev(chip), "%s, old_blk = 0x%x, new_blk = 0x%x, log_blk = 0x%x\n",
		__func__, old_blk, new_blk, log_blk);

	अगर (start_page > end_page)
		जाओ status_fail;

	page_cnt = end_page - start_page;
	zone_no = (पूर्णांक)(log_blk / 1000);
	log_off = (u16)(log_blk % 1000);

	page_addr = (new_blk << xd_card->block_shअगरt) + start_page;

	retval = xd_send_cmd(chip, READ1_1);
	अगर (retval != STATUS_SUCCESS)
		जाओ status_fail;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_H,
		     0xFF, (u8)(log_off >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_L, 0xFF, (u8)log_off);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_STATUS, 0xFF, XD_GBLK);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_STATUS, 0xFF, XD_GPG);

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CFG, XD_BA_TRANSFORM,
		     XD_BA_TRANSFORM);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF, page_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);

	trans_dma_enable(chip->srb->sc_data_direction, chip,
			 page_cnt * 512, DMA_512);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER,
		     0xFF, XD_TRANSFER_START | XD_WRITE_PAGES);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	rtsx_send_cmd_no_रुको(chip);

	retval = rtsx_transfer_data_partial(chip, XD_CARD, buf, page_cnt * 512,
					    scsi_sg_count(chip->srb),
					    index, offset, DMA_TO_DEVICE, chip->xd_समयout);
	अगर (retval < 0) अणु
		rtsx_clear_xd_error(chip);

		अगर (retval == -ETIMEDOUT) अणु
			xd_set_err_code(chip, XD_TO_ERROR);
			जाओ status_fail;
		पूर्ण अन्यथा अणु
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (end_page == (xd_card->page_off + 1)) अणु
		xd_card->delay_ग_लिखो.delay_ग_लिखो_flag = 0;

		अगर (old_blk != BLK_NOT_FOUND) अणु
			retval = xd_erase_block(chip, old_blk);
			अगर (retval == STATUS_SUCCESS) अणु
				अगर (XD_CHK_BAD_OLDBLK(xd_card)) अणु
					xd_mark_bad_block(chip, old_blk);
					XD_CLR_BAD_OLDBLK(xd_card);
				पूर्ण अन्यथा अणु
					xd_set_unused_block(chip, old_blk);
				पूर्ण
			पूर्ण अन्यथा अणु
				xd_set_err_code(chip, XD_NO_ERROR);
				XD_CLR_BAD_OLDBLK(xd_card);
			पूर्ण
		पूर्ण
		xd_set_l2p_tbl(chip, zone_no, log_off, (u16)(new_blk & 0x3FF));
	पूर्ण

	वापस STATUS_SUCCESS;

fail:
	retval = rtsx_पढ़ो_रेजिस्टर(chip, XD_DAT, &reg_val);
	अगर (retval)
		वापस retval;
	अगर (reg_val & PROGRAM_ERROR) अणु
		xd_set_err_code(chip, XD_PRG_ERROR);
		xd_mark_bad_block(chip, new_blk);
	पूर्ण

status_fail:
	वापस STATUS_FAIL;
पूर्ण

#अगर_घोषित XD_DELAY_WRITE
पूर्णांक xd_delay_ग_लिखो(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा xd_delay_ग_लिखो_tag *delay_ग_लिखो = &xd_card->delay_ग_लिखो;
	पूर्णांक retval;

	अगर (delay_ग_लिखो->delay_ग_लिखो_flag) अणु
		retval = xd_चयन_घड़ी(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		delay_ग_लिखो->delay_ग_लिखो_flag = 0;
		retval = xd_finish_ग_लिखो(chip,
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

पूर्णांक xd_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	  u32 start_sector, u16 sector_cnt)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
#अगर_घोषित XD_DELAY_WRITE
	काष्ठा xd_delay_ग_लिखो_tag *delay_ग_लिखो = &xd_card->delay_ग_लिखो;
#पूर्ण_अगर
	पूर्णांक retval, zone_no;
	अचिन्हित पूर्णांक index = 0, offset = 0;
	u32 log_blk, old_blk = 0, new_blk = 0;
	u16 log_off, total_sec_cnt = sector_cnt;
	u8 start_page, end_page = 0, page_cnt;
	u8 *ptr;

	xd_set_err_code(chip, XD_NO_ERROR);

	xd_card->cleanup_counter = 0;

	dev_dbg(rtsx_dev(chip), "%s: scsi_sg_count = %d\n", __func__,
		scsi_sg_count(srb));

	ptr = (u8 *)scsi_sglist(srb);

	retval = xd_चयन_घड़ी(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
		chip->card_fail |= XD_CARD;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस STATUS_FAIL;
	पूर्ण

	log_blk = start_sector >> xd_card->block_shअगरt;
	start_page = (u8)start_sector & xd_card->page_off;
	zone_no = (पूर्णांक)(log_blk / 1000);
	log_off = (u16)(log_blk % 1000);

	अगर (xd_card->zone[zone_no].build_flag == 0) अणु
		retval = xd_build_l2p_tbl(chip, zone_no);
		अगर (retval != STATUS_SUCCESS) अणु
			chip->card_fail |= XD_CARD;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
#अगर_घोषित XD_DELAY_WRITE
		अगर (delay_ग_लिखो->delay_ग_लिखो_flag &&
		    (delay_ग_लिखो->logblock == log_blk) &&
		    (start_page > delay_ग_लिखो->pageoff)) अणु
			delay_ग_लिखो->delay_ग_लिखो_flag = 0;
			अगर (delay_ग_लिखो->old_phyblock != BLK_NOT_FOUND) अणु
				retval = xd_copy_page(chip,
						      delay_ग_लिखो->old_phyblock,
						      delay_ग_लिखो->new_phyblock,
						      delay_ग_लिखो->pageoff,
						      start_page);
				अगर (retval != STATUS_SUCCESS) अणु
					set_sense_type(chip, lun,
						       SENSE_TYPE_MEDIA_WRITE_ERR);
					वापस STATUS_FAIL;
				पूर्ण
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
			retval = xd_delay_ग_लिखो(chip);
			अगर (retval != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
#पूर्ण_अगर
			old_blk = xd_get_l2p_tbl(chip, zone_no, log_off);
			new_blk  = xd_get_unused_block(chip, zone_no);
			अगर ((old_blk == BLK_NOT_FOUND) ||
			    (new_blk == BLK_NOT_FOUND)) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण

			retval = xd_prepare_ग_लिखो(chip, old_blk, new_blk,
						  log_blk, start_page);
			अगर (retval != STATUS_SUCCESS) अणु
				अगर (detect_card_cd(chip, XD_CARD) !=
					STATUS_SUCCESS) अणु
					set_sense_type(chip, lun,
						       SENSE_TYPE_MEDIA_NOT_PRESENT);
					वापस STATUS_FAIL;
				पूर्ण
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
#अगर_घोषित XD_DELAY_WRITE
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित XD_DELAY_WRITE
		retval = xd_delay_ग_लिखो(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				वापस STATUS_FAIL;
			पूर्ण
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस STATUS_FAIL;
		पूर्ण
#पूर्ण_अगर

		old_blk = xd_get_l2p_tbl(chip, zone_no, log_off);
		अगर (old_blk == BLK_NOT_FOUND) अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	dev_dbg(rtsx_dev(chip), "old_blk = 0x%x\n", old_blk);

	जबतक (total_sec_cnt) अणु
		अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
			chip->card_fail |= XD_CARD;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			वापस STATUS_FAIL;
		पूर्ण

		अगर ((start_page + total_sec_cnt) > (xd_card->page_off + 1))
			end_page = xd_card->page_off + 1;
		अन्यथा
			end_page = start_page + (u8)total_sec_cnt;

		page_cnt = end_page - start_page;
		अगर (srb->sc_data_direction == DMA_FROM_DEVICE) अणु
			retval = xd_पढ़ो_multiple_pages(chip, old_blk, log_blk,
							start_page, end_page,
							ptr, &index, &offset);
			अगर (retval != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			retval = xd_ग_लिखो_multiple_pages(chip, old_blk,
							 new_blk, log_blk,
							 start_page, end_page,
							 ptr, &index, &offset);
			अगर (retval != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		total_sec_cnt -= page_cnt;
		अगर (scsi_sg_count(srb) == 0)
			ptr += page_cnt * 512;

		अगर (total_sec_cnt == 0)
			अवरोध;

		log_blk++;
		zone_no = (पूर्णांक)(log_blk / 1000);
		log_off = (u16)(log_blk % 1000);

		अगर (xd_card->zone[zone_no].build_flag == 0) अणु
			retval = xd_build_l2p_tbl(chip, zone_no);
			अगर (retval != STATUS_SUCCESS) अणु
				chip->card_fail |= XD_CARD;
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		old_blk = xd_get_l2p_tbl(chip, zone_no, log_off);
		अगर (old_blk == BLK_NOT_FOUND) अणु
			अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			अन्यथा
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);

			वापस STATUS_FAIL;
		पूर्ण

		अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
			new_blk = xd_get_unused_block(chip, zone_no);
			अगर (new_blk == BLK_NOT_FOUND) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस STATUS_FAIL;
			पूर्ण
		पूर्ण

		start_page = 0;
	पूर्ण

	अगर ((srb->sc_data_direction == DMA_TO_DEVICE) &&
	    (end_page != (xd_card->page_off + 1))) अणु
#अगर_घोषित XD_DELAY_WRITE
		delay_ग_लिखो->delay_ग_लिखो_flag = 1;
		delay_ग_लिखो->old_phyblock = old_blk;
		delay_ग_लिखो->new_phyblock = new_blk;
		delay_ग_लिखो->logblock = log_blk;
		delay_ग_लिखो->pageoff = end_page;
#अन्यथा
		अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
			chip->card_fail |= XD_CARD;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			वापस STATUS_FAIL;
		पूर्ण

		retval = xd_finish_ग_लिखो(chip, old_blk, new_blk,
					 log_blk, end_page);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) अणु
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				वापस STATUS_FAIL;
			पूर्ण
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस STATUS_FAIL;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	scsi_set_resid(srb, 0);

	वापस STATUS_SUCCESS;
पूर्ण

व्योम xd_मुक्त_l2p_tbl(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक i = 0;

	अगर (xd_card->zone) अणु
		क्रम (i = 0; i < xd_card->zone_cnt; i++) अणु
			vमुक्त(xd_card->zone[i].l2p_table);
			xd_card->zone[i].l2p_table = शून्य;
			vमुक्त(xd_card->zone[i].मुक्त_table);
			xd_card->zone[i].मुक्त_table = शून्य;
		पूर्ण
		vमुक्त(xd_card->zone);
		xd_card->zone = शून्य;
	पूर्ण
पूर्ण

व्योम xd_cleanup_work(काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित XD_DELAY_WRITE
	काष्ठा xd_info *xd_card = &chip->xd_card;

	अगर (xd_card->delay_ग_लिखो.delay_ग_लिखो_flag) अणु
		dev_dbg(rtsx_dev(chip), "xD: delay write\n");
		xd_delay_ग_लिखो(chip);
		xd_card->cleanup_counter = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक xd_घातer_off_card3v3(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = disable_card_घड़ी(chip, XD_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, XD_OUTPUT_EN, 0);
	अगर (retval)
		वापस retval;

	अगर (!chip->ft2_fast_mode) अणु
		retval = card_घातer_off(chip, XD_CARD);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		रुको_समयout(50);
	पूर्ण

	अगर (chip->asic_code) अणु
		retval = xd_pull_ctl_disable(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL, 0xFF, 0xDF);
		अगर (retval)
			वापस retval;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक release_xd_card(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा xd_info *xd_card = &chip->xd_card;
	पूर्णांक retval;

	chip->card_पढ़ोy &= ~XD_CARD;
	chip->card_fail &= ~XD_CARD;
	chip->card_wp &= ~XD_CARD;

	xd_card->delay_ग_लिखो.delay_ग_लिखो_flag = 0;

	xd_मुक्त_l2p_tbl(chip);

	retval = xd_घातer_off_card3v3(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण
