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
#समावेश <linux/workqueue.h>
#समावेश <linux/kernel.h>

#समावेश "rtsx.h"
#समावेश "sd.h"
#समावेश "xd.h"
#समावेश "ms.h"

व्योम करो_reमुख्यing_work(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
#अगर_घोषित XD_DELAY_WRITE
	काष्ठा xd_info *xd_card = &chip->xd_card;
#पूर्ण_अगर
	काष्ठा ms_info *ms_card = &chip->ms_card;

	अगर (chip->card_पढ़ोy & SD_CARD) अणु
		अगर (sd_card->seq_mode) अणु
			rtsx_set_stat(chip, RTSX_STAT_RUN);
			sd_card->cleanup_counter++;
		पूर्ण अन्यथा अणु
			sd_card->cleanup_counter = 0;
		पूर्ण
	पूर्ण

#अगर_घोषित XD_DELAY_WRITE
	अगर (chip->card_पढ़ोy & XD_CARD) अणु
		अगर (xd_card->delay_ग_लिखो.delay_ग_लिखो_flag) अणु
			rtsx_set_stat(chip, RTSX_STAT_RUN);
			xd_card->cleanup_counter++;
		पूर्ण अन्यथा अणु
			xd_card->cleanup_counter = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (chip->card_पढ़ोy & MS_CARD) अणु
		अगर (CHK_MSPRO(ms_card)) अणु
			अगर (ms_card->seq_mode) अणु
				rtsx_set_stat(chip, RTSX_STAT_RUN);
				ms_card->cleanup_counter++;
			पूर्ण अन्यथा अणु
				ms_card->cleanup_counter = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
#अगर_घोषित MS_DELAY_WRITE
			अगर (ms_card->delay_ग_लिखो.delay_ग_लिखो_flag) अणु
				rtsx_set_stat(chip, RTSX_STAT_RUN);
				ms_card->cleanup_counter++;
			पूर्ण अन्यथा अणु
				ms_card->cleanup_counter = 0;
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (sd_card->cleanup_counter > POLLING_WAIT_CNT)
		sd_cleanup_work(chip);

	अगर (xd_card->cleanup_counter > POLLING_WAIT_CNT)
		xd_cleanup_work(chip);

	अगर (ms_card->cleanup_counter > POLLING_WAIT_CNT)
		ms_cleanup_work(chip);
पूर्ण

व्योम try_to_चयन_sdio_ctrl(काष्ठा rtsx_chip *chip)
अणु
	u8 reg1 = 0, reg2 = 0;

	rtsx_पढ़ो_रेजिस्टर(chip, 0xFF34, &reg1);
	rtsx_पढ़ो_रेजिस्टर(chip, 0xFF38, &reg2);
	dev_dbg(rtsx_dev(chip), "reg 0xFF34: 0x%x, reg 0xFF38: 0x%x\n",
		reg1, reg2);
	अगर ((reg1 & 0xC0) && (reg2 & 0xC0)) अणु
		chip->sd_पूर्णांक = 1;
		rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL, 0xFF,
				    SDIO_BUS_CTRL | SDIO_CD_CTRL);
		rtsx_ग_लिखो_रेजिस्टर(chip, PWR_GATE_CTRL,
				    LDO3318_PWR_MASK, LDO_ON);
	पूर्ण
पूर्ण

#अगर_घोषित SUPPORT_SDIO_ASPM
व्योम dynamic_configure_sdio_aspm(काष्ठा rtsx_chip *chip)
अणु
	u8 buf[12], reg;
	पूर्णांक i;

	क्रम (i = 0; i < 12; i++)
		rtsx_पढ़ो_रेजिस्टर(chip, 0xFF08 + i, &buf[i]);
	rtsx_पढ़ो_रेजिस्टर(chip, 0xFF25, &reg);
	अगर ((स_भेद(buf, chip->sdio_raw_data, 12) != 0) || (reg & 0x03)) अणु
		chip->sdio_counter = 0;
		chip->sdio_idle = 0;
	पूर्ण अन्यथा अणु
		अगर (!chip->sdio_idle) अणु
			chip->sdio_counter++;
			अगर (chip->sdio_counter >= SDIO_IDLE_COUNT) अणु
				chip->sdio_counter = 0;
				chip->sdio_idle = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	स_नकल(chip->sdio_raw_data, buf, 12);

	अगर (chip->sdio_idle) अणु
		अगर (!chip->sdio_aspm) अणु
			dev_dbg(rtsx_dev(chip), "SDIO enter ASPM!\n");
			rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL, 0xFC,
					    0x30 | (chip->aspm_level[1] << 2));
			chip->sdio_aspm = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->sdio_aspm) अणु
			dev_dbg(rtsx_dev(chip), "SDIO exit ASPM!\n");
			rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL, 0xFC, 0x30);
			chip->sdio_aspm = 0;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम करो_reset_sd_card(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	dev_dbg(rtsx_dev(chip), "%s: %d, card2lun = 0x%x\n", __func__,
		chip->sd_reset_counter, chip->card2lun[SD_CARD]);

	अगर (chip->card2lun[SD_CARD] >= MAX_ALLOWED_LUN_CNT) अणु
		clear_bit(SD_NR, &chip->need_reset);
		chip->sd_reset_counter = 0;
		chip->sd_show_cnt = 0;
		वापस;
	पूर्ण

	chip->rw_fail_cnt[chip->card2lun[SD_CARD]] = 0;

	rtsx_set_stat(chip, RTSX_STAT_RUN);
	rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL, 0xFF, 0);

	retval = reset_sd_card(chip);
	अगर (chip->need_release & SD_CARD)
		वापस;
	अगर (retval == STATUS_SUCCESS) अणु
		clear_bit(SD_NR, &chip->need_reset);
		chip->sd_reset_counter = 0;
		chip->sd_show_cnt = 0;
		chip->card_पढ़ोy |= SD_CARD;
		chip->card_fail &= ~SD_CARD;
		chip->rw_card[chip->card2lun[SD_CARD]] = sd_rw;
	पूर्ण अन्यथा अणु
		अगर (chip->sd_io || (chip->sd_reset_counter >= MAX_RESET_CNT)) अणु
			clear_bit(SD_NR, &chip->need_reset);
			chip->sd_reset_counter = 0;
			chip->sd_show_cnt = 0;
		पूर्ण अन्यथा अणु
			chip->sd_reset_counter++;
		पूर्ण
		chip->card_पढ़ोy &= ~SD_CARD;
		chip->card_fail |= SD_CARD;
		chip->capacity[chip->card2lun[SD_CARD]] = 0;
		chip->rw_card[chip->card2lun[SD_CARD]] = शून्य;

		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SD_OUTPUT_EN, 0);
		अगर (!chip->ft2_fast_mode)
			card_घातer_off(chip, SD_CARD);
		अगर (chip->sd_io) अणु
			chip->sd_पूर्णांक = 0;
			try_to_चयन_sdio_ctrl(chip);
		पूर्ण अन्यथा अणु
			disable_card_घड़ी(chip, SD_CARD);
		पूर्ण
	पूर्ण
पूर्ण

व्योम करो_reset_xd_card(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	dev_dbg(rtsx_dev(chip), "%s: %d, card2lun = 0x%x\n", __func__,
		chip->xd_reset_counter, chip->card2lun[XD_CARD]);

	अगर (chip->card2lun[XD_CARD] >= MAX_ALLOWED_LUN_CNT) अणु
		clear_bit(XD_NR, &chip->need_reset);
		chip->xd_reset_counter = 0;
		chip->xd_show_cnt = 0;
		वापस;
	पूर्ण

	chip->rw_fail_cnt[chip->card2lun[XD_CARD]] = 0;

	rtsx_set_stat(chip, RTSX_STAT_RUN);
	rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL, 0xFF, 0);

	retval = reset_xd_card(chip);
	अगर (chip->need_release & XD_CARD)
		वापस;
	अगर (retval == STATUS_SUCCESS) अणु
		clear_bit(XD_NR, &chip->need_reset);
		chip->xd_reset_counter = 0;
		chip->card_पढ़ोy |= XD_CARD;
		chip->card_fail &= ~XD_CARD;
		chip->rw_card[chip->card2lun[XD_CARD]] = xd_rw;
	पूर्ण अन्यथा अणु
		अगर (chip->xd_reset_counter >= MAX_RESET_CNT) अणु
			clear_bit(XD_NR, &chip->need_reset);
			chip->xd_reset_counter = 0;
			chip->xd_show_cnt = 0;
		पूर्ण अन्यथा अणु
			chip->xd_reset_counter++;
		पूर्ण
		chip->card_पढ़ोy &= ~XD_CARD;
		chip->card_fail |= XD_CARD;
		chip->capacity[chip->card2lun[XD_CARD]] = 0;
		chip->rw_card[chip->card2lun[XD_CARD]] = शून्य;

		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, XD_OUTPUT_EN, 0);
		अगर (!chip->ft2_fast_mode)
			card_घातer_off(chip, XD_CARD);
		disable_card_घड़ी(chip, XD_CARD);
	पूर्ण
पूर्ण

व्योम करो_reset_ms_card(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	dev_dbg(rtsx_dev(chip), "%s: %d, card2lun = 0x%x\n", __func__,
		chip->ms_reset_counter, chip->card2lun[MS_CARD]);

	अगर (chip->card2lun[MS_CARD] >= MAX_ALLOWED_LUN_CNT) अणु
		clear_bit(MS_NR, &chip->need_reset);
		chip->ms_reset_counter = 0;
		chip->ms_show_cnt = 0;
		वापस;
	पूर्ण

	chip->rw_fail_cnt[chip->card2lun[MS_CARD]] = 0;

	rtsx_set_stat(chip, RTSX_STAT_RUN);
	rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL, 0xFF, 0);

	retval = reset_ms_card(chip);
	अगर (chip->need_release & MS_CARD)
		वापस;
	अगर (retval == STATUS_SUCCESS) अणु
		clear_bit(MS_NR, &chip->need_reset);
		chip->ms_reset_counter = 0;
		chip->card_पढ़ोy |= MS_CARD;
		chip->card_fail &= ~MS_CARD;
		chip->rw_card[chip->card2lun[MS_CARD]] = ms_rw;
	पूर्ण अन्यथा अणु
		अगर (chip->ms_reset_counter >= MAX_RESET_CNT) अणु
			clear_bit(MS_NR, &chip->need_reset);
			chip->ms_reset_counter = 0;
			chip->ms_show_cnt = 0;
		पूर्ण अन्यथा अणु
			chip->ms_reset_counter++;
		पूर्ण
		chip->card_पढ़ोy &= ~MS_CARD;
		chip->card_fail |= MS_CARD;
		chip->capacity[chip->card2lun[MS_CARD]] = 0;
		chip->rw_card[chip->card2lun[MS_CARD]] = शून्य;

		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, MS_OUTPUT_EN, 0);
		अगर (!chip->ft2_fast_mode)
			card_घातer_off(chip, MS_CARD);
		disable_card_घड़ी(chip, MS_CARD);
	पूर्ण
पूर्ण

अटल व्योम release_sdio(काष्ठा rtsx_chip *chip)
अणु
	अगर (chip->sd_io) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, SD_STOP | SD_CLR_ERR,
				    SD_STOP | SD_CLR_ERR);

		अगर (chip->chip_insert_with_sdio) अणु
			chip->chip_insert_with_sdio = 0;

			अगर (CHECK_PID(chip, 0x5288))
				rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE5A, 0x08, 0x00);
			अन्यथा
				rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE70, 0x80, 0x00);
		पूर्ण

		rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL, SDIO_CD_CTRL, 0);
		chip->sd_io = 0;
	पूर्ण
पूर्ण

व्योम rtsx_घातer_off_card(काष्ठा rtsx_chip *chip)
अणु
	अगर ((chip->card_पढ़ोy & SD_CARD) || chip->sd_io) अणु
		sd_cleanup_work(chip);
		sd_घातer_off_card3v3(chip);
	पूर्ण

	अगर (chip->card_पढ़ोy & XD_CARD) अणु
		xd_cleanup_work(chip);
		xd_घातer_off_card3v3(chip);
	पूर्ण

	अगर (chip->card_पढ़ोy & MS_CARD) अणु
		ms_cleanup_work(chip);
		ms_घातer_off_card3v3(chip);
	पूर्ण
पूर्ण

व्योम rtsx_release_cards(काष्ठा rtsx_chip *chip)
अणु
	chip->पूर्णांक_reg = rtsx_पढ़ोl(chip, RTSX_BIPR);

	अगर ((chip->card_पढ़ोy & SD_CARD) || chip->sd_io) अणु
		अगर (chip->पूर्णांक_reg & SD_EXIST)
			sd_cleanup_work(chip);
		release_sd_card(chip);
	पूर्ण

	अगर (chip->card_पढ़ोy & XD_CARD) अणु
		अगर (chip->पूर्णांक_reg & XD_EXIST)
			xd_cleanup_work(chip);
		release_xd_card(chip);
	पूर्ण

	अगर (chip->card_पढ़ोy & MS_CARD) अणु
		अगर (chip->पूर्णांक_reg & MS_EXIST)
			ms_cleanup_work(chip);
		release_ms_card(chip);
	पूर्ण
पूर्ण

व्योम rtsx_reset_cards(काष्ठा rtsx_chip *chip)
अणु
	अगर (!chip->need_reset)
		वापस;

	rtsx_set_stat(chip, RTSX_STAT_RUN);

	rtsx_क्रमce_घातer_on(chip, SSC_PDCTL | OC_PDCTL);

	rtsx_disable_aspm(chip);

	अगर ((chip->need_reset & SD_CARD) && chip->chip_insert_with_sdio)
		clear_bit(SD_NR, &chip->need_reset);

	अगर (chip->need_reset & XD_CARD) अणु
		chip->card_exist |= XD_CARD;

		अगर (chip->xd_show_cnt >= MAX_SHOW_CNT)
			करो_reset_xd_card(chip);
		अन्यथा
			chip->xd_show_cnt++;
	पूर्ण
	अगर (CHECK_PID(chip, 0x5288) && CHECK_BARO_PKG(chip, QFN)) अणु
		अगर (chip->card_exist & XD_CARD) अणु
			clear_bit(SD_NR, &chip->need_reset);
			clear_bit(MS_NR, &chip->need_reset);
		पूर्ण
	पूर्ण
	अगर (chip->need_reset & SD_CARD) अणु
		chip->card_exist |= SD_CARD;

		अगर (chip->sd_show_cnt >= MAX_SHOW_CNT) अणु
			rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, RB_FLUSH, RB_FLUSH);
			करो_reset_sd_card(chip);
		पूर्ण अन्यथा अणु
			chip->sd_show_cnt++;
		पूर्ण
	पूर्ण
	अगर (chip->need_reset & MS_CARD) अणु
		chip->card_exist |= MS_CARD;

		अगर (chip->ms_show_cnt >= MAX_SHOW_CNT)
			करो_reset_ms_card(chip);
		अन्यथा
			chip->ms_show_cnt++;
	पूर्ण
पूर्ण

व्योम rtsx_reinit_cards(काष्ठा rtsx_chip *chip, पूर्णांक reset_chip)
अणु
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	rtsx_क्रमce_घातer_on(chip, SSC_PDCTL | OC_PDCTL);

	अगर (reset_chip)
		rtsx_reset_chip(chip);

	chip->पूर्णांक_reg = rtsx_पढ़ोl(chip, RTSX_BIPR);

	अगर ((chip->पूर्णांक_reg & SD_EXIST) && (chip->need_reinit & SD_CARD)) अणु
		release_sdio(chip);
		release_sd_card(chip);

		रुको_समयout(100);

		chip->card_exist |= SD_CARD;
		करो_reset_sd_card(chip);
	पूर्ण

	अगर ((chip->पूर्णांक_reg & XD_EXIST) && (chip->need_reinit & XD_CARD)) अणु
		release_xd_card(chip);

		रुको_समयout(100);

		chip->card_exist |= XD_CARD;
		करो_reset_xd_card(chip);
	पूर्ण

	अगर ((chip->पूर्णांक_reg & MS_EXIST) && (chip->need_reinit & MS_CARD)) अणु
		release_ms_card(chip);

		रुको_समयout(100);

		chip->card_exist |= MS_CARD;
		करो_reset_ms_card(chip);
	पूर्ण

	chip->need_reinit = 0;
पूर्ण

#अगर_घोषित DISABLE_CARD_INT
व्योम card_cd_debounce(काष्ठा rtsx_chip *chip, अचिन्हित दीर्घ *need_reset,
		      अचिन्हित दीर्घ *need_release)
अणु
	u8 release_map = 0, reset_map = 0;

	chip->पूर्णांक_reg = rtsx_पढ़ोl(chip, RTSX_BIPR);

	अगर (chip->card_exist) अणु
		अगर (chip->card_exist & XD_CARD) अणु
			अगर (!(chip->पूर्णांक_reg & XD_EXIST))
				release_map |= XD_CARD;
		पूर्ण अन्यथा अगर (chip->card_exist & SD_CARD) अणु
			अगर (!(chip->पूर्णांक_reg & SD_EXIST))
				release_map |= SD_CARD;
		पूर्ण अन्यथा अगर (chip->card_exist & MS_CARD) अणु
			अगर (!(chip->पूर्णांक_reg & MS_EXIST))
				release_map |= MS_CARD;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->पूर्णांक_reg & XD_EXIST)
			reset_map |= XD_CARD;
		अन्यथा अगर (chip->पूर्णांक_reg & SD_EXIST)
			reset_map |= SD_CARD;
		अन्यथा अगर (chip->पूर्णांक_reg & MS_EXIST)
			reset_map |= MS_CARD;
	पूर्ण

	अगर (reset_map) अणु
		पूर्णांक xd_cnt = 0, sd_cnt = 0, ms_cnt = 0;
		पूर्णांक i;

		क्रम (i = 0; i < (DEBOUNCE_CNT); i++) अणु
			chip->पूर्णांक_reg = rtsx_पढ़ोl(chip, RTSX_BIPR);

			अगर (chip->पूर्णांक_reg & XD_EXIST)
				xd_cnt++;
			अन्यथा
				xd_cnt = 0;

			अगर (chip->पूर्णांक_reg & SD_EXIST)
				sd_cnt++;
			अन्यथा
				sd_cnt = 0;

			अगर (chip->पूर्णांक_reg & MS_EXIST)
				ms_cnt++;
			अन्यथा
				ms_cnt = 0;

			रुको_समयout(30);
		पूर्ण

		reset_map = 0;
		अगर (!(chip->card_exist & XD_CARD) &&
		    (xd_cnt > (DEBOUNCE_CNT - 1)))
			reset_map |= XD_CARD;
		अगर (!(chip->card_exist & SD_CARD) &&
		    (sd_cnt > (DEBOUNCE_CNT - 1)))
			reset_map |= SD_CARD;
		अगर (!(chip->card_exist & MS_CARD) &&
		    (ms_cnt > (DEBOUNCE_CNT - 1)))
			reset_map |= MS_CARD;
	पूर्ण

	अगर (CHECK_PID(chip, 0x5288) && CHECK_BARO_PKG(chip, QFN))
		rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0xC0, 0x00);

	अगर (need_reset)
		*need_reset = reset_map;
	अगर (need_release)
		*need_release = release_map;
पूर्ण
#पूर्ण_अगर

व्योम rtsx_init_cards(काष्ठा rtsx_chip *chip)
अणु
	अगर (RTSX_TST_DELINK(chip) && (rtsx_get_stat(chip) != RTSX_STAT_SS)) अणु
		dev_dbg(rtsx_dev(chip), "Reset chip in polling thread!\n");
		rtsx_reset_chip(chip);
		RTSX_CLR_DELINK(chip);
	पूर्ण

#अगर_घोषित DISABLE_CARD_INT
	card_cd_debounce(chip, &chip->need_reset, &chip->need_release);
#पूर्ण_अगर

	अगर (chip->need_release) अणु
		अगर (CHECK_PID(chip, 0x5288) && CHECK_BARO_PKG(chip, QFN)) अणु
			अगर (chip->पूर्णांक_reg & XD_EXIST) अणु
				clear_bit(SD_NR, &chip->need_release);
				clear_bit(MS_NR, &chip->need_release);
			पूर्ण
		पूर्ण

		अगर (!(chip->card_exist & SD_CARD) && !chip->sd_io)
			clear_bit(SD_NR, &chip->need_release);
		अगर (!(chip->card_exist & XD_CARD))
			clear_bit(XD_NR, &chip->need_release);
		अगर (!(chip->card_exist & MS_CARD))
			clear_bit(MS_NR, &chip->need_release);

		dev_dbg(rtsx_dev(chip), "chip->need_release = 0x%x\n",
			(अचिन्हित पूर्णांक)(chip->need_release));

#अगर_घोषित SUPPORT_OCP
		अगर (chip->need_release) अणु
			अगर (chip->ocp_stat & (CARD_OC_NOW | CARD_OC_EVER))
				rtsx_ग_लिखो_रेजिस्टर(chip, OCPCLR,
						    CARD_OC_INT_CLR |
						    CARD_OC_CLR,
						    CARD_OC_INT_CLR |
						    CARD_OC_CLR);
			chip->ocp_stat = 0;
		पूर्ण
#पूर्ण_अगर
		अगर (chip->need_release) अणु
			rtsx_set_stat(chip, RTSX_STAT_RUN);
			rtsx_क्रमce_घातer_on(chip, SSC_PDCTL | OC_PDCTL);
		पूर्ण

		अगर (chip->need_release & SD_CARD) अणु
			clear_bit(SD_NR, &chip->need_release);
			chip->card_exist &= ~SD_CARD;
			chip->card_ejected &= ~SD_CARD;
			chip->card_fail &= ~SD_CARD;
			CLR_BIT(chip->lun_mc, chip->card2lun[SD_CARD]);
			chip->rw_fail_cnt[chip->card2lun[SD_CARD]] = 0;
			rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, RB_FLUSH, RB_FLUSH);

			release_sdio(chip);
			release_sd_card(chip);
		पूर्ण

		अगर (chip->need_release & XD_CARD) अणु
			clear_bit(XD_NR, &chip->need_release);
			chip->card_exist &= ~XD_CARD;
			chip->card_ejected &= ~XD_CARD;
			chip->card_fail &= ~XD_CARD;
			CLR_BIT(chip->lun_mc, chip->card2lun[XD_CARD]);
			chip->rw_fail_cnt[chip->card2lun[XD_CARD]] = 0;

			release_xd_card(chip);

			अगर (CHECK_PID(chip, 0x5288) &&
			    CHECK_BARO_PKG(chip, QFN))
				rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE,
						    0xC0, 0xC0);
		पूर्ण

		अगर (chip->need_release & MS_CARD) अणु
			clear_bit(MS_NR, &chip->need_release);
			chip->card_exist &= ~MS_CARD;
			chip->card_ejected &= ~MS_CARD;
			chip->card_fail &= ~MS_CARD;
			CLR_BIT(chip->lun_mc, chip->card2lun[MS_CARD]);
			chip->rw_fail_cnt[chip->card2lun[MS_CARD]] = 0;

			release_ms_card(chip);
		पूर्ण

		dev_dbg(rtsx_dev(chip), "chip->card_exist = 0x%x\n",
			chip->card_exist);

		अगर (!chip->card_exist)
			turn_off_led(chip, LED_GPIO);
	पूर्ण

	अगर (chip->need_reset) अणु
		dev_dbg(rtsx_dev(chip), "chip->need_reset = 0x%x\n",
			(अचिन्हित पूर्णांक)(chip->need_reset));

		rtsx_reset_cards(chip);
	पूर्ण

	अगर (chip->need_reinit) अणु
		dev_dbg(rtsx_dev(chip), "chip->need_reinit = 0x%x\n",
			(अचिन्हित पूर्णांक)(chip->need_reinit));

		rtsx_reinit_cards(chip, 0);
	पूर्ण
पूर्ण

पूर्णांक चयन_ssc_घड़ी(काष्ठा rtsx_chip *chip, पूर्णांक clk)
अणु
	पूर्णांक retval;
	u8 n = (u8)(clk - 2), min_n, max_n;
	u8 mcu_cnt, भाग, max_भाग, ssc_depth, ssc_depth_mask;
	पूर्णांक sd_vpclk_phase_reset = 0;

	अगर (chip->cur_clk == clk)
		वापस STATUS_SUCCESS;

	min_n = 60;
	max_n = 120;
	max_भाग = CLK_DIV_4;

	dev_dbg(rtsx_dev(chip), "Switch SSC clock to %dMHz (cur_clk = %d)\n",
		clk, chip->cur_clk);

	अगर ((clk <= 2) || (n > max_n))
		वापस STATUS_FAIL;

	mcu_cnt = (u8)(125 / clk + 3);
	अगर (mcu_cnt > 7)
		mcu_cnt = 7;

	भाग = CLK_DIV_1;
	जबतक ((n < min_n) && (भाग < max_भाग)) अणु
		n = (n + 2) * 2 - 2;
		भाग++;
	पूर्ण
	dev_dbg(rtsx_dev(chip), "n = %d, div = %d\n", n, भाग);

	अगर (chip->ssc_en) अणु
		ssc_depth = 0x01;
		n -= 2;
	पूर्ण अन्यथा अणु
		ssc_depth = 0;
	पूर्ण

	ssc_depth_mask = 0x03;

	dev_dbg(rtsx_dev(chip), "ssc_depth = %d\n", ssc_depth);

	rtsx_init_cmd(chip);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CLK_CTL, CLK_LOW_FREQ, CLK_LOW_FREQ);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CLK_DIV, 0xFF, (भाग << 4) | mcu_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_CTL2, ssc_depth_mask, ssc_depth);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_DIV_N_0, 0xFF, n);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, SSC_RSTB);
	अगर (sd_vpclk_phase_reset) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, SD_VPCLK0_CTL,
			     PHASE_NOT_RESET, 0);
		rtsx_add_cmd(chip, WRITE_REG_CMD, SD_VPCLK0_CTL,
			     PHASE_NOT_RESET, PHASE_NOT_RESET);
	पूर्ण

	retval = rtsx_send_cmd(chip, 0, WAIT_TIME);
	अगर (retval < 0)
		वापस STATUS_ERROR;

	udelay(10);
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL, CLK_LOW_FREQ, 0);
	अगर (retval)
		वापस retval;

	chip->cur_clk = clk;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक चयन_normal_घड़ी(काष्ठा rtsx_chip *chip, पूर्णांक clk)
अणु
	पूर्णांक retval;
	u8 sel, भाग, mcu_cnt;
	पूर्णांक sd_vpclk_phase_reset = 0;

	अगर (chip->cur_clk == clk)
		वापस STATUS_SUCCESS;

	चयन (clk) अणु
	हाल CLK_20:
		dev_dbg(rtsx_dev(chip), "Switch clock to 20MHz\n");
		sel = SSC_80;
		भाग = CLK_DIV_4;
		mcu_cnt = 7;
		अवरोध;

	हाल CLK_30:
		dev_dbg(rtsx_dev(chip), "Switch clock to 30MHz\n");
		sel = SSC_120;
		भाग = CLK_DIV_4;
		mcu_cnt = 7;
		अवरोध;

	हाल CLK_40:
		dev_dbg(rtsx_dev(chip), "Switch clock to 40MHz\n");
		sel = SSC_80;
		भाग = CLK_DIV_2;
		mcu_cnt = 7;
		अवरोध;

	हाल CLK_50:
		dev_dbg(rtsx_dev(chip), "Switch clock to 50MHz\n");
		sel = SSC_100;
		भाग = CLK_DIV_2;
		mcu_cnt = 6;
		अवरोध;

	हाल CLK_60:
		dev_dbg(rtsx_dev(chip), "Switch clock to 60MHz\n");
		sel = SSC_120;
		भाग = CLK_DIV_2;
		mcu_cnt = 6;
		अवरोध;

	हाल CLK_80:
		dev_dbg(rtsx_dev(chip), "Switch clock to 80MHz\n");
		sel = SSC_80;
		भाग = CLK_DIV_1;
		mcu_cnt = 5;
		अवरोध;

	हाल CLK_100:
		dev_dbg(rtsx_dev(chip), "Switch clock to 100MHz\n");
		sel = SSC_100;
		भाग = CLK_DIV_1;
		mcu_cnt = 5;
		अवरोध;

	हाल CLK_120:
		dev_dbg(rtsx_dev(chip), "Switch clock to 120MHz\n");
		sel = SSC_120;
		भाग = CLK_DIV_1;
		mcu_cnt = 5;
		अवरोध;

	हाल CLK_150:
		dev_dbg(rtsx_dev(chip), "Switch clock to 150MHz\n");
		sel = SSC_150;
		भाग = CLK_DIV_1;
		mcu_cnt = 4;
		अवरोध;

	हाल CLK_200:
		dev_dbg(rtsx_dev(chip), "Switch clock to 200MHz\n");
		sel = SSC_200;
		भाग = CLK_DIV_1;
		mcu_cnt = 4;
		अवरोध;

	शेष:
		dev_dbg(rtsx_dev(chip), "Try to switch to an illegal clock (%d)\n",
			clk);
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL, 0xFF, CLK_LOW_FREQ);
	अगर (retval)
		वापस retval;
	अगर (sd_vpclk_phase_reset) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VPCLK0_CTL,
					     PHASE_NOT_RESET, 0);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VPCLK1_CTL,
					     PHASE_NOT_RESET, 0);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_DIV, 0xFF,
				     (भाग << 4) | mcu_cnt);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_SEL, 0xFF, sel);
	अगर (retval)
		वापस retval;

	अगर (sd_vpclk_phase_reset) अणु
		udelay(200);
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VPCLK0_CTL,
					     PHASE_NOT_RESET, PHASE_NOT_RESET);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SD_VPCLK1_CTL,
					     PHASE_NOT_RESET, PHASE_NOT_RESET);
		अगर (retval)
			वापस retval;
		udelay(200);
	पूर्ण
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_CTL, 0xFF, 0);
	अगर (retval)
		वापस retval;

	chip->cur_clk = clk;

	वापस STATUS_SUCCESS;
पूर्ण

व्योम trans_dma_enable(क्रमागत dma_data_direction dir, काष्ठा rtsx_chip *chip,
		      u32 byte_cnt, u8 pack_size)
अणु
	अगर (pack_size > DMA_1024)
		pack_size = DMA_512;

	rtsx_add_cmd(chip, WRITE_REG_CMD, IRQSTAT0, DMA_DONE_INT, DMA_DONE_INT);

	rtsx_add_cmd(chip, WRITE_REG_CMD, DMATC3, 0xFF, (u8)(byte_cnt >> 24));
	rtsx_add_cmd(chip, WRITE_REG_CMD, DMATC2, 0xFF, (u8)(byte_cnt >> 16));
	rtsx_add_cmd(chip, WRITE_REG_CMD, DMATC1, 0xFF, (u8)(byte_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, DMATC0, 0xFF, (u8)byte_cnt);

	अगर (dir == DMA_FROM_DEVICE) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, DMACTL,
			     0x03 | DMA_PACK_SIZE_MASK,
			     DMA_सूची_FROM_CARD | DMA_EN | pack_size);
	पूर्ण अन्यथा अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, DMACTL,
			     0x03 | DMA_PACK_SIZE_MASK,
			     DMA_सूची_TO_CARD | DMA_EN | pack_size);
	पूर्ण

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
पूर्ण

पूर्णांक enable_card_घड़ी(काष्ठा rtsx_chip *chip, u8 card)
अणु
	पूर्णांक retval;
	u8 clk_en = 0;

	अगर (card & XD_CARD)
		clk_en |= XD_CLK_EN;
	अगर (card & SD_CARD)
		clk_en |= SD_CLK_EN;
	अगर (card & MS_CARD)
		clk_en |= MS_CLK_EN;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_CLK_EN, clk_en, clk_en);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक disable_card_घड़ी(काष्ठा rtsx_chip *chip, u8 card)
अणु
	पूर्णांक retval;
	u8 clk_en = 0;

	अगर (card & XD_CARD)
		clk_en |= XD_CLK_EN;
	अगर (card & SD_CARD)
		clk_en |= SD_CLK_EN;
	अगर (card & MS_CARD)
		clk_en |= MS_CLK_EN;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_CLK_EN, clk_en, 0);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक card_घातer_on(काष्ठा rtsx_chip *chip, u8 card)
अणु
	पूर्णांक retval;
	u8 mask, val1, val2;

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN) && (card == MS_CARD)) अणु
		mask = MS_POWER_MASK;
		val1 = MS_PARTIAL_POWER_ON;
		val2 = MS_POWER_ON;
	पूर्ण अन्यथा अणु
		mask = SD_POWER_MASK;
		val1 = SD_PARTIAL_POWER_ON;
		val2 = SD_POWER_ON;
	पूर्ण

	rtsx_init_cmd(chip);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PWR_CTL, mask, val1);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	udelay(chip->pmos_pwr_on_पूर्णांकerval);

	rtsx_init_cmd(chip);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PWR_CTL, mask, val2);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक card_घातer_off(काष्ठा rtsx_chip *chip, u8 card)
अणु
	पूर्णांक retval;
	u8 mask, val;

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN) && (card == MS_CARD)) अणु
		mask = MS_POWER_MASK;
		val = MS_POWER_OFF;
	पूर्ण अन्यथा अणु
		mask = SD_POWER_MASK;
		val = SD_POWER_OFF;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PWR_CTL, mask, val);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक card_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	    u32 sec_addr, u16 sec_cnt)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक i;

	अगर (!chip->rw_card[lun])
		वापस STATUS_FAIL;

	क्रम (i = 0; i < 3; i++) अणु
		chip->rw_need_retry = 0;

		retval = chip->rw_card[lun](srb, chip, sec_addr, sec_cnt);
		अगर (retval != STATUS_SUCCESS) अणु
			अगर (rtsx_check_chip_exist(chip) != STATUS_SUCCESS) अणु
				rtsx_release_chip(chip);
				वापस STATUS_FAIL;
			पूर्ण
			अगर (detect_card_cd(chip, chip->cur_card) !=
							STATUS_SUCCESS) अणु
				वापस STATUS_FAIL;
			पूर्ण

			अगर (!chip->rw_need_retry) अणु
				dev_dbg(rtsx_dev(chip), "RW fail, but no need to retry\n");
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			chip->rw_need_retry = 0;
			अवरोध;
		पूर्ण

		dev_dbg(rtsx_dev(chip), "Retry RW, (i = %d)\n", i);
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक card_share_mode(काष्ठा rtsx_chip *chip, पूर्णांक card)
अणु
	पूर्णांक retval;
	u8 mask, value;

	अगर (CHECK_PID(chip, 0x5208)) अणु
		mask = CARD_SHARE_MASK;
		अगर (card == SD_CARD)
			value = CARD_SHARE_48_SD;
		अन्यथा अगर (card == MS_CARD)
			value = CARD_SHARE_48_MS;
		अन्यथा अगर (card == XD_CARD)
			value = CARD_SHARE_48_XD;
		अन्यथा
			वापस STATUS_FAIL;

	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		mask = 0x03;
		अगर (card == SD_CARD)
			value = CARD_SHARE_BAROSSA_SD;
		अन्यथा अगर (card == MS_CARD)
			value = CARD_SHARE_BAROSSA_MS;
		अन्यथा अगर (card == XD_CARD)
			value = CARD_SHARE_BAROSSA_XD;
		अन्यथा
			वापस STATUS_FAIL;

	पूर्ण अन्यथा अणु
		वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_SHARE_MODE, mask, value);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक select_card(काष्ठा rtsx_chip *chip, पूर्णांक card)
अणु
	पूर्णांक retval;

	अगर (chip->cur_card != card) अणु
		u8 mod;

		अगर (card == SD_CARD)
			mod = SD_MOD_SEL;
		अन्यथा अगर (card == MS_CARD)
			mod = MS_MOD_SEL;
		अन्यथा अगर (card == XD_CARD)
			mod = XD_MOD_SEL;
		अन्यथा अगर (card == SPI_CARD)
			mod = SPI_MOD_SEL;
		अन्यथा
			वापस STATUS_FAIL;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_SELECT, 0x07, mod);
		अगर (retval)
			वापस retval;
		chip->cur_card = card;

		retval =  card_share_mode(chip, card);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

व्योम toggle_gpio(काष्ठा rtsx_chip *chip, u8 gpio)
अणु
	u8 temp_reg;

	rtsx_पढ़ो_रेजिस्टर(chip, CARD_GPIO, &temp_reg);
	temp_reg ^= (0x01 << gpio);
	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO, 0xFF, temp_reg);
पूर्ण

व्योम turn_on_led(काष्ठा rtsx_chip *chip, u8 gpio)
अणु
	अगर (CHECK_PID(chip, 0x5288))
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO, (u8)(1 << gpio),
				    (u8)(1 << gpio));
	अन्यथा
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO, (u8)(1 << gpio), 0);
पूर्ण

व्योम turn_off_led(काष्ठा rtsx_chip *chip, u8 gpio)
अणु
	अगर (CHECK_PID(chip, 0x5288))
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO, (u8)(1 << gpio), 0);
	अन्यथा
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO, (u8)(1 << gpio),
				    (u8)(1 << gpio));
पूर्ण

पूर्णांक detect_card_cd(काष्ठा rtsx_chip *chip, पूर्णांक card)
अणु
	u32 card_cd, status;

	अगर (card == SD_CARD) अणु
		card_cd = SD_EXIST;
	पूर्ण अन्यथा अगर (card == MS_CARD) अणु
		card_cd = MS_EXIST;
	पूर्ण अन्यथा अगर (card == XD_CARD) अणु
		card_cd = XD_EXIST;
	पूर्ण अन्यथा अणु
		dev_dbg(rtsx_dev(chip), "Wrong card type: 0x%x\n", card);
		वापस STATUS_FAIL;
	पूर्ण

	status = rtsx_पढ़ोl(chip, RTSX_BIPR);
	अगर (!(status & card_cd))
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक check_card_exist(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun)
अणु
	अगर (chip->card_exist & chip->lun2card[lun])
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक check_card_पढ़ोy(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun)
अणु
	अगर (chip->card_पढ़ोy & chip->lun2card[lun])
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक check_card_wp(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun)
अणु
	अगर (chip->card_wp & chip->lun2card[lun])
		वापस 1;

	वापस 0;
पूर्ण

u8 get_lun_card(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun)
अणु
	अगर ((chip->card_पढ़ोy & chip->lun2card[lun]) == XD_CARD)
		वापस (u8)XD_CARD;
	अन्यथा अगर ((chip->card_पढ़ोy & chip->lun2card[lun]) == SD_CARD)
		वापस (u8)SD_CARD;
	अन्यथा अगर ((chip->card_पढ़ोy & chip->lun2card[lun]) == MS_CARD)
		वापस (u8)MS_CARD;

	वापस 0;
पूर्ण

व्योम eject_card(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun)
अणु
	करो_reमुख्यing_work(chip);

	अगर ((chip->card_पढ़ोy & chip->lun2card[lun]) == SD_CARD) अणु
		release_sd_card(chip);
		chip->card_ejected |= SD_CARD;
		chip->card_पढ़ोy &= ~SD_CARD;
		chip->capacity[lun] = 0;
	पूर्ण अन्यथा अगर ((chip->card_पढ़ोy & chip->lun2card[lun]) == XD_CARD) अणु
		release_xd_card(chip);
		chip->card_ejected |= XD_CARD;
		chip->card_पढ़ोy &= ~XD_CARD;
		chip->capacity[lun] = 0;
	पूर्ण अन्यथा अगर ((chip->card_पढ़ोy & chip->lun2card[lun]) == MS_CARD) अणु
		release_ms_card(chip);
		chip->card_ejected |= MS_CARD;
		chip->card_पढ़ोy &= ~MS_CARD;
		chip->capacity[lun] = 0;
	पूर्ण
पूर्ण
