<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sपंचांग32fx-घड़ी.h
 *
 * Copyright (C) 2016 STMicroelectronics
 * Author: Gabriel Fernandez क्रम STMicroelectronics.
 */

/*
 * List of घड़ीs wich are not derived from प्रणाली घड़ी (SYSCLOCK)
 *
 * The index of these घड़ीs is the secondary index of DT bindings
 * (see Documentम_से_पn/devicetree/bindings/घड़ी/st,sपंचांग32-rcc.txt)
 *
 * e.g:
	<asचिन्हित-घड़ीs = <&rcc 1 CLK_LSE>;
*/

#अगर_अघोषित _DT_BINDINGS_CLK_STMFX_H
#घोषणा _DT_BINDINGS_CLK_STMFX_H

#घोषणा SYSTICK			0
#घोषणा FCLK			1
#घोषणा CLK_LSI			2
#घोषणा CLK_LSE			3
#घोषणा CLK_HSE_RTC		4
#घोषणा CLK_RTC			5
#घोषणा PLL_VCO_I2S		6
#घोषणा PLL_VCO_SAI		7
#घोषणा CLK_LCD			8
#घोषणा CLK_I2S			9
#घोषणा CLK_SAI1		10
#घोषणा CLK_SAI2		11
#घोषणा CLK_I2SQ_PDIV		12
#घोषणा CLK_SAIQ_PDIV		13
#घोषणा CLK_HSI			14
#घोषणा CLK_SYSCLK		15
#घोषणा CLK_F469_DSI		16

#घोषणा END_PRIMARY_CLK		17

#घोषणा CLK_HDMI_CEC		16
#घोषणा CLK_SPDIF		17
#घोषणा CLK_USART1		18
#घोषणा CLK_USART2		19
#घोषणा CLK_USART3		20
#घोषणा CLK_UART4		21
#घोषणा CLK_UART5		22
#घोषणा CLK_USART6		23
#घोषणा CLK_UART7		24
#घोषणा CLK_UART8		25
#घोषणा CLK_I2C1		26
#घोषणा CLK_I2C2		27
#घोषणा CLK_I2C3		28
#घोषणा CLK_I2C4		29
#घोषणा CLK_LPTIMER		30
#घोषणा CLK_PLL_SRC		31
#घोषणा CLK_DFSDM1		32
#घोषणा CLK_ADFSDM1		33
#घोषणा CLK_F769_DSI		34
#घोषणा END_PRIMARY_CLK_F7	35

#पूर्ण_अगर
