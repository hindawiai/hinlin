<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux Driver क्रम Mylex DAC960/AcceleRAID/eXtremeRAID PCI RAID Controllers
 *
 * Copyright 2017 Hannes Reinecke, SUSE Linux GmbH <hare@suse.com>
 *
 * Based on the original DAC960 driver,
 * Copyright 1998-2001 by Leonard N. Zubkoff <lnz@dandelion.com>
 * Portions Copyright 2002 by Mylex (An IBM Business Unit)
 *
 */

#अगर_अघोषित MYRB_H
#घोषणा MYRB_H

#घोषणा MYRB_MAX_LDEVS			32
#घोषणा MYRB_MAX_CHANNELS		3
#घोषणा MYRB_MAX_TARGETS		16
#घोषणा MYRB_MAX_PHYSICAL_DEVICES	45
#घोषणा MYRB_SCATTER_GATHER_LIMIT	32
#घोषणा MYRB_CMD_MBOX_COUNT		256
#घोषणा MYRB_STAT_MBOX_COUNT		1024

#घोषणा MYRB_BLKSIZE_BITS		9
#घोषणा MYRB_MAILBOX_TIMEOUT		1000000

#घोषणा MYRB_DCMD_TAG			1
#घोषणा MYRB_MCMD_TAG			2

#घोषणा MYRB_PRIMARY_MONITOR_INTERVAL (10 * HZ)
#घोषणा MYRB_SECONDARY_MONITOR_INTERVAL (60 * HZ)

/*
 * DAC960 V1 Firmware Command Opcodes.
 */
क्रमागत myrb_cmd_opcode अणु
	/* I/O Commands */
	MYRB_CMD_READ_EXTENDED =	0x33,
	MYRB_CMD_WRITE_EXTENDED =	0x34,
	MYRB_CMD_READAHEAD_EXTENDED =	0x35,
	MYRB_CMD_READ_EXTENDED_SG =	0xB3,
	MYRB_CMD_WRITE_EXTENDED_SG =	0xB4,
	MYRB_CMD_READ =			0x36,
	MYRB_CMD_READ_SG =		0xB6,
	MYRB_CMD_WRITE =		0x37,
	MYRB_CMD_WRITE_SG =		0xB7,
	MYRB_CMD_DCDB =			0x04,
	MYRB_CMD_DCDB_SG =		0x84,
	MYRB_CMD_FLUSH =		0x0A,
	/* Controller Status Related Commands */
	MYRB_CMD_ENQUIRY =		0x53,
	MYRB_CMD_ENQUIRY2 =		0x1C,
	MYRB_CMD_GET_LDRV_ELEMENT =	0x55,
	MYRB_CMD_GET_LDEV_INFO =	0x19,
	MYRB_CMD_IOPORTREAD =		0x39,
	MYRB_CMD_IOPORTWRITE =		0x3A,
	MYRB_CMD_GET_SD_STATS =		0x3E,
	MYRB_CMD_GET_PD_STATS =		0x3F,
	MYRB_CMD_EVENT_LOG_OPERATION =	0x72,
	/* Device Related Commands */
	MYRB_CMD_START_DEVICE =		0x10,
	MYRB_CMD_GET_DEVICE_STATE =	0x50,
	MYRB_CMD_STOP_CHANNEL =		0x13,
	MYRB_CMD_START_CHANNEL =	0x12,
	MYRB_CMD_RESET_CHANNEL =	0x1A,
	/* Commands Associated with Data Consistency and Errors */
	MYRB_CMD_REBUILD =		0x09,
	MYRB_CMD_REBUILD_ASYNC =	0x16,
	MYRB_CMD_CHECK_CONSISTENCY =	0x0F,
	MYRB_CMD_CHECK_CONSISTENCY_ASYNC = 0x1E,
	MYRB_CMD_REBUILD_STAT =		0x0C,
	MYRB_CMD_GET_REBUILD_PROGRESS =	0x27,
	MYRB_CMD_REBUILD_CONTROL =	0x1F,
	MYRB_CMD_READ_BADBLOCK_TABLE =	0x0B,
	MYRB_CMD_READ_BADDATA_TABLE =	0x25,
	MYRB_CMD_CLEAR_BADDATA_TABLE =	0x26,
	MYRB_CMD_GET_ERROR_TABLE =	0x17,
	MYRB_CMD_ADD_CAPACITY_ASYNC =	0x2A,
	MYRB_CMD_BGI_CONTROL =		0x2B,
	/* Configuration Related Commands */
	MYRB_CMD_READ_CONFIG2 =		0x3D,
	MYRB_CMD_WRITE_CONFIG2 =	0x3C,
	MYRB_CMD_READ_CONFIG_ONDISK =	0x4A,
	MYRB_CMD_WRITE_CONFIG_ONDISK =	0x4B,
	MYRB_CMD_READ_CONFIG =		0x4E,
	MYRB_CMD_READ_BACKUP_CONFIG =	0x4D,
	MYRB_CMD_WRITE_CONFIG =		0x4F,
	MYRB_CMD_ADD_CONFIG =		0x4C,
	MYRB_CMD_READ_CONFIG_LABEL =	0x48,
	MYRB_CMD_WRITE_CONFIG_LABEL =	0x49,
	/* Firmware Upgrade Related Commands */
	MYRB_CMD_LOAD_IMAGE =		0x20,
	MYRB_CMD_STORE_IMAGE =		0x21,
	MYRB_CMD_PROGRAM_IMAGE =	0x22,
	/* Diagnostic Commands */
	MYRB_CMD_SET_DIAGNOSTIC_MODE =	0x31,
	MYRB_CMD_RUN_DIAGNOSTIC =	0x32,
	/* Subप्रणाली Service Commands */
	MYRB_CMD_GET_SUBSYS_DATA =	0x70,
	MYRB_CMD_SET_SUBSYS_PARAM =	0x71,
	/* Version 2.xx Firmware Commands */
	MYRB_CMD_ENQUIRY_OLD =		0x05,
	MYRB_CMD_GET_DEVICE_STATE_OLD =	0x14,
	MYRB_CMD_READ_OLD =		0x02,
	MYRB_CMD_WRITE_OLD =		0x03,
	MYRB_CMD_READ_SG_OLD =		0x82,
	MYRB_CMD_WRITE_SG_OLD =		0x83
पूर्ण __packed;

/*
 * DAC960 V1 Firmware Command Status Codes.
 */
#घोषणा MYRB_STATUS_SUCCESS			0x0000	/* Common */
#घोषणा MYRB_STATUS_CHECK_CONDITION		0x0002	/* Common */
#घोषणा MYRB_STATUS_NO_DEVICE			0x0102	/* Common */
#घोषणा MYRB_STATUS_INVALID_ADDRESS		0x0105	/* Common */
#घोषणा MYRB_STATUS_INVALID_PARAM		0x0105	/* Common */
#घोषणा MYRB_STATUS_IRRECOVERABLE_DATA_ERROR	0x0001	/* I/O */
#घोषणा MYRB_STATUS_LDRV_NONEXISTENT_OR_OFFLINE 0x0002	/* I/O */
#घोषणा MYRB_STATUS_ACCESS_BEYOND_END_OF_LDRV	0x0105	/* I/O */
#घोषणा MYRB_STATUS_BAD_DATA			0x010C	/* I/O */
#घोषणा MYRB_STATUS_DEVICE_BUSY			0x0008	/* DCDB */
#घोषणा MYRB_STATUS_DEVICE_NONRESPONSIVE	0x000E	/* DCDB */
#घोषणा MYRB_STATUS_COMMAND_TERMINATED		0x000F	/* DCDB */
#घोषणा MYRB_STATUS_START_DEVICE_FAILED		0x0002	/* Device */
#घोषणा MYRB_STATUS_INVALID_CHANNEL_OR_TARGET	0x0105	/* Device */
#घोषणा MYRB_STATUS_CHANNEL_BUSY		0x0106	/* Device */
#घोषणा MYRB_STATUS_OUT_OF_MEMORY		0x0107	/* Device */
#घोषणा MYRB_STATUS_CHANNEL_NOT_STOPPED		0x0002	/* Device */
#घोषणा MYRB_STATUS_ATTEMPT_TO_RBLD_ONLINE_DRIVE 0x0002	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_BADBLOCKS		0x0003	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_NEW_DISK_FAILED	0x0004	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_OR_CHECK_INPROGRESS	0x0106	/* Consistency */
#घोषणा MYRB_STATUS_DEPENDENT_DISK_DEAD		0x0002	/* Consistency */
#घोषणा MYRB_STATUS_INCONSISTENT_BLOCKS		0x0003	/* Consistency */
#घोषणा MYRB_STATUS_INVALID_OR_NONREDUNDANT_LDRV 0x0105 /* Consistency */
#घोषणा MYRB_STATUS_NO_RBLD_OR_CHECK_INPROGRESS	0x0105	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_IN_PROGRESS_DATA_VALID	0x0000	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_FAILED_LDEV_FAILURE	0x0002	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_FAILED_BADBLOCKS	0x0003	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_FAILED_NEW_DRIVE_FAILED 0x0004	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_SUCCESS		0x0100	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_SUCCESS_TERMINATED	0x0107	/* Consistency */
#घोषणा MYRB_STATUS_RBLD_NOT_CHECKED		0x0108	/* Consistency */
#घोषणा MYRB_STATUS_BGI_SUCCESS			0x0100	/* Consistency */
#घोषणा MYRB_STATUS_BGI_ABORTED			0x0005	/* Consistency */
#घोषणा MYRB_STATUS_NO_BGI_INPROGRESS		0x0105	/* Consistency */
#घोषणा MYRB_STATUS_ADD_CAPACITY_INPROGRESS	0x0004	/* Consistency */
#घोषणा MYRB_STATUS_ADD_CAPACITY_FAILED_OR_SUSPENDED 0x00F4 /* Consistency */
#घोषणा MYRB_STATUS_CONFIG2_CSUM_ERROR		0x0002	/* Configuration */
#घोषणा MYRB_STATUS_CONFIGURATION_SUSPENDED	0x0106	/* Configuration */
#घोषणा MYRB_STATUS_FAILED_TO_CONFIGURE_NVRAM	0x0105	/* Configuration */
#घोषणा MYRB_STATUS_CONFIGURATION_NOT_SAVED	0x0106	/* Configuration */
#घोषणा MYRB_STATUS_SUBSYS_NOTINSTALLED		0x0001	/* Subप्रणाली */
#घोषणा MYRB_STATUS_SUBSYS_FAILED		0x0002	/* Subप्रणाली */
#घोषणा MYRB_STATUS_SUBSYS_BUSY			0x0106	/* Subप्रणाली */
#घोषणा MYRB_STATUS_SUBSYS_TIMEOUT		0x0108	/* Subप्रणाली */

/*
 * DAC960 V1 Firmware Enquiry Command reply काष्ठाure.
 */
काष्ठा myrb_enquiry अणु
	अचिन्हित अक्षर ldev_count;			/* Byte 0 */
	अचिन्हित पूर्णांक rsvd1:24;				/* Bytes 1-3 */
	अचिन्हित पूर्णांक ldev_sizes[32];			/* Bytes 4-131 */
	अचिन्हित लघु flash_age;			/* Bytes 132-133 */
	काष्ठा अणु
		अचिन्हित अक्षर deferred:1;		/* Byte 134 Bit 0 */
		अचिन्हित अक्षर low_bat:1;		/* Byte 134 Bit 1 */
		अचिन्हित अक्षर rsvd2:6;			/* Byte 134 Bits 2-7 */
	पूर्ण status;
	अचिन्हित अक्षर rsvd3:8;				/* Byte 135 */
	अचिन्हित अक्षर fw_minor_version;			/* Byte 136 */
	अचिन्हित अक्षर fw_major_version;			/* Byte 137 */
	क्रमागत अणु
		MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS =	0x00,
		MYRB_STDBY_RBLD_IN_PROGRESS =			0x01,
		MYRB_BG_RBLD_IN_PROGRESS =			0x02,
		MYRB_BG_CHECK_IN_PROGRESS =			0x03,
		MYRB_STDBY_RBLD_COMPLETED_WITH_ERROR =		0xFF,
		MYRB_BG_RBLD_OR_CHECK_FAILED_DRIVE_FAILED =	0xF0,
		MYRB_BG_RBLD_OR_CHECK_FAILED_LDEV_FAILED =	0xF1,
		MYRB_BG_RBLD_OR_CHECK_FAILED_OTHER =		0xF2,
		MYRB_BG_RBLD_OR_CHECK_SUCCESS_TERMINATED =	0xF3
	पूर्ण __packed rbld;		/* Byte 138 */
	अचिन्हित अक्षर max_tcq;				/* Byte 139 */
	अचिन्हित अक्षर ldev_offline;			/* Byte 140 */
	अचिन्हित अक्षर rsvd4:8;				/* Byte 141 */
	अचिन्हित लघु ev_seq;				/* Bytes 142-143 */
	अचिन्हित अक्षर ldev_critical;			/* Byte 144 */
	अचिन्हित पूर्णांक rsvd5:24;				/* Bytes 145-147 */
	अचिन्हित अक्षर pdev_dead;			/* Byte 148 */
	अचिन्हित अक्षर rsvd6:8;				/* Byte 149 */
	अचिन्हित अक्षर rbld_count;			/* Byte 150 */
	काष्ठा अणु
		अचिन्हित अक्षर rsvd7:3;			/* Byte 151 Bits 0-2 */
		अचिन्हित अक्षर bbu_present:1;		/* Byte 151 Bit 3 */
		अचिन्हित अक्षर rsvd8:4;			/* Byte 151 Bits 4-7 */
	पूर्ण misc;
	काष्ठा अणु
		अचिन्हित अक्षर target;
		अचिन्हित अक्षर channel;
	पूर्ण dead_drives[21];				/* Bytes 152-194 */
	अचिन्हित अक्षर rsvd9[62];			/* Bytes 195-255 */
पूर्ण __packed;

/*
 * DAC960 V1 Firmware Enquiry2 Command reply काष्ठाure.
 */
काष्ठा myrb_enquiry2 अणु
	काष्ठा अणु
		क्रमागत अणु
			DAC960_V1_P_PD_PU =			0x01,
			DAC960_V1_PL =				0x02,
			DAC960_V1_PG =				0x10,
			DAC960_V1_PJ =				0x11,
			DAC960_V1_PR =				0x12,
			DAC960_V1_PT =				0x13,
			DAC960_V1_PTL0 =			0x14,
			DAC960_V1_PRL =				0x15,
			DAC960_V1_PTL1 =			0x16,
			DAC960_V1_1164P =			0x20
		पूर्ण __packed sub_model;		/* Byte 0 */
		अचिन्हित अक्षर actual_channels;			/* Byte 1 */
		क्रमागत अणु
			MYRB_5_CHANNEL_BOARD =		0x01,
			MYRB_3_CHANNEL_BOARD =		0x02,
			MYRB_2_CHANNEL_BOARD =		0x03,
			MYRB_3_CHANNEL_ASIC_DAC =	0x04
		पूर्ण __packed model;		/* Byte 2 */
		क्रमागत अणु
			MYRB_EISA_CONTROLLER =		0x01,
			MYRB_MCA_CONTROLLER =		0x02,
			MYRB_PCI_CONTROLLER =		0x03,
			MYRB_SCSI_TO_SCSI =		0x08
		पूर्ण __packed controller;	/* Byte 3 */
	पूर्ण hw;						/* Bytes 0-3 */
	/* MajorVersion.MinorVersion-FirmwareType-TurnID */
	काष्ठा अणु
		अचिन्हित अक्षर major_version;		/* Byte 4 */
		अचिन्हित अक्षर minor_version;		/* Byte 5 */
		अचिन्हित अक्षर turn_id;			/* Byte 6 */
		अक्षर firmware_type;			/* Byte 7 */
	पूर्ण fw;						/* Bytes 4-7 */
	अचिन्हित पूर्णांक rsvd1;				/* Byte 8-11 */
	अचिन्हित अक्षर cfg_chan;				/* Byte 12 */
	अचिन्हित अक्षर cur_chan;				/* Byte 13 */
	अचिन्हित अक्षर max_tarमाला_लो;			/* Byte 14 */
	अचिन्हित अक्षर max_tcq;				/* Byte 15 */
	अचिन्हित अक्षर max_ldev;				/* Byte 16 */
	अचिन्हित अक्षर max_arms;				/* Byte 17 */
	अचिन्हित अक्षर max_spans;			/* Byte 18 */
	अचिन्हित अक्षर rsvd2;				/* Byte 19 */
	अचिन्हित पूर्णांक rsvd3;				/* Bytes 20-23 */
	अचिन्हित पूर्णांक mem_size;				/* Bytes 24-27 */
	अचिन्हित पूर्णांक cache_size;			/* Bytes 28-31 */
	अचिन्हित पूर्णांक flash_size;			/* Bytes 32-35 */
	अचिन्हित पूर्णांक nvram_size;			/* Bytes 36-39 */
	काष्ठा अणु
		क्रमागत अणु
			MYRB_RAM_TYPE_DRAM =		0x0,
			MYRB_RAM_TYPE_EDO =			0x1,
			MYRB_RAM_TYPE_SDRAM =		0x2,
			MYRB_RAM_TYPE_Last =		0x7
		पूर्ण __packed ram:3;	/* Byte 40 Bits 0-2 */
		क्रमागत अणु
			MYRB_ERR_CORR_None =	0x0,
			MYRB_ERR_CORR_Parity =	0x1,
			MYRB_ERR_CORR_ECC =		0x2,
			MYRB_ERR_CORR_Last =	0x7
		पूर्ण __packed ec:3;	/* Byte 40 Bits 3-5 */
		अचिन्हित अक्षर fast_page:1;		/* Byte 40 Bit 6 */
		अचिन्हित अक्षर low_घातer:1;		/* Byte 40 Bit 7 */
		अचिन्हित अक्षर rsvd4;			/* Bytes 41 */
	पूर्ण mem_type;
	अचिन्हित लघु घड़ी_speed;			/* Bytes 42-43 */
	अचिन्हित लघु mem_speed;			/* Bytes 44-45 */
	अचिन्हित लघु hw_speed;			/* Bytes 46-47 */
	अचिन्हित अक्षर rsvd5[12];			/* Bytes 48-59 */
	अचिन्हित लघु max_cmds;			/* Bytes 60-61 */
	अचिन्हित लघु max_sge;				/* Bytes 62-63 */
	अचिन्हित लघु max_drv_cmds;			/* Bytes 64-65 */
	अचिन्हित लघु max_io_desc;			/* Bytes 66-67 */
	अचिन्हित लघु max_sectors;			/* Bytes 68-69 */
	अचिन्हित अक्षर latency;				/* Byte 70 */
	अचिन्हित अक्षर rsvd6;				/* Byte 71 */
	अचिन्हित अक्षर scsi_पंचांगo;				/* Byte 72 */
	अचिन्हित अक्षर rsvd7;				/* Byte 73 */
	अचिन्हित लघु min_मुक्तlines;			/* Bytes 74-75 */
	अचिन्हित अक्षर rsvd8[8];				/* Bytes 76-83 */
	अचिन्हित अक्षर rbld_rate_स्थिर;			/* Byte 84 */
	अचिन्हित अक्षर rsvd9[11];			/* Byte 85-95 */
	अचिन्हित लघु pdrv_block_size;			/* Bytes 96-97 */
	अचिन्हित लघु ldev_block_size;			/* Bytes 98-99 */
	अचिन्हित लघु max_blocks_per_cmd;		/* Bytes 100-101 */
	अचिन्हित लघु block_factor;			/* Bytes 102-103 */
	अचिन्हित लघु cacheline_size;			/* Bytes 104-105 */
	काष्ठा अणु
		क्रमागत अणु
			MYRB_WIDTH_NARROW_8BIT =		0x0,
			MYRB_WIDTH_WIDE_16BIT =			0x1,
			MYRB_WIDTH_WIDE_32BIT =			0x2
		पूर्ण __packed bus_width:2;	/* Byte 106 Bits 0-1 */
		क्रमागत अणु
			MYRB_SCSI_SPEED_FAST =			0x0,
			MYRB_SCSI_SPEED_ULTRA =			0x1,
			MYRB_SCSI_SPEED_ULTRA2 =		0x2
		पूर्ण __packed bus_speed:2;	/* Byte 106 Bits 2-3 */
		अचिन्हित अक्षर dअगरferential:1;		/* Byte 106 Bit 4 */
		अचिन्हित अक्षर rsvd10:3;			/* Byte 106 Bits 5-7 */
	पूर्ण scsi_cap;
	अचिन्हित अक्षर rsvd11[5];			/* Byte 107-111 */
	अचिन्हित लघु fw_build;			/* Bytes 112-113 */
	क्रमागत अणु
		MYRB_FAULT_AEMI =				0x01,
		MYRB_FAULT_OEM1 =				0x02,
		MYRB_FAULT_OEM2 =				0x04,
		MYRB_FAULT_OEM3 =				0x08,
		MYRB_FAULT_CONNER =				0x10,
		MYRB_FAULT_SAFTE =				0x20
	पूर्ण __packed fault_mgmt;		/* Byte 114 */
	अचिन्हित अक्षर rsvd12;				/* Byte 115 */
	काष्ठा अणु
		अचिन्हित पूर्णांक clustering:1;		/* Byte 116 Bit 0 */
		अचिन्हित पूर्णांक online_RAID_expansion:1;	/* Byte 116 Bit 1 */
		अचिन्हित पूर्णांक पढ़ोahead:1;		/* Byte 116 Bit 2 */
		अचिन्हित पूर्णांक bgi:1;			/* Byte 116 Bit 3 */
		अचिन्हित पूर्णांक rsvd13:28;			/* Bytes 116-119 */
	पूर्ण fw_features;
	अचिन्हित अक्षर rsvd14[8];			/* Bytes 120-127 */
पूर्ण __packed;

/*
 * DAC960 V1 Firmware Logical Drive State type.
 */
क्रमागत myrb_devstate अणु
	MYRB_DEVICE_DEAD =		0x00,
	MYRB_DEVICE_WO =		0x02,
	MYRB_DEVICE_ONLINE =		0x03,
	MYRB_DEVICE_CRITICAL =		0x04,
	MYRB_DEVICE_STANDBY =		0x10,
	MYRB_DEVICE_OFFLINE =		0xFF
पूर्ण __packed;

/*
 * DAC960 V1 RAID Levels
 */
क्रमागत myrb_raidlevel अणु
	MYRB_RAID_LEVEL0 =		0x0,     /* RAID 0 */
	MYRB_RAID_LEVEL1 =		0x1,     /* RAID 1 */
	MYRB_RAID_LEVEL3 =		0x3,     /* RAID 3 */
	MYRB_RAID_LEVEL5 =		0x5,     /* RAID 5 */
	MYRB_RAID_LEVEL6 =		0x6,     /* RAID 6 */
	MYRB_RAID_JBOD =		0x7,     /* RAID 7 (JBOD) */
पूर्ण __packed;

/*
 * DAC960 V1 Firmware Logical Drive Inक्रमmation काष्ठाure.
 */
काष्ठा myrb_ldev_info अणु
	अचिन्हित पूर्णांक size;				/* Bytes 0-3 */
	क्रमागत myrb_devstate state;			/* Byte 4 */
	अचिन्हित पूर्णांक raid_level:7;			/* Byte 5 Bits 0-6 */
	अचिन्हित पूर्णांक wb_enabled:1;			/* Byte 5 Bit 7 */
	अचिन्हित पूर्णांक rsvd:16;				/* Bytes 6-7 */
पूर्ण;

/*
 * DAC960 V1 Firmware Perक्रमm Event Log Operation Types.
 */
#घोषणा DAC960_V1_GetEventLogEntry		0x00

/*
 * DAC960 V1 Firmware Get Event Log Entry Command reply काष्ठाure.
 */
काष्ठा myrb_log_entry अणु
	अचिन्हित अक्षर msg_type;			/* Byte 0 */
	अचिन्हित अक्षर msg_len;			/* Byte 1 */
	अचिन्हित अक्षर target:5;			/* Byte 2 Bits 0-4 */
	अचिन्हित अक्षर channel:3;		/* Byte 2 Bits 5-7 */
	अचिन्हित अक्षर lun:6;			/* Byte 3 Bits 0-5 */
	अचिन्हित अक्षर rsvd1:2;			/* Byte 3 Bits 6-7 */
	अचिन्हित लघु seq_num;			/* Bytes 4-5 */
	अचिन्हित अक्षर sense[26];		/* Bytes 6-31 */
पूर्ण;

/*
 * DAC960 V1 Firmware Get Device State Command reply काष्ठाure.
 * The काष्ठाure is padded by 2 bytes क्रम compatibility with Version 2.xx
 * Firmware.
 */
काष्ठा myrb_pdev_state अणु
	अचिन्हित पूर्णांक present:1;			/* Byte 0 Bit 0 */
	अचिन्हित पूर्णांक :7;				/* Byte 0 Bits 1-7 */
	क्रमागत अणु
		MYRB_TYPE_OTHER =			0x0,
		MYRB_TYPE_DISK =			0x1,
		MYRB_TYPE_TAPE =			0x2,
		MYRB_TYPE_CDROM_OR_WORM =		0x3
	पूर्ण __packed devtype:2;		/* Byte 1 Bits 0-1 */
	अचिन्हित पूर्णांक rsvd1:1;				/* Byte 1 Bit 2 */
	अचिन्हित पूर्णांक fast20:1;				/* Byte 1 Bit 3 */
	अचिन्हित पूर्णांक sync:1;				/* Byte 1 Bit 4 */
	अचिन्हित पूर्णांक fast:1;				/* Byte 1 Bit 5 */
	अचिन्हित पूर्णांक wide:1;				/* Byte 1 Bit 6 */
	अचिन्हित पूर्णांक tcq_supported:1;			/* Byte 1 Bit 7 */
	क्रमागत myrb_devstate state;			/* Byte 2 */
	अचिन्हित पूर्णांक rsvd2:8;				/* Byte 3 */
	अचिन्हित पूर्णांक sync_multiplier;			/* Byte 4 */
	अचिन्हित पूर्णांक sync_offset:5;			/* Byte 5 Bits 0-4 */
	अचिन्हित पूर्णांक rsvd3:3;				/* Byte 5 Bits 5-7 */
	अचिन्हित पूर्णांक size;				/* Bytes 6-9 */
	अचिन्हित पूर्णांक rsvd4:16;			/* Bytes 10-11 */
पूर्ण __packed;

/*
 * DAC960 V1 Firmware Get Rebuild Progress Command reply काष्ठाure.
 */
काष्ठा myrb_rbld_progress अणु
	अचिन्हित पूर्णांक ldev_num;				/* Bytes 0-3 */
	अचिन्हित पूर्णांक ldev_size;				/* Bytes 4-7 */
	अचिन्हित पूर्णांक blocks_left;			/* Bytes 8-11 */
पूर्ण;

/*
 * DAC960 V1 Firmware Background Initialization Status Command reply काष्ठाure.
 */
काष्ठा myrb_bgi_status अणु
	अचिन्हित पूर्णांक ldev_size;				/* Bytes 0-3 */
	अचिन्हित पूर्णांक blocks_करोne;			/* Bytes 4-7 */
	अचिन्हित अक्षर rsvd1[12];			/* Bytes 8-19 */
	अचिन्हित पूर्णांक ldev_num;				/* Bytes 20-23 */
	अचिन्हित अक्षर raid_level;			/* Byte 24 */
	क्रमागत अणु
		MYRB_BGI_INVALID =	0x00,
		MYRB_BGI_STARTED =	0x02,
		MYRB_BGI_INPROGRESS =	0x04,
		MYRB_BGI_SUSPENDED =	0x05,
		MYRB_BGI_CANCELLED =	0x06
	पूर्ण __packed status;		/* Byte 25 */
	अचिन्हित अक्षर rsvd2[6];				/* Bytes 26-31 */
पूर्ण;

/*
 * DAC960 V1 Firmware Error Table Entry काष्ठाure.
 */
काष्ठा myrb_error_entry अणु
	अचिन्हित अक्षर parity_err;			/* Byte 0 */
	अचिन्हित अक्षर soft_err;				/* Byte 1 */
	अचिन्हित अक्षर hard_err;				/* Byte 2 */
	अचिन्हित अक्षर misc_err;				/* Byte 3 */
पूर्ण;

/*
 * DAC960 V1 Firmware Read Config2 Command reply काष्ठाure.
 */
काष्ठा myrb_config2 अणु
	अचिन्हित rsvd1:1;				/* Byte 0 Bit 0 */
	अचिन्हित active_negation:1;			/* Byte 0 Bit 1 */
	अचिन्हित rsvd2:5;				/* Byte 0 Bits 2-6 */
	अचिन्हित no_rescan_on_reset_during_scan:1;	/* Byte 0 Bit 7 */
	अचिन्हित StorageWorks_support:1;		/* Byte 1 Bit 0 */
	अचिन्हित HewlettPackard_support:1;		/* Byte 1 Bit 1 */
	अचिन्हित no_disconnect_on_first_command:1;	/* Byte 1 Bit 2 */
	अचिन्हित rsvd3:2;				/* Byte 1 Bits 3-4 */
	अचिन्हित AEMI_ARM:1;				/* Byte 1 Bit 5 */
	अचिन्हित AEMI_OFM:1;				/* Byte 1 Bit 6 */
	अचिन्हित rsvd4:1;				/* Byte 1 Bit 7 */
	क्रमागत अणु
		MYRB_OEMID_MYLEX =		0x00,
		MYRB_OEMID_IBM =		0x08,
		MYRB_OEMID_HP =			0x0A,
		MYRB_OEMID_DEC =		0x0C,
		MYRB_OEMID_SIEMENS =		0x10,
		MYRB_OEMID_INTEL =		0x12
	पूर्ण __packed OEMID;		/* Byte 2 */
	अचिन्हित अक्षर oem_model_number;			/* Byte 3 */
	अचिन्हित अक्षर physical_sector;			/* Byte 4 */
	अचिन्हित अक्षर logical_sector;			/* Byte 5 */
	अचिन्हित अक्षर block_factor;			/* Byte 6 */
	अचिन्हित पढ़ोahead_enabled:1;			/* Byte 7 Bit 0 */
	अचिन्हित low_BIOS_delay:1;			/* Byte 7 Bit 1 */
	अचिन्हित rsvd5:2;				/* Byte 7 Bits 2-3 */
	अचिन्हित restrict_reassign_to_one_sector:1;	/* Byte 7 Bit 4 */
	अचिन्हित rsvd6:1;				/* Byte 7 Bit 5 */
	अचिन्हित FUA_during_ग_लिखो_recovery:1;		/* Byte 7 Bit 6 */
	अचिन्हित enable_LeftSymmetricRAID5Algorithm:1;	/* Byte 7 Bit 7 */
	अचिन्हित अक्षर शेष_rebuild_rate;		/* Byte 8 */
	अचिन्हित अक्षर rsvd7;				/* Byte 9 */
	अचिन्हित अक्षर blocks_per_cacheline;		/* Byte 10 */
	अचिन्हित अक्षर blocks_per_stripe;		/* Byte 11 */
	काष्ठा अणु
		क्रमागत अणु
			MYRB_SPEED_ASYNC =		0x0,
			MYRB_SPEED_SYNC_8MHz =		0x1,
			MYRB_SPEED_SYNC_5MHz =		0x2,
			MYRB_SPEED_SYNC_10_OR_20MHz =	0x3
		पूर्ण __packed speed:2;	/* Byte 11 Bits 0-1 */
		अचिन्हित क्रमce_8bit:1;			/* Byte 11 Bit 2 */
		अचिन्हित disable_fast20:1;		/* Byte 11 Bit 3 */
		अचिन्हित rsvd8:3;			/* Byte 11 Bits 4-6 */
		अचिन्हित enable_tcq:1;			/* Byte 11 Bit 7 */
	पूर्ण __packed channelparam[6];	/* Bytes 12-17 */
	अचिन्हित अक्षर SCSIInitiatorID;			/* Byte 18 */
	अचिन्हित अक्षर rsvd9;				/* Byte 19 */
	क्रमागत अणु
		MYRB_STARTUP_CONTROLLER_SPINUP =	0x00,
		MYRB_STARTUP_POWERON_SPINUP =		0x01
	पूर्ण __packed startup;		/* Byte 20 */
	अचिन्हित अक्षर simultaneous_device_spinup_count;	/* Byte 21 */
	अचिन्हित अक्षर seconds_delay_between_spinups;	/* Byte 22 */
	अचिन्हित अक्षर rsvd10[29];			/* Bytes 23-51 */
	अचिन्हित BIOS_disabled:1;			/* Byte 52 Bit 0 */
	अचिन्हित CDROM_boot_enabled:1;			/* Byte 52 Bit 1 */
	अचिन्हित rsvd11:3;				/* Byte 52 Bits 2-4 */
	क्रमागत अणु
		MYRB_GEOM_128_32 =		0x0,
		MYRB_GEOM_255_63 =		0x1,
		MYRB_GEOM_RESERVED1 =		0x2,
		MYRB_GEOM_RESERVED2 =		0x3
	पूर्ण __packed drive_geometry:2;	/* Byte 52 Bits 5-6 */
	अचिन्हित rsvd12:1;				/* Byte 52 Bit 7 */
	अचिन्हित अक्षर rsvd13[9];			/* Bytes 53-61 */
	अचिन्हित लघु csum;				/* Bytes 62-63 */
पूर्ण;

/*
 * DAC960 V1 Firmware DCDB request काष्ठाure.
 */
काष्ठा myrb_dcdb अणु
	अचिन्हित target:4;				 /* Byte 0 Bits 0-3 */
	अचिन्हित channel:4;				 /* Byte 0 Bits 4-7 */
	क्रमागत अणु
		MYRB_DCDB_XFER_NONE =		0,
		MYRB_DCDB_XFER_DEVICE_TO_SYSTEM = 1,
		MYRB_DCDB_XFER_SYSTEM_TO_DEVICE = 2,
		MYRB_DCDB_XFER_ILLEGAL =	3
	पूर्ण __packed data_xfer:2;				/* Byte 1 Bits 0-1 */
	अचिन्हित early_status:1;			/* Byte 1 Bit 2 */
	अचिन्हित rsvd1:1;				/* Byte 1 Bit 3 */
	क्रमागत अणु
		MYRB_DCDB_TMO_24_HRS =	0,
		MYRB_DCDB_TMO_10_SECS =	1,
		MYRB_DCDB_TMO_60_SECS =	2,
		MYRB_DCDB_TMO_10_MINS =	3
	पूर्ण __packed समयout:2;				/* Byte 1 Bits 4-5 */
	अचिन्हित no_स्वतःsense:1;			/* Byte 1 Bit 6 */
	अचिन्हित allow_disconnect:1;			/* Byte 1 Bit 7 */
	अचिन्हित लघु xfer_len_lo;			/* Bytes 2-3 */
	u32 dma_addr;					/* Bytes 4-7 */
	अचिन्हित अक्षर cdb_len:4;			/* Byte 8 Bits 0-3 */
	अचिन्हित अक्षर xfer_len_hi4:4;			/* Byte 8 Bits 4-7 */
	अचिन्हित अक्षर sense_len;			/* Byte 9 */
	अचिन्हित अक्षर cdb[12];				/* Bytes 10-21 */
	अचिन्हित अक्षर sense[64];			/* Bytes 22-85 */
	अचिन्हित अक्षर status;				/* Byte 86 */
	अचिन्हित अक्षर rsvd2;				/* Byte 87 */
पूर्ण;

/*
 * DAC960 V1 Firmware Scatter/Gather List Type 1 32 Bit Address
 *32 Bit Byte Count काष्ठाure.
 */
काष्ठा myrb_sge अणु
	u32 sge_addr;		/* Bytes 0-3 */
	u32 sge_count;		/* Bytes 4-7 */
पूर्ण;

/*
 * 13 Byte DAC960 V1 Firmware Command Mailbox काष्ठाure.
 * Bytes 13-15 are not used.  The काष्ठाure is padded to 16 bytes क्रम
 * efficient access.
 */
जोड़ myrb_cmd_mbox अणु
	अचिन्हित पूर्णांक words[4];				/* Words 0-3 */
	अचिन्हित अक्षर bytes[16];			/* Bytes 0-15 */
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर rsvd[14];			/* Bytes 2-15 */
	पूर्ण __packed common;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर rsvd1[6];			/* Bytes 2-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर rsvd2[4];			/* Bytes 12-15 */
	पूर्ण __packed type3;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर optype;			/* Byte 2 */
		अचिन्हित अक्षर rsvd1[5];			/* Bytes 3-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर rsvd2[4];			/* Bytes 12-15 */
	पूर्ण __packed type3B;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर rsvd1[5];			/* Bytes 2-6 */
		अचिन्हित अक्षर ldev_num:6;		/* Byte 7 Bits 0-6 */
		अचिन्हित अक्षर स्वतः_restore:1;		/* Byte 7 Bit 7 */
		अचिन्हित अक्षर rsvd2[8];			/* Bytes 8-15 */
	पूर्ण __packed type3C;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर channel;			/* Byte 2 */
		अचिन्हित अक्षर target;			/* Byte 3 */
		क्रमागत myrb_devstate state;		/* Byte 4 */
		अचिन्हित अक्षर rsvd1[3];			/* Bytes 5-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर rsvd2[4];			/* Bytes 12-15 */
	पूर्ण __packed type3D;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर optype;			/* Byte 2 */
		अचिन्हित अक्षर opqual;			/* Byte 3 */
		अचिन्हित लघु ev_seq;			/* Bytes 4-5 */
		अचिन्हित अक्षर rsvd1[2];			/* Bytes 6-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर rsvd2[4];			/* Bytes 12-15 */
	पूर्ण __packed type3E;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर rsvd1[2];			/* Bytes 2-3 */
		अचिन्हित अक्षर rbld_rate;		/* Byte 4 */
		अचिन्हित अक्षर rsvd2[3];			/* Bytes 5-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर rsvd3[4];			/* Bytes 12-15 */
	पूर्ण __packed type3R;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित लघु xfer_len;		/* Bytes 2-3 */
		अचिन्हित पूर्णांक lba;			/* Bytes 4-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर ldev_num;			/* Byte 12 */
		अचिन्हित अक्षर rsvd[3];			/* Bytes 13-15 */
	पूर्ण __packed type4;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		काष्ठा अणु
			अचिन्हित लघु xfer_len:11;	/* Bytes 2-3 */
			अचिन्हित अक्षर ldev_num:5;	/* Byte 3 Bits 3-7 */
		पूर्ण __packed ld;
		अचिन्हित पूर्णांक lba;			/* Bytes 4-7 */
		u32 addr;				/* Bytes 8-11 */
		अचिन्हित अक्षर sg_count:6;		/* Byte 12 Bits 0-5 */
		क्रमागत अणु
			MYRB_SGL_ADDR32_COUNT32 = 0x0,
			MYRB_SGL_ADDR32_COUNT16 = 0x1,
			MYRB_SGL_COUNT32_ADDR32 = 0x2,
			MYRB_SGL_COUNT16_ADDR32 = 0x3
		पूर्ण __packed sg_type:2;	/* Byte 12 Bits 6-7 */
		अचिन्हित अक्षर rsvd[3];			/* Bytes 13-15 */
	पूर्ण __packed type5;
	काष्ठा अणु
		क्रमागत myrb_cmd_opcode opcode;		/* Byte 0 */
		अचिन्हित अक्षर id;			/* Byte 1 */
		अचिन्हित अक्षर opcode2;			/* Byte 2 */
		अचिन्हित अक्षर rsvd1:8;			/* Byte 3 */
		u32 cmd_mbox_addr;			/* Bytes 4-7 */
		u32 stat_mbox_addr;			/* Bytes 8-11 */
		अचिन्हित अक्षर rsvd2[4];			/* Bytes 12-15 */
	पूर्ण __packed typeX;
पूर्ण;

/*
 * DAC960 V1 Firmware Controller Status Mailbox काष्ठाure.
 */
काष्ठा myrb_stat_mbox अणु
	अचिन्हित अक्षर id;		/* Byte 0 */
	अचिन्हित अक्षर rsvd:7;		/* Byte 1 Bits 0-6 */
	अचिन्हित अक्षर valid:1;			/* Byte 1 Bit 7 */
	अचिन्हित लघु status;		/* Bytes 2-3 */
पूर्ण;

काष्ठा myrb_cmdblk अणु
	जोड़ myrb_cmd_mbox mbox;
	अचिन्हित लघु status;
	काष्ठा completion *completion;
	काष्ठा myrb_dcdb *dcdb;
	dma_addr_t dcdb_addr;
	काष्ठा myrb_sge *sgl;
	dma_addr_t sgl_addr;
पूर्ण;

काष्ठा myrb_hba अणु
	अचिन्हित पूर्णांक ldev_block_size;
	अचिन्हित अक्षर ldev_geom_heads;
	अचिन्हित अक्षर ldev_geom_sectors;
	अचिन्हित अक्षर bus_width;
	अचिन्हित लघु stripe_size;
	अचिन्हित लघु segment_size;
	अचिन्हित लघु new_ev_seq;
	अचिन्हित लघु old_ev_seq;
	bool dual_mode_पूर्णांकerface;
	bool bgi_status_supported;
	bool safte_enabled;
	bool need_ldev_info;
	bool need_err_info;
	bool need_rbld;
	bool need_cc_status;
	bool need_bgi_status;
	bool rbld_first;

	काष्ठा pci_dev *pdev;
	काष्ठा Scsi_Host *host;

	काष्ठा workqueue_काष्ठा *work_q;
	अक्षर work_q_name[20];
	काष्ठा delayed_work monitor_work;
	अचिन्हित दीर्घ primary_monitor_समय;
	अचिन्हित दीर्घ secondary_monitor_समय;

	काष्ठा dma_pool *sg_pool;
	काष्ठा dma_pool *dcdb_pool;

	spinlock_t queue_lock;

	व्योम (*qcmd)(काष्ठा myrb_hba *cs, काष्ठा myrb_cmdblk *cmd_blk);
	व्योम (*ग_लिखो_cmd_mbox)(जोड़ myrb_cmd_mbox *next_mbox,
			       जोड़ myrb_cmd_mbox *cmd_mbox);
	व्योम (*get_cmd_mbox)(व्योम __iomem *base);
	व्योम (*disable_पूर्णांकr)(व्योम __iomem *base);
	व्योम (*reset)(व्योम __iomem *base);

	अचिन्हित पूर्णांक ctlr_num;
	अचिन्हित अक्षर model_name[20];
	अचिन्हित अक्षर fw_version[12];

	अचिन्हित पूर्णांक irq;
	phys_addr_t io_addr;
	phys_addr_t pci_addr;
	व्योम __iomem *io_base;
	व्योम __iomem *mmio_base;

	माप_प्रकार cmd_mbox_size;
	dma_addr_t cmd_mbox_addr;
	जोड़ myrb_cmd_mbox *first_cmd_mbox;
	जोड़ myrb_cmd_mbox *last_cmd_mbox;
	जोड़ myrb_cmd_mbox *next_cmd_mbox;
	जोड़ myrb_cmd_mbox *prev_cmd_mbox1;
	जोड़ myrb_cmd_mbox *prev_cmd_mbox2;

	माप_प्रकार stat_mbox_size;
	dma_addr_t stat_mbox_addr;
	काष्ठा myrb_stat_mbox *first_stat_mbox;
	काष्ठा myrb_stat_mbox *last_stat_mbox;
	काष्ठा myrb_stat_mbox *next_stat_mbox;

	काष्ठा myrb_cmdblk dcmd_blk;
	काष्ठा myrb_cmdblk mcmd_blk;
	काष्ठा mutex dcmd_mutex;

	काष्ठा myrb_enquiry *enquiry;
	dma_addr_t enquiry_addr;

	काष्ठा myrb_error_entry *err_table;
	dma_addr_t err_table_addr;

	अचिन्हित लघु last_rbld_status;

	काष्ठा myrb_ldev_info *ldev_info_buf;
	dma_addr_t ldev_info_addr;

	काष्ठा myrb_bgi_status bgi_status;

	काष्ठा mutex dma_mutex;
पूर्ण;

/*
 * DAC960 LA Series Controller Interface Register Offsets.
 */
#घोषणा DAC960_LA_mmio_size		0x80

क्रमागत DAC960_LA_reg_offset अणु
	DAC960_LA_IRQMASK_OFFSET	= 0x34,
	DAC960_LA_CMDOP_OFFSET		= 0x50,
	DAC960_LA_CMDID_OFFSET		= 0x51,
	DAC960_LA_MBOX2_OFFSET		= 0x52,
	DAC960_LA_MBOX3_OFFSET		= 0x53,
	DAC960_LA_MBOX4_OFFSET		= 0x54,
	DAC960_LA_MBOX5_OFFSET		= 0x55,
	DAC960_LA_MBOX6_OFFSET		= 0x56,
	DAC960_LA_MBOX7_OFFSET		= 0x57,
	DAC960_LA_MBOX8_OFFSET		= 0x58,
	DAC960_LA_MBOX9_OFFSET		= 0x59,
	DAC960_LA_MBOX10_OFFSET		= 0x5A,
	DAC960_LA_MBOX11_OFFSET		= 0x5B,
	DAC960_LA_MBOX12_OFFSET		= 0x5C,
	DAC960_LA_STSID_OFFSET		= 0x5D,
	DAC960_LA_STS_OFFSET		= 0x5E,
	DAC960_LA_IDB_OFFSET		= 0x60,
	DAC960_LA_ODB_OFFSET		= 0x61,
	DAC960_LA_ERRSTS_OFFSET		= 0x63,
पूर्ण;

/*
 * DAC960 LA Series Inbound Door Bell Register.
 */
#घोषणा DAC960_LA_IDB_HWMBOX_NEW_CMD 0x01
#घोषणा DAC960_LA_IDB_HWMBOX_ACK_STS 0x02
#घोषणा DAC960_LA_IDB_GEN_IRQ 0x04
#घोषणा DAC960_LA_IDB_CTRL_RESET 0x08
#घोषणा DAC960_LA_IDB_MMBOX_NEW_CMD 0x10

#घोषणा DAC960_LA_IDB_HWMBOX_EMPTY 0x01
#घोषणा DAC960_LA_IDB_INIT_DONE 0x02

/*
 * DAC960 LA Series Outbound Door Bell Register.
 */
#घोषणा DAC960_LA_ODB_HWMBOX_ACK_IRQ 0x01
#घोषणा DAC960_LA_ODB_MMBOX_ACK_IRQ 0x02
#घोषणा DAC960_LA_ODB_HWMBOX_STS_AVAIL 0x01
#घोषणा DAC960_LA_ODB_MMBOX_STS_AVAIL 0x02

/*
 * DAC960 LA Series Interrupt Mask Register.
 */
#घोषणा DAC960_LA_IRQMASK_DISABLE_IRQ 0x04

/*
 * DAC960 LA Series Error Status Register.
 */
#घोषणा DAC960_LA_ERRSTS_PENDING 0x02

/*
 * DAC960 PG Series Controller Interface Register Offsets.
 */
#घोषणा DAC960_PG_mmio_size		0x2000

क्रमागत DAC960_PG_reg_offset अणु
	DAC960_PG_IDB_OFFSET		= 0x0020,
	DAC960_PG_ODB_OFFSET		= 0x002C,
	DAC960_PG_IRQMASK_OFFSET	= 0x0034,
	DAC960_PG_CMDOP_OFFSET		= 0x1000,
	DAC960_PG_CMDID_OFFSET		= 0x1001,
	DAC960_PG_MBOX2_OFFSET		= 0x1002,
	DAC960_PG_MBOX3_OFFSET		= 0x1003,
	DAC960_PG_MBOX4_OFFSET		= 0x1004,
	DAC960_PG_MBOX5_OFFSET		= 0x1005,
	DAC960_PG_MBOX6_OFFSET		= 0x1006,
	DAC960_PG_MBOX7_OFFSET		= 0x1007,
	DAC960_PG_MBOX8_OFFSET		= 0x1008,
	DAC960_PG_MBOX9_OFFSET		= 0x1009,
	DAC960_PG_MBOX10_OFFSET		= 0x100A,
	DAC960_PG_MBOX11_OFFSET		= 0x100B,
	DAC960_PG_MBOX12_OFFSET		= 0x100C,
	DAC960_PG_STSID_OFFSET		= 0x1018,
	DAC960_PG_STS_OFFSET		= 0x101A,
	DAC960_PG_ERRSTS_OFFSET		= 0x103F,
पूर्ण;

/*
 * DAC960 PG Series Inbound Door Bell Register.
 */
#घोषणा DAC960_PG_IDB_HWMBOX_NEW_CMD 0x01
#घोषणा DAC960_PG_IDB_HWMBOX_ACK_STS 0x02
#घोषणा DAC960_PG_IDB_GEN_IRQ 0x04
#घोषणा DAC960_PG_IDB_CTRL_RESET 0x08
#घोषणा DAC960_PG_IDB_MMBOX_NEW_CMD 0x10

#घोषणा DAC960_PG_IDB_HWMBOX_FULL 0x01
#घोषणा DAC960_PG_IDB_INIT_IN_PROGRESS 0x02

/*
 * DAC960 PG Series Outbound Door Bell Register.
 */
#घोषणा DAC960_PG_ODB_HWMBOX_ACK_IRQ 0x01
#घोषणा DAC960_PG_ODB_MMBOX_ACK_IRQ 0x02
#घोषणा DAC960_PG_ODB_HWMBOX_STS_AVAIL 0x01
#घोषणा DAC960_PG_ODB_MMBOX_STS_AVAIL 0x02

/*
 * DAC960 PG Series Interrupt Mask Register.
 */
#घोषणा DAC960_PG_IRQMASK_MSI_MASK1 0x03
#घोषणा DAC960_PG_IRQMASK_DISABLE_IRQ 0x04
#घोषणा DAC960_PG_IRQMASK_MSI_MASK2 0xF8

/*
 * DAC960 PG Series Error Status Register.
 */
#घोषणा DAC960_PG_ERRSTS_PENDING 0x04

/*
 * DAC960 PD Series Controller Interface Register Offsets.
 */
#घोषणा DAC960_PD_mmio_size		0x80

क्रमागत DAC960_PD_reg_offset अणु
	DAC960_PD_CMDOP_OFFSET		= 0x00,
	DAC960_PD_CMDID_OFFSET		= 0x01,
	DAC960_PD_MBOX2_OFFSET		= 0x02,
	DAC960_PD_MBOX3_OFFSET		= 0x03,
	DAC960_PD_MBOX4_OFFSET		= 0x04,
	DAC960_PD_MBOX5_OFFSET		= 0x05,
	DAC960_PD_MBOX6_OFFSET		= 0x06,
	DAC960_PD_MBOX7_OFFSET		= 0x07,
	DAC960_PD_MBOX8_OFFSET		= 0x08,
	DAC960_PD_MBOX9_OFFSET		= 0x09,
	DAC960_PD_MBOX10_OFFSET		= 0x0A,
	DAC960_PD_MBOX11_OFFSET		= 0x0B,
	DAC960_PD_MBOX12_OFFSET		= 0x0C,
	DAC960_PD_STSID_OFFSET		= 0x0D,
	DAC960_PD_STS_OFFSET		= 0x0E,
	DAC960_PD_ERRSTS_OFFSET		= 0x3F,
	DAC960_PD_IDB_OFFSET		= 0x40,
	DAC960_PD_ODB_OFFSET		= 0x41,
	DAC960_PD_IRQEN_OFFSET		= 0x43,
पूर्ण;

/*
 * DAC960 PD Series Inbound Door Bell Register.
 */
#घोषणा DAC960_PD_IDB_HWMBOX_NEW_CMD 0x01
#घोषणा DAC960_PD_IDB_HWMBOX_ACK_STS 0x02
#घोषणा DAC960_PD_IDB_GEN_IRQ 0x04
#घोषणा DAC960_PD_IDB_CTRL_RESET 0x08

#घोषणा DAC960_PD_IDB_HWMBOX_FULL 0x01
#घोषणा DAC960_PD_IDB_INIT_IN_PROGRESS 0x02

/*
 * DAC960 PD Series Outbound Door Bell Register.
 */
#घोषणा DAC960_PD_ODB_HWMBOX_ACK_IRQ 0x01
#घोषणा DAC960_PD_ODB_HWMBOX_STS_AVAIL 0x01

/*
 * DAC960 PD Series Interrupt Enable Register.
 */
#घोषणा DAC960_PD_IRQMASK_ENABLE_IRQ 0x01

/*
 * DAC960 PD Series Error Status Register.
 */
#घोषणा DAC960_PD_ERRSTS_PENDING 0x04

प्रकार पूर्णांक (*myrb_hw_init_t)(काष्ठा pci_dev *pdev,
			      काष्ठा myrb_hba *cb, व्योम __iomem *base);
प्रकार अचिन्हित लघु (*mbox_mmio_init_t)(काष्ठा pci_dev *pdev,
					   व्योम __iomem *base,
					   जोड़ myrb_cmd_mbox *mbox);

काष्ठा myrb_privdata अणु
	myrb_hw_init_t		hw_init;
	irq_handler_t		irq_handler;
	अचिन्हित पूर्णांक		mmio_size;
पूर्ण;

#पूर्ण_अगर /* MYRB_H */
