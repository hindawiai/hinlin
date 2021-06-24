<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * I2O user space accessible काष्ठाures/APIs
 *
 * (c) Copyright 1999, 2000 Red Hat Software
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 *************************************************************************
 *
 * This header file defines the I2O APIs that are available to both
 * the kernel and user level applications.  Kernel specअगरic काष्ठाures
 * are defined in i2o_osm. OSMs should include _only_ i2o_osm.h which
 * स्वतःmatically includes this file.
 *
 */

#अगर_अघोषित _I2O_DEV_H
#घोषणा _I2O_DEV_H

/* How many controllers are we allowing */
#घोषणा MAX_I2O_CONTROLLERS	32

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/*
 * I2O Control IOCTLs and काष्ठाures
 */
#घोषणा I2O_MAGIC_NUMBER	'i'
#घोषणा I2OGETIOPS		_IOR(I2O_MAGIC_NUMBER,0,__u8[MAX_I2O_CONTROLLERS])
#घोषणा I2OHRTGET		_IOWR(I2O_MAGIC_NUMBER,1,काष्ठा i2o_cmd_hrtlct)
#घोषणा I2OLCTGET		_IOWR(I2O_MAGIC_NUMBER,2,काष्ठा i2o_cmd_hrtlct)
#घोषणा I2OPARMSET		_IOWR(I2O_MAGIC_NUMBER,3,काष्ठा i2o_cmd_psetget)
#घोषणा I2OPARMGET		_IOWR(I2O_MAGIC_NUMBER,4,काष्ठा i2o_cmd_psetget)
#घोषणा I2OSWDL 		_IOWR(I2O_MAGIC_NUMBER,5,काष्ठा i2o_sw_xfer)
#घोषणा I2OSWUL 		_IOWR(I2O_MAGIC_NUMBER,6,काष्ठा i2o_sw_xfer)
#घोषणा I2OSWDEL		_IOWR(I2O_MAGIC_NUMBER,7,काष्ठा i2o_sw_xfer)
#घोषणा I2OVALIDATE		_IOR(I2O_MAGIC_NUMBER,8,__u32)
#घोषणा I2OHTML 		_IOWR(I2O_MAGIC_NUMBER,9,काष्ठा i2o_hपंचांगl)
#घोषणा I2OEVTREG		_IOW(I2O_MAGIC_NUMBER,10,काष्ठा i2o_evt_id)
#घोषणा I2OEVTGET		_IOR(I2O_MAGIC_NUMBER,11,काष्ठा i2o_evt_info)
#घोषणा I2OPASSTHRU		_IOR(I2O_MAGIC_NUMBER,12,काष्ठा i2o_cmd_passthru)
#घोषणा I2OPASSTHRU32		_IOR(I2O_MAGIC_NUMBER,12,काष्ठा i2o_cmd_passthru32)

काष्ठा i2o_cmd_passthru32 अणु
	अचिन्हित पूर्णांक iop;	/* IOP unit number */
	__u32 msg;		/* message */
पूर्ण;

काष्ठा i2o_cmd_passthru अणु
	अचिन्हित पूर्णांक iop;	/* IOP unit number */
	व्योम __user *msg;	/* message */
पूर्ण;

काष्ठा i2o_cmd_hrtlct अणु
	अचिन्हित पूर्णांक iop;	/* IOP unit number */
	व्योम __user *resbuf;	/* Buffer क्रम result */
	अचिन्हित पूर्णांक __user *reslen;	/* Buffer length in bytes */
पूर्ण;

काष्ठा i2o_cmd_psetget अणु
	अचिन्हित पूर्णांक iop;	/* IOP unit number */
	अचिन्हित पूर्णांक tid;	/* Target device TID */
	व्योम __user *opbuf;	/* Operation List buffer */
	अचिन्हित पूर्णांक oplen;	/* Operation List buffer length in bytes */
	व्योम __user *resbuf;	/* Result List buffer */
	अचिन्हित पूर्णांक __user *reslen;	/* Result List buffer length in bytes */
पूर्ण;

काष्ठा i2o_sw_xfer अणु
	अचिन्हित पूर्णांक iop;	/* IOP unit number */
	अचिन्हित अक्षर flags;	/* Flags field */
	अचिन्हित अक्षर sw_type;	/* Software type */
	अचिन्हित पूर्णांक sw_id;	/* Software ID */
	व्योम __user *buf;	/* Poपूर्णांकer to software buffer */
	अचिन्हित पूर्णांक __user *swlen;	/* Length of software data */
	अचिन्हित पूर्णांक __user *maxfrag;	/* Maximum fragment count */
	अचिन्हित पूर्णांक __user *curfrag;	/* Current fragment count */
पूर्ण;

काष्ठा i2o_hपंचांगl अणु
	अचिन्हित पूर्णांक iop;	/* IOP unit number */
	अचिन्हित पूर्णांक tid;	/* Target device ID */
	अचिन्हित पूर्णांक page;	/* HTML page */
	व्योम __user *resbuf;	/* Buffer क्रम reply HTML page */
	अचिन्हित पूर्णांक __user *reslen;	/* Length in bytes of reply buffer */
	व्योम __user *qbuf;	/* Poपूर्णांकer to HTTP query string */
	अचिन्हित पूर्णांक qlen;	/* Length in bytes of query string buffer */
पूर्ण;

#घोषणा I2O_EVT_Q_LEN 32

काष्ठा i2o_evt_id अणु
	अचिन्हित पूर्णांक iop;
	अचिन्हित पूर्णांक tid;
	अचिन्हित पूर्णांक evt_mask;
पूर्ण;

/* Event data size = frame size - message header + evt indicator */
#घोषणा I2O_EVT_DATA_SIZE 88

काष्ठा i2o_evt_info अणु
	काष्ठा i2o_evt_id id;
	अचिन्हित अक्षर evt_data[I2O_EVT_DATA_SIZE];
	अचिन्हित पूर्णांक data_size;
पूर्ण;

काष्ठा i2o_evt_get अणु
	काष्ठा i2o_evt_info info;
	पूर्णांक pending;
	पूर्णांक lost;
पूर्ण;

प्रकार काष्ठा i2o_sg_io_hdr अणु
	अचिन्हित पूर्णांक flags;	/* see I2O_DPT_SG_IO_FLAGS */
पूर्ण i2o_sg_io_hdr_t;

/**************************************************************************
 * HRT related स्थिरants and काष्ठाures
 **************************************************************************/
#घोषणा I2O_BUS_LOCAL	0
#घोषणा I2O_BUS_ISA	1
#घोषणा I2O_BUS_EISA	2
/* was  I2O_BUS_MCA	3 */
#घोषणा I2O_BUS_PCI	4
#घोषणा I2O_BUS_PCMCIA	5
#घोषणा I2O_BUS_NUBUS	6
#घोषणा I2O_BUS_CARDBUS 7
#घोषणा I2O_BUS_UNKNOWN 0x80

प्रकार काष्ठा _i2o_pci_bus अणु
	__u8 PciFunctionNumber;
	__u8 PciDeviceNumber;
	__u8 PciBusNumber;
	__u8 reserved;
	__u16 PciVenकरोrID;
	__u16 PciDeviceID;
पूर्ण i2o_pci_bus;

प्रकार काष्ठा _i2o_local_bus अणु
	__u16 LbBaseIOPort;
	__u16 reserved;
	__u32 LbBaseMemoryAddress;
पूर्ण i2o_local_bus;

प्रकार काष्ठा _i2o_isa_bus अणु
	__u16 IsaBaseIOPort;
	__u8 CSN;
	__u8 reserved;
	__u32 IsaBaseMemoryAddress;
पूर्ण i2o_isa_bus;

प्रकार काष्ठा _i2o_eisa_bus_info अणु
	__u16 EisaBaseIOPort;
	__u8 reserved;
	__u8 EisaSlotNumber;
	__u32 EisaBaseMemoryAddress;
पूर्ण i2o_eisa_bus;

प्रकार काष्ठा _i2o_mca_bus अणु
	__u16 McaBaseIOPort;
	__u8 reserved;
	__u8 McaSlotNumber;
	__u32 McaBaseMemoryAddress;
पूर्ण i2o_mca_bus;

प्रकार काष्ठा _i2o_other_bus अणु
	__u16 BaseIOPort;
	__u16 reserved;
	__u32 BaseMemoryAddress;
पूर्ण i2o_other_bus;

प्रकार काष्ठा _i2o_hrt_entry अणु
	__u32 adapter_id;
	__u32 parent_tid:12;
	__u32 state:4;
	__u32 bus_num:8;
	__u32 bus_type:8;
	जोड़ अणु
		i2o_pci_bus pci_bus;
		i2o_local_bus local_bus;
		i2o_isa_bus isa_bus;
		i2o_eisa_bus eisa_bus;
		i2o_mca_bus mca_bus;
		i2o_other_bus other_bus;
	पूर्ण bus;
पूर्ण i2o_hrt_entry;

प्रकार काष्ठा _i2o_hrt अणु
	__u16 num_entries;
	__u8 entry_len;
	__u8 hrt_version;
	__u32 change_ind;
	i2o_hrt_entry hrt_entry[1];
पूर्ण i2o_hrt;

प्रकार काष्ठा _i2o_lct_entry अणु
	__u32 entry_size:16;
	__u32 tid:12;
	__u32 reserved:4;
	__u32 change_ind;
	__u32 device_flags;
	__u32 class_id:12;
	__u32 version:4;
	__u32 venकरोr_id:16;
	__u32 sub_class;
	__u32 user_tid:12;
	__u32 parent_tid:12;
	__u32 bios_info:8;
	__u8 identity_tag[8];
	__u32 event_capabilities;
पूर्ण i2o_lct_entry;

प्रकार काष्ठा _i2o_lct अणु
	__u32 table_size:16;
	__u32 boot_tid:12;
	__u32 lct_ver:4;
	__u32 iop_flags;
	__u32 change_ind;
	i2o_lct_entry lct_entry[1];
पूर्ण i2o_lct;

प्रकार काष्ठा _i2o_status_block अणु
	__u16 org_id;
	__u16 reserved;
	__u16 iop_id:12;
	__u16 reserved1:4;
	__u16 host_unit_id;
	__u16 segment_number:12;
	__u16 i2o_version:4;
	__u8 iop_state;
	__u8 msg_type;
	__u16 inbound_frame_size;
	__u8 init_code;
	__u8 reserved2;
	__u32 max_inbound_frames;
	__u32 cur_inbound_frames;
	__u32 max_outbound_frames;
	अक्षर product_id[24];
	__u32 expected_lct_size;
	__u32 iop_capabilities;
	__u32 desired_mem_size;
	__u32 current_mem_size;
	__u32 current_mem_base;
	__u32 desired_io_size;
	__u32 current_io_size;
	__u32 current_io_base;
	__u32 reserved3:24;
	__u32 cmd_status:8;
पूर्ण i2o_status_block;

/* Event indicator mask flags */
#घोषणा I2O_EVT_IND_STATE_CHANGE		0x80000000
#घोषणा I2O_EVT_IND_GENERAL_WARNING		0x40000000
#घोषणा I2O_EVT_IND_CONFIGURATION_FLAG		0x20000000
#घोषणा I2O_EVT_IND_LOCK_RELEASE		0x10000000
#घोषणा I2O_EVT_IND_CAPABILITY_CHANGE		0x08000000
#घोषणा I2O_EVT_IND_DEVICE_RESET		0x04000000
#घोषणा I2O_EVT_IND_EVT_MASK_MODIFIED		0x02000000
#घोषणा I2O_EVT_IND_FIELD_MODIFIED		0x01000000
#घोषणा I2O_EVT_IND_VENDOR_EVT			0x00800000
#घोषणा I2O_EVT_IND_DEVICE_STATE		0x00400000

/* Executive event indicitors */
#घोषणा I2O_EVT_IND_EXEC_RESOURCE_LIMITS	0x00000001
#घोषणा I2O_EVT_IND_EXEC_CONNECTION_FAIL	0x00000002
#घोषणा I2O_EVT_IND_EXEC_ADAPTER_FAULT		0x00000004
#घोषणा I2O_EVT_IND_EXEC_POWER_FAIL		0x00000008
#घोषणा I2O_EVT_IND_EXEC_RESET_PENDING		0x00000010
#घोषणा I2O_EVT_IND_EXEC_RESET_IMMINENT 	0x00000020
#घोषणा I2O_EVT_IND_EXEC_HW_FAIL		0x00000040
#घोषणा I2O_EVT_IND_EXEC_XCT_CHANGE		0x00000080
#घोषणा I2O_EVT_IND_EXEC_NEW_LCT_ENTRY		0x00000100
#घोषणा I2O_EVT_IND_EXEC_MODIFIED_LCT		0x00000200
#घोषणा I2O_EVT_IND_EXEC_DDM_AVAILABILITY	0x00000400

/* Ranकरोm Block Storage Event Indicators */
#घोषणा I2O_EVT_IND_BSA_VOLUME_LOAD		0x00000001
#घोषणा I2O_EVT_IND_BSA_VOLUME_UNLOAD		0x00000002
#घोषणा I2O_EVT_IND_BSA_VOLUME_UNLOAD_REQ	0x00000004
#घोषणा I2O_EVT_IND_BSA_CAPACITY_CHANGE 	0x00000008
#घोषणा I2O_EVT_IND_BSA_SCSI_SMART		0x00000010

/* Event data क्रम generic events */
#घोषणा I2O_EVT_STATE_CHANGE_NORMAL		0x00
#घोषणा I2O_EVT_STATE_CHANGE_SUSPENDED		0x01
#घोषणा I2O_EVT_STATE_CHANGE_RESTART		0x02
#घोषणा I2O_EVT_STATE_CHANGE_NA_RECOVER 	0x03
#घोषणा I2O_EVT_STATE_CHANGE_NA_NO_RECOVER	0x04
#घोषणा I2O_EVT_STATE_CHANGE_QUIESCE_REQUEST	0x05
#घोषणा I2O_EVT_STATE_CHANGE_FAILED		0x10
#घोषणा I2O_EVT_STATE_CHANGE_FAULTED		0x11

#घोषणा I2O_EVT_GEN_WARNING_NORMAL		0x00
#घोषणा I2O_EVT_GEN_WARNING_ERROR_THRESHOLD	0x01
#घोषणा I2O_EVT_GEN_WARNING_MEDIA_FAULT 	0x02

#घोषणा I2O_EVT_CAPABILITY_OTHER		0x01
#घोषणा I2O_EVT_CAPABILITY_CHANGED		0x02

#घोषणा I2O_EVT_SENSOR_STATE_CHANGED		0x01

/*
 *	I2O classes / subclasses
 */

/*  Class ID and Code Assignments
 *  (LCT.ClassID.Version field)
 */
#घोषणा I2O_CLASS_VERSION_10			0x00
#घोषणा I2O_CLASS_VERSION_11			0x01

/*  Class code names
 *  (from v1.5 Table 6-1 Class Code Assignments.)
 */

#घोषणा I2O_CLASS_EXECUTIVE			0x000
#घोषणा I2O_CLASS_DDM				0x001
#घोषणा I2O_CLASS_RANDOM_BLOCK_STORAGE		0x010
#घोषणा I2O_CLASS_SEQUENTIAL_STORAGE		0x011
#घोषणा I2O_CLASS_LAN				0x020
#घोषणा I2O_CLASS_WAN				0x030
#घोषणा I2O_CLASS_FIBRE_CHANNEL_PORT		0x040
#घोषणा I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL	0x041
#घोषणा I2O_CLASS_SCSI_PERIPHERAL		0x051
#घोषणा I2O_CLASS_ATE_PORT			0x060
#घोषणा I2O_CLASS_ATE_PERIPHERAL		0x061
#घोषणा I2O_CLASS_FLOPPY_CONTROLLER		0x070
#घोषणा I2O_CLASS_FLOPPY_DEVICE 		0x071
#घोषणा I2O_CLASS_BUS_ADAPTER			0x080
#घोषणा I2O_CLASS_PEER_TRANSPORT_AGENT		0x090
#घोषणा I2O_CLASS_PEER_TRANSPORT		0x091
#घोषणा	I2O_CLASS_END				0xfff

/*
 *  Rest of 0x092 - 0x09f reserved क्रम peer-to-peer classes
 */

#घोषणा I2O_CLASS_MATCH_ANYCLASS		0xffffffff

/*
 *  Subclasses
 */

#घोषणा I2O_SUBCLASS_i960			0x001
#घोषणा I2O_SUBCLASS_HDM			0x020
#घोषणा I2O_SUBCLASS_ISM			0x021

/* Operation functions */

#घोषणा I2O_PARAMS_FIELD_GET			0x0001
#घोषणा I2O_PARAMS_LIST_GET			0x0002
#घोषणा I2O_PARAMS_MORE_GET			0x0003
#घोषणा I2O_PARAMS_SIZE_GET			0x0004
#घोषणा I2O_PARAMS_TABLE_GET			0x0005
#घोषणा I2O_PARAMS_FIELD_SET			0x0006
#घोषणा I2O_PARAMS_LIST_SET			0x0007
#घोषणा I2O_PARAMS_ROW_ADD			0x0008
#घोषणा I2O_PARAMS_ROW_DELETE			0x0009
#घोषणा I2O_PARAMS_TABLE_CLEAR			0x000A

/*
 * I2O serial number conventions / क्रमmats
 * (circa v1.5)
 */

#घोषणा I2O_SNFORMAT_UNKNOWN			0
#घोषणा I2O_SNFORMAT_BINARY			1
#घोषणा I2O_SNFORMAT_ASCII			2
#घोषणा I2O_SNFORMAT_UNICODE			3
#घोषणा I2O_SNFORMAT_LAN48_MAC			4
#घोषणा I2O_SNFORMAT_WAN			5

/*
 * Plus new in v2.0 (Yellowstone pdf करोc)
 */

#घोषणा I2O_SNFORMAT_LAN64_MAC			6
#घोषणा I2O_SNFORMAT_DDM			7
#घोषणा I2O_SNFORMAT_IEEE_REG64 		8
#घोषणा I2O_SNFORMAT_IEEE_REG128		9
#घोषणा I2O_SNFORMAT_UNKNOWN2			0xff

/*
 *	I2O Get Status State values
 */

#घोषणा ADAPTER_STATE_INITIALIZING		0x01
#घोषणा ADAPTER_STATE_RESET			0x02
#घोषणा ADAPTER_STATE_HOLD			0x04
#घोषणा ADAPTER_STATE_READY			0x05
#घोषणा ADAPTER_STATE_OPERATIONAL		0x08
#घोषणा ADAPTER_STATE_FAILED			0x10
#घोषणा ADAPTER_STATE_FAULTED			0x11

/*
 *	Software module types
 */
#घोषणा I2O_SOFTWARE_MODULE_IRTOS		0x11
#घोषणा I2O_SOFTWARE_MODULE_IOP_PRIVATE		0x22
#घोषणा I2O_SOFTWARE_MODULE_IOP_CONFIG		0x23

/*
 *	Venकरोrs
 */
#घोषणा I2O_VENDOR_DPT				0x001b

/*
 * DPT / Adaptec specअगरic values क्रम i2o_sg_io_hdr flags.
 */
#घोषणा I2O_DPT_SG_FLAG_INTERPRET		0x00010000
#घोषणा I2O_DPT_SG_FLAG_PHYSICAL		0x00020000

#घोषणा I2O_DPT_FLASH_FRAG_SIZE			0x10000
#घोषणा I2O_DPT_FLASH_READ			0x0101
#घोषणा I2O_DPT_FLASH_WRITE			0x0102

#पूर्ण_अगर				/* _I2O_DEV_H */
