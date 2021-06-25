<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * mtip32xx.h - Header file क्रम the P320 SSD Block Driver
 *   Copyright (C) 2011 Micron Technology, Inc.
 *
 * Portions of this code were derived from works subjected to the
 * following copyright:
 *    Copyright (C) 2009 Integrated Device Technology, Inc.
 */

#अगर_अघोषित __MTIP32XX_H__
#घोषणा __MTIP32XX_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/ata.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/genhd.h>

/* Offset of Subप्रणाली Device ID in pci confoguration space */
#घोषणा PCI_SUBSYSTEM_DEVICEID	0x2E

/* offset of Device Control रेजिस्टर in PCIe extended capabilites space */
#घोषणा PCIE_CONFIG_EXT_DEVICE_CONTROL_OFFSET	0x48

/* check क्रम erase mode support during secure erase */
#घोषणा MTIP_SEC_ERASE_MODE     0x2

/* # of बार to retry समयd out/failed IOs */
#घोषणा MTIP_MAX_RETRIES	2

/* Various समयout values in ms */
#घोषणा MTIP_NCQ_CMD_TIMEOUT_MS      15000
#घोषणा MTIP_IOCTL_CMD_TIMEOUT_MS    5000
#घोषणा MTIP_INT_CMD_TIMEOUT_MS      5000
#घोषणा MTIP_QUIESCE_IO_TIMEOUT_MS   (MTIP_NCQ_CMD_TIMEOUT_MS * \
				     (MTIP_MAX_RETRIES + 1))

/* check क्रम समयouts every 500ms */
#घोषणा MTIP_TIMEOUT_CHECK_PERIOD	500

/* ftl rebuild */
#घोषणा MTIP_FTL_REBUILD_OFFSET		142
#घोषणा MTIP_FTL_REBUILD_MAGIC		0xED51
#घोषणा MTIP_FTL_REBUILD_TIMEOUT_MS	2400000

/* unaligned IO handling */
#घोषणा MTIP_MAX_UNALIGNED_SLOTS	2

/* Macro to extract the tag bit number from a tag value. */
#घोषणा MTIP_TAG_BIT(tag)	(tag & 0x1F)

/*
 * Macro to extract the tag index from a tag value. The index
 * is used to access the correct s_active/Command Issue रेजिस्टर based
 * on the tag value.
 */
#घोषणा MTIP_TAG_INDEX(tag)	(tag >> 5)

/*
 * Maximum number of scatter gather entries
 * a single command may have.
 */
#घोषणा MTIP_MAX_SG		504

/*
 * Maximum number of slot groups (Command Issue & s_active रेजिस्टरs)
 * NOTE: This is the driver maximum; check dd->slot_groups क्रम actual value.
 */
#घोषणा MTIP_MAX_SLOT_GROUPS	8

/* Internal command tag. */
#घोषणा MTIP_TAG_INTERNAL	0

/* Micron Venकरोr ID & P320x SSD Device ID */
#घोषणा PCI_VENDOR_ID_MICRON    0x1344
#घोषणा P320H_DEVICE_ID		0x5150
#घोषणा P320M_DEVICE_ID		0x5151
#घोषणा P320S_DEVICE_ID		0x5152
#घोषणा P325M_DEVICE_ID		0x5153
#घोषणा P420H_DEVICE_ID		0x5160
#घोषणा P420M_DEVICE_ID		0x5161
#घोषणा P425M_DEVICE_ID		0x5163

/* Driver name and version strings */
#घोषणा MTIP_DRV_NAME		"mtip32xx"
#घोषणा MTIP_DRV_VERSION	"1.3.1"

/* Maximum number of minor device numbers per device. */
#घोषणा MTIP_MAX_MINORS		16

/* Maximum number of supported command slots. */
#घोषणा MTIP_MAX_COMMAND_SLOTS	(MTIP_MAX_SLOT_GROUPS * 32)

/*
 * Per-tag bitfield size in दीर्घs.
 * Linux bit manipulation functions
 * (i.e. test_and_set_bit, find_next_zero_bit)
 * manipulate memory in दीर्घs, so we try to make the math work.
 * take the slot groups and find the number of दीर्घs, rounding up.
 * Careful! i386 and x86_64 use dअगरferent size दीर्घs!
 */
#घोषणा U32_PER_LONG	(माप(दीर्घ) / माप(u32))
#घोषणा SLOTBITS_IN_LONGS ((MTIP_MAX_SLOT_GROUPS + \
					(U32_PER_LONG-1))/U32_PER_LONG)

/* BAR number used to access the HBA रेजिस्टरs. */
#घोषणा MTIP_ABAR		5

#अगर_घोषित DEBUG
 #घोषणा dbg_prपूर्णांकk(क्रमmat, arg...)	\
	prपूर्णांकk(pr_fmt(क्रमmat), ##arg);
#अन्यथा
 #घोषणा dbg_prपूर्णांकk(क्रमmat, arg...)
#पूर्ण_अगर

#घोषणा MTIP_DFS_MAX_BUF_SIZE 1024

क्रमागत अणु
	/* below are bit numbers in 'flags' defined in mtip_port */
	MTIP_PF_IC_ACTIVE_BIT       = 0, /* pio/ioctl */
	MTIP_PF_EH_ACTIVE_BIT       = 1, /* error handling */
	MTIP_PF_SE_ACTIVE_BIT       = 2, /* secure erase */
	MTIP_PF_DM_ACTIVE_BIT       = 3, /* करोwnload microcde */
	MTIP_PF_TO_ACTIVE_BIT       = 9, /* समयout handling */
	MTIP_PF_PAUSE_IO      =	((1 << MTIP_PF_IC_ACTIVE_BIT) |
				(1 << MTIP_PF_EH_ACTIVE_BIT) |
				(1 << MTIP_PF_SE_ACTIVE_BIT) |
				(1 << MTIP_PF_DM_ACTIVE_BIT) |
				(1 << MTIP_PF_TO_ACTIVE_BIT)),
	MTIP_PF_HOST_CAP_64         = 10, /* cache HOST_CAP_64 */

	MTIP_PF_SVC_THD_ACTIVE_BIT  = 4,
	MTIP_PF_ISSUE_CMDS_BIT      = 5,
	MTIP_PF_REBUILD_BIT         = 6,
	MTIP_PF_SVC_THD_STOP_BIT    = 8,

	MTIP_PF_SVC_THD_WORK	= ((1 << MTIP_PF_EH_ACTIVE_BIT) |
				  (1 << MTIP_PF_ISSUE_CMDS_BIT) |
				  (1 << MTIP_PF_REBUILD_BIT) |
				  (1 << MTIP_PF_SVC_THD_STOP_BIT) |
				  (1 << MTIP_PF_TO_ACTIVE_BIT)),

	/* below are bit numbers in 'dd_flag' defined in driver_data */
	MTIP_DDF_SEC_LOCK_BIT	    = 0,
	MTIP_DDF_REMOVE_PENDING_BIT = 1,
	MTIP_DDF_OVER_TEMP_BIT      = 2,
	MTIP_DDF_WRITE_PROTECT_BIT  = 3,
	MTIP_DDF_CLEANUP_BIT        = 5,
	MTIP_DDF_RESUME_BIT         = 6,
	MTIP_DDF_INIT_DONE_BIT      = 7,
	MTIP_DDF_REBUILD_FAILED_BIT = 8,
	MTIP_DDF_REMOVAL_BIT	    = 9,

	MTIP_DDF_STOP_IO      = ((1 << MTIP_DDF_REMOVE_PENDING_BIT) |
				(1 << MTIP_DDF_SEC_LOCK_BIT) |
				(1 << MTIP_DDF_OVER_TEMP_BIT) |
				(1 << MTIP_DDF_WRITE_PROTECT_BIT) |
				(1 << MTIP_DDF_REBUILD_FAILED_BIT)),

पूर्ण;

काष्ठा smart_attr अणु
	u8 attr_id;
	__le16 flags;
	u8 cur;
	u8 worst;
	__le32 data;
	u8 res[3];
पूर्ण __packed;

काष्ठा mtip_work अणु
	काष्ठा work_काष्ठा work;
	व्योम *port;
	पूर्णांक cpu_binding;
	u32 completed;
पूर्ण ____cacheline_aligned_in_smp;

#घोषणा DEFINE_HANDLER(group)                                  \
	व्योम mtip_workq_sdbf##group(काष्ठा work_काष्ठा *work)       \
	अणु                                                      \
		काष्ठा mtip_work *w = (काष्ठा mtip_work *) work;         \
		mtip_workq_sdbfx(w->port, group, w->completed);     \
	पूर्ण

/* Register Frame Inक्रमmation Structure (FIS), host to device. */
काष्ठा host_to_dev_fis अणु
	/*
	 * FIS type.
	 * - 27h Register FIS, host to device.
	 * - 34h Register FIS, device to host.
	 * - 39h DMA Activate FIS, device to host.
	 * - 41h DMA Setup FIS, bi-directional.
	 * - 46h Data FIS, bi-directional.
	 * - 58h BIST Activate FIS, bi-directional.
	 * - 5Fh PIO Setup FIS, device to host.
	 * - A1h Set Device Bits FIS, device to host.
	 */
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर opts;
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर features;

	जोड़ अणु
		अचिन्हित अक्षर lba_low;
		अचिन्हित अक्षर sector;
	पूर्ण;
	जोड़ अणु
		अचिन्हित अक्षर lba_mid;
		अचिन्हित अक्षर cyl_low;
	पूर्ण;
	जोड़ अणु
		अचिन्हित अक्षर lba_hi;
		अचिन्हित अक्षर cyl_hi;
	पूर्ण;
	जोड़ अणु
		अचिन्हित अक्षर device;
		अचिन्हित अक्षर head;
	पूर्ण;

	जोड़ अणु
		अचिन्हित अक्षर lba_low_ex;
		अचिन्हित अक्षर sector_ex;
	पूर्ण;
	जोड़ अणु
		अचिन्हित अक्षर lba_mid_ex;
		अचिन्हित अक्षर cyl_low_ex;
	पूर्ण;
	जोड़ अणु
		अचिन्हित अक्षर lba_hi_ex;
		अचिन्हित अक्षर cyl_hi_ex;
	पूर्ण;
	अचिन्हित अक्षर features_ex;

	अचिन्हित अक्षर sect_count;
	अचिन्हित अक्षर sect_cnt_ex;
	अचिन्हित अक्षर res2;
	अचिन्हित अक्षर control;

	अचिन्हित पूर्णांक res3;
पूर्ण;

/* Command header काष्ठाure. */
काष्ठा mtip_cmd_hdr अणु
	/*
	 * Command options.
	 * - Bits 31:16 Number of PRD entries.
	 * - Bits 15:8 Unused in this implementation.
	 * - Bit 7 Prefetch bit, inक्रमms the drive to prefetch PRD entries.
	 * - Bit 6 Write bit, should be set when writing data to the device.
	 * - Bit 5 Unused in this implementation.
	 * - Bits 4:0 Length of the command FIS in DWords (DWord = 4 bytes).
	 */
	__le32 opts;
	/* This field is unsed when using NCQ. */
	जोड़ अणु
		__le32 byte_count;
		__le32 status;
	पूर्ण;
	/*
	 * Lower 32 bits of the command table address associated with this
	 * header. The command table addresses must be 128 byte aligned.
	 */
	__le32 ctba;
	/*
	 * If 64 bit addressing is used this field is the upper 32 bits
	 * of the command table address associated with this command.
	 */
	__le32 ctbau;
	/* Reserved and unused. */
	u32 res[4];
पूर्ण;

/* Command scatter gather काष्ठाure (PRD). */
काष्ठा mtip_cmd_sg अणु
	/*
	 * Low 32 bits of the data buffer address. For P320 this
	 * address must be 8 byte aligned signअगरied by bits 2:0 being
	 * set to 0.
	 */
	__le32 dba;
	/*
	 * When 64 bit addressing is used this field is the upper
	 * 32 bits of the data buffer address.
	 */
	__le32 dba_upper;
	/* Unused. */
	__le32 reserved;
	/*
	 * Bit 31: पूर्णांकerrupt when this data block has been transferred.
	 * Bits 30..22: reserved
	 * Bits 21..0: byte count (minus 1).  For P320 the byte count must be
	 * 8 byte aligned signअगरied by bits 2:0 being set to 1.
	 */
	__le32 info;
पूर्ण;
काष्ठा mtip_port;

काष्ठा mtip_पूर्णांक_cmd;

/* Structure used to describe a command. */
काष्ठा mtip_cmd अणु
	व्योम *command; /* ptr to command table entry */

	dma_addr_t command_dma; /* corresponding physical address */

	पूर्णांक scatter_ents; /* Number of scatter list entries used */

	पूर्णांक unaligned; /* command is unaligned on 4k boundary */

	जोड़ अणु
		काष्ठा scatterlist sg[MTIP_MAX_SG]; /* Scatter list entries */
		काष्ठा mtip_पूर्णांक_cmd *icmd;
	पूर्ण;

	पूर्णांक retries; /* The number of retries left क्रम this command. */

	पूर्णांक direction; /* Data transfer direction */
	blk_status_t status;
पूर्ण;

/* Structure used to describe a port. */
काष्ठा mtip_port अणु
	/* Poपूर्णांकer back to the driver data क्रम this port. */
	काष्ठा driver_data *dd;
	/*
	 * Used to determine अगर the data poपूर्णांकed to by the
	 * identअगरy field is valid.
	 */
	अचिन्हित दीर्घ identअगरy_valid;
	/* Base address of the memory mapped IO क्रम the port. */
	व्योम __iomem *mmio;
	/* Array of poपूर्णांकers to the memory mapped s_active रेजिस्टरs. */
	व्योम __iomem *s_active[MTIP_MAX_SLOT_GROUPS];
	/* Array of poपूर्णांकers to the memory mapped completed रेजिस्टरs. */
	व्योम __iomem *completed[MTIP_MAX_SLOT_GROUPS];
	/* Array of poपूर्णांकers to the memory mapped Command Issue रेजिस्टरs. */
	व्योम __iomem *cmd_issue[MTIP_MAX_SLOT_GROUPS];
	/*
	 * Poपूर्णांकer to the beginning of the command header memory as used
	 * by the driver.
	 */
	व्योम *command_list;
	/*
	 * Poपूर्णांकer to the beginning of the command header memory as used
	 * by the DMA.
	 */
	dma_addr_t command_list_dma;
	/*
	 * Poपूर्णांकer to the beginning of the RX FIS memory as used
	 * by the driver.
	 */
	व्योम *rxfis;
	/*
	 * Poपूर्णांकer to the beginning of the RX FIS memory as used
	 * by the DMA.
	 */
	dma_addr_t rxfis_dma;
	/*
	 * Poपूर्णांकer to the DMA region क्रम RX Fis, Identअगरy, RLE10, and SMART
	 */
	व्योम *block1;
	/*
	 * DMA address of region क्रम RX Fis, Identअगरy, RLE10, and SMART
	 */
	dma_addr_t block1_dma;
	/*
	 * Poपूर्णांकer to the beginning of the identअगरy data memory as used
	 * by the driver.
	 */
	u16 *identअगरy;
	/*
	 * Poपूर्णांकer to the beginning of the identअगरy data memory as used
	 * by the DMA.
	 */
	dma_addr_t identअगरy_dma;
	/*
	 * Poपूर्णांकer to the beginning of a sector buffer that is used
	 * by the driver when issuing पूर्णांकernal commands.
	 */
	u16 *sector_buffer;
	/*
	 * Poपूर्णांकer to the beginning of a sector buffer that is used
	 * by the DMA when the driver issues पूर्णांकernal commands.
	 */
	dma_addr_t sector_buffer_dma;

	u16 *log_buf;
	dma_addr_t log_buf_dma;

	u8 *smart_buf;
	dma_addr_t smart_buf_dma;

	/*
	 * used to queue commands when an पूर्णांकernal command is in progress
	 * or error handling is active
	 */
	अचिन्हित दीर्घ cmds_to_issue[SLOTBITS_IN_LONGS];
	/* Used by mtip_service_thपढ़ो to रुको क्रम an event */
	रुको_queue_head_t svc_रुको;
	/*
	 * indicates the state of the port. Also, helps the service thपढ़ो
	 * to determine its action on wake up.
	 */
	अचिन्हित दीर्घ flags;
	/*
	 * Timer used to complete commands that have been active क्रम too दीर्घ.
	 */
	अचिन्हित दीर्घ ic_छोड़ो_समयr;

	/* Counter to control queue depth of unaligned IOs */
	atomic_t cmd_slot_unal;

	/* Spinlock क्रम working around command-issue bug. */
	spinlock_t cmd_issue_lock[MTIP_MAX_SLOT_GROUPS];
पूर्ण;

/*
 * Driver निजी data काष्ठाure.
 *
 * One काष्ठाure is allocated per probed device.
 */
काष्ठा driver_data अणु
	व्योम __iomem *mmio; /* Base address of the HBA रेजिस्टरs. */

	पूर्णांक major; /* Major device number. */

	पूर्णांक instance; /* Instance number. First device probed is 0, ... */

	काष्ठा gendisk *disk; /* Poपूर्णांकer to our gendisk काष्ठाure. */

	काष्ठा pci_dev *pdev; /* Poपूर्णांकer to the PCI device काष्ठाure. */

	काष्ठा request_queue *queue; /* Our request queue. */

	काष्ठा blk_mq_tag_set tags; /* blk_mq tags */

	काष्ठा mtip_port *port; /* Poपूर्णांकer to the port data काष्ठाure. */

	अचिन्हित product_type; /* magic value declaring the product type */

	अचिन्हित slot_groups; /* number of slot groups the product supports */

	अचिन्हित दीर्घ index; /* Index to determine the disk name */

	अचिन्हित दीर्घ dd_flag; /* NOTE: use atomic bit operations on this */

	काष्ठा task_काष्ठा *mtip_svc_handler; /* task_काष्ठा of svc thd */

	काष्ठा dentry *dfs_node;

	bool sr;

	पूर्णांक numa_node; /* NUMA support */

	अक्षर workq_name[32];

	काष्ठा workqueue_काष्ठा *isr_workq;

	atomic_t irq_workers_active;

	काष्ठा mtip_work work[MTIP_MAX_SLOT_GROUPS];

	पूर्णांक isr_binding;

	काष्ठा list_head online_list; /* linkage क्रम online list */

	काष्ठा list_head हटाओ_list; /* linkage क्रम removing list */

	पूर्णांक unal_qdepth; /* qdepth of unaligned IO queue */
पूर्ण;

#पूर्ण_अगर
