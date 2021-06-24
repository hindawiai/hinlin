<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GOYAP_H_
#घोषणा GOYAP_H_

#समावेश <uapi/misc/habanaद_असल.h>
#समावेश "../common/habanalabs.h"
#समावेश "../include/common/hl_boot_if.h"
#समावेश "../include/goya/goya_packets.h"
#समावेश "../include/goya/goya.h"
#समावेश "../include/goya/goya_async_events.h"
#समावेश "../include/goya/goya_fw_if.h"

#घोषणा NUMBER_OF_CMPLT_QUEUES		5
#घोषणा NUMBER_OF_EXT_HW_QUEUES		5
#घोषणा NUMBER_OF_CPU_HW_QUEUES		1
#घोषणा NUMBER_OF_INT_HW_QUEUES		9
#घोषणा NUMBER_OF_HW_QUEUES		(NUMBER_OF_EXT_HW_QUEUES + \
					NUMBER_OF_CPU_HW_QUEUES + \
					NUMBER_OF_INT_HW_QUEUES)

/*
 * Number of MSIX पूर्णांकerrupts IDS:
 * Each completion queue has 1 ID
 * The event queue has 1 ID
 */
#घोषणा NUMBER_OF_INTERRUPTS		(NUMBER_OF_CMPLT_QUEUES + 1)

#अगर (NUMBER_OF_INTERRUPTS > GOYA_MSIX_ENTRIES)
#त्रुटि "Number of MSIX interrupts must be smaller or equal to GOYA_MSIX_ENTRIES"
#पूर्ण_अगर

#घोषणा QMAN_FENCE_TIMEOUT_USEC		10000		/* 10 ms */

#घोषणा QMAN_STOP_TIMEOUT_USEC		100000		/* 100 ms */

#घोषणा CORESIGHT_TIMEOUT_USEC		100000		/* 100 ms */

#घोषणा GOYA_CPU_TIMEOUT_USEC		15000000	/* 15s */

#घोषणा TPC_ENABLED_MASK		0xFF

#घोषणा PLL_HIGH_DEFAULT		1575000000	/* 1.575 GHz */

#घोषणा MAX_POWER_DEFAULT		200000		/* 200W */

#घोषणा DC_POWER_DEFAULT		20000		/* 20W */

#घोषणा DRAM_PHYS_DEFAULT_SIZE		0x100000000ull	/* 4GB */

#घोषणा GOYA_DEFAULT_CARD_NAME		"HL1000"

#घोषणा GOYA_MAX_PENDING_CS		64

#अगर !IS_MAX_PENDING_CS_VALID(GOYA_MAX_PENDING_CS)
#त्रुटि "GOYA_MAX_PENDING_CS must be power of 2 and greater than 1"
#पूर्ण_अगर

/* DRAM Memory Map */

#घोषणा CPU_FW_IMAGE_SIZE		0x10000000	/* 256MB */
#घोषणा MMU_PAGE_TABLES_SIZE		0x0FC00000	/* 252MB */
#घोषणा MMU_DRAM_DEFAULT_PAGE_SIZE	0x00200000	/* 2MB */
#घोषणा MMU_CACHE_MNG_SIZE		0x00001000	/* 4KB */

#घोषणा CPU_FW_IMAGE_ADDR		DRAM_PHYS_BASE
#घोषणा MMU_PAGE_TABLES_ADDR		(CPU_FW_IMAGE_ADDR + CPU_FW_IMAGE_SIZE)
#घोषणा MMU_DRAM_DEFAULT_PAGE_ADDR	(MMU_PAGE_TABLES_ADDR + \
						MMU_PAGE_TABLES_SIZE)
#घोषणा MMU_CACHE_MNG_ADDR		(MMU_DRAM_DEFAULT_PAGE_ADDR + \
					MMU_DRAM_DEFAULT_PAGE_SIZE)
#घोषणा DRAM_DRIVER_END_ADDR		(MMU_CACHE_MNG_ADDR + \
						MMU_CACHE_MNG_SIZE)

#घोषणा DRAM_BASE_ADDR_USER		0x20000000

#अगर (DRAM_DRIVER_END_ADDR > DRAM_BASE_ADDR_USER)
#त्रुटि "Driver must reserve no more than 512MB"
#पूर्ण_अगर

/*
 * SRAM Memory Map क्रम Driver
 *
 * Driver occupies DRIVER_SRAM_SIZE bytes from the start of SRAM. It is used क्रम
 * MME/TPC QMANs
 *
 */

#घोषणा MME_QMAN_BASE_OFFSET	0x000000	/* Must be 0 */
#घोषणा MME_QMAN_LENGTH		64
#घोषणा TPC_QMAN_LENGTH		64

#घोषणा TPC0_QMAN_BASE_OFFSET	(MME_QMAN_BASE_OFFSET + \
				(MME_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC1_QMAN_BASE_OFFSET	(TPC0_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC2_QMAN_BASE_OFFSET	(TPC1_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC3_QMAN_BASE_OFFSET	(TPC2_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC4_QMAN_BASE_OFFSET	(TPC3_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC5_QMAN_BASE_OFFSET	(TPC4_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC6_QMAN_BASE_OFFSET	(TPC5_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))
#घोषणा TPC7_QMAN_BASE_OFFSET	(TPC6_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))

#घोषणा SRAM_DRIVER_RES_OFFSET	(TPC7_QMAN_BASE_OFFSET + \
				(TPC_QMAN_LENGTH * QMAN_PQ_ENTRY_SIZE))

#अगर (SRAM_DRIVER_RES_OFFSET >= GOYA_KMD_SRAM_RESERVED_SIZE_FROM_START)
#त्रुटि "MME/TPC QMANs SRAM space exceeds limit"
#पूर्ण_अगर

#घोषणा SRAM_USER_BASE_OFFSET	GOYA_KMD_SRAM_RESERVED_SIZE_FROM_START

/* Virtual address space */
#घोषणा VA_HOST_SPACE_START	0x1000000000000ull	/* 256TB */
#घोषणा VA_HOST_SPACE_END	0x3FF8000000000ull	/* 1PB - 1TB */
#घोषणा VA_HOST_SPACE_SIZE	(VA_HOST_SPACE_END - \
					VA_HOST_SPACE_START) /* 767TB */

#घोषणा VA_DDR_SPACE_START	0x800000000ull		/* 32GB */
#घोषणा VA_DDR_SPACE_END	0x2000000000ull		/* 128GB */
#घोषणा VA_DDR_SPACE_SIZE	(VA_DDR_SPACE_END - \
					VA_DDR_SPACE_START)	/* 128GB */

#अगर (HL_CPU_ACCESSIBLE_MEM_SIZE != SZ_2M)
#त्रुटि "HL_CPU_ACCESSIBLE_MEM_SIZE must be exactly 2MB to enable MMU mapping"
#पूर्ण_अगर

#घोषणा VA_CPU_ACCESSIBLE_MEM_ADDR	0x8000000000ull

#घोषणा DMA_MAX_TRANSFER_SIZE	U32_MAX

#घोषणा HW_CAP_PLL		0x00000001
#घोषणा HW_CAP_DDR_0		0x00000002
#घोषणा HW_CAP_DDR_1		0x00000004
#घोषणा HW_CAP_MME		0x00000008
#घोषणा HW_CAP_CPU		0x00000010
#घोषणा HW_CAP_DMA		0x00000020
#घोषणा HW_CAP_MSIX		0x00000040
#घोषणा HW_CAP_CPU_Q		0x00000080
#घोषणा HW_CAP_MMU		0x00000100
#घोषणा HW_CAP_TPC_MBIST	0x00000200
#घोषणा HW_CAP_GOLDEN		0x00000400
#घोषणा HW_CAP_TPC		0x00000800

काष्ठा goya_device अणु
	/* TODO: हटाओ hw_queues_lock after moving to scheduler code */
	spinlock_t	hw_queues_lock;

	u64		mme_clk;
	u64		tpc_clk;
	u64		ic_clk;

	u64		ddr_bar_cur_addr;
	u32		events_stat[GOYA_ASYNC_EVENT_ID_SIZE];
	u32		events_stat_aggregate[GOYA_ASYNC_EVENT_ID_SIZE];
	u32		hw_cap_initialized;
	u8		device_cpu_mmu_mappings_करोne;
पूर्ण;

पूर्णांक goya_get_fixed_properties(काष्ठा hl_device *hdev);
पूर्णांक goya_mmu_init(काष्ठा hl_device *hdev);
व्योम goya_init_dma_qmans(काष्ठा hl_device *hdev);
व्योम goya_init_mme_qmans(काष्ठा hl_device *hdev);
व्योम goya_init_tpc_qmans(काष्ठा hl_device *hdev);
पूर्णांक goya_init_cpu_queues(काष्ठा hl_device *hdev);
व्योम goya_init_security(काष्ठा hl_device *hdev);
व्योम goya_ack_protection_bits_errors(काष्ठा hl_device *hdev);
पूर्णांक goya_late_init(काष्ठा hl_device *hdev);
व्योम goya_late_fini(काष्ठा hl_device *hdev);

व्योम goya_ring_करोorbell(काष्ठा hl_device *hdev, u32 hw_queue_id, u32 pi);
व्योम goya_pqe_ग_लिखो(काष्ठा hl_device *hdev, __le64 *pqe, काष्ठा hl_bd *bd);
व्योम goya_update_eq_ci(काष्ठा hl_device *hdev, u32 val);
व्योम goya_restore_phase_topology(काष्ठा hl_device *hdev);
पूर्णांक goya_context_चयन(काष्ठा hl_device *hdev, u32 asid);

पूर्णांक goya_debugfs_i2c_पढ़ो(काष्ठा hl_device *hdev, u8 i2c_bus,
			u8 i2c_addr, u8 i2c_reg, u32 *val);
पूर्णांक goya_debugfs_i2c_ग_लिखो(काष्ठा hl_device *hdev, u8 i2c_bus,
			u8 i2c_addr, u8 i2c_reg, u32 val);
व्योम goya_debugfs_led_set(काष्ठा hl_device *hdev, u8 led, u8 state);

पूर्णांक goya_test_queue(काष्ठा hl_device *hdev, u32 hw_queue_id);
पूर्णांक goya_test_queues(काष्ठा hl_device *hdev);
पूर्णांक goya_test_cpu_queue(काष्ठा hl_device *hdev);
पूर्णांक goya_send_cpu_message(काष्ठा hl_device *hdev, u32 *msg, u16 len,
				u32 समयout, u64 *result);

दीर्घ goya_get_temperature(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr);
दीर्घ goya_get_voltage(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr);
दीर्घ goya_get_current(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr);
दीर्घ goya_get_fan_speed(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr);
दीर्घ goya_get_pwm_info(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr);
व्योम goya_set_pwm_info(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr,
			दीर्घ value);
u64 goya_get_max_घातer(काष्ठा hl_device *hdev);
व्योम goya_set_max_घातer(काष्ठा hl_device *hdev, u64 value);

व्योम goya_set_pll_profile(काष्ठा hl_device *hdev, क्रमागत hl_pll_frequency freq);
व्योम goya_add_device_attr(काष्ठा hl_device *hdev,
			काष्ठा attribute_group *dev_attr_grp);
पूर्णांक goya_cpucp_info_get(काष्ठा hl_device *hdev);
पूर्णांक goya_debug_coresight(काष्ठा hl_device *hdev, व्योम *data);
व्योम goya_halt_coresight(काष्ठा hl_device *hdev);

पूर्णांक goya_suspend(काष्ठा hl_device *hdev);
पूर्णांक goya_resume(काष्ठा hl_device *hdev);

व्योम goya_handle_eqe(काष्ठा hl_device *hdev, काष्ठा hl_eq_entry *eq_entry);
व्योम *goya_get_events_stat(काष्ठा hl_device *hdev, bool aggregate, u32 *size);

व्योम goya_add_end_of_cb_packets(काष्ठा hl_device *hdev, व्योम *kernel_address,
				u32 len, u64 cq_addr, u32 cq_val, u32 msix_vec,
				bool eb);
पूर्णांक goya_cs_parser(काष्ठा hl_device *hdev, काष्ठा hl_cs_parser *parser);
पूर्णांक goya_scrub_device_mem(काष्ठा hl_device *hdev, u64 addr, u64 size);
व्योम *goya_get_पूर्णांक_queue_base(काष्ठा hl_device *hdev, u32 queue_id,
				dma_addr_t *dma_handle,	u16 *queue_len);
u32 goya_get_dma_desc_list_size(काष्ठा hl_device *hdev, काष्ठा sg_table *sgt);
पूर्णांक goya_send_heartbeat(काष्ठा hl_device *hdev);
व्योम *goya_cpu_accessible_dma_pool_alloc(काष्ठा hl_device *hdev, माप_प्रकार size,
					dma_addr_t *dma_handle);
व्योम goya_cpu_accessible_dma_pool_मुक्त(काष्ठा hl_device *hdev, माप_प्रकार size,
					व्योम *vaddr);
व्योम goya_mmu_हटाओ_device_cpu_mappings(काष्ठा hl_device *hdev);

पूर्णांक goya_get_clk_rate(काष्ठा hl_device *hdev, u32 *cur_clk, u32 *max_clk);
u32 goya_get_queue_id_क्रम_cq(काष्ठा hl_device *hdev, u32 cq_idx);
u64 goya_get_device_समय(काष्ठा hl_device *hdev);

#पूर्ण_अगर /* GOYAP_H_ */
