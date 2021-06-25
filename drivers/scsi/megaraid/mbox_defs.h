<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *			Linux MegaRAID Unअगरied device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: mbox_defs.h
 */
#अगर_अघोषित _MRAID_MBOX_DEFS_H_
#घोषणा _MRAID_MBOX_DEFS_H_

#समावेश <linux/types.h>

/*
 * Commands and states क्रम mailbox based controllers
 */

#घोषणा MBOXCMD_LREAD		0x01
#घोषणा MBOXCMD_LWRITE		0x02
#घोषणा MBOXCMD_PASSTHRU	0x03
#घोषणा MBOXCMD_ADPEXTINQ	0x04
#घोषणा MBOXCMD_ADAPTERINQ	0x05
#घोषणा MBOXCMD_LREAD64		0xA7
#घोषणा MBOXCMD_LWRITE64	0xA8
#घोषणा MBOXCMD_PASSTHRU64	0xC3
#घोषणा MBOXCMD_EXTPTHRU	0xE3

#घोषणा MAIN_MISC_OPCODE	0xA4
#घोषणा GET_MAX_SG_SUPPORT	0x01
#घोषणा SUPPORT_EXT_CDB		0x16

#घोषणा FC_NEW_CONFIG		0xA1
#घोषणा NC_SUBOP_PRODUCT_INFO	0x0E
#घोषणा NC_SUBOP_ENQUIRY3	0x0F
#घोषणा ENQ3_GET_SOLICITED_FULL	0x02
#घोषणा OP_DCMD_READ_CONFIG	0x04
#घोषणा NEW_READ_CONFIG_8LD	0x67
#घोषणा READ_CONFIG_8LD		0x07
#घोषणा FLUSH_ADAPTER		0x0A
#घोषणा FLUSH_SYSTEM		0xFE

/*
 * Command क्रम अक्रमom deletion of logical drives
 */
#घोषणा	FC_DEL_LOGDRV		0xA4
#घोषणा	OP_SUP_DEL_LOGDRV	0x2A
#घोषणा OP_GET_LDID_MAP		0x18
#घोषणा OP_DEL_LOGDRV		0x1C

/*
 * BIOS commands
 */
#घोषणा IS_BIOS_ENABLED		0x62
#घोषणा GET_BIOS		0x01
#घोषणा CHNL_CLASS		0xA9
#घोषणा GET_CHNL_CLASS		0x00
#घोषणा SET_CHNL_CLASS		0x01
#घोषणा CH_RAID			0x01
#घोषणा CH_SCSI			0x00
#घोषणा BIOS_PVT_DATA		0x40
#घोषणा GET_BIOS_PVT_DATA	0x00


/*
 * Commands to support clustering
 */
#घोषणा GET_TARGET_ID		0x7D
#घोषणा CLUSTER_OP		0x70
#घोषणा GET_CLUSTER_MODE	0x02
#घोषणा CLUSTER_CMD		0x6E
#घोषणा RESERVE_LD		0x01
#घोषणा RELEASE_LD		0x02
#घोषणा RESET_RESERVATIONS	0x03
#घोषणा RESERVATION_STATUS	0x04
#घोषणा RESERVE_PD		0x05
#घोषणा RELEASE_PD		0x06


/*
 * Module battery status
 */
#घोषणा BATTERY_MODULE_MISSING		0x01
#घोषणा BATTERY_LOW_VOLTAGE		0x02
#घोषणा BATTERY_TEMP_HIGH		0x04
#घोषणा BATTERY_PACK_MISSING		0x08
#घोषणा BATTERY_CHARGE_MASK		0x30
#घोषणा BATTERY_CHARGE_DONE		0x00
#घोषणा BATTERY_CHARGE_INPROG		0x10
#घोषणा BATTERY_CHARGE_FAIL		0x20
#घोषणा BATTERY_CYCLES_EXCEEDED		0x40

/*
 * Physical drive states.
 */
#घोषणा PDRV_UNCNF	0
#घोषणा PDRV_ONLINE	3
#घोषणा PDRV_FAILED	4
#घोषणा PDRV_RBLD	5
#घोषणा PDRV_HOTSPARE	6


/*
 * Raid logical drive states.
 */
#घोषणा RDRV_OFFLINE	0
#घोषणा RDRV_DEGRADED	1
#घोषणा RDRV_OPTIMAL	2
#घोषणा RDRV_DELETED	3

/*
 * Read, ग_लिखो and cache policies
 */
#घोषणा NO_READ_AHEAD		0
#घोषणा READ_AHEAD		1
#घोषणा ADAP_READ_AHEAD		2
#घोषणा WRMODE_WRITE_THRU	0
#घोषणा WRMODE_WRITE_BACK	1
#घोषणा CACHED_IO		0
#घोषणा सूचीECT_IO		1

#घोषणा MAX_LOGICAL_DRIVES_8LD		8
#घोषणा MAX_LOGICAL_DRIVES_40LD		40
#घोषणा FC_MAX_PHYSICAL_DEVICES		256
#घोषणा MAX_MBOX_CHANNELS		5
#घोषणा MAX_MBOX_TARGET			15
#घोषणा MBOX_MAX_PHYSICAL_DRIVES	MAX_MBOX_CHANNELS*MAX_MBOX_TARGET
#घोषणा MAX_ROW_SIZE_40LD		32
#घोषणा MAX_ROW_SIZE_8LD		8
#घोषणा SPAN_DEPTH_8_SPANS		8
#घोषणा SPAN_DEPTH_4_SPANS		4
#घोषणा MAX_REQ_SENSE_LEN		0x20



/**
 * काष्ठा mbox_t - Driver and f/w handshake काष्ठाure.
 * @cmd		: firmware command
 * @cmdid	: command id
 * @numsectors	: number of sectors to be transferred
 * @lba		: Logical Block Address on LD
 * @xferaddr	: DMA address क्रम data transfer
 * @logdrv	: logical drive number
 * @numsge	: number of scatter gather elements in sg list
 * @resvd	: reserved
 * @busy	: f/w busy, must रुको to issue more commands.
 * @numstatus	: number of commands completed.
 * @status	: status of the commands completed
 * @completed	: array of completed command ids.
 * @poll	: poll and ack sequence
 * @ack		: poll and ack sequence
 *
 * The central handshake काष्ठाure between the driver and the firmware. This
 * काष्ठाure must be allocated by the driver and aligned at 8-byte boundary.
 */
#घोषणा MBOX_MAX_FIRMWARE_STATUS	46
प्रकार काष्ठा अणु
	uपूर्णांक8_t		cmd;
	uपूर्णांक8_t		cmdid;
	uपूर्णांक16_t	numsectors;
	uपूर्णांक32_t	lba;
	uपूर्णांक32_t	xferaddr;
	uपूर्णांक8_t		logdrv;
	uपूर्णांक8_t		numsge;
	uपूर्णांक8_t		resvd;
	uपूर्णांक8_t		busy;
	uपूर्णांक8_t		numstatus;
	uपूर्णांक8_t		status;
	uपूर्णांक8_t		completed[MBOX_MAX_FIRMWARE_STATUS];
	uपूर्णांक8_t		poll;
	uपूर्णांक8_t		ack;
पूर्ण __attribute__ ((packed)) mbox_t;


/**
 * mbox64_t - 64-bit extension क्रम the mailbox
 * @segment_lo	: the low 32-bits of the address of the scatter-gather list
 * @segment_hi	: the upper 32-bits of the address of the scatter-gather list
 * @mbox	: 32-bit mailbox, whose xferadder field must be set to
 *		0xFFFFFFFF
 *
 * This is the extension of the 32-bit mailbox to be able to perक्रमm DMA
 * beyond 4GB address range.
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t	xferaddr_lo;
	uपूर्णांक32_t	xferaddr_hi;
	mbox_t		mbox32;
पूर्ण __attribute__ ((packed)) mbox64_t;

/*
 * mailbox काष्ठाure used क्रम पूर्णांकernal commands
 */
प्रकार काष्ठा अणु
	u8	cmd;
	u8	cmdid;
	u8	opcode;
	u8	subopcode;
	u32	lba;
	u32	xferaddr;
	u8	logdrv;
	u8	rsvd[3];
	u8	numstatus;
	u8	status;
पूर्ण __attribute__ ((packed)) पूर्णांक_mbox_t;

/**
 * mraid_passthru_t - passthru काष्ठाure to issue commands to physical devices
 * @समयout		: command समयout, 0=6sec, 1=60sec, 2=10min, 3=3hr
 * @ars			: set अगर ARS required after check condition
 * @islogical		: set अगर command meant क्रम logical devices
 * @logdrv		: logical drive number अगर command क्रम LD
 * @channel		: Channel on which physical device is located
 * @target		: SCSI target of the device
 * @queuetag		: unused
 * @queueaction		: unused
 * @cdb			: SCSI CDB
 * @cdblen		: length of the CDB
 * @reqsenselen		: amount of request sense data to be वापसed
 * @reqsensearea	: Sense inक्रमmation buffer
 * @numsge		: number of scatter-gather elements in the sg list
 * @scsistatus		: SCSI status of the command completed.
 * @dataxferaddr	: DMA data transfer address
 * @dataxferlen		: amount of the data to be transferred.
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		समयout		:3;
	uपूर्णांक8_t		ars		:1;
	uपूर्णांक8_t		reserved	:3;
	uपूर्णांक8_t		islogical	:1;
	uपूर्णांक8_t		logdrv;
	uपूर्णांक8_t		channel;
	uपूर्णांक8_t		target;
	uपूर्णांक8_t		queuetag;
	uपूर्णांक8_t		queueaction;
	uपूर्णांक8_t		cdb[10];
	uपूर्णांक8_t		cdblen;
	uपूर्णांक8_t		reqsenselen;
	uपूर्णांक8_t		reqsensearea[MAX_REQ_SENSE_LEN];
	uपूर्णांक8_t		numsge;
	uपूर्णांक8_t		scsistatus;
	uपूर्णांक32_t	dataxferaddr;
	uपूर्णांक32_t	dataxferlen;
पूर्ण __attribute__ ((packed)) mraid_passthru_t;

प्रकार काष्ठा अणु

	uपूर्णांक32_t		dataxferaddr_lo;
	uपूर्णांक32_t		dataxferaddr_hi;
	mraid_passthru_t	pthru32;

पूर्ण __attribute__ ((packed)) mega_passthru64_t;

/**
 * mraid_epassthru_t - passthru काष्ठाure to issue commands to physical devices
 * @समयout		: command समयout, 0=6sec, 1=60sec, 2=10min, 3=3hr
 * @ars			: set अगर ARS required after check condition
 * @rsvd1		: reserved field
 * @cd_rom		: (?)
 * @rsvd2		: reserved field
 * @islogical		: set अगर command meant क्रम logical devices
 * @logdrv		: logical drive number अगर command क्रम LD
 * @channel		: Channel on which physical device is located
 * @target		: SCSI target of the device
 * @queuetag		: unused
 * @queueaction		: unused
 * @cdblen		: length of the CDB
 * @rsvd3		: reserved field
 * @cdb			: SCSI CDB
 * @numsge		: number of scatter-gather elements in the sg list
 * @status		: SCSI status of the command completed.
 * @reqsenselen		: amount of request sense data to be वापसed
 * @reqsensearea	: Sense inक्रमmation buffer
 * @rsvd4		: reserved field
 * @dataxferaddr	: DMA data transfer address
 * @dataxferlen		: amount of the data to be transferred.
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		समयout		:3;
	uपूर्णांक8_t		ars		:1;
	uपूर्णांक8_t		rsvd1		:1;
	uपूर्णांक8_t		cd_rom		:1;
	uपूर्णांक8_t		rsvd2		:1;
	uपूर्णांक8_t		islogical	:1;
	uपूर्णांक8_t		logdrv;
	uपूर्णांक8_t		channel;
	uपूर्णांक8_t		target;
	uपूर्णांक8_t		queuetag;
	uपूर्णांक8_t		queueaction;
	uपूर्णांक8_t		cdblen;
	uपूर्णांक8_t		rsvd3;
	uपूर्णांक8_t		cdb[16];
	uपूर्णांक8_t		numsge;
	uपूर्णांक8_t		status;
	uपूर्णांक8_t		reqsenselen;
	uपूर्णांक8_t		reqsensearea[MAX_REQ_SENSE_LEN];
	uपूर्णांक8_t		rsvd4;
	uपूर्णांक32_t	dataxferaddr;
	uपूर्णांक32_t	dataxferlen;
पूर्ण __attribute__ ((packed)) mraid_epassthru_t;


/**
 * mraid_pinfo_t - product info, अटल inक्रमmation about the controller
 * @data_size		: current size in bytes (not including resvd)
 * @config_signature	: Current value is 0x00282008
 * @fw_version		: Firmware version
 * @bios_version	: version of the BIOS
 * @product_name	: Name given to the controller
 * @max_commands	: Maximum concurrent commands supported
 * @nchannels		: Number of SCSI Channels detected
 * @fc_loop_present	: Number of Fibre Loops detected
 * @mem_type		: EDO, FPM, SDRAM etc
 * @signature		:
 * @dram_size		: In terms of MB
 * @subsysid		: device PCI subप्रणाली ID
 * @subsysvid		: device PCI subप्रणाली venकरोr ID
 * @notअगरy_counters	:
 * @pad1k		: 135 + 889 resvd = 1024 total size
 *
 * This काष्ठाures holds the inक्रमmation about the controller which is not
 * expected to change dynamically.
 *
 * The current value of config signature is 0x00282008:
 * 0x28 = MAX_LOGICAL_DRIVES,
 * 0x20 = Number of stripes and
 * 0x08 = Number of spans
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t	data_size;
	uपूर्णांक32_t	config_signature;
	uपूर्णांक8_t		fw_version[16];
	uपूर्णांक8_t		bios_version[16];
	uपूर्णांक8_t		product_name[80];
	uपूर्णांक8_t		max_commands;
	uपूर्णांक8_t		nchannels;
	uपूर्णांक8_t		fc_loop_present;
	uपूर्णांक8_t		mem_type;
	uपूर्णांक32_t	signature;
	uपूर्णांक16_t	dram_size;
	uपूर्णांक16_t	subsysid;
	uपूर्णांक16_t	subsysvid;
	uपूर्णांक8_t		notअगरy_counters;
	uपूर्णांक8_t		pad1k[889];
पूर्ण __attribute__ ((packed)) mraid_pinfo_t;


/**
 * mraid_notअगरy_t - the notअगरication काष्ठाure
 * @global_counter		: Any change increments this counter
 * @param_counter		: Indicates any params changed
 * @param_id			: Param modअगरied - defined below
 * @param_val			: New val of last param modअगरied
 * @ग_लिखो_config_counter	: ग_लिखो config occurred
 * @ग_लिखो_config_rsvd		:
 * @ldrv_op_counter		: Indicates ldrv op started/completed
 * @ldrv_opid			: ldrv num
 * @ldrv_opcmd			: ldrv operation - defined below
 * @ldrv_opstatus		: status of the operation
 * @ldrv_state_counter		: Indicates change of ldrv state
 * @ldrv_state_id		: ldrv num
 * @ldrv_state_new		: New state
 * @ldrv_state_old		: old state
 * @pdrv_state_counter		: Indicates change of ldrv state
 * @pdrv_state_id		: pdrv id
 * @pdrv_state_new		: New state
 * @pdrv_state_old		: old state
 * @pdrv_fmt_counter		: Indicates pdrv क्रमmat started/over
 * @pdrv_fmt_id			: pdrv id
 * @pdrv_fmt_val		: क्रमmat started/over
 * @pdrv_fmt_rsvd		:
 * @targ_xfer_counter		: Indicates SCSI-2 Xfer rate change
 * @targ_xfer_id		: pdrv Id
 * @targ_xfer_val		: new Xfer params of last pdrv
 * @targ_xfer_rsvd		:
 * @fcloop_id_chg_counter	: Indicates loopid changed
 * @fcloopid_pdrvid		: pdrv id
 * @fcloop_id0			: loopid on fc loop 0
 * @fcloop_id1			: loopid on fc loop 1
 * @fcloop_state_counter	: Indicates loop state changed
 * @fcloop_state0		: state of fc loop 0
 * @fcloop_state1		: state of fc loop 1
 * @fcloop_state_rsvd		:
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t	global_counter;
	uपूर्णांक8_t		param_counter;
	uपूर्णांक8_t		param_id;
	uपूर्णांक16_t	param_val;
	uपूर्णांक8_t		ग_लिखो_config_counter;
	uपूर्णांक8_t		ग_लिखो_config_rsvd[3];
	uपूर्णांक8_t		ldrv_op_counter;
	uपूर्णांक8_t		ldrv_opid;
	uपूर्णांक8_t		ldrv_opcmd;
	uपूर्णांक8_t		ldrv_opstatus;
	uपूर्णांक8_t		ldrv_state_counter;
	uपूर्णांक8_t		ldrv_state_id;
	uपूर्णांक8_t		ldrv_state_new;
	uपूर्णांक8_t		ldrv_state_old;
	uपूर्णांक8_t		pdrv_state_counter;
	uपूर्णांक8_t		pdrv_state_id;
	uपूर्णांक8_t		pdrv_state_new;
	uपूर्णांक8_t		pdrv_state_old;
	uपूर्णांक8_t		pdrv_fmt_counter;
	uपूर्णांक8_t		pdrv_fmt_id;
	uपूर्णांक8_t		pdrv_fmt_val;
	uपूर्णांक8_t		pdrv_fmt_rsvd;
	uपूर्णांक8_t		targ_xfer_counter;
	uपूर्णांक8_t		targ_xfer_id;
	uपूर्णांक8_t		targ_xfer_val;
	uपूर्णांक8_t		targ_xfer_rsvd;
	uपूर्णांक8_t		fcloop_id_chg_counter;
	uपूर्णांक8_t		fcloopid_pdrvid;
	uपूर्णांक8_t		fcloop_id0;
	uपूर्णांक8_t		fcloop_id1;
	uपूर्णांक8_t		fcloop_state_counter;
	uपूर्णांक8_t		fcloop_state0;
	uपूर्णांक8_t		fcloop_state1;
	uपूर्णांक8_t		fcloop_state_rsvd;
पूर्ण __attribute__ ((packed)) mraid_notअगरy_t;


/**
 * mraid_inquiry3_t - enquiry क्रम device inक्रमmation
 *
 * @data_size		: current size in bytes (not including resvd)
 * @notअगरy		:
 * @notअगरy_rsvd		:
 * @rebuild_rate	: rebuild rate (0% - 100%)
 * @cache_flush_पूर्णांक	: cache flush पूर्णांकerval in seconds
 * @sense_alert		:
 * @drive_insert_count	: drive insertion count
 * @battery_status	:
 * @num_ldrv		: no. of Log Drives configured
 * @recon_state		: state of reस्थिरruct
 * @ldrv_op_status	: logdrv Status
 * @ldrv_size		: size of each log drv
 * @ldrv_prop		:
 * @ldrv_state		: state of log drives
 * @pdrv_state		: state of phys drvs.
 * @pdrv_क्रमmat		:
 * @targ_xfer		: phys device transfer rate
 * @pad1k		: 761 + 263reserved = 1024 bytes total size
 */
#घोषणा MAX_NOTIFY_SIZE		0x80
#घोषणा CUR_NOTIFY_SIZE		माप(mraid_notअगरy_t)

प्रकार काष्ठा अणु
	uपूर्णांक32_t	data_size;

	mraid_notअगरy_t	notअगरy;

	uपूर्णांक8_t		notअगरy_rsvd[MAX_NOTIFY_SIZE - CUR_NOTIFY_SIZE];

	uपूर्णांक8_t		rebuild_rate;
	uपूर्णांक8_t		cache_flush_पूर्णांक;
	uपूर्णांक8_t		sense_alert;
	uपूर्णांक8_t		drive_insert_count;

	uपूर्णांक8_t		battery_status;
	uपूर्णांक8_t		num_ldrv;
	uपूर्णांक8_t		recon_state[MAX_LOGICAL_DRIVES_40LD / 8];
	uपूर्णांक16_t	ldrv_op_status[MAX_LOGICAL_DRIVES_40LD / 8];

	uपूर्णांक32_t	ldrv_size[MAX_LOGICAL_DRIVES_40LD];
	uपूर्णांक8_t		ldrv_prop[MAX_LOGICAL_DRIVES_40LD];
	uपूर्णांक8_t		ldrv_state[MAX_LOGICAL_DRIVES_40LD];
	uपूर्णांक8_t		pdrv_state[FC_MAX_PHYSICAL_DEVICES];
	uपूर्णांक16_t	pdrv_क्रमmat[FC_MAX_PHYSICAL_DEVICES / 16];

	uपूर्णांक8_t		targ_xfer[80];
	uपूर्णांक8_t		pad1k[263];
पूर्ण __attribute__ ((packed)) mraid_inquiry3_t;


/**
 * mraid_adapinfo_t - inक्रमmation about the adapter
 * @max_commands		: max concurrent commands supported
 * @rebuild_rate		: rebuild rate - 0% thru 100%
 * @max_targ_per_chan		: max targ per channel
 * @nchannels			: number of channels on HBA
 * @fw_version			: firmware version
 * @age_of_flash		: number of बार FW has been flashed
 * @chip_set_value		: contents of 0xC0000832
 * @dram_size			: in MB
 * @cache_flush_पूर्णांकerval	: in seconds
 * @bios_version		:
 * @board_type			:
 * @sense_alert			:
 * @ग_लिखो_config_count		: increase with every configuration change
 * @drive_inserted_count	: increase with every drive inserted
 * @inserted_drive		: channel:Id of inserted drive
 * @battery_status		: bit 0: battery module missing
 *				bit 1: VBAD
 *				bit 2: temperature high
 *				bit 3: battery pack missing
 *				bit 4,5:
 *					00 - अक्षरge complete
 *					01 - fast अक्षरge in progress
 *					10 - fast अक्षरge fail
 *					11 - undefined
 *				bit 6: counter > 1000
 *				bit 7: Undefined
 * @dec_fault_bus_info		:
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		max_commands;
	uपूर्णांक8_t		rebuild_rate;
	uपूर्णांक8_t		max_targ_per_chan;
	uपूर्णांक8_t		nchannels;
	uपूर्णांक8_t		fw_version[4];
	uपूर्णांक16_t	age_of_flash;
	uपूर्णांक8_t		chip_set_value;
	uपूर्णांक8_t		dram_size;
	uपूर्णांक8_t		cache_flush_पूर्णांकerval;
	uपूर्णांक8_t		bios_version[4];
	uपूर्णांक8_t		board_type;
	uपूर्णांक8_t		sense_alert;
	uपूर्णांक8_t		ग_लिखो_config_count;
	uपूर्णांक8_t		battery_status;
	uपूर्णांक8_t		dec_fault_bus_info;
पूर्ण __attribute__ ((packed)) mraid_adapinfo_t;


/**
 * mraid_ldrv_info_t - inक्रमmation about the logical drives
 * @nldrv	: Number of logical drives configured
 * @rsvd	:
 * @size	: size of each logical drive
 * @prop	:
 * @state	: state of each logical drive
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		nldrv;
	uपूर्णांक8_t		rsvd[3];
	uपूर्णांक32_t	size[MAX_LOGICAL_DRIVES_8LD];
	uपूर्णांक8_t		prop[MAX_LOGICAL_DRIVES_8LD];
	uपूर्णांक8_t		state[MAX_LOGICAL_DRIVES_8LD];
पूर्ण __attribute__ ((packed)) mraid_ldrv_info_t;


/**
 * mraid_pdrv_info_t - inक्रमmation about the physical drives
 * @pdrv_state	: state of each physical drive
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		pdrv_state[MBOX_MAX_PHYSICAL_DRIVES];
	uपूर्णांक8_t		rsvd;
पूर्ण __attribute__ ((packed)) mraid_pdrv_info_t;


/**
 * mraid_inquiry_t - RAID inquiry, mailbox command 0x05
 * @mraid_adapinfo_t	: adapter inक्रमmation
 * @mraid_ldrv_info_t	: logical drives inक्रमmation
 * @mraid_pdrv_info_t	: physical drives inक्रमmation
 */
प्रकार काष्ठा अणु
	mraid_adapinfo_t	adapter_info;
	mraid_ldrv_info_t	logdrv_info;
	mraid_pdrv_info_t	pdrv_info;
पूर्ण __attribute__ ((packed)) mraid_inquiry_t;


/**
 * mraid_extinq_t - RAID extended inquiry, mailbox command 0x04
 *
 * @raid_inq		: raid inquiry
 * @phys_drv_क्रमmat	:
 * @stack_attn		:
 * @modem_status	:
 * @rsvd		:
 */
प्रकार काष्ठा अणु
	mraid_inquiry_t	raid_inq;
	uपूर्णांक16_t	phys_drv_क्रमmat[MAX_MBOX_CHANNELS];
	uपूर्णांक8_t		stack_attn;
	uपूर्णांक8_t		modem_status;
	uपूर्णांक8_t		rsvd[2];
पूर्ण __attribute__ ((packed)) mraid_extinq_t;


/**
 * adap_device_t - device inक्रमmation
 * @channel	: channel fpor the device
 * @target	: target ID of the device
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		channel;
	uपूर्णांक8_t		target;
पूर्ण__attribute__ ((packed)) adap_device_t;


/**
 * adap_span_40ld_t - 40LD span
 * @start_blk	: starting block
 * @num_blks	: number of blocks
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t	start_blk;
	uपूर्णांक32_t	num_blks;
	adap_device_t	device[MAX_ROW_SIZE_40LD];
पूर्ण__attribute__ ((packed)) adap_span_40ld_t;


/**
 * adap_span_8ld_t - 8LD span
 * @start_blk	: starting block
 * @num_blks	: number of blocks
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t	start_blk;
	uपूर्णांक32_t	num_blks;
	adap_device_t	device[MAX_ROW_SIZE_8LD];
पूर्ण__attribute__ ((packed)) adap_span_8ld_t;


/**
 * logdrv_param_t - logical drives parameters
 *
 * @span_depth	: total number of spans
 * @level	: RAID level
 * @पढ़ो_ahead	: पढ़ो ahead, no पढ़ो ahead, adaptive पढ़ो ahead
 * @stripe_sz	: encoded stripe size
 * @status	: status of the logical drive
 * @ग_लिखो_mode	: ग_लिखो mode, ग_लिखो_through/ग_लिखो_back
 * @direct_io	: direct io or through cache
 * @row_size	: number of stripes in a row
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		span_depth;
	uपूर्णांक8_t		level;
	uपूर्णांक8_t		पढ़ो_ahead;
	uपूर्णांक8_t		stripe_sz;
	uपूर्णांक8_t		status;
	uपूर्णांक8_t		ग_लिखो_mode;
	uपूर्णांक8_t		direct_io;
	uपूर्णांक8_t		row_size;
पूर्ण __attribute__ ((packed)) logdrv_param_t;


/**
 * logdrv_40ld_t - logical drive definition क्रम 40LD controllers
 * @lparam	: logical drives parameters
 * @span	: span
 */
प्रकार काष्ठा अणु
	logdrv_param_t		lparam;
	adap_span_40ld_t	span[SPAN_DEPTH_8_SPANS];
पूर्ण__attribute__ ((packed)) logdrv_40ld_t;


/**
 * logdrv_8ld_span8_t - logical drive definition क्रम 8LD controllers
 * @lparam	: logical drives parameters
 * @span	: span
 *
 * 8-LD logical drive with up to 8 spans
 */
प्रकार काष्ठा अणु
	logdrv_param_t	lparam;
	adap_span_8ld_t	span[SPAN_DEPTH_8_SPANS];
पूर्ण__attribute__ ((packed)) logdrv_8ld_span8_t;


/**
 * logdrv_8ld_span4_t - logical drive definition क्रम 8LD controllers
 * @lparam	: logical drives parameters
 * @span	: span
 *
 * 8-LD logical drive with up to 4 spans
 */
प्रकार काष्ठा अणु
	logdrv_param_t	lparam;
	adap_span_8ld_t	span[SPAN_DEPTH_4_SPANS];
पूर्ण__attribute__ ((packed)) logdrv_8ld_span4_t;


/**
 * phys_drive_t - physical device inक्रमmation
 * @type	: Type of the device
 * @cur_status	: current status of the device
 * @tag_depth	: Level of tagging
 * @sync_neg	: sync negotiation - ENABLE or DISABLE
 * @size	: configurable size in terms of 512 byte
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		cur_status;
	uपूर्णांक8_t		tag_depth;
	uपूर्णांक8_t		sync_neg;
	uपूर्णांक32_t	size;
पूर्ण__attribute__ ((packed)) phys_drive_t;


/**
 * disk_array_40ld_t - disk array क्रम 40LD controllers
 * @numldrv	: number of logical drives
 * @resvd	:
 * @ldrv	: logical drives inक्रमmation
 * @pdrv	: physical drives inक्रमmation
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		numldrv;
	uपूर्णांक8_t		resvd[3];
	logdrv_40ld_t	ldrv[MAX_LOGICAL_DRIVES_40LD];
	phys_drive_t	pdrv[MBOX_MAX_PHYSICAL_DRIVES];
पूर्ण__attribute__ ((packed)) disk_array_40ld_t;


/**
 * disk_array_8ld_span8_t - disk array क्रम 8LD controllers
 * @numldrv	: number of logical drives
 * @resvd	:
 * @ldrv	: logical drives inक्रमmation
 * @pdrv	: physical drives inक्रमmation
 *
 * Disk array क्रम 8LD logical drives with up to 8 spans
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t			numldrv;
	uपूर्णांक8_t			resvd[3];
	logdrv_8ld_span8_t	ldrv[MAX_LOGICAL_DRIVES_8LD];
	phys_drive_t		pdrv[MBOX_MAX_PHYSICAL_DRIVES];
पूर्ण__attribute__ ((packed)) disk_array_8ld_span8_t;


/**
 * disk_array_8ld_span4_t - disk array क्रम 8LD controllers
 * @numldrv	: number of logical drives
 * @resvd	:
 * @ldrv	: logical drives inक्रमmation
 * @pdrv	: physical drives inक्रमmation
 *
 * Disk array क्रम 8LD logical drives with up to 4 spans
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t			numldrv;
	uपूर्णांक8_t			resvd[3];
	logdrv_8ld_span4_t	ldrv[MAX_LOGICAL_DRIVES_8LD];
	phys_drive_t		pdrv[MBOX_MAX_PHYSICAL_DRIVES];
पूर्ण__attribute__ ((packed)) disk_array_8ld_span4_t;


/**
 * काष्ठा निजी_bios_data - bios निजी data क्रम boot devices
 * @geometry	: bits 0-3 - BIOS geometry, 0x0001 - 1GB, 0x0010 - 2GB,
 *		0x1000 - 8GB, Others values are invalid
 * @unused	: bits 4-7 are unused
 * @boot_drv	: logical drive set as boot drive, 0..7 - क्रम 8LD cards,
 * 		0..39 - क्रम 40LD cards
 * @cksum	: 0-(sum of first 13 bytes of this काष्ठाure)
 */
काष्ठा निजी_bios_data अणु
	uपूर्णांक8_t		geometry	:4;
	uपूर्णांक8_t		unused		:4;
	uपूर्णांक8_t		boot_drv;
	uपूर्णांक8_t		rsvd[12];
	uपूर्णांक16_t	cksum;
पूर्ण __attribute__ ((packed));


/**
 * mbox_sgl64 - 64-bit scatter list क्रम mailbox based controllers
 * @address	: address of the buffer
 * @length	: data transfer length
 */
प्रकार काष्ठा अणु
	uपूर्णांक64_t	address;
	uपूर्णांक32_t	length;
पूर्ण __attribute__ ((packed)) mbox_sgl64;

/**
 * mbox_sgl32 - 32-bit scatter list क्रम mailbox based controllers
 * @address	: address of the buffer
 * @length	: data transfer length
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t	address;
	uपूर्णांक32_t	length;
पूर्ण __attribute__ ((packed)) mbox_sgl32;

#पूर्ण_अगर		// _MRAID_MBOX_DEFS_H_
