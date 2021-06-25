<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header file contains खुला स्थिरants and काष्ठाures used by
 * both the SCSI initiator and the SCSI target code.
 *
 * For करोcumentation on the OPCODES, MESSAGES, and SENSE values,
 * please consult the SCSI standard.
 */

#अगर_अघोषित _SCSI_PROTO_H_
#घोषणा _SCSI_PROTO_H_

#समावेश <linux/types.h>

/*
 *      SCSI opcodes
 */

#घोषणा TEST_UNIT_READY       0x00
#घोषणा REZERO_UNIT           0x01
#घोषणा REQUEST_SENSE         0x03
#घोषणा FORMAT_UNIT           0x04
#घोषणा READ_BLOCK_LIMITS     0x05
#घोषणा REASSIGN_BLOCKS       0x07
#घोषणा INITIALIZE_ELEMENT_STATUS 0x07
#घोषणा READ_6                0x08
#घोषणा WRITE_6               0x0a
#घोषणा SEEK_6                0x0b
#घोषणा READ_REVERSE          0x0f
#घोषणा WRITE_खाताMARKS       0x10
#घोषणा SPACE                 0x11
#घोषणा INQUIRY               0x12
#घोषणा RECOVER_BUFFERED_DATA 0x14
#घोषणा MODE_SELECT           0x15
#घोषणा RESERVE               0x16
#घोषणा RELEASE               0x17
#घोषणा COPY                  0x18
#घोषणा ERASE                 0x19
#घोषणा MODE_SENSE            0x1a
#घोषणा START_STOP            0x1b
#घोषणा RECEIVE_DIAGNOSTIC    0x1c
#घोषणा SEND_DIAGNOSTIC       0x1d
#घोषणा ALLOW_MEDIUM_REMOVAL  0x1e

#घोषणा READ_FORMAT_CAPACITIES 0x23
#घोषणा SET_WINDOW            0x24
#घोषणा READ_CAPACITY         0x25
#घोषणा READ_10               0x28
#घोषणा WRITE_10              0x2a
#घोषणा SEEK_10               0x2b
#घोषणा POSITION_TO_ELEMENT   0x2b
#घोषणा WRITE_VERIFY          0x2e
#घोषणा VERIFY                0x2f
#घोषणा SEARCH_HIGH           0x30
#घोषणा SEARCH_EQUAL          0x31
#घोषणा SEARCH_LOW            0x32
#घोषणा SET_LIMITS            0x33
#घोषणा PRE_FETCH             0x34
#घोषणा READ_POSITION         0x34
#घोषणा SYNCHRONIZE_CACHE     0x35
#घोषणा LOCK_UNLOCK_CACHE     0x36
#घोषणा READ_DEFECT_DATA      0x37
#घोषणा MEDIUM_SCAN           0x38
#घोषणा COMPARE               0x39
#घोषणा COPY_VERIFY           0x3a
#घोषणा WRITE_BUFFER          0x3b
#घोषणा READ_BUFFER           0x3c
#घोषणा UPDATE_BLOCK          0x3d
#घोषणा READ_LONG             0x3e
#घोषणा WRITE_LONG            0x3f
#घोषणा CHANGE_DEFINITION     0x40
#घोषणा WRITE_SAME            0x41
#घोषणा UNMAP		      0x42
#घोषणा READ_TOC              0x43
#घोषणा READ_HEADER           0x44
#घोषणा GET_EVENT_STATUS_NOTIFICATION 0x4a
#घोषणा LOG_SELECT            0x4c
#घोषणा LOG_SENSE             0x4d
#घोषणा XDWRITEREAD_10        0x53
#घोषणा MODE_SELECT_10        0x55
#घोषणा RESERVE_10            0x56
#घोषणा RELEASE_10            0x57
#घोषणा MODE_SENSE_10         0x5a
#घोषणा PERSISTENT_RESERVE_IN 0x5e
#घोषणा PERSISTENT_RESERVE_OUT 0x5f
#घोषणा VARIABLE_LENGTH_CMD   0x7f
#घोषणा REPORT_LUNS           0xa0
#घोषणा SECURITY_PROTOCOL_IN  0xa2
#घोषणा MAINTEन_अंकCE_IN        0xa3
#घोषणा MAINTEन_अंकCE_OUT       0xa4
#घोषणा MOVE_MEDIUM           0xa5
#घोषणा EXCHANGE_MEDIUM       0xa6
#घोषणा READ_12               0xa8
#घोषणा SERVICE_ACTION_OUT_12 0xa9
#घोषणा WRITE_12              0xaa
#घोषणा READ_MEDIA_SERIAL_NUMBER 0xab /* Obsolete with SPC-2 */
#घोषणा SERVICE_ACTION_IN_12  0xab
#घोषणा WRITE_VERIFY_12       0xae
#घोषणा VERIFY_12	      0xaf
#घोषणा SEARCH_HIGH_12        0xb0
#घोषणा SEARCH_EQUAL_12       0xb1
#घोषणा SEARCH_LOW_12         0xb2
#घोषणा SECURITY_PROTOCOL_OUT 0xb5
#घोषणा READ_ELEMENT_STATUS   0xb8
#घोषणा SEND_VOLUME_TAG       0xb6
#घोषणा WRITE_LONG_2          0xea
#घोषणा EXTENDED_COPY         0x83
#घोषणा RECEIVE_COPY_RESULTS  0x84
#घोषणा ACCESS_CONTROL_IN     0x86
#घोषणा ACCESS_CONTROL_OUT    0x87
#घोषणा READ_16               0x88
#घोषणा COMPARE_AND_WRITE     0x89
#घोषणा WRITE_16              0x8a
#घोषणा READ_ATTRIBUTE        0x8c
#घोषणा WRITE_ATTRIBUTE	      0x8d
#घोषणा WRITE_VERIFY_16	      0x8e
#घोषणा VERIFY_16	      0x8f
#घोषणा SYNCHRONIZE_CACHE_16  0x91
#घोषणा WRITE_SAME_16	      0x93
#घोषणा ZBC_OUT		      0x94
#घोषणा ZBC_IN		      0x95
#घोषणा SERVICE_ACTION_BIसूचीECTIONAL 0x9d
#घोषणा SERVICE_ACTION_IN_16  0x9e
#घोषणा SERVICE_ACTION_OUT_16 0x9f
/* values क्रम service action in */
#घोषणा	SAI_READ_CAPACITY_16  0x10
#घोषणा SAI_GET_LBA_STATUS    0x12
#घोषणा SAI_REPORT_REFERRALS  0x13
/* values क्रम मुख्यtenance in */
#घोषणा MI_REPORT_IDENTIFYING_INFORMATION 0x05
#घोषणा MI_REPORT_TARGET_PGS  0x0a
#घोषणा MI_REPORT_ALIASES     0x0b
#घोषणा MI_REPORT_SUPPORTED_OPERATION_CODES 0x0c
#घोषणा MI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS 0x0d
#घोषणा MI_REPORT_PRIORITY    0x0e
#घोषणा MI_REPORT_TIMESTAMP   0x0f
#घोषणा MI_MANAGEMENT_PROTOCOL_IN 0x10
/* value क्रम MI_REPORT_TARGET_PGS ext header */
#घोषणा MI_EXT_HDR_PARAM_FMT  0x20
/* values क्रम मुख्यtenance out */
#घोषणा MO_SET_IDENTIFYING_INFORMATION 0x06
#घोषणा MO_SET_TARGET_PGS     0x0a
#घोषणा MO_CHANGE_ALIASES     0x0b
#घोषणा MO_SET_PRIORITY       0x0e
#घोषणा MO_SET_TIMESTAMP      0x0f
#घोषणा MO_MANAGEMENT_PROTOCOL_OUT 0x10
/* values क्रम ZBC_IN */
#घोषणा ZI_REPORT_ZONES	      0x00
/* values क्रम ZBC_OUT */
#घोषणा ZO_CLOSE_ZONE	      0x01
#घोषणा ZO_FINISH_ZONE	      0x02
#घोषणा ZO_OPEN_ZONE	      0x03
#घोषणा ZO_RESET_WRITE_POINTER 0x04
/* values क्रम variable length command */
#घोषणा XDREAD_32	      0x03
#घोषणा XDWRITE_32	      0x04
#घोषणा XPWRITE_32	      0x06
#घोषणा XDWRITEREAD_32	      0x07
#घोषणा READ_32		      0x09
#घोषणा VERIFY_32	      0x0a
#घोषणा WRITE_32	      0x0b
#घोषणा WRITE_VERIFY_32	      0x0c
#घोषणा WRITE_SAME_32	      0x0d
#घोषणा ATA_32		      0x1ff0

/* Values क्रम T10/04-262r7 */
#घोषणा	ATA_16		      0x85	/* 16-byte pass-thru */
#घोषणा	ATA_12		      0xa1	/* 12-byte pass-thru */

/* Venकरोr specअगरic CDBs start here */
#घोषणा VENDOR_SPECIFIC_CDB 0xc0

/*
 *	SCSI command lengths
 */

#घोषणा SCSI_MAX_VARLEN_CDB_SIZE 260

/* defined in T10 SCSI Primary Commands-2 (SPC2) */
काष्ठा scsi_varlen_cdb_hdr अणु
	__u8 opcode;        /* opcode always == VARIABLE_LENGTH_CMD */
	__u8 control;
	__u8 misc[5];
	__u8 additional_cdb_length;         /* total cdb length - 8 */
	__be16 service_action;
	/* service specअगरic data follows */
पूर्ण;

/*
 *  SCSI Architecture Model (SAM) Status codes. Taken from SAM-3 draft
 *  T10/1561-D Revision 4 Draft dated 7th November 2002.
 */
#घोषणा SAM_STAT_GOOD            0x00
#घोषणा SAM_STAT_CHECK_CONDITION 0x02
#घोषणा SAM_STAT_CONDITION_MET   0x04
#घोषणा SAM_STAT_BUSY            0x08
#घोषणा SAM_STAT_INTERMEDIATE    0x10
#घोषणा SAM_STAT_INTERMEDIATE_CONDITION_MET 0x14
#घोषणा SAM_STAT_RESERVATION_CONFLICT 0x18
#घोषणा SAM_STAT_COMMAND_TERMINATED 0x22	/* obsolete in SAM-3 */
#घोषणा SAM_STAT_TASK_SET_FULL   0x28
#घोषणा SAM_STAT_ACA_ACTIVE      0x30
#घोषणा SAM_STAT_TASK_ABORTED    0x40

/*
 *  Status codes. These are deprecated as they are shअगरted 1 bit right
 *  from those found in the SCSI standards. This causes confusion क्रम
 *  applications that are ported to several OSes. Prefer SAM Status codes
 *  above.
 */

#घोषणा GOOD                 0x00
#घोषणा CHECK_CONDITION      0x01
#घोषणा CONDITION_GOOD       0x02
#घोषणा BUSY                 0x04
#घोषणा INTERMEDIATE_GOOD    0x08
#घोषणा INTERMEDIATE_C_GOOD  0x0a
#घोषणा RESERVATION_CONFLICT 0x0c
#घोषणा COMMAND_TERMINATED   0x11
#घोषणा QUEUE_FULL           0x14
#घोषणा ACA_ACTIVE           0x18
#घोषणा TASK_ABORTED         0x20

#घोषणा STATUS_MASK          0xfe

/*
 *  SENSE KEYS
 */

#घोषणा NO_SENSE            0x00
#घोषणा RECOVERED_ERROR     0x01
#घोषणा NOT_READY           0x02
#घोषणा MEDIUM_ERROR        0x03
#घोषणा HARDWARE_ERROR      0x04
#घोषणा ILLEGAL_REQUEST     0x05
#घोषणा UNIT_ATTENTION      0x06
#घोषणा DATA_PROTECT        0x07
#घोषणा BLANK_CHECK         0x08
#घोषणा VENDOR_SPECIFIC     0x09
#घोषणा COPY_ABORTED        0x0a
#घोषणा ABORTED_COMMAND     0x0b
#घोषणा VOLUME_OVERFLOW     0x0d
#घोषणा MISCOMPARE          0x0e


/*
 *  DEVICE TYPES
 *  Please keep them in 0x%02x क्रमmat क्रम $MODALIAS to work
 */

#घोषणा TYPE_DISK           0x00
#घोषणा TYPE_TAPE           0x01
#घोषणा TYPE_PRINTER        0x02
#घोषणा TYPE_PROCESSOR      0x03    /* HP scanners use this */
#घोषणा TYPE_WORM           0x04    /* Treated as ROM by our प्रणाली */
#घोषणा TYPE_ROM            0x05
#घोषणा TYPE_SCANNER        0x06
#घोषणा TYPE_MOD            0x07    /* Magneto-optical disk -
				     * - treated as TYPE_DISK */
#घोषणा TYPE_MEDIUM_CHANGER 0x08
#घोषणा TYPE_COMM           0x09    /* Communications device */
#घोषणा TYPE_RAID           0x0c
#घोषणा TYPE_ENCLOSURE      0x0d    /* Enclosure Services Device */
#घोषणा TYPE_RBC	    0x0e
#घोषणा TYPE_OSD            0x11
#घोषणा TYPE_ZBC            0x14
#घोषणा TYPE_WLUN           0x1e    /* well-known logical unit */
#घोषणा TYPE_NO_LUN         0x7f

/* SCSI protocols; these are taken from SPC-3 section 7.5 */
क्रमागत scsi_protocol अणु
	SCSI_PROTOCOL_FCP = 0,	/* Fibre Channel */
	SCSI_PROTOCOL_SPI = 1,	/* parallel SCSI */
	SCSI_PROTOCOL_SSA = 2,	/* Serial Storage Architecture - Obsolete */
	SCSI_PROTOCOL_SBP = 3,	/* firewire */
	SCSI_PROTOCOL_SRP = 4,	/* Infiniband RDMA */
	SCSI_PROTOCOL_ISCSI = 5,
	SCSI_PROTOCOL_SAS = 6,
	SCSI_PROTOCOL_ADT = 7,	/* Media Changers */
	SCSI_PROTOCOL_ATA = 8,
	SCSI_PROTOCOL_UNSPEC = 0xf, /* No specअगरic protocol */
पूर्ण;

/*
 * ScsiLun: 8 byte LUN.
 */
काष्ठा scsi_lun अणु
	__u8 scsi_lun[8];
पूर्ण;

/* SPC asymmetric access states */
#घोषणा SCSI_ACCESS_STATE_OPTIMAL     0x00
#घोषणा SCSI_ACCESS_STATE_ACTIVE      0x01
#घोषणा SCSI_ACCESS_STATE_STANDBY     0x02
#घोषणा SCSI_ACCESS_STATE_UNAVAILABLE 0x03
#घोषणा SCSI_ACCESS_STATE_LBA         0x04
#घोषणा SCSI_ACCESS_STATE_OFFLINE     0x0e
#घोषणा SCSI_ACCESS_STATE_TRANSITIONING 0x0f

/* Values क्रम REPORT TARGET GROUP STATES */
#घोषणा SCSI_ACCESS_STATE_MASK        0x0f
#घोषणा SCSI_ACCESS_STATE_PREFERRED   0x80

/* Reporting options क्रम REPORT ZONES */
क्रमागत zbc_zone_reporting_options अणु
	ZBC_ZONE_REPORTING_OPTION_ALL		= 0x00,
	ZBC_ZONE_REPORTING_OPTION_EMPTY		= 0x01,
	ZBC_ZONE_REPORTING_OPTION_IMPLICIT_OPEN	= 0x02,
	ZBC_ZONE_REPORTING_OPTION_EXPLICIT_OPEN	= 0x03,
	ZBC_ZONE_REPORTING_OPTION_CLOSED	= 0x04,
	ZBC_ZONE_REPORTING_OPTION_FULL		= 0x05,
	ZBC_ZONE_REPORTING_OPTION_READONLY	= 0x06,
	ZBC_ZONE_REPORTING_OPTION_OFFLINE	= 0x07,
	/* 0x08 to 0x0f are reserved */
	ZBC_ZONE_REPORTING_OPTION_NEED_RESET_WP	= 0x10,
	ZBC_ZONE_REPORTING_OPTION_NON_SEQWRITE	= 0x11,
	/* 0x12 to 0x3e are reserved */
	ZBC_ZONE_REPORTING_OPTION_NON_WP	= 0x3f,
पूर्ण;

#घोषणा ZBC_REPORT_ZONE_PARTIAL 0x80

/* Zone types of REPORT ZONES zone descriptors */
क्रमागत zbc_zone_type अणु
	ZBC_ZONE_TYPE_CONV		= 0x1,
	ZBC_ZONE_TYPE_SEQWRITE_REQ	= 0x2,
	ZBC_ZONE_TYPE_SEQWRITE_PREF	= 0x3,
	/* 0x4 to 0xf are reserved */
पूर्ण;

/* Zone conditions of REPORT ZONES zone descriptors */
क्रमागत zbc_zone_cond अणु
	ZBC_ZONE_COND_NO_WP		= 0x0,
	ZBC_ZONE_COND_EMPTY		= 0x1,
	ZBC_ZONE_COND_IMP_OPEN		= 0x2,
	ZBC_ZONE_COND_EXP_OPEN		= 0x3,
	ZBC_ZONE_COND_CLOSED		= 0x4,
	/* 0x5 to 0xc are reserved */
	ZBC_ZONE_COND_READONLY		= 0xd,
	ZBC_ZONE_COND_FULL		= 0xe,
	ZBC_ZONE_COND_OFFLINE		= 0xf,
पूर्ण;

#पूर्ण_अगर /* _SCSI_PROTO_H_ */
