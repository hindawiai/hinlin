<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _SCSI_I2O_H
#घोषणा _SCSI_I2O_H

/* I2O kernel space accessible काष्ठाures/APIs
 *
 * (c) Copyright 1999, 2000 Red Hat Software
 *
 *************************************************************************
 *
 * This header file defined the I2O APIs/काष्ठाures क्रम use by
 * the I2O kernel modules.
 */

#अगर_घोषित __KERNEL__       /* This file to be included by kernel only */

#समावेश <linux/i2o-dev.h>

#समावेश <linux/notअगरier.h>
#समावेश <linux/atomic.h>


/*
 *	Tunable parameters first
 */

/* How many dअगरferent OSM's are we allowing */
#घोषणा MAX_I2O_MODULES		64

#घोषणा I2O_EVT_CAPABILITY_OTHER		0x01
#घोषणा I2O_EVT_CAPABILITY_CHANGED		0x02

#घोषणा I2O_EVT_SENSOR_STATE_CHANGED		0x01

//#अगर_घोषित __KERNEL__   /* ioctl stuff only thing exported to users */

#घोषणा I2O_MAX_MANAGERS	4

/*
 *	I2O Interface Objects
 */

#समावेश <linux/रुको.h>
प्रकार रुको_queue_head_t adpt_रुको_queue_head_t;
#घोषणा ADPT_DECLARE_WAIT_QUEUE_HEAD(रुको) DECLARE_WAIT_QUEUE_HEAD_ONSTACK(रुको)
प्रकार रुको_queue_entry_t adpt_रुको_queue_entry_t;

/*
 * message काष्ठाures
 */

काष्ठा i2o_message
अणु
	u8	version_offset;
	u8	flags;
	u16	size;
	u32	target_tid:12;
	u32	init_tid:12;
	u32	function:8;
	u32	initiator_context;
	/* List follows */
पूर्ण;

काष्ठा adpt_device;
काष्ठा _adpt_hba;
काष्ठा i2o_device
अणु
	काष्ठा i2o_device *next;	/* Chain */
	काष्ठा i2o_device *prev;

	अक्षर dev_name[8];		/* linux /dev name अगर available */
	i2o_lct_entry lct_data;/* Device LCT inक्रमmation */
	u32 flags;
	काष्ठा proc_dir_entry* proc_entry;	/* /proc dir */
	काष्ठा adpt_device *owner;
	काष्ठा _adpt_hba *controller;	/* Controlling IOP */
पूर्ण;

/*
 *	Each I2O controller has one of these objects
 */

काष्ठा i2o_controller
अणु
	अक्षर name[16];
	पूर्णांक unit;
	पूर्णांक type;
	पूर्णांक enabled;

	काष्ठा notअगरier_block *event_notअगरer;	/* Events */
	atomic_t users;
	काष्ठा i2o_device *devices;		/* I2O device chain */
	काष्ठा i2o_controller *next;		/* Controller chain */

पूर्ण;

/*
 * I2O System table entry
 */
काष्ठा i2o_sys_tbl_entry
अणु
	u16	org_id;
	u16	reserved1;
	u32	iop_id:12;
	u32	reserved2:20;
	u16	seg_num:12;
	u16	i2o_version:4;
	u8	iop_state;
	u8	msg_type;
	u16	frame_size;
	u16	reserved3;
	u32	last_changed;
	u32	iop_capabilities;
	u32	inbound_low;
	u32	inbound_high;
पूर्ण;

काष्ठा i2o_sys_tbl
अणु
	u8	num_entries;
	u8	version;
	u16	reserved1;
	u32	change_ind;
	u32	reserved2;
	u32	reserved3;
	काष्ठा i2o_sys_tbl_entry iops[0];
पूर्ण;

/*
 *	I2O classes / subclasses
 */

/*  Class ID and Code Assignments
 *  (LCT.ClassID.Version field)
 */
#घोषणा    I2O_CLASS_VERSION_10                        0x00
#घोषणा    I2O_CLASS_VERSION_11                        0x01

/*  Class code names
 *  (from v1.5 Table 6-1 Class Code Assignments.)
 */

#घोषणा    I2O_CLASS_EXECUTIVE                         0x000
#घोषणा    I2O_CLASS_DDM                               0x001
#घोषणा    I2O_CLASS_RANDOM_BLOCK_STORAGE              0x010
#घोषणा    I2O_CLASS_SEQUENTIAL_STORAGE                0x011
#घोषणा    I2O_CLASS_LAN                               0x020
#घोषणा    I2O_CLASS_WAN                               0x030
#घोषणा    I2O_CLASS_FIBRE_CHANNEL_PORT                0x040
#घोषणा    I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL          0x041
#घोषणा    I2O_CLASS_SCSI_PERIPHERAL                   0x051
#घोषणा    I2O_CLASS_ATE_PORT                          0x060
#घोषणा    I2O_CLASS_ATE_PERIPHERAL                    0x061
#घोषणा    I2O_CLASS_FLOPPY_CONTROLLER                 0x070
#घोषणा    I2O_CLASS_FLOPPY_DEVICE                     0x071
#घोषणा    I2O_CLASS_BUS_ADAPTER_PORT                  0x080
#घोषणा    I2O_CLASS_PEER_TRANSPORT_AGENT              0x090
#घोषणा    I2O_CLASS_PEER_TRANSPORT                    0x091

/*  Rest of 0x092 - 0x09f reserved क्रम peer-to-peer classes
 */

#घोषणा    I2O_CLASS_MATCH_ANYCLASS                    0xffffffff

/*  Subclasses
 */

#घोषणा    I2O_SUBCLASS_i960                           0x001
#घोषणा    I2O_SUBCLASS_HDM                            0x020
#घोषणा    I2O_SUBCLASS_ISM                            0x021

/* Operation functions */

#घोषणा I2O_PARAMS_FIELD_GET	0x0001
#घोषणा I2O_PARAMS_LIST_GET	0x0002
#घोषणा I2O_PARAMS_MORE_GET	0x0003
#घोषणा I2O_PARAMS_SIZE_GET	0x0004
#घोषणा I2O_PARAMS_TABLE_GET	0x0005
#घोषणा I2O_PARAMS_FIELD_SET	0x0006
#घोषणा I2O_PARAMS_LIST_SET	0x0007
#घोषणा I2O_PARAMS_ROW_ADD	0x0008
#घोषणा I2O_PARAMS_ROW_DELETE	0x0009
#घोषणा I2O_PARAMS_TABLE_CLEAR	0x000A

/*
 *	I2O serial number conventions / क्रमmats
 *	(circa v1.5)
 */

#घोषणा    I2O_SNFORMAT_UNKNOWN                        0
#घोषणा    I2O_SNFORMAT_BINARY                         1
#घोषणा    I2O_SNFORMAT_ASCII                          2
#घोषणा    I2O_SNFORMAT_UNICODE                        3
#घोषणा    I2O_SNFORMAT_LAN48_MAC                      4
#घोषणा    I2O_SNFORMAT_WAN                            5

/* Plus new in v2.0 (Yellowstone pdf करोc)
 */

#घोषणा    I2O_SNFORMAT_LAN64_MAC                      6
#घोषणा    I2O_SNFORMAT_DDM                            7
#घोषणा    I2O_SNFORMAT_IEEE_REG64                     8
#घोषणा    I2O_SNFORMAT_IEEE_REG128                    9
#घोषणा    I2O_SNFORMAT_UNKNOWN2                       0xff

/* Transaction Reply Lists (TRL) Control Word काष्ठाure */

#घोषणा TRL_SINGLE_FIXED_LENGTH		0x00
#घोषणा TRL_SINGLE_VARIABLE_LENGTH	0x40
#घोषणा TRL_MULTIPLE_FIXED_LENGTH	0x80

/*
 *	Messaging API values
 */

#घोषणा	I2O_CMD_ADAPTER_ASSIGN		0xB3
#घोषणा	I2O_CMD_ADAPTER_READ		0xB2
#घोषणा	I2O_CMD_ADAPTER_RELEASE		0xB5
#घोषणा	I2O_CMD_BIOS_INFO_SET		0xA5
#घोषणा	I2O_CMD_BOOT_DEVICE_SET		0xA7
#घोषणा	I2O_CMD_CONFIG_VALIDATE		0xBB
#घोषणा	I2O_CMD_CONN_SETUP		0xCA
#घोषणा	I2O_CMD_DDM_DESTROY		0xB1
#घोषणा	I2O_CMD_DDM_ENABLE		0xD5
#घोषणा	I2O_CMD_DDM_QUIESCE		0xC7
#घोषणा	I2O_CMD_DDM_RESET		0xD9
#घोषणा	I2O_CMD_DDM_SUSPEND		0xAF
#घोषणा	I2O_CMD_DEVICE_ASSIGN		0xB7
#घोषणा	I2O_CMD_DEVICE_RELEASE		0xB9
#घोषणा	I2O_CMD_HRT_GET			0xA8
#घोषणा	I2O_CMD_ADAPTER_CLEAR		0xBE
#घोषणा	I2O_CMD_ADAPTER_CONNECT		0xC9
#घोषणा	I2O_CMD_ADAPTER_RESET		0xBD
#घोषणा	I2O_CMD_LCT_NOTIFY		0xA2
#घोषणा	I2O_CMD_OUTBOUND_INIT		0xA1
#घोषणा	I2O_CMD_PATH_ENABLE		0xD3
#घोषणा	I2O_CMD_PATH_QUIESCE		0xC5
#घोषणा	I2O_CMD_PATH_RESET		0xD7
#घोषणा	I2O_CMD_STATIC_MF_CREATE	0xDD
#घोषणा	I2O_CMD_STATIC_MF_RELEASE	0xDF
#घोषणा	I2O_CMD_STATUS_GET		0xA0
#घोषणा	I2O_CMD_SW_DOWNLOAD		0xA9
#घोषणा	I2O_CMD_SW_UPLOAD		0xAB
#घोषणा	I2O_CMD_SW_REMOVE		0xAD
#घोषणा	I2O_CMD_SYS_ENABLE		0xD1
#घोषणा	I2O_CMD_SYS_MODIFY		0xC1
#घोषणा	I2O_CMD_SYS_QUIESCE		0xC3
#घोषणा	I2O_CMD_SYS_TAB_SET		0xA3

#घोषणा I2O_CMD_UTIL_NOP		0x00
#घोषणा I2O_CMD_UTIL_ABORT		0x01
#घोषणा I2O_CMD_UTIL_CLAIM		0x09
#घोषणा I2O_CMD_UTIL_RELEASE		0x0B
#घोषणा I2O_CMD_UTIL_PARAMS_GET		0x06
#घोषणा I2O_CMD_UTIL_PARAMS_SET		0x05
#घोषणा I2O_CMD_UTIL_EVT_REGISTER	0x13
#घोषणा I2O_CMD_UTIL_EVT_ACK		0x14
#घोषणा I2O_CMD_UTIL_CONFIG_DIALOG	0x10
#घोषणा I2O_CMD_UTIL_DEVICE_RESERVE	0x0D
#घोषणा I2O_CMD_UTIL_DEVICE_RELEASE	0x0F
#घोषणा I2O_CMD_UTIL_LOCK		0x17
#घोषणा I2O_CMD_UTIL_LOCK_RELEASE	0x19
#घोषणा I2O_CMD_UTIL_REPLY_FAULT_NOTIFY	0x15

#घोषणा I2O_CMD_SCSI_EXEC		0x81
#घोषणा I2O_CMD_SCSI_ABORT		0x83
#घोषणा I2O_CMD_SCSI_BUSRESET		0x27

#घोषणा I2O_CMD_BLOCK_READ		0x30
#घोषणा I2O_CMD_BLOCK_WRITE		0x31
#घोषणा I2O_CMD_BLOCK_CFLUSH		0x37
#घोषणा I2O_CMD_BLOCK_MLOCK		0x49
#घोषणा I2O_CMD_BLOCK_MUNLOCK		0x4B
#घोषणा I2O_CMD_BLOCK_MMOUNT		0x41
#घोषणा I2O_CMD_BLOCK_MEJECT		0x43

#घोषणा I2O_PRIVATE_MSG			0xFF

/*
 *	Init Outbound Q status
 */

#घोषणा I2O_CMD_OUTBOUND_INIT_IN_PROGRESS	0x01
#घोषणा I2O_CMD_OUTBOUND_INIT_REJECTED		0x02
#घोषणा I2O_CMD_OUTBOUND_INIT_FAILED		0x03
#घोषणा I2O_CMD_OUTBOUND_INIT_COMPLETE		0x04

/*
 *	I2O Get Status State values
 */

#घोषणा	ADAPTER_STATE_INITIALIZING		0x01
#घोषणा	ADAPTER_STATE_RESET			0x02
#घोषणा	ADAPTER_STATE_HOLD			0x04
#घोषणा ADAPTER_STATE_READY			0x05
#घोषणा	ADAPTER_STATE_OPERATIONAL		0x08
#घोषणा	ADAPTER_STATE_FAILED			0x10
#घोषणा	ADAPTER_STATE_FAULTED			0x11

/* I2O API function वापस values */

#घोषणा I2O_RTN_NO_ERROR			0
#घोषणा I2O_RTN_NOT_INIT			1
#घोषणा I2O_RTN_FREE_Q_EMPTY			2
#घोषणा I2O_RTN_TCB_ERROR			3
#घोषणा I2O_RTN_TRANSACTION_ERROR		4
#घोषणा I2O_RTN_ADAPTER_ALREADY_INIT		5
#घोषणा I2O_RTN_MALLOC_ERROR			6
#घोषणा I2O_RTN_ADPTR_NOT_REGISTERED		7
#घोषणा I2O_RTN_MSG_REPLY_TIMEOUT		8
#घोषणा I2O_RTN_NO_STATUS			9
#घोषणा I2O_RTN_NO_FIRM_VER			10
#घोषणा	I2O_RTN_NO_LINK_SPEED			11

/* Reply message status defines क्रम all messages */

#घोषणा I2O_REPLY_STATUS_SUCCESS			0x00
#घोषणा I2O_REPLY_STATUS_ABORT_सूचीTY			0x01
#घोषणा I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER		0x02
#घोषणा	I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER		0x03
#घोषणा	I2O_REPLY_STATUS_ERROR_सूचीTY			0x04
#घोषणा	I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER		0x05
#घोषणा	I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER		0x06
#घोषणा	I2O_REPLY_STATUS_PROCESS_ABORT_सूचीTY		0x08
#घोषणा	I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER	0x09
#घोषणा	I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER	0x0A
#घोषणा	I2O_REPLY_STATUS_TRANSACTION_ERROR		0x0B
#घोषणा	I2O_REPLY_STATUS_PROGRESS_REPORT		0x80

/* Status codes and Error Inक्रमmation क्रम Parameter functions */

#घोषणा I2O_PARAMS_STATUS_SUCCESS		0x00
#घोषणा I2O_PARAMS_STATUS_BAD_KEY_ABORT		0x01
#घोषणा I2O_PARAMS_STATUS_BAD_KEY_CONTINUE	0x02
#घोषणा I2O_PARAMS_STATUS_BUFFER_FULL		0x03
#घोषणा I2O_PARAMS_STATUS_BUFFER_TOO_SMALL	0x04
#घोषणा I2O_PARAMS_STATUS_FIELD_UNREADABLE	0x05
#घोषणा I2O_PARAMS_STATUS_FIELD_UNWRITEABLE	0x06
#घोषणा I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS	0x07
#घोषणा I2O_PARAMS_STATUS_INVALID_GROUP_ID	0x08
#घोषणा I2O_PARAMS_STATUS_INVALID_OPERATION	0x09
#घोषणा I2O_PARAMS_STATUS_NO_KEY_FIELD		0x0A
#घोषणा I2O_PARAMS_STATUS_NO_SUCH_FIELD		0x0B
#घोषणा I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP	0x0C
#घोषणा I2O_PARAMS_STATUS_OPERATION_ERROR	0x0D
#घोषणा I2O_PARAMS_STATUS_SCALAR_ERROR		0x0E
#घोषणा I2O_PARAMS_STATUS_TABLE_ERROR		0x0F
#घोषणा I2O_PARAMS_STATUS_WRONG_GROUP_TYPE	0x10

/* DetailedStatusCode defines क्रम Executive, DDM, Util and Transaction error
 * messages: Table 3-2 Detailed Status Codes.*/

#घोषणा I2O_DSC_SUCCESS                        0x0000
#घोषणा I2O_DSC_BAD_KEY                        0x0002
#घोषणा I2O_DSC_TCL_ERROR                      0x0003
#घोषणा I2O_DSC_REPLY_BUFFER_FULL              0x0004
#घोषणा I2O_DSC_NO_SUCH_PAGE                   0x0005
#घोषणा I2O_DSC_INSUFFICIENT_RESOURCE_SOFT     0x0006
#घोषणा I2O_DSC_INSUFFICIENT_RESOURCE_HARD     0x0007
#घोषणा I2O_DSC_CHAIN_BUFFER_TOO_LARGE         0x0009
#घोषणा I2O_DSC_UNSUPPORTED_FUNCTION           0x000A
#घोषणा I2O_DSC_DEVICE_LOCKED                  0x000B
#घोषणा I2O_DSC_DEVICE_RESET                   0x000C
#घोषणा I2O_DSC_INAPPROPRIATE_FUNCTION         0x000D
#घोषणा I2O_DSC_INVALID_INITIATOR_ADDRESS      0x000E
#घोषणा I2O_DSC_INVALID_MESSAGE_FLAGS          0x000F
#घोषणा I2O_DSC_INVALID_OFFSET                 0x0010
#घोषणा I2O_DSC_INVALID_PARAMETER              0x0011
#घोषणा I2O_DSC_INVALID_REQUEST                0x0012
#घोषणा I2O_DSC_INVALID_TARGET_ADDRESS         0x0013
#घोषणा I2O_DSC_MESSAGE_TOO_LARGE              0x0014
#घोषणा I2O_DSC_MESSAGE_TOO_SMALL              0x0015
#घोषणा I2O_DSC_MISSING_PARAMETER              0x0016
#घोषणा I2O_DSC_TIMEOUT                        0x0017
#घोषणा I2O_DSC_UNKNOWN_ERROR                  0x0018
#घोषणा I2O_DSC_UNKNOWN_FUNCTION               0x0019
#घोषणा I2O_DSC_UNSUPPORTED_VERSION            0x001A
#घोषणा I2O_DSC_DEVICE_BUSY                    0x001B
#घोषणा I2O_DSC_DEVICE_NOT_AVAILABLE           0x001C

/* Device Claim Types */
#घोषणा	I2O_CLAIM_PRIMARY					0x01000000
#घोषणा	I2O_CLAIM_MANAGEMENT					0x02000000
#घोषणा	I2O_CLAIM_AUTHORIZED					0x03000000
#घोषणा	I2O_CLAIM_SECONDARY					0x04000000

/* Message header defines क्रम VersionOffset */
#घोषणा I2OVER15	0x0001
#घोषणा I2OVER20	0x0002
/* Default is 1.5, FIXME: Need support क्रम both 1.5 and 2.0 */
#घोषणा I2OVERSION	I2OVER15
#घोषणा SGL_OFFSET_0    I2OVERSION
#घोषणा SGL_OFFSET_4    (0x0040 | I2OVERSION)
#घोषणा SGL_OFFSET_5    (0x0050 | I2OVERSION)
#घोषणा SGL_OFFSET_6    (0x0060 | I2OVERSION)
#घोषणा SGL_OFFSET_7    (0x0070 | I2OVERSION)
#घोषणा SGL_OFFSET_8    (0x0080 | I2OVERSION)
#घोषणा SGL_OFFSET_9    (0x0090 | I2OVERSION)
#घोषणा SGL_OFFSET_10   (0x00A0 | I2OVERSION)
#घोषणा SGL_OFFSET_12   (0x00C0 | I2OVERSION)

#घोषणा TRL_OFFSET_5    (0x0050 | I2OVERSION)
#घोषणा TRL_OFFSET_6    (0x0060 | I2OVERSION)

 /* msg header defines क्रम MsgFlags */
#घोषणा MSG_STATIC	0x0100
#घोषणा MSG_64BIT_CNTXT	0x0200
#घोषणा MSG_MULTI_TRANS	0x1000
#घोषणा MSG_FAIL	0x2000
#घोषणा MSG_LAST	0x4000
#घोषणा MSG_REPLY	0x8000

 /* minimum size msg */
#घोषणा THREE_WORD_MSG_SIZE	0x00030000
#घोषणा FOUR_WORD_MSG_SIZE	0x00040000
#घोषणा FIVE_WORD_MSG_SIZE	0x00050000
#घोषणा SIX_WORD_MSG_SIZE	0x00060000
#घोषणा SEVEN_WORD_MSG_SIZE	0x00070000
#घोषणा EIGHT_WORD_MSG_SIZE	0x00080000
#घोषणा NINE_WORD_MSG_SIZE	0x00090000
#घोषणा TEN_WORD_MSG_SIZE	0x000A0000
#घोषणा I2O_MESSAGE_SIZE(x)	((x)<<16)


/* Special TID Assignments */

#घोषणा ADAPTER_TID		0
#घोषणा HOST_TID		1

#घोषणा MSG_FRAME_SIZE		128
#घोषणा NMBR_MSG_FRAMES		128

#घोषणा MSG_POOL_SIZE		16384

#घोषणा I2O_POST_WAIT_OK	0
#घोषणा I2O_POST_WAIT_TIMEOUT	-ETIMEDOUT


#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _SCSI_I2O_H */
