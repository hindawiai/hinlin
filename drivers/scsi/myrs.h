<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux Driver क्रम Mylex DAC960/AcceleRAID/eXtremeRAID PCI RAID Controllers
 *
 * This driver supports the newer, SCSI-based firmware पूर्णांकerface only.
 *
 * Copyright 2018 Hannes Reinecke, SUSE Linux GmbH <hare@suse.com>
 *
 * Based on the original DAC960 driver, which has
 * Copyright 1998-2001 by Leonard N. Zubkoff <lnz@dandelion.com>
 * Portions Copyright 2002 by Mylex (An IBM Business Unit)
 */

#अगर_अघोषित _MYRS_H
#घोषणा _MYRS_H

#घोषणा MYRS_MAILBOX_TIMEOUT 1000000

#घोषणा MYRS_DCMD_TAG 1
#घोषणा MYRS_MCMD_TAG 2

#घोषणा MYRS_LINE_BUFFER_SIZE 128

#घोषणा MYRS_PRIMARY_MONITOR_INTERVAL (10 * HZ)
#घोषणा MYRS_SECONDARY_MONITOR_INTERVAL (60 * HZ)

/* Maximum number of Scatter/Gather Segments supported */
#घोषणा MYRS_SG_LIMIT		128

/*
 * Number of Command and Status Mailboxes used by the
 * DAC960 V2 Firmware Memory Mailbox Interface.
 */
#घोषणा MYRS_MAX_CMD_MBOX		512
#घोषणा MYRS_MAX_STAT_MBOX		512

#घोषणा MYRS_DCDB_SIZE			16
#घोषणा MYRS_SENSE_SIZE			14

/*
 * DAC960 V2 Firmware Command Opcodes.
 */
क्रमागत myrs_cmd_opcode अणु
	MYRS_CMD_OP_MEMCOPY		= 0x01,
	MYRS_CMD_OP_SCSI_10_PASSTHRU	= 0x02,
	MYRS_CMD_OP_SCSI_255_PASSTHRU	= 0x03,
	MYRS_CMD_OP_SCSI_10		= 0x04,
	MYRS_CMD_OP_SCSI_256		= 0x05,
	MYRS_CMD_OP_IOCTL		= 0x20,
पूर्ण __packed;

/*
 * DAC960 V2 Firmware IOCTL Opcodes.
 */
क्रमागत myrs_ioctl_opcode अणु
	MYRS_IOCTL_GET_CTLR_INFO	= 0x01,
	MYRS_IOCTL_GET_LDEV_INFO_VALID	= 0x03,
	MYRS_IOCTL_GET_PDEV_INFO_VALID	= 0x05,
	MYRS_IOCTL_GET_HEALTH_STATUS	= 0x11,
	MYRS_IOCTL_GET_EVENT		= 0x15,
	MYRS_IOCTL_START_DISCOVERY	= 0x81,
	MYRS_IOCTL_SET_DEVICE_STATE	= 0x82,
	MYRS_IOCTL_INIT_PDEV_START	= 0x84,
	MYRS_IOCTL_INIT_PDEV_STOP	= 0x85,
	MYRS_IOCTL_INIT_LDEV_START	= 0x86,
	MYRS_IOCTL_INIT_LDEV_STOP	= 0x87,
	MYRS_IOCTL_RBLD_DEVICE_START	= 0x88,
	MYRS_IOCTL_RBLD_DEVICE_STOP	= 0x89,
	MYRS_IOCTL_MAKE_CONSISTENT_START = 0x8A,
	MYRS_IOCTL_MAKE_CONSISTENT_STOP = 0x8B,
	MYRS_IOCTL_CC_START		= 0x8C,
	MYRS_IOCTL_CC_STOP		= 0x8D,
	MYRS_IOCTL_SET_MEM_MBOX		= 0x8E,
	MYRS_IOCTL_RESET_DEVICE		= 0x90,
	MYRS_IOCTL_FLUSH_DEVICE_DATA	= 0x91,
	MYRS_IOCTL_PAUSE_DEVICE		= 0x92,
	MYRS_IOCTL_UNPAUS_EDEVICE	= 0x93,
	MYRS_IOCTL_LOCATE_DEVICE	= 0x94,
	MYRS_IOCTL_CREATE_CONFIGURATION = 0xC0,
	MYRS_IOCTL_DELETE_LDEV		= 0xC1,
	MYRS_IOCTL_REPLACE_INTERNALDEVICE = 0xC2,
	MYRS_IOCTL_RENAME_LDEV		= 0xC3,
	MYRS_IOCTL_ADD_CONFIGURATION	= 0xC4,
	MYRS_IOCTL_XLATE_PDEV_TO_LDEV	= 0xC5,
	MYRS_IOCTL_CLEAR_CONFIGURATION	= 0xCA,
पूर्ण __packed;

/*
 * DAC960 V2 Firmware Command Status Codes.
 */
#घोषणा MYRS_STATUS_SUCCESS			0x00
#घोषणा MYRS_STATUS_FAILED			0x02
#घोषणा MYRS_STATUS_DEVICE_BUSY			0x08
#घोषणा MYRS_STATUS_DEVICE_NON_RESPONSIVE	0x0E
#घोषणा MYRS_STATUS_DEVICE_NON_RESPONSIVE2	0x0F
#घोषणा MYRS_STATUS_RESERVATION_CONFLICT	0x18

/*
 * DAC960 V2 Firmware Memory Type काष्ठाure.
 */
काष्ठा myrs_mem_type अणु
	क्रमागत अणु
		MYRS_MEMTYPE_RESERVED	= 0x00,
		MYRS_MEMTYPE_DRAM	= 0x01,
		MYRS_MEMTYPE_EDRAM	= 0x02,
		MYRS_MEMTYPE_EDO	= 0x03,
		MYRS_MEMTYPE_SDRAM	= 0x04,
		MYRS_MEMTYPE_LAST	= 0x1F,
	पूर्ण __packed mem_type:5;	/* Byte 0 Bits 0-4 */
	अचिन्हित rsvd:1;			/* Byte 0 Bit 5 */
	अचिन्हित mem_parity:1;			/* Byte 0 Bit 6 */
	अचिन्हित mem_ecc:1;			/* Byte 0 Bit 7 */
पूर्ण;

/*
 * DAC960 V2 Firmware Processor Type काष्ठाure.
 */
क्रमागत myrs_cpu_type अणु
	MYRS_CPUTYPE_i960CA	= 0x01,
	MYRS_CPUTYPE_i960RD	= 0x02,
	MYRS_CPUTYPE_i960RN	= 0x03,
	MYRS_CPUTYPE_i960RP	= 0x04,
	MYRS_CPUTYPE_NorthBay	= 0x05,
	MYRS_CPUTYPE_StrongArm	= 0x06,
	MYRS_CPUTYPE_i960RM	= 0x07,
पूर्ण __packed;

/*
 * DAC960 V2 Firmware Get Controller Info reply काष्ठाure.
 */
काष्ठा myrs_ctlr_info अणु
	अचिन्हित अक्षर rsvd1;				/* Byte 0 */
	क्रमागत अणु
		MYRS_SCSI_BUS	= 0x00,
		MYRS_Fibre_BUS	= 0x01,
		MYRS_PCI_BUS	= 0x03
	पूर्ण __packed bus;	/* Byte 1 */
	क्रमागत अणु
		MYRS_CTLR_DAC960E	= 0x01,
		MYRS_CTLR_DAC960M	= 0x08,
		MYRS_CTLR_DAC960PD	= 0x10,
		MYRS_CTLR_DAC960PL	= 0x11,
		MYRS_CTLR_DAC960PU	= 0x12,
		MYRS_CTLR_DAC960PE	= 0x13,
		MYRS_CTLR_DAC960PG	= 0x14,
		MYRS_CTLR_DAC960PJ	= 0x15,
		MYRS_CTLR_DAC960PTL0	= 0x16,
		MYRS_CTLR_DAC960PR	= 0x17,
		MYRS_CTLR_DAC960PRL	= 0x18,
		MYRS_CTLR_DAC960PT	= 0x19,
		MYRS_CTLR_DAC1164P	= 0x1A,
		MYRS_CTLR_DAC960PTL1	= 0x1B,
		MYRS_CTLR_EXR2000P	= 0x1C,
		MYRS_CTLR_EXR3000P	= 0x1D,
		MYRS_CTLR_ACCELERAID352 = 0x1E,
		MYRS_CTLR_ACCELERAID170 = 0x1F,
		MYRS_CTLR_ACCELERAID160 = 0x20,
		MYRS_CTLR_DAC960S	= 0x60,
		MYRS_CTLR_DAC960SU	= 0x61,
		MYRS_CTLR_DAC960SX	= 0x62,
		MYRS_CTLR_DAC960SF	= 0x63,
		MYRS_CTLR_DAC960SS	= 0x64,
		MYRS_CTLR_DAC960FL	= 0x65,
		MYRS_CTLR_DAC960LL	= 0x66,
		MYRS_CTLR_DAC960FF	= 0x67,
		MYRS_CTLR_DAC960HP	= 0x68,
		MYRS_CTLR_RAIDBRICK	= 0x69,
		MYRS_CTLR_METEOR_FL	= 0x6A,
		MYRS_CTLR_METEOR_FF	= 0x6B
	पूर्ण __packed ctlr_type;	/* Byte 2 */
	अचिन्हित अक्षर rsvd2;			/* Byte 3 */
	अचिन्हित लघु bus_speed_mhz;		/* Bytes 4-5 */
	अचिन्हित अक्षर bus_width;		/* Byte 6 */
	अचिन्हित अक्षर flash_code;		/* Byte 7 */
	अचिन्हित अक्षर ports_present;		/* Byte 8 */
	अचिन्हित अक्षर rsvd3[7];			/* Bytes 9-15 */
	अचिन्हित अक्षर bus_name[16];		/* Bytes 16-31 */
	अचिन्हित अक्षर ctlr_name[16];		/* Bytes 32-47 */
	अचिन्हित अक्षर rsvd4[16];		/* Bytes 48-63 */
	/* Firmware Release Inक्रमmation */
	अचिन्हित अक्षर fw_major_version;		/* Byte 64 */
	अचिन्हित अक्षर fw_minor_version;		/* Byte 65 */
	अचिन्हित अक्षर fw_turn_number;		/* Byte 66 */
	अचिन्हित अक्षर fw_build_number;		/* Byte 67 */
	अचिन्हित अक्षर fw_release_day;		/* Byte 68 */
	अचिन्हित अक्षर fw_release_month;		/* Byte 69 */
	अचिन्हित अक्षर fw_release_year_hi;	/* Byte 70 */
	अचिन्हित अक्षर fw_release_year_lo;	/* Byte 71 */
	/* Hardware Release Inक्रमmation */
	अचिन्हित अक्षर hw_rev;			/* Byte 72 */
	अचिन्हित अक्षर rsvd5[3];			/* Bytes 73-75 */
	अचिन्हित अक्षर hw_release_day;		/* Byte 76 */
	अचिन्हित अक्षर hw_release_month;		/* Byte 77 */
	अचिन्हित अक्षर hw_release_year_hi;	/* Byte 78 */
	अचिन्हित अक्षर hw_release_year_lo;	/* Byte 79 */
	/* Hardware Manufacturing Inक्रमmation */
	अचिन्हित अक्षर manuf_batch_num;		/* Byte 80 */
	अचिन्हित अक्षर rsvd6;			/* Byte 81 */
	अचिन्हित अक्षर manuf_plant_num;		/* Byte 82 */
	अचिन्हित अक्षर rsvd7;			/* Byte 83 */
	अचिन्हित अक्षर hw_manuf_day;		/* Byte 84 */
	अचिन्हित अक्षर hw_manuf_month;		/* Byte 85 */
	अचिन्हित अक्षर hw_manuf_year_hi;		/* Byte 86 */
	अचिन्हित अक्षर hw_manuf_year_lo;		/* Byte 87 */
	अचिन्हित अक्षर max_pd_per_xld;		/* Byte 88 */
	अचिन्हित अक्षर max_ild_per_xld;		/* Byte 89 */
	अचिन्हित लघु nvram_size_kb;		/* Bytes 90-91 */
	अचिन्हित अक्षर max_xld;			/* Byte 92 */
	अचिन्हित अक्षर rsvd8[3];			/* Bytes 93-95 */
	/* Unique Inक्रमmation per Controller */
	अचिन्हित अक्षर serial_number[16];	/* Bytes 96-111 */
	अचिन्हित अक्षर rsvd9[16];		/* Bytes 112-127 */
	/* Venकरोr Inक्रमmation */
	अचिन्हित अक्षर rsvd10[3];		/* Bytes 128-130 */
	अचिन्हित अक्षर oem_code;			/* Byte 131 */
	अचिन्हित अक्षर venकरोr[16];		/* Bytes 132-147 */
	/* Other Physical/Controller/Operation Inक्रमmation */
	अचिन्हित अक्षर bbu_present:1;		/* Byte 148 Bit 0 */
	अचिन्हित अक्षर cluster_mode:1;		/* Byte 148 Bit 1 */
	अचिन्हित अक्षर rsvd11:6;			/* Byte 148 Bits 2-7 */
	अचिन्हित अक्षर rsvd12[3];		/* Bytes 149-151 */
	/* Physical Device Scan Inक्रमmation */
	अचिन्हित अक्षर pscan_active:1;		/* Byte 152 Bit 0 */
	अचिन्हित अक्षर rsvd13:7;			/* Byte 152 Bits 1-7 */
	अचिन्हित अक्षर pscan_chan;		/* Byte 153 */
	अचिन्हित अक्षर pscan_target;		/* Byte 154 */
	अचिन्हित अक्षर pscan_lun;		/* Byte 155 */
	/* Maximum Command Data Transfer Sizes */
	अचिन्हित लघु max_transfer_size;	/* Bytes 156-157 */
	अचिन्हित लघु max_sge;			/* Bytes 158-159 */
	/* Logical/Physical Device Counts */
	अचिन्हित लघु ldev_present;		/* Bytes 160-161 */
	अचिन्हित लघु ldev_critical;		/* Bytes 162-163 */
	अचिन्हित लघु ldev_offline;		/* Bytes 164-165 */
	अचिन्हित लघु pdev_present;		/* Bytes 166-167 */
	अचिन्हित लघु pdisk_present;		/* Bytes 168-169 */
	अचिन्हित लघु pdisk_critical;		/* Bytes 170-171 */
	अचिन्हित लघु pdisk_offline;		/* Bytes 172-173 */
	अचिन्हित लघु max_tcq;			/* Bytes 174-175 */
	/* Channel and Target ID Inक्रमmation */
	अचिन्हित अक्षर physchan_present;		/* Byte 176 */
	अचिन्हित अक्षर virtchan_present;		/* Byte 177 */
	अचिन्हित अक्षर physchan_max;		/* Byte 178 */
	अचिन्हित अक्षर virtchan_max;		/* Byte 179 */
	अचिन्हित अक्षर max_tarमाला_लो[16];		/* Bytes 180-195 */
	अचिन्हित अक्षर rsvd14[12];		/* Bytes 196-207 */
	/* Memory/Cache Inक्रमmation */
	अचिन्हित लघु mem_size_mb;		/* Bytes 208-209 */
	अचिन्हित लघु cache_size_mb;		/* Bytes 210-211 */
	अचिन्हित पूर्णांक valid_cache_bytes;		/* Bytes 212-215 */
	अचिन्हित पूर्णांक dirty_cache_bytes;		/* Bytes 216-219 */
	अचिन्हित लघु mem_speed_mhz;		/* Bytes 220-221 */
	अचिन्हित अक्षर mem_data_width;		/* Byte 222 */
	काष्ठा myrs_mem_type mem_type;		/* Byte 223 */
	अचिन्हित अक्षर cache_mem_type_name[16];	/* Bytes 224-239 */
	/* Execution Memory Inक्रमmation */
	अचिन्हित लघु exec_mem_size_mb;	/* Bytes 240-241 */
	अचिन्हित लघु exec_l2_cache_size_mb;	/* Bytes 242-243 */
	अचिन्हित अक्षर rsvd15[8];		/* Bytes 244-251 */
	अचिन्हित लघु exec_mem_speed_mhz;	/* Bytes 252-253 */
	अचिन्हित अक्षर exec_mem_data_width;	/* Byte 254 */
	काष्ठा myrs_mem_type exec_mem_type;	/* Byte 255 */
	अचिन्हित अक्षर exec_mem_type_name[16];	/* Bytes 256-271 */
	/* CPU Type Inक्रमmation */
	काष्ठा अणु				/* Bytes 272-335 */
		अचिन्हित लघु cpu_speed_mhz;
		क्रमागत myrs_cpu_type cpu_type;
		अचिन्हित अक्षर cpu_count;
		अचिन्हित अक्षर rsvd16[12];
		अचिन्हित अक्षर cpu_name[16];
	पूर्ण __packed cpu[2];
	/* Debugging/Profiling/Command Time Tracing Inक्रमmation */
	अचिन्हित लघु cur_prof_page_num;	/* Bytes 336-337 */
	अचिन्हित लघु num_prof_रुकोers;	/* Bytes 338-339 */
	अचिन्हित लघु cur_trace_page_num;	/* Bytes 340-341 */
	अचिन्हित लघु num_trace_रुकोers;	/* Bytes 342-343 */
	अचिन्हित अक्षर rsvd18[8];		/* Bytes 344-351 */
	/* Error Counters on Physical Devices */
	अचिन्हित लघु pdev_bus_resets;		/* Bytes 352-353 */
	अचिन्हित लघु pdev_parity_errors;	/* Bytes 355-355 */
	अचिन्हित लघु pdev_soft_errors;	/* Bytes 356-357 */
	अचिन्हित लघु pdev_cmds_failed;	/* Bytes 358-359 */
	अचिन्हित लघु pdev_misc_errors;	/* Bytes 360-361 */
	अचिन्हित लघु pdev_cmd_समयouts;	/* Bytes 362-363 */
	अचिन्हित लघु pdev_sel_समयouts;	/* Bytes 364-365 */
	अचिन्हित लघु pdev_retries_करोne;	/* Bytes 366-367 */
	अचिन्हित लघु pdev_पातs_करोne;	/* Bytes 368-369 */
	अचिन्हित लघु pdev_host_पातs_करोne;	/* Bytes 370-371 */
	अचिन्हित लघु pdev_predicted_failures;	/* Bytes 372-373 */
	अचिन्हित लघु pdev_host_cmds_failed;	/* Bytes 374-375 */
	अचिन्हित लघु pdev_hard_errors;	/* Bytes 376-377 */
	अचिन्हित अक्षर rsvd19[6];		/* Bytes 378-383 */
	/* Error Counters on Logical Devices */
	अचिन्हित लघु ldev_soft_errors;	/* Bytes 384-385 */
	अचिन्हित लघु ldev_cmds_failed;	/* Bytes 386-387 */
	अचिन्हित लघु ldev_host_पातs_करोne;	/* Bytes 388-389 */
	अचिन्हित अक्षर rsvd20[2];		/* Bytes 390-391 */
	/* Error Counters on Controller */
	अचिन्हित लघु ctlr_mem_errors;		/* Bytes 392-393 */
	अचिन्हित लघु ctlr_host_पातs_करोne;	/* Bytes 394-395 */
	अचिन्हित अक्षर rsvd21[4];		/* Bytes 396-399 */
	/* Long Duration Activity Inक्रमmation */
	अचिन्हित लघु bg_init_active;		/* Bytes 400-401 */
	अचिन्हित लघु ldev_init_active;	/* Bytes 402-403 */
	अचिन्हित लघु pdev_init_active;	/* Bytes 404-405 */
	अचिन्हित लघु cc_active;		/* Bytes 406-407 */
	अचिन्हित लघु rbld_active;		/* Bytes 408-409 */
	अचिन्हित लघु exp_active;		/* Bytes 410-411 */
	अचिन्हित लघु patrol_active;		/* Bytes 412-413 */
	अचिन्हित अक्षर rsvd22[2];		/* Bytes 414-415 */
	/* Flash ROM Inक्रमmation */
	अचिन्हित अक्षर flash_type;		/* Byte 416 */
	अचिन्हित अक्षर rsvd23;			/* Byte 417 */
	अचिन्हित लघु flash_size_MB;		/* Bytes 418-419 */
	अचिन्हित पूर्णांक flash_limit;		/* Bytes 420-423 */
	अचिन्हित पूर्णांक flash_count;		/* Bytes 424-427 */
	अचिन्हित अक्षर rsvd24[4];		/* Bytes 428-431 */
	अचिन्हित अक्षर flash_type_name[16];	/* Bytes 432-447 */
	/* Firmware Run Time Inक्रमmation */
	अचिन्हित अक्षर rbld_rate;		/* Byte 448 */
	अचिन्हित अक्षर bg_init_rate;		/* Byte 449 */
	अचिन्हित अक्षर fg_init_rate;		/* Byte 450 */
	अचिन्हित अक्षर cc_rate;			/* Byte 451 */
	अचिन्हित अक्षर rsvd25[4];		/* Bytes 452-455 */
	अचिन्हित पूर्णांक max_dp;			/* Bytes 456-459 */
	अचिन्हित पूर्णांक मुक्त_dp;			/* Bytes 460-463 */
	अचिन्हित पूर्णांक max_iop;			/* Bytes 464-467 */
	अचिन्हित पूर्णांक मुक्त_iop;			/* Bytes 468-471 */
	अचिन्हित लघु max_combined_len;	/* Bytes 472-473 */
	अचिन्हित लघु num_cfg_groups;		/* Bytes 474-475 */
	अचिन्हित installation_पात_status:1;	/* Byte 476 Bit 0 */
	अचिन्हित मुख्यt_mode_status:1;		/* Byte 476 Bit 1 */
	अचिन्हित rsvd26:6;			/* Byte 476 Bits 2-7 */
	अचिन्हित अक्षर rsvd27[6];		/* Bytes 477-511 */
	अचिन्हित अक्षर rsvd28[512];		/* Bytes 512-1023 */
पूर्ण;

/*
 * DAC960 V2 Firmware Device State type.
 */
क्रमागत myrs_devstate अणु
	MYRS_DEVICE_UNCONFIGURED	= 0x00,
	MYRS_DEVICE_ONLINE		= 0x01,
	MYRS_DEVICE_REBUILD		= 0x03,
	MYRS_DEVICE_MISSING		= 0x04,
	MYRS_DEVICE_SUSPECTED_CRITICAL	= 0x05,
	MYRS_DEVICE_OFFLINE		= 0x08,
	MYRS_DEVICE_CRITICAL		= 0x09,
	MYRS_DEVICE_SUSPECTED_DEAD	= 0x0C,
	MYRS_DEVICE_COMMANDED_OFFLINE	= 0x10,
	MYRS_DEVICE_STANDBY		= 0x21,
	MYRS_DEVICE_INVALID_STATE	= 0xFF,
पूर्ण __packed;

/*
 * DAC960 V2 RAID Levels
 */
क्रमागत myrs_raid_level अणु
	MYRS_RAID_LEVEL0	= 0x0,     /* RAID 0 */
	MYRS_RAID_LEVEL1	= 0x1,     /* RAID 1 */
	MYRS_RAID_LEVEL3	= 0x3,     /* RAID 3 right asymmetric parity */
	MYRS_RAID_LEVEL5	= 0x5,     /* RAID 5 right asymmetric parity */
	MYRS_RAID_LEVEL6	= 0x6,     /* RAID 6 (Mylex RAID 6) */
	MYRS_RAID_JBOD		= 0x7,     /* RAID 7 (JBOD) */
	MYRS_RAID_NEWSPAN	= 0x8,     /* New Mylex SPAN */
	MYRS_RAID_LEVEL3F	= 0x9,     /* RAID 3 fixed parity */
	MYRS_RAID_LEVEL3L	= 0xb,     /* RAID 3 left symmetric parity */
	MYRS_RAID_SPAN		= 0xc,     /* current spanning implementation */
	MYRS_RAID_LEVEL5L	= 0xd,     /* RAID 5 left symmetric parity */
	MYRS_RAID_LEVELE	= 0xe,     /* RAID E (concatenation) */
	MYRS_RAID_PHYSICAL	= 0xf,     /* physical device */
पूर्ण __packed;

क्रमागत myrs_stripe_size अणु
	MYRS_STRIPE_SIZE_0	= 0x0,	/* no stripe (RAID 1, RAID 7, etc) */
	MYRS_STRIPE_SIZE_512B	= 0x1,
	MYRS_STRIPE_SIZE_1K	= 0x2,
	MYRS_STRIPE_SIZE_2K	= 0x3,
	MYRS_STRIPE_SIZE_4K	= 0x4,
	MYRS_STRIPE_SIZE_8K	= 0x5,
	MYRS_STRIPE_SIZE_16K	= 0x6,
	MYRS_STRIPE_SIZE_32K	= 0x7,
	MYRS_STRIPE_SIZE_64K	= 0x8,
	MYRS_STRIPE_SIZE_128K	= 0x9,
	MYRS_STRIPE_SIZE_256K	= 0xa,
	MYRS_STRIPE_SIZE_512K	= 0xb,
	MYRS_STRIPE_SIZE_1M	= 0xc,
पूर्ण __packed;

क्रमागत myrs_cacheline_size अणु
	MYRS_CACHELINE_ZERO	= 0x0,	/* caching cannot be enabled */
	MYRS_CACHELINE_512B	= 0x1,
	MYRS_CACHELINE_1K	= 0x2,
	MYRS_CACHELINE_2K	= 0x3,
	MYRS_CACHELINE_4K	= 0x4,
	MYRS_CACHELINE_8K	= 0x5,
	MYRS_CACHELINE_16K	= 0x6,
	MYRS_CACHELINE_32K	= 0x7,
	MYRS_CACHELINE_64K	= 0x8,
पूर्ण __packed;

/*
 * DAC960 V2 Firmware Get Logical Device Info reply काष्ठाure.
 */
काष्ठा myrs_ldev_info अणु
	अचिन्हित अक्षर ctlr;			/* Byte 0 */
	अचिन्हित अक्षर channel;			/* Byte 1 */
	अचिन्हित अक्षर target;			/* Byte 2 */
	अचिन्हित अक्षर lun;			/* Byte 3 */
	क्रमागत myrs_devstate dev_state;		/* Byte 4 */
	अचिन्हित अक्षर raid_level;		/* Byte 5 */
	क्रमागत myrs_stripe_size stripe_size;	/* Byte 6 */
	क्रमागत myrs_cacheline_size cacheline_size; /* Byte 7 */
	काष्ठा अणु
		क्रमागत अणु
			MYRS_READCACHE_DISABLED		= 0x0,
			MYRS_READCACHE_ENABLED		= 0x1,
			MYRS_READAHEAD_ENABLED		= 0x2,
			MYRS_INTELLIGENT_READAHEAD_ENABLED = 0x3,
			MYRS_READCACHE_LAST		= 0x7,
		पूर्ण __packed rce:3; /* Byte 8 Bits 0-2 */
		क्रमागत अणु
			MYRS_WRITECACHE_DISABLED	= 0x0,
			MYRS_LOGICALDEVICE_RO		= 0x1,
			MYRS_WRITECACHE_ENABLED		= 0x2,
			MYRS_INTELLIGENT_WRITECACHE_ENABLED = 0x3,
			MYRS_WRITECACHE_LAST		= 0x7,
		पूर्ण __packed wce:3; /* Byte 8 Bits 3-5 */
		अचिन्हित rsvd1:1;		/* Byte 8 Bit 6 */
		अचिन्हित ldev_init_करोne:1;	/* Byte 8 Bit 7 */
	पूर्ण ldev_control;				/* Byte 8 */
	/* Logical Device Operations Status */
	अचिन्हित अक्षर cc_active:1;		/* Byte 9 Bit 0 */
	अचिन्हित अक्षर rbld_active:1;		/* Byte 9 Bit 1 */
	अचिन्हित अक्षर bg_init_active:1;		/* Byte 9 Bit 2 */
	अचिन्हित अक्षर fg_init_active:1;		/* Byte 9 Bit 3 */
	अचिन्हित अक्षर migration_active:1;	/* Byte 9 Bit 4 */
	अचिन्हित अक्षर patrol_active:1;		/* Byte 9 Bit 5 */
	अचिन्हित अक्षर rsvd2:2;			/* Byte 9 Bits 6-7 */
	अचिन्हित अक्षर raid5_ग_लिखोupdate;	/* Byte 10 */
	अचिन्हित अक्षर raid5_algo;		/* Byte 11 */
	अचिन्हित लघु ldev_num;		/* Bytes 12-13 */
	/* BIOS Info */
	अचिन्हित अक्षर bios_disabled:1;		/* Byte 14 Bit 0 */
	अचिन्हित अक्षर cdrom_boot:1;		/* Byte 14 Bit 1 */
	अचिन्हित अक्षर drv_coercion:1;		/* Byte 14 Bit 2 */
	अचिन्हित अक्षर ग_लिखो_same_disabled:1;	/* Byte 14 Bit 3 */
	अचिन्हित अक्षर hba_mode:1;		/* Byte 14 Bit 4 */
	क्रमागत अणु
		MYRS_GEOMETRY_128_32	= 0x0,
		MYRS_GEOMETRY_255_63	= 0x1,
		MYRS_GEOMETRY_RSVD1	= 0x2,
		MYRS_GEOMETRY_RSVD2	= 0x3
	पूर्ण __packed drv_geom:2;	/* Byte 14 Bits 5-6 */
	अचिन्हित अक्षर super_ra_enabled:1;	/* Byte 14 Bit 7 */
	अचिन्हित अक्षर rsvd3;			/* Byte 15 */
	/* Error Counters */
	अचिन्हित लघु soft_errs;		/* Bytes 16-17 */
	अचिन्हित लघु cmds_failed;		/* Bytes 18-19 */
	अचिन्हित लघु cmds_पातed;		/* Bytes 20-21 */
	अचिन्हित लघु deferred_ग_लिखो_errs;	/* Bytes 22-23 */
	अचिन्हित पूर्णांक rsvd4;			/* Bytes 24-27 */
	अचिन्हित पूर्णांक rsvd5;			/* Bytes 28-31 */
	/* Device Size Inक्रमmation */
	अचिन्हित लघु rsvd6;			/* Bytes 32-33 */
	अचिन्हित लघु devsize_bytes;		/* Bytes 34-35 */
	अचिन्हित पूर्णांक orig_devsize;		/* Bytes 36-39 */
	अचिन्हित पूर्णांक cfg_devsize;		/* Bytes 40-43 */
	अचिन्हित पूर्णांक rsvd7;			/* Bytes 44-47 */
	अचिन्हित अक्षर ldev_name[32];		/* Bytes 48-79 */
	अचिन्हित अक्षर inquiry[36];		/* Bytes 80-115 */
	अचिन्हित अक्षर rsvd8[12];		/* Bytes 116-127 */
	u64 last_पढ़ो_lba;			/* Bytes 128-135 */
	u64 last_ग_लिखो_lba;			/* Bytes 136-143 */
	u64 cc_lba;				/* Bytes 144-151 */
	u64 rbld_lba;				/* Bytes 152-159 */
	u64 bg_init_lba;			/* Bytes 160-167 */
	u64 fg_init_lba;			/* Bytes 168-175 */
	u64 migration_lba;			/* Bytes 176-183 */
	u64 patrol_lba;				/* Bytes 184-191 */
	अचिन्हित अक्षर rsvd9[64];		/* Bytes 192-255 */
पूर्ण;

/*
 * DAC960 V2 Firmware Get Physical Device Info reply काष्ठाure.
 */
काष्ठा myrs_pdev_info अणु
	अचिन्हित अक्षर rsvd1;			/* Byte 0 */
	अचिन्हित अक्षर channel;			/* Byte 1 */
	अचिन्हित अक्षर target;			/* Byte 2 */
	अचिन्हित अक्षर lun;			/* Byte 3 */
	/* Configuration Status Bits */
	अचिन्हित अक्षर pdev_fault_tolerant:1;	/* Byte 4 Bit 0 */
	अचिन्हित अक्षर pdev_connected:1;		/* Byte 4 Bit 1 */
	अचिन्हित अक्षर pdev_local_to_ctlr:1;	/* Byte 4 Bit 2 */
	अचिन्हित अक्षर rsvd2:5;			/* Byte 4 Bits 3-7 */
	/* Multiple Host/Controller Status Bits */
	अचिन्हित अक्षर remote_host_dead:1;	/* Byte 5 Bit 0 */
	अचिन्हित अक्षर हटाओ_ctlr_dead:1;	/* Byte 5 Bit 1 */
	अचिन्हित अक्षर rsvd3:6;			/* Byte 5 Bits 2-7 */
	क्रमागत myrs_devstate dev_state;		/* Byte 6 */
	अचिन्हित अक्षर nego_data_width;		/* Byte 7 */
	अचिन्हित लघु nego_sync_rate;		/* Bytes 8-9 */
	/* Multiported Physical Device Inक्रमmation */
	अचिन्हित अक्षर num_ports;		/* Byte 10 */
	अचिन्हित अक्षर drv_access_biपंचांगap;	/* Byte 11 */
	अचिन्हित पूर्णांक rsvd4;			/* Bytes 12-15 */
	अचिन्हित अक्षर ip_address[16];		/* Bytes 16-31 */
	अचिन्हित लघु max_tags;		/* Bytes 32-33 */
	/* Physical Device Operations Status */
	अचिन्हित अक्षर cc_in_progress:1;		/* Byte 34 Bit 0 */
	अचिन्हित अक्षर rbld_in_progress:1;	/* Byte 34 Bit 1 */
	अचिन्हित अक्षर makecc_in_progress:1;	/* Byte 34 Bit 2 */
	अचिन्हित अक्षर pdevinit_in_progress:1;	/* Byte 34 Bit 3 */
	अचिन्हित अक्षर migration_in_progress:1;	/* Byte 34 Bit 4 */
	अचिन्हित अक्षर patrol_in_progress:1;	/* Byte 34 Bit 5 */
	अचिन्हित अक्षर rsvd5:2;			/* Byte 34 Bits 6-7 */
	अचिन्हित अक्षर दीर्घ_op_status;		/* Byte 35 */
	अचिन्हित अक्षर parity_errs;		/* Byte 36 */
	अचिन्हित अक्षर soft_errs;		/* Byte 37 */
	अचिन्हित अक्षर hard_errs;		/* Byte 38 */
	अचिन्हित अक्षर misc_errs;		/* Byte 39 */
	अचिन्हित अक्षर cmd_समयouts;		/* Byte 40 */
	अचिन्हित अक्षर retries;			/* Byte 41 */
	अचिन्हित अक्षर पातs;			/* Byte 42 */
	अचिन्हित अक्षर pred_failures;		/* Byte 43 */
	अचिन्हित पूर्णांक rsvd6;			/* Bytes 44-47 */
	अचिन्हित लघु rsvd7;			/* Bytes 48-49 */
	अचिन्हित लघु devsize_bytes;		/* Bytes 50-51 */
	अचिन्हित पूर्णांक orig_devsize;		/* Bytes 52-55 */
	अचिन्हित पूर्णांक cfg_devsize;		/* Bytes 56-59 */
	अचिन्हित पूर्णांक rsvd8;			/* Bytes 60-63 */
	अचिन्हित अक्षर pdev_name[16];		/* Bytes 64-79 */
	अचिन्हित अक्षर rsvd9[16];		/* Bytes 80-95 */
	अचिन्हित अक्षर rsvd10[32];		/* Bytes 96-127 */
	अचिन्हित अक्षर inquiry[36];		/* Bytes 128-163 */
	अचिन्हित अक्षर rsvd11[20];		/* Bytes 164-183 */
	अचिन्हित अक्षर rsvd12[8];		/* Bytes 184-191 */
	u64 last_पढ़ो_lba;			/* Bytes 192-199 */
	u64 last_ग_लिखो_lba;			/* Bytes 200-207 */
	u64 cc_lba;				/* Bytes 208-215 */
	u64 rbld_lba;				/* Bytes 216-223 */
	u64 makecc_lba;				/* Bytes 224-231 */
	u64 devinit_lba;			/* Bytes 232-239 */
	u64 migration_lba;			/* Bytes 240-247 */
	u64 patrol_lba;				/* Bytes 248-255 */
	अचिन्हित अक्षर rsvd13[256];		/* Bytes 256-511 */
पूर्ण;

/*
 * DAC960 V2 Firmware Health Status Buffer काष्ठाure.
 */
काष्ठा myrs_fwstat अणु
	अचिन्हित पूर्णांक upसमय_usecs;		/* Bytes 0-3 */
	अचिन्हित पूर्णांक upसमय_msecs;		/* Bytes 4-7 */
	अचिन्हित पूर्णांक seconds;			/* Bytes 8-11 */
	अचिन्हित अक्षर rsvd1[4];			/* Bytes 12-15 */
	अचिन्हित पूर्णांक epoch;			/* Bytes 16-19 */
	अचिन्हित अक्षर rsvd2[4];			/* Bytes 20-23 */
	अचिन्हित पूर्णांक dbg_msgbuf_idx;		/* Bytes 24-27 */
	अचिन्हित पूर्णांक coded_msgbuf_idx;		/* Bytes 28-31 */
	अचिन्हित पूर्णांक cur_समयtrace_page;	/* Bytes 32-35 */
	अचिन्हित पूर्णांक cur_prof_page;		/* Bytes 36-39 */
	अचिन्हित पूर्णांक next_evseq;		/* Bytes 40-43 */
	अचिन्हित अक्षर rsvd3[4];			/* Bytes 44-47 */
	अचिन्हित अक्षर rsvd4[16];		/* Bytes 48-63 */
	अचिन्हित अक्षर rsvd5[64];		/* Bytes 64-127 */
पूर्ण;

/*
 * DAC960 V2 Firmware Get Event reply काष्ठाure.
 */
काष्ठा myrs_event अणु
	अचिन्हित पूर्णांक ev_seq;			/* Bytes 0-3 */
	अचिन्हित पूर्णांक ev_समय;			/* Bytes 4-7 */
	अचिन्हित पूर्णांक ev_code;			/* Bytes 8-11 */
	अचिन्हित अक्षर rsvd1;			/* Byte 12 */
	अचिन्हित अक्षर channel;			/* Byte 13 */
	अचिन्हित अक्षर target;			/* Byte 14 */
	अचिन्हित अक्षर lun;			/* Byte 15 */
	अचिन्हित पूर्णांक rsvd2;			/* Bytes 16-19 */
	अचिन्हित पूर्णांक ev_parm;			/* Bytes 20-23 */
	अचिन्हित अक्षर sense_data[40];		/* Bytes 24-63 */
पूर्ण;

/*
 * DAC960 V2 Firmware Command Control Bits काष्ठाure.
 */
काष्ठा myrs_cmd_ctrl अणु
	अचिन्हित अक्षर fua:1;			/* Byte 0 Bit 0 */
	अचिन्हित अक्षर disable_pgout:1;		/* Byte 0 Bit 1 */
	अचिन्हित अक्षर rsvd1:1;			/* Byte 0 Bit 2 */
	अचिन्हित अक्षर add_sge_mem:1;		/* Byte 0 Bit 3 */
	अचिन्हित अक्षर dma_ctrl_to_host:1;	/* Byte 0 Bit 4 */
	अचिन्हित अक्षर rsvd2:1;			/* Byte 0 Bit 5 */
	अचिन्हित अक्षर no_स्वतःsense:1;		/* Byte 0 Bit 6 */
	अचिन्हित अक्षर disc_prohibited:1;	/* Byte 0 Bit 7 */
पूर्ण;

/*
 * DAC960 V2 Firmware Command Timeout काष्ठाure.
 */
काष्ठा myrs_cmd_पंचांगo अणु
	अचिन्हित अक्षर पंचांगo_val:6;			/* Byte 0 Bits 0-5 */
	क्रमागत अणु
		MYRS_TMO_SCALE_SECONDS	= 0,
		MYRS_TMO_SCALE_MINUTES	= 1,
		MYRS_TMO_SCALE_HOURS	= 2,
		MYRS_TMO_SCALE_RESERVED = 3
	पूर्ण __packed पंचांगo_scale:2;		/* Byte 0 Bits 6-7 */
पूर्ण;

/*
 * DAC960 V2 Firmware Physical Device काष्ठाure.
 */
काष्ठा myrs_pdev अणु
	अचिन्हित अक्षर lun;			/* Byte 0 */
	अचिन्हित अक्षर target;			/* Byte 1 */
	अचिन्हित अक्षर channel:3;		/* Byte 2 Bits 0-2 */
	अचिन्हित अक्षर ctlr:5;			/* Byte 2 Bits 3-7 */
पूर्ण __packed;

/*
 * DAC960 V2 Firmware Logical Device काष्ठाure.
 */
काष्ठा myrs_ldev अणु
	अचिन्हित लघु ldev_num;		/* Bytes 0-1 */
	अचिन्हित अक्षर rsvd:3;			/* Byte 2 Bits 0-2 */
	अचिन्हित अक्षर ctlr:5;			/* Byte 2 Bits 3-7 */
पूर्ण __packed;

/*
 * DAC960 V2 Firmware Operation Device type.
 */
क्रमागत myrs_opdev अणु
	MYRS_PHYSICAL_DEVICE	= 0x00,
	MYRS_RAID_DEVICE	= 0x01,
	MYRS_PHYSICAL_CHANNEL	= 0x02,
	MYRS_RAID_CHANNEL	= 0x03,
	MYRS_PHYSICAL_CONTROLLER = 0x04,
	MYRS_RAID_CONTROLLER	= 0x05,
	MYRS_CONFIGURATION_GROUP = 0x10,
	MYRS_ENCLOSURE		= 0x11,
पूर्ण __packed;

/*
 * DAC960 V2 Firmware Translate Physical To Logical Device काष्ठाure.
 */
काष्ठा myrs_devmap अणु
	अचिन्हित लघु ldev_num;		/* Bytes 0-1 */
	अचिन्हित लघु rsvd;			/* Bytes 2-3 */
	अचिन्हित अक्षर prev_boot_ctlr;		/* Byte 4 */
	अचिन्हित अक्षर prev_boot_channel;	/* Byte 5 */
	अचिन्हित अक्षर prev_boot_target;		/* Byte 6 */
	अचिन्हित अक्षर prev_boot_lun;		/* Byte 7 */
पूर्ण;

/*
 * DAC960 V2 Firmware Scatter/Gather List Entry काष्ठाure.
 */
काष्ठा myrs_sge अणु
	u64 sge_addr;			/* Bytes 0-7 */
	u64 sge_count;			/* Bytes 8-15 */
पूर्ण;

/*
 * DAC960 V2 Firmware Data Transfer Memory Address काष्ठाure.
 */
जोड़ myrs_sgl अणु
	काष्ठा myrs_sge sge[2]; /* Bytes 0-31 */
	काष्ठा अणु
		अचिन्हित लघु sge0_len;	/* Bytes 0-1 */
		अचिन्हित लघु sge1_len;	/* Bytes 2-3 */
		अचिन्हित लघु sge2_len;	/* Bytes 4-5 */
		अचिन्हित लघु rsvd;		/* Bytes 6-7 */
		u64 sge0_addr;			/* Bytes 8-15 */
		u64 sge1_addr;			/* Bytes 16-23 */
		u64 sge2_addr;			/* Bytes 24-31 */
	पूर्ण ext;
पूर्ण;

/*
 * 64 Byte DAC960 V2 Firmware Command Mailbox काष्ठाure.
 */
जोड़ myrs_cmd_mbox अणु
	अचिन्हित पूर्णांक words[16];				/* Words 0-15 */
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		अचिन्हित पूर्णांक rsvd1:24;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित अक्षर rsvd2[10];		/* Bytes 22-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण common;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size;				/* Bytes 4-7 */
		u64 sense_addr;				/* Bytes 8-15 */
		काष्ठा myrs_pdev pdev;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		अचिन्हित अक्षर cdb_len;			/* Byte 21 */
		अचिन्हित अक्षर cdb[10];			/* Bytes 22-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण SCSI_10;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size;				/* Bytes 4-7 */
		u64 sense_addr;				/* Bytes 8-15 */
		काष्ठा myrs_pdev pdev;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		अचिन्हित अक्षर cdb_len;			/* Byte 21 */
		अचिन्हित लघु rsvd;			/* Bytes 22-23 */
		u64 cdb_addr;				/* Bytes 24-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण SCSI_255;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		अचिन्हित लघु rsvd1;			/* Bytes 16-17 */
		अचिन्हित अक्षर ctlr_num;			/* Byte 18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित अक्षर rsvd2[10];		/* Bytes 22-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण ctlr_info;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		काष्ठा myrs_ldev ldev;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित अक्षर rsvd[10];			/* Bytes 22-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण ldev_info;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		काष्ठा myrs_pdev pdev;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित अक्षर rsvd[10];			/* Bytes 22-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण pdev_info;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		अचिन्हित लघु evnum_upper;		/* Bytes 16-17 */
		अचिन्हित अक्षर ctlr_num;			/* Byte 18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित लघु evnum_lower;		/* Bytes 22-23 */
		अचिन्हित अक्षर rsvd[8];			/* Bytes 24-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण get_event;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		जोड़ अणु
			काष्ठा myrs_ldev ldev;		/* Bytes 16-18 */
			काष्ठा myrs_pdev pdev;		/* Bytes 16-18 */
		पूर्ण;
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		क्रमागत myrs_devstate state;		/* Byte 22 */
		अचिन्हित अक्षर rsvd[9];			/* Bytes 23-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण set_devstate;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		काष्ठा myrs_ldev ldev;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित अक्षर restore_consistency:1;	/* Byte 22 Bit 0 */
		अचिन्हित अक्षर initialized_area_only:1;	/* Byte 22 Bit 1 */
		अचिन्हित अक्षर rsvd1:6;			/* Byte 22 Bits 2-7 */
		अचिन्हित अक्षर rsvd2[9];			/* Bytes 23-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण cc;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		अचिन्हित अक्षर first_cmd_mbox_size_kb;	/* Byte 4 */
		अचिन्हित अक्षर first_stat_mbox_size_kb;	/* Byte 5 */
		अचिन्हित अक्षर second_cmd_mbox_size_kb;	/* Byte 6 */
		अचिन्हित अक्षर second_stat_mbox_size_kb;	/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		अचिन्हित पूर्णांक rsvd1:24;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		अचिन्हित अक्षर fwstat_buf_size_kb;	/* Byte 22 */
		अचिन्हित अक्षर rsvd2;			/* Byte 23 */
		u64 fwstat_buf_addr;			/* Bytes 24-31 */
		u64 first_cmd_mbox_addr;		/* Bytes 32-39 */
		u64 first_stat_mbox_addr;		/* Bytes 40-47 */
		u64 second_cmd_mbox_addr;		/* Bytes 48-55 */
		u64 second_stat_mbox_addr;		/* Bytes 56-63 */
	पूर्ण set_mbox;
	काष्ठा अणु
		अचिन्हित लघु id;			/* Bytes 0-1 */
		क्रमागत myrs_cmd_opcode opcode;		/* Byte 2 */
		काष्ठा myrs_cmd_ctrl control;		/* Byte 3 */
		u32 dma_size:24;			/* Bytes 4-6 */
		अचिन्हित अक्षर dma_num;			/* Byte 7 */
		u64 sense_addr;				/* Bytes 8-15 */
		काष्ठा myrs_pdev pdev;			/* Bytes 16-18 */
		काष्ठा myrs_cmd_पंचांगo पंचांगo;		/* Byte 19 */
		अचिन्हित अक्षर sense_len;		/* Byte 20 */
		क्रमागत myrs_ioctl_opcode ioctl_opcode;	/* Byte 21 */
		क्रमागत myrs_opdev opdev;			/* Byte 22 */
		अचिन्हित अक्षर rsvd[9];			/* Bytes 23-31 */
		जोड़ myrs_sgl dma_addr;		/* Bytes 32-63 */
	पूर्ण dev_op;
पूर्ण;

/*
 * DAC960 V2 Firmware Controller Status Mailbox काष्ठाure.
 */
काष्ठा myrs_stat_mbox अणु
	अचिन्हित लघु id;		/* Bytes 0-1 */
	अचिन्हित अक्षर status;		/* Byte 2 */
	अचिन्हित अक्षर sense_len;	/* Byte 3 */
	पूर्णांक residual;			/* Bytes 4-7 */
पूर्ण;

काष्ठा myrs_cmdblk अणु
	जोड़ myrs_cmd_mbox mbox;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर sense_len;
	पूर्णांक residual;
	काष्ठा completion *complete;
	काष्ठा myrs_sge *sgl;
	dma_addr_t sgl_addr;
	अचिन्हित अक्षर *dcdb;
	dma_addr_t dcdb_dma;
	अचिन्हित अक्षर *sense;
	dma_addr_t sense_addr;
पूर्ण;

/*
 * DAC960 Driver Controller काष्ठाure.
 */
काष्ठा myrs_hba अणु
	व्योम __iomem *io_base;
	व्योम __iomem *mmio_base;
	phys_addr_t io_addr;
	phys_addr_t pci_addr;
	अचिन्हित पूर्णांक irq;

	अचिन्हित अक्षर model_name[28];
	अचिन्हित अक्षर fw_version[12];

	काष्ठा Scsi_Host *host;
	काष्ठा pci_dev *pdev;

	अचिन्हित पूर्णांक epoch;
	अचिन्हित पूर्णांक next_evseq;
	/* Monitor flags */
	bool needs_update;
	bool disable_enc_msg;

	काष्ठा workqueue_काष्ठा *work_q;
	अक्षर work_q_name[20];
	काष्ठा delayed_work monitor_work;
	अचिन्हित दीर्घ primary_monitor_समय;
	अचिन्हित दीर्घ secondary_monitor_समय;

	spinlock_t queue_lock;

	काष्ठा dma_pool *sg_pool;
	काष्ठा dma_pool *sense_pool;
	काष्ठा dma_pool *dcdb_pool;

	व्योम (*ग_लिखो_cmd_mbox)(जोड़ myrs_cmd_mbox *next_mbox,
			       जोड़ myrs_cmd_mbox *cmd_mbox);
	व्योम (*get_cmd_mbox)(व्योम __iomem *base);
	व्योम (*disable_पूर्णांकr)(व्योम __iomem *base);
	व्योम (*reset)(व्योम __iomem *base);

	dma_addr_t cmd_mbox_addr;
	माप_प्रकार cmd_mbox_size;
	जोड़ myrs_cmd_mbox *first_cmd_mbox;
	जोड़ myrs_cmd_mbox *last_cmd_mbox;
	जोड़ myrs_cmd_mbox *next_cmd_mbox;
	जोड़ myrs_cmd_mbox *prev_cmd_mbox1;
	जोड़ myrs_cmd_mbox *prev_cmd_mbox2;

	dma_addr_t stat_mbox_addr;
	माप_प्रकार stat_mbox_size;
	काष्ठा myrs_stat_mbox *first_stat_mbox;
	काष्ठा myrs_stat_mbox *last_stat_mbox;
	काष्ठा myrs_stat_mbox *next_stat_mbox;

	काष्ठा myrs_cmdblk dcmd_blk;
	काष्ठा myrs_cmdblk mcmd_blk;
	काष्ठा mutex dcmd_mutex;

	काष्ठा myrs_fwstat *fwstat_buf;
	dma_addr_t fwstat_addr;

	काष्ठा myrs_ctlr_info *ctlr_info;
	काष्ठा mutex cinfo_mutex;

	काष्ठा myrs_event *event_buf;
पूर्ण;

प्रकार अचिन्हित अक्षर (*enable_mbox_t)(व्योम __iomem *base, dma_addr_t addr);
प्रकार पूर्णांक (*myrs_hwinit_t)(काष्ठा pci_dev *pdev,
			     काष्ठा myrs_hba *c, व्योम __iomem *base);

काष्ठा myrs_privdata अणु
	myrs_hwinit_t		hw_init;
	irq_handler_t		irq_handler;
	अचिन्हित पूर्णांक		mmio_size;
पूर्ण;

/*
 * DAC960 GEM Series Controller Interface Register Offsets.
 */

#घोषणा DAC960_GEM_mmio_size	0x600

क्रमागत DAC960_GEM_reg_offset अणु
	DAC960_GEM_IDB_READ_OFFSET	= 0x214,
	DAC960_GEM_IDB_CLEAR_OFFSET	= 0x218,
	DAC960_GEM_ODB_READ_OFFSET	= 0x224,
	DAC960_GEM_ODB_CLEAR_OFFSET	= 0x228,
	DAC960_GEM_IRQSTS_OFFSET	= 0x208,
	DAC960_GEM_IRQMASK_READ_OFFSET	= 0x22C,
	DAC960_GEM_IRQMASK_CLEAR_OFFSET	= 0x230,
	DAC960_GEM_CMDMBX_OFFSET	= 0x510,
	DAC960_GEM_CMDSTS_OFFSET	= 0x518,
	DAC960_GEM_ERRSTS_READ_OFFSET	= 0x224,
	DAC960_GEM_ERRSTS_CLEAR_OFFSET	= 0x228,
पूर्ण;

/*
 * DAC960 GEM Series Inbound Door Bell Register.
 */
#घोषणा DAC960_GEM_IDB_HWMBOX_NEW_CMD	0x01
#घोषणा DAC960_GEM_IDB_HWMBOX_ACK_STS	0x02
#घोषणा DAC960_GEM_IDB_GEN_IRQ		0x04
#घोषणा DAC960_GEM_IDB_CTRL_RESET	0x08
#घोषणा DAC960_GEM_IDB_MMBOX_NEW_CMD	0x10

#घोषणा DAC960_GEM_IDB_HWMBOX_FULL	0x01
#घोषणा DAC960_GEM_IDB_INIT_IN_PROGRESS	0x02

/*
 * DAC960 GEM Series Outbound Door Bell Register.
 */
#घोषणा DAC960_GEM_ODB_HWMBOX_ACK_IRQ	0x01
#घोषणा DAC960_GEM_ODB_MMBOX_ACK_IRQ	0x02
#घोषणा DAC960_GEM_ODB_HWMBOX_STS_AVAIL 0x01
#घोषणा DAC960_GEM_ODB_MMBOX_STS_AVAIL	0x02

/*
 * DAC960 GEM Series Interrupt Mask Register.
 */
#घोषणा DAC960_GEM_IRQMASK_HWMBOX_IRQ	0x01
#घोषणा DAC960_GEM_IRQMASK_MMBOX_IRQ	0x02

/*
 * DAC960 GEM Series Error Status Register.
 */
#घोषणा DAC960_GEM_ERRSTS_PENDING	0x20

/*
 * dma_addr_ग_लिखोql is provided to ग_लिखो dma_addr_t types
 * to a 64-bit pci address space रेजिस्टर.  The controller
 * will accept having the रेजिस्टर written as two 32-bit
 * values.
 *
 * In HIGHMEM kernels, dma_addr_t is a 64-bit value.
 * without HIGHMEM,  dma_addr_t is a 32-bit value.
 *
 * The compiler should always fix up the assignment
 * to u.wq appropriately, depending upon the size of
 * dma_addr_t.
 */
अटल अंतरभूत
व्योम dma_addr_ग_लिखोql(dma_addr_t addr, व्योम __iomem *ग_लिखो_address)
अणु
	जोड़ अणु
		u64 wq;
		uपूर्णांक wl[2];
	पूर्ण u;

	u.wq = addr;

	ग_लिखोl(u.wl[0], ग_लिखो_address);
	ग_लिखोl(u.wl[1], ग_लिखो_address + 4);
पूर्ण

/*
 * DAC960 BA Series Controller Interface Register Offsets.
 */

#घोषणा DAC960_BA_mmio_size		0x80

क्रमागत DAC960_BA_reg_offset अणु
	DAC960_BA_IRQSTS_OFFSET	= 0x30,
	DAC960_BA_IRQMASK_OFFSET = 0x34,
	DAC960_BA_CMDMBX_OFFSET = 0x50,
	DAC960_BA_CMDSTS_OFFSET = 0x58,
	DAC960_BA_IDB_OFFSET	= 0x60,
	DAC960_BA_ODB_OFFSET	= 0x61,
	DAC960_BA_ERRSTS_OFFSET = 0x63,
पूर्ण;

/*
 * DAC960 BA Series Inbound Door Bell Register.
 */
#घोषणा DAC960_BA_IDB_HWMBOX_NEW_CMD	0x01
#घोषणा DAC960_BA_IDB_HWMBOX_ACK_STS	0x02
#घोषणा DAC960_BA_IDB_GEN_IRQ		0x04
#घोषणा DAC960_BA_IDB_CTRL_RESET	0x08
#घोषणा DAC960_BA_IDB_MMBOX_NEW_CMD	0x10

#घोषणा DAC960_BA_IDB_HWMBOX_EMPTY	0x01
#घोषणा DAC960_BA_IDB_INIT_DONE		0x02

/*
 * DAC960 BA Series Outbound Door Bell Register.
 */
#घोषणा DAC960_BA_ODB_HWMBOX_ACK_IRQ	0x01
#घोषणा DAC960_BA_ODB_MMBOX_ACK_IRQ	0x02

#घोषणा DAC960_BA_ODB_HWMBOX_STS_AVAIL	0x01
#घोषणा DAC960_BA_ODB_MMBOX_STS_AVAIL	0x02

/*
 * DAC960 BA Series Interrupt Mask Register.
 */
#घोषणा DAC960_BA_IRQMASK_DISABLE_IRQ	0x04
#घोषणा DAC960_BA_IRQMASK_DISABLEW_I2O	0x08

/*
 * DAC960 BA Series Error Status Register.
 */
#घोषणा DAC960_BA_ERRSTS_PENDING	0x04

/*
 * DAC960 LP Series Controller Interface Register Offsets.
 */

#घोषणा DAC960_LP_mmio_size		0x80

क्रमागत DAC960_LP_reg_offset अणु
	DAC960_LP_CMDMBX_OFFSET = 0x10,
	DAC960_LP_CMDSTS_OFFSET = 0x18,
	DAC960_LP_IDB_OFFSET	= 0x20,
	DAC960_LP_ODB_OFFSET	= 0x2C,
	DAC960_LP_ERRSTS_OFFSET = 0x2E,
	DAC960_LP_IRQSTS_OFFSET	= 0x30,
	DAC960_LP_IRQMASK_OFFSET = 0x34,
पूर्ण;

/*
 * DAC960 LP Series Inbound Door Bell Register.
 */
#घोषणा DAC960_LP_IDB_HWMBOX_NEW_CMD	0x01
#घोषणा DAC960_LP_IDB_HWMBOX_ACK_STS	0x02
#घोषणा DAC960_LP_IDB_GEN_IRQ		0x04
#घोषणा DAC960_LP_IDB_CTRL_RESET	0x08
#घोषणा DAC960_LP_IDB_MMBOX_NEW_CMD	0x10

#घोषणा DAC960_LP_IDB_HWMBOX_FULL	0x01
#घोषणा DAC960_LP_IDB_INIT_IN_PROGRESS	0x02

/*
 * DAC960 LP Series Outbound Door Bell Register.
 */
#घोषणा DAC960_LP_ODB_HWMBOX_ACK_IRQ	0x01
#घोषणा DAC960_LP_ODB_MMBOX_ACK_IRQ	0x02

#घोषणा DAC960_LP_ODB_HWMBOX_STS_AVAIL	0x01
#घोषणा DAC960_LP_ODB_MMBOX_STS_AVAIL	0x02

/*
 * DAC960 LP Series Interrupt Mask Register.
 */
#घोषणा DAC960_LP_IRQMASK_DISABLE_IRQ	0x04

/*
 * DAC960 LP Series Error Status Register.
 */
#घोषणा DAC960_LP_ERRSTS_PENDING	0x04

#पूर्ण_अगर /* _MYRS_H */
