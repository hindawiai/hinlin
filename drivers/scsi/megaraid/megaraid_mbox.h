<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: megaraid_mbox.h
 */

#अगर_अघोषित _MEGARAID_H_
#घोषणा _MEGARAID_H_


#समावेश "mega_common.h"
#समावेश "mbox_defs.h"
#समावेश "megaraid_ioctl.h"


#घोषणा MEGARAID_VERSION	"2.20.5.1"
#घोषणा MEGARAID_EXT_VERSION	"(Release Date: Thu Nov 16 15:32:35 EST 2006)"


/*
 * Define some PCI values here until they are put in the kernel
 */
#घोषणा PCI_DEVICE_ID_PERC4_DI_DISCOVERY		0x000E
#घोषणा PCI_SUBSYS_ID_PERC4_DI_DISCOVERY		0x0123

#घोषणा PCI_DEVICE_ID_PERC4_SC				0x1960
#घोषणा PCI_SUBSYS_ID_PERC4_SC				0x0520

#घोषणा PCI_DEVICE_ID_PERC4_DC				0x1960
#घोषणा PCI_SUBSYS_ID_PERC4_DC				0x0518

#घोषणा PCI_DEVICE_ID_VERDE				0x0407

#घोषणा PCI_DEVICE_ID_PERC4_DI_EVERGLADES		0x000F
#घोषणा PCI_SUBSYS_ID_PERC4_DI_EVERGLADES		0x014A

#घोषणा PCI_DEVICE_ID_PERC4E_SI_BIGBEND			0x0013
#घोषणा PCI_SUBSYS_ID_PERC4E_SI_BIGBEND			0x016c

#घोषणा PCI_DEVICE_ID_PERC4E_DI_KOBUK			0x0013
#घोषणा PCI_SUBSYS_ID_PERC4E_DI_KOBUK			0x016d

#घोषणा PCI_DEVICE_ID_PERC4E_DI_CORVETTE		0x0013
#घोषणा PCI_SUBSYS_ID_PERC4E_DI_CORVETTE		0x016e

#घोषणा PCI_DEVICE_ID_PERC4E_DI_EXPEDITION		0x0013
#घोषणा PCI_SUBSYS_ID_PERC4E_DI_EXPEDITION		0x016f

#घोषणा PCI_DEVICE_ID_PERC4E_DI_GUADALUPE		0x0013
#घोषणा PCI_SUBSYS_ID_PERC4E_DI_GUADALUPE		0x0170

#घोषणा PCI_DEVICE_ID_DOBSON				0x0408

#घोषणा PCI_DEVICE_ID_MEGARAID_SCSI_320_0		0x1960
#घोषणा PCI_SUBSYS_ID_MEGARAID_SCSI_320_0		0xA520

#घोषणा PCI_DEVICE_ID_MEGARAID_SCSI_320_1		0x1960
#घोषणा PCI_SUBSYS_ID_MEGARAID_SCSI_320_1		0x0520

#घोषणा PCI_DEVICE_ID_MEGARAID_SCSI_320_2		0x1960
#घोषणा PCI_SUBSYS_ID_MEGARAID_SCSI_320_2		0x0518

#घोषणा PCI_DEVICE_ID_MEGARAID_I4_133_RAID		0x1960
#घोषणा PCI_SUBSYS_ID_MEGARAID_I4_133_RAID		0x0522

#घोषणा PCI_DEVICE_ID_MEGARAID_SATA_150_4		0x1960
#घोषणा PCI_SUBSYS_ID_MEGARAID_SATA_150_4		0x4523

#घोषणा PCI_DEVICE_ID_MEGARAID_SATA_150_6		0x1960
#घोषणा PCI_SUBSYS_ID_MEGARAID_SATA_150_6		0x0523

#घोषणा PCI_DEVICE_ID_LINDSAY				0x0409

#घोषणा PCI_DEVICE_ID_INTEL_RAID_SRCS16			0x1960
#घोषणा PCI_SUBSYS_ID_INTEL_RAID_SRCS16			0x0523

#घोषणा PCI_DEVICE_ID_INTEL_RAID_SRCU41L_LAKE_SHETEK	0x1960
#घोषणा PCI_SUBSYS_ID_INTEL_RAID_SRCU41L_LAKE_SHETEK	0x0520

#घोषणा PCI_SUBSYS_ID_PERC3_QC				0x0471
#घोषणा PCI_SUBSYS_ID_PERC3_DC				0x0493
#घोषणा PCI_SUBSYS_ID_PERC3_SC				0x0475
#घोषणा PCI_SUBSYS_ID_CERC_ATA100_4CH			0x0511


#घोषणा MBOX_MAX_SCSI_CMDS	128	// number of cmds reserved क्रम kernel
#घोषणा MBOX_MAX_USER_CMDS	32	// number of cmds क्रम applications
#घोषणा MBOX_DEF_CMD_PER_LUN	64	// शेष commands per lun
#घोषणा MBOX_DEFAULT_SG_SIZE	26	// शेष sg size supported by all fw
#घोषणा MBOX_MAX_SG_SIZE	32	// maximum scatter-gather list size
#घोषणा MBOX_MAX_SECTORS	128	// maximum sectors per IO
#घोषणा MBOX_TIMEOUT		30	// समयout value क्रम पूर्णांकernal cmds
#घोषणा MBOX_BUSY_WAIT		10	// max usec to रुको क्रम busy mailbox
#घोषणा MBOX_RESET_WAIT		180	// रुको these many seconds in reset
#घोषणा MBOX_RESET_EXT_WAIT	120	// extended रुको reset
#घोषणा MBOX_SYNC_WAIT_CNT	0xFFFF	// रुको loop index क्रम synchronous mode

#घोषणा MBOX_SYNC_DELAY_200	200	// 200 micro-seconds

/*
 * maximum transfer that can happen through the firmware commands issued
 * पूर्णांकernnaly from the driver.
 */
#घोषणा MBOX_IBUF_SIZE		4096


/**
 * mbox_ccb_t - command control block specअगरic to mailbox based controllers
 * @raw_mbox		: raw mailbox poपूर्णांकer
 * @mbox		: mailbox
 * @mbox64		: extended mailbox
 * @mbox_dma_h		: mailbox dma address
 * @sgl64		: 64-bit scatter-gather list
 * @sgl32		: 32-bit scatter-gather list
 * @sgl_dma_h		: dma handle क्रम the scatter-gather list
 * @pthru		: passthru काष्ठाure
 * @pthru_dma_h		: dma handle क्रम the passthru काष्ठाure
 * @epthru		: extended passthru काष्ठाure
 * @epthru_dma_h	: dma handle क्रम extended passthru काष्ठाure
 * @buf_dma_h		: dma handle क्रम buffers w/o sg list
 *
 * command control block specअगरic to the mailbox based controllers
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t			*raw_mbox;
	mbox_t			*mbox;
	mbox64_t		*mbox64;
	dma_addr_t		mbox_dma_h;
	mbox_sgl64		*sgl64;
	mbox_sgl32		*sgl32;
	dma_addr_t		sgl_dma_h;
	mraid_passthru_t	*pthru;
	dma_addr_t		pthru_dma_h;
	mraid_epassthru_t	*epthru;
	dma_addr_t		epthru_dma_h;
	dma_addr_t		buf_dma_h;
पूर्ण mbox_ccb_t;


/**
 * mraid_device_t - adapter soft state काष्ठाure क्रम mailbox controllers
 * @una_mbox64			: 64-bit mbox - unaligned
 * @una_mbox64_dma		: mbox dma addr - unaligned
 * @mbox			: 32-bit mbox - aligned
 * @mbox64			: 64-bit mbox - aligned
 * @mbox_dma			: mbox dma addr - aligned
 * @mailbox_lock		: exclusion lock क्रम the mailbox
 * @baseport			: base port of hba memory
 * @baseaddr			: mapped addr of hba memory
 * @mbox_pool			: pool of mailboxes
 * @mbox_pool_handle		: handle क्रम the mailbox pool memory
 * @epthru_pool			: a pool क्रम extended passthru commands
 * @epthru_pool_handle		: handle to the pool above
 * @sg_pool			: pool of scatter-gather lists क्रम this driver
 * @sg_pool_handle		: handle to the pool above
 * @ccb_list			: list of our command control blocks
 * @uccb_list			: list of cmd control blocks क्रम mgmt module
 * @umbox64			: array of mailbox क्रम user commands (cmm)
 * @pdrv_state			: array क्रम state of each physical drive.
 * @last_disp			: flag used to show device scanning
 * @hw_error			: set अगर FW not responding
 * @fast_load			: If set, skip physical device scanning
 * @channel_class		: channel class, RAID or SCSI
 * @sysfs_mtx			: mutex to serialize access to sysfs res.
 * @sysfs_uioc			: management packet to issue FW calls from sysfs
 * @sysfs_mbox64		: mailbox packet to issue FW calls from sysfs
 * @sysfs_buffer		: data buffer क्रम FW commands issued from sysfs
 * @sysfs_buffer_dma		: DMA buffer क्रम FW commands issued from sysfs
 * @sysfs_रुको_q		: रुको queue क्रम sysfs operations
 * @अक्रमom_del_supported	: set अगर the अक्रमom deletion is supported
 * @curr_ldmap			: current LDID map
 *
 * Initialization काष्ठाure क्रम mailbox controllers: memory based and IO based
 * All the fields in this काष्ठाure are LLD specअगरic and may be discovered at
 * init() or start() समय.
 *
 * NOTE: The fields of this काष्ठाures are placed to minimize cache misses
 */
#घोषणा MAX_LD_EXTENDED64	64
प्रकार काष्ठा अणु
	mbox64_t			*una_mbox64;
	dma_addr_t			una_mbox64_dma;
	mbox_t				*mbox;
	mbox64_t			*mbox64;
	dma_addr_t			mbox_dma;
	spinlock_t			mailbox_lock;
	अचिन्हित दीर्घ			baseport;
	व्योम __iomem *			baseaddr;
	काष्ठा mraid_pci_blk		mbox_pool[MBOX_MAX_SCSI_CMDS];
	काष्ठा dma_pool			*mbox_pool_handle;
	काष्ठा mraid_pci_blk		epthru_pool[MBOX_MAX_SCSI_CMDS];
	काष्ठा dma_pool			*epthru_pool_handle;
	काष्ठा mraid_pci_blk		sg_pool[MBOX_MAX_SCSI_CMDS];
	काष्ठा dma_pool			*sg_pool_handle;
	mbox_ccb_t			ccb_list[MBOX_MAX_SCSI_CMDS];
	mbox_ccb_t			uccb_list[MBOX_MAX_USER_CMDS];
	mbox64_t			umbox64[MBOX_MAX_USER_CMDS];

	uपूर्णांक8_t				pdrv_state[MBOX_MAX_PHYSICAL_DRIVES];
	uपूर्णांक32_t			last_disp;
	पूर्णांक				hw_error;
	पूर्णांक				fast_load;
	uपूर्णांक8_t				channel_class;
	काष्ठा mutex			sysfs_mtx;
	uioc_t				*sysfs_uioc;
	mbox64_t			*sysfs_mbox64;
	caddr_t				sysfs_buffer;
	dma_addr_t			sysfs_buffer_dma;
	रुको_queue_head_t		sysfs_रुको_q;
	पूर्णांक				अक्रमom_del_supported;
	uपूर्णांक16_t			curr_ldmap[MAX_LD_EXTENDED64];
पूर्ण mraid_device_t;

// route to raid device from adapter
#घोषणा ADAP2RAIDDEV(adp)	((mraid_device_t *)((adp)->raid_device))

#घोषणा MAILBOX_LOCK(rdev)	(&(rdev)->mailbox_lock)

// Find out अगर this channel is a RAID or SCSI
#घोषणा IS_RAID_CH(rdev, ch)	(((rdev)->channel_class >> (ch)) & 0x01)


#घोषणा RDINDOOR(rdev)		पढ़ोl((rdev)->baseaddr + 0x20)
#घोषणा RDOUTDOOR(rdev)		पढ़ोl((rdev)->baseaddr + 0x2C)
#घोषणा WRINDOOR(rdev, value)	ग_लिखोl(value, (rdev)->baseaddr + 0x20)
#घोषणा WROUTDOOR(rdev, value)	ग_लिखोl(value, (rdev)->baseaddr + 0x2C)

#पूर्ण_अगर // _MEGARAID_H_
