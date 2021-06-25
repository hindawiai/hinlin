<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2018-2019 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Ricky WU <ricky_wu@realtek.com>
 *   Rui FENG <rui_feng@realsil.com.cn>
 *   Wei WANG <wei_wang@realsil.com.cn>
 */
#अगर_अघोषित RTS5228_H
#घोषणा RTS5228_H


#घोषणा RTS5228_AUTOLOAD_CFG0			0xFF7B
#घोषणा RTS5228_AUTOLOAD_CFG1			0xFF7C
#घोषणा RTS5228_AUTOLOAD_CFG2			0xFF7D
#घोषणा RTS5228_AUTOLOAD_CFG3			0xFF7E
#घोषणा RTS5228_AUTOLOAD_CFG4			0xFF7F

#घोषणा RTS5228_REG_VREF			0xFE97
#घोषणा RTS5228_PWD_SUSPND_EN			(1 << 4)

#घोषणा RTS5228_PAD_H3L1			0xFF79
#घोषणा PAD_GPIO_H3L1			(1 << 3)

/* SSC_CTL2 0xFC12 */
#घोषणा RTS5228_SSC_DEPTH_MASK		0x07
#घोषणा RTS5228_SSC_DEPTH_DISALBE	0x00
#घोषणा RTS5228_SSC_DEPTH_8M		0x01
#घोषणा RTS5228_SSC_DEPTH_4M		0x02
#घोषणा RTS5228_SSC_DEPTH_2M		0x03
#घोषणा RTS5228_SSC_DEPTH_1M		0x04
#घोषणा RTS5228_SSC_DEPTH_512K		0x05
#घोषणा RTS5228_SSC_DEPTH_256K		0x06
#घोषणा RTS5228_SSC_DEPTH_128K		0x07

/* DMACTL 0xFE2C */
#घोषणा RTS5228_DMA_PACK_SIZE_MASK		0xF0

#घोषणा RTS5228_REG_LDO12_CFG			0xFF6E
#घोषणा RTS5228_LDO12_VO_TUNE_MASK		(0x07<<1)
#घोषणा RTS5228_LDO12_100				(0x00<<1)
#घोषणा RTS5228_LDO12_105				(0x01<<1)
#घोषणा RTS5228_LDO12_110				(0x02<<1)
#घोषणा RTS5228_LDO12_115				(0x03<<1)
#घोषणा RTS5228_LDO12_120				(0x04<<1)
#घोषणा RTS5228_LDO12_125				(0x05<<1)
#घोषणा RTS5228_LDO12_130				(0x06<<1)
#घोषणा RTS5228_LDO12_135				(0x07<<1)
#घोषणा RTS5228_REG_PWD_LDO12			(0x01<<0)

#घोषणा RTS5228_REG_LDO12_L12	0xFF6F
#घोषणा RTS5228_LDO12_L12_MASK			(0x07<<4)
#घोषणा RTS5228_LDO12_L12_120			(0x04<<4)

/* LDO control रेजिस्टर */
#घोषणा RTS5228_CARD_PWR_CTL			0xFD50
#घोषणा RTS5228_PUPDC					(0x01<<5)

#घोषणा RTS5228_LDO1233318_POW_CTL		0xFF70
#घोषणा RTS5228_LDO3318_POWERON			(0x01<<3)
#घोषणा RTS5228_LDO1_POWEROFF			(0x00<<0)
#घोषणा RTS5228_LDO1_SOFTSTART			(0x01<<0)
#घोषणा RTS5228_LDO1_FULLON				(0x03<<0)
#घोषणा RTS5228_LDO1_POWERON_MASK		(0x03<<0)
#घोषणा RTS5228_LDO_POWERON_MASK		(0x0F<<0)

#घोषणा RTS5228_DV3318_CFG				0xFF71
#घोषणा RTS5228_DV3318_TUNE_MASK		(0x07<<4)
#घोषणा RTS5228_DV3318_17				(0x00<<4)
#घोषणा RTS5228_DV3318_1V75				(0x01<<4)
#घोषणा RTS5228_DV3318_18				(0x02<<4)
#घोषणा RTS5228_DV3318_1V85				(0x03<<4)
#घोषणा RTS5228_DV3318_19				(0x04<<4)
#घोषणा RTS5228_DV3318_33				(0x07<<4)
#घोषणा RTS5228_DV3318_SR_MASK			(0x03<<2)
#घोषणा RTS5228_DV3318_SR_0				(0x00<<2)
#घोषणा RTS5228_DV3318_SR_250			(0x01<<2)
#घोषणा RTS5228_DV3318_SR_500			(0x02<<2)
#घोषणा RTS5228_DV3318_SR_1000			(0x03<<2)

#घोषणा RTS5228_LDO1_CFG0				0xFF72
#घोषणा RTS5228_LDO1_OCP_THD_MASK		(0x07<<5)
#घोषणा RTS5228_LDO1_OCP_EN				(0x01<<4)
#घोषणा RTS5228_LDO1_OCP_LMT_THD_MASK	(0x03<<2)
#घोषणा RTS5228_LDO1_OCP_LMT_EN			(0x01<<1)

#घोषणा RTS5228_LDO1_OCP_THD_730		(0x00<<5)
#घोषणा RTS5228_LDO1_OCP_THD_780		(0x01<<5)
#घोषणा RTS5228_LDO1_OCP_THD_860		(0x02<<5)
#घोषणा RTS5228_LDO1_OCP_THD_930		(0x03<<5)
#घोषणा RTS5228_LDO1_OCP_THD_1000		(0x04<<5)
#घोषणा RTS5228_LDO1_OCP_THD_1070		(0x05<<5)
#घोषणा RTS5228_LDO1_OCP_THD_1140		(0x06<<5)
#घोषणा RTS5228_LDO1_OCP_THD_1220		(0x07<<5)

#घोषणा RTS5228_LDO1_LMT_THD_450		(0x00<<2)
#घोषणा RTS5228_LDO1_LMT_THD_1000		(0x01<<2)
#घोषणा RTS5228_LDO1_LMT_THD_1500		(0x02<<2)
#घोषणा RTS5228_LDO1_LMT_THD_2000		(0x03<<2)

#घोषणा RTS5228_LDO1_CFG1				0xFF73
#घोषणा RTS5228_LDO1_SR_TIME_MASK		(0x03<<6)
#घोषणा RTS5228_LDO1_SR_0_0				(0x00<<6)
#घोषणा RTS5228_LDO1_SR_0_25			(0x01<<6)
#घोषणा RTS5228_LDO1_SR_0_5				(0x02<<6)
#घोषणा RTS5228_LDO1_SR_1_0				(0x03<<6)
#घोषणा RTS5228_LDO1_TUNE_MASK			(0x07<<1)
#घोषणा RTS5228_LDO1_18					(0x05<<1)
#घोषणा RTS5228_LDO1_33					(0x07<<1)
#घोषणा RTS5228_LDO1_PWD_MASK			(0x01<<0)

#घोषणा RTS5228_AUXCLK_GAT_CTL			0xFF74

#घोषणा RTS5228_REG_RREF_CTL_0			0xFF75
#घोषणा RTS5228_FORCE_RREF_EXTL			(0x01<<7)
#घोषणा RTS5228_REG_BG33_MASK			(0x07<<0)
#घोषणा RTS5228_RREF_12_1V				(0x04<<0)
#घोषणा RTS5228_RREF_12_3V				(0x05<<0)

#घोषणा RTS5228_REG_RREF_CTL_1			0xFF76

#घोषणा RTS5228_REG_RREF_CTL_2			0xFF77
#घोषणा RTS5228_TEST_INTL_RREF			(0x01<<7)
#घोषणा RTS5228_DGLCH_TIME_MASK			(0x03<<5)
#घोषणा RTS5228_DGLCH_TIME_50			(0x00<<5)
#घोषणा RTS5228_DGLCH_TIME_75			(0x01<<5)
#घोषणा RTS5228_DGLCH_TIME_100			(0x02<<5)
#घोषणा RTS5228_DGLCH_TIME_125			(0x03<<5)
#घोषणा RTS5228_REG_REXT_TUNE_MASK		(0x1F<<0)

#घोषणा RTS5228_REG_PME_FORCE_CTL		0xFF78
#घोषणा FORCE_PM_CONTROL		0x20
#घोषणा FORCE_PM_VALUE			0x10


/* Single LUN, support SD */
#घोषणा DEFAULT_SINGLE		0
#घोषणा SD_LUN				1


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

पूर्णांक rts5228_pci_चयन_घड़ी(काष्ठा rtsx_pcr *pcr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk);

#पूर्ण_अगर /* RTS5228_H */
