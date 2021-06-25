<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Rockchip Electronics Co. Ltd.
 * Author: Xing Zheng <zhengxing@rock-chips.com>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RK3036_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RK3036_H

/* core घड़ीs */
#घोषणा PLL_APLL		1
#घोषणा PLL_DPLL		2
#घोषणा PLL_GPLL		3
#घोषणा ARMCLK			4

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_GPU		64
#घोषणा SCLK_SPI		65
#घोषणा SCLK_SDMMC		68
#घोषणा SCLK_SDIO		69
#घोषणा SCLK_EMMC		71
#घोषणा SCLK_न_अंकDC		76
#घोषणा SCLK_UART0		77
#घोषणा SCLK_UART1		78
#घोषणा SCLK_UART2		79
#घोषणा SCLK_I2S		82
#घोषणा SCLK_SPDIF		83
#घोषणा SCLK_TIMER0		85
#घोषणा SCLK_TIMER1		86
#घोषणा SCLK_TIMER2		87
#घोषणा SCLK_TIMER3		88
#घोषणा SCLK_OTGPHY0		93
#घोषणा SCLK_LCDC		100
#घोषणा SCLK_HDMI		109
#घोषणा SCLK_HEVC		111
#घोषणा SCLK_I2S_OUT		113
#घोषणा SCLK_SDMMC_DRV		114
#घोषणा SCLK_SDIO_DRV		115
#घोषणा SCLK_EMMC_DRV		117
#घोषणा SCLK_SDMMC_SAMPLE	118
#घोषणा SCLK_SDIO_SAMPLE	119
#घोषणा SCLK_EMMC_SAMPLE	121
#घोषणा SCLK_PVTM_CORE		123
#घोषणा SCLK_PVTM_GPU		124
#घोषणा SCLK_PVTM_VIDEO		125
#घोषणा SCLK_MAC		151
#घोषणा SCLK_MACREF		152
#घोषणा SCLK_MACPLL		153
#घोषणा SCLK_SFC		160

/* aclk gates */
#घोषणा ACLK_DMAC2		194
#घोषणा ACLK_LCDC		197
#घोषणा ACLK_VIO		203
#घोषणा ACLK_VCODEC		208
#घोषणा ACLK_CPU		209
#घोषणा ACLK_PERI		210

/* pclk gates */
#घोषणा PCLK_GPIO0		320
#घोषणा PCLK_GPIO1		321
#घोषणा PCLK_GPIO2		322
#घोषणा PCLK_GRF		329
#घोषणा PCLK_I2C0		332
#घोषणा PCLK_I2C1		333
#घोषणा PCLK_I2C2		334
#घोषणा PCLK_SPI		338
#घोषणा PCLK_UART0		341
#घोषणा PCLK_UART1		342
#घोषणा PCLK_UART2		343
#घोषणा PCLK_PWM		350
#घोषणा PCLK_TIMER		353
#घोषणा PCLK_HDMI		360
#घोषणा PCLK_CPU		362
#घोषणा PCLK_PERI		363
#घोषणा PCLK_DDRUPCTL		364
#घोषणा PCLK_WDT		368
#घोषणा PCLK_ACODEC		369

/* hclk gates */
#घोषणा HCLK_OTG0		449
#घोषणा HCLK_OTG1		450
#घोषणा HCLK_न_अंकDC		453
#घोषणा HCLK_SDMMC		456
#घोषणा HCLK_SDIO		457
#घोषणा HCLK_EMMC		459
#घोषणा HCLK_MAC		460
#घोषणा HCLK_I2S		462
#घोषणा HCLK_LCDC		465
#घोषणा HCLK_ROM		467
#घोषणा HCLK_VIO_BUS		472
#घोषणा HCLK_VCODEC		476
#घोषणा HCLK_CPU		477
#घोषणा HCLK_PERI		478

#घोषणा CLK_NR_CLKS		(HCLK_PERI + 1)

/* soft-reset indices */
#घोषणा SRST_CORE0		0
#घोषणा SRST_CORE1		1
#घोषणा SRST_CORE0_DBG		4
#घोषणा SRST_CORE1_DBG		5
#घोषणा SRST_CORE0_POR		8
#घोषणा SRST_CORE1_POR		9
#घोषणा SRST_L2C		12
#घोषणा SRST_TOPDBG		13
#घोषणा SRST_STRC_SYS_A		14
#घोषणा SRST_PD_CORE_NIU	15

#घोषणा SRST_TIMER2		16
#घोषणा SRST_CPUSYS_H		17
#घोषणा SRST_AHB2APB_H		19
#घोषणा SRST_TIMER3		20
#घोषणा SRST_INTMEM		21
#घोषणा SRST_ROM		22
#घोषणा SRST_PERI_NIU		23
#घोषणा SRST_I2S		24
#घोषणा SRST_DDR_PLL		25
#घोषणा SRST_GPU_DLL		26
#घोषणा SRST_TIMER0		27
#घोषणा SRST_TIMER1		28
#घोषणा SRST_CORE_DLL		29
#घोषणा SRST_EFUSE_P		30
#घोषणा SRST_ACODEC_P		31

#घोषणा SRST_GPIO0		32
#घोषणा SRST_GPIO1		33
#घोषणा SRST_GPIO2		34
#घोषणा SRST_UART0		39
#घोषणा SRST_UART1		40
#घोषणा SRST_UART2		41
#घोषणा SRST_I2C0		43
#घोषणा SRST_I2C1		44
#घोषणा SRST_I2C2		45
#घोषणा SRST_SFC		47

#घोषणा SRST_PWM0		48
#घोषणा SRST_DAP		51
#घोषणा SRST_DAP_SYS		52
#घोषणा SRST_GRF		55
#घोषणा SRST_PERIPHSYS_A	57
#घोषणा SRST_PERIPHSYS_H	58
#घोषणा SRST_PERIPHSYS_P	59
#घोषणा SRST_CPU_PERI		61
#घोषणा SRST_EMEM_PERI		62
#घोषणा SRST_USB_PERI		63

#घोषणा SRST_DMA2		64
#घोषणा SRST_MAC		66
#घोषणा SRST_न_अंकDC		68
#घोषणा SRST_USBOTG0		69
#घोषणा SRST_OTGC0		71
#घोषणा SRST_USBOTG1		72
#घोषणा SRST_OTGC1		74
#घोषणा SRST_DDRMSCH		79

#घोषणा SRST_MMC0		81
#घोषणा SRST_SDIO		82
#घोषणा SRST_EMMC		83
#घोषणा SRST_SPI0		84
#घोषणा SRST_WDT		86
#घोषणा SRST_DDRPHY		88
#घोषणा SRST_DDRPHY_P		89
#घोषणा SRST_DDRCTRL		90
#घोषणा SRST_DDRCTRL_P		91

#घोषणा SRST_HDMI_P		96
#घोषणा SRST_VIO_BUS_H		99
#घोषणा SRST_UTMI0		103
#घोषणा SRST_UTMI1		104
#घोषणा SRST_USBPOR		105

#घोषणा SRST_VCODEC_A		112
#घोषणा SRST_VCODEC_H		113
#घोषणा SRST_VIO1_A		114
#घोषणा SRST_HEVC		115
#घोषणा SRST_VCODEC_NIU_A	116
#घोषणा SRST_LCDC1_A		117
#घोषणा SRST_LCDC1_H		118
#घोषणा SRST_LCDC1_D		119
#घोषणा SRST_GPU		120
#घोषणा SRST_GPU_NIU_A		122

#घोषणा SRST_DBG_P		131

#पूर्ण_अगर
