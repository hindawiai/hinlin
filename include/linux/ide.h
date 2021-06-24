<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IDE_H
#घोषणा _IDE_H
/*
 *  linux/include/linux/ide.h
 *
 *  Copyright (C) 1994-2002  Linus Torvalds & authors
 */

#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/ata.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/completion.h>
#समावेश <linux/pm.h>
#समावेश <linux/mutex.h>
/* क्रम request_sense */
#समावेश <linux/cdrom.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>

/*
 * Probably not wise to fiddle with these
 */
#घोषणा SUPPORT_VLB_SYNC 1
#घोषणा IDE_DEFAULT_MAX_FAILURES	1
#घोषणा ERROR_MAX	8	/* Max पढ़ो/ग_लिखो errors per sector */
#घोषणा ERROR_RESET	3	/* Reset controller every 4th retry */
#घोषणा ERROR_RECAL	1	/* Recalibrate every 2nd retry */

काष्ठा device;

/* values क्रम ide_request.type */
क्रमागत ata_priv_type अणु
	ATA_PRIV_MISC,
	ATA_PRIV_TASKखाता,
	ATA_PRIV_PC,
	ATA_PRIV_SENSE,		/* sense request */
	ATA_PRIV_PM_SUSPEND,	/* suspend request */
	ATA_PRIV_PM_RESUME,	/* resume request */
पूर्ण;

काष्ठा ide_request अणु
	काष्ठा scsi_request sreq;
	u8 sense[SCSI_SENSE_BUFFERSIZE];
	u8 type;
	व्योम *special;
पूर्ण;

अटल अंतरभूत काष्ठा ide_request *ide_req(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_to_pdu(rq);
पूर्ण

अटल अंतरभूत bool ata_misc_request(काष्ठा request *rq)
अणु
	वापस blk_rq_is_निजी(rq) && ide_req(rq)->type == ATA_PRIV_MISC;
पूर्ण

अटल अंतरभूत bool ata_taskfile_request(काष्ठा request *rq)
अणु
	वापस blk_rq_is_निजी(rq) && ide_req(rq)->type == ATA_PRIV_TASKखाता;
पूर्ण

अटल अंतरभूत bool ata_pc_request(काष्ठा request *rq)
अणु
	वापस blk_rq_is_निजी(rq) && ide_req(rq)->type == ATA_PRIV_PC;
पूर्ण

अटल अंतरभूत bool ata_sense_request(काष्ठा request *rq)
अणु
	वापस blk_rq_is_निजी(rq) && ide_req(rq)->type == ATA_PRIV_SENSE;
पूर्ण

अटल अंतरभूत bool ata_pm_request(काष्ठा request *rq)
अणु
	वापस blk_rq_is_निजी(rq) &&
		(ide_req(rq)->type == ATA_PRIV_PM_SUSPEND ||
		 ide_req(rq)->type == ATA_PRIV_PM_RESUME);
पूर्ण

/* Error codes वापसed in result to the higher part of the driver. */
क्रमागत अणु
	IDE_DRV_ERROR_GENERAL	= 101,
	IDE_DRV_ERROR_खाताMARK	= 102,
	IDE_DRV_ERROR_EOD	= 103,
पूर्ण;

/*
 * Definitions क्रम accessing IDE controller रेजिस्टरs
 */
#घोषणा IDE_NR_PORTS		(10)

काष्ठा ide_io_ports अणु
	अचिन्हित दीर्घ	data_addr;

	जोड़ अणु
		अचिन्हित दीर्घ error_addr;	/*   पढ़ो:  error */
		अचिन्हित दीर्घ feature_addr;	/*  ग_लिखो: feature */
	पूर्ण;

	अचिन्हित दीर्घ	nsect_addr;
	अचिन्हित दीर्घ	lbal_addr;
	अचिन्हित दीर्घ	lbam_addr;
	अचिन्हित दीर्घ	lbah_addr;

	अचिन्हित दीर्घ	device_addr;

	जोड़ अणु
		अचिन्हित दीर्घ status_addr;	/* त पढ़ो: status त */
		अचिन्हित दीर्घ command_addr;	/* ग_लिखो: command */
	पूर्ण;

	अचिन्हित दीर्घ	ctl_addr;

	अचिन्हित दीर्घ	irq_addr;
पूर्ण;

#घोषणा OK_STAT(stat,good,bad)	(((stat)&((good)|(bad)))==(good))

#घोषणा BAD_R_STAT	(ATA_BUSY | ATA_ERR)
#घोषणा BAD_W_STAT	(BAD_R_STAT | ATA_DF)
#घोषणा BAD_STAT	(BAD_R_STAT | ATA_DRQ)
#घोषणा DRIVE_READY	(ATA_DRDY | ATA_DSC)

#घोषणा BAD_CRC		(ATA_ABORTED | ATA_ICRC)

#घोषणा SATA_NR_PORTS		(3)	/* 16 possible ?? */

#घोषणा SATA_STATUS_OFFSET	(0)
#घोषणा SATA_ERROR_OFFSET	(1)
#घोषणा SATA_CONTROL_OFFSET	(2)

/*
 * Our Physical Region Descriptor (PRD) table should be large enough
 * to handle the biggest I/O request we are likely to see.  Since requests
 * can have no more than 256 sectors, and since the typical blocksize is
 * two or more sectors, we could get by with a limit of 128 entries here क्रम
 * the usual worst हाल.  Most requests seem to include some contiguous blocks,
 * further reducing the number of table entries required.
 *
 * The driver reverts to PIO mode क्रम inभागidual requests that exceed
 * this limit (possible with 512 byte blocksizes, eg. MSDOS f/s), so handling
 * 100% of all crazy scenarios here is not necessary.
 *
 * As it turns out though, we must allocate a full 4KB page क्रम this,
 * so the two PRD tables (ide0 & ide1) will each get half of that,
 * allowing each to have about 256 entries (8 bytes each) from this.
 */
#घोषणा PRD_BYTES       8
#घोषणा PRD_ENTRIES	256

/*
 * Some more useful definitions
 */
#घोषणा PARTN_BITS	6	/* number of minor dev bits क्रम partitions */
#घोषणा MAX_DRIVES	2	/* per पूर्णांकerface; 2 assumed by lots of code */

/*
 * Timeouts क्रम various operations:
 */
क्रमागत अणु
	/* spec allows up to 20ms, but CF cards and SSD drives need more */
	WAIT_DRQ	= 1 * HZ,	/* 1s */
	/* some laptops are very slow */
	WAIT_READY	= 5 * HZ,	/* 5s */
	/* should be less than 3ms (?), अगर all ATAPI CD is बंदd at boot */
	WAIT_PIDENTIFY	= 10 * HZ,	/* 10s */
	/* worst हाल when spinning up */
	WAIT_WORSTCASE	= 30 * HZ,	/* 30s */
	/* maximum रुको क्रम an IRQ to happen */
	WAIT_CMD	= 10 * HZ,	/* 10s */
	/* Some drives require a दीर्घer IRQ समयout. */
	WAIT_FLOPPY_CMD	= 50 * HZ,	/* 50s */
	/*
	 * Some drives (क्रम example, Seagate STT3401A Travan) require a very
	 * दीर्घ समयout, because they करोn't वापस an पूर्णांकerrupt or clear their
	 * BSY bit until after the command completes (even retension commands).
	 */
	WAIT_TAPE_CMD	= 900 * HZ,	/* 900s */
	/* minimum sleep समय */
	WAIT_MIN_SLEEP	= HZ / 50,	/* 20ms */
पूर्ण;

/*
 * Op codes क्रम special requests to be handled by ide_special_rq().
 * Values should be in the range of 0x20 to 0x3f.
 */
#घोषणा REQ_DRIVE_RESET		0x20
#घोषणा REQ_DEVSET_EXEC		0x21
#घोषणा REQ_PARK_HEADS		0x22
#घोषणा REQ_UNPARK_HEADS	0x23

/*
 * hwअगर_chipset_t is used to keep track of the specअगरic hardware
 * chipset used by each IDE पूर्णांकerface, अगर known.
 */
क्रमागत अणु		ide_unknown,	ide_generic,	ide_pci,
		ide_cmd640,	ide_dtc2278,	ide_ali14xx,
		ide_qd65xx,	ide_umc8672,	ide_ht6560b,
		ide_4drives,	ide_pmac,	ide_acorn,
		ide_au1xxx,	ide_palm3710
पूर्ण;

प्रकार u8 hwअगर_chipset_t;

/*
 * Structure to hold all inक्रमmation about the location of this port
 */
काष्ठा ide_hw अणु
	जोड़ अणु
		काष्ठा ide_io_ports	io_ports;
		अचिन्हित दीर्घ		io_ports_array[IDE_NR_PORTS];
	पूर्ण;

	पूर्णांक		irq;			/* our irq number */
	काष्ठा device	*dev, *parent;
	अचिन्हित दीर्घ	config;
पूर्ण;

अटल अंतरभूत व्योम ide_std_init_ports(काष्ठा ide_hw *hw,
				      अचिन्हित दीर्घ io_addr,
				      अचिन्हित दीर्घ ctl_addr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i <= 7; i++)
		hw->io_ports_array[i] = io_addr++;

	hw->io_ports.ctl_addr = ctl_addr;
पूर्ण

#घोषणा MAX_HWIFS	10

/*
 * Now क्रम the data we need to मुख्यtain per-drive:  ide_drive_t
 */

#घोषणा ide_scsi	0x21
#घोषणा ide_disk	0x20
#घोषणा ide_optical	0x7
#घोषणा ide_cdrom	0x5
#घोषणा ide_tape	0x1
#घोषणा ide_floppy	0x0

/*
 * Special Driver Flags
 */
क्रमागत अणु
	IDE_SFLAG_SET_GEOMETRY		= BIT(0),
	IDE_SFLAG_RECALIBRATE		= BIT(1),
	IDE_SFLAG_SET_MULTMODE		= BIT(2),
पूर्ण;

/*
 * Status वापसed from various ide_ functions
 */
प्रकार क्रमागत अणु
	ide_stopped,	/* no drive operation was started */
	ide_started,	/* a drive operation was started, handler was set */
पूर्ण ide_startstop_t;

क्रमागत अणु
	IDE_VALID_ERROR 		= BIT(1),
	IDE_VALID_FEATURE		= IDE_VALID_ERROR,
	IDE_VALID_NSECT 		= BIT(2),
	IDE_VALID_LBAL			= BIT(3),
	IDE_VALID_LBAM			= BIT(4),
	IDE_VALID_LBAH			= BIT(5),
	IDE_VALID_DEVICE		= BIT(6),
	IDE_VALID_LBA			= IDE_VALID_LBAL |
					  IDE_VALID_LBAM |
					  IDE_VALID_LBAH,
	IDE_VALID_OUT_TF		= IDE_VALID_FEATURE |
					  IDE_VALID_NSECT |
					  IDE_VALID_LBA,
	IDE_VALID_IN_TF 		= IDE_VALID_NSECT |
					  IDE_VALID_LBA,
	IDE_VALID_OUT_HOB		= IDE_VALID_OUT_TF,
	IDE_VALID_IN_HOB		= IDE_VALID_ERROR |
					  IDE_VALID_NSECT |
					  IDE_VALID_LBA,
पूर्ण;

क्रमागत अणु
	IDE_TFLAG_LBA48			= BIT(0),
	IDE_TFLAG_WRITE			= BIT(1),
	IDE_TFLAG_CUSTOM_HANDLER	= BIT(2),
	IDE_TFLAG_DMA_PIO_FALLBACK	= BIT(3),
	/* क्रमce 16-bit I/O operations */
	IDE_TFLAG_IO_16BIT		= BIT(4),
	/* काष्ठा ide_cmd was allocated using kदो_स्मृति() */
	IDE_TFLAG_DYN			= BIT(5),
	IDE_TFLAG_FS			= BIT(6),
	IDE_TFLAG_MULTI_PIO		= BIT(7),
	IDE_TFLAG_SET_XFER		= BIT(8),
पूर्ण;

क्रमागत अणु
	IDE_FTFLAG_FLAGGED		= BIT(0),
	IDE_FTFLAG_SET_IN_FLAGS		= BIT(1),
	IDE_FTFLAG_OUT_DATA		= BIT(2),
	IDE_FTFLAG_IN_DATA		= BIT(3),
पूर्ण;

काष्ठा ide_taskfile अणु
	u8	data;		/* 0: data byte (क्रम TASKखाता ioctl) */
	जोड़ अणु			/* 1: */
		u8 error;	/*  पढ़ो: error */
		u8 feature;	/* ग_लिखो: feature */
	पूर्ण;
	u8	nsect;		/* 2: number of sectors */
	u8	lbal;		/* 3: LBA low */
	u8	lbam;		/* 4: LBA mid */
	u8	lbah;		/* 5: LBA high */
	u8	device;		/* 6: device select */
	जोड़ अणु			/* 7: */
		u8 status;	/*  पढ़ो: status */
		u8 command;	/* ग_लिखो: command */
	पूर्ण;
पूर्ण;

काष्ठा ide_cmd अणु
	काष्ठा ide_taskfile	tf;
	काष्ठा ide_taskfile	hob;
	काष्ठा अणु
		काष्ठा अणु
			u8		tf;
			u8		hob;
		पूर्ण out, in;
	पूर्ण valid;

	u16			tf_flags;
	u8			ftf_flags;	/* क्रम TASKखाता ioctl */
	पूर्णांक			protocol;

	पूर्णांक			sg_nents;	  /* number of sg entries */
	पूर्णांक			orig_sg_nents;
	पूर्णांक			sg_dma_direction; /* DMA transfer direction */

	अचिन्हित पूर्णांक		nbytes;
	अचिन्हित पूर्णांक		nleft;
	अचिन्हित पूर्णांक		last_xfer_len;

	काष्ठा scatterlist	*cursg;
	अचिन्हित पूर्णांक		cursg_ofs;

	काष्ठा request		*rq;		/* copy of request */
पूर्ण;

/* ATAPI packet command flags */
क्रमागत अणु
	/* set when an error is considered normal - no retry (ide-tape) */
	PC_FLAG_ABORT			= BIT(0),
	PC_FLAG_SUPPRESS_ERROR		= BIT(1),
	PC_FLAG_WAIT_FOR_DSC		= BIT(2),
	PC_FLAG_DMA_OK			= BIT(3),
	PC_FLAG_DMA_IN_PROGRESS		= BIT(4),
	PC_FLAG_DMA_ERROR		= BIT(5),
	PC_FLAG_WRITING			= BIT(6),
पूर्ण;

#घोषणा ATAPI_WAIT_PC		(60 * HZ)

काष्ठा ide_atapi_pc अणु
	/* actual packet bytes */
	u8 c[12];
	/* incremented on each retry */
	पूर्णांक retries;
	पूर्णांक error;

	/* bytes to transfer */
	पूर्णांक req_xfer;

	/* the corresponding request */
	काष्ठा request *rq;

	अचिन्हित दीर्घ flags;

	/*
	 * those are more or less driver-specअगरic and some of them are subject
	 * to change/removal later.
	 */
	अचिन्हित दीर्घ समयout;
पूर्ण;

काष्ठा ide_devset;
काष्ठा ide_driver;

#अगर_घोषित CONFIG_BLK_DEV_IDEACPI
काष्ठा ide_acpi_drive_link;
काष्ठा ide_acpi_hwअगर_link;
#पूर्ण_अगर

काष्ठा ide_drive_s;

काष्ठा ide_disk_ops अणु
	पूर्णांक		(*check)(काष्ठा ide_drive_s *, स्थिर अक्षर *);
	पूर्णांक		(*get_capacity)(काष्ठा ide_drive_s *);
	व्योम		(*unlock_native_capacity)(काष्ठा ide_drive_s *);
	व्योम		(*setup)(काष्ठा ide_drive_s *);
	व्योम		(*flush)(काष्ठा ide_drive_s *);
	पूर्णांक		(*init_media)(काष्ठा ide_drive_s *, काष्ठा gendisk *);
	पूर्णांक		(*set_करोorlock)(काष्ठा ide_drive_s *, काष्ठा gendisk *,
					पूर्णांक);
	ide_startstop_t	(*करो_request)(काष्ठा ide_drive_s *, काष्ठा request *,
				      sector_t);
	पूर्णांक		(*ioctl)(काष्ठा ide_drive_s *, काष्ठा block_device *,
				 भ_शेषe_t, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	पूर्णांक		(*compat_ioctl)(काष्ठा ide_drive_s *, काष्ठा block_device *,
					भ_शेषe_t, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
पूर्ण;

/* ATAPI device flags */
क्रमागत अणु
	IDE_AFLAG_DRQ_INTERRUPT		= BIT(0),

	/* ide-cd */
	/* Drive cannot eject the disc. */
	IDE_AFLAG_NO_EJECT		= BIT(1),
	/* Drive is a pre ATAPI 1.2 drive. */
	IDE_AFLAG_PRE_ATAPI12		= BIT(2),
	/* TOC addresses are in BCD. */
	IDE_AFLAG_TOCADDR_AS_BCD	= BIT(3),
	/* TOC track numbers are in BCD. */
	IDE_AFLAG_TOCTRACKS_AS_BCD	= BIT(4),
	/* Saved TOC inक्रमmation is current. */
	IDE_AFLAG_TOC_VALID		= BIT(6),
	/* We think that the drive करोor is locked. */
	IDE_AFLAG_DOOR_LOCKED		= BIT(7),
	/* SET_CD_SPEED command is unsupported. */
	IDE_AFLAG_NO_SPEED_SELECT	= BIT(8),
	IDE_AFLAG_VERTOS_300_SSD	= BIT(9),
	IDE_AFLAG_VERTOS_600_ESD	= BIT(10),
	IDE_AFLAG_SANYO_3CD		= BIT(11),
	IDE_AFLAG_FULL_CAPS_PAGE	= BIT(12),
	IDE_AFLAG_PLAY_AUDIO_OK		= BIT(13),
	IDE_AFLAG_LE_SPEED_FIELDS	= BIT(14),

	/* ide-floppy */
	/* Aव्योम commands not supported in Clik drive */
	IDE_AFLAG_CLIK_DRIVE		= BIT(15),
	/* Requires BH algorithm क्रम packets */
	IDE_AFLAG_ZIP_DRIVE		= BIT(16),
	/* Supports क्रमmat progress report */
	IDE_AFLAG_SRFP			= BIT(17),

	/* ide-tape */
	IDE_AFLAG_IGNORE_DSC		= BIT(18),
	/* 0 When the tape position is unknown */
	IDE_AFLAG_ADDRESS_VALID		= BIT(19),
	/* Device alपढ़ोy खोलोed */
	IDE_AFLAG_BUSY			= BIT(20),
	/* Attempt to स्वतः-detect the current user block size */
	IDE_AFLAG_DETECT_BS		= BIT(21),
	/* Currently on a filemark */
	IDE_AFLAG_खाताMARK		= BIT(22),
	/* 0 = no tape is loaded, so we करोn't शुरुआत after ejecting */
	IDE_AFLAG_MEDIUM_PRESENT	= BIT(23),

	IDE_AFLAG_NO_AUTOCLOSE		= BIT(24),
पूर्ण;

/* device flags */
क्रमागत अणु
	/* restore settings after device reset */
	IDE_DFLAG_KEEP_SETTINGS		= BIT(0),
	/* device is using DMA क्रम पढ़ो/ग_लिखो */
	IDE_DFLAG_USING_DMA		= BIT(1),
	/* okay to unmask other IRQs */
	IDE_DFLAG_UNMASK		= BIT(2),
	/* करोn't attempt flushes */
	IDE_DFLAG_NOFLUSH		= BIT(3),
	/* DSC overlap */
	IDE_DFLAG_DSC_OVERLAP		= BIT(4),
	/* give potential excess bandwidth */
	IDE_DFLAG_NICE1			= BIT(5),
	/* device is physically present */
	IDE_DFLAG_PRESENT		= BIT(6),
	/* disable Host Protected Area */
	IDE_DFLAG_NOHPA			= BIT(7),
	/* id पढ़ो from device (synthetic अगर not set) */
	IDE_DFLAG_ID_READ		= BIT(8),
	IDE_DFLAG_NOPROBE		= BIT(9),
	/* need to करो check_media_change() */
	IDE_DFLAG_REMOVABLE		= BIT(10),
	IDE_DFLAG_FORCED_GEOM		= BIT(12),
	/* disallow setting unmask bit */
	IDE_DFLAG_NO_UNMASK		= BIT(13),
	/* disallow enabling 32-bit I/O */
	IDE_DFLAG_NO_IO_32BIT		= BIT(14),
	/* क्रम removable only: करोor lock/unlock works */
	IDE_DFLAG_DOORLOCKING		= BIT(15),
	/* disallow DMA */
	IDE_DFLAG_NODMA			= BIT(16),
	/* घातermanagement told us not to करो anything, so sleep nicely */
	IDE_DFLAG_BLOCKED		= BIT(17),
	/* sleeping & sleep field valid */
	IDE_DFLAG_SLEEPING		= BIT(18),
	IDE_DFLAG_POST_RESET		= BIT(19),
	IDE_DFLAG_UDMA33_WARNED		= BIT(20),
	IDE_DFLAG_LBA48			= BIT(21),
	/* status of ग_लिखो cache */
	IDE_DFLAG_WCACHE		= BIT(22),
	/* used क्रम ignoring ATA_DF */
	IDE_DFLAG_NOWERR		= BIT(23),
	/* retrying in PIO */
	IDE_DFLAG_DMA_PIO_RETRY		= BIT(24),
	IDE_DFLAG_LBA			= BIT(25),
	/* करोn't unload heads */
	IDE_DFLAG_NO_UNLOAD		= BIT(26),
	/* heads unloaded, please करोn't reset port */
	IDE_DFLAG_PARKED		= BIT(27),
	IDE_DFLAG_MEDIA_CHANGED		= BIT(28),
	/* ग_लिखो protect */
	IDE_DFLAG_WP			= BIT(29),
	IDE_DFLAG_FORMAT_IN_PROGRESS	= BIT(30),
	IDE_DFLAG_NIEN_QUIRK		= BIT(31),
पूर्ण;

काष्ठा ide_drive_s अणु
	अक्षर		name[4];	/* drive name, such as "hda" */
        अक्षर            driver_req[10];	/* requests specअगरic driver */

	काष्ठा request_queue	*queue;	/* request queue */

	bool (*prep_rq)(काष्ठा ide_drive_s *, काष्ठा request *);

	काष्ठा blk_mq_tag_set	tag_set;

	काष्ठा request		*rq;	/* current request */
	व्योम		*driver_data;	/* extra driver data */
	u16			*id;	/* identअगरication info */
#अगर_घोषित CONFIG_IDE_PROC_FS
	काष्ठा proc_dir_entry *proc;	/* /proc/ide/ directory entry */
	स्थिर काष्ठा ide_proc_devset *settings; /* /proc/ide/ drive settings */
#पूर्ण_अगर
	काष्ठा hwअगर_s		*hwअगर;	/* actually (ide_hwअगर_t *) */

	स्थिर काष्ठा ide_disk_ops *disk_ops;

	अचिन्हित दीर्घ dev_flags;

	अचिन्हित दीर्घ sleep;		/* sleep until this समय */
	अचिन्हित दीर्घ समयout;		/* max समय to रुको क्रम irq */

	u8	special_flags;		/* special action flags */

	u8	select;			/* basic drive/head select reg value */
	u8	retry_pio;		/* retrying dma capable host in pio */
	u8	रुकोing_क्रम_dma;	/* dma currently in progress */
	u8	dma;			/* atapi dma flag */

        u8	init_speed;	/* transfer rate set at boot */
        u8	current_speed;	/* current transfer rate set */
	u8	desired_speed;	/* desired transfer rate set */
	u8	pio_mode;	/* क्रम ->set_pio_mode _only_ */
	u8	dma_mode;	/* क्रम ->set_dma_mode _only_ */
	u8	dn;		/* now wide spपढ़ो use */
	u8	acoustic;	/* acoustic management */
	u8	media;		/* disk, cdrom, tape, floppy, ... */
	u8	पढ़ोy_stat;	/* min status value क्रम drive पढ़ोy */
	u8	mult_count;	/* current multiple sector setting */
	u8	mult_req;	/* requested multiple sector setting */
	u8	io_32bit;	/* 0=16-bit, 1=32-bit, 2/3=32bit+sync */
	u8	bad_wstat;	/* used क्रम ignoring ATA_DF */
	u8	head;		/* "real" number of heads */
	u8	sect;		/* "real" sectors per track */
	u8	bios_head;	/* BIOS/fdisk/LILO number of heads */
	u8	bios_sect;	/* BIOS/fdisk/LILO sectors per track */

	/* delay this दीर्घ beक्रमe sending packet command */
	u8 pc_delay;

	अचिन्हित पूर्णांक	bios_cyl;	/* BIOS/fdisk/LILO number of cyls */
	अचिन्हित पूर्णांक	cyl;		/* "real" number of cyls */
	व्योम		*drive_data;	/* used by set_pio_mode/dev_select() */
	अचिन्हित पूर्णांक	failures;	/* current failure count */
	अचिन्हित पूर्णांक	max_failures;	/* maximum allowed failure count */
	u64		probed_capacity;/* initial/native media capacity */
	u64		capacity64;	/* total number of sectors */

	पूर्णांक		lun;		/* logical unit */
	पूर्णांक		crc_count;	/* crc counter to reduce drive speed */

	अचिन्हित दीर्घ	debug_mask;	/* debugging levels चयन */

#अगर_घोषित CONFIG_BLK_DEV_IDEACPI
	काष्ठा ide_acpi_drive_link *acpidata;
#पूर्ण_अगर
	काष्ठा list_head list;
	काष्ठा device	gendev;
	काष्ठा completion gendev_rel_comp;	/* to deal with device release() */

	/* current packet command */
	काष्ठा ide_atapi_pc *pc;

	/* last failed packet command */
	काष्ठा ide_atapi_pc *failed_pc;

	/* callback क्रम packet commands */
	पूर्णांक  (*pc_callback)(काष्ठा ide_drive_s *, पूर्णांक);

	ide_startstop_t (*irq_handler)(काष्ठा ide_drive_s *);

	अचिन्हित दीर्घ atapi_flags;

	काष्ठा ide_atapi_pc request_sense_pc;

	/* current sense rq and buffer */
	bool sense_rq_armed;
	bool sense_rq_active;
	काष्ठा request *sense_rq;
	काष्ठा request_sense sense_data;

	/* async sense insertion */
	काष्ठा work_काष्ठा rq_work;
	काष्ठा list_head rq_list;
पूर्ण;

प्रकार काष्ठा ide_drive_s ide_drive_t;

#घोषणा to_ide_device(dev)		container_of(dev, ide_drive_t, gendev)

#घोषणा to_ide_drv(obj, cont_type)	\
	container_of(obj, काष्ठा cont_type, dev)

#घोषणा ide_drv_g(disk, cont_type)	\
	container_of((disk)->निजी_data, काष्ठा cont_type, driver)

काष्ठा ide_port_info;

काष्ठा ide_tp_ops अणु
	व्योम	(*exec_command)(काष्ठा hwअगर_s *, u8);
	u8	(*पढ़ो_status)(काष्ठा hwअगर_s *);
	u8	(*पढ़ो_altstatus)(काष्ठा hwअगर_s *);
	व्योम	(*ग_लिखो_devctl)(काष्ठा hwअगर_s *, u8);

	व्योम	(*dev_select)(ide_drive_t *);
	व्योम	(*tf_load)(ide_drive_t *, काष्ठा ide_taskfile *, u8);
	व्योम	(*tf_पढ़ो)(ide_drive_t *, काष्ठा ide_taskfile *, u8);

	व्योम	(*input_data)(ide_drive_t *, काष्ठा ide_cmd *,
			      व्योम *, अचिन्हित पूर्णांक);
	व्योम	(*output_data)(ide_drive_t *, काष्ठा ide_cmd *,
			       व्योम *, अचिन्हित पूर्णांक);
पूर्ण;

बाह्य स्थिर काष्ठा ide_tp_ops शेष_tp_ops;

/**
 * काष्ठा ide_port_ops - IDE port operations
 *
 * @init_dev:		host specअगरic initialization of a device
 * @set_pio_mode:	routine to program host क्रम PIO mode
 * @set_dma_mode:	routine to program host क्रम DMA mode
 * @reset_poll:		chipset polling based on hba specअगरics
 * @pre_reset:		chipset specअगरic changes to शेष क्रम device-hba resets
 * @resetproc:		routine to reset controller after a disk reset
 * @maskproc:		special host masking क्रम drive selection
 * @quirkproc:		check host's drive quirk list
 * @clear_irq:		clear IRQ
 *
 * @mdma_filter:	filter MDMA modes
 * @udma_filter:	filter UDMA modes
 *
 * @cable_detect:	detect cable type
 */
काष्ठा ide_port_ops अणु
	व्योम	(*init_dev)(ide_drive_t *);
	व्योम	(*set_pio_mode)(काष्ठा hwअगर_s *, ide_drive_t *);
	व्योम	(*set_dma_mode)(काष्ठा hwअगर_s *, ide_drive_t *);
	blk_status_t (*reset_poll)(ide_drive_t *);
	व्योम	(*pre_reset)(ide_drive_t *);
	व्योम	(*resetproc)(ide_drive_t *);
	व्योम	(*maskproc)(ide_drive_t *, पूर्णांक);
	व्योम	(*quirkproc)(ide_drive_t *);
	व्योम	(*clear_irq)(ide_drive_t *);
	पूर्णांक	(*test_irq)(काष्ठा hwअगर_s *);

	u8	(*mdma_filter)(ide_drive_t *);
	u8	(*udma_filter)(ide_drive_t *);

	u8	(*cable_detect)(काष्ठा hwअगर_s *);
पूर्ण;

काष्ठा ide_dma_ops अणु
	व्योम	(*dma_host_set)(काष्ठा ide_drive_s *, पूर्णांक);
	पूर्णांक	(*dma_setup)(काष्ठा ide_drive_s *, काष्ठा ide_cmd *);
	व्योम	(*dma_start)(काष्ठा ide_drive_s *);
	पूर्णांक	(*dma_end)(काष्ठा ide_drive_s *);
	पूर्णांक	(*dma_test_irq)(काष्ठा ide_drive_s *);
	व्योम	(*dma_lost_irq)(काष्ठा ide_drive_s *);
	/* below ones are optional */
	पूर्णांक	(*dma_check)(काष्ठा ide_drive_s *, काष्ठा ide_cmd *);
	पूर्णांक	(*dma_समयr_expiry)(काष्ठा ide_drive_s *);
	व्योम	(*dma_clear)(काष्ठा ide_drive_s *);
	/*
	 * The following method is optional and only required to be
	 * implemented क्रम the SFF-8038i compatible controllers.
	 */
	u8	(*dma_sff_पढ़ो_status)(काष्ठा hwअगर_s *);
पूर्ण;

क्रमागत अणु
	IDE_PFLAG_PROBING		= BIT(0),
पूर्ण;

काष्ठा ide_host;

प्रकार काष्ठा hwअगर_s अणु
	काष्ठा hwअगर_s *mate;		/* other hwअगर from same PCI chip */
	काष्ठा proc_dir_entry *proc;	/* /proc/ide/ directory entry */

	काष्ठा ide_host *host;

	अक्षर name[6];			/* name of पूर्णांकerface, eg. "ide0" */

	काष्ठा ide_io_ports	io_ports;

	अचिन्हित दीर्घ	sata_scr[SATA_NR_PORTS];

	ide_drive_t	*devices[MAX_DRIVES + 1];

	अचिन्हित दीर्घ	port_flags;

	u8 major;	/* our major number */
	u8 index;	/* 0 क्रम ide0; 1 क्रम ide1; ... */
	u8 channel;	/* क्रम dual-port chips: 0=primary, 1=secondary */

	u32 host_flags;

	u8 pio_mask;

	u8 ultra_mask;
	u8 mwdma_mask;
	u8 swdma_mask;

	u8 cbl;		/* cable type */

	hwअगर_chipset_t chipset;	/* sub-module क्रम tuning.. */

	काष्ठा device *dev;

	व्योम (*rw_disk)(ide_drive_t *, काष्ठा request *);

	स्थिर काष्ठा ide_tp_ops		*tp_ops;
	स्थिर काष्ठा ide_port_ops	*port_ops;
	स्थिर काष्ठा ide_dma_ops	*dma_ops;

	/* dma physical region descriptor table (cpu view) */
	अचिन्हित पूर्णांक	*dmatable_cpu;
	/* dma physical region descriptor table (dma view) */
	dma_addr_t	dmatable_dma;

	/* maximum number of PRD table entries */
	पूर्णांक prd_max_nents;
	/* PRD entry size in bytes */
	पूर्णांक prd_ent_size;

	/* Scatter-gather list used to build the above */
	काष्ठा scatterlist *sg_table;
	पूर्णांक sg_max_nents;		/* Maximum number of entries in it */

	काष्ठा ide_cmd cmd;		/* current command */

	पूर्णांक		rqsize;		/* max sectors per request */
	पूर्णांक		irq;		/* our irq number */

	अचिन्हित दीर्घ	dma_base;	/* base addr क्रम dma ports */

	अचिन्हित दीर्घ	config_data;	/* क्रम use by chipset-specअगरic code */
	अचिन्हित दीर्घ	select_data;	/* क्रम use by chipset-specअगरic code */

	अचिन्हित दीर्घ	extra_base;	/* extra addr क्रम dma ports */
	अचिन्हित	extra_ports;	/* number of extra dma ports */

	अचिन्हित	present    : 1;	/* this पूर्णांकerface exists */
	अचिन्हित	busy	   : 1; /* serializes devices on a port */

	काष्ठा device		gendev;
	काष्ठा device		*portdev;

	काष्ठा completion gendev_rel_comp; /* To deal with device release() */

	व्योम		*hwअगर_data;	/* extra hwअगर data */

#अगर_घोषित CONFIG_BLK_DEV_IDEACPI
	काष्ठा ide_acpi_hwअगर_link *acpidata;
#पूर्ण_अगर

	/* IRQ handler, अगर active */
	ide_startstop_t	(*handler)(ide_drive_t *);

	/* BOOL: polling active & poll_समयout field valid */
	अचिन्हित पूर्णांक polling : 1;

	/* current drive */
	ide_drive_t *cur_dev;

	/* current request */
	काष्ठा request *rq;

	/* failsafe समयr */
	काष्ठा समयr_list समयr;
	/* समयout value during दीर्घ polls */
	अचिन्हित दीर्घ poll_समयout;
	/* queried upon समयouts */
	पूर्णांक (*expiry)(ide_drive_t *);

	पूर्णांक req_gen;
	पूर्णांक req_gen_समयr;

	spinlock_t lock;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp ide_hwअगर_t;

#घोषणा MAX_HOST_PORTS 4

काष्ठा ide_host अणु
	ide_hwअगर_t	*ports[MAX_HOST_PORTS + 1];
	अचिन्हित पूर्णांक	n_ports;
	काष्ठा device	*dev[2];

	पूर्णांक		(*init_chipset)(काष्ठा pci_dev *);

	व्योम		(*get_lock)(irq_handler_t, व्योम *);
	व्योम		(*release_lock)(व्योम);

	irq_handler_t	irq_handler;

	अचिन्हित दीर्घ	host_flags;

	पूर्णांक		irq_flags;

	व्योम		*host_priv;
	ide_hwअगर_t	*cur_port;	/* क्रम hosts requiring serialization */

	/* used क्रम hosts requiring serialization */
	अस्थिर अचिन्हित दीर्घ	host_busy;
पूर्ण;

#घोषणा IDE_HOST_BUSY 0

/*
 *  पूर्णांकernal ide पूर्णांकerrupt handler type
 */
प्रकार ide_startstop_t (ide_handler_t)(ide_drive_t *);
प्रकार पूर्णांक (ide_expiry_t)(ide_drive_t *);

/* used by ide-cd, ide-floppy, etc. */
प्रकार व्योम (xfer_func_t)(ide_drive_t *, काष्ठा ide_cmd *, व्योम *, अचिन्हित);

बाह्य काष्ठा mutex ide_setting_mtx;

/*
 * configurable drive settings
 */

#घोषणा DS_SYNC	BIT(0)

काष्ठा ide_devset अणु
	पूर्णांक		(*get)(ide_drive_t *);
	पूर्णांक		(*set)(ide_drive_t *, पूर्णांक);
	अचिन्हित पूर्णांक	flags;
पूर्ण;

#घोषणा __DEVSET(_flags, _get, _set) अणु \
	.flags	= _flags, \
	.get	= _get,	\
	.set	= _set,	\
पूर्ण

#घोषणा ide_devset_get(name, field) \
अटल पूर्णांक get_##name(ide_drive_t *drive) \
अणु \
	वापस drive->field; \
पूर्ण

#घोषणा ide_devset_set(name, field) \
अटल पूर्णांक set_##name(ide_drive_t *drive, पूर्णांक arg) \
अणु \
	drive->field = arg; \
	वापस 0; \
पूर्ण

#घोषणा ide_devset_get_flag(name, flag) \
अटल पूर्णांक get_##name(ide_drive_t *drive) \
अणु \
	वापस !!(drive->dev_flags & flag); \
पूर्ण

#घोषणा ide_devset_set_flag(name, flag) \
अटल पूर्णांक set_##name(ide_drive_t *drive, पूर्णांक arg) \
अणु \
	अगर (arg) \
		drive->dev_flags |= flag; \
	अन्यथा \
		drive->dev_flags &= ~flag; \
	वापस 0; \
पूर्ण

#घोषणा __IDE_DEVSET(_name, _flags, _get, _set) \
स्थिर काष्ठा ide_devset ide_devset_##_name = \
	__DEVSET(_flags, _get, _set)

#घोषणा IDE_DEVSET(_name, _flags, _get, _set) \
अटल __IDE_DEVSET(_name, _flags, _get, _set)

#घोषणा ide_devset_rw(_name, _func) \
IDE_DEVSET(_name, 0, get_##_func, set_##_func)

#घोषणा ide_devset_w(_name, _func) \
IDE_DEVSET(_name, 0, शून्य, set_##_func)

#घोषणा ide_ext_devset_rw(_name, _func) \
__IDE_DEVSET(_name, 0, get_##_func, set_##_func)

#घोषणा ide_ext_devset_rw_sync(_name, _func) \
__IDE_DEVSET(_name, DS_SYNC, get_##_func, set_##_func)

#घोषणा ide_decl_devset(_name) \
बाह्य स्थिर काष्ठा ide_devset ide_devset_##_name

ide_decl_devset(io_32bit);
ide_decl_devset(keepsettings);
ide_decl_devset(pio_mode);
ide_decl_devset(unmaskirq);
ide_decl_devset(using_dma);

#अगर_घोषित CONFIG_IDE_PROC_FS
/*
 * /proc/ide पूर्णांकerface
 */

#घोषणा ide_devset_rw_field(_name, _field) \
ide_devset_get(_name, _field); \
ide_devset_set(_name, _field); \
IDE_DEVSET(_name, DS_SYNC, get_##_name, set_##_name)

#घोषणा ide_devset_ro_field(_name, _field) \
ide_devset_get(_name, _field); \
IDE_DEVSET(_name, 0, get_##_name, शून्य)

#घोषणा ide_devset_rw_flag(_name, _field) \
ide_devset_get_flag(_name, _field); \
ide_devset_set_flag(_name, _field); \
IDE_DEVSET(_name, DS_SYNC, get_##_name, set_##_name)

काष्ठा ide_proc_devset अणु
	स्थिर अक्षर		*name;
	स्थिर काष्ठा ide_devset	*setting;
	पूर्णांक			min, max;
	पूर्णांक			(*mulf)(ide_drive_t *);
	पूर्णांक			(*भागf)(ide_drive_t *);
पूर्ण;

#घोषणा __IDE_PROC_DEVSET(_name, _min, _max, _mulf, _भागf) अणु \
	.name = __stringअगरy(_name), \
	.setting = &ide_devset_##_name, \
	.min = _min, \
	.max = _max, \
	.mulf = _mulf, \
	.भागf = _भागf, \
पूर्ण

#घोषणा IDE_PROC_DEVSET(_name, _min, _max) \
__IDE_PROC_DEVSET(_name, _min, _max, शून्य, शून्य)

प्रकार काष्ठा अणु
	स्थिर अक्षर	*name;
	umode_t		mode;
	पूर्णांक (*show)(काष्ठा seq_file *, व्योम *);
पूर्ण ide_proc_entry_t;

व्योम proc_ide_create(व्योम);
व्योम proc_ide_destroy(व्योम);
व्योम ide_proc_रेजिस्टर_port(ide_hwअगर_t *);
व्योम ide_proc_port_रेजिस्टर_devices(ide_hwअगर_t *);
व्योम ide_proc_unरेजिस्टर_device(ide_drive_t *);
व्योम ide_proc_unरेजिस्टर_port(ide_hwअगर_t *);
व्योम ide_proc_रेजिस्टर_driver(ide_drive_t *, काष्ठा ide_driver *);
व्योम ide_proc_unरेजिस्टर_driver(ide_drive_t *, काष्ठा ide_driver *);

पूर्णांक ide_capacity_proc_show(काष्ठा seq_file *m, व्योम *v);
पूर्णांक ide_geometry_proc_show(काष्ठा seq_file *m, व्योम *v);
#अन्यथा
अटल अंतरभूत व्योम proc_ide_create(व्योम) अणु ; पूर्ण
अटल अंतरभूत व्योम proc_ide_destroy(व्योम) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_proc_रेजिस्टर_port(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_proc_port_रेजिस्टर_devices(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_proc_unरेजिस्टर_device(ide_drive_t *drive) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_proc_unरेजिस्टर_port(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_proc_रेजिस्टर_driver(ide_drive_t *drive,
					    काष्ठा ide_driver *driver) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_proc_unरेजिस्टर_driver(ide_drive_t *drive,
					      काष्ठा ide_driver *driver) अणु ; पूर्ण
#पूर्ण_अगर

क्रमागत अणु
	/* enter/निकास functions */
	IDE_DBG_FUNC =			BIT(0),
	/* sense key/asc handling */
	IDE_DBG_SENSE =			BIT(1),
	/* packet commands handling */
	IDE_DBG_PC =			BIT(2),
	/* request handling */
	IDE_DBG_RQ =			BIT(3),
	/* driver probing/setup */
	IDE_DBG_PROBE =			BIT(4),
पूर्ण;

/* DRV_NAME has to be defined in the driver beक्रमe using the macro below */
#घोषणा __ide_debug_log(lvl, fmt, args...)				\
अणु									\
	अगर (unlikely(drive->debug_mask & lvl))				\
		prपूर्णांकk(KERN_INFO DRV_NAME ": %s: " fmt "\n",		\
					  __func__, ## args);		\
पूर्ण

/*
 * Power Management state machine (rq->pm->pm_step).
 *
 * For each step, the core calls ide_start_घातer_step() first.
 * This can वापस:
 *	- ide_stopped :	In this हाल, the core calls us back again unless
 *			step have been set to ide_घातer_state_completed.
 *	- ide_started :	In this हाल, the channel is left busy until an
 *			async event (पूर्णांकerrupt) occurs.
 * Typically, ide_start_घातer_step() will issue a taskfile request with
 * करो_rw_taskfile().
 *
 * Upon reception of the पूर्णांकerrupt, the core will call ide_complete_घातer_step()
 * with the error code अगर any. This routine should update the step value
 * and वापस. It should not start a new request. The core will call
 * ide_start_घातer_step() क्रम the new step value, unless step have been
 * set to IDE_PM_COMPLETED.
 */
क्रमागत अणु
	IDE_PM_START_SUSPEND,
	IDE_PM_FLUSH_CACHE	= IDE_PM_START_SUSPEND,
	IDE_PM_STANDBY,

	IDE_PM_START_RESUME,
	IDE_PM_RESTORE_PIO	= IDE_PM_START_RESUME,
	IDE_PM_IDLE,
	IDE_PM_RESTORE_DMA,

	IDE_PM_COMPLETED,
पूर्ण;

पूर्णांक generic_ide_suspend(काष्ठा device *, pm_message_t);
पूर्णांक generic_ide_resume(काष्ठा device *);

व्योम ide_complete_घातer_step(ide_drive_t *, काष्ठा request *);
ide_startstop_t ide_start_घातer_step(ide_drive_t *, काष्ठा request *);
व्योम ide_complete_pm_rq(ide_drive_t *, काष्ठा request *);
व्योम ide_check_pm_state(ide_drive_t *, काष्ठा request *);

/*
 * Subdrivers support.
 *
 * The gendriver.owner field should be set to the module owner of this driver.
 * The gendriver.name field should be set to the name of this driver
 */
काष्ठा ide_driver अणु
	स्थिर अक्षर			*version;
	ide_startstop_t	(*करो_request)(ide_drive_t *, काष्ठा request *, sector_t);
	काष्ठा device_driver	gen_driver;
	पूर्णांक		(*probe)(ide_drive_t *);
	व्योम		(*हटाओ)(ide_drive_t *);
	व्योम		(*resume)(ide_drive_t *);
	व्योम		(*shutकरोwn)(ide_drive_t *);
#अगर_घोषित CONFIG_IDE_PROC_FS
	ide_proc_entry_t *		(*proc_entries)(ide_drive_t *);
	स्थिर काष्ठा ide_proc_devset *	(*proc_devsets)(ide_drive_t *);
#पूर्ण_अगर
पूर्ण;

#घोषणा to_ide_driver(drv) container_of(drv, काष्ठा ide_driver, gen_driver)

पूर्णांक ide_device_get(ide_drive_t *);
व्योम ide_device_put(ide_drive_t *);

काष्ठा ide_ioctl_devset अणु
	अचिन्हित पूर्णांक	get_ioctl;
	अचिन्हित पूर्णांक	set_ioctl;
	स्थिर काष्ठा ide_devset *setting;
पूर्ण;

पूर्णांक ide_setting_ioctl(ide_drive_t *, काष्ठा block_device *, अचिन्हित पूर्णांक,
		      अचिन्हित दीर्घ, स्थिर काष्ठा ide_ioctl_devset *);

पूर्णांक generic_ide_ioctl(ide_drive_t *, काष्ठा block_device *, अचिन्हित, अचिन्हित दीर्घ);

बाह्य पूर्णांक ide_vlb_clk;
बाह्य पूर्णांक ide_pci_clk;

पूर्णांक ide_end_rq(ide_drive_t *, काष्ठा request *, blk_status_t, अचिन्हित पूर्णांक);
व्योम ide_समाप्त_rq(ide_drive_t *, काष्ठा request *);
व्योम ide_insert_request_head(ide_drive_t *, काष्ठा request *);

व्योम __ide_set_handler(ide_drive_t *, ide_handler_t *, अचिन्हित पूर्णांक);
व्योम ide_set_handler(ide_drive_t *, ide_handler_t *, अचिन्हित पूर्णांक);

व्योम ide_execute_command(ide_drive_t *, काष्ठा ide_cmd *, ide_handler_t *,
			 अचिन्हित पूर्णांक);

व्योम ide_pad_transfer(ide_drive_t *, पूर्णांक, पूर्णांक);

ide_startstop_t ide_error(ide_drive_t *, स्थिर अक्षर *, u8);

व्योम ide_fix_driveid(u16 *);

बाह्य व्योम ide_fixstring(u8 *, स्थिर पूर्णांक, स्थिर पूर्णांक);

पूर्णांक ide_busy_sleep(ide_drive_t *, अचिन्हित दीर्घ, पूर्णांक);

पूर्णांक __ide_रुको_stat(ide_drive_t *, u8, u8, अचिन्हित दीर्घ, u8 *);
पूर्णांक ide_रुको_stat(ide_startstop_t *, ide_drive_t *, u8, u8, अचिन्हित दीर्घ);

ide_startstop_t ide_करो_park_unpark(ide_drive_t *, काष्ठा request *);
ide_startstop_t ide_करो_devset(ide_drive_t *, काष्ठा request *);

बाह्य ide_startstop_t ide_करो_reset (ide_drive_t *);

बाह्य पूर्णांक ide_devset_execute(ide_drive_t *drive,
			      स्थिर काष्ठा ide_devset *setting, पूर्णांक arg);

व्योम ide_complete_cmd(ide_drive_t *, काष्ठा ide_cmd *, u8, u8);
पूर्णांक ide_complete_rq(ide_drive_t *, blk_status_t, अचिन्हित पूर्णांक);

व्योम ide_tf_पढ़ोback(ide_drive_t *drive, काष्ठा ide_cmd *cmd);
व्योम ide_tf_dump(स्थिर अक्षर *, काष्ठा ide_cmd *);

व्योम ide_exec_command(ide_hwअगर_t *, u8);
u8 ide_पढ़ो_status(ide_hwअगर_t *);
u8 ide_पढ़ो_altstatus(ide_hwअगर_t *);
व्योम ide_ग_लिखो_devctl(ide_hwअगर_t *, u8);

व्योम ide_dev_select(ide_drive_t *);
व्योम ide_tf_load(ide_drive_t *, काष्ठा ide_taskfile *, u8);
व्योम ide_tf_पढ़ो(ide_drive_t *, काष्ठा ide_taskfile *, u8);

व्योम ide_input_data(ide_drive_t *, काष्ठा ide_cmd *, व्योम *, अचिन्हित पूर्णांक);
व्योम ide_output_data(ide_drive_t *, काष्ठा ide_cmd *, व्योम *, अचिन्हित पूर्णांक);

व्योम SELECT_MASK(ide_drive_t *, पूर्णांक);

u8 ide_पढ़ो_error(ide_drive_t *);
व्योम ide_पढ़ो_bcount_and_ireason(ide_drive_t *, u16 *, u8 *);

पूर्णांक ide_check_ireason(ide_drive_t *, काष्ठा request *, पूर्णांक, पूर्णांक, पूर्णांक);

पूर्णांक ide_check_atapi_device(ide_drive_t *, स्थिर अक्षर *);

व्योम ide_init_pc(काष्ठा ide_atapi_pc *);

/* Disk head parking */
बाह्य रुको_queue_head_t ide_park_wq;
sमाप_प्रकार ide_park_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf);
sमाप_प्रकार ide_park_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार len);

/*
 * Special requests क्रम ide-tape block device strategy routine.
 *
 * In order to service a अक्षरacter device command, we add special requests to
 * the tail of our block device request queue and रुको क्रम their completion.
 */
क्रमागत अणु
	REQ_IDETAPE_PC1		= BIT(0), /* packet command (first stage) */
	REQ_IDETAPE_PC2		= BIT(1), /* packet command (second stage) */
	REQ_IDETAPE_READ	= BIT(2),
	REQ_IDETAPE_WRITE	= BIT(3),
पूर्ण;

पूर्णांक ide_queue_pc_tail(ide_drive_t *, काष्ठा gendisk *, काष्ठा ide_atapi_pc *,
		      व्योम *, अचिन्हित पूर्णांक);

पूर्णांक ide_करो_test_unit_पढ़ोy(ide_drive_t *, काष्ठा gendisk *);
पूर्णांक ide_करो_start_stop(ide_drive_t *, काष्ठा gendisk *, पूर्णांक);
पूर्णांक ide_set_media_lock(ide_drive_t *, काष्ठा gendisk *, पूर्णांक);
व्योम ide_create_request_sense_cmd(ide_drive_t *, काष्ठा ide_atapi_pc *);
व्योम ide_retry_pc(ide_drive_t *drive);

व्योम ide_prep_sense(ide_drive_t *drive, काष्ठा request *rq);
पूर्णांक ide_queue_sense_rq(ide_drive_t *drive, व्योम *special);

पूर्णांक ide_cd_expiry(ide_drive_t *);

पूर्णांक ide_cd_get_xferlen(काष्ठा request *);

ide_startstop_t ide_issue_pc(ide_drive_t *, काष्ठा ide_cmd *);

ide_startstop_t करो_rw_taskfile(ide_drive_t *, काष्ठा ide_cmd *);

व्योम ide_pio_bytes(ide_drive_t *, काष्ठा ide_cmd *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

व्योम ide_finish_cmd(ide_drive_t *, काष्ठा ide_cmd *, u8);

पूर्णांक ide_raw_taskfile(ide_drive_t *, काष्ठा ide_cmd *, u8 *, u16);
पूर्णांक ide_no_data_taskfile(ide_drive_t *, काष्ठा ide_cmd *);

पूर्णांक ide_taskfile_ioctl(ide_drive_t *, अचिन्हित दीर्घ);

पूर्णांक ide_dev_पढ़ो_id(ide_drive_t *, u8, u16 *, पूर्णांक);

बाह्य पूर्णांक ide_driveid_update(ide_drive_t *);
बाह्य पूर्णांक ide_config_drive_speed(ide_drive_t *, u8);
बाह्य u8 eighty_nपूर्णांकy_three (ide_drive_t *);
बाह्य पूर्णांक taskfile_lib_get_identअगरy(ide_drive_t *drive, u8 *);

बाह्य पूर्णांक ide_रुको_not_busy(ide_hwअगर_t *hwअगर, अचिन्हित दीर्घ समयout);

बाह्य व्योम ide_stall_queue(ide_drive_t *drive, अचिन्हित दीर्घ समयout);

बाह्य व्योम ide_समयr_expiry(काष्ठा समयr_list *t);
बाह्य irqवापस_t ide_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
बाह्य blk_status_t ide_queue_rq(काष्ठा blk_mq_hw_ctx *, स्थिर काष्ठा blk_mq_queue_data *);
बाह्य blk_status_t ide_issue_rq(ide_drive_t *, काष्ठा request *, bool);
बाह्य व्योम ide_requeue_and_plug(ide_drive_t *drive, काष्ठा request *rq);

व्योम ide_init_disk(काष्ठा gendisk *, ide_drive_t *);

#अगर_घोषित CONFIG_IDEPCI_PCIBUS_ORDER
बाह्य पूर्णांक __ide_pci_रेजिस्टर_driver(काष्ठा pci_driver *driver, काष्ठा module *owner, स्थिर अक्षर *mod_name);
#घोषणा ide_pci_रेजिस्टर_driver(d) __ide_pci_रेजिस्टर_driver(d, THIS_MODULE, KBUILD_MODNAME)
#अन्यथा
#घोषणा ide_pci_रेजिस्टर_driver(d) pci_रेजिस्टर_driver(d)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक ide_pci_is_in_compatibility_mode(काष्ठा pci_dev *dev)
अणु
	अगर ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE && (dev->class & 5) != 5)
		वापस 1;
	वापस 0;
पूर्ण

व्योम ide_pci_setup_ports(काष्ठा pci_dev *, स्थिर काष्ठा ide_port_info *,
			 काष्ठा ide_hw *, काष्ठा ide_hw **);
व्योम ide_setup_pci_noise(काष्ठा pci_dev *, स्थिर काष्ठा ide_port_info *);

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA_PCI
पूर्णांक ide_pci_set_master(काष्ठा pci_dev *, स्थिर अक्षर *);
अचिन्हित दीर्घ ide_pci_dma_base(ide_hwअगर_t *, स्थिर काष्ठा ide_port_info *);
पूर्णांक ide_pci_check_simplex(ide_hwअगर_t *, स्थिर काष्ठा ide_port_info *);
पूर्णांक ide_hwअगर_setup_dma(ide_hwअगर_t *, स्थिर काष्ठा ide_port_info *);
#अन्यथा
अटल अंतरभूत पूर्णांक ide_hwअगर_setup_dma(ide_hwअगर_t *hwअगर,
				     स्थिर काष्ठा ide_port_info *d)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

काष्ठा ide_pci_enablebit अणु
	u8	reg;	/* byte pci reg holding the enable-bit */
	u8	mask;	/* mask to isolate the enable-bit */
	u8	val;	/* value of masked reg when "enabled" */
पूर्ण;

क्रमागत अणु
	/* Uses ISA control ports not PCI ones. */
	IDE_HFLAG_ISA_PORTS		= BIT(0),
	/* single port device */
	IDE_HFLAG_SINGLE		= BIT(1),
	/* करोn't use legacy PIO blacklist */
	IDE_HFLAG_PIO_NO_BLACKLIST	= BIT(2),
	/* set क्रम the second port of QD65xx */
	IDE_HFLAG_QD_2ND_PORT		= BIT(3),
	/* use PIO8/9 क्रम prefetch off/on */
	IDE_HFLAG_ABUSE_PREFETCH	= BIT(4),
	/* use PIO6/7 क्रम fast-devsel off/on */
	IDE_HFLAG_ABUSE_FAST_DEVSEL	= BIT(5),
	/* use 100-102 and 200-202 PIO values to set DMA modes */
	IDE_HFLAG_ABUSE_DMA_MODES	= BIT(6),
	/*
	 * keep DMA setting when programming PIO mode, may be used only
	 * क्रम hosts which have separate PIO and DMA timings (ie. PMAC)
	 */
	IDE_HFLAG_SET_PIO_MODE_KEEP_DMA	= BIT(7),
	/* program host क्रम the transfer mode after programming device */
	IDE_HFLAG_POST_SET_MODE		= BIT(8),
	/* करोn't program host/device क्रम the transfer mode ("smart" hosts) */
	IDE_HFLAG_NO_SET_MODE		= BIT(9),
	/* trust BIOS क्रम programming chipset/device क्रम DMA */
	IDE_HFLAG_TRUST_BIOS_FOR_DMA	= BIT(10),
	/* host is CS5510/CS5520 */
	IDE_HFLAG_CS5520		= BIT(11),
	/* ATAPI DMA is unsupported */
	IDE_HFLAG_NO_ATAPI_DMA		= BIT(12),
	/* set अगर host is a "non-bootable" controller */
	IDE_HFLAG_NON_BOOTABLE		= BIT(13),
	/* host करोesn't support DMA */
	IDE_HFLAG_NO_DMA		= BIT(14),
	/* check अगर host is PCI IDE device beक्रमe allowing DMA */
	IDE_HFLAG_NO_AUTODMA		= BIT(15),
	/* host uses MMIO */
	IDE_HFLAG_MMIO			= BIT(16),
	/* no LBA48 */
	IDE_HFLAG_NO_LBA48		= BIT(17),
	/* no LBA48 DMA */
	IDE_HFLAG_NO_LBA48_DMA		= BIT(18),
	/* data FIFO is cleared by an error */
	IDE_HFLAG_ERROR_STOPS_FIFO	= BIT(19),
	/* serialize ports */
	IDE_HFLAG_SERIALIZE		= BIT(20),
	/* host is DTC2278 */
	IDE_HFLAG_DTC2278		= BIT(21),
	/* 4 devices on a single set of I/O ports */
	IDE_HFLAG_4DRIVES		= BIT(22),
	/* host is TRM290 */
	IDE_HFLAG_TRM290		= BIT(23),
	/* use 32-bit I/O ops */
	IDE_HFLAG_IO_32BIT		= BIT(24),
	/* unmask IRQs */
	IDE_HFLAG_UNMASK_IRQS		= BIT(25),
	IDE_HFLAG_BROKEN_ALTSTATUS	= BIT(26),
	/* serialize ports अगर DMA is possible (क्रम sl82c105) */
	IDE_HFLAG_SERIALIZE_DMA		= BIT(27),
	/* क्रमce host out of "simplex" mode */
	IDE_HFLAG_CLEAR_SIMPLEX		= BIT(28),
	/* DSC overlap is unsupported */
	IDE_HFLAG_NO_DSC		= BIT(29),
	/* never use 32-bit I/O ops */
	IDE_HFLAG_NO_IO_32BIT		= BIT(30),
	/* never unmask IRQs */
	IDE_HFLAG_NO_UNMASK_IRQS	= BIT(31),
पूर्ण;

#अगर_घोषित CONFIG_BLK_DEV_OFFBOARD
# define IDE_HFLAG_OFF_BOARD	0
#अन्यथा
# define IDE_HFLAG_OFF_BOARD	IDE_HFLAG_NON_BOOTABLE
#पूर्ण_अगर

काष्ठा ide_port_info अणु
	अक्षर			*name;

	पूर्णांक			(*init_chipset)(काष्ठा pci_dev *);

	व्योम			(*get_lock)(irq_handler_t, व्योम *);
	व्योम			(*release_lock)(व्योम);

	व्योम			(*init_iops)(ide_hwअगर_t *);
	व्योम                    (*init_hwअगर)(ide_hwअगर_t *);
	पूर्णांक			(*init_dma)(ide_hwअगर_t *,
					    स्थिर काष्ठा ide_port_info *);

	स्थिर काष्ठा ide_tp_ops		*tp_ops;
	स्थिर काष्ठा ide_port_ops	*port_ops;
	स्थिर काष्ठा ide_dma_ops	*dma_ops;

	काष्ठा ide_pci_enablebit	enablebits[2];

	hwअगर_chipset_t		chipset;

	u16			max_sectors;	/* अगर < than the शेष one */

	u32			host_flags;

	पूर्णांक			irq_flags;

	u8			pio_mask;
	u8			swdma_mask;
	u8			mwdma_mask;
	u8			udma_mask;
पूर्ण;

/*
 * State inक्रमmation carried क्रम REQ_TYPE_ATA_PM_SUSPEND and REQ_TYPE_ATA_PM_RESUME
 * requests.
 */
काष्ठा ide_pm_state अणु
	/* PM state machine step value, currently driver specअगरic */
	पूर्णांक	pm_step;
	/* requested PM state value (S1, S2, S3, S4, ...) */
	u32	pm_state;
	व्योम*	data;		/* क्रम driver use */
पूर्ण;


पूर्णांक ide_pci_init_one(काष्ठा pci_dev *, स्थिर काष्ठा ide_port_info *, व्योम *);
पूर्णांक ide_pci_init_two(काष्ठा pci_dev *, काष्ठा pci_dev *,
		     स्थिर काष्ठा ide_port_info *, व्योम *);
व्योम ide_pci_हटाओ(काष्ठा pci_dev *);

#अगर_घोषित CONFIG_PM
पूर्णांक ide_pci_suspend(काष्ठा pci_dev *, pm_message_t);
पूर्णांक ide_pci_resume(काष्ठा pci_dev *);
#अन्यथा
#घोषणा ide_pci_suspend शून्य
#घोषणा ide_pci_resume शून्य
#पूर्ण_अगर

व्योम ide_map_sg(ide_drive_t *, काष्ठा ide_cmd *);
व्योम ide_init_sg_cmd(काष्ठा ide_cmd *, अचिन्हित पूर्णांक);

#घोषणा BAD_DMA_DRIVE		0
#घोषणा GOOD_DMA_DRIVE		1

काष्ठा drive_list_entry अणु
	स्थिर अक्षर *id_model;
	स्थिर अक्षर *id_firmware;
पूर्ण;

पूर्णांक ide_in_drive_list(u16 *, स्थिर काष्ठा drive_list_entry *);

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA
पूर्णांक ide_dma_good_drive(ide_drive_t *);
पूर्णांक __ide_dma_bad_drive(ide_drive_t *);

u8 ide_find_dma_mode(ide_drive_t *, u8);

अटल अंतरभूत u8 ide_max_dma_mode(ide_drive_t *drive)
अणु
	वापस ide_find_dma_mode(drive, XFER_UDMA_6);
पूर्ण

व्योम ide_dma_off_quietly(ide_drive_t *);
व्योम ide_dma_off(ide_drive_t *);
व्योम ide_dma_on(ide_drive_t *);
पूर्णांक ide_set_dma(ide_drive_t *);
व्योम ide_check_dma_crc(ide_drive_t *);
ide_startstop_t ide_dma_पूर्णांकr(ide_drive_t *);

पूर्णांक ide_allocate_dma_engine(ide_hwअगर_t *);
व्योम ide_release_dma_engine(ide_hwअगर_t *);

पूर्णांक ide_dma_prepare(ide_drive_t *, काष्ठा ide_cmd *);
व्योम ide_dma_unmap_sg(ide_drive_t *, काष्ठा ide_cmd *);

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA_SFF
पूर्णांक config_drive_क्रम_dma(ide_drive_t *);
पूर्णांक ide_build_dmatable(ide_drive_t *, काष्ठा ide_cmd *);
व्योम ide_dma_host_set(ide_drive_t *, पूर्णांक);
पूर्णांक ide_dma_setup(ide_drive_t *, काष्ठा ide_cmd *);
बाह्य व्योम ide_dma_start(ide_drive_t *);
पूर्णांक ide_dma_end(ide_drive_t *);
पूर्णांक ide_dma_test_irq(ide_drive_t *);
पूर्णांक ide_dma_sff_समयr_expiry(ide_drive_t *);
u8 ide_dma_sff_पढ़ो_status(ide_hwअगर_t *);
बाह्य स्थिर काष्ठा ide_dma_ops sff_dma_ops;
#अन्यथा
अटल अंतरभूत पूर्णांक config_drive_क्रम_dma(ide_drive_t *drive) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_IDEDMA_SFF */

व्योम ide_dma_lost_irq(ide_drive_t *);
ide_startstop_t ide_dma_समयout_retry(ide_drive_t *, पूर्णांक);

#अन्यथा
अटल अंतरभूत u8 ide_find_dma_mode(ide_drive_t *drive, u8 speed) अणु वापस 0; पूर्ण
अटल अंतरभूत u8 ide_max_dma_mode(ide_drive_t *drive) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ide_dma_off_quietly(ide_drive_t *drive) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_dma_off(ide_drive_t *drive) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_dma_on(ide_drive_t *drive) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_dma_verbose(ide_drive_t *drive) अणु ; पूर्ण
अटल अंतरभूत पूर्णांक ide_set_dma(ide_drive_t *drive) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम ide_check_dma_crc(ide_drive_t *drive) अणु ; पूर्ण
अटल अंतरभूत ide_startstop_t ide_dma_पूर्णांकr(ide_drive_t *drive) अणु वापस ide_stopped; पूर्ण
अटल अंतरभूत ide_startstop_t ide_dma_समयout_retry(ide_drive_t *drive, पूर्णांक error) अणु वापस ide_stopped; पूर्ण
अटल अंतरभूत व्योम ide_release_dma_engine(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत पूर्णांक ide_dma_prepare(ide_drive_t *drive,
				  काष्ठा ide_cmd *cmd) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम ide_dma_unmap_sg(ide_drive_t *drive,
				    काष्ठा ide_cmd *cmd) अणु ; पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_IDEDMA */

#अगर_घोषित CONFIG_BLK_DEV_IDEACPI
पूर्णांक ide_acpi_init(व्योम);
bool ide_port_acpi(ide_hwअगर_t *hwअगर);
बाह्य पूर्णांक ide_acpi_exec_tfs(ide_drive_t *drive);
बाह्य व्योम ide_acpi_get_timing(ide_hwअगर_t *hwअगर);
बाह्य व्योम ide_acpi_push_timing(ide_hwअगर_t *hwअगर);
व्योम ide_acpi_init_port(ide_hwअगर_t *);
व्योम ide_acpi_port_init_devices(ide_hwअगर_t *);
बाह्य व्योम ide_acpi_set_state(ide_hwअगर_t *hwअगर, पूर्णांक on);
#अन्यथा
अटल अंतरभूत पूर्णांक ide_acpi_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत bool ide_port_acpi(ide_hwअगर_t *hwअगर) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक ide_acpi_exec_tfs(ide_drive_t *drive) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ide_acpi_get_timing(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_acpi_push_timing(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_acpi_init_port(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_acpi_port_init_devices(ide_hwअगर_t *hwअगर) अणु ; पूर्ण
अटल अंतरभूत व्योम ide_acpi_set_state(ide_hwअगर_t *hwअगर, पूर्णांक on) अणुपूर्ण
#पूर्ण_अगर

व्योम ide_check_nien_quirk_list(ide_drive_t *);
व्योम ide_undecoded_slave(ide_drive_t *);

व्योम ide_port_apply_params(ide_hwअगर_t *);
पूर्णांक ide_sysfs_रेजिस्टर_port(ide_hwअगर_t *);

काष्ठा ide_host *ide_host_alloc(स्थिर काष्ठा ide_port_info *, काष्ठा ide_hw **,
				अचिन्हित पूर्णांक);
व्योम ide_host_मुक्त(काष्ठा ide_host *);
पूर्णांक ide_host_रेजिस्टर(काष्ठा ide_host *, स्थिर काष्ठा ide_port_info *,
		      काष्ठा ide_hw **);
पूर्णांक ide_host_add(स्थिर काष्ठा ide_port_info *, काष्ठा ide_hw **, अचिन्हित पूर्णांक,
		 काष्ठा ide_host **);
व्योम ide_host_हटाओ(काष्ठा ide_host *);
पूर्णांक ide_legacy_device_add(स्थिर काष्ठा ide_port_info *, अचिन्हित दीर्घ);
व्योम ide_port_unरेजिस्टर_devices(ide_hwअगर_t *);
व्योम ide_port_scan(ide_hwअगर_t *);

अटल अंतरभूत व्योम *ide_get_hwअगरdata (ide_hwअगर_t * hwअगर)
अणु
	वापस hwअगर->hwअगर_data;
पूर्ण

अटल अंतरभूत व्योम ide_set_hwअगरdata (ide_hwअगर_t * hwअगर, व्योम *data)
अणु
	hwअगर->hwअगर_data = data;
पूर्ण

u64 ide_get_lba_addr(काष्ठा ide_cmd *, पूर्णांक);
u8 ide_dump_status(ide_drive_t *, स्थिर अक्षर *, u8);

काष्ठा ide_timing अणु
	u8  mode;
	u8  setup;	/* t1 */
	u16 act8b;	/* t2 क्रम 8-bit io */
	u16 rec8b;	/* t2i क्रम 8-bit io */
	u16 cyc8b;	/* t0 क्रम 8-bit io */
	u16 active;	/* t2 or tD */
	u16 recover;	/* t2i or tK */
	u16 cycle;	/* t0 */
	u16 udma;	/* t2CYCTYP/2 */
पूर्ण;

क्रमागत अणु
	IDE_TIMING_SETUP	= BIT(0),
	IDE_TIMING_ACT8B	= BIT(1),
	IDE_TIMING_REC8B	= BIT(2),
	IDE_TIMING_CYC8B	= BIT(3),
	IDE_TIMING_8BIT		= IDE_TIMING_ACT8B | IDE_TIMING_REC8B |
				  IDE_TIMING_CYC8B,
	IDE_TIMING_ACTIVE	= BIT(4),
	IDE_TIMING_RECOVER	= BIT(5),
	IDE_TIMING_CYCLE	= BIT(6),
	IDE_TIMING_UDMA		= BIT(7),
	IDE_TIMING_ALL		= IDE_TIMING_SETUP | IDE_TIMING_8BIT |
				  IDE_TIMING_ACTIVE | IDE_TIMING_RECOVER |
				  IDE_TIMING_CYCLE | IDE_TIMING_UDMA,
पूर्ण;

काष्ठा ide_timing *ide_timing_find_mode(u8);
u16 ide_pio_cycle_समय(ide_drive_t *, u8);
व्योम ide_timing_merge(काष्ठा ide_timing *, काष्ठा ide_timing *,
		      काष्ठा ide_timing *, अचिन्हित पूर्णांक);
पूर्णांक ide_timing_compute(ide_drive_t *, u8, काष्ठा ide_timing *, पूर्णांक, पूर्णांक);

#अगर_घोषित CONFIG_IDE_XFER_MODE
पूर्णांक ide_scan_pio_blacklist(अक्षर *);
स्थिर अक्षर *ide_xfer_verbose(u8);
पूर्णांक ide_pio_need_iordy(ide_drive_t *, स्थिर u8);
पूर्णांक ide_set_pio_mode(ide_drive_t *, u8);
पूर्णांक ide_set_dma_mode(ide_drive_t *, u8);
व्योम ide_set_pio(ide_drive_t *, u8);
पूर्णांक ide_set_xfer_rate(ide_drive_t *, u8);
#अन्यथा
अटल अंतरभूत व्योम ide_set_pio(ide_drive_t *drive, u8 pio) अणु ; पूर्ण
अटल अंतरभूत पूर्णांक ide_set_xfer_rate(ide_drive_t *drive, u8 rate) अणु वापस -1; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ide_set_max_pio(ide_drive_t *drive)
अणु
	ide_set_pio(drive, 255);
पूर्ण

अक्षर *ide_media_string(ide_drive_t *);

बाह्य स्थिर काष्ठा attribute_group *ide_dev_groups[];
बाह्य काष्ठा bus_type ide_bus_type;
बाह्य काष्ठा class *ide_port_class;

अटल अंतरभूत व्योम ide_dump_identअगरy(u8 *id)
अणु
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 2, id, 512, 0);
पूर्ण

अटल अंतरभूत पूर्णांक hwअगर_to_node(ide_hwअगर_t *hwअगर)
अणु
	वापस hwअगर->dev ? dev_to_node(hwअगर->dev) : -1;
पूर्ण

अटल अंतरभूत ide_drive_t *ide_get_pair_dev(ide_drive_t *drive)
अणु
	ide_drive_t *peer = drive->hwअगर->devices[(drive->dn ^ 1) & 1];

	वापस (peer->dev_flags & IDE_DFLAG_PRESENT) ? peer : शून्य;
पूर्ण

अटल अंतरभूत व्योम *ide_get_drivedata(ide_drive_t *drive)
अणु
	वापस drive->drive_data;
पूर्ण

अटल अंतरभूत व्योम ide_set_drivedata(ide_drive_t *drive, व्योम *data)
अणु
	drive->drive_data = data;
पूर्ण

#घोषणा ide_port_क्रम_each_dev(i, dev, port) \
	क्रम ((i) = 0; ((dev) = (port)->devices[i]) || (i) < MAX_DRIVES; (i)++)

#घोषणा ide_port_क्रम_each_present_dev(i, dev, port) \
	क्रम ((i) = 0; ((dev) = (port)->devices[i]) || (i) < MAX_DRIVES; (i)++) \
		अगर ((dev)->dev_flags & IDE_DFLAG_PRESENT)

#घोषणा ide_host_क्रम_each_port(i, port, host) \
	क्रम ((i) = 0; ((port) = (host)->ports[i]) || (i) < MAX_HOST_PORTS; (i)++)


#पूर्ण_अगर /* _IDE_H */
