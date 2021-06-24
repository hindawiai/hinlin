<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * wm9713.h  --  WM9713 Soc Audio driver
 */

#अगर_अघोषित _WM9713_H
#घोषणा _WM9713_H

/* घड़ी inमाला_दो */
#घोषणा WM9713_CLKA_PIN			0
#घोषणा WM9713_CLKB_PIN			1

/* घड़ी भागider ID's */
#घोषणा WM9713_PCMCLK_DIV		0
#घोषणा WM9713_CLKA_MULT		1
#घोषणा WM9713_CLKB_MULT		2
#घोषणा WM9713_HIFI_DIV			3
#घोषणा WM9713_PCMBCLK_DIV		4
#घोषणा WM9713_PCMCLK_PLL_DIV           5
#घोषणा WM9713_HIFI_PLL_DIV             6

/* Calculate the appropriate bit mask क्रम the बाह्यal PCM घड़ी भागider */
#घोषणा WM9713_PCMDIV(x)	((x - 1) << 8)

/* Calculate the appropriate bit mask क्रम the बाह्यal HiFi घड़ी भागider */
#घोषणा WM9713_HIFIDIV(x)	((x - 1) << 12)

/* MCLK घड़ी mulitipliers */
#घोषणा WM9713_CLKA_X1		(0 << 1)
#घोषणा WM9713_CLKA_X2		(1 << 1)
#घोषणा WM9713_CLKB_X1		(0 << 2)
#घोषणा WM9713_CLKB_X2		(1 << 2)

/* MCLK घड़ी MUX */
#घोषणा WM9713_CLK_MUX_A		(0 << 0)
#घोषणा WM9713_CLK_MUX_B		(1 << 0)

/* Voice DAI BCLK भागider */
#घोषणा WM9713_PCMBCLK_DIV_1	(0 << 9)
#घोषणा WM9713_PCMBCLK_DIV_2	(1 << 9)
#घोषणा WM9713_PCMBCLK_DIV_4	(2 << 9)
#घोषणा WM9713_PCMBCLK_DIV_8	(3 << 9)
#घोषणा WM9713_PCMBCLK_DIV_16	(4 << 9)

#पूर्ण_अगर
