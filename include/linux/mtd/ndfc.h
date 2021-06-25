<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (c) 2006 Thomas Gleixner <tglx@linutronix.de>
 *
 *  Info:
 *   Contains defines, dataकाष्ठाures क्रम ndfc nand controller
 */
#अगर_अघोषित __LINUX_MTD_NDFC_H
#घोषणा __LINUX_MTD_NDFC_H

/* NDFC Register definitions */
#घोषणा NDFC_CMD		0x00
#घोषणा NDFC_ALE		0x04
#घोषणा NDFC_DATA		0x08
#घोषणा NDFC_ECC		0x10
#घोषणा NDFC_BCFG0		0x30
#घोषणा NDFC_BCFG1		0x34
#घोषणा NDFC_BCFG2		0x38
#घोषणा NDFC_BCFG3		0x3c
#घोषणा NDFC_CCR		0x40
#घोषणा NDFC_STAT		0x44
#घोषणा NDFC_HWCTL		0x48
#घोषणा NDFC_REVID		0x50

#घोषणा NDFC_STAT_IS_READY	0x01000000

#घोषणा NDFC_CCR_RESET_CE	0x80000000 /* CE Reset */
#घोषणा NDFC_CCR_RESET_ECC	0x40000000 /* ECC Reset */
#घोषणा NDFC_CCR_RIE		0x20000000 /* Interrupt Enable on Device Rdy */
#घोषणा NDFC_CCR_REN		0x10000000 /* Enable रुको क्रम Rdy in LinearR */
#घोषणा NDFC_CCR_ROMEN		0x08000000 /* Enable ROM In LinearR */
#घोषणा NDFC_CCR_ARE		0x04000000 /* Auto-Read Enable */
#घोषणा NDFC_CCR_BS(x)		(((x) & 0x3) << 24) /* Select Bank on CE[x] */
#घोषणा NDFC_CCR_BS_MASK	0x03000000 /* Select Bank */
#घोषणा NDFC_CCR_ARAC0		0x00000000 /* 3 Addr, 1 Col 2 Row 512b page */
#घोषणा NDFC_CCR_ARAC1		0x00001000 /* 4 Addr, 1 Col 3 Row 512b page */
#घोषणा NDFC_CCR_ARAC2		0x00002000 /* 4 Addr, 2 Col 2 Row 2K page */
#घोषणा NDFC_CCR_ARAC3		0x00003000 /* 5 Addr, 2 Col 3 Row 2K page */
#घोषणा NDFC_CCR_ARAC_MASK	0x00003000 /* Auto-Read mode Addr Cycles */
#घोषणा NDFC_CCR_RPG		0x0000C000 /* Auto-Read Page */
#घोषणा NDFC_CCR_EBCC		0x00000004 /* EBC Configuration Completed */
#घोषणा NDFC_CCR_DHC		0x00000002 /* Direct Hardware Control Enable */

#घोषणा NDFC_BxCFG_EN		0x80000000 /* Bank Enable */
#घोषणा NDFC_BxCFG_CED		0x40000000 /* nCE Style */
#घोषणा NDFC_BxCFG_SZ_MASK	0x08000000 /* Bank Size */
#घोषणा NDFC_BxCFG_SZ_8BIT	0x00000000 /* 8bit */
#घोषणा NDFC_BxCFG_SZ_16BIT	0x08000000 /* 16bit */

#घोषणा NDFC_MAX_BANKS		4

काष्ठा ndfc_controller_settings अणु
	uपूर्णांक32_t	ccr_settings;
	uपूर्णांक64_t	ndfc_erpn;
पूर्ण;

काष्ठा ndfc_chip_settings अणु
	uपूर्णांक32_t	bank_settings;
पूर्ण;

#पूर्ण_अगर
