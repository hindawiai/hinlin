<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8960.h  --  WM8960 Soc Audio driver
 */

#अगर_अघोषित _WM8960_H
#घोषणा _WM8960_H

/* WM8960 रेजिस्टर space */


#घोषणा WM8960_CACHEREGNUM 	56

#घोषणा WM8960_LINVOL		0x0
#घोषणा WM8960_RINVOL		0x1
#घोषणा WM8960_LOUT1		0x2
#घोषणा WM8960_ROUT1		0x3
#घोषणा WM8960_CLOCK1		0x4
#घोषणा WM8960_DACCTL1		0x5
#घोषणा WM8960_DACCTL2		0x6
#घोषणा WM8960_IFACE1		0x7
#घोषणा WM8960_CLOCK2		0x8
#घोषणा WM8960_IFACE2		0x9
#घोषणा WM8960_LDAC		0xa
#घोषणा WM8960_RDAC		0xb

#घोषणा WM8960_RESET		0xf
#घोषणा WM8960_3D		0x10
#घोषणा WM8960_ALC1		0x11
#घोषणा WM8960_ALC2		0x12
#घोषणा WM8960_ALC3		0x13
#घोषणा WM8960_NOISEG		0x14
#घोषणा WM8960_LADC		0x15
#घोषणा WM8960_RADC		0x16
#घोषणा WM8960_ADDCTL1		0x17
#घोषणा WM8960_ADDCTL2		0x18
#घोषणा WM8960_POWER1		0x19
#घोषणा WM8960_POWER2		0x1a
#घोषणा WM8960_ADDCTL3		0x1b
#घोषणा WM8960_APOP1		0x1c
#घोषणा WM8960_APOP2		0x1d

#घोषणा WM8960_LINPATH		0x20
#घोषणा WM8960_RINPATH		0x21
#घोषणा WM8960_LOUTMIX		0x22

#घोषणा WM8960_ROUTMIX		0x25
#घोषणा WM8960_MONOMIX1		0x26
#घोषणा WM8960_MONOMIX2		0x27
#घोषणा WM8960_LOUT2		0x28
#घोषणा WM8960_ROUT2		0x29
#घोषणा WM8960_MONO		0x2a
#घोषणा WM8960_INBMIX1		0x2b
#घोषणा WM8960_INBMIX2		0x2c
#घोषणा WM8960_BYPASS1		0x2d
#घोषणा WM8960_BYPASS2		0x2e
#घोषणा WM8960_POWER3		0x2f
#घोषणा WM8960_ADDCTL4		0x30
#घोषणा WM8960_CLASSD1		0x31

#घोषणा WM8960_CLASSD3		0x33
#घोषणा WM8960_PLL1		0x34
#घोषणा WM8960_PLL2		0x35
#घोषणा WM8960_PLL3		0x36
#घोषणा WM8960_PLL4		0x37


/*
 * WM8960 Clock भागiders
 */
#घोषणा WM8960_SYSCLKDIV 		0
#घोषणा WM8960_DACDIV			1
#घोषणा WM8960_OPCLKDIV			2
#घोषणा WM8960_DCLKDIV			3
#घोषणा WM8960_TOCLKSEL			4

#घोषणा WM8960_SYSCLK_DIV_1		(0 << 1)
#घोषणा WM8960_SYSCLK_DIV_2		(2 << 1)

#घोषणा WM8960_SYSCLK_MCLK		(0 << 0)
#घोषणा WM8960_SYSCLK_PLL		(1 << 0)
#घोषणा WM8960_SYSCLK_AUTO		(2 << 0)

#घोषणा WM8960_DAC_DIV_1		(0 << 3)
#घोषणा WM8960_DAC_DIV_1_5		(1 << 3)
#घोषणा WM8960_DAC_DIV_2		(2 << 3)
#घोषणा WM8960_DAC_DIV_3		(3 << 3)
#घोषणा WM8960_DAC_DIV_4		(4 << 3)
#घोषणा WM8960_DAC_DIV_5_5		(5 << 3)
#घोषणा WM8960_DAC_DIV_6		(6 << 3)

#घोषणा WM8960_DCLK_DIV_1_5		(0 << 6)
#घोषणा WM8960_DCLK_DIV_2		(1 << 6)
#घोषणा WM8960_DCLK_DIV_3		(2 << 6)
#घोषणा WM8960_DCLK_DIV_4		(3 << 6)
#घोषणा WM8960_DCLK_DIV_6		(4 << 6)
#घोषणा WM8960_DCLK_DIV_8		(5 << 6)
#घोषणा WM8960_DCLK_DIV_12		(6 << 6)
#घोषणा WM8960_DCLK_DIV_16		(7 << 6)

#घोषणा WM8960_TOCLK_F19		(0 << 1)
#घोषणा WM8960_TOCLK_F21		(1 << 1)

#घोषणा WM8960_OPCLK_DIV_1		(0 << 0)
#घोषणा WM8960_OPCLK_DIV_2		(1 << 0)
#घोषणा WM8960_OPCLK_DIV_3		(2 << 0)
#घोषणा WM8960_OPCLK_DIV_4		(3 << 0)
#घोषणा WM8960_OPCLK_DIV_5_5		(4 << 0)
#घोषणा WM8960_OPCLK_DIV_6		(5 << 0)

#पूर्ण_अगर
