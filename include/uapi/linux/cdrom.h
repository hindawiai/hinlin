<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * -- <linux/cdrom.h>
 * General header file क्रम linux CD-ROM drivers 
 * Copyright (C) 1992         David Giller, rafeपंचांगad@oxy.edu
 *               1994, 1995   Eberhard Mथघnkeberg, emoenke@gwdg.de
 *               1996         David van Leeuwen, david@पंचांग.tno.nl
 *               1997, 1998   Erik Andersen, andersee@debian.org
 *               1998-2002    Jens Axboe, axboe@suse.de
 */
 
#अगर_अघोषित _UAPI_LINUX_CDROM_H
#घोषणा _UAPI_LINUX_CDROM_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/*******************************************************
 * As of Linux 2.1.x, all Linux CD-ROM application programs will use this 
 * (and only this) include file.  It is my hope to provide Linux with
 * a unअगरorm पूर्णांकerface between software accessing CD-ROMs and the various 
 * device drivers that actually talk to the drives.  There may still be
 * 23 dअगरferent kinds of strange CD-ROM drives, but at least there will 
 * now be one, and only one, Linux CD-ROM पूर्णांकerface.
 *
 * Additionally, as of Linux 2.1.x, all Linux application programs 
 * should use the O_NONBLOCK option when खोलोing a CD-ROM device 
 * क्रम subsequent ioctl commands.  This allows क्रम neat प्रणाली errors 
 * like "No medium found" or "Wrong medium type" upon attempting to 
 * mount or play an empty slot, mount an audio disc, or play a data disc.
 * Generally, changing an application program to support O_NONBLOCK
 * is as easy as the following:
 *       -    drive = खोलो("/dev/cdrom", O_RDONLY);
 *       +    drive = खोलो("/dev/cdrom", O_RDONLY | O_NONBLOCK);
 * It is worth the small change.
 *
 *  Patches क्रम many common CD programs (provided by David A. van Leeuwen)
 *  can be found at:  ftp://ftp.gwdg.de/pub/linux/cdrom/drivers/cm206/
 * 
 *******************************************************/

/* When a driver supports a certain function, but the cdrom drive we are 
 * using करोesn't, we will वापस the error EDRIVE_CANT_DO_THIS.  We will 
 * borrow the "Operation not supported" error from the network folks to 
 * accomplish this.  Maybe someday we will get a more targeted error code, 
 * but this will करो क्रम now... */
#घोषणा EDRIVE_CANT_DO_THIS  EOPNOTSUPP

/*******************************************************
 * The CD-ROM IOCTL commands  -- these should be supported by 
 * all the various cdrom drivers.  For the CD-ROM ioctls, we 
 * will commandeer byte 0x53, or 'S'.
 *******************************************************/
#घोषणा CDROMPAUSE		0x5301 /* Pause Audio Operation */ 
#घोषणा CDROMRESUME		0x5302 /* Resume छोड़ोd Audio Operation */
#घोषणा CDROMPLAYMSF		0x5303 /* Play Audio MSF (काष्ठा cdrom_msf) */
#घोषणा CDROMPLAYTRKIND		0x5304 /* Play Audio Track/index 
                                           (काष्ठा cdrom_ti) */
#घोषणा CDROMREADTOCHDR		0x5305 /* Read TOC header 
                                           (काष्ठा cdrom_tochdr) */
#घोषणा CDROMREADTOCENTRY	0x5306 /* Read TOC entry 
                                           (काष्ठा cdrom_tocentry) */
#घोषणा CDROMSTOP		0x5307 /* Stop the cdrom drive */
#घोषणा CDROMSTART		0x5308 /* Start the cdrom drive */
#घोषणा CDROMEJECT		0x5309 /* Ejects the cdrom media */
#घोषणा CDROMVOLCTRL		0x530a /* Control output volume 
                                           (काष्ठा cdrom_volctrl) */
#घोषणा CDROMSUBCHNL		0x530b /* Read subchannel data 
                                           (काष्ठा cdrom_subchnl) */
#घोषणा CDROMREADMODE2		0x530c /* Read CDROM mode 2 data (2336 Bytes) 
                                           (काष्ठा cdrom_पढ़ो) */
#घोषणा CDROMREADMODE1		0x530d /* Read CDROM mode 1 data (2048 Bytes)
                                           (काष्ठा cdrom_पढ़ो) */
#घोषणा CDROMREADAUDIO		0x530e /* (काष्ठा cdrom_पढ़ो_audio) */
#घोषणा CDROMEJECT_SW		0x530f /* enable(1)/disable(0) स्वतः-ejecting */
#घोषणा CDROMMULTISESSION	0x5310 /* Obtain the start-of-last-session 
                                           address of multi session disks 
                                           (काष्ठा cdrom_multisession) */
#घोषणा CDROM_GET_MCN		0x5311 /* Obtain the "Universal Product Code" 
                                           अगर available (काष्ठा cdrom_mcn) */
#घोषणा CDROM_GET_UPC		CDROM_GET_MCN  /* This one is deprecated, 
                                          but here anyway क्रम compatibility */
#घोषणा CDROMRESET		0x5312 /* hard-reset the drive */
#घोषणा CDROMVOLREAD		0x5313 /* Get the drive's volume setting 
                                          (काष्ठा cdrom_volctrl) */
#घोषणा CDROMREADRAW		0x5314	/* पढ़ो data in raw mode (2352 Bytes)
                                           (काष्ठा cdrom_पढ़ो) */
/* 
 * These ioctls are used only used in aztcd.c and optcd.c
 */
#घोषणा CDROMREADCOOKED		0x5315	/* पढ़ो data in cooked mode */
#घोषणा CDROMSEEK		0x5316  /* seek msf address */
  
/*
 * This ioctl is only used by the scsi-cd driver.  
   It is क्रम playing audio in logical block addressing mode.
 */
#घोषणा CDROMPLAYBLK		0x5317	/* (काष्ठा cdrom_blk) */

/* 
 * These ioctls are only used in optcd.c
 */
#घोषणा CDROMREADALL		0x5318	/* पढ़ो all 2646 bytes */

/* 
 * These ioctls are (now) only in ide-cd.c क्रम controlling 
 * drive spinकरोwn समय.  They should be implemented in the
 * Unअगरorm driver, via generic packet commands, GPCMD_MODE_SELECT_10,
 * GPCMD_MODE_SENSE_10 and the GPMODE_POWER_PAGE...
 *  -Erik
 */
#घोषणा CDROMGETSPINDOWN        0x531d
#घोषणा CDROMSETSPINDOWN        0x531e

/* 
 * These ioctls are implemented through the unअगरorm CD-ROM driver
 * They _will_ be aकरोpted by all CD-ROM drivers, when all the CD-ROM
 * drivers are eventually ported to the unअगरorm CD-ROM driver पूर्णांकerface.
 */
#घोषणा CDROMCLOSETRAY		0x5319	/* pendant of CDROMEJECT */
#घोषणा CDROM_SET_OPTIONS	0x5320  /* Set behavior options */
#घोषणा CDROM_CLEAR_OPTIONS	0x5321  /* Clear behavior options */
#घोषणा CDROM_SELECT_SPEED	0x5322  /* Set the CD-ROM speed */
#घोषणा CDROM_SELECT_DISC	0x5323  /* Select disc (क्रम juke-boxes) */
#घोषणा CDROM_MEDIA_CHANGED	0x5325  /* Check is media changed  */
#घोषणा CDROM_DRIVE_STATUS	0x5326  /* Get tray position, etc. */
#घोषणा CDROM_DISC_STATUS	0x5327  /* Get disc type, etc. */
#घोषणा CDROM_CHANGER_NSLOTS    0x5328  /* Get number of slots */
#घोषणा CDROM_LOCKDOOR		0x5329  /* lock or unlock करोor */
#घोषणा CDROM_DEBUG		0x5330	/* Turn debug messages on/off */
#घोषणा CDROM_GET_CAPABILITY	0x5331	/* get capabilities */

/* Note that scsi/scsi_ioctl.h also uses 0x5382 - 0x5386.
 * Future CDROM ioctls should be kept below 0x537F
 */

/* This ioctl is only used by sbpcd at the moment */
#घोषणा CDROMAUDIOबफ_मान        0x5382	/* set the audio buffer size */
					/* conflict with SCSI_IOCTL_GET_IDLUN */

/* DVD-ROM Specअगरic ioctls */
#घोषणा DVD_READ_STRUCT		0x5390  /* Read काष्ठाure */
#घोषणा DVD_WRITE_STRUCT	0x5391  /* Write काष्ठाure */
#घोषणा DVD_AUTH		0x5392  /* Authentication */

#घोषणा CDROM_SEND_PACKET	0x5393	/* send a packet to the drive */
#घोषणा CDROM_NEXT_WRITABLE	0x5394	/* get next writable block */
#घोषणा CDROM_LAST_WRITTEN	0x5395	/* get last block written on disc */

/*******************************************************
 * CDROM IOCTL काष्ठाures
 *******************************************************/

/* Address in MSF क्रमmat */
काष्ठा cdrom_msf0		
अणु
	__u8	minute;
	__u8	second;
	__u8	frame;
पूर्ण;

/* Address in either MSF or logical क्रमmat */
जोड़ cdrom_addr		
अणु
	काष्ठा cdrom_msf0	msf;
	पूर्णांक			lba;
पूर्ण;

/* This काष्ठा is used by the CDROMPLAYMSF ioctl */ 
काष्ठा cdrom_msf 
अणु
	__u8	cdmsf_min0;	/* start minute */
	__u8	cdmsf_sec0;	/* start second */
	__u8	cdmsf_frame0;	/* start frame */
	__u8	cdmsf_min1;	/* end minute */
	__u8	cdmsf_sec1;	/* end second */
	__u8	cdmsf_frame1;	/* end frame */
पूर्ण;

/* This काष्ठा is used by the CDROMPLAYTRKIND ioctl */
काष्ठा cdrom_ti 
अणु
	__u8	cdti_trk0;	/* start track */
	__u8	cdti_ind0;	/* start index */
	__u8	cdti_trk1;	/* end track */
	__u8	cdti_ind1;	/* end index */
पूर्ण;

/* This काष्ठा is used by the CDROMREADTOCHDR ioctl */
काष्ठा cdrom_tochdr 	
अणु
	__u8	cdth_trk0;	/* start track */
	__u8	cdth_trk1;	/* end track */
पूर्ण;

/* This काष्ठा is used by the CDROMVOLCTRL and CDROMVOLREAD ioctls */
काष्ठा cdrom_volctrl
अणु
	__u8	channel0;
	__u8	channel1;
	__u8	channel2;
	__u8	channel3;
पूर्ण;

/* This काष्ठा is used by the CDROMSUBCHNL ioctl */
काष्ठा cdrom_subchnl 
अणु
	__u8	cdsc_क्रमmat;
	__u8	cdsc_audiostatus;
	__u8	cdsc_adr:	4;
	__u8	cdsc_ctrl:	4;
	__u8	cdsc_trk;
	__u8	cdsc_ind;
	जोड़ cdrom_addr cdsc_असलaddr;
	जोड़ cdrom_addr cdsc_reladdr;
पूर्ण;


/* This काष्ठा is used by the CDROMREADTOCENTRY ioctl */
काष्ठा cdrom_tocentry 
अणु
	__u8	cdte_track;
	__u8	cdte_adr	:4;
	__u8	cdte_ctrl	:4;
	__u8	cdte_क्रमmat;
	जोड़ cdrom_addr cdte_addr;
	__u8	cdte_datamode;
पूर्ण;

/* This काष्ठा is used by the CDROMREADMODE1, and CDROMREADMODE2 ioctls */
काष्ठा cdrom_पढ़ो      
अणु
	पूर्णांक	cdपढ़ो_lba;
	अक्षर 	*cdपढ़ो_bufaddr;
	पूर्णांक	cdपढ़ो_buflen;
पूर्ण;

/* This काष्ठा is used by the CDROMREADAUDIO ioctl */
काष्ठा cdrom_पढ़ो_audio
अणु
	जोड़ cdrom_addr addr; /* frame address */
	__u8 addr_क्रमmat;      /* CDROM_LBA or CDROM_MSF */
	पूर्णांक nframes;           /* number of 2352-byte-frames to पढ़ो at once */
	__u8 __user *buf;      /* frame buffer (size: nframes*2352 bytes) */
पूर्ण;

/* This काष्ठा is used with the CDROMMULTISESSION ioctl */
काष्ठा cdrom_multisession
अणु
	जोड़ cdrom_addr addr; /* frame address: start-of-last-session 
	                           (not the new "frame 16"!).  Only valid
	                           अगर the "xa_flag" is true. */
	__u8 xa_flag;        /* 1: "is XA disk" */
	__u8 addr_क्रमmat;    /* CDROM_LBA or CDROM_MSF */
पूर्ण;

/* This काष्ठा is used with the CDROM_GET_MCN ioctl.  
 * Very few audio discs actually have Universal Product Code inक्रमmation, 
 * which should just be the Medium Catalog Number on the box.  Also note 
 * that the way the codeis written on CD is _not_ unअगरorm across all discs!
 */  
काष्ठा cdrom_mcn 
अणु
  __u8 medium_catalog_number[14]; /* 13 ASCII digits, null-terminated */
पूर्ण;

/* This is used by the CDROMPLAYBLK ioctl */
काष्ठा cdrom_blk 
अणु
	अचिन्हित from;
	अचिन्हित लघु len;
पूर्ण;

#घोषणा CDROM_PACKET_SIZE	12

#घोषणा CGC_DATA_UNKNOWN	0
#घोषणा CGC_DATA_WRITE		1
#घोषणा CGC_DATA_READ		2
#घोषणा CGC_DATA_NONE		3

/* क्रम CDROM_PACKET_COMMAND ioctl */
काष्ठा cdrom_generic_command
अणु
	अचिन्हित अक्षर 		cmd[CDROM_PACKET_SIZE];
	अचिन्हित अक्षर		__user *buffer;
	अचिन्हित पूर्णांक 		buflen;
	पूर्णांक			stat;
	काष्ठा request_sense	__user *sense;
	अचिन्हित अक्षर		data_direction;
	पूर्णांक			quiet;
	पूर्णांक			समयout;
	जोड़ अणु
		व्योम		__user *reserved[1];	/* unused, actually */
		व्योम            __user *unused;
	पूर्ण;
पूर्ण;

/*
 * A CD-ROM physical sector size is 2048, 2052, 2056, 2324, 2332, 2336, 
 * 2340, or 2352 bytes दीर्घ.  

*         Sector types of the standard CD-ROM data क्रमmats:
 *
 * क्रमmat   sector type               user data size (bytes)
 * -----------------------------------------------------------------------------
 *   1     (Red Book)    CD-DA          2352    (CD_FRAMESIZE_RAW)
 *   2     (Yellow Book) Mode1 Form1    2048    (CD_FRAMESIZE)
 *   3     (Yellow Book) Mode1 Form2    2336    (CD_FRAMESIZE_RAW0)
 *   4     (Green Book)  Mode2 Form1    2048    (CD_FRAMESIZE)
 *   5     (Green Book)  Mode2 Form2    2328    (2324+4 spare bytes)
 *
 *
 *       The layout of the standard CD-ROM data क्रमmats:
 * -----------------------------------------------------------------------------
 * - audio (red):                  | audio_sample_bytes |
 *                                 |        2352        |
 *
 * - data (yellow, mode1):         | sync - head - data - EDC - zero - ECC |
 *                                 |  12  -   4  - 2048 -  4  -   8  - 276 |
 *
 * - data (yellow, mode2):         | sync - head - data |
 *                                 |  12  -   4  - 2336 |
 *
 * - XA data (green, mode2 क्रमm1): | sync - head - sub - data - EDC - ECC |
 *                                 |  12  -   4  -  8  - 2048 -  4  - 276 |
 *
 * - XA data (green, mode2 क्रमm2): | sync - head - sub - data - Spare |
 *                                 |  12  -   4  -  8  - 2324 -  4    |
 *
 */

/* Some generally useful CD-ROM inक्रमmation -- mostly based on the above */
#घोषणा CD_MINS              74 /* max. minutes per CD, not really a limit */
#घोषणा CD_SECS              60 /* seconds per minute */
#घोषणा CD_FRAMES            75 /* frames per second */
#घोषणा CD_SYNC_SIZE         12 /* 12 sync bytes per raw data frame */
#घोषणा CD_MSF_OFFSET       150 /* MSF numbering offset of first frame */
#घोषणा CD_CHUNK_SIZE        24 /* lowest-level "data bytes piece" */
#घोषणा CD_NUM_OF_CHUNKS     98 /* chunks per frame */
#घोषणा CD_FRAMESIZE_SUB     96 /* subchannel data "frame" size */
#घोषणा CD_HEAD_SIZE          4 /* header (address) bytes per raw data frame */
#घोषणा CD_SUBHEAD_SIZE       8 /* subheader bytes per raw XA data frame */
#घोषणा CD_EDC_SIZE           4 /* bytes EDC per most raw data frame types */
#घोषणा CD_ZERO_SIZE          8 /* bytes zero per yellow book mode 1 frame */
#घोषणा CD_ECC_SIZE         276 /* bytes ECC per most raw data frame types */
#घोषणा CD_FRAMESIZE       2048 /* bytes per frame, "cooked" mode */
#घोषणा CD_FRAMESIZE_RAW   2352 /* bytes per frame, "raw" mode */
#घोषणा CD_FRAMESIZE_RAWER 2646 /* The maximum possible वापसed bytes */ 
/* most drives करोn't deliver everything: */
#घोषणा CD_FRAMESIZE_RAW1 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE) /*2340*/
#घोषणा CD_FRAMESIZE_RAW0 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE-CD_HEAD_SIZE) /*2336*/

#घोषणा CD_XA_HEAD        (CD_HEAD_SIZE+CD_SUBHEAD_SIZE) /* "before data" part of raw XA frame */
#घोषणा CD_XA_TAIL        (CD_EDC_SIZE+CD_ECC_SIZE) /* "after data" part of raw XA frame */
#घोषणा CD_XA_SYNC_HEAD   (CD_SYNC_SIZE+CD_XA_HEAD) /* sync bytes + header of XA frame */

/* CD-ROM address types (cdrom_tocentry.cdte_क्रमmat) */
#घोषणा	CDROM_LBA 0x01 /* "logical block": first frame is #0 */
#घोषणा	CDROM_MSF 0x02 /* "minute-second-frame": binary, not bcd here! */

/* bit to tell whether track is data or audio (cdrom_tocentry.cdte_ctrl) */
#घोषणा	CDROM_DATA_TRACK	0x04

/* The leaकरोut track is always 0xAA, regardless of # of tracks on disc */
#घोषणा	CDROM_LEADOUT		0xAA

/* audio states (from SCSI-2, but seen with other drives, too) */
#घोषणा	CDROM_AUDIO_INVALID	0x00	/* audio status not supported */
#घोषणा	CDROM_AUDIO_PLAY	0x11	/* audio play operation in progress */
#घोषणा	CDROM_AUDIO_PAUSED	0x12	/* audio play operation छोड़ोd */
#घोषणा	CDROM_AUDIO_COMPLETED	0x13	/* audio play successfully completed */
#घोषणा	CDROM_AUDIO_ERROR	0x14	/* audio play stopped due to error */
#घोषणा	CDROM_AUDIO_NO_STATUS	0x15	/* no current audio status to वापस */

/* capability flags used with the unअगरorm CD-ROM driver */ 
#घोषणा CDC_CLOSE_TRAY		0x1     /* caddy प्रणालीs _can't_ बंद */
#घोषणा CDC_OPEN_TRAY		0x2     /* but _can_ eject.  */
#घोषणा CDC_LOCK		0x4     /* disable manual eject */
#घोषणा CDC_SELECT_SPEED 	0x8     /* programmable speed */
#घोषणा CDC_SELECT_DISC		0x10    /* select disc from juke-box */
#घोषणा CDC_MULTI_SESSION 	0x20    /* पढ़ो sessions>1 */
#घोषणा CDC_MCN			0x40    /* Medium Catalog Number */
#घोषणा CDC_MEDIA_CHANGED 	0x80    /* media changed */
#घोषणा CDC_PLAY_AUDIO		0x100   /* audio functions */
#घोषणा CDC_RESET               0x200   /* hard reset device */
#घोषणा CDC_DRIVE_STATUS        0x800   /* driver implements drive status */
#घोषणा CDC_GENERIC_PACKET	0x1000	/* driver implements generic packets */
#घोषणा CDC_CD_R		0x2000	/* drive is a CD-R */
#घोषणा CDC_CD_RW		0x4000	/* drive is a CD-RW */
#घोषणा CDC_DVD			0x8000	/* drive is a DVD */
#घोषणा CDC_DVD_R		0x10000	/* drive can ग_लिखो DVD-R */
#घोषणा CDC_DVD_RAM		0x20000	/* drive can ग_लिखो DVD-RAM */
#घोषणा CDC_MO_DRIVE		0x40000 /* drive is an MO device */
#घोषणा CDC_MRW			0x80000 /* drive can पढ़ो MRW */
#घोषणा CDC_MRW_W		0x100000 /* drive can ग_लिखो MRW */
#घोषणा CDC_RAM			0x200000 /* ok to खोलो क्रम WRITE */

/* drive status possibilities वापसed by CDROM_DRIVE_STATUS ioctl */
#घोषणा CDS_NO_INFO		0	/* अगर not implemented */
#घोषणा CDS_NO_DISC		1
#घोषणा CDS_TRAY_OPEN		2
#घोषणा CDS_DRIVE_NOT_READY	3
#घोषणा CDS_DISC_OK		4

/* वापस values क्रम the CDROM_DISC_STATUS ioctl */
/* can also वापस CDS_NO_[INFO|DISC], from above */
#घोषणा CDS_AUDIO		100
#घोषणा CDS_DATA_1		101
#घोषणा CDS_DATA_2		102
#घोषणा CDS_XA_2_1		103
#घोषणा CDS_XA_2_2		104
#घोषणा CDS_MIXED		105

/* User-configurable behavior options क्रम the unअगरorm CD-ROM driver */
#घोषणा CDO_AUTO_CLOSE		0x1     /* बंद tray on first खोलो() */
#घोषणा CDO_AUTO_EJECT		0x2     /* खोलो tray on last release() */
#घोषणा CDO_USE_FFLAGS		0x4     /* use O_NONBLOCK inक्रमmation on खोलो */
#घोषणा CDO_LOCK		0x8     /* lock tray on खोलो files */
#घोषणा CDO_CHECK_TYPE		0x10    /* check type on खोलो क्रम data */

/* Special codes used when specअगरying changer slots. */
#घोषणा CDSL_NONE       	(पूर्णांक_उच्च-1)
#घोषणा CDSL_CURRENT    	पूर्णांक_उच्च

/* For partition based multisession access. IDE can handle 64 partitions
 * per drive - SCSI CD-ROM's use minors to dअगरferentiate between the
 * various drives, so we can't करो multisessions the same way there.
 * Use the -o session=x option to mount on them.
 */
#घोषणा CD_PART_MAX		64
#घोषणा CD_PART_MASK		(CD_PART_MAX - 1)

/*********************************************************************
 * Generic Packet commands, MMC commands, and such
 *********************************************************************/

 /* The generic packet command opcodes क्रम CD/DVD Logical Units,
 * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
#घोषणा GPCMD_BLANK			    0xa1
#घोषणा GPCMD_CLOSE_TRACK		    0x5b
#घोषणा GPCMD_FLUSH_CACHE		    0x35
#घोषणा GPCMD_FORMAT_UNIT		    0x04
#घोषणा GPCMD_GET_CONFIGURATION		    0x46
#घोषणा GPCMD_GET_EVENT_STATUS_NOTIFICATION 0x4a
#घोषणा GPCMD_GET_PERFORMANCE		    0xac
#घोषणा GPCMD_INQUIRY			    0x12
#घोषणा GPCMD_LOAD_UNLOAD		    0xa6
#घोषणा GPCMD_MECHANISM_STATUS		    0xbd
#घोषणा GPCMD_MODE_SELECT_10		    0x55
#घोषणा GPCMD_MODE_SENSE_10		    0x5a
#घोषणा GPCMD_PAUSE_RESUME		    0x4b
#घोषणा GPCMD_PLAY_AUDIO_10		    0x45
#घोषणा GPCMD_PLAY_AUDIO_MSF		    0x47
#घोषणा GPCMD_PLAY_AUDIO_TI		    0x48
#घोषणा GPCMD_PLAY_CD			    0xbc
#घोषणा GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL  0x1e
#घोषणा GPCMD_READ_10			    0x28
#घोषणा GPCMD_READ_12			    0xa8
#घोषणा GPCMD_READ_BUFFER		    0x3c
#घोषणा GPCMD_READ_BUFFER_CAPACITY	    0x5c
#घोषणा GPCMD_READ_CDVD_CAPACITY	    0x25
#घोषणा GPCMD_READ_CD			    0xbe
#घोषणा GPCMD_READ_CD_MSF		    0xb9
#घोषणा GPCMD_READ_DISC_INFO		    0x51
#घोषणा GPCMD_READ_DVD_STRUCTURE	    0xad
#घोषणा GPCMD_READ_FORMAT_CAPACITIES	    0x23
#घोषणा GPCMD_READ_HEADER		    0x44
#घोषणा GPCMD_READ_TRACK_RZONE_INFO	    0x52
#घोषणा GPCMD_READ_SUBCHANNEL		    0x42
#घोषणा GPCMD_READ_TOC_PMA_ATIP		    0x43
#घोषणा GPCMD_REPAIR_RZONE_TRACK	    0x58
#घोषणा GPCMD_REPORT_KEY		    0xa4
#घोषणा GPCMD_REQUEST_SENSE		    0x03
#घोषणा GPCMD_RESERVE_RZONE_TRACK	    0x53
#घोषणा GPCMD_SEND_CUE_SHEET		    0x5d
#घोषणा GPCMD_SCAN			    0xba
#घोषणा GPCMD_SEEK			    0x2b
#घोषणा GPCMD_SEND_DVD_STRUCTURE	    0xbf
#घोषणा GPCMD_SEND_EVENT		    0xa2
#घोषणा GPCMD_SEND_KEY			    0xa3
#घोषणा GPCMD_SEND_OPC			    0x54
#घोषणा GPCMD_SET_READ_AHEAD		    0xa7
#घोषणा GPCMD_SET_STREAMING		    0xb6
#घोषणा GPCMD_START_STOP_UNIT		    0x1b
#घोषणा GPCMD_STOP_PLAY_SCAN		    0x4e
#घोषणा GPCMD_TEST_UNIT_READY		    0x00
#घोषणा GPCMD_VERIFY_10			    0x2f
#घोषणा GPCMD_WRITE_10			    0x2a
#घोषणा GPCMD_WRITE_12			    0xaa
#घोषणा GPCMD_WRITE_AND_VERIFY_10	    0x2e
#घोषणा GPCMD_WRITE_BUFFER		    0x3b
/* This is listed as optional in ATAPI 2.6, but is (curiously) 
 * missing from Mt. Fuji, Table 57.  It _is_ mentioned in Mt. Fuji
 * Table 377 as an MMC command क्रम SCSi devices though...  Most ATAPI
 * drives support it. */
#घोषणा GPCMD_SET_SPEED			    0xbb
/* This seems to be a SCSI specअगरic CD-ROM opcode 
 * to play data at track/index */
#घोषणा GPCMD_PLAYAUDIO_TI		    0x48
/*
 * From MS Media Status Notअगरication Support Specअगरication. For
 * older drives only.
 */
#घोषणा GPCMD_GET_MEDIA_STATUS		    0xda

/* Mode page codes क्रम mode sense/set */
#घोषणा GPMODE_VENDOR_PAGE		0x00
#घोषणा GPMODE_R_W_ERROR_PAGE		0x01
#घोषणा GPMODE_WRITE_PARMS_PAGE		0x05
#घोषणा GPMODE_WCACHING_PAGE		0x08
#घोषणा GPMODE_AUDIO_CTL_PAGE		0x0e
#घोषणा GPMODE_POWER_PAGE		0x1a
#घोषणा GPMODE_FAULT_FAIL_PAGE		0x1c
#घोषणा GPMODE_TO_PROTECT_PAGE		0x1d
#घोषणा GPMODE_CAPABILITIES_PAGE	0x2a
#घोषणा GPMODE_ALL_PAGES		0x3f
/* Not in Mt. Fuji, but in ATAPI 2.6 -- deprecated now in favor
 * of MODE_SENSE_POWER_PAGE */
#घोषणा GPMODE_CDROM_PAGE		0x0d



/* DVD काष्ठा types */
#घोषणा DVD_STRUCT_PHYSICAL	0x00
#घोषणा DVD_STRUCT_COPYRIGHT	0x01
#घोषणा DVD_STRUCT_DISCKEY	0x02
#घोषणा DVD_STRUCT_BCA		0x03
#घोषणा DVD_STRUCT_MANUFACT	0x04

काष्ठा dvd_layer अणु
	__u8 book_version	: 4;
	__u8 book_type		: 4;
	__u8 min_rate		: 4;
	__u8 disc_size		: 4;
	__u8 layer_type		: 4;
	__u8 track_path		: 1;
	__u8 nlayers		: 2;
	__u8 track_density	: 4;
	__u8 linear_density	: 4;
	__u8 bca		: 1;
	__u32 start_sector;
	__u32 end_sector;
	__u32 end_sector_l0;
पूर्ण;

#घोषणा DVD_LAYERS	4

काष्ठा dvd_physical अणु
	__u8 type;
	__u8 layer_num;
	काष्ठा dvd_layer layer[DVD_LAYERS];
पूर्ण;

काष्ठा dvd_copyright अणु
	__u8 type;

	__u8 layer_num;
	__u8 cpst;
	__u8 rmi;
पूर्ण;

काष्ठा dvd_disckey अणु
	__u8 type;

	अचिन्हित agid		: 2;
	__u8 value[2048];
पूर्ण;

काष्ठा dvd_bca अणु
	__u8 type;

	पूर्णांक len;
	__u8 value[188];
पूर्ण;

काष्ठा dvd_manufact अणु
	__u8 type;

	__u8 layer_num;
	पूर्णांक len;
	__u8 value[2048];
पूर्ण;

प्रकार जोड़ अणु
	__u8 type;

	काष्ठा dvd_physical	physical;
	काष्ठा dvd_copyright	copyright;
	काष्ठा dvd_disckey	disckey;
	काष्ठा dvd_bca		bca;
	काष्ठा dvd_manufact	manufact;
पूर्ण dvd_काष्ठा;

/*
 * DVD authentication ioctl
 */

/* Authentication states */
#घोषणा DVD_LU_SEND_AGID	0
#घोषणा DVD_HOST_SEND_CHALLENGE	1
#घोषणा DVD_LU_SEND_KEY1	2
#घोषणा DVD_LU_SEND_CHALLENGE	3
#घोषणा DVD_HOST_SEND_KEY2	4

/* Termination states */
#घोषणा DVD_AUTH_ESTABLISHED	5
#घोषणा DVD_AUTH_FAILURE	6

/* Other functions */
#घोषणा DVD_LU_SEND_TITLE_KEY	7
#घोषणा DVD_LU_SEND_ASF		8
#घोषणा DVD_INVALIDATE_AGID	9
#घोषणा DVD_LU_SEND_RPC_STATE	10
#घोषणा DVD_HOST_SEND_RPC_STATE	11

/* State data */
प्रकार __u8 dvd_key[5];		/* 40-bit value, MSB is first elem. */
प्रकार __u8 dvd_challenge[10];	/* 80-bit value, MSB is first elem. */

काष्ठा dvd_lu_send_agid अणु
	__u8 type;
	अचिन्हित agid		: 2;
पूर्ण;

काष्ठा dvd_host_send_challenge अणु
	__u8 type;
	अचिन्हित agid		: 2;

	dvd_challenge chal;
पूर्ण;

काष्ठा dvd_send_key अणु
	__u8 type;
	अचिन्हित agid		: 2;

	dvd_key key;
पूर्ण;

काष्ठा dvd_lu_send_challenge अणु
	__u8 type;
	अचिन्हित agid		: 2;

	dvd_challenge chal;
पूर्ण;

#घोषणा DVD_CPM_NO_COPYRIGHT	0
#घोषणा DVD_CPM_COPYRIGHTED	1

#घोषणा DVD_CP_SEC_NONE		0
#घोषणा DVD_CP_SEC_EXIST	1

#घोषणा DVD_CGMS_UNRESTRICTED	0
#घोषणा DVD_CGMS_SINGLE		2
#घोषणा DVD_CGMS_RESTRICTED	3

काष्ठा dvd_lu_send_title_key अणु
	__u8 type;
	अचिन्हित agid		: 2;

	dvd_key title_key;
	पूर्णांक lba;
	अचिन्हित cpm		: 1;
	अचिन्हित cp_sec		: 1;
	अचिन्हित cgms		: 2;
पूर्ण;

काष्ठा dvd_lu_send_asf अणु
	__u8 type;
	अचिन्हित agid		: 2;

	अचिन्हित asf		: 1;
पूर्ण;

काष्ठा dvd_host_send_rpcstate अणु
	__u8 type;
	__u8 pdrc;
पूर्ण;

काष्ठा dvd_lu_send_rpcstate अणु
	__u8 type		: 2;
	__u8 vra		: 3;
	__u8 ucca		: 3;
	__u8 region_mask;
	__u8 rpc_scheme;
पूर्ण;

प्रकार जोड़ अणु
	__u8 type;

	काष्ठा dvd_lu_send_agid		lsa;
	काष्ठा dvd_host_send_challenge	hsc;
	काष्ठा dvd_send_key		lsk;
	काष्ठा dvd_lu_send_challenge	lsc;
	काष्ठा dvd_send_key		hsk;
	काष्ठा dvd_lu_send_title_key	lstk;
	काष्ठा dvd_lu_send_asf		lsasf;
	काष्ठा dvd_host_send_rpcstate	hrpcs;
	काष्ठा dvd_lu_send_rpcstate	lrpcs;
पूर्ण dvd_authinfo;

काष्ठा request_sense अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 valid		: 1;
	__u8 error_code		: 7;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 error_code		: 7;
	__u8 valid		: 1;
#पूर्ण_अगर
	__u8 segment_number;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved1		: 2;
	__u8 ili		: 1;
	__u8 reserved2		: 1;
	__u8 sense_key		: 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 sense_key		: 4;
	__u8 reserved2		: 1;
	__u8 ili		: 1;
	__u8 reserved1		: 2;
#पूर्ण_अगर
	__u8 inक्रमmation[4];
	__u8 add_sense_len;
	__u8 command_info[4];
	__u8 asc;
	__u8 ascq;
	__u8 fruc;
	__u8 sks[3];
	__u8 asb[46];
पूर्ण;

/*
 * feature profile
 */
#घोषणा CDF_RWRT	0x0020	/* "Random Writable" */
#घोषणा CDF_HWDM	0x0024	/* "Hardware Defect Management" */
#घोषणा CDF_MRW 	0x0028

/*
 * media status bits
 */
#घोषणा CDM_MRW_NOTMRW			0
#घोषणा CDM_MRW_BGFORMAT_INACTIVE	1
#घोषणा CDM_MRW_BGFORMAT_ACTIVE		2
#घोषणा CDM_MRW_BGFORMAT_COMPLETE	3

/*
 * mrw address spaces
 */
#घोषणा MRW_LBA_DMA			0
#घोषणा MRW_LBA_GAA			1

/*
 * mrw mode pages (first is deprecated) -- probed at init समय and
 * cdi->mrw_mode_page is set
 */
#घोषणा MRW_MODE_PC_PRE1		0x2c
#घोषणा MRW_MODE_PC			0x03

काष्ठा mrw_feature_desc अणु
	__be16 feature_code;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved1		: 2;
	__u8 feature_version	: 4;
	__u8 persistent		: 1;
	__u8 curr		: 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 curr		: 1;
	__u8 persistent		: 1;
	__u8 feature_version	: 4;
	__u8 reserved1		: 2;
#पूर्ण_अगर
	__u8 add_len;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved2		: 7;
	__u8 ग_लिखो		: 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 ग_लिखो		: 1;
	__u8 reserved2		: 7;
#पूर्ण_अगर
	__u8 reserved3;
	__u8 reserved4;
	__u8 reserved5;
पूर्ण;

/* cf. mmc4r02g.pdf 5.3.10 Ranकरोm Writable Feature (0020h) pg 197 of 635 */
काष्ठा rwrt_feature_desc अणु
	__be16 feature_code;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved1		: 2;
	__u8 feature_version	: 4;
	__u8 persistent		: 1;
	__u8 curr		: 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 curr		: 1;
	__u8 persistent		: 1;
	__u8 feature_version	: 4;
	__u8 reserved1		: 2;
#पूर्ण_अगर
	__u8 add_len;
	__u32 last_lba;
	__u32 block_size;
	__u16 blocking;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved2		: 7;
	__u8 page_present	: 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 page_present	: 1;
	__u8 reserved2		: 7;
#पूर्ण_अगर
	__u8 reserved3;
पूर्ण;

प्रकार काष्ठा अणु
	__be16 disc_inक्रमmation_length;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved1			: 3;
        __u8 erasable			: 1;
        __u8 border_status		: 2;
        __u8 disc_status		: 2;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
        __u8 disc_status		: 2;
        __u8 border_status		: 2;
        __u8 erasable			: 1;
	__u8 reserved1			: 3;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8 n_first_track;
	__u8 n_sessions_lsb;
	__u8 first_track_lsb;
	__u8 last_track_lsb;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 did_v			: 1;
        __u8 dbc_v			: 1;
        __u8 uru			: 1;
        __u8 reserved2			: 2;
	__u8 dbit			: 1;
	__u8 mrw_status			: 2;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 mrw_status			: 2;
	__u8 dbit			: 1;
        __u8 reserved2			: 2;
        __u8 uru			: 1;
        __u8 dbc_v			: 1;
	__u8 did_v			: 1;
#पूर्ण_अगर
	__u8 disc_type;
	__u8 n_sessions_msb;
	__u8 first_track_msb;
	__u8 last_track_msb;
	__u32 disc_id;
	__u32 lead_in;
	__u32 lead_out;
	__u8 disc_bar_code[8];
	__u8 reserved3;
	__u8 n_opc;
पूर्ण disc_inक्रमmation;

प्रकार काष्ठा अणु
	__be16 track_inक्रमmation_length;
	__u8 track_lsb;
	__u8 session_lsb;
	__u8 reserved1;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved2			: 2;
        __u8 damage			: 1;
        __u8 copy			: 1;
        __u8 track_mode			: 4;
	__u8 rt				: 1;
	__u8 blank			: 1;
	__u8 packet			: 1;
	__u8 fp				: 1;
	__u8 data_mode			: 4;
	__u8 reserved3			: 6;
	__u8 lra_v			: 1;
	__u8 nwa_v			: 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
        __u8 track_mode			: 4;
        __u8 copy			: 1;
        __u8 damage			: 1;
	__u8 reserved2			: 2;
	__u8 data_mode			: 4;
	__u8 fp				: 1;
	__u8 packet			: 1;
	__u8 blank			: 1;
	__u8 rt				: 1;
	__u8 nwa_v			: 1;
	__u8 lra_v			: 1;
	__u8 reserved3			: 6;
#पूर्ण_अगर
	__be32 track_start;
	__be32 next_writable;
	__be32 मुक्त_blocks;
	__be32 fixed_packet_size;
	__be32 track_size;
	__be32 last_rec_address;
पूर्ण track_inक्रमmation;

काष्ठा feature_header अणु
	__u32 data_len;
	__u8 reserved1;
	__u8 reserved2;
	__u16 curr_profile;
पूर्ण;

काष्ठा mode_page_header अणु
	__be16 mode_data_length;
	__u8 medium_type;
	__u8 reserved1;
	__u8 reserved2;
	__u8 reserved3;
	__be16 desc_length;
पूर्ण;

/* removable medium feature descriptor */
काष्ठा rm_feature_desc अणु
	__be16 feature_code;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved1:2;
	__u8 feature_version:4;
	__u8 persistent:1;
	__u8 curr:1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 curr:1;
	__u8 persistent:1;
	__u8 feature_version:4;
	__u8 reserved1:2;
#पूर्ण_अगर
	__u8 add_len;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 mech_type:3;
	__u8 load:1;
	__u8 eject:1;
	__u8 pvnt_jmpr:1;
	__u8 dbml:1;
	__u8 lock:1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 lock:1;
	__u8 dbml:1;
	__u8 pvnt_jmpr:1;
	__u8 eject:1;
	__u8 load:1;
	__u8 mech_type:3;
#पूर्ण_अगर
	__u8 reserved2;
	__u8 reserved3;
	__u8 reserved4;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_CDROM_H */
