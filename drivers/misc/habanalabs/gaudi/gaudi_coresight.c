<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2018 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "gaudiP.h"
#समावेश "../include/gaudi/gaudi_coresight.h"
#समावेश "../include/gaudi/asic_reg/gaudi_regs.h"
#समावेश "../include/gaudi/gaudi_masks.h"
#समावेश "../include/gaudi/gaudi_reg_map.h"

#समावेश <uapi/misc/habanaद_असल.h>
#घोषणा SPMU_SECTION_SIZE		MME0_ACC_SPMU_MAX_OFFSET
#घोषणा SPMU_EVENT_TYPES_OFFSET		0x400
#घोषणा SPMU_MAX_COUNTERS		6

अटल u64 debug_sपंचांग_regs[GAUDI_STM_LAST + 1] = अणु
	[GAUDI_STM_MME0_ACC]	= mmMME0_ACC_STM_BASE,
	[GAUDI_STM_MME0_SBAB]	= mmMME0_SBAB_STM_BASE,
	[GAUDI_STM_MME0_CTRL]	= mmMME0_CTRL_STM_BASE,
	[GAUDI_STM_MME1_ACC]	= mmMME1_ACC_STM_BASE,
	[GAUDI_STM_MME1_SBAB]	= mmMME1_SBAB_STM_BASE,
	[GAUDI_STM_MME1_CTRL]	= mmMME1_CTRL_STM_BASE,
	[GAUDI_STM_MME2_ACC]	= mmMME2_ACC_STM_BASE,
	[GAUDI_STM_MME2_SBAB]	= mmMME2_SBAB_STM_BASE,
	[GAUDI_STM_MME2_CTRL]	= mmMME2_CTRL_STM_BASE,
	[GAUDI_STM_MME3_ACC]	= mmMME3_ACC_STM_BASE,
	[GAUDI_STM_MME3_SBAB]	= mmMME3_SBAB_STM_BASE,
	[GAUDI_STM_MME3_CTRL]	= mmMME3_CTRL_STM_BASE,
	[GAUDI_STM_DMA_IF_W_S]	= mmDMA_IF_W_S_STM_BASE,
	[GAUDI_STM_DMA_IF_E_S]	= mmDMA_IF_E_S_STM_BASE,
	[GAUDI_STM_DMA_IF_W_N]	= mmDMA_IF_W_N_STM_BASE,
	[GAUDI_STM_DMA_IF_E_N]	= mmDMA_IF_E_N_STM_BASE,
	[GAUDI_STM_CPU]		= mmCPU_STM_BASE,
	[GAUDI_STM_DMA_CH_0_CS]	= mmDMA_CH_0_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_1_CS]	= mmDMA_CH_1_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_2_CS]	= mmDMA_CH_2_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_3_CS]	= mmDMA_CH_3_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_4_CS]	= mmDMA_CH_4_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_5_CS]	= mmDMA_CH_5_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_6_CS]	= mmDMA_CH_6_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_7_CS]	= mmDMA_CH_7_CS_STM_BASE,
	[GAUDI_STM_PCIE]	= mmPCIE_STM_BASE,
	[GAUDI_STM_MMU_CS]	= mmMMU_CS_STM_BASE,
	[GAUDI_STM_PSOC]	= mmPSOC_STM_BASE,
	[GAUDI_STM_NIC0_0]	= mmSTM_0_NIC0_DBG_BASE,
	[GAUDI_STM_NIC0_1]	= mmSTM_1_NIC0_DBG_BASE,
	[GAUDI_STM_NIC1_0]	= mmSTM_0_NIC1_DBG_BASE,
	[GAUDI_STM_NIC1_1]	= mmSTM_1_NIC1_DBG_BASE,
	[GAUDI_STM_NIC2_0]	= mmSTM_0_NIC2_DBG_BASE,
	[GAUDI_STM_NIC2_1]	= mmSTM_1_NIC2_DBG_BASE,
	[GAUDI_STM_NIC3_0]	= mmSTM_0_NIC3_DBG_BASE,
	[GAUDI_STM_NIC3_1]	= mmSTM_1_NIC3_DBG_BASE,
	[GAUDI_STM_NIC4_0]	= mmSTM_0_NIC4_DBG_BASE,
	[GAUDI_STM_NIC4_1]	= mmSTM_1_NIC4_DBG_BASE,
	[GAUDI_STM_TPC0_EML]	= mmTPC0_EML_STM_BASE,
	[GAUDI_STM_TPC1_EML]	= mmTPC1_EML_STM_BASE,
	[GAUDI_STM_TPC2_EML]	= mmTPC2_EML_STM_BASE,
	[GAUDI_STM_TPC3_EML]	= mmTPC3_EML_STM_BASE,
	[GAUDI_STM_TPC4_EML]	= mmTPC4_EML_STM_BASE,
	[GAUDI_STM_TPC5_EML]	= mmTPC5_EML_STM_BASE,
	[GAUDI_STM_TPC6_EML]	= mmTPC6_EML_STM_BASE,
	[GAUDI_STM_TPC7_EML]	= mmTPC7_EML_STM_BASE
पूर्ण;

अटल u64 debug_etf_regs[GAUDI_ETF_LAST + 1] = अणु
	[GAUDI_ETF_MME0_ACC]		= mmMME0_ACC_ETF_BASE,
	[GAUDI_ETF_MME0_SBAB]		= mmMME0_SBAB_ETF_BASE,
	[GAUDI_ETF_MME0_CTRL]		= mmMME0_CTRL_ETF_BASE,
	[GAUDI_ETF_MME1_ACC]		= mmMME1_ACC_ETF_BASE,
	[GAUDI_ETF_MME1_SBAB]		= mmMME1_SBAB_ETF_BASE,
	[GAUDI_ETF_MME1_CTRL]		= mmMME1_CTRL_ETF_BASE,
	[GAUDI_ETF_MME2_ACC]		= mmMME2_MME2_ACC_ETF_BASE,
	[GAUDI_ETF_MME2_SBAB]		= mmMME2_SBAB_ETF_BASE,
	[GAUDI_ETF_MME2_CTRL]		= mmMME2_CTRL_ETF_BASE,
	[GAUDI_ETF_MME3_ACC]		= mmMME3_ACC_ETF_BASE,
	[GAUDI_ETF_MME3_SBAB]		= mmMME3_SBAB_ETF_BASE,
	[GAUDI_ETF_MME3_CTRL]		= mmMME3_CTRL_ETF_BASE,
	[GAUDI_ETF_DMA_IF_W_S]		= mmDMA_IF_W_S_ETF_BASE,
	[GAUDI_ETF_DMA_IF_E_S]		= mmDMA_IF_E_S_ETF_BASE,
	[GAUDI_ETF_DMA_IF_W_N]		= mmDMA_IF_W_N_ETF_BASE,
	[GAUDI_ETF_DMA_IF_E_N]		= mmDMA_IF_E_N_ETF_BASE,
	[GAUDI_ETF_CPU_0]		= mmCPU_ETF_0_BASE,
	[GAUDI_ETF_CPU_1]		= mmCPU_ETF_1_BASE,
	[GAUDI_ETF_CPU_TRACE]		= mmCPU_ETF_TRACE_BASE,
	[GAUDI_ETF_DMA_CH_0_CS]		= mmDMA_CH_0_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_1_CS]		= mmDMA_CH_1_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_2_CS]		= mmDMA_CH_2_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_3_CS]		= mmDMA_CH_3_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_4_CS]		= mmDMA_CH_4_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_5_CS]		= mmDMA_CH_5_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_6_CS]		= mmDMA_CH_6_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_7_CS]		= mmDMA_CH_7_CS_ETF_BASE,
	[GAUDI_ETF_PCIE]		= mmPCIE_ETF_BASE,
	[GAUDI_ETF_MMU_CS]		= mmMMU_CS_ETF_BASE,
	[GAUDI_ETF_PSOC]		= mmPSOC_ETF_BASE,
	[GAUDI_ETF_NIC0_0]		= mmETF_0_NIC0_DBG_BASE,
	[GAUDI_ETF_NIC0_1]		= mmETF_1_NIC0_DBG_BASE,
	[GAUDI_ETF_NIC1_0]		= mmETF_0_NIC1_DBG_BASE,
	[GAUDI_ETF_NIC1_1]		= mmETF_1_NIC1_DBG_BASE,
	[GAUDI_ETF_NIC2_0]		= mmETF_0_NIC2_DBG_BASE,
	[GAUDI_ETF_NIC2_1]		= mmETF_1_NIC2_DBG_BASE,
	[GAUDI_ETF_NIC3_0]		= mmETF_0_NIC3_DBG_BASE,
	[GAUDI_ETF_NIC3_1]		= mmETF_1_NIC3_DBG_BASE,
	[GAUDI_ETF_NIC4_0]		= mmETF_0_NIC4_DBG_BASE,
	[GAUDI_ETF_NIC4_1]		= mmETF_1_NIC4_DBG_BASE,
	[GAUDI_ETF_TPC0_EML]		= mmTPC0_EML_ETF_BASE,
	[GAUDI_ETF_TPC1_EML]		= mmTPC1_EML_ETF_BASE,
	[GAUDI_ETF_TPC2_EML]		= mmTPC2_EML_ETF_BASE,
	[GAUDI_ETF_TPC3_EML]		= mmTPC3_EML_ETF_BASE,
	[GAUDI_ETF_TPC4_EML]		= mmTPC4_EML_ETF_BASE,
	[GAUDI_ETF_TPC5_EML]		= mmTPC5_EML_ETF_BASE,
	[GAUDI_ETF_TPC6_EML]		= mmTPC6_EML_ETF_BASE,
	[GAUDI_ETF_TPC7_EML]		= mmTPC7_EML_ETF_BASE
पूर्ण;

अटल u64 debug_funnel_regs[GAUDI_FUNNEL_LAST + 1] = अणु
	[GAUDI_FUNNEL_MME0_ACC]		= mmMME0_ACC_FUNNEL_BASE,
	[GAUDI_FUNNEL_MME1_ACC]		= mmMME1_ACC_FUNNEL_BASE,
	[GAUDI_FUNNEL_MME2_ACC]		= mmMME2_ACC_FUNNEL_BASE,
	[GAUDI_FUNNEL_MME3_ACC]		= mmMME3_ACC_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X0]	= mmSRAM_Y0_X0_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X1]	= mmSRAM_Y0_X1_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X2]	= mmSRAM_Y0_X2_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X3]	= mmSRAM_Y0_X3_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X4]	= mmSRAM_Y0_X4_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X5]	= mmSRAM_Y0_X5_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X6]	= mmSRAM_Y0_X6_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y0_X7]	= mmSRAM_Y0_X7_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X0]	= mmSRAM_Y1_X0_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X1]	= mmSRAM_Y1_X1_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X2]	= mmSRAM_Y1_X2_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X3]	= mmSRAM_Y1_X3_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X4]	= mmSRAM_Y1_X4_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X5]	= mmSRAM_Y1_X5_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X6]	= mmSRAM_Y1_X6_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y1_X7]	= mmSRAM_Y1_X7_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X0]	= mmSRAM_Y2_X0_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X1]	= mmSRAM_Y2_X1_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X2]	= mmSRAM_Y2_X2_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X3]	= mmSRAM_Y2_X3_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X4]	= mmSRAM_Y2_X4_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X5]	= mmSRAM_Y2_X5_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X6]	= mmSRAM_Y2_X6_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y2_X7]	= mmSRAM_Y2_X7_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X0]	= mmSRAM_Y3_X0_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X1]	= mmSRAM_Y3_X1_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X2]	= mmSRAM_Y3_X2_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X4]	= mmSRAM_Y3_X4_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X3]	= mmSRAM_Y3_X3_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X5]	= mmSRAM_Y3_X5_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X6]	= mmSRAM_Y3_X6_FUNNEL_BASE,
	[GAUDI_FUNNEL_SRAM_Y3_X7]	= mmSRAM_Y3_X7_FUNNEL_BASE,
	[GAUDI_FUNNEL_SIF_0]		= mmSIF_FUNNEL_0_BASE,
	[GAUDI_FUNNEL_SIF_1]		= mmSIF_FUNNEL_1_BASE,
	[GAUDI_FUNNEL_SIF_2]		= mmSIF_FUNNEL_2_BASE,
	[GAUDI_FUNNEL_SIF_3]		= mmSIF_FUNNEL_3_BASE,
	[GAUDI_FUNNEL_SIF_4]		= mmSIF_FUNNEL_4_BASE,
	[GAUDI_FUNNEL_SIF_5]		= mmSIF_FUNNEL_5_BASE,
	[GAUDI_FUNNEL_SIF_6]		= mmSIF_FUNNEL_6_BASE,
	[GAUDI_FUNNEL_SIF_7]		= mmSIF_FUNNEL_7_BASE,
	[GAUDI_FUNNEL_NIF_0]		= mmNIF_FUNNEL_0_BASE,
	[GAUDI_FUNNEL_NIF_1]		= mmNIF_FUNNEL_1_BASE,
	[GAUDI_FUNNEL_NIF_2]		= mmNIF_FUNNEL_2_BASE,
	[GAUDI_FUNNEL_NIF_3]		= mmNIF_FUNNEL_3_BASE,
	[GAUDI_FUNNEL_NIF_4]		= mmNIF_FUNNEL_4_BASE,
	[GAUDI_FUNNEL_NIF_5]		= mmNIF_FUNNEL_5_BASE,
	[GAUDI_FUNNEL_NIF_6]		= mmNIF_FUNNEL_6_BASE,
	[GAUDI_FUNNEL_NIF_7]		= mmNIF_FUNNEL_7_BASE,
	[GAUDI_FUNNEL_DMA_IF_W_S]	= mmDMA_IF_W_S_FUNNEL_BASE,
	[GAUDI_FUNNEL_DMA_IF_E_S]	= mmDMA_IF_E_S_FUNNEL_BASE,
	[GAUDI_FUNNEL_DMA_IF_W_N]	= mmDMA_IF_W_N_FUNNEL_BASE,
	[GAUDI_FUNNEL_DMA_IF_E_N]	= mmDMA_IF_E_N_FUNNEL_BASE,
	[GAUDI_FUNNEL_CPU]		= mmCPU_FUNNEL_BASE,
	[GAUDI_FUNNEL_NIC_TPC_W_S]	= mmNIC_TPC_FUNNEL_W_S_BASE,
	[GAUDI_FUNNEL_NIC_TPC_E_S]	= mmNIC_TPC_FUNNEL_E_S_BASE,
	[GAUDI_FUNNEL_NIC_TPC_W_N]	= mmNIC_TPC_FUNNEL_W_N_BASE,
	[GAUDI_FUNNEL_NIC_TPC_E_N]	= mmNIC_TPC_FUNNEL_E_N_BASE,
	[GAUDI_FUNNEL_PCIE]		= mmPCIE_FUNNEL_BASE,
	[GAUDI_FUNNEL_PSOC]		= mmPSOC_FUNNEL_BASE,
	[GAUDI_FUNNEL_NIC0]		= mmFUNNEL_NIC0_DBG_BASE,
	[GAUDI_FUNNEL_NIC1]		= mmFUNNEL_NIC1_DBG_BASE,
	[GAUDI_FUNNEL_NIC2]		= mmFUNNEL_NIC2_DBG_BASE,
	[GAUDI_FUNNEL_NIC3]		= mmFUNNEL_NIC3_DBG_BASE,
	[GAUDI_FUNNEL_NIC4]		= mmFUNNEL_NIC4_DBG_BASE,
	[GAUDI_FUNNEL_TPC0_EML]		= mmTPC0_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC1_EML]		= mmTPC1_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC2_EML]		= mmTPC2_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC3_EML]		= mmTPC3_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC4_EML]		= mmTPC4_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC5_EML]		= mmTPC5_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC6_EML]		= mmTPC6_EML_FUNNEL_BASE,
	[GAUDI_FUNNEL_TPC7_EML]		= mmTPC7_EML_FUNNEL_BASE
पूर्ण;

अटल u64 debug_bmon_regs[GAUDI_BMON_LAST + 1] = अणु
	[GAUDI_BMON_MME0_ACC_0]		= mmMME0_ACC_BMON0_BASE,
	[GAUDI_BMON_MME0_SBAB_0]	= mmMME0_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME0_SBAB_1]	= mmMME0_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME0_CTRL_0]	= mmMME0_CTRL_BMON0_BASE,
	[GAUDI_BMON_MME0_CTRL_1]	= mmMME0_CTRL_BMON1_BASE,
	[GAUDI_BMON_MME1_ACC_0]		= mmMME1_ACC_BMON0_BASE,
	[GAUDI_BMON_MME1_SBAB_0]	= mmMME1_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME1_SBAB_1]	= mmMME1_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME1_CTRL_0]	= mmMME1_CTRL_BMON0_BASE,
	[GAUDI_BMON_MME1_CTRL_1]	= mmMME1_CTRL_BMON1_BASE,
	[GAUDI_BMON_MME2_ACC_0]		= mmMME2_ACC_BMON0_BASE,
	[GAUDI_BMON_MME2_SBAB_0]	= mmMME2_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME2_SBAB_1]	= mmMME2_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME2_CTRL_0]	= mmMME2_CTRL_BMON0_BASE,
	[GAUDI_BMON_MME2_CTRL_1]	= mmMME2_CTRL_BMON1_BASE,
	[GAUDI_BMON_MME3_ACC_0]		= mmMME3_ACC_BMON0_BASE,
	[GAUDI_BMON_MME3_SBAB_0]	= mmMME3_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME3_SBAB_1]	= mmMME3_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME3_CTRL_0]	= mmMME3_CTRL_BMON0_BASE,
	[GAUDI_BMON_MME3_CTRL_1]	= mmMME3_CTRL_BMON1_BASE,
	[GAUDI_BMON_DMA_IF_W_S_SOB_WR]	= mmDMA_IF_W_S_SOB_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_0_WR]	= mmDMA_IF_W_S_HBM0_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_0_RD]	= mmDMA_IF_W_S_HBM0_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_1_WR]	= mmDMA_IF_W_S_HBM1_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_1_RD]	= mmDMA_IF_W_S_HBM1_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_SOB_WR]	= mmDMA_IF_E_S_SOB_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_0_WR]	= mmDMA_IF_E_S_HBM0_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_0_RD]	= mmDMA_IF_E_S_HBM0_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_1_WR]	= mmDMA_IF_E_S_HBM1_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_1_RD]	= mmDMA_IF_E_S_HBM1_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_SOB_WR]	= mmDMA_IF_W_N_SOB_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM0_WR]	= mmDMA_IF_W_N_HBM0_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM0_RD]	= mmDMA_IF_W_N_HBM0_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM1_WR]	= mmDMA_IF_W_N_HBM1_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM1_RD]	= mmDMA_IF_W_N_HBM1_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_SOB_WR]	= mmDMA_IF_E_N_SOB_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM0_WR]	= mmDMA_IF_E_N_HBM0_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM0_RD]	= mmDMA_IF_E_N_HBM0_RD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM1_WR]	= mmDMA_IF_E_N_HBM1_WR_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM1_RD]	= mmDMA_IF_E_N_HBM1_RD_BMON_BASE,
	[GAUDI_BMON_CPU_WR]		= mmCPU_WR_BMON_BASE,
	[GAUDI_BMON_CPU_RD]		= mmCPU_RD_BMON_BASE,
	[GAUDI_BMON_DMA_CH_0_0]		= mmDMA_CH_0_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_0_1]		= mmDMA_CH_0_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_1_0]		= mmDMA_CH_1_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_1_1]		= mmDMA_CH_1_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_2_0]		= mmDMA_CH_2_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_2_1]		= mmDMA_CH_2_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_3_0]		= mmDMA_CH_3_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_3_1]		= mmDMA_CH_3_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_4_0]		= mmDMA_CH_4_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_4_1]		= mmDMA_CH_4_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_5_0]		= mmDMA_CH_5_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_5_1]		= mmDMA_CH_5_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_6_0]		= mmDMA_CH_6_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_6_1]		= mmDMA_CH_6_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_7_0]		= mmDMA_CH_7_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_7_1]		= mmDMA_CH_7_BMON_1_BASE,
	[GAUDI_BMON_PCIE_MSTR_WR]	= mmPCIE_BMON_MSTR_WR_BASE,
	[GAUDI_BMON_PCIE_MSTR_RD]	= mmPCIE_BMON_MSTR_RD_BASE,
	[GAUDI_BMON_PCIE_SLV_WR]	= mmPCIE_BMON_SLV_WR_BASE,
	[GAUDI_BMON_PCIE_SLV_RD]	= mmPCIE_BMON_SLV_RD_BASE,
	[GAUDI_BMON_MMU_0]		= mmMMU_BMON_0_BASE,
	[GAUDI_BMON_MMU_1]		= mmMMU_BMON_1_BASE,
	[GAUDI_BMON_NIC0_0]		= mmBMON0_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_1]		= mmBMON1_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_2]		= mmBMON2_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_3]		= mmBMON3_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_4]		= mmBMON4_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC1_0]		= mmBMON0_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_1]		= mmBMON1_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_2]		= mmBMON2_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_3]		= mmBMON3_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_4]		= mmBMON4_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC2_0]		= mmBMON0_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_1]		= mmBMON1_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_2]		= mmBMON2_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_3]		= mmBMON3_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_4]		= mmBMON4_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC3_0]		= mmBMON0_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_1]		= mmBMON1_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_2]		= mmBMON2_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_3]		= mmBMON3_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_4]		= mmBMON4_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC4_0]		= mmBMON0_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_1]		= mmBMON1_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_2]		= mmBMON2_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_3]		= mmBMON3_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_4]		= mmBMON4_NIC4_DBG_BASE,
	[GAUDI_BMON_TPC0_EML_0]		= mmTPC0_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC0_EML_1]		= mmTPC0_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC0_EML_2]		= mmTPC0_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC0_EML_3]		= mmTPC0_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC1_EML_0]		= mmTPC1_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC1_EML_1]		= mmTPC1_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC1_EML_2]		= mmTPC1_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC1_EML_3]		= mmTPC1_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC2_EML_0]		= mmTPC2_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC2_EML_1]		= mmTPC2_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC2_EML_2]		= mmTPC2_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC2_EML_3]		= mmTPC2_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC3_EML_0]		= mmTPC3_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC3_EML_1]		= mmTPC3_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC3_EML_2]		= mmTPC3_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC3_EML_3]		= mmTPC3_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC4_EML_0]		= mmTPC4_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC4_EML_1]		= mmTPC4_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC4_EML_2]		= mmTPC4_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC4_EML_3]		= mmTPC4_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC5_EML_0]		= mmTPC5_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC5_EML_1]		= mmTPC5_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC5_EML_2]		= mmTPC5_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC5_EML_3]		= mmTPC5_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC6_EML_0]		= mmTPC6_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC6_EML_1]		= mmTPC6_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC6_EML_2]		= mmTPC6_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC6_EML_3]		= mmTPC6_EML_BUSMON_3_BASE,
	[GAUDI_BMON_TPC7_EML_0]		= mmTPC7_EML_BUSMON_0_BASE,
	[GAUDI_BMON_TPC7_EML_1]		= mmTPC7_EML_BUSMON_1_BASE,
	[GAUDI_BMON_TPC7_EML_2]		= mmTPC7_EML_BUSMON_2_BASE,
	[GAUDI_BMON_TPC7_EML_3]		= mmTPC7_EML_BUSMON_3_BASE
पूर्ण;

अटल u64 debug_spmu_regs[GAUDI_SPMU_LAST + 1] = अणु
	[GAUDI_SPMU_MME0_ACC]		= mmMME0_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME0_SBAB]		= mmMME0_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME0_CTRL]		= mmMME0_CTRL_SPMU_BASE,
	[GAUDI_SPMU_MME1_ACC]		= mmMME1_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME1_SBAB]		= mmMME1_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME1_CTRL]		= mmMME1_CTRL_SPMU_BASE,
	[GAUDI_SPMU_MME2_MME2_ACC]	= mmMME2_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME2_SBAB]		= mmMME2_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME2_CTRL]		= mmMME2_CTRL_SPMU_BASE,
	[GAUDI_SPMU_MME3_ACC]		= mmMME3_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME3_SBAB]		= mmMME3_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME3_CTRL]		= mmMME3_CTRL_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_0_CS]	= mmDMA_CH_0_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_1_CS]	= mmDMA_CH_1_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_2_CS]	= mmDMA_CH_2_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_3_CS]	= mmDMA_CH_3_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_4_CS]	= mmDMA_CH_4_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_5_CS]	= mmDMA_CH_5_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_6_CS]	= mmDMA_CH_6_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_7_CS]	= mmDMA_CH_7_CS_SPMU_BASE,
	[GAUDI_SPMU_PCIE]		= mmPCIE_SPMU_BASE,
	[GAUDI_SPMU_MMU_CS]		= mmMMU_CS_SPMU_BASE,
	[GAUDI_SPMU_NIC0_0]		= mmSPMU_0_NIC0_DBG_BASE,
	[GAUDI_SPMU_NIC0_1]		= mmSPMU_1_NIC0_DBG_BASE,
	[GAUDI_SPMU_NIC1_0]		= mmSPMU_0_NIC1_DBG_BASE,
	[GAUDI_SPMU_NIC1_1]		= mmSPMU_1_NIC1_DBG_BASE,
	[GAUDI_SPMU_NIC2_0]		= mmSPMU_0_NIC2_DBG_BASE,
	[GAUDI_SPMU_NIC2_1]		= mmSPMU_1_NIC2_DBG_BASE,
	[GAUDI_SPMU_NIC3_0]		= mmSPMU_0_NIC3_DBG_BASE,
	[GAUDI_SPMU_NIC3_1]		= mmSPMU_1_NIC3_DBG_BASE,
	[GAUDI_SPMU_NIC4_0]		= mmSPMU_0_NIC4_DBG_BASE,
	[GAUDI_SPMU_NIC4_1]		= mmSPMU_1_NIC4_DBG_BASE,
	[GAUDI_SPMU_TPC0_EML]		= mmTPC0_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC1_EML]		= mmTPC1_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC2_EML]		= mmTPC2_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC3_EML]		= mmTPC3_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC4_EML]		= mmTPC4_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC5_EML]		= mmTPC5_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC6_EML]		= mmTPC6_EML_SPMU_BASE,
	[GAUDI_SPMU_TPC7_EML]		= mmTPC7_EML_SPMU_BASE
पूर्ण;

अटल पूर्णांक gaudi_coresight_समयout(काष्ठा hl_device *hdev, u64 addr,
		पूर्णांक position, bool up)
अणु
	पूर्णांक rc;
	u32 val;

	rc = hl_poll_समयout(
		hdev,
		addr,
		val,
		up ? val & BIT(position) : !(val & BIT(position)),
		1000,
		CORESIGHT_TIMEOUT_USEC);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout while waiting for coresight, addr: 0x%llx, position: %d, up: %d\n",
				addr, position, up);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_config_sपंचांग(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_sपंचांग *input;
	u64 base_reg;
	u32 frequency;
	पूर्णांक rc;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_sपंचांग_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in STM\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_sपंचांग_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		WREG32(base_reg + 0xE80, 0x80004);
		WREG32(base_reg + 0xD64, 7);
		WREG32(base_reg + 0xD60, 0);
		WREG32(base_reg + 0xD00, lower_32_bits(input->he_mask));
		WREG32(base_reg + 0xD60, 1);
		WREG32(base_reg + 0xD00, upper_32_bits(input->he_mask));
		WREG32(base_reg + 0xE70, 0x10);
		WREG32(base_reg + 0xE60, 0);
		WREG32(base_reg + 0xE00, lower_32_bits(input->sp_mask));
		WREG32(base_reg + 0xEF4, input->id);
		WREG32(base_reg + 0xDF4, 0x80);
		frequency = hdev->asic_prop.psoc_बारtamp_frequency;
		अगर (frequency == 0)
			frequency = input->frequency;
		WREG32(base_reg + 0xE8C, frequency);
		WREG32(base_reg + 0xE90, 0x7FF);

		/* SW-2176 - SW WA क्रम HW bug */
		अगर ((CFG_BASE + base_reg) >= mmDMA_CH_0_CS_STM_BASE &&
			(CFG_BASE + base_reg) <= mmDMA_CH_7_CS_STM_BASE) अणु

			WREG32(base_reg + 0xE68, 0xffff8005);
			WREG32(base_reg + 0xE6C, 0x0);
		पूर्ण

		WREG32(base_reg + 0xE80, 0x27 | (input->id << 16));
	पूर्ण अन्यथा अणु
		WREG32(base_reg + 0xE80, 4);
		WREG32(base_reg + 0xD64, 0);
		WREG32(base_reg + 0xD60, 1);
		WREG32(base_reg + 0xD00, 0);
		WREG32(base_reg + 0xD20, 0);
		WREG32(base_reg + 0xD60, 0);
		WREG32(base_reg + 0xE20, 0);
		WREG32(base_reg + 0xE00, 0);
		WREG32(base_reg + 0xDF4, 0x80);
		WREG32(base_reg + 0xE70, 0);
		WREG32(base_reg + 0xE60, 0);
		WREG32(base_reg + 0xE64, 0);
		WREG32(base_reg + 0xE8C, 0);

		rc = gaudi_coresight_समयout(hdev, base_reg + 0xE80, 23, false);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to disable STM on timeout, error %d\n",
				rc);
			वापस rc;
		पूर्ण

		WREG32(base_reg + 0xE80, 4);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_config_etf(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_etf *input;
	u64 base_reg;
	u32 val;
	पूर्णांक rc;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_etf_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in ETF\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_etf_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	val = RREG32(base_reg + 0x304);
	val |= 0x1000;
	WREG32(base_reg + 0x304, val);
	val |= 0x40;
	WREG32(base_reg + 0x304, val);

	rc = gaudi_coresight_समयout(hdev, base_reg + 0x304, 6, false);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to %s ETF on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	rc = gaudi_coresight_समयout(hdev, base_reg + 0xC, 2, true);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to %s ETF on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	WREG32(base_reg + 0x20, 0);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		WREG32(base_reg + 0x34, 0x3FFC);
		WREG32(base_reg + 0x28, input->sink_mode);
		WREG32(base_reg + 0x304, 0x4001);
		WREG32(base_reg + 0x308, 0xA);
		WREG32(base_reg + 0x20, 1);
	पूर्ण अन्यथा अणु
		WREG32(base_reg + 0x34, 0);
		WREG32(base_reg + 0x28, 0);
		WREG32(base_reg + 0x304, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool gaudi_etr_validate_address(काष्ठा hl_device *hdev, u64 addr,
					u64 size, bool *is_host)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	/* maximum address length is 50 bits */
	अगर (addr >> 50) अणु
		dev_err(hdev->dev,
			"ETR buffer address shouldn't exceed 50 bits\n");
		वापस false;
	पूर्ण

	अगर (addr > (addr + size)) अणु
		dev_err(hdev->dev,
			"ETR buffer size %llu overflow\n", size);
		वापस false;
	पूर्ण

	/* PMMU and HPMMU addresses are equal, check only one of them */
	अगर ((gaudi->hw_cap_initialized & HW_CAP_MMU) &&
		hl_mem_area_inside_range(addr, size,
				prop->pmmu.start_addr,
				prop->pmmu.end_addr)) अणु
		*is_host = true;
		वापस true;
	पूर्ण

	अगर (hl_mem_area_inside_range(addr, size,
			prop->dram_user_base_address,
			prop->dram_end_address))
		वापस true;

	अगर (hl_mem_area_inside_range(addr, size,
			prop->sram_user_base_address,
			prop->sram_end_address))
		वापस true;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU))
		dev_err(hdev->dev, "ETR buffer should be in SRAM/DRAM\n");

	वापस false;
पूर्ण

अटल पूर्णांक gaudi_config_etr(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_etr *input;
	u64 msb;
	u32 val;
	पूर्णांक rc;

	WREG32(mmPSOC_ETR_LAR, CORESIGHT_UNLOCK);

	val = RREG32(mmPSOC_ETR_FFCR);
	val |= 0x1000;
	WREG32(mmPSOC_ETR_FFCR, val);
	val |= 0x40;
	WREG32(mmPSOC_ETR_FFCR, val);

	rc = gaudi_coresight_समयout(hdev, mmPSOC_ETR_FFCR, 6, false);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to %s ETR on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	rc = gaudi_coresight_समयout(hdev, mmPSOC_ETR_STS, 2, true);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to %s ETR on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	WREG32(mmPSOC_ETR_CTL, 0);

	अगर (params->enable) अणु
		bool is_host = false;

		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		अगर (input->buffer_size == 0) अणु
			dev_err(hdev->dev,
				"ETR buffer size should be bigger than 0\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!gaudi_etr_validate_address(hdev,
				input->buffer_address, input->buffer_size,
				&is_host)) अणु
			dev_err(hdev->dev, "ETR buffer address is invalid\n");
			वापस -EINVAL;
		पूर्ण

		gaudi_mmu_prepare_reg(hdev, mmPSOC_GLOBAL_CONF_TRACE_ARUSER,
						hdev->compute_ctx->asid);
		gaudi_mmu_prepare_reg(hdev, mmPSOC_GLOBAL_CONF_TRACE_AWUSER,
						hdev->compute_ctx->asid);

		msb = upper_32_bits(input->buffer_address) >> 8;
		msb &= PSOC_GLOBAL_CONF_TRACE_ADDR_MSB_MASK;
		WREG32(mmPSOC_GLOBAL_CONF_TRACE_ADDR, msb);

		WREG32(mmPSOC_ETR_BUFWM, 0x3FFC);
		WREG32(mmPSOC_ETR_RSZ, input->buffer_size);
		WREG32(mmPSOC_ETR_MODE, input->sink_mode);
		अगर (hdev->asic_prop.fw_security_disabled) अणु
			/* make ETR not privileged */
			val = FIELD_PREP(
					PSOC_ETR_AXICTL_PROTCTRLBIT0_MASK, 0);
			/* make ETR non-secured (inverted logic) */
			val |= FIELD_PREP(
					PSOC_ETR_AXICTL_PROTCTRLBIT1_MASK, 1);
			/*
			 * Workaround क्रम H3 #HW-2075 bug: use small data
			 * chunks
			 */
			val |= FIELD_PREP(PSOC_ETR_AXICTL_WRBURSTLEN_MASK,
							is_host ? 0 : 7);
			WREG32(mmPSOC_ETR_AXICTL, val);
		पूर्ण
		WREG32(mmPSOC_ETR_DBALO,
				lower_32_bits(input->buffer_address));
		WREG32(mmPSOC_ETR_DBAHI,
				upper_32_bits(input->buffer_address));
		WREG32(mmPSOC_ETR_FFCR, 3);
		WREG32(mmPSOC_ETR_PSCR, 0xA);
		WREG32(mmPSOC_ETR_CTL, 1);
	पूर्ण अन्यथा अणु
		WREG32(mmPSOC_ETR_BUFWM, 0);
		WREG32(mmPSOC_ETR_RSZ, 0x400);
		WREG32(mmPSOC_ETR_DBALO, 0);
		WREG32(mmPSOC_ETR_DBAHI, 0);
		WREG32(mmPSOC_ETR_PSCR, 0);
		WREG32(mmPSOC_ETR_MODE, 0);
		WREG32(mmPSOC_ETR_FFCR, 0);

		अगर (params->output_size >= माप(u64)) अणु
			u32 rwp, rwphi;

			/*
			 * The trace buffer address is 50 bits wide. The end of
			 * the buffer is set in the RWP रेजिस्टर (lower 32
			 * bits), and in the RWPHI रेजिस्टर (upper 8 bits).
			 * The 10 msb of the 50-bit address are stored in a
			 * global configuration रेजिस्टर.
			 */
			rwp = RREG32(mmPSOC_ETR_RWP);
			rwphi = RREG32(mmPSOC_ETR_RWPHI) & 0xff;
			msb = RREG32(mmPSOC_GLOBAL_CONF_TRACE_ADDR) &
					PSOC_GLOBAL_CONF_TRACE_ADDR_MSB_MASK;
			*(u64 *) params->output = ((u64) msb << 40) |
						((u64) rwphi << 32) | rwp;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_config_funnel(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	u64 base_reg;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_funnel_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in FUNNEL\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_funnel_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	WREG32(base_reg, params->enable ? 0x33F : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_config_bmon(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_bmon *input;
	u64 base_reg;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_bmon_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in BMON\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_bmon_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0x104, 1);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		WREG32(base_reg + 0x200, lower_32_bits(input->start_addr0));
		WREG32(base_reg + 0x204, upper_32_bits(input->start_addr0));
		WREG32(base_reg + 0x208, lower_32_bits(input->addr_mask0));
		WREG32(base_reg + 0x20C, upper_32_bits(input->addr_mask0));
		WREG32(base_reg + 0x240, lower_32_bits(input->start_addr1));
		WREG32(base_reg + 0x244, upper_32_bits(input->start_addr1));
		WREG32(base_reg + 0x248, lower_32_bits(input->addr_mask1));
		WREG32(base_reg + 0x24C, upper_32_bits(input->addr_mask1));
		WREG32(base_reg + 0x224, 0);
		WREG32(base_reg + 0x234, 0);
		WREG32(base_reg + 0x30C, input->bw_win);
		WREG32(base_reg + 0x308, input->win_capture);
		WREG32(base_reg + 0x700, 0xA000B00 | (input->id << 12));
		WREG32(base_reg + 0x708, 0xA000A00 | (input->id << 12));
		WREG32(base_reg + 0x70C, 0xA000C00 | (input->id << 12));
		WREG32(base_reg + 0x100, 0x11);
		WREG32(base_reg + 0x304, 0x1);
	पूर्ण अन्यथा अणु
		WREG32(base_reg + 0x200, 0);
		WREG32(base_reg + 0x204, 0);
		WREG32(base_reg + 0x208, 0xFFFFFFFF);
		WREG32(base_reg + 0x20C, 0xFFFFFFFF);
		WREG32(base_reg + 0x240, 0);
		WREG32(base_reg + 0x244, 0);
		WREG32(base_reg + 0x248, 0xFFFFFFFF);
		WREG32(base_reg + 0x24C, 0xFFFFFFFF);
		WREG32(base_reg + 0x224, 0xFFFFFFFF);
		WREG32(base_reg + 0x234, 0x1070F);
		WREG32(base_reg + 0x30C, 0);
		WREG32(base_reg + 0x308, 0xFFFF);
		WREG32(base_reg + 0x700, 0xA000B00);
		WREG32(base_reg + 0x708, 0xA000A00);
		WREG32(base_reg + 0x70C, 0xA000C00);
		WREG32(base_reg + 0x100, 1);
		WREG32(base_reg + 0x304, 0);
		WREG32(base_reg + 0x104, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_config_spmu(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	u64 base_reg;
	काष्ठा hl_debug_params_spmu *input = params->input;
	u64 *output;
	u32 output_arr_len;
	u32 events_num;
	u32 overflow_idx;
	u32 cycle_cnt_idx;
	पूर्णांक i;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_spmu_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in SPMU\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_spmu_regs[params->reg_idx] - CFG_BASE;

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		अगर (input->event_types_num < 3) अणु
			dev_err(hdev->dev,
				"not enough event types values for SPMU enable\n");
			वापस -EINVAL;
		पूर्ण

		अगर (input->event_types_num > SPMU_MAX_COUNTERS) अणु
			dev_err(hdev->dev,
				"too many event types values for SPMU enable\n");
			वापस -EINVAL;
		पूर्ण

		WREG32(base_reg + 0xE04, 0x41013046);
		WREG32(base_reg + 0xE04, 0x41013040);

		क्रम (i = 0 ; i < input->event_types_num ; i++)
			WREG32(base_reg + SPMU_EVENT_TYPES_OFFSET + i * 4,
				input->event_types[i]);

		WREG32(base_reg + 0xE04, 0x41013041);
		WREG32(base_reg + 0xC00, 0x8000003F);
	पूर्ण अन्यथा अणु
		output = params->output;
		output_arr_len = params->output_size / 8;
		events_num = output_arr_len - 2;
		overflow_idx = output_arr_len - 2;
		cycle_cnt_idx = output_arr_len - 1;

		अगर (!output)
			वापस -EINVAL;

		अगर (output_arr_len < 3) अणु
			dev_err(hdev->dev,
				"not enough values for SPMU disable\n");
			वापस -EINVAL;
		पूर्ण

		अगर (events_num > SPMU_MAX_COUNTERS) अणु
			dev_err(hdev->dev,
				"too many events values for SPMU disable\n");
			वापस -EINVAL;
		पूर्ण

		WREG32(base_reg + 0xE04, 0x41013040);

		क्रम (i = 0 ; i < events_num ; i++)
			output[i] = RREG32(base_reg + i * 8);

		output[overflow_idx] = RREG32(base_reg + 0xCC0);

		output[cycle_cnt_idx] = RREG32(base_reg + 0xFC);
		output[cycle_cnt_idx] <<= 32;
		output[cycle_cnt_idx] |= RREG32(base_reg + 0xF8);

		WREG32(base_reg + 0xCC0, 0);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gaudi_debug_coresight(काष्ठा hl_device *hdev, व्योम *data)
अणु
	काष्ठा hl_debug_params *params = data;
	पूर्णांक rc = 0;

	चयन (params->op) अणु
	हाल HL_DEBUG_OP_STM:
		rc = gaudi_config_sपंचांग(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_ETF:
		rc = gaudi_config_etf(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_ETR:
		rc = gaudi_config_etr(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_FUNNEL:
		rc = gaudi_config_funnel(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_BMON:
		rc = gaudi_config_bmon(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_SPMU:
		rc = gaudi_config_spmu(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_TIMESTAMP:
		/* Do nothing as this opcode is deprecated */
		अवरोध;

	शेष:
		dev_err(hdev->dev, "Unknown coresight id %d\n", params->op);
		वापस -EINVAL;
	पूर्ण

	/* Perक्रमm पढ़ो from the device to flush all configuration */
	RREG32(mmHW_STATE);

	वापस rc;
पूर्ण

व्योम gaudi_halt_coresight(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_debug_params params = अणुपूर्ण;
	पूर्णांक i, rc;

	क्रम (i = GAUDI_ETF_FIRST ; i <= GAUDI_ETF_LAST ; i++) अणु
		params.reg_idx = i;
		rc = gaudi_config_etf(hdev, &params);
		अगर (rc)
			dev_err(hdev->dev, "halt ETF failed, %d/%d\n", rc, i);
	पूर्ण

	rc = gaudi_config_etr(hdev, &params);
	अगर (rc)
		dev_err(hdev->dev, "halt ETR failed, %d\n", rc);
पूर्ण
