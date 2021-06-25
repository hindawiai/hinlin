<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_health.h"

/*
 * Warn about metadata corruption that we detected but haven't fixed, and
 * make sure we're not sitting on anything that would get in the way of
 * recovery.
 */
व्योम
xfs_health_unmount(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		agno;
	अचिन्हित पूर्णांक		sick = 0;
	अचिन्हित पूर्णांक		checked = 0;
	bool			warn = false;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस;

	/* Measure AG corruption levels. */
	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		pag = xfs_perag_get(mp, agno);
		xfs_ag_measure_sickness(pag, &sick, &checked);
		अगर (sick) अणु
			trace_xfs_ag_unfixed_corruption(mp, agno, sick);
			warn = true;
		पूर्ण
		xfs_perag_put(pag);
	पूर्ण

	/* Measure realसमय volume corruption levels. */
	xfs_rt_measure_sickness(mp, &sick, &checked);
	अगर (sick) अणु
		trace_xfs_rt_unfixed_corruption(mp, sick);
		warn = true;
	पूर्ण

	/*
	 * Measure fs corruption and keep the sample around क्रम the warning.
	 * See the note below क्रम why we exempt FS_COUNTERS.
	 */
	xfs_fs_measure_sickness(mp, &sick, &checked);
	अगर (sick & ~XFS_SICK_FS_COUNTERS) अणु
		trace_xfs_fs_unfixed_corruption(mp, sick);
		warn = true;
	पूर्ण

	अगर (warn) अणु
		xfs_warn(mp,
"Uncorrected metadata errors detected; please run xfs_repair.");

		/*
		 * We discovered uncorrected metadata problems at some poपूर्णांक
		 * during this fileप्रणाली mount and have advised the
		 * administrator to run repair once the unmount completes.
		 *
		 * However, we must be careful -- when FSCOUNTERS are flagged
		 * unhealthy, the unmount procedure omits writing the clean
		 * unmount record to the log so that the next mount will run
		 * recovery and recompute the summary counters.  In other
		 * words, we leave a dirty log to get the counters fixed.
		 *
		 * Unक्रमtunately, xfs_repair cannot recover dirty logs, so अगर
		 * there were fileप्रणाली problems, FSCOUNTERS was flagged, and
		 * the administrator takes our advice to run xfs_repair,
		 * they'll have to zap the log beक्रमe repairing काष्ठाures.
		 * We करोn't really want to encourage this, so we mark the
		 * FSCOUNTERS healthy so that a subsequent repair run won't see
		 * a dirty log.
		 */
		अगर (sick & XFS_SICK_FS_COUNTERS)
			xfs_fs_mark_healthy(mp, XFS_SICK_FS_COUNTERS);
	पूर्ण
पूर्ण

/* Mark unhealthy per-fs metadata. */
व्योम
xfs_fs_mark_sick(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_FS_PRIMARY));
	trace_xfs_fs_mark_sick(mp, mask);

	spin_lock(&mp->m_sb_lock);
	mp->m_fs_sick |= mask;
	mp->m_fs_checked |= mask;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/* Mark a per-fs metadata healed. */
व्योम
xfs_fs_mark_healthy(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_FS_PRIMARY));
	trace_xfs_fs_mark_healthy(mp, mask);

	spin_lock(&mp->m_sb_lock);
	mp->m_fs_sick &= ~mask;
	mp->m_fs_checked |= mask;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/* Sample which per-fs metadata are unhealthy. */
व्योम
xfs_fs_measure_sickness(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		*sick,
	अचिन्हित पूर्णांक		*checked)
अणु
	spin_lock(&mp->m_sb_lock);
	*sick = mp->m_fs_sick;
	*checked = mp->m_fs_checked;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/* Mark unhealthy realसमय metadata. */
व्योम
xfs_rt_mark_sick(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_RT_PRIMARY));
	trace_xfs_rt_mark_sick(mp, mask);

	spin_lock(&mp->m_sb_lock);
	mp->m_rt_sick |= mask;
	mp->m_rt_checked |= mask;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/* Mark a realसमय metadata healed. */
व्योम
xfs_rt_mark_healthy(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_RT_PRIMARY));
	trace_xfs_rt_mark_healthy(mp, mask);

	spin_lock(&mp->m_sb_lock);
	mp->m_rt_sick &= ~mask;
	mp->m_rt_checked |= mask;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/* Sample which realसमय metadata are unhealthy. */
व्योम
xfs_rt_measure_sickness(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		*sick,
	अचिन्हित पूर्णांक		*checked)
अणु
	spin_lock(&mp->m_sb_lock);
	*sick = mp->m_rt_sick;
	*checked = mp->m_rt_checked;
	spin_unlock(&mp->m_sb_lock);
पूर्ण

/* Mark unhealthy per-ag metadata. */
व्योम
xfs_ag_mark_sick(
	काष्ठा xfs_perag	*pag,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_AG_PRIMARY));
	trace_xfs_ag_mark_sick(pag->pag_mount, pag->pag_agno, mask);

	spin_lock(&pag->pag_state_lock);
	pag->pag_sick |= mask;
	pag->pag_checked |= mask;
	spin_unlock(&pag->pag_state_lock);
पूर्ण

/* Mark per-ag metadata ok. */
व्योम
xfs_ag_mark_healthy(
	काष्ठा xfs_perag	*pag,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_AG_PRIMARY));
	trace_xfs_ag_mark_healthy(pag->pag_mount, pag->pag_agno, mask);

	spin_lock(&pag->pag_state_lock);
	pag->pag_sick &= ~mask;
	pag->pag_checked |= mask;
	spin_unlock(&pag->pag_state_lock);
पूर्ण

/* Sample which per-ag metadata are unhealthy. */
व्योम
xfs_ag_measure_sickness(
	काष्ठा xfs_perag	*pag,
	अचिन्हित पूर्णांक		*sick,
	अचिन्हित पूर्णांक		*checked)
अणु
	spin_lock(&pag->pag_state_lock);
	*sick = pag->pag_sick;
	*checked = pag->pag_checked;
	spin_unlock(&pag->pag_state_lock);
पूर्ण

/* Mark the unhealthy parts of an inode. */
व्योम
xfs_inode_mark_sick(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_INO_PRIMARY));
	trace_xfs_inode_mark_sick(ip, mask);

	spin_lock(&ip->i_flags_lock);
	ip->i_sick |= mask;
	ip->i_checked |= mask;
	spin_unlock(&ip->i_flags_lock);
पूर्ण

/* Mark parts of an inode healed. */
व्योम
xfs_inode_mark_healthy(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		mask)
अणु
	ASSERT(!(mask & ~XFS_SICK_INO_PRIMARY));
	trace_xfs_inode_mark_healthy(ip, mask);

	spin_lock(&ip->i_flags_lock);
	ip->i_sick &= ~mask;
	ip->i_checked |= mask;
	spin_unlock(&ip->i_flags_lock);
पूर्ण

/* Sample which parts of an inode are unhealthy. */
व्योम
xfs_inode_measure_sickness(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		*sick,
	अचिन्हित पूर्णांक		*checked)
अणु
	spin_lock(&ip->i_flags_lock);
	*sick = ip->i_sick;
	*checked = ip->i_checked;
	spin_unlock(&ip->i_flags_lock);
पूर्ण

/* Mappings between पूर्णांकernal sick masks and ioctl sick masks. */

काष्ठा ioctl_sick_map अणु
	अचिन्हित पूर्णांक		sick_mask;
	अचिन्हित पूर्णांक		ioctl_mask;
पूर्ण;

अटल स्थिर काष्ठा ioctl_sick_map fs_map[] = अणु
	अणु XFS_SICK_FS_COUNTERS,	XFS_FSOP_GEOM_SICK_COUNTERSपूर्ण,
	अणु XFS_SICK_FS_UQUOTA,	XFS_FSOP_GEOM_SICK_UQUOTA पूर्ण,
	अणु XFS_SICK_FS_GQUOTA,	XFS_FSOP_GEOM_SICK_GQUOTA पूर्ण,
	अणु XFS_SICK_FS_PQUOTA,	XFS_FSOP_GEOM_SICK_PQUOTA पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ioctl_sick_map rt_map[] = अणु
	अणु XFS_SICK_RT_BITMAP,	XFS_FSOP_GEOM_SICK_RT_BITMAP पूर्ण,
	अणु XFS_SICK_RT_SUMMARY,	XFS_FSOP_GEOM_SICK_RT_SUMMARY पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम
xfgeo_health_tick(
	काष्ठा xfs_fsop_geom		*geo,
	अचिन्हित पूर्णांक			sick,
	अचिन्हित पूर्णांक			checked,
	स्थिर काष्ठा ioctl_sick_map	*m)
अणु
	अगर (checked & m->sick_mask)
		geo->checked |= m->ioctl_mask;
	अगर (sick & m->sick_mask)
		geo->sick |= m->ioctl_mask;
पूर्ण

/* Fill out fs geometry health info. */
व्योम
xfs_fsop_geom_health(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_fsop_geom		*geo)
अणु
	स्थिर काष्ठा ioctl_sick_map	*m;
	अचिन्हित पूर्णांक			sick;
	अचिन्हित पूर्णांक			checked;

	geo->sick = 0;
	geo->checked = 0;

	xfs_fs_measure_sickness(mp, &sick, &checked);
	क्रम (m = fs_map; m->sick_mask; m++)
		xfgeo_health_tick(geo, sick, checked, m);

	xfs_rt_measure_sickness(mp, &sick, &checked);
	क्रम (m = rt_map; m->sick_mask; m++)
		xfgeo_health_tick(geo, sick, checked, m);
पूर्ण

अटल स्थिर काष्ठा ioctl_sick_map ag_map[] = अणु
	अणु XFS_SICK_AG_SB,	XFS_AG_GEOM_SICK_SB पूर्ण,
	अणु XFS_SICK_AG_AGF,	XFS_AG_GEOM_SICK_AGF पूर्ण,
	अणु XFS_SICK_AG_AGFL,	XFS_AG_GEOM_SICK_AGFL पूर्ण,
	अणु XFS_SICK_AG_AGI,	XFS_AG_GEOM_SICK_AGI पूर्ण,
	अणु XFS_SICK_AG_BNOBT,	XFS_AG_GEOM_SICK_BNOBT पूर्ण,
	अणु XFS_SICK_AG_CNTBT,	XFS_AG_GEOM_SICK_CNTBT पूर्ण,
	अणु XFS_SICK_AG_INOBT,	XFS_AG_GEOM_SICK_INOBT पूर्ण,
	अणु XFS_SICK_AG_FINOBT,	XFS_AG_GEOM_SICK_FINOBT पूर्ण,
	अणु XFS_SICK_AG_RMAPBT,	XFS_AG_GEOM_SICK_RMAPBT पूर्ण,
	अणु XFS_SICK_AG_REFCNTBT,	XFS_AG_GEOM_SICK_REFCNTBT पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

/* Fill out ag geometry health info. */
व्योम
xfs_ag_geom_health(
	काष्ठा xfs_perag		*pag,
	काष्ठा xfs_ag_geometry		*ageo)
अणु
	स्थिर काष्ठा ioctl_sick_map	*m;
	अचिन्हित पूर्णांक			sick;
	अचिन्हित पूर्णांक			checked;

	ageo->ag_sick = 0;
	ageo->ag_checked = 0;

	xfs_ag_measure_sickness(pag, &sick, &checked);
	क्रम (m = ag_map; m->sick_mask; m++) अणु
		अगर (checked & m->sick_mask)
			ageo->ag_checked |= m->ioctl_mask;
		अगर (sick & m->sick_mask)
			ageo->ag_sick |= m->ioctl_mask;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ioctl_sick_map ino_map[] = अणु
	अणु XFS_SICK_INO_CORE,	XFS_BS_SICK_INODE पूर्ण,
	अणु XFS_SICK_INO_BMBTD,	XFS_BS_SICK_BMBTD पूर्ण,
	अणु XFS_SICK_INO_BMBTA,	XFS_BS_SICK_BMBTA पूर्ण,
	अणु XFS_SICK_INO_BMBTC,	XFS_BS_SICK_BMBTC पूर्ण,
	अणु XFS_SICK_INO_सूची,	XFS_BS_SICK_सूची पूर्ण,
	अणु XFS_SICK_INO_XATTR,	XFS_BS_SICK_XATTR पूर्ण,
	अणु XFS_SICK_INO_SYMLINK,	XFS_BS_SICK_SYMLINK पूर्ण,
	अणु XFS_SICK_INO_PARENT,	XFS_BS_SICK_PARENT पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

/* Fill out bulkstat health info. */
व्योम
xfs_bulkstat_health(
	काष्ठा xfs_inode		*ip,
	काष्ठा xfs_bulkstat		*bs)
अणु
	स्थिर काष्ठा ioctl_sick_map	*m;
	अचिन्हित पूर्णांक			sick;
	अचिन्हित पूर्णांक			checked;

	bs->bs_sick = 0;
	bs->bs_checked = 0;

	xfs_inode_measure_sickness(ip, &sick, &checked);
	क्रम (m = ino_map; m->sick_mask; m++) अणु
		अगर (checked & m->sick_mask)
			bs->bs_checked |= m->ioctl_mask;
		अगर (sick & m->sick_mask)
			bs->bs_sick |= m->ioctl_mask;
	पूर्ण
पूर्ण
