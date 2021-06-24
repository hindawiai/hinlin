<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#अगर_अघोषित __RTSX_PCR_H
#घोषणा __RTSX_PCR_H

#समावेश <linux/rtsx_pci.h>

#घोषणा MIN_DIV_N_PCR		80
#घोषणा MAX_DIV_N_PCR		208

#घोषणा RTS522A_PM_CTRL3		0xFF7E

#घोषणा RTS524A_PME_FORCE_CTL		0xFF78
#घोषणा REG_EFUSE_BYPASS		0x08
#घोषणा REG_EFUSE_POR			0x04
#घोषणा REG_EFUSE_POWER_MASK		0x03
#घोषणा REG_EFUSE_POWERON		0x03
#घोषणा REG_EFUSE_POWEROFF		0x00
#घोषणा RTS5250_CLK_CFG3		0xFF79
#घोषणा RTS525A_CFG_MEM_PD		0xF0
#घोषणा RTS524A_PM_CTRL3		0xFF7E
#घोषणा RTS525A_BIOS_CFG		0xFF2D
#घोषणा RTS525A_LOAD_BIOS_FLAG	0x01
#घोषणा RTS525A_CLEAR_BIOS_FLAG	0x00

#घोषणा RTS525A_EFUSE_CTL		0xFC32
#घोषणा REG_EFUSE_ENABLE		0x80
#घोषणा REG_EFUSE_MODE			0x40
#घोषणा RTS525A_EFUSE_ADD		0xFC33
#घोषणा REG_EFUSE_ADD_MASK		0x3F
#घोषणा RTS525A_EFUSE_DATA		0xFC35

#घोषणा LTR_ACTIVE_LATENCY_DEF		0x883C
#घोषणा LTR_IDLE_LATENCY_DEF		0x892C
#घोषणा LTR_L1OFF_LATENCY_DEF		0x9003
#घोषणा L1_SNOOZE_DELAY_DEF		1
#घोषणा LTR_L1OFF_SSPWRGATE_5249_DEF		0xAF
#घोषणा LTR_L1OFF_SSPWRGATE_5250_DEF		0xFF
#घोषणा LTR_L1OFF_SNOOZE_SSPWRGATE_5249_DEF	0xAC
#घोषणा LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF	0xF8
#घोषणा CMD_TIMEOUT_DEF		100
#घोषणा MASK_8_BIT_DEF		0xFF

#घोषणा SSC_CLOCK_STABLE_WAIT	130

#घोषणा RTS524A_OCP_THD_800	0x04
#घोषणा RTS525A_OCP_THD_800	0x05
#घोषणा RTS522A_OCP_THD_800	0x06


पूर्णांक __rtsx_pci_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 val);
पूर्णांक __rtsx_pci_पढ़ो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 *val);

व्योम rts5209_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts5229_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rtl8411_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rtl8402_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts5227_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts522a_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts5249_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts524a_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts525a_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rtl8411b_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts5260_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts5261_init_params(काष्ठा rtsx_pcr *pcr);
व्योम rts5228_init_params(काष्ठा rtsx_pcr *pcr);

अटल अंतरभूत u8 map_sd_drive(पूर्णांक idx)
अणु
	u8 sd_drive[4] = अणु
		0x01,	/* Type D */
		0x02,	/* Type C */
		0x05,	/* Type A */
		0x03	/* Type B */
	पूर्ण;

	वापस sd_drive[idx];
पूर्ण

#घोषणा rtsx_venकरोr_setting_valid(reg)		(!((reg) & 0x1000000))
#घोषणा rts5209_venकरोr_setting1_valid(reg)	(!((reg) & 0x80))
#घोषणा rts5209_venकरोr_setting2_valid(reg)	((reg) & 0x80)

#घोषणा rtsx_check_mmc_support(reg)		((reg) & 0x10)
#घोषणा rtsx_reg_to_rtd3(reg)				((reg) & 0x02)
#घोषणा rtsx_reg_to_rtd3_uhsii(reg)				((reg) & 0x04)
#घोषणा rtsx_reg_to_aspm(reg)			(((reg) >> 28) & 0x03)
#घोषणा rtsx_reg_to_sd30_drive_sel_1v8(reg)	(((reg) >> 26) & 0x03)
#घोषणा rtsx_reg_to_sd30_drive_sel_3v3(reg)	(((reg) >> 5) & 0x03)
#घोषणा rtsx_reg_to_card_drive_sel(reg)		((((reg) >> 25) & 0x01) << 6)
#घोषणा rtsx_reg_check_reverse_socket(reg)	((reg) & 0x4000)
#घोषणा rts5209_reg_to_aspm(reg)		(((reg) >> 5) & 0x03)
#घोषणा rts5209_reg_check_ms_pmos(reg)		(!((reg) & 0x08))
#घोषणा rts5209_reg_to_sd30_drive_sel_1v8(reg)	(((reg) >> 3) & 0x07)
#घोषणा rts5209_reg_to_sd30_drive_sel_3v3(reg)	((reg) & 0x07)
#घोषणा rts5209_reg_to_card_drive_sel(reg)	((reg) >> 8)
#घोषणा rtl8411_reg_to_sd30_drive_sel_3v3(reg)	(((reg) >> 5) & 0x07)
#घोषणा rtl8411b_reg_to_sd30_drive_sel_3v3(reg)	((reg) & 0x03)

#घोषणा set_pull_ctrl_tables(pcr, __device)				\
करो अणु									\
	pcr->sd_pull_ctl_enable_tbl  = __device##_sd_pull_ctl_enable_tbl;  \
	pcr->sd_pull_ctl_disable_tbl = __device##_sd_pull_ctl_disable_tbl; \
	pcr->ms_pull_ctl_enable_tbl  = __device##_ms_pull_ctl_enable_tbl;  \
	pcr->ms_pull_ctl_disable_tbl = __device##_ms_pull_ctl_disable_tbl; \
पूर्ण जबतक (0)

/* generic operations */
पूर्णांक rtsx_gops_pm_reset(काष्ठा rtsx_pcr *pcr);
पूर्णांक rtsx_set_ltr_latency(काष्ठा rtsx_pcr *pcr, u32 latency);
पूर्णांक rtsx_set_l1off_sub(काष्ठा rtsx_pcr *pcr, u8 val);
व्योम rtsx_pci_init_ocp(काष्ठा rtsx_pcr *pcr);
व्योम rtsx_pci_disable_ocp(काष्ठा rtsx_pcr *pcr);
व्योम rtsx_pci_enable_ocp(काष्ठा rtsx_pcr *pcr);
पूर्णांक rtsx_pci_get_ocpstat(काष्ठा rtsx_pcr *pcr, u8 *val);
व्योम rtsx_pci_clear_ocpstat(काष्ठा rtsx_pcr *pcr);
व्योम rtsx_pci_enable_oobs_polling(काष्ठा rtsx_pcr *pcr);
व्योम rtsx_pci_disable_oobs_polling(काष्ठा rtsx_pcr *pcr);
पूर्णांक rtsx_sd_घातer_off_card3v3(काष्ठा rtsx_pcr *pcr);
पूर्णांक rtsx_ms_घातer_off_card3v3(काष्ठा rtsx_pcr *pcr);

#पूर्ण_अगर
