<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014, Steffen Trumtrar <s.trumtrar@pengutronix.de>
 */

#अगर_अघोषित _DT_BINDINGS_RESET_ALTR_RST_MGR_A10_H
#घोषणा _DT_BINDINGS_RESET_ALTR_RST_MGR_A10_H

/* MPUMODRST */
#घोषणा CPU0_RESET		0
#घोषणा CPU1_RESET		1
#घोषणा WDS_RESET		2
#घोषणा SCUPER_RESET		3

/* PER0MODRST */
#घोषणा EMAC0_RESET		32
#घोषणा EMAC1_RESET		33
#घोषणा EMAC2_RESET		34
#घोषणा USB0_RESET		35
#घोषणा USB1_RESET		36
#घोषणा न_अंकD_RESET		37
#घोषणा QSPI_RESET		38
#घोषणा SDMMC_RESET		39
#घोषणा EMAC0_OCP_RESET		40
#घोषणा EMAC1_OCP_RESET		41
#घोषणा EMAC2_OCP_RESET		42
#घोषणा USB0_OCP_RESET		43
#घोषणा USB1_OCP_RESET		44
#घोषणा न_अंकD_OCP_RESET		45
#घोषणा QSPI_OCP_RESET		46
#घोषणा SDMMC_OCP_RESET		47
#घोषणा DMA_RESET		48
#घोषणा SPIM0_RESET		49
#घोषणा SPIM1_RESET		50
#घोषणा SPIS0_RESET		51
#घोषणा SPIS1_RESET		52
#घोषणा DMA_OCP_RESET		53
#घोषणा EMAC_PTP_RESET		54
/* 55 is empty*/
#घोषणा DMAIF0_RESET		56
#घोषणा DMAIF1_RESET		57
#घोषणा DMAIF2_RESET		58
#घोषणा DMAIF3_RESET		59
#घोषणा DMAIF4_RESET		60
#घोषणा DMAIF5_RESET		61
#घोषणा DMAIF6_RESET		62
#घोषणा DMAIF7_RESET		63

/* PER1MODRST */
#घोषणा L4WD0_RESET		64
#घोषणा L4WD1_RESET		65
#घोषणा L4SYSTIMER0_RESET	66
#घोषणा L4SYSTIMER1_RESET	67
#घोषणा SPTIMER0_RESET		68
#घोषणा SPTIMER1_RESET		69
/* 70-71 is reserved */
#घोषणा I2C0_RESET		72
#घोषणा I2C1_RESET		73
#घोषणा I2C2_RESET		74
#घोषणा I2C3_RESET		75
#घोषणा I2C4_RESET		76
/* 77-79 is reserved */
#घोषणा UART0_RESET		80
#घोषणा UART1_RESET		81
/* 82-87 is reserved */
#घोषणा GPIO0_RESET		88
#घोषणा GPIO1_RESET		89
#घोषणा GPIO2_RESET		90

/* BRGMODRST */
#घोषणा HPS2FPGA_RESET		96
#घोषणा LWHPS2FPGA_RESET	97
#घोषणा FPGA2HPS_RESET		98
#घोषणा F2SSDRAM0_RESET		99
#घोषणा F2SSDRAM1_RESET		100
#घोषणा F2SSDRAM2_RESET		101
#घोषणा DDRSCH_RESET		102

/* SYSMODRST*/
#घोषणा ROM_RESET		128
#घोषणा OCRAM_RESET		129
/* 130 is reserved */
#घोषणा FPGAMGR_RESET		131
#घोषणा S2F_RESET		132
#घोषणा SYSDBG_RESET		133
#घोषणा OCRAM_OCP_RESET		134

/* COLDMODRST */
#घोषणा CLKMGRCOLD_RESET	160
/* 161-162 is reserved */
#घोषणा S2FCOLD_RESET		163
#घोषणा TIMESTAMPCOLD_RESET	164
#घोषणा TAPCOLD_RESET		165
#घोषणा HMCCOLD_RESET		166
#घोषणा IOMGRCOLD_RESET		167

/* NRSTMODRST */
#घोषणा NRSTPINOE_RESET		192

/* DBGMODRST */
#घोषणा DBG_RESET		224
#पूर्ण_अगर
