<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FD_H
#घोषणा _UAPI_LINUX_FD_H

#समावेश <linux/ioctl.h>
#समावेश <linux/compiler.h>

/* New file layout: Now the ioctl definitions immediately follow the
 * definitions of the काष्ठाures that they use */

/*
 * Geometry
 */
काष्ठा floppy_काष्ठा अणु
	अचिन्हित पूर्णांक	size,		/* nr of sectors total */
			sect,		/* sectors per track */
			head,		/* nr of heads */
			track,		/* nr of tracks */
			stretch;	/* bit 0 !=0 means द्विगुन track steps */
					/* bit 1 != 0 means swap sides */
					/* bits 2..9 give the first sector */
					/*  number (the LSB is flipped) */
#घोषणा FD_STRETCH 1
#घोषणा FD_SWAPSIDES 2
#घोषणा FD_ZEROBASED 4
#घोषणा FD_SECTBASEMASK 0x3FC
#घोषणा FD_MKSECTBASE(s) (((s) ^ 1) << 2)
#घोषणा FD_SECTBASE(floppy) ((((floppy)->stretch & FD_SECTBASEMASK) >> 2) ^ 1)

	अचिन्हित अक्षर	gap,		/* gap1 size */

			rate,		/* data rate. |= 0x40 क्रम perpendicular */
#घोषणा FD_2M 0x4
#घोषणा FD_SIZECODEMASK 0x38
#घोषणा FD_SIZECODE(floppy) (((((floppy)->rate&FD_SIZECODEMASK)>> 3)+ 2) %8)
#घोषणा FD_SECTSIZE(floppy) ( (floppy)->rate & FD_2M ? \
			     512 : 128 << FD_SIZECODE(floppy) )
#घोषणा FD_PERP 0x40

			spec1,		/* stepping rate, head unload समय */
			fmt_gap;	/* gap2 size */
	स्थिर अक्षर	* name; /* used only क्रम predefined क्रमmats */
पूर्ण;


/* commands needing ग_लिखो access have 0x40 set */
/* commands needing super user access have 0x80 set */

#घोषणा FDCLRPRM _IO(2, 0x41)
/* clear user-defined parameters */

#घोषणा FDSETPRM _IOW(2, 0x42, काष्ठा floppy_काष्ठा)
#घोषणा FDSETMEDIAPRM FDSETPRM
/* set user-defined parameters क्रम current media */

#घोषणा FDDEFPRM _IOW(2, 0x43, काष्ठा floppy_काष्ठा)
#घोषणा FDGETPRM _IOR(2, 0x04, काष्ठा floppy_काष्ठा)
#घोषणा FDDEFMEDIAPRM FDDEFPRM
#घोषणा FDGETMEDIAPRM FDGETPRM
/* set/get disk parameters */


#घोषणा	FDMSGON  _IO(2,0x45)
#घोषणा	FDMSGOFF _IO(2,0x46)
/* issue/करोn't issue kernel messages on media type change */


/*
 * Formatting (obsolete)
 */
#घोषणा FD_FILL_BYTE 0xF6 /* क्रमmat fill byte. */

काष्ठा क्रमmat_descr अणु
	अचिन्हित पूर्णांक device,head,track;
पूर्ण;

#घोषणा FDFMTBEG _IO(2,0x47)
/* begin क्रमmatting a disk */
#घोषणा	FDFMTTRK _IOW(2,0x48, काष्ठा क्रमmat_descr)
/* क्रमmat the specअगरied track */
#घोषणा FDFMTEND _IO(2,0x49)
/* end क्रमmatting a disk */


/*
 * Error thresholds
 */
काष्ठा floppy_max_errors अणु
	अचिन्हित पूर्णांक
	  पात,      /* number of errors to be reached beक्रमe पातing */
	  पढ़ो_track, /* maximal number of errors permitted to पढ़ो an
		       * entire track at once */
	  reset,      /* maximal number of errors beक्रमe a reset is tried */
	  recal,      /* maximal number of errors beक्रमe a recalibrate is
		       * tried */

	  /*
	   * Threshold क्रम reporting FDC errors to the console.
	   * Setting this to zero may flood your screen when using
	   * ultra cheap floppies ;-)
	   */
	  reporting;

पूर्ण;

#घोषणा FDSETEMSGTRESH	_IO(2,0x4a)
/* set fdc error reporting threshold */

#घोषणा FDFLUSH  _IO(2,0x4b)
/* flush buffers क्रम media; either क्रम verअगरying media, or क्रम
 * handling a media change without closing the file descriptor */

#घोषणा FDSETMAXERRS _IOW(2, 0x4c, काष्ठा floppy_max_errors)
#घोषणा FDGETMAXERRS _IOR(2, 0x0e, काष्ठा floppy_max_errors)
/* set/get पातion and पढ़ो_track threshold. See also floppy_drive_params
 * काष्ठाure */


प्रकार अक्षर floppy_drive_name[16];
#घोषणा FDGETDRVTYP _IOR(2, 0x0f, floppy_drive_name)
/* get drive type: 5 1/4 or 3 1/2 */


/*
 * Drive parameters (user modअगरiable)
 */
काष्ठा floppy_drive_params अणु
	चिन्हित अक्षर cmos;		/* CMOS type */

	/* Spec2 is (HLD<<1 | ND), where HLD is head load समय (1=2ms, 2=4 ms
	 * etc) and ND is set means no DMA. Hardcoded to 6 (HLD=6ms, use DMA).
	 */
	अचिन्हित दीर्घ max_dtr;		/* Step rate, usec */
	अचिन्हित दीर्घ hlt;     		/* Head load/settle समय, msec */
	अचिन्हित दीर्घ hut;     		/* Head unload समय (remnant of
					 * 8" drives) */
	अचिन्हित दीर्घ srt;     		/* Step rate, usec */

	अचिन्हित दीर्घ spinup;		/* समय needed क्रम spinup (expressed
					 * in jअगरfies) */
	अचिन्हित दीर्घ spinकरोwn;		/* समयout needed क्रम spinकरोwn */
	अचिन्हित अक्षर spinकरोwn_offset;	/* decides in which position the disk
					 * will stop */
	अचिन्हित अक्षर select_delay;	/* delay to रुको after select */
	अचिन्हित अक्षर rps;		/* rotations per second */
	अचिन्हित अक्षर tracks;		/* maximum number of tracks */
	अचिन्हित दीर्घ समयout;		/* समयout क्रम पूर्णांकerrupt requests */

	अचिन्हित अक्षर पूर्णांकerleave_sect;	/* अगर there are more sectors, use
					 * पूर्णांकerleave */

	काष्ठा floppy_max_errors max_errors;

	अक्षर flags;			/* various flags, including ftd_msg */
/*
 * Announce successful media type detection and media inक्रमmation loss after
 * disk changes.
 * Also used to enable/disable prपूर्णांकing of overrun warnings.
 */

#घोषणा FTD_MSG 0x10
#घोषणा FD_BROKEN_DCL 0x20
#घोषणा FD_DEBUG 0x02
#घोषणा FD_SILENT_DCL_CLEAR 0x4
#घोषणा FD_INVERTED_DCL 0x80 /* must be 0x80, because of hardware
				considerations */

	अक्षर पढ़ो_track;		/* use पढ़ोtrack during probing? */

/*
 * Auto-detection. Each drive type has eight क्रमmats which are
 * used in succession to try to पढ़ो the disk. If the FDC cannot lock onto
 * the disk, the next क्रमmat is tried. This uses the variable 'probing'.
 */

#घोषणा FD_AUTODETECT_SIZE 8

	लघु स्वतःdetect[FD_AUTODETECT_SIZE]; /* स्वतःdetected क्रमmats */

	पूर्णांक checkfreq; /* how often should the drive be checked क्रम disk
			* changes */
	पूर्णांक native_क्रमmat; /* native क्रमmat of this drive */
पूर्ण;

क्रमागत अणु
	FD_NEED_TWADDLE_BIT,	/* more magic */
	FD_VERIFY_BIT,		/* inquire क्रम ग_लिखो protection */
	FD_DISK_NEWCHANGE_BIT,	/* change detected, and no action undertaken yet
				 * to clear media change status */
	FD_UNUSED_BIT,
	FD_DISK_CHANGED_BIT,	/* disk has been changed since last i/o */
	FD_DISK_WRITABLE_BIT,	/* disk is writable */
	FD_OPEN_SHOULD_FAIL_BIT
पूर्ण;

#घोषणा FDSETDRVPRM _IOW(2, 0x90, काष्ठा floppy_drive_params)
#घोषणा FDGETDRVPRM _IOR(2, 0x11, काष्ठा floppy_drive_params)
/* set/get drive parameters */


/*
 * Current drive state (not directly modअगरiable by user, पढ़ोonly)
 */
काष्ठा floppy_drive_काष्ठा अणु
	अचिन्हित दीर्घ flags;
/* values क्रम these flags */
#घोषणा FD_NEED_TWADDLE (1 << FD_NEED_TWADDLE_BIT)
#घोषणा FD_VERIFY (1 << FD_VERIFY_BIT)
#घोषणा FD_DISK_NEWCHANGE (1 << FD_DISK_NEWCHANGE_BIT)
#घोषणा FD_DISK_CHANGED (1 << FD_DISK_CHANGED_BIT)
#घोषणा FD_DISK_WRITABLE (1 << FD_DISK_WRITABLE_BIT)

	अचिन्हित दीर्घ spinup_date;
	अचिन्हित दीर्घ select_date;
	अचिन्हित दीर्घ first_पढ़ो_date;
	लघु probed_क्रमmat;
	लघु track; /* current track */
	लघु maxblock; /* id of highest block पढ़ो */
	लघु maxtrack; /* id of highest half track पढ़ो */
	पूर्णांक generation; /* how many diskchanges? */

/*
 * (User-provided) media inक्रमmation is _not_ discarded after a media change
 * अगर the corresponding keep_data flag is non-zero. Positive values are
 * decremented after each probe.
 */
	पूर्णांक keep_data;

	/* Prevent "aliased" accesses. */
	पूर्णांक fd_ref;
	पूर्णांक fd_device;
	अचिन्हित दीर्घ last_checked; /* when was the drive last checked क्रम a disk
			   * change? */

	अक्षर *dmabuf;
	पूर्णांक bufblocks;
पूर्ण;

#घोषणा FDGETDRVSTAT _IOR(2, 0x12, काष्ठा floppy_drive_काष्ठा)
#घोषणा FDPOLLDRVSTAT _IOR(2, 0x13, काष्ठा floppy_drive_काष्ठा)
/* get drive state: GET वापसs the cached state, POLL polls क्रम new state */


/*
 * reset FDC
 */
क्रमागत reset_mode अणु
	FD_RESET_IF_NEEDED,	/* reset only अगर the reset flags is set */
	FD_RESET_IF_RAWCMD,	/* obsolete */
	FD_RESET_ALWAYS		/* reset always */
पूर्ण;
#घोषणा FDRESET _IO(2, 0x54)


/*
 * FDC state
 */
काष्ठा floppy_fdc_state अणु
	पूर्णांक spec1;		/* spec1 value last used */
	पूर्णांक spec2;		/* spec2 value last used */
	पूर्णांक dtr;
	अचिन्हित अक्षर version;	/* FDC version code */
	अचिन्हित अक्षर करोr;
	अचिन्हित दीर्घ address;	/* io address */
	अचिन्हित पूर्णांक rawcmd:2;
	अचिन्हित पूर्णांक reset:1;
	अचिन्हित पूर्णांक need_configure:1;
	अचिन्हित पूर्णांक perp_mode:2;
	अचिन्हित पूर्णांक has_fअगरo:1;
	अचिन्हित पूर्णांक driver_version;	/* version code क्रम floppy driver */
#घोषणा FD_DRIVER_VERSION 0x100
/* user programs using the floppy API should use floppy_fdc_state to
 * get the version number of the floppy driver that they are running
 * on. If this version number is bigger than the one compiled पूर्णांकo the
 * user program (the FD_DRIVER_VERSION define), it should be prepared
 * to bigger काष्ठाures
 */

	अचिन्हित अक्षर track[4];
	/* Position of the heads of the 4 units attached to this FDC,
	 * as stored on the FDC. In the future, the position as stored
	 * on the FDC might not agree with the actual physical
	 * position of these drive heads. By allowing such
	 * disagreement, it will be possible to reset the FDC without
	 * incurring the expensive cost of repositioning all heads.
	 * Right now, these positions are hard wired to 0. */

पूर्ण;

#घोषणा FDGETFDCSTAT _IOR(2, 0x15, काष्ठा floppy_fdc_state)


/*
 * Asynchronous Write error tracking
 */
काष्ठा floppy_ग_लिखो_errors अणु
	/* Write error logging.
	 *
	 * These fields can be cleared with the FDWERRORCLR ioctl.
	 * Only ग_लिखोs that were attempted but failed due to a physical media
	 * error are logged.  ग_लिखो(2) calls that fail and वापस an error code
	 * to the user process are not counted.
	 */

	अचिन्हित पूर्णांक ग_लिखो_errors;  /* number of physical ग_लिखो errors
				     * encountered */

	/* position of first and last ग_लिखो errors */
	अचिन्हित दीर्घ first_error_sector;
	पूर्णांक           first_error_generation;
	अचिन्हित दीर्घ last_error_sector;
	पूर्णांक           last_error_generation;

	अचिन्हित पूर्णांक badness; /* highest retry count क्रम a पढ़ो or ग_लिखो
			       * operation */
पूर्ण;

#घोषणा FDWERRORCLR  _IO(2, 0x56)
/* clear ग_लिखो error and badness inक्रमmation */
#घोषणा FDWERRORGET  _IOR(2, 0x17, काष्ठा floppy_ग_लिखो_errors)
/* get ग_लिखो error and badness inक्रमmation */


/*
 * Raw commands
 */
/* new पूर्णांकerface flag: now we can करो them in batches */
#घोषणा FDHAVEBATCHEDRAWCMD

काष्ठा floppy_raw_cmd अणु
	अचिन्हित पूर्णांक flags;
#घोषणा FD_RAW_READ 1
#घोषणा FD_RAW_WRITE 2
#घोषणा FD_RAW_NO_MOTOR 4
#घोषणा FD_RAW_DISK_CHANGE 4 /* out: disk change flag was set */
#घोषणा FD_RAW_INTR 8    /* रुको क्रम an पूर्णांकerrupt */
#घोषणा FD_RAW_SPIN 0x10 /* spin up the disk क्रम this command */
#घोषणा FD_RAW_NO_MOTOR_AFTER 0x20 /* चयन the motor off after command
				    * completion */
#घोषणा FD_RAW_NEED_DISK 0x40  /* this command needs a disk to be present */
#घोषणा FD_RAW_NEED_SEEK 0x80  /* this command uses an implied seek (soft) */

/* more "in" flags */
#घोषणा FD_RAW_MORE 0x100  /* more records follow */
#घोषणा FD_RAW_STOP_IF_FAILURE 0x200 /* stop अगर we encounter a failure */
#घोषणा FD_RAW_STOP_IF_SUCCESS 0x400 /* stop अगर command successful */
#घोषणा FD_RAW_SOFTFAILURE 0x800 /* consider the वापस value क्रम failure
				  * detection too */

/* more "out" flags */
#घोषणा FD_RAW_FAILURE 0x10000 /* command sent to fdc, fdc वापसed error */
#घोषणा FD_RAW_HARDFAILURE 0x20000 /* fdc had to be reset, or समयd out */

	व्योम __user *data;
	अक्षर *kernel_data; /* location of data buffer in the kernel */
	काष्ठा floppy_raw_cmd *next; /* used क्रम chaining of raw cmd's
				      * within the kernel */
	दीर्घ length; /* in: length of dma transfer. out: reमुख्यing bytes */
	दीर्घ phys_length; /* physical length, अगर dअगरferent from dma length */
	पूर्णांक buffer_length; /* length of allocated buffer */

	अचिन्हित अक्षर rate;

#घोषणा FD_RAW_CMD_SIZE 16
#घोषणा FD_RAW_REPLY_SIZE 16
#घोषणा FD_RAW_CMD_FULLSIZE (FD_RAW_CMD_SIZE + 1 + FD_RAW_REPLY_SIZE)

	/* The command may take up the space initially पूर्णांकended क्रम the reply
	 * and the reply count. Needed क्रम दीर्घ 82078 commands such as RESTORE,
	 * which takes 17 command bytes.
	 */

	अचिन्हित अक्षर cmd_count;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित अक्षर cmd[FD_RAW_CMD_SIZE];
			अचिन्हित अक्षर reply_count;
			अचिन्हित अक्षर reply[FD_RAW_REPLY_SIZE];
		पूर्ण;
		अचिन्हित अक्षर fullcmd[FD_RAW_CMD_FULLSIZE];
	पूर्ण;
	पूर्णांक track;
	पूर्णांक resultcode;

	पूर्णांक reserved1;
	पूर्णांक reserved2;
पूर्ण;

#घोषणा FDRAWCMD _IO(2, 0x58)
/* send a raw command to the fdc. Structure size not included, because of
 * batches */

#घोषणा FDTWADDLE _IO(2, 0x59)
/* flicker motor-on bit beक्रमe पढ़ोing a sector. Experimental */


#घोषणा FDEJECT _IO(2, 0x5a)
/* eject the disk */



#पूर्ण_अगर /* _UAPI_LINUX_FD_H */
