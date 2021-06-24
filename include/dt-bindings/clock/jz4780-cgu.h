<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides घड़ी numbers क्रम the ingenic,jz4780-cgu DT binding.
 *
 * They are roughly ordered as:
 *   - बाह्यal घड़ीs
 *   - PLLs
 *   - muxes/भागiders in the order they appear in the jz4780 programmers manual
 *   - gates in order of their bit in the CLKGR* रेजिस्टरs
 */

#अगर_अघोषित __DT_BINDINGS_CLOCK_JZ4780_CGU_H__
#घोषणा __DT_BINDINGS_CLOCK_JZ4780_CGU_H__

#घोषणा JZ4780_CLK_EXCLK		0
#घोषणा JZ4780_CLK_RTCLK		1
#घोषणा JZ4780_CLK_APLL			2
#घोषणा JZ4780_CLK_MPLL			3
#घोषणा JZ4780_CLK_EPLL			4
#घोषणा JZ4780_CLK_VPLL			5
#घोषणा JZ4780_CLK_OTGPHY		6
#घोषणा JZ4780_CLK_SCLKA		7
#घोषणा JZ4780_CLK_CPUMUX		8
#घोषणा JZ4780_CLK_CPU			9
#घोषणा JZ4780_CLK_L2CACHE		10
#घोषणा JZ4780_CLK_AHB0			11
#घोषणा JZ4780_CLK_AHB2PMUX		12
#घोषणा JZ4780_CLK_AHB2			13
#घोषणा JZ4780_CLK_PCLK			14
#घोषणा JZ4780_CLK_DDR			15
#घोषणा JZ4780_CLK_VPU			16
#घोषणा JZ4780_CLK_I2SPLL		17
#घोषणा JZ4780_CLK_I2S			18
#घोषणा JZ4780_CLK_LCD0PIXCLK	19
#घोषणा JZ4780_CLK_LCD1PIXCLK	20
#घोषणा JZ4780_CLK_MSCMUX		21
#घोषणा JZ4780_CLK_MSC0			22
#घोषणा JZ4780_CLK_MSC1			23
#घोषणा JZ4780_CLK_MSC2			24
#घोषणा JZ4780_CLK_UHC			25
#घोषणा JZ4780_CLK_SSIPLL		26
#घोषणा JZ4780_CLK_SSI			27
#घोषणा JZ4780_CLK_CIMMCLK		28
#घोषणा JZ4780_CLK_PCMPLL		29
#घोषणा JZ4780_CLK_PCM			30
#घोषणा JZ4780_CLK_GPU			31
#घोषणा JZ4780_CLK_HDMI			32
#घोषणा JZ4780_CLK_BCH			33
#घोषणा JZ4780_CLK_NEMC			34
#घोषणा JZ4780_CLK_OTG0			35
#घोषणा JZ4780_CLK_SSI0			36
#घोषणा JZ4780_CLK_SMB0			37
#घोषणा JZ4780_CLK_SMB1			38
#घोषणा JZ4780_CLK_SCC			39
#घोषणा JZ4780_CLK_AIC			40
#घोषणा JZ4780_CLK_TSSI0		41
#घोषणा JZ4780_CLK_OWI			42
#घोषणा JZ4780_CLK_KBC			43
#घोषणा JZ4780_CLK_SADC			44
#घोषणा JZ4780_CLK_UART0		45
#घोषणा JZ4780_CLK_UART1		46
#घोषणा JZ4780_CLK_UART2		47
#घोषणा JZ4780_CLK_UART3		48
#घोषणा JZ4780_CLK_SSI1			49
#घोषणा JZ4780_CLK_SSI2			50
#घोषणा JZ4780_CLK_PDMA			51
#घोषणा JZ4780_CLK_GPS			52
#घोषणा JZ4780_CLK_MAC			53
#घोषणा JZ4780_CLK_SMB2			54
#घोषणा JZ4780_CLK_CIM			55
#घोषणा JZ4780_CLK_LCD			56
#घोषणा JZ4780_CLK_TVE			57
#घोषणा JZ4780_CLK_IPU			58
#घोषणा JZ4780_CLK_DDR0			59
#घोषणा JZ4780_CLK_DDR1			60
#घोषणा JZ4780_CLK_SMB3			61
#घोषणा JZ4780_CLK_TSSI1		62
#घोषणा JZ4780_CLK_COMPRESS		63
#घोषणा JZ4780_CLK_AIC1			64
#घोषणा JZ4780_CLK_GPVLC		65
#घोषणा JZ4780_CLK_OTG1			66
#घोषणा JZ4780_CLK_UART4		67
#घोषणा JZ4780_CLK_AHBMON		68
#घोषणा JZ4780_CLK_SMB4			69
#घोषणा JZ4780_CLK_DES			70
#घोषणा JZ4780_CLK_X2D			71
#घोषणा JZ4780_CLK_CORE1		72
#घोषणा JZ4780_CLK_EXCLK_DIV512	73
#घोषणा JZ4780_CLK_RTC			74

#पूर्ण_अगर /* __DT_BINDINGS_CLOCK_JZ4780_CGU_H__ */
