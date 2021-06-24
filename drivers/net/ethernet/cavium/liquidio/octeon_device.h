<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*! \पile octeon_device.h
 *  \मrief Host Driver: This file defines the octeon device काष्ठाure.
 */

#अगर_अघोषित _OCTEON_DEVICE_H_
#घोषणा  _OCTEON_DEVICE_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/devlink.h>

/** PCI VenकरोrId Device Id */
#घोषणा  OCTEON_CN68XX_PCIID          0x91177d
#घोषणा  OCTEON_CN66XX_PCIID          0x92177d
#घोषणा  OCTEON_CN23XX_PCIID_PF       0x9702177d
/** Driver identअगरies chips by these Ids, created by clubbing together
 *  DeviceId+RevisionId; Where Revision Id is not used to distinguish
 *  between chips, a value of 0 is used क्रम revision id.
 */
#घोषणा  OCTEON_CN68XX                0x0091
#घोषणा  OCTEON_CN66XX                0x0092
#घोषणा  OCTEON_CN23XX_PF_VID         0x9702
#घोषणा  OCTEON_CN23XX_VF_VID         0x9712

/**RevisionId क्रम the chips */
#घोषणा  OCTEON_CN23XX_REV_1_0        0x00
#घोषणा  OCTEON_CN23XX_REV_1_1        0x01
#घोषणा  OCTEON_CN23XX_REV_2_0        0x80

/**Subप्रणालीId क्रम the chips */
#घोषणा	 OCTEON_CN2350_10GB_SUBSYS_ID_1	0X3177d
#घोषणा	 OCTEON_CN2350_10GB_SUBSYS_ID_2	0X4177d
#घोषणा	 OCTEON_CN2360_10GB_SUBSYS_ID	0X5177d
#घोषणा	 OCTEON_CN2350_25GB_SUBSYS_ID	0X7177d
#घोषणा	 OCTEON_CN2360_25GB_SUBSYS_ID	0X6177d

/** Endian-swap modes supported by Octeon. */
क्रमागत octeon_pci_swap_mode अणु
	OCTEON_PCI_PASSTHROUGH = 0,
	OCTEON_PCI_64BIT_SWAP = 1,
	OCTEON_PCI_32BIT_BYTE_SWAP = 2,
	OCTEON_PCI_32BIT_LW_SWAP = 3
पूर्ण;

क्रमागत lio_fw_state अणु
	FW_IS_PRELOADED = 0,
	FW_NEEDS_TO_BE_LOADED = 1,
	FW_IS_BEING_LOADED = 2,
	FW_HAS_BEEN_LOADED = 3,
पूर्ण;

क्रमागत अणु
	OCTEON_CONFIG_TYPE_DEFAULT = 0,
	NUM_OCTEON_CONFS,
पूर्ण;

#घोषणा  OCTEON_INPUT_INTR    (1)
#घोषणा  OCTEON_OUTPUT_INTR   (2)
#घोषणा  OCTEON_MBOX_INTR     (4)
#घोषणा  OCTEON_ALL_INTR      0xff

/*---------------   PCI BAR1 index रेजिस्टरs -------------*/

/* BAR1 Mask */
#घोषणा    PCI_BAR1_ENABLE_CA            1
#घोषणा    PCI_BAR1_ENDIAN_MODE          OCTEON_PCI_64BIT_SWAP
#घोषणा    PCI_BAR1_ENTRY_VALID          1
#घोषणा    PCI_BAR1_MASK                 ((PCI_BAR1_ENABLE_CA << 3)   \
					    | (PCI_BAR1_ENDIAN_MODE << 1) \
					    | PCI_BAR1_ENTRY_VALID)

/** Octeon Device state.
 *  Each octeon device goes through each of these states
 *  as it is initialized.
 */
#घोषणा    OCT_DEV_BEGIN_STATE            0x0
#घोषणा    OCT_DEV_PCI_ENABLE_DONE        0x1
#घोषणा    OCT_DEV_PCI_MAP_DONE           0x2
#घोषणा    OCT_DEV_DISPATCH_INIT_DONE     0x3
#घोषणा    OCT_DEV_INSTR_QUEUE_INIT_DONE  0x4
#घोषणा    OCT_DEV_SC_BUFF_POOL_INIT_DONE 0x5
#घोषणा    OCT_DEV_RESP_LIST_INIT_DONE    0x6
#घोषणा    OCT_DEV_DROQ_INIT_DONE         0x7
#घोषणा    OCT_DEV_MBOX_SETUP_DONE        0x8
#घोषणा    OCT_DEV_MSIX_ALLOC_VECTOR_DONE 0x9
#घोषणा    OCT_DEV_INTR_SET_DONE          0xa
#घोषणा    OCT_DEV_IO_QUEUES_DONE         0xb
#घोषणा    OCT_DEV_CONSOLE_INIT_DONE      0xc
#घोषणा    OCT_DEV_HOST_OK                0xd
#घोषणा    OCT_DEV_CORE_OK                0xe
#घोषणा    OCT_DEV_RUNNING                0xf
#घोषणा    OCT_DEV_IN_RESET               0x10
#घोषणा    OCT_DEV_STATE_INVALID          0x11

#घोषणा    OCT_DEV_STATES                 OCT_DEV_STATE_INVALID

/** Octeon Device पूर्णांकerrupts
 * These पूर्णांकerrupt bits are set in पूर्णांक_status filed of
 * octeon_device काष्ठाure
 */
#घोषणा	   OCT_DEV_INTR_DMA0_FORCE	  0x01
#घोषणा	   OCT_DEV_INTR_DMA1_FORCE	  0x02
#घोषणा	   OCT_DEV_INTR_PKT_DATA	  0x04

#घोषणा LIO_RESET_SECS (3)

/*---------------------------DISPATCH LIST-------------------------------*/

/** The dispatch list entry.
 *  The driver keeps a record of functions रेजिस्टरed क्रम each
 *  response header opcode in this काष्ठाure. Since the opcode is
 *  hashed to index पूर्णांकo the driver's list, more than one opcode
 *  can hash to the same entry, in which हाल the list field poपूर्णांकs
 *  to a linked list with the other entries.
 */
काष्ठा octeon_dispatch अणु
	/** List head क्रम this entry */
	काष्ठा list_head list;

	/** The opcode क्रम which the dispatch function & arg should be used */
	u16 opcode;

	/** The function to be called क्रम a packet received by the driver */
	octeon_dispatch_fn_t dispatch_fn;

	/* The application specअगरied argument to be passed to the above
	 * function aदीर्घ with the received packet
	 */
	व्योम *arg;
पूर्ण;

/** The dispatch list काष्ठाure. */
काष्ठा octeon_dispatch_list अणु
	/** access to dispatch list must be atomic */
	spinlock_t lock;

	/** Count of dispatch functions currently रेजिस्टरed */
	u32 count;

	/** The list of dispatch functions */
	काष्ठा octeon_dispatch *dlist;
पूर्ण;

/*-----------------------  THE OCTEON DEVICE  ---------------------------*/

#घोषणा OCT_MEM_REGIONS     3
/** PCI address space mapping inक्रमmation.
 *  Each of the 3 address spaces given by BAR0, BAR2 and BAR4 of
 *  Octeon माला_लो mapped to dअगरferent physical address spaces in
 *  the kernel.
 */
काष्ठा octeon_mmio अणु
	/** PCI address to which the BAR is mapped. */
	u64 start;

	/** Length of this PCI address space. */
	u32 len;

	/** Length that has been mapped to phys. address space. */
	u32 mapped_len;

	/** The physical address to which the PCI address space is mapped. */
	u8 __iomem *hw_addr;

	/** Flag indicating the mapping was successful. */
	u32 करोne;
पूर्ण;

#घोषणा   MAX_OCTEON_MAPS    32

काष्ठा octeon_io_enable अणु
	u64 iq;
	u64 oq;
	u64 iq64B;
पूर्ण;

काष्ठा octeon_reg_list अणु
	u32 __iomem *pci_win_wr_addr_hi;
	u32 __iomem *pci_win_wr_addr_lo;
	u64 __iomem *pci_win_wr_addr;

	u32 __iomem *pci_win_rd_addr_hi;
	u32 __iomem *pci_win_rd_addr_lo;
	u64 __iomem *pci_win_rd_addr;

	u32 __iomem *pci_win_wr_data_hi;
	u32 __iomem *pci_win_wr_data_lo;
	u64 __iomem *pci_win_wr_data;

	u32 __iomem *pci_win_rd_data_hi;
	u32 __iomem *pci_win_rd_data_lo;
	u64 __iomem *pci_win_rd_data;
पूर्ण;

#घोषणा OCTEON_CONSOLE_MAX_READ_BYTES 512
प्रकार पूर्णांक (*octeon_console_prपूर्णांक_fn)(काष्ठा octeon_device *oct,
				       u32 num, अक्षर *pre, अक्षर *suf);
काष्ठा octeon_console अणु
	u32 active;
	u32 रुकोing;
	u64 addr;
	u32 buffer_size;
	u64 input_base_addr;
	u64 output_base_addr;
	octeon_console_prपूर्णांक_fn prपूर्णांक;
	अक्षर leftover[OCTEON_CONSOLE_MAX_READ_BYTES];
पूर्ण;

काष्ठा octeon_board_info अणु
	अक्षर name[OCT_BOARD_NAME];
	अक्षर serial_number[OCT_SERIAL_LEN];
	u64 major;
	u64 minor;
पूर्ण;

काष्ठा octeon_fn_list अणु
	व्योम (*setup_iq_regs)(काष्ठा octeon_device *, u32);
	व्योम (*setup_oq_regs)(काष्ठा octeon_device *, u32);

	irqवापस_t (*process_पूर्णांकerrupt_regs)(व्योम *);
	u64 (*msix_पूर्णांकerrupt_handler)(व्योम *);

	पूर्णांक (*setup_mbox)(काष्ठा octeon_device *);
	पूर्णांक (*मुक्त_mbox)(काष्ठा octeon_device *);

	पूर्णांक (*soft_reset)(काष्ठा octeon_device *);
	पूर्णांक (*setup_device_regs)(काष्ठा octeon_device *);
	व्योम (*bar1_idx_setup)(काष्ठा octeon_device *, u64, u32, पूर्णांक);
	व्योम (*bar1_idx_ग_लिखो)(काष्ठा octeon_device *, u32, u32);
	u32 (*bar1_idx_पढ़ो)(काष्ठा octeon_device *, u32);
	u32 (*update_iq_पढ़ो_idx)(काष्ठा octeon_instr_queue *);

	व्योम (*enable_oq_pkt_समय_पूर्णांकr)(काष्ठा octeon_device *, u32);
	व्योम (*disable_oq_pkt_समय_पूर्णांकr)(काष्ठा octeon_device *, u32);

	व्योम (*enable_पूर्णांकerrupt)(काष्ठा octeon_device *, u8);
	व्योम (*disable_पूर्णांकerrupt)(काष्ठा octeon_device *, u8);

	पूर्णांक (*enable_io_queues)(काष्ठा octeon_device *);
	व्योम (*disable_io_queues)(काष्ठा octeon_device *);
पूर्ण;

/* Must be multiple of 8, changing अवरोधs ABI */
#घोषणा CVMX_BOOTMEM_NAME_LEN 128

/* Structure क्रम named memory blocks
 * Number of descriptors
 * available can be changed without affecting compatibility,
 * but name length changes require a bump in the booपंचांगem
 * descriptor version
 * Note: This काष्ठाure must be naturally 64 bit aligned, as a single
 * memory image will be used by both 32 and 64 bit programs.
 */
काष्ठा cvmx_booपंचांगem_named_block_desc अणु
	/** Base address of named block */
	u64 base_addr;

	/** Size actually allocated क्रम named block */
	u64 size;

	/** name of named block */
	अक्षर name[CVMX_BOOTMEM_NAME_LEN];
पूर्ण;

काष्ठा oct_fw_info अणु
	u32 max_nic_ports;      /** max nic ports क्रम the device */
	u32 num_gmx_ports;      /** num gmx ports */
	u64 app_cap_flags;      /** firmware cap flags */

	/** The core application is running in this mode.
	 * See octeon-drv-opcodes.h क्रम values.
	 */
	u32 app_mode;
	अक्षर   liquidio_firmware_version[32];
	/* Fields extracted from legacy string 'liquidio_firmware_version' */
	काष्ठा अणु
		u8  maj;
		u8  min;
		u8  rev;
	पूर्ण ver;
पूर्ण;

#घोषणा OCT_FW_VER(maj, min, rev) \
	(((u32)(maj) << 16) | ((u32)(min) << 8) | ((u32)(rev)))

/* wrappers around work काष्ठाs */
काष्ठा cavium_wk अणु
	काष्ठा delayed_work work;
	व्योम *ctxptr;
	u64 ctxul;
पूर्ण;

काष्ठा cavium_wq अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा cavium_wk wk;
पूर्ण;

काष्ठा octdev_props अणु
	/* Each पूर्णांकerface in the Octeon device has a network
	 * device poपूर्णांकer (used क्रम OS specअगरic calls).
	 */
	पूर्णांक    rx_on;
	पूर्णांक    fec;
	पूर्णांक    fec_boot;
	पूर्णांक    napi_enabled;
	पूर्णांक    gmxport;
	काष्ठा net_device *netdev;
पूर्ण;

#घोषणा LIO_FLAG_MSIX_ENABLED	0x1
#घोषणा MSIX_PO_INT		0x1
#घोषणा MSIX_PI_INT		0x2
#घोषणा MSIX_MBOX_INT		0x4

काष्ठा octeon_pf_vf_hs_word अणु
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	/** PKIND value asचिन्हित क्रम the DPI पूर्णांकerface */
	u64        pkind : 8;

	/** OCTEON core घड़ी multiplier   */
	u64        core_tics_per_us : 16;

	/** OCTEON coprocessor घड़ी multiplier  */
	u64        coproc_tics_per_us : 16;

	/** app that currently running on OCTEON  */
	u64        app_mode : 8;

	/** RESERVED */
	u64 reserved : 16;

#अन्यथा

	/** RESERVED */
	u64 reserved : 16;

	/** app that currently running on OCTEON  */
	u64        app_mode : 8;

	/** OCTEON coprocessor घड़ी multiplier  */
	u64        coproc_tics_per_us : 16;

	/** OCTEON core घड़ी multiplier   */
	u64        core_tics_per_us : 16;

	/** PKIND value asचिन्हित क्रम the DPI पूर्णांकerface */
	u64        pkind : 8;
#पूर्ण_अगर
पूर्ण;

काष्ठा octeon_sriov_info अणु
	/* Number of rings asचिन्हित to VF */
	u32	rings_per_vf;

	/** Max Number of VF devices that can be enabled. This variable can
	 *  specअगरied during load समय or it will be derived after allocating
	 *  PF queues. When max_vfs is derived then each VF will get one queue
	 **/
	u32	max_vfs;

	/** Number of VF devices enabled using sysfs. */
	u32	num_vfs_alloced;

	/* Actual rings left क्रम PF device */
	u32	num_pf_rings;

	/* SRN of PF usable IO queues */
	u32	pf_srn;

	/* total pf rings */
	u32	trs;

	u32	sriov_enabled;

	काष्ठा lio_trusted_vf	trusted_vf;

	/*lookup table that maps DPI ring number to VF pci_dev काष्ठा poपूर्णांकer*/
	काष्ठा pci_dev *dpiring_to_vfpcidev_lut[MAX_POSSIBLE_VFS];

	u64	vf_macaddr[MAX_POSSIBLE_VFS];

	u16	vf_vlantci[MAX_POSSIBLE_VFS];

	पूर्णांक	vf_linkstate[MAX_POSSIBLE_VFS];

	bool    vf_spoofchk[MAX_POSSIBLE_VFS];

	u64	vf_drv_loaded_mask;
पूर्ण;

काष्ठा octeon_ioq_vector अणु
	काष्ठा octeon_device   *oct_dev;
	पूर्णांक		        iq_index;
	पूर्णांक		        droq_index;
	पूर्णांक			vector;
	काष्ठा octeon_mbox     *mbox;
	काष्ठा cpumask		affinity_mask;
	u32			ioq_num;
पूर्ण;

काष्ठा lio_vf_rep_list अणु
	पूर्णांक num_vfs;
	काष्ठा net_device *ndev[CN23XX_MAX_VFS_PER_PF];
पूर्ण;

काष्ठा lio_devlink_priv अणु
	काष्ठा octeon_device *oct;
पूर्ण;

/** The Octeon device.
 *  Each Octeon device has this काष्ठाure to represent all its
 *  components.
 */
काष्ठा octeon_device अणु
	/** Lock क्रम PCI winकरोw configuration accesses */
	spinlock_t pci_win_lock;

	/** Lock क्रम memory accesses */
	spinlock_t mem_access_lock;

	/** PCI device poपूर्णांकer */
	काष्ठा pci_dev *pci_dev;

	/** Chip specअगरic inक्रमmation. */
	व्योम *chip;

	/** Number of पूर्णांकerfaces detected in this octeon device. */
	u32 अगरcount;

	काष्ठा octdev_props props[MAX_OCTEON_LINKS];

	/** Octeon Chip type. */
	u16 chip_id;

	u16 rev_id;

	u32 subप्रणाली_id;

	u16 pf_num;

	u16 vf_num;

	/** This device's id - set by the driver. */
	u32 octeon_id;

	/** This device's PCIe port used क्रम traffic. */
	u16 pcie_port;

	u16 flags;
#घोषणा LIO_FLAG_MSI_ENABLED                  (u32)(1 << 1)

	/** The state of this device */
	atomic_t status;

	/** memory mapped io range */
	काष्ठा octeon_mmio mmio[OCT_MEM_REGIONS];

	काष्ठा octeon_reg_list reg_list;

	काष्ठा octeon_fn_list fn_list;

	काष्ठा octeon_board_info boardinfo;

	u32 num_iqs;

	/* The pool containing pre allocated buffers used क्रम soft commands */
	काष्ठा octeon_sc_buffer_pool	sc_buf_pool;

	/** The input inकाष्ठाion queues */
	काष्ठा octeon_instr_queue *instr_queue
		[MAX_POSSIBLE_OCTEON_INSTR_QUEUES];

	/** The करोubly-linked list of inकाष्ठाion response */
	काष्ठा octeon_response_list response_list[MAX_RESPONSE_LISTS];

	u32 num_oqs;

	/** The DROQ output queues  */
	काष्ठा octeon_droq *droq[MAX_POSSIBLE_OCTEON_OUTPUT_QUEUES];

	काष्ठा octeon_io_enable io_qmask;

	/** List of dispatch functions */
	काष्ठा octeon_dispatch_list dispatch;

	u32 पूर्णांक_status;

	u64 droq_पूर्णांकr;

	/** Physical location of the cvmx_booपंचांगem_desc_t in octeon memory */
	u64 booपंचांगem_desc_addr;

	/** Placeholder memory क्रम named blocks.
	 * Assumes single-thपढ़ोed access
	 */
	काष्ठा cvmx_booपंचांगem_named_block_desc booपंचांगem_named_block_desc;

	/** Address of consoles descriptor */
	u64 console_desc_addr;

	/** Number of consoles available. 0 means they are inaccessible */
	u32 num_consoles;

	/* Console caches */
	काष्ठा octeon_console console[MAX_OCTEON_MAPS];

	/* Console named block info */
	काष्ठा अणु
		u64 dram_region_base;
		पूर्णांक bar1_index;
	पूर्ण console_nb_info;

	/* Coprocessor घड़ी rate. */
	u64 coproc_घड़ी_rate;

	/** The core application is running in this mode. See liquidio_common.h
	 * क्रम values.
	 */
	u32 app_mode;

	काष्ठा oct_fw_info fw_info;

	/** The name given to this device. */
	अक्षर device_name[32];

	/** Application Context */
	व्योम *app_ctx;

	काष्ठा cavium_wq dma_comp_wq;

	/** Lock क्रम dma response list */
	spinlock_t cmd_resp_wqlock;
	u32 cmd_resp_state;

	काष्ठा cavium_wq check_db_wq[MAX_POSSIBLE_OCTEON_INSTR_QUEUES];

	काष्ठा cavium_wk nic_poll_work;

	काष्ठा cavium_wk console_poll_work[MAX_OCTEON_MAPS];

	व्योम *priv;

	पूर्णांक num_msix_irqs;

	व्योम *msix_entries;

	/* when requesting IRQs, the names are stored here */
	व्योम *irq_name_storage;

	काष्ठा octeon_sriov_info sriov_info;

	काष्ठा octeon_pf_vf_hs_word pfvf_hsword;

	पूर्णांक msix_on;

	/** Mail Box details of each octeon queue. */
	काष्ठा octeon_mbox  *mbox[MAX_POSSIBLE_VFS];

	/** IOq inक्रमmation of it's corresponding MSI-X पूर्णांकerrupt. */
	काष्ठा octeon_ioq_vector    *ioq_vector;

	पूर्णांक rx_छोड़ो;
	पूर्णांक tx_छोड़ो;

	काष्ठा oct_link_stats link_stats; /*stastics from firmware*/

	/* निजी flags to control driver-specअगरic features through ethtool */
	u32 priv_flags;

	व्योम *watchकरोg_task;

	u32 rx_coalesce_usecs;
	u32 rx_max_coalesced_frames;
	u32 tx_max_coalesced_frames;

	bool cores_crashed;

	काष्ठा अणु
		पूर्णांक bus;
		पूर्णांक dev;
		पूर्णांक func;
	पूर्ण loc;

	atomic_t *adapter_refcount; /* reference count of adapter */

	atomic_t *adapter_fw_state; /* per-adapter, lio_fw_state */

	bool ptp_enable;

	काष्ठा lio_vf_rep_list vf_rep_list;
	काष्ठा devlink *devlink;
	क्रमागत devlink_eचयन_mode eचयन_mode;

	/* क्रम 25G NIC speed change */
	u8  speed_boot;
	u8  speed_setting;
	u8  no_speed_setting;

	u32    vख_स्थितिs_poll;
#घोषणा LIO_VFSTATS_POLL 10
पूर्ण;

#घोषणा  OCT_DRV_ONLINE 1
#घोषणा  OCT_DRV_OFFLINE 2
#घोषणा  OCTEON_CN6XXX(oct)	(अणु					\
				 typeof(oct) _oct = (oct);		\
				 ((_oct->chip_id == OCTEON_CN66XX) ||	\
				  (_oct->chip_id == OCTEON_CN68XX));	पूर्ण)
#घोषणा  OCTEON_CN23XX_PF(oct)        ((oct)->chip_id == OCTEON_CN23XX_PF_VID)
#घोषणा  OCTEON_CN23XX_VF(oct)        ((oct)->chip_id == OCTEON_CN23XX_VF_VID)
#घोषणा CHIP_CONF(oct, TYPE)             \
	(((काष्ठा octeon_ ## TYPE  *)((oct)->chip))->conf)

#घोषणा MAX_IO_PENDING_PKT_COUNT 100

/*------------------ Function Prototypes ----------------------*/

/** Initialize device list memory */
व्योम octeon_init_device_list(पूर्णांक conf_type);

/** Free memory क्रम Input and Output queue काष्ठाures क्रम a octeon device */
व्योम octeon_मुक्त_device_mem(काष्ठा octeon_device *oct);

/* Look up a मुक्त entry in the octeon_device table and allocate resources
 * क्रम the octeon_device काष्ठाure क्रम an octeon device. Called at init
 * समय.
 */
काष्ठा octeon_device *octeon_allocate_device(u32 pci_id,
					     u32 priv_size);

/** Register a device's bus location at initialization समय.
 *  @param octeon_dev - poपूर्णांकer to the octeon device काष्ठाure.
 *  @param bus        - PCIe bus #
 *  @param dev        - PCIe device #
 *  @param func       - PCIe function #
 *  @param is_pf      - TRUE क्रम PF, FALSE क्रम VF
 *  @वापस reference count of device's adapter
 */
पूर्णांक octeon_रेजिस्टर_device(काष्ठा octeon_device *oct,
			   पूर्णांक bus, पूर्णांक dev, पूर्णांक func, पूर्णांक is_pf);

/** Deरेजिस्टर a device at de-initialization समय.
 *  @param octeon_dev - poपूर्णांकer to the octeon device काष्ठाure.
 *  @वापस reference count of device's adapter
 */
पूर्णांक octeon_deरेजिस्टर_device(काष्ठा octeon_device *oct);

/**  Initialize the driver's dispatch list which is a mix of a hash table
 *  and a linked list. This is करोne at driver load समय.
 *  @param octeon_dev - poपूर्णांकer to the octeon device काष्ठाure.
 *  @वापस 0 on success, अन्यथा -ve error value
 */
पूर्णांक octeon_init_dispatch_list(काष्ठा octeon_device *octeon_dev);

/**  Delete the driver's dispatch list and all रेजिस्टरed entries.
 * This is करोne at driver unload समय.
 *  @param octeon_dev - poपूर्णांकer to the octeon device काष्ठाure.
 */
व्योम octeon_delete_dispatch_list(काष्ठा octeon_device *octeon_dev);

/** Initialize the core device fields with the info वापसed by the FW.
 * @param recv_info - Receive info काष्ठाure
 * @param buf       - Receive buffer
 */
पूर्णांक octeon_core_drv_init(काष्ठा octeon_recv_info *recv_info, व्योम *buf);

/** Gets the dispatch function रेजिस्टरed to receive packets with a
 *  given opcode/subcode.
 *  @param  octeon_dev  - the octeon device poपूर्णांकer.
 *  @param  opcode      - the opcode क्रम which the dispatch function
 *                        is to checked.
 *  @param  subcode     - the subcode क्रम which the dispatch function
 *                        is to checked.
 *
 *  @वापस Success: octeon_dispatch_fn_t (dispatch function poपूर्णांकer)
 *  @वापस Failure: शून्य
 *
 *  Looks up the dispatch list to get the dispatch function क्रम a
 *  given opcode.
 */
octeon_dispatch_fn_t
octeon_get_dispatch(काष्ठा octeon_device *octeon_dev, u16 opcode,
		    u16 subcode);

/** Get the octeon device poपूर्णांकer.
 *  @param octeon_id  - The id क्रम which the octeon device poपूर्णांकer is required.
 *  @वापस Success: Octeon device poपूर्णांकer.
 *  @वापस Failure: शून्य.
 */
काष्ठा octeon_device *lio_get_device(u32 octeon_id);

/** Get the octeon id asचिन्हित to the octeon device passed as argument.
 *  This function is exported to other modules.
 *  @param dev - octeon device poपूर्णांकer passed as a व्योम *.
 *  @वापस octeon device id
 */
पूर्णांक lio_get_device_id(व्योम *dev);

/** Read winकरोwed रेजिस्टर.
 *  @param  oct   -  poपूर्णांकer to the Octeon device.
 *  @param  addr  -  Address of the रेजिस्टर to पढ़ो.
 *
 *  This routine is called to पढ़ो from the indirectly accessed
 *  Octeon रेजिस्टरs that are visible through a PCI BAR0 mapped winकरोw
 *  रेजिस्टर.
 *  @वापस  - 64 bit value पढ़ो from the रेजिस्टर.
 */

u64 lio_pci_पढ़ोq(काष्ठा octeon_device *oct, u64 addr);

/** Write winकरोwed रेजिस्टर.
 *  @param  oct  -  poपूर्णांकer to the Octeon device.
 *  @param  val  -  Value to ग_लिखो
 *  @param  addr -  Address of the रेजिस्टर to ग_लिखो
 *
 *  This routine is called to ग_लिखो to the indirectly accessed
 *  Octeon रेजिस्टरs that are visible through a PCI BAR0 mapped winकरोw
 *  रेजिस्टर.
 *  @वापस   Nothing.
 */
व्योम lio_pci_ग_लिखोq(काष्ठा octeon_device *oct, u64 val, u64 addr);

/* Routines क्रम पढ़ोing and writing CSRs */
#घोषणा   octeon_ग_लिखो_csr(oct_dev, reg_off, value) \
		ग_लिखोl(value, (oct_dev)->mmio[0].hw_addr + (reg_off))

#घोषणा   octeon_ग_लिखो_csr64(oct_dev, reg_off, val64) \
		ग_लिखोq(val64, (oct_dev)->mmio[0].hw_addr + (reg_off))

#घोषणा   octeon_पढ़ो_csr(oct_dev, reg_off)         \
		पढ़ोl((oct_dev)->mmio[0].hw_addr + (reg_off))

#घोषणा   octeon_पढ़ो_csr64(oct_dev, reg_off)         \
		पढ़ोq((oct_dev)->mmio[0].hw_addr + (reg_off))

/**
 * Checks अगर memory access is okay
 *
 * @param oct which octeon to send to
 * @वापस Zero on success, negative on failure.
 */
पूर्णांक octeon_mem_access_ok(काष्ठा octeon_device *oct);

/**
 * Waits क्रम DDR initialization.
 *
 * @param oct which octeon to send to
 * @param समयout_in_ms poपूर्णांकer to how दीर्घ to रुको until DDR is initialized
 * in ms.
 *                      If contents are 0, it रुकोs until contents are non-zero
 *                      beक्रमe starting to check.
 * @वापस Zero on success, negative on failure.
 */
पूर्णांक octeon_रुको_क्रम_ddr_init(काष्ठा octeon_device *oct,
			     u32 *समयout_in_ms);

/**
 * Wait क्रम u-boot to boot and be रुकोing क्रम a command.
 *
 * @param रुको_समय_hundredths
 *               Maximum समय to रुको
 *
 * @वापस Zero on success, negative on failure.
 */
पूर्णांक octeon_रुको_क्रम_bootloader(काष्ठा octeon_device *oct,
			       u32 रुको_समय_hundredths);

/**
 * Initialize console access
 *
 * @param oct which octeon initialize
 * @वापस Zero on success, negative on failure.
 */
पूर्णांक octeon_init_consoles(काष्ठा octeon_device *oct);

/**
 * Adds access to a console to the device.
 *
 * @param oct:          which octeon to add to
 * @param console_num:  which console
 * @param dbg_enb:      ptr to debug enablement string, one of:
 *                    * शून्य क्रम no debug output (i.e. disabled)
 *                    * empty string enables debug output (via शेष method)
 *                    * specअगरic string to enable debug console output
 *
 * @वापस Zero on success, negative on failure.
 */
पूर्णांक octeon_add_console(काष्ठा octeon_device *oct, u32 console_num,
		       अक्षर *dbg_enb);

/** ग_लिखो or पढ़ो from a console */
पूर्णांक octeon_console_ग_लिखो(काष्ठा octeon_device *oct, u32 console_num,
			 अक्षर *buffer, u32 ग_लिखो_request_size, u32 flags);
पूर्णांक octeon_console_ग_लिखो_avail(काष्ठा octeon_device *oct, u32 console_num);

पूर्णांक octeon_console_पढ़ो_avail(काष्ठा octeon_device *oct, u32 console_num);

/** Removes all attached consoles. */
व्योम octeon_हटाओ_consoles(काष्ठा octeon_device *oct);

/**
 * Send a string to u-boot on console 0 as a command.
 *
 * @param oct which octeon to send to
 * @param cmd_str String to send
 * @param रुको_hundredths Time to रुको क्रम u-boot to accept the command.
 *
 * @वापस Zero on success, negative on failure.
 */
पूर्णांक octeon_console_send_cmd(काष्ठा octeon_device *oct, अक्षर *cmd_str,
			    u32 रुको_hundredths);

/** Parses, validates, and करोwnloads firmware, then boots associated cores.
 *  @param oct which octeon to करोwnload firmware to
 *  @param data  - The complete firmware file image
 *  @param size  - The size of the data
 *
 *  @वापस 0 अगर success.
 *         -EINVAL अगर file is incompatible or badly क्रमmatted.
 *         -ENODEV अगर no handler was found क्रम the application type or an
 *         invalid octeon id was passed.
 */
पूर्णांक octeon_करोwnload_firmware(काष्ठा octeon_device *oct, स्थिर u8 *data,
			     माप_प्रकार size);

अक्षर *lio_get_state_string(atomic_t *state_ptr);

/** Sets up inकाष्ठाion queues क्रम the device
 *  @param oct which octeon to setup
 *
 *  @वापस 0 अगर success. 1 अगर fails
 */
पूर्णांक octeon_setup_instr_queues(काष्ठा octeon_device *oct);

/** Sets up output queues क्रम the device
 *  @param oct which octeon to setup
 *
 *  @वापस 0 अगर success. 1 अगर fails
 */
पूर्णांक octeon_setup_output_queues(काष्ठा octeon_device *oct);

पूर्णांक octeon_get_tx_qsize(काष्ठा octeon_device *oct, u32 q_no);

पूर्णांक octeon_get_rx_qsize(काष्ठा octeon_device *oct, u32 q_no);

/** Turns off the input and output queues क्रम the device
 *  @param oct which octeon to disable
 */
पूर्णांक octeon_set_io_queues_off(काष्ठा octeon_device *oct);

/** Turns on or off the given output queue क्रम the device
 *  @param oct which octeon to change
 *  @param q_no which queue
 *  @param enable 1 to enable, 0 to disable
 */
व्योम octeon_set_droq_pkt_op(काष्ठा octeon_device *oct, u32 q_no, u32 enable);

/** Retrieve the config क्रम the device
 *  @param oct which octeon
 *  @param card_type type of card
 *
 *  @वापसs poपूर्णांकer to configuration
 */
व्योम *oct_get_config_info(काष्ठा octeon_device *oct, u16 card_type);

/** Gets the octeon device configuration
 *  @वापस - poपूर्णांकer to the octeon configuration struture
 */
काष्ठा octeon_config *octeon_get_conf(काष्ठा octeon_device *oct);

व्योम octeon_मुक्त_ioq_vector(काष्ठा octeon_device *oct);
पूर्णांक octeon_allocate_ioq_vector(काष्ठा octeon_device  *oct, u32 num_ioqs);
व्योम lio_enable_irq(काष्ठा octeon_droq *droq, काष्ठा octeon_instr_queue *iq);

/* LiquidIO driver pivate flags */
क्रमागत अणु
	OCT_PRIV_FLAG_TX_BYTES = 0, /* Tx पूर्णांकerrupts by pending byte count */
पूर्ण;

#घोषणा OCT_PRIV_FLAG_DEFAULT 0x0

अटल अंतरभूत u32 lio_get_priv_flag(काष्ठा octeon_device *octdev, u32 flag)
अणु
	वापस !!(octdev->priv_flags & (0x1 << flag));
पूर्ण

अटल अंतरभूत व्योम lio_set_priv_flag(काष्ठा octeon_device *octdev,
				     u32 flag, u32 val)
अणु
	अगर (val)
		octdev->priv_flags |= (0x1 << flag);
	अन्यथा
		octdev->priv_flags &= ~(0x1 << flag);
पूर्ण
#पूर्ण_अगर
