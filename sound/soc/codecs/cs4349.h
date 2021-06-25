<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALSA SoC CS4349 codec driver
 *
 * Copyright 2015 Cirrus Logic, Inc.
 *
 * Author: Tim Howe <Tim.Howe@cirrus.com>
 */

#अगर_अघोषित __CS4349_H__
#घोषणा __CS4349_H__

/* CS4349 रेजिस्टरs addresses */
#घोषणा CS4349_CHIPID		0x01	/* Device and Rev ID, Read Only */
#घोषणा CS4349_MODE		0x02	/* Mode Control */
#घोषणा CS4349_VMI		0x03	/* Volume, Mixing, Inversion Control */
#घोषणा CS4349_MUTE		0x04	/* Mute Control */
#घोषणा CS4349_VOLA		0x05	/* DAC Channel A Volume Control */
#घोषणा CS4349_VOLB		0x06	/* DAC Channel B Volume Control */
#घोषणा CS4349_RMPFLT		0x07	/* Ramp and Filter Control */
#घोषणा CS4349_MISC		0x08	/* Power Down,Freeze Control,Pop Stop*/

#घोषणा CS4349_I2C_INCR		0x80


/* Device and Revision ID */
#घोषणा CS4349_REVA		0xF0	/* Rev A */
#घोषणा CS4349_REVB		0xF1	/* Rev B */
#घोषणा CS4349_REVC2		0xFF	/* Rev C2 */


/* PDN_DONE Poll Maximum
 * If soft ramp is set it will take much दीर्घer to घातer करोwn
 * the प्रणाली.
 */
#घोषणा PDN_POLL_MAX		900


/* Bitfield Definitions */

/* CS4349_MODE */
/* (Digital Interface Format, De-Emphasis Control, Functional Mode */
#घोषणा DIF2			(1 << 6)
#घोषणा DIF1			(1 << 5)
#घोषणा DIF0			(1 << 4)
#घोषणा DEM1			(1 << 3)
#घोषणा DEM0			(1 << 2)
#घोषणा FM1			(1 << 1)
#घोषणा DIF_LEFT_JST		0x00
#घोषणा DIF_I2S			0x01
#घोषणा DIF_RGHT_JST16		0x02
#घोषणा DIF_RGHT_JST24		0x03
#घोषणा DIF_TDM0		0x04
#घोषणा DIF_TDM1		0x05
#घोषणा DIF_TDM2		0x06
#घोषणा DIF_TDM3		0x07
#घोषणा DIF_MASK		0x70
#घोषणा MODE_FORMAT(x)		(((x)&7)<<4)
#घोषणा DEM_MASK		0x0C
#घोषणा NO_DEM			0x00
#घोषणा DEM_441			0x04
#घोषणा DEM_48K			0x08
#घोषणा DEM_32K			0x0C
#घोषणा FM_AUTO			0x00
#घोषणा FM_SNGL			0x01
#घोषणा FM_DBL			0x02
#घोषणा FM_QUAD			0x03
#घोषणा FM_SNGL_MIN		30000
#घोषणा FM_SNGL_MAX		54000
#घोषणा FM_द्विग_उच्च		108000
#घोषणा FM_QUAD_MAX		216000
#घोषणा FM_MASK			0x03

/* CS4349_VMI (VMI = Volume, Mixing and Inversion Controls) */
#घोषणा VOLBISA			(1 << 7)
#घोषणा VOLAISB			(1 << 7)
/* INVERT_A only available क्रम Left Jstfd, Right Jstfd16 and Right Jstfd24 */
#घोषणा INVERT_A		(1 << 6)
/* INVERT_B only available क्रम Left Jstfd, Right Jstfd16 and Right Jstfd24 */
#घोषणा INVERT_B		(1 << 5)
#घोषणा ATAPI3			(1 << 3)
#घोषणा ATAPI2			(1 << 2)
#घोषणा ATAPI1			(1 << 1)
#घोषणा ATAPI0			(1 << 0)
#घोषणा MUTEAB			0x00
#घोषणा MUTEA_RIGHTB		0x01
#घोषणा MUTEA_LEFTB		0x02
#घोषणा MUTEA_SUMLRDIV2B	0x03
#घोषणा RIGHTA_MUTEB		0x04
#घोषणा RIGHTA_RIGHTB		0x05
#घोषणा RIGHTA_LEFTB		0x06
#घोषणा RIGHTA_SUMLRDIV2B	0x07
#घोषणा LEFTA_MUTEB		0x08
#घोषणा LEFTA_RIGHTB		0x09	/* Default */
#घोषणा LEFTA_LEFTB		0x0A
#घोषणा LEFTA_SUMLRDIV2B	0x0B
#घोषणा SUMLRDIV2A_MUTEB	0x0C
#घोषणा SUMLRDIV2A_RIGHTB	0x0D
#घोषणा SUMLRDIV2A_LEFTB	0x0E
#घोषणा SUMLRDIV2_AB		0x0F
#घोषणा CHMIX_MASK		0x0F

/* CS4349_MUTE */
#घोषणा AUTOMUTE		(1 << 7)
#घोषणा MUTEC_AB		(1 << 5)
#घोषणा MUTE_A			(1 << 4)
#घोषणा MUTE_B			(1 << 3)
#घोषणा MUTE_AB_MASK		0x18

/* CS4349_RMPFLT (Ramp and Filter Control) */
#घोषणा SCZ1			(1 << 7)
#घोषणा SCZ0			(1 << 6)
#घोषणा RMP_UP			(1 << 5)
#घोषणा RMP_DN			(1 << 4)
#घोषणा FILT_SEL		(1 << 2)
#घोषणा IMMDT_CHNG		0x31
#घोषणा ZEROCRSS		0x71
#घोषणा SOFT_RMP		0xB1
#घोषणा SFTRMP_ZEROCRSS		0xF1
#घोषणा SR_ZC_MASK		0xC0

/* CS4349_MISC */
#घोषणा PWR_DWN			(1 << 7)
#घोषणा FREEZE			(1 << 5)
#घोषणा POPG_EN			(1 << 4)

#पूर्ण_अगर	/* __CS4349_H__ */
