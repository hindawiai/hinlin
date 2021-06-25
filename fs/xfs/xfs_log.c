<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_sysfs.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_health.h"

kmem_zone_t	*xfs_log_ticket_zone;

/* Local miscellaneous function prototypes */
STATIC काष्ठा xlog *
xlog_alloc_log(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buftarg	*log_target,
	xfs_daddr_t		blk_offset,
	पूर्णांक			num_bblks);
STATIC पूर्णांक
xlog_space_left(
	काष्ठा xlog		*log,
	atomic64_t		*head);
STATIC व्योम
xlog_dealloc_log(
	काष्ठा xlog		*log);

/* local state machine functions */
STATIC व्योम xlog_state_करोne_syncing(
	काष्ठा xlog_in_core	*iclog);
STATIC पूर्णांक
xlog_state_get_iclog_space(
	काष्ठा xlog		*log,
	पूर्णांक			len,
	काष्ठा xlog_in_core	**iclog,
	काष्ठा xlog_ticket	*ticket,
	पूर्णांक			*जारीd_ग_लिखो,
	पूर्णांक			*logoffsetp);
STATIC व्योम
xlog_state_चयन_iclogs(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			eventual_size);
STATIC व्योम
xlog_grant_push_ail(
	काष्ठा xlog		*log,
	पूर्णांक			need_bytes);
STATIC व्योम
xlog_sync(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog);
#अगर defined(DEBUG)
STATIC व्योम
xlog_verअगरy_dest_ptr(
	काष्ठा xlog		*log,
	व्योम			*ptr);
STATIC व्योम
xlog_verअगरy_grant_tail(
	काष्ठा xlog *log);
STATIC व्योम
xlog_verअगरy_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			count);
STATIC व्योम
xlog_verअगरy_tail_lsn(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	xfs_lsn_t		tail_lsn);
#अन्यथा
#घोषणा xlog_verअगरy_dest_ptr(a,b)
#घोषणा xlog_verअगरy_grant_tail(a)
#घोषणा xlog_verअगरy_iclog(a,b,c)
#घोषणा xlog_verअगरy_tail_lsn(a,b,c)
#पूर्ण_अगर

STATIC पूर्णांक
xlog_iclogs_empty(
	काष्ठा xlog		*log);

अटल पूर्णांक
xfs_log_cover(काष्ठा xfs_mount *);

अटल व्योम
xlog_grant_sub_space(
	काष्ठा xlog		*log,
	atomic64_t		*head,
	पूर्णांक			bytes)
अणु
	पूर्णांक64_t	head_val = atomic64_पढ़ो(head);
	पूर्णांक64_t new, old;

	करो अणु
		पूर्णांक	cycle, space;

		xlog_crack_grant_head_val(head_val, &cycle, &space);

		space -= bytes;
		अगर (space < 0) अणु
			space += log->l_logsize;
			cycle--;
		पूर्ण

		old = head_val;
		new = xlog_assign_grant_head_val(cycle, space);
		head_val = atomic64_cmpxchg(head, old, new);
	पूर्ण जबतक (head_val != old);
पूर्ण

अटल व्योम
xlog_grant_add_space(
	काष्ठा xlog		*log,
	atomic64_t		*head,
	पूर्णांक			bytes)
अणु
	पूर्णांक64_t	head_val = atomic64_पढ़ो(head);
	पूर्णांक64_t new, old;

	करो अणु
		पूर्णांक		पंचांगp;
		पूर्णांक		cycle, space;

		xlog_crack_grant_head_val(head_val, &cycle, &space);

		पंचांगp = log->l_logsize - space;
		अगर (पंचांगp > bytes)
			space += bytes;
		अन्यथा अणु
			space = bytes - पंचांगp;
			cycle++;
		पूर्ण

		old = head_val;
		new = xlog_assign_grant_head_val(cycle, space);
		head_val = atomic64_cmpxchg(head, old, new);
	पूर्ण जबतक (head_val != old);
पूर्ण

STATIC व्योम
xlog_grant_head_init(
	काष्ठा xlog_grant_head	*head)
अणु
	xlog_assign_grant_head(&head->grant, 1, 0);
	INIT_LIST_HEAD(&head->रुकोers);
	spin_lock_init(&head->lock);
पूर्ण

STATIC व्योम
xlog_grant_head_wake_all(
	काष्ठा xlog_grant_head	*head)
अणु
	काष्ठा xlog_ticket	*tic;

	spin_lock(&head->lock);
	list_क्रम_each_entry(tic, &head->रुकोers, t_queue)
		wake_up_process(tic->t_task);
	spin_unlock(&head->lock);
पूर्ण

अटल अंतरभूत पूर्णांक
xlog_ticket_reservation(
	काष्ठा xlog		*log,
	काष्ठा xlog_grant_head	*head,
	काष्ठा xlog_ticket	*tic)
अणु
	अगर (head == &log->l_ग_लिखो_head) अणु
		ASSERT(tic->t_flags & XLOG_TIC_PERM_RESERV);
		वापस tic->t_unit_res;
	पूर्ण अन्यथा अणु
		अगर (tic->t_flags & XLOG_TIC_PERM_RESERV)
			वापस tic->t_unit_res * tic->t_cnt;
		अन्यथा
			वापस tic->t_unit_res;
	पूर्ण
पूर्ण

STATIC bool
xlog_grant_head_wake(
	काष्ठा xlog		*log,
	काष्ठा xlog_grant_head	*head,
	पूर्णांक			*मुक्त_bytes)
अणु
	काष्ठा xlog_ticket	*tic;
	पूर्णांक			need_bytes;
	bool			woken_task = false;

	list_क्रम_each_entry(tic, &head->रुकोers, t_queue) अणु

		/*
		 * There is a chance that the size of the CIL checkpoपूर्णांकs in
		 * progress at the last AIL push target calculation resulted in
		 * limiting the target to the log head (l_last_sync_lsn) at the
		 * समय. This may not reflect where the log head is now as the
		 * CIL checkpoपूर्णांकs may have completed.
		 *
		 * Hence when we are woken here, it may be that the head of the
		 * log that has moved rather than the tail. As the tail didn't
		 * move, there still won't be space available क्रम the
		 * reservation we require.  However, अगर the AIL has alपढ़ोy
		 * pushed to the target defined by the old log head location, we
		 * will hang here रुकोing क्रम something अन्यथा to update the AIL
		 * push target.
		 *
		 * Thereक्रमe, अगर there isn't space to wake the first रुकोer on
		 * the grant head, we need to push the AIL again to ensure the
		 * target reflects both the current log tail and log head
		 * position beक्रमe we रुको क्रम the tail to move again.
		 */

		need_bytes = xlog_ticket_reservation(log, head, tic);
		अगर (*मुक्त_bytes < need_bytes) अणु
			अगर (!woken_task)
				xlog_grant_push_ail(log, need_bytes);
			वापस false;
		पूर्ण

		*मुक्त_bytes -= need_bytes;
		trace_xfs_log_grant_wake_up(log, tic);
		wake_up_process(tic->t_task);
		woken_task = true;
	पूर्ण

	वापस true;
पूर्ण

STATIC पूर्णांक
xlog_grant_head_रुको(
	काष्ठा xlog		*log,
	काष्ठा xlog_grant_head	*head,
	काष्ठा xlog_ticket	*tic,
	पूर्णांक			need_bytes) __releases(&head->lock)
					    __acquires(&head->lock)
अणु
	list_add_tail(&tic->t_queue, &head->रुकोers);

	करो अणु
		अगर (XLOG_FORCED_SHUTDOWN(log))
			जाओ shutकरोwn;
		xlog_grant_push_ail(log, need_bytes);

		__set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock(&head->lock);

		XFS_STATS_INC(log->l_mp, xs_sleep_logspace);

		trace_xfs_log_grant_sleep(log, tic);
		schedule();
		trace_xfs_log_grant_wake(log, tic);

		spin_lock(&head->lock);
		अगर (XLOG_FORCED_SHUTDOWN(log))
			जाओ shutकरोwn;
	पूर्ण जबतक (xlog_space_left(log, &head->grant) < need_bytes);

	list_del_init(&tic->t_queue);
	वापस 0;
shutकरोwn:
	list_del_init(&tic->t_queue);
	वापस -EIO;
पूर्ण

/*
 * Atomically get the log space required क्रम a log ticket.
 *
 * Once a ticket माला_लो put onto head->रुकोers, it will only वापस after the
 * needed reservation is satisfied.
 *
 * This function is काष्ठाured so that it has a lock मुक्त fast path. This is
 * necessary because every new transaction reservation will come through this
 * path. Hence any lock will be globally hot अगर we take it unconditionally on
 * every pass.
 *
 * As tickets are only ever moved on and off head->रुकोers under head->lock, we
 * only need to take that lock अगर we are going to add the ticket to the queue
 * and sleep. We can aव्योम taking the lock अगर the ticket was never added to
 * head->रुकोers because the t_queue list head will be empty and we hold the
 * only reference to it so it can safely be checked unlocked.
 */
STATIC पूर्णांक
xlog_grant_head_check(
	काष्ठा xlog		*log,
	काष्ठा xlog_grant_head	*head,
	काष्ठा xlog_ticket	*tic,
	पूर्णांक			*need_bytes)
अणु
	पूर्णांक			मुक्त_bytes;
	पूर्णांक			error = 0;

	ASSERT(!(log->l_flags & XLOG_ACTIVE_RECOVERY));

	/*
	 * If there are other रुकोers on the queue then give them a chance at
	 * logspace beक्रमe us.  Wake up the first रुकोers, अगर we करो not wake
	 * up all the रुकोers then go to sleep रुकोing क्रम more मुक्त space,
	 * otherwise try to get some space क्रम this transaction.
	 */
	*need_bytes = xlog_ticket_reservation(log, head, tic);
	मुक्त_bytes = xlog_space_left(log, &head->grant);
	अगर (!list_empty_careful(&head->रुकोers)) अणु
		spin_lock(&head->lock);
		अगर (!xlog_grant_head_wake(log, head, &मुक्त_bytes) ||
		    मुक्त_bytes < *need_bytes) अणु
			error = xlog_grant_head_रुको(log, head, tic,
						     *need_bytes);
		पूर्ण
		spin_unlock(&head->lock);
	पूर्ण अन्यथा अगर (मुक्त_bytes < *need_bytes) अणु
		spin_lock(&head->lock);
		error = xlog_grant_head_रुको(log, head, tic, *need_bytes);
		spin_unlock(&head->lock);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम
xlog_tic_reset_res(xlog_ticket_t *tic)
अणु
	tic->t_res_num = 0;
	tic->t_res_arr_sum = 0;
	tic->t_res_num_ophdrs = 0;
पूर्ण

अटल व्योम
xlog_tic_add_region(xlog_ticket_t *tic, uपूर्णांक len, uपूर्णांक type)
अणु
	अगर (tic->t_res_num == XLOG_TIC_LEN_MAX) अणु
		/* add to overflow and start again */
		tic->t_res_o_flow += tic->t_res_arr_sum;
		tic->t_res_num = 0;
		tic->t_res_arr_sum = 0;
	पूर्ण

	tic->t_res_arr[tic->t_res_num].r_len = len;
	tic->t_res_arr[tic->t_res_num].r_type = type;
	tic->t_res_arr_sum += len;
	tic->t_res_num++;
पूर्ण

bool
xfs_log_writable(
	काष्ठा xfs_mount	*mp)
अणु
	/*
	 * Do not ग_लिखो to the log on norecovery mounts, अगर the data or log
	 * devices are पढ़ो-only, or अगर the fileप्रणाली is shutकरोwn. Read-only
	 * mounts allow पूर्णांकernal ग_लिखोs क्रम log recovery and unmount purposes,
	 * so करोn't restrict that हाल.
	 */
	अगर (mp->m_flags & XFS_MOUNT_NORECOVERY)
		वापस false;
	अगर (xfs_पढ़ोonly_buftarg(mp->m_ddev_targp))
		वापस false;
	अगर (xfs_पढ़ोonly_buftarg(mp->m_log->l_targ))
		वापस false;
	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस false;
	वापस true;
पूर्ण

/*
 * Replenish the byte reservation required by moving the grant ग_लिखो head.
 */
पूर्णांक
xfs_log_regrant(
	काष्ठा xfs_mount	*mp,
	काष्ठा xlog_ticket	*tic)
अणु
	काष्ठा xlog		*log = mp->m_log;
	पूर्णांक			need_bytes;
	पूर्णांक			error = 0;

	अगर (XLOG_FORCED_SHUTDOWN(log))
		वापस -EIO;

	XFS_STATS_INC(mp, xs_try_logspace);

	/*
	 * This is a new transaction on the ticket, so we need to change the
	 * transaction ID so that the next transaction has a dअगरferent TID in
	 * the log. Just add one to the existing tid so that we can see chains
	 * of rolling transactions in the log easily.
	 */
	tic->t_tid++;

	xlog_grant_push_ail(log, tic->t_unit_res);

	tic->t_curr_res = tic->t_unit_res;
	xlog_tic_reset_res(tic);

	अगर (tic->t_cnt > 0)
		वापस 0;

	trace_xfs_log_regrant(log, tic);

	error = xlog_grant_head_check(log, &log->l_ग_लिखो_head, tic,
				      &need_bytes);
	अगर (error)
		जाओ out_error;

	xlog_grant_add_space(log, &log->l_ग_लिखो_head.grant, need_bytes);
	trace_xfs_log_regrant_निकास(log, tic);
	xlog_verअगरy_grant_tail(log);
	वापस 0;

out_error:
	/*
	 * If we are failing, make sure the ticket करोesn't have any current
	 * reservations.  We करोn't want to add this back when the ticket/
	 * transaction माला_लो cancelled.
	 */
	tic->t_curr_res = 0;
	tic->t_cnt = 0;	/* ungrant will give back unit_res * t_cnt. */
	वापस error;
पूर्ण

/*
 * Reserve log space and वापस a ticket corresponding to the reservation.
 *
 * Each reservation is going to reserve extra space क्रम a log record header.
 * When ग_लिखोs happen to the on-disk log, we करोn't subtract the length of the
 * log record header from any reservation.  By wasting space in each
 * reservation, we prevent over allocation problems.
 */
पूर्णांक
xfs_log_reserve(
	काष्ठा xfs_mount	*mp,
	पूर्णांक		 	unit_bytes,
	पूर्णांक		 	cnt,
	काष्ठा xlog_ticket	**ticp,
	uपूर्णांक8_t		 	client,
	bool			permanent)
अणु
	काष्ठा xlog		*log = mp->m_log;
	काष्ठा xlog_ticket	*tic;
	पूर्णांक			need_bytes;
	पूर्णांक			error = 0;

	ASSERT(client == XFS_TRANSACTION || client == XFS_LOG);

	अगर (XLOG_FORCED_SHUTDOWN(log))
		वापस -EIO;

	XFS_STATS_INC(mp, xs_try_logspace);

	ASSERT(*ticp == शून्य);
	tic = xlog_ticket_alloc(log, unit_bytes, cnt, client, permanent);
	*ticp = tic;

	xlog_grant_push_ail(log, tic->t_cnt ? tic->t_unit_res * tic->t_cnt
					    : tic->t_unit_res);

	trace_xfs_log_reserve(log, tic);

	error = xlog_grant_head_check(log, &log->l_reserve_head, tic,
				      &need_bytes);
	अगर (error)
		जाओ out_error;

	xlog_grant_add_space(log, &log->l_reserve_head.grant, need_bytes);
	xlog_grant_add_space(log, &log->l_ग_लिखो_head.grant, need_bytes);
	trace_xfs_log_reserve_निकास(log, tic);
	xlog_verअगरy_grant_tail(log);
	वापस 0;

out_error:
	/*
	 * If we are failing, make sure the ticket करोesn't have any current
	 * reservations.  We करोn't want to add this back when the ticket/
	 * transaction माला_लो cancelled.
	 */
	tic->t_curr_res = 0;
	tic->t_cnt = 0;	/* ungrant will give back unit_res * t_cnt. */
	वापस error;
पूर्ण

अटल bool
__xlog_state_release_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog)
अणु
	lockdep_निश्चित_held(&log->l_icloglock);

	अगर (iclog->ic_state == XLOG_STATE_WANT_SYNC) अणु
		/* update tail beक्रमe writing to iclog */
		xfs_lsn_t tail_lsn = xlog_assign_tail_lsn(log->l_mp);

		iclog->ic_state = XLOG_STATE_SYNCING;
		iclog->ic_header.h_tail_lsn = cpu_to_be64(tail_lsn);
		xlog_verअगरy_tail_lsn(log, iclog, tail_lsn);
		/* cycle incremented when incrementing curr_block */
		वापस true;
	पूर्ण

	ASSERT(iclog->ic_state == XLOG_STATE_ACTIVE);
	वापस false;
पूर्ण

/*
 * Flush iclog to disk अगर this is the last reference to the given iclog and the
 * it is in the WANT_SYNC state.
 */
अटल पूर्णांक
xlog_state_release_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog)
अणु
	lockdep_निश्चित_held(&log->l_icloglock);

	अगर (iclog->ic_state == XLOG_STATE_IOERROR)
		वापस -EIO;

	अगर (atomic_dec_and_test(&iclog->ic_refcnt) &&
	    __xlog_state_release_iclog(log, iclog)) अणु
		spin_unlock(&log->l_icloglock);
		xlog_sync(log, iclog);
		spin_lock(&log->l_icloglock);
	पूर्ण

	वापस 0;
पूर्ण

व्योम
xfs_log_release_iclog(
	काष्ठा xlog_in_core	*iclog)
अणु
	काष्ठा xlog		*log = iclog->ic_log;
	bool			sync = false;

	अगर (atomic_dec_and_lock(&iclog->ic_refcnt, &log->l_icloglock)) अणु
		अगर (iclog->ic_state != XLOG_STATE_IOERROR)
			sync = __xlog_state_release_iclog(log, iclog);
		spin_unlock(&log->l_icloglock);
	पूर्ण

	अगर (sync)
		xlog_sync(log, iclog);
पूर्ण

/*
 * Mount a log fileप्रणाली
 *
 * mp		- ubiquitous xfs mount poपूर्णांक काष्ठाure
 * log_target	- buftarg of on-disk log device
 * blk_offset	- Start block # where block size is 512 bytes (BBSIZE)
 * num_bblocks	- Number of BBSIZE blocks in on-disk log
 *
 * Return error or zero.
 */
पूर्णांक
xfs_log_mount(
	xfs_mount_t	*mp,
	xfs_buftarg_t	*log_target,
	xfs_daddr_t	blk_offset,
	पूर्णांक		num_bblks)
अणु
	bool		fatal = xfs_sb_version_hascrc(&mp->m_sb);
	पूर्णांक		error = 0;
	पूर्णांक		min_logfsbs;

	अगर (!(mp->m_flags & XFS_MOUNT_NORECOVERY)) अणु
		xfs_notice(mp, "Mounting V%d Filesystem",
			   XFS_SB_VERSION_NUM(&mp->m_sb));
	पूर्ण अन्यथा अणु
		xfs_notice(mp,
"Mounting V%d filesystem in no-recovery mode. Filesystem will be inconsistent.",
			   XFS_SB_VERSION_NUM(&mp->m_sb));
		ASSERT(mp->m_flags & XFS_MOUNT_RDONLY);
	पूर्ण

	mp->m_log = xlog_alloc_log(mp, log_target, blk_offset, num_bblks);
	अगर (IS_ERR(mp->m_log)) अणु
		error = PTR_ERR(mp->m_log);
		जाओ out;
	पूर्ण

	/*
	 * Validate the given log space and drop a critical message via syslog
	 * अगर the log size is too small that would lead to some unexpected
	 * situations in transaction log space reservation stage.
	 *
	 * Note: we can't just reject the mount अगर the validation fails.  This
	 * would mean that people would have to करोwngrade their kernel just to
	 * remedy the situation as there is no way to grow the log (लघु of
	 * black magic surgery with xfs_db).
	 *
	 * We can, however, reject mounts क्रम CRC क्रमmat fileप्रणालीs, as the
	 * mkfs binary being used to make the fileप्रणाली should never create a
	 * fileप्रणाली with a log that is too small.
	 */
	min_logfsbs = xfs_log_calc_minimum_size(mp);

	अगर (mp->m_sb.sb_logblocks < min_logfsbs) अणु
		xfs_warn(mp,
		"Log size %d blocks too small, minimum size is %d blocks",
			 mp->m_sb.sb_logblocks, min_logfsbs);
		error = -EINVAL;
	पूर्ण अन्यथा अगर (mp->m_sb.sb_logblocks > XFS_MAX_LOG_BLOCKS) अणु
		xfs_warn(mp,
		"Log size %d blocks too large, maximum size is %lld blocks",
			 mp->m_sb.sb_logblocks, XFS_MAX_LOG_BLOCKS);
		error = -EINVAL;
	पूर्ण अन्यथा अगर (XFS_FSB_TO_B(mp, mp->m_sb.sb_logblocks) > XFS_MAX_LOG_BYTES) अणु
		xfs_warn(mp,
		"log size %lld bytes too large, maximum size is %lld bytes",
			 XFS_FSB_TO_B(mp, mp->m_sb.sb_logblocks),
			 XFS_MAX_LOG_BYTES);
		error = -EINVAL;
	पूर्ण अन्यथा अगर (mp->m_sb.sb_logsunit > 1 &&
		   mp->m_sb.sb_logsunit % mp->m_sb.sb_blocksize) अणु
		xfs_warn(mp,
		"log stripe unit %u bytes must be a multiple of block size",
			 mp->m_sb.sb_logsunit);
		error = -EINVAL;
		fatal = true;
	पूर्ण
	अगर (error) अणु
		/*
		 * Log check errors are always fatal on v5; or whenever bad
		 * metadata leads to a crash.
		 */
		अगर (fatal) अणु
			xfs_crit(mp, "AAIEEE! Log failed size checks. Abort!");
			ASSERT(0);
			जाओ out_मुक्त_log;
		पूर्ण
		xfs_crit(mp, "Log size out of supported range.");
		xfs_crit(mp,
"Continuing onwards, but if log hangs are experienced then please report this message in the bug report.");
	पूर्ण

	/*
	 * Initialize the AIL now we have a log.
	 */
	error = xfs_trans_ail_init(mp);
	अगर (error) अणु
		xfs_warn(mp, "AIL initialisation failed: error %d", error);
		जाओ out_मुक्त_log;
	पूर्ण
	mp->m_log->l_ailp = mp->m_ail;

	/*
	 * skip log recovery on a norecovery mount.  pretend it all
	 * just worked.
	 */
	अगर (!(mp->m_flags & XFS_MOUNT_NORECOVERY)) अणु
		पूर्णांक	पढ़ोonly = (mp->m_flags & XFS_MOUNT_RDONLY);

		अगर (पढ़ोonly)
			mp->m_flags &= ~XFS_MOUNT_RDONLY;

		error = xlog_recover(mp->m_log);

		अगर (पढ़ोonly)
			mp->m_flags |= XFS_MOUNT_RDONLY;
		अगर (error) अणु
			xfs_warn(mp, "log mount/recovery failed: error %d",
				error);
			xlog_recover_cancel(mp->m_log);
			जाओ out_destroy_ail;
		पूर्ण
	पूर्ण

	error = xfs_sysfs_init(&mp->m_log->l_kobj, &xfs_log_ktype, &mp->m_kobj,
			       "log");
	अगर (error)
		जाओ out_destroy_ail;

	/* Normal transactions can now occur */
	mp->m_log->l_flags &= ~XLOG_ACTIVE_RECOVERY;

	/*
	 * Now the log has been fully initialised and we know were our
	 * space grant counters are, we can initialise the permanent ticket
	 * needed क्रम delayed logging to work.
	 */
	xlog_cil_init_post_recovery(mp->m_log);

	वापस 0;

out_destroy_ail:
	xfs_trans_ail_destroy(mp);
out_मुक्त_log:
	xlog_dealloc_log(mp->m_log);
out:
	वापस error;
पूर्ण

/*
 * Finish the recovery of the file प्रणाली.  This is separate from the
 * xfs_log_mount() call, because it depends on the code in xfs_mountfs() to पढ़ो
 * in the root and real-समय biपंचांगap inodes between calling xfs_log_mount() and
 * here.
 *
 * If we finish recovery successfully, start the background log work. If we are
 * not करोing recovery, then we have a RO fileप्रणाली and we करोn't need to start
 * it.
 */
पूर्णांक
xfs_log_mount_finish(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक	error = 0;
	bool	पढ़ोonly = (mp->m_flags & XFS_MOUNT_RDONLY);
	bool	recovered = mp->m_log->l_flags & XLOG_RECOVERY_NEEDED;

	अगर (mp->m_flags & XFS_MOUNT_NORECOVERY) अणु
		ASSERT(mp->m_flags & XFS_MOUNT_RDONLY);
		वापस 0;
	पूर्ण अन्यथा अगर (पढ़ोonly) अणु
		/* Allow unlinked processing to proceed */
		mp->m_flags &= ~XFS_MOUNT_RDONLY;
	पूर्ण

	/*
	 * During the second phase of log recovery, we need iget and
	 * iput to behave like they करो क्रम an active fileप्रणाली.
	 * xfs_fs_drop_inode needs to be able to prevent the deletion
	 * of inodes beक्रमe we're करोne replaying log items on those
	 * inodes.  Turn it off immediately after recovery finishes
	 * so that we करोn't leak the quota inodes अगर subsequent mount
	 * activities fail.
	 *
	 * We let all inodes involved in reकरो item processing end up on
	 * the LRU instead of being evicted immediately so that अगर we करो
	 * something to an unlinked inode, the irele won't cause
	 * premature truncation and मुक्तing of the inode, which results
	 * in log recovery failure.  We have to evict the unreferenced
	 * lru inodes after clearing SB_ACTIVE because we करोn't
	 * otherwise clean up the lru अगर there's a subsequent failure in
	 * xfs_mountfs, which leads to us leaking the inodes अगर nothing
	 * अन्यथा (e.g. quotacheck) references the inodes beक्रमe the
	 * mount failure occurs.
	 */
	mp->m_super->s_flags |= SB_ACTIVE;
	error = xlog_recover_finish(mp->m_log);
	अगर (!error)
		xfs_log_work_queue(mp);
	mp->m_super->s_flags &= ~SB_ACTIVE;
	evict_inodes(mp->m_super);

	/*
	 * Drain the buffer LRU after log recovery. This is required क्रम v4
	 * fileप्रणालीs to aव्योम leaving around buffers with शून्य verअगरier ops,
	 * but we करो it unconditionally to make sure we're always in a clean
	 * cache state after mount.
	 *
	 * Don't push in the error हाल because the AIL may have pending पूर्णांकents
	 * that aren't हटाओd until recovery is cancelled.
	 */
	अगर (!error && recovered) अणु
		xfs_log_क्रमce(mp, XFS_LOG_SYNC);
		xfs_ail_push_all_sync(mp->m_ail);
	पूर्ण
	xfs_buftarg_drain(mp->m_ddev_targp);

	अगर (पढ़ोonly)
		mp->m_flags |= XFS_MOUNT_RDONLY;

	वापस error;
पूर्ण

/*
 * The mount has failed. Cancel the recovery अगर it hasn't completed and destroy
 * the log.
 */
व्योम
xfs_log_mount_cancel(
	काष्ठा xfs_mount	*mp)
अणु
	xlog_recover_cancel(mp->m_log);
	xfs_log_unmount(mp);
पूर्ण

/*
 * Wait क्रम the iclog to be written disk, or वापस an error अगर the log has been
 * shut करोwn.
 */
अटल पूर्णांक
xlog_रुको_on_iclog(
	काष्ठा xlog_in_core	*iclog)
		__releases(iclog->ic_log->l_icloglock)
अणु
	काष्ठा xlog		*log = iclog->ic_log;

	अगर (!XLOG_FORCED_SHUTDOWN(log) &&
	    iclog->ic_state != XLOG_STATE_ACTIVE &&
	    iclog->ic_state != XLOG_STATE_सूचीTY) अणु
		XFS_STATS_INC(log->l_mp, xs_log_क्रमce_sleep);
		xlog_रुको(&iclog->ic_क्रमce_रुको, &log->l_icloglock);
	पूर्ण अन्यथा अणु
		spin_unlock(&log->l_icloglock);
	पूर्ण

	अगर (XLOG_FORCED_SHUTDOWN(log))
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Write out an unmount record using the ticket provided. We have to account क्रम
 * the data space used in the unmount ticket as this ग_लिखो is not करोne from a
 * transaction context that has alपढ़ोy करोne the accounting क्रम us.
 */
अटल पूर्णांक
xlog_ग_लिखो_unmount_record(
	काष्ठा xlog		*log,
	काष्ठा xlog_ticket	*ticket,
	xfs_lsn_t		*lsn,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_unmount_log_क्रमmat ulf = अणु
		.magic = XLOG_UNMOUNT_TYPE,
	पूर्ण;
	काष्ठा xfs_log_iovec reg = अणु
		.i_addr = &ulf,
		.i_len = माप(ulf),
		.i_type = XLOG_REG_TYPE_UNMOUNT,
	पूर्ण;
	काष्ठा xfs_log_vec vec = अणु
		.lv_niovecs = 1,
		.lv_iovecp = &reg,
	पूर्ण;

	/* account क्रम space used by record data */
	ticket->t_curr_res -= माप(ulf);
	वापस xlog_ग_लिखो(log, &vec, ticket, lsn, शून्य, flags, false);
पूर्ण

/*
 * Mark the fileप्रणाली clean by writing an unmount record to the head of the
 * log.
 */
अटल व्योम
xlog_unmount_ग_लिखो(
	काष्ठा xlog		*log)
अणु
	काष्ठा xfs_mount	*mp = log->l_mp;
	काष्ठा xlog_in_core	*iclog;
	काष्ठा xlog_ticket	*tic = शून्य;
	xfs_lsn_t		lsn;
	uपूर्णांक			flags = XLOG_UNMOUNT_TRANS;
	पूर्णांक			error;

	error = xfs_log_reserve(mp, 600, 1, &tic, XFS_LOG, 0);
	अगर (error)
		जाओ out_err;

	error = xlog_ग_लिखो_unmount_record(log, tic, &lsn, flags);
	/*
	 * At this poपूर्णांक, we're umounting anyway, so there's no poपूर्णांक in
	 * transitioning log state to IOERROR. Just जारी...
	 */
out_err:
	अगर (error)
		xfs_alert(mp, "%s: unmount record failed", __func__);

	spin_lock(&log->l_icloglock);
	iclog = log->l_iclog;
	atomic_inc(&iclog->ic_refcnt);
	अगर (iclog->ic_state == XLOG_STATE_ACTIVE)
		xlog_state_चयन_iclogs(log, iclog, 0);
	अन्यथा
		ASSERT(iclog->ic_state == XLOG_STATE_WANT_SYNC ||
		       iclog->ic_state == XLOG_STATE_IOERROR);
	error = xlog_state_release_iclog(log, iclog);
	xlog_रुको_on_iclog(iclog);

	अगर (tic) अणु
		trace_xfs_log_umount_ग_लिखो(log, tic);
		xfs_log_ticket_ungrant(log, tic);
	पूर्ण
पूर्ण

अटल व्योम
xfs_log_unmount_verअगरy_iclog(
	काष्ठा xlog		*log)
अणु
	काष्ठा xlog_in_core	*iclog = log->l_iclog;

	करो अणु
		ASSERT(iclog->ic_state == XLOG_STATE_ACTIVE);
		ASSERT(iclog->ic_offset == 0);
	पूर्ण जबतक ((iclog = iclog->ic_next) != log->l_iclog);
पूर्ण

/*
 * Unmount record used to have a string "Unmount filesystem--" in the
 * data section where the "Un" was really a magic number (XLOG_UNMOUNT_TYPE).
 * We just ग_लिखो the magic number now since that particular field isn't
 * currently architecture converted and "Unmount" is a bit foo.
 * As far as I know, there weren't any dependencies on the old behaviour.
 */
अटल व्योम
xfs_log_unmount_ग_लिखो(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xlog		*log = mp->m_log;

	अगर (!xfs_log_writable(mp))
		वापस;

	xfs_log_क्रमce(mp, XFS_LOG_SYNC);

	अगर (XLOG_FORCED_SHUTDOWN(log))
		वापस;

	/*
	 * If we think the summary counters are bad, aव्योम writing the unmount
	 * record to क्रमce log recovery at next mount, after which the summary
	 * counters will be recalculated.  Refer to xlog_check_unmount_rec क्रम
	 * more details.
	 */
	अगर (XFS_TEST_ERROR(xfs_fs_has_sickness(mp, XFS_SICK_FS_COUNTERS), mp,
			XFS_ERRTAG_FORCE_SUMMARY_RECALC)) अणु
		xfs_alert(mp, "%s: will fix summary counters at next mount",
				__func__);
		वापस;
	पूर्ण

	xfs_log_unmount_verअगरy_iclog(log);
	xlog_unmount_ग_लिखो(log);
पूर्ण

/*
 * Empty the log क्रम unmount/मुक्तze.
 *
 * To करो this, we first need to shut करोwn the background log work so it is not
 * trying to cover the log as we clean up. We then need to unpin all objects in
 * the log so we can then flush them out. Once they have completed their IO and
 * run the callbacks removing themselves from the AIL, we can cover the log.
 */
पूर्णांक
xfs_log_quiesce(
	काष्ठा xfs_mount	*mp)
अणु
	cancel_delayed_work_sync(&mp->m_log->l_work);
	xfs_log_क्रमce(mp, XFS_LOG_SYNC);

	/*
	 * The superblock buffer is uncached and जबतक xfs_ail_push_all_sync()
	 * will push it, xfs_buftarg_रुको() will not रुको क्रम it. Further,
	 * xfs_buf_ioरुको() cannot be used because it was pushed with the
	 * XBF_ASYNC flag set, so we need to use a lock/unlock pair to रुको क्रम
	 * the IO to complete.
	 */
	xfs_ail_push_all_sync(mp->m_ail);
	xfs_buftarg_रुको(mp->m_ddev_targp);
	xfs_buf_lock(mp->m_sb_bp);
	xfs_buf_unlock(mp->m_sb_bp);

	वापस xfs_log_cover(mp);
पूर्ण

व्योम
xfs_log_clean(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_log_quiesce(mp);
	xfs_log_unmount_ग_लिखो(mp);
पूर्ण

/*
 * Shut करोwn and release the AIL and Log.
 *
 * During unmount, we need to ensure we flush all the dirty metadata objects
 * from the AIL so that the log is empty beक्रमe we ग_लिखो the unmount record to
 * the log. Once this is करोne, we can tear करोwn the AIL and the log.
 */
व्योम
xfs_log_unmount(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_log_clean(mp);

	xfs_buftarg_drain(mp->m_ddev_targp);

	xfs_trans_ail_destroy(mp);

	xfs_sysfs_del(&mp->m_log->l_kobj);

	xlog_dealloc_log(mp->m_log);
पूर्ण

व्योम
xfs_log_item_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_log_item	*item,
	पूर्णांक			type,
	स्थिर काष्ठा xfs_item_ops *ops)
अणु
	item->li_mountp = mp;
	item->li_ailp = mp->m_ail;
	item->li_type = type;
	item->li_ops = ops;
	item->li_lv = शून्य;

	INIT_LIST_HEAD(&item->li_ail);
	INIT_LIST_HEAD(&item->li_cil);
	INIT_LIST_HEAD(&item->li_bio_list);
	INIT_LIST_HEAD(&item->li_trans);
पूर्ण

/*
 * Wake up processes रुकोing क्रम log space after we have moved the log tail.
 */
व्योम
xfs_log_space_wake(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xlog		*log = mp->m_log;
	पूर्णांक			मुक्त_bytes;

	अगर (XLOG_FORCED_SHUTDOWN(log))
		वापस;

	अगर (!list_empty_careful(&log->l_ग_लिखो_head.रुकोers)) अणु
		ASSERT(!(log->l_flags & XLOG_ACTIVE_RECOVERY));

		spin_lock(&log->l_ग_लिखो_head.lock);
		मुक्त_bytes = xlog_space_left(log, &log->l_ग_लिखो_head.grant);
		xlog_grant_head_wake(log, &log->l_ग_लिखो_head, &मुक्त_bytes);
		spin_unlock(&log->l_ग_लिखो_head.lock);
	पूर्ण

	अगर (!list_empty_careful(&log->l_reserve_head.रुकोers)) अणु
		ASSERT(!(log->l_flags & XLOG_ACTIVE_RECOVERY));

		spin_lock(&log->l_reserve_head.lock);
		मुक्त_bytes = xlog_space_left(log, &log->l_reserve_head.grant);
		xlog_grant_head_wake(log, &log->l_reserve_head, &मुक्त_bytes);
		spin_unlock(&log->l_reserve_head.lock);
	पूर्ण
पूर्ण

/*
 * Determine अगर we have a transaction that has gone to disk that needs to be
 * covered. To begin the transition to the idle state firstly the log needs to
 * be idle. That means the CIL, the AIL and the iclogs needs to be empty beक्रमe
 * we start attempting to cover the log.
 *
 * Only अगर we are then in a state where covering is needed, the caller is
 * inक्रमmed that dummy transactions are required to move the log पूर्णांकo the idle
 * state.
 *
 * If there are any items in the AIl or CIL, then we करो not want to attempt to
 * cover the log as we may be in a situation where there isn't log space
 * available to run a dummy transaction and this can lead to deadlocks when the
 * tail of the log is pinned by an item that is modअगरied in the CIL.  Hence
 * there's no poपूर्णांक in running a dummy transaction at this poपूर्णांक because we
 * can't start trying to idle the log until both the CIL and AIL are empty.
 */
अटल bool
xfs_log_need_covered(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xlog		*log = mp->m_log;
	bool			needed = false;

	अगर (!xlog_cil_empty(log))
		वापस false;

	spin_lock(&log->l_icloglock);
	चयन (log->l_covered_state) अणु
	हाल XLOG_STATE_COVER_DONE:
	हाल XLOG_STATE_COVER_DONE2:
	हाल XLOG_STATE_COVER_IDLE:
		अवरोध;
	हाल XLOG_STATE_COVER_NEED:
	हाल XLOG_STATE_COVER_NEED2:
		अगर (xfs_ail_min_lsn(log->l_ailp))
			अवरोध;
		अगर (!xlog_iclogs_empty(log))
			अवरोध;

		needed = true;
		अगर (log->l_covered_state == XLOG_STATE_COVER_NEED)
			log->l_covered_state = XLOG_STATE_COVER_DONE;
		अन्यथा
			log->l_covered_state = XLOG_STATE_COVER_DONE2;
		अवरोध;
	शेष:
		needed = true;
		अवरोध;
	पूर्ण
	spin_unlock(&log->l_icloglock);
	वापस needed;
पूर्ण

/*
 * Explicitly cover the log. This is similar to background log covering but
 * पूर्णांकended क्रम usage in quiesce codepaths. The caller is responsible to ensure
 * the log is idle and suitable क्रम covering. The CIL, iclog buffers and AIL
 * must all be empty.
 */
अटल पूर्णांक
xfs_log_cover(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			error = 0;
	bool			need_covered;

	ASSERT((xlog_cil_empty(mp->m_log) && xlog_iclogs_empty(mp->m_log) &&
	        !xfs_ail_min_lsn(mp->m_log->l_ailp)) ||
	       XFS_FORCED_SHUTDOWN(mp));

	अगर (!xfs_log_writable(mp))
		वापस 0;

	/*
	 * xfs_log_need_covered() is not idempotent because it progresses the
	 * state machine अगर the log requires covering. Thereक्रमe, we must call
	 * this function once and use the result until we've issued an sb sync.
	 * Do so first to make that abundantly clear.
	 *
	 * Fall पूर्णांकo the covering sequence अगर the log needs covering or the
	 * mount has lazy superblock accounting to sync to disk. The sb sync
	 * used क्रम covering accumulates the in-core counters, so covering
	 * handles this क्रम us.
	 */
	need_covered = xfs_log_need_covered(mp);
	अगर (!need_covered && !xfs_sb_version_haslazysbcount(&mp->m_sb))
		वापस 0;

	/*
	 * To cover the log, commit the superblock twice (at most) in
	 * independent checkpoपूर्णांकs. The first serves as a reference क्रम the
	 * tail poपूर्णांकer. The sync transaction and AIL push empties the AIL and
	 * updates the in-core tail to the LSN of the first checkpoपूर्णांक. The
	 * second commit updates the on-disk tail with the in-core LSN,
	 * covering the log. Push the AIL one more समय to leave it empty, as
	 * we found it.
	 */
	करो अणु
		error = xfs_sync_sb(mp, true);
		अगर (error)
			अवरोध;
		xfs_ail_push_all_sync(mp->m_ail);
	पूर्ण जबतक (xfs_log_need_covered(mp));

	वापस error;
पूर्ण

/*
 * We may be holding the log iclog lock upon entering this routine.
 */
xfs_lsn_t
xlog_assign_tail_lsn_locked(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xlog		*log = mp->m_log;
	काष्ठा xfs_log_item	*lip;
	xfs_lsn_t		tail_lsn;

	निश्चित_spin_locked(&mp->m_ail->ail_lock);

	/*
	 * To make sure we always have a valid LSN क्रम the log tail we keep
	 * track of the last LSN which was committed in log->l_last_sync_lsn,
	 * and use that when the AIL was empty.
	 */
	lip = xfs_ail_min(mp->m_ail);
	अगर (lip)
		tail_lsn = lip->li_lsn;
	अन्यथा
		tail_lsn = atomic64_पढ़ो(&log->l_last_sync_lsn);
	trace_xfs_log_assign_tail_lsn(log, tail_lsn);
	atomic64_set(&log->l_tail_lsn, tail_lsn);
	वापस tail_lsn;
पूर्ण

xfs_lsn_t
xlog_assign_tail_lsn(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_lsn_t		tail_lsn;

	spin_lock(&mp->m_ail->ail_lock);
	tail_lsn = xlog_assign_tail_lsn_locked(mp);
	spin_unlock(&mp->m_ail->ail_lock);

	वापस tail_lsn;
पूर्ण

/*
 * Return the space in the log between the tail and the head.  The head
 * is passed in the cycle/bytes क्रमmal parms.  In the special हाल where
 * the reserve head has wrapped passed the tail, this calculation is no
 * दीर्घer valid.  In this हाल, just वापस 0 which means there is no space
 * in the log.  This works क्रम all places where this function is called
 * with the reserve head.  Of course, अगर the ग_लिखो head were to ever
 * wrap the tail, we should blow up.  Rather than catch this हाल here,
 * we depend on other ASSERTions in other parts of the code.   XXXmiken
 *
 * This code also handles the हाल where the reservation head is behind
 * the tail.  The details of this हाल are described below, but the end
 * result is that we वापस the size of the log as the amount of space left.
 */
STATIC पूर्णांक
xlog_space_left(
	काष्ठा xlog	*log,
	atomic64_t	*head)
अणु
	पूर्णांक		मुक्त_bytes;
	पूर्णांक		tail_bytes;
	पूर्णांक		tail_cycle;
	पूर्णांक		head_cycle;
	पूर्णांक		head_bytes;

	xlog_crack_grant_head(head, &head_cycle, &head_bytes);
	xlog_crack_atomic_lsn(&log->l_tail_lsn, &tail_cycle, &tail_bytes);
	tail_bytes = BBTOB(tail_bytes);
	अगर (tail_cycle == head_cycle && head_bytes >= tail_bytes)
		मुक्त_bytes = log->l_logsize - (head_bytes - tail_bytes);
	अन्यथा अगर (tail_cycle + 1 < head_cycle)
		वापस 0;
	अन्यथा अगर (tail_cycle < head_cycle) अणु
		ASSERT(tail_cycle == (head_cycle - 1));
		मुक्त_bytes = tail_bytes - head_bytes;
	पूर्ण अन्यथा अणु
		/*
		 * The reservation head is behind the tail.
		 * In this हाल we just want to वापस the size of the
		 * log as the amount of space left.
		 */
		xfs_alert(log->l_mp, "xlog_space_left: head behind tail");
		xfs_alert(log->l_mp,
			  "  tail_cycle = %d, tail_bytes = %d",
			  tail_cycle, tail_bytes);
		xfs_alert(log->l_mp,
			  "  GH   cycle = %d, GH   bytes = %d",
			  head_cycle, head_bytes);
		ASSERT(0);
		मुक्त_bytes = log->l_logsize;
	पूर्ण
	वापस मुक्त_bytes;
पूर्ण


अटल व्योम
xlog_ioend_work(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xlog_in_core     *iclog =
		container_of(work, काष्ठा xlog_in_core, ic_end_io_work);
	काष्ठा xlog		*log = iclog->ic_log;
	पूर्णांक			error;

	error = blk_status_to_त्रुटि_सं(iclog->ic_bio.bi_status);
#अगर_घोषित DEBUG
	/* treat ग_लिखोs with injected CRC errors as failed */
	अगर (iclog->ic_fail_crc)
		error = -EIO;
#पूर्ण_अगर

	/*
	 * Race to shutकरोwn the fileप्रणाली अगर we see an error.
	 */
	अगर (XFS_TEST_ERROR(error, log->l_mp, XFS_ERRTAG_IODONE_IOERR)) अणु
		xfs_alert(log->l_mp, "log I/O error %d", error);
		xfs_क्रमce_shutकरोwn(log->l_mp, SHUTDOWN_LOG_IO_ERROR);
	पूर्ण

	xlog_state_करोne_syncing(iclog);
	bio_uninit(&iclog->ic_bio);

	/*
	 * Drop the lock to संकेत that we are करोne. Nothing references the
	 * iclog after this, so an unmount रुकोing on this lock can now tear it
	 * करोwn safely. As such, it is unsafe to reference the iclog after the
	 * unlock as we could race with it being मुक्तd.
	 */
	up(&iclog->ic_sema);
पूर्ण

/*
 * Return size of each in-core log record buffer.
 *
 * All machines get 8 x 32kB buffers by शेष, unless tuned otherwise.
 *
 * If the fileप्रणाली blocksize is too large, we may need to choose a
 * larger size since the directory code currently logs entire blocks.
 */
STATIC व्योम
xlog_get_iclog_buffer_size(
	काष्ठा xfs_mount	*mp,
	काष्ठा xlog		*log)
अणु
	अगर (mp->m_logbufs <= 0)
		mp->m_logbufs = XLOG_MAX_ICLOGS;
	अगर (mp->m_logbsize <= 0)
		mp->m_logbsize = XLOG_BIG_RECORD_BSIZE;

	log->l_iclog_bufs = mp->m_logbufs;
	log->l_iclog_size = mp->m_logbsize;

	/*
	 * # headers = size / 32k - one header holds cycles from 32k of data.
	 */
	log->l_iclog_heads =
		DIV_ROUND_UP(mp->m_logbsize, XLOG_HEADER_CYCLE_SIZE);
	log->l_iclog_hsize = log->l_iclog_heads << BBSHIFT;
पूर्ण

व्योम
xfs_log_work_queue(
	काष्ठा xfs_mount        *mp)
अणु
	queue_delayed_work(mp->m_sync_workqueue, &mp->m_log->l_work,
				msecs_to_jअगरfies(xfs_syncd_centisecs * 10));
पूर्ण

/*
 * Every sync period we need to unpin all items in the AIL and push them to
 * disk. If there is nothing dirty, then we might need to cover the log to
 * indicate that the fileप्रणाली is idle.
 */
अटल व्योम
xfs_log_worker(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xlog		*log = container_of(to_delayed_work(work),
						काष्ठा xlog, l_work);
	काष्ठा xfs_mount	*mp = log->l_mp;

	/* dgc: errors ignored - not fatal and nowhere to report them */
	अगर (xfs_fs_writable(mp, SB_FREEZE_WRITE) && xfs_log_need_covered(mp)) अणु
		/*
		 * Dump a transaction पूर्णांकo the log that contains no real change.
		 * This is needed to stamp the current tail LSN पूर्णांकo the log
		 * during the covering operation.
		 *
		 * We cannot use an inode here क्रम this - that will push dirty
		 * state back up पूर्णांकo the VFS and then periodic inode flushing
		 * will prevent log covering from making progress. Hence we
		 * synchronously log the superblock instead to ensure the
		 * superblock is immediately unpinned and can be written back.
		 */
		xfs_sync_sb(mp, true);
	पूर्ण अन्यथा
		xfs_log_क्रमce(mp, 0);

	/* start pushing all the metadata that is currently dirty */
	xfs_ail_push_all(mp->m_ail);

	/* queue us up again */
	xfs_log_work_queue(mp);
पूर्ण

/*
 * This routine initializes some of the log काष्ठाure क्रम a given mount poपूर्णांक.
 * Its primary purpose is to fill in enough, so recovery can occur.  However,
 * some other stuff may be filled in too.
 */
STATIC काष्ठा xlog *
xlog_alloc_log(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buftarg	*log_target,
	xfs_daddr_t		blk_offset,
	पूर्णांक			num_bblks)
अणु
	काष्ठा xlog		*log;
	xlog_rec_header_t	*head;
	xlog_in_core_t		**iclogp;
	xlog_in_core_t		*iclog, *prev_iclog=शून्य;
	पूर्णांक			i;
	पूर्णांक			error = -ENOMEM;
	uपूर्णांक			log2_size = 0;

	log = kmem_zalloc(माप(काष्ठा xlog), KM_MAYFAIL);
	अगर (!log) अणु
		xfs_warn(mp, "Log allocation failed: No memory!");
		जाओ out;
	पूर्ण

	log->l_mp	   = mp;
	log->l_targ	   = log_target;
	log->l_logsize     = BBTOB(num_bblks);
	log->l_logBBstart  = blk_offset;
	log->l_logBBsize   = num_bblks;
	log->l_covered_state = XLOG_STATE_COVER_IDLE;
	log->l_flags	   |= XLOG_ACTIVE_RECOVERY;
	INIT_DELAYED_WORK(&log->l_work, xfs_log_worker);

	log->l_prev_block  = -1;
	/* log->l_tail_lsn = 0x100000000LL; cycle = 1; current block = 0 */
	xlog_assign_atomic_lsn(&log->l_tail_lsn, 1, 0);
	xlog_assign_atomic_lsn(&log->l_last_sync_lsn, 1, 0);
	log->l_curr_cycle  = 1;	    /* 0 is bad since this is initial value */

	xlog_grant_head_init(&log->l_reserve_head);
	xlog_grant_head_init(&log->l_ग_लिखो_head);

	error = -EFSCORRUPTED;
	अगर (xfs_sb_version_hassector(&mp->m_sb)) अणु
	        log2_size = mp->m_sb.sb_logsectlog;
		अगर (log2_size < BBSHIFT) अणु
			xfs_warn(mp, "Log sector size too small (0x%x < 0x%x)",
				log2_size, BBSHIFT);
			जाओ out_मुक्त_log;
		पूर्ण

	        log2_size -= BBSHIFT;
		अगर (log2_size > mp->m_sectbb_log) अणु
			xfs_warn(mp, "Log sector size too large (0x%x > 0x%x)",
				log2_size, mp->m_sectbb_log);
			जाओ out_मुक्त_log;
		पूर्ण

		/* क्रम larger sector sizes, must have v2 or बाह्यal log */
		अगर (log2_size && log->l_logBBstart > 0 &&
			    !xfs_sb_version_haslogv2(&mp->m_sb)) अणु
			xfs_warn(mp,
		"log sector size (0x%x) invalid for configuration.",
				log2_size);
			जाओ out_मुक्त_log;
		पूर्ण
	पूर्ण
	log->l_sectBBsize = 1 << log2_size;

	xlog_get_iclog_buffer_size(mp, log);

	spin_lock_init(&log->l_icloglock);
	init_रुकोqueue_head(&log->l_flush_रुको);

	iclogp = &log->l_iclog;
	/*
	 * The amount of memory to allocate क्रम the iclog काष्ठाure is
	 * rather funky due to the way the काष्ठाure is defined.  It is
	 * करोne this way so that we can use dअगरferent sizes क्रम machines
	 * with dअगरferent amounts of memory.  See the definition of
	 * xlog_in_core_t in xfs_log_priv.h क्रम details.
	 */
	ASSERT(log->l_iclog_size >= 4096);
	क्रम (i = 0; i < log->l_iclog_bufs; i++) अणु
		पूर्णांक align_mask = xfs_buftarg_dma_alignment(mp->m_logdev_targp);
		माप_प्रकार bvec_size = howmany(log->l_iclog_size, PAGE_SIZE) *
				माप(काष्ठा bio_vec);

		iclog = kmem_zalloc(माप(*iclog) + bvec_size, KM_MAYFAIL);
		अगर (!iclog)
			जाओ out_मुक्त_iclog;

		*iclogp = iclog;
		iclog->ic_prev = prev_iclog;
		prev_iclog = iclog;

		iclog->ic_data = kmem_alloc_io(log->l_iclog_size, align_mask,
						KM_MAYFAIL | KM_ZERO);
		अगर (!iclog->ic_data)
			जाओ out_मुक्त_iclog;
#अगर_घोषित DEBUG
		log->l_iclog_bak[i] = &iclog->ic_header;
#पूर्ण_अगर
		head = &iclog->ic_header;
		स_रखो(head, 0, माप(xlog_rec_header_t));
		head->h_magicno = cpu_to_be32(XLOG_HEADER_MAGIC_NUM);
		head->h_version = cpu_to_be32(
			xfs_sb_version_haslogv2(&log->l_mp->m_sb) ? 2 : 1);
		head->h_size = cpu_to_be32(log->l_iclog_size);
		/* new fields */
		head->h_fmt = cpu_to_be32(XLOG_FMT);
		स_नकल(&head->h_fs_uuid, &mp->m_sb.sb_uuid, माप(uuid_t));

		iclog->ic_size = log->l_iclog_size - log->l_iclog_hsize;
		iclog->ic_state = XLOG_STATE_ACTIVE;
		iclog->ic_log = log;
		atomic_set(&iclog->ic_refcnt, 0);
		spin_lock_init(&iclog->ic_callback_lock);
		INIT_LIST_HEAD(&iclog->ic_callbacks);
		iclog->ic_datap = (अक्षर *)iclog->ic_data + log->l_iclog_hsize;

		init_रुकोqueue_head(&iclog->ic_क्रमce_रुको);
		init_रुकोqueue_head(&iclog->ic_ग_लिखो_रुको);
		INIT_WORK(&iclog->ic_end_io_work, xlog_ioend_work);
		sema_init(&iclog->ic_sema, 1);

		iclogp = &iclog->ic_next;
	पूर्ण
	*iclogp = log->l_iclog;			/* complete ring */
	log->l_iclog->ic_prev = prev_iclog;	/* re-ग_लिखो 1st prev ptr */

	log->l_ioend_workqueue = alloc_workqueue("xfs-log/%s",
			XFS_WQFLAGS(WQ_FREEZABLE | WQ_MEM_RECLAIM |
				    WQ_HIGHPRI),
			0, mp->m_super->s_id);
	अगर (!log->l_ioend_workqueue)
		जाओ out_मुक्त_iclog;

	error = xlog_cil_init(log);
	अगर (error)
		जाओ out_destroy_workqueue;
	वापस log;

out_destroy_workqueue:
	destroy_workqueue(log->l_ioend_workqueue);
out_मुक्त_iclog:
	क्रम (iclog = log->l_iclog; iclog; iclog = prev_iclog) अणु
		prev_iclog = iclog->ic_next;
		kmem_मुक्त(iclog->ic_data);
		kmem_मुक्त(iclog);
		अगर (prev_iclog == log->l_iclog)
			अवरोध;
	पूर्ण
out_मुक्त_log:
	kmem_मुक्त(log);
out:
	वापस ERR_PTR(error);
पूर्ण	/* xlog_alloc_log */

/*
 * Write out the commit record of a transaction associated with the given
 * ticket to बंद off a running log ग_लिखो. Return the lsn of the commit record.
 */
पूर्णांक
xlog_commit_record(
	काष्ठा xlog		*log,
	काष्ठा xlog_ticket	*ticket,
	काष्ठा xlog_in_core	**iclog,
	xfs_lsn_t		*lsn)
अणु
	काष्ठा xfs_log_iovec reg = अणु
		.i_addr = शून्य,
		.i_len = 0,
		.i_type = XLOG_REG_TYPE_COMMIT,
	पूर्ण;
	काष्ठा xfs_log_vec vec = अणु
		.lv_niovecs = 1,
		.lv_iovecp = &reg,
	पूर्ण;
	पूर्णांक	error;

	अगर (XLOG_FORCED_SHUTDOWN(log))
		वापस -EIO;

	error = xlog_ग_लिखो(log, &vec, ticket, lsn, iclog, XLOG_COMMIT_TRANS,
			   false);
	अगर (error)
		xfs_क्रमce_shutकरोwn(log->l_mp, SHUTDOWN_LOG_IO_ERROR);
	वापस error;
पूर्ण

/*
 * Compute the LSN that we'd need to push the log tail towards in order to have
 * (a) enough on-disk log space to log the number of bytes specअगरied, (b) at
 * least 25% of the log space मुक्त, and (c) at least 256 blocks मुक्त.  If the
 * log मुक्त space alपढ़ोy meets all three thresholds, this function वापसs
 * शून्यCOMMITLSN.
 */
xfs_lsn_t
xlog_grant_push_threshold(
	काष्ठा xlog	*log,
	पूर्णांक		need_bytes)
अणु
	xfs_lsn_t	threshold_lsn = 0;
	xfs_lsn_t	last_sync_lsn;
	पूर्णांक		मुक्त_blocks;
	पूर्णांक		मुक्त_bytes;
	पूर्णांक		threshold_block;
	पूर्णांक		threshold_cycle;
	पूर्णांक		मुक्त_threshold;

	ASSERT(BTOBB(need_bytes) < log->l_logBBsize);

	मुक्त_bytes = xlog_space_left(log, &log->l_reserve_head.grant);
	मुक्त_blocks = BTOBBT(मुक्त_bytes);

	/*
	 * Set the threshold क्रम the minimum number of मुक्त blocks in the
	 * log to the maximum of what the caller needs, one quarter of the
	 * log, and 256 blocks.
	 */
	मुक्त_threshold = BTOBB(need_bytes);
	मुक्त_threshold = max(मुक्त_threshold, (log->l_logBBsize >> 2));
	मुक्त_threshold = max(मुक्त_threshold, 256);
	अगर (मुक्त_blocks >= मुक्त_threshold)
		वापस शून्यCOMMITLSN;

	xlog_crack_atomic_lsn(&log->l_tail_lsn, &threshold_cycle,
						&threshold_block);
	threshold_block += मुक्त_threshold;
	अगर (threshold_block >= log->l_logBBsize) अणु
		threshold_block -= log->l_logBBsize;
		threshold_cycle += 1;
	पूर्ण
	threshold_lsn = xlog_assign_lsn(threshold_cycle,
					threshold_block);
	/*
	 * Don't pass in an lsn greater than the lsn of the last
	 * log record known to be on disk. Use a snapshot of the last sync lsn
	 * so that it करोesn't change between the compare and the set.
	 */
	last_sync_lsn = atomic64_पढ़ो(&log->l_last_sync_lsn);
	अगर (XFS_LSN_CMP(threshold_lsn, last_sync_lsn) > 0)
		threshold_lsn = last_sync_lsn;

	वापस threshold_lsn;
पूर्ण

/*
 * Push the tail of the log अगर we need to करो so to मुख्यtain the मुक्त log space
 * thresholds set out by xlog_grant_push_threshold.  We may need to aकरोpt a
 * policy which pushes on an lsn which is further aदीर्घ in the log once we
 * reach the high water mark.  In this manner, we would be creating a low water
 * mark.
 */
STATIC व्योम
xlog_grant_push_ail(
	काष्ठा xlog	*log,
	पूर्णांक		need_bytes)
अणु
	xfs_lsn_t	threshold_lsn;

	threshold_lsn = xlog_grant_push_threshold(log, need_bytes);
	अगर (threshold_lsn == शून्यCOMMITLSN || XLOG_FORCED_SHUTDOWN(log))
		वापस;

	/*
	 * Get the transaction layer to kick the dirty buffers out to
	 * disk asynchronously. No poपूर्णांक in trying to करो this अगर
	 * the fileप्रणाली is shutting करोwn.
	 */
	xfs_ail_push(log->l_ailp, threshold_lsn);
पूर्ण

/*
 * Stamp cycle number in every block
 */
STATIC व्योम
xlog_pack_data(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			rounकरोff)
अणु
	पूर्णांक			i, j, k;
	पूर्णांक			size = iclog->ic_offset + rounकरोff;
	__be32			cycle_lsn;
	अक्षर			*dp;

	cycle_lsn = CYCLE_LSN_DISK(iclog->ic_header.h_lsn);

	dp = iclog->ic_datap;
	क्रम (i = 0; i < BTOBB(size); i++) अणु
		अगर (i >= (XLOG_HEADER_CYCLE_SIZE / BBSIZE))
			अवरोध;
		iclog->ic_header.h_cycle_data[i] = *(__be32 *)dp;
		*(__be32 *)dp = cycle_lsn;
		dp += BBSIZE;
	पूर्ण

	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb)) अणु
		xlog_in_core_2_t *xhdr = iclog->ic_data;

		क्रम ( ; i < BTOBB(size); i++) अणु
			j = i / (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
			k = i % (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
			xhdr[j].hic_xheader.xh_cycle_data[k] = *(__be32 *)dp;
			*(__be32 *)dp = cycle_lsn;
			dp += BBSIZE;
		पूर्ण

		क्रम (i = 1; i < log->l_iclog_heads; i++)
			xhdr[i].hic_xheader.xh_cycle = cycle_lsn;
	पूर्ण
पूर्ण

/*
 * Calculate the checksum क्रम a log buffer.
 *
 * This is a little more complicated than it should be because the various
 * headers and the actual data are non-contiguous.
 */
__le32
xlog_cksum(
	काष्ठा xlog		*log,
	काष्ठा xlog_rec_header	*rhead,
	अक्षर			*dp,
	पूर्णांक			size)
अणु
	uपूर्णांक32_t		crc;

	/* first generate the crc क्रम the record header ... */
	crc = xfs_start_cksum_update((अक्षर *)rhead,
			      माप(काष्ठा xlog_rec_header),
			      दुरत्व(काष्ठा xlog_rec_header, h_crc));

	/* ... then क्रम additional cycle data क्रम v2 logs ... */
	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb)) अणु
		जोड़ xlog_in_core2 *xhdr = (जोड़ xlog_in_core2 *)rhead;
		पूर्णांक		i;
		पूर्णांक		xheads;

		xheads = DIV_ROUND_UP(size, XLOG_HEADER_CYCLE_SIZE);

		क्रम (i = 1; i < xheads; i++) अणु
			crc = crc32c(crc, &xhdr[i].hic_xheader,
				     माप(काष्ठा xlog_rec_ext_header));
		पूर्ण
	पूर्ण

	/* ... and finally क्रम the payload */
	crc = crc32c(crc, dp, size);

	वापस xfs_end_cksum(crc);
पूर्ण

अटल व्योम
xlog_bio_end_io(
	काष्ठा bio		*bio)
अणु
	काष्ठा xlog_in_core	*iclog = bio->bi_निजी;

	queue_work(iclog->ic_log->l_ioend_workqueue,
		   &iclog->ic_end_io_work);
पूर्ण

अटल पूर्णांक
xlog_map_iclog_data(
	काष्ठा bio		*bio,
	व्योम			*data,
	माप_प्रकार			count)
अणु
	करो अणु
		काष्ठा page	*page = kmem_to_page(data);
		अचिन्हित पूर्णांक	off = offset_in_page(data);
		माप_प्रकार		len = min_t(माप_प्रकार, count, PAGE_SIZE - off);

		अगर (bio_add_page(bio, page, len, off) != len)
			वापस -EIO;

		data += len;
		count -= len;
	पूर्ण जबतक (count);

	वापस 0;
पूर्ण

STATIC व्योम
xlog_ग_लिखो_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	uपूर्णांक64_t		bno,
	अचिन्हित पूर्णांक		count,
	bool			need_flush)
अणु
	ASSERT(bno < log->l_logBBsize);

	/*
	 * We lock the iclogbufs here so that we can serialise against I/O
	 * completion during unmount.  We might be processing a shutकरोwn
	 * triggered during unmount, and that can occur asynchronously to the
	 * unmount thपढ़ो, and hence we need to ensure that completes beक्रमe
	 * tearing करोwn the iclogbufs.  Hence we need to hold the buffer lock
	 * across the log IO to archieve that.
	 */
	करोwn(&iclog->ic_sema);
	अगर (unlikely(iclog->ic_state == XLOG_STATE_IOERROR)) अणु
		/*
		 * It would seem logical to वापस EIO here, but we rely on
		 * the log state machine to propagate I/O errors instead of
		 * करोing it here.  We kick of the state machine and unlock
		 * the buffer manually, the code needs to be kept in sync
		 * with the I/O completion path.
		 */
		xlog_state_करोne_syncing(iclog);
		up(&iclog->ic_sema);
		वापस;
	पूर्ण

	bio_init(&iclog->ic_bio, iclog->ic_bvec, howmany(count, PAGE_SIZE));
	bio_set_dev(&iclog->ic_bio, log->l_targ->bt_bdev);
	iclog->ic_bio.bi_iter.bi_sector = log->l_logBBstart + bno;
	iclog->ic_bio.bi_end_io = xlog_bio_end_io;
	iclog->ic_bio.bi_निजी = iclog;

	/*
	 * We use REQ_SYNC | REQ_IDLE here to tell the block layer the are more
	 * IOs coming immediately after this one. This prevents the block layer
	 * ग_लिखोback throttle from throttling log ग_लिखोs behind background
	 * metadata ग_लिखोback and causing priority inversions.
	 */
	iclog->ic_bio.bi_opf = REQ_OP_WRITE | REQ_META | REQ_SYNC |
				REQ_IDLE | REQ_FUA;
	अगर (need_flush)
		iclog->ic_bio.bi_opf |= REQ_PREFLUSH;

	अगर (xlog_map_iclog_data(&iclog->ic_bio, iclog->ic_data, count)) अणु
		xfs_क्रमce_shutकरोwn(log->l_mp, SHUTDOWN_LOG_IO_ERROR);
		वापस;
	पूर्ण
	अगर (is_vदो_स्मृति_addr(iclog->ic_data))
		flush_kernel_vmap_range(iclog->ic_data, count);

	/*
	 * If this log buffer would straddle the end of the log we will have
	 * to split it up पूर्णांकo two bios, so that we can जारी at the start.
	 */
	अगर (bno + BTOBB(count) > log->l_logBBsize) अणु
		काष्ठा bio *split;

		split = bio_split(&iclog->ic_bio, log->l_logBBsize - bno,
				  GFP_NOIO, &fs_bio_set);
		bio_chain(split, &iclog->ic_bio);
		submit_bio(split);

		/* restart at logical offset zero क्रम the reमुख्यder */
		iclog->ic_bio.bi_iter.bi_sector = log->l_logBBstart;
	पूर्ण

	submit_bio(&iclog->ic_bio);
पूर्ण

/*
 * We need to bump cycle number क्रम the part of the iclog that is
 * written to the start of the log. Watch out क्रम the header magic
 * number हाल, though.
 */
अटल व्योम
xlog_split_iclog(
	काष्ठा xlog		*log,
	व्योम			*data,
	uपूर्णांक64_t		bno,
	अचिन्हित पूर्णांक		count)
अणु
	अचिन्हित पूर्णांक		split_offset = BBTOB(log->l_logBBsize - bno);
	अचिन्हित पूर्णांक		i;

	क्रम (i = split_offset; i < count; i += BBSIZE) अणु
		uपूर्णांक32_t cycle = get_unaligned_be32(data + i);

		अगर (++cycle == XLOG_HEADER_MAGIC_NUM)
			cycle++;
		put_unaligned_be32(cycle, data + i);
	पूर्ण
पूर्ण

अटल पूर्णांक
xlog_calc_iclog_size(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	uपूर्णांक32_t		*rounकरोff)
अणु
	uपूर्णांक32_t		count_init, count;
	bool			use_lsunit;

	use_lsunit = xfs_sb_version_haslogv2(&log->l_mp->m_sb) &&
			log->l_mp->m_sb.sb_logsunit > 1;

	/* Add क्रम LR header */
	count_init = log->l_iclog_hsize + iclog->ic_offset;

	/* Round out the log ग_लिखो size */
	अगर (use_lsunit) अणु
		/* we have a v2 stripe unit to use */
		count = XLOG_LSUNITTOB(log, XLOG_BTOLSUNIT(log, count_init));
	पूर्ण अन्यथा अणु
		count = BBTOB(BTOBB(count_init));
	पूर्ण

	ASSERT(count >= count_init);
	*rounकरोff = count - count_init;

	अगर (use_lsunit)
		ASSERT(*rounकरोff < log->l_mp->m_sb.sb_logsunit);
	अन्यथा
		ASSERT(*rounकरोff < BBTOB(1));
	वापस count;
पूर्ण

/*
 * Flush out the in-core log (iclog) to the on-disk log in an asynchronous 
 * fashion.  Previously, we should have moved the current iclog
 * ptr in the log to poपूर्णांक to the next available iclog.  This allows further
 * ग_लिखो to जारी जबतक this code syncs out an iclog पढ़ोy to go.
 * Beक्रमe an in-core log can be written out, the data section must be scanned
 * to save away the 1st word of each BBSIZE block पूर्णांकo the header.  We replace
 * it with the current cycle count.  Each BBSIZE block is tagged with the
 * cycle count because there in an implicit assumption that drives will
 * guarantee that entire 512 byte blocks get written at once.  In other words,
 * we can't have part of a 512 byte block written and part not written.  By
 * tagging each block, we will know which blocks are valid when recovering
 * after an unclean shutकरोwn.
 *
 * This routine is single thपढ़ोed on the iclog.  No other thपढ़ो can be in
 * this routine with the same iclog.  Changing contents of iclog can there-
 * क्रमe be करोne without grabbing the state machine lock.  Updating the global
 * log will require grabbing the lock though.
 *
 * The entire log manager uses a logical block numbering scheme.  Only
 * xlog_ग_लिखो_iclog knows about the fact that the log may not start with
 * block zero on a given device.
 */
STATIC व्योम
xlog_sync(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog)
अणु
	अचिन्हित पूर्णांक		count;		/* byte count of bग_लिखो */
	अचिन्हित पूर्णांक		rounकरोff;       /* rounकरोff to BB or stripe */
	uपूर्णांक64_t		bno;
	अचिन्हित पूर्णांक		size;
	bool			need_flush = true, split = false;

	ASSERT(atomic_पढ़ो(&iclog->ic_refcnt) == 0);

	count = xlog_calc_iclog_size(log, iclog, &rounकरोff);

	/* move grant heads by rounकरोff in sync */
	xlog_grant_add_space(log, &log->l_reserve_head.grant, rounकरोff);
	xlog_grant_add_space(log, &log->l_ग_लिखो_head.grant, rounकरोff);

	/* put cycle number in every block */
	xlog_pack_data(log, iclog, rounकरोff); 

	/* real byte length */
	size = iclog->ic_offset;
	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb))
		size += rounकरोff;
	iclog->ic_header.h_len = cpu_to_be32(size);

	XFS_STATS_INC(log->l_mp, xs_log_ग_लिखोs);
	XFS_STATS_ADD(log->l_mp, xs_log_blocks, BTOBB(count));

	bno = BLOCK_LSN(be64_to_cpu(iclog->ic_header.h_lsn));

	/* Do we need to split this ग_लिखो पूर्णांकo 2 parts? */
	अगर (bno + BTOBB(count) > log->l_logBBsize) अणु
		xlog_split_iclog(log, &iclog->ic_header, bno, count);
		split = true;
	पूर्ण

	/* calculcate the checksum */
	iclog->ic_header.h_crc = xlog_cksum(log, &iclog->ic_header,
					    iclog->ic_datap, size);
	/*
	 * Intentionally corrupt the log record CRC based on the error injection
	 * frequency, अगर defined. This facilitates testing log recovery in the
	 * event of torn ग_लिखोs. Hence, set the IOABORT state to पात the log
	 * ग_लिखो on I/O completion and shutकरोwn the fs. The subsequent mount
	 * detects the bad CRC and attempts to recover.
	 */
#अगर_घोषित DEBUG
	अगर (XFS_TEST_ERROR(false, log->l_mp, XFS_ERRTAG_LOG_BAD_CRC)) अणु
		iclog->ic_header.h_crc &= cpu_to_le32(0xAAAAAAAA);
		iclog->ic_fail_crc = true;
		xfs_warn(log->l_mp,
	"Intentionally corrupted log record at LSN 0x%llx. Shutdown imminent.",
			 be64_to_cpu(iclog->ic_header.h_lsn));
	पूर्ण
#पूर्ण_अगर

	/*
	 * Flush the data device beक्रमe flushing the log to make sure all meta
	 * data written back from the AIL actually made it to disk beक्रमe
	 * stamping the new log tail LSN पूर्णांकo the log buffer.  For an बाह्यal
	 * log we need to issue the flush explicitly, and unक्रमtunately
	 * synchronously here; क्रम an पूर्णांकernal log we can simply use the block
	 * layer state machine क्रम preflushes.
	 */
	अगर (log->l_targ != log->l_mp->m_ddev_targp || split) अणु
		xfs_blkdev_issue_flush(log->l_mp->m_ddev_targp);
		need_flush = false;
	पूर्ण

	xlog_verअगरy_iclog(log, iclog, count);
	xlog_ग_लिखो_iclog(log, iclog, bno, count, need_flush);
पूर्ण

/*
 * Deallocate a log काष्ठाure
 */
STATIC व्योम
xlog_dealloc_log(
	काष्ठा xlog	*log)
अणु
	xlog_in_core_t	*iclog, *next_iclog;
	पूर्णांक		i;

	xlog_cil_destroy(log);

	/*
	 * Cycle all the iclogbuf locks to make sure all log IO completion
	 * is करोne beक्रमe we tear करोwn these buffers.
	 */
	iclog = log->l_iclog;
	क्रम (i = 0; i < log->l_iclog_bufs; i++) अणु
		करोwn(&iclog->ic_sema);
		up(&iclog->ic_sema);
		iclog = iclog->ic_next;
	पूर्ण

	iclog = log->l_iclog;
	क्रम (i = 0; i < log->l_iclog_bufs; i++) अणु
		next_iclog = iclog->ic_next;
		kmem_मुक्त(iclog->ic_data);
		kmem_मुक्त(iclog);
		iclog = next_iclog;
	पूर्ण

	log->l_mp->m_log = शून्य;
	destroy_workqueue(log->l_ioend_workqueue);
	kmem_मुक्त(log);
पूर्ण

/*
 * Update counters atomically now that स_नकल is करोne.
 */
अटल अंतरभूत व्योम
xlog_state_finish_copy(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			record_cnt,
	पूर्णांक			copy_bytes)
अणु
	lockdep_निश्चित_held(&log->l_icloglock);

	be32_add_cpu(&iclog->ic_header.h_num_logops, record_cnt);
	iclog->ic_offset += copy_bytes;
पूर्ण

/*
 * prपूर्णांक out info relating to regions written which consume
 * the reservation
 */
व्योम
xlog_prपूर्णांक_tic_res(
	काष्ठा xfs_mount	*mp,
	काष्ठा xlog_ticket	*ticket)
अणु
	uपूर्णांक i;
	uपूर्णांक ophdr_spc = ticket->t_res_num_ophdrs * (uपूर्णांक)माप(xlog_op_header_t);

	/* match with XLOG_REG_TYPE_* in xfs_log.h */
#घोषणा REG_TYPE_STR(type, str)	[XLOG_REG_TYPE_##type] = str
	अटल अक्षर *res_type_str[] = अणु
	    REG_TYPE_STR(BFORMAT, "bformat"),
	    REG_TYPE_STR(BCHUNK, "bchunk"),
	    REG_TYPE_STR(EFI_FORMAT, "efi_format"),
	    REG_TYPE_STR(EFD_FORMAT, "efd_format"),
	    REG_TYPE_STR(IFORMAT, "iformat"),
	    REG_TYPE_STR(ICORE, "icore"),
	    REG_TYPE_STR(IEXT, "iext"),
	    REG_TYPE_STR(IBROOT, "ibroot"),
	    REG_TYPE_STR(ILOCAL, "ilocal"),
	    REG_TYPE_STR(IATTR_EXT, "iattr_ext"),
	    REG_TYPE_STR(IATTR_BROOT, "iattr_broot"),
	    REG_TYPE_STR(IATTR_LOCAL, "iattr_local"),
	    REG_TYPE_STR(QFORMAT, "qformat"),
	    REG_TYPE_STR(DQUOT, "dquot"),
	    REG_TYPE_STR(QUOTAOFF, "quotaoff"),
	    REG_TYPE_STR(LRHEADER, "LR header"),
	    REG_TYPE_STR(UNMOUNT, "unmount"),
	    REG_TYPE_STR(COMMIT, "commit"),
	    REG_TYPE_STR(TRANSHDR, "trans header"),
	    REG_TYPE_STR(ICREATE, "inode create"),
	    REG_TYPE_STR(RUI_FORMAT, "rui_format"),
	    REG_TYPE_STR(RUD_FORMAT, "rud_format"),
	    REG_TYPE_STR(CUI_FORMAT, "cui_format"),
	    REG_TYPE_STR(CUD_FORMAT, "cud_format"),
	    REG_TYPE_STR(BUI_FORMAT, "bui_format"),
	    REG_TYPE_STR(BUD_FORMAT, "bud_format"),
	पूर्ण;
	BUILD_BUG_ON(ARRAY_SIZE(res_type_str) != XLOG_REG_TYPE_MAX + 1);
#अघोषित REG_TYPE_STR

	xfs_warn(mp, "ticket reservation summary:");
	xfs_warn(mp, "  unit res    = %d bytes",
		 ticket->t_unit_res);
	xfs_warn(mp, "  current res = %d bytes",
		 ticket->t_curr_res);
	xfs_warn(mp, "  total reg   = %u bytes (o/flow = %u bytes)",
		 ticket->t_res_arr_sum, ticket->t_res_o_flow);
	xfs_warn(mp, "  ophdrs      = %u (ophdr space = %u bytes)",
		 ticket->t_res_num_ophdrs, ophdr_spc);
	xfs_warn(mp, "  ophdr + reg = %u bytes",
		 ticket->t_res_arr_sum + ticket->t_res_o_flow + ophdr_spc);
	xfs_warn(mp, "  num regions = %u",
		 ticket->t_res_num);

	क्रम (i = 0; i < ticket->t_res_num; i++) अणु
		uपूर्णांक r_type = ticket->t_res_arr[i].r_type;
		xfs_warn(mp, "region[%u]: %s - %u bytes", i,
			    ((r_type <= 0 || r_type > XLOG_REG_TYPE_MAX) ?
			    "bad-rtype" : res_type_str[r_type]),
			    ticket->t_res_arr[i].r_len);
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक a summary of the transaction.
 */
व्योम
xlog_prपूर्णांक_trans(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_log_item	*lip;

	/* dump core transaction and ticket info */
	xfs_warn(mp, "transaction summary:");
	xfs_warn(mp, "  log res   = %d", tp->t_log_res);
	xfs_warn(mp, "  log count = %d", tp->t_log_count);
	xfs_warn(mp, "  flags     = 0x%x", tp->t_flags);

	xlog_prपूर्णांक_tic_res(mp, tp->t_ticket);

	/* dump each log item */
	list_क्रम_each_entry(lip, &tp->t_items, li_trans) अणु
		काष्ठा xfs_log_vec	*lv = lip->li_lv;
		काष्ठा xfs_log_iovec	*vec;
		पूर्णांक			i;

		xfs_warn(mp, "log item: ");
		xfs_warn(mp, "  type	= 0x%x", lip->li_type);
		xfs_warn(mp, "  flags	= 0x%lx", lip->li_flags);
		अगर (!lv)
			जारी;
		xfs_warn(mp, "  niovecs	= %d", lv->lv_niovecs);
		xfs_warn(mp, "  size	= %d", lv->lv_size);
		xfs_warn(mp, "  bytes	= %d", lv->lv_bytes);
		xfs_warn(mp, "  buf len	= %d", lv->lv_buf_len);

		/* dump each iovec क्रम the log item */
		vec = lv->lv_iovecp;
		क्रम (i = 0; i < lv->lv_niovecs; i++) अणु
			पूर्णांक dumplen = min(vec->i_len, 32);

			xfs_warn(mp, "  iovec[%d]", i);
			xfs_warn(mp, "    type	= 0x%x", vec->i_type);
			xfs_warn(mp, "    len	= %d", vec->i_len);
			xfs_warn(mp, "    first %d bytes of iovec[%d]:", dumplen, i);
			xfs_hex_dump(vec->i_addr, dumplen);

			vec++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Calculate the potential space needed by the log vector.  We may need a start
 * record, and each region माला_लो its own काष्ठा xlog_op_header and may need to be
 * द्विगुन word aligned.
 */
अटल पूर्णांक
xlog_ग_लिखो_calc_vec_length(
	काष्ठा xlog_ticket	*ticket,
	काष्ठा xfs_log_vec	*log_vector,
	bool			need_start_rec)
अणु
	काष्ठा xfs_log_vec	*lv;
	पूर्णांक			headers = need_start_rec ? 1 : 0;
	पूर्णांक			len = 0;
	पूर्णांक			i;

	क्रम (lv = log_vector; lv; lv = lv->lv_next) अणु
		/* we करोn't ग_लिखो ordered log vectors */
		अगर (lv->lv_buf_len == XFS_LOG_VEC_ORDERED)
			जारी;

		headers += lv->lv_niovecs;

		क्रम (i = 0; i < lv->lv_niovecs; i++) अणु
			काष्ठा xfs_log_iovec	*vecp = &lv->lv_iovecp[i];

			len += vecp->i_len;
			xlog_tic_add_region(ticket, vecp->i_len, vecp->i_type);
		पूर्ण
	पूर्ण

	ticket->t_res_num_ophdrs += headers;
	len += headers * माप(काष्ठा xlog_op_header);

	वापस len;
पूर्ण

अटल व्योम
xlog_ग_लिखो_start_rec(
	काष्ठा xlog_op_header	*ophdr,
	काष्ठा xlog_ticket	*ticket)
अणु
	ophdr->oh_tid	= cpu_to_be32(ticket->t_tid);
	ophdr->oh_clientid = ticket->t_clientid;
	ophdr->oh_len = 0;
	ophdr->oh_flags = XLOG_START_TRANS;
	ophdr->oh_res2 = 0;
पूर्ण

अटल xlog_op_header_t *
xlog_ग_लिखो_setup_ophdr(
	काष्ठा xlog		*log,
	काष्ठा xlog_op_header	*ophdr,
	काष्ठा xlog_ticket	*ticket,
	uपूर्णांक			flags)
अणु
	ophdr->oh_tid = cpu_to_be32(ticket->t_tid);
	ophdr->oh_clientid = ticket->t_clientid;
	ophdr->oh_res2 = 0;

	/* are we copying a commit or unmount record? */
	ophdr->oh_flags = flags;

	/*
	 * We've seen logs corrupted with bad transaction client ids.  This
	 * makes sure that XFS करोesn't generate them on.  Turn this पूर्णांकo an EIO
	 * and shut करोwn the fileप्रणाली.
	 */
	चयन (ophdr->oh_clientid)  अणु
	हाल XFS_TRANSACTION:
	हाल XFS_VOLUME:
	हाल XFS_LOG:
		अवरोध;
	शेष:
		xfs_warn(log->l_mp,
			"Bad XFS transaction clientid 0x%x in ticket "PTR_FMT,
			ophdr->oh_clientid, ticket);
		वापस शून्य;
	पूर्ण

	वापस ophdr;
पूर्ण

/*
 * Set up the parameters of the region copy पूर्णांकo the log. This has
 * to handle region ग_लिखो split across multiple log buffers - this
 * state is kept बाह्यal to this function so that this code can
 * be written in an obvious, self करोcumenting manner.
 */
अटल पूर्णांक
xlog_ग_लिखो_setup_copy(
	काष्ठा xlog_ticket	*ticket,
	काष्ठा xlog_op_header	*ophdr,
	पूर्णांक			space_available,
	पूर्णांक			space_required,
	पूर्णांक			*copy_off,
	पूर्णांक			*copy_len,
	पूर्णांक			*last_was_partial_copy,
	पूर्णांक			*bytes_consumed)
अणु
	पूर्णांक			still_to_copy;

	still_to_copy = space_required - *bytes_consumed;
	*copy_off = *bytes_consumed;

	अगर (still_to_copy <= space_available) अणु
		/* ग_लिखो of region completes here */
		*copy_len = still_to_copy;
		ophdr->oh_len = cpu_to_be32(*copy_len);
		अगर (*last_was_partial_copy)
			ophdr->oh_flags |= (XLOG_END_TRANS|XLOG_WAS_CONT_TRANS);
		*last_was_partial_copy = 0;
		*bytes_consumed = 0;
		वापस 0;
	पूर्ण

	/* partial ग_लिखो of region, needs extra log op header reservation */
	*copy_len = space_available;
	ophdr->oh_len = cpu_to_be32(*copy_len);
	ophdr->oh_flags |= XLOG_CONTINUE_TRANS;
	अगर (*last_was_partial_copy)
		ophdr->oh_flags |= XLOG_WAS_CONT_TRANS;
	*bytes_consumed += *copy_len;
	(*last_was_partial_copy)++;

	/* account क्रम new log op header */
	ticket->t_curr_res -= माप(काष्ठा xlog_op_header);
	ticket->t_res_num_ophdrs++;

	वापस माप(काष्ठा xlog_op_header);
पूर्ण

अटल पूर्णांक
xlog_ग_लिखो_copy_finish(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	uपूर्णांक			flags,
	पूर्णांक			*record_cnt,
	पूर्णांक			*data_cnt,
	पूर्णांक			*partial_copy,
	पूर्णांक			*partial_copy_len,
	पूर्णांक			log_offset,
	काष्ठा xlog_in_core	**commit_iclog)
अणु
	पूर्णांक			error;

	अगर (*partial_copy) अणु
		/*
		 * This iclog has alपढ़ोy been marked WANT_SYNC by
		 * xlog_state_get_iclog_space.
		 */
		spin_lock(&log->l_icloglock);
		xlog_state_finish_copy(log, iclog, *record_cnt, *data_cnt);
		*record_cnt = 0;
		*data_cnt = 0;
		जाओ release_iclog;
	पूर्ण

	*partial_copy = 0;
	*partial_copy_len = 0;

	अगर (iclog->ic_size - log_offset <= माप(xlog_op_header_t)) अणु
		/* no more space in this iclog - push it. */
		spin_lock(&log->l_icloglock);
		xlog_state_finish_copy(log, iclog, *record_cnt, *data_cnt);
		*record_cnt = 0;
		*data_cnt = 0;

		अगर (iclog->ic_state == XLOG_STATE_ACTIVE)
			xlog_state_चयन_iclogs(log, iclog, 0);
		अन्यथा
			ASSERT(iclog->ic_state == XLOG_STATE_WANT_SYNC ||
			       iclog->ic_state == XLOG_STATE_IOERROR);
		अगर (!commit_iclog)
			जाओ release_iclog;
		spin_unlock(&log->l_icloglock);
		ASSERT(flags & XLOG_COMMIT_TRANS);
		*commit_iclog = iclog;
	पूर्ण

	वापस 0;

release_iclog:
	error = xlog_state_release_iclog(log, iclog);
	spin_unlock(&log->l_icloglock);
	वापस error;
पूर्ण

/*
 * Write some region out to in-core log
 *
 * This will be called when writing बाह्यally provided regions or when
 * writing out a commit record क्रम a given transaction.
 *
 * General algorithm:
 *	1. Find total length of this ग_लिखो.  This may include adding to the
 *		lengths passed in.
 *	2. Check whether we violate the tickets reservation.
 *	3. While writing to this iclog
 *	    A. Reserve as much space in this iclog as can get
 *	    B. If this is first ग_लिखो, save away start lsn
 *	    C. While writing this region:
 *		1. If first ग_लिखो of transaction, ग_लिखो start record
 *		2. Write log operation header (header per region)
 *		3. Find out अगर we can fit entire region पूर्णांकo this iclog
 *		4. Potentially, verअगरy destination स_नकल ptr
 *		5. Memcpy (partial) region
 *		6. If partial copy, release iclog; otherwise, जारी
 *			copying more regions पूर्णांकo current iclog
 *	4. Mark want sync bit (in simulation mode)
 *	5. Release iclog क्रम potential flush to on-disk log.
 *
 * ERRORS:
 * 1.	Panic अगर reservation is overrun.  This should never happen since
 *	reservation amounts are generated पूर्णांकernal to the fileप्रणाली.
 * NOTES:
 * 1. Tickets are single thपढ़ोed data काष्ठाures.
 * 2. The XLOG_END_TRANS & XLOG_CONTINUE_TRANS flags are passed करोwn to the
 *	syncing routine.  When a single log_ग_लिखो region needs to span
 *	multiple in-core logs, the XLOG_CONTINUE_TRANS bit should be set
 *	on all log operation ग_लिखोs which करोn't contain the end of the
 *	region.  The XLOG_END_TRANS bit is used क्रम the in-core log
 *	operation which contains the end of the जारीd log_ग_लिखो region.
 * 3. When xlog_state_get_iclog_space() grअसल the rest of the current iclog,
 *	we करोn't really know exactly how much space will be used.  As a result,
 *	we करोn't update ic_offset until the end when we know exactly how many
 *	bytes have been written out.
 */
पूर्णांक
xlog_ग_लिखो(
	काष्ठा xlog		*log,
	काष्ठा xfs_log_vec	*log_vector,
	काष्ठा xlog_ticket	*ticket,
	xfs_lsn_t		*start_lsn,
	काष्ठा xlog_in_core	**commit_iclog,
	uपूर्णांक			flags,
	bool			need_start_rec)
अणु
	काष्ठा xlog_in_core	*iclog = शून्य;
	काष्ठा xfs_log_vec	*lv = log_vector;
	काष्ठा xfs_log_iovec	*vecp = lv->lv_iovecp;
	पूर्णांक			index = 0;
	पूर्णांक			len;
	पूर्णांक			partial_copy = 0;
	पूर्णांक			partial_copy_len = 0;
	पूर्णांक			contwr = 0;
	पूर्णांक			record_cnt = 0;
	पूर्णांक			data_cnt = 0;
	पूर्णांक			error = 0;

	/*
	 * If this is a commit or unmount transaction, we करोn't need a start
	 * record to be written.  We करो, however, have to account क्रम the
	 * commit or unmount header that माला_लो written. Hence we always have
	 * to account क्रम an extra xlog_op_header here.
	 */
	ticket->t_curr_res -= माप(काष्ठा xlog_op_header);
	अगर (ticket->t_curr_res < 0) अणु
		xfs_alert_tag(log->l_mp, XFS_PTAG_LOGRES,
		     "ctx ticket reservation ran out. Need to up reservation");
		xlog_prपूर्णांक_tic_res(log->l_mp, ticket);
		xfs_क्रमce_shutकरोwn(log->l_mp, SHUTDOWN_LOG_IO_ERROR);
	पूर्ण

	len = xlog_ग_लिखो_calc_vec_length(ticket, log_vector, need_start_rec);
	*start_lsn = 0;
	जबतक (lv && (!lv->lv_niovecs || index < lv->lv_niovecs)) अणु
		व्योम		*ptr;
		पूर्णांक		log_offset;

		error = xlog_state_get_iclog_space(log, len, &iclog, ticket,
						   &contwr, &log_offset);
		अगर (error)
			वापस error;

		ASSERT(log_offset <= iclog->ic_size - 1);
		ptr = iclog->ic_datap + log_offset;

		/* start_lsn is the first lsn written to. That's all we need. */
		अगर (!*start_lsn)
			*start_lsn = be64_to_cpu(iclog->ic_header.h_lsn);

		/*
		 * This loop ग_लिखोs out as many regions as can fit in the amount
		 * of space which was allocated by xlog_state_get_iclog_space().
		 */
		जबतक (lv && (!lv->lv_niovecs || index < lv->lv_niovecs)) अणु
			काष्ठा xfs_log_iovec	*reg;
			काष्ठा xlog_op_header	*ophdr;
			पूर्णांक			copy_len;
			पूर्णांक			copy_off;
			bool			ordered = false;

			/* ordered log vectors have no regions to ग_लिखो */
			अगर (lv->lv_buf_len == XFS_LOG_VEC_ORDERED) अणु
				ASSERT(lv->lv_niovecs == 0);
				ordered = true;
				जाओ next_lv;
			पूर्ण

			reg = &vecp[index];
			ASSERT(reg->i_len % माप(पूर्णांक32_t) == 0);
			ASSERT((अचिन्हित दीर्घ)ptr % माप(पूर्णांक32_t) == 0);

			/*
			 * Beक्रमe we start क्रमmatting log vectors, we need to
			 * ग_लिखो a start record. Only करो this क्रम the first
			 * iclog we ग_लिखो to.
			 */
			अगर (need_start_rec) अणु
				xlog_ग_लिखो_start_rec(ptr, ticket);
				xlog_ग_लिखो_adv_cnt(&ptr, &len, &log_offset,
						माप(काष्ठा xlog_op_header));
			पूर्ण

			ophdr = xlog_ग_लिखो_setup_ophdr(log, ptr, ticket, flags);
			अगर (!ophdr)
				वापस -EIO;

			xlog_ग_लिखो_adv_cnt(&ptr, &len, &log_offset,
					   माप(काष्ठा xlog_op_header));

			len += xlog_ग_लिखो_setup_copy(ticket, ophdr,
						     iclog->ic_size-log_offset,
						     reg->i_len,
						     &copy_off, &copy_len,
						     &partial_copy,
						     &partial_copy_len);
			xlog_verअगरy_dest_ptr(log, ptr);

			/*
			 * Copy region.
			 *
			 * Unmount records just log an opheader, so can have
			 * empty payloads with no data region to copy. Hence we
			 * only copy the payload अगर the vector says it has data
			 * to copy.
			 */
			ASSERT(copy_len >= 0);
			अगर (copy_len > 0) अणु
				स_नकल(ptr, reg->i_addr + copy_off, copy_len);
				xlog_ग_लिखो_adv_cnt(&ptr, &len, &log_offset,
						   copy_len);
			पूर्ण
			copy_len += माप(काष्ठा xlog_op_header);
			record_cnt++;
			अगर (need_start_rec) अणु
				copy_len += माप(काष्ठा xlog_op_header);
				record_cnt++;
				need_start_rec = false;
			पूर्ण
			data_cnt += contwr ? copy_len : 0;

			error = xlog_ग_लिखो_copy_finish(log, iclog, flags,
						       &record_cnt, &data_cnt,
						       &partial_copy,
						       &partial_copy_len,
						       log_offset,
						       commit_iclog);
			अगर (error)
				वापस error;

			/*
			 * अगर we had a partial copy, we need to get more iclog
			 * space but we करोn't want to increment the region
			 * index because there is still more is this region to
			 * ग_लिखो.
			 *
			 * If we completed writing this region, and we flushed
			 * the iclog (indicated by resetting of the record
			 * count), then we also need to get more log space. If
			 * this was the last record, though, we are करोne and
			 * can just वापस.
			 */
			अगर (partial_copy)
				अवरोध;

			अगर (++index == lv->lv_niovecs) अणु
next_lv:
				lv = lv->lv_next;
				index = 0;
				अगर (lv)
					vecp = lv->lv_iovecp;
			पूर्ण
			अगर (record_cnt == 0 && !ordered) अणु
				अगर (!lv)
					वापस 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ASSERT(len == 0);

	spin_lock(&log->l_icloglock);
	xlog_state_finish_copy(log, iclog, record_cnt, data_cnt);
	अगर (commit_iclog) अणु
		ASSERT(flags & XLOG_COMMIT_TRANS);
		*commit_iclog = iclog;
	पूर्ण अन्यथा अणु
		error = xlog_state_release_iclog(log, iclog);
	पूर्ण
	spin_unlock(&log->l_icloglock);

	वापस error;
पूर्ण

अटल व्योम
xlog_state_activate_iclog(
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			*iclogs_changed)
अणु
	ASSERT(list_empty_careful(&iclog->ic_callbacks));

	/*
	 * If the number of ops in this iclog indicate it just contains the
	 * dummy transaction, we can change state पूर्णांकo IDLE (the second समय
	 * around). Otherwise we should change the state पूर्णांकo NEED a dummy.
	 * We करोn't need to cover the dummy.
	 */
	अगर (*iclogs_changed == 0 &&
	    iclog->ic_header.h_num_logops == cpu_to_be32(XLOG_COVER_OPS)) अणु
		*iclogs_changed = 1;
	पूर्ण अन्यथा अणु
		/*
		 * We have two dirty iclogs so start over.  This could also be
		 * num of ops indicating this is not the dummy going out.
		 */
		*iclogs_changed = 2;
	पूर्ण

	iclog->ic_state	= XLOG_STATE_ACTIVE;
	iclog->ic_offset = 0;
	iclog->ic_header.h_num_logops = 0;
	स_रखो(iclog->ic_header.h_cycle_data, 0,
		माप(iclog->ic_header.h_cycle_data));
	iclog->ic_header.h_lsn = 0;
पूर्ण

/*
 * Loop through all iclogs and mark all iclogs currently marked सूचीTY as
 * ACTIVE after iclog I/O has completed.
 */
अटल व्योम
xlog_state_activate_iclogs(
	काष्ठा xlog		*log,
	पूर्णांक			*iclogs_changed)
अणु
	काष्ठा xlog_in_core	*iclog = log->l_iclog;

	करो अणु
		अगर (iclog->ic_state == XLOG_STATE_सूचीTY)
			xlog_state_activate_iclog(iclog, iclogs_changed);
		/*
		 * The ordering of marking iclogs ACTIVE must be मुख्यtained, so
		 * an iclog करोesn't become ACTIVE beyond one that is SYNCING.
		 */
		अन्यथा अगर (iclog->ic_state != XLOG_STATE_ACTIVE)
			अवरोध;
	पूर्ण जबतक ((iclog = iclog->ic_next) != log->l_iclog);
पूर्ण

अटल पूर्णांक
xlog_covered_state(
	पूर्णांक			prev_state,
	पूर्णांक			iclogs_changed)
अणु
	/*
	 * We go to NEED क्रम any non-covering ग_लिखोs. We go to NEED2 अगर we just
	 * wrote the first covering record (DONE). We go to IDLE अगर we just
	 * wrote the second covering record (DONE2) and reमुख्य in IDLE until a
	 * non-covering ग_लिखो occurs.
	 */
	चयन (prev_state) अणु
	हाल XLOG_STATE_COVER_IDLE:
		अगर (iclogs_changed == 1)
			वापस XLOG_STATE_COVER_IDLE;
	हाल XLOG_STATE_COVER_NEED:
	हाल XLOG_STATE_COVER_NEED2:
		अवरोध;
	हाल XLOG_STATE_COVER_DONE:
		अगर (iclogs_changed == 1)
			वापस XLOG_STATE_COVER_NEED2;
		अवरोध;
	हाल XLOG_STATE_COVER_DONE2:
		अगर (iclogs_changed == 1)
			वापस XLOG_STATE_COVER_IDLE;
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण

	वापस XLOG_STATE_COVER_NEED;
पूर्ण

STATIC व्योम
xlog_state_clean_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*dirty_iclog)
अणु
	पूर्णांक			iclogs_changed = 0;

	dirty_iclog->ic_state = XLOG_STATE_सूचीTY;

	xlog_state_activate_iclogs(log, &iclogs_changed);
	wake_up_all(&dirty_iclog->ic_क्रमce_रुको);

	अगर (iclogs_changed) अणु
		log->l_covered_state = xlog_covered_state(log->l_covered_state,
				iclogs_changed);
	पूर्ण
पूर्ण

STATIC xfs_lsn_t
xlog_get_lowest_lsn(
	काष्ठा xlog		*log)
अणु
	काष्ठा xlog_in_core	*iclog = log->l_iclog;
	xfs_lsn_t		lowest_lsn = 0, lsn;

	करो अणु
		अगर (iclog->ic_state == XLOG_STATE_ACTIVE ||
		    iclog->ic_state == XLOG_STATE_सूचीTY)
			जारी;

		lsn = be64_to_cpu(iclog->ic_header.h_lsn);
		अगर ((lsn && !lowest_lsn) || XFS_LSN_CMP(lsn, lowest_lsn) < 0)
			lowest_lsn = lsn;
	पूर्ण जबतक ((iclog = iclog->ic_next) != log->l_iclog);

	वापस lowest_lsn;
पूर्ण

/*
 * Completion of a iclog IO करोes not imply that a transaction has completed, as
 * transactions can be large enough to span many iclogs. We cannot change the
 * tail of the log half way through a transaction as this may be the only
 * transaction in the log and moving the tail to poपूर्णांक to the middle of it
 * will prevent recovery from finding the start of the transaction. Hence we
 * should only update the last_sync_lsn अगर this iclog contains transaction
 * completion callbacks on it.
 *
 * We have to करो this beक्रमe we drop the icloglock to ensure we are the only one
 * that can update it.
 *
 * If we are moving the last_sync_lsn क्रमwards, we also need to ensure we kick
 * the reservation grant head pushing. This is due to the fact that the push
 * target is bound by the current last_sync_lsn value. Hence अगर we have a large
 * amount of log space bound up in this committing transaction then the
 * last_sync_lsn value may be the limiting factor preventing tail pushing from
 * मुक्तing space in the log. Hence once we've updated the last_sync_lsn we
 * should push the AIL to ensure the push target (and hence the grant head) is
 * no दीर्घer bound by the old log head location and can move क्रमwards and make
 * progress again.
 */
अटल व्योम
xlog_state_set_callback(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	xfs_lsn_t		header_lsn)
अणु
	iclog->ic_state = XLOG_STATE_CALLBACK;

	ASSERT(XFS_LSN_CMP(atomic64_पढ़ो(&log->l_last_sync_lsn),
			   header_lsn) <= 0);

	अगर (list_empty_careful(&iclog->ic_callbacks))
		वापस;

	atomic64_set(&log->l_last_sync_lsn, header_lsn);
	xlog_grant_push_ail(log, 0);
पूर्ण

/*
 * Return true अगर we need to stop processing, false to जारी to the next
 * iclog. The caller will need to run callbacks अगर the iclog is वापसed in the
 * XLOG_STATE_CALLBACK state.
 */
अटल bool
xlog_state_ioकरोne_process_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	bool			*ioerror)
अणु
	xfs_lsn_t		lowest_lsn;
	xfs_lsn_t		header_lsn;

	चयन (iclog->ic_state) अणु
	हाल XLOG_STATE_ACTIVE:
	हाल XLOG_STATE_सूचीTY:
		/*
		 * Skip all iclogs in the ACTIVE & सूचीTY states:
		 */
		वापस false;
	हाल XLOG_STATE_IOERROR:
		/*
		 * Between marking a fileप्रणाली SHUTDOWN and stopping the log,
		 * we करो flush all iclogs to disk (अगर there wasn't a log I/O
		 * error). So, we करो want things to go smoothly in हाल of just
		 * a SHUTDOWN w/o a LOG_IO_ERROR.
		 */
		*ioerror = true;
		वापस false;
	हाल XLOG_STATE_DONE_SYNC:
		/*
		 * Now that we have an iclog that is in the DONE_SYNC state, करो
		 * one more check here to see अगर we have chased our tail around.
		 * If this is not the lowest lsn iclog, then we will leave it
		 * क्रम another completion to process.
		 */
		header_lsn = be64_to_cpu(iclog->ic_header.h_lsn);
		lowest_lsn = xlog_get_lowest_lsn(log);
		अगर (lowest_lsn && XFS_LSN_CMP(lowest_lsn, header_lsn) < 0)
			वापस false;
		xlog_state_set_callback(log, iclog, header_lsn);
		वापस false;
	शेष:
		/*
		 * Can only perक्रमm callbacks in order.  Since this iclog is not
		 * in the DONE_SYNC state, we skip the rest and just try to
		 * clean up.
		 */
		वापस true;
	पूर्ण
पूर्ण

/*
 * Keep processing entries in the iclog callback list until we come around and
 * it is empty.  We need to atomically see that the list is empty and change the
 * state to सूचीTY so that we करोn't miss any more callbacks being added.
 *
 * This function is called with the icloglock held and वापसs with it held. We
 * drop it जबतक running callbacks, however, as holding it over thousands of
 * callbacks is unnecessary and causes excessive contention अगर we करो.
 */
अटल व्योम
xlog_state_करो_iclog_callbacks(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog)
		__releases(&log->l_icloglock)
		__acquires(&log->l_icloglock)
अणु
	spin_unlock(&log->l_icloglock);
	spin_lock(&iclog->ic_callback_lock);
	जबतक (!list_empty(&iclog->ic_callbacks)) अणु
		LIST_HEAD(पंचांगp);

		list_splice_init(&iclog->ic_callbacks, &पंचांगp);

		spin_unlock(&iclog->ic_callback_lock);
		xlog_cil_process_committed(&पंचांगp);
		spin_lock(&iclog->ic_callback_lock);
	पूर्ण

	/*
	 * Pick up the icloglock जबतक still holding the callback lock so we
	 * serialise against anyone trying to add more callbacks to this iclog
	 * now we've finished processing.
	 */
	spin_lock(&log->l_icloglock);
	spin_unlock(&iclog->ic_callback_lock);
पूर्ण

STATIC व्योम
xlog_state_करो_callback(
	काष्ठा xlog		*log)
अणु
	काष्ठा xlog_in_core	*iclog;
	काष्ठा xlog_in_core	*first_iclog;
	bool			cycled_icloglock;
	bool			ioerror;
	पूर्णांक			flushcnt = 0;
	पूर्णांक			repeats = 0;

	spin_lock(&log->l_icloglock);
	करो अणु
		/*
		 * Scan all iclogs starting with the one poपूर्णांकed to by the
		 * log.  Reset this starting poपूर्णांक each समय the log is
		 * unlocked (during callbacks).
		 *
		 * Keep looping through iclogs until one full pass is made
		 * without running any callbacks.
		 */
		first_iclog = log->l_iclog;
		iclog = log->l_iclog;
		cycled_icloglock = false;
		ioerror = false;
		repeats++;

		करो अणु
			अगर (xlog_state_ioकरोne_process_iclog(log, iclog,
							&ioerror))
				अवरोध;

			अगर (iclog->ic_state != XLOG_STATE_CALLBACK &&
			    iclog->ic_state != XLOG_STATE_IOERROR) अणु
				iclog = iclog->ic_next;
				जारी;
			पूर्ण

			/*
			 * Running callbacks will drop the icloglock which means
			 * we'll have to run at least one more complete loop.
			 */
			cycled_icloglock = true;
			xlog_state_करो_iclog_callbacks(log, iclog);
			अगर (XLOG_FORCED_SHUTDOWN(log))
				wake_up_all(&iclog->ic_क्रमce_रुको);
			अन्यथा
				xlog_state_clean_iclog(log, iclog);
			iclog = iclog->ic_next;
		पूर्ण जबतक (first_iclog != iclog);

		अगर (repeats > 5000) अणु
			flushcnt += repeats;
			repeats = 0;
			xfs_warn(log->l_mp,
				"%s: possible infinite loop (%d iterations)",
				__func__, flushcnt);
		पूर्ण
	पूर्ण जबतक (!ioerror && cycled_icloglock);

	अगर (log->l_iclog->ic_state == XLOG_STATE_ACTIVE ||
	    log->l_iclog->ic_state == XLOG_STATE_IOERROR)
		wake_up_all(&log->l_flush_रुको);

	spin_unlock(&log->l_icloglock);
पूर्ण


/*
 * Finish transitioning this iclog to the dirty state.
 *
 * Make sure that we completely execute this routine only when this is
 * the last call to the iclog.  There is a good chance that iclog flushes,
 * when we reach the end of the physical log, get turned पूर्णांकo 2 separate
 * calls to bग_लिखो.  Hence, one iclog flush could generate two calls to this
 * routine.  By using the reference count bग_लिखोcnt, we guarantee that only
 * the second completion goes through.
 *
 * Callbacks could take समय, so they are करोne outside the scope of the
 * global state machine log lock.
 */
STATIC व्योम
xlog_state_करोne_syncing(
	काष्ठा xlog_in_core	*iclog)
अणु
	काष्ठा xlog		*log = iclog->ic_log;

	spin_lock(&log->l_icloglock);
	ASSERT(atomic_पढ़ो(&iclog->ic_refcnt) == 0);

	/*
	 * If we got an error, either on the first buffer, or in the हाल of
	 * split log ग_लिखोs, on the second, we shut करोwn the file प्रणाली and
	 * no iclogs should ever be attempted to be written to disk again.
	 */
	अगर (!XLOG_FORCED_SHUTDOWN(log)) अणु
		ASSERT(iclog->ic_state == XLOG_STATE_SYNCING);
		iclog->ic_state = XLOG_STATE_DONE_SYNC;
	पूर्ण

	/*
	 * Someone could be sleeping prior to writing out the next
	 * iclog buffer, we wake them all, one will get to करो the
	 * I/O, the others get to रुको क्रम the result.
	 */
	wake_up_all(&iclog->ic_ग_लिखो_रुको);
	spin_unlock(&log->l_icloglock);
	xlog_state_करो_callback(log);
पूर्ण

/*
 * If the head of the in-core log ring is not (ACTIVE or सूचीTY), then we must
 * sleep.  We रुको on the flush queue on the head iclog as that should be
 * the first iclog to complete flushing. Hence अगर all iclogs are syncing,
 * we will रुको here and all new ग_लिखोs will sleep until a sync completes.
 *
 * The in-core logs are used in a circular fashion. They are not used
 * out-of-order even when an iclog past the head is मुक्त.
 *
 * वापस:
 *	* log_offset where xlog_ग_लिखो() can start writing पूर्णांकo the in-core
 *		log's data space.
 *	* in-core log poपूर्णांकer to which xlog_ग_लिखो() should ग_लिखो.
 *	* boolean indicating this is a जारीd ग_लिखो to an in-core log.
 *		If this is the last ग_लिखो, then the in-core log's offset field
 *		needs to be incremented, depending on the amount of data which
 *		is copied.
 */
STATIC पूर्णांक
xlog_state_get_iclog_space(
	काष्ठा xlog		*log,
	पूर्णांक			len,
	काष्ठा xlog_in_core	**iclogp,
	काष्ठा xlog_ticket	*ticket,
	पूर्णांक			*जारीd_ग_लिखो,
	पूर्णांक			*logoffsetp)
अणु
	पूर्णांक		  log_offset;
	xlog_rec_header_t *head;
	xlog_in_core_t	  *iclog;

restart:
	spin_lock(&log->l_icloglock);
	अगर (XLOG_FORCED_SHUTDOWN(log)) अणु
		spin_unlock(&log->l_icloglock);
		वापस -EIO;
	पूर्ण

	iclog = log->l_iclog;
	अगर (iclog->ic_state != XLOG_STATE_ACTIVE) अणु
		XFS_STATS_INC(log->l_mp, xs_log_noiclogs);

		/* Wait क्रम log ग_लिखोs to have flushed */
		xlog_रुको(&log->l_flush_रुको, &log->l_icloglock);
		जाओ restart;
	पूर्ण

	head = &iclog->ic_header;

	atomic_inc(&iclog->ic_refcnt);	/* prevents sync */
	log_offset = iclog->ic_offset;

	/* On the 1st ग_लिखो to an iclog, figure out lsn.  This works
	 * अगर iclogs marked XLOG_STATE_WANT_SYNC always ग_लिखो out what they are
	 * committing to.  If the offset is set, that's how many blocks
	 * must be written.
	 */
	अगर (log_offset == 0) अणु
		ticket->t_curr_res -= log->l_iclog_hsize;
		xlog_tic_add_region(ticket,
				    log->l_iclog_hsize,
				    XLOG_REG_TYPE_LRHEADER);
		head->h_cycle = cpu_to_be32(log->l_curr_cycle);
		head->h_lsn = cpu_to_be64(
			xlog_assign_lsn(log->l_curr_cycle, log->l_curr_block));
		ASSERT(log->l_curr_block >= 0);
	पूर्ण

	/* If there is enough room to ग_लिखो everything, then करो it.  Otherwise,
	 * claim the rest of the region and make sure the XLOG_STATE_WANT_SYNC
	 * bit is on, so this will get flushed out.  Don't update ic_offset
	 * until you know exactly how many bytes get copied.  Thereक्रमe, रुको
	 * until later to update ic_offset.
	 *
	 * xlog_ग_लिखो() algorithm assumes that at least 2 xlog_op_header_t's
	 * can fit पूर्णांकo reमुख्यing data section.
	 */
	अगर (iclog->ic_size - iclog->ic_offset < 2*माप(xlog_op_header_t)) अणु
		पूर्णांक		error = 0;

		xlog_state_चयन_iclogs(log, iclog, iclog->ic_size);

		/*
		 * If we are the only one writing to this iclog, sync it to
		 * disk.  We need to करो an atomic compare and decrement here to
		 * aव्योम racing with concurrent atomic_dec_and_lock() calls in
		 * xlog_state_release_iclog() when there is more than one
		 * reference to the iclog.
		 */
		अगर (!atomic_add_unless(&iclog->ic_refcnt, -1, 1))
			error = xlog_state_release_iclog(log, iclog);
		spin_unlock(&log->l_icloglock);
		अगर (error)
			वापस error;
		जाओ restart;
	पूर्ण

	/* Do we have enough room to ग_लिखो the full amount in the reमुख्यder
	 * of this iclog?  Or must we जारी a ग_लिखो on the next iclog and
	 * mark this iclog as completely taken?  In the हाल where we चयन
	 * iclogs (to mark it taken), this particular iclog will release/sync
	 * to disk in xlog_ग_लिखो().
	 */
	अगर (len <= iclog->ic_size - iclog->ic_offset) अणु
		*जारीd_ग_लिखो = 0;
		iclog->ic_offset += len;
	पूर्ण अन्यथा अणु
		*जारीd_ग_लिखो = 1;
		xlog_state_चयन_iclogs(log, iclog, iclog->ic_size);
	पूर्ण
	*iclogp = iclog;

	ASSERT(iclog->ic_offset <= iclog->ic_size);
	spin_unlock(&log->l_icloglock);

	*logoffsetp = log_offset;
	वापस 0;
पूर्ण

/*
 * The first cnt-1 बार a ticket goes through here we करोn't need to move the
 * grant ग_लिखो head because the permanent reservation has reserved cnt बार the
 * unit amount.  Release part of current permanent unit reservation and reset
 * current reservation to be one units worth.  Also move grant reservation head
 * क्रमward.
 */
व्योम
xfs_log_ticket_regrant(
	काष्ठा xlog		*log,
	काष्ठा xlog_ticket	*ticket)
अणु
	trace_xfs_log_ticket_regrant(log, ticket);

	अगर (ticket->t_cnt > 0)
		ticket->t_cnt--;

	xlog_grant_sub_space(log, &log->l_reserve_head.grant,
					ticket->t_curr_res);
	xlog_grant_sub_space(log, &log->l_ग_लिखो_head.grant,
					ticket->t_curr_res);
	ticket->t_curr_res = ticket->t_unit_res;
	xlog_tic_reset_res(ticket);

	trace_xfs_log_ticket_regrant_sub(log, ticket);

	/* just वापस अगर we still have some of the pre-reserved space */
	अगर (!ticket->t_cnt) अणु
		xlog_grant_add_space(log, &log->l_reserve_head.grant,
				     ticket->t_unit_res);
		trace_xfs_log_ticket_regrant_निकास(log, ticket);

		ticket->t_curr_res = ticket->t_unit_res;
		xlog_tic_reset_res(ticket);
	पूर्ण

	xfs_log_ticket_put(ticket);
पूर्ण

/*
 * Give back the space left from a reservation.
 *
 * All the inक्रमmation we need to make a correct determination of space left
 * is present.  For non-permanent reservations, things are quite easy.  The
 * count should have been decremented to zero.  We only need to deal with the
 * space reमुख्यing in the current reservation part of the ticket.  If the
 * ticket contains a permanent reservation, there may be left over space which
 * needs to be released.  A count of N means that N-1 refills of the current
 * reservation can be करोne beक्रमe we need to ask क्रम more space.  The first
 * one goes to fill up the first current reservation.  Once we run out of
 * space, the count will stay at zero and the only space reमुख्यing will be
 * in the current reservation field.
 */
व्योम
xfs_log_ticket_ungrant(
	काष्ठा xlog		*log,
	काष्ठा xlog_ticket	*ticket)
अणु
	पूर्णांक			bytes;

	trace_xfs_log_ticket_ungrant(log, ticket);

	अगर (ticket->t_cnt > 0)
		ticket->t_cnt--;

	trace_xfs_log_ticket_ungrant_sub(log, ticket);

	/*
	 * If this is a permanent reservation ticket, we may be able to मुक्त
	 * up more space based on the reमुख्यing count.
	 */
	bytes = ticket->t_curr_res;
	अगर (ticket->t_cnt > 0) अणु
		ASSERT(ticket->t_flags & XLOG_TIC_PERM_RESERV);
		bytes += ticket->t_unit_res*ticket->t_cnt;
	पूर्ण

	xlog_grant_sub_space(log, &log->l_reserve_head.grant, bytes);
	xlog_grant_sub_space(log, &log->l_ग_लिखो_head.grant, bytes);

	trace_xfs_log_ticket_ungrant_निकास(log, ticket);

	xfs_log_space_wake(log->l_mp);
	xfs_log_ticket_put(ticket);
पूर्ण

/*
 * This routine will mark the current iclog in the ring as WANT_SYNC and move
 * the current iclog poपूर्णांकer to the next iclog in the ring.
 */
STATIC व्योम
xlog_state_चयन_iclogs(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			eventual_size)
अणु
	ASSERT(iclog->ic_state == XLOG_STATE_ACTIVE);
	निश्चित_spin_locked(&log->l_icloglock);

	अगर (!eventual_size)
		eventual_size = iclog->ic_offset;
	iclog->ic_state = XLOG_STATE_WANT_SYNC;
	iclog->ic_header.h_prev_block = cpu_to_be32(log->l_prev_block);
	log->l_prev_block = log->l_curr_block;
	log->l_prev_cycle = log->l_curr_cycle;

	/* roll log?: ic_offset changed later */
	log->l_curr_block += BTOBB(eventual_size)+BTOBB(log->l_iclog_hsize);

	/* Round up to next log-sunit */
	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb) &&
	    log->l_mp->m_sb.sb_logsunit > 1) अणु
		uपूर्णांक32_t sunit_bb = BTOBB(log->l_mp->m_sb.sb_logsunit);
		log->l_curr_block = roundup(log->l_curr_block, sunit_bb);
	पूर्ण

	अगर (log->l_curr_block >= log->l_logBBsize) अणु
		/*
		 * Rewind the current block beक्रमe the cycle is bumped to make
		 * sure that the combined LSN never transiently moves क्रमward
		 * when the log wraps to the next cycle. This is to support the
		 * unlocked sample of these fields from xlog_valid_lsn(). Most
		 * other हालs should acquire l_icloglock.
		 */
		log->l_curr_block -= log->l_logBBsize;
		ASSERT(log->l_curr_block >= 0);
		smp_wmb();
		log->l_curr_cycle++;
		अगर (log->l_curr_cycle == XLOG_HEADER_MAGIC_NUM)
			log->l_curr_cycle++;
	पूर्ण
	ASSERT(iclog == log->l_iclog);
	log->l_iclog = iclog->ic_next;
पूर्ण

/*
 * Write out all data in the in-core log as of this exact moment in समय.
 *
 * Data may be written to the in-core log during this call.  However,
 * we करोn't guarantee this data will be written out.  A change from past
 * implementation means this routine will *not* ग_लिखो out zero length LRs.
 *
 * Basically, we try and perक्रमm an पूर्णांकelligent scan of the in-core logs.
 * If we determine there is no flushable data, we just वापस.  There is no
 * flushable data अगर:
 *
 *	1. the current iclog is active and has no data; the previous iclog
 *		is in the active or dirty state.
 *	2. the current iclog is drity, and the previous iclog is in the
 *		active or dirty state.
 *
 * We may sleep अगर:
 *
 *	1. the current iclog is not in the active nor dirty state.
 *	2. the current iclog dirty, and the previous iclog is not in the
 *		active nor dirty state.
 *	3. the current iclog is active, and there is another thपढ़ो writing
 *		to this particular iclog.
 *	4. a) the current iclog is active and has no other ग_लिखोrs
 *	   b) when we वापस from flushing out this iclog, it is still
 *		not in the active nor dirty state.
 */
पूर्णांक
xfs_log_क्रमce(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक			flags)
अणु
	काष्ठा xlog		*log = mp->m_log;
	काष्ठा xlog_in_core	*iclog;
	xfs_lsn_t		lsn;

	XFS_STATS_INC(mp, xs_log_क्रमce);
	trace_xfs_log_क्रमce(mp, 0, _RET_IP_);

	xlog_cil_क्रमce(log);

	spin_lock(&log->l_icloglock);
	iclog = log->l_iclog;
	अगर (iclog->ic_state == XLOG_STATE_IOERROR)
		जाओ out_error;

	अगर (iclog->ic_state == XLOG_STATE_सूचीTY ||
	    (iclog->ic_state == XLOG_STATE_ACTIVE &&
	     atomic_पढ़ो(&iclog->ic_refcnt) == 0 && iclog->ic_offset == 0)) अणु
		/*
		 * If the head is dirty or (active and empty), then we need to
		 * look at the previous iclog.
		 *
		 * If the previous iclog is active or dirty we are करोne.  There
		 * is nothing to sync out. Otherwise, we attach ourselves to the
		 * previous iclog and go to sleep.
		 */
		iclog = iclog->ic_prev;
	पूर्ण अन्यथा अगर (iclog->ic_state == XLOG_STATE_ACTIVE) अणु
		अगर (atomic_पढ़ो(&iclog->ic_refcnt) == 0) अणु
			/*
			 * We are the only one with access to this iclog.
			 *
			 * Flush it out now.  There should be a rounकरोff of zero
			 * to show that someone has alपढ़ोy taken care of the
			 * rounकरोff from the previous sync.
			 */
			atomic_inc(&iclog->ic_refcnt);
			lsn = be64_to_cpu(iclog->ic_header.h_lsn);
			xlog_state_चयन_iclogs(log, iclog, 0);
			अगर (xlog_state_release_iclog(log, iclog))
				जाओ out_error;

			अगर (be64_to_cpu(iclog->ic_header.h_lsn) != lsn)
				जाओ out_unlock;
		पूर्ण अन्यथा अणु
			/*
			 * Someone अन्यथा is writing to this iclog.
			 *
			 * Use its call to flush out the data.  However, the
			 * other thपढ़ो may not क्रमce out this LR, so we mark
			 * it WANT_SYNC.
			 */
			xlog_state_चयन_iclogs(log, iclog, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If the head iclog is not active nor dirty, we just attach
		 * ourselves to the head and go to sleep अगर necessary.
		 */
		;
	पूर्ण

	अगर (flags & XFS_LOG_SYNC)
		वापस xlog_रुको_on_iclog(iclog);
out_unlock:
	spin_unlock(&log->l_icloglock);
	वापस 0;
out_error:
	spin_unlock(&log->l_icloglock);
	वापस -EIO;
पूर्ण

अटल पूर्णांक
__xfs_log_क्रमce_lsn(
	काष्ठा xfs_mount	*mp,
	xfs_lsn_t		lsn,
	uपूर्णांक			flags,
	पूर्णांक			*log_flushed,
	bool			alपढ़ोy_slept)
अणु
	काष्ठा xlog		*log = mp->m_log;
	काष्ठा xlog_in_core	*iclog;

	spin_lock(&log->l_icloglock);
	iclog = log->l_iclog;
	अगर (iclog->ic_state == XLOG_STATE_IOERROR)
		जाओ out_error;

	जबतक (be64_to_cpu(iclog->ic_header.h_lsn) != lsn) अणु
		iclog = iclog->ic_next;
		अगर (iclog == log->l_iclog)
			जाओ out_unlock;
	पूर्ण

	अगर (iclog->ic_state == XLOG_STATE_ACTIVE) अणु
		/*
		 * We sleep here अगर we haven't alपढ़ोy slept (e.g. this is the
		 * first समय we've looked at the correct iclog buf) and the
		 * buffer beक्रमe us is going to be sync'ed.  The reason क्रम this
		 * is that अगर we are करोing sync transactions here, by रुकोing
		 * क्रम the previous I/O to complete, we can allow a few more
		 * transactions पूर्णांकo this iclog beक्रमe we बंद it करोwn.
		 *
		 * Otherwise, we mark the buffer WANT_SYNC, and bump up the
		 * refcnt so we can release the log (which drops the ref count).
		 * The state चयन keeps new transaction commits from using
		 * this buffer.  When the current commits finish writing पूर्णांकo
		 * the buffer, the refcount will drop to zero and the buffer
		 * will go out then.
		 */
		अगर (!alपढ़ोy_slept &&
		    (iclog->ic_prev->ic_state == XLOG_STATE_WANT_SYNC ||
		     iclog->ic_prev->ic_state == XLOG_STATE_SYNCING)) अणु
			XFS_STATS_INC(mp, xs_log_क्रमce_sleep);

			xlog_रुको(&iclog->ic_prev->ic_ग_लिखो_रुको,
					&log->l_icloglock);
			वापस -EAGAIN;
		पूर्ण
		atomic_inc(&iclog->ic_refcnt);
		xlog_state_चयन_iclogs(log, iclog, 0);
		अगर (xlog_state_release_iclog(log, iclog))
			जाओ out_error;
		अगर (log_flushed)
			*log_flushed = 1;
	पूर्ण

	अगर (flags & XFS_LOG_SYNC)
		वापस xlog_रुको_on_iclog(iclog);
out_unlock:
	spin_unlock(&log->l_icloglock);
	वापस 0;
out_error:
	spin_unlock(&log->l_icloglock);
	वापस -EIO;
पूर्ण

/*
 * Force the in-core log to disk क्रम a specअगरic LSN.
 *
 * Find in-core log with lsn.
 *	If it is in the सूचीTY state, just वापस.
 *	If it is in the ACTIVE state, move the in-core log पूर्णांकo the WANT_SYNC
 *		state and go to sleep or वापस.
 *	If it is in any other state, go to sleep or वापस.
 *
 * Synchronous क्रमces are implemented with a रुको queue.  All callers trying
 * to क्रमce a given lsn to disk must रुको on the queue attached to the
 * specअगरic in-core log.  When given in-core log finally completes its ग_लिखो
 * to disk, that thपढ़ो will wake up all thपढ़ोs रुकोing on the queue.
 */
पूर्णांक
xfs_log_क्रमce_lsn(
	काष्ठा xfs_mount	*mp,
	xfs_lsn_t		lsn,
	uपूर्णांक			flags,
	पूर्णांक			*log_flushed)
अणु
	पूर्णांक			ret;
	ASSERT(lsn != 0);

	XFS_STATS_INC(mp, xs_log_क्रमce);
	trace_xfs_log_क्रमce(mp, lsn, _RET_IP_);

	lsn = xlog_cil_क्रमce_lsn(mp->m_log, lsn);
	अगर (lsn == शून्यCOMMITLSN)
		वापस 0;

	ret = __xfs_log_क्रमce_lsn(mp, lsn, flags, log_flushed, false);
	अगर (ret == -EAGAIN)
		ret = __xfs_log_क्रमce_lsn(mp, lsn, flags, log_flushed, true);
	वापस ret;
पूर्ण

/*
 * Free a used ticket when its refcount falls to zero.
 */
व्योम
xfs_log_ticket_put(
	xlog_ticket_t	*ticket)
अणु
	ASSERT(atomic_पढ़ो(&ticket->t_ref) > 0);
	अगर (atomic_dec_and_test(&ticket->t_ref))
		kmem_cache_मुक्त(xfs_log_ticket_zone, ticket);
पूर्ण

xlog_ticket_t *
xfs_log_ticket_get(
	xlog_ticket_t	*ticket)
अणु
	ASSERT(atomic_पढ़ो(&ticket->t_ref) > 0);
	atomic_inc(&ticket->t_ref);
	वापस ticket;
पूर्ण

/*
 * Figure out the total log space unit (in bytes) that would be
 * required क्रम a log ticket.
 */
पूर्णांक
xfs_log_calc_unit_res(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			unit_bytes)
अणु
	काष्ठा xlog		*log = mp->m_log;
	पूर्णांक			iclog_space;
	uपूर्णांक			num_headers;

	/*
	 * Permanent reservations have up to 'cnt'-1 active log operations
	 * in the log.  A unit in this हाल is the amount of space क्रम one
	 * of these log operations.  Normal reservations have a cnt of 1
	 * and their unit amount is the total amount of space required.
	 *
	 * The following lines of code account क्रम non-transaction data
	 * which occupy space in the on-disk log.
	 *
	 * Normal क्रमm of a transaction is:
	 * <oph><trans-hdr><start-oph><reg1-oph><reg1><reg2-oph>...<commit-oph>
	 * and then there are LR hdrs, split-recs and rounकरोff at end of syncs.
	 *
	 * We need to account क्रम all the leadup data and trailer data
	 * around the transaction data.
	 * And then we need to account क्रम the worst हाल in terms of using
	 * more space.
	 * The worst हाल will happen अगर:
	 * - the placement of the transaction happens to be such that the
	 *   rounकरोff is at its maximum
	 * - the transaction data is synced beक्रमe the commit record is synced
	 *   i.e. <transaction-data><rounकरोff> | <commit-rec><rounकरोff>
	 *   Thereक्रमe the commit record is in its own Log Record.
	 *   This can happen as the commit record is called with its
	 *   own region to xlog_ग_लिखो().
	 *   This then means that in the worst हाल, rounकरोff can happen क्रम
	 *   the commit-rec as well.
	 *   The commit-rec is smaller than padding in this scenario and so it is
	 *   not added separately.
	 */

	/* क्रम trans header */
	unit_bytes += माप(xlog_op_header_t);
	unit_bytes += माप(xfs_trans_header_t);

	/* क्रम start-rec */
	unit_bytes += माप(xlog_op_header_t);

	/*
	 * क्रम LR headers - the space क्रम data in an iclog is the size minus
	 * the space used क्रम the headers. If we use the iclog size, then we
	 * undercalculate the number of headers required.
	 *
	 * Furthermore - the addition of op headers क्रम split-recs might
	 * increase the space required enough to require more log and op
	 * headers, so take that पूर्णांकo account too.
	 *
	 * IMPORTANT: This reservation makes the assumption that अगर this
	 * transaction is the first in an iclog and hence has the LR headers
	 * accounted to it, then the reमुख्यing space in the iclog is
	 * exclusively क्रम this transaction.  i.e. अगर the transaction is larger
	 * than the iclog, it will be the only thing in that iclog.
	 * Fundamentally, this means we must pass the entire log vector to
	 * xlog_ग_लिखो to guarantee this.
	 */
	iclog_space = log->l_iclog_size - log->l_iclog_hsize;
	num_headers = howmany(unit_bytes, iclog_space);

	/* क्रम split-recs - ophdrs added when data split over LRs */
	unit_bytes += माप(xlog_op_header_t) * num_headers;

	/* add extra header reservations अगर we overrun */
	जबतक (!num_headers ||
	       howmany(unit_bytes, iclog_space) > num_headers) अणु
		unit_bytes += माप(xlog_op_header_t);
		num_headers++;
	पूर्ण
	unit_bytes += log->l_iclog_hsize * num_headers;

	/* क्रम commit-rec LR header - note: padding will subsume the ophdr */
	unit_bytes += log->l_iclog_hsize;

	/* क्रम rounकरोff padding क्रम transaction data and one क्रम commit record */
	अगर (xfs_sb_version_haslogv2(&mp->m_sb) && mp->m_sb.sb_logsunit > 1) अणु
		/* log su rounकरोff */
		unit_bytes += 2 * mp->m_sb.sb_logsunit;
	पूर्ण अन्यथा अणु
		/* BB rounकरोff */
		unit_bytes += 2 * BBSIZE;
        पूर्ण

	वापस unit_bytes;
पूर्ण

/*
 * Allocate and initialise a new log ticket.
 */
काष्ठा xlog_ticket *
xlog_ticket_alloc(
	काष्ठा xlog		*log,
	पूर्णांक			unit_bytes,
	पूर्णांक			cnt,
	अक्षर			client,
	bool			permanent)
अणु
	काष्ठा xlog_ticket	*tic;
	पूर्णांक			unit_res;

	tic = kmem_cache_zalloc(xfs_log_ticket_zone, GFP_NOFS | __GFP_NOFAIL);

	unit_res = xfs_log_calc_unit_res(log->l_mp, unit_bytes);

	atomic_set(&tic->t_ref, 1);
	tic->t_task		= current;
	INIT_LIST_HEAD(&tic->t_queue);
	tic->t_unit_res		= unit_res;
	tic->t_curr_res		= unit_res;
	tic->t_cnt		= cnt;
	tic->t_ocnt		= cnt;
	tic->t_tid		= pअक्रमom_u32();
	tic->t_clientid		= client;
	अगर (permanent)
		tic->t_flags |= XLOG_TIC_PERM_RESERV;

	xlog_tic_reset_res(tic);

	वापस tic;
पूर्ण

#अगर defined(DEBUG)
/*
 * Make sure that the destination ptr is within the valid data region of
 * one of the iclogs.  This uses backup poपूर्णांकers stored in a dअगरferent
 * part of the log in हाल we trash the log काष्ठाure.
 */
STATIC व्योम
xlog_verअगरy_dest_ptr(
	काष्ठा xlog	*log,
	व्योम		*ptr)
अणु
	पूर्णांक i;
	पूर्णांक good_ptr = 0;

	क्रम (i = 0; i < log->l_iclog_bufs; i++) अणु
		अगर (ptr >= log->l_iclog_bak[i] &&
		    ptr <= log->l_iclog_bak[i] + log->l_iclog_size)
			good_ptr++;
	पूर्ण

	अगर (!good_ptr)
		xfs_emerg(log->l_mp, "%s: invalid ptr", __func__);
पूर्ण

/*
 * Check to make sure the grant ग_लिखो head didn't just over lap the tail.  If
 * the cycles are the same, we can't be overlapping.  Otherwise, make sure that
 * the cycles dअगरfer by exactly one and check the byte count.
 *
 * This check is run unlocked, so can give false positives. Rather than निश्चित
 * on failures, use a warn-once flag and a panic tag to allow the admin to
 * determine अगर they want to panic the machine when such an error occurs. For
 * debug kernels this will have the same effect as using an निश्चित but, unlinke
 * an निश्चित, it can be turned off at runसमय.
 */
STATIC व्योम
xlog_verअगरy_grant_tail(
	काष्ठा xlog	*log)
अणु
	पूर्णांक		tail_cycle, tail_blocks;
	पूर्णांक		cycle, space;

	xlog_crack_grant_head(&log->l_ग_लिखो_head.grant, &cycle, &space);
	xlog_crack_atomic_lsn(&log->l_tail_lsn, &tail_cycle, &tail_blocks);
	अगर (tail_cycle != cycle) अणु
		अगर (cycle - 1 != tail_cycle &&
		    !(log->l_flags & XLOG_TAIL_WARN)) अणु
			xfs_alert_tag(log->l_mp, XFS_PTAG_LOGRES,
				"%s: cycle - 1 != tail_cycle", __func__);
			log->l_flags |= XLOG_TAIL_WARN;
		पूर्ण

		अगर (space > BBTOB(tail_blocks) &&
		    !(log->l_flags & XLOG_TAIL_WARN)) अणु
			xfs_alert_tag(log->l_mp, XFS_PTAG_LOGRES,
				"%s: space > BBTOB(tail_blocks)", __func__);
			log->l_flags |= XLOG_TAIL_WARN;
		पूर्ण
	पूर्ण
पूर्ण

/* check अगर it will fit */
STATIC व्योम
xlog_verअगरy_tail_lsn(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	xfs_lsn_t		tail_lsn)
अणु
    पूर्णांक blocks;

    अगर (CYCLE_LSN(tail_lsn) == log->l_prev_cycle) अणु
	blocks =
	    log->l_logBBsize - (log->l_prev_block - BLOCK_LSN(tail_lsn));
	अगर (blocks < BTOBB(iclog->ic_offset)+BTOBB(log->l_iclog_hsize))
		xfs_emerg(log->l_mp, "%s: ran out of log space", __func__);
    पूर्ण अन्यथा अणु
	ASSERT(CYCLE_LSN(tail_lsn)+1 == log->l_prev_cycle);

	अगर (BLOCK_LSN(tail_lsn) == log->l_prev_block)
		xfs_emerg(log->l_mp, "%s: tail wrapped", __func__);

	blocks = BLOCK_LSN(tail_lsn) - log->l_prev_block;
	अगर (blocks < BTOBB(iclog->ic_offset) + 1)
		xfs_emerg(log->l_mp, "%s: ran out of log space", __func__);
    पूर्ण
पूर्ण

/*
 * Perक्रमm a number of checks on the iclog beक्रमe writing to disk.
 *
 * 1. Make sure the iclogs are still circular
 * 2. Make sure we have a good magic number
 * 3. Make sure we करोn't have magic numbers in the data
 * 4. Check fields of each log operation header क्रम:
 *	A. Valid client identअगरier
 *	B. tid ptr value falls in valid ptr space (user space code)
 *	C. Length in log record header is correct according to the
 *		inभागidual operation headers within record.
 * 5. When a bग_लिखो will occur within 5 blocks of the front of the physical
 *	log, check the preceding blocks of the physical log to make sure all
 *	the cycle numbers agree with the current cycle number.
 */
STATIC व्योम
xlog_verअगरy_iclog(
	काष्ठा xlog		*log,
	काष्ठा xlog_in_core	*iclog,
	पूर्णांक			count)
अणु
	xlog_op_header_t	*ophead;
	xlog_in_core_t		*icptr;
	xlog_in_core_2_t	*xhdr;
	व्योम			*base_ptr, *ptr, *p;
	सूचक_भेद_प्रकार		field_offset;
	uपूर्णांक8_t			clientid;
	पूर्णांक			len, i, j, k, op_len;
	पूर्णांक			idx;

	/* check validity of iclog poपूर्णांकers */
	spin_lock(&log->l_icloglock);
	icptr = log->l_iclog;
	क्रम (i = 0; i < log->l_iclog_bufs; i++, icptr = icptr->ic_next)
		ASSERT(icptr);

	अगर (icptr != log->l_iclog)
		xfs_emerg(log->l_mp, "%s: corrupt iclog ring", __func__);
	spin_unlock(&log->l_icloglock);

	/* check log magic numbers */
	अगर (iclog->ic_header.h_magicno != cpu_to_be32(XLOG_HEADER_MAGIC_NUM))
		xfs_emerg(log->l_mp, "%s: invalid magic num", __func__);

	base_ptr = ptr = &iclog->ic_header;
	p = &iclog->ic_header;
	क्रम (ptr += BBSIZE; ptr < base_ptr + count; ptr += BBSIZE) अणु
		अगर (*(__be32 *)ptr == cpu_to_be32(XLOG_HEADER_MAGIC_NUM))
			xfs_emerg(log->l_mp, "%s: unexpected magic num",
				__func__);
	पूर्ण

	/* check fields */
	len = be32_to_cpu(iclog->ic_header.h_num_logops);
	base_ptr = ptr = iclog->ic_datap;
	ophead = ptr;
	xhdr = iclog->ic_data;
	क्रम (i = 0; i < len; i++) अणु
		ophead = ptr;

		/* clientid is only 1 byte */
		p = &ophead->oh_clientid;
		field_offset = p - base_ptr;
		अगर (field_offset & 0x1ff) अणु
			clientid = ophead->oh_clientid;
		पूर्ण अन्यथा अणु
			idx = BTOBBT((अक्षर *)&ophead->oh_clientid - iclog->ic_datap);
			अगर (idx >= (XLOG_HEADER_CYCLE_SIZE / BBSIZE)) अणु
				j = idx / (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
				k = idx % (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
				clientid = xlog_get_client_id(
					xhdr[j].hic_xheader.xh_cycle_data[k]);
			पूर्ण अन्यथा अणु
				clientid = xlog_get_client_id(
					iclog->ic_header.h_cycle_data[idx]);
			पूर्ण
		पूर्ण
		अगर (clientid != XFS_TRANSACTION && clientid != XFS_LOG)
			xfs_warn(log->l_mp,
				"%s: invalid clientid %d op "PTR_FMT" offset 0x%lx",
				__func__, clientid, ophead,
				(अचिन्हित दीर्घ)field_offset);

		/* check length */
		p = &ophead->oh_len;
		field_offset = p - base_ptr;
		अगर (field_offset & 0x1ff) अणु
			op_len = be32_to_cpu(ophead->oh_len);
		पूर्ण अन्यथा अणु
			idx = BTOBBT((uपूर्णांकptr_t)&ophead->oh_len -
				    (uपूर्णांकptr_t)iclog->ic_datap);
			अगर (idx >= (XLOG_HEADER_CYCLE_SIZE / BBSIZE)) अणु
				j = idx / (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
				k = idx % (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
				op_len = be32_to_cpu(xhdr[j].hic_xheader.xh_cycle_data[k]);
			पूर्ण अन्यथा अणु
				op_len = be32_to_cpu(iclog->ic_header.h_cycle_data[idx]);
			पूर्ण
		पूर्ण
		ptr += माप(xlog_op_header_t) + op_len;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * Mark all iclogs IOERROR. l_icloglock is held by the caller.
 */
STATIC पूर्णांक
xlog_state_ioerror(
	काष्ठा xlog	*log)
अणु
	xlog_in_core_t	*iclog, *ic;

	iclog = log->l_iclog;
	अगर (iclog->ic_state != XLOG_STATE_IOERROR) अणु
		/*
		 * Mark all the incore logs IOERROR.
		 * From now on, no log flushes will result.
		 */
		ic = iclog;
		करो अणु
			ic->ic_state = XLOG_STATE_IOERROR;
			ic = ic->ic_next;
		पूर्ण जबतक (ic != iclog);
		वापस 0;
	पूर्ण
	/*
	 * Return non-zero, अगर state transition has alपढ़ोy happened.
	 */
	वापस 1;
पूर्ण

/*
 * This is called from xfs_क्रमce_shutकरोwn, when we're क्रमcibly
 * shutting करोwn the fileप्रणाली, typically because of an IO error.
 * Our मुख्य objectives here are to make sure that:
 *	a. अगर !logerror, flush the logs to disk. Anything modअगरied
 *	   after this is ignored.
 *	b. the fileप्रणाली माला_लो marked 'SHUTDOWN' क्रम all पूर्णांकerested
 *	   parties to find out, 'atomically'.
 *	c. those who're sleeping on log reservations, pinned objects and
 *	    other resources get woken up, and be told the bad news.
 *	d. nothing new माला_लो queued up after (b) and (c) are करोne.
 *
 * Note: क्रम the !logerror हाल we need to flush the regions held in memory out
 * to disk first. This needs to be करोne beक्रमe the log is marked as shutकरोwn,
 * otherwise the iclog ग_लिखोs will fail.
 */
पूर्णांक
xfs_log_क्रमce_umount(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			logerror)
अणु
	काष्ठा xlog	*log;
	पूर्णांक		retval;

	log = mp->m_log;

	/*
	 * If this happens during log recovery, करोn't worry about
	 * locking; the log isn't खोलो क्रम business yet.
	 */
	अगर (!log ||
	    log->l_flags & XLOG_ACTIVE_RECOVERY) अणु
		mp->m_flags |= XFS_MOUNT_FS_SHUTDOWN;
		अगर (mp->m_sb_bp)
			mp->m_sb_bp->b_flags |= XBF_DONE;
		वापस 0;
	पूर्ण

	/*
	 * Somebody could've alपढ़ोy करोne the hard work क्रम us.
	 * No need to get locks क्रम this.
	 */
	अगर (logerror && log->l_iclog->ic_state == XLOG_STATE_IOERROR) अणु
		ASSERT(XLOG_FORCED_SHUTDOWN(log));
		वापस 1;
	पूर्ण

	/*
	 * Flush all the completed transactions to disk beक्रमe marking the log
	 * being shut करोwn. We need to करो it in this order to ensure that
	 * completed operations are safely on disk beक्रमe we shut करोwn, and that
	 * we करोn't have to issue any buffer IO after the shutकरोwn flags are set
	 * to guarantee this.
	 */
	अगर (!logerror)
		xfs_log_क्रमce(mp, XFS_LOG_SYNC);

	/*
	 * mark the fileप्रणाली and the as in a shutकरोwn state and wake
	 * everybody up to tell them the bad news.
	 */
	spin_lock(&log->l_icloglock);
	mp->m_flags |= XFS_MOUNT_FS_SHUTDOWN;
	अगर (mp->m_sb_bp)
		mp->m_sb_bp->b_flags |= XBF_DONE;

	/*
	 * Mark the log and the iclogs with IO error flags to prevent any
	 * further log IO from being issued or completed.
	 */
	log->l_flags |= XLOG_IO_ERROR;
	retval = xlog_state_ioerror(log);
	spin_unlock(&log->l_icloglock);

	/*
	 * We करोn't want anybody रुकोing क्रम log reservations after this. That
	 * means we have to wake up everybody queued up on reserveq as well as
	 * ग_लिखोq.  In addition, we make sure in xlog_अणुreपूर्णgrant_log_space that
	 * we करोn't enqueue anything once the SHUTDOWN flag is set, and this
	 * action is रक्षित by the grant locks.
	 */
	xlog_grant_head_wake_all(&log->l_reserve_head);
	xlog_grant_head_wake_all(&log->l_ग_लिखो_head);

	/*
	 * Wake up everybody रुकोing on xfs_log_क्रमce. Wake the CIL push first
	 * as अगर the log ग_लिखोs were completed. The पात handling in the log
	 * item committed callback functions will करो this again under lock to
	 * aव्योम races.
	 */
	spin_lock(&log->l_cilp->xc_push_lock);
	wake_up_all(&log->l_cilp->xc_commit_रुको);
	spin_unlock(&log->l_cilp->xc_push_lock);
	xlog_state_करो_callback(log);

	/* वापस non-zero अगर log IOERROR transition had alपढ़ोy happened */
	वापस retval;
पूर्ण

STATIC पूर्णांक
xlog_iclogs_empty(
	काष्ठा xlog	*log)
अणु
	xlog_in_core_t	*iclog;

	iclog = log->l_iclog;
	करो अणु
		/* endianness करोes not matter here, zero is zero in
		 * any language.
		 */
		अगर (iclog->ic_header.h_num_logops)
			वापस 0;
		iclog = iclog->ic_next;
	पूर्ण जबतक (iclog != log->l_iclog);
	वापस 1;
पूर्ण

/*
 * Verअगरy that an LSN stamped पूर्णांकo a piece of metadata is valid. This is
 * पूर्णांकended क्रम use in पढ़ो verअगरiers on v5 superblocks.
 */
bool
xfs_log_check_lsn(
	काष्ठा xfs_mount	*mp,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xlog		*log = mp->m_log;
	bool			valid;

	/*
	 * norecovery mode skips mount-समय log processing and unconditionally
	 * resets the in-core LSN. We can't validate in this mode, but
	 * modअगरications are not allowed anyways so just वापस true.
	 */
	अगर (mp->m_flags & XFS_MOUNT_NORECOVERY)
		वापस true;

	/*
	 * Some metadata LSNs are initialized to शून्य (e.g., the agfl). This is
	 * handled by recovery and thus safe to ignore here.
	 */
	अगर (lsn == शून्यCOMMITLSN)
		वापस true;

	valid = xlog_valid_lsn(mp->m_log, lsn);

	/* warn the user about what's gone wrong beक्रमe verअगरier failure */
	अगर (!valid) अणु
		spin_lock(&log->l_icloglock);
		xfs_warn(mp,
"Corruption warning: Metadata has LSN (%d:%d) ahead of current LSN (%d:%d). "
"Please unmount and run xfs_repair (>= v4.3) to resolve.",
			 CYCLE_LSN(lsn), BLOCK_LSN(lsn),
			 log->l_curr_cycle, log->l_curr_block);
		spin_unlock(&log->l_icloglock);
	पूर्ण

	वापस valid;
पूर्ण

bool
xfs_log_in_recovery(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xlog		*log = mp->m_log;

	वापस log->l_flags & XLOG_ACTIVE_RECOVERY;
पूर्ण
