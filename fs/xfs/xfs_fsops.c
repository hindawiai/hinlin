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
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_error.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_fsops.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_log.h"
#समावेश "xfs_ag.h"
#समावेश "xfs_ag_resv.h"

/*
 * Write new AG headers to disk. Non-transactional, but need to be
 * written and completed prior to the growfs transaction being logged.
 * To करो this, we use a delayed ग_लिखो buffer list and रुको क्रम
 * submission and IO completion of the list as a whole. This allows the
 * IO subप्रणाली to merge all the AG headers in a single AG पूर्णांकo a single
 * IO and hide most of the latency of the IO from us.
 *
 * This also means that अगर we get an error whilst building the buffer
 * list to ग_लिखो, we can cancel the entire list without having written
 * anything.
 */
अटल पूर्णांक
xfs_resizefs_init_new_ags(
	काष्ठा xfs_trans	*tp,
	काष्ठा aghdr_init_data	*id,
	xfs_agnumber_t		oagcount,
	xfs_agnumber_t		nagcount,
	xfs_rfsblock_t		delta,
	bool			*lastag_extended)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	xfs_rfsblock_t		nb = mp->m_sb.sb_dblocks + delta;
	पूर्णांक			error;

	*lastag_extended = false;

	INIT_LIST_HEAD(&id->buffer_list);
	क्रम (id->agno = nagcount - 1;
	     id->agno >= oagcount;
	     id->agno--, delta -= id->agsize) अणु

		अगर (id->agno == nagcount - 1)
			id->agsize = nb - (id->agno *
					(xfs_rfsblock_t)mp->m_sb.sb_agblocks);
		अन्यथा
			id->agsize = mp->m_sb.sb_agblocks;

		error = xfs_ag_init_headers(mp, id);
		अगर (error) अणु
			xfs_buf_delwri_cancel(&id->buffer_list);
			वापस error;
		पूर्ण
	पूर्ण

	error = xfs_buf_delwri_submit(&id->buffer_list);
	अगर (error)
		वापस error;

	अगर (delta) अणु
		*lastag_extended = true;
		error = xfs_ag_extend_space(mp, tp, id, delta);
	पूर्ण
	वापस error;
पूर्ण

/*
 * growfs operations
 */
अटल पूर्णांक
xfs_growfs_data_निजी(
	काष्ठा xfs_mount	*mp,		/* mount poपूर्णांक क्रम fileप्रणाली */
	काष्ठा xfs_growfs_data	*in)		/* growfs data input काष्ठा */
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
	xfs_agnumber_t		nagcount;
	xfs_agnumber_t		nagimax = 0;
	xfs_rfsblock_t		nb, nb_भाग, nb_mod;
	पूर्णांक64_t			delta;
	bool			lastag_extended;
	xfs_agnumber_t		oagcount;
	काष्ठा xfs_trans	*tp;
	काष्ठा aghdr_init_data	id = अणुपूर्ण;

	nb = in->newblocks;
	error = xfs_sb_validate_fsb_count(&mp->m_sb, nb);
	अगर (error)
		वापस error;

	अगर (nb > mp->m_sb.sb_dblocks) अणु
		error = xfs_buf_पढ़ो_uncached(mp->m_ddev_targp,
				XFS_FSB_TO_BB(mp, nb) - XFS_FSS_TO_BB(mp, 1),
				XFS_FSS_TO_BB(mp, 1), 0, &bp, शून्य);
		अगर (error)
			वापस error;
		xfs_buf_rअन्यथा(bp);
	पूर्ण

	nb_भाग = nb;
	nb_mod = करो_भाग(nb_भाग, mp->m_sb.sb_agblocks);
	nagcount = nb_भाग + (nb_mod != 0);
	अगर (nb_mod && nb_mod < XFS_MIN_AG_BLOCKS) अणु
		nagcount--;
		nb = (xfs_rfsblock_t)nagcount * mp->m_sb.sb_agblocks;
	पूर्ण
	delta = nb - mp->m_sb.sb_dblocks;
	/*
	 * Reject fileप्रणालीs with a single AG because they are not
	 * supported, and reject a shrink operation that would cause a
	 * fileप्रणाली to become unsupported.
	 */
	अगर (delta < 0 && nagcount < 2)
		वापस -EINVAL;

	oagcount = mp->m_sb.sb_agcount;

	/* allocate the new per-ag काष्ठाures */
	अगर (nagcount > oagcount) अणु
		error = xfs_initialize_perag(mp, nagcount, &nagimax);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अगर (nagcount < oagcount) अणु
		/* TODO: shrinking the entire AGs hasn't yet completed */
		वापस -EINVAL;
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_growdata,
			(delta > 0 ? XFS_GROWFS_SPACE_RES(mp) : -delta), 0,
			XFS_TRANS_RESERVE, &tp);
	अगर (error)
		वापस error;

	अगर (delta > 0) अणु
		error = xfs_resizefs_init_new_ags(tp, &id, oagcount, nagcount,
						  delta, &lastag_extended);
	पूर्ण अन्यथा अणु
		अटल काष्ठा ratelimit_state shrink_warning = \
			RATELIMIT_STATE_INIT("shrink_warning", 86400 * HZ, 1);
		ratelimit_set_flags(&shrink_warning, RATELIMIT_MSG_ON_RELEASE);

		अगर (__ratelimit(&shrink_warning))
			xfs_alert(mp,
	"EXPERIMENTAL online shrink feature in use. Use at your own risk!");

		error = xfs_ag_shrink_space(mp, &tp, nagcount - 1, -delta);
	पूर्ण
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * Update changed superblock fields transactionally. These are not
	 * seen by the rest of the world until the transaction commit applies
	 * them atomically to the superblock.
	 */
	अगर (nagcount > oagcount)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_AGCOUNT, nagcount - oagcount);
	अगर (delta)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_DBLOCKS, delta);
	अगर (id.nमुक्त)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_FDBLOCKS, id.nमुक्त);

	/*
	 * Sync sb counters now to reflect the updated values. This is
	 * particularly important क्रम shrink because the ग_लिखो verअगरier
	 * will fail अगर sb_fdblocks is ever larger than sb_dblocks.
	 */
	अगर (xfs_sb_version_haslazysbcount(&mp->m_sb))
		xfs_log_sb(tp);

	xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);
	अगर (error)
		वापस error;

	/* New allocation groups fully initialized, so update mount काष्ठा */
	अगर (nagimax)
		mp->m_maxagi = nagimax;
	xfs_set_low_space_thresholds(mp);
	mp->m_alloc_set_aside = xfs_alloc_set_aside(mp);

	अगर (delta > 0) अणु
		/*
		 * If we expanded the last AG, मुक्त the per-AG reservation
		 * so we can reinitialize it with the new size.
		 */
		अगर (lastag_extended) अणु
			काष्ठा xfs_perag	*pag;

			pag = xfs_perag_get(mp, id.agno);
			error = xfs_ag_resv_मुक्त(pag);
			xfs_perag_put(pag);
			अगर (error)
				वापस error;
		पूर्ण
		/*
		 * Reserve AG metadata blocks. ENOSPC here करोes not mean there
		 * was a growfs failure, just that there still isn't space क्रम
		 * new user data after the grow has been run.
		 */
		error = xfs_fs_reserve_ag_blocks(mp);
		अगर (error == -ENOSPC)
			error = 0;
	पूर्ण
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_growfs_log_निजी(
	काष्ठा xfs_mount	*mp,	/* mount poपूर्णांक क्रम fileप्रणाली */
	काष्ठा xfs_growfs_log	*in)	/* growfs log input काष्ठा */
अणु
	xfs_extlen_t		nb;

	nb = in->newblocks;
	अगर (nb < XFS_MIN_LOG_BLOCKS || nb < XFS_B_TO_FSB(mp, XFS_MIN_LOG_BYTES))
		वापस -EINVAL;
	अगर (nb == mp->m_sb.sb_logblocks &&
	    in->isपूर्णांक == (mp->m_sb.sb_logstart != 0))
		वापस -EINVAL;
	/*
	 * Moving the log is hard, need new पूर्णांकerfaces to sync
	 * the log first, hold off all activity जबतक moving it.
	 * Can have लघुer or दीर्घer log in the same space,
	 * or transक्रमm पूर्णांकernal to बाह्यal log or vice versa.
	 */
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक
xfs_growfs_imaxpct(
	काष्ठा xfs_mount	*mp,
	__u32			imaxpct)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			dpct;
	पूर्णांक			error;

	अगर (imaxpct > 100)
		वापस -EINVAL;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_growdata,
			XFS_GROWFS_SPACE_RES(mp), 0, XFS_TRANS_RESERVE, &tp);
	अगर (error)
		वापस error;

	dpct = imaxpct - mp->m_sb.sb_imax_pct;
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_IMAXPCT, dpct);
	xfs_trans_set_sync(tp);
	वापस xfs_trans_commit(tp);
पूर्ण

/*
 * रक्षित versions of growfs function acquire and release locks on the mount
 * poपूर्णांक - exported through ioctls: XFS_IOC_FSGROWFSDATA, XFS_IOC_FSGROWFSLOG,
 * XFS_IOC_FSGROWFSRT
 */
पूर्णांक
xfs_growfs_data(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_growfs_data	*in)
अणु
	पूर्णांक			error = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!mutex_trylock(&mp->m_growlock))
		वापस -EWOULDBLOCK;

	/* update imaxpct separately to the physical grow of the fileप्रणाली */
	अगर (in->imaxpct != mp->m_sb.sb_imax_pct) अणु
		error = xfs_growfs_imaxpct(mp, in->imaxpct);
		अगर (error)
			जाओ out_error;
	पूर्ण

	अगर (in->newblocks != mp->m_sb.sb_dblocks) अणु
		error = xfs_growfs_data_निजी(mp, in);
		अगर (error)
			जाओ out_error;
	पूर्ण

	/* Post growfs calculations needed to reflect new state in operations */
	अगर (mp->m_sb.sb_imax_pct) अणु
		uपूर्णांक64_t icount = mp->m_sb.sb_dblocks * mp->m_sb.sb_imax_pct;
		करो_भाग(icount, 100);
		M_IGEO(mp)->maxicount = XFS_FSB_TO_INO(mp, icount);
	पूर्ण अन्यथा
		M_IGEO(mp)->maxicount = 0;

	/* Update secondary superblocks now the physical grow has completed */
	error = xfs_update_secondary_sbs(mp);

out_error:
	/*
	 * Increment the generation unconditionally, the error could be from
	 * updating the secondary superblocks, in which हाल the new size
	 * is live alपढ़ोy.
	 */
	mp->m_generation++;
	mutex_unlock(&mp->m_growlock);
	वापस error;
पूर्ण

पूर्णांक
xfs_growfs_log(
	xfs_mount_t		*mp,
	काष्ठा xfs_growfs_log	*in)
अणु
	पूर्णांक error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!mutex_trylock(&mp->m_growlock))
		वापस -EWOULDBLOCK;
	error = xfs_growfs_log_निजी(mp, in);
	mutex_unlock(&mp->m_growlock);
	वापस error;
पूर्ण

/*
 * exported through ioctl XFS_IOC_FSCOUNTS
 */

व्योम
xfs_fs_counts(
	xfs_mount_t		*mp,
	xfs_fsop_counts_t	*cnt)
अणु
	cnt->allocino = percpu_counter_पढ़ो_positive(&mp->m_icount);
	cnt->मुक्तino = percpu_counter_पढ़ो_positive(&mp->m_अगरree);
	cnt->मुक्तdata = percpu_counter_पढ़ो_positive(&mp->m_fdblocks) -
						mp->m_alloc_set_aside;

	spin_lock(&mp->m_sb_lock);
	cnt->मुक्तrtx = mp->m_sb.sb_frextents;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/*
 * exported through ioctl XFS_IOC_SET_RESBLKS & XFS_IOC_GET_RESBLKS
 *
 * xfs_reserve_blocks is called to set m_resblks
 * in the in-core mount table. The number of unused reserved blocks
 * is kept in m_resblks_avail.
 *
 * Reserve the requested number of blocks अगर available. Otherwise वापस
 * as many as possible to satisfy the request. The actual number
 * reserved are वापसed in outval
 *
 * A null inval poपूर्णांकer indicates that only the current reserved blocks
 * available  should  be वापसed no settings are changed.
 */

पूर्णांक
xfs_reserve_blocks(
	xfs_mount_t             *mp,
	uपूर्णांक64_t              *inval,
	xfs_fsop_resblks_t      *outval)
अणु
	पूर्णांक64_t			lcounter, delta;
	पूर्णांक64_t			fdblks_delta = 0;
	uपूर्णांक64_t		request;
	पूर्णांक64_t			मुक्त;
	पूर्णांक			error = 0;

	/* If inval is null, report current values and वापस */
	अगर (inval == (uपूर्णांक64_t *)शून्य) अणु
		अगर (!outval)
			वापस -EINVAL;
		outval->resblks = mp->m_resblks;
		outval->resblks_avail = mp->m_resblks_avail;
		वापस 0;
	पूर्ण

	request = *inval;

	/*
	 * With per-cpu counters, this becomes an पूर्णांकeresting problem. we need
	 * to work out अगर we are मुक्तing or allocation blocks first, then we can
	 * करो the modअगरication as necessary.
	 *
	 * We करो this under the m_sb_lock so that अगर we are near ENOSPC, we will
	 * hold out any changes जबतक we work out what to करो. This means that
	 * the amount of मुक्त space can change जबतक we करो this, so we need to
	 * retry अगर we end up trying to reserve more space than is available.
	 */
	spin_lock(&mp->m_sb_lock);

	/*
	 * If our previous reservation was larger than the current value,
	 * then move any unused blocks back to the मुक्त pool. Modअगरy the resblks
	 * counters directly since we shouldn't have any problems unreserving
	 * space.
	 */
	अगर (mp->m_resblks > request) अणु
		lcounter = mp->m_resblks_avail - request;
		अगर (lcounter  > 0) अणु		/* release unused blocks */
			fdblks_delta = lcounter;
			mp->m_resblks_avail -= lcounter;
		पूर्ण
		mp->m_resblks = request;
		अगर (fdblks_delta) अणु
			spin_unlock(&mp->m_sb_lock);
			error = xfs_mod_fdblocks(mp, fdblks_delta, 0);
			spin_lock(&mp->m_sb_lock);
		पूर्ण

		जाओ out;
	पूर्ण

	/*
	 * If the request is larger than the current reservation, reserve the
	 * blocks beक्रमe we update the reserve counters. Sample m_fdblocks and
	 * perक्रमm a partial reservation अगर the request exceeds मुक्त space.
	 */
	error = -ENOSPC;
	करो अणु
		मुक्त = percpu_counter_sum(&mp->m_fdblocks) -
						mp->m_alloc_set_aside;
		अगर (मुक्त <= 0)
			अवरोध;

		delta = request - mp->m_resblks;
		lcounter = मुक्त - delta;
		अगर (lcounter < 0)
			/* We can't satisfy the request, just get what we can */
			fdblks_delta = मुक्त;
		अन्यथा
			fdblks_delta = delta;

		/*
		 * We'll either succeed in getting space from the मुक्त block
		 * count or we'll get an ENOSPC. If we get a ENOSPC, it means
		 * things changed जबतक we were calculating fdblks_delta and so
		 * we should try again to see अगर there is anything left to
		 * reserve.
		 *
		 * Don't set the reserved flag here - we don't want to reserve
		 * the extra reserve blocks from the reserve.....
		 */
		spin_unlock(&mp->m_sb_lock);
		error = xfs_mod_fdblocks(mp, -fdblks_delta, 0);
		spin_lock(&mp->m_sb_lock);
	पूर्ण जबतक (error == -ENOSPC);

	/*
	 * Update the reserve counters अगर blocks have been successfully
	 * allocated.
	 */
	अगर (!error && fdblks_delta) अणु
		mp->m_resblks += fdblks_delta;
		mp->m_resblks_avail += fdblks_delta;
	पूर्ण

out:
	अगर (outval) अणु
		outval->resblks = mp->m_resblks;
		outval->resblks_avail = mp->m_resblks_avail;
	पूर्ण

	spin_unlock(&mp->m_sb_lock);
	वापस error;
पूर्ण

पूर्णांक
xfs_fs_goingकरोwn(
	xfs_mount_t	*mp,
	uपूर्णांक32_t	inflags)
अणु
	चयन (inflags) अणु
	हाल XFS_FSOP_GOING_FLAGS_DEFAULT: अणु
		अगर (!मुक्तze_bdev(mp->m_super->s_bdev)) अणु
			xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_FORCE_UMOUNT);
			thaw_bdev(mp->m_super->s_bdev);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल XFS_FSOP_GOING_FLAGS_LOGFLUSH:
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_FORCE_UMOUNT);
		अवरोध;
	हाल XFS_FSOP_GOING_FLAGS_NOLOGFLUSH:
		xfs_क्रमce_shutकरोwn(mp,
				SHUTDOWN_FORCE_UMOUNT | SHUTDOWN_LOG_IO_ERROR);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Force a shutकरोwn of the fileप्रणाली instantly जबतक keeping the fileप्रणाली
 * consistent. We करोn't करो an unmount here; just shutकरोwn the shop, make sure
 * that असलolutely nothing persistent happens to this fileप्रणाली after this
 * poपूर्णांक.
 */
व्योम
xfs_करो_क्रमce_shutकरोwn(
	काष्ठा xfs_mount *mp,
	पूर्णांक		flags,
	अक्षर		*fname,
	पूर्णांक		lnnum)
अणु
	bool		logerror = flags & SHUTDOWN_LOG_IO_ERROR;

	/*
	 * No need to duplicate efक्रमts.
	 */
	अगर (XFS_FORCED_SHUTDOWN(mp) && !logerror)
		वापस;

	/*
	 * This flags XFS_MOUNT_FS_SHUTDOWN, makes sure that we करोn't
	 * queue up anybody new on the log reservations, and wakes up
	 * everybody who's sleeping on log reservations to tell them
	 * the bad news.
	 */
	अगर (xfs_log_क्रमce_umount(mp, logerror))
		वापस;

	अगर (flags & SHUTDOWN_FORCE_UMOUNT) अणु
		xfs_alert(mp,
"User initiated shutdown received. Shutting down filesystem");
		वापस;
	पूर्ण

	xfs_notice(mp,
"%s(0x%x) called from line %d of file %s. Return address = "PTR_FMT,
		__func__, flags, lnnum, fname, __वापस_address);

	अगर (flags & SHUTDOWN_CORRUPT_INCORE) अणु
		xfs_alert_tag(mp, XFS_PTAG_SHUTDOWN_CORRUPT,
"Corruption of in-memory data detected.  Shutting down filesystem");
		अगर (XFS_ERRLEVEL_HIGH <= xfs_error_level)
			xfs_stack_trace();
	पूर्ण अन्यथा अगर (logerror) अणु
		xfs_alert_tag(mp, XFS_PTAG_SHUTDOWN_LOGERROR,
			"Log I/O Error Detected. Shutting down filesystem");
	पूर्ण अन्यथा अणु
		xfs_alert_tag(mp, XFS_PTAG_SHUTDOWN_IOERROR,
			"I/O Error Detected. Shutting down filesystem");
	पूर्ण

	xfs_alert(mp,
		"Please unmount the filesystem and rectify the problem(s)");
पूर्ण

/*
 * Reserve मुक्त space क्रम per-AG metadata.
 */
पूर्णांक
xfs_fs_reserve_ag_blocks(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_agnumber_t		agno;
	काष्ठा xfs_perag	*pag;
	पूर्णांक			error = 0;
	पूर्णांक			err2;

	mp->m_finobt_nores = false;
	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		pag = xfs_perag_get(mp, agno);
		err2 = xfs_ag_resv_init(pag, शून्य);
		xfs_perag_put(pag);
		अगर (err2 && !error)
			error = err2;
	पूर्ण

	अगर (error && error != -ENOSPC) अणु
		xfs_warn(mp,
	"Error %d reserving per-AG metadata reserve pool.", error);
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Free space reserved क्रम per-AG metadata.
 */
पूर्णांक
xfs_fs_unreserve_ag_blocks(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_agnumber_t		agno;
	काष्ठा xfs_perag	*pag;
	पूर्णांक			error = 0;
	पूर्णांक			err2;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		pag = xfs_perag_get(mp, agno);
		err2 = xfs_ag_resv_मुक्त(pag);
		xfs_perag_put(pag);
		अगर (err2 && !error)
			error = err2;
	पूर्ण

	अगर (error)
		xfs_warn(mp,
	"Error %d freeing per-AG metadata reserve pool.", error);

	वापस error;
पूर्ण
