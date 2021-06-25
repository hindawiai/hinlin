<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8510.h  --  WM8510 Soc Audio driver
 */

#अगर_अघोषित _WM8510_H
#घोषणा _WM8510_H

/* WM8510 रेजिस्टर space */

#घोषणा WM8510_RESET		0x0
#घोषणा WM8510_POWER1		0x1
#घोषणा WM8510_POWER2		0x2
#घोषणा WM8510_POWER3		0x3
#घोषणा WM8510_IFACE		0x4
#घोषणा WM8510_COMP			0x5
#घोषणा WM8510_CLOCK		0x6
#घोषणा WM8510_ADD			0x7
#घोषणा WM8510_GPIO			0x8
#घोषणा WM8510_DAC			0xa
#घोषणा WM8510_DACVOL		0xb
#घोषणा WM8510_ADC			0xe
#घोषणा WM8510_ADCVOL		0xf
#घोषणा WM8510_EQ1			0x12
#घोषणा WM8510_EQ2			0x13
#घोषणा WM8510_EQ3			0x14
#घोषणा WM8510_EQ4			0x15
#घोषणा WM8510_EQ5			0x16
#घोषणा WM8510_DACLIM1		0x18
#घोषणा WM8510_DACLIM2		0x19
#घोषणा WM8510_NOTCH1		0x1b
#घोषणा WM8510_NOTCH2		0x1c
#घोषणा WM8510_NOTCH3		0x1d
#घोषणा WM8510_NOTCH4		0x1e
#घोषणा WM8510_ALC1			0x20
#घोषणा WM8510_ALC2			0x21
#घोषणा WM8510_ALC3			0x22
#घोषणा WM8510_NGATE		0x23
#घोषणा WM8510_PLLN			0x24
#घोषणा WM8510_PLLK1		0x25
#घोषणा WM8510_PLLK2		0x26
#घोषणा WM8510_PLLK3		0x27
#घोषणा WM8510_ATTEN		0x28
#घोषणा WM8510_INPUT		0x2c
#घोषणा WM8510_INPPGA		0x2d
#घोषणा WM8510_ADCBOOST		0x2f
#घोषणा WM8510_OUTPUT		0x31
#घोषणा WM8510_SPKMIX		0x32
#घोषणा WM8510_SPKVOL		0x36
#घोषणा WM8510_MONOMIX		0x38

#घोषणा WM8510_CACHEREGNUM 	57

/* Clock भागider Id's */
#घोषणा WM8510_OPCLKDIV		0
#घोषणा WM8510_MCLKDIV		1
#घोषणा WM8510_ADCCLK		2
#घोषणा WM8510_DACCLK		3
#घोषणा WM8510_BCLKDIV		4

/* DAC घड़ी भागiders */
#घोषणा WM8510_DACCLK_F2	(1 << 3)
#घोषणा WM8510_DACCLK_F4	(0 << 3)

/* ADC घड़ी भागiders */
#घोषणा WM8510_ADCCLK_F2	(1 << 3)
#घोषणा WM8510_ADCCLK_F4	(0 << 3)

/* PLL Out भागiders */
#घोषणा WM8510_OPCLKDIV_1	(0 << 4)
#घोषणा WM8510_OPCLKDIV_2	(1 << 4)
#घोषणा WM8510_OPCLKDIV_3	(2 << 4)
#घोषणा WM8510_OPCLKDIV_4	(3 << 4)

/* BCLK घड़ी भागiders */
#घोषणा WM8510_BCLKDIV_1	(0 << 2)
#घोषणा WM8510_BCLKDIV_2	(1 << 2)
#घोषणा WM8510_BCLKDIV_4	(2 << 2)
#घोषणा WM8510_BCLKDIV_8	(3 << 2)
#घोषणा WM8510_BCLKDIV_16	(4 << 2)
#घोषणा WM8510_BCLKDIV_32	(5 << 2)

/* MCLK घड़ी भागiders */
#घोषणा WM8510_MCLKDIV_1	(0 << 5)
#घोषणा WM8510_MCLKDIV_1_5	(1 << 5)
#घोषणा WM8510_MCLKDIV_2	(2 << 5)
#घोषणा WM8510_MCLKDIV_3	(3 << 5)
#घोषणा WM8510_MCLKDIV_4	(4 << 5)
#घोषणा WM8510_MCLKDIV_6	(5 << 5)
#घोषणा WM8510_MCLKDIV_8	(6 << 5)
#घोषणा WM8510_MCLKDIV_12	(7 << 5)

काष्ठा wm8510_setup_data अणु
	पूर्णांक spi;
	पूर्णांक i2c_bus;
	अचिन्हित लघु i2c_address;
पूर्ण;

#पूर्ण_अगर
