<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/kसमय.स>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "log.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "recovery.h"
#समावेश "super.h"
#समावेश "util.h"
#समावेश "dir.h"

काष्ठा workqueue_काष्ठा *gfs_recovery_wq;

पूर्णांक gfs2_replay_पढ़ो_block(काष्ठा gfs2_jdesc *jd, अचिन्हित पूर्णांक blk,
			   काष्ठा buffer_head **bh)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	u64 dblock;
	u32 extlen;
	पूर्णांक error;

	extlen = 32;
	error = gfs2_get_extent(&ip->i_inode, blk, &dblock, &extlen);
	अगर (error)
		वापस error;
	अगर (!dblock) अणु
		gfs2_consist_inode(ip);
		वापस -EIO;
	पूर्ण

	*bh = gfs2_meta_ra(gl, dblock, extlen);

	वापस error;
पूर्ण

पूर्णांक gfs2_revoke_add(काष्ठा gfs2_jdesc *jd, u64 blkno, अचिन्हित पूर्णांक where)
अणु
	काष्ठा list_head *head = &jd->jd_revoke_list;
	काष्ठा gfs2_revoke_replay *rr;
	पूर्णांक found = 0;

	list_क्रम_each_entry(rr, head, rr_list) अणु
		अगर (rr->rr_blkno == blkno) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		rr->rr_where = where;
		वापस 0;
	पूर्ण

	rr = kदो_स्मृति(माप(काष्ठा gfs2_revoke_replay), GFP_NOFS);
	अगर (!rr)
		वापस -ENOMEM;

	rr->rr_blkno = blkno;
	rr->rr_where = where;
	list_add(&rr->rr_list, head);

	वापस 1;
पूर्ण

पूर्णांक gfs2_revoke_check(काष्ठा gfs2_jdesc *jd, u64 blkno, अचिन्हित पूर्णांक where)
अणु
	काष्ठा gfs2_revoke_replay *rr;
	पूर्णांक wrap, a, b, revoke;
	पूर्णांक found = 0;

	list_क्रम_each_entry(rr, &jd->jd_revoke_list, rr_list) अणु
		अगर (rr->rr_blkno == blkno) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस 0;

	wrap = (rr->rr_where < jd->jd_replay_tail);
	a = (jd->jd_replay_tail < where);
	b = (where < rr->rr_where);
	revoke = (wrap) ? (a || b) : (a && b);

	वापस revoke;
पूर्ण

व्योम gfs2_revoke_clean(काष्ठा gfs2_jdesc *jd)
अणु
	काष्ठा list_head *head = &jd->jd_revoke_list;
	काष्ठा gfs2_revoke_replay *rr;

	जबतक (!list_empty(head)) अणु
		rr = list_first_entry(head, काष्ठा gfs2_revoke_replay, rr_list);
		list_del(&rr->rr_list);
		kमुक्त(rr);
	पूर्ण
पूर्ण

पूर्णांक __get_log_header(काष्ठा gfs2_sbd *sdp, स्थिर काष्ठा gfs2_log_header *lh,
		     अचिन्हित पूर्णांक blkno, काष्ठा gfs2_log_header_host *head)
अणु
	u32 hash, crc;

	अगर (lh->lh_header.mh_magic != cpu_to_be32(GFS2_MAGIC) ||
	    lh->lh_header.mh_type != cpu_to_be32(GFS2_METATYPE_LH) ||
	    (blkno && be32_to_cpu(lh->lh_blkno) != blkno))
		वापस 1;

	hash = crc32(~0, lh, LH_V1_SIZE - 4);
	hash = ~crc32_le_shअगरt(hash, 4); /* assume lh_hash is zero */

	अगर (be32_to_cpu(lh->lh_hash) != hash)
		वापस 1;

	crc = crc32c(~0, (व्योम *)lh + LH_V1_SIZE + 4,
		     sdp->sd_sb.sb_bsize - LH_V1_SIZE - 4);

	अगर ((lh->lh_crc != 0 && be32_to_cpu(lh->lh_crc) != crc))
		वापस 1;

	head->lh_sequence = be64_to_cpu(lh->lh_sequence);
	head->lh_flags = be32_to_cpu(lh->lh_flags);
	head->lh_tail = be32_to_cpu(lh->lh_tail);
	head->lh_blkno = be32_to_cpu(lh->lh_blkno);

	head->lh_local_total = be64_to_cpu(lh->lh_local_total);
	head->lh_local_मुक्त = be64_to_cpu(lh->lh_local_मुक्त);
	head->lh_local_dinodes = be64_to_cpu(lh->lh_local_dinodes);

	वापस 0;
पूर्ण
/**
 * get_log_header - पढ़ो the log header क्रम a given segment
 * @jd: the journal
 * @blk: the block to look at
 * @head: the log header to वापस
 *
 * Read the log header क्रम a given segement in a given journal.  Do a few
 * sanity checks on it.
 *
 * Returns: 0 on success,
 *          1 अगर the header was invalid or incomplete,
 *          त्रुटि_सं on error
 */

अटल पूर्णांक get_log_header(काष्ठा gfs2_jdesc *jd, अचिन्हित पूर्णांक blk,
			  काष्ठा gfs2_log_header_host *head)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा buffer_head *bh;
	पूर्णांक error;

	error = gfs2_replay_पढ़ो_block(jd, blk, &bh);
	अगर (error)
		वापस error;

	error = __get_log_header(sdp, (स्थिर काष्ठा gfs2_log_header *)bh->b_data,
				 blk, head);
	brअन्यथा(bh);

	वापस error;
पूर्ण

/**
 * क्रमeach_descriptor - go through the active part of the log
 * @jd: the journal
 * @start: the first log header in the active region
 * @end: the last log header (करोn't process the contents of this entry))
 * @pass: iteration number (क्रमeach_descriptor() is called in a क्रम() loop)
 *
 * Call a given function once क्रम every log descriptor in the active
 * portion of the log.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक क्रमeach_descriptor(काष्ठा gfs2_jdesc *jd, u32 start,
			      अचिन्हित पूर्णांक end, पूर्णांक pass)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_log_descriptor *ld;
	पूर्णांक error = 0;
	u32 length;
	__be64 *ptr;
	अचिन्हित पूर्णांक offset = माप(काष्ठा gfs2_log_descriptor);
	offset += माप(__be64) - 1;
	offset &= ~(माप(__be64) - 1);

	जबतक (start != end) अणु
		error = gfs2_replay_पढ़ो_block(jd, start, &bh);
		अगर (error)
			वापस error;
		अगर (gfs2_meta_check(sdp, bh)) अणु
			brअन्यथा(bh);
			वापस -EIO;
		पूर्ण
		ld = (काष्ठा gfs2_log_descriptor *)bh->b_data;
		length = be32_to_cpu(ld->ld_length);

		अगर (be32_to_cpu(ld->ld_header.mh_type) == GFS2_METATYPE_LH) अणु
			काष्ठा gfs2_log_header_host lh;
			error = get_log_header(jd, start, &lh);
			अगर (!error) अणु
				gfs2_replay_incr_blk(jd, &start);
				brअन्यथा(bh);
				जारी;
			पूर्ण
			अगर (error == 1) अणु
				gfs2_consist_inode(GFS2_I(jd->jd_inode));
				error = -EIO;
			पूर्ण
			brअन्यथा(bh);
			वापस error;
		पूर्ण अन्यथा अगर (gfs2_metatype_check(sdp, bh, GFS2_METATYPE_LD)) अणु
			brअन्यथा(bh);
			वापस -EIO;
		पूर्ण
		ptr = (__be64 *)(bh->b_data + offset);
		error = lops_scan_elements(jd, start, ld, ptr, pass);
		अगर (error) अणु
			brअन्यथा(bh);
			वापस error;
		पूर्ण

		जबतक (length--)
			gfs2_replay_incr_blk(jd, &start);

		brअन्यथा(bh);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * clean_journal - mark a dirty journal as being clean
 * @jd: the journal
 * @head: the head journal to start from
 *
 * Returns: त्रुटि_सं
 */

अटल व्योम clean_journal(काष्ठा gfs2_jdesc *jd,
			  काष्ठा gfs2_log_header_host *head)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	u32 lblock = head->lh_blkno;

	gfs2_replay_incr_blk(jd, &lblock);
	gfs2_ग_लिखो_log_header(sdp, jd, head->lh_sequence + 1, 0, lblock,
			      GFS2_LOG_HEAD_UNMOUNT | GFS2_LOG_HEAD_RECOVERY,
			      REQ_PREFLUSH | REQ_FUA | REQ_META | REQ_SYNC);
	अगर (jd->jd_jid == sdp->sd_lockकाष्ठा.ls_jid) अणु
		sdp->sd_log_flush_head = lblock;
		gfs2_log_incr_head(sdp);
	पूर्ण
पूर्ण


अटल व्योम gfs2_recovery_करोne(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक jid,
                               अचिन्हित पूर्णांक message)
अणु
	अक्षर env_jid[20];
	अक्षर env_status[20];
	अक्षर *envp[] = अणु env_jid, env_status, शून्य पूर्ण;
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;

        ls->ls_recover_jid_करोne = jid;
        ls->ls_recover_jid_status = message;
	प्र_लिखो(env_jid, "JID=%u", jid);
	प्र_लिखो(env_status, "RECOVERY=%s",
		message == LM_RD_SUCCESS ? "Done" : "Failed");
        kobject_uevent_env(&sdp->sd_kobj, KOBJ_CHANGE, envp);

	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_recovery_result)
		sdp->sd_lockकाष्ठा.ls_ops->lm_recovery_result(sdp, jid, message);
पूर्ण

/**
 * update_statfs_inode - Update the master statfs inode or zero out the local
 *			 statfs inode क्रम a given journal.
 * @jd: The journal
 * @head: If शून्य, @inode is the local statfs inode and we need to zero it out.
 *	  Otherwise, it @head contains the statfs change info that needs to be
 *	  synced to the master statfs inode (poपूर्णांकed to by @inode).
 * @inode: statfs inode to update.
 */
अटल पूर्णांक update_statfs_inode(काष्ठा gfs2_jdesc *jd,
			       काष्ठा gfs2_log_header_host *head,
			       काष्ठा inode *inode)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा gfs2_inode *ip;
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_statfs_change_host sc;
	पूर्णांक error = 0;

	BUG_ON(!inode);
	ip = GFS2_I(inode);

	error = gfs2_meta_inode_buffer(ip, &bh);
	अगर (error)
		जाओ out;

	spin_lock(&sdp->sd_statfs_spin);

	अगर (head) अणु /* Update the master statfs inode */
		gfs2_statfs_change_in(&sc, bh->b_data + माप(काष्ठा gfs2_dinode));
		sc.sc_total += head->lh_local_total;
		sc.sc_मुक्त += head->lh_local_मुक्त;
		sc.sc_dinodes += head->lh_local_dinodes;
		gfs2_statfs_change_out(&sc, bh->b_data + माप(काष्ठा gfs2_dinode));

		fs_info(sdp, "jid=%u: Updated master statfs Total:%lld, "
			"Free:%lld, Dinodes:%lld after change "
			"[%+lld,%+lld,%+lld]\n", jd->jd_jid, sc.sc_total,
			sc.sc_मुक्त, sc.sc_dinodes, head->lh_local_total,
			head->lh_local_मुक्त, head->lh_local_dinodes);
	पूर्ण अन्यथा अणु /* Zero out the local statfs inode */
		स_रखो(bh->b_data + माप(काष्ठा gfs2_dinode), 0,
		       माप(काष्ठा gfs2_statfs_change));
		/* If it's our own journal, reset any in-memory changes too */
		अगर (jd->jd_jid == sdp->sd_lockकाष्ठा.ls_jid) अणु
			स_रखो(&sdp->sd_statfs_local, 0,
			       माप(काष्ठा gfs2_statfs_change_host));
		पूर्ण
	पूर्ण
	spin_unlock(&sdp->sd_statfs_spin);

	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	gfs2_inode_metasync(ip->i_gl);

out:
	वापस error;
पूर्ण

/**
 * recover_local_statfs - Update the master and local statfs changes क्रम this
 *			  journal.
 *
 * Previously, statfs updates would be पढ़ो in from the local statfs inode and
 * synced to the master statfs inode during recovery.
 *
 * We now use the statfs updates in the journal head to update the master statfs
 * inode instead of पढ़ोing in from the local statfs inode. To preserve backward
 * compatibility with kernels that can't करो this, we still need to keep the
 * local statfs inode up to date by writing changes to it. At some poपूर्णांक in the
 * future, we can करो away with the local statfs inodes altogether and keep the
 * statfs changes solely in the journal.
 *
 * @jd: the journal
 * @head: the journal head
 *
 * Returns: त्रुटि_सं
 */
अटल व्योम recover_local_statfs(काष्ठा gfs2_jdesc *jd,
				 काष्ठा gfs2_log_header_host *head)
अणु
	पूर्णांक error;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	अगर (!head->lh_local_total && !head->lh_local_मुक्त
	    && !head->lh_local_dinodes) /* No change */
		जाओ zero_local;

	 /* First update the master statfs inode with the changes we
	  * found in the journal. */
	error = update_statfs_inode(jd, head, sdp->sd_statfs_inode);
	अगर (error)
		जाओ out;

zero_local:
	/* Zero out the local statfs inode so any changes in there
	 * are not re-recovered. */
	error = update_statfs_inode(jd, शून्य,
				    find_local_statfs_inode(sdp, jd->jd_jid));
out:
	वापस;
पूर्ण

व्योम gfs2_recover_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gfs2_jdesc *jd = container_of(work, काष्ठा gfs2_jdesc, jd_work);
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा gfs2_log_header_host head;
	काष्ठा gfs2_holder j_gh, ji_gh, thaw_gh;
	kसमय_प्रकार t_start, t_jlck, t_jhd, t_tlck, t_rep;
	पूर्णांक ro = 0;
	अचिन्हित पूर्णांक pass;
	पूर्णांक error = 0;
	पूर्णांक jlocked = 0;

	अगर (gfs2_withdrawn(sdp)) अणु
		fs_err(sdp, "jid=%u: Recovery not attempted due to withdraw.\n",
		       jd->jd_jid);
		जाओ fail;
	पूर्ण
	t_start = kसमय_get();
	अगर (sdp->sd_args.ar_spectator)
		जाओ fail;
	अगर (jd->jd_jid != sdp->sd_lockकाष्ठा.ls_jid) अणु
		fs_info(sdp, "jid=%u: Trying to acquire journal lock...\n",
			jd->jd_jid);
		jlocked = 1;
		/* Acquire the journal lock so we can करो recovery */

		error = gfs2_glock_nq_num(sdp, jd->jd_jid, &gfs2_journal_glops,
					  LM_ST_EXCLUSIVE,
					  LM_FLAG_NOEXP | LM_FLAG_TRY | GL_NOCACHE,
					  &j_gh);
		चयन (error) अणु
		हाल 0:
			अवरोध;

		हाल GLR_TRYFAILED:
			fs_info(sdp, "jid=%u: Busy\n", jd->jd_jid);
			error = 0;
			जाओ fail;

		शेष:
			जाओ fail;
		पूर्ण

		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED,
					   LM_FLAG_NOEXP | GL_NOCACHE, &ji_gh);
		अगर (error)
			जाओ fail_gunlock_j;
	पूर्ण अन्यथा अणु
		fs_info(sdp, "jid=%u, already locked for use\n", jd->jd_jid);
	पूर्ण

	t_jlck = kसमय_get();
	fs_info(sdp, "jid=%u: Looking at journal...\n", jd->jd_jid);

	error = gfs2_jdesc_check(jd);
	अगर (error)
		जाओ fail_gunlock_ji;

	error = gfs2_find_jhead(jd, &head, true);
	अगर (error)
		जाओ fail_gunlock_ji;
	t_jhd = kसमय_get();
	fs_info(sdp, "jid=%u: Journal head lookup took %lldms\n", jd->jd_jid,
		kसमय_ms_delta(t_jhd, t_jlck));

	अगर (!(head.lh_flags & GFS2_LOG_HEAD_UNMOUNT)) अणु
		fs_info(sdp, "jid=%u: Acquiring the transaction lock...\n",
			jd->jd_jid);

		/* Acquire a shared hold on the मुक्तze lock */

		error = gfs2_मुक्तze_lock(sdp, &thaw_gh, LM_FLAG_PRIORITY);
		अगर (error)
			जाओ fail_gunlock_ji;

		अगर (test_bit(SDF_RORECOVERY, &sdp->sd_flags)) अणु
			ro = 1;
		पूर्ण अन्यथा अगर (test_bit(SDF_JOURNAL_CHECKED, &sdp->sd_flags)) अणु
			अगर (!test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))
				ro = 1;
		पूर्ण अन्यथा अणु
			अगर (sb_rकरोnly(sdp->sd_vfs)) अणु
				/* check अगर device itself is पढ़ो-only */
				ro = bdev_पढ़ो_only(sdp->sd_vfs->s_bdev);
				अगर (!ro) अणु
					fs_info(sdp, "recovery required on "
						"read-only filesystem.\n");
					fs_info(sdp, "write access will be "
						"enabled during recovery.\n");
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (ro) अणु
			fs_warn(sdp, "jid=%u: Can't replay: read-only block "
				"device\n", jd->jd_jid);
			error = -EROFS;
			जाओ fail_gunlock_thaw;
		पूर्ण

		t_tlck = kसमय_get();
		fs_info(sdp, "jid=%u: Replaying journal...0x%x to 0x%x\n",
			jd->jd_jid, head.lh_tail, head.lh_blkno);

		/* We take the sd_log_flush_lock here primarily to prevent log
		 * flushes and simultaneous journal replays from stomping on
		 * each other wrt jd_log_bio. */
		करोwn_पढ़ो(&sdp->sd_log_flush_lock);
		क्रम (pass = 0; pass < 2; pass++) अणु
			lops_beक्रमe_scan(jd, &head, pass);
			error = क्रमeach_descriptor(jd, head.lh_tail,
						   head.lh_blkno, pass);
			lops_after_scan(jd, error, pass);
			अगर (error) अणु
				up_पढ़ो(&sdp->sd_log_flush_lock);
				जाओ fail_gunlock_thaw;
			पूर्ण
		पूर्ण

		recover_local_statfs(jd, &head);
		clean_journal(jd, &head);
		up_पढ़ो(&sdp->sd_log_flush_lock);

		gfs2_मुक्तze_unlock(&thaw_gh);
		t_rep = kसमय_get();
		fs_info(sdp, "jid=%u: Journal replayed in %lldms [jlck:%lldms, "
			"jhead:%lldms, tlck:%lldms, replay:%lldms]\n",
			jd->jd_jid, kसमय_ms_delta(t_rep, t_start),
			kसमय_ms_delta(t_jlck, t_start),
			kसमय_ms_delta(t_jhd, t_jlck),
			kसमय_ms_delta(t_tlck, t_jhd),
			kसमय_ms_delta(t_rep, t_tlck));
	पूर्ण

	gfs2_recovery_करोne(sdp, jd->jd_jid, LM_RD_SUCCESS);

	अगर (jlocked) अणु
		gfs2_glock_dq_uninit(&ji_gh);
		gfs2_glock_dq_uninit(&j_gh);
	पूर्ण

	fs_info(sdp, "jid=%u: Done\n", jd->jd_jid);
	जाओ करोne;

fail_gunlock_thaw:
	gfs2_मुक्तze_unlock(&thaw_gh);
fail_gunlock_ji:
	अगर (jlocked) अणु
		gfs2_glock_dq_uninit(&ji_gh);
fail_gunlock_j:
		gfs2_glock_dq_uninit(&j_gh);
	पूर्ण

	fs_info(sdp, "jid=%u: %s\n", jd->jd_jid, (error) ? "Failed" : "Done");
fail:
	jd->jd_recover_error = error;
	gfs2_recovery_करोne(sdp, jd->jd_jid, LM_RD_GAVEUP);
करोne:
	clear_bit(JDF_RECOVERY, &jd->jd_flags);
	smp_mb__after_atomic();
	wake_up_bit(&jd->jd_flags, JDF_RECOVERY);
पूर्ण

पूर्णांक gfs2_recover_journal(काष्ठा gfs2_jdesc *jd, bool रुको)
अणु
	पूर्णांक rv;

	अगर (test_and_set_bit(JDF_RECOVERY, &jd->jd_flags))
		वापस -EBUSY;

	/* we have JDF_RECOVERY, queue should always succeed */
	rv = queue_work(gfs_recovery_wq, &jd->jd_work);
	BUG_ON(!rv);

	अगर (रुको)
		रुको_on_bit(&jd->jd_flags, JDF_RECOVERY,
			    TASK_UNINTERRUPTIBLE);

	वापस रुको ? jd->jd_recover_error : 0;
पूर्ण

