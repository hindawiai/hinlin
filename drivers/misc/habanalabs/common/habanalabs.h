<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित HABANALABSP_H_
#घोषणा HABANALABSP_H_

#समावेश "../include/common/cpucp_if.h"
#समावेश "../include/common/qman_if.h"
#समावेश "../include/hw_ip/mmu/mmu_general.h"
#समावेश <uapi/misc/habanaद_असल.h>

#समावेश <linux/cdev.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/coresight.h>

#घोषणा HL_NAME				"habanalabs"

/* Use upper bits of mmap offset to store habana driver specअगरic inक्रमmation.
 * bits[63:61] - Encode mmap type
 * bits[45:0]  - mmap offset value
 *
 * NOTE: काष्ठा vm_area_काष्ठा.vm_pgoff uses offset in pages. Hence, these
 *  defines are w.r.t to PAGE_SIZE
 */
#घोषणा HL_MMAP_TYPE_SHIFT		(61 - PAGE_SHIFT)
#घोषणा HL_MMAP_TYPE_MASK		(0x7ull << HL_MMAP_TYPE_SHIFT)
#घोषणा HL_MMAP_TYPE_BLOCK		(0x4ull << HL_MMAP_TYPE_SHIFT)
#घोषणा HL_MMAP_TYPE_CB			(0x2ull << HL_MMAP_TYPE_SHIFT)

#घोषणा HL_MMAP_OFFSET_VALUE_MASK	(0x1FFFFFFFFFFFull >> PAGE_SHIFT)
#घोषणा HL_MMAP_OFFSET_VALUE_GET(off)	(off & HL_MMAP_OFFSET_VALUE_MASK)

#घोषणा HL_PENDING_RESET_PER_SEC	10
#घोषणा HL_PENDING_RESET_MAX_TRIALS	60 /* 10 minutes */
#घोषणा HL_PENDING_RESET_LONG_SEC	60

#घोषणा HL_HARD_RESET_MAX_TIMEOUT	120

#घोषणा HL_DEVICE_TIMEOUT_USEC		1000000 /* 1 s */

#घोषणा HL_HEARTBEAT_PER_USEC		5000000 /* 5 s */

#घोषणा HL_PLL_LOW_JOB_FREQ_USEC	5000000 /* 5 s */

#घोषणा HL_CPUCP_INFO_TIMEOUT_USEC	10000000 /* 10s */
#घोषणा HL_CPUCP_EEPROM_TIMEOUT_USEC	10000000 /* 10s */

#घोषणा HL_PCI_ELBI_TIMEOUT_MSEC	10 /* 10ms */

#घोषणा HL_SIM_MAX_TIMEOUT_US		10000000 /* 10s */

#घोषणा HL_COMMON_USER_INTERRUPT_ID	0xFFF

/* Memory */
#घोषणा MEM_HASH_TABLE_BITS		7 /* 1 << 7 buckets */

/* MMU */
#घोषणा MMU_HASH_TABLE_BITS		7 /* 1 << 7 buckets */

/**
 * क्रमागत hl_mmu_page_table_locaion - mmu page table location
 * @MMU_DR_PGT: page-table is located on device DRAM.
 * @MMU_HR_PGT: page-table is located on host memory.
 * @MMU_NUM_PGT_LOCATIONS: number of page-table locations currently supported.
 */
क्रमागत hl_mmu_page_table_location अणु
	MMU_DR_PGT = 0,		/* device-dram-resident MMU PGT */
	MMU_HR_PGT,		/* host resident MMU PGT */
	MMU_NUM_PGT_LOCATIONS	/* num of PGT locations */
पूर्ण;

/*
 * HL_RSVD_SOBS 'sync stream' reserved sync objects per QMAN stream
 * HL_RSVD_MONS 'sync stream' reserved monitors per QMAN stream
 */
#घोषणा HL_RSVD_SOBS			2
#घोषणा HL_RSVD_MONS			1

/*
 * HL_COLLECTIVE_RSVD_MSTR_MONS 'collective' reserved monitors per QMAN stream
 */
#घोषणा HL_COLLECTIVE_RSVD_MSTR_MONS	2

#घोषणा HL_MAX_SOB_VAL			(1 << 15)

#घोषणा IS_POWER_OF_2(n)		(n != 0 && ((n & (n - 1)) == 0))
#घोषणा IS_MAX_PENDING_CS_VALID(n)	(IS_POWER_OF_2(n) && (n > 1))

#घोषणा HL_PCI_NUM_BARS			6

#घोषणा HL_MAX_DCORES			4

/*
 * Reset Flags
 *
 * - HL_RESET_HARD
 *       If set करो hard reset to all engines. If not set reset just
 *       compute/DMA engines.
 *
 * - HL_RESET_FROM_RESET_THREAD
 *       Set अगर the caller is the hard-reset thपढ़ो
 *
 * - HL_RESET_HEARTBEAT
 *       Set अगर reset is due to heartbeat
 */
#घोषणा HL_RESET_HARD			(1 << 0)
#घोषणा HL_RESET_FROM_RESET_THREAD	(1 << 1)
#घोषणा HL_RESET_HEARTBEAT		(1 << 2)

#घोषणा HL_MAX_SOBS_PER_MONITOR	8

/**
 * काष्ठा hl_gen_रुको_properties - properties क्रम generating a रुको CB
 * @data: command buffer
 * @q_idx: queue id is used to extract fence रेजिस्टर address
 * @size: offset in command buffer
 * @sob_base: SOB base to use in this रुको CB
 * @sob_val: SOB value to रुको क्रम
 * @mon_id: monitor to use in this रुको CB
 * @sob_mask: each bit represents a SOB offset from sob_base to be used
 */
काष्ठा hl_gen_रुको_properties अणु
	व्योम	*data;
	u32	q_idx;
	u32	size;
	u16	sob_base;
	u16	sob_val;
	u16	mon_id;
	u8	sob_mask;
पूर्ण;

/**
 * काष्ठा pgt_info - MMU hop page info.
 * @node: hash linked-list node क्रम the pgts shaकरोw hash of pgts.
 * @phys_addr: physical address of the pgt.
 * @shaकरोw_addr: shaकरोw hop in the host.
 * @ctx: poपूर्णांकer to the owner ctx.
 * @num_of_ptes: indicates how many ptes are used in the pgt.
 *
 * The MMU page tables hierarchy is placed on the DRAM. When a new level (hop)
 * is needed during mapping, a new page is allocated and this काष्ठाure holds
 * its essential inक्रमmation. During unmapping, अगर no valid PTEs reमुख्यed in the
 * page, it is मुक्तd with its pgt_info काष्ठाure.
 */
काष्ठा pgt_info अणु
	काष्ठा hlist_node	node;
	u64			phys_addr;
	u64			shaकरोw_addr;
	काष्ठा hl_ctx		*ctx;
	पूर्णांक			num_of_ptes;
पूर्ण;

काष्ठा hl_device;
काष्ठा hl_fpriv;

/**
 * क्रमागत hl_pci_match_mode - pci match mode per region
 * @PCI_ADDRESS_MATCH_MODE: address match mode
 * @PCI_BAR_MATCH_MODE: bar match mode
 */
क्रमागत hl_pci_match_mode अणु
	PCI_ADDRESS_MATCH_MODE,
	PCI_BAR_MATCH_MODE
पूर्ण;

/**
 * क्रमागत hl_fw_component - F/W components to पढ़ो version through रेजिस्टरs.
 * @FW_COMP_UBOOT: u-boot.
 * @FW_COMP_PREBOOT: preboot.
 */
क्रमागत hl_fw_component अणु
	FW_COMP_UBOOT,
	FW_COMP_PREBOOT
पूर्ण;

/**
 * क्रमागत hl_fw_types - F/W types present in the प्रणाली
 * @FW_TYPE_LINUX: Linux image क्रम device CPU
 * @FW_TYPE_BOOT_CPU: Boot image क्रम device CPU
 * @FW_TYPE_PREBOOT_CPU: Indicates pre-loaded CPUs are present in the प्रणाली
 *                       (preboot, ppboot etc...)
 * @FW_TYPE_ALL_TYPES: Mask क्रम all types
 */
क्रमागत hl_fw_types अणु
	FW_TYPE_LINUX = 0x1,
	FW_TYPE_BOOT_CPU = 0x2,
	FW_TYPE_PREBOOT_CPU = 0x4,
	FW_TYPE_ALL_TYPES =
		(FW_TYPE_LINUX | FW_TYPE_BOOT_CPU | FW_TYPE_PREBOOT_CPU)
पूर्ण;

/**
 * क्रमागत hl_queue_type - Supported QUEUE types.
 * @QUEUE_TYPE_NA: queue is not available.
 * @QUEUE_TYPE_EXT: बाह्यal queue which is a DMA channel that may access the
 *                  host.
 * @QUEUE_TYPE_INT: पूर्णांकernal queue that perक्रमms DMA inside the device's
 *			memories and/or operates the compute engines.
 * @QUEUE_TYPE_CPU: S/W queue क्रम communication with the device's CPU.
 * @QUEUE_TYPE_HW: queue of DMA and compute engines jobs, क्रम which completion
 *                 notअगरications are sent by H/W.
 */
क्रमागत hl_queue_type अणु
	QUEUE_TYPE_NA,
	QUEUE_TYPE_EXT,
	QUEUE_TYPE_INT,
	QUEUE_TYPE_CPU,
	QUEUE_TYPE_HW
पूर्ण;

क्रमागत hl_cs_type अणु
	CS_TYPE_DEFAULT,
	CS_TYPE_SIGNAL,
	CS_TYPE_WAIT,
	CS_TYPE_COLLECTIVE_WAIT
पूर्ण;

/*
 * काष्ठा hl_inbound_pci_region - inbound region descriptor
 * @mode: pci match mode क्रम this region
 * @addr: region target address
 * @size: region size in bytes
 * @offset_in_bar: offset within bar (address match mode)
 * @bar: bar id
 */
काष्ठा hl_inbound_pci_region अणु
	क्रमागत hl_pci_match_mode	mode;
	u64			addr;
	u64			size;
	u64			offset_in_bar;
	u8			bar;
पूर्ण;

/*
 * काष्ठा hl_outbound_pci_region - outbound region descriptor
 * @addr: region target address
 * @size: region size in bytes
 */
काष्ठा hl_outbound_pci_region अणु
	u64	addr;
	u64	size;
पूर्ण;

/*
 * क्रमागत queue_cb_alloc_flags - Indicates queue support क्रम CBs that
 * allocated by Kernel or by User
 * @CB_ALLOC_KERNEL: support only CBs that allocated by Kernel
 * @CB_ALLOC_USER: support only CBs that allocated by User
 */
क्रमागत queue_cb_alloc_flags अणु
	CB_ALLOC_KERNEL = 0x1,
	CB_ALLOC_USER   = 0x2
पूर्ण;

/*
 * काष्ठा hl_hw_sob - H/W SOB info.
 * @hdev: habanaद_असल device काष्ठाure.
 * @kref: refcount of this SOB. The SOB will reset once the refcount is zero.
 * @sob_id: id of this SOB.
 * @q_idx: the H/W queue that uses this SOB.
 */
काष्ठा hl_hw_sob अणु
	काष्ठा hl_device	*hdev;
	काष्ठा kref		kref;
	u32			sob_id;
	u32			q_idx;
पूर्ण;

क्रमागत hl_collective_mode अणु
	HL_COLLECTIVE_NOT_SUPPORTED = 0x0,
	HL_COLLECTIVE_MASTER = 0x1,
	HL_COLLECTIVE_SLAVE = 0x2
पूर्ण;

/**
 * काष्ठा hw_queue_properties - queue inक्रमmation.
 * @type: queue type.
 * @queue_cb_alloc_flags: biपंचांगap which indicates अगर the hw queue supports CB
 *                        that allocated by the Kernel driver and thereक्रमe,
 *                        a CB handle can be provided क्रम jobs on this queue.
 *                        Otherwise, a CB address must be provided.
 * @collective_mode: collective mode of current queue
 * @driver_only: true अगर only the driver is allowed to send a job to this queue,
 *               false otherwise.
 * @supports_sync_stream: True अगर queue supports sync stream
 */
काष्ठा hw_queue_properties अणु
	क्रमागत hl_queue_type	type;
	क्रमागत queue_cb_alloc_flags cb_alloc_flags;
	क्रमागत hl_collective_mode	collective_mode;
	u8			driver_only;
	u8			supports_sync_stream;
पूर्ण;

/**
 * क्रमागत vm_type_t - भव memory mapping request inक्रमmation.
 * @VM_TYPE_USERPTR: mapping of user memory to device भव address.
 * @VM_TYPE_PHYS_PACK: mapping of DRAM memory to device भव address.
 */
क्रमागत vm_type_t अणु
	VM_TYPE_USERPTR = 0x1,
	VM_TYPE_PHYS_PACK = 0x2
पूर्ण;

/**
 * क्रमागत hl_device_hw_state - H/W device state. use this to understand whether
 *                           to करो reset beक्रमe hw_init or not
 * @HL_DEVICE_HW_STATE_CLEAN: H/W state is clean. i.e. after hard reset
 * @HL_DEVICE_HW_STATE_सूचीTY: H/W state is dirty. i.e. we started to execute
 *                            hw_init
 */
क्रमागत hl_device_hw_state अणु
	HL_DEVICE_HW_STATE_CLEAN = 0,
	HL_DEVICE_HW_STATE_सूचीTY
पूर्ण;

#घोषणा HL_MMU_VA_ALIGNMENT_NOT_NEEDED 0

/**
 * काष्ठा hl_mmu_properties - ASIC specअगरic MMU address translation properties.
 * @start_addr: भव start address of the memory region.
 * @end_addr: भव end address of the memory region.
 * @hop0_shअगरt: shअगरt of hop 0 mask.
 * @hop1_shअगरt: shअगरt of hop 1 mask.
 * @hop2_shअगरt: shअगरt of hop 2 mask.
 * @hop3_shअगरt: shअगरt of hop 3 mask.
 * @hop4_shअगरt: shअगरt of hop 4 mask.
 * @hop5_shअगरt: shअगरt of hop 5 mask.
 * @hop0_mask: mask to get the PTE address in hop 0.
 * @hop1_mask: mask to get the PTE address in hop 1.
 * @hop2_mask: mask to get the PTE address in hop 2.
 * @hop3_mask: mask to get the PTE address in hop 3.
 * @hop4_mask: mask to get the PTE address in hop 4.
 * @hop5_mask: mask to get the PTE address in hop 5.
 * @page_size: शेष page size used to allocate memory.
 * @num_hops: The amount of hops supported by the translation table.
 * @host_resident: Should the MMU page table reside in host memory or in the
 *                 device DRAM.
 */
काष्ठा hl_mmu_properties अणु
	u64	start_addr;
	u64	end_addr;
	u64	hop0_shअगरt;
	u64	hop1_shअगरt;
	u64	hop2_shअगरt;
	u64	hop3_shअगरt;
	u64	hop4_shअगरt;
	u64	hop5_shअगरt;
	u64	hop0_mask;
	u64	hop1_mask;
	u64	hop2_mask;
	u64	hop3_mask;
	u64	hop4_mask;
	u64	hop5_mask;
	u32	page_size;
	u32	num_hops;
	u8	host_resident;
पूर्ण;

/**
 * काष्ठा asic_fixed_properties - ASIC specअगरic immutable properties.
 * @hw_queues_props: H/W queues properties.
 * @cpucp_info: received various inक्रमmation from CPU-CP regarding the H/W, e.g.
 *		available sensors.
 * @uboot_ver: F/W U-boot version.
 * @preboot_ver: F/W Preboot version.
 * @dmmu: DRAM MMU address translation properties.
 * @pmmu: PCI (host) MMU address translation properties.
 * @pmmu_huge: PCI (host) MMU address translation properties क्रम memory
 *              allocated with huge pages.
 * @sram_base_address: SRAM physical start address.
 * @sram_end_address: SRAM physical end address.
 * @sram_user_base_address - SRAM physical start address क्रम user access.
 * @dram_base_address: DRAM physical start address.
 * @dram_end_address: DRAM physical end address.
 * @dram_user_base_address: DRAM physical start address क्रम user access.
 * @dram_size: DRAM total size.
 * @dram_pci_bar_size: size of PCI bar towards DRAM.
 * @max_घातer_शेष: max घातer of the device after reset
 * @dc_घातer_शेष: घातer consumed by the device in mode idle.
 * @dram_size_क्रम_शेष_page_mapping: DRAM size needed to map to aव्योम page
 *                                      fault.
 * @pcie_dbi_base_address: Base address of the PCIE_DBI block.
 * @pcie_aux_dbi_reg_addr: Address of the PCIE_AUX DBI रेजिस्टर.
 * @mmu_pgt_addr: base physical address in DRAM of MMU page tables.
 * @mmu_dram_शेष_page_addr: DRAM शेष page physical address.
 * @cb_बहु_शुरू_addr: भव start address of command buffers which are mapped
 *                    to the device's MMU.
 * @cb_बहु_पूर्ण_addr: भव end address of command buffers which are mapped to
 *                  the device's MMU.
 * @mmu_pgt_size: MMU page tables total size.
 * @mmu_pte_size: PTE size in MMU page tables.
 * @mmu_hop_table_size: MMU hop table size.
 * @mmu_hop0_tables_total_size: total size of MMU hop0 tables.
 * @dram_page_size: page size क्रम MMU DRAM allocation.
 * @cfg_size: configuration space size on SRAM.
 * @sram_size: total size of SRAM.
 * @max_asid: maximum number of खोलो contexts (ASIDs).
 * @num_of_events: number of possible पूर्णांकernal H/W IRQs.
 * @psoc_pci_pll_nr: PCI PLL NR value.
 * @psoc_pci_pll_nf: PCI PLL NF value.
 * @psoc_pci_pll_od: PCI PLL OD value.
 * @psoc_pci_pll_भाग_factor: PCI PLL DIV FACTOR 1 value.
 * @psoc_बारtamp_frequency: frequency of the psoc बारtamp घड़ी.
 * @high_pll: high PLL frequency used by the device.
 * @cb_pool_cb_cnt: number of CBs in the CB pool.
 * @cb_pool_cb_size: size of each CB in the CB pool.
 * @max_pending_cs: maximum of concurrent pending command submissions
 * @max_queues: maximum amount of queues in the प्रणाली
 * @fw_boot_cpu_security_map: biपंचांगap representation of boot cpu security status
 *                            reported by FW, bit description can be found in
 *                            CPU_BOOT_DEV_STS*
 * @fw_app_security_map: biपंचांगap representation of application security status
 *                       reported by FW, bit description can be found in
 *                       CPU_BOOT_DEV_STS*
 * @collective_first_sob: first sync object available क्रम collective use
 * @collective_first_mon: first monitor available क्रम collective use
 * @sync_stream_first_sob: first sync object available क्रम sync stream use
 * @sync_stream_first_mon: first monitor available क्रम sync stream use
 * @first_available_user_sob: first sob available क्रम the user
 * @first_available_user_mon: first monitor available क्रम the user
 * @first_available_user_msix_पूर्णांकerrupt: first available msix पूर्णांकerrupt
 *                                       reserved क्रम the user
 * @first_available_cq: first available CQ क्रम the user.
 * @user_पूर्णांकerrupt_count: number of user पूर्णांकerrupts.
 * @tpc_enabled_mask: which TPCs are enabled.
 * @completion_queues_count: number of completion queues.
 * @fw_security_disabled: true अगर security measures are disabled in firmware,
 *                        false otherwise
 * @fw_security_status_valid: security status bits are valid and can be fetched
 *                            from BOOT_DEV_STS0
 * @dram_supports_भव_memory: is there an MMU towards the DRAM
 * @hard_reset_करोne_by_fw: true अगर firmware is handling hard reset flow
 * @num_functional_hbms: number of functional HBMs in each DCORE.
 * @iatu_करोne_by_fw: true अगर iATU configuration is being करोne by FW.
 */
काष्ठा asic_fixed_properties अणु
	काष्ठा hw_queue_properties	*hw_queues_props;
	काष्ठा cpucp_info		cpucp_info;
	अक्षर				uboot_ver[VERSION_MAX_LEN];
	अक्षर				preboot_ver[VERSION_MAX_LEN];
	काष्ठा hl_mmu_properties	dmmu;
	काष्ठा hl_mmu_properties	pmmu;
	काष्ठा hl_mmu_properties	pmmu_huge;
	u64				sram_base_address;
	u64				sram_end_address;
	u64				sram_user_base_address;
	u64				dram_base_address;
	u64				dram_end_address;
	u64				dram_user_base_address;
	u64				dram_size;
	u64				dram_pci_bar_size;
	u64				max_घातer_शेष;
	u64				dc_घातer_शेष;
	u64				dram_size_क्रम_शेष_page_mapping;
	u64				pcie_dbi_base_address;
	u64				pcie_aux_dbi_reg_addr;
	u64				mmu_pgt_addr;
	u64				mmu_dram_शेष_page_addr;
	u64				cb_बहु_शुरू_addr;
	u64				cb_बहु_पूर्ण_addr;
	u32				mmu_pgt_size;
	u32				mmu_pte_size;
	u32				mmu_hop_table_size;
	u32				mmu_hop0_tables_total_size;
	u32				dram_page_size;
	u32				cfg_size;
	u32				sram_size;
	u32				max_asid;
	u32				num_of_events;
	u32				psoc_pci_pll_nr;
	u32				psoc_pci_pll_nf;
	u32				psoc_pci_pll_od;
	u32				psoc_pci_pll_भाग_factor;
	u32				psoc_बारtamp_frequency;
	u32				high_pll;
	u32				cb_pool_cb_cnt;
	u32				cb_pool_cb_size;
	u32				max_pending_cs;
	u32				max_queues;
	u32				fw_boot_cpu_security_map;
	u32				fw_app_security_map;
	u16				collective_first_sob;
	u16				collective_first_mon;
	u16				sync_stream_first_sob;
	u16				sync_stream_first_mon;
	u16				first_available_user_sob[HL_MAX_DCORES];
	u16				first_available_user_mon[HL_MAX_DCORES];
	u16				first_available_user_msix_पूर्णांकerrupt;
	u16				first_available_cq[HL_MAX_DCORES];
	u16				user_पूर्णांकerrupt_count;
	u8				tpc_enabled_mask;
	u8				completion_queues_count;
	u8				fw_security_disabled;
	u8				fw_security_status_valid;
	u8				dram_supports_भव_memory;
	u8				hard_reset_करोne_by_fw;
	u8				num_functional_hbms;
	u8				iatu_करोne_by_fw;
पूर्ण;

/**
 * काष्ठा hl_fence - software synchronization primitive
 * @completion: fence is implemented using completion
 * @refcount: refcount क्रम this fence
 * @cs_sequence: sequence of the corresponding command submission
 * @error: mark this fence with error
 * @बारtamp: बारtamp upon completion
 *
 */
काष्ठा hl_fence अणु
	काष्ठा completion	completion;
	काष्ठा kref		refcount;
	u64			cs_sequence;
	पूर्णांक			error;
	kसमय_प्रकार			बारtamp;
पूर्ण;

/**
 * काष्ठा hl_cs_compl - command submission completion object.
 * @sob_reset_work: workqueue object to run SOB reset flow.
 * @base_fence: hl fence object.
 * @lock: spinlock to protect fence.
 * @hdev: habanaद_असल device काष्ठाure.
 * @hw_sob: the H/W SOB used in this संकेत/रुको CS.
 * @cs_seq: command submission sequence number.
 * @type: type of the CS - संकेत/रुको.
 * @sob_val: the SOB value that is used in this संकेत/रुको CS.
 * @sob_group: the SOB group that is used in this collective रुको CS.
 */
काष्ठा hl_cs_compl अणु
	काष्ठा work_काष्ठा	sob_reset_work;
	काष्ठा hl_fence		base_fence;
	spinlock_t		lock;
	काष्ठा hl_device	*hdev;
	काष्ठा hl_hw_sob	*hw_sob;
	u64			cs_seq;
	क्रमागत hl_cs_type		type;
	u16			sob_val;
	u16			sob_group;
पूर्ण;

/*
 * Command Buffers
 */

/**
 * काष्ठा hl_cb_mgr - describes a Command Buffer Manager.
 * @cb_lock: protects cb_handles.
 * @cb_handles: an idr to hold all command buffer handles.
 */
काष्ठा hl_cb_mgr अणु
	spinlock_t		cb_lock;
	काष्ठा idr		cb_handles; /* रक्षित by cb_lock */
पूर्ण;

/**
 * काष्ठा hl_cb - describes a Command Buffer.
 * @refcount: reference counter क्रम usage of the CB.
 * @hdev: poपूर्णांकer to device this CB beदीर्घs to.
 * @ctx: poपूर्णांकer to the CB owner's context.
 * @lock: spinlock to protect mmap flows.
 * @debugfs_list: node in debugfs list of command buffers.
 * @pool_list: node in pool list of command buffers.
 * @va_block_list: list of भव addresses blocks of the CB अगर it is mapped to
 *                 the device's MMU.
 * @id: the CB's ID.
 * @kernel_address: Holds the CB's kernel भव address.
 * @bus_address: Holds the CB's DMA address.
 * @mmap_size: Holds the CB's size that was mmaped.
 * @size: holds the CB's size.
 * @cs_cnt: holds number of CS that this CB participates in.
 * @mmap: true अगर the CB is currently mmaped to user.
 * @is_pool: true अगर CB was acquired from the pool, false otherwise.
 * @is_पूर्णांकernal: पूर्णांकernaly allocated
 * @is_mmu_mapped: true अगर the CB is mapped to the device's MMU.
 */
काष्ठा hl_cb अणु
	काष्ठा kref		refcount;
	काष्ठा hl_device	*hdev;
	काष्ठा hl_ctx		*ctx;
	spinlock_t		lock;
	काष्ठा list_head	debugfs_list;
	काष्ठा list_head	pool_list;
	काष्ठा list_head	va_block_list;
	u64			id;
	व्योम			*kernel_address;
	dma_addr_t		bus_address;
	u32			mmap_size;
	u32			size;
	atomic_t		cs_cnt;
	u8			mmap;
	u8			is_pool;
	u8			is_पूर्णांकernal;
	u8			is_mmu_mapped;
पूर्ण;


/*
 * QUEUES
 */

काष्ठा hl_cs;
काष्ठा hl_cs_job;

/* Queue length of बाह्यal and HW queues */
#घोषणा HL_QUEUE_LENGTH			4096
#घोषणा HL_QUEUE_SIZE_IN_BYTES		(HL_QUEUE_LENGTH * HL_BD_SIZE)

#अगर (HL_MAX_JOBS_PER_CS > HL_QUEUE_LENGTH)
#त्रुटि "HL_QUEUE_LENGTH must be greater than HL_MAX_JOBS_PER_CS"
#पूर्ण_अगर

/* HL_CQ_LENGTH is in units of काष्ठा hl_cq_entry */
#घोषणा HL_CQ_LENGTH			HL_QUEUE_LENGTH
#घोषणा HL_CQ_SIZE_IN_BYTES		(HL_CQ_LENGTH * HL_CQ_ENTRY_SIZE)

/* Must be घातer of 2 */
#घोषणा HL_EQ_LENGTH			64
#घोषणा HL_EQ_SIZE_IN_BYTES		(HL_EQ_LENGTH * HL_EQ_ENTRY_SIZE)

/* Host <-> CPU-CP shared memory size */
#घोषणा HL_CPU_ACCESSIBLE_MEM_SIZE	SZ_2M

/**
 * काष्ठा hl_sync_stream_properties -
 *     describes a H/W queue sync stream properties
 * @hw_sob: array of the used H/W SOBs by this H/W queue.
 * @next_sob_val: the next value to use क्रम the currently used SOB.
 * @base_sob_id: the base SOB id of the SOBs used by this queue.
 * @base_mon_id: the base MON id of the MONs used by this queue.
 * @collective_mstr_mon_id: the MON ids of the MONs used by this master queue
 *                          in order to sync with all slave queues.
 * @collective_slave_mon_id: the MON id used by this slave queue in order to
 *                           sync with its master queue.
 * @collective_sob_id: current SOB id used by this collective slave queue
 *                     to संकेत its collective master queue upon completion.
 * @curr_sob_offset: the id offset to the currently used SOB from the
 *                   HL_RSVD_SOBS that are being used by this queue.
 */
काष्ठा hl_sync_stream_properties अणु
	काष्ठा hl_hw_sob hw_sob[HL_RSVD_SOBS];
	u16		next_sob_val;
	u16		base_sob_id;
	u16		base_mon_id;
	u16		collective_mstr_mon_id[HL_COLLECTIVE_RSVD_MSTR_MONS];
	u16		collective_slave_mon_id;
	u16		collective_sob_id;
	u8		curr_sob_offset;
पूर्ण;

/**
 * काष्ठा hl_hw_queue - describes a H/W transport queue.
 * @shaकरोw_queue: poपूर्णांकer to a shaकरोw queue that holds poपूर्णांकers to jobs.
 * @sync_stream_prop: sync stream queue properties
 * @queue_type: type of queue.
 * @collective_mode: collective mode of current queue
 * @kernel_address: holds the queue's kernel भव address.
 * @bus_address: holds the queue's DMA address.
 * @pi: holds the queue's pi value.
 * @ci: holds the queue's ci value, AS CALCULATED BY THE DRIVER (not real ci).
 * @hw_queue_id: the id of the H/W queue.
 * @cq_id: the id क्रम the corresponding CQ क्रम this H/W queue.
 * @msi_vec: the IRQ number of the H/W queue.
 * @पूर्णांक_queue_len: length of पूर्णांकernal queue (number of entries).
 * @valid: is the queue valid (we have array of 32 queues, not all of them
 *         exist).
 * @supports_sync_stream: True अगर queue supports sync stream
 */
काष्ठा hl_hw_queue अणु
	काष्ठा hl_cs_job			**shaकरोw_queue;
	काष्ठा hl_sync_stream_properties	sync_stream_prop;
	क्रमागत hl_queue_type			queue_type;
	क्रमागत hl_collective_mode			collective_mode;
	व्योम					*kernel_address;
	dma_addr_t				bus_address;
	u32					pi;
	atomic_t				ci;
	u32					hw_queue_id;
	u32					cq_id;
	u32					msi_vec;
	u16					पूर्णांक_queue_len;
	u8					valid;
	u8					supports_sync_stream;
पूर्ण;

/**
 * काष्ठा hl_cq - describes a completion queue
 * @hdev: poपूर्णांकer to the device काष्ठाure
 * @kernel_address: holds the queue's kernel भव address
 * @bus_address: holds the queue's DMA address
 * @cq_idx: completion queue index in array
 * @hw_queue_id: the id of the matching H/W queue
 * @ci: ci inside the queue
 * @pi: pi inside the queue
 * @मुक्त_slots_cnt: counter of मुक्त slots in queue
 */
काष्ठा hl_cq अणु
	काष्ठा hl_device	*hdev;
	व्योम			*kernel_address;
	dma_addr_t		bus_address;
	u32			cq_idx;
	u32			hw_queue_id;
	u32			ci;
	u32			pi;
	atomic_t		मुक्त_slots_cnt;
पूर्ण;

/**
 * काष्ठा hl_user_पूर्णांकerrupt - holds user पूर्णांकerrupt inक्रमmation
 * @hdev: poपूर्णांकer to the device काष्ठाure
 * @रुको_list_head: head to the list of user thपढ़ोs pending on this पूर्णांकerrupt
 * @रुको_list_lock: protects रुको_list_head
 * @पूर्णांकerrupt_id: msix पूर्णांकerrupt id
 */
काष्ठा hl_user_पूर्णांकerrupt अणु
	काष्ठा hl_device	*hdev;
	काष्ठा list_head	रुको_list_head;
	spinlock_t		रुको_list_lock;
	u32			पूर्णांकerrupt_id;
पूर्ण;

/**
 * काष्ठा hl_user_pending_पूर्णांकerrupt - holds a context to a user thपढ़ो
 *                                    pending on an पूर्णांकerrupt
 * @रुको_list_node: node in the list of user thपढ़ोs pending on an पूर्णांकerrupt
 * @fence: hl fence object क्रम पूर्णांकerrupt completion
 */
काष्ठा hl_user_pending_पूर्णांकerrupt अणु
	काष्ठा list_head	रुको_list_node;
	काष्ठा hl_fence		fence;
पूर्ण;

/**
 * काष्ठा hl_eq - describes the event queue (single one per device)
 * @hdev: poपूर्णांकer to the device काष्ठाure
 * @kernel_address: holds the queue's kernel भव address
 * @bus_address: holds the queue's DMA address
 * @ci: ci inside the queue
 */
काष्ठा hl_eq अणु
	काष्ठा hl_device	*hdev;
	व्योम			*kernel_address;
	dma_addr_t		bus_address;
	u32			ci;
पूर्ण;


/*
 * ASICs
 */

/**
 * क्रमागत hl_asic_type - supported ASIC types.
 * @ASIC_INVALID: Invalid ASIC type.
 * @ASIC_GOYA: Goya device.
 * @ASIC_GAUDI: Gaudi device.
 * @ASIC_GAUDI_SEC: Gaudi secured device (HL-2000).
 */
क्रमागत hl_asic_type अणु
	ASIC_INVALID,
	ASIC_GOYA,
	ASIC_GAUDI,
	ASIC_GAUDI_SEC
पूर्ण;

काष्ठा hl_cs_parser;

/**
 * क्रमागत hl_pm_mng_profile - घातer management profile.
 * @PM_AUTO: पूर्णांकernal घड़ी is set by the Linux driver.
 * @PM_MANUAL: पूर्णांकernal घड़ी is set by the user.
 * @PM_LAST: last घातer management type.
 */
क्रमागत hl_pm_mng_profile अणु
	PM_AUTO = 1,
	PM_MANUAL,
	PM_LAST
पूर्ण;

/**
 * क्रमागत hl_pll_frequency - PLL frequency.
 * @PLL_HIGH: high frequency.
 * @PLL_LOW: low frequency.
 * @PLL_LAST: last frequency values that were configured by the user.
 */
क्रमागत hl_pll_frequency अणु
	PLL_HIGH = 1,
	PLL_LOW,
	PLL_LAST
पूर्ण;

#घोषणा PLL_REF_CLK 50

क्रमागत भाग_select_defs अणु
	DIV_SEL_REF_CLK = 0,
	DIV_SEL_PLL_CLK = 1,
	DIV_SEL_DIVIDED_REF = 2,
	DIV_SEL_DIVIDED_PLL = 3,
पूर्ण;

/**
 * काष्ठा hl_asic_funcs - ASIC specअगरic functions that are can be called from
 *                        common code.
 * @early_init: sets up early driver state (pre sw_init), करोesn't configure H/W.
 * @early_fini: tears करोwn what was करोne in early_init.
 * @late_init: sets up late driver/hw state (post hw_init) - Optional.
 * @late_fini: tears करोwn what was करोne in late_init (pre hw_fini) - Optional.
 * @sw_init: sets up driver state, करोes not configure H/W.
 * @sw_fini: tears करोwn driver state, करोes not configure H/W.
 * @hw_init: sets up the H/W state.
 * @hw_fini: tears करोwn the H/W state.
 * @halt_engines: halt engines, needed क्रम reset sequence. This also disables
 *                पूर्णांकerrupts from the device. Should be called beक्रमe
 *                hw_fini and beक्रमe CS rollback.
 * @suspend: handles IP specअगरic H/W or SW changes क्रम suspend.
 * @resume: handles IP specअगरic H/W or SW changes क्रम resume.
 * @cb_mmap: maps a CB.
 * @ring_करोorbell: increment PI on a given QMAN.
 * @pqe_ग_लिखो: Write the PQ entry to the PQ. This is ASIC-specअगरic
 *             function because the PQs are located in dअगरferent memory areas
 *             per ASIC (SRAM, DRAM, Host memory) and thereक्रमe, the method of
 *             writing the PQE must match the destination memory area
 *             properties.
 * @asic_dma_alloc_coherent: Allocate coherent DMA memory by calling
 *                           dma_alloc_coherent(). This is ASIC function because
 *                           its implementation is not trivial when the driver
 *                           is loaded in simulation mode (not upstreamed).
 * @asic_dma_मुक्त_coherent:  Free coherent DMA memory by calling
 *                           dma_मुक्त_coherent(). This is ASIC function because
 *                           its implementation is not trivial when the driver
 *                           is loaded in simulation mode (not upstreamed).
 * @scrub_device_mem: Scrub device memory given an address and size
 * @get_पूर्णांक_queue_base: get the पूर्णांकernal queue base address.
 * @test_queues: run simple test on all queues क्रम sanity check.
 * @asic_dma_pool_zalloc: small DMA allocation of coherent memory from DMA pool.
 *                        size of allocation is HL_DMA_POOL_BLK_SIZE.
 * @asic_dma_pool_मुक्त: मुक्त small DMA allocation from pool.
 * @cpu_accessible_dma_pool_alloc: allocate CPU PQ packet from DMA pool.
 * @cpu_accessible_dma_pool_मुक्त: मुक्त CPU PQ packet from DMA pool.
 * @hl_dma_unmap_sg: DMA unmap scatter-gather list.
 * @cs_parser: parse Command Submission.
 * @asic_dma_map_sg: DMA map scatter-gather list.
 * @get_dma_desc_list_size: get number of LIN_DMA packets required क्रम CB.
 * @add_end_of_cb_packets: Add packets to the end of CB, अगर device requires it.
 * @update_eq_ci: update event queue CI.
 * @context_चयन: called upon ASID context चयन.
 * @restore_phase_topology: clear all SOBs amd MONs.
 * @debugfs_पढ़ो32: debug पूर्णांकerface क्रम पढ़ोing u32 from DRAM/SRAM/Host memory.
 * @debugfs_ग_लिखो32: debug पूर्णांकerface क्रम writing u32 to DRAM/SRAM/Host memory.
 * @debugfs_पढ़ो64: debug पूर्णांकerface क्रम पढ़ोing u64 from DRAM/SRAM/Host memory.
 * @debugfs_ग_लिखो64: debug पूर्णांकerface क्रम writing u64 to DRAM/SRAM/Host memory.
 * @debugfs_पढ़ो_dma: debug पूर्णांकerface क्रम पढ़ोing up to 2MB from the device's
 *                    पूर्णांकernal memory via DMA engine.
 * @add_device_attr: add ASIC specअगरic device attributes.
 * @handle_eqe: handle event queue entry (IRQ) from CPU-CP.
 * @set_pll_profile: change PLL profile (manual/स्वतःmatic).
 * @get_events_stat: retrieve event queue entries histogram.
 * @पढ़ो_pte: पढ़ो MMU page table entry from DRAM.
 * @ग_लिखो_pte: ग_लिखो MMU page table entry to DRAM.
 * @mmu_invalidate_cache: flush MMU STLB host/DRAM cache, either with soft
 *                        (L1 only) or hard (L0 & L1) flush.
 * @mmu_invalidate_cache_range: flush specअगरic MMU STLB cache lines with
 *                              ASID-VA-size mask.
 * @send_heartbeat: send is-alive packet to CPU-CP and verअगरy response.
 * @set_घड़ी_gating: enable/disable घड़ी gating per engine according to
 *                    घड़ी gating mask in hdev
 * @disable_घड़ी_gating: disable घड़ी gating completely
 * @debug_coresight: perक्रमm certain actions on Coresight क्रम debugging.
 * @is_device_idle: वापस true अगर device is idle, false otherwise.
 * @soft_reset_late_init: perक्रमm certain actions needed after soft reset.
 * @hw_queues_lock: acquire H/W queues lock.
 * @hw_queues_unlock: release H/W queues lock.
 * @get_pci_id: retrieve PCI ID.
 * @get_eeprom_data: retrieve EEPROM data from F/W.
 * @send_cpu_message: send message to F/W. If the message is समयकरोut, the
 *                    driver will eventually reset the device. The समयout can
 *                    be determined by the calling function or it can be 0 and
 *                    then the समयout is the शेष समयout क्रम the specअगरic
 *                    ASIC
 * @get_hw_state: retrieve the H/W state
 * @pci_bars_map: Map PCI BARs.
 * @init_iatu: Initialize the iATU unit inside the PCI controller.
 * @rreg: Read a रेजिस्टर. Needed क्रम simulator support.
 * @wreg: Write a रेजिस्टर. Needed क्रम simulator support.
 * @halt_coresight: stop the ETF and ETR traces.
 * @ctx_init: context dependent initialization.
 * @ctx_fini: context dependent cleanup.
 * @get_clk_rate: Retrieve the ASIC current and maximum घड़ी rate in MHz
 * @get_queue_id_क्रम_cq: Get the H/W queue id related to the given CQ index.
 * @पढ़ो_device_fw_version: पढ़ो the device's firmware versions that are
 *                          contained in रेजिस्टरs
 * @load_firmware_to_device: load the firmware to the device's memory
 * @load_boot_fit_to_device: load boot fit to device's memory
 * @get_संकेत_cb_size: Get संकेत CB size.
 * @get_रुको_cb_size: Get रुको CB size.
 * @gen_संकेत_cb: Generate a संकेत CB.
 * @gen_रुको_cb: Generate a रुको CB.
 * @reset_sob: Reset a SOB.
 * @reset_sob_group: Reset SOB group
 * @set_dma_mask_from_fw: set the DMA mask in the driver according to the
 *                        firmware configuration
 * @get_device_समय: Get the device समय.
 * @collective_रुको_init_cs: Generate collective master/slave packets
 *                           and place them in the relevant cs jobs
 * @collective_रुको_create_jobs: allocate collective रुको cs jobs
 * @scramble_addr: Routine to scramble the address prior of mapping it
 *                 in the MMU.
 * @descramble_addr: Routine to de-scramble the address prior of
 *                   showing it to users.
 * @ack_protection_bits_errors: ack and dump all security violations
 * @get_hw_block_id: retrieve a HW block id to be used by the user to mmap it.
 *                   also वापसs the size of the block अगर caller supplies
 *                   a valid poपूर्णांकer क्रम it
 * @hw_block_mmap: mmap a HW block with a given id.
 * @enable_events_from_fw: send पूर्णांकerrupt to firmware to notअगरy them the
 *                         driver is पढ़ोy to receive asynchronous events. This
 *                         function should be called during the first init and
 *                         after every hard-reset of the device
 * @get_msi_info: Retrieve asic-specअगरic MSI ID of the f/w async event
 * @map_pll_idx_to_fw_idx: convert driver specअगरic per asic PLL index to
 *                         generic f/w compatible PLL Indexes
 */
काष्ठा hl_asic_funcs अणु
	पूर्णांक (*early_init)(काष्ठा hl_device *hdev);
	पूर्णांक (*early_fini)(काष्ठा hl_device *hdev);
	पूर्णांक (*late_init)(काष्ठा hl_device *hdev);
	व्योम (*late_fini)(काष्ठा hl_device *hdev);
	पूर्णांक (*sw_init)(काष्ठा hl_device *hdev);
	पूर्णांक (*sw_fini)(काष्ठा hl_device *hdev);
	पूर्णांक (*hw_init)(काष्ठा hl_device *hdev);
	व्योम (*hw_fini)(काष्ठा hl_device *hdev, bool hard_reset);
	व्योम (*halt_engines)(काष्ठा hl_device *hdev, bool hard_reset);
	पूर्णांक (*suspend)(काष्ठा hl_device *hdev);
	पूर्णांक (*resume)(काष्ठा hl_device *hdev);
	पूर्णांक (*cb_mmap)(काष्ठा hl_device *hdev, काष्ठा vm_area_काष्ठा *vma,
			व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size);
	व्योम (*ring_करोorbell)(काष्ठा hl_device *hdev, u32 hw_queue_id, u32 pi);
	व्योम (*pqe_ग_लिखो)(काष्ठा hl_device *hdev, __le64 *pqe,
			काष्ठा hl_bd *bd);
	व्योम* (*asic_dma_alloc_coherent)(काष्ठा hl_device *hdev, माप_प्रकार size,
					dma_addr_t *dma_handle, gfp_t flag);
	व्योम (*asic_dma_मुक्त_coherent)(काष्ठा hl_device *hdev, माप_प्रकार size,
					व्योम *cpu_addr, dma_addr_t dma_handle);
	पूर्णांक (*scrub_device_mem)(काष्ठा hl_device *hdev, u64 addr, u64 size);
	व्योम* (*get_पूर्णांक_queue_base)(काष्ठा hl_device *hdev, u32 queue_id,
				dma_addr_t *dma_handle, u16 *queue_len);
	पूर्णांक (*test_queues)(काष्ठा hl_device *hdev);
	व्योम* (*asic_dma_pool_zalloc)(काष्ठा hl_device *hdev, माप_प्रकार size,
				gfp_t mem_flags, dma_addr_t *dma_handle);
	व्योम (*asic_dma_pool_मुक्त)(काष्ठा hl_device *hdev, व्योम *vaddr,
				dma_addr_t dma_addr);
	व्योम* (*cpu_accessible_dma_pool_alloc)(काष्ठा hl_device *hdev,
				माप_प्रकार size, dma_addr_t *dma_handle);
	व्योम (*cpu_accessible_dma_pool_मुक्त)(काष्ठा hl_device *hdev,
				माप_प्रकार size, व्योम *vaddr);
	व्योम (*hl_dma_unmap_sg)(काष्ठा hl_device *hdev,
				काष्ठा scatterlist *sgl, पूर्णांक nents,
				क्रमागत dma_data_direction dir);
	पूर्णांक (*cs_parser)(काष्ठा hl_device *hdev, काष्ठा hl_cs_parser *parser);
	पूर्णांक (*asic_dma_map_sg)(काष्ठा hl_device *hdev,
				काष्ठा scatterlist *sgl, पूर्णांक nents,
				क्रमागत dma_data_direction dir);
	u32 (*get_dma_desc_list_size)(काष्ठा hl_device *hdev,
					काष्ठा sg_table *sgt);
	व्योम (*add_end_of_cb_packets)(काष्ठा hl_device *hdev,
					व्योम *kernel_address, u32 len,
					u64 cq_addr, u32 cq_val, u32 msix_num,
					bool eb);
	व्योम (*update_eq_ci)(काष्ठा hl_device *hdev, u32 val);
	पूर्णांक (*context_चयन)(काष्ठा hl_device *hdev, u32 asid);
	व्योम (*restore_phase_topology)(काष्ठा hl_device *hdev);
	पूर्णांक (*debugfs_पढ़ो32)(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u32 *val);
	पूर्णांक (*debugfs_ग_लिखो32)(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u32 val);
	पूर्णांक (*debugfs_पढ़ो64)(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u64 *val);
	पूर्णांक (*debugfs_ग_लिखो64)(काष्ठा hl_device *hdev, u64 addr,
				bool user_address, u64 val);
	पूर्णांक (*debugfs_पढ़ो_dma)(काष्ठा hl_device *hdev, u64 addr, u32 size,
				व्योम *blob_addr);
	व्योम (*add_device_attr)(काष्ठा hl_device *hdev,
				काष्ठा attribute_group *dev_attr_grp);
	व्योम (*handle_eqe)(काष्ठा hl_device *hdev,
				काष्ठा hl_eq_entry *eq_entry);
	व्योम (*set_pll_profile)(काष्ठा hl_device *hdev,
			क्रमागत hl_pll_frequency freq);
	व्योम* (*get_events_stat)(काष्ठा hl_device *hdev, bool aggregate,
				u32 *size);
	u64 (*पढ़ो_pte)(काष्ठा hl_device *hdev, u64 addr);
	व्योम (*ग_लिखो_pte)(काष्ठा hl_device *hdev, u64 addr, u64 val);
	पूर्णांक (*mmu_invalidate_cache)(काष्ठा hl_device *hdev, bool is_hard,
					u32 flags);
	पूर्णांक (*mmu_invalidate_cache_range)(काष्ठा hl_device *hdev, bool is_hard,
			u32 asid, u64 va, u64 size);
	पूर्णांक (*send_heartbeat)(काष्ठा hl_device *hdev);
	व्योम (*set_घड़ी_gating)(काष्ठा hl_device *hdev);
	व्योम (*disable_घड़ी_gating)(काष्ठा hl_device *hdev);
	पूर्णांक (*debug_coresight)(काष्ठा hl_device *hdev, व्योम *data);
	bool (*is_device_idle)(काष्ठा hl_device *hdev, u64 *mask_arr,
					u8 mask_len, काष्ठा seq_file *s);
	पूर्णांक (*soft_reset_late_init)(काष्ठा hl_device *hdev);
	व्योम (*hw_queues_lock)(काष्ठा hl_device *hdev);
	व्योम (*hw_queues_unlock)(काष्ठा hl_device *hdev);
	u32 (*get_pci_id)(काष्ठा hl_device *hdev);
	पूर्णांक (*get_eeprom_data)(काष्ठा hl_device *hdev, व्योम *data,
				माप_प्रकार max_size);
	पूर्णांक (*send_cpu_message)(काष्ठा hl_device *hdev, u32 *msg,
				u16 len, u32 समयout, u64 *result);
	पूर्णांक (*pci_bars_map)(काष्ठा hl_device *hdev);
	पूर्णांक (*init_iatu)(काष्ठा hl_device *hdev);
	u32 (*rreg)(काष्ठा hl_device *hdev, u32 reg);
	व्योम (*wreg)(काष्ठा hl_device *hdev, u32 reg, u32 val);
	व्योम (*halt_coresight)(काष्ठा hl_device *hdev);
	पूर्णांक (*ctx_init)(काष्ठा hl_ctx *ctx);
	व्योम (*ctx_fini)(काष्ठा hl_ctx *ctx);
	पूर्णांक (*get_clk_rate)(काष्ठा hl_device *hdev, u32 *cur_clk, u32 *max_clk);
	u32 (*get_queue_id_क्रम_cq)(काष्ठा hl_device *hdev, u32 cq_idx);
	पूर्णांक (*पढ़ो_device_fw_version)(काष्ठा hl_device *hdev,
					क्रमागत hl_fw_component fwc);
	पूर्णांक (*load_firmware_to_device)(काष्ठा hl_device *hdev);
	पूर्णांक (*load_boot_fit_to_device)(काष्ठा hl_device *hdev);
	u32 (*get_संकेत_cb_size)(काष्ठा hl_device *hdev);
	u32 (*get_रुको_cb_size)(काष्ठा hl_device *hdev);
	u32 (*gen_संकेत_cb)(काष्ठा hl_device *hdev, व्योम *data, u16 sob_id,
			u32 size, bool eb);
	u32 (*gen_रुको_cb)(काष्ठा hl_device *hdev,
			काष्ठा hl_gen_रुको_properties *prop);
	व्योम (*reset_sob)(काष्ठा hl_device *hdev, व्योम *data);
	व्योम (*reset_sob_group)(काष्ठा hl_device *hdev, u16 sob_group);
	व्योम (*set_dma_mask_from_fw)(काष्ठा hl_device *hdev);
	u64 (*get_device_समय)(काष्ठा hl_device *hdev);
	व्योम (*collective_रुको_init_cs)(काष्ठा hl_cs *cs);
	पूर्णांक (*collective_रुको_create_jobs)(काष्ठा hl_device *hdev,
			काष्ठा hl_ctx *ctx, काष्ठा hl_cs *cs, u32 रुको_queue_id,
			u32 collective_engine_id);
	u64 (*scramble_addr)(काष्ठा hl_device *hdev, u64 addr);
	u64 (*descramble_addr)(काष्ठा hl_device *hdev, u64 addr);
	व्योम (*ack_protection_bits_errors)(काष्ठा hl_device *hdev);
	पूर्णांक (*get_hw_block_id)(काष्ठा hl_device *hdev, u64 block_addr,
				u32 *block_size, u32 *block_id);
	पूर्णांक (*hw_block_mmap)(काष्ठा hl_device *hdev, काष्ठा vm_area_काष्ठा *vma,
			u32 block_id, u32 block_size);
	व्योम (*enable_events_from_fw)(काष्ठा hl_device *hdev);
	व्योम (*get_msi_info)(u32 *table);
	पूर्णांक (*map_pll_idx_to_fw_idx)(u32 pll_idx);
पूर्ण;


/*
 * CONTEXTS
 */

#घोषणा HL_KERNEL_ASID_ID	0

/**
 * क्रमागत hl_va_range_type - भव address range type.
 * @HL_VA_RANGE_TYPE_HOST: range type of host pages
 * @HL_VA_RANGE_TYPE_HOST_HUGE: range type of host huge pages
 * @HL_VA_RANGE_TYPE_DRAM: range type of dram pages
 */
क्रमागत hl_va_range_type अणु
	HL_VA_RANGE_TYPE_HOST,
	HL_VA_RANGE_TYPE_HOST_HUGE,
	HL_VA_RANGE_TYPE_DRAM,
	HL_VA_RANGE_TYPE_MAX
पूर्ण;

/**
 * काष्ठा hl_va_range - भव addresses range.
 * @lock: protects the भव addresses list.
 * @list: list of भव addresses blocks available क्रम mappings.
 * @start_addr: range start address.
 * @end_addr: range end address.
 * @page_size: page size of this va range.
 */
काष्ठा hl_va_range अणु
	काष्ठा mutex		lock;
	काष्ठा list_head	list;
	u64			start_addr;
	u64			end_addr;
	u32			page_size;
पूर्ण;

/**
 * काष्ठा hl_cs_counters_atomic - command submission counters
 * @out_of_mem_drop_cnt: dropped due to memory allocation issue
 * @parsing_drop_cnt: dropped due to error in packet parsing
 * @queue_full_drop_cnt: dropped due to queue full
 * @device_in_reset_drop_cnt: dropped due to device in reset
 * @max_cs_in_flight_drop_cnt: dropped due to maximum CS in-flight
 * @validation_drop_cnt: dropped due to error in validation
 */
काष्ठा hl_cs_counters_atomic अणु
	atomic64_t out_of_mem_drop_cnt;
	atomic64_t parsing_drop_cnt;
	atomic64_t queue_full_drop_cnt;
	atomic64_t device_in_reset_drop_cnt;
	atomic64_t max_cs_in_flight_drop_cnt;
	atomic64_t validation_drop_cnt;
पूर्ण;

/**
 * काष्ठा hl_pending_cb - pending command buffer काष्ठाure
 * @cb_node: cb node in pending cb list
 * @cb: command buffer to send in next submission
 * @cb_size: command buffer size
 * @hw_queue_id: destination queue id
 */
काष्ठा hl_pending_cb अणु
	काष्ठा list_head	cb_node;
	काष्ठा hl_cb		*cb;
	u32			cb_size;
	u32			hw_queue_id;
पूर्ण;

/**
 * काष्ठा hl_ctx - user/kernel context.
 * @mem_hash: holds mapping from भव address to भव memory area
 *		descriptor (hl_vm_phys_pg_list or hl_userptr).
 * @mmu_shaकरोw_hash: holds a mapping from shaकरोw address to pgt_info काष्ठाure.
 * @hpriv: poपूर्णांकer to the निजी (Kernel Driver) data of the process (fd).
 * @hdev: poपूर्णांकer to the device काष्ठाure.
 * @refcount: reference counter क्रम the context. Context is released only when
 *		this hits 0l. It is incremented on CS and CS_WAIT.
 * @cs_pending: array of hl fence objects representing pending CS.
 * @va_range: holds available भव addresses क्रम host and dram mappings.
 * @mem_hash_lock: protects the mem_hash.
 * @mmu_lock: protects the MMU page tables. Any change to the PGT, modअगरying the
 *            MMU hash or walking the PGT requires talking this lock.
 * @hw_block_list_lock: protects the HW block memory list.
 * @debugfs_list: node in debugfs list of contexts.
 * pending_cb_list: list of pending command buffers रुकोing to be sent upon
 *                  next user command submission context.
 * @hw_block_mem_list: list of HW block भव mapped addresses.
 * @cs_counters: context command submission counters.
 * @cb_va_pool: device VA pool क्रम command buffers which are mapped to the
 *              device's MMU.
 * @cs_sequence: sequence number क्रम CS. Value is asचिन्हित to a CS and passed
 *			to user so user could inquire about CS. It is used as
 *			index to cs_pending array.
 * @dram_शेष_hops: array that holds all hops addresses needed क्रम शेष
 *                     DRAM mapping.
 * @pending_cb_lock: spinlock to protect pending cb list
 * @cs_lock: spinlock to protect cs_sequence.
 * @dram_phys_mem: amount of used physical DRAM memory by this context.
 * @thपढ़ो_ctx_चयन_token: token to prevent multiple thपढ़ोs of the same
 *				context	from running the context चयन phase.
 *				Only a single thपढ़ो should run it.
 * @thपढ़ो_pending_cb_token: token to prevent multiple thपढ़ोs from processing
 *				the pending CB list. Only a single thपढ़ो should
 *				process the list since it is रक्षित by a
 *				spinlock and we करोn't want to halt the entire
 *				command submission sequence.
 * @thपढ़ो_ctx_चयन_रुको_token: token to prevent the thपढ़ोs that didn't run
 *				the context चयन phase from moving to their
 *				execution phase beक्रमe the context चयन phase
 *				has finished.
 * @asid: context's unique address space ID in the device's MMU.
 * @handle: context's opaque handle क्रम user
 */
काष्ठा hl_ctx अणु
	DECLARE_HASHTABLE(mem_hash, MEM_HASH_TABLE_BITS);
	DECLARE_HASHTABLE(mmu_shaकरोw_hash, MMU_HASH_TABLE_BITS);
	काष्ठा hl_fpriv			*hpriv;
	काष्ठा hl_device		*hdev;
	काष्ठा kref			refcount;
	काष्ठा hl_fence			**cs_pending;
	काष्ठा hl_va_range		*va_range[HL_VA_RANGE_TYPE_MAX];
	काष्ठा mutex			mem_hash_lock;
	काष्ठा mutex			mmu_lock;
	काष्ठा mutex			hw_block_list_lock;
	काष्ठा list_head		debugfs_list;
	काष्ठा list_head		pending_cb_list;
	काष्ठा list_head		hw_block_mem_list;
	काष्ठा hl_cs_counters_atomic	cs_counters;
	काष्ठा gen_pool			*cb_va_pool;
	u64				cs_sequence;
	u64				*dram_शेष_hops;
	spinlock_t			pending_cb_lock;
	spinlock_t			cs_lock;
	atomic64_t			dram_phys_mem;
	atomic_t			thपढ़ो_ctx_चयन_token;
	atomic_t			thपढ़ो_pending_cb_token;
	u32				thपढ़ो_ctx_चयन_रुको_token;
	u32				asid;
	u32				handle;
पूर्ण;

/**
 * काष्ठा hl_ctx_mgr - क्रम handling multiple contexts.
 * @ctx_lock: protects ctx_handles.
 * @ctx_handles: idr to hold all ctx handles.
 */
काष्ठा hl_ctx_mgr अणु
	काष्ठा mutex		ctx_lock;
	काष्ठा idr		ctx_handles;
पूर्ण;



/*
 * COMMAND SUBMISSIONS
 */

/**
 * काष्ठा hl_userptr - memory mapping chunk inक्रमmation
 * @vm_type: type of the VM.
 * @job_node: linked-list node क्रम hanging the object on the Job's list.
 * @pages: poपूर्णांकer to काष्ठा page array
 * @npages: size of @pages array
 * @sgt: poपूर्णांकer to the scatter-gather table that holds the pages.
 * @dir: क्रम DMA unmapping, the direction must be supplied, so save it.
 * @debugfs_list: node in debugfs list of command submissions.
 * @addr: user-space भव address of the start of the memory area.
 * @size: size of the memory area to pin & map.
 * @dma_mapped: true अगर the SG was mapped to DMA addresses, false otherwise.
 */
काष्ठा hl_userptr अणु
	क्रमागत vm_type_t		vm_type; /* must be first */
	काष्ठा list_head	job_node;
	काष्ठा page		**pages;
	अचिन्हित पूर्णांक		npages;
	काष्ठा sg_table		*sgt;
	क्रमागत dma_data_direction dir;
	काष्ठा list_head	debugfs_list;
	u64			addr;
	u32			size;
	u8			dma_mapped;
पूर्ण;

/**
 * काष्ठा hl_cs - command submission.
 * @jobs_in_queue_cnt: per each queue, मुख्यtain counter of submitted jobs.
 * @ctx: the context this CS beदीर्घs to.
 * @job_list: list of the CS's jobs in the various queues.
 * @job_lock: spinlock क्रम the CS's jobs list. Needed क्रम मुक्त_job.
 * @refcount: reference counter क्रम usage of the CS.
 * @fence: poपूर्णांकer to the fence object of this CS.
 * @संकेत_fence: poपूर्णांकer to the fence object of the संकेत CS (used by रुको
 *                CS only).
 * @finish_work: workqueue object to run when CS is completed by H/W.
 * @work_tdr: delayed work node क्रम TDR.
 * @mirror_node : node in device mirror list of command submissions.
 * @staged_cs_node: node in the staged cs list.
 * @debugfs_list: node in debugfs list of command submissions.
 * @sequence: the sequence number of this CS.
 * @staged_sequence: the sequence of the staged submission this CS is part of,
 *                   relevant only अगर staged_cs is set.
 * @समयout_jअगरfies: cs समयout in jअगरfies.
 * @type: CS_TYPE_*.
 * @submitted: true अगर CS was submitted to H/W.
 * @completed: true अगर CS was completed by device.
 * @समयकरोut : true अगर CS was समयकरोut.
 * @tdr_active: true अगर TDR was activated क्रम this CS (to prevent
 *		द्विगुन TDR activation).
 * @पातed: true अगर CS was पातed due to some device error.
 * @बारtamp: true अगर a बारपंचांगap must be captured upon completion.
 * @staged_last: true अगर this is the last staged CS and needs completion.
 * @staged_first: true अगर this is the first staged CS and we need to receive
 *                समयout क्रम this CS.
 * @staged_cs: true अगर this CS is part of a staged submission.
 */
काष्ठा hl_cs अणु
	u16			*jobs_in_queue_cnt;
	काष्ठा hl_ctx		*ctx;
	काष्ठा list_head	job_list;
	spinlock_t		job_lock;
	काष्ठा kref		refcount;
	काष्ठा hl_fence		*fence;
	काष्ठा hl_fence		*संकेत_fence;
	काष्ठा work_काष्ठा	finish_work;
	काष्ठा delayed_work	work_tdr;
	काष्ठा list_head	mirror_node;
	काष्ठा list_head	staged_cs_node;
	काष्ठा list_head	debugfs_list;
	u64			sequence;
	u64			staged_sequence;
	u64			समयout_jअगरfies;
	क्रमागत hl_cs_type		type;
	u8			submitted;
	u8			completed;
	u8			समयकरोut;
	u8			tdr_active;
	u8			पातed;
	u8			बारtamp;
	u8			staged_last;
	u8			staged_first;
	u8			staged_cs;
पूर्ण;

/**
 * काष्ठा hl_cs_job - command submission job.
 * @cs_node: the node to hang on the CS jobs list.
 * @cs: the CS this job beदीर्घs to.
 * @user_cb: the CB we got from the user.
 * @patched_cb: in हाल of patching, this is पूर्णांकernal CB which is submitted on
 *		the queue instead of the CB we got from the IOCTL.
 * @finish_work: workqueue object to run when job is completed.
 * @userptr_list: linked-list of userptr mappings that beदीर्घ to this job and
 *			रुको क्रम completion.
 * @debugfs_list: node in debugfs list of command submission jobs.
 * @refcount: reference counter क्रम usage of the CS job.
 * @queue_type: the type of the H/W queue this job is submitted to.
 * @id: the id of this job inside a CS.
 * @hw_queue_id: the id of the H/W queue this job is submitted to.
 * @user_cb_size: the actual size of the CB we got from the user.
 * @job_cb_size: the actual size of the CB that we put on the queue.
 * @is_kernel_allocated_cb: true अगर the CB handle we got from the user holds a
 *                          handle to a kernel-allocated CB object, false
 *                          otherwise (SRAM/DRAM/host address).
 * @contains_dma_pkt: whether the JOB contains at least one DMA packet. This
 *                    info is needed later, when adding the 2xMSG_PROT at the
 *                    end of the JOB, to know which barriers to put in the
 *                    MSG_PROT packets. Relevant only क्रम GAUDI as GOYA करोesn't
 *                    have streams so the engine can't be busy by another
 *                    stream.
 */
काष्ठा hl_cs_job अणु
	काष्ठा list_head	cs_node;
	काष्ठा hl_cs		*cs;
	काष्ठा hl_cb		*user_cb;
	काष्ठा hl_cb		*patched_cb;
	काष्ठा work_काष्ठा	finish_work;
	काष्ठा list_head	userptr_list;
	काष्ठा list_head	debugfs_list;
	काष्ठा kref		refcount;
	क्रमागत hl_queue_type	queue_type;
	u32			id;
	u32			hw_queue_id;
	u32			user_cb_size;
	u32			job_cb_size;
	u8			is_kernel_allocated_cb;
	u8			contains_dma_pkt;
पूर्ण;

/**
 * काष्ठा hl_cs_parser - command submission parser properties.
 * @user_cb: the CB we got from the user.
 * @patched_cb: in हाल of patching, this is पूर्णांकernal CB which is submitted on
 *		the queue instead of the CB we got from the IOCTL.
 * @job_userptr_list: linked-list of userptr mappings that beदीर्घ to the related
 *			job and रुको क्रम completion.
 * @cs_sequence: the sequence number of the related CS.
 * @queue_type: the type of the H/W queue this job is submitted to.
 * @ctx_id: the ID of the context the related CS beदीर्घs to.
 * @hw_queue_id: the id of the H/W queue this job is submitted to.
 * @user_cb_size: the actual size of the CB we got from the user.
 * @patched_cb_size: the size of the CB after parsing.
 * @job_id: the id of the related job inside the related CS.
 * @is_kernel_allocated_cb: true अगर the CB handle we got from the user holds a
 *                          handle to a kernel-allocated CB object, false
 *                          otherwise (SRAM/DRAM/host address).
 * @contains_dma_pkt: whether the JOB contains at least one DMA packet. This
 *                    info is needed later, when adding the 2xMSG_PROT at the
 *                    end of the JOB, to know which barriers to put in the
 *                    MSG_PROT packets. Relevant only क्रम GAUDI as GOYA करोesn't
 *                    have streams so the engine can't be busy by another
 *                    stream.
 * @completion: true अगर we need completion क्रम this CS.
 */
काष्ठा hl_cs_parser अणु
	काष्ठा hl_cb		*user_cb;
	काष्ठा hl_cb		*patched_cb;
	काष्ठा list_head	*job_userptr_list;
	u64			cs_sequence;
	क्रमागत hl_queue_type	queue_type;
	u32			ctx_id;
	u32			hw_queue_id;
	u32			user_cb_size;
	u32			patched_cb_size;
	u8			job_id;
	u8			is_kernel_allocated_cb;
	u8			contains_dma_pkt;
	u8			completion;
पूर्ण;

/*
 * MEMORY STRUCTURE
 */

/**
 * काष्ठा hl_vm_hash_node - hash element from भव address to भव
 *				memory area descriptor (hl_vm_phys_pg_list or
 *				hl_userptr).
 * @node: node to hang on the hash table in context object.
 * @vaddr: key भव address.
 * @ptr: value poपूर्णांकer (hl_vm_phys_pg_list or hl_userptr).
 */
काष्ठा hl_vm_hash_node अणु
	काष्ठा hlist_node	node;
	u64			vaddr;
	व्योम			*ptr;
पूर्ण;

/**
 * काष्ठा hl_vm_hw_block_list_node - list element from user भव address to
 *				HW block id.
 * @node: node to hang on the list in context object.
 * @ctx: the context this node beदीर्घs to.
 * @vaddr: भव address of the HW block.
 * @size: size of the block.
 * @id: HW block id (handle).
 */
काष्ठा hl_vm_hw_block_list_node अणु
	काष्ठा list_head	node;
	काष्ठा hl_ctx		*ctx;
	अचिन्हित दीर्घ		vaddr;
	u32			size;
	u32			id;
पूर्ण;

/**
 * काष्ठा hl_vm_phys_pg_pack - physical page pack.
 * @vm_type: describes the type of the भव area descriptor.
 * @pages: the physical page array.
 * @npages: num physical pages in the pack.
 * @total_size: total size of all the pages in this list.
 * @mapping_cnt: number of shared mappings.
 * @asid: the context related to this list.
 * @page_size: size of each page in the pack.
 * @flags: HL_MEM_* flags related to this list.
 * @handle: the provided handle related to this list.
 * @offset: offset from the first page.
 * @contiguous: is contiguous physical memory.
 * @created_from_userptr: is product of host भव address.
 */
काष्ठा hl_vm_phys_pg_pack अणु
	क्रमागत vm_type_t		vm_type; /* must be first */
	u64			*pages;
	u64			npages;
	u64			total_size;
	atomic_t		mapping_cnt;
	u32			asid;
	u32			page_size;
	u32			flags;
	u32			handle;
	u32			offset;
	u8			contiguous;
	u8			created_from_userptr;
पूर्ण;

/**
 * काष्ठा hl_vm_va_block - भव range block inक्रमmation.
 * @node: node to hang on the भव range list in context object.
 * @start: भव range start address.
 * @end: भव range end address.
 * @size: भव range size.
 */
काष्ठा hl_vm_va_block अणु
	काष्ठा list_head	node;
	u64			start;
	u64			end;
	u64			size;
पूर्ण;

/**
 * काष्ठा hl_vm - भव memory manager क्रम MMU.
 * @dram_pg_pool: pool क्रम DRAM physical pages of 2MB.
 * @dram_pg_pool_refcount: reference counter क्रम the pool usage.
 * @idr_lock: protects the phys_pg_list_handles.
 * @phys_pg_pack_handles: idr to hold all device allocations handles.
 * @init_करोne: whether initialization was करोne. We need this because VM
 *		initialization might be skipped during device initialization.
 */
काष्ठा hl_vm अणु
	काष्ठा gen_pool		*dram_pg_pool;
	काष्ठा kref		dram_pg_pool_refcount;
	spinlock_t		idr_lock;
	काष्ठा idr		phys_pg_pack_handles;
	u8			init_करोne;
पूर्ण;


/*
 * DEBUG, PROFILING STRUCTURE
 */

/**
 * काष्ठा hl_debug_params - Coresight debug parameters.
 * @input: poपूर्णांकer to component specअगरic input parameters.
 * @output: poपूर्णांकer to component specअगरic output parameters.
 * @output_size: size of output buffer.
 * @reg_idx: relevant रेजिस्टर ID.
 * @op: component operation to execute.
 * @enable: true अगर to enable component debugging, false otherwise.
 */
काष्ठा hl_debug_params अणु
	व्योम *input;
	व्योम *output;
	u32 output_size;
	u32 reg_idx;
	u32 op;
	bool enable;
पूर्ण;

/*
 * खाता PRIVATE STRUCTURE
 */

/**
 * काष्ठा hl_fpriv - process inक्रमmation stored in FD निजी data.
 * @hdev: habanaद_असल device काष्ठाure.
 * @filp: poपूर्णांकer to the given file काष्ठाure.
 * @taskpid: current process ID.
 * @ctx: current executing context. TODO: हटाओ क्रम multiple ctx per process
 * @ctx_mgr: context manager to handle multiple context क्रम this FD.
 * @cb_mgr: command buffer manager to handle multiple buffers क्रम this FD.
 * @debugfs_list: list of relevant ASIC debugfs.
 * @dev_node: node in the device list of file निजी data
 * @refcount: number of related contexts.
 * @restore_phase_mutex: lock क्रम context चयन and restore phase.
 * @is_control: true क्रम control device, false otherwise
 */
काष्ठा hl_fpriv अणु
	काष्ठा hl_device	*hdev;
	काष्ठा file		*filp;
	काष्ठा pid		*taskpid;
	काष्ठा hl_ctx		*ctx;
	काष्ठा hl_ctx_mgr	ctx_mgr;
	काष्ठा hl_cb_mgr	cb_mgr;
	काष्ठा list_head	debugfs_list;
	काष्ठा list_head	dev_node;
	काष्ठा kref		refcount;
	काष्ठा mutex		restore_phase_mutex;
	u8			is_control;
पूर्ण;


/*
 * DebugFS
 */

/**
 * काष्ठा hl_info_list - debugfs file ops.
 * @name: file name.
 * @show: function to output inक्रमmation.
 * @ग_लिखो: function to ग_लिखो to the file.
 */
काष्ठा hl_info_list अणु
	स्थिर अक्षर	*name;
	पूर्णांक		(*show)(काष्ठा seq_file *s, व्योम *data);
	sमाप_प्रकार		(*ग_लिखो)(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *f_pos);
पूर्ण;

/**
 * काष्ठा hl_debugfs_entry - debugfs dentry wrapper.
 * @info_ent: dentry realted ops.
 * @dev_entry: ASIC specअगरic debugfs manager.
 */
काष्ठा hl_debugfs_entry अणु
	स्थिर काष्ठा hl_info_list	*info_ent;
	काष्ठा hl_dbg_device_entry	*dev_entry;
पूर्ण;

/**
 * काष्ठा hl_dbg_device_entry - ASIC specअगरic debugfs manager.
 * @root: root dentry.
 * @hdev: habanaद_असल device काष्ठाure.
 * @entry_arr: array of available hl_debugfs_entry.
 * @file_list: list of available debugfs files.
 * @file_mutex: protects file_list.
 * @cb_list: list of available CBs.
 * @cb_spinlock: protects cb_list.
 * @cs_list: list of available CSs.
 * @cs_spinlock: protects cs_list.
 * @cs_job_list: list of available CB jobs.
 * @cs_job_spinlock: protects cs_job_list.
 * @userptr_list: list of available userptrs (भव memory chunk descriptor).
 * @userptr_spinlock: protects userptr_list.
 * @ctx_mem_hash_list: list of available contexts with MMU mappings.
 * @ctx_mem_hash_spinlock: protects cb_list.
 * @blob_desc: descriptor of blob
 * @addr: next address to पढ़ो/ग_लिखो from/to in पढ़ो/ग_लिखो32.
 * @mmu_addr: next भव address to translate to physical address in mmu_show.
 * @mmu_asid: ASID to use जबतक translating in mmu_show.
 * @i2c_bus: generic u8 debugfs file क्रम bus value to use in i2c_data_पढ़ो.
 * @i2c_addr: generic u8 debugfs file क्रम address value to use in i2c_data_पढ़ो.
 * @i2c_reg: generic u8 debugfs file क्रम रेजिस्टर value to use in i2c_data_पढ़ो.
 */
काष्ठा hl_dbg_device_entry अणु
	काष्ठा dentry			*root;
	काष्ठा hl_device		*hdev;
	काष्ठा hl_debugfs_entry		*entry_arr;
	काष्ठा list_head		file_list;
	काष्ठा mutex			file_mutex;
	काष्ठा list_head		cb_list;
	spinlock_t			cb_spinlock;
	काष्ठा list_head		cs_list;
	spinlock_t			cs_spinlock;
	काष्ठा list_head		cs_job_list;
	spinlock_t			cs_job_spinlock;
	काष्ठा list_head		userptr_list;
	spinlock_t			userptr_spinlock;
	काष्ठा list_head		ctx_mem_hash_list;
	spinlock_t			ctx_mem_hash_spinlock;
	काष्ठा debugfs_blob_wrapper	blob_desc;
	u64				addr;
	u64				mmu_addr;
	u32				mmu_asid;
	u8				i2c_bus;
	u8				i2c_addr;
	u8				i2c_reg;
पूर्ण;


/*
 * DEVICES
 */

#घोषणा HL_STR_MAX	32

#घोषणा HL_DEV_STS_MAX (HL_DEVICE_STATUS_NEEDS_RESET + 1)

/* Theoretical limit only. A single host can only contain up to 4 or 8 PCIe
 * x16 cards. In extreme हालs, there are hosts that can accommodate 16 cards.
 */
#घोषणा HL_MAX_MINORS	256

/*
 * Registers पढ़ो & ग_लिखो functions.
 */

u32 hl_rreg(काष्ठा hl_device *hdev, u32 reg);
व्योम hl_wreg(काष्ठा hl_device *hdev, u32 reg, u32 val);

#घोषणा RREG32(reg) hdev->asic_funcs->rreg(hdev, (reg))
#घोषणा WREG32(reg, v) hdev->asic_funcs->wreg(hdev, (reg), (v))
#घोषणा DREG32(reg) pr_info("REGISTER: " #reg " : 0x%08X\n",	\
			hdev->asic_funcs->rreg(hdev, (reg)))

#घोषणा WREG32_P(reg, val, mask)				\
	करो अणु							\
		u32 पंचांगp_ = RREG32(reg);				\
		पंचांगp_ &= (mask);					\
		पंचांगp_ |= ((val) & ~(mask));			\
		WREG32(reg, पंचांगp_);				\
	पूर्ण जबतक (0)
#घोषणा WREG32_AND(reg, and) WREG32_P(reg, 0, and)
#घोषणा WREG32_OR(reg, or) WREG32_P(reg, or, ~(or))

#घोषणा RMWREG32(reg, val, mask)				\
	करो अणु							\
		u32 पंचांगp_ = RREG32(reg);				\
		पंचांगp_ &= ~(mask);				\
		पंचांगp_ |= ((val) << __ffs(mask));			\
		WREG32(reg, पंचांगp_);				\
	पूर्ण जबतक (0)

#घोषणा RREG32_MASK(reg, mask) ((RREG32(reg) & mask) >> __ffs(mask))

#घोषणा REG_FIELD_SHIFT(reg, field) reg##_##field##_SHIFT
#घोषणा REG_FIELD_MASK(reg, field) reg##_##field##_MASK
#घोषणा WREG32_FIELD(reg, offset, field, val)	\
	WREG32(mm##reg + offset, (RREG32(mm##reg + offset) & \
				~REG_FIELD_MASK(reg, field)) | \
				(val) << REG_FIELD_SHIFT(reg, field))

/* Timeout should be दीर्घer when working with simulator but cap the
 * increased समयout to some maximum
 */
#घोषणा hl_poll_समयout(hdev, addr, val, cond, sleep_us, समयout_us) \
(अणु \
	kसमय_प्रकार __समयout; \
	अगर (hdev->pdev) \
		__समयout = kसमय_add_us(kसमय_get(), समयout_us); \
	अन्यथा \
		__समयout = kसमय_add_us(kसमय_get(),\
				min((u64)(समयout_us * 10), \
					(u64) HL_SIM_MAX_TIMEOUT_US)); \
	might_sleep_अगर(sleep_us); \
	क्रम (;;) अणु \
		(val) = RREG32(addr); \
		अगर (cond) \
			अवरोध; \
		अगर (समयout_us && kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			(val) = RREG32(addr); \
			अवरोध; \
		पूर्ण \
		अगर (sleep_us) \
			usleep_range((sleep_us >> 2) + 1, sleep_us); \
	पूर्ण \
	(cond) ? 0 : -ETIMEDOUT; \
पूर्ण)

/*
 * address in this macro poपूर्णांकs always to a memory location in the
 * host's (server's) memory. That location is updated asynchronously
 * either by the direct access of the device or by another core.
 *
 * To work both in LE and BE architectures, we need to distinguish between the
 * two states (device or another core updates the memory location). Thereक्रमe,
 * अगर mem_written_by_device is true, the host memory being polled will be
 * updated directly by the device. If false, the host memory being polled will
 * be updated by host CPU. Required so host knows whether or not the memory
 * might need to be byte-swapped beक्रमe वापसing value to caller.
 */
#घोषणा hl_poll_समयout_memory(hdev, addr, val, cond, sleep_us, समयout_us, \
				mem_written_by_device) \
(अणु \
	kसमय_प्रकार __समयout; \
	अगर (hdev->pdev) \
		__समयout = kसमय_add_us(kसमय_get(), समयout_us); \
	अन्यथा \
		__समयout = kसमय_add_us(kसमय_get(),\
				min((u64)(समयout_us * 10), \
					(u64) HL_SIM_MAX_TIMEOUT_US)); \
	might_sleep_अगर(sleep_us); \
	क्रम (;;) अणु \
		/* Verअगरy we पढ़ो updates करोne by other cores or by device */ \
		mb(); \
		(val) = *((u32 *)(addr)); \
		अगर (mem_written_by_device) \
			(val) = le32_to_cpu(*(__le32 *) &(val)); \
		अगर (cond) \
			अवरोध; \
		अगर (समयout_us && kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			(val) = *((u32 *)(addr)); \
			अगर (mem_written_by_device) \
				(val) = le32_to_cpu(*(__le32 *) &(val)); \
			अवरोध; \
		पूर्ण \
		अगर (sleep_us) \
			usleep_range((sleep_us >> 2) + 1, sleep_us); \
	पूर्ण \
	(cond) ? 0 : -ETIMEDOUT; \
पूर्ण)

#घोषणा hl_poll_समयout_device_memory(hdev, addr, val, cond, sleep_us, \
					समयout_us) \
(अणु \
	kसमय_प्रकार __समयout; \
	अगर (hdev->pdev) \
		__समयout = kसमय_add_us(kसमय_get(), समयout_us); \
	अन्यथा \
		__समयout = kसमय_add_us(kसमय_get(),\
				min((u64)(समयout_us * 10), \
					(u64) HL_SIM_MAX_TIMEOUT_US)); \
	might_sleep_अगर(sleep_us); \
	क्रम (;;) अणु \
		(val) = पढ़ोl(addr); \
		अगर (cond) \
			अवरोध; \
		अगर (समयout_us && kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			(val) = पढ़ोl(addr); \
			अवरोध; \
		पूर्ण \
		अगर (sleep_us) \
			usleep_range((sleep_us >> 2) + 1, sleep_us); \
	पूर्ण \
	(cond) ? 0 : -ETIMEDOUT; \
पूर्ण)

काष्ठा hwmon_chip_info;

/**
 * काष्ठा hl_device_reset_work - reset workqueue task wrapper.
 * @wq: work queue क्रम device reset procedure.
 * @reset_work: reset work to be करोne.
 * @hdev: habanaद_असल device काष्ठाure.
 */
काष्ठा hl_device_reset_work अणु
	काष्ठा workqueue_काष्ठा		*wq;
	काष्ठा delayed_work		reset_work;
	काष्ठा hl_device		*hdev;
पूर्ण;

/**
 * काष्ठा hr_mmu_hop_addrs - used क्रम holding per-device host-resident mmu hop
 * inक्रमmation.
 * @virt_addr: the भव address of the hop.
 * @phys-addr: the physical address of the hop (used by the device-mmu).
 * @shaकरोw_addr: The shaकरोw of the hop used by the driver क्रम walking the hops.
 */
काष्ठा hr_mmu_hop_addrs अणु
	u64 virt_addr;
	u64 phys_addr;
	u64 shaकरोw_addr;
पूर्ण;

/**
 * काष्ठा hl_mmu_hr_pgt_priv - used क्रम holding per-device mmu host-resident
 * page-table पूर्णांकernal inक्रमmation.
 * @mmu_pgt_pool: pool of page tables used by MMU क्रम allocating hops.
 * @mmu_shaकरोw_hop0: shaकरोw array of hop0 tables.
 */
काष्ठा hl_mmu_hr_priv अणु
	काष्ठा gen_pool *mmu_pgt_pool;
	काष्ठा hr_mmu_hop_addrs *mmu_shaकरोw_hop0;
पूर्ण;

/**
 * काष्ठा hl_mmu_dr_pgt_priv - used क्रम holding per-device mmu device-resident
 * page-table पूर्णांकernal inक्रमmation.
 * @mmu_pgt_pool: pool of page tables used by MMU क्रम allocating hops.
 * @mmu_shaकरोw_hop0: shaकरोw array of hop0 tables.
 */
काष्ठा hl_mmu_dr_priv अणु
	काष्ठा gen_pool *mmu_pgt_pool;
	व्योम *mmu_shaकरोw_hop0;
पूर्ण;

/**
 * काष्ठा hl_mmu_priv - used क्रम holding per-device mmu पूर्णांकernal inक्रमmation.
 * @dr: inक्रमmation on the device-resident MMU, when exists.
 * @hr: inक्रमmation on the host-resident MMU, when exists.
 */
काष्ठा hl_mmu_priv अणु
	काष्ठा hl_mmu_dr_priv dr;
	काष्ठा hl_mmu_hr_priv hr;
पूर्ण;

/**
 * काष्ठा hl_mmu_per_hop_info - A काष्ठाure describing one TLB HOP and its entry
 *                that was created in order to translate a भव address to a
 *                physical one.
 * @hop_addr: The address of the hop.
 * @hop_pte_addr: The address of the hop entry.
 * @hop_pte_val: The value in the hop entry.
 */
काष्ठा hl_mmu_per_hop_info अणु
	u64 hop_addr;
	u64 hop_pte_addr;
	u64 hop_pte_val;
पूर्ण;

/**
 * काष्ठा hl_mmu_hop_info - A काष्ठाure describing the TLB hops and their
 * hop-entries that were created in order to translate a भव address to a
 * physical one.
 * @scrambled_vaddr: The value of the भव address after scrambling. This
 *                   address replaces the original भव-address when mapped
 *                   in the MMU tables.
 * @unscrambled_paddr: The un-scrambled physical address.
 * @hop_info: Array holding the per-hop inक्रमmation used क्रम the translation.
 * @used_hops: The number of hops used क्रम the translation.
 * @range_type: भव address range type.
 */
काष्ठा hl_mmu_hop_info अणु
	u64 scrambled_vaddr;
	u64 unscrambled_paddr;
	काष्ठा hl_mmu_per_hop_info hop_info[MMU_ARCH_5_HOPS];
	u32 used_hops;
	क्रमागत hl_va_range_type range_type;
पूर्ण;

/**
 * काष्ठा hl_mmu_funcs - Device related MMU functions.
 * @init: initialize the MMU module.
 * @fini: release the MMU module.
 * @ctx_init: Initialize a context क्रम using the MMU module.
 * @ctx_fini: disable a ctx from using the mmu module.
 * @map: maps a भव address to physical address क्रम a context.
 * @unmap: unmap a भव address of a context.
 * @flush: flush all ग_लिखोs from all cores to reach device MMU.
 * @swap_out: marks all mapping of the given context as swapped out.
 * @swap_in: marks all mapping of the given context as swapped in.
 * @get_tlb_info: वापसs the list of hops and hop-entries used that were
 *                created in order to translate the giver भव address to a
 *                physical one.
 */
काष्ठा hl_mmu_funcs अणु
	पूर्णांक (*init)(काष्ठा hl_device *hdev);
	व्योम (*fini)(काष्ठा hl_device *hdev);
	पूर्णांक (*ctx_init)(काष्ठा hl_ctx *ctx);
	व्योम (*ctx_fini)(काष्ठा hl_ctx *ctx);
	पूर्णांक (*map)(काष्ठा hl_ctx *ctx,
			u64 virt_addr, u64 phys_addr, u32 page_size,
			bool is_dram_addr);
	पूर्णांक (*unmap)(काष्ठा hl_ctx *ctx,
			u64 virt_addr, bool is_dram_addr);
	व्योम (*flush)(काष्ठा hl_ctx *ctx);
	व्योम (*swap_out)(काष्ठा hl_ctx *ctx);
	व्योम (*swap_in)(काष्ठा hl_ctx *ctx);
	पूर्णांक (*get_tlb_info)(काष्ठा hl_ctx *ctx,
			u64 virt_addr, काष्ठा hl_mmu_hop_info *hops);
पूर्ण;

/**
 * काष्ठा hl_device - habanaद_असल device काष्ठाure.
 * @pdev: poपूर्णांकer to PCI device, can be शून्य in हाल of simulator device.
 * @pcie_bar_phys: array of available PCIe bars physical addresses.
 *		   (required only क्रम PCI address match mode)
 * @pcie_bar: array of available PCIe bars भव addresses.
 * @rmmio: configuration area address on SRAM.
 * @cdev: related अक्षर device.
 * @cdev_ctrl: अक्षर device क्रम control operations only (INFO IOCTL)
 * @dev: related kernel basic device काष्ठाure.
 * @dev_ctrl: related kernel device काष्ठाure क्रम the control device
 * @work_freq: delayed work to lower device frequency अगर possible.
 * @work_heartbeat: delayed work क्रम CPU-CP is-alive check.
 * @device_reset_work: delayed work which perक्रमms hard reset
 * @asic_name: ASIC specअगरic name.
 * @asic_type: ASIC specअगरic type.
 * @completion_queue: array of hl_cq.
 * @user_पूर्णांकerrupt: array of hl_user_पूर्णांकerrupt. upon the corresponding user
 *                  पूर्णांकerrupt, driver will monitor the list of fences
 *                  रेजिस्टरed to this पूर्णांकerrupt.
 * @common_user_पूर्णांकerrupt: common user पूर्णांकerrupt क्रम all user पूर्णांकerrupts.
 *                         upon any user पूर्णांकerrupt, driver will monitor the
 *                         list of fences रेजिस्टरed to this common काष्ठाure.
 * @cq_wq: work queues of completion queues क्रम executing work in process
 *         context.
 * @eq_wq: work queue of event queue क्रम executing work in process context.
 * @sob_reset_wq: work queue क्रम sob reset executions.
 * @kernel_ctx: Kernel driver context काष्ठाure.
 * @kernel_queues: array of hl_hw_queue.
 * @cs_mirror_list: CS mirror list क्रम TDR.
 * @cs_mirror_lock: protects cs_mirror_list.
 * @kernel_cb_mgr: command buffer manager क्रम creating/destroying/handling CGs.
 * @event_queue: event queue क्रम IRQ from CPU-CP.
 * @dma_pool: DMA pool क्रम small allocations.
 * @cpu_accessible_dma_mem: Host <-> CPU-CP shared memory CPU address.
 * @cpu_accessible_dma_address: Host <-> CPU-CP shared memory DMA address.
 * @cpu_accessible_dma_pool: Host <-> CPU-CP shared memory pool.
 * @asid_biपंचांगap: holds used/available ASIDs.
 * @asid_mutex: protects asid_biपंचांगap.
 * @send_cpu_message_lock: enक्रमces only one message in Host <-> CPU-CP queue.
 * @debug_lock: protects critical section of setting debug mode क्रम device
 * @asic_prop: ASIC specअगरic immutable properties.
 * @asic_funcs: ASIC specअगरic functions.
 * @asic_specअगरic: ASIC specअगरic inक्रमmation to use only from ASIC files.
 * @vm: भव memory manager क्रम MMU.
 * @hwmon_dev: H/W monitor device.
 * @pm_mng_profile: current घातer management profile.
 * @hl_chip_info: ASIC's sensors inक्रमmation.
 * @device_status_description: device status description.
 * @hl_debugfs: device's debugfs manager.
 * @cb_pool: list of pपुनः_स्मृतिated CBs.
 * @cb_pool_lock: protects the CB pool.
 * @पूर्णांकernal_cb_pool_virt_addr: पूर्णांकernal command buffer pool भव address.
 * @पूर्णांकernal_cb_pool_dma_addr: पूर्णांकernal command buffer pool dma address.
 * @पूर्णांकernal_cb_pool: पूर्णांकernal command buffer memory pool.
 * @पूर्णांकernal_cb_va_base: पूर्णांकernal cb pool mmu भव address base
 * @fpriv_list: list of file निजी data काष्ठाures. Each काष्ठाure is created
 *              when a user खोलोs the device
 * @fpriv_list_lock: protects the fpriv_list
 * @compute_ctx: current compute context executing.
 * @aggregated_cs_counters: aggregated cs counters among all contexts
 * @mmu_priv: device-specअगरic MMU data.
 * @mmu_func: device-related MMU functions.
 * @dram_used_mem: current DRAM memory consumption.
 * @समयout_jअगरfies: device CS समयout value.
 * @max_घातer: the max घातer of the device, as configured by the sysadmin. This
 *             value is saved so in हाल of hard-reset, the driver will restore
 *             this value and update the F/W after the re-initialization
 * @घड़ी_gating_mask: is घड़ी gating enabled. biपंचांगask that represents the
 *                     dअगरferent engines. See debugfs-driver-habanaद_असल क्रम
 *                     details.
 * @boot_error_status_mask: contains a mask of the device boot error status.
 *                          Each bit represents a dअगरferent error, according to
 *                          the defines in hl_boot_अगर.h. If the bit is cleared,
 *                          the error will be ignored by the driver during
 *                          device initialization. Mainly used to debug and
 *                          workaround firmware bugs
 * @in_reset: is device in reset flow.
 * @curr_pll_profile: current PLL profile.
 * @card_type: Various ASICs have several card types. This indicates the card
 *             type of the current device.
 * @major: habanaद_असल kernel driver major.
 * @high_pll: high PLL profile frequency.
 * @soft_reset_cnt: number of soft reset since the driver was loaded.
 * @hard_reset_cnt: number of hard reset since the driver was loaded.
 * @clk_throttling_reason: biपंचांगask represents the current clk throttling reasons
 * @id: device minor.
 * @id_control: minor of the control device
 * @cpu_pci_msb_addr: 50-bit extension bits क्रम the device CPU's 40-bit
 *                    addresses.
 * @disabled: is device disabled.
 * @late_init_करोne: is late init stage was करोne during initialization.
 * @hwmon_initialized: is H/W monitor sensors was initialized.
 * @hard_reset_pending: is there a hard reset work pending.
 * @heartbeat: is heartbeat sanity check towards CPU-CP enabled.
 * @reset_on_lockup: true अगर a reset should be करोne in हाल of stuck CS, false
 *                   otherwise.
 * @dram_शेष_page_mapping: is DRAM शेष page mapping enabled.
 * @memory_scrub: true to perक्रमm device memory scrub in various locations,
 *                such as context-चयन, context बंद, page मुक्त, etc.
 * @pmmu_huge_range: is a dअगरferent भव addresses range used क्रम PMMU with
 *                   huge pages.
 * @init_करोne: is the initialization of the device करोne.
 * @device_cpu_disabled: is the device CPU disabled (due to समयouts)
 * @dma_mask: the dma mask that was set क्रम this device
 * @in_debug: is device under debug. This, together with fpriv_list, enक्रमces
 *            that only a single user is configuring the debug infraकाष्ठाure.
 * @घातer9_64bit_dma_enable: true to enable 64-bit DMA mask support. Relevant
 *                           only to POWER9 machines.
 * @cdev_sysfs_created: were अक्षर devices and sysfs nodes created.
 * @stop_on_err: true अगर engines should stop on error.
 * @supports_sync_stream: is sync stream supported.
 * @sync_stream_queue_idx: helper index क्रम sync stream queues initialization.
 * @collective_mon_idx: helper index क्रम collective initialization
 * @supports_coresight: is CoreSight supported.
 * @supports_soft_reset: is soft reset supported.
 * @supports_cb_mapping: is mapping a CB to the device's MMU supported.
 * @needs_reset: true अगर reset_on_lockup is false and device should be reset
 *               due to lockup.
 * @process_समाप्त_trial_cnt: number of trials reset thपढ़ो tried समाप्तing
 *                          user processes
 * @device_fini_pending: true अगर device_fini was called and might be
 *                       रुकोing क्रम the reset thपढ़ो to finish
 * @supports_staged_submission: true अगर staged submissions are supported
 */
काष्ठा hl_device अणु
	काष्ठा pci_dev			*pdev;
	u64				pcie_bar_phys[HL_PCI_NUM_BARS];
	व्योम __iomem			*pcie_bar[HL_PCI_NUM_BARS];
	व्योम __iomem			*rmmio;
	काष्ठा cdev			cdev;
	काष्ठा cdev			cdev_ctrl;
	काष्ठा device			*dev;
	काष्ठा device			*dev_ctrl;
	काष्ठा delayed_work		work_freq;
	काष्ठा delayed_work		work_heartbeat;
	काष्ठा hl_device_reset_work	device_reset_work;
	अक्षर				asic_name[HL_STR_MAX];
	अक्षर				status[HL_DEV_STS_MAX][HL_STR_MAX];
	क्रमागत hl_asic_type		asic_type;
	काष्ठा hl_cq			*completion_queue;
	काष्ठा hl_user_पूर्णांकerrupt	*user_पूर्णांकerrupt;
	काष्ठा hl_user_पूर्णांकerrupt	common_user_पूर्णांकerrupt;
	काष्ठा workqueue_काष्ठा		**cq_wq;
	काष्ठा workqueue_काष्ठा		*eq_wq;
	काष्ठा workqueue_काष्ठा		*sob_reset_wq;
	काष्ठा hl_ctx			*kernel_ctx;
	काष्ठा hl_hw_queue		*kernel_queues;
	काष्ठा list_head		cs_mirror_list;
	spinlock_t			cs_mirror_lock;
	काष्ठा hl_cb_mgr		kernel_cb_mgr;
	काष्ठा hl_eq			event_queue;
	काष्ठा dma_pool			*dma_pool;
	व्योम				*cpu_accessible_dma_mem;
	dma_addr_t			cpu_accessible_dma_address;
	काष्ठा gen_pool			*cpu_accessible_dma_pool;
	अचिन्हित दीर्घ			*asid_biपंचांगap;
	काष्ठा mutex			asid_mutex;
	काष्ठा mutex			send_cpu_message_lock;
	काष्ठा mutex			debug_lock;
	काष्ठा asic_fixed_properties	asic_prop;
	स्थिर काष्ठा hl_asic_funcs	*asic_funcs;
	व्योम				*asic_specअगरic;
	काष्ठा hl_vm			vm;
	काष्ठा device			*hwmon_dev;
	क्रमागत hl_pm_mng_profile		pm_mng_profile;
	काष्ठा hwmon_chip_info		*hl_chip_info;

	काष्ठा hl_dbg_device_entry	hl_debugfs;

	काष्ठा list_head		cb_pool;
	spinlock_t			cb_pool_lock;

	व्योम				*पूर्णांकernal_cb_pool_virt_addr;
	dma_addr_t			पूर्णांकernal_cb_pool_dma_addr;
	काष्ठा gen_pool			*पूर्णांकernal_cb_pool;
	u64				पूर्णांकernal_cb_va_base;

	काष्ठा list_head		fpriv_list;
	काष्ठा mutex			fpriv_list_lock;

	काष्ठा hl_ctx			*compute_ctx;

	काष्ठा hl_cs_counters_atomic	aggregated_cs_counters;

	काष्ठा hl_mmu_priv		mmu_priv;
	काष्ठा hl_mmu_funcs		mmu_func[MMU_NUM_PGT_LOCATIONS];

	atomic64_t			dram_used_mem;
	u64				समयout_jअगरfies;
	u64				max_घातer;
	u64				घड़ी_gating_mask;
	u64				boot_error_status_mask;
	atomic_t			in_reset;
	क्रमागत hl_pll_frequency		curr_pll_profile;
	क्रमागत cpucp_card_types		card_type;
	u32				major;
	u32				high_pll;
	u32				soft_reset_cnt;
	u32				hard_reset_cnt;
	u32				clk_throttling_reason;
	u16				id;
	u16				id_control;
	u16				cpu_pci_msb_addr;
	u8				disabled;
	u8				late_init_करोne;
	u8				hwmon_initialized;
	u8				hard_reset_pending;
	u8				heartbeat;
	u8				reset_on_lockup;
	u8				dram_शेष_page_mapping;
	u8				memory_scrub;
	u8				pmmu_huge_range;
	u8				init_करोne;
	u8				device_cpu_disabled;
	u8				dma_mask;
	u8				in_debug;
	u8				घातer9_64bit_dma_enable;
	u8				cdev_sysfs_created;
	u8				stop_on_err;
	u8				supports_sync_stream;
	u8				sync_stream_queue_idx;
	u8				collective_mon_idx;
	u8				supports_coresight;
	u8				supports_soft_reset;
	u8				supports_cb_mapping;
	u8				needs_reset;
	u8				process_समाप्त_trial_cnt;
	u8				device_fini_pending;
	u8				supports_staged_submission;

	/* Parameters क्रम bring-up */
	u64				nic_ports_mask;
	u64				fw_components;
	u8				mmu_enable;
	u8				mmu_huge_page_opt;
	u8				reset_pcilink;
	u8				cpu_queues_enable;
	u8				pldm;
	u8				axi_drain;
	u8				sram_scrambler_enable;
	u8				dram_scrambler_enable;
	u8				hard_reset_on_fw_events;
	u8				bmc_enable;
	u8				rl_enable;
	u8				reset_on_preboot_fail;
	u8				reset_upon_device_release;
पूर्ण;


/*
 * IOCTLs
 */

/**
 * प्रकार hl_ioctl_t - प्रकार क्रम ioctl function in the driver
 * @hpriv: poपूर्णांकer to the FD's निजी data, which contains state of
 *		user process
 * @data: poपूर्णांकer to the input/output arguments काष्ठाure of the IOCTL
 *
 * Return: 0 क्रम success, negative value क्रम error
 */
प्रकार पूर्णांक hl_ioctl_t(काष्ठा hl_fpriv *hpriv, व्योम *data);

/**
 * काष्ठा hl_ioctl_desc - describes an IOCTL entry of the driver.
 * @cmd: the IOCTL code as created by the kernel macros.
 * @func: poपूर्णांकer to the driver's function that should be called क्रम this IOCTL.
 */
काष्ठा hl_ioctl_desc अणु
	अचिन्हित पूर्णांक cmd;
	hl_ioctl_t *func;
पूर्ण;


/*
 * Kernel module functions that can be accessed by entire module
 */

/**
 * hl_mem_area_inside_range() - Checks whether address+size are inside a range.
 * @address: The start address of the area we want to validate.
 * @size: The size in bytes of the area we want to validate.
 * @range_start_address: The start address of the valid range.
 * @range_end_address: The end address of the valid range.
 *
 * Return: true अगर the area is inside the valid range, false otherwise.
 */
अटल अंतरभूत bool hl_mem_area_inside_range(u64 address, u64 size,
				u64 range_start_address, u64 range_end_address)
अणु
	u64 end_address = address + size;

	अगर ((address >= range_start_address) &&
			(end_address <= range_end_address) &&
			(end_address > address))
		वापस true;

	वापस false;
पूर्ण

/**
 * hl_mem_area_crosses_range() - Checks whether address+size crossing a range.
 * @address: The start address of the area we want to validate.
 * @size: The size in bytes of the area we want to validate.
 * @range_start_address: The start address of the valid range.
 * @range_end_address: The end address of the valid range.
 *
 * Return: true अगर the area overlaps part or all of the valid range,
 *		false otherwise.
 */
अटल अंतरभूत bool hl_mem_area_crosses_range(u64 address, u32 size,
				u64 range_start_address, u64 range_end_address)
अणु
	u64 end_address = address + size;

	अगर ((address >= range_start_address) &&
			(address < range_end_address))
		वापस true;

	अगर ((end_address >= range_start_address) &&
			(end_address < range_end_address))
		वापस true;

	अगर ((address < range_start_address) &&
			(end_address >= range_end_address))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक hl_device_खोलो(काष्ठा inode *inode, काष्ठा file *filp);
पूर्णांक hl_device_खोलो_ctrl(काष्ठा inode *inode, काष्ठा file *filp);
bool hl_device_operational(काष्ठा hl_device *hdev,
		क्रमागत hl_device_status *status);
क्रमागत hl_device_status hl_device_status(काष्ठा hl_device *hdev);
पूर्णांक hl_device_set_debug_mode(काष्ठा hl_device *hdev, bool enable);
पूर्णांक create_hdev(काष्ठा hl_device **dev, काष्ठा pci_dev *pdev,
		क्रमागत hl_asic_type asic_type, पूर्णांक minor);
व्योम destroy_hdev(काष्ठा hl_device *hdev);
पूर्णांक hl_hw_queues_create(काष्ठा hl_device *hdev);
व्योम hl_hw_queues_destroy(काष्ठा hl_device *hdev);
पूर्णांक hl_hw_queue_send_cb_no_cmpl(काष्ठा hl_device *hdev, u32 hw_queue_id,
				u32 cb_size, u64 cb_ptr);
पूर्णांक hl_hw_queue_schedule_cs(काष्ठा hl_cs *cs);
u32 hl_hw_queue_add_ptr(u32 ptr, u16 val);
व्योम hl_hw_queue_inc_ci_kernel(काष्ठा hl_device *hdev, u32 hw_queue_id);
व्योम hl_hw_queue_update_ci(काष्ठा hl_cs *cs);
व्योम hl_hw_queue_reset(काष्ठा hl_device *hdev, bool hard_reset);

#घोषणा hl_queue_inc_ptr(p)		hl_hw_queue_add_ptr(p, 1)
#घोषणा hl_pi_2_offset(pi)		((pi) & (HL_QUEUE_LENGTH - 1))

पूर्णांक hl_cq_init(काष्ठा hl_device *hdev, काष्ठा hl_cq *q, u32 hw_queue_id);
व्योम hl_cq_fini(काष्ठा hl_device *hdev, काष्ठा hl_cq *q);
पूर्णांक hl_eq_init(काष्ठा hl_device *hdev, काष्ठा hl_eq *q);
व्योम hl_eq_fini(काष्ठा hl_device *hdev, काष्ठा hl_eq *q);
व्योम hl_cq_reset(काष्ठा hl_device *hdev, काष्ठा hl_cq *q);
व्योम hl_eq_reset(काष्ठा hl_device *hdev, काष्ठा hl_eq *q);
irqवापस_t hl_irq_handler_cq(पूर्णांक irq, व्योम *arg);
irqवापस_t hl_irq_handler_eq(पूर्णांक irq, व्योम *arg);
irqवापस_t hl_irq_handler_user_cq(पूर्णांक irq, व्योम *arg);
irqवापस_t hl_irq_handler_शेष(पूर्णांक irq, व्योम *arg);
u32 hl_cq_inc_ptr(u32 ptr);

पूर्णांक hl_asid_init(काष्ठा hl_device *hdev);
व्योम hl_asid_fini(काष्ठा hl_device *hdev);
अचिन्हित दीर्घ hl_asid_alloc(काष्ठा hl_device *hdev);
व्योम hl_asid_मुक्त(काष्ठा hl_device *hdev, अचिन्हित दीर्घ asid);

पूर्णांक hl_ctx_create(काष्ठा hl_device *hdev, काष्ठा hl_fpriv *hpriv);
व्योम hl_ctx_मुक्त(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx);
पूर्णांक hl_ctx_init(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx, bool is_kernel_ctx);
व्योम hl_ctx_करो_release(काष्ठा kref *ref);
व्योम hl_ctx_get(काष्ठा hl_device *hdev,	काष्ठा hl_ctx *ctx);
पूर्णांक hl_ctx_put(काष्ठा hl_ctx *ctx);
काष्ठा hl_fence *hl_ctx_get_fence(काष्ठा hl_ctx *ctx, u64 seq);
व्योम hl_ctx_mgr_init(काष्ठा hl_ctx_mgr *mgr);
व्योम hl_ctx_mgr_fini(काष्ठा hl_device *hdev, काष्ठा hl_ctx_mgr *mgr);

पूर्णांक hl_device_init(काष्ठा hl_device *hdev, काष्ठा class *hclass);
व्योम hl_device_fini(काष्ठा hl_device *hdev);
पूर्णांक hl_device_suspend(काष्ठा hl_device *hdev);
पूर्णांक hl_device_resume(काष्ठा hl_device *hdev);
पूर्णांक hl_device_reset(काष्ठा hl_device *hdev, u32 flags);
व्योम hl_hpriv_get(काष्ठा hl_fpriv *hpriv);
पूर्णांक hl_hpriv_put(काष्ठा hl_fpriv *hpriv);
पूर्णांक hl_device_set_frequency(काष्ठा hl_device *hdev, क्रमागत hl_pll_frequency freq);
पूर्णांक hl_device_utilization(काष्ठा hl_device *hdev, u32 *utilization);

पूर्णांक hl_build_hwmon_channel_info(काष्ठा hl_device *hdev,
		काष्ठा cpucp_sensor *sensors_arr);

पूर्णांक hl_sysfs_init(काष्ठा hl_device *hdev);
व्योम hl_sysfs_fini(काष्ठा hl_device *hdev);

पूर्णांक hl_hwmon_init(काष्ठा hl_device *hdev);
व्योम hl_hwmon_fini(काष्ठा hl_device *hdev);

पूर्णांक hl_cb_create(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr,
			काष्ठा hl_ctx *ctx, u32 cb_size, bool पूर्णांकernal_cb,
			bool map_cb, u64 *handle);
पूर्णांक hl_cb_destroy(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr, u64 cb_handle);
पूर्णांक hl_cb_mmap(काष्ठा hl_fpriv *hpriv, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक hl_hw_block_mmap(काष्ठा hl_fpriv *hpriv, काष्ठा vm_area_काष्ठा *vma);
काष्ठा hl_cb *hl_cb_get(काष्ठा hl_device *hdev,	काष्ठा hl_cb_mgr *mgr,
			u32 handle);
व्योम hl_cb_put(काष्ठा hl_cb *cb);
व्योम hl_cb_mgr_init(काष्ठा hl_cb_mgr *mgr);
व्योम hl_cb_mgr_fini(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr);
काष्ठा hl_cb *hl_cb_kernel_create(काष्ठा hl_device *hdev, u32 cb_size,
					bool पूर्णांकernal_cb);
पूर्णांक hl_cb_pool_init(काष्ठा hl_device *hdev);
पूर्णांक hl_cb_pool_fini(काष्ठा hl_device *hdev);
पूर्णांक hl_cb_va_pool_init(काष्ठा hl_ctx *ctx);
व्योम hl_cb_va_pool_fini(काष्ठा hl_ctx *ctx);

व्योम hl_cs_rollback_all(काष्ठा hl_device *hdev);
व्योम hl_pending_cb_list_flush(काष्ठा hl_ctx *ctx);
काष्ठा hl_cs_job *hl_cs_allocate_job(काष्ठा hl_device *hdev,
		क्रमागत hl_queue_type queue_type, bool is_kernel_allocated_cb);
व्योम hl_sob_reset_error(काष्ठा kref *ref);
पूर्णांक hl_gen_sob_mask(u16 sob_base, u8 sob_mask, u8 *mask);
व्योम hl_fence_put(काष्ठा hl_fence *fence);
व्योम hl_fence_get(काष्ठा hl_fence *fence);
व्योम cs_get(काष्ठा hl_cs *cs);
bool cs_needs_completion(काष्ठा hl_cs *cs);
bool cs_needs_समयout(काष्ठा hl_cs *cs);
bool is_staged_cs_last_exists(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs);
काष्ठा hl_cs *hl_staged_cs_find_first(काष्ठा hl_device *hdev, u64 cs_seq);

व्योम goya_set_asic_funcs(काष्ठा hl_device *hdev);
व्योम gaudi_set_asic_funcs(काष्ठा hl_device *hdev);

पूर्णांक hl_vm_ctx_init(काष्ठा hl_ctx *ctx);
व्योम hl_vm_ctx_fini(काष्ठा hl_ctx *ctx);

पूर्णांक hl_vm_init(काष्ठा hl_device *hdev);
व्योम hl_vm_fini(काष्ठा hl_device *hdev);

व्योम hl_hw_block_mem_init(काष्ठा hl_ctx *ctx);
व्योम hl_hw_block_mem_fini(काष्ठा hl_ctx *ctx);

u64 hl_reserve_va_block(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
		क्रमागत hl_va_range_type type, u32 size, u32 alignment);
पूर्णांक hl_unreserve_va_block(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
		u64 start_addr, u64 size);
पूर्णांक hl_pin_host_memory(काष्ठा hl_device *hdev, u64 addr, u64 size,
			काष्ठा hl_userptr *userptr);
व्योम hl_unpin_host_memory(काष्ठा hl_device *hdev, काष्ठा hl_userptr *userptr);
व्योम hl_userptr_delete_list(काष्ठा hl_device *hdev,
				काष्ठा list_head *userptr_list);
bool hl_userptr_is_pinned(काष्ठा hl_device *hdev, u64 addr, u32 size,
				काष्ठा list_head *userptr_list,
				काष्ठा hl_userptr **userptr);

पूर्णांक hl_mmu_init(काष्ठा hl_device *hdev);
व्योम hl_mmu_fini(काष्ठा hl_device *hdev);
पूर्णांक hl_mmu_ctx_init(काष्ठा hl_ctx *ctx);
व्योम hl_mmu_ctx_fini(काष्ठा hl_ctx *ctx);
पूर्णांक hl_mmu_map_page(काष्ठा hl_ctx *ctx, u64 virt_addr, u64 phys_addr,
		u32 page_size, bool flush_pte);
पूर्णांक hl_mmu_unmap_page(काष्ठा hl_ctx *ctx, u64 virt_addr, u32 page_size,
		bool flush_pte);
पूर्णांक hl_mmu_map_contiguous(काष्ठा hl_ctx *ctx, u64 virt_addr,
					u64 phys_addr, u32 size);
पूर्णांक hl_mmu_unmap_contiguous(काष्ठा hl_ctx *ctx, u64 virt_addr, u32 size);
व्योम hl_mmu_swap_out(काष्ठा hl_ctx *ctx);
व्योम hl_mmu_swap_in(काष्ठा hl_ctx *ctx);
पूर्णांक hl_mmu_अगर_set_funcs(काष्ठा hl_device *hdev);
व्योम hl_mmu_v1_set_funcs(काष्ठा hl_device *hdev, काष्ठा hl_mmu_funcs *mmu);
पूर्णांक hl_mmu_va_to_pa(काष्ठा hl_ctx *ctx, u64 virt_addr, u64 *phys_addr);
पूर्णांक hl_mmu_get_tlb_info(काष्ठा hl_ctx *ctx, u64 virt_addr,
			काष्ठा hl_mmu_hop_info *hops);
u64 hl_mmu_scramble_addr(काष्ठा hl_device *hdev, u64 addr);
u64 hl_mmu_descramble_addr(काष्ठा hl_device *hdev, u64 addr);
bool hl_is_dram_va(काष्ठा hl_device *hdev, u64 virt_addr);

पूर्णांक hl_fw_load_fw_to_device(काष्ठा hl_device *hdev, स्थिर अक्षर *fw_name,
				व्योम __iomem *dst, u32 src_offset, u32 size);
पूर्णांक hl_fw_send_pci_access_msg(काष्ठा hl_device *hdev, u32 opcode);
पूर्णांक hl_fw_send_cpu_message(काष्ठा hl_device *hdev, u32 hw_queue_id, u32 *msg,
				u16 len, u32 समयout, u64 *result);
पूर्णांक hl_fw_unmask_irq(काष्ठा hl_device *hdev, u16 event_type);
पूर्णांक hl_fw_unmask_irq_arr(काष्ठा hl_device *hdev, स्थिर u32 *irq_arr,
		माप_प्रकार irq_arr_size);
पूर्णांक hl_fw_test_cpu_queue(काष्ठा hl_device *hdev);
व्योम *hl_fw_cpu_accessible_dma_pool_alloc(काष्ठा hl_device *hdev, माप_प्रकार size,
						dma_addr_t *dma_handle);
व्योम hl_fw_cpu_accessible_dma_pool_मुक्त(काष्ठा hl_device *hdev, माप_प्रकार size,
					व्योम *vaddr);
पूर्णांक hl_fw_send_heartbeat(काष्ठा hl_device *hdev);
पूर्णांक hl_fw_cpucp_info_get(काष्ठा hl_device *hdev,
			u32 cpu_security_boot_status_reg,
			u32 boot_err0_reg);
पूर्णांक hl_fw_cpucp_handshake(काष्ठा hl_device *hdev,
			u32 cpu_security_boot_status_reg,
			u32 boot_err0_reg);
पूर्णांक hl_fw_get_eeprom_data(काष्ठा hl_device *hdev, व्योम *data, माप_प्रकार max_size);
पूर्णांक hl_fw_cpucp_pci_counters_get(काष्ठा hl_device *hdev,
		काष्ठा hl_info_pci_counters *counters);
पूर्णांक hl_fw_cpucp_total_energy_get(काष्ठा hl_device *hdev,
			u64 *total_energy);
पूर्णांक get_used_pll_index(काष्ठा hl_device *hdev, u32 input_pll_index,
						क्रमागत pll_index *pll_index);
पूर्णांक hl_fw_cpucp_pll_info_get(काष्ठा hl_device *hdev, u32 pll_index,
		u16 *pll_freq_arr);
पूर्णांक hl_fw_cpucp_घातer_get(काष्ठा hl_device *hdev, u64 *घातer);
पूर्णांक hl_fw_init_cpu(काष्ठा hl_device *hdev, u32 cpu_boot_status_reg,
			u32 msg_to_cpu_reg, u32 cpu_msg_status_reg,
			u32 cpu_security_boot_status_reg, u32 boot_err0_reg,
			bool skip_bmc, u32 cpu_समयout, u32 boot_fit_समयout);
पूर्णांक hl_fw_पढ़ो_preboot_status(काष्ठा hl_device *hdev, u32 cpu_boot_status_reg,
		u32 cpu_security_boot_status_reg, u32 boot_err0_reg,
		u32 समयout);

पूर्णांक hl_pci_bars_map(काष्ठा hl_device *hdev, स्थिर अक्षर * स्थिर name[3],
			bool is_wc[3]);
पूर्णांक hl_pci_elbi_पढ़ो(काष्ठा hl_device *hdev, u64 addr, u32 *data);
पूर्णांक hl_pci_iatu_ग_लिखो(काष्ठा hl_device *hdev, u32 addr, u32 data);
पूर्णांक hl_pci_set_inbound_region(काष्ठा hl_device *hdev, u8 region,
		काष्ठा hl_inbound_pci_region *pci_region);
पूर्णांक hl_pci_set_outbound_region(काष्ठा hl_device *hdev,
		काष्ठा hl_outbound_pci_region *pci_region);
पूर्णांक hl_pci_init(काष्ठा hl_device *hdev);
व्योम hl_pci_fini(काष्ठा hl_device *hdev);

दीर्घ hl_get_frequency(काष्ठा hl_device *hdev, u32 pll_index,
								bool curr);
व्योम hl_set_frequency(काष्ठा hl_device *hdev, u32 pll_index,
								u64 freq);
पूर्णांक hl_get_temperature(काष्ठा hl_device *hdev,
		       पूर्णांक sensor_index, u32 attr, दीर्घ *value);
पूर्णांक hl_set_temperature(काष्ठा hl_device *hdev,
		       पूर्णांक sensor_index, u32 attr, दीर्घ value);
पूर्णांक hl_get_voltage(काष्ठा hl_device *hdev,
		   पूर्णांक sensor_index, u32 attr, दीर्घ *value);
पूर्णांक hl_get_current(काष्ठा hl_device *hdev,
		   पूर्णांक sensor_index, u32 attr, दीर्घ *value);
पूर्णांक hl_get_fan_speed(काष्ठा hl_device *hdev,
		     पूर्णांक sensor_index, u32 attr, दीर्घ *value);
पूर्णांक hl_get_pwm_info(काष्ठा hl_device *hdev,
		    पूर्णांक sensor_index, u32 attr, दीर्घ *value);
व्योम hl_set_pwm_info(काष्ठा hl_device *hdev, पूर्णांक sensor_index, u32 attr,
			दीर्घ value);
u64 hl_get_max_घातer(काष्ठा hl_device *hdev);
व्योम hl_set_max_घातer(काष्ठा hl_device *hdev);
पूर्णांक hl_set_voltage(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ value);
पूर्णांक hl_set_current(काष्ठा hl_device *hdev,
			पूर्णांक sensor_index, u32 attr, दीर्घ value);
व्योम hl_release_pending_user_पूर्णांकerrupts(काष्ठा hl_device *hdev);

#अगर_घोषित CONFIG_DEBUG_FS

व्योम hl_debugfs_init(व्योम);
व्योम hl_debugfs_fini(व्योम);
व्योम hl_debugfs_add_device(काष्ठा hl_device *hdev);
व्योम hl_debugfs_हटाओ_device(काष्ठा hl_device *hdev);
व्योम hl_debugfs_add_file(काष्ठा hl_fpriv *hpriv);
व्योम hl_debugfs_हटाओ_file(काष्ठा hl_fpriv *hpriv);
व्योम hl_debugfs_add_cb(काष्ठा hl_cb *cb);
व्योम hl_debugfs_हटाओ_cb(काष्ठा hl_cb *cb);
व्योम hl_debugfs_add_cs(काष्ठा hl_cs *cs);
व्योम hl_debugfs_हटाओ_cs(काष्ठा hl_cs *cs);
व्योम hl_debugfs_add_job(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job);
व्योम hl_debugfs_हटाओ_job(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job);
व्योम hl_debugfs_add_userptr(काष्ठा hl_device *hdev, काष्ठा hl_userptr *userptr);
व्योम hl_debugfs_हटाओ_userptr(काष्ठा hl_device *hdev,
				काष्ठा hl_userptr *userptr);
व्योम hl_debugfs_add_ctx_mem_hash(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx);
व्योम hl_debugfs_हटाओ_ctx_mem_hash(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx);

#अन्यथा

अटल अंतरभूत व्योम __init hl_debugfs_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_fini(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_device(काष्ठा hl_device *hdev)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_device(काष्ठा hl_device *hdev)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_file(काष्ठा hl_fpriv *hpriv)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_file(काष्ठा hl_fpriv *hpriv)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_cb(काष्ठा hl_cb *cb)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_cb(काष्ठा hl_cb *cb)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_cs(काष्ठा hl_cs *cs)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_cs(काष्ठा hl_cs *cs)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_job(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_job *job)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_job(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_job *job)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_userptr(काष्ठा hl_device *hdev,
					काष्ठा hl_userptr *userptr)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_userptr(काष्ठा hl_device *hdev,
					काष्ठा hl_userptr *userptr)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_add_ctx_mem_hash(काष्ठा hl_device *hdev,
					काष्ठा hl_ctx *ctx)
अणु
पूर्ण

अटल अंतरभूत व्योम hl_debugfs_हटाओ_ctx_mem_hash(काष्ठा hl_device *hdev,
					काष्ठा hl_ctx *ctx)
अणु
पूर्ण

#पूर्ण_अगर

/* IOCTLs */
दीर्घ hl_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ hl_ioctl_control(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक hl_cb_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data);
पूर्णांक hl_cs_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data);
पूर्णांक hl_रुको_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data);
पूर्णांक hl_mem_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data);

#पूर्ण_अगर /* HABANALABSP_H_ */
