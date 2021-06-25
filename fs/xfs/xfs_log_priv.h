<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_LOG_PRIV_H__
#घोषणा __XFS_LOG_PRIV_H__

काष्ठा xfs_buf;
काष्ठा xlog;
काष्ठा xlog_ticket;
काष्ठा xfs_mount;

/*
 * Flags क्रम log काष्ठाure
 */
#घोषणा XLOG_ACTIVE_RECOVERY	0x2	/* in the middle of recovery */
#घोषणा	XLOG_RECOVERY_NEEDED	0x4	/* log was recovered */
#घोषणा XLOG_IO_ERROR		0x8	/* log hit an I/O error, and being
					   shutकरोwn */
#घोषणा XLOG_TAIL_WARN		0x10	/* log tail verअगरy warning issued */

/*
 * get client id from packed copy.
 *
 * this hack is here because the xlog_pack code copies four bytes
 * of xlog_op_header containing the fields oh_clientid, oh_flags
 * and oh_res2 पूर्णांकo the packed copy.
 *
 * later on this four byte chunk is treated as an पूर्णांक and the
 * client id is pulled out.
 *
 * this has endian issues, of course.
 */
अटल अंतरभूत uपूर्णांक xlog_get_client_id(__be32 i)
अणु
	वापस be32_to_cpu(i) >> 24;
पूर्ण

/*
 * In core log state
 */
क्रमागत xlog_iclog_state अणु
	XLOG_STATE_ACTIVE,	/* Current IC log being written to */
	XLOG_STATE_WANT_SYNC,	/* Want to sync this iclog; no more ग_लिखोs */
	XLOG_STATE_SYNCING,	/* This IC log is syncing */
	XLOG_STATE_DONE_SYNC,	/* Done syncing to disk */
	XLOG_STATE_CALLBACK,	/* Callback functions now */
	XLOG_STATE_सूचीTY,	/* Dirty IC log, not पढ़ोy क्रम ACTIVE status */
	XLOG_STATE_IOERROR,	/* IO error happened in sync'ing log */
पूर्ण;

/*
 * Log ticket flags
 */
#घोषणा XLOG_TIC_PERM_RESERV	0x1	/* permanent reservation */

#घोषणा XLOG_TIC_FLAGS \
	अणु XLOG_TIC_PERM_RESERV,	"XLOG_TIC_PERM_RESERV" पूर्ण

/*
 * Below are states क्रम covering allocation transactions.
 * By covering, we mean changing the h_tail_lsn in the last on-disk
 * log ग_लिखो such that no allocation transactions will be re-करोne during
 * recovery after a प्रणाली crash. Recovery starts at the last on-disk
 * log ग_लिखो.
 *
 * These states are used to insert dummy log entries to cover
 * space allocation transactions which can unकरो non-transactional changes
 * after a crash. Writes to a file with space
 * alपढ़ोy allocated करो not result in any transactions. Allocations
 * might include space beyond the खातापूर्ण. So अगर we just push the खातापूर्ण a
 * little, the last transaction क्रम the file could contain the wrong
 * size. If there is no file प्रणाली activity, after an allocation
 * transaction, and the प्रणाली crashes, the allocation transaction
 * will get replayed and the file will be truncated. This could
 * be hours/days/... after the allocation occurred.
 *
 * The fix क्रम this is to करो two dummy transactions when the
 * प्रणाली is idle. We need two dummy transaction because the h_tail_lsn
 * in the log record header needs to poपूर्णांक beyond the last possible
 * non-dummy transaction. The first dummy changes the h_tail_lsn to
 * the first transaction beक्रमe the dummy. The second dummy causes
 * h_tail_lsn to poपूर्णांक to the first dummy. Recovery starts at h_tail_lsn.
 *
 * These dummy transactions get committed when everything
 * is idle (after there has been some activity).
 *
 * There are 5 states used to control this.
 *
 *  IDLE -- no logging has been करोne on the file प्रणाली or
 *		we are करोne covering previous transactions.
 *  NEED -- logging has occurred and we need a dummy transaction
 *		when the log becomes idle.
 *  DONE -- we were in the NEED state and have committed a dummy
 *		transaction.
 *  NEED2 -- we detected that a dummy transaction has gone to the
 *		on disk log with no other transactions.
 *  DONE2 -- we committed a dummy transaction when in the NEED2 state.
 *
 * There are two places where we चयन states:
 *
 * 1.) In xfs_sync, when we detect an idle log and are in NEED or NEED2.
 *	We commit the dummy transaction and चयन to DONE or DONE2,
 *	respectively. In all other states, we करोn't करो anything.
 *
 * 2.) When we finish writing the on-disk log (xlog_state_clean_log).
 *
 *	No matter what state we are in, अगर this isn't the dummy
 *	transaction going out, the next state is NEED.
 *	So, अगर we aren't in the DONE or DONE2 states, the next state
 *	is NEED. We can't be finishing a ग_लिखो of the dummy record
 *	unless it was committed and the state चयनed to DONE or DONE2.
 *
 *	If we are in the DONE state and this was a ग_लिखो of the
 *		dummy transaction, we move to NEED2.
 *
 *	If we are in the DONE2 state and this was a ग_लिखो of the
 *		dummy transaction, we move to IDLE.
 *
 *
 * Writing only one dummy transaction can get appended to
 * one file space allocation. When this happens, the log recovery
 * code replays the space allocation and a file could be truncated.
 * This is why we have the NEED2 and DONE2 states beक्रमe going idle.
 */

#घोषणा XLOG_STATE_COVER_IDLE	0
#घोषणा XLOG_STATE_COVER_NEED	1
#घोषणा XLOG_STATE_COVER_DONE	2
#घोषणा XLOG_STATE_COVER_NEED2	3
#घोषणा XLOG_STATE_COVER_DONE2	4

#घोषणा XLOG_COVER_OPS		5

/* Ticket reservation region accounting */ 
#घोषणा XLOG_TIC_LEN_MAX	15

/*
 * Reservation region
 * As would be stored in xfs_log_iovec but without the i_addr which
 * we करोn't care about.
 */
प्रकार काष्ठा xlog_res अणु
	uपूर्णांक	r_len;	/* region length		:4 */
	uपूर्णांक	r_type;	/* region's transaction type	:4 */
पूर्ण xlog_res_t;

प्रकार काष्ठा xlog_ticket अणु
	काष्ठा list_head   t_queue;	 /* reserve/ग_लिखो queue */
	काष्ठा task_काष्ठा *t_task;	 /* task that owns this ticket */
	xlog_tid_t	   t_tid;	 /* transaction identअगरier	 : 4  */
	atomic_t	   t_ref;	 /* ticket reference count       : 4  */
	पूर्णांक		   t_curr_res;	 /* current reservation in bytes : 4  */
	पूर्णांक		   t_unit_res;	 /* unit reservation in bytes    : 4  */
	अक्षर		   t_ocnt;	 /* original count		 : 1  */
	अक्षर		   t_cnt;	 /* current count		 : 1  */
	अक्षर		   t_clientid;	 /* who करोes this beदीर्घ to;	 : 1  */
	अक्षर		   t_flags;	 /* properties of reservation	 : 1  */

        /* reservation array fields */
	uपूर्णांक		   t_res_num;                    /* num in array : 4 */
	uपूर्णांक		   t_res_num_ophdrs;		 /* num op hdrs  : 4 */
	uपूर्णांक		   t_res_arr_sum;		 /* array sum    : 4 */
	uपूर्णांक		   t_res_o_flow;		 /* sum overflow : 4 */
	xlog_res_t	   t_res_arr[XLOG_TIC_LEN_MAX];  /* array of res : 8 * 15 */ 
पूर्ण xlog_ticket_t;

/*
 * - A log record header is 512 bytes.  There is plenty of room to grow the
 *	xlog_rec_header_t पूर्णांकo the reserved space.
 * - ic_data follows, so a ग_लिखो to disk can start at the beginning of
 *	the iclog.
 * - ic_क्रमceरुको is used to implement synchronous क्रमcing of the iclog to disk.
 * - ic_next is the poपूर्णांकer to the next iclog in the ring.
 * - ic_log is a poपूर्णांकer back to the global log काष्ठाure.
 * - ic_size is the full size of the log buffer, minus the cycle headers.
 * - ic_offset is the current number of bytes written to in this iclog.
 * - ic_refcnt is bumped when someone is writing to the log.
 * - ic_state is the state of the iclog.
 *
 * Because of cacheline contention on large machines, we need to separate
 * various resources onto dअगरferent cachelines. To start with, make the
 * काष्ठाure cacheline aligned. The following fields can be contended on
 * by independent processes:
 *
 *	- ic_callbacks
 *	- ic_refcnt
 *	- fields रक्षित by the global l_icloglock
 *
 * so we need to ensure that these fields are located in separate cachelines.
 * We'll put all the पढ़ो-only and l_icloglock fields in the first cacheline,
 * and move everything अन्यथा out to subsequent cachelines.
 */
प्रकार काष्ठा xlog_in_core अणु
	रुको_queue_head_t	ic_क्रमce_रुको;
	रुको_queue_head_t	ic_ग_लिखो_रुको;
	काष्ठा xlog_in_core	*ic_next;
	काष्ठा xlog_in_core	*ic_prev;
	काष्ठा xlog		*ic_log;
	u32			ic_size;
	u32			ic_offset;
	क्रमागत xlog_iclog_state	ic_state;
	अक्षर			*ic_datap;	/* poपूर्णांकer to iclog data */

	/* Callback काष्ठाures need their own cacheline */
	spinlock_t		ic_callback_lock ____cacheline_aligned_in_smp;
	काष्ठा list_head	ic_callbacks;

	/* reference counts need their own cacheline */
	atomic_t		ic_refcnt ____cacheline_aligned_in_smp;
	xlog_in_core_2_t	*ic_data;
#घोषणा ic_header	ic_data->hic_header
#अगर_घोषित DEBUG
	bool			ic_fail_crc : 1;
#पूर्ण_अगर
	काष्ठा semaphore	ic_sema;
	काष्ठा work_काष्ठा	ic_end_io_work;
	काष्ठा bio		ic_bio;
	काष्ठा bio_vec		ic_bvec[];
पूर्ण xlog_in_core_t;

/*
 * The CIL context is used to aggregate per-transaction details as well be
 * passed to the iclog क्रम checkpoपूर्णांक post-commit processing.  After being
 * passed to the iclog, another context needs to be allocated क्रम tracking the
 * next set of transactions to be aggregated पूर्णांकo a checkpoपूर्णांक.
 */
काष्ठा xfs_cil;

काष्ठा xfs_cil_ctx अणु
	काष्ठा xfs_cil		*cil;
	xfs_lsn_t		sequence;	/* chkpt sequence # */
	xfs_lsn_t		start_lsn;	/* first LSN of chkpt commit */
	xfs_lsn_t		commit_lsn;	/* chkpt commit record lsn */
	काष्ठा xlog_ticket	*ticket;	/* chkpt ticket */
	पूर्णांक			nvecs;		/* number of regions */
	पूर्णांक			space_used;	/* aggregate size of regions */
	काष्ठा list_head	busy_extents;	/* busy extents in chkpt */
	काष्ठा xfs_log_vec	*lv_chain;	/* logvecs being pushed */
	काष्ठा list_head	iclog_entry;
	काष्ठा list_head	committing;	/* ctx committing list */
	काष्ठा work_काष्ठा	discard_endio_work;
पूर्ण;

/*
 * Committed Item List काष्ठाure
 *
 * This काष्ठाure is used to track log items that have been committed but not
 * yet written पूर्णांकo the log. It is used only when the delayed logging mount
 * option is enabled.
 *
 * This काष्ठाure tracks the list of committing checkpoपूर्णांक contexts so
 * we can aव्योम the problem of having to hold out new transactions during a
 * flush until we have a the commit record LSN of the checkpoपूर्णांक. We can
 * traverse the list of committing contexts in xlog_cil_push_lsn() to find a
 * sequence match and extract the commit LSN directly from there. If the
 * checkpoपूर्णांक is still in the process of committing, we can block रुकोing क्रम
 * the commit LSN to be determined as well. This should make synchronous
 * operations almost as efficient as the old logging methods.
 */
काष्ठा xfs_cil अणु
	काष्ठा xlog		*xc_log;
	काष्ठा list_head	xc_cil;
	spinlock_t		xc_cil_lock;

	काष्ठा rw_semaphore	xc_ctx_lock ____cacheline_aligned_in_smp;
	काष्ठा xfs_cil_ctx	*xc_ctx;

	spinlock_t		xc_push_lock ____cacheline_aligned_in_smp;
	xfs_lsn_t		xc_push_seq;
	काष्ठा list_head	xc_committing;
	रुको_queue_head_t	xc_commit_रुको;
	xfs_lsn_t		xc_current_sequence;
	काष्ठा work_काष्ठा	xc_push_work;
	रुको_queue_head_t	xc_push_रुको;	/* background push throttle */
पूर्ण ____cacheline_aligned_in_smp;

/*
 * The amount of log space we allow the CIL to aggregate is dअगरficult to size.
 * Whatever we choose, we have to make sure we can get a reservation क्रम the
 * log space effectively, that it is large enough to capture sufficient
 * relogging to reduce log buffer IO signअगरicantly, but it is not too large क्रम
 * the log or induces too much latency when writing out through the iclogs. We
 * track both space consumed and the number of vectors in the checkpoपूर्णांक
 * context, so we need to decide which to use क्रम limiting.
 *
 * Every log buffer we ग_लिखो out during a push needs a header reserved, which
 * is at least one sector and more क्रम v2 logs. Hence we need a reservation of
 * at least 512 bytes per 32k of log space just क्रम the LR headers. That means
 * 16KB of reservation per megabyte of delayed logging space we will consume,
 * plus various headers.  The number of headers will vary based on the num of
 * io vectors, so limiting on a specअगरic number of vectors is going to result
 * in transactions of varying size. IOWs, it is more consistent to track and
 * limit space consumed in the log rather than by the number of objects being
 * logged in order to prevent checkpoपूर्णांक ticket overruns.
 *
 * Further, use of अटल reservations through the log grant mechanism is
 * problematic. It पूर्णांकroduces a lot of complनिकासy (e.g. reserve grant vs ग_लिखो
 * grant) and a signअगरicant deadlock potential because regranting ग_लिखो space
 * can block on log pushes. Hence अगर we have to regrant log space during a log
 * push, we can deadlock.
 *
 * However, we can aव्योम this by use of a dynamic "reservation stealing"
 * technique during transaction commit whereby unused reservation space in the
 * transaction ticket is transferred to the CIL ctx commit ticket to cover the
 * space needed by the checkpoपूर्णांक transaction. This means that we never need to
 * specअगरically reserve space क्रम the CIL checkpoपूर्णांक transaction, nor करो we
 * need to regrant space once the checkpoपूर्णांक completes. This also means the
 * checkpoपूर्णांक transaction ticket is specअगरic to the checkpoपूर्णांक context, rather
 * than the CIL itself.
 *
 * With dynamic reservations, we can effectively make up arbitrary limits क्रम
 * the checkpoपूर्णांक size so दीर्घ as they करोn't violate any other size rules.
 * Recovery imposes a rule that no transaction exceed half the log, so we are
 * limited by that.  Furthermore, the log transaction reservation subप्रणाली
 * tries to keep 25% of the log मुक्त, so we need to keep below that limit or we
 * risk running out of मुक्त log space to start any new transactions.
 *
 * In order to keep background CIL push efficient, we only need to ensure the
 * CIL is large enough to मुख्यtain sufficient in-memory relogging to aव्योम
 * repeated physical ग_लिखोs of frequently modअगरied metadata. If we allow the CIL
 * to grow to a substantial fraction of the log, then we may be pinning hundreds
 * of megabytes of metadata in memory until the CIL flushes. This can cause
 * issues when we are running low on memory - pinned memory cannot be reclaimed,
 * and the CIL consumes a lot of memory. Hence we need to set an upper physical
 * size limit क्रम the CIL that limits the maximum amount of memory pinned by the
 * CIL but करोes not limit perक्रमmance by reducing relogging efficiency
 * signअगरicantly.
 *
 * As such, the CIL push threshold ends up being the smaller of two thresholds:
 * - a threshold large enough that it allows CIL to be pushed and progress to be
 *   made without excessive blocking of incoming transaction commits. This is
 *   defined to be 12.5% of the log space - half the 25% push threshold of the
 *   AIL.
 * - small enough that it करोesn't pin excessive amounts of memory but मुख्यtains
 *   बंद to peak relogging efficiency. This is defined to be 16x the iclog
 *   buffer winकरोw (32MB) as measurements have shown this to be roughly the
 *   poपूर्णांक of diminishing perक्रमmance increases under highly concurrent
 *   modअगरication workloads.
 *
 * To prevent the CIL from overflowing upper commit size bounds, we पूर्णांकroduce a
 * new threshold at which we block committing transactions until the background
 * CIL commit commences and चयनes to a new context. While this is not a hard
 * limit, it क्रमces the process committing a transaction to the CIL to block and
 * yeild the CPU, giving the CIL push work a chance to be scheduled and start
 * work. This prevents a process running lots of transactions from overfilling
 * the CIL because it is not yielding the CPU. We set the blocking limit at
 * twice the background push space threshold so we keep in line with the AIL
 * push thresholds.
 *
 * Note: this is not a -hard- limit as blocking is applied after the transaction
 * is inserted पूर्णांकo the CIL and the push has been triggered. It is largely a
 * throttling mechanism that allows the CIL push to be scheduled and run. A hard
 * limit will be dअगरficult to implement without पूर्णांकroducing global serialisation
 * in the CIL commit fast path, and it's not at all clear that we actually need
 * such hard limits given the ~7 years we've run without a hard limit beक्रमe
 * finding the first situation where a checkpoपूर्णांक size overflow actually
 * occurred. Hence the simple throttle, and an ASSERT check to tell us that
 * we've overrun the max size.
 */
#घोषणा XLOG_CIL_SPACE_LIMIT(log)	\
	min_t(पूर्णांक, (log)->l_logsize >> 3, BBTOB(XLOG_TOTAL_REC_SHIFT(log)) << 4)

#घोषणा XLOG_CIL_BLOCKING_SPACE_LIMIT(log)	\
	(XLOG_CIL_SPACE_LIMIT(log) * 2)

/*
 * ticket grant locks, queues and accounting have their own cachlines
 * as these are quite hot and can be operated on concurrently.
 */
काष्ठा xlog_grant_head अणु
	spinlock_t		lock ____cacheline_aligned_in_smp;
	काष्ठा list_head	रुकोers;
	atomic64_t		grant;
पूर्ण;

/*
 * The reservation head lsn is not made up of a cycle number and block number.
 * Instead, it uses a cycle number and byte number.  Logs करोn't expect to
 * overflow 31 bits worth of byte offset, so using a byte number will mean
 * that round off problems won't occur when releasing partial reservations.
 */
काष्ठा xlog अणु
	/* The following fields करोn't need locking */
	काष्ठा xfs_mount	*l_mp;	        /* mount poपूर्णांक */
	काष्ठा xfs_ail		*l_ailp;	/* AIL log is working with */
	काष्ठा xfs_cil		*l_cilp;	/* CIL log is working with */
	काष्ठा xfs_buftarg	*l_targ;        /* buftarg of log */
	काष्ठा workqueue_काष्ठा	*l_ioend_workqueue; /* क्रम I/O completions */
	काष्ठा delayed_work	l_work;		/* background flush work */
	uपूर्णांक			l_flags;
	uपूर्णांक			l_quotaoffs_flag; /* XFS_DQ_*, क्रम QUOTAOFFs */
	काष्ठा list_head	*l_buf_cancel_table;
	पूर्णांक			l_iclog_hsize;  /* size of iclog header */
	पूर्णांक			l_iclog_heads;  /* # of iclog header sectors */
	uपूर्णांक			l_sectBBsize;   /* sector size in BBs (2^n) */
	पूर्णांक			l_iclog_size;	/* size of log in bytes */
	पूर्णांक			l_iclog_bufs;	/* number of iclog buffers */
	xfs_daddr_t		l_logBBstart;   /* start block of log */
	पूर्णांक			l_logsize;      /* size of log in bytes */
	पूर्णांक			l_logBBsize;    /* size of log in BB chunks */

	/* The following block of fields are changed जबतक holding icloglock */
	रुको_queue_head_t	l_flush_रुको ____cacheline_aligned_in_smp;
						/* रुकोing क्रम iclog flush */
	पूर्णांक			l_covered_state;/* state of "covering disk
						 * log entries" */
	xlog_in_core_t		*l_iclog;       /* head log queue	*/
	spinlock_t		l_icloglock;    /* grab to change iclog state */
	पूर्णांक			l_curr_cycle;   /* Cycle number of log ग_लिखोs */
	पूर्णांक			l_prev_cycle;   /* Cycle number beक्रमe last
						 * block increment */
	पूर्णांक			l_curr_block;   /* current logical log block */
	पूर्णांक			l_prev_block;   /* previous logical log block */

	/*
	 * l_last_sync_lsn and l_tail_lsn are atomics so they can be set and
	 * पढ़ो without needing to hold specअगरic locks. To aव्योम operations
	 * contending with other hot objects, place each of them on a separate
	 * cacheline.
	 */
	/* lsn of last LR on disk */
	atomic64_t		l_last_sync_lsn ____cacheline_aligned_in_smp;
	/* lsn of 1st LR with unflushed * buffers */
	atomic64_t		l_tail_lsn ____cacheline_aligned_in_smp;

	काष्ठा xlog_grant_head	l_reserve_head;
	काष्ठा xlog_grant_head	l_ग_लिखो_head;

	काष्ठा xfs_kobj		l_kobj;

	/* The following field are used क्रम debugging; need to hold icloglock */
#अगर_घोषित DEBUG
	व्योम			*l_iclog_bak[XLOG_MAX_ICLOGS];
#पूर्ण_अगर
	/* log recovery lsn tracking (क्रम buffer submission */
	xfs_lsn_t		l_recovery_lsn;
पूर्ण;

#घोषणा XLOG_BUF_CANCEL_BUCKET(log, blkno) \
	((log)->l_buf_cancel_table + ((uपूर्णांक64_t)blkno % XLOG_BC_TABLE_SIZE))

#घोषणा XLOG_FORCED_SHUTDOWN(log) \
	(unlikely((log)->l_flags & XLOG_IO_ERROR))

/* common routines */
बाह्य पूर्णांक
xlog_recover(
	काष्ठा xlog		*log);
बाह्य पूर्णांक
xlog_recover_finish(
	काष्ठा xlog		*log);
बाह्य व्योम
xlog_recover_cancel(काष्ठा xlog *);

बाह्य __le32	 xlog_cksum(काष्ठा xlog *log, काष्ठा xlog_rec_header *rhead,
			    अक्षर *dp, पूर्णांक size);

बाह्य kmem_zone_t *xfs_log_ticket_zone;
काष्ठा xlog_ticket *
xlog_ticket_alloc(
	काष्ठा xlog	*log,
	पूर्णांक		unit_bytes,
	पूर्णांक		count,
	अक्षर		client,
	bool		permanent);

अटल अंतरभूत व्योम
xlog_ग_लिखो_adv_cnt(व्योम **ptr, पूर्णांक *len, पूर्णांक *off, माप_प्रकार bytes)
अणु
	*ptr += bytes;
	*len -= bytes;
	*off += bytes;
पूर्ण

व्योम	xlog_prपूर्णांक_tic_res(काष्ठा xfs_mount *mp, काष्ठा xlog_ticket *ticket);
व्योम	xlog_prपूर्णांक_trans(काष्ठा xfs_trans *);
पूर्णांक	xlog_ग_लिखो(काष्ठा xlog *log, काष्ठा xfs_log_vec *log_vector,
		काष्ठा xlog_ticket *tic, xfs_lsn_t *start_lsn,
		काष्ठा xlog_in_core **commit_iclog, uपूर्णांक flags,
		bool need_start_rec);
पूर्णांक	xlog_commit_record(काष्ठा xlog *log, काष्ठा xlog_ticket *ticket,
		काष्ठा xlog_in_core **iclog, xfs_lsn_t *lsn);
व्योम	xfs_log_ticket_ungrant(काष्ठा xlog *log, काष्ठा xlog_ticket *ticket);
व्योम	xfs_log_ticket_regrant(काष्ठा xlog *log, काष्ठा xlog_ticket *ticket);

/*
 * When we crack an atomic LSN, we sample it first so that the value will not
 * change जबतक we are cracking it पूर्णांकo the component values. This means we
 * will always get consistent component values to work from. This should always
 * be used to sample and crack LSNs that are stored and updated in atomic
 * variables.
 */
अटल अंतरभूत व्योम
xlog_crack_atomic_lsn(atomic64_t *lsn, uपूर्णांक *cycle, uपूर्णांक *block)
अणु
	xfs_lsn_t val = atomic64_पढ़ो(lsn);

	*cycle = CYCLE_LSN(val);
	*block = BLOCK_LSN(val);
पूर्ण

/*
 * Calculate and assign a value to an atomic LSN variable from component pieces.
 */
अटल अंतरभूत व्योम
xlog_assign_atomic_lsn(atomic64_t *lsn, uपूर्णांक cycle, uपूर्णांक block)
अणु
	atomic64_set(lsn, xlog_assign_lsn(cycle, block));
पूर्ण

/*
 * When we crack the grant head, we sample it first so that the value will not
 * change जबतक we are cracking it पूर्णांकo the component values. This means we
 * will always get consistent component values to work from.
 */
अटल अंतरभूत व्योम
xlog_crack_grant_head_val(पूर्णांक64_t val, पूर्णांक *cycle, पूर्णांक *space)
अणु
	*cycle = val >> 32;
	*space = val & 0xffffffff;
पूर्ण

अटल अंतरभूत व्योम
xlog_crack_grant_head(atomic64_t *head, पूर्णांक *cycle, पूर्णांक *space)
अणु
	xlog_crack_grant_head_val(atomic64_पढ़ो(head), cycle, space);
पूर्ण

अटल अंतरभूत पूर्णांक64_t
xlog_assign_grant_head_val(पूर्णांक cycle, पूर्णांक space)
अणु
	वापस ((पूर्णांक64_t)cycle << 32) | space;
पूर्ण

अटल अंतरभूत व्योम
xlog_assign_grant_head(atomic64_t *head, पूर्णांक cycle, पूर्णांक space)
अणु
	atomic64_set(head, xlog_assign_grant_head_val(cycle, space));
पूर्ण

/*
 * Committed Item List पूर्णांकerfaces
 */
पूर्णांक	xlog_cil_init(काष्ठा xlog *log);
व्योम	xlog_cil_init_post_recovery(काष्ठा xlog *log);
व्योम	xlog_cil_destroy(काष्ठा xlog *log);
bool	xlog_cil_empty(काष्ठा xlog *log);

/*
 * CIL क्रमce routines
 */
xfs_lsn_t
xlog_cil_क्रमce_lsn(
	काष्ठा xlog *log,
	xfs_lsn_t sequence);

अटल अंतरभूत व्योम
xlog_cil_क्रमce(काष्ठा xlog *log)
अणु
	xlog_cil_क्रमce_lsn(log, log->l_cilp->xc_current_sequence);
पूर्ण

/*
 * Wrapper function क्रम रुकोing on a रुको queue serialised against wakeups
 * by a spinlock. This matches the semantics of all the रुको queues used in the
 * log code.
 */
अटल अंतरभूत व्योम
xlog_रुको(
	काष्ठा रुको_queue_head	*wq,
	काष्ठा spinlock		*lock)
		__releases(lock)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	add_रुको_queue_exclusive(wq, &रुको);
	__set_current_state(TASK_UNINTERRUPTIBLE);
	spin_unlock(lock);
	schedule();
	हटाओ_रुको_queue(wq, &रुको);
पूर्ण

/*
 * The LSN is valid so दीर्घ as it is behind the current LSN. If it isn't, this
 * means that the next log record that includes this metadata could have a
 * smaller LSN. In turn, this means that the modअगरication in the log would not
 * replay.
 */
अटल अंतरभूत bool
xlog_valid_lsn(
	काष्ठा xlog	*log,
	xfs_lsn_t	lsn)
अणु
	पूर्णांक		cur_cycle;
	पूर्णांक		cur_block;
	bool		valid = true;

	/*
	 * First, sample the current lsn without locking to aव्योम added
	 * contention from metadata I/O. The current cycle and block are updated
	 * (in xlog_state_चयन_iclogs()) and पढ़ो here in a particular order
	 * to aव्योम false negatives (e.g., thinking the metadata LSN is valid
	 * when it is not).
	 *
	 * The current block is always rewound beक्रमe the cycle is bumped in
	 * xlog_state_चयन_iclogs() to ensure the current LSN is never seen in
	 * a transiently क्रमward state. Instead, we can see the LSN in a
	 * transiently behind state अगर we happen to race with a cycle wrap.
	 */
	cur_cycle = READ_ONCE(log->l_curr_cycle);
	smp_rmb();
	cur_block = READ_ONCE(log->l_curr_block);

	अगर ((CYCLE_LSN(lsn) > cur_cycle) ||
	    (CYCLE_LSN(lsn) == cur_cycle && BLOCK_LSN(lsn) > cur_block)) अणु
		/*
		 * If the metadata LSN appears invalid, it's possible the check
		 * above raced with a wrap to the next log cycle. Grab the lock
		 * to check क्रम sure.
		 */
		spin_lock(&log->l_icloglock);
		cur_cycle = log->l_curr_cycle;
		cur_block = log->l_curr_block;
		spin_unlock(&log->l_icloglock);

		अगर ((CYCLE_LSN(lsn) > cur_cycle) ||
		    (CYCLE_LSN(lsn) == cur_cycle && BLOCK_LSN(lsn) > cur_block))
			valid = false;
	पूर्ण

	वापस valid;
पूर्ण

#पूर्ण_अगर	/* __XFS_LOG_PRIV_H__ */
