<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/plat-omap/include/mach/mux.h
 *
 * Table of the Omap रेजिस्टर configurations क्रम the FUNC_MUX and
 * PULL_DWN combinations.
 *
 * Copyright (C) 2004 - 2008 Texas Instruments Inc.
 * Copyright (C) 2003 - 2008 Nokia Corporation
 *
 * Written by Tony Lindgren
 *
 * NOTE: Please use the following naming style क्रम new pin entries.
 *	 For example, W8_1610_MMC2_DAT0, where:
 *	 - W8	     = ball
 *	 - 1610	     = 1510 or 1610, none अगर common क्रम both 1510 and 1610
 *	 - MMC2_DAT0 = function
 */

#अगर_अघोषित __ASM_ARCH_MUX_H
#घोषणा __ASM_ARCH_MUX_H

#घोषणा PU_PD_SEL_NA		0	/* No pu_pd reg available */
#घोषणा PULL_DWN_CTRL_NA	0	/* No pull-करोwn control needed */

#अगर_घोषित	CONFIG_OMAP_MUX_DEBUG
#घोषणा MUX_REG(reg, mode_offset, mode) .mux_reg_name = "FUNC_MUX_CTRL_"#reg, \
					.mux_reg = FUNC_MUX_CTRL_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#घोषणा PULL_REG(reg, bit, status)	.pull_name = "PULL_DWN_CTRL_"#reg, \
					.pull_reg = PULL_DWN_CTRL_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#घोषणा PU_PD_REG(reg, status)		.pu_pd_name = "PU_PD_SEL_"#reg, \
					.pu_pd_reg = PU_PD_SEL_##reg, \
					.pu_pd_val = status,

#घोषणा MUX_REG_7XX(reg, mode_offset, mode) .mux_reg_name = "OMAP7XX_IO_CONF_"#reg, \
					.mux_reg = OMAP7XX_IO_CONF_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#घोषणा PULL_REG_7XX(reg, bit, status)	.pull_name = "OMAP7XX_IO_CONF_"#reg, \
					.pull_reg = OMAP7XX_IO_CONF_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#अन्यथा

#घोषणा MUX_REG(reg, mode_offset, mode) .mux_reg = FUNC_MUX_CTRL_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#घोषणा PULL_REG(reg, bit, status)	.pull_reg = PULL_DWN_CTRL_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#घोषणा PU_PD_REG(reg, status)		.pu_pd_reg = PU_PD_SEL_##reg, \
					.pu_pd_val = status,

#घोषणा MUX_REG_7XX(reg, mode_offset, mode) \
					.mux_reg = OMAP7XX_IO_CONF_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#घोषणा PULL_REG_7XX(reg, bit, status)	.pull_reg = OMAP7XX_IO_CONF_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#पूर्ण_अगर /* CONFIG_OMAP_MUX_DEBUG */

#घोषणा MUX_CFG(desc, mux_reg, mode_offset, mode,	\
		pull_reg, pull_bit, pull_status,	\
		pu_pd_reg, pu_pd_status, debug_status)	\
अणु							\
	.name =	 desc,					\
	.debug = debug_status,				\
	MUX_REG(mux_reg, mode_offset, mode)		\
	PULL_REG(pull_reg, pull_bit, pull_status)	\
	PU_PD_REG(pu_pd_reg, pu_pd_status)		\
पूर्ण,


/*
 * OMAP730/850 has a slightly dअगरferent config क्रम the pin mux.
 * - config regs are the OMAP7XX_IO_CONF_x regs (see omap7xx.h) regs and
 *   not the FUNC_MUX_CTRL_x regs from hardware.h
 * - क्रम pull-up/करोwn, only has one enable bit which is in the same रेजिस्टर
 *   as mux config
 */
#घोषणा MUX_CFG_7XX(desc, mux_reg, mode_offset, mode,	\
		   pull_bit, pull_status, debug_status)\
अणु							\
	.name =	 desc,					\
	.debug = debug_status,				\
	MUX_REG_7XX(mux_reg, mode_offset, mode)		\
	PULL_REG_7XX(mux_reg, pull_bit, pull_status)	\
	PU_PD_REG(NA, 0)		\
पूर्ण,

काष्ठा pin_config अणु
	अक्षर 			*name;
	स्थिर अचिन्हित पूर्णांक 	mux_reg;
	अचिन्हित अक्षर		debug;

	स्थिर अचिन्हित अक्षर mask_offset;
	स्थिर अचिन्हित अक्षर mask;

	स्थिर अक्षर *pull_name;
	स्थिर अचिन्हित पूर्णांक pull_reg;
	स्थिर अचिन्हित अक्षर pull_val;
	स्थिर अचिन्हित अक्षर pull_bit;

	स्थिर अक्षर *pu_pd_name;
	स्थिर अचिन्हित पूर्णांक pu_pd_reg;
	स्थिर अचिन्हित अक्षर pu_pd_val;

#अगर	defined(CONFIG_OMAP_MUX_DEBUG) || defined(CONFIG_OMAP_MUX_WARNINGS)
	स्थिर अक्षर *mux_reg_name;
#पूर्ण_अगर

पूर्ण;

क्रमागत omap7xx_index अणु
	/* OMAP 730 keyboard */
	E2_7XX_KBR0,
	J7_7XX_KBR1,
	E1_7XX_KBR2,
	F3_7XX_KBR3,
	D2_7XX_KBR4,
	C2_7XX_KBC0,
	D3_7XX_KBC1,
	E4_7XX_KBC2,
	F4_7XX_KBC3,
	E3_7XX_KBC4,

	/* USB */
	AA17_7XX_USB_DM,
	W16_7XX_USB_PU_EN,
	W17_7XX_USB_VBUSI,
	W18_7XX_USB_DMCK_OUT,
	W19_7XX_USB_DCRST,

	/* MMC */
	MMC_7XX_CMD,
	MMC_7XX_CLK,
	MMC_7XX_DAT0,

	/* I2C */
	I2C_7XX_SCL,
	I2C_7XX_SDA,

	/* SPI */
	SPI_7XX_1,
	SPI_7XX_2,
	SPI_7XX_3,
	SPI_7XX_4,
	SPI_7XX_5,
	SPI_7XX_6,

	/* UART */
	UART_7XX_1,
	UART_7XX_2,
पूर्ण;

क्रमागत omap1xxx_index अणु
	/* UART1 (BT_UART_GATING)*/
	UART1_TX = 0,
	UART1_RTS,

	/* UART2 (COM_UART_GATING)*/
	UART2_TX,
	UART2_RX,
	UART2_CTS,
	UART2_RTS,

	/* UART3 (GIGA_UART_GATING) */
	UART3_TX,
	UART3_RX,
	UART3_CTS,
	UART3_RTS,
	UART3_CLKREQ,
	UART3_BCLK,	/* 12MHz घड़ी out */
	Y15_1610_UART3_RTS,

	/* PWT & PWL */
	PWT,
	PWL,

	/* USB master generic */
	R18_USB_VBUS,
	R18_1510_USB_GPIO0,
	W4_USB_PUEN,
	W4_USB_CLKO,
	W4_USB_HIGHZ,
	W4_GPIO58,

	/* USB1 master */
	USB1_SUSP,
	USB1_SEO,
	W13_1610_USB1_SE0,
	USB1_TXEN,
	USB1_TXD,
	USB1_VP,
	USB1_VM,
	USB1_RCV,
	USB1_SPEED,
	R13_1610_USB1_SPEED,
	R13_1710_USB1_SE0,

	/* USB2 master */
	USB2_SUSP,
	USB2_VP,
	USB2_TXEN,
	USB2_VM,
	USB2_RCV,
	USB2_SEO,
	USB2_TXD,

	/* OMAP-1510 GPIO */
	R18_1510_GPIO0,
	R19_1510_GPIO1,
	M14_1510_GPIO2,

	/* OMAP1610 GPIO */
	P18_1610_GPIO3,
	Y15_1610_GPIO17,

	/* OMAP-1710 GPIO */
	R18_1710_GPIO0,
	V2_1710_GPIO10,
	N21_1710_GPIO14,
	W15_1710_GPIO40,

	/* MPUIO */
	MPUIO2,
	N15_1610_MPUIO2,
	MPUIO4,
	MPUIO5,
	T20_1610_MPUIO5,
	W11_1610_MPUIO6,
	V10_1610_MPUIO7,
	W11_1610_MPUIO9,
	V10_1610_MPUIO10,
	W10_1610_MPUIO11,
	E20_1610_MPUIO13,
	U20_1610_MPUIO14,
	E19_1610_MPUIO15,

	/* MCBSP2 */
	MCBSP2_CLKR,
	MCBSP2_CLKX,
	MCBSP2_DR,
	MCBSP2_DX,
	MCBSP2_FSR,
	MCBSP2_FSX,

	/* MCBSP3 */
	MCBSP3_CLKX,

	/* Misc ballouts */
	BALLOUT_V8_ARMIO3,
	N20_HDQ,

	/* OMAP-1610 MMC2 */
	W8_1610_MMC2_DAT0,
	V8_1610_MMC2_DAT1,
	W15_1610_MMC2_DAT2,
	R10_1610_MMC2_DAT3,
	Y10_1610_MMC2_CLK,
	Y8_1610_MMC2_CMD,
	V9_1610_MMC2_CMDसूची,
	V5_1610_MMC2_DATसूची0,
	W19_1610_MMC2_DATसूची1,
	R18_1610_MMC2_CLKIN,

	/* OMAP-1610 External Trace Interface */
	M19_1610_ETM_PSTAT0,
	L15_1610_ETM_PSTAT1,
	L18_1610_ETM_PSTAT2,
	L19_1610_ETM_D0,
	J19_1610_ETM_D6,
	J18_1610_ETM_D7,

	/* OMAP16XX GPIO */
	P20_1610_GPIO4,
	V9_1610_GPIO7,
	W8_1610_GPIO9,
	N20_1610_GPIO11,
	N19_1610_GPIO13,
	P10_1610_GPIO22,
	V5_1610_GPIO24,
	AA20_1610_GPIO_41,
	W19_1610_GPIO48,
	M7_1610_GPIO62,
	V14_16XX_GPIO37,
	R9_16XX_GPIO18,
	L14_16XX_GPIO49,

	/* OMAP-1610 uWire */
	V19_1610_UWIRE_SCLK,
	U18_1610_UWIRE_SDI,
	W21_1610_UWIRE_SDO,
	N14_1610_UWIRE_CS0,
	P15_1610_UWIRE_CS3,
	N15_1610_UWIRE_CS1,

	/* OMAP-1610 SPI */
	U19_1610_SPIF_SCK,
	U18_1610_SPIF_DIN,
	P20_1610_SPIF_DIN,
	W21_1610_SPIF_DOUT,
	R18_1610_SPIF_DOUT,
	N14_1610_SPIF_CS0,
	N15_1610_SPIF_CS1,
	T19_1610_SPIF_CS2,
	P15_1610_SPIF_CS3,

	/* OMAP-1610 Flash */
	L3_1610_FLASH_CS2B_OE,
	M8_1610_FLASH_CS2B_WE,

	/* First MMC */
	MMC_CMD,
	MMC_DAT1,
	MMC_DAT2,
	MMC_DAT0,
	MMC_CLK,
	MMC_DAT3,

	/* OMAP-1710 MMC CMDसूची and DATसूची0 */
	M15_1710_MMC_CLKI,
	P19_1710_MMC_CMDसूची,
	P20_1710_MMC_DATसूची0,

	/* OMAP-1610 USB0 alternate pin configuration */
	W9_USB0_TXEN,
	AA9_USB0_VP,
	Y5_USB0_RCV,
	R9_USB0_VM,
	V6_USB0_TXD,
	W5_USB0_SE0,
	V9_USB0_SPEED,
	V9_USB0_SUSP,

	/* USB2 */
	W9_USB2_TXEN,
	AA9_USB2_VP,
	Y5_USB2_RCV,
	R9_USB2_VM,
	V6_USB2_TXD,
	W5_USB2_SE0,

	/* 16XX UART */
	R13_1610_UART1_TX,
	V14_16XX_UART1_RX,
	R14_1610_UART1_CTS,
	AA15_1610_UART1_RTS,
	R9_16XX_UART2_RX,
	L14_16XX_UART3_RX,

	/* I2C OMAP-1610 */
	I2C_SCL,
	I2C_SDA,

	/* Keypad */
	F18_1610_KBC0,
	D20_1610_KBC1,
	D19_1610_KBC2,
	E18_1610_KBC3,
	C21_1610_KBC4,
	G18_1610_KBR0,
	F19_1610_KBR1,
	H14_1610_KBR2,
	E20_1610_KBR3,
	E19_1610_KBR4,
	N19_1610_KBR5,

	/* Power management */
	T20_1610_LOW_PWR,

	/* MCLK Settings */
	V5_1710_MCLK_ON,
	V5_1710_MCLK_OFF,
	R10_1610_MCLK_ON,
	R10_1610_MCLK_OFF,

	/* CompactFlash controller */
	P11_1610_CF_CD2,
	R11_1610_CF_IOIS16,
	V10_1610_CF_IREQ,
	W10_1610_CF_RESET,
	W11_1610_CF_CD1,

	/* parallel camera */
	J15_1610_CAM_LCLK,
	J18_1610_CAM_D7,
	J19_1610_CAM_D6,
	J14_1610_CAM_D5,
	K18_1610_CAM_D4,
	K19_1610_CAM_D3,
	K15_1610_CAM_D2,
	K14_1610_CAM_D1,
	L19_1610_CAM_D0,
	L18_1610_CAM_VS,
	L15_1610_CAM_HS,
	M19_1610_CAM_RSTZ,
	Y15_1610_CAM_OUTCLK,

	/* serial camera */
	H19_1610_CAM_EXCLK,
	Y12_1610_CCP_CLKP,
	W13_1610_CCP_CLKM,
	W14_1610_CCP_DATAP,
	Y14_1610_CCP_DATAM,

पूर्ण;

काष्ठा omap_mux_cfg अणु
	काष्ठा pin_config	*pins;
	अचिन्हित दीर्घ		size;
	पूर्णांक			(*cfg_reg)(स्थिर काष्ठा pin_config *cfg);
पूर्ण;

#अगर_घोषित	CONFIG_OMAP_MUX
/* setup pin muxing in Linux */
बाह्य पूर्णांक omap1_mux_init(व्योम);
बाह्य पूर्णांक omap_mux_रेजिस्टर(काष्ठा omap_mux_cfg *);
बाह्य पूर्णांक omap_cfg_reg(अचिन्हित दीर्घ reg_cfg);
#अन्यथा
/* boot loader करोes it all (no warnings from CONFIG_OMAP_MUX_WARNINGS) */
अटल अंतरभूत पूर्णांक omap1_mux_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक omap_cfg_reg(अचिन्हित दीर्घ reg_cfg) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक omap2_mux_init(व्योम);

#पूर्ण_अगर
