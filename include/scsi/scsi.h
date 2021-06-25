<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header file contains खुला स्थिरants and काष्ठाures used by
 * the SCSI initiator code.
 */
#अगर_अघोषित _SCSI_SCSI_H
#घोषणा _SCSI_SCSI_H

#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kernel.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_proto.h>

काष्ठा scsi_cmnd;

क्रमागत scsi_समयouts अणु
	SCSI_DEFAULT_EH_TIMEOUT		= 10 * HZ,
पूर्ण;

/*
 * DIX-capable adapters effectively support infinite chaining क्रम the
 * protection inक्रमmation scatterlist
 */
#घोषणा SCSI_MAX_PROT_SG_SEGMENTS	0xFFFF

/*
 * Special value क्रम scanning to specअगरy scanning or rescanning of all
 * possible channels, (target) ids, or luns on a given shost.
 */
#घोषणा SCAN_WILD_CARD	~0

/** scsi_status_is_good - check the status वापस.
 *
 * @status: the status passed up from the driver (including host and
 *          driver components)
 *
 * This वापसs true क्रम known good conditions that may be treated as
 * command completed normally
 */
अटल अंतरभूत पूर्णांक scsi_status_is_good(पूर्णांक status)
अणु
	/*
	 * FIXME: bit0 is listed as reserved in SCSI-2, but is
	 * signअगरicant in SCSI-3.  For now, we follow the SCSI-2
	 * behaviour and ignore reserved bits.
	 */
	status &= 0xfe;
	वापस ((status == SAM_STAT_GOOD) ||
		(status == SAM_STAT_CONDITION_MET) ||
		/* Next two "intermediate" statuses are obsolete in SAM-4 */
		(status == SAM_STAT_INTERMEDIATE) ||
		(status == SAM_STAT_INTERMEDIATE_CONDITION_MET) ||
		/* FIXME: this is obsolete in SAM-3 */
		(status == SAM_STAT_COMMAND_TERMINATED));
पूर्ण


/*
 * standard mode-select header prepended to all mode-select commands
 */

काष्ठा ccs_modesel_head अणु
	__u8 _r1;			/* reserved */
	__u8 medium;		/* device-specअगरic medium type */
	__u8 _r2;			/* reserved */
	__u8 block_desc_length;	/* block descriptor length */
	__u8 density;		/* device-specअगरic density code */
	__u8 number_blocks_hi;	/* number of blocks in this block desc */
	__u8 number_blocks_med;
	__u8 number_blocks_lo;
	__u8 _r3;
	__u8 block_length_hi;	/* block length क्रम blocks in this desc */
	__u8 block_length_med;
	__u8 block_length_lo;
पूर्ण;

/*
 * The Well Known LUNS (SAM-3) in our पूर्णांक representation of a LUN
 */
#घोषणा SCSI_W_LUN_BASE 0xc100
#घोषणा SCSI_W_LUN_REPORT_LUNS (SCSI_W_LUN_BASE + 1)
#घोषणा SCSI_W_LUN_ACCESS_CONTROL (SCSI_W_LUN_BASE + 2)
#घोषणा SCSI_W_LUN_TARGET_LOG_PAGE (SCSI_W_LUN_BASE + 3)

अटल अंतरभूत पूर्णांक scsi_is_wlun(u64 lun)
अणु
	वापस (lun & 0xff00) == SCSI_W_LUN_BASE;
पूर्ण


/*
 *  MESSAGE CODES
 */

#घोषणा COMMAND_COMPLETE    0x00
#घोषणा EXTENDED_MESSAGE    0x01
#घोषणा     EXTENDED_MODIFY_DATA_POINTER    0x00
#घोषणा     EXTENDED_SDTR                   0x01
#घोषणा     EXTENDED_EXTENDED_IDENTIFY      0x02    /* SCSI-I only */
#घोषणा     EXTENDED_WDTR                   0x03
#घोषणा     EXTENDED_PPR                    0x04
#घोषणा     EXTENDED_MODIFY_BIDI_DATA_PTR   0x05
#घोषणा SAVE_POINTERS       0x02
#घोषणा RESTORE_POINTERS    0x03
#घोषणा DISCONNECT          0x04
#घोषणा INITIATOR_ERROR     0x05
#घोषणा ABORT_TASK_SET      0x06
#घोषणा MESSAGE_REJECT      0x07
#घोषणा NOP                 0x08
#घोषणा MSG_PARITY_ERROR    0x09
#घोषणा LINKED_CMD_COMPLETE 0x0a
#घोषणा LINKED_FLG_CMD_COMPLETE 0x0b
#घोषणा TARGET_RESET        0x0c
#घोषणा ABORT_TASK          0x0d
#घोषणा CLEAR_TASK_SET      0x0e
#घोषणा INITIATE_RECOVERY   0x0f            /* SCSI-II only */
#घोषणा RELEASE_RECOVERY    0x10            /* SCSI-II only */
#घोषणा TERMINATE_IO_PROC   0x11            /* SCSI-II only */
#घोषणा CLEAR_ACA           0x16
#घोषणा LOGICAL_UNIT_RESET  0x17
#घोषणा SIMPLE_QUEUE_TAG    0x20
#घोषणा HEAD_OF_QUEUE_TAG   0x21
#घोषणा ORDERED_QUEUE_TAG   0x22
#घोषणा IGNORE_WIDE_RESIDUE 0x23
#घोषणा ACA                 0x24
#घोषणा QAS_REQUEST         0x55

/* Old SCSI2 names, करोn't use in new code */
#घोषणा BUS_DEVICE_RESET    TARGET_RESET
#घोषणा ABORT               ABORT_TASK_SET

/*
 * Host byte codes
 */

#घोषणा DID_OK          0x00	/* NO error                                */
#घोषणा DID_NO_CONNECT  0x01	/* Couldn't connect beक्रमe समयout period  */
#घोषणा DID_BUS_BUSY    0x02	/* BUS stayed busy through समय out period */
#घोषणा DID_TIME_OUT    0x03	/* TIMED OUT क्रम other reason              */
#घोषणा DID_BAD_TARGET  0x04	/* BAD target.                             */
#घोषणा DID_ABORT       0x05	/* Told to पात क्रम some other reason     */
#घोषणा DID_PARITY      0x06	/* Parity error                            */
#घोषणा DID_ERROR       0x07	/* Internal error                          */
#घोषणा DID_RESET       0x08	/* Reset by somebody.                      */
#घोषणा DID_BAD_INTR    0x09	/* Got an पूर्णांकerrupt we weren't expecting.  */
#घोषणा DID_PASSTHROUGH 0x0a	/* Force command past mid-layer            */
#घोषणा DID_SOFT_ERROR  0x0b	/* The low level driver just wish a retry  */
#घोषणा DID_IMM_RETRY   0x0c	/* Retry without decrementing retry count  */
#घोषणा DID_REQUEUE	0x0d	/* Requeue command (no immediate retry) also
				 * without decrementing the retry count	   */
#घोषणा DID_TRANSPORT_DISRUPTED 0x0e /* Transport error disrupted execution
				      * and the driver blocked the port to
				      * recover the link. Transport class will
				      * retry or fail IO */
#घोषणा DID_TRANSPORT_FAILFAST	0x0f /* Transport class fastfailed the io */
#घोषणा DID_TARGET_FAILURE 0x10 /* Permanent target failure, करो not retry on
				 * other paths */
#घोषणा DID_NEXUS_FAILURE 0x11  /* Permanent nexus failure, retry on other
				 * paths might yield dअगरferent results */
#घोषणा DID_ALLOC_FAILURE 0x12  /* Space allocation on the device failed */
#घोषणा DID_MEDIUM_ERROR  0x13  /* Medium error */
#घोषणा DID_TRANSPORT_MARGINAL 0x14 /* Transport marginal errors */
#घोषणा DRIVER_OK       0x00	/* Driver status                           */

/*
 *  These indicate the error that occurred, and what is available.
 */

#घोषणा DRIVER_BUSY         0x01
#घोषणा DRIVER_SOFT         0x02
#घोषणा DRIVER_MEDIA        0x03
#घोषणा DRIVER_ERROR        0x04

#घोषणा DRIVER_INVALID      0x05
#घोषणा DRIVER_TIMEOUT      0x06
#घोषणा DRIVER_HARD         0x07
#घोषणा DRIVER_SENSE	    0x08

/*
 * Internal वापस values.
 */
क्रमागत scsi_disposition अणु
	NEEDS_RETRY		= 0x2001,
	SUCCESS			= 0x2002,
	FAILED			= 0x2003,
	QUEUED			= 0x2004,
	SOFT_ERROR		= 0x2005,
	ADD_TO_MLQUEUE		= 0x2006,
	TIMEOUT_ERROR		= 0x2007,
	SCSI_RETURN_NOT_HANDLED	= 0x2008,
	FAST_IO_FAIL		= 0x2009,
पूर्ण;

/*
 * Midlevel queue वापस values.
 */
#घोषणा SCSI_MLQUEUE_HOST_BUSY   0x1055
#घोषणा SCSI_MLQUEUE_DEVICE_BUSY 0x1056
#घोषणा SCSI_MLQUEUE_EH_RETRY    0x1057
#घोषणा SCSI_MLQUEUE_TARGET_BUSY 0x1058

/*
 *  Use these to separate status msg and our bytes
 *
 *  These are set by:
 *
 *      status byte = set from target device
 *      msg_byte    = वापस status from host adapter itself.
 *      host_byte   = set by low-level driver to indicate status.
 *      driver_byte = set by mid-level.
 */
#घोषणा status_byte(result) (((result) >> 1) & 0x7f)
#घोषणा msg_byte(result)    (((result) >> 8) & 0xff)
#घोषणा host_byte(result)   (((result) >> 16) & 0xff)
#घोषणा driver_byte(result) (((result) >> 24) & 0xff)

#घोषणा sense_class(sense)  (((sense) >> 4) & 0x7)
#घोषणा sense_error(sense)  ((sense) & 0xf)
#घोषणा sense_valid(sense)  ((sense) & 0x80)

/*
 * शेष समयouts
*/
#घोषणा FORMAT_UNIT_TIMEOUT		(2 * 60 * 60 * HZ)
#घोषणा START_STOP_TIMEOUT		(60 * HZ)
#घोषणा MOVE_MEDIUM_TIMEOUT		(5 * 60 * HZ)
#घोषणा READ_ELEMENT_STATUS_TIMEOUT	(5 * 60 * HZ)
#घोषणा READ_DEFECT_DATA_TIMEOUT	(60 * HZ )


#घोषणा IDENTIFY_BASE       0x80
#घोषणा IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |\
		     ((can_disconnect) ?  0x40 : 0) |\
		     ((lun) & 0x07))

/*
 *  काष्ठा scsi_device::scsi_level values. For SCSI devices other than those
 *  prior to SCSI-2 (i.e. over 12 years old) this value is (resp[2] + 1)
 *  where "resp" is a byte array of the response to an INQUIRY. The scsi_level
 *  variable is visible to the user via sysfs.
 */

#घोषणा SCSI_UNKNOWN    0
#घोषणा SCSI_1          1
#घोषणा SCSI_1_CCS      2
#घोषणा SCSI_2          3
#घोषणा SCSI_3          4        /* SPC */
#घोषणा SCSI_SPC_2      5
#घोषणा SCSI_SPC_3      6

/*
 * INQ PERIPHERAL QUALIFIERS
 */
#घोषणा SCSI_INQ_PQ_CON         0x00
#घोषणा SCSI_INQ_PQ_NOT_CON     0x01
#घोषणा SCSI_INQ_PQ_NOT_CAP     0x03


/*
 * Here are some scsi specअगरic ioctl commands which are someबार useful.
 *
 * Note that include/linux/cdrom.h also defines IOCTL 0x5300 - 0x5395
 */

/* Used to obtain PUN and LUN info.  Conflicts with CDROMAUDIOबफ_मान */
#घोषणा SCSI_IOCTL_GET_IDLUN		0x5382

/* 0x5383 and 0x5384 were used क्रम SCSI_IOCTL_TAGGED_अणुENABLE,DISABLEपूर्ण */

/* Used to obtain the host number of a device. */
#घोषणा SCSI_IOCTL_PROBE_HOST		0x5385

/* Used to obtain the bus number क्रम a device */
#घोषणा SCSI_IOCTL_GET_BUS_NUMBER	0x5386

/* Used to obtain the PCI location of a device */
#घोषणा SCSI_IOCTL_GET_PCI		0x5387

#पूर्ण_अगर /* _SCSI_SCSI_H */
