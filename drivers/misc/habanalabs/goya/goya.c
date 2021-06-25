<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "goyaP.h"
#समावेश "../include/hw_ip/mmu/mmu_general.h"
#समावेश "../include/hw_ip/mmu/mmu_v1_0.h"
#समावेश "../include/goya/asic_reg/goya_masks.h"
#समावेश "../include/goya/goya_reg_map.h"

#समावेश <linux/pci.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/iommu.h>
#समावेश <linux/seq_file.h>

/*
 * GOYA security scheme:
 *
 * 1. Host is रक्षित by:
 *        - Range रेजिस्टरs (When MMU is enabled, DMA RR करोes NOT protect host)
 *        - MMU
 *
 * 2. DRAM is रक्षित by:
 *        - Range रेजिस्टरs (protect the first 512MB)
 *        - MMU (isolation between users)
 *
 * 3. Configuration is रक्षित by:
 *        - Range रेजिस्टरs
 *        - Protection bits
 *
 * When MMU is disabled:
 *
 * QMAN DMA: PQ, CQ, CP, DMA are secured.
 * PQ, CB and the data are on the host.
 *
 * QMAN TPC/MME:
 * PQ, CQ and CP are not secured.
 * PQ, CB and the data are on the SRAM/DRAM.
 *
 * Since QMAN DMA is secured, the driver is parsing the DMA CB:
 *     - checks DMA poपूर्णांकer
 *     - WREG, MSG_PROT are not allowed.
 *     - MSG_LONG/SHORT are allowed.
 *
 * A पढ़ो/ग_लिखो transaction by the QMAN to a रक्षित area will succeed अगर
 * and only अगर the QMAN's CP is secured and MSG_PROT is used
 *
 *
 * When MMU is enabled:
 *
 * QMAN DMA: PQ, CQ and CP are secured.
 * MMU is set to bypass on the Secure props रेजिस्टर of the QMAN.
 * The reasons we करोn't enable MMU क्रम PQ, CQ and CP are:
 *     - PQ entry is in kernel address space and the driver करोesn't map it.
 *     - CP ग_लिखोs to MSIX रेजिस्टर and to kernel address space (completion
 *       queue).
 *
 * DMA is not secured but because CP is secured, the driver still needs to parse
 * the CB, but करोesn't need to check the DMA addresses.
 *
 * For QMAN DMA 0, DMA is also secured because only the driver uses this DMA and
 * the driver करोesn't map memory in MMU.
 *
 * QMAN TPC/MME: PQ, CQ and CP aren't secured (no change from MMU disabled mode)
 *
 * DMA RR करोes NOT protect host because DMA is not secured
 *
 */

#घोषणा GOYA_BOOT_FIT_खाता	"habanalabs/goya/goya-boot-fit.itb"
#घोषणा GOYA_LINUX_FW_खाता	"habanalabs/goya/goya-fit.itb"

#घोषणा GOYA_MMU_REGS_NUM		63

#घोषणा GOYA_DMA_POOL_BLK_SIZE		0x100		/* 256 bytes */

#घोषणा GOYA_RESET_TIMEOUT_MSEC		500		/* 500ms */
#घोषणा GOYA_PLDM_RESET_TIMEOUT_MSEC	20000		/* 20s */
#घोषणा GOYA_RESET_WAIT_MSEC		1		/* 1ms */
#घोषणा GOYA_CPU_RESET_WAIT_MSEC	100		/* 100ms */
#घोषणा GOYA_PLDM_RESET_WAIT_MSEC	1000		/* 1s */
#घोषणा GOYA_TEST_QUEUE_WAIT_USEC	100000		/* 100ms */
#घोषणा GOYA_PLDM_MMU_TIMEOUT_USEC	(MMU_CONFIG_TIMEOUT_USEC * 100)
#घोषणा GOYA_PLDM_QMAN0_TIMEOUT_USEC	(HL_DEVICE_TIMEOUT_USEC * 30)
#घोषणा GOYA_BOOT_FIT_REQ_TIMEOUT_USEC	1000000		/* 1s */
#घोषणा GOYA_MSG_TO_CPU_TIMEOUT_USEC	4000000		/* 4s */

#घोषणा GOYA_QMAN0_FENCE_VAL		0xD169B243

#घोषणा GOYA_MAX_STRING_LEN		20

#घोषणा GOYA_CB_POOL_CB_CNT		512
#घोषणा GOYA_CB_POOL_CB_SIZE		0x20000		/* 128KB */

#घोषणा IS_QM_IDLE(engine, qm_glbl_sts0) \
	(((qm_glbl_sts0) & engine##_QM_IDLE_MASK) == engine##_QM_IDLE_MASK)
#घोषणा IS_DMA_QM_IDLE(qm_glbl_sts0)	IS_QM_IDLE(DMA, qm_glbl_sts0)
#घोषणा IS_TPC_QM_IDLE(qm_glbl_sts0)	IS_QM_IDLE(TPC, qm_glbl_sts0)
#घोषणा IS_MME_QM_IDLE(qm_glbl_sts0)	IS_QM_IDLE(MME, qm_glbl_sts0)

#घोषणा IS_CMDQ_IDLE(engine, cmdq_glbl_sts0) \
	(((cmdq_glbl_sts0) & engine##_CMDQ_IDLE_MASK) == \
			engine##_CMDQ_IDLE_MASK)
#घोषणा IS_TPC_CMDQ_IDLE(cmdq_glbl_sts0) \
	IS_CMDQ_IDLE(TPC, cmdq_glbl_sts0)
#घोषणा IS_MME_CMDQ_IDLE(cmdq_glbl_sts0) \
	IS_CMDQ_IDLE(MME, cmdq_glbl_sts0)

#घोषणा IS_DMA_IDLE(dma_core_sts0) \
	!((dma_core_sts0) & DMA_CH_0_STS0_DMA_BUSY_MASK)

#घोषणा IS_TPC_IDLE(tpc_cfg_sts) \
	(((tpc_cfg_sts) & TPC_CFG_IDLE_MASK) == TPC_CFG_IDLE_MASK)

#घोषणा IS_MME_IDLE(mme_arch_sts) \
	(((mme_arch_sts) & MME_ARCH_IDLE_MASK) == MME_ARCH_IDLE_MASK)

अटल स्थिर अक्षर goya_irq_name[GOYA_MSIX_ENTRIES][GOYA_MAX_STRING_LEN] = अणु
		"goya cq 0", "goya cq 1", "goya cq 2", "goya cq 3",
		"goya cq 4", "goya cpu eq"
पूर्ण;

अटल u16 goya_packet_sizes[MAX_PACKET_ID] = अणु
	[PACKET_WREG_32]	= माप(काष्ठा packet_wreg32),
	[PACKET_WREG_BULK]	= माप(काष्ठा packet_wreg_bulk),
	[PACKET_MSG_LONG]	= माप(काष्ठा packet_msg_दीर्घ),
	[PACKET_MSG_SHORT]	= माप(काष्ठा packet_msg_लघु),
	[PACKET_CP_DMA]		= माप(काष्ठा packet_cp_dma),
	[PACKET_MSG_PROT]	= माप(काष्ठा packet_msg_prot),
	[PACKET_FENCE]		= माप(काष्ठा packet_fence),
	[PACKET_LIN_DMA]	= माप(काष्ठा packet_lin_dma),
	[PACKET_NOP]		= माप(काष्ठा packet_nop),
	[PACKET_STOP]		= माप(काष्ठा packet_stop)
पूर्ण;

अटल अंतरभूत bool validate_packet_id(क्रमागत packet_id id)
अणु
	चयन (id) अणु
	हाल PACKET_WREG_32:
	हाल PACKET_WREG_BULK:
	हाल PACKET_MSG_LONG:
	हाल PACKET_MSG_SHORT:
	हाल PACKET_CP_DMA:
	हाल PACKET_MSG_PROT:
	हाल PACKET_FENCE:
	हाल PACKET_LIN_DMA:
	हाल PACKET_NOP:
	हाल PACKET_STOP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u64 goya_mmu_regs[GOYA_MMU_REGS_NUM] = अणु
	mmDMA_QM_0_GLBL_NON_SECURE_PROPS,
	mmDMA_QM_1_GLBL_NON_SECURE_PROPS,
	mmDMA_QM_2_GLBL_NON_SECURE_PROPS,
	mmDMA_QM_3_GLBL_NON_SECURE_PROPS,
	mmDMA_QM_4_GLBL_NON_SECURE_PROPS,
	mmTPC0_QM_GLBL_SECURE_PROPS,
	mmTPC0_QM_GLBL_NON_SECURE_PROPS,
	mmTPC0_CMDQ_GLBL_SECURE_PROPS,
	mmTPC0_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC0_CFG_ARUSER,
	mmTPC0_CFG_AWUSER,
	mmTPC1_QM_GLBL_SECURE_PROPS,
	mmTPC1_QM_GLBL_NON_SECURE_PROPS,
	mmTPC1_CMDQ_GLBL_SECURE_PROPS,
	mmTPC1_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC1_CFG_ARUSER,
	mmTPC1_CFG_AWUSER,
	mmTPC2_QM_GLBL_SECURE_PROPS,
	mmTPC2_QM_GLBL_NON_SECURE_PROPS,
	mmTPC2_CMDQ_GLBL_SECURE_PROPS,
	mmTPC2_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC2_CFG_ARUSER,
	mmTPC2_CFG_AWUSER,
	mmTPC3_QM_GLBL_SECURE_PROPS,
	mmTPC3_QM_GLBL_NON_SECURE_PROPS,
	mmTPC3_CMDQ_GLBL_SECURE_PROPS,
	mmTPC3_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC3_CFG_ARUSER,
	mmTPC3_CFG_AWUSER,
	mmTPC4_QM_GLBL_SECURE_PROPS,
	mmTPC4_QM_GLBL_NON_SECURE_PROPS,
	mmTPC4_CMDQ_GLBL_SECURE_PROPS,
	mmTPC4_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC4_CFG_ARUSER,
	mmTPC4_CFG_AWUSER,
	mmTPC5_QM_GLBL_SECURE_PROPS,
	mmTPC5_QM_GLBL_NON_SECURE_PROPS,
	mmTPC5_CMDQ_GLBL_SECURE_PROPS,
	mmTPC5_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC5_CFG_ARUSER,
	mmTPC5_CFG_AWUSER,
	mmTPC6_QM_GLBL_SECURE_PROPS,
	mmTPC6_QM_GLBL_NON_SECURE_PROPS,
	mmTPC6_CMDQ_GLBL_SECURE_PROPS,
	mmTPC6_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC6_CFG_ARUSER,
	mmTPC6_CFG_AWUSER,
	mmTPC7_QM_GLBL_SECURE_PROPS,
	mmTPC7_QM_GLBL_NON_SECURE_PROPS,
	mmTPC7_CMDQ_GLBL_SECURE_PROPS,
	mmTPC7_CMDQ_GLBL_NON_SECURE_PROPS,
	mmTPC7_CFG_ARUSER,
	mmTPC7_CFG_AWUSER,
	mmMME_QM_GLBL_SECURE_PROPS,
	mmMME_QM_GLBL_NON_SECURE_PROPS,
	mmMME_CMDQ_GLBL_SECURE_PROPS,
	mmMME_CMDQ_GLBL_NON_SECURE_PROPS,
	mmMME_SBA_CONTROL_DATA,
	mmMME_SBB_CONTROL_DATA,
	mmMME_SBC_CONTROL_DATA,
	mmMME_WBC_CONTROL_DATA,
	mmPCIE_WRAP_PSOC_ARUSER,
	mmPCIE_WRAP_PSOC_AWUSER
पूर्ण;

अटल u32 goya_all_events[] = अणु
	GOYA_ASYNC_EVENT_ID_PCIE_IF,
	GOYA_ASYNC_EVENT_ID_TPC0_ECC,
	GOYA_ASYNC_EVENT_ID_TPC1_ECC,
	GOYA_ASYNC_EVENT_ID_TPC2_ECC,
	GOYA_ASYNC_EVENT_ID_TPC3_ECC,
	GOYA_ASYNC_EVENT_ID_TPC4_ECC,
	GOYA_ASYNC_EVENT_ID_TPC5_ECC,
	GOYA_ASYNC_EVENT_ID_TPC6_ECC,
	GOYA_ASYNC_EVENT_ID_TPC7_ECC,
	GOYA_ASYNC_EVENT_ID_MME_ECC,
	GOYA_ASYNC_EVENT_ID_MME_ECC_EXT,
	GOYA_ASYNC_EVENT_ID_MMU_ECC,
	GOYA_ASYNC_EVENT_ID_DMA_MACRO,
	GOYA_ASYNC_EVENT_ID_DMA_ECC,
	GOYA_ASYNC_EVENT_ID_CPU_IF_ECC,
	GOYA_ASYNC_EVENT_ID_PSOC_MEM,
	GOYA_ASYNC_EVENT_ID_PSOC_CORESIGHT,
	GOYA_ASYNC_EVENT_ID_SRAM0,
	GOYA_ASYNC_EVENT_ID_SRAM1,
	GOYA_ASYNC_EVENT_ID_SRAM2,
	GOYA_ASYNC_EVENT_ID_SRAM3,
	GOYA_ASYNC_EVENT_ID_SRAM4,
	GOYA_ASYNC_EVENT_ID_SRAM5,
	GOYA_ASYNC_EVENT_ID_SRAM6,
	GOYA_ASYNC_EVENT_ID_SRAM7,
	GOYA_ASYNC_EVENT_ID_SRAM8,
	GOYA_ASYNC_EVENT_ID_SRAM9,
	GOYA_ASYNC_EVENT_ID_SRAM10,
	GOYA_ASYNC_EVENT_ID_SRAM11,
	GOYA_ASYNC_EVENT_ID_SRAM12,
	GOYA_ASYNC_EVENT_ID_SRAM13,
	GOYA_ASYNC_EVENT_ID_SRAM14,
	GOYA_ASYNC_EVENT_ID_SRAM15,
	GOYA_ASYNC_EVENT_ID_SRAM16,
	GOYA_ASYNC_EVENT_ID_SRAM17,
	GOYA_ASYNC_EVENT_ID_SRAM18,
	GOYA_ASYNC_EVENT_ID_SRAM19,
	GOYA_ASYNC_EVENT_ID_SRAM20,
	GOYA_ASYNC_EVENT_ID_SRAM21,
	GOYA_ASYNC_EVENT_ID_SRAM22,
	GOYA_ASYNC_EVENT_ID_SRAM23,
	GOYA_ASYNC_EVENT_ID_SRAM24,
	GOYA_ASYNC_EVENT_ID_SRAM25,
	GOYA_ASYNC_EVENT_ID_SRAM26,
	GOYA_ASYNC_EVENT_ID_SRAM27,
	GOYA_ASYNC_EVENT_ID_SRAM28,
	GOYA_ASYNC_EVENT_ID_SRAM29,
	GOYA_ASYNC_EVENT_ID_GIC500,
	GOYA_ASYNC_EVENT_ID_PLL0,
	GOYA_ASYNC_EVENT_ID_PLL1,
	GOYA_ASYNC_EVENT_ID_PLL3,
	GOYA_ASYNC_EVENT_ID_PLL4,
	GOYA_ASYNC_EVENT_ID_PLL5,
	GOYA_ASYNC_EVENT_ID_PLL6,
	GOYA_ASYNC_EVENT_ID_AXI_ECC,
	GOYA_ASYNC_EVENT_ID_L2_RAM_ECC,
	GOYA_ASYNC_EVENT_ID_PSOC_GPIO_05_SW_RESET,
	GOYA_ASYNC_EVENT_ID_PSOC_GPIO_10_VRHOT_ICRIT,
	GOYA_ASYNC_EVENT_ID_PCIE_DEC,
	GOYA_ASYNC_EVENT_ID_TPC0_DEC,
	GOYA_ASYNC_EVENT_ID_TPC1_DEC,
	GOYA_ASYNC_EVENT_ID_TPC2_DEC,
	GOYA_ASYNC_EVENT_ID_TPC3_DEC,
	GOYA_ASYNC_EVENT_ID_TPC4_DEC,
	GOYA_ASYNC_EVENT_ID_TPC5_DEC,
	GOYA_ASYNC_EVENT_ID_TPC6_DEC,
	GOYA_ASYNC_EVENT_ID_TPC7_DEC,
	GOYA_ASYNC_EVENT_ID_MME_WACS,
	GOYA_ASYNC_EVENT_ID_MME_WACSD,
	GOYA_ASYNC_EVENT_ID_CPU_AXI_SPLITTER,
	GOYA_ASYNC_EVENT_ID_PSOC_AXI_DEC,
	GOYA_ASYNC_EVENT_ID_PSOC,
	GOYA_ASYNC_EVENT_ID_TPC0_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC1_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC2_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC3_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC4_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC5_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC6_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC7_KRN_ERR,
	GOYA_ASYNC_EVENT_ID_TPC0_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC1_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC2_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC3_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC4_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC5_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC6_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC7_CMDQ,
	GOYA_ASYNC_EVENT_ID_TPC0_QM,
	GOYA_ASYNC_EVENT_ID_TPC1_QM,
	GOYA_ASYNC_EVENT_ID_TPC2_QM,
	GOYA_ASYNC_EVENT_ID_TPC3_QM,
	GOYA_ASYNC_EVENT_ID_TPC4_QM,
	GOYA_ASYNC_EVENT_ID_TPC5_QM,
	GOYA_ASYNC_EVENT_ID_TPC6_QM,
	GOYA_ASYNC_EVENT_ID_TPC7_QM,
	GOYA_ASYNC_EVENT_ID_MME_QM,
	GOYA_ASYNC_EVENT_ID_MME_CMDQ,
	GOYA_ASYNC_EVENT_ID_DMA0_QM,
	GOYA_ASYNC_EVENT_ID_DMA1_QM,
	GOYA_ASYNC_EVENT_ID_DMA2_QM,
	GOYA_ASYNC_EVENT_ID_DMA3_QM,
	GOYA_ASYNC_EVENT_ID_DMA4_QM,
	GOYA_ASYNC_EVENT_ID_DMA0_CH,
	GOYA_ASYNC_EVENT_ID_DMA1_CH,
	GOYA_ASYNC_EVENT_ID_DMA2_CH,
	GOYA_ASYNC_EVENT_ID_DMA3_CH,
	GOYA_ASYNC_EVENT_ID_DMA4_CH,
	GOYA_ASYNC_EVENT_ID_TPC0_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC1_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC2_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC3_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC4_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC5_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC6_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_TPC7_BMON_SPMU,
	GOYA_ASYNC_EVENT_ID_DMA_BM_CH0,
	GOYA_ASYNC_EVENT_ID_DMA_BM_CH1,
	GOYA_ASYNC_EVENT_ID_DMA_BM_CH2,
	GOYA_ASYNC_EVENT_ID_DMA_BM_CH3,
	GOYA_ASYNC_EVENT_ID_DMA_BM_CH4,
	GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_S,
	GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_E,
	GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_S,
	GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_E
पूर्ण;

अटल पूर्णांक goya_mmu_clear_pgt_range(काष्ठा hl_device *hdev);
अटल पूर्णांक goya_mmu_set_dram_शेष_page(काष्ठा hl_device *hdev);
अटल पूर्णांक goya_mmu_add_mappings_क्रम_device_cpu(काष्ठा hl_device *hdev);
अटल व्योम goya_mmu_prepare(काष्ठा hl_device *hdev, u32 asid);

पूर्णांक goya_get_fixed_properties(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक i;

	prop->max_queues = GOYA_QUEUE_ID_SIZE;
	prop->hw_queues_props = kसुस्मृति(prop->max_queues,
			माप(काष्ठा hw_queue_properties),
			GFP_KERNEL);

	अगर (!prop->hw_queues_props)
		वापस -ENOMEM;

	क्रम (i = 0 ; i < NUMBER_OF_EXT_HW_QUEUES ; i++) अणु
		prop->hw_queues_props[i].type = QUEUE_TYPE_EXT;
		prop->hw_queues_props[i].driver_only = 0;
		prop->hw_queues_props[i].cb_alloc_flags = CB_ALLOC_KERNEL;
	पूर्ण

	क्रम (; i < NUMBER_OF_EXT_HW_QUEUES + NUMBER_OF_CPU_HW_QUEUES ; i++) अणु
		prop->hw_queues_props[i].type = QUEUE_TYPE_CPU;
		prop->hw_queues_props[i].driver_only = 1;
		prop->hw_queues_props[i].cb_alloc_flags = CB_ALLOC_KERNEL;
	पूर्ण

	क्रम (; i < NUMBER_OF_EXT_HW_QUEUES + NUMBER_OF_CPU_HW_QUEUES +
			NUMBER_OF_INT_HW_QUEUES; i++) अणु
		prop->hw_queues_props[i].type = QUEUE_TYPE_INT;
		prop->hw_queues_props[i].driver_only = 0;
		prop->hw_queues_props[i].cb_alloc_flags = CB_ALLOC_USER;
	पूर्ण

	prop->completion_queues_count = NUMBER_OF_CMPLT_QUEUES;

	prop->dram_base_address = DRAM_PHYS_BASE;
	prop->dram_size = DRAM_PHYS_DEFAULT_SIZE;
	prop->dram_end_address = prop->dram_base_address + prop->dram_size;
	prop->dram_user_base_address = DRAM_BASE_ADDR_USER;

	prop->sram_base_address = SRAM_BASE_ADDR;
	prop->sram_size = SRAM_SIZE;
	prop->sram_end_address = prop->sram_base_address + prop->sram_size;
	prop->sram_user_base_address = prop->sram_base_address +
						SRAM_USER_BASE_OFFSET;

	prop->mmu_pgt_addr = MMU_PAGE_TABLES_ADDR;
	prop->mmu_dram_शेष_page_addr = MMU_DRAM_DEFAULT_PAGE_ADDR;
	अगर (hdev->pldm)
		prop->mmu_pgt_size = 0x800000; /* 8MB */
	अन्यथा
		prop->mmu_pgt_size = MMU_PAGE_TABLES_SIZE;
	prop->mmu_pte_size = HL_PTE_SIZE;
	prop->mmu_hop_table_size = HOP_TABLE_SIZE;
	prop->mmu_hop0_tables_total_size = HOP0_TABLES_TOTAL_SIZE;
	prop->dram_page_size = PAGE_SIZE_2MB;
	prop->dram_supports_भव_memory = true;

	prop->dmmu.hop0_shअगरt = HOP0_SHIFT;
	prop->dmmu.hop1_shअगरt = HOP1_SHIFT;
	prop->dmmu.hop2_shअगरt = HOP2_SHIFT;
	prop->dmmu.hop3_shअगरt = HOP3_SHIFT;
	prop->dmmu.hop4_shअगरt = HOP4_SHIFT;
	prop->dmmu.hop0_mask = HOP0_MASK;
	prop->dmmu.hop1_mask = HOP1_MASK;
	prop->dmmu.hop2_mask = HOP2_MASK;
	prop->dmmu.hop3_mask = HOP3_MASK;
	prop->dmmu.hop4_mask = HOP4_MASK;
	prop->dmmu.start_addr = VA_DDR_SPACE_START;
	prop->dmmu.end_addr = VA_DDR_SPACE_END;
	prop->dmmu.page_size = PAGE_SIZE_2MB;
	prop->dmmu.num_hops = MMU_ARCH_5_HOPS;

	/* shअगरts and masks are the same in PMMU and DMMU */
	स_नकल(&prop->pmmu, &prop->dmmu, माप(prop->dmmu));
	prop->pmmu.start_addr = VA_HOST_SPACE_START;
	prop->pmmu.end_addr = VA_HOST_SPACE_END;
	prop->pmmu.page_size = PAGE_SIZE_4KB;
	prop->pmmu.num_hops = MMU_ARCH_5_HOPS;

	/* PMMU and HPMMU are the same except of page size */
	स_नकल(&prop->pmmu_huge, &prop->pmmu, माप(prop->pmmu));
	prop->pmmu_huge.page_size = PAGE_SIZE_2MB;

	prop->dram_size_क्रम_शेष_page_mapping = VA_DDR_SPACE_END;
	prop->cfg_size = CFG_SIZE;
	prop->max_asid = MAX_ASID;
	prop->num_of_events = GOYA_ASYNC_EVENT_ID_SIZE;
	prop->high_pll = PLL_HIGH_DEFAULT;
	prop->cb_pool_cb_cnt = GOYA_CB_POOL_CB_CNT;
	prop->cb_pool_cb_size = GOYA_CB_POOL_CB_SIZE;
	prop->max_घातer_शेष = MAX_POWER_DEFAULT;
	prop->dc_घातer_शेष = DC_POWER_DEFAULT;
	prop->tpc_enabled_mask = TPC_ENABLED_MASK;
	prop->pcie_dbi_base_address = mmPCIE_DBI_BASE;
	prop->pcie_aux_dbi_reg_addr = CFG_BASE + mmPCIE_AUX_DBI;

	म_नकलन(prop->cpucp_info.card_name, GOYA_DEFAULT_CARD_NAME,
		CARD_NAME_MAX_LEN);

	prop->max_pending_cs = GOYA_MAX_PENDING_CS;

	prop->first_available_user_msix_पूर्णांकerrupt = अच_लघु_उच्च;

	क्रम (i = 0 ; i < HL_MAX_DCORES ; i++)
		prop->first_available_cq[i] = अच_लघु_उच्च;

	prop->fw_security_status_valid = false;
	prop->hard_reset_करोne_by_fw = false;

	वापस 0;
पूर्ण

/*
 * goya_pci_bars_map - Map PCI BARS of Goya device
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Request PCI regions and map them to kernel भव addresses.
 * Returns 0 on success
 *
 */
अटल पूर्णांक goya_pci_bars_map(काष्ठा hl_device *hdev)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु"SRAM_CFG", "MSIX", "DDR"पूर्ण;
	bool is_wc[3] = अणुfalse, false, trueपूर्ण;
	पूर्णांक rc;

	rc = hl_pci_bars_map(hdev, name, is_wc);
	अगर (rc)
		वापस rc;

	hdev->rmmio = hdev->pcie_bar[SRAM_CFG_BAR_ID] +
			(CFG_BASE - SRAM_BASE_ADDR);

	वापस 0;
पूर्ण

अटल u64 goya_set_ddr_bar_base(काष्ठा hl_device *hdev, u64 addr)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	काष्ठा hl_inbound_pci_region pci_region;
	u64 old_addr = addr;
	पूर्णांक rc;

	अगर ((goya) && (goya->ddr_bar_cur_addr == addr))
		वापस old_addr;

	/* Inbound Region 1 - Bar 4 - Poपूर्णांक to DDR */
	pci_region.mode = PCI_BAR_MATCH_MODE;
	pci_region.bar = DDR_BAR_ID;
	pci_region.addr = addr;
	rc = hl_pci_set_inbound_region(hdev, 1, &pci_region);
	अगर (rc)
		वापस U64_MAX;

	अगर (goya) अणु
		old_addr = goya->ddr_bar_cur_addr;
		goya->ddr_bar_cur_addr = addr;
	पूर्ण

	वापस old_addr;
पूर्ण

/*
 * goya_init_iatu - Initialize the iATU unit inside the PCI controller
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * This is needed in हाल the firmware करोesn't initialize the iATU
 *
 */
अटल पूर्णांक goya_init_iatu(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_inbound_pci_region inbound_region;
	काष्ठा hl_outbound_pci_region outbound_region;
	पूर्णांक rc;

	अगर (hdev->asic_prop.iatu_करोne_by_fw) अणु
		hdev->asic_funcs->set_dma_mask_from_fw(hdev);
		वापस 0;
	पूर्ण

	/* Inbound Region 0 - Bar 0 - Poपूर्णांक to SRAM and CFG */
	inbound_region.mode = PCI_BAR_MATCH_MODE;
	inbound_region.bar = SRAM_CFG_BAR_ID;
	inbound_region.addr = SRAM_BASE_ADDR;
	rc = hl_pci_set_inbound_region(hdev, 0, &inbound_region);
	अगर (rc)
		जाओ करोne;

	/* Inbound Region 1 - Bar 4 - Poपूर्णांक to DDR */
	inbound_region.mode = PCI_BAR_MATCH_MODE;
	inbound_region.bar = DDR_BAR_ID;
	inbound_region.addr = DRAM_PHYS_BASE;
	rc = hl_pci_set_inbound_region(hdev, 1, &inbound_region);
	अगर (rc)
		जाओ करोne;

	hdev->asic_funcs->set_dma_mask_from_fw(hdev);

	/* Outbound Region 0 - Poपूर्णांक to Host  */
	outbound_region.addr = HOST_PHYS_BASE;
	outbound_region.size = HOST_PHYS_SIZE;
	rc = hl_pci_set_outbound_region(hdev, &outbound_region);

करोne:
	वापस rc;
पूर्ण

अटल क्रमागत hl_device_hw_state goya_get_hw_state(काष्ठा hl_device *hdev)
अणु
	वापस RREG32(mmHW_STATE);
पूर्ण

/*
 * goya_early_init - GOYA early initialization code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Verअगरy PCI bars
 * Set DMA masks
 * PCI controller initialization
 * Map PCI bars
 *
 */
अटल पूर्णांक goya_early_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा pci_dev *pdev = hdev->pdev;
	u32 fw_boot_status, val;
	पूर्णांक rc;

	rc = goya_get_fixed_properties(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to get fixed properties\n");
		वापस rc;
	पूर्ण

	/* Check BAR sizes */
	अगर (pci_resource_len(pdev, SRAM_CFG_BAR_ID) != CFG_BAR_SIZE) अणु
		dev_err(hdev->dev,
			"Not " HL_NAME "? BAR %d size %llu, expecting %llu\n",
			SRAM_CFG_BAR_ID,
			(अचिन्हित दीर्घ दीर्घ) pci_resource_len(pdev,
							SRAM_CFG_BAR_ID),
			CFG_BAR_SIZE);
		rc = -ENODEV;
		जाओ मुक्त_queue_props;
	पूर्ण

	अगर (pci_resource_len(pdev, MSIX_BAR_ID) != MSIX_BAR_SIZE) अणु
		dev_err(hdev->dev,
			"Not " HL_NAME "? BAR %d size %llu, expecting %llu\n",
			MSIX_BAR_ID,
			(अचिन्हित दीर्घ दीर्घ) pci_resource_len(pdev,
								MSIX_BAR_ID),
			MSIX_BAR_SIZE);
		rc = -ENODEV;
		जाओ मुक्त_queue_props;
	पूर्ण

	prop->dram_pci_bar_size = pci_resource_len(pdev, DDR_BAR_ID);

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
			GOYA_BOOT_FIT_REQ_TIMEOUT_USEC);
	अगर (rc) अणु
		अगर (hdev->reset_on_preboot_fail)
			hdev->asic_funcs->hw_fini(hdev, true);
		जाओ pci_fini;
	पूर्ण

	अगर (goya_get_hw_state(hdev) == HL_DEVICE_HW_STATE_सूचीTY) अणु
		dev_info(hdev->dev,
			"H/W state is dirty, must reset before initializing\n");
		hdev->asic_funcs->hw_fini(hdev, true);
	पूर्ण

	अगर (!hdev->pldm) अणु
		val = RREG32(mmPSOC_GLOBAL_CONF_BOOT_STRAP_PINS);
		अगर (val & PSOC_GLOBAL_CONF_BOOT_STRAP_PINS_SRIOV_EN_MASK)
			dev_warn(hdev->dev,
				"PCI strap is not configured correctly, PCI bus errors may occur\n");
	पूर्ण

	वापस 0;

pci_fini:
	hl_pci_fini(hdev);
मुक्त_queue_props:
	kमुक्त(hdev->asic_prop.hw_queues_props);
	वापस rc;
पूर्ण

/*
 * goya_early_fini - GOYA early finalization code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Unmap PCI bars
 *
 */
अटल पूर्णांक goya_early_fini(काष्ठा hl_device *hdev)
अणु
	kमुक्त(hdev->asic_prop.hw_queues_props);
	hl_pci_fini(hdev);

	वापस 0;
पूर्ण

अटल व्योम goya_mmu_prepare_reg(काष्ठा hl_device *hdev, u64 reg, u32 asid)
अणु
	/* mask to zero the MMBP and ASID bits */
	WREG32_AND(reg, ~0x7FF);
	WREG32_OR(reg, asid);
पूर्ण

अटल व्योम goya_qman0_set_security(काष्ठा hl_device *hdev, bool secure)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	अगर (secure)
		WREG32(mmDMA_QM_0_GLBL_PROT, QMAN_DMA_FULLY_TRUSTED);
	अन्यथा
		WREG32(mmDMA_QM_0_GLBL_PROT, QMAN_DMA_PARTLY_TRUSTED);

	RREG32(mmDMA_QM_0_GLBL_PROT);
पूर्ण

/*
 * goya_fetch_psoc_frequency - Fetch PSOC frequency values
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
अटल व्योम goya_fetch_psoc_frequency(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u32 nr = 0, nf = 0, od = 0, भाग_fctr = 0, pll_clk, भाग_sel;
	u16 pll_freq_arr[HL_PLL_NUM_OUTPUTS], freq;
	पूर्णांक rc;

	अगर (hdev->asic_prop.fw_security_disabled) अणु
		भाग_fctr = RREG32(mmPSOC_PCI_PLL_DIV_FACTOR_1);
		भाग_sel = RREG32(mmPSOC_PCI_PLL_DIV_SEL_1);
		nr = RREG32(mmPSOC_PCI_PLL_NR);
		nf = RREG32(mmPSOC_PCI_PLL_NF);
		od = RREG32(mmPSOC_PCI_PLL_OD);

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
		rc = hl_fw_cpucp_pll_info_get(hdev, HL_GOYA_PCI_PLL,
				pll_freq_arr);

		अगर (rc)
			वापस;

		freq = pll_freq_arr[1];
	पूर्ण

	prop->psoc_बारtamp_frequency = freq;
	prop->psoc_pci_pll_nr = nr;
	prop->psoc_pci_pll_nf = nf;
	prop->psoc_pci_pll_od = od;
	prop->psoc_pci_pll_भाग_factor = भाग_fctr;
पूर्ण

पूर्णांक goya_late_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक rc;

	goya_fetch_psoc_frequency(hdev);

	rc = goya_mmu_clear_pgt_range(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to clear MMU page tables range %d\n", rc);
		वापस rc;
	पूर्ण

	rc = goya_mmu_set_dram_शेष_page(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to set DRAM default page %d\n", rc);
		वापस rc;
	पूर्ण

	rc = goya_mmu_add_mappings_क्रम_device_cpu(hdev);
	अगर (rc)
		वापस rc;

	rc = goya_init_cpu_queues(hdev);
	अगर (rc)
		वापस rc;

	rc = goya_test_cpu_queue(hdev);
	अगर (rc)
		वापस rc;

	rc = goya_cpucp_info_get(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to get cpucp info %d\n", rc);
		वापस rc;
	पूर्ण

	/* Now that we have the DRAM size in ASIC prop, we need to check
	 * its size and configure the DMA_IF DDR wrap protection (which is in
	 * the MMU block) accordingly. The value is the log2 of the DRAM size
	 */
	WREG32(mmMMU_LOG2_DDR_SIZE, ilog2(prop->dram_size));

	rc = hl_fw_send_pci_access_msg(hdev, CPUCP_PACKET_ENABLE_PCI_ACCESS);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to enable PCI access from CPU %d\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * goya_late_fini - GOYA late tear-करोwn code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Free sensors allocated काष्ठाures
 */
व्योम goya_late_fini(काष्ठा hl_device *hdev)
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

/*
 * goya_sw_init - Goya software initialization code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
अटल पूर्णांक goya_sw_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya;
	पूर्णांक rc;

	/* Allocate device काष्ठाure */
	goya = kzalloc(माप(*goya), GFP_KERNEL);
	अगर (!goya)
		वापस -ENOMEM;

	/* according to goya_init_iatu */
	goya->ddr_bar_cur_addr = DRAM_PHYS_BASE;

	goya->mme_clk = GOYA_PLL_FREQ_LOW;
	goya->tpc_clk = GOYA_PLL_FREQ_LOW;
	goya->ic_clk = GOYA_PLL_FREQ_LOW;

	hdev->asic_specअगरic = goya;

	/* Create DMA pool क्रम small allocations */
	hdev->dma_pool = dma_pool_create(dev_name(hdev->dev),
			&hdev->pdev->dev, GOYA_DMA_POOL_BLK_SIZE, 8, 0);
	अगर (!hdev->dma_pool) अणु
		dev_err(hdev->dev, "failed to create DMA pool\n");
		rc = -ENOMEM;
		जाओ मुक्त_goya_device;
	पूर्ण

	hdev->cpu_accessible_dma_mem =
			hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
					HL_CPU_ACCESSIBLE_MEM_SIZE,
					&hdev->cpu_accessible_dma_address,
					GFP_KERNEL | __GFP_ZERO);

	अगर (!hdev->cpu_accessible_dma_mem) अणु
		rc = -ENOMEM;
		जाओ मुक्त_dma_pool;
	पूर्ण

	dev_dbg(hdev->dev, "cpu accessible memory at bus address %pad\n",
		&hdev->cpu_accessible_dma_address);

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

	spin_lock_init(&goya->hw_queues_lock);
	hdev->supports_coresight = true;
	hdev->supports_soft_reset = true;

	वापस 0;

मुक्त_cpu_accessible_dma_pool:
	gen_pool_destroy(hdev->cpu_accessible_dma_pool);
मुक्त_cpu_dma_mem:
	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
			HL_CPU_ACCESSIBLE_MEM_SIZE,
			hdev->cpu_accessible_dma_mem,
			hdev->cpu_accessible_dma_address);
मुक्त_dma_pool:
	dma_pool_destroy(hdev->dma_pool);
मुक्त_goya_device:
	kमुक्त(goya);

	वापस rc;
पूर्ण

/*
 * goya_sw_fini - Goya software tear-करोwn code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
अटल पूर्णांक goya_sw_fini(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	gen_pool_destroy(hdev->cpu_accessible_dma_pool);

	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
			HL_CPU_ACCESSIBLE_MEM_SIZE,
			hdev->cpu_accessible_dma_mem,
			hdev->cpu_accessible_dma_address);

	dma_pool_destroy(hdev->dma_pool);

	kमुक्त(goya);

	वापस 0;
पूर्ण

अटल व्योम goya_init_dma_qman(काष्ठा hl_device *hdev, पूर्णांक dma_id,
		dma_addr_t bus_address)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u32 reg_off = dma_id * (mmDMA_QM_1_PQ_PI - mmDMA_QM_0_PQ_PI);
	u32 dma_err_cfg = QMAN_DMA_ERR_MSG_EN;

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmDMA_QM_0_PQ_BASE_LO + reg_off, lower_32_bits(bus_address));
	WREG32(mmDMA_QM_0_PQ_BASE_HI + reg_off, upper_32_bits(bus_address));

	WREG32(mmDMA_QM_0_PQ_SIZE + reg_off, ilog2(HL_QUEUE_LENGTH));
	WREG32(mmDMA_QM_0_PQ_PI + reg_off, 0);
	WREG32(mmDMA_QM_0_PQ_CI + reg_off, 0);

	WREG32(mmDMA_QM_0_CP_MSG_BASE0_ADDR_LO + reg_off, mtr_base_lo);
	WREG32(mmDMA_QM_0_CP_MSG_BASE0_ADDR_HI + reg_off, mtr_base_hi);
	WREG32(mmDMA_QM_0_CP_MSG_BASE1_ADDR_LO + reg_off, so_base_lo);
	WREG32(mmDMA_QM_0_CP_MSG_BASE1_ADDR_HI + reg_off, so_base_hi);
	WREG32(mmDMA_QM_0_GLBL_ERR_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmDMA_QM_0_GLBL_ERR_ADDR_HI + reg_off, gic_base_hi);
	WREG32(mmDMA_QM_0_GLBL_ERR_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_DMA0_QM + dma_id);

	/* PQ has buffer of 2 cache lines, जबतक CQ has 8 lines */
	WREG32(mmDMA_QM_0_PQ_CFG1 + reg_off, 0x00020002);
	WREG32(mmDMA_QM_0_CQ_CFG1 + reg_off, 0x00080008);

	अगर (goya->hw_cap_initialized & HW_CAP_MMU)
		WREG32(mmDMA_QM_0_GLBL_PROT + reg_off, QMAN_DMA_PARTLY_TRUSTED);
	अन्यथा
		WREG32(mmDMA_QM_0_GLBL_PROT + reg_off, QMAN_DMA_FULLY_TRUSTED);

	अगर (hdev->stop_on_err)
		dma_err_cfg |= 1 << DMA_QM_0_GLBL_ERR_CFG_DMA_STOP_ON_ERR_SHIFT;

	WREG32(mmDMA_QM_0_GLBL_ERR_CFG + reg_off, dma_err_cfg);
	WREG32(mmDMA_QM_0_GLBL_CFG0 + reg_off, QMAN_DMA_ENABLE);
पूर्ण

अटल व्योम goya_init_dma_ch(काष्ठा hl_device *hdev, पूर्णांक dma_id)
अणु
	u32 gic_base_lo, gic_base_hi;
	u64 sob_addr;
	u32 reg_off = dma_id * (mmDMA_CH_1_CFG1 - mmDMA_CH_0_CFG1);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmDMA_CH_0_ERRMSG_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmDMA_CH_0_ERRMSG_ADDR_HI + reg_off, gic_base_hi);
	WREG32(mmDMA_CH_0_ERRMSG_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_DMA0_CH + dma_id);

	अगर (dma_id)
		sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1000 +
				(dma_id - 1) * 4;
	अन्यथा
		sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1007;

	WREG32(mmDMA_CH_0_WR_COMP_ADDR_HI + reg_off, upper_32_bits(sob_addr));
	WREG32(mmDMA_CH_0_WR_COMP_WDATA + reg_off, 0x80000001);
पूर्ण

/*
 * goya_init_dma_qmans - Initialize QMAN DMA रेजिस्टरs
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Initialize the H/W रेजिस्टरs of the QMAN DMA channels
 *
 */
व्योम goya_init_dma_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	काष्ठा hl_hw_queue *q;
	पूर्णांक i;

	अगर (goya->hw_cap_initialized & HW_CAP_DMA)
		वापस;

	q = &hdev->kernel_queues[0];

	क्रम (i = 0 ; i < NUMBER_OF_EXT_HW_QUEUES ; i++, q++) अणु
		q->cq_id = q->msi_vec = i;
		goya_init_dma_qman(hdev, i, q->bus_address);
		goya_init_dma_ch(hdev, i);
	पूर्ण

	goya->hw_cap_initialized |= HW_CAP_DMA;
पूर्ण

/*
 * goya_disable_बाह्यal_queues - Disable बाह्यal queues
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
अटल व्योम goya_disable_बाह्यal_queues(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_DMA))
		वापस;

	WREG32(mmDMA_QM_0_GLBL_CFG0, 0);
	WREG32(mmDMA_QM_1_GLBL_CFG0, 0);
	WREG32(mmDMA_QM_2_GLBL_CFG0, 0);
	WREG32(mmDMA_QM_3_GLBL_CFG0, 0);
	WREG32(mmDMA_QM_4_GLBL_CFG0, 0);
पूर्ण

अटल पूर्णांक goya_stop_queue(काष्ठा hl_device *hdev, u32 cfg_reg,
				u32 cp_sts_reg, u32 glbl_sts0_reg)
अणु
	पूर्णांक rc;
	u32 status;

	/* use the values of TPC0 as they are all the same*/

	WREG32(cfg_reg, 1 << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);

	status = RREG32(cp_sts_reg);
	अगर (status & TPC0_QM_CP_STS_FENCE_IN_PROGRESS_MASK) अणु
		rc = hl_poll_समयout(
			hdev,
			cp_sts_reg,
			status,
			!(status & TPC0_QM_CP_STS_FENCE_IN_PROGRESS_MASK),
			1000,
			QMAN_FENCE_TIMEOUT_USEC);

		/* अगर QMAN is stuck in fence no need to check क्रम stop */
		अगर (rc)
			वापस 0;
	पूर्ण

	rc = hl_poll_समयout(
		hdev,
		glbl_sts0_reg,
		status,
		(status & TPC0_QM_GLBL_STS0_CP_IS_STOP_MASK),
		1000,
		QMAN_STOP_TIMEOUT_USEC);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout while waiting for QMAN to stop\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * goya_stop_बाह्यal_queues - Stop बाह्यal queues
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Returns 0 on success
 *
 */
अटल पूर्णांक goya_stop_बाह्यal_queues(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc, retval = 0;

	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_DMA))
		वापस retval;

	rc = goya_stop_queue(hdev,
			mmDMA_QM_0_GLBL_CFG1,
			mmDMA_QM_0_CP_STS,
			mmDMA_QM_0_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop DMA QMAN 0\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmDMA_QM_1_GLBL_CFG1,
			mmDMA_QM_1_CP_STS,
			mmDMA_QM_1_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop DMA QMAN 1\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmDMA_QM_2_GLBL_CFG1,
			mmDMA_QM_2_CP_STS,
			mmDMA_QM_2_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop DMA QMAN 2\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmDMA_QM_3_GLBL_CFG1,
			mmDMA_QM_3_CP_STS,
			mmDMA_QM_3_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop DMA QMAN 3\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmDMA_QM_4_GLBL_CFG1,
			mmDMA_QM_4_CP_STS,
			mmDMA_QM_4_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop DMA QMAN 4\n");
		retval = -EIO;
	पूर्ण

	वापस retval;
पूर्ण

/*
 * goya_init_cpu_queues - Initialize PQ/CQ/EQ of CPU
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Returns 0 on success
 *
 */
पूर्णांक goya_init_cpu_queues(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_eq *eq;
	u32 status;
	काष्ठा hl_hw_queue *cpu_pq = &hdev->kernel_queues[GOYA_QUEUE_ID_CPU_PQ];
	पूर्णांक err;

	अगर (!hdev->cpu_queues_enable)
		वापस 0;

	अगर (goya->hw_cap_initialized & HW_CAP_CPU_Q)
		वापस 0;

	eq = &hdev->event_queue;

	WREG32(mmCPU_PQ_BASE_ADDR_LOW, lower_32_bits(cpu_pq->bus_address));
	WREG32(mmCPU_PQ_BASE_ADDR_HIGH, upper_32_bits(cpu_pq->bus_address));

	WREG32(mmCPU_EQ_BASE_ADDR_LOW, lower_32_bits(eq->bus_address));
	WREG32(mmCPU_EQ_BASE_ADDR_HIGH, upper_32_bits(eq->bus_address));

	WREG32(mmCPU_CQ_BASE_ADDR_LOW,
			lower_32_bits(VA_CPU_ACCESSIBLE_MEM_ADDR));
	WREG32(mmCPU_CQ_BASE_ADDR_HIGH,
			upper_32_bits(VA_CPU_ACCESSIBLE_MEM_ADDR));

	WREG32(mmCPU_PQ_LENGTH, HL_QUEUE_SIZE_IN_BYTES);
	WREG32(mmCPU_EQ_LENGTH, HL_EQ_SIZE_IN_BYTES);
	WREG32(mmCPU_CQ_LENGTH, HL_CPU_ACCESSIBLE_MEM_SIZE);

	/* Used क्रम EQ CI */
	WREG32(mmCPU_EQ_CI, 0);

	WREG32(mmCPU_IF_PF_PQ_PI, 0);

	WREG32(mmCPU_PQ_INIT_STATUS, PQ_INIT_STATUS_READY_FOR_CP);

	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
			GOYA_ASYNC_EVENT_ID_PI_UPDATE);

	err = hl_poll_समयout(
		hdev,
		mmCPU_PQ_INIT_STATUS,
		status,
		(status == PQ_INIT_STATUS_READY_FOR_HOST),
		1000,
		GOYA_CPU_TIMEOUT_USEC);

	अगर (err) अणु
		dev_err(hdev->dev,
			"Failed to setup communication with device CPU\n");
		वापस -EIO;
	पूर्ण

	/* update FW application security bits */
	अगर (prop->fw_security_status_valid)
		prop->fw_app_security_map = RREG32(mmCPU_BOOT_DEV_STS0);

	goya->hw_cap_initialized |= HW_CAP_CPU_Q;
	वापस 0;
पूर्ण

अटल व्योम goya_set_pll_refclk(काष्ठा hl_device *hdev)
अणु
	WREG32(mmCPU_PLL_DIV_SEL_0, 0x0);
	WREG32(mmCPU_PLL_DIV_SEL_1, 0x0);
	WREG32(mmCPU_PLL_DIV_SEL_2, 0x0);
	WREG32(mmCPU_PLL_DIV_SEL_3, 0x0);

	WREG32(mmIC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmIC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmIC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmIC_PLL_DIV_SEL_3, 0x0);

	WREG32(mmMC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmMC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmMC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmMC_PLL_DIV_SEL_3, 0x0);

	WREG32(mmPSOC_MME_PLL_DIV_SEL_0, 0x0);
	WREG32(mmPSOC_MME_PLL_DIV_SEL_1, 0x0);
	WREG32(mmPSOC_MME_PLL_DIV_SEL_2, 0x0);
	WREG32(mmPSOC_MME_PLL_DIV_SEL_3, 0x0);

	WREG32(mmPSOC_PCI_PLL_DIV_SEL_0, 0x0);
	WREG32(mmPSOC_PCI_PLL_DIV_SEL_1, 0x0);
	WREG32(mmPSOC_PCI_PLL_DIV_SEL_2, 0x0);
	WREG32(mmPSOC_PCI_PLL_DIV_SEL_3, 0x0);

	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_3, 0x0);

	WREG32(mmTPC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmTPC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmTPC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmTPC_PLL_DIV_SEL_3, 0x0);
पूर्ण

अटल व्योम goya_disable_clk_rlx(काष्ठा hl_device *hdev)
अणु
	WREG32(mmPSOC_MME_PLL_CLK_RLX_0, 0x100010);
	WREG32(mmIC_PLL_CLK_RLX_0, 0x100010);
पूर्ण

अटल व्योम _goya_tpc_mbist_workaround(काष्ठा hl_device *hdev, u8 tpc_id)
अणु
	u64 tpc_eml_address;
	u32 val, tpc_offset, tpc_eml_offset, tpc_slm_offset;
	पूर्णांक err, slm_index;

	tpc_offset = tpc_id * 0x40000;
	tpc_eml_offset = tpc_id * 0x200000;
	tpc_eml_address = (mmTPC0_EML_CFG_BASE + tpc_eml_offset - CFG_BASE);
	tpc_slm_offset = tpc_eml_address + 0x100000;

	/*
	 * Workaround क्रम Bug H2 #2443 :
	 * "TPC SB is not initialized on chip reset"
	 */

	val = RREG32(mmTPC0_CFG_FUNC_MBIST_CNTRL + tpc_offset);
	अगर (val & TPC0_CFG_FUNC_MBIST_CNTRL_MBIST_ACTIVE_MASK)
		dev_warn(hdev->dev, "TPC%d MBIST ACTIVE is not cleared\n",
			tpc_id);

	WREG32(mmTPC0_CFG_FUNC_MBIST_PAT + tpc_offset, val & 0xFFFFF000);

	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_0 + tpc_offset, 0x37FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_1 + tpc_offset, 0x303F);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_2 + tpc_offset, 0x71FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_3 + tpc_offset, 0x71FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_4 + tpc_offset, 0x70FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_5 + tpc_offset, 0x70FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_6 + tpc_offset, 0x70FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_7 + tpc_offset, 0x70FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_8 + tpc_offset, 0x70FF);
	WREG32(mmTPC0_CFG_FUNC_MBIST_MEM_9 + tpc_offset, 0x70FF);

	WREG32_OR(mmTPC0_CFG_FUNC_MBIST_CNTRL + tpc_offset,
		1 << TPC0_CFG_FUNC_MBIST_CNTRL_MBIST_START_SHIFT);

	err = hl_poll_समयout(
		hdev,
		mmTPC0_CFG_FUNC_MBIST_CNTRL + tpc_offset,
		val,
		(val & TPC0_CFG_FUNC_MBIST_CNTRL_MBIST_DONE_MASK),
		1000,
		HL_DEVICE_TIMEOUT_USEC);

	अगर (err)
		dev_err(hdev->dev,
			"Timeout while waiting for TPC%d MBIST DONE\n", tpc_id);

	WREG32_OR(mmTPC0_EML_CFG_DBG_CNT + tpc_eml_offset,
		1 << TPC0_EML_CFG_DBG_CNT_CORE_RST_SHIFT);

	msleep(GOYA_RESET_WAIT_MSEC);

	WREG32_AND(mmTPC0_EML_CFG_DBG_CNT + tpc_eml_offset,
		~(1 << TPC0_EML_CFG_DBG_CNT_CORE_RST_SHIFT));

	msleep(GOYA_RESET_WAIT_MSEC);

	क्रम (slm_index = 0 ; slm_index < 256 ; slm_index++)
		WREG32(tpc_slm_offset + (slm_index << 2), 0);

	val = RREG32(tpc_slm_offset);
पूर्ण

अटल व्योम goya_tpc_mbist_workaround(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक i;

	अगर (hdev->pldm)
		वापस;

	अगर (goya->hw_cap_initialized & HW_CAP_TPC_MBIST)
		वापस;

	/* Workaround क्रम H2 #2443 */

	क्रम (i = 0 ; i < TPC_MAX_NUM ; i++)
		_goya_tpc_mbist_workaround(hdev, i);

	goya->hw_cap_initialized |= HW_CAP_TPC_MBIST;
पूर्ण

/*
 * goya_init_golden_रेजिस्टरs - Initialize golden रेजिस्टरs
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Initialize the H/W रेजिस्टरs of the device
 *
 */
अटल व्योम goya_init_golden_रेजिस्टरs(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 polynom[10], tpc_पूर्णांकr_mask, offset;
	पूर्णांक i;

	अगर (goya->hw_cap_initialized & HW_CAP_GOLDEN)
		वापस;

	polynom[0] = 0x00020080;
	polynom[1] = 0x00401000;
	polynom[2] = 0x00200800;
	polynom[3] = 0x00002000;
	polynom[4] = 0x00080200;
	polynom[5] = 0x00040100;
	polynom[6] = 0x00100400;
	polynom[7] = 0x00004000;
	polynom[8] = 0x00010000;
	polynom[9] = 0x00008000;

	/* Mask all arithmetic पूर्णांकerrupts from TPC */
	tpc_पूर्णांकr_mask = 0x7FFF;

	क्रम (i = 0, offset = 0 ; i < 6 ; i++, offset += 0x20000) अणु
		WREG32(mmSRAM_Y0_X0_RTR_HBW_RD_RQ_L_ARB + offset, 0x302);
		WREG32(mmSRAM_Y0_X1_RTR_HBW_RD_RQ_L_ARB + offset, 0x302);
		WREG32(mmSRAM_Y0_X2_RTR_HBW_RD_RQ_L_ARB + offset, 0x302);
		WREG32(mmSRAM_Y0_X3_RTR_HBW_RD_RQ_L_ARB + offset, 0x302);
		WREG32(mmSRAM_Y0_X4_RTR_HBW_RD_RQ_L_ARB + offset, 0x302);

		WREG32(mmSRAM_Y0_X0_RTR_HBW_DATA_L_ARB + offset, 0x204);
		WREG32(mmSRAM_Y0_X1_RTR_HBW_DATA_L_ARB + offset, 0x204);
		WREG32(mmSRAM_Y0_X2_RTR_HBW_DATA_L_ARB + offset, 0x204);
		WREG32(mmSRAM_Y0_X3_RTR_HBW_DATA_L_ARB + offset, 0x204);
		WREG32(mmSRAM_Y0_X4_RTR_HBW_DATA_L_ARB + offset, 0x204);


		WREG32(mmSRAM_Y0_X0_RTR_HBW_DATA_E_ARB + offset, 0x206);
		WREG32(mmSRAM_Y0_X1_RTR_HBW_DATA_E_ARB + offset, 0x206);
		WREG32(mmSRAM_Y0_X2_RTR_HBW_DATA_E_ARB + offset, 0x206);
		WREG32(mmSRAM_Y0_X3_RTR_HBW_DATA_E_ARB + offset, 0x207);
		WREG32(mmSRAM_Y0_X4_RTR_HBW_DATA_E_ARB + offset, 0x207);

		WREG32(mmSRAM_Y0_X0_RTR_HBW_DATA_W_ARB + offset, 0x207);
		WREG32(mmSRAM_Y0_X1_RTR_HBW_DATA_W_ARB + offset, 0x207);
		WREG32(mmSRAM_Y0_X2_RTR_HBW_DATA_W_ARB + offset, 0x206);
		WREG32(mmSRAM_Y0_X3_RTR_HBW_DATA_W_ARB + offset, 0x206);
		WREG32(mmSRAM_Y0_X4_RTR_HBW_DATA_W_ARB + offset, 0x206);

		WREG32(mmSRAM_Y0_X0_RTR_HBW_WR_RS_E_ARB + offset, 0x101);
		WREG32(mmSRAM_Y0_X1_RTR_HBW_WR_RS_E_ARB + offset, 0x102);
		WREG32(mmSRAM_Y0_X2_RTR_HBW_WR_RS_E_ARB + offset, 0x103);
		WREG32(mmSRAM_Y0_X3_RTR_HBW_WR_RS_E_ARB + offset, 0x104);
		WREG32(mmSRAM_Y0_X4_RTR_HBW_WR_RS_E_ARB + offset, 0x105);

		WREG32(mmSRAM_Y0_X0_RTR_HBW_WR_RS_W_ARB + offset, 0x105);
		WREG32(mmSRAM_Y0_X1_RTR_HBW_WR_RS_W_ARB + offset, 0x104);
		WREG32(mmSRAM_Y0_X2_RTR_HBW_WR_RS_W_ARB + offset, 0x103);
		WREG32(mmSRAM_Y0_X3_RTR_HBW_WR_RS_W_ARB + offset, 0x102);
		WREG32(mmSRAM_Y0_X4_RTR_HBW_WR_RS_W_ARB + offset, 0x101);
	पूर्ण

	WREG32(mmMME_STORE_MAX_CREDIT, 0x21);
	WREG32(mmMME_AGU, 0x0f0f0f10);
	WREG32(mmMME_SEI_MASK, ~0x0);

	WREG32(mmMME6_RTR_HBW_RD_RQ_N_ARB, 0x01010101);
	WREG32(mmMME5_RTR_HBW_RD_RQ_N_ARB, 0x01040101);
	WREG32(mmMME4_RTR_HBW_RD_RQ_N_ARB, 0x01030101);
	WREG32(mmMME3_RTR_HBW_RD_RQ_N_ARB, 0x01020101);
	WREG32(mmMME2_RTR_HBW_RD_RQ_N_ARB, 0x01010101);
	WREG32(mmMME1_RTR_HBW_RD_RQ_N_ARB, 0x07010701);
	WREG32(mmMME6_RTR_HBW_RD_RQ_S_ARB, 0x04010401);
	WREG32(mmMME5_RTR_HBW_RD_RQ_S_ARB, 0x04050401);
	WREG32(mmMME4_RTR_HBW_RD_RQ_S_ARB, 0x03070301);
	WREG32(mmMME3_RTR_HBW_RD_RQ_S_ARB, 0x01030101);
	WREG32(mmMME2_RTR_HBW_RD_RQ_S_ARB, 0x01040101);
	WREG32(mmMME1_RTR_HBW_RD_RQ_S_ARB, 0x01050105);
	WREG32(mmMME6_RTR_HBW_RD_RQ_W_ARB, 0x01010501);
	WREG32(mmMME5_RTR_HBW_RD_RQ_W_ARB, 0x01010501);
	WREG32(mmMME4_RTR_HBW_RD_RQ_W_ARB, 0x01040301);
	WREG32(mmMME3_RTR_HBW_RD_RQ_W_ARB, 0x01030401);
	WREG32(mmMME2_RTR_HBW_RD_RQ_W_ARB, 0x01040101);
	WREG32(mmMME1_RTR_HBW_RD_RQ_W_ARB, 0x01050101);
	WREG32(mmMME6_RTR_HBW_WR_RQ_N_ARB, 0x02020202);
	WREG32(mmMME5_RTR_HBW_WR_RQ_N_ARB, 0x01070101);
	WREG32(mmMME4_RTR_HBW_WR_RQ_N_ARB, 0x02020201);
	WREG32(mmMME3_RTR_HBW_WR_RQ_N_ARB, 0x07020701);
	WREG32(mmMME2_RTR_HBW_WR_RQ_N_ARB, 0x01020101);
	WREG32(mmMME1_RTR_HBW_WR_RQ_S_ARB, 0x01010101);
	WREG32(mmMME6_RTR_HBW_WR_RQ_S_ARB, 0x01070101);
	WREG32(mmMME5_RTR_HBW_WR_RQ_S_ARB, 0x01070101);
	WREG32(mmMME4_RTR_HBW_WR_RQ_S_ARB, 0x07020701);
	WREG32(mmMME3_RTR_HBW_WR_RQ_S_ARB, 0x02020201);
	WREG32(mmMME2_RTR_HBW_WR_RQ_S_ARB, 0x01070101);
	WREG32(mmMME1_RTR_HBW_WR_RQ_S_ARB, 0x01020102);
	WREG32(mmMME6_RTR_HBW_WR_RQ_W_ARB, 0x01020701);
	WREG32(mmMME5_RTR_HBW_WR_RQ_W_ARB, 0x01020701);
	WREG32(mmMME4_RTR_HBW_WR_RQ_W_ARB, 0x07020707);
	WREG32(mmMME3_RTR_HBW_WR_RQ_W_ARB, 0x01020201);
	WREG32(mmMME2_RTR_HBW_WR_RQ_W_ARB, 0x01070201);
	WREG32(mmMME1_RTR_HBW_WR_RQ_W_ARB, 0x01070201);
	WREG32(mmMME6_RTR_HBW_RD_RS_N_ARB, 0x01070102);
	WREG32(mmMME5_RTR_HBW_RD_RS_N_ARB, 0x01070102);
	WREG32(mmMME4_RTR_HBW_RD_RS_N_ARB, 0x01060102);
	WREG32(mmMME3_RTR_HBW_RD_RS_N_ARB, 0x01040102);
	WREG32(mmMME2_RTR_HBW_RD_RS_N_ARB, 0x01020102);
	WREG32(mmMME1_RTR_HBW_RD_RS_N_ARB, 0x01020107);
	WREG32(mmMME6_RTR_HBW_RD_RS_S_ARB, 0x01020106);
	WREG32(mmMME5_RTR_HBW_RD_RS_S_ARB, 0x01020102);
	WREG32(mmMME4_RTR_HBW_RD_RS_S_ARB, 0x01040102);
	WREG32(mmMME3_RTR_HBW_RD_RS_S_ARB, 0x01060102);
	WREG32(mmMME2_RTR_HBW_RD_RS_S_ARB, 0x01070102);
	WREG32(mmMME1_RTR_HBW_RD_RS_S_ARB, 0x01070102);
	WREG32(mmMME6_RTR_HBW_RD_RS_E_ARB, 0x01020702);
	WREG32(mmMME5_RTR_HBW_RD_RS_E_ARB, 0x01020702);
	WREG32(mmMME4_RTR_HBW_RD_RS_E_ARB, 0x01040602);
	WREG32(mmMME3_RTR_HBW_RD_RS_E_ARB, 0x01060402);
	WREG32(mmMME2_RTR_HBW_RD_RS_E_ARB, 0x01070202);
	WREG32(mmMME1_RTR_HBW_RD_RS_E_ARB, 0x01070102);
	WREG32(mmMME6_RTR_HBW_RD_RS_W_ARB, 0x01060401);
	WREG32(mmMME5_RTR_HBW_RD_RS_W_ARB, 0x01060401);
	WREG32(mmMME4_RTR_HBW_RD_RS_W_ARB, 0x01060401);
	WREG32(mmMME3_RTR_HBW_RD_RS_W_ARB, 0x01060401);
	WREG32(mmMME2_RTR_HBW_RD_RS_W_ARB, 0x01060401);
	WREG32(mmMME1_RTR_HBW_RD_RS_W_ARB, 0x01060401);
	WREG32(mmMME6_RTR_HBW_WR_RS_N_ARB, 0x01050101);
	WREG32(mmMME5_RTR_HBW_WR_RS_N_ARB, 0x01040101);
	WREG32(mmMME4_RTR_HBW_WR_RS_N_ARB, 0x01030101);
	WREG32(mmMME3_RTR_HBW_WR_RS_N_ARB, 0x01020101);
	WREG32(mmMME2_RTR_HBW_WR_RS_N_ARB, 0x01010101);
	WREG32(mmMME1_RTR_HBW_WR_RS_N_ARB, 0x01010107);
	WREG32(mmMME6_RTR_HBW_WR_RS_S_ARB, 0x01010107);
	WREG32(mmMME5_RTR_HBW_WR_RS_S_ARB, 0x01010101);
	WREG32(mmMME4_RTR_HBW_WR_RS_S_ARB, 0x01020101);
	WREG32(mmMME3_RTR_HBW_WR_RS_S_ARB, 0x01030101);
	WREG32(mmMME2_RTR_HBW_WR_RS_S_ARB, 0x01040101);
	WREG32(mmMME1_RTR_HBW_WR_RS_S_ARB, 0x01050101);
	WREG32(mmMME6_RTR_HBW_WR_RS_E_ARB, 0x01010501);
	WREG32(mmMME5_RTR_HBW_WR_RS_E_ARB, 0x01010501);
	WREG32(mmMME4_RTR_HBW_WR_RS_E_ARB, 0x01040301);
	WREG32(mmMME3_RTR_HBW_WR_RS_E_ARB, 0x01030401);
	WREG32(mmMME2_RTR_HBW_WR_RS_E_ARB, 0x01040101);
	WREG32(mmMME1_RTR_HBW_WR_RS_E_ARB, 0x01050101);
	WREG32(mmMME6_RTR_HBW_WR_RS_W_ARB, 0x01010101);
	WREG32(mmMME5_RTR_HBW_WR_RS_W_ARB, 0x01010101);
	WREG32(mmMME4_RTR_HBW_WR_RS_W_ARB, 0x01010101);
	WREG32(mmMME3_RTR_HBW_WR_RS_W_ARB, 0x01010101);
	WREG32(mmMME2_RTR_HBW_WR_RS_W_ARB, 0x01010101);
	WREG32(mmMME1_RTR_HBW_WR_RS_W_ARB, 0x01010101);

	WREG32(mmTPC1_RTR_HBW_RD_RQ_N_ARB, 0x01010101);
	WREG32(mmTPC1_RTR_HBW_RD_RQ_S_ARB, 0x01010101);
	WREG32(mmTPC1_RTR_HBW_RD_RQ_E_ARB, 0x01060101);
	WREG32(mmTPC1_RTR_HBW_WR_RQ_N_ARB, 0x02020102);
	WREG32(mmTPC1_RTR_HBW_WR_RQ_S_ARB, 0x01010101);
	WREG32(mmTPC1_RTR_HBW_WR_RQ_E_ARB, 0x02070202);
	WREG32(mmTPC1_RTR_HBW_RD_RS_N_ARB, 0x01020201);
	WREG32(mmTPC1_RTR_HBW_RD_RS_S_ARB, 0x01070201);
	WREG32(mmTPC1_RTR_HBW_RD_RS_W_ARB, 0x01070202);
	WREG32(mmTPC1_RTR_HBW_WR_RS_N_ARB, 0x01010101);
	WREG32(mmTPC1_RTR_HBW_WR_RS_S_ARB, 0x01050101);
	WREG32(mmTPC1_RTR_HBW_WR_RS_W_ARB, 0x01050101);

	WREG32(mmTPC2_RTR_HBW_RD_RQ_N_ARB, 0x01020101);
	WREG32(mmTPC2_RTR_HBW_RD_RQ_S_ARB, 0x01050101);
	WREG32(mmTPC2_RTR_HBW_RD_RQ_E_ARB, 0x01010201);
	WREG32(mmTPC2_RTR_HBW_WR_RQ_N_ARB, 0x02040102);
	WREG32(mmTPC2_RTR_HBW_WR_RQ_S_ARB, 0x01050101);
	WREG32(mmTPC2_RTR_HBW_WR_RQ_E_ARB, 0x02060202);
	WREG32(mmTPC2_RTR_HBW_RD_RS_N_ARB, 0x01020201);
	WREG32(mmTPC2_RTR_HBW_RD_RS_S_ARB, 0x01070201);
	WREG32(mmTPC2_RTR_HBW_RD_RS_W_ARB, 0x01070202);
	WREG32(mmTPC2_RTR_HBW_WR_RS_N_ARB, 0x01010101);
	WREG32(mmTPC2_RTR_HBW_WR_RS_S_ARB, 0x01040101);
	WREG32(mmTPC2_RTR_HBW_WR_RS_W_ARB, 0x01040101);

	WREG32(mmTPC3_RTR_HBW_RD_RQ_N_ARB, 0x01030101);
	WREG32(mmTPC3_RTR_HBW_RD_RQ_S_ARB, 0x01040101);
	WREG32(mmTPC3_RTR_HBW_RD_RQ_E_ARB, 0x01040301);
	WREG32(mmTPC3_RTR_HBW_WR_RQ_N_ARB, 0x02060102);
	WREG32(mmTPC3_RTR_HBW_WR_RQ_S_ARB, 0x01040101);
	WREG32(mmTPC3_RTR_HBW_WR_RQ_E_ARB, 0x01040301);
	WREG32(mmTPC3_RTR_HBW_RD_RS_N_ARB, 0x01040201);
	WREG32(mmTPC3_RTR_HBW_RD_RS_S_ARB, 0x01060201);
	WREG32(mmTPC3_RTR_HBW_RD_RS_W_ARB, 0x01060402);
	WREG32(mmTPC3_RTR_HBW_WR_RS_N_ARB, 0x01020101);
	WREG32(mmTPC3_RTR_HBW_WR_RS_S_ARB, 0x01030101);
	WREG32(mmTPC3_RTR_HBW_WR_RS_W_ARB, 0x01030401);

	WREG32(mmTPC4_RTR_HBW_RD_RQ_N_ARB, 0x01040101);
	WREG32(mmTPC4_RTR_HBW_RD_RQ_S_ARB, 0x01030101);
	WREG32(mmTPC4_RTR_HBW_RD_RQ_E_ARB, 0x01030401);
	WREG32(mmTPC4_RTR_HBW_WR_RQ_N_ARB, 0x02070102);
	WREG32(mmTPC4_RTR_HBW_WR_RQ_S_ARB, 0x01030101);
	WREG32(mmTPC4_RTR_HBW_WR_RQ_E_ARB, 0x02060702);
	WREG32(mmTPC4_RTR_HBW_RD_RS_N_ARB, 0x01060201);
	WREG32(mmTPC4_RTR_HBW_RD_RS_S_ARB, 0x01040201);
	WREG32(mmTPC4_RTR_HBW_RD_RS_W_ARB, 0x01040602);
	WREG32(mmTPC4_RTR_HBW_WR_RS_N_ARB, 0x01030101);
	WREG32(mmTPC4_RTR_HBW_WR_RS_S_ARB, 0x01020101);
	WREG32(mmTPC4_RTR_HBW_WR_RS_W_ARB, 0x01040301);

	WREG32(mmTPC5_RTR_HBW_RD_RQ_N_ARB, 0x01050101);
	WREG32(mmTPC5_RTR_HBW_RD_RQ_S_ARB, 0x01020101);
	WREG32(mmTPC5_RTR_HBW_RD_RQ_E_ARB, 0x01200501);
	WREG32(mmTPC5_RTR_HBW_WR_RQ_N_ARB, 0x02070102);
	WREG32(mmTPC5_RTR_HBW_WR_RQ_S_ARB, 0x01020101);
	WREG32(mmTPC5_RTR_HBW_WR_RQ_E_ARB, 0x02020602);
	WREG32(mmTPC5_RTR_HBW_RD_RS_N_ARB, 0x01070201);
	WREG32(mmTPC5_RTR_HBW_RD_RS_S_ARB, 0x01020201);
	WREG32(mmTPC5_RTR_HBW_RD_RS_W_ARB, 0x01020702);
	WREG32(mmTPC5_RTR_HBW_WR_RS_N_ARB, 0x01040101);
	WREG32(mmTPC5_RTR_HBW_WR_RS_S_ARB, 0x01010101);
	WREG32(mmTPC5_RTR_HBW_WR_RS_W_ARB, 0x01010501);

	WREG32(mmTPC6_RTR_HBW_RD_RQ_N_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_RD_RQ_S_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_RD_RQ_E_ARB, 0x01010601);
	WREG32(mmTPC6_RTR_HBW_WR_RQ_N_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_WR_RQ_S_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_WR_RQ_E_ARB, 0x02020702);
	WREG32(mmTPC6_RTR_HBW_RD_RS_N_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_RD_RS_S_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_RD_RS_W_ARB, 0x01020702);
	WREG32(mmTPC6_RTR_HBW_WR_RS_N_ARB, 0x01050101);
	WREG32(mmTPC6_RTR_HBW_WR_RS_S_ARB, 0x01010101);
	WREG32(mmTPC6_RTR_HBW_WR_RS_W_ARB, 0x01010501);

	क्रम (i = 0, offset = 0 ; i < 10 ; i++, offset += 4) अणु
		WREG32(mmMME1_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmMME2_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmMME3_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmMME4_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmMME5_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmMME6_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);

		WREG32(mmTPC0_NRTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC1_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC2_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC3_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC4_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC5_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC6_RTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmTPC7_NRTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);

		WREG32(mmPCI_NRTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
		WREG32(mmDMA_NRTR_SPLIT_COEF_0 + offset, polynom[i] >> 7);
	पूर्ण

	क्रम (i = 0, offset = 0 ; i < 6 ; i++, offset += 0x40000) अणु
		WREG32(mmMME1_RTR_SCRAMB_EN + offset,
				1 << MME1_RTR_SCRAMB_EN_VAL_SHIFT);
		WREG32(mmMME1_RTR_NON_LIN_SCRAMB + offset,
				1 << MME1_RTR_NON_LIN_SCRAMB_EN_SHIFT);
	पूर्ण

	क्रम (i = 0, offset = 0 ; i < 8 ; i++, offset += 0x40000) अणु
		/*
		 * Workaround क्रम Bug H2 #2441 :
		 * "ST.NOP set trace event illegal opcode"
		 */
		WREG32(mmTPC0_CFG_TPC_INTR_MASK + offset, tpc_पूर्णांकr_mask);

		WREG32(mmTPC0_NRTR_SCRAMB_EN + offset,
				1 << TPC0_NRTR_SCRAMB_EN_VAL_SHIFT);
		WREG32(mmTPC0_NRTR_NON_LIN_SCRAMB + offset,
				1 << TPC0_NRTR_NON_LIN_SCRAMB_EN_SHIFT);

		WREG32_FIELD(TPC0_CFG_MSS_CONFIG, offset,
				ICACHE_FETCH_LINE_NUM, 2);
	पूर्ण

	WREG32(mmDMA_NRTR_SCRAMB_EN, 1 << DMA_NRTR_SCRAMB_EN_VAL_SHIFT);
	WREG32(mmDMA_NRTR_NON_LIN_SCRAMB,
			1 << DMA_NRTR_NON_LIN_SCRAMB_EN_SHIFT);

	WREG32(mmPCI_NRTR_SCRAMB_EN, 1 << PCI_NRTR_SCRAMB_EN_VAL_SHIFT);
	WREG32(mmPCI_NRTR_NON_LIN_SCRAMB,
			1 << PCI_NRTR_NON_LIN_SCRAMB_EN_SHIFT);

	/*
	 * Workaround क्रम H2 #HW-23 bug
	 * Set DMA max outstanding पढ़ो requests to 240 on DMA CH 1.
	 * This limitation is still large enough to not affect Gen4 bandwidth.
	 * We need to only limit that DMA channel because the user can only पढ़ो
	 * from Host using DMA CH 1
	 */
	WREG32(mmDMA_CH_1_CFG0, 0x0fff00F0);

	WREG32(mmTPC_PLL_CLK_RLX_0, 0x200020);

	goya->hw_cap_initialized |= HW_CAP_GOLDEN;
पूर्ण

अटल व्योम goya_init_mme_qman(काष्ठा hl_device *hdev)
अणु
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u64 qman_base_addr;

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	qman_base_addr = hdev->asic_prop.sram_base_address +
				MME_QMAN_BASE_OFFSET;

	WREG32(mmMME_QM_PQ_BASE_LO, lower_32_bits(qman_base_addr));
	WREG32(mmMME_QM_PQ_BASE_HI, upper_32_bits(qman_base_addr));
	WREG32(mmMME_QM_PQ_SIZE, ilog2(MME_QMAN_LENGTH));
	WREG32(mmMME_QM_PQ_PI, 0);
	WREG32(mmMME_QM_PQ_CI, 0);
	WREG32(mmMME_QM_CP_LDMA_SRC_BASE_LO_OFFSET, 0x10C0);
	WREG32(mmMME_QM_CP_LDMA_SRC_BASE_HI_OFFSET, 0x10C4);
	WREG32(mmMME_QM_CP_LDMA_TSIZE_OFFSET, 0x10C8);
	WREG32(mmMME_QM_CP_LDMA_COMMIT_OFFSET, 0x10CC);

	WREG32(mmMME_QM_CP_MSG_BASE0_ADDR_LO, mtr_base_lo);
	WREG32(mmMME_QM_CP_MSG_BASE0_ADDR_HI, mtr_base_hi);
	WREG32(mmMME_QM_CP_MSG_BASE1_ADDR_LO, so_base_lo);
	WREG32(mmMME_QM_CP_MSG_BASE1_ADDR_HI, so_base_hi);

	/* QMAN CQ has 8 cache lines */
	WREG32(mmMME_QM_CQ_CFG1, 0x00080008);

	WREG32(mmMME_QM_GLBL_ERR_ADDR_LO, gic_base_lo);
	WREG32(mmMME_QM_GLBL_ERR_ADDR_HI, gic_base_hi);

	WREG32(mmMME_QM_GLBL_ERR_WDATA, GOYA_ASYNC_EVENT_ID_MME_QM);

	WREG32(mmMME_QM_GLBL_ERR_CFG, QMAN_MME_ERR_MSG_EN);

	WREG32(mmMME_QM_GLBL_PROT, QMAN_MME_ERR_PROT);

	WREG32(mmMME_QM_GLBL_CFG0, QMAN_MME_ENABLE);
पूर्ण

अटल व्योम goya_init_mme_cmdq(काष्ठा hl_device *hdev)
अणु
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmMME_CMDQ_CP_MSG_BASE0_ADDR_LO, mtr_base_lo);
	WREG32(mmMME_CMDQ_CP_MSG_BASE0_ADDR_HI, mtr_base_hi);
	WREG32(mmMME_CMDQ_CP_MSG_BASE1_ADDR_LO,	so_base_lo);
	WREG32(mmMME_CMDQ_CP_MSG_BASE1_ADDR_HI, so_base_hi);

	/* CMDQ CQ has 20 cache lines */
	WREG32(mmMME_CMDQ_CQ_CFG1, 0x00140014);

	WREG32(mmMME_CMDQ_GLBL_ERR_ADDR_LO, gic_base_lo);
	WREG32(mmMME_CMDQ_GLBL_ERR_ADDR_HI, gic_base_hi);

	WREG32(mmMME_CMDQ_GLBL_ERR_WDATA, GOYA_ASYNC_EVENT_ID_MME_CMDQ);

	WREG32(mmMME_CMDQ_GLBL_ERR_CFG, CMDQ_MME_ERR_MSG_EN);

	WREG32(mmMME_CMDQ_GLBL_PROT, CMDQ_MME_ERR_PROT);

	WREG32(mmMME_CMDQ_GLBL_CFG0, CMDQ_MME_ENABLE);
पूर्ण

व्योम goya_init_mme_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 so_base_lo, so_base_hi;

	अगर (goya->hw_cap_initialized & HW_CAP_MME)
		वापस;

	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	WREG32(mmMME_SM_BASE_ADDRESS_LOW, so_base_lo);
	WREG32(mmMME_SM_BASE_ADDRESS_HIGH, so_base_hi);

	goya_init_mme_qman(hdev);
	goya_init_mme_cmdq(hdev);

	goya->hw_cap_initialized |= HW_CAP_MME;
पूर्ण

अटल व्योम goya_init_tpc_qman(काष्ठा hl_device *hdev, u32 base_off, पूर्णांक tpc_id)
अणु
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u64 qman_base_addr;
	u32 reg_off = tpc_id * (mmTPC1_QM_PQ_PI - mmTPC0_QM_PQ_PI);

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	qman_base_addr = hdev->asic_prop.sram_base_address + base_off;

	WREG32(mmTPC0_QM_PQ_BASE_LO + reg_off, lower_32_bits(qman_base_addr));
	WREG32(mmTPC0_QM_PQ_BASE_HI + reg_off, upper_32_bits(qman_base_addr));
	WREG32(mmTPC0_QM_PQ_SIZE + reg_off, ilog2(TPC_QMAN_LENGTH));
	WREG32(mmTPC0_QM_PQ_PI + reg_off, 0);
	WREG32(mmTPC0_QM_PQ_CI + reg_off, 0);
	WREG32(mmTPC0_QM_CP_LDMA_SRC_BASE_LO_OFFSET + reg_off, 0x10C0);
	WREG32(mmTPC0_QM_CP_LDMA_SRC_BASE_HI_OFFSET + reg_off, 0x10C4);
	WREG32(mmTPC0_QM_CP_LDMA_TSIZE_OFFSET + reg_off, 0x10C8);
	WREG32(mmTPC0_QM_CP_LDMA_COMMIT_OFFSET + reg_off, 0x10CC);

	WREG32(mmTPC0_QM_CP_MSG_BASE0_ADDR_LO + reg_off, mtr_base_lo);
	WREG32(mmTPC0_QM_CP_MSG_BASE0_ADDR_HI + reg_off, mtr_base_hi);
	WREG32(mmTPC0_QM_CP_MSG_BASE1_ADDR_LO + reg_off, so_base_lo);
	WREG32(mmTPC0_QM_CP_MSG_BASE1_ADDR_HI + reg_off, so_base_hi);

	WREG32(mmTPC0_QM_CQ_CFG1 + reg_off, 0x00080008);

	WREG32(mmTPC0_QM_GLBL_ERR_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmTPC0_QM_GLBL_ERR_ADDR_HI + reg_off, gic_base_hi);

	WREG32(mmTPC0_QM_GLBL_ERR_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_TPC0_QM + tpc_id);

	WREG32(mmTPC0_QM_GLBL_ERR_CFG + reg_off, QMAN_TPC_ERR_MSG_EN);

	WREG32(mmTPC0_QM_GLBL_PROT + reg_off, QMAN_TPC_ERR_PROT);

	WREG32(mmTPC0_QM_GLBL_CFG0 + reg_off, QMAN_TPC_ENABLE);
पूर्ण

अटल व्योम goya_init_tpc_cmdq(काष्ठा hl_device *hdev, पूर्णांक tpc_id)
अणु
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u32 reg_off = tpc_id * (mmTPC1_CMDQ_CQ_CFG1 - mmTPC0_CMDQ_CQ_CFG1);

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmTPC0_CMDQ_CP_MSG_BASE0_ADDR_LO + reg_off, mtr_base_lo);
	WREG32(mmTPC0_CMDQ_CP_MSG_BASE0_ADDR_HI + reg_off, mtr_base_hi);
	WREG32(mmTPC0_CMDQ_CP_MSG_BASE1_ADDR_LO + reg_off, so_base_lo);
	WREG32(mmTPC0_CMDQ_CP_MSG_BASE1_ADDR_HI + reg_off, so_base_hi);

	WREG32(mmTPC0_CMDQ_CQ_CFG1 + reg_off, 0x00140014);

	WREG32(mmTPC0_CMDQ_GLBL_ERR_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmTPC0_CMDQ_GLBL_ERR_ADDR_HI + reg_off, gic_base_hi);

	WREG32(mmTPC0_CMDQ_GLBL_ERR_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_TPC0_CMDQ + tpc_id);

	WREG32(mmTPC0_CMDQ_GLBL_ERR_CFG + reg_off, CMDQ_TPC_ERR_MSG_EN);

	WREG32(mmTPC0_CMDQ_GLBL_PROT + reg_off, CMDQ_TPC_ERR_PROT);

	WREG32(mmTPC0_CMDQ_GLBL_CFG0 + reg_off, CMDQ_TPC_ENABLE);
पूर्ण

व्योम goya_init_tpc_qmans(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 so_base_lo, so_base_hi;
	u32 cfg_off = mmTPC1_CFG_SM_BASE_ADDRESS_LOW -
			mmTPC0_CFG_SM_BASE_ADDRESS_LOW;
	पूर्णांक i;

	अगर (goya->hw_cap_initialized & HW_CAP_TPC)
		वापस;

	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	क्रम (i = 0 ; i < TPC_MAX_NUM ; i++) अणु
		WREG32(mmTPC0_CFG_SM_BASE_ADDRESS_LOW + i * cfg_off,
				so_base_lo);
		WREG32(mmTPC0_CFG_SM_BASE_ADDRESS_HIGH + i * cfg_off,
				so_base_hi);
	पूर्ण

	goya_init_tpc_qman(hdev, TPC0_QMAN_BASE_OFFSET, 0);
	goya_init_tpc_qman(hdev, TPC1_QMAN_BASE_OFFSET, 1);
	goya_init_tpc_qman(hdev, TPC2_QMAN_BASE_OFFSET, 2);
	goya_init_tpc_qman(hdev, TPC3_QMAN_BASE_OFFSET, 3);
	goya_init_tpc_qman(hdev, TPC4_QMAN_BASE_OFFSET, 4);
	goya_init_tpc_qman(hdev, TPC5_QMAN_BASE_OFFSET, 5);
	goya_init_tpc_qman(hdev, TPC6_QMAN_BASE_OFFSET, 6);
	goya_init_tpc_qman(hdev, TPC7_QMAN_BASE_OFFSET, 7);

	क्रम (i = 0 ; i < TPC_MAX_NUM ; i++)
		goya_init_tpc_cmdq(hdev, i);

	goya->hw_cap_initialized |= HW_CAP_TPC;
पूर्ण

/*
 * goya_disable_पूर्णांकernal_queues - Disable पूर्णांकernal queues
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
अटल व्योम goya_disable_पूर्णांकernal_queues(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MME))
		जाओ disable_tpc;

	WREG32(mmMME_QM_GLBL_CFG0, 0);
	WREG32(mmMME_CMDQ_GLBL_CFG0, 0);

disable_tpc:
	अगर (!(goya->hw_cap_initialized & HW_CAP_TPC))
		वापस;

	WREG32(mmTPC0_QM_GLBL_CFG0, 0);
	WREG32(mmTPC0_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC1_QM_GLBL_CFG0, 0);
	WREG32(mmTPC1_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC2_QM_GLBL_CFG0, 0);
	WREG32(mmTPC2_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC3_QM_GLBL_CFG0, 0);
	WREG32(mmTPC3_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC4_QM_GLBL_CFG0, 0);
	WREG32(mmTPC4_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC5_QM_GLBL_CFG0, 0);
	WREG32(mmTPC5_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC6_QM_GLBL_CFG0, 0);
	WREG32(mmTPC6_CMDQ_GLBL_CFG0, 0);

	WREG32(mmTPC7_QM_GLBL_CFG0, 0);
	WREG32(mmTPC7_CMDQ_GLBL_CFG0, 0);
पूर्ण

/*
 * goya_stop_पूर्णांकernal_queues - Stop पूर्णांकernal queues
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Returns 0 on success
 *
 */
अटल पूर्णांक goya_stop_पूर्णांकernal_queues(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक rc, retval = 0;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MME))
		जाओ stop_tpc;

	/*
	 * Each queue (QMAN) is a separate H/W logic. That means that each
	 * QMAN can be stopped independently and failure to stop one करोes NOT
	 * mandate we should not try to stop other QMANs
	 */

	rc = goya_stop_queue(hdev,
			mmMME_QM_GLBL_CFG1,
			mmMME_QM_CP_STS,
			mmMME_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop MME QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmMME_CMDQ_GLBL_CFG1,
			mmMME_CMDQ_CP_STS,
			mmMME_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop MME CMDQ\n");
		retval = -EIO;
	पूर्ण

stop_tpc:
	अगर (!(goya->hw_cap_initialized & HW_CAP_TPC))
		वापस retval;

	rc = goya_stop_queue(hdev,
			mmTPC0_QM_GLBL_CFG1,
			mmTPC0_QM_CP_STS,
			mmTPC0_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 0 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC0_CMDQ_GLBL_CFG1,
			mmTPC0_CMDQ_CP_STS,
			mmTPC0_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 0 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC1_QM_GLBL_CFG1,
			mmTPC1_QM_CP_STS,
			mmTPC1_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 1 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC1_CMDQ_GLBL_CFG1,
			mmTPC1_CMDQ_CP_STS,
			mmTPC1_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 1 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC2_QM_GLBL_CFG1,
			mmTPC2_QM_CP_STS,
			mmTPC2_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 2 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC2_CMDQ_GLBL_CFG1,
			mmTPC2_CMDQ_CP_STS,
			mmTPC2_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 2 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC3_QM_GLBL_CFG1,
			mmTPC3_QM_CP_STS,
			mmTPC3_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 3 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC3_CMDQ_GLBL_CFG1,
			mmTPC3_CMDQ_CP_STS,
			mmTPC3_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 3 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC4_QM_GLBL_CFG1,
			mmTPC4_QM_CP_STS,
			mmTPC4_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 4 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC4_CMDQ_GLBL_CFG1,
			mmTPC4_CMDQ_CP_STS,
			mmTPC4_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 4 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC5_QM_GLBL_CFG1,
			mmTPC5_QM_CP_STS,
			mmTPC5_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 5 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC5_CMDQ_GLBL_CFG1,
			mmTPC5_CMDQ_CP_STS,
			mmTPC5_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 5 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC6_QM_GLBL_CFG1,
			mmTPC6_QM_CP_STS,
			mmTPC6_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 6 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC6_CMDQ_GLBL_CFG1,
			mmTPC6_CMDQ_CP_STS,
			mmTPC6_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 6 CMDQ\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC7_QM_GLBL_CFG1,
			mmTPC7_QM_CP_STS,
			mmTPC7_QM_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 7 QMAN\n");
		retval = -EIO;
	पूर्ण

	rc = goya_stop_queue(hdev,
			mmTPC7_CMDQ_GLBL_CFG1,
			mmTPC7_CMDQ_CP_STS,
			mmTPC7_CMDQ_GLBL_STS0);

	अगर (rc) अणु
		dev_err(hdev->dev, "failed to stop TPC 7 CMDQ\n");
		retval = -EIO;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम goya_dma_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_DMA))
		वापस;

	WREG32(mmDMA_QM_0_GLBL_CFG1, 1 << DMA_QM_0_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_1_GLBL_CFG1, 1 << DMA_QM_1_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_2_GLBL_CFG1, 1 << DMA_QM_2_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_3_GLBL_CFG1, 1 << DMA_QM_3_GLBL_CFG1_DMA_STOP_SHIFT);
	WREG32(mmDMA_QM_4_GLBL_CFG1, 1 << DMA_QM_4_GLBL_CFG1_DMA_STOP_SHIFT);
पूर्ण

अटल व्योम goya_tpc_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_TPC))
		वापस;

	WREG32(mmTPC0_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC1_CFG_TPC_STALL, 1 << TPC1_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC2_CFG_TPC_STALL, 1 << TPC2_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC3_CFG_TPC_STALL, 1 << TPC3_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC4_CFG_TPC_STALL, 1 << TPC4_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC5_CFG_TPC_STALL, 1 << TPC5_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC6_CFG_TPC_STALL, 1 << TPC6_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC7_CFG_TPC_STALL, 1 << TPC7_CFG_TPC_STALL_V_SHIFT);
पूर्ण

अटल व्योम goya_mme_stall(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MME))
		वापस;

	WREG32(mmMME_STALL, 0xFFFFFFFF);
पूर्ण

अटल पूर्णांक goya_enable_msix(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक cq_cnt = hdev->asic_prop.completion_queues_count;
	पूर्णांक rc, i, irq_cnt_init, irq;

	अगर (goya->hw_cap_initialized & HW_CAP_MSIX)
		वापस 0;

	rc = pci_alloc_irq_vectors(hdev->pdev, GOYA_MSIX_ENTRIES,
				GOYA_MSIX_ENTRIES, PCI_IRQ_MSIX);
	अगर (rc < 0) अणु
		dev_err(hdev->dev,
			"MSI-X: Failed to enable support -- %d/%d\n",
			GOYA_MSIX_ENTRIES, rc);
		वापस rc;
	पूर्ण

	क्रम (i = 0, irq_cnt_init = 0 ; i < cq_cnt ; i++, irq_cnt_init++) अणु
		irq = pci_irq_vector(hdev->pdev, i);
		rc = request_irq(irq, hl_irq_handler_cq, 0, goya_irq_name[i],
				&hdev->completion_queue[i]);
		अगर (rc) अणु
			dev_err(hdev->dev, "Failed to request IRQ %d", irq);
			जाओ मुक्त_irqs;
		पूर्ण
	पूर्ण

	irq = pci_irq_vector(hdev->pdev, GOYA_EVENT_QUEUE_MSIX_IDX);

	rc = request_irq(irq, hl_irq_handler_eq, 0,
			goya_irq_name[GOYA_EVENT_QUEUE_MSIX_IDX],
			&hdev->event_queue);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to request IRQ %d", irq);
		जाओ मुक्त_irqs;
	पूर्ण

	goya->hw_cap_initialized |= HW_CAP_MSIX;
	वापस 0;

मुक्त_irqs:
	क्रम (i = 0 ; i < irq_cnt_init ; i++)
		मुक्त_irq(pci_irq_vector(hdev->pdev, i),
			&hdev->completion_queue[i]);

	pci_मुक्त_irq_vectors(hdev->pdev);
	वापस rc;
पूर्ण

अटल व्योम goya_sync_irqs(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक i;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MSIX))
		वापस;

	/* Wait क्रम all pending IRQs to be finished */
	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		synchronize_irq(pci_irq_vector(hdev->pdev, i));

	synchronize_irq(pci_irq_vector(hdev->pdev, GOYA_EVENT_QUEUE_MSIX_IDX));
पूर्ण

अटल व्योम goya_disable_msix(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक i, irq;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MSIX))
		वापस;

	goya_sync_irqs(hdev);

	irq = pci_irq_vector(hdev->pdev, GOYA_EVENT_QUEUE_MSIX_IDX);
	मुक्त_irq(irq, &hdev->event_queue);

	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++) अणु
		irq = pci_irq_vector(hdev->pdev, i);
		मुक्त_irq(irq, &hdev->completion_queue[i]);
	पूर्ण

	pci_मुक्त_irq_vectors(hdev->pdev);

	goya->hw_cap_initialized &= ~HW_CAP_MSIX;
पूर्ण

अटल व्योम goya_enable_बारtamp(काष्ठा hl_device *hdev)
अणु
	/* Disable the बारtamp counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 0);

	/* Zero the lower/upper parts of the 64-bit counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE + 0xC, 0);
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE + 0x8, 0);

	/* Enable the counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 1);
पूर्ण

अटल व्योम goya_disable_बारtamp(काष्ठा hl_device *hdev)
अणु
	/* Disable the बारtamp counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 0);
पूर्ण

अटल व्योम goya_halt_engines(काष्ठा hl_device *hdev, bool hard_reset)
अणु
	u32 रुको_समयout_ms;

	dev_info(hdev->dev,
		"Halting compute engines and disabling interrupts\n");

	अगर (hdev->pldm)
		रुको_समयout_ms = GOYA_PLDM_RESET_WAIT_MSEC;
	अन्यथा
		रुको_समयout_ms = GOYA_RESET_WAIT_MSEC;

	goya_stop_बाह्यal_queues(hdev);
	goya_stop_पूर्णांकernal_queues(hdev);

	msleep(रुको_समयout_ms);

	goya_dma_stall(hdev);
	goya_tpc_stall(hdev);
	goya_mme_stall(hdev);

	msleep(रुको_समयout_ms);

	goya_disable_बाह्यal_queues(hdev);
	goya_disable_पूर्णांकernal_queues(hdev);

	goya_disable_बारtamp(hdev);

	अगर (hard_reset) अणु
		goya_disable_msix(hdev);
		goya_mmu_हटाओ_device_cpu_mappings(hdev);
	पूर्ण अन्यथा अणु
		goya_sync_irqs(hdev);
	पूर्ण
पूर्ण

/*
 * goya_load_firmware_to_device() - Load LINUX FW code to device.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 *
 * Copy LINUX fw code from firmware file to HBM BAR.
 *
 * Return: 0 on success, non-zero क्रम failure.
 */
अटल पूर्णांक goya_load_firmware_to_device(काष्ठा hl_device *hdev)
अणु
	व्योम __iomem *dst;

	dst = hdev->pcie_bar[DDR_BAR_ID] + LINUX_FW_OFFSET;

	वापस hl_fw_load_fw_to_device(hdev, GOYA_LINUX_FW_खाता, dst, 0, 0);
पूर्ण

/*
 * goya_load_boot_fit_to_device() - Load boot fit to device.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 *
 * Copy boot fit file to SRAM BAR.
 *
 * Return: 0 on success, non-zero क्रम failure.
 */
अटल पूर्णांक goya_load_boot_fit_to_device(काष्ठा hl_device *hdev)
अणु
	व्योम __iomem *dst;

	dst = hdev->pcie_bar[SRAM_CFG_BAR_ID] + BOOT_FIT_SRAM_OFFSET;

	वापस hl_fw_load_fw_to_device(hdev, GOYA_BOOT_FIT_खाता, dst, 0, 0);
पूर्ण

/*
 * FW component passes an offset from SRAM_BASE_ADDR in SCRATCHPAD_xx.
 * The version string should be located by that offset.
 */
अटल पूर्णांक goya_पढ़ो_device_fw_version(काष्ठा hl_device *hdev,
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
		स_नकल_fromio(dest, hdev->pcie_bar[SRAM_CFG_BAR_ID] + ver_off,
							VERSION_MAX_LEN);
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev, "%s version offset (0x%x) is above SRAM\n",
								name, ver_off);
		म_नकल(dest, "unavailable");

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_init_cpu(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक rc;

	अगर (!(hdev->fw_components & FW_TYPE_PREBOOT_CPU))
		वापस 0;

	अगर (goya->hw_cap_initialized & HW_CAP_CPU)
		वापस 0;

	/*
	 * Beक्रमe pushing u-boot/linux to device, need to set the ddr bar to
	 * base address of dram
	 */
	अगर (goya_set_ddr_bar_base(hdev, DRAM_PHYS_BASE) == U64_MAX) अणु
		dev_err(hdev->dev,
			"failed to map DDR bar to DRAM base address\n");
		वापस -EIO;
	पूर्ण

	rc = hl_fw_init_cpu(hdev, mmPSOC_GLOBAL_CONF_CPU_BOOT_STATUS,
			mmPSOC_GLOBAL_CONF_UBOOT_MAGIC,
			mmCPU_CMD_STATUS_TO_HOST,
			mmCPU_BOOT_DEV_STS0, mmCPU_BOOT_ERR0,
			false, GOYA_CPU_TIMEOUT_USEC,
			GOYA_BOOT_FIT_REQ_TIMEOUT_USEC);

	अगर (rc)
		वापस rc;

	goya->hw_cap_initialized |= HW_CAP_CPU;

	वापस 0;
पूर्ण

अटल पूर्णांक goya_mmu_update_asid_hop0_addr(काष्ठा hl_device *hdev, u32 asid,
						u64 phys_addr)
अणु
	u32 status, समयout_usec;
	पूर्णांक rc;

	अगर (hdev->pldm)
		समयout_usec = GOYA_PLDM_MMU_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = MMU_CONFIG_TIMEOUT_USEC;

	WREG32(MMU_HOP0_PA43_12, phys_addr >> MMU_HOP0_PA43_12_SHIFT);
	WREG32(MMU_HOP0_PA49_44, phys_addr >> MMU_HOP0_PA49_44_SHIFT);
	WREG32(MMU_ASID_BUSY, 0x80000000 | asid);

	rc = hl_poll_समयout(
		hdev,
		MMU_ASID_BUSY,
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

पूर्णांक goya_mmu_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u64 hop0_addr;
	पूर्णांक rc, i;

	अगर (!hdev->mmu_enable)
		वापस 0;

	अगर (goya->hw_cap_initialized & HW_CAP_MMU)
		वापस 0;

	hdev->dram_शेष_page_mapping = true;

	क्रम (i = 0 ; i < prop->max_asid ; i++) अणु
		hop0_addr = prop->mmu_pgt_addr +
				(i * prop->mmu_hop_table_size);

		rc = goya_mmu_update_asid_hop0_addr(hdev, i, hop0_addr);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed to set hop0 addr for asid %d\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	goya->hw_cap_initialized |= HW_CAP_MMU;

	/* init MMU cache manage page */
	WREG32(mmSTLB_CACHE_INV_BASE_39_8,
				lower_32_bits(MMU_CACHE_MNG_ADDR >> 8));
	WREG32(mmSTLB_CACHE_INV_BASE_49_40, MMU_CACHE_MNG_ADDR >> 40);

	/* Remove follower feature due to perक्रमmance bug */
	WREG32_AND(mmSTLB_STLB_FEATURE_EN,
			(~STLB_STLB_FEATURE_EN_FOLLOWER_EN_MASK));

	hdev->asic_funcs->mmu_invalidate_cache(hdev, true,
					VM_TYPE_USERPTR | VM_TYPE_PHYS_PACK);

	WREG32(mmMMU_MMU_ENABLE, 1);
	WREG32(mmMMU_SPI_MASK, 0xF);

	वापस 0;

err:
	वापस rc;
पूर्ण

/*
 * goya_hw_init - Goya hardware initialization code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 * Returns 0 on success
 *
 */
अटल पूर्णांक goya_hw_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक rc;

	/* Perक्रमm पढ़ो from the device to make sure device is up */
	RREG32(mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG);

	/*
	 * Let's mark in the H/W that we have reached this poपूर्णांक. We check
	 * this value in the reset_beक्रमe_init function to understand whether
	 * we need to reset the chip beक्रमe करोing H/W init. This रेजिस्टर is
	 * cleared by the H/W upon H/W reset
	 */
	WREG32(mmHW_STATE, HL_DEVICE_HW_STATE_सूचीTY);

	rc = goya_init_cpu(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize CPU\n");
		वापस rc;
	पूर्ण

	goya_tpc_mbist_workaround(hdev);

	goya_init_golden_रेजिस्टरs(hdev);

	/*
	 * After CPU initialization is finished, change DDR bar mapping inside
	 * iATU to poपूर्णांक to the start address of the MMU page tables
	 */
	अगर (goya_set_ddr_bar_base(hdev, (MMU_PAGE_TABLES_ADDR &
			~(prop->dram_pci_bar_size - 0x1ull))) == U64_MAX) अणु
		dev_err(hdev->dev,
			"failed to map DDR bar to MMU page tables\n");
		वापस -EIO;
	पूर्ण

	rc = goya_mmu_init(hdev);
	अगर (rc)
		वापस rc;

	goya_init_security(hdev);

	goya_init_dma_qmans(hdev);

	goya_init_mme_qmans(hdev);

	goya_init_tpc_qmans(hdev);

	goya_enable_बारtamp(hdev);

	/* MSI-X must be enabled beक्रमe CPU queues are initialized */
	rc = goya_enable_msix(hdev);
	अगर (rc)
		जाओ disable_queues;

	/* Perक्रमm पढ़ो from the device to flush all MSI-X configuration */
	RREG32(mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG);

	वापस 0;

disable_queues:
	goya_disable_पूर्णांकernal_queues(hdev);
	goya_disable_बाह्यal_queues(hdev);

	वापस rc;
पूर्ण

/*
 * goya_hw_fini - Goya hardware tear-करोwn code
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 * @hard_reset: should we करो hard reset to all engines or just reset the
 *              compute/dma engines
 */
अटल व्योम goya_hw_fini(काष्ठा hl_device *hdev, bool hard_reset)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 reset_समयout_ms, cpu_समयout_ms, status;

	अगर (hdev->pldm) अणु
		reset_समयout_ms = GOYA_PLDM_RESET_TIMEOUT_MSEC;
		cpu_समयout_ms = GOYA_PLDM_RESET_WAIT_MSEC;
	पूर्ण अन्यथा अणु
		reset_समयout_ms = GOYA_RESET_TIMEOUT_MSEC;
		cpu_समयout_ms = GOYA_CPU_RESET_WAIT_MSEC;
	पूर्ण

	अगर (hard_reset) अणु
		/* I करोn't know what is the state of the CPU so make sure it is
		 * stopped in any means necessary
		 */
		WREG32(mmPSOC_GLOBAL_CONF_UBOOT_MAGIC, KMD_MSG_GOTO_WFE);
		WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
			GOYA_ASYNC_EVENT_ID_HALT_MACHINE);

		msleep(cpu_समयout_ms);

		goya_set_ddr_bar_base(hdev, DRAM_PHYS_BASE);
		goya_disable_clk_rlx(hdev);
		goya_set_pll_refclk(hdev);

		WREG32(mmPSOC_GLOBAL_CONF_SW_ALL_RST_CFG, RESET_ALL);
		dev_info(hdev->dev,
			"Issued HARD reset command, going to wait %dms\n",
			reset_समयout_ms);
	पूर्ण अन्यथा अणु
		WREG32(mmPSOC_GLOBAL_CONF_SW_ALL_RST_CFG, DMA_MME_TPC_RESET);
		dev_info(hdev->dev,
			"Issued SOFT reset command, going to wait %dms\n",
			reset_समयout_ms);
	पूर्ण

	/*
	 * After hard reset, we can't poll the BTM_FSM रेजिस्टर because the PSOC
	 * itself is in reset. In either reset we need to रुको until the reset
	 * is deनिश्चितed
	 */
	msleep(reset_समयout_ms);

	status = RREG32(mmPSOC_GLOBAL_CONF_BTM_FSM);
	अगर (status & PSOC_GLOBAL_CONF_BTM_FSM_STATE_MASK)
		dev_err(hdev->dev,
			"Timeout while waiting for device to reset 0x%x\n",
			status);

	अगर (!hard_reset && goya) अणु
		goya->hw_cap_initialized &= ~(HW_CAP_DMA | HW_CAP_MME |
						HW_CAP_GOLDEN | HW_CAP_TPC);
		WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
				GOYA_ASYNC_EVENT_ID_SOFT_RESET);
		वापस;
	पूर्ण

	/* Chicken bit to re-initiate boot sequencer flow */
	WREG32(mmPSOC_GLOBAL_CONF_BOOT_SEQ_RE_START,
		1 << PSOC_GLOBAL_CONF_BOOT_SEQ_RE_START_IND_SHIFT);
	/* Move boot manager FSM to pre boot sequencer init state */
	WREG32(mmPSOC_GLOBAL_CONF_SW_BTM_FSM,
			0xA << PSOC_GLOBAL_CONF_SW_BTM_FSM_CTRL_SHIFT);

	अगर (goya) अणु
		goya->hw_cap_initialized &= ~(HW_CAP_CPU | HW_CAP_CPU_Q |
				HW_CAP_DDR_0 | HW_CAP_DDR_1 |
				HW_CAP_DMA | HW_CAP_MME |
				HW_CAP_MMU | HW_CAP_TPC_MBIST |
				HW_CAP_GOLDEN | HW_CAP_TPC);

		स_रखो(goya->events_stat, 0, माप(goya->events_stat));
	पूर्ण
पूर्ण

पूर्णांक goya_suspend(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	rc = hl_fw_send_pci_access_msg(hdev, CPUCP_PACKET_DISABLE_PCI_ACCESS);
	अगर (rc)
		dev_err(hdev->dev, "Failed to disable PCI access from CPU\n");

	वापस rc;
पूर्ण

पूर्णांक goya_resume(काष्ठा hl_device *hdev)
अणु
	वापस goya_init_iatu(hdev);
पूर्ण

अटल पूर्णांक goya_cb_mmap(काष्ठा hl_device *hdev, काष्ठा vm_area_काष्ठा *vma,
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

व्योम goya_ring_करोorbell(काष्ठा hl_device *hdev, u32 hw_queue_id, u32 pi)
अणु
	u32 db_reg_offset, db_value;

	चयन (hw_queue_id) अणु
	हाल GOYA_QUEUE_ID_DMA_0:
		db_reg_offset = mmDMA_QM_0_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_DMA_1:
		db_reg_offset = mmDMA_QM_1_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_DMA_2:
		db_reg_offset = mmDMA_QM_2_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_DMA_3:
		db_reg_offset = mmDMA_QM_3_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_DMA_4:
		db_reg_offset = mmDMA_QM_4_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_CPU_PQ:
		db_reg_offset = mmCPU_IF_PF_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_MME:
		db_reg_offset = mmMME_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC0:
		db_reg_offset = mmTPC0_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC1:
		db_reg_offset = mmTPC1_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC2:
		db_reg_offset = mmTPC2_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC3:
		db_reg_offset = mmTPC3_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC4:
		db_reg_offset = mmTPC4_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC5:
		db_reg_offset = mmTPC5_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC6:
		db_reg_offset = mmTPC6_QM_PQ_PI;
		अवरोध;

	हाल GOYA_QUEUE_ID_TPC7:
		db_reg_offset = mmTPC7_QM_PQ_PI;
		अवरोध;

	शेष:
		/* Should never get here */
		dev_err(hdev->dev, "H/W queue %d is invalid. Can't set pi\n",
			hw_queue_id);
		वापस;
	पूर्ण

	db_value = pi;

	/* ring the करोorbell */
	WREG32(db_reg_offset, db_value);

	अगर (hw_queue_id == GOYA_QUEUE_ID_CPU_PQ) अणु
		/* make sure device CPU will पढ़ो latest data from host */
		mb();
		WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
				GOYA_ASYNC_EVENT_ID_PI_UPDATE);
	पूर्ण
पूर्ण

व्योम goya_pqe_ग_लिखो(काष्ठा hl_device *hdev, __le64 *pqe, काष्ठा hl_bd *bd)
अणु
	/* The QMANs are on the SRAM so need to copy to IO space */
	स_नकल_toio((व्योम __iomem *) pqe, bd, माप(काष्ठा hl_bd));
पूर्ण

अटल व्योम *goya_dma_alloc_coherent(काष्ठा hl_device *hdev, माप_प्रकार size,
					dma_addr_t *dma_handle, gfp_t flags)
अणु
	व्योम *kernel_addr = dma_alloc_coherent(&hdev->pdev->dev, size,
						dma_handle, flags);

	/* Shअगरt to the device's base physical address of host memory */
	अगर (kernel_addr)
		*dma_handle += HOST_PHYS_BASE;

	वापस kernel_addr;
पूर्ण

अटल व्योम goya_dma_मुक्त_coherent(काष्ठा hl_device *hdev, माप_प्रकार size,
					व्योम *cpu_addr, dma_addr_t dma_handle)
अणु
	/* Cancel the device's base physical address of host memory */
	dma_addr_t fixed_dma_handle = dma_handle - HOST_PHYS_BASE;

	dma_मुक्त_coherent(&hdev->pdev->dev, size, cpu_addr, fixed_dma_handle);
पूर्ण

पूर्णांक goya_scrub_device_mem(काष्ठा hl_device *hdev, u64 addr, u64 size)
अणु
	वापस 0;
पूर्ण

व्योम *goya_get_पूर्णांक_queue_base(काष्ठा hl_device *hdev, u32 queue_id,
				dma_addr_t *dma_handle,	u16 *queue_len)
अणु
	व्योम *base;
	u32 offset;

	*dma_handle = hdev->asic_prop.sram_base_address;

	base = (व्योम *) hdev->pcie_bar[SRAM_CFG_BAR_ID];

	चयन (queue_id) अणु
	हाल GOYA_QUEUE_ID_MME:
		offset = MME_QMAN_BASE_OFFSET;
		*queue_len = MME_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC0:
		offset = TPC0_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC1:
		offset = TPC1_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC2:
		offset = TPC2_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC3:
		offset = TPC3_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC4:
		offset = TPC4_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC5:
		offset = TPC5_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC6:
		offset = TPC6_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	हाल GOYA_QUEUE_ID_TPC7:
		offset = TPC7_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		अवरोध;
	शेष:
		dev_err(hdev->dev, "Got invalid queue id %d\n", queue_id);
		वापस शून्य;
	पूर्ण

	base += offset;
	*dma_handle += offset;

	वापस base;
पूर्ण

अटल पूर्णांक goya_send_job_on_qman0(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job)
अणु
	काष्ठा packet_msg_prot *fence_pkt;
	u32 *fence_ptr;
	dma_addr_t fence_dma_addr;
	काष्ठा hl_cb *cb;
	u32 पंचांगp, समयout;
	पूर्णांक rc;

	अगर (hdev->pldm)
		समयout = GOYA_PLDM_QMAN0_TIMEOUT_USEC;
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

	goya_qman0_set_security(hdev, true);

	cb = job->patched_cb;

	fence_pkt = cb->kernel_address +
			job->job_cb_size - माप(काष्ठा packet_msg_prot);

	पंचांगp = (PACKET_MSG_PROT << GOYA_PKT_CTL_OPCODE_SHIFT) |
			(1 << GOYA_PKT_CTL_EB_SHIFT) |
			(1 << GOYA_PKT_CTL_MB_SHIFT);
	fence_pkt->ctl = cpu_to_le32(पंचांगp);
	fence_pkt->value = cpu_to_le32(GOYA_QMAN0_FENCE_VAL);
	fence_pkt->addr = cpu_to_le64(fence_dma_addr);

	rc = hl_hw_queue_send_cb_no_cmpl(hdev, GOYA_QUEUE_ID_DMA_0,
					job->job_cb_size, cb->bus_address);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to send CB on QMAN0, %d\n", rc);
		जाओ मुक्त_fence_ptr;
	पूर्ण

	rc = hl_poll_समयout_memory(hdev, fence_ptr, पंचांगp,
				(पंचांगp == GOYA_QMAN0_FENCE_VAL), 1000,
				समयout, true);

	hl_hw_queue_inc_ci_kernel(hdev, GOYA_QUEUE_ID_DMA_0);

	अगर (rc == -ETIMEDOUT) अणु
		dev_err(hdev->dev, "QMAN0 Job timeout (0x%x)\n", पंचांगp);
		जाओ मुक्त_fence_ptr;
	पूर्ण

मुक्त_fence_ptr:
	hdev->asic_funcs->asic_dma_pool_मुक्त(hdev, (व्योम *) fence_ptr,
					fence_dma_addr);

	goya_qman0_set_security(hdev, false);

	वापस rc;
पूर्ण

पूर्णांक goya_send_cpu_message(काष्ठा hl_device *hdev, u32 *msg, u16 len,
				u32 समयout, u64 *result)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_CPU_Q)) अणु
		अगर (result)
			*result = 0;
		वापस 0;
	पूर्ण

	अगर (!समयout)
		समयout = GOYA_MSG_TO_CPU_TIMEOUT_USEC;

	वापस hl_fw_send_cpu_message(hdev, GOYA_QUEUE_ID_CPU_PQ, msg, len,
					समयout, result);
पूर्ण

पूर्णांक goya_test_queue(काष्ठा hl_device *hdev, u32 hw_queue_id)
अणु
	काष्ठा packet_msg_prot *fence_pkt;
	dma_addr_t pkt_dma_addr;
	u32 fence_val, पंचांगp;
	dma_addr_t fence_dma_addr;
	u32 *fence_ptr;
	पूर्णांक rc;

	fence_val = GOYA_QMAN0_FENCE_VAL;

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

	पंचांगp = (PACKET_MSG_PROT << GOYA_PKT_CTL_OPCODE_SHIFT) |
			(1 << GOYA_PKT_CTL_EB_SHIFT) |
			(1 << GOYA_PKT_CTL_MB_SHIFT);
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
					1000, GOYA_TEST_QUEUE_WAIT_USEC, true);

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

पूर्णांक goya_test_cpu_queue(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	/*
	 * check capability here as send_cpu_message() won't update the result
	 * value अगर no capability
	 */
	अगर (!(goya->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	वापस hl_fw_test_cpu_queue(hdev);
पूर्ण

पूर्णांक goya_test_queues(काष्ठा hl_device *hdev)
अणु
	पूर्णांक i, rc, ret_val = 0;

	क्रम (i = 0 ; i < NUMBER_OF_EXT_HW_QUEUES ; i++) अणु
		rc = goya_test_queue(hdev, i);
		अगर (rc)
			ret_val = -EINVAL;
	पूर्ण

	वापस ret_val;
पूर्ण

अटल व्योम *goya_dma_pool_zalloc(काष्ठा hl_device *hdev, माप_प्रकार size,
					gfp_t mem_flags, dma_addr_t *dma_handle)
अणु
	व्योम *kernel_addr;

	अगर (size > GOYA_DMA_POOL_BLK_SIZE)
		वापस शून्य;

	kernel_addr =  dma_pool_zalloc(hdev->dma_pool, mem_flags, dma_handle);

	/* Shअगरt to the device's base physical address of host memory */
	अगर (kernel_addr)
		*dma_handle += HOST_PHYS_BASE;

	वापस kernel_addr;
पूर्ण

अटल व्योम goya_dma_pool_मुक्त(काष्ठा hl_device *hdev, व्योम *vaddr,
				dma_addr_t dma_addr)
अणु
	/* Cancel the device's base physical address of host memory */
	dma_addr_t fixed_dma_addr = dma_addr - HOST_PHYS_BASE;

	dma_pool_मुक्त(hdev->dma_pool, vaddr, fixed_dma_addr);
पूर्ण

व्योम *goya_cpu_accessible_dma_pool_alloc(काष्ठा hl_device *hdev, माप_प्रकार size,
					dma_addr_t *dma_handle)
अणु
	व्योम *vaddr;

	vaddr = hl_fw_cpu_accessible_dma_pool_alloc(hdev, size, dma_handle);
	*dma_handle = (*dma_handle) - hdev->cpu_accessible_dma_address +
			VA_CPU_ACCESSIBLE_MEM_ADDR;

	वापस vaddr;
पूर्ण

व्योम goya_cpu_accessible_dma_pool_मुक्त(काष्ठा hl_device *hdev, माप_प्रकार size,
					व्योम *vaddr)
अणु
	hl_fw_cpu_accessible_dma_pool_मुक्त(hdev, size, vaddr);
पूर्ण

अटल पूर्णांक goya_dma_map_sg(काष्ठा hl_device *hdev, काष्ठा scatterlist *sgl,
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

अटल व्योम goya_dma_unmap_sg(काष्ठा hl_device *hdev, काष्ठा scatterlist *sgl,
				पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	/* Cancel the device's base physical address of host memory */
	क्रम_each_sg(sgl, sg, nents, i)
		sg->dma_address -= HOST_PHYS_BASE;

	dma_unmap_sg(&hdev->pdev->dev, sgl, nents, dir);
पूर्ण

u32 goya_get_dma_desc_list_size(काष्ठा hl_device *hdev, काष्ठा sg_table *sgt)
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

अटल पूर्णांक goya_pin_memory_beक्रमe_cs(काष्ठा hl_device *hdev,
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
			goya_get_dma_desc_list_size(hdev, userptr->sgt);

	वापस 0;

unpin_memory:
	hl_unpin_host_memory(hdev, userptr);
मुक्त_userptr:
	kमुक्त(userptr);
	वापस rc;
पूर्ण

अटल पूर्णांक goya_validate_dma_pkt_host(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt)
अणु
	u64 device_memory_addr, addr;
	क्रमागत dma_data_direction dir;
	क्रमागत goya_dma_direction user_dir;
	bool sram_addr = true;
	bool skip_host_mem_pin = false;
	bool user_स_रखो;
	u32 ctl;
	पूर्णांक rc = 0;

	ctl = le32_to_cpu(user_dma_pkt->ctl);

	user_dir = (ctl & GOYA_PKT_LIN_DMA_CTL_DMA_सूची_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_DMA_सूची_SHIFT;

	user_स_रखो = (ctl & GOYA_PKT_LIN_DMA_CTL_MEMSET_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_MEMSET_SHIFT;

	चयन (user_dir) अणु
	हाल DMA_HOST_TO_DRAM:
		dev_dbg(hdev->dev, "DMA direction is HOST --> DRAM\n");
		dir = DMA_TO_DEVICE;
		sram_addr = false;
		addr = le64_to_cpu(user_dma_pkt->src_addr);
		device_memory_addr = le64_to_cpu(user_dma_pkt->dst_addr);
		अगर (user_स_रखो)
			skip_host_mem_pin = true;
		अवरोध;

	हाल DMA_DRAM_TO_HOST:
		dev_dbg(hdev->dev, "DMA direction is DRAM --> HOST\n");
		dir = DMA_FROM_DEVICE;
		sram_addr = false;
		addr = le64_to_cpu(user_dma_pkt->dst_addr);
		device_memory_addr = le64_to_cpu(user_dma_pkt->src_addr);
		अवरोध;

	हाल DMA_HOST_TO_SRAM:
		dev_dbg(hdev->dev, "DMA direction is HOST --> SRAM\n");
		dir = DMA_TO_DEVICE;
		addr = le64_to_cpu(user_dma_pkt->src_addr);
		device_memory_addr = le64_to_cpu(user_dma_pkt->dst_addr);
		अगर (user_स_रखो)
			skip_host_mem_pin = true;
		अवरोध;

	हाल DMA_SRAM_TO_HOST:
		dev_dbg(hdev->dev, "DMA direction is SRAM --> HOST\n");
		dir = DMA_FROM_DEVICE;
		addr = le64_to_cpu(user_dma_pkt->dst_addr);
		device_memory_addr = le64_to_cpu(user_dma_pkt->src_addr);
		अवरोध;
	शेष:
		dev_err(hdev->dev, "DMA direction is undefined\n");
		वापस -EFAULT;
	पूर्ण

	अगर (sram_addr) अणु
		अगर (!hl_mem_area_inside_range(device_memory_addr,
				le32_to_cpu(user_dma_pkt->tsize),
				hdev->asic_prop.sram_user_base_address,
				hdev->asic_prop.sram_end_address)) अणु

			dev_err(hdev->dev,
				"SRAM address 0x%llx + 0x%x is invalid\n",
				device_memory_addr,
				user_dma_pkt->tsize);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!hl_mem_area_inside_range(device_memory_addr,
				le32_to_cpu(user_dma_pkt->tsize),
				hdev->asic_prop.dram_user_base_address,
				hdev->asic_prop.dram_end_address)) अणु

			dev_err(hdev->dev,
				"DRAM address 0x%llx + 0x%x is invalid\n",
				device_memory_addr,
				user_dma_pkt->tsize);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (skip_host_mem_pin)
		parser->patched_cb_size += माप(*user_dma_pkt);
	अन्यथा अणु
		अगर ((dir == DMA_TO_DEVICE) &&
				(parser->hw_queue_id > GOYA_QUEUE_ID_DMA_1)) अणु
			dev_err(hdev->dev,
				"Can't DMA from host on queue other then 1\n");
			वापस -EFAULT;
		पूर्ण

		rc = goya_pin_memory_beक्रमe_cs(hdev, parser, user_dma_pkt,
						addr, dir);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक goya_validate_dma_pkt_no_host(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt)
अणु
	u64 sram_memory_addr, dram_memory_addr;
	क्रमागत goya_dma_direction user_dir;
	u32 ctl;

	ctl = le32_to_cpu(user_dma_pkt->ctl);
	user_dir = (ctl & GOYA_PKT_LIN_DMA_CTL_DMA_सूची_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_DMA_सूची_SHIFT;

	अगर (user_dir == DMA_DRAM_TO_SRAM) अणु
		dev_dbg(hdev->dev, "DMA direction is DRAM --> SRAM\n");
		dram_memory_addr = le64_to_cpu(user_dma_pkt->src_addr);
		sram_memory_addr = le64_to_cpu(user_dma_pkt->dst_addr);
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev, "DMA direction is SRAM --> DRAM\n");
		sram_memory_addr = le64_to_cpu(user_dma_pkt->src_addr);
		dram_memory_addr = le64_to_cpu(user_dma_pkt->dst_addr);
	पूर्ण

	अगर (!hl_mem_area_inside_range(sram_memory_addr,
				le32_to_cpu(user_dma_pkt->tsize),
				hdev->asic_prop.sram_user_base_address,
				hdev->asic_prop.sram_end_address)) अणु
		dev_err(hdev->dev, "SRAM address 0x%llx + 0x%x is invalid\n",
			sram_memory_addr, user_dma_pkt->tsize);
		वापस -EFAULT;
	पूर्ण

	अगर (!hl_mem_area_inside_range(dram_memory_addr,
				le32_to_cpu(user_dma_pkt->tsize),
				hdev->asic_prop.dram_user_base_address,
				hdev->asic_prop.dram_end_address)) अणु
		dev_err(hdev->dev, "DRAM address 0x%llx + 0x%x is invalid\n",
			dram_memory_addr, user_dma_pkt->tsize);
		वापस -EFAULT;
	पूर्ण

	parser->patched_cb_size += माप(*user_dma_pkt);

	वापस 0;
पूर्ण

अटल पूर्णांक goya_validate_dma_pkt_no_mmu(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt)
अणु
	क्रमागत goya_dma_direction user_dir;
	u32 ctl;
	पूर्णांक rc;

	dev_dbg(hdev->dev, "DMA packet details:\n");
	dev_dbg(hdev->dev, "source == 0x%llx\n",
		le64_to_cpu(user_dma_pkt->src_addr));
	dev_dbg(hdev->dev, "destination == 0x%llx\n",
		le64_to_cpu(user_dma_pkt->dst_addr));
	dev_dbg(hdev->dev, "size == %u\n", le32_to_cpu(user_dma_pkt->tsize));

	ctl = le32_to_cpu(user_dma_pkt->ctl);
	user_dir = (ctl & GOYA_PKT_LIN_DMA_CTL_DMA_सूची_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_DMA_सूची_SHIFT;

	/*
	 * Special handling क्रम DMA with size 0. The H/W has a bug where
	 * this can cause the QMAN DMA to get stuck, so block it here.
	 */
	अगर (user_dma_pkt->tsize == 0) अणु
		dev_err(hdev->dev,
			"Got DMA with size 0, might reset the device\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((user_dir == DMA_DRAM_TO_SRAM) || (user_dir == DMA_SRAM_TO_DRAM))
		rc = goya_validate_dma_pkt_no_host(hdev, parser, user_dma_pkt);
	अन्यथा
		rc = goya_validate_dma_pkt_host(hdev, parser, user_dma_pkt);

	वापस rc;
पूर्ण

अटल पूर्णांक goya_validate_dma_pkt_mmu(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt)
अणु
	dev_dbg(hdev->dev, "DMA packet details:\n");
	dev_dbg(hdev->dev, "source == 0x%llx\n",
		le64_to_cpu(user_dma_pkt->src_addr));
	dev_dbg(hdev->dev, "destination == 0x%llx\n",
		le64_to_cpu(user_dma_pkt->dst_addr));
	dev_dbg(hdev->dev, "size == %u\n", le32_to_cpu(user_dma_pkt->tsize));

	/*
	 * WA क्रम HW-23.
	 * We can't allow user to पढ़ो from Host using QMANs other than 1.
	 * PMMU and HPMMU addresses are equal, check only one of them.
	 */
	अगर (parser->hw_queue_id != GOYA_QUEUE_ID_DMA_1 &&
		hl_mem_area_inside_range(le64_to_cpu(user_dma_pkt->src_addr),
				le32_to_cpu(user_dma_pkt->tsize),
				hdev->asic_prop.pmmu.start_addr,
				hdev->asic_prop.pmmu.end_addr)) अणु
		dev_err(hdev->dev,
			"Can't DMA from host on queue other then 1\n");
		वापस -EFAULT;
	पूर्ण

	अगर (user_dma_pkt->tsize == 0) अणु
		dev_err(hdev->dev,
			"Got DMA with size 0, might reset the device\n");
		वापस -EINVAL;
	पूर्ण

	parser->patched_cb_size += माप(*user_dma_pkt);

	वापस 0;
पूर्ण

अटल पूर्णांक goya_validate_wreg32(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_wreg32 *wreg_pkt)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 sob_start_addr, sob_end_addr;
	u16 reg_offset;

	reg_offset = le32_to_cpu(wreg_pkt->ctl) &
			GOYA_PKT_WREG32_CTL_REG_OFFSET_MASK;

	dev_dbg(hdev->dev, "WREG32 packet details:\n");
	dev_dbg(hdev->dev, "reg_offset == 0x%x\n", reg_offset);
	dev_dbg(hdev->dev, "value      == 0x%x\n",
		le32_to_cpu(wreg_pkt->value));

	अगर (reg_offset != (mmDMA_CH_0_WR_COMP_ADDR_LO & 0x1FFF)) अणु
		dev_err(hdev->dev, "WREG32 packet with illegal address 0x%x\n",
			reg_offset);
		वापस -EPERM;
	पूर्ण

	/*
	 * With MMU, DMA channels are not secured, so it करोesn't matter where
	 * the WR COMP will be written to because it will go out with
	 * non-secured property
	 */
	अगर (goya->hw_cap_initialized & HW_CAP_MMU)
		वापस 0;

	sob_start_addr = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	sob_end_addr = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1023);

	अगर ((le32_to_cpu(wreg_pkt->value) < sob_start_addr) ||
			(le32_to_cpu(wreg_pkt->value) > sob_end_addr)) अणु

		dev_err(hdev->dev, "WREG32 packet with illegal value 0x%x\n",
			wreg_pkt->value);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_validate_cb(काष्ठा hl_device *hdev,
			काष्ठा hl_cs_parser *parser, bool is_mmu)
अणु
	u32 cb_parsed_length = 0;
	पूर्णांक rc = 0;

	parser->patched_cb_size = 0;

	/* cb_user_size is more than 0 so loop will always be executed */
	जबतक (cb_parsed_length < parser->user_cb_size) अणु
		क्रमागत packet_id pkt_id;
		u16 pkt_size;
		काष्ठा goya_packet *user_pkt;

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

		pkt_size = goya_packet_sizes[pkt_id];
		cb_parsed_length += pkt_size;
		अगर (cb_parsed_length > parser->user_cb_size) अणु
			dev_err(hdev->dev,
				"packet 0x%x is out of CB boundary\n", pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (pkt_id) अणु
		हाल PACKET_WREG_32:
			/*
			 * Although it is validated after copy in patch_cb(),
			 * need to validate here as well because patch_cb() is
			 * not called in MMU path जबतक this function is called
			 */
			rc = goya_validate_wreg32(hdev,
				parser, (काष्ठा packet_wreg32 *) user_pkt);
			parser->patched_cb_size += pkt_size;
			अवरोध;

		हाल PACKET_WREG_BULK:
			dev_err(hdev->dev,
				"User not allowed to use WREG_BULK\n");
			rc = -EPERM;
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

		हाल PACKET_LIN_DMA:
			अगर (is_mmu)
				rc = goya_validate_dma_pkt_mmu(hdev, parser,
					(काष्ठा packet_lin_dma *) user_pkt);
			अन्यथा
				rc = goya_validate_dma_pkt_no_mmu(hdev, parser,
					(काष्ठा packet_lin_dma *) user_pkt);
			अवरोध;

		हाल PACKET_MSG_LONG:
		हाल PACKET_MSG_SHORT:
		हाल PACKET_FENCE:
		हाल PACKET_NOP:
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
	parser->patched_cb_size += माप(काष्ठा packet_msg_prot) * 2;

	वापस rc;
पूर्ण

अटल पूर्णांक goya_patch_dma_packet(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser,
				काष्ठा packet_lin_dma *user_dma_pkt,
				काष्ठा packet_lin_dma *new_dma_pkt,
				u32 *new_dma_pkt_size)
अणु
	काष्ठा hl_userptr *userptr;
	काष्ठा scatterlist *sg, *sg_next_iter;
	u32 count, dma_desc_cnt;
	u64 len, len_next;
	dma_addr_t dma_addr, dma_addr_next;
	क्रमागत goya_dma_direction user_dir;
	u64 device_memory_addr, addr;
	क्रमागत dma_data_direction dir;
	काष्ठा sg_table *sgt;
	bool skip_host_mem_pin = false;
	bool user_स_रखो;
	u32 user_rdcomp_mask, user_wrcomp_mask, ctl;

	ctl = le32_to_cpu(user_dma_pkt->ctl);

	user_dir = (ctl & GOYA_PKT_LIN_DMA_CTL_DMA_सूची_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_DMA_सूची_SHIFT;

	user_स_रखो = (ctl & GOYA_PKT_LIN_DMA_CTL_MEMSET_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_MEMSET_SHIFT;

	अगर ((user_dir == DMA_DRAM_TO_SRAM) || (user_dir == DMA_SRAM_TO_DRAM) ||
			(user_dma_pkt->tsize == 0)) अणु
		स_नकल(new_dma_pkt, user_dma_pkt, माप(*new_dma_pkt));
		*new_dma_pkt_size = माप(*new_dma_pkt);
		वापस 0;
	पूर्ण

	अगर ((user_dir == DMA_HOST_TO_DRAM) || (user_dir == DMA_HOST_TO_SRAM)) अणु
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
		(hl_userptr_is_pinned(hdev, addr,
			le32_to_cpu(user_dma_pkt->tsize),
			parser->job_userptr_list, &userptr) == false)) अणु
		dev_err(hdev->dev, "Userptr 0x%llx + 0x%x NOT mapped\n",
				addr, user_dma_pkt->tsize);
		वापस -EFAULT;
	पूर्ण

	अगर ((user_स_रखो) && (dir == DMA_TO_DEVICE)) अणु
		स_नकल(new_dma_pkt, user_dma_pkt, माप(*user_dma_pkt));
		*new_dma_pkt_size = माप(*user_dma_pkt);
		वापस 0;
	पूर्ण

	user_rdcomp_mask = ctl & GOYA_PKT_LIN_DMA_CTL_RDCOMP_MASK;

	user_wrcomp_mask = ctl & GOYA_PKT_LIN_DMA_CTL_WRCOMP_MASK;

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
			ctl &= ~GOYA_PKT_CTL_EB_MASK;
		ctl &= ~(GOYA_PKT_LIN_DMA_CTL_RDCOMP_MASK |
				GOYA_PKT_LIN_DMA_CTL_WRCOMP_MASK);
		new_dma_pkt->ctl = cpu_to_le32(ctl);
		new_dma_pkt->tsize = cpu_to_le32((u32) len);

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

	/* Fix the last dma packet - rdcomp/wrcomp must be as user set them */
	new_dma_pkt--;
	new_dma_pkt->ctl |= cpu_to_le32(user_rdcomp_mask | user_wrcomp_mask);

	*new_dma_pkt_size = dma_desc_cnt * माप(काष्ठा packet_lin_dma);

	वापस 0;
पूर्ण

अटल पूर्णांक goya_patch_cb(काष्ठा hl_device *hdev,
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
		काष्ठा goya_packet *user_pkt, *kernel_pkt;

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

		pkt_size = goya_packet_sizes[pkt_id];
		cb_parsed_length += pkt_size;
		अगर (cb_parsed_length > parser->user_cb_size) अणु
			dev_err(hdev->dev,
				"packet 0x%x is out of CB boundary\n", pkt_id);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (pkt_id) अणु
		हाल PACKET_LIN_DMA:
			rc = goya_patch_dma_packet(hdev, parser,
					(काष्ठा packet_lin_dma *) user_pkt,
					(काष्ठा packet_lin_dma *) kernel_pkt,
					&new_pkt_size);
			cb_patched_cur_length += new_pkt_size;
			अवरोध;

		हाल PACKET_WREG_32:
			स_नकल(kernel_pkt, user_pkt, pkt_size);
			cb_patched_cur_length += pkt_size;
			rc = goya_validate_wreg32(hdev, parser,
					(काष्ठा packet_wreg32 *) kernel_pkt);
			अवरोध;

		हाल PACKET_WREG_BULK:
			dev_err(hdev->dev,
				"User not allowed to use WREG_BULK\n");
			rc = -EPERM;
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

		हाल PACKET_MSG_LONG:
		हाल PACKET_MSG_SHORT:
		हाल PACKET_FENCE:
		हाल PACKET_NOP:
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

अटल पूर्णांक goya_parse_cb_mmu(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_parser *parser)
अणु
	u64 patched_cb_handle;
	u32 patched_cb_size;
	काष्ठा hl_cb *user_cb;
	पूर्णांक rc;

	/*
	 * The new CB should have space at the end क्रम two MSG_PROT pkt:
	 * 1. A packet that will act as a completion packet
	 * 2. A packet that will generate MSI-X पूर्णांकerrupt
	 */
	parser->patched_cb_size = parser->user_cb_size +
			माप(काष्ठा packet_msg_prot) * 2;

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
	/* hl_cb_get should never fail here */
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

	/* validate patched CB instead of user CB */
	user_cb = parser->user_cb;
	parser->user_cb = parser->patched_cb;
	rc = goya_validate_cb(hdev, parser, true);
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

अटल पूर्णांक goya_parse_cb_no_mmu(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_parser *parser)
अणु
	u64 patched_cb_handle;
	पूर्णांक rc;

	rc = goya_validate_cb(hdev, parser, false);

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

	rc = goya_patch_cb(hdev, parser);

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

अटल पूर्णांक goya_parse_cb_no_ext_queue(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_parser *parser)
अणु
	काष्ठा asic_fixed_properties *asic_prop = &hdev->asic_prop;
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (goya->hw_cap_initialized & HW_CAP_MMU)
		वापस 0;

	/* For पूर्णांकernal queue jobs, just check अगर CB address is valid */
	अगर (hl_mem_area_inside_range(
			(u64) (uपूर्णांकptr_t) parser->user_cb,
			parser->user_cb_size,
			asic_prop->sram_user_base_address,
			asic_prop->sram_end_address))
		वापस 0;

	अगर (hl_mem_area_inside_range(
			(u64) (uपूर्णांकptr_t) parser->user_cb,
			parser->user_cb_size,
			asic_prop->dram_user_base_address,
			asic_prop->dram_end_address))
		वापस 0;

	dev_err(hdev->dev,
		"Internal CB address 0x%px + 0x%x is not in SRAM nor in DRAM\n",
		parser->user_cb, parser->user_cb_size);

	वापस -EFAULT;
पूर्ण

पूर्णांक goya_cs_parser(काष्ठा hl_device *hdev, काष्ठा hl_cs_parser *parser)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (parser->queue_type == QUEUE_TYPE_INT)
		वापस goya_parse_cb_no_ext_queue(hdev, parser);

	अगर (goya->hw_cap_initialized & HW_CAP_MMU)
		वापस goya_parse_cb_mmu(hdev, parser);
	अन्यथा
		वापस goya_parse_cb_no_mmu(hdev, parser);
पूर्ण

व्योम goya_add_end_of_cb_packets(काष्ठा hl_device *hdev, व्योम *kernel_address,
				u32 len, u64 cq_addr, u32 cq_val, u32 msix_vec,
				bool eb)
अणु
	काष्ठा packet_msg_prot *cq_pkt;
	u32 पंचांगp;

	cq_pkt = kernel_address + len - (माप(काष्ठा packet_msg_prot) * 2);

	पंचांगp = (PACKET_MSG_PROT << GOYA_PKT_CTL_OPCODE_SHIFT) |
			(1 << GOYA_PKT_CTL_EB_SHIFT) |
			(1 << GOYA_PKT_CTL_MB_SHIFT);
	cq_pkt->ctl = cpu_to_le32(पंचांगp);
	cq_pkt->value = cpu_to_le32(cq_val);
	cq_pkt->addr = cpu_to_le64(cq_addr);

	cq_pkt++;

	पंचांगp = (PACKET_MSG_PROT << GOYA_PKT_CTL_OPCODE_SHIFT) |
			(1 << GOYA_PKT_CTL_MB_SHIFT);
	cq_pkt->ctl = cpu_to_le32(पंचांगp);
	cq_pkt->value = cpu_to_le32(msix_vec & 0x7FF);
	cq_pkt->addr = cpu_to_le64(CFG_BASE + mmPCIE_DBI_MSIX_DOORBELL_OFF);
पूर्ण

व्योम goya_update_eq_ci(काष्ठा hl_device *hdev, u32 val)
अणु
	WREG32(mmCPU_EQ_CI, val);
पूर्ण

व्योम goya_restore_phase_topology(काष्ठा hl_device *hdev)
अणु

पूर्ण

अटल व्योम goya_clear_sm_regs(काष्ठा hl_device *hdev)
अणु
	पूर्णांक i, num_of_sob_in_दीर्घs, num_of_mon_in_दीर्घs;

	num_of_sob_in_दीर्घs =
		((mmSYNC_MNGR_SOB_OBJ_1023 - mmSYNC_MNGR_SOB_OBJ_0) + 4);

	num_of_mon_in_दीर्घs =
		((mmSYNC_MNGR_MON_STATUS_255 - mmSYNC_MNGR_MON_STATUS_0) + 4);

	क्रम (i = 0 ; i < num_of_sob_in_दीर्घs ; i += 4)
		WREG32(mmSYNC_MNGR_SOB_OBJ_0 + i, 0);

	क्रम (i = 0 ; i < num_of_mon_in_दीर्घs ; i += 4)
		WREG32(mmSYNC_MNGR_MON_STATUS_0 + i, 0);

	/* Flush all WREG to prevent race */
	i = RREG32(mmSYNC_MNGR_SOB_OBJ_0);
पूर्ण

/*
 * goya_debugfs_पढ़ो32 - पढ़ो a 32bit value from a given device or a host mapped
 *                       address.
 *
 * @hdev:	poपूर्णांकer to hl_device काष्ठाure
 * @addr:	device or host mapped address
 * @val:	वापसed value
 *
 * In हाल of DDR address that is not mapped पूर्णांकo the शेष aperture that
 * the DDR bar exposes, the function will configure the iATU so that the DDR
 * bar will be positioned at a base address that allows पढ़ोing from the
 * required address. Configuring the iATU during normal operation can
 * lead to undefined behavior and thereक्रमe, should be करोne with extreme care
 *
 */
अटल पूर्णांक goya_debugfs_पढ़ो32(काष्ठा hl_device *hdev, u64 addr,
			bool user_address, u32 *val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 ddr_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr < CFG_BASE + CFG_SIZE)) अणु
		*val = RREG32(addr - CFG_BASE);

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
			(addr < SRAM_BASE_ADDR + SRAM_SIZE)) अणु

		*val = पढ़ोl(hdev->pcie_bar[SRAM_CFG_BAR_ID] +
				(addr - SRAM_BASE_ADDR));

	पूर्ण अन्यथा अगर (addr < DRAM_PHYS_BASE + hdev->asic_prop.dram_size) अणु

		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		ddr_bar_addr = goya_set_ddr_bar_base(hdev, bar_base_addr);
		अगर (ddr_bar_addr != U64_MAX) अणु
			*val = पढ़ोl(hdev->pcie_bar[DDR_BAR_ID] +
						(addr - bar_base_addr));

			ddr_bar_addr = goya_set_ddr_bar_base(hdev,
							ddr_bar_addr);
		पूर्ण
		अगर (ddr_bar_addr == U64_MAX)
			rc = -EIO;

	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*val = *(u32 *) phys_to_virt(addr - HOST_PHYS_BASE);

	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * goya_debugfs_ग_लिखो32 - ग_लिखो a 32bit value to a given device or a host mapped
 *                        address.
 *
 * @hdev:	poपूर्णांकer to hl_device काष्ठाure
 * @addr:	device or host mapped address
 * @val:	वापसed value
 *
 * In हाल of DDR address that is not mapped पूर्णांकo the शेष aperture that
 * the DDR bar exposes, the function will configure the iATU so that the DDR
 * bar will be positioned at a base address that allows writing to the
 * required address. Configuring the iATU during normal operation can
 * lead to undefined behavior and thereक्रमe, should be करोne with extreme care
 *
 */
अटल पूर्णांक goya_debugfs_ग_लिखो32(काष्ठा hl_device *hdev, u64 addr,
			bool user_address, u32 val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 ddr_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr < CFG_BASE + CFG_SIZE)) अणु
		WREG32(addr - CFG_BASE, val);

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
			(addr < SRAM_BASE_ADDR + SRAM_SIZE)) अणु

		ग_लिखोl(val, hdev->pcie_bar[SRAM_CFG_BAR_ID] +
					(addr - SRAM_BASE_ADDR));

	पूर्ण अन्यथा अगर (addr < DRAM_PHYS_BASE + hdev->asic_prop.dram_size) अणु

		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		ddr_bar_addr = goya_set_ddr_bar_base(hdev, bar_base_addr);
		अगर (ddr_bar_addr != U64_MAX) अणु
			ग_लिखोl(val, hdev->pcie_bar[DDR_BAR_ID] +
						(addr - bar_base_addr));

			ddr_bar_addr = goya_set_ddr_bar_base(hdev,
							ddr_bar_addr);
		पूर्ण
		अगर (ddr_bar_addr == U64_MAX)
			rc = -EIO;

	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*(u32 *) phys_to_virt(addr - HOST_PHYS_BASE) = val;

	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक goya_debugfs_पढ़ो64(काष्ठा hl_device *hdev, u64 addr,
			bool user_address, u64 *val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 ddr_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr <= CFG_BASE + CFG_SIZE - माप(u64))) अणु
		u32 val_l = RREG32(addr - CFG_BASE);
		u32 val_h = RREG32(addr + माप(u32) - CFG_BASE);

		*val = (((u64) val_h) << 32) | val_l;

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
			(addr <= SRAM_BASE_ADDR + SRAM_SIZE - माप(u64))) अणु

		*val = पढ़ोq(hdev->pcie_bar[SRAM_CFG_BAR_ID] +
				(addr - SRAM_BASE_ADDR));

	पूर्ण अन्यथा अगर (addr <=
		   DRAM_PHYS_BASE + hdev->asic_prop.dram_size - माप(u64)) अणु

		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		ddr_bar_addr = goya_set_ddr_bar_base(hdev, bar_base_addr);
		अगर (ddr_bar_addr != U64_MAX) अणु
			*val = पढ़ोq(hdev->pcie_bar[DDR_BAR_ID] +
						(addr - bar_base_addr));

			ddr_bar_addr = goya_set_ddr_bar_base(hdev,
							ddr_bar_addr);
		पूर्ण
		अगर (ddr_bar_addr == U64_MAX)
			rc = -EIO;

	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*val = *(u64 *) phys_to_virt(addr - HOST_PHYS_BASE);

	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक goya_debugfs_ग_लिखो64(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u64 val)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 ddr_bar_addr, host_phys_end;
	पूर्णांक rc = 0;

	host_phys_end = HOST_PHYS_BASE + HOST_PHYS_SIZE;

	अगर ((addr >= CFG_BASE) && (addr <= CFG_BASE + CFG_SIZE - माप(u64))) अणु
		WREG32(addr - CFG_BASE, lower_32_bits(val));
		WREG32(addr + माप(u32) - CFG_BASE, upper_32_bits(val));

	पूर्ण अन्यथा अगर ((addr >= SRAM_BASE_ADDR) &&
			(addr <= SRAM_BASE_ADDR + SRAM_SIZE - माप(u64))) अणु

		ग_लिखोq(val, hdev->pcie_bar[SRAM_CFG_BAR_ID] +
					(addr - SRAM_BASE_ADDR));

	पूर्ण अन्यथा अगर (addr <=
		   DRAM_PHYS_BASE + hdev->asic_prop.dram_size - माप(u64)) अणु

		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		ddr_bar_addr = goya_set_ddr_bar_base(hdev, bar_base_addr);
		अगर (ddr_bar_addr != U64_MAX) अणु
			ग_लिखोq(val, hdev->pcie_bar[DDR_BAR_ID] +
						(addr - bar_base_addr));

			ddr_bar_addr = goya_set_ddr_bar_base(hdev,
							ddr_bar_addr);
		पूर्ण
		अगर (ddr_bar_addr == U64_MAX)
			rc = -EIO;

	पूर्ण अन्यथा अगर (addr >= HOST_PHYS_BASE && addr < host_phys_end &&
			user_address && !iommu_present(&pci_bus_type)) अणु
		*(u64 *) phys_to_virt(addr - HOST_PHYS_BASE) = val;

	पूर्ण अन्यथा अणु
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक goya_debugfs_पढ़ो_dma(काष्ठा hl_device *hdev, u64 addr, u32 size,
				व्योम *blob_addr)
अणु
	dev_err(hdev->dev, "Reading via DMA is unimplemented yet\n");
	वापस -EPERM;
पूर्ण

अटल u64 goya_पढ़ो_pte(काष्ठा hl_device *hdev, u64 addr)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (hdev->hard_reset_pending)
		वापस U64_MAX;

	वापस पढ़ोq(hdev->pcie_bar[DDR_BAR_ID] +
			(addr - goya->ddr_bar_cur_addr));
पूर्ण

अटल व्योम goya_ग_लिखो_pte(काष्ठा hl_device *hdev, u64 addr, u64 val)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (hdev->hard_reset_pending)
		वापस;

	ग_लिखोq(val, hdev->pcie_bar[DDR_BAR_ID] +
			(addr - goya->ddr_bar_cur_addr));
पूर्ण

अटल स्थिर अक्षर *_goya_get_event_desc(u16 event_type)
अणु
	चयन (event_type) अणु
	हाल GOYA_ASYNC_EVENT_ID_PCIE_IF:
		वापस "PCIe_if";
	हाल GOYA_ASYNC_EVENT_ID_TPC0_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_ECC:
		वापस "TPC%d_ecc";
	हाल GOYA_ASYNC_EVENT_ID_MME_ECC:
		वापस "MME_ecc";
	हाल GOYA_ASYNC_EVENT_ID_MME_ECC_EXT:
		वापस "MME_ecc_ext";
	हाल GOYA_ASYNC_EVENT_ID_MMU_ECC:
		वापस "MMU_ecc";
	हाल GOYA_ASYNC_EVENT_ID_DMA_MACRO:
		वापस "DMA_macro";
	हाल GOYA_ASYNC_EVENT_ID_DMA_ECC:
		वापस "DMA_ecc";
	हाल GOYA_ASYNC_EVENT_ID_CPU_IF_ECC:
		वापस "CPU_if_ecc";
	हाल GOYA_ASYNC_EVENT_ID_PSOC_MEM:
		वापस "PSOC_mem";
	हाल GOYA_ASYNC_EVENT_ID_PSOC_CORESIGHT:
		वापस "PSOC_coresight";
	हाल GOYA_ASYNC_EVENT_ID_SRAM0 ... GOYA_ASYNC_EVENT_ID_SRAM29:
		वापस "SRAM%d";
	हाल GOYA_ASYNC_EVENT_ID_GIC500:
		वापस "GIC500";
	हाल GOYA_ASYNC_EVENT_ID_PLL0 ... GOYA_ASYNC_EVENT_ID_PLL6:
		वापस "PLL%d";
	हाल GOYA_ASYNC_EVENT_ID_AXI_ECC:
		वापस "AXI_ecc";
	हाल GOYA_ASYNC_EVENT_ID_L2_RAM_ECC:
		वापस "L2_ram_ecc";
	हाल GOYA_ASYNC_EVENT_ID_PSOC_GPIO_05_SW_RESET:
		वापस "PSOC_gpio_05_sw_reset";
	हाल GOYA_ASYNC_EVENT_ID_PSOC_GPIO_10_VRHOT_ICRIT:
		वापस "PSOC_gpio_10_vrhot_icrit";
	हाल GOYA_ASYNC_EVENT_ID_PCIE_DEC:
		वापस "PCIe_dec";
	हाल GOYA_ASYNC_EVENT_ID_TPC0_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_DEC:
		वापस "TPC%d_dec";
	हाल GOYA_ASYNC_EVENT_ID_MME_WACS:
		वापस "MME_wacs";
	हाल GOYA_ASYNC_EVENT_ID_MME_WACSD:
		वापस "MME_wacsd";
	हाल GOYA_ASYNC_EVENT_ID_CPU_AXI_SPLITTER:
		वापस "CPU_axi_splitter";
	हाल GOYA_ASYNC_EVENT_ID_PSOC_AXI_DEC:
		वापस "PSOC_axi_dec";
	हाल GOYA_ASYNC_EVENT_ID_PSOC:
		वापस "PSOC";
	हाल GOYA_ASYNC_EVENT_ID_TPC0_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_KRN_ERR:
		वापस "TPC%d_krn_err";
	हाल GOYA_ASYNC_EVENT_ID_TPC0_CMDQ ... GOYA_ASYNC_EVENT_ID_TPC7_CMDQ:
		वापस "TPC%d_cq";
	हाल GOYA_ASYNC_EVENT_ID_TPC0_QM ... GOYA_ASYNC_EVENT_ID_TPC7_QM:
		वापस "TPC%d_qm";
	हाल GOYA_ASYNC_EVENT_ID_MME_QM:
		वापस "MME_qm";
	हाल GOYA_ASYNC_EVENT_ID_MME_CMDQ:
		वापस "MME_cq";
	हाल GOYA_ASYNC_EVENT_ID_DMA0_QM ... GOYA_ASYNC_EVENT_ID_DMA4_QM:
		वापस "DMA%d_qm";
	हाल GOYA_ASYNC_EVENT_ID_DMA0_CH ... GOYA_ASYNC_EVENT_ID_DMA4_CH:
		वापस "DMA%d_ch";
	हाल GOYA_ASYNC_EVENT_ID_TPC0_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_BMON_SPMU:
		वापस "TPC%d_bmon_spmu";
	हाल GOYA_ASYNC_EVENT_ID_DMA_BM_CH0 ... GOYA_ASYNC_EVENT_ID_DMA_BM_CH4:
		वापस "DMA_bm_ch%d";
	हाल GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_S:
		वापस "POWER_ENV_S";
	हाल GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_E:
		वापस "POWER_ENV_E";
	हाल GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_S:
		वापस "THERMAL_ENV_S";
	हाल GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_E:
		वापस "THERMAL_ENV_E";
	हाल GOYA_ASYNC_EVENT_PKT_QUEUE_OUT_SYNC:
		वापस "QUEUE_OUT_OF_SYNC";
	शेष:
		वापस "N/A";
	पूर्ण
पूर्ण

अटल व्योम goya_get_event_desc(u16 event_type, अक्षर *desc, माप_प्रकार size)
अणु
	u8 index;

	चयन (event_type) अणु
	हाल GOYA_ASYNC_EVENT_ID_TPC0_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_ECC:
		index = (event_type - GOYA_ASYNC_EVENT_ID_TPC0_ECC) / 3;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_SRAM0 ... GOYA_ASYNC_EVENT_ID_SRAM29:
		index = event_type - GOYA_ASYNC_EVENT_ID_SRAM0;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_PLL0 ... GOYA_ASYNC_EVENT_ID_PLL6:
		index = event_type - GOYA_ASYNC_EVENT_ID_PLL0;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_TPC0_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_DEC:
		index = (event_type - GOYA_ASYNC_EVENT_ID_TPC0_DEC) / 3;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_TPC0_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_KRN_ERR:
		index = (event_type - GOYA_ASYNC_EVENT_ID_TPC0_KRN_ERR) / 10;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_TPC0_CMDQ ... GOYA_ASYNC_EVENT_ID_TPC7_CMDQ:
		index = event_type - GOYA_ASYNC_EVENT_ID_TPC0_CMDQ;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_TPC0_QM ... GOYA_ASYNC_EVENT_ID_TPC7_QM:
		index = event_type - GOYA_ASYNC_EVENT_ID_TPC0_QM;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_DMA0_QM ... GOYA_ASYNC_EVENT_ID_DMA4_QM:
		index = event_type - GOYA_ASYNC_EVENT_ID_DMA0_QM;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_DMA0_CH ... GOYA_ASYNC_EVENT_ID_DMA4_CH:
		index = event_type - GOYA_ASYNC_EVENT_ID_DMA0_CH;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_TPC0_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_BMON_SPMU:
		index = (event_type - GOYA_ASYNC_EVENT_ID_TPC0_BMON_SPMU) / 10;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_DMA_BM_CH0 ... GOYA_ASYNC_EVENT_ID_DMA_BM_CH4:
		index = event_type - GOYA_ASYNC_EVENT_ID_DMA_BM_CH0;
		snम_लिखो(desc, size, _goya_get_event_desc(event_type), index);
		अवरोध;
	हाल GOYA_ASYNC_EVENT_PKT_QUEUE_OUT_SYNC:
		snम_लिखो(desc, size, _goya_get_event_desc(event_type));
		अवरोध;
	शेष:
		snम_लिखो(desc, size, _goya_get_event_desc(event_type));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम goya_prपूर्णांक_razwi_info(काष्ठा hl_device *hdev)
अणु
	अगर (RREG32(mmDMA_MACRO_RAZWI_LBW_WT_VLD)) अणु
		dev_err_ratelimited(hdev->dev, "Illegal write to LBW\n");
		WREG32(mmDMA_MACRO_RAZWI_LBW_WT_VLD, 0);
	पूर्ण

	अगर (RREG32(mmDMA_MACRO_RAZWI_LBW_RD_VLD)) अणु
		dev_err_ratelimited(hdev->dev, "Illegal read from LBW\n");
		WREG32(mmDMA_MACRO_RAZWI_LBW_RD_VLD, 0);
	पूर्ण

	अगर (RREG32(mmDMA_MACRO_RAZWI_HBW_WT_VLD)) अणु
		dev_err_ratelimited(hdev->dev, "Illegal write to HBW\n");
		WREG32(mmDMA_MACRO_RAZWI_HBW_WT_VLD, 0);
	पूर्ण

	अगर (RREG32(mmDMA_MACRO_RAZWI_HBW_RD_VLD)) अणु
		dev_err_ratelimited(hdev->dev, "Illegal read from HBW\n");
		WREG32(mmDMA_MACRO_RAZWI_HBW_RD_VLD, 0);
	पूर्ण
पूर्ण

अटल व्योम goya_prपूर्णांक_mmu_error_info(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u64 addr;
	u32 val;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	val = RREG32(mmMMU_PAGE_ERROR_CAPTURE);
	अगर (val & MMU_PAGE_ERROR_CAPTURE_ENTRY_VALID_MASK) अणु
		addr = val & MMU_PAGE_ERROR_CAPTURE_VA_49_32_MASK;
		addr <<= 32;
		addr |= RREG32(mmMMU_PAGE_ERROR_CAPTURE_VA);

		dev_err_ratelimited(hdev->dev, "MMU page fault on va 0x%llx\n",
					addr);

		WREG32(mmMMU_PAGE_ERROR_CAPTURE, 0);
	पूर्ण
पूर्ण

अटल व्योम goya_prपूर्णांक_out_of_sync_info(काष्ठा hl_device *hdev,
					काष्ठा cpucp_pkt_sync_err *sync_err)
अणु
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[GOYA_QUEUE_ID_CPU_PQ];

	dev_err(hdev->dev, "Out of sync with FW, FW: pi=%u, ci=%u, LKD: pi=%u, ci=%u\n",
			sync_err->pi, sync_err->ci, q->pi, atomic_पढ़ो(&q->ci));
पूर्ण

अटल व्योम goya_prपूर्णांक_irq_info(काष्ठा hl_device *hdev, u16 event_type,
				bool razwi)
अणु
	अक्षर desc[20] = "";

	goya_get_event_desc(event_type, desc, माप(desc));
	dev_err_ratelimited(hdev->dev, "Received H/W interrupt %d [\"%s\"]\n",
		event_type, desc);

	अगर (razwi) अणु
		goya_prपूर्णांक_razwi_info(hdev);
		goya_prपूर्णांक_mmu_error_info(hdev);
	पूर्ण
पूर्ण

अटल पूर्णांक goya_unmask_irq_arr(काष्ठा hl_device *hdev, u32 *irq_arr,
		माप_प्रकार irq_arr_size)
अणु
	काष्ठा cpucp_unmask_irq_arr_packet *pkt;
	माप_प्रकार total_pkt_size;
	u64 result;
	पूर्णांक rc;
	पूर्णांक irq_num_entries, irq_arr_index;
	__le32 *goya_irq_arr;

	total_pkt_size = माप(काष्ठा cpucp_unmask_irq_arr_packet) +
			irq_arr_size;

	/* data should be aligned to 8 bytes in order to CPU-CP to copy it */
	total_pkt_size = (total_pkt_size + 0x7) & ~0x7;

	/* total_pkt_size is casted to u16 later on */
	अगर (total_pkt_size > अच_लघु_उच्च) अणु
		dev_err(hdev->dev, "too many elements in IRQ array\n");
		वापस -EINVAL;
	पूर्ण

	pkt = kzalloc(total_pkt_size, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	irq_num_entries = irq_arr_size / माप(irq_arr[0]);
	pkt->length = cpu_to_le32(irq_num_entries);

	/* We must perक्रमm any necessary endianness conversation on the irq
	 * array being passed to the goya hardware
	 */
	क्रम (irq_arr_index = 0, goya_irq_arr = (__le32 *) &pkt->irqs;
			irq_arr_index < irq_num_entries ; irq_arr_index++)
		goya_irq_arr[irq_arr_index] =
				cpu_to_le32(irq_arr[irq_arr_index]);

	pkt->cpucp_pkt.ctl = cpu_to_le32(CPUCP_PACKET_UNMASK_RAZWI_IRQ_ARRAY <<
						CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) pkt,
						total_pkt_size,	0, &result);

	अगर (rc)
		dev_err(hdev->dev, "failed to unmask IRQ array\n");

	kमुक्त(pkt);

	वापस rc;
पूर्ण

अटल पूर्णांक goya_soft_reset_late_init(काष्ठा hl_device *hdev)
अणु
	/*
	 * Unmask all IRQs since some could have been received
	 * during the soft reset
	 */
	वापस goya_unmask_irq_arr(hdev, goya_all_events,
					माप(goya_all_events));
पूर्ण

अटल पूर्णांक goya_unmask_irq(काष्ठा hl_device *hdev, u16 event_type)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_UNMASK_RAZWI_IRQ <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.value = cpu_to_le64(event_type);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	अगर (rc)
		dev_err(hdev->dev, "failed to unmask RAZWI IRQ %d", event_type);

	वापस rc;
पूर्ण

अटल व्योम goya_prपूर्णांक_clk_change_info(काष्ठा hl_device *hdev, u16 event_type)
अणु
	चयन (event_type) अणु
	हाल GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_S:
		hdev->clk_throttling_reason |= HL_CLK_THROTTLE_POWER;
		dev_info_ratelimited(hdev->dev,
			"Clock throttling due to power consumption\n");
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_E:
		hdev->clk_throttling_reason &= ~HL_CLK_THROTTLE_POWER;
		dev_info_ratelimited(hdev->dev,
			"Power envelop is safe, back to optimal clock\n");
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_S:
		hdev->clk_throttling_reason |= HL_CLK_THROTTLE_THERMAL;
		dev_info_ratelimited(hdev->dev,
			"Clock throttling due to overheating\n");
		अवरोध;
	हाल GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_E:
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

व्योम goya_handle_eqe(काष्ठा hl_device *hdev, काष्ठा hl_eq_entry *eq_entry)
अणु
	u32 ctl = le32_to_cpu(eq_entry->hdr.ctl);
	u16 event_type = ((ctl & EQ_CTL_EVENT_TYPE_MASK)
				>> EQ_CTL_EVENT_TYPE_SHIFT);
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	goya->events_stat[event_type]++;
	goya->events_stat_aggregate[event_type]++;

	चयन (event_type) अणु
	हाल GOYA_ASYNC_EVENT_ID_PCIE_IF:
	हाल GOYA_ASYNC_EVENT_ID_TPC0_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_ECC:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_ECC:
	हाल GOYA_ASYNC_EVENT_ID_MME_ECC:
	हाल GOYA_ASYNC_EVENT_ID_MME_ECC_EXT:
	हाल GOYA_ASYNC_EVENT_ID_MMU_ECC:
	हाल GOYA_ASYNC_EVENT_ID_DMA_MACRO:
	हाल GOYA_ASYNC_EVENT_ID_DMA_ECC:
	हाल GOYA_ASYNC_EVENT_ID_CPU_IF_ECC:
	हाल GOYA_ASYNC_EVENT_ID_PSOC_MEM:
	हाल GOYA_ASYNC_EVENT_ID_PSOC_CORESIGHT:
	हाल GOYA_ASYNC_EVENT_ID_SRAM0 ... GOYA_ASYNC_EVENT_ID_SRAM29:
	हाल GOYA_ASYNC_EVENT_ID_GIC500:
	हाल GOYA_ASYNC_EVENT_ID_PLL0 ... GOYA_ASYNC_EVENT_ID_PLL6:
	हाल GOYA_ASYNC_EVENT_ID_AXI_ECC:
	हाल GOYA_ASYNC_EVENT_ID_L2_RAM_ECC:
	हाल GOYA_ASYNC_EVENT_ID_PSOC_GPIO_05_SW_RESET:
		goya_prपूर्णांक_irq_info(hdev, event_type, false);
		अगर (hdev->hard_reset_on_fw_events)
			hl_device_reset(hdev, HL_RESET_HARD);
		अवरोध;

	हाल GOYA_ASYNC_EVENT_ID_PCIE_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC0_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_DEC:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_DEC:
	हाल GOYA_ASYNC_EVENT_ID_MME_WACS:
	हाल GOYA_ASYNC_EVENT_ID_MME_WACSD:
	हाल GOYA_ASYNC_EVENT_ID_CPU_AXI_SPLITTER:
	हाल GOYA_ASYNC_EVENT_ID_PSOC_AXI_DEC:
	हाल GOYA_ASYNC_EVENT_ID_PSOC:
	हाल GOYA_ASYNC_EVENT_ID_TPC0_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_KRN_ERR:
	हाल GOYA_ASYNC_EVENT_ID_TPC0_CMDQ ... GOYA_ASYNC_EVENT_ID_TPC7_QM:
	हाल GOYA_ASYNC_EVENT_ID_MME_QM:
	हाल GOYA_ASYNC_EVENT_ID_MME_CMDQ:
	हाल GOYA_ASYNC_EVENT_ID_DMA0_QM ... GOYA_ASYNC_EVENT_ID_DMA4_QM:
	हाल GOYA_ASYNC_EVENT_ID_DMA0_CH ... GOYA_ASYNC_EVENT_ID_DMA4_CH:
		goya_prपूर्णांक_irq_info(hdev, event_type, true);
		goya_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GOYA_ASYNC_EVENT_ID_PSOC_GPIO_10_VRHOT_ICRIT:
	हाल GOYA_ASYNC_EVENT_ID_TPC0_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC1_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC2_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC3_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC4_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC5_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC6_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_TPC7_BMON_SPMU:
	हाल GOYA_ASYNC_EVENT_ID_DMA_BM_CH0 ... GOYA_ASYNC_EVENT_ID_DMA_BM_CH4:
		goya_prपूर्णांक_irq_info(hdev, event_type, false);
		goya_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_S:
	हाल GOYA_ASYNC_EVENT_ID_FIX_POWER_ENV_E:
	हाल GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_S:
	हाल GOYA_ASYNC_EVENT_ID_FIX_THERMAL_ENV_E:
		goya_prपूर्णांक_clk_change_info(hdev, event_type);
		goya_unmask_irq(hdev, event_type);
		अवरोध;

	हाल GOYA_ASYNC_EVENT_PKT_QUEUE_OUT_SYNC:
		goya_prपूर्णांक_irq_info(hdev, event_type, false);
		goya_prपूर्णांक_out_of_sync_info(hdev, &eq_entry->pkt_sync_err);
		अगर (hdev->hard_reset_on_fw_events)
			hl_device_reset(hdev, HL_RESET_HARD);
		अन्यथा
			hl_fw_unmask_irq(hdev, event_type);
		अवरोध;

	शेष:
		dev_err(hdev->dev, "Received invalid H/W interrupt %d\n",
				event_type);
		अवरोध;
	पूर्ण
पूर्ण

व्योम *goya_get_events_stat(काष्ठा hl_device *hdev, bool aggregate, u32 *size)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (aggregate) अणु
		*size = (u32) माप(goya->events_stat_aggregate);
		वापस goya->events_stat_aggregate;
	पूर्ण

	*size = (u32) माप(goya->events_stat);
	वापस goya->events_stat;
पूर्ण

अटल पूर्णांक goya_स_रखो_device_memory(काष्ठा hl_device *hdev, u64 addr, u64 size,
				u64 val, bool is_dram)
अणु
	काष्ठा packet_lin_dma *lin_dma_pkt;
	काष्ठा hl_cs_job *job;
	u32 cb_size, ctl;
	काष्ठा hl_cb *cb;
	पूर्णांक rc, lin_dma_pkts_cnt;

	lin_dma_pkts_cnt = DIV_ROUND_UP_ULL(size, SZ_2G);
	cb_size = lin_dma_pkts_cnt * माप(काष्ठा packet_lin_dma) +
						माप(काष्ठा packet_msg_prot);
	cb = hl_cb_kernel_create(hdev, cb_size, false);
	अगर (!cb)
		वापस -ENOMEM;

	lin_dma_pkt = cb->kernel_address;

	करो अणु
		स_रखो(lin_dma_pkt, 0, माप(*lin_dma_pkt));

		ctl = ((PACKET_LIN_DMA << GOYA_PKT_CTL_OPCODE_SHIFT) |
				(1 << GOYA_PKT_LIN_DMA_CTL_MEMSET_SHIFT) |
				(1 << GOYA_PKT_LIN_DMA_CTL_WO_SHIFT) |
				(1 << GOYA_PKT_CTL_RB_SHIFT) |
				(1 << GOYA_PKT_CTL_MB_SHIFT));
		ctl |= (is_dram ? DMA_HOST_TO_DRAM : DMA_HOST_TO_SRAM) <<
				GOYA_PKT_LIN_DMA_CTL_DMA_सूची_SHIFT;
		lin_dma_pkt->ctl = cpu_to_le32(ctl);

		lin_dma_pkt->src_addr = cpu_to_le64(val);
		lin_dma_pkt->dst_addr = cpu_to_le64(addr);
		अगर (lin_dma_pkts_cnt > 1)
			lin_dma_pkt->tsize = cpu_to_le32(SZ_2G);
		अन्यथा
			lin_dma_pkt->tsize = cpu_to_le32(size);

		size -= SZ_2G;
		addr += SZ_2G;
		lin_dma_pkt++;
	पूर्ण जबतक (--lin_dma_pkts_cnt);

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
	job->hw_queue_id = GOYA_QUEUE_ID_DMA_0;
	job->patched_cb = job->user_cb;
	job->job_cb_size = job->user_cb_size;

	hl_debugfs_add_job(hdev, job);

	rc = goya_send_job_on_qman0(hdev, job);

	hl_debugfs_हटाओ_job(hdev, job);
	kमुक्त(job);
	atomic_dec(&cb->cs_cnt);

release_cb:
	hl_cb_put(cb);
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	वापस rc;
पूर्ण

पूर्णांक goya_context_चयन(काष्ठा hl_device *hdev, u32 asid)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 addr = prop->sram_base_address, sob_addr;
	u32 size = hdev->pldm ? 0x10000 : prop->sram_size;
	u64 val = 0x7777777777777777ull;
	पूर्णांक rc, dma_id;
	u32 channel_off = mmDMA_CH_1_WR_COMP_ADDR_LO -
					mmDMA_CH_0_WR_COMP_ADDR_LO;

	rc = goya_स_रखो_device_memory(hdev, addr, size, val, false);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to clear SRAM in context switch\n");
		वापस rc;
	पूर्ण

	/* we need to reset रेजिस्टरs that the user is allowed to change */
	sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1007;
	WREG32(mmDMA_CH_0_WR_COMP_ADDR_LO, lower_32_bits(sob_addr));

	क्रम (dma_id = 1 ; dma_id < NUMBER_OF_EXT_HW_QUEUES ; dma_id++) अणु
		sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1000 +
							(dma_id - 1) * 4;
		WREG32(mmDMA_CH_0_WR_COMP_ADDR_LO + channel_off * dma_id,
						lower_32_bits(sob_addr));
	पूर्ण

	WREG32(mmTPC_PLL_CLK_RLX_0, 0x200020);

	goya_clear_sm_regs(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक goya_mmu_clear_pgt_range(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u64 addr = prop->mmu_pgt_addr;
	u32 size = prop->mmu_pgt_size + MMU_DRAM_DEFAULT_PAGE_SIZE +
			MMU_CACHE_MNG_SIZE;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस 0;

	वापस goya_स_रखो_device_memory(hdev, addr, size, 0, true);
पूर्ण

अटल पूर्णांक goya_mmu_set_dram_शेष_page(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u64 addr = hdev->asic_prop.mmu_dram_शेष_page_addr;
	u32 size = MMU_DRAM_DEFAULT_PAGE_SIZE;
	u64 val = 0x9999999999999999ull;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस 0;

	वापस goya_स_रखो_device_memory(hdev, addr, size, val, true);
पूर्ण

अटल पूर्णांक goya_mmu_add_mappings_क्रम_device_cpu(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	s64 off, cpu_off;
	पूर्णांक rc;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस 0;

	क्रम (off = 0 ; off < CPU_FW_IMAGE_SIZE ; off += PAGE_SIZE_2MB) अणु
		rc = hl_mmu_map_page(hdev->kernel_ctx,
			prop->dram_base_address + off,
			prop->dram_base_address + off, PAGE_SIZE_2MB,
			(off + PAGE_SIZE_2MB) == CPU_FW_IMAGE_SIZE);
		अगर (rc) अणु
			dev_err(hdev->dev, "Map failed for address 0x%llx\n",
				prop->dram_base_address + off);
			जाओ unmap;
		पूर्ण
	पूर्ण

	अगर (!(hdev->cpu_accessible_dma_address & (PAGE_SIZE_2MB - 1))) अणु
		rc = hl_mmu_map_page(hdev->kernel_ctx,
			VA_CPU_ACCESSIBLE_MEM_ADDR,
			hdev->cpu_accessible_dma_address,
			PAGE_SIZE_2MB, true);

		अगर (rc) अणु
			dev_err(hdev->dev,
				"Map failed for CPU accessible memory\n");
			off -= PAGE_SIZE_2MB;
			जाओ unmap;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (cpu_off = 0 ; cpu_off < SZ_2M ; cpu_off += PAGE_SIZE_4KB) अणु
			rc = hl_mmu_map_page(hdev->kernel_ctx,
				VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off,
				hdev->cpu_accessible_dma_address + cpu_off,
				PAGE_SIZE_4KB, true);
			अगर (rc) अणु
				dev_err(hdev->dev,
					"Map failed for CPU accessible memory\n");
				cpu_off -= PAGE_SIZE_4KB;
				जाओ unmap_cpu;
			पूर्ण
		पूर्ण
	पूर्ण

	goya_mmu_prepare_reg(hdev, mmCPU_IF_ARUSER_OVR, HL_KERNEL_ASID_ID);
	goya_mmu_prepare_reg(hdev, mmCPU_IF_AWUSER_OVR, HL_KERNEL_ASID_ID);
	WREG32(mmCPU_IF_ARUSER_OVR_EN, 0x7FF);
	WREG32(mmCPU_IF_AWUSER_OVR_EN, 0x7FF);

	/* Make sure configuration is flushed to device */
	RREG32(mmCPU_IF_AWUSER_OVR_EN);

	goya->device_cpu_mmu_mappings_करोne = true;

	वापस 0;

unmap_cpu:
	क्रम (; cpu_off >= 0 ; cpu_off -= PAGE_SIZE_4KB)
		अगर (hl_mmu_unmap_page(hdev->kernel_ctx,
				VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off,
				PAGE_SIZE_4KB, true))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap address 0x%llx\n",
				VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off);
unmap:
	क्रम (; off >= 0 ; off -= PAGE_SIZE_2MB)
		अगर (hl_mmu_unmap_page(hdev->kernel_ctx,
				prop->dram_base_address + off, PAGE_SIZE_2MB,
				true))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap address 0x%llx\n",
				prop->dram_base_address + off);

	वापस rc;
पूर्ण

व्योम goya_mmu_हटाओ_device_cpu_mappings(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 off, cpu_off;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	अगर (!goya->device_cpu_mmu_mappings_करोne)
		वापस;

	WREG32(mmCPU_IF_ARUSER_OVR_EN, 0);
	WREG32(mmCPU_IF_AWUSER_OVR_EN, 0);

	अगर (!(hdev->cpu_accessible_dma_address & (PAGE_SIZE_2MB - 1))) अणु
		अगर (hl_mmu_unmap_page(hdev->kernel_ctx,
				VA_CPU_ACCESSIBLE_MEM_ADDR,
				PAGE_SIZE_2MB, true))
			dev_warn(hdev->dev,
				"Failed to unmap CPU accessible memory\n");
	पूर्ण अन्यथा अणु
		क्रम (cpu_off = 0 ; cpu_off < SZ_2M ; cpu_off += PAGE_SIZE_4KB)
			अगर (hl_mmu_unmap_page(hdev->kernel_ctx,
					VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off,
					PAGE_SIZE_4KB,
					(cpu_off + PAGE_SIZE_4KB) >= SZ_2M))
				dev_warn_ratelimited(hdev->dev,
					"failed to unmap address 0x%llx\n",
					VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off);
	पूर्ण

	क्रम (off = 0 ; off < CPU_FW_IMAGE_SIZE ; off += PAGE_SIZE_2MB)
		अगर (hl_mmu_unmap_page(hdev->kernel_ctx,
				prop->dram_base_address + off, PAGE_SIZE_2MB,
				(off + PAGE_SIZE_2MB) >= CPU_FW_IMAGE_SIZE))
			dev_warn_ratelimited(hdev->dev,
					"Failed to unmap address 0x%llx\n",
					prop->dram_base_address + off);

	goya->device_cpu_mmu_mappings_करोne = false;
पूर्ण

अटल व्योम goya_mmu_prepare(काष्ठा hl_device *hdev, u32 asid)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक i;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU))
		वापस;

	अगर (asid & ~MME_QM_GLBL_SECURE_PROPS_ASID_MASK) अणु
		dev_crit(hdev->dev, "asid %u is too big\n", asid);
		वापस;
	पूर्ण

	/* zero the MMBP and ASID bits and then set the ASID */
	क्रम (i = 0 ; i < GOYA_MMU_REGS_NUM ; i++)
		goya_mmu_prepare_reg(hdev, goya_mmu_regs[i], asid);
पूर्ण

अटल पूर्णांक goya_mmu_invalidate_cache(काष्ठा hl_device *hdev, bool is_hard,
					u32 flags)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 status, समयout_usec;
	पूर्णांक rc;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU) ||
		hdev->hard_reset_pending)
		वापस 0;

	/* no need in L1 only invalidation in Goya */
	अगर (!is_hard)
		वापस 0;

	अगर (hdev->pldm)
		समयout_usec = GOYA_PLDM_MMU_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = MMU_CONFIG_TIMEOUT_USEC;

	/* L0 & L1 invalidation */
	WREG32(mmSTLB_INV_ALL_START, 1);

	rc = hl_poll_समयout(
		hdev,
		mmSTLB_INV_ALL_START,
		status,
		!status,
		1000,
		समयout_usec);

	अगर (rc) अणु
		dev_err_ratelimited(hdev->dev,
					"MMU cache invalidation timeout\n");
		hl_device_reset(hdev, HL_RESET_HARD);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक goya_mmu_invalidate_cache_range(काष्ठा hl_device *hdev,
				bool is_hard, u32 asid, u64 va, u64 size)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	u32 status, समयout_usec, inv_data, pi;
	पूर्णांक rc;

	अगर (!(goya->hw_cap_initialized & HW_CAP_MMU) ||
		hdev->hard_reset_pending)
		वापस 0;

	/* no need in L1 only invalidation in Goya */
	अगर (!is_hard)
		वापस 0;

	अगर (hdev->pldm)
		समयout_usec = GOYA_PLDM_MMU_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = MMU_CONFIG_TIMEOUT_USEC;

	/*
	 * TODO: currently invalidate entire L0 & L1 as in regular hard
	 * invalidation. Need to apply invalidation of specअगरic cache lines with
	 * mask of ASID & VA & size.
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

पूर्णांक goya_send_heartbeat(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	वापस hl_fw_send_heartbeat(hdev);
पूर्ण

पूर्णांक goya_cpucp_info_get(काष्ठा hl_device *hdev)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 dram_size;
	पूर्णांक rc;

	अगर (!(goya->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	rc = hl_fw_cpucp_handshake(hdev, mmCPU_BOOT_DEV_STS0, mmCPU_BOOT_ERR0);
	अगर (rc)
		वापस rc;

	dram_size = le64_to_cpu(prop->cpucp_info.dram_size);
	अगर (dram_size) अणु
		अगर ((!is_घातer_of_2(dram_size)) ||
				(dram_size < DRAM_PHYS_DEFAULT_SIZE)) अणु
			dev_err(hdev->dev,
				"F/W reported invalid DRAM size %llu. Trying to use default size\n",
				dram_size);
			dram_size = DRAM_PHYS_DEFAULT_SIZE;
		पूर्ण

		prop->dram_size = dram_size;
		prop->dram_end_address = prop->dram_base_address + dram_size;
	पूर्ण

	अगर (!म_माप(prop->cpucp_info.card_name))
		म_नकलन(prop->cpucp_info.card_name, GOYA_DEFAULT_CARD_NAME,
				CARD_NAME_MAX_LEN);

	वापस 0;
पूर्ण

अटल व्योम goya_set_घड़ी_gating(काष्ठा hl_device *hdev)
अणु
	/* घड़ी gating not supported in Goya */
पूर्ण

अटल व्योम goya_disable_घड़ी_gating(काष्ठा hl_device *hdev)
अणु
	/* घड़ी gating not supported in Goya */
पूर्ण

अटल bool goya_is_device_idle(काष्ठा hl_device *hdev, u64 *mask_arr,
					u8 mask_len, काष्ठा seq_file *s)
अणु
	स्थिर अक्षर *fmt = "%-5d%-9s%#-14x%#-16x%#x\n";
	स्थिर अक्षर *dma_fmt = "%-5d%-9s%#-14x%#x\n";
	अचिन्हित दीर्घ *mask = (अचिन्हित दीर्घ *)mask_arr;
	u32 qm_glbl_sts0, cmdq_glbl_sts0, dma_core_sts0, tpc_cfg_sts,
		mme_arch_sts;
	bool is_idle = true, is_eng_idle;
	u64 offset;
	पूर्णांक i;

	अगर (s)
		seq_माला_दो(s, "\nDMA  is_idle  QM_GLBL_STS0  DMA_CORE_STS0\n"
				"---  -------  ------------  -------------\n");

	offset = mmDMA_QM_1_GLBL_STS0 - mmDMA_QM_0_GLBL_STS0;

	क्रम (i = 0 ; i < DMA_MAX_NUM ; i++) अणु
		qm_glbl_sts0 = RREG32(mmDMA_QM_0_GLBL_STS0 + i * offset);
		dma_core_sts0 = RREG32(mmDMA_CH_0_STS0 + i * offset);
		is_eng_idle = IS_DMA_QM_IDLE(qm_glbl_sts0) &&
				IS_DMA_IDLE(dma_core_sts0);
		is_idle &= is_eng_idle;

		अगर (mask && !is_eng_idle)
			set_bit(GOYA_ENGINE_ID_DMA_0 + i, mask);
		अगर (s)
			seq_म_लिखो(s, dma_fmt, i, is_eng_idle ? "Y" : "N",
					qm_glbl_sts0, dma_core_sts0);
	पूर्ण

	अगर (s)
		seq_माला_दो(s,
			"\nTPC  is_idle  QM_GLBL_STS0  CMDQ_GLBL_STS0  CFG_STATUS\n"
			"---  -------  ------------  --------------  ----------\n");

	offset = mmTPC1_QM_GLBL_STS0 - mmTPC0_QM_GLBL_STS0;

	क्रम (i = 0 ; i < TPC_MAX_NUM ; i++) अणु
		qm_glbl_sts0 = RREG32(mmTPC0_QM_GLBL_STS0 + i * offset);
		cmdq_glbl_sts0 = RREG32(mmTPC0_CMDQ_GLBL_STS0 + i * offset);
		tpc_cfg_sts = RREG32(mmTPC0_CFG_STATUS + i * offset);
		is_eng_idle = IS_TPC_QM_IDLE(qm_glbl_sts0) &&
				IS_TPC_CMDQ_IDLE(cmdq_glbl_sts0) &&
				IS_TPC_IDLE(tpc_cfg_sts);
		is_idle &= is_eng_idle;

		अगर (mask && !is_eng_idle)
			set_bit(GOYA_ENGINE_ID_TPC_0 + i, mask);
		अगर (s)
			seq_म_लिखो(s, fmt, i, is_eng_idle ? "Y" : "N",
				qm_glbl_sts0, cmdq_glbl_sts0, tpc_cfg_sts);
	पूर्ण

	अगर (s)
		seq_माला_दो(s,
			"\nMME  is_idle  QM_GLBL_STS0  CMDQ_GLBL_STS0  ARCH_STATUS\n"
			"---  -------  ------------  --------------  -----------\n");

	qm_glbl_sts0 = RREG32(mmMME_QM_GLBL_STS0);
	cmdq_glbl_sts0 = RREG32(mmMME_CMDQ_GLBL_STS0);
	mme_arch_sts = RREG32(mmMME_ARCH_STATUS);
	is_eng_idle = IS_MME_QM_IDLE(qm_glbl_sts0) &&
			IS_MME_CMDQ_IDLE(cmdq_glbl_sts0) &&
			IS_MME_IDLE(mme_arch_sts);
	is_idle &= is_eng_idle;

	अगर (mask && !is_eng_idle)
		set_bit(GOYA_ENGINE_ID_MME_0, mask);
	अगर (s) अणु
		seq_म_लिखो(s, fmt, 0, is_eng_idle ? "Y" : "N", qm_glbl_sts0,
				cmdq_glbl_sts0, mme_arch_sts);
		seq_माला_दो(s, "\n");
	पूर्ण

	वापस is_idle;
पूर्ण

अटल व्योम goya_hw_queues_lock(काष्ठा hl_device *hdev)
	__acquires(&goya->hw_queues_lock)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	spin_lock(&goya->hw_queues_lock);
पूर्ण

अटल व्योम goya_hw_queues_unlock(काष्ठा hl_device *hdev)
	__releases(&goya->hw_queues_lock)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	spin_unlock(&goya->hw_queues_lock);
पूर्ण

अटल u32 goya_get_pci_id(काष्ठा hl_device *hdev)
अणु
	वापस hdev->pdev->device;
पूर्ण

अटल पूर्णांक goya_get_eeprom_data(काष्ठा hl_device *hdev, व्योम *data,
				माप_प्रकार max_size)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	अगर (!(goya->hw_cap_initialized & HW_CAP_CPU_Q))
		वापस 0;

	वापस hl_fw_get_eeprom_data(hdev, data, max_size);
पूर्ण

अटल पूर्णांक goya_ctx_init(काष्ठा hl_ctx *ctx)
अणु
	अगर (ctx->asid != HL_KERNEL_ASID_ID)
		goya_mmu_prepare(ctx->hdev, ctx->asid);

	वापस 0;
पूर्ण

u32 goya_get_queue_id_क्रम_cq(काष्ठा hl_device *hdev, u32 cq_idx)
अणु
	वापस cq_idx;
पूर्ण

अटल u32 goya_get_संकेत_cb_size(काष्ठा hl_device *hdev)
अणु
	वापस 0;
पूर्ण

अटल u32 goya_get_रुको_cb_size(काष्ठा hl_device *hdev)
अणु
	वापस 0;
पूर्ण

अटल u32 goya_gen_संकेत_cb(काष्ठा hl_device *hdev, व्योम *data, u16 sob_id,
				u32 size, bool eb)
अणु
	वापस 0;
पूर्ण

अटल u32 goya_gen_रुको_cb(काष्ठा hl_device *hdev,
		काष्ठा hl_gen_रुको_properties *prop)
अणु
	वापस 0;
पूर्ण

अटल व्योम goya_reset_sob(काष्ठा hl_device *hdev, व्योम *data)
अणु

पूर्ण

अटल व्योम goya_reset_sob_group(काष्ठा hl_device *hdev, u16 sob_group)
अणु

पूर्ण

अटल व्योम goya_set_dma_mask_from_fw(काष्ठा hl_device *hdev)
अणु
	अगर (RREG32(mmPSOC_GLOBAL_CONF_NON_RST_FLOPS_0) ==
							HL_POWER9_HOST_MAGIC) अणु
		dev_dbg(hdev->dev, "Working in 64-bit DMA mode\n");
		hdev->घातer9_64bit_dma_enable = 1;
		hdev->dma_mask = 64;
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev, "Working in 48-bit DMA mode\n");
		hdev->घातer9_64bit_dma_enable = 0;
		hdev->dma_mask = 48;
	पूर्ण
पूर्ण

u64 goya_get_device_समय(काष्ठा hl_device *hdev)
अणु
	u64 device_समय = ((u64) RREG32(mmPSOC_TIMESTAMP_CNTCVU)) << 32;

	वापस device_समय | RREG32(mmPSOC_TIMESTAMP_CNTCVL);
पूर्ण

अटल व्योम goya_collective_रुको_init_cs(काष्ठा hl_cs *cs)
अणु

पूर्ण

अटल पूर्णांक goya_collective_रुको_create_jobs(काष्ठा hl_device *hdev,
		काष्ठा hl_ctx *ctx, काष्ठा hl_cs *cs, u32 रुको_queue_id,
		u32 collective_engine_id)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम goya_ctx_fini(काष्ठा hl_ctx *ctx)
अणु

पूर्ण

अटल पूर्णांक goya_get_hw_block_id(काष्ठा hl_device *hdev, u64 block_addr,
			u32 *block_size, u32 *block_id)
अणु
	वापस -EPERM;
पूर्ण

अटल पूर्णांक goya_block_mmap(काष्ठा hl_device *hdev, काष्ठा vm_area_काष्ठा *vma,
				u32 block_id, u32 block_size)
अणु
	वापस -EPERM;
पूर्ण

अटल व्योम goya_enable_events_from_fw(काष्ठा hl_device *hdev)
अणु
	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
			GOYA_ASYNC_EVENT_ID_INTS_REGISTER);
पूर्ण

अटल पूर्णांक goya_map_pll_idx_to_fw_idx(u32 pll_idx)
अणु
	चयन (pll_idx) अणु
	हाल HL_GOYA_CPU_PLL: वापस CPU_PLL;
	हाल HL_GOYA_PCI_PLL: वापस PCI_PLL;
	हाल HL_GOYA_MME_PLL: वापस MME_PLL;
	हाल HL_GOYA_TPC_PLL: वापस TPC_PLL;
	हाल HL_GOYA_IC_PLL: वापस IC_PLL;
	हाल HL_GOYA_MC_PLL: वापस MC_PLL;
	हाल HL_GOYA_EMMC_PLL: वापस EMMC_PLL;
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hl_asic_funcs goya_funcs = अणु
	.early_init = goya_early_init,
	.early_fini = goya_early_fini,
	.late_init = goya_late_init,
	.late_fini = goya_late_fini,
	.sw_init = goya_sw_init,
	.sw_fini = goya_sw_fini,
	.hw_init = goya_hw_init,
	.hw_fini = goya_hw_fini,
	.halt_engines = goya_halt_engines,
	.suspend = goya_suspend,
	.resume = goya_resume,
	.cb_mmap = goya_cb_mmap,
	.ring_करोorbell = goya_ring_करोorbell,
	.pqe_ग_लिखो = goya_pqe_ग_लिखो,
	.asic_dma_alloc_coherent = goya_dma_alloc_coherent,
	.asic_dma_मुक्त_coherent = goya_dma_मुक्त_coherent,
	.scrub_device_mem = goya_scrub_device_mem,
	.get_पूर्णांक_queue_base = goya_get_पूर्णांक_queue_base,
	.test_queues = goya_test_queues,
	.asic_dma_pool_zalloc = goya_dma_pool_zalloc,
	.asic_dma_pool_मुक्त = goya_dma_pool_मुक्त,
	.cpu_accessible_dma_pool_alloc = goya_cpu_accessible_dma_pool_alloc,
	.cpu_accessible_dma_pool_मुक्त = goya_cpu_accessible_dma_pool_मुक्त,
	.hl_dma_unmap_sg = goya_dma_unmap_sg,
	.cs_parser = goya_cs_parser,
	.asic_dma_map_sg = goya_dma_map_sg,
	.get_dma_desc_list_size = goya_get_dma_desc_list_size,
	.add_end_of_cb_packets = goya_add_end_of_cb_packets,
	.update_eq_ci = goya_update_eq_ci,
	.context_चयन = goya_context_चयन,
	.restore_phase_topology = goya_restore_phase_topology,
	.debugfs_पढ़ो32 = goya_debugfs_पढ़ो32,
	.debugfs_ग_लिखो32 = goya_debugfs_ग_लिखो32,
	.debugfs_पढ़ो64 = goya_debugfs_पढ़ो64,
	.debugfs_ग_लिखो64 = goya_debugfs_ग_लिखो64,
	.debugfs_पढ़ो_dma = goya_debugfs_पढ़ो_dma,
	.add_device_attr = goya_add_device_attr,
	.handle_eqe = goya_handle_eqe,
	.set_pll_profile = goya_set_pll_profile,
	.get_events_stat = goya_get_events_stat,
	.पढ़ो_pte = goya_पढ़ो_pte,
	.ग_लिखो_pte = goya_ग_लिखो_pte,
	.mmu_invalidate_cache = goya_mmu_invalidate_cache,
	.mmu_invalidate_cache_range = goya_mmu_invalidate_cache_range,
	.send_heartbeat = goya_send_heartbeat,
	.set_घड़ी_gating = goya_set_घड़ी_gating,
	.disable_घड़ी_gating = goya_disable_घड़ी_gating,
	.debug_coresight = goya_debug_coresight,
	.is_device_idle = goya_is_device_idle,
	.soft_reset_late_init = goya_soft_reset_late_init,
	.hw_queues_lock = goya_hw_queues_lock,
	.hw_queues_unlock = goya_hw_queues_unlock,
	.get_pci_id = goya_get_pci_id,
	.get_eeprom_data = goya_get_eeprom_data,
	.send_cpu_message = goya_send_cpu_message,
	.pci_bars_map = goya_pci_bars_map,
	.init_iatu = goya_init_iatu,
	.rreg = hl_rreg,
	.wreg = hl_wreg,
	.halt_coresight = goya_halt_coresight,
	.ctx_init = goya_ctx_init,
	.ctx_fini = goya_ctx_fini,
	.get_clk_rate = goya_get_clk_rate,
	.get_queue_id_क्रम_cq = goya_get_queue_id_क्रम_cq,
	.पढ़ो_device_fw_version = goya_पढ़ो_device_fw_version,
	.load_firmware_to_device = goya_load_firmware_to_device,
	.load_boot_fit_to_device = goya_load_boot_fit_to_device,
	.get_संकेत_cb_size = goya_get_संकेत_cb_size,
	.get_रुको_cb_size = goya_get_रुको_cb_size,
	.gen_संकेत_cb = goya_gen_संकेत_cb,
	.gen_रुको_cb = goya_gen_रुको_cb,
	.reset_sob = goya_reset_sob,
	.reset_sob_group = goya_reset_sob_group,
	.set_dma_mask_from_fw = goya_set_dma_mask_from_fw,
	.get_device_समय = goya_get_device_समय,
	.collective_रुको_init_cs = goya_collective_रुको_init_cs,
	.collective_रुको_create_jobs = goya_collective_रुको_create_jobs,
	.scramble_addr = hl_mmu_scramble_addr,
	.descramble_addr = hl_mmu_descramble_addr,
	.ack_protection_bits_errors = goya_ack_protection_bits_errors,
	.get_hw_block_id = goya_get_hw_block_id,
	.hw_block_mmap = goya_block_mmap,
	.enable_events_from_fw = goya_enable_events_from_fw,
	.map_pll_idx_to_fw_idx = goya_map_pll_idx_to_fw_idx
पूर्ण;

/*
 * goya_set_asic_funcs - set Goya function poपूर्णांकers
 *
 * @*hdev: poपूर्णांकer to hl_device काष्ठाure
 *
 */
व्योम goya_set_asic_funcs(काष्ठा hl_device *hdev)
अणु
	hdev->asic_funcs = &goya_funcs;
पूर्ण
