<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* 
 * linux/mtपन.स header file क्रम Linux. Written by H. Bergman
 *
 * Modअगरied क्रम special ioctls provided by zftape in September 1997
 * by C.-J. Heine.
 */

#अगर_अघोषित _LINUX_MTIO_H
#घोषणा _LINUX_MTIO_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * Structures and definitions क्रम mag tape io control commands
 */

/* काष्ठाure क्रम MTIOCTOP - mag tape op command */
काष्ठा	mtop अणु
	लघु	mt_op;		/* operations defined below */
	पूर्णांक	mt_count;	/* how many of them */
पूर्ण;

/* Magnetic Tape operations [Not all operations supported by all drivers]: */
#घोषणा MTRESET 0	/* +reset drive in हाल of problems */
#घोषणा MTFSF	1	/* क्रमward space over FileMark,
			 * position at first record of next file 
			 */
#घोषणा MTBSF	2	/* backward space FileMark (position beक्रमe FM) */
#घोषणा MTFSR	3	/* क्रमward space record */
#घोषणा MTBSR	4	/* backward space record */
#घोषणा MTWखातापूर्ण	5	/* ग_लिखो an end-of-file record (mark) */
#घोषणा MTREW	6	/* शुरुआत */
#घोषणा MTOFFL	7	/* शुरुआत and put the drive offline (eject?) */
#घोषणा MTNOP	8	/* no op, set status only (पढ़ो with MTIOCGET) */
#घोषणा MTRETEN 9	/* retension tape */
#घोषणा MTBSFM	10	/* +backward space FileMark, position at FM */
#घोषणा MTFSFM  11	/* +क्रमward space FileMark, position at FM */
#घोषणा MTEOM	12	/* जाओ end of recorded media (क्रम appending files).
			 * MTEOM positions after the last FM, पढ़ोy क्रम
			 * appending another file.
			 */
#घोषणा MTERASE 13	/* erase tape -- be careful! */

#घोषणा MTRAS1  14	/* run self test 1 (nondeकाष्ठाive) */
#घोषणा MTRAS2	15	/* run self test 2 (deकाष्ठाive) */
#घोषणा MTRAS3  16	/* reserved क्रम self test 3 */

#घोषणा MTSETBLK 20	/* set block length (SCSI) */
#घोषणा MTSETDENSITY 21	/* set tape density (SCSI) */
#घोषणा MTSEEK	22	/* seek to block (Tandberg, etc.) */
#घोषणा MTTELL	23	/* tell block (Tandberg, etc.) */
#घोषणा MTSETDRVBUFFER 24 /* set the drive buffering according to SCSI-2 */
			/* ordinary buffered operation with code 1 */
#घोषणा MTFSS	25	/* space क्रमward over seपंचांगarks */
#घोषणा MTBSS	26	/* space backward over seपंचांगarks */
#घोषणा MTWSM	27	/* ग_लिखो seपंचांगarks */

#घोषणा MTLOCK  28	/* lock the drive करोor */
#घोषणा MTUNLOCK 29	/* unlock the drive करोor */
#घोषणा MTLOAD  30	/* execute the SCSI load command */
#घोषणा MTUNLOAD 31	/* execute the SCSI unload command */
#घोषणा MTCOMPRESSION 32/* control compression with SCSI mode page 15 */
#घोषणा MTSETPART 33	/* Change the active tape partition */
#घोषणा MTMKPART  34	/* Format the tape with one or two partitions */
#घोषणा MTWखातापूर्णI	35	/* ग_लिखो an end-of-file record (mark) in immediate mode */

/* काष्ठाure क्रम MTIOCGET - mag tape get status command */

काष्ठा	mtget अणु
	दीर्घ	mt_type;	/* type of magtape device */
	दीर्घ	mt_resid;	/* residual count: (not sure)
				 *	number of bytes ignored, or
				 *	number of files not skipped, or
				 *	number of records not skipped.
				 */
	/* the following रेजिस्टरs are device dependent */
	दीर्घ	mt_dsreg;	/* status रेजिस्टर */
	दीर्घ	mt_gstat;	/* generic (device independent) status */
	दीर्घ	mt_erreg;	/* error रेजिस्टर */
	/* The next two fields are not always used */
	__kernel_daddr_t mt_fileno;	/* number of current file on tape */
	__kernel_daddr_t mt_blkno;	/* current block number */
पूर्ण;



/*
 * Constants क्रम mt_type. Not all of these are supported,
 * and these are not all of the ones that are supported.
 */
#घोषणा MT_ISUNKNOWN		0x01
#घोषणा MT_ISQIC02		0x02	/* Generic QIC-02 tape streamer */
#घोषणा MT_ISWT5150		0x03	/* Wangtek 5150EQ, QIC-150, QIC-02 */
#घोषणा MT_ISARCHIVE_5945L2	0x04	/* Archive 5945L-2, QIC-24, QIC-02? */
#घोषणा MT_ISCMSJ500		0x05	/* CMS Jumbo 500 (QIC-02?) */
#घोषणा MT_ISTDC3610		0x06	/* Tandberg 6310, QIC-24 */
#घोषणा MT_ISARCHIVE_VP60I	0x07	/* Archive VP60i, QIC-02 */
#घोषणा MT_ISARCHIVE_2150L	0x08	/* Archive Viper 2150L */
#घोषणा MT_ISARCHIVE_2060L	0x09	/* Archive Viper 2060L */
#घोषणा MT_ISARCHIVESC499	0x0A	/* Archive SC-499 QIC-36 controller */
#घोषणा MT_ISQIC02_ALL_FEATURES	0x0F	/* Generic QIC-02 with all features */
#घोषणा MT_ISWT5099EEN24	0x11	/* Wangtek 5099-een24, 60MB, QIC-24 */
#घोषणा MT_ISTEAC_MT2ST		0x12	/* Teac MT-2ST 155mb drive, Teac DC-1 card (Wangtek type) */
#घोषणा MT_ISEVEREX_FT40A	0x32	/* Everex FT40A (QIC-40) */
#घोषणा MT_ISDDS1		0x51	/* DDS device without partitions */
#घोषणा MT_ISDDS2		0x52	/* DDS device with partitions */
#घोषणा MT_ISONSTREAM_SC        0x61   /* OnStream SCSI tape drives (SC-x0)
					  and SCSI emulated (DI, DP, USB) */
#घोषणा MT_ISSCSI1		0x71	/* Generic ANSI SCSI-1 tape unit */
#घोषणा MT_ISSCSI2		0x72	/* Generic ANSI SCSI-2 tape unit */

/* QIC-40/80/3010/3020 ftape supported drives.
 * 20bit venकरोr ID + 0x800000 (see ftape-venकरोrs.h)
 */
#घोषणा MT_ISFTAPE_UNKNOWN	0x800000 /* obsolete */
#घोषणा MT_ISFTAPE_FLAG	0x800000


/* काष्ठाure क्रम MTIOCPOS - mag tape get position command */

काष्ठा	mtpos अणु
	दीर्घ 	mt_blkno;	/* current block number */
पूर्ण;


/* mag tape io control commands */
#घोषणा	MTIOCTOP	_IOW('m', 1, काष्ठा mtop)	/* करो a mag tape op */
#घोषणा	MTIOCGET	_IOR('m', 2, काष्ठा mtget)	/* get tape status */
#घोषणा	MTIOCPOS	_IOR('m', 3, काष्ठा mtpos)	/* get tape position */


/* Generic Mag Tape (device independent) status macros क्रम examining
 * mt_gstat -- HP-UX compatible.
 * There is room क्रम more generic status bits here, but I करोn't
 * know which of them are reserved. At least three or so should
 * be added to make this really useful.
 */
#घोषणा GMT_खातापूर्ण(x)              ((x) & 0x80000000)
#घोषणा GMT_BOT(x)              ((x) & 0x40000000)
#घोषणा GMT_EOT(x)              ((x) & 0x20000000)
#घोषणा GMT_SM(x)               ((x) & 0x10000000)  /* DDS seपंचांगark */
#घोषणा GMT_EOD(x)              ((x) & 0x08000000)  /* DDS EOD */
#घोषणा GMT_WR_PROT(x)          ((x) & 0x04000000)
/* #घोषणा GMT_ ? 		((x) & 0x02000000) */
#घोषणा GMT_ONLINE(x)           ((x) & 0x01000000)
#घोषणा GMT_D_6250(x)           ((x) & 0x00800000)
#घोषणा GMT_D_1600(x)           ((x) & 0x00400000)
#घोषणा GMT_D_800(x)            ((x) & 0x00200000)
/* #घोषणा GMT_ ? 		((x) & 0x00100000) */
/* #घोषणा GMT_ ? 		((x) & 0x00080000) */
#घोषणा GMT_DR_OPEN(x)          ((x) & 0x00040000)  /* करोor खोलो (no tape) */
/* #घोषणा GMT_ ? 		((x) & 0x00020000) */
#घोषणा GMT_IM_REP_EN(x)        ((x) & 0x00010000)  /* immediate report mode */
#घोषणा GMT_CLN(x)              ((x) & 0x00008000)  /* cleaning requested */
/* 15 generic status bits unused */


/* SCSI-tape specअगरic definitions */
/* Bitfield shअगरts in the status  */
#घोषणा MT_ST_BLKSIZE_SHIFT	0
#घोषणा MT_ST_BLKSIZE_MASK	0xffffff
#घोषणा MT_ST_DENSITY_SHIFT	24
#घोषणा MT_ST_DENSITY_MASK	0xff000000

#घोषणा MT_ST_SOFTERR_SHIFT	0
#घोषणा MT_ST_SOFTERR_MASK	0xffff

/* Bitfields क्रम the MTSETDRVBUFFER ioctl */
#घोषणा MT_ST_OPTIONS		0xf0000000
#घोषणा MT_ST_BOOLEANS		0x10000000
#घोषणा MT_ST_SETBOOLEANS	0x30000000
#घोषणा MT_ST_CLEARBOOLEANS	0x40000000
#घोषणा MT_ST_WRITE_THRESHOLD	0x20000000
#घोषणा MT_ST_DEF_BLKSIZE	0x50000000
#घोषणा MT_ST_DEF_OPTIONS	0x60000000
#घोषणा MT_ST_TIMEOUTS		0x70000000
#घोषणा MT_ST_SET_TIMEOUT	(MT_ST_TIMEOUTS | 0x000000)
#घोषणा MT_ST_SET_LONG_TIMEOUT	(MT_ST_TIMEOUTS | 0x100000)
#घोषणा MT_ST_SET_CLN		0x80000000

#घोषणा MT_ST_BUFFER_WRITES	0x1
#घोषणा MT_ST_ASYNC_WRITES	0x2
#घोषणा MT_ST_READ_AHEAD	0x4
#घोषणा MT_ST_DEBUGGING		0x8
#घोषणा MT_ST_TWO_FM		0x10
#घोषणा MT_ST_FAST_MTEOM	0x20
#घोषणा MT_ST_AUTO_LOCK		0x40
#घोषणा MT_ST_DEF_WRITES	0x80
#घोषणा MT_ST_CAN_BSR		0x100
#घोषणा MT_ST_NO_BLKLIMS	0x200
#घोषणा MT_ST_CAN_PARTITIONS    0x400
#घोषणा MT_ST_SCSI2LOGICAL      0x800
#घोषणा MT_ST_SYSV              0x1000
#घोषणा MT_ST_NOWAIT            0x2000
#घोषणा MT_ST_SILI		0x4000
#घोषणा MT_ST_NOWAIT_खातापूर्ण	0x8000

/* The mode parameters to be controlled. Parameter chosen with bits 20-28 */
#घोषणा MT_ST_CLEAR_DEFAULT	0xfffff
#घोषणा MT_ST_DEF_DENSITY	(MT_ST_DEF_OPTIONS | 0x100000)
#घोषणा MT_ST_DEF_COMPRESSION	(MT_ST_DEF_OPTIONS | 0x200000)
#घोषणा MT_ST_DEF_DRVBUFFER	(MT_ST_DEF_OPTIONS | 0x300000)

/* The offset क्रम the arguments क्रम the special HP changer load command. */
#घोषणा MT_ST_HPLOADER_OFFSET 10000

#पूर्ण_अगर /* _LINUX_MTIO_H */
