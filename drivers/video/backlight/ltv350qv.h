<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definitions क्रम Samsung LTV350QV Quarter VGA LCD Panel
 *
 * Copyright (C) 2006, 2007 Aपंचांगel Corporation
 */
#अगर_अघोषित __LTV350QV_H
#घोषणा __LTV350QV_H

#घोषणा LTV_OPC_INDEX	0x74
#घोषणा LTV_OPC_DATA	0x76

#घोषणा LTV_ID		0x00		/* ID Read */
#घोषणा LTV_IFCTL	0x01		/* Display Interface Control */
#घोषणा LTV_DATACTL	0x02		/* Display Data Control */
#घोषणा LTV_ENTRY_MODE	0x03		/* Entry Mode */
#घोषणा LTV_GATECTL1	0x04		/* Gate Control 1 */
#घोषणा LTV_GATECTL2	0x05		/* Gate Control 2 */
#घोषणा LTV_VBP		0x06		/* Vertical Back Porch */
#घोषणा LTV_HBP		0x07		/* Horizontal Back Porch */
#घोषणा LTV_SOTCTL	0x08		/* Source Output Timing Control */
#घोषणा LTV_PWRCTL1	0x09		/* Power Control 1 */
#घोषणा LTV_PWRCTL2	0x0a		/* Power Control 2 */
#घोषणा LTV_GAMMA(x)	(0x10 + (x))	/* Gamma control */

/* Bit definitions क्रम LTV_IFCTL */
#घोषणा LTV_IM			(1 << 15)
#घोषणा LTV_NMD			(1 << 14)
#घोषणा LTV_SSMD		(1 << 13)
#घोषणा LTV_REV			(1 <<  7)
#घोषणा LTV_NL(x)		(((x) & 0x001f) << 0)

/* Bit definitions क्रम LTV_DATACTL */
#घोषणा LTV_DS_SAME		(0 << 12)
#घोषणा LTV_DS_D_TO_S		(1 << 12)
#घोषणा LTV_DS_S_TO_D		(2 << 12)
#घोषणा LTV_CHS_384		(0 <<  9)
#घोषणा LTV_CHS_480		(1 <<  9)
#घोषणा LTV_CHS_492		(2 <<  9)
#घोषणा LTV_DF_RGB		(0 <<  6)
#घोषणा LTV_DF_RGBX		(1 <<  6)
#घोषणा LTV_DF_XRGB		(2 <<  6)
#घोषणा LTV_RGB_RGB		(0 <<  2)
#घोषणा LTV_RGB_BGR		(1 <<  2)
#घोषणा LTV_RGB_GRB		(2 <<  2)
#घोषणा LTV_RGB_RBG		(3 <<  2)

/* Bit definitions क्रम LTV_ENTRY_MODE */
#घोषणा LTV_VSPL_ACTIVE_LOW	(0 << 15)
#घोषणा LTV_VSPL_ACTIVE_HIGH	(1 << 15)
#घोषणा LTV_HSPL_ACTIVE_LOW	(0 << 14)
#घोषणा LTV_HSPL_ACTIVE_HIGH	(1 << 14)
#घोषणा LTV_DPL_SAMPLE_RISING	(0 << 13)
#घोषणा LTV_DPL_SAMPLE_FALLING	(1 << 13)
#घोषणा LTV_EPL_ACTIVE_LOW	(0 << 12)
#घोषणा LTV_EPL_ACTIVE_HIGH	(1 << 12)
#घोषणा LTV_SS_LEFT_TO_RIGHT	(0 <<  8)
#घोषणा LTV_SS_RIGHT_TO_LEFT	(1 <<  8)
#घोषणा LTV_STB			(1 <<  1)

/* Bit definitions क्रम LTV_GATECTL1 */
#घोषणा LTV_CLW(x)		(((x) & 0x0007) << 12)
#घोषणा LTV_GAON		(1 <<  5)
#घोषणा LTV_SDR			(1 <<  3)

/* Bit definitions क्रम LTV_GATECTL2 */
#घोषणा LTV_NW_INV_FRAME	(0 << 14)
#घोषणा LTV_NW_INV_1LINE	(1 << 14)
#घोषणा LTV_NW_INV_2LINE	(2 << 14)
#घोषणा LTV_DSC			(1 << 12)
#घोषणा LTV_GIF			(1 <<  8)
#घोषणा LTV_FHN			(1 <<  7)
#घोषणा LTV_FTI(x)		(((x) & 0x0003) << 4)
#घोषणा LTV_FWI(x)		(((x) & 0x0003) << 0)

/* Bit definitions क्रम LTV_SOTCTL */
#घोषणा LTV_SDT(x)		(((x) & 0x0007) << 10)
#घोषणा LTV_EQ(x)		(((x) & 0x0007) <<  2)

/* Bit definitions क्रम LTV_PWRCTL1 */
#घोषणा LTV_VCOM_DISABLE	(1 << 14)
#घोषणा LTV_VCOMOUT_ENABLE	(1 << 11)
#घोषणा LTV_POWER_ON		(1 <<  9)
#घोषणा LTV_DRIVE_CURRENT(x)	(((x) & 0x0007) << 4)	/* 0=off, 5=max */
#घोषणा LTV_SUPPLY_CURRENT(x)	(((x) & 0x0007) << 0)	/* 0=off, 5=max */

/* Bit definitions क्रम LTV_PWRCTL2 */
#घोषणा LTV_VCOML_ENABLE	(1 << 13)
#घोषणा LTV_VCOML_VOLTAGE(x)	(((x) & 0x001f) << 8)	/* 0=1V, 31=-1V */
#घोषणा LTV_VCOMH_VOLTAGE(x)	(((x) & 0x001f) << 0)	/* 0=3V, 31=4.5V */

#पूर्ण_अगर /* __LTV350QV_H */
