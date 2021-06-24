<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 *   Roger Tseng <rogerable@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtsx_pci.h>

#समावेश "rtsx_pcr.h"

अटल u8 rtl8411_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, SYS_VER, &val);
	वापस val & 0x0F;
पूर्ण

अटल पूर्णांक rtl8411b_is_qfn48(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val = 0;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTL8411B_PACKAGE_MODE, &val);

	अगर (val & 0x2)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम rtl8411_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg1 = 0;
	u8 reg3 = 0;

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg1);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg1);

	अगर (!rtsx_venकरोr_setting_valid(reg1))
		वापस;

	pcr->aspm_en = rtsx_reg_to_aspm(reg1);
	pcr->sd30_drive_sel_1v8 =
		map_sd_drive(rtsx_reg_to_sd30_drive_sel_1v8(reg1));
	pcr->card_drive_sel &= 0x3F;
	pcr->card_drive_sel |= rtsx_reg_to_card_drive_sel(reg1);

	pci_पढ़ो_config_byte(pdev, PCR_SETTING_REG3, &reg3);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG3, reg3);
	pcr->sd30_drive_sel_3v3 = rtl8411_reg_to_sd30_drive_sel_3v3(reg3);
पूर्ण

अटल व्योम rtl8411b_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg = 0;

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	अगर (!rtsx_venकरोr_setting_valid(reg))
		वापस;

	pcr->aspm_en = rtsx_reg_to_aspm(reg);
	pcr->sd30_drive_sel_1v8 =
		map_sd_drive(rtsx_reg_to_sd30_drive_sel_1v8(reg));
	pcr->sd30_drive_sel_3v3 =
		map_sd_drive(rtl8411b_reg_to_sd30_drive_sel_3v3(reg));
पूर्ण

अटल व्योम rtl8411_क्रमce_घातer_करोwn(काष्ठा rtsx_pcr *pcr, u8 pm_state)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, 0x07, 0x07);
पूर्ण

अटल पूर्णांक rtl8411_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_DRIVE_SEL,
			0xFF, pcr->sd30_drive_sel_3v3);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CD_PAD_CTL,
			CD_DISABLE_MASK | CD_AUTO_DISABLE, CD_ENABLE);

	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rtl8411b_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_init_cmd(pcr);

	अगर (rtl8411b_is_qfn48(pcr))
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				CARD_PULL_CTL3, 0xFF, 0xF5);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_DRIVE_SEL,
			0xFF, pcr->sd30_drive_sel_3v3);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CD_PAD_CTL,
			CD_DISABLE_MASK | CD_AUTO_DISABLE, CD_ENABLE);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, FUNC_FORCE_CTL,
			0x06, 0x00);

	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rtl8411_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_GPIO, 0x01, 0x00);
पूर्ण

अटल पूर्णांक rtl8411_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_GPIO, 0x01, 0x01);
पूर्ण

अटल पूर्णांक rtl8411_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_AUTO_BLINK, 0xFF, 0x0D);
पूर्ण

अटल पूर्णांक rtl8411_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_AUTO_BLINK, 0x08, 0x00);
पूर्ण

अटल पूर्णांक rtl8411_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err;

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_5_PERCENT_ON);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_CTL,
			BPP_LDO_POWB, BPP_LDO_SUSPEND);
	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	/* To aव्योम too large in-rush current */
	udelay(150);

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_10_PERCENT_ON);
	अगर (err < 0)
		वापस err;

	udelay(150);

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_15_PERCENT_ON);
	अगर (err < 0)
		वापस err;

	udelay(150);

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_ON);
	अगर (err < 0)
		वापस err;

	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CTL, BPP_LDO_POWB, BPP_LDO_ON);
पूर्ण

अटल पूर्णांक rtl8411_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_OFF);
	अगर (err < 0)
		वापस err;

	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CTL,
			BPP_LDO_POWB, BPP_LDO_SUSPEND);
पूर्ण

अटल पूर्णांक rtl8411_करो_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage,
		पूर्णांक bpp_tuned18_shअगरt, पूर्णांक bpp_asic_1v8)
अणु
	u8 mask, val;
	पूर्णांक err;

	mask = (BPP_REG_TUNED18 << bpp_tuned18_shअगरt) | BPP_PAD_MASK;
	अगर (voltage == OUTPUT_3V3) अणु
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr,
				SD30_DRIVE_SEL, 0x07, pcr->sd30_drive_sel_3v3);
		अगर (err < 0)
			वापस err;
		val = (BPP_ASIC_3V3 << bpp_tuned18_shअगरt) | BPP_PAD_3V3;
	पूर्ण अन्यथा अगर (voltage == OUTPUT_1V8) अणु
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr,
				SD30_DRIVE_SEL, 0x07, pcr->sd30_drive_sel_1v8);
		अगर (err < 0)
			वापस err;
		val = (bpp_asic_1v8 << bpp_tuned18_shअगरt) | BPP_PAD_1V8;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CTL, mask, val);
पूर्ण

अटल पूर्णांक rtl8411_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	वापस rtl8411_करो_चयन_output_voltage(pcr, voltage,
			BPP_TUNED18_SHIFT_8411, BPP_ASIC_1V8);
पूर्ण

अटल पूर्णांक rtl8402_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	वापस rtl8411_करो_चयन_output_voltage(pcr, voltage,
			BPP_TUNED18_SHIFT_8402, BPP_ASIC_2V0);
पूर्ण

अटल अचिन्हित पूर्णांक rtl8411_cd_deglitch(काष्ठा rtsx_pcr *pcr)
अणु
	अचिन्हित पूर्णांक card_exist;

	card_exist = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	card_exist &= CARD_EXIST;
	अगर (!card_exist) अणु
		/* Enable card CD */
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CD_PAD_CTL,
				CD_DISABLE_MASK, CD_ENABLE);
		/* Enable card पूर्णांकerrupt */
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, EFUSE_CONTENT, 0xe0, 0x00);
		वापस 0;
	पूर्ण

	अगर (hweight32(card_exist) > 1) अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL,
				BPP_POWER_MASK, BPP_POWER_5_PERCENT_ON);
		msleep(100);

		card_exist = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
		अगर (card_exist & MS_EXIST)
			card_exist = MS_EXIST;
		अन्यथा अगर (card_exist & SD_EXIST)
			card_exist = SD_EXIST;
		अन्यथा
			card_exist = 0;

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL,
				BPP_POWER_MASK, BPP_POWER_OFF);

		pcr_dbg(pcr, "After CD deglitch, card_exist = 0x%x\n",
			card_exist);
	पूर्ण

	अगर (card_exist & MS_EXIST) अणु
		/* Disable SD पूर्णांकerrupt */
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, EFUSE_CONTENT, 0xe0, 0x40);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CD_PAD_CTL,
				CD_DISABLE_MASK, MS_CD_EN_ONLY);
	पूर्ण अन्यथा अगर (card_exist & SD_EXIST) अणु
		/* Disable MS पूर्णांकerrupt */
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, EFUSE_CONTENT, 0xe0, 0x80);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CD_PAD_CTL,
				CD_DISABLE_MASK, SD_CD_EN_ONLY);
	पूर्ण

	वापस card_exist;
पूर्ण

अटल पूर्णांक rtl8411_conv_clk_and_भाग_n(पूर्णांक input, पूर्णांक dir)
अणु
	पूर्णांक output;

	अगर (dir == CLK_TO_DIV_N)
		output = input * 4 / 5 - 2;
	अन्यथा
		output = (input + 2) * 5 / 4;

	वापस output;
पूर्ण

अटल स्थिर काष्ठा pcr_ops rtl8411_pcr_ops = अणु
	.fetch_venकरोr_settings = rtl8411_fetch_venकरोr_settings,
	.extra_init_hw = rtl8411_extra_init_hw,
	.optimize_phy = शून्य,
	.turn_on_led = rtl8411_turn_on_led,
	.turn_off_led = rtl8411_turn_off_led,
	.enable_स्वतः_blink = rtl8411_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtl8411_disable_स्वतः_blink,
	.card_घातer_on = rtl8411_card_घातer_on,
	.card_घातer_off = rtl8411_card_घातer_off,
	.चयन_output_voltage = rtl8411_चयन_output_voltage,
	.cd_deglitch = rtl8411_cd_deglitch,
	.conv_clk_and_भाग_n = rtl8411_conv_clk_and_भाग_n,
	.क्रमce_घातer_करोwn = rtl8411_क्रमce_घातer_करोwn,
पूर्ण;

अटल स्थिर काष्ठा pcr_ops rtl8402_pcr_ops = अणु
	.fetch_venकरोr_settings = rtl8411_fetch_venकरोr_settings,
	.extra_init_hw = rtl8411_extra_init_hw,
	.optimize_phy = शून्य,
	.turn_on_led = rtl8411_turn_on_led,
	.turn_off_led = rtl8411_turn_off_led,
	.enable_स्वतः_blink = rtl8411_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtl8411_disable_स्वतः_blink,
	.card_घातer_on = rtl8411_card_घातer_on,
	.card_घातer_off = rtl8411_card_घातer_off,
	.चयन_output_voltage = rtl8402_चयन_output_voltage,
	.cd_deglitch = rtl8411_cd_deglitch,
	.conv_clk_and_भाग_n = rtl8411_conv_clk_and_भाग_n,
	.क्रमce_घातer_करोwn = rtl8411_क्रमce_घातer_करोwn,
पूर्ण;

अटल स्थिर काष्ठा pcr_ops rtl8411b_pcr_ops = अणु
	.fetch_venकरोr_settings = rtl8411b_fetch_venकरोr_settings,
	.extra_init_hw = rtl8411b_extra_init_hw,
	.optimize_phy = शून्य,
	.turn_on_led = rtl8411_turn_on_led,
	.turn_off_led = rtl8411_turn_off_led,
	.enable_स्वतः_blink = rtl8411_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtl8411_disable_स्वतः_blink,
	.card_घातer_on = rtl8411_card_घातer_on,
	.card_घातer_off = rtl8411_card_घातer_off,
	.चयन_output_voltage = rtl8411_चयन_output_voltage,
	.cd_deglitch = rtl8411_cd_deglitch,
	.conv_clk_and_भाग_n = rtl8411_conv_clk_and_भाग_n,
	.क्रमce_घातer_करोwn = rtl8411_क्रमce_घातer_करोwn,
पूर्ण;

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rtl8411_sd_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xA9),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x09),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x09),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04),
	0,
पूर्ण;

/* SD Pull Control Disable:
 *     SD_DAT[3:0] ==> pull करोwn
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull करोwn
 *     SD_CMD      ==> pull करोwn
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rtl8411_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x65),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x95),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x09),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04),
	0,
पूर्ण;

/* MS Pull Control Enable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rtl8411_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x65),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x95),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x05),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04),
	0,
पूर्ण;

/* MS Pull Control Disable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rtl8411_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x65),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x95),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x09),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn64_sd_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x09 | 0xD0),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x09 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn48_sd_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x69 | 0x90),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x08 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn64_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x65),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x05 | 0xD0),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x09 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn48_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x65 | 0x90),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn64_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x65),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x05 | 0xD0),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x05 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn48_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x65 | 0x90),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn64_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x65),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x05 | 0xD0),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x09 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x05 | 0x50),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल स्थिर u32 rtl8411b_qfn48_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0x65 | 0x90),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x04 | 0x11),
	0,
पूर्ण;

अटल व्योम rtl8411_init_common_params(काष्ठा rtsx_pcr *pcr)
अणु
	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	pcr->num_slots = 2;
	pcr->flags = 0;
	pcr->card_drive_sel = RTL8411_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = DRIVER_TYPE_D;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_CFG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(23, 7, 14);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(4, 3, 10);
	pcr->ic_version = rtl8411_get_ic_version(pcr);
पूर्ण

व्योम rtl8411_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	rtl8411_init_common_params(pcr);
	pcr->ops = &rtl8411_pcr_ops;
	set_pull_ctrl_tables(pcr, rtl8411);
पूर्ण

व्योम rtl8411b_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	rtl8411_init_common_params(pcr);
	pcr->ops = &rtl8411b_pcr_ops;
	अगर (rtl8411b_is_qfn48(pcr))
		set_pull_ctrl_tables(pcr, rtl8411b_qfn48);
	अन्यथा
		set_pull_ctrl_tables(pcr, rtl8411b_qfn64);
पूर्ण

व्योम rtl8402_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	rtl8411_init_common_params(pcr);
	pcr->ops = &rtl8402_pcr_ops;
	set_pull_ctrl_tables(pcr, rtl8411);
पूर्ण
