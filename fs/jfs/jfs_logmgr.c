<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

/*
 *	jfs_logmgr.c: log manager
 *
 * क्रम related inक्रमmation, see transaction manager (jfs_txnmgr.c), and
 * recovery manager (jfs_logreकरो.c).
 *
 * note: क्रम detail, RTFS.
 *
 *	log buffer manager:
 * special purpose buffer manager supporting log i/o requirements.
 * per log serial pageout of logpage
 * queuing i/o requests and redrive i/o at ioकरोne
 * मुख्यtain current logpage buffer
 * no caching since append only
 * appropriate jfs buffer cache buffers as needed
 *
 *	group commit:
 * transactions which wrote COMMIT records in the same in-memory
 * log page during the pageout of previous/current log page(s) are
 * committed together by the pageout of the page.
 *
 *	TBD lazy commit:
 * transactions are committed asynchronously when the log page
 * containing it COMMIT is paged out when it becomes full;
 *
 *	serialization:
 * . a per log lock serialize log ग_लिखो.
 * . a per log lock serialize group commit.
 * . a per log lock serialize log खोलो/बंद;
 *
 *	TBD log पूर्णांकegrity:
 * careful-ग_लिखो (ping-pong) of last logpage to recover from crash
 * in overग_लिखो.
 * detection of split (out-of-order) ग_लिखो of physical sectors
 * of last logpage via बारtamp at end of each sector
 * with its mirror data array at trailer).
 *
 *	alternatives:
 * lsn - 64-bit monotonically increasing पूर्णांकeger vs
 * 32-bit lspn and page eor.
 */

#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/buffer_head.h>		/* क्रम sync_blockdev() */
#समावेश <linux/bपन.स>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_txnmgr.h"
#समावेश "jfs_debug.h"


/*
 * lbuf's पढ़ोy to be redriven.  Protected by log_redrive_lock (jfsIO thपढ़ो)
 */
अटल काष्ठा lbuf *log_redrive_list;
अटल DEFINE_SPINLOCK(log_redrive_lock);


/*
 *	log पढ़ो/ग_लिखो serialization (per log)
 */
#घोषणा LOG_LOCK_INIT(log)	mutex_init(&(log)->loglock)
#घोषणा LOG_LOCK(log)		mutex_lock(&((log)->loglock))
#घोषणा LOG_UNLOCK(log)		mutex_unlock(&((log)->loglock))


/*
 *	log group commit serialization (per log)
 */

#घोषणा LOGGC_LOCK_INIT(log)	spin_lock_init(&(log)->gघड़ी)
#घोषणा LOGGC_LOCK(log)		spin_lock_irq(&(log)->gघड़ी)
#घोषणा LOGGC_UNLOCK(log)	spin_unlock_irq(&(log)->gघड़ी)
#घोषणा LOGGC_WAKEUP(tblk)	wake_up_all(&(tblk)->gcरुको)

/*
 *	log sync serialization (per log)
 */
#घोषणा	LOGSYNC_DELTA(logsize)		min((logsize)/8, 128*LOGPSIZE)
#घोषणा	LOGSYNC_BARRIER(logsize)	((logsize)/4)
/*
#घोषणा	LOGSYNC_DELTA(logsize)		min((logsize)/4, 256*LOGPSIZE)
#घोषणा	LOGSYNC_BARRIER(logsize)	((logsize)/2)
*/


/*
 *	log buffer cache synchronization
 */
अटल DEFINE_SPINLOCK(jfsLCacheLock);

#घोषणा	LCACHE_LOCK(flags)	spin_lock_irqsave(&jfsLCacheLock, flags)
#घोषणा	LCACHE_UNLOCK(flags)	spin_unlock_irqrestore(&jfsLCacheLock, flags)

/*
 * See __SLEEP_COND in jfs_locks.h
 */
#घोषणा LCACHE_SLEEP_COND(wq, cond, flags)	\
करो अणु						\
	अगर (cond)				\
		अवरोध;				\
	__SLEEP_COND(wq, cond, LCACHE_LOCK(flags), LCACHE_UNLOCK(flags)); \
पूर्ण जबतक (0)

#घोषणा	LCACHE_WAKEUP(event)	wake_up(event)


/*
 *	lbuf buffer cache (lCache) control
 */
/* log buffer manager pageout control (cumulative, inclusive) */
#घोषणा	lbmREAD		0x0001
#घोषणा	lbmWRITE	0x0002	/* enqueue at tail of ग_लिखो queue;
				 * init pageout अगर at head of queue;
				 */
#घोषणा	lbmRELEASE	0x0004	/* हटाओ from ग_लिखो queue
				 * at completion of pageout;
				 * करो not मुक्त/recycle it yet:
				 * caller will मुक्त it;
				 */
#घोषणा	lbmSYNC		0x0008	/* करो not वापस to मुक्तlist
				 * when हटाओd from ग_लिखो queue;
				 */
#घोषणा lbmFREE		0x0010	/* वापस to मुक्तlist
				 * at completion of pageout;
				 * the buffer may be recycled;
				 */
#घोषणा	lbmDONE		0x0020
#घोषणा	lbmERROR	0x0040
#घोषणा lbmGC		0x0080	/* lbmIODone to perक्रमm post-GC processing
				 * of log page
				 */
#घोषणा lbmसूचीECT	0x0100

/*
 * Global list of active बाह्यal journals
 */
अटल LIST_HEAD(jfs_बाह्यal_logs);
अटल काष्ठा jfs_log *dummy_log;
अटल DEFINE_MUTEX(jfs_log_mutex);

/*
 * क्रमward references
 */
अटल पूर्णांक lmWriteRecord(काष्ठा jfs_log * log, काष्ठा tblock * tblk,
			 काष्ठा lrd * lrd, काष्ठा tlock * tlck);

अटल पूर्णांक lmNextPage(काष्ठा jfs_log * log);
अटल पूर्णांक lmLogFileSystem(काष्ठा jfs_log * log, काष्ठा jfs_sb_info *sbi,
			   पूर्णांक activate);

अटल पूर्णांक खोलो_अंतरभूत_log(काष्ठा super_block *sb);
अटल पूर्णांक खोलो_dummy_log(काष्ठा super_block *sb);
अटल पूर्णांक lbmLogInit(काष्ठा jfs_log * log);
अटल व्योम lbmLogShutकरोwn(काष्ठा jfs_log * log);
अटल काष्ठा lbuf *lbmAllocate(काष्ठा jfs_log * log, पूर्णांक);
अटल व्योम lbmFree(काष्ठा lbuf * bp);
अटल व्योम lbmमुक्त(काष्ठा lbuf * bp);
अटल पूर्णांक lbmRead(काष्ठा jfs_log * log, पूर्णांक pn, काष्ठा lbuf ** bpp);
अटल व्योम lbmWrite(काष्ठा jfs_log * log, काष्ठा lbuf * bp, पूर्णांक flag, पूर्णांक cant_block);
अटल व्योम lbmDirectWrite(काष्ठा jfs_log * log, काष्ठा lbuf * bp, पूर्णांक flag);
अटल पूर्णांक lbmIOWait(काष्ठा lbuf * bp, पूर्णांक flag);
अटल bio_end_io_t lbmIODone;
अटल व्योम lbmStartIO(काष्ठा lbuf * bp);
अटल व्योम lmGCग_लिखो(काष्ठा jfs_log * log, पूर्णांक cant_block);
अटल पूर्णांक lmLogSync(काष्ठा jfs_log * log, पूर्णांक hard_sync);



/*
 *	statistics
 */
#अगर_घोषित CONFIG_JFS_STATISTICS
अटल काष्ठा lmStat अणु
	uपूर्णांक commit;		/* # of commit */
	uपूर्णांक pageकरोne;		/* # of page written */
	uपूर्णांक submitted;		/* # of pages submitted */
	uपूर्णांक full_page;		/* # of full pages submitted */
	uपूर्णांक partial_page;	/* # of partial pages submitted */
पूर्ण lmStat;
#पूर्ण_अगर

अटल व्योम ग_लिखो_special_inodes(काष्ठा jfs_log *log,
				 पूर्णांक (*ग_लिखोr)(काष्ठा address_space *))
अणु
	काष्ठा jfs_sb_info *sbi;

	list_क्रम_each_entry(sbi, &log->sb_list, log_list) अणु
		ग_लिखोr(sbi->ipbmap->i_mapping);
		ग_लिखोr(sbi->ipimap->i_mapping);
		ग_लिखोr(sbi->direct_inode->i_mapping);
	पूर्ण
पूर्ण

/*
 * NAME:	lmLog()
 *
 * FUNCTION:	ग_लिखो a log record;
 *
 * PARAMETER:
 *
 * RETURN:	lsn - offset to the next log record to ग_लिखो (end-of-log);
 *		-1  - error;
 *
 * note: toकरो: log error handler
 */
पूर्णांक lmLog(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
	  काष्ठा tlock * tlck)
अणु
	पूर्णांक lsn;
	पूर्णांक dअगरfp, dअगरft;
	काष्ठा metapage *mp = शून्य;
	अचिन्हित दीर्घ flags;

	jfs_info("lmLog: log:0x%p tblk:0x%p, lrd:0x%p tlck:0x%p",
		 log, tblk, lrd, tlck);

	LOG_LOCK(log);

	/* log by (out-of-transaction) JFS ? */
	अगर (tblk == शून्य)
		जाओ ग_लिखोRecord;

	/* log from page ? */
	अगर (tlck == शून्य ||
	    tlck->type & tlckBTROOT || (mp = tlck->mp) == शून्य)
		जाओ ग_लिखोRecord;

	/*
	 *	initialize/update page/transaction recovery lsn
	 */
	lsn = log->lsn;

	LOGSYNC_LOCK(log, flags);

	/*
	 * initialize page lsn अगर first log ग_लिखो of the page
	 */
	अगर (mp->lsn == 0) अणु
		mp->log = log;
		mp->lsn = lsn;
		log->count++;

		/* insert page at tail of logsynclist */
		list_add_tail(&mp->synclist, &log->synclist);
	पूर्ण

	/*
	 *	initialize/update lsn of tblock of the page
	 *
	 * transaction inherits oldest lsn of pages associated
	 * with allocation/deallocation of resources (their
	 * log records are used to reस्थिरruct allocation map
	 * at recovery समय: inode क्रम inode allocation map,
	 * B+-tree index of extent descriptors क्रम block
	 * allocation map);
	 * allocation map pages inherit transaction lsn at
	 * commit समय to allow क्रमwarding log syncpt past log
	 * records associated with allocation/deallocation of
	 * resources only after persistent map of these map pages
	 * have been updated and propagated to home.
	 */
	/*
	 * initialize transaction lsn:
	 */
	अगर (tblk->lsn == 0) अणु
		/* inherit lsn of its first page logged */
		tblk->lsn = mp->lsn;
		log->count++;

		/* insert tblock after the page on logsynclist */
		list_add(&tblk->synclist, &mp->synclist);
	पूर्ण
	/*
	 * update transaction lsn:
	 */
	अन्यथा अणु
		/* inherit oldest/smallest lsn of page */
		logdअगरf(dअगरfp, mp->lsn, log);
		logdअगरf(dअगरft, tblk->lsn, log);
		अगर (dअगरfp < dअगरft) अणु
			/* update tblock lsn with page lsn */
			tblk->lsn = mp->lsn;

			/* move tblock after page on logsynclist */
			list_move(&tblk->synclist, &mp->synclist);
		पूर्ण
	पूर्ण

	LOGSYNC_UNLOCK(log, flags);

	/*
	 *	ग_लिखो the log record
	 */
      ग_लिखोRecord:
	lsn = lmWriteRecord(log, tblk, lrd, tlck);

	/*
	 * क्रमward log syncpt अगर log reached next syncpt trigger
	 */
	logdअगरf(dअगरfp, lsn, log);
	अगर (dअगरfp >= log->nextsync)
		lsn = lmLogSync(log, 0);

	/* update end-of-log lsn */
	log->lsn = lsn;

	LOG_UNLOCK(log);

	/* वापस end-of-log address */
	वापस lsn;
पूर्ण

/*
 * NAME:	lmWriteRecord()
 *
 * FUNCTION:	move the log record to current log page
 *
 * PARAMETER:	cd	- commit descriptor
 *
 * RETURN:	end-of-log address
 *
 * serialization: LOG_LOCK() held on entry/निकास
 */
अटल पूर्णांक
lmWriteRecord(काष्ठा jfs_log * log, काष्ठा tblock * tblk, काष्ठा lrd * lrd,
	      काष्ठा tlock * tlck)
अणु
	पूर्णांक lsn = 0;		/* end-of-log address */
	काष्ठा lbuf *bp;	/* dst log page buffer */
	काष्ठा logpage *lp;	/* dst log page */
	caddr_t dst;		/* destination address in log page */
	पूर्णांक dstoffset;		/* end-of-log offset in log page */
	पूर्णांक मुक्तspace;		/* मुक्त space in log page */
	caddr_t p;		/* src meta-data page */
	caddr_t src;
	पूर्णांक srclen;
	पूर्णांक nbytes;		/* number of bytes to move */
	पूर्णांक i;
	पूर्णांक len;
	काष्ठा linelock *linelock;
	काष्ठा lv *lv;
	काष्ठा lvd *lvd;
	पूर्णांक l2linesize;

	len = 0;

	/* retrieve destination log page to ग_लिखो */
	bp = (काष्ठा lbuf *) log->bp;
	lp = (काष्ठा logpage *) bp->l_ldata;
	dstoffset = log->eor;

	/* any log data to ग_लिखो ? */
	अगर (tlck == शून्य)
		जाओ moveLrd;

	/*
	 *	move log record data
	 */
	/* retrieve source meta-data page to log */
	अगर (tlck->flag & tlckPAGELOCK) अणु
		p = (caddr_t) (tlck->mp->data);
		linelock = (काष्ठा linelock *) & tlck->lock;
	पूर्ण
	/* retrieve source in-memory inode to log */
	अन्यथा अगर (tlck->flag & tlckINODELOCK) अणु
		अगर (tlck->type & tlckDTREE)
			p = (caddr_t) &JFS_IP(tlck->ip)->i_dtroot;
		अन्यथा
			p = (caddr_t) &JFS_IP(tlck->ip)->i_xtroot;
		linelock = (काष्ठा linelock *) & tlck->lock;
	पूर्ण
#अगर_घोषित	_JFS_WIP
	अन्यथा अगर (tlck->flag & tlckINLINELOCK) अणु

		अंतरभूतlock = (काष्ठा अंतरभूतlock *) & tlck;
		p = (caddr_t) & अंतरभूतlock->pxd;
		linelock = (काष्ठा linelock *) & tlck;
	पूर्ण
#पूर्ण_अगर				/* _JFS_WIP */
	अन्यथा अणु
		jfs_err("lmWriteRecord: UFO tlck:0x%p", tlck);
		वापस 0;	/* Probably should trap */
	पूर्ण
	l2linesize = linelock->l2linesize;

      moveData:
	ASSERT(linelock->index <= linelock->maxcnt);

	lv = linelock->lv;
	क्रम (i = 0; i < linelock->index; i++, lv++) अणु
		अगर (lv->length == 0)
			जारी;

		/* is page full ? */
		अगर (dstoffset >= LOGPSIZE - LOGPTLRSIZE) अणु
			/* page become full: move on to next page */
			lmNextPage(log);

			bp = log->bp;
			lp = (काष्ठा logpage *) bp->l_ldata;
			dstoffset = LOGPHDRSIZE;
		पूर्ण

		/*
		 * move log vector data
		 */
		src = (u8 *) p + (lv->offset << l2linesize);
		srclen = lv->length << l2linesize;
		len += srclen;
		जबतक (srclen > 0) अणु
			मुक्तspace = (LOGPSIZE - LOGPTLRSIZE) - dstoffset;
			nbytes = min(मुक्तspace, srclen);
			dst = (caddr_t) lp + dstoffset;
			स_नकल(dst, src, nbytes);
			dstoffset += nbytes;

			/* is page not full ? */
			अगर (dstoffset < LOGPSIZE - LOGPTLRSIZE)
				अवरोध;

			/* page become full: move on to next page */
			lmNextPage(log);

			bp = (काष्ठा lbuf *) log->bp;
			lp = (काष्ठा logpage *) bp->l_ldata;
			dstoffset = LOGPHDRSIZE;

			srclen -= nbytes;
			src += nbytes;
		पूर्ण

		/*
		 * move log vector descriptor
		 */
		len += 4;
		lvd = (काष्ठा lvd *) ((caddr_t) lp + dstoffset);
		lvd->offset = cpu_to_le16(lv->offset);
		lvd->length = cpu_to_le16(lv->length);
		dstoffset += 4;
		jfs_info("lmWriteRecord: lv offset:%d length:%d",
			 lv->offset, lv->length);
	पूर्ण

	अगर ((i = linelock->next)) अणु
		linelock = (काष्ठा linelock *) lid_to_tlock(i);
		जाओ moveData;
	पूर्ण

	/*
	 *	move log record descriptor
	 */
      moveLrd:
	lrd->length = cpu_to_le16(len);

	src = (caddr_t) lrd;
	srclen = LOGRDSIZE;

	जबतक (srclen > 0) अणु
		मुक्तspace = (LOGPSIZE - LOGPTLRSIZE) - dstoffset;
		nbytes = min(मुक्तspace, srclen);
		dst = (caddr_t) lp + dstoffset;
		स_नकल(dst, src, nbytes);

		dstoffset += nbytes;
		srclen -= nbytes;

		/* are there more to move than मुक्तspace of page ? */
		अगर (srclen)
			जाओ pageFull;

		/*
		 * end of log record descriptor
		 */

		/* update last log record eor */
		log->eor = dstoffset;
		bp->l_eor = dstoffset;
		lsn = (log->page << L2LOGPSIZE) + dstoffset;

		अगर (lrd->type & cpu_to_le16(LOG_COMMIT)) अणु
			tblk->clsn = lsn;
			jfs_info("wr: tclsn:0x%x, beor:0x%x", tblk->clsn,
				 bp->l_eor);

			INCREMENT(lmStat.commit);	/* # of commit */

			/*
			 * enqueue tblock क्रम group commit:
			 *
			 * enqueue tblock of non-trivial/synchronous COMMIT
			 * at tail of group commit queue
			 * (trivial/asynchronous COMMITs are ignored by
			 * group commit.)
			 */
			LOGGC_LOCK(log);

			/* init tblock gc state */
			tblk->flag = tblkGC_QUEUE;
			tblk->bp = log->bp;
			tblk->pn = log->page;
			tblk->eor = log->eor;

			/* enqueue transaction to commit queue */
			list_add_tail(&tblk->cqueue, &log->cqueue);

			LOGGC_UNLOCK(log);
		पूर्ण

		jfs_info("lmWriteRecord: lrd:0x%04x bp:0x%p pn:%d eor:0x%x",
			le16_to_cpu(lrd->type), log->bp, log->page, dstoffset);

		/* page not full ? */
		अगर (dstoffset < LOGPSIZE - LOGPTLRSIZE)
			वापस lsn;

	      pageFull:
		/* page become full: move on to next page */
		lmNextPage(log);

		bp = (काष्ठा lbuf *) log->bp;
		lp = (काष्ठा logpage *) bp->l_ldata;
		dstoffset = LOGPHDRSIZE;
		src += nbytes;
	पूर्ण

	वापस lsn;
पूर्ण


/*
 * NAME:	lmNextPage()
 *
 * FUNCTION:	ग_लिखो current page and allocate next page.
 *
 * PARAMETER:	log
 *
 * RETURN:	0
 *
 * serialization: LOG_LOCK() held on entry/निकास
 */
अटल पूर्णांक lmNextPage(काष्ठा jfs_log * log)
अणु
	काष्ठा logpage *lp;
	पूर्णांक lspn;		/* log sequence page number */
	पूर्णांक pn;			/* current page number */
	काष्ठा lbuf *bp;
	काष्ठा lbuf *nextbp;
	काष्ठा tblock *tblk;

	/* get current log page number and log sequence page number */
	pn = log->page;
	bp = log->bp;
	lp = (काष्ठा logpage *) bp->l_ldata;
	lspn = le32_to_cpu(lp->h.page);

	LOGGC_LOCK(log);

	/*
	 *	ग_लिखो or queue the full page at the tail of ग_लिखो queue
	 */
	/* get the tail tblk on commit queue */
	अगर (list_empty(&log->cqueue))
		tblk = शून्य;
	अन्यथा
		tblk = list_entry(log->cqueue.prev, काष्ठा tblock, cqueue);

	/* every tblk who has COMMIT record on the current page,
	 * and has not been committed, must be on commit queue
	 * since tblk is queued at commit queueu at the समय
	 * of writing its COMMIT record on the page beक्रमe
	 * page becomes full (even though the tblk thपढ़ो
	 * who wrote COMMIT record may have been suspended
	 * currently);
	 */

	/* is page bound with outstanding tail tblk ? */
	अगर (tblk && tblk->pn == pn) अणु
		/* mark tblk क्रम end-of-page */
		tblk->flag |= tblkGC_EOP;

		अगर (log->cflag & logGC_PAGEOUT) अणु
			/* अगर page is not alपढ़ोy on ग_लिखो queue,
			 * just enqueue (no lbmWRITE to prevent redrive)
			 * buffer to wqueue to ensure correct serial order
			 * of the pages since log pages will be added
			 * continuously
			 */
			अगर (bp->l_wqnext == शून्य)
				lbmWrite(log, bp, 0, 0);
		पूर्ण अन्यथा अणु
			/*
			 * No current GC leader, initiate group commit
			 */
			log->cflag |= logGC_PAGEOUT;
			lmGCग_लिखो(log, 0);
		पूर्ण
	पूर्ण
	/* page is not bound with outstanding tblk:
	 * init ग_लिखो or mark it to be redriven (lbmWRITE)
	 */
	अन्यथा अणु
		/* finalize the page */
		bp->l_ceor = bp->l_eor;
		lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_ceor);
		lbmWrite(log, bp, lbmWRITE | lbmRELEASE | lbmFREE, 0);
	पूर्ण
	LOGGC_UNLOCK(log);

	/*
	 *	allocate/initialize next page
	 */
	/* अगर log wraps, the first data page of log is 2
	 * (0 never used, 1 is superblock).
	 */
	log->page = (pn == log->size - 1) ? 2 : pn + 1;
	log->eor = LOGPHDRSIZE;	/* ? valid page empty/full at logReकरो() */

	/* allocate/initialize next log page buffer */
	nextbp = lbmAllocate(log, log->page);
	nextbp->l_eor = log->eor;
	log->bp = nextbp;

	/* initialize next log page */
	lp = (काष्ठा logpage *) nextbp->l_ldata;
	lp->h.page = lp->t.page = cpu_to_le32(lspn + 1);
	lp->h.eor = lp->t.eor = cpu_to_le16(LOGPHDRSIZE);

	वापस 0;
पूर्ण


/*
 * NAME:	lmGroupCommit()
 *
 * FUNCTION:	group commit
 *	initiate pageout of the pages with COMMIT in the order of
 *	page number - redrive pageout of the page at the head of
 *	pageout queue until full page has been written.
 *
 * RETURN:
 *
 * NOTE:
 *	LOGGC_LOCK serializes log group commit queue, and
 *	transaction blocks on the commit queue.
 *	N.B. LOG_LOCK is NOT held during lmGroupCommit().
 */
पूर्णांक lmGroupCommit(काष्ठा jfs_log * log, काष्ठा tblock * tblk)
अणु
	पूर्णांक rc = 0;

	LOGGC_LOCK(log);

	/* group committed alपढ़ोy ? */
	अगर (tblk->flag & tblkGC_COMMITTED) अणु
		अगर (tblk->flag & tblkGC_ERROR)
			rc = -EIO;

		LOGGC_UNLOCK(log);
		वापस rc;
	पूर्ण
	jfs_info("lmGroup Commit: tblk = 0x%p, gcrtc = %d", tblk, log->gcrtc);

	अगर (tblk->xflag & COMMIT_LAZY)
		tblk->flag |= tblkGC_LAZY;

	अगर ((!(log->cflag & logGC_PAGEOUT)) && (!list_empty(&log->cqueue)) &&
	    (!(tblk->xflag & COMMIT_LAZY) || test_bit(log_FLUSH, &log->flag)
	     || jfs_tlocks_low)) अणु
		/*
		 * No pageout in progress
		 *
		 * start group commit as its group leader.
		 */
		log->cflag |= logGC_PAGEOUT;

		lmGCग_लिखो(log, 0);
	पूर्ण

	अगर (tblk->xflag & COMMIT_LAZY) अणु
		/*
		 * Lazy transactions can leave now
		 */
		LOGGC_UNLOCK(log);
		वापस 0;
	पूर्ण

	/* lmGCग_लिखो gives up LOGGC_LOCK, check again */

	अगर (tblk->flag & tblkGC_COMMITTED) अणु
		अगर (tblk->flag & tblkGC_ERROR)
			rc = -EIO;

		LOGGC_UNLOCK(log);
		वापस rc;
	पूर्ण

	/* upcount transaction रुकोing क्रम completion
	 */
	log->gcrtc++;
	tblk->flag |= tblkGC_READY;

	__SLEEP_COND(tblk->gcरुको, (tblk->flag & tblkGC_COMMITTED),
		     LOGGC_LOCK(log), LOGGC_UNLOCK(log));

	/* हटाओd from commit queue */
	अगर (tblk->flag & tblkGC_ERROR)
		rc = -EIO;

	LOGGC_UNLOCK(log);
	वापस rc;
पूर्ण

/*
 * NAME:	lmGCग_लिखो()
 *
 * FUNCTION:	group commit ग_लिखो
 *	initiate ग_लिखो of log page, building a group of all transactions
 *	with commit records on that page.
 *
 * RETURN:	None
 *
 * NOTE:
 *	LOGGC_LOCK must be held by caller.
 *	N.B. LOG_LOCK is NOT held during lmGroupCommit().
 */
अटल व्योम lmGCग_लिखो(काष्ठा jfs_log * log, पूर्णांक cant_ग_लिखो)
अणु
	काष्ठा lbuf *bp;
	काष्ठा logpage *lp;
	पूर्णांक gcpn;		/* group commit page number */
	काष्ठा tblock *tblk;
	काष्ठा tblock *xtblk = शून्य;

	/*
	 * build the commit group of a log page
	 *
	 * scan commit queue and make a commit group of all
	 * transactions with COMMIT records on the same log page.
	 */
	/* get the head tblk on the commit queue */
	gcpn = list_entry(log->cqueue.next, काष्ठा tblock, cqueue)->pn;

	list_क्रम_each_entry(tblk, &log->cqueue, cqueue) अणु
		अगर (tblk->pn != gcpn)
			अवरोध;

		xtblk = tblk;

		/* state transition: (QUEUE, READY) -> COMMIT */
		tblk->flag |= tblkGC_COMMIT;
	पूर्ण
	tblk = xtblk;		/* last tblk of the page */

	/*
	 * pageout to commit transactions on the log page.
	 */
	bp = (काष्ठा lbuf *) tblk->bp;
	lp = (काष्ठा logpage *) bp->l_ldata;
	/* is page alपढ़ोy full ? */
	अगर (tblk->flag & tblkGC_EOP) अणु
		/* mark page to मुक्त at end of group commit of the page */
		tblk->flag &= ~tblkGC_EOP;
		tblk->flag |= tblkGC_FREE;
		bp->l_ceor = bp->l_eor;
		lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_ceor);
		lbmWrite(log, bp, lbmWRITE | lbmRELEASE | lbmGC,
			 cant_ग_लिखो);
		INCREMENT(lmStat.full_page);
	पूर्ण
	/* page is not yet full */
	अन्यथा अणु
		bp->l_ceor = tblk->eor;	/* ? bp->l_ceor = bp->l_eor; */
		lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_ceor);
		lbmWrite(log, bp, lbmWRITE | lbmGC, cant_ग_लिखो);
		INCREMENT(lmStat.partial_page);
	पूर्ण
पूर्ण

/*
 * NAME:	lmPostGC()
 *
 * FUNCTION:	group commit post-processing
 *	Processes transactions after their commit records have been written
 *	to disk, redriving log I/O अगर necessary.
 *
 * RETURN:	None
 *
 * NOTE:
 *	This routine is called a पूर्णांकerrupt समय by lbmIODone
 */
अटल व्योम lmPostGC(काष्ठा lbuf * bp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा jfs_log *log = bp->l_log;
	काष्ठा logpage *lp;
	काष्ठा tblock *tblk, *temp;

	//LOGGC_LOCK(log);
	spin_lock_irqsave(&log->gघड़ी, flags);
	/*
	 * current pageout of group commit completed.
	 *
	 * हटाओ/wakeup transactions from commit queue who were
	 * group committed with the current log page
	 */
	list_क्रम_each_entry_safe(tblk, temp, &log->cqueue, cqueue) अणु
		अगर (!(tblk->flag & tblkGC_COMMIT))
			अवरोध;
		/* अगर transaction was marked GC_COMMIT then
		 * it has been shipped in the current pageout
		 * and made it to disk - it is committed.
		 */

		अगर (bp->l_flag & lbmERROR)
			tblk->flag |= tblkGC_ERROR;

		/* हटाओ it from the commit queue */
		list_del(&tblk->cqueue);
		tblk->flag &= ~tblkGC_QUEUE;

		अगर (tblk == log->flush_tblk) अणु
			/* we can stop flushing the log now */
			clear_bit(log_FLUSH, &log->flag);
			log->flush_tblk = शून्य;
		पूर्ण

		jfs_info("lmPostGC: tblk = 0x%p, flag = 0x%x", tblk,
			 tblk->flag);

		अगर (!(tblk->xflag & COMMIT_FORCE))
			/*
			 * Hand tblk over to lazy commit thपढ़ो
			 */
			txLazyUnlock(tblk);
		अन्यथा अणु
			/* state transition: COMMIT -> COMMITTED */
			tblk->flag |= tblkGC_COMMITTED;

			अगर (tblk->flag & tblkGC_READY)
				log->gcrtc--;

			LOGGC_WAKEUP(tblk);
		पूर्ण

		/* was page full beक्रमe pageout ?
		 * (and this is the last tblk bound with the page)
		 */
		अगर (tblk->flag & tblkGC_FREE)
			lbmFree(bp);
		/* did page become full after pageout ?
		 * (and this is the last tblk bound with the page)
		 */
		अन्यथा अगर (tblk->flag & tblkGC_EOP) अणु
			/* finalize the page */
			lp = (काष्ठा logpage *) bp->l_ldata;
			bp->l_ceor = bp->l_eor;
			lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_eor);
			jfs_info("lmPostGC: calling lbmWrite");
			lbmWrite(log, bp, lbmWRITE | lbmRELEASE | lbmFREE,
				 1);
		पूर्ण

	पूर्ण

	/* are there any transactions who have entered lnGroupCommit()
	 * (whose COMMITs are after that of the last log page written.
	 * They are रुकोing क्रम new group commit (above at (SLEEP 1))
	 * or lazy transactions are on a full (queued) log page,
	 * select the latest पढ़ोy transaction as new group leader and
	 * wake her up to lead her group.
	 */
	अगर ((!list_empty(&log->cqueue)) &&
	    ((log->gcrtc > 0) || (tblk->bp->l_wqnext != शून्य) ||
	     test_bit(log_FLUSH, &log->flag) || jfs_tlocks_low))
		/*
		 * Call lmGCग_लिखो with new group leader
		 */
		lmGCग_लिखो(log, 1);

	/* no transaction are पढ़ोy yet (transactions are only just
	 * queued (GC_QUEUE) and not entered क्रम group commit yet).
	 * the first transaction entering group commit
	 * will elect herself as new group leader.
	 */
	अन्यथा
		log->cflag &= ~logGC_PAGEOUT;

	//LOGGC_UNLOCK(log);
	spin_unlock_irqrestore(&log->gघड़ी, flags);
	वापस;
पूर्ण

/*
 * NAME:	lmLogSync()
 *
 * FUNCTION:	ग_लिखो log SYNCPT record क्रम specअगरied log
 *	अगर new sync address is available
 *	(normally the हाल अगर sync() is executed by back-ground
 *	process).
 *	calculate new value of i_nextsync which determines when
 *	this code is called again.
 *
 * PARAMETERS:	log	- log काष्ठाure
 *		hard_sync - 1 to क्रमce all metadata to be written
 *
 * RETURN:	0
 *
 * serialization: LOG_LOCK() held on entry/निकास
 */
अटल पूर्णांक lmLogSync(काष्ठा jfs_log * log, पूर्णांक hard_sync)
अणु
	पूर्णांक logsize;
	पूर्णांक written;		/* written since last syncpt */
	पूर्णांक मुक्त;		/* मुक्त space left available */
	पूर्णांक delta;		/* additional delta to ग_लिखो normally */
	पूर्णांक more;		/* additional ग_लिखो granted */
	काष्ठा lrd lrd;
	पूर्णांक lsn;
	काष्ठा logsyncblk *lp;
	अचिन्हित दीर्घ flags;

	/* push dirty metapages out to disk */
	अगर (hard_sync)
		ग_लिखो_special_inodes(log, filemap_fdataग_लिखो);
	अन्यथा
		ग_लिखो_special_inodes(log, filemap_flush);

	/*
	 *	क्रमward syncpt
	 */
	/* अगर last sync is same as last syncpt,
	 * invoke sync poपूर्णांक क्रमward processing to update sync.
	 */

	अगर (log->sync == log->syncpt) अणु
		LOGSYNC_LOCK(log, flags);
		अगर (list_empty(&log->synclist))
			log->sync = log->lsn;
		अन्यथा अणु
			lp = list_entry(log->synclist.next,
					काष्ठा logsyncblk, synclist);
			log->sync = lp->lsn;
		पूर्ण
		LOGSYNC_UNLOCK(log, flags);

	पूर्ण

	/* अगर sync is dअगरferent from last syncpt,
	 * ग_लिखो a SYNCPT record with syncpt = sync.
	 * reset syncpt = sync
	 */
	अगर (log->sync != log->syncpt) अणु
		lrd.logtid = 0;
		lrd.backchain = 0;
		lrd.type = cpu_to_le16(LOG_SYNCPT);
		lrd.length = 0;
		lrd.log.syncpt.sync = cpu_to_le32(log->sync);
		lsn = lmWriteRecord(log, शून्य, &lrd, शून्य);

		log->syncpt = log->sync;
	पूर्ण अन्यथा
		lsn = log->lsn;

	/*
	 *	setup next syncpt trigger (SWAG)
	 */
	logsize = log->logsize;

	logdअगरf(written, lsn, log);
	मुक्त = logsize - written;
	delta = LOGSYNC_DELTA(logsize);
	more = min(मुक्त / 2, delta);
	अगर (more < 2 * LOGPSIZE) अणु
		jfs_warn("\n ... Log Wrap ... Log Wrap ... Log Wrap ...\n");
		/*
		 *	log wrapping
		 *
		 * option 1 - panic ? No.!
		 * option 2 - shutकरोwn file प्रणालीs
		 *	      associated with log ?
		 * option 3 - extend log ?
		 * option 4 - second chance
		 *
		 * mark log wrapped, and जारी.
		 * when all active transactions are completed,
		 * mark log valid क्रम recovery.
		 * अगर crashed during invalid state, log state
		 * implies invalid log, क्रमcing fsck().
		 */
		/* mark log state log wrap in log superblock */
		/* log->state = LOGWRAP; */

		/* reset sync poपूर्णांक computation */
		log->syncpt = log->sync = lsn;
		log->nextsync = delta;
	पूर्ण अन्यथा
		/* next syncpt trigger = written + more */
		log->nextsync = written + more;

	/* अगर number of bytes written from last sync poपूर्णांक is more
	 * than 1/4 of the log size, stop new transactions from
	 * starting until all current transactions are completed
	 * by setting syncbarrier flag.
	 */
	अगर (!test_bit(log_SYNCBARRIER, &log->flag) &&
	    (written > LOGSYNC_BARRIER(logsize)) && log->active) अणु
		set_bit(log_SYNCBARRIER, &log->flag);
		jfs_info("log barrier on: lsn=0x%x syncpt=0x%x", lsn,
			 log->syncpt);
		/*
		 * We may have to initiate group commit
		 */
		jfs_flush_journal(log, 0);
	पूर्ण

	वापस lsn;
पूर्ण

/*
 * NAME:	jfs_syncpt
 *
 * FUNCTION:	ग_लिखो log SYNCPT record क्रम specअगरied log
 *
 * PARAMETERS:	log	  - log काष्ठाure
 *		hard_sync - set to 1 to क्रमce metadata to be written
 */
व्योम jfs_syncpt(काष्ठा jfs_log *log, पूर्णांक hard_sync)
अणु	LOG_LOCK(log);
	अगर (!test_bit(log_QUIESCE, &log->flag))
		lmLogSync(log, hard_sync);
	LOG_UNLOCK(log);
पूर्ण

/*
 * NAME:	lmLogOpen()
 *
 * FUNCTION:	खोलो the log on first खोलो;
 *	insert fileप्रणाली in the active list of the log.
 *
 * PARAMETER:	ipmnt	- file प्रणाली mount inode
 *		iplog	- log inode (out)
 *
 * RETURN:
 *
 * serialization:
 */
पूर्णांक lmLogOpen(काष्ठा super_block *sb)
अणु
	पूर्णांक rc;
	काष्ठा block_device *bdev;
	काष्ठा jfs_log *log;
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);

	अगर (sbi->flag & JFS_NOINTEGRITY)
		वापस खोलो_dummy_log(sb);

	अगर (sbi->mntflag & JFS_INLINELOG)
		वापस खोलो_अंतरभूत_log(sb);

	mutex_lock(&jfs_log_mutex);
	list_क्रम_each_entry(log, &jfs_बाह्यal_logs, journal_list) अणु
		अगर (log->bdev->bd_dev == sbi->logdev) अणु
			अगर (!uuid_equal(&log->uuid, &sbi->loguuid)) अणु
				jfs_warn("wrong uuid on JFS journal");
				mutex_unlock(&jfs_log_mutex);
				वापस -EINVAL;
			पूर्ण
			/*
			 * add file प्रणाली to log active file प्रणाली list
			 */
			अगर ((rc = lmLogFileSystem(log, sbi, 1))) अणु
				mutex_unlock(&jfs_log_mutex);
				वापस rc;
			पूर्ण
			जाओ journal_found;
		पूर्ण
	पूर्ण

	अगर (!(log = kzalloc(माप(काष्ठा jfs_log), GFP_KERNEL))) अणु
		mutex_unlock(&jfs_log_mutex);
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&log->sb_list);
	init_रुकोqueue_head(&log->syncरुको);

	/*
	 *	बाह्यal log as separate logical volume
	 *
	 * file प्रणालीs to log may have n-to-1 relationship;
	 */

	bdev = blkdev_get_by_dev(sbi->logdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL,
				 log);
	अगर (IS_ERR(bdev)) अणु
		rc = PTR_ERR(bdev);
		जाओ मुक्त;
	पूर्ण

	log->bdev = bdev;
	uuid_copy(&log->uuid, &sbi->loguuid);

	/*
	 * initialize log:
	 */
	अगर ((rc = lmLogInit(log)))
		जाओ बंद;

	list_add(&log->journal_list, &jfs_बाह्यal_logs);

	/*
	 * add file प्रणाली to log active file प्रणाली list
	 */
	अगर ((rc = lmLogFileSystem(log, sbi, 1)))
		जाओ shutकरोwn;

journal_found:
	LOG_LOCK(log);
	list_add(&sbi->log_list, &log->sb_list);
	sbi->log = log;
	LOG_UNLOCK(log);

	mutex_unlock(&jfs_log_mutex);
	वापस 0;

	/*
	 *	unwind on error
	 */
      shutकरोwn:		/* unwind lbmLogInit() */
	list_del(&log->journal_list);
	lbmLogShutकरोwn(log);

      बंद:		/* बंद बाह्यal log device */
	blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);

      मुक्त:		/* मुक्त log descriptor */
	mutex_unlock(&jfs_log_mutex);
	kमुक्त(log);

	jfs_warn("lmLogOpen: exit(%d)", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक खोलो_अंतरभूत_log(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_log *log;
	पूर्णांक rc;

	अगर (!(log = kzalloc(माप(काष्ठा jfs_log), GFP_KERNEL)))
		वापस -ENOMEM;
	INIT_LIST_HEAD(&log->sb_list);
	init_रुकोqueue_head(&log->syncरुको);

	set_bit(log_INLINELOG, &log->flag);
	log->bdev = sb->s_bdev;
	log->base = addressPXD(&JFS_SBI(sb)->logpxd);
	log->size = lengthPXD(&JFS_SBI(sb)->logpxd) >>
	    (L2LOGPSIZE - sb->s_blocksize_bits);
	log->l2bsize = sb->s_blocksize_bits;
	ASSERT(L2LOGPSIZE >= sb->s_blocksize_bits);

	/*
	 * initialize log.
	 */
	अगर ((rc = lmLogInit(log))) अणु
		kमुक्त(log);
		jfs_warn("lmLogOpen: exit(%d)", rc);
		वापस rc;
	पूर्ण

	list_add(&JFS_SBI(sb)->log_list, &log->sb_list);
	JFS_SBI(sb)->log = log;

	वापस rc;
पूर्ण

अटल पूर्णांक खोलो_dummy_log(काष्ठा super_block *sb)
अणु
	पूर्णांक rc;

	mutex_lock(&jfs_log_mutex);
	अगर (!dummy_log) अणु
		dummy_log = kzalloc(माप(काष्ठा jfs_log), GFP_KERNEL);
		अगर (!dummy_log) अणु
			mutex_unlock(&jfs_log_mutex);
			वापस -ENOMEM;
		पूर्ण
		INIT_LIST_HEAD(&dummy_log->sb_list);
		init_रुकोqueue_head(&dummy_log->syncरुको);
		dummy_log->no_पूर्णांकegrity = 1;
		/* Make up some stuff */
		dummy_log->base = 0;
		dummy_log->size = 1024;
		rc = lmLogInit(dummy_log);
		अगर (rc) अणु
			kमुक्त(dummy_log);
			dummy_log = शून्य;
			mutex_unlock(&jfs_log_mutex);
			वापस rc;
		पूर्ण
	पूर्ण

	LOG_LOCK(dummy_log);
	list_add(&JFS_SBI(sb)->log_list, &dummy_log->sb_list);
	JFS_SBI(sb)->log = dummy_log;
	LOG_UNLOCK(dummy_log);
	mutex_unlock(&jfs_log_mutex);

	वापस 0;
पूर्ण

/*
 * NAME:	lmLogInit()
 *
 * FUNCTION:	log initialization at first log खोलो.
 *
 *	logreकरो() (or logक्रमmat()) should have been run previously.
 *	initialize the log from log superblock.
 *	set the log state in the superblock to LOGMOUNT and
 *	ग_लिखो SYNCPT log record.
 *
 * PARAMETER:	log	- log काष्ठाure
 *
 * RETURN:	0	- अगर ok
 *		-EINVAL	- bad log magic number or superblock dirty
 *		error वापसed from logरुको()
 *
 * serialization: single first खोलो thपढ़ो
 */
पूर्णांक lmLogInit(काष्ठा jfs_log * log)
अणु
	पूर्णांक rc = 0;
	काष्ठा lrd lrd;
	काष्ठा logsuper *logsuper;
	काष्ठा lbuf *bpsuper;
	काष्ठा lbuf *bp;
	काष्ठा logpage *lp;
	पूर्णांक lsn = 0;

	jfs_info("lmLogInit: log:0x%p", log);

	/* initialize the group commit serialization lock */
	LOGGC_LOCK_INIT(log);

	/* allocate/initialize the log ग_लिखो serialization lock */
	LOG_LOCK_INIT(log);

	LOGSYNC_LOCK_INIT(log);

	INIT_LIST_HEAD(&log->synclist);

	INIT_LIST_HEAD(&log->cqueue);
	log->flush_tblk = शून्य;

	log->count = 0;

	/*
	 * initialize log i/o
	 */
	अगर ((rc = lbmLogInit(log)))
		वापस rc;

	अगर (!test_bit(log_INLINELOG, &log->flag))
		log->l2bsize = L2LOGPSIZE;

	/* check क्रम disabled journaling to disk */
	अगर (log->no_पूर्णांकegrity) अणु
		/*
		 * Journal pages will still be filled.  When the समय comes
		 * to actually करो the I/O, the ग_लिखो is not करोne, and the
		 * endio routine is called directly.
		 */
		bp = lbmAllocate(log , 0);
		log->bp = bp;
		bp->l_pn = bp->l_eor = 0;
	पूर्ण अन्यथा अणु
		/*
		 * validate log superblock
		 */
		अगर ((rc = lbmRead(log, 1, &bpsuper)))
			जाओ errout10;

		logsuper = (काष्ठा logsuper *) bpsuper->l_ldata;

		अगर (logsuper->magic != cpu_to_le32(LOGMAGIC)) अणु
			jfs_warn("*** Log Format Error ! ***");
			rc = -EINVAL;
			जाओ errout20;
		पूर्ण

		/* logreकरो() should have been run successfully. */
		अगर (logsuper->state != cpu_to_le32(LOGREDONE)) अणु
			jfs_warn("*** Log Is Dirty ! ***");
			rc = -EINVAL;
			जाओ errout20;
		पूर्ण

		/* initialize log from log superblock */
		अगर (test_bit(log_INLINELOG,&log->flag)) अणु
			अगर (log->size != le32_to_cpu(logsuper->size)) अणु
				rc = -EINVAL;
				जाओ errout20;
			पूर्ण
			jfs_info("lmLogInit: inline log:0x%p base:0x%Lx size:0x%x",
				 log, (अचिन्हित दीर्घ दीर्घ)log->base, log->size);
		पूर्ण अन्यथा अणु
			अगर (!uuid_equal(&logsuper->uuid, &log->uuid)) अणु
				jfs_warn("wrong uuid on JFS log device");
				जाओ errout20;
			पूर्ण
			log->size = le32_to_cpu(logsuper->size);
			log->l2bsize = le32_to_cpu(logsuper->l2bsize);
			jfs_info("lmLogInit: external log:0x%p base:0x%Lx size:0x%x",
				 log, (अचिन्हित दीर्घ दीर्घ)log->base, log->size);
		पूर्ण

		log->page = le32_to_cpu(logsuper->end) / LOGPSIZE;
		log->eor = le32_to_cpu(logsuper->end) - (LOGPSIZE * log->page);

		/*
		 * initialize क्रम log append ग_लिखो mode
		 */
		/* establish current/end-of-log page/buffer */
		अगर ((rc = lbmRead(log, log->page, &bp)))
			जाओ errout20;

		lp = (काष्ठा logpage *) bp->l_ldata;

		jfs_info("lmLogInit: lsn:0x%x page:%d eor:%d:%d",
			 le32_to_cpu(logsuper->end), log->page, log->eor,
			 le16_to_cpu(lp->h.eor));

		log->bp = bp;
		bp->l_pn = log->page;
		bp->l_eor = log->eor;

		/* अगर current page is full, move on to next page */
		अगर (log->eor >= LOGPSIZE - LOGPTLRSIZE)
			lmNextPage(log);

		/*
		 * initialize log syncpoपूर्णांक
		 */
		/*
		 * ग_लिखो the first SYNCPT record with syncpoपूर्णांक = 0
		 * (i.e., log reकरो up to HERE !);
		 * हटाओ current page from lbm ग_लिखो queue at end of pageout
		 * (to ग_लिखो log superblock update), but करो not release to
		 * मुक्तlist;
		 */
		lrd.logtid = 0;
		lrd.backchain = 0;
		lrd.type = cpu_to_le16(LOG_SYNCPT);
		lrd.length = 0;
		lrd.log.syncpt.sync = 0;
		lsn = lmWriteRecord(log, शून्य, &lrd, शून्य);
		bp = log->bp;
		bp->l_ceor = bp->l_eor;
		lp = (काष्ठा logpage *) bp->l_ldata;
		lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_eor);
		lbmWrite(log, bp, lbmWRITE | lbmSYNC, 0);
		अगर ((rc = lbmIOWait(bp, 0)))
			जाओ errout30;

		/*
		 * update/ग_लिखो superblock
		 */
		logsuper->state = cpu_to_le32(LOGMOUNT);
		log->serial = le32_to_cpu(logsuper->serial) + 1;
		logsuper->serial = cpu_to_le32(log->serial);
		lbmDirectWrite(log, bpsuper, lbmWRITE | lbmRELEASE | lbmSYNC);
		अगर ((rc = lbmIOWait(bpsuper, lbmFREE)))
			जाओ errout30;
	पूर्ण

	/* initialize logsync parameters */
	log->logsize = (log->size - 2) << L2LOGPSIZE;
	log->lsn = lsn;
	log->syncpt = lsn;
	log->sync = log->syncpt;
	log->nextsync = LOGSYNC_DELTA(log->logsize);

	jfs_info("lmLogInit: lsn:0x%x syncpt:0x%x sync:0x%x",
		 log->lsn, log->syncpt, log->sync);

	/*
	 * initialize क्रम lazy/group commit
	 */
	log->clsn = lsn;

	वापस 0;

	/*
	 *	unwind on error
	 */
      errout30:		/* release log page */
	log->wqueue = शून्य;
	bp->l_wqnext = शून्य;
	lbmFree(bp);

      errout20:		/* release log superblock */
	lbmFree(bpsuper);

      errout10:		/* unwind lbmLogInit() */
	lbmLogShutकरोwn(log);

	jfs_warn("lmLogInit: exit(%d)", rc);
	वापस rc;
पूर्ण


/*
 * NAME:	lmLogClose()
 *
 * FUNCTION:	हटाओ file प्रणाली <ipmnt> from active list of log <iplog>
 *		and बंद it on last बंद.
 *
 * PARAMETER:	sb	- superblock
 *
 * RETURN:	errors from subroutines
 *
 * serialization:
 */
पूर्णांक lmLogClose(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा jfs_log *log = sbi->log;
	काष्ठा block_device *bdev;
	पूर्णांक rc = 0;

	jfs_info("lmLogClose: log:0x%p", log);

	mutex_lock(&jfs_log_mutex);
	LOG_LOCK(log);
	list_del(&sbi->log_list);
	LOG_UNLOCK(log);
	sbi->log = शून्य;

	/*
	 * We need to make sure all of the "written" metapages
	 * actually make it to disk
	 */
	sync_blockdev(sb->s_bdev);

	अगर (test_bit(log_INLINELOG, &log->flag)) अणु
		/*
		 *	in-line log in host file प्रणाली
		 */
		rc = lmLogShutकरोwn(log);
		kमुक्त(log);
		जाओ out;
	पूर्ण

	अगर (!log->no_पूर्णांकegrity)
		lmLogFileSystem(log, sbi, 0);

	अगर (!list_empty(&log->sb_list))
		जाओ out;

	/*
	 * TODO: ensure that the dummy_log is in a state to allow
	 * lbmLogShutकरोwn to deallocate all the buffers and call
	 * kमुक्त against dummy_log.  For now, leave dummy_log & its
	 * buffers in memory, and resuse अगर another no-पूर्णांकegrity mount
	 * is requested.
	 */
	अगर (log->no_पूर्णांकegrity)
		जाओ out;

	/*
	 *	बाह्यal log as separate logical volume
	 */
	list_del(&log->journal_list);
	bdev = log->bdev;
	rc = lmLogShutकरोwn(log);

	blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);

	kमुक्त(log);

      out:
	mutex_unlock(&jfs_log_mutex);
	jfs_info("lmLogClose: exit(%d)", rc);
	वापस rc;
पूर्ण


/*
 * NAME:	jfs_flush_journal()
 *
 * FUNCTION:	initiate ग_लिखो of any outstanding transactions to the journal
 *		and optionally रुको until they are all written to disk
 *
 *		रुको == 0  flush until latest txn is committed, करोn't रुको
 *		रुको == 1  flush until latest txn is committed, रुको
 *		रुको > 1   flush until all txn's are complete, रुको
 */
व्योम jfs_flush_journal(काष्ठा jfs_log *log, पूर्णांक रुको)
अणु
	पूर्णांक i;
	काष्ठा tblock *target = शून्य;

	/* jfs_ग_लिखो_inode may call us during पढ़ो-only mount */
	अगर (!log)
		वापस;

	jfs_info("jfs_flush_journal: log:0x%p wait=%d", log, रुको);

	LOGGC_LOCK(log);

	अगर (!list_empty(&log->cqueue)) अणु
		/*
		 * This ensures that we will keep writing to the journal as दीर्घ
		 * as there are unwritten commit records
		 */
		target = list_entry(log->cqueue.prev, काष्ठा tblock, cqueue);

		अगर (test_bit(log_FLUSH, &log->flag)) अणु
			/*
			 * We're alपढ़ोy flushing.
			 * अगर flush_tblk is शून्य, we are flushing everything,
			 * so leave it that way.  Otherwise, update it to the
			 * latest transaction
			 */
			अगर (log->flush_tblk)
				log->flush_tblk = target;
		पूर्ण अन्यथा अणु
			/* Only flush until latest transaction is committed */
			log->flush_tblk = target;
			set_bit(log_FLUSH, &log->flag);

			/*
			 * Initiate I/O on outstanding transactions
			 */
			अगर (!(log->cflag & logGC_PAGEOUT)) अणु
				log->cflag |= logGC_PAGEOUT;
				lmGCग_लिखो(log, 0);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((रुको > 1) || test_bit(log_SYNCBARRIER, &log->flag)) अणु
		/* Flush until all activity complete */
		set_bit(log_FLUSH, &log->flag);
		log->flush_tblk = शून्य;
	पूर्ण

	अगर (रुको && target && !(target->flag & tblkGC_COMMITTED)) अणु
		DECLARE_WAITQUEUE(__रुको, current);

		add_रुको_queue(&target->gcरुको, &__रुको);
		set_current_state(TASK_UNINTERRUPTIBLE);
		LOGGC_UNLOCK(log);
		schedule();
		LOGGC_LOCK(log);
		हटाओ_रुको_queue(&target->gcरुको, &__रुको);
	पूर्ण
	LOGGC_UNLOCK(log);

	अगर (रुको < 2)
		वापस;

	ग_लिखो_special_inodes(log, filemap_fdataग_लिखो);

	/*
	 * If there was recent activity, we may need to रुको
	 * क्रम the lazycommit thपढ़ो to catch up
	 */
	अगर ((!list_empty(&log->cqueue)) || !list_empty(&log->synclist)) अणु
		क्रम (i = 0; i < 200; i++) अणु	/* Too much? */
			msleep(250);
			ग_लिखो_special_inodes(log, filemap_fdataग_लिखो);
			अगर (list_empty(&log->cqueue) &&
			    list_empty(&log->synclist))
				अवरोध;
		पूर्ण
	पूर्ण
	निश्चित(list_empty(&log->cqueue));

#अगर_घोषित CONFIG_JFS_DEBUG
	अगर (!list_empty(&log->synclist)) अणु
		काष्ठा logsyncblk *lp;

		prपूर्णांकk(KERN_ERR "jfs_flush_journal: synclist not empty\n");
		list_क्रम_each_entry(lp, &log->synclist, synclist) अणु
			अगर (lp->xflag & COMMIT_PAGE) अणु
				काष्ठा metapage *mp = (काष्ठा metapage *)lp;
				prपूर्णांक_hex_dump(KERN_ERR, "metapage: ",
					       DUMP_PREFIX_ADDRESS, 16, 4,
					       mp, माप(काष्ठा metapage), 0);
				prपूर्णांक_hex_dump(KERN_ERR, "page: ",
					       DUMP_PREFIX_ADDRESS, 16,
					       माप(दीर्घ), mp->page,
					       माप(काष्ठा page), 0);
			पूर्ण अन्यथा
				prपूर्णांक_hex_dump(KERN_ERR, "tblock:",
					       DUMP_PREFIX_ADDRESS, 16, 4,
					       lp, माप(काष्ठा tblock), 0);
		पूर्ण
	पूर्ण
#अन्यथा
	WARN_ON(!list_empty(&log->synclist));
#पूर्ण_अगर
	clear_bit(log_FLUSH, &log->flag);
पूर्ण

/*
 * NAME:	lmLogShutकरोwn()
 *
 * FUNCTION:	log shutकरोwn at last LogClose().
 *
 *		ग_लिखो log syncpt record.
 *		update super block to set reकरोne flag to 0.
 *
 * PARAMETER:	log	- log inode
 *
 * RETURN:	0	- success
 *
 * serialization: single last बंद thपढ़ो
 */
पूर्णांक lmLogShutकरोwn(काष्ठा jfs_log * log)
अणु
	पूर्णांक rc;
	काष्ठा lrd lrd;
	पूर्णांक lsn;
	काष्ठा logsuper *logsuper;
	काष्ठा lbuf *bpsuper;
	काष्ठा lbuf *bp;
	काष्ठा logpage *lp;

	jfs_info("lmLogShutdown: log:0x%p", log);

	jfs_flush_journal(log, 2);

	/*
	 * ग_लिखो the last SYNCPT record with syncpoपूर्णांक = 0
	 * (i.e., log reकरो up to HERE !)
	 */
	lrd.logtid = 0;
	lrd.backchain = 0;
	lrd.type = cpu_to_le16(LOG_SYNCPT);
	lrd.length = 0;
	lrd.log.syncpt.sync = 0;

	lsn = lmWriteRecord(log, शून्य, &lrd, शून्य);
	bp = log->bp;
	lp = (काष्ठा logpage *) bp->l_ldata;
	lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_eor);
	lbmWrite(log, log->bp, lbmWRITE | lbmRELEASE | lbmSYNC, 0);
	lbmIOWait(log->bp, lbmFREE);
	log->bp = शून्य;

	/*
	 * synchronous update log superblock
	 * mark log state as shutकरोwn cleanly
	 * (i.e., Log करोes not need to be replayed).
	 */
	अगर ((rc = lbmRead(log, 1, &bpsuper)))
		जाओ out;

	logsuper = (काष्ठा logsuper *) bpsuper->l_ldata;
	logsuper->state = cpu_to_le32(LOGREDONE);
	logsuper->end = cpu_to_le32(lsn);
	lbmDirectWrite(log, bpsuper, lbmWRITE | lbmRELEASE | lbmSYNC);
	rc = lbmIOWait(bpsuper, lbmFREE);

	jfs_info("lmLogShutdown: lsn:0x%x page:%d eor:%d",
		 lsn, log->page, log->eor);

      out:
	/*
	 * shutकरोwn per log i/o
	 */
	lbmLogShutकरोwn(log);

	अगर (rc) अणु
		jfs_warn("lmLogShutdown: exit(%d)", rc);
	पूर्ण
	वापस rc;
पूर्ण


/*
 * NAME:	lmLogFileSystem()
 *
 * FUNCTION:	insert (<activate> = true)/हटाओ (<activate> = false)
 *	file प्रणाली पूर्णांकo/from log active file प्रणाली list.
 *
 * PARAMETE:	log	- poपूर्णांकer to logs inode.
 *		fsdev	- kdev_t of fileप्रणाली.
 *		serial	- poपूर्णांकer to वापसed log serial number
 *		activate - insert/हटाओ device from active list.
 *
 * RETURN:	0	- success
 *		errors वापसed by vms_ioरुको().
 */
अटल पूर्णांक lmLogFileSystem(काष्ठा jfs_log * log, काष्ठा jfs_sb_info *sbi,
			   पूर्णांक activate)
अणु
	पूर्णांक rc = 0;
	पूर्णांक i;
	काष्ठा logsuper *logsuper;
	काष्ठा lbuf *bpsuper;
	uuid_t *uuid = &sbi->uuid;

	/*
	 * insert/हटाओ file प्रणाली device to log active file प्रणाली list.
	 */
	अगर ((rc = lbmRead(log, 1, &bpsuper)))
		वापस rc;

	logsuper = (काष्ठा logsuper *) bpsuper->l_ldata;
	अगर (activate) अणु
		क्रम (i = 0; i < MAX_ACTIVE; i++)
			अगर (uuid_is_null(&logsuper->active[i].uuid)) अणु
				uuid_copy(&logsuper->active[i].uuid, uuid);
				sbi->aggregate = i;
				अवरोध;
			पूर्ण
		अगर (i == MAX_ACTIVE) अणु
			jfs_warn("Too many file systems sharing journal!");
			lbmFree(bpsuper);
			वापस -EMखाता;	/* Is there a better rc? */
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < MAX_ACTIVE; i++)
			अगर (uuid_equal(&logsuper->active[i].uuid, uuid)) अणु
				uuid_copy(&logsuper->active[i].uuid,
					  &uuid_null);
				अवरोध;
			पूर्ण
		अगर (i == MAX_ACTIVE) अणु
			jfs_warn("Somebody stomped on the journal!");
			lbmFree(bpsuper);
			वापस -EIO;
		पूर्ण

	पूर्ण

	/*
	 * synchronous ग_लिखो log superblock:
	 *
	 * ग_लिखो sidestream bypassing ग_लिखो queue:
	 * at file प्रणाली mount, log super block is updated क्रम
	 * activation of the file प्रणाली beक्रमe any log record
	 * (MOUNT record) of the file प्रणाली, and at file प्रणाली
	 * unmount, all meta data क्रम the file प्रणाली has been
	 * flushed beक्रमe log super block is updated क्रम deactivation
	 * of the file प्रणाली.
	 */
	lbmDirectWrite(log, bpsuper, lbmWRITE | lbmRELEASE | lbmSYNC);
	rc = lbmIOWait(bpsuper, lbmFREE);

	वापस rc;
पूर्ण

/*
 *		log buffer manager (lbm)
 *		------------------------
 *
 * special purpose buffer manager supporting log i/o requirements.
 *
 * per log ग_लिखो queue:
 * log pageout occurs in serial order by fअगरo ग_लिखो queue and
 * restricting to a single i/o in pregress at any one समय.
 * a circular singly-linked list
 * (log->wrqueue poपूर्णांकs to the tail, and buffers are linked via
 * bp->wrqueue field), and
 * मुख्यtains log page in pageout ot रुकोing क्रम pageout in serial pageout.
 */

/*
 *	lbmLogInit()
 *
 * initialize per log I/O setup at lmLogInit()
 */
अटल पूर्णांक lbmLogInit(काष्ठा jfs_log * log)
अणु				/* log inode */
	पूर्णांक i;
	काष्ठा lbuf *lbuf;

	jfs_info("lbmLogInit: log:0x%p", log);

	/* initialize current buffer cursor */
	log->bp = शून्य;

	/* initialize log device ग_लिखो queue */
	log->wqueue = शून्य;

	/*
	 * Each log has its own buffer pages allocated to it.  These are
	 * not managed by the page cache.  This ensures that a transaction
	 * writing to the log करोes not block trying to allocate a page from
	 * the page cache (क्रम the log).  This would be bad, since page
	 * allocation रुकोs on the kswapd thपढ़ो that may be committing inodes
	 * which would cause log activity.  Was that clear?  I'm trying to
	 * aव्योम deadlock here.
	 */
	init_रुकोqueue_head(&log->मुक्त_रुको);

	log->lbuf_मुक्त = शून्य;

	क्रम (i = 0; i < LOGPAGES;) अणु
		अक्षर *buffer;
		uपूर्णांक offset;
		काष्ठा page *page = alloc_page(GFP_KERNEL | __GFP_ZERO);

		अगर (!page)
			जाओ error;
		buffer = page_address(page);
		क्रम (offset = 0; offset < PAGE_SIZE; offset += LOGPSIZE) अणु
			lbuf = kदो_स्मृति(माप(काष्ठा lbuf), GFP_KERNEL);
			अगर (lbuf == शून्य) अणु
				अगर (offset == 0)
					__मुक्त_page(page);
				जाओ error;
			पूर्ण
			अगर (offset) /* we alपढ़ोy have one reference */
				get_page(page);
			lbuf->l_offset = offset;
			lbuf->l_ldata = buffer + offset;
			lbuf->l_page = page;
			lbuf->l_log = log;
			init_रुकोqueue_head(&lbuf->l_ioevent);

			lbuf->l_मुक्तlist = log->lbuf_मुक्त;
			log->lbuf_मुक्त = lbuf;
			i++;
		पूर्ण
	पूर्ण

	वापस (0);

      error:
	lbmLogShutकरोwn(log);
	वापस -ENOMEM;
पूर्ण


/*
 *	lbmLogShutकरोwn()
 *
 * finalize per log I/O setup at lmLogShutकरोwn()
 */
अटल व्योम lbmLogShutकरोwn(काष्ठा jfs_log * log)
अणु
	काष्ठा lbuf *lbuf;

	jfs_info("lbmLogShutdown: log:0x%p", log);

	lbuf = log->lbuf_मुक्त;
	जबतक (lbuf) अणु
		काष्ठा lbuf *next = lbuf->l_मुक्तlist;
		__मुक्त_page(lbuf->l_page);
		kमुक्त(lbuf);
		lbuf = next;
	पूर्ण
पूर्ण


/*
 *	lbmAllocate()
 *
 * allocate an empty log buffer
 */
अटल काष्ठा lbuf *lbmAllocate(काष्ठा jfs_log * log, पूर्णांक pn)
अणु
	काष्ठा lbuf *bp;
	अचिन्हित दीर्घ flags;

	/*
	 * recycle from log buffer मुक्तlist अगर any
	 */
	LCACHE_LOCK(flags);
	LCACHE_SLEEP_COND(log->मुक्त_रुको, (bp = log->lbuf_मुक्त), flags);
	log->lbuf_मुक्त = bp->l_मुक्तlist;
	LCACHE_UNLOCK(flags);

	bp->l_flag = 0;

	bp->l_wqnext = शून्य;
	bp->l_मुक्तlist = शून्य;

	bp->l_pn = pn;
	bp->l_blkno = log->base + (pn << (L2LOGPSIZE - log->l2bsize));
	bp->l_ceor = 0;

	वापस bp;
पूर्ण


/*
 *	lbmFree()
 *
 * release a log buffer to मुक्तlist
 */
अटल व्योम lbmFree(काष्ठा lbuf * bp)
अणु
	अचिन्हित दीर्घ flags;

	LCACHE_LOCK(flags);

	lbmमुक्त(bp);

	LCACHE_UNLOCK(flags);
पूर्ण

अटल व्योम lbmमुक्त(काष्ठा lbuf * bp)
अणु
	काष्ठा jfs_log *log = bp->l_log;

	निश्चित(bp->l_wqnext == शून्य);

	/*
	 * वापस the buffer to head of मुक्तlist
	 */
	bp->l_मुक्तlist = log->lbuf_मुक्त;
	log->lbuf_मुक्त = bp;

	wake_up(&log->मुक्त_रुको);
	वापस;
पूर्ण


/*
 * NAME:	lbmRedrive
 *
 * FUNCTION:	add a log buffer to the log redrive list
 *
 * PARAMETER:
 *	bp	- log buffer
 *
 * NOTES:
 *	Takes log_redrive_lock.
 */
अटल अंतरभूत व्योम lbmRedrive(काष्ठा lbuf *bp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&log_redrive_lock, flags);
	bp->l_redrive_next = log_redrive_list;
	log_redrive_list = bp;
	spin_unlock_irqrestore(&log_redrive_lock, flags);

	wake_up_process(jfsIOthपढ़ो);
पूर्ण


/*
 *	lbmRead()
 */
अटल पूर्णांक lbmRead(काष्ठा jfs_log * log, पूर्णांक pn, काष्ठा lbuf ** bpp)
अणु
	काष्ठा bio *bio;
	काष्ठा lbuf *bp;

	/*
	 * allocate a log buffer
	 */
	*bpp = bp = lbmAllocate(log, pn);
	jfs_info("lbmRead: bp:0x%p pn:0x%x", bp, pn);

	bp->l_flag |= lbmREAD;

	bio = bio_alloc(GFP_NOFS, 1);

	bio->bi_iter.bi_sector = bp->l_blkno << (log->l2bsize - 9);
	bio_set_dev(bio, log->bdev);

	bio_add_page(bio, bp->l_page, LOGPSIZE, bp->l_offset);
	BUG_ON(bio->bi_iter.bi_size != LOGPSIZE);

	bio->bi_end_io = lbmIODone;
	bio->bi_निजी = bp;
	bio->bi_opf = REQ_OP_READ;
	/*check अगर journaling to disk has been disabled*/
	अगर (log->no_पूर्णांकegrity) अणु
		bio->bi_iter.bi_size = 0;
		lbmIODone(bio);
	पूर्ण अन्यथा अणु
		submit_bio(bio);
	पूर्ण

	रुको_event(bp->l_ioevent, (bp->l_flag != lbmREAD));

	वापस 0;
पूर्ण


/*
 *	lbmWrite()
 *
 * buffer at head of pageout queue stays after completion of
 * partial-page pageout and redriven by explicit initiation of
 * pageout by caller until full-page pageout is completed and
 * released.
 *
 * device driver i/o करोne redrives pageout of new buffer at
 * head of pageout queue when current buffer at head of pageout
 * queue is released at the completion of its full-page pageout.
 *
 * LOGGC_LOCK() serializes lbmWrite() by lmNextPage() and lmGroupCommit().
 * LCACHE_LOCK() serializes xflag between lbmWrite() and lbmIODone()
 */
अटल व्योम lbmWrite(काष्ठा jfs_log * log, काष्ठा lbuf * bp, पूर्णांक flag,
		     पूर्णांक cant_block)
अणु
	काष्ठा lbuf *tail;
	अचिन्हित दीर्घ flags;

	jfs_info("lbmWrite: bp:0x%p flag:0x%x pn:0x%x", bp, flag, bp->l_pn);

	/* map the logical block address to physical block address */
	bp->l_blkno =
	    log->base + (bp->l_pn << (L2LOGPSIZE - log->l2bsize));

	LCACHE_LOCK(flags);		/* disable+lock */

	/*
	 * initialize buffer क्रम device driver
	 */
	bp->l_flag = flag;

	/*
	 *	insert bp at tail of ग_लिखो queue associated with log
	 *
	 * (request is either क्रम bp alपढ़ोy/currently at head of queue
	 * or new bp to be inserted at tail)
	 */
	tail = log->wqueue;

	/* is buffer not alपढ़ोy on ग_लिखो queue ? */
	अगर (bp->l_wqnext == शून्य) अणु
		/* insert at tail of wqueue */
		अगर (tail == शून्य) अणु
			log->wqueue = bp;
			bp->l_wqnext = bp;
		पूर्ण अन्यथा अणु
			log->wqueue = bp;
			bp->l_wqnext = tail->l_wqnext;
			tail->l_wqnext = bp;
		पूर्ण

		tail = bp;
	पूर्ण

	/* is buffer at head of wqueue and क्रम ग_लिखो ? */
	अगर ((bp != tail->l_wqnext) || !(flag & lbmWRITE)) अणु
		LCACHE_UNLOCK(flags);	/* unlock+enable */
		वापस;
	पूर्ण

	LCACHE_UNLOCK(flags);	/* unlock+enable */

	अगर (cant_block)
		lbmRedrive(bp);
	अन्यथा अगर (flag & lbmSYNC)
		lbmStartIO(bp);
	अन्यथा अणु
		LOGGC_UNLOCK(log);
		lbmStartIO(bp);
		LOGGC_LOCK(log);
	पूर्ण
पूर्ण


/*
 *	lbmDirectWrite()
 *
 * initiate pageout bypassing ग_लिखो queue क्रम sidestream
 * (e.g., log superblock) ग_लिखो;
 */
अटल व्योम lbmDirectWrite(काष्ठा jfs_log * log, काष्ठा lbuf * bp, पूर्णांक flag)
अणु
	jfs_info("lbmDirectWrite: bp:0x%p flag:0x%x pn:0x%x",
		 bp, flag, bp->l_pn);

	/*
	 * initialize buffer क्रम device driver
	 */
	bp->l_flag = flag | lbmसूचीECT;

	/* map the logical block address to physical block address */
	bp->l_blkno =
	    log->base + (bp->l_pn << (L2LOGPSIZE - log->l2bsize));

	/*
	 *	initiate pageout of the page
	 */
	lbmStartIO(bp);
पूर्ण


/*
 * NAME:	lbmStartIO()
 *
 * FUNCTION:	Interface to DD strategy routine
 *
 * RETURN:	none
 *
 * serialization: LCACHE_LOCK() is NOT held during log i/o;
 */
अटल व्योम lbmStartIO(काष्ठा lbuf * bp)
अणु
	काष्ठा bio *bio;
	काष्ठा jfs_log *log = bp->l_log;

	jfs_info("lbmStartIO");

	bio = bio_alloc(GFP_NOFS, 1);
	bio->bi_iter.bi_sector = bp->l_blkno << (log->l2bsize - 9);
	bio_set_dev(bio, log->bdev);

	bio_add_page(bio, bp->l_page, LOGPSIZE, bp->l_offset);
	BUG_ON(bio->bi_iter.bi_size != LOGPSIZE);

	bio->bi_end_io = lbmIODone;
	bio->bi_निजी = bp;
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC;

	/* check अगर journaling to disk has been disabled */
	अगर (log->no_पूर्णांकegrity) अणु
		bio->bi_iter.bi_size = 0;
		lbmIODone(bio);
	पूर्ण अन्यथा अणु
		submit_bio(bio);
		INCREMENT(lmStat.submitted);
	पूर्ण
पूर्ण


/*
 *	lbmIOWait()
 */
अटल पूर्णांक lbmIOWait(काष्ठा lbuf * bp, पूर्णांक flag)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	jfs_info("lbmIOWait1: bp:0x%p flag:0x%x:0x%x", bp, bp->l_flag, flag);

	LCACHE_LOCK(flags);		/* disable+lock */

	LCACHE_SLEEP_COND(bp->l_ioevent, (bp->l_flag & lbmDONE), flags);

	rc = (bp->l_flag & lbmERROR) ? -EIO : 0;

	अगर (flag & lbmFREE)
		lbmमुक्त(bp);

	LCACHE_UNLOCK(flags);	/* unlock+enable */

	jfs_info("lbmIOWait2: bp:0x%p flag:0x%x:0x%x", bp, bp->l_flag, flag);
	वापस rc;
पूर्ण

/*
 *	lbmIODone()
 *
 * executed at INTIODONE level
 */
अटल व्योम lbmIODone(काष्ठा bio *bio)
अणु
	काष्ठा lbuf *bp = bio->bi_निजी;
	काष्ठा lbuf *nextbp, *tail;
	काष्ठा jfs_log *log;
	अचिन्हित दीर्घ flags;

	/*
	 * get back jfs buffer bound to the i/o buffer
	 */
	jfs_info("lbmIODone: bp:0x%p flag:0x%x", bp, bp->l_flag);

	LCACHE_LOCK(flags);		/* disable+lock */

	bp->l_flag |= lbmDONE;

	अगर (bio->bi_status) अणु
		bp->l_flag |= lbmERROR;

		jfs_err("lbmIODone: I/O error in JFS log");
	पूर्ण

	bio_put(bio);

	/*
	 *	pagein completion
	 */
	अगर (bp->l_flag & lbmREAD) अणु
		bp->l_flag &= ~lbmREAD;

		LCACHE_UNLOCK(flags);	/* unlock+enable */

		/* wakeup I/O initiator */
		LCACHE_WAKEUP(&bp->l_ioevent);

		वापस;
	पूर्ण

	/*
	 *	pageout completion
	 *
	 * the bp at the head of ग_लिखो queue has completed pageout.
	 *
	 * अगर single-commit/full-page pageout, हटाओ the current buffer
	 * from head of pageout queue, and redrive pageout with
	 * the new buffer at head of pageout queue;
	 * otherwise, the partial-page pageout buffer stays at
	 * the head of pageout queue to be redriven क्रम pageout
	 * by lmGroupCommit() until full-page pageout is completed.
	 */
	bp->l_flag &= ~lbmWRITE;
	INCREMENT(lmStat.pageकरोne);

	/* update committed lsn */
	log = bp->l_log;
	log->clsn = (bp->l_pn << L2LOGPSIZE) + bp->l_ceor;

	अगर (bp->l_flag & lbmसूचीECT) अणु
		LCACHE_WAKEUP(&bp->l_ioevent);
		LCACHE_UNLOCK(flags);
		वापस;
	पूर्ण

	tail = log->wqueue;

	/* single element queue */
	अगर (bp == tail) अणु
		/* हटाओ head buffer of full-page pageout
		 * from log device ग_लिखो queue
		 */
		अगर (bp->l_flag & lbmRELEASE) अणु
			log->wqueue = शून्य;
			bp->l_wqnext = शून्य;
		पूर्ण
	पूर्ण
	/* multi element queue */
	अन्यथा अणु
		/* हटाओ head buffer of full-page pageout
		 * from log device ग_लिखो queue
		 */
		अगर (bp->l_flag & lbmRELEASE) अणु
			nextbp = tail->l_wqnext = bp->l_wqnext;
			bp->l_wqnext = शून्य;

			/*
			 * redrive pageout of next page at head of ग_लिखो queue:
			 * redrive next page without any bound tblk
			 * (i.e., page w/o any COMMIT records), or
			 * first page of new group commit which has been
			 * queued after current page (subsequent pageout
			 * is perक्रमmed synchronously, except page without
			 * any COMMITs) by lmGroupCommit() as indicated
			 * by lbmWRITE flag;
			 */
			अगर (nextbp->l_flag & lbmWRITE) अणु
				/*
				 * We can't करो the I/O at पूर्णांकerrupt समय.
				 * The jfsIO thपढ़ो can करो it
				 */
				lbmRedrive(nextbp);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 *	synchronous pageout:
	 *
	 * buffer has not necessarily been हटाओd from ग_लिखो queue
	 * (e.g., synchronous ग_लिखो of partial-page with COMMIT):
	 * leave buffer क्रम i/o initiator to dispose
	 */
	अगर (bp->l_flag & lbmSYNC) अणु
		LCACHE_UNLOCK(flags);	/* unlock+enable */

		/* wakeup I/O initiator */
		LCACHE_WAKEUP(&bp->l_ioevent);
	पूर्ण

	/*
	 *	Group Commit pageout:
	 */
	अन्यथा अगर (bp->l_flag & lbmGC) अणु
		LCACHE_UNLOCK(flags);
		lmPostGC(bp);
	पूर्ण

	/*
	 *	asynchronous pageout:
	 *
	 * buffer must have been हटाओd from ग_लिखो queue:
	 * insert buffer at head of मुक्तlist where it can be recycled
	 */
	अन्यथा अणु
		निश्चित(bp->l_flag & lbmRELEASE);
		निश्चित(bp->l_flag & lbmFREE);
		lbmमुक्त(bp);

		LCACHE_UNLOCK(flags);	/* unlock+enable */
	पूर्ण
पूर्ण

पूर्णांक jfsIOWait(व्योम *arg)
अणु
	काष्ठा lbuf *bp;

	करो अणु
		spin_lock_irq(&log_redrive_lock);
		जबतक ((bp = log_redrive_list)) अणु
			log_redrive_list = bp->l_redrive_next;
			bp->l_redrive_next = शून्य;
			spin_unlock_irq(&log_redrive_lock);
			lbmStartIO(bp);
			spin_lock_irq(&log_redrive_lock);
		पूर्ण

		अगर (मुक्तzing(current)) अणु
			spin_unlock_irq(&log_redrive_lock);
			try_to_मुक्तze();
		पूर्ण अन्यथा अणु
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&log_redrive_lock);
			schedule();
		पूर्ण
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	jfs_info("jfsIOWait being killed!");
	वापस 0;
पूर्ण

/*
 * NAME:	lmLogFormat()/jfs_logक्रमm()
 *
 * FUNCTION:	क्रमmat file प्रणाली log
 *
 * PARAMETERS:
 *	log	- volume log
 *	logAddress - start address of log space in FS block
 *	logSize	- length of log space in FS block;
 *
 * RETURN:	0	- success
 *		-EIO	- i/o error
 *
 * XXX: We're synchronously writing one page at a समय.  This needs to
 *	be improved by writing multiple pages at once.
 */
पूर्णांक lmLogFormat(काष्ठा jfs_log *log, s64 logAddress, पूर्णांक logSize)
अणु
	पूर्णांक rc = -EIO;
	काष्ठा jfs_sb_info *sbi;
	काष्ठा logsuper *logsuper;
	काष्ठा logpage *lp;
	पूर्णांक lspn;		/* log sequence page number */
	काष्ठा lrd *lrd_ptr;
	पूर्णांक npages = 0;
	काष्ठा lbuf *bp;

	jfs_info("lmLogFormat: logAddress:%Ld logSize:%d",
		 (दीर्घ दीर्घ)logAddress, logSize);

	sbi = list_entry(log->sb_list.next, काष्ठा jfs_sb_info, log_list);

	/* allocate a log buffer */
	bp = lbmAllocate(log, 1);

	npages = logSize >> sbi->l2nbperpage;

	/*
	 *	log space:
	 *
	 * page 0 - reserved;
	 * page 1 - log superblock;
	 * page 2 - log data page: A SYNC log record is written
	 *	    पूर्णांकo this page at logक्रमm समय;
	 * pages 3-N - log data page: set to empty log data pages;
	 */
	/*
	 *	init log superblock: log page 1
	 */
	logsuper = (काष्ठा logsuper *) bp->l_ldata;

	logsuper->magic = cpu_to_le32(LOGMAGIC);
	logsuper->version = cpu_to_le32(LOGVERSION);
	logsuper->state = cpu_to_le32(LOGREDONE);
	logsuper->flag = cpu_to_le32(sbi->mntflag);	/* ? */
	logsuper->size = cpu_to_le32(npages);
	logsuper->bsize = cpu_to_le32(sbi->bsize);
	logsuper->l2bsize = cpu_to_le32(sbi->l2bsize);
	logsuper->end = cpu_to_le32(2 * LOGPSIZE + LOGPHDRSIZE + LOGRDSIZE);

	bp->l_flag = lbmWRITE | lbmSYNC | lbmसूचीECT;
	bp->l_blkno = logAddress + sbi->nbperpage;
	lbmStartIO(bp);
	अगर ((rc = lbmIOWait(bp, 0)))
		जाओ निकास;

	/*
	 *	init pages 2 to npages-1 as log data pages:
	 *
	 * log page sequence number (lpsn) initialization:
	 *
	 * pn:   0     1     2     3                 n-1
	 *       +-----+-----+=====+=====+===.....===+=====+
	 * lspn:             N-1   0     1           N-2
	 *                   <--- N page circular file ---->
	 *
	 * the N (= npages-2) data pages of the log is मुख्यtained as
	 * a circular file क्रम the log records;
	 * lpsn grows by 1 monotonically as each log page is written
	 * to the circular file of the log;
	 * and setLogpage() will not reset the page number even अगर
	 * the eor is equal to LOGPHDRSIZE. In order क्रम binary search
	 * still work in find log end process, we have to simulate the
	 * log wrap situation at the log क्रमmat समय.
	 * The 1st log page written will have the highest lpsn. Then
	 * the succeeding log pages will have ascending order of
	 * the lspn starting from 0, ... (N-2)
	 */
	lp = (काष्ठा logpage *) bp->l_ldata;
	/*
	 * initialize 1st log page to be written: lpsn = N - 1,
	 * ग_लिखो a SYNCPT log record is written to this page
	 */
	lp->h.page = lp->t.page = cpu_to_le32(npages - 3);
	lp->h.eor = lp->t.eor = cpu_to_le16(LOGPHDRSIZE + LOGRDSIZE);

	lrd_ptr = (काष्ठा lrd *) &lp->data;
	lrd_ptr->logtid = 0;
	lrd_ptr->backchain = 0;
	lrd_ptr->type = cpu_to_le16(LOG_SYNCPT);
	lrd_ptr->length = 0;
	lrd_ptr->log.syncpt.sync = 0;

	bp->l_blkno += sbi->nbperpage;
	bp->l_flag = lbmWRITE | lbmSYNC | lbmसूचीECT;
	lbmStartIO(bp);
	अगर ((rc = lbmIOWait(bp, 0)))
		जाओ निकास;

	/*
	 *	initialize succeeding log pages: lpsn = 0, 1, ..., (N-2)
	 */
	क्रम (lspn = 0; lspn < npages - 3; lspn++) अणु
		lp->h.page = lp->t.page = cpu_to_le32(lspn);
		lp->h.eor = lp->t.eor = cpu_to_le16(LOGPHDRSIZE);

		bp->l_blkno += sbi->nbperpage;
		bp->l_flag = lbmWRITE | lbmSYNC | lbmसूचीECT;
		lbmStartIO(bp);
		अगर ((rc = lbmIOWait(bp, 0)))
			जाओ निकास;
	पूर्ण

	rc = 0;
निकास:
	/*
	 *	finalize log
	 */
	/* release the buffer */
	lbmFree(bp);

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_JFS_STATISTICS
पूर्णांक jfs_lmstats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m,
		       "JFS Logmgr stats\n"
		       "================\n"
		       "commits = %d\n"
		       "writes submitted = %d\n"
		       "writes completed = %d\n"
		       "full pages submitted = %d\n"
		       "partial pages submitted = %d\n",
		       lmStat.commit,
		       lmStat.submitted,
		       lmStat.pageकरोne,
		       lmStat.full_page,
		       lmStat.partial_page);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_JFS_STATISTICS */
