<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2016-2017 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Steven FENG <steven_feng@realsil.com.cn>
 *   Rui FENG <rui_feng@realsil.com.cn>
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtsx_pci.h>

#समावेश "rts5260.h"
#समावेश "rtsx_pcr.h"

अटल u8 rts5260_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, DUMMY_REG_RESET_0, &val);
	वापस val & IC_VERSION_MASK;
पूर्ण

अटल व्योम rts5260_fill_driving(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	u8 driving_3v3[4][3] = अणु
		अणु0x11, 0x11, 0x11पूर्ण,
		अणु0x22, 0x22, 0x22पूर्ण,
		अणु0x55, 0x55, 0x55पूर्ण,
		अणु0x33, 0x33, 0x33पूर्ण,
	पूर्ण;
	u8 driving_1v8[4][3] = अणु
		अणु0x35, 0x33, 0x33पूर्ण,
		अणु0x8A, 0x88, 0x88पूर्ण,
		अणु0xBD, 0xBB, 0xBBपूर्ण,
		अणु0x9B, 0x99, 0x99पूर्ण,
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
	अगर (rtsx_check_mmc_support(reg))
		pcr->extra_caps |= EXTRA_CAPS_NO_MMC;
	pcr->sd30_drive_sel_3v3 = rtsx_reg_to_sd30_drive_sel_3v3(reg);
	अगर (rtsx_reg_check_reverse_socket(reg))
		pcr->flags |= PCR_REVERSE_SOCKET;
पूर्ण

अटल पूर्णांक rtsx_base_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL,
		LED_SHINE_MASK, LED_SHINE_EN);
पूर्ण

अटल पूर्णांक rtsx_base_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, OLT_LED_CTL,
		LED_SHINE_MASK, LED_SHINE_DISABLE);
पूर्ण

अटल पूर्णांक rts5260_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_REG_GPIO_CTL0,
		RTS5260_REG_GPIO_MASK, RTS5260_REG_GPIO_ON);
पूर्ण

अटल पूर्णांक rts5260_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_REG_GPIO_CTL0,
		RTS5260_REG_GPIO_MASK, RTS5260_REG_GPIO_OFF);
पूर्ण

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5260_sd_pull_ctl_enable_tbl[] = अणु
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
अटल स्थिर u32 rts5260_sd_pull_ctl_disable_tbl[] = अणु
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
अटल स्थिर u32 rts5260_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

/* MS Pull Control Disable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5260_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

अटल पूर्णांक sd_set_sample_push_timing_sd30(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1, SD_MODE_SELECT_MASK
		| SD_ASYNC_FIFO_NOT_RST, SD_30_MODE | SD_ASYNC_FIFO_NOT_RST);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CLK_LOW_FREQ, CLK_LOW_FREQ);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_CLK_SOURCE, 0xFF,
			CRC_VAR_CLK0 | SD30_FIX_CLK | SAMPLE_VAR_CLK1);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CLK_LOW_FREQ, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rts5260_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ocp_en)
		rtsx_pci_enable_ocp(pcr);


	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2, DV331812_VDD1, DV331812_VDD1);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG0,
			 RTS5260_DVCC_TUNE_MASK, RTS5260_DVCC_33);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG1, LDO_POW_SDVDD1_MASK,
			LDO_POW_SDVDD1_ON);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2,
			 DV331812_POWERON, DV331812_POWERON);
	msleep(20);

	अगर (pcr->extra_caps & EXTRA_CAPS_SD_SDR50 ||
	    pcr->extra_caps & EXTRA_CAPS_SD_SDR104)
		sd_set_sample_push_timing_sd30(pcr);

	/* Initialize SD_CFG1 रेजिस्टर */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1, 0xFF,
				SD_CLK_DIVIDE_128 | SD_20_MODE);

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

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_PRE_RW_MODE, EN_INFINITE_MODE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rts5260_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	चयन (voltage) अणु
	हाल OUTPUT_3V3:
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2,
					DV331812_VDD1, DV331812_VDD1);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_DV18_CFG,
					DV331812_MASK, DV331812_33);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PAD_CTL, SD_IO_USING_1V8, 0);
		अवरोध;
	हाल OUTPUT_1V8:
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2,
					DV331812_VDD1, DV331812_VDD1);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_DV18_CFG,
					DV331812_MASK, DV331812_17);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_PAD_CTL, SD_IO_USING_1V8,
					SD_IO_USING_1V8);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set pad drive */
	rts5260_fill_driving(pcr, voltage);

	वापस 0;
पूर्ण

अटल व्योम rts5260_stop_cmd(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBCTLR, STOP_CMD);
	rtsx_pci_ग_लिखोl(pcr, RTSX_HDBCTLR, STOP_DMA);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DMA_RST_CTL_0,
				RTS5260_DMA_RST | RTS5260_ADMA3_RST,
				RTS5260_DMA_RST | RTS5260_ADMA3_RST);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RBCTL, RB_FLUSH, RB_FLUSH);
पूर्ण

अटल व्योम rts5260_card_beक्रमe_घातer_off(काष्ठा rtsx_pcr *pcr)
अणु
	rts5260_stop_cmd(pcr);
	rts5260_चयन_output_voltage(pcr, OUTPUT_3V3);

पूर्ण

अटल पूर्णांक rts5260_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err = 0;

	rts5260_card_beक्रमe_घातer_off(pcr);
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG1,
			 LDO_POW_SDVDD1_MASK, LDO_POW_SDVDD1_OFF);
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_CONFIG2,
			 DV331812_POWERON, DV331812_POWEROFF);
	अगर (pcr->option.ocp_en)
		rtsx_pci_disable_ocp(pcr);

	वापस err;
पूर्ण

अटल व्योम rts5260_init_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ocp_en) अणु
		u8 mask, val;


		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DVCC_CTRL,
				RTS5260_DVCC_OCP_THD_MASK,
				option->sd_800mA_ocp_thd);

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DV331812_CFG,
				RTS5260_DV331812_OCP_THD_MASK,
				RTS5260_DV331812_OCP_THD_270);

		mask = SD_OCP_GLITCH_MASK;
		val = pcr->hw_param.ocp_glitch;
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPGLITCH, mask, val);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DVCC_CTRL,
					RTS5260_DVCC_OCP_EN |
					RTS5260_DVCC_OCP_CL_EN,
					RTS5260_DVCC_OCP_EN |
					RTS5260_DVCC_OCP_CL_EN);

		rtsx_pci_enable_ocp(pcr);
	पूर्ण अन्यथा अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DVCC_CTRL,
					RTS5260_DVCC_OCP_EN |
					RTS5260_DVCC_OCP_CL_EN, 0);
	पूर्ण
पूर्ण

अटल व्योम rts5260_enable_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val = 0;

	val = SD_OCP_INT_EN | SD_DETECT_EN;
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, 0xFF, val);

पूर्ण

अटल व्योम rts5260_disable_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	u8 mask = 0;

	mask = SD_OCP_INT_EN | SD_DETECT_EN;
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, 0);

पूर्ण


अटल पूर्णांक rts5260_get_ocpstat(काष्ठा rtsx_pcr *pcr, u8 *val)
अणु
	वापस rtsx_pci_पढ़ो_रेजिस्टर(pcr, REG_OCPSTAT, val);
पूर्ण

अटल पूर्णांक rts5260_get_ocpstat2(काष्ठा rtsx_pcr *pcr, u8 *val)
अणु
	वापस rtsx_pci_पढ़ो_रेजिस्टर(pcr, REG_DV3318_OCPSTAT, val);
पूर्ण

अटल व्योम rts5260_clear_ocpstat(काष्ठा rtsx_pcr *pcr)
अणु
	u8 mask = 0;
	u8 val = 0;

	mask = SD_OCP_INT_CLR | SD_OC_CLR;
	val = SD_OCP_INT_CLR | SD_OC_CLR;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, val);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_DV3318_OCPCTL,
				DV3318_OCP_INT_CLR | DV3318_OCP_CLR,
				DV3318_OCP_INT_CLR | DV3318_OCP_CLR);
	udelay(10);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_DV3318_OCPCTL,
				DV3318_OCP_INT_CLR | DV3318_OCP_CLR, 0);
पूर्ण

अटल व्योम rts5260_process_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (!pcr->option.ocp_en)
		वापस;

	rtsx_pci_get_ocpstat(pcr, &pcr->ocp_stat);
	rts5260_get_ocpstat2(pcr, &pcr->ocp_stat2);

	अगर ((pcr->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) ||
		(pcr->ocp_stat2 & (DV3318_OCP_NOW | DV3318_OCP_EVER))) अणु
		rtsx_pci_card_घातer_off(pcr, RTSX_SD_CARD);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, SD_OUTPUT_EN, 0);
		rtsx_pci_clear_ocpstat(pcr);
		pcr->ocp_stat = 0;
		pcr->ocp_stat2 = 0;
	पूर्ण

पूर्ण

अटल पूर्णांक rts5260_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, L1SUB_CONFIG1,
			 AUX_CLK_ACTIVE_SEL_MASK, MAC_CKSW_DONE);
	/* Rest L1SUB Config */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, L1SUB_CONFIG3, 0xFF, 0x00);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PM_CLK_FORCE_CTL,
			 CLK_PM_EN, CLK_PM_EN);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWD_SUSPEND_EN, 0xFF, 0xFF);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			 PWR_GATE_EN, PWR_GATE_EN);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, REG_VREF,
			 PWD_SUSPND_EN, PWD_SUSPND_EN);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, RBCTL,
			 U_AUTO_DMA_EN_MASK, U_AUTO_DMA_DISABLE);

	अगर (pcr->flags & PCR_REVERSE_SOCKET)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB0, 0xB0);
	अन्यथा
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB0, 0x80);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OBFF_CFG,
			 OBFF_EN_MASK, OBFF_DISABLE);

	err = rtsx_pci_send_cmd(pcr, CMD_TIMEOUT_DEF);
	अगर (err < 0)
		वापस err;

	rtsx_pci_init_ocp(pcr);

	वापस 0;
पूर्ण

अटल व्योम rts5260_pwr_saving_setting(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक lss_l1_1, lss_l1_2;

	lss_l1_1 = rtsx_check_dev_flag(pcr, ASPM_L1_1_EN)
			| rtsx_check_dev_flag(pcr, PM_L1_1_EN);
	lss_l1_2 = rtsx_check_dev_flag(pcr, ASPM_L1_2_EN)
			| rtsx_check_dev_flag(pcr, PM_L1_2_EN);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, 0xFF, 0);
	अगर (lss_l1_2) अणु
		pcr_dbg(pcr, "Set parameters for L1.2.");
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_GLOBAL_CTRL,
					0xFF, PCIE_L1_2_EN);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_DVCC_CTRL,
					RTS5260_DVCC_OCP_EN |
					RTS5260_DVCC_OCP_CL_EN,
					RTS5260_DVCC_OCP_EN |
					RTS5260_DVCC_OCP_CL_EN);

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_FE_CTL,
					0xFF, PCIE_L1_2_PD_FE_EN);
	पूर्ण अन्यथा अगर (lss_l1_1) अणु
		pcr_dbg(pcr, "Set parameters for L1.1.");
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_GLOBAL_CTRL,
					0xFF, PCIE_L1_1_EN);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_FE_CTL,
					0xFF, PCIE_L1_1_PD_FE_EN);
	पूर्ण अन्यथा अणु
		pcr_dbg(pcr, "Set parameters for L1.");
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_GLOBAL_CTRL,
					0xFF, PCIE_L1_0_EN);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWR_FE_CTL,
					0xFF, PCIE_L1_0_PD_FE_EN);
	पूर्ण

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_L1_0_PCIE_DPHY_RET_VALUE,
				0xFF, CFG_L1_0_RET_VALUE_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_L1_0_PCIE_MAC_RET_VALUE,
				0xFF, CFG_L1_0_RET_VALUE_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_L1_0_CRC_SD30_RET_VALUE,
				0xFF, CFG_L1_0_RET_VALUE_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_L1_0_CRC_SD40_RET_VALUE,
				0xFF, CFG_L1_0_RET_VALUE_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_L1_0_SYS_RET_VALUE,
				0xFF, CFG_L1_0_RET_VALUE_DEFAULT);
	/*Option cut APHY*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_PCIE_APHY_OFF_0,
				0xFF, CFG_PCIE_APHY_OFF_0_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_PCIE_APHY_OFF_1,
				0xFF, CFG_PCIE_APHY_OFF_1_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_PCIE_APHY_OFF_2,
				0xFF, CFG_PCIE_APHY_OFF_2_DEFAULT);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_PCIE_APHY_OFF_3,
				0xFF, CFG_PCIE_APHY_OFF_3_DEFAULT);
	/*CDR DEC*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PWC_CDR, 0xFF, PWC_CDR_DEFAULT);
	/*PWMPFM*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_LP_FPWM_VALUE,
				0xFF, CFG_LP_FPWM_VALUE_DEFAULT);
	/*No Power Saving WA*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CFG_L1_0_CRC_MISC_RET_VALUE,
				0xFF, CFG_L1_0_CRC_MISC_RET_VALUE_DEFAULT);
पूर्ण

अटल व्योम rts5260_init_from_cfg(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	पूर्णांक l1ss;
	काष्ठा rtsx_cr_option *option = &pcr->option;
	u32 lval;

	l1ss = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_L1SS);
	अगर (!l1ss)
		वापस;

	pci_पढ़ो_config_dword(pdev, l1ss + PCI_L1SS_CTL1, &lval);

	अगर (lval & PCI_L1SS_CTL1_ASPM_L1_1)
		rtsx_set_dev_flag(pcr, ASPM_L1_1_EN);

	अगर (lval & PCI_L1SS_CTL1_ASPM_L1_2)
		rtsx_set_dev_flag(pcr, ASPM_L1_2_EN);

	अगर (lval & PCI_L1SS_CTL1_PCIPM_L1_1)
		rtsx_set_dev_flag(pcr, PM_L1_1_EN);

	अगर (lval & PCI_L1SS_CTL1_PCIPM_L1_2)
		rtsx_set_dev_flag(pcr, PM_L1_2_EN);

	rts5260_pwr_saving_setting(pcr);

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

अटल पूर्णांक rts5260_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	/* Set mcu_cnt to 7 to ensure data can be sampled properly */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, 0xFC03, 0x7F, 0x07);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SSC_DIV_N_0, 0xFF, 0x5D);

	rts5260_init_from_cfg(pcr);

	/* क्रमce no MDIO*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5260_AUTOLOAD_CFG4,
				0xFF, RTS5260_MIMO_DISABLE);
	/*Modअगरy SDVCC Tune Default Parameters!*/
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LDO_VCC_CFG0,
				RTS5260_DVCC_TUNE_MASK, RTS5260_DVCC_33);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PCLK_CTL, PCLK_MODE_SEL, PCLK_MODE_SEL);

	rts5260_init_hw(pcr);

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

	वापस 0;
पूर्ण

अटल व्योम rts5260_set_l1off_cfg_sub_d0(काष्ठा rtsx_pcr *pcr, पूर्णांक active)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;
	u32 पूर्णांकerrupt = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	पूर्णांक card_exist = (पूर्णांकerrupt & SD_EXIST) | (पूर्णांकerrupt & MS_EXIST);
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

अटल स्थिर काष्ठा pcr_ops rts5260_pcr_ops = अणु
	.fetch_venकरोr_settings = rtsx_base_fetch_venकरोr_settings,
	.turn_on_led = rts5260_turn_on_led,
	.turn_off_led = rts5260_turn_off_led,
	.extra_init_hw = rts5260_extra_init_hw,
	.enable_स्वतः_blink = rtsx_base_enable_स्वतः_blink,
	.disable_स्वतः_blink = rtsx_base_disable_स्वतः_blink,
	.card_घातer_on = rts5260_card_घातer_on,
	.card_घातer_off = rts5260_card_घातer_off,
	.चयन_output_voltage = rts5260_चयन_output_voltage,
	.stop_cmd = rts5260_stop_cmd,
	.set_l1off_cfg_sub_d0 = rts5260_set_l1off_cfg_sub_d0,
	.enable_ocp = rts5260_enable_ocp,
	.disable_ocp = rts5260_disable_ocp,
	.init_ocp = rts5260_init_ocp,
	.process_ocp = rts5260_process_ocp,
	.get_ocpstat = rts5260_get_ocpstat,
	.clear_ocpstat = rts5260_clear_ocpstat,
पूर्ण;

व्योम rts5260_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;
	काष्ठा rtsx_hw_param *hw_param = &pcr->hw_param;

	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	pcr->num_slots = 2;

	pcr->flags = 0;
	pcr->card_drive_sel = RTSX_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = CFG_DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = CFG_DRIVER_TYPE_B;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_REG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(27, 29, 11);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(24, 6, 5);

	pcr->ic_version = rts5260_get_ic_version(pcr);
	pcr->sd_pull_ctl_enable_tbl = rts5260_sd_pull_ctl_enable_tbl;
	pcr->sd_pull_ctl_disable_tbl = rts5260_sd_pull_ctl_disable_tbl;
	pcr->ms_pull_ctl_enable_tbl = rts5260_ms_pull_ctl_enable_tbl;
	pcr->ms_pull_ctl_disable_tbl = rts5260_ms_pull_ctl_disable_tbl;

	pcr->reg_pm_ctrl3 = RTS524A_PM_CTRL3;

	pcr->ops = &rts5260_pcr_ops;

	option->dev_flags = (LTR_L1SS_PWR_GATE_CHECK_CARD_EN
				| LTR_L1SS_PWR_GATE_EN);
	option->ltr_en = true;

	/* init latency of active, idle, L1OFF to 60us, 300us, 3ms */
	option->ltr_active_latency = LTR_ACTIVE_LATENCY_DEF;
	option->ltr_idle_latency = LTR_IDLE_LATENCY_DEF;
	option->ltr_l1off_latency = LTR_L1OFF_LATENCY_DEF;
	option->l1_snooze_delay = L1_SNOOZE_DELAY_DEF;
	option->ltr_l1off_sspwrgate = LTR_L1OFF_SSPWRGATE_5250_DEF;
	option->ltr_l1off_snooze_sspwrgate =
		LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF;

	option->ocp_en = 1;
	अगर (option->ocp_en)
		hw_param->पूर्णांकerrupt_en |= SD_OC_INT_EN;
	hw_param->ocp_glitch =  SD_OCP_GLITCH_100U | SDVIO_OCP_GLITCH_800U;
	option->sd_400mA_ocp_thd = RTS5260_DVCC_OCP_THD_550;
	option->sd_800mA_ocp_thd = RTS5260_DVCC_OCP_THD_970;
पूर्ण
