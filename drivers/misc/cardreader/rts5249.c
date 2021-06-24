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

अटल u8 rts5249_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, DUMMY_REG_RESET_0, &val);
	वापस val & 0x0F;
पूर्ण

अटल व्योम rts5249_fill_driving(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	u8 driving_3v3[4][3] = अणु
		अणु0x11, 0x11, 0x18पूर्ण,
		अणु0x55, 0x55, 0x5Cपूर्ण,
		अणु0xFF, 0xFF, 0xFFपूर्ण,
		अणु0x96, 0x96, 0x96पूर्ण,
	पूर्ण;
	u8 driving_1v8[4][3] = अणु
		अणु0xC4, 0xC4, 0xC4पूर्ण,
		अणु0x3C, 0x3C, 0x3Cपूर्ण,
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

अटल व्योम rtsx_base_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg;

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	अगर (!rtsx_venकरोr_setting_valid(reg)) अणु
		pcr_dbg(pcr, "skip fetch vendor setting\n");
		वापस;
	पूर्ण

	pcr->aspm_en = rtsx_reg_to_aspm(reg);
	pcr->sd30_drive_sel_1v8 = rtsx_reg_to_sd30_drive_sel_1v8(reg);
	pcr->card_drive_sel &= 0x3F;
	pcr->card_drive_sel |= rtsx_reg_to_card_drive_sel(reg);

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);

	pcr->rtd3_en = rtsx_reg_to_rtd3_uhsii(reg);

	अगर (rtsx_check_mmc_support(reg))
		pcr->extra_caps |= EXTRA_CAPS_NO_MMC;
	pcr->sd30_drive_sel_3v3 = rtsx_reg_to_sd30_drive_sel_3v3(reg);
	अगर (rtsx_reg_check_reverse_socket(reg))
		pcr->flags |= PCR_REVERSE_SOCKET;
पूर्ण

अटल व्योम rts5249_init_from_cfg(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	पूर्णांक l1ss;
	काष्ठा rtsx_cr_option *option = &(pcr->option);
	u32 lval;

	l1ss = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_L1SS);
	अगर (!l1ss)
		वापस;

	pci_पढ़ो_config_dword(pdev, l1ss + PCI_L1SS_CTL1, &lval);

	अगर (CHK_PCI_PID(pcr, PID_524A) || CHK_PCI_PID(pcr, PID_525A)) अणु
		अगर (0 == (lval & 0x0F))
			rtsx_pci_enable_oobs_polling(pcr);
		अन्यथा
			rtsx_pci_disable_oobs_polling(pcr);
	पूर्ण


	अगर (lval & PCI_L1SS_CTL1_ASPM_L1_1)
		rtsx_set_dev_flag(pcr, ASPM_L1_1_EN);

	अगर (lval & PCI_L1SS_CTL1_ASPM_L1_2)
		rtsx_set_dev_flag(pcr, ASPM_L1_2_EN);

	अगर (lval & PCI_L1SS_CTL1_PCIPM_L1_1)
		rtsx_set_dev_flag(pcr, PM_L1_1_EN);

	अगर (lval & PCI_L1SS_CTL1_PCIPM_L1_2)
		rtsx_set_dev_flag(pcr, PM_L1_2_EN);

	अगर (option->ltr_en) अणु
		u16 val;

		pcie_capability_पढ़ो_word(pdev, PCI_EXP_DEVCTL2, &val);
		अगर (val & PCI_EXP_DEVCTL2_LTR_EN) अणु
			option->ltr_enabled = true;
			option->ltr_active = true;
			rtsx_set_ltr_latency(pcr, option->ltr_active_latency);
		पूर्ण अन्यथा अणु
			option->ltr_enabled = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rts5249_init_from_hw(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &(pcr->option);

	अगर (rtsx_check_dev_flag(pcr, ASPM_L1_1_EN | ASPM_L1_2_EN
				| PM_L1_1_EN | PM_L1_2_EN))
		option->क्रमce_clkreq_0 = false;
	अन्यथा
		option->क्रमce_clkreq_0 = true;

	वापस 0;
पूर्ण

अटल व्योम rts52xa_save_content_from_efuse(काष्ठा rtsx_pcr *pcr)
अणु
	u8 cnt, sv;
	u16 j = 0;
	u8 पंचांगp;
	u8 val;
	पूर्णांक i;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL,
				REG_EFUSE_BYPASS | REG_EFUSE_POR, REG_EFUSE_POR);
	udelay(1);

	pcr_dbg(pcr, "Enable efuse por!");
	pcr_dbg(pcr, "save efuse to autoload");

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_ADD, REG_EFUSE_ADD_MASK, 0x00);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_CTL,
				REG_EFUSE_ENABLE | REG_EFUSE_MODE, REG_EFUSE_ENABLE);
	/* Wait transfer end */
	क्रम (j = 0; j < 1024; j++) अणु
		rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_EFUSE_CTL, &पंचांगp);
		अगर ((पंचांगp & 0x80) == 0)
			अवरोध;
	पूर्ण
	rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_EFUSE_DATA, &val);
	cnt = val & 0x0F;
	sv = val & 0x10;

	अगर (sv) अणु
		क्रम (i = 0; i < 4; i++) अणु
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_ADD,
				REG_EFUSE_ADD_MASK, 0x04 + i);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_CTL,
				REG_EFUSE_ENABLE | REG_EFUSE_MODE, REG_EFUSE_ENABLE);
			/* Wait transfer end */
			क्रम (j = 0; j < 1024; j++) अणु
				rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_EFUSE_CTL, &पंचांगp);
				अगर ((पंचांगp & 0x80) == 0)
					अवरोध;
			पूर्ण
			rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_EFUSE_DATA, &val);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF04 + i, 0xFF, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF04, 0xFF, (u8)PCI_VID(pcr));
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF05, 0xFF, (u8)(PCI_VID(pcr) >> 8));
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF06, 0xFF, (u8)PCI_PID(pcr));
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF07, 0xFF, (u8)(PCI_PID(pcr) >> 8));
	पूर्ण

	क्रम (i = 0; i < cnt * 4; i++) अणु
		अगर (sv)
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_ADD,
				REG_EFUSE_ADD_MASK, 0x08 + i);
		अन्यथा
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_ADD,
				REG_EFUSE_ADD_MASK, 0x04 + i);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_EFUSE_CTL,
				REG_EFUSE_ENABLE | REG_EFUSE_MODE, REG_EFUSE_ENABLE);
		/* Wait transfer end */
		क्रम (j = 0; j < 1024; j++) अणु
			rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_EFUSE_CTL, &पंचांगp);
			अगर ((पंचांगp & 0x80) == 0)
				अवरोध;
		पूर्ण
		rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_EFUSE_DATA, &val);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF08 + i, 0xFF, val);
	पूर्ण
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF00, 0xFF, (cnt & 0x7F) | 0x80);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL,
		REG_EFUSE_BYPASS | REG_EFUSE_POR, REG_EFUSE_BYPASS);
	pcr_dbg(pcr, "Disable efuse por!");
पूर्ण

अटल व्योम rts52xa_save_content_to_स्वतःload_space(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, RESET_LOAD_REG, &val);
	अगर (val & 0x02) अणु
		rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS525A_BIOS_CFG, &val);
		अगर (val & RTS525A_LOAD_BIOS_FLAG) अणु
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS525A_BIOS_CFG,
				RTS525A_LOAD_BIOS_FLAG, RTS525A_CLEAR_BIOS_FLAG);

			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL,
				REG_EFUSE_POWER_MASK, REG_EFUSE_POWERON);

			pcr_dbg(pcr, "Power ON efuse!");
			mdelay(1);
			rts52xa_save_content_from_efuse(pcr);
		पूर्ण अन्यथा अणु
			rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL, &val);
			अगर (!(val & 0x08))
				rts52xa_save_content_from_efuse(pcr);
		पूर्ण
	पूर्ण अन्यथा अणु
		pcr_dbg(pcr, "Load from autoload");
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF00, 0xFF, 0x80);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF04, 0xFF, (u8)PCI_VID(pcr));
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF05, 0xFF, (u8)(PCI_VID(pcr) >> 8));
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF06, 0xFF, (u8)PCI_PID(pcr));
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFF07, 0xFF, (u8)(PCI_PID(pcr) >> 8));
	पूर्ण
पूर्ण

अटल पूर्णांक rts5249_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &(pcr->option);

	rts5249_init_from_cfg(pcr);
	rts5249_init_from_hw(pcr);

	rtsx_pci_init_cmd(pcr);

	अगर (CHK_PCI_PID(pcr, PID_524A) || CHK_PCI_PID(pcr, PID_525A))
		rts52xa_save_content_to_स्वतःload_space(pcr);

	/* Rest L1SUB Config */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, L1SUB_CONFIG3, 0xFF, 0x00);
	/* Configure GPIO as output */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, GPIO_CTL, 0x02, 0x02);
	/* Reset ASPM state to शेष value */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, ASPM_FORCE_CTL, 0x3F, 0);
	/* Switch LDO3318 source from DV33 to card_3v3 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x00);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x01);
	/* LED shine disabled, set initial shine cycle period */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OLT_LED_CTL, 0x0F, 0x02);
	/* Configure driving */
	rts5249_fill_driving(pcr, OUTPUT_3V3);
	अगर (pcr->flags & PCR_REVERSE_SOCKET)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB0, 0xB0);
	अन्यथा
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB0, 0x80);

	rtsx_pci_send_cmd(pcr, CMD_TIMEOUT_DEF);

	अगर (CHK_PCI_PID(pcr, PID_524A) || CHK_PCI_PID(pcr, PID_525A))
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_VREF, PWD_SUSPND_EN, PWD_SUSPND_EN);

	अगर (pcr->rtd3_en) अणु
		अगर (CHK_PCI_PID(pcr, PID_524A) || CHK_PCI_PID(pcr, PID_525A)) अणु
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PM_CTRL3, 0x01, 0x01);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL, 0x30, 0x30);
		पूर्ण अन्यथा अणु
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CTRL3, 0x01, 0x01);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PME_FORCE_CTL, 0xFF, 0x33);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (CHK_PCI_PID(pcr, PID_524A) || CHK_PCI_PID(pcr, PID_525A)) अणु
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PM_CTRL3, 0x01, 0x00);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL, 0x30, 0x20);
		पूर्ण अन्यथा अणु
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PME_FORCE_CTL, 0xFF, 0x30);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CTRL3, 0x01, 0x00);
		पूर्ण
	पूर्ण


	/*
	 * If u_क्रमce_clkreq_0 is enabled, CLKREQ# PIN will be क्रमced
	 * to drive low, and we क्रमcibly request घड़ी.
	 */
	अगर (option->क्रमce_clkreq_0)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PETXCFG,
			FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_LOW);
	अन्यथा
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PETXCFG,
			FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_HIGH);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, pcr->reg_pm_ctrl3, 0x10, 0x00);
	अगर (CHK_PCI_PID(pcr, PID_524A) || CHK_PCI_PID(pcr, PID_525A)) अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PME_FORCE_CTL,
				REG_EFUSE_POWER_MASK, REG_EFUSE_POWEROFF);
		pcr_dbg(pcr, "Power OFF efuse!");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rts5249_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CTRL3, D3_DELINK_MODE_EN, 0x00);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_REV,
			PHY_REV_RESV | PHY_REV_RXIDLE_LATCHED |
			PHY_REV_P1_EN | PHY_REV_RXIDLE_EN |
			PHY_REV_CLKREQ_TX_EN | PHY_REV_RX_PWST |
			PHY_REV_CLKREQ_DT_1_0 | PHY_REV_STOP_CLKRD |
			PHY_REV_STOP_CLKWR);
	अगर (err < 0)
		वापस err;

	msleep(1);

	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_BPCR,
			PHY_BPCR_IBRXSEL | PHY_BPCR_IBTXSEL |
			PHY_BPCR_IB_FILTER | PHY_BPCR_CMIRROR_EN);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_PCR,
			PHY_PCR_FORCE_CODE | PHY_PCR_OOBS_CALI_50 |
			PHY_PCR_OOBS_VCM_08 | PHY_PCR_OOBS_SEN_90 |
			PHY_PCR_RSSI_EN | PHY_PCR_RX10K);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_RCR2,
			PHY_RCR2_EMPHASE_EN | PHY_RCR2_NADJR |
			PHY_RCR2_CDR_SR_2 | PHY_RCR2_FREQSEL_12 |
			PHY_RCR2_CDR_SC_12P | PHY_RCR2_CALIB_LATE);
	अगर (err < 0)
		वापस err;

	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_FLD4,
			PHY_FLD4_FLDEN_SEL | PHY_FLD4_REQ_REF |
			PHY_FLD4_RXAMP_OFF | PHY_FLD4_REQ_ADDA |
			PHY_FLD4_BER_COUNT | PHY_FLD4_BER_TIMER |
			PHY_FLD4_BER_CHK_EN);
	अगर (err < 0)
		वापस err;
	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_RDR,
			PHY_RDR_RXDSEL_1_9 | PHY_SSC_AUTO_PWD);
	अगर (err < 0)
		वापस err;
	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_RCR1,
			PHY_RCR1_ADP_TIME_4 | PHY_RCR1_VCO_COARSE);
	अगर (err < 0)
		वापस err;
	err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_FLD3,
			PHY_FLD3_TIMER_4 | PHY_FLD3_TIMER_6 |
			PHY_FLD3_RXDELINK);
	अगर (err < 0)
		वापस err;

	वापस rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_TUNE,
			PHY_TUNE_TUNEREF_1_0 | PHY_TUNE_VBGSEL_1252 |
			PHY_TUNE_SDBUS_33 | PHY_TUNE_TUNED18 |
			PHY_TUNE_TUNED12 | PHY_TUNE_TUNEA12);
पूर्ण

अटल पूर्णांक rtsx_base_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL, 0x02, 0x02);
पूर्ण

अटल पूर्णांक rtsx_base_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL, 0x02, 0x00);
पूर्ण

अटल पूर्णांक rtsx_base_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x08, 0x08);
पूर्ण

अटल पूर्णांक rtsx_base_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x08, 0x00);
पूर्ण

अटल पूर्णांक rtsx_base_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err;
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ocp_en)
		rtsx_pci_enable_ocp(pcr);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_VCC_PARTIAL_POWER_ON);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x02);
	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	msleep(5);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_VCC_POWER_ON);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x06);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rtsx_base_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ocp_en)
		rtsx_pci_disable_ocp(pcr);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_PWR_CTL, SD_POWER_MASK, SD_POWER_OFF);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_GATE_CTRL, LDO3318_PWR_MASK, 0x00);
	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_base_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	पूर्णांक err;
	u16 append;

	चयन (voltage) अणु
	हाल OUTPUT_3V3:
		err = rtsx_pci_update_phy(pcr, PHY_TUNE, PHY_TUNE_VOLTAGE_MASK,
			PHY_TUNE_VOLTAGE_3V3);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल OUTPUT_1V8:
		append = PHY_TUNE_D18_1V8;
		अगर (CHK_PCI_PID(pcr, 0x5249)) अणु
			err = rtsx_pci_update_phy(pcr, PHY_BACR,
				PHY_BACR_BASIC_MASK, 0);
			अगर (err < 0)
				वापस err;
			append = PHY_TUNE_D18_1V7;
		पूर्ण

		err = rtsx_pci_update_phy(pcr, PHY_TUNE, PHY_TUNE_VOLTAGE_MASK,
			append);
		अगर (err < 0)
			वापस err;
		अवरोध;
	शेष:
		pcr_dbg(pcr, "unknown output voltage %d\n", voltage);
		वापस -EINVAL;
	पूर्ण

	/* set pad drive */
	rtsx_pci_init_cmd(pcr);
	rts5249_fill_driving(pcr, voltage);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल स्थिर काष्ठा pcr_ops rts5249_pcr_ops = अणु
	.fetch_venकरोr_settings = rtsx_base_fetch_venकरोr_settings,
	.extra_init_hw = rts5249_extra_init_hw,
	.optimize_phy = rts5249_optimize_phy,
	.turn_on_led = rtsx_base_turn_on_led,
	.turn_off_led = rtsx_base_turn_off_led,
	.enable_स्वतः_blink = rtsx_base_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtsx_base_disable_स्वतः_blink,
	.card_घातer_on = rtsx_base_card_घातer_on,
	.card_घातer_off = rtsx_base_card_घातer_off,
	.चयन_output_voltage = rtsx_base_चयन_output_voltage,
पूर्ण;

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5249_sd_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x66),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0xAA),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xE9),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0xAA),
	0,
पूर्ण;

/* SD Pull Control Disable:
 *     SD_DAT[3:0] ==> pull करोwn
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull करोwn
 *     SD_CMD      ==> pull करोwn
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5249_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x66),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xD5),
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	0,
पूर्ण;

/* MS Pull Control Enable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5249_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

/* MS Pull Control Disable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5249_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

व्योम rts5249_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &(pcr->option);

	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	pcr->num_slots = 2;
	pcr->ops = &rts5249_pcr_ops;

	pcr->flags = 0;
	pcr->card_drive_sel = RTSX_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = CFG_DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = CFG_DRIVER_TYPE_B;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_CFG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(1, 29, 16);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(24, 6, 5);

	pcr->ic_version = rts5249_get_ic_version(pcr);
	pcr->sd_pull_ctl_enable_tbl = rts5249_sd_pull_ctl_enable_tbl;
	pcr->sd_pull_ctl_disable_tbl = rts5249_sd_pull_ctl_disable_tbl;
	pcr->ms_pull_ctl_enable_tbl = rts5249_ms_pull_ctl_enable_tbl;
	pcr->ms_pull_ctl_disable_tbl = rts5249_ms_pull_ctl_disable_tbl;

	pcr->reg_pm_ctrl3 = PM_CTRL3;

	option->dev_flags = (LTR_L1SS_PWR_GATE_CHECK_CARD_EN
				| LTR_L1SS_PWR_GATE_EN);
	option->ltr_en = true;

	/* Init latency of active, idle, L1OFF to 60us, 300us, 3ms */
	option->ltr_active_latency = LTR_ACTIVE_LATENCY_DEF;
	option->ltr_idle_latency = LTR_IDLE_LATENCY_DEF;
	option->ltr_l1off_latency = LTR_L1OFF_LATENCY_DEF;
	option->l1_snooze_delay = L1_SNOOZE_DELAY_DEF;
	option->ltr_l1off_sspwrgate = LTR_L1OFF_SSPWRGATE_5249_DEF;
	option->ltr_l1off_snooze_sspwrgate =
		LTR_L1OFF_SNOOZE_SSPWRGATE_5249_DEF;
पूर्ण

अटल पूर्णांक rts524a_ग_लिखो_phy(काष्ठा rtsx_pcr *pcr, u8 addr, u16 val)
अणु
	addr = addr & 0x80 ? (addr & 0x7F) | 0x40 : addr;

	वापस __rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, addr, val);
पूर्ण

अटल पूर्णांक rts524a_पढ़ो_phy(काष्ठा rtsx_pcr *pcr, u8 addr, u16 *val)
अणु
	addr = addr & 0x80 ? (addr & 0x7F) | 0x40 : addr;

	वापस __rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, addr, val);
पूर्ण

अटल पूर्णांक rts524a_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PM_CTRL3,
		D3_DELINK_MODE_EN, 0x00);
	अगर (err < 0)
		वापस err;

	rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_PCR,
		PHY_PCR_FORCE_CODE | PHY_PCR_OOBS_CALI_50 |
		PHY_PCR_OOBS_VCM_08 | PHY_PCR_OOBS_SEN_90 | PHY_PCR_RSSI_EN);
	rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_SSCCR3,
		PHY_SSCCR3_STEP_IN | PHY_SSCCR3_CHECK_DELAY);

	अगर (is_version(pcr, 0x524A, IC_VER_A)) अणु
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_SSCCR3,
			PHY_SSCCR3_STEP_IN | PHY_SSCCR3_CHECK_DELAY);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_SSCCR2,
			PHY_SSCCR2_PLL_NCODE | PHY_SSCCR2_TIME0 |
			PHY_SSCCR2_TIME2_WIDTH);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_ANA1A,
			PHY_ANA1A_TXR_LOOPBACK | PHY_ANA1A_RXT_BIST |
			PHY_ANA1A_TXR_BIST | PHY_ANA1A_REV);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_ANA1D,
			PHY_ANA1D_DEBUG_ADDR);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_DIG1E,
			PHY_DIG1E_REV | PHY_DIG1E_D0_X_D1 |
			PHY_DIG1E_RX_ON_HOST | PHY_DIG1E_RCLK_REF_HOST |
			PHY_DIG1E_RCLK_TX_EN_KEEP |
			PHY_DIG1E_RCLK_TX_TERM_KEEP |
			PHY_DIG1E_RCLK_RX_EIDLE_ON | PHY_DIG1E_TX_TERM_KEEP |
			PHY_DIG1E_RX_TERM_KEEP | PHY_DIG1E_TX_EN_KEEP |
			PHY_DIG1E_RX_EN_KEEP);
	पूर्ण

	rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_ANA08,
		PHY_ANA08_RX_EQ_DCGAIN | PHY_ANA08_SEL_RX_EN |
		PHY_ANA08_RX_EQ_VAL | PHY_ANA08_SCP | PHY_ANA08_SEL_IPI);

	वापस 0;
पूर्ण

अटल पूर्णांक rts524a_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rts5249_extra_init_hw(pcr);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FUNC_FORCE_CTL,
		FORCE_ASPM_L1_EN, FORCE_ASPM_L1_EN);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG1, LDO_VCC_LMT_EN,
		LDO_VCC_LMT_EN);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PCLK_CTL, PCLK_MODE_SEL, PCLK_MODE_SEL);
	अगर (is_version(pcr, 0x524A, IC_VER_A)) अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_DV18_CFG,
			LDO_DV18_SR_MASK, LDO_DV18_SR_DF);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG1,
			LDO_VCC_REF_TUNE_MASK, LDO_VCC_REF_1V2);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VIO_CFG,
			LDO_VIO_REF_TUNE_MASK, LDO_VIO_REF_1V2);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VIO_CFG,
			LDO_VIO_SR_MASK, LDO_VIO_SR_DF);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_DV12S_CFG,
			LDO_REF12_TUNE_MASK, LDO_REF12_TUNE_DF);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD40_LDO_CTL1,
			SD40_VIO_TUNE_MASK, SD40_VIO_TUNE_1V7);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rts5250_set_l1off_cfg_sub_d0(काष्ठा rtsx_pcr *pcr, पूर्णांक active)
अणु
	काष्ठा rtsx_cr_option *option = &(pcr->option);

	u32 पूर्णांकerrupt = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	पूर्णांक card_exist = (पूर्णांकerrupt & SD_EXIST) | (पूर्णांकerrupt & MS_EXIST);
	पूर्णांक aspm_L1_1, aspm_L1_2;
	u8 val = 0;

	aspm_L1_1 = rtsx_check_dev_flag(pcr, ASPM_L1_1_EN);
	aspm_L1_2 = rtsx_check_dev_flag(pcr, ASPM_L1_2_EN);

	अगर (active) अणु
		/* Run, latency: 60us */
		अगर (aspm_L1_1)
			val = option->ltr_l1off_snooze_sspwrgate;
	पूर्ण अन्यथा अणु
		/* L1off, latency: 300us */
		अगर (aspm_L1_2)
			val = option->ltr_l1off_sspwrgate;
	पूर्ण

	अगर (aspm_L1_1 || aspm_L1_2) अणु
		अगर (rtsx_check_dev_flag(pcr,
					LTR_L1SS_PWR_GATE_CHECK_CARD_EN)) अणु
			अगर (card_exist)
				val &= ~L1OFF_MBIAS2_EN_5250;
			अन्यथा
				val |= L1OFF_MBIAS2_EN_5250;
		पूर्ण
	पूर्ण
	rtsx_set_l1off_sub(pcr, val);
पूर्ण

अटल स्थिर काष्ठा pcr_ops rts524a_pcr_ops = अणु
	.ग_लिखो_phy = rts524a_ग_लिखो_phy,
	.पढ़ो_phy = rts524a_पढ़ो_phy,
	.fetch_venकरोr_settings = rtsx_base_fetch_venकरोr_settings,
	.extra_init_hw = rts524a_extra_init_hw,
	.optimize_phy = rts524a_optimize_phy,
	.turn_on_led = rtsx_base_turn_on_led,
	.turn_off_led = rtsx_base_turn_off_led,
	.enable_स्वतः_blink = rtsx_base_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtsx_base_disable_स्वतः_blink,
	.card_घातer_on = rtsx_base_card_घातer_on,
	.card_घातer_off = rtsx_base_card_घातer_off,
	.चयन_output_voltage = rtsx_base_चयन_output_voltage,
	.set_l1off_cfg_sub_d0 = rts5250_set_l1off_cfg_sub_d0,
पूर्ण;

व्योम rts524a_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	rts5249_init_params(pcr);
	pcr->aspm_mode = ASPM_MODE_REG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(27, 29, 11);
	pcr->option.ltr_l1off_sspwrgate = LTR_L1OFF_SSPWRGATE_5250_DEF;
	pcr->option.ltr_l1off_snooze_sspwrgate =
		LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF;

	pcr->reg_pm_ctrl3 = RTS524A_PM_CTRL3;
	pcr->ops = &rts524a_pcr_ops;

	pcr->option.ocp_en = 1;
	अगर (pcr->option.ocp_en)
		pcr->hw_param.पूर्णांकerrupt_en |= SD_OC_INT_EN;
	pcr->hw_param.ocp_glitch = SD_OCP_GLITCH_10M;
	pcr->option.sd_800mA_ocp_thd = RTS524A_OCP_THD_800;

पूर्ण

अटल पूर्णांक rts525a_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG1,
		LDO_VCC_TUNE_MASK, LDO_VCC_3V3);
	वापस rtsx_base_card_घातer_on(pcr, card);
पूर्ण

अटल पूर्णांक rts525a_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	चयन (voltage) अणु
	हाल OUTPUT_3V3:
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2,
			LDO_D3318_MASK, LDO_D3318_33V);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PAD_CTL, SD_IO_USING_1V8, 0);
		अवरोध;
	हाल OUTPUT_1V8:
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2,
			LDO_D3318_MASK, LDO_D3318_18V);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PAD_CTL, SD_IO_USING_1V8,
			SD_IO_USING_1V8);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rtsx_pci_init_cmd(pcr);
	rts5249_fill_driving(pcr, voltage);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts525a_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;

	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS524A_PM_CTRL3,
		D3_DELINK_MODE_EN, 0x00);
	अगर (err < 0)
		वापस err;

	rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, _PHY_FLD0,
		_PHY_FLD0_CLK_REQ_20C | _PHY_FLD0_RX_IDLE_EN |
		_PHY_FLD0_BIT_ERR_RSTN | _PHY_FLD0_BER_COUNT |
		_PHY_FLD0_BER_TIMER | _PHY_FLD0_CHECK_EN);

	rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, _PHY_ANA03,
		_PHY_ANA03_TIMER_MAX | _PHY_ANA03_OOBS_DEB_EN |
		_PHY_CMU_DEBUG_EN);

	अगर (is_version(pcr, 0x525A, IC_VER_A))
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, _PHY_REV0,
			_PHY_REV0_FILTER_OUT | _PHY_REV0_CDR_BYPASS_PFD |
			_PHY_REV0_CDR_RX_IDLE_BYPASS);

	वापस 0;
पूर्ण

अटल पूर्णांक rts525a_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rts5249_extra_init_hw(pcr);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5250_CLK_CFG3, RTS525A_CFG_MEM_PD, RTS525A_CFG_MEM_PD);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PCLK_CTL, PCLK_MODE_SEL, PCLK_MODE_SEL);
	अगर (is_version(pcr, 0x525A, IC_VER_A)) अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, L1SUB_CONFIG2,
			L1SUB_AUTO_CFG, L1SUB_AUTO_CFG);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RREF_CFG,
			RREF_VBGSEL_MASK, RREF_VBGSEL_1V25);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VIO_CFG,
			LDO_VIO_TUNE_MASK, LDO_VIO_1V7);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_DV12S_CFG,
			LDO_D12_TUNE_MASK, LDO_D12_TUNE_DF);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_AV12S_CFG,
			LDO_AV12S_TUNE_MASK, LDO_AV12S_TUNE_DF);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG0,
			LDO_VCC_LMTVTH_MASK, LDO_VCC_LMTVTH_2A);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OOBS_CONFIG,
			OOBS_AUTOK_DIS | OOBS_VAL_MASK, 0x89);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcr_ops rts525a_pcr_ops = अणु
	.fetch_venकरोr_settings = rtsx_base_fetch_venकरोr_settings,
	.extra_init_hw = rts525a_extra_init_hw,
	.optimize_phy = rts525a_optimize_phy,
	.turn_on_led = rtsx_base_turn_on_led,
	.turn_off_led = rtsx_base_turn_off_led,
	.enable_स्वतः_blink = rtsx_base_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtsx_base_disable_स्वतः_blink,
	.card_घातer_on = rts525a_card_घातer_on,
	.card_घातer_off = rtsx_base_card_घातer_off,
	.चयन_output_voltage = rts525a_चयन_output_voltage,
	.set_l1off_cfg_sub_d0 = rts5250_set_l1off_cfg_sub_d0,
पूर्ण;

व्योम rts525a_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	rts5249_init_params(pcr);
	pcr->aspm_mode = ASPM_MODE_REG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(25, 29, 11);
	pcr->option.ltr_l1off_sspwrgate = LTR_L1OFF_SSPWRGATE_5250_DEF;
	pcr->option.ltr_l1off_snooze_sspwrgate =
		LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF;

	pcr->reg_pm_ctrl3 = RTS524A_PM_CTRL3;
	pcr->ops = &rts525a_pcr_ops;

	pcr->option.ocp_en = 1;
	अगर (pcr->option.ocp_en)
		pcr->hw_param.पूर्णांकerrupt_en |= SD_OC_INT_EN;
	pcr->hw_param.ocp_glitch = SD_OCP_GLITCH_10M;
	pcr->option.sd_800mA_ocp_thd = RTS525A_OCP_THD_800;
पूर्ण
