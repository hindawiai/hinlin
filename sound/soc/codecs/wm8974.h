<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8974.h  --  WM8974 Soc Audio driver
 */

#अगर_अघोषित _WM8974_H
#घोषणा _WM8974_H

/* WM8974 रेजिस्टर space */

#घोषणा WM8974_RESET		0x0
#घोषणा WM8974_POWER1		0x1
#घोषणा WM8974_POWER2		0x2
#घोषणा WM8974_POWER3		0x3
#घोषणा WM8974_IFACE		0x4
#घोषणा WM8974_COMP		0x5
#घोषणा WM8974_CLOCK		0x6
#घोषणा WM8974_ADD		0x7
#घोषणा WM8974_GPIO		0x8
#घोषणा WM8974_DAC		0xa
#घोषणा WM8974_DACVOL		0xb
#घोषणा WM8974_ADC		0xe
#घोषणा WM8974_ADCVOL		0xf
#घोषणा WM8974_EQ1		0x12
#घोषणा WM8974_EQ2		0x13
#घोषणा WM8974_EQ3		0x14
#घोषणा WM8974_EQ4		0x15
#घोषणा WM8974_EQ5		0x16
#घोषणा WM8974_DACLIM1		0x18
#घोषणा WM8974_DACLIM2		0x19
#घोषणा WM8974_NOTCH1		0x1b
#घोषणा WM8974_NOTCH2		0x1c
#घोषणा WM8974_NOTCH3		0x1d
#घोषणा WM8974_NOTCH4		0x1e
#घोषणा WM8974_ALC1		0x20
#घोषणा WM8974_ALC2		0x21
#घोषणा WM8974_ALC3		0x22
#घोषणा WM8974_NGATE		0x23
#घोषणा WM8974_PLLN		0x24
#घोषणा WM8974_PLLK1		0x25
#घोषणा WM8974_PLLK2		0x26
#घोषणा WM8974_PLLK3		0x27
#घोषणा WM8974_ATTEN		0x28
#घोषणा WM8974_INPUT		0x2c
#घोषणा WM8974_INPPGA		0x2d
#घोषणा WM8974_ADCBOOST		0x2f
#घोषणा WM8974_OUTPUT		0x31
#घोषणा WM8974_SPKMIX		0x32
#घोषणा WM8974_SPKVOL		0x36
#घोषणा WM8974_MONOMIX		0x38

#घोषणा WM8974_CACHEREGNUM 	57

/* Clock भागider Id's */
#घोषणा WM8974_OPCLKDIV		0
#घोषणा WM8974_MCLKDIV		1
#घोषणा WM8974_BCLKDIV		2

/* PLL Out भागiders */
#घोषणा WM8974_OPCLKDIV_1	(0 << 4)
#घोषणा WM8974_OPCLKDIV_2	(1 << 4)
#घोषणा WM8974_OPCLKDIV_3	(2 << 4)
#घोषणा WM8974_OPCLKDIV_4	(3 << 4)

/* BCLK घड़ी भागiders */
#घोषणा WM8974_BCLKDIV_1	(0 << 2)
#घोषणा WM8974_BCLKDIV_2	(1 << 2)
#घोषणा WM8974_BCLKDIV_4	(2 << 2)
#घोषणा WM8974_BCLKDIV_8	(3 << 2)
#घोषणा WM8974_BCLKDIV_16	(4 << 2)
#घोषणा WM8974_BCLKDIV_32	(5 << 2)

/* MCLK घड़ी भागiders */
#घोषणा WM8974_MCLKDIV_1	(0 << 5)
#घोषणा WM8974_MCLKDIV_1_5	(1 << 5)
#घोषणा WM8974_MCLKDIV_2	(2 << 5)
#घोषणा WM8974_MCLKDIV_3	(3 << 5)
#घोषणा WM8974_MCLKDIV_4	(4 << 5)
#घोषणा WM8974_MCLKDIV_6	(5 << 5)
#घोषणा WM8974_MCLKDIV_8	(6 << 5)
#घोषणा WM8974_MCLKDIV_12	(7 << 5)

#पूर्ण_अगर
