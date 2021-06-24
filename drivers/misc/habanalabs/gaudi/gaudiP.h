<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2019-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GAUDIP_H_
#घोषणा GAUDIP_H_

#समावेश <uapi/misc/habanaद_असल.h>
#समावेश "../common/habanalabs.h"
#समावेश "../include/common/hl_boot_if.h"
#समावेश "../include/gaudi/gaudi_packets.h"
#समावेश "../include/gaudi/gaudi.h"
#समावेश "../include/gaudi/gaudi_async_events.h"
#समावेश "../include/gaudi/gaudi_fw_if.h"

#घोषणा NUMBER_OF_EXT_HW_QUEUES		8
#घोषणा NUMBER_OF_CMPLT_QUEUES		NUMBER_OF_EXT_HW_QUEUES
#घोषणा NUMBER_OF_CPU_HW_QUEUES		1
#घोषणा NUMBER_OF_INT_HW_QUEUES		100
#घोषणा NUMBER_OF_HW_QUEUES		(NUMBER_OF_EXT_HW_QUEUES + \
					NUMBER_OF_CPU_HW_QUEUES + \
					NUMBER_OF_INT_HW_QUEUES)

/* 10 NIC QMANs, DMA5 QMAN, TPC7 QMAN */
#घोषणा NUMBER_OF_COLLECTIVE_QUEUES	12
#घोषणा NUMBER_OF_SOBS_IN_GRP		11

/*
 * Number of MSI पूर्णांकerrupts IDS:
 * Each completion queue has 1 ID
 * The event queue has 1 ID
 */
#घोषणा NUMBER_OF_INTERRUPTS		(NUMBER_OF_CMPLT_QUEUES + \
						NUMBER_OF_CPU_HW_QUEUES)

#अगर (NUMBER_OF_INTERRUPTS > GAUDI_MSI_ENTRIES)
#त्रुटि "Number of MSI interrupts must be smaller or equal to GAUDI_MSI_ENTRIES"
#पूर्ण_अगर

#घोषणा CORESIGHT_TIMEOUT_USEC		100000		/* 100 ms */

#घोषणा GAUDI_MAX_CLK_FREQ		2200000000ull	/* 2200 MHz */

#घोषणा MAX_POWER_DEFAULT_PCI		200000		/* 200W */
#घोषणा MAX_POWER_DEFAULT_PMC		350000		/* 350W */

#घोषणा DC_POWER_DEFAULT_PCI		60000		/* 60W */
#घोषणा DC_POWER_DEFAULT_PMC		60000		/* 60W */

#घोषणा GAUDI_CPU_TIMEOUT_USEC		30000000	/* 30s */

#घोषणा TPC_ENABLED_MASK		0xFF

#घोषणा GAUDI_HBM_SIZE_32GB		0x800000000ull
#घोषणा GAUDI_HBM_DEVICES		4
#घोषणा GAUDI_HBM_CHANNELS		8
#घोषणा GAUDI_HBM_CFG_BASE		(mmHBM0_BASE - CFG_BASE)
#घोषणा GAUDI_HBM_CFG_OFFSET		(mmHBM1_BASE - mmHBM0_BASE)

#घोषणा DMA_MAX_TRANSFER_SIZE		U32_MAX

#घोषणा GAUDI_DEFAULT_CARD_NAME		"HL2000"

#घोषणा GAUDI_MAX_PENDING_CS		SZ_16K

#अगर !IS_MAX_PENDING_CS_VALID(GAUDI_MAX_PENDING_CS)
#त्रुटि "GAUDI_MAX_PENDING_CS must be power of 2 and greater than 1"
#पूर्ण_अगर

#घोषणा PCI_DMA_NUMBER_OF_CHNLS		2
#घोषणा HBM_DMA_NUMBER_OF_CHNLS		6
#घोषणा DMA_NUMBER_OF_CHNLS		(PCI_DMA_NUMBER_OF_CHNLS + \
						HBM_DMA_NUMBER_OF_CHNLS)

#घोषणा MME_NUMBER_OF_SLAVE_ENGINES	2
#घोषणा MME_NUMBER_OF_ENGINES		(MME_NUMBER_OF_MASTER_ENGINES + \
					MME_NUMBER_OF_SLAVE_ENGINES)
#घोषणा MME_NUMBER_OF_QMANS		(MME_NUMBER_OF_MASTER_ENGINES * \
					QMAN_STREAMS)

#घोषणा QMAN_STREAMS		4

#घोषणा DMA_QMAN_OFFSET		(mmDMA1_QM_BASE - mmDMA0_QM_BASE)
#घोषणा TPC_QMAN_OFFSET		(mmTPC1_QM_BASE - mmTPC0_QM_BASE)
#घोषणा MME_QMAN_OFFSET		(mmMME1_QM_BASE - mmMME0_QM_BASE)
#घोषणा NIC_MACRO_QMAN_OFFSET	(mmNIC1_QM0_BASE - mmNIC0_QM0_BASE)
#घोषणा NIC_ENGINE_QMAN_OFFSET	(mmNIC0_QM1_BASE - mmNIC0_QM0_BASE)

#घोषणा TPC_CFG_OFFSET		(mmTPC1_CFG_BASE - mmTPC0_CFG_BASE)

#घोषणा DMA_CORE_OFFSET		(mmDMA1_CORE_BASE - mmDMA0_CORE_BASE)

#घोषणा QMAN_LDMA_SRC_OFFSET	(mmDMA0_CORE_SRC_BASE_LO - mmDMA0_CORE_CFG_0)
#घोषणा QMAN_LDMA_DST_OFFSET	(mmDMA0_CORE_DST_BASE_LO - mmDMA0_CORE_CFG_0)
#घोषणा QMAN_LDMA_SIZE_OFFSET	(mmDMA0_CORE_DST_TSIZE_0 - mmDMA0_CORE_CFG_0)

#घोषणा QMAN_CPDMA_SRC_OFFSET	(mmDMA0_QM_CQ_PTR_LO_4 - mmDMA0_CORE_CFG_0)
#घोषणा QMAN_CPDMA_DST_OFFSET	(mmDMA0_CORE_DST_BASE_LO - mmDMA0_CORE_CFG_0)
#घोषणा QMAN_CPDMA_SIZE_OFFSET	(mmDMA0_QM_CQ_TSIZE_4 - mmDMA0_CORE_CFG_0)

#घोषणा SIF_RTR_CTRL_OFFSET	(mmSIF_RTR_CTRL_1_BASE - mmSIF_RTR_CTRL_0_BASE)

#घोषणा NIF_RTR_CTRL_OFFSET	(mmNIF_RTR_CTRL_1_BASE - mmNIF_RTR_CTRL_0_BASE)

#घोषणा MME_ACC_OFFSET		(mmMME1_ACC_BASE - mmMME0_ACC_BASE)
#घोषणा SRAM_BANK_OFFSET	(mmSRAM_Y0_X1_RTR_BASE - mmSRAM_Y0_X0_RTR_BASE)

#घोषणा NUM_OF_SOB_IN_BLOCK		\
	(((mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_2047 - \
	mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_SOB_OBJ_0) + 4) >> 2)

#घोषणा NUM_OF_MONITORS_IN_BLOCK	\
	(((mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_STATUS_511 - \
	mmSYNC_MNGR_E_N_SYNC_MNGR_OBJS_MON_STATUS_0) + 4) >> 2)


/* DRAM Memory Map */

#घोषणा CPU_FW_IMAGE_SIZE	0x10000000	/* 256MB */
#घोषणा MMU_PAGE_TABLES_SIZE	0x0BF00000	/* 191MB */
#घोषणा MMU_CACHE_MNG_SIZE	0x00100000	/* 1MB */
#घोषणा RESERVED		0x04000000	/* 64MB */

#घोषणा CPU_FW_IMAGE_ADDR	DRAM_PHYS_BASE
#घोषणा MMU_PAGE_TABLES_ADDR	(CPU_FW_IMAGE_ADDR + CPU_FW_IMAGE_SIZE)
#घोषणा MMU_CACHE_MNG_ADDR	(MMU_PAGE_TABLES_ADDR + MMU_PAGE_TABLES_SIZE)

#घोषणा DRAM_DRIVER_END_ADDR	(MMU_CACHE_MNG_ADDR + MMU_CACHE_MNG_SIZE +\
								RESERVED)

#घोषणा DRAM_BASE_ADDR_USER	0x20000000

#अगर (DRAM_DRIVER_END_ADDR > DRAM_BASE_ADDR_USER)
#त्रुटि "Driver must reserve no more than 512MB"
#पूर्ण_अगर

/* Internal QMANs PQ sizes */

#घोषणा MME_QMAN_LENGTH			1024
#घोषणा MME_QMAN_SIZE_IN_BYTES		(MME_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE)

#घोषणा HBM_DMA_QMAN_LENGTH		1024
#घोषणा HBM_DMA_QMAN_SIZE_IN_BYTES	\
				(HBM_DMA_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE)

#घोषणा TPC_QMAN_LENGTH			1024
#घोषणा TPC_QMAN_SIZE_IN_BYTES		(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE)

#घोषणा NIC_QMAN_LENGTH			1024
#घोषणा NIC_QMAN_SIZE_IN_BYTES		(NIC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE)


#घोषणा SRAM_USER_BASE_OFFSET  GAUDI_DRIVER_SRAM_RESERVED_SIZE_FROM_START

/* Virtual address space */
#घोषणा VA_HOST_SPACE_START	0x1000000000000ull	/* 256TB */
#घोषणा VA_HOST_SPACE_END	0x3FF8000000000ull	/* 1PB - 512GB */
#घोषणा VA_HOST_SPACE_SIZE	(VA_HOST_SPACE_END - \
					VA_HOST_SPACE_START) /* 767TB */
#घोषणा HOST_SPACE_INTERNAL_CB_SZ	SZ_2M

#घोषणा HW_CAP_PLL		BIT(0)
#घोषणा HW_CAP_HBM		BIT(1)
#घोषणा HW_CAP_MMU		BIT(2)
#घोषणा HW_CAP_MME		BIT(3)
#घोषणा HW_CAP_CPU		BIT(4)
#घोषणा HW_CAP_PCI_DMA		BIT(5)
#घोषणा HW_CAP_MSI		BIT(6)
#घोषणा HW_CAP_CPU_Q		BIT(7)
#घोषणा HW_CAP_HBM_DMA		BIT(8)
#घोषणा HW_CAP_CLK_GATE		BIT(9)
#घोषणा HW_CAP_SRAM_SCRAMBLER	BIT(10)
#घोषणा HW_CAP_HBM_SCRAMBLER	BIT(11)

#घोषणा HW_CAP_NIC0		BIT(14)
#घोषणा HW_CAP_NIC1		BIT(15)
#घोषणा HW_CAP_NIC2		BIT(16)
#घोषणा HW_CAP_NIC3		BIT(17)
#घोषणा HW_CAP_NIC4		BIT(18)
#घोषणा HW_CAP_NIC5		BIT(19)
#घोषणा HW_CAP_NIC6		BIT(20)
#घोषणा HW_CAP_NIC7		BIT(21)
#घोषणा HW_CAP_NIC8		BIT(22)
#घोषणा HW_CAP_NIC9		BIT(23)
#घोषणा HW_CAP_NIC_MASK		GENMASK(23, 14)
#घोषणा HW_CAP_NIC_SHIFT	14

#घोषणा HW_CAP_TPC0		BIT(24)
#घोषणा HW_CAP_TPC1		BIT(25)
#घोषणा HW_CAP_TPC2		BIT(26)
#घोषणा HW_CAP_TPC3		BIT(27)
#घोषणा HW_CAP_TPC4		BIT(28)
#घोषणा HW_CAP_TPC5		BIT(29)
#घोषणा HW_CAP_TPC6		BIT(30)
#घोषणा HW_CAP_TPC7		BIT(31)
#घोषणा HW_CAP_TPC_MASK		GENMASK(31, 24)
#घोषणा HW_CAP_TPC_SHIFT	24

#घोषणा GAUDI_CPU_PCI_MSB_ADDR(addr)	(((addr) & GENMASK_ULL(49, 39)) >> 39)
#घोषणा GAUDI_PCI_TO_CPU_ADDR(addr)			\
	करो अणु						\
		(addr) &= ~GENMASK_ULL(49, 39);		\
		(addr) |= BIT_ULL(39);			\
	पूर्ण जबतक (0)
#घोषणा GAUDI_CPU_TO_PCI_ADDR(addr, extension)		\
	करो अणु						\
		(addr) &= ~GENMASK_ULL(49, 39);		\
		(addr) |= (u64) (extension) << 39;	\
	पूर्ण जबतक (0)

क्रमागत gaudi_dma_channels अणु
	GAUDI_PCI_DMA_1,
	GAUDI_PCI_DMA_2,
	GAUDI_HBM_DMA_1,
	GAUDI_HBM_DMA_2,
	GAUDI_HBM_DMA_3,
	GAUDI_HBM_DMA_4,
	GAUDI_HBM_DMA_5,
	GAUDI_HBM_DMA_6,
	GAUDI_DMA_MAX
पूर्ण;

क्रमागत gaudi_tpc_mask अणु
	GAUDI_TPC_MASK_TPC0 = 0x01,
	GAUDI_TPC_MASK_TPC1 = 0x02,
	GAUDI_TPC_MASK_TPC2 = 0x04,
	GAUDI_TPC_MASK_TPC3 = 0x08,
	GAUDI_TPC_MASK_TPC4 = 0x10,
	GAUDI_TPC_MASK_TPC5 = 0x20,
	GAUDI_TPC_MASK_TPC6 = 0x40,
	GAUDI_TPC_MASK_TPC7 = 0x80,
	GAUDI_TPC_MASK_ALL = 0xFF
पूर्ण;

क्रमागत gaudi_nic_mask अणु
	GAUDI_NIC_MASK_NIC0 = 0x01,
	GAUDI_NIC_MASK_NIC1 = 0x02,
	GAUDI_NIC_MASK_NIC2 = 0x04,
	GAUDI_NIC_MASK_NIC3 = 0x08,
	GAUDI_NIC_MASK_NIC4 = 0x10,
	GAUDI_NIC_MASK_NIC5 = 0x20,
	GAUDI_NIC_MASK_NIC6 = 0x40,
	GAUDI_NIC_MASK_NIC7 = 0x80,
	GAUDI_NIC_MASK_NIC8 = 0x100,
	GAUDI_NIC_MASK_NIC9 = 0x200,
	GAUDI_NIC_MASK_ALL = 0x3FF
पूर्ण;

/*
 * काष्ठा gaudi_hw_sob_group - H/W SOB group info.
 * @hdev: habanaद_असल device काष्ठाure.
 * @kref: refcount of this SOB group. group will reset once refcount is zero.
 * @base_sob_id: base sob id of this SOB group.
 * @queue_id: id of the queue that रुकोs on this sob group
 */
काष्ठा gaudi_hw_sob_group अणु
	काष्ठा hl_device	*hdev;
	काष्ठा kref		kref;
	u32			base_sob_id;
	u32			queue_id;
पूर्ण;

#घोषणा NUM_SOB_GROUPS (HL_RSVD_SOBS * QMAN_STREAMS)
/**
 * काष्ठा gaudi_collective_properties -
 *     holds all SOB groups and queues info reserved क्रम the collective
 * @hw_sob_group: H/W SOB groups.
 * @next_sob_group_val: the next value to use क्रम the currently used SOB group.
 * @curr_sob_group_idx: the index of the currently used SOB group.
 * @mstr_sob_mask: pre-defined masks क्रम collective master monitors
 */
काष्ठा gaudi_collective_properties अणु
	काष्ठा gaudi_hw_sob_group hw_sob_group[NUM_SOB_GROUPS];
	u16			next_sob_group_val[QMAN_STREAMS];
	u8			curr_sob_group_idx[QMAN_STREAMS];
	u8			mstr_sob_mask[HL_COLLECTIVE_RSVD_MSTR_MONS];
पूर्ण;

/**
 * काष्ठा gaudi_पूर्णांकernal_qman_info - Internal QMAN inक्रमmation.
 * @pq_kernel_addr: Kernel address of the PQ memory area in the host.
 * @pq_dma_addr: DMA address of the PQ memory area in the host.
 * @pq_size: Size of allocated host memory क्रम PQ.
 */
काष्ठा gaudi_पूर्णांकernal_qman_info अणु
	व्योम		*pq_kernel_addr;
	dma_addr_t	pq_dma_addr;
	माप_प्रकार		pq_size;
पूर्ण;

/**
 * काष्ठा gaudi_device - ASIC specअगरic manage काष्ठाure.
 * @cpucp_info_get: get inक्रमmation on device from CPU-CP
 * @hw_queues_lock: protects the H/W queues from concurrent access.
 * @clk_gate_mutex: protects code areas that require घड़ी gating to be disabled
 *                  temporarily
 * @पूर्णांकernal_qmans: Internal QMANs inक्रमmation. The array size is larger than
 *                  the actual number of पूर्णांकernal queues because they are not in
 *                  consecutive order.
 * @hbm_bar_cur_addr: current address of HBM PCI bar.
 * @max_freq_value: current max clk frequency.
 * @events: array that holds all event id's
 * @events_stat: array that holds histogram of all received events.
 * @events_stat_aggregate: same as events_stat but करोesn't get cleared on reset
 * @hw_cap_initialized: This field contains a bit per H/W engine. When that
 *                      engine is initialized, that bit is set by the driver to
 *                      संकेत we can use this engine in later code paths.
 *                      Each bit is cleared upon reset of its corresponding H/W
 *                      engine.
 * @multi_msi_mode: whether we are working in multi MSI single MSI mode.
 *                  Multi MSI is possible only with IOMMU enabled.
 * @mmu_cache_inv_pi: PI क्रम MMU cache invalidation flow. The H/W expects an
 *                    8-bit value so use u8.
 */
काष्ठा gaudi_device अणु
	पूर्णांक (*cpucp_info_get)(काष्ठा hl_device *hdev);

	/* TODO: हटाओ hw_queues_lock after moving to scheduler code */
	spinlock_t			hw_queues_lock;
	काष्ठा mutex			clk_gate_mutex;

	काष्ठा gaudi_पूर्णांकernal_qman_info	पूर्णांकernal_qmans[GAUDI_QUEUE_ID_SIZE];

	काष्ठा gaudi_collective_properties collective_props;

	u64				hbm_bar_cur_addr;
	u64				max_freq_value;

	u32				events[GAUDI_EVENT_SIZE];
	u32				events_stat[GAUDI_EVENT_SIZE];
	u32				events_stat_aggregate[GAUDI_EVENT_SIZE];
	u32				hw_cap_initialized;
	u8				multi_msi_mode;
	u8				mmu_cache_inv_pi;
पूर्ण;

व्योम gaudi_init_security(काष्ठा hl_device *hdev);
व्योम gaudi_ack_protection_bits_errors(काष्ठा hl_device *hdev);
व्योम gaudi_add_device_attr(काष्ठा hl_device *hdev,
			काष्ठा attribute_group *dev_attr_grp);
व्योम gaudi_set_pll_profile(काष्ठा hl_device *hdev, क्रमागत hl_pll_frequency freq);
पूर्णांक gaudi_debug_coresight(काष्ठा hl_device *hdev, व्योम *data);
व्योम gaudi_halt_coresight(काष्ठा hl_device *hdev);
पूर्णांक gaudi_get_clk_rate(काष्ठा hl_device *hdev, u32 *cur_clk, u32 *max_clk);
व्योम gaudi_mmu_prepare_reg(काष्ठा hl_device *hdev, u64 reg, u32 asid);

#पूर्ण_अगर /* GAUDIP_H_ */
