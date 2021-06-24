<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_error.h"

पूर्णांक
xfs_calc_dquots_per_chunk(
	अचिन्हित पूर्णांक		nbblks)	/* basic block units */
अणु
	ASSERT(nbblks > 0);
	वापस BBTOB(nbblks) / माप(xfs_dqblk_t);
पूर्ण

/*
 * Do some primitive error checking on ondisk dquot data काष्ठाures.
 *
 * The xfs_dqblk काष्ठाure /contains/ the xfs_disk_dquot काष्ठाure;
 * we verअगरy them separately because at some poपूर्णांकs we have only the
 * smaller xfs_disk_dquot काष्ठाure available.
 */

xfs_failaddr_t
xfs_dquot_verअगरy(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_disk_dquot	*ddq,
	xfs_dqid_t		id)	/* used only during quotacheck */
अणु
	__u8			ddq_type;

	/*
	 * We can encounter an uninitialized dquot buffer क्रम 2 reasons:
	 * 1. If we crash जबतक deleting the quotainode(s), and those blks got
	 *    used क्रम user data. This is because we take the path of regular
	 *    file deletion; however, the size field of quotainodes is never
	 *    updated, so all the tricks that we play in itruncate_finish
	 *    करोn't quite matter.
	 *
	 * 2. We करोn't play the quota buffers when there's a quotaoff logitem.
	 *    But the allocation will be replayed so we'll end up with an
	 *    uninitialized quota block.
	 *
	 * This is all fine; things are still consistent, and we haven't lost
	 * any quota inक्रमmation. Just करोn't complain about bad dquot blks.
	 */
	अगर (ddq->d_magic != cpu_to_be16(XFS_DQUOT_MAGIC))
		वापस __this_address;
	अगर (ddq->d_version != XFS_DQUOT_VERSION)
		वापस __this_address;

	अगर (ddq->d_type & ~XFS_DQTYPE_ANY)
		वापस __this_address;
	ddq_type = ddq->d_type & XFS_DQTYPE_REC_MASK;
	अगर (ddq_type != XFS_DQTYPE_USER &&
	    ddq_type != XFS_DQTYPE_PROJ &&
	    ddq_type != XFS_DQTYPE_GROUP)
		वापस __this_address;

	अगर ((ddq->d_type & XFS_DQTYPE_BIGTIME) &&
	    !xfs_sb_version_hasbigसमय(&mp->m_sb))
		वापस __this_address;

	अगर ((ddq->d_type & XFS_DQTYPE_BIGTIME) && !ddq->d_id)
		वापस __this_address;

	अगर (id != -1 && id != be32_to_cpu(ddq->d_id))
		वापस __this_address;

	अगर (!ddq->d_id)
		वापस शून्य;

	अगर (ddq->d_blk_softlimit &&
	    be64_to_cpu(ddq->d_bcount) > be64_to_cpu(ddq->d_blk_softlimit) &&
	    !ddq->d_bसमयr)
		वापस __this_address;

	अगर (ddq->d_ino_softlimit &&
	    be64_to_cpu(ddq->d_icount) > be64_to_cpu(ddq->d_ino_softlimit) &&
	    !ddq->d_iसमयr)
		वापस __this_address;

	अगर (ddq->d_rtb_softlimit &&
	    be64_to_cpu(ddq->d_rtbcount) > be64_to_cpu(ddq->d_rtb_softlimit) &&
	    !ddq->d_rtbसमयr)
		वापस __this_address;

	वापस शून्य;
पूर्ण

xfs_failaddr_t
xfs_dqblk_verअगरy(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dqblk	*dqb,
	xfs_dqid_t		id)	/* used only during quotacheck */
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    !uuid_equal(&dqb->dd_uuid, &mp->m_sb.sb_meta_uuid))
		वापस __this_address;

	वापस xfs_dquot_verअगरy(mp, &dqb->dd_diskdq, id);
पूर्ण

/*
 * Do some primitive error checking on ondisk dquot data काष्ठाures.
 */
व्योम
xfs_dqblk_repair(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dqblk	*dqb,
	xfs_dqid_t		id,
	xfs_dqtype_t		type)
अणु
	/*
	 * Typically, a repair is only requested by quotacheck.
	 */
	ASSERT(id != -1);
	स_रखो(dqb, 0, माप(xfs_dqblk_t));

	dqb->dd_diskdq.d_magic = cpu_to_be16(XFS_DQUOT_MAGIC);
	dqb->dd_diskdq.d_version = XFS_DQUOT_VERSION;
	dqb->dd_diskdq.d_type = type;
	dqb->dd_diskdq.d_id = cpu_to_be32(id);

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		uuid_copy(&dqb->dd_uuid, &mp->m_sb.sb_meta_uuid);
		xfs_update_cksum((अक्षर *)dqb, माप(काष्ठा xfs_dqblk),
				 XFS_DQUOT_CRC_OFF);
	पूर्ण
पूर्ण

STATIC bool
xfs_dquot_buf_verअगरy_crc(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	bool			पढ़ोahead)
अणु
	काष्ठा xfs_dqblk	*d = (काष्ठा xfs_dqblk *)bp->b_addr;
	पूर्णांक			ndquots;
	पूर्णांक			i;

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस true;

	/*
	 * अगर we are in log recovery, the quota subप्रणाली has not been
	 * initialised so we have no quotainfo काष्ठाure. In that हाल, we need
	 * to manually calculate the number of dquots in the buffer.
	 */
	अगर (mp->m_quotainfo)
		ndquots = mp->m_quotainfo->qi_dqperchunk;
	अन्यथा
		ndquots = xfs_calc_dquots_per_chunk(bp->b_length);

	क्रम (i = 0; i < ndquots; i++, d++) अणु
		अगर (!xfs_verअगरy_cksum((अक्षर *)d, माप(काष्ठा xfs_dqblk),
				 XFS_DQUOT_CRC_OFF)) अणु
			अगर (!पढ़ोahead)
				xfs_buf_verअगरier_error(bp, -EFSBADCRC, __func__,
					d, माप(*d), __this_address);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

STATIC xfs_failaddr_t
xfs_dquot_buf_verअगरy(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	bool			पढ़ोahead)
अणु
	काष्ठा xfs_dqblk	*dqb = bp->b_addr;
	xfs_failaddr_t		fa;
	xfs_dqid_t		id = 0;
	पूर्णांक			ndquots;
	पूर्णांक			i;

	/*
	 * अगर we are in log recovery, the quota subप्रणाली has not been
	 * initialised so we have no quotainfo काष्ठाure. In that हाल, we need
	 * to manually calculate the number of dquots in the buffer.
	 */
	अगर (mp->m_quotainfo)
		ndquots = mp->m_quotainfo->qi_dqperchunk;
	अन्यथा
		ndquots = xfs_calc_dquots_per_chunk(bp->b_length);

	/*
	 * On the first पढ़ो of the buffer, verअगरy that each dquot is valid.
	 * We करोn't know what the id of the dquot is supposed to be, just that
	 * they should be increasing monotonically within the buffer. If the
	 * first id is corrupt, then it will fail on the second dquot in the
	 * buffer so corruptions could poपूर्णांक to the wrong dquot in this हाल.
	 */
	क्रम (i = 0; i < ndquots; i++) अणु
		काष्ठा xfs_disk_dquot	*ddq;

		ddq = &dqb[i].dd_diskdq;

		अगर (i == 0)
			id = be32_to_cpu(ddq->d_id);

		fa = xfs_dqblk_verअगरy(mp, &dqb[i], id + i);
		अगर (fa) अणु
			अगर (!पढ़ोahead)
				xfs_buf_verअगरier_error(bp, -EFSCORRUPTED,
					__func__, &dqb[i],
					माप(काष्ठा xfs_dqblk), fa);
			वापस fa;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल xfs_failaddr_t
xfs_dquot_buf_verअगरy_काष्ठा(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;

	वापस xfs_dquot_buf_verअगरy(mp, bp, false);
पूर्ण

अटल व्योम
xfs_dquot_buf_पढ़ो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;

	अगर (!xfs_dquot_buf_verअगरy_crc(mp, bp, false))
		वापस;
	xfs_dquot_buf_verअगरy(mp, bp, false);
पूर्ण

/*
 * पढ़ोahead errors are silent and simply leave the buffer as !करोne so a real
 * पढ़ो will then be run with the xfs_dquot_buf_ops verअगरier. See
 * xfs_inode_buf_verअगरy() क्रम why we use EIO and ~XBF_DONE here rather than
 * reporting the failure.
 */
अटल व्योम
xfs_dquot_buf_पढ़ोahead_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;

	अगर (!xfs_dquot_buf_verअगरy_crc(mp, bp, true) ||
	    xfs_dquot_buf_verअगरy(mp, bp, true) != शून्य) अणु
		xfs_buf_ioerror(bp, -EIO);
		bp->b_flags &= ~XBF_DONE;
	पूर्ण
पूर्ण

/*
 * we करोn't calculate the CRC here as that is करोne when the dquot is flushed to
 * the buffer after the update is करोne. This ensures that the dquot in the
 * buffer always has an up-to-date CRC value.
 */
अटल व्योम
xfs_dquot_buf_ग_लिखो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;

	xfs_dquot_buf_verअगरy(mp, bp, false);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_dquot_buf_ops = अणु
	.name = "xfs_dquot",
	.magic16 = अणु cpu_to_be16(XFS_DQUOT_MAGIC),
		     cpu_to_be16(XFS_DQUOT_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dquot_buf_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_dquot_buf_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_dquot_buf_verअगरy_काष्ठा,
पूर्ण;

स्थिर काष्ठा xfs_buf_ops xfs_dquot_buf_ra_ops = अणु
	.name = "xfs_dquot_ra",
	.magic16 = अणु cpu_to_be16(XFS_DQUOT_MAGIC),
		     cpu_to_be16(XFS_DQUOT_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dquot_buf_पढ़ोahead_verअगरy,
	.verअगरy_ग_लिखो = xfs_dquot_buf_ग_लिखो_verअगरy,
पूर्ण;

/* Convert an on-disk समयr value पूर्णांकo an incore समयr value. */
समय64_t
xfs_dquot_from_disk_ts(
	काष्ठा xfs_disk_dquot	*ddq,
	__be32			dसमयr)
अणु
	uपूर्णांक32_t		t = be32_to_cpu(dसमयr);

	अगर (t != 0 && (ddq->d_type & XFS_DQTYPE_BIGTIME))
		वापस xfs_dq_bigसमय_प्रकारo_unix(t);

	वापस t;
पूर्ण

/* Convert an incore समयr value पूर्णांकo an on-disk समयr value. */
__be32
xfs_dquot_to_disk_ts(
	काष्ठा xfs_dquot	*dqp,
	समय64_t		समयr)
अणु
	uपूर्णांक32_t		t = समयr;

	अगर (समयr != 0 && (dqp->q_type & XFS_DQTYPE_BIGTIME))
		t = xfs_dq_unix_to_bigसमय(समयr);

	वापस cpu_to_be32(t);
पूर्ण
