<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */
#अगर_अघोषित	_H_JFS_LOGMGR
#घोषणा _H_JFS_LOGMGR

#समावेश <linux/uuid.h>

#समावेश "jfs_filsys.h"
#समावेश "jfs_lock.h"

/*
 *	log manager configuration parameters
 */

/* log page size */
#घोषणा	LOGPSIZE	4096
#घोषणा	L2LOGPSIZE	12

#घोषणा LOGPAGES	16	/* Log pages per mounted file प्रणाली */

/*
 *	log logical volume
 *
 * a log is used to make the commit operation on journalled
 * files within the same logical volume group atomic.
 * a log is implemented with a logical volume.
 * there is one log per logical volume group.
 *
 * block 0 of the log logical volume is not used (ipl etc).
 * block 1 contains a log "superblock" and is used by logFormat(),
 * lmLogInit(), lmLogShutकरोwn(), and logReकरो() to record status
 * of the log but is not otherwise used during normal processing.
 * blocks 2 - (N-1) are used to contain log records.
 *
 * when a volume group is varied-on-line, logReकरो() must have
 * been executed beक्रमe the file प्रणालीs (logical volumes) in
 * the volume group can be mounted.
 */
/*
 *	log superblock (block 1 of logical volume)
 */
#घोषणा	LOGSUPER_B	1
#घोषणा	LOGSTART_B	2

#घोषणा	LOGMAGIC	0x87654321
#घोषणा	LOGVERSION	1

#घोषणा MAX_ACTIVE	128	/* Max active file प्रणालीs sharing log */

काष्ठा logsuper अणु
	__le32 magic;		/* 4: log lv identअगरier */
	__le32 version;		/* 4: version number */
	__le32 serial;		/* 4: log खोलो/mount counter */
	__le32 size;		/* 4: size in number of LOGPSIZE blocks */
	__le32 bsize;		/* 4: logical block size in byte */
	__le32 l2bsize;		/* 4: log2 of bsize */

	__le32 flag;		/* 4: option */
	__le32 state;		/* 4: state - see below */

	__le32 end;		/* 4: addr of last log record set by logreकरो */
	uuid_t uuid;		/* 16: 128-bit journal uuid */
	अक्षर label[16];		/* 16: journal label */
	काष्ठा अणु
		uuid_t uuid;
	पूर्ण active[MAX_ACTIVE];	/* 2048: active file प्रणालीs list */
पूर्ण;

/* log flag: commit option (see jfs_filsys.h) */

/* log state */
#घोषणा	LOGMOUNT	0	/* log mounted by lmLogInit() */
#घोषणा LOGREDONE	1	/* log shutकरोwn by lmLogShutकरोwn().
				 * log reकरो completed by logreकरो().
				 */
#घोषणा LOGWRAP		2	/* log wrapped */
#घोषणा LOGREADERR	3	/* log पढ़ो error detected in logreकरो() */


/*
 *	log logical page
 *
 * (this comment should be rewritten !)
 * the header and trailer काष्ठाures (h,t) will normally have
 * the same page and eor value.
 * An exception to this occurs when a complete page ग_लिखो is not
 * accomplished on a घातer failure. Since the hardware may "split write"
 * sectors in the page, any out of order sequence may occur during घातerfail
 * and needs to be recognized during log replay.  The xor value is
 * an "exclusive or" of all log words in the page up to eor.  This
 * 32 bit eor is stored with the top 16 bits in the header and the
 * bottom 16 bits in the trailer.  logreकरो can easily recognize pages
 * that were not completed by reस्थिरructing this eor and checking
 * the log page.
 *
 * Previous versions of the operating प्रणाली did not allow split
 * ग_लिखोs and detected partially written records in logreकरो by
 * ordering the updates to the header, trailer, and the move of data
 * पूर्णांकo the logdata area.  The order: (1) data is moved (2) header
 * is updated (3) trailer is updated.  In logreकरो, when the header
 * dअगरfered from the trailer, the header and trailer were reconciled
 * as follows: अगर h.page != t.page they were set to the smaller of
 * the two and h.eor and t.eor set to 8 (i.e. empty page). अगर (only)
 * h.eor != t.eor they were set to the smaller of their two values.
 */
काष्ठा logpage अणु
	काष्ठा अणु		/* header */
		__le32 page;	/* 4: log sequence page number */
		__le16 rsrvd;	/* 2: */
		__le16 eor;	/* 2: end-of-log offset of lasrt record ग_लिखो */
	पूर्ण h;

	__le32 data[LOGPSIZE / 4 - 4];	/* log record area */

	काष्ठा अणु		/* trailer */
		__le32 page;	/* 4: normally the same as h.page */
		__le16 rsrvd;	/* 2: */
		__le16 eor;	/* 2: normally the same as h.eor */
	पूर्ण t;
पूर्ण;

#घोषणा LOGPHDRSIZE	8	/* log page header size */
#घोषणा LOGPTLRSIZE	8	/* log page trailer size */


/*
 *	log record
 *
 * (this comment should be rewritten !)
 * jfs uses only "after" log records (only a single ग_लिखोr is allowed
 * in a page, pages are written to temporary paging space अगर
 * they must be written to disk beक्रमe commit, and i/o is
 * scheduled क्रम modअगरied pages to their home location after
 * the log records containing the after values and the commit
 * record is written to the log on disk, unकरो discards the copy
 * in मुख्य-memory.)
 *
 * a log record consists of a data area of variable length followed by
 * a descriptor of fixed size LOGRDSIZE bytes.
 * the data area is rounded up to an पूर्णांकegral number of 4-bytes and
 * must be no दीर्घer than LOGPSIZE.
 * the descriptor is of size of multiple of 4-bytes and aligned on a
 * 4-byte boundary.
 * records are packed one after the other in the data area of log pages.
 * (someबार a DUMMY record is inserted so that at least one record ends
 * on every page or the दीर्घest record is placed on at most two pages).
 * the field eor in page header/trailer poपूर्णांकs to the byte following
 * the last record on a page.
 */

/* log record types */
#घोषणा LOG_COMMIT		0x8000
#घोषणा LOG_SYNCPT		0x4000
#घोषणा LOG_MOUNT		0x2000
#घोषणा LOG_REDOPAGE		0x0800
#घोषणा LOG_NOREDOPAGE		0x0080
#घोषणा LOG_NOREDOINOEXT	0x0040
#घोषणा LOG_UPDATEMAP		0x0008
#घोषणा LOG_NOREDOखाता		0x0001

/* REDOPAGE/NOREDOPAGE log record data type */
#घोषणा	LOG_INODE		0x0001
#घोषणा	LOG_XTREE		0x0002
#घोषणा	LOG_DTREE		0x0004
#घोषणा	LOG_BTROOT		0x0010
#घोषणा	LOG_EA			0x0020
#घोषणा	LOG_ACL			0x0040
#घोषणा	LOG_DATA		0x0080
#घोषणा	LOG_NEW			0x0100
#घोषणा	LOG_EXTEND		0x0200
#घोषणा LOG_RELOCATE		0x0400
#घोषणा LOG_सूची_XTREE		0x0800	/* Xtree is in directory inode */

/* UPDATEMAP log record descriptor type */
#घोषणा	LOG_ALLOCXADLIST	0x0080
#घोषणा	LOG_ALLOCPXDLIST	0x0040
#घोषणा	LOG_ALLOCXAD		0x0020
#घोषणा	LOG_ALLOCPXD		0x0010
#घोषणा	LOG_FREEXADLIST		0x0008
#घोषणा	LOG_FREEPXDLIST		0x0004
#घोषणा	LOG_FREEXAD		0x0002
#घोषणा	LOG_FREEPXD		0x0001


काष्ठा lrd अणु
	/*
	 * type independent area
	 */
	__le32 logtid;		/* 4: log transaction identअगरier */
	__le32 backchain;	/* 4: ptr to prev record of same transaction */
	__le16 type;		/* 2: record type */
	__le16 length;		/* 2: length of data in record (in byte) */
	__le32 aggregate;	/* 4: file प्रणाली lv/aggregate */
	/* (16) */

	/*
	 * type dependent area (20)
	 */
	जोड़ अणु

		/*
		 *	COMMIT: commit
		 *
		 * transaction commit: no type-dependent inक्रमmation;
		 */

		/*
		 *	REDOPAGE: after-image
		 *
		 * apply after-image;
		 *
		 * N.B. REDOPAGE, NOREDOPAGE, and UPDATEMAP must be same क्रमmat;
		 */
		काष्ठा अणु
			__le32 fileset;	/* 4: fileset number */
			__le32 inode;	/* 4: inode number */
			__le16 type;	/* 2: REDOPAGE record type */
			__le16 l2linesize;	/* 2: log2 of line size */
			pxd_t pxd;	/* 8: on-disk page pxd */
		पूर्ण reकरोpage;	/* (20) */

		/*
		 *	NOREDOPAGE: the page is मुक्तd
		 *
		 * करो not apply after-image records which precede this record
		 * in the log with the same page block number to this page.
		 *
		 * N.B. REDOPAGE, NOREDOPAGE, and UPDATEMAP must be same क्रमmat;
		 */
		काष्ठा अणु
			__le32 fileset;	/* 4: fileset number */
			__le32 inode;	/* 4: inode number */
			__le16 type;	/* 2: NOREDOPAGE record type */
			__le16 rsrvd;	/* 2: reserved */
			pxd_t pxd;	/* 8: on-disk page pxd */
		पूर्ण noreकरोpage;	/* (20) */

		/*
		 *	UPDATEMAP: update block allocation map
		 *
		 * either in-line PXD,
		 * or     out-of-line  XADLIST;
		 *
		 * N.B. REDOPAGE, NOREDOPAGE, and UPDATEMAP must be same क्रमmat;
		 */
		काष्ठा अणु
			__le32 fileset;	/* 4: fileset number */
			__le32 inode;	/* 4: inode number */
			__le16 type;	/* 2: UPDATEMAP record type */
			__le16 nxd;	/* 2: number of extents */
			pxd_t pxd;	/* 8: pxd */
		पूर्ण updatemap;	/* (20) */

		/*
		 *	NOREDOINOEXT: the inode extent is मुक्तd
		 *
		 * करो not apply after-image records which precede this
		 * record in the log with the any of the 4 page block
		 * numbers in this inode extent.
		 *
		 * NOTE: The fileset and pxd fields MUST reमुख्य in
		 *       the same fields in the REDOPAGE record क्रमmat.
		 *
		 */
		काष्ठा अणु
			__le32 fileset;	/* 4: fileset number */
			__le32 iagnum;	/* 4: IAG number     */
			__le32 inoext_idx;	/* 4: inode extent index */
			pxd_t pxd;	/* 8: on-disk page pxd */
		पूर्ण noreकरोinoext;	/* (20) */

		/*
		 *	SYNCPT: log sync poपूर्णांक
		 *
		 * replay log up to syncpt address specअगरied;
		 */
		काष्ठा अणु
			__le32 sync;	/* 4: syncpt address (0 = here) */
		पूर्ण syncpt;

		/*
		 *	MOUNT: file प्रणाली mount
		 *
		 * file प्रणाली mount: no type-dependent inक्रमmation;
		 */

		/*
		 *	? FREEXTENT: मुक्त specअगरied extent(s)
		 *
		 * मुक्त specअगरied extent(s) from block allocation map
		 * N.B.: nextents should be length of data/माप(xad_t)
		 */
		काष्ठा अणु
			__le32 type;	/* 4: FREEXTENT record type */
			__le32 nextent;	/* 4: number of extents */

			/* data: PXD or XAD list */
		पूर्ण मुक्तxtent;

		/*
		 *	? NOREDOखाता: this file is मुक्तd
		 *
		 * करो not apply records which precede this record in the log
		 * with the same inode number.
		 *
		 * NOREDOखाता must be the first to be written at commit
		 * (last to be पढ़ो in logreकरो()) - it prevents
		 * replay of preceding updates of all preceding generations
		 * of the inumber esp. the on-disk inode itself.
		 */
		काष्ठा अणु
			__le32 fileset;	/* 4: fileset number */
			__le32 inode;	/* 4: inode number */
		पूर्ण noreकरोfile;

		/*
		 *	? NEWPAGE:
		 *
		 * metadata type dependent
		 */
		काष्ठा अणु
			__le32 fileset;	/* 4: fileset number */
			__le32 inode;	/* 4: inode number */
			__le32 type;	/* 4: NEWPAGE record type */
			pxd_t pxd;	/* 8: on-disk page pxd */
		पूर्ण newpage;

		/*
		 *	? DUMMY: filler
		 *
		 * no type-dependent inक्रमmation
		 */
	पूर्ण log;
पूर्ण;					/* (36) */

#घोषणा	LOGRDSIZE	(माप(काष्ठा lrd))

/*
 *	line vector descriptor
 */
काष्ठा lvd अणु
	__le16 offset;
	__le16 length;
पूर्ण;


/*
 *	log logical volume
 */
काष्ठा jfs_log अणु

	काष्ठा list_head sb_list;/*  This is used to sync metadata
				 *    beक्रमe writing syncpt.
				 */
	काष्ठा list_head journal_list; /* Global list */
	काष्ठा block_device *bdev; /* 4: log lv poपूर्णांकer */
	पूर्णांक serial;		/* 4: log mount serial number */

	s64 base;		/* @8: log extent address (अंतरभूत log ) */
	पूर्णांक size;		/* 4: log size in log page (in page) */
	पूर्णांक l2bsize;		/* 4: log2 of bsize */

	अचिन्हित दीर्घ flag;	/* 4: flag */

	काष्ठा lbuf *lbuf_मुक्त;	/* 4: मुक्त lbufs */
	रुको_queue_head_t मुक्त_रुको;	/* 4: */

	/* log ग_लिखो */
	पूर्णांक logtid;		/* 4: log tid */
	पूर्णांक page;		/* 4: page number of eol page */
	पूर्णांक eor;		/* 4: eor of last record in eol page */
	काष्ठा lbuf *bp;	/* 4: current log page buffer */

	काष्ठा mutex loglock;	/* 4: log ग_लिखो serialization lock */

	/* syncpt */
	पूर्णांक nextsync;		/* 4: bytes to ग_लिखो beक्रमe next syncpt */
	पूर्णांक active;		/* 4: */
	रुको_queue_head_t syncरुको;	/* 4: */

	/* commit */
	uपूर्णांक cflag;		/* 4: */
	काष्ठा list_head cqueue; /* FIFO commit queue */
	काष्ठा tblock *flush_tblk; /* tblk we're रुकोing on क्रम flush */
	पूर्णांक gcrtc;		/* 4: GC_READY transaction count */
	काष्ठा tblock *gclrt;	/* 4: latest GC_READY transaction */
	spinlock_t gघड़ी;	/* 4: group commit lock */
	पूर्णांक logsize;		/* 4: log data area size in byte */
	पूर्णांक lsn;		/* 4: end-of-log */
	पूर्णांक clsn;		/* 4: clsn */
	पूर्णांक syncpt;		/* 4: addr of last syncpt record */
	पूर्णांक sync;		/* 4: addr from last logsync() */
	काष्ठा list_head synclist;	/* 8: logsynclist anchor */
	spinlock_t synघड़ी;	/* 4: synclist lock */
	काष्ठा lbuf *wqueue;	/* 4: log pageout queue */
	पूर्णांक count;		/* 4: count */
	uuid_t uuid;		/* 16: 128-bit uuid of log device */

	पूर्णांक no_पूर्णांकegrity;	/* 3: flag to disable journaling to disk */
पूर्ण;

/*
 * Log flag
 */
#घोषणा log_INLINELOG	1
#घोषणा log_SYNCBARRIER	2
#घोषणा log_QUIESCE	3
#घोषणा log_FLUSH	4

/*
 * group commit flag
 */
/* jfs_log */
#घोषणा logGC_PAGEOUT	0x00000001

/* tblock/lbuf */
#घोषणा tblkGC_QUEUE		0x0001
#घोषणा tblkGC_READY		0x0002
#घोषणा tblkGC_COMMIT		0x0004
#घोषणा tblkGC_COMMITTED	0x0008
#घोषणा tblkGC_EOP		0x0010
#घोषणा tblkGC_FREE		0x0020
#घोषणा tblkGC_LEADER		0x0040
#घोषणा tblkGC_ERROR		0x0080
#घोषणा tblkGC_LAZY		0x0100	// D230860
#घोषणा tblkGC_UNLOCKED		0x0200	// D230860

/*
 *		log cache buffer header
 */
काष्ठा lbuf अणु
	काष्ठा jfs_log *l_log;	/* 4: log associated with buffer */

	/*
	 * data buffer base area
	 */
	uपूर्णांक l_flag;		/* 4: pageout control flags */

	काष्ठा lbuf *l_wqnext;	/* 4: ग_लिखो queue link */
	काष्ठा lbuf *l_मुक्तlist;	/* 4: मुक्तlistlink */

	पूर्णांक l_pn;		/* 4: log page number */
	पूर्णांक l_eor;		/* 4: log record eor */
	पूर्णांक l_ceor;		/* 4: committed log record eor */

	s64 l_blkno;		/* 8: log page block number */
	caddr_t l_ldata;	/* 4: data page */
	काष्ठा page *l_page;	/* The page itself */
	uपूर्णांक l_offset;		/* Offset of l_ldata within the page */

	रुको_queue_head_t l_ioevent;	/* 4: i/o करोne event */
पूर्ण;

/* Reuse l_मुक्तlist क्रम redrive list */
#घोषणा l_redrive_next l_मुक्तlist

/*
 *	logsynclist block
 *
 * common logsyncblk prefix क्रम jbuf_t and tblock
 */
काष्ठा logsyncblk अणु
	u16 xflag;		/* flags */
	u16 flag;		/* only meaninful in tblock */
	lid_t lid;		/* lock id */
	s32 lsn;		/* log sequence number */
	काष्ठा list_head synclist;	/* log sync list link */
पूर्ण;

/*
 *	logsynclist serialization (per log)
 */

#घोषणा LOGSYNC_LOCK_INIT(log) spin_lock_init(&(log)->synघड़ी)
#घोषणा LOGSYNC_LOCK(log, flags) spin_lock_irqsave(&(log)->synघड़ी, flags)
#घोषणा LOGSYNC_UNLOCK(log, flags) \
	spin_unlock_irqrestore(&(log)->synघड़ी, flags)

/* compute the dअगरference in bytes of lsn from sync poपूर्णांक */
#घोषणा logdअगरf(dअगरf, lsn, log)\
अणु\
	dअगरf = (lsn) - (log)->syncpt;\
	अगर (dअगरf < 0)\
		dअगरf += (log)->logsize;\
पूर्ण

बाह्य पूर्णांक lmLogOpen(काष्ठा super_block *sb);
बाह्य पूर्णांक lmLogClose(काष्ठा super_block *sb);
बाह्य पूर्णांक lmLogShutकरोwn(काष्ठा jfs_log * log);
बाह्य पूर्णांक lmLogInit(काष्ठा jfs_log * log);
बाह्य पूर्णांक lmLogFormat(काष्ठा jfs_log *log, s64 logAddress, पूर्णांक logSize);
बाह्य पूर्णांक lmGroupCommit(काष्ठा jfs_log *, काष्ठा tblock *);
बाह्य पूर्णांक jfsIOWait(व्योम *);
बाह्य व्योम jfs_flush_journal(काष्ठा jfs_log * log, पूर्णांक रुको);
बाह्य व्योम jfs_syncpt(काष्ठा jfs_log *log, पूर्णांक hard_sync);

#पूर्ण_अगर				/* _H_JFS_LOGMGR */
