<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_HDREG_H
#घोषणा _LINUX_HDREG_H

#समावेश <linux/types.h>

/*
 * Command Header sizes क्रम IOCTL commands
 */

#घोषणा HDIO_DRIVE_CMD_HDR_SIZE		(4 * माप(__u8))
#घोषणा HDIO_DRIVE_HOB_HDR_SIZE		(8 * माप(__u8))
#घोषणा HDIO_DRIVE_TASK_HDR_SIZE	(8 * माप(__u8))

#घोषणा IDE_DRIVE_TASK_NO_DATA		0
#अगर_अघोषित __KERNEL__
#घोषणा IDE_DRIVE_TASK_INVALID		-1
#घोषणा IDE_DRIVE_TASK_SET_XFER		1
#घोषणा IDE_DRIVE_TASK_IN		2
#घोषणा IDE_DRIVE_TASK_OUT		3
#पूर्ण_अगर
#घोषणा IDE_DRIVE_TASK_RAW_WRITE	4

/*
 * Define standard taskfile in/out रेजिस्टर
 */
#घोषणा IDE_TASKखाता_STD_IN_FLAGS	0xFE
#घोषणा IDE_HOB_STD_IN_FLAGS		0x3C
#अगर_अघोषित __KERNEL__
#घोषणा IDE_TASKखाता_STD_OUT_FLAGS	0xFE
#घोषणा IDE_HOB_STD_OUT_FLAGS		0x3C

प्रकार अचिन्हित अक्षर task_ioreg_t;
प्रकार अचिन्हित दीर्घ sata_ioreg_t;
#पूर्ण_अगर

प्रकार जोड़ ide_reg_valid_s अणु
	अचिन्हित all				: 16;
	काष्ठा अणु
		अचिन्हित data			: 1;
		अचिन्हित error_feature		: 1;
		अचिन्हित sector			: 1;
		अचिन्हित nsector		: 1;
		अचिन्हित lcyl			: 1;
		अचिन्हित hcyl			: 1;
		अचिन्हित select			: 1;
		अचिन्हित status_command		: 1;

		अचिन्हित data_hob		: 1;
		अचिन्हित error_feature_hob	: 1;
		अचिन्हित sector_hob		: 1;
		अचिन्हित nsector_hob		: 1;
		अचिन्हित lcyl_hob		: 1;
		अचिन्हित hcyl_hob		: 1;
		अचिन्हित select_hob		: 1;
		अचिन्हित control_hob		: 1;
	पूर्ण b;
पूर्ण ide_reg_valid_t;

प्रकार काष्ठा ide_task_request_s अणु
	__u8		io_ports[8];
	__u8		hob_ports[8]; /* bytes 6 and 7 are unused */
	ide_reg_valid_t	out_flags;
	ide_reg_valid_t	in_flags;
	पूर्णांक		data_phase;
	पूर्णांक		req_cmd;
	अचिन्हित दीर्घ	out_size;
	अचिन्हित दीर्घ	in_size;
पूर्ण ide_task_request_t;

प्रकार काष्ठा ide_ioctl_request_s अणु
	ide_task_request_t	*task_request;
	अचिन्हित अक्षर		*out_buffer;
	अचिन्हित अक्षर		*in_buffer;
पूर्ण ide_ioctl_request_t;

काष्ठा hd_drive_cmd_hdr अणु
	__u8 command;
	__u8 sector_number;
	__u8 feature;
	__u8 sector_count;
पूर्ण;

#अगर_अघोषित __KERNEL__
प्रकार काष्ठा hd_drive_task_hdr अणु
	__u8 data;
	__u8 feature;
	__u8 sector_count;
	__u8 sector_number;
	__u8 low_cylinder;
	__u8 high_cylinder;
	__u8 device_head;
	__u8 command;
पूर्ण task_काष्ठा_t;

प्रकार काष्ठा hd_drive_hob_hdr अणु
	__u8 data;
	__u8 feature;
	__u8 sector_count;
	__u8 sector_number;
	__u8 low_cylinder;
	__u8 high_cylinder;
	__u8 device_head;
	__u8 control;
पूर्ण hob_काष्ठा_t;
#पूर्ण_अगर

#घोषणा TASKखाता_NO_DATA		0x0000

#घोषणा TASKखाता_IN			0x0001
#घोषणा TASKखाता_MULTI_IN		0x0002

#घोषणा TASKखाता_OUT			0x0004
#घोषणा TASKखाता_MULTI_OUT		0x0008
#घोषणा TASKखाता_IN_OUT			0x0010

#घोषणा TASKखाता_IN_DMA			0x0020
#घोषणा TASKखाता_OUT_DMA		0x0040
#घोषणा TASKखाता_IN_DMAQ		0x0080
#घोषणा TASKखाता_OUT_DMAQ		0x0100

#अगर_अघोषित __KERNEL__
#घोषणा TASKखाता_P_IN			0x0200
#घोषणा TASKखाता_P_OUT			0x0400
#घोषणा TASKखाता_P_IN_DMA		0x0800
#घोषणा TASKखाता_P_OUT_DMA		0x1000
#घोषणा TASKखाता_P_IN_DMAQ		0x2000
#घोषणा TASKखाता_P_OUT_DMAQ		0x4000
#घोषणा TASKखाता_48			0x8000
#घोषणा TASKखाता_INVALID		0x7fff
#पूर्ण_अगर

#अगर_अघोषित __KERNEL__
/* ATA/ATAPI Commands pre T13 Spec */
#घोषणा WIN_NOP				0x00
/*
 *	0x01->0x02 Reserved
 */
#घोषणा CFA_REQ_EXT_ERROR_CODE		0x03 /* CFA Request Extended Error Code */
/*
 *	0x04->0x07 Reserved
 */
#घोषणा WIN_SRST			0x08 /* ATAPI soft reset command */
#घोषणा WIN_DEVICE_RESET		0x08
/*
 *	0x09->0x0F Reserved
 */
#घोषणा WIN_RECAL			0x10
#घोषणा WIN_RESTORE			WIN_RECAL
/*
 *	0x10->0x1F Reserved
 */
#घोषणा WIN_READ			0x20 /* 28-Bit */
#घोषणा WIN_READ_ONCE			0x21 /* 28-Bit without retries */
#घोषणा WIN_READ_LONG			0x22 /* 28-Bit */
#घोषणा WIN_READ_LONG_ONCE		0x23 /* 28-Bit without retries */
#घोषणा WIN_READ_EXT			0x24 /* 48-Bit */
#घोषणा WIN_READDMA_EXT			0x25 /* 48-Bit */
#घोषणा WIN_READDMA_QUEUED_EXT		0x26 /* 48-Bit */
#घोषणा WIN_READ_NATIVE_MAX_EXT		0x27 /* 48-Bit */
/*
 *	0x28
 */
#घोषणा WIN_MULTREAD_EXT		0x29 /* 48-Bit */
/*
 *	0x2A->0x2F Reserved
 */
#घोषणा WIN_WRITE			0x30 /* 28-Bit */
#घोषणा WIN_WRITE_ONCE			0x31 /* 28-Bit without retries */
#घोषणा WIN_WRITE_LONG			0x32 /* 28-Bit */
#घोषणा WIN_WRITE_LONG_ONCE		0x33 /* 28-Bit without retries */
#घोषणा WIN_WRITE_EXT			0x34 /* 48-Bit */
#घोषणा WIN_WRITEDMA_EXT		0x35 /* 48-Bit */
#घोषणा WIN_WRITEDMA_QUEUED_EXT		0x36 /* 48-Bit */
#घोषणा WIN_SET_MAX_EXT			0x37 /* 48-Bit */
#घोषणा CFA_WRITE_SECT_WO_ERASE		0x38 /* CFA Write Sectors without erase */
#घोषणा WIN_MULTWRITE_EXT		0x39 /* 48-Bit */
/*
 *	0x3A->0x3B Reserved
 */
#घोषणा WIN_WRITE_VERIFY		0x3C /* 28-Bit */
/*
 *	0x3D->0x3F Reserved
 */
#घोषणा WIN_VERIFY			0x40 /* 28-Bit - Read Verअगरy Sectors */
#घोषणा WIN_VERIFY_ONCE			0x41 /* 28-Bit - without retries */
#घोषणा WIN_VERIFY_EXT			0x42 /* 48-Bit */
/*
 *	0x43->0x4F Reserved
 */
#घोषणा WIN_FORMAT			0x50
/*
 *	0x51->0x5F Reserved
 */
#घोषणा WIN_INIT			0x60
/*
 *	0x61->0x5F Reserved
 */
#घोषणा WIN_SEEK			0x70 /* 0x70-0x7F Reserved */

#घोषणा CFA_TRANSLATE_SECTOR		0x87 /* CFA Translate Sector */
#घोषणा WIN_DIAGNOSE			0x90
#घोषणा WIN_SPECIFY			0x91 /* set drive geometry translation */
#घोषणा WIN_DOWNLOAD_MICROCODE		0x92
#घोषणा WIN_STANDBYNOW2			0x94
#घोषणा WIN_STANDBY2			0x96
#घोषणा WIN_SETIDLE2			0x97
#घोषणा WIN_CHECKPOWERMODE2		0x98
#घोषणा WIN_SLEEPNOW2			0x99
/*
 *	0x9A VENDOR
 */
#घोषणा WIN_PACKETCMD			0xA0 /* Send a packet command. */
#घोषणा WIN_PIDENTIFY			0xA1 /* identअगरy ATAPI device	*/
#घोषणा WIN_QUEUED_SERVICE		0xA2
#घोषणा WIN_SMART			0xB0 /* self-monitoring and reporting */
#घोषणा CFA_ERASE_SECTORS		0xC0
#घोषणा WIN_MULTREAD			0xC4 /* पढ़ो sectors using multiple mode*/
#घोषणा WIN_MULTWRITE			0xC5 /* ग_लिखो sectors using multiple mode */
#घोषणा WIN_SETMULT			0xC6 /* enable/disable multiple mode */
#घोषणा WIN_READDMA_QUEUED		0xC7 /* पढ़ो sectors using Queued DMA transfers */
#घोषणा WIN_READDMA			0xC8 /* पढ़ो sectors using DMA transfers */
#घोषणा WIN_READDMA_ONCE		0xC9 /* 28-Bit - without retries */
#घोषणा WIN_WRITEDMA			0xCA /* ग_लिखो sectors using DMA transfers */
#घोषणा WIN_WRITEDMA_ONCE		0xCB /* 28-Bit - without retries */
#घोषणा WIN_WRITEDMA_QUEUED		0xCC /* ग_लिखो sectors using Queued DMA transfers */
#घोषणा CFA_WRITE_MULTI_WO_ERASE	0xCD /* CFA Write multiple without erase */
#घोषणा WIN_GETMEDIASTATUS		0xDA
#घोषणा WIN_ACKMEDIACHANGE		0xDB /* ATA-1, ATA-2 venकरोr */
#घोषणा WIN_POSTBOOT			0xDC
#घोषणा WIN_PREBOOT 			0xDD
#घोषणा WIN_DOORLOCK			0xDE /* lock करोor on removable drives */
#घोषणा WIN_DOORUNLOCK			0xDF /* unlock करोor on removable drives */
#घोषणा WIN_STANDBYNOW1			0xE0
#घोषणा WIN_IDLEIMMEDIATE		0xE1 /* क्रमce drive to become "ready" */
#घोषणा WIN_STANDBY			0xE2 /* Set device in Standby Mode */
#घोषणा WIN_SETIDLE1			0xE3
#घोषणा WIN_READ_BUFFER			0xE4 /* क्रमce पढ़ो only 1 sector */
#घोषणा WIN_CHECKPOWERMODE1		0xE5
#घोषणा WIN_SLEEPNOW1			0xE6
#घोषणा WIN_FLUSH_CACHE			0xE7
#घोषणा WIN_WRITE_BUFFER		0xE8 /* क्रमce ग_लिखो only 1 sector */
#घोषणा WIN_WRITE_SAME			0xE9 /* पढ़ो ata-2 to use */
	/* SET_FEATURES 0x22 or 0xDD */
#घोषणा WIN_FLUSH_CACHE_EXT		0xEA /* 48-Bit */
#घोषणा WIN_IDENTIFY			0xEC /* ask drive to identअगरy itself	*/
#घोषणा WIN_MEDIAEJECT			0xED
#घोषणा WIN_IDENTIFY_DMA		0xEE /* same as WIN_IDENTIFY, but DMA */
#घोषणा WIN_SETFEATURES			0xEF /* set special drive features */
#घोषणा EXABYTE_ENABLE_NEST		0xF0
#घोषणा WIN_SECURITY_SET_PASS		0xF1
#घोषणा WIN_SECURITY_UNLOCK		0xF2
#घोषणा WIN_SECURITY_ERASE_PREPARE	0xF3
#घोषणा WIN_SECURITY_ERASE_UNIT		0xF4
#घोषणा WIN_SECURITY_FREEZE_LOCK	0xF5
#घोषणा WIN_SECURITY_DISABLE		0xF6
#घोषणा WIN_READ_NATIVE_MAX		0xF8 /* वापस the native maximum address */
#घोषणा WIN_SET_MAX			0xF9
#घोषणा DISABLE_SEAGATE			0xFB

/* WIN_SMART sub-commands */

#घोषणा SMART_READ_VALUES		0xD0
#घोषणा SMART_READ_THRESHOLDS		0xD1
#घोषणा SMART_AUTOSAVE			0xD2
#घोषणा SMART_SAVE			0xD3
#घोषणा SMART_IMMEDIATE_OFFLINE		0xD4
#घोषणा SMART_READ_LOG_SECTOR		0xD5
#घोषणा SMART_WRITE_LOG_SECTOR		0xD6
#घोषणा SMART_WRITE_THRESHOLDS		0xD7
#घोषणा SMART_ENABLE			0xD8
#घोषणा SMART_DISABLE			0xD9
#घोषणा SMART_STATUS			0xDA
#घोषणा SMART_AUTO_OFFLINE		0xDB

/* Password used in TF4 & TF5 executing SMART commands */

#घोषणा SMART_LCYL_PASS			0x4F
#घोषणा SMART_HCYL_PASS			0xC2

/* WIN_SETFEATURES sub-commands */
#घोषणा SETFEATURES_EN_8BIT	0x01	/* Enable 8-Bit Transfers */
#घोषणा SETFEATURES_EN_WCACHE	0x02	/* Enable ग_लिखो cache */
#घोषणा SETFEATURES_DIS_DEFECT	0x04	/* Disable Defect Management */
#घोषणा SETFEATURES_EN_APM	0x05	/* Enable advanced घातer management */
#घोषणा SETFEATURES_EN_SAME_R	0x22	/* क्रम a region ATA-1 */
#घोषणा SETFEATURES_DIS_MSN	0x31	/* Disable Media Status Notअगरication */
#घोषणा SETFEATURES_DIS_RETRY	0x33	/* Disable Retry */
#घोषणा SETFEATURES_EN_AAM	0x42	/* Enable Automatic Acoustic Management */
#घोषणा SETFEATURES_RW_LONG	0x44	/* Set Length of VS bytes */
#घोषणा SETFEATURES_SET_CACHE	0x54	/* Set Cache segments to SC Reg. Val */
#घोषणा SETFEATURES_DIS_RLA	0x55	/* Disable पढ़ो look-ahead feature */
#घोषणा SETFEATURES_EN_RI	0x5D	/* Enable release पूर्णांकerrupt */
#घोषणा SETFEATURES_EN_SI	0x5E	/* Enable SERVICE पूर्णांकerrupt */
#घोषणा SETFEATURES_DIS_RPOD	0x66	/* Disable reverting to घातer on शेषs */
#घोषणा SETFEATURES_DIS_ECC	0x77	/* Disable ECC byte count */
#घोषणा SETFEATURES_DIS_8BIT	0x81	/* Disable 8-Bit Transfers */
#घोषणा SETFEATURES_DIS_WCACHE	0x82	/* Disable ग_लिखो cache */
#घोषणा SETFEATURES_EN_DEFECT	0x84	/* Enable Defect Management */
#घोषणा SETFEATURES_DIS_APM	0x85	/* Disable advanced घातer management */
#घोषणा SETFEATURES_EN_ECC	0x88	/* Enable ECC byte count */
#घोषणा SETFEATURES_EN_MSN	0x95	/* Enable Media Status Notअगरication */
#घोषणा SETFEATURES_EN_RETRY	0x99	/* Enable Retry */
#घोषणा SETFEATURES_EN_RLA	0xAA	/* Enable पढ़ो look-ahead feature */
#घोषणा SETFEATURES_PREFETCH	0xAB	/* Sets drive prefetch value */
#घोषणा SETFEATURES_EN_REST	0xAC	/* ATA-1 */
#घोषणा SETFEATURES_4B_RW_LONG	0xBB	/* Set Length of 4 bytes */
#घोषणा SETFEATURES_DIS_AAM	0xC2	/* Disable Automatic Acoustic Management */
#घोषणा SETFEATURES_EN_RPOD	0xCC	/* Enable reverting to घातer on शेषs */
#घोषणा SETFEATURES_DIS_RI	0xDD	/* Disable release पूर्णांकerrupt ATAPI */
#घोषणा SETFEATURES_EN_SAME_M	0xDD	/* क्रम a entire device ATA-1 */
#घोषणा SETFEATURES_DIS_SI	0xDE	/* Disable SERVICE पूर्णांकerrupt ATAPI */

/* WIN_SECURITY sub-commands */

#घोषणा SECURITY_SET_PASSWORD		0xBA
#घोषणा SECURITY_UNLOCK			0xBB
#घोषणा SECURITY_ERASE_PREPARE		0xBC
#घोषणा SECURITY_ERASE_UNIT		0xBD
#घोषणा SECURITY_FREEZE_LOCK		0xBE
#घोषणा SECURITY_DISABLE_PASSWORD	0xBF
#पूर्ण_अगर /* __KERNEL__ */

काष्ठा hd_geometry अणु
      अचिन्हित अक्षर heads;
      अचिन्हित अक्षर sectors;
      अचिन्हित लघु cylinders;
      अचिन्हित दीर्घ start;
पूर्ण;

/* hd/ide ctl's that pass (arg) ptrs to user space are numbered 0x030n/0x031n */
#घोषणा HDIO_GETGEO		0x0301	/* get device geometry */
#घोषणा HDIO_GET_UNMASKINTR	0x0302	/* get current unmask setting */
#घोषणा HDIO_GET_MULTCOUNT	0x0304	/* get current IDE blockmode setting */
#घोषणा HDIO_GET_QDMA		0x0305	/* get use-qdma flag */

#घोषणा HDIO_SET_XFER		0x0306  /* set transfer rate via proc */

#घोषणा HDIO_OBSOLETE_IDENTITY	0x0307	/* OBSOLETE, DO NOT USE: वापसs 142 bytes */
#घोषणा HDIO_GET_KEEPSETTINGS	0x0308	/* get keep-settings-on-reset flag */
#घोषणा HDIO_GET_32BIT		0x0309	/* get current io_32bit setting */
#घोषणा HDIO_GET_NOWERR		0x030a	/* get ignore-ग_लिखो-error flag */
#घोषणा HDIO_GET_DMA		0x030b	/* get use-dma flag */
#घोषणा HDIO_GET_NICE		0x030c	/* get nice flags */
#घोषणा HDIO_GET_IDENTITY	0x030d	/* get IDE identअगरication info */
#घोषणा HDIO_GET_WCACHE		0x030e	/* get ग_लिखो cache mode on|off */
#घोषणा HDIO_GET_ACOUSTIC	0x030f	/* get acoustic value */
#घोषणा	HDIO_GET_ADDRESS	0x0310	/* */

#घोषणा HDIO_GET_BUSSTATE	0x031a	/* get the bus state of the hwअगर */
#घोषणा HDIO_TRISTATE_HWIF	0x031b	/* execute a channel tristate */
#घोषणा HDIO_DRIVE_RESET	0x031c	/* execute a device reset */
#घोषणा HDIO_DRIVE_TASKखाता	0x031d	/* execute raw taskfile */
#घोषणा HDIO_DRIVE_TASK		0x031e	/* execute task and special drive command */
#घोषणा HDIO_DRIVE_CMD		0x031f	/* execute a special drive command */
#घोषणा HDIO_DRIVE_CMD_AEB	HDIO_DRIVE_TASK

/* hd/ide ctl's that pass (arg) non-ptr values are numbered 0x032n/0x033n */
#घोषणा HDIO_SET_MULTCOUNT	0x0321	/* change IDE blockmode */
#घोषणा HDIO_SET_UNMASKINTR	0x0322	/* permit other irqs during I/O */
#घोषणा HDIO_SET_KEEPSETTINGS	0x0323	/* keep ioctl settings on reset */
#घोषणा HDIO_SET_32BIT		0x0324	/* change io_32bit flags */
#घोषणा HDIO_SET_NOWERR		0x0325	/* change ignore-ग_लिखो-error flag */
#घोषणा HDIO_SET_DMA		0x0326	/* change use-dma flag */
#घोषणा HDIO_SET_PIO_MODE	0x0327	/* reconfig पूर्णांकerface to new speed */
#अगर_अघोषित __KERNEL__
#घोषणा HDIO_SCAN_HWIF		0x0328	/* रेजिस्टर and (re)scan पूर्णांकerface */
#घोषणा HDIO_UNREGISTER_HWIF	0x032a  /* unरेजिस्टर पूर्णांकerface */
#पूर्ण_अगर
#घोषणा HDIO_SET_NICE		0x0329	/* set nice flags */
#घोषणा HDIO_SET_WCACHE		0x032b	/* change ग_लिखो cache enable-disable */
#घोषणा HDIO_SET_ACOUSTIC	0x032c	/* change acoustic behavior */
#घोषणा HDIO_SET_BUSSTATE	0x032d	/* set the bus state of the hwअगर */
#घोषणा HDIO_SET_QDMA		0x032e	/* change use-qdma flag */
#घोषणा HDIO_SET_ADDRESS	0x032f	/* change lba addressing modes */

/* bus states */
क्रमागत अणु
	BUSSTATE_OFF = 0,
	BUSSTATE_ON,
	BUSSTATE_TRISTATE
पूर्ण;

/* hd/ide ctl's that pass (arg) ptrs to user space are numbered 0x033n/0x033n */
/* 0x330 is reserved - used to be HDIO_GETGEO_BIG */
/* 0x331 is reserved - used to be HDIO_GETGEO_BIG_RAW */
/* 0x338 is reserved - used to be HDIO_SET_IDE_SCSI */
/* 0x339 is reserved - used to be HDIO_SET_SCSI_IDE */

#घोषणा __NEW_HD_DRIVE_ID

#अगर_अघोषित __KERNEL__
/*
 * Structure वापसed by HDIO_GET_IDENTITY, as per ANSI NCITS ATA6 rev.1b spec.
 *
 * If you change something here, please remember to update fix_driveid() in
 * ide/probe.c.
 */
काष्ठा hd_driveid अणु
	अचिन्हित लघु	config;		/* lots of obsolete bit flags */
	अचिन्हित लघु	cyls;		/* Obsolete, "physical" cyls */
	अचिन्हित लघु	reserved2;	/* reserved (word 2) */
	अचिन्हित लघु	heads;		/* Obsolete, "physical" heads */
	अचिन्हित लघु	track_bytes;	/* unक्रमmatted bytes per track */
	अचिन्हित लघु	sector_bytes;	/* unक्रमmatted bytes per sector */
	अचिन्हित लघु	sectors;	/* Obsolete, "physical" sectors per track */
	अचिन्हित लघु	venकरोr0;	/* venकरोr unique */
	अचिन्हित लघु	venकरोr1;	/* venकरोr unique */
	अचिन्हित लघु	venकरोr2;	/* Retired venकरोr unique */
	अचिन्हित अक्षर	serial_no[20];	/* 0 = not_specअगरied */
	अचिन्हित लघु	buf_type;	/* Retired */
	अचिन्हित लघु	buf_size;	/* Retired, 512 byte increments
					 * 0 = not_specअगरied
					 */
	अचिन्हित लघु	ecc_bytes;	/* क्रम r/w दीर्घ cmds; 0 = not_specअगरied */
	अचिन्हित अक्षर	fw_rev[8];	/* 0 = not_specअगरied */
	अचिन्हित अक्षर	model[40];	/* 0 = not_specअगरied */
	अचिन्हित अक्षर	max_multsect;	/* 0=not_implemented */
	अचिन्हित अक्षर	venकरोr3;	/* venकरोr unique */
	अचिन्हित लघु	dword_io;	/* 0=not_implemented; 1=implemented */
	अचिन्हित अक्षर	venकरोr4;	/* venकरोr unique */
	अचिन्हित अक्षर	capability;	/* (upper byte of word 49)
					 *  3:	IORDYsup
					 *  2:	IORDYsw
					 *  1:	LBA
					 *  0:	DMA
					 */
	अचिन्हित लघु	reserved50;	/* reserved (word 50) */
	अचिन्हित अक्षर	venकरोr5;	/* Obsolete, venकरोr unique */
	अचिन्हित अक्षर	tPIO;		/* Obsolete, 0=slow, 1=medium, 2=fast */
	अचिन्हित अक्षर	venकरोr6;	/* Obsolete, venकरोr unique */
	अचिन्हित अक्षर	tDMA;		/* Obsolete, 0=slow, 1=medium, 2=fast */
	अचिन्हित लघु	field_valid;	/* (word 53)
					 *  2:	ultra_ok	word  88
					 *  1:	eide_ok		words 64-70
					 *  0:	cur_ok		words 54-58
					 */
	अचिन्हित लघु	cur_cyls;	/* Obsolete, logical cylinders */
	अचिन्हित लघु	cur_heads;	/* Obsolete, l heads */
	अचिन्हित लघु	cur_sectors;	/* Obsolete, l sectors per track */
	अचिन्हित लघु	cur_capacity0;	/* Obsolete, l total sectors on drive */
	अचिन्हित लघु	cur_capacity1;	/* Obsolete, (2 words, misaligned पूर्णांक)     */
	अचिन्हित अक्षर	multsect;	/* current multiple sector count */
	अचिन्हित अक्षर	multsect_valid;	/* when (bit0==1) multsect is ok */
	अचिन्हित पूर्णांक	lba_capacity;	/* Obsolete, total number of sectors */
	अचिन्हित लघु	dma_1word;	/* Obsolete, single-word dma info */
	अचिन्हित लघु	dma_mword;	/* multiple-word dma info */
	अचिन्हित लघु  eide_pio_modes; /* bits 0:mode3 1:mode4 */
	अचिन्हित लघु  eide_dma_min;	/* min mword dma cycle समय (ns) */
	अचिन्हित लघु  eide_dma_समय;	/* recommended mword dma cycle समय (ns) */
	अचिन्हित लघु  eide_pio;       /* min cycle समय (ns), no IORDY  */
	अचिन्हित लघु  eide_pio_iordy; /* min cycle समय (ns), with IORDY */
	अचिन्हित लघु	words69_70[2];	/* reserved words 69-70
					 * future command overlap and queuing
					 */
	अचिन्हित लघु	words71_74[4];	/* reserved words 71-74
					 * क्रम IDENTIFY PACKET DEVICE command
					 */
	अचिन्हित लघु  queue_depth;	/* (word 75)
					 * 15:5	reserved
					 *  4:0	Maximum queue depth -1
					 */
	अचिन्हित लघु  words76_79[4];	/* reserved words 76-79 */
	अचिन्हित लघु  major_rev_num;	/* (word 80) */
	अचिन्हित लघु  minor_rev_num;	/* (word 81) */
	अचिन्हित लघु  command_set_1;	/* (word 82) supported
					 * 15:	Obsolete
					 * 14:	NOP command
					 * 13:	READ_BUFFER
					 * 12:	WRITE_BUFFER
					 * 11:	Obsolete
					 * 10:	Host Protected Area
					 *  9:	DEVICE Reset
					 *  8:	SERVICE Interrupt
					 *  7:	Release Interrupt
					 *  6:	look-ahead
					 *  5:	ग_लिखो cache
					 *  4:	PACKET Command
					 *  3:	Power Management Feature Set
					 *  2:	Removable Feature Set
					 *  1:	Security Feature Set
					 *  0:	SMART Feature Set
					 */
	अचिन्हित लघु  command_set_2;	/* (word 83)
					 * 15:	Shall be ZERO
					 * 14:	Shall be ONE
					 * 13:	FLUSH CACHE EXT
					 * 12:	FLUSH CACHE
					 * 11:	Device Configuration Overlay
					 * 10:	48-bit Address Feature Set
					 *  9:	Automatic Acoustic Management
					 *  8:	SET MAX security
					 *  7:	reserved 1407DT PARTIES
					 *  6:	SetF sub-command Power-Up
					 *  5:	Power-Up in Standby Feature Set
					 *  4:	Removable Media Notअगरication
					 *  3:	APM Feature Set
					 *  2:	CFA Feature Set
					 *  1:	READ/WRITE DMA QUEUED
					 *  0:	Download MicroCode
					 */
	अचिन्हित लघु  cfsse;		/* (word 84)
					 * cmd set-feature supported extensions
					 * 15:	Shall be ZERO
					 * 14:	Shall be ONE
					 * 13:6	reserved
					 *  5:	General Purpose Logging
					 *  4:	Streaming Feature Set
					 *  3:	Media Card Pass Through
					 *  2:	Media Serial Number Valid
					 *  1:	SMART selt-test supported
					 *  0:	SMART error logging
					 */
	अचिन्हित लघु  cfs_enable_1;	/* (word 85)
					 * command set-feature enabled
					 * 15:	Obsolete
					 * 14:	NOP command
					 * 13:	READ_BUFFER
					 * 12:	WRITE_BUFFER
					 * 11:	Obsolete
					 * 10:	Host Protected Area
					 *  9:	DEVICE Reset
					 *  8:	SERVICE Interrupt
					 *  7:	Release Interrupt
					 *  6:	look-ahead
					 *  5:	ग_लिखो cache
					 *  4:	PACKET Command
					 *  3:	Power Management Feature Set
					 *  2:	Removable Feature Set
					 *  1:	Security Feature Set
					 *  0:	SMART Feature Set
					 */
	अचिन्हित लघु  cfs_enable_2;	/* (word 86)
					 * command set-feature enabled
					 * 15:	Shall be ZERO
					 * 14:	Shall be ONE
					 * 13:	FLUSH CACHE EXT
					 * 12:	FLUSH CACHE
					 * 11:	Device Configuration Overlay
					 * 10:	48-bit Address Feature Set
					 *  9:	Automatic Acoustic Management
					 *  8:	SET MAX security
					 *  7:	reserved 1407DT PARTIES
					 *  6:	SetF sub-command Power-Up
					 *  5:	Power-Up in Standby Feature Set
					 *  4:	Removable Media Notअगरication
					 *  3:	APM Feature Set
					 *  2:	CFA Feature Set
					 *  1:	READ/WRITE DMA QUEUED
					 *  0:	Download MicroCode
					 */
	अचिन्हित लघु  csf_शेष;	/* (word 87)
					 * command set-feature शेष
					 * 15:	Shall be ZERO
					 * 14:	Shall be ONE
					 * 13:6	reserved
					 *  5:	General Purpose Logging enabled
					 *  4:	Valid CONFIGURE STREAM executed
					 *  3:	Media Card Pass Through enabled
					 *  2:	Media Serial Number Valid
					 *  1:	SMART selt-test supported
					 *  0:	SMART error logging
					 */
	अचिन्हित लघु  dma_ultra;	/* (word 88) */
	अचिन्हित लघु	trseuc;		/* समय required क्रम security erase */
	अचिन्हित लघु	trsEuc;		/* समय required क्रम enhanced erase */
	अचिन्हित लघु	CurAPMvalues;	/* current APM values */
	अचिन्हित लघु	mprc;		/* master password revision code */
	अचिन्हित लघु	hw_config;	/* hardware config (word 93)
					 * 15:	Shall be ZERO
					 * 14:	Shall be ONE
					 * 13:
					 * 12:
					 * 11:
					 * 10:
					 *  9:
					 *  8:
					 *  7:
					 *  6:
					 *  5:
					 *  4:
					 *  3:
					 *  2:
					 *  1:
					 *  0:	Shall be ONE
					 */
	अचिन्हित लघु	acoustic;	/* (word 94)
					 * 15:8	Venकरोr's recommended value
					 *  7:0	current value
					 */
	अचिन्हित लघु	msrqs;		/* min stream request size */
	अचिन्हित लघु	sxfert;		/* stream transfer समय */
	अचिन्हित लघु	sal;		/* stream access latency */
	अचिन्हित पूर्णांक	spg;		/* stream perक्रमmance granularity */
	अचिन्हित दीर्घ दीर्घ lba_capacity_2;/* 48-bit total number of sectors */
	अचिन्हित लघु	words104_125[22];/* reserved words 104-125 */
	अचिन्हित लघु	last_lun;	/* (word 126) */
	अचिन्हित लघु	word127;	/* (word 127) Feature Set
					 * Removable Media Notअगरication
					 * 15:2	reserved
					 *  1:0	00 = not supported
					 *	01 = supported
					 *	10 = reserved
					 *	11 = reserved
					 */
	अचिन्हित लघु	dlf;		/* (word 128)
					 * device lock function
					 * 15:9	reserved
					 *  8	security level 1:max 0:high
					 *  7:6	reserved
					 *  5	enhanced erase
					 *  4	expire
					 *  3	frozen
					 *  2	locked
					 *  1	en/disabled
					 *  0	capability
					 */
	अचिन्हित लघु  csfo;		/*  (word 129)
					 * current set features options
					 * 15:4	reserved
					 *  3:	स्वतः reassign
					 *  2:	reverting
					 *  1:	पढ़ो-look-ahead
					 *  0:	ग_लिखो cache
					 */
	अचिन्हित लघु	words130_155[26];/* reserved venकरोr words 130-155 */
	अचिन्हित लघु	word156;	/* reserved venकरोr word 156 */
	अचिन्हित लघु	words157_159[3];/* reserved venकरोr words 157-159 */
	अचिन्हित लघु	cfa_घातer;	/* (word 160) CFA Power Mode
					 * 15 word 160 supported
					 * 14 reserved
					 * 13
					 * 12
					 * 11:0
					 */
	अचिन्हित लघु	words161_175[15];/* Reserved क्रम CFA */
	अचिन्हित लघु	words176_205[30];/* Current Media Serial Number */
	अचिन्हित लघु	words206_254[49];/* reserved words 206-254 */
	अचिन्हित लघु	पूर्णांकegrity_word;	/* (word 255)
					 * 15:8 Checksum
					 *  7:0 Signature
					 */
पूर्ण;
#पूर्ण_अगर /* __KERNEL__ */

/*
 * IDE "nice" flags. These are used on a per drive basis to determine
 * when to be nice and give more bandwidth to the other devices which
 * share the same IDE bus.
 */
#घोषणा IDE_NICE_DSC_OVERLAP	(0)	/* per the DSC overlap protocol */
#घोषणा IDE_NICE_ATAPI_OVERLAP	(1)	/* not supported yet */
#घोषणा IDE_NICE_1		(3)	/* when probably won't affect us much */
#अगर_अघोषित __KERNEL__
#घोषणा IDE_NICE_0		(2)	/* when sure that it won't affect us */
#घोषणा IDE_NICE_2		(4)	/* when we know it's on our expense */
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_HDREG_H */
