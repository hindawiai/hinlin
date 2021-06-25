<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/block/ataflop.c
 *
 *  Copyright (C) 1993  Greg Harp
 *  Atari Support by Bjoern Brauel, Roman Hodek
 *
 *  Big cleanup Sep 11..14 1994 Roman Hodek:
 *   - Driver now works पूर्णांकerrupt driven
 *   - Support क्रम two drives; should work, but I cannot test that :-(
 *   - Reading is करोne in whole tracks and buffered to speed up things
 *   - Disk change detection and drive deselecting after motor-off
 *     similar to TOS
 *   - Autodetection of disk क्रमmat (DD/HD); untested yet, because I
 *     करोn't have an HD drive :-(
 *
 *  Fixes Nov 13 1994 Martin Schaller:
 *   - Autodetection works now
 *   - Support क्रम 5 1/4'' disks
 *   - Removed drive type (unknown on atari)
 *   - Do seeks with 8 Mhz
 *
 *  Changes by Andreas Schwab:
 *   - After errors in multiple पढ़ो mode try again पढ़ोing single sectors
 *  (Feb 1995):
 *   - Clean up error handling
 *   - Set blk_size क्रम proper size checking
 *   - Initialize track रेजिस्टर when testing presence of floppy
 *   - Implement some ioctl's
 *
 *  Changes by Torsten Lang:
 *   - When probing the floppies we should add the FDCCMDADD_H flag since
 *     the FDC will otherwise रुको क्रमever when no disk is inserted...
 *
 * ++ Freddi Aschwanden (fa) 20.9.95 fixes क्रम medusa:
 *  - MFPDELAY() after each FDC access -> atari 
 *  - more/other disk क्रमmats
 *  - DMA to the block buffer directly अगर we have a 32bit DMA
 *  - क्रम medusa, the step rate is always 3ms
 *  - on medusa, use only cache_push()
 * Roman:
 *  - Make disk क्रमmat numbering independent from minors
 *  - Let user set max. supported drive type (speeds up क्रमmat
 *    detection, saves buffer space)
 *
 * Roman 10/15/95:
 *  - implement some more ioctls
 *  - disk क्रमmatting
 *  
 * Andreas 95/12/12:
 *  - increase gap size at start of track क्रम HD/ED disks
 *
 * Michael (MSch) 11/07/96:
 *  - implemented FDSETPRM and FDDEFPRM ioctl
 *
 * Andreas (97/03/19):
 *  - implemented missing BLK* ioctls
 *
 *  Things left to करो:
 *   - Formatting
 *   - Maybe a better strategy क्रम disk change detection (करोes anyone
 *     know one?)
 */

#समावेश <linux/module.h>

#समावेश <linux/fd.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/रुको.h>

#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stdma.h>
#समावेश <यंत्र/atari_stram.h>

#घोषणा	FD_MAX_UNITS 2

#अघोषित DEBUG

अटल DEFINE_MUTEX(ataflop_mutex);
अटल काष्ठा request *fd_request;

/*
 * WD1772 stuff
 */

/* रेजिस्टर codes */

#घोषणा FDCSELREG_STP   (0x80)   /* command/status रेजिस्टर */
#घोषणा FDCSELREG_TRA   (0x82)   /* track रेजिस्टर */
#घोषणा FDCSELREG_SEC   (0x84)   /* sector रेजिस्टर */
#घोषणा FDCSELREG_DTA   (0x86)   /* data रेजिस्टर */

/* रेजिस्टर names क्रम FDC_READ/WRITE macros */

#घोषणा FDCREG_CMD		0
#घोषणा FDCREG_STATUS	0
#घोषणा FDCREG_TRACK	2
#घोषणा FDCREG_SECTOR	4
#घोषणा FDCREG_DATA		6

/* command opcodes */

#घोषणा FDCCMD_RESTORE  (0x00)   /*  -                   */
#घोषणा FDCCMD_SEEK     (0x10)   /*   |                  */
#घोषणा FDCCMD_STEP     (0x20)   /*   |  TYP 1 Commands  */
#घोषणा FDCCMD_STIN     (0x40)   /*   |                  */
#घोषणा FDCCMD_STOT     (0x60)   /*  -                   */
#घोषणा FDCCMD_RDSEC    (0x80)   /*  -   TYP 2 Commands  */
#घोषणा FDCCMD_WRSEC    (0xa0)   /*  -          "        */
#घोषणा FDCCMD_RDADR    (0xc0)   /*  -                   */
#घोषणा FDCCMD_RDTRA    (0xe0)   /*   |  TYP 3 Commands  */
#घोषणा FDCCMD_WRTRA    (0xf0)   /*  -                   */
#घोषणा FDCCMD_FORCI    (0xd0)   /*  -   TYP 4 Command   */

/* command modअगरier bits */

#घोषणा FDCCMDADD_SR6   (0x00)   /* step rate settings */
#घोषणा FDCCMDADD_SR12  (0x01)
#घोषणा FDCCMDADD_SR2   (0x02)
#घोषणा FDCCMDADD_SR3   (0x03)
#घोषणा FDCCMDADD_V     (0x04)   /* verअगरy */
#घोषणा FDCCMDADD_H     (0x08)   /* रुको क्रम spin-up */
#घोषणा FDCCMDADD_U     (0x10)   /* update track रेजिस्टर */
#घोषणा FDCCMDADD_M     (0x10)   /* multiple sector access */
#घोषणा FDCCMDADD_E     (0x04)   /* head settling flag */
#घोषणा FDCCMDADD_P     (0x02)   /* precompensation off */
#घोषणा FDCCMDADD_A0    (0x01)   /* DAM flag */

/* status रेजिस्टर bits */

#घोषणा	FDCSTAT_MOTORON	(0x80)   /* motor on */
#घोषणा	FDCSTAT_WPROT	(0x40)   /* ग_लिखो रक्षित (FDCCMD_WR*) */
#घोषणा	FDCSTAT_SPINUP	(0x20)   /* motor speed stable (Type I) */
#घोषणा	FDCSTAT_DELDAM	(0x20)   /* sector has deleted DAM (Type II+III) */
#घोषणा	FDCSTAT_RECNF	(0x10)   /* record not found */
#घोषणा	FDCSTAT_CRC		(0x08)   /* CRC error */
#घोषणा	FDCSTAT_TR00	(0x04)   /* Track 00 flag (Type I) */
#घोषणा	FDCSTAT_LOST	(0x04)   /* Lost Data (Type II+III) */
#घोषणा	FDCSTAT_IDX		(0x02)   /* Index status (Type I) */
#घोषणा	FDCSTAT_DRQ		(0x02)   /* DRQ status (Type II+III) */
#घोषणा	FDCSTAT_BUSY	(0x01)   /* FDC is busy */


/* PSG Port A Bit Nr 0 .. Side Sel .. 0 -> Side 1  1 -> Side 2 */
#घोषणा DSKSIDE     (0x01)

#घोषणा DSKDRVNONE  (0x06)
#घोषणा DSKDRV0     (0x02)
#घोषणा DSKDRV1     (0x04)

/* step rates */
#घोषणा	FDCSTEP_6	0x00
#घोषणा	FDCSTEP_12	0x01
#घोषणा	FDCSTEP_2	0x02
#घोषणा	FDCSTEP_3	0x03

काष्ठा atari_क्रमmat_descr अणु
	पूर्णांक track;		/* to be क्रमmatted */
	पूर्णांक head;		/*   ""     ""     */
	पूर्णांक sect_offset;	/* offset of first sector */
पूर्ण;

/* Disk types: DD, HD, ED */
अटल काष्ठा atari_disk_type अणु
	स्थिर अक्षर	*name;
	अचिन्हित	spt;		/* sectors per track */
	अचिन्हित	blocks;		/* total number of blocks */
	अचिन्हित	fdc_speed;	/* fdc_speed setting */
	अचिन्हित 	stretch;	/* track करोubling ? */
पूर्ण atari_disk_type[] = अणु
	अणु "d360",  9, 720, 0, 0पूर्ण,	/*  0: 360kB diskette */
	अणु "D360",  9, 720, 0, 1पूर्ण,	/*  1: 360kb in 720k or 1.2MB drive */
	अणु "D720",  9,1440, 0, 0पूर्ण,	/*  2: 720kb in 720k or 1.2MB drive */
	अणु "D820", 10,1640, 0, 0पूर्ण,	/*  3: DD disk with 82 tracks/10 sectors */
/* क्रमmats above are probed क्रम type DD */
#घोषणा	MAX_TYPE_DD 3
	अणु "h1200",15,2400, 3, 0पूर्ण,	/*  4: 1.2MB diskette */
	अणु "H1440",18,2880, 3, 0पूर्ण,	/*  5: 1.4 MB diskette (HD) */
	अणु "H1640",20,3280, 3, 0पूर्ण,	/*  6: 1.64MB diskette (fat HD) 82 tr 20 sec */
/* क्रमmats above are probed क्रम types DD and HD */
#घोषणा	MAX_TYPE_HD 6
	अणु "E2880",36,5760, 3, 0पूर्ण,	/*  7: 2.8 MB diskette (ED) */
	अणु "E3280",40,6560, 3, 0पूर्ण,	/*  8: 3.2 MB diskette (fat ED) 82 tr 40 sec */
/* क्रमmats above are probed क्रम types DD, HD and ED */
#घोषणा	MAX_TYPE_ED 8
/* types below are never स्वतःprobed */
	अणु "H1680",21,3360, 3, 0पूर्ण,	/*  9: 1.68MB diskette (fat HD) 80 tr 21 sec */
	अणु "h410",10,820, 0, 1पूर्ण,		/* 10: 410k diskette 41 tr 10 sec, stretch */
	अणु "h1476",18,2952, 3, 0पूर्ण,	/* 11: 1.48MB diskette 82 tr 18 sec */
	अणु "H1722",21,3444, 3, 0पूर्ण,	/* 12: 1.72MB diskette 82 tr 21 sec */
	अणु "h420",10,840, 0, 1पूर्ण,		/* 13: 420k diskette 42 tr 10 sec, stretch */
	अणु "H830",10,1660, 0, 0पूर्ण,	/* 14: 820k diskette 83 tr 10 sec */
	अणु "h1494",18,2952, 3, 0पूर्ण,	/* 15: 1.49MB diskette 83 tr 18 sec */
	अणु "H1743",21,3486, 3, 0पूर्ण,	/* 16: 1.74MB diskette 83 tr 21 sec */
	अणु "h880",11,1760, 0, 0पूर्ण,	/* 17: 880k diskette 80 tr 11 sec */
	अणु "D1040",13,2080, 0, 0पूर्ण,	/* 18: 1.04MB diskette 80 tr 13 sec */
	अणु "D1120",14,2240, 0, 0पूर्ण,	/* 19: 1.12MB diskette 80 tr 14 sec */
	अणु "h1600",20,3200, 3, 0पूर्ण,	/* 20: 1.60MB diskette 80 tr 20 sec */
	अणु "H1760",22,3520, 3, 0पूर्ण,	/* 21: 1.76MB diskette 80 tr 22 sec */
	अणु "H1920",24,3840, 3, 0पूर्ण,	/* 22: 1.92MB diskette 80 tr 24 sec */
	अणु "E3200",40,6400, 3, 0पूर्ण,	/* 23: 3.2MB diskette 80 tr 40 sec */
	अणु "E3520",44,7040, 3, 0पूर्ण,	/* 24: 3.52MB diskette 80 tr 44 sec */
	अणु "E3840",48,7680, 3, 0पूर्ण,	/* 25: 3.84MB diskette 80 tr 48 sec */
	अणु "H1840",23,3680, 3, 0पूर्ण,	/* 26: 1.84MB diskette 80 tr 23 sec */
	अणु "D800",10,1600, 0, 0पूर्ण,	/* 27: 800k diskette 80 tr 10 sec */
पूर्ण;

अटल पूर्णांक StartDiskType[] = अणु
	MAX_TYPE_DD,
	MAX_TYPE_HD,
	MAX_TYPE_ED
पूर्ण;

#घोषणा	TYPE_DD		0
#घोषणा	TYPE_HD		1
#घोषणा	TYPE_ED		2

अटल पूर्णांक DriveType = TYPE_HD;

अटल DEFINE_SPINLOCK(ataflop_lock);

/* Array क्रम translating minors पूर्णांकo disk क्रमmats */
अटल काष्ठा अणु
	पूर्णांक 	 index;
	अचिन्हित drive_types;
पूर्ण minor2disktype[] = अणु
	अणु  0, TYPE_DD पूर्ण,	/*  1: d360 */
	अणु  4, TYPE_HD पूर्ण,	/*  2: h1200 */
	अणु  1, TYPE_DD पूर्ण,	/*  3: D360 */
	अणु  2, TYPE_DD पूर्ण,	/*  4: D720 */
	अणु  1, TYPE_DD पूर्ण,	/*  5: h360 = D360 */
	अणु  2, TYPE_DD पूर्ण,	/*  6: h720 = D720 */
	अणु  5, TYPE_HD पूर्ण,	/*  7: H1440 */
	अणु  7, TYPE_ED पूर्ण,	/*  8: E2880 */
/* some PC क्रमmats :-) */
	अणु  8, TYPE_ED पूर्ण,	/*  9: E3280    <- was "CompaQ" == E2880 क्रम PC */
	अणु  5, TYPE_HD पूर्ण,	/* 10: h1440 = H1440 */
	अणु  9, TYPE_HD पूर्ण,	/* 11: H1680 */
	अणु 10, TYPE_DD पूर्ण,	/* 12: h410  */
	अणु  3, TYPE_DD पूर्ण,	/* 13: H820     <- == D820, 82x10 */
	अणु 11, TYPE_HD पूर्ण,	/* 14: h1476 */
	अणु 12, TYPE_HD पूर्ण,	/* 15: H1722 */
	अणु 13, TYPE_DD पूर्ण,	/* 16: h420  */
	अणु 14, TYPE_DD पूर्ण,	/* 17: H830  */
	अणु 15, TYPE_HD पूर्ण,	/* 18: h1494 */
	अणु 16, TYPE_HD पूर्ण,	/* 19: H1743 */
	अणु 17, TYPE_DD पूर्ण,	/* 20: h880  */
	अणु 18, TYPE_DD पूर्ण,	/* 21: D1040 */
	अणु 19, TYPE_DD पूर्ण,	/* 22: D1120 */
	अणु 20, TYPE_HD पूर्ण,	/* 23: h1600 */
	अणु 21, TYPE_HD पूर्ण,	/* 24: H1760 */
	अणु 22, TYPE_HD पूर्ण,	/* 25: H1920 */
	अणु 23, TYPE_ED पूर्ण,	/* 26: E3200 */
	अणु 24, TYPE_ED पूर्ण,	/* 27: E3520 */
	अणु 25, TYPE_ED पूर्ण,	/* 28: E3840 */
	अणु 26, TYPE_HD पूर्ण,	/* 29: H1840 */
	अणु 27, TYPE_DD पूर्ण,	/* 30: D800  */
	अणु  6, TYPE_HD पूर्ण,	/* 31: H1640    <- was H1600 == h1600 क्रम PC */
पूर्ण;

#घोषणा NUM_DISK_MINORS ARRAY_SIZE(minor2disktype)

/*
 * Maximum disk size (in kilobytes). This शेष is used whenever the
 * current disk size is unknown.
 */
#घोषणा MAX_DISK_SIZE 3280

/*
 * MSch: User-provided type inक्रमmation. 'drive' poपूर्णांकs to
 * the respective entry of this array. Set by FDSETPRM ioctls.
 */
अटल काष्ठा atari_disk_type user_params[FD_MAX_UNITS];

/*
 * User-provided permanent type inक्रमmation. 'drive' poपूर्णांकs to
 * the respective entry of this array.  Set by FDDEFPRM ioctls, 
 * restored upon disk change by floppy_revalidate() अगर valid (as seen by
 * शेष_params[].blocks > 0 - a bit in unit[].flags might be used क्रम this?)
 */
अटल काष्ठा atari_disk_type शेष_params[FD_MAX_UNITS];

/* current info on each unit */
अटल काष्ठा atari_floppy_काष्ठा अणु
	पूर्णांक connected;				/* !=0 : drive is connected */
	पूर्णांक स्वतःprobe;				/* !=0 : करो स्वतःprobe	    */

	काष्ठा atari_disk_type	*disktype;	/* current type of disk */

	पूर्णांक track;		/* current head position or -1 अगर
				   unknown */
	अचिन्हित पूर्णांक steprate;	/* steprate setting */
	अचिन्हित पूर्णांक wpstat;	/* current state of WP संकेत (क्रम
				   disk change detection) */
	पूर्णांक flags;		/* flags */
	काष्ठा gendisk *disk[NUM_DISK_MINORS];
	पूर्णांक ref;
	पूर्णांक type;
	काष्ठा blk_mq_tag_set tag_set;
पूर्ण unit[FD_MAX_UNITS];

#घोषणा	UD	unit[drive]
#घोषणा	UDT	unit[drive].disktype
#घोषणा	SUD	unit[SelectedDrive]
#घोषणा	SUDT	unit[SelectedDrive].disktype


#घोषणा FDC_READ(reg) (अणु			\
    /* अचिन्हित दीर्घ __flags; */		\
    अचिन्हित लघु __val;			\
    /* local_irq_save(__flags); */		\
    dma_wd.dma_mode_status = 0x80 | (reg);	\
    udelay(25);					\
    __val = dma_wd.fdc_acces_seccount;		\
    MFPDELAY();					\
    /* local_irq_restore(__flags); */		\
    __val & 0xff;				\
पूर्ण)

#घोषणा FDC_WRITE(reg,val)			\
    करो अणु					\
	/* अचिन्हित दीर्घ __flags; */		\
	/* local_irq_save(__flags); */		\
	dma_wd.dma_mode_status = 0x80 | (reg);	\
	udelay(25);				\
	dma_wd.fdc_acces_seccount = (val);	\
	MFPDELAY();				\
        /* local_irq_restore(__flags); */	\
    पूर्ण जबतक(0)


/* Buffering variables:
 * First, there is a DMA buffer in ST-RAM that is used क्रम floppy DMA
 * operations. Second, a track buffer is used to cache a whole track
 * of the disk to save पढ़ो operations. These are two separate buffers
 * because that allows ग_लिखो operations without clearing the track buffer.
 */

अटल पूर्णांक MaxSectors[] = अणु
	11, 22, 44
पूर्ण;
अटल पूर्णांक BufferSize[] = अणु
	15*512, 30*512, 60*512
पूर्ण;

#घोषणा	BUFFER_SIZE	(BufferSize[DriveType])

अचिन्हित अक्षर *DMABuffer;			  /* buffer क्रम ग_लिखोs */
अटल अचिन्हित दीर्घ PhysDMABuffer;   /* physical address */

अटल पूर्णांक UseTrackbuffer = -1;		  /* Do track buffering? */
module_param(UseTrackbuffer, पूर्णांक, 0);

अचिन्हित अक्षर *TrackBuffer;			  /* buffer क्रम पढ़ोs */
अटल अचिन्हित दीर्घ PhysTrackBuffer; /* physical address */
अटल पूर्णांक BufferDrive, BufferSide, BufferTrack;
अटल पूर्णांक पढ़ो_track;		/* non-zero अगर we are पढ़ोing whole tracks */

#घोषणा	SECTOR_BUFFER(sec)	(TrackBuffer + ((sec)-1)*512)
#घोषणा	IS_BUFFERED(drive,side,track) \
    (BufferDrive == (drive) && BufferSide == (side) && BufferTrack == (track))

/*
 * These are global variables, as that's the easiest way to give
 * inक्रमmation to पूर्णांकerrupts. They are the data used क्रम the current
 * request.
 */
अटल पूर्णांक SelectedDrive = 0;
अटल पूर्णांक ReqCmd, ReqBlock;
अटल पूर्णांक ReqSide, ReqTrack, ReqSector, ReqCnt;
अटल पूर्णांक HeadSettleFlag = 0;
अटल अचिन्हित अक्षर *ReqData, *ReqBuffer;
अटल पूर्णांक MotorOn = 0, MotorOffTrys;
अटल पूर्णांक IsFormatting = 0, FormatError;

अटल पूर्णांक UserSteprate[FD_MAX_UNITS] = अणु -1, -1 पूर्ण;
module_param_array(UserSteprate, पूर्णांक, शून्य, 0);

अटल DECLARE_COMPLETION(क्रमmat_रुको);

अटल अचिन्हित दीर्घ changed_floppies = 0xff, fake_change = 0;
#घोषणा	CHECK_CHANGE_DELAY	HZ/2

#घोषणा	FD_MOTOR_OFF_DELAY	(3*HZ)
#घोषणा	FD_MOTOR_OFF_MAXTRY	(10*20)

#घोषणा FLOPPY_TIMEOUT		(6*HZ)
#घोषणा RECALIBRATE_ERRORS	4	/* After this many errors the drive
					 * will be recalibrated. */
#घोषणा MAX_ERRORS		8	/* After this many errors the driver
					 * will give up. */


/*
 * The driver is trying to determine the correct media क्रमmat
 * जबतक Probing is set. fd_rwsec_करोne() clears it after a
 * successful access.
 */
अटल पूर्णांक Probing = 0;

/* This flag is set when a dummy seek is necessary to make the WP
 * status bit accessible.
 */
अटल पूर्णांक NeedSeek = 0;


#अगर_घोषित DEBUG
#घोषणा DPRINT(a)	prपूर्णांकk a
#अन्यथा
#घोषणा DPRINT(a)
#पूर्ण_अगर

/***************************** Prototypes *****************************/

अटल व्योम fd_select_side( पूर्णांक side );
अटल व्योम fd_select_drive( पूर्णांक drive );
अटल व्योम fd_deselect( व्योम );
अटल व्योम fd_motor_off_समयr(काष्ठा समयr_list *unused);
अटल व्योम check_change(काष्ठा समयr_list *unused);
अटल irqवापस_t floppy_irq (पूर्णांक irq, व्योम *dummy);
अटल व्योम fd_error( व्योम );
अटल पूर्णांक करो_क्रमmat(पूर्णांक drive, पूर्णांक type, काष्ठा atari_क्रमmat_descr *desc);
अटल व्योम करो_fd_action( पूर्णांक drive );
अटल व्योम fd_calibrate( व्योम );
अटल व्योम fd_calibrate_करोne( पूर्णांक status );
अटल व्योम fd_seek( व्योम );
अटल व्योम fd_seek_करोne( पूर्णांक status );
अटल व्योम fd_rwsec( व्योम );
अटल व्योम fd_पढ़ोtrack_check(काष्ठा समयr_list *unused);
अटल व्योम fd_rwsec_करोne( पूर्णांक status );
अटल व्योम fd_rwsec_करोne1(पूर्णांक status);
अटल व्योम fd_ग_लिखोtrack( व्योम );
अटल व्योम fd_ग_लिखोtrack_करोne( पूर्णांक status );
अटल व्योम fd_बार_out(काष्ठा समयr_list *unused);
अटल व्योम finish_fdc( व्योम );
अटल व्योम finish_fdc_करोne( पूर्णांक dummy );
अटल व्योम setup_req_params( पूर्णांक drive );
अटल पूर्णांक fd_locked_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित पूर्णांक
                     cmd, अचिन्हित दीर्घ param);
अटल व्योम fd_probe( पूर्णांक drive );
अटल पूर्णांक fd_test_drive_present( पूर्णांक drive );
अटल व्योम config_types( व्योम );
अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode);
अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode);

/************************* End of Prototypes **************************/

अटल DEFINE_TIMER(motor_off_समयr, fd_motor_off_समयr);
अटल DEFINE_TIMER(पढ़ोtrack_समयr, fd_पढ़ोtrack_check);
अटल DEFINE_TIMER(समयout_समयr, fd_बार_out);
अटल DEFINE_TIMER(fd_समयr, check_change);
	
अटल व्योम fd_end_request_cur(blk_status_t err)
अणु
	अगर (!blk_update_request(fd_request, err,
				blk_rq_cur_bytes(fd_request))) अणु
		__blk_mq_end_request(fd_request, err);
		fd_request = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम start_motor_off_समयr(व्योम)
अणु
	mod_समयr(&motor_off_समयr, jअगरfies + FD_MOTOR_OFF_DELAY);
	MotorOffTrys = 0;
पूर्ण

अटल अंतरभूत व्योम start_check_change_समयr( व्योम )
अणु
	mod_समयr(&fd_समयr, jअगरfies + CHECK_CHANGE_DELAY);
पूर्ण

अटल अंतरभूत व्योम start_समयout(व्योम)
अणु
	mod_समयr(&समयout_समयr, jअगरfies + FLOPPY_TIMEOUT);
पूर्ण

अटल अंतरभूत व्योम stop_समयout(व्योम)
अणु
	del_समयr(&समयout_समयr);
पूर्ण

/* Select the side to use. */

अटल व्योम fd_select_side( पूर्णांक side )
अणु
	अचिन्हित दीर्घ flags;

	/* protect against various other पूर्णांकs mucking around with the PSG */
	local_irq_save(flags);
  
	sound_ym.rd_data_reg_sel = 14; /* Select PSG Port A */
	sound_ym.wd_data = (side == 0) ? sound_ym.rd_data_reg_sel | 0x01 :
	                                 sound_ym.rd_data_reg_sel & 0xfe;

	local_irq_restore(flags);
पूर्ण


/* Select a drive, update the FDC's track रेजिस्टर and set the correct
 * घड़ी speed क्रम this disk's type.
 */

अटल व्योम fd_select_drive( पूर्णांक drive )
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
  
	अगर (drive == SelectedDrive)
	  वापस;

	/* protect against various other पूर्णांकs mucking around with the PSG */
	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 14; /* Select PSG Port A */
	पंचांगp = sound_ym.rd_data_reg_sel;
	sound_ym.wd_data = (पंचांगp | DSKDRVNONE) & ~(drive == 0 ? DSKDRV0 : DSKDRV1);
	atari_करोnt_touch_floppy_select = 1;
	local_irq_restore(flags);

	/* restore track रेजिस्टर to saved value */
	FDC_WRITE( FDCREG_TRACK, UD.track );
	udelay(25);

	/* select 8/16 MHz */
	अगर (UDT)
		अगर (ATARIHW_PRESENT(FDCSPEED))
			dma_wd.fdc_speed = UDT->fdc_speed;
	
	SelectedDrive = drive;
पूर्ण


/* Deselect both drives. */

अटल व्योम fd_deselect( व्योम )
अणु
	अचिन्हित दीर्घ flags;

	/* protect against various other पूर्णांकs mucking around with the PSG */
	local_irq_save(flags);
	atari_करोnt_touch_floppy_select = 0;
	sound_ym.rd_data_reg_sel=14;	/* Select PSG Port A */
	sound_ym.wd_data = (sound_ym.rd_data_reg_sel |
			    (MACH_IS_FALCON ? 3 : 7)); /* no drives selected */
	/* On Falcon, the drive B select line is used on the prपूर्णांकer port, so
	 * leave it alone... */
	SelectedDrive = -1;
	local_irq_restore(flags);
पूर्ण


/* This समयr function deselects the drives when the FDC चयनed the
 * motor off. The deselection cannot happen earlier because the FDC
 * counts the index संकेतs, which arrive only अगर one drive is selected.
 */

अटल व्योम fd_motor_off_समयr(काष्ठा समयr_list *unused)
अणु
	अचिन्हित अक्षर status;

	अगर (SelectedDrive < 0)
		/* no drive selected, needn't deselect anyone */
		वापस;

	अगर (stdma_islocked())
		जाओ retry;

	status = FDC_READ( FDCREG_STATUS );

	अगर (!(status & 0x80)) अणु
		/* motor alपढ़ोy turned off by FDC -> deselect drives */
		MotorOn = 0;
		fd_deselect();
		वापस;
	पूर्ण
	/* not yet off, try again */

  retry:
	/* Test again later; अगर tested too often, it seems there is no disk
	 * in the drive and the FDC will leave the motor on क्रमever (or,
	 * at least until a disk is inserted). So we'll test only twice
	 * per second from then on...
	 */
	mod_समयr(&motor_off_समयr,
		  jअगरfies + (MotorOffTrys++ < FD_MOTOR_OFF_MAXTRY ? HZ/20 : HZ/2));
पूर्ण


/* This function is repeatedly called to detect disk changes (as good
 * as possible) and keep track of the current state of the ग_लिखो protection.
 */

अटल व्योम check_change(काष्ठा समयr_list *unused)
अणु
	अटल पूर्णांक    drive = 0;

	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर old_porta;
	पूर्णांक			  stat;

	अगर (++drive > 1 || !UD.connected)
		drive = 0;

	/* protect against various other पूर्णांकs mucking around with the PSG */
	local_irq_save(flags);

	अगर (!stdma_islocked()) अणु
		sound_ym.rd_data_reg_sel = 14;
		old_porta = sound_ym.rd_data_reg_sel;
		sound_ym.wd_data = (old_porta | DSKDRVNONE) &
			               ~(drive == 0 ? DSKDRV0 : DSKDRV1);
		stat = !!(FDC_READ( FDCREG_STATUS ) & FDCSTAT_WPROT);
		sound_ym.wd_data = old_porta;

		अगर (stat != UD.wpstat) अणु
			DPRINT(( "wpstat[%d] = %d\n", drive, stat ));
			UD.wpstat = stat;
			set_bit (drive, &changed_floppies);
		पूर्ण
	पूर्ण
	local_irq_restore(flags);

	start_check_change_समयr();
पूर्ण

 
/* Handling of the Head Settling Flag: This flag should be set after each
 * seek operation, because we करोn't use seeks with verअगरy.
 */

अटल अंतरभूत व्योम set_head_settle_flag(व्योम)
अणु
	HeadSettleFlag = FDCCMDADD_E;
पूर्ण

अटल अंतरभूत पूर्णांक get_head_settle_flag(व्योम)
अणु
	पूर्णांक	पंचांगp = HeadSettleFlag;
	HeadSettleFlag = 0;
	वापस( पंचांगp );
पूर्ण

अटल अंतरभूत व्योम copy_buffer(व्योम *from, व्योम *to)
अणु
	uदीर्घ *p1 = (uदीर्घ *)from, *p2 = (uदीर्घ *)to;
	पूर्णांक cnt;

	क्रम (cnt = 512/4; cnt; cnt--)
		*p2++ = *p1++;
पूर्ण

  
  

/* General Interrupt Handling */

अटल व्योम (*FloppyIRQHandler)( पूर्णांक status ) = शून्य;

अटल irqवापस_t floppy_irq (पूर्णांक irq, व्योम *dummy)
अणु
	अचिन्हित अक्षर status;
	व्योम (*handler)( पूर्णांक );

	handler = xchg(&FloppyIRQHandler, शून्य);

	अगर (handler) अणु
		nop();
		status = FDC_READ( FDCREG_STATUS );
		DPRINT(("FDC irq, status = %02x handler = %08lx\n",status,(अचिन्हित दीर्घ)handler));
		handler( status );
	पूर्ण
	अन्यथा अणु
		DPRINT(("FDC irq, no handler\n"));
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


/* Error handling: If some error happened, retry some बार, then
 * recalibrate, then try again, and fail after MAX_ERRORS.
 */

अटल व्योम fd_error( व्योम )
अणु
	अगर (IsFormatting) अणु
		IsFormatting = 0;
		FormatError = 1;
		complete(&क्रमmat_रुको);
		वापस;
	पूर्ण

	अगर (!fd_request)
		वापस;

	fd_request->error_count++;
	अगर (fd_request->error_count >= MAX_ERRORS) अणु
		prपूर्णांकk(KERN_ERR "fd%d: too many errors.\n", SelectedDrive );
		fd_end_request_cur(BLK_STS_IOERR);
	पूर्ण
	अन्यथा अगर (fd_request->error_count == RECALIBRATE_ERRORS) अणु
		prपूर्णांकk(KERN_WARNING "fd%d: recalibrating\n", SelectedDrive );
		अगर (SelectedDrive != -1)
			SUD.track = -1;
	पूर्ण
पूर्ण



#घोषणा	SET_IRQ_HANDLER(proc) करो अणु FloppyIRQHandler = (proc); पूर्ण जबतक(0)


/* ---------- Formatting ---------- */

#घोषणा FILL(n,val)		\
    करो अणु			\
	स_रखो( p, val, n );	\
	p += n;			\
    पूर्ण जबतक(0)

अटल पूर्णांक करो_क्रमmat(पूर्णांक drive, पूर्णांक type, काष्ठा atari_क्रमmat_descr *desc)
अणु
	काष्ठा request_queue *q;
	अचिन्हित अक्षर	*p;
	पूर्णांक sect, nsect;
	अचिन्हित दीर्घ	flags;
	पूर्णांक ret;

	अगर (type) अणु
		type--;
		अगर (type >= NUM_DISK_MINORS ||
		    minor2disktype[type].drive_types > DriveType)
			वापस -EINVAL;
	पूर्ण

	q = unit[drive].disk[type]->queue;
	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);

	local_irq_save(flags);
	stdma_lock(floppy_irq, शून्य);
	atari_turnon_irq( IRQ_MFP_FDC ); /* should be alपढ़ोy, just to be sure */
	local_irq_restore(flags);

	अगर (type) अणु
		type = minor2disktype[type].index;
		UDT = &atari_disk_type[type];
	पूर्ण

	अगर (!UDT || desc->track >= UDT->blocks/UDT->spt/2 || desc->head >= 2) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	nsect = UDT->spt;
	p = TrackBuffer;
	/* The track buffer is used क्रम the raw track data, so its
	   contents become invalid! */
	BufferDrive = -1;
	/* stop deselect समयr */
	del_समयr( &motor_off_समयr );

	FILL( 60 * (nsect / 9), 0x4e );
	क्रम( sect = 0; sect < nsect; ++sect ) अणु
		FILL( 12, 0 );
		FILL( 3, 0xf5 );
		*p++ = 0xfe;
		*p++ = desc->track;
		*p++ = desc->head;
		*p++ = (nsect + sect - desc->sect_offset) % nsect + 1;
		*p++ = 2;
		*p++ = 0xf7;
		FILL( 22, 0x4e );
		FILL( 12, 0 );
		FILL( 3, 0xf5 );
		*p++ = 0xfb;
		FILL( 512, 0xe5 );
		*p++ = 0xf7;
		FILL( 40, 0x4e );
	पूर्ण
	FILL( TrackBuffer+BUFFER_SIZE-p, 0x4e );

	IsFormatting = 1;
	FormatError = 0;
	ReqTrack = desc->track;
	ReqSide  = desc->head;
	करो_fd_action( drive );

	रुको_क्रम_completion(&क्रमmat_रुको);

	ret = FormatError ? -EIO : 0;
out:
	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);
	वापस ret;
पूर्ण


/* करो_fd_action() is the general procedure क्रम a fd request: All
 * required parameter settings (drive select, side select, track
 * position) are checked and set अगर needed. For each of these
 * parameters and the actual पढ़ोing or writing exist two functions:
 * one that starts the setting (or skips it अगर possible) and one
 * callback क्रम the "done" पूर्णांकerrupt. Each करोne func calls the next
 * set function to propagate the request करोwn to fd_rwsec_करोne().
 */

अटल व्योम करो_fd_action( पूर्णांक drive )
अणु
	DPRINT(("do_fd_action\n"));
	
	अगर (UseTrackbuffer && !IsFormatting) अणु
	repeat:
	    अगर (IS_BUFFERED( drive, ReqSide, ReqTrack )) अणु
		अगर (ReqCmd == READ) अणु
		    copy_buffer( SECTOR_BUFFER(ReqSector), ReqData );
		    अगर (++ReqCnt < blk_rq_cur_sectors(fd_request)) अणु
			/* पढ़ो next sector */
			setup_req_params( drive );
			जाओ repeat;
		    पूर्ण
		    अन्यथा अणु
			/* all sectors finished */
			fd_end_request_cur(BLK_STS_OK);
			वापस;
		    पूर्ण
		पूर्ण
		अन्यथा अणु
		    /* cmd == WRITE, pay attention to track buffer
		     * consistency! */
		    copy_buffer( ReqData, SECTOR_BUFFER(ReqSector) );
		पूर्ण
	    पूर्ण
	पूर्ण

	अगर (SelectedDrive != drive)
		fd_select_drive( drive );
    
	अगर (UD.track == -1)
		fd_calibrate();
	अन्यथा अगर (UD.track != ReqTrack << UDT->stretch)
		fd_seek();
	अन्यथा अगर (IsFormatting)
		fd_ग_लिखोtrack();
	अन्यथा
		fd_rwsec();
पूर्ण


/* Seek to track 0 अगर the current track is unknown */

अटल व्योम fd_calibrate( व्योम )
अणु
	अगर (SUD.track >= 0) अणु
		fd_calibrate_करोne( 0 );
		वापस;
	पूर्ण

	अगर (ATARIHW_PRESENT(FDCSPEED))
		dma_wd.fdc_speed = 0;   /* always seek with 8 Mhz */
	DPRINT(("fd_calibrate\n"));
	SET_IRQ_HANDLER( fd_calibrate_करोne );
	/* we can't verअगरy, since the speed may be incorrect */
	FDC_WRITE( FDCREG_CMD, FDCCMD_RESTORE | SUD.steprate );

	NeedSeek = 1;
	MotorOn = 1;
	start_समयout();
	/* रुको क्रम IRQ */
पूर्ण


अटल व्योम fd_calibrate_करोne( पूर्णांक status )
अणु
	DPRINT(("fd_calibrate_done()\n"));
	stop_समयout();
    
	/* set the correct speed now */
	अगर (ATARIHW_PRESENT(FDCSPEED))
		dma_wd.fdc_speed = SUDT->fdc_speed;
	अगर (status & FDCSTAT_RECNF) अणु
		prपूर्णांकk(KERN_ERR "fd%d: restore failed\n", SelectedDrive );
		fd_error();
	पूर्ण
	अन्यथा अणु
		SUD.track = 0;
		fd_seek();
	पूर्ण
पूर्ण
  
  
/* Seek the drive to the requested track. The drive must have been
 * calibrated at some poपूर्णांक beक्रमe this.
 */
  
अटल व्योम fd_seek( व्योम )
अणु
	अगर (SUD.track == ReqTrack << SUDT->stretch) अणु
		fd_seek_करोne( 0 );
		वापस;
	पूर्ण

	अगर (ATARIHW_PRESENT(FDCSPEED)) अणु
		dma_wd.fdc_speed = 0;	/* always seek witch 8 Mhz */
		MFPDELAY();
	पूर्ण

	DPRINT(("fd_seek() to track %d\n",ReqTrack));
	FDC_WRITE( FDCREG_DATA, ReqTrack << SUDT->stretch);
	udelay(25);
	SET_IRQ_HANDLER( fd_seek_करोne );
	FDC_WRITE( FDCREG_CMD, FDCCMD_SEEK | SUD.steprate );

	MotorOn = 1;
	set_head_settle_flag();
	start_समयout();
	/* रुको क्रम IRQ */
पूर्ण


अटल व्योम fd_seek_करोne( पूर्णांक status )
अणु
	DPRINT(("fd_seek_done()\n"));
	stop_समयout();
	
	/* set the correct speed */
	अगर (ATARIHW_PRESENT(FDCSPEED))
		dma_wd.fdc_speed = SUDT->fdc_speed;
	अगर (status & FDCSTAT_RECNF) अणु
		prपूर्णांकk(KERN_ERR "fd%d: seek error (to track %d)\n",
				SelectedDrive, ReqTrack );
		/* we करोn't know exactly which track we are on now! */
		SUD.track = -1;
		fd_error();
	पूर्ण
	अन्यथा अणु
		SUD.track = ReqTrack << SUDT->stretch;
		NeedSeek = 0;
		अगर (IsFormatting)
			fd_ग_लिखोtrack();
		अन्यथा
			fd_rwsec();
	पूर्ण
पूर्ण


/* This करोes the actual पढ़ोing/writing after positioning the head
 * over the correct track.
 */

अटल पूर्णांक MultReadInProgress = 0;


अटल व्योम fd_rwsec( व्योम )
अणु
	अचिन्हित दीर्घ paddr, flags;
	अचिन्हित पूर्णांक  rwflag, old_motoron;
	अचिन्हित पूर्णांक track;
	
	DPRINT(("fd_rwsec(), Sec=%d, Access=%c\n",ReqSector, ReqCmd == WRITE ? 'w' : 'r' ));
	अगर (ReqCmd == WRITE) अणु
		अगर (ATARIHW_PRESENT(EXTD_DMA)) अणु
			paddr = virt_to_phys(ReqData);
		पूर्ण
		अन्यथा अणु
			copy_buffer( ReqData, DMABuffer );
			paddr = PhysDMABuffer;
		पूर्ण
		dma_cache_मुख्यtenance( paddr, 512, 1 );
		rwflag = 0x100;
	पूर्ण
	अन्यथा अणु
		अगर (पढ़ो_track)
			paddr = PhysTrackBuffer;
		अन्यथा
			paddr = ATARIHW_PRESENT(EXTD_DMA) ? 
				virt_to_phys(ReqData) : PhysDMABuffer;
		rwflag = 0;
	पूर्ण

	fd_select_side( ReqSide );
  
	/* Start sector of this operation */
	FDC_WRITE( FDCREG_SECTOR, पढ़ो_track ? 1 : ReqSector );
	MFPDELAY();
	/* Cheat क्रम track अगर stretch != 0 */
	अगर (SUDT->stretch) अणु
		track = FDC_READ( FDCREG_TRACK);
		MFPDELAY();
		FDC_WRITE( FDCREG_TRACK, track >> SUDT->stretch);
	पूर्ण
	udelay(25);
  
	/* Setup DMA */
	local_irq_save(flags);
	dma_wd.dma_lo = (अचिन्हित अक्षर)paddr;
	MFPDELAY();
	paddr >>= 8;
	dma_wd.dma_md = (अचिन्हित अक्षर)paddr;
	MFPDELAY();
	paddr >>= 8;
	अगर (ATARIHW_PRESENT(EXTD_DMA))
		st_dma_ext_dmahi = (अचिन्हित लघु)paddr;
	अन्यथा
		dma_wd.dma_hi = (अचिन्हित अक्षर)paddr;
	MFPDELAY();
	local_irq_restore(flags);
  
	/* Clear FIFO and चयन DMA to correct mode */  
	dma_wd.dma_mode_status = 0x90 | rwflag;  
	MFPDELAY();
	dma_wd.dma_mode_status = 0x90 | (rwflag ^ 0x100);  
	MFPDELAY();
	dma_wd.dma_mode_status = 0x90 | rwflag;
	MFPDELAY();
  
	/* How many sectors क्रम DMA */
	dma_wd.fdc_acces_seccount = पढ़ो_track ? SUDT->spt : 1;
  
	udelay(25);  
  
	/* Start operation */
	dma_wd.dma_mode_status = FDCSELREG_STP | rwflag;
	udelay(25);
	SET_IRQ_HANDLER( fd_rwsec_करोne );
	dma_wd.fdc_acces_seccount =
	  (get_head_settle_flag() |
	   (rwflag ? FDCCMD_WRSEC : (FDCCMD_RDSEC | (पढ़ो_track ? FDCCMDADD_M : 0))));

	old_motoron = MotorOn;
	MotorOn = 1;
	NeedSeek = 1;
	/* रुको क्रम पूर्णांकerrupt */

	अगर (पढ़ो_track) अणु
		/* If पढ़ोing a whole track, रुको about one disk rotation and
		 * then check अगर all sectors are पढ़ो. The FDC will even
		 * search क्रम the first non-existent sector and need 1 sec to
		 * recognise that it isn't present :-(
		 */
		MultReadInProgress = 1;
		mod_समयr(&पढ़ोtrack_समयr,
			  /* 1 rot. + 5 rot.s अगर motor was off  */
			  jअगरfies + HZ/5 + (old_motoron ? 0 : HZ));
	पूर्ण
	start_समयout();
पूर्ण

    
अटल व्योम fd_पढ़ोtrack_check(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags, addr, addr2;

	local_irq_save(flags);

	अगर (!MultReadInProgress) अणु
		/* This prevents a race condition that could arise अगर the
		 * पूर्णांकerrupt is triggered जबतक the calling of this समयr
		 * callback function takes place. The IRQ function then has
		 * alपढ़ोy cleared 'MultReadInProgress'  when flow of control
		 * माला_लो here.
		 */
		local_irq_restore(flags);
		वापस;
	पूर्ण

	/* get the current DMA address */
	/* ++ f.a. पढ़ो twice to aव्योम being fooled by चयनer */
	addr = 0;
	करो अणु
		addr2 = addr;
		addr = dma_wd.dma_lo & 0xff;
		MFPDELAY();
		addr |= (dma_wd.dma_md & 0xff) << 8;
		MFPDELAY();
		अगर (ATARIHW_PRESENT( EXTD_DMA ))
			addr |= (st_dma_ext_dmahi & 0xffff) << 16;
		अन्यथा
			addr |= (dma_wd.dma_hi & 0xff) << 16;
		MFPDELAY();
	पूर्ण जबतक(addr != addr2);
  
	अगर (addr >= PhysTrackBuffer + SUDT->spt*512) अणु
		/* alपढ़ोy पढ़ो enough data, क्रमce an FDC पूर्णांकerrupt to stop
		 * the पढ़ो operation
		 */
		SET_IRQ_HANDLER( शून्य );
		MultReadInProgress = 0;
		local_irq_restore(flags);
		DPRINT(("fd_readtrack_check(): done\n"));
		FDC_WRITE( FDCREG_CMD, FDCCMD_FORCI );
		udelay(25);

		/* No error until now -- the FDC would have पूर्णांकerrupted
		 * otherwise!
		 */
		fd_rwsec_करोne1(0);
	पूर्ण
	अन्यथा अणु
		/* not yet finished, रुको another tenth rotation */
		local_irq_restore(flags);
		DPRINT(("fd_readtrack_check(): not yet finished\n"));
		mod_समयr(&पढ़ोtrack_समयr, jअगरfies + HZ/5/10);
	पूर्ण
पूर्ण


अटल व्योम fd_rwsec_करोne( पूर्णांक status )
अणु
	DPRINT(("fd_rwsec_done()\n"));

	अगर (पढ़ो_track) अणु
		del_समयr(&पढ़ोtrack_समयr);
		अगर (!MultReadInProgress)
			वापस;
		MultReadInProgress = 0;
	पूर्ण
	fd_rwsec_करोne1(status);
पूर्ण

अटल व्योम fd_rwsec_करोne1(पूर्णांक status)
अणु
	अचिन्हित पूर्णांक track;

	stop_समयout();
	
	/* Correct the track अगर stretch != 0 */
	अगर (SUDT->stretch) अणु
		track = FDC_READ( FDCREG_TRACK);
		MFPDELAY();
		FDC_WRITE( FDCREG_TRACK, track << SUDT->stretch);
	पूर्ण

	अगर (!UseTrackbuffer) अणु
		dma_wd.dma_mode_status = 0x90;
		MFPDELAY();
		अगर (!(dma_wd.dma_mode_status & 0x01)) अणु
			prपूर्णांकk(KERN_ERR "fd%d: DMA error\n", SelectedDrive );
			जाओ err_end;
		पूर्ण
	पूर्ण
	MFPDELAY();

	अगर (ReqCmd == WRITE && (status & FDCSTAT_WPROT)) अणु
		prपूर्णांकk(KERN_NOTICE "fd%d: is write protected\n", SelectedDrive );
		जाओ err_end;
	पूर्ण	
	अगर ((status & FDCSTAT_RECNF) &&
	    /* RECNF is no error after a multiple पढ़ो when the FDC
	       searched क्रम a non-existent sector! */
	    !(पढ़ो_track && FDC_READ(FDCREG_SECTOR) > SUDT->spt)) अणु
		अगर (Probing) अणु
			अगर (SUDT > atari_disk_type) अणु
			    अगर (SUDT[-1].blocks > ReqBlock) अणु
				/* try another disk type */
				SUDT--;
				set_capacity(unit[SelectedDrive].disk[0],
							SUDT->blocks);
			    पूर्ण अन्यथा
				Probing = 0;
			पूर्ण
			अन्यथा अणु
				अगर (SUD.flags & FTD_MSG)
					prपूर्णांकk(KERN_INFO "fd%d: Auto-detected floppy type %s\n",
					       SelectedDrive, SUDT->name );
				Probing=0;
			पूर्ण
		पूर्ण अन्यथा अणु	
/* record not found, but not probing. Maybe stretch wrong ? Restart probing */
			अगर (SUD.स्वतःprobe) अणु
				SUDT = atari_disk_type + StartDiskType[DriveType];
				set_capacity(unit[SelectedDrive].disk[0],
							SUDT->blocks);
				Probing = 1;
			पूर्ण
		पूर्ण
		अगर (Probing) अणु
			अगर (ATARIHW_PRESENT(FDCSPEED)) अणु
				dma_wd.fdc_speed = SUDT->fdc_speed;
				MFPDELAY();
			पूर्ण
			setup_req_params( SelectedDrive );
			BufferDrive = -1;
			करो_fd_action( SelectedDrive );
			वापस;
		पूर्ण

		prपूर्णांकk(KERN_ERR "fd%d: sector %d not found (side %d, track %d)\n",
		       SelectedDrive, FDC_READ (FDCREG_SECTOR), ReqSide, ReqTrack );
		जाओ err_end;
	पूर्ण
	अगर (status & FDCSTAT_CRC) अणु
		prपूर्णांकk(KERN_ERR "fd%d: CRC error (side %d, track %d, sector %d)\n",
		       SelectedDrive, ReqSide, ReqTrack, FDC_READ (FDCREG_SECTOR) );
		जाओ err_end;
	पूर्ण
	अगर (status & FDCSTAT_LOST) अणु
		prपूर्णांकk(KERN_ERR "fd%d: lost data (side %d, track %d, sector %d)\n",
		       SelectedDrive, ReqSide, ReqTrack, FDC_READ (FDCREG_SECTOR) );
		जाओ err_end;
	पूर्ण

	Probing = 0;
	
	अगर (ReqCmd == READ) अणु
		अगर (!पढ़ो_track) अणु
			व्योम *addr;
			addr = ATARIHW_PRESENT( EXTD_DMA ) ? ReqData : DMABuffer;
			dma_cache_मुख्यtenance( virt_to_phys(addr), 512, 0 );
			अगर (!ATARIHW_PRESENT( EXTD_DMA ))
				copy_buffer (addr, ReqData);
		पूर्ण अन्यथा अणु
			dma_cache_मुख्यtenance( PhysTrackBuffer, MaxSectors[DriveType] * 512, 0 );
			BufferDrive = SelectedDrive;
			BufferSide  = ReqSide;
			BufferTrack = ReqTrack;
			copy_buffer (SECTOR_BUFFER (ReqSector), ReqData);
		पूर्ण
	पूर्ण
  
	अगर (++ReqCnt < blk_rq_cur_sectors(fd_request)) अणु
		/* पढ़ो next sector */
		setup_req_params( SelectedDrive );
		करो_fd_action( SelectedDrive );
	पूर्ण
	अन्यथा अणु
		/* all sectors finished */
		fd_end_request_cur(BLK_STS_OK);
	पूर्ण
	वापस;
  
  err_end:
	BufferDrive = -1;
	fd_error();
पूर्ण


अटल व्योम fd_ग_लिखोtrack( व्योम )
अणु
	अचिन्हित दीर्घ paddr, flags;
	अचिन्हित पूर्णांक track;
	
	DPRINT(("fd_writetrack() Tr=%d Si=%d\n", ReqTrack, ReqSide ));

	paddr = PhysTrackBuffer;
	dma_cache_मुख्यtenance( paddr, BUFFER_SIZE, 1 );

	fd_select_side( ReqSide );
  
	/* Cheat क्रम track अगर stretch != 0 */
	अगर (SUDT->stretch) अणु
		track = FDC_READ( FDCREG_TRACK);
		MFPDELAY();
		FDC_WRITE(FDCREG_TRACK,track >> SUDT->stretch);
	पूर्ण
	udelay(40);
  
	/* Setup DMA */
	local_irq_save(flags);
	dma_wd.dma_lo = (अचिन्हित अक्षर)paddr;
	MFPDELAY();
	paddr >>= 8;
	dma_wd.dma_md = (अचिन्हित अक्षर)paddr;
	MFPDELAY();
	paddr >>= 8;
	अगर (ATARIHW_PRESENT( EXTD_DMA ))
		st_dma_ext_dmahi = (अचिन्हित लघु)paddr;
	अन्यथा
		dma_wd.dma_hi = (अचिन्हित अक्षर)paddr;
	MFPDELAY();
	local_irq_restore(flags);
  
	/* Clear FIFO and चयन DMA to correct mode */  
	dma_wd.dma_mode_status = 0x190;  
	MFPDELAY();
	dma_wd.dma_mode_status = 0x90;  
	MFPDELAY();
	dma_wd.dma_mode_status = 0x190;
	MFPDELAY();
  
	/* How many sectors क्रम DMA */
	dma_wd.fdc_acces_seccount = BUFFER_SIZE/512;
	udelay(40);  
  
	/* Start operation */
	dma_wd.dma_mode_status = FDCSELREG_STP | 0x100;
	udelay(40);
	SET_IRQ_HANDLER( fd_ग_लिखोtrack_करोne );
	dma_wd.fdc_acces_seccount = FDCCMD_WRTRA | get_head_settle_flag(); 

	MotorOn = 1;
	start_समयout();
	/* रुको क्रम पूर्णांकerrupt */
पूर्ण


अटल व्योम fd_ग_लिखोtrack_करोne( पूर्णांक status )
अणु
	DPRINT(("fd_writetrack_done()\n"));

	stop_समयout();

	अगर (status & FDCSTAT_WPROT) अणु
		prपूर्णांकk(KERN_NOTICE "fd%d: is write protected\n", SelectedDrive );
		जाओ err_end;
	पूर्ण	
	अगर (status & FDCSTAT_LOST) अणु
		prपूर्णांकk(KERN_ERR "fd%d: lost data (side %d, track %d)\n",
				SelectedDrive, ReqSide, ReqTrack );
		जाओ err_end;
	पूर्ण

	complete(&क्रमmat_रुको);
	वापस;

  err_end:
	fd_error();
पूर्ण

अटल व्योम fd_बार_out(काष्ठा समयr_list *unused)
अणु
	atari_disable_irq( IRQ_MFP_FDC );
	अगर (!FloppyIRQHandler) जाओ end; /* पूर्णांक occurred after समयr was fired, but
					  * beक्रमe we came here... */

	SET_IRQ_HANDLER( शून्य );
	/* If the समयout occurred जबतक the पढ़ोtrack_check समयr was
	 * active, we need to cancel it, अन्यथा bad things will happen */
	अगर (UseTrackbuffer)
		del_समयr( &पढ़ोtrack_समयr );
	FDC_WRITE( FDCREG_CMD, FDCCMD_FORCI );
	udelay( 25 );
	
	prपूर्णांकk(KERN_ERR "floppy timeout\n" );
	fd_error();
  end:
	atari_enable_irq( IRQ_MFP_FDC );
पूर्ण


/* The (noop) seek operation here is needed to make the WP bit in the
 * FDC status रेजिस्टर accessible क्रम check_change. If the last disk
 * operation would have been a RDSEC, this bit would always पढ़ो as 0
 * no matter what :-( To save समय, the seek goes to the track we're
 * alपढ़ोy on.
 */

अटल व्योम finish_fdc( व्योम )
अणु
	अगर (!NeedSeek) अणु
		finish_fdc_करोne( 0 );
	पूर्ण
	अन्यथा अणु
		DPRINT(("finish_fdc: dummy seek started\n"));
		FDC_WRITE (FDCREG_DATA, SUD.track);
		SET_IRQ_HANDLER( finish_fdc_करोne );
		FDC_WRITE (FDCREG_CMD, FDCCMD_SEEK);
		MotorOn = 1;
		start_समयout();
		/* we must रुको क्रम the IRQ here, because the ST-DMA
		   is released immediately afterwards and the पूर्णांकerrupt
		   may be delivered to the wrong driver. */
	  पूर्ण
पूर्ण


अटल व्योम finish_fdc_करोne( पूर्णांक dummy )
अणु
	अचिन्हित दीर्घ flags;

	DPRINT(("finish_fdc_done entered\n"));
	stop_समयout();
	NeedSeek = 0;

	अगर (समयr_pending(&fd_समयr) && समय_beक्रमe(fd_समयr.expires, jअगरfies + 5))
		/* If the check क्रम a disk change is करोne too early after this
		 * last seek command, the WP bit still पढ़ोs wrong :-((
		 */
		mod_समयr(&fd_समयr, jअगरfies + 5);
	अन्यथा
		start_check_change_समयr();
	start_motor_off_समयr();

	local_irq_save(flags);
	stdma_release();
	local_irq_restore(flags);

	DPRINT(("finish_fdc() finished\n"));
पूर्ण

/* The detection of disk changes is a dark chapter in Atari history :-(
 * Because the "Drive ready" संकेत isn't present in the Atari
 * hardware, one has to rely on the "Write Protect". This works fine,
 * as दीर्घ as no ग_लिखो रक्षित disks are used. TOS solves this
 * problem by पूर्णांकroducing tri-state logic ("maybe changed") and
 * looking at the serial number in block 0. This isn't possible क्रम
 * Linux, since the floppy driver can't make assumptions about the
 * fileप्रणाली used on the disk and thus the contents of block 0. I've
 * chosen the method to always say "The disk was changed" अगर it is
 * unsure whether it was. This implies that every खोलो or mount
 * invalidates the disk buffers अगर you work with ग_लिखो रक्षित
 * disks. But at least this is better than working with incorrect data
 * due to unrecognised disk changes.
 */

अटल अचिन्हित पूर्णांक floppy_check_events(काष्ठा gendisk *disk,
					अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा atari_floppy_काष्ठा *p = disk->निजी_data;
	अचिन्हित पूर्णांक drive = p - unit;
	अगर (test_bit (drive, &fake_change)) अणु
		/* simulated change (e.g. after क्रमmatting) */
		वापस DISK_EVENT_MEDIA_CHANGE;
	पूर्ण
	अगर (test_bit (drive, &changed_floppies)) अणु
		/* surely changed (the WP संकेत changed at least once) */
		वापस DISK_EVENT_MEDIA_CHANGE;
	पूर्ण
	अगर (UD.wpstat) अणु
		/* WP is on -> could be changed: to be sure, buffers should be
		 * invalidated...
		 */
		वापस DISK_EVENT_MEDIA_CHANGE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक floppy_revalidate(काष्ठा gendisk *disk)
अणु
	काष्ठा atari_floppy_काष्ठा *p = disk->निजी_data;
	अचिन्हित पूर्णांक drive = p - unit;

	अगर (test_bit(drive, &changed_floppies) ||
	    test_bit(drive, &fake_change) ||
	    p->disktype == 0) अणु
		अगर (UD.flags & FTD_MSG)
			prपूर्णांकk(KERN_ERR "floppy: clear format %p!\n", UDT);
		BufferDrive = -1;
		clear_bit(drive, &fake_change);
		clear_bit(drive, &changed_floppies);
		/* MSch: clearing geometry makes sense only क्रम स्वतःprobe
		   क्रमmats, क्रम 'permanent user-defined' parameter:
		   restore शेष_params[] here अगर flagged valid! */
		अगर (शेष_params[drive].blocks == 0)
			UDT = शून्य;
		अन्यथा
			UDT = &शेष_params[drive];
	पूर्ण
	वापस 0;
पूर्ण


/* This sets up the global variables describing the current request. */

अटल व्योम setup_req_params( पूर्णांक drive )
अणु
	पूर्णांक block = ReqBlock + ReqCnt;

	ReqTrack = block / UDT->spt;
	ReqSector = block - ReqTrack * UDT->spt + 1;
	ReqSide = ReqTrack & 1;
	ReqTrack >>= 1;
	ReqData = ReqBuffer + 512 * ReqCnt;

	अगर (UseTrackbuffer)
		पढ़ो_track = (ReqCmd == READ && fd_request->error_count == 0);
	अन्यथा
		पढ़ो_track = 0;

	DPRINT(("Request params: Si=%d Tr=%d Se=%d Data=%08lx\n",ReqSide,
			ReqTrack, ReqSector, (अचिन्हित दीर्घ)ReqData ));
पूर्ण

अटल व्योम ataflop_commit_rqs(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	spin_lock_irq(&ataflop_lock);
	atari_disable_irq(IRQ_MFP_FDC);
	finish_fdc();
	atari_enable_irq(IRQ_MFP_FDC);
	spin_unlock_irq(&ataflop_lock);
पूर्ण

अटल blk_status_t ataflop_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				     स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा atari_floppy_काष्ठा *floppy = bd->rq->rq_disk->निजी_data;
	पूर्णांक drive = floppy - unit;
	पूर्णांक type = floppy->type;

	spin_lock_irq(&ataflop_lock);
	अगर (fd_request) अणु
		spin_unlock_irq(&ataflop_lock);
		वापस BLK_STS_DEV_RESOURCE;
	पूर्ण
	अगर (!stdma_try_lock(floppy_irq, शून्य))  अणु
		spin_unlock_irq(&ataflop_lock);
		वापस BLK_STS_RESOURCE;
	पूर्ण
	fd_request = bd->rq;
	blk_mq_start_request(fd_request);

	atari_disable_irq( IRQ_MFP_FDC );

	IsFormatting = 0;

	अगर (!UD.connected) अणु
		/* drive not connected */
		prपूर्णांकk(KERN_ERR "Unknown Device: fd%d\n", drive );
		fd_end_request_cur(BLK_STS_IOERR);
		जाओ out;
	पूर्ण
		
	अगर (type == 0) अणु
		अगर (!UDT) अणु
			Probing = 1;
			UDT = atari_disk_type + StartDiskType[DriveType];
			set_capacity(bd->rq->rq_disk, UDT->blocks);
			UD.स्वतःprobe = 1;
		पूर्ण
	पूर्ण 
	अन्यथा अणु
		/* user supplied disk type */
		अगर (--type >= NUM_DISK_MINORS) अणु
			prपूर्णांकk(KERN_WARNING "fd%d: invalid disk format", drive );
			fd_end_request_cur(BLK_STS_IOERR);
			जाओ out;
		पूर्ण
		अगर (minor2disktype[type].drive_types > DriveType)  अणु
			prपूर्णांकk(KERN_WARNING "fd%d: unsupported disk format", drive );
			fd_end_request_cur(BLK_STS_IOERR);
			जाओ out;
		पूर्ण
		type = minor2disktype[type].index;
		UDT = &atari_disk_type[type];
		set_capacity(bd->rq->rq_disk, UDT->blocks);
		UD.स्वतःprobe = 0;
	पूर्ण

	/* stop deselect समयr */
	del_समयr( &motor_off_समयr );
		
	ReqCnt = 0;
	ReqCmd = rq_data_dir(fd_request);
	ReqBlock = blk_rq_pos(fd_request);
	ReqBuffer = bio_data(fd_request->bio);
	setup_req_params( drive );
	करो_fd_action( drive );

	अगर (bd->last)
		finish_fdc();
	atari_enable_irq( IRQ_MFP_FDC );

out:
	spin_unlock_irq(&ataflop_lock);
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक fd_locked_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा atari_floppy_काष्ठा *floppy = disk->निजी_data;
	पूर्णांक drive = floppy - unit;
	पूर्णांक type = floppy->type;
	काष्ठा atari_क्रमmat_descr fmt_desc;
	काष्ठा atari_disk_type *dtp;
	काष्ठा floppy_काष्ठा getprm;
	पूर्णांक settype;
	काष्ठा floppy_काष्ठा setprm;
	व्योम __user *argp = (व्योम __user *)param;

	चयन (cmd) अणु
	हाल FDGETPRM:
		अगर (type) अणु
			अगर (--type >= NUM_DISK_MINORS)
				वापस -ENODEV;
			अगर (minor2disktype[type].drive_types > DriveType)
				वापस -ENODEV;
			type = minor2disktype[type].index;
			dtp = &atari_disk_type[type];
			अगर (UD.flags & FTD_MSG)
			    prपूर्णांकk (KERN_ERR "floppy%d: found dtp %p name %s!\n",
			        drive, dtp, dtp->name);
		पूर्ण
		अन्यथा अणु
			अगर (!UDT)
				वापस -ENXIO;
			अन्यथा
				dtp = UDT;
		पूर्ण
		स_रखो((व्योम *)&getprm, 0, माप(getprm));
		getprm.size = dtp->blocks;
		getprm.sect = dtp->spt;
		getprm.head = 2;
		getprm.track = dtp->blocks/dtp->spt/2;
		getprm.stretch = dtp->stretch;
		अगर (copy_to_user(argp, &getprm, माप(getprm)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	चयन (cmd) अणु
	हाल FDSETPRM:
	हाल FDDEFPRM:
	        /* 
		 * MSch 7/96: simple 'set geometry' हाल: just set the
		 * 'default' device params (minor == 0).
		 * Currently, the drive geometry is cleared after each
		 * disk change and subsequent revalidate()! simple
		 * implementation of FDDEFPRM: save geometry from a
		 * FDDEFPRM call and restore it in floppy_revalidate() !
		 */

		/* get the parameters from user space */
		अगर (floppy->ref != 1 && floppy->ref != -1)
			वापस -EBUSY;
		अगर (copy_from_user(&setprm, argp, माप(setprm)))
			वापस -EFAULT;
		/* 
		 * first of all: check क्रम floppy change and revalidate, 
		 * or the next access will revalidate - and clear UDT :-(
		 */

		अगर (floppy_check_events(disk, 0))
		        floppy_revalidate(disk);

		अगर (UD.flags & FTD_MSG)
		    prपूर्णांकk (KERN_INFO "floppy%d: setting size %d spt %d str %d!\n",
			drive, setprm.size, setprm.sect, setprm.stretch);

		/* what अगर type > 0 here? Overग_लिखो specअगरied entry ? */
		अगर (type) अणु
		        /* refuse to re-set a predefined type क्रम now */
			वापस -EINVAL;
		पूर्ण

		/* 
		 * type == 0: first look क्रम a matching entry in the type list,
		 * and set the UD.disktype field to use the perdefined entry.
		 * TODO: add user-defined क्रमmat to head of स्वतःprobe list ? 
		 * Useful to include the user-type क्रम future स्वतःdetection!
		 */

		क्रम (settype = 0; settype < NUM_DISK_MINORS; settype++) अणु
			पूर्णांक setidx = 0;
			अगर (minor2disktype[settype].drive_types > DriveType) अणु
				/* skip this one, invalid क्रम drive ... */
				जारी;
			पूर्ण
			setidx = minor2disktype[settype].index;
			dtp = &atari_disk_type[setidx];

			/* found matching entry ?? */
			अगर (   dtp->blocks  == setprm.size 
			    && dtp->spt     == setprm.sect
			    && dtp->stretch == setprm.stretch ) अणु
				अगर (UD.flags & FTD_MSG)
				    prपूर्णांकk (KERN_INFO "floppy%d: setting %s %p!\n",
				        drive, dtp->name, dtp);
				UDT = dtp;
				set_capacity(disk, UDT->blocks);

				अगर (cmd == FDDEFPRM) अणु
				  /* save settings as permanent शेष type */
				  शेष_params[drive].name    = dtp->name;
				  शेष_params[drive].spt     = dtp->spt;
				  शेष_params[drive].blocks  = dtp->blocks;
				  शेष_params[drive].fdc_speed = dtp->fdc_speed;
				  शेष_params[drive].stretch = dtp->stretch;
				पूर्ण
				
				वापस 0;
			पूर्ण

		पूर्ण

		/* no matching disk type found above - setting user_params */

	       	अगर (cmd == FDDEFPRM) अणु
			/* set permanent type */
			dtp = &शेष_params[drive];
		पूर्ण अन्यथा
			/* set user type (reset by disk change!) */
			dtp = &user_params[drive];

		dtp->name   = "user format";
		dtp->blocks = setprm.size;
		dtp->spt    = setprm.sect;
		अगर (setprm.sect > 14) 
			dtp->fdc_speed = 3;
		अन्यथा
			dtp->fdc_speed = 0;
		dtp->stretch = setprm.stretch;

		अगर (UD.flags & FTD_MSG)
			prपूर्णांकk (KERN_INFO "floppy%d: blk %d spt %d str %d!\n",
				drive, dtp->blocks, dtp->spt, dtp->stretch);

		/* sanity check */
		अगर (setprm.track != dtp->blocks/dtp->spt/2 ||
		    setprm.head != 2)
			वापस -EINVAL;

		UDT = dtp;
		set_capacity(disk, UDT->blocks);

		वापस 0;
	हाल FDMSGON:
		UD.flags |= FTD_MSG;
		वापस 0;
	हाल FDMSGOFF:
		UD.flags &= ~FTD_MSG;
		वापस 0;
	हाल FDSETEMSGTRESH:
		वापस -EINVAL;
	हाल FDFMTBEG:
		वापस 0;
	हाल FDFMTTRK:
		अगर (floppy->ref != 1 && floppy->ref != -1)
			वापस -EBUSY;
		अगर (copy_from_user(&fmt_desc, argp, माप(fmt_desc)))
			वापस -EFAULT;
		वापस करो_क्रमmat(drive, type, &fmt_desc);
	हाल FDCLRPRM:
		UDT = शून्य;
		/* MSch: invalidate शेष_params */
		शेष_params[drive].blocks  = 0;
		set_capacity(disk, MAX_DISK_SIZE * 2);
		fallthrough;
	हाल FDFMTEND:
	हाल FDFLUSH:
		/* invalidate the buffer track to क्रमce a reपढ़ो */
		BufferDrive = -1;
		set_bit(drive, &fake_change);
		अगर (bdev_check_media_change(bdev))
			floppy_revalidate(bdev->bd_disk);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक fd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&ataflop_mutex);
	ret = fd_locked_ioctl(bdev, mode, cmd, arg);
	mutex_unlock(&ataflop_mutex);

	वापस ret;
पूर्ण

/* Initialize the 'unit' variable for drive 'drive' */

अटल व्योम __init fd_probe( पूर्णांक drive )
अणु
	UD.connected = 0;
	UDT  = शून्य;

	अगर (!fd_test_drive_present( drive ))
		वापस;

	UD.connected = 1;
	UD.track     = 0;
	चयन( UserSteprate[drive] ) अणु
	हाल 2:
		UD.steprate = FDCSTEP_2;
		अवरोध;
	हाल 3:
		UD.steprate = FDCSTEP_3;
		अवरोध;
	हाल 6:
		UD.steprate = FDCSTEP_6;
		अवरोध;
	हाल 12:
		UD.steprate = FDCSTEP_12;
		अवरोध;
	शेष: /* should be -1 क्रम "not set by user" */
		अगर (ATARIHW_PRESENT( FDCSPEED ) || MACH_IS_MEDUSA)
			UD.steprate = FDCSTEP_3;
		अन्यथा
			UD.steprate = FDCSTEP_6;
		अवरोध;
	पूर्ण
	MotorOn = 1;	/* from probe restore operation! */
पूर्ण


/* This function tests the physical presence of a floppy drive (not
 * whether a disk is inserted). This is करोne by issuing a restore
 * command, रुकोing max. 2 seconds (that should be enough to move the
 * head across the whole disk) and looking at the state of the "TR00"
 * संकेत. This should now be उठाओd अगर there is a drive connected
 * (and there is no hardware failure :-) Otherwise, the drive is
 * declared असलent.
 */

अटल पूर्णांक __init fd_test_drive_present( पूर्णांक drive )
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित अक्षर status;
	पूर्णांक ok;
	
	अगर (drive >= (MACH_IS_FALCON ? 1 : 2)) वापस( 0 );
	fd_select_drive( drive );

	/* disable पूर्णांकerrupt temporarily */
	atari_turnoff_irq( IRQ_MFP_FDC );
	FDC_WRITE (FDCREG_TRACK, 0xff00);
	FDC_WRITE( FDCREG_CMD, FDCCMD_RESTORE | FDCCMDADD_H | FDCSTEP_6 );

	समयout = jअगरfies + 2*HZ+HZ/2;
	जबतक (समय_beक्रमe(jअगरfies, समयout))
		अगर (!(st_mfp.par_dt_reg & 0x20))
			अवरोध;

	status = FDC_READ( FDCREG_STATUS );
	ok = (status & FDCSTAT_TR00) != 0;

	/* क्रमce पूर्णांकerrupt to पात restore operation (FDC would try
	 * about 50 seconds!) */
	FDC_WRITE( FDCREG_CMD, FDCCMD_FORCI );
	udelay(500);
	status = FDC_READ( FDCREG_STATUS );
	udelay(20);

	अगर (ok) अणु
		/* dummy seek command to make WP bit accessible */
		FDC_WRITE( FDCREG_DATA, 0 );
		FDC_WRITE( FDCREG_CMD, FDCCMD_SEEK );
		जबतक( st_mfp.par_dt_reg & 0x20 )
			;
		status = FDC_READ( FDCREG_STATUS );
	पूर्ण

	atari_turnon_irq( IRQ_MFP_FDC );
	वापस( ok );
पूर्ण


/* Look how many and which kind of drives are connected. If there are
 * floppies, additionally start the disk-change and motor-off समयrs.
 */

अटल व्योम __init config_types( व्योम )
अणु
	पूर्णांक drive, cnt = 0;

	/* क्रम probing drives, set the FDC speed to 8 MHz */
	अगर (ATARIHW_PRESENT(FDCSPEED))
		dma_wd.fdc_speed = 0;

	prपूर्णांकk(KERN_INFO "Probing floppy drive(s):\n");
	क्रम( drive = 0; drive < FD_MAX_UNITS; drive++ ) अणु
		fd_probe( drive );
		अगर (UD.connected) अणु
			prपूर्णांकk(KERN_INFO "fd%d\n", drive);
			++cnt;
		पूर्ण
	पूर्ण

	अगर (FDC_READ( FDCREG_STATUS ) & FDCSTAT_BUSY) अणु
		/* If FDC is still busy from probing, give it another FORCI
		 * command to पात the operation. If this isn't करोne, the FDC
		 * will पूर्णांकerrupt later and its IRQ line stays low, because
		 * the status रेजिस्टर isn't पढ़ो. And this will block any
		 * पूर्णांकerrupts on this IRQ line :-(
		 */
		FDC_WRITE( FDCREG_CMD, FDCCMD_FORCI );
		udelay(500);
		FDC_READ( FDCREG_STATUS );
		udelay(20);
	पूर्ण
	
	अगर (cnt > 0) अणु
		start_motor_off_समयr();
		अगर (cnt == 1) fd_select_drive( 0 );
		start_check_change_समयr();
	पूर्ण
पूर्ण

/*
 * floppy_खोलो check क्रम aliasing (/dev/fd0 can be the same as
 * /dev/PS0 etc), and disallows simultaneous access to the same
 * drive with dअगरferent device numbers.
 */

अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा atari_floppy_काष्ठा *p = bdev->bd_disk->निजी_data;
	पूर्णांक type  = MINOR(bdev->bd_dev) >> 2;

	DPRINT(("fd_open: type=%d\n",type));
	अगर (p->ref && p->type != type)
		वापस -EBUSY;

	अगर (p->ref == -1 || (p->ref && mode & FMODE_EXCL))
		वापस -EBUSY;

	अगर (mode & FMODE_EXCL)
		p->ref = -1;
	अन्यथा
		p->ref++;

	p->type = type;

	अगर (mode & FMODE_NDELAY)
		वापस 0;

	अगर (mode & (FMODE_READ|FMODE_WRITE)) अणु
		अगर (bdev_check_media_change(bdev))
			floppy_revalidate(bdev->bd_disk);
		अगर (mode & FMODE_WRITE) अणु
			अगर (p->wpstat) अणु
				अगर (p->ref < 0)
					p->ref = 0;
				अन्यथा
					p->ref--;
				वापस -EROFS;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक floppy_unlocked_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक ret;

	mutex_lock(&ataflop_mutex);
	ret = floppy_खोलो(bdev, mode);
	mutex_unlock(&ataflop_mutex);

	वापस ret;
पूर्ण

अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा atari_floppy_काष्ठा *p = disk->निजी_data;
	mutex_lock(&ataflop_mutex);
	अगर (p->ref < 0)
		p->ref = 0;
	अन्यथा अगर (!p->ref--) अणु
		prपूर्णांकk(KERN_ERR "floppy_release with fd_ref == 0");
		p->ref = 0;
	पूर्ण
	mutex_unlock(&ataflop_mutex);
पूर्ण

अटल स्थिर काष्ठा block_device_operations floppy_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= floppy_unlocked_खोलो,
	.release	= floppy_release,
	.ioctl		= fd_ioctl,
	.check_events	= floppy_check_events,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops ataflop_mq_ops = अणु
	.queue_rq = ataflop_queue_rq,
	.commit_rqs = ataflop_commit_rqs,
पूर्ण;

अटल पूर्णांक ataflop_alloc_disk(अचिन्हित पूर्णांक drive, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gendisk *disk;
	पूर्णांक ret;

	disk = alloc_disk(1);
	अगर (!disk)
		वापस -ENOMEM;

	disk->queue = blk_mq_init_queue(&unit[drive].tag_set);
	अगर (IS_ERR(disk->queue)) अणु
		ret = PTR_ERR(disk->queue);
		disk->queue = शून्य;
		put_disk(disk);
		वापस ret;
	पूर्ण

	disk->major = FLOPPY_MAJOR;
	disk->first_minor = drive + (type << 2);
	प्र_लिखो(disk->disk_name, "fd%d", drive);
	disk->fops = &floppy_fops;
	disk->events = DISK_EVENT_MEDIA_CHANGE;
	disk->निजी_data = &unit[drive];
	set_capacity(disk, MAX_DISK_SIZE * 2);

	unit[drive].disk[type] = disk;
	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(ataflop_probe_lock);

अटल व्योम ataflop_probe(dev_t dev)
अणु
	पूर्णांक drive = MINOR(dev) & 3;
	पूर्णांक type  = MINOR(dev) >> 2;

	अगर (type)
		type--;

	अगर (drive >= FD_MAX_UNITS || type >= NUM_DISK_MINORS)
		वापस;
	mutex_lock(&ataflop_probe_lock);
	अगर (!unit[drive].disk[type]) अणु
		अगर (ataflop_alloc_disk(drive, type) == 0)
			add_disk(unit[drive].disk[type]);
	पूर्ण
	mutex_unlock(&ataflop_probe_lock);
पूर्ण

अटल पूर्णांक __init atari_floppy_init (व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!MACH_IS_ATARI)
		/* Amiga, Mac, ... करोn't have Atari-compatible floppy :-) */
		वापस -ENODEV;

	mutex_lock(&ataflop_probe_lock);
	ret = __रेजिस्टर_blkdev(FLOPPY_MAJOR, "fd", ataflop_probe);
	अगर (ret)
		जाओ out_unlock;

	क्रम (i = 0; i < FD_MAX_UNITS; i++) अणु
		स_रखो(&unit[i].tag_set, 0, माप(unit[i].tag_set));
		unit[i].tag_set.ops = &ataflop_mq_ops;
		unit[i].tag_set.nr_hw_queues = 1;
		unit[i].tag_set.nr_maps = 1;
		unit[i].tag_set.queue_depth = 2;
		unit[i].tag_set.numa_node = NUMA_NO_NODE;
		unit[i].tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
		ret = blk_mq_alloc_tag_set(&unit[i].tag_set);
		अगर (ret)
			जाओ err;

		ret = ataflop_alloc_disk(i, 0);
		अगर (ret) अणु
			blk_mq_मुक्त_tag_set(&unit[i].tag_set);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (UseTrackbuffer < 0)
		/* not set by user -> use शेष: क्रम now, we turn
		   track buffering off क्रम all Medusas, though it
		   could be used with ones that have a counter
		   card. But the test is too hard :-( */
		UseTrackbuffer = !MACH_IS_MEDUSA;

	/* initialize variables */
	SelectedDrive = -1;
	BufferDrive = -1;

	DMABuffer = atari_stram_alloc(BUFFER_SIZE+512, "ataflop");
	अगर (!DMABuffer) अणु
		prपूर्णांकk(KERN_ERR "atari_floppy_init: cannot get dma buffer\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	TrackBuffer = DMABuffer + 512;
	PhysDMABuffer = atari_stram_to_phys(DMABuffer);
	PhysTrackBuffer = virt_to_phys(TrackBuffer);
	BufferDrive = BufferSide = BufferTrack = -1;

	क्रम (i = 0; i < FD_MAX_UNITS; i++) अणु
		unit[i].track = -1;
		unit[i].flags = 0;
		add_disk(unit[i].disk[0]);
	पूर्ण

	prपूर्णांकk(KERN_INFO "Atari floppy driver: max. %cD, %strack buffering\n",
	       DriveType == 0 ? 'D' : DriveType == 1 ? 'H' : 'E',
	       UseTrackbuffer ? "" : "no ");
	config_types();

	वापस 0;

err:
	जबतक (--i >= 0) अणु
		blk_cleanup_queue(unit[i].disk[0]->queue);
		put_disk(unit[i].disk[0]);
		blk_mq_मुक्त_tag_set(&unit[i].tag_set);
	पूर्ण

	unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
out_unlock:
	mutex_unlock(&ataflop_probe_lock);
	वापस ret;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init atari_floppy_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[3 + FD_MAX_UNITS];
	पूर्णांक i;

	अगर (!MACH_IS_ATARI)
		वापस 0;

	str = get_options(str, 3 + FD_MAX_UNITS, पूर्णांकs);
	
	अगर (पूर्णांकs[0] < 1) अणु
		prपूर्णांकk(KERN_ERR "ataflop_setup: no arguments!\n" );
		वापस 0;
	पूर्ण
	अन्यथा अगर (पूर्णांकs[0] > 2+FD_MAX_UNITS) अणु
		prपूर्णांकk(KERN_ERR "ataflop_setup: too many arguments\n" );
	पूर्ण

	अगर (पूर्णांकs[1] < 0 || पूर्णांकs[1] > 2)
		prपूर्णांकk(KERN_ERR "ataflop_setup: bad drive type\n" );
	अन्यथा
		DriveType = पूर्णांकs[1];

	अगर (पूर्णांकs[0] >= 2)
		UseTrackbuffer = (पूर्णांकs[2] > 0);

	क्रम( i = 3; i <= पूर्णांकs[0] && i-3 < FD_MAX_UNITS; ++i ) अणु
		अगर (पूर्णांकs[i] != 2 && पूर्णांकs[i] != 3 && पूर्णांकs[i] != 6 && पूर्णांकs[i] != 12)
			prपूर्णांकk(KERN_ERR "ataflop_setup: bad steprate\n" );
		अन्यथा
			UserSteprate[i-3] = पूर्णांकs[i];
	पूर्ण
	वापस 1;
पूर्ण

__setup("floppy=", atari_floppy_setup);
#पूर्ण_अगर

अटल व्योम __निकास atari_floppy_निकास(व्योम)
अणु
	पूर्णांक i, type;

	क्रम (i = 0; i < FD_MAX_UNITS; i++) अणु
		क्रम (type = 0; type < NUM_DISK_MINORS; type++) अणु
			अगर (!unit[i].disk[type])
				जारी;
			del_gendisk(unit[i].disk[type]);
			blk_cleanup_queue(unit[i].disk[type]->queue);
			put_disk(unit[i].disk[type]);
		पूर्ण
		blk_mq_मुक्त_tag_set(&unit[i].tag_set);
	पूर्ण
	unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");

	del_समयr_sync(&fd_समयr);
	atari_stram_मुक्त( DMABuffer );
पूर्ण

module_init(atari_floppy_init)
module_निकास(atari_floppy_निकास)

MODULE_LICENSE("GPL");
