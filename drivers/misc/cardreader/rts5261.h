<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2018-2019 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Rui FENG <rui_feng@realsil.com.cn>
 *   Wei WANG <wei_wang@realsil.com.cn>
 */
#अगर_अघोषित RTS5261_H
#घोषणा RTS5261_H

/*New add*/
#घोषणा rts5261_venकरोr_setting_valid(reg)	((reg) & 0x010000)
#घोषणा rts5261_reg_to_aspm(reg) \
	(((~(reg) >> 28) & 0x02) | (((reg) >> 28) & 0x01))
#घोषणा rts5261_reg_check_reverse_socket(reg)	((reg) & 0x04)
#घोषणा rts5261_reg_to_sd30_drive_sel_1v8(reg)	(((reg) >> 22) & 0x03)
#घोषणा rts5261_reg_to_sd30_drive_sel_3v3(reg)	(((reg) >> 16) & 0x03)
#घोषणा rts5261_reg_to_rtd3(reg)		((reg) & 0x08)
#घोषणा rts5261_reg_check_mmc_support(reg)	((reg) & 0x10)

#घोषणा RTS5261_AUTOLOAD_CFG0		0xFF7B
#घोषणा RTS5261_AUTOLOAD_CFG1		0xFF7C
#घोषणा RTS5261_AUTOLOAD_CFG2		0xFF7D
#घोषणा RTS5261_AUTOLOAD_CFG3		0xFF7E
#घोषणा RTS5261_AUTOLOAD_CFG4		0xFF7F
#घोषणा RTS5261_FORCE_PRSNT_LOW		(1 << 6)
#घोषणा RTS5261_AUX_CLK_16M_EN		(1 << 5)

#घोषणा RTS5261_REG_VREF		0xFE97
#घोषणा RTS5261_PWD_SUSPND_EN		(1 << 4)

#घोषणा RTS5261_PAD_H3L1		0xFF79
#घोषणा PAD_GPIO_H3L1			(1 << 3)

/* SSC_CTL2 0xFC12 */
#घोषणा RTS5261_SSC_DEPTH_MASK		0x07
#घोषणा RTS5261_SSC_DEPTH_DISALBE	0x00
#घोषणा RTS5261_SSC_DEPTH_8M		0x01
#घोषणा RTS5261_SSC_DEPTH_4M		0x02
#घोषणा RTS5261_SSC_DEPTH_2M		0x03
#घोषणा RTS5261_SSC_DEPTH_1M		0x04
#घोषणा RTS5261_SSC_DEPTH_512K		0x05
#घोषणा RTS5261_SSC_DEPTH_256K		0x06
#घोषणा RTS5261_SSC_DEPTH_128K		0x07

/* efuse control रेजिस्टर*/
#घोषणा RTS5261_EFUSE_CTL		0xFC30
#घोषणा RTS5261_EFUSE_ENABLE		0x80
/* EFUSE_MODE: 0=READ 1=PROGRAM */
#घोषणा RTS5261_EFUSE_MODE_MASK		0x40
#घोषणा RTS5261_EFUSE_PROGRAM		0x40

#घोषणा RTS5261_EFUSE_ADDR		0xFC31
#घोषणा	RTS5261_EFUSE_ADDR_MASK		0x3F

#घोषणा RTS5261_EFUSE_WRITE_DATA	0xFC32
#घोषणा RTS5261_EFUSE_READ_DATA		0xFC34

/* DMACTL 0xFE2C */
#घोषणा RTS5261_DMA_PACK_SIZE_MASK	0xF0

/* FW status रेजिस्टर */
#घोषणा RTS5261_FW_STATUS		0xFF56
#घोषणा RTS5261_EXPRESS_LINK_FAIL_MASK	(0x01<<7)

/* FW control रेजिस्टर */
#घोषणा RTS5261_FW_CTL			0xFF5F
#घोषणा RTS5261_INFORM_RTD3_COLD	(0x01<<5)

#घोषणा RTS5261_REG_FPDCTL		0xFF60

#घोषणा RTS5261_REG_LDO12_CFG		0xFF6E
#घोषणा RTS5261_LDO12_VO_TUNE_MASK	(0x07<<1)
#घोषणा RTS5261_LDO12_115		(0x03<<1)
#घोषणा RTS5261_LDO12_120		(0x04<<1)
#घोषणा RTS5261_LDO12_125		(0x05<<1)
#घोषणा RTS5261_LDO12_130		(0x06<<1)
#घोषणा RTS5261_LDO12_135		(0x07<<1)

/* LDO control रेजिस्टर */
#घोषणा RTS5261_CARD_PWR_CTL		0xFD50
#घोषणा RTS5261_SD_CLK_ISO		(0x01<<7)
#घोषणा RTS5261_PAD_SD_DAT_FW_CTRL	(0x01<<6)
#घोषणा RTS5261_PUPDC			(0x01<<5)
#घोषणा RTS5261_SD_CMD_ISO		(0x01<<4)
#घोषणा RTS5261_SD_DAT_ISO_MASK		(0x0F<<0)

#घोषणा RTS5261_LDO1233318_POW_CTL	0xFF70
#घोषणा RTS5261_LDO3318_POWERON		(0x01<<3)
#घोषणा RTS5261_LDO3_POWERON		(0x01<<2)
#घोषणा RTS5261_LDO2_POWERON		(0x01<<1)
#घोषणा RTS5261_LDO1_POWERON		(0x01<<0)
#घोषणा RTS5261_LDO_POWERON_MASK	(0x0F<<0)

#घोषणा RTS5261_DV3318_CFG		0xFF71
#घोषणा RTS5261_DV3318_TUNE_MASK	(0x07<<4)
#घोषणा RTS5261_DV3318_18		(0x02<<4)
#घोषणा RTS5261_DV3318_19		(0x04<<4)
#घोषणा RTS5261_DV3318_33		(0x07<<4)

/* CRD6603-433 190319 request changed */
#घोषणा RTS5261_LDO1_OCP_THD_740	(0x00<<5)
#घोषणा RTS5261_LDO1_OCP_THD_800	(0x01<<5)
#घोषणा RTS5261_LDO1_OCP_THD_860	(0x02<<5)
#घोषणा RTS5261_LDO1_OCP_THD_920	(0x03<<5)
#घोषणा RTS5261_LDO1_OCP_THD_980	(0x04<<5)
#घोषणा RTS5261_LDO1_OCP_THD_1040	(0x05<<5)
#घोषणा RTS5261_LDO1_OCP_THD_1100	(0x06<<5)
#घोषणा RTS5261_LDO1_OCP_THD_1160	(0x07<<5)

#घोषणा RTS5261_LDO1_LMT_THD_450	(0x00<<2)
#घोषणा RTS5261_LDO1_LMT_THD_1000	(0x01<<2)
#घोषणा RTS5261_LDO1_LMT_THD_1500	(0x02<<2)
#घोषणा RTS5261_LDO1_LMT_THD_2000	(0x03<<2)

#घोषणा RTS5261_LDO1_CFG1		0xFF73
#घोषणा RTS5261_LDO1_TUNE_MASK		(0x07<<1)
#घोषणा RTS5261_LDO1_18			(0x05<<1)
#घोषणा RTS5261_LDO1_33			(0x07<<1)
#घोषणा RTS5261_LDO1_PWD_MASK		(0x01<<0)

#घोषणा RTS5261_LDO2_CFG0		0xFF74
#घोषणा RTS5261_LDO2_OCP_THD_MASK	(0x07<<5)
#घोषणा RTS5261_LDO2_OCP_EN		(0x01<<4)
#घोषणा RTS5261_LDO2_OCP_LMT_THD_MASK	(0x03<<2)
#घोषणा RTS5261_LDO2_OCP_LMT_EN		(0x01<<1)

#घोषणा RTS5261_LDO2_OCP_THD_620	(0x00<<5)
#घोषणा RTS5261_LDO2_OCP_THD_650	(0x01<<5)
#घोषणा RTS5261_LDO2_OCP_THD_680	(0x02<<5)
#घोषणा RTS5261_LDO2_OCP_THD_720	(0x03<<5)
#घोषणा RTS5261_LDO2_OCP_THD_750	(0x04<<5)
#घोषणा RTS5261_LDO2_OCP_THD_780	(0x05<<5)
#घोषणा RTS5261_LDO2_OCP_THD_810	(0x06<<5)
#घोषणा RTS5261_LDO2_OCP_THD_840	(0x07<<5)

#घोषणा RTS5261_LDO2_CFG1		0xFF75
#घोषणा RTS5261_LDO2_TUNE_MASK		(0x07<<1)
#घोषणा RTS5261_LDO2_18			(0x05<<1)
#घोषणा RTS5261_LDO2_33			(0x07<<1)
#घोषणा RTS5261_LDO2_PWD_MASK		(0x01<<0)

#घोषणा RTS5261_LDO3_CFG0		0xFF76
#घोषणा RTS5261_LDO3_OCP_THD_MASK	(0x07<<5)
#घोषणा RTS5261_LDO3_OCP_EN		(0x01<<4)
#घोषणा RTS5261_LDO3_OCP_LMT_THD_MASK	(0x03<<2)
#घोषणा RTS5261_LDO3_OCP_LMT_EN		(0x01<<1)

#घोषणा RTS5261_LDO3_OCP_THD_620	(0x00<<5)
#घोषणा RTS5261_LDO3_OCP_THD_650	(0x01<<5)
#घोषणा RTS5261_LDO3_OCP_THD_680	(0x02<<5)
#घोषणा RTS5261_LDO3_OCP_THD_720	(0x03<<5)
#घोषणा RTS5261_LDO3_OCP_THD_750	(0x04<<5)
#घोषणा RTS5261_LDO3_OCP_THD_780	(0x05<<5)
#घोषणा RTS5261_LDO3_OCP_THD_810	(0x06<<5)
#घोषणा RTS5261_LDO3_OCP_THD_840	(0x07<<5)

#घोषणा RTS5261_LDO3_CFG1		0xFF77
#घोषणा RTS5261_LDO3_TUNE_MASK		(0x07<<1)
#घोषणा RTS5261_LDO3_18			(0x05<<1)
#घोषणा RTS5261_LDO3_33			(0x07<<1)
#घोषणा RTS5261_LDO3_PWD_MASK		(0x01<<0)

#घोषणा RTS5261_REG_PME_FORCE_CTL	0xFF78
#घोषणा FORCE_PM_CONTROL		0x20
#घोषणा FORCE_PM_VALUE			0x10
#घोषणा REG_EFUSE_BYPASS		0x08
#घोषणा REG_EFUSE_POR			0x04
#घोषणा REG_EFUSE_POWER_MASK		0x03
#घोषणा REG_EFUSE_POWERON		0x03
#घोषणा REG_EFUSE_POWEROFF		0x00


/* Single LUN, support SD/SD EXPRESS */
#घोषणा DEFAULT_SINGLE		0
#घोषणा SD_LUN			1
#घोषणा SD_EXPRESS_LUN		2

/* For Change_FPGA_SSCClock Function */
#घोषणा MULTIPLY_BY_1    0x00
#घोषणा MULTIPLY_BY_2    0x01
#घोषणा MULTIPLY_BY_3    0x02
#घोषणा MULTIPLY_BY_4    0x03
#घोषणा MULTIPLY_BY_5    0x04
#घोषणा MULTIPLY_BY_6    0x05
#घोषणा MULTIPLY_BY_7    0x06
#घोषणा MULTIPLY_BY_8    0x07
#घोषणा MULTIPLY_BY_9    0x08
#घोषणा MULTIPLY_BY_10   0x09

#घोषणा DIVIDE_BY_2      0x01
#घोषणा DIVIDE_BY_3      0x02
#घोषणा DIVIDE_BY_4      0x03
#घोषणा DIVIDE_BY_5      0x04
#घोषणा DIVIDE_BY_6      0x05
#घोषणा DIVIDE_BY_7      0x06
#घोषणा DIVIDE_BY_8      0x07
#घोषणा DIVIDE_BY_9      0x08
#घोषणा DIVIDE_BY_10     0x09

पूर्णांक rts5261_pci_चयन_घड़ी(काष्ठा rtsx_pcr *pcr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk);

#पूर्ण_अगर /* RTS5261_H */
