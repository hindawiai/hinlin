<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_LOG_H__
#घोषणा __XFS_LOG_H__

काष्ठा xfs_cil_ctx;

काष्ठा xfs_log_vec अणु
	काष्ठा xfs_log_vec	*lv_next;	/* next lv in build list */
	पूर्णांक			lv_niovecs;	/* number of iovecs in lv */
	काष्ठा xfs_log_iovec	*lv_iovecp;	/* iovec array */
	काष्ठा xfs_log_item	*lv_item;	/* owner */
	अक्षर			*lv_buf;	/* क्रमmatted buffer */
	पूर्णांक			lv_bytes;	/* accounted space in buffer */
	पूर्णांक			lv_buf_len;	/* aligned size of buffer */
	पूर्णांक			lv_size;	/* size of allocated lv */
पूर्ण;

#घोषणा XFS_LOG_VEC_ORDERED	(-1)

अटल अंतरभूत व्योम *
xlog_prepare_iovec(काष्ठा xfs_log_vec *lv, काष्ठा xfs_log_iovec **vecp,
		uपूर्णांक type)
अणु
	काष्ठा xfs_log_iovec *vec = *vecp;

	अगर (vec) अणु
		ASSERT(vec - lv->lv_iovecp < lv->lv_niovecs);
		vec++;
	पूर्ण अन्यथा अणु
		vec = &lv->lv_iovecp[0];
	पूर्ण

	vec->i_type = type;
	vec->i_addr = lv->lv_buf + lv->lv_buf_len;

	ASSERT(IS_ALIGNED((अचिन्हित दीर्घ)vec->i_addr, माप(uपूर्णांक64_t)));

	*vecp = vec;
	वापस vec->i_addr;
पूर्ण

/*
 * We need to make sure the next buffer is naturally aligned क्रम the biggest
 * basic data type we put पूर्णांकo it.  We alपढ़ोy accounted क्रम this padding when
 * sizing the buffer.
 *
 * However, this padding करोes not get written पूर्णांकo the log, and hence we have to
 * track the space used by the log vectors separately to prevent log space hangs
 * due to inaccurate accounting (i.e. a leak) of the used log space through the
 * CIL context ticket.
 */
अटल अंतरभूत व्योम
xlog_finish_iovec(काष्ठा xfs_log_vec *lv, काष्ठा xfs_log_iovec *vec, पूर्णांक len)
अणु
	lv->lv_buf_len += round_up(len, माप(uपूर्णांक64_t));
	lv->lv_bytes += len;
	vec->i_len = len;
पूर्ण

अटल अंतरभूत व्योम *
xlog_copy_iovec(काष्ठा xfs_log_vec *lv, काष्ठा xfs_log_iovec **vecp,
		uपूर्णांक type, व्योम *data, पूर्णांक len)
अणु
	व्योम *buf;

	buf = xlog_prepare_iovec(lv, vecp, type);
	स_नकल(buf, data, len);
	xlog_finish_iovec(lv, *vecp, len);
	वापस buf;
पूर्ण

/*
 * By comparing each component, we करोn't have to worry about extra
 * endian issues in treating two 32 bit numbers as one 64 bit number
 */
अटल अंतरभूत xfs_lsn_t	_lsn_cmp(xfs_lsn_t lsn1, xfs_lsn_t lsn2)
अणु
	अगर (CYCLE_LSN(lsn1) != CYCLE_LSN(lsn2))
		वापस (CYCLE_LSN(lsn1)<CYCLE_LSN(lsn2))? -999 : 999;

	अगर (BLOCK_LSN(lsn1) != BLOCK_LSN(lsn2))
		वापस (BLOCK_LSN(lsn1)<BLOCK_LSN(lsn2))? -999 : 999;

	वापस 0;
पूर्ण

#घोषणा	XFS_LSN_CMP(x,y) _lsn_cmp(x,y)

/*
 * Flags to xfs_log_क्रमce()
 *
 *	XFS_LOG_SYNC:	Synchronous क्रमce in-core log to disk
 */
#घोषणा XFS_LOG_SYNC		0x1

/* Log manager पूर्णांकerfaces */
काष्ठा xfs_mount;
काष्ठा xlog_in_core;
काष्ठा xlog_ticket;
काष्ठा xfs_log_item;
काष्ठा xfs_item_ops;
काष्ठा xfs_trans;

पूर्णांक	  xfs_log_क्रमce(काष्ठा xfs_mount *mp, uपूर्णांक flags);
पूर्णांक	  xfs_log_क्रमce_lsn(काष्ठा xfs_mount *mp, xfs_lsn_t lsn, uपूर्णांक flags,
		पूर्णांक *log_क्रमced);
पूर्णांक	  xfs_log_mount(काष्ठा xfs_mount	*mp,
			काष्ठा xfs_buftarg	*log_target,
			xfs_daddr_t		start_block,
			पूर्णांक		 	num_bblocks);
पूर्णांक	  xfs_log_mount_finish(काष्ठा xfs_mount *mp);
व्योम	xfs_log_mount_cancel(काष्ठा xfs_mount *);
xfs_lsn_t xlog_assign_tail_lsn(काष्ठा xfs_mount *mp);
xfs_lsn_t xlog_assign_tail_lsn_locked(काष्ठा xfs_mount *mp);
व्योम	  xfs_log_space_wake(काष्ठा xfs_mount *mp);
व्योम	  xfs_log_release_iclog(काष्ठा xlog_in_core *iclog);
पूर्णांक	  xfs_log_reserve(काष्ठा xfs_mount *mp,
			  पूर्णांक		   length,
			  पूर्णांक		   count,
			  काष्ठा xlog_ticket **ticket,
			  uपूर्णांक8_t		   clientid,
			  bool		   permanent);
पूर्णांक	  xfs_log_regrant(काष्ठा xfs_mount *mp, काष्ठा xlog_ticket *tic);
व्योम      xfs_log_unmount(काष्ठा xfs_mount *mp);
पूर्णांक	  xfs_log_क्रमce_umount(काष्ठा xfs_mount *mp, पूर्णांक logerror);
bool	xfs_log_writable(काष्ठा xfs_mount *mp);

काष्ठा xlog_ticket *xfs_log_ticket_get(काष्ठा xlog_ticket *ticket);
व्योम	  xfs_log_ticket_put(काष्ठा xlog_ticket *ticket);

व्योम	xfs_log_commit_cil(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
				xfs_lsn_t *commit_lsn, bool regrant);
व्योम	xlog_cil_process_committed(काष्ठा list_head *list);
bool	xfs_log_item_in_current_chkpt(काष्ठा xfs_log_item *lip);

व्योम	xfs_log_work_queue(काष्ठा xfs_mount *mp);
पूर्णांक	xfs_log_quiesce(काष्ठा xfs_mount *mp);
व्योम	xfs_log_clean(काष्ठा xfs_mount *mp);
bool	xfs_log_check_lsn(काष्ठा xfs_mount *, xfs_lsn_t);
bool	xfs_log_in_recovery(काष्ठा xfs_mount *);

xfs_lsn_t xlog_grant_push_threshold(काष्ठा xlog *log, पूर्णांक need_bytes);

#पूर्ण_अगर	/* __XFS_LOG_H__ */
