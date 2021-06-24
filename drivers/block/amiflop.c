<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/amiga/amअगरlop.c
 *
 *  Copyright (C) 1993  Greg Harp
 *  Portions of this driver are based on code contributed by Brad Pepers
 *  
 *  revised 28.5.95 by Joerg Dorchain
 *  - now no bugs(?) any more क्रम both HD & DD
 *  - added support क्रम 40 Track 5.25" drives, 80-track hopefully behaves
 *    like 3.5" dd (no way to test - are there any 5.25" drives out there
 *    that work on an A4000?)
 *  - wrote क्रमmatting routine (maybe dirty, but works)
 *
 *  june/july 1995 added ms-करोs support by Joerg Dorchain
 *  (portions based on messyकरोs.device and various contributors)
 *  - currently only 9 and 18 sector disks
 *
 *  - fixed a bug with the पूर्णांकernal trackbuffer when using multiple 
 *    disks the same समय
 *  - made क्रमmatting a bit safer
 *  - added command line and machine based शेष क्रम "silent" df0
 *
 *  december 1995 adapted क्रम 1.2.13pl4 by Joerg Dorchain
 *  - works but I think it's inefficient. (look in reकरो_fd_request)
 *    But the changes were very efficient. (only three and a half lines)
 *
 *  january 1996 added special ioctl क्रम tracking करोwn पढ़ो/ग_लिखो problems
 *  - usage ioctl(d, RAW_TRACK, ptr); the raw track buffer (MFM-encoded data
 *    is copied to area. (area should be large enough since no checking is
 *    करोne - 30K is currently sufficient). वापस the actual size of the
 *    trackbuffer
 *  - replaced udelays() by a समयr (CIAA समयr B) क्रम the रुकोs 
 *    needed क्रम the disk mechanic.
 *
 *  february 1996 fixed error recovery and multiple disk access
 *  - both got broken the first समय I tampered with the driver :-(
 *  - still not safe, but better than beक्रमe
 *
 *  revised Marts 3rd, 1996 by Jes Sorensen क्रम use in the 1.3.28 kernel.
 *  - Minor changes to accept the kdev_t.
 *  - Replaced some more udelays with ms_delays. Udelay is just a loop,
 *    and so the delay will be dअगरferent depending on the given
 *    processor :-(
 *  - The driver could use a major cleanup because of the new
 *    major/minor handling that came with kdev_t. It seems to work क्रम
 *    the समय being, but I can't guarantee that it will stay like
 *    that when we start using 16 (24?) bit minors.
 *
 * reकाष्ठाured jan 1997 by Joerg Dorchain
 * - Fixed Bug accessing multiple disks
 * - some code cleanup
 * - added trackbuffer क्रम each drive to speed things up
 * - fixed some race conditions (who finds the next may send it to me ;-)
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/fd.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/elevator.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/irq.h>

#अघोषित DEBUG /* prपूर्णांक _LOTS_ of infos */

#घोषणा RAW_IOCTL
#अगर_घोषित RAW_IOCTL
#घोषणा IOCTL_RAW_TRACK 0x5254524B  /* 'RTRK' */
#पूर्ण_अगर

/*
 *  Defines
 */

/*
 * CIAAPRA bits (पढ़ो only)
 */

#घोषणा DSKRDY      (0x1<<5)        /* disk पढ़ोy when low */
#घोषणा DSKTRACK0   (0x1<<4)        /* head at track zero when low */
#घोषणा DSKPROT     (0x1<<3)        /* disk रक्षित when low */
#घोषणा DSKCHANGE   (0x1<<2)        /* low when disk हटाओd */

/*
 * CIAAPRB bits (पढ़ो/ग_लिखो)
 */

#घोषणा DSKMOTOR    (0x1<<7)        /* motor on when low */
#घोषणा DSKSEL3     (0x1<<6)        /* select drive 3 when low */
#घोषणा DSKSEL2     (0x1<<5)        /* select drive 2 when low */
#घोषणा DSKSEL1     (0x1<<4)        /* select drive 1 when low */
#घोषणा DSKSEL0     (0x1<<3)        /* select drive 0 when low */
#घोषणा DSKSIDE     (0x1<<2)        /* side selection: 0 = upper, 1 = lower */
#घोषणा DSKसूचीEC    (0x1<<1)        /* step direction: 0=in, 1=out (to trk 0) */
#घोषणा DSKSTEP     (0x1)           /* pulse low to step head 1 track */

/*
 * DSKBYTR bits (पढ़ो only)
 */

#घोषणा DSKBYT      (1<<15)         /* रेजिस्टर contains valid byte when set */
#घोषणा DMAON       (1<<14)         /* disk DMA enabled */
#घोषणा DISKWRITE   (1<<13)         /* disk ग_लिखो bit in DSKLEN enabled */
#घोषणा WORDEQUAL   (1<<12)         /* DSKSYNC रेजिस्टर match when true */
/* bits 7-0 are data */

/*
 * ADKCON/ADKCONR bits
 */

#अगर_अघोषित SETCLR
#घोषणा ADK_SETCLR      (1<<15)     /* control bit */
#पूर्ण_अगर
#घोषणा ADK_PRECOMP1    (1<<14)     /* precompensation selection */
#घोषणा ADK_PRECOMP0    (1<<13)     /* 00=none, 01=140ns, 10=280ns, 11=500ns */
#घोषणा ADK_MFMPREC     (1<<12)     /* 0=GCR precomp., 1=MFM precomp. */
#घोषणा ADK_WORDSYNC    (1<<10)     /* enable DSKSYNC स्वतः DMA */
#घोषणा ADK_MSBSYNC     (1<<9)      /* when 1, enable sync on MSbit (क्रम GCR) */
#घोषणा ADK_FAST        (1<<8)      /* bit cell: 0=2us (GCR), 1=1us (MFM) */

/*
 * DSKLEN bits
 */

#घोषणा DSKLEN_DMAEN    (1<<15)
#घोषणा DSKLEN_WRITE    (1<<14)

/*
 * INTENA/INTREQ bits
 */

#घोषणा DSKINDEX    (0x1<<4)        /* DSKINDEX bit */

/*
 * Misc
 */

#घोषणा MFM_SYNC    0x4489          /* standard MFM sync value */

/* Values क्रम FD_COMMAND */
#घोषणा FD_RECALIBRATE		0x07	/* move to track 0 */
#घोषणा FD_SEEK			0x0F	/* seek track */
#घोषणा FD_READ			0xE6	/* पढ़ो with MT, MFM, SKip deleted */
#घोषणा FD_WRITE		0xC5	/* ग_लिखो with MT, MFM */
#घोषणा FD_SENSEI		0x08	/* Sense Interrupt Status */
#घोषणा FD_SPECIFY		0x03	/* specअगरy HUT etc */
#घोषणा FD_FORMAT		0x4D	/* क्रमmat one track */
#घोषणा FD_VERSION		0x10	/* get version code */
#घोषणा FD_CONFIGURE		0x13	/* configure FIFO operation */
#घोषणा FD_PERPENDICULAR	0x12	/* perpendicular r/w mode */

#घोषणा FD_MAX_UNITS    4	/* Max. Number of drives */
#घोषणा FLOPPY_MAX_SECTORS	22	/* Max. Number of sectors per track */

काष्ठा fd_data_type अणु
	अक्षर *name;		/* description of data type */
	पूर्णांक sects;		/* sectors per track */
	पूर्णांक (*पढ़ो_fkt)(पूर्णांक);	/* पढ़ो whole track */
	व्योम (*ग_लिखो_fkt)(पूर्णांक);	/* ग_लिखो whole track */
पूर्ण;

काष्ठा fd_drive_type अणु
	अचिन्हित दीर्घ code;		/* code वापसed from drive */
	अक्षर *name;			/* description of drive */
	अचिन्हित पूर्णांक tracks;	/* number of tracks */
	अचिन्हित पूर्णांक heads;		/* number of heads */
	अचिन्हित पूर्णांक पढ़ो_size;	/* raw पढ़ो size क्रम one track */
	अचिन्हित पूर्णांक ग_लिखो_size;	/* raw ग_लिखो size क्रम one track */
	अचिन्हित पूर्णांक sect_mult;	/* sectors and gap multiplier (HD = 2) */
	अचिन्हित पूर्णांक precomp1;	/* start track क्रम precomp 1 */
	अचिन्हित पूर्णांक precomp2;	/* start track क्रम precomp 2 */
	अचिन्हित पूर्णांक step_delay;	/* समय (in ms) क्रम delay after step */
	अचिन्हित पूर्णांक settle_समय;	/* समय to settle after dir change */
	अचिन्हित पूर्णांक side_समय;	/* समय needed to change sides */
पूर्ण;

काष्ठा amiga_floppy_काष्ठा अणु
	काष्ठा fd_drive_type *type;	/* type of floppy क्रम this unit */
	काष्ठा fd_data_type *dtype;	/* type of floppy क्रम this unit */
	पूर्णांक track;			/* current track (-1 == unknown) */
	अचिन्हित अक्षर *trackbuf;	/* current track (kmaloc()'d */

	पूर्णांक blocks;			/* total # blocks on disk */

	पूर्णांक changed;			/* true when not known */
	पूर्णांक disk;			/* disk in drive (-1 == unknown) */
	पूर्णांक motor;			/* true when motor is at speed */
	पूर्णांक busy;			/* true when drive is active */
	पूर्णांक dirty;			/* true when trackbuf is not on disk */
	पूर्णांक status;			/* current error code क्रम unit */
	काष्ठा gendisk *gendisk[2];
	काष्ठा blk_mq_tag_set tag_set;
पूर्ण;

/*
 *  Error codes
 */
#घोषणा FD_OK		0	/* operation succeeded */
#घोषणा FD_ERROR	-1	/* general error (seek, पढ़ो, ग_लिखो, etc) */
#घोषणा FD_NOUNIT	1	/* unit करोes not exist */
#घोषणा FD_UNITBUSY	2	/* unit alपढ़ोy active */
#घोषणा FD_NOTACTIVE	3	/* unit is not active */
#घोषणा FD_NOTREADY	4	/* unit is not पढ़ोy (motor not on/no disk) */

#घोषणा MFM_NOSYNC	1
#घोषणा MFM_HEADER	2
#घोषणा MFM_DATA	3
#घोषणा MFM_TRACK	4

/*
 *  Floppy ID values
 */
#घोषणा FD_NODRIVE	0x00000000  /* response when no unit is present */
#घोषणा FD_DD_3 	0xffffffff  /* द्विगुन-density 3.5" (880K) drive */
#घोषणा FD_HD_3 	0x55555555  /* high-density 3.5" (1760K) drive */
#घोषणा FD_DD_5 	0xaaaaaaaa  /* द्विगुन-density 5.25" (440K) drive */

अटल DEFINE_MUTEX(amअगरlop_mutex);
अटल अचिन्हित दीर्घ पूर्णांक fd_def_df0 = FD_DD_3;     /* शेष क्रम df0 अगर it करोesn't identअगरy */

module_param(fd_def_df0, uदीर्घ, 0);
MODULE_LICENSE("GPL");

/*
 *  Macros
 */
#घोषणा MOTOR_ON	(ciab.prb &= ~DSKMOTOR)
#घोषणा MOTOR_OFF	(ciab.prb |= DSKMOTOR)
#घोषणा SELECT(mask)    (ciab.prb &= ~mask)
#घोषणा DESELECT(mask)  (ciab.prb |= mask)
#घोषणा SELMASK(drive)  (1 << (3 + (drive & 3)))

अटल काष्ठा fd_drive_type drive_types[] = अणु
/*  code	name	   tr he   rdsz   wrsz sm pc1 pc2 sd  st st*/
/*  warning: बार are now in milliseconds (ms)                    */
अणु FD_DD_3,	"DD 3.5",  80, 2, 14716, 13630, 1, 80,161, 3, 18, 1पूर्ण,
अणु FD_HD_3,	"HD 3.5",  80, 2, 28344, 27258, 2, 80,161, 3, 18, 1पूर्ण,
अणु FD_DD_5,	"DD 5.25", 40, 2, 14716, 13630, 1, 40, 81, 6, 30, 2पूर्ण,
अणु FD_NODRIVE, "No Drive", 0, 0,     0,     0, 0,  0,  0,  0,  0, 0पूर्ण
पूर्ण;
अटल पूर्णांक num_dr_types = ARRAY_SIZE(drive_types);

अटल पूर्णांक amiga_पढ़ो(पूर्णांक), करोs_पढ़ो(पूर्णांक);
अटल व्योम amiga_ग_लिखो(पूर्णांक), करोs_ग_लिखो(पूर्णांक);
अटल काष्ठा fd_data_type data_types[] = अणु
	अणु "Amiga", 11 , amiga_पढ़ो, amiga_ग_लिखोपूर्ण,
	अणु "MS-Dos", 9, करोs_पढ़ो, करोs_ग_लिखोपूर्ण
पूर्ण;

/* current info on each unit */
अटल काष्ठा amiga_floppy_काष्ठा unit[FD_MAX_UNITS];

अटल काष्ठा समयr_list flush_track_समयr[FD_MAX_UNITS];
अटल काष्ठा समयr_list post_ग_लिखो_समयr;
अटल अचिन्हित दीर्घ post_ग_लिखो_समयr_drive;
अटल काष्ठा समयr_list motor_on_समयr;
अटल काष्ठा समयr_list motor_off_समयr[FD_MAX_UNITS];
अटल पूर्णांक on_attempts;

/* Synchronization of FDC access */
/* request loop (trackbuffer) */
अटल अस्थिर पूर्णांक fdc_busy = -1;
अटल अस्थिर पूर्णांक fdc_nested;
अटल DECLARE_WAIT_QUEUE_HEAD(fdc_रुको);
 
अटल DECLARE_COMPLETION(motor_on_completion);

अटल अस्थिर पूर्णांक selected = -1;	/* currently selected drive */

अटल पूर्णांक ग_लिखोpending;
अटल पूर्णांक ग_लिखोfromपूर्णांक;
अटल अक्षर *raw_buf;

अटल DEFINE_SPINLOCK(amअगरlop_lock);

#घोषणा RAW_BUF_SIZE 30000  /* size of raw disk data */

/*
 * These are global variables, as that's the easiest way to give
 * inक्रमmation to पूर्णांकerrupts. They are the data used क्रम the current
 * request.
 */
अटल अस्थिर अक्षर block_flag;
अटल DECLARE_WAIT_QUEUE_HEAD(रुको_fd_block);

/* MS-Dos MFM Coding tables (should go quick and easy) */
अटल अचिन्हित अक्षर mfmencode[16]=अणु
	0x2a, 0x29, 0x24, 0x25, 0x12, 0x11, 0x14, 0x15,
	0x4a, 0x49, 0x44, 0x45, 0x52, 0x51, 0x54, 0x55
पूर्ण;
अटल अचिन्हित अक्षर mfmdecode[128];

/* floppy पूर्णांकernal millisecond समयr stuff */
अटल DECLARE_COMPLETION(ms_रुको_completion);
#घोषणा MS_TICKS ((amiga_eघड़ी+50)/1000)

/*
 * Note that MAX_ERRORS=X करोesn't imply that we retry every bad पढ़ो
 * max X बार - some types of errors increase the errorcount by 2 or
 * even 3, so we might actually retry only X/2 बार beक्रमe giving up.
 */
#घोषणा MAX_ERRORS 12

#घोषणा custom amiga_custom

/* Prevent "aliased" accesses. */
अटल पूर्णांक fd_ref[4] = अणु 0,0,0,0 पूर्ण;
अटल पूर्णांक fd_device[4] = अणु 0, 0, 0, 0 पूर्ण;

/*
 * Here come the actual hardware access and helper functions.
 * They are not reentrant and single thपढ़ोed because all drives
 * share the same hardware and the same trackbuffer.
 */

/* Milliseconds समयr */

अटल irqवापस_t ms_isr(पूर्णांक irq, व्योम *dummy)
अणु
	complete(&ms_रुको_completion);
	वापस IRQ_HANDLED;
पूर्ण

/* all रुकोs are queued up 
   A more generic routine would करो a schedule a la समयr.device */
अटल व्योम ms_delay(पूर्णांक ms)
अणु
	पूर्णांक ticks;
	अटल DEFINE_MUTEX(mutex);

	अगर (ms > 0) अणु
		mutex_lock(&mutex);
		ticks = MS_TICKS*ms-1;
		ciaa.tblo=ticks%256;
		ciaa.tbhi=ticks/256;
		ciaa.crb=0x19; /*count eघड़ी, क्रमce load, one-shoot, start */
		रुको_क्रम_completion(&ms_रुको_completion);
		mutex_unlock(&mutex);
	पूर्ण
पूर्ण

/* Hardware semaphore */

/* वापसs true when we would get the semaphore */
अटल अंतरभूत पूर्णांक try_fdc(पूर्णांक drive)
अणु
	drive &= 3;
	वापस ((fdc_busy < 0) || (fdc_busy == drive));
पूर्ण

अटल व्योम get_fdc(पूर्णांक drive)
अणु
	अचिन्हित दीर्घ flags;

	drive &= 3;
#अगर_घोषित DEBUG
	prपूर्णांकk("get_fdc: drive %d  fdc_busy %d  fdc_nested %d\n",drive,fdc_busy,fdc_nested);
#पूर्ण_अगर
	local_irq_save(flags);
	रुको_event(fdc_रुको, try_fdc(drive));
	fdc_busy = drive;
	fdc_nested++;
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम rel_fdc(व्योम)
अणु
#अगर_घोषित DEBUG
	अगर (fdc_nested == 0)
		prपूर्णांकk("fd: unmatched rel_fdc\n");
	prपूर्णांकk("rel_fdc: fdc_busy %d fdc_nested %d\n",fdc_busy,fdc_nested);
#पूर्ण_अगर
	fdc_nested--;
	अगर (fdc_nested == 0) अणु
		fdc_busy = -1;
		wake_up(&fdc_रुको);
	पूर्ण
पूर्ण

अटल व्योम fd_select (पूर्णांक drive)
अणु
	अचिन्हित अक्षर prb = ~0;

	drive&=3;
#अगर_घोषित DEBUG
	prपूर्णांकk("selecting %d\n",drive);
#पूर्ण_अगर
	अगर (drive == selected)
		वापस;
	get_fdc(drive);
	selected = drive;

	अगर (unit[drive].track % 2 != 0)
		prb &= ~DSKSIDE;
	अगर (unit[drive].motor == 1)
		prb &= ~DSKMOTOR;
	ciab.prb |= (SELMASK(0)|SELMASK(1)|SELMASK(2)|SELMASK(3));
	ciab.prb = prb;
	prb &= ~SELMASK(drive);
	ciab.prb = prb;
	rel_fdc();
पूर्ण

अटल व्योम fd_deselect (पूर्णांक drive)
अणु
	अचिन्हित अक्षर prb;
	अचिन्हित दीर्घ flags;

	drive&=3;
#अगर_घोषित DEBUG
	prपूर्णांकk("deselecting %d\n",drive);
#पूर्ण_अगर
	अगर (drive != selected) अणु
		prपूर्णांकk(KERN_WARNING "Deselecting drive %d while %d was selected!\n",drive,selected);
		वापस;
	पूर्ण

	get_fdc(drive);
	local_irq_save(flags);

	selected = -1;

	prb = ciab.prb;
	prb |= (SELMASK(0)|SELMASK(1)|SELMASK(2)|SELMASK(3));
	ciab.prb = prb;

	local_irq_restore (flags);
	rel_fdc();

पूर्ण

अटल व्योम motor_on_callback(काष्ठा समयr_list *unused)
अणु
	अगर (!(ciaa.pra & DSKRDY) || --on_attempts == 0) अणु
		complete_all(&motor_on_completion);
	पूर्ण अन्यथा अणु
		motor_on_समयr.expires = jअगरfies + HZ/10;
		add_समयr(&motor_on_समयr);
	पूर्ण
पूर्ण

अटल पूर्णांक fd_motor_on(पूर्णांक nr)
अणु
	nr &= 3;

	del_समयr(motor_off_समयr + nr);

	अगर (!unit[nr].motor) अणु
		unit[nr].motor = 1;
		fd_select(nr);

		reinit_completion(&motor_on_completion);
		mod_समयr(&motor_on_समयr, jअगरfies + HZ/2);

		on_attempts = 10;
		रुको_क्रम_completion(&motor_on_completion);
		fd_deselect(nr);
	पूर्ण

	अगर (on_attempts == 0) अणु
		on_attempts = -1;
#अगर 0
		prपूर्णांकk (KERN_ERR "motor_on failed, turning motor off\n");
		fd_motor_off (motor_off_समयr + nr);
		वापस 0;
#अन्यथा
		prपूर्णांकk (KERN_WARNING "DSKRDY not set after 1.5 seconds - assuming drive is spinning notwithstanding\n");
#पूर्ण_अगर
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम fd_motor_off(काष्ठा समयr_list *समयr)
अणु
	अचिन्हित दीर्घ drive = ((अचिन्हित दीर्घ)समयr -
			       (अचिन्हित दीर्घ)&motor_off_समयr[0]) /
					माप(motor_off_समयr[0]);

	drive&=3;
	अगर (!try_fdc(drive)) अणु
		/* We would be blocked in an पूर्णांकerrupt, so try again later */
		समयr->expires = jअगरfies + 1;
		add_समयr(समयr);
		वापस;
	पूर्ण
	unit[drive].motor = 0;
	fd_select(drive);
	udelay (1);
	fd_deselect(drive);
पूर्ण

अटल व्योम floppy_off (अचिन्हित पूर्णांक nr)
अणु
	पूर्णांक drive;

	drive = nr & 3;
	mod_समयr(motor_off_समयr + drive, jअगरfies + 3*HZ);
पूर्ण

अटल पूर्णांक fd_calibrate(पूर्णांक drive)
अणु
	अचिन्हित अक्षर prb;
	पूर्णांक n;

	drive &= 3;
	get_fdc(drive);
	अगर (!fd_motor_on (drive))
		वापस 0;
	fd_select (drive);
	prb = ciab.prb;
	prb |= DSKSIDE;
	prb &= ~DSKसूचीEC;
	ciab.prb = prb;
	क्रम (n = unit[drive].type->tracks/2; n != 0; --n) अणु
		अगर (ciaa.pra & DSKTRACK0)
			अवरोध;
		prb &= ~DSKSTEP;
		ciab.prb = prb;
		prb |= DSKSTEP;
		udelay (2);
		ciab.prb = prb;
		ms_delay(unit[drive].type->step_delay);
	पूर्ण
	ms_delay (unit[drive].type->settle_समय);
	prb |= DSKसूचीEC;
	n = unit[drive].type->tracks + 20;
	क्रम (;;) अणु
		prb &= ~DSKSTEP;
		ciab.prb = prb;
		prb |= DSKSTEP;
		udelay (2);
		ciab.prb = prb;
		ms_delay(unit[drive].type->step_delay + 1);
		अगर ((ciaa.pra & DSKTRACK0) == 0)
			अवरोध;
		अगर (--n == 0) अणु
			prपूर्णांकk (KERN_ERR "fd%d: calibrate failed, turning motor off\n", drive);
			fd_motor_off (motor_off_समयr + drive);
			unit[drive].track = -1;
			rel_fdc();
			वापस 0;
		पूर्ण
	पूर्ण
	unit[drive].track = 0;
	ms_delay(unit[drive].type->settle_समय);

	rel_fdc();
	fd_deselect(drive);
	वापस 1;
पूर्ण

अटल पूर्णांक fd_seek(पूर्णांक drive, पूर्णांक track)
अणु
	अचिन्हित अक्षर prb;
	पूर्णांक cnt;

#अगर_घोषित DEBUG
	prपूर्णांकk("seeking drive %d to track %d\n",drive,track);
#पूर्ण_अगर
	drive &= 3;
	get_fdc(drive);
	अगर (unit[drive].track == track) अणु
		rel_fdc();
		वापस 1;
	पूर्ण
	अगर (!fd_motor_on(drive)) अणु
		rel_fdc();
		वापस 0;
	पूर्ण
	अगर (unit[drive].track < 0 && !fd_calibrate(drive)) अणु
		rel_fdc();
		वापस 0;
	पूर्ण

	fd_select (drive);
	cnt = unit[drive].track/2 - track/2;
	prb = ciab.prb;
	prb |= DSKSIDE | DSKसूचीEC;
	अगर (track % 2 != 0)
		prb &= ~DSKSIDE;
	अगर (cnt < 0) अणु
		cnt = - cnt;
		prb &= ~DSKसूचीEC;
	पूर्ण
	ciab.prb = prb;
	अगर (track % 2 != unit[drive].track % 2)
		ms_delay (unit[drive].type->side_समय);
	unit[drive].track = track;
	अगर (cnt == 0) अणु
		rel_fdc();
		fd_deselect(drive);
		वापस 1;
	पूर्ण
	करो अणु
		prb &= ~DSKSTEP;
		ciab.prb = prb;
		prb |= DSKSTEP;
		udelay (1);
		ciab.prb = prb;
		ms_delay (unit[drive].type->step_delay);
	पूर्ण जबतक (--cnt != 0);
	ms_delay (unit[drive].type->settle_समय);

	rel_fdc();
	fd_deselect(drive);
	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ fd_get_drive_id(पूर्णांक drive)
अणु
	पूर्णांक i;
	uदीर्घ id = 0;

  	drive&=3;
  	get_fdc(drive);
	/* set up क्रम ID */
	MOTOR_ON;
	udelay(2);
	SELECT(SELMASK(drive));
	udelay(2);
	DESELECT(SELMASK(drive));
	udelay(2);
	MOTOR_OFF;
	udelay(2);
	SELECT(SELMASK(drive));
	udelay(2);
	DESELECT(SELMASK(drive));
	udelay(2);

	/* loop and पढ़ो disk ID */
	क्रम (i=0; i<32; i++) अणु
		SELECT(SELMASK(drive));
		udelay(2);

		/* पढ़ो and store value of DSKRDY */
		id <<= 1;
		id |= (ciaa.pra & DSKRDY) ? 0 : 1;	/* cia regs are low-active! */

		DESELECT(SELMASK(drive));
	पूर्ण

	rel_fdc();

        /*
         * RB: At least A500/A2000's df0: don't identअगरy themselves.
         * As every (real) Amiga has at least a 3.5" DD drive as df0:
         * we शेष to that अगर df0: करोesn't identअगरy as a certain
         * type.
         */
        अगर(drive == 0 && id == FD_NODRIVE)
	अणु
                id = fd_def_df0;
                prपूर्णांकk(KERN_NOTICE "fd: drive 0 didn't identify, setting default %08lx\n", (uदीर्घ)fd_def_df0);
	पूर्ण
	/* वापस the ID value */
	वापस (id);
पूर्ण

अटल irqवापस_t fd_block_करोne(पूर्णांक irq, व्योम *dummy)
अणु
	अगर (block_flag)
		custom.dsklen = 0x4000;

	अगर (block_flag == 2) अणु /* writing */
		ग_लिखोpending = 2;
		post_ग_लिखो_समयr.expires = jअगरfies + 1; /* at least 2 ms */
		post_ग_लिखो_समयr_drive = selected;
		add_समयr(&post_ग_लिखो_समयr);
	पूर्ण
	अन्यथा अणु                /* पढ़ोing */
		block_flag = 0;
		wake_up (&रुको_fd_block);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम raw_पढ़ो(पूर्णांक drive)
अणु
	drive&=3;
	get_fdc(drive);
	रुको_event(रुको_fd_block, !block_flag);
	fd_select(drive);
	/* setup adkcon bits correctly */
	custom.adkcon = ADK_MSBSYNC;
	custom.adkcon = ADK_SETCLR|ADK_WORDSYNC|ADK_FAST;

	custom.dsksync = MFM_SYNC;

	custom.dsklen = 0;
	custom.dskptr = (u_अक्षर *)ZTWO_PADDR((u_अक्षर *)raw_buf);
	custom.dsklen = unit[drive].type->पढ़ो_size/माप(लघु) | DSKLEN_DMAEN;
	custom.dsklen = unit[drive].type->पढ़ो_size/माप(लघु) | DSKLEN_DMAEN;

	block_flag = 1;

	रुको_event(रुको_fd_block, !block_flag);

	custom.dsklen = 0;
	fd_deselect(drive);
	rel_fdc();
पूर्ण

अटल पूर्णांक raw_ग_लिखो(पूर्णांक drive)
अणु
	uलघु adk;

	drive&=3;
	get_fdc(drive); /* corresponds to rel_fdc() in post_ग_लिखो() */
	अगर ((ciaa.pra & DSKPROT) == 0) अणु
		rel_fdc();
		वापस 0;
	पूर्ण
	रुको_event(रुको_fd_block, !block_flag);
	fd_select(drive);
	/* clear adkcon bits */
	custom.adkcon = ADK_PRECOMP1|ADK_PRECOMP0|ADK_WORDSYNC|ADK_MSBSYNC;
	/* set appropriate adkcon bits */
	adk = ADK_SETCLR|ADK_FAST;
	अगर ((uदीर्घ)unit[drive].track >= unit[drive].type->precomp2)
		adk |= ADK_PRECOMP1;
	अन्यथा अगर ((uदीर्घ)unit[drive].track >= unit[drive].type->precomp1)
		adk |= ADK_PRECOMP0;
	custom.adkcon = adk;

	custom.dsklen = DSKLEN_WRITE;
	custom.dskptr = (u_अक्षर *)ZTWO_PADDR((u_अक्षर *)raw_buf);
	custom.dsklen = unit[drive].type->ग_लिखो_size/माप(लघु) | DSKLEN_DMAEN|DSKLEN_WRITE;
	custom.dsklen = unit[drive].type->ग_लिखो_size/माप(लघु) | DSKLEN_DMAEN|DSKLEN_WRITE;

	block_flag = 2;
	वापस 1;
पूर्ण

/*
 * to be called at least 2ms after the ग_लिखो has finished but beक्रमe any
 * other access to the hardware.
 */
अटल व्योम post_ग_लिखो (अचिन्हित दीर्घ drive)
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk("post_write for drive %ld\n",drive);
#पूर्ण_अगर
	drive &= 3;
	custom.dsklen = 0;
	block_flag = 0;
	ग_लिखोpending = 0;
	ग_लिखोfromपूर्णांक = 0;
	unit[drive].dirty = 0;
	wake_up(&रुको_fd_block);
	fd_deselect(drive);
	rel_fdc(); /* corresponds to get_fdc() in raw_ग_लिखो */
पूर्ण

अटल व्योम post_ग_लिखो_callback(काष्ठा समयr_list *समयr)
अणु
	post_ग_लिखो(post_ग_लिखो_समयr_drive);
पूर्ण

/*
 * The following functions are to convert the block contents पूर्णांकo raw data
 * written to disk and vice versa.
 * (Add other क्रमmats here ;-))
 */

अटल अचिन्हित दीर्घ scan_sync(अचिन्हित दीर्घ raw, अचिन्हित दीर्घ end)
अणु
	uलघु *ptr = (uलघु *)raw, *endp = (uलघु *)end;

	जबतक (ptr < endp && *ptr++ != 0x4489)
		;
	अगर (ptr < endp) अणु
		जबतक (*ptr == 0x4489 && ptr < endp)
			ptr++;
		वापस (uदीर्घ)ptr;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ checksum(अचिन्हित दीर्घ *addr, पूर्णांक len)
अणु
	अचिन्हित दीर्घ csum = 0;

	len /= माप(*addr);
	जबतक (len-- > 0)
		csum ^= *addr++;
	csum = ((csum>>1) & 0x55555555)  ^  (csum & 0x55555555);

	वापस csum;
पूर्ण

अटल अचिन्हित दीर्घ decode (अचिन्हित दीर्घ *data, अचिन्हित दीर्घ *raw,
			     पूर्णांक len)
अणु
	uदीर्घ *odd, *even;

	/* convert length from bytes to दीर्घwords */
	len >>= 2;
	odd = raw;
	even = odd + len;

	/* prepare वापस poपूर्णांकer */
	raw += len * 2;

	करो अणु
		*data++ = ((*odd++ & 0x55555555) << 1) | (*even++ & 0x55555555);
	पूर्ण जबतक (--len != 0);

	वापस (uदीर्घ)raw;
पूर्ण

काष्ठा header अणु
	अचिन्हित अक्षर magic;
	अचिन्हित अक्षर track;
	अचिन्हित अक्षर sect;
	अचिन्हित अक्षर ord;
	अचिन्हित अक्षर labels[16];
	अचिन्हित दीर्घ hdrchk;
	अचिन्हित दीर्घ datachk;
पूर्ण;

अटल पूर्णांक amiga_पढ़ो(पूर्णांक drive)
अणु
	अचिन्हित दीर्घ raw;
	अचिन्हित दीर्घ end;
	पूर्णांक scnt;
	अचिन्हित दीर्घ csum;
	काष्ठा header hdr;

	drive&=3;
	raw = (दीर्घ) raw_buf;
	end = raw + unit[drive].type->पढ़ो_size;

	क्रम (scnt = 0;scnt < unit[drive].dtype->sects * unit[drive].type->sect_mult; scnt++) अणु
		अगर (!(raw = scan_sync(raw, end))) अणु
			prपूर्णांकk (KERN_INFO "can't find sync for sector %d\n", scnt);
			वापस MFM_NOSYNC;
		पूर्ण

		raw = decode ((uदीर्घ *)&hdr.magic, (uदीर्घ *)raw, 4);
		raw = decode ((uदीर्घ *)&hdr.labels, (uदीर्घ *)raw, 16);
		raw = decode ((uदीर्घ *)&hdr.hdrchk, (uदीर्घ *)raw, 4);
		raw = decode ((uदीर्घ *)&hdr.datachk, (uदीर्घ *)raw, 4);
		csum = checksum((uदीर्घ *)&hdr,
				(अक्षर *)&hdr.hdrchk-(अक्षर *)&hdr);

#अगर_घोषित DEBUG
		prपूर्णांकk ("(%x,%d,%d,%d) (%lx,%lx,%lx,%lx) %lx %lx\n",
			hdr.magic, hdr.track, hdr.sect, hdr.ord,
			*(uदीर्घ *)&hdr.labels[0], *(uदीर्घ *)&hdr.labels[4],
			*(uदीर्घ *)&hdr.labels[8], *(uदीर्घ *)&hdr.labels[12],
			hdr.hdrchk, hdr.datachk);
#पूर्ण_अगर

		अगर (hdr.hdrchk != csum) अणु
			prपूर्णांकk(KERN_INFO "MFM_HEADER: %08lx,%08lx\n", hdr.hdrchk, csum);
			वापस MFM_HEADER;
		पूर्ण

		/* verअगरy track */
		अगर (hdr.track != unit[drive].track) अणु
			prपूर्णांकk(KERN_INFO "MFM_TRACK: %d, %d\n", hdr.track, unit[drive].track);
			वापस MFM_TRACK;
		पूर्ण

		raw = decode ((uदीर्घ *)(unit[drive].trackbuf + hdr.sect*512),
			      (uदीर्घ *)raw, 512);
		csum = checksum((uदीर्घ *)(unit[drive].trackbuf + hdr.sect*512), 512);

		अगर (hdr.datachk != csum) अणु
			prपूर्णांकk(KERN_INFO "MFM_DATA: (%x:%d:%d:%d) sc=%d %lx, %lx\n",
			       hdr.magic, hdr.track, hdr.sect, hdr.ord, scnt,
			       hdr.datachk, csum);
			prपूर्णांकk (KERN_INFO "data=(%lx,%lx,%lx,%lx)\n",
				((uदीर्घ *)(unit[drive].trackbuf+hdr.sect*512))[0],
				((uदीर्घ *)(unit[drive].trackbuf+hdr.sect*512))[1],
				((uदीर्घ *)(unit[drive].trackbuf+hdr.sect*512))[2],
				((uदीर्घ *)(unit[drive].trackbuf+hdr.sect*512))[3]);
			वापस MFM_DATA;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम encode(अचिन्हित दीर्घ data, अचिन्हित दीर्घ *dest)
अणु
	अचिन्हित दीर्घ data2;

	data &= 0x55555555;
	data2 = data ^ 0x55555555;
	data |= ((data2 >> 1) | 0x80000000) & (data2 << 1);

	अगर (*(dest - 1) & 0x00000001)
		data &= 0x7FFFFFFF;

	*dest = data;
पूर्ण

अटल व्योम encode_block(अचिन्हित दीर्घ *dest, अचिन्हित दीर्घ *src, पूर्णांक len)
अणु
	पूर्णांक cnt, to_cnt = 0;
	अचिन्हित दीर्घ data;

	/* odd bits */
	क्रम (cnt = 0; cnt < len / 4; cnt++) अणु
		data = src[cnt] >> 1;
		encode(data, dest + to_cnt++);
	पूर्ण

	/* even bits */
	क्रम (cnt = 0; cnt < len / 4; cnt++) अणु
		data = src[cnt];
		encode(data, dest + to_cnt++);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ *माला_दोec(पूर्णांक disk, अचिन्हित दीर्घ *raw, पूर्णांक cnt)
अणु
	काष्ठा header hdr;
	पूर्णांक i;

	disk&=3;
	*raw = (raw[-1]&1) ? 0x2AAAAAAA : 0xAAAAAAAA;
	raw++;
	*raw++ = 0x44894489;

	hdr.magic = 0xFF;
	hdr.track = unit[disk].track;
	hdr.sect = cnt;
	hdr.ord = unit[disk].dtype->sects * unit[disk].type->sect_mult - cnt;
	क्रम (i = 0; i < 16; i++)
		hdr.labels[i] = 0;
	hdr.hdrchk = checksum((uदीर्घ *)&hdr,
			      (अक्षर *)&hdr.hdrchk-(अक्षर *)&hdr);
	hdr.datachk = checksum((uदीर्घ *)(unit[disk].trackbuf+cnt*512), 512);

	encode_block(raw, (uदीर्घ *)&hdr.magic, 4);
	raw += 2;
	encode_block(raw, (uदीर्घ *)&hdr.labels, 16);
	raw += 8;
	encode_block(raw, (uदीर्घ *)&hdr.hdrchk, 4);
	raw += 2;
	encode_block(raw, (uदीर्घ *)&hdr.datachk, 4);
	raw += 2;
	encode_block(raw, (uदीर्घ *)(unit[disk].trackbuf+cnt*512), 512);
	raw += 256;

	वापस raw;
पूर्ण

अटल व्योम amiga_ग_लिखो(पूर्णांक disk)
अणु
	अचिन्हित पूर्णांक cnt;
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)raw_buf;

	disk&=3;
	/* gap space */
	क्रम (cnt = 0; cnt < 415 * unit[disk].type->sect_mult; cnt++)
		*ptr++ = 0xaaaaaaaa;

	/* sectors */
	क्रम (cnt = 0; cnt < unit[disk].dtype->sects * unit[disk].type->sect_mult; cnt++)
		ptr = माला_दोec (disk, ptr, cnt);
	*(uलघु *)ptr = (ptr[-1]&1) ? 0x2AA8 : 0xAAA8;
पूर्ण


काष्ठा करोs_header अणु
	अचिन्हित अक्षर track,   /* 0-80 */
		side,    /* 0-1 */
		sec,     /* 0-...*/
		len_desc;/* 2 */
	अचिन्हित लघु crc;     /* on 68000 we got an alignment problem, 
				   but this compiler solves it  by adding silently 
				   adding a pad byte so data won't fit
				   and this took about 3h to discover.... */
	अचिन्हित अक्षर gap1[22];     /* क्रम दीर्घword-alignedness (0x4e) */
पूर्ण;

/* crc routines are borrowed from the messyकरोs-handler  */

/* excerpt from the messyकरोs-device           
; The CRC is computed not only over the actual data, but including
; the SYNC mark (3 * $a1) and the 'ID/DATA - Address Mark' ($fe/$fb).
; As we करोn't पढ़ो or encode these fields पूर्णांकo our buffers, we have to
; preload the रेजिस्टरs containing the CRC with the values they would have
; after stepping over these fields.
;
; How CRCs "really" work:
;
; First, you should regard a bitstring as a series of coefficients of
; polynomials. We calculate with these polynomials in modulo-2
; arithmetic, in which both add and subtract are करोne the same as
; exclusive-or. Now, we modअगरy our data (a very दीर्घ polynomial) in
; such a way that it becomes भागisible by the CCITT-standard 16-bit
;		 16   12   5
; polynomial:	x  + x	+ x + 1, represented by $11021. The easiest
; way to करो this would be to multiply (using proper arithmetic) our
; datablock with $11021. So we have:
;   data * $11021		 =
;   data * ($10000 + $1021)      =
;   data * $10000 + data * $1021
; The left part of this is simple: Just add two 0 bytes. But then
; the right part (data $1021) reमुख्यs dअगरficult and even could have
; a carry पूर्णांकo the left part. The solution is to use a modअगरied
; multiplication, which has a result that is not correct, but with
; a dअगरference of any multiple of $11021. We then only need to keep
; the 16 least signअगरicant bits of the result.
;
; The following algorithm करोes this क्रम us:
;
;   अचिन्हित अक्षर *data, c, crclo, crchi;
;   जबतक (not करोne) अणु
;	c = *data++ + crchi;
;	crchi = (@ c) >> 8 + crclo;
;	crclo = @ c;
;   पूर्ण
;
; Remember, + is करोne with EOR, the @ चालक is in two tables (high
; and low byte separately), which is calculated as
;
;      $1021 * (c & $F0)
;  xor $1021 * (c & $0F)
;  xor $1021 * (c >> 4)         (* is regular multiplication)
;
;
; Anyway, the end result is the same as the reमुख्यder of the भागision of
; the data by $11021. I am afraid I need to study theory a bit more...


my only works was to code this from manx to C....

*/

अटल uलघु करोs_crc(व्योम * data_a3, पूर्णांक data_d0, पूर्णांक data_d1, पूर्णांक data_d3)
अणु
	अटल अचिन्हित अक्षर CRCTable1[] = अणु
		0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x81,0x91,0xa1,0xb1,0xc1,0xd1,0xe1,0xf1,
		0x12,0x02,0x32,0x22,0x52,0x42,0x72,0x62,0x93,0x83,0xb3,0xa3,0xd3,0xc3,0xf3,0xe3,
		0x24,0x34,0x04,0x14,0x64,0x74,0x44,0x54,0xa5,0xb5,0x85,0x95,0xe5,0xf5,0xc5,0xd5,
		0x36,0x26,0x16,0x06,0x76,0x66,0x56,0x46,0xb7,0xa7,0x97,0x87,0xf7,0xe7,0xd7,0xc7,
		0x48,0x58,0x68,0x78,0x08,0x18,0x28,0x38,0xc9,0xd9,0xe9,0xf9,0x89,0x99,0xa9,0xb9,
		0x5a,0x4a,0x7a,0x6a,0x1a,0x0a,0x3a,0x2a,0xdb,0xcb,0xfb,0xeb,0x9b,0x8b,0xbb,0xab,
		0x6c,0x7c,0x4c,0x5c,0x2c,0x3c,0x0c,0x1c,0xed,0xfd,0xcd,0xdd,0xad,0xbd,0x8d,0x9d,
		0x7e,0x6e,0x5e,0x4e,0x3e,0x2e,0x1e,0x0e,0xff,0xef,0xdf,0xcf,0xbf,0xaf,0x9f,0x8f,
		0x91,0x81,0xb1,0xa1,0xd1,0xc1,0xf1,0xe1,0x10,0x00,0x30,0x20,0x50,0x40,0x70,0x60,
		0x83,0x93,0xa3,0xb3,0xc3,0xd3,0xe3,0xf3,0x02,0x12,0x22,0x32,0x42,0x52,0x62,0x72,
		0xb5,0xa5,0x95,0x85,0xf5,0xe5,0xd5,0xc5,0x34,0x24,0x14,0x04,0x74,0x64,0x54,0x44,
		0xa7,0xb7,0x87,0x97,0xe7,0xf7,0xc7,0xd7,0x26,0x36,0x06,0x16,0x66,0x76,0x46,0x56,
		0xd9,0xc9,0xf9,0xe9,0x99,0x89,0xb9,0xa9,0x58,0x48,0x78,0x68,0x18,0x08,0x38,0x28,
		0xcb,0xdb,0xeb,0xfb,0x8b,0x9b,0xab,0xbb,0x4a,0x5a,0x6a,0x7a,0x0a,0x1a,0x2a,0x3a,
		0xfd,0xed,0xdd,0xcd,0xbd,0xad,0x9d,0x8d,0x7c,0x6c,0x5c,0x4c,0x3c,0x2c,0x1c,0x0c,
		0xef,0xff,0xcf,0xdf,0xaf,0xbf,0x8f,0x9f,0x6e,0x7e,0x4e,0x5e,0x2e,0x3e,0x0e,0x1e
	पूर्ण;

	अटल अचिन्हित अक्षर CRCTable2[] = अणु
		0x00,0x21,0x42,0x63,0x84,0xa5,0xc6,0xe7,0x08,0x29,0x4a,0x6b,0x8c,0xad,0xce,0xef,
		0x31,0x10,0x73,0x52,0xb5,0x94,0xf7,0xd6,0x39,0x18,0x7b,0x5a,0xbd,0x9c,0xff,0xde,
		0x62,0x43,0x20,0x01,0xe6,0xc7,0xa4,0x85,0x6a,0x4b,0x28,0x09,0xee,0xcf,0xac,0x8d,
		0x53,0x72,0x11,0x30,0xd7,0xf6,0x95,0xb4,0x5b,0x7a,0x19,0x38,0xdf,0xfe,0x9d,0xbc,
		0xc4,0xe5,0x86,0xa7,0x40,0x61,0x02,0x23,0xcc,0xed,0x8e,0xaf,0x48,0x69,0x0a,0x2b,
		0xf5,0xd4,0xb7,0x96,0x71,0x50,0x33,0x12,0xfd,0xdc,0xbf,0x9e,0x79,0x58,0x3b,0x1a,
		0xa6,0x87,0xe4,0xc5,0x22,0x03,0x60,0x41,0xae,0x8f,0xec,0xcd,0x2a,0x0b,0x68,0x49,
		0x97,0xb6,0xd5,0xf4,0x13,0x32,0x51,0x70,0x9f,0xbe,0xdd,0xfc,0x1b,0x3a,0x59,0x78,
		0x88,0xa9,0xca,0xeb,0x0c,0x2d,0x4e,0x6f,0x80,0xa1,0xc2,0xe3,0x04,0x25,0x46,0x67,
		0xb9,0x98,0xfb,0xda,0x3d,0x1c,0x7f,0x5e,0xb1,0x90,0xf3,0xd2,0x35,0x14,0x77,0x56,
		0xea,0xcb,0xa8,0x89,0x6e,0x4f,0x2c,0x0d,0xe2,0xc3,0xa0,0x81,0x66,0x47,0x24,0x05,
		0xdb,0xfa,0x99,0xb8,0x5f,0x7e,0x1d,0x3c,0xd3,0xf2,0x91,0xb0,0x57,0x76,0x15,0x34,
		0x4c,0x6d,0x0e,0x2f,0xc8,0xe9,0x8a,0xab,0x44,0x65,0x06,0x27,0xc0,0xe1,0x82,0xa3,
		0x7d,0x5c,0x3f,0x1e,0xf9,0xd8,0xbb,0x9a,0x75,0x54,0x37,0x16,0xf1,0xd0,0xb3,0x92,
		0x2e,0x0f,0x6c,0x4d,0xaa,0x8b,0xe8,0xc9,0x26,0x07,0x64,0x45,0xa2,0x83,0xe0,0xc1,
		0x1f,0x3e,0x5d,0x7c,0x9b,0xba,0xd9,0xf8,0x17,0x36,0x55,0x74,0x93,0xb2,0xd1,0xf0
	पूर्ण;

/* look at the यंत्र-code - what looks in C a bit strange is almost as good as handmade */
	रेजिस्टर पूर्णांक i;
	रेजिस्टर अचिन्हित अक्षर *CRCT1, *CRCT2, *data, c, crch, crcl;

	CRCT1=CRCTable1;
	CRCT2=CRCTable2;
	data=data_a3;
	crcl=data_d1;
	crch=data_d0;
	क्रम (i=data_d3; i>=0; i--) अणु
		c = (*data++) ^ crch;
		crch = CRCT1[c] ^ crcl;
		crcl = CRCT2[c];
	पूर्ण
	वापस (crch<<8)|crcl;
पूर्ण

अटल अंतरभूत uलघु करोs_hdr_crc (काष्ठा करोs_header *hdr)
अणु
	वापस करोs_crc(&(hdr->track), 0xb2, 0x30, 3); /* precomputed magic */
पूर्ण

अटल अंतरभूत uलघु करोs_data_crc(अचिन्हित अक्षर *data)
अणु
	वापस करोs_crc(data, 0xe2, 0x95 ,511); /* precomputed magic */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर करोs_decode_byte(uलघु word)
अणु
	रेजिस्टर uलघु w2;
	रेजिस्टर अचिन्हित अक्षर byte;
	रेजिस्टर अचिन्हित अक्षर *dec = mfmdecode;

	w2=word;
	w2>>=8;
	w2&=127;
	byte = dec[w2];
	byte <<= 4;
	w2 = word & 127;
	byte |= dec[w2];
	वापस byte;
पूर्ण

अटल अचिन्हित दीर्घ करोs_decode(अचिन्हित अक्षर *data, अचिन्हित लघु *raw, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		*data++=करोs_decode_byte(*raw++);
	वापस ((uदीर्घ)raw);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम dbg(अचिन्हित दीर्घ ptr)
अणु
	prपूर्णांकk("raw data @%08lx: %08lx, %08lx ,%08lx, %08lx\n", ptr,
	       ((uदीर्घ *)ptr)[0], ((uदीर्घ *)ptr)[1],
	       ((uदीर्घ *)ptr)[2], ((uदीर्घ *)ptr)[3]);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक करोs_पढ़ो(पूर्णांक drive)
अणु
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ raw;
	पूर्णांक scnt;
	अचिन्हित लघु crc,data_crc[2];
	काष्ठा करोs_header hdr;

	drive&=3;
	raw = (दीर्घ) raw_buf;
	end = raw + unit[drive].type->पढ़ो_size;

	क्रम (scnt=0; scnt < unit[drive].dtype->sects * unit[drive].type->sect_mult; scnt++) अणु
		करो अणु /* search क्रम the right sync of each sec-hdr */
			अगर (!(raw = scan_sync (raw, end))) अणु
				prपूर्णांकk(KERN_INFO "dos_read: no hdr sync on "
				       "track %d, unit %d for sector %d\n",
				       unit[drive].track,drive,scnt);
				वापस MFM_NOSYNC;
			पूर्ण
#अगर_घोषित DEBUG
			dbg(raw);
#पूर्ण_अगर
		पूर्ण जबतक (*((uलघु *)raw)!=0x5554); /* loop usually only once करोne */
		raw+=2; /* skip over headermark */
		raw = करोs_decode((अचिन्हित अक्षर *)&hdr,(uलघु *) raw,8);
		crc = करोs_hdr_crc(&hdr);

#अगर_घोषित DEBUG
		prपूर्णांकk("(%3d,%d,%2d,%d) %x\n", hdr.track, hdr.side,
		       hdr.sec, hdr.len_desc, hdr.crc);
#पूर्ण_अगर

		अगर (crc != hdr.crc) अणु
			prपूर्णांकk(KERN_INFO "dos_read: MFM_HEADER %04x,%04x\n",
			       hdr.crc, crc);
			वापस MFM_HEADER;
		पूर्ण
		अगर (hdr.track != unit[drive].track/unit[drive].type->heads) अणु
			prपूर्णांकk(KERN_INFO "dos_read: MFM_TRACK %d, %d\n",
			       hdr.track,
			       unit[drive].track/unit[drive].type->heads);
			वापस MFM_TRACK;
		पूर्ण

		अगर (hdr.side != unit[drive].track%unit[drive].type->heads) अणु
			prपूर्णांकk(KERN_INFO "dos_read: MFM_SIDE %d, %d\n",
			       hdr.side,
			       unit[drive].track%unit[drive].type->heads);
			वापस MFM_TRACK;
		पूर्ण

		अगर (hdr.len_desc != 2) अणु
			prपूर्णांकk(KERN_INFO "dos_read: unknown sector len "
			       "descriptor %d\n", hdr.len_desc);
			वापस MFM_DATA;
		पूर्ण
#अगर_घोषित DEBUG
		prपूर्णांकk("hdr accepted\n");
#पूर्ण_अगर
		अगर (!(raw = scan_sync (raw, end))) अणु
			prपूर्णांकk(KERN_INFO "dos_read: no data sync on track "
			       "%d, unit %d for sector%d, disk sector %d\n",
			       unit[drive].track, drive, scnt, hdr.sec);
			वापस MFM_NOSYNC;
		पूर्ण
#अगर_घोषित DEBUG
		dbg(raw);
#पूर्ण_अगर

		अगर (*((uलघु *)raw)!=0x5545) अणु
			prपूर्णांकk(KERN_INFO "dos_read: no data mark after "
			       "sync (%d,%d,%d,%d) sc=%d\n",
			       hdr.track,hdr.side,hdr.sec,hdr.len_desc,scnt);
			वापस MFM_NOSYNC;
		पूर्ण

		raw+=2;  /* skip data mark (included in checksum) */
		raw = करोs_decode((अचिन्हित अक्षर *)(unit[drive].trackbuf + (hdr.sec - 1) * 512), (uलघु *) raw, 512);
		raw = करोs_decode((अचिन्हित अक्षर  *)data_crc,(uलघु *) raw,4);
		crc = करोs_data_crc(unit[drive].trackbuf + (hdr.sec - 1) * 512);

		अगर (crc != data_crc[0]) अणु
			prपूर्णांकk(KERN_INFO "dos_read: MFM_DATA (%d,%d,%d,%d) "
			       "sc=%d, %x %x\n", hdr.track, hdr.side,
			       hdr.sec, hdr.len_desc, scnt,data_crc[0], crc);
			prपूर्णांकk(KERN_INFO "data=(%lx,%lx,%lx,%lx,...)\n",
			       ((uदीर्घ *)(unit[drive].trackbuf+(hdr.sec-1)*512))[0],
			       ((uदीर्घ *)(unit[drive].trackbuf+(hdr.sec-1)*512))[1],
			       ((uदीर्घ *)(unit[drive].trackbuf+(hdr.sec-1)*512))[2],
			       ((uदीर्घ *)(unit[drive].trackbuf+(hdr.sec-1)*512))[3]);
			वापस MFM_DATA;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत uलघु करोs_encode_byte(अचिन्हित अक्षर byte)
अणु
	रेजिस्टर अचिन्हित अक्षर *enc, b2, b1;
	रेजिस्टर uलघु word;

	enc=mfmencode;
	b1=byte;
	b2=b1>>4;
	b1&=15;
	word=enc[b2] <<8 | enc [b1];
	वापस (word|((word&(256|64)) ? 0: 128));
पूर्ण

अटल व्योम करोs_encode_block(uलघु *dest, अचिन्हित अक्षर *src, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		*dest=करोs_encode_byte(*src++);
		*dest|=((dest[-1]&1)||(*dest&0x4000))? 0: 0x8000;
		dest++;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ *ms_माला_दोec(पूर्णांक drive, अचिन्हित दीर्घ *raw, पूर्णांक cnt)
अणु
	अटल काष्ठा करोs_header hdr=अणु0,0,0,2,0,
	  अणु78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78पूर्णपूर्ण;
	पूर्णांक i;
	अटल uलघु crc[2]=अणु0,0x4e4eपूर्ण;

	drive&=3;
/* id gap 1 */
/* the MFM word beक्रमe is always 9254 */
	क्रम(i=0;i<6;i++)
		*raw++=0xaaaaaaaa;
/* 3 sync + 1 headermark */
	*raw++=0x44894489;
	*raw++=0x44895554;

/* fill in the variable parts of the header */
	hdr.track=unit[drive].track/unit[drive].type->heads;
	hdr.side=unit[drive].track%unit[drive].type->heads;
	hdr.sec=cnt+1;
	hdr.crc=करोs_hdr_crc(&hdr);

/* header (without "magic") and id gap 2*/
	करोs_encode_block((uलघु *)raw,(अचिन्हित अक्षर *) &hdr.track,28);
	raw+=14;

/*id gap 3 */
	क्रम(i=0;i<6;i++)
		*raw++=0xaaaaaaaa;

/* 3 syncs and 1 datamark */
	*raw++=0x44894489;
	*raw++=0x44895545;

/* data */
	करोs_encode_block((uलघु *)raw,
			 (अचिन्हित अक्षर *)unit[drive].trackbuf+cnt*512,512);
	raw+=256;

/*data crc + jd's special gap (दीर्घ words :-/) */
	crc[0]=करोs_data_crc(unit[drive].trackbuf+cnt*512);
	करोs_encode_block((uलघु *) raw,(अचिन्हित अक्षर *)crc,4);
	raw+=2;

/* data gap */
	क्रम(i=0;i<38;i++)
		*raw++=0x92549254;

	वापस raw; /* wrote 652 MFM words */
पूर्ण

अटल व्योम करोs_ग_लिखो(पूर्णांक disk)
अणु
	पूर्णांक cnt;
	अचिन्हित दीर्घ raw = (अचिन्हित दीर्घ) raw_buf;
	अचिन्हित दीर्घ *ptr=(अचिन्हित दीर्घ *)raw;

	disk&=3;
/* really gap4 + indexgap , but we ग_लिखो it first and round it up */
	क्रम (cnt=0;cnt<425;cnt++)
		*ptr++=0x92549254;

/* the following is just guessed */
	अगर (unit[disk].type->sect_mult==2)  /* check क्रम HD-Disks */
		क्रम(cnt=0;cnt<473;cnt++)
			*ptr++=0x92549254;

/* now the index marks...*/
	क्रम (cnt=0;cnt<20;cnt++)
		*ptr++=0x92549254;
	क्रम (cnt=0;cnt<6;cnt++)
		*ptr++=0xaaaaaaaa;
	*ptr++=0x52245224;
	*ptr++=0x52245552;
	क्रम (cnt=0;cnt<20;cnt++)
		*ptr++=0x92549254;

/* sectors */
	क्रम(cnt = 0; cnt < unit[disk].dtype->sects * unit[disk].type->sect_mult; cnt++)
		ptr=ms_माला_दोec(disk,ptr,cnt);

	*(uलघु *)ptr = 0xaaa8; /* MFM word beक्रमe is always 0x9254 */
पूर्ण

/*
 * Here comes the high level stuff (i.e. the fileप्रणाली पूर्णांकerface)
 * and helper functions.
 * Normally this should be the only part that has to be adapted to
 * dअगरferent kernel versions.
 */

/* FIXME: this assumes the drive is still spinning -
 * which is only true अगर we complete writing a track within three seconds
 */
अटल व्योम flush_track_callback(काष्ठा समयr_list *समयr)
अणु
	अचिन्हित दीर्घ nr = ((अचिन्हित दीर्घ)समयr -
			       (अचिन्हित दीर्घ)&flush_track_समयr[0]) /
					माप(flush_track_समयr[0]);

	nr&=3;
	ग_लिखोfromपूर्णांक = 1;
	अगर (!try_fdc(nr)) अणु
		/* we might block in an पूर्णांकerrupt, so try again later */
		flush_track_समयr[nr].expires = jअगरfies + 1;
		add_समयr(flush_track_समयr + nr);
		वापस;
	पूर्ण
	get_fdc(nr);
	(*unit[nr].dtype->ग_लिखो_fkt)(nr);
	अगर (!raw_ग_लिखो(nr)) अणु
		prपूर्णांकk (KERN_NOTICE "floppy disk write protected\n");
		ग_लिखोfromपूर्णांक = 0;
		ग_लिखोpending = 0;
	पूर्ण
	rel_fdc();
पूर्ण

अटल पूर्णांक non_पूर्णांक_flush_track (अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ flags;

	nr&=3;
	ग_लिखोfromपूर्णांक = 0;
	del_समयr(&post_ग_लिखो_समयr);
	get_fdc(nr);
	अगर (!fd_motor_on(nr)) अणु
		ग_लिखोpending = 0;
		rel_fdc();
		वापस 0;
	पूर्ण
	local_irq_save(flags);
	अगर (ग_लिखोpending != 2) अणु
		local_irq_restore(flags);
		(*unit[nr].dtype->ग_लिखो_fkt)(nr);
		अगर (!raw_ग_लिखो(nr)) अणु
			prपूर्णांकk (KERN_NOTICE "floppy disk write protected "
				"in write!\n");
			ग_लिखोpending = 0;
			वापस 0;
		पूर्ण
		रुको_event(रुको_fd_block, block_flag != 2);
	पूर्ण
	अन्यथा अणु
		local_irq_restore(flags);
		ms_delay(2); /* 2 ms post_ग_लिखो delay */
		post_ग_लिखो(nr);
	पूर्ण
	rel_fdc();
	वापस 1;
पूर्ण

अटल पूर्णांक get_track(पूर्णांक drive, पूर्णांक track)
अणु
	पूर्णांक error, errcnt;

	drive&=3;
	अगर (unit[drive].track == track)
		वापस 0;
	get_fdc(drive);
	अगर (!fd_motor_on(drive)) अणु
		rel_fdc();
		वापस -1;
	पूर्ण

	अगर (unit[drive].dirty == 1) अणु
		del_समयr (flush_track_समयr + drive);
		non_पूर्णांक_flush_track (drive);
	पूर्ण
	errcnt = 0;
	जबतक (errcnt < MAX_ERRORS) अणु
		अगर (!fd_seek(drive, track))
			वापस -1;
		raw_पढ़ो(drive);
		error = (*unit[drive].dtype->पढ़ो_fkt)(drive);
		अगर (error == 0) अणु
			rel_fdc();
			वापस 0;
		पूर्ण
		/* Read Error Handling: recalibrate and try again */
		unit[drive].track = -1;
		errcnt++;
	पूर्ण
	rel_fdc();
	वापस -1;
पूर्ण

अटल blk_status_t amअगरlop_rw_cur_segment(काष्ठा amiga_floppy_काष्ठा *floppy,
					   काष्ठा request *rq)
अणु
	पूर्णांक drive = floppy - unit;
	अचिन्हित पूर्णांक cnt, block, track, sector;
	अक्षर *data;

	क्रम (cnt = 0; cnt < blk_rq_cur_sectors(rq); cnt++) अणु
#अगर_घोषित DEBUG
		prपूर्णांकk("fd: sector %ld + %d requested for %s\n",
		       blk_rq_pos(rq), cnt,
		       (rq_data_dir(rq) == READ) ? "read" : "write");
#पूर्ण_अगर
		block = blk_rq_pos(rq) + cnt;
		track = block / (floppy->dtype->sects * floppy->type->sect_mult);
		sector = block % (floppy->dtype->sects * floppy->type->sect_mult);
		data = bio_data(rq->bio) + 512 * cnt;
#अगर_घोषित DEBUG
		prपूर्णांकk("access to track %d, sector %d, with buffer at "
		       "0x%08lx\n", track, sector, data);
#पूर्ण_अगर

		अगर (get_track(drive, track) == -1)
			वापस BLK_STS_IOERR;

		अगर (rq_data_dir(rq) == READ) अणु
			स_नकल(data, floppy->trackbuf + sector * 512, 512);
		पूर्ण अन्यथा अणु
			स_नकल(floppy->trackbuf + sector * 512, data, 512);

			/* keep the drive spinning जबतक ग_लिखोs are scheduled */
			अगर (!fd_motor_on(drive))
				वापस BLK_STS_IOERR;
			/*
			 * setup a callback to ग_लिखो the track buffer
			 * after a लघु (1 tick) delay.
			 */
			floppy->dirty = 1;
		        /* reset the समयr */
			mod_समयr (flush_track_समयr + drive, jअगरfies + 1);
		पूर्ण
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t amअगरlop_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				     स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *rq = bd->rq;
	काष्ठा amiga_floppy_काष्ठा *floppy = rq->rq_disk->निजी_data;
	blk_status_t err;

	अगर (!spin_trylock_irq(&amअगरlop_lock))
		वापस BLK_STS_DEV_RESOURCE;

	blk_mq_start_request(rq);

	करो अणु
		err = amअगरlop_rw_cur_segment(floppy, rq);
	पूर्ण जबतक (blk_update_request(rq, err, blk_rq_cur_bytes(rq)));
	blk_mq_end_request(rq, err);

	spin_unlock_irq(&amअगरlop_lock);
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक fd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	पूर्णांक drive = MINOR(bdev->bd_dev) & 3;

	geo->heads = unit[drive].type->heads;
	geo->sectors = unit[drive].dtype->sects * unit[drive].type->sect_mult;
	geo->cylinders = unit[drive].type->tracks;
	वापस 0;
पूर्ण

अटल पूर्णांक fd_locked_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	काष्ठा amiga_floppy_काष्ठा *p = bdev->bd_disk->निजी_data;
	पूर्णांक drive = p - unit;
	अटल काष्ठा floppy_काष्ठा getprm;
	व्योम __user *argp = (व्योम __user *)param;

	चयन(cmd)अणु
	हाल FDFMTBEG:
		get_fdc(drive);
		अगर (fd_ref[drive] > 1) अणु
			rel_fdc();
			वापस -EBUSY;
		पूर्ण
		fsync_bdev(bdev);
		अगर (fd_motor_on(drive) == 0) अणु
			rel_fdc();
			वापस -ENODEV;
		पूर्ण
		अगर (fd_calibrate(drive) == 0) अणु
			rel_fdc();
			वापस -ENXIO;
		पूर्ण
		floppy_off(drive);
		rel_fdc();
		अवरोध;
	हाल FDFMTTRK:
		अगर (param < p->type->tracks * p->type->heads)
		अणु
			get_fdc(drive);
			अगर (fd_seek(drive,param) != 0)अणु
				स_रखो(p->trackbuf, FD_FILL_BYTE,
				       p->dtype->sects * p->type->sect_mult * 512);
				non_पूर्णांक_flush_track(drive);
			पूर्ण
			floppy_off(drive);
			rel_fdc();
		पूर्ण
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल FDFMTEND:
		floppy_off(drive);
		invalidate_bdev(bdev);
		अवरोध;
	हाल FDGETPRM:
		स_रखो((व्योम *)&getprm, 0, माप (getprm));
		getprm.track=p->type->tracks;
		getprm.head=p->type->heads;
		getprm.sect=p->dtype->sects * p->type->sect_mult;
		getprm.size=p->blocks;
		अगर (copy_to_user(argp, &getprm, माप(काष्ठा floppy_काष्ठा)))
			वापस -EFAULT;
		अवरोध;
	हाल FDSETPRM:
	हाल FDDEFPRM:
		वापस -EINVAL;
	हाल FDFLUSH: /* unconditionally, even अगर not needed */
		del_समयr (flush_track_समयr + drive);
		non_पूर्णांक_flush_track(drive);
		अवरोध;
#अगर_घोषित RAW_IOCTL
	हाल IOCTL_RAW_TRACK:
		अगर (copy_to_user(argp, raw_buf, p->type->पढ़ो_size))
			वापस -EFAULT;
		अन्यथा
			वापस p->type->पढ़ो_size;
#पूर्ण_अगर
	शेष:
		वापस -ENOSYS;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	पूर्णांक ret;

	mutex_lock(&amअगरlop_mutex);
	ret = fd_locked_ioctl(bdev, mode, cmd, param);
	mutex_unlock(&amअगरlop_mutex);

	वापस ret;
पूर्ण

अटल व्योम fd_probe(पूर्णांक dev)
अणु
	अचिन्हित दीर्घ code;
	पूर्णांक type;
	पूर्णांक drive;

	drive = dev & 3;
	code = fd_get_drive_id(drive);

	/* get drive type */
	क्रम (type = 0; type < num_dr_types; type++)
		अगर (drive_types[type].code == code)
			अवरोध;

	अगर (type >= num_dr_types) अणु
		prपूर्णांकk(KERN_WARNING "fd_probe: unsupported drive type "
		       "%08lx found\n", code);
		unit[drive].type = &drive_types[num_dr_types-1]; /* FD_NODRIVE */
		वापस;
	पूर्ण

	unit[drive].type = drive_types + type;
	unit[drive].track = -1;

	unit[drive].disk = -1;
	unit[drive].motor = 0;
	unit[drive].busy = 0;
	unit[drive].status = -1;
पूर्ण

/*
 * floppy_खोलो check क्रम aliasing (/dev/fd0 can be the same as
 * /dev/PS0 etc), and disallows simultaneous access to the same
 * drive with dअगरferent device numbers.
 */
अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक drive = MINOR(bdev->bd_dev) & 3;
	पूर्णांक प्रणाली =  (MINOR(bdev->bd_dev) & 4) >> 2;
	पूर्णांक old_dev;
	अचिन्हित दीर्घ flags;

	mutex_lock(&amअगरlop_mutex);
	old_dev = fd_device[drive];

	अगर (fd_ref[drive] && old_dev != प्रणाली) अणु
		mutex_unlock(&amअगरlop_mutex);
		वापस -EBUSY;
	पूर्ण

	अगर (unit[drive].type->code == FD_NODRIVE) अणु
		mutex_unlock(&amअगरlop_mutex);
		वापस -ENXIO;
	पूर्ण

	अगर (mode & (FMODE_READ|FMODE_WRITE)) अणु
		bdev_check_media_change(bdev);
		अगर (mode & FMODE_WRITE) अणु
			पूर्णांक wrprot;

			get_fdc(drive);
			fd_select (drive);
			wrprot = !(ciaa.pra & DSKPROT);
			fd_deselect (drive);
			rel_fdc();

			अगर (wrprot) अणु
				mutex_unlock(&amअगरlop_mutex);
				वापस -EROFS;
			पूर्ण
		पूर्ण
	पूर्ण

	local_irq_save(flags);
	fd_ref[drive]++;
	fd_device[drive] = प्रणाली;
	local_irq_restore(flags);

	unit[drive].dtype=&data_types[प्रणाली];
	unit[drive].blocks=unit[drive].type->heads*unit[drive].type->tracks*
		data_types[प्रणाली].sects*unit[drive].type->sect_mult;
	set_capacity(unit[drive].gendisk[प्रणाली], unit[drive].blocks);

	prपूर्णांकk(KERN_INFO "fd%d: accessing %s-disk with %s-layout\n",drive,
	       unit[drive].type->name, data_types[प्रणाली].name);

	mutex_unlock(&amअगरlop_mutex);
	वापस 0;
पूर्ण

अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा amiga_floppy_काष्ठा *p = disk->निजी_data;
	पूर्णांक drive = p - unit;

	mutex_lock(&amअगरlop_mutex);
	अगर (unit[drive].dirty == 1) अणु
		del_समयr (flush_track_समयr + drive);
		non_पूर्णांक_flush_track (drive);
	पूर्ण
  
	अगर (!fd_ref[drive]--) अणु
		prपूर्णांकk(KERN_CRIT "floppy_release with fd_ref == 0");
		fd_ref[drive] = 0;
	पूर्ण
#अगर_घोषित MODULE
	floppy_off (drive);
#पूर्ण_अगर
	mutex_unlock(&amअगरlop_mutex);
पूर्ण

/*
 * check_events is never called from an पूर्णांकerrupt, so we can relax a bit
 * here, sleep etc. Note that floppy-on tries to set current_DOR to poपूर्णांक
 * to the desired drive, but it will probably not survive the sleep अगर
 * several floppies are used at the same समय: thus the loop.
 */
अटल अचिन्हित amiga_check_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा amiga_floppy_काष्ठा *p = disk->निजी_data;
	पूर्णांक drive = p - unit;
	पूर्णांक changed;
	अटल पूर्णांक first_समय = 1;

	अगर (first_समय)
		changed = first_समय--;
	अन्यथा अणु
		get_fdc(drive);
		fd_select (drive);
		changed = !(ciaa.pra & DSKCHANGE);
		fd_deselect (drive);
		rel_fdc();
	पूर्ण

	अगर (changed) अणु
		fd_probe(drive);
		p->track = -1;
		p->dirty = 0;
		ग_लिखोpending = 0; /* अगर this was true beक्रमe, too bad! */
		ग_लिखोfromपूर्णांक = 0;
		वापस DISK_EVENT_MEDIA_CHANGE;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations floppy_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= floppy_खोलो,
	.release	= floppy_release,
	.ioctl		= fd_ioctl,
	.getgeo		= fd_getgeo,
	.check_events	= amiga_check_events,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops amअगरlop_mq_ops = अणु
	.queue_rq = amअगरlop_queue_rq,
पूर्ण;

अटल पूर्णांक fd_alloc_disk(पूर्णांक drive, पूर्णांक प्रणाली)
अणु
	काष्ठा gendisk *disk;

	disk = alloc_disk(1);
	अगर (!disk)
		जाओ out;
	disk->queue = blk_mq_init_queue(&unit[drive].tag_set);
	अगर (IS_ERR(disk->queue))
		जाओ out_put_disk;

	disk->major = FLOPPY_MAJOR;
	disk->first_minor = drive + प्रणाली;
	disk->fops = &floppy_fops;
	disk->events = DISK_EVENT_MEDIA_CHANGE;
	अगर (प्रणाली)
		प्र_लिखो(disk->disk_name, "fd%d_msdos", drive);
	अन्यथा
		प्र_लिखो(disk->disk_name, "fd%d", drive);
	disk->निजी_data = &unit[drive];
	set_capacity(disk, 880 * 2);

	unit[drive].gendisk[प्रणाली] = disk;
	add_disk(disk);
	वापस 0;

out_put_disk:
	disk->queue = शून्य;
	put_disk(disk);
out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक fd_alloc_drive(पूर्णांक drive)
अणु
	unit[drive].trackbuf = kदो_स्मृति(FLOPPY_MAX_SECTORS * 512, GFP_KERNEL);
	अगर (!unit[drive].trackbuf)
		जाओ out;

	स_रखो(&unit[drive].tag_set, 0, माप(unit[drive].tag_set));
	unit[drive].tag_set.ops = &amअगरlop_mq_ops;
	unit[drive].tag_set.nr_hw_queues = 1;
	unit[drive].tag_set.nr_maps = 1;
	unit[drive].tag_set.queue_depth = 2;
	unit[drive].tag_set.numa_node = NUMA_NO_NODE;
	unit[drive].tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	अगर (blk_mq_alloc_tag_set(&unit[drive].tag_set))
		जाओ out_cleanup_trackbuf;

	pr_cont(" fd%d", drive);

	अगर (fd_alloc_disk(drive, 0) || fd_alloc_disk(drive, 1))
		जाओ out_cleanup_tagset;
	वापस 0;

out_cleanup_tagset:
	blk_mq_मुक्त_tag_set(&unit[drive].tag_set);
out_cleanup_trackbuf:
	kमुक्त(unit[drive].trackbuf);
out:
	unit[drive].type->code = FD_NODRIVE;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init fd_probe_drives(व्योम)
अणु
	पूर्णांक drive,drives,nomem;

	pr_info("FD: probing units\nfound");
	drives=0;
	nomem=0;
	क्रम(drive=0;drive<FD_MAX_UNITS;drive++) अणु
		fd_probe(drive);
		अगर (unit[drive].type->code == FD_NODRIVE)
			जारी;

		अगर (fd_alloc_drive(drive) < 0) अणु
			pr_cont(" no mem for fd%d", drive);
			nomem = 1;
			जारी;
		पूर्ण
		drives++;
	पूर्ण
	अगर ((drives > 0) || (nomem == 0)) अणु
		अगर (drives == 0)
			pr_cont(" no drives");
		pr_cont("\n");
		वापस drives;
	पूर्ण
	pr_cont("\n");
	वापस -ENOMEM;
पूर्ण
 
अटल पूर्णांक __init amiga_floppy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;

	अगर (रेजिस्टर_blkdev(FLOPPY_MAJOR,"fd"))
		वापस -EBUSY;

	ret = -ENOMEM;
	raw_buf = amiga_chip_alloc(RAW_BUF_SIZE, "Floppy");
	अगर (!raw_buf) अणु
		prपूर्णांकk("fd: cannot get chip mem buffer\n");
		जाओ out_blkdev;
	पूर्ण

	ret = -EBUSY;
	अगर (request_irq(IRQ_AMIGA_DSKBLK, fd_block_करोne, 0, "floppy_dma", शून्य)) अणु
		prपूर्णांकk("fd: cannot get irq for dma\n");
		जाओ out_irq;
	पूर्ण

	अगर (request_irq(IRQ_AMIGA_CIAA_TB, ms_isr, 0, "floppy_timer", शून्य)) अणु
		prपूर्णांकk("fd: cannot get irq for timer\n");
		जाओ out_irq2;
	पूर्ण

	ret = -ENODEV;
	अगर (fd_probe_drives() < 1) /* No usable drives */
		जाओ out_probe;

	/* initialize variables */
	समयr_setup(&motor_on_समयr, motor_on_callback, 0);
	motor_on_समयr.expires = 0;
	क्रम (i = 0; i < FD_MAX_UNITS; i++) अणु
		समयr_setup(&motor_off_समयr[i], fd_motor_off, 0);
		motor_off_समयr[i].expires = 0;
		समयr_setup(&flush_track_समयr[i], flush_track_callback, 0);
		flush_track_समयr[i].expires = 0;

		unit[i].track = -1;
	पूर्ण

	समयr_setup(&post_ग_लिखो_समयr, post_ग_लिखो_callback, 0);
	post_ग_लिखो_समयr.expires = 0;
  
	क्रम (i = 0; i < 128; i++)
		mfmdecode[i]=255;
	क्रम (i = 0; i < 16; i++)
		mfmdecode[mfmencode[i]]=i;

	/* make sure that disk DMA is enabled */
	custom.dmacon = DMAF_SETCLR | DMAF_DISK;

	/* init ms समयr */
	ciaa.crb = 8; /* one-shot, stop */
	वापस 0;

out_probe:
	मुक्त_irq(IRQ_AMIGA_CIAA_TB, शून्य);
out_irq2:
	मुक्त_irq(IRQ_AMIGA_DSKBLK, शून्य);
out_irq:
	amiga_chip_मुक्त(raw_buf);
out_blkdev:
	unरेजिस्टर_blkdev(FLOPPY_MAJOR,"fd");
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_floppy_driver = अणु
	.driver   = अणु
		.name	= "amiga-floppy",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init amiga_floppy_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&amiga_floppy_driver, amiga_floppy_probe);
पूर्ण

module_init(amiga_floppy_init);

#अगर_अघोषित MODULE
अटल पूर्णांक __init amiga_floppy_setup (अक्षर *str)
अणु
	पूर्णांक n;
	अगर (!MACH_IS_AMIGA)
		वापस 0;
	अगर (!get_option(&str, &n))
		वापस 0;
	prपूर्णांकk (KERN_INFO "amiflop: Setting default df0 to %x\n", n);
	fd_def_df0 = n;
	वापस 1;
पूर्ण

__setup("floppy=", amiga_floppy_setup);
#पूर्ण_अगर

MODULE_ALIAS("platform:amiga-floppy");
