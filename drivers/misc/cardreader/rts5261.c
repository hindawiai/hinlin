<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2018-2019 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Rui FENG <rui_feng@realsil.com.cn>
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtsx_pci.h>

#समावेश "rts5261.h"
#समावेश "rtsx_pcr.h"

अटल u8 rts5261_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, DUMMY_REG_RESET_0, &val);
	वापस val & IC_VERSION_MASK;
पूर्ण

अटल व्योम rts5261_fill_driving(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	u8 driving_3v3[4][3] = अणु
		अणु0x96, 0x96, 0x96पूर्ण,
		अणु0x96, 0x96, 0x96पूर्ण,
		अणु0x7F, 0x7F, 0x7Fपूर्ण,
		अणु0x13, 0x13, 0x13पूर्ण,
	पूर्ण;
	u8 driving_1v8[4][3] = अणु
		अणु0xB3, 0xB3, 0xB3पूर्ण,
		अणु0x3A, 0x3A, 0x3Aपूर्ण,
		अणु0xE6, 0xE6, 0xE6पूर्ण,
		अणु0x99, 0x99, 0x99पूर्ण,
	पूर्ण;
	u8 (*driving)[3], drive_sel;

	अगर (voltage == OUTPUT_3V3) अणु
		driving = driving_3v3;
		drive_sel = pcr->sd30_drive_sel_3v3;
	पूर्ण अन्यथा अणु
		driving = driving_1v8;
		drive_sel = pcr->sd30_drive_sel_1v8;
	पूर्ण

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD30_CLK_DRIVE_SEL,
			 0xFF, driving[drive_sel][0]);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD30_CMD_DRIVE_SEL,
			 0xFF, driving[drive_sel][1]);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD30_DAT_DRIVE_SEL,
			 0xFF, driving[drive_sel][2]);
पूर्ण

अटल व्योम rtsx5261_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg;

	/* 0x814~0x817 */
	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);

	अगर (!rts5261_venकरोr_setting_valid(reg)) अणु
		/* Not support MMC शेष */
		pcr->extra_caps |= EXTRA_CAPS_NO_MMC;
		pcr_dbg(pcr, "skip fetch vendor setting\n");
		वापस;
	पूर्ण

	अगर (!rts5261_reg_check_mmc_support(reg))
		pcr->extra_caps |= EXTRA_CAPS_NO_MMC;

	/* TO करो: need to add rtd3 function */
	pcr->rtd3_en = rts5261_reg_to_rtd3(reg);

	अगर (rts5261_reg_check_reverse_socket(reg))
		pcr->flags |= PCR_REVERSE_SOCKET;

	/* 0x724~0x727 */
	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	pcr->aspm_en = rts5261_reg_to_aspm(reg);
	pcr->sd30_drive_sel_1v8 = rts5261_reg_to_sd30_drive_sel_1v8(reg);
	pcr->sd30_drive_sel_3v3 = rts5261_reg_to_sd30_drive_sel_3v3(reg);
पूर्ण

अटल व्योम rts5261_क्रमce_घातer_करोwn(काष्ठा rtsx_pcr *pcr, u8 pm_state)
अणु
	/* Set relink_समय to 0 */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, AUTOLOAD_CFG_BASE + 1, MASK_8_BIT_DEF, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, AUTOLOAD_CFG_BASE + 2, MASK_8_BIT_DEF, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, AUTOLOAD_CFG_BASE + 3,
				RELINK_TIME_MASK, 0);

	अगर (pm_state == HOST_ENTER_S3)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, pcr->reg_pm_ctrl3,
					D3_DELINK_MODE_EN, D3_DELINK_MODE_EN);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_REG_FPDCTL,
		SSC_POWER_DOWN, SSC_POWER_DOWN);
पूर्ण

अटल पूर्णांक rts5261_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL,
		LED_SHINE_MASK, LED_SHINE_EN);
पूर्ण

अटल पूर्णांक rts5261_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL,
		LED_SHINE_MASK, LED_SHINE_DISABLE);
पूर्ण

अटल पूर्णांक rts5261_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL,
		0x02, 0x02);
पूर्ण

अटल पूर्णांक rts5261_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, GPIO_CTL,
		0x02, 0x00);
पूर्ण

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5261_sd_pull_ctl_enable_tbl[] = अणु
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
अटल स्थिर u32 rts5261_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xD5),
	0,
पूर्ण;

अटल पूर्णांक rts5261_sd_set_sample_push_timing_sd30(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1, SD_MODE_SELECT_MASK
		| SD_ASYNC_FIFO_NOT_RST, SD_30_MODE | SD_ASYNC_FIFO_NOT_RST);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CLK_LOW_FREQ, CLK_LOW_FREQ);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_CLK_SOURCE, 0xFF,
			CRC_VAR_CLK0 | SD30_FIX_CLK | SAMPLE_VAR_CLK1);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CLK_LOW_FREQ, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rts5261_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ocp_en)
		rtsx_pci_enable_ocp(pcr);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CRC_DUMMY_0,
		CFG_SD_POW_AUTO_PD, CFG_SD_POW_AUTO_PD);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG1,
			RTS5261_LDO1_TUNE_MASK, RTS5261_LDO1_33);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1233318_POW_CTL,
			RTS5261_LDO1_POWERON, RTS5261_LDO1_POWERON);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1233318_POW_CTL,
			RTS5261_LDO3318_POWERON, RTS5261_LDO3318_POWERON);

	msleep(20);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, SD_OUTPUT_EN, SD_OUTPUT_EN);

	/* Initialize SD_CFG1 रेजिस्टर */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1, 0xFF,
			SD_CLK_DIVIDE_128 | SD_20_MODE | SD_BUS_WIDTH_1BIT);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_SAMPLE_POINT_CTL,
			0xFF, SD20_RX_POS_EDGE);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PUSH_POINT_CTL, 0xFF, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_STOP, SD_STOP | SD_CLR_ERR,
			SD_STOP | SD_CLR_ERR);

	/* Reset SD_CFG3 रेजिस्टर */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG3, SD30_CLK_END_EN, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_SD_STOP_SDCLK_CFG,
			SD30_CLK_STOP_CFG_EN | SD30_CLK_STOP_CFG1 |
			SD30_CLK_STOP_CFG0, 0);

	अगर (pcr->extra_caps & EXTRA_CAPS_SD_SDR50 ||
	    pcr->extra_caps & EXTRA_CAPS_SD_SDR104)
		rts5261_sd_set_sample_push_timing_sd30(pcr);

	वापस 0;
पूर्ण

अटल पूर्णांक rts5261_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	पूर्णांक err;
	u16 val = 0;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_CARD_PWR_CTL,
			RTS5261_PUPDC, RTS5261_PUPDC);

	चयन (voltage) अणु
	हाल OUTPUT_3V3:
		rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, PHY_TUNE, &val);
		val |= PHY_TUNE_SDBUS_33;
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_TUNE, val);
		अगर (err < 0)
			वापस err;

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_DV3318_CFG,
				RTS5261_DV3318_TUNE_MASK, RTS5261_DV3318_33);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PAD_CTL,
				SD_IO_USING_1V8, 0);
		अवरोध;
	हाल OUTPUT_1V8:
		rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, PHY_TUNE, &val);
		val &= ~PHY_TUNE_SDBUS_33;
		err = rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, PHY_TUNE, val);
		अगर (err < 0)
			वापस err;

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_DV3318_CFG,
				RTS5261_DV3318_TUNE_MASK, RTS5261_DV3318_18);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PAD_CTL,
				SD_IO_USING_1V8, SD_IO_USING_1V8);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set pad drive */
	rts5261_fill_driving(pcr, voltage);

	वापस 0;
पूर्ण

अटल व्योम rts5261_stop_cmd(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBCTLR, STOP_CMD);
	rtsx_pci_ग_लिखोl(pcr, RTSX_HDBCTLR, STOP_DMA);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DMA_RST_CTL_0,
				RTS5260_DMA_RST | RTS5260_ADMA3_RST,
				RTS5260_DMA_RST | RTS5260_ADMA3_RST);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RBCTL, RB_FLUSH, RB_FLUSH);
पूर्ण

अटल व्योम rts5261_card_beक्रमe_घातer_off(काष्ठा rtsx_pcr *pcr)
अणु
	rts5261_stop_cmd(pcr);
	rts5261_चयन_output_voltage(pcr, OUTPUT_3V3);

पूर्ण

अटल व्योम rts5261_enable_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val = 0;

	val = SD_OCP_INT_EN | SD_DETECT_EN;
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG0,
			RTS5261_LDO1_OCP_EN | RTS5261_LDO1_OCP_LMT_EN,
			RTS5261_LDO1_OCP_EN | RTS5261_LDO1_OCP_LMT_EN);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, 0xFF, val);

पूर्ण

अटल व्योम rts5261_disable_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	u8 mask = 0;

	mask = SD_OCP_INT_EN | SD_DETECT_EN;
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG0,
			RTS5261_LDO1_OCP_EN | RTS5261_LDO1_OCP_LMT_EN, 0);

पूर्ण

अटल पूर्णांक rts5261_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err = 0;

	rts5261_card_beक्रमe_घातer_off(pcr);
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1233318_POW_CTL,
				RTS5261_LDO_POWERON_MASK, 0);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CRC_DUMMY_0,
		CFG_SD_POW_AUTO_PD, 0);
	अगर (pcr->option.ocp_en)
		rtsx_pci_disable_ocp(pcr);

	वापस err;
पूर्ण

अटल व्योम rts5261_init_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ocp_en) अणु
		u8 mask, val;

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG0,
			RTS5261_LDO1_OCP_EN | RTS5261_LDO1_OCP_LMT_EN,
			RTS5261_LDO1_OCP_EN | RTS5261_LDO1_OCP_LMT_EN);

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG0,
			RTS5261_LDO1_OCP_THD_MASK, option->sd_800mA_ocp_thd);

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG0,
			RTS5261_LDO1_OCP_LMT_THD_MASK,
			RTS5261_LDO1_LMT_THD_2000);

		mask = SD_OCP_GLITCH_MASK;
		val = pcr->hw_param.ocp_glitch;
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPGLITCH, mask, val);

		rts5261_enable_ocp(pcr);
	पूर्ण अन्यथा अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_LDO1_CFG0,
			RTS5261_LDO1_OCP_EN | RTS5261_LDO1_OCP_LMT_EN, 0);
	पूर्ण
पूर्ण

अटल व्योम rts5261_clear_ocpstat(काष्ठा rtsx_pcr *pcr)
अणु
	u8 mask = 0;
	u8 val = 0;

	mask = SD_OCP_INT_CLR | SD_OC_CLR;
	val = SD_OCP_INT_CLR | SD_OC_CLR;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, val);

	udelay(1000);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, 0);

पूर्ण

अटल व्योम rts5261_process_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (!pcr->option.ocp_en)
		वापस;

	rtsx_pci_get_ocpstat(pcr, &pcr->ocp_stat);

	अगर (pcr->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) अणु
		rts5261_clear_ocpstat(pcr);
		rts5261_card_घातer_off(pcr, RTSX_SD_CARD);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, SD_OUTPUT_EN, 0);
		pcr->ocp_stat = 0;
	पूर्ण

पूर्ण

अटल पूर्णांक rts5261_init_from_hw(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	पूर्णांक retval;
	u32 lval, i;
	u8 valid, efuse_valid, पंचांगp;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_REG_PME_FORCE_CTL,
		REG_EFUSE_POR | REG_EFUSE_POWER_MASK,
		REG_EFUSE_POR | REG_EFUSE_POWERON);
	udelay(1);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_EFUSE_ADDR,
		RTS5261_EFUSE_ADDR_MASK, 0x00);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_EFUSE_CTL,
		RTS5261_EFUSE_ENABLE | RTS5261_EFUSE_MODE_MASK,
		RTS5261_EFUSE_ENABLE);

	/* Wait transfer end */
	क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
		rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS5261_EFUSE_CTL, &पंचांगp);
		अगर ((पंचांगp & 0x80) == 0)
			अवरोध;
	पूर्ण
	rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS5261_EFUSE_READ_DATA, &पंचांगp);
	efuse_valid = ((पंचांगp & 0x0C) >> 2);
	pcr_dbg(pcr, "Load efuse valid: 0x%x\n", efuse_valid);

	अगर (efuse_valid == 0) अणु
		retval = pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &lval);
		अगर (retval != 0)
			pcr_dbg(pcr, "read 0x814 DW fail\n");
		pcr_dbg(pcr, "DW from 0x814: 0x%x\n", lval);
		/* 0x816 */
		valid = (u8)((lval >> 16) & 0x03);
		pcr_dbg(pcr, "0x816: %d\n", valid);
	पूर्ण
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_REG_PME_FORCE_CTL,
		REG_EFUSE_POR, 0);
	pcr_dbg(pcr, "Disable efuse por!\n");

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &lval);
	lval = lval & 0x00FFFFFF;
	retval = pci_ग_लिखो_config_dword(pdev, PCR_SETTING_REG2, lval);
	अगर (retval != 0)
		pcr_dbg(pcr, "write config fail\n");

	वापस retval;
पूर्ण

अटल व्योम rts5261_init_from_cfg(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	पूर्णांक l1ss;
	u32 lval;
	काष्ठा rtsx_cr_option *option = &pcr->option;

	l1ss = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_L1SS);
	अगर (!l1ss)
		वापस;

	pci_पढ़ो_config_dword(pdev, l1ss + PCI_L1SS_CTL1, &lval);

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

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, 0xFF, 0);
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

	अगर (rtsx_check_dev_flag(pcr, ASPM_L1_1_EN | ASPM_L1_2_EN
				| PM_L1_1_EN | PM_L1_2_EN))
		option->क्रमce_clkreq_0 = false;
	अन्यथा
		option->क्रमce_clkreq_0 = true;
पूर्ण

अटल पूर्णांक rts5261_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;
	u32 val;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_AUTOLOAD_CFG1,
			CD_RESUME_EN_MASK, CD_RESUME_EN_MASK);

	rts5261_init_from_cfg(pcr);
	rts5261_init_from_hw(pcr);

	/* घातer off efuse */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_REG_PME_FORCE_CTL,
			REG_EFUSE_POWER_MASK, REG_EFUSE_POWEROFF);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, L1SUB_CONFIG1,
			AUX_CLK_ACTIVE_SEL_MASK, MAC_CKSW_DONE);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, L1SUB_CONFIG3, 0xFF, 0);

	अगर (is_version_higher_than(pcr, PID_5261, IC_VER_B)) अणु
		val = rtsx_pci_पढ़ोl(pcr, RTSX_DUM_REG);
		rtsx_pci_ग_लिखोl(pcr, RTSX_DUM_REG, val | 0x1);
	पूर्ण
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_AUTOLOAD_CFG4,
			RTS5261_AUX_CLK_16M_EN, 0);

	/* Release PRSNT# */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_AUTOLOAD_CFG4,
			RTS5261_FORCE_PRSNT_LOW, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FUNC_FORCE_CTL,
			FUNC_FORCE_UPME_XMT_DBG, FUNC_FORCE_UPME_XMT_DBG);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PCLK_CTL,
			PCLK_MODE_SEL, PCLK_MODE_SEL);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CLK_FORCE_CTL, CLK_PM_EN, CLK_PM_EN);

	/* LED shine disabled, set initial shine cycle period */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL, 0x0F, 0x02);

	/* Configure driving */
	rts5261_fill_driving(pcr, OUTPUT_3V3);

	अगर (pcr->flags & PCR_REVERSE_SOCKET)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PETXCFG, 0x30, 0x30);
	अन्यथा
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PETXCFG, 0x30, 0x00);

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

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWD_SUSPEND_EN, 0xFF, 0xFB);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, pcr->reg_pm_ctrl3, 0x10, 0x00);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_REG_PME_FORCE_CTL,
			FORCE_PM_CONTROL | FORCE_PM_VALUE, FORCE_PM_CONTROL);

	/* Clear Enter RTD3_cold Inक्रमmation*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_FW_CTL,
		RTS5261_INFORM_RTD3_COLD, 0);

	वापस 0;
पूर्ण

अटल व्योम rts5261_enable_aspm(काष्ठा rtsx_pcr *pcr, bool enable)
अणु
	u8 val = FORCE_ASPM_CTL0 | FORCE_ASPM_CTL1;
	u8 mask = FORCE_ASPM_VAL_MASK | FORCE_ASPM_CTL0 | FORCE_ASPM_CTL1;

	अगर (pcr->aspm_enabled == enable)
		वापस;

	val |= (pcr->aspm_en & 0x02);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, mask, val);
	pcie_capability_clear_and_set_word(pcr->pci, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC, pcr->aspm_en);
	pcr->aspm_enabled = enable;
पूर्ण

अटल व्योम rts5261_disable_aspm(काष्ठा rtsx_pcr *pcr, bool enable)
अणु
	u8 val = FORCE_ASPM_CTL0 | FORCE_ASPM_CTL1;
	u8 mask = FORCE_ASPM_VAL_MASK | FORCE_ASPM_CTL0 | FORCE_ASPM_CTL1;

	अगर (pcr->aspm_enabled == enable)
		वापस;

	pcie_capability_clear_and_set_word(pcr->pci, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, mask, val);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1, SD_ASYNC_FIFO_NOT_RST, 0);
	udelay(10);
	pcr->aspm_enabled = enable;
पूर्ण

अटल व्योम rts5261_set_aspm(काष्ठा rtsx_pcr *pcr, bool enable)
अणु
	अगर (enable)
		rts5261_enable_aspm(pcr, true);
	अन्यथा
		rts5261_disable_aspm(pcr, false);
पूर्ण

अटल व्योम rts5261_set_l1off_cfg_sub_d0(काष्ठा rtsx_pcr *pcr, पूर्णांक active)
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

अटल स्थिर काष्ठा pcr_ops rts5261_pcr_ops = अणु
	.fetch_venकरोr_settings = rtsx5261_fetch_venकरोr_settings,
	.turn_on_led = rts5261_turn_on_led,
	.turn_off_led = rts5261_turn_off_led,
	.extra_init_hw = rts5261_extra_init_hw,
	.enable_स्वतः_blink = rts5261_enable_स्वतः_blink,
	.disable_स्वतः_blink = rts5261_disable_स्वतः_blink,
	.card_घातer_on = rts5261_card_घातer_on,
	.card_घातer_off = rts5261_card_घातer_off,
	.चयन_output_voltage = rts5261_चयन_output_voltage,
	.क्रमce_घातer_करोwn = rts5261_क्रमce_घातer_करोwn,
	.stop_cmd = rts5261_stop_cmd,
	.set_aspm = rts5261_set_aspm,
	.set_l1off_cfg_sub_d0 = rts5261_set_l1off_cfg_sub_d0,
	.enable_ocp = rts5261_enable_ocp,
	.disable_ocp = rts5261_disable_ocp,
	.init_ocp = rts5261_init_ocp,
	.process_ocp = rts5261_process_ocp,
	.clear_ocpstat = rts5261_clear_ocpstat,
पूर्ण;

अटल अंतरभूत u8 द्विगुन_ssc_depth(u8 depth)
अणु
	वापस ((depth > 1) ? (depth - 1) : depth);
पूर्ण

पूर्णांक rts5261_pci_चयन_घड़ी(काष्ठा rtsx_pcr *pcr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk)
अणु
	पूर्णांक err, clk;
	u16 n;
	u8 clk_भागider, mcu_cnt, भाग;
	अटल स्थिर u8 depth[] = अणु
		[RTSX_SSC_DEPTH_4M] = RTS5261_SSC_DEPTH_4M,
		[RTSX_SSC_DEPTH_2M] = RTS5261_SSC_DEPTH_2M,
		[RTSX_SSC_DEPTH_1M] = RTS5261_SSC_DEPTH_1M,
		[RTSX_SSC_DEPTH_500K] = RTS5261_SSC_DEPTH_512K,
	पूर्ण;

	अगर (initial_mode) अणु
		/* We use 250k(around) here, in initial stage */
		अगर (is_version_higher_than(pcr, PID_5261, IC_VER_C)) अणु
			clk_भागider = SD_CLK_DIVIDE_256;
			card_घड़ी = 60000000;
		पूर्ण अन्यथा अणु
			clk_भागider = SD_CLK_DIVIDE_128;
			card_घड़ी = 30000000;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_भागider = SD_CLK_DIVIDE_0;
	पूर्ण
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, clk_भागider);
	अगर (err < 0)
		वापस err;

	card_घड़ी /= 1000000;
	pcr_dbg(pcr, "Switch card clock to %dMHz\n", card_घड़ी);

	clk = card_घड़ी;
	अगर (!initial_mode && द्विगुन_clk)
		clk = card_घड़ी * 2;
	pcr_dbg(pcr, "Internal SSC clock: %dMHz (cur_clock = %d)\n",
		clk, pcr->cur_घड़ी);

	अगर (clk == pcr->cur_घड़ी)
		वापस 0;

	अगर (pcr->ops->conv_clk_and_भाग_n)
		n = pcr->ops->conv_clk_and_भाग_n(clk, CLK_TO_DIV_N);
	अन्यथा
		n = clk - 4;
	अगर ((clk <= 4) || (n > 396))
		वापस -EINVAL;

	mcu_cnt = 125/clk + 3;
	अगर (mcu_cnt > 15)
		mcu_cnt = 15;

	भाग = CLK_DIV_1;
	जबतक ((n < MIN_DIV_N_PCR - 4) && (भाग < CLK_DIV_8)) अणु
		अगर (pcr->ops->conv_clk_and_भाग_n) अणु
			पूर्णांक dbl_clk = pcr->ops->conv_clk_and_भाग_n(n,
					DIV_N_TO_CLK) * 2;
			n = pcr->ops->conv_clk_and_भाग_n(dbl_clk,
					CLK_TO_DIV_N);
		पूर्ण अन्यथा अणु
			n = (n + 4) * 2 - 4;
		पूर्ण
		भाग++;
	पूर्ण

	n = (n / 2) - 1;
	pcr_dbg(pcr, "n = %d, div = %d\n", n, भाग);

	ssc_depth = depth[ssc_depth];
	अगर (द्विगुन_clk)
		ssc_depth = द्विगुन_ssc_depth(ssc_depth);

	अगर (ssc_depth) अणु
		अगर (भाग == CLK_DIV_2) अणु
			अगर (ssc_depth > 1)
				ssc_depth -= 1;
			अन्यथा
				ssc_depth = RTS5261_SSC_DEPTH_8M;
		पूर्ण अन्यथा अगर (भाग == CLK_DIV_4) अणु
			अगर (ssc_depth > 2)
				ssc_depth -= 2;
			अन्यथा
				ssc_depth = RTS5261_SSC_DEPTH_8M;
		पूर्ण अन्यथा अगर (भाग == CLK_DIV_8) अणु
			अगर (ssc_depth > 3)
				ssc_depth -= 3;
			अन्यथा
				ssc_depth = RTS5261_SSC_DEPTH_8M;
		पूर्ण
	पूर्ण अन्यथा अणु
		ssc_depth = 0;
	पूर्ण
	pcr_dbg(pcr, "ssc_depth = %d\n", ssc_depth);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL,
				CLK_LOW_FREQ, CLK_LOW_FREQ);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_DIV,
			0xFF, (भाग << 4) | mcu_cnt);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, 0);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL2,
			SSC_DEPTH_MASK, ssc_depth);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_DIV_N_0, 0xFF, n);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, SSC_RSTB);
	अगर (vpclk) अणु
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_VPCLK1_CTL,
				PHASE_NOT_RESET, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, PHASE_NOT_RESET);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_VPCLK1_CTL,
				PHASE_NOT_RESET, PHASE_NOT_RESET);
	पूर्ण

	err = rtsx_pci_send_cmd(pcr, 2000);
	अगर (err < 0)
		वापस err;

	/* Wait SSC घड़ी stable */
	udelay(SSC_CLOCK_STABLE_WAIT);
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CLK_LOW_FREQ, 0);
	अगर (err < 0)
		वापस err;

	pcr->cur_घड़ी = clk;
	वापस 0;

पूर्ण

व्योम rts5261_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;
	काष्ठा rtsx_hw_param *hw_param = &pcr->hw_param;
	u8 val;

	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	rtsx_pci_पढ़ो_रेजिस्टर(pcr, RTS5261_FW_STATUS, &val);
	अगर (!(val & RTS5261_EXPRESS_LINK_FAIL_MASK))
		pcr->extra_caps |= EXTRA_CAPS_SD_EXPRESS;
	pcr->num_slots = 1;
	pcr->ops = &rts5261_pcr_ops;

	pcr->flags = 0;
	pcr->card_drive_sel = RTSX_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = 0x00;
	pcr->sd30_drive_sel_3v3 = 0x00;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_REG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(27, 27, 11);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(24, 6, 5);

	pcr->ic_version = rts5261_get_ic_version(pcr);
	pcr->sd_pull_ctl_enable_tbl = rts5261_sd_pull_ctl_enable_tbl;
	pcr->sd_pull_ctl_disable_tbl = rts5261_sd_pull_ctl_disable_tbl;

	pcr->reg_pm_ctrl3 = RTS5261_AUTOLOAD_CFG3;

	option->dev_flags = (LTR_L1SS_PWR_GATE_CHECK_CARD_EN
				| LTR_L1SS_PWR_GATE_EN);
	option->ltr_en = true;

	/* init latency of active, idle, L1OFF to 60us, 300us, 3ms */
	option->ltr_active_latency = LTR_ACTIVE_LATENCY_DEF;
	option->ltr_idle_latency = LTR_IDLE_LATENCY_DEF;
	option->ltr_l1off_latency = LTR_L1OFF_LATENCY_DEF;
	option->l1_snooze_delay = L1_SNOOZE_DELAY_DEF;
	option->ltr_l1off_sspwrgate = 0x7F;
	option->ltr_l1off_snooze_sspwrgate = 0x78;

	option->ocp_en = 1;
	hw_param->पूर्णांकerrupt_en |= SD_OC_INT_EN;
	hw_param->ocp_glitch =  SD_OCP_GLITCH_800U;
	option->sd_800mA_ocp_thd =  RTS5261_LDO1_OCP_THD_1040;
पूर्ण
