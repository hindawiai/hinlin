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
#समावेश <linux/vदो_स्मृति.h>

#समावेश "rtsx.h"
#समावेश "sd.h"
#समावेश "xd.h"
#समावेश "ms.h"

अटल व्योम rtsx_calibration(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x1B, 0x135E);
	रुको_समयout(10);
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x00, 0x0280);
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x01, 0x7112);
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x01, 0x7110);
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x01, 0x7112);
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x01, 0x7113);
	rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x00, 0x0288);
पूर्ण

व्योम rtsx_enable_card_पूर्णांक(काष्ठा rtsx_chip *chip)
अणु
	u32 reg = rtsx_पढ़ोl(chip, RTSX_BIER);
	पूर्णांक i;

	क्रम (i = 0; i <= chip->max_lun; i++) अणु
		अगर (chip->lun2card[i] & XD_CARD)
			reg |= XD_INT_EN;
		अगर (chip->lun2card[i] & SD_CARD)
			reg |= SD_INT_EN;
		अगर (chip->lun2card[i] & MS_CARD)
			reg |= MS_INT_EN;
	पूर्ण
	अगर (chip->hw_bypass_sd)
		reg &= ~((u32)SD_INT_EN);

	rtsx_ग_लिखोl(chip, RTSX_BIER, reg);
पूर्ण

व्योम rtsx_enable_bus_पूर्णांक(काष्ठा rtsx_chip *chip)
अणु
	u32 reg = 0;
#अगर_अघोषित DISABLE_CARD_INT
	पूर्णांक i;
#पूर्ण_अगर

	reg = TRANS_OK_INT_EN | TRANS_FAIL_INT_EN;

#अगर_अघोषित DISABLE_CARD_INT
	क्रम (i = 0; i <= chip->max_lun; i++) अणु
		dev_dbg(rtsx_dev(chip), "lun2card[%d] = 0x%02x\n",
			i, chip->lun2card[i]);

		अगर (chip->lun2card[i] & XD_CARD)
			reg |= XD_INT_EN;
		अगर (chip->lun2card[i] & SD_CARD)
			reg |= SD_INT_EN;
		अगर (chip->lun2card[i] & MS_CARD)
			reg |= MS_INT_EN;
	पूर्ण
	अगर (chip->hw_bypass_sd)
		reg &= ~((u32)SD_INT_EN);
#पूर्ण_अगर

	अगर (chip->ic_version >= IC_VER_C)
		reg |= DELINK_INT_EN;
#अगर_घोषित SUPPORT_OCP
	reg |= OC_INT_EN;
#पूर्ण_अगर
	अगर (!chip->adma_mode)
		reg |= DATA_DONE_INT_EN;

	/* Enable Bus Interrupt */
	rtsx_ग_लिखोl(chip, RTSX_BIER, reg);

	dev_dbg(rtsx_dev(chip), "RTSX_BIER: 0x%08x\n", reg);
पूर्ण

व्योम rtsx_disable_bus_पूर्णांक(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखोl(chip, RTSX_BIER, 0);
पूर्ण

अटल पूर्णांक rtsx_pre_handle_sdio_old(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	अगर (chip->ignore_sd && CHK_SDIO_EXIST(chip)) अणु
		अगर (chip->asic_code) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PULL_CTL5,
						     0xFF,
						     MS_INS_PU | SD_WP_PU |
						     SD_CD_PU | SD_CMD_PU);
			अगर (retval)
				वापस retval;
		पूर्ण अन्यथा अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPGA_PULL_CTL,
						     0xFF,
						     FPGA_SD_PULL_CTL_EN);
			अगर (retval)
				वापस retval;
		पूर्ण
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_SHARE_MODE, 0xFF,
					     CARD_SHARE_48_SD);
		अगर (retval)
			वापस retval;

		/* Enable SDIO पूर्णांकernal घड़ी */
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, 0xFF2C, 0x01, 0x01);
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL, 0xFF,
					     SDIO_BUS_CTRL | SDIO_CD_CTRL);
		अगर (retval)
			वापस retval;

		chip->sd_पूर्णांक = 1;
		chip->sd_io = 1;
	पूर्ण अन्यथा अणु
		chip->need_reset |= SD_CARD;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

#अगर_घोषित HW_AUTO_SWITCH_SD_BUS
अटल पूर्णांक rtsx_pre_handle_sdio_new(काष्ठा rtsx_chip *chip)
अणु
	u8 पंचांगp;
	bool sw_bypass_sd = false;
	पूर्णांक retval;

	अगर (chip->driver_first_load) अणु
		अगर (CHECK_PID(chip, 0x5288)) अणु
			retval = rtsx_पढ़ो_रेजिस्टर(chip, 0xFE5A, &पंचांगp);
			अगर (retval)
				वापस retval;
			अगर (पंचांगp & 0x08)
				sw_bypass_sd = true;
		पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5208)) अणु
			retval = rtsx_पढ़ो_रेजिस्टर(chip, 0xFE70, &पंचांगp);
			अगर (retval)
				वापस retval;
			अगर (पंचांगp & 0x80)
				sw_bypass_sd = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->sdio_in_अक्षरge)
			sw_bypass_sd = true;
	पूर्ण
	dev_dbg(rtsx_dev(chip), "chip->sdio_in_charge = %d\n",
		chip->sdio_in_अक्षरge);
	dev_dbg(rtsx_dev(chip), "chip->driver_first_load = %d\n",
		chip->driver_first_load);
	dev_dbg(rtsx_dev(chip), "sw_bypass_sd = %d\n",
		sw_bypass_sd);

	अगर (sw_bypass_sd) अणु
		u8 cd_toggle_mask = 0;

		retval = rtsx_पढ़ो_रेजिस्टर(chip, TLPTISTAT, &पंचांगp);
		अगर (retval)
			वापस retval;
		cd_toggle_mask = 0x08;

		अगर (पंचांगp & cd_toggle_mask) अणु
			/* Disable sdio_bus_स्वतः_चयन */
			अगर (CHECK_PID(chip, 0x5288)) अणु
				retval = rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE5A,
							     0x08, 0x00);
				अगर (retval)
					वापस retval;
			पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5208)) अणु
				retval = rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE70,
							     0x80, 0x00);
				अगर (retval)
					वापस retval;
			पूर्ण

			retval = rtsx_ग_लिखो_रेजिस्टर(chip, TLPTISTAT, 0xFF,
						     पंचांगp);
			अगर (retval)
				वापस retval;

			chip->need_reset |= SD_CARD;
		पूर्ण अन्यथा अणु
			dev_dbg(rtsx_dev(chip), "Chip inserted with SDIO!\n");

			अगर (chip->asic_code) अणु
				retval = sd_pull_ctl_enable(chip);
				अगर (retval != STATUS_SUCCESS)
					वापस STATUS_FAIL;
			पूर्ण अन्यथा अणु
				retval = rtsx_ग_लिखो_रेजिस्टर
						(chip, FPGA_PULL_CTL,
						 FPGA_SD_PULL_CTL_BIT | 0x20,
						 0);
				अगर (retval)
					वापस retval;
			पूर्ण
			retval = card_share_mode(chip, SD_CARD);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;

			/* Enable sdio_bus_स्वतः_चयन */
			अगर (CHECK_PID(chip, 0x5288)) अणु
				retval = rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE5A,
							     0x08, 0x08);
				अगर (retval)
					वापस retval;
			पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5208)) अणु
				retval = rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE70,
							     0x80, 0x80);
				अगर (retval)
					वापस retval;
			पूर्ण

			chip->chip_insert_with_sdio = 1;
			chip->sd_io = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, TLPTISTAT, 0x08, 0x08);
		अगर (retval)
			वापस retval;

		chip->need_reset |= SD_CARD;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtsx_reset_aspm(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक ret;

	अगर (chip->dynamic_aspm) अणु
		अगर (!CHK_SDIO_EXIST(chip) || !CHECK_PID(chip, 0x5288))
			वापस STATUS_SUCCESS;

		ret = rtsx_ग_लिखो_cfg_dw(chip, 2, 0xC0, 0xFF,
					chip->aspm_l0s_l1_en);
		अगर (ret != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		वापस STATUS_SUCCESS;
	पूर्ण

	अगर (CHECK_PID(chip, 0x5208)) अणु
		ret = rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL, 0xFF, 0x3F);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = rtsx_ग_लिखो_config_byte(chip, LCTLR, chip->aspm_l0s_l1_en);
	अगर (ret != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	chip->aspm_level[0] = chip->aspm_l0s_l1_en;
	अगर (CHK_SDIO_EXIST(chip)) अणु
		chip->aspm_level[1] = chip->aspm_l0s_l1_en;
		ret = rtsx_ग_लिखो_cfg_dw(chip, CHECK_PID(chip, 0x5288) ? 2 : 1,
					0xC0, 0xFF, chip->aspm_l0s_l1_en);
		अगर (ret != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	chip->aspm_enabled = 1;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक rtsx_enable_pcie_पूर्णांकr(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक ret;

	अगर (!chip->asic_code || !CHECK_PID(chip, 0x5208)) अणु
		rtsx_enable_bus_पूर्णांक(chip);
		वापस STATUS_SUCCESS;
	पूर्ण

	अगर (chip->phy_debug_mode) अणु
		ret = rtsx_ग_लिखो_रेजिस्टर(chip, CDRESUMECTL, 0x77, 0);
		अगर (ret)
			वापस ret;
		rtsx_disable_bus_पूर्णांक(chip);
	पूर्ण अन्यथा अणु
		rtsx_enable_bus_पूर्णांक(chip);
	पूर्ण

	अगर (chip->ic_version >= IC_VER_D) अणु
		u16 reg;

		ret = rtsx_पढ़ो_phy_रेजिस्टर(chip, 0x00, &reg);
		अगर (ret != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		reg &= 0xFE7F;
		reg |= 0x80;
		ret = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x00, reg);
		अगर (ret != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		ret = rtsx_पढ़ो_phy_रेजिस्टर(chip, 0x1C, &reg);
		अगर (ret != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		reg &= 0xFFF7;
		ret = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x1C, reg);
		अगर (ret != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	अगर (chip->driver_first_load && (chip->ic_version < IC_VER_C))
		rtsx_calibration(chip);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_reset_chip(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	rtsx_ग_लिखोl(chip, RTSX_HCBAR, chip->host_cmds_addr);

	rtsx_disable_aspm(chip);

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0x03, 0x00);
	अगर (retval)
		वापस retval;

	/* Disable card घड़ी */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_CLK_EN, 0x1E, 0);
	अगर (retval)
		वापस retval;

#अगर_घोषित SUPPORT_OCP
	/* SSC घातer on, OCD घातer on */
	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPDCTL, OC_POWER_DOWN, 0);
		अगर (retval)
			वापस retval;
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPDCTL, OC_POWER_DOWN,
					     MS_OC_POWER_DOWN);
		अगर (retval)
			वापस retval;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, OCPPARA1, OCP_TIME_MASK,
				     OCP_TIME_800);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, OCPPARA2, OCP_THD_MASK,
				     OCP_THD_244_946);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, OCPCTL, 0xFF,
				     CARD_OC_INT_EN | CARD_DETECT_EN);
	अगर (retval)
		वापस retval;
#अन्यथा
	/* OC घातer करोwn */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPDCTL, OC_POWER_DOWN,
				     OC_POWER_DOWN);
	अगर (retval)
		वापस retval;
#पूर्ण_अगर

	अगर (!CHECK_PID(chip, 0x5288)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0xFF, 0x03);
		अगर (retval)
			वापस retval;
	पूर्ण

	/* Turn off LED */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO, 0xFF, 0x03);
	अगर (retval)
		वापस retval;

	/* Reset delink mode */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CHANGE_LINK_STATE, 0x0A, 0);
	अगर (retval)
		वापस retval;

	/* Card driving select */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_DRIVE_SEL, 0xFF,
				     chip->card_drive_sel);
	अगर (retval)
		वापस retval;

#अगर_घोषित LED_AUTO_BLINK
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_AUTO_BLINK, 0xFF,
				     LED_BLINK_SPEED | BLINK_EN | LED_GPIO0);
	अगर (retval)
		वापस retval;
#पूर्ण_अगर

	अगर (chip->asic_code) अणु
		/* Enable SSC Clock */
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SSC_CTL1, 0xFF,
					     SSC_8X_EN | SSC_SEL_4M);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SSC_CTL2, 0xFF, 0x12);
		अगर (retval)
			वापस retval;
	पूर्ण

	/*
	 * Disable cd_pwr_save (u_क्रमce_rst_core_en=0, u_cd_rst_core_en=0)
	 *    0xFE5B
	 *    bit[1]    u_cd_rst_core_en	rst_value = 0
	 *    bit[2]    u_क्रमce_rst_core_en	rst_value = 0
	 *    bit[5]    u_mac_phy_rst_n_dbg	rst_value = 1
	 *    bit[4]	u_non_sticky_rst_n_dbg	rst_value = 0
	 */
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CHANGE_LINK_STATE, 0x16, 0x10);
	अगर (retval)
		वापस retval;

	/* Enable ASPM */
	अगर (chip->aspm_l0s_l1_en) अणु
		retval = rtsx_reset_aspm(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		अगर (chip->asic_code && CHECK_PID(chip, 0x5208)) अणु
			retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x07, 0x0129);
			अगर (retval != STATUS_SUCCESS)
				वापस STATUS_FAIL;
		पूर्ण
		retval = rtsx_ग_लिखो_config_byte(chip, LCTLR,
						chip->aspm_l0s_l1_en);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_config_byte(chip, 0x81, 1);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (CHK_SDIO_EXIST(chip)) अणु
		retval = rtsx_ग_लिखो_cfg_dw(chip,
					   CHECK_PID(chip, 0x5288) ? 2 : 1,
					   0xC0, 0xFF00, 0x0100);

		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	अगर (CHECK_PID(chip, 0x5288) && !CHK_SDIO_EXIST(chip)) अणु
		retval = rtsx_ग_लिखो_cfg_dw(chip, 2, 0xC0, 0xFFFF, 0x0103);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = rtsx_ग_लिखो_cfg_dw(chip, 2, 0x84, 0xFF, 0x03);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, IRQSTAT0, LINK_RDY_INT,
				     LINK_RDY_INT);
	अगर (retval)
		वापस retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PERST_GLITCH_WIDTH, 0xFF, 0x80);
	अगर (retval)
		वापस retval;

	retval = rtsx_enable_pcie_पूर्णांकr(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	chip->need_reset = 0;

	chip->पूर्णांक_reg = rtsx_पढ़ोl(chip, RTSX_BIPR);

	अगर (chip->hw_bypass_sd)
		जाओ nextcard;
	dev_dbg(rtsx_dev(chip), "In %s, chip->int_reg = 0x%x\n", __func__,
		chip->पूर्णांक_reg);
	अगर (chip->पूर्णांक_reg & SD_EXIST) अणु
#अगर_घोषित HW_AUTO_SWITCH_SD_BUS
		अगर (CHECK_PID(chip, 0x5208) && (chip->ic_version < IC_VER_C))
			retval = rtsx_pre_handle_sdio_old(chip);
		अन्यथा
			retval = rtsx_pre_handle_sdio_new(chip);

		dev_dbg(rtsx_dev(chip), "chip->need_reset = 0x%x (%s)\n",
			(अचिन्हित पूर्णांक)(chip->need_reset), __func__);
#अन्यथा  /* HW_AUTO_SWITCH_SD_BUS */
		retval = rtsx_pre_handle_sdio_old(chip);
#पूर्ण_अगर  /* HW_AUTO_SWITCH_SD_BUS */
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

	पूर्ण अन्यथा अणु
		chip->sd_io = 0;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SDIO_CTRL,
					     SDIO_BUS_CTRL | SDIO_CD_CTRL, 0);
		अगर (retval)
			वापस retval;
	पूर्ण

nextcard:
	अगर (chip->पूर्णांक_reg & XD_EXIST)
		chip->need_reset |= XD_CARD;
	अगर (chip->पूर्णांक_reg & MS_EXIST)
		chip->need_reset |= MS_CARD;
	अगर (chip->पूर्णांक_reg & CARD_EXIST) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, SSC_CTL1, SSC_RSTB,
					     SSC_RSTB);
		अगर (retval)
			वापस retval;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "In %s, chip->need_reset = 0x%x\n", __func__,
		(अचिन्हित पूर्णांक)(chip->need_reset));

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, RCCTL, 0x01, 0x00);
	अगर (retval)
		वापस retval;

	अगर (CHECK_PID(chip, 0x5208) || CHECK_PID(chip, 0x5288)) अणु
		/* Turn off मुख्य घातer when entering S3/S4 state */
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, MAIN_PWR_OFF_CTL, 0x03,
					     0x03);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (chip->remote_wakeup_en && !chip->स्वतः_delink_en) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, WAKE_SEL_CTL, 0x07, 0x07);
		अगर (retval)
			वापस retval;
		अगर (chip->aux_pwr_exist) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, PME_FORCE_CTL,
						     0xFF, 0x33);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, WAKE_SEL_CTL, 0x07, 0x04);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PME_FORCE_CTL, 0xFF, 0x30);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (CHECK_PID(chip, 0x5208) && (chip->ic_version >= IC_VER_D)) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PETXCFG, 0x1C, 0x14);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (chip->asic_code && CHECK_PID(chip, 0x5208)) अणु
		retval = rtsx_clr_phy_reg_bit(chip, 0x1C, 2);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	अगर (chip->ft2_fast_mode) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PWR_CTL, 0xFF,
					     MS_PARTIAL_POWER_ON |
					     SD_PARTIAL_POWER_ON);
		अगर (retval)
			वापस retval;
		udelay(chip->pmos_pwr_on_पूर्णांकerval);
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PWR_CTL, 0xFF,
					     MS_POWER_ON | SD_POWER_ON);
		अगर (retval)
			वापस retval;

		रुको_समयout(200);
	पूर्ण

	/* Reset card */
	rtsx_reset_detected_cards(chip, 0);

	chip->driver_first_load = 0;

	वापस STATUS_SUCCESS;
पूर्ण

अटल अंतरभूत पूर्णांक valid_sd_speed_prior(u32 sd_speed_prior)
अणु
	bool valid_para = true;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		u8 पंचांगp = (u8)(sd_speed_prior >> (i * 8));

		अगर ((पंचांगp < 0x01) || (पंचांगp > 0x04)) अणु
			valid_para = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस valid_para;
पूर्ण

अटल अंतरभूत पूर्णांक valid_sd_current_prior(u32 sd_current_prior)
अणु
	bool valid_para = true;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		u8 पंचांगp = (u8)(sd_current_prior >> (i * 8));

		अगर (पंचांगp > 0x03) अणु
			valid_para = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस valid_para;
पूर्ण

अटल पूर्णांक rts5208_init(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u16 reg = 0;
	u8 val = 0;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_SEL, 0x03, 0x03);
	अगर (retval)
		वापस retval;
	retval = rtsx_पढ़ो_रेजिस्टर(chip, CLK_SEL, &val);
	अगर (retval)
		वापस retval;
	chip->asic_code = val == 0 ? 1 : 0;

	अगर (chip->asic_code) अणु
		retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, 0x1C, &reg);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		dev_dbg(rtsx_dev(chip), "Value of phy register 0x1C is 0x%x\n",
			reg);
		chip->ic_version = (reg >> 4) & 0x07;
		chip->phy_debug_mode = reg & PHY_DEBUG_MODE ? 1 : 0;

	पूर्ण अन्यथा अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, 0xFE80, &val);
		अगर (retval)
			वापस retval;
		chip->ic_version = val;
		chip->phy_debug_mode = 0;
	पूर्ण

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PDINFO, &val);
	अगर (retval)
		वापस retval;
	dev_dbg(rtsx_dev(chip), "PDINFO: 0x%x\n", val);
	chip->aux_pwr_exist = val & AUX_PWR_DETECTED ? 1 : 0;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, 0xFE50, &val);
	अगर (retval)
		वापस retval;
	chip->hw_bypass_sd = val & 0x01 ? 1 : 0;

	rtsx_पढ़ो_config_byte(chip, 0x0E, &val);
	अगर (val & 0x80)
		SET_SDIO_EXIST(chip);
	अन्यथा
		CLR_SDIO_EXIST(chip);

	अगर (chip->use_hw_setting) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, CHANGE_LINK_STATE, &val);
		अगर (retval)
			वापस retval;
		chip->स्वतः_delink_en = val & 0x80 ? 1 : 0;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक rts5288_init(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 val = 0, max_func;
	u32 lval = 0;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_SEL, 0x03, 0x03);
	अगर (retval)
		वापस retval;
	retval = rtsx_पढ़ो_रेजिस्टर(chip, CLK_SEL, &val);
	अगर (retval)
		वापस retval;
	chip->asic_code = val == 0 ? 1 : 0;

	chip->ic_version = 0;
	chip->phy_debug_mode = 0;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PDINFO, &val);
	अगर (retval)
		वापस retval;
	dev_dbg(rtsx_dev(chip), "PDINFO: 0x%x\n", val);
	chip->aux_pwr_exist = val & AUX_PWR_DETECTED ? 1 : 0;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, CARD_SHARE_MODE, &val);
	अगर (retval)
		वापस retval;
	dev_dbg(rtsx_dev(chip), "CARD_SHARE_MODE: 0x%x\n", val);
	chip->baro_pkg = val & 0x04 ? QFN : LQFP;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, 0xFE5A, &val);
	अगर (retval)
		वापस retval;
	chip->hw_bypass_sd = val & 0x10 ? 1 : 0;

	retval = rtsx_पढ़ो_cfg_dw(chip, 0, 0x718, &lval);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	max_func = (u8)((lval >> 29) & 0x07);
	dev_dbg(rtsx_dev(chip), "Max function number: %d\n", max_func);
	अगर (max_func == 0x02)
		SET_SDIO_EXIST(chip);
	अन्यथा
		CLR_SDIO_EXIST(chip);

	अगर (chip->use_hw_setting) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, CHANGE_LINK_STATE, &val);
		अगर (retval)
			वापस retval;
		chip->स्वतः_delink_en = val & 0x80 ? 1 : 0;

		अगर (CHECK_BARO_PKG(chip, LQFP))
			chip->lun_mode = SD_MS_1LUN;
		अन्यथा
			chip->lun_mode = DEFAULT_SINGLE;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_init_chip(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक retval;
	अचिन्हित पूर्णांक i;

	dev_dbg(rtsx_dev(chip), "Vendor ID: 0x%04x, Product ID: 0x%04x\n",
		chip->venकरोr_id, chip->product_id);

	chip->ic_version = 0;

	स_रखो(xd_card, 0, माप(काष्ठा xd_info));
	स_रखो(sd_card, 0, माप(काष्ठा sd_info));
	स_रखो(ms_card, 0, माप(काष्ठा ms_info));

	chip->xd_reset_counter = 0;
	chip->sd_reset_counter = 0;
	chip->ms_reset_counter = 0;

	chip->xd_show_cnt = MAX_SHOW_CNT;
	chip->sd_show_cnt = MAX_SHOW_CNT;
	chip->ms_show_cnt = MAX_SHOW_CNT;

	chip->sd_io = 0;
	chip->स्वतः_delink_cnt = 0;
	chip->स्वतः_delink_allowed = 1;
	rtsx_set_stat(chip, RTSX_STAT_INIT);

	chip->aspm_enabled = 0;
	chip->chip_insert_with_sdio = 0;
	chip->sdio_aspm = 0;
	chip->sdio_idle = 0;
	chip->sdio_counter = 0;
	chip->cur_card = 0;
	chip->phy_debug_mode = 0;
	chip->sdio_func_exist = 0;
	स_रखो(chip->sdio_raw_data, 0, 12);

	क्रम (i = 0; i < MAX_ALLOWED_LUN_CNT; i++) अणु
		set_sense_type(chip, i, SENSE_TYPE_NO_SENSE);
		chip->rw_fail_cnt[i] = 0;
	पूर्ण

	अगर (!valid_sd_speed_prior(chip->sd_speed_prior))
		chip->sd_speed_prior = 0x01040203;

	dev_dbg(rtsx_dev(chip), "sd_speed_prior = 0x%08x\n",
		chip->sd_speed_prior);

	अगर (!valid_sd_current_prior(chip->sd_current_prior))
		chip->sd_current_prior = 0x00010203;

	dev_dbg(rtsx_dev(chip), "sd_current_prior = 0x%08x\n",
		chip->sd_current_prior);

	अगर ((chip->sd_ddr_tx_phase > 31) || (chip->sd_ddr_tx_phase < 0))
		chip->sd_ddr_tx_phase = 0;

	अगर ((chip->mmc_ddr_tx_phase > 31) || (chip->mmc_ddr_tx_phase < 0))
		chip->mmc_ddr_tx_phase = 0;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPDCTL, SSC_POWER_DOWN, 0);
	अगर (retval)
		वापस retval;
	रुको_समयout(200);
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CLK_DIV, 0x07, 0x07);
	अगर (retval)
		वापस retval;
	dev_dbg(rtsx_dev(chip), "chip->use_hw_setting = %d\n",
		chip->use_hw_setting);

	अगर (CHECK_PID(chip, 0x5208)) अणु
		retval = rts5208_init(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

	पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
		retval = rts5288_init(chip);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	अगर (chip->ss_en == 2)
		chip->ss_en = 0;

	dev_dbg(rtsx_dev(chip), "chip->asic_code = %d\n", chip->asic_code);
	dev_dbg(rtsx_dev(chip), "chip->ic_version = 0x%x\n", chip->ic_version);
	dev_dbg(rtsx_dev(chip), "chip->phy_debug_mode = %d\n",
		chip->phy_debug_mode);
	dev_dbg(rtsx_dev(chip), "chip->aux_pwr_exist = %d\n",
		chip->aux_pwr_exist);
	dev_dbg(rtsx_dev(chip), "chip->sdio_func_exist = %d\n",
		chip->sdio_func_exist);
	dev_dbg(rtsx_dev(chip), "chip->hw_bypass_sd = %d\n",
		chip->hw_bypass_sd);
	dev_dbg(rtsx_dev(chip), "chip->aspm_l0s_l1_en = %d\n",
		chip->aspm_l0s_l1_en);
	dev_dbg(rtsx_dev(chip), "chip->lun_mode = %d\n", chip->lun_mode);
	dev_dbg(rtsx_dev(chip), "chip->auto_delink_en = %d\n",
		chip->स्वतः_delink_en);
	dev_dbg(rtsx_dev(chip), "chip->ss_en = %d\n", chip->ss_en);
	dev_dbg(rtsx_dev(chip), "chip->baro_pkg = %d\n", chip->baro_pkg);

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN)) अणु
		chip->card2lun[SD_CARD] = 0;
		chip->card2lun[MS_CARD] = 1;
		chip->card2lun[XD_CARD] = 0xFF;
		chip->lun2card[0] = SD_CARD;
		chip->lun2card[1] = MS_CARD;
		chip->max_lun = 1;
		SET_SDIO_IGNORED(chip);
	पूर्ण अन्यथा अगर (CHECK_LUN_MODE(chip, SD_MS_1LUN)) अणु
		chip->card2lun[SD_CARD] = 0;
		chip->card2lun[MS_CARD] = 0;
		chip->card2lun[XD_CARD] = 0xFF;
		chip->lun2card[0] = SD_CARD | MS_CARD;
		chip->max_lun = 0;
	पूर्ण अन्यथा अणु
		chip->card2lun[XD_CARD] = 0;
		chip->card2lun[SD_CARD] = 0;
		chip->card2lun[MS_CARD] = 0;
		chip->lun2card[0] = XD_CARD | SD_CARD | MS_CARD;
		chip->max_lun = 0;
	पूर्ण

	retval = rtsx_reset_chip(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

व्योम rtsx_release_chip(काष्ठा rtsx_chip *chip)
अणु
	xd_मुक्त_l2p_tbl(chip);
	ms_मुक्त_l2p_tbl(chip);
	chip->card_exist = 0;
	chip->card_पढ़ोy = 0;
पूर्ण

#अगर !defined(LED_AUTO_BLINK) && defined(REGULAR_BLINK)
अटल अंतरभूत व्योम rtsx_blink_led(काष्ठा rtsx_chip *chip)
अणु
	अगर (chip->card_exist && chip->blink_led) अणु
		अगर (chip->led_toggle_counter < LED_TOGGLE_INTERVAL) अणु
			chip->led_toggle_counter++;
		पूर्ण अन्यथा अणु
			chip->led_toggle_counter = 0;
			toggle_gpio(chip, LED_GPIO);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम rtsx_monitor_aspm_config(काष्ठा rtsx_chip *chip)
अणु
	bool reg_changed, maybe_support_aspm;
	u32 पंचांगp = 0;
	u8 reg0 = 0, reg1 = 0;

	maybe_support_aspm = false;
	reg_changed = false;
	rtsx_पढ़ो_config_byte(chip, LCTLR, &reg0);
	अगर (chip->aspm_level[0] != reg0) अणु
		reg_changed = true;
		chip->aspm_level[0] = reg0;
	पूर्ण
	अगर (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNORED(chip)) अणु
		rtsx_पढ़ो_cfg_dw(chip, 1, 0xC0, &पंचांगp);
		reg1 = (u8)पंचांगp;
		अगर (chip->aspm_level[1] != reg1) अणु
			reg_changed = true;
			chip->aspm_level[1] = reg1;
		पूर्ण

		अगर ((reg0 & 0x03) && (reg1 & 0x03))
			maybe_support_aspm = true;

	पूर्ण अन्यथा अणु
		अगर (reg0 & 0x03)
			maybe_support_aspm = true;
	पूर्ण

	अगर (reg_changed) अणु
		अगर (maybe_support_aspm)
			chip->aspm_l0s_l1_en = 0x03;

		dev_dbg(rtsx_dev(chip),
			"aspm_level[0] = 0x%02x, aspm_level[1] = 0x%02x\n",
			chip->aspm_level[0], chip->aspm_level[1]);

		अगर (chip->aspm_l0s_l1_en) अणु
			chip->aspm_enabled = 1;
		पूर्ण अन्यथा अणु
			chip->aspm_enabled = 0;
			chip->sdio_aspm = 0;
		पूर्ण
		rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL, 0xFF,
				    0x30 | chip->aspm_level[0] |
				    (chip->aspm_level[1] << 2));
	पूर्ण
पूर्ण

अटल व्योम rtsx_manage_ocp(काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित SUPPORT_OCP
	अगर (!chip->ocp_पूर्णांक)
		वापस;

	rtsx_पढ़ो_रेजिस्टर(chip, OCPSTAT, &chip->ocp_stat);

	अगर (chip->card_exist & SD_CARD)
		sd_घातer_off_card3v3(chip);
	अन्यथा अगर (chip->card_exist & MS_CARD)
		ms_घातer_off_card3v3(chip);
	अन्यथा अगर (chip->card_exist & XD_CARD)
		xd_घातer_off_card3v3(chip);

	chip->ocp_पूर्णांक = 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम rtsx_manage_sd_lock(काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित SUPPORT_SD_LOCK
	काष्ठा sd_info *sd_card = &chip->sd_card;
	u8 val;

	अगर (!sd_card->sd_erase_status)
		वापस;

	अगर (chip->card_exist & SD_CARD) अणु
		rtsx_पढ़ो_रेजिस्टर(chip, 0xFD30, &val);
		अगर (val & 0x02) अणु
			sd_card->sd_erase_status = SD_NOT_ERASE;
			sd_card->sd_lock_notअगरy = 1;
			chip->need_reinit |= SD_CARD;
		पूर्ण
	पूर्ण अन्यथा अणु
		sd_card->sd_erase_status = SD_NOT_ERASE;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल bool rtsx_is_ss_allowed(काष्ठा rtsx_chip *chip)
अणु
	u32 val;

	अगर (!chip->ss_en || CHECK_PID(chip, 0x5288))
		वापस false;

	अगर (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNORED(chip)) अणु
		rtsx_पढ़ो_cfg_dw(chip, 1, 0x04, &val);
		अगर (val & 0x07)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम rtsx_manage_ss(काष्ठा rtsx_chip *chip)
अणु
	अगर (!rtsx_is_ss_allowed(chip) || chip->sd_io)
		वापस;

	अगर (rtsx_get_stat(chip) != RTSX_STAT_IDLE) अणु
		chip->ss_counter = 0;
		वापस;
	पूर्ण

	अगर (chip->ss_counter < (chip->ss_idle_period / POLLING_INTERVAL))
		chip->ss_counter++;
	अन्यथा
		rtsx_exclusive_enter_ss(chip);
पूर्ण

अटल व्योम rtsx_manage_aspm(काष्ठा rtsx_chip *chip)
अणु
	u8 data;

	अगर (!CHECK_PID(chip, 0x5208))
		वापस;

	rtsx_monitor_aspm_config(chip);

#अगर_घोषित SUPPORT_SDIO_ASPM
	अगर (!CHK_SDIO_EXIST(chip) || CHK_SDIO_IGNORED(chip) ||
	    !chip->aspm_l0s_l1_en || !chip->dynamic_aspm)
		वापस;

	अगर (chip->sd_io) अणु
		dynamic_configure_sdio_aspm(chip);
		वापस;
	पूर्ण

	अगर (chip->sdio_aspm)
		वापस;

	dev_dbg(rtsx_dev(chip), "SDIO enter ASPM!\n");
	data = 0x30 | (chip->aspm_level[1] << 2);
	rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL, 0xFC, data);
	chip->sdio_aspm = 1;
#पूर्ण_अगर
पूर्ण

अटल व्योम rtsx_manage_idle(काष्ठा rtsx_chip *chip)
अणु
	अगर (chip->idle_counter < IDLE_MAX_COUNT) अणु
		chip->idle_counter++;
		वापस;
	पूर्ण

	अगर (rtsx_get_stat(chip) == RTSX_STAT_IDLE)
		वापस;

	dev_dbg(rtsx_dev(chip), "Idle state!\n");
	rtsx_set_stat(chip, RTSX_STAT_IDLE);

#अगर !defined(LED_AUTO_BLINK) && defined(REGULAR_BLINK)
	chip->led_toggle_counter = 0;
#पूर्ण_अगर
	rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);

	turn_off_led(chip, LED_GPIO);

	अगर (chip->स्वतः_घातer_करोwn && !chip->card_पढ़ोy && !chip->sd_io)
		rtsx_क्रमce_घातer_करोwn(chip, SSC_PDCTL | OC_PDCTL);
पूर्ण

अटल व्योम rtsx_manage_2lun_mode(काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित SUPPORT_OCP
	u8 sd_oc, ms_oc;

	sd_oc = chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER);
	ms_oc = chip->ocp_stat & (MS_OC_NOW | MS_OC_EVER);

	अगर (sd_oc || ms_oc)
		dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
			chip->ocp_stat);

	अगर (sd_oc && (chip->card_exist & SD_CARD)) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SD_OUTPUT_EN, 0);
		card_घातer_off(chip, SD_CARD);
		chip->card_fail |= SD_CARD;
	पूर्ण

	अगर (ms_oc && (chip->card_exist & MS_CARD)) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, MS_OUTPUT_EN, 0);
		card_घातer_off(chip, MS_CARD);
		chip->card_fail |= MS_CARD;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम rtsx_manage_1lun_mode(काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित SUPPORT_OCP
	अगर (!(chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER)))
		वापस;

	dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
		chip->ocp_stat);

	अगर (chip->card_exist & SD_CARD) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SD_OUTPUT_EN, 0);
		chip->card_fail |= SD_CARD;
	पूर्ण अन्यथा अगर (chip->card_exist & MS_CARD) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, MS_OUTPUT_EN, 0);
		chip->card_fail |= MS_CARD;
	पूर्ण अन्यथा अगर (chip->card_exist & XD_CARD) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, XD_OUTPUT_EN, 0);
		chip->card_fail |= XD_CARD;
	पूर्ण
	card_घातer_off(chip, SD_CARD);
#पूर्ण_अगर
पूर्ण

अटल व्योम rtsx_delink_stage1(काष्ठा rtsx_chip *chip, पूर्णांक enter_L1,
			       पूर्णांक stage3_cnt)
अणु
	u8 val;

	rtsx_set_stat(chip, RTSX_STAT_DELINK);

	अगर (chip->asic_code && CHECK_PID(chip, 0x5208))
		rtsx_set_phy_reg_bit(chip, 0x1C, 2);

	अगर (chip->card_exist)
		dev_dbg(rtsx_dev(chip), "False card inserted, do force delink\n");
	अन्यथा
		dev_dbg(rtsx_dev(chip), "No card inserted, do delink\n");

	अगर (enter_L1)
		rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0x03, 1);

	अगर (chip->card_exist)
		val = 0x02;
	अन्यथा
		val = 0x0A;

	rtsx_ग_लिखो_रेजिस्टर(chip, CHANGE_LINK_STATE, val, val);

	अगर (enter_L1)
		rtsx_enter_L1(chip);

	अगर (chip->card_exist)
		chip->स्वतः_delink_cnt = stage3_cnt + 1;
पूर्ण

अटल व्योम rtsx_delink_stage(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक delink_stage1_cnt, delink_stage2_cnt, delink_stage3_cnt;
	पूर्णांक enter_L1;

	अगर (!chip->स्वतः_delink_en || !chip->स्वतः_delink_allowed ||
	    chip->card_पढ़ोy || chip->card_ejected || chip->sd_io) अणु
		chip->स्वतः_delink_cnt = 0;
		वापस;
	पूर्ण

	enter_L1 = chip->स्वतः_delink_in_L1 &&
		(chip->aspm_l0s_l1_en || chip->ss_en);

	delink_stage1_cnt = chip->delink_stage1_step;
	delink_stage2_cnt = delink_stage1_cnt + chip->delink_stage2_step;
	delink_stage3_cnt = delink_stage2_cnt + chip->delink_stage3_step;

	अगर (chip->स्वतः_delink_cnt > delink_stage3_cnt)
		वापस;

	अगर (chip->स्वतः_delink_cnt == delink_stage1_cnt)
		rtsx_delink_stage1(chip, enter_L1, delink_stage3_cnt);

	अगर (chip->स्वतः_delink_cnt == delink_stage2_cnt) अणु
		dev_dbg(rtsx_dev(chip), "Try to do force delink\n");

		अगर (enter_L1)
			rtsx_निकास_L1(chip);

		अगर (chip->asic_code && CHECK_PID(chip, 0x5208))
			rtsx_set_phy_reg_bit(chip, 0x1C, 2);

		rtsx_ग_लिखो_रेजिस्टर(chip, CHANGE_LINK_STATE, 0x0A, 0x0A);
	पूर्ण

	chip->स्वतः_delink_cnt++;
पूर्ण

व्योम rtsx_polling_func(काष्ठा rtsx_chip *chip)
अणु
	अगर (rtsx_chk_stat(chip, RTSX_STAT_SUSPEND))
		वापस;

	अगर (rtsx_chk_stat(chip, RTSX_STAT_DELINK))
		जाओ delink_stage;

	अगर (chip->polling_config) अणु
		u8 val;

		rtsx_पढ़ो_config_byte(chip, 0, &val);
	पूर्ण

	अगर (rtsx_chk_stat(chip, RTSX_STAT_SS))
		वापस;

	rtsx_manage_ocp(chip);

	rtsx_manage_sd_lock(chip);

	rtsx_init_cards(chip);

	rtsx_manage_ss(chip);

	rtsx_manage_aspm(chip);

	rtsx_manage_idle(chip);

	चयन (rtsx_get_stat(chip)) अणु
	हाल RTSX_STAT_RUN:
#अगर !defined(LED_AUTO_BLINK) && defined(REGULAR_BLINK)
		rtsx_blink_led(chip);
#पूर्ण_अगर
		करो_reमुख्यing_work(chip);
		अवरोध;

	हाल RTSX_STAT_IDLE:
		अगर (chip->sd_io && !chip->sd_पूर्णांक)
			try_to_चयन_sdio_ctrl(chip);

		rtsx_enable_aspm(chip);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN))
		rtsx_manage_2lun_mode(chip);
	अन्यथा
		rtsx_manage_1lun_mode(chip);

delink_stage:
	rtsx_delink_stage(chip);
पूर्ण

/**
 * rtsx_stop_cmd - stop command transfer and DMA transfer
 * @chip: Realtek's card पढ़ोer chip
 * @card: flash card type
 *
 * Stop command transfer and DMA transfer.
 * This function is called in error handler.
 */
व्योम rtsx_stop_cmd(काष्ठा rtsx_chip *chip, पूर्णांक card)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= 8; i++) अणु
		पूर्णांक addr = RTSX_HCBAR + i * 4;
		u32 reg;

		reg = rtsx_पढ़ोl(chip, addr);
		dev_dbg(rtsx_dev(chip), "BAR (0x%02x): 0x%08x\n", addr, reg);
	पूर्ण
	rtsx_ग_लिखोl(chip, RTSX_HCBCTLR, STOP_CMD);
	rtsx_ग_लिखोl(chip, RTSX_HDBCTLR, STOP_DMA);

	क्रम (i = 0; i < 16; i++) अणु
		u16 addr = 0xFE20 + (u16)i;
		u8 val;

		rtsx_पढ़ो_रेजिस्टर(chip, addr, &val);
		dev_dbg(rtsx_dev(chip), "0x%04X: 0x%02x\n", addr, val);
	पूर्ण

	rtsx_ग_लिखो_रेजिस्टर(chip, DMACTL, 0x80, 0x80);
	rtsx_ग_लिखो_रेजिस्टर(chip, RBCTL, 0x80, 0x80);
पूर्ण

#घोषणा MAX_RW_REG_CNT		1024

पूर्णांक rtsx_ग_लिखो_रेजिस्टर(काष्ठा rtsx_chip *chip, u16 addr, u8 mask, u8 data)
अणु
	पूर्णांक i;
	u32 val = 3 << 30;

	val |= (u32)(addr & 0x3FFF) << 16;
	val |= (u32)mask << 8;
	val |= (u32)data;

	rtsx_ग_लिखोl(chip, RTSX_HAIMR, val);

	क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
		val = rtsx_पढ़ोl(chip, RTSX_HAIMR);
		अगर ((val & BIT(31)) == 0) अणु
			अगर (data != (u8)val)
				वापस STATUS_FAIL;

			वापस STATUS_SUCCESS;
		पूर्ण
	पूर्ण

	वापस STATUS_TIMEDOUT;
पूर्ण

पूर्णांक rtsx_पढ़ो_रेजिस्टर(काष्ठा rtsx_chip *chip, u16 addr, u8 *data)
अणु
	u32 val = 2 << 30;
	पूर्णांक i;

	अगर (data)
		*data = 0;

	val |= (u32)(addr & 0x3FFF) << 16;

	rtsx_ग_लिखोl(chip, RTSX_HAIMR, val);

	क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
		val = rtsx_पढ़ोl(chip, RTSX_HAIMR);
		अगर ((val & BIT(31)) == 0)
			अवरोध;
	पूर्ण

	अगर (i >= MAX_RW_REG_CNT)
		वापस STATUS_TIMEDOUT;

	अगर (data)
		*data = (u8)(val & 0xFF);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_ग_लिखो_cfg_dw(काष्ठा rtsx_chip *chip, u8 func_no, u16 addr, u32 mask,
		      u32 val)
अणु
	पूर्णांक retval;
	u8 mode = 0, पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (mask & 0xFF) अणु
			retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGDATA0 + i,
						     0xFF,
						     (u8)(val & mask & 0xFF));
			अगर (retval)
				वापस retval;
			mode |= (1 << i);
		पूर्ण
		mask >>= 8;
		val >>= 8;
	पूर्ण

	अगर (mode) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGADDR0, 0xFF, (u8)addr);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGADDR1, 0xFF,
					     (u8)(addr >> 8));
		अगर (retval)
			वापस retval;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGRWCTL, 0xFF,
					     0x80 | mode |
					     ((func_no & 0x03) << 4));
		अगर (retval)
			वापस retval;

		क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
			retval = rtsx_पढ़ो_रेजिस्टर(chip, CFGRWCTL, &पंचांगp);
			अगर (retval)
				वापस retval;
			अगर ((पंचांगp & 0x80) == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_पढ़ो_cfg_dw(काष्ठा rtsx_chip *chip, u8 func_no, u16 addr, u32 *val)
अणु
	पूर्णांक retval;
	पूर्णांक i;
	u8 पंचांगp;
	u32 data = 0;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGADDR0, 0xFF, (u8)addr);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGADDR1, 0xFF, (u8)(addr >> 8));
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CFGRWCTL, 0xFF,
				     0x80 | ((func_no & 0x03) << 4));
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, CFGRWCTL, &पंचांगp);
		अगर (retval)
			वापस retval;
		अगर ((पंचांगp & 0x80) == 0)
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, CFGDATA0 + i, &पंचांगp);
		अगर (retval)
			वापस retval;
		data |= (u32)पंचांगp << (i * 8);
	पूर्ण

	अगर (val)
		*val = data;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_ग_लिखो_cfg_seq(काष्ठा rtsx_chip *chip, u8 func, u16 addr, u8 *buf,
		       पूर्णांक len)
अणु
	u32 *data, *mask;
	u16 offset = addr % 4;
	u16 aligned_addr = addr - offset;
	पूर्णांक dw_len, i, j;
	पूर्णांक retval;
	माप_प्रकार size;

	अगर (!buf)
		वापस STATUS_NOMEM;

	अगर ((len + offset) % 4)
		dw_len = (len + offset) / 4 + 1;
	अन्यथा
		dw_len = (len + offset) / 4;

	dev_dbg(rtsx_dev(chip), "dw_len = %d\n", dw_len);

	size = array_size(dw_len, 4);
	data = vzalloc(size);
	अगर (!data)
		वापस STATUS_NOMEM;

	mask = vzalloc(size);
	अगर (!mask) अणु
		vमुक्त(data);
		वापस STATUS_NOMEM;
	पूर्ण

	j = 0;
	क्रम (i = 0; i < len; i++) अणु
		mask[j] |= 0xFF << (offset * 8);
		data[j] |= buf[i] << (offset * 8);
		अगर (++offset == 4) अणु
			j++;
			offset = 0;
		पूर्ण
	पूर्ण

	prपूर्णांक_hex_dump_bytes(KBUILD_MODNAME ": ", DUMP_PREFIX_NONE, mask, size);
	prपूर्णांक_hex_dump_bytes(KBUILD_MODNAME ": ", DUMP_PREFIX_NONE, data, size);

	क्रम (i = 0; i < dw_len; i++) अणु
		retval = rtsx_ग_लिखो_cfg_dw(chip, func, aligned_addr + i * 4,
					   mask[i], data[i]);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(data);
			vमुक्त(mask);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	vमुक्त(data);
	vमुक्त(mask);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_पढ़ो_cfg_seq(काष्ठा rtsx_chip *chip, u8 func, u16 addr, u8 *buf,
		      पूर्णांक len)
अणु
	u32 *data;
	u16 offset = addr % 4;
	u16 aligned_addr = addr - offset;
	पूर्णांक dw_len, i, j;
	पूर्णांक retval;

	अगर ((len + offset) % 4)
		dw_len = (len + offset) / 4 + 1;
	अन्यथा
		dw_len = (len + offset) / 4;

	dev_dbg(rtsx_dev(chip), "dw_len = %d\n", dw_len);

	data = vदो_स्मृति(array_size(dw_len, 4));
	अगर (!data)
		वापस STATUS_NOMEM;

	क्रम (i = 0; i < dw_len; i++) अणु
		retval = rtsx_पढ़ो_cfg_dw(chip, func, aligned_addr + i * 4,
					  data + i);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(data);
			वापस STATUS_FAIL;
		पूर्ण
	पूर्ण

	अगर (buf) अणु
		j = 0;

		क्रम (i = 0; i < len; i++) अणु
			buf[i] = (u8)(data[j] >> (offset * 8));
			अगर (++offset == 4) अणु
				j++;
				offset = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	vमुक्त(data);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_chip *chip, u8 addr, u16 val)
अणु
	पूर्णांक retval;
	bool finished = false;
	पूर्णांक i;
	u8 पंचांगp;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PHYDATA0, 0xFF, (u8)val);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PHYDATA1, 0xFF, (u8)(val >> 8));
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PHYADDR, 0xFF, addr);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PHYRWCTL, 0xFF, 0x81);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < 100000; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, PHYRWCTL, &पंचांगp);
		अगर (retval)
			वापस retval;
		अगर (!(पंचांगp & 0x80)) अणु
			finished = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!finished)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_पढ़ो_phy_रेजिस्टर(काष्ठा rtsx_chip *chip, u8 addr, u16 *val)
अणु
	पूर्णांक retval;
	bool finished = false;
	पूर्णांक i;
	u16 data = 0;
	u8 पंचांगp;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PHYADDR, 0xFF, addr);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, PHYRWCTL, 0xFF, 0x80);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < 100000; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, PHYRWCTL, &पंचांगp);
		अगर (retval)
			वापस retval;
		अगर (!(पंचांगp & 0x80)) अणु
			finished = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!finished)
		वापस STATUS_FAIL;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, PHYDATA0, &पंचांगp);
	अगर (retval)
		वापस retval;
	data = पंचांगp;
	retval = rtsx_पढ़ो_रेजिस्टर(chip, PHYDATA1, &पंचांगp);
	अगर (retval)
		वापस retval;
	data |= (u16)पंचांगp << 8;

	अगर (val)
		*val = data;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_पढ़ो_efuse(काष्ठा rtsx_chip *chip, u8 addr, u8 *val)
अणु
	पूर्णांक retval;
	पूर्णांक i;
	u8 data = 0;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, EFUSE_CTRL, 0xFF, 0x80 | addr);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < 100; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, EFUSE_CTRL, &data);
		अगर (retval)
			वापस retval;
		अगर (!(data & 0x80))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (data & 0x80)
		वापस STATUS_TIMEDOUT;

	retval = rtsx_पढ़ो_रेजिस्टर(chip, EFUSE_DATA, &data);
	अगर (retval)
		वापस retval;
	अगर (val)
		*val = data;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_ग_लिखो_efuse(काष्ठा rtsx_chip *chip, u8 addr, u8 val)
अणु
	पूर्णांक retval;
	पूर्णांक i, j;
	u8 data = 0, पंचांगp = 0xFF;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (val & (u8)(1 << i))
			जारी;

		पंचांगp &= (~(u8)(1 << i));
		dev_dbg(rtsx_dev(chip), "Write 0x%x to 0x%x\n", पंचांगp, addr);

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, EFUSE_DATA, 0xFF, पंचांगp);
		अगर (retval)
			वापस retval;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, EFUSE_CTRL, 0xFF,
					     0xA0 | addr);
		अगर (retval)
			वापस retval;

		क्रम (j = 0; j < 100; j++) अणु
			retval = rtsx_पढ़ो_रेजिस्टर(chip, EFUSE_CTRL, &data);
			अगर (retval)
				वापस retval;
			अगर (!(data & 0x80))
				अवरोध;
			रुको_समयout(3);
		पूर्ण

		अगर (data & 0x80)
			वापस STATUS_TIMEDOUT;

		रुको_समयout(5);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_clr_phy_reg_bit(काष्ठा rtsx_chip *chip, u8 reg, u8 bit)
अणु
	पूर्णांक retval;
	u16 value;

	retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, reg, &value);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर (value & (1 << bit)) अणु
		value &= ~(1 << bit);
		retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, reg, value);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_set_phy_reg_bit(काष्ठा rtsx_chip *chip, u8 reg, u8 bit)
अणु
	पूर्णांक retval;
	u16 value;

	retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, reg, &value);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	अगर ((value & (1 << bit)) == 0) अणु
		value |= (1 << bit);
		retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, reg, value);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल व्योम rtsx_handle_pm_dstate(काष्ठा rtsx_chip *chip, u8 dstate)
अणु
	u32 ulपंचांगp;

	dev_dbg(rtsx_dev(chip), "%04x set pm_dstate to %d\n",
		chip->product_id, dstate);

	अगर (CHK_SDIO_EXIST(chip)) अणु
		u8 func_no;

		अगर (CHECK_PID(chip, 0x5288))
			func_no = 2;
		अन्यथा
			func_no = 1;

		rtsx_पढ़ो_cfg_dw(chip, func_no, 0x84, &ulपंचांगp);
		dev_dbg(rtsx_dev(chip), "pm_dstate of function %d: 0x%x\n",
			(पूर्णांक)func_no, ulपंचांगp);
		rtsx_ग_लिखो_cfg_dw(chip, func_no, 0x84, 0xFF, dstate);
	पूर्ण

	rtsx_ग_लिखो_config_byte(chip, 0x44, dstate);
	rtsx_ग_लिखो_config_byte(chip, 0x45, 0);
पूर्ण

व्योम rtsx_enter_L1(काष्ठा rtsx_chip *chip)
अणु
	rtsx_handle_pm_dstate(chip, 2);
पूर्ण

व्योम rtsx_निकास_L1(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखो_config_byte(chip, 0x44, 0);
	rtsx_ग_लिखो_config_byte(chip, 0x45, 0);
पूर्ण

व्योम rtsx_enter_ss(काष्ठा rtsx_chip *chip)
अणु
	dev_dbg(rtsx_dev(chip), "Enter Selective Suspend State!\n");

	rtsx_ग_लिखो_रेजिस्टर(chip, IRQSTAT0, LINK_RDY_INT, LINK_RDY_INT);

	अगर (chip->घातer_करोwn_in_ss) अणु
		rtsx_घातer_off_card(chip);
		rtsx_क्रमce_घातer_करोwn(chip, SSC_PDCTL | OC_PDCTL);
	पूर्ण

	अगर (CHK_SDIO_EXIST(chip))
		rtsx_ग_लिखो_cfg_dw(chip, CHECK_PID(chip, 0x5288) ? 2 : 1,
				  0xC0, 0xFF00, 0x0100);

	अगर (chip->स्वतः_delink_en) अणु
		rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0x01, 0x01);
	पूर्ण अन्यथा अणु
		अगर (!chip->phy_debug_mode) अणु
			u32 पंचांगp;

			पंचांगp = rtsx_पढ़ोl(chip, RTSX_BIER);
			पंचांगp |= CARD_INT;
			rtsx_ग_लिखोl(chip, RTSX_BIER, पंचांगp);
		पूर्ण

		rtsx_ग_लिखो_रेजिस्टर(chip, CHANGE_LINK_STATE, 0x02, 0);
	पूर्ण

	rtsx_enter_L1(chip);

	RTSX_CLR_DELINK(chip);
	rtsx_set_stat(chip, RTSX_STAT_SS);
पूर्ण

व्योम rtsx_निकास_ss(काष्ठा rtsx_chip *chip)
अणु
	dev_dbg(rtsx_dev(chip), "Exit Selective Suspend State!\n");

	rtsx_निकास_L1(chip);

	अगर (chip->घातer_करोwn_in_ss) अणु
		rtsx_क्रमce_घातer_on(chip, SSC_PDCTL | OC_PDCTL);
		udelay(1000);
	पूर्ण

	अगर (RTSX_TST_DELINK(chip)) अणु
		chip->need_reinit = SD_CARD | MS_CARD | XD_CARD;
		rtsx_reinit_cards(chip, 1);
		RTSX_CLR_DELINK(chip);
	पूर्ण अन्यथा अगर (chip->घातer_करोwn_in_ss) अणु
		chip->need_reinit = SD_CARD | MS_CARD | XD_CARD;
		rtsx_reinit_cards(chip, 0);
	पूर्ण
पूर्ण

पूर्णांक rtsx_pre_handle_पूर्णांकerrupt(काष्ठा rtsx_chip *chip)
अणु
	u32 status, पूर्णांक_enable;
	bool निकास_ss = false;
#अगर_घोषित SUPPORT_OCP
	u32 ocp_पूर्णांक = 0;

	ocp_पूर्णांक = OC_INT;
#पूर्ण_अगर

	अगर (chip->ss_en) अणु
		chip->ss_counter = 0;
		अगर (rtsx_get_stat(chip) == RTSX_STAT_SS) अणु
			निकास_ss = true;
			rtsx_निकास_L1(chip);
			rtsx_set_stat(chip, RTSX_STAT_RUN);
		पूर्ण
	पूर्ण

	पूर्णांक_enable = rtsx_पढ़ोl(chip, RTSX_BIER);
	chip->पूर्णांक_reg = rtsx_पढ़ोl(chip, RTSX_BIPR);

	अगर (((chip->पूर्णांक_reg & पूर्णांक_enable) == 0) ||
	    (chip->पूर्णांक_reg == 0xFFFFFFFF))
		वापस STATUS_FAIL;

	status = chip->पूर्णांक_reg &= (पूर्णांक_enable | 0x7FFFFF);

	अगर (status & CARD_INT) अणु
		chip->स्वतः_delink_cnt = 0;

		अगर (status & SD_INT) अणु
			अगर (status & SD_EXIST) अणु
				set_bit(SD_NR, &chip->need_reset);
			पूर्ण अन्यथा अणु
				set_bit(SD_NR, &chip->need_release);
				chip->sd_reset_counter = 0;
				chip->sd_show_cnt = 0;
				clear_bit(SD_NR, &chip->need_reset);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * If multi-luns, it's possible that
			 * when plugging/unplugging one card
			 * there is another card which still
			 * exists in the slot. In this हाल,
			 * all existed cards should be reset.
			 */
			अगर (निकास_ss && (status & SD_EXIST))
				set_bit(SD_NR, &chip->need_reinit);
		पूर्ण
		अगर (!CHECK_PID(chip, 0x5288) || CHECK_BARO_PKG(chip, QFN)) अणु
			अगर (status & XD_INT) अणु
				अगर (status & XD_EXIST) अणु
					set_bit(XD_NR, &chip->need_reset);
				पूर्ण अन्यथा अणु
					set_bit(XD_NR, &chip->need_release);
					chip->xd_reset_counter = 0;
					chip->xd_show_cnt = 0;
					clear_bit(XD_NR, &chip->need_reset);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (निकास_ss && (status & XD_EXIST))
					set_bit(XD_NR, &chip->need_reinit);
			पूर्ण
		पूर्ण
		अगर (status & MS_INT) अणु
			अगर (status & MS_EXIST) अणु
				set_bit(MS_NR, &chip->need_reset);
			पूर्ण अन्यथा अणु
				set_bit(MS_NR, &chip->need_release);
				chip->ms_reset_counter = 0;
				chip->ms_show_cnt = 0;
				clear_bit(MS_NR, &chip->need_reset);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (निकास_ss && (status & MS_EXIST))
				set_bit(MS_NR, &chip->need_reinit);
		पूर्ण
	पूर्ण

#अगर_घोषित SUPPORT_OCP
	chip->ocp_पूर्णांक = ocp_पूर्णांक & status;
#पूर्ण_अगर

	अगर (chip->sd_io && (chip->पूर्णांक_reg & DATA_DONE_INT))
		chip->पूर्णांक_reg &= ~(u32)DATA_DONE_INT;

	वापस STATUS_SUCCESS;
पूर्ण

व्योम rtsx_करो_beक्रमe_घातer_करोwn(काष्ठा rtsx_chip *chip, पूर्णांक pm_stat)
अणु
	पूर्णांक retval;

	dev_dbg(rtsx_dev(chip), "%s, pm_stat = %d\n", __func__, pm_stat);

	rtsx_set_stat(chip, RTSX_STAT_SUSPEND);

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS)
		वापस;

	rtsx_release_cards(chip);
	rtsx_disable_bus_पूर्णांक(chip);
	turn_off_led(chip, LED_GPIO);

#अगर_घोषित HW_AUTO_SWITCH_SD_BUS
	अगर (chip->sd_io) अणु
		chip->sdio_in_अक्षरge = 1;
		अगर (CHECK_PID(chip, 0x5208)) अणु
			rtsx_ग_लिखो_रेजिस्टर(chip, TLPTISTAT, 0x08, 0x08);
			/* Enable sdio_bus_स्वतः_चयन */
			rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE70, 0x80, 0x80);
		पूर्ण अन्यथा अगर (CHECK_PID(chip, 0x5288)) अणु
			rtsx_ग_लिखो_रेजिस्टर(chip, TLPTISTAT, 0x08, 0x08);
			/* Enable sdio_bus_स्वतः_चयन */
			rtsx_ग_लिखो_रेजिस्टर(chip, 0xFE5A, 0x08, 0x08);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (CHECK_PID(chip, 0x5208) && (chip->ic_version >= IC_VER_D)) अणु
		/* u_क्रमce_clkreq_0 */
		rtsx_ग_लिखो_रेजिस्टर(chip, PETXCFG, 0x08, 0x08);
	पूर्ण

	अगर (pm_stat == PM_S1) अणु
		dev_dbg(rtsx_dev(chip), "Host enter S1\n");
		rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0x03,
				    HOST_ENTER_S1);
	पूर्ण अन्यथा अगर (pm_stat == PM_S3) अणु
		अगर (chip->s3_pwr_off_delay > 0)
			रुको_समयout(chip->s3_pwr_off_delay);

		dev_dbg(rtsx_dev(chip), "Host enter S3\n");
		rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0x03,
				    HOST_ENTER_S3);
	पूर्ण

	अगर (chip->करो_delink_beक्रमe_घातer_करोwn && chip->स्वतः_delink_en)
		rtsx_ग_लिखो_रेजिस्टर(chip, CHANGE_LINK_STATE, 0x02, 2);

	rtsx_क्रमce_घातer_करोwn(chip, SSC_PDCTL | OC_PDCTL);

	chip->cur_clk = 0;
	chip->cur_card = 0;
	chip->card_exist = 0;
पूर्ण

व्योम rtsx_enable_aspm(काष्ठा rtsx_chip *chip)
अणु
	अगर (chip->aspm_l0s_l1_en && chip->dynamic_aspm && !chip->aspm_enabled) अणु
		dev_dbg(rtsx_dev(chip), "Try to enable ASPM\n");
		chip->aspm_enabled = 1;

		अगर (chip->asic_code && CHECK_PID(chip, 0x5208))
			rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x07, 0);
		अगर (CHECK_PID(chip, 0x5208)) अणु
			rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL, 0xF3,
					    0x30 | chip->aspm_level[0]);
		पूर्ण अन्यथा अणु
			rtsx_ग_लिखो_config_byte(chip, LCTLR,
					       chip->aspm_l0s_l1_en);
		पूर्ण

		अगर (CHK_SDIO_EXIST(chip)) अणु
			u16 val = chip->aspm_l0s_l1_en | 0x0100;

			rtsx_ग_लिखो_cfg_dw(chip, CHECK_PID(chip, 0x5288) ? 2 : 1,
					  0xC0, 0xFFF, val);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtsx_disable_aspm(काष्ठा rtsx_chip *chip)
अणु
	अगर (CHECK_PID(chip, 0x5208))
		rtsx_monitor_aspm_config(chip);

	अगर (chip->aspm_l0s_l1_en && chip->dynamic_aspm && chip->aspm_enabled) अणु
		dev_dbg(rtsx_dev(chip), "Try to disable ASPM\n");
		chip->aspm_enabled = 0;

		अगर (chip->asic_code && CHECK_PID(chip, 0x5208))
			rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x07, 0x0129);
		अगर (CHECK_PID(chip, 0x5208))
			rtsx_ग_लिखो_रेजिस्टर(chip, ASPM_FORCE_CTL,
					    0xF3, 0x30);
		अन्यथा
			rtsx_ग_लिखो_config_byte(chip, LCTLR, 0x00);

		रुको_समयout(1);
	पूर्ण
पूर्ण

पूर्णांक rtsx_पढ़ो_ppbuf(काष्ठा rtsx_chip *chip, u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक retval;
	पूर्णांक i, j;
	u16 reg_addr;
	u8 *ptr;

	अगर (!buf)
		वापस STATUS_ERROR;

	ptr = buf;
	reg_addr = PPBUF_BASE2;
	क्रम (i = 0; i < buf_len / 256; i++) अणु
		rtsx_init_cmd(chip);

		क्रम (j = 0; j < 256; j++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr++, 0, 0);

		retval = rtsx_send_cmd(chip, 0, 250);
		अगर (retval < 0)
			वापस STATUS_FAIL;

		स_नकल(ptr, rtsx_get_cmd_data(chip), 256);
		ptr += 256;
	पूर्ण

	अगर (buf_len % 256) अणु
		rtsx_init_cmd(chip);

		क्रम (j = 0; j < buf_len % 256; j++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr++, 0, 0);

		retval = rtsx_send_cmd(chip, 0, 250);
		अगर (retval < 0)
			वापस STATUS_FAIL;
	पूर्ण

	स_नकल(ptr, rtsx_get_cmd_data(chip), buf_len % 256);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_ग_लिखो_ppbuf(काष्ठा rtsx_chip *chip, u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक retval;
	पूर्णांक i, j;
	u16 reg_addr;
	u8 *ptr;

	अगर (!buf)
		वापस STATUS_ERROR;

	ptr = buf;
	reg_addr = PPBUF_BASE2;
	क्रम (i = 0; i < buf_len / 256; i++) अणु
		rtsx_init_cmd(chip);

		क्रम (j = 0; j < 256; j++) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, reg_addr++, 0xFF,
				     *ptr);
			ptr++;
		पूर्ण

		retval = rtsx_send_cmd(chip, 0, 250);
		अगर (retval < 0)
			वापस STATUS_FAIL;
	पूर्ण

	अगर (buf_len % 256) अणु
		rtsx_init_cmd(chip);

		क्रम (j = 0; j < buf_len % 256; j++) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, reg_addr++, 0xFF,
				     *ptr);
			ptr++;
		पूर्ण

		retval = rtsx_send_cmd(chip, 0, 250);
		अगर (retval < 0)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_check_chip_exist(काष्ठा rtsx_chip *chip)
अणु
	अगर (rtsx_पढ़ोl(chip, 0) == 0xFFFFFFFF)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_क्रमce_घातer_on(काष्ठा rtsx_chip *chip, u8 ctl)
अणु
	पूर्णांक retval;
	u8 mask = 0;

	अगर (ctl & SSC_PDCTL)
		mask |= SSC_POWER_DOWN;

#अगर_घोषित SUPPORT_OCP
	अगर (ctl & OC_PDCTL) अणु
		mask |= SD_OC_POWER_DOWN;
		अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN))
			mask |= MS_OC_POWER_DOWN;
	पूर्ण
#पूर्ण_अगर

	अगर (mask) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPDCTL, mask, 0);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		अगर (CHECK_PID(chip, 0x5288))
			रुको_समयout(200);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक rtsx_क्रमce_घातer_करोwn(काष्ठा rtsx_chip *chip, u8 ctl)
अणु
	पूर्णांक retval;
	u8 mask = 0, val = 0;

	अगर (ctl & SSC_PDCTL)
		mask |= SSC_POWER_DOWN;

#अगर_घोषित SUPPORT_OCP
	अगर (ctl & OC_PDCTL) अणु
		mask |= SD_OC_POWER_DOWN;
		अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN))
			mask |= MS_OC_POWER_DOWN;
	पूर्ण
#पूर्ण_अगर

	अगर (mask) अणु
		val = mask;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, FPDCTL, mask, val);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण
