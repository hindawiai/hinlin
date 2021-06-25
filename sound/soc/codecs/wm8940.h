<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8940.h -- WM8940 Soc Audio driver
 */

#अगर_अघोषित _WM8940_H
#घोषणा _WM8940_H

काष्ठा wm8940_setup_data अणु
	/* Vref to analogue output resistance */
#घोषणा WM8940_VROI_1K 0
#घोषणा WM8940_VROI_30K 1
	अचिन्हित पूर्णांक vroi:1;
पूर्ण;

/* WM8940 रेजिस्टर space */
#घोषणा WM8940_SOFTRESET	0x00
#घोषणा WM8940_POWER1		0x01
#घोषणा WM8940_POWER2		0x02
#घोषणा WM8940_POWER3		0x03
#घोषणा WM8940_IFACE		0x04
#घोषणा WM8940_COMPANDINGCTL	0x05
#घोषणा WM8940_CLOCK		0x06
#घोषणा WM8940_ADDCNTRL		0x07
#घोषणा WM8940_GPIO		0x08
#घोषणा WM8940_CTLINT		0x09
#घोषणा WM8940_DAC		0x0A
#घोषणा WM8940_DACVOL		0x0B

#घोषणा WM8940_ADC		0x0E
#घोषणा WM8940_ADCVOL		0x0F
#घोषणा WM8940_NOTCH1		0x10
#घोषणा WM8940_NOTCH2		0x11
#घोषणा WM8940_NOTCH3		0x12
#घोषणा WM8940_NOTCH4		0x13
#घोषणा WM8940_NOTCH5		0x14
#घोषणा WM8940_NOTCH6		0x15
#घोषणा WM8940_NOTCH7		0x16
#घोषणा WM8940_NOTCH8		0x17
#घोषणा WM8940_DACLIM1		0x18
#घोषणा WM8940_DACLIM2		0x19

#घोषणा WM8940_ALC1		0x20
#घोषणा WM8940_ALC2		0x21
#घोषणा WM8940_ALC3		0x22
#घोषणा WM8940_NOISEGATE	0x23
#घोषणा WM8940_PLLN		0x24
#घोषणा WM8940_PLLK1		0x25
#घोषणा WM8940_PLLK2		0x26
#घोषणा WM8940_PLLK3		0x27

#घोषणा WM8940_ALC4		0x2A

#घोषणा WM8940_INPUTCTL		0x2C
#घोषणा WM8940_PGAGAIN		0x2D

#घोषणा WM8940_ADCBOOST		0x2F

#घोषणा WM8940_OUTPUTCTL	0x31
#घोषणा WM8940_SPKMIX		0x32

#घोषणा WM8940_SPKVOL		0x36

#घोषणा WM8940_MONOMIX		0x38

#घोषणा WM8940_CACHEREGNUM  0x57


/* Clock भागider Id's */
#घोषणा WM8940_BCLKDIV 0
#घोषणा WM8940_MCLKDIV 1
#घोषणा WM8940_OPCLKDIV 2

/* MCLK घड़ी भागiders */
#घोषणा WM8940_MCLKDIV_1	0
#घोषणा WM8940_MCLKDIV_1_5	1
#घोषणा WM8940_MCLKDIV_2	2
#घोषणा WM8940_MCLKDIV_3	3
#घोषणा WM8940_MCLKDIV_4	4
#घोषणा WM8940_MCLKDIV_6	5
#घोषणा WM8940_MCLKDIV_8	6
#घोषणा WM8940_MCLKDIV_12	7

/* BCLK घड़ी भागiders */
#घोषणा WM8940_BCLKDIV_1 0
#घोषणा WM8940_BCLKDIV_2 1
#घोषणा WM8940_BCLKDIV_4 2
#घोषणा WM8940_BCLKDIV_8 3
#घोषणा WM8940_BCLKDIV_16 4
#घोषणा WM8940_BCLKDIV_32 5

/* PLL Out Dividers */
#घोषणा WM8940_OPCLKDIV_1 0
#घोषणा WM8940_OPCLKDIV_2 1
#घोषणा WM8940_OPCLKDIV_3 2
#घोषणा WM8940_OPCLKDIV_4 3

#पूर्ण_अगर /* _WM8940_H */

