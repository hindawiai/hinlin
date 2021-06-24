<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note
 *
 * Copyright 2016-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित HABANALABS_H_
#घोषणा HABANALABS_H_

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * Defines that are asic-specअगरic but स्थिरitutes as ABI between kernel driver
 * and userspace
 */
#घोषणा GOYA_KMD_SRAM_RESERVED_SIZE_FROM_START		0x8000	/* 32KB */
#घोषणा GAUDI_DRIVER_SRAM_RESERVED_SIZE_FROM_START	0x80	/* 128 bytes */

/*
 * 128 SOBs reserved क्रम collective रुको
 * 16 SOBs reserved क्रम sync stream
 */
#घोषणा GAUDI_FIRST_AVAILABLE_W_S_SYNC_OBJECT		144

/*
 * 64 monitors reserved क्रम collective रुको
 * 8 monitors reserved क्रम sync stream
 */
#घोषणा GAUDI_FIRST_AVAILABLE_W_S_MONITOR		72

/*
 * Goya queue Numbering
 *
 * The बाह्यal queues (PCI DMA channels) MUST be beक्रमe the पूर्णांकernal queues
 * and each group (PCI DMA channels and पूर्णांकernal) must be contiguous inside
 * itself but there can be a gap between the two groups (although not
 * recommended)
 */

क्रमागत goya_queue_id अणु
	GOYA_QUEUE_ID_DMA_0 = 0,
	GOYA_QUEUE_ID_DMA_1 = 1,
	GOYA_QUEUE_ID_DMA_2 = 2,
	GOYA_QUEUE_ID_DMA_3 = 3,
	GOYA_QUEUE_ID_DMA_4 = 4,
	GOYA_QUEUE_ID_CPU_PQ = 5,
	GOYA_QUEUE_ID_MME = 6,	/* Internal queues start here */
	GOYA_QUEUE_ID_TPC0 = 7,
	GOYA_QUEUE_ID_TPC1 = 8,
	GOYA_QUEUE_ID_TPC2 = 9,
	GOYA_QUEUE_ID_TPC3 = 10,
	GOYA_QUEUE_ID_TPC4 = 11,
	GOYA_QUEUE_ID_TPC5 = 12,
	GOYA_QUEUE_ID_TPC6 = 13,
	GOYA_QUEUE_ID_TPC7 = 14,
	GOYA_QUEUE_ID_SIZE
पूर्ण;

/*
 * Gaudi queue Numbering
 * External queues (PCI DMA channels) are DMA_0_*, DMA_1_* and DMA_5_*.
 * Except one CPU queue, all the rest are पूर्णांकernal queues.
 */

क्रमागत gaudi_queue_id अणु
	GAUDI_QUEUE_ID_DMA_0_0 = 0,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_0_1 = 1,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_0_2 = 2,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_0_3 = 3,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_1_0 = 4,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_1_1 = 5,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_1_2 = 6,	/* बाह्यal */
	GAUDI_QUEUE_ID_DMA_1_3 = 7,	/* बाह्यal */
	GAUDI_QUEUE_ID_CPU_PQ = 8,	/* CPU */
	GAUDI_QUEUE_ID_DMA_2_0 = 9,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_2_1 = 10,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_2_2 = 11,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_2_3 = 12,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_3_0 = 13,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_3_1 = 14,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_3_2 = 15,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_3_3 = 16,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_4_0 = 17,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_4_1 = 18,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_4_2 = 19,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_4_3 = 20,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_5_0 = 21,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_5_1 = 22,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_5_2 = 23,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_5_3 = 24,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_6_0 = 25,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_6_1 = 26,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_6_2 = 27,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_6_3 = 28,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_7_0 = 29,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_7_1 = 30,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_7_2 = 31,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_DMA_7_3 = 32,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_0_0 = 33,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_0_1 = 34,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_0_2 = 35,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_0_3 = 36,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_1_0 = 37,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_1_1 = 38,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_1_2 = 39,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_MME_1_3 = 40,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_0_0 = 41,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_0_1 = 42,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_0_2 = 43,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_0_3 = 44,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_1_0 = 45,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_1_1 = 46,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_1_2 = 47,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_1_3 = 48,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_2_0 = 49,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_2_1 = 50,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_2_2 = 51,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_2_3 = 52,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_3_0 = 53,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_3_1 = 54,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_3_2 = 55,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_3_3 = 56,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_4_0 = 57,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_4_1 = 58,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_4_2 = 59,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_4_3 = 60,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_5_0 = 61,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_5_1 = 62,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_5_2 = 63,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_5_3 = 64,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_6_0 = 65,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_6_1 = 66,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_6_2 = 67,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_6_3 = 68,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_7_0 = 69,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_7_1 = 70,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_7_2 = 71,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_TPC_7_3 = 72,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_0_0 = 73,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_0_1 = 74,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_0_2 = 75,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_0_3 = 76,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_1_0 = 77,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_1_1 = 78,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_1_2 = 79,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_1_3 = 80,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_2_0 = 81,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_2_1 = 82,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_2_2 = 83,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_2_3 = 84,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_3_0 = 85,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_3_1 = 86,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_3_2 = 87,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_3_3 = 88,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_4_0 = 89,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_4_1 = 90,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_4_2 = 91,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_4_3 = 92,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_5_0 = 93,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_5_1 = 94,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_5_2 = 95,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_5_3 = 96,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_6_0 = 97,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_6_1 = 98,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_6_2 = 99,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_6_3 = 100,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_7_0 = 101,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_7_1 = 102,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_7_2 = 103,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_7_3 = 104,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_8_0 = 105,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_8_1 = 106,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_8_2 = 107,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_8_3 = 108,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_9_0 = 109,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_9_1 = 110,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_9_2 = 111,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_NIC_9_3 = 112,	/* पूर्णांकernal */
	GAUDI_QUEUE_ID_SIZE
पूर्ण;

/*
 * Engine Numbering
 *
 * Used in the "busy_engines_mask" field in `काष्ठा hl_info_hw_idle'
 */

क्रमागत goya_engine_id अणु
	GOYA_ENGINE_ID_DMA_0 = 0,
	GOYA_ENGINE_ID_DMA_1,
	GOYA_ENGINE_ID_DMA_2,
	GOYA_ENGINE_ID_DMA_3,
	GOYA_ENGINE_ID_DMA_4,
	GOYA_ENGINE_ID_MME_0,
	GOYA_ENGINE_ID_TPC_0,
	GOYA_ENGINE_ID_TPC_1,
	GOYA_ENGINE_ID_TPC_2,
	GOYA_ENGINE_ID_TPC_3,
	GOYA_ENGINE_ID_TPC_4,
	GOYA_ENGINE_ID_TPC_5,
	GOYA_ENGINE_ID_TPC_6,
	GOYA_ENGINE_ID_TPC_7,
	GOYA_ENGINE_ID_SIZE
पूर्ण;

क्रमागत gaudi_engine_id अणु
	GAUDI_ENGINE_ID_DMA_0 = 0,
	GAUDI_ENGINE_ID_DMA_1,
	GAUDI_ENGINE_ID_DMA_2,
	GAUDI_ENGINE_ID_DMA_3,
	GAUDI_ENGINE_ID_DMA_4,
	GAUDI_ENGINE_ID_DMA_5,
	GAUDI_ENGINE_ID_DMA_6,
	GAUDI_ENGINE_ID_DMA_7,
	GAUDI_ENGINE_ID_MME_0,
	GAUDI_ENGINE_ID_MME_1,
	GAUDI_ENGINE_ID_MME_2,
	GAUDI_ENGINE_ID_MME_3,
	GAUDI_ENGINE_ID_TPC_0,
	GAUDI_ENGINE_ID_TPC_1,
	GAUDI_ENGINE_ID_TPC_2,
	GAUDI_ENGINE_ID_TPC_3,
	GAUDI_ENGINE_ID_TPC_4,
	GAUDI_ENGINE_ID_TPC_5,
	GAUDI_ENGINE_ID_TPC_6,
	GAUDI_ENGINE_ID_TPC_7,
	GAUDI_ENGINE_ID_NIC_0,
	GAUDI_ENGINE_ID_NIC_1,
	GAUDI_ENGINE_ID_NIC_2,
	GAUDI_ENGINE_ID_NIC_3,
	GAUDI_ENGINE_ID_NIC_4,
	GAUDI_ENGINE_ID_NIC_5,
	GAUDI_ENGINE_ID_NIC_6,
	GAUDI_ENGINE_ID_NIC_7,
	GAUDI_ENGINE_ID_NIC_8,
	GAUDI_ENGINE_ID_NIC_9,
	GAUDI_ENGINE_ID_SIZE
पूर्ण;

/*
 * ASIC specअगरic PLL index
 *
 * Used to retrieve in frequency info of dअगरferent IPs via
 * HL_INFO_PLL_FREQUENCY under HL_IOCTL_INFO IOCTL. The क्रमागतs need to be
 * used as an index in काष्ठा hl_pll_frequency_info
 */

क्रमागत hl_goya_pll_index अणु
	HL_GOYA_CPU_PLL = 0,
	HL_GOYA_IC_PLL,
	HL_GOYA_MC_PLL,
	HL_GOYA_MME_PLL,
	HL_GOYA_PCI_PLL,
	HL_GOYA_EMMC_PLL,
	HL_GOYA_TPC_PLL,
	HL_GOYA_PLL_MAX
पूर्ण;

क्रमागत hl_gaudi_pll_index अणु
	HL_GAUDI_CPU_PLL = 0,
	HL_GAUDI_PCI_PLL,
	HL_GAUDI_SRAM_PLL,
	HL_GAUDI_HBM_PLL,
	HL_GAUDI_NIC_PLL,
	HL_GAUDI_DMA_PLL,
	HL_GAUDI_MESH_PLL,
	HL_GAUDI_MME_PLL,
	HL_GAUDI_TPC_PLL,
	HL_GAUDI_IF_PLL,
	HL_GAUDI_PLL_MAX
पूर्ण;

क्रमागत hl_device_status अणु
	HL_DEVICE_STATUS_OPERATIONAL,
	HL_DEVICE_STATUS_IN_RESET,
	HL_DEVICE_STATUS_MALFUNCTION,
	HL_DEVICE_STATUS_NEEDS_RESET
पूर्ण;

/* Opcode क्रम management ioctl
 *
 * HW_IP_INFO            - Receive inक्रमmation about dअगरferent IP blocks in the
 *                         device.
 * HL_INFO_HW_EVENTS     - Receive an array describing how many बार each event
 *                         occurred since the last hard reset.
 * HL_INFO_DRAM_USAGE    - Retrieve the dram usage inside the device and of the
 *                         specअगरic context. This is relevant only क्रम devices
 *                         where the dram is managed by the kernel driver
 * HL_INFO_HW_IDLE       - Retrieve inक्रमmation about the idle status of each
 *                         पूर्णांकernal engine.
 * HL_INFO_DEVICE_STATUS - Retrieve the device's status. This opcode doesn't
 *                         require an खोलो context.
 * HL_INFO_DEVICE_UTILIZATION  - Retrieve the total utilization of the device
 *                               over the last period specअगरied by the user.
 *                               The period can be between 100ms to 1s, in
 *                               resolution of 100ms. The वापस value is a
 *                               percentage of the utilization rate.
 * HL_INFO_HW_EVENTS_AGGREGATE - Receive an array describing how many बार each
 *                               event occurred since the driver was loaded.
 * HL_INFO_CLK_RATE            - Retrieve the current and maximum घड़ी rate
 *                               of the device in MHz. The maximum घड़ी rate is
 *                               configurable via sysfs parameter
 * HL_INFO_RESET_COUNT   - Retrieve the counts of the soft and hard reset
 *                         operations perक्रमmed on the device since the last
 *                         समय the driver was loaded.
 * HL_INFO_TIME_SYNC     - Retrieve the device's time alongside the host's समय
 *                         क्रम synchronization.
 * HL_INFO_CS_COUNTERS   - Retrieve command submission counters
 * HL_INFO_PCI_COUNTERS  - Retrieve PCI counters
 * HL_INFO_CLK_THROTTLE_REASON - Retrieve घड़ी throttling reason
 * HL_INFO_SYNC_MANAGER  - Retrieve sync manager info per dcore
 * HL_INFO_TOTAL_ENERGY  - Retrieve total energy consumption
 * HL_INFO_PLL_FREQUENCY - Retrieve PLL frequency
 */
#घोषणा HL_INFO_HW_IP_INFO		0
#घोषणा HL_INFO_HW_EVENTS		1
#घोषणा HL_INFO_DRAM_USAGE		2
#घोषणा HL_INFO_HW_IDLE			3
#घोषणा HL_INFO_DEVICE_STATUS		4
#घोषणा HL_INFO_DEVICE_UTILIZATION	6
#घोषणा HL_INFO_HW_EVENTS_AGGREGATE	7
#घोषणा HL_INFO_CLK_RATE		8
#घोषणा HL_INFO_RESET_COUNT		9
#घोषणा HL_INFO_TIME_SYNC		10
#घोषणा HL_INFO_CS_COUNTERS		11
#घोषणा HL_INFO_PCI_COUNTERS		12
#घोषणा HL_INFO_CLK_THROTTLE_REASON	13
#घोषणा HL_INFO_SYNC_MANAGER		14
#घोषणा HL_INFO_TOTAL_ENERGY		15
#घोषणा HL_INFO_PLL_FREQUENCY		16
#घोषणा HL_INFO_POWER			17

#घोषणा HL_INFO_VERSION_MAX_LEN	128
#घोषणा HL_INFO_CARD_NAME_MAX_LEN	16

काष्ठा hl_info_hw_ip_info अणु
	__u64 sram_base_address;
	__u64 dram_base_address;
	__u64 dram_size;
	__u32 sram_size;
	__u32 num_of_events;
	__u32 device_id; /* PCI Device ID */
	__u32 module_id; /* For mezzanine cards in servers (From OCP spec.) */
	__u32 reserved;
	__u16 first_available_पूर्णांकerrupt_id;
	__u16 reserved2;
	__u32 cpld_version;
	__u32 psoc_pci_pll_nr;
	__u32 psoc_pci_pll_nf;
	__u32 psoc_pci_pll_od;
	__u32 psoc_pci_pll_भाग_factor;
	__u8 tpc_enabled_mask;
	__u8 dram_enabled;
	__u8 pad[2];
	__u8 cpucp_version[HL_INFO_VERSION_MAX_LEN];
	__u8 card_name[HL_INFO_CARD_NAME_MAX_LEN];
	__u64 reserved3;
	__u64 dram_page_size;
पूर्ण;

काष्ठा hl_info_dram_usage अणु
	__u64 dram_मुक्त_mem;
	__u64 ctx_dram_mem;
पूर्ण;

#घोषणा HL_BUSY_ENGINES_MASK_EXT_SIZE	2

काष्ठा hl_info_hw_idle अणु
	__u32 is_idle;
	/*
	 * Biपंचांगask of busy engines.
	 * Bits definition is according to `क्रमागत <chip>_enging_id'.
	 */
	__u32 busy_engines_mask;

	/*
	 * Extended Biपंचांगask of busy engines.
	 * Bits definition is according to `क्रमागत <chip>_enging_id'.
	 */
	__u64 busy_engines_mask_ext[HL_BUSY_ENGINES_MASK_EXT_SIZE];
पूर्ण;

काष्ठा hl_info_device_status अणु
	__u32 status;
	__u32 pad;
पूर्ण;

काष्ठा hl_info_device_utilization अणु
	__u32 utilization;
	__u32 pad;
पूर्ण;

काष्ठा hl_info_clk_rate अणु
	__u32 cur_clk_rate_mhz;
	__u32 max_clk_rate_mhz;
पूर्ण;

काष्ठा hl_info_reset_count अणु
	__u32 hard_reset_cnt;
	__u32 soft_reset_cnt;
पूर्ण;

काष्ठा hl_info_समय_sync अणु
	__u64 device_समय;
	__u64 host_समय;
पूर्ण;

/**
 * काष्ठा hl_info_pci_counters - pci counters
 * @rx_throughput: PCI rx throughput KBps
 * @tx_throughput: PCI tx throughput KBps
 * @replay_cnt: PCI replay counter
 */
काष्ठा hl_info_pci_counters अणु
	__u64 rx_throughput;
	__u64 tx_throughput;
	__u64 replay_cnt;
पूर्ण;

#घोषणा HL_CLK_THROTTLE_POWER	0x1
#घोषणा HL_CLK_THROTTLE_THERMAL	0x2

/**
 * काष्ठा hl_info_clk_throttle - घड़ी throttling reason
 * @clk_throttling_reason: each bit represents a clk throttling reason
 */
काष्ठा hl_info_clk_throttle अणु
	__u32 clk_throttling_reason;
पूर्ण;

/**
 * काष्ठा hl_info_energy - device energy inक्रमmation
 * @total_energy_consumption: total device energy consumption
 */
काष्ठा hl_info_energy अणु
	__u64 total_energy_consumption;
पूर्ण;

#घोषणा HL_PLL_NUM_OUTPUTS 4

काष्ठा hl_pll_frequency_info अणु
	__u16 output[HL_PLL_NUM_OUTPUTS];
पूर्ण;

/**
 * काष्ठा hl_घातer_info - घातer inक्रमmation
 * @घातer: घातer consumption
 */
काष्ठा hl_घातer_info अणु
	__u64 घातer;
पूर्ण;

/**
 * काष्ठा hl_info_sync_manager - sync manager inक्रमmation
 * @first_available_sync_object: first available sob
 * @first_available_monitor: first available monitor
 * @first_available_cq: first available cq
 */
काष्ठा hl_info_sync_manager अणु
	__u32 first_available_sync_object;
	__u32 first_available_monitor;
	__u32 first_available_cq;
	__u32 reserved;
पूर्ण;

/**
 * काष्ठा hl_info_cs_counters - command submission counters
 * @total_out_of_mem_drop_cnt: total dropped due to memory allocation issue
 * @ctx_out_of_mem_drop_cnt: context dropped due to memory allocation issue
 * @total_parsing_drop_cnt: total dropped due to error in packet parsing
 * @ctx_parsing_drop_cnt: context dropped due to error in packet parsing
 * @total_queue_full_drop_cnt: total dropped due to queue full
 * @ctx_queue_full_drop_cnt: context dropped due to queue full
 * @total_device_in_reset_drop_cnt: total dropped due to device in reset
 * @ctx_device_in_reset_drop_cnt: context dropped due to device in reset
 * @total_max_cs_in_flight_drop_cnt: total dropped due to maximum CS in-flight
 * @ctx_max_cs_in_flight_drop_cnt: context dropped due to maximum CS in-flight
 * @total_validation_drop_cnt: total dropped due to validation error
 * @ctx_validation_drop_cnt: context dropped due to validation error
 */
काष्ठा hl_info_cs_counters अणु
	__u64 total_out_of_mem_drop_cnt;
	__u64 ctx_out_of_mem_drop_cnt;
	__u64 total_parsing_drop_cnt;
	__u64 ctx_parsing_drop_cnt;
	__u64 total_queue_full_drop_cnt;
	__u64 ctx_queue_full_drop_cnt;
	__u64 total_device_in_reset_drop_cnt;
	__u64 ctx_device_in_reset_drop_cnt;
	__u64 total_max_cs_in_flight_drop_cnt;
	__u64 ctx_max_cs_in_flight_drop_cnt;
	__u64 total_validation_drop_cnt;
	__u64 ctx_validation_drop_cnt;
पूर्ण;

क्रमागत gaudi_dcores अणु
	HL_GAUDI_WS_DCORE,
	HL_GAUDI_WN_DCORE,
	HL_GAUDI_EN_DCORE,
	HL_GAUDI_ES_DCORE
पूर्ण;

काष्ठा hl_info_args अणु
	/* Location of relevant काष्ठा in userspace */
	__u64 वापस_poपूर्णांकer;
	/*
	 * The size of the वापस value. Just like "size" in "snprintf",
	 * it limits how many bytes the kernel can ग_लिखो
	 *
	 * For hw_events array, the size should be
	 * hl_info_hw_ip_info.num_of_events * माप(__u32)
	 */
	__u32 वापस_size;

	/* HL_INFO_* */
	__u32 op;

	जोड़ अणु
		/* Dcore id क्रम which the inक्रमmation is relevant.
		 * For Gaudi refer to 'enum gaudi_dcores'
		 */
		__u32 dcore_id;
		/* Context ID - Currently not in use */
		__u32 ctx_id;
		/* Period value क्रम utilization rate (100ms - 1000ms, in 100ms
		 * resolution.
		 */
		__u32 period_ms;
		/* PLL frequency retrieval */
		__u32 pll_index;
	पूर्ण;

	__u32 pad;
पूर्ण;

/* Opcode to create a new command buffer */
#घोषणा HL_CB_OP_CREATE		0
/* Opcode to destroy previously created command buffer */
#घोषणा HL_CB_OP_DESTROY	1
/* Opcode to retrieve inक्रमmation about a command buffer */
#घोषणा HL_CB_OP_INFO		2

/* 2MB minus 32 bytes क्रम 2xMSG_PROT */
#घोषणा HL_MAX_CB_SIZE		(0x200000 - 32)

/* Indicates whether the command buffer should be mapped to the device's MMU */
#घोषणा HL_CB_FLAGS_MAP		0x1

काष्ठा hl_cb_in अणु
	/* Handle of CB or 0 अगर we want to create one */
	__u64 cb_handle;
	/* HL_CB_OP_* */
	__u32 op;
	/* Size of CB. Maximum size is HL_MAX_CB_SIZE. The minimum size that
	 * will be allocated, regardless of this parameter's value, is PAGE_SIZE
	 */
	__u32 cb_size;
	/* Context ID - Currently not in use */
	__u32 ctx_id;
	/* HL_CB_FLAGS_* */
	__u32 flags;
पूर्ण;

काष्ठा hl_cb_out अणु
	जोड़ अणु
		/* Handle of CB */
		__u64 cb_handle;

		/* Inक्रमmation about CB */
		काष्ठा अणु
			/* Usage count of CB */
			__u32 usage_cnt;
			__u32 pad;
		पूर्ण;
	पूर्ण;
पूर्ण;

जोड़ hl_cb_args अणु
	काष्ठा hl_cb_in in;
	काष्ठा hl_cb_out out;
पूर्ण;

/* HL_CS_CHUNK_FLAGS_ values
 *
 * HL_CS_CHUNK_FLAGS_USER_ALLOC_CB:
 *      Indicates अगर the CB was allocated and mapped by userspace.
 *      User allocated CB is a command buffer allocated by the user, via दो_स्मृति
 *      (or similar). After allocating the CB, the user invokes ै memory ioctlै 
 *      to map the user memory पूर्णांकo a device भव address. The user provides
 *      this address via the cb_handle field. The पूर्णांकerface provides the
 *      ability to create a large CBs, Which arenै t limited to
 *      ै HL_MAX_CB_SIZEै . Thereक्रमe, it increases the PCI-DMA queues
 *      throughput. This CB allocation method also reduces the use of Linux
 *      DMA-able memory pool. Which are limited and used by other Linux
 *      sub-प्रणालीs.
 */
#घोषणा HL_CS_CHUNK_FLAGS_USER_ALLOC_CB 0x1

/*
 * This काष्ठाure size must always be fixed to 64-bytes क्रम backward
 * compatibility
 */
काष्ठा hl_cs_chunk अणु
	जोड़ अणु
		/* For बाह्यal queue, this represents a Handle of CB on the
		 * Host.
		 * For पूर्णांकernal queue in Goya, this represents an SRAM or
		 * a DRAM address of the पूर्णांकernal CB. In Gaudi, this might also
		 * represent a mapped host address of the CB.
		 *
		 * A mapped host address is in the device address space, after
		 * a host address was mapped by the device MMU.
		 */
		__u64 cb_handle;

		/* Relevant only when HL_CS_FLAGS_WAIT or
		 * HL_CS_FLAGS_COLLECTIVE_WAIT is set.
		 * This holds address of array of u64 values that contain
		 * संकेत CS sequence numbers. The रुको described by this job
		 * will listen on all those संकेतs (रुको event per संकेत)
		 */
		__u64 संकेत_seq_arr;
	पूर्ण;

	/* Index of queue to put the CB on */
	__u32 queue_index;

	जोड़ अणु
		/*
		 * Size of command buffer with valid packets
		 * Can be smaller then actual CB size
		 */
		__u32 cb_size;

		/* Relevant only when HL_CS_FLAGS_WAIT or
		 * HL_CS_FLAGS_COLLECTIVE_WAIT is set.
		 * Number of entries in संकेत_seq_arr
		 */
		__u32 num_संकेत_seq_arr;
	पूर्ण;

	/* HL_CS_CHUNK_FLAGS_* */
	__u32 cs_chunk_flags;

	/* Relevant only when HL_CS_FLAGS_COLLECTIVE_WAIT is set.
	 * This holds the collective engine ID. The रुको described by this job
	 * will sync with this engine and with all NICs beक्रमe completion.
	 */
	__u32 collective_engine_id;

	/* Align काष्ठाure to 64 bytes */
	__u32 pad[10];
पूर्ण;

/* SIGNAL and WAIT/COLLECTIVE_WAIT flags are mutually exclusive */
#घोषणा HL_CS_FLAGS_FORCE_RESTORE		0x1
#घोषणा HL_CS_FLAGS_SIGNAL			0x2
#घोषणा HL_CS_FLAGS_WAIT			0x4
#घोषणा HL_CS_FLAGS_COLLECTIVE_WAIT		0x8
#घोषणा HL_CS_FLAGS_TIMESTAMP			0x20
#घोषणा HL_CS_FLAGS_STAGED_SUBMISSION		0x40
#घोषणा HL_CS_FLAGS_STAGED_SUBMISSION_FIRST	0x80
#घोषणा HL_CS_FLAGS_STAGED_SUBMISSION_LAST	0x100
#घोषणा HL_CS_FLAGS_CUSTOM_TIMEOUT		0x200

#घोषणा HL_CS_STATUS_SUCCESS		0

#घोषणा HL_MAX_JOBS_PER_CS		512

काष्ठा hl_cs_in अणु

	/* this holds address of array of hl_cs_chunk क्रम restore phase */
	__u64 chunks_restore;

	/* holds address of array of hl_cs_chunk क्रम execution phase */
	__u64 chunks_execute;

	/* Sequence number of a staged submission CS
	 * valid only अगर HL_CS_FLAGS_STAGED_SUBMISSION is set
	 */
	__u64 seq;

	/* Number of chunks in restore phase array. Maximum number is
	 * HL_MAX_JOBS_PER_CS
	 */
	__u32 num_chunks_restore;

	/* Number of chunks in execution array. Maximum number is
	 * HL_MAX_JOBS_PER_CS
	 */
	__u32 num_chunks_execute;

	/* समयout in seconds - valid only अगर HL_CS_FLAGS_CUSTOM_TIMEOUT
	 * is set
	 */
	__u32 समयout;

	/* HL_CS_FLAGS_* */
	__u32 cs_flags;

	/* Context ID - Currently not in use */
	__u32 ctx_id;
पूर्ण;

काष्ठा hl_cs_out अणु
	/*
	 * seq holds the sequence number of the CS to pass to रुको ioctl. All
	 * values are valid except क्रम 0 and ULदीर्घ_उच्च
	 */
	__u64 seq;
	/* HL_CS_STATUS_* */
	__u32 status;
	__u32 pad;
पूर्ण;

जोड़ hl_cs_args अणु
	काष्ठा hl_cs_in in;
	काष्ठा hl_cs_out out;
पूर्ण;

#घोषणा HL_WAIT_CS_FLAGS_INTERRUPT	0x2
#घोषणा HL_WAIT_CS_FLAGS_INTERRUPT_MASK 0xFFF00000

काष्ठा hl_रुको_cs_in अणु
	जोड़ अणु
		काष्ठा अणु
			/* Command submission sequence number */
			__u64 seq;
			/* Absolute समयout to रुको क्रम command submission
			 * in microseconds
			 */
			__u64 समयout_us;
		पूर्ण;

		काष्ठा अणु
			/* User address क्रम completion comparison.
			 * upon पूर्णांकerrupt, driver will compare the value poपूर्णांकed
			 * by this address with the supplied target value.
			 * in order not to perक्रमm any comparison, set address
			 * to all 1s.
			 * Relevant only when HL_WAIT_CS_FLAGS_INTERRUPT is set
			 */
			__u64 addr;
			/* Target value क्रम completion comparison */
			__u32 target;
			/* Absolute समयout to रुको क्रम पूर्णांकerrupt
			 * in microseconds
			 */
			__u32 पूर्णांकerrupt_समयout_us;
		पूर्ण;
	पूर्ण;

	/* Context ID - Currently not in use */
	__u32 ctx_id;
	/* HL_WAIT_CS_FLAGS_*
	 * If HL_WAIT_CS_FLAGS_INTERRUPT is set, this field should include
	 * पूर्णांकerrupt id according to HL_WAIT_CS_FLAGS_INTERRUPT_MASK, in order
	 * not to specअगरy an पूर्णांकerrupt id ,set mask to all 1s.
	 */
	__u32 flags;
पूर्ण;

#घोषणा HL_WAIT_CS_STATUS_COMPLETED	0
#घोषणा HL_WAIT_CS_STATUS_BUSY		1
#घोषणा HL_WAIT_CS_STATUS_TIMEDOUT	2
#घोषणा HL_WAIT_CS_STATUS_ABORTED	3
#घोषणा HL_WAIT_CS_STATUS_INTERRUPTED	4

#घोषणा HL_WAIT_CS_STATUS_FLAG_GONE		0x1
#घोषणा HL_WAIT_CS_STATUS_FLAG_TIMESTAMP_VLD	0x2

काष्ठा hl_रुको_cs_out अणु
	/* HL_WAIT_CS_STATUS_* */
	__u32 status;
	/* HL_WAIT_CS_STATUS_FLAG* */
	__u32 flags;
	/* valid only अगर HL_WAIT_CS_STATUS_FLAG_TIMESTAMP_VLD is set */
	__s64 बारtamp_nsec;
पूर्ण;

जोड़ hl_रुको_cs_args अणु
	काष्ठा hl_रुको_cs_in in;
	काष्ठा hl_रुको_cs_out out;
पूर्ण;

/* Opcode to allocate device memory */
#घोषणा HL_MEM_OP_ALLOC			0
/* Opcode to मुक्त previously allocated device memory */
#घोषणा HL_MEM_OP_FREE			1
/* Opcode to map host and device memory */
#घोषणा HL_MEM_OP_MAP			2
/* Opcode to unmap previously mapped host and device memory */
#घोषणा HL_MEM_OP_UNMAP			3
/* Opcode to map a hw block */
#घोषणा HL_MEM_OP_MAP_BLOCK		4

/* Memory flags */
#घोषणा HL_MEM_CONTIGUOUS	0x1
#घोषणा HL_MEM_SHARED		0x2
#घोषणा HL_MEM_USERPTR		0x4

काष्ठा hl_mem_in अणु
	जोड़ अणु
		/* HL_MEM_OP_ALLOC- allocate device memory */
		काष्ठा अणु
			/* Size to alloc */
			__u64 mem_size;
		पूर्ण alloc;

		/* HL_MEM_OP_FREE - मुक्त device memory */
		काष्ठा अणु
			/* Handle वापसed from HL_MEM_OP_ALLOC */
			__u64 handle;
		पूर्ण मुक्त;

		/* HL_MEM_OP_MAP - map device memory */
		काष्ठा अणु
			/*
			 * Requested भव address of mapped memory.
			 * The driver will try to map the requested region to
			 * this hपूर्णांक address, as दीर्घ as the address is valid
			 * and not alपढ़ोy mapped. The user should check the
			 * वापसed address of the IOCTL to make sure he got
			 * the hपूर्णांक address. Passing 0 here means that the
			 * driver will choose the address itself.
			 */
			__u64 hपूर्णांक_addr;
			/* Handle वापसed from HL_MEM_OP_ALLOC */
			__u64 handle;
		पूर्ण map_device;

		/* HL_MEM_OP_MAP - map host memory */
		काष्ठा अणु
			/* Address of allocated host memory */
			__u64 host_virt_addr;
			/*
			 * Requested भव address of mapped memory.
			 * The driver will try to map the requested region to
			 * this hपूर्णांक address, as दीर्घ as the address is valid
			 * and not alपढ़ोy mapped. The user should check the
			 * वापसed address of the IOCTL to make sure he got
			 * the hपूर्णांक address. Passing 0 here means that the
			 * driver will choose the address itself.
			 */
			__u64 hपूर्णांक_addr;
			/* Size of allocated host memory */
			__u64 mem_size;
		पूर्ण map_host;

		/* HL_MEM_OP_MAP_BLOCK - map a hw block */
		काष्ठा अणु
			/*
			 * HW block address to map, a handle and size will be
			 * वापसed to the user and will be used to mmap the
			 * relevant block. Only addresses from configuration
			 * space are allowed.
			 */
			__u64 block_addr;
		पूर्ण map_block;

		/* HL_MEM_OP_UNMAP - unmap host memory */
		काष्ठा अणु
			/* Virtual address वापसed from HL_MEM_OP_MAP */
			__u64 device_virt_addr;
		पूर्ण unmap;
	पूर्ण;

	/* HL_MEM_OP_* */
	__u32 op;
	/* HL_MEM_* flags */
	__u32 flags;
	/* Context ID - Currently not in use */
	__u32 ctx_id;
	__u32 pad;
पूर्ण;

काष्ठा hl_mem_out अणु
	जोड़ अणु
		/*
		 * Used क्रम HL_MEM_OP_MAP as the भव address that was
		 * asचिन्हित in the device VA space.
		 * A value of 0 means the requested operation failed.
		 */
		__u64 device_virt_addr;

		/*
		 * Used in HL_MEM_OP_ALLOC
		 * This is the asचिन्हित handle क्रम the allocated memory
		 */
		__u64 handle;

		काष्ठा अणु
			/*
			 * Used in HL_MEM_OP_MAP_BLOCK.
			 * This is the asचिन्हित handle क्रम the mapped block
			 */
			__u64 block_handle;

			/*
			 * Used in HL_MEM_OP_MAP_BLOCK
			 * This is the size of the mapped block
			 */
			__u32 block_size;

			__u32 pad;
		पूर्ण;
	पूर्ण;
पूर्ण;

जोड़ hl_mem_args अणु
	काष्ठा hl_mem_in in;
	काष्ठा hl_mem_out out;
पूर्ण;

#घोषणा HL_DEBUG_MAX_AUX_VALUES		10

काष्ठा hl_debug_params_etr अणु
	/* Address in memory to allocate buffer */
	__u64 buffer_address;

	/* Size of buffer to allocate */
	__u64 buffer_size;

	/* Sink operation mode: SW fअगरo, HW fअगरo, Circular buffer */
	__u32 sink_mode;
	__u32 pad;
पूर्ण;

काष्ठा hl_debug_params_etf अणु
	/* Address in memory to allocate buffer */
	__u64 buffer_address;

	/* Size of buffer to allocate */
	__u64 buffer_size;

	/* Sink operation mode: SW fअगरo, HW fअगरo, Circular buffer */
	__u32 sink_mode;
	__u32 pad;
पूर्ण;

काष्ठा hl_debug_params_sपंचांग अणु
	/* Two bit masks क्रम HW event and Stimulus Port */
	__u64 he_mask;
	__u64 sp_mask;

	/* Trace source ID */
	__u32 id;

	/* Frequency क्रम the बारtamp रेजिस्टर */
	__u32 frequency;
पूर्ण;

काष्ठा hl_debug_params_bmon अणु
	/* Two address ranges that the user can request to filter */
	__u64 start_addr0;
	__u64 addr_mask0;

	__u64 start_addr1;
	__u64 addr_mask1;

	/* Capture winकरोw configuration */
	__u32 bw_win;
	__u32 win_capture;

	/* Trace source ID */
	__u32 id;
	__u32 pad;
पूर्ण;

काष्ठा hl_debug_params_spmu अणु
	/* Event types selection */
	__u64 event_types[HL_DEBUG_MAX_AUX_VALUES];

	/* Number of event types selection */
	__u32 event_types_num;
	__u32 pad;
पूर्ण;

/* Opcode क्रम ETR component */
#घोषणा HL_DEBUG_OP_ETR		0
/* Opcode क्रम ETF component */
#घोषणा HL_DEBUG_OP_ETF		1
/* Opcode क्रम STM component */
#घोषणा HL_DEBUG_OP_STM		2
/* Opcode क्रम FUNNEL component */
#घोषणा HL_DEBUG_OP_FUNNEL	3
/* Opcode क्रम BMON component */
#घोषणा HL_DEBUG_OP_BMON	4
/* Opcode क्रम SPMU component */
#घोषणा HL_DEBUG_OP_SPMU	5
/* Opcode क्रम बारtamp (deprecated) */
#घोषणा HL_DEBUG_OP_TIMESTAMP	6
/* Opcode क्रम setting the device पूर्णांकo or out of debug mode. The enable
 * variable should be 1 क्रम enabling debug mode and 0 क्रम disabling it
 */
#घोषणा HL_DEBUG_OP_SET_MODE	7

काष्ठा hl_debug_args अणु
	/*
	 * Poपूर्णांकer to user input काष्ठाure.
	 * This field is relevant to specअगरic opcodes.
	 */
	__u64 input_ptr;
	/* Poपूर्णांकer to user output काष्ठाure */
	__u64 output_ptr;
	/* Size of user input काष्ठाure */
	__u32 input_size;
	/* Size of user output काष्ठाure */
	__u32 output_size;
	/* HL_DEBUG_OP_* */
	__u32 op;
	/*
	 * Register index in the component, taken from the debug_regs_index क्रमागत
	 * in the various ASIC header files
	 */
	__u32 reg_idx;
	/* Enable/disable */
	__u32 enable;
	/* Context ID - Currently not in use */
	__u32 ctx_id;
पूर्ण;

/*
 * Various inक्रमmation operations such as:
 * - H/W IP inक्रमmation
 * - Current dram usage
 *
 * The user calls this IOCTL with an opcode that describes the required
 * inक्रमmation. The user should supply a poपूर्णांकer to a user-allocated memory
 * chunk, which will be filled by the driver with the requested inक्रमmation.
 *
 * The user supplies the maximum amount of size to copy पूर्णांकo the user's memory,
 * in order to prevent data corruption in हाल of dअगरferences between the
 * definitions of काष्ठाures in kernel and userspace, e.g. in हाल of old
 * userspace and new kernel driver
 */
#घोषणा HL_IOCTL_INFO	\
		_IOWR('H', 0x01, काष्ठा hl_info_args)

/*
 * Command Buffer
 * - Request a Command Buffer
 * - Destroy a Command Buffer
 *
 * The command buffers are memory blocks that reside in DMA-able address
 * space and are physically contiguous so they can be accessed by the device
 * directly. They are allocated using the coherent DMA API.
 *
 * When creating a new CB, the IOCTL वापसs a handle of it, and the user-space
 * process needs to use that handle to mmap the buffer so it can access them.
 *
 * In some instances, the device must access the command buffer through the
 * device's MMU, and thus its memory should be mapped. In these हालs, user can
 * indicate the driver that such a mapping is required.
 * The resulting device भव address will be used पूर्णांकernally by the driver,
 * and won't be वापसed to user.
 *
 */
#घोषणा HL_IOCTL_CB		\
		_IOWR('H', 0x02, जोड़ hl_cb_args)

/*
 * Command Submission
 *
 * To submit work to the device, the user need to call this IOCTL with a set
 * of JOBS. That set of JOBS स्थिरitutes a CS object.
 * Each JOB will be enqueued on a specअगरic queue, according to the user's input.
 * There can be more then one JOB per queue.
 *
 * The CS IOCTL will receive two sets of JOBS. One set is क्रम "restore" phase
 * and a second set is क्रम "execution" phase.
 * The JOBS on the "restore" phase are enqueued only after context-चयन
 * (or अगर its the first CS क्रम this context). The user can also order the
 * driver to run the "restore" phase explicitly
 *
 * There are two types of queues - बाह्यal and पूर्णांकernal. External queues
 * are DMA queues which transfer data from/to the Host. All other queues are
 * पूर्णांकernal. The driver will get completion notअगरications from the device only
 * on JOBS which are enqueued in the बाह्यal queues.
 *
 * For jobs on बाह्यal queues, the user needs to create command buffers
 * through the CB ioctl and give the CB's handle to the CS ioctl. For jobs on
 * पूर्णांकernal queues, the user needs to prepare a "command buffer" with packets
 * on either the device SRAM/DRAM or the host, and give the device address of
 * that buffer to the CS ioctl.
 *
 * This IOCTL is asynchronous in regard to the actual execution of the CS. This
 * means it वापसs immediately after ALL the JOBS were enqueued on their
 * relevant queues. Thereक्रमe, the user mustn't assume the CS has been completed
 * or has even started to execute.
 *
 * Upon successful enqueue, the IOCTL वापसs a sequence number which the user
 * can use with the "Wait for CS" IOCTL to check whether the handle's CS
 * बाह्यal JOBS have been completed. Note that अगर the CS has पूर्णांकernal JOBS
 * which can execute AFTER the बाह्यal JOBS have finished, the driver might
 * report that the CS has finished executing BEFORE the पूर्णांकernal JOBS have
 * actually finished executing.
 *
 * Even though the sequence number increments per CS, the user can NOT
 * स्वतःmatically assume that अगर CS with sequence number N finished, then CS
 * with sequence number N-1 also finished. The user can make this assumption अगर
 * and only अगर CS N and CS N-1 are exactly the same (same CBs क्रम the same
 * queues).
 */
#घोषणा HL_IOCTL_CS			\
		_IOWR('H', 0x03, जोड़ hl_cs_args)

/*
 * Wait क्रम Command Submission
 *
 * The user can call this IOCTL with a handle it received from the CS IOCTL
 * to रुको until the handle's CS has finished executing. The user will रुको
 * inside the kernel until the CS has finished or until the user-requested
 * समयout has expired.
 *
 * If the समयout value is 0, the driver won't sleep at all. It will check
 * the status of the CS and वापस immediately
 *
 * The वापस value of the IOCTL is a standard Linux error code. The possible
 * values are:
 *
 * EINTR     - Kernel रुकोing has been पूर्णांकerrupted, e.g. due to OS संकेत
 *             that the user process received
 * ETIMEDOUT - The CS has caused a समयout on the device
 * EIO       - The CS was पातed (usually because the device was reset)
 * ENODEV    - The device wants to करो hard-reset (so user need to बंद FD)
 *
 * The driver also वापसs a custom define inside the IOCTL which can be:
 *
 * HL_WAIT_CS_STATUS_COMPLETED   - The CS has been completed successfully (0)
 * HL_WAIT_CS_STATUS_BUSY        - The CS is still executing (0)
 * HL_WAIT_CS_STATUS_TIMEDOUT    - The CS has caused a समयout on the device
 *                                 (ETIMEDOUT)
 * HL_WAIT_CS_STATUS_ABORTED     - The CS was पातed, usually because the
 *                                 device was reset (EIO)
 * HL_WAIT_CS_STATUS_INTERRUPTED - Waiting क्रम the CS was पूर्णांकerrupted (EINTR)
 *
 */

#घोषणा HL_IOCTL_WAIT_CS			\
		_IOWR('H', 0x04, जोड़ hl_रुको_cs_args)

/*
 * Memory
 * - Map host memory to device MMU
 * - Unmap host memory from device MMU
 *
 * This IOCTL allows the user to map host memory to the device MMU
 *
 * For host memory, the IOCTL करोesn't allocate memory. The user is supposed
 * to allocate the memory in user-space (दो_स्मृति/new). The driver pins the
 * physical pages (up to the allowed limit by the OS), assigns a भव
 * address in the device VA space and initializes the device MMU.
 *
 * There is an option क्रम the user to specअगरy the requested भव address.
 *
 */
#घोषणा HL_IOCTL_MEMORY		\
		_IOWR('H', 0x05, जोड़ hl_mem_args)

/*
 * Debug
 * - Enable/disable the ETR/ETF/FUNNEL/STM/BMON/SPMU debug traces
 *
 * This IOCTL allows the user to get debug traces from the chip.
 *
 * Beक्रमe the user can send configuration requests of the various
 * debug/profile engines, it needs to set the device पूर्णांकo debug mode.
 * This is because the debug/profile infraकाष्ठाure is shared component in the
 * device and we can't allow multiple users to access it at the same समय.
 *
 * Once a user set the device पूर्णांकo debug mode, the driver won't allow other
 * users to "work" with the device, i.e. खोलो a FD. If there are multiple users
 * खोलोed on the device, the driver won't allow any user to debug the device.
 *
 * For each configuration request, the user needs to provide the रेजिस्टर index
 * and essential data such as buffer address and size.
 *
 * Once the user has finished using the debug/profile engines, he should
 * set the device पूर्णांकo non-debug mode, i.e. disable debug mode.
 *
 * The driver can decide to "kick out" the user अगर he abuses this पूर्णांकerface.
 *
 */
#घोषणा HL_IOCTL_DEBUG		\
		_IOWR('H', 0x06, काष्ठा hl_debug_args)

#घोषणा HL_COMMAND_START	0x01
#घोषणा HL_COMMAND_END		0x07

#पूर्ण_अगर /* HABANALABS_H_ */
