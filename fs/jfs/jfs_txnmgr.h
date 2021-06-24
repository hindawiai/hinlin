<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */
#अगर_अघोषित _H_JFS_TXNMGR
#घोषणा _H_JFS_TXNMGR

#समावेश "jfs_logmgr.h"

/*
 * Hide implementation of TxBlock and TxLock
 */
#घोषणा tid_to_tblock(tid) (&TxBlock[tid])

#घोषणा lid_to_tlock(lid) (&TxLock[lid])

/*
 *	transaction block
 */
काष्ठा tblock अणु
	/*
	 * tblock and jbuf_t common area: काष्ठा logsyncblk
	 *
	 * the following 5 fields are the same as काष्ठा logsyncblk
	 * which is common to tblock and jbuf to क्रमm logsynclist
	 */
	u16 xflag;		/* tx commit type */
	u16 flag;		/* tx commit state */
	lid_t dummy;		/* Must keep काष्ठाures common */
	s32 lsn;		/* recovery lsn */
	काष्ठा list_head synclist;	/* logsynclist link */

	/* lock management */
	काष्ठा super_block *sb;	/* super block */
	lid_t next;		/* index of first tlock of tid */
	lid_t last;		/* index of last tlock of tid */
	रुको_queue_head_t रुकोor;	/* tids रुकोing on this tid */

	/* log management */
	u32 logtid;		/* log transaction id */

	/* commit management */
	काष्ठा list_head cqueue;	/* commit queue list */
	s32 clsn;		/* commit lsn */
	काष्ठा lbuf *bp;
	s32 pn;			/* commit record log page number */
	s32 eor;		/* commit record eor */
	रुको_queue_head_t gcरुको;	/* group commit event list:
					 * पढ़ोy transactions रुको on this
					 * event क्रम group commit completion.
					 */
	जोड़ अणु
		काष्ठा inode *ip; /* inode being deleted */
		pxd_t ixpxd;	/* pxd of inode extent क्रम created inode */
	पूर्ण u;
	u32 ino;		/* inode number being created */
पूर्ण;

बाह्य काष्ठा tblock *TxBlock;	/* transaction block table */

/* commit flags: tblk->xflag */
#घोषणा	COMMIT_SYNC	0x0001	/* synchronous commit */
#घोषणा	COMMIT_FORCE	0x0002	/* क्रमce pageout at end of commit */
#घोषणा	COMMIT_FLUSH	0x0004	/* init flush at end of commit */
#घोषणा COMMIT_MAP	0x00f0
#घोषणा	COMMIT_PMAP	0x0010	/* update pmap */
#घोषणा	COMMIT_WMAP	0x0020	/* update wmap */
#घोषणा	COMMIT_PWMAP	0x0040	/* update pwmap */
#घोषणा	COMMIT_FREE	0x0f00
#घोषणा	COMMIT_DELETE	0x0100	/* inode delete */
#घोषणा	COMMIT_TRUNCATE	0x0200	/* file truncation */
#घोषणा	COMMIT_CREATE	0x0400	/* inode create */
#घोषणा	COMMIT_LAZY	0x0800	/* lazy commit */
#घोषणा COMMIT_PAGE	0x1000	/* Identअगरies element as metapage */
#घोषणा COMMIT_INODE	0x2000	/* Identअगरies element as inode */

/* group commit flags tblk->flag: see jfs_logmgr.h */

/*
 *	transaction lock
 */
काष्ठा tlock अणु
	lid_t next;		/* 2: index next lockword on tid locklist
				 *	    next lockword on मुक्तlist
				 */
	tid_t tid;		/* 2: transaction id holding lock */

	u16 flag;		/* 2: lock control */
	u16 type;		/* 2: log type */

	काष्ठा metapage *mp;	/* 4/8: object page buffer locked */
	काष्ठा inode *ip;	/* 4/8: object */
	/* (16) */

	s16 lock[24];		/* 48: overlay area */
पूर्ण;				/* (64) */

बाह्य काष्ठा tlock *TxLock;	/* transaction lock table */

/*
 * tlock flag
 */
/* txLock state */
#घोषणा tlckPAGELOCK		0x8000
#घोषणा tlckINODELOCK		0x4000
#घोषणा tlckLINELOCK		0x2000
#घोषणा tlckINLINELOCK		0x1000
/* lmLog state */
#घोषणा tlckLOG			0x0800
/* updateMap state */
#घोषणा	tlckUPDATEMAP		0x0080
#घोषणा	tlckसूचीECTORY		0x0040
/* मुक्तLock state */
#घोषणा tlckFREELOCK		0x0008
#घोषणा tlckWRITEPAGE		0x0004
#घोषणा tlckFREEPAGE		0x0002

/*
 * tlock type
 */
#घोषणा	tlckTYPE		0xfe00
#घोषणा	tlckINODE		0x8000
#घोषणा	tlckXTREE		0x4000
#घोषणा	tlckDTREE		0x2000
#घोषणा	tlckMAP			0x1000
#घोषणा	tlckEA			0x0800
#घोषणा	tlckACL			0x0400
#घोषणा	tlckDATA		0x0200
#घोषणा	tlckBTROOT		0x0100

#घोषणा	tlckOPERATION		0x00ff
#घोषणा tlckGROW		0x0001	/* file grow */
#घोषणा tlckREMOVE		0x0002	/* file delete */
#घोषणा tlckTRUNCATE		0x0004	/* file truncate */
#घोषणा tlckRELOCATE		0x0008	/* file/directory relocate */
#घोषणा tlckENTRY		0x0001	/* directory insert/delete */
#घोषणा tlckEXTEND		0x0002	/* directory extend in-line */
#घोषणा tlckSPLIT		0x0010	/* splited page */
#घोषणा tlckNEW			0x0020	/* new page from split */
#घोषणा tlckFREE		0x0040	/* मुक्त page */
#घोषणा tlckRELINK		0x0080	/* update sibling poपूर्णांकer */

/*
 *	linelock क्रम lmLog()
 *
 * note: linelock and its variations are overlaid
 * at tlock.lock: watch क्रम alignment;
 */
काष्ठा lv अणु
	u8 offset;		/* 1: */
	u8 length;		/* 1: */
पूर्ण;				/* (2) */

#घोषणा	TLOCKSHORT	20
#घोषणा	TLOCKLONG	28

काष्ठा linelock अणु
	lid_t next;		/* 2: next linelock */

	s8 maxcnt;		/* 1: */
	s8 index;		/* 1: */

	u16 flag;		/* 2: */
	u8 type;		/* 1: */
	u8 l2linesize;		/* 1: log2 of linesize */
	/* (8) */

	काष्ठा lv lv[20];	/* 40: */
पूर्ण;				/* (48) */

#घोषणा dt_lock	linelock

काष्ठा xtlock अणु
	lid_t next;		/* 2: */

	s8 maxcnt;		/* 1: */
	s8 index;		/* 1: */

	u16 flag;		/* 2: */
	u8 type;		/* 1: */
	u8 l2linesize;		/* 1: log2 of linesize */
				/* (8) */

	काष्ठा lv header;	/* 2: */
	काष्ठा lv lwm;		/* 2: low water mark */
	काष्ठा lv hwm;		/* 2: high water mark */
	काष्ठा lv twm;		/* 2: */
				/* (16) */

	s32 pxdlock[8];		/* 32: */
पूर्ण;				/* (48) */


/*
 *	maplock क्रम txUpdateMap()
 *
 * note: maplock and its variations are overlaid
 * at tlock.lock/linelock: watch क्रम alignment;
 * N.B. next field may be set by linelock, and should not
 * be modअगरied by maplock;
 * N.B. index of the first pxdlock specअगरies index of next
 * मुक्त maplock (i.e., number of maplock) in the tlock;
 */
काष्ठा maplock अणु
	lid_t next;		/* 2: */

	u8 maxcnt;		/* 2: */
	u8 index;		/* 2: next मुक्त maplock index */

	u16 flag;		/* 2: */
	u8 type;		/* 1: */
	u8 count;		/* 1: number of pxd/xad */
				/* (8) */

	pxd_t pxd;		/* 8: */
पूर्ण;				/* (16): */

/* maplock flag */
#घोषणा	mlckALLOC		0x00f0
#घोषणा	mlckALLOCXADLIST	0x0080
#घोषणा	mlckALLOCPXDLIST	0x0040
#घोषणा	mlckALLOCXAD		0x0020
#घोषणा	mlckALLOCPXD		0x0010
#घोषणा	mlckFREE		0x000f
#घोषणा	mlckFREEXADLIST		0x0008
#घोषणा	mlckFREEPXDLIST		0x0004
#घोषणा	mlckFREEXAD		0x0002
#घोषणा	mlckFREEPXD		0x0001

#घोषणा	pxd_lock	maplock

काष्ठा xdlistlock अणु
	lid_t next;		/* 2: */

	u8 maxcnt;		/* 2: */
	u8 index;		/* 2: */

	u16 flag;		/* 2: */
	u8 type;		/* 1: */
	u8 count;		/* 1: number of pxd/xad */
				/* (8) */

	/*
	 * We need xdlist to be 64 bits (8 bytes), regardless of
	 * whether व्योम * is 32 or 64 bits
	 */
	जोड़ अणु
		व्योम *_xdlist;	/* pxd/xad list */
		s64 pad;	/* 8: Force 64-bit xdlist size */
	पूर्ण जोड़64;
पूर्ण;				/* (16): */

#घोषणा xdlist जोड़64._xdlist

/*
 *	commit
 *
 * parameter to the commit manager routines
 */
काष्ठा commit अणु
	tid_t tid;		/* tid = index of tblock */
	पूर्णांक flag;		/* flags */
	काष्ठा jfs_log *log;	/* log */
	काष्ठा super_block *sb;	/* superblock */

	पूर्णांक nip;		/* number of entries in iplist */
	काष्ठा inode **iplist;	/* list of poपूर्णांकers to inodes */

	/* log record descriptor on 64-bit boundary */
	काष्ठा lrd lrd;		/* : log record descriptor */
पूर्ण;

/*
 * बाह्यal declarations
 */
बाह्य पूर्णांक jfs_tlocks_low;

बाह्य पूर्णांक txInit(व्योम);
बाह्य व्योम txExit(व्योम);
बाह्य काष्ठा tlock *txLock(tid_t, काष्ठा inode *, काष्ठा metapage *, पूर्णांक);
बाह्य काष्ठा tlock *txMaplock(tid_t, काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक txCommit(tid_t, पूर्णांक, काष्ठा inode **, पूर्णांक);
बाह्य tid_t txBegin(काष्ठा super_block *, पूर्णांक);
बाह्य व्योम txBeginAnon(काष्ठा super_block *);
बाह्य व्योम txEnd(tid_t);
बाह्य व्योम txAbort(tid_t, पूर्णांक);
बाह्य काष्ठा linelock *txLinelock(काष्ठा linelock *);
बाह्य व्योम txFreeMap(काष्ठा inode *, काष्ठा maplock *, काष्ठा tblock *, पूर्णांक);
बाह्य व्योम txEA(tid_t, काष्ठा inode *, dxd_t *, dxd_t *);
बाह्य व्योम txFreelock(काष्ठा inode *);
बाह्य पूर्णांक lmLog(काष्ठा jfs_log *, काष्ठा tblock *, काष्ठा lrd *,
		 काष्ठा tlock *);
बाह्य व्योम txQuiesce(काष्ठा super_block *);
बाह्य व्योम txResume(काष्ठा super_block *);
बाह्य व्योम txLazyUnlock(काष्ठा tblock *);
बाह्य पूर्णांक jfs_lazycommit(व्योम *);
बाह्य पूर्णांक jfs_sync(व्योम *);
#पूर्ण_अगर				/* _H_JFS_TXNMGR */
