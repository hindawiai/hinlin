<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * wm8753.h  --  audio driver क्रम WM8753
 *
 * Copyright 2003 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#अगर_अघोषित _WM8753_H
#घोषणा _WM8753_H

/* WM8753 रेजिस्टर space */

#घोषणा WM8753_DAC		0x01
#घोषणा WM8753_ADC		0x02
#घोषणा WM8753_PCM		0x03
#घोषणा WM8753_HIFI		0x04
#घोषणा WM8753_IOCTL		0x05
#घोषणा WM8753_SRATE1		0x06
#घोषणा WM8753_SRATE2		0x07
#घोषणा WM8753_LDAC		0x08
#घोषणा WM8753_RDAC		0x09
#घोषणा WM8753_BASS		0x0a
#घोषणा WM8753_TREBLE		0x0b
#घोषणा WM8753_ALC1		0x0c
#घोषणा WM8753_ALC2		0x0d
#घोषणा WM8753_ALC3		0x0e
#घोषणा WM8753_NGATE		0x0f
#घोषणा WM8753_LADC		0x10
#घोषणा WM8753_RADC		0x11
#घोषणा WM8753_ADCTL1		0x12
#घोषणा WM8753_3D		0x13
#घोषणा WM8753_PWR1		0x14
#घोषणा WM8753_PWR2		0x15
#घोषणा WM8753_PWR3		0x16
#घोषणा WM8753_PWR4		0x17
#घोषणा WM8753_ID		0x18
#घोषणा WM8753_INTPOL		0x19
#घोषणा WM8753_INTEN		0x1a
#घोषणा WM8753_GPIO1		0x1b
#घोषणा WM8753_GPIO2		0x1c
#घोषणा WM8753_RESET		0x1f
#घोषणा WM8753_RECMIX1		0x20
#घोषणा WM8753_RECMIX2		0x21
#घोषणा WM8753_LOUTM1		0x22
#घोषणा WM8753_LOUTM2		0x23
#घोषणा WM8753_ROUTM1		0x24
#घोषणा WM8753_ROUTM2		0x25
#घोषणा WM8753_MOUTM1		0x26
#घोषणा WM8753_MOUTM2		0x27
#घोषणा WM8753_LOUT1V		0x28
#घोषणा WM8753_ROUT1V		0x29
#घोषणा WM8753_LOUT2V		0x2a
#घोषणा WM8753_ROUT2V		0x2b
#घोषणा WM8753_MOUTV		0x2c
#घोषणा WM8753_OUTCTL		0x2d
#घोषणा WM8753_ADCIN		0x2e
#घोषणा WM8753_INCTL1		0x2f
#घोषणा WM8753_INCTL2		0x30
#घोषणा WM8753_LINVOL		0x31
#घोषणा WM8753_RINVOL		0x32
#घोषणा WM8753_MICBIAS		0x33
#घोषणा WM8753_CLOCK		0x34
#घोषणा WM8753_PLL1CTL1		0x35
#घोषणा WM8753_PLL1CTL2		0x36
#घोषणा WM8753_PLL1CTL3		0x37
#घोषणा WM8753_PLL1CTL4		0x38
#घोषणा WM8753_PLL2CTL1		0x39
#घोषणा WM8753_PLL2CTL2		0x3a
#घोषणा WM8753_PLL2CTL3		0x3b
#घोषणा WM8753_PLL2CTL4		0x3c
#घोषणा WM8753_BIASCTL		0x3d
#घोषणा WM8753_ADCTL2		0x3f

#घोषणा WM8753_PLL1			0
#घोषणा WM8753_PLL2			1

/* घड़ी inमाला_दो */
#घोषणा WM8753_MCLK		0
#घोषणा WM8753_PCMCLK		1

/* घड़ी भागider id's */
#घोषणा WM8753_PCMDIV		0
#घोषणा WM8753_BCLKDIV		1
#घोषणा WM8753_VXCLKDIV		2

/* PCM घड़ी भागiders */
#घोषणा WM8753_PCM_DIV_1	(0 << 6)
#घोषणा WM8753_PCM_DIV_3	(2 << 6)
#घोषणा WM8753_PCM_DIV_5_5	(3 << 6)
#घोषणा WM8753_PCM_DIV_2	(4 << 6)
#घोषणा WM8753_PCM_DIV_4	(5 << 6)
#घोषणा WM8753_PCM_DIV_6	(6 << 6)
#घोषणा WM8753_PCM_DIV_8	(7 << 6)

/* BCLK घड़ी भागiders */
#घोषणा WM8753_BCLK_DIV_1	(0 << 3)
#घोषणा WM8753_BCLK_DIV_2	(1 << 3)
#घोषणा WM8753_BCLK_DIV_4	(2 << 3)
#घोषणा WM8753_BCLK_DIV_8	(3 << 3)
#घोषणा WM8753_BCLK_DIV_16	(4 << 3)

/* VXCLK घड़ी भागiders */
#घोषणा WM8753_VXCLK_DIV_1	(0 << 6)
#घोषणा WM8753_VXCLK_DIV_2	(1 << 6)
#घोषणा WM8753_VXCLK_DIV_4	(2 << 6)
#घोषणा WM8753_VXCLK_DIV_8	(3 << 6)
#घोषणा WM8753_VXCLK_DIV_16	(4 << 6)

#पूर्ण_अगर
