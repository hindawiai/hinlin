<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 Hisilicon Limited.
 *
 * Author: Bपूर्णांकian Wang <bपूर्णांकian.wang@huawei.com>
 */

#अगर_अघोषित __DT_BINDINGS_CLOCK_HI6220_H
#घोषणा __DT_BINDINGS_CLOCK_HI6220_H

/* clk in Hi6220 AO (always on) controller */
#घोषणा HI6220_NONE_CLOCK	0

/* fixed rate घड़ीs */
#घोषणा HI6220_REF32K		1
#घोषणा HI6220_CLK_TCXO		2
#घोषणा HI6220_MMC1_PAD		3
#घोषणा HI6220_MMC2_PAD		4
#घोषणा HI6220_MMC0_PAD		5
#घोषणा HI6220_PLL_BBP		6
#घोषणा HI6220_PLL_GPU		7
#घोषणा HI6220_PLL1_DDR		8
#घोषणा HI6220_PLL_SYS		9
#घोषणा HI6220_PLL_SYS_MEDIA	10
#घोषणा HI6220_DDR_SRC		11
#घोषणा HI6220_PLL_MEDIA	12
#घोषणा HI6220_PLL_DDR		13

/* fixed factor घड़ीs */
#घोषणा HI6220_300M		14
#घोषणा HI6220_150M		15
#घोषणा HI6220_PICOPHY_SRC	16
#घोषणा HI6220_MMC0_SRC_SEL	17
#घोषणा HI6220_MMC1_SRC_SEL	18
#घोषणा HI6220_MMC2_SRC_SEL	19
#घोषणा HI6220_VPU_CODEC	20
#घोषणा HI6220_MMC0_SMP		21
#घोषणा HI6220_MMC1_SMP		22
#घोषणा HI6220_MMC2_SMP		23

/* gate घड़ीs */
#घोषणा HI6220_WDT0_PCLK	24
#घोषणा HI6220_WDT1_PCLK	25
#घोषणा HI6220_WDT2_PCLK	26
#घोषणा HI6220_TIMER0_PCLK	27
#घोषणा HI6220_TIMER1_PCLK	28
#घोषणा HI6220_TIMER2_PCLK	29
#घोषणा HI6220_TIMER3_PCLK	30
#घोषणा HI6220_TIMER4_PCLK	31
#घोषणा HI6220_TIMER5_PCLK	32
#घोषणा HI6220_TIMER6_PCLK	33
#घोषणा HI6220_TIMER7_PCLK	34
#घोषणा HI6220_TIMER8_PCLK	35
#घोषणा HI6220_UART0_PCLK	36
#घोषणा HI6220_RTC0_PCLK	37
#घोषणा HI6220_RTC1_PCLK	38
#घोषणा HI6220_AO_NR_CLKS	39

/* clk in Hi6220 systrl */
/* gate घड़ी */
#घोषणा HI6220_MMC0_CLK		1
#घोषणा HI6220_MMC0_CIUCLK	2
#घोषणा HI6220_MMC1_CLK		3
#घोषणा HI6220_MMC1_CIUCLK	4
#घोषणा HI6220_MMC2_CLK		5
#घोषणा HI6220_MMC2_CIUCLK	6
#घोषणा HI6220_USBOTG_HCLK	7
#घोषणा HI6220_CLK_PICOPHY	8
#घोषणा HI6220_HIFI		9
#घोषणा HI6220_DACODEC_PCLK	10
#घोषणा HI6220_EDMAC_ACLK	11
#घोषणा HI6220_CS_ATB		12
#घोषणा HI6220_I2C0_CLK		13
#घोषणा HI6220_I2C1_CLK		14
#घोषणा HI6220_I2C2_CLK		15
#घोषणा HI6220_I2C3_CLK		16
#घोषणा HI6220_UART1_PCLK	17
#घोषणा HI6220_UART2_PCLK	18
#घोषणा HI6220_UART3_PCLK	19
#घोषणा HI6220_UART4_PCLK	20
#घोषणा HI6220_SPI_CLK		21
#घोषणा HI6220_TSENSOR_CLK	22
#घोषणा HI6220_MMU_CLK		23
#घोषणा HI6220_HIFI_SEL		24
#घोषणा HI6220_MMC0_SYSPLL	25
#घोषणा HI6220_MMC1_SYSPLL	26
#घोषणा HI6220_MMC2_SYSPLL	27
#घोषणा HI6220_MMC0_SEL		28
#घोषणा HI6220_MMC1_SEL		29
#घोषणा HI6220_BBPPLL_SEL	30
#घोषणा HI6220_MEDIA_PLL_SRC	31
#घोषणा HI6220_MMC2_SEL		32
#घोषणा HI6220_CS_ATB_SYSPLL	33

/* mux घड़ीs */
#घोषणा HI6220_MMC0_SRC		34
#घोषणा HI6220_MMC0_SMP_IN	35
#घोषणा HI6220_MMC1_SRC		36
#घोषणा HI6220_MMC1_SMP_IN	37
#घोषणा HI6220_MMC2_SRC		38
#घोषणा HI6220_MMC2_SMP_IN	39
#घोषणा HI6220_HIFI_SRC		40
#घोषणा HI6220_UART1_SRC	41
#घोषणा HI6220_UART2_SRC	42
#घोषणा HI6220_UART3_SRC	43
#घोषणा HI6220_UART4_SRC	44
#घोषणा HI6220_MMC0_MUX0	45
#घोषणा HI6220_MMC1_MUX0	46
#घोषणा HI6220_MMC2_MUX0	47
#घोषणा HI6220_MMC0_MUX1	48
#घोषणा HI6220_MMC1_MUX1	49
#घोषणा HI6220_MMC2_MUX1	50

/* भागider घड़ीs */
#घोषणा HI6220_CLK_BUS		51
#घोषणा HI6220_MMC0_DIV		52
#घोषणा HI6220_MMC1_DIV		53
#घोषणा HI6220_MMC2_DIV		54
#घोषणा HI6220_HIFI_DIV		55
#घोषणा HI6220_BBPPLL0_DIV	56
#घोषणा HI6220_CS_DAPB		57
#घोषणा HI6220_CS_ATB_DIV	58

/* gate घड़ी */
#घोषणा HI6220_DAPB_CLK		59

#घोषणा HI6220_SYS_NR_CLKS	60

/* clk in Hi6220 media controller */
/* gate घड़ीs */
#घोषणा HI6220_DSI_PCLK		1
#घोषणा HI6220_G3D_PCLK		2
#घोषणा HI6220_ACLK_CODEC_VPU	3
#घोषणा HI6220_ISP_SCLK		4
#घोषणा HI6220_ADE_CORE		5
#घोषणा HI6220_MED_MMU		6
#घोषणा HI6220_CFG_CSI4PHY	7
#घोषणा HI6220_CFG_CSI2PHY	8
#घोषणा HI6220_ISP_SCLK_GATE	9
#घोषणा HI6220_ISP_SCLK_GATE1	10
#घोषणा HI6220_ADE_CORE_GATE	11
#घोषणा HI6220_CODEC_VPU_GATE	12
#घोषणा HI6220_MED_SYSPLL	13

/* mux घड़ीs */
#घोषणा HI6220_1440_1200	14
#घोषणा HI6220_1000_1200	15
#घोषणा HI6220_1000_1440	16

/* भागider घड़ीs */
#घोषणा HI6220_CODEC_JPEG	17
#घोषणा HI6220_ISP_SCLK_SRC	18
#घोषणा HI6220_ISP_SCLK1	19
#घोषणा HI6220_ADE_CORE_SRC	20
#घोषणा HI6220_ADE_PIX_SRC	21
#घोषणा HI6220_G3D_CLK		22
#घोषणा HI6220_CODEC_VPU_SRC	23

#घोषणा HI6220_MEDIA_NR_CLKS	24

/* clk in Hi6220 घातer controller */
/* gate घड़ीs */
#घोषणा HI6220_PLL_GPU_GATE	1
#घोषणा HI6220_PLL1_DDR_GATE	2
#घोषणा HI6220_PLL_DDR_GATE	3
#घोषणा HI6220_PLL_MEDIA_GATE	4
#घोषणा HI6220_PLL0_BBP_GATE	5

/* भागider घड़ीs */
#घोषणा HI6220_DDRC_SRC		6
#घोषणा HI6220_DDRC_AXI1	7

#घोषणा HI6220_POWER_NR_CLKS	8

/* clk in Hi6220 acpu sctrl */
#घोषणा HI6220_ACPU_SFT_AT_S		0

#पूर्ण_अगर
