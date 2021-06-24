<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MEGARAID_H__
#घोषणा __MEGARAID_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>

#घोषणा MEGARAID_VERSION	\
	"v2.00.4 (Release Date: Thu Feb 9 08:51:30 EST 2006)\n"

/*
 * Driver features - change the values to enable or disable features in the
 * driver.
 */

/*
 * Command coalescing - This feature allows the driver to be able to combine
 * two or more commands and issue as one command in order to boost I/O
 * perक्रमmance. Useful अगर the nature of the I/O is sequential. It is not very
 * useful क्रम अक्रमom natured I/Os.
 */
#घोषणा MEGA_HAVE_COALESCING	0

/*
 * Clustering support - Set this flag अगर you are planning to use the
 * clustering services provided by the megaraid controllers and planning to
 * setup a cluster
 */
#घोषणा MEGA_HAVE_CLUSTERING	1

/*
 * Driver statistics - Set this flag अगर you are पूर्णांकerested in अटलs about
 * number of I/O completed on each logical drive and how many पूर्णांकerrupts
 * generated. If enabled, this inक्रमmation is available through /proc
 * पूर्णांकerface and through the निजी ioctl. Setting this flag has a
 * perक्रमmance penalty.
 */
#घोषणा MEGA_HAVE_STATS		0

/*
 * Enhanced /proc पूर्णांकerface - This feature will allow you to have a more
 * detailed /proc पूर्णांकerface क्रम megaraid driver. E.g., a real समय update of
 * the status of the logical drives, battery status, physical drives etc.
 */
#घोषणा MEGA_HAVE_ENH_PROC	1

#घोषणा MAX_DEV_TYPE	32

#घोषणा PCI_DEVICE_ID_DISCOVERY		0x000E
#घोषणा PCI_DEVICE_ID_PERC4_DI		0x000F
#घोषणा PCI_DEVICE_ID_PERC4_QC_VERDE	0x0407

#घोषणा HBA_SIGNATURE	      		0x3344
#घोषणा HBA_SIGNATURE_471	  	0xCCCC
#घोषणा HBA_SIGNATURE_64BIT		0x0299

#घोषणा MBOX_BUSY_WAIT			10	/* रुको क्रम up to 10 usec क्रम
						   mailbox to be मुक्त */
#घोषणा DEFAULT_INITIATOR_ID	7

#घोषणा MAX_SGLIST		64	/* max supported in f/w */
#घोषणा MIN_SGLIST		26	/* guaranteed to support these many */
#घोषणा MAX_COMMANDS		126
#घोषणा CMDID_INT_CMDS		MAX_COMMANDS+1	/* make sure CMDID_INT_CMDS
					 	is less than max commands
						supported by any f/w */

#घोषणा MAX_CDB_LEN	     	10
#घोषणा MAX_EXT_CDB_LEN		16	/* we support cdb length up to 16 */

#घोषणा DEF_CMD_PER_LUN		63
#घोषणा MAX_CMD_PER_LUN		MAX_COMMANDS
#घोषणा MAX_FIRMWARE_STATUS	46
#घोषणा MAX_XFER_PER_CMD	(64*1024)
#घोषणा MAX_SECTORS_PER_IO	128

#घोषणा MAX_LOGICAL_DRIVES_40LD		40
#घोषणा FC_MAX_PHYSICAL_DEVICES		256
#घोषणा MAX_LOGICAL_DRIVES_8LD		8
#घोषणा MAX_CHANNELS			5
#घोषणा MAX_TARGET			15
#घोषणा MAX_PHYSICAL_DRIVES		MAX_CHANNELS*MAX_TARGET
#घोषणा MAX_ROW_SIZE_40LD		32
#घोषणा MAX_ROW_SIZE_8LD		8
#घोषणा MAX_SPAN_DEPTH			8

#घोषणा NVIRT_CHAN		4	/* # of भव channels to represent
					   up to 60 logical drives */
काष्ठा mbox_out अणु
	/* 0x0 */ u8 cmd;
	/* 0x1 */ u8 cmdid;
	/* 0x2 */ u16 numsectors;
	/* 0x4 */ u32 lba;
	/* 0x8 */ u32 xferaddr;
	/* 0xC */ u8 logdrv;
	/* 0xD */ u8 numsgelements;
	/* 0xE */ u8 resvd;
पूर्ण __attribute__ ((packed));

काष्ठा mbox_in अणु
	/* 0xF */ अस्थिर u8 busy;
	/* 0x10 */ अस्थिर u8 numstatus;
	/* 0x11 */ अस्थिर u8 status;
	/* 0x12 */ अस्थिर u8 completed[MAX_FIRMWARE_STATUS];
	अस्थिर u8 poll;
	अस्थिर u8 ack;
पूर्ण __attribute__ ((packed));

प्रकार काष्ठा अणु
	काष्ठा mbox_out	m_out;
	काष्ठा mbox_in	m_in;
पूर्ण __attribute__ ((packed)) mbox_t;

प्रकार काष्ठा अणु
	u32 xfer_segment_lo;
	u32 xfer_segment_hi;
	mbox_t mbox;
पूर्ण __attribute__ ((packed)) mbox64_t;


/*
 * Passthru definitions
 */
#घोषणा MAX_REQ_SENSE_LEN       0x20

प्रकार काष्ठा अणु
	u8 समयout:3;		/* 0=6sec/1=60sec/2=10min/3=3hrs */
	u8 ars:1;
	u8 reserved:3;
	u8 islogical:1;
	u8 logdrv;		/* अगर islogical == 1 */
	u8 channel;		/* अगर islogical == 0 */
	u8 target;		/* अगर islogical == 0 */
	u8 queuetag;		/* unused */
	u8 queueaction;		/* unused */
	u8 cdb[MAX_CDB_LEN];
	u8 cdblen;
	u8 reqsenselen;
	u8 reqsensearea[MAX_REQ_SENSE_LEN];
	u8 numsgelements;
	u8 scsistatus;
	u32 dataxferaddr;
	u32 dataxferlen;
पूर्ण __attribute__ ((packed)) mega_passthru;


/*
 * Extended passthru: support CDB > 10 bytes
 */
प्रकार काष्ठा अणु
	u8 समयout:3;		/* 0=6sec/1=60sec/2=10min/3=3hrs */
	u8 ars:1;
	u8 rsvd1:1;
	u8 cd_rom:1;
	u8 rsvd2:1;
	u8 islogical:1;
	u8 logdrv;		/* अगर islogical == 1 */
	u8 channel;		/* अगर islogical == 0 */
	u8 target;		/* अगर islogical == 0 */
	u8 queuetag;		/* unused */
	u8 queueaction;		/* unused */
	u8 cdblen;
	u8 rsvd3;
	u8 cdb[MAX_EXT_CDB_LEN];
	u8 numsgelements;
	u8 status;
	u8 reqsenselen;
	u8 reqsensearea[MAX_REQ_SENSE_LEN];
	u8 rsvd4;
	u32 dataxferaddr;
	u32 dataxferlen;
पूर्ण __attribute__ ((packed)) mega_ext_passthru;

प्रकार काष्ठा अणु
	u64 address;
	u32 length;
पूर्ण __attribute__ ((packed)) mega_sgl64;

प्रकार काष्ठा अणु
	u32 address;
	u32 length;
पूर्ण __attribute__ ((packed)) mega_sglist;


/* Queued command data */
प्रकार काष्ठा अणु
	पूर्णांक	idx;
	u32	state;
	काष्ठा list_head	list;
	u8	raw_mbox[66];
	u32	dma_type;
	u32	dma_direction;

	काष्ठा scsi_cmnd	*cmd;
	dma_addr_t	dma_h_bulkdata;
	dma_addr_t	dma_h_sgdata;

	mega_sglist	*sgl;
	mega_sgl64	*sgl64;
	dma_addr_t	sgl_dma_addr;

	mega_passthru		*pthru;
	dma_addr_t		pthru_dma_addr;
	mega_ext_passthru	*epthru;
	dma_addr_t		epthru_dma_addr;
पूर्ण scb_t;

/*
 * Flags to follow the scb as it transitions between various stages
 */
#घोषणा SCB_FREE	0x0000	/* on the मुक्त list */
#घोषणा SCB_ACTIVE	0x0001	/* off the मुक्त list */
#घोषणा SCB_PENDQ	0x0002	/* on the pending queue */
#घोषणा SCB_ISSUED	0x0004	/* issued - owner f/w */
#घोषणा SCB_ABORT	0x0008	/* Got an पात क्रम this one */
#घोषणा SCB_RESET	0x0010	/* Got a reset क्रम this one */

/*
 * Utilities declare this strcture size as 1024 bytes. So more fields can
 * be added in future.
 */
प्रकार काष्ठा अणु
	u32	data_size; /* current size in bytes (not including resvd) */

	u32	config_signature;
		/* Current value is 0x00282008
		 * 0x28=MAX_LOGICAL_DRIVES,
		 * 0x20=Number of stripes and
		 * 0x08=Number of spans */

	u8	fw_version[16];		/* prपूर्णांकable ASCI string */
	u8	bios_version[16];	/* prपूर्णांकable ASCI string */
	u8	product_name[80];	/* prपूर्णांकable ASCI string */

	u8	max_commands;		/* Max. concurrent commands supported */
	u8	nchannels;		/* Number of SCSI Channels detected */
	u8	fc_loop_present;	/* Number of Fibre Loops detected */
	u8	mem_type;		/* EDO, FPM, SDRAM etc */

	u32	signature;
	u16	dram_size;		/* In terms of MB */
	u16	subsysid;

	u16	subsysvid;
	u8	notअगरy_counters;
	u8	pad1k[889];		/* 135 + 889 resvd = 1024 total size */
पूर्ण __attribute__ ((packed)) mega_product_info;

काष्ठा notअगरy अणु
	u32 global_counter;	/* Any change increments this counter */

	u8 param_counter;	/* Indicates any params changed  */
	u8 param_id;		/* Param modअगरied - defined below */
	u16 param_val;		/* New val of last param modअगरied */

	u8 ग_लिखो_config_counter;	/* ग_लिखो config occurred */
	u8 ग_लिखो_config_rsvd[3];

	u8 ldrv_op_counter;	/* Indicates ldrv op started/completed */
	u8 ldrv_opid;		/* ldrv num */
	u8 ldrv_opcmd;		/* ldrv operation - defined below */
	u8 ldrv_opstatus;	/* status of the operation */

	u8 ldrv_state_counter;	/* Indicates change of ldrv state */
	u8 ldrv_state_id;		/* ldrv num */
	u8 ldrv_state_new;	/* New state */
	u8 ldrv_state_old;	/* old state */

	u8 pdrv_state_counter;	/* Indicates change of ldrv state */
	u8 pdrv_state_id;		/* pdrv id */
	u8 pdrv_state_new;	/* New state */
	u8 pdrv_state_old;	/* old state */

	u8 pdrv_fmt_counter;	/* Indicates pdrv क्रमmat started/over */
	u8 pdrv_fmt_id;		/* pdrv id */
	u8 pdrv_fmt_val;		/* क्रमmat started/over */
	u8 pdrv_fmt_rsvd;

	u8 targ_xfer_counter;	/* Indicates SCSI-2 Xfer rate change */
	u8 targ_xfer_id;	/* pdrv Id  */
	u8 targ_xfer_val;		/* new Xfer params of last pdrv */
	u8 targ_xfer_rsvd;

	u8 fcloop_id_chg_counter;	/* Indicates loopid changed */
	u8 fcloopid_pdrvid;		/* pdrv id */
	u8 fcloop_id0;			/* loopid on fc loop 0 */
	u8 fcloop_id1;			/* loopid on fc loop 1 */

	u8 fcloop_state_counter;	/* Indicates loop state changed */
	u8 fcloop_state0;		/* state of fc loop 0 */
	u8 fcloop_state1;		/* state of fc loop 1 */
	u8 fcloop_state_rsvd;
पूर्ण __attribute__ ((packed));

#घोषणा MAX_NOTIFY_SIZE     0x80
#घोषणा CUR_NOTIFY_SIZE     माप(काष्ठा notअगरy)

प्रकार काष्ठा अणु
	u32	data_size; /* current size in bytes (not including resvd) */

	काष्ठा notअगरy notअगरy;

	u8	notअगरy_rsvd[MAX_NOTIFY_SIZE - CUR_NOTIFY_SIZE];

	u8	rebuild_rate;		/* Rebuild rate (0% - 100%) */
	u8	cache_flush_पूर्णांकerval;	/* In terms of Seconds */
	u8	sense_alert;
	u8	drive_insert_count;	/* drive insertion count */

	u8	battery_status;
	u8	num_ldrv;		/* No. of Log Drives configured */
	u8	recon_state[MAX_LOGICAL_DRIVES_40LD / 8];	/* State of
							   reस्थिरruct */
	u16	ldrv_op_status[MAX_LOGICAL_DRIVES_40LD / 8]; /* logdrv
								 Status */

	u32	ldrv_size[MAX_LOGICAL_DRIVES_40LD];/* Size of each log drv */
	u8	ldrv_prop[MAX_LOGICAL_DRIVES_40LD];
	u8	ldrv_state[MAX_LOGICAL_DRIVES_40LD];/* State of log drives */
	u8	pdrv_state[FC_MAX_PHYSICAL_DEVICES];/* State of phys drvs. */
	u16	pdrv_क्रमmat[FC_MAX_PHYSICAL_DEVICES / 16];

	u8	targ_xfer[80];	/* phys device transfer rate */
	u8	pad1k[263];	/* 761 + 263reserved = 1024 bytes total size */
पूर्ण __attribute__ ((packed)) mega_inquiry3;


/* Structures */
प्रकार काष्ठा अणु
	u8	max_commands;	/* Max concurrent commands supported */
	u8	rebuild_rate;	/* Rebuild rate - 0% thru 100% */
	u8	max_targ_per_chan;	/* Max targ per channel */
	u8	nchannels;	/* Number of channels on HBA */
	u8	fw_version[4];	/* Firmware version */
	u16	age_of_flash;	/* Number of बार FW has been flashed */
	u8	chip_set_value;	/* Contents of 0xC0000832 */
	u8	dram_size;	/* In MB */
	u8	cache_flush_पूर्णांकerval;	/* in seconds */
	u8	bios_version[4];
	u8	board_type;
	u8	sense_alert;
	u8	ग_लिखो_config_count;	/* Increase with every configuration
					   change */
	u8	drive_inserted_count;	/* Increase with every drive inserted
					 */
	u8	inserted_drive;	/* Channel:Id of inserted drive */
	u8	battery_status;	/*
				 * BIT 0: battery module missing
				 * BIT 1: VBAD
				 * BIT 2: temperature high
				 * BIT 3: battery pack missing
				 * BIT 4,5:
				 *   00 - अक्षरge complete
				 *   01 - fast अक्षरge in progress
				 *   10 - fast अक्षरge fail
				 *   11 - undefined
				 * Bit 6: counter > 1000
				 * Bit 7: Undefined
				 */
	u8	dec_fault_bus_info;
पूर्ण __attribute__ ((packed)) mega_adp_info;


प्रकार काष्ठा अणु
	u8	num_ldrv;	/* Number of logical drives configured */
	u8	rsvd[3];
	u32	ldrv_size[MAX_LOGICAL_DRIVES_8LD];
	u8	ldrv_prop[MAX_LOGICAL_DRIVES_8LD];
	u8	ldrv_state[MAX_LOGICAL_DRIVES_8LD];
पूर्ण __attribute__ ((packed)) mega_ldrv_info;

प्रकार काष्ठा अणु
	u8	pdrv_state[MAX_PHYSICAL_DRIVES];
	u8	rsvd;
पूर्ण __attribute__ ((packed)) mega_pdrv_info;

/* RAID inquiry: Mailbox command 0x05*/
प्रकार काष्ठा अणु
	mega_adp_info	adapter_info;
	mega_ldrv_info	logdrv_info;
	mega_pdrv_info	pdrv_info;
पूर्ण __attribute__ ((packed)) mraid_inquiry;


/* RAID extended inquiry: Mailbox command 0x04*/
प्रकार काष्ठा अणु
	mraid_inquiry	raid_inq;
	u16	phys_drv_क्रमmat[MAX_CHANNELS];
	u8	stack_attn;
	u8	modem_status;
	u8	rsvd[2];
पूर्ण __attribute__ ((packed)) mraid_ext_inquiry;


प्रकार काष्ठा अणु
	u8	channel;
	u8	target;
पूर्ण__attribute__ ((packed)) adp_device;

प्रकार काष्ठा अणु
	u32		start_blk;	/* starting block */
	u32		num_blks;	/* # of blocks */
	adp_device	device[MAX_ROW_SIZE_40LD];
पूर्ण__attribute__ ((packed)) adp_span_40ld;

प्रकार काष्ठा अणु
	u32		start_blk;	/* starting block */
	u32		num_blks;	/* # of blocks */
	adp_device	device[MAX_ROW_SIZE_8LD];
पूर्ण__attribute__ ((packed)) adp_span_8ld;

प्रकार काष्ठा अणु
	u8	span_depth;	/* Total # of spans */
	u8	level;		/* RAID level */
	u8	पढ़ो_ahead;	/* पढ़ो ahead, no पढ़ो ahead, adaptive पढ़ो
				   ahead */
	u8	stripe_sz;	/* Encoded stripe size */
	u8	status;		/* Status of the logical drive */
	u8	ग_लिखो_mode;	/* ग_लिखो mode, ग_लिखो_through/ग_लिखो_back */
	u8	direct_io;	/* direct io or through cache */
	u8	row_size;	/* Number of stripes in a row */
पूर्ण __attribute__ ((packed)) logdrv_param;

प्रकार काष्ठा अणु
	logdrv_param	lparam;
	adp_span_40ld	span[MAX_SPAN_DEPTH];
पूर्ण__attribute__ ((packed)) logdrv_40ld;

प्रकार काष्ठा अणु
	logdrv_param	lparam;
	adp_span_8ld	span[MAX_SPAN_DEPTH];
पूर्ण__attribute__ ((packed)) logdrv_8ld;

प्रकार काष्ठा अणु
	u8	type;		/* Type of the device */
	u8	cur_status;	/* current status of the device */
	u8	tag_depth;	/* Level of tagging */
	u8	sync_neg;	/* sync negotiation - ENABLE or DISABLE */
	u32	size;		/* configurable size in terms of 512 byte
				   blocks */
पूर्ण__attribute__ ((packed)) phys_drv;

प्रकार काष्ठा अणु
	u8		nlog_drives;		/* number of logical drives */
	u8		resvd[3];
	logdrv_40ld	ldrv[MAX_LOGICAL_DRIVES_40LD];
	phys_drv	pdrv[MAX_PHYSICAL_DRIVES];
पूर्ण__attribute__ ((packed)) disk_array_40ld;

प्रकार काष्ठा अणु
	u8		nlog_drives;	/* number of logical drives */
	u8		resvd[3];
	logdrv_8ld	ldrv[MAX_LOGICAL_DRIVES_8LD];
	phys_drv	pdrv[MAX_PHYSICAL_DRIVES];
पूर्ण__attribute__ ((packed)) disk_array_8ld;


/*
 * User ioctl काष्ठाure.
 * This काष्ठाure will be used क्रम Traditional Method ioctl पूर्णांकerface
 * commands (0x80),Alternate Buffer Method (0x81) ioctl commands and the
 * Driver ioctls.
 * The Driver ioctl पूर्णांकerface handles the commands at the driver level,
 * without being sent to the card.
 */
/* प्रणाली call imposed limit. Change accordingly */
#घोषणा IOCTL_MAX_DATALEN       4096

काष्ठा uioctl_t अणु
	u32 inlen;
	u32 outlen;
	जोड़ अणु
		u8 fca[16];
		काष्ठा अणु
			u8 opcode;
			u8 subopcode;
			u16 adapno;
#अगर BITS_PER_LONG == 32
			u8 *buffer;
			u8 pad[4];
#पूर्ण_अगर
#अगर BITS_PER_LONG == 64
			u8 *buffer;
#पूर्ण_अगर
			u32 length;
		पूर्ण __attribute__ ((packed)) fcs;
	पूर्ण __attribute__ ((packed)) ui;
	u8 mbox[18];		/* 16 bytes + 2 status bytes */
	mega_passthru pthru;
#अगर BITS_PER_LONG == 32
	अक्षर __user *data;		/* buffer <= 4096 क्रम 0x80 commands */
	अक्षर pad[4];
#पूर्ण_अगर
#अगर BITS_PER_LONG == 64
	अक्षर __user *data;
#पूर्ण_अगर
पूर्ण __attribute__ ((packed));

/*
 * काष्ठा mcontroller is used to pass inक्रमmation about the controllers in the
 * प्रणाली. Its up to the application how to use the inक्रमmation. We are passing
 * as much info about the cards as possible and useful. Beक्रमe issuing the
 * call to find inक्रमmation about the cards, the application needs to issue a
 * ioctl first to find out the number of controllers in the प्रणाली.
 */
#घोषणा MAX_CONTROLLERS 32

काष्ठा mcontroller अणु
	u64 base;
	u8 irq;
	u8 numldrv;
	u8 pcibus;
	u16 pcidev;
	u8 pcअगरun;
	u16 pciid;
	u16 pcivenकरोr;
	u8 pcislot;
	u32 uid;
पूर्ण;

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
पूर्ण __attribute__ ((packed)) megacmd_t;

/*
 * Defines क्रम Driver IOCTL पूर्णांकerface
 */
#घोषणा MEGAIOC_MAGIC  	'm'

#घोषणा MEGAIOC_QNADAP		'm'	/* Query # of adapters */
#घोषणा MEGAIOC_QDRVRVER	'e'	/* Query driver version */
#घोषणा MEGAIOC_QADAPINFO   	'g'	/* Query adapter inक्रमmation */
#घोषणा MKADAP(adapno)	  	(MEGAIOC_MAGIC << 8 | (adapno) )
#घोषणा GETADAP(mkadap)	 	( (mkadap) ^ MEGAIOC_MAGIC << 8 )

/*
 * Definition क्रम the new ioctl पूर्णांकerface (NIT)
 */

/*
 * Venकरोr specअगरic Group-7 commands
 */
#घोषणा VENDOR_SPECIFIC_COMMANDS	0xE0
#घोषणा MEGA_INTERNAL_CMD		VENDOR_SPECIFIC_COMMANDS + 0x01

/*
 * The ioctl command. No other command shall be used क्रम this पूर्णांकerface
 */
#घोषणा USCSICMD	VENDOR_SPECIFIC_COMMANDS

/*
 * Data direction flags
 */
#घोषणा UIOC_RD		0x00001
#घोषणा UIOC_WR		0x00002

/*
 * ioctl opcodes
 */
#घोषणा MBOX_CMD	0x00000	/* DCMD or passthru command */
#घोषणा GET_DRIVER_VER	0x10000	/* Get driver version */
#घोषणा GET_N_ADAP	0x20000	/* Get number of adapters */
#घोषणा GET_ADAP_INFO	0x30000	/* Get inक्रमmation about a adapter */
#घोषणा GET_CAP		0x40000	/* Get ioctl capabilities */
#घोषणा GET_STATS	0x50000	/* Get statistics, including error info */


/*
 * The ioctl काष्ठाure.
 * MBOX macro converts a nitioctl_t काष्ठाure to megacmd_t poपूर्णांकer and
 * MBOX_P macro converts a nitioctl_t poपूर्णांकer to megacmd_t poपूर्णांकer.
 */
प्रकार काष्ठा अणु
	अक्षर		signature[8];	/* Must contain "MEGANIT" */
	u32		opcode;		/* opcode क्रम the command */
	u32		adapno;		/* adapter number */
	जोड़ अणु
		u8	__raw_mbox[18];
		व्योम __user *__uaddr; /* xferaddr क्रम non-mbox cmds */
	पूर्ण__ua;

#घोषणा uioc_rmbox	__ua.__raw_mbox
#घोषणा MBOX(uioc)	((megacmd_t *)&((uioc).__ua.__raw_mbox[0]))
#घोषणा MBOX_P(uioc)	((megacmd_t __user *)&((uioc)->__ua.__raw_mbox[0]))
#घोषणा uioc_uaddr	__ua.__uaddr

	u32		xferlen;	/* xferlen क्रम DCMD and non-mbox
					   commands */
	u32		flags;		/* data direction flags */
पूर्णnitioctl_t;


/*
 * I/O statistics क्रम some applications like SNMP agent. The caller must
 * provide the number of logical drives क्रम which status should be reported.
 */
प्रकार काष्ठा अणु
	पूर्णांक	num_ldrv;	/* Number क्रम logical drives क्रम which the
				   status should be reported. */
	u32	nपढ़ोs[MAX_LOGICAL_DRIVES_40LD];	/* number of पढ़ोs क्रम
							each logical drive */
	u32	nपढ़ोblocks[MAX_LOGICAL_DRIVES_40LD];	/* number of blocks
							पढ़ो क्रम each logical
							drive */
	u32	nग_लिखोs[MAX_LOGICAL_DRIVES_40LD];	/* number of ग_लिखोs
							क्रम each logical
							drive */
	u32	nग_लिखोblocks[MAX_LOGICAL_DRIVES_40LD];	/* number of blocks
							ग_लिखोs क्रम each
							logical drive */
	u32	rd_errors[MAX_LOGICAL_DRIVES_40LD];	/* number of पढ़ो
							   errors क्रम each
							   logical drive */
	u32	wr_errors[MAX_LOGICAL_DRIVES_40LD];	/* number of ग_लिखो
							   errors क्रम each
							   logical drive */
पूर्णmegastat_t;


काष्ठा निजी_bios_data अणु
	u8	geometry:4;	/*
				 * bits 0-3 - BIOS geometry
				 * 0x0001 - 1GB
				 * 0x0010 - 2GB
				 * 0x1000 - 8GB
				 * Others values are invalid
							 */
	u8	unused:4;	/* bits 4-7 are unused */
	u8	boot_drv;	/*
				 * logical drive set as boot drive
				 * 0..7 - क्रम 8LD cards
				 * 0..39 - क्रम 40LD cards
				 */
	u8	rsvd[12];
	u16	cksum;	/* 0-(sum of first 13 bytes of this काष्ठाure) */
पूर्ण __attribute__ ((packed));




/*
 * Mailbox and firmware commands and subopcodes used in this driver.
 */

#घोषणा MEGA_MBOXCMD_LREAD	0x01
#घोषणा MEGA_MBOXCMD_LWRITE	0x02
#घोषणा MEGA_MBOXCMD_PASSTHRU	0x03
#घोषणा MEGA_MBOXCMD_ADPEXTINQ	0x04
#घोषणा MEGA_MBOXCMD_ADAPTERINQ	0x05
#घोषणा MEGA_MBOXCMD_LREAD64	0xA7
#घोषणा MEGA_MBOXCMD_LWRITE64	0xA8
#घोषणा MEGA_MBOXCMD_PASSTHRU64	0xC3
#घोषणा MEGA_MBOXCMD_EXTPTHRU	0xE3

#घोषणा MAIN_MISC_OPCODE	0xA4	/* f/w misc opcode */
#घोषणा GET_MAX_SG_SUPPORT	0x01	/* get max sg len supported by f/w */

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
#घोषणा	FC_DEL_LOGDRV		0xA4	/* f/w command */
#घोषणा	OP_SUP_DEL_LOGDRV	0x2A	/* is feature supported */
#घोषणा OP_GET_LDID_MAP		0x18	/* get ldid and logdrv number map */
#घोषणा OP_DEL_LOGDRV		0x1C	/* delete logical drive */

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
#घोषणा MEGA_GET_TARGET_ID	0x7D
#घोषणा MEGA_CLUSTER_OP		0x70
#घोषणा MEGA_GET_CLUSTER_MODE	0x02
#घोषणा MEGA_CLUSTER_CMD	0x6E
#घोषणा MEGA_RESERVE_LD		0x01
#घोषणा MEGA_RELEASE_LD		0x02
#घोषणा MEGA_RESET_RESERVATIONS	0x03
#घोषणा MEGA_RESERVATION_STATUS	0x04
#घोषणा MEGA_RESERVE_PD		0x05
#घोषणा MEGA_RELEASE_PD		0x06


/*
 * Module battery status
 */
#घोषणा MEGA_BATT_MODULE_MISSING	0x01
#घोषणा MEGA_BATT_LOW_VOLTAGE		0x02
#घोषणा MEGA_BATT_TEMP_HIGH		0x04
#घोषणा MEGA_BATT_PACK_MISSING		0x08
#घोषणा MEGA_BATT_CHARGE_MASK		0x30
#घोषणा MEGA_BATT_CHARGE_DONE		0x00
#घोषणा MEGA_BATT_CHARGE_INPROG		0x10
#घोषणा MEGA_BATT_CHARGE_FAIL		0x20
#घोषणा MEGA_BATT_CYCLES_EXCEEDED	0x40

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


#घोषणा SCSI_LIST(scp) ((काष्ठा list_head *)(&(scp)->SCp))

/*
 * Each controller's soft state
 */
प्रकार काष्ठा अणु
	पूर्णांक	this_id;	/* our id, may set to dअगरferent than 7 अगर
				   clustering is available */
	u32	flag;

	अचिन्हित दीर्घ		base;
	व्योम __iomem		*mmio_base;

	/* mbox64 with mbox not aligned on 16-byte boundary */
	mbox64_t	*una_mbox64;
	dma_addr_t	una_mbox64_dma;

	अस्थिर mbox64_t	*mbox64;/* ptr to 64-bit mailbox */
	अस्थिर mbox_t		*mbox;	/* ptr to standard mailbox */
	dma_addr_t		mbox_dma;

	काष्ठा pci_dev	*dev;

	काष्ठा list_head	मुक्त_list;
	काष्ठा list_head	pending_list;
	काष्ठा list_head	completed_list;

	काष्ठा Scsi_Host	*host;

#घोषणा MEGA_BUFFER_SIZE (2*1024)
	u8		*mega_buffer;
	dma_addr_t	buf_dma_handle;

	mega_product_info	product_info;

	u8		max_cmds;
	scb_t		*scb_list;

	atomic_t	pend_cmds;	/* मुख्यtain a counter क्रम pending
					   commands in firmware */

#अगर MEGA_HAVE_STATS
	u32	nपढ़ोs[MAX_LOGICAL_DRIVES_40LD];
	u32	nपढ़ोblocks[MAX_LOGICAL_DRIVES_40LD];
	u32	nग_लिखोs[MAX_LOGICAL_DRIVES_40LD];
	u32	nग_लिखोblocks[MAX_LOGICAL_DRIVES_40LD];
	u32	rd_errors[MAX_LOGICAL_DRIVES_40LD];
	u32	wr_errors[MAX_LOGICAL_DRIVES_40LD];
#पूर्ण_अगर

	/* Host adapter parameters */
	u8	numldrv;
	u8	fw_version[7];
	u8	bios_version[7];

#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry	*controller_proc_dir_entry;
#पूर्ण_अगर

	पूर्णांक	has_64bit_addr;		/* are we using 64-bit addressing */
	पूर्णांक	support_ext_cdb;
	पूर्णांक	boot_ldrv_enabled;
	पूर्णांक	boot_ldrv;
	पूर्णांक	boot_pdrv_enabled;	/* boot from physical drive */
	पूर्णांक	boot_pdrv_ch;		/* boot physical drive channel */
	पूर्णांक	boot_pdrv_tgt;		/* boot physical drive target */


	पूर्णांक	support_अक्रमom_del;	/* Do we support अक्रमom deletion of
					   logdrvs */
	पूर्णांक	पढ़ो_ldidmap;	/* set after logical drive deltion. The
				   logical drive number must be पढ़ो from the
				   map */
	atomic_t	quiescent;	/* a stage reached when delete logical
					   drive needs to be करोne. Stop
					   sending requests to the hba till
					   delete operation is completed */
	spinlock_t	lock;

	u8	logdrv_chan[MAX_CHANNELS+NVIRT_CHAN]; /* logical drive are on
							what channels. */
	पूर्णांक	mega_ch_class;

	u8	sglen;	/* f/w supported scatter-gather list length */

	scb_t			पूर्णांक_scb;
	काष्ठा mutex		पूर्णांक_mtx;	/* To synchronize the पूर्णांकernal
						commands */
	पूर्णांक			पूर्णांक_status;	/* status of पूर्णांकernal cmd */
	काष्ठा completion	पूर्णांक_रुकोq;	/* रुको queue क्रम पूर्णांकernal
						 cmds */

	पूर्णांक	has_cluster;	/* cluster support on this HBA */
पूर्णadapter_t;


काष्ठा mega_hbas अणु
	पूर्णांक is_bios_enabled;
	adapter_t *hostdata_addr;
पूर्ण;


/*
 * For state flag. Do not use LSB(8 bits) which are
 * reserved क्रम storing info about channels.
 */
#घोषणा IN_ABORT	0x80000000L
#घोषणा IN_RESET	0x40000000L
#घोषणा BOARD_MEMMAP	0x20000000L
#घोषणा BOARD_IOMAP	0x10000000L
#घोषणा BOARD_40LD   	0x08000000L
#घोषणा BOARD_64BIT	0x04000000L

#घोषणा INTR_VALID			0x40

#घोषणा PCI_CONF_AMISIG			0xa0
#घोषणा PCI_CONF_AMISIG64		0xa4


#घोषणा MEGA_DMA_TYPE_NONE		0xFFFF
#घोषणा MEGA_BULK_DATA			0x0001
#घोषणा MEGA_SGLIST			0x0002

/*
 * Parameters क्रम the io-mapped controllers
 */

/* I/O Port offsets */
#घोषणा CMD_PORT	 	0x00
#घोषणा ACK_PORT	 	0x00
#घोषणा TOGGLE_PORT		0x01
#घोषणा INTR_PORT	  	0x0a

#घोषणा MBOX_BUSY_PORT     	0x00
#घोषणा MBOX_PORT0	 	0x04
#घोषणा MBOX_PORT1	 	0x05
#घोषणा MBOX_PORT2	 	0x06
#घोषणा MBOX_PORT3	 	0x07
#घोषणा ENABLE_MBOX_REGION 	0x0B

/* I/O Port Values */
#घोषणा ISSUE_BYTE	 	0x10
#घोषणा ACK_BYTE	   	0x08
#घोषणा ENABLE_INTR_BYTE   	0xc0
#घोषणा DISABLE_INTR_BYTE  	0x00
#घोषणा VALID_INTR_BYTE    	0x40
#घोषणा MBOX_BUSY_BYTE     	0x10
#घोषणा ENABLE_MBOX_BYTE   	0x00


/* Setup some port macros here */
#घोषणा issue_command(adapter)	\
		outb_p(ISSUE_BYTE, (adapter)->base + CMD_PORT)

#घोषणा irq_state(adapter)	inb_p((adapter)->base + INTR_PORT)

#घोषणा set_irq_state(adapter, value)	\
		outb_p((value), (adapter)->base + INTR_PORT)

#घोषणा irq_ack(adapter)	\
		outb_p(ACK_BYTE, (adapter)->base + ACK_PORT)

#घोषणा irq_enable(adapter)	\
	outb_p(ENABLE_INTR_BYTE, (adapter)->base + TOGGLE_PORT)

#घोषणा irq_disable(adapter)	\
	outb_p(DISABLE_INTR_BYTE, (adapter)->base + TOGGLE_PORT)


/*
 * This is our SYSDEP area. All kernel specअगरic detail should be placed here -
 * as much as possible
 */

/*
 * End of SYSDEP area
 */

स्थिर अक्षर *megaraid_info (काष्ठा Scsi_Host *);

अटल पूर्णांक mega_query_adapter(adapter_t *);
अटल पूर्णांक issue_scb(adapter_t *, scb_t *);
अटल पूर्णांक mega_setup_mailbox(adapter_t *);

अटल पूर्णांक megaraid_queue (काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
अटल scb_t * mega_build_cmd(adapter_t *, काष्ठा scsi_cmnd *, पूर्णांक *);
अटल व्योम __mega_runpendq(adapter_t *);
अटल पूर्णांक issue_scb_block(adapter_t *, u_अक्षर *);

अटल irqवापस_t megaraid_isr_memmapped(पूर्णांक, व्योम *);
अटल irqवापस_t megaraid_isr_iomapped(पूर्णांक, व्योम *);

अटल व्योम mega_मुक्त_scb(adapter_t *, scb_t *);

अटल पूर्णांक megaraid_पात(काष्ठा scsi_cmnd *);
अटल पूर्णांक megaraid_reset(काष्ठा scsi_cmnd *);
अटल पूर्णांक megaraid_पात_and_reset(adapter_t *, काष्ठा scsi_cmnd *, पूर्णांक);
अटल पूर्णांक megaraid_biosparam(काष्ठा scsi_device *, काष्ठा block_device *,
		sector_t, पूर्णांक []);

अटल पूर्णांक mega_build_sglist (adapter_t *adapter, scb_t *scb,
			      u32 *buffer, u32 *length);
अटल पूर्णांक __mega_busyरुको_mbox (adapter_t *);
अटल व्योम mega_runकरोneq (adapter_t *);
अटल व्योम mega_cmd_करोne(adapter_t *, u8 [], पूर्णांक, पूर्णांक);
अटल अंतरभूत व्योम mega_मुक्त_sgl (adapter_t *adapter);
अटल व्योम mega_8_to_40ld (mraid_inquiry *inquiry,
		mega_inquiry3 *enquiry3, mega_product_info *);

अटल पूर्णांक megadev_खोलो (काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक megadev_ioctl (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक mega_m_to_n(व्योम __user *, nitioctl_t *);
अटल पूर्णांक mega_n_to_m(व्योम __user *, megacmd_t *);

अटल पूर्णांक mega_init_scb (adapter_t *);

अटल पूर्णांक mega_is_bios_enabled (adapter_t *);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम mega_create_proc_entry(पूर्णांक, काष्ठा proc_dir_entry *);
अटल पूर्णांक mega_adapinq(adapter_t *, dma_addr_t);
अटल पूर्णांक mega_पूर्णांकernal_dev_inquiry(adapter_t *, u8, u8, dma_addr_t);
#पूर्ण_अगर

अटल पूर्णांक mega_support_ext_cdb(adapter_t *);
अटल mega_passthru* mega_prepare_passthru(adapter_t *, scb_t *,
		काष्ठा scsi_cmnd *, पूर्णांक, पूर्णांक);
अटल mega_ext_passthru* mega_prepare_extpassthru(adapter_t *,
		scb_t *, काष्ठा scsi_cmnd *, पूर्णांक, पूर्णांक);
अटल व्योम mega_क्रमागत_raid_scsi(adapter_t *);
अटल व्योम mega_get_boot_drv(adapter_t *);
अटल पूर्णांक mega_support_अक्रमom_del(adapter_t *);
अटल पूर्णांक mega_del_logdrv(adapter_t *, पूर्णांक);
अटल पूर्णांक mega_करो_del_logdrv(adapter_t *, पूर्णांक);
अटल व्योम mega_get_max_sgl(adapter_t *);
अटल पूर्णांक mega_पूर्णांकernal_command(adapter_t *, megacmd_t *, mega_passthru *);
अटल पूर्णांक mega_support_cluster(adapter_t *);
#पूर्ण_अगर

/* vi: set ts=8 sw=8 tw=78: */
