<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "gaudiP.h"
#समावेश "../include/hw_ip/mmu/mmu_general.h"
#समावेश "../include/hw_ip/mmu/mmu_v1_1.h"
#समावेश "../include/gaudi/gaudi_masks.h"
#समावेश "../include/gaudi/gaudi_fw_if.h"
#समावेश "../include/gaudi/gaudi_reg_map.h"
#समावेश "../include/gaudi/gaudi_async_ids_map_extended.h"

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/iommu.h>
#समावेश <linux/seq_file.h>

/*
 * Gaudi security scheme:
 *
 * 1. Host is रक्षित by:
 *        - Range रेजिस्टरs
 *        - MMU
 *
 * 2. DDR is रक्षित by:
 *        - Range रेजिस्टरs (protect the first 512MB)
 *
 * 3. Configuration is रक्षित by:
 *        - Range रेजिस्टरs
 *        - Protection bits
 *
 * MMU is always enabled.
 *
 * QMAN DMA channels 0,1 (PCI DMAN):
 *     - DMA is not secured.
 *     - PQ and CQ are secured.
 *     - CP is secured: The driver needs to parse CB but WREG should be allowed
 *                      because of TDMA (tensor DMA). Hence, WREG is always not
 *                      secured.
 *
 * When the driver needs to use DMA it will check that Gaudi is idle, set DMA
 * channel 0 to be secured, execute the DMA and change it back to not secured.
 * Currently, the driver करोesn't use the DMA जबतक there are compute jobs
 * running.
 *
 * The current use हालs क्रम the driver to use the DMA are:
 *     - Clear SRAM on context चयन (happens on context चयन when device is
 *       idle)
 *     - MMU page tables area clear (happens on init)
 *
 * QMAN DMA 2-7, TPC, MME, NIC:
 * PQ is secured and is located on the Host (HBM CON TPC3 bug)
 * CQ, CP and the engine are not secured
 *
 */

#घोषणा GAUDI_BOOT_FIT_खाता	"habanalabs/gaudi/gaudi-boot-fit.itb"
#घोषणा GAUDI_LINUX_FW_खाता	"habanalabs/gaudi/gaudi-fit.itb"
#घोषणा GAUDI_TPC_FW_खाता	"habanalabs/gaudi/gaudi_tpc.bin"

#घोषणा GAUDI_DMA_POOL_BLK_SIZE		0x100 /* 256 bytes */

#घोषणा GAUDI_RESET_TIMEOUT_MSEC	2000		/* 2000ms */
#घोषणा GAUDI_RESET_WAIT_MSEC		1		/* 1ms */
#घोषणा GAUDI_CPU_RESET_WAIT_MSEC	200		/* 200ms */
#घोषणा GAUDI_TEST_QUEUE_WAIT_USEC	100000		/* 100ms */

#घोषणा GAUDI_PLDM_RESET_WAIT_MSEC	1000		/* 1s */
#घोषणा GAUDI_PLDM_HRESET_TIMEOUT_MSEC	20000		/* 20s */
#घोषणा GAUDI_PLDM_TEST_QUEUE_WAIT_USEC	1000000		/* 1s */
#घोषणा GAUDI_PLDM_MMU_TIMEOUT_USEC	(MMU_CONFIG_TIMEOUT_USEC * 100)
#घोषणा GAUDI_PLDM_QMAN0_TIMEOUT_USEC	(HL_DEVICE_TIMEOUT_USEC * 30)
#घोषणा GAUDI_PLDM_TPC_KERNEL_WAIT_USEC	(HL_DEVICE_TIMEOUT_USEC * 30)
#घोषणा GAUDI_BOOT_FIT_REQ_TIMEOUT_USEC	1000000		/* 1s */
#घोषणा GAUDI_MSG_TO_CPU_TIMEOUT_USEC	4000000		/* 4s */

#घोषणा GAUDI_QMAN0_FENCE_VAL		0x72E91AB9

#घोषणा GAUDI_MAX_STRING_LEN		20

#घोषणा GAUDI_CB_POOL_CB_CNT		512
#घोषणा GAUDI_CB_POOL_CB_SIZE		0x20000 /* 128KB */

#घोषणा GAUDI_ALLOC_CPU_MEM_RETRY_CNT	3

#घोषणा GAUDI_NUM_OF_TPC_INTR_CAUSE	20

#घोषणा GAUDI_NUM_OF_QM_ERR_CAUSE	16

#घोषणा GAUDI_NUM_OF_QM_ARB_ERR_CAUSE	3

#घोषणा GAUDI_ARB_WDT_TIMEOUT		0x1000000

#घोषणा GAUDI_CLK_GATE_DEBUGFS_MASK	(\
		BIT(GAUDI_ENGINE_ID_MME_0) |\
		BIT(GAUDI_ENGINE_ID_MME_2) |\
		GENMASK_ULL(GAUDI_ENGINE_ID_TPC_7, GAUDI_ENGINE_ID_TPC_0))

#घोषणा HBM_SCRUBBING_TIMEOUT_US	1000000 /* 1s */

#घोषणा GAUDI_PLL_MAX 10

अटल स्थिर अक्षर gaudi_irq_name[GAUDI_MSI_ENTRIES][GAUDI_MAX_STRING_LEN] = अणु
		"gaudi cq 0_0", "gaudi cq 0_1", "gaudi cq 0_2", "gaudi cq 0_3",
		"gaudi cq 1_0", "gaudi cq 1_1", "gaudi cq 1_2", "gaudi cq 1_3",
		"gaudi cq 5_0", "gaudi cq 5_1", "gaudi cq 5_2", "gaudi cq 5_3",
		"gaudi cpu eq"
पूर्ण;

अटल स्थिर u8 gaudi_dma_assignment[GAUDI_DMA_MAX] = अणु
	[GAUDI_PCI_DMA_1] = GAUDI_ENGINE_ID_DMA_0,
	[GAUDI_PCI_DMA_2] = GAUDI_ENGINE_ID_DMA_1,
	[GAUDI_HBM_DMA_1] = GAUDI_ENGINE_ID_DMA_2,
	[GAUDI_HBM_DMA_2] = GAUDI_ENGINE_ID_DMA_3,
	[GAUDI_HBM_DMA_3] = GAUDI_ENGINE_ID_DMA_4,
	[GAUDI_HBM_DMA_4] = GAUDI_ENGINE_ID_DMA_5,
	[GAUDI_HBM_DMA_5] = GAUDI_ENGINE_ID_DMA_6,
	[GAUDI_HBM_DMA_6] = GAUDI_ENGINE_ID_DMA_7
पूर्ण;

अटल स्थिर u8 gaudi_cq_assignment[NUMBER_OF_CMPLT_QUEUES] = अणु
	[0] = GAUDI_QUEUE_ID_DMA_0_0,
	[1] = GAUDI_QUEUE_ID_DMA_0_1,
	[2] = GAUDI_QUEUE_ID_DMA_0_2,
	[3] = GAUDI_QUEUE_ID_DMA_0_3,
	[4] = GAUDI_QUEUE_ID_DMA_1_0,
	[5] = GAUDI_QUEUE_ID_DMA_1_1,
	[6] = GAUDI_QUEUE_ID_DMA_1_2,
	[7] = GAUDI_QUEUE_ID_DMA_1_3,
पूर्ण;

अटल स्थिर u16 gaudi_packet_sizes[MAX_PACKET_ID] = अणु
	[PACKET_WREG_32]	= माप(काष्ठा packet_wreg32),
	[PACKET_WREG_BULK]	= माप(काष्ठा packet_wreg_bulk),
	[PACKET_MSG_LONG]	= माप(काष्ठा packet_msg_दीर्घ),
	[PACKET_MSG_SHORT]	= माप(काष्ठा packet_msg_लघु),
	[PACKET_CP_DMA]		= माप(काष्ठा packet_cp_dma),
	[PACKET_REPEAT]		= माप(काष्ठा packet_repeat),
	[PACKET_MSG_PROT]	= माप(काष्ठा packet_msg_prot),
	[PACKET_FENCE]		= माप(काष्ठा packet_fence),
	[PACKET_LIN_DMA]	= माप(काष्ठा packet_lin_dma),
	[PACKET_NOP]		= माप(काष्ठा packet_nop),
	[PACKET_STOP]		= माप(काष्ठा packet_stop),
	[PACKET_ARB_POINT]	= माप(काष्ठा packet_arb_poपूर्णांक),
	[PACKET_WAIT]		= माप(काष्ठा packet_रुको),
	[PACKET_LOAD_AND_EXE]	= माप(काष्ठा packet_load_and_exe)
पूर्ण;

अटल अंतरभूत bool validate_packet_id(क्रमागत packet_id id)
अणु
	चयन (id) अणु
	हाल PACKET_WREG_32:
	हाल PACKET_WREG_BULK:
	हाल PACKET_MSG_LONG:
	हाल PACKET_MSG_SHORT:
	हाल PACKET_CP_DMA:
	हाल PACKET_REPEAT:
	हाल PACKET_MSG_PROT:
	हाल PACKET_FENCE:
	हाल PACKET_LIN_DMA:
	हाल PACKET_NOP:
	हाल PACKET_STOP:
	हाल PACKET_ARB_POINT:
	हाल PACKET_WAIT:
	हाल PACKET_LOAD_AND_EXE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर
gaudi_tpc_पूर्णांकerrupts_cause[GAUDI_NUM_OF_TPC_INTR_CAUSE] = अणु
	"tpc_address_exceed_slm",
	"tpc_div_by_0",
	"tpc_spu_mac_overflow",
	"tpc_spu_addsub_overflow",
	"tpc_spu_abs_overflow",
	"tpc_spu_fp_dst_nan_inf",
	"tpc_spu_fp_dst_denorm",
	"tpc_vpu_mac_overflow",
	"tpc_vpu_addsub_overflow",
	"tpc_vpu_abs_overflow",
	"tpc_vpu_fp_dst_nan_inf",
	"tpc_vpu_fp_dst_denorm",
	"tpc_assertions",
	"tpc_illegal_instruction",
	"tpc_pc_wrap_around",
	"tpc_qm_sw_err",
	"tpc_hbw_rresp_err",
	"tpc_hbw_bresp_err",
	"tpc_lbw_rresp_err",
	"tpc_lbw_bresp_err"
पूर्ण;

अटल स्थिर अक्षर * स्थिर
gaudi_qman_error_cause[GAUDI_NUM_OF_QM_ERR_CAUSE] = अणु
	"PQ AXI HBW error",
	"CQ AXI HBW error",
	"CP AXI HBW error",
	"CP error due to undefined OPCODE",
	"CP encountered STOP OPCODE",
	"CP AXI LBW error",
	"CP WRREG32 or WRBULK returned error",
	"N/A",
	"FENCE 0 inc over max value and clipped",
	"FENCE 1 inc over max value and clipped",
	"FENCE 2 inc over max value and clipped",
	"FENCE 3 inc over max value and clipped",
	"FENCE 0 dec under min value and clipped",
	"FENCE 1 dec under min value and clipped",
	"FENCE 2 dec under min value and clipped",
	"FENCE 3 dec under min value and clipped"
पूर्ण;

अटल स्थिर अक्षर * स्थिर
gaudi_qman_arb_error_cause[GAUDI_NUM_OF_QM_ARB_ERR_CAUSE] = अणु
	"Choice push while full error",
	"Choice Q watchdog error",
	"MSG AXI LBW returned with error"
पूर्ण;

क्रमागत gaudi_sm_sei_cause अणु
	GAUDI_SM_SEI_SO_OVERFLOW,
	GAUDI_SM_SEI_LBW_4B_UNALIGNED,
	GAUDI_SM_SEI_AXI_RESPONSE_ERR
पूर्ण;

अटल क्रमागत hl_queue_type gaudi_queue_type[GAUDI_QUEUE_ID_SIZE] = अणु
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_0_0 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_0_1 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_0_2 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_0_3 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_1_0 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_1_1 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_1_2 */
	QUEUE_TYPE_EXT, /* GAUDI_QUEUE_ID_DMA_1_3 */
	QUEUE_TYPE_CPU, /* GAUDI_QUEUE_ID_CPU_PQ */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_2_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_2_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_2_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_2_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_3_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_3_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_3_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_3_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_4_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_4_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_4_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_4_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_5_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_5_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_5_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_5_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_6_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_6_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_6_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_6_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_7_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_7_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_7_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_DMA_7_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_0_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_0_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_0_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_0_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_1_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_1_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_1_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_MME_1_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_0_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_0_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_0_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_0_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_1_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_1_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_1_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_1_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_2_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_2_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_2_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_2_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_3_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_3_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_3_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_3_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_4_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_4_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_4_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_4_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_5_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_5_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_5_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_5_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_6_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_6_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_6_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_6_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_7_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_7_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_7_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_TPC_7_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_0_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_0_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_0_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_0_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_1_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_1_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_1_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_1_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_2_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_2_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_2_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_2_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_3_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_3_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_3_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_3_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_4_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_4_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_4_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_4_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_5_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_5_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_5_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_5_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_6_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_6_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_6_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_6_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_7_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_7_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_7_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_7_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_8_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_8_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_8_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_8_3 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_9_0 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_9_1 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_9_2 */
	QUEUE_TYPE_INT, /* GAUDI_QUEUE_ID_NIC_9_3 */
पूर्ण;

काष्ठा ecc_info_extract_params अणु
	u64 block_address;
	u32 num_memories;
	bool derr;
	bool disable_घड़ी_gating;
पूर्ण;

अटल पूर्णांक gaudi_mmu_update_asid_hop0_addr(काष्ठा hl_device *hdev, u32 asid,
								u64 phys_addr);
अटल पूर्णांक gaudi_send_job_on_qman0(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_job *job);
अटल पूर्णांक gaudi_स_रखो_device_memory(काष्ठा hl_device *hdev, u64 addr,
					u32 size, u64 val);
अटल पूर्णांक gaudi_स_रखो_रेजिस्टरs(काष्ठा hl_device *hdev, u64 reg_base,
					u32 num_regs, u32 val);
अटल पूर्णांक gaudi_schedule_रेजिस्टर_स_रखो(काष्ठा hl_device *hdev,
		u32 hw_queue_id, u64 reg_base, u32 num_regs, u32 val);
अटल पूर्णांक gaudi_run_tpc_kernel(काष्ठा hl_device *hdev, u64 tpc_kernel,
				u32 tpc_id);
अटल पूर्णांक gaudi_mmu_clear_pgt_range(काष्ठा hl_device *hdev);
अटल पूर्णांक gaudi_cpucp_info_get(काष्ठा hl_device *hdev);
अटल व्योम gaudi_disable_घड़ी_gating(काष्ठा hl_device *hdev);
अटल व्योम gaudi_mmu_prepare(काष्ठा hl_device *hdev, u32 asid);
अटल u32 gaudi_gen_संकेत_cb(काष्ठा hl_device *hdev, व्योम *data, u16 sob_id,
				u32 size, bool eb);
अटल u32 gaudi_gen_रुको_cb(काष्ठा hl_device *hdev,
				काष्ठा hl_gen_रुको_properties *prop);

अटल अंतरभूत क्रमागत hl_collective_mode
get_collective_mode(काष्ठा hl_device *hdev, u32 queue_id)
अणु
	अगर (gaudi_queue_type[queue_id] == QUEUE_TYPE_EXT)
		वापस HL_COLLECTIVE_MASTER;

	अगर (queue_id >= GAUDI_QUEUE_ID_DMA_5_0 &&
			queue_id <= GAUDI_QUEUE_ID_DMA_5_3)
		वापस HL_COLLECTIVE_SLAVE;

	अगर (queue_id >= GAUDI_QUEUE_ID_TPC_7_0 &&
			queue_id <= GAUDI_QUEUE_ID_TPC_7_3)
		वापस HL_COLLECTIVE_SLAVE;

	अगर (queue_id >= GAUDI_QUEUE_ID_NIC_0_0 &&
			queue_id <= GAUDI_QUEUE_ID_NIC_9_3)
		वापस HL_COLLECTIVE_SLAVE;

	वापस HL_COLLECTIVE_NOT_SUPPORTED;
पूर्ण

अटल अंतरभूत व्योम set_शेष_घातer_values(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;

	अगर (hdev->card_type == cpucp_card_type_pmc) अणु
		prop->max_घातer_शेष = MAX_POWER_DEFAULT_PMC;
		prop->dc_घातer_शेष = DC_POWER_DEFAULT_PMC;
	पूर्ण अन्यथा अणु
		prop->max_घातer_शेष = MAX_POWER_DEFAULT_PCI;
		prop->dc_घातer_शेष = DC_POWER_DEFAULT_PCI;
	पूर्ण
पूर्ण

अटल पूर्णांक gaudi_get_fixed_properties(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u32 num_sync_stream_queues = 0;
	पूर्णांक i;

	prop->max_queues = GAUDI_QUEUE_ID_SIZE;
	prop->hw_queues_props = kसुस्मृति(prop->max_queues,
			माप(काष्ठा hw_queue_properties),
			GFP_KERNEL);

	अगर (!prop->hw_queues_props)
		वापस -ENOMEM;

	क्रम (i = 0 ; i < prop->max_queues ; i++) अणु
		अगर (gaudi_queue_type[i] == QUEUE_TYPE_EXT) अणु
			prop->hw_queues_props[i].type = QUEUE_TYPE_EXT;
			prop->hw_queues_props[i].driver_only = 0;
			prop->hw_queues_props[i].supports_sync_stream = 1;
			prop->hw_queues_props[i].cb_alloc_flags =
				CB_ALLOC_KERNEL;
			num_sync_stream_queues++;
		पूर्ण अन्यथा अगर (gaudi_queue_type[i] == QUEUE_TYPE_CPU) अणु
			prop->hw_queues_props[i].type = QUEUE_TYPE_CPU;
			prop->hw_queues_props[i].driver_only = 1;
			prop->hw_queues_props[i].supports_sync_stream = 0;
			prop->hw_queues_props[i].cb_alloc_flags =
				CB_ALLOC_KERNEL;
		पूर्ण अन्यथा अगर (gaudi_queue_type[i] == QUEUE_TYPE_INT) अणु
			prop->hw_queues_props[i].type = QUEUE_TYPE_INT;
			prop->hw_queues_props[i].driver_only = 0;
			prop->hw_queues_props[i].supports_sync_stream = 0;
			prop->hw_queues_props[i].cb_alloc_flags =
				CB_ALLOC_USER;

		पूर्ण
		prop->hw_queues_props[i].collective_mode =
						get_collective_mode(hdev, i);
	पूर्ण

	prop->completion_queues_count = NUMBER_OF_CMPLT_QUEUES;
	prop->collective_first_sob = 0;
	prop->collective_first_mon = 0;

	/* 2 SOBs per पूर्णांकernal queue stream are reserved क्रम collective */
	prop->sync_stream_first_sob =
			ALIGN(NUMBER_OF_SOBS_IN_GRP, HL_MAX_SOBS_PER_MONITOR)
			* QMAN_STREAMS * HL_RSVD_SOBS;

	/* 1 monitor per पूर्णांकernal queue stream are reserved क्रम collective
	 * 2 monitors per बाह्यal queue stream are reserved क्रम collective
	 */
	prop->sync_stream_first_mon =
			(NUMBER_OF_COLLECTIVE_QUEUES * QMAN_STREAMS) +
			(NUMBER_OF_EXT_HW_QUEUES * 2);

	prop->dram_base_address = DRAM_PHYS_BASE;
	prop->dram_size = GAUDI_HBM_SIZE_32GB;
	prop->dram_end_address = prop->dram_base_address +
					prop->dram_size;
	prop->dram_user_base_address = DRAM_BASE_ADDR_USER;

	prop->sram_base_address = SRAM_BASE_ADDR;
	prop->sram_size = SRAM_SIZE;
	prop->sram_end_address = prop->sram_base_address +
					prop->sram_size;
	prop->sram_user_base_address = prop->sram_base_address +
					SRAM_USER_BASE_OFFSET;

	prop->mmu_pgt_addr = MMU_PAGE_TABLES_ADDR;
	अगर (hdev->pldm)
		prop->mmu_pgt_size = 0x800000; /* 8MB */
	अन्यथा
		prop->mmu_pgt_size = MMU_PAGE_TABLES_SIZE;
	prop->mmu_pte_size = HL_PTE_SIZE;
	prop->mmu_hop_table_size = HOP_TABLE_SIZE;
	prop->mmu_hop0_tables_total_size = HOP0_TABLES_TOTAL_SIZE;
	prop->dram_page_size = PAGE_SIZE_2MB;
	prop->dram_supports_भव_memory = false;

	prop->pmmu.hop0_shअगरt = HOP0_SHIFT;
	prop->pmmu.hop1_shअगरt = HOP1_SHIFT;
	prop->pmmu.hop2_shअगरt = HOP2_SHIFT;
	prop->pmmu.hop3_shअगरt = HOP3_SHIFT;
	prop->pmmu.hop4_shअगरt = HOP4_SHIFT;
	prop->pmmu.hop0_mask = HOP0_MASK;
	prop->pmmu.hop1_mask = HOP1_MASK;
	prop->pmmu.hop2_mask = HOP2_MASK;
	prop->pmmu.hop3_mask = HOP3_MASK;
	prop->pmmu.hop4_mask = HOP4_MASK;
	prop->pmmu.start_addr = VA_HOST_SPACE_START;
	prop->pmmu.end_addr =
			(VA_HOST_SPACE_START + VA_HOST_SPACE_SIZE / 2) - 1;
	prop->pmmu.page_size = PAGE_SIZE_4KB;
	prop->pmmu.num_hops = MMU_ARCH_5_HOPS;

	/* PMMU and HPMMU are the same except of page size */
	स_नकल(&prop->pmmu_huge, &prop->pmmu, माप(prop->pmmu));
	prop->pmmu_huge.page_size = PAGE_SIZE_2MB;

	/* shअगरts and masks are the same in PMMU and DMMU */
	स_नकल(&prop->dmmu, &prop->pmmu, माप(prop->pmmu));
	prop->dmmu.start_addr = (VA_HOST_SPACE_START + VA_HOST_SPACE_SIZE / 2);
	prop->dmmu.end_addr = VA_HOST_SPACE_END;
	prop->dmmu.page_size = PAGE_SIZE_2MB;

	prop->cfg_size = CFG_SIZE;
	prop->max_asid = MAX_ASID;
	prop->num_of_events = GAUDI_EVENT_SIZE;
	prop->tpc_enabled_mask = TPC_ENABLED_MASK;

	set_शेष_घातer_values(hdev);

	prop->cb_pool_cb_cnt = GAUDI_CB_POOL_CB_CNT;
	prop->cb_pool_cb_size = GAUDI_CB_POOL_CB_SIZE;

	prop->pcie_dbi_base_address = mmPCIE_DBI_BASE;
	prop->pcie_aux_dbi_reg_addr = CFG_BASE + mmPCIE_AUX_DBI;

	म_नकलन(prop->cpucp_info.card_name, GAUDI_DEFAULT_CARD_NAME,
					CARD_NAME_MAX_LEN);

	prop->max_pending_cs = GAUDI_MAX_PENDING_CS;

	prop->first_available_user_sob[HL_GAUDI_WS_DCORE] =
			prop->sync_stream_first_sob +
			(num_sync_stream_queues * HL_RSVD_SOBS);
	prop->first_available_user_mon[HL_GAUDI_WS_DCORE] =
			prop->sync_stream_first_mon +
			(num_sync_stream_queues * HL_RSVD_MONS);

	prop->first_available_user_msix_पूर्णांकerrupt = अच_लघु_उच्च;

	क्रम (i = 0 ; i < HL_MAX_DCORES ; i++)
		prop->first_available_cq[i] = अच_लघु_उच्च;

	prop->fw_security_status_valid = false;
	prop->hard_reset_करोne_by_fw = false;

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_pci_bars_map(काष्ठा hl_device *hdev)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु"SRAM", "CFG", "HBM"पूर्ण;
	bool is_wc[3] = अणुfalse, false, trueपूर्ण;
	पूर्णांक rc;

	rc = hl_pci_bars_map(hdev, name, is_wc);
	अगर (rc)
		वापस rc;

	hdev->rmmio = hdev->pcie_bar[CFG_BAR_ID] +
			(CFG_BASE - SPI_FLASH_BASE_ADDR);

	वापस 0;
पूर्ण

अटल u64 gaudi_set_hbm_bar_base(काष्ठा hl_device *hdev, u64 addr)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा hl_inbound_pci_region pci_region;
	u64 old_addr = addr;
	पूर्णांक rc;

	अगर ((gaudi) && (gaudi->hbm_bar_cur_addr == addr))
		वापस old_addr;

	/* Inbound Region 2 - Bar 4 - Poपूर्णांक to HBM */
	pci_region.mode = PCI_BAR_MATCH_MODE;
	pci_region.bar = HBM_BAR_ID;
	pci_region.addr = addr;
	rc = hl_pci_set_inbound_region(hdev, 2, &pci_region);
	अगर (rc)
		वापस U64_MAX;

	अगर (gaudi) अणु
		old_addr = gaudi->hbm_bar_cur_addr;
		gaudi->hbm_bar_cur_addr = addr;
	पूर्ण

	वापस old_addr;
पूर्ण

अटल पूर्णांक gaudi_init_iatu(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_inbound_pci_region inbound_region;
	काष्ठा hl_outbound_pci_region outbound_region;
	पूर्णांक rc;

	अगर (hdev->asic_prop.iatu_करोne_by_fw) अणु
		hdev->asic_funcs->set_dma_mask_from_fw(hdev);
		वापस 0;
	पूर्ण

	/* Inbound Region 0 - Bar 0 - Poपूर्णांक to SRAM + CFG */
	inbound_region.mode = PCI_BAR_MATCH_MODE;
	inbound_region.bar = SRAM_BAR_ID;
	inbound_region.addr = SRAM_BASE_ADDR;
	rc = hl_pci_set_inbound_region(hdev, 0, &inbound_region);
	अगर (rc)
		जाओ करोne;

	/* Inbound Region 1 - Bar 2 - Poपूर्णांक to SPI FLASH */
	inbound_region.mode = PCI_BAR_MATCH_MODE;
	inbound_region.bar = CFG_BAR_ID;
	inbound_region.addr = SPI_FLASH_BASE_ADDR;
	rc = hl_pci_set_inbound_region(hdev, 1, &inbound_region);
	अगर (rc)
		जाओ करोne;

	/* Inbound Region 2 - Bar 4 - Poपूर्णांक to HBM */
	inbound_region.mode = PCI_BAR_MATCH_MODE;
	inbound_region.bar = HBM_BAR_ID;
	inbound_region.addr = DRAM_PHYS_BASE;
	rc = hl_pci_set_inbound_region(hdev, 2, &inbound_region);
	अगर (rc)
		जाओ करोne;

	hdev->asic_funcs->set_dma_mask_from_fw(hdev);

	/* Outbound Region 0 - Poपूर्णांक to Host */
	outbound_region.addr = HOST_PHYS_BASE;
	outbound_region.size = HOST_PHYS_SIZE;
	rc = hl_pci_set_outbound_region(hdev, &outbound_region);

करोne:
	वापस rc;
पूर्ण

अटल क्रमागत hl_device_hw_state gaudi_get_hw_state(काष्ठा hl_device *hdev)
अणु
	वापस RREG32(mmHW_STATE);
पूर्ण

अटल पूर्णांक gaudi_early_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा pci_dev *pdev = hdev->pdev;
	u32 fw_boot_status;
	पूर्णांक rc;

	rc = gaudi_get_fixed_properties(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to get fixed properties\n");
		वापस rc;
	पूर्ण

	/* Check BAR sizes */
	अगर (pci_resource_len(pdev, SRAM_BAR_ID) != SRAM_BAR_SIZE) अणु
		dev_err(hdev->dev,
			"Not " HL_NAME "? BAR %d size %llu, expecting %llu\n",
			SRAM_BAR_ID,
			(अचिन्हित दीर्घ दीर्घ) pci_resource_len(pdev,
							SRAM_BAR_ID),
			SRAM_BAR_SIZE);
		rc = -ENODEV;
		जाओ मुक्त_queue_props;
	पूर्ण

	अगर (pci_resource_len(pdev, CFG_BAR_ID) != CFG_BAR_SIZE) अणु
		dev_err(hdev->dev,
			"Not " HL_NAME "? BAR %d size %llu, expecting %llu\n",
			CFG_BAR_ID,
			(अचिन्हित दीर्घ दीर्घ) pci_resource_len(pdev,
								CFG_BAR_ID),
			CFG_BAR_SIZE);
		rc = -ENODEV;
		जाओ मुक्त_queue_props;
	पूर्ण

	prop->dram_pci_bar_size = pci_resource_len(pdev, HBM_BAR_ID);

	/* If FW security is enabled at this poपूर्णांक it means no access to ELBI */
	अगर (!hdev->asic_prop.fw_security_disabled) अणु
		hdev->asic_prop.iatu_करोne_by_fw = true;
		जाओ pci_init;
	पूर्ण

	rc = hl_pci_elbi_पढ़ो(hdev, CFG_BASE + mmCPU_BOOT_DEV_STS0,
				&fw_boot_status);
	अगर (rc)
		जाओ मुक्त_queue_props;

	/* Check whether FW is configuring iATU */
	अगर ((fw_boot_status & CPU_BOOT_DEV_STS0_ENABLED) &&
			(fw_boot_status & CPU_BOOT_DEV_STS0_FW_IATU_CONF_EN))
		hdev->asic_prop.iatu_करोne_by_fw = true;

pci_init:
	rc = hl_pci_init(hdev);
	अगर (rc)
		जाओ मुक्त_queue_props;

	/* Beक्रमe continuing in the initialization, we need to पढ़ो the preboot
	 * version to determine whether we run with a security-enabled firmware
	 */
	rc = hl_fw_पढ़ो_preboot_status(hdev, mmPSOC_GLOBAL_CONF_CPU_BOOT_STATUS,
			mmCPU_BOOT_DEV_STS0, mmCPU_BOOT_ERR0,
			GAUDI_BOOT_FIT_REQ_TIMEOUT_USEC);
	अगर (rc) अणु
		अगर (hdev->reset_on_preboot_fail)
			hdev->asic_funcs->hw_fini(hdev, true);
		जाओ pci_fini;
	पूर्ण

	अगर (gaudi_get_hw_state(hdev) == HL_DEVICE_HW_STATE_सूचीTY) अणु
		dev_info(hdev->dev,
			"H/W state is dirty, must reset before initializing\n");
		hdev->asic_funcs->hw_fini(hdev, true);
	पूर्ण

	वापस 0;

pci_fini:
	hl_pci_fini(hdev);
मुक्त_queue_props:
	kमुक्त(hdev->asic_prop.hw_queues_props);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_early_fini(काष्ठा hl_device *hdev)
अणु
	kमुक्त(hdev->asic_prop.hw_queues_props);
	hl_pci_fini(hdev);

	वापस 0;
पूर्ण

/**
 * gaudi_fetch_psoc_frequency - Fetch PSOC frequency values
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
अटल पूर्णांक gaudi_fetch_psoc_frequency(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u32 nr = 0, nf = 0, od = 0, भाग_fctr = 0, pll_clk, भाग_sel;
	u16 pll_freq_arr[HL_PLL_NUM_OUTPUTS], freq;
	पूर्णांक rc;

	अगर (hdev->asic_prop.fw_security_disabled) अणु
		/* Backward compatibility */
		भाग_fctr = RREG32(mmPSOC_CPU_PLL_DIV_FACTOR_2);
		भाग_sel = RREG32(mmPSOC_CPU_PLL_DIV_SEL_2);
		nr = RREG32(mmPSOC_CPU_PLL_NR);
		nf = RREG32(mmPSOC_CPU_PLL_NF);
		od = RREG32(mmPSOC_CPU_PLL_OD);

		अगर (भाग_sel == DIV_SEL_REF_CLK ||
				भाग_sel == DIV_SEL_DIVIDED_REF) अणु
			अगर (भाग_sel == DIV_SEL_REF_CLK)
				freq = PLL_REF_CLK;
			अन्यथा
				freq = PLL_REF_CLK / (भाग_fctr + 1);
		पूर्ण अन्यथा अगर (भाग_sel == DIV_SEL_PLL_CLK ||
			भाग_sel == DIV_SEL_DIVIDED_PLL) अणु
			pll_clk = PLL_REF_CLK * (nf + 1) /
					((nr + 1) * (od + 1));
			अगर (भाग_sel == DIV_SEL_PLL_CLK)
				freq = pll_clk;
			अन्यथा
				freq = pll_clk / (भाग_fctr + 1);
		पूर्ण अन्यथा अणु
			dev_warn(hdev->dev,
				"Received invalid div select value: %d",
				भाग_sel);
			freq = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = hl_fw_cpucp_pll_info_get(hdev, HL_GAUDI_CPU_PLL, pll_freq_arr);

		अगर (rc)
			वापस rc;

		freq = pll_freq_arr[2];
	पूर्ण

	prop->psoc_बारtamp_frequency = freq;
	prop->psoc_pci_pll_nr = nr;
	prop->psoc_pci_pll_nf = nf;
	prop->psoc_pci_pll_od = od;
	prop->psoc_pci_pll_भाग_factor = भाग_fctr;

	वापस 0;
पूर्ण

अटल पूर्णांक _gaudi_init_tpc_mem(काष्ठा hl_device *hdev,
		dma_addr_t tpc_kernel_src_addr, u32 tpc_kernel_size)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा packet_lin_dma *init_tpc_mem_pkt;
	काष्ठा hl_cs_job *job;
	काष्ठा hl_cb *cb;
	u64 dst_addr;
	u32 cb_size, ctl;
	u8 tpc_id;
	पूर्णांक rc;

	cb = hl_cb_kernel_create(hdev, PAGE_SIZE, false);
	अगर (!cb)
		वापस -EFAULT;

	init_tpc_mem_pkt = cb->kernel_address;
	cb_size = माप(*init_tpc_mem_pkt);
	स_रखो(init_tpc_mem_pkt, 0, cb_size);

	init_tpc_mem_pkt->tsize = cpu_to_le32(tpc_kernel_size);

	ctl = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_LIN_DMA);
	ctl |= FIELD_PREP(GAUDI_PKT_LIN_DMA_CTL_LIN_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	init_tpc_mem_pkt->ctl = cpu_to_le32(ctl);

	init_tpc_mem_pkt->src_addr = cpu_to_le64(tpc_kernel_src_addr);
	dst_addr = (prop->sram_user_base_address &
			GAUDI_PKT_LIN_DMA_DST_ADDR_MASK) >>
			GAUDI_PKT_LIN_DMA_DST_ADDR_SHIFT;
	init_tpc_mem_pkt->dst_addr |= cpu_to_le64(dst_addr);

	job = hl_cs_allocate_job(hdev, QUEUE_TYPE_EXT, true);
	अगर (!job) अणु
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		rc = -ENOMEM;
		जाओ release_cb;
	पूर्ण

	job->id = 0;
	job->user_cb = cb;
	atomic_inc(&job->user_cb->cs_cnt);
	job->user_cb_size = cb_size;
	job->hw_queue_id = GAUDI_QUEUE_ID_DMA_0_0;
	job->patched_cb = job->user_cb;
	job->job_cb_size = job->user_cb_size + माप(काष्ठा packet_msg_prot);

	hl_debugfs_add_job(hdev, job);

	rc = gaudi_send_job_on_qman0(hdev, job);

	अगर (rc)
		जाओ मुक्त_job;

	क्रम (tpc_id = 0 ; tpc_id < TPC_NUMBER_OF_ENGINES ; tpc_id++) अणु
		rc = gaudi_run_tpc_kernel(hdev, dst_addr, tpc_id);
		अगर (rc)
			अवरोध;
	पूर्ण

मुक्त_job:
	hl_userptr_delete_list(hdev, &job->userptr_list);
	hl_debugfs_हटाओ_job(hdev, job);
	kमुक्त(job);
	atomic_dec(&cb->cs_cnt);

release_cb:
	hl_cb_put(cb);
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	वापस rc;
पूर्ण

/*
 * gaudi_init_tpc_mem() - Initialize TPC memories.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 *
 * Copy TPC kernel fw from firmware file and run it to initialize TPC memories.
 *
 * Return: 0 क्रम success, negative value क्रम error.
 */
अटल पूर्णांक gaudi_init_tpc_mem(काष्ठा hl_device *hdev)
अणु
	स्थिर काष्ठा firmware *fw;
	माप_प्रकार fw_size;
	व्योम *cpu_addr;
	dma_addr_t dma_handle;
	पूर्णांक rc, count = 5;

again:
	rc = request_firmware(&fw, GAUDI_TPC_FW_खाता, hdev->dev);
	अगर (rc == -EINTR && count-- > 0) अणु
		msleep(50);
		जाओ again;
	पूर्ण

	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to load firmware file %s\n",
				GAUDI_TPC_FW_खाता);
		जाओ out;
	पूर्ण

	fw_size = fw->size;
	cpu_addr = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, fw_size,
			&dma_handle, GFP_KERNEL | __GFP_ZERO);
	अगर (!cpu_addr) अणु
		dev_err(hdev->dev,
			"Failed to allocate %zu of dma memory for TPC kernel\n",
			fw_size);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(cpu_addr, fw->data, fw_size);

	rc = _gaudi_init_tpc_mem(hdev, dma_handle, fw_size);

	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev, fw->size, cpu_addr,
			dma_handle);

out:
	release_firmware(fw);
	वापस rc;
पूर्ण

अटल व्योम gaudi_collective_map_sobs(काष्ठा hl_device *hdev, u32 stream)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_collective_properties *prop = &gaudi->collective_props;
	काष्ठा hl_hw_queue *q;
	u32 i, sob_id, sob_group_id, queue_id;

	/* Iterate through SOB groups and assign a SOB क्रम each slave queue */
	sob_group_id =
		stream * HL_RSVD_SOBS + prop->curr_sob_group_idx[stream];
	sob_id = prop->hw_sob_group[sob_group_id].base_sob_id;

	queue_id = GAUDI_QUEUE_ID_NIC_0_0 + stream;
	क्रम (i = 0 ; i < NIC_NUMBER_OF_ENGINES ; i++) अणु
		q = &hdev->kernel_queues[queue_id + (4 * i)];
		q->sync_stream_prop.collective_sob_id = sob_id + i;
	पूर्ण

	/* Both DMA5 and TPC7 use the same resources since only a single
	 * engine need to participate in the reduction process
	 */
	queue_id = GAUDI_QUEUE_ID_DMA_5_0 + stream;
	q = &hdev->kernel_queues[queue_id];
	q->sync_stream_prop.collective_sob_id =
			sob_id + NIC_NUMBER_OF_ENGINES;

	queue_id = GAUDI_QUEUE_ID_TPC_7_0 + stream;
	q = &hdev->kernel_queues[queue_id];
	q->sync_stream_prop.collective_sob_id =
			sob_id + NIC_NUMBER_OF_ENGINES;
पूर्ण

अटल व्योम gaudi_sob_group_hw_reset(काष्ठा kref *ref)
अणु
	काष्ठा gaudi_hw_sob_group *hw_sob_group =
		container_of(ref, काष्ठा gaudi_hw_sob_group, kref);
	काष्ठा hl_device *hdev = hw_sob_group->hdev;
	u64 base_addr;
	पूर्णांक rc;

	base_addr = CFG_BASE + mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0 +
			hw_sob_group->base_sob_id * 4;
	rc = gaudi_schedule_रेजिस्टर_स_रखो(hdev, hw_sob_group->queue_id,
			base_addr, NUMBER_OF_SOBS_IN_GRP, 0);
	अगर (rc)
		dev_err(hdev->dev,
			"failed resetting sob group - sob base %u, count %u",
			hw_sob_group->base_sob_id, NUMBER_OF_SOBS_IN_GRP);

	kref_init(&hw_sob_group->kref);
पूर्ण

अटल व्योम gaudi_sob_group_reset_error(काष्ठा kref *ref)
अणु
	काष्ठा gaudi_hw_sob_group *hw_sob_group =
		container_of(ref, काष्ठा gaudi_hw_sob_group, kref);
	काष्ठा hl_device *hdev = hw_sob_group->hdev;

	dev_crit(hdev->dev,
		"SOB release shouldn't be called here, base_sob_id: %d\n",
		hw_sob_group->base_sob_id);
पूर्ण

अटल पूर्णांक gaudi_collective_init(काष्ठा hl_device *hdev)
अणु
	u32 i, master_monitor_sobs, sob_id, reserved_sobs_per_group;
	काष्ठा gaudi_collective_properties *prop;
	काष्ठा gaudi_device *gaudi;

	gaudi = hdev->asic_specअगरic;
	prop = &gaudi->collective_props;
	sob_id = hdev->asic_prop.collective_first_sob;

	/* First sob in group must be aligned to HL_MAX_SOBS_PER_MONITOR */
	reserved_sobs_per_group =
		ALIGN(NUMBER_OF_SOBS_IN_GRP, HL_MAX_SOBS_PER_MONITOR);

	/* Init SOB groups */
	क्रम (i = 0 ; i < NUM_SOB_GROUPS; i++) अणु
		prop->hw_sob_group[i].hdev = hdev;
		prop->hw_sob_group[i].base_sob_id = sob_id;
		sob_id += reserved_sobs_per_group;
		gaudi_sob_group_hw_reset(&prop->hw_sob_group[i].kref);
	पूर्ण

	क्रम (i = 0 ; i < QMAN_STREAMS; i++) अणु
		prop->next_sob_group_val[i] = 1;
		prop->curr_sob_group_idx[i] = 0;
		gaudi_collective_map_sobs(hdev, i);
	पूर्ण

	prop->mstr_sob_mask[0] = 0;
	master_monitor_sobs = HL_MAX_SOBS_PER_MONITOR;
	क्रम (i = 0 ; i < master_monitor_sobs ; i++)
		अगर (gaudi->hw_cap_initialized & BIT(HW_CAP_NIC_SHIFT + i))
			prop->mstr_sob_mask[0] |= BIT(i);

	prop->mstr_sob_mask[1] = 0;
	master_monitor_sobs =
		NIC_NUMBER_OF_ENGINES - HL_MAX_SOBS_PER_MONITOR;
	क्रम (i = 0 ; i < master_monitor_sobs; i++) अणु
		अगर (gaudi->hw_cap_initialized & BIT(HW_CAP_NIC_SHIFT + i))
			prop->mstr_sob_mask[1] |= BIT(i);
	पूर्ण

	/* Set collective engine bit */
	prop->mstr_sob_mask[1] |= BIT(i);

	वापस 0;
पूर्ण

अटल व्योम gaudi_reset_sob_group(काष्ठा hl_device *hdev, u16 sob_group)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_collective_properties *cprop = &gaudi->collective_props;

	kref_put(&cprop->hw_sob_group[sob_group].kref,
					gaudi_sob_group_hw_reset);
पूर्ण

अटल व्योम gaudi_collective_master_init_job(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_job *job, u32 stream, u32 sob_group_offset)
अणु
	u32 master_sob_base, master_monitor, queue_id, cb_size = 0;
	काष्ठा gaudi_collective_properties *cprop;
	काष्ठा hl_gen_रुको_properties रुको_prop;
	काष्ठा hl_sync_stream_properties *prop;
	काष्ठा gaudi_device *gaudi;

	gaudi = hdev->asic_specअगरic;
	cprop = &gaudi->collective_props;
	queue_id = job->hw_queue_id;
	prop = &hdev->kernel_queues[queue_id].sync_stream_prop;

	master_sob_base =
		cprop->hw_sob_group[sob_group_offset].base_sob_id;
	master_monitor = prop->collective_mstr_mon_id[0];

	cprop->hw_sob_group[sob_group_offset].queue_id = queue_id;

	dev_dbg(hdev->dev,
		"Generate master wait CBs, sob %d (mask %#x), val:0x%x, mon %u, q %d\n",
		master_sob_base, cprop->mstr_sob_mask[0],
		cprop->next_sob_group_val[stream],
		master_monitor, queue_id);

	रुको_prop.data = (व्योम *) job->patched_cb;
	रुको_prop.sob_base = master_sob_base;
	रुको_prop.sob_mask = cprop->mstr_sob_mask[0];
	रुको_prop.sob_val = cprop->next_sob_group_val[stream];
	रुको_prop.mon_id = master_monitor;
	रुको_prop.q_idx = queue_id;
	रुको_prop.size = cb_size;
	cb_size += gaudi_gen_रुको_cb(hdev, &रुको_prop);

	master_sob_base += HL_MAX_SOBS_PER_MONITOR;
	master_monitor = prop->collective_mstr_mon_id[1];

	dev_dbg(hdev->dev,
		"Generate master wait CBs, sob %d (mask %#x), val:0x%x, mon %u, q %d\n",
		master_sob_base, cprop->mstr_sob_mask[1],
		cprop->next_sob_group_val[stream],
		master_monitor, queue_id);

	रुको_prop.sob_base = master_sob_base;
	रुको_prop.sob_mask = cprop->mstr_sob_mask[1];
	रुको_prop.mon_id = master_monitor;
	रुको_prop.size = cb_size;
	cb_size += gaudi_gen_रुको_cb(hdev, &रुको_prop);
पूर्ण

अटल व्योम gaudi_collective_slave_init_job(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_job *job, काष्ठा hl_cs_compl *cs_cmpl)
अणु
	काष्ठा hl_gen_रुको_properties रुको_prop;
	काष्ठा hl_sync_stream_properties *prop;
	u32 queue_id, cb_size = 0;

	queue_id = job->hw_queue_id;
	prop = &hdev->kernel_queues[queue_id].sync_stream_prop;

	/* Add to रुको CBs using slave monitor */
	रुको_prop.data = (व्योम *) job->user_cb;
	रुको_prop.sob_base = cs_cmpl->hw_sob->sob_id;
	रुको_prop.sob_mask = 0x1;
	रुको_prop.sob_val = cs_cmpl->sob_val;
	रुको_prop.mon_id = prop->collective_slave_mon_id;
	रुको_prop.q_idx = queue_id;
	रुको_prop.size = cb_size;

	dev_dbg(hdev->dev,
		"Generate slave wait CB, sob %d, val:0x%x, mon %d, q %d\n",
		cs_cmpl->hw_sob->sob_id, cs_cmpl->sob_val,
		prop->collective_slave_mon_id, queue_id);

	cb_size += gaudi_gen_रुको_cb(hdev, &रुको_prop);

	dev_dbg(hdev->dev,
		"generate signal CB, sob_id: %d, sob val: 1, q_idx: %d\n",
		prop->collective_sob_id, queue_id);

	cb_size += gaudi_gen_संकेत_cb(hdev, job->user_cb,
			prop->collective_sob_id, cb_size, false);
पूर्ण

अटल व्योम gaudi_collective_रुको_init_cs(काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_cs_compl *संकेत_cs_cmpl =
		container_of(cs->संकेत_fence, काष्ठा hl_cs_compl, base_fence);
	काष्ठा hl_cs_compl *cs_cmpl =
		container_of(cs->fence, काष्ठा hl_cs_compl, base_fence);
	काष्ठा gaudi_collective_properties *cprop;
	u32 stream, queue_id, sob_group_offset;
	काष्ठा gaudi_device *gaudi;
	काष्ठा hl_device *hdev;
	काष्ठा hl_cs_job *job;
	काष्ठा hl_ctx *ctx;

	ctx = cs->ctx;
	hdev = ctx->hdev;
	gaudi = hdev->asic_specअगरic;
	cprop = &gaudi->collective_props;

	/* copy the SOB id and value of the संकेत CS */
	cs_cmpl->hw_sob = संकेत_cs_cmpl->hw_sob;
	cs_cmpl->sob_val = संकेत_cs_cmpl->sob_val;

	/* Calculate the stream from collective master queue (1st job) */
	job = list_first_entry(&cs->job_list, काष्ठा hl_cs_job, cs_node);
	stream = job->hw_queue_id % 4;
	sob_group_offset =
		stream * HL_RSVD_SOBS + cprop->curr_sob_group_idx[stream];

	list_क्रम_each_entry(job, &cs->job_list, cs_node) अणु
		queue_id = job->hw_queue_id;

		अगर (hdev->kernel_queues[queue_id].collective_mode ==
				HL_COLLECTIVE_MASTER)
			gaudi_collective_master_init_job(hdev, job, stream,
						sob_group_offset);
		अन्यथा
			gaudi_collective_slave_init_job(hdev, job, cs_cmpl);
	पूर्ण

	cs_cmpl->sob_group = sob_group_offset;

	/* Handle sob group kref and wraparound */
	kref_get(&cprop->hw_sob_group[sob_group_offset].kref);
	cprop->next_sob_group_val[stream]++;

	अगर (cprop->next_sob_group_val[stream] == HL_MAX_SOB_VAL) अणु
		/*
		 * Decrement as we reached the max value.
		 * The release function won't be called here as we've
		 * just incremented the refcount.
		 */
		kref_put(&cprop->hw_sob_group[sob_group_offset].kref,
				gaudi_sob_group_reset_error);
		cprop->next_sob_group_val[stream] = 1;
		/* only two SOBs are currently in use */
		cprop->curr_sob_group_idx[stream] =
			(cprop->curr_sob_group_idx[stream] + 1) &
							(HL_RSVD_SOBS - 1);

		gaudi_collective_map_sobs(hdev, stream);

		dev_dbg(hdev->dev, "switched to SOB group %d, stream: %d\n",
				cprop->curr_sob_group_idx[stream], stream);
	पूर्ण

	/* Increment kref since all slave queues are now रुकोing on it */
	kref_get(&cs_cmpl->hw_sob->kref);
	/*
	 * Must put the संकेत fence after the SOB refcnt increment so
	 * the SOB refcnt won't turn 0 and reset the SOB beक्रमe the
	 * रुको CS was submitted.
	 */
	mb();
	hl_fence_put(cs->संकेत_fence);
	cs->संकेत_fence = शून्य;
पूर्ण

अटल पूर्णांक gaudi_collective_रुको_create_job(काष्ठा hl_device *hdev,
		काष्ठा hl_ctx *ctx, काष्ठा hl_cs *cs,
		क्रमागत hl_collective_mode mode, u32 queue_id, u32 रुको_queue_id)
अणु
	काष्ठा hw_queue_properties *hw_queue_prop;
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_cs_job *job;
	काष्ठा hl_cb *cb;
	u32 cb_size;
	bool patched_cb;

	cntr = &hdev->aggregated_cs_counters;

	अगर (mode == HL_COLLECTIVE_MASTER) अणु
		/* CB size of collective master queue contains
		 * 4 msg लघु packets क्रम monitor 1 configuration
		 * 1 fence packet
		 * 4 msg लघु packets क्रम monitor 2 configuration
		 * 1 fence packet
		 * 2 msg prot packets क्रम completion and MSI-X
		 */
		cb_size = माप(काष्ठा packet_msg_लघु) * 8 +
				माप(काष्ठा packet_fence) * 2 +
				माप(काष्ठा packet_msg_prot) * 2;
		patched_cb = true;
	पूर्ण अन्यथा अणु
		/* CB size of collective slave queues contains
		 * 4 msg लघु packets क्रम monitor configuration
		 * 1 fence packet
		 * 1 additional msg लघु packet क्रम sob संकेत
		 */
		cb_size = माप(काष्ठा packet_msg_लघु) * 5 +
				माप(काष्ठा packet_fence);
		patched_cb = false;
	पूर्ण

	hw_queue_prop = &hdev->asic_prop.hw_queues_props[queue_id];
	job = hl_cs_allocate_job(hdev, hw_queue_prop->type, true);
	अगर (!job) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		वापस -ENOMEM;
	पूर्ण

	/* Allocate पूर्णांकernal mapped CB क्रम non patched CBs */
	cb = hl_cb_kernel_create(hdev, cb_size,
			hdev->mmu_enable && !patched_cb);
	अगर (!cb) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		kमुक्त(job);
		वापस -EFAULT;
	पूर्ण

	job->id = 0;
	job->cs = cs;
	job->user_cb = cb;
	atomic_inc(&job->user_cb->cs_cnt);
	job->user_cb_size = cb_size;
	job->hw_queue_id = queue_id;

	/*
	 * No need in parsing, user CB is the patched CB.
	 * We call hl_cb_destroy() out of two reasons - we करोn't need
	 * the CB in the CB idr anymore and to decrement its refcount as
	 * it was incremented inside hl_cb_kernel_create().
	 */
	अगर (patched_cb)
		job->patched_cb = job->user_cb;
	अन्यथा
		job->patched_cb = शून्य;

	job->job_cb_size = job->user_cb_size;
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	/* increment refcount as क्रम बाह्यal queues we get completion */
	अगर (hw_queue_prop->type == QUEUE_TYPE_EXT)
		cs_get(cs);

	cs->jobs_in_queue_cnt[job->hw_queue_id]++;

	list_add_tail(&job->cs_node, &cs->job_list);

	hl_debugfs_add_job(hdev, job);

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_collective_रुको_create_jobs(काष्ठा hl_device *hdev,
		काष्ठा hl_ctx *ctx, काष्ठा hl_cs *cs, u32 रुको_queue_id,
		u32 collective_engine_id)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा hw_queue_properties *hw_queue_prop;
	u32 queue_id, collective_queue, num_jobs;
	u32 stream, nic_queue, nic_idx = 0;
	bool skip;
	पूर्णांक i, rc = 0;

	/* Verअगरy रुको queue id is configured as master */
	hw_queue_prop = &hdev->asic_prop.hw_queues_props[रुको_queue_id];
	अगर (!(hw_queue_prop->collective_mode == HL_COLLECTIVE_MASTER)) अणु
		dev_err(hdev->dev,
			"Queue %d is not configured as collective master\n",
			रुको_queue_id);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy engine id is supported */
	अगर (collective_engine_id != GAUDI_ENGINE_ID_DMA_5 &&
			collective_engine_id != GAUDI_ENGINE_ID_TPC_7) अणु
		dev_err(hdev->dev,
			"Collective wait does not support engine %u\n",
			collective_engine_id);
		वापस -EINVAL;
	पूर्ण

	stream = रुको_queue_id % 4;

	अगर (collective_engine_id == GAUDI_ENGINE_ID_DMA_5)
		collective_queue = GAUDI_QUEUE_ID_DMA_5_0 + stream;
	अन्यथा
		collective_queue = GAUDI_QUEUE_ID_TPC_7_0 + stream;

	num_jobs = NUMBER_OF_SOBS_IN_GRP + 1;
	nic_queue = GAUDI_QUEUE_ID_NIC_0_0 + stream;

	/* First job goes to the collective master queue, it will रुको क्रम
	 * the collective slave queues to finish execution.
	 * The synchronization is करोne using two monitors:
	 * First monitor क्रम NICs 0-7, second monitor क्रम NICs 8-9 and the
	 * reduction engine (DMA5/TPC7).
	 *
	 * Rest of the jobs goes to the collective slave queues which will
	 * all रुको क्रम the user to संकेत sob 'cs_cmpl->sob_val'.
	 */
	क्रम (i = 0 ; i < num_jobs ; i++) अणु
		अगर (i == 0) अणु
			queue_id = रुको_queue_id;
			rc = gaudi_collective_रुको_create_job(hdev, ctx, cs,
				HL_COLLECTIVE_MASTER, queue_id, रुको_queue_id);
		पूर्ण अन्यथा अणु
			अगर (nic_idx < NIC_NUMBER_OF_ENGINES) अणु
				अगर (gaudi->hw_cap_initialized &
					BIT(HW_CAP_NIC_SHIFT + nic_idx))
					skip = false;
				अन्यथा
					skip = true;

				queue_id = nic_queue;
				nic_queue += 4;
				nic_idx++;

				अगर (skip)
					जारी;
			पूर्ण अन्यथा अणु
				queue_id = collective_queue;
			पूर्ण

			rc = gaudi_collective_रुको_create_job(hdev, ctx, cs,
				HL_COLLECTIVE_SLAVE, queue_id, रुको_queue_id);
		पूर्ण

		अगर (rc)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_late_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक rc;

	rc = gaudi->cpucp_info_get(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to get cpucp info\n");
		वापस rc;
	पूर्ण

	अगर ((hdev->card_type == cpucp_card_type_pci) &&
			(hdev->nic_ports_mask & 0x3)) अणु
		dev_info(hdev->dev,
			"PCI card detected, only 8 ports are enabled\n");
		hdev->nic_ports_mask &= ~0x3;

		/* Stop and disable unused NIC QMANs */
		WREG32(mmNIC0_QM0_GLBL_CFG1, NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
					NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
					NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

		WREG32(mmNIC0_QM1_GLBL_CFG1, NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
					NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
					NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

		WREG32(mmNIC0_QM0_GLBL_CFG0, 0);
		WREG32(mmNIC0_QM1_GLBL_CFG0, 0);

		gaudi->hw_cap_initialized &= ~(HW_CAP_NIC0 | HW_CAP_NIC1);
	पूर्ण

	rc = hl_fw_send_pci_access_msg(hdev, CPUCP_PACKET_ENABLE_PCI_ACCESS);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to enable PCI access from CPU\n");
		वापस rc;
	पूर्ण

	rc = gaudi_fetch_psoc_frequency(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to fetch psoc frequency\n");
		जाओ disable_pci_access;
	पूर्ण

	rc = gaudi_mmu_clear_pgt_range(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to clear MMU page tables range\n");
		जाओ disable_pci_access;
	पूर्ण

	rc = gaudi_init_tpc_mem(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to initialize TPC memories\n");
		जाओ disable_pci_access;
	पूर्ण

	rc = gaudi_collective_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to init collective\n");
		जाओ disable_pci_access;
	पूर्ण

	वापस 0;

disable_pci_access:
	hl_fw_send_pci_access_msg(hdev, CPUCP_PACKET_DISABLE_PCI_ACCESS);

	वापस rc;
पूर्ण

अटल व्योम gaudi_late_fini(काष्ठा hl_device *hdev)
अणु
	स्थिर काष्ठा hwmon_channel_info **channel_info_arr;
	पूर्णांक i = 0;

	अगर (!hdev->hl_chip_info->info)
		वापस;

	channel_info_arr = hdev->hl_chip_info->info;

	जबतक (channel_info_arr[i]) अणु
		kमुक्त(channel_info_arr[i]->config);
		kमुक्त(channel_info_arr[i]);
		i++;
	पूर्ण

	kमुक्त(channel_info_arr);

	hdev->hl_chip_info->info = शून्य;
पूर्ण

अटल पूर्णांक gaudi_alloc_cpu_accessible_dma_mem(काष्ठा hl_device *hdev)
अणु
	dma_addr_t dma_addr_arr[GAUDI_ALLOC_CPU_MEM_RETRY_CNT] = अणुपूर्ण, end_addr;
	व्योम *virt_addr_arr[GAUDI_ALLOC_CPU_MEM_RETRY_CNT] = अणुपूर्ण;
	पूर्णांक i, j, rc = 0;

	/*
	 * The device CPU works with 40-bits addresses, जबतक bit 39 must be set
	 * to '1' when accessing the host.
	 * Bits 49:39 of the full host address are saved क्रम a later
	 * configuration of the HW to perक्रमm extension to 50 bits.
	 * Because there is a single HW रेजिस्टर that holds the extension bits,
	 * these bits must be identical in all allocated range.
	 */

	क्रम (i = 0 ; i < GAUDI_ALLOC_CPU_MEM_RETRY_CNT ; i++) अणु
		virt_addr_arr[i] =
			hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
						HL_CPU_ACCESSIBLE_MEM_SIZE,
						&dma_addr_arr[i],
						GFP_KERNEL | __GFP_ZERO);
		अगर (!virt_addr_arr[i]) अणु
			rc = -ENOMEM;
			जाओ मुक्त_dma_mem_arr;
		पूर्ण

		end_addr = dma_addr_arr[i] + HL_CPU_ACCESSIBLE_MEM_SIZE - 1;
		अगर (GAUDI_CPU_PCI_MSB_ADDR(dma_addr_arr[i]) ==
				GAUDI_CPU_PCI_MSB_ADDR(end_addr))
			अवरोध;
	पूर्ण

	अगर (i == GAUDI_ALLOC_CPU_MEM_RETRY_CNT) अणु
		dev_err(hdev->dev,
			"MSB of CPU accessible DMA memory are not identical in all range\n");
		rc = -EFAULT;
		जाओ मुक्त_dma_mem_arr;
	पूर्ण

	hdev->cpu_accessible_dma_mem = virt_addr_arr[i];
	hdev->cpu_accessible_dma_address = dma_addr_arr[i];
	hdev->cpu_pci_msb_addr =
		GAUDI_CPU_PCI_MSB_ADDR(hdev->cpu_accessible_dma_address);

	अगर (hdev->asic_prop.fw_security_disabled)
		GAUDI_PCI_TO_CPU_ADDR(hdev->cpu_accessible_dma_address);

मुक्त_dma_mem_arr:
	क्रम (j = 0 ; j < i ; j++)
		hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
						HL_CPU_ACCESSIBLE_MEM_SIZE,
						virt_addr_arr[j],
						dma_addr_arr[j]);

	वापस rc;
पूर्ण

अटल व्योम gaudi_मुक्त_पूर्णांकernal_qmans_pq_mem(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;
	u32 i;

	क्रम (i = 0 ; i < GAUDI_QUEUE_ID_SIZE ; i++) अणु
		q = &gaudi->पूर्णांकernal_qmans[i];
		अगर (!q->pq_kernel_addr)
			जारी;
		hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev, q->pq_size,
							q->pq_kernel_addr,
							q->pq_dma_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक gaudi_alloc_पूर्णांकernal_qmans_pq_mem(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;
	पूर्णांक rc, i;

	क्रम (i = 0 ; i < GAUDI_QUEUE_ID_SIZE ; i++) अणु
		अगर (gaudi_queue_type[i] != QUEUE_TYPE_INT)
			जारी;

		q = &gaudi->पूर्णांकernal_qmans[i];

		चयन (i) अणु
		हाल GAUDI_QUEUE_ID_DMA_2_0 ... GAUDI_QUEUE_ID_DMA_7_3:
			q->pq_size = HBM_DMA_QMAN_SIZE_IN_BYTES;
			अवरोध;
		हाल GAUDI_QUEUE_ID_MME_0_0 ... GAUDI_QUEUE_ID_MME_1_3:
			q->pq_size = MME_QMAN_SIZE_IN_BYTES;
			अवरोध;
		हाल GAUDI_QUEUE_ID_TPC_0_0 ... GAUDI_QUEUE_ID_TPC_7_3:
			q->pq_size = TPC_QMAN_SIZE_IN_BYTES;
			अवरोध;
		हाल GAUDI_QUEUE_ID_NIC_0_0 ... GAUDI_QUEUE_ID_NIC_9_3:
			q->pq_size = NIC_QMAN_SIZE_IN_BYTES;
			अवरोध;
		शेष:
			dev_err(hdev->dev, "Bad internal queue index %d", i);
			rc = -EINVAL;
			जाओ मुक्त_पूर्णांकernal_qmans_pq_mem;
		पूर्ण

		q->pq_kernel_addr = hdev->asic_funcs->asic_dma_alloc_coherent(
						hdev, q->pq_size,
						&q->pq_dma_addr,
						GFP_KERNEL | __GFP_ZERO);
		अगर (!q->pq_kernel_addr) अणु
			rc = -ENOMEM;
			जाओ मुक्त_पूर्णांकernal_qmans_pq_mem;
		पूर्ण
	पूर्ण

	वापस 0;

मुक्त_पूर्णांकernal_qmans_pq_mem:
	gaudi_मुक्त_पूर्णांकernal_qmans_pq_mem(hdev);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_sw_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi;
	u32 i, event_id = 0;
	पूर्णांक rc;

	/* Allocate device काष्ठाure */
	gaudi = kzalloc(माप(*gaudi), GFP_KERNEL);
	अगर (!gaudi)
		वापस -ENOMEM;

	क्रम (i = 0 ; i < ARRAY_SIZE(gaudi_irq_map_table) ; i++) अणु
		अगर (gaudi_irq_map_table[i].valid) अणु
			अगर (event_id == GAUDI_EVENT_SIZE) अणु
				dev_err(hdev->dev,
					"Event array exceeds the limit of %u events\n",
					GAUDI_EVENT_SIZE);
				rc = -EINVAL;
				जाओ मुक्त_gaudi_device;
			पूर्ण

			gaudi->events[event_id++] =
					gaudi_irq_map_table[i].fc_id;
		पूर्ण
	पूर्ण

	gaudi->cpucp_info_get = gaudi_cpucp_info_get;

	gaudi->max_freq_value = GAUDI_MAX_CLK_FREQ;

	hdev->asic_specअगरic = gaudi;

	/* Create DMA pool क्रम small allocations */
	hdev->dma_pool = dma_pool_create(dev_name(hdev->dev),
			&hdev->pdev->dev, GAUDI_DMA_POOL_BLK_SIZE, 8, 0);
	अगर (!hdev->dma_pool) अणु
		dev_err(hdev->dev, "failed to create DMA pool\n");
		rc = -ENOMEM;
		जाओ मुक्त_gaudi_device;
	पूर्ण

	rc = gaudi_alloc_cpu_accessible_dma_mem(hdev);
	अगर (rc)
		जाओ मुक्त_dma_pool;

	hdev->cpu_accessible_dma_pool = gen_pool_create(ilog2(32), -1);
	अगर (!hdev->cpu_accessible_dma_pool) अणु
		dev_err(hdev->dev,
			"Failed to create CPU accessible DMA pool\n");
		rc = -ENOMEM;
		जाओ मुक्त_cpu_dma_mem;
	पूर्ण

	rc = gen_pool_add(hdev->cpu_accessible_dma_pool,
				(uपूर्णांकptr_t) hdev->cpu_accessible_dma_mem,
				HL_CPU_ACCESSIBLE_MEM_SIZE, -1);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to add memory to CPU accessible DMA pool\n");
		rc = -EFAULT;
		जाओ मुक्त_cpu_accessible_dma_pool;
	पूर्ण

	rc = gaudi_alloc_पूर्णांकernal_qmans_pq_mem(hdev);
	अगर (rc)
		जाओ मुक्त_cpu_accessible_dma_pool;

	spin_lock_init(&gaudi->hw_queues_lock);
	mutex_init(&gaudi->clk_gate_mutex);

	hdev->supports_sync_stream = true;
	hdev->supports_coresight = true;
	hdev->supports_staged_submission = true;

	वापस 0;

मुक्त_cpu_accessible_dma_pool:
	gen_pool_destroy(hdev->cpu_accessible_dma_pool);
मुक्त_cpu_dma_mem:
	अगर (hdev->asic_prop.fw_security_disabled)
		GAUDI_CPU_TO_PCI_ADDR(hdev->cpu_accessible_dma_address,
					hdev->cpu_pci_msb_addr);
	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
			HL_CPU_ACCESSIBLE_MEM_SIZE,
			hdev->cpu_accessible_dma_mem,
			hdev->cpu_accessible_dma_address);
मुक्त_dma_pool:
	dma_pool_destroy(hdev->dma_pool);
मुक्त_gaudi_device:
	kमुक्त(gaudi);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_sw_fini(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	gaudi_मुक्त_पूर्णांकernal_qmans_pq_mem(hdev);

	gen_pool_destroy(hdev->cpu_accessible_dma_pool);

	अगर (hdev->asic_prop.fw_security_disabled)
		GAUDI_CPU_TO_PCI_ADDR(hdev->cpu_accessible_dma_address,
					hdev->cpu_pci_msb_addr);

	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
			HL_CPU_ACCESSIBLE_MEM_SIZE,
			hdev->cpu_accessible_dma_mem,
			hdev->cpu_accessible_dma_address);

	dma_pool_destroy(hdev->dma_pool);

	mutex_destroy(&gaudi->clk_gate_mutex);

	kमुक्त(gaudi);

	वापस 0;
पूर्ण

अटल irqवापस_t gaudi_irq_handler_single(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hl_device *hdev = arg;
	पूर्णांक i;

	अगर (hdev->disabled)
		वापस IRQ_HANDLED;

	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		hl_irq_handler_cq(irq, &hdev->completion_queue[i]);

	hl_irq_handler_eq(irq, &hdev->event_queue);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * For backward compatibility, new MSI पूर्णांकerrupts should be set after the
 * existing CPU and NIC पूर्णांकerrupts.
 */
अटल पूर्णांक gaudi_pci_irq_vector(काष्ठा hl_device *hdev, अचिन्हित पूर्णांक nr,
				bool cpu_eq)
अणु
	पूर्णांक msi_vec;

	अगर ((nr != GAUDI_EVENT_QUEUE_MSI_IDX) && (cpu_eq))
		dev_crit(hdev->dev, "CPU EQ must use IRQ %d\n",
				GAUDI_EVENT_QUEUE_MSI_IDX);

	msi_vec = ((nr < GAUDI_EVENT_QUEUE_MSI_IDX) || (cpu_eq)) ? nr :
			(nr + NIC_NUMBER_OF_ENGINES + 1);

	वापस pci_irq_vector(hdev->pdev, msi_vec);
पूर्ण

अटल पूर्णांक gaudi_enable_msi_single(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc, irq;

	dev_dbg(hdev->dev, "Working in single MSI IRQ mode\n");

	irq = gaudi_pci_irq_vector(hdev, 0, false);
	rc = request_irq(irq, gaudi_irq_handler_single, 0,
			"gaudi single msi", hdev);
	अगर (rc)
		dev_err(hdev->dev,
			"Failed to request single MSI IRQ\n");

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_enable_msi_multi(काष्ठा hl_device *hdev)
अणु
	पूर्णांक cq_cnt = hdev->asic_prop.completion_queues_count;
	पूर्णांक rc, i, irq_cnt_init, irq;

	क्रम (i = 0, irq_cnt_init = 0 ; i < cq_cnt ; i++, irq_cnt_init++) अणु
		irq = gaudi_pci_irq_vector(hdev, i, false);
		rc = request_irq(irq, hl_irq_handler_cq, 0, gaudi_irq_name[i],
				&hdev->completion_queue[i]);
		अगर (rc) अणु
			dev_err(hdev->dev, "Failed to request IRQ %d", irq);
			जाओ मुक्त_irqs;
		पूर्ण
	पूर्ण

	irq = gaudi_pci_irq_vector(hdev, GAUDI_EVENT_QUEUE_MSI_IDX, true);
	rc = request_irq(irq, hl_irq_handler_eq, 0, gaudi_irq_name[cq_cnt],
				&hdev->event_queue);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to request IRQ %d", irq);
		जाओ मुक्त_irqs;
	पूर्ण

	वापस 0;

मुक्त_irqs:
	क्रम (i = 0 ; i < irq_cnt_init ; i++)
		मुक्त_irq(gaudi_pci_irq_vector(hdev, i, false),
				&hdev->completion_queue[i]);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_enable_msi(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक rc;

	अगर (gaudi->hw_cap_initialized & HW_CAP_MSI)
		वापस 0;

	rc = pci_alloc_irq_vectors(hdev->pdev, 1, 1, PCI_IRQ_MSI);
	अगर (rc < 0) अणु
		dev_err(hdev->dev, "MSI: Failed to enable support %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (rc < NUMBER_OF_INTERRUPTS) अणु
		gaudi->multi_msi_mode = false;
		rc = gaudi_enable_msi_single(hdev);
	पूर्ण अन्यथा अणु
		gaudi->multi_msi_mode = true;
		rc = gaudi_enable_msi_multi(hdev);
	पूर्ण

	अगर (rc)
		जाओ मुक्त_pci_irq_vectors;

	gaudi->hw_cap_initialized |= HW_CAP_MSI;

	वापस 0;

मुक्त_pci_irq_vectors:
	pci_मुक्त_irq_vectors(hdev->pdev);
	वापस rc;
पूर्ण

अटल व्योम gaudi_sync_irqs(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक i, cq_cnt = hdev->asic_prop.completion_queues_count;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MSI))
		वापस;

	/* Wait क्रम all pending IRQs to be finished */
	अगर (gaudi->multi_msi_mode) अणु
		क्रम (i = 0 ; i < cq_cnt ; i++)
			synchronize_irq(gaudi_pci_irq_vector(hdev, i, false));

		synchronize_irq(gaudi_pci_irq_vector(hdev,
						GAUDI_EVENT_QUEUE_MSI_IDX,
						true));
	पूर्ण अन्यथा अणु
		synchronize_irq(gaudi_pci_irq_vector(hdev, 0, false));
	पूर्ण
पूर्ण

अटल व्योम gaudi_disable_msi(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक i, irq, cq_cnt = hdev->asic_prop.completion_queues_count;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MSI))
		वापस;

	gaudi_sync_irqs(hdev);

	अगर (gaudi->multi_msi_mode) अणु
		irq = gaudi_pci_irq_vector(hdev, GAUDI_EVENT_QUEUE_MSI_IDX,
						true);
		मुक्त_irq(irq, &hdev->event_queue);

		क्रम (i = 0 ; i < cq_cnt ; i++) अणु
			irq = gaudi_pci_irq_vector(hdev, i, false);
			मुक्त_irq(irq, &hdev->completion_queue[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		मुक्त_irq(gaudi_pci_irq_vector(hdev, 0, false), hdev);
	पूर्ण

	pci_मुक्त_irq_vectors(hdev->pdev);

	gaudi->hw_cap_initialized &= ~HW_CAP_MSI;
पूर्ण

अटल व्योम gaudi_init_scrambler_sram(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!hdev->asic_prop.fw_security_disabled)
		वापस;

	अगर (hdev->asic_prop.fw_security_status_valid &&
			(hdev->asic_prop.fw_app_security_map &
					CPU_BOOT_DEV_STS0_SRAM_SCR_EN))
		वापस;

	अगर (gaudi->hw_cap_initialized & HW_CAP_SRAM_SCRAMBLER)
		वापस;

	अगर (!hdev->sram_scrambler_enable)
		वापस;

	WREG32(mmNIF_RTR_CTRL_0_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_1_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_2_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_3_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_4_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_5_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_6_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_7_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_0_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_1_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_2_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_3_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_4_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_5_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_6_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_7_SCRAM_SRAM_EN,
			1 << IF_RTR_CTRL_SCRAM_SRAM_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_E_N_DOWN_CH0_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_N_DOWN_CH1_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_S_DOWN_CH0_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_S_DOWN_CH1_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_N_DOWN_CH0_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_N_DOWN_CH1_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_S_DOWN_CH0_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_S_DOWN_CH1_SCRAM_SRAM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_SRAM_EN_VAL_SHIFT);

	gaudi->hw_cap_initialized |= HW_CAP_SRAM_SCRAMBLER;
पूर्ण

अटल व्योम gaudi_init_scrambler_hbm(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!hdev->asic_prop.fw_security_disabled)
		वापस;

	अगर (hdev->asic_prop.fw_security_status_valid &&
			(hdev->asic_prop.fw_boot_cpu_security_map &
					CPU_BOOT_DEV_STS0_DRAM_SCR_EN))
		वापस;

	अगर (gaudi->hw_cap_initialized & HW_CAP_HBM_SCRAMBLER)
		वापस;

	अगर (!hdev->dram_scrambler_enable)
		वापस;

	WREG32(mmNIF_RTR_CTRL_0_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_1_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_2_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_3_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_4_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_5_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_6_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_7_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_0_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_1_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_2_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_3_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_4_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_5_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_6_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_7_SCRAM_HBM_EN,
			1 << IF_RTR_CTRL_SCRAM_HBM_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_E_N_DOWN_CH0_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_N_DOWN_CH1_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_S_DOWN_CH0_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_S_DOWN_CH1_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_N_DOWN_CH0_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_N_DOWN_CH1_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_S_DOWN_CH0_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_S_DOWN_CH1_SCRAM_HBM_EN,
			1 << DMA_IF_DOWN_CHX_SCRAM_HBM_EN_VAL_SHIFT);

	gaudi->hw_cap_initialized |= HW_CAP_HBM_SCRAMBLER;
पूर्ण

अटल व्योम gaudi_init_e2e(काष्ठा hl_device *hdev)
अणु
	अगर (!hdev->asic_prop.fw_security_disabled)
		वापस;

	अगर (hdev->asic_prop.fw_security_status_valid &&
			(hdev->asic_prop.fw_boot_cpu_security_map &
					CPU_BOOT_DEV_STS0_E2E_CRED_EN))
		वापस;

	WREG32(mmSIF_RTR_CTRL_0_E2E_HBM_WR_SIZE, 247 >> 3);
	WREG32(mmSIF_RTR_CTRL_0_E2E_HBM_RD_SIZE, 785 >> 3);
	WREG32(mmSIF_RTR_CTRL_0_E2E_PCI_WR_SIZE, 49);
	WREG32(mmSIF_RTR_CTRL_0_E2E_PCI_RD_SIZE, 101);

	WREG32(mmSIF_RTR_CTRL_1_E2E_HBM_WR_SIZE, 275 >> 3);
	WREG32(mmSIF_RTR_CTRL_1_E2E_HBM_RD_SIZE, 614 >> 3);
	WREG32(mmSIF_RTR_CTRL_1_E2E_PCI_WR_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_1_E2E_PCI_RD_SIZE, 39);

	WREG32(mmSIF_RTR_CTRL_2_E2E_HBM_WR_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_2_E2E_HBM_RD_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_2_E2E_PCI_WR_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_2_E2E_PCI_RD_SIZE, 32);

	WREG32(mmSIF_RTR_CTRL_3_E2E_HBM_WR_SIZE, 176 >> 3);
	WREG32(mmSIF_RTR_CTRL_3_E2E_HBM_RD_SIZE, 32 >> 3);
	WREG32(mmSIF_RTR_CTRL_3_E2E_PCI_WR_SIZE, 19);
	WREG32(mmSIF_RTR_CTRL_3_E2E_PCI_RD_SIZE, 32);

	WREG32(mmSIF_RTR_CTRL_4_E2E_HBM_WR_SIZE, 176 >> 3);
	WREG32(mmSIF_RTR_CTRL_4_E2E_HBM_RD_SIZE, 32 >> 3);
	WREG32(mmSIF_RTR_CTRL_4_E2E_PCI_WR_SIZE, 19);
	WREG32(mmSIF_RTR_CTRL_4_E2E_PCI_RD_SIZE, 32);

	WREG32(mmSIF_RTR_CTRL_5_E2E_HBM_WR_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_5_E2E_HBM_RD_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_5_E2E_PCI_WR_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_5_E2E_PCI_RD_SIZE, 32);

	WREG32(mmSIF_RTR_CTRL_6_E2E_HBM_WR_SIZE, 275 >> 3);
	WREG32(mmSIF_RTR_CTRL_6_E2E_HBM_RD_SIZE, 614 >> 3);
	WREG32(mmSIF_RTR_CTRL_6_E2E_PCI_WR_SIZE, 1);
	WREG32(mmSIF_RTR_CTRL_6_E2E_PCI_RD_SIZE, 39);

	WREG32(mmSIF_RTR_CTRL_7_E2E_HBM_WR_SIZE, 297 >> 3);
	WREG32(mmSIF_RTR_CTRL_7_E2E_HBM_RD_SIZE, 908 >> 3);
	WREG32(mmSIF_RTR_CTRL_7_E2E_PCI_WR_SIZE, 19);
	WREG32(mmSIF_RTR_CTRL_7_E2E_PCI_RD_SIZE, 19);

	WREG32(mmNIF_RTR_CTRL_0_E2E_HBM_WR_SIZE, 318 >> 3);
	WREG32(mmNIF_RTR_CTRL_0_E2E_HBM_RD_SIZE, 956 >> 3);
	WREG32(mmNIF_RTR_CTRL_0_E2E_PCI_WR_SIZE, 79);
	WREG32(mmNIF_RTR_CTRL_0_E2E_PCI_RD_SIZE, 163);

	WREG32(mmNIF_RTR_CTRL_1_E2E_HBM_WR_SIZE, 275 >> 3);
	WREG32(mmNIF_RTR_CTRL_1_E2E_HBM_RD_SIZE, 614 >> 3);
	WREG32(mmNIF_RTR_CTRL_1_E2E_PCI_WR_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_1_E2E_PCI_RD_SIZE, 39);

	WREG32(mmNIF_RTR_CTRL_2_E2E_HBM_WR_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_2_E2E_HBM_RD_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_2_E2E_PCI_WR_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_2_E2E_PCI_RD_SIZE, 32);

	WREG32(mmNIF_RTR_CTRL_3_E2E_HBM_WR_SIZE, 176 >> 3);
	WREG32(mmNIF_RTR_CTRL_3_E2E_HBM_RD_SIZE, 32 >> 3);
	WREG32(mmNIF_RTR_CTRL_3_E2E_PCI_WR_SIZE, 19);
	WREG32(mmNIF_RTR_CTRL_3_E2E_PCI_RD_SIZE, 32);

	WREG32(mmNIF_RTR_CTRL_4_E2E_HBM_WR_SIZE, 176 >> 3);
	WREG32(mmNIF_RTR_CTRL_4_E2E_HBM_RD_SIZE, 32 >> 3);
	WREG32(mmNIF_RTR_CTRL_4_E2E_PCI_WR_SIZE, 19);
	WREG32(mmNIF_RTR_CTRL_4_E2E_PCI_RD_SIZE, 32);

	WREG32(mmNIF_RTR_CTRL_5_E2E_HBM_WR_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_5_E2E_HBM_RD_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_5_E2E_PCI_WR_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_5_E2E_PCI_RD_SIZE, 32);

	WREG32(mmNIF_RTR_CTRL_6_E2E_HBM_WR_SIZE, 275 >> 3);
	WREG32(mmNIF_RTR_CTRL_6_E2E_HBM_RD_SIZE, 614 >> 3);
	WREG32(mmNIF_RTR_CTRL_6_E2E_PCI_WR_SIZE, 1);
	WREG32(mmNIF_RTR_CTRL_6_E2E_PCI_RD_SIZE, 39);

	WREG32(mmNIF_RTR_CTRL_7_E2E_HBM_WR_SIZE, 318 >> 3);
	WREG32(mmNIF_RTR_CTRL_7_E2E_HBM_RD_SIZE, 956 >> 3);
	WREG32(mmNIF_RTR_CTRL_7_E2E_PCI_WR_SIZE, 79);
	WREG32(mmNIF_RTR_CTRL_7_E2E_PCI_RD_SIZE, 79);

	WREG32(mmDMA_IF_E_N_DOWN_CH0_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_E_N_DOWN_CH0_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_E_N_DOWN_CH0_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_E_N_DOWN_CH0_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_E_N_DOWN_CH1_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_E_N_DOWN_CH1_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_E_N_DOWN_CH1_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_E_N_DOWN_CH1_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_E_S_DOWN_CH0_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_E_S_DOWN_CH0_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_E_S_DOWN_CH0_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_E_S_DOWN_CH0_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_E_S_DOWN_CH1_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_E_S_DOWN_CH1_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_E_S_DOWN_CH1_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_E_S_DOWN_CH1_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_W_N_DOWN_CH0_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_W_N_DOWN_CH0_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_W_N_DOWN_CH0_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_W_N_DOWN_CH0_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_W_N_DOWN_CH1_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_W_N_DOWN_CH1_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_W_N_DOWN_CH1_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_W_N_DOWN_CH1_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_W_S_DOWN_CH0_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_W_S_DOWN_CH0_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_W_S_DOWN_CH0_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_W_S_DOWN_CH0_E2E_PCI_RD_SIZE, 338);

	WREG32(mmDMA_IF_W_S_DOWN_CH1_E2E_HBM_WR_SIZE, 344 >> 3);
	WREG32(mmDMA_IF_W_S_DOWN_CH1_E2E_HBM_RD_SIZE, 1000 >> 3);
	WREG32(mmDMA_IF_W_S_DOWN_CH1_E2E_PCI_WR_SIZE, 162);
	WREG32(mmDMA_IF_W_S_DOWN_CH1_E2E_PCI_RD_SIZE, 338);

	अगर (!hdev->dram_scrambler_enable) अणु
		WREG32(mmSIF_RTR_CTRL_0_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_0_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_0_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_0_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_1_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_1_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_1_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_1_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_2_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_2_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_2_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_2_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_3_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_3_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_3_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_3_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_4_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_4_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_4_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_4_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_5_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_5_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_5_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_5_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_6_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_6_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_6_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_6_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmSIF_RTR_CTRL_7_NL_HBM_SEL_0, 0x21);
		WREG32(mmSIF_RTR_CTRL_7_NL_HBM_SEL_1, 0x22);
		WREG32(mmSIF_RTR_CTRL_7_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmSIF_RTR_CTRL_7_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_0_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_0_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_0_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_0_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_1_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_1_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_1_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_1_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_2_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_2_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_2_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_2_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_3_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_3_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_3_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_3_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_4_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_4_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_4_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_4_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_5_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_5_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_5_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_5_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_6_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_6_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_6_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_6_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmNIF_RTR_CTRL_7_NL_HBM_SEL_0, 0x21);
		WREG32(mmNIF_RTR_CTRL_7_NL_HBM_SEL_1, 0x22);
		WREG32(mmNIF_RTR_CTRL_7_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmNIF_RTR_CTRL_7_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_E_N_DOWN_CH0_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_E_N_DOWN_CH0_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_E_N_DOWN_CH0_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_E_N_DOWN_CH0_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_E_N_DOWN_CH1_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_E_N_DOWN_CH1_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_E_N_DOWN_CH1_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_E_N_DOWN_CH1_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_E_S_DOWN_CH0_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_E_S_DOWN_CH0_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_E_S_DOWN_CH0_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_E_S_DOWN_CH0_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_E_S_DOWN_CH1_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_E_S_DOWN_CH1_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_E_S_DOWN_CH1_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_E_S_DOWN_CH1_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_W_N_DOWN_CH0_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_W_N_DOWN_CH0_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_W_N_DOWN_CH0_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_W_N_DOWN_CH0_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_W_N_DOWN_CH1_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_W_N_DOWN_CH1_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_W_N_DOWN_CH1_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_W_N_DOWN_CH1_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_W_S_DOWN_CH0_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_W_S_DOWN_CH0_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_W_S_DOWN_CH0_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_W_S_DOWN_CH0_NL_HBM_PC_SEL_3, 0x20);

		WREG32(mmDMA_IF_W_S_DOWN_CH1_NL_HBM_SEL_0, 0x21);
		WREG32(mmDMA_IF_W_S_DOWN_CH1_NL_HBM_SEL_1, 0x22);
		WREG32(mmDMA_IF_W_S_DOWN_CH1_NL_HBM_OFFSET_18, 0x1F);
		WREG32(mmDMA_IF_W_S_DOWN_CH1_NL_HBM_PC_SEL_3, 0x20);
	पूर्ण

	WREG32(mmSIF_RTR_CTRL_0_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_0_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_1_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_1_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_2_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_2_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_3_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_3_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_4_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_4_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_5_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_5_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_6_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_6_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmSIF_RTR_CTRL_7_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmSIF_RTR_CTRL_7_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_0_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_0_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_1_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_1_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_2_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_2_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_3_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_3_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_4_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_4_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_5_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_5_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_6_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_6_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmNIF_RTR_CTRL_7_E2E_HBM_EN,
			1 << IF_RTR_CTRL_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmNIF_RTR_CTRL_7_E2E_PCI_EN,
			1 << IF_RTR_CTRL_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_E_N_DOWN_CH0_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_N_DOWN_CH0_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_E_N_DOWN_CH1_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_N_DOWN_CH1_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_E_S_DOWN_CH0_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_S_DOWN_CH0_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_E_S_DOWN_CH1_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_E_S_DOWN_CH1_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_W_N_DOWN_CH0_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_N_DOWN_CH0_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_W_N_DOWN_CH1_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_N_DOWN_CH1_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_W_S_DOWN_CH0_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_S_DOWN_CH0_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);

	WREG32(mmDMA_IF_W_S_DOWN_CH1_E2E_HBM_EN,
			1 << DMA_IF_DOWN_CHX_E2E_HBM_EN_VAL_SHIFT);
	WREG32(mmDMA_IF_W_S_DOWN_CH1_E2E_PCI_EN,
			1 << DMA_IF_DOWN_CHX_E2E_PCI_EN_VAL_SHIFT);
पूर्ण

अटल व्योम gaudi_init_hbm_cred(काष्ठा hl_device *hdev)
अणु
	uपूर्णांक32_t hbm0_wr, hbm1_wr, hbm0_rd, hbm1_rd;

	अगर (!hdev->asic_prop.fw_security_disabled)
		वापस;

	अगर (hdev->asic_prop.fw_security_status_valid &&
			(hdev->asic_prop.fw_boot_cpu_security_map &
					CPU_BOOT_DEV_STS0_HBM_CRED_EN))
		वापस;

	hbm0_wr = 0x33333333;
	hbm0_rd = 0x77777777;
	hbm1_wr = 0x55555555;
	hbm1_rd = 0xDDDDDDDD;

	WREG32(mmDMA_IF_E_N_HBM0_WR_CRED_CNT, hbm0_wr);
	WREG32(mmDMA_IF_E_N_HBM1_WR_CRED_CNT, hbm1_wr);
	WREG32(mmDMA_IF_E_N_HBM0_RD_CRED_CNT, hbm0_rd);
	WREG32(mmDMA_IF_E_N_HBM1_RD_CRED_CNT, hbm1_rd);

	WREG32(mmDMA_IF_E_S_HBM0_WR_CRED_CNT, hbm0_wr);
	WREG32(mmDMA_IF_E_S_HBM1_WR_CRED_CNT, hbm1_wr);
	WREG32(mmDMA_IF_E_S_HBM0_RD_CRED_CNT, hbm0_rd);
	WREG32(mmDMA_IF_E_S_HBM1_RD_CRED_CNT, hbm1_rd);

	WREG32(mmDMA_IF_W_N_HBM0_WR_CRED_CNT, hbm0_wr);
	WREG32(mmDMA_IF_W_N_HBM1_WR_CRED_CNT, hbm1_wr);
	WREG32(mmDMA_IF_W_N_HBM0_RD_CRED_CNT, hbm0_rd);
	WREG32(mmDMA_IF_W_N_HBM1_RD_CRED_CNT, hbm1_rd);

	WREG32(mmDMA_IF_W_S_HBM0_WR_CRED_CNT, hbm0_wr);
	WREG32(mmDMA_IF_W_S_HBM1_WR_CRED_CNT, hbm1_wr);
	WREG32(mmDMA_IF_W_S_HBM0_RD_CRED_CNT, hbm0_rd);
	WREG32(mmDMA_IF_W_S_HBM1_RD_CRED_CNT, hbm1_rd);

	WREG32(mmDMA_IF_E_N_HBM_CRED_EN_0,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
	WREG32(mmDMA_IF_E_S_HBM_CRED_EN_0,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
	WREG32(mmDMA_IF_W_N_HBM_CRED_EN_0,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
	WREG32(mmDMA_IF_W_S_HBM_CRED_EN_0,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));

	WREG32(mmDMA_IF_E_N_HBM_CRED_EN_1,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
	WREG32(mmDMA_IF_E_S_HBM_CRED_EN_1,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
	WREG32(mmDMA_IF_W_N_HBM_CRED_EN_1,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
	WREG32(mmDMA_IF_W_S_HBM_CRED_EN_1,
			(1 << DMA_IF_HBM_CRED_EN_READ_CREDIT_EN_SHIFT) |
			(1 << DMA_IF_HBM_CRED_EN_WRITE_CREDIT_EN_SHIFT));
पूर्ण

अटल व्योम gaudi_init_golden_रेजिस्टरs(काष्ठा hl_device *hdev)
अणु
	u32 tpc_offset;
	पूर्णांक tpc_id, i;

	gaudi_init_e2e(hdev);
	gaudi_init_hbm_cred(hdev);

	क्रम (tpc_id = 0, tpc_offset = 0;
				tpc_id < TPC_NUMBER_OF_ENGINES;
				tpc_id++, tpc_offset += TPC_CFG_OFFSET) अणु
		/* Mask all arithmetic पूर्णांकerrupts from TPC */
		WREG32(mmTPC0_CFG_TPC_INTR_MASK + tpc_offset, 0x8FFF);
		/* Set 16 cache lines */
		WREG32_FIELD(TPC0_CFG_MSS_CONFIG, tpc_offset,
				ICACHE_FETCH_LINE_NUM, 2);
	पूर्ण

	/* Make sure 1st 128 bytes in SRAM are 0 क्रम Tensor DMA */
	क्रम (i = 0 ; i < 128 ; i += 8)
		ग_लिखोq(0, hdev->pcie_bar[SRAM_BAR_ID] + i);

	WREG32(mmMME0_CTRL_EUS_ROLLUP_CNT_ADD, 3);
	WREG32(mmMME1_CTRL_EUS_ROLLUP_CNT_ADD, 3);
	WREG32(mmMME2_CTRL_EUS_ROLLUP_CNT_ADD, 3);
	WREG32(mmMME3_CTRL_EUS_ROLLUP_CNT_ADD, 3);
पूर्ण

अटल व्योम gaudi_init_pci_dma_qman(काष्ठा hl_device *hdev, पूर्णांक dma_id,
					पूर्णांक qman_id, dma_addr_t qman_pq_addr)
अणु
	u32 mtr_base_en_lo, mtr_base_en_hi, mtr_base_ws_lo, mtr_base_ws_hi;
	u32 so_base_en_lo, so_base_en_hi, so_base_ws_lo, so_base_ws_hi;
	u32 q_off, dma_qm_offset;
	u32 dma_qm_err_cfg;

	dma_qm_offset = dma_id * DMA_QMAN_OFFSET;

	mtr_base_en_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_en_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	mtr_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);

	q_off = dma_qm_offset + qman_id * 4;

	WREG32(mmDMA0_QM_PQ_BASE_LO_0 + q_off, lower_32_bits(qman_pq_addr));
	WREG32(mmDMA0_QM_PQ_BASE_HI_0 + q_off, upper_32_bits(qman_pq_addr));

	WREG32(mmDMA0_QM_PQ_SIZE_0 + q_off, ilog2(HL_QUEUE_LENGTH));
	WREG32(mmDMA0_QM_PQ_PI_0 + q_off, 0);
	WREG32(mmDMA0_QM_PQ_CI_0 + q_off, 0);

	WREG32(mmDMA0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off, QMAN_LDMA_SIZE_OFFSET);
	WREG32(mmDMA0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_SRC_OFFSET);
	WREG32(mmDMA0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_DST_OFFSET);

	WREG32(mmDMA0_QM_CP_MSG_BASE0_ADDR_LO_0 + q_off, mtr_base_en_lo);
	WREG32(mmDMA0_QM_CP_MSG_BASE0_ADDR_HI_0 + q_off, mtr_base_en_hi);
	WREG32(mmDMA0_QM_CP_MSG_BASE1_ADDR_LO_0 + q_off, so_base_en_lo);
	WREG32(mmDMA0_QM_CP_MSG_BASE1_ADDR_HI_0 + q_off, so_base_en_hi);
	WREG32(mmDMA0_QM_CP_MSG_BASE2_ADDR_LO_0 + q_off, mtr_base_ws_lo);
	WREG32(mmDMA0_QM_CP_MSG_BASE2_ADDR_HI_0 + q_off, mtr_base_ws_hi);
	WREG32(mmDMA0_QM_CP_MSG_BASE3_ADDR_LO_0 + q_off, so_base_ws_lo);
	WREG32(mmDMA0_QM_CP_MSG_BASE3_ADDR_HI_0 + q_off, so_base_ws_hi);

	WREG32(mmDMA0_QM_CP_BARRIER_CFG_0 + q_off, 0x100);

	/* The following configuration is needed only once per QMAN */
	अगर (qman_id == 0) अणु
		/* Configure RAZWI IRQ */
		dma_qm_err_cfg = PCI_DMA_QMAN_GLBL_ERR_CFG_MSG_EN_MASK;
		अगर (hdev->stop_on_err) अणु
			dma_qm_err_cfg |=
				PCI_DMA_QMAN_GLBL_ERR_CFG_STOP_ON_ERR_EN_MASK;
		पूर्ण

		WREG32(mmDMA0_QM_GLBL_ERR_CFG + dma_qm_offset, dma_qm_err_cfg);
		WREG32(mmDMA0_QM_GLBL_ERR_ADDR_LO + dma_qm_offset,
			lower_32_bits(CFG_BASE +
					mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmDMA0_QM_GLBL_ERR_ADDR_HI + dma_qm_offset,
			upper_32_bits(CFG_BASE +
					mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmDMA0_QM_GLBL_ERR_WDATA + dma_qm_offset,
			gaudi_irq_map_table[GAUDI_EVENT_DMA0_QM].cpu_id +
									dma_id);

		WREG32(mmDMA0_QM_ARB_ERR_MSG_EN + dma_qm_offset,
				QM_ARB_ERR_MSG_EN_MASK);

		/* Increase ARB WDT to support streams architecture */
		WREG32(mmDMA0_QM_ARB_SLV_CHOISE_WDT + dma_qm_offset,
				GAUDI_ARB_WDT_TIMEOUT);

		WREG32(mmDMA0_QM_GLBL_PROT + dma_qm_offset,
				QMAN_EXTERNAL_MAKE_TRUSTED);

		WREG32(mmDMA0_QM_GLBL_CFG1 + dma_qm_offset, 0);
	पूर्ण
पूर्ण

अटल व्योम gaudi_init_dma_core(काष्ठा hl_device *hdev, पूर्णांक dma_id)
अणु
	u32 dma_offset = dma_id * DMA_CORE_OFFSET;
	u32 dma_err_cfg = 1 << DMA0_CORE_ERR_CFG_ERR_MSG_EN_SHIFT;

	/* Set to maximum possible according to physical size */
	WREG32(mmDMA0_CORE_RD_MAX_OUTSTAND + dma_offset, 0);
	WREG32(mmDMA0_CORE_RD_MAX_SIZE + dma_offset, 0);

	/* WA क्रम H/W bug H3-2116 */
	WREG32(mmDMA0_CORE_LBW_MAX_OUTSTAND + dma_offset, 15);

	/* STOP_ON bit implies no completion to operation in हाल of RAZWI */
	अगर (hdev->stop_on_err)
		dma_err_cfg |= 1 << DMA0_CORE_ERR_CFG_STOP_ON_ERR_SHIFT;

	WREG32(mmDMA0_CORE_ERR_CFG + dma_offset, dma_err_cfg);
	WREG32(mmDMA0_CORE_ERRMSG_ADDR_LO + dma_offset,
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
	WREG32(mmDMA0_CORE_ERRMSG_ADDR_HI + dma_offset,
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
	WREG32(mmDMA0_CORE_ERRMSG_WDATA + dma_offset,
		gaudi_irq_map_table[GAUDI_EVENT_DMA0_CORE].cpu_id + dma_id);
	WREG32(mmDMA0_CORE_PROT + dma_offset,
			1 << DMA0_CORE_PROT_ERR_VAL_SHIFT);
	/* If the channel is secured, it should be in MMU bypass mode */
	WREG32(mmDMA0_CORE_SECURE_PROPS + dma_offset,
			1 << DMA0_CORE_SECURE_PROPS_MMBP_SHIFT);
	WREG32(mmDMA0_CORE_CFG_0 + dma_offset, 1 << DMA0_CORE_CFG_0_EN_SHIFT);
पूर्ण

अटल व्योम gaudi_enable_qman(काष्ठा hl_device *hdev, पूर्णांक dma_id,
				u32 enable_mask)
अणु
	u32 dma_qm_offset = dma_id * DMA_QMAN_OFFSET;

	WREG32(mmDMA0_QM_GLBL_CFG0 + dma_qm_offset, enable_mask);
पूर्ण

अटल व्योम gaudi_init_pci_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा hl_hw_queue *q;
	पूर्णांक i, j, dma_id, cpu_skip, nic_skip, cq_id = 0, q_idx, msi_vec = 0;

	अगर (gaudi->hw_cap_initialized & HW_CAP_PCI_DMA)
		वापस;

	क्रम (i = 0 ; i < PCI_DMA_NUMBER_OF_CHNLS ; i++) अणु
		dma_id = gaudi_dma_assignment[i];
		/*
		 * For queues after the CPU Q need to add 1 to get the correct
		 * queue. In addition, need to add the CPU EQ and NIC IRQs in
		 * order to get the correct MSI रेजिस्टर.
		 */
		अगर (dma_id > 1) अणु
			cpu_skip = 1;
			nic_skip = NIC_NUMBER_OF_ENGINES;
		पूर्ण अन्यथा अणु
			cpu_skip = 0;
			nic_skip = 0;
		पूर्ण

		क्रम (j = 0 ; j < QMAN_STREAMS ; j++) अणु
			q_idx = 4 * dma_id + j + cpu_skip;
			q = &hdev->kernel_queues[q_idx];
			q->cq_id = cq_id++;
			q->msi_vec = nic_skip + cpu_skip + msi_vec++;
			gaudi_init_pci_dma_qman(hdev, dma_id, j,
						q->bus_address);
		पूर्ण

		gaudi_init_dma_core(hdev, dma_id);

		gaudi_enable_qman(hdev, dma_id, PCI_DMA_QMAN_ENABLE);
	पूर्ण

	gaudi->hw_cap_initialized |= HW_CAP_PCI_DMA;
पूर्ण

अटल व्योम gaudi_init_hbm_dma_qman(काष्ठा hl_device *hdev, पूर्णांक dma_id,
					पूर्णांक qman_id, u64 qman_base_addr)
अणु
	u32 mtr_base_en_lo, mtr_base_en_hi, mtr_base_ws_lo, mtr_base_ws_hi;
	u32 so_base_en_lo, so_base_en_hi, so_base_ws_lo, so_base_ws_hi;
	u32 q_off, dma_qm_offset;
	u32 dma_qm_err_cfg;

	dma_qm_offset = dma_id * DMA_QMAN_OFFSET;

	mtr_base_en_lo = lower_32_bits(CFG_BASE +
			mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_en_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	mtr_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);

	q_off = dma_qm_offset + qman_id * 4;

	अगर (qman_id < 4) अणु
		WREG32(mmDMA0_QM_PQ_BASE_LO_0 + q_off,
					lower_32_bits(qman_base_addr));
		WREG32(mmDMA0_QM_PQ_BASE_HI_0 + q_off,
					upper_32_bits(qman_base_addr));

		WREG32(mmDMA0_QM_PQ_SIZE_0 + q_off, ilog2(HBM_DMA_QMAN_LENGTH));
		WREG32(mmDMA0_QM_PQ_PI_0 + q_off, 0);
		WREG32(mmDMA0_QM_PQ_CI_0 + q_off, 0);

		WREG32(mmDMA0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_CPDMA_SIZE_OFFSET);
		WREG32(mmDMA0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_CPDMA_SRC_OFFSET);
		WREG32(mmDMA0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_CPDMA_DST_OFFSET);
	पूर्ण अन्यथा अणु
		WREG32(mmDMA0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_LDMA_SIZE_OFFSET);
		WREG32(mmDMA0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_SRC_OFFSET);
		WREG32(mmDMA0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_DST_OFFSET);

		/* Configure RAZWI IRQ */
		dma_qm_err_cfg = HBM_DMA_QMAN_GLBL_ERR_CFG_MSG_EN_MASK;
		अगर (hdev->stop_on_err) अणु
			dma_qm_err_cfg |=
				HBM_DMA_QMAN_GLBL_ERR_CFG_STOP_ON_ERR_EN_MASK;
		पूर्ण
		WREG32(mmDMA0_QM_GLBL_ERR_CFG + dma_qm_offset, dma_qm_err_cfg);

		WREG32(mmDMA0_QM_GLBL_ERR_ADDR_LO + dma_qm_offset,
			lower_32_bits(CFG_BASE +
					mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmDMA0_QM_GLBL_ERR_ADDR_HI + dma_qm_offset,
			upper_32_bits(CFG_BASE +
					mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmDMA0_QM_GLBL_ERR_WDATA + dma_qm_offset,
			gaudi_irq_map_table[GAUDI_EVENT_DMA0_QM].cpu_id +
									dma_id);

		WREG32(mmDMA0_QM_ARB_ERR_MSG_EN + dma_qm_offset,
				QM_ARB_ERR_MSG_EN_MASK);

		/* Increase ARB WDT to support streams architecture */
		WREG32(mmDMA0_QM_ARB_SLV_CHOISE_WDT + dma_qm_offset,
				GAUDI_ARB_WDT_TIMEOUT);

		WREG32(mmDMA0_QM_GLBL_CFG1 + dma_qm_offset, 0);
		WREG32(mmDMA0_QM_GLBL_PROT + dma_qm_offset,
				QMAN_INTERNAL_MAKE_TRUSTED);
	पूर्ण

	WREG32(mmDMA0_QM_CP_MSG_BASE0_ADDR_LO_0 + q_off, mtr_base_en_lo);
	WREG32(mmDMA0_QM_CP_MSG_BASE0_ADDR_HI_0 + q_off, mtr_base_en_hi);
	WREG32(mmDMA0_QM_CP_MSG_BASE1_ADDR_LO_0 + q_off, so_base_en_lo);
	WREG32(mmDMA0_QM_CP_MSG_BASE1_ADDR_HI_0 + q_off, so_base_en_hi);

	/* Configure DMA5 CP_MSG_BASE 2/3 क्रम sync stream collective */
	अगर (gaudi_dma_assignment[dma_id] == GAUDI_ENGINE_ID_DMA_5) अणु
		WREG32(mmDMA0_QM_CP_MSG_BASE2_ADDR_LO_0 + q_off,
				mtr_base_ws_lo);
		WREG32(mmDMA0_QM_CP_MSG_BASE2_ADDR_HI_0 + q_off,
				mtr_base_ws_hi);
		WREG32(mmDMA0_QM_CP_MSG_BASE3_ADDR_LO_0 + q_off,
				so_base_ws_lo);
		WREG32(mmDMA0_QM_CP_MSG_BASE3_ADDR_HI_0 + q_off,
				so_base_ws_hi);
	पूर्ण
पूर्ण

अटल व्योम gaudi_init_hbm_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;
	u64 qman_base_addr;
	पूर्णांक i, j, dma_id, पूर्णांकernal_q_index;

	अगर (gaudi->hw_cap_initialized & HW_CAP_HBM_DMA)
		वापस;

	क्रम (i = 0 ; i < HBM_DMA_NUMBER_OF_CHNLS ; i++) अणु
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_1 + i];

		क्रम (j = 0 ; j < QMAN_STREAMS ; j++) अणु
			 /*
			  * Add the CPU queue in order to get the correct queue
			  * number as all पूर्णांकernal queue are placed after it
			  */
			पूर्णांकernal_q_index = dma_id * QMAN_STREAMS + j + 1;

			q = &gaudi->पूर्णांकernal_qmans[पूर्णांकernal_q_index];
			qman_base_addr = (u64) q->pq_dma_addr;
			gaudi_init_hbm_dma_qman(hdev, dma_id, j,
						qman_base_addr);
		पूर्ण

		/* Initializing lower CP क्रम HBM DMA QMAN */
		gaudi_init_hbm_dma_qman(hdev, dma_id, 4, 0);

		gaudi_init_dma_core(hdev, dma_id);

		gaudi_enable_qman(hdev, dma_id, HBM_DMA_QMAN_ENABLE);
	पूर्ण

	gaudi->hw_cap_initialized |= HW_CAP_HBM_DMA;
पूर्ण

अटल व्योम gaudi_init_mme_qman(काष्ठा hl_device *hdev, u32 mme_offset,
					पूर्णांक qman_id, u64 qman_base_addr)
अणु
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 q_off, mme_id;
	u32 mme_qm_err_cfg;

	mtr_base_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);

	q_off = mme_offset + qman_id * 4;

	अगर (qman_id < 4) अणु
		WREG32(mmMME0_QM_PQ_BASE_LO_0 + q_off,
					lower_32_bits(qman_base_addr));
		WREG32(mmMME0_QM_PQ_BASE_HI_0 + q_off,
					upper_32_bits(qman_base_addr));

		WREG32(mmMME0_QM_PQ_SIZE_0 + q_off, ilog2(MME_QMAN_LENGTH));
		WREG32(mmMME0_QM_PQ_PI_0 + q_off, 0);
		WREG32(mmMME0_QM_PQ_CI_0 + q_off, 0);

		WREG32(mmMME0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_CPDMA_SIZE_OFFSET);
		WREG32(mmMME0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_CPDMA_SRC_OFFSET);
		WREG32(mmMME0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_CPDMA_DST_OFFSET);
	पूर्ण अन्यथा अणु
		WREG32(mmMME0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_LDMA_SIZE_OFFSET);
		WREG32(mmMME0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_SRC_OFFSET);
		WREG32(mmMME0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_DST_OFFSET);

		/* Configure RAZWI IRQ */
		mme_id = mme_offset /
				(mmMME1_QM_GLBL_CFG0 - mmMME0_QM_GLBL_CFG0);

		mme_qm_err_cfg = MME_QMAN_GLBL_ERR_CFG_MSG_EN_MASK;
		अगर (hdev->stop_on_err) अणु
			mme_qm_err_cfg |=
				MME_QMAN_GLBL_ERR_CFG_STOP_ON_ERR_EN_MASK;
		पूर्ण
		WREG32(mmMME0_QM_GLBL_ERR_CFG + mme_offset, mme_qm_err_cfg);
		WREG32(mmMME0_QM_GLBL_ERR_ADDR_LO + mme_offset,
			lower_32_bits(CFG_BASE +
					mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmMME0_QM_GLBL_ERR_ADDR_HI + mme_offset,
			upper_32_bits(CFG_BASE +
					mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmMME0_QM_GLBL_ERR_WDATA + mme_offset,
			gaudi_irq_map_table[GAUDI_EVENT_MME0_QM].cpu_id +
									mme_id);

		WREG32(mmMME0_QM_ARB_ERR_MSG_EN + mme_offset,
				QM_ARB_ERR_MSG_EN_MASK);

		/* Increase ARB WDT to support streams architecture */
		WREG32(mmMME0_QM_ARB_SLV_CHOISE_WDT + mme_offset,
				GAUDI_ARB_WDT_TIMEOUT);

		WREG32(mmMME0_QM_GLBL_CFG1 + mme_offset, 0);
		WREG32(mmMME0_QM_GLBL_PROT + mme_offset,
				QMAN_INTERNAL_MAKE_TRUSTED);
	पूर्ण

	WREG32(mmMME0_QM_CP_MSG_BASE0_ADDR_LO_0 + q_off, mtr_base_lo);
	WREG32(mmMME0_QM_CP_MSG_BASE0_ADDR_HI_0 + q_off, mtr_base_hi);
	WREG32(mmMME0_QM_CP_MSG_BASE1_ADDR_LO_0 + q_off, so_base_lo);
	WREG32(mmMME0_QM_CP_MSG_BASE1_ADDR_HI_0 + q_off, so_base_hi);
पूर्ण

अटल व्योम gaudi_init_mme_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;
	u64 qman_base_addr;
	u32 mme_offset;
	पूर्णांक i, पूर्णांकernal_q_index;

	अगर (gaudi->hw_cap_initialized & HW_CAP_MME)
		वापस;

	/*
	 * map GAUDI_QUEUE_ID_MME_0_X to the N_W_MME (mmMME2_QM_BASE)
	 * and GAUDI_QUEUE_ID_MME_1_X to the S_W_MME (mmMME0_QM_BASE)
	 */

	mme_offset = mmMME2_QM_GLBL_CFG0 - mmMME0_QM_GLBL_CFG0;

	क्रम (i = 0 ; i < MME_NUMBER_OF_QMANS ; i++) अणु
		पूर्णांकernal_q_index = GAUDI_QUEUE_ID_MME_0_0 + i;
		q = &gaudi->पूर्णांकernal_qmans[पूर्णांकernal_q_index];
		qman_base_addr = (u64) q->pq_dma_addr;
		gaudi_init_mme_qman(hdev, mme_offset, (i & 0x3),
					qman_base_addr);
		अगर (i == 3)
			mme_offset = 0;
	पूर्ण

	/* Initializing lower CP क्रम MME QMANs */
	mme_offset = mmMME2_QM_GLBL_CFG0 - mmMME0_QM_GLBL_CFG0;
	gaudi_init_mme_qman(hdev, mme_offset, 4, 0);
	gaudi_init_mme_qman(hdev, 0, 4, 0);

	WREG32(mmMME2_QM_GLBL_CFG0, QMAN_MME_ENABLE);
	WREG32(mmMME0_QM_GLBL_CFG0, QMAN_MME_ENABLE);

	gaudi->hw_cap_initialized |= HW_CAP_MME;
पूर्ण

अटल व्योम gaudi_init_tpc_qman(काष्ठा hl_device *hdev, u32 tpc_offset,
				पूर्णांक qman_id, u64 qman_base_addr)
अणु
	u32 mtr_base_en_lo, mtr_base_en_hi, mtr_base_ws_lo, mtr_base_ws_hi;
	u32 so_base_en_lo, so_base_en_hi, so_base_ws_lo, so_base_ws_hi;
	u32 q_off, tpc_id;
	u32 tpc_qm_err_cfg;

	mtr_base_en_lo = lower_32_bits(CFG_BASE +
			mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_en_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	mtr_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);

	q_off = tpc_offset + qman_id * 4;

	tpc_id = tpc_offset /
			(mmTPC1_QM_GLBL_CFG0 - mmTPC0_QM_GLBL_CFG0);

	अगर (qman_id < 4) अणु
		WREG32(mmTPC0_QM_PQ_BASE_LO_0 + q_off,
					lower_32_bits(qman_base_addr));
		WREG32(mmTPC0_QM_PQ_BASE_HI_0 + q_off,
					upper_32_bits(qman_base_addr));

		WREG32(mmTPC0_QM_PQ_SIZE_0 + q_off, ilog2(TPC_QMAN_LENGTH));
		WREG32(mmTPC0_QM_PQ_PI_0 + q_off, 0);
		WREG32(mmTPC0_QM_PQ_CI_0 + q_off, 0);

		WREG32(mmTPC0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_CPDMA_SIZE_OFFSET);
		WREG32(mmTPC0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_CPDMA_SRC_OFFSET);
		WREG32(mmTPC0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_CPDMA_DST_OFFSET);
	पूर्ण अन्यथा अणु
		WREG32(mmTPC0_QM_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_LDMA_SIZE_OFFSET);
		WREG32(mmTPC0_QM_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_SRC_OFFSET);
		WREG32(mmTPC0_QM_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_DST_OFFSET);

		/* Configure RAZWI IRQ */
		tpc_qm_err_cfg = TPC_QMAN_GLBL_ERR_CFG_MSG_EN_MASK;
		अगर (hdev->stop_on_err) अणु
			tpc_qm_err_cfg |=
				TPC_QMAN_GLBL_ERR_CFG_STOP_ON_ERR_EN_MASK;
		पूर्ण

		WREG32(mmTPC0_QM_GLBL_ERR_CFG + tpc_offset, tpc_qm_err_cfg);
		WREG32(mmTPC0_QM_GLBL_ERR_ADDR_LO + tpc_offset,
			lower_32_bits(CFG_BASE +
				mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmTPC0_QM_GLBL_ERR_ADDR_HI + tpc_offset,
			upper_32_bits(CFG_BASE +
				mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmTPC0_QM_GLBL_ERR_WDATA + tpc_offset,
			gaudi_irq_map_table[GAUDI_EVENT_TPC0_QM].cpu_id +
									tpc_id);

		WREG32(mmTPC0_QM_ARB_ERR_MSG_EN + tpc_offset,
				QM_ARB_ERR_MSG_EN_MASK);

		/* Increase ARB WDT to support streams architecture */
		WREG32(mmTPC0_QM_ARB_SLV_CHOISE_WDT + tpc_offset,
				GAUDI_ARB_WDT_TIMEOUT);

		WREG32(mmTPC0_QM_GLBL_CFG1 + tpc_offset, 0);
		WREG32(mmTPC0_QM_GLBL_PROT + tpc_offset,
				QMAN_INTERNAL_MAKE_TRUSTED);
	पूर्ण

	WREG32(mmTPC0_QM_CP_MSG_BASE0_ADDR_LO_0 + q_off, mtr_base_en_lo);
	WREG32(mmTPC0_QM_CP_MSG_BASE0_ADDR_HI_0 + q_off, mtr_base_en_hi);
	WREG32(mmTPC0_QM_CP_MSG_BASE1_ADDR_LO_0 + q_off, so_base_en_lo);
	WREG32(mmTPC0_QM_CP_MSG_BASE1_ADDR_HI_0 + q_off, so_base_en_hi);

	/* Configure TPC7 CP_MSG_BASE 2/3 क्रम sync stream collective */
	अगर (tpc_id == 6) अणु
		WREG32(mmTPC0_QM_CP_MSG_BASE2_ADDR_LO_0 + q_off,
				mtr_base_ws_lo);
		WREG32(mmTPC0_QM_CP_MSG_BASE2_ADDR_HI_0 + q_off,
				mtr_base_ws_hi);
		WREG32(mmTPC0_QM_CP_MSG_BASE3_ADDR_LO_0 + q_off,
				so_base_ws_lo);
		WREG32(mmTPC0_QM_CP_MSG_BASE3_ADDR_HI_0 + q_off,
				so_base_ws_hi);
	पूर्ण
पूर्ण

अटल व्योम gaudi_init_tpc_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;
	u64 qman_base_addr;
	u32 so_base_hi, tpc_offset = 0;
	u32 tpc_delta = mmTPC1_CFG_SM_BASE_ADDRESS_HIGH -
			mmTPC0_CFG_SM_BASE_ADDRESS_HIGH;
	पूर्णांक i, tpc_id, पूर्णांकernal_q_index;

	अगर (gaudi->hw_cap_initialized & HW_CAP_TPC_MASK)
		वापस;

	so_base_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);

	क्रम (tpc_id = 0 ; tpc_id < TPC_NUMBER_OF_ENGINES ; tpc_id++) अणु
		क्रम (i = 0 ; i < QMAN_STREAMS ; i++) अणु
			पूर्णांकernal_q_index = GAUDI_QUEUE_ID_TPC_0_0 +
						tpc_id * QMAN_STREAMS + i;
			q = &gaudi->पूर्णांकernal_qmans[पूर्णांकernal_q_index];
			qman_base_addr = (u64) q->pq_dma_addr;
			gaudi_init_tpc_qman(hdev, tpc_offset, i,
						qman_base_addr);

			अगर (i == 3) अणु
				/* Initializing lower CP क्रम TPC QMAN */
				gaudi_init_tpc_qman(hdev, tpc_offset, 4, 0);

				/* Enable the QMAN and TPC channel */
				WREG32(mmTPC0_QM_GLBL_CFG0 + tpc_offset,
						QMAN_TPC_ENABLE);
			पूर्ण
		पूर्ण

		WREG32(mmTPC0_CFG_SM_BASE_ADDRESS_HIGH + tpc_id * tpc_delta,
				so_base_hi);

		tpc_offset += mmTPC1_QM_GLBL_CFG0 - mmTPC0_QM_GLBL_CFG0;

		gaudi->hw_cap_initialized |=
				FIELD_PREP(HW_CAP_TPC_MASK, 1 << tpc_id);
	पूर्ण
पूर्ण

अटल व्योम gaudi_init_nic_qman(काष्ठा hl_device *hdev, u32 nic_offset,
				पूर्णांक qman_id, u64 qman_base_addr, पूर्णांक nic_id)
अणु
	u32 mtr_base_en_lo, mtr_base_en_hi, mtr_base_ws_lo, mtr_base_ws_hi;
	u32 so_base_en_lo, so_base_en_hi, so_base_ws_lo, so_base_ws_hi;
	u32 q_off;
	u32 nic_qm_err_cfg;

	mtr_base_en_lo = lower_32_bits(CFG_BASE +
			mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_en_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_en_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0);
	mtr_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	mtr_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0);
	so_base_ws_lo = lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);
	so_base_ws_hi = upper_32_bits(CFG_BASE +
				mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0);

	q_off = nic_offset + qman_id * 4;

	WREG32(mmNIC0_QM0_PQ_BASE_LO_0 + q_off, lower_32_bits(qman_base_addr));
	WREG32(mmNIC0_QM0_PQ_BASE_HI_0 + q_off, upper_32_bits(qman_base_addr));

	WREG32(mmNIC0_QM0_PQ_SIZE_0 + q_off, ilog2(NIC_QMAN_LENGTH));
	WREG32(mmNIC0_QM0_PQ_PI_0 + q_off, 0);
	WREG32(mmNIC0_QM0_PQ_CI_0 + q_off, 0);

	WREG32(mmNIC0_QM0_CP_LDMA_TSIZE_OFFSET_0 + q_off,
							QMAN_LDMA_SIZE_OFFSET);
	WREG32(mmNIC0_QM0_CP_LDMA_SRC_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_SRC_OFFSET);
	WREG32(mmNIC0_QM0_CP_LDMA_DST_BASE_LO_OFFSET_0 + q_off,
							QMAN_LDMA_DST_OFFSET);

	WREG32(mmNIC0_QM0_CP_MSG_BASE0_ADDR_LO_0 + q_off, mtr_base_en_lo);
	WREG32(mmNIC0_QM0_CP_MSG_BASE0_ADDR_HI_0 + q_off, mtr_base_en_hi);
	WREG32(mmNIC0_QM0_CP_MSG_BASE1_ADDR_LO_0 + q_off, so_base_en_lo);
	WREG32(mmNIC0_QM0_CP_MSG_BASE1_ADDR_HI_0 + q_off, so_base_en_hi);

	/* Configure NIC CP_MSG_BASE 2/3 क्रम sync stream collective */
	WREG32(mmNIC0_QM0_CP_MSG_BASE2_ADDR_LO_0 + q_off, mtr_base_ws_lo);
	WREG32(mmNIC0_QM0_CP_MSG_BASE2_ADDR_HI_0 + q_off, mtr_base_ws_hi);
	WREG32(mmNIC0_QM0_CP_MSG_BASE3_ADDR_LO_0 + q_off, so_base_ws_lo);
	WREG32(mmNIC0_QM0_CP_MSG_BASE3_ADDR_HI_0 + q_off, so_base_ws_hi);

	अगर (qman_id == 0) अणु
		/* Configure RAZWI IRQ */
		nic_qm_err_cfg = NIC_QMAN_GLBL_ERR_CFG_MSG_EN_MASK;
		अगर (hdev->stop_on_err) अणु
			nic_qm_err_cfg |=
				NIC_QMAN_GLBL_ERR_CFG_STOP_ON_ERR_EN_MASK;
		पूर्ण

		WREG32(mmNIC0_QM0_GLBL_ERR_CFG + nic_offset, nic_qm_err_cfg);
		WREG32(mmNIC0_QM0_GLBL_ERR_ADDR_LO + nic_offset,
			lower_32_bits(CFG_BASE +
				mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmNIC0_QM0_GLBL_ERR_ADDR_HI + nic_offset,
			upper_32_bits(CFG_BASE +
				mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR));
		WREG32(mmNIC0_QM0_GLBL_ERR_WDATA + nic_offset,
			gaudi_irq_map_table[GAUDI_EVENT_NIC0_QM0].cpu_id +
									nic_id);

		WREG32(mmNIC0_QM0_ARB_ERR_MSG_EN + nic_offset,
				QM_ARB_ERR_MSG_EN_MASK);

		/* Increase ARB WDT to support streams architecture */
		WREG32(mmNIC0_QM0_ARB_SLV_CHOISE_WDT + nic_offset,
				GAUDI_ARB_WDT_TIMEOUT);

		WREG32(mmNIC0_QM0_GLBL_CFG1 + nic_offset, 0);
		WREG32(mmNIC0_QM0_GLBL_PROT + nic_offset,
				QMAN_INTERNAL_MAKE_TRUSTED);
	पूर्ण
पूर्ण

अटल व्योम gaudi_init_nic_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;
	u64 qman_base_addr;
	u32 nic_offset = 0;
	u32 nic_delta_between_qmans =
			mmNIC0_QM1_GLBL_CFG0 - mmNIC0_QM0_GLBL_CFG0;
	u32 nic_delta_between_nics =
			mmNIC1_QM0_GLBL_CFG0 - mmNIC0_QM0_GLBL_CFG0;
	पूर्णांक i, nic_id, पूर्णांकernal_q_index;

	अगर (!hdev->nic_ports_mask)
		वापस;

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC_MASK)
		वापस;

	dev_dbg(hdev->dev, "Initializing NIC QMANs\n");

	क्रम (nic_id = 0 ; nic_id < NIC_NUMBER_OF_ENGINES ; nic_id++) अणु
		अगर (!(hdev->nic_ports_mask & (1 << nic_id))) अणु
			nic_offset += nic_delta_between_qmans;
			अगर (nic_id & 1) अणु
				nic_offset -= (nic_delta_between_qmans * 2);
				nic_offset += nic_delta_between_nics;
			पूर्ण
			जारी;
		पूर्ण

		क्रम (i = 0 ; i < QMAN_STREAMS ; i++) अणु
			पूर्णांकernal_q_index = GAUDI_QUEUE_ID_NIC_0_0 +
						nic_id * QMAN_STREAMS + i;
			q = &gaudi->पूर्णांकernal_qmans[पूर्णांकernal_q_index];
			qman_base_addr = (u64) q->pq_dma_addr;
			gaudi_init_nic_qman(hdev, nic_offset, (i & 0x3),
						qman_base_addr, nic_id);
		पूर्ण

		/* Enable the QMAN */
		WREG32(mmNIC0_QM0_GLBL_CFG0 + nic_offset, NIC_QMAN_ENABLE);

		nic_offset += nic_delta_between_qmans;
		अगर (nic_id & 1) अणु
			nic_offset -= (nic_delta_between_qmans * 2);
			nic_offset += nic_delta_between_nics;
		पूर्ण

		gaudi->hw_cap_initialized |= 1 << (HW_CAP_NIC_SHIFT + nic_id);
	पूर्ण
पूर्ण

अटल व्योम gaudi_disable_pci_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_PCI_DMA))
		वापस;

	WREG32(mmDMA0_QM_GLBL_CFG0, 0);
	WREG32(mmDMA1_QM_GLBL_CFG0, 0);
	WREG32(mmDMA5_QM_GLBL_CFG0, 0);
पूर्ण

अटल व्योम gaudi_disable_hbm_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_HBM_DMA))
		वापस;

	WREG32(mmDMA2_QM_GLBL_CFG0, 0);
	WREG32(mmDMA3_QM_GLBL_CFG0, 0);
	WREG32(mmDMA4_QM_GLBL_CFG0, 0);
	WREG32(mmDMA6_QM_GLBL_CFG0, 0);
	WREG32(mmDMA7_QM_GLBL_CFG0, 0);
पूर्ण

अटल व्योम gaudi_disable_mme_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MME))
		वापस;

	WREG32(mmMME2_QM_GLBL_CFG0, 0);
	WREG32(mmMME0_QM_GLBL_CFG0, 0);
पूर्ण

अटल व्योम gaudi_disable_tpc_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 tpc_offset = 0;
	पूर्णांक tpc_id;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_TPC_MASK))
		वापस;

	क्रम (tpc_id = 0 ; tpc_id < TPC_NUMBER_OF_ENGINES ; tpc_id++) अणु
		WREG32(mmTPC0_QM_GLBL_CFG0 + tpc_offset, 0);
		tpc_offset += mmTPC1_QM_GLBL_CFG0 - mmTPC0_QM_GLBL_CFG0;
	पूर्ण
पूर्ण

अटल व्योम gaudi_disable_nic_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 nic_mask, nic_offset = 0;
	u32 nic_delta_between_qmans =
			mmNIC0_QM1_GLBL_CFG0 - mmNIC0_QM0_GLBL_CFG0;
	u32 nic_delta_between_nics =
			mmNIC1_QM0_GLBL_CFG0 - mmNIC0_QM0_GLBL_CFG0;
	पूर्णांक nic_id;

	क्रम (nic_id = 0 ; nic_id < NIC_NUMBER_OF_ENGINES ; nic_id++) अणु
		nic_mask = 1 << (HW_CAP_NIC_SHIFT + nic_id);

		अगर (gaudi->hw_cap_initialized & nic_mask)
			WREG32(mmNIC0_QM0_GLBL_CFG0 + nic_offset, 0);

		nic_offset += nic_delta_between_qmans;
		अगर (nic_id & 1) अणु
			nic_offset -= (nic_delta_between_qmans * 2);
			nic_offset += nic_delta_between_nics;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gaudi_stop_pci_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_PCI_DMA))
		वापस;

	/* Stop upper CPs of QMANs 0.0 to 1.3 and 5.0 to 5.3 */
	WREG32(mmDMA0_QM_GLBL_CFG1, 0xF << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmDMA1_QM_GLBL_CFG1, 0xF << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmDMA5_QM_GLBL_CFG1, 0xF << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
पूर्ण

अटल व्योम gaudi_stop_hbm_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_HBM_DMA))
		वापस;

	/* Stop CPs of HBM DMA QMANs */

	WREG32(mmDMA2_QM_GLBL_CFG1, 0x1F << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmDMA3_QM_GLBL_CFG1, 0x1F << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmDMA4_QM_GLBL_CFG1, 0x1F << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmDMA6_QM_GLBL_CFG1, 0x1F << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmDMA7_QM_GLBL_CFG1, 0x1F << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);
पूर्ण

अटल व्योम gaudi_stop_mme_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MME))
		वापस;

	/* Stop CPs of MME QMANs */
	WREG32(mmMME2_QM_GLBL_CFG1, 0x1F << MME0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmMME0_QM_GLBL_CFG1, 0x1F << MME0_QM_GLBL_CFG1_CP_STOP_SHIFT);
पूर्ण

अटल व्योम gaudi_stop_tpc_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_TPC_MASK))
		वापस;

	WREG32(mmTPC0_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC1_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC2_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC3_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC4_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC5_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC6_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
	WREG32(mmTPC7_QM_GLBL_CFG1, 0x1F << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);
पूर्ण

अटल व्योम gaudi_stop_nic_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	/* Stop upper CPs of QMANs */

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC0)
		WREG32(mmNIC0_QM0_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC1)
		WREG32(mmNIC0_QM1_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC2)
		WREG32(mmNIC1_QM0_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC3)
		WREG32(mmNIC1_QM1_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC4)
		WREG32(mmNIC2_QM0_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC5)
		WREG32(mmNIC2_QM1_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC6)
		WREG32(mmNIC3_QM0_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC7)
		WREG32(mmNIC3_QM1_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC8)
		WREG32(mmNIC4_QM0_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);

	अगर (gaudi->hw_cap_initialized & HW_CAP_NIC9)
		WREG32(mmNIC4_QM1_GLBL_CFG1,
				NIC0_QM0_GLBL_CFG1_PQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CQF_STOP_MASK |
				NIC0_QM0_GLBL_CFG1_CP_STOP_MASK);
पूर्ण

अटल व्योम gaudi_pci_dma_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_PCI_DMA))
		वापस;

	WREG32(mmDMA0_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
	WREG32(mmDMA1_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
	WREG32(mmDMA5_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
पूर्ण

अटल व्योम gaudi_hbm_dma_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_HBM_DMA))
		वापस;

	WREG32(mmDMA2_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
	WREG32(mmDMA3_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
	WREG32(mmDMA4_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
	WREG32(mmDMA6_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
	WREG32(mmDMA7_CORE_CFG_1, 1 << DMA0_CORE_CFG_1_HALT_SHIFT);
पूर्ण

अटल व्योम gaudi_mme_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MME))
		वापस;

	/* WA क्रम H3-1800 bug: करो ACC and SBAB ग_लिखोs twice */
	WREG32(mmMME0_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME0_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME0_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME0_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME1_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME1_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME1_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME1_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME2_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME2_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME2_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME2_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME3_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME3_ACC_ACC_STALL, 1 << MME_ACC_ACC_STALL_R_SHIFT);
	WREG32(mmMME3_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
	WREG32(mmMME3_SBAB_SB_STALL, 1 << MME_SBAB_SB_STALL_R_SHIFT);
पूर्ण

अटल व्योम gaudi_tpc_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_TPC_MASK))
		वापस;

	WREG32(mmTPC0_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC1_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC2_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC3_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC4_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC5_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC6_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC7_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
पूर्ण

अटल व्योम gaudi_set_घड़ी_gating(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 qman_offset;
	bool enable;
	पूर्णांक i;

	/* In हाल we are during debug session, करोn't enable the घड़ी gate
	 * as it may पूर्णांकerfere
	 */
	अगर (hdev->in_debug)
		वापस;

	अगर (!hdev->asic_prop.fw_security_disabled)
		वापस;

	क्रम (i = GAUDI_PCI_DMA_1, qman_offset = 0 ; i < GAUDI_HBM_DMA_1 ; i++) अणु
		enable = !!(hdev->घड़ी_gating_mask &
				(BIT_ULL(gaudi_dma_assignment[i])));

		qman_offset = gaudi_dma_assignment[i] * DMA_QMAN_OFFSET;
		WREG32(mmDMA0_QM_CGM_CFG1 + qman_offset,
				enable ? QMAN_CGM1_PWR_GATE_EN : 0);
		WREG32(mmDMA0_QM_CGM_CFG + qman_offset,
				enable ? QMAN_UPPER_CP_CGM_PWR_GATE_EN : 0);
	पूर्ण

	क्रम (i = GAUDI_HBM_DMA_1 ; i < GAUDI_DMA_MAX ; i++) अणु
		enable = !!(hdev->घड़ी_gating_mask &
				(BIT_ULL(gaudi_dma_assignment[i])));

		/* GC sends work to DMA engine through Upper CP in DMA5 so
		 * we need to not enable घड़ी gating in that DMA
		 */
		अगर (i == GAUDI_HBM_DMA_4)
			enable = 0;

		qman_offset = gaudi_dma_assignment[i] * DMA_QMAN_OFFSET;
		WREG32(mmDMA0_QM_CGM_CFG1 + qman_offset,
				enable ? QMAN_CGM1_PWR_GATE_EN : 0);
		WREG32(mmDMA0_QM_CGM_CFG + qman_offset,
				enable ? QMAN_COMMON_CP_CGM_PWR_GATE_EN : 0);
	पूर्ण

	enable = !!(hdev->घड़ी_gating_mask & (BIT_ULL(GAUDI_ENGINE_ID_MME_0)));
	WREG32(mmMME0_QM_CGM_CFG1, enable ? QMAN_CGM1_PWR_GATE_EN : 0);
	WREG32(mmMME0_QM_CGM_CFG, enable ? QMAN_COMMON_CP_CGM_PWR_GATE_EN : 0);

	enable = !!(hdev->घड़ी_gating_mask & (BIT_ULL(GAUDI_ENGINE_ID_MME_2)));
	WREG32(mmMME2_QM_CGM_CFG1, enable ? QMAN_CGM1_PWR_GATE_EN : 0);
	WREG32(mmMME2_QM_CGM_CFG, enable ? QMAN_COMMON_CP_CGM_PWR_GATE_EN : 0);

	क्रम (i = 0, qman_offset = 0 ; i < TPC_NUMBER_OF_ENGINES ; i++) अणु
		enable = !!(hdev->घड़ी_gating_mask &
				(BIT_ULL(GAUDI_ENGINE_ID_TPC_0 + i)));

		WREG32(mmTPC0_QM_CGM_CFG1 + qman_offset,
				enable ? QMAN_CGM1_PWR_GATE_EN : 0);
		WREG32(mmTPC0_QM_CGM_CFG + qman_offset,
				enable ? QMAN_COMMON_CP_CGM_PWR_GATE_EN : 0);

		qman_offset += TPC_QMAN_OFFSET;
	पूर्ण

	gaudi->hw_cap_initialized |= HW_CAP_CLK_GATE;
पूर्ण

अटल व्योम gaudi_disable_घड़ी_gating(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 qman_offset;
	पूर्णांक i;

	अगर (!hdev->asic_prop.fw_security_disabled)
		वापस;

	क्रम (i = 0, qman_offset = 0 ; i < DMA_NUMBER_OF_CHANNELS ; i++) अणु
		WREG32(mmDMA0_QM_CGM_CFG + qman_offset, 0);
		WREG32(mmDMA0_QM_CGM_CFG1 + qman_offset, 0);

		qman_offset += (mmDMA1_QM_CGM_CFG - mmDMA0_QM_CGM_CFG);
	पूर्ण

	WREG32(mmMME0_QM_CGM_CFG, 0);
	WREG32(mmMME0_QM_CGM_CFG1, 0);
	WREG32(mmMME2_QM_CGM_CFG, 0);
	WREG32(mmMME2_QM_CGM_CFG1, 0);

	क्रम (i = 0, qman_offset = 0 ; i < TPC_NUMBER_OF_ENGINES ; i++) अणु
		WREG32(mmTPC0_QM_CGM_CFG + qman_offset, 0);
		WREG32(mmTPC0_QM_CGM_CFG1 + qman_offset, 0);

		qman_offset += (mmTPC1_QM_CGM_CFG - mmTPC0_QM_CGM_CFG);
	पूर्ण

	gaudi->hw_cap_initialized &= ~(HW_CAP_CLK_GATE);
पूर्ण

अटल व्योम gaudi_enable_बारtamp(काष्ठा hl_device *hdev)
अणु
	/* Disable the बारtamp counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 0);

	/* Zero the lower/upper parts of the 64-bit counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE + 0xC, 0);
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE + 0x8, 0);

	/* Enable the counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 1);
पूर्ण

अटल व्योम gaudi_disable_बारtamp(काष्ठा hl_device *hdev)
अणु
	/* Disable the बारtamp counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 0);
पूर्ण

अटल व्योम gaudi_halt_engines(काष्ठा hl_device *hdev, bool hard_reset)
अणु
	u32 रुको_समयout_ms;

	dev_info(hdev->dev,
		"Halting compute engines and disabling interrupts\n");

	अगर (hdev->pldm)
		रुको_समयout_ms = GAUDI_PLDM_RESET_WAIT_MSEC;
	अन्यथा
		रुको_समयout_ms = GAUDI_RESET_WAIT_MSEC;

	gaudi_stop_nic_qmans(hdev);
	gaudi_stop_mme_qmans(hdev);
	gaudi_stop_tpc_qmans(hdev);
	gaudi_stop_hbm_dma_qmans(hdev);
	gaudi_stop_pci_dma_qmans(hdev);

	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	msleep(रुको_समयout_ms);

	gaudi_pci_dma_stall(hdev);
	gaudi_hbm_dma_stall(hdev);
	gaudi_tpc_stall(hdev);
	gaudi_mme_stall(hdev);

	msleep(रुको_समयout_ms);

	gaudi_disable_nic_qmans(hdev);
	gaudi_disable_mme_qmans(hdev);
	gaudi_disable_tpc_qmans(hdev);
	gaudi_disable_hbm_dma_qmans(hdev);
	gaudi_disable_pci_dma_qmans(hdev);

	gaudi_disable_बारtamp(hdev);

	gaudi_disable_msi(hdev);
पूर्ण

अटल पूर्णांक gaudi_mmu_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 hop0_addr;
	पूर्णांक rc, i;

	अगर (!hdev->mmu_enable)
		वापस 0;

	अगर (gaudi->hw_cap_initialized & HW_CAP_MMU)
		वापस 0;

	क्रम (i = 0 ; i < prop->max_asid ; i++) अणु
		hop0_addr = prop->mmu_pgt_addr +
				(i * prop->mmu_hop_table_size);

		rc = gaudi_mmu_update_asid_hop0_addr(hdev, i, hop0_addr);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed to set hop0 addr for asid %d\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	/* init MMU cache manage page */
	WREG32(mmSTLB_CACHE_INV_BASE_39_8, MMU_CACHE_MNG_ADDR >> 8);
	WREG32(mmSTLB_CACHE_INV_BASE_49_40, MMU_CACHE_MNG_ADDR >> 40);

	hdev->asic_funcs->mmu_invalidate_cache(hdev, true, 0);

	WREG32(mmMMU_UP_MMU_ENABLE, 1);
	WREG32(mmMMU_UP_SPI_MASK, 0xF);

	WREG32(mmSTLB_HOP_CONFIGURATION,
			hdev->mmu_huge_page_opt ? 0x30440 : 0x40440);

	/*
	 * The H/W expects the first PI after init to be 1. After wraparound
	 * we'll ग_लिखो 0.
	 */
	gaudi->mmu_cache_inv_pi = 1;

	gaudi->hw_cap_initialized |= HW_CAP_MMU;

	वापस 0;

err:
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_load_firmware_to_device(काष्ठा hl_device *hdev)
अणु
	व्योम __iomem *dst;

	/* HBM scrambler must be initialized beक्रमe pushing F/W to HBM */
	gaudi_init_scrambler_hbm(hdev);

	dst = hdev->pcie_bar[HBM_BAR_ID] + LINUX_FW_OFFSET;

	वापस hl_fw_load_fw_to_device(hdev, GAUDI_LINUX_FW_खाता, dst, 0, 0);
पूर्ण

अटल पूर्णांक gaudi_load_boot_fit_to_device(काष्ठा hl_device *hdev)
अणु
	व्योम __iomem *dst;

	dst = hdev->pcie_bar[SRAM_BAR_ID] + BOOT_FIT_SRAM_OFFSET;

	वापस hl_fw_load_fw_to_device(hdev, GAUDI_BOOT_FIT_खाता, dst, 0, 0);
पूर्ण

अटल पूर्णांक gaudi_पढ़ो_device_fw_version(काष्ठा hl_device *hdev,
					क्रमागत hl_fw_component fwc)
अणु
	स्थिर अक्षर *name;
	u32 ver_off;
	अक्षर *dest;

	चयन (fwc) अणु
	हाल FW_COMP_UBOOT:
		ver_off = RREG32(mmUBOOT_VER_OFFSET);
		dest = hdev->asic_prop.uboot_ver;
		name = "U-Boot";
		अवरोध;
	हाल FW_COMP_PREBOOT:
		ver_off = RREG32(mmPREBOOT_VER_OFFSET);
		dest = hdev->asic_prop.preboot_ver;
		name = "Preboot";
		अवरोध;
	शेष:
		dev_warn(hdev->dev, "Undefined FW component: %d\n", fwc);
		वापस -EIO;
	पूर्ण

	ver_off &= ~((u32)SRAM_BASE_ADDR);

	अगर (ver_off < SRAM_SIZE - VERSION_MAX_LEN) अणु
		स_नकल_fromio(dest, hdev->pcie_bar[SRAM_BAR_ID] + ver_off,
							VERSION_MAX_LEN);
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev, "%s version offset (0x%x) is above SRAM\n",
								name, ver_off);
		म_नकल(dest, "unavailable");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_init_cpu(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक rc;

	अगर (!(hdev->fw_components & FW_TYPE_PREBOOT_CPU))
		वापस 0;

	अगर (gaudi->hw_cap_initialized & HW_CAP_CPU)
		वापस 0;

	/*
	 * The device CPU works with 40 bits addresses.
	 * This रेजिस्टर sets the extension to 50 bits.
	 */
	अगर (hdev->asic_prop.fw_security_disabled)
		WREG32(mmCPU_IF_CPU_MSB_ADDR, hdev->cpu_pci_msb_addr);

	rc = hl_fw_init_cpu(hdev, mmPSOC_GLOBAL_CONF_CPU_BOOT_STATUS,
			mmPSOC_GLOBAL_CONF_KMD_MSG_TO_CPU,
			mmCPU_CMD_STATUS_TO_HOST,
			mmCPU_BOOT_DEV_STS0, mmCPU_BOOT_ERR0,
			!hdev->bmc_enable, GAUDI_CPU_TIMEOUT_USEC,
			GAUDI_BOOT_FIT_REQ_TIMEOUT_USEC);

	अगर (rc)
		वापस rc;

	gaudi->hw_cap_initialized |= HW_CAP_CPU;

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_init_cpu_queues(काष्ठा hl_device *hdev, u32 cpu_समयout)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_eq *eq;
	u32 status;
	काष्ठा hl_hw_queue *cpu_pq =
			&hdev->kernel_queues[GAUDI_QUEUE_ID_CPU_PQ];
	पूर्णांक err;

	अगर (!hdev->cpu_queues_enable)
		वापस 0;

	अगर (gaudi->hw_cap_initialized & HW_CAP_CPU_Q)
		वापस 0;

	eq = &hdev->event_queue;

	WREG32(mmCPU_IF_PQ_BASE_ADDR_LOW, lower_32_bits(cpu_pq->bus_address));
	WREG32(mmCPU_IF_PQ_BASE_ADDR_HIGH, upper_32_bits(cpu_pq->bus_address));

	WREG32(mmCPU_IF_EQ_BASE_ADDR_LOW, lower_32_bits(eq->bus_address));
	WREG32(mmCPU_IF_EQ_BASE_ADDR_HIGH, upper_32_bits(eq->bus_address));

	WREG32(mmCPU_IF_CQ_BASE_ADDR_LOW,
			lower_32_bits(hdev->cpu_accessible_dma_address));
	WREG32(mmCPU_IF_CQ_BASE_ADDR_HIGH,
			upper_32_bits(hdev->cpu_accessible_dma_address));

	WREG32(mmCPU_IF_PQ_LENGTH, HL_QUEUE_SIZE_IN_BYTES);
	WREG32(mmCPU_IF_EQ_LENGTH, HL_EQ_SIZE_IN_BYTES);
	WREG32(mmCPU_IF_CQ_LENGTH, HL_CPU_ACCESSIBLE_MEM_SIZE);

	/* Used क्रम EQ CI */
	WREG32(mmCPU_IF_EQ_RD_OFFS, 0);

	WREG32(mmCPU_IF_PF_PQ_PI, 0);

	अगर (gaudi->multi_msi_mode)
		WREG32(mmCPU_IF_QUEUE_INIT, PQ_INIT_STATUS_READY_FOR_CP);
	अन्यथा
		WREG32(mmCPU_IF_QUEUE_INIT,
			PQ_INIT_STATUS_READY_FOR_CP_SINGLE_MSI);

	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR, GAUDI_EVENT_PI_UPDATE);

	err = hl_poll_समयout(
		hdev,
		mmCPU_IF_QUEUE_INIT,
		status,
		(status == PQ_INIT_STATUS_READY_FOR_HOST),
		1000,
		cpu_समयout);

	अगर (err) अणु
		dev_err(hdev->dev,
			"Failed to communicate with Device CPU (CPU-CP timeout)\n");
		वापस -EIO;
	पूर्ण

	/* update FW application security bits */
	अगर (prop->fw_security_status_valid)
		prop->fw_app_security_map = RREG32(mmCPU_BOOT_DEV_STS0);

	gaudi->hw_cap_initialized |= HW_CAP_CPU_Q;
	वापस 0;
पूर्ण

अटल व्योम gaudi_pre_hw_init(काष्ठा hl_device *hdev)
अणु
	/* Perक्रमm पढ़ो from the device to make sure device is up */
	RREG32(mmHW_STATE);

	अगर (hdev->asic_prop.fw_security_disabled) अणु
		/* Set the access through PCI bars (Linux driver only) as
		 * secured
		 */
		WREG32(mmPCIE_WRAP_LBW_PROT_OVR,
				(PCIE_WRAP_LBW_PROT_OVR_RD_EN_MASK |
				PCIE_WRAP_LBW_PROT_OVR_WR_EN_MASK));

		/* Perक्रमm पढ़ो to flush the रुकोing ग_लिखोs to ensure
		 * configuration was set in the device
		 */
		RREG32(mmPCIE_WRAP_LBW_PROT_OVR);
	पूर्ण

	/*
	 * Let's mark in the H/W that we have reached this poपूर्णांक. We check
	 * this value in the reset_beक्रमe_init function to understand whether
	 * we need to reset the chip beक्रमe करोing H/W init. This रेजिस्टर is
	 * cleared by the H/W upon H/W reset
	 */
	WREG32(mmHW_STATE, HL_DEVICE_HW_STATE_सूचीTY);
पूर्ण

अटल पूर्णांक gaudi_hw_init(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	gaudi_pre_hw_init(hdev);

	gaudi_init_pci_dma_qmans(hdev);

	gaudi_init_hbm_dma_qmans(hdev);

	rc = gaudi_init_cpu(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize CPU\n");
		वापस rc;
	पूर्ण

	/* In हाल the घड़ी gating was enabled in preboot we need to disable
	 * it here beक्रमe touching the MME/TPC रेजिस्टरs.
	 * There is no need to take clk gating mutex because when this function
	 * runs, no other relevant code can run
	 */
	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	/* SRAM scrambler must be initialized after CPU is running from HBM */
	gaudi_init_scrambler_sram(hdev);

	/* This is here just in हाल we are working without CPU */
	gaudi_init_scrambler_hbm(hdev);

	gaudi_init_golden_रेजिस्टरs(hdev);

	rc = gaudi_mmu_init(hdev);
	अगर (rc)
		वापस rc;

	gaudi_init_security(hdev);

	gaudi_init_mme_qmans(hdev);

	gaudi_init_tpc_qmans(hdev);

	gaudi_init_nic_qmans(hdev);

	hdev->asic_funcs->set_घड़ी_gating(hdev);

	gaudi_enable_बारtamp(hdev);

	/* MSI must be enabled beक्रमe CPU queues and NIC are initialized */
	rc = gaudi_enable_msi(hdev);
	अगर (rc)
		जाओ disable_queues;

	/* must be called after MSI was enabled */
	rc = gaudi_init_cpu_queues(hdev, GAUDI_CPU_TIMEOUT_USEC);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize CPU H/W queues %d\n",
			rc);
		जाओ disable_msi;
	पूर्ण

	/* Perक्रमm पढ़ो from the device to flush all configuration */
	RREG32(mmHW_STATE);

	वापस 0;

disable_msi:
	gaudi_disable_msi(hdev);
disable_queues:
	gaudi_disable_mme_qmans(hdev);
	gaudi_disable_pci_dma_qmans(hdev);

	वापस rc;
पूर्ण

अटल व्योम gaudi_hw_fini(काष्ठा hl_device *hdev, bool hard_reset)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 status, reset_समयout_ms, cpu_समयout_ms;

	अगर (!hard_reset) अणु
		dev_err(hdev->dev, "GAUDI doesn't support soft-reset\n");
		वापस;
	पूर्ण

	अगर (hdev->pldm) अणु
		reset_समयout_ms = GAUDI_PLDM_HRESET_TIMEOUT_MSEC;
		cpu_समयout_ms = GAUDI_PLDM_RESET_WAIT_MSEC;
	पूर्ण अन्यथा अणु
		reset_समयout_ms = GAUDI_RESET_TIMEOUT_MSEC;
		cpu_समयout_ms = GAUDI_CPU_RESET_WAIT_MSEC;
	पूर्ण

	/* Set device to handle FLR by H/W as we will put the device CPU to
	 * halt mode
	 */
	अगर (hdev->asic_prop.fw_security_disabled &&
				!hdev->asic_prop.hard_reset_करोne_by_fw)
		WREG32(mmPCIE_AUX_FLR_CTRL, (PCIE_AUX_FLR_CTRL_HW_CTRL_MASK |
					PCIE_AUX_FLR_CTRL_INT_MASK_MASK));

	/* I करोn't know what is the state of the CPU so make sure it is
	 * stopped in any means necessary
	 */
	अगर (hdev->asic_prop.hard_reset_करोne_by_fw)
		WREG32(mmPSOC_GLOBAL_CONF_KMD_MSG_TO_CPU, KMD_MSG_RST_DEV);
	अन्यथा
		WREG32(mmPSOC_GLOBAL_CONF_KMD_MSG_TO_CPU, KMD_MSG_GOTO_WFE);

	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR, GAUDI_EVENT_HALT_MACHINE);

	अगर (hdev->asic_prop.fw_security_disabled &&
				!hdev->asic_prop.hard_reset_करोne_by_fw) अणु

		/* Configure the reset रेजिस्टरs. Must be करोne as early as
		 * possible in हाल we fail during H/W initialization
		 */
		WREG32(mmPSOC_GLOBAL_CONF_SOFT_RST_CFG_H,
						(CFG_RST_H_DMA_MASK |
						CFG_RST_H_MME_MASK |
						CFG_RST_H_SM_MASK |
						CFG_RST_H_TPC_7_MASK));

		WREG32(mmPSOC_GLOBAL_CONF_SOFT_RST_CFG_L, CFG_RST_L_TPC_MASK);

		WREG32(mmPSOC_GLOBAL_CONF_SW_ALL_RST_CFG_H,
						(CFG_RST_H_HBM_MASK |
						CFG_RST_H_TPC_7_MASK |
						CFG_RST_H_NIC_MASK |
						CFG_RST_H_SM_MASK |
						CFG_RST_H_DMA_MASK |
						CFG_RST_H_MME_MASK |
						CFG_RST_H_CPU_MASK |
						CFG_RST_H_MMU_MASK));

		WREG32(mmPSOC_GLOBAL_CONF_SW_ALL_RST_CFG_L,
						(CFG_RST_L_IF_MASK |
						CFG_RST_L_PSOC_MASK |
						CFG_RST_L_TPC_MASK));

		msleep(cpu_समयout_ms);

		/* Tell ASIC not to re-initialize PCIe */
		WREG32(mmPREBOOT_PCIE_EN, LKD_HARD_RESET_MAGIC);

		/* Restart BTL/BLR upon hard-reset */
		अगर (hdev->asic_prop.fw_security_disabled)
			WREG32(mmPSOC_GLOBAL_CONF_BOOT_SEQ_RE_START, 1);

		WREG32(mmPSOC_GLOBAL_CONF_SW_ALL_RST,
			1 << PSOC_GLOBAL_CONF_SW_ALL_RST_IND_SHIFT);

		dev_info(hdev->dev,
			"Issued HARD reset command, going to wait %dms\n",
			reset_समयout_ms);
	पूर्ण अन्यथा अणु
		dev_info(hdev->dev,
			"Firmware performs HARD reset, going to wait %dms\n",
			reset_समयout_ms);
	पूर्ण

	/*
	 * After hard reset, we can't poll the BTM_FSM रेजिस्टर because the PSOC
	 * itself is in reset. Need to रुको until the reset is deनिश्चितed
	 */
	msleep(reset_समयout_ms);

	status = RREG32(mmPSOC_GLOBAL_CONF_BTM_FSM);
	अगर (status & PSOC_GLOBAL_CONF_BTM_FSM_STATE_MASK)
		dev_err(hdev->dev,
			"Timeout while waiting for device to reset 0x%x\n",
			status);

	अगर (gaudi) अणु
		gaudi->hw_cap_initialized &= ~(HW_CAP_CPU | HW_CAP_CPU_Q |
				HW_CAP_HBM | HW_CAP_PCI_DMA |
				HW_CAP_MME | HW_CAP_TPC_MASK |
				HW_CAP_HBM_DMA | HW_CAP_PLL |
				HW_CAP_NIC_MASK | HW_CAP_MMU |
				HW_CAP_SRAM_SCRAMBLER |
				HW_CAP_HBM_SCRAMBLER |
				HW_CAP_CLK_GATE);

		स_रखो(gaudi->events_stat, 0, माप(gaudi->events_stat));
	पूर्ण
पूर्ण

अटल पूर्णांक gaudi_suspend(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	rc = hl_fw_send_pci_access_msg(hdev, CPUCP_PACKET_DISABLE_PCI_ACCESS);
	अगर (rc)
		dev_err(hdev->dev, "Failed to disable PCI access from CPU\n");

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_resume(काष्ठा hl_device *hdev)
अणु
	वापस gaudi_init_iatu(hdev);
पूर्ण

अटल पूर्णांक gaudi_cb_mmap(काष्ठा hl_device *hdev, काष्ठा vm_area_काष्ठा *vma,
			व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size)
अणु
	पूर्णांक rc;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP |
			VM_DONTCOPY | VM_NORESERVE;

	rc = dma_mmap_coherent(hdev->dev, vma, cpu_addr,
				(dma_addr - HOST_PHYS_BASE), size);
	अगर (rc)
		dev_err(hdev->dev, "dma_mmap_coherent error %d", rc);

	वापस rc;
पूर्ण

अटल व्योम gaudi_ring_करोorbell(काष्ठा hl_device *hdev, u32 hw_queue_id, u32 pi)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 db_reg_offset, db_value, dma_qm_offset, q_off;
	पूर्णांक dma_id;
	bool invalid_queue = false;

	चयन (hw_queue_id) अणु
	हाल GAUDI_QUEUE_ID_DMA_0_0...GAUDI_QUEUE_ID_DMA_0_3:
		dma_id = gaudi_dma_assignment[GAUDI_PCI_DMA_1];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + (hw_queue_id & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_1_0...GAUDI_QUEUE_ID_DMA_1_3:
		dma_id = gaudi_dma_assignment[GAUDI_PCI_DMA_2];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + (hw_queue_id & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_2_0...GAUDI_QUEUE_ID_DMA_2_3:
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_1];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + ((hw_queue_id - 1) & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_3_0...GAUDI_QUEUE_ID_DMA_3_3:
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_2];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + ((hw_queue_id - 1) & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_4_0...GAUDI_QUEUE_ID_DMA_4_3:
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_3];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + ((hw_queue_id - 1) & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_5_0...GAUDI_QUEUE_ID_DMA_5_3:
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_4];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + ((hw_queue_id - 1) & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_6_0...GAUDI_QUEUE_ID_DMA_6_3:
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_5];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + ((hw_queue_id - 1) & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_DMA_7_0...GAUDI_QUEUE_ID_DMA_7_3:
		dma_id = gaudi_dma_assignment[GAUDI_HBM_DMA_6];
		dma_qm_offset = dma_id * DMA_QMAN_OFFSET;
		q_off = dma_qm_offset + ((hw_queue_id - 1) & 0x3) * 4;
		db_reg_offset = mmDMA0_QM_PQ_PI_0 + q_off;
		अवरोध;

	हाल GAUDI_QUEUE_ID_CPU_PQ:
		अगर (gaudi->hw_cap_initialized & HW_CAP_CPU_Q)
			db_reg_offset = mmCPU_IF_PF_PQ_PI;
		अन्यथा
			invalid_queue = true;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_0_0:
		db_reg_offset = mmMME2_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_0_1:
		db_reg_offset = mmMME2_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_0_2:
		db_reg_offset = mmMME2_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_0_3:
		db_reg_offset = mmMME2_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_1_0:
		db_reg_offset = mmMME0_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_1_1:
		db_reg_offset = mmMME0_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_1_2:
		db_reg_offset = mmMME0_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_MME_1_3:
		db_reg_offset = mmMME0_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_0_0:
		db_reg_offset = mmTPC0_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_0_1:
		db_reg_offset = mmTPC0_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_0_2:
		db_reg_offset = mmTPC0_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_0_3:
		db_reg_offset = mmTPC0_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_1_0:
		db_reg_offset = mmTPC1_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_1_1:
		db_reg_offset = mmTPC1_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_1_2:
		db_reg_offset = mmTPC1_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_1_3:
		db_reg_offset = mmTPC1_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_2_0:
		db_reg_offset = mmTPC2_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_2_1:
		db_reg_offset = mmTPC2_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_2_2:
		db_reg_offset = mmTPC2_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_2_3:
		db_reg_offset = mmTPC2_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_3_0:
		db_reg_offset = mmTPC3_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_3_1:
		db_reg_offset = mmTPC3_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_3_2:
		db_reg_offset = mmTPC3_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_3_3:
		db_reg_offset = mmTPC3_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_4_0:
		db_reg_offset = mmTPC4_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_4_1:
		db_reg_offset = mmTPC4_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_4_2:
		db_reg_offset = mmTPC4_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_4_3:
		db_reg_offset = mmTPC4_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_5_0:
		db_reg_offset = mmTPC5_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_5_1:
		db_reg_offset = mmTPC5_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_5_2:
		db_reg_offset = mmTPC5_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_5_3:
		db_reg_offset = mmTPC5_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_6_0:
		db_reg_offset = mmTPC6_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_6_1:
		db_reg_offset = mmTPC6_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_6_2:
		db_reg_offset = mmTPC6_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_6_3:
		db_reg_offset = mmTPC6_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_7_0:
		db_reg_offset = mmTPC7_QM_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_7_1:
		db_reg_offset = mmTPC7_QM_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_7_2:
		db_reg_offset = mmTPC7_QM_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_TPC_7_3:
		db_reg_offset = mmTPC7_QM_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_0_0:
		db_reg_offset = mmNIC0_QM0_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_0_1:
		db_reg_offset = mmNIC0_QM0_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_0_2:
		db_reg_offset = mmNIC0_QM0_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_0_3:
		db_reg_offset = mmNIC0_QM0_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_1_0:
		db_reg_offset = mmNIC0_QM1_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_1_1:
		db_reg_offset = mmNIC0_QM1_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_1_2:
		db_reg_offset = mmNIC0_QM1_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_1_3:
		db_reg_offset = mmNIC0_QM1_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_2_0:
		db_reg_offset = mmNIC1_QM0_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_2_1:
		db_reg_offset = mmNIC1_QM0_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_2_2:
		db_reg_offset = mmNIC1_QM0_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_2_3:
		db_reg_offset = mmNIC1_QM0_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_3_0:
		db_reg_offset = mmNIC1_QM1_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_3_1:
		db_reg_offset = mmNIC1_QM1_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_3_2:
		db_reg_offset = mmNIC1_QM1_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_3_3:
		db_reg_offset = mmNIC1_QM1_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_4_0:
		db_reg_offset = mmNIC2_QM0_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_4_1:
		db_reg_offset = mmNIC2_QM0_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_4_2:
		db_reg_offset = mmNIC2_QM0_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_4_3:
		db_reg_offset = mmNIC2_QM0_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_5_0:
		db_reg_offset = mmNIC2_QM1_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_5_1:
		db_reg_offset = mmNIC2_QM1_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_5_2:
		db_reg_offset = mmNIC2_QM1_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_5_3:
		db_reg_offset = mmNIC2_QM1_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_6_0:
		db_reg_offset = mmNIC3_QM0_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_6_1:
		db_reg_offset = mmNIC3_QM0_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_6_2:
		db_reg_offset = mmNIC3_QM0_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_6_3:
		db_reg_offset = mmNIC3_QM0_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_7_0:
		db_reg_offset = mmNIC3_QM1_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_7_1:
		db_reg_offset = mmNIC3_QM1_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_7_2:
		db_reg_offset = mmNIC3_QM1_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_7_3:
		db_reg_offset = mmNIC3_QM1_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_8_0:
		db_reg_offset = mmNIC4_QM0_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_8_1:
		db_reg_offset = mmNIC4_QM0_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_8_2:
		db_reg_offset = mmNIC4_QM0_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_8_3:
		db_reg_offset = mmNIC4_QM0_PQ_PI_3;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_9_0:
		db_reg_offset = mmNIC4_QM1_PQ_PI_0;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_9_1:
		db_reg_offset = mmNIC4_QM1_PQ_PI_1;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_9_2:
		db_reg_offset = mmNIC4_QM1_PQ_PI_2;
		अवरोध;

	हाल GAUDI_QUEUE_ID_NIC_9_3:
		db_reg_offset = mmNIC4_QM1_PQ_PI_3;
		अवरोध;

	शेष:
		invalid_queue = true;
	पूर्ण

	अगर (invalid_queue) अणु
		/* Should never get here */
		dev_err(hdev->dev, "h/w queue %d is invalid. Can't set pi\n",
			hw_queue_id);
		वापस;
	पूर्ण

	db_value = pi;

	/* ring the करोorbell */
	WREG32(db_reg_offset, db_value);

	अगर (hw_queue_id == GAUDI_QUEUE_ID_CPU_PQ) अणु
		/* make sure device CPU will पढ़ो latest data from host */
		mb();
		WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
				GAUDI_EVENT_PI_UPDATE);
	पूर्ण
पूर्ण

अटल व्योम gaudi_pqe_ग_लिखो(काष्ठा hl_device *hdev, __le64 *pqe,
				काष्ठा hl_bd *bd)
अणु
	__le64 *pbd = (__le64 *) bd;

	/* The QMANs are on the host memory so a simple copy suffice */
	pqe[0] = pbd[0];
	pqe[1] = pbd[1];
पूर्ण

अटल व्योम *gaudi_dma_alloc_coherent(काष्ठा hl_device *hdev, माप_प्रकार size,
					dma_addr_t *dma_handle, gfp_t flags)
अणु
	व्योम *kernel_addr = dma_alloc_coherent(&hdev->pdev->dev, size,
						dma_handle, flags);

	/* Shअगरt to the device's base physical address of host memory */
	अगर (kernel_addr)
		*dma_handle += HOST_PHYS_BASE;

	वापस kernel_addr;
पूर्ण

अटल व्योम gaudi_dma_मुक्त_coherent(काष्ठा hl_device *hdev, माप_प्रकार size,
		व्योम *cpu_addr, dma_addr_t dma_handle)
अणु
	/* Cancel the device's base physical address of host memory */
	dma_addr_t fixed_dma_handle = dma_handle - HOST_PHYS_BASE;

	dma_मुक्त_coherent(&hdev->pdev->dev, size, cpu_addr, fixed_dma_handle);
पूर्ण

अटल पूर्णांक gaudi_hbm_scrubbing(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64  cur_addr = DRAM_BASE_ADDR_USER;
	u32 val;
	u32 chunk_size;
	पूर्णांक rc, dma_id;

	जबतक (cur_addr < prop->dram_end_address) अणु
		क्रम (dma_id = 0 ; dma_id < DMA_NUMBER_OF_CHANNELS ; dma_id++) अणु
			u32 dma_offset = dma_id * DMA_CORE_OFFSET;

			chunk_size =
			min((u64)SZ_2G, prop->dram_end_address - cur_addr);

			dev_dbg(hdev->dev,
				"Doing HBM scrubbing for 0x%09llx - 0x%09llx\n",
				cur_addr, cur_addr + chunk_size);

			WREG32(mmDMA0_CORE_SRC_BASE_LO + dma_offset, 0);
			WREG32(mmDMA0_CORE_SRC_BASE_HI + dma_offset, 0);
			WREG32(mmDMA0_CORE_DST_BASE_LO + dma_offset,
						lower_32_bits(cur_addr));
			WREG32(mmDMA0_CORE_DST_BASE_HI + dma_offset,
						upper_32_bits(cur_addr));
			WREG32(mmDMA0_CORE_DST_TSIZE_0 + dma_offset,
					chunk_size);
			WREG32(mmDMA0_CORE_COMMIT + dma_offset,
					((1 << DMA0_CORE_COMMIT_LIN_SHIFT) |
					(1 << DMA0_CORE_COMMIT_MEM_SET_SHIFT)));

			cur_addr += chunk_size;

			अगर (cur_addr == prop->dram_end_address)
				अवरोध;
		पूर्ण

		क्रम (dma_id = 0 ; dma_id < DMA_NUMBER_OF_CHANNELS ; dma_id++) अणु
			u32 dma_offset = dma_id * DMA_CORE_OFFSET;

			rc = hl_poll_समयout(
				hdev,
				mmDMA0_CORE_STS0 + dma_offset,
				val,
				((val & DMA0_CORE_STS0_BUSY_MASK) == 0),
				1000,
				HBM_SCRUBBING_TIMEOUT_US);

			अगर (rc) अणु
				dev_err(hdev->dev,
					"DMA Timeout during HBM scrubbing of DMA #%d\n",
					dma_id);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_scrub_device_mem(काष्ठा hl_device *hdev, u64 addr, u64 size)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक rc = 0;
	u64 val = 0;

	अगर (!hdev->memory_scrub)
		वापस 0;

	अगर (!addr && !size) अणु
		/* Wait till device is idle */
		rc = hl_poll_समयout(
				hdev,
				mmDMA0_CORE_STS0/* dummy */,
				val/* dummy */,
				(hdev->asic_funcs->is_device_idle(hdev, शून्य,
						0, शून्य)),
						1000,
						HBM_SCRUBBING_TIMEOUT_US);
		अगर (rc) अणु
			dev_err(hdev->dev, "waiting for idle timeout\n");
			वापस -EIO;
		पूर्ण

		/* Scrub SRAM */
		addr = prop->sram_user_base_address;
		size = hdev->pldm ? 0x10000 :
				(prop->sram_size - SRAM_USER_BASE_OFFSET);
		val = 0x7777777777777777ull;

		rc = gaudi_स_रखो_device_memory(hdev, addr, size, val);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to clear SRAM in mem scrub all\n");
			वापस rc;
		पूर्ण

		mutex_lock(&gaudi->clk_gate_mutex);
		hdev->asic_funcs->disable_घड़ी_gating(hdev);

		/* Scrub HBM using all DMA channels in parallel */
		rc = gaudi_hbm_scrubbing(hdev);
		अगर (rc)
			dev_err(hdev->dev,
				"Failed to clear HBM in mem scrub all\n");

		hdev->asic_funcs->set_घड़ी_gating(hdev);
		mutex_unlock(&gaudi->clk_gate_mutex);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम *gaudi_get_पूर्णांक_queue_base(काष्ठा hl_device *hdev,
				u32 queue_id, dma_addr_t *dma_handle,
				u16 *queue_len)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा gaudi_पूर्णांकernal_qman_info *q;

	अगर (queue_id >= GAUDI_QUEUE_ID_SIZE ||
			gaudi_queue_type[queue_id] != QUEUE_TYPE_INT) अणु
		dev_err(hdev->dev, "Got invalid queue id %d\n", queue_id);
		वापस शून्य;
	पूर्ण

	q = &gaudi->पूर्णांकernal_qmans[queue_id];
	*dma_handle = q->pq_dma_addr;
	*queue_len = q->pq_size / QMAN_PQ_ENTRY_SIZE;

	वापस q->pq_kernel_addr;
पूर्ण

अटल पूर्णांक gaudi_send_cpu_message(काष्ठा hl_device *hdev, u32 *msg,
				u16 len, u32 समयout, u64 *result)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_CPU_Q)) अणु
		अगर (result)
			*result = 0;
		वापस 0;
	पूर्ण

	अगर (!समयout)
		समयout = GAUDI_MSG_TO_CPU_TIMEOUT_USEC;

	वापस hl_fw_send_cpu_message(hdev, GAUDI_QUEUE_ID_CPU_PQ, msg, len,
						समयout, result);
पूर्ण

अटल पूर्णांक gaudi_test_queue(काष्ठा hl_device *hdev, u32 hw_queue_id)
अणु
	काष्ठा packet_msg_prot *fence_pkt;
	dma_addr_t pkt_dma_addr;
	u32 fence_val, पंचांगp, समयout_usec;
	dma_addr_t fence_dma_addr;
	u32 *fence_ptr;
	पूर्णांक rc;

	अगर (hdev->pldm)
		समयout_usec = GAUDI_PLDM_TEST_QUEUE_WAIT_USEC;
	अन्यथा
		समयout_usec = GAUDI_TEST_QUEUE_WAIT_USEC;

	fence_val = GAUDI_QMAN0_FENCE_VAL;

	fence_ptr = hdev->asic_funcs->asic_dma_pool_zalloc(hdev, 4, GFP_KERNEL,
							&fence_dma_addr);
	अगर (!fence_ptr) अणु
		dev_err(hdev->dev,
			"Failed to allocate memory for H/W queue %d testing\n",
			hw_queue_id);
		वापस -ENOMEM;
	पूर्ण

	*fence_ptr = 0;

	fence_pkt = hdev->asic_funcs->asic_dma_pool_zalloc(hdev,
					माप(काष्ठा packet_msg_prot),
					GFP_KERNEL, &pkt_dma_addr);
	अगर (!fence_pkt) अणु
		dev_err(hdev->dev,
			"Failed to allocate packet for H/W queue %d testing\n",
			hw_queue_id);
		rc = -ENOMEM;
		जाओ मुक्त_fence_ptr;
	पूर्ण

	पंचांगp = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_PROT);
	पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 1);
	पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	fence_pkt->ctl = cpu_to_le32(पंचांगp);
	fence_pkt->value = cpu_to_le32(fence_val);
	fence_pkt->addr = cpu_to_le64(fence_dma_addr);

	rc = hl_hw_queue_send_cb_no_cmpl(hdev, hw_queue_id,
					माप(काष्ठा packet_msg_prot),
					pkt_dma_addr);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to send fence packet to H/W queue %d\n",
			hw_queue_id);
		जाओ मुक्त_pkt;
	पूर्ण

	rc = hl_poll_समयout_memory(hdev, fence_ptr, पंचांगp, (पंचांगp == fence_val),
					1000, समयout_usec, true);

	hl_hw_queue_inc_ci_kernel(hdev, hw_queue_id);

	अगर (rc == -ETIMEDOUT) अणु
		dev_err(hdev->dev,
			"H/W queue %d test failed (scratch(0x%08llX) == 0x%08X)\n",
			hw_queue_id, (अचिन्हित दीर्घ दीर्घ) fence_dma_addr, पंचांगp);
		rc = -EIO;
	पूर्ण

मुक्त_pkt:
	hdev->asic_funcs->asic_dma_pool_मुक्त(hdev, (व्योम *) fence_pkt,
					pkt_dma_addr);
मुक्त_fence_ptr:
	hdev->asic_funcs->asic_dma_pool_मुक्त(hdev, (व्योम *) fence_ptr,
					fence_dma_addr);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_test_cpu_queue(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	/*
	 * check capability here as send_cpu_message() won't update the result
	 * value अगर no capability
	 */
	अगर (!(gaudi->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	वापस hl_fw_test_cpu_queue(hdev);
पूर्ण

अटल पूर्णांक gaudi_test_queues(काष्ठा hl_device *hdev)
अणु
	पूर्णांक i, rc, ret_val = 0;

	क्रम (i = 0 ; i < hdev->asic_prop.max_queues ; i++) अणु
		अगर (hdev->asic_prop.hw_queues_props[i].type == QUEUE_TYPE_EXT) अणु
			rc = gaudi_test_queue(hdev, i);
			अगर (rc)
				ret_val = -EINVAL;
		पूर्ण
	पूर्ण

	rc = gaudi_test_cpu_queue(hdev);
	अगर (rc)
		ret_val = -EINVAL;

	वापस ret_val;
पूर्ण

अटल व्योम *gaudi_dma_pool_zalloc(काष्ठा hl_device *hdev, माप_प्रकार size,
		gfp_t mem_flags, dma_addr_t *dma_handle)
अणु
	व्योम *kernel_addr;

	अगर (size > GAUDI_DMA_POOL_BLK_SIZE)
		वापस शून्य;

	kernel_addr = dma_pool_zalloc(hdev->dma_pool, mem_flags, dma_handle);

	/* Shअगरt to the device's base physical address of host memory */
	अगर (kernel_addr)
		*dma_handle += HOST_PHYS_BASE;

	वापस kernel_addr;
पूर्ण

अटल व्योम gaudi_dma_pool_मुक्त(काष्ठा hl_device *hdev, व्योम *vaddr,
			dma_addr_t dma_addr)
अणु
	/* Cancel the device's base physical address of host memory */
	dma_addr_t fixed_dma_addr = dma_addr - HOST_PHYS_BASE;

	dma_pool_मुक्त(hdev->dma_pool, vaddr, fixed_dma_addr);
पूर्ण

अटल व्योम *gaudi_cpu_accessible_dma_pool_alloc(काष्ठा hl_device *hdev,
					माप_प्रकार size, dma_addr_t *dma_handle)
अणु
	वापस hl_fw_cpu_accessible_dma_pool_alloc(hdev, size, dma_handle);
पूर्ण

अटल व्योम gaudi_cpu_accessible_dma_pool_मुक्त(काष्ठा hl_device *hdev,
						माप_प्रकार size, व्योम *vaddr)
अणु
	hl_fw_cpu_accessible_dma_pool_मुक्त(hdev, size, vaddr);
पूर्ण

अटल पूर्णांक gaudi_dma_map_sg(काष्ठा hl_device *hdev, काष्ठा scatterlist *sgl,
			पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (!dma_map_sg(&hdev->pdev->dev, sgl, nents, dir))
		वापस -ENOMEM;

	/* Shअगरt to the device's base physical address of host memory */
	क्रम_each_sg(sgl, sg, nents, i)
		sg->dma_address += HOST_PHYS_BASE;

	वापस 0;
पूर्ण

अटल व्योम gaudi_dma_unmap_sg(काष्ठा hl_device *hdev, काष्ठा scatterlist *sgl,
			पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	/* Cancel the device's base physical address of host memory */
	क्रम_each_sg(sgl, sg, nents, i)
		sg->dma_address -= HOST_PHYS_BASE;

	dma_unmap_sg(&hdev->pdev->dev, sgl, nents, dir);
पूर्ण

अटल u32 gaudi_get_dma_desc_list_size(काष्ठा hl_device *hdev,
					काष्ठा sg_table *sgt)
अणु
	काष्ठा scatterlist *sg, *sg_next_iter;
	u32 count, dma_desc_cnt;
	u64 len, len_next;
	dma_addr_t addr, addr_next;

	dma_desc_cnt = 0;

	क्रम_each_sg(sgt->sgl, sg, sgt->nents, count) अणु

		len = sg_dma_len(sg);
		addr = sg_dma_address(sg);

		अगर (len == 0)
			अवरोध;

		जबतक ((count + 1) < sgt->nents) अणु
			sg_next_iter = sg_next(sg);
			len_next = sg_dma_len(sg_next_iter);
			addr_next = sg_dma_address(sg_next_iter);

			अगर (len_next == 0)
				अवरोध;

			अगर ((addr + len == addr_next) &&
				(len + len_next <= DMA_MAX_TRANSFER_SIZE)) अणु
				len += len_next;
				count++;
				sg = sg_next_iter;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		dma_desc_cnt++;
	पूर्ण

	वापस dma_desc_cnt * माप(काष्ठा packet_lin_dma);
पूर्ण

अटल पूर्णांक gaudi_pin_memory_beक्रमe_cs(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt,
				u64 addr, क्रमागत dma_data_direction dir)
अणु
	काष्ठा hl_userptr *userptr;
	पूर्णांक rc;

	अगर (hl_userptr_is_pinned(hdev, addr, le32_to_cpu(user_dma_pkt->tsize),
			parser->job_userptr_list, &userptr))
		जाओ alपढ़ोy_pinned;

	userptr = kzalloc(माप(*userptr), GFP_KERNEL);
	अगर (!userptr)
		वापस -ENOMEM;

	rc = hl_pin_host_memory(hdev, addr, le32_to_cpu(user_dma_pkt->tsize),
				userptr);
	अगर (rc)
		जाओ मुक्त_userptr;

	list_add_tail(&userptr->job_node, parser->job_userptr_list);

	rc = hdev->asic_funcs->asic_dma_map_sg(hdev, userptr->sgt->sgl,
					userptr->sgt->nents, dir);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to map sgt with DMA region\n");
		जाओ unpin_memory;
	पूर्ण

	userptr->dma_mapped = true;
	userptr->dir = dir;

alपढ़ोy_pinned:
	parser->patched_cb_size +=
			gaudi_get_dma_desc_list_size(hdev, userptr->sgt);

	वापस 0;

unpin_memory:
	hl_unpin_host_memory(hdev, userptr);
मुक्त_userptr:
	kमुक्त(userptr);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_validate_dma_pkt_host(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt,
				bool src_in_host)
अणु
	क्रमागत dma_data_direction dir;
	bool skip_host_mem_pin = false, user_स_रखो;
	u64 addr;
	पूर्णांक rc = 0;

	user_स_रखो = (le32_to_cpu(user_dma_pkt->ctl) &
			GAUDI_PKT_LIN_DMA_CTL_MEMSET_MASK) >>
			GAUDI_PKT_LIN_DMA_CTL_MEMSET_SHIFT;

	अगर (src_in_host) अणु
		अगर (user_स_रखो)
			skip_host_mem_pin = true;

		dev_dbg(hdev->dev, "DMA direction is HOST --> DEVICE\n");
		dir = DMA_TO_DEVICE;
		addr = le64_to_cpu(user_dma_pkt->src_addr);
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev, "DMA direction is DEVICE --> HOST\n");
		dir = DMA_FROM_DEVICE;
		addr = (le64_to_cpu(user_dma_pkt->dst_addr) &
				GAUDI_PKT_LIN_DMA_DST_ADDR_MASK) >>
				GAUDI_PKT_LIN_DMA_DST_ADDR_SHIFT;
	पूर्ण

	अगर (skip_host_mem_pin)
		parser->patched_cb_size += माप(*user_dma_pkt);
	अन्यथा
		rc = gaudi_pin_memory_beक्रमe_cs(hdev, parser, user_dma_pkt,
						addr, dir);

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_validate_dma_pkt_no_mmu(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt)
अणु
	bool src_in_host = false;
	u64 dst_addr = (le64_to_cpu(user_dma_pkt->dst_addr) &
			GAUDI_PKT_LIN_DMA_DST_ADDR_MASK) >>
			GAUDI_PKT_LIN_DMA_DST_ADDR_SHIFT;

	dev_dbg(hdev->dev, "DMA packet details:\n");
	dev_dbg(hdev->dev, "source == 0x%llx\n",
				le64_to_cpu(user_dma_pkt->src_addr));
	dev_dbg(hdev->dev, "destination == 0x%llx\n", dst_addr);
	dev_dbg(hdev->dev, "size == %u\n", le32_to_cpu(user_dma_pkt->tsize));

	/*
	 * Special handling क्रम DMA with size 0. Bypass all validations
	 * because no transactions will be करोne except क्रम WR_COMP, which
	 * is not a security issue
	 */
	अगर (!le32_to_cpu(user_dma_pkt->tsize)) अणु
		parser->patched_cb_size += माप(*user_dma_pkt);
		वापस 0;
	पूर्ण

	अगर (parser->hw_queue_id <= GAUDI_QUEUE_ID_DMA_0_3)
		src_in_host = true;

	वापस gaudi_validate_dma_pkt_host(hdev, parser, user_dma_pkt,
						src_in_host);
पूर्ण

अटल पूर्णांक gaudi_validate_load_and_exe_pkt(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_parser *parser,
					काष्ठा packet_load_and_exe *user_pkt)
अणु
	u32 cfg;

	cfg = le32_to_cpu(user_pkt->cfg);

	अगर (cfg & GAUDI_PKT_LOAD_AND_EXE_CFG_DST_MASK) अणु
		dev_err(hdev->dev,
			"User not allowed to use Load and Execute\n");
		वापस -EPERM;
	पूर्ण

	parser->patched_cb_size += माप(काष्ठा packet_load_and_exe);

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_validate_cb(काष्ठा hl_device *hdev,
			काष्ठा hl_cs_parser *parser, bool is_mmu)
अणु
	u32 cb_parsed_length = 0;
	पूर्णांक rc = 0;

	parser->patched_cb_size = 0;

	/* cb_user_size is more than 0 so loop will always be executed */
	जबतक (cb_parsed_length < parser->user_cb_size) अणु
		क्रमागत packet_id pkt_id;
		u16 pkt_size;
		काष्ठा gaudi_packet *user_pkt;

		user_pkt = parser->user_cb->kernel_address + cb_parsed_length;

		pkt_id = (क्रमागत packet_id) (
				(le64_to_cpu(user_pkt->header) &
				PACKET_HEADER_PACKET_ID_MASK) >>
					PACKET_HEADER_PACKET_ID_SHIFT);

		अगर (!validate_packet_id(pkt_id)) अणु
			dev_err(hdev->dev, "Invalid packet id %u\n", pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		pkt_size = gaudi_packet_sizes[pkt_id];
		cb_parsed_length += pkt_size;
		अगर (cb_parsed_length > parser->user_cb_size) अणु
			dev_err(hdev->dev,
				"packet 0x%x is out of CB boundary\n", pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (pkt_id) अणु
		हाल PACKET_MSG_PROT:
			dev_err(hdev->dev,
				"User not allowed to use MSG_PROT\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_CP_DMA:
			dev_err(hdev->dev, "User not allowed to use CP_DMA\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_STOP:
			dev_err(hdev->dev, "User not allowed to use STOP\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_WREG_BULK:
			dev_err(hdev->dev,
				"User not allowed to use WREG_BULK\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_LOAD_AND_EXE:
			rc = gaudi_validate_load_and_exe_pkt(hdev, parser,
				(काष्ठा packet_load_and_exe *) user_pkt);
			अवरोध;

		हाल PACKET_LIN_DMA:
			parser->contains_dma_pkt = true;
			अगर (is_mmu)
				parser->patched_cb_size += pkt_size;
			अन्यथा
				rc = gaudi_validate_dma_pkt_no_mmu(hdev, parser,
					(काष्ठा packet_lin_dma *) user_pkt);
			अवरोध;

		हाल PACKET_WREG_32:
		हाल PACKET_MSG_LONG:
		हाल PACKET_MSG_SHORT:
		हाल PACKET_REPEAT:
		हाल PACKET_FENCE:
		हाल PACKET_NOP:
		हाल PACKET_ARB_POINT:
			parser->patched_cb_size += pkt_size;
			अवरोध;

		शेष:
			dev_err(hdev->dev, "Invalid packet header 0x%x\n",
				pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (rc)
			अवरोध;
	पूर्ण

	/*
	 * The new CB should have space at the end क्रम two MSG_PROT packets:
	 * 1. A packet that will act as a completion packet
	 * 2. A packet that will generate MSI-X पूर्णांकerrupt
	 */
	अगर (parser->completion)
		parser->patched_cb_size += माप(काष्ठा packet_msg_prot) * 2;

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_patch_dma_packet(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt,
				काष्ठा packet_lin_dma *new_dma_pkt,
				u32 *new_dma_pkt_size)
अणु
	काष्ठा hl_userptr *userptr;
	काष्ठा scatterlist *sg, *sg_next_iter;
	u32 count, dma_desc_cnt, user_wrcomp_en_mask, ctl;
	u64 len, len_next;
	dma_addr_t dma_addr, dma_addr_next;
	u64 device_memory_addr, addr;
	क्रमागत dma_data_direction dir;
	काष्ठा sg_table *sgt;
	bool src_in_host = false;
	bool skip_host_mem_pin = false;
	bool user_स_रखो;

	ctl = le32_to_cpu(user_dma_pkt->ctl);

	अगर (parser->hw_queue_id <= GAUDI_QUEUE_ID_DMA_0_3)
		src_in_host = true;

	user_स_रखो = (ctl & GAUDI_PKT_LIN_DMA_CTL_MEMSET_MASK) >>
			GAUDI_PKT_LIN_DMA_CTL_MEMSET_SHIFT;

	अगर (src_in_host) अणु
		addr = le64_to_cpu(user_dma_pkt->src_addr);
		device_memory_addr = le64_to_cpu(user_dma_pkt->dst_addr);
		dir = DMA_TO_DEVICE;
		अगर (user_स_रखो)
			skip_host_mem_pin = true;
	पूर्ण अन्यथा अणु
		addr = le64_to_cpu(user_dma_pkt->dst_addr);
		device_memory_addr = le64_to_cpu(user_dma_pkt->src_addr);
		dir = DMA_FROM_DEVICE;
	पूर्ण

	अगर ((!skip_host_mem_pin) &&
		(!hl_userptr_is_pinned(hdev, addr,
					le32_to_cpu(user_dma_pkt->tsize),
					parser->job_userptr_list, &userptr))) अणु
		dev_err(hdev->dev, "Userptr 0x%llx + 0x%x NOT mapped\n",
				addr, user_dma_pkt->tsize);
		वापस -EFAULT;
	पूर्ण

	अगर ((user_स_रखो) && (dir == DMA_TO_DEVICE)) अणु
		स_नकल(new_dma_pkt, user_dma_pkt, माप(*user_dma_pkt));
		*new_dma_pkt_size = माप(*user_dma_pkt);
		वापस 0;
	पूर्ण

	user_wrcomp_en_mask = ctl & GAUDI_PKT_LIN_DMA_CTL_WRCOMP_EN_MASK;

	sgt = userptr->sgt;
	dma_desc_cnt = 0;

	क्रम_each_sg(sgt->sgl, sg, sgt->nents, count) अणु
		len = sg_dma_len(sg);
		dma_addr = sg_dma_address(sg);

		अगर (len == 0)
			अवरोध;

		जबतक ((count + 1) < sgt->nents) अणु
			sg_next_iter = sg_next(sg);
			len_next = sg_dma_len(sg_next_iter);
			dma_addr_next = sg_dma_address(sg_next_iter);

			अगर (len_next == 0)
				अवरोध;

			अगर ((dma_addr + len == dma_addr_next) &&
				(len + len_next <= DMA_MAX_TRANSFER_SIZE)) अणु
				len += len_next;
				count++;
				sg = sg_next_iter;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		ctl = le32_to_cpu(user_dma_pkt->ctl);
		अगर (likely(dma_desc_cnt))
			ctl &= ~GAUDI_PKT_CTL_EB_MASK;
		ctl &= ~GAUDI_PKT_LIN_DMA_CTL_WRCOMP_EN_MASK;
		new_dma_pkt->ctl = cpu_to_le32(ctl);
		new_dma_pkt->tsize = cpu_to_le32(len);

		अगर (dir == DMA_TO_DEVICE) अणु
			new_dma_pkt->src_addr = cpu_to_le64(dma_addr);
			new_dma_pkt->dst_addr = cpu_to_le64(device_memory_addr);
		पूर्ण अन्यथा अणु
			new_dma_pkt->src_addr = cpu_to_le64(device_memory_addr);
			new_dma_pkt->dst_addr = cpu_to_le64(dma_addr);
		पूर्ण

		अगर (!user_स_रखो)
			device_memory_addr += len;
		dma_desc_cnt++;
		new_dma_pkt++;
	पूर्ण

	अगर (!dma_desc_cnt) अणु
		dev_err(hdev->dev,
			"Error of 0 SG entries when patching DMA packet\n");
		वापस -EFAULT;
	पूर्ण

	/* Fix the last dma packet - wrcomp must be as user set it */
	new_dma_pkt--;
	new_dma_pkt->ctl |= cpu_to_le32(user_wrcomp_en_mask);

	*new_dma_pkt_size = dma_desc_cnt * माप(काष्ठा packet_lin_dma);

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_patch_cb(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser)
अणु
	u32 cb_parsed_length = 0;
	u32 cb_patched_cur_length = 0;
	पूर्णांक rc = 0;

	/* cb_user_size is more than 0 so loop will always be executed */
	जबतक (cb_parsed_length < parser->user_cb_size) अणु
		क्रमागत packet_id pkt_id;
		u16 pkt_size;
		u32 new_pkt_size = 0;
		काष्ठा gaudi_packet *user_pkt, *kernel_pkt;

		user_pkt = parser->user_cb->kernel_address + cb_parsed_length;
		kernel_pkt = parser->patched_cb->kernel_address +
					cb_patched_cur_length;

		pkt_id = (क्रमागत packet_id) (
				(le64_to_cpu(user_pkt->header) &
				PACKET_HEADER_PACKET_ID_MASK) >>
					PACKET_HEADER_PACKET_ID_SHIFT);

		अगर (!validate_packet_id(pkt_id)) अणु
			dev_err(hdev->dev, "Invalid packet id %u\n", pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		pkt_size = gaudi_packet_sizes[pkt_id];
		cb_parsed_length += pkt_size;
		अगर (cb_parsed_length > parser->user_cb_size) अणु
			dev_err(hdev->dev,
				"packet 0x%x is out of CB boundary\n", pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (pkt_id) अणु
		हाल PACKET_LIN_DMA:
			rc = gaudi_patch_dma_packet(hdev, parser,
					(काष्ठा packet_lin_dma *) user_pkt,
					(काष्ठा packet_lin_dma *) kernel_pkt,
					&new_pkt_size);
			cb_patched_cur_length += new_pkt_size;
			अवरोध;

		हाल PACKET_MSG_PROT:
			dev_err(hdev->dev,
				"User not allowed to use MSG_PROT\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_CP_DMA:
			dev_err(hdev->dev, "User not allowed to use CP_DMA\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_STOP:
			dev_err(hdev->dev, "User not allowed to use STOP\n");
			rc = -EPERM;
			अवरोध;

		हाल PACKET_WREG_32:
		हाल PACKET_WREG_BULK:
		हाल PACKET_MSG_LONG:
		हाल PACKET_MSG_SHORT:
		हाल PACKET_REPEAT:
		हाल PACKET_FENCE:
		हाल PACKET_NOP:
		हाल PACKET_ARB_POINT:
		हाल PACKET_LOAD_AND_EXE:
			स_नकल(kernel_pkt, user_pkt, pkt_size);
			cb_patched_cur_length += pkt_size;
			अवरोध;

		शेष:
			dev_err(hdev->dev, "Invalid packet header 0x%x\n",
				pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_parse_cb_mmu(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_parser *parser)
अणु
	u64 patched_cb_handle;
	u32 patched_cb_size;
	काष्ठा hl_cb *user_cb;
	पूर्णांक rc;

	/*
	 * The new CB should have space at the end क्रम two MSG_PROT pkt:
	 * 1. A packet that will act as a completion packet
	 * 2. A packet that will generate MSI पूर्णांकerrupt
	 */
	अगर (parser->completion)
		parser->patched_cb_size = parser->user_cb_size +
				माप(काष्ठा packet_msg_prot) * 2;
	अन्यथा
		parser->patched_cb_size = parser->user_cb_size;

	rc = hl_cb_create(hdev, &hdev->kernel_cb_mgr, hdev->kernel_ctx,
				parser->patched_cb_size, false, false,
				&patched_cb_handle);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to allocate patched CB for DMA CS %d\n",
			rc);
		वापस rc;
	पूर्ण

	patched_cb_handle >>= PAGE_SHIFT;
	parser->patched_cb = hl_cb_get(hdev, &hdev->kernel_cb_mgr,
				(u32) patched_cb_handle);
	/* hl_cb_get should never fail */
	अगर (!parser->patched_cb) अणु
		dev_crit(hdev->dev, "DMA CB handle invalid 0x%x\n",
			(u32) patched_cb_handle);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	/*
	 * The check that parser->user_cb_size <= parser->user_cb->size was करोne
	 * in validate_queue_index().
	 */
	स_नकल(parser->patched_cb->kernel_address,
		parser->user_cb->kernel_address,
		parser->user_cb_size);

	patched_cb_size = parser->patched_cb_size;

	/* Validate patched CB instead of user CB */
	user_cb = parser->user_cb;
	parser->user_cb = parser->patched_cb;
	rc = gaudi_validate_cb(hdev, parser, true);
	parser->user_cb = user_cb;

	अगर (rc) अणु
		hl_cb_put(parser->patched_cb);
		जाओ out;
	पूर्ण

	अगर (patched_cb_size != parser->patched_cb_size) अणु
		dev_err(hdev->dev, "user CB size mismatch\n");
		hl_cb_put(parser->patched_cb);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

out:
	/*
	 * Always call cb destroy here because we still have 1 reference
	 * to it by calling cb_get earlier. After the job will be completed,
	 * cb_put will release it, but here we want to हटाओ it from the
	 * idr
	 */
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr,
					patched_cb_handle << PAGE_SHIFT);

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_parse_cb_no_mmu(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_parser *parser)
अणु
	u64 patched_cb_handle;
	पूर्णांक rc;

	rc = gaudi_validate_cb(hdev, parser, false);

	अगर (rc)
		जाओ मुक्त_userptr;

	rc = hl_cb_create(hdev, &hdev->kernel_cb_mgr, hdev->kernel_ctx,
				parser->patched_cb_size, false, false,
				&patched_cb_handle);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to allocate patched CB for DMA CS %d\n", rc);
		जाओ मुक्त_userptr;
	पूर्ण

	patched_cb_handle >>= PAGE_SHIFT;
	parser->patched_cb = hl_cb_get(hdev, &hdev->kernel_cb_mgr,
				(u32) patched_cb_handle);
	/* hl_cb_get should never fail here */
	अगर (!parser->patched_cb) अणु
		dev_crit(hdev->dev, "DMA CB handle invalid 0x%x\n",
				(u32) patched_cb_handle);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	rc = gaudi_patch_cb(hdev, parser);

	अगर (rc)
		hl_cb_put(parser->patched_cb);

out:
	/*
	 * Always call cb destroy here because we still have 1 reference
	 * to it by calling cb_get earlier. After the job will be completed,
	 * cb_put will release it, but here we want to हटाओ it from the
	 * idr
	 */
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr,
				patched_cb_handle << PAGE_SHIFT);

मुक्त_userptr:
	अगर (rc)
		hl_userptr_delete_list(hdev, parser->job_userptr_list);
	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_parse_cb_no_ext_queue(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_parser *parser)
अणु
	काष्ठा asic_fixed_properties *asic_prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 nic_mask_q_id = 1 << (HW_CAP_NIC_SHIFT +
		((parser->hw_queue_id - GAUDI_QUEUE_ID_NIC_0_0) >> 2));

	अगर ((parser->hw_queue_id >= GAUDI_QUEUE_ID_NIC_0_0) &&
			(parser->hw_queue_id <= GAUDI_QUEUE_ID_NIC_9_3) &&
			(!(gaudi->hw_cap_initialized & nic_mask_q_id))) अणु
		dev_err(hdev->dev, "h/w queue %d is disabled\n",
				parser->hw_queue_id);
		वापस -EINVAL;
	पूर्ण

	/* For पूर्णांकernal queue jobs just check अगर CB address is valid */
	अगर (hl_mem_area_inside_range((u64) (uपूर्णांकptr_t) parser->user_cb,
					parser->user_cb_size,
					asic_prop->sram_user_base_address,
					asic_prop->sram_end_address))
		वापस 0;

	अगर (hl_mem_area_inside_range((u64) (uपूर्णांकptr_t) parser->user_cb,
					parser->user_cb_size,
					asic_prop->dram_user_base_address,
					asic_prop->dram_end_address))
		वापस 0;

	/* PMMU and HPMMU addresses are equal, check only one of them */
	अगर (hl_mem_area_inside_range((u64) (uपूर्णांकptr_t) parser->user_cb,
					parser->user_cb_size,
					asic_prop->pmmu.start_addr,
					asic_prop->pmmu.end_addr))
		वापस 0;

	dev_err(hdev->dev,
		"CB address 0x%px + 0x%x for internal QMAN is not valid\n",
		parser->user_cb, parser->user_cb_size);

	वापस -EFAULT;
पूर्ण

अटल पूर्णांक gaudi_cs_parser(काष्ठा hl_device *hdev, काष्ठा hl_cs_parser *parser)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (parser->queue_type == QUEUE_TYPE_INT)
		वापस gaudi_parse_cb_no_ext_queue(hdev, parser);

	अगर (gaudi->hw_cap_initialized & HW_CAP_MMU)
		वापस gaudi_parse_cb_mmu(hdev, parser);
	अन्यथा
		वापस gaudi_parse_cb_no_mmu(hdev, parser);
पूर्ण

अटल व्योम gaudi_add_end_of_cb_packets(काष्ठा hl_device *hdev,
					व्योम *kernel_address, u32 len,
					u64 cq_addr, u32 cq_val, u32 msi_vec,
					bool eb)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा packet_msg_prot *cq_pkt;
	u32 पंचांगp;

	cq_pkt = kernel_address + len - (माप(काष्ठा packet_msg_prot) * 2);

	पंचांगp = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_PROT);
	पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	अगर (eb)
		पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 1);

	cq_pkt->ctl = cpu_to_le32(पंचांगp);
	cq_pkt->value = cpu_to_le32(cq_val);
	cq_pkt->addr = cpu_to_le64(cq_addr);

	cq_pkt++;

	पंचांगp = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_PROT);
	पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);
	cq_pkt->ctl = cpu_to_le32(पंचांगp);
	cq_pkt->value = cpu_to_le32(1);

	अगर (!gaudi->multi_msi_mode)
		msi_vec = 0;

	cq_pkt->addr = cpu_to_le64(CFG_BASE + mmPCIE_MSI_INTR_0 + msi_vec * 4);
पूर्ण

अटल व्योम gaudi_update_eq_ci(काष्ठा hl_device *hdev, u32 val)
अणु
	WREG32(mmCPU_IF_EQ_RD_OFFS, val);
पूर्ण

अटल पूर्णांक gaudi_स_रखो_device_memory(काष्ठा hl_device *hdev, u64 addr,
					u32 size, u64 val)
अणु
	काष्ठा packet_lin_dma *lin_dma_pkt;
	काष्ठा hl_cs_job *job;
	u32 cb_size, ctl, err_cause;
	काष्ठा hl_cb *cb;
	u64 id;
	पूर्णांक rc;

	cb = hl_cb_kernel_create(hdev, PAGE_SIZE, false);
	अगर (!cb)
		वापस -EFAULT;

	lin_dma_pkt = cb->kernel_address;
	स_रखो(lin_dma_pkt, 0, माप(*lin_dma_pkt));
	cb_size = माप(*lin_dma_pkt);

	ctl = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_LIN_DMA);
	ctl |= FIELD_PREP(GAUDI_PKT_LIN_DMA_CTL_MEMSET_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_LIN_DMA_CTL_LIN_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);

	lin_dma_pkt->ctl = cpu_to_le32(ctl);
	lin_dma_pkt->src_addr = cpu_to_le64(val);
	lin_dma_pkt->dst_addr |= cpu_to_le64(addr);
	lin_dma_pkt->tsize = cpu_to_le32(size);

	job = hl_cs_allocate_job(hdev, QUEUE_TYPE_EXT, true);
	अगर (!job) अणु
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		rc = -ENOMEM;
		जाओ release_cb;
	पूर्ण

	/* Verअगरy DMA is OK */
	err_cause = RREG32(mmDMA0_CORE_ERR_CAUSE);
	अगर (err_cause && !hdev->init_करोne) अणु
		dev_dbg(hdev->dev,
			"Clearing DMA0 engine from errors (cause 0x%x)\n",
			err_cause);
		WREG32(mmDMA0_CORE_ERR_CAUSE, err_cause);
	पूर्ण

	job->id = 0;
	job->user_cb = cb;
	atomic_inc(&job->user_cb->cs_cnt);
	job->user_cb_size = cb_size;
	job->hw_queue_id = GAUDI_QUEUE_ID_DMA_0_0;
	job->patched_cb = job->user_cb;
	job->job_cb_size = job->user_cb_size + माप(काष्ठा packet_msg_prot);

	hl_debugfs_add_job(hdev, job);

	rc = gaudi_send_job_on_qman0(hdev, job);
	hl_debugfs_हटाओ_job(hdev, job);
	kमुक्त(job);
	atomic_dec(&cb->cs_cnt);

	/* Verअगरy DMA is OK */
	err_cause = RREG32(mmDMA0_CORE_ERR_CAUSE);
	अगर (err_cause) अणु
		dev_err(hdev->dev, "DMA Failed, cause 0x%x\n", err_cause);
		rc = -EIO;
		अगर (!hdev->init_करोne) अणु
			dev_dbg(hdev->dev,
				"Clearing DMA0 engine from errors (cause 0x%x)\n",
				err_cause);
			WREG32(mmDMA0_CORE_ERR_CAUSE, err_cause);
		पूर्ण
	पूर्ण

release_cb:
	id = cb->id;
	hl_cb_put(cb);
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, id << PAGE_SHIFT);

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_स_रखो_रेजिस्टरs(काष्ठा hl_device *hdev, u64 reg_base,
					u32 num_regs, u32 val)
अणु
	काष्ठा packet_msg_दीर्घ *pkt;
	काष्ठा hl_cs_job *job;
	u32 cb_size, ctl;
	काष्ठा hl_cb *cb;
	पूर्णांक i, rc;

	cb_size = (माप(*pkt) * num_regs) + माप(काष्ठा packet_msg_prot);

	अगर (cb_size > SZ_2M) अणु
		dev_err(hdev->dev, "CB size must be smaller than %uMB", SZ_2M);
		वापस -ENOMEM;
	पूर्ण

	cb = hl_cb_kernel_create(hdev, cb_size, false);
	अगर (!cb)
		वापस -EFAULT;

	pkt = cb->kernel_address;

	ctl = FIELD_PREP(GAUDI_PKT_LONG_CTL_OP_MASK, 0); /* ग_लिखो the value */
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_LONG);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	क्रम (i = 0; i < num_regs ; i++, pkt++) अणु
		pkt->ctl = cpu_to_le32(ctl);
		pkt->value = cpu_to_le32(val);
		pkt->addr = cpu_to_le64(reg_base + (i * 4));
	पूर्ण

	job = hl_cs_allocate_job(hdev, QUEUE_TYPE_EXT, true);
	अगर (!job) अणु
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		rc = -ENOMEM;
		जाओ release_cb;
	पूर्ण

	job->id = 0;
	job->user_cb = cb;
	atomic_inc(&job->user_cb->cs_cnt);
	job->user_cb_size = cb_size;
	job->hw_queue_id = GAUDI_QUEUE_ID_DMA_0_0;
	job->patched_cb = job->user_cb;
	job->job_cb_size = cb_size;

	hl_debugfs_add_job(hdev, job);

	rc = gaudi_send_job_on_qman0(hdev, job);
	hl_debugfs_हटाओ_job(hdev, job);
	kमुक्त(job);
	atomic_dec(&cb->cs_cnt);

release_cb:
	hl_cb_put(cb);
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_schedule_रेजिस्टर_स_रखो(काष्ठा hl_device *hdev,
		u32 hw_queue_id, u64 reg_base, u32 num_regs, u32 val)
अणु
	काष्ठा hl_ctx *ctx;
	काष्ठा hl_pending_cb *pending_cb;
	काष्ठा packet_msg_दीर्घ *pkt;
	u32 cb_size, ctl;
	काष्ठा hl_cb *cb;
	पूर्णांक i, rc;

	mutex_lock(&hdev->fpriv_list_lock);
	ctx = hdev->compute_ctx;

	/* If no compute context available or context is going करोwn
	 * स_रखो रेजिस्टरs directly
	 */
	अगर (!ctx || kref_पढ़ो(&ctx->refcount) == 0) अणु
		rc = gaudi_स_रखो_रेजिस्टरs(hdev, reg_base, num_regs, val);
		mutex_unlock(&hdev->fpriv_list_lock);
		वापस rc;
	पूर्ण

	mutex_unlock(&hdev->fpriv_list_lock);

	cb_size = (माप(*pkt) * num_regs) +
			माप(काष्ठा packet_msg_prot) * 2;

	अगर (cb_size > SZ_2M) अणु
		dev_err(hdev->dev, "CB size must be smaller than %uMB", SZ_2M);
		वापस -ENOMEM;
	पूर्ण

	pending_cb = kzalloc(माप(*pending_cb), GFP_KERNEL);
	अगर (!pending_cb)
		वापस -ENOMEM;

	cb = hl_cb_kernel_create(hdev, cb_size, false);
	अगर (!cb) अणु
		kमुक्त(pending_cb);
		वापस -EFAULT;
	पूर्ण

	pkt = cb->kernel_address;

	ctl = FIELD_PREP(GAUDI_PKT_LONG_CTL_OP_MASK, 0); /* ग_लिखो the value */
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_LONG);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	क्रम (i = 0; i < num_regs ; i++, pkt++) अणु
		pkt->ctl = cpu_to_le32(ctl);
		pkt->value = cpu_to_le32(val);
		pkt->addr = cpu_to_le64(reg_base + (i * 4));
	पूर्ण

	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	pending_cb->cb = cb;
	pending_cb->cb_size = cb_size;
	/* The queue ID MUST be an बाह्यal queue ID. Otherwise, we will
	 * have undefined behavior
	 */
	pending_cb->hw_queue_id = hw_queue_id;

	spin_lock(&ctx->pending_cb_lock);
	list_add_tail(&pending_cb->cb_node, &ctx->pending_cb_list);
	spin_unlock(&ctx->pending_cb_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_restore_sm_रेजिस्टरs(काष्ठा hl_device *hdev)
अणु
	u64 base_addr;
	u32 num_regs;
	पूर्णांक rc;

	base_addr = CFG_BASE + mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0;
	num_regs = NUM_OF_SOB_IN_BLOCK;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_E_S_SYNC_MNGR_OBJS_SOB_OBJ_0;
	num_regs = NUM_OF_SOB_IN_BLOCK;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_W_N_SYNC_MNGR_OBJS_SOB_OBJ_0;
	num_regs = NUM_OF_SOB_IN_BLOCK;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_STATUS_0;
	num_regs = NUM_OF_MONITORS_IN_BLOCK;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_E_S_SYNC_MNGR_OBJS_MON_STATUS_0;
	num_regs = NUM_OF_MONITORS_IN_BLOCK;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_W_N_SYNC_MNGR_OBJS_MON_STATUS_0;
	num_regs = NUM_OF_MONITORS_IN_BLOCK;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0 +
			(GAUDI_FIRST_AVAILABLE_W_S_SYNC_OBJECT * 4);
	num_regs = NUM_OF_SOB_IN_BLOCK - GAUDI_FIRST_AVAILABLE_W_S_SYNC_OBJECT;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	base_addr = CFG_BASE +  mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_STATUS_0 +
			(GAUDI_FIRST_AVAILABLE_W_S_MONITOR * 4);
	num_regs = NUM_OF_MONITORS_IN_BLOCK - GAUDI_FIRST_AVAILABLE_W_S_MONITOR;
	rc = gaudi_स_रखो_रेजिस्टरs(hdev, base_addr, num_regs, 0);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed resetting SM registers");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gaudi_restore_dma_रेजिस्टरs(काष्ठा hl_device *hdev)
अणु
	u32 sob_delta = mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_1 -
			mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0;
	पूर्णांक i;

	क्रम (i = 0 ; i < DMA_NUMBER_OF_CHANNELS ; i++) अणु
		u64 sob_addr = CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0 +
				(i * sob_delta);
		u32 dma_offset = i * DMA_CORE_OFFSET;

		WREG32(mmDMA0_CORE_WR_COMP_ADDR_LO + dma_offset,
				lower_32_bits(sob_addr));
		WREG32(mmDMA0_CORE_WR_COMP_ADDR_HI + dma_offset,
				upper_32_bits(sob_addr));
		WREG32(mmDMA0_CORE_WR_COMP_WDATA + dma_offset, 0x80000001);

		/* For DMAs 2-7, need to restore WR_AWUSER_31_11 as it can be
		 * modअगरied by the user क्रम SRAM reduction
		 */
		अगर (i > 1)
			WREG32(mmDMA0_CORE_WR_AWUSER_31_11 + dma_offset,
								0x00000001);
	पूर्ण
पूर्ण

अटल व्योम gaudi_restore_qm_रेजिस्टरs(काष्ठा hl_device *hdev)
अणु
	u32 qman_offset;
	पूर्णांक i;

	क्रम (i = 0 ; i < DMA_NUMBER_OF_CHANNELS ; i++) अणु
		qman_offset = i * DMA_QMAN_OFFSET;
		WREG32(mmDMA0_QM_ARB_CFG_0 + qman_offset, 0);
	पूर्ण

	क्रम (i = 0 ; i < MME_NUMBER_OF_MASTER_ENGINES ; i++) अणु
		qman_offset = i * (mmMME2_QM_BASE - mmMME0_QM_BASE);
		WREG32(mmMME0_QM_ARB_CFG_0 + qman_offset, 0);
	पूर्ण

	क्रम (i = 0 ; i < TPC_NUMBER_OF_ENGINES ; i++) अणु
		qman_offset = i * TPC_QMAN_OFFSET;
		WREG32(mmTPC0_QM_ARB_CFG_0 + qman_offset, 0);
	पूर्ण

	क्रम (i = 0 ; i < NIC_NUMBER_OF_ENGINES ; i++) अणु
		qman_offset = (i >> 1) * NIC_MACRO_QMAN_OFFSET +
				(i & 0x1) * NIC_ENGINE_QMAN_OFFSET;
		WREG32(mmNIC0_QM0_ARB_CFG_0 + qman_offset, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक gaudi_restore_user_रेजिस्टरs(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	rc = gaudi_restore_sm_रेजिस्टरs(hdev);
	अगर (rc)
		वापस rc;

	gaudi_restore_dma_रेजिस्टरs(hdev);
	gaudi_restore_qm_रेजिस्टरs(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_context_चयन(काष्ठा hl_device *hdev, u32 asid)
अणु
	वापस gaudi_restore_user_रेजिस्टरs(hdev);
पूर्ण

अटल पूर्णांक gaudi_mmu_clear_pgt_range(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 addr = prop->mmu_pgt_addr;
	u32 size = prop->mmu_pgt_size + MMU_CACHE_MNG_SIZE;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU))
		वापस 0;

	वापस gaudi_स_रखो_device_memory(hdev, addr, size, 0);
पूर्ण

अटल व्योम gaudi_restore_phase_topology(काष्ठा hl_device *hdev)
अणु

पूर्ण

अटल पूर्णांक gaudi_debugfs_पढ़ो32(काष्ठा hl_device *hdev, u64 addr,
			bool user_address, u32 *val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 hbm_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr < CFG_BASE + CFG_SIZE)) अणु

		अगर ((gaudi->hw_cap_initialized & HW_CAP_CLK_GATE) &&
				(hdev->घड़ी_gating_mask &
						GAUDI_CLK_GATE_DEBUGFS_MASK)) अणु

			dev_err_ratelimited(hdev->dev,
				"Can't read register - clock gating is enabled!\n");
			rc = -EFAULT;
		पूर्ण अन्यथा अणु
			*val = RREG32(addr - CFG_BASE);
		पूर्ण

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
			(addr < SRAM_BASE_ADDR + SRAM_BAR_SIZE)) अणु
		*val = पढ़ोl(hdev->pcie_bar[SRAM_BAR_ID] +
				(addr - SRAM_BASE_ADDR));
	पूर्ण अन्यथा अगर (addr < DRAM_PHYS_BASE + hdev->asic_prop.dram_size) अणु
		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		hbm_bar_addr = gaudi_set_hbm_bar_base(hdev, bar_base_addr);
		अगर (hbm_bar_addr != U64_MAX) अणु
			*val = पढ़ोl(hdev->pcie_bar[HBM_BAR_ID] +
						(addr - bar_base_addr));

			hbm_bar_addr = gaudi_set_hbm_bar_base(hdev,
						hbm_bar_addr);
		पूर्ण
		अगर (hbm_bar_addr == U64_MAX)
			rc = -EIO;
	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*val = *(u32 *) phys_to_virt(addr - HOST_PHYS_BASE);
	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_debugfs_ग_लिखो32(काष्ठा hl_device *hdev, u64 addr,
			bool user_address, u32 val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 hbm_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr < CFG_BASE + CFG_SIZE)) अणु

		अगर ((gaudi->hw_cap_initialized & HW_CAP_CLK_GATE) &&
				(hdev->घड़ी_gating_mask &
						GAUDI_CLK_GATE_DEBUGFS_MASK)) अणु

			dev_err_ratelimited(hdev->dev,
				"Can't write register - clock gating is enabled!\n");
			rc = -EFAULT;
		पूर्ण अन्यथा अणु
			WREG32(addr - CFG_BASE, val);
		पूर्ण

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
			(addr < SRAM_BASE_ADDR + SRAM_BAR_SIZE)) अणु
		ग_लिखोl(val, hdev->pcie_bar[SRAM_BAR_ID] +
					(addr - SRAM_BASE_ADDR));
	पूर्ण अन्यथा अगर (addr < DRAM_PHYS_BASE + hdev->asic_prop.dram_size) अणु
		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		hbm_bar_addr = gaudi_set_hbm_bar_base(hdev, bar_base_addr);
		अगर (hbm_bar_addr != U64_MAX) अणु
			ग_लिखोl(val, hdev->pcie_bar[HBM_BAR_ID] +
						(addr - bar_base_addr));

			hbm_bar_addr = gaudi_set_hbm_bar_base(hdev,
						hbm_bar_addr);
		पूर्ण
		अगर (hbm_bar_addr == U64_MAX)
			rc = -EIO;
	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*(u32 *) phys_to_virt(addr - HOST_PHYS_BASE) = val;
	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_debugfs_पढ़ो64(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u64 *val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 hbm_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr <= CFG_BASE + CFG_SIZE - माप(u64))) अणु

		अगर ((gaudi->hw_cap_initialized & HW_CAP_CLK_GATE) &&
				(hdev->घड़ी_gating_mask &
						GAUDI_CLK_GATE_DEBUGFS_MASK)) अणु

			dev_err_ratelimited(hdev->dev,
				"Can't read register - clock gating is enabled!\n");
			rc = -EFAULT;
		पूर्ण अन्यथा अणु
			u32 val_l = RREG32(addr - CFG_BASE);
			u32 val_h = RREG32(addr + माप(u32) - CFG_BASE);

			*val = (((u64) val_h) << 32) | val_l;
		पूर्ण

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
		   (addr <= SRAM_BASE_ADDR + SRAM_BAR_SIZE - माप(u64))) अणु
		*val = पढ़ोq(hdev->pcie_bar[SRAM_BAR_ID] +
				(addr - SRAM_BASE_ADDR));
	पूर्ण अन्यथा अगर (addr <=
		    DRAM_PHYS_BASE + hdev->asic_prop.dram_size - माप(u64)) अणु
		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		hbm_bar_addr = gaudi_set_hbm_bar_base(hdev, bar_base_addr);
		अगर (hbm_bar_addr != U64_MAX) अणु
			*val = पढ़ोq(hdev->pcie_bar[HBM_BAR_ID] +
						(addr - bar_base_addr));

			hbm_bar_addr = gaudi_set_hbm_bar_base(hdev,
						hbm_bar_addr);
		पूर्ण
		अगर (hbm_bar_addr == U64_MAX)
			rc = -EIO;
	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*val = *(u64 *) phys_to_virt(addr - HOST_PHYS_BASE);
	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_debugfs_ग_लिखो64(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u64 val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 hbm_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr <= CFG_BASE + CFG_SIZE - माप(u64))) अणु

		अगर ((gaudi->hw_cap_initialized & HW_CAP_CLK_GATE) &&
				(hdev->घड़ी_gating_mask &
						GAUDI_CLK_GATE_DEBUGFS_MASK)) अणु

			dev_err_ratelimited(hdev->dev,
				"Can't write register - clock gating is enabled!\n");
			rc = -EFAULT;
		पूर्ण अन्यथा अणु
			WREG32(addr - CFG_BASE, lower_32_bits(val));
			WREG32(addr + माप(u32) - CFG_BASE,
				upper_32_bits(val));
		पूर्ण

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
		   (addr <= SRAM_BASE_ADDR + SRAM_BAR_SIZE - माप(u64))) अणु
		ग_लिखोq(val, hdev->pcie_bar[SRAM_BAR_ID] +
					(addr - SRAM_BASE_ADDR));
	पूर्ण अन्यथा अगर (addr <=
		    DRAM_PHYS_BASE + hdev->asic_prop.dram_size - माप(u64)) अणु
		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		hbm_bar_addr = gaudi_set_hbm_bar_base(hdev, bar_base_addr);
		अगर (hbm_bar_addr != U64_MAX) अणु
			ग_लिखोq(val, hdev->pcie_bar[HBM_BAR_ID] +
						(addr - bar_base_addr));

			hbm_bar_addr = gaudi_set_hbm_bar_base(hdev,
						hbm_bar_addr);
		पूर्ण
		अगर (hbm_bar_addr == U64_MAX)
			rc = -EIO;
	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*(u64 *) phys_to_virt(addr - HOST_PHYS_BASE) = val;
	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_dma_core_transfer(काष्ठा hl_device *hdev, पूर्णांक dma_id, u64 addr,
					u32 माप_प्रकारo_dma, dma_addr_t dma_addr)
अणु
	u32 err_cause, val;
	u64 dma_offset;
	पूर्णांक rc;

	dma_offset = dma_id * DMA_CORE_OFFSET;

	WREG32(mmDMA0_CORE_SRC_BASE_LO + dma_offset, lower_32_bits(addr));
	WREG32(mmDMA0_CORE_SRC_BASE_HI + dma_offset, upper_32_bits(addr));
	WREG32(mmDMA0_CORE_DST_BASE_LO + dma_offset, lower_32_bits(dma_addr));
	WREG32(mmDMA0_CORE_DST_BASE_HI + dma_offset, upper_32_bits(dma_addr));
	WREG32(mmDMA0_CORE_DST_TSIZE_0 + dma_offset, माप_प्रकारo_dma);
	WREG32(mmDMA0_CORE_COMMIT + dma_offset,
			(1 << DMA0_CORE_COMMIT_LIN_SHIFT));

	rc = hl_poll_समयout(
		hdev,
		mmDMA0_CORE_STS0 + dma_offset,
		val,
		((val & DMA0_CORE_STS0_BUSY_MASK) == 0),
		0,
		1000000);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"DMA %d timed-out during reading of 0x%llx\n",
			dma_id, addr);
		वापस -EIO;
	पूर्ण

	/* Verअगरy DMA is OK */
	err_cause = RREG32(mmDMA0_CORE_ERR_CAUSE + dma_offset);
	अगर (err_cause) अणु
		dev_err(hdev->dev, "DMA Failed, cause 0x%x\n", err_cause);
		dev_dbg(hdev->dev,
			"Clearing DMA0 engine from errors (cause 0x%x)\n",
			err_cause);
		WREG32(mmDMA0_CORE_ERR_CAUSE + dma_offset, err_cause);

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_debugfs_पढ़ो_dma(काष्ठा hl_device *hdev, u64 addr, u32 size,
				व्योम *blob_addr)
अणु
	u32 dma_core_sts0, err_cause, cfg1, size_left, pos, माप_प्रकारo_dma;
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 dma_offset, qm_offset;
	dma_addr_t dma_addr;
	व्योम *kernel_addr;
	bool is_eng_idle;
	पूर्णांक rc = 0, dma_id;

	kernel_addr = hdev->asic_funcs->asic_dma_alloc_coherent(
						hdev, SZ_2M,
						&dma_addr,
						GFP_KERNEL | __GFP_ZERO);

	अगर (!kernel_addr)
		वापस -ENOMEM;

	mutex_lock(&gaudi->clk_gate_mutex);

	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	hdev->asic_funcs->hw_queues_lock(hdev);

	dma_id = gaudi_dma_assignment[GAUDI_PCI_DMA_1];
	dma_offset = dma_id * DMA_CORE_OFFSET;
	qm_offset = dma_id * DMA_QMAN_OFFSET;
	dma_core_sts0 = RREG32(mmDMA0_CORE_STS0 + dma_offset);
	is_eng_idle = IS_DMA_IDLE(dma_core_sts0);

	अगर (!is_eng_idle) अणु
		dma_id = gaudi_dma_assignment[GAUDI_PCI_DMA_2];
		dma_offset = dma_id * DMA_CORE_OFFSET;
		qm_offset = dma_id * DMA_QMAN_OFFSET;
		dma_core_sts0 = RREG32(mmDMA0_CORE_STS0 + dma_offset);
		is_eng_idle = IS_DMA_IDLE(dma_core_sts0);

		अगर (!is_eng_idle) अणु
			dev_err_ratelimited(hdev->dev,
				"Can't read via DMA because it is BUSY\n");
			rc = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण

	cfg1 = RREG32(mmDMA0_QM_GLBL_CFG1 + qm_offset);
	WREG32(mmDMA0_QM_GLBL_CFG1 + qm_offset,
			0xF << DMA0_QM_GLBL_CFG1_CP_STOP_SHIFT);

	/* TODO: हटाओ this by mapping the DMA temporary buffer to the MMU
	 * using the compute ctx ASID, अगर exists. If not, use the kernel ctx
	 * ASID
	 */
	WREG32_OR(mmDMA0_CORE_PROT + dma_offset, BIT(DMA0_CORE_PROT_VAL_SHIFT));

	/* Verअगरy DMA is OK */
	err_cause = RREG32(mmDMA0_CORE_ERR_CAUSE + dma_offset);
	अगर (err_cause) अणु
		dev_dbg(hdev->dev,
			"Clearing DMA0 engine from errors (cause 0x%x)\n",
			err_cause);
		WREG32(mmDMA0_CORE_ERR_CAUSE + dma_offset, err_cause);
	पूर्ण

	pos = 0;
	size_left = size;
	माप_प्रकारo_dma = SZ_2M;

	जबतक (size_left > 0) अणु

		अगर (size_left < SZ_2M)
			माप_प्रकारo_dma = size_left;

		rc = gaudi_dma_core_transfer(hdev, dma_id, addr, माप_प्रकारo_dma,
						dma_addr);
		अगर (rc)
			अवरोध;

		स_नकल(blob_addr + pos, kernel_addr, माप_प्रकारo_dma);

		अगर (size_left <= SZ_2M)
			अवरोध;

		pos += SZ_2M;
		addr += SZ_2M;
		size_left -= SZ_2M;
	पूर्ण

	/* TODO: हटाओ this by mapping the DMA temporary buffer to the MMU
	 * using the compute ctx ASID, अगर exists. If not, use the kernel ctx
	 * ASID
	 */
	WREG32_AND(mmDMA0_CORE_PROT + dma_offset,
			~BIT(DMA0_CORE_PROT_VAL_SHIFT));

	WREG32(mmDMA0_QM_GLBL_CFG1 + qm_offset, cfg1);

out:
	hdev->asic_funcs->hw_queues_unlock(hdev);

	hdev->asic_funcs->set_घड़ी_gating(hdev);

	mutex_unlock(&gaudi->clk_gate_mutex);

	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev, SZ_2M, kernel_addr,
						dma_addr);

	वापस rc;
पूर्ण

अटल u64 gaudi_पढ़ो_pte(काष्ठा hl_device *hdev, u64 addr)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (hdev->hard_reset_pending)
		वापस U64_MAX;

	वापस पढ़ोq(hdev->pcie_bar[HBM_BAR_ID] +
			(addr - gaudi->hbm_bar_cur_addr));
पूर्ण

अटल व्योम gaudi_ग_लिखो_pte(काष्ठा hl_device *hdev, u64 addr, u64 val)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (hdev->hard_reset_pending)
		वापस;

	ग_लिखोq(val, hdev->pcie_bar[HBM_BAR_ID] +
			(addr - gaudi->hbm_bar_cur_addr));
पूर्ण

व्योम gaudi_mmu_prepare_reg(काष्ठा hl_device *hdev, u64 reg, u32 asid)
अणु
	/* mask to zero the MMBP and ASID bits */
	WREG32_AND(reg, ~0x7FF);
	WREG32_OR(reg, asid);
पूर्ण

अटल व्योम gaudi_mmu_prepare(काष्ठा hl_device *hdev, u32 asid)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	अगर (asid & ~DMA0_QM_GLBL_NON_SECURE_PROPS_0_ASID_MASK) अणु
		dev_crit(hdev->dev, "asid %u is too big\n", asid);
		वापस;
	पूर्ण

	mutex_lock(&gaudi->clk_gate_mutex);

	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	gaudi_mmu_prepare_reg(hdev, mmDMA0_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA0_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA0_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA0_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA0_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA1_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA1_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA1_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA1_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA1_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA2_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA2_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA2_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA2_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA2_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA3_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA3_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA3_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA3_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA3_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA4_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA4_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA4_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA4_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA4_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA5_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA5_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA5_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA5_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA5_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA6_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA6_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA6_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA6_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA6_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA7_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA7_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA7_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA7_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA7_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmDMA0_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA1_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA2_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA3_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA4_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA5_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA6_CORE_NON_SECURE_PROPS, asid);
	gaudi_mmu_prepare_reg(hdev, mmDMA7_CORE_NON_SECURE_PROPS, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC0_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC0_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC0_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC0_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC0_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC0_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC0_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC1_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC1_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC1_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC1_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC1_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC1_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC1_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC2_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC2_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC2_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC2_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC2_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC2_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC2_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC3_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC3_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC3_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC3_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC3_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC3_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC3_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC4_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC4_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC4_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC4_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC4_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC4_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC4_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC5_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC5_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC5_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC5_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC5_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC5_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC5_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC6_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC6_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC6_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC6_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC6_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC6_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC6_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmTPC7_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC7_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC7_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC7_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC7_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC7_CFG_ARUSER_LO, asid);
	gaudi_mmu_prepare_reg(hdev, mmTPC7_CFG_AWUSER_LO, asid);

	gaudi_mmu_prepare_reg(hdev, mmMME0_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME0_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME0_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME0_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME0_QM_GLBL_NON_SECURE_PROPS_4, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_QM_GLBL_NON_SECURE_PROPS_0, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_QM_GLBL_NON_SECURE_PROPS_1, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_QM_GLBL_NON_SECURE_PROPS_2, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_QM_GLBL_NON_SECURE_PROPS_3, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_QM_GLBL_NON_SECURE_PROPS_4, asid);

	gaudi_mmu_prepare_reg(hdev, mmMME0_SBAB_ARUSER0, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME0_SBAB_ARUSER1, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME1_SBAB_ARUSER0, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME1_SBAB_ARUSER1, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_SBAB_ARUSER0, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_SBAB_ARUSER1, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME3_SBAB_ARUSER0, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME3_SBAB_ARUSER1, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME0_ACC_WBC, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME1_ACC_WBC, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME2_ACC_WBC, asid);
	gaudi_mmu_prepare_reg(hdev, mmMME3_ACC_WBC, asid);

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC0) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM0_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM0_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM0_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM0_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM0_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC1) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM1_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM1_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM1_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM1_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC0_QM1_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC2) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM0_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM0_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM0_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM0_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM0_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC3) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM1_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM1_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM1_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM1_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC1_QM1_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC4) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM0_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM0_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM0_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM0_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM0_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC5) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM1_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM1_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM1_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM1_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC2_QM1_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC6) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM0_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM0_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM0_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM0_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM0_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC7) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM1_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM1_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM1_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM1_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC3_QM1_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC8) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM0_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM0_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM0_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM0_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM0_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	अगर (hdev->nic_ports_mask & GAUDI_NIC_MASK_NIC9) अणु
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM1_GLBL_NON_SECURE_PROPS_0,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM1_GLBL_NON_SECURE_PROPS_1,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM1_GLBL_NON_SECURE_PROPS_2,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM1_GLBL_NON_SECURE_PROPS_3,
				asid);
		gaudi_mmu_prepare_reg(hdev, mmNIC4_QM1_GLBL_NON_SECURE_PROPS_4,
				asid);
	पूर्ण

	hdev->asic_funcs->set_घड़ी_gating(hdev);

	mutex_unlock(&gaudi->clk_gate_mutex);
पूर्ण

अटल पूर्णांक gaudi_send_job_on_qman0(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_job *job)
अणु
	काष्ठा packet_msg_prot *fence_pkt;
	u32 *fence_ptr;
	dma_addr_t fence_dma_addr;
	काष्ठा hl_cb *cb;
	u32 पंचांगp, समयout, dma_offset;
	पूर्णांक rc;

	अगर (hdev->pldm)
		समयout = GAUDI_PLDM_QMAN0_TIMEOUT_USEC;
	अन्यथा
		समयout = HL_DEVICE_TIMEOUT_USEC;

	अगर (!hdev->asic_funcs->is_device_idle(hdev, शून्य, 0, शून्य)) अणु
		dev_err_ratelimited(hdev->dev,
			"Can't send driver job on QMAN0 because the device is not idle\n");
		वापस -EBUSY;
	पूर्ण

	fence_ptr = hdev->asic_funcs->asic_dma_pool_zalloc(hdev, 4, GFP_KERNEL,
							&fence_dma_addr);
	अगर (!fence_ptr) अणु
		dev_err(hdev->dev,
			"Failed to allocate fence memory for QMAN0\n");
		वापस -ENOMEM;
	पूर्ण

	cb = job->patched_cb;

	fence_pkt = cb->kernel_address +
			job->job_cb_size - माप(काष्ठा packet_msg_prot);

	पंचांगp = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_PROT);
	पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 1);
	पंचांगp |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	fence_pkt->ctl = cpu_to_le32(पंचांगp);
	fence_pkt->value = cpu_to_le32(GAUDI_QMAN0_FENCE_VAL);
	fence_pkt->addr = cpu_to_le64(fence_dma_addr);

	dma_offset = gaudi_dma_assignment[GAUDI_PCI_DMA_1] * DMA_CORE_OFFSET;

	WREG32_OR(mmDMA0_CORE_PROT + dma_offset, BIT(DMA0_CORE_PROT_VAL_SHIFT));

	rc = hl_hw_queue_send_cb_no_cmpl(hdev, GAUDI_QUEUE_ID_DMA_0_0,
					job->job_cb_size, cb->bus_address);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to send CB on QMAN0, %d\n", rc);
		जाओ मुक्त_fence_ptr;
	पूर्ण

	rc = hl_poll_समयout_memory(hdev, fence_ptr, पंचांगp,
				(पंचांगp == GAUDI_QMAN0_FENCE_VAL), 1000,
				समयout, true);

	hl_hw_queue_inc_ci_kernel(hdev, GAUDI_QUEUE_ID_DMA_0_0);

	अगर (rc == -ETIMEDOUT) अणु
		dev_err(hdev->dev, "QMAN0 Job timeout (0x%x)\n", पंचांगp);
		जाओ मुक्त_fence_ptr;
	पूर्ण

मुक्त_fence_ptr:
	WREG32_AND(mmDMA0_CORE_PROT + dma_offset,
			~BIT(DMA0_CORE_PROT_VAL_SHIFT));

	hdev->asic_funcs->asic_dma_pool_मुक्त(hdev, (व्योम *) fence_ptr,
					fence_dma_addr);
	वापस rc;
पूर्ण

अटल व्योम gaudi_get_event_desc(u16 event_type, अक्षर *desc, माप_प्रकार size)
अणु
	अगर (event_type >= GAUDI_EVENT_SIZE)
		जाओ event_not_supported;

	अगर (!gaudi_irq_map_table[event_type].valid)
		जाओ event_not_supported;

	snम_लिखो(desc, size, gaudi_irq_map_table[event_type].name);

	वापस;

event_not_supported:
	snम_लिखो(desc, size, "N/A");
पूर्ण

अटल स्थिर अक्षर *gaudi_get_razwi_initiator_dma_name(काष्ठा hl_device *hdev,
							u32 x_y, bool is_ग_लिखो)
अणु
	u32 dma_id[2], dma_offset, err_cause[2], mask, i;

	mask = is_ग_लिखो ? DMA0_CORE_ERR_CAUSE_HBW_WR_ERR_MASK :
				DMA0_CORE_ERR_CAUSE_HBW_RD_ERR_MASK;

	चयन (x_y) अणु
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_S_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_S_1:
		dma_id[0] = 0;
		dma_id[1] = 2;
		अवरोध;
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_S_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_S_1:
		dma_id[0] = 1;
		dma_id[1] = 3;
		अवरोध;
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_N_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_N_1:
		dma_id[0] = 4;
		dma_id[1] = 6;
		अवरोध;
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_N_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_N_1:
		dma_id[0] = 5;
		dma_id[1] = 7;
		अवरोध;
	शेष:
		जाओ unknown_initiator;
	पूर्ण

	क्रम (i = 0 ; i < 2 ; i++) अणु
		dma_offset = dma_id[i] * DMA_CORE_OFFSET;
		err_cause[i] = RREG32(mmDMA0_CORE_ERR_CAUSE + dma_offset);
	पूर्ण

	चयन (x_y) अणु
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_S_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_S_1:
		अगर ((err_cause[0] & mask) && !(err_cause[1] & mask))
			वापस "DMA0";
		अन्यथा अगर (!(err_cause[0] & mask) && (err_cause[1] & mask))
			वापस "DMA2";
		अन्यथा
			वापस "DMA0 or DMA2";
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_S_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_S_1:
		अगर ((err_cause[0] & mask) && !(err_cause[1] & mask))
			वापस "DMA1";
		अन्यथा अगर (!(err_cause[0] & mask) && (err_cause[1] & mask))
			वापस "DMA3";
		अन्यथा
			वापस "DMA1 or DMA3";
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_N_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_N_1:
		अगर ((err_cause[0] & mask) && !(err_cause[1] & mask))
			वापस "DMA4";
		अन्यथा अगर (!(err_cause[0] & mask) && (err_cause[1] & mask))
			वापस "DMA6";
		अन्यथा
			वापस "DMA4 or DMA6";
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_N_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_N_1:
		अगर ((err_cause[0] & mask) && !(err_cause[1] & mask))
			वापस "DMA5";
		अन्यथा अगर (!(err_cause[0] & mask) && (err_cause[1] & mask))
			वापस "DMA7";
		अन्यथा
			वापस "DMA5 or DMA7";
	पूर्ण

unknown_initiator:
	वापस "unknown initiator";
पूर्ण

अटल स्थिर अक्षर *gaudi_get_razwi_initiator_name(काष्ठा hl_device *hdev,
							bool is_ग_लिखो)
अणु
	u32 val, x_y, axi_id;

	val = is_ग_लिखो ? RREG32(mmMMU_UP_RAZWI_WRITE_ID) :
				RREG32(mmMMU_UP_RAZWI_READ_ID);
	x_y = val & ((RAZWI_INITIATOR_Y_MASK << RAZWI_INITIATOR_Y_SHIFT) |
			(RAZWI_INITIATOR_X_MASK << RAZWI_INITIATOR_X_SHIFT));
	axi_id = val & (RAZWI_INITIATOR_AXI_ID_MASK <<
			RAZWI_INITIATOR_AXI_ID_SHIFT);

	चयन (x_y) अणु
	हाल RAZWI_INITIATOR_ID_X_Y_TPC0_NIC0:
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_TPC))
			वापस "TPC0";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_NIC))
			वापस "NIC0";
		अवरोध;
	हाल RAZWI_INITIATOR_ID_X_Y_TPC1:
		वापस "TPC1";
	हाल RAZWI_INITIATOR_ID_X_Y_MME0_0:
	हाल RAZWI_INITIATOR_ID_X_Y_MME0_1:
		वापस "MME0";
	हाल RAZWI_INITIATOR_ID_X_Y_MME1_0:
	हाल RAZWI_INITIATOR_ID_X_Y_MME1_1:
		वापस "MME1";
	हाल RAZWI_INITIATOR_ID_X_Y_TPC2:
		वापस "TPC2";
	हाल RAZWI_INITIATOR_ID_X_Y_TPC3_PCI_CPU_PSOC:
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_TPC))
			वापस "TPC3";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_PCI))
			वापस "PCI";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_CPU))
			वापस "CPU";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_PSOC))
			वापस "PSOC";
		अवरोध;
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_S_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_S_1:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_S_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_S_1:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_N_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_W_N_1:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_N_0:
	हाल RAZWI_INITIATOR_ID_X_Y_DMA_IF_E_N_1:
		वापस gaudi_get_razwi_initiator_dma_name(hdev, x_y, is_ग_लिखो);
	हाल RAZWI_INITIATOR_ID_X_Y_TPC4_NIC1_NIC2:
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_TPC))
			वापस "TPC4";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_NIC))
			वापस "NIC1";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_NIC_FT))
			वापस "NIC2";
		अवरोध;
	हाल RAZWI_INITIATOR_ID_X_Y_TPC5:
		वापस "TPC5";
	हाल RAZWI_INITIATOR_ID_X_Y_MME2_0:
	हाल RAZWI_INITIATOR_ID_X_Y_MME2_1:
		वापस "MME2";
	हाल RAZWI_INITIATOR_ID_X_Y_MME3_0:
	हाल RAZWI_INITIATOR_ID_X_Y_MME3_1:
		वापस "MME3";
	हाल RAZWI_INITIATOR_ID_X_Y_TPC6:
		वापस "TPC6";
	हाल RAZWI_INITIATOR_ID_X_Y_TPC7_NIC4_NIC5:
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_TPC))
			वापस "TPC7";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_NIC))
			वापस "NIC4";
		अगर (axi_id == RAZWI_INITIATOR_ID_AXI_ID(AXI_ID_NIC_FT))
			वापस "NIC5";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_err(hdev->dev,
		"Unknown RAZWI initiator ID 0x%x [Y=%d, X=%d, AXI_ID=%d]\n",
		val,
		(val >> RAZWI_INITIATOR_Y_SHIFT) & RAZWI_INITIATOR_Y_MASK,
		(val >> RAZWI_INITIATOR_X_SHIFT) & RAZWI_INITIATOR_X_MASK,
		(val >> RAZWI_INITIATOR_AXI_ID_SHIFT) &
			RAZWI_INITIATOR_AXI_ID_MASK);

	वापस "unknown initiator";
पूर्ण

अटल व्योम gaudi_prपूर्णांक_razwi_info(काष्ठा hl_device *hdev)
अणु
	अगर (RREG32(mmMMU_UP_RAZWI_WRITE_VLD)) अणु
		dev_err_ratelimited(hdev->dev,
			"RAZWI event caused by illegal write of %s\n",
			gaudi_get_razwi_initiator_name(hdev, true));
		WREG32(mmMMU_UP_RAZWI_WRITE_VLD, 0);
	पूर्ण

	अगर (RREG32(mmMMU_UP_RAZWI_READ_VLD)) अणु
		dev_err_ratelimited(hdev->dev,
			"RAZWI event caused by illegal read of %s\n",
			gaudi_get_razwi_initiator_name(hdev, false));
		WREG32(mmMMU_UP_RAZWI_READ_VLD, 0);
	पूर्ण
पूर्ण

अटल व्योम gaudi_prपूर्णांक_mmu_error_info(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 addr;
	u32 val;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	val = RREG32(mmMMU_UP_PAGE_ERROR_CAPTURE);
	अगर (val & MMU_UP_PAGE_ERROR_CAPTURE_ENTRY_VALID_MASK) अणु
		addr = val & MMU_UP_PAGE_ERROR_CAPTURE_VA_49_32_MASK;
		addr <<= 32;
		addr |= RREG32(mmMMU_UP_PAGE_ERROR_CAPTURE_VA);

		dev_err_ratelimited(hdev->dev, "MMU page fault on va 0x%llx\n",
					addr);

		WREG32(mmMMU_UP_PAGE_ERROR_CAPTURE, 0);
	पूर्ण

	val = RREG32(mmMMU_UP_ACCESS_ERROR_CAPTURE);
	अगर (val & MMU_UP_ACCESS_ERROR_CAPTURE_ENTRY_VALID_MASK) अणु
		addr = val & MMU_UP_ACCESS_ERROR_CAPTURE_VA_49_32_MASK;
		addr <<= 32;
		addr |= RREG32(mmMMU_UP_ACCESS_ERROR_CAPTURE_VA);

		dev_err_ratelimited(hdev->dev,
				"MMU access error on va 0x%llx\n", addr);

		WREG32(mmMMU_UP_ACCESS_ERROR_CAPTURE, 0);
	पूर्ण
पूर्ण

/*
 *  +-------------------+------------------------------------------------------+
 *  | Configuration Reg |                     Description                      |
 *  |      Address      |                                                      |
 *  +-------------------+------------------------------------------------------+
 *  |  0xF30 - 0xF3F    |ECC single error indication (1 bit per memory wrapper)|
 *  |                   |0xF30 memory wrappers 31:0 (MSB to LSB)               |
 *  |                   |0xF34 memory wrappers 63:32                           |
 *  |                   |0xF38 memory wrappers 95:64                           |
 *  |                   |0xF3C memory wrappers 127:96                          |
 *  +-------------------+------------------------------------------------------+
 *  |  0xF40 - 0xF4F    |ECC द्विगुन error indication (1 bit per memory wrapper)|
 *  |                   |0xF40 memory wrappers 31:0 (MSB to LSB)               |
 *  |                   |0xF44 memory wrappers 63:32                           |
 *  |                   |0xF48 memory wrappers 95:64                           |
 *  |                   |0xF4C memory wrappers 127:96                          |
 *  +-------------------+------------------------------------------------------+
 */
अटल पूर्णांक gaudi_extract_ecc_info(काष्ठा hl_device *hdev,
		काष्ठा ecc_info_extract_params *params, u64 *ecc_address,
		u64 *ecc_syndrom, u8 *memory_wrapper_idx)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 i, num_mem_regs, reg, err_bit;
	u64 err_addr, err_word = 0;
	पूर्णांक rc = 0;

	num_mem_regs = params->num_memories / 32 +
			((params->num_memories % 32) ? 1 : 0);

	अगर (params->block_address >= CFG_BASE)
		params->block_address -= CFG_BASE;

	अगर (params->derr)
		err_addr = params->block_address + GAUDI_ECC_DERR0_OFFSET;
	अन्यथा
		err_addr = params->block_address + GAUDI_ECC_SERR0_OFFSET;

	अगर (params->disable_घड़ी_gating) अणु
		mutex_lock(&gaudi->clk_gate_mutex);
		hdev->asic_funcs->disable_घड़ी_gating(hdev);
	पूर्ण

	/* Set invalid wrapper index */
	*memory_wrapper_idx = 0xFF;

	/* Iterate through memory wrappers, a single bit must be set */
	क्रम (i = 0 ; i < num_mem_regs ; i++) अणु
		err_addr += i * 4;
		err_word = RREG32(err_addr);
		अगर (err_word) अणु
			err_bit = __ffs(err_word);
			*memory_wrapper_idx = err_bit + (32 * i);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*memory_wrapper_idx == 0xFF) अणु
		dev_err(hdev->dev, "ECC error information cannot be found\n");
		rc = -EINVAL;
		जाओ enable_clk_gate;
	पूर्ण

	WREG32(params->block_address + GAUDI_ECC_MEM_SEL_OFFSET,
			*memory_wrapper_idx);

	*ecc_address =
		RREG32(params->block_address + GAUDI_ECC_ADDRESS_OFFSET);
	*ecc_syndrom =
		RREG32(params->block_address + GAUDI_ECC_SYNDROME_OFFSET);

	/* Clear error indication */
	reg = RREG32(params->block_address + GAUDI_ECC_MEM_INFO_CLR_OFFSET);
	अगर (params->derr)
		reg |= FIELD_PREP(GAUDI_ECC_MEM_INFO_CLR_DERR_MASK, 1);
	अन्यथा
		reg |= FIELD_PREP(GAUDI_ECC_MEM_INFO_CLR_SERR_MASK, 1);

	WREG32(params->block_address + GAUDI_ECC_MEM_INFO_CLR_OFFSET, reg);

enable_clk_gate:
	अगर (params->disable_घड़ी_gating) अणु
		hdev->asic_funcs->set_घड़ी_gating(hdev);

		mutex_unlock(&gaudi->clk_gate_mutex);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम gaudi_handle_qman_err_generic(काष्ठा hl_device *hdev,
					  स्थिर अक्षर *qm_name,
					  u64 glbl_sts_addr,
					  u64 arb_err_addr)
अणु
	u32 i, j, glbl_sts_val, arb_err_val, glbl_sts_clr_val;
	अक्षर reg_desc[32];

	/* Iterate through all stream GLBL_STS1 रेजिस्टरs + Lower CP */
	क्रम (i = 0 ; i < QMAN_STREAMS + 1 ; i++) अणु
		glbl_sts_clr_val = 0;
		glbl_sts_val = RREG32(glbl_sts_addr + 4 * i);

		अगर (!glbl_sts_val)
			जारी;

		अगर (i == QMAN_STREAMS)
			snम_लिखो(reg_desc, ARRAY_SIZE(reg_desc), "LowerCP");
		अन्यथा
			snम_लिखो(reg_desc, ARRAY_SIZE(reg_desc), "stream%u", i);

		क्रम (j = 0 ; j < GAUDI_NUM_OF_QM_ERR_CAUSE ; j++) अणु
			अगर (glbl_sts_val & BIT(j)) अणु
				dev_err_ratelimited(hdev->dev,
						"%s %s. err cause: %s\n",
						qm_name, reg_desc,
						gaudi_qman_error_cause[j]);
				glbl_sts_clr_val |= BIT(j);
			पूर्ण
		पूर्ण

		/* Write 1 clear errors */
		अगर (!hdev->stop_on_err)
			WREG32(glbl_sts_addr + 4 * i, glbl_sts_clr_val);
	पूर्ण

	arb_err_val = RREG32(arb_err_addr);

	अगर (!arb_err_val)
		वापस;

	क्रम (j = 0 ; j < GAUDI_NUM_OF_QM_ARB_ERR_CAUSE ; j++) अणु
		अगर (arb_err_val & BIT(j)) अणु
			dev_err_ratelimited(hdev->dev,
					"%s ARB_ERR. err cause: %s\n",
					qm_name,
					gaudi_qman_arb_error_cause[j]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gaudi_prपूर्णांक_sm_sei_info(काष्ठा hl_device *hdev, u16 event_type,
		काष्ठा hl_eq_sm_sei_data *sei_data)
अणु
	u32 index = event_type - GAUDI_EVENT_DMA_IF_SEI_0;

	चयन (sei_data->sei_cause) अणु
	हाल SM_SEI_SO_OVERFLOW:
		dev_err(hdev->dev,
			"SM %u SEI Error: SO %u overflow/underflow",
			index, le32_to_cpu(sei_data->sei_log));
		अवरोध;
	हाल SM_SEI_LBW_4B_UNALIGNED:
		dev_err(hdev->dev,
			"SM %u SEI Error: Unaligned 4B LBW access, monitor agent address low - %#x",
			index, le32_to_cpu(sei_data->sei_log));
		अवरोध;
	हाल SM_SEI_AXI_RESPONSE_ERR:
		dev_err(hdev->dev,
			"SM %u SEI Error: AXI ID %u response error",
			index, le32_to_cpu(sei_data->sei_log));
		अवरोध;
	शेष:
		dev_err(hdev->dev, "Unknown SM SEI cause %u",
				le32_to_cpu(sei_data->sei_log));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gaudi_handle_ecc_event(काष्ठा hl_device *hdev, u16 event_type,
		काष्ठा hl_eq_ecc_data *ecc_data)
अणु
	काष्ठा ecc_info_extract_params params;
	u64 ecc_address = 0, ecc_syndrom = 0;
	u8 index, memory_wrapper_idx = 0;
	bool extract_info_from_fw;
	पूर्णांक rc;

	चयन (event_type) अणु
	हाल GAUDI_EVENT_PCIE_CORE_SERR ... GAUDI_EVENT_PCIE_PHY_DERR:
	हाल GAUDI_EVENT_DMA0_SERR_ECC ... GAUDI_EVENT_MMU_DERR:
		extract_info_from_fw = true;
		अवरोध;
	हाल GAUDI_EVENT_TPC0_SERR ... GAUDI_EVENT_TPC7_SERR:
		index = event_type - GAUDI_EVENT_TPC0_SERR;
		params.block_address = mmTPC0_CFG_BASE + index * TPC_CFG_OFFSET;
		params.num_memories = 90;
		params.derr = false;
		params.disable_घड़ी_gating = true;
		extract_info_from_fw = false;
		अवरोध;
	हाल GAUDI_EVENT_TPC0_DERR ... GAUDI_EVENT_TPC7_DERR:
		index = event_type - GAUDI_EVENT_TPC0_DERR;
		params.block_address =
			mmTPC0_CFG_BASE + index * TPC_CFG_OFFSET;
		params.num_memories = 90;
		params.derr = true;
		params.disable_घड़ी_gating = true;
		extract_info_from_fw = false;
		अवरोध;
	हाल GAUDI_EVENT_MME0_ACC_SERR:
	हाल GAUDI_EVENT_MME1_ACC_SERR:
	हाल GAUDI_EVENT_MME2_ACC_SERR:
	हाल GAUDI_EVENT_MME3_ACC_SERR:
		index = (event_type - GAUDI_EVENT_MME0_ACC_SERR) / 4;
		params.block_address = mmMME0_ACC_BASE + index * MME_ACC_OFFSET;
		params.num_memories = 128;
		params.derr = false;
		params.disable_घड़ी_gating = true;
		extract_info_from_fw = false;
		अवरोध;
	हाल GAUDI_EVENT_MME0_ACC_DERR:
	हाल GAUDI_EVENT_MME1_ACC_DERR:
	हाल GAUDI_EVENT_MME2_ACC_DERR:
	हाल GAUDI_EVENT_MME3_ACC_DERR:
		index = (event_type - GAUDI_EVENT_MME0_ACC_DERR) / 4;
		params.block_address = mmMME0_ACC_BASE + index * MME_ACC_OFFSET;
		params.num_memories = 128;
		params.derr = true;
		params.disable_घड़ी_gating = true;
		extract_info_from_fw = false;
		अवरोध;
	हाल GAUDI_EVENT_MME0_SBAB_SERR:
	हाल GAUDI_EVENT_MME1_SBAB_SERR:
	हाल GAUDI_EVENT_MME2_SBAB_SERR:
	हाल GAUDI_EVENT_MME3_SBAB_SERR:
		index = (event_type - GAUDI_EVENT_MME0_SBAB_SERR) / 4;
		params.block_address =
			mmMME0_SBAB_BASE + index * MME_ACC_OFFSET;
		params.num_memories = 33;
		params.derr = false;
		params.disable_घड़ी_gating = true;
		extract_info_from_fw = false;
		अवरोध;
	हाल GAUDI_EVENT_MME0_SBAB_DERR:
	हाल GAUDI_EVENT_MME1_SBAB_DERR:
	हाल GAUDI_EVENT_MME2_SBAB_DERR:
	हाल GAUDI_EVENT_MME3_SBAB_DERR:
		index = (event_type - GAUDI_EVENT_MME0_SBAB_DERR) / 4;
		params.block_address =
			mmMME0_SBAB_BASE + index * MME_ACC_OFFSET;
		params.num_memories = 33;
		params.derr = true;
		params.disable_घड़ी_gating = true;
		extract_info_from_fw = false;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (extract_info_from_fw) अणु
		ecc_address = le64_to_cpu(ecc_data->ecc_address);
		ecc_syndrom = le64_to_cpu(ecc_data->ecc_syndrom);
		memory_wrapper_idx = ecc_data->memory_wrapper_idx;
	पूर्ण अन्यथा अणु
		rc = gaudi_extract_ecc_info(hdev, &params, &ecc_address,
				&ecc_syndrom, &memory_wrapper_idx);
		अगर (rc)
			वापस;
	पूर्ण

	dev_err(hdev->dev,
		"ECC error detected. address: %#llx. Syndrom: %#llx. block id %u\n",
		ecc_address, ecc_syndrom, memory_wrapper_idx);
पूर्ण

अटल व्योम gaudi_handle_qman_err(काष्ठा hl_device *hdev, u16 event_type)
अणु
	u64 glbl_sts_addr, arb_err_addr;
	u8 index;
	अक्षर desc[32];

	चयन (event_type) अणु
	हाल GAUDI_EVENT_TPC0_QM ... GAUDI_EVENT_TPC7_QM:
		index = event_type - GAUDI_EVENT_TPC0_QM;
		glbl_sts_addr =
			mmTPC0_QM_GLBL_STS1_0 + index * TPC_QMAN_OFFSET;
		arb_err_addr =
			mmTPC0_QM_ARB_ERR_CAUSE + index * TPC_QMAN_OFFSET;
		snम_लिखो(desc, ARRAY_SIZE(desc), "%s%d", "TPC_QM", index);
		अवरोध;
	हाल GAUDI_EVENT_MME0_QM ... GAUDI_EVENT_MME2_QM:
		index = event_type - GAUDI_EVENT_MME0_QM;
		glbl_sts_addr =
			mmMME0_QM_GLBL_STS1_0 + index * MME_QMAN_OFFSET;
		arb_err_addr =
			mmMME0_QM_ARB_ERR_CAUSE + index * MME_QMAN_OFFSET;
		snम_लिखो(desc, ARRAY_SIZE(desc), "%s%d", "MME_QM", index);
		अवरोध;
	हाल GAUDI_EVENT_DMA0_QM ... GAUDI_EVENT_DMA7_QM:
		index = event_type - GAUDI_EVENT_DMA0_QM;
		glbl_sts_addr =
			mmDMA0_QM_GLBL_STS1_0 + index * DMA_QMAN_OFFSET;
		arb_err_addr =
			mmDMA0_QM_ARB_ERR_CAUSE + index * DMA_QMAN_OFFSET;
		snम_लिखो(desc, ARRAY_SIZE(desc), "%s%d", "DMA_QM", index);
		अवरोध;
	हाल GAUDI_EVENT_NIC0_QM0:
		glbl_sts_addr = mmNIC0_QM0_GLBL_STS1_0;
		arb_err_addr = mmNIC0_QM0_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC0_QM0");
		अवरोध;
	हाल GAUDI_EVENT_NIC0_QM1:
		glbl_sts_addr = mmNIC0_QM1_GLBL_STS1_0;
		arb_err_addr = mmNIC0_QM1_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC0_QM1");
		अवरोध;
	हाल GAUDI_EVENT_NIC1_QM0:
		glbl_sts_addr = mmNIC1_QM0_GLBL_STS1_0;
		arb_err_addr = mmNIC1_QM0_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC1_QM0");
		अवरोध;
	हाल GAUDI_EVENT_NIC1_QM1:
		glbl_sts_addr = mmNIC1_QM1_GLBL_STS1_0;
		arb_err_addr = mmNIC1_QM1_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC1_QM1");
		अवरोध;
	हाल GAUDI_EVENT_NIC2_QM0:
		glbl_sts_addr = mmNIC2_QM0_GLBL_STS1_0;
		arb_err_addr = mmNIC2_QM0_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC2_QM0");
		अवरोध;
	हाल GAUDI_EVENT_NIC2_QM1:
		glbl_sts_addr = mmNIC2_QM1_GLBL_STS1_0;
		arb_err_addr = mmNIC2_QM1_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC2_QM1");
		अवरोध;
	हाल GAUDI_EVENT_NIC3_QM0:
		glbl_sts_addr = mmNIC3_QM0_GLBL_STS1_0;
		arb_err_addr = mmNIC3_QM0_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC3_QM0");
		अवरोध;
	हाल GAUDI_EVENT_NIC3_QM1:
		glbl_sts_addr = mmNIC3_QM1_GLBL_STS1_0;
		arb_err_addr = mmNIC3_QM1_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC3_QM1");
		अवरोध;
	हाल GAUDI_EVENT_NIC4_QM0:
		glbl_sts_addr = mmNIC4_QM0_GLBL_STS1_0;
		arb_err_addr = mmNIC4_QM0_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC4_QM0");
		अवरोध;
	हाल GAUDI_EVENT_NIC4_QM1:
		glbl_sts_addr = mmNIC4_QM1_GLBL_STS1_0;
		arb_err_addr = mmNIC4_QM1_ARB_ERR_CAUSE;
		snम_लिखो(desc, ARRAY_SIZE(desc), "NIC4_QM1");
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	gaudi_handle_qman_err_generic(hdev, desc, glbl_sts_addr, arb_err_addr);
पूर्ण

अटल व्योम gaudi_prपूर्णांक_irq_info(काष्ठा hl_device *hdev, u16 event_type,
					bool razwi)
अणु
	अक्षर desc[64] = "";

	gaudi_get_event_desc(event_type, desc, माप(desc));
	dev_err_ratelimited(hdev->dev, "Received H/W interrupt %d [\"%s\"]\n",
		event_type, desc);

	अगर (razwi) अणु
		gaudi_prपूर्णांक_razwi_info(hdev);
		gaudi_prपूर्णांक_mmu_error_info(hdev);
	पूर्ण
पूर्ण

अटल व्योम gaudi_prपूर्णांक_out_of_sync_info(काष्ठा hl_device *hdev,
					काष्ठा cpucp_pkt_sync_err *sync_err)
अणु
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[GAUDI_QUEUE_ID_CPU_PQ];

	dev_err(hdev->dev, "Out of sync with FW, FW: pi=%u, ci=%u, LKD: pi=%u, ci=%u\n",
			sync_err->pi, sync_err->ci, q->pi, atomic_पढ़ो(&q->ci));
पूर्ण

अटल पूर्णांक gaudi_soft_reset_late_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	/* Unmask all IRQs since some could have been received
	 * during the soft reset
	 */
	वापस hl_fw_unmask_irq_arr(hdev, gaudi->events, माप(gaudi->events));
पूर्ण

अटल पूर्णांक gaudi_hbm_पढ़ो_पूर्णांकerrupts(काष्ठा hl_device *hdev, पूर्णांक device,
			काष्ठा hl_eq_hbm_ecc_data *hbm_ecc_data)
अणु
	u32 base, val, val2, wr_par, rd_par, ca_par, derr, serr, type, ch;
	पूर्णांक err = 0;

	अगर (hdev->asic_prop.fw_security_status_valid &&
			(hdev->asic_prop.fw_app_security_map &
				CPU_BOOT_DEV_STS0_HBM_ECC_EN)) अणु
		अगर (!hbm_ecc_data) अणु
			dev_err(hdev->dev, "No FW ECC data");
			वापस 0;
		पूर्ण

		wr_par = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_WR_PAR_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));
		rd_par = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_RD_PAR_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));
		ca_par = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_CA_PAR_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));
		derr = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_DERR_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));
		serr = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_SERR_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));
		type = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_TYPE_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));
		ch = FIELD_GET(CPUCP_PKT_HBM_ECC_INFO_HBM_CH_MASK,
				le32_to_cpu(hbm_ecc_data->hbm_ecc_info));

		dev_err(hdev->dev,
			"HBM%d pc%d interrupts info: WR_PAR=%d, RD_PAR=%d, CA_PAR=%d, SERR=%d, DERR=%d\n",
			device, ch, wr_par, rd_par, ca_par, serr, derr);
		dev_err(hdev->dev,
			"HBM%d pc%d ECC info: 1ST_ERR_ADDR=0x%x, 1ST_ERR_TYPE=%d, SEC_CONT_CNT=%u, SEC_CNT=%d, DEC_CNT=%d\n",
			device, ch, hbm_ecc_data->first_addr, type,
			hbm_ecc_data->sec_cont_cnt, hbm_ecc_data->sec_cnt,
			hbm_ecc_data->dec_cnt);

		err = 1;

		वापस 0;
	पूर्ण

	अगर (!hdev->asic_prop.fw_security_disabled) अणु
		dev_info(hdev->dev, "Cannot access MC regs for ECC data while security is enabled\n");
		वापस 0;
	पूर्ण

	base = GAUDI_HBM_CFG_BASE + device * GAUDI_HBM_CFG_OFFSET;
	क्रम (ch = 0 ; ch < GAUDI_HBM_CHANNELS ; ch++) अणु
		val = RREG32_MASK(base + ch * 0x1000 + 0x06C, 0x0000FFFF);
		val = (val & 0xFF) | ((val >> 8) & 0xFF);
		अगर (val) अणु
			err = 1;
			dev_err(hdev->dev,
				"HBM%d pc%d interrupts info: WR_PAR=%d, RD_PAR=%d, CA_PAR=%d, SERR=%d, DERR=%d\n",
				device, ch * 2, val & 0x1, (val >> 1) & 0x1,
				(val >> 2) & 0x1, (val >> 3) & 0x1,
				(val >> 4) & 0x1);

			val2 = RREG32(base + ch * 0x1000 + 0x060);
			dev_err(hdev->dev,
				"HBM%d pc%d ECC info: 1ST_ERR_ADDR=0x%x, 1ST_ERR_TYPE=%d, SEC_CONT_CNT=%d, SEC_CNT=%d, DEC_CNT=%d\n",
				device, ch * 2,
				RREG32(base + ch * 0x1000 + 0x064),
				(val2 & 0x200) >> 9, (val2 & 0xFC00) >> 10,
				(val2 & 0xFF0000) >> 16,
				(val2 & 0xFF000000) >> 24);
		पूर्ण

		val = RREG32_MASK(base + ch * 0x1000 + 0x07C, 0x0000FFFF);
		val = (val & 0xFF) | ((val >> 8) & 0xFF);
		अगर (val) अणु
			err = 1;
			dev_err(hdev->dev,
				"HBM%d pc%d interrupts info: WR_PAR=%d, RD_PAR=%d, CA_PAR=%d, SERR=%d, DERR=%d\n",
				device, ch * 2 + 1, val & 0x1, (val >> 1) & 0x1,
				(val >> 2) & 0x1, (val >> 3) & 0x1,
				(val >> 4) & 0x1);

			val2 = RREG32(base + ch * 0x1000 + 0x070);
			dev_err(hdev->dev,
				"HBM%d pc%d ECC info: 1ST_ERR_ADDR=0x%x, 1ST_ERR_TYPE=%d, SEC_CONT_CNT=%d, SEC_CNT=%d, DEC_CNT=%d\n",
				device, ch * 2 + 1,
				RREG32(base + ch * 0x1000 + 0x074),
				(val2 & 0x200) >> 9, (val2 & 0xFC00) >> 10,
				(val2 & 0xFF0000) >> 16,
				(val2 & 0xFF000000) >> 24);
		पूर्ण

		/* Clear पूर्णांकerrupts */
		RMWREG32(base + (ch * 0x1000) + 0x060, 0x1C8, 0x1FF);
		RMWREG32(base + (ch * 0x1000) + 0x070, 0x1C8, 0x1FF);
		WREG32(base + (ch * 0x1000) + 0x06C, 0x1F1F);
		WREG32(base + (ch * 0x1000) + 0x07C, 0x1F1F);
		RMWREG32(base + (ch * 0x1000) + 0x060, 0x0, 0xF);
		RMWREG32(base + (ch * 0x1000) + 0x070, 0x0, 0xF);
	पूर्ण

	val  = RREG32(base + 0x8F30);
	val2 = RREG32(base + 0x8F34);
	अगर (val | val2) अणु
		err = 1;
		dev_err(hdev->dev,
			"HBM %d MC SRAM SERR info: Reg 0x8F30=0x%x, Reg 0x8F34=0x%x\n",
			device, val, val2);
	पूर्ण
	val  = RREG32(base + 0x8F40);
	val2 = RREG32(base + 0x8F44);
	अगर (val | val2) अणु
		err = 1;
		dev_err(hdev->dev,
			"HBM %d MC SRAM DERR info: Reg 0x8F40=0x%x, Reg 0x8F44=0x%x\n",
			device, val, val2);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक gaudi_hbm_event_to_dev(u16 hbm_event_type)
अणु
	चयन (hbm_event_type) अणु
	हाल GAUDI_EVENT_HBM0_SPI_0:
	हाल GAUDI_EVENT_HBM0_SPI_1:
		वापस 0;
	हाल GAUDI_EVENT_HBM1_SPI_0:
	हाल GAUDI_EVENT_HBM1_SPI_1:
		वापस 1;
	हाल GAUDI_EVENT_HBM2_SPI_0:
	हाल GAUDI_EVENT_HBM2_SPI_1:
		वापस 2;
	हाल GAUDI_EVENT_HBM3_SPI_0:
	हाल GAUDI_EVENT_HBM3_SPI_1:
		वापस 3;
	शेष:
		अवरोध;
	पूर्ण

	/* Should never happen */
	वापस 0;
पूर्ण

अटल bool gaudi_tpc_पढ़ो_पूर्णांकerrupts(काष्ठा hl_device *hdev, u8 tpc_id,
					अक्षर *पूर्णांकerrupt_name)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 tpc_offset = tpc_id * TPC_CFG_OFFSET, tpc_पूर्णांकerrupts_cause, i;
	bool soft_reset_required = false;

	/* Accessing the TPC_INTR_CAUSE रेजिस्टरs requires disabling the घड़ी
	 * gating, and thus cannot be करोne in CPU-CP and should be करोne instead
	 * by the driver.
	 */

	mutex_lock(&gaudi->clk_gate_mutex);

	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	tpc_पूर्णांकerrupts_cause = RREG32(mmTPC0_CFG_TPC_INTR_CAUSE + tpc_offset) &
				TPC0_CFG_TPC_INTR_CAUSE_CAUSE_MASK;

	क्रम (i = 0 ; i < GAUDI_NUM_OF_TPC_INTR_CAUSE ; i++)
		अगर (tpc_पूर्णांकerrupts_cause & BIT(i)) अणु
			dev_err_ratelimited(hdev->dev,
					"TPC%d_%s interrupt cause: %s\n",
					tpc_id, पूर्णांकerrupt_name,
					gaudi_tpc_पूर्णांकerrupts_cause[i]);
			/* If this is QM error, we need to soft-reset */
			अगर (i == 15)
				soft_reset_required = true;
		पूर्ण

	/* Clear पूर्णांकerrupts */
	WREG32(mmTPC0_CFG_TPC_INTR_CAUSE + tpc_offset, 0);

	hdev->asic_funcs->set_घड़ी_gating(hdev);

	mutex_unlock(&gaudi->clk_gate_mutex);

	वापस soft_reset_required;
पूर्ण

अटल पूर्णांक tpc_dec_event_to_tpc_id(u16 tpc_dec_event_type)
अणु
	वापस (tpc_dec_event_type - GAUDI_EVENT_TPC0_DEC) >> 1;
पूर्ण

अटल पूर्णांक tpc_krn_event_to_tpc_id(u16 tpc_dec_event_type)
अणु
	वापस (tpc_dec_event_type - GAUDI_EVENT_TPC0_KRN_ERR) / 6;
पूर्ण

अटल व्योम gaudi_prपूर्णांक_clk_change_info(काष्ठा hl_device *hdev,
					u16 event_type)
अणु
	चयन (event_type) अणु
	हाल GAUDI_EVENT_FIX_POWER_ENV_S:
		hdev->clk_throttling_reason |= HL_CLK_THROTTLE_POWER;
		dev_info_ratelimited(hdev->dev,
			"Clock throttling due to power consumption\n");
		अवरोध;

	हाल GAUDI_EVENT_FIX_POWER_ENV_E:
		hdev->clk_throttling_reason &= ~HL_CLK_THROTTLE_POWER;
		dev_info_ratelimited(hdev->dev,
			"Power envelop is safe, back to optimal clock\n");
		अवरोध;

	हाल GAUDI_EVENT_FIX_THERMAL_ENV_S:
		hdev->clk_throttling_reason |= HL_CLK_THROTTLE_THERMAL;
		dev_info_ratelimited(hdev->dev,
			"Clock throttling due to overheating\n");
		अवरोध;

	हाल GAUDI_EVENT_FIX_THERMAL_ENV_E:
		hdev->clk_throttling_reason &= ~HL_CLK_THROTTLE_THERMAL;
		dev_info_ratelimited(hdev->dev,
			"Thermal envelop is safe, back to optimal clock\n");
		अवरोध;

	शेष:
		dev_err(hdev->dev, "Received invalid clock change event %d\n",
			event_type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gaudi_handle_eqe(काष्ठा hl_device *hdev,
				काष्ठा hl_eq_entry *eq_entry)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 ctl = le32_to_cpu(eq_entry->hdr.ctl);
	u16 event_type = ((ctl & EQ_CTL_EVENT_TYPE_MASK)
			>> EQ_CTL_EVENT_TYPE_SHIFT);
	u8 cause;
	bool reset_required;

	gaudi->events_stat[event_type]++;
	gaudi->events_stat_aggregate[event_type]++;

	चयन (event_type) अणु
	हाल GAUDI_EVENT_PCIE_CORE_DERR:
	हाल GAUDI_EVENT_PCIE_IF_DERR:
	हाल GAUDI_EVENT_PCIE_PHY_DERR:
	हाल GAUDI_EVENT_TPC0_DERR ... GAUDI_EVENT_TPC7_DERR:
	हाल GAUDI_EVENT_MME0_ACC_DERR:
	हाल GAUDI_EVENT_MME0_SBAB_DERR:
	हाल GAUDI_EVENT_MME1_ACC_DERR:
	हाल GAUDI_EVENT_MME1_SBAB_DERR:
	हाल GAUDI_EVENT_MME2_ACC_DERR:
	हाल GAUDI_EVENT_MME2_SBAB_DERR:
	हाल GAUDI_EVENT_MME3_ACC_DERR:
	हाल GAUDI_EVENT_MME3_SBAB_DERR:
	हाल GAUDI_EVENT_DMA0_DERR_ECC ... GAUDI_EVENT_DMA7_DERR_ECC:
		fallthrough;
	हाल GAUDI_EVENT_CPU_IF_ECC_DERR:
	हाल GAUDI_EVENT_PSOC_MEM_DERR:
	हाल GAUDI_EVENT_PSOC_CORESIGHT_DERR:
	हाल GAUDI_EVENT_SRAM0_DERR ... GAUDI_EVENT_SRAM28_DERR:
	हाल GAUDI_EVENT_DMA_IF0_DERR ... GAUDI_EVENT_DMA_IF3_DERR:
	हाल GAUDI_EVENT_HBM_0_DERR ... GAUDI_EVENT_HBM_3_DERR:
	हाल GAUDI_EVENT_MMU_DERR:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, true);
		gaudi_handle_ecc_event(hdev, event_type, &eq_entry->ecc_data);
		जाओ reset_device;

	हाल GAUDI_EVENT_GIC500:
	हाल GAUDI_EVENT_AXI_ECC:
	हाल GAUDI_EVENT_L2_RAM_ECC:
	हाल GAUDI_EVENT_PLL0 ... GAUDI_EVENT_PLL17:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		जाओ reset_device;

	हाल GAUDI_EVENT_HBM0_SPI_0:
	हाल GAUDI_EVENT_HBM1_SPI_0:
	हाल GAUDI_EVENT_HBM2_SPI_0:
	हाल GAUDI_EVENT_HBM3_SPI_0:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		gaudi_hbm_पढ़ो_पूर्णांकerrupts(hdev,
				gaudi_hbm_event_to_dev(event_type),
				&eq_entry->hbm_ecc_data);
		जाओ reset_device;

	हाल GAUDI_EVENT_HBM0_SPI_1:
	हाल GAUDI_EVENT_HBM1_SPI_1:
	हाल GAUDI_EVENT_HBM2_SPI_1:
	हाल GAUDI_EVENT_HBM3_SPI_1:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		gaudi_hbm_पढ़ो_पूर्णांकerrupts(hdev,
				gaudi_hbm_event_to_dev(event_type),
				&eq_entry->hbm_ecc_data);
		hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GAUDI_EVENT_TPC0_DEC:
	हाल GAUDI_EVENT_TPC1_DEC:
	हाल GAUDI_EVENT_TPC2_DEC:
	हाल GAUDI_EVENT_TPC3_DEC:
	हाल GAUDI_EVENT_TPC4_DEC:
	हाल GAUDI_EVENT_TPC5_DEC:
	हाल GAUDI_EVENT_TPC6_DEC:
	हाल GAUDI_EVENT_TPC7_DEC:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, true);
		reset_required = gaudi_tpc_पढ़ो_पूर्णांकerrupts(hdev,
					tpc_dec_event_to_tpc_id(event_type),
					"AXI_SLV_DEC_Error");
		अगर (reset_required) अणु
			dev_err(hdev->dev, "hard reset required due to %s\n",
				gaudi_irq_map_table[event_type].name);

			जाओ reset_device;
		पूर्ण अन्यथा अणु
			hl_fw_unmask_irq(hdev, event_type);
		पूर्ण
		अवरोध;

	हाल GAUDI_EVENT_TPC0_KRN_ERR:
	हाल GAUDI_EVENT_TPC1_KRN_ERR:
	हाल GAUDI_EVENT_TPC2_KRN_ERR:
	हाल GAUDI_EVENT_TPC3_KRN_ERR:
	हाल GAUDI_EVENT_TPC4_KRN_ERR:
	हाल GAUDI_EVENT_TPC5_KRN_ERR:
	हाल GAUDI_EVENT_TPC6_KRN_ERR:
	हाल GAUDI_EVENT_TPC7_KRN_ERR:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, true);
		reset_required = gaudi_tpc_पढ़ो_पूर्णांकerrupts(hdev,
					tpc_krn_event_to_tpc_id(event_type),
					"KRN_ERR");
		अगर (reset_required) अणु
			dev_err(hdev->dev, "hard reset required due to %s\n",
				gaudi_irq_map_table[event_type].name);

			जाओ reset_device;
		पूर्ण अन्यथा अणु
			hl_fw_unmask_irq(hdev, event_type);
		पूर्ण
		अवरोध;

	हाल GAUDI_EVENT_PCIE_CORE_SERR:
	हाल GAUDI_EVENT_PCIE_IF_SERR:
	हाल GAUDI_EVENT_PCIE_PHY_SERR:
	हाल GAUDI_EVENT_TPC0_SERR ... GAUDI_EVENT_TPC7_SERR:
	हाल GAUDI_EVENT_MME0_ACC_SERR:
	हाल GAUDI_EVENT_MME0_SBAB_SERR:
	हाल GAUDI_EVENT_MME1_ACC_SERR:
	हाल GAUDI_EVENT_MME1_SBAB_SERR:
	हाल GAUDI_EVENT_MME2_ACC_SERR:
	हाल GAUDI_EVENT_MME2_SBAB_SERR:
	हाल GAUDI_EVENT_MME3_ACC_SERR:
	हाल GAUDI_EVENT_MME3_SBAB_SERR:
	हाल GAUDI_EVENT_DMA0_SERR_ECC ... GAUDI_EVENT_DMA7_SERR_ECC:
	हाल GAUDI_EVENT_CPU_IF_ECC_SERR:
	हाल GAUDI_EVENT_PSOC_MEM_SERR:
	हाल GAUDI_EVENT_PSOC_CORESIGHT_SERR:
	हाल GAUDI_EVENT_SRAM0_SERR ... GAUDI_EVENT_SRAM28_SERR:
	हाल GAUDI_EVENT_DMA_IF0_SERR ... GAUDI_EVENT_DMA_IF3_SERR:
	हाल GAUDI_EVENT_HBM_0_SERR ... GAUDI_EVENT_HBM_3_SERR:
		fallthrough;
	हाल GAUDI_EVENT_MMU_SERR:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, true);
		gaudi_handle_ecc_event(hdev, event_type, &eq_entry->ecc_data);
		hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GAUDI_EVENT_PCIE_DEC:
	हाल GAUDI_EVENT_MME0_WBC_RSP:
	हाल GAUDI_EVENT_MME0_SBAB0_RSP:
	हाल GAUDI_EVENT_MME1_WBC_RSP:
	हाल GAUDI_EVENT_MME1_SBAB0_RSP:
	हाल GAUDI_EVENT_MME2_WBC_RSP:
	हाल GAUDI_EVENT_MME2_SBAB0_RSP:
	हाल GAUDI_EVENT_MME3_WBC_RSP:
	हाल GAUDI_EVENT_MME3_SBAB0_RSP:
	हाल GAUDI_EVENT_CPU_AXI_SPLITTER:
	हाल GAUDI_EVENT_PSOC_AXI_DEC:
	हाल GAUDI_EVENT_PSOC_PRSTN_FALL:
	हाल GAUDI_EVENT_MMU_PAGE_FAULT:
	हाल GAUDI_EVENT_MMU_WR_PERM:
	हाल GAUDI_EVENT_RAZWI_OR_ADC:
	हाल GAUDI_EVENT_TPC0_QM ... GAUDI_EVENT_TPC7_QM:
	हाल GAUDI_EVENT_MME0_QM ... GAUDI_EVENT_MME2_QM:
	हाल GAUDI_EVENT_DMA0_QM ... GAUDI_EVENT_DMA7_QM:
		fallthrough;
	हाल GAUDI_EVENT_NIC0_QM0:
	हाल GAUDI_EVENT_NIC0_QM1:
	हाल GAUDI_EVENT_NIC1_QM0:
	हाल GAUDI_EVENT_NIC1_QM1:
	हाल GAUDI_EVENT_NIC2_QM0:
	हाल GAUDI_EVENT_NIC2_QM1:
	हाल GAUDI_EVENT_NIC3_QM0:
	हाल GAUDI_EVENT_NIC3_QM1:
	हाल GAUDI_EVENT_NIC4_QM0:
	हाल GAUDI_EVENT_NIC4_QM1:
	हाल GAUDI_EVENT_DMA0_CORE ... GAUDI_EVENT_DMA7_CORE:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, true);
		gaudi_handle_qman_err(hdev, event_type);
		hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GAUDI_EVENT_RAZWI_OR_ADC_SW:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, true);
		जाओ reset_device;

	हाल GAUDI_EVENT_TPC0_BMON_SPMU:
	हाल GAUDI_EVENT_TPC1_BMON_SPMU:
	हाल GAUDI_EVENT_TPC2_BMON_SPMU:
	हाल GAUDI_EVENT_TPC3_BMON_SPMU:
	हाल GAUDI_EVENT_TPC4_BMON_SPMU:
	हाल GAUDI_EVENT_TPC5_BMON_SPMU:
	हाल GAUDI_EVENT_TPC6_BMON_SPMU:
	हाल GAUDI_EVENT_TPC7_BMON_SPMU:
	हाल GAUDI_EVENT_DMA_BM_CH0 ... GAUDI_EVENT_DMA_BM_CH7:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GAUDI_EVENT_DMA_IF_SEI_0 ... GAUDI_EVENT_DMA_IF_SEI_3:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		gaudi_prपूर्णांक_sm_sei_info(hdev, event_type,
					&eq_entry->sm_sei_data);
		hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GAUDI_EVENT_FIX_POWER_ENV_S ... GAUDI_EVENT_FIX_THERMAL_ENV_E:
		gaudi_prपूर्णांक_clk_change_info(hdev, event_type);
		hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GAUDI_EVENT_PSOC_GPIO_U16_0:
		cause = le64_to_cpu(eq_entry->data[0]) & 0xFF;
		dev_err(hdev->dev,
			"Received high temp H/W interrupt %d (cause %d)\n",
			event_type, cause);
		अवरोध;

	हाल GAUDI_EVENT_DEV_RESET_REQ:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		जाओ reset_device;

	हाल GAUDI_EVENT_PKT_QUEUE_OUT_SYNC:
		gaudi_prपूर्णांक_irq_info(hdev, event_type, false);
		gaudi_prपूर्णांक_out_of_sync_info(hdev, &eq_entry->pkt_sync_err);
		जाओ reset_device;

	शेष:
		dev_err(hdev->dev, "Received invalid H/W interrupt %d\n",
				event_type);
		अवरोध;
	पूर्ण

	वापस;

reset_device:
	अगर (hdev->hard_reset_on_fw_events)
		hl_device_reset(hdev, HL_RESET_HARD);
	अन्यथा
		hl_fw_unmask_irq(hdev, event_type);
पूर्ण

अटल व्योम *gaudi_get_events_stat(काष्ठा hl_device *hdev, bool aggregate,
					u32 *size)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (aggregate) अणु
		*size = (u32) माप(gaudi->events_stat_aggregate);
		वापस gaudi->events_stat_aggregate;
	पूर्ण

	*size = (u32) माप(gaudi->events_stat);
	वापस gaudi->events_stat;
पूर्ण

अटल पूर्णांक gaudi_mmu_invalidate_cache(काष्ठा hl_device *hdev, bool is_hard,
					u32 flags)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 status, समयout_usec;
	पूर्णांक rc;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU) ||
		hdev->hard_reset_pending)
		वापस 0;

	अगर (hdev->pldm)
		समयout_usec = GAUDI_PLDM_MMU_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = MMU_CONFIG_TIMEOUT_USEC;

	/* L0 & L1 invalidation */
	WREG32(mmSTLB_INV_PS, 3);
	WREG32(mmSTLB_CACHE_INV, gaudi->mmu_cache_inv_pi++);
	WREG32(mmSTLB_INV_PS, 2);

	rc = hl_poll_समयout(
		hdev,
		mmSTLB_INV_PS,
		status,
		!status,
		1000,
		समयout_usec);

	WREG32(mmSTLB_INV_SET, 0);

	अगर (rc) अणु
		dev_err_ratelimited(hdev->dev,
					"MMU cache invalidation timeout\n");
		hl_device_reset(hdev, HL_RESET_HARD);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_mmu_invalidate_cache_range(काष्ठा hl_device *hdev,
				bool is_hard, u32 asid, u64 va, u64 size)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u32 status, समयout_usec;
	u32 inv_data;
	u32 pi;
	पूर्णांक rc;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU) ||
		hdev->hard_reset_pending)
		वापस 0;

	अगर (hdev->pldm)
		समयout_usec = GAUDI_PLDM_MMU_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = MMU_CONFIG_TIMEOUT_USEC;

	/*
	 * TODO: currently invalidate entire L0 & L1 as in regular hard
	 * invalidation. Need to apply invalidation of specअगरic cache
	 * lines with mask of ASID & VA & size.
	 * Note that L1 with be flushed entirely in any हाल.
	 */

	/* L0 & L1 invalidation */
	inv_data = RREG32(mmSTLB_CACHE_INV);
	/* PI is 8 bit */
	pi = ((inv_data & STLB_CACHE_INV_PRODUCER_INDEX_MASK) + 1) & 0xFF;
	WREG32(mmSTLB_CACHE_INV,
		(inv_data & STLB_CACHE_INV_INDEX_MASK_MASK) | pi);

	rc = hl_poll_समयout(
		hdev,
		mmSTLB_INV_CONSUMER_INDEX,
		status,
		status == pi,
		1000,
		समयout_usec);

	अगर (rc) अणु
		dev_err_ratelimited(hdev->dev,
					"MMU cache invalidation timeout\n");
		hl_device_reset(hdev, HL_RESET_HARD);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gaudi_mmu_update_asid_hop0_addr(काष्ठा hl_device *hdev,
					u32 asid, u64 phys_addr)
अणु
	u32 status, समयout_usec;
	पूर्णांक rc;

	अगर (hdev->pldm)
		समयout_usec = GAUDI_PLDM_MMU_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = MMU_CONFIG_TIMEOUT_USEC;

	WREG32(MMU_ASID, asid);
	WREG32(MMU_HOP0_PA43_12, phys_addr >> MMU_HOP0_PA43_12_SHIFT);
	WREG32(MMU_HOP0_PA49_44, phys_addr >> MMU_HOP0_PA49_44_SHIFT);
	WREG32(MMU_BUSY, 0x80000000);

	rc = hl_poll_समयout(
		hdev,
		MMU_BUSY,
		status,
		!(status & 0x80000000),
		1000,
		समयout_usec);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout during MMU hop0 config of asid %d\n", asid);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_send_heartbeat(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	वापस hl_fw_send_heartbeat(hdev);
पूर्ण

अटल पूर्णांक gaudi_cpucp_info_get(काष्ठा hl_device *hdev)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक rc;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	rc = hl_fw_cpucp_handshake(hdev, mmCPU_BOOT_DEV_STS0, mmCPU_BOOT_ERR0);
	अगर (rc)
		वापस rc;

	अगर (!म_माप(prop->cpucp_info.card_name))
		म_नकलन(prop->cpucp_info.card_name, GAUDI_DEFAULT_CARD_NAME,
				CARD_NAME_MAX_LEN);

	hdev->card_type = le32_to_cpu(hdev->asic_prop.cpucp_info.card_type);

	set_शेष_घातer_values(hdev);

	hdev->max_घातer = prop->max_घातer_शेष;

	वापस 0;
पूर्ण

अटल bool gaudi_is_device_idle(काष्ठा hl_device *hdev, u64 *mask_arr,
					u8 mask_len, काष्ठा seq_file *s)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	स्थिर अक्षर *fmt = "%-5d%-9s%#-14x%#-12x%#x\n";
	स्थिर अक्षर *mme_slave_fmt = "%-5d%-9s%-14s%-12s%#x\n";
	स्थिर अक्षर *nic_fmt = "%-5d%-9s%#-14x%#x\n";
	अचिन्हित दीर्घ *mask = (अचिन्हित दीर्घ *)mask_arr;
	u32 qm_glbl_sts0, qm_cgm_sts, dma_core_sts0, tpc_cfg_sts, mme_arch_sts;
	bool is_idle = true, is_eng_idle, is_slave;
	u64 offset;
	पूर्णांक i, dma_id, port;

	mutex_lock(&gaudi->clk_gate_mutex);

	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	अगर (s)
		seq_माला_दो(s,
			"\nDMA  is_idle  QM_GLBL_STS0  QM_CGM_STS  DMA_CORE_STS0\n"
			"---  -------  ------------  ----------  -------------\n");

	क्रम (i = 0 ; i < DMA_NUMBER_OF_CHNLS ; i++) अणु
		dma_id = gaudi_dma_assignment[i];
		offset = dma_id * DMA_QMAN_OFFSET;

		qm_glbl_sts0 = RREG32(mmDMA0_QM_GLBL_STS0 + offset);
		qm_cgm_sts = RREG32(mmDMA0_QM_CGM_STS + offset);
		dma_core_sts0 = RREG32(mmDMA0_CORE_STS0 + offset);
		is_eng_idle = IS_QM_IDLE(qm_glbl_sts0, qm_cgm_sts) &&
				IS_DMA_IDLE(dma_core_sts0);
		is_idle &= is_eng_idle;

		अगर (mask && !is_eng_idle)
			set_bit(GAUDI_ENGINE_ID_DMA_0 + dma_id, mask);
		अगर (s)
			seq_म_लिखो(s, fmt, dma_id,
				is_eng_idle ? "Y" : "N", qm_glbl_sts0,
				qm_cgm_sts, dma_core_sts0);
	पूर्ण

	अगर (s)
		seq_माला_दो(s,
			"\nTPC  is_idle  QM_GLBL_STS0  QM_CGM_STS  CFG_STATUS\n"
			"---  -------  ------------  ----------  ----------\n");

	क्रम (i = 0 ; i < TPC_NUMBER_OF_ENGINES ; i++) अणु
		offset = i * TPC_QMAN_OFFSET;
		qm_glbl_sts0 = RREG32(mmTPC0_QM_GLBL_STS0 + offset);
		qm_cgm_sts = RREG32(mmTPC0_QM_CGM_STS + offset);
		tpc_cfg_sts = RREG32(mmTPC0_CFG_STATUS + offset);
		is_eng_idle = IS_QM_IDLE(qm_glbl_sts0, qm_cgm_sts) &&
				IS_TPC_IDLE(tpc_cfg_sts);
		is_idle &= is_eng_idle;

		अगर (mask && !is_eng_idle)
			set_bit(GAUDI_ENGINE_ID_TPC_0 + i, mask);
		अगर (s)
			seq_म_लिखो(s, fmt, i,
				is_eng_idle ? "Y" : "N",
				qm_glbl_sts0, qm_cgm_sts, tpc_cfg_sts);
	पूर्ण

	अगर (s)
		seq_माला_दो(s,
			"\nMME  is_idle  QM_GLBL_STS0  QM_CGM_STS  ARCH_STATUS\n"
			"---  -------  ------------  ----------  -----------\n");

	क्रम (i = 0 ; i < MME_NUMBER_OF_ENGINES ; i++) अणु
		offset = i * MME_QMAN_OFFSET;
		mme_arch_sts = RREG32(mmMME0_CTRL_ARCH_STATUS + offset);
		is_eng_idle = IS_MME_IDLE(mme_arch_sts);

		/* MME 1 & 3 are slaves, no need to check their QMANs */
		is_slave = i % 2;
		अगर (!is_slave) अणु
			qm_glbl_sts0 = RREG32(mmMME0_QM_GLBL_STS0 + offset);
			qm_cgm_sts = RREG32(mmMME0_QM_CGM_STS + offset);
			is_eng_idle &= IS_QM_IDLE(qm_glbl_sts0, qm_cgm_sts);
		पूर्ण

		is_idle &= is_eng_idle;

		अगर (mask && !is_eng_idle)
			set_bit(GAUDI_ENGINE_ID_MME_0 + i, mask);
		अगर (s) अणु
			अगर (!is_slave)
				seq_म_लिखो(s, fmt, i,
					is_eng_idle ? "Y" : "N",
					qm_glbl_sts0, qm_cgm_sts, mme_arch_sts);
			अन्यथा
				seq_म_लिखो(s, mme_slave_fmt, i,
					is_eng_idle ? "Y" : "N", "-",
					"-", mme_arch_sts);
		पूर्ण
	पूर्ण

	अगर (s)
		seq_माला_दो(s, "\nNIC  is_idle  QM_GLBL_STS0  QM_CGM_STS\n"
				"---  -------  ------------  ----------\n");

	क्रम (i = 0 ; i < (NIC_NUMBER_OF_ENGINES / 2) ; i++) अणु
		offset = i * NIC_MACRO_QMAN_OFFSET;
		port = 2 * i;
		अगर (hdev->nic_ports_mask & BIT(port)) अणु
			qm_glbl_sts0 = RREG32(mmNIC0_QM0_GLBL_STS0 + offset);
			qm_cgm_sts = RREG32(mmNIC0_QM0_CGM_STS + offset);
			is_eng_idle = IS_QM_IDLE(qm_glbl_sts0, qm_cgm_sts);
			is_idle &= is_eng_idle;

			अगर (mask && !is_eng_idle)
				set_bit(GAUDI_ENGINE_ID_NIC_0 + port, mask);
			अगर (s)
				seq_म_लिखो(s, nic_fmt, port,
						is_eng_idle ? "Y" : "N",
						qm_glbl_sts0, qm_cgm_sts);
		पूर्ण

		port = 2 * i + 1;
		अगर (hdev->nic_ports_mask & BIT(port)) अणु
			qm_glbl_sts0 = RREG32(mmNIC0_QM1_GLBL_STS0 + offset);
			qm_cgm_sts = RREG32(mmNIC0_QM1_CGM_STS + offset);
			is_eng_idle = IS_QM_IDLE(qm_glbl_sts0, qm_cgm_sts);
			is_idle &= is_eng_idle;

			अगर (mask && !is_eng_idle)
				set_bit(GAUDI_ENGINE_ID_NIC_0 + port, mask);
			अगर (s)
				seq_म_लिखो(s, nic_fmt, port,
						is_eng_idle ? "Y" : "N",
						qm_glbl_sts0, qm_cgm_sts);
		पूर्ण
	पूर्ण

	अगर (s)
		seq_माला_दो(s, "\n");

	hdev->asic_funcs->set_घड़ी_gating(hdev);

	mutex_unlock(&gaudi->clk_gate_mutex);

	वापस is_idle;
पूर्ण

अटल व्योम gaudi_hw_queues_lock(काष्ठा hl_device *hdev)
	__acquires(&gaudi->hw_queues_lock)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	spin_lock(&gaudi->hw_queues_lock);
पूर्ण

अटल व्योम gaudi_hw_queues_unlock(काष्ठा hl_device *hdev)
	__releases(&gaudi->hw_queues_lock)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	spin_unlock(&gaudi->hw_queues_lock);
पूर्ण

अटल u32 gaudi_get_pci_id(काष्ठा hl_device *hdev)
अणु
	वापस hdev->pdev->device;
पूर्ण

अटल पूर्णांक gaudi_get_eeprom_data(काष्ठा hl_device *hdev, व्योम *data,
				माप_प्रकार max_size)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	वापस hl_fw_get_eeprom_data(hdev, data, max_size);
पूर्ण

/*
 * this function should be used only during initialization and/or after reset,
 * when there are no active users.
 */
अटल पूर्णांक gaudi_run_tpc_kernel(काष्ठा hl_device *hdev, u64 tpc_kernel,
				u32 tpc_id)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	u64 kernel_समयout;
	u32 status, offset;
	पूर्णांक rc;

	offset = tpc_id * (mmTPC1_CFG_STATUS - mmTPC0_CFG_STATUS);

	अगर (hdev->pldm)
		kernel_समयout = GAUDI_PLDM_TPC_KERNEL_WAIT_USEC;
	अन्यथा
		kernel_समयout = HL_DEVICE_TIMEOUT_USEC;

	mutex_lock(&gaudi->clk_gate_mutex);

	hdev->asic_funcs->disable_घड़ी_gating(hdev);

	WREG32(mmTPC0_CFG_QM_KERNEL_BASE_ADDRESS_LOW + offset,
			lower_32_bits(tpc_kernel));
	WREG32(mmTPC0_CFG_QM_KERNEL_BASE_ADDRESS_HIGH + offset,
			upper_32_bits(tpc_kernel));

	WREG32(mmTPC0_CFG_ICACHE_BASE_ADDERESS_LOW + offset,
			lower_32_bits(tpc_kernel));
	WREG32(mmTPC0_CFG_ICACHE_BASE_ADDERESS_HIGH + offset,
			upper_32_bits(tpc_kernel));
	/* set a valid LUT poपूर्णांकer, content is of no signअगरicance */
	WREG32(mmTPC0_CFG_LUT_FUNC256_BASE_ADDR_LO + offset,
			lower_32_bits(tpc_kernel));
	WREG32(mmTPC0_CFG_LUT_FUNC256_BASE_ADDR_HI + offset,
			upper_32_bits(tpc_kernel));

	WREG32(mmTPC0_CFG_QM_SYNC_OBJECT_ADDR + offset,
			lower_32_bits(CFG_BASE +
				mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0));

	WREG32(mmTPC0_CFG_TPC_CMD + offset,
			(1 << TPC0_CFG_TPC_CMD_ICACHE_INVALIDATE_SHIFT |
			1 << TPC0_CFG_TPC_CMD_ICACHE_PREFETCH_64KB_SHIFT));
	/* रुको a bit क्रम the engine to start executing */
	usleep_range(1000, 1500);

	/* रुको until engine has finished executing */
	rc = hl_poll_समयout(
		hdev,
		mmTPC0_CFG_STATUS + offset,
		status,
		(status & TPC0_CFG_STATUS_VECTOR_PIPE_EMPTY_MASK) ==
				TPC0_CFG_STATUS_VECTOR_PIPE_EMPTY_MASK,
		1000,
		kernel_समयout);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout while waiting for TPC%d icache prefetch\n",
			tpc_id);
		hdev->asic_funcs->set_घड़ी_gating(hdev);
		mutex_unlock(&gaudi->clk_gate_mutex);
		वापस -EIO;
	पूर्ण

	WREG32(mmTPC0_CFG_TPC_EXECUTE + offset,
			1 << TPC0_CFG_TPC_EXECUTE_V_SHIFT);

	/* रुको a bit क्रम the engine to start executing */
	usleep_range(1000, 1500);

	/* रुको until engine has finished executing */
	rc = hl_poll_समयout(
		hdev,
		mmTPC0_CFG_STATUS + offset,
		status,
		(status & TPC0_CFG_STATUS_VECTOR_PIPE_EMPTY_MASK) ==
				TPC0_CFG_STATUS_VECTOR_PIPE_EMPTY_MASK,
		1000,
		kernel_समयout);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout while waiting for TPC%d vector pipe\n",
			tpc_id);
		hdev->asic_funcs->set_घड़ी_gating(hdev);
		mutex_unlock(&gaudi->clk_gate_mutex);
		वापस -EIO;
	पूर्ण

	rc = hl_poll_समयout(
		hdev,
		mmTPC0_CFG_WQ_INFLIGHT_CNTR + offset,
		status,
		(status == 0),
		1000,
		kernel_समयout);

	hdev->asic_funcs->set_घड़ी_gating(hdev);
	mutex_unlock(&gaudi->clk_gate_mutex);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout while waiting for TPC%d kernel to execute\n",
			tpc_id);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gaudi_पूर्णांकernal_cb_pool_init(काष्ठा hl_device *hdev,
		काष्ठा hl_ctx *ctx)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक min_alloc_order, rc, collective_cb_size;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU))
		वापस 0;

	hdev->पूर्णांकernal_cb_pool_virt_addr =
			hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
					HOST_SPACE_INTERNAL_CB_SZ,
					&hdev->पूर्णांकernal_cb_pool_dma_addr,
					GFP_KERNEL | __GFP_ZERO);

	अगर (!hdev->पूर्णांकernal_cb_pool_virt_addr)
		वापस -ENOMEM;

	collective_cb_size = माप(काष्ठा packet_msg_लघु) * 5 +
			माप(काष्ठा packet_fence);
	min_alloc_order = ilog2(collective_cb_size);

	hdev->पूर्णांकernal_cb_pool = gen_pool_create(min_alloc_order, -1);
	अगर (!hdev->पूर्णांकernal_cb_pool) अणु
		dev_err(hdev->dev,
			"Failed to create internal CB pool\n");
		rc = -ENOMEM;
		जाओ मुक्त_पूर्णांकernal_cb_pool;
	पूर्ण

	rc = gen_pool_add(hdev->पूर्णांकernal_cb_pool,
				(uपूर्णांकptr_t) hdev->पूर्णांकernal_cb_pool_virt_addr,
				HOST_SPACE_INTERNAL_CB_SZ, -1);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to add memory to internal CB pool\n");
		rc = -EFAULT;
		जाओ destroy_पूर्णांकernal_cb_pool;
	पूर्ण

	hdev->पूर्णांकernal_cb_va_base = hl_reserve_va_block(hdev, ctx,
			HL_VA_RANGE_TYPE_HOST, HOST_SPACE_INTERNAL_CB_SZ,
			HL_MMU_VA_ALIGNMENT_NOT_NEEDED);

	अगर (!hdev->पूर्णांकernal_cb_va_base)
		जाओ destroy_पूर्णांकernal_cb_pool;

	mutex_lock(&ctx->mmu_lock);
	rc = hl_mmu_map_contiguous(ctx, hdev->पूर्णांकernal_cb_va_base,
			hdev->पूर्णांकernal_cb_pool_dma_addr,
			HOST_SPACE_INTERNAL_CB_SZ);

	hdev->asic_funcs->mmu_invalidate_cache(hdev, false, VM_TYPE_USERPTR);
	mutex_unlock(&ctx->mmu_lock);

	अगर (rc)
		जाओ unreserve_पूर्णांकernal_cb_pool;

	वापस 0;

unreserve_पूर्णांकernal_cb_pool:
	hl_unreserve_va_block(hdev, ctx, hdev->पूर्णांकernal_cb_va_base,
			HOST_SPACE_INTERNAL_CB_SZ);
destroy_पूर्णांकernal_cb_pool:
	gen_pool_destroy(hdev->पूर्णांकernal_cb_pool);
मुक्त_पूर्णांकernal_cb_pool:
	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
			HOST_SPACE_INTERNAL_CB_SZ,
			hdev->पूर्णांकernal_cb_pool_virt_addr,
			hdev->पूर्णांकernal_cb_pool_dma_addr);

	वापस rc;
पूर्ण

अटल व्योम gaudi_पूर्णांकernal_cb_pool_fini(काष्ठा hl_device *hdev,
		काष्ठा hl_ctx *ctx)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (!(gaudi->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	mutex_lock(&ctx->mmu_lock);
	hl_mmu_unmap_contiguous(ctx, hdev->पूर्णांकernal_cb_va_base,
			HOST_SPACE_INTERNAL_CB_SZ);
	hl_unreserve_va_block(hdev, ctx, hdev->पूर्णांकernal_cb_va_base,
			HOST_SPACE_INTERNAL_CB_SZ);
	hdev->asic_funcs->mmu_invalidate_cache(hdev, true, VM_TYPE_USERPTR);
	mutex_unlock(&ctx->mmu_lock);

	gen_pool_destroy(hdev->पूर्णांकernal_cb_pool);

	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
			HOST_SPACE_INTERNAL_CB_SZ,
			hdev->पूर्णांकernal_cb_pool_virt_addr,
			hdev->पूर्णांकernal_cb_pool_dma_addr);
पूर्ण

अटल पूर्णांक gaudi_ctx_init(काष्ठा hl_ctx *ctx)
अणु
	अगर (ctx->asid == HL_KERNEL_ASID_ID)
		वापस 0;

	gaudi_mmu_prepare(ctx->hdev, ctx->asid);
	वापस gaudi_पूर्णांकernal_cb_pool_init(ctx->hdev, ctx);
पूर्ण

अटल व्योम gaudi_ctx_fini(काष्ठा hl_ctx *ctx)
अणु
	अगर (ctx->asid == HL_KERNEL_ASID_ID)
		वापस;

	gaudi_पूर्णांकernal_cb_pool_fini(ctx->hdev, ctx);
पूर्ण

अटल u32 gaudi_get_queue_id_क्रम_cq(काष्ठा hl_device *hdev, u32 cq_idx)
अणु
	वापस gaudi_cq_assignment[cq_idx];
पूर्ण

अटल u32 gaudi_get_संकेत_cb_size(काष्ठा hl_device *hdev)
अणु
	वापस माप(काष्ठा packet_msg_लघु) +
			माप(काष्ठा packet_msg_prot) * 2;
पूर्ण

अटल u32 gaudi_get_रुको_cb_size(काष्ठा hl_device *hdev)
अणु
	वापस माप(काष्ठा packet_msg_लघु) * 4 +
			माप(काष्ठा packet_fence) +
			माप(काष्ठा packet_msg_prot) * 2;
पूर्ण

अटल u32 gaudi_gen_संकेत_cb(काष्ठा hl_device *hdev, व्योम *data, u16 sob_id,
				u32 size, bool eb)
अणु
	काष्ठा hl_cb *cb = (काष्ठा hl_cb *) data;
	काष्ठा packet_msg_लघु *pkt;
	u32 value, ctl, pkt_size = माप(*pkt);

	pkt = cb->kernel_address + size;
	स_रखो(pkt, 0, pkt_size);

	/* Inc by 1, Mode ADD */
	value = FIELD_PREP(GAUDI_PKT_SHORT_VAL_SOB_SYNC_VAL_MASK, 1);
	value |= FIELD_PREP(GAUDI_PKT_SHORT_VAL_SOB_MOD_MASK, 1);

	ctl = FIELD_PREP(GAUDI_PKT_SHORT_CTL_ADDR_MASK, sob_id * 4);
	ctl |= FIELD_PREP(GAUDI_PKT_SHORT_CTL_OP_MASK, 0); /* ग_लिखो the value */
	ctl |= FIELD_PREP(GAUDI_PKT_SHORT_CTL_BASE_MASK, 3); /* W_S SOB base */
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_SHORT);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, eb);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	pkt->value = cpu_to_le32(value);
	pkt->ctl = cpu_to_le32(ctl);

	वापस size + pkt_size;
पूर्ण

अटल u32 gaudi_add_mon_msg_लघु(काष्ठा packet_msg_लघु *pkt, u32 value,
					u16 addr)
अणु
	u32 ctl, pkt_size = माप(*pkt);

	स_रखो(pkt, 0, pkt_size);

	ctl = FIELD_PREP(GAUDI_PKT_SHORT_CTL_ADDR_MASK, addr);
	ctl |= FIELD_PREP(GAUDI_PKT_SHORT_CTL_BASE_MASK, 2);  /* W_S MON base */
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_SHORT);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 0);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 0); /* last pkt MB */

	pkt->value = cpu_to_le32(value);
	pkt->ctl = cpu_to_le32(ctl);

	वापस pkt_size;
पूर्ण

अटल u32 gaudi_add_arm_monitor_pkt(काष्ठा hl_device *hdev,
		काष्ठा packet_msg_लघु *pkt, u16 sob_base, u8 sob_mask,
		u16 sob_val, u16 mon_id)
अणु
	u64 monitor_base;
	u32 ctl, value, pkt_size = माप(*pkt);
	u16 msg_addr_offset;
	u8 mask;

	अगर (hl_gen_sob_mask(sob_base, sob_mask, &mask)) अणु
		dev_err(hdev->dev,
			"sob_base %u (mask %#x) is not valid\n",
			sob_base, sob_mask);
		वापस 0;
	पूर्ण

	/*
	 * monitor_base should be the content of the base0 address रेजिस्टरs,
	 * so it will be added to the msg लघु offsets
	 */
	monitor_base = mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0;

	msg_addr_offset =
		(mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_ARM_0 + mon_id * 4) -
				monitor_base;

	स_रखो(pkt, 0, pkt_size);

	/* Monitor config packet: bind the monitor to a sync object */
	value = FIELD_PREP(GAUDI_PKT_SHORT_VAL_MON_SYNC_GID_MASK, sob_base / 8);
	value |= FIELD_PREP(GAUDI_PKT_SHORT_VAL_MON_SYNC_VAL_MASK, sob_val);
	value |= FIELD_PREP(GAUDI_PKT_SHORT_VAL_MON_MODE_MASK,
			0); /* GREATER OR EQUAL*/
	value |= FIELD_PREP(GAUDI_PKT_SHORT_VAL_MON_MASK_MASK, mask);

	ctl = FIELD_PREP(GAUDI_PKT_SHORT_CTL_ADDR_MASK, msg_addr_offset);
	ctl |= FIELD_PREP(GAUDI_PKT_SHORT_CTL_OP_MASK, 0); /* ग_लिखो the value */
	ctl |= FIELD_PREP(GAUDI_PKT_SHORT_CTL_BASE_MASK, 2); /* W_S MON base */
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_MSG_SHORT);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 0);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	pkt->value = cpu_to_le32(value);
	pkt->ctl = cpu_to_le32(ctl);

	वापस pkt_size;
पूर्ण

अटल u32 gaudi_add_fence_pkt(काष्ठा packet_fence *pkt)
अणु
	u32 ctl, cfg, pkt_size = माप(*pkt);

	स_रखो(pkt, 0, pkt_size);

	cfg = FIELD_PREP(GAUDI_PKT_FENCE_CFG_DEC_VAL_MASK, 1);
	cfg |= FIELD_PREP(GAUDI_PKT_FENCE_CFG_TARGET_VAL_MASK, 1);
	cfg |= FIELD_PREP(GAUDI_PKT_FENCE_CFG_ID_MASK, 2);

	ctl = FIELD_PREP(GAUDI_PKT_CTL_OPCODE_MASK, PACKET_FENCE);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_EB_MASK, 0);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_RB_MASK, 1);
	ctl |= FIELD_PREP(GAUDI_PKT_CTL_MB_MASK, 1);

	pkt->cfg = cpu_to_le32(cfg);
	pkt->ctl = cpu_to_le32(ctl);

	वापस pkt_size;
पूर्ण

अटल पूर्णांक gaudi_get_fence_addr(काष्ठा hl_device *hdev, u32 queue_id, u64 *addr)
अणु
	u32 offset, nic_index;

	चयन (queue_id) अणु
	हाल GAUDI_QUEUE_ID_DMA_0_0:
		offset = mmDMA0_QM_CP_FENCE2_RDATA_0;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_0_1:
		offset = mmDMA0_QM_CP_FENCE2_RDATA_1;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_0_2:
		offset = mmDMA0_QM_CP_FENCE2_RDATA_2;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_0_3:
		offset = mmDMA0_QM_CP_FENCE2_RDATA_3;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_1_0:
		offset = mmDMA1_QM_CP_FENCE2_RDATA_0;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_1_1:
		offset = mmDMA1_QM_CP_FENCE2_RDATA_1;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_1_2:
		offset = mmDMA1_QM_CP_FENCE2_RDATA_2;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_1_3:
		offset = mmDMA1_QM_CP_FENCE2_RDATA_3;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_5_0:
		offset = mmDMA5_QM_CP_FENCE2_RDATA_0;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_5_1:
		offset = mmDMA5_QM_CP_FENCE2_RDATA_1;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_5_2:
		offset = mmDMA5_QM_CP_FENCE2_RDATA_2;
		अवरोध;
	हाल GAUDI_QUEUE_ID_DMA_5_3:
		offset = mmDMA5_QM_CP_FENCE2_RDATA_3;
		अवरोध;
	हाल GAUDI_QUEUE_ID_TPC_7_0:
		offset = mmTPC7_QM_CP_FENCE2_RDATA_0;
		अवरोध;
	हाल GAUDI_QUEUE_ID_TPC_7_1:
		offset = mmTPC7_QM_CP_FENCE2_RDATA_1;
		अवरोध;
	हाल GAUDI_QUEUE_ID_TPC_7_2:
		offset = mmTPC7_QM_CP_FENCE2_RDATA_2;
		अवरोध;
	हाल GAUDI_QUEUE_ID_TPC_7_3:
		offset = mmTPC7_QM_CP_FENCE2_RDATA_3;
		अवरोध;
	हाल GAUDI_QUEUE_ID_NIC_0_0:
	हाल GAUDI_QUEUE_ID_NIC_1_0:
	हाल GAUDI_QUEUE_ID_NIC_2_0:
	हाल GAUDI_QUEUE_ID_NIC_3_0:
	हाल GAUDI_QUEUE_ID_NIC_4_0:
	हाल GAUDI_QUEUE_ID_NIC_5_0:
	हाल GAUDI_QUEUE_ID_NIC_6_0:
	हाल GAUDI_QUEUE_ID_NIC_7_0:
	हाल GAUDI_QUEUE_ID_NIC_8_0:
	हाल GAUDI_QUEUE_ID_NIC_9_0:
		nic_index = (queue_id - GAUDI_QUEUE_ID_NIC_0_0) >> 2;
		offset = mmNIC0_QM0_CP_FENCE2_RDATA_0 +
				(nic_index >> 1) * NIC_MACRO_QMAN_OFFSET +
				(nic_index & 0x1) * NIC_ENGINE_QMAN_OFFSET;
		अवरोध;
	हाल GAUDI_QUEUE_ID_NIC_0_1:
	हाल GAUDI_QUEUE_ID_NIC_1_1:
	हाल GAUDI_QUEUE_ID_NIC_2_1:
	हाल GAUDI_QUEUE_ID_NIC_3_1:
	हाल GAUDI_QUEUE_ID_NIC_4_1:
	हाल GAUDI_QUEUE_ID_NIC_5_1:
	हाल GAUDI_QUEUE_ID_NIC_6_1:
	हाल GAUDI_QUEUE_ID_NIC_7_1:
	हाल GAUDI_QUEUE_ID_NIC_8_1:
	हाल GAUDI_QUEUE_ID_NIC_9_1:
		nic_index = (queue_id - GAUDI_QUEUE_ID_NIC_0_1) >> 2;
		offset = mmNIC0_QM0_CP_FENCE2_RDATA_1 +
				(nic_index >> 1) * NIC_MACRO_QMAN_OFFSET +
				(nic_index & 0x1) * NIC_ENGINE_QMAN_OFFSET;
		अवरोध;
	हाल GAUDI_QUEUE_ID_NIC_0_2:
	हाल GAUDI_QUEUE_ID_NIC_1_2:
	हाल GAUDI_QUEUE_ID_NIC_2_2:
	हाल GAUDI_QUEUE_ID_NIC_3_2:
	हाल GAUDI_QUEUE_ID_NIC_4_2:
	हाल GAUDI_QUEUE_ID_NIC_5_2:
	हाल GAUDI_QUEUE_ID_NIC_6_2:
	हाल GAUDI_QUEUE_ID_NIC_7_2:
	हाल GAUDI_QUEUE_ID_NIC_8_2:
	हाल GAUDI_QUEUE_ID_NIC_9_2:
		nic_index = (queue_id - GAUDI_QUEUE_ID_NIC_0_2) >> 2;
		offset = mmNIC0_QM0_CP_FENCE2_RDATA_2 +
				(nic_index >> 1) * NIC_MACRO_QMAN_OFFSET +
				(nic_index & 0x1) * NIC_ENGINE_QMAN_OFFSET;
		अवरोध;
	हाल GAUDI_QUEUE_ID_NIC_0_3:
	हाल GAUDI_QUEUE_ID_NIC_1_3:
	हाल GAUDI_QUEUE_ID_NIC_2_3:
	हाल GAUDI_QUEUE_ID_NIC_3_3:
	हाल GAUDI_QUEUE_ID_NIC_4_3:
	हाल GAUDI_QUEUE_ID_NIC_5_3:
	हाल GAUDI_QUEUE_ID_NIC_6_3:
	हाल GAUDI_QUEUE_ID_NIC_7_3:
	हाल GAUDI_QUEUE_ID_NIC_8_3:
	हाल GAUDI_QUEUE_ID_NIC_9_3:
		nic_index = (queue_id - GAUDI_QUEUE_ID_NIC_0_3) >> 2;
		offset = mmNIC0_QM0_CP_FENCE2_RDATA_3 +
				(nic_index >> 1) * NIC_MACRO_QMAN_OFFSET +
				(nic_index & 0x1) * NIC_ENGINE_QMAN_OFFSET;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*addr = CFG_BASE + offset;

	वापस 0;
पूर्ण

अटल u32 gaudi_add_mon_pkts(व्योम *buf, u16 mon_id, u64 fence_addr)
अणु
	u64 monitor_base;
	u32 size = 0;
	u16 msg_addr_offset;

	/*
	 * monitor_base should be the content of the base0 address रेजिस्टरs,
	 * so it will be added to the msg लघु offsets
	 */
	monitor_base = mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0;

	/* First monitor config packet: low address of the sync */
	msg_addr_offset =
		(mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRL_0 + mon_id * 4) -
				monitor_base;

	size += gaudi_add_mon_msg_लघु(buf + size, (u32) fence_addr,
					msg_addr_offset);

	/* Second monitor config packet: high address of the sync */
	msg_addr_offset =
		(mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_ADDRH_0 + mon_id * 4) -
				monitor_base;

	size += gaudi_add_mon_msg_लघु(buf + size, (u32) (fence_addr >> 32),
					msg_addr_offset);

	/*
	 * Third monitor config packet: the payload, i.e. what to ग_लिखो when the
	 * sync triggers
	 */
	msg_addr_offset =
		(mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_MON_PAY_DATA_0 + mon_id * 4) -
				monitor_base;

	size += gaudi_add_mon_msg_लघु(buf + size, 1, msg_addr_offset);

	वापस size;
पूर्ण

अटल u32 gaudi_gen_रुको_cb(काष्ठा hl_device *hdev,
				काष्ठा hl_gen_रुको_properties *prop)
अणु
	काष्ठा hl_cb *cb = (काष्ठा hl_cb *) prop->data;
	व्योम *buf = cb->kernel_address;
	u64 fence_addr = 0;
	u32 size = prop->size;

	अगर (gaudi_get_fence_addr(hdev, prop->q_idx, &fence_addr)) अणु
		dev_crit(hdev->dev, "wrong queue id %d for wait packet\n",
				prop->q_idx);
		वापस 0;
	पूर्ण

	size += gaudi_add_mon_pkts(buf + size, prop->mon_id, fence_addr);
	size += gaudi_add_arm_monitor_pkt(hdev, buf + size, prop->sob_base,
			prop->sob_mask, prop->sob_val, prop->mon_id);
	size += gaudi_add_fence_pkt(buf + size);

	वापस size;
पूर्ण

अटल व्योम gaudi_reset_sob(काष्ठा hl_device *hdev, व्योम *data)
अणु
	काष्ठा hl_hw_sob *hw_sob = (काष्ठा hl_hw_sob *) data;
	पूर्णांक rc;

	dev_dbg(hdev->dev, "reset SOB, q_idx: %d, sob_id: %d\n", hw_sob->q_idx,
		hw_sob->sob_id);

	rc = gaudi_schedule_रेजिस्टर_स_रखो(hdev, hw_sob->q_idx,
			CFG_BASE + mmSYNC_MNGR_W_S_SYNC_MNGR_OBJS_SOB_OBJ_0 +
			hw_sob->sob_id * 4, 1, 0);
	अगर (rc)
		dev_err(hdev->dev, "failed resetting sob %u", hw_sob->sob_id);

	kref_init(&hw_sob->kref);
पूर्ण

अटल व्योम gaudi_set_dma_mask_from_fw(काष्ठा hl_device *hdev)
अणु
	अगर (RREG32(mmPSOC_GLOBAL_CONF_NON_RST_FLOPS_0) ==
							HL_POWER9_HOST_MAGIC) अणु
		hdev->घातer9_64bit_dma_enable = 1;
		hdev->dma_mask = 64;
	पूर्ण अन्यथा अणु
		hdev->घातer9_64bit_dma_enable = 0;
		hdev->dma_mask = 48;
	पूर्ण
पूर्ण

अटल u64 gaudi_get_device_समय(काष्ठा hl_device *hdev)
अणु
	u64 device_समय = ((u64) RREG32(mmPSOC_TIMESTAMP_CNTCVU)) << 32;

	वापस device_समय | RREG32(mmPSOC_TIMESTAMP_CNTCVL);
पूर्ण

अटल पूर्णांक gaudi_get_hw_block_id(काष्ठा hl_device *hdev, u64 block_addr,
				u32 *block_size, u32 *block_id)
अणु
	वापस -EPERM;
पूर्ण

अटल पूर्णांक gaudi_block_mmap(काष्ठा hl_device *hdev,
				काष्ठा vm_area_काष्ठा *vma,
				u32 block_id, u32 block_size)
अणु
	वापस -EPERM;
पूर्ण

अटल व्योम gaudi_enable_events_from_fw(काष्ठा hl_device *hdev)
अणु
	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR, GAUDI_EVENT_INTS_REGISTER);
पूर्ण

अटल पूर्णांक gaudi_map_pll_idx_to_fw_idx(u32 pll_idx)
अणु
	चयन (pll_idx) अणु
	हाल HL_GAUDI_CPU_PLL: वापस CPU_PLL;
	हाल HL_GAUDI_PCI_PLL: वापस PCI_PLL;
	हाल HL_GAUDI_NIC_PLL: वापस NIC_PLL;
	हाल HL_GAUDI_DMA_PLL: वापस DMA_PLL;
	हाल HL_GAUDI_MESH_PLL: वापस MESH_PLL;
	हाल HL_GAUDI_MME_PLL: वापस MME_PLL;
	हाल HL_GAUDI_TPC_PLL: वापस TPC_PLL;
	हाल HL_GAUDI_IF_PLL: वापस IF_PLL;
	हाल HL_GAUDI_SRAM_PLL: वापस SRAM_PLL;
	हाल HL_GAUDI_HBM_PLL: वापस HBM_PLL;
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hl_asic_funcs gaudi_funcs = अणु
	.early_init = gaudi_early_init,
	.early_fini = gaudi_early_fini,
	.late_init = gaudi_late_init,
	.late_fini = gaudi_late_fini,
	.sw_init = gaudi_sw_init,
	.sw_fini = gaudi_sw_fini,
	.hw_init = gaudi_hw_init,
	.hw_fini = gaudi_hw_fini,
	.halt_engines = gaudi_halt_engines,
	.suspend = gaudi_suspend,
	.resume = gaudi_resume,
	.cb_mmap = gaudi_cb_mmap,
	.ring_करोorbell = gaudi_ring_करोorbell,
	.pqe_ग_लिखो = gaudi_pqe_ग_लिखो,
	.asic_dma_alloc_coherent = gaudi_dma_alloc_coherent,
	.asic_dma_मुक्त_coherent = gaudi_dma_मुक्त_coherent,
	.scrub_device_mem = gaudi_scrub_device_mem,
	.get_पूर्णांक_queue_base = gaudi_get_पूर्णांक_queue_base,
	.test_queues = gaudi_test_queues,
	.asic_dma_pool_zalloc = gaudi_dma_pool_zalloc,
	.asic_dma_pool_मुक्त = gaudi_dma_pool_मुक्त,
	.cpu_accessible_dma_pool_alloc = gaudi_cpu_accessible_dma_pool_alloc,
	.cpu_accessible_dma_pool_मुक्त = gaudi_cpu_accessible_dma_pool_मुक्त,
	.hl_dma_unmap_sg = gaudi_dma_unmap_sg,
	.cs_parser = gaudi_cs_parser,
	.asic_dma_map_sg = gaudi_dma_map_sg,
	.get_dma_desc_list_size = gaudi_get_dma_desc_list_size,
	.add_end_of_cb_packets = gaudi_add_end_of_cb_packets,
	.update_eq_ci = gaudi_update_eq_ci,
	.context_चयन = gaudi_context_चयन,
	.restore_phase_topology = gaudi_restore_phase_topology,
	.debugfs_पढ़ो32 = gaudi_debugfs_पढ़ो32,
	.debugfs_ग_लिखो32 = gaudi_debugfs_ग_लिखो32,
	.debugfs_पढ़ो64 = gaudi_debugfs_पढ़ो64,
	.debugfs_ग_लिखो64 = gaudi_debugfs_ग_लिखो64,
	.debugfs_पढ़ो_dma = gaudi_debugfs_पढ़ो_dma,
	.add_device_attr = gaudi_add_device_attr,
	.handle_eqe = gaudi_handle_eqe,
	.set_pll_profile = gaudi_set_pll_profile,
	.get_events_stat = gaudi_get_events_stat,
	.पढ़ो_pte = gaudi_पढ़ो_pte,
	.ग_लिखो_pte = gaudi_ग_लिखो_pte,
	.mmu_invalidate_cache = gaudi_mmu_invalidate_cache,
	.mmu_invalidate_cache_range = gaudi_mmu_invalidate_cache_range,
	.send_heartbeat = gaudi_send_heartbeat,
	.set_घड़ी_gating = gaudi_set_घड़ी_gating,
	.disable_घड़ी_gating = gaudi_disable_घड़ी_gating,
	.debug_coresight = gaudi_debug_coresight,
	.is_device_idle = gaudi_is_device_idle,
	.soft_reset_late_init = gaudi_soft_reset_late_init,
	.hw_queues_lock = gaudi_hw_queues_lock,
	.hw_queues_unlock = gaudi_hw_queues_unlock,
	.get_pci_id = gaudi_get_pci_id,
	.get_eeprom_data = gaudi_get_eeprom_data,
	.send_cpu_message = gaudi_send_cpu_message,
	.pci_bars_map = gaudi_pci_bars_map,
	.init_iatu = gaudi_init_iatu,
	.rreg = hl_rreg,
	.wreg = hl_wreg,
	.halt_coresight = gaudi_halt_coresight,
	.ctx_init = gaudi_ctx_init,
	.ctx_fini = gaudi_ctx_fini,
	.get_clk_rate = gaudi_get_clk_rate,
	.get_queue_id_क्रम_cq = gaudi_get_queue_id_क्रम_cq,
	.पढ़ो_device_fw_version = gaudi_पढ़ो_device_fw_version,
	.load_firmware_to_device = gaudi_load_firmware_to_device,
	.load_boot_fit_to_device = gaudi_load_boot_fit_to_device,
	.get_संकेत_cb_size = gaudi_get_संकेत_cb_size,
	.get_रुको_cb_size = gaudi_get_रुको_cb_size,
	.gen_संकेत_cb = gaudi_gen_संकेत_cb,
	.gen_रुको_cb = gaudi_gen_रुको_cb,
	.reset_sob = gaudi_reset_sob,
	.reset_sob_group = gaudi_reset_sob_group,
	.set_dma_mask_from_fw = gaudi_set_dma_mask_from_fw,
	.get_device_समय = gaudi_get_device_समय,
	.collective_रुको_init_cs = gaudi_collective_रुको_init_cs,
	.collective_रुको_create_jobs = gaudi_collective_रुको_create_jobs,
	.scramble_addr = hl_mmu_scramble_addr,
	.descramble_addr = hl_mmu_descramble_addr,
	.ack_protection_bits_errors = gaudi_ack_protection_bits_errors,
	.get_hw_block_id = gaudi_get_hw_block_id,
	.hw_block_mmap = gaudi_block_mmap,
	.enable_events_from_fw = gaudi_enable_events_from_fw,
	.map_pll_idx_to_fw_idx = gaudi_map_pll_idx_to_fw_idx
पूर्ण;

/**
 * gaudi_set_asic_funcs - set GAUDI function poपूर्णांकers
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
व्योम gaudi_set_asic_funcs(काष्ठा hl_device *hdev)
अणु
	hdev->asic_funcs = &gaudi_funcs;
पूर्ण
