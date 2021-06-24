<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtsx_pci.h>

#समावेश "rtsx_pcr.h"

अटल u8 rts5229_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, DUMMY_REG_RESET_0, &val);
	वापस val & 0x0F;
पूर्ण

अटल व्योम rts5229_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg;

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	अगर (!rtsx_venकरोr_setting_valid(reg))
		वापस;

	pcr->aspm_en = rtsx_reg_to_aspm(reg);
	pcr->sd30_drive_sel_1v8 =
		map_sd_drive(rtsx_reg_to_sd30_drive_sel_1v8(reg));
	pcr->card_drive_sel &= 0x3F;
	pcr->card_drive_sel |= rtsx_reg_to_card_drive_sel(reg);

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);
	pcr->sd30_drive_sel_3v3 =
		map_sd_drive(rtsx_reg_to_sd30_drive_sel_3v3(reg));
पूर्ण

अटल व्योम rts5229_क्रमce_घातer_करोwn(काष्ठा rtsx_pcr *pcr, u8 pm_state)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, 0x03, 0x03);
पूर्ण

अटल पूर्णांक rts5229_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_init_cmd(pcr);

	/* Configure GPIO as output */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, GPIO_CTL, 0x02, 0x02);
	/* Reset ASPM state to शेष value */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, ASPM_FORCE_CTL, 0x3F, 0);
	/* Force CLKREQ# PIN to drive 0 to request घड़ी */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0x08, 0x08);
	/* Switch LDO3318 source from DV33 to card_3v3 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x00);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x01);
	/* LED shine disabled, set initial shine cycle period */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OLT_LED_CTL, 0x0F, 0x02);
	/* Configure driving */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_DRIVE_SEL,
			0xFF, pcr->sd30_drive_sel_3v3);

	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5229_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	/* Optimize RX sensitivity */
	वापस rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x00, 0xBA42);
पूर्ण

अटल पूर्णांक rts5229_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL, 0x02, 0x02);
पूर्ण

अटल पूर्णांक rts5229_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL, 0x02, 0x00);
पूर्ण

अटल पूर्णांक rts5229_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x08, 0x08);
पूर्ण

अटल पूर्णांक rts5229_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x08, 0x00);
पूर्ण

अटल पूर्णांक rts5229_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err;

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_PARTIAL_POWER_ON);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x02);
	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	/* To aव्योम too large in-rush current */
	udelay(150);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_POWER_ON);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x06);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5229_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK | PMOS_STRG_MASK,
			SD_POWER_OFF | PMOS_STRG_400mA);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x00);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5229_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	पूर्णांक err;

	अगर (voltage == OUTPUT_3V3) अणु
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr,
				SD30_DRIVE_SEL, 0x07, pcr->sd30_drive_sel_3v3);
		अगर (err < 0)
			वापस err;
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x08, 0x4FC0 | 0x24);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (voltage == OUTPUT_1V8) अणु
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr,
				SD30_DRIVE_SEL, 0x07, pcr->sd30_drive_sel_1v8);
		अगर (err < 0)
			वापस err;
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x08, 0x4C40 | 0x24);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcr_ops rts5229_pcr_ops = अणु
	.fetch_venकरोr_settings = rts5229_fetch_venकरोr_settings,
	.extra_init_hw = rts5229_extra_init_hw,
	.optimize_phy = rts5229_optimize_phy,
	.turn_on_led = rts5229_turn_on_led,
	.turn_off_led = rts5229_turn_off_led,
	.enable_स्वतः_blink = rts5229_enable_स्वतः_blink,
	.disable_स्वतः_blink = rts5229_disable_स्वतः_blink,
	.card_घातer_on = rts5229_card_घातer_on,
	.card_घातer_off = rts5229_card_घातer_off,
	.चयन_output_voltage = rts5229_चयन_output_voltage,
	.cd_deglitch = शून्य,
	.conv_clk_and_भाग_n = शून्य,
	.क्रमce_घातer_करोwn = rts5229_क्रमce_घातer_करोwn,
पूर्ण;

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5229_sd_pull_ctl_enable_tbl1[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xE9),
	0,
पूर्ण;

/* For RTS5229 version C */
अटल स्थिर u32 rts5229_sd_pull_ctl_enable_tbl2[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xD9),
	0,
पूर्ण;

/* SD Pull Control Disable:
 *     SD_DAT[3:0] ==> pull करोwn
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull करोwn
 *     SD_CMD      ==> pull करोwn
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5229_sd_pull_ctl_disable_tbl1[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xD5),
	0,
पूर्ण;

/* For RTS5229 version C */
अटल स्थिर u32 rts5229_sd_pull_ctl_disable_tbl2[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xE5),
	0,
पूर्ण;

/* MS Pull Control Enable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5229_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

/* MS Pull Control Disable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5229_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

व्योम rts5229_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	pcr->num_slots = 2;
	pcr->ops = &rts5229_pcr_ops;

	pcr->flags = 0;
	pcr->card_drive_sel = RTSX_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = DRIVER_TYPE_D;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_CFG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(27, 27, 15);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(30, 6, 6);

	pcr->ic_version = rts5229_get_ic_version(pcr);
	अगर (pcr->ic_version == IC_VER_C) अणु
		pcr->sd_pull_ctl_enable_tbl = rts5229_sd_pull_ctl_enable_tbl2;
		pcr->sd_pull_ctl_disable_tbl = rts5229_sd_pull_ctl_disable_tbl2;
	पूर्ण अन्यथा अणु
		pcr->sd_pull_ctl_enable_tbl = rts5229_sd_pull_ctl_enable_tbl1;
		pcr->sd_pull_ctl_disable_tbl = rts5229_sd_pull_ctl_disable_tbl1;
	पूर्ण
	pcr->ms_pull_ctl_enable_tbl = rts5229_ms_pull_ctl_enable_tbl;
	pcr->ms_pull_ctl_disable_tbl = rts5229_ms_pull_ctl_disable_tbl;
पूर्ण
