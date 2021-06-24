<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Linux MegaRAID driver क्रम SAS based RAID controllers
 *
 *  Copyright (c) 2003-2013  LSI Corporation
 *  Copyright (c) 2013-2016  Avago Technologies
 *  Copyright (c) 2016-2018  Broadcom Inc.
 *
 *  खाता: megaraid_sas.h
 *
 *  Authors: Broadcom Inc.
 *           Kashyap Desai <kashyap.desai@broadcom.com>
 *           Sumit Saxena <sumit.saxena@broadcom.com>
 *
 *  Send feedback to: megaraidlinux.pdl@broadcom.com
 */

#अगर_अघोषित LSI_MEGARAID_SAS_H
#घोषणा LSI_MEGARAID_SAS_H

/*
 * MegaRAID SAS Driver meta data
 */
#घोषणा MEGASAS_VERSION				"07.714.04.00-rc1"
#घोषणा MEGASAS_RELDATE				"Apr 14, 2020"

#घोषणा MEGASAS_MSIX_NAME_LEN			32

/*
 * Device IDs
 */
#घोषणा	PCI_DEVICE_ID_LSI_SAS1078R		0x0060
#घोषणा	PCI_DEVICE_ID_LSI_SAS1078DE		0x007C
#घोषणा	PCI_DEVICE_ID_LSI_VERDE_ZCR		0x0413
#घोषणा	PCI_DEVICE_ID_LSI_SAS1078GEN2		0x0078
#घोषणा	PCI_DEVICE_ID_LSI_SAS0079GEN2		0x0079
#घोषणा	PCI_DEVICE_ID_LSI_SAS0073SKINNY		0x0073
#घोषणा	PCI_DEVICE_ID_LSI_SAS0071SKINNY		0x0071
#घोषणा	PCI_DEVICE_ID_LSI_FUSION		0x005b
#घोषणा PCI_DEVICE_ID_LSI_PLASMA		0x002f
#घोषणा PCI_DEVICE_ID_LSI_INVADER		0x005d
#घोषणा PCI_DEVICE_ID_LSI_FURY			0x005f
#घोषणा PCI_DEVICE_ID_LSI_INTRUDER		0x00ce
#घोषणा PCI_DEVICE_ID_LSI_INTRUDER_24		0x00cf
#घोषणा PCI_DEVICE_ID_LSI_CUTLASS_52		0x0052
#घोषणा PCI_DEVICE_ID_LSI_CUTLASS_53		0x0053
#घोषणा PCI_DEVICE_ID_LSI_VENTURA		    0x0014
#घोषणा PCI_DEVICE_ID_LSI_CRUSADER		    0x0015
#घोषणा PCI_DEVICE_ID_LSI_HARPOON		    0x0016
#घोषणा PCI_DEVICE_ID_LSI_TOMCAT		    0x0017
#घोषणा PCI_DEVICE_ID_LSI_VENTURA_4PORT		0x001B
#घोषणा PCI_DEVICE_ID_LSI_CRUSADER_4PORT	0x001C
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E1		0x10e1
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E2		0x10e2
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E5		0x10e5
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E6		0x10e6
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E0		0x10e0
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E3		0x10e3
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E4		0x10e4
#घोषणा PCI_DEVICE_ID_LSI_AERO_10E7		0x10e7

/*
 * Intel HBA SSDIDs
 */
#घोषणा MEGARAID_INTEL_RS3DC080_SSDID		0x9360
#घोषणा MEGARAID_INTEL_RS3DC040_SSDID		0x9362
#घोषणा MEGARAID_INTEL_RS3SC008_SSDID		0x9380
#घोषणा MEGARAID_INTEL_RS3MC044_SSDID		0x9381
#घोषणा MEGARAID_INTEL_RS3WC080_SSDID		0x9341
#घोषणा MEGARAID_INTEL_RS3WC040_SSDID		0x9343
#घोषणा MEGARAID_INTEL_RMS3BC160_SSDID		0x352B

/*
 * Intruder HBA SSDIDs
 */
#घोषणा MEGARAID_INTRUDER_SSDID1		0x9371
#घोषणा MEGARAID_INTRUDER_SSDID2		0x9390
#घोषणा MEGARAID_INTRUDER_SSDID3		0x9370

/*
 * Intel HBA bअक्रमing
 */
#घोषणा MEGARAID_INTEL_RS3DC080_BRANDING	\
	"Intel(R) RAID Controller RS3DC080"
#घोषणा MEGARAID_INTEL_RS3DC040_BRANDING	\
	"Intel(R) RAID Controller RS3DC040"
#घोषणा MEGARAID_INTEL_RS3SC008_BRANDING	\
	"Intel(R) RAID Controller RS3SC008"
#घोषणा MEGARAID_INTEL_RS3MC044_BRANDING	\
	"Intel(R) RAID Controller RS3MC044"
#घोषणा MEGARAID_INTEL_RS3WC080_BRANDING	\
	"Intel(R) RAID Controller RS3WC080"
#घोषणा MEGARAID_INTEL_RS3WC040_BRANDING	\
	"Intel(R) RAID Controller RS3WC040"
#घोषणा MEGARAID_INTEL_RMS3BC160_BRANDING	\
	"Intel(R) Integrated RAID Module RMS3BC160"

/*
 * =====================================
 * MegaRAID SAS MFI firmware definitions
 * =====================================
 */

/*
 * MFI stands क्रम  MegaRAID SAS FW Interface. This is just a moniker क्रम
 * protocol between the software and firmware. Commands are issued using
 * "message frames"
 */

/*
 * FW posts its state in upper 4 bits of outbound_msg_0 रेजिस्टर
 */
#घोषणा MFI_STATE_MASK				0xF0000000
#घोषणा MFI_STATE_UNDEFINED			0x00000000
#घोषणा MFI_STATE_BB_INIT			0x10000000
#घोषणा MFI_STATE_FW_INIT			0x40000000
#घोषणा MFI_STATE_WAIT_HANDSHAKE		0x60000000
#घोषणा MFI_STATE_FW_INIT_2			0x70000000
#घोषणा MFI_STATE_DEVICE_SCAN			0x80000000
#घोषणा MFI_STATE_BOOT_MESSAGE_PENDING		0x90000000
#घोषणा MFI_STATE_FLUSH_CACHE			0xA0000000
#घोषणा MFI_STATE_READY				0xB0000000
#घोषणा MFI_STATE_OPERATIONAL			0xC0000000
#घोषणा MFI_STATE_FAULT				0xF0000000
#घोषणा MFI_STATE_FORCE_OCR			0x00000080
#घोषणा MFI_STATE_DMADONE			0x00000008
#घोषणा MFI_STATE_CRASH_DUMP_DONE		0x00000004
#घोषणा MFI_RESET_REQUIRED			0x00000001
#घोषणा MFI_RESET_ADAPTER			0x00000002
#घोषणा MEGAMFI_FRAME_SIZE			64

#घोषणा MFI_STATE_FAULT_CODE			0x0FFF0000
#घोषणा MFI_STATE_FAULT_SUBCODE			0x0000FF00
/*
 * During FW init, clear pending cmds & reset state using inbound_msg_0
 *
 * ABORT	: Abort all pending cmds
 * READY	: Move from OPERATIONAL to READY state; discard queue info
 * MFIMODE	: Discard (possible) low MFA posted in 64-bit mode (??)
 * CLR_HANDSHAKE: FW is रुकोing क्रम HANDSHAKE from BIOS or Driver
 * HOTPLUG	: Resume from Hotplug
 * MFI_STOP_ADP	: Send संकेत to FW to stop processing
 * MFI_ADP_TRIGGER_SNAP_DUMP: Inक्रमm firmware to initiate snap dump
 */
#घोषणा WRITE_SEQUENCE_OFFSET		(0x0000000FC) /* I20 */
#घोषणा HOST_DIAGNOSTIC_OFFSET		(0x000000F8)  /* I20 */
#घोषणा DIAG_WRITE_ENABLE			(0x00000080)
#घोषणा DIAG_RESET_ADAPTER			(0x00000004)

#घोषणा MFI_ADP_RESET				0x00000040
#घोषणा MFI_INIT_ABORT				0x00000001
#घोषणा MFI_INIT_READY				0x00000002
#घोषणा MFI_INIT_MFIMODE			0x00000004
#घोषणा MFI_INIT_CLEAR_HANDSHAKE		0x00000008
#घोषणा MFI_INIT_HOTPLUG			0x00000010
#घोषणा MFI_STOP_ADP				0x00000020
#घोषणा MFI_RESET_FLAGS				MFI_INIT_READY| \
						MFI_INIT_MFIMODE| \
						MFI_INIT_ABORT
#घोषणा MFI_ADP_TRIGGER_SNAP_DUMP		0x00000100
#घोषणा MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE    (0x01)

/*
 * MFI frame flags
 */
#घोषणा MFI_FRAME_POST_IN_REPLY_QUEUE		0x0000
#घोषणा MFI_FRAME_DONT_POST_IN_REPLY_QUEUE	0x0001
#घोषणा MFI_FRAME_SGL32				0x0000
#घोषणा MFI_FRAME_SGL64				0x0002
#घोषणा MFI_FRAME_SENSE32			0x0000
#घोषणा MFI_FRAME_SENSE64			0x0004
#घोषणा MFI_FRAME_सूची_NONE			0x0000
#घोषणा MFI_FRAME_सूची_WRITE			0x0008
#घोषणा MFI_FRAME_सूची_READ			0x0010
#घोषणा MFI_FRAME_सूची_BOTH			0x0018
#घोषणा MFI_FRAME_IEEE                          0x0020

/* Driver पूर्णांकernal */
#घोषणा DRV_DCMD_POLLED_MODE		0x1
#घोषणा DRV_DCMD_SKIP_REFIRE		0x2

/*
 * Definition क्रम cmd_status
 */
#घोषणा MFI_CMD_STATUS_POLL_MODE		0xFF

/*
 * MFI command opcodes
 */
क्रमागत MFI_CMD_OP अणु
	MFI_CMD_INIT		= 0x0,
	MFI_CMD_LD_READ		= 0x1,
	MFI_CMD_LD_WRITE	= 0x2,
	MFI_CMD_LD_SCSI_IO	= 0x3,
	MFI_CMD_PD_SCSI_IO	= 0x4,
	MFI_CMD_DCMD		= 0x5,
	MFI_CMD_ABORT		= 0x6,
	MFI_CMD_SMP		= 0x7,
	MFI_CMD_STP		= 0x8,
	MFI_CMD_NVME		= 0x9,
	MFI_CMD_TOOLBOX		= 0xa,
	MFI_CMD_OP_COUNT,
	MFI_CMD_INVALID		= 0xff
पूर्ण;

#घोषणा MR_DCMD_CTRL_GET_INFO			0x01010000
#घोषणा MR_DCMD_LD_GET_LIST			0x03010000
#घोषणा MR_DCMD_LD_LIST_QUERY			0x03010100

#घोषणा MR_DCMD_CTRL_CACHE_FLUSH		0x01101000
#घोषणा MR_FLUSH_CTRL_CACHE			0x01
#घोषणा MR_FLUSH_DISK_CACHE			0x02

#घोषणा MR_DCMD_CTRL_SHUTDOWN			0x01050000
#घोषणा MR_DCMD_HIBERNATE_SHUTDOWN		0x01060000
#घोषणा MR_ENABLE_DRIVE_SPINDOWN		0x01

#घोषणा MR_DCMD_CTRL_EVENT_GET_INFO		0x01040100
#घोषणा MR_DCMD_CTRL_EVENT_GET			0x01040300
#घोषणा MR_DCMD_CTRL_EVENT_WAIT			0x01040500
#घोषणा MR_DCMD_LD_GET_PROPERTIES		0x03030000

#घोषणा MR_DCMD_CLUSTER				0x08000000
#घोषणा MR_DCMD_CLUSTER_RESET_ALL		0x08010100
#घोषणा MR_DCMD_CLUSTER_RESET_LD		0x08010200
#घोषणा MR_DCMD_PD_LIST_QUERY                   0x02010100

#घोषणा MR_DCMD_CTRL_SET_CRASH_DUMP_PARAMS	0x01190100
#घोषणा MR_DRIVER_SET_APP_CRASHDUMP_MODE	(0xF0010000 | 0x0600)
#घोषणा MR_DCMD_PD_GET_INFO			0x02020000

/*
 * Global functions
 */
बाह्य u8 MR_ValidateMapInfo(काष्ठा megasas_instance *instance, u64 map_id);


/*
 * MFI command completion codes
 */
क्रमागत MFI_STAT अणु
	MFI_STAT_OK = 0x00,
	MFI_STAT_INVALID_CMD = 0x01,
	MFI_STAT_INVALID_DCMD = 0x02,
	MFI_STAT_INVALID_PARAMETER = 0x03,
	MFI_STAT_INVALID_SEQUENCE_NUMBER = 0x04,
	MFI_STAT_ABORT_NOT_POSSIBLE = 0x05,
	MFI_STAT_APP_HOST_CODE_NOT_FOUND = 0x06,
	MFI_STAT_APP_IN_USE = 0x07,
	MFI_STAT_APP_NOT_INITIALIZED = 0x08,
	MFI_STAT_ARRAY_INDEX_INVALID = 0x09,
	MFI_STAT_ARRAY_ROW_NOT_EMPTY = 0x0a,
	MFI_STAT_CONFIG_RESOURCE_CONFLICT = 0x0b,
	MFI_STAT_DEVICE_NOT_FOUND = 0x0c,
	MFI_STAT_DRIVE_TOO_SMALL = 0x0d,
	MFI_STAT_FLASH_ALLOC_FAIL = 0x0e,
	MFI_STAT_FLASH_BUSY = 0x0f,
	MFI_STAT_FLASH_ERROR = 0x10,
	MFI_STAT_FLASH_IMAGE_BAD = 0x11,
	MFI_STAT_FLASH_IMAGE_INCOMPLETE = 0x12,
	MFI_STAT_FLASH_NOT_OPEN = 0x13,
	MFI_STAT_FLASH_NOT_STARTED = 0x14,
	MFI_STAT_FLUSH_FAILED = 0x15,
	MFI_STAT_HOST_CODE_NOT_FOUNT = 0x16,
	MFI_STAT_LD_CC_IN_PROGRESS = 0x17,
	MFI_STAT_LD_INIT_IN_PROGRESS = 0x18,
	MFI_STAT_LD_LBA_OUT_OF_RANGE = 0x19,
	MFI_STAT_LD_MAX_CONFIGURED = 0x1a,
	MFI_STAT_LD_NOT_OPTIMAL = 0x1b,
	MFI_STAT_LD_RBLD_IN_PROGRESS = 0x1c,
	MFI_STAT_LD_RECON_IN_PROGRESS = 0x1d,
	MFI_STAT_LD_WRONG_RAID_LEVEL = 0x1e,
	MFI_STAT_MAX_SPARES_EXCEEDED = 0x1f,
	MFI_STAT_MEMORY_NOT_AVAILABLE = 0x20,
	MFI_STAT_MFC_HW_ERROR = 0x21,
	MFI_STAT_NO_HW_PRESENT = 0x22,
	MFI_STAT_NOT_FOUND = 0x23,
	MFI_STAT_NOT_IN_ENCL = 0x24,
	MFI_STAT_PD_CLEAR_IN_PROGRESS = 0x25,
	MFI_STAT_PD_TYPE_WRONG = 0x26,
	MFI_STAT_PR_DISABLED = 0x27,
	MFI_STAT_ROW_INDEX_INVALID = 0x28,
	MFI_STAT_SAS_CONFIG_INVALID_ACTION = 0x29,
	MFI_STAT_SAS_CONFIG_INVALID_DATA = 0x2a,
	MFI_STAT_SAS_CONFIG_INVALID_PAGE = 0x2b,
	MFI_STAT_SAS_CONFIG_INVALID_TYPE = 0x2c,
	MFI_STAT_SCSI_DONE_WITH_ERROR = 0x2d,
	MFI_STAT_SCSI_IO_FAILED = 0x2e,
	MFI_STAT_SCSI_RESERVATION_CONFLICT = 0x2f,
	MFI_STAT_SHUTDOWN_FAILED = 0x30,
	MFI_STAT_TIME_NOT_SET = 0x31,
	MFI_STAT_WRONG_STATE = 0x32,
	MFI_STAT_LD_OFFLINE = 0x33,
	MFI_STAT_PEER_NOTIFICATION_REJECTED = 0x34,
	MFI_STAT_PEER_NOTIFICATION_FAILED = 0x35,
	MFI_STAT_RESERVATION_IN_PROGRESS = 0x36,
	MFI_STAT_I2C_ERRORS_DETECTED = 0x37,
	MFI_STAT_PCI_ERRORS_DETECTED = 0x38,
	MFI_STAT_CONFIG_SEQ_MISMATCH = 0x67,

	MFI_STAT_INVALID_STATUS = 0xFF
पूर्ण;

क्रमागत mfi_evt_class अणु
	MFI_EVT_CLASS_DEBUG =		-2,
	MFI_EVT_CLASS_PROGRESS =	-1,
	MFI_EVT_CLASS_INFO =		0,
	MFI_EVT_CLASS_WARNING =		1,
	MFI_EVT_CLASS_CRITICAL =	2,
	MFI_EVT_CLASS_FATAL =		3,
	MFI_EVT_CLASS_DEAD =		4
पूर्ण;

/*
 * Crash dump related defines
 */
#घोषणा MAX_CRASH_DUMP_SIZE 512
#घोषणा CRASH_DMA_BUF_SIZE  (1024 * 1024)

क्रमागत MR_FW_CRASH_DUMP_STATE अणु
	UNAVAILABLE = 0,
	AVAILABLE = 1,
	COPYING = 2,
	COPIED = 3,
	COPY_ERROR = 4,
पूर्ण;

क्रमागत _MR_CRASH_BUF_STATUS अणु
	MR_CRASH_BUF_TURN_OFF = 0,
	MR_CRASH_BUF_TURN_ON = 1,
पूर्ण;

/*
 * Number of mailbox bytes in DCMD message frame
 */
#घोषणा MFI_MBOX_SIZE				12

क्रमागत MR_EVT_CLASS अणु

	MR_EVT_CLASS_DEBUG = -2,
	MR_EVT_CLASS_PROGRESS = -1,
	MR_EVT_CLASS_INFO = 0,
	MR_EVT_CLASS_WARNING = 1,
	MR_EVT_CLASS_CRITICAL = 2,
	MR_EVT_CLASS_FATAL = 3,
	MR_EVT_CLASS_DEAD = 4,

पूर्ण;

क्रमागत MR_EVT_LOCALE अणु

	MR_EVT_LOCALE_LD = 0x0001,
	MR_EVT_LOCALE_PD = 0x0002,
	MR_EVT_LOCALE_ENCL = 0x0004,
	MR_EVT_LOCALE_BBU = 0x0008,
	MR_EVT_LOCALE_SAS = 0x0010,
	MR_EVT_LOCALE_CTRL = 0x0020,
	MR_EVT_LOCALE_CONFIG = 0x0040,
	MR_EVT_LOCALE_CLUSTER = 0x0080,
	MR_EVT_LOCALE_ALL = 0xffff,

पूर्ण;

क्रमागत MR_EVT_ARGS अणु

	MR_EVT_ARGS_NONE,
	MR_EVT_ARGS_CDB_SENSE,
	MR_EVT_ARGS_LD,
	MR_EVT_ARGS_LD_COUNT,
	MR_EVT_ARGS_LD_LBA,
	MR_EVT_ARGS_LD_OWNER,
	MR_EVT_ARGS_LD_LBA_PD_LBA,
	MR_EVT_ARGS_LD_PROG,
	MR_EVT_ARGS_LD_STATE,
	MR_EVT_ARGS_LD_STRIP,
	MR_EVT_ARGS_PD,
	MR_EVT_ARGS_PD_ERR,
	MR_EVT_ARGS_PD_LBA,
	MR_EVT_ARGS_PD_LBA_LD,
	MR_EVT_ARGS_PD_PROG,
	MR_EVT_ARGS_PD_STATE,
	MR_EVT_ARGS_PCI,
	MR_EVT_ARGS_RATE,
	MR_EVT_ARGS_STR,
	MR_EVT_ARGS_TIME,
	MR_EVT_ARGS_ECC,
	MR_EVT_ARGS_LD_PROP,
	MR_EVT_ARGS_PD_SPARE,
	MR_EVT_ARGS_PD_INDEX,
	MR_EVT_ARGS_DIAG_PASS,
	MR_EVT_ARGS_DIAG_FAIL,
	MR_EVT_ARGS_PD_LBA_LBA,
	MR_EVT_ARGS_PORT_PHY,
	MR_EVT_ARGS_PD_MISSING,
	MR_EVT_ARGS_PD_ADDRESS,
	MR_EVT_ARGS_BITMAP,
	MR_EVT_ARGS_CONNECTOR,
	MR_EVT_ARGS_PD_PD,
	MR_EVT_ARGS_PD_FRU,
	MR_EVT_ARGS_PD_PATHINFO,
	MR_EVT_ARGS_PD_POWER_STATE,
	MR_EVT_ARGS_GENERIC,
पूर्ण;


#घोषणा SGE_BUFFER_SIZE	4096
#घोषणा MEGASAS_CLUSTER_ID_SIZE	16
/*
 * define स्थिरants क्रम device list query options
 */
क्रमागत MR_PD_QUERY_TYPE अणु
	MR_PD_QUERY_TYPE_ALL                = 0,
	MR_PD_QUERY_TYPE_STATE              = 1,
	MR_PD_QUERY_TYPE_POWER_STATE        = 2,
	MR_PD_QUERY_TYPE_MEDIA_TYPE         = 3,
	MR_PD_QUERY_TYPE_SPEED              = 4,
	MR_PD_QUERY_TYPE_EXPOSED_TO_HOST    = 5,
पूर्ण;

क्रमागत MR_LD_QUERY_TYPE अणु
	MR_LD_QUERY_TYPE_ALL	         = 0,
	MR_LD_QUERY_TYPE_EXPOSED_TO_HOST = 1,
	MR_LD_QUERY_TYPE_USED_TGT_IDS    = 2,
	MR_LD_QUERY_TYPE_CLUSTER_ACCESS  = 3,
	MR_LD_QUERY_TYPE_CLUSTER_LOCALE  = 4,
पूर्ण;


#घोषणा MR_EVT_CFG_CLEARED                              0x0004
#घोषणा MR_EVT_LD_STATE_CHANGE                          0x0051
#घोषणा MR_EVT_PD_INSERTED                              0x005b
#घोषणा MR_EVT_PD_REMOVED                               0x0070
#घोषणा MR_EVT_LD_CREATED                               0x008a
#घोषणा MR_EVT_LD_DELETED                               0x008b
#घोषणा MR_EVT_FOREIGN_CFG_IMPORTED                     0x00db
#घोषणा MR_EVT_LD_OFFLINE                               0x00fc
#घोषणा MR_EVT_CTRL_HOST_BUS_SCAN_REQUESTED             0x0152
#घोषणा MR_EVT_CTRL_PROP_CHANGED			0x012f

क्रमागत MR_PD_STATE अणु
	MR_PD_STATE_UNCONFIGURED_GOOD   = 0x00,
	MR_PD_STATE_UNCONFIGURED_BAD    = 0x01,
	MR_PD_STATE_HOT_SPARE           = 0x02,
	MR_PD_STATE_OFFLINE             = 0x10,
	MR_PD_STATE_FAILED              = 0x11,
	MR_PD_STATE_REBUILD             = 0x14,
	MR_PD_STATE_ONLINE              = 0x18,
	MR_PD_STATE_COPYBACK            = 0x20,
	MR_PD_STATE_SYSTEM              = 0x40,
 पूर्ण;

जोड़ MR_PD_REF अणु
	काष्ठा अणु
		u16	 deviceId;
		u16	 seqNum;
	पूर्ण mrPdRef;
	u32	 ref;
पूर्ण;

/*
 * define the DDF Type bit काष्ठाure
 */
जोड़ MR_PD_DDF_TYPE अणु
	 काष्ठा अणु
		जोड़ अणु
			काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
				 u16	 क्रमcedPDGUID:1;
				 u16	 inVD:1;
				 u16	 isGlobalSpare:1;
				 u16	 isSpare:1;
				 u16	 isForeign:1;
				 u16	 reserved:7;
				 u16	 पूर्णांकf:4;
#अन्यथा
				 u16	 पूर्णांकf:4;
				 u16	 reserved:7;
				 u16	 isForeign:1;
				 u16	 isSpare:1;
				 u16	 isGlobalSpare:1;
				 u16	 inVD:1;
				 u16	 क्रमcedPDGUID:1;
#पूर्ण_अगर
			 पूर्ण pdType;
			 u16	 type;
		 पूर्ण;
		 u16	 reserved;
	 पूर्ण ddf;
	 काष्ठा अणु
		 u32	reserved;
	 पूर्ण nonDisk;
	 u32	 type;
पूर्ण __packed;

/*
 * defines the progress काष्ठाure
 */
जोड़ MR_PROGRESS अणु
	काष्ठा  अणु
		u16 progress;
		जोड़ अणु
			u16 elapsedSecs;
			u16 elapsedSecsForLastPercent;
		पूर्ण;
	पूर्ण mrProgress;
	u32 w;
पूर्ण __packed;

/*
 * defines the physical drive progress काष्ठाure
 */
काष्ठा MR_PD_PROGRESS अणु
	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u32     rbld:1;
		u32     patrol:1;
		u32     clear:1;
		u32     copyBack:1;
		u32     erase:1;
		u32     locate:1;
		u32     reserved:26;
#अन्यथा
		u32     reserved:26;
		u32     locate:1;
		u32     erase:1;
		u32     copyBack:1;
		u32     clear:1;
		u32     patrol:1;
		u32     rbld:1;
#पूर्ण_अगर
	पूर्ण active;
	जोड़ MR_PROGRESS     rbld;
	जोड़ MR_PROGRESS     patrol;
	जोड़ अणु
		जोड़ MR_PROGRESS     clear;
		जोड़ MR_PROGRESS     erase;
	पूर्ण;

	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u32     rbld:1;
		u32     patrol:1;
		u32     clear:1;
		u32     copyBack:1;
		u32     erase:1;
		u32     reserved:27;
#अन्यथा
		u32     reserved:27;
		u32     erase:1;
		u32     copyBack:1;
		u32     clear:1;
		u32     patrol:1;
		u32     rbld:1;
#पूर्ण_अगर
	पूर्ण छोड़ो;

	जोड़ MR_PROGRESS     reserved[3];
पूर्ण __packed;

काष्ठा  MR_PD_INFO अणु
	जोड़ MR_PD_REF	ref;
	u8 inquiryData[96];
	u8 vpdPage83[64];
	u8 notSupported;
	u8 scsiDevType;

	जोड़ अणु
		u8 connectedPortBiपंचांगap;
		u8 connectedPortNumbers;
	पूर्ण;

	u8 deviceSpeed;
	u32 mediaErrCount;
	u32 otherErrCount;
	u32 predFailCount;
	u32 lastPredFailEventSeqNum;

	u16 fwState;
	u8 disabledForRemoval;
	u8 linkSpeed;
	जोड़ MR_PD_DDF_TYPE state;

	काष्ठा अणु
		u8 count;
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u8 isPathBroken:4;
		u8 reserved3:3;
		u8 widePortCapable:1;
#अन्यथा
		u8 widePortCapable:1;
		u8 reserved3:3;
		u8 isPathBroken:4;
#पूर्ण_अगर

		u8 connectorIndex[2];
		u8 reserved[4];
		u64 sasAddr[2];
		u8 reserved2[16];
	पूर्ण pathInfo;

	u64 rawSize;
	u64 nonCoercedSize;
	u64 coercedSize;
	u16 enclDeviceId;
	u8 enclIndex;

	जोड़ अणु
		u8 slotNumber;
		u8 enclConnectorIndex;
	पूर्ण;

	काष्ठा MR_PD_PROGRESS progInfo;
	u8 badBlockTableFull;
	u8 unusableInCurrentConfig;
	u8 vpdPage83Ext[64];
	u8 घातerState;
	u8 enclPosition;
	u32 allowedOps;
	u16 copyBackPartnerId;
	u16 enclPartnerDeviceId;
	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u16 fdeCapable:1;
		u16 fdeEnabled:1;
		u16 secured:1;
		u16 locked:1;
		u16 क्रमeign:1;
		u16 needsEKM:1;
		u16 reserved:10;
#अन्यथा
		u16 reserved:10;
		u16 needsEKM:1;
		u16 क्रमeign:1;
		u16 locked:1;
		u16 secured:1;
		u16 fdeEnabled:1;
		u16 fdeCapable:1;
#पूर्ण_अगर
	पूर्ण security;
	u8 mediaType;
	u8 notCertअगरied;
	u8 bridgeVenकरोr[8];
	u8 bridgeProductIdentअगरication[16];
	u8 bridgeProductRevisionLevel[4];
	u8 satBridgeExists;

	u8 पूर्णांकerfaceType;
	u8 temperature;
	u8 emulatedBlockSize;
	u16 userDataBlockSize;
	u16 reserved2;

	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u32 piType:3;
		u32 piFormatted:1;
		u32 piEligible:1;
		u32 NCQ:1;
		u32 WCE:1;
		u32 commissionedSpare:1;
		u32 emergencySpare:1;
		u32 ineligibleForSSCD:1;
		u32 ineligibleForLd:1;
		u32 useSSEraseType:1;
		u32 wceUnchanged:1;
		u32 supportScsiUnmap:1;
		u32 reserved:18;
#अन्यथा
		u32 reserved:18;
		u32 supportScsiUnmap:1;
		u32 wceUnchanged:1;
		u32 useSSEraseType:1;
		u32 ineligibleForLd:1;
		u32 ineligibleForSSCD:1;
		u32 emergencySpare:1;
		u32 commissionedSpare:1;
		u32 WCE:1;
		u32 NCQ:1;
		u32 piEligible:1;
		u32 piFormatted:1;
		u32 piType:3;
#पूर्ण_अगर
	पूर्ण properties;

	u64 shieldDiagCompletionTime;
	u8 shieldCounter;

	u8 linkSpeedOther;
	u8 reserved4[2];

	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u32 bbmErrCountSupported:1;
		u32 bbmErrCount:31;
#अन्यथा
		u32 bbmErrCount:31;
		u32 bbmErrCountSupported:1;
#पूर्ण_अगर
	पूर्ण bbmErr;

	u8 reserved1[512-428];
पूर्ण __packed;

/*
 * Definition of काष्ठाure used to expose attributes of VD or JBOD
 * (this काष्ठाure is to be filled by firmware when MR_DCMD_DRV_GET_TARGET_PROP
 * is fired by driver)
 */
काष्ठा MR_TARGET_PROPERTIES अणु
	u32    max_io_size_kb;
	u32    device_qdepth;
	u32    sector_size;
	u8     reset_पंचांगo;
	u8     reserved[499];
पूर्ण __packed;

 /*
 * defines the physical drive address काष्ठाure
 */
काष्ठा MR_PD_ADDRESS अणु
	__le16	deviceId;
	u16     enclDeviceId;

	जोड़ अणु
		काष्ठा अणु
			u8  enclIndex;
			u8  slotNumber;
		पूर्ण mrPdAddress;
		काष्ठा अणु
			u8  enclPosition;
			u8  enclConnectorIndex;
		पूर्ण mrEnclAddress;
	पूर्ण;
	u8      scsiDevType;
	जोड़ अणु
		u8      connectedPortBiपंचांगap;
		u8      connectedPortNumbers;
	पूर्ण;
	u64     sasAddr[2];
पूर्ण __packed;

/*
 * defines the physical drive list काष्ठाure
 */
काष्ठा MR_PD_LIST अणु
	__le32		size;
	__le32		count;
	काष्ठा MR_PD_ADDRESS   addr[1];
पूर्ण __packed;

काष्ठा megasas_pd_list अणु
	u16             tid;
	u8             driveType;
	u8             driveState;
पूर्ण __packed;

 /*
 * defines the logical drive reference काष्ठाure
 */
जोड़  MR_LD_REF अणु
	काष्ठा अणु
		u8      targetId;
		u8      reserved;
		__le16     seqNum;
	पूर्ण;
	__le32     ref;
पूर्ण __packed;

/*
 * defines the logical drive list काष्ठाure
 */
काष्ठा MR_LD_LIST अणु
	__le32     ldCount;
	__le32     reserved;
	काष्ठा अणु
		जोड़ MR_LD_REF   ref;
		u8          state;
		u8          reserved[3];
		__le64		size;
	पूर्ण ldList[MAX_LOGICAL_DRIVES_EXT];
पूर्ण __packed;

काष्ठा MR_LD_TARGETID_LIST अणु
	__le32	size;
	__le32	count;
	u8	pad[3];
	u8	targetId[MAX_LOGICAL_DRIVES_EXT];
पूर्ण;

काष्ठा MR_HOST_DEVICE_LIST_ENTRY अणु
	काष्ठा अणु
		जोड़ अणु
			काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
				u8 reserved:7;
				u8 is_sys_pd:1;
#अन्यथा
				u8 is_sys_pd:1;
				u8 reserved:7;
#पूर्ण_अगर
			पूर्ण bits;
			u8 byte;
		पूर्ण u;
	पूर्ण flags;
	u8 scsi_type;
	__le16 target_id;
	u8 reserved[4];
	__le64 sas_addr[2];
पूर्ण __packed;

काष्ठा MR_HOST_DEVICE_LIST अणु
	__le32			size;
	__le32			count;
	__le32			reserved[2];
	काष्ठा MR_HOST_DEVICE_LIST_ENTRY	host_device_list[1];
पूर्ण __packed;

#घोषणा HOST_DEVICE_LIST_SZ (माप(काष्ठा MR_HOST_DEVICE_LIST) +	       \
			      (माप(काष्ठा MR_HOST_DEVICE_LIST_ENTRY) *      \
			      (MEGASAS_MAX_PD + MAX_LOGICAL_DRIVES_EXT - 1)))


/*
 * SAS controller properties
 */
काष्ठा megasas_ctrl_prop अणु

	u16 seq_num;
	u16 pred_fail_poll_पूर्णांकerval;
	u16 पूर्णांकr_throttle_count;
	u16 पूर्णांकr_throttle_समयouts;
	u8 rebuild_rate;
	u8 patrol_पढ़ो_rate;
	u8 bgi_rate;
	u8 cc_rate;
	u8 recon_rate;
	u8 cache_flush_पूर्णांकerval;
	u8 spinup_drv_count;
	u8 spinup_delay;
	u8 cluster_enable;
	u8 coercion_mode;
	u8 alarm_enable;
	u8 disable_स्वतः_rebuild;
	u8 disable_battery_warn;
	u8 ecc_bucket_size;
	u16 ecc_bucket_leak_rate;
	u8 restore_hotspare_on_insertion;
	u8 expose_encl_devices;
	u8 मुख्यtainPdFailHistory;
	u8 disallowHostRequestReordering;
	u8 पातCCOnError;
	u8 loadBalanceMode;
	u8 disableAutoDetectBackplane;

	u8 snapVDSpace;

	/*
	* Add properties that can be controlled by
	* a bit in the following काष्ठाure.
	*/
	काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
		u32     reserved:18;
		u32     enableJBOD:1;
		u32     disableSpinDownHS:1;
		u32     allowBootWithPinnedCache:1;
		u32     disableOnlineCtrlReset:1;
		u32     enableSecretKeyControl:1;
		u32     स्वतःEnhancedImport:1;
		u32     enableSpinDownUnconfigured:1;
		u32     SSDPatrolReadEnabled:1;
		u32     SSDSMARTerEnabled:1;
		u32     disableNCQ:1;
		u32     useFdeOnly:1;
		u32     prCorrectUnconfiguredAreas:1;
		u32     SMARTerEnabled:1;
		u32     copyBackDisabled:1;
#अन्यथा
		u32     copyBackDisabled:1;
		u32     SMARTerEnabled:1;
		u32     prCorrectUnconfiguredAreas:1;
		u32     useFdeOnly:1;
		u32     disableNCQ:1;
		u32     SSDSMARTerEnabled:1;
		u32     SSDPatrolReadEnabled:1;
		u32     enableSpinDownUnconfigured:1;
		u32     स्वतःEnhancedImport:1;
		u32     enableSecretKeyControl:1;
		u32     disableOnlineCtrlReset:1;
		u32     allowBootWithPinnedCache:1;
		u32     disableSpinDownHS:1;
		u32     enableJBOD:1;
		u32     reserved:18;
#पूर्ण_अगर
	पूर्ण OnOffProperties;

	जोड़ अणु
		u8 स्वतःSnapVDSpace;
		u8 viewSpace;
		काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
			u16 reserved3:9;
			u16 enable_fw_dev_list:1;
			u16 reserved2:1;
			u16 enable_snap_dump:1;
			u16 reserved1:4;
#अन्यथा
			u16 reserved1:4;
			u16 enable_snap_dump:1;
			u16 reserved2:1;
			u16 enable_fw_dev_list:1;
			u16 reserved3:9;
#पूर्ण_अगर
		पूर्ण on_off_properties2;
	पूर्ण;
	__le16 spinDownTime;
	u8  reserved[24];
पूर्ण __packed;

/*
 * SAS controller inक्रमmation
 */
काष्ठा megasas_ctrl_info अणु

	/*
	 * PCI device inक्रमmation
	 */
	काष्ठा अणु

		__le16 venकरोr_id;
		__le16 device_id;
		__le16 sub_venकरोr_id;
		__le16 sub_device_id;
		u8 reserved[24];

	पूर्ण __attribute__ ((packed)) pci;

	/*
	 * Host पूर्णांकerface inक्रमmation
	 */
	काष्ठा अणु

		u8 PCIX:1;
		u8 PCIE:1;
		u8 iSCSI:1;
		u8 SAS_3G:1;
		u8 SRIOV:1;
		u8 reserved_0:3;
		u8 reserved_1[6];
		u8 port_count;
		u64 port_addr[8];

	पूर्ण __attribute__ ((packed)) host_पूर्णांकerface;

	/*
	 * Device (backend) पूर्णांकerface inक्रमmation
	 */
	काष्ठा अणु

		u8 SPI:1;
		u8 SAS_3G:1;
		u8 SATA_1_5G:1;
		u8 SATA_3G:1;
		u8 reserved_0:4;
		u8 reserved_1[6];
		u8 port_count;
		u64 port_addr[8];

	पूर्ण __attribute__ ((packed)) device_पूर्णांकerface;

	/*
	 * List of components residing in flash. All str are null terminated
	 */
	__le32 image_check_word;
	__le32 image_component_count;

	काष्ठा अणु

		अक्षर name[8];
		अक्षर version[32];
		अक्षर build_date[16];
		अक्षर built_समय[16];

	पूर्ण __attribute__ ((packed)) image_component[8];

	/*
	 * List of flash components that have been flashed on the card, but
	 * are not in use, pending reset of the adapter. This list will be
	 * empty अगर a flash operation has not occurred. All stings are null
	 * terminated
	 */
	__le32 pending_image_component_count;

	काष्ठा अणु

		अक्षर name[8];
		अक्षर version[32];
		अक्षर build_date[16];
		अक्षर build_समय[16];

	पूर्ण __attribute__ ((packed)) pending_image_component[8];

	u8 max_arms;
	u8 max_spans;
	u8 max_arrays;
	u8 max_lds;

	अक्षर product_name[80];
	अक्षर serial_no[32];

	/*
	 * Other physical/controller/operation inक्रमmation. Indicates the
	 * presence of the hardware
	 */
	काष्ठा अणु

		u32 bbu:1;
		u32 alarm:1;
		u32 nvram:1;
		u32 uart:1;
		u32 reserved:28;

	पूर्ण __attribute__ ((packed)) hw_present;

	__le32 current_fw_समय;

	/*
	 * Maximum data transfer sizes
	 */
	__le16 max_concurrent_cmds;
	__le16 max_sge_count;
	__le32 max_request_size;

	/*
	 * Logical and physical device counts
	 */
	__le16 ld_present_count;
	__le16 ld_degraded_count;
	__le16 ld_offline_count;

	__le16 pd_present_count;
	__le16 pd_disk_present_count;
	__le16 pd_disk_pred_failure_count;
	__le16 pd_disk_failed_count;

	/*
	 * Memory size inक्रमmation
	 */
	__le16 nvram_size;
	__le16 memory_size;
	__le16 flash_size;

	/*
	 * Error counters
	 */
	__le16 mem_correctable_error_count;
	__le16 mem_uncorrectable_error_count;

	/*
	 * Cluster inक्रमmation
	 */
	u8 cluster_permitted;
	u8 cluster_active;

	/*
	 * Additional max data transfer sizes
	 */
	__le16 max_strips_per_io;

	/*
	 * Controller capabilities काष्ठाures
	 */
	काष्ठा अणु

		u32 raid_level_0:1;
		u32 raid_level_1:1;
		u32 raid_level_5:1;
		u32 raid_level_1E:1;
		u32 raid_level_6:1;
		u32 reserved:27;

	पूर्ण __attribute__ ((packed)) raid_levels;

	काष्ठा अणु

		u32 rbld_rate:1;
		u32 cc_rate:1;
		u32 bgi_rate:1;
		u32 recon_rate:1;
		u32 patrol_rate:1;
		u32 alarm_control:1;
		u32 cluster_supported:1;
		u32 bbu:1;
		u32 spanning_allowed:1;
		u32 dedicated_hotspares:1;
		u32 revertible_hotspares:1;
		u32 क्रमeign_config_import:1;
		u32 self_diagnostic:1;
		u32 mixed_redundancy_arr:1;
		u32 global_hot_spares:1;
		u32 reserved:17;

	पूर्ण __attribute__ ((packed)) adapter_operations;

	काष्ठा अणु

		u32 पढ़ो_policy:1;
		u32 ग_लिखो_policy:1;
		u32 io_policy:1;
		u32 access_policy:1;
		u32 disk_cache_policy:1;
		u32 reserved:27;

	पूर्ण __attribute__ ((packed)) ld_operations;

	काष्ठा अणु

		u8 min;
		u8 max;
		u8 reserved[2];

	पूर्ण __attribute__ ((packed)) stripe_sz_ops;

	काष्ठा अणु

		u32 क्रमce_online:1;
		u32 क्रमce_offline:1;
		u32 क्रमce_rebuild:1;
		u32 reserved:29;

	पूर्ण __attribute__ ((packed)) pd_operations;

	काष्ठा अणु

		u32 ctrl_supports_sas:1;
		u32 ctrl_supports_sata:1;
		u32 allow_mix_in_encl:1;
		u32 allow_mix_in_ld:1;
		u32 allow_sata_in_cluster:1;
		u32 reserved:27;

	पूर्ण __attribute__ ((packed)) pd_mix_support;

	/*
	 * Define ECC single-bit-error bucket inक्रमmation
	 */
	u8 ecc_bucket_count;
	u8 reserved_2[11];

	/*
	 * Include the controller properties (changeable items)
	 */
	काष्ठा megasas_ctrl_prop properties;

	/*
	 * Define FW pkg version (set in envt v'bles on OEM basis)
	 */
	अक्षर package_version[0x60];


	/*
	* If adapterOperations.supportMoreThan8Phys is set,
	* and deviceInterface.portCount is greater than 8,
	* SAS Addrs क्रम first 8 ports shall be populated in
	* deviceInterface.portAddr, and the rest shall be
	* populated in deviceInterfacePortAddr2.
	*/
	__le64	    deviceInterfacePortAddr2[8]; /*6a0h */
	u8          reserved3[128];              /*6e0h */

	काष्ठा अणु                                /*760h */
		u16 minPdRaidLevel_0:4;
		u16 maxPdRaidLevel_0:12;

		u16 minPdRaidLevel_1:4;
		u16 maxPdRaidLevel_1:12;

		u16 minPdRaidLevel_5:4;
		u16 maxPdRaidLevel_5:12;

		u16 minPdRaidLevel_1E:4;
		u16 maxPdRaidLevel_1E:12;

		u16 minPdRaidLevel_6:4;
		u16 maxPdRaidLevel_6:12;

		u16 minPdRaidLevel_10:4;
		u16 maxPdRaidLevel_10:12;

		u16 minPdRaidLevel_50:4;
		u16 maxPdRaidLevel_50:12;

		u16 minPdRaidLevel_60:4;
		u16 maxPdRaidLevel_60:12;

		u16 minPdRaidLevel_1E_RLQ0:4;
		u16 maxPdRaidLevel_1E_RLQ0:12;

		u16 minPdRaidLevel_1E0_RLQ0:4;
		u16 maxPdRaidLevel_1E0_RLQ0:12;

		u16 reserved[6];
	पूर्ण pdsForRaidLevels;

	__le16 maxPds;                          /*780h */
	__le16 maxDedHSPs;                      /*782h */
	__le16 maxGlobalHSP;                    /*784h */
	__le16 ddfSize;                         /*786h */
	u8  maxLdsPerArray;                     /*788h */
	u8  partitionsInDDF;                    /*789h */
	u8  lockKeyBinding;                     /*78ah */
	u8  maxPITsPerLd;                       /*78bh */
	u8  maxViewsPerLd;                      /*78ch */
	u8  maxTargetId;                        /*78dh */
	__le16 maxBvlVdSize;                    /*78eh */

	__le16 maxConfigurableSSCSize;          /*790h */
	__le16 currentSSCsize;                  /*792h */

	अक्षर    expanderFwVersion[12];          /*794h */

	__le16 PFKTrialTimeReमुख्यing;           /*7A0h */

	__le16 cacheMemorySize;                 /*7A2h */

	काष्ठा अणु                                /*7A4h */
#अगर   defined(__BIG_ENDIAN_BITFIELD)
		u32     reserved:5;
		u32	activePassive:2;
		u32	supportConfigAutoBalance:1;
		u32	mpio:1;
		u32	supportDataLDonSSCArray:1;
		u32	supportPoपूर्णांकInTimeProgress:1;
		u32     supportUnevenSpans:1;
		u32     dedicatedHotSparesLimited:1;
		u32     headlessMode:1;
		u32     supportEmulatedDrives:1;
		u32     supportResetNow:1;
		u32     realTimeScheduler:1;
		u32     supportSSDPatrolRead:1;
		u32     supportPerfTuning:1;
		u32     disableOnlinePFKChange:1;
		u32     supportJBOD:1;
		u32     supportBootTimePFKChange:1;
		u32     supportSetLinkSpeed:1;
		u32     supportEmergencySpares:1;
		u32     supportSuspendResumeBGops:1;
		u32     blockSSDWriteCacheChange:1;
		u32     supportShieldState:1;
		u32     supportLdBBMInfo:1;
		u32     supportLdPIType3:1;
		u32     supportLdPIType2:1;
		u32     supportLdPIType1:1;
		u32     supportPIcontroller:1;
#अन्यथा
		u32     supportPIcontroller:1;
		u32     supportLdPIType1:1;
		u32     supportLdPIType2:1;
		u32     supportLdPIType3:1;
		u32     supportLdBBMInfo:1;
		u32     supportShieldState:1;
		u32     blockSSDWriteCacheChange:1;
		u32     supportSuspendResumeBGops:1;
		u32     supportEmergencySpares:1;
		u32     supportSetLinkSpeed:1;
		u32     supportBootTimePFKChange:1;
		u32     supportJBOD:1;
		u32     disableOnlinePFKChange:1;
		u32     supportPerfTuning:1;
		u32     supportSSDPatrolRead:1;
		u32     realTimeScheduler:1;

		u32     supportResetNow:1;
		u32     supportEmulatedDrives:1;
		u32     headlessMode:1;
		u32     dedicatedHotSparesLimited:1;


		u32     supportUnevenSpans:1;
		u32	supportPoपूर्णांकInTimeProgress:1;
		u32	supportDataLDonSSCArray:1;
		u32	mpio:1;
		u32	supportConfigAutoBalance:1;
		u32	activePassive:2;
		u32     reserved:5;
#पूर्ण_अगर
	पूर्ण adapterOperations2;

	u8  driverVersion[32];                  /*7A8h */
	u8  maxDAPdCountSpinup60;               /*7C8h */
	u8  temperatureROC;                     /*7C9h */
	u8  temperatureCtrl;                    /*7CAh */
	u8  reserved4;                          /*7CBh */
	__le16 maxConfigurablePds;              /*7CCh */


	u8  reserved5[2];                       /*0x7CDh */

	/*
	* HA cluster inक्रमmation
	*/
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u32     reserved:25;
		u32     passive:1;
		u32     premiumFeatureMismatch:1;
		u32     ctrlPropIncompatible:1;
		u32     fwVersionMismatch:1;
		u32     hwIncompatible:1;
		u32     peerIsIncompatible:1;
		u32     peerIsPresent:1;
#अन्यथा
		u32     peerIsPresent:1;
		u32     peerIsIncompatible:1;
		u32     hwIncompatible:1;
		u32     fwVersionMismatch:1;
		u32     ctrlPropIncompatible:1;
		u32     premiumFeatureMismatch:1;
		u32     passive:1;
		u32     reserved:25;
#पूर्ण_अगर
	पूर्ण cluster;

	अक्षर clusterId[MEGASAS_CLUSTER_ID_SIZE]; /*0x7D4 */
	काष्ठा अणु
		u8  maxVFsSupported;            /*0x7E4*/
		u8  numVFsEnabled;              /*0x7E5*/
		u8  requestorId;                /*0x7E6 0:PF, 1:VF1, 2:VF2*/
		u8  reserved;                   /*0x7E7*/
	पूर्ण iov;

	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u32     reserved:7;
		u32     useSeqNumJbodFP:1;
		u32     supportExtendedSSCSize:1;
		u32     supportDiskCacheSettingForSysPDs:1;
		u32     supportCPLDUpdate:1;
		u32     supportTTYLogCompression:1;
		u32     discardCacheDuringLDDelete:1;
		u32     supportSecurityonJBOD:1;
		u32     supportCacheBypassModes:1;
		u32     supportDisableSESMonitoring:1;
		u32     supportForceFlash:1;
		u32     supportNVDRAM:1;
		u32     supportDrvActivityLEDSetting:1;
		u32     supportAllowedOpsक्रमDrvRemoval:1;
		u32     supportHOQRebuild:1;
		u32     supportForceTo512e:1;
		u32     supportNVCacheErase:1;
		u32     supportDebugQueue:1;
		u32     supportSwZone:1;
		u32     supportCrashDump:1;
		u32     supportMaxExtLDs:1;
		u32     supportT10RebuildAssist:1;
		u32     supportDisableImmediateIO:1;
		u32     supportThermalPollInterval:1;
		u32     supportPersonalityChange:2;
#अन्यथा
		u32     supportPersonalityChange:2;
		u32     supportThermalPollInterval:1;
		u32     supportDisableImmediateIO:1;
		u32     supportT10RebuildAssist:1;
		u32	supportMaxExtLDs:1;
		u32	supportCrashDump:1;
		u32     supportSwZone:1;
		u32     supportDebugQueue:1;
		u32     supportNVCacheErase:1;
		u32     supportForceTo512e:1;
		u32     supportHOQRebuild:1;
		u32     supportAllowedOpsक्रमDrvRemoval:1;
		u32     supportDrvActivityLEDSetting:1;
		u32     supportNVDRAM:1;
		u32     supportForceFlash:1;
		u32     supportDisableSESMonitoring:1;
		u32     supportCacheBypassModes:1;
		u32     supportSecurityonJBOD:1;
		u32     discardCacheDuringLDDelete:1;
		u32     supportTTYLogCompression:1;
		u32     supportCPLDUpdate:1;
		u32     supportDiskCacheSettingForSysPDs:1;
		u32     supportExtendedSSCSize:1;
		u32     useSeqNumJbodFP:1;
		u32     reserved:7;
#पूर्ण_अगर
	पूर्ण adapterOperations3;

	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 reserved:7;
	/* Indicates whether the CPLD image is part of
	 *  the package and stored in flash
	 */
	u8 cpld_in_flash:1;
#अन्यथा
	u8 cpld_in_flash:1;
	u8 reserved:7;
#पूर्ण_अगर
	u8 reserved1[3];
	/* Null terminated string. Has the version
	 *  inक्रमmation अगर cpld_in_flash = FALSE
	 */
	u8 userCodeDefinition[12];
	पूर्ण cpld;  /* Valid only अगर upgradableCPLD is TRUE */

	काष्ठा अणु
	#अगर defined(__BIG_ENDIAN_BITFIELD)
		u16 reserved:2;
		u16 support_nvme_passthru:1;
		u16 support_pl_debug_info:1;
		u16 support_flash_comp_info:1;
		u16 support_host_info:1;
		u16 support_dual_fw_update:1;
		u16 support_ssc_rev3:1;
		u16 fw_swaps_bbu_vpd_info:1;
		u16 support_pd_map_target_id:1;
		u16 support_ses_ctrl_in_multipathcfg:1;
		u16 image_upload_supported:1;
		u16 support_encrypted_mfc:1;
		u16 supported_enc_algo:1;
		u16 support_ibutton_less:1;
		u16 ctrl_info_ext_supported:1;
	#अन्यथा

		u16 ctrl_info_ext_supported:1;
		u16 support_ibutton_less:1;
		u16 supported_enc_algo:1;
		u16 support_encrypted_mfc:1;
		u16 image_upload_supported:1;
		/* FW supports LUN based association and target port based */
		u16 support_ses_ctrl_in_multipathcfg:1;
		/* association क्रम the SES device connected in multipath mode */
		/* FW defines Jbod target Id within MR_PD_CFG_SEQ */
		u16 support_pd_map_target_id:1;
		/* FW swaps relevant fields in MR_BBU_VPD_INFO_FIXED to
		 *  provide the data in little endian order
		 */
		u16 fw_swaps_bbu_vpd_info:1;
		u16 support_ssc_rev3:1;
		/* FW supports CacheCade 3.0, only one SSCD creation allowed */
		u16 support_dual_fw_update:1;
		/* FW supports dual firmware update feature */
		u16 support_host_info:1;
		/* FW supports MR_DCMD_CTRL_HOST_INFO_SET/GET */
		u16 support_flash_comp_info:1;
		/* FW supports MR_DCMD_CTRL_FLASH_COMP_INFO_GET */
		u16 support_pl_debug_info:1;
		/* FW supports retrieval of PL debug inक्रमmation through apps */
		u16 support_nvme_passthru:1;
		/* FW supports NVMe passthru commands */
		u16 reserved:2;
	#पूर्ण_अगर
		पूर्ण adapter_operations4;
	u8 pad[0x800 - 0x7FE]; /* 0x7FE pad to 2K क्रम expansion */

	u32 size;
	u32 pad1;

	u8 reserved6[64];

	काष्ठा अणु
	#अगर defined(__BIG_ENDIAN_BITFIELD)
		u32 reserved:19;
		u32 support_pci_lane_margining: 1;
		u32 support_psoc_update:1;
		u32 support_क्रमce_personality_change:1;
		u32 support_fde_type_mix:1;
		u32 support_snap_dump:1;
		u32 support_nvme_पंचांग:1;
		u32 support_oce_only:1;
		u32 support_ext_mfg_vpd:1;
		u32 support_pcie:1;
		u32 support_cvhealth_info:1;
		u32 support_profile_change:2;
		u32 mr_config_ext2_supported:1;
	#अन्यथा
		u32 mr_config_ext2_supported:1;
		u32 support_profile_change:2;
		u32 support_cvhealth_info:1;
		u32 support_pcie:1;
		u32 support_ext_mfg_vpd:1;
		u32 support_oce_only:1;
		u32 support_nvme_पंचांग:1;
		u32 support_snap_dump:1;
		u32 support_fde_type_mix:1;
		u32 support_क्रमce_personality_change:1;
		u32 support_psoc_update:1;
		u32 support_pci_lane_margining: 1;
		u32 reserved:19;
	#पूर्ण_अगर
	पूर्ण adapter_operations5;

	u32 rsvdForAdptOp[63];

	u8 reserved7[3];

	u8 TaskAbortTO;	/* Timeout value in seconds used by Abort Task TM */
	u8 MaxResetTO;	/* Max Supported Reset समयout in seconds. */
	u8 reserved8[3];
पूर्ण __packed;

/*
 * ===============================
 * MegaRAID SAS driver definitions
 * ===============================
 */
#घोषणा MEGASAS_MAX_PD_CHANNELS			2
#घोषणा MEGASAS_MAX_LD_CHANNELS			2
#घोषणा MEGASAS_MAX_CHANNELS			(MEGASAS_MAX_PD_CHANNELS + \
						MEGASAS_MAX_LD_CHANNELS)
#घोषणा MEGASAS_MAX_DEV_PER_CHANNEL		128
#घोषणा MEGASAS_DEFAULT_INIT_ID			-1
#घोषणा MEGASAS_MAX_LUN				8
#घोषणा MEGASAS_DEFAULT_CMD_PER_LUN		256
#घोषणा MEGASAS_MAX_PD                          (MEGASAS_MAX_PD_CHANNELS * \
						MEGASAS_MAX_DEV_PER_CHANNEL)
#घोषणा MEGASAS_MAX_LD_IDS			(MEGASAS_MAX_LD_CHANNELS * \
						MEGASAS_MAX_DEV_PER_CHANNEL)

#घोषणा MEGASAS_MAX_SECTORS                    (2*1024)
#घोषणा MEGASAS_MAX_SECTORS_IEEE		(2*128)
#घोषणा MEGASAS_DBG_LVL				1

#घोषणा MEGASAS_FW_BUSY				1

/* Driver's पूर्णांकernal Logging levels*/
#घोषणा OCR_DEBUG    (1 << 0)
#घोषणा TM_DEBUG     (1 << 1)
#घोषणा LD_PD_DEBUG    (1 << 2)

#घोषणा SCAN_PD_CHANNEL	0x1
#घोषणा SCAN_VD_CHANNEL	0x2

#घोषणा MEGASAS_KDUMP_QUEUE_DEPTH               100
#घोषणा MR_LARGE_IO_MIN_SIZE			(32 * 1024)
#घोषणा MR_R1_LDIO_PIGGYBACK_DEFAULT		4

क्रमागत MR_SCSI_CMD_TYPE अणु
	READ_WRITE_LDIO = 0,
	NON_READ_WRITE_LDIO = 1,
	READ_WRITE_SYSPDIO = 2,
	NON_READ_WRITE_SYSPDIO = 3,
पूर्ण;

क्रमागत DCMD_TIMEOUT_ACTION अणु
	INITIATE_OCR = 0,
	KILL_ADAPTER = 1,
	IGNORE_TIMEOUT = 2,
पूर्ण;

क्रमागत FW_BOOT_CONTEXT अणु
	PROBE_CONTEXT = 0,
	OCR_CONTEXT = 1,
पूर्ण;

/* Frame Type */
#घोषणा IO_FRAME				0
#घोषणा PTHRU_FRAME				1

/*
 * When SCSI mid-layer calls driver's reset routine, driver रुकोs क्रम
 * MEGASAS_RESET_WAIT_TIME seconds क्रम all outstanding IO to complete. Note
 * that the driver cannot _actually_ पात or reset pending commands. While
 * it is रुकोing क्रम the commands to complete, it prपूर्णांकs a diagnostic message
 * every MEGASAS_RESET_NOTICE_INTERVAL seconds
 */
#घोषणा MEGASAS_RESET_WAIT_TIME			180
#घोषणा MEGASAS_INTERNAL_CMD_WAIT_TIME		180
#घोषणा	MEGASAS_RESET_NOTICE_INTERVAL		5
#घोषणा MEGASAS_IOCTL_CMD			0
#घोषणा MEGASAS_DEFAULT_CMD_TIMEOUT		90
#घोषणा MEGASAS_THROTTLE_QUEUE_DEPTH		16
#घोषणा MEGASAS_DEFAULT_TM_TIMEOUT		50
/*
 * FW reports the maximum of number of commands that it can accept (maximum
 * commands that can be outstanding) at any समय. The driver must report a
 * lower number to the mid layer because it can issue a few पूर्णांकernal commands
 * itself (E.g, AEN, पात cmd, IOCTLs etc). The number of commands it needs
 * is shown below
 */
#घोषणा MEGASAS_INT_CMDS			32
#घोषणा MEGASAS_SKINNY_INT_CMDS			5
#घोषणा MEGASAS_FUSION_INTERNAL_CMDS		8
#घोषणा MEGASAS_FUSION_IOCTL_CMDS		3
#घोषणा MEGASAS_MFI_IOCTL_CMDS			27

#घोषणा MEGASAS_MAX_MSIX_QUEUES			128
/*
 * FW can accept both 32 and 64 bit SGLs. We want to allocate 32/64 bit
 * SGLs based on the size of dma_addr_t
 */
#घोषणा IS_DMA64				(माप(dma_addr_t) == 8)

#घोषणा MFI_XSCALE_OMR0_CHANGE_INTERRUPT		0x00000001

#घोषणा MFI_INTR_FLAG_REPLY_MESSAGE			0x00000001
#घोषणा MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE		0x00000002
#घोषणा MFI_G2_OUTBOUND_DOORBELL_CHANGE_INTERRUPT	0x00000004

#घोषणा MFI_OB_INTR_STATUS_MASK			0x00000002
#घोषणा MFI_POLL_TIMEOUT_SECS			60
#घोषणा MFI_IO_TIMEOUT_SECS			180
#घोषणा MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF	(5 * HZ)
#घोषणा MEGASAS_OCR_SETTLE_TIME_VF		(1000 * 30)
#घोषणा MEGASAS_SRIOV_MAX_RESET_TRIES_VF	1
#घोषणा MEGASAS_ROUTINE_WAIT_TIME_VF		300
#घोषणा MFI_REPLY_1078_MESSAGE_INTERRUPT	0x80000000
#घोषणा MFI_REPLY_GEN2_MESSAGE_INTERRUPT	0x00000001
#घोषणा MFI_GEN2_ENABLE_INTERRUPT_MASK		(0x00000001 | 0x00000004)
#घोषणा MFI_REPLY_SKINNY_MESSAGE_INTERRUPT	0x40000000
#घोषणा MFI_SKINNY_ENABLE_INTERRUPT_MASK	(0x00000001)

#घोषणा MFI_1068_PCSR_OFFSET			0x84
#घोषणा MFI_1068_FW_HANDSHAKE_OFFSET		0x64
#घोषणा MFI_1068_FW_READY			0xDDDD0000

#घोषणा MR_MAX_REPLY_QUEUES_OFFSET              0X0000001F
#घोषणा MR_MAX_REPLY_QUEUES_EXT_OFFSET          0X003FC000
#घोषणा MR_MAX_REPLY_QUEUES_EXT_OFFSET_SHIFT    14
#घोषणा MR_MAX_MSIX_REG_ARRAY                   16
#घोषणा MR_RDPQ_MODE_OFFSET			0X00800000

#घोषणा MR_MAX_RAID_MAP_SIZE_OFFSET_SHIFT	16
#घोषणा MR_MAX_RAID_MAP_SIZE_MASK		0x1FF
#घोषणा MR_MIN_MAP_SIZE				0x10000
/* 64k */

#घोषणा MR_CAN_HANDLE_SYNC_CACHE_OFFSET		0X01000000

#घोषणा MR_ATOMIC_DESCRIPTOR_SUPPORT_OFFSET	(1 << 24)

#घोषणा MR_CAN_HANDLE_64_BIT_DMA_OFFSET		(1 << 25)
#घोषणा MR_INTR_COALESCING_SUPPORT_OFFSET	(1 << 26)

#घोषणा MEGASAS_WATCHDOG_THREAD_INTERVAL	1000
#घोषणा MEGASAS_WAIT_FOR_NEXT_DMA_MSECS		20
#घोषणा MEGASAS_WATCHDOG_WAIT_COUNT		50

क्रमागत MR_ADAPTER_TYPE अणु
	MFI_SERIES = 1,
	THUNDERBOLT_SERIES = 2,
	INVADER_SERIES = 3,
	VENTURA_SERIES = 4,
	AERO_SERIES = 5,
पूर्ण;

/*
* रेजिस्टर set क्रम both 1068 and 1078 controllers
* काष्ठाure extended क्रम 1078 रेजिस्टरs
*/

काष्ठा megasas_रेजिस्टर_set अणु
	u32	करोorbell;                       /*0000h*/
	u32	fusion_seq_offset;		/*0004h*/
	u32	fusion_host_diag;		/*0008h*/
	u32	reserved_01;			/*000Ch*/

	u32 	inbound_msg_0;			/*0010h*/
	u32 	inbound_msg_1;			/*0014h*/
	u32 	outbound_msg_0;			/*0018h*/
	u32 	outbound_msg_1;			/*001Ch*/

	u32 	inbound_करोorbell;		/*0020h*/
	u32 	inbound_पूर्णांकr_status;		/*0024h*/
	u32 	inbound_पूर्णांकr_mask;		/*0028h*/

	u32 	outbound_करोorbell;		/*002Ch*/
	u32 	outbound_पूर्णांकr_status;		/*0030h*/
	u32 	outbound_पूर्णांकr_mask;		/*0034h*/

	u32 	reserved_1[2];			/*0038h*/

	u32 	inbound_queue_port;		/*0040h*/
	u32 	outbound_queue_port;		/*0044h*/

	u32	reserved_2[9];			/*0048h*/
	u32	reply_post_host_index;		/*006Ch*/
	u32	reserved_2_2[12];		/*0070h*/

	u32 	outbound_करोorbell_clear;	/*00A0h*/

	u32 	reserved_3[3];			/*00A4h*/

	u32	outbound_scratch_pad_0;		/*00B0h*/
	u32	outbound_scratch_pad_1;         /*00B4h*/
	u32	outbound_scratch_pad_2;         /*00B8h*/
	u32	outbound_scratch_pad_3;         /*00BCh*/

	u32 	inbound_low_queue_port ;	/*00C0h*/

	u32 	inbound_high_queue_port ;	/*00C4h*/

	u32 inbound_single_queue_port;	/*00C8h*/
	u32	res_6[11];			/*CCh*/
	u32	host_diag;
	u32	seq_offset;
	u32 	index_रेजिस्टरs[807];		/*00CCh*/
पूर्ण __attribute__ ((packed));

काष्ठा megasas_sge32 अणु

	__le32 phys_addr;
	__le32 length;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_sge64 अणु

	__le64 phys_addr;
	__le32 length;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_sge_skinny अणु
	__le64 phys_addr;
	__le32 length;
	__le32 flag;
पूर्ण __packed;

जोड़ megasas_sgl अणु

	काष्ठा megasas_sge32 sge32[1];
	काष्ठा megasas_sge64 sge64[1];
	काष्ठा megasas_sge_skinny sge_skinny[1];

पूर्ण __attribute__ ((packed));

काष्ठा megasas_header अणु

	u8 cmd;			/*00h */
	u8 sense_len;		/*01h */
	u8 cmd_status;		/*02h */
	u8 scsi_status;		/*03h */

	u8 target_id;		/*04h */
	u8 lun;			/*05h */
	u8 cdb_len;		/*06h */
	u8 sge_count;		/*07h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 समयout;		/*12h */
	__le32 data_xferlen;	/*14h */

पूर्ण __attribute__ ((packed));

जोड़ megasas_sgl_frame अणु

	काष्ठा megasas_sge32 sge32[8];
	काष्ठा megasas_sge64 sge64[5];

पूर्ण __attribute__ ((packed));

प्रकार जोड़ _MFI_CAPABILITIES अणु
	काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
	u32     reserved:16;
	u32	support_fw_exposed_dev_list:1;
	u32	support_nvme_passthru:1;
	u32     support_64bit_mode:1;
	u32 support_pd_map_target_id:1;
	u32     support_qd_throttling:1;
	u32     support_fp_rlbypass:1;
	u32     support_vfid_in_ioframe:1;
	u32     support_ext_io_size:1;
	u32		support_ext_queue_depth:1;
	u32     security_protocol_cmds_fw:1;
	u32     support_core_affinity:1;
	u32     support_ndrive_r1_lb:1;
	u32		support_max_255lds:1;
	u32		support_fastpath_wb:1;
	u32     support_additional_msix:1;
	u32     support_fp_remote_lun:1;
#अन्यथा
	u32     support_fp_remote_lun:1;
	u32     support_additional_msix:1;
	u32		support_fastpath_wb:1;
	u32		support_max_255lds:1;
	u32     support_ndrive_r1_lb:1;
	u32     support_core_affinity:1;
	u32     security_protocol_cmds_fw:1;
	u32		support_ext_queue_depth:1;
	u32     support_ext_io_size:1;
	u32     support_vfid_in_ioframe:1;
	u32     support_fp_rlbypass:1;
	u32     support_qd_throttling:1;
	u32	support_pd_map_target_id:1;
	u32     support_64bit_mode:1;
	u32	support_nvme_passthru:1;
	u32	support_fw_exposed_dev_list:1;
	u32     reserved:16;
#पूर्ण_अगर
	पूर्ण mfi_capabilities;
	__le32		reg;
पूर्ण MFI_CAPABILITIES;

काष्ठा megasas_init_frame अणु

	u8 cmd;			/*00h */
	u8 reserved_0;		/*01h */
	u8 cmd_status;		/*02h */

	u8 reserved_1;		/*03h */
	MFI_CAPABILITIES driver_operations; /*04h*/

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 replyqueue_mask;		/*12h */
	__le32 data_xfer_len;	/*14h */

	__le32 queue_info_new_phys_addr_lo;	/*18h */
	__le32 queue_info_new_phys_addr_hi;	/*1Ch */
	__le32 queue_info_old_phys_addr_lo;	/*20h */
	__le32 queue_info_old_phys_addr_hi;	/*24h */
	__le32 reserved_4[2];	/*28h */
	__le32 प्रणाली_info_lo;      /*30h */
	__le32 प्रणाली_info_hi;      /*34h */
	__le32 reserved_5[2];	/*38h */

पूर्ण __attribute__ ((packed));

काष्ठा megasas_init_queue_info अणु

	__le32 init_flags;		/*00h */
	__le32 reply_queue_entries;	/*04h */

	__le32 reply_queue_start_phys_addr_lo;	/*08h */
	__le32 reply_queue_start_phys_addr_hi;	/*0Ch */
	__le32 producer_index_phys_addr_lo;	/*10h */
	__le32 producer_index_phys_addr_hi;	/*14h */
	__le32 consumer_index_phys_addr_lo;	/*18h */
	__le32 consumer_index_phys_addr_hi;	/*1Ch */

पूर्ण __attribute__ ((packed));

काष्ठा megasas_io_frame अणु

	u8 cmd;			/*00h */
	u8 sense_len;		/*01h */
	u8 cmd_status;		/*02h */
	u8 scsi_status;		/*03h */

	u8 target_id;		/*04h */
	u8 access_byte;		/*05h */
	u8 reserved_0;		/*06h */
	u8 sge_count;		/*07h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 समयout;		/*12h */
	__le32 lba_count;	/*14h */

	__le32 sense_buf_phys_addr_lo;	/*18h */
	__le32 sense_buf_phys_addr_hi;	/*1Ch */

	__le32 start_lba_lo;	/*20h */
	__le32 start_lba_hi;	/*24h */

	जोड़ megasas_sgl sgl;	/*28h */

पूर्ण __attribute__ ((packed));

काष्ठा megasas_pthru_frame अणु

	u8 cmd;			/*00h */
	u8 sense_len;		/*01h */
	u8 cmd_status;		/*02h */
	u8 scsi_status;		/*03h */

	u8 target_id;		/*04h */
	u8 lun;			/*05h */
	u8 cdb_len;		/*06h */
	u8 sge_count;		/*07h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 समयout;		/*12h */
	__le32 data_xfer_len;	/*14h */

	__le32 sense_buf_phys_addr_lo;	/*18h */
	__le32 sense_buf_phys_addr_hi;	/*1Ch */

	u8 cdb[16];		/*20h */
	जोड़ megasas_sgl sgl;	/*30h */

पूर्ण __attribute__ ((packed));

काष्ठा megasas_dcmd_frame अणु

	u8 cmd;			/*00h */
	u8 reserved_0;		/*01h */
	u8 cmd_status;		/*02h */
	u8 reserved_1[4];	/*03h */
	u8 sge_count;		/*07h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 समयout;		/*12h */

	__le32 data_xfer_len;	/*14h */
	__le32 opcode;		/*18h */

	जोड़ अणु			/*1Ch */
		u8 b[12];
		__le16 s[6];
		__le32 w[3];
	पूर्ण mbox;

	जोड़ megasas_sgl sgl;	/*28h */

पूर्ण __attribute__ ((packed));

काष्ठा megasas_पात_frame अणु

	u8 cmd;			/*00h */
	u8 reserved_0;		/*01h */
	u8 cmd_status;		/*02h */

	u8 reserved_1;		/*03h */
	__le32 reserved_2;	/*04h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 reserved_3;	/*12h */
	__le32 reserved_4;	/*14h */

	__le32 पात_context;	/*18h */
	__le32 pad_1;		/*1Ch */

	__le32 पात_mfi_phys_addr_lo;	/*20h */
	__le32 पात_mfi_phys_addr_hi;	/*24h */

	__le32 reserved_5[6];	/*28h */

पूर्ण __attribute__ ((packed));

काष्ठा megasas_smp_frame अणु

	u8 cmd;			/*00h */
	u8 reserved_1;		/*01h */
	u8 cmd_status;		/*02h */
	u8 connection_status;	/*03h */

	u8 reserved_2[3];	/*04h */
	u8 sge_count;		/*07h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 समयout;		/*12h */

	__le32 data_xfer_len;	/*14h */
	__le64 sas_addr;	/*18h */

	जोड़ अणु
		काष्ठा megasas_sge32 sge32[2];	/* [0]: resp [1]: req */
		काष्ठा megasas_sge64 sge64[2];	/* [0]: resp [1]: req */
	पूर्ण sgl;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_stp_frame अणु

	u8 cmd;			/*00h */
	u8 reserved_1;		/*01h */
	u8 cmd_status;		/*02h */
	u8 reserved_2;		/*03h */

	u8 target_id;		/*04h */
	u8 reserved_3[2];	/*05h */
	u8 sge_count;		/*07h */

	__le32 context;		/*08h */
	__le32 pad_0;		/*0Ch */

	__le16 flags;		/*10h */
	__le16 समयout;		/*12h */

	__le32 data_xfer_len;	/*14h */

	__le16 fis[10];		/*18h */
	__le32 stp_flags;

	जोड़ अणु
		काष्ठा megasas_sge32 sge32[2];	/* [0]: resp [1]: data */
		काष्ठा megasas_sge64 sge64[2];	/* [0]: resp [1]: data */
	पूर्ण sgl;

पूर्ण __attribute__ ((packed));

जोड़ megasas_frame अणु

	काष्ठा megasas_header hdr;
	काष्ठा megasas_init_frame init;
	काष्ठा megasas_io_frame io;
	काष्ठा megasas_pthru_frame pthru;
	काष्ठा megasas_dcmd_frame dcmd;
	काष्ठा megasas_पात_frame पात;
	काष्ठा megasas_smp_frame smp;
	काष्ठा megasas_stp_frame stp;

	u8 raw_bytes[64];
पूर्ण;

/**
 * काष्ठा MR_PRIV_DEVICE - sdev निजी hostdata
 * @is_पंचांग_capable: firmware managed पंचांग_capable flag
 * @पंचांग_busy: TM request is in progress
 * @sdev_priv_busy: pending command per sdev
 */
काष्ठा MR_PRIV_DEVICE अणु
	bool is_पंचांग_capable;
	bool पंचांग_busy;
	atomic_t sdev_priv_busy;
	atomic_t r1_ldio_hपूर्णांक;
	u8 पूर्णांकerface_type;
	u8 task_पात_पंचांगo;
	u8 target_reset_पंचांगo;
पूर्ण;
काष्ठा megasas_cmd;

जोड़ megasas_evt_class_locale अणु

	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u16 locale;
		u8 reserved;
		s8 class;
#अन्यथा
		s8 class;
		u8 reserved;
		u16 locale;
#पूर्ण_अगर
	पूर्ण __attribute__ ((packed)) members;

	u32 word;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_evt_log_info अणु
	__le32 newest_seq_num;
	__le32 oldest_seq_num;
	__le32 clear_seq_num;
	__le32 shutकरोwn_seq_num;
	__le32 boot_seq_num;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_progress अणु

	__le16 progress;
	__le16 elapsed_seconds;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_evtarg_ld अणु

	u16 target_id;
	u8 ld_index;
	u8 reserved;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_evtarg_pd अणु
	u16 device_id;
	u8 encl_index;
	u8 slot_number;

पूर्ण __attribute__ ((packed));

काष्ठा megasas_evt_detail अणु

	__le32 seq_num;
	__le32 समय_stamp;
	__le32 code;
	जोड़ megasas_evt_class_locale cl;
	u8 arg_type;
	u8 reserved1[15];

	जोड़ अणु
		काष्ठा अणु
			काष्ठा megasas_evtarg_pd pd;
			u8 cdb_length;
			u8 sense_length;
			u8 reserved[2];
			u8 cdb[16];
			u8 sense[64];
		पूर्ण __attribute__ ((packed)) cdbSense;

		काष्ठा megasas_evtarg_ld ld;

		काष्ठा अणु
			काष्ठा megasas_evtarg_ld ld;
			__le64 count;
		पूर्ण __attribute__ ((packed)) ld_count;

		काष्ठा अणु
			__le64 lba;
			काष्ठा megasas_evtarg_ld ld;
		पूर्ण __attribute__ ((packed)) ld_lba;

		काष्ठा अणु
			काष्ठा megasas_evtarg_ld ld;
			__le32 prevOwner;
			__le32 newOwner;
		पूर्ण __attribute__ ((packed)) ld_owner;

		काष्ठा अणु
			u64 ld_lba;
			u64 pd_lba;
			काष्ठा megasas_evtarg_ld ld;
			काष्ठा megasas_evtarg_pd pd;
		पूर्ण __attribute__ ((packed)) ld_lba_pd_lba;

		काष्ठा अणु
			काष्ठा megasas_evtarg_ld ld;
			काष्ठा megasas_progress prog;
		पूर्ण __attribute__ ((packed)) ld_prog;

		काष्ठा अणु
			काष्ठा megasas_evtarg_ld ld;
			u32 prev_state;
			u32 new_state;
		पूर्ण __attribute__ ((packed)) ld_state;

		काष्ठा अणु
			u64 strip;
			काष्ठा megasas_evtarg_ld ld;
		पूर्ण __attribute__ ((packed)) ld_strip;

		काष्ठा megasas_evtarg_pd pd;

		काष्ठा अणु
			काष्ठा megasas_evtarg_pd pd;
			u32 err;
		पूर्ण __attribute__ ((packed)) pd_err;

		काष्ठा अणु
			u64 lba;
			काष्ठा megasas_evtarg_pd pd;
		पूर्ण __attribute__ ((packed)) pd_lba;

		काष्ठा अणु
			u64 lba;
			काष्ठा megasas_evtarg_pd pd;
			काष्ठा megasas_evtarg_ld ld;
		पूर्ण __attribute__ ((packed)) pd_lba_ld;

		काष्ठा अणु
			काष्ठा megasas_evtarg_pd pd;
			काष्ठा megasas_progress prog;
		पूर्ण __attribute__ ((packed)) pd_prog;

		काष्ठा अणु
			काष्ठा megasas_evtarg_pd pd;
			u32 prevState;
			u32 newState;
		पूर्ण __attribute__ ((packed)) pd_state;

		काष्ठा अणु
			u16 venकरोrId;
			__le16 deviceId;
			u16 subVenकरोrId;
			u16 subDeviceId;
		पूर्ण __attribute__ ((packed)) pci;

		u32 rate;
		अक्षर str[96];

		काष्ठा अणु
			u32 rtc;
			u32 elapsedSeconds;
		पूर्ण __attribute__ ((packed)) समय;

		काष्ठा अणु
			u32 ecar;
			u32 elog;
			अक्षर str[64];
		पूर्ण __attribute__ ((packed)) ecc;

		u8 b[96];
		__le16 s[48];
		__le32 w[24];
		__le64 d[12];
	पूर्ण args;

	अक्षर description[128];

पूर्ण __attribute__ ((packed));

काष्ठा megasas_aen_event अणु
	काष्ठा delayed_work hotplug_work;
	काष्ठा megasas_instance *instance;
पूर्ण;

काष्ठा megasas_irq_context अणु
	अक्षर name[MEGASAS_MSIX_NAME_LEN];
	काष्ठा megasas_instance *instance;
	u32 MSIxIndex;
	u32 os_irq;
	काष्ठा irq_poll irqpoll;
	bool irq_poll_scheduled;
	bool irq_line_enable;
	atomic_t   in_used;
पूर्ण;

काष्ठा MR_DRV_SYSTEM_INFO अणु
	u8	infoVersion;
	u8	प्रणालीIdLength;
	u16	reserved0;
	u8	प्रणालीId[64];
	u8	reserved[1980];
पूर्ण;

क्रमागत MR_PD_TYPE अणु
	UNKNOWN_DRIVE = 0,
	PARALLEL_SCSI = 1,
	SAS_PD = 2,
	SATA_PD = 3,
	FC_PD = 4,
	NVME_PD = 5,
पूर्ण;

/* JBOD Queue depth definitions */
#घोषणा MEGASAS_SATA_QD	32
#घोषणा MEGASAS_SAS_QD 256
#घोषणा MEGASAS_DEFAULT_PD_QD	64
#घोषणा MEGASAS_NVME_QD        64

#घोषणा MR_DEFAULT_NVME_PAGE_SIZE	4096
#घोषणा MR_DEFAULT_NVME_PAGE_SHIFT	12
#घोषणा MR_DEFAULT_NVME_MDTS_KB		128
#घोषणा MR_NVME_PAGE_SIZE_MASK		0x000000FF

/*Aero perक्रमmance parameters*/
#घोषणा MR_HIGH_IOPS_QUEUE_COUNT	8
#घोषणा MR_DEVICE_HIGH_IOPS_DEPTH	8
#घोषणा MR_HIGH_IOPS_BATCH_COUNT	16

क्रमागत MR_PERF_MODE अणु
	MR_BALANCED_PERF_MODE		= 0,
	MR_IOPS_PERF_MODE		= 1,
	MR_LATENCY_PERF_MODE		= 2,
पूर्ण;

#घोषणा MEGASAS_PERF_MODE_2STR(mode) \
		((mode) == MR_BALANCED_PERF_MODE ? "Balanced" : \
		 (mode) == MR_IOPS_PERF_MODE ? "IOPS" : \
		 (mode) == MR_LATENCY_PERF_MODE ? "Latency" : \
		 "Unknown")

काष्ठा megasas_instance अणु

	अचिन्हित पूर्णांक *reply_map;
	__le32 *producer;
	dma_addr_t producer_h;
	__le32 *consumer;
	dma_addr_t consumer_h;
	काष्ठा MR_DRV_SYSTEM_INFO *प्रणाली_info_buf;
	dma_addr_t प्रणाली_info_h;
	काष्ठा MR_LD_VF_AFFILIATION *vf_affiliation;
	dma_addr_t vf_affiliation_h;
	काष्ठा MR_LD_VF_AFFILIATION_111 *vf_affiliation_111;
	dma_addr_t vf_affiliation_111_h;
	काष्ठा MR_CTRL_HB_HOST_MEM *hb_host_mem;
	dma_addr_t hb_host_mem_h;
	काष्ठा MR_PD_INFO *pd_info;
	dma_addr_t pd_info_h;
	काष्ठा MR_TARGET_PROPERTIES *tgt_prop;
	dma_addr_t tgt_prop_h;

	__le32 *reply_queue;
	dma_addr_t reply_queue_h;

	u32 *crash_dump_buf;
	dma_addr_t crash_dump_h;

	काष्ठा MR_PD_LIST *pd_list_buf;
	dma_addr_t pd_list_buf_h;

	काष्ठा megasas_ctrl_info *ctrl_info_buf;
	dma_addr_t ctrl_info_buf_h;

	काष्ठा MR_LD_LIST *ld_list_buf;
	dma_addr_t ld_list_buf_h;

	काष्ठा MR_LD_TARGETID_LIST *ld_targetid_list_buf;
	dma_addr_t ld_targetid_list_buf_h;

	काष्ठा MR_HOST_DEVICE_LIST *host_device_list_buf;
	dma_addr_t host_device_list_buf_h;

	काष्ठा MR_SNAPDUMP_PROPERTIES *snapdump_prop;
	dma_addr_t snapdump_prop_h;

	व्योम *crash_buf[MAX_CRASH_DUMP_SIZE];
	अचिन्हित पूर्णांक    fw_crash_buffer_size;
	अचिन्हित पूर्णांक    fw_crash_state;
	अचिन्हित पूर्णांक    fw_crash_buffer_offset;
	u32 drv_buf_index;
	u32 drv_buf_alloc;
	u32 crash_dump_fw_support;
	u32 crash_dump_drv_support;
	u32 crash_dump_app_support;
	u32 secure_jbod_support;
	u32 support_morethan256jbod; /* FW support क्रम more than 256 PD/JBOD */
	bool use_seqnum_jbod_fp;   /* Added क्रम PD sequence */
	bool smp_affinity_enable;
	spinlock_t crashdump_lock;

	काष्ठा megasas_रेजिस्टर_set __iomem *reg_set;
	u32 __iomem *reply_post_host_index_addr[MR_MAX_MSIX_REG_ARRAY];
	काष्ठा megasas_pd_list          pd_list[MEGASAS_MAX_PD];
	काष्ठा megasas_pd_list          local_pd_list[MEGASAS_MAX_PD];
	u8 ld_ids[MEGASAS_MAX_LD_IDS];
	s8 init_id;

	u16 max_num_sge;
	u16 max_fw_cmds;
	u16 max_mpt_cmds;
	u16 max_mfi_cmds;
	u16 max_scsi_cmds;
	u16 ldio_threshold;
	u16 cur_can_queue;
	u32 max_sectors_per_req;
	bool msix_load_balance;
	काष्ठा megasas_aen_event *ev;

	काष्ठा megasas_cmd **cmd_list;
	काष्ठा list_head cmd_pool;
	/* used to sync fire the cmd to fw */
	spinlock_t mfi_pool_lock;
	/* used to sync fire the cmd to fw */
	spinlock_t hba_lock;
	/* used to synch producer, consumer ptrs in dpc */
	spinlock_t stream_lock;
	spinlock_t completion_lock;
	काष्ठा dma_pool *frame_dma_pool;
	काष्ठा dma_pool *sense_dma_pool;

	काष्ठा megasas_evt_detail *evt_detail;
	dma_addr_t evt_detail_h;
	काष्ठा megasas_cmd *aen_cmd;
	काष्ठा semaphore ioctl_sem;

	काष्ठा Scsi_Host *host;

	रुको_queue_head_t पूर्णांक_cmd_रुको_q;
	रुको_queue_head_t पात_cmd_रुको_q;

	काष्ठा pci_dev *pdev;
	u32 unique_id;
	u32 fw_support_ieee;
	u32 threshold_reply_count;

	atomic_t fw_outstanding;
	atomic_t ldio_outstanding;
	atomic_t fw_reset_no_pci_access;
	atomic64_t total_io_count;
	atomic64_t high_iops_outstanding;

	काष्ठा megasas_instance_ढाँचा *instancet;
	काष्ठा tasklet_काष्ठा isr_tasklet;
	काष्ठा work_काष्ठा work_init;
	काष्ठा delayed_work fw_fault_work;
	काष्ठा workqueue_काष्ठा *fw_fault_work_q;
	अक्षर fault_handler_work_q_name[48];

	u8 flag;
	u8 unload;
	u8 flag_ieee;
	u8 issuepend_करोne;
	u8 disableOnlineCtrlReset;
	u8 UnevenSpanSupport;

	u8 supporपंचांगax256vd;
	u8 pd_list_not_supported;
	u16 fw_supported_vd_count;
	u16 fw_supported_pd_count;

	u16 drv_supported_vd_count;
	u16 drv_supported_pd_count;

	atomic_t adprecovery;
	अचिन्हित दीर्घ last_समय;
	u32 mfiStatus;
	u32 last_seq_num;

	काष्ठा list_head पूर्णांकernal_reset_pending_q;

	/* Ptr to hba specअगरic inक्रमmation */
	व्योम *ctrl_context;
	अचिन्हित पूर्णांक msix_vectors;
	काष्ठा megasas_irq_context irq_context[MEGASAS_MAX_MSIX_QUEUES];
	u64 map_id;
	u64 pd_seq_map_id;
	काष्ठा megasas_cmd *map_update_cmd;
	काष्ठा megasas_cmd *jbod_seq_cmd;
	अचिन्हित दीर्घ bar;
	दीर्घ reset_flags;
	काष्ठा mutex reset_mutex;
	काष्ठा समयr_list sriov_heartbeat_समयr;
	अक्षर skip_heartbeat_समयr_del;
	u8 requestorId;
	अक्षर Plयंत्रaFW111;
	अक्षर clusterId[MEGASAS_CLUSTER_ID_SIZE];
	u8 peerIsPresent;
	u8 passive;
	u16 throttlequeuedepth;
	u8 mask_पूर्णांकerrupts;
	u16 max_chain_frame_sz;
	u8 is_imr;
	u8 is_rdpq;
	bool dev_handle;
	bool fw_sync_cache_support;
	u32 mfi_frame_size;
	bool msix_combined;
	u16 max_raid_mapsize;
	/* preffered count to send as LDIO irrspective of FP capable.*/
	u8  r1_ldio_hपूर्णांक_शेष;
	u32 nvme_page_size;
	u8 adapter_type;
	bool consistent_mask_64bit;
	bool support_nvme_passthru;
	bool enable_sdev_max_qd;
	u8 task_पात_पंचांगo;
	u8 max_reset_पंचांगo;
	u8 snapdump_रुको_समय;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_root;
	काष्ठा dentry *raidmap_dump;
#पूर्ण_अगर
	u8 enable_fw_dev_list;
	bool atomic_desc_support;
	bool support_seqnum_jbod_fp;
	bool support_pci_lane_margining;
	u8  low_latency_index_start;
	पूर्णांक perf_mode;
	पूर्णांक iopoll_q_count;
पूर्ण;

काष्ठा MR_LD_VF_MAP अणु
	u32 size;
	जोड़ MR_LD_REF ref;
	u8 ldVfCount;
	u8 reserved[6];
	u8 policy[1];
पूर्ण;

काष्ठा MR_LD_VF_AFFILIATION अणु
	u32 size;
	u8 ldCount;
	u8 vfCount;
	u8 thisVf;
	u8 reserved[9];
	काष्ठा MR_LD_VF_MAP map[1];
पूर्ण;

/* Plयंत्रa 1.11 FW backward compatibility काष्ठाures */
#घोषणा IOV_111_OFFSET 0x7CE
#घोषणा MAX_VIRTUAL_FUNCTIONS 8
#घोषणा MR_LD_ACCESS_HIDDEN 15

काष्ठा IOV_111 अणु
	u8 maxVFsSupported;
	u8 numVFsEnabled;
	u8 requestorId;
	u8 reserved[5];
पूर्ण;

काष्ठा MR_LD_VF_MAP_111 अणु
	u8 targetId;
	u8 reserved[3];
	u8 policy[MAX_VIRTUAL_FUNCTIONS];
पूर्ण;

काष्ठा MR_LD_VF_AFFILIATION_111 अणु
	u8 vdCount;
	u8 vfCount;
	u8 thisVf;
	u8 reserved[5];
	काष्ठा MR_LD_VF_MAP_111 map[MAX_LOGICAL_DRIVES];
पूर्ण;

काष्ठा MR_CTRL_HB_HOST_MEM अणु
	काष्ठा अणु
		u32 fwCounter;	/* Firmware heart beat counter */
		काष्ठा अणु
			u32 debugmode:1; /* 1=Firmware is in debug mode.
					    Heart beat will not be updated. */
			u32 reserved:31;
		पूर्ण debug;
		u32 reserved_fw[6];
		u32 driverCounter; /* Driver heart beat counter.  0x20 */
		u32 reserved_driver[7];
	पूर्ण HB;
	u8 pad[0x400-0x40];
पूर्ण;

क्रमागत अणु
	MEGASAS_HBA_OPERATIONAL			= 0,
	MEGASAS_ADPRESET_SM_INFAULT		= 1,
	MEGASAS_ADPRESET_SM_FW_RESET_SUCCESS	= 2,
	MEGASAS_ADPRESET_SM_OPERATIONAL		= 3,
	MEGASAS_HW_CRITICAL_ERROR		= 4,
	MEGASAS_ADPRESET_SM_POLLING		= 5,
	MEGASAS_ADPRESET_INPROG_SIGN		= 0xDEADDEAD,
पूर्ण;

काष्ठा megasas_instance_ढाँचा अणु
	व्योम (*fire_cmd)(काष्ठा megasas_instance *, dma_addr_t, \
		u32, काष्ठा megasas_रेजिस्टर_set __iomem *);

	व्योम (*enable_पूर्णांकr)(काष्ठा megasas_instance *);
	व्योम (*disable_पूर्णांकr)(काष्ठा megasas_instance *);

	पूर्णांक (*clear_पूर्णांकr)(काष्ठा megasas_instance *);

	u32 (*पढ़ो_fw_status_reg)(काष्ठा megasas_instance *);
	पूर्णांक (*adp_reset)(काष्ठा megasas_instance *, \
		काष्ठा megasas_रेजिस्टर_set __iomem *);
	पूर्णांक (*check_reset)(काष्ठा megasas_instance *, \
		काष्ठा megasas_रेजिस्टर_set __iomem *);
	irqवापस_t (*service_isr)(पूर्णांक irq, व्योम *devp);
	व्योम (*tasklet)(अचिन्हित दीर्घ);
	u32 (*init_adapter)(काष्ठा megasas_instance *);
	u32 (*build_and_issue_cmd) (काष्ठा megasas_instance *,
				    काष्ठा scsi_cmnd *);
	व्योम (*issue_dcmd)(काष्ठा megasas_instance *instance,
			    काष्ठा megasas_cmd *cmd);
पूर्ण;

#घोषणा MEGASAS_IS_LOGICAL(sdev)					\
	((sdev->channel < MEGASAS_MAX_PD_CHANNELS) ? 0 : 1)

#घोषणा MEGASAS_DEV_INDEX(scp)						\
	(((scp->device->channel % 2) * MEGASAS_MAX_DEV_PER_CHANNEL) +	\
	scp->device->id)

#घोषणा MEGASAS_PD_INDEX(scp)						\
	((scp->device->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +		\
	scp->device->id)

काष्ठा megasas_cmd अणु

	जोड़ megasas_frame *frame;
	dma_addr_t frame_phys_addr;
	u8 *sense;
	dma_addr_t sense_phys_addr;

	u32 index;
	u8 sync_cmd;
	u8 cmd_status_drv;
	u8 पात_aen;
	u8 retry_क्रम_fw_reset;


	काष्ठा list_head list;
	काष्ठा scsi_cmnd *scmd;
	u8 flags;

	काष्ठा megasas_instance *instance;
	जोड़ अणु
		काष्ठा अणु
			u16 smid;
			u16 resvd;
		पूर्ण context;
		u32 frame_count;
	पूर्ण;
पूर्ण;

#घोषणा MAX_MGMT_ADAPTERS		1024
#घोषणा MAX_IOCTL_SGE			16

काष्ठा megasas_iocpacket अणु

	u16 host_no;
	u16 __pad1;
	u32 sgl_off;
	u32 sge_count;
	u32 sense_off;
	u32 sense_len;
	जोड़ अणु
		u8 raw[128];
		काष्ठा megasas_header hdr;
	पूर्ण frame;

	काष्ठा iovec sgl[MAX_IOCTL_SGE];

पूर्ण __attribute__ ((packed));

काष्ठा megasas_aen अणु
	u16 host_no;
	u16 __pad1;
	u32 seq_num;
	u32 class_locale_word;
पूर्ण __attribute__ ((packed));

काष्ठा compat_megasas_iocpacket अणु
	u16 host_no;
	u16 __pad1;
	u32 sgl_off;
	u32 sge_count;
	u32 sense_off;
	u32 sense_len;
	जोड़ अणु
		u8 raw[128];
		काष्ठा megasas_header hdr;
	पूर्ण frame;
	काष्ठा compat_iovec sgl[MAX_IOCTL_SGE];
पूर्ण __attribute__ ((packed));

#घोषणा MEGASAS_IOC_FIRMWARE32	_IOWR('M', 1, काष्ठा compat_megasas_iocpacket)

#घोषणा MEGASAS_IOC_FIRMWARE	_IOWR('M', 1, काष्ठा megasas_iocpacket)
#घोषणा MEGASAS_IOC_GET_AEN	_IOW('M', 3, काष्ठा megasas_aen)

काष्ठा megasas_mgmt_info अणु

	u16 count;
	काष्ठा megasas_instance *instance[MAX_MGMT_ADAPTERS];
	पूर्णांक max_index;
पूर्ण;

क्रमागत MEGASAS_OCR_CAUSE अणु
	FW_FAULT_OCR			= 0,
	SCSIIO_TIMEOUT_OCR		= 1,
	MFI_IO_TIMEOUT_OCR		= 2,
पूर्ण;

क्रमागत DCMD_RETURN_STATUS अणु
	DCMD_SUCCESS    = 0x00,
	DCMD_TIMEOUT    = 0x01,
	DCMD_FAILED     = 0x02,
	DCMD_BUSY       = 0x03,
	DCMD_INIT       = 0xff,
पूर्ण;

u8
MR_BuildRaidContext(काष्ठा megasas_instance *instance,
		    काष्ठा IO_REQUEST_INFO *io_info,
		    काष्ठा RAID_CONTEXT *pRAID_Context,
		    काष्ठा MR_DRV_RAID_MAP_ALL *map, u8 **raidLUN);
u16 MR_TargetIdToLdGet(u32 ldTgtId, काष्ठा MR_DRV_RAID_MAP_ALL *map);
काष्ठा MR_LD_RAID *MR_LdRaidGet(u32 ld, काष्ठा MR_DRV_RAID_MAP_ALL *map);
u16 MR_ArPdGet(u32 ar, u32 arm, काष्ठा MR_DRV_RAID_MAP_ALL *map);
u16 MR_LdSpanArrayGet(u32 ld, u32 span, काष्ठा MR_DRV_RAID_MAP_ALL *map);
__le16 MR_PdDevHandleGet(u32 pd, काष्ठा MR_DRV_RAID_MAP_ALL *map);
u16 MR_GetLDTgtId(u32 ld, काष्ठा MR_DRV_RAID_MAP_ALL *map);

__le16 get_updated_dev_handle(काष्ठा megasas_instance *instance,
			      काष्ठा LD_LOAD_BALANCE_INFO *lbInfo,
			      काष्ठा IO_REQUEST_INFO *in_info,
			      काष्ठा MR_DRV_RAID_MAP_ALL *drv_map);
व्योम mr_update_load_balance_params(काष्ठा MR_DRV_RAID_MAP_ALL *map,
	काष्ठा LD_LOAD_BALANCE_INFO *lbInfo);
पूर्णांक megasas_get_ctrl_info(काष्ठा megasas_instance *instance);
/* PD sequence */
पूर्णांक
megasas_sync_pd_seq_num(काष्ठा megasas_instance *instance, bool pend);
व्योम megasas_set_dynamic_target_properties(काष्ठा scsi_device *sdev,
					   bool is_target_prop);
पूर्णांक megasas_get_target_prop(काष्ठा megasas_instance *instance,
			    काष्ठा scsi_device *sdev);
व्योम megasas_get_snapdump_properties(काष्ठा megasas_instance *instance);

पूर्णांक megasas_set_crash_dump_params(काष्ठा megasas_instance *instance,
	u8 crash_buf_state);
व्योम megasas_मुक्त_host_crash_buffer(काष्ठा megasas_instance *instance);

व्योम megasas_वापस_cmd_fusion(काष्ठा megasas_instance *instance,
	काष्ठा megasas_cmd_fusion *cmd);
पूर्णांक megasas_issue_blocked_cmd(काष्ठा megasas_instance *instance,
	काष्ठा megasas_cmd *cmd, पूर्णांक समयout);
व्योम __megasas_वापस_cmd(काष्ठा megasas_instance *instance,
	काष्ठा megasas_cmd *cmd);

व्योम megasas_वापस_mfi_mpt_pthr(काष्ठा megasas_instance *instance,
	काष्ठा megasas_cmd *cmd_mfi, काष्ठा megasas_cmd_fusion *cmd_fusion);
पूर्णांक megasas_cmd_type(काष्ठा scsi_cmnd *cmd);
व्योम megasas_setup_jbod_map(काष्ठा megasas_instance *instance);

व्योम megasas_update_sdev_properties(काष्ठा scsi_device *sdev);
पूर्णांक megasas_reset_fusion(काष्ठा Scsi_Host *shost, पूर्णांक reason);
पूर्णांक megasas_task_पात_fusion(काष्ठा scsi_cmnd *scmd);
पूर्णांक megasas_reset_target_fusion(काष्ठा scsi_cmnd *scmd);
u32 mega_mod64(u64 भागidend, u32 भागisor);
पूर्णांक megasas_alloc_fusion_context(काष्ठा megasas_instance *instance);
व्योम megasas_मुक्त_fusion_context(काष्ठा megasas_instance *instance);
पूर्णांक megasas_fusion_start_watchकरोg(काष्ठा megasas_instance *instance);
व्योम megasas_fusion_stop_watchकरोg(काष्ठा megasas_instance *instance);

व्योम megasas_set_dma_settings(काष्ठा megasas_instance *instance,
			      काष्ठा megasas_dcmd_frame *dcmd,
			      dma_addr_t dma_addr, u32 dma_len);
पूर्णांक megasas_adp_reset_रुको_क्रम_पढ़ोy(काष्ठा megasas_instance *instance,
				     bool करो_adp_reset,
				     पूर्णांक ocr_context);
पूर्णांक megasas_irqpoll(काष्ठा irq_poll *irqpoll, पूर्णांक budget);
व्योम megasas_dump_fusion_io(काष्ठा scsi_cmnd *scmd);
u32 megasas_पढ़ोl(काष्ठा megasas_instance *instance,
		  स्थिर अस्थिर व्योम __iomem *addr);
काष्ठा megasas_cmd *megasas_get_cmd(काष्ठा megasas_instance *instance);
व्योम megasas_वापस_cmd(काष्ठा megasas_instance *instance,
			काष्ठा megasas_cmd *cmd);
पूर्णांक megasas_issue_polled(काष्ठा megasas_instance *instance,
			 काष्ठा megasas_cmd *cmd);
व्योम megaraid_sas_समाप्त_hba(काष्ठा megasas_instance *instance);
व्योम megasas_check_and_restore_queue_depth(काष्ठा megasas_instance *instance);
व्योम megasas_start_समयr(काष्ठा megasas_instance *instance);
पूर्णांक megasas_sriov_start_heartbeat(काष्ठा megasas_instance *instance,
				  पूर्णांक initial);
पूर्णांक megasas_alloc_cmds(काष्ठा megasas_instance *instance);
व्योम megasas_मुक्त_cmds(काष्ठा megasas_instance *instance);

व्योम megasas_init_debugfs(व्योम);
व्योम megasas_निकास_debugfs(व्योम);
व्योम megasas_setup_debugfs(काष्ठा megasas_instance *instance);
व्योम megasas_destroy_debugfs(काष्ठा megasas_instance *instance);
पूर्णांक megasas_blk_mq_poll(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक queue_num);

#पूर्ण_अगर				/*LSI_MEGARAID_SAS_H */
