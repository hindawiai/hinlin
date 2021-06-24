<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित ASIC_REG_GOYA_REGS_H_
#घोषणा ASIC_REG_GOYA_REGS_H_

#समावेश "goya_blocks.h"
#समावेश "stlb_regs.h"
#समावेश "mmu_regs.h"
#समावेश "pcie_aux_regs.h"
#समावेश "pcie_wrap_regs.h"
#समावेश "psoc_global_conf_regs.h"
#समावेश "psoc_spi_regs.h"
#समावेश "psoc_mme_pll_regs.h"
#समावेश "psoc_pci_pll_regs.h"
#समावेश "psoc_emmc_pll_regs.h"
#समावेश "psoc_timestamp_regs.h"
#समावेश "cpu_if_regs.h"
#समावेश "cpu_ca53_cfg_regs.h"
#समावेश "cpu_pll_regs.h"
#समावेश "ic_pll_regs.h"
#समावेश "mc_pll_regs.h"
#समावेश "tpc_pll_regs.h"
#समावेश "dma_qm_0_regs.h"
#समावेश "dma_qm_1_regs.h"
#समावेश "dma_qm_2_regs.h"
#समावेश "dma_qm_3_regs.h"
#समावेश "dma_qm_4_regs.h"
#समावेश "dma_ch_0_regs.h"
#समावेश "dma_ch_1_regs.h"
#समावेश "dma_ch_2_regs.h"
#समावेश "dma_ch_3_regs.h"
#समावेश "dma_ch_4_regs.h"
#समावेश "dma_macro_regs.h"
#समावेश "dma_nrtr_regs.h"
#समावेश "pci_nrtr_regs.h"
#समावेश "sram_y0_x0_rtr_regs.h"
#समावेश "sram_y0_x1_rtr_regs.h"
#समावेश "sram_y0_x2_rtr_regs.h"
#समावेश "sram_y0_x3_rtr_regs.h"
#समावेश "sram_y0_x4_rtr_regs.h"
#समावेश "mme_regs.h"
#समावेश "mme_qm_regs.h"
#समावेश "mme_cmdq_regs.h"
#समावेश "mme1_rtr_regs.h"
#समावेश "mme2_rtr_regs.h"
#समावेश "mme3_rtr_regs.h"
#समावेश "mme4_rtr_regs.h"
#समावेश "mme5_rtr_regs.h"
#समावेश "mme6_rtr_regs.h"
#समावेश "tpc0_cfg_regs.h"
#समावेश "tpc1_cfg_regs.h"
#समावेश "tpc2_cfg_regs.h"
#समावेश "tpc3_cfg_regs.h"
#समावेश "tpc4_cfg_regs.h"
#समावेश "tpc5_cfg_regs.h"
#समावेश "tpc6_cfg_regs.h"
#समावेश "tpc7_cfg_regs.h"
#समावेश "tpc0_qm_regs.h"
#समावेश "tpc1_qm_regs.h"
#समावेश "tpc2_qm_regs.h"
#समावेश "tpc3_qm_regs.h"
#समावेश "tpc4_qm_regs.h"
#समावेश "tpc5_qm_regs.h"
#समावेश "tpc6_qm_regs.h"
#समावेश "tpc7_qm_regs.h"
#समावेश "tpc0_cmdq_regs.h"
#समावेश "tpc1_cmdq_regs.h"
#समावेश "tpc2_cmdq_regs.h"
#समावेश "tpc3_cmdq_regs.h"
#समावेश "tpc4_cmdq_regs.h"
#समावेश "tpc5_cmdq_regs.h"
#समावेश "tpc6_cmdq_regs.h"
#समावेश "tpc7_cmdq_regs.h"
#समावेश "tpc0_nrtr_regs.h"
#समावेश "tpc1_rtr_regs.h"
#समावेश "tpc2_rtr_regs.h"
#समावेश "tpc3_rtr_regs.h"
#समावेश "tpc4_rtr_regs.h"
#समावेश "tpc5_rtr_regs.h"
#समावेश "tpc6_rtr_regs.h"
#समावेश "tpc7_nrtr_regs.h"
#समावेश "tpc0_eml_cfg_regs.h"
#समावेश "psoc_etr_regs.h"

#समावेश "psoc_global_conf_masks.h"
#समावेश "dma_macro_masks.h"
#समावेश "dma_qm_0_masks.h"
#समावेश "dma_ch_0_masks.h"
#समावेश "tpc0_qm_masks.h"
#समावेश "tpc0_cmdq_masks.h"
#समावेश "mme_qm_masks.h"
#समावेश "mme_cmdq_masks.h"
#समावेश "tpc0_cfg_masks.h"
#समावेश "tpc0_eml_cfg_masks.h"
#समावेश "mme1_rtr_masks.h"
#समावेश "tpc0_nrtr_masks.h"
#समावेश "dma_nrtr_masks.h"
#समावेश "pci_nrtr_masks.h"
#समावेश "stlb_masks.h"
#समावेश "cpu_ca53_cfg_masks.h"
#समावेश "mmu_masks.h"
#समावेश "mme_masks.h"

#घोषणा mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG                           0xC02000
#घोषणा mmPCIE_DBI_MSIX_DOORBELL_OFF                                 0xC02948

#घोषणा mmSYNC_MNGR_MON_PAY_ADDRL_0                                  0x113000
#घोषणा mmSYNC_MNGR_SOB_OBJ_0                                        0x112000
#घोषणा mmSYNC_MNGR_SOB_OBJ_1000                                     0x112FA0
#घोषणा mmSYNC_MNGR_SOB_OBJ_1007                                     0x112FBC
#घोषणा mmSYNC_MNGR_SOB_OBJ_1023                                     0x112FFC
#घोषणा mmSYNC_MNGR_MON_STATUS_0                                     0x114000
#घोषणा mmSYNC_MNGR_MON_STATUS_255                                   0x1143FC

#घोषणा mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR                         0x800040

#पूर्ण_अगर /* ASIC_REG_GOYA_REGS_H_ */
