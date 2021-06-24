<शैली गुरु>
/*
 *    Disk Array driver क्रम HP Smart Array SAS controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright 2016 Microsemi Corporation
 *    Copyright 2014-2015 PMC-Sierra, Inc.
 *    Copyright 2000,2009-2015 Hewlett-Packard Development Company, L.P.
 *
 *    This program is मुक्त software; you can redistribute it and/or modअगरy
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; version 2 of the License.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 *    NON INFRINGEMENT.  See the GNU General Public License क्रम more details.
 *
 *    Questions/Comments/Bugfixes to esc.storagedev@microsemi.com
 *
 */
#अगर_अघोषित HPSA_CMD_H
#घोषणा HPSA_CMD_H

#समावेश <linux/compiler.h>

#समावेश <linux/build_bug.h> /* अटल_निश्चित */
#समावेश <linux/मानकघोष.स> /* दुरत्व */

/* general boundary defपूर्णांकions */
#घोषणा SENSEINFOBYTES          32 /* may vary between hbas */
#घोषणा SG_ENTRIES_IN_CMD	32 /* Max SG entries excluding chain blocks */
#घोषणा HPSA_SG_CHAIN		0x80000000
#घोषणा HPSA_SG_LAST		0x40000000
#घोषणा MAXREPLYQS              256

/* Command Status value */
#घोषणा CMD_SUCCESS             0x0000
#घोषणा CMD_TARGET_STATUS       0x0001
#घोषणा CMD_DATA_UNDERRUN       0x0002
#घोषणा CMD_DATA_OVERRUN        0x0003
#घोषणा CMD_INVALID             0x0004
#घोषणा CMD_PROTOCOL_ERR        0x0005
#घोषणा CMD_HARDWARE_ERR        0x0006
#घोषणा CMD_CONNECTION_LOST     0x0007
#घोषणा CMD_ABORTED             0x0008
#घोषणा CMD_ABORT_FAILED        0x0009
#घोषणा CMD_UNSOLICITED_ABORT   0x000A
#घोषणा CMD_TIMEOUT             0x000B
#घोषणा CMD_UNABORTABLE		0x000C
#घोषणा CMD_TMF_STATUS		0x000D
#घोषणा CMD_IOACCEL_DISABLED	0x000E
#घोषणा CMD_CTLR_LOCKUP		0xffff
/* Note: CMD_CTLR_LOCKUP is not a value defined by the CISS spec
 * it is a value defined by the driver that commands can be marked
 * with when a controller lockup has been detected by the driver
 */

/* TMF function status values */
#घोषणा CISS_TMF_COMPLETE	0x00
#घोषणा CISS_TMF_INVALID_FRAME	0x02
#घोषणा CISS_TMF_NOT_SUPPORTED	0x04
#घोषणा CISS_TMF_FAILED		0x05
#घोषणा CISS_TMF_SUCCESS	0x08
#घोषणा CISS_TMF_WRONG_LUN	0x09
#घोषणा CISS_TMF_OVERLAPPED_TAG 0x0a

/* Unit Attentions ASC's as defined क्रम the MSA2012sa */
#घोषणा POWER_OR_RESET			0x29
#घोषणा STATE_CHANGED			0x2a
#घोषणा UNIT_ATTENTION_CLEARED		0x2f
#घोषणा LUN_FAILED			0x3e
#घोषणा REPORT_LUNS_CHANGED		0x3f

/* Unit Attentions ASCQ's as defined क्रम the MSA2012sa */

	/* These ASCQ's defined क्रम ASC = POWER_OR_RESET */
#घोषणा POWER_ON_RESET			0x00
#घोषणा POWER_ON_REBOOT			0x01
#घोषणा SCSI_BUS_RESET			0x02
#घोषणा MSA_TARGET_RESET		0x03
#घोषणा CONTROLLER_FAILOVER		0x04
#घोषणा TRANSCEIVER_SE			0x05
#घोषणा TRANSCEIVER_LVD			0x06

	/* These ASCQ's defined क्रम ASC = STATE_CHANGED */
#घोषणा RESERVATION_PREEMPTED		0x03
#घोषणा ASYM_ACCESS_CHANGED		0x06
#घोषणा LUN_CAPACITY_CHANGED		0x09

/* transfer direction */
#घोषणा XFER_NONE               0x00
#घोषणा XFER_WRITE              0x01
#घोषणा XFER_READ               0x02
#घोषणा XFER_RSVD               0x03

/* task attribute */
#घोषणा ATTR_UNTAGGED           0x00
#घोषणा ATTR_SIMPLE             0x04
#घोषणा ATTR_HEADOFQUEUE        0x05
#घोषणा ATTR_ORDERED            0x06
#घोषणा ATTR_ACA                0x07

/* cdb type */
#घोषणा TYPE_CMD		0x00
#घोषणा TYPE_MSG		0x01
#घोषणा TYPE_IOACCEL2_CMD	0x81 /* 0x81 is not used by hardware */

/* Message Types  */
#घोषणा HPSA_TASK_MANAGEMENT    0x00
#घोषणा HPSA_RESET              0x01
#घोषणा HPSA_SCAN               0x02
#घोषणा HPSA_NOOP               0x03

#घोषणा HPSA_CTLR_RESET_TYPE    0x00
#घोषणा HPSA_BUS_RESET_TYPE     0x01
#घोषणा HPSA_TARGET_RESET_TYPE  0x03
#घोषणा HPSA_LUN_RESET_TYPE     0x04
#घोषणा HPSA_NEXUS_RESET_TYPE   0x05

/* Task Management Functions */
#घोषणा HPSA_TMF_ABORT_TASK     0x00
#घोषणा HPSA_TMF_ABORT_TASK_SET 0x01
#घोषणा HPSA_TMF_CLEAR_ACA      0x02
#घोषणा HPSA_TMF_CLEAR_TASK_SET 0x03
#घोषणा HPSA_TMF_QUERY_TASK     0x04
#घोषणा HPSA_TMF_QUERY_TASK_SET 0x05
#घोषणा HPSA_TMF_QUERY_ASYNCEVENT 0x06



/* config space रेजिस्टर offsets */
#घोषणा CFG_VENDORID            0x00
#घोषणा CFG_DEVICEID            0x02
#घोषणा CFG_I2OBAR              0x10
#घोषणा CFG_MEM1BAR             0x14

/* i2o space रेजिस्टर offsets */
#घोषणा I2O_IBDB_SET            0x20
#घोषणा I2O_IBDB_CLEAR          0x70
#घोषणा I2O_INT_STATUS          0x30
#घोषणा I2O_INT_MASK            0x34
#घोषणा I2O_IBPOST_Q            0x40
#घोषणा I2O_OBPOST_Q            0x44
#घोषणा I2O_DMA1_CFG		0x214

/* Configuration Table */
#घोषणा CFGTBL_ChangeReq        0x00000001l
#घोषणा CFGTBL_AccCmds          0x00000001l
#घोषणा DOORBELL_CTLR_RESET	0x00000004l
#घोषणा DOORBELL_CTLR_RESET2	0x00000020l
#घोषणा DOORBELL_CLEAR_EVENTS	0x00000040l
#घोषणा DOORBELL_GENERATE_CHKPT	0x00000080l

#घोषणा CFGTBL_Trans_Simple     0x00000002l
#घोषणा CFGTBL_Trans_Perक्रमmant 0x00000004l
#घोषणा CFGTBL_Trans_io_accel1	0x00000080l
#घोषणा CFGTBL_Trans_io_accel2	0x00000100l
#घोषणा CFGTBL_Trans_use_लघु_tags 0x20000000l
#घोषणा CFGTBL_Trans_enable_directed_msix (1 << 30)

#घोषणा CFGTBL_BusType_Ultra2   0x00000001l
#घोषणा CFGTBL_BusType_Ultra3   0x00000002l
#घोषणा CFGTBL_BusType_Fibre1G  0x00000100l
#घोषणा CFGTBL_BusType_Fibre2G  0x00000200l

/* VPD Inquiry types */
#घोषणा HPSA_INQUIRY_FAILED		0x02
#घोषणा HPSA_VPD_SUPPORTED_PAGES        0x00
#घोषणा HPSA_VPD_LV_DEVICE_ID           0x83
#घोषणा HPSA_VPD_LV_DEVICE_GEOMETRY     0xC1
#घोषणा HPSA_VPD_LV_IOACCEL_STATUS      0xC2
#घोषणा HPSA_VPD_LV_STATUS		0xC3
#घोषणा HPSA_VPD_HEADER_SZ              4

/* Logical volume states */
#घोषणा HPSA_VPD_LV_STATUS_UNSUPPORTED			0xff
#घोषणा HPSA_LV_OK                                      0x0
#घोषणा HPSA_LV_FAILED					0x01
#घोषणा HPSA_LV_NOT_AVAILABLE				0x0b
#घोषणा HPSA_LV_UNDERGOING_ERASE			0x0F
#घोषणा HPSA_LV_UNDERGOING_RPI				0x12
#घोषणा HPSA_LV_PENDING_RPI				0x13
#घोषणा HPSA_LV_ENCRYPTED_NO_KEY			0x14
#घोषणा HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER	0x15
#घोषणा HPSA_LV_UNDERGOING_ENCRYPTION			0x16
#घोषणा HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING		0x17
#घोषणा HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER	0x18
#घोषणा HPSA_LV_PENDING_ENCRYPTION			0x19
#घोषणा HPSA_LV_PENDING_ENCRYPTION_REKEYING		0x1A

काष्ठा vals32 अणु
	u32   lower;
	u32   upper;
पूर्ण;

जोड़ u64bit अणु
	काष्ठा vals32 val32;
	u64 val;
पूर्ण;

/* FIXME this is a per controller value (barf!) */
#घोषणा HPSA_MAX_LUN 1024
#घोषणा HPSA_MAX_PHYS_LUN 1024
#घोषणा MAX_EXT_TARGETS 32
#घोषणा HPSA_MAX_DEVICES (HPSA_MAX_PHYS_LUN + HPSA_MAX_LUN + \
	MAX_EXT_TARGETS + 1) /* + 1 is क्रम the controller itself */

/* SCSI-3 Commands */
#घोषणा HPSA_INQUIRY 0x12
काष्ठा InquiryData अणु
	u8 data_byte[36];
पूर्ण __packed;

#घोषणा HPSA_REPORT_LOG 0xc2    /* Report Logical LUNs */
#घोषणा HPSA_REPORT_PHYS 0xc3   /* Report Physical LUNs */
#घोषणा HPSA_REPORT_PHYS_EXTENDED 0x02
#घोषणा HPSA_CISS_READ	0xc0	/* CISS Read */
#घोषणा HPSA_GET_RAID_MAP 0xc8	/* CISS Get RAID Layout Map */

#घोषणा RAID_MAP_MAX_ENTRIES   256

काष्ठा raid_map_disk_data अणु
	u32   ioaccel_handle;         /**< Handle to access this disk via the
					*  I/O accelerator */
	u8    xor_mult[2];            /**< XOR multipliers क्रम this position,
					*  valid क्रम data disks only */
	u8    reserved[2];
पूर्ण __packed;

काष्ठा raid_map_data अणु
	__le32   काष्ठाure_size;	/* Size of entire काष्ठाure in bytes */
	__le32   volume_blk_size;	/* bytes / block in the volume */
	__le64   volume_blk_cnt;	/* logical blocks on the volume */
	u8    phys_blk_shअगरt;		/* Shअगरt factor to convert between
					 * units of logical blocks and physical
					 * disk blocks */
	u8    parity_rotation_shअगरt;	/* Shअगरt factor to convert between units
					 * of logical stripes and physical
					 * stripes */
	__le16   strip_size;		/* blocks used on each disk / stripe */
	__le64   disk_starting_blk;	/* First disk block used in volume */
	__le64   disk_blk_cnt;		/* disk blocks used by volume / disk */
	__le16   data_disks_per_row;	/* data disk entries / row in the map */
	__le16   metadata_disks_per_row;/* mirror/parity disk entries / row
					 * in the map */
	__le16   row_cnt;		/* rows in each layout map */
	__le16   layout_map_count;	/* layout maps (1 map per mirror/parity
					 * group) */
	__le16   flags;			/* Bit 0 set अगर encryption enabled */
#घोषणा RAID_MAP_FLAG_ENCRYPT_ON  0x01
	__le16   dekindex;		/* Data encryption key index. */
	u8    reserved[16];
	काष्ठा raid_map_disk_data data[RAID_MAP_MAX_ENTRIES];
पूर्ण __packed;

काष्ठा ReportLUNdata अणु
	u8 LUNListLength[4];
	u8 extended_response_flag;
	u8 reserved[3];
	u8 LUN[HPSA_MAX_LUN][8];
पूर्ण __packed;

काष्ठा ext_report_lun_entry अणु
	u8 lunid[8];
#घोषणा MASKED_DEVICE(x) ((x)[3] & 0xC0)
#घोषणा GET_BMIC_BUS(lunid) ((lunid)[7] & 0x3F)
#घोषणा GET_BMIC_LEVEL_TWO_TARGET(lunid) ((lunid)[6])
#घोषणा GET_BMIC_DRIVE_NUMBER(lunid) (((GET_BMIC_BUS((lunid)) - 1) << 8) + \
			GET_BMIC_LEVEL_TWO_TARGET((lunid)))
	u8 wwid[8];
	u8 device_type;
	u8 device_flags;
	u8 lun_count; /* multi-lun device, how many luns */
	u8 redundant_paths;
	u32 ioaccel_handle; /* ioaccel1 only uses lower 16 bits */
पूर्ण __packed;

काष्ठा ReportExtendedLUNdata अणु
	u8 LUNListLength[4];
	u8 extended_response_flag;
	u8 reserved[3];
	काष्ठा ext_report_lun_entry LUN[HPSA_MAX_PHYS_LUN];
पूर्ण __packed;

काष्ठा SenseSubप्रणाली_info अणु
	u8 reserved[36];
	u8 portname[8];
	u8 reserved1[1108];
पूर्ण __packed;

/* BMIC commands */
#घोषणा BMIC_READ 0x26
#घोषणा BMIC_WRITE 0x27
#घोषणा BMIC_CACHE_FLUSH 0xc2
#घोषणा HPSA_CACHE_FLUSH 0x01	/* C2 was alपढ़ोy being used by HPSA */
#घोषणा BMIC_FLASH_FIRMWARE 0xF7
#घोषणा BMIC_SENSE_CONTROLLER_PARAMETERS 0x64
#घोषणा BMIC_IDENTIFY_PHYSICAL_DEVICE 0x15
#घोषणा BMIC_IDENTIFY_CONTROLLER 0x11
#घोषणा BMIC_SET_DIAG_OPTIONS 0xF4
#घोषणा BMIC_SENSE_DIAG_OPTIONS 0xF5
#घोषणा HPSA_DIAG_OPTS_DISABLE_RLD_CACHING 0x80000000
#घोषणा BMIC_SENSE_SUBSYSTEM_INFORMATION 0x66
#घोषणा BMIC_SENSE_STORAGE_BOX_PARAMS 0x65

/* Command List Structure */
जोड़ SCSI3Addr अणु
	काष्ठा अणु
		u8 Dev;
		u8 Bus:6;
		u8 Mode:2;        /* b00 */
	पूर्ण PeripDev;
	काष्ठा अणु
		u8 DevLSB;
		u8 DevMSB:6;
		u8 Mode:2;        /* b01 */
	पूर्ण LogDev;
	काष्ठा अणु
		u8 Dev:5;
		u8 Bus:3;
		u8 Targ:6;
		u8 Mode:2;        /* b10 */
	पूर्ण LogUnit;
पूर्ण __packed;

काष्ठा PhysDevAddr अणु
	u32             TargetId:24;
	u32             Bus:6;
	u32             Mode:2;
	/* 2 level target device addr */
	जोड़ SCSI3Addr  Target[2];
पूर्ण __packed;

काष्ठा LogDevAddr अणु
	u32            VolId:30;
	u32            Mode:2;
	u8             reserved[4];
पूर्ण __packed;

जोड़ LUNAddr अणु
	u8               LunAddrBytes[8];
	जोड़ SCSI3Addr    SCSI3Lun[4];
	काष्ठा PhysDevAddr PhysDev;
	काष्ठा LogDevAddr  LogDev;
पूर्ण __packed;

काष्ठा CommandListHeader अणु
	u8              ReplyQueue;
	u8              SGList;
	__le16          SGTotal;
	__le64		tag;
	जोड़ LUNAddr     LUN;
पूर्ण __packed;

काष्ठा RequestBlock अणु
	u8   CDBLen;
	/*
	 * type_attr_dir:
	 * type: low 3 bits
	 * attr: middle 3 bits
	 * dir: high 2 bits
	 */
	u8	type_attr_dir;
#घोषणा TYPE_ATTR_सूची(t, a, d) ((((d) & 0x03) << 6) |\
				(((a) & 0x07) << 3) |\
				((t) & 0x07))
#घोषणा GET_TYPE(tad) ((tad) & 0x07)
#घोषणा GET_ATTR(tad) (((tad) >> 3) & 0x07)
#घोषणा GET_सूची(tad) (((tad) >> 6) & 0x03)
	u16  Timeout;
	u8   CDB[16];
पूर्ण __packed;

काष्ठा ErrDescriptor अणु
	__le64 Addr;
	__le32 Len;
पूर्ण __packed;

काष्ठा SGDescriptor अणु
	__le64 Addr;
	__le32 Len;
	__le32 Ext;
पूर्ण __packed;

जोड़ MoreErrInfo अणु
	काष्ठा अणु
		u8  Reserved[3];
		u8  Type;
		u32 ErrorInfo;
	पूर्ण Common_Info;
	काष्ठा अणु
		u8  Reserved[2];
		u8  offense_size; /* size of offending entry */
		u8  offense_num;  /* byte # of offense 0-base */
		u32 offense_value;
	पूर्ण Invalid_Cmd;
पूर्ण __packed;

काष्ठा ErrorInfo अणु
	u8               ScsiStatus;
	u8               SenseLen;
	u16              CommandStatus;
	u32              ResidualCnt;
	जोड़ MoreErrInfo  MoreErrInfo;
	u8               SenseInfo[SENSEINFOBYTES];
पूर्ण __packed;
/* Command types */
#घोषणा CMD_IOCTL_PEND  0x01
#घोषणा CMD_SCSI	0x03
#घोषणा CMD_IOACCEL1	0x04
#घोषणा CMD_IOACCEL2	0x05
#घोषणा IOACCEL2_TMF	0x06

#घोषणा सूचीECT_LOOKUP_SHIFT 4
#घोषणा सूचीECT_LOOKUP_MASK (~((1 << सूचीECT_LOOKUP_SHIFT) - 1))

#घोषणा HPSA_ERROR_BIT          0x02
काष्ठा ctlr_info; /* defined in hpsa.h */
/* The size of this काष्ठाure needs to be भागisible by 128
 * on all architectures.  The low 4 bits of the addresses
 * are used as follows:
 *
 * bit 0: to device, used to indicate "performant mode" command
 *        from device, indidcates error status.
 * bit 1-3: to device, indicates block fetch table entry क्रम
 *          reducing DMA in fetching commands from host memory.
 */

#घोषणा COMMANDLIST_ALIGNMENT 128
काष्ठा CommandList अणु
	काष्ठा CommandListHeader Header;
	काष्ठा RequestBlock      Request;
	काष्ठा ErrDescriptor     ErrDesc;
	काष्ठा SGDescriptor      SG[SG_ENTRIES_IN_CMD];
	/* inक्रमmation associated with the command */
	u32			   busaddr; /* physical addr of this record */
	काष्ठा ErrorInfo *err_info; /* poपूर्णांकer to the allocated mem */
	काष्ठा ctlr_info	   *h;
	पूर्णांक			   cmd_type;
	दीर्घ			   cmdindex;
	काष्ठा completion *रुकोing;
	काष्ठा scsi_cmnd *scsi_cmd;
	काष्ठा work_काष्ठा work;

	/*
	 * For commands using either of the two "ioaccel" paths to
	 * bypass the RAID stack and go directly to the physical disk
	 * phys_disk is a poपूर्णांकer to the hpsa_scsi_dev_t to which the
	 * i/o is destined.  We need to store that here because the command
	 * may potentially encounter TASK SET FULL and need to be resubmitted
	 * For "normal" i/o's not using the "ioaccel" paths, phys_disk is
	 * not used.
	 */
	काष्ठा hpsa_scsi_dev_t *phys_disk;

	bool retry_pending;
	काष्ठा hpsa_scsi_dev_t *device;
	atomic_t refcount; /* Must be last to aव्योम स_रखो in hpsa_cmd_init() */
पूर्ण __aligned(COMMANDLIST_ALIGNMENT);

/*
 * Make sure our embedded atomic variable is aligned. Otherwise we अवरोध atomic
 * operations on architectures that करोn't support unaligned atomics like IA64.
 *
 * The निश्चित guards against reपूर्णांकroductin against unwanted __packed to
 * the काष्ठा CommandList.
 */
अटल_निश्चित(दुरत्व(काष्ठा CommandList, refcount) % __alignof__(atomic_t) == 0);

/* Max S/G elements in I/O accelerator command */
#घोषणा IOACCEL1_MAXSGENTRIES           24
#घोषणा IOACCEL2_MAXSGENTRIES		28

/*
 * Structure क्रम I/O accelerator (mode 1) commands.
 * Note that this काष्ठाure must be 128-byte aligned in size.
 */
#घोषणा IOACCEL1_COMMANDLIST_ALIGNMENT 128
काष्ठा io_accel1_cmd अणु
	__le16 dev_handle;		/* 0x00 - 0x01 */
	u8  reserved1;			/* 0x02 */
	u8  function;			/* 0x03 */
	u8  reserved2[8];		/* 0x04 - 0x0B */
	u32 err_info;			/* 0x0C - 0x0F */
	u8  reserved3[2];		/* 0x10 - 0x11 */
	u8  err_info_len;		/* 0x12 */
	u8  reserved4;			/* 0x13 */
	u8  sgl_offset;			/* 0x14 */
	u8  reserved5[7];		/* 0x15 - 0x1B */
	__le32 transfer_len;		/* 0x1C - 0x1F */
	u8  reserved6[4];		/* 0x20 - 0x23 */
	__le16 io_flags;		/* 0x24 - 0x25 */
	u8  reserved7[14];		/* 0x26 - 0x33 */
	u8  LUN[8];			/* 0x34 - 0x3B */
	__le32 control;			/* 0x3C - 0x3F */
	u8  CDB[16];			/* 0x40 - 0x4F */
	u8  reserved8[16];		/* 0x50 - 0x5F */
	__le16 host_context_flags;	/* 0x60 - 0x61 */
	__le16 समयout_sec;		/* 0x62 - 0x63 */
	u8  ReplyQueue;			/* 0x64 */
	u8  reserved9[3];		/* 0x65 - 0x67 */
	__le64 tag;			/* 0x68 - 0x6F */
	__le64 host_addr;		/* 0x70 - 0x77 */
	u8  CISS_LUN[8];		/* 0x78 - 0x7F */
	काष्ठा SGDescriptor SG[IOACCEL1_MAXSGENTRIES];
पूर्ण __packed __aligned(IOACCEL1_COMMANDLIST_ALIGNMENT);

#घोषणा IOACCEL1_FUNCTION_SCSIIO        0x00
#घोषणा IOACCEL1_SGLOFFSET              32

#घोषणा IOACCEL1_IOFLAGS_IO_REQ         0x4000
#घोषणा IOACCEL1_IOFLAGS_CDBLEN_MASK    0x001F
#घोषणा IOACCEL1_IOFLAGS_CDBLEN_MAX     16

#घोषणा IOACCEL1_CONTROL_NODATAXFER     0x00000000
#घोषणा IOACCEL1_CONTROL_DATA_OUT       0x01000000
#घोषणा IOACCEL1_CONTROL_DATA_IN        0x02000000
#घोषणा IOACCEL1_CONTROL_TASKPRIO_MASK  0x00007800
#घोषणा IOACCEL1_CONTROL_TASKPRIO_SHIFT 11
#घोषणा IOACCEL1_CONTROL_SIMPLEQUEUE    0x00000000
#घोषणा IOACCEL1_CONTROL_HEADOFQUEUE    0x00000100
#घोषणा IOACCEL1_CONTROL_ORDEREDQUEUE   0x00000200
#घोषणा IOACCEL1_CONTROL_ACA            0x00000400

#घोषणा IOACCEL1_HCFLAGS_CISS_FORMAT    0x0013

#घोषणा IOACCEL1_BUSADDR_CMDTYPE        0x00000060

काष्ठा ioaccel2_sg_element अणु
	__le64 address;
	__le32 length;
	u8 reserved[3];
	u8 chain_indicator;
#घोषणा IOACCEL2_CHAIN 0x80
#घोषणा IOACCEL2_LAST_SG 0x40
पूर्ण __packed;

/*
 * SCSI Response Format काष्ठाure क्रम IO Accelerator Mode 2
 */
काष्ठा io_accel2_scsi_response अणु
	u8 IU_type;
#घोषणा IOACCEL2_IU_TYPE_SRF			0x60
	u8 reserved1[3];
	u8 req_id[4];		/* request identअगरier */
	u8 reserved2[4];
	u8 serv_response;		/* service response */
#घोषणा IOACCEL2_SERV_RESPONSE_COMPLETE		0x000
#घोषणा IOACCEL2_SERV_RESPONSE_FAILURE		0x001
#घोषणा IOACCEL2_SERV_RESPONSE_TMF_COMPLETE	0x002
#घोषणा IOACCEL2_SERV_RESPONSE_TMF_SUCCESS	0x003
#घोषणा IOACCEL2_SERV_RESPONSE_TMF_REJECTED	0x004
#घोषणा IOACCEL2_SERV_RESPONSE_TMF_WRONG_LUN	0x005
	u8 status;			/* status */
#घोषणा IOACCEL2_STATUS_SR_TASK_COMP_GOOD	0x00
#घोषणा IOACCEL2_STATUS_SR_TASK_COMP_CHK_COND	0x02
#घोषणा IOACCEL2_STATUS_SR_TASK_COMP_BUSY	0x08
#घोषणा IOACCEL2_STATUS_SR_TASK_COMP_RES_CON	0x18
#घोषणा IOACCEL2_STATUS_SR_TASK_COMP_SET_FULL	0x28
#घोषणा IOACCEL2_STATUS_SR_TASK_COMP_ABORTED	0x40
#घोषणा IOACCEL2_STATUS_SR_IOACCEL_DISABLED	0x0E
#घोषणा IOACCEL2_STATUS_SR_IO_ERROR		0x01
#घोषणा IOACCEL2_STATUS_SR_IO_ABORTED		0x02
#घोषणा IOACCEL2_STATUS_SR_NO_PATH_TO_DEVICE	0x03
#घोषणा IOACCEL2_STATUS_SR_INVALID_DEVICE	0x04
#घोषणा IOACCEL2_STATUS_SR_UNDERRUN		0x51
#घोषणा IOACCEL2_STATUS_SR_OVERRUN		0x75
	u8 data_present;		/* low 2 bits */
#घोषणा IOACCEL2_NO_DATAPRESENT		0x000
#घोषणा IOACCEL2_RESPONSE_DATAPRESENT	0x001
#घोषणा IOACCEL2_SENSE_DATA_PRESENT	0x002
#घोषणा IOACCEL2_RESERVED		0x003
	u8 sense_data_len;		/* sense/response data length */
	u8 resid_cnt[4];		/* residual count */
	u8 sense_data_buff[32];		/* sense/response data buffer */
पूर्ण __packed;

/*
 * Structure क्रम I/O accelerator (mode 2 or m2) commands.
 * Note that this काष्ठाure must be 128-byte aligned in size.
 */
#घोषणा IOACCEL2_COMMANDLIST_ALIGNMENT 128
काष्ठा io_accel2_cmd अणु
	u8  IU_type;			/* IU Type */
	u8  direction;			/* direction, memtype, and encryption */
#घोषणा IOACCEL2_सूचीECTION_MASK		0x03 /* bits 0,1: direction  */
#घोषणा IOACCEL2_सूचीECTION_MEMTYPE_MASK	0x04 /* bit 2: memtype source/dest */
					     /*     0b=PCIe, 1b=DDR */
#घोषणा IOACCEL2_सूचीECTION_ENCRYPT_MASK	0x08 /* bit 3: encryption flag */
					     /*     0=off, 1=on */
	u8  reply_queue;		/* Reply Queue ID */
	u8  reserved1;			/* Reserved */
	__le32 scsi_nexus;		/* Device Handle */
	__le32 Tag;			/* cciss tag, lower 4 bytes only */
	__le32 tweak_lower;		/* Encryption tweak, lower 4 bytes */
	u8  cdb[16];			/* SCSI Command Descriptor Block */
	u8  cciss_lun[8];		/* 8 byte SCSI address */
	__le32 data_len;		/* Total bytes to transfer */
	u8  cmd_priority_task_attr;	/* priority and task attrs */
#घोषणा IOACCEL2_PRIORITY_MASK 0x78
#घोषणा IOACCEL2_ATTR_MASK 0x07
	u8  sg_count;			/* Number of sg elements */
	__le16 dekindex;		/* Data encryption key index */
	__le64 err_ptr;			/* Error Poपूर्णांकer */
	__le32 err_len;			/* Error Length*/
	__le32 tweak_upper;		/* Encryption tweak, upper 4 bytes */
	काष्ठा ioaccel2_sg_element sg[IOACCEL2_MAXSGENTRIES];
	काष्ठा io_accel2_scsi_response error_data;
पूर्ण __packed __aligned(IOACCEL2_COMMANDLIST_ALIGNMENT);

/*
 * defines क्रम Mode 2 command काष्ठा
 * FIXME: this can't be all I need mfm
 */
#घोषणा IOACCEL2_IU_TYPE	0x40
#घोषणा IOACCEL2_IU_TMF_TYPE	0x41
#घोषणा IOACCEL2_सूची_NO_DATA	0x00
#घोषणा IOACCEL2_सूची_DATA_IN	0x01
#घोषणा IOACCEL2_सूची_DATA_OUT	0x02
#घोषणा IOACCEL2_TMF_ABORT	0x01
/*
 * SCSI Task Management Request क्रमmat क्रम Accelerator Mode 2
 */
काष्ठा hpsa_पंचांगf_काष्ठा अणु
	u8 iu_type;		/* Inक्रमmation Unit Type */
	u8 reply_queue;		/* Reply Queue ID */
	u8 पंचांगf;			/* Task Management Function */
	u8 reserved1;		/* byte 3 Reserved */
	__le32 it_nexus;	/* SCSI I-T Nexus */
	u8 lun_id[8];		/* LUN ID क्रम TMF request */
	__le64 tag;		/* cciss tag associated w/ request */
	__le64 पात_tag;	/* cciss tag of SCSI cmd or TMF to पात */
	__le64 error_ptr;		/* Error Poपूर्णांकer */
	__le32 error_len;		/* Error Length */
पूर्ण __packed __aligned(IOACCEL2_COMMANDLIST_ALIGNMENT);

/* Configuration Table Structure */
काष्ठा HostWrite अणु
	__le32		TransportRequest;
	__le32		command_pool_addr_hi;
	__le32		CoalIntDelay;
	__le32		CoalIntCount;
पूर्ण __packed;

#घोषणा SIMPLE_MODE     0x02
#घोषणा PERFORMANT_MODE 0x04
#घोषणा MEMQ_MODE       0x08
#घोषणा IOACCEL_MODE_1  0x80

#घोषणा DRIVER_SUPPORT_UA_ENABLE        0x00000001

काष्ठा CfgTable अणु
	u8		Signature[4];
	__le32		SpecValence;
	__le32		TransportSupport;
	__le32		TransportActive;
	काष्ठा HostWrite HostWrite;
	__le32		CmdsOutMax;
	__le32		BusTypes;
	__le32		TransMethodOffset;
	u8		ServerName[16];
	__le32		HeartBeat;
	__le32		driver_support;
#घोषणा			ENABLE_SCSI_PREFETCH		0x100
#घोषणा			ENABLE_UNIT_ATTN		0x01
	__le32		MaxScatterGatherElements;
	__le32		MaxLogicalUnits;
	__le32		MaxPhysicalDevices;
	__le32		MaxPhysicalDrivesPerLogicalUnit;
	__le32		MaxPerक्रमmantModeCommands;
	__le32		MaxBlockFetch;
	__le32		PowerConservationSupport;
	__le32		PowerConservationEnable;
	__le32		TMFSupportFlags;
	u8		TMFTagMask[8];
	u8		reserved[0x78 - 0x70];
	__le32		misc_fw_support;		/* offset 0x78 */
#घोषणा			MISC_FW_DOORBELL_RESET		0x02
#घोषणा			MISC_FW_DOORBELL_RESET2		0x010
#घोषणा			MISC_FW_RAID_OFFLOAD_BASIC	0x020
#घोषणा			MISC_FW_EVENT_NOTIFY		0x080
	u8		driver_version[32];
	__le32		max_cached_ग_लिखो_size;
	u8		driver_scratchpad[16];
	__le32		max_error_info_length;
	__le32		io_accel_max_embedded_sg_count;
	__le32		io_accel_request_size_offset;
	__le32		event_notअगरy;
#घोषणा		HPSA_EVENT_NOTIFY_ACCEL_IO_PATH_STATE_CHANGE (1 << 30)
#घोषणा		HPSA_EVENT_NOTIFY_ACCEL_IO_PATH_CONFIG_CHANGE (1 << 31)
	__le32		clear_event_notअगरy;
पूर्ण __packed;

#घोषणा NUM_BLOCKFETCH_ENTRIES 8
काष्ठा TransTable_काष्ठा अणु
	__le32		BlockFetch[NUM_BLOCKFETCH_ENTRIES];
	__le32		RepQSize;
	__le32		RepQCount;
	__le32		RepQCtrAddrLow32;
	__le32		RepQCtrAddrHigh32;
#घोषणा MAX_REPLY_QUEUES 64
	काष्ठा vals32  RepQAddr[MAX_REPLY_QUEUES];
पूर्ण __packed;

काष्ठा hpsa_pci_info अणु
	अचिन्हित अक्षर	bus;
	अचिन्हित अक्षर	dev_fn;
	अचिन्हित लघु	करोमुख्य;
	u32		board_id;
पूर्ण __packed;

काष्ठा bmic_identअगरy_controller अणु
	u8	configured_logical_drive_count;	/* offset 0 */
	u8	pad1[153];
	__le16	extended_logical_unit_count;	/* offset 154 */
	u8	pad2[136];
	u8	controller_mode;	/* offset 292 */
	u8	pad3[32];
पूर्ण __packed;


काष्ठा bmic_identअगरy_physical_device अणु
	u8    scsi_bus;          /* SCSI Bus number on controller */
	u8    scsi_id;           /* SCSI ID on this bus */
	__le16 block_size;	     /* sector size in bytes */
	__le32 total_blocks;	     /* number क्रम sectors on drive */
	__le32 reserved_blocks;   /* controller reserved (RIS) */
	u8    model[40];         /* Physical Drive Model */
	u8    serial_number[40]; /* Drive Serial Number */
	u8    firmware_revision[8]; /* drive firmware revision */
	u8    scsi_inquiry_bits; /* inquiry byte 7 bits */
	u8    compaq_drive_stamp; /* 0 means drive not stamped */
	u8    last_failure_reason;
#घोषणा BMIC_LAST_FAILURE_TOO_SMALL_IN_LOAD_CONFIG		0x01
#घोषणा BMIC_LAST_FAILURE_ERROR_ERASING_RIS			0x02
#घोषणा BMIC_LAST_FAILURE_ERROR_SAVING_RIS			0x03
#घोषणा BMIC_LAST_FAILURE_FAIL_DRIVE_COMMAND			0x04
#घोषणा BMIC_LAST_FAILURE_MARK_BAD_FAILED			0x05
#घोषणा BMIC_LAST_FAILURE_MARK_BAD_FAILED_IN_FINISH_REMAP	0x06
#घोषणा BMIC_LAST_FAILURE_TIMEOUT				0x07
#घोषणा BMIC_LAST_FAILURE_AUTOSENSE_FAILED			0x08
#घोषणा BMIC_LAST_FAILURE_MEDIUM_ERROR_1			0x09
#घोषणा BMIC_LAST_FAILURE_MEDIUM_ERROR_2			0x0a
#घोषणा BMIC_LAST_FAILURE_NOT_READY_BAD_SENSE			0x0b
#घोषणा BMIC_LAST_FAILURE_NOT_READY				0x0c
#घोषणा BMIC_LAST_FAILURE_HARDWARE_ERROR			0x0d
#घोषणा BMIC_LAST_FAILURE_ABORTED_COMMAND			0x0e
#घोषणा BMIC_LAST_FAILURE_WRITE_PROTECTED			0x0f
#घोषणा BMIC_LAST_FAILURE_SPIN_UP_FAILURE_IN_RECOVER		0x10
#घोषणा BMIC_LAST_FAILURE_REBUILD_WRITE_ERROR			0x11
#घोषणा BMIC_LAST_FAILURE_TOO_SMALL_IN_HOT_PLUG			0x12
#घोषणा BMIC_LAST_FAILURE_BUS_RESET_RECOVERY_ABORTED		0x13
#घोषणा BMIC_LAST_FAILURE_REMOVED_IN_HOT_PLUG			0x14
#घोषणा BMIC_LAST_FAILURE_INIT_REQUEST_SENSE_FAILED		0x15
#घोषणा BMIC_LAST_FAILURE_INIT_START_UNIT_FAILED		0x16
#घोषणा BMIC_LAST_FAILURE_INQUIRY_FAILED			0x17
#घोषणा BMIC_LAST_FAILURE_NON_DISK_DEVICE			0x18
#घोषणा BMIC_LAST_FAILURE_READ_CAPACITY_FAILED			0x19
#घोषणा BMIC_LAST_FAILURE_INVALID_BLOCK_SIZE			0x1a
#घोषणा BMIC_LAST_FAILURE_HOT_PLUG_REQUEST_SENSE_FAILED		0x1b
#घोषणा BMIC_LAST_FAILURE_HOT_PLUG_START_UNIT_FAILED		0x1c
#घोषणा BMIC_LAST_FAILURE_WRITE_ERROR_AFTER_REMAP		0x1d
#घोषणा BMIC_LAST_FAILURE_INIT_RESET_RECOVERY_ABORTED		0x1e
#घोषणा BMIC_LAST_FAILURE_DEFERRED_WRITE_ERROR			0x1f
#घोषणा BMIC_LAST_FAILURE_MISSING_IN_SAVE_RIS			0x20
#घोषणा BMIC_LAST_FAILURE_WRONG_REPLACE				0x21
#घोषणा BMIC_LAST_FAILURE_GDP_VPD_INQUIRY_FAILED		0x22
#घोषणा BMIC_LAST_FAILURE_GDP_MODE_SENSE_FAILED			0x23
#घोषणा BMIC_LAST_FAILURE_DRIVE_NOT_IN_48BIT_MODE		0x24
#घोषणा BMIC_LAST_FAILURE_DRIVE_TYPE_MIX_IN_HOT_PLUG		0x25
#घोषणा BMIC_LAST_FAILURE_DRIVE_TYPE_MIX_IN_LOAD_CFG		0x26
#घोषणा BMIC_LAST_FAILURE_PROTOCOL_ADAPTER_FAILED		0x27
#घोषणा BMIC_LAST_FAILURE_FAULTY_ID_BAY_EMPTY			0x28
#घोषणा BMIC_LAST_FAILURE_FAULTY_ID_BAY_OCCUPIED		0x29
#घोषणा BMIC_LAST_FAILURE_FAULTY_ID_INVALID_BAY			0x2a
#घोषणा BMIC_LAST_FAILURE_WRITE_RETRIES_FAILED			0x2b

#घोषणा BMIC_LAST_FAILURE_SMART_ERROR_REPORTED			0x37
#घोषणा BMIC_LAST_FAILURE_PHY_RESET_FAILED			0x38
#घोषणा BMIC_LAST_FAILURE_ONLY_ONE_CTLR_CAN_SEE_DRIVE		0x40
#घोषणा BMIC_LAST_FAILURE_KC_VOLUME_FAILED			0x41
#घोषणा BMIC_LAST_FAILURE_UNEXPECTED_REPLACEMENT		0x42
#घोषणा BMIC_LAST_FAILURE_OFFLINE_ERASE				0x80
#घोषणा BMIC_LAST_FAILURE_OFFLINE_TOO_SMALL			0x81
#घोषणा BMIC_LAST_FAILURE_OFFLINE_DRIVE_TYPE_MIX		0x82
#घोषणा BMIC_LAST_FAILURE_OFFLINE_ERASE_COMPLETE		0x83

	u8     flags;
	u8     more_flags;
	u8     scsi_lun;          /* SCSI LUN क्रम phys drive */
	u8     yet_more_flags;
	u8     even_more_flags;
	__le32 spi_speed_rules;/* SPI Speed data:Ultra disable diagnose */
	u8     phys_connector[2];         /* connector number on controller */
	u8     phys_box_on_bus;  /* phys enclosure this drive resides */
	u8     phys_bay_in_box;  /* phys drv bay this drive resides */
	__le32 rpm;              /* Drive rotational speed in rpm */
	u8     device_type;       /* type of drive */
#घोषणा BMIC_DEVICE_TYPE_CONTROLLER	0x07

	u8     sata_version;     /* only valid when drive_type is SATA */
	__le64 big_total_block_count;
	__le64 ris_starting_lba;
	__le32 ris_size;
	u8     wwid[20];
	u8     controller_phy_map[32];
	__le16 phy_count;
	u8     phy_connected_dev_type[256];
	u8     phy_to_drive_bay_num[256];
	__le16 phy_to_attached_dev_index[256];
	u8     box_index;
	u8     reserved;
	__le16 extra_physical_drive_flags;
#घोषणा BMIC_PHYS_DRIVE_SUPPORTS_GAS_GAUGE(idphydrv) \
	(idphydrv->extra_physical_drive_flags & (1 << 10))
	u8     negotiated_link_rate[256];
	u8     phy_to_phy_map[256];
	u8     redundant_path_present_map;
	u8     redundant_path_failure_map;
	u8     active_path_number;
	__le16 alternate_paths_phys_connector[8];
	u8     alternate_paths_phys_box_on_port[8];
	u8     multi_lun_device_lun_count;
	u8     minimum_good_fw_revision[8];
	u8     unique_inquiry_bytes[20];
	u8     current_temperature_degreesC;
	u8     temperature_threshold_degreesC;
	u8     max_temperature_degreesC;
	u8     logical_blocks_per_phys_block_exp; /* phyblocksize = 512*2^exp */
	__le16 current_queue_depth_limit;
	u8     reserved_चयन_stuff[60];
	__le16 घातer_on_hours; /* valid only अगर gas gauge supported */
	__le16 percent_endurance_used; /* valid only अगर gas gauge supported. */
#घोषणा BMIC_PHYS_DRIVE_SSD_WEAROUT(idphydrv) \
	((idphydrv->percent_endurance_used & 0x80) || \
	 (idphydrv->percent_endurance_used > 10000))
	u8     drive_authentication;
#घोषणा BMIC_PHYS_DRIVE_AUTHENTICATED(idphydrv) \
	(idphydrv->drive_authentication == 0x80)
	u8     smart_carrier_authentication;
#घोषणा BMIC_SMART_CARRIER_AUTHENTICATION_SUPPORTED(idphydrv) \
	(idphydrv->smart_carrier_authentication != 0x0)
#घोषणा BMIC_SMART_CARRIER_AUTHENTICATED(idphydrv) \
	(idphydrv->smart_carrier_authentication == 0x01)
	u8     smart_carrier_app_fw_version;
	u8     smart_carrier_bootloader_fw_version;
	u8     sanitize_support_flags;
	u8     drive_key_flags;
	u8     encryption_key_name[64];
	__le32 misc_drive_flags;
	__le16 dek_index;
	__le16 hba_drive_encryption_flags;
	__le16 max_overग_लिखो_समय;
	__le16 max_block_erase_समय;
	__le16 max_crypto_erase_समय;
	u8     device_connector_info[5];
	u8     connector_name[8][8];
	u8     page_83_id[16];
	u8     max_link_rate[256];
	u8     neg_phys_link_rate[256];
	u8     box_conn_name[8];
पूर्ण __packed __attribute((aligned(512)));

काष्ठा bmic_sense_subप्रणाली_info अणु
	u8	primary_slot_number;
	u8	reserved[3];
	u8	chasis_serial_number[32];
	u8	primary_world_wide_id[8];
	u8	primary_array_serial_number[32]; /* शून्य terminated */
	u8	primary_cache_serial_number[32]; /* शून्य terminated */
	u8	reserved_2[8];
	u8	secondary_array_serial_number[32];
	u8	secondary_cache_serial_number[32];
	u8	pad[332];
पूर्ण __packed;

काष्ठा bmic_sense_storage_box_params अणु
	u8	reserved[36];
	u8	inquiry_valid;
	u8	reserved_1[68];
	u8	phys_box_on_port;
	u8	reserved_2[22];
	u16	connection_info;
	u8	reserver_3[84];
	u8	phys_connector[2];
	u8	reserved_4[296];
पूर्ण __packed;

#पूर्ण_अगर /* HPSA_CMD_H */
