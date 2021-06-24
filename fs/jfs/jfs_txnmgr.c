<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2005
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

/*
 *	jfs_txnmgr.c: transaction manager
 *
 * notes:
 * transaction starts with txBegin() and ends with txCommit()
 * or txAbort().
 *
 * tlock is acquired at the समय of update;
 * (obviate scan at commit समय क्रम xtree and dtree)
 * tlock and mp poपूर्णांकs to each other;
 * (no hashlist क्रम mp -> tlock).
 *
 * special हालs:
 * tlock on in-memory inode:
 * in-place tlock in the in-memory inode itself;
 * converted to page lock by iWrite() at commit समय.
 *
 * tlock during ग_लिखो()/mmap() under anonymous transaction (tid = 0):
 * transferred (?) to transaction at commit समय.
 *
 * use the page itself to update allocation maps
 * (obviate पूर्णांकermediate replication of allocation/deallocation data)
 * hold on to mp+lock thru update of maps
 */

#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/completion.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/seq_file.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_debug.h"

/*
 *	transaction management काष्ठाures
 */
अटल काष्ठा अणु
	पूर्णांक मुक्तtid;		/* index of a मुक्त tid काष्ठाure */
	पूर्णांक मुक्तlock;		/* index first मुक्त lock word */
	रुको_queue_head_t मुक्तरुको;	/* eventlist of मुक्त tblock */
	रुको_queue_head_t मुक्तlockरुको;	/* eventlist of मुक्त tlock */
	रुको_queue_head_t lowlockरुको;	/* eventlist of ample tlocks */
	पूर्णांक tlocksInUse;	/* Number of tlocks in use */
	spinlock_t LazyLock;	/* synchronize sync_queue & unlock_queue */
/*	काष्ठा tblock *sync_queue; * Transactions रुकोing क्रम data sync */
	काष्ठा list_head unlock_queue;	/* Txns रुकोing to be released */
	काष्ठा list_head anon_list;	/* inodes having anonymous txns */
	काष्ठा list_head anon_list2;	/* inodes having anonymous txns
					   that couldn't be sync'ed */
पूर्ण TxAnchor;

पूर्णांक jfs_tlocks_low;		/* Indicates low number of available tlocks */

#अगर_घोषित CONFIG_JFS_STATISTICS
अटल काष्ठा अणु
	uपूर्णांक txBegin;
	uपूर्णांक txBegin_barrier;
	uपूर्णांक txBegin_lockslow;
	uपूर्णांक txBegin_मुक्तtid;
	uपूर्णांक txBeginAnon;
	uपूर्णांक txBeginAnon_barrier;
	uपूर्णांक txBeginAnon_lockslow;
	uपूर्णांक txLockAlloc;
	uपूर्णांक txLockAlloc_मुक्तlock;
पूर्ण TxStat;
#पूर्ण_अगर

अटल पूर्णांक nTxBlock = -1;	/* number of transaction blocks */
module_param(nTxBlock, पूर्णांक, 0);
MODULE_PARM_DESC(nTxBlock,
		 "Number of transaction blocks (max:65536)");

अटल पूर्णांक nTxLock = -1;	/* number of transaction locks */
module_param(nTxLock, पूर्णांक, 0);
MODULE_PARM_DESC(nTxLock,
		 "Number of transaction locks (max:65536)");

काष्ठा tblock *TxBlock;	/* transaction block table */
अटल पूर्णांक TxLockLWM;	/* Low water mark क्रम number of txLocks used */
अटल पूर्णांक TxLockHWM;	/* High water mark क्रम number of txLocks used */
अटल पूर्णांक TxLockVHWM;	/* Very High water mark */
काष्ठा tlock *TxLock;	/* transaction lock table */

/*
 *	transaction management lock
 */
अटल DEFINE_SPINLOCK(jfsTxnLock);

#घोषणा TXN_LOCK()		spin_lock(&jfsTxnLock)
#घोषणा TXN_UNLOCK()		spin_unlock(&jfsTxnLock)

#घोषणा LAZY_LOCK_INIT()	spin_lock_init(&TxAnchor.LazyLock);
#घोषणा LAZY_LOCK(flags)	spin_lock_irqsave(&TxAnchor.LazyLock, flags)
#घोषणा LAZY_UNLOCK(flags) spin_unlock_irqrestore(&TxAnchor.LazyLock, flags)

अटल DECLARE_WAIT_QUEUE_HEAD(jfs_commit_thपढ़ो_रुको);
अटल पूर्णांक jfs_commit_thपढ़ो_waking;

/*
 * Retry logic exist outside these macros to protect from spurrious wakeups.
 */
अटल अंतरभूत व्योम TXN_SLEEP_DROP_LOCK(रुको_queue_head_t * event)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	add_रुको_queue(event, &रुको);
	set_current_state(TASK_UNINTERRUPTIBLE);
	TXN_UNLOCK();
	io_schedule();
	हटाओ_रुको_queue(event, &रुको);
पूर्ण

#घोषणा TXN_SLEEP(event)\
अणु\
	TXN_SLEEP_DROP_LOCK(event);\
	TXN_LOCK();\
पूर्ण

#घोषणा TXN_WAKEUP(event) wake_up_all(event)

/*
 *	statistics
 */
अटल काष्ठा अणु
	tid_t maxtid;		/* 4: biggest tid ever used */
	lid_t maxlid;		/* 4: biggest lid ever used */
	पूर्णांक ntid;		/* 4: # of transactions perक्रमmed */
	पूर्णांक nlid;		/* 4: # of tlocks acquired */
	पूर्णांक रुकोlock;		/* 4: # of tlock रुको */
पूर्ण stattx;

/*
 * क्रमward references
 */
अटल व्योम diLog(काष्ठा jfs_log *log, काष्ठा tblock *tblk, काष्ठा lrd *lrd,
		काष्ठा tlock *tlck, काष्ठा commit *cd);
अटल व्योम dataLog(काष्ठा jfs_log *log, काष्ठा tblock *tblk, काष्ठा lrd *lrd,
		काष्ठा tlock *tlck);
अटल व्योम dtLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
		काष्ठा tlock * tlck);
अटल व्योम mapLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
		काष्ठा tlock * tlck);
अटल व्योम txAllocPMap(काष्ठा inode *ip, काष्ठा maplock * maplock,
		काष्ठा tblock * tblk);
अटल व्योम txForce(काष्ठा tblock * tblk);
अटल व्योम txLog(काष्ठा jfs_log *log, काष्ठा tblock *tblk,
		काष्ठा commit *cd);
अटल व्योम txUpdateMap(काष्ठा tblock * tblk);
अटल व्योम txRelease(काष्ठा tblock * tblk);
अटल व्योम xtLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
	   काष्ठा tlock * tlck);
अटल व्योम LogSyncRelease(काष्ठा metapage * mp);

/*
 *		transaction block/lock management
 *		---------------------------------
 */

/*
 * Get a transaction lock from the मुक्त list.  If the number in use is
 * greater than the high water mark, wake up the sync daemon.  This should
 * मुक्त some anonymous transaction locks.  (TXN_LOCK must be held.)
 */
अटल lid_t txLockAlloc(व्योम)
अणु
	lid_t lid;

	INCREMENT(TxStat.txLockAlloc);
	अगर (!TxAnchor.मुक्तlock) अणु
		INCREMENT(TxStat.txLockAlloc_मुक्तlock);
	पूर्ण

	जबतक (!(lid = TxAnchor.मुक्तlock))
		TXN_SLEEP(&TxAnchor.मुक्तlockरुको);
	TxAnchor.मुक्तlock = TxLock[lid].next;
	HIGHWATERMARK(stattx.maxlid, lid);
	अगर ((++TxAnchor.tlocksInUse > TxLockHWM) && (jfs_tlocks_low == 0)) अणु
		jfs_info("txLockAlloc tlocks low");
		jfs_tlocks_low = 1;
		wake_up_process(jfsSyncThपढ़ो);
	पूर्ण

	वापस lid;
पूर्ण

अटल व्योम txLockFree(lid_t lid)
अणु
	TxLock[lid].tid = 0;
	TxLock[lid].next = TxAnchor.मुक्तlock;
	TxAnchor.मुक्तlock = lid;
	TxAnchor.tlocksInUse--;
	अगर (jfs_tlocks_low && (TxAnchor.tlocksInUse < TxLockLWM)) अणु
		jfs_info("txLockFree jfs_tlocks_low no more");
		jfs_tlocks_low = 0;
		TXN_WAKEUP(&TxAnchor.lowlockरुको);
	पूर्ण
	TXN_WAKEUP(&TxAnchor.मुक्तlockरुको);
पूर्ण

/*
 * NAME:	txInit()
 *
 * FUNCTION:	initialize transaction management काष्ठाures
 *
 * RETURN:
 *
 * serialization: single thपढ़ो at jfs_init()
 */
पूर्णांक txInit(व्योम)
अणु
	पूर्णांक k, size;
	काष्ठा sysinfo si;

	/* Set शेषs क्रम nTxLock and nTxBlock अगर unset */

	अगर (nTxLock == -1) अणु
		अगर (nTxBlock == -1) अणु
			/* Base शेष on memory size */
			si_meminfo(&si);
			अगर (si.totalram > (256 * 1024)) /* 1 GB */
				nTxLock = 64 * 1024;
			अन्यथा
				nTxLock = si.totalram >> 2;
		पूर्ण अन्यथा अगर (nTxBlock > (8 * 1024))
			nTxLock = 64 * 1024;
		अन्यथा
			nTxLock = nTxBlock << 3;
	पूर्ण
	अगर (nTxBlock == -1)
		nTxBlock = nTxLock >> 3;

	/* Verअगरy tunable parameters */
	अगर (nTxBlock < 16)
		nTxBlock = 16;	/* No one should set it this low */
	अगर (nTxBlock > 65536)
		nTxBlock = 65536;
	अगर (nTxLock < 256)
		nTxLock = 256;	/* No one should set it this low */
	अगर (nTxLock > 65536)
		nTxLock = 65536;

	prपूर्णांकk(KERN_INFO "JFS: nTxBlock = %d, nTxLock = %d\n",
	       nTxBlock, nTxLock);
	/*
	 * initialize transaction block (tblock) table
	 *
	 * transaction id (tid) = tblock index
	 * tid = 0 is reserved.
	 */
	TxLockLWM = (nTxLock * 4) / 10;
	TxLockHWM = (nTxLock * 7) / 10;
	TxLockVHWM = (nTxLock * 8) / 10;

	size = माप(काष्ठा tblock) * nTxBlock;
	TxBlock = vदो_स्मृति(size);
	अगर (TxBlock == शून्य)
		वापस -ENOMEM;

	क्रम (k = 1; k < nTxBlock - 1; k++) अणु
		TxBlock[k].next = k + 1;
		init_रुकोqueue_head(&TxBlock[k].gcरुको);
		init_रुकोqueue_head(&TxBlock[k].रुकोor);
	पूर्ण
	TxBlock[k].next = 0;
	init_रुकोqueue_head(&TxBlock[k].gcरुको);
	init_रुकोqueue_head(&TxBlock[k].रुकोor);

	TxAnchor.मुक्तtid = 1;
	init_रुकोqueue_head(&TxAnchor.मुक्तरुको);

	stattx.maxtid = 1;	/* statistics */

	/*
	 * initialize transaction lock (tlock) table
	 *
	 * transaction lock id = tlock index
	 * tlock id = 0 is reserved.
	 */
	size = माप(काष्ठा tlock) * nTxLock;
	TxLock = vदो_स्मृति(size);
	अगर (TxLock == शून्य) अणु
		vमुक्त(TxBlock);
		वापस -ENOMEM;
	पूर्ण

	/* initialize tlock table */
	क्रम (k = 1; k < nTxLock - 1; k++)
		TxLock[k].next = k + 1;
	TxLock[k].next = 0;
	init_रुकोqueue_head(&TxAnchor.मुक्तlockरुको);
	init_रुकोqueue_head(&TxAnchor.lowlockरुको);

	TxAnchor.मुक्तlock = 1;
	TxAnchor.tlocksInUse = 0;
	INIT_LIST_HEAD(&TxAnchor.anon_list);
	INIT_LIST_HEAD(&TxAnchor.anon_list2);

	LAZY_LOCK_INIT();
	INIT_LIST_HEAD(&TxAnchor.unlock_queue);

	stattx.maxlid = 1;	/* statistics */

	वापस 0;
पूर्ण

/*
 * NAME:	txExit()
 *
 * FUNCTION:	clean up when module is unloaded
 */
व्योम txExit(व्योम)
अणु
	vमुक्त(TxLock);
	TxLock = शून्य;
	vमुक्त(TxBlock);
	TxBlock = शून्य;
पूर्ण

/*
 * NAME:	txBegin()
 *
 * FUNCTION:	start a transaction.
 *
 * PARAMETER:	sb	- superblock
 *		flag	- क्रमce क्रम nested tx;
 *
 * RETURN:	tid	- transaction id
 *
 * note: flag क्रमce allows to start tx क्रम nested tx
 * to prevent deadlock on logsync barrier;
 */
tid_t txBegin(काष्ठा super_block *sb, पूर्णांक flag)
अणु
	tid_t t;
	काष्ठा tblock *tblk;
	काष्ठा jfs_log *log;

	jfs_info("txBegin: flag = 0x%x", flag);
	log = JFS_SBI(sb)->log;

	TXN_LOCK();

	INCREMENT(TxStat.txBegin);

      retry:
	अगर (!(flag & COMMIT_FORCE)) अणु
		/*
		 * synchronize with logsync barrier
		 */
		अगर (test_bit(log_SYNCBARRIER, &log->flag) ||
		    test_bit(log_QUIESCE, &log->flag)) अणु
			INCREMENT(TxStat.txBegin_barrier);
			TXN_SLEEP(&log->syncरुको);
			जाओ retry;
		पूर्ण
	पूर्ण
	अगर (flag == 0) अणु
		/*
		 * Don't begin transaction if we're getting starved क्रम tlocks
		 * unless COMMIT_FORCE or COMMIT_INODE (which may ultimately
		 * मुक्त tlocks)
		 */
		अगर (TxAnchor.tlocksInUse > TxLockVHWM) अणु
			INCREMENT(TxStat.txBegin_lockslow);
			TXN_SLEEP(&TxAnchor.lowlockरुको);
			जाओ retry;
		पूर्ण
	पूर्ण

	/*
	 * allocate transaction id/block
	 */
	अगर ((t = TxAnchor.मुक्तtid) == 0) अणु
		jfs_info("txBegin: waiting for free tid");
		INCREMENT(TxStat.txBegin_मुक्तtid);
		TXN_SLEEP(&TxAnchor.मुक्तरुको);
		जाओ retry;
	पूर्ण

	tblk = tid_to_tblock(t);

	अगर ((tblk->next == 0) && !(flag & COMMIT_FORCE)) अणु
		/* Don't let a non-क्रमced transaction take the last tblk */
		jfs_info("txBegin: waiting for free tid");
		INCREMENT(TxStat.txBegin_मुक्तtid);
		TXN_SLEEP(&TxAnchor.मुक्तरुको);
		जाओ retry;
	पूर्ण

	TxAnchor.मुक्तtid = tblk->next;

	/*
	 * initialize transaction
	 */

	/*
	 * We can't zero the whole thing or we screw up another thपढ़ो being
	 * awakened after sleeping on tblk->रुकोor
	 *
	 * स_रखो(tblk, 0, माप(काष्ठा tblock));
	 */
	tblk->next = tblk->last = tblk->xflag = tblk->flag = tblk->lsn = 0;

	tblk->sb = sb;
	++log->logtid;
	tblk->logtid = log->logtid;

	++log->active;

	HIGHWATERMARK(stattx.maxtid, t);	/* statistics */
	INCREMENT(stattx.ntid);	/* statistics */

	TXN_UNLOCK();

	jfs_info("txBegin: returning tid = %d", t);

	वापस t;
पूर्ण

/*
 * NAME:	txBeginAnon()
 *
 * FUNCTION:	start an anonymous transaction.
 *		Blocks अगर logsync or available tlocks are low to prevent
 *		anonymous tlocks from depleting supply.
 *
 * PARAMETER:	sb	- superblock
 *
 * RETURN:	none
 */
व्योम txBeginAnon(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_log *log;

	log = JFS_SBI(sb)->log;

	TXN_LOCK();
	INCREMENT(TxStat.txBeginAnon);

      retry:
	/*
	 * synchronize with logsync barrier
	 */
	अगर (test_bit(log_SYNCBARRIER, &log->flag) ||
	    test_bit(log_QUIESCE, &log->flag)) अणु
		INCREMENT(TxStat.txBeginAnon_barrier);
		TXN_SLEEP(&log->syncरुको);
		जाओ retry;
	पूर्ण

	/*
	 * Don't begin transaction if we're getting starved क्रम tlocks
	 */
	अगर (TxAnchor.tlocksInUse > TxLockVHWM) अणु
		INCREMENT(TxStat.txBeginAnon_lockslow);
		TXN_SLEEP(&TxAnchor.lowlockरुको);
		जाओ retry;
	पूर्ण
	TXN_UNLOCK();
पूर्ण

/*
 *	txEnd()
 *
 * function: मुक्त specअगरied transaction block.
 *
 *	logsync barrier processing:
 *
 * serialization:
 */
व्योम txEnd(tid_t tid)
अणु
	काष्ठा tblock *tblk = tid_to_tblock(tid);
	काष्ठा jfs_log *log;

	jfs_info("txEnd: tid = %d", tid);
	TXN_LOCK();

	/*
	 * wakeup transactions रुकोing on the page locked
	 * by the current transaction
	 */
	TXN_WAKEUP(&tblk->रुकोor);

	log = JFS_SBI(tblk->sb)->log;

	/*
	 * Lazy commit thपढ़ो can't मुक्त this guy until we mark it UNLOCKED,
	 * otherwise, we would be left with a transaction that may have been
	 * reused.
	 *
	 * Lazy commit thपढ़ो will turn off tblkGC_LAZY beक्रमe calling this
	 * routine.
	 */
	अगर (tblk->flag & tblkGC_LAZY) अणु
		jfs_info("txEnd called w/lazy tid: %d, tblk = 0x%p", tid, tblk);
		TXN_UNLOCK();

		spin_lock_irq(&log->gघड़ी);	// LOGGC_LOCK
		tblk->flag |= tblkGC_UNLOCKED;
		spin_unlock_irq(&log->gघड़ी);	// LOGGC_UNLOCK
		वापस;
	पूर्ण

	jfs_info("txEnd: tid: %d, tblk = 0x%p", tid, tblk);

	निश्चित(tblk->next == 0);

	/*
	 * insert tblock back on मुक्तlist
	 */
	tblk->next = TxAnchor.मुक्तtid;
	TxAnchor.मुक्तtid = tid;

	/*
	 * mark the tblock not active
	 */
	अगर (--log->active == 0) अणु
		clear_bit(log_FLUSH, &log->flag);

		/*
		 * synchronize with logsync barrier
		 */
		अगर (test_bit(log_SYNCBARRIER, &log->flag)) अणु
			TXN_UNLOCK();

			/* ग_लिखो dirty metadata & क्रमward log syncpt */
			jfs_syncpt(log, 1);

			jfs_info("log barrier off: 0x%x", log->lsn);

			/* enable new transactions start */
			clear_bit(log_SYNCBARRIER, &log->flag);

			/* wakeup all रुकोors क्रम logsync barrier */
			TXN_WAKEUP(&log->syncरुको);

			जाओ wakeup;
		पूर्ण
	पूर्ण

	TXN_UNLOCK();
wakeup:
	/*
	 * wakeup all रुकोors क्रम a मुक्त tblock
	 */
	TXN_WAKEUP(&TxAnchor.मुक्तरुको);
पूर्ण

/*
 *	txLock()
 *
 * function: acquire a transaction lock on the specअगरied <mp>
 *
 * parameter:
 *
 * वापस:	transaction lock id
 *
 * serialization:
 */
काष्ठा tlock *txLock(tid_t tid, काष्ठा inode *ip, काष्ठा metapage * mp,
		     पूर्णांक type)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	पूर्णांक dir_xtree = 0;
	lid_t lid;
	tid_t xtid;
	काष्ठा tlock *tlck;
	काष्ठा xtlock *xtlck;
	काष्ठा linelock *linelock;
	xtpage_t *p;
	काष्ठा tblock *tblk;

	TXN_LOCK();

	अगर (S_ISसूची(ip->i_mode) && (type & tlckXTREE) &&
	    !(mp->xflag & COMMIT_PAGE)) अणु
		/*
		 * Directory inode is special.  It can have both an xtree tlock
		 * and a dtree tlock associated with it.
		 */
		dir_xtree = 1;
		lid = jfs_ip->xtlid;
	पूर्ण अन्यथा
		lid = mp->lid;

	/* is page not locked by a transaction ? */
	अगर (lid == 0)
		जाओ allocateLock;

	jfs_info("txLock: tid:%d ip:0x%p mp:0x%p lid:%d", tid, ip, mp, lid);

	/* is page locked by the requester transaction ? */
	tlck = lid_to_tlock(lid);
	अगर ((xtid = tlck->tid) == tid) अणु
		TXN_UNLOCK();
		जाओ grantLock;
	पूर्ण

	/*
	 * is page locked by anonymous transaction/lock ?
	 *
	 * (page update without transaction (i.e., file ग_लिखो) is
	 * locked under anonymous transaction tid = 0:
	 * anonymous tlocks मुख्यtained on anonymous tlock list of
	 * the inode of the page and available to all anonymous
	 * transactions until txCommit() समय at which poपूर्णांक
	 * they are transferred to the transaction tlock list of
	 * the committing transaction of the inode)
	 */
	अगर (xtid == 0) अणु
		tlck->tid = tid;
		TXN_UNLOCK();
		tblk = tid_to_tblock(tid);
		/*
		 * The order of the tlocks in the transaction is important
		 * (during truncate, child xtree pages must be मुक्तd beक्रमe
		 * parent's tlocks change the working map).
		 * Take tlock off anonymous list and add to tail of
		 * transaction list
		 *
		 * Note:  We really need to get rid of the tid & lid and
		 * use list_head's.  This code is getting UGLY!
		 */
		अगर (jfs_ip->atlhead == lid) अणु
			अगर (jfs_ip->atltail == lid) अणु
				/* only anonymous txn.
				 * Remove from anon_list
				 */
				TXN_LOCK();
				list_del_init(&jfs_ip->anon_inode_list);
				TXN_UNLOCK();
			पूर्ण
			jfs_ip->atlhead = tlck->next;
		पूर्ण अन्यथा अणु
			lid_t last;
			क्रम (last = jfs_ip->atlhead;
			     lid_to_tlock(last)->next != lid;
			     last = lid_to_tlock(last)->next) अणु
				निश्चित(last);
			पूर्ण
			lid_to_tlock(last)->next = tlck->next;
			अगर (jfs_ip->atltail == lid)
				jfs_ip->atltail = last;
		पूर्ण

		/* insert the tlock at tail of transaction tlock list */

		अगर (tblk->next)
			lid_to_tlock(tblk->last)->next = lid;
		अन्यथा
			tblk->next = lid;
		tlck->next = 0;
		tblk->last = lid;

		जाओ grantLock;
	पूर्ण

	जाओ रुकोLock;

	/*
	 * allocate a tlock
	 */
      allocateLock:
	lid = txLockAlloc();
	tlck = lid_to_tlock(lid);

	/*
	 * initialize tlock
	 */
	tlck->tid = tid;

	TXN_UNLOCK();

	/* mark tlock क्रम meta-data page */
	अगर (mp->xflag & COMMIT_PAGE) अणु

		tlck->flag = tlckPAGELOCK;

		/* mark the page dirty and nohomeok */
		metapage_nohomeok(mp);

		jfs_info("locking mp = 0x%p, nohomeok = %d tid = %d tlck = 0x%p",
			 mp, mp->nohomeok, tid, tlck);

		/* अगर anonymous transaction, and buffer is on the group
		 * commit synclist, mark inode to show this.  This will
		 * prevent the buffer from being marked nohomeok क्रम too
		 * दीर्घ a समय.
		 */
		अगर ((tid == 0) && mp->lsn)
			set_cflag(COMMIT_Synclist, ip);
	पूर्ण
	/* mark tlock क्रम in-memory inode */
	अन्यथा
		tlck->flag = tlckINODELOCK;

	अगर (S_ISसूची(ip->i_mode))
		tlck->flag |= tlckसूचीECTORY;

	tlck->type = 0;

	/* bind the tlock and the page */
	tlck->ip = ip;
	tlck->mp = mp;
	अगर (dir_xtree)
		jfs_ip->xtlid = lid;
	अन्यथा
		mp->lid = lid;

	/*
	 * enqueue transaction lock to transaction/inode
	 */
	/* insert the tlock at tail of transaction tlock list */
	अगर (tid) अणु
		tblk = tid_to_tblock(tid);
		अगर (tblk->next)
			lid_to_tlock(tblk->last)->next = lid;
		अन्यथा
			tblk->next = lid;
		tlck->next = 0;
		tblk->last = lid;
	पूर्ण
	/* anonymous transaction:
	 * insert the tlock at head of inode anonymous tlock list
	 */
	अन्यथा अणु
		tlck->next = jfs_ip->atlhead;
		jfs_ip->atlhead = lid;
		अगर (tlck->next == 0) अणु
			/* This inode's first anonymous transaction */
			jfs_ip->atltail = lid;
			TXN_LOCK();
			list_add_tail(&jfs_ip->anon_inode_list,
				      &TxAnchor.anon_list);
			TXN_UNLOCK();
		पूर्ण
	पूर्ण

	/* initialize type dependent area क्रम linelock */
	linelock = (काष्ठा linelock *) & tlck->lock;
	linelock->next = 0;
	linelock->flag = tlckLINELOCK;
	linelock->maxcnt = TLOCKSHORT;
	linelock->index = 0;

	चयन (type & tlckTYPE) अणु
	हाल tlckDTREE:
		linelock->l2linesize = L2DTSLOTSIZE;
		अवरोध;

	हाल tlckXTREE:
		linelock->l2linesize = L2XTSLOTSIZE;

		xtlck = (काष्ठा xtlock *) linelock;
		xtlck->header.offset = 0;
		xtlck->header.length = 2;

		अगर (type & tlckNEW) अणु
			xtlck->lwm.offset = XTENTRYSTART;
		पूर्ण अन्यथा अणु
			अगर (mp->xflag & COMMIT_PAGE)
				p = (xtpage_t *) mp->data;
			अन्यथा
				p = &jfs_ip->i_xtroot;
			xtlck->lwm.offset =
			    le16_to_cpu(p->header.nextindex);
		पूर्ण
		xtlck->lwm.length = 0;	/* ! */
		xtlck->twm.offset = 0;
		xtlck->hwm.offset = 0;

		xtlck->index = 2;
		अवरोध;

	हाल tlckINODE:
		linelock->l2linesize = L2INODESLOTSIZE;
		अवरोध;

	हाल tlckDATA:
		linelock->l2linesize = L2DATASLOTSIZE;
		अवरोध;

	शेष:
		jfs_err("UFO tlock:0x%p", tlck);
	पूर्ण

	/*
	 * update tlock vector
	 */
      grantLock:
	tlck->type |= type;

	वापस tlck;

	/*
	 * page is being locked by another transaction:
	 */
      रुकोLock:
	/* Only locks on ipimap or ipaimap should reach here */
	/* निश्चित(jfs_ip->fileset == AGGREGATE_I); */
	अगर (jfs_ip->fileset != AGGREGATE_I) अणु
		prपूर्णांकk(KERN_ERR "txLock: trying to lock locked page!");
		prपूर्णांक_hex_dump(KERN_ERR, "ip: ", DUMP_PREFIX_ADDRESS, 16, 4,
			       ip, माप(*ip), 0);
		prपूर्णांक_hex_dump(KERN_ERR, "mp: ", DUMP_PREFIX_ADDRESS, 16, 4,
			       mp, माप(*mp), 0);
		prपूर्णांक_hex_dump(KERN_ERR, "Locker's tblock: ",
			       DUMP_PREFIX_ADDRESS, 16, 4, tid_to_tblock(tid),
			       माप(काष्ठा tblock), 0);
		prपूर्णांक_hex_dump(KERN_ERR, "Tlock: ", DUMP_PREFIX_ADDRESS, 16, 4,
			       tlck, माप(*tlck), 0);
		BUG();
	पूर्ण
	INCREMENT(stattx.रुकोlock);	/* statistics */
	TXN_UNLOCK();
	release_metapage(mp);
	TXN_LOCK();
	xtid = tlck->tid;	/* reacquire after dropping TXN_LOCK */

	jfs_info("txLock: in waitLock, tid = %d, xtid = %d, lid = %d",
		 tid, xtid, lid);

	/* Recheck everything since dropping TXN_LOCK */
	अगर (xtid && (tlck->mp == mp) && (mp->lid == lid))
		TXN_SLEEP_DROP_LOCK(&tid_to_tblock(xtid)->रुकोor);
	अन्यथा
		TXN_UNLOCK();
	jfs_info("txLock: awakened     tid = %d, lid = %d", tid, lid);

	वापस शून्य;
पूर्ण

/*
 * NAME:	txRelease()
 *
 * FUNCTION:	Release buffers associated with transaction locks, but करोn't
 *		mark homeok yet.  The allows other transactions to modअगरy
 *		buffers, but won't let them go to disk until commit record
 *		actually माला_लो written.
 *
 * PARAMETER:
 *		tblk	-
 *
 * RETURN:	Errors from subroutines.
 */
अटल व्योम txRelease(काष्ठा tblock * tblk)
अणु
	काष्ठा metapage *mp;
	lid_t lid;
	काष्ठा tlock *tlck;

	TXN_LOCK();

	क्रम (lid = tblk->next; lid; lid = tlck->next) अणु
		tlck = lid_to_tlock(lid);
		अगर ((mp = tlck->mp) != शून्य &&
		    (tlck->type & tlckBTROOT) == 0) अणु
			निश्चित(mp->xflag & COMMIT_PAGE);
			mp->lid = 0;
		पूर्ण
	पूर्ण

	/*
	 * wakeup transactions रुकोing on a page locked
	 * by the current transaction
	 */
	TXN_WAKEUP(&tblk->रुकोor);

	TXN_UNLOCK();
पूर्ण

/*
 * NAME:	txUnlock()
 *
 * FUNCTION:	Initiates pageout of pages modअगरied by tid in journalled
 *		objects and मुक्तs their lockwords.
 */
अटल व्योम txUnlock(काष्ठा tblock * tblk)
अणु
	काष्ठा tlock *tlck;
	काष्ठा linelock *linelock;
	lid_t lid, next, llid, k;
	काष्ठा metapage *mp;
	काष्ठा jfs_log *log;
	पूर्णांक dअगरft, dअगरfp;
	अचिन्हित दीर्घ flags;

	jfs_info("txUnlock: tblk = 0x%p", tblk);
	log = JFS_SBI(tblk->sb)->log;

	/*
	 * mark page under tlock homeok (its log has been written):
	 */
	क्रम (lid = tblk->next; lid; lid = next) अणु
		tlck = lid_to_tlock(lid);
		next = tlck->next;

		jfs_info("unlocking lid = %d, tlck = 0x%p", lid, tlck);

		/* unbind page from tlock */
		अगर ((mp = tlck->mp) != शून्य &&
		    (tlck->type & tlckBTROOT) == 0) अणु
			निश्चित(mp->xflag & COMMIT_PAGE);

			/* hold buffer
			 */
			hold_metapage(mp);

			निश्चित(mp->nohomeok > 0);
			_metapage_homeok(mp);

			/* inherit younger/larger clsn */
			LOGSYNC_LOCK(log, flags);
			अगर (mp->clsn) अणु
				logdअगरf(dअगरft, tblk->clsn, log);
				logdअगरf(dअगरfp, mp->clsn, log);
				अगर (dअगरft > dअगरfp)
					mp->clsn = tblk->clsn;
			पूर्ण अन्यथा
				mp->clsn = tblk->clsn;
			LOGSYNC_UNLOCK(log, flags);

			निश्चित(!(tlck->flag & tlckFREEPAGE));

			put_metapage(mp);
		पूर्ण

		/* insert tlock, and linelock(s) of the tlock अगर any,
		 * at head of मुक्तlist
		 */
		TXN_LOCK();

		llid = ((काष्ठा linelock *) & tlck->lock)->next;
		जबतक (llid) अणु
			linelock = (काष्ठा linelock *) lid_to_tlock(llid);
			k = linelock->next;
			txLockFree(llid);
			llid = k;
		पूर्ण
		txLockFree(lid);

		TXN_UNLOCK();
	पूर्ण
	tblk->next = tblk->last = 0;

	/*
	 * हटाओ tblock from logsynclist
	 * (allocation map pages inherited lsn of tblk and
	 * has been inserted in logsync list at txUpdateMap())
	 */
	अगर (tblk->lsn) अणु
		LOGSYNC_LOCK(log, flags);
		log->count--;
		list_del(&tblk->synclist);
		LOGSYNC_UNLOCK(log, flags);
	पूर्ण
पूर्ण

/*
 *	txMaplock()
 *
 * function: allocate a transaction lock क्रम मुक्तd page/entry;
 *	क्रम मुक्तd page, maplock is used as xtlock/dtlock type;
 */
काष्ठा tlock *txMaplock(tid_t tid, काष्ठा inode *ip, पूर्णांक type)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	lid_t lid;
	काष्ठा tblock *tblk;
	काष्ठा tlock *tlck;
	काष्ठा maplock *maplock;

	TXN_LOCK();

	/*
	 * allocate a tlock
	 */
	lid = txLockAlloc();
	tlck = lid_to_tlock(lid);

	/*
	 * initialize tlock
	 */
	tlck->tid = tid;

	/* bind the tlock and the object */
	tlck->flag = tlckINODELOCK;
	अगर (S_ISसूची(ip->i_mode))
		tlck->flag |= tlckसूचीECTORY;
	tlck->ip = ip;
	tlck->mp = शून्य;

	tlck->type = type;

	/*
	 * enqueue transaction lock to transaction/inode
	 */
	/* insert the tlock at tail of transaction tlock list */
	अगर (tid) अणु
		tblk = tid_to_tblock(tid);
		अगर (tblk->next)
			lid_to_tlock(tblk->last)->next = lid;
		अन्यथा
			tblk->next = lid;
		tlck->next = 0;
		tblk->last = lid;
	पूर्ण
	/* anonymous transaction:
	 * insert the tlock at head of inode anonymous tlock list
	 */
	अन्यथा अणु
		tlck->next = jfs_ip->atlhead;
		jfs_ip->atlhead = lid;
		अगर (tlck->next == 0) अणु
			/* This inode's first anonymous transaction */
			jfs_ip->atltail = lid;
			list_add_tail(&jfs_ip->anon_inode_list,
				      &TxAnchor.anon_list);
		पूर्ण
	पूर्ण

	TXN_UNLOCK();

	/* initialize type dependent area क्रम maplock */
	maplock = (काष्ठा maplock *) & tlck->lock;
	maplock->next = 0;
	maplock->maxcnt = 0;
	maplock->index = 0;

	वापस tlck;
पूर्ण

/*
 *	txLinelock()
 *
 * function: allocate a transaction lock क्रम log vector list
 */
काष्ठा linelock *txLinelock(काष्ठा linelock * tlock)
अणु
	lid_t lid;
	काष्ठा tlock *tlck;
	काष्ठा linelock *linelock;

	TXN_LOCK();

	/* allocate a TxLock काष्ठाure */
	lid = txLockAlloc();
	tlck = lid_to_tlock(lid);

	TXN_UNLOCK();

	/* initialize linelock */
	linelock = (काष्ठा linelock *) tlck;
	linelock->next = 0;
	linelock->flag = tlckLINELOCK;
	linelock->maxcnt = TLOCKLONG;
	linelock->index = 0;
	अगर (tlck->flag & tlckसूचीECTORY)
		linelock->flag |= tlckसूचीECTORY;

	/* append linelock after tlock */
	linelock->next = tlock->next;
	tlock->next = lid;

	वापस linelock;
पूर्ण

/*
 *		transaction commit management
 *		-----------------------------
 */

/*
 * NAME:	txCommit()
 *
 * FUNCTION:	commit the changes to the objects specअगरied in
 *		clist.  For journalled segments only the
 *		changes of the caller are committed, ie by tid.
 *		क्रम non-journalled segments the data are flushed to
 *		disk and then the change to the disk inode and indirect
 *		blocks committed (so blocks newly allocated to the
 *		segment will be made a part of the segment atomically).
 *
 *		all of the segments specअगरied in clist must be in
 *		one file प्रणाली. no more than 6 segments are needed
 *		to handle all unix svcs.
 *
 *		अगर the i_nlink field (i.e. disk inode link count)
 *		is zero, and the type of inode is a regular file or
 *		directory, or symbolic link , the inode is truncated
 *		to zero length. the truncation is committed but the
 *		VM resources are unaffected until it is बंदd (see
 *		iput and iबंद).
 *
 * PARAMETER:
 *
 * RETURN:
 *
 * serialization:
 *		on entry the inode lock on each segment is assumed
 *		to be held.
 *
 * i/o error:
 */
पूर्णांक txCommit(tid_t tid,		/* transaction identअगरier */
	     पूर्णांक nip,		/* number of inodes to commit */
	     काष्ठा inode **iplist,	/* list of inode to commit */
	     पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	काष्ठा commit cd;
	काष्ठा jfs_log *log;
	काष्ठा tblock *tblk;
	काष्ठा lrd *lrd;
	काष्ठा inode *ip;
	काष्ठा jfs_inode_info *jfs_ip;
	पूर्णांक k, n;
	ino_t top;
	काष्ठा super_block *sb;

	jfs_info("txCommit, tid = %d, flag = %d", tid, flag);
	/* is पढ़ो-only file प्रणाली ? */
	अगर (isReadOnly(iplist[0])) अणु
		rc = -EROFS;
		जाओ TheEnd;
	पूर्ण

	sb = cd.sb = iplist[0]->i_sb;
	cd.tid = tid;

	अगर (tid == 0)
		tid = txBegin(sb, 0);
	tblk = tid_to_tblock(tid);

	/*
	 * initialize commit काष्ठाure
	 */
	log = JFS_SBI(sb)->log;
	cd.log = log;

	/* initialize log record descriptor in commit */
	lrd = &cd.lrd;
	lrd->logtid = cpu_to_le32(tblk->logtid);
	lrd->backchain = 0;

	tblk->xflag |= flag;

	अगर ((flag & (COMMIT_FORCE | COMMIT_SYNC)) == 0)
		tblk->xflag |= COMMIT_LAZY;
	/*
	 *	prepare non-journaled objects क्रम commit
	 *
	 * flush data pages of non-journaled file
	 * to prevent the file getting non-initialized disk blocks
	 * in हाल of crash.
	 * (new blocks - )
	 */
	cd.iplist = iplist;
	cd.nip = nip;

	/*
	 *	acquire transaction lock on (on-disk) inodes
	 *
	 * update on-disk inode from in-memory inode
	 * acquiring transaction locks क्रम AFTER records
	 * on the on-disk inode of file object
	 *
	 * sort the inodes array by inode number in descending order
	 * to prevent deadlock when acquiring transaction lock
	 * of on-disk inodes on multiple on-disk inode pages by
	 * multiple concurrent transactions
	 */
	क्रम (k = 0; k < cd.nip; k++) अणु
		top = (cd.iplist[k])->i_ino;
		क्रम (n = k + 1; n < cd.nip; n++) अणु
			ip = cd.iplist[n];
			अगर (ip->i_ino > top) अणु
				top = ip->i_ino;
				cd.iplist[n] = cd.iplist[k];
				cd.iplist[k] = ip;
			पूर्ण
		पूर्ण

		ip = cd.iplist[k];
		jfs_ip = JFS_IP(ip);

		/*
		 * BUGBUG - This code has temporarily been हटाओd.  The
		 * पूर्णांकent is to ensure that any file data is written beक्रमe
		 * the metadata is committed to the journal.  This prevents
		 * uninitialized data from appearing in a file after the
		 * journal has been replayed.  (The uninitialized data
		 * could be sensitive data हटाओd by another user.)
		 *
		 * The problem now is that we are holding the IWRITELOCK
		 * on the inode, and calling filemap_fdataग_लिखो on an
		 * unmapped page will cause a deadlock in jfs_get_block.
		 *
		 * The दीर्घ term solution is to pare करोwn the use of
		 * IWRITELOCK.  We are currently holding it too दीर्घ.
		 * We could also be smarter about which data pages need
		 * to be written beक्रमe the transaction is committed and
		 * when we करोn't need to worry about it at all.
		 *
		 * अगर ((!S_ISसूची(ip->i_mode))
		 *    && (tblk->flag & COMMIT_DELETE) == 0)
		 *	filemap_ग_लिखो_and_रुको(ip->i_mapping);
		 */

		/*
		 * Mark inode as not dirty.  It will still be on the dirty
		 * inode list, but we'll know not to commit it again unless
		 * it माला_लो marked dirty again
		 */
		clear_cflag(COMMIT_Dirty, ip);

		/* inherit anonymous tlock(s) of inode */
		अगर (jfs_ip->atlhead) अणु
			lid_to_tlock(jfs_ip->atltail)->next = tblk->next;
			tblk->next = jfs_ip->atlhead;
			अगर (!tblk->last)
				tblk->last = jfs_ip->atltail;
			jfs_ip->atlhead = jfs_ip->atltail = 0;
			TXN_LOCK();
			list_del_init(&jfs_ip->anon_inode_list);
			TXN_UNLOCK();
		पूर्ण

		/*
		 * acquire transaction lock on on-disk inode page
		 * (become first tlock of the tblk's tlock list)
		 */
		अगर (((rc = diWrite(tid, ip))))
			जाओ out;
	पूर्ण

	/*
	 *	ग_लिखो log records from transaction locks
	 *
	 * txUpdateMap() resets XAD_NEW in XAD.
	 */
	txLog(log, tblk, &cd);

	/*
	 * Ensure that inode isn't reused beक्रमe
	 * lazy commit thपढ़ो finishes processing
	 */
	अगर (tblk->xflag & COMMIT_DELETE) अणु
		ihold(tblk->u.ip);
		/*
		 * Aव्योम a rare deadlock
		 *
		 * If the inode is locked, we may be blocked in
		 * jfs_commit_inode.  If so, we करोn't want the
		 * lazy_commit thपढ़ो करोing the last iput() on the inode
		 * since that may block on the locked inode.  Instead,
		 * commit the transaction synchronously, so the last iput
		 * will be करोne by the calling thपढ़ो (or later)
		 */
		/*
		 * I believe this code is no दीर्घer needed.  Splitting I_LOCK
		 * पूर्णांकo two bits, I_NEW and I_SYNC should prevent this
		 * deadlock as well.  But since I करोn't have a JFS testload
		 * to verअगरy this, only a trivial s/I_LOCK/I_SYNC/ was करोne.
		 * Joern
		 */
		अगर (tblk->u.ip->i_state & I_SYNC)
			tblk->xflag &= ~COMMIT_LAZY;
	पूर्ण

	ASSERT((!(tblk->xflag & COMMIT_DELETE)) ||
	       ((tblk->u.ip->i_nlink == 0) &&
		!test_cflag(COMMIT_Nolink, tblk->u.ip)));

	/*
	 *	ग_लिखो COMMIT log record
	 */
	lrd->type = cpu_to_le16(LOG_COMMIT);
	lrd->length = 0;
	lmLog(log, tblk, lrd, शून्य);

	lmGroupCommit(log, tblk);

	/*
	 *	- transaction is now committed -
	 */

	/*
	 * क्रमce pages in careful update
	 * (imap addressing काष्ठाure update)
	 */
	अगर (flag & COMMIT_FORCE)
		txForce(tblk);

	/*
	 *	update allocation map.
	 *
	 * update inode allocation map and inode:
	 * मुक्त pager lock on memory object of inode अगर any.
	 * update block allocation map.
	 *
	 * txUpdateMap() resets XAD_NEW in XAD.
	 */
	अगर (tblk->xflag & COMMIT_FORCE)
		txUpdateMap(tblk);

	/*
	 *	मुक्त transaction locks and pageout/मुक्त pages
	 */
	txRelease(tblk);

	अगर ((tblk->flag & tblkGC_LAZY) == 0)
		txUnlock(tblk);


	/*
	 *	reset in-memory object state
	 */
	क्रम (k = 0; k < cd.nip; k++) अणु
		ip = cd.iplist[k];
		jfs_ip = JFS_IP(ip);

		/*
		 * reset in-memory inode state
		 */
		jfs_ip->bxflag = 0;
		jfs_ip->blid = 0;
	पूर्ण

      out:
	अगर (rc != 0)
		txAbort(tid, 1);

      TheEnd:
	jfs_info("txCommit: tid = %d, returning %d", tid, rc);
	वापस rc;
पूर्ण

/*
 * NAME:	txLog()
 *
 * FUNCTION:	Writes AFTER log records क्रम all lines modअगरied
 *		by tid क्रम segments specअगरied by inodes in comdata.
 *		Code assumes only WRITELOCKS are recorded in lockwords.
 *
 * PARAMETERS:
 *
 * RETURN :
 */
अटल व्योम txLog(काष्ठा jfs_log *log, काष्ठा tblock *tblk, काष्ठा commit *cd)
अणु
	काष्ठा inode *ip;
	lid_t lid;
	काष्ठा tlock *tlck;
	काष्ठा lrd *lrd = &cd->lrd;

	/*
	 * ग_लिखो log record(s) क्रम each tlock of transaction,
	 */
	क्रम (lid = tblk->next; lid; lid = tlck->next) अणु
		tlck = lid_to_tlock(lid);

		tlck->flag |= tlckLOG;

		/* initialize lrd common */
		ip = tlck->ip;
		lrd->aggregate = cpu_to_le32(JFS_SBI(ip->i_sb)->aggregate);
		lrd->log.reकरोpage.fileset = cpu_to_le32(JFS_IP(ip)->fileset);
		lrd->log.reकरोpage.inode = cpu_to_le32(ip->i_ino);

		/* ग_लिखो log record of page from the tlock */
		चयन (tlck->type & tlckTYPE) अणु
		हाल tlckXTREE:
			xtLog(log, tblk, lrd, tlck);
			अवरोध;

		हाल tlckDTREE:
			dtLog(log, tblk, lrd, tlck);
			अवरोध;

		हाल tlckINODE:
			diLog(log, tblk, lrd, tlck, cd);
			अवरोध;

		हाल tlckMAP:
			mapLog(log, tblk, lrd, tlck);
			अवरोध;

		हाल tlckDATA:
			dataLog(log, tblk, lrd, tlck);
			अवरोध;

		शेष:
			jfs_err("UFO tlock:0x%p", tlck);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/*
 *	diLog()
 *
 * function:	log inode tlock and क्रमmat maplock to update bmap;
 */
अटल व्योम diLog(काष्ठा jfs_log *log, काष्ठा tblock *tblk, काष्ठा lrd *lrd,
		 काष्ठा tlock *tlck, काष्ठा commit *cd)
अणु
	काष्ठा metapage *mp;
	pxd_t *pxd;
	काष्ठा pxd_lock *pxdlock;

	mp = tlck->mp;

	/* initialize as REDOPAGE record क्रमmat */
	lrd->log.reकरोpage.type = cpu_to_le16(LOG_INODE);
	lrd->log.reकरोpage.l2linesize = cpu_to_le16(L2INODESLOTSIZE);

	pxd = &lrd->log.reकरोpage.pxd;

	/*
	 *	inode after image
	 */
	अगर (tlck->type & tlckENTRY) अणु
		/* log after-image क्रम logreकरो(): */
		lrd->type = cpu_to_le16(LOG_REDOPAGE);
		PXDaddress(pxd, mp->index);
		PXDlength(pxd,
			  mp->logical_size >> tblk->sb->s_blocksize_bits);
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
	पूर्ण अन्यथा अगर (tlck->type & tlckFREE) अणु
		/*
		 *	मुक्त inode extent
		 *
		 * (pages of the मुक्तd inode extent have been invalidated and
		 * a maplock क्रम मुक्त of the extent has been क्रमmatted at
		 * txLock() समय);
		 *
		 * the tlock had been acquired on the inode allocation map page
		 * (iag) that specअगरies the मुक्तd extent, even though the map
		 * page is not itself logged, to prevent pageout of the map
		 * page beक्रमe the log;
		 */

		/* log LOG_NOREDOINOEXT of the मुक्तd inode extent क्रम
		 * logreकरो() to start NoReकरोPage filters, and to update
		 * imap and bmap क्रम मुक्त of the extent;
		 */
		lrd->type = cpu_to_le16(LOG_NOREDOINOEXT);
		/*
		 * For the LOG_NOREDOINOEXT record, we need
		 * to pass the IAG number and inode extent
		 * index (within that IAG) from which the
		 * extent is being released.  These have been
		 * passed to us in the iplist[1] and iplist[2].
		 */
		lrd->log.noreकरोinoext.iagnum =
		    cpu_to_le32((u32) (माप_प्रकार) cd->iplist[1]);
		lrd->log.noreकरोinoext.inoext_idx =
		    cpu_to_le32((u32) (माप_प्रकार) cd->iplist[2]);

		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		*pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, शून्य));

		/* update bmap */
		tlck->flag |= tlckUPDATEMAP;

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
	पूर्ण अन्यथा
		jfs_err("diLog: UFO type tlck:0x%p", tlck);
#अगर_घोषित  _JFS_WIP
	/*
	 *	alloc/मुक्त बाह्यal EA extent
	 *
	 * a maplock क्रम txUpdateMap() to update bPWMAP क्रम alloc/मुक्त
	 * of the extent has been क्रमmatted at txLock() समय;
	 */
	अन्यथा अणु
		निश्चित(tlck->type & tlckEA);

		/* log LOG_UPDATEMAP क्रम logreकरो() to update bmap क्रम
		 * alloc of new (and मुक्त of old) बाह्यal EA extent;
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		nlock = pxdlock->index;
		क्रम (i = 0; i < nlock; i++, pxdlock++) अणु
			अगर (pxdlock->flag & mlckALLOCPXD)
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_ALLOCPXD);
			अन्यथा
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_FREEPXD);
			lrd->log.updatemap.nxd = cpu_to_le16(1);
			lrd->log.updatemap.pxd = pxdlock->pxd;
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, शून्य));
		पूर्ण

		/* update bmap */
		tlck->flag |= tlckUPDATEMAP;
	पूर्ण
#पूर्ण_अगर				/* _JFS_WIP */

	वापस;
पूर्ण

/*
 *	dataLog()
 *
 * function:	log data tlock
 */
अटल व्योम dataLog(काष्ठा jfs_log *log, काष्ठा tblock *tblk, काष्ठा lrd *lrd,
	    काष्ठा tlock *tlck)
अणु
	काष्ठा metapage *mp;
	pxd_t *pxd;

	mp = tlck->mp;

	/* initialize as REDOPAGE record क्रमmat */
	lrd->log.reकरोpage.type = cpu_to_le16(LOG_DATA);
	lrd->log.reकरोpage.l2linesize = cpu_to_le16(L2DATASLOTSIZE);

	pxd = &lrd->log.reकरोpage.pxd;

	/* log after-image क्रम logreकरो(): */
	lrd->type = cpu_to_le16(LOG_REDOPAGE);

	अगर (jfs_dirtable_अंतरभूत(tlck->ip)) अणु
		/*
		 * The table has been truncated, we've must have deleted
		 * the last entry, so करोn't bother logging this
		 */
		mp->lid = 0;
		grab_metapage(mp);
		metapage_homeok(mp);
		discard_metapage(mp);
		tlck->mp = शून्य;
		वापस;
	पूर्ण

	PXDaddress(pxd, mp->index);
	PXDlength(pxd, mp->logical_size >> tblk->sb->s_blocksize_bits);

	lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

	/* mark page as homeward bound */
	tlck->flag |= tlckWRITEPAGE;

	वापस;
पूर्ण

/*
 *	dtLog()
 *
 * function:	log dtree tlock and क्रमmat maplock to update bmap;
 */
अटल व्योम dtLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
	   काष्ठा tlock * tlck)
अणु
	काष्ठा metapage *mp;
	काष्ठा pxd_lock *pxdlock;
	pxd_t *pxd;

	mp = tlck->mp;

	/* initialize as REDOPAGE/NOREDOPAGE record क्रमmat */
	lrd->log.reकरोpage.type = cpu_to_le16(LOG_DTREE);
	lrd->log.reकरोpage.l2linesize = cpu_to_le16(L2DTSLOTSIZE);

	pxd = &lrd->log.reकरोpage.pxd;

	अगर (tlck->type & tlckBTROOT)
		lrd->log.reकरोpage.type |= cpu_to_le16(LOG_BTROOT);

	/*
	 *	page extension via relocation: entry insertion;
	 *	page extension in-place: entry insertion;
	 *	new right page from page split, reinitialized in-line
	 *	root from root page split: entry insertion;
	 */
	अगर (tlck->type & (tlckNEW | tlckEXTEND)) अणु
		/* log after-image of the new page क्रम logreकरो():
		 * mark log (LOG_NEW) क्रम logreकरो() to initialize
		 * मुक्तlist and update bmap क्रम alloc of the new page;
		 */
		lrd->type = cpu_to_le16(LOG_REDOPAGE);
		अगर (tlck->type & tlckEXTEND)
			lrd->log.reकरोpage.type |= cpu_to_le16(LOG_EXTEND);
		अन्यथा
			lrd->log.reकरोpage.type |= cpu_to_le16(LOG_NEW);
		PXDaddress(pxd, mp->index);
		PXDlength(pxd,
			  mp->logical_size >> tblk->sb->s_blocksize_bits);
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/* क्रमmat a maplock क्रम txUpdateMap() to update bPMAP क्रम
		 * alloc of the new page;
		 */
		अगर (tlck->type & tlckBTROOT)
			वापस;
		tlck->flag |= tlckUPDATEMAP;
		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		pxdlock->flag = mlckALLOCPXD;
		pxdlock->pxd = *pxd;

		pxdlock->index = 1;

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
		वापस;
	पूर्ण

	/*
	 *	entry insertion/deletion,
	 *	sibling page link update (old right page beक्रमe split);
	 */
	अगर (tlck->type & (tlckENTRY | tlckRELINK)) अणु
		/* log after-image क्रम logreकरो(): */
		lrd->type = cpu_to_le16(LOG_REDOPAGE);
		PXDaddress(pxd, mp->index);
		PXDlength(pxd,
			  mp->logical_size >> tblk->sb->s_blocksize_bits);
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
		वापस;
	पूर्ण

	/*
	 *	page deletion: page has been invalidated
	 *	page relocation: source extent
	 *
	 *	a maplock क्रम मुक्त of the page has been क्रमmatted
	 *	at txLock() समय);
	 */
	अगर (tlck->type & (tlckFREE | tlckRELOCATE)) अणु
		/* log LOG_NOREDOPAGE of the deleted page क्रम logreकरो()
		 * to start NoReकरोPage filter and to update bmap क्रम मुक्त
		 * of the deletd page
		 */
		lrd->type = cpu_to_le16(LOG_NOREDOPAGE);
		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		*pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, शून्य));

		/* a maplock क्रम txUpdateMap() क्रम मुक्त of the page
		 * has been क्रमmatted at txLock() समय;
		 */
		tlck->flag |= tlckUPDATEMAP;
	पूर्ण
	वापस;
पूर्ण

/*
 *	xtLog()
 *
 * function:	log xtree tlock and क्रमmat maplock to update bmap;
 */
अटल व्योम xtLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
	   काष्ठा tlock * tlck)
अणु
	काष्ठा inode *ip;
	काष्ठा metapage *mp;
	xtpage_t *p;
	काष्ठा xtlock *xtlck;
	काष्ठा maplock *maplock;
	काष्ठा xdlistlock *xadlock;
	काष्ठा pxd_lock *pxdlock;
	pxd_t *page_pxd;
	पूर्णांक next, lwm, hwm;

	ip = tlck->ip;
	mp = tlck->mp;

	/* initialize as REDOPAGE/NOREDOPAGE record क्रमmat */
	lrd->log.reकरोpage.type = cpu_to_le16(LOG_XTREE);
	lrd->log.reकरोpage.l2linesize = cpu_to_le16(L2XTSLOTSIZE);

	page_pxd = &lrd->log.reकरोpage.pxd;

	अगर (tlck->type & tlckBTROOT) अणु
		lrd->log.reकरोpage.type |= cpu_to_le16(LOG_BTROOT);
		p = &JFS_IP(ip)->i_xtroot;
		अगर (S_ISसूची(ip->i_mode))
			lrd->log.reकरोpage.type |=
			    cpu_to_le16(LOG_सूची_XTREE);
	पूर्ण अन्यथा
		p = (xtpage_t *) mp->data;
	next = le16_to_cpu(p->header.nextindex);

	xtlck = (काष्ठा xtlock *) & tlck->lock;

	maplock = (काष्ठा maplock *) & tlck->lock;
	xadlock = (काष्ठा xdlistlock *) maplock;

	/*
	 *	entry insertion/extension;
	 *	sibling page link update (old right page beक्रमe split);
	 */
	अगर (tlck->type & (tlckNEW | tlckGROW | tlckRELINK)) अणु
		/* log after-image क्रम logreकरो():
		 * logreकरो() will update bmap क्रम alloc of new/extended
		 * extents (XAD_NEW|XAD_EXTEND) of XAD[lwm:next) from
		 * after-image of XADlist;
		 * logreकरो() resets (XAD_NEW|XAD_EXTEND) flag when
		 * applying the after-image to the meta-data page.
		 */
		lrd->type = cpu_to_le16(LOG_REDOPAGE);
		PXDaddress(page_pxd, mp->index);
		PXDlength(page_pxd,
			  mp->logical_size >> tblk->sb->s_blocksize_bits);
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/* क्रमmat a maplock क्रम txUpdateMap() to update bPMAP
		 * क्रम alloc of new/extended extents of XAD[lwm:next)
		 * from the page itself;
		 * txUpdateMap() resets (XAD_NEW|XAD_EXTEND) flag.
		 */
		lwm = xtlck->lwm.offset;
		अगर (lwm == 0)
			lwm = XTPAGEMAXSLOT;

		अगर (lwm == next)
			जाओ out;
		अगर (lwm > next) अणु
			jfs_err("xtLog: lwm > next");
			जाओ out;
		पूर्ण
		tlck->flag |= tlckUPDATEMAP;
		xadlock->flag = mlckALLOCXADLIST;
		xadlock->count = next - lwm;
		अगर ((xadlock->count <= 4) && (tblk->xflag & COMMIT_LAZY)) अणु
			पूर्णांक i;
			pxd_t *pxd;
			/*
			 * Lazy commit may allow xtree to be modअगरied beक्रमe
			 * txUpdateMap runs.  Copy xad पूर्णांकo linelock to
			 * preserve correct data.
			 *
			 * We can fit twice as may pxd's as xads in the lock
			 */
			xadlock->flag = mlckALLOCPXDLIST;
			pxd = xadlock->xdlist = &xtlck->pxdlock;
			क्रम (i = 0; i < xadlock->count; i++) अणु
				PXDaddress(pxd, addressXAD(&p->xad[lwm + i]));
				PXDlength(pxd, lengthXAD(&p->xad[lwm + i]));
				p->xad[lwm + i].flag &=
				    ~(XAD_NEW | XAD_EXTENDED);
				pxd++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * xdlist will poपूर्णांक to पूर्णांकo inode's xtree, ensure
			 * that transaction is not committed lazily.
			 */
			xadlock->flag = mlckALLOCXADLIST;
			xadlock->xdlist = &p->xad[lwm];
			tblk->xflag &= ~COMMIT_LAZY;
		पूर्ण
		jfs_info("xtLog: alloc ip:0x%p mp:0x%p tlck:0x%p lwm:%d count:%d",
			 tlck->ip, mp, tlck, lwm, xadlock->count);

		maplock->index = 1;

	      out:
		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;

		वापस;
	पूर्ण

	/*
	 *	page deletion: file deletion/truncation (ref. xtTruncate())
	 *
	 * (page will be invalidated after log is written and bmap
	 * is updated from the page);
	 */
	अगर (tlck->type & tlckFREE) अणु
		/* LOG_NOREDOPAGE log क्रम NoReकरोPage filter:
		 * अगर page मुक्त from file delete, NoReकरोFile filter from
		 * inode image of zero link count will subsume NoReकरोPage
		 * filters क्रम each page;
		 * अगर page मुक्त from file truncattion, ग_लिखो NoReकरोPage
		 * filter;
		 *
		 * upadte of block allocation map क्रम the page itself:
		 * अगर page मुक्त from deletion and truncation, LOG_UPDATEMAP
		 * log क्रम the page itself is generated from processing
		 * its parent page xad entries;
		 */
		/* अगर page मुक्त from file truncation, log LOG_NOREDOPAGE
		 * of the deleted page क्रम logreकरो() to start NoReकरोPage
		 * filter क्रम the page;
		 */
		अगर (tblk->xflag & COMMIT_TRUNCATE) अणु
			/* ग_लिखो NOREDOPAGE क्रम the page */
			lrd->type = cpu_to_le16(LOG_NOREDOPAGE);
			PXDaddress(page_pxd, mp->index);
			PXDlength(page_pxd,
				  mp->logical_size >> tblk->sb->
				  s_blocksize_bits);
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, शून्य));

			अगर (tlck->type & tlckBTROOT) अणु
				/* Empty xtree must be logged */
				lrd->type = cpu_to_le16(LOG_REDOPAGE);
				lrd->backchain =
				    cpu_to_le32(lmLog(log, tblk, lrd, tlck));
			पूर्ण
		पूर्ण

		/* init LOG_UPDATEMAP of the मुक्तd extents
		 * XAD[XTENTRYSTART:hwm) from the deleted page itself
		 * क्रम logreकरो() to update bmap;
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		lrd->log.updatemap.type = cpu_to_le16(LOG_FREEXADLIST);
		xtlck = (काष्ठा xtlock *) & tlck->lock;
		hwm = xtlck->hwm.offset;
		lrd->log.updatemap.nxd =
		    cpu_to_le16(hwm - XTENTRYSTART + 1);
		/* reक्रमmat linelock क्रम lmLog() */
		xtlck->header.offset = XTENTRYSTART;
		xtlck->header.length = hwm - XTENTRYSTART + 1;
		xtlck->index = 1;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/* क्रमmat a maplock क्रम txUpdateMap() to update bmap
		 * to मुक्त extents of XAD[XTENTRYSTART:hwm) from the
		 * deleted page itself;
		 */
		tlck->flag |= tlckUPDATEMAP;
		xadlock->count = hwm - XTENTRYSTART + 1;
		अगर ((xadlock->count <= 4) && (tblk->xflag & COMMIT_LAZY)) अणु
			पूर्णांक i;
			pxd_t *pxd;
			/*
			 * Lazy commit may allow xtree to be modअगरied beक्रमe
			 * txUpdateMap runs.  Copy xad पूर्णांकo linelock to
			 * preserve correct data.
			 *
			 * We can fit twice as may pxd's as xads in the lock
			 */
			xadlock->flag = mlckFREEPXDLIST;
			pxd = xadlock->xdlist = &xtlck->pxdlock;
			क्रम (i = 0; i < xadlock->count; i++) अणु
				PXDaddress(pxd,
					addressXAD(&p->xad[XTENTRYSTART + i]));
				PXDlength(pxd,
					lengthXAD(&p->xad[XTENTRYSTART + i]));
				pxd++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * xdlist will poपूर्णांक to पूर्णांकo inode's xtree, ensure
			 * that transaction is not committed lazily.
			 */
			xadlock->flag = mlckFREEXADLIST;
			xadlock->xdlist = &p->xad[XTENTRYSTART];
			tblk->xflag &= ~COMMIT_LAZY;
		पूर्ण
		jfs_info("xtLog: free ip:0x%p mp:0x%p count:%d lwm:2",
			 tlck->ip, mp, xadlock->count);

		maplock->index = 1;

		/* mark page as invalid */
		अगर (((tblk->xflag & COMMIT_PWMAP) || S_ISसूची(ip->i_mode))
		    && !(tlck->type & tlckBTROOT))
			tlck->flag |= tlckFREEPAGE;
		/*
		   अन्यथा (tblk->xflag & COMMIT_PMAP)
		   ? release the page;
		 */
		वापस;
	पूर्ण

	/*
	 *	page/entry truncation: file truncation (ref. xtTruncate())
	 *
	 *	|----------+------+------+---------------|
	 *		   |      |      |
	 *		   |      |     hwm - hwm beक्रमe truncation
	 *		   |     next - truncation poपूर्णांक
	 *		  lwm - lwm beक्रमe truncation
	 * header ?
	 */
	अगर (tlck->type & tlckTRUNCATE) अणु
		pxd_t pxd;	/* truncated extent of xad */
		पूर्णांक twm;

		/*
		 * For truncation the entire linelock may be used, so it would
		 * be dअगरficult to store xad list in linelock itself.
		 * Thereक्रमe, we'll just क्रमce transaction to be committed
		 * synchronously, so that xtree pages won't be changed beक्रमe
		 * txUpdateMap runs.
		 */
		tblk->xflag &= ~COMMIT_LAZY;
		lwm = xtlck->lwm.offset;
		अगर (lwm == 0)
			lwm = XTPAGEMAXSLOT;
		hwm = xtlck->hwm.offset;
		twm = xtlck->twm.offset;

		/*
		 *	ग_लिखो log records
		 */
		/* log after-image क्रम logreकरो():
		 *
		 * logreकरो() will update bmap क्रम alloc of new/extended
		 * extents (XAD_NEW|XAD_EXTEND) of XAD[lwm:next) from
		 * after-image of XADlist;
		 * logreकरो() resets (XAD_NEW|XAD_EXTEND) flag when
		 * applying the after-image to the meta-data page.
		 */
		lrd->type = cpu_to_le16(LOG_REDOPAGE);
		PXDaddress(page_pxd, mp->index);
		PXDlength(page_pxd,
			  mp->logical_size >> tblk->sb->s_blocksize_bits);
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/*
		 * truncate entry XAD[twm == next - 1]:
		 */
		अगर (twm == next - 1) अणु
			/* init LOG_UPDATEMAP क्रम logreकरो() to update bmap क्रम
			 * मुक्त of truncated delta extent of the truncated
			 * entry XAD[next - 1]:
			 * (xtlck->pxdlock = truncated delta extent);
			 */
			pxdlock = (काष्ठा pxd_lock *) & xtlck->pxdlock;
			/* निश्चित(pxdlock->type & tlckTRUNCATE); */
			lrd->type = cpu_to_le16(LOG_UPDATEMAP);
			lrd->log.updatemap.type = cpu_to_le16(LOG_FREEPXD);
			lrd->log.updatemap.nxd = cpu_to_le16(1);
			lrd->log.updatemap.pxd = pxdlock->pxd;
			pxd = pxdlock->pxd;	/* save to क्रमmat maplock */
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, शून्य));
		पूर्ण

		/*
		 * मुक्त entries XAD[next:hwm]:
		 */
		अगर (hwm >= next) अणु
			/* init LOG_UPDATEMAP of the मुक्तd extents
			 * XAD[next:hwm] from the deleted page itself
			 * क्रम logreकरो() to update bmap;
			 */
			lrd->type = cpu_to_le16(LOG_UPDATEMAP);
			lrd->log.updatemap.type =
			    cpu_to_le16(LOG_FREEXADLIST);
			xtlck = (काष्ठा xtlock *) & tlck->lock;
			hwm = xtlck->hwm.offset;
			lrd->log.updatemap.nxd =
			    cpu_to_le16(hwm - next + 1);
			/* reक्रमmat linelock क्रम lmLog() */
			xtlck->header.offset = next;
			xtlck->header.length = hwm - next + 1;
			xtlck->index = 1;
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, tlck));
		पूर्ण

		/*
		 *	क्रमmat maplock(s) क्रम txUpdateMap() to update bmap
		 */
		maplock->index = 0;

		/*
		 * allocate entries XAD[lwm:next):
		 */
		अगर (lwm < next) अणु
			/* क्रमmat a maplock क्रम txUpdateMap() to update bPMAP
			 * क्रम alloc of new/extended extents of XAD[lwm:next)
			 * from the page itself;
			 * txUpdateMap() resets (XAD_NEW|XAD_EXTEND) flag.
			 */
			tlck->flag |= tlckUPDATEMAP;
			xadlock->flag = mlckALLOCXADLIST;
			xadlock->count = next - lwm;
			xadlock->xdlist = &p->xad[lwm];

			jfs_info("xtLog: alloc ip:0x%p mp:0x%p count:%d lwm:%d next:%d",
				 tlck->ip, mp, xadlock->count, lwm, next);
			maplock->index++;
			xadlock++;
		पूर्ण

		/*
		 * truncate entry XAD[twm == next - 1]:
		 */
		अगर (twm == next - 1) अणु
			/* क्रमmat a maplock क्रम txUpdateMap() to update bmap
			 * to मुक्त truncated delta extent of the truncated
			 * entry XAD[next - 1];
			 * (xtlck->pxdlock = truncated delta extent);
			 */
			tlck->flag |= tlckUPDATEMAP;
			pxdlock = (काष्ठा pxd_lock *) xadlock;
			pxdlock->flag = mlckFREEPXD;
			pxdlock->count = 1;
			pxdlock->pxd = pxd;

			jfs_info("xtLog: truncate ip:0x%p mp:0x%p count:%d hwm:%d",
				 ip, mp, pxdlock->count, hwm);
			maplock->index++;
			xadlock++;
		पूर्ण

		/*
		 * मुक्त entries XAD[next:hwm]:
		 */
		अगर (hwm >= next) अणु
			/* क्रमmat a maplock क्रम txUpdateMap() to update bmap
			 * to मुक्त extents of XAD[next:hwm] from thedeleted
			 * page itself;
			 */
			tlck->flag |= tlckUPDATEMAP;
			xadlock->flag = mlckFREEXADLIST;
			xadlock->count = hwm - next + 1;
			xadlock->xdlist = &p->xad[next];

			jfs_info("xtLog: free ip:0x%p mp:0x%p count:%d next:%d hwm:%d",
				 tlck->ip, mp, xadlock->count, next, hwm);
			maplock->index++;
		पूर्ण

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
	पूर्ण
	वापस;
पूर्ण

/*
 *	mapLog()
 *
 * function:	log from maplock of मुक्तd data extents;
 */
अटल व्योम mapLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
		   काष्ठा tlock * tlck)
अणु
	काष्ठा pxd_lock *pxdlock;
	पूर्णांक i, nlock;
	pxd_t *pxd;

	/*
	 *	page relocation: मुक्त the source page extent
	 *
	 * a maplock क्रम txUpdateMap() क्रम मुक्त of the page
	 * has been क्रमmatted at txLock() समय saving the src
	 * relocated page address;
	 */
	अगर (tlck->type & tlckRELOCATE) अणु
		/* log LOG_NOREDOPAGE of the old relocated page
		 * क्रम logreकरो() to start NoReकरोPage filter;
		 */
		lrd->type = cpu_to_le16(LOG_NOREDOPAGE);
		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		pxd = &lrd->log.reकरोpage.pxd;
		*pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, शून्य));

		/* (N.B. currently, logreकरो() करोes NOT update bmap
		 * क्रम मुक्त of the page itself क्रम (LOG_XTREE|LOG_NOREDOPAGE);
		 * अगर page मुक्त from relocation, LOG_UPDATEMAP log is
		 * specअगरically generated now क्रम logreकरो()
		 * to update bmap क्रम मुक्त of src relocated page;
		 * (new flag LOG_RELOCATE may be पूर्णांकroduced which will
		 * inक्रमm logreकरो() to start NOReकरोPage filter and also
		 * update block allocation map at the same समय, thus
		 * aव्योमing an extra log ग_लिखो);
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		lrd->log.updatemap.type = cpu_to_le16(LOG_FREEPXD);
		lrd->log.updatemap.nxd = cpu_to_le16(1);
		lrd->log.updatemap.pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, शून्य));

		/* a maplock क्रम txUpdateMap() क्रम मुक्त of the page
		 * has been क्रमmatted at txLock() समय;
		 */
		tlck->flag |= tlckUPDATEMAP;
		वापस;
	पूर्ण
	/*

	 * Otherwise it's not a relocate request
	 *
	 */
	अन्यथा अणु
		/* log LOG_UPDATEMAP क्रम logreकरो() to update bmap क्रम
		 * मुक्त of truncated/relocated delta extent of the data;
		 * e.g.: बाह्यal EA extent, relocated/truncated extent
		 * from xtTailgate();
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
		nlock = pxdlock->index;
		क्रम (i = 0; i < nlock; i++, pxdlock++) अणु
			अगर (pxdlock->flag & mlckALLOCPXD)
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_ALLOCPXD);
			अन्यथा
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_FREEPXD);
			lrd->log.updatemap.nxd = cpu_to_le16(1);
			lrd->log.updatemap.pxd = pxdlock->pxd;
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, शून्य));
			jfs_info("mapLog: xaddr:0x%lx xlen:0x%x",
				 (uदीर्घ) addressPXD(&pxdlock->pxd),
				 lengthPXD(&pxdlock->pxd));
		पूर्ण

		/* update bmap */
		tlck->flag |= tlckUPDATEMAP;
	पूर्ण
पूर्ण

/*
 *	txEA()
 *
 * function:	acquire maplock क्रम EA/ACL extents or
 *		set COMMIT_INLINE flag;
 */
व्योम txEA(tid_t tid, काष्ठा inode *ip, dxd_t * oldea, dxd_t * newea)
अणु
	काष्ठा tlock *tlck = शून्य;
	काष्ठा pxd_lock *maplock = शून्य, *pxdlock = शून्य;

	/*
	 * क्रमmat maplock क्रम alloc of new EA extent
	 */
	अगर (newea) अणु
		/* Since the newea could be a completely zeroed entry we need to
		 * check क्रम the two flags which indicate we should actually
		 * commit new EA data
		 */
		अगर (newea->flag & DXD_EXTENT) अणु
			tlck = txMaplock(tid, ip, tlckMAP);
			maplock = (काष्ठा pxd_lock *) & tlck->lock;
			pxdlock = (काष्ठा pxd_lock *) maplock;
			pxdlock->flag = mlckALLOCPXD;
			PXDaddress(&pxdlock->pxd, addressDXD(newea));
			PXDlength(&pxdlock->pxd, lengthDXD(newea));
			pxdlock++;
			maplock->index = 1;
		पूर्ण अन्यथा अगर (newea->flag & DXD_INLINE) अणु
			tlck = शून्य;

			set_cflag(COMMIT_Inlineea, ip);
		पूर्ण
	पूर्ण

	/*
	 * क्रमmat maplock क्रम मुक्त of old EA extent
	 */
	अगर (!test_cflag(COMMIT_Nolink, ip) && oldea->flag & DXD_EXTENT) अणु
		अगर (tlck == शून्य) अणु
			tlck = txMaplock(tid, ip, tlckMAP);
			maplock = (काष्ठा pxd_lock *) & tlck->lock;
			pxdlock = (काष्ठा pxd_lock *) maplock;
			maplock->index = 0;
		पूर्ण
		pxdlock->flag = mlckFREEPXD;
		PXDaddress(&pxdlock->pxd, addressDXD(oldea));
		PXDlength(&pxdlock->pxd, lengthDXD(oldea));
		maplock->index++;
	पूर्ण
पूर्ण

/*
 *	txForce()
 *
 * function: synchronously ग_लिखो pages locked by transaction
 *	     after txLog() but beक्रमe txUpdateMap();
 */
अटल व्योम txForce(काष्ठा tblock * tblk)
अणु
	काष्ठा tlock *tlck;
	lid_t lid, next;
	काष्ठा metapage *mp;

	/*
	 * reverse the order of transaction tlocks in
	 * careful update order of address index pages
	 * (right to left, bottom up)
	 */
	tlck = lid_to_tlock(tblk->next);
	lid = tlck->next;
	tlck->next = 0;
	जबतक (lid) अणु
		tlck = lid_to_tlock(lid);
		next = tlck->next;
		tlck->next = tblk->next;
		tblk->next = lid;
		lid = next;
	पूर्ण

	/*
	 * synchronously ग_लिखो the page, and
	 * hold the page क्रम txUpdateMap();
	 */
	क्रम (lid = tblk->next; lid; lid = next) अणु
		tlck = lid_to_tlock(lid);
		next = tlck->next;

		अगर ((mp = tlck->mp) != शून्य &&
		    (tlck->type & tlckBTROOT) == 0) अणु
			निश्चित(mp->xflag & COMMIT_PAGE);

			अगर (tlck->flag & tlckWRITEPAGE) अणु
				tlck->flag &= ~tlckWRITEPAGE;

				/* करो not release page to मुक्तlist */
				क्रमce_metapage(mp);
#अगर 0
				/*
				 * The "right" thing to करो here is to
				 * synchronously ग_लिखो the metadata.
				 * With the current implementation this
				 * is hard since ग_लिखो_metapage requires
				 * us to kunmap & remap the page.  If we
				 * have tlocks poपूर्णांकing पूर्णांकo the metadata
				 * pages, we करोn't want to करो this.  I think
				 * we can get by with synchronously writing
				 * the pages when they are released.
				 */
				निश्चित(mp->nohomeok);
				set_bit(META_dirty, &mp->flag);
				set_bit(META_sync, &mp->flag);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	txUpdateMap()
 *
 * function:	update persistent allocation map (and working map
 *		अगर appropriate);
 *
 * parameter:
 */
अटल व्योम txUpdateMap(काष्ठा tblock * tblk)
अणु
	काष्ठा inode *ip;
	काष्ठा inode *ipimap;
	lid_t lid;
	काष्ठा tlock *tlck;
	काष्ठा maplock *maplock;
	काष्ठा pxd_lock pxdlock;
	पूर्णांक maptype;
	पूर्णांक k, nlock;
	काष्ठा metapage *mp = शून्य;

	ipimap = JFS_SBI(tblk->sb)->ipimap;

	maptype = (tblk->xflag & COMMIT_PMAP) ? COMMIT_PMAP : COMMIT_PWMAP;


	/*
	 *	update block allocation map
	 *
	 * update allocation state in pmap (and wmap) and
	 * update lsn of the pmap page;
	 */
	/*
	 * scan each tlock/page of transaction क्रम block allocation/मुक्त:
	 *
	 * क्रम each tlock/page of transaction, update map.
	 *  ? are there tlock क्रम pmap and pwmap at the same समय ?
	 */
	क्रम (lid = tblk->next; lid; lid = tlck->next) अणु
		tlck = lid_to_tlock(lid);

		अगर ((tlck->flag & tlckUPDATEMAP) == 0)
			जारी;

		अगर (tlck->flag & tlckFREEPAGE) अणु
			/*
			 * Another thपढ़ो may attempt to reuse मुक्तd space
			 * immediately, so we want to get rid of the metapage
			 * beक्रमe anyone अन्यथा has a chance to get it.
			 * Lock metapage, update maps, then invalidate
			 * the metapage.
			 */
			mp = tlck->mp;
			ASSERT(mp->xflag & COMMIT_PAGE);
			grab_metapage(mp);
		पूर्ण

		/*
		 * extent list:
		 * . in-line PXD list:
		 * . out-of-line XAD list:
		 */
		maplock = (काष्ठा maplock *) & tlck->lock;
		nlock = maplock->index;

		क्रम (k = 0; k < nlock; k++, maplock++) अणु
			/*
			 * allocate blocks in persistent map:
			 *
			 * blocks have been allocated from wmap at alloc समय;
			 */
			अगर (maplock->flag & mlckALLOC) अणु
				txAllocPMap(ipimap, maplock, tblk);
			पूर्ण
			/*
			 * मुक्त blocks in persistent and working map:
			 * blocks will be मुक्तd in pmap and then in wmap;
			 *
			 * ? tblock specअगरies the PMAP/PWMAP based upon
			 * transaction
			 *
			 * मुक्त blocks in persistent map:
			 * blocks will be मुक्तd from wmap at last reference
			 * release of the object क्रम regular files;
			 *
			 * Alway मुक्त blocks from both persistent & working
			 * maps क्रम directories
			 */
			अन्यथा अणु	/* (maplock->flag & mlckFREE) */

				अगर (tlck->flag & tlckसूचीECTORY)
					txFreeMap(ipimap, maplock,
						  tblk, COMMIT_PWMAP);
				अन्यथा
					txFreeMap(ipimap, maplock,
						  tblk, maptype);
			पूर्ण
		पूर्ण
		अगर (tlck->flag & tlckFREEPAGE) अणु
			अगर (!(tblk->flag & tblkGC_LAZY)) अणु
				/* This is equivalent to txRelease */
				ASSERT(mp->lid == lid);
				tlck->mp->lid = 0;
			पूर्ण
			निश्चित(mp->nohomeok == 1);
			metapage_homeok(mp);
			discard_metapage(mp);
			tlck->mp = शून्य;
		पूर्ण
	पूर्ण
	/*
	 *	update inode allocation map
	 *
	 * update allocation state in pmap and
	 * update lsn of the pmap page;
	 * update in-memory inode flag/state
	 *
	 * unlock mapper/ग_लिखो lock
	 */
	अगर (tblk->xflag & COMMIT_CREATE) अणु
		diUpdatePMap(ipimap, tblk->ino, false, tblk);
		/* update persistent block allocation map
		 * क्रम the allocation of inode extent;
		 */
		pxdlock.flag = mlckALLOCPXD;
		pxdlock.pxd = tblk->u.ixpxd;
		pxdlock.index = 1;
		txAllocPMap(ipimap, (काष्ठा maplock *) & pxdlock, tblk);
	पूर्ण अन्यथा अगर (tblk->xflag & COMMIT_DELETE) अणु
		ip = tblk->u.ip;
		diUpdatePMap(ipimap, ip->i_ino, true, tblk);
		iput(ip);
	पूर्ण
पूर्ण

/*
 *	txAllocPMap()
 *
 * function: allocate from persistent map;
 *
 * parameter:
 *	ipbmap	-
 *	malock	-
 *		xad list:
 *		pxd:
 *
 *	maptype -
 *		allocate from persistent map;
 *		मुक्त from persistent map;
 *		(e.g., पंचांगp file - मुक्त from working map at releae
 *		 of last reference);
 *		मुक्त from persistent and working map;
 *
 *	lsn	- log sequence number;
 */
अटल व्योम txAllocPMap(काष्ठा inode *ip, काष्ठा maplock * maplock,
			काष्ठा tblock * tblk)
अणु
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा xdlistlock *xadlistlock;
	xad_t *xad;
	s64 xaddr;
	पूर्णांक xlen;
	काष्ठा pxd_lock *pxdlock;
	काष्ठा xdlistlock *pxdlistlock;
	pxd_t *pxd;
	पूर्णांक n;

	/*
	 * allocate from persistent map;
	 */
	अगर (maplock->flag & mlckALLOCXADLIST) अणु
		xadlistlock = (काष्ठा xdlistlock *) maplock;
		xad = xadlistlock->xdlist;
		क्रम (n = 0; n < xadlistlock->count; n++, xad++) अणु
			अगर (xad->flag & (XAD_NEW | XAD_EXTENDED)) अणु
				xaddr = addressXAD(xad);
				xlen = lengthXAD(xad);
				dbUpdatePMap(ipbmap, false, xaddr,
					     (s64) xlen, tblk);
				xad->flag &= ~(XAD_NEW | XAD_EXTENDED);
				jfs_info("allocPMap: xaddr:0x%lx xlen:%d",
					 (uदीर्घ) xaddr, xlen);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (maplock->flag & mlckALLOCPXD) अणु
		pxdlock = (काष्ठा pxd_lock *) maplock;
		xaddr = addressPXD(&pxdlock->pxd);
		xlen = lengthPXD(&pxdlock->pxd);
		dbUpdatePMap(ipbmap, false, xaddr, (s64) xlen, tblk);
		jfs_info("allocPMap: xaddr:0x%lx xlen:%d", (uदीर्घ) xaddr, xlen);
	पूर्ण अन्यथा अणु		/* (maplock->flag & mlckALLOCPXDLIST) */

		pxdlistlock = (काष्ठा xdlistlock *) maplock;
		pxd = pxdlistlock->xdlist;
		क्रम (n = 0; n < pxdlistlock->count; n++, pxd++) अणु
			xaddr = addressPXD(pxd);
			xlen = lengthPXD(pxd);
			dbUpdatePMap(ipbmap, false, xaddr, (s64) xlen,
				     tblk);
			jfs_info("allocPMap: xaddr:0x%lx xlen:%d",
				 (uदीर्घ) xaddr, xlen);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	txFreeMap()
 *
 * function:	मुक्त from persistent and/or working map;
 *
 * toकरो: optimization
 */
व्योम txFreeMap(काष्ठा inode *ip,
	       काष्ठा maplock * maplock, काष्ठा tblock * tblk, पूर्णांक maptype)
अणु
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा xdlistlock *xadlistlock;
	xad_t *xad;
	s64 xaddr;
	पूर्णांक xlen;
	काष्ठा pxd_lock *pxdlock;
	काष्ठा xdlistlock *pxdlistlock;
	pxd_t *pxd;
	पूर्णांक n;

	jfs_info("txFreeMap: tblk:0x%p maplock:0x%p maptype:0x%x",
		 tblk, maplock, maptype);

	/*
	 * मुक्त from persistent map;
	 */
	अगर (maptype == COMMIT_PMAP || maptype == COMMIT_PWMAP) अणु
		अगर (maplock->flag & mlckFREEXADLIST) अणु
			xadlistlock = (काष्ठा xdlistlock *) maplock;
			xad = xadlistlock->xdlist;
			क्रम (n = 0; n < xadlistlock->count; n++, xad++) अणु
				अगर (!(xad->flag & XAD_NEW)) अणु
					xaddr = addressXAD(xad);
					xlen = lengthXAD(xad);
					dbUpdatePMap(ipbmap, true, xaddr,
						     (s64) xlen, tblk);
					jfs_info("freePMap: xaddr:0x%lx xlen:%d",
						 (uदीर्घ) xaddr, xlen);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (maplock->flag & mlckFREEPXD) अणु
			pxdlock = (काष्ठा pxd_lock *) maplock;
			xaddr = addressPXD(&pxdlock->pxd);
			xlen = lengthPXD(&pxdlock->pxd);
			dbUpdatePMap(ipbmap, true, xaddr, (s64) xlen,
				     tblk);
			jfs_info("freePMap: xaddr:0x%lx xlen:%d",
				 (uदीर्घ) xaddr, xlen);
		पूर्ण अन्यथा अणु	/* (maplock->flag & mlckALLOCPXDLIST) */

			pxdlistlock = (काष्ठा xdlistlock *) maplock;
			pxd = pxdlistlock->xdlist;
			क्रम (n = 0; n < pxdlistlock->count; n++, pxd++) अणु
				xaddr = addressPXD(pxd);
				xlen = lengthPXD(pxd);
				dbUpdatePMap(ipbmap, true, xaddr,
					     (s64) xlen, tblk);
				jfs_info("freePMap: xaddr:0x%lx xlen:%d",
					 (uदीर्घ) xaddr, xlen);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * मुक्त from working map;
	 */
	अगर (maptype == COMMIT_PWMAP || maptype == COMMIT_WMAP) अणु
		अगर (maplock->flag & mlckFREEXADLIST) अणु
			xadlistlock = (काष्ठा xdlistlock *) maplock;
			xad = xadlistlock->xdlist;
			क्रम (n = 0; n < xadlistlock->count; n++, xad++) अणु
				xaddr = addressXAD(xad);
				xlen = lengthXAD(xad);
				dbFree(ip, xaddr, (s64) xlen);
				xad->flag = 0;
				jfs_info("freeWMap: xaddr:0x%lx xlen:%d",
					 (uदीर्घ) xaddr, xlen);
			पूर्ण
		पूर्ण अन्यथा अगर (maplock->flag & mlckFREEPXD) अणु
			pxdlock = (काष्ठा pxd_lock *) maplock;
			xaddr = addressPXD(&pxdlock->pxd);
			xlen = lengthPXD(&pxdlock->pxd);
			dbFree(ip, xaddr, (s64) xlen);
			jfs_info("freeWMap: xaddr:0x%lx xlen:%d",
				 (uदीर्घ) xaddr, xlen);
		पूर्ण अन्यथा अणु	/* (maplock->flag & mlckFREEPXDLIST) */

			pxdlistlock = (काष्ठा xdlistlock *) maplock;
			pxd = pxdlistlock->xdlist;
			क्रम (n = 0; n < pxdlistlock->count; n++, pxd++) अणु
				xaddr = addressPXD(pxd);
				xlen = lengthPXD(pxd);
				dbFree(ip, xaddr, (s64) xlen);
				jfs_info("freeWMap: xaddr:0x%lx xlen:%d",
					 (uदीर्घ) xaddr, xlen);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	txFreelock()
 *
 * function:	हटाओ tlock from inode anonymous locklist
 */
व्योम txFreelock(काष्ठा inode *ip)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	काष्ठा tlock *xtlck, *tlck;
	lid_t xlid = 0, lid;

	अगर (!jfs_ip->atlhead)
		वापस;

	TXN_LOCK();
	xtlck = (काष्ठा tlock *) &jfs_ip->atlhead;

	जबतक ((lid = xtlck->next) != 0) अणु
		tlck = lid_to_tlock(lid);
		अगर (tlck->flag & tlckFREELOCK) अणु
			xtlck->next = tlck->next;
			txLockFree(lid);
		पूर्ण अन्यथा अणु
			xtlck = tlck;
			xlid = lid;
		पूर्ण
	पूर्ण

	अगर (jfs_ip->atlhead)
		jfs_ip->atltail = xlid;
	अन्यथा अणु
		jfs_ip->atltail = 0;
		/*
		 * If inode was on anon_list, हटाओ it
		 */
		list_del_init(&jfs_ip->anon_inode_list);
	पूर्ण
	TXN_UNLOCK();
पूर्ण

/*
 *	txAbort()
 *
 * function: पात tx beक्रमe commit;
 *
 * मुक्तs line-locks and segment locks क्रम all
 * segments in comdata काष्ठाure.
 * Optionally sets state of file-प्रणाली to FM_सूचीTY in super-block.
 * log age of page-frames in memory क्रम which caller has
 * are reset to 0 (to aव्योम logwarap).
 */
व्योम txAbort(tid_t tid, पूर्णांक dirty)
अणु
	lid_t lid, next;
	काष्ठा metapage *mp;
	काष्ठा tblock *tblk = tid_to_tblock(tid);
	काष्ठा tlock *tlck;

	/*
	 * मुक्त tlocks of the transaction
	 */
	क्रम (lid = tblk->next; lid; lid = next) अणु
		tlck = lid_to_tlock(lid);
		next = tlck->next;
		mp = tlck->mp;
		JFS_IP(tlck->ip)->xtlid = 0;

		अगर (mp) अणु
			mp->lid = 0;

			/*
			 * reset lsn of page to aव्योम logwarap:
			 *
			 * (page may have been previously committed by another
			 * transaction(s) but has not been paged, i.e.,
			 * it may be on logsync list even though it has not
			 * been logged क्रम the current tx.)
			 */
			अगर (mp->xflag & COMMIT_PAGE && mp->lsn)
				LogSyncRelease(mp);
		पूर्ण
		/* insert tlock at head of मुक्तlist */
		TXN_LOCK();
		txLockFree(lid);
		TXN_UNLOCK();
	पूर्ण

	/* caller will मुक्त the transaction block */

	tblk->next = tblk->last = 0;

	/*
	 * mark fileप्रणाली dirty
	 */
	अगर (dirty)
		jfs_error(tblk->sb, "\n");

	वापस;
पूर्ण

/*
 *	txLazyCommit(व्योम)
 *
 *	All transactions except those changing ipimap (COMMIT_FORCE) are
 *	processed by this routine.  This insures that the inode and block
 *	allocation maps are updated in order.  For synchronous transactions,
 *	let the user thपढ़ो finish processing after txUpdateMap() is called.
 */
अटल व्योम txLazyCommit(काष्ठा tblock * tblk)
अणु
	काष्ठा jfs_log *log;

	जबतक (((tblk->flag & tblkGC_READY) == 0) &&
	       ((tblk->flag & tblkGC_UNLOCKED) == 0)) अणु
		/* We must have gotten ahead of the user thपढ़ो
		 */
		jfs_info("jfs_lazycommit: tblk 0x%p not unlocked", tblk);
		yield();
	पूर्ण

	jfs_info("txLazyCommit: processing tblk 0x%p", tblk);

	txUpdateMap(tblk);

	log = (काष्ठा jfs_log *) JFS_SBI(tblk->sb)->log;

	spin_lock_irq(&log->gघड़ी);	// LOGGC_LOCK

	tblk->flag |= tblkGC_COMMITTED;

	अगर (tblk->flag & tblkGC_READY)
		log->gcrtc--;

	wake_up_all(&tblk->gcरुको);	// LOGGC_WAKEUP

	/*
	 * Can't release log->gclock until we've tested tblk->flag
	 */
	अगर (tblk->flag & tblkGC_LAZY) अणु
		spin_unlock_irq(&log->gघड़ी);	// LOGGC_UNLOCK
		txUnlock(tblk);
		tblk->flag &= ~tblkGC_LAZY;
		txEnd(tblk - TxBlock);	/* Convert back to tid */
	पूर्ण अन्यथा
		spin_unlock_irq(&log->gघड़ी);	// LOGGC_UNLOCK

	jfs_info("txLazyCommit: done: tblk = 0x%p", tblk);
पूर्ण

/*
 *	jfs_lazycommit(व्योम)
 *
 *	To be run as a kernel daemon.  If lbmIODone is called in an पूर्णांकerrupt
 *	context, or where blocking is not wanted, this routine will process
 *	committed transactions from the unlock queue.
 */
पूर्णांक jfs_lazycommit(व्योम *arg)
अणु
	पूर्णांक WorkDone;
	काष्ठा tblock *tblk;
	अचिन्हित दीर्घ flags;
	काष्ठा jfs_sb_info *sbi;

	करो अणु
		LAZY_LOCK(flags);
		jfs_commit_thपढ़ो_waking = 0;	/* OK to wake another thपढ़ो */
		जबतक (!list_empty(&TxAnchor.unlock_queue)) अणु
			WorkDone = 0;
			list_क्रम_each_entry(tblk, &TxAnchor.unlock_queue,
					    cqueue) अणु

				sbi = JFS_SBI(tblk->sb);
				/*
				 * For each volume, the transactions must be
				 * handled in order.  If another commit thपढ़ो
				 * is handling a tblk क्रम this superblock,
				 * skip it
				 */
				अगर (sbi->commit_state & IN_LAZYCOMMIT)
					जारी;

				sbi->commit_state |= IN_LAZYCOMMIT;
				WorkDone = 1;

				/*
				 * Remove transaction from queue
				 */
				list_del(&tblk->cqueue);

				LAZY_UNLOCK(flags);
				txLazyCommit(tblk);
				LAZY_LOCK(flags);

				sbi->commit_state &= ~IN_LAZYCOMMIT;
				/*
				 * Don't continue in the for loop.  (We can't
				 * anyway, it's unsafe!)  We want to go back to
				 * the beginning of the list.
				 */
				अवरोध;
			पूर्ण

			/* If there was nothing to करो, करोn't जारी */
			अगर (!WorkDone)
				अवरोध;
		पूर्ण
		/* In हाल a wakeup came जबतक all thपढ़ोs were active */
		jfs_commit_thपढ़ो_waking = 0;

		अगर (मुक्तzing(current)) अणु
			LAZY_UNLOCK(flags);
			try_to_मुक्तze();
		पूर्ण अन्यथा अणु
			DECLARE_WAITQUEUE(wq, current);

			add_रुको_queue(&jfs_commit_thपढ़ो_रुको, &wq);
			set_current_state(TASK_INTERRUPTIBLE);
			LAZY_UNLOCK(flags);
			schedule();
			हटाओ_रुको_queue(&jfs_commit_thपढ़ो_रुको, &wq);
		पूर्ण
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	अगर (!list_empty(&TxAnchor.unlock_queue))
		jfs_err("jfs_lazycommit being killed w/pending transactions!");
	अन्यथा
		jfs_info("jfs_lazycommit being killed");
	वापस 0;
पूर्ण

व्योम txLazyUnlock(काष्ठा tblock * tblk)
अणु
	अचिन्हित दीर्घ flags;

	LAZY_LOCK(flags);

	list_add_tail(&tblk->cqueue, &TxAnchor.unlock_queue);
	/*
	 * Don't wake up a commit thपढ़ो अगर there is alपढ़ोy one servicing
	 * this superblock, or अगर the last one we woke up hasn't started yet.
	 */
	अगर (!(JFS_SBI(tblk->sb)->commit_state & IN_LAZYCOMMIT) &&
	    !jfs_commit_thपढ़ो_waking) अणु
		jfs_commit_thपढ़ो_waking = 1;
		wake_up(&jfs_commit_thपढ़ो_रुको);
	पूर्ण
	LAZY_UNLOCK(flags);
पूर्ण

अटल व्योम LogSyncRelease(काष्ठा metapage * mp)
अणु
	काष्ठा jfs_log *log = mp->log;

	निश्चित(mp->nohomeok);
	निश्चित(log);
	metapage_homeok(mp);
पूर्ण

/*
 *	txQuiesce
 *
 *	Block all new transactions and push anonymous transactions to
 *	completion
 *
 *	This करोes almost the same thing as jfs_sync below.  We करोn't
 *	worry about deadlocking when jfs_tlocks_low is set, since we would
 *	expect jfs_sync to get us out of that jam.
 */
व्योम txQuiesce(काष्ठा super_block *sb)
अणु
	काष्ठा inode *ip;
	काष्ठा jfs_inode_info *jfs_ip;
	काष्ठा jfs_log *log = JFS_SBI(sb)->log;
	tid_t tid;

	set_bit(log_QUIESCE, &log->flag);

	TXN_LOCK();
restart:
	जबतक (!list_empty(&TxAnchor.anon_list)) अणु
		jfs_ip = list_entry(TxAnchor.anon_list.next,
				    काष्ठा jfs_inode_info,
				    anon_inode_list);
		ip = &jfs_ip->vfs_inode;

		/*
		 * inode will be हटाओd from anonymous list
		 * when it is committed
		 */
		TXN_UNLOCK();
		tid = txBegin(ip->i_sb, COMMIT_INODE | COMMIT_FORCE);
		mutex_lock(&jfs_ip->commit_mutex);
		txCommit(tid, 1, &ip, 0);
		txEnd(tid);
		mutex_unlock(&jfs_ip->commit_mutex);
		/*
		 * Just to be safe.  I करोn't know how
		 * दीर्घ we can run without blocking
		 */
		cond_resched();
		TXN_LOCK();
	पूर्ण

	/*
	 * If jfs_sync is running in parallel, there could be some inodes
	 * on anon_list2.  Let's check.
	 */
	अगर (!list_empty(&TxAnchor.anon_list2)) अणु
		list_splice_init(&TxAnchor.anon_list2, &TxAnchor.anon_list);
		जाओ restart;
	पूर्ण
	TXN_UNLOCK();

	/*
	 * We may need to kick off the group commit
	 */
	jfs_flush_journal(log, 0);
पूर्ण

/*
 * txResume()
 *
 * Allows transactions to start again following txQuiesce
 */
व्योम txResume(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_log *log = JFS_SBI(sb)->log;

	clear_bit(log_QUIESCE, &log->flag);
	TXN_WAKEUP(&log->syncरुको);
पूर्ण

/*
 *	jfs_sync(व्योम)
 *
 *	To be run as a kernel daemon.  This is awakened when tlocks run low.
 *	We ग_लिखो any inodes that have anonymous tlocks so they will become
 *	available.
 */
पूर्णांक jfs_sync(व्योम *arg)
अणु
	काष्ठा inode *ip;
	काष्ठा jfs_inode_info *jfs_ip;
	tid_t tid;

	करो अणु
		/*
		 * ग_लिखो each inode on the anonymous inode list
		 */
		TXN_LOCK();
		जबतक (jfs_tlocks_low && !list_empty(&TxAnchor.anon_list)) अणु
			jfs_ip = list_entry(TxAnchor.anon_list.next,
					    काष्ठा jfs_inode_info,
					    anon_inode_list);
			ip = &jfs_ip->vfs_inode;

			अगर (! igrab(ip)) अणु
				/*
				 * Inode is being मुक्तd
				 */
				list_del_init(&jfs_ip->anon_inode_list);
			पूर्ण अन्यथा अगर (mutex_trylock(&jfs_ip->commit_mutex)) अणु
				/*
				 * inode will be हटाओd from anonymous list
				 * when it is committed
				 */
				TXN_UNLOCK();
				tid = txBegin(ip->i_sb, COMMIT_INODE);
				txCommit(tid, 1, &ip, 0);
				txEnd(tid);
				mutex_unlock(&jfs_ip->commit_mutex);

				iput(ip);
				/*
				 * Just to be safe.  I करोn't know how
				 * दीर्घ we can run without blocking
				 */
				cond_resched();
				TXN_LOCK();
			पूर्ण अन्यथा अणु
				/* We can't get the commit mutex.  It may
				 * be held by a thपढ़ो रुकोing क्रम tlock's
				 * so let's not block here.  Save it to
				 * put back on the anon_list.
				 */

				/* Move from anon_list to anon_list2 */
				list_move(&jfs_ip->anon_inode_list,
					  &TxAnchor.anon_list2);

				TXN_UNLOCK();
				iput(ip);
				TXN_LOCK();
			पूर्ण
		पूर्ण
		/* Add anon_list2 back to anon_list */
		list_splice_init(&TxAnchor.anon_list2, &TxAnchor.anon_list);

		अगर (मुक्तzing(current)) अणु
			TXN_UNLOCK();
			try_to_मुक्तze();
		पूर्ण अन्यथा अणु
			set_current_state(TASK_INTERRUPTIBLE);
			TXN_UNLOCK();
			schedule();
		पूर्ण
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	jfs_info("jfs_sync being killed");
	वापस 0;
पूर्ण

#अगर defined(CONFIG_PROC_FS) && defined(CONFIG_JFS_DEBUG)
पूर्णांक jfs_txanchor_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर *मुक्तरुको;
	अक्षर *मुक्तlockरुको;
	अक्षर *lowlockरुको;

	मुक्तरुको =
	    रुकोqueue_active(&TxAnchor.मुक्तरुको) ? "active" : "empty";
	मुक्तlockरुको =
	    रुकोqueue_active(&TxAnchor.मुक्तlockरुको) ? "active" : "empty";
	lowlockरुको =
	    रुकोqueue_active(&TxAnchor.lowlockरुको) ? "active" : "empty";

	seq_म_लिखो(m,
		       "JFS TxAnchor\n"
		       "============\n"
		       "freetid = %d\n"
		       "freewait = %s\n"
		       "freelock = %d\n"
		       "freelockwait = %s\n"
		       "lowlockwait = %s\n"
		       "tlocksInUse = %d\n"
		       "jfs_tlocks_low = %d\n"
		       "unlock_queue is %sempty\n",
		       TxAnchor.मुक्तtid,
		       मुक्तरुको,
		       TxAnchor.मुक्तlock,
		       मुक्तlockरुको,
		       lowlockरुको,
		       TxAnchor.tlocksInUse,
		       jfs_tlocks_low,
		       list_empty(&TxAnchor.unlock_queue) ? "" : "not ");
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PROC_FS) && defined(CONFIG_JFS_STATISTICS)
पूर्णांक jfs_txstats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m,
		       "JFS TxStats\n"
		       "===========\n"
		       "calls to txBegin = %d\n"
		       "txBegin blocked by sync barrier = %d\n"
		       "txBegin blocked by tlocks low = %d\n"
		       "txBegin blocked by no free tid = %d\n"
		       "calls to txBeginAnon = %d\n"
		       "txBeginAnon blocked by sync barrier = %d\n"
		       "txBeginAnon blocked by tlocks low = %d\n"
		       "calls to txLockAlloc = %d\n"
		       "tLockAlloc blocked by no free lock = %d\n",
		       TxStat.txBegin,
		       TxStat.txBegin_barrier,
		       TxStat.txBegin_lockslow,
		       TxStat.txBegin_मुक्तtid,
		       TxStat.txBeginAnon,
		       TxStat.txBeginAnon_barrier,
		       TxStat.txBeginAnon_lockslow,
		       TxStat.txLockAlloc,
		       TxStat.txLockAlloc_मुक्तlock);
	वापस 0;
पूर्ण
#पूर्ण_अगर
