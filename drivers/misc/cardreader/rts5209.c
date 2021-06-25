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

अटल u8 rts5209_get_ic_version(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val;

	val = rtsx_pci_पढ़ोb(pcr, 0x1C);
	वापस val & 0x0F;
पूर्ण

अटल व्योम rts5209_fetch_venकरोr_settings(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	u32 reg;

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	अगर (rts5209_venकरोr_setting1_valid(reg)) अणु
		अगर (rts5209_reg_check_ms_pmos(reg))
			pcr->flags |= PCR_MS_PMOS;
		pcr->aspm_en = rts5209_reg_to_aspm(reg);
	पूर्ण

	pci_पढ़ो_config_dword(pdev, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);

	अगर (rts5209_venकरोr_setting2_valid(reg)) अणु
		pcr->sd30_drive_sel_1v8 =
			rts5209_reg_to_sd30_drive_sel_1v8(reg);
		pcr->sd30_drive_sel_3v3 =
			rts5209_reg_to_sd30_drive_sel_3v3(reg);
		pcr->card_drive_sel = rts5209_reg_to_card_drive_sel(reg);
	पूर्ण
पूर्ण

अटल व्योम rts5209_क्रमce_घातer_करोwn(काष्ठा rtsx_pcr *pcr, u8 pm_state)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, 0x07, 0x07);
पूर्ण

अटल पूर्णांक rts5209_extra_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_init_cmd(pcr);

	/* Turn off LED */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_GPIO, 0xFF, 0x03);
	/* Reset ASPM state to शेष value */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, ASPM_FORCE_CTL, 0x3F, 0);
	/* Force CLKREQ# PIN to drive 0 to request घड़ी */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0x08, 0x08);
	/* Configure GPIO as output */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_GPIO_सूची, 0xFF, 0x03);
	/* Configure driving */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_DRIVE_SEL,
			0xFF, pcr->sd30_drive_sel_3v3);

	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5209_optimize_phy(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x00, 0xB966);
पूर्ण

अटल पूर्णांक rts5209_turn_on_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_GPIO, 0x01, 0x00);
पूर्ण

अटल पूर्णांक rts5209_turn_off_led(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_GPIO, 0x01, 0x01);
पूर्ण

अटल पूर्णांक rts5209_enable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_AUTO_BLINK, 0xFF, 0x0D);
पूर्ण

अटल पूर्णांक rts5209_disable_स्वतः_blink(काष्ठा rtsx_pcr *pcr)
अणु
	वापस rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_AUTO_BLINK, 0x08, 0x00);
पूर्ण

अटल पूर्णांक rts5209_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	पूर्णांक err;
	u8 pwr_mask, partial_pwr_on, pwr_on;

	pwr_mask = SD_POWER_MASK;
	partial_pwr_on = SD_PARTIAL_POWER_ON;
	pwr_on = SD_POWER_ON;

	अगर ((pcr->flags & PCR_MS_PMOS) && (card == RTSX_MS_CARD)) अणु
		pwr_mask = MS_POWER_MASK;
		partial_pwr_on = MS_PARTIAL_POWER_ON;
		pwr_on = MS_POWER_ON;
	पूर्ण

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			pwr_mask, partial_pwr_on);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x04);
	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	/* To aव्योम too large in-rush current */
	udelay(150);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL, pwr_mask, pwr_on);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x00);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5209_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	u8 pwr_mask, pwr_off;

	pwr_mask = SD_POWER_MASK;
	pwr_off = SD_POWER_OFF;

	अगर ((pcr->flags & PCR_MS_PMOS) && (card == RTSX_MS_CARD)) अणु
		pwr_mask = MS_POWER_MASK;
		pwr_off = MS_POWER_OFF;
	पूर्ण

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			pwr_mask | PMOS_STRG_MASK, pwr_off | PMOS_STRG_400mA);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x06);
	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

अटल पूर्णांक rts5209_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
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

अटल स्थिर काष्ठा pcr_ops rts5209_pcr_ops = अणु
	.fetch_venकरोr_settings = rts5209_fetch_venकरोr_settings,
	.extra_init_hw = rts5209_extra_init_hw,
	.optimize_phy = rts5209_optimize_phy,
	.turn_on_led = rts5209_turn_on_led,
	.turn_off_led = rts5209_turn_off_led,
	.enable_स्वतः_blink = rts5209_enable_स्वतः_blink,
	.disable_स्वतः_blink = rts5209_disable_स्वतः_blink,
	.card_घातer_on = rts5209_card_घातer_on,
	.card_घातer_off = rts5209_card_घातer_off,
	.चयन_output_voltage = rts5209_चयन_output_voltage,
	.cd_deglitch = शून्य,
	.conv_clk_and_भाग_n = शून्य,
	.क्रमce_घातer_करोwn = rts5209_क्रमce_घातer_करोwn,
पूर्ण;

/* SD Pull Control Enable:
 *     SD_DAT[3:0] ==> pull up
 *     SD_CD       ==> pull up
 *     SD_WP       ==> pull up
 *     SD_CMD      ==> pull up
 *     SD_CLK      ==> pull करोwn
 */
अटल स्थिर u32 rts5209_sd_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0xAA),
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
अटल स्थिर u32 rts5209_sd_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL1, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL2, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL3, 0xD5),
	0,
पूर्ण;

/* MS Pull Control Enable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5209_ms_pull_ctl_enable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

/* MS Pull Control Disable:
 *     MS CD       ==> pull up
 *     others      ==> pull करोwn
 */
अटल स्थिर u32 rts5209_ms_pull_ctl_disable_tbl[] = अणु
	RTSX_REG_PAIR(CARD_PULL_CTL4, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL5, 0x55),
	RTSX_REG_PAIR(CARD_PULL_CTL6, 0x15),
	0,
पूर्ण;

व्योम rts5209_init_params(काष्ठा rtsx_pcr *pcr)
अणु
	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 |
		EXTRA_CAPS_SD_SDR104 | EXTRA_CAPS_MMC_8BIT;
	pcr->num_slots = 2;
	pcr->ops = &rts5209_pcr_ops;

	pcr->flags = 0;
	pcr->card_drive_sel = RTS5209_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = DRIVER_TYPE_D;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->aspm_mode = ASPM_MODE_CFG;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(27, 27, 16);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(24, 6, 5);

	pcr->ic_version = rts5209_get_ic_version(pcr);
	pcr->sd_pull_ctl_enable_tbl = rts5209_sd_pull_ctl_enable_tbl;
	pcr->sd_pull_ctl_disable_tbl = rts5209_sd_pull_ctl_disable_tbl;
	pcr->ms_pull_ctl_enable_tbl = rts5209_ms_pull_ctl_enable_tbl;
	pcr->ms_pull_ctl_disable_tbl = rts5209_ms_pull_ctl_disable_tbl;
पूर्ण
