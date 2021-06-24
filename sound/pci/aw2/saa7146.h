<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*****************************************************************************
 *
 * Copyright (C) 2008 Cedric Bregardis <cedric.bregardis@मुक्त.fr> and
 * Jean-Christian Hassler <jhassler@मुक्त.fr>
 *
 * This file is part of the Audiowerk2 ALSA driver
 *
 *****************************************************************************/

/* SAA7146 रेजिस्टरs */
#घोषणा PCI_BT_A	0x4C
#घोषणा IICTFR		0x8C
#घोषणा IICSTA		0x90
#घोषणा BaseA1_in	0x94
#घोषणा ProtA1_in	0x98
#घोषणा PageA1_in	0x9C
#घोषणा BaseA1_out	0xA0
#घोषणा ProtA1_out	0xA4
#घोषणा PageA1_out	0xA8
#घोषणा BaseA2_in	0xAC
#घोषणा ProtA2_in	0xB0
#घोषणा PageA2_in	0xB4
#घोषणा BaseA2_out	0xB8
#घोषणा ProtA2_out	0xBC
#घोषणा PageA2_out	0xC0
#घोषणा IER		0xDC
#घोषणा GPIO_CTRL	0xE0
#घोषणा ACON1		0xF4
#घोषणा ACON2		0xF8
#घोषणा MC1		0xFC
#घोषणा MC2		0x100
#घोषणा ISR		0x10C
#घोषणा PSR		0x110
#घोषणा SSR		0x114
#घोषणा PCI_ADP1	0x12C
#घोषणा PCI_ADP2	0x130
#घोषणा PCI_ADP3	0x134
#घोषणा PCI_ADP4	0x138
#घोषणा LEVEL_REP	0x140
#घोषणा FB_BUFFER1	0x144
#घोषणा FB_BUFFER2	0x148
#घोषणा TSL1		0x180
#घोषणा TSL2		0x1C0

#घोषणा ME	(1UL << 11)
#घोषणा LIMIT	(1UL << 4)
#घोषणा PV	(1UL << 3)

/* PSR/ISR/IER */
#घोषणा PPEF		(1UL << 31)
#घोषणा PABO		(1UL << 30)
#घोषणा IIC_S		(1UL << 17)
#घोषणा IIC_E		(1UL << 16)
#घोषणा A2_in		(1UL << 15)
#घोषणा A2_out		(1UL << 14)
#घोषणा A1_in		(1UL << 13)
#घोषणा A1_out		(1UL << 12)
#घोषणा AFOU		(1UL << 11)
#घोषणा PIN3		(1UL << 6)
#घोषणा PIN2		(1UL << 5)
#घोषणा PIN1		(1UL << 4)
#घोषणा PIN0		(1UL << 3)
#घोषणा ECS		(1UL << 2)
#घोषणा EC3S		(1UL << 1)
#घोषणा EC0S		(1UL << 0)

/* SSR */
#घोषणा PRQ		(1UL << 31)
#घोषणा PMA		(1UL << 30)
#घोषणा IIC_EA		(1UL << 21)
#घोषणा IIC_EW		(1UL << 20)
#घोषणा IIC_ER		(1UL << 19)
#घोषणा IIC_EL		(1UL << 18)
#घोषणा IIC_EF		(1UL << 17)
#घोषणा AF2_in		(1UL << 10)
#घोषणा AF2_out		(1UL << 9)
#घोषणा AF1_in		(1UL << 8)
#घोषणा AF1_out		(1UL << 7)
#घोषणा EC5S		(1UL << 3)
#घोषणा EC4S		(1UL << 2)
#घोषणा EC2S		(1UL << 1)
#घोषणा EC1S		(1UL << 0)

/* PCI_BT_A */
#घोषणा BurstA1_in	(1UL << 26)
#घोषणा ThreshA1_in	(1UL << 24)
#घोषणा BurstA1_out	(1UL << 18)
#घोषणा ThreshA1_out	(1UL << 16)
#घोषणा BurstA2_in	(1UL << 10)
#घोषणा ThreshA2_in	(1UL << 8)
#घोषणा BurstA2_out	(1UL << 2)
#घोषणा ThreshA2_out	(1UL << 0)

/* MC1 */
#घोषणा MRST_N		(1UL << 15)
#घोषणा EAP		(1UL << 9)
#घोषणा EI2C		(1UL << 8)
#घोषणा TR_E_A2_OUT	(1UL << 3)
#घोषणा TR_E_A2_IN	(1UL << 2)
#घोषणा TR_E_A1_OUT	(1UL << 1)
#घोषणा TR_E_A1_IN	(1UL << 0)

/* MC2 */
#घोषणा UPLD_IIC	(1UL << 0)

/* ACON1 */
#घोषणा AUDIO_MODE	(1UL << 29)
#घोषणा MAXLEVEL	(1UL << 22)
#घोषणा A1_SWAP		(1UL << 21)
#घोषणा A2_SWAP		(1UL << 20)
#घोषणा WS0_CTRL	(1UL << 18)
#घोषणा WS0_SYNC	(1UL << 16)
#घोषणा WS1_CTRL	(1UL << 14)
#घोषणा WS1_SYNC	(1UL << 12)
#घोषणा WS2_CTRL	(1UL << 10)
#घोषणा WS2_SYNC	(1UL << 8)
#घोषणा WS3_CTRL	(1UL << 6)
#घोषणा WS3_SYNC	(1UL << 4)
#घोषणा WS4_CTRL	(1UL << 2)
#घोषणा WS4_SYNC	(1UL << 0)

/* ACON2 */
#घोषणा A1_CLKSRC	(1UL << 27)
#घोषणा A2_CLKSRC	(1UL << 22)
#घोषणा INVERT_BCLK1	(1UL << 21)
#घोषणा INVERT_BCLK2	(1UL << 20)
#घोषणा BCLK1_OEN	(1UL << 19)
#घोषणा BCLK2_OEN	(1UL << 18)

/* IICSTA */
#घोषणा IICCC		(1UL << 8)
#घोषणा ABORT		(1UL << 7)
#घोषणा SPERR		(1UL << 6)
#घोषणा APERR		(1UL << 5)
#घोषणा DTERR		(1UL << 4)
#घोषणा DRERR		(1UL << 3)
#घोषणा AL		(1UL << 2)
#घोषणा ERR		(1UL << 1)
#घोषणा BUSY		(1UL << 0)

/* IICTFR */
#घोषणा BYTE2		(1UL << 24)
#घोषणा BYTE1		(1UL << 16)
#घोषणा BYTE0		(1UL << 8)
#घोषणा ATRR2		(1UL << 6)
#घोषणा ATRR1		(1UL << 4)
#घोषणा ATRR0		(1UL << 2)
#घोषणा ERR		(1UL << 1)
#घोषणा BUSY		(1UL << 0)

#घोषणा START	3
#घोषणा CONT	2
#घोषणा STOP	1
#घोषणा NOP	0
