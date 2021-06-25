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
#समावेश <linux/delay.h>
#समावेश <linux/rtsx_pci.h>

#समावेश "rtsx_pcr.h"

अटल u8 rts5227_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, DUMMY_REG_RESET_0, &val);
	वापस val & 0x0F;
पूर्ण

अटल व्योम rts5227_fill_driving(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	u8 driving_3v3[4][3] = अणु
		अणु0x13, 0x13, 0x13पूर्ण,
		अणु0x96, 0x96, 0x96पूर्ण,
		अणु0x7F, 0x7F, 0x7Fपूर्ण,
		अणु0x96, 0x96, 0x96पूर्ण,
	पूर्ण;
	u8 driving_1v8[4][3] = अणु
		अणु0x99, 0x99, 0x99पूर्ण,
		अणु0xAA, 0xAA, 0xAAपूर्ण,
		अणु0xFE, 0xFE, 0xFEपूर्ण,
		अणु0xB3, 0xB3, 0xB3पूर्ण,
	पूर्ण;
	u8 (*driving)[3], drive_sel;

	अगर (voltage == OUTPUT_3V3) अणु
		driving = driving_3v3;
		drive_sel = pcr->sd30_drive_sel_3v3;
	पूर्ण अन्यथा अणु
		driving = driving_1v8;
		drive_sel = pcr->sd30_drive_sel_1v8;
	पूर्ण

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_CLK_DRIVE_SEL,
			0xFF, driving[drive_sel][0]);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_CMD_DRIVE_SEL,
			0xFF, driving[drive_sel][1]);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_DAT_DRIVE_SEL,
			0xFF, driving[drive_sel][2]);
पूर्ण

अटल व्योम rts5227_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg;

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	अगर (!rtsx_venकरोr_setting_valid(reg))
		वापस;

	pcr->aspm_en = rtsx_reg_to_aspm(reg);
	pcr->sd30_drive_sel_1v8 = rtsx_reg_to_sd30_drive_sel_1v8(reg);
	pcr->card_drive_sel &= 0x3F;
	pcr->card_drive_sel |= rtsx_reg_to_card_drive_sel(reg);

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);
	अगर (rtsx_check_mmc_support(reg))
		pcr->extra_caps |= EXTRA_CAPS_NO_MMC;
	pcr->sd30_drive_sel_3v3 = rtsx_reg_to_sd30_drive_sel_3v3(reg);
	अगर (rtsx_reg_check_reverse_socket(reg))
		pcr->flags |= PCR_REVERSE_SOCKET;
पूर्ण

अटल व्योम rts5227_init_from_cfg(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	पूर्णांक l1ss;
	u32 lval;
	काष्ठा rtsx_cr_option *option = &pcr->option;

	l1ss = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_L1SS);
	अगर (!l1ss)
		वापस;

	pci_पढ़ो_config_dword(pdev, l1ss + PCI_L1SS_CTL1, &lval);

	अगर (CHK_PCI_PID(pcr, 0x522A)) अणु
		अगर (0 == (lval & 0x0F))
			rtsx_pci_enable_oobs_polling(pcr);
		अन्यथा
			rtsx_pci_disable_oobs_polling(pcr);
	पूर्ण

	अगर (lval & PCI_L1SS_CTL1_ASPM_L1_1)
		rtsx_set_dev_flag(pcr, ASPM_L1_1_EN);
	अन्यथा
		rtsx_clear_dev_flag(pcr, ASPM_L1_1_EN);

	अगर (lval & PCI_L1SS_CTL1_ASPM_L1_2)
		rtsx_set_dev_flag(pcr, ASPM_L1_2_EN);
	अन्यथा
		rtsx_clear_dev_flag(pcr, ASPM_L1_2_EN);

	अगर (lval & PCI_L1SS_CTL1_PCIPM_L1_1)
		rtsx_set_dev_flag(pcr, PM_L1_1_EN);
	अन्यथा
		rtsx_clear_dev_flag(pcr, PM_L1_1_EN);

	अगर (lval & PCI_L1SS_CTL1_PCIPM_L1_2)
		rtsx_set_dev_flag(pcr, PM_L1_2_EN);
	अन्यथा
		rtsx_clear_dev_flag(pcr, PM_L1_2_EN);

	अगर (option->ltr_en) अणु
		u16 val;

		pcie_capability_पढ़ो_word(pcr->pci, PCI_EXP_DEVCTL2, &val);
		अगर (val & PCI_EXP_DEVCTL2_LTR_EN) अणु
			option->ltr_enabled = true;
			option->ltr_active = true;
			rtsx_set_ltr_latency(pcr, option->ltr_active_latency);
		पूर्ण अन्यथा अणु
			option->ltr_enabled = false;
		पूर्ण
	पूर्ण

	अगर (rtsx_check_dev_flag(pcr, ASPM_L1_1_EN | ASPM_L1_2_EN
				| PM_L1_1_EN | PM_L1_2_EN))
		option->क्रमce_clkreq_0 = false;
	अन्यथा
		option->क्रमce_clkreq_0 = true;

पूर्ण

अटल पूर्णांक rts5227_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	u16 cap;
	काष्ठा rtsx_cr_option *option = &pcr->option;

	rts5227_init_from_cfg(pcr);
	rtsx_pci_init_cmd(pcr);

	/* Configure GPIO as output */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, GPIO_CTL, 0x02, 0x02);
	/* Reset ASPM state to शेष value */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, ASPM_FORCE_CTL, 0x3F, 0);
	/* Switch LDO3318 source from DV33 to card_3v3 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x00);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x01);
	/* LED shine disabled, set initial shine cycle period */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OLT_LED_CTL, 0x0F, 0x02);
	/* Configure LTR */
	pcie_capability_पढ़ो_word(pcr->pci, PCI_EXP_DEVCTL2, &cap);
	अगर (cap & PCI_EXP_DEVCTL2_LTR_EN)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LTR_CTL, 0xFF, 0xA3);
	/* Configure OBFF */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OBFF_CFG, 0x03, 0x03);
	/* Configure driving */
	rts5227_fill_driving(pcr, OUTPUT_3V3);
	/* Configure क्रमce_घड़ी_req */
	अगर (pcr->flags & PCR_REVERSE_SOCKET)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0x30, 0x30);
	अन्यथा
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0x30, 0x00);

	अगर (option->क्रमce_clkreq_0)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG,
				FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_LOW);
	अन्यथा
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG,
				FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_HIGH);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, pcr->reg_pm_ctrl3, 0x10, 0x00);

	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5227_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CTRL3, D3_DELINK_MODE_EN, 0x00);
	अगर (err < 0)
		वापस err;

	/* Optimize RX sensitivity */
	वापस rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x00, 0xBA42);
पूर्ण

अटल पूर्णांक rts5227_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL, 0x02, 0x02);
पूर्ण

अटल पूर्णांक rts5227_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL, 0x02, 0x00);
पूर्ण

अटल पूर्णांक rts5227_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x08, 0x08);
पूर्ण

अटल पूर्णांक rts5227_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x08, 0x00);
पूर्ण

अटल पूर्णांक rts5227_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err;

	अगर (pcr->option.ocp_en)
		rtsx_pci_enable_ocp(pcr);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_PARTIAL_POWER_ON);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x02);

	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	/* To aव्योम too large in-rush current */
	msleep(20);
	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_POWER_ON);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x06);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE,
			SD_OUTPUT_EN, SD_OUTPUT_EN);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5227_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	अगर (pcr->option.ocp_en)
		rtsx_pci_disable_ocp(pcr);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL, SD_POWER_MASK |
			PMOS_STRG_MASK, SD_POWER_OFF | PMOS_STRG_400mA);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_GATE_CTRL, LDO3318_PWR_MASK, 0X00);

	वापस 0;
पूर्ण

अटल पूर्णांक rts5227_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	पूर्णांक err;

	अगर (voltage == OUTPUT_3V3) अणु
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x08, 0x4FC0 | 0x24);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (voltage == OUTPUT_1V8) अणु
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x11, 0x3C02);
		अगर (err < 0)
			वापस err;
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x08, 0x4C80 | 0x24);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* set pad drive */
	rtsx_pci_init_cmd(pcr);
	rts5227_fill_driving(pcr, voltage);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल स्थिर काष्ठा pcr_ops rts5227_pcr_ops = अणु
	.fetch_venकरोr_settings = rts5227_fetch_venकरोr_settings,
	.extra_init_hw = rts5227_extra_init_hw,
	.optimize_phy = rts5227_optimize_phy,
	.turn_on_led = rts5227_turn_on_led,
	.turn_off_led = rts5227_turn_off_led,
	.enable_स्वतः_blink = rts5227_enable_स्वतः_blink,
	.disable_स्वतः_blink = rts5227_disable_स्वतः_blink,
	.card_घातer_on = rts5227_card_घातer_on,
	.card_घातer_off = rts5227_card_घातer_off,
	.चयन_output_voltage = rts5227_चयन_output_voltage,
	.cd_deglitch = शून्य,
	.conv_clk_and_भाग_n = शून्य,
पूर्ण;

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5227_sd_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xE9),
	0,
पूर्ण;

/* SD Pull Control Disable:
 *     SD_DAT[3:0] ==> pull करोwn
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull करोwn
 *     SD_CMD      ==> pull करोwn
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5227_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xD5),
	0,
पूर्ण;

/* MS Pull Control Enable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5227_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

/* MS Pull Control Disable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5227_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

व्योम rts5227_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	pcr->num_slots = 2;
	pcr->ops = &rts5227_pcr_ops;

	pcr->flags = 0;
	pcr->card_drive_sel = RTSX_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = CFG_DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = CFG_DRIVER_TYPE_B;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_CFG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(27, 27, 15);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(30, 7, 7);

	pcr->ic_version = rts5227_get_ic_version(pcr);
	pcr->sd_pull_ctl_enable_tbl = rts5227_sd_pull_ctl_enable_tbl;
	pcr->sd_pull_ctl_disable_tbl = rts5227_sd_pull_ctl_disable_tbl;
	pcr->ms_pull_ctl_enable_tbl = rts5227_ms_pull_ctl_enable_tbl;
	pcr->ms_pull_ctl_disable_tbl = rts5227_ms_pull_ctl_disable_tbl;

	pcr->reg_pm_ctrl3 = PM_CTRL3;
पूर्ण

अटल पूर्णांक rts522a_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS522A_PM_CTRL3, D3_DELINK_MODE_EN,
		0x00);
	अगर (err < 0)
		वापस err;

	अगर (is_version(pcr, 0x522A, IC_VER_A)) अणु
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_RCR2,
			PHY_RCR2_INIT_27S);
		अगर (err)
			वापस err;

		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_RCR1, PHY_RCR1_INIT_27S);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_FLD0, PHY_FLD0_INIT_27S);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_FLD3, PHY_FLD3_INIT_27S);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_FLD4, PHY_FLD4_INIT_27S);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rts522a_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rts5227_extra_init_hw(pcr);

	/* Power करोwn OCP क्रम घातer consumption */
	अगर (!pcr->card_exist)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, OC_POWER_DOWN,
				OC_POWER_DOWN);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FUNC_FORCE_CTL, FUNC_FORCE_UPME_XMT_DBG,
		FUNC_FORCE_UPME_XMT_DBG);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PCLK_CTL, 0x04, 0x04);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CLK_FORCE_CTL, 0xFF, 0x11);

	वापस 0;
पूर्ण

अटल पूर्णांक rts522a_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	पूर्णांक err;

	अगर (voltage == OUTPUT_3V3) अणु
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x08, 0x57E4);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (voltage == OUTPUT_1V8) अणु
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x11, 0x3C02);
		अगर (err < 0)
			वापस err;
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x08, 0x54A4);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* set pad drive */
	rtsx_pci_init_cmd(pcr);
	rts5227_fill_driving(pcr, voltage);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल व्योम rts522a_set_l1off_cfg_sub_d0(काष्ठा rtsx_pcr *pcr, पूर्णांक active)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;
	पूर्णांक aspm_L1_1, aspm_L1_2;
	u8 val = 0;

	aspm_L1_1 = rtsx_check_dev_flag(pcr, ASPM_L1_1_EN);
	aspm_L1_2 = rtsx_check_dev_flag(pcr, ASPM_L1_2_EN);

	अगर (active) अणु
		/* run, latency: 60us */
		अगर (aspm_L1_1)
			val = option->ltr_l1off_snooze_sspwrgate;
	पूर्ण अन्यथा अणु
		/* l1off, latency: 300us */
		अगर (aspm_L1_2)
			val = option->ltr_l1off_sspwrgate;
	पूर्ण

	rtsx_set_l1off_sub(pcr, val);
पूर्ण

/* rts522a operations मुख्यly derived from rts5227, except phy/hw init setting.
 */
अटल स्थिर काष्ठा pcr_ops rts522a_pcr_ops = अणु
	.fetch_venकरोr_settings = rts5227_fetch_venकरोr_settings,
	.extra_init_hw = rts522a_extra_init_hw,
	.optimize_phy = rts522a_optimize_phy,
	.turn_on_led = rts5227_turn_on_led,
	.turn_off_led = rts5227_turn_off_led,
	.enable_स्वतः_blink = rts5227_enable_स्वतः_blink,
	.disable_स्वतः_blink = rts5227_disable_स्वतः_blink,
	.card_घातer_on = rts5227_card_घातer_on,
	.card_घातer_off = rts5227_card_घातer_off,
	.चयन_output_voltage = rts522a_चयन_output_voltage,
	.cd_deglitch = शून्य,
	.conv_clk_and_भाग_n = शून्य,
	.set_l1off_cfg_sub_d0 = rts522a_set_l1off_cfg_sub_d0,
पूर्ण;

व्योम rts522a_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	rts5227_init_params(pcr);
	pcr->ops = &rts522a_pcr_ops;
	pcr->aspm_mode = ASPM_MODE_REG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(20, 20, 11);
	pcr->reg_pm_ctrl3 = RTS522A_PM_CTRL3;

	option->dev_flags = LTR_L1SS_PWR_GATE_EN;
	option->ltr_en = true;

	/* init latency of active, idle, L1OFF to 60us, 300us, 3ms */
	option->ltr_active_latency = LTR_ACTIVE_LATENCY_DEF;
	option->ltr_idle_latency = LTR_IDLE_LATENCY_DEF;
	option->ltr_l1off_latency = LTR_L1OFF_LATENCY_DEF;
	option->l1_snooze_delay = L1_SNOOZE_DELAY_DEF;
	option->ltr_l1off_sspwrgate = 0x7F;
	option->ltr_l1off_snooze_sspwrgate = 0x78;

	pcr->option.ocp_en = 1;
	अगर (pcr->option.ocp_en)
		pcr->hw_param.पूर्णांकerrupt_en |= SD_OC_INT_EN;
	pcr->hw_param.ocp_glitch = SD_OCP_GLITCH_10M;
	pcr->option.sd_800mA_ocp_thd = RTS522A_OCP_THD_800;

पूर्ण
