<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IRQ_LOCAL_H_INCLUDED__
#घोषणा __IRQ_LOCAL_H_INCLUDED__

#समावेश "irq_global.h"

#समावेश <irq_controller_defs.h>

/* IRQ0_ID */
#समावेश "hive_isp_css_defs.h"
#घोषणा HIVE_GP_DEV_IRQ_NUM_IRQS	32
/* IRQ1_ID */
#समावेश "input_formatter_subsystem_defs.h"
#घोषणा HIVE_IFMT_IRQ_NUM_IRQS		5
/* IRQ2_ID */
#समावेश "input_system_defs.h"
/* IRQ3_ID */
#समावेश "input_selector_defs.h"

#घोषणा	IRQ_ID_OFFSET	32
#घोषणा	IRQ0_ID_OFFSET	0
#घोषणा	IRQ1_ID_OFFSET	IRQ_ID_OFFSET
#घोषणा	IRQ2_ID_OFFSET	(2 * IRQ_ID_OFFSET)
#घोषणा	IRQ3_ID_OFFSET	(3 * IRQ_ID_OFFSET)
#घोषणा	IRQ_END_OFFSET	(4 * IRQ_ID_OFFSET)

#घोषणा	IRQ0_ID_N_CHANNEL	HIVE_GP_DEV_IRQ_NUM_IRQS
#घोषणा	IRQ1_ID_N_CHANNEL	HIVE_IFMT_IRQ_NUM_IRQS
#घोषणा	IRQ2_ID_N_CHANNEL	HIVE_ISYS_IRQ_NUM_BITS
#घोषणा	IRQ3_ID_N_CHANNEL	HIVE_ISEL_IRQ_NUM_IRQS

क्रमागत virq_id अणु
	virq_gpio_pin_0            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_0_BIT_ID,
	virq_gpio_pin_1            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_1_BIT_ID,
	virq_gpio_pin_2            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_2_BIT_ID,
	virq_gpio_pin_3            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_3_BIT_ID,
	virq_gpio_pin_4            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_4_BIT_ID,
	virq_gpio_pin_5            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_5_BIT_ID,
	virq_gpio_pin_6            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_6_BIT_ID,
	virq_gpio_pin_7            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_7_BIT_ID,
	virq_gpio_pin_8            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_8_BIT_ID,
	virq_gpio_pin_9            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_9_BIT_ID,
	virq_gpio_pin_10           = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_10_BIT_ID,
	virq_gpio_pin_11           = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GPIO_PIN_11_BIT_ID,
	virq_sp                    = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SP_BIT_ID,
	virq_isp                   = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISP_BIT_ID,
	virq_isys                  = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISYS_BIT_ID,
	virq_isel                  = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISEL_BIT_ID,
	virq_अगरmt                  = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_IFMT_BIT_ID,
	virq_sp_stream_mon         = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SP_STREAM_MON_BIT_ID,
	virq_isp_stream_mon        = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISP_STREAM_MON_BIT_ID,
	virq_mod_stream_mon        = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_MOD_STREAM_MON_BIT_ID,
	virq_isp_pmem_error        = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISP_PMEM_ERROR_BIT_ID,
	virq_isp_bamem_error       = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISP_BAMEM_ERROR_BIT_ID,
	virq_isp_dmem_error        = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_ISP_DMEM_ERROR_BIT_ID,
	virq_sp_icache_mem_error   = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SP_ICACHE_MEM_ERROR_BIT_ID,
	virq_sp_dmem_error         = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SP_DMEM_ERROR_BIT_ID,
	virq_mmu_cache_mem_error   = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_MMU_CACHE_MEM_ERROR_BIT_ID,
	virq_gp_समयr_0            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GP_TIMER_0_BIT_ID,
	virq_gp_समयr_1            = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_GP_TIMER_1_BIT_ID,
	virq_sw_pin_0              = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SW_PIN_0_BIT_ID,
	virq_sw_pin_1              = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SW_PIN_1_BIT_ID,
	virq_dma                   = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_DMA_BIT_ID,
	virq_sp_stream_mon_b       = IRQ0_ID_OFFSET + HIVE_GP_DEV_IRQ_SP_STREAM_MON_B_BIT_ID,

	virq_अगरmt0_id              = IRQ1_ID_OFFSET + HIVE_IFMT_IRQ_IFT_PRIM_BIT_ID,
	virq_अगरmt1_id              = IRQ1_ID_OFFSET + HIVE_IFMT_IRQ_IFT_PRIM_B_BIT_ID,
	virq_अगरmt2_id              = IRQ1_ID_OFFSET + HIVE_IFMT_IRQ_IFT_SEC_BIT_ID,
	virq_अगरmt3_id              = IRQ1_ID_OFFSET + HIVE_IFMT_IRQ_MEM_CPY_BIT_ID,
	virq_अगरmt_sideband_changed = IRQ1_ID_OFFSET + HIVE_IFMT_IRQ_SIDEBAND_CHANGED_BIT_ID,

	virq_isys_sof              = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CSI_SOF_BIT_ID,
	virq_isys_eof              = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CSI_खातापूर्ण_BIT_ID,
	virq_isys_sol              = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CSI_SOL_BIT_ID,
	virq_isys_eol              = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CSI_EOL_BIT_ID,
	virq_isys_csi              = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CSI_RECEIVER_BIT_ID,
	virq_isys_csi_be           = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CSI_RECEIVER_BE_BIT_ID,
	virq_isys_capt0_id_no_sop  = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CAP_UNIT_A_NO_SOP,
	virq_isys_capt0_id_late_sop = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CAP_UNIT_A_LATE_SOP,
	virq_isys_capt1_id_no_sop  = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CAP_UNIT_B_NO_SOP,
	virq_isys_capt1_id_late_sop = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CAP_UNIT_B_LATE_SOP,
	virq_isys_capt2_id_no_sop  = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CAP_UNIT_C_NO_SOP,
	virq_isys_capt2_id_late_sop = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CAP_UNIT_C_LATE_SOP,
	virq_isys_acq_sop_mismatch = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_ACQ_UNIT_SOP_MISMATCH,
	virq_isys_ctrl_capt0       = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_INP_CTRL_CAPA,
	virq_isys_ctrl_capt1       = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_INP_CTRL_CAPB,
	virq_isys_ctrl_capt2       = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_INP_CTRL_CAPC,
	virq_isys_cio_to_ahb       = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_CIO2AHB,
	virq_isys_dma              = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_DMA_BIT_ID,
	virq_isys_fअगरo_monitor     = IRQ2_ID_OFFSET + HIVE_ISYS_IRQ_STREAM_MON_BIT_ID,

	virq_isel_sof              = IRQ3_ID_OFFSET + HIVE_ISEL_IRQ_SYNC_GEN_SOF_BIT_ID,
	virq_isel_eof              = IRQ3_ID_OFFSET + HIVE_ISEL_IRQ_SYNC_GEN_खातापूर्ण_BIT_ID,
	virq_isel_sol              = IRQ3_ID_OFFSET + HIVE_ISEL_IRQ_SYNC_GEN_SOL_BIT_ID,
	virq_isel_eol              = IRQ3_ID_OFFSET + HIVE_ISEL_IRQ_SYNC_GEN_EOL_BIT_ID,

	N_virq_id                  = IRQ_END_OFFSET
पूर्ण;

काष्ठा virq_info अणु
	hrt_data		irq_status_reg[N_IRQ_ID];
पूर्ण;

काष्ठा irq_controller_state अणु
	अचिन्हित पूर्णांक	irq_edge;
	अचिन्हित पूर्णांक	irq_mask;
	अचिन्हित पूर्णांक	irq_status;
	अचिन्हित पूर्णांक	irq_enable;
	अचिन्हित पूर्णांक	irq_level_not_pulse;
पूर्ण;

#पूर्ण_अगर /* __IRQ_LOCAL_H_INCLUDED__ */
