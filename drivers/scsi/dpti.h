<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
                          dpti.h  -  description
                             -------------------
    begin                : Thu Sep 7 2000
    copyright            : (C) 2001 by Adaptec

    See Documentation/scsi/dpti.rst क्रम history, notes, license info
    and credits
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

#अगर_अघोषित _DPT_H
#घोषणा _DPT_H

#घोषणा MAX_TO_IOP_MESSAGES   (255)
#घोषणा MAX_FROM_IOP_MESSAGES (255)


/*
 * SCSI पूर्णांकerface function Prototypes
 */

अटल पूर्णांक adpt_detect(काष्ठा scsi_host_ढाँचा * sht);
अटल पूर्णांक adpt_queue(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd * cmd);
अटल पूर्णांक adpt_पात(काष्ठा scsi_cmnd * cmd);
अटल पूर्णांक adpt_reset(काष्ठा scsi_cmnd* cmd);
अटल पूर्णांक adpt_slave_configure(काष्ठा scsi_device *);

अटल स्थिर अक्षर *adpt_info(काष्ठा Scsi_Host *pSHost);
अटल पूर्णांक adpt_bios_param(काष्ठा scsi_device * sdev, काष्ठा block_device *dev,
		sector_t, पूर्णांक geom[]);

अटल पूर्णांक adpt_bus_reset(काष्ठा scsi_cmnd* cmd);
अटल पूर्णांक adpt_device_reset(काष्ठा scsi_cmnd* cmd);


/*
 * काष्ठा scsi_host_ढाँचा (see scsi/scsi_host.h)
 */

#घोषणा DPT_DRIVER_NAME	"Adaptec I2O RAID"

#अगर_अघोषित HOSTS_C

#समावेश "dpt/sys_info.h"
#समावेश <linux/रुको.h>
#समावेश "dpt/dpti_i2o.h"
#समावेश "dpt/dpti_ioctl.h"

#घोषणा DPT_I2O_VERSION "2.4 Build 5go"
#घोषणा DPT_VERSION     2
#घोषणा DPT_REVISION    '4'
#घोषणा DPT_SUBREVISION '5'
#घोषणा DPT_BETA	""
#घोषणा DPT_MONTH      8 
#घोषणा DPT_DAY        7
#घोषणा DPT_YEAR        (2001-1980)

#घोषणा DPT_DRIVER	"dpt_i2o"
#घोषणा DPTI_I2O_MAJOR	(151)
#घोषणा DPT_ORGANIZATION_ID (0x1B)        /* For Private Messages */
#घोषणा DPTI_MAX_HBA	(16)
#घोषणा MAX_CHANNEL     (5)	// Maximum Channel # Supported
#घोषणा MAX_ID        	(128)	// Maximum Target ID Supported

/* Sizes in 4 byte words */
#घोषणा REPLY_FRAME_SIZE  (17)
#घोषणा MAX_MESSAGE_SIZE  (128)
#घोषणा SG_LIST_ELEMENTS  (56)

#घोषणा EMPTY_QUEUE           0xffffffff
#घोषणा I2O_INTERRUPT_PENDING_B   (0x08)

#घोषणा PCI_DPT_VENDOR_ID         (0x1044)	// DPT PCI Venकरोr ID
#घोषणा PCI_DPT_DEVICE_ID         (0xA501)	// DPT PCI I2O Device ID
#घोषणा PCI_DPT_RAPTOR_DEVICE_ID  (0xA511)	

/* Debugging macro from Linux Device Drivers - Rubini */
#अघोषित PDEBUG
#अगर_घोषित DEBUG
//TODO add debug level चयन
#  define PDEBUG(fmt, args...)  prपूर्णांकk(KERN_DEBUG "dpti: " fmt, ##args)
#  define PDEBUGV(fmt, args...) prपूर्णांकk(KERN_DEBUG "dpti: " fmt, ##args)
#अन्यथा
# define PDEBUG(fmt, args...) /* not debugging: nothing */
# define PDEBUGV(fmt, args...) /* not debugging: nothing */
#पूर्ण_अगर

#घोषणा PERROR(fmt, args...) prपूर्णांकk(KERN_ERR fmt, ##args)
#घोषणा PWARN(fmt, args...) prपूर्णांकk(KERN_WARNING fmt, ##args)
#घोषणा PINFO(fmt, args...) prपूर्णांकk(KERN_INFO fmt, ##args)
#घोषणा PCRIT(fmt, args...) prपूर्णांकk(KERN_CRIT fmt, ##args)

#घोषणा SHUTDOWN_SIGS	(sigmask(SIGKILL)|sigmask(संक_विघ्न)|sigmask(संक_इति))

// Command समयouts
#घोषणा FOREVER			(0)
#घोषणा TMOUT_INQUIRY 		(20)
#घोषणा TMOUT_FLUSH		(360/45)
#घोषणा TMOUT_ABORT		(30)
#घोषणा TMOUT_SCSI		(300)
#घोषणा TMOUT_IOPRESET		(360)
#घोषणा TMOUT_GETSTATUS		(15)
#घोषणा TMOUT_INITOUTBOUND	(15)
#घोषणा TMOUT_LCT		(360)


#घोषणा I2O_SCSI_DEVICE_DSC_MASK                0x00FF

#घोषणा I2O_DETAIL_STATUS_UNSUPPORTED_FUNCTION  0x000A

#घोषणा I2O_SCSI_DSC_MASK                   0xFF00
#घोषणा I2O_SCSI_DSC_SUCCESS                0x0000
#घोषणा I2O_SCSI_DSC_REQUEST_ABORTED        0x0200
#घोषणा I2O_SCSI_DSC_UNABLE_TO_ABORT        0x0300
#घोषणा I2O_SCSI_DSC_COMPLETE_WITH_ERROR    0x0400
#घोषणा I2O_SCSI_DSC_ADAPTER_BUSY           0x0500
#घोषणा I2O_SCSI_DSC_REQUEST_INVALID        0x0600
#घोषणा I2O_SCSI_DSC_PATH_INVALID           0x0700
#घोषणा I2O_SCSI_DSC_DEVICE_NOT_PRESENT     0x0800
#घोषणा I2O_SCSI_DSC_UNABLE_TO_TERMINATE    0x0900
#घोषणा I2O_SCSI_DSC_SELECTION_TIMEOUT      0x0A00
#घोषणा I2O_SCSI_DSC_COMMAND_TIMEOUT        0x0B00
#घोषणा I2O_SCSI_DSC_MR_MESSAGE_RECEIVED    0x0D00
#घोषणा I2O_SCSI_DSC_SCSI_BUS_RESET         0x0E00
#घोषणा I2O_SCSI_DSC_PARITY_ERROR_FAILURE   0x0F00
#घोषणा I2O_SCSI_DSC_AUTOSENSE_FAILED       0x1000
#घोषणा I2O_SCSI_DSC_NO_ADAPTER             0x1100
#घोषणा I2O_SCSI_DSC_DATA_OVERRUN           0x1200
#घोषणा I2O_SCSI_DSC_UNEXPECTED_BUS_FREE    0x1300
#घोषणा I2O_SCSI_DSC_SEQUENCE_FAILURE       0x1400
#घोषणा I2O_SCSI_DSC_REQUEST_LENGTH_ERROR   0x1500
#घोषणा I2O_SCSI_DSC_PROVIDE_FAILURE        0x1600
#घोषणा I2O_SCSI_DSC_BDR_MESSAGE_SENT       0x1700
#घोषणा I2O_SCSI_DSC_REQUEST_TERMINATED     0x1800
#घोषणा I2O_SCSI_DSC_IDE_MESSAGE_SENT       0x3300
#घोषणा I2O_SCSI_DSC_RESOURCE_UNAVAILABLE   0x3400
#घोषणा I2O_SCSI_DSC_UNACKNOWLEDGED_EVENT   0x3500
#घोषणा I2O_SCSI_DSC_MESSAGE_RECEIVED       0x3600
#घोषणा I2O_SCSI_DSC_INVALID_CDB            0x3700
#घोषणा I2O_SCSI_DSC_LUN_INVALID            0x3800
#घोषणा I2O_SCSI_DSC_SCSI_TID_INVALID       0x3900
#घोषणा I2O_SCSI_DSC_FUNCTION_UNAVAILABLE   0x3A00
#घोषणा I2O_SCSI_DSC_NO_NEXUS               0x3B00
#घोषणा I2O_SCSI_DSC_SCSI_IID_INVALID       0x3C00
#घोषणा I2O_SCSI_DSC_CDB_RECEIVED           0x3D00
#घोषणा I2O_SCSI_DSC_LUN_ALREADY_ENABLED    0x3E00
#घोषणा I2O_SCSI_DSC_BUS_BUSY               0x3F00
#घोषणा I2O_SCSI_DSC_QUEUE_FROZEN           0x4000


#अगर_अघोषित TRUE
#घोषणा TRUE                  1
#घोषणा FALSE                 0
#पूर्ण_अगर

#घोषणा HBA_FLAGS_INSTALLED_B       0x00000001	// Adapter Was Installed
#घोषणा HBA_FLAGS_BLINKLED_B        0x00000002	// Adapter In Blink LED State
#घोषणा HBA_FLAGS_IN_RESET	0x00000040	/* in reset */
#घोषणा HBA_HOSTRESET_FAILED	0x00000080	/* adpt_resethost failed */


// Device state flags
#घोषणा DPTI_DEV_ONLINE    0x00
#घोषणा DPTI_DEV_UNSCANNED 0x01
#घोषणा DPTI_DEV_RESET	   0x02
#घोषणा DPTI_DEV_OFFLINE   0x04


काष्ठा adpt_device अणु
	काष्ठा adpt_device* next_lun;
	u32	flags;
	u32	type;
	u32	capacity;
	u32	block_size;
	u8	scsi_channel;
	u8	scsi_id;
	u64	scsi_lun;
	u8	state;
	u16	tid;
	काष्ठा i2o_device* pI2o_dev;
	काष्ठा scsi_device *pScsi_dev;
पूर्ण;

काष्ठा adpt_channel अणु
	काष्ठा adpt_device* device[MAX_ID];	/* used as an array of 128 scsi ids */
	u8	scsi_id;
	u8	type;
	u16	tid;
	u32	state;
	काष्ठा i2o_device* pI2o_dev;
पूर्ण;

// HBA state flags
#घोषणा DPTI_STATE_RESET	(0x01)

प्रकार काष्ठा _adpt_hba अणु
	काष्ठा _adpt_hba *next;
	काष्ठा pci_dev *pDev;
	काष्ठा Scsi_Host *host;
	u32 state;
	spinlock_t state_lock;
	पूर्णांक unit;
	पूर्णांक host_no;		/* SCSI host number */
	u8 initialized;
	u8 in_use;		/* is the management node खोलो*/

	अक्षर name[32];
	अक्षर detail[55];

	व्योम __iomem *base_addr_virt;
	व्योम __iomem *msg_addr_virt;
	uदीर्घ base_addr_phys;
	व्योम __iomem *post_port;
	व्योम __iomem *reply_port;
	व्योम __iomem *irq_mask;
	u16  post_count;
	u32  post_fअगरo_size;
	u32  reply_fअगरo_size;
	u32* reply_pool;
	dma_addr_t reply_pool_pa;
	u32  sg_tablesize;	// Scatter/Gather List Size.       
	u8  top_scsi_channel;
	u8  top_scsi_id;
	u64  top_scsi_lun;
	u8  dma64;

	i2o_status_block* status_block;
	dma_addr_t status_block_pa;
	i2o_hrt* hrt;
	dma_addr_t hrt_pa;
	i2o_lct* lct;
	dma_addr_t lct_pa;
	uपूर्णांक lct_size;
	काष्ठा i2o_device* devices;
	काष्ठा adpt_channel channel[MAX_CHANNEL];
	काष्ठा proc_dir_entry* proc_entry;	/* /proc dir */

	व्योम __iomem *FwDebugBuffer_P;	// Virtual Address Of FW Debug Buffer
	u32   FwDebugBufferSize;	// FW Debug Buffer Size In Bytes
	व्योम __iomem *FwDebugStrLength_P;// Virtual Addr Of FW Debug String Len
	व्योम __iomem *FwDebugFlags_P;	// Virtual Address Of FW Debug Flags 
	व्योम __iomem *FwDebugBLEDflag_P;// Virtual Addr Of FW Debug BLED
	व्योम __iomem *FwDebugBLEDvalue_P;// Virtual Addr Of FW Debug BLED
	u32 FwDebugFlags;
	u32 *ioctl_reply_context[4];
पूर्ण adpt_hba;

काष्ठा sg_simple_element अणु
   u32  flag_count;
   u32 addr_bus;
पूर्ण; 

/*
 * Function Prototypes
 */

अटल व्योम adpt_i2o_sys_shutकरोwn(व्योम);
अटल पूर्णांक adpt_init(व्योम);
अटल पूर्णांक adpt_i2o_build_sys_table(व्योम);
अटल irqवापस_t adpt_isr(पूर्णांक irq, व्योम *dev_id);

अटल व्योम adpt_i2o_report_hba_unit(adpt_hba* pHba, काष्ठा i2o_device *d);
अटल पूर्णांक adpt_i2o_query_scalar(adpt_hba* pHba, पूर्णांक tid, 
			पूर्णांक group, पूर्णांक field, व्योम *buf, पूर्णांक buflen);
#अगर_घोषित DEBUG
अटल स्थिर अक्षर *adpt_i2o_get_class_name(पूर्णांक class);
#पूर्ण_अगर
अटल पूर्णांक adpt_i2o_issue_params(पूर्णांक cmd, adpt_hba* pHba, पूर्णांक tid, 
		  व्योम *opblk, dma_addr_t opblk_pa, पूर्णांक oplen,
		  व्योम *resblk, dma_addr_t resblk_pa, पूर्णांक reslen);
अटल पूर्णांक adpt_i2o_post_रुको(adpt_hba* pHba, u32* msg, पूर्णांक len, पूर्णांक समयout);
अटल पूर्णांक adpt_i2o_lct_get(adpt_hba* pHba);
अटल पूर्णांक adpt_i2o_parse_lct(adpt_hba* pHba);
अटल पूर्णांक adpt_i2o_activate_hba(adpt_hba* pHba);
अटल पूर्णांक adpt_i2o_enable_hba(adpt_hba* pHba);
अटल पूर्णांक adpt_i2o_install_device(adpt_hba* pHba, काष्ठा i2o_device *d);
अटल s32 adpt_i2o_post_this(adpt_hba* pHba, u32* data, पूर्णांक len);
अटल s32 adpt_i2o_quiesce_hba(adpt_hba* pHba);
अटल s32 adpt_i2o_status_get(adpt_hba* pHba);
अटल s32 adpt_i2o_init_outbound_q(adpt_hba* pHba);
अटल s32 adpt_i2o_hrt_get(adpt_hba* pHba);
अटल s32 adpt_scsi_to_i2o(adpt_hba* pHba, काष्ठा scsi_cmnd* cmd, काष्ठा adpt_device* dptdevice);
अटल व्योम adpt_i2o_scsi_complete(व्योम __iomem *reply, काष्ठा scsi_cmnd *cmd);
अटल s32 adpt_scsi_host_alloc(adpt_hba* pHba,काष्ठा scsi_host_ढाँचा * sht);
अटल s32 adpt_hba_reset(adpt_hba* pHba);
अटल s32 adpt_i2o_reset_hba(adpt_hba* pHba);
अटल s32 adpt_rescan(adpt_hba* pHba);
अटल s32 adpt_i2o_reparse_lct(adpt_hba* pHba);
अटल s32 adpt_send_nop(adpt_hba*pHba,u32 m);
अटल व्योम adpt_i2o_delete_hba(adpt_hba* pHba);
अटल व्योम adpt_inquiry(adpt_hba* pHba);
अटल काष्ठा adpt_device* adpt_find_device(adpt_hba* pHba, u32 chan, u32 id, u64 lun);
अटल पूर्णांक adpt_install_hba(काष्ठा scsi_host_ढाँचा* sht, काष्ठा pci_dev* pDev) ;
अटल पूर्णांक adpt_i2o_online_hba(adpt_hba* pHba);
अटल व्योम adpt_i2o_post_रुको_complete(u32, पूर्णांक);
अटल पूर्णांक adpt_i2o_systab_send(adpt_hba* pHba);

अटल पूर्णांक adpt_ioctl(काष्ठा inode *inode, काष्ठा file *file, uपूर्णांक cmd, uदीर्घ arg);
अटल पूर्णांक adpt_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक adpt_बंद(काष्ठा inode *inode, काष्ठा file *file);


#अगर_घोषित UARTDELAY
अटल व्योम adpt_delay(पूर्णांक millisec);
#पूर्ण_अगर

#घोषणा PRINT_BUFFER_SIZE     512

#घोषणा HBA_FLAGS_DBG_FLAGS_MASK         0xffff0000	// Mask क्रम debug flags
#घोषणा HBA_FLAGS_DBG_KERNEL_PRINT_B     0x00010000	// Kernel Debugger Prपूर्णांक
#घोषणा HBA_FLAGS_DBG_FW_PRINT_B         0x00020000	// Firmware Debugger Prपूर्णांक
#घोषणा HBA_FLAGS_DBG_FUNCTION_ENTRY_B   0x00040000	// Function Entry Poपूर्णांक
#घोषणा HBA_FLAGS_DBG_FUNCTION_EXIT_B    0x00080000	// Function Exit
#घोषणा HBA_FLAGS_DBG_ERROR_B            0x00100000	// Error Conditions
#घोषणा HBA_FLAGS_DBG_INIT_B             0x00200000	// Init Prपूर्णांकs
#घोषणा HBA_FLAGS_DBG_OS_COMMANDS_B      0x00400000	// OS Command Info
#घोषणा HBA_FLAGS_DBG_SCAN_B             0x00800000	// Device Scan

#घोषणा FW_DEBUG_STR_LENGTH_OFFSET 0
#घोषणा FW_DEBUG_FLAGS_OFFSET      4
#घोषणा FW_DEBUG_BLED_OFFSET       8

#घोषणा FW_DEBUG_FLAGS_NO_HEADERS_B    0x01
#पूर्ण_अगर				/* !HOSTS_C */
#पूर्ण_अगर				/* _DPT_H */
